# Matching functions

A function is **matching** when its C in `src/` compiles to exactly the bytes of the original
executable (relocated fields aside). Its tag then says so:

```c
/* 0x001E3D50, 0x1C bytes, matching. ... */
```

`tools/progress.py` counts tagged functions as matching instead of non-matching.

## Compiler and settings

The game was built with Metrowerks CodeWarrior for PlayStation 2 (the executable names its back end
`MW MIPS C Compiler 2.4.1.01`, shared by several releases). Functions are verified with
CodeWarrior for PS2 **3.0.1 build 210 (2006-03-08)**; builds 198 and 205 give the same results,
older ones fewer matches (the 2.4 release saves `$ra` with 128-bit `sq`, the game with 64-bit `sd`).
Settings:

- `-O4` (`-O3` gives the same results so far);
- `#pragma tailcall off` (the game never turns a final call into a jump);
- `#pragma no_branch_likely on` (the game never uses branch-likely instructions; this pragma
  exists from build 198 on);
- default small-data settings (small globals through `$gp`, as in the game).

Using CodeWarrior for PS2 is done with the rights holder's written permission, for this
non-commercial project; the compiler is not distributed with the project.

## On decomp.me

The same compilers are available on decomp.me (platform PlayStation 2, preset
`mwcps2-3.0.1b210-060308`), which anyone can use to check or improve a function by hand:

```
py tools/decompme.py path/SLES_546.24 ADDR [ADDR ...]
```

writes `build/decompme/<ADDR>/` (git-ignored: the assembly comes from the game's executable):

| File | Paste into |
|---|---|
| `target.s` | "Target assembly" when creating the scratch |
| `context.h` | the scratch's "Context" tab |
| `code.c` | the scratch's "Source" tab, with `#pragma tailcall off` and `#pragma no_branch_likely on` at the top |

Scratches are public on decomp.me.

## Status

30 functions match (1,352 bytes), all as first written: small call wrappers, struct copies, the
scene step functions, the shop helpers and the Treasures mode handlers (see the `, matching` tags
in `src/`). The other functions are equivalent C that still needs reshaping (register use,
statement order, local variables) to match.
