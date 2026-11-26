"""PAC0 files (BNS, one per voice 0x11CF-0x151D: ev_main.c loads entry 0xE3 + n, func_001DB520 plays
it with the voice), see docs/formats/PAC0.md.

A 0x20-byte header ("PAC0", "2_00JM20", u32, then three u16 counts at +0x10, +0x12, +0x14),
then three sections of 3-byte entries (func_00147C50 finds section 1 after count 0 entries,
section 2 after count 0 + count 1).

Usage:
  py tools/pac0.py FILE.pac
"""
import struct
import sys


def parse(data):
    """The three sections' entries, or None when `data` is not exactly a PAC0 file."""
    if data[:4] != b"PAC0" or len(data) < 0x20:
        return None
    counts = struct.unpack_from("<3H", data, 0x10)
    end = 0x20 + 3 * sum(counts)
    if not 0 <= len(data) - end < 16 or any(data[end:]):      # zero padding inside packs
        return None
    out, p = [], 0x20
    for c in counts:
        out.append([tuple(data[p + 3 * i:p + 3 * i + 3]) for i in range(c)])
        p += 3 * c
    return out



def parse_wrapped(data):
    """The PAC0 files of ev_message.c (BNS entries 3262+): a 16-byte header (u16, u16 0x10, ...),
    then a PAC0 file."""
    if len(data) < 0x30 or data[2:4] != bytes((0x10, 0)):
        return None
    return parse(data[16:])

def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    sections = parse(open(sys.argv[1], "rb").read())
    if sections is None:
        print("not a PAC0 file")
        return
    for i, s in enumerate(sections):
        print(f"section {i}: {len(s)} entries", s[:12])


if __name__ == "__main__":
    main()
