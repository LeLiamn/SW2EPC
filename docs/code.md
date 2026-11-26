# The code

Notes on the code of `SLES_546.24`, function by function. Decompiled C goes in `src/`. Addresses are
virtual addresses (the executable loads at `0x00100000`).

Tools so far: `tools/mips_disasm.py` (minimal R5900 disassembler). Ghidra will take over for larger
work.

## Start-up (crt0, Metrowerks runtime)

The entry point `0x00100008` is the runtime start-up code, not game code:

1. Clears the 128-bit registers (R5900 MMI instructions) and the FPU registers.
2. Clears the BSS: bytes from `0x0045D180` up to a 16-byte boundary, then 16-byte stores (`sq`) up to
   `0x007C0000`, then the remaining bytes.
3. `gp = 0x00464BF0`, then kernel syscall `0x3C` (SetupThread: stack, heap) and syscall `0x3D`
   (SetupHeap, from `0x007C0000`).
4. Calls `0x00132158` and `0x00128060` (runtime and library initialisation).
5. Loads argc/argv from `0x0056CB00`, calls **`main` at `0x00102A20`**, then `exit` (`0x0011CD38`)
   with main's return value.

## Functions

| Address | Size | Name | Status | Notes |
|---|---:|---|---|---|
| `0x00102A20` | 0x58 | `main` | Decompiled, not compiler-verified (`src/main.c`) | Set-up, main loop, shutdown |
| `0x00117E50` | | `func_00117E50` | Unknown | First call of main: system set-up? |
| `0x00106750` | | `func_00106750` | Unknown | Game set-up? |
| `0x001005A0` | | `func_001005A0` | Unknown | Loop condition: non-zero leaves the main loop |
| `0x00106810` | | `func_00106810` | Unknown | Called once per loop: one frame? |
| `0x001067D0` | | `func_001067D0` | Unknown | Game shutdown? |
| `0x00117E90` | | `func_00117E90` | Unknown | System shutdown? |

Question marks are hypotheses from the structure of `main` only.

## Other finds

- The strings next to the LINKDATA paths include `cdrom0:LINKDATA.DNS;1`: a fourth container that is
  not on the disc (a leftover?), and `file.c`, the source file of the file-loading code.
