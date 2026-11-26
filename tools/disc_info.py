"""First look at a PS2 disc image: boot executable, region settings, files, executable summary.

Reads SYSTEM.CNF to find the boot executable (SLUS_xxx.xx, SLES_xxx.xx, SLPM_xxx.xx...), so it
works whatever the region of the disc.

Usage:
  py tools/disc_info.py image.iso                  summary
  py tools/disc_info.py image.iso --extract-exe    also copy the executable to extracted/
"""
import hashlib
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import elf_info  # noqa: E402
from iso_list import list_image, read_file  # noqa: E402


def system_cnf(image):
    text = read_file(image, "SYSTEM.CNF").decode("ascii", "replace")
    fields = dict(re.findall(r"^\s*(\w+)\s*=\s*(.+?)\s*$", text, re.M))
    boot = fields.get("BOOT2", "")
    exe = re.sub(r"^cdrom0:\\?", "", boot).split(";")[0].lstrip("\\")
    return fields, exe


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    image = sys.argv[1]
    total, layers, files = list_image(image)
    fields, exe = system_cnf(image)

    print(f"Image: {total} sectors, {len(layers)} layer(s), {len(files)} files")
    for key, value in fields.items():
        print(f"SYSTEM.CNF {key} = {value}")

    data = read_file(image, exe)
    print(f"\nExecutable: {exe} ({len(data)} bytes)")
    print(f"  MD5  : {hashlib.md5(data).hexdigest()}")
    print(f"  SHA-1: {hashlib.sha1(data).hexdigest()}")
    elf = elf_info.parse(data)
    print(f"  Symbols: {len(elf['symbols'])}, sections: "
          f"{', '.join(s['name'] or '(unnamed)' for s in elf['sections'][1:])}")
    for c in elf_info.compiler_strings(elf):
        print(f"  .comment: {c!r}")
    start, end, count = elf_info.estimate_code(elf)
    print(f"  Estimated code: 0x{start:08x}-0x{end:08x} ({end - start} bytes, {count} 'jr $ra')")

    print("\nLargest files:")
    for name, _, size in sorted(files, key=lambda f: -f[2])[:15]:
        print(f"  {size:>12}  {name}")

    if "--extract-exe" in sys.argv:
        out = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "extracted")
        os.makedirs(out, exist_ok=True)
        with open(os.path.join(out, exe), "wb") as f:
            f.write(data)
        print(f"\nExecutable copied to {os.path.join(out, exe)}")


if __name__ == "__main__":
    main()
