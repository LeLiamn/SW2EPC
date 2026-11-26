# Matching functions

A function is **matching** when its C in `src/` compiles to exactly the bytes of the original
executable (relocated fields aside). Its tag then says so:

```c
/* 0x001E3D50, 0x1C bytes, matching. ... */
```

`tools/progress.py` counts tagged functions as matching instead of non-matching.

## Compiler and settings

The game was built with Metrowerks CodeWarrior for PlayStation 2 (the executable names its back end
`MW MIPS C Compiler 2.4.1.01`). Functions are verified with CodeWarrior for PS2 **3.0 (build of
2001-11-26)**, which reproduces the game's code where the 2.4 release does not (2.4 saves `$ra`
with 128-bit `sq`, the game with 64-bit `sd`). Settings:

- `-O4` (`-O3` gives the same results so far);
- `#pragma tailcall off` (the game never turns a final call into a jump);
- default small-data settings (small globals through `$gp`, as in the game).

Later 3.0.x builds (2003-2006) have not been compared yet; one of them may be the exact build used.
Using CodeWarrior for PS2 is done with the rights holder's written permission, for this
non-commercial project; the compiler is not distributed with the project.

## On decomp.me

The same compilers are available on decomp.me (platform PlayStation 2, preset
`mwcps2-3.0-011126`), which anyone can use to check or improve a function by hand:

```
py tools/decompme.py path/SLES_546.24 ADDR [ADDR ...]
```

writes `build/decompme/<ADDR>/` (git-ignored: the assembly comes from the game's executable):

| File | Paste into |
|---|---|
| `target.s` | "Target assembly" when creating the scratch |
| `context.h` | the scratch's "Context" tab |
| `code.c` | the scratch's "Source" tab (add `#pragma tailcall off` at the top) |

Scratches are public on decomp.me.

## Status

18 functions match (496 bytes): `0x001014D0`, `0x00106810`, `0x001067D0`, `0x00117E90`,
`0x001E3CD0`, `0x001E3D50`, `0x001E3D70`, `0x001E3D90`, `0x001E6BB0`, `0x001E9140`,
`0x0029FB70`, `0x0029FD70`, `0x0029FD90`, `0x002A01A0`, `0x002A1740`, `0x002A2AE0`, `0x002A45E0`,
`0x002A4940`. They matched as first written: the other functions are equivalent C that still
needs reshaping (register use, statement order, local variables) to match.
