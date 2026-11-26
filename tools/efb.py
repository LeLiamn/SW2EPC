"""EFB visual-effect files (`EFB\\0`), see docs/formats/EFB.md.

The field meanings come from the game's effect code (effect.c, 0x001C0000-0x001CC000): the layer
walker func_001C09C0, the sprite layer (type 0) functions func_001C3490 / func_001C15E0 /
func_001C1810 / func_001C1900 / func_001C2270, and the emitter layer (type 1) func_001C4B10.

Usage:
  py tools/efb.py FILE.efb                print an effect's layers and main parameters
  py tools/efb.py --check image.iso       parse every EFB file on the disc
"""
import math
import os
import struct
import sys

MAGIC = b"EFB\0"
SIZES = {0: 336, 1: 576}     # layer type -> block size
NAMES = {0: "sprite", 1: "emitter"}


class EfbError(Exception):
    pass


def f32(data, off):
    return struct.unpack_from("<f", data, off)[0]


def u32(data, off):
    return struct.unpack_from("<I", data, off)[0]


def parse(data):
    """{"speed", "layers": [{"type", "offset", "start", ...}]} (raises EfbError)."""
    if data[:4] != MAGIC or len(data) < 0x18:
        raise EfbError("not an EFB file")
    count = u32(data, 4)
    if u32(data, 8) or u32(data, 12):
        raise EfbError("header words 8-15 not zero")
    speed = f32(data, 0x10)
    table = u32(data, 0x14)
    if table != 0x18 or not 1 <= count <= 64 or not math.isfinite(speed):
        raise EfbError("bad header")
    first = (table + 8 * count + 15) & ~15
    layers, pos = [], first
    for i in range(count):
        kind, off = struct.unpack_from("<II", data, table + 8 * i)
        if kind not in SIZES:
            raise EfbError(f"layer {i}: unknown type {kind}")
        if off != pos or off + SIZES[kind] > len(data):
            raise EfbError(f"layer {i}: block not where expected")
        layer = {"type": kind, "offset": off, "flags": u32(data, off + 4)}
        if kind == 0:
            p = off + 0x10                      # parameters
            layer.update({
                "start": f32(data, off + 0x1C),
                "texture": u32(data, p),
                "frames": (u32(data, p + 4), u32(data, p + 8)),
                "life": f32(data, p + 0x14),
                "size": (f32(data, p + 0x38), f32(data, p + 0x3C)),
                "size_random": (f32(data, p + 0x40), f32(data, p + 0x44)),
                "position": struct.unpack_from("<4f", data, p + 0x50),
                "acceleration": struct.unpack_from("<4f", data, p + 0x70),
            })
            if layer["frames"][0] > 256 or layer["frames"][1] > 256:
                raise EfbError(f"layer {i}: frame grid out of range")
        else:
            layer.update({
                "start": f32(data, off + 0x5C),
                "count": u32(data, off + 0xC),
                "count_random": u32(data, off + 0x10),
            })
        if not math.isfinite(layer["start"]) or layer["start"] < 0:
            raise EfbError(f"layer {i}: bad start time")
        layers.append(layer)
        pos = off + SIZES[kind]
    if any(data[pos:]):
        raise EfbError("bytes after the last block")
    return {"speed": speed, "layers": layers}


def iter_files(image):
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
        ok = bad = 0
        for path, leaf in iter_files(sys.argv[2]):
            try:
                parse(leaf)
                ok += 1
            except EfbError as e:
                bad += 1
                if bad <= 20:
                    print(f"{path}: {e}")
        print(f"{ok} parsed, {bad} failed")
        return
    info = parse(open(sys.argv[1], "rb").read())
    print(f"time step {info['speed']}")
    for i, layer in enumerate(info["layers"]):
        print(i, NAMES[layer["type"]], {k: v for k, v in layer.items() if k != "type"})


if __name__ == "__main__":
    main()
