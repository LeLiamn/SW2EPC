"""Battlefield terrain files (LINKDATA leaves starting `00 C0 04 66`), see docs/formats/BATTLEFIELD.md.

The structure comes from the game code that reads them (Stage.c, func_00196540 and the terrain
drawing code around 0x00194D10 and 0x00200490).

Usage:
  py tools/battlefield.py FILE.bin                 print the file's structure
  py tools/battlefield.py FILE.bin OUT.obj         export the terrain (heights) as a Wavefront OBJ
  py tools/battlefield.py --check image.iso        parse every battlefield file on the disc
"""
import os
import struct
import sys

MAGIC = bytes.fromhex("00c00466")
CELL = 500.0                 # world units between two grid vertices
VERTEX = 20                  # bytes per grid vertex
LAYER_SIDE = 50              # a layer is 50 x 50 cells of 12 bytes
LAYER_CELL = 12
TILE = 12
REGS = 8
UV = 16


class BattlefieldError(Exception):
    pass


PAD = bytes([0]) + bytes([0xCC]) * 7


def _filler(b):
    """Padding the original tools left at the end of a section (to a 16-byte boundary): 0x00 then
    0xCC bytes, and past them leftovers of memory."""
    return not b or b[:8] == PAD[:len(b)]


def _records(data, start, end, size, name):
    """Number of `size`-byte records in [start, end), the rest being padding (shorter than
    16 bytes, or one record's worth more when the padding starts inside the last record slot)."""
    count = (end - start) // size
    while count and data[start + (count - 1) * size:start + (count - 1) * size + 8] == PAD:
        count -= 1
    tail = data[start + count * size:end]
    if len(tail) >= 16 + size or not _filler(tail):
        raise BattlefieldError(f"{name}: {len(tail)} bytes left after {count} records")
    return count


def parse(data):
    """Structure of a battlefield file (raises BattlefieldError when something does not fit)."""
    if data[:4] != MAGIC or len(data) < 0x100:
        raise BattlefieldError("not a battlefield file")
    offs = list(struct.unpack_from("<9I", data, 0x80))
    width, height = data[0xD0], data[0xD1]
    origins = [(data[0xD2 + 2 * i], data[0xD3 + 2 * i]) for i in range(5)]
    layered = struct.unpack_from("<I", data, 0xDC)[0]
    used = [o for o in offs if o]
    if used != sorted(used) or used[-1] > len(data) or offs[0] < 0x100:
        raise BattlefieldError("section offsets out of order")

    def end_of(i):
        later = [o for o in offs[i + 1:] if o > offs[i]]
        return min(later) if later else len(data)

    # Section 0: the terrain grid, (width + 1) x (height + 1) vertices (empty in placeholder files).
    grid_end = end_of(0)
    if grid_end - offs[0] >= (width + 1) * (height + 1) * VERTEX:
        nvert = (width + 1) * (height + 1)
        if not _filler(data[offs[0] + nvert * VERTEX:grid_end]):
            raise BattlefieldError("terrain grid: unexpected bytes after the vertices")
    elif grid_end - offs[0] <= 16:            # placeholder: no grid, only padding
        nvert = 0
    else:
        raise BattlefieldError("terrain grid too small")

    # Sections 1-5: five layers of 50 x 50 cells (only when the header's flag is set).
    layers = []
    if layered:
        for i in range(5):
            start = offs[1 + i]
            if end_of(1 + i) - start < LAYER_SIDE * LAYER_SIDE * LAYER_CELL:
                raise BattlefieldError(f"layer {i} too small")
            layers.append(start)
    elif any(offs[1:6]):
        raise BattlefieldError("layer offsets without the layer flag")

    # Sections 6-8: tiles (12 bytes), register sets (8 bytes), texture coordinates (16 bytes).
    ntile = _records(data, offs[6], offs[7], TILE, "tiles")
    nregs = _records(data, offs[7], offs[8], REGS, "register sets")
    nuv = _records(data, offs[8], len(data), UV, "texture coordinates")

    info = {"width": width, "height": height, "origins": origins, "layered": layered,
            "grid": offs[0], "vertices": nvert, "layers": layers, "tiles": offs[6], "ntile": ntile,
            "regs": offs[7], "nregs": nregs, "uvs": offs[8], "nuv": nuv}

    for i in range(ntile):
        material, regs, *uv = struct.unpack_from("<6H", data, offs[6] + i * TILE)
        if regs >= nregs or any(u >= nuv for u in uv):
            raise BattlefieldError(f"tile {i}: index out of range")
    for i in range(nvert):
        for k in range(3):
            t = struct.unpack_from("<H", data, offs[0] + i * VERTEX + 6 + 2 * k)[0]
            if t != 0xFFFF and t >= ntile:
                raise BattlefieldError(f"vertex {i}: tile {t} out of range")
    for start in layers:
        for c in range(LAYER_SIDE * LAYER_SIDE):
            t = struct.unpack_from("<H", data, start + c * LAYER_CELL + 4)[0]
            if t != 0xFFFF and t >= ntile:
                raise BattlefieldError(f"layer cell {c}: tile {t} out of range")
    return info


def vertex(data, info, x, z):
    """(height, tiles[3], colour, diagonal) of grid vertex (x, z)."""
    off = info["grid"] + (x + z * (info["width"] + 1)) * VERTEX
    h, t0, t1, t2 = struct.unpack_from("<h3H", data, off + 4)
    return h, (t0, t1, t2), data[off + 0xC] & 0x7F, data[off + 0xD] & 3


def export_obj(data, info, path):
    """Terrain heights as a mesh: one vertex per grid point, two triangles per cell (split along
    the diagonal the file chooses). The game's Y axis points down, so heights are negated."""
    w, h = info["width"], info["height"]
    if not info["vertices"]:
        raise BattlefieldError("placeholder file: no terrain grid")
    with open(path, "w", encoding="utf-8", newline="\n") as out:
        out.write("# battlefield terrain exported by tools/battlefield.py\n")
        for z in range(h + 1):
            for x in range(w + 1):
                y = vertex(data, info, x, z)[0]
                out.write(f"v {x * CELL:.1f} {-y:.1f} {z * CELL:.1f}\n")
        for z in range(h):
            for x in range(w):
                a = 1 + x + z * (w + 1)
                b, c, d = a + 1, a + w + 1, a + w + 2
                if vertex(data, info, x, z)[3] & 1:
                    out.write(f"f {a} {c} {b}\nf {b} {c} {d}\n")
                else:
                    out.write(f"f {a} {c} {d}\nf {a} {d} {b}\n")


def iter_files(image):
    """(path, data) of every battlefield file of a disc image."""
    here = os.path.dirname(os.path.abspath(__file__))
    sys.path.insert(0, here)
    import pack
    import progress
    disc = open(image, "rb")
    for name, lba, size in progress.list_image(image)[2]:
        if os.path.basename(name).upper() != "LINKDATA.BNS":
            continue
        disc.seek(lba * progress.SECTOR)
        for path, leaf in pack.iter_leaves(disc.read(size)):
            if leaf[:4] == MAGIC:
                yield path, leaf


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] == "--check":
        ok = bad = placeholders = 0
        for path, leaf in iter_files(sys.argv[2]):
            try:
                info = parse(leaf)
                ok += 1
                placeholders += info["vertices"] == 0
            except BattlefieldError as e:
                bad += 1
                print(f"{path}: {e}")
        print(f"{ok} parsed ({placeholders} placeholders without terrain), {bad} failed")
        return
    data = open(sys.argv[1], "rb").read()
    info = parse(data)
    for k, v in info.items():
        print(f"{k}: {v}")
    if len(sys.argv) > 2:
        export_obj(data, info, sys.argv[2])
        print("wrote", sys.argv[2])


if __name__ == "__main__":
    main()
