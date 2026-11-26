"""Inspect a PS2 ELF executable (MIPS R5900): sections, symbols, debug info, compiler.

No external dependency (binutils not needed).

Usage:
  py tools/elf_info.py path/SCES_538.51               summary
  py tools/elf_info.py path/SCES_538.51 --symbols     list every symbol (CSV)
"""
import struct
import sys

SHT_NAMES = {0: "NULL", 1: "PROGBITS", 2: "SYMTAB", 3: "STRTAB", 4: "RELA", 8: "NOBITS",
             9: "REL", 0x70000005: "MIPS_DEBUG", 0x70000006: "MIPS_REGINFO"}
STT_NAMES = {0: "NOTYPE", 1: "OBJECT", 2: "FUNC", 3: "SECTION", 4: "FILE"}
STB_NAMES = {0: "LOCAL", 1: "GLOBAL", 2: "WEAK"}
JR_RA = struct.pack("<I", 0x03E00008)


def cstr(buf, off):
    end = buf.index(b"\0", off)
    return buf[off:end].decode("latin-1")


def parse(path_or_bytes):
    data = path_or_bytes if isinstance(path_or_bytes, bytes) else open(path_or_bytes, "rb").read()
    if data[:4] != b"\x7fELF":
        raise SystemExit("Not an ELF file")
    (e_type, e_machine, _, e_entry, e_phoff, e_shoff, e_flags, _, e_phentsize, e_phnum,
     e_shentsize, e_shnum, e_shstrndx) = struct.unpack_from("<HHIIIIIHHHHHH", data, 16)

    segments = []
    for i in range(e_phnum):
        p_type, p_offset, p_vaddr, _, p_filesz, p_memsz, p_flags, _ = struct.unpack_from(
            "<8I", data, e_phoff + i * e_phentsize)
        segments.append(dict(type=p_type, offset=p_offset, vaddr=p_vaddr, filesz=p_filesz,
                             memsz=p_memsz, flags=p_flags))

    sections = []
    for i in range(e_shnum):
        f = struct.unpack_from("<IIIIIIIIII", data, e_shoff + i * e_shentsize)
        sections.append(dict(name_off=f[0], type=f[1], flags=f[2], addr=f[3], offset=f[4],
                             size=f[5], link=f[6], info=f[7], align=f[8], entsize=f[9]))
    shstr = sections[e_shstrndx]
    for s in sections:
        s["name"] = cstr(data, shstr["offset"] + s["name_off"])

    symbols = []
    for s in sections:
        if s["type"] != 2:
            continue
        strtab = sections[s["link"]]
        for j in range(s["size"] // 16):
            name_off, value, size, info, other, shndx = struct.unpack_from(
                "<IIIBBH", data, s["offset"] + j * 16)
            symbols.append(dict(
                name=cstr(data, strtab["offset"] + name_off), value=value, size=size,
                type=STT_NAMES.get(info & 0xF, str(info & 0xF)),
                bind=STB_NAMES.get(info >> 4, str(info >> 4)), shndx=shndx))

    return dict(data=data, entry=e_entry, flags=e_flags, segments=segments,
                sections=sections, symbols=symbols)


def estimate_code(elf):
    """Estimate the code range of the first loaded segment.

    The executable has no named .text section, so the end of code is estimated as the
    last `jr $ra` (plus its delay slot). Code comes first in the segment, data after.
    Returns (start address, end address, number of `jr $ra`).
    """
    seg = next(s for s in elf["segments"] if s["type"] == 1 and s["filesz"])
    data = elf["data"]
    start, end = seg["offset"], seg["offset"] + seg["filesz"]
    last, count = None, 0
    for off in range(start, end - 3, 4):
        if data[off:off + 4] == JR_RA:
            last, count = off, count + 1
    code_end = last + 8 - start + seg["vaddr"]
    return seg["vaddr"], code_end, count


def compiler_strings(elf):
    found = []
    for s in elf["sections"]:
        if s["name"] == ".comment":
            raw = elf["data"][s["offset"]:s["offset"] + s["size"]]
            found += [x.decode("latin-1") for x in raw.split(b"\0") if x]
    return found


def summary(elf):
    print(f"Entry point: 0x{elf['entry']:08x}   e_flags: 0x{elf['flags']:08x}")
    print("\nSegments:")
    for s in elf["segments"]:
        print(f"  type {s['type']} vaddr 0x{s['vaddr']:08x} filesz 0x{s['filesz']:x} "
              f"memsz 0x{s['memsz']:x}")
    print("\nSections:")
    print(f"  {'name':<20} {'type':<13} {'address':>10} {'size':>10}")
    for s in elf["sections"]:
        t = SHT_NAMES.get(s["type"], hex(s["type"]))
        print(f"  {s['name']:<20} {t:<13} 0x{s['addr']:08x} {s['size']:>10}")

    syms = elf["symbols"]
    by_type = {}
    for s in syms:
        by_type[s["type"]] = by_type.get(s["type"], 0) + 1
    print(f"\nSymbols: {len(syms)} total", by_type)
    files = sorted({s["name"] for s in syms if s["type"] == "FILE"})
    print(f"Source files named (STT_FILE): {len(files)}")
    for f in files[:40]:
        print("   ", f)

    has_mdebug = any(s["name"] == ".mdebug" or s["type"] == 0x70000005 for s in elf["sections"])
    has_dwarf = any(s["name"].startswith(".debug") for s in elf["sections"])
    print(f"\nDebug info: .mdebug={'yes' if has_mdebug else 'no'}, "
          f"DWARF={'yes' if has_dwarf else 'no'}")
    for c in compiler_strings(elf):
        print(f".comment: {c!r}")

    start, end, count = estimate_code(elf)
    print(f"\nEstimated code: 0x{start:08x}-0x{end:08x} ({end - start} bytes), "
          f"{count} 'jr $ra' instructions")


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    elf = parse(sys.argv[1])
    if "--symbols" in sys.argv:
        print("address,size,type,binding,section,name")
        for s in sorted(elf["symbols"], key=lambda s: s["value"]):
            print(f"0x{s['value']:08x},{s['size']},{s['type']},{s['bind']},{s['shndx']},{s['name']}")
    else:
        summary(elf)


if __name__ == "__main__":
    main()
