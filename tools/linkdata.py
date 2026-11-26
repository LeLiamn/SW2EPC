"""List or extract Samurai Warriors 2: Empires LINKDATA containers (LINKDATA.ANS/.BNS/.CNS).

Format documented in docs/formats/LINKDATA.md. The tool reads the disc image directly.
LINKDATA files have no file names: entries are numbered, and extracted files are named
<index>.<guessed extension> from their first bytes.

Usage:
  py tools/linkdata.py image.iso list [ANS|BNS|CNS]
  py tools/linkdata.py image.iso extract out_dir [ANS|BNS|CNS] [first[-last]]
  py tools/linkdata.py file.bin list                  a LINKDATA blob already extracted
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from iso_list import SECTOR, list_image  # noqa: E402

MAGIC = 0x00033B59
HEADER = 16

SIGNATURES = [
    (b"TIM2", "tm2"),
    (b"PAC0", "pac"),
    (b"PS2 ", "ps2"),
    (b"\x00\x00\x01\xba", "pss"),
    (struct.pack("<I", MAGIC), "linkdata"),
]


class LinkdataError(ValueError):
    pass


def parse_header(data):
    magic, count, align, _ = struct.unpack_from("<4I", data, 0)
    if magic != MAGIC:
        raise LinkdataError(f"Bad magic 0x{magic:08x}")
    entries = []
    for i in range(count):
        block, size = struct.unpack_from("<2I", data, HEADER + 8 * i)
        entries.append(dict(index=i, offset=block * align, size=size))
    return dict(count=count, align=align, entries=entries)


def guess_extension(head):
    for sig, ext in SIGNATURES:
        if head.startswith(sig):
            return ext
    return "bin"


def open_container(image, which):
    """Return (file, base offset, parsed table) for LINKDATA.<which> inside the image."""
    for name, lba, _ in list_image(image)[2]:
        if os.path.basename(name).upper() == f"LINKDATA.{which.upper()}":
            f = open(image, "rb")
            base = lba * SECTOR
            f.seek(base)
            head = f.read(HEADER)
            count = struct.unpack_from("<I", head, 4)[0]
            table = parse_header(head + f.read(8 * count))
            return f, base, table
    raise FileNotFoundError(f"LINKDATA.{which} not found")


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    source, command = sys.argv[1], sys.argv[2]

    if not source.lower().endswith(".iso"):
        data = open(source, "rb").read()
        table = parse_header(data)
        for e in table["entries"]:
            head = data[e["offset"]:e["offset"] + 4]
            print(f"{e['index']:5d} 0x{e['offset']:08x} {e['size']:>10}  {guess_extension(head)}")
        return

    args = sys.argv[3:]
    out_dir = args.pop(0) if command == "extract" else None
    which = [a.upper() for a in args if a.upper() in ("ANS", "BNS", "CNS")] or ["ANS", "BNS", "CNS"]
    span = next((a for a in args if a[0].isdigit()), None)
    first, last = 0, None
    if span:
        first, _, last = span.partition("-")
        first, last = int(first), int(last or first)

    for w in which:
        f, base, table = open_container(source, w)
        print(f"LINKDATA.{w}: {table['count']} entries, alignment 0x{table['align']:x}")
        for e in table["entries"][first:None if last is None else last + 1]:
            f.seek(base + e["offset"])
            if command == "list":
                head = f.read(4)
                print(f"{e['index']:5d} 0x{e['offset']:08x} {e['size']:>10}  {guess_extension(head)}")
            elif command == "extract":
                data = f.read(e["size"])
                dest = os.path.join(out_dir, w, f"{e['index']:04d}.{guess_extension(data[:4])}")
                os.makedirs(os.path.dirname(dest), exist_ok=True)
                with open(dest, "wb") as out:
                    out.write(data)
        f.close()


if __name__ == "__main__":
    main()
