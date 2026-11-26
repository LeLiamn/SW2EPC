"""Compute the CRC32, MD5 and SHA-1 of a disc image in a single pass.

These three values can be compared directly with the disc's entry on redump.org.

Usage: py tools/hash_image.py "Iso/my_disc.iso"
"""
import hashlib
import os
import sys
import zlib

CHUNK = 16 * 1024 * 1024


def hash_file(path):
    size = os.path.getsize(path)
    crc = 0
    md5 = hashlib.md5()
    sha1 = hashlib.sha1()
    done = 0
    with open(path, "rb") as f:
        while True:
            block = f.read(CHUNK)
            if not block:
                break
            crc = zlib.crc32(block, crc)
            md5.update(block)
            sha1.update(block)
            done += len(block)
            print(f"\r{done * 100 // size:3d} %", end="", file=sys.stderr, flush=True)
    print(file=sys.stderr)
    return {
        "size": size,
        "crc32": f"{crc & 0xFFFFFFFF:08x}",
        "md5": md5.hexdigest(),
        "sha1": sha1.hexdigest(),
    }


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(1)
    result = hash_file(sys.argv[1])
    print(f"File  : {os.path.basename(sys.argv[1])}")
    print(f"Size  : {result['size']} bytes")
    print(f"CRC32 : {result['crc32']}")
    print(f"MD5   : {result['md5']}")
    print(f"SHA-1 : {result['sha1']}")


if __name__ == "__main__":
    main()
