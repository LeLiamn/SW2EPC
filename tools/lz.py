"""LZ-compressed files of LINKDATA.BNS (SceneTitle.c's func_00279F20 and its four methods),
see docs/formats/LZ.md.

Method 2 (func_00279D40): header u32 method, u32 decompressed size, u32 offset of the match
stream, u32 offset of the literal stream; from +0x10, 64-bit flag words read from the top bit
down: 1 = copy a literal byte, 0 = a 16-bit match (low 12 bits: position in the current 4 KB
window, 1-based, else in the previous window; high 4 bits: length - 3); a match with position 0
ends the data.

Usage:
  py tools/lz.py FILE.bin OUT.bin
"""
import struct
import sys


class LzError(Exception):
    pass


def header(data):
    if len(data) < 16:
        raise LzError("too small")
    method, size, matches, literals = struct.unpack_from("<4I", data, 0)
    if method > 3 or not 0 < size < 1 << 26 or not 16 <= matches <= len(data) or \
            not 16 <= literals <= len(data):
        raise LzError("bad header")
    return method, size, matches & ~3, literals & ~3


def decompress(data):
    method, size, mpos, lpos = header(data)
    if method != 2:
        raise LzError(f"method {method} not supported")
    out = bytearray()
    fpos, bit, word = 8, 0, 0
    while True:
        bit >>= 1
        if bit == 0:
            fpos += 8
            if fpos + 8 > len(data):
                raise LzError("flags past the end")
            word = struct.unpack_from("<Q", data, fpos)[0]
            bit = 1 << 63
        if word & bit:
            if lpos >= len(data):
                raise LzError("literals past the end")
            out.append(data[lpos])
            lpos += 1
            continue
        if mpos + 2 > len(data):
            raise LzError("matches past the end")
        token = struct.unpack_from("<H", data, mpos)[0]
        mpos += 2
        where = token & 0xFFF
        if where == 0:
            break
        pos = len(out)
        src = (pos & ~0xFFF) + where - 1
        if (pos & 0xFFF) < where:
            src -= 0x1000
        if src < 0:
            raise LzError("match before the start")
        for _ in range((token >> 12) + 3):
            out.append(out[src])
            src += 1
    if len(out) != size:
        raise LzError(f"decompressed {len(out)} bytes, header says {size}")
    return bytes(out)


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    out = decompress(open(sys.argv[1], "rb").read())
    open(sys.argv[2], "wb").write(out)
    print(f"wrote {len(out)} bytes")


if __name__ == "__main__":
    main()
