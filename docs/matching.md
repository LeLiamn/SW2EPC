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

- `-O4,p` (level 4, optimised for speed: divisions by a constant become multiplications);
- `#pragma tailcall off` (the game never turns a final call into a jump);
- `#pragma no_branch_likely on` (the game never uses branch-likely instructions; this pragma
  exists from build 198 on);
- `#pragma opt_unroll_loops off` (the game's loops are never unrolled, although `-O4,p` would);
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
| `code.c` | the scratch's "Source" tab, with `#pragma tailcall off`, `#pragma no_branch_likely on` and `#pragma opt_unroll_loops off` at the top |

Scratches are public on decomp.me.

## How the source has to be written

What makes the compiler produce the game's exact code, learnt so far:

- **Globals outside the small-data area are parts of larger objects.** CodeWarrior reaches any
  global of 8 bytes or less through `$gp`, but the game does so only for its small-data area
  (around `gp = 0x00464BF0`). `tools/group_globals.py` turns the scalar `extern`s of a file into
  structs covering their address ranges (old names kept as macros), padded beyond 8 bytes when
  only a small part of the object is known. When the real start of an
  object is known, model it from there: the system settings start at `0x00669D60`, and the code
  adds `+0x2C` to reach the pads' settings.
- **Flag bytes are bitfields** (first field = lowest bit): the game extracts them with
  `dsll32` / `dsrl32` pairs.
- **`if` / `else` statements, not `?:`**, where the game branches (and the branch order follows the
  condition as written: `if (flag == 0) a; else b;` and `if (flag) b; else a;` differ).
- **Locals change the order of loads and stores**: copying two fields through locals first
  gives "load, load, store, store".
- A symbol, not an integer cast, where the game builds an address with `lui` / `addiu`.
- Four different symbols when the same address is loaded four times.
- **Switch cases in the game's order** (read it from the jump table), empty cases written out
  when the table has them, and clamps written as `?:` (`x = v < lo ? lo : v`).
- **MIN / MAX macros** `MAX(a, b) ((a) > (b) ? (a) : (b))`, `MIN(a, b) ((a) > (b) ? (b) : (a))`;
  the game's random generator is an inlined macro, not a function.
- **A pointer to a struct member stays in a register** (`lui s0; addiu s0, +off`), where a pointer
  to a whole object is folded into each access: the options menu's state at `0x00731140` is one
  object whose members are the settings copies.
- **Controller values are `int` locals holding a 16-bit value**: `int pressed = (u16)(...)`. With
  `unsigned short` locals, the compiler re-extends them before each first use.
- **The shop's state is one object** (`0x00772DF0`-`0x007731A4`: skill, mount and hire offers,
  then the shop's variables): stores to an offer must be assumed to change the counts, and the code
  reaches the offers as `base + 0x280`.
- **Small helpers used only inside their file are `static`**: the compiler then knows which
  registers they leave alone, and keeps values in argument registers across the call.
- **Declaration order picks the registers**: when only the `s` registers differ, reorder the locals.
- **Several `return` statements**: a branch that ends with its own `return 0` gives a separate
  `v0 = 0` before the jump to the epilogue.
- **Inlined helpers have one buffer per function**: the message helper's 256-byte text buffer is
  a local of each caller, and a message without a name calls the formatter with two arguments.
- **The message boxes are indexed from their object's base** (`0x0068F3E0`), with the box offset in
  the load (`lbu 0x40D4(base + box * 0x128)`).
- **After reading the controller, the code uses the port number**, not the player argument.
- **A count used twice around a random draw is read into a local**:
  `int n = count; r = n != 0 ? random16() % n : 0;`.

## Status

**StateTreasures.c is fully matching** (all 24 functions of `src/scene_treasures.c`), and so is
`src/main.c` (start-up and the scene manager).

95 functions match (32 of the 42 functions of `src/scene_shop.c`, 24 of the 33 of `src/scene_config.c`, 6 of the 8 of `src/scene_setup_emp_mogi.c`). The other functions are equivalent C that
still needs reshaping.
