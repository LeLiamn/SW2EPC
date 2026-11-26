# Matching functions on decomp.me

The project is non-matching (see the roadmap): the game was built with CodeWarrior for PS2
(`MW MIPS C Compiler 2.4.1.01`), which cannot run locally. decomp.me runs CodeWarrior compilers on its
server, so a few functions can still be proven byte-identical there, by hand, in the browser.

## Preparing scratches

```
py tools/decompme.py path/SLES_546.24 ADDR [ADDR ...]
```

For each function already decompiled in `src/`, this writes `build/decompme/<ADDR>/` (git-ignored:
the assembly comes from the game's executable):

| File | Paste into |
|---|---|
| `target.s` | "Target assembly" when creating the scratch |
| `context.h` | the scratch's "Context" tab |
| `code.c` | the scratch's "Source" tab |

`build/decompme/README.txt` lists the functions and their sizes.

## On decomp.me

1. New scratch, platform **PlayStation 2**, a **MWCC** compiler (CodeWarrior). Several versions
   exist; the game's is 2.4.1.01, so try the MWCC presets one after the other and keep the one whose
   prologue (`addiu $sp`, `sd $ra`) and delay-slot use look like the target.
2. Paste `target.s`, then `context.h` and `code.c`.
3. Compare. Usual differences and what to try:
   - globals read through `$gp` instead of `lui`/`%lo` (or the reverse): change the small-data
     threshold flag;
   - instructions in a different order: optimisation level, or reorder the C statements;
   - a different register: declare locals in another order or write the expression differently.
4. At 100 %, save the scratch and note its link.

Scratches are public on decomp.me.

## Recording a match

Add `, matching` after the size in the function's tag, then the scratch link:

```c
/* 0x001E86A0, 0x2C bytes, matching: https://decomp.me/scratch/XXXXX. Mode 4: ... */
```

Change the C in `src/` to exactly what matched on decomp.me. `tools/progress.py` then counts the
function as matching instead of non-matching.

## First batch

11 small functions, 408 bytes (about 0.013 % of the code):
`0x001E86A0`, `0x001E8A20`, `0x001E8A50`, `0x001E8A80` (call, test, call),
`0x001E3D50`, `0x001E3D70`, `0x001E3D90`, `0x00117E90` (single call),
`0x001E9140` (empty), `0x001E3CD0` (struct writes and a call), `0x001E4030` (global copies).
