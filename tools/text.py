"""Text tables of LINKDATA.BNS (system messages, dialogue lines...), see docs/formats/TEXT.md.

Three layouts, all checked down to the strings (NUL-terminated, printable):
  - count, then `count` offsets from the table's start, then the strings;
  - offsets only (the first offset gives the size of the offset table);
  - (offset, length) pairs (the first offset gives the size of the pair table).

Usage:
  py tools/text.py FILE.bin        print the strings of a table
"""
import struct
import sys


def _printable(s):
    good = sum(1 for c in s if 32 <= c < 127 or c in (9, 10, 13) or c >= 0x80)
    return good >= 0.95 * len(s)


def _strings_at(d, offs):
    out = []
    for o in offs:
        e = d.find(b"\0", o)
        if e < 0 or not _printable(d[o:e]):
            return None
        out.append(d[o:e])
    return out


def strings(d):
    """The strings of a text table, or None when `d` is not one."""
    if len(d) < 8:
        return None
    n = struct.unpack_from("<I", d, 0)[0]
    if 0 < n < 20000 and 4 + 4 * n <= len(d):                    # count + offsets
        offs = struct.unpack_from(f"<{n}I", d, 4)
        if offs[0] >= 4 + 4 * n and list(offs) == sorted(offs) and offs[-1] < len(d):
            s = _strings_at(d, offs)
            if s is not None:
                return s
    first = n
    if first % 4 == 0 and 4 <= first < len(d):                  # offsets only
        offs = struct.unpack_from(f"<{first // 4}I", d, 0)
        if list(offs) == sorted(offs) and offs[-1] < len(d):
            s = _strings_at(d, offs)
            if s is not None:
                return s
    if first % 8 == 0 and 8 <= first < len(d):                  # (offset, length) pairs
        pairs = [struct.unpack_from("<II", d, 8 * i) for i in range(first // 8)]
        p, out = first, []
        for o, length in pairs:
            text = d[o:o + length].rstrip(b"\0")
            if o < p or o + length > len(d) or not _printable(text):
                return None
            out.append(text)
            p = o
        return out
    return None



def record_tables(d):
    """Officer quotes (e.g. BNS entries 0200-0226): an offset table (the first offset gives its
    size) of records, each two u32 then a text table. Returns the list of string lists, or None."""
    if len(d) < 8:
        return None
    first = struct.unpack_from("<I", d, 0)[0]
    if first % 4 or not 8 <= first < len(d):
        return None
    offs = list(struct.unpack_from(f"<{first // 4}I", d, 0)) + [len(d)]
    if offs != sorted(offs):
        return None
    out = []
    for a, b in zip(offs, offs[1:]):
        s = strings(d[a + 8:b]) if b - a > 8 else None
        if s is None:
            return None
        out.append(s)
    return out


def pair_tables(d):
    """(offset, size) pairs (the first offset gives the size of the pair table), each part a text
    table (e.g. part 2 of BNS entry 0050). Returns the list of string lists, or None."""
    if len(d) < 16:
        return None
    first = struct.unpack_from("<I", d, 0)[0]
    if first % 8 or not 8 <= first < len(d):
        return None
    out, p = [], first
    for i in range(first // 8):
        o, size = struct.unpack_from("<II", d, 8 * i)
        if o < p or o + size > len(d):
            return None
        s = strings(d[o:o + size])
        if s is None:
            return None
        out.append(s)
        p = o + size
    return out


def plain(d):
    """A bare string (printable text, then NUL padding), e.g. the leaves of BNS entry 0128."""
    text = d.rstrip(b"\0")
    return bool(text) and len(d) > len(text) and b"\0" not in text and _printable(text)


def telop(d):
    """Movie subtitles (BNS entries 3388+, MovieTelop.c): u32 n, n (start, end) frame pairs, then
    the n NUL-terminated lines. Returns [(start, end, text)] or None."""
    if len(d) < 12:
        return None
    n = struct.unpack_from("<I", d, 0)[0]
    if not 0 < n < 1000 or 4 + 8 * n >= len(d):
        return None
    frames = struct.unpack_from(f"<{2 * n}I", d, 4)
    p, out = 4 + 8 * n, []
    for i in range(n):
        e = d.find(bytes(1), p)
        if e < 0 or not _printable(d[p:e]) or frames[2 * i] > frames[2 * i + 1]:
            return None
        out.append((frames[2 * i], frames[2 * i + 1], d[p:e]))
        p = e + 1
    return out if not any(d[p:]) else None

def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    s = strings(open(sys.argv[1], "rb").read())
    if s is None:
        print("not a text table")
        return
    for i, t in enumerate(s):
        print(i, t.decode("latin-1"))


if __name__ == "__main__":
    main()
