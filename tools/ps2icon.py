"""PS2 memory-card icon (BNS entry 0061, loaded by saveload.c), see docs/formats/MISC.md.

The standard PS2 3D save icon: a header, the vertices of each animation shape, the animation
keys, then a 128 x 128 texture (16-bit, uncompressed here).

Usage:
  py tools/ps2icon.py FILE.ico [OUT.png]
"""
import struct
import sys

sys.path.insert(0, __import__("os").path.dirname(__import__("os").path.abspath(__file__)))
import tim2  # noqa: E402


class IconError(Exception):
    pass


def parse(data):
    """{"shapes", "vertices", "frames", "texture"} (raises IconError when it does not end right)."""
    if len(data) < 20:
        raise IconError("too small")
    version, shapes, tex_type, _, count = struct.unpack_from("<IIIfI", data, 0)
    if version != 0x10000 or not 1 <= shapes <= 16:
        raise IconError("bad header")
    p = 20 + count * (shapes * 8 + 8 + 4 + 4)    # per vertex: shapes x position, normal, uv, colour
    if p + 20 > len(data):
        raise IconError("vertices past the end")
    _, _, _, _, frames = struct.unpack_from("<IIfII", data, p)
    p += 20
    for _ in range(frames):
        _, keys = struct.unpack_from("<II", data, p)
        p += 8 + 8 * keys                        # keys: (time, value) floats
    if tex_type & 8:
        raise IconError("compressed texture (not used here)")
    if len(data) - p != 128 * 128 * 2:
        raise IconError("texture size")
    return {"shapes": shapes, "vertices": count, "frames": frames, "texture": p}


def texture_png(data, info, path):
    rgba = bytearray()
    for i in range(128 * 128):
        c = struct.unpack_from("<H", data, info["texture"] + 2 * i)[0]
        rgba += bytes(((c & 31) << 3, ((c >> 5) & 31) << 3, ((c >> 10) & 31) << 3, 255))
    open(path, "wb").write(tim2.png_bytes(128, 128, bytes(rgba)))


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    data = open(sys.argv[1], "rb").read()
    info = parse(data)
    print(info)
    if len(sys.argv) > 2:
        texture_png(data, info, sys.argv[2])
        print("wrote", sys.argv[2])


if __name__ == "__main__":
    main()
