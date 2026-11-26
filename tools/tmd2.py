"""Read TMD2 files (static scene objects of the battlefields) and export them as OBJ.

A TMD2 is a header with a world bounding box, then VIF packets for the VU1: per batch a GIF tag,
the UVs (V2-32), vertex colours (V4-8), positions then normals (V3-32). Format documented in
docs/formats/TMD2.md.

Usage:
  py tools/tmd2.py file.tmd2 out.obj
  py tools/tmd2.py --iso image.iso check
  py tools/tmd2.py --iso image.iso scene PACK out.obj      every TMD2 of a pack (e.g. 2528.3.0)
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

MAGIC = b"TMD2"
BITS = {0: 32, 1: 16, 2: 8, 3: 5}


class Tmd2Error(ValueError):
    pass


def vif_commands(data, p):
    """Yield (kind, count, data offset) for the VIF commands from p. kind is e.g. 'V3-32'."""
    while p + 4 <= len(data):
        w = struct.unpack_from("<I", data, p)[0]
        cmd, num, imm = (w >> 24) & 0x7F, (w >> 16) & 0xFF, w & 0xFFFF
        p += 4
        if cmd >= 0x60:
            vn, vl = (cmd >> 2) & 3, cmd & 3
            n = num or 256
            size = (n * (vn + 1) * BITS[vl] + 31) // 32 * 4 if vl != 3 else (n * 2 + 3) // 4 * 4
            yield f"V{vn + 1}-{BITS[vl]}", n, p
            p += size
        elif cmd in (0x50, 0x51):
            p += (imm or 65536) * 16
        elif cmd == 0x4A:
            p += (num or 256) * 8
        elif cmd == 0x20:
            p += 4
        elif cmd in (0x30, 0x31):
            p += 16
        elif cmd not in (0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x10, 0x11, 0x13, 0x14, 0x15, 0x17):
            raise Tmd2Error(f"Unknown VIF command 0x{cmd:02x} at 0x{p - 4:x}")
    if p != len(data):
        raise Tmd2Error("VIF stream does not end at the end of the file")


def parse(data):
    if data[:4] != MAGIC:
        raise Tmd2Error("Missing TMD2 signature")
    lo = struct.unpack_from("<3f", data, 0x50)
    hi = struct.unpack_from("<3f", data, 0x60)
    start = data.find(b"\x02\xc0\x01\x6c", 0x40)
    if start < 0:
        raise Tmd2Error("No vertex batch found")
    batches, cur = [], None
    for kind, n, p in vif_commands(data, start):
        if kind == "V4-32" and n == 1:
            tag = struct.unpack_from("<Q", data, p)[0]
            cur = dict(nloop=tag & 0x7FFF, prim=(tag >> 47) & 7, uv=[], rgba=[], pos=[], nrm=[])
            batches.append(cur)
        elif cur is None:
            continue
        elif kind == "V2-32":
            cur["uv"] = [struct.unpack_from("<2f", data, p + 8 * k) for k in range(n)]
        elif kind == "V4-8":
            cur["rgba"] = [tuple(data[p + 4 * k:p + 4 * k + 4]) for k in range(n)]
        elif kind == "V3-32":
            vec = [struct.unpack_from("<3f", data, p + 12 * k) for k in range(n)]
            cur["pos"], cur["nrm"] = vec[:cur["nloop"]], vec[cur["nloop"]:2 * cur["nloop"]]
    # Placement: half the objects store world positions, the other half positions centred on
    # their bounding box. Positions that do not fit the box get the box centre added.
    pts = [q for b in batches for q in b["pos"]]
    in_box = all(lo[i] - 1 <= q[i] <= hi[i] + 1 for q in pts for i in range(3))
    offset = (0.0, 0.0, 0.0) if in_box else tuple((lo[i] + hi[i]) / 2 for i in range(3))
    return dict(box=(lo, hi), offset=offset, batches=batches)


def triangles(batch, base):
    n = len(batch["pos"])
    if batch["prim"] == 4:
        for i in range(2, n):
            yield (base + i - 2, base + i - 1, base + i) if i % 2 == 0 else (base + i - 1, base + i - 2, base + i)
    elif batch["prim"] == 3:
        for i in range(0, n - 2, 3):
            yield base + i, base + i + 1, base + i + 2


def to_obj(objects):
    """OBJ text for a list of parsed TMD2 objects (Y turned up like the models)."""
    lines, faces, base = ["# Samurai Warriors 2: Empires scene objects, exported by SW2EPC"], [], 1
    for obj in objects:
        ox, oy, oz = obj["offset"]
        for b in obj["batches"]:
            for k, (x, y, z) in enumerate(b["pos"]):
                lines.append(f"v {x + ox:.4f} {-(y + oy):.4f} {-(z + oz):.4f}")
                u, v = b["uv"][k] if k < len(b["uv"]) else (0.0, 0.0)
                lines.append(f"vt {u:.5f} {1 - v:.5f}")
            for a, c, d in triangles(b, base):
                faces.append(f"f {a}/{a} {c}/{c} {d}/{d}")
            base += len(b["pos"])
    return chr(10).join(lines + faces) + chr(10)


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        with open(sys.argv[2], "w") as f:
            f.write(to_obj([parse(open(sys.argv[1], "rb").read())]))
        return
    import pack
    image, command = sys.argv[2], sys.argv[3]
    if command == "check":
        ok = bad = 0
        for path, leaf in pack.iter_bns(image):
            if leaf[:4] == MAGIC:
                try:
                    parse(leaf)
                    ok += 1
                except (Tmd2Error, struct.error) as e:
                    bad += 1
                    print(f"FAIL {path}: {e}")
        print(f"{ok} TMD2 files parse, {bad} failed")
    elif command == "scene":
        prefix, out = sys.argv[4], sys.argv[5]
        entry = int(prefix.split(".")[0])
        objects = [parse(leaf) for path, leaf in pack.iter_bns(image, entry, entry)
                   if leaf[:4] == MAGIC and path.rsplit(".", 1)[0] == prefix]
        with open(out, "w") as f:
            f.write(to_obj(objects))
        print(f"{len(objects)} objects -> {out}")


if __name__ == "__main__":
    main()
