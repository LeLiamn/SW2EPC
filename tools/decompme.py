"""Prepare decomp.me scratches for functions already decompiled in src/.

For each function this writes, under build/decompme/<address>/ (git-ignored: the assembly comes
from the game's executable and stays on your machine):
- target.s   the original function's assembly in decomp.me's format (GNU as syntax, symbols for
             calls, %hi/%lo and %gp_rel for globals, local labels for branches);
- code.c     the function's C from src/ (what to paste in the "Source" box);
- context.h  the declarations it uses (what to paste in the "Context" box).
It also writes build/decompme/README.txt listing them all.

Usage:
  py tools/decompme.py path/SLES_546.24 ADDR [ADDR ...]
"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mips_disasm import (BRANCH1, BRANCH2, IMM, MEM, REGIMM, REGS, disasm, load, s16)  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "src")
OUT = os.path.join(ROOT, "build", "decompme")
GP = 0x00464BF0
TAG = re.compile(r"/\* 0x([0-9A-Fa-f]{8}), (0x[0-9A-Fa-f]+|\d+) bytes")


def find_function(addr):
    """(file text, C text of the function, size) for the function tagged with `addr` in src/."""
    for name in sorted(os.listdir(SRC)):
        if not name.endswith(".c"):
            continue
        text = open(os.path.join(SRC, name), encoding="utf-8").read()
        for m in TAG.finditer(text):
            if int(m.group(1), 16) == addr:
                start = text.rfind("\n", 0, m.start()) + 1
                body = re.search(r"\n\{.*?\n\}\n", text[m.end():], re.S)
                return text, text[start:m.end() + body.end()], int(m.group(2), 0)
    raise SystemExit(f"0x{addr:08X} is not tagged in src/")


def r(n):
    return "$" + REGS[n]


def to_gas(data, offset, vaddr, addr, size):
    """The function's instructions in GNU as syntax, with symbols instead of addresses."""
    words = [struct.unpack_from("<I", data, a - vaddr + offset)[0] for a in range(addr, addr + size, 4)]
    labels = set()
    for i, w in enumerate(words):
        op = w >> 26
        if op in BRANCH2 or op in BRANCH1 or op == 1:
            labels.add(addr + 4 * i + 4 + (s16(w & 0xFFFF) << 2))
    hi = {}                                     # register -> upper half from a pending lui
    lines = [f"glabel func_{addr:08X}"]
    for i, w in enumerate(words):
        pc = addr + 4 * i
        if pc in labels:
            lines.append(f".L{pc:08X}:")
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        imm = w & 0xFFFF
        target = pc + 4 + (s16(imm) << 2)
        text = None
        if op == 3:
            text = f"jal func_{(w & 0x3FFFFFF) << 2:08X}"
        elif op == 2:
            text = f"j func_{(w & 0x3FFFFFF) << 2:08X}"
        elif op in BRANCH2:
            text = f"{BRANCH2[op]} {r(rs)}, {r(rt)}, .L{target:08X}"
        elif op in BRANCH1:
            text = f"{BRANCH1[op]} {r(rs)}, .L{target:08X}"
        elif op == 1:
            text = f"{REGIMM[rt]} {r(rs)}, .L{target:08X}"
        elif op == 0x0F:
            hi[rt] = imm
            text = f"lui {r(rt)}, 0x{imm:X}"     # rewritten below if a %lo follows
            lines.append(text)
            continue
        elif (op in MEM or op == 0x09) and (rs in hi or rs == 28):
            sym_addr = (hi[rs] << 16) + s16(imm) if rs != 28 else GP + s16(imm)
            sym = f"g_{sym_addr:08X}"
            if rs == 28:
                ref = f"%gp_rel({sym})"
            else:
                ref = f"%lo({sym})"
                for j in range(len(lines) - 1, -1, -1):          # give the lui its %hi
                    if lines[j].startswith(f"lui {r(rs)}, "):
                        lines[j] = f"lui {r(rs)}, %hi({sym})"
                        break
                hi.pop(rs)
            if op == 0x09:
                text = f"addiu {r(rt)}, {r(rs)}, {ref}"
            else:
                reg = f"$f{rt}" if op in (0x31, 0x39) else r(rt)
                text = f"{MEM[op]} {reg}, {ref}({r(rs)})"
        else:
            text = disasm(w, pc)
            text = re.sub(r"\b(" + "|".join(REGS) + r")\b", lambda m: "$" + m.group(1), text)
        # a register written by this instruction no longer holds a pending %hi
        dest = rt if op in IMM or op in MEM else ((w >> 11) & 31 if op == 0 else None)
        if dest in hi and not (op in MEM and op in (0x28, 0x29, 0x2B, 0x3F, 0x1F, 0x39)):
            hi.pop(dest)
        lines.append(text)
    return "\n".join(l if l.endswith(":") or l.startswith("glabel") else "    " + l for l in lines) + "\n"


def context(file_text, code):
    """Typedefs, defines, structs and the declarations of every name the function uses."""
    names = set(re.findall(r"\b(?:func|g)_[0-9A-Fa-f]{8}\b|\b[A-Z][A-Z0-9_]{2,}\b|\b\w+_t\b", code))
    names |= set(re.findall(r"\b(pad1_\w+|\w+_option|load_scene|main_menu_move)\b", code))
    out = [l for l in file_text.splitlines() if l.startswith("typedef unsigned")]
    for m in re.finditer(r"^typedef struct \{.*?^\} (\w+);", file_text, re.S | re.M):
        if m.group(1) in code:
            out.append(m.group(0))
    for line in file_text.splitlines():
        decl = re.match(r"^(#define \w+ |extern .*;|\w[\w ]*\**\s*\*?\w+\(.*\);)", line)
        if decl and any(re.search(rf"\b{n}\b", line) for n in names):
            if line not in out:
                out.append(line)
    for line in file_text.splitlines():        # functions defined in the file, without a prototype
        head = re.match(r"^(?!static)\w[\w ]*\**\s*\*?(func_[0-9A-Fa-f]{8})\(.*\)$", line)
        if head and head.group(1) in names and not any(head.group(1) + "(" in l for l in out):
            out.append(line + ";")
    return "\n".join(out) + "\n"


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    data, offset, vaddr, _ = load(sys.argv[1])
    os.makedirs(OUT, exist_ok=True)
    index, total = [], 0
    for a in sys.argv[2:]:
        addr = int(a, 16)
        file_text, code, size = find_function(addr)
        folder = os.path.join(OUT, f"{addr:08X}")
        os.makedirs(folder, exist_ok=True)
        open(os.path.join(folder, "target.s"), "w", newline="\n").write(to_gas(data, offset, vaddr, addr, size))
        open(os.path.join(folder, "code.c"), "w", encoding="utf-8", newline="\n").write(code.strip() + "\n")
        open(os.path.join(folder, "context.h"), "w", encoding="utf-8", newline="\n").write(context(file_text, code))
        index.append(f"func_{addr:08X}  {size:4d} bytes  {folder}")
        total += size
    index.append(f"{len(sys.argv) - 2} functions, {total} bytes")
    open(os.path.join(OUT, "README.txt"), "w", newline="\n").write("\n".join(index) + "\n")
    print("\n".join(index))


if __name__ == "__main__":
    main()
