"""Koei offset-table packs: the unnamed archive format nested everywhere in LINKDATA.BNS.

A pack is: u32 count, then `count` u32 offsets (non-decreasing, 4-byte aligned) from the start of
the pack, then the data. Sub-file i runs from offset[i] to offset[i+1] (the last one to the end).
Packs nest inside packs and inside LINKDATA containers. There is no signature, so detection is
heuristic but strict (see is_pack). Format documented in docs/formats/PACK.md.

Usage:
  py tools/pack.py file.bin list                      tree of a pack file
  py tools/pack.py --iso image.iso stats              leaf formats of LINKDATA.BNS, by size
  py tools/pack.py --iso image.iso extract out_dir [first[-last]]   extract the leaves
"""
import os
import struct
import sys
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import linkdata  # noqa: E402

LINKDATA_SIG = linkdata.MAGIC.to_bytes(4, "little")
SIGNATURES = [(b"TIM2", "tm2"), (b"tm3 ", "tm3"), (b"TMD2", "tmd2"), (b"PS2 ", "ps2"),
              (b"PAC0", "pac"), (b"ipu2", "ipu"), (b"\x00\x00\x01\xba", "pss")]
MAX_ENTRIES = 20000


def is_pack(data):
    """Return the offsets if `data` looks like a pack, else None."""
    if len(data) < 8:
        return None
    count = struct.unpack_from("<I", data, 0)[0]
    header = 4 + 4 * count
    if not 0 < count < MAX_ENTRIES or header > len(data):
        return None
    offsets = struct.unpack_from(f"<{count}I", data, 4)
    if not header <= offsets[0] <= ((header + 15) // 16) * 16 + 16:
        return None
    if any(o % 4 for o in offsets) or offsets[-1] > len(data):
        return None
    if any(b < a for a, b in zip(offsets, offsets[1:])):
        return None
    return offsets


def kind_of(data):
    head = data[:4]
    for sig, ext in SIGNATURES:
        if head.startswith(sig):
            return ext
    return "bin"


def iter_leaves(data, path=""):
    """Yield (path, bytes) for every leaf of `data`, opening LINKDATA containers and packs."""
    if data[:4] == LINKDATA_SIG:
        for e in linkdata.parse_header(data)["entries"]:
            yield from iter_leaves(data[e["offset"]:e["offset"] + e["size"]],
                                   f"{path}/{e['index']:04d}" if path else f"{e['index']:04d}")
        return
    offsets = is_pack(data)
    if offsets is None or kind_of(data) != "bin":
        yield path, data
        return
    bounds = list(offsets) + [len(data)]
    for i, (start, end) in enumerate(zip(bounds, bounds[1:])):
        if end > start:
            yield from iter_leaves(data[start:end], f"{path}.{i}")


def iter_bns(image, first=0, last=None):
    """Yield (path, bytes) for every leaf of LINKDATA.BNS in the disc image."""
    f, base, table = linkdata.open_container(image, "BNS")
    for e in table["entries"][first:None if last is None else last + 1]:
        f.seek(base + e["offset"])
        yield from iter_leaves(f.read(e["size"]), f"{e['index']:04d}")
    f.close()


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] != "--iso":
        data = open(sys.argv[1], "rb").read()
        for path, leaf in iter_leaves(data, os.path.basename(sys.argv[1])):
            print(f"{len(leaf):>10}  {kind_of(leaf):5}  {path}")
        return

    image, command = sys.argv[2], sys.argv[3]
    if command == "stats":
        count, size = Counter(), Counter()
        for _, leaf in iter_bns(image):
            k = kind_of(leaf) if kind_of(leaf) != "bin" else "bin:" + leaf[:4].hex()
            count[k] += 1
            size[k] += len(leaf)
        total = sum(size.values())
        print(f"{sum(count.values())} leaves, {total} bytes")
        for k, s in size.most_common(40):
            print(f"{k:14} {count[k]:7d} {s:>12} {s / total * 100:5.1f}%")
    elif command == "extract":
        out_dir = sys.argv[4]
        first, last = 0, None
        if len(sys.argv) > 5:
            a, _, b = sys.argv[5].partition("-")
            first, last = int(a), int(b or a)
        n = 0
        for path, leaf in iter_bns(image, first, last):
            dest = os.path.join(out_dir, *path.split("/")) + "." + kind_of(leaf)
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with open(dest, "wb") as out:
                out.write(leaf)
            n += 1
        print(f"{n} leaves extracted to {out_dir}")


if __name__ == "__main__":
    main()
