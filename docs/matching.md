# Matching functions

A function is **matching** when its C in `src/` compiles to exactly the bytes of the original
executable (relocated fields aside). Its tag then says so:

```c
/* 0x001E3D50, 0x1C bytes, matching. ... */
```

`tools/progress.py` counts tagged functions as matching instead of non-matching. The size in a
tag ends at the function's last instruction. The report adds the alignment padding after it:
`nop` words, up to the next 16-byte boundary. That padding is not code, and no tag could cover it
otherwise. The start-up code at `0x00100008` is assembly, so it is never counted.

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
- **After reading the controller, the code uses the port number**, not the player argument,
  except where the argument register is never reloaded: `func_002A2110(player)` is called with
  `a0` still holding the argument (a call with no `a0` set-up passes the function's own argument).
- **A count used twice around a random draw is read into a local**:
  `int n = count; r = n != 0 ? random16() % n : 0;`.
- **List cursors read the count into an `int` local for the tests only**: the moves re-read the
  global (`(cursor + g_count - 1) % g_count`); `if (n <= 1) return;` before them, `cursor > 0` (not
  `!= 0`) for "not at the top".
- **Clamps against a count are `x > n - 1 ? n - 1 : x`**, stored even when nothing changes.
- **Branch order**: write the test the way the game branches (`if (mode >= 5) ... else ...`,
  `if (flag != 0) a else b`, `if (count <= 0)` where the game uses `bgtz`); byte counts compare as
  `> 1`, not `>= 2`.
- **An address inside the shop object is base plus offsets** (`g_00772DF0 + player * 0x140 +
  slot * 0x50`), in that order, not an array index.
- **Keep the slot of modes 5-8 as a small `switch`** (`case 5: slot = 0` ...): the game tests
  `mode == 8, 7, 6, 5`, and leaves the slot unset for other modes.
- **Small page objects are reached through a pointer**: when the game computes an object's
  address once and stores at offsets from it, write `u8 *page = (u8 *)&s_00749B9E; page[1] = 0;`
  (separate objects, not one big struct: check what the code clears with one memset).
- **Parameter types show in the narrowing**: an `andi 0xFF` before a call means the caller had an
  `int` and the callee takes a `u8` (and a function returning `u8` from an `int` result masks it).
- **Scratchpad words are constant addresses** (`#define g_70000154 (*(int *)0x70000154)`): an
  `extern int` goes to the small-data area and is read through `$gp`.
- **Check struct layouts**: `py tools/check_layout.py` checks that every `g_XXXXXXXX` field of a
  one-object struct sits at its address (relocations are masked by the matching check, so a wrong
  padding can stay invisible; the shop state had 4 bytes too many after `0x00773170`).

- **Flag bits are signed one-bit fields**: a test compiled as `lb` + `dsll32` + `dsra32` is a
  `signed char x : 1` bitfield (LSB first), not `& mask`; the unit files use a `Bits8` struct and
  a `BIT(o, off, n)` macro for them, for tests and for single-bit writes; `model.c` gives the
  actor's flag byte a `Bits8` member, and the scene files use `SBIT` / `UBIT` (signed or
  unsigned, by `lb` or `lbu`) on their flag bytes.
- **Officers are reached through the game state**: the code addresses officer `i` as
  `0x00693970 + i * 0xC0 + 0x100C0 + field` (a `lui 1` plus the field offset), not from the
  table's own address `0x006A3A30`.
- **`p != 0 ? x : 0`, not `p == 0 ? 0 : x`**: the branch order follows the written order.
- **Weapon.c was built with the loop unroller on** (`#pragma opt_unroll_loops on` in
  `src/weapon.c`).

- **Unit loops walk a struct pointer**: when the game reloads a unit's flag byte from the unit
  each time instead of keeping its address, the loop variable is a pointer to a struct with the
  flags as a member (`UnitFlags *` in `src/battle_units.c`), not a `u8 *`.

- **Members of a big object keep their offset in the instruction**: when the game writes
  `sw x, 0x1BD0(v1)` after adding the index to the object's address, write the access as
  object + index + offset (`*(int *)((u8 *)&obj + i * 4 + 0x1BD0)`), not as an array member.

- **Single-bit writes are bitfield assignments** (`((struct { u8 a : 6; u8 b : 1; } *)p)->b = 1`),
  and unsigned bitfield tests compile to `dsll32` + `dsrl32`.
- **Write pointer walks step by step** when the game stores as it goes (`out[0] = c; c += 0x14;
  out[1] = c; ...`), not as independent expressions.

- **A base kept in a register means a byte pointer** (StateStartUp.c): when the game loads a
  fixed address once (`lui s0` + `addiu s0`) and reaches every field from it, write a local
  `u8 *st = &first_field;` and the fields as offsets from it (`ST_AT(st, off, i)`). A pointer of
  the struct's own type to the known address is folded back into constants by the compiler.
- **Booleans that end up in a register come from inlined functions**: a test compiled as
  "set 0 / set 1, then branch on the value" (`slti v1` / `xori` and a `beq v0, zero`) is a small
  inline function or a variable (`int ok = a && b; if (ok)`), not an `if` on the expression.
- **One `return` per branch** when the game computes the return value at the end of each branch
  and jumps to a shared `jr ra`.
- **Check the size tag** when ours has an epilogue the original lacks: the function may go on past
  the tagged size (0x366030 was 0xF0 bytes, not 0xE0).
- **A loop the game unrolls by 4 or 5 needs the unroller for that function**: wrap the function
  with `#pragma opt_unroll_loops on` / `off` (outside the function body).

## Status

**StateTreasures.c is fully matching** (all 24 functions of `src/scene_treasures.c`), and so is
`src/main.c` (start-up and the scene manager).

1745 functions match (37 of the 42 functions of `src/scene_shop.c`, 24 of the 33 of `src/scene_config.c`, 6 of the 8 of `src/scene_setup_emp_mogi.c`, 3 of the 37 of `src/scene_post_battle.c`, 18 of 23 in `src/scene_initialize.c`, 8 of 25 in `src/scene_demo.c`, 9 of 10 in `src/scene_empty.c`, 14 of 18 in `src/scene_loading.c`, 30 of 67 in `src/scene_battle_initialize.c`, 9 of 15 in `src/scene_conquest.c`, 26 of 82 in `src/scene_pre_battle.c`, 37 of 117 in `src/scene_edit.c`, 26 of 55 in `src/scene_start_up.c`, 28 of 51 in `src/scene_tutorial.c`, 22 of 73 in `src/scene_battle_menu.c`, 7 of 35 in `src/battle_menu_draw.c`, 32 of 53 in `src/battle_mission.c`, 27 of 54 in `src/battle_formation.c`, 4 of 8 in `src/empire_challenge.c`, 3 of 9 in `src/bg_manager.c`, 29 of 46 in `src/system.c`, 6 of 10 in `src/file.c`, 7 of 13 in `src/heap.c`, 4 of 22 in `src/pad.c`, 12 of 55 in `src/gs_packet.c`, 1 of 4 in `src/iop_boot.c`, 11 of 22 in `src/texture.c`, 12 of 28 in `src/sound_stream.c`, 5 of 19 in `src/disc_reader.c`, 5 of 15 in `src/movie.c`, 18 of 28 in `src/sound_cmd.c`, 1 of 11 in `src/runtime.c`, 7 of 13 in `src/ipu_picture.c`, 3 of 17 in `src/text_draw.c`, 1 of 3 in `src/font.c`, 28 of 75 in `src/model.c`, 9 of 83 in `src/unit.c`, 0 of 22 in `src/camera.c`, 20 of 70 in `src/unit_setup.c`, 8 of 27 in `src/weapon.c`, 0 of 5 in `src/unit_touch.c`, 0 of 6 in `src/motion_misc.c`, 5 of 13 in `src/battle_units.c`, 4 of 10 in `src/motion_manager.c`, 37 of 103 in `src/sc_ctrl.c`, 25 of 75 in `src/field.c`, 34 of 92 in `src/stage.c`, 7 of 56 in `src/sc_cond.c`, 44 of 117 in `src/sc_ubase.c`, 2 of 48 in `src/ui_parts.c`, 8 of 36 in `src/cmnparts.c`, all of `src/scene_season_anime.c`). The other functions are equivalent C that
still needs reshaping.
