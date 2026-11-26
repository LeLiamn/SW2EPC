"""List the contents of a PS2 ISO9660 image, with the position (LBA) of every file.

Handles dual-layer DVDs (DVD-9): on PS2, the second layer carries its own ISO9660
volume descriptor, which most tools (7-Zip...) ignore.

Usage:
  py tools/iso_list.py image.iso
  py tools/iso_list.py image.iso --extract FILE_NAME output_dir
"""
import os
import struct
import sys

SECTOR = 2048


def read_sector(f, lba, count=1):
    f.seek(lba * SECTOR)
    return f.read(SECTOR * count)


def parse_pvd(f, base_lba):
    pvd = read_sector(f, base_lba + 16)
    if pvd[1:6] != b"CD001" or pvd[0] != 1:
        return None
    return dict(
        volume_id=pvd[40:72].decode("ascii", "replace").strip(),
        volume_size=struct.unpack_from("<I", pvd, 80)[0],
        root=pvd[156:156 + 34],
    )


def walk(f, base_lba, record, path=""):
    lba, size = struct.unpack_from("<I", record, 2)[0], struct.unpack_from("<I", record, 10)[0]
    data = read_sector(f, base_lba + lba, (size + SECTOR - 1) // SECTOR)
    pos = 0
    while pos < size:
        length = data[pos]
        if length == 0:  # no more records in this sector
            pos = (pos // SECTOR + 1) * SECTOR
            continue
        rec = data[pos:pos + length]
        name_len = rec[32]
        name = rec[33:33 + name_len]
        flags = rec[25]
        if name not in (b"\x00", b"\x01"):
            name = name.decode("ascii", "replace").split(";")[0]
            e_lba = struct.unpack_from("<I", rec, 2)[0]
            e_size = struct.unpack_from("<I", rec, 10)[0]
            full = f"{path}/{name}"
            if flags & 2:
                yield from walk(f, base_lba, rec, full)
            else:
                yield full, base_lba + e_lba, e_size
        pos += length


def list_image(path):
    total_sectors = os.path.getsize(path) // SECTOR
    layers = []
    with open(path, "rb") as f:
        pvd0 = parse_pvd(f, 0)
        if not pvd0:
            raise SystemExit("No ISO9660 descriptor at sector 16")
        layers.append((0, pvd0))
        # PS2 DVD-9: layer 1 starts where the layer 0 volume ends, minus 16 sectors,
        # and its descriptor sits at (layer 1 start + 16).
        l1 = pvd0["volume_size"] - 16
        if l1 + 17 <= total_sectors:
            pvd1 = parse_pvd(f, l1)
            if pvd1:
                layers.append((l1, pvd1))
        files = []
        for base, pvd in layers:
            files.extend(walk(f, base, pvd["root"]))
    return total_sectors, layers, files


def read_file(image, wanted):
    """Return the bytes of a file of the image, found by its base name."""
    _, _, files = list_image(image)
    for name, lba, size in files:
        if os.path.basename(name).upper() == wanted.upper():
            with open(image, "rb") as f:
                f.seek(lba * SECTOR)
                return f.read(size)
    raise FileNotFoundError(wanted)


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    image = sys.argv[1]
    if "--extract" in sys.argv:
        i = sys.argv.index("--extract")
        wanted, out_dir = sys.argv[i + 1], sys.argv[i + 2]
        os.makedirs(out_dir, exist_ok=True)
        dest = os.path.join(out_dir, wanted.upper())
        data = read_file(image, wanted)
        with open(dest, "wb") as out:
            out.write(data)
        print(f"Extracted: {dest} ({len(data)} bytes)")
        return

    total, layers, files = list_image(image)
    print(f"Image: {total} sectors ({total * SECTOR} bytes)")
    for base, pvd in layers:
        print(f"Layer starting at sector {base}: volume '{pvd['volume_id']}', "
              f"{pvd['volume_size']} sectors")
    print(f"\n{'LBA':>9} {'end':>9} {'size':>12}  name")
    for name, lba, size in sorted(files, key=lambda e: e[1]):
        end = lba + (size + SECTOR - 1) // SECTOR
        print(f"{lba:>9} {end:>9} {size:>12}  {name}")
    used_end = max(lba + (size + SECTOR - 1) // SECTOR for _, lba, size in files)
    print(f"\nLast sector used by a file: {used_end} / {total}")


if __name__ == "__main__":
    main()
