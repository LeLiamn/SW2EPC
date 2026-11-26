# The code

Notes on the code of `SLES_546.24`, function by function. Decompiled C goes in `src/`. Addresses are
virtual addresses (the executable loads at `0x00100000`).

Tools: `tools/mips_disasm.py` (minimal R5900 disassembler) and **Ghidra 12.2 with the
[ghidra-emotionengine-reloaded](https://github.com/chaoticgd/ghidra-emotionengine-reloaded) extension**
(processor `r5900:LE:32:default`), run headless with `tools/ghidra_run.ps1` (needs JDK 25+). With the
R5900 processor Ghidra finds **10,583 functions** (9,820 with plain MIPS64), and its output for `main`
matches the hand decompilation in `src/main.c` call for call.

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

Decompiled functions live in `src/`, each tagged with its original address and size
(`/* 0x00106750, 0x80 bytes`); `tools/progress.py` adds those sizes up as "non-matching" code for
decompilati.onl (equivalent C, not verified by compiling).

| Address | Size | Name | Status | Notes |
|---|---:|---|---|---|
| `0x00102A20` | 0x58 | `main` | Decompiled (`src/main.c`) | System set-up, game set-up, main loop, shutdowns |
| `0x00117E50` | 0x38 | `func_00117E50` | Decompiled | System set-up: `func_00117F10(g_0045CB80 ×4)` |
| `0x00106750` | 0x80 | `func_00106750` | Decompiled | Game set-up: 10 init calls, writes 12345 to scratchpad `0x7000015C` (random seed?) |
| `0x001005A0` | 0x2C4 | `func_001005A0` | Decompiled | **Scene manager**: enters, updates, steps, draws and leaves the current scene through function pointers; handles reset requests; returns when the game quits |
| `0x00106810` | 0x24 | `func_00106810` | Decompiled | After each loop pass: sets the flag `g_0045D1C4` to 0 then 1 |
| `0x001014D0` | 0x08 | `func_001014D0` | Decompiled | Stores its argument in `g_0045D1C4` (gp − 0x7A2C) |
| `0x001067D0` | 0x3C | `func_001067D0` | Decompiled | Game shutdown: 3 calls, bracketed by the flag |
| `0x00117E90` | 0x1C | `func_00117E90` | Decompiled | System shutdown: calls `func_00117EB0` |

Correction (2026-11-26): an earlier version guessed that `func_001014D0` ran an update or draw phase.
It only stores a flag; the per-frame work is in `func_001005A0`.

## The scene manager (`0x0045D880`)

The whole game runs inside `func_001005A0`, which drives a block of globals at `0x0045D880` (see the
`SceneManager` structure in `src/main.c`): the current, requested and previous state numbers, and
function pointers for the current scene (enter, update, step, draw, leave, plus alternative enter
and leave functions and a reset hook). Each scene of the game (title, map, battle...?) installs its
own functions there. State 0x18 means "no change requested"; a reset request (`0x0045D20C` or
`0x0045D210`, set elsewhere: button combination?) sends the game to state 0x10.

Next: find who writes the function pointers, which maps state numbers to scenes and their
source files (`SceneTitle.c`, `StateConquest.c`, `StatePreBattle.c`...).

## Other finds

- The strings next to the LINKDATA paths include `cdrom0:LINKDATA.DNS;1`: a fourth container that is
  not on the disc (a leftover?), and `file.c`, the source file of the file-loading code.
