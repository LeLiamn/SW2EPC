"""Group a source file's scalar globals that live outside the small-data area into structs.

CodeWarrior reaches small globals (8 bytes or less) through $gp, and larger objects through lui /
%lo. The game reaches only the variables of its small-data area (around gp = 0x00464BF0) through
$gp; every other scalar was part of something larger in the original source. To reproduce that,
the scalar `extern` declarations outside the small-data area are replaced by structs covering
their address ranges, and each old name becomes a macro naming its field, so the code using them
does not change.

Usage: py tools/group_globals.py src/file.c [--write]
"""
import re
import sys

GP = 0x00464BF0
SDATA = (GP - 0x8000, GP + 0x8000)
SIZES = {"u8": 1, "char": 1, "signed char": 1, "unsigned char": 1, "unsigned short": 2, "short": 2,
         "int": 4, "u32": 4, "unsigned int": 4, "float": 4}
GAP = 0x400            # a larger hole starts a new struct
DECL = re.compile(r"^extern ((?:const )?[A-Za-z_][A-Za-z0-9_ ]*?)\s+(\*?\s*g_[0-9A-F]{8}(?:\s*,\s*\*?\s*g_[0-9A-F]{8})*);(.*)$")


def size_of(typ, ptr):
    if ptr or "*" in typ:
        return 4
    return SIZES.get(typ.replace("const ", "").strip())


def main():
    path = sys.argv[1]
    lines = open(path, encoding="utf-8").read().split("\n")
    found = []                                  # (addr, size, field decl, line index)
    keep = set()
    for i, line in enumerate(lines):
        m = DECL.match(line)
        if not m:
            continue
        typ, names, comment = m.group(1).strip(), m.group(2), m.group(3)
        if "/*" in comment and "*/" not in comment:
            sys.exit(f"line {i + 1}: put the comment of this declaration on one line first")
        items = [n.strip() for n in names.split(",")]
        ok = []
        for n in items:
            ptr = n.startswith("*")
            name = n.lstrip("* ").strip()
            addr = int(name[2:], 16)
            size = size_of(typ, ptr)
            if size is None or SDATA[0] <= addr < SDATA[1] or addr % size:
                keep.add(i)
                continue
            ok.append((addr, size, f"{typ} {'*' if ptr else ''}{name};{comment if len(items) == 1 else ''}"))
        if ok and len(ok) == len(items):
            found.extend((a, s, d, i) for a, s, d in ok)
        elif ok:
            keep.add(i)
    if not found:
        print("nothing to group")
        return
    found.sort()
    groups, cur = [], [found[0]]
    for f in found[1:]:
        prev = cur[-1]
        if f[0] < prev[0] + prev[1]:
            sys.exit(f"overlap at 0x{f[0]:08X}")
        if f[0] - (prev[0] + prev[1]) > GAP:
            groups.append(cur)
            cur = []
        cur.append(f)
    groups.append(cur)

    out = []
    for g in groups:
        base = g[0][0]
        body, pos, pad = [], base, 0
        for addr, size, decl, _ in g:
            if addr > pos:
                body.append(f"    char pad_{pad}[0x{addr - pos:X}];")
                pad += 1
            body.append("    " + decl.strip())
            pos = addr + size
        if pos - base <= 8:                     # still small: the compiler would use $gp
            body.append(f"    char size_unknown[{9 - (pos - base)}];   /* the whole object is larger */")
        sname = f"s_{base:08X}"
        out.append(f"/* Globals 0x{base:08X}-0x{pos:08X}: one object in the original (not reached through $gp). */")
        out.append("extern struct {")
        out.extend(body)
        out.append(f"}} {sname};")
        for addr, size, decl, _ in g:
            name = re.search(r"g_[0-9A-F]{8}", decl).group(0)
            out.append(f"#define {name} ({sname}.{name})")
        out.append("")
    used = {i for _, _, _, i in found} - keep
    first = min(used)
    new = []
    for i, line in enumerate(lines):
        if i == first:
            new.extend(out)
        if i in used:
            continue
        new.append(line)
    text = "\n".join(new)
    if "--write" in sys.argv:
        open(path, "w", encoding="utf-8", newline="\n").write(text)
    print("\n".join(out))


if __name__ == "__main__":
    main()
