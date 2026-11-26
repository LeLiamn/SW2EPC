"""Read the game's 3D models ("PS2 " files) and export them as OBJ, with a quick PNG preview.

Geometry, UVs, normals, the skeleton and skinning (up to 4 weighted bones per vertex) are decoded:
models are exported in their bind pose, upright (the PS2 data has Y pointing down; the export turns
it 180 degrees around X).
Format documented in docs/formats/PS2MODEL.md.

Usage:
  py tools/ps2model.py model.ps2 out.obj [--png preview.png]
  py tools/ps2model.py --iso image.iso out_dir [--png]       every model of LINKDATA.BNS
"""
import math
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

MAGIC = b"PS2 "
GIF_REGS_ST_RGBAQ_XYZ2 = 0x412
PRIM_TRIANGLE, PRIM_TRISTRIP = 3, 4


class ModelError(ValueError):
    pass


def parse(data):
    if data[:4] != MAGIC:
        raise ModelError("Missing 'PS2 ' signature")
    geometry_offset = struct.unpack_from("<I", data, 8)[0]
    node_count, matrix_count = struct.unpack_from("<HH", data, 0x10)
    parents = struct.unpack_from(f"<{node_count}i", data, 0x14)
    links = struct.unpack_from(f"<{node_count}i", data, 0x14 + 4 * node_count)
    base = 0x14 + 8 * node_count
    nodes = []
    for i in range(node_count):
        v = struct.unpack_from("<9f", data, base + 36 * i)
        nodes.append(dict(parent=parents[i], link=links[i], rotation=v[0:3], scale=v[3:6],
                          translation=v[6:9]))
    if base + 36 * node_count > geometry_offset:
        raise ModelError("Skeleton runs past the geometry offset")
    return dict(nodes=nodes, matrix_count=matrix_count,
                strips=list(iter_strips(data, geometry_offset)))


def iter_strips(data, start):
    """Find the GIF tags (ST, RGBAQ, XYZ2) of the vertex batches and yield their vertices.

    A vertex is 1 + 2k quadwords: (s, t, flags, k), then k times (normal * weight, bone address)
    and (position in that bone's space, weight).
    """
    p = start
    while p + 16 <= len(data):
        lo, hi = struct.unpack_from("<QQ", data, p)
        nloop, nreg, flg = lo & 0x7FFF, (lo >> 60) & 0xF, (lo >> 58) & 3
        prim = (lo >> 47) & 7
        if nreg == 3 and hi == GIF_REGS_ST_RGBAQ_XYZ2 and 0 < nloop < 256 and flg == 0:
            q, verts = p + 16, []
            for _ in range(nloop):
                if q + 16 > len(data):
                    break
                s, t, flags, count = struct.unpack_from("<ffII", data, q)
                if not 1 <= count <= 4 or q + 16 + 32 * count > len(data):
                    break
                q += 16
                influences = []
                for _ in range(count):
                    nx, ny, nz, bone = struct.unpack_from("<fffI", data, q)
                    x, y, z, w = struct.unpack_from("<ffff", data, q + 16)
                    influences.append(dict(bone=bone, weight=w, position=(x, y, z),
                                           normal=(nx, ny, nz)))
                    q += 32
                verts.append(dict(uv=(s, t), skip=bool(flags & 0x8000), influences=influences))
            if len(verts) == nloop:
                yield dict(offset=p, prim=prim, vertices=verts)
                p = q
                continue
        p += 4


def mat_mul(a, b):
    return [[sum(a[i][k] * b[k][j] for k in range(4)) for j in range(4)] for i in range(4)]


def node_matrix(node):
    """Local matrix of a node: T * Rz * Ry * Rx * S (the order that gives correct characters)."""
    rx, ry, rz = node["rotation"]
    cx, sx, cy, sy, cz, sz = (math.cos(rx), math.sin(rx), math.cos(ry), math.sin(ry),
                              math.cos(rz), math.sin(rz))
    m_z = [[cz, -sz, 0, 0], [sz, cz, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]
    m_y = [[cy, 0, sy, 0], [0, 1, 0, 0], [-sy, 0, cy, 0], [0, 0, 0, 1]]
    m_x = [[1, 0, 0, 0], [0, cx, -sx, 0], [0, sx, cx, 0], [0, 0, 0, 1]]
    sc = node["scale"]
    m = mat_mul(mat_mul(mat_mul(m_z, m_y), m_x),
                [[sc[0], 0, 0, 0], [0, sc[1], 0, 0], [0, 0, sc[2], 0], [0, 0, 0, 1]])
    m[0][3], m[1][3], m[2][3] = node["translation"]
    return m


def world_matrices(nodes):
    world = [None] * len(nodes)

    def get(i):
        if world[i] is None:
            local = node_matrix(nodes[i])
            parent = nodes[i]["parent"]
            world[i] = local if parent < 0 else mat_mul(get(parent), local)
        return world[i]

    return [get(i) for i in range(len(nodes))]


def posed_vertices(model):
    """Yield, per strip, the vertices in bind pose: (position, normal, uv, skip). Y up."""
    world = world_matrices(model["nodes"])
    for strip in model["strips"]:
        out = []
        for v in strip["vertices"]:
            pos, nrm = [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]
            for inf in v["influences"]:
                m = world[min(inf["bone"] // 4, len(world) - 1)]
                x, y, z = inf["position"]
                nx, ny, nz = inf["normal"]
                for r in range(3):
                    pos[r] += inf["weight"] * (m[r][0] * x + m[r][1] * y + m[r][2] * z + m[r][3])
                    nrm[r] += m[r][0] * nx + m[r][1] * ny + m[r][2] * nz
            length = math.sqrt(sum(c * c for c in nrm)) or 1.0
            out.append(((pos[0], -pos[1], -pos[2]),
                        (nrm[0] / length, -nrm[1] / length, -nrm[2] / length), v["uv"], v["skip"]))
        yield strip["prim"], out


def triangles(prim, verts, base):
    v = verts
    if prim == PRIM_TRISTRIP:
        for i in range(2, len(v)):
            if not v[i][3]:
                a, b = (i - 2, i - 1) if i % 2 == 0 else (i - 1, i - 2)
                yield base + a, base + b, base + i
    elif prim == PRIM_TRIANGLE:
        for i in range(0, len(v) - 2, 3):
            yield base + i, base + i + 1, base + i + 2


def to_obj(model):
    lines, faces, base = ["# Samurai Warriors 2: Empires model, exported by SW2EPC"], [], 1
    for prim, verts in posed_vertices(model):
        for pos, nrm, uv, _ in verts:
            lines.append("v %.5f %.5f %.5f" % pos)
            lines.append("vt %.5f %.5f" % (uv[0], 1 - uv[1]))
            lines.append("vn %.5f %.5f %.5f" % nrm)
        for a, b, c in triangles(prim, verts, base):
            faces.append(f"f {a}/{a}/{a} {b}/{b}/{b} {c}/{c}/{c}")
        base += len(verts)
    return chr(10).join(lines + faces) + chr(10)


def preview_png(model, path, size=512, yaw=0.6):
    """Flat-shaded orthographic render, to check a model without a 3D viewer."""
    from tim2 import png_bytes
    pts, tris, base = [], [], 0
    for prim, verts in posed_vertices(model):
        pts += [v[0] for v in verts]
        tris += list(triangles(prim, verts, base))
        base += len(verts)
    img = bytearray([30, 30, 40, 255] * size * size)
    if not pts:
        open(path, "wb").write(png_bytes(size, size, bytes(img)))
        return
    c, s = math.cos(yaw), math.sin(yaw)
    P = [(x * c + z * s, y, -x * s + z * c) for x, y, z in pts]
    xs, ys = [p[0] for p in P], [p[1] for p in P]
    cx, cy = (min(xs) + max(xs)) / 2, (min(ys) + max(ys)) / 2
    scale = (size - 20) / (max(max(xs) - min(xs), max(ys) - min(ys)) or 1)
    zbuf = [-1e30] * (size * size)
    for ia, ib, ic in tris:
        a, b, cc = P[ia], P[ib], P[ic]
        u = [b[k] - a[k] for k in range(3)]
        v = [cc[k] - a[k] for k in range(3)]
        n = (u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0])
        shade = int(60 + 190 * abs(n[2]) / (math.sqrt(sum(k * k for k in n)) or 1))
        q = [((p[0] - cx) * scale + size / 2, size / 2 - (p[1] - cy) * scale, p[2]) for p in (a, b, cc)]
        den = (q[1][1] - q[2][1]) * (q[0][0] - q[2][0]) + (q[2][0] - q[1][0]) * (q[0][1] - q[2][1])
        if abs(den) < 1e-9:
            continue
        for yy in range(int(max(0, min(p[1] for p in q))), int(min(size - 1, max(p[1] for p in q))) + 1):
            for xx in range(int(max(0, min(p[0] for p in q))), int(min(size - 1, max(p[0] for p in q))) + 1):
                l1 = ((q[1][1] - q[2][1]) * (xx - q[2][0]) + (q[2][0] - q[1][0]) * (yy - q[2][1])) / den
                l2 = ((q[2][1] - q[0][1]) * (xx - q[2][0]) + (q[0][0] - q[2][0]) * (yy - q[2][1])) / den
                l3 = 1 - l1 - l2
                if min(l1, l2, l3) < 0:
                    continue
                z = l1 * q[0][2] + l2 * q[1][2] + l3 * q[2][2]
                i = yy * size + xx
                if z > zbuf[i]:
                    zbuf[i] = z
                    img[i * 4:i * 4 + 4] = bytes((shade, shade, int(shade * 0.9), 255))
    with open(path, "wb") as f:
        f.write(png_bytes(size, size, bytes(img)))


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] == "--iso":
        import pack
        image, out_dir = sys.argv[2], sys.argv[3]
        os.makedirs(out_dir, exist_ok=True)
        ok = failed = 0
        for path, leaf in pack.iter_bns(image):
            if leaf[:4] != MAGIC:
                continue
            name = path.replace("/", "_")
            try:
                model = parse(leaf)
                with open(os.path.join(out_dir, name + ".obj"), "w") as f:
                    f.write(to_obj(model))
                if "--png" in sys.argv:
                    preview_png(model, os.path.join(out_dir, name + ".png"))
                ok += 1
            except (ModelError, struct.error) as e:
                failed += 1
                print(f"FAIL {name}: {e}")
        print(f"{ok} models exported, {failed} failed")
        return
    model = parse(open(sys.argv[1], "rb").read())
    with open(sys.argv[2], "w") as f:
        f.write(to_obj(model))
    n = sum(len(s["vertices"]) for s in model["strips"])
    print(f"{len(model['nodes'])} nodes, {len(model['strips'])} batches, {n} vertices -> {sys.argv[2]}")
    if "--png" in sys.argv:
        preview_png(model, sys.argv[sys.argv.index("--png") + 1])


if __name__ == "__main__":
    main()
