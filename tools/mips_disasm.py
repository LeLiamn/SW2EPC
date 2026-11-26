"""Minimal MIPS (R5900 subset) disassembler for quick looks at SCES_538.51.

Covers the common integer instructions, which is enough to follow most game code.
For real work use Ghidra; this is for quick checks without leaving the terminal.

Usage:
  py tools/mips_disasm.py path/SCES_538.51 START_ADDR [COUNT]
  py tools/mips_disasm.py path/SCES_538.51 --refs ADDR     find lui/addiu pairs building ADDR
"""
import struct
import sys

REGS = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5",
        "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1",
        "gp", "sp", "fp", "ra"]

SPECIAL = {0x00: "sll", 0x02: "srl", 0x03: "sra", 0x04: "sllv", 0x06: "srlv", 0x07: "srav",
           0x08: "jr", 0x09: "jalr", 0x0A: "movz", 0x0B: "movn", 0x0C: "syscall", 0x0D: "break",
           0x0F: "sync", 0x10: "mfhi", 0x11: "mthi", 0x12: "mflo", 0x13: "mtlo", 0x14: "dsllv",
           0x16: "dsrlv", 0x17: "dsrav", 0x18: "mult", 0x19: "multu", 0x1A: "div", 0x1B: "divu",
           0x20: "add", 0x21: "addu", 0x22: "sub", 0x23: "subu", 0x24: "and", 0x25: "or",
           0x26: "xor", 0x27: "nor", 0x2A: "slt", 0x2B: "sltu", 0x2D: "daddu", 0x2F: "dsubu",
           0x38: "dsll", 0x3A: "dsrl", 0x3B: "dsra", 0x3C: "dsll32", 0x3E: "dsrl32", 0x3F: "dsra32"}
IMM = {0x08: "addi", 0x09: "addiu", 0x0A: "slti", 0x0B: "sltiu", 0x0C: "andi", 0x0D: "ori",
       0x0E: "xori", 0x19: "daddiu"}
MEM = {0x1A: "ldl", 0x1B: "ldr", 0x1E: "lq", 0x1F: "sq", 0x20: "lb", 0x21: "lh", 0x22: "lwl",
       0x23: "lw", 0x24: "lbu", 0x25: "lhu", 0x26: "lwr", 0x27: "lwu", 0x28: "sb", 0x29: "sh",
       0x2A: "swl", 0x2B: "sw", 0x2C: "sdl", 0x2D: "sdr", 0x2E: "swr", 0x31: "lwc1", 0x37: "ld",
       0x39: "swc1", 0x3F: "sd"}
BRANCH2 = {0x04: "beq", 0x05: "bne", 0x14: "beql", 0x15: "bnel"}
BRANCH1 = {0x06: "blez", 0x07: "bgtz", 0x16: "blezl", 0x17: "bgtzl"}
REGIMM = {0x00: "bltz", 0x01: "bgez", 0x02: "bltzl", 0x03: "bgezl", 0x10: "bltzal", 0x11: "bgezal"}


def s16(x):
    return x - 0x10000 if x & 0x8000 else x


def disasm(word, pc):
    op = word >> 26
    rs, rt, rd = (word >> 21) & 31, (word >> 16) & 31, (word >> 11) & 31
    sa, fn, imm = (word >> 6) & 31, word & 63, word & 0xFFFF
    target = pc + 4 + (s16(imm) << 2)
    if word == 0:
        return "nop"
    if op == 0:
        name = SPECIAL.get(fn, f"special.{fn:#x}")
        if fn in (0x00, 0x02, 0x03, 0x38, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F):
            return f"{name} {REGS[rd]}, {REGS[rt]}, {sa}"
        if fn in (0x04, 0x06, 0x07, 0x14, 0x16, 0x17):
            return f"{name} {REGS[rd]}, {REGS[rt]}, {REGS[rs]}"
        if fn == 0x08:
            return f"jr {REGS[rs]}"
        if fn == 0x09:
            return f"jalr {REGS[rd]}, {REGS[rs]}"
        if fn in (0x10, 0x12):
            return f"{name} {REGS[rd]}"
        if fn in (0x11, 0x13):
            return f"{name} {REGS[rs]}"
        if fn in (0x18, 0x19, 0x1A, 0x1B):
            return f"{name} {REGS[rd]}, {REGS[rs]}, {REGS[rt]}" if rd else f"{name} {REGS[rs]}, {REGS[rt]}"
        if fn in (0x0C, 0x0D, 0x0F):
            return name
        return f"{name} {REGS[rd]}, {REGS[rs]}, {REGS[rt]}"
    if op == 1:
        return f"{REGIMM.get(rt, f'regimm.{rt:#x}')} {REGS[rs]}, 0x{target:08x}"
    if op in (2, 3):
        return f"{'j' if op == 2 else 'jal'} 0x{((pc + 4) & 0xF0000000) | ((word & 0x3FFFFFF) << 2):08x}"
    if op in BRANCH2:
        return f"{BRANCH2[op]} {REGS[rs]}, {REGS[rt]}, 0x{target:08x}"
    if op in BRANCH1:
        return f"{BRANCH1[op]} {REGS[rs]}, 0x{target:08x}"
    if op in IMM:
        val = imm if op in (0x0C, 0x0D, 0x0E) else s16(imm)
        return f"{IMM[op]} {REGS[rt]}, {REGS[rs]}, {val:#x}" if val >= 0 else \
            f"{IMM[op]} {REGS[rt]}, {REGS[rs]}, -{-val:#x}"
    if op == 0x0F:
        return f"lui {REGS[rt]}, {imm:#x}"
    if op in MEM:
        r = f"$f{rt}" if op in (0x31, 0x39) else REGS[rt]
        return f"{MEM[op]} {r}, {s16(imm)}({REGS[rs]})"
    return f".word 0x{word:08x}"


def load(path):
    data = open(path, "rb").read()
    phoff = struct.unpack_from("<I", data, 28)[0]
    _, offset, vaddr, _, filesz = struct.unpack_from("<5I", data, phoff)
    return data, offset, vaddr, filesz


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    data, offset, vaddr, filesz = load(sys.argv[1])
    if sys.argv[2] == "--refs":
        want = int(sys.argv[3], 16)
        lo = want & 0xFFFF
        for off in range(offset, offset + filesz - 4, 4):
            w = struct.unpack_from("<I", data, off)[0]
            if (w & 0xFFFF) == lo and (w >> 26) in (0x09, 0x0D, 0x23, 0x2B, 0x20, 0x24, 0x31):
                print(f"0x{off - offset + vaddr:08x}  {disasm(w, off - offset + vaddr)}")
        return
    start = int(sys.argv[2], 16)
    count = int(sys.argv[3]) if len(sys.argv) > 3 else 64
    for i in range(count):
        pc = start + 4 * i
        w = struct.unpack_from("<I", data, pc - vaddr + offset)[0]
        print(f"0x{pc:08x}  {w:08x}  {disasm(w, pc)}")


if __name__ == "__main__":
    main()
