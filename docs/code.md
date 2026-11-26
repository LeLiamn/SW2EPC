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

## The scene table (`0x00422000`)

24 entries of 0x24 bytes (`SceneEntry` in `src/main.c`), indexed by state number: the state number
itself, then enter, leave, update, step, draw, enter_alt, leave_alt and on_reset. `func_00100500`
copies the current entry into the manager. The game starts on scene 0. Several of these functions are
only reached through this table, so Ghidra's automatic analysis missed them.

A scene is "certain" when its enter function is the function that names the source file (through an
assertion string), "probable" when its functions sit right next to that file's code.

| State | Enter | Source file | Match |
|---|---|---|---|
| `0x00` | `0x00161250` | StateInitialize.c | probable |
| `0x01` | `0x00160220` | StateInitialize.c | probable |
| `0x02` | `0x001BFFA0` | StateDemo.c | probable |
| `0x03` | `0x00236D40` |  | unknown |
| `0x04` | `0x001D4490` | StateBattleInitialize.c | probable |
| `0x05` | `0x001D2A90` | StateBattleInitialize.c | probable |
| `0x06` | `0x001D1F30` |  | unknown |
| `0x07` | `0x001D5F00` | StateBattleInitialize.c | probable |
| `0x08` | `0x00235A70` |  | unknown |
| `0x09` | `0x002267F0` | StatePreBattle.c | probable |
| `0x0A` | `0x0021C5F0` | StatePostBattle.c | certain |
| `0x0B` | `0x00236C50` |  | unknown |
| `0x0C` | `0x001E6860` | StateConfig.c | certain |
| `0x0D` | `0x001E8B30` | StateTreasures.c | certain |
| `0x0E` | `0x002A4210` | StateShop.c | certain |
| `0x0F` | `0x002F1790` | StateConquest.c | probable |
| `0x10` | `0x0015FF70` | StateInitialize.c | probable |
| `0x11` | `0x003F2A50` | SceneTutorial.c | probable |
| `0x12` | `0x002F2620` | StateConquest.c | probable |
| `0x13` | `0x003694B0` |  | unknown |
| `0x14` | `0x0037D060` |  | unknown |
| `0x15` | `0x00390C70` | StateSetupEmpMogi.c | certain |
| `0x16` | `0x003DABC0` | SeasonAnime.c | probable |
| `0x17` | `0x003F46B0` | SceneTutorial.c | probable |

## Scene 0x0C: the options menu (`src/scene_config.c`)

Original source file `StateConfig.c`. Fully decompiled (5 functions):

- **enter** (`0x001E6860`) creates the menu window and resets its page and phase;
- **update** (`0x001E69B0`) runs a 4-phase state machine (opening, in use, closing, leaving); in use,
  it calls the handler of the current page (pages 0 to 10). When leaving, the scene itself switches
  the manager to the requested scene, or back to the one it came from;
- **step** (`0x001E6BB0`) is empty;
- **draw** (`0x001E6BC0`) draws the current page, then its button help line ("Select  Back  OK",
  "Default  Adjust  Back", "Select  Change  Cancel  Play"...; `0xF0` + a letter inserts a button
  icon in these strings);
- **leave** (`0x001E6960`) destroys the window and restores a value saved at enter.

Also decompiled: the page opener `0x001E3DB0` (starts closing the current page, prepares the next
one; page 14 = leave the menu), the page switch `0x001E4030`, page 0 `0x001E4080` (main options page:
3 entries, up/down with wrap-around on a fresh press only, OK/Cancel sounds, and the message boxes
"The abilities and experience of all officers will be reset to default levels. Proceed?" and "Void
interim data?"), a table lookup `0x001E6670` and four small helpers.

Two findings while checking against the machine code:
- page 0 tests "message box 1 open" twice in a row; the second branch can never run (a small bug in
  the original code, kept as is);
- in the page opener, case 3 calls `func_002B3CF0` with the value 2 left in the argument register;
  Ghidra shows the call without argument.

Pages decompiled so far: 0 (main options page), 1 (sub-menu opening pages 5, 6, 7), 3 (save or load
the settings on the memory card), 6 ("press OK on controller 1 or 2", remembers which pad), 8 (screen
position: offsets clamped to −24..24, a reset button). Ghidra flagged 4 "unreachable" blocks in page 3:
they are the compiler's negative fix-up for `(cursor + 1) % 2`, which never runs since the cursor is
unsigned, and they show the original source used `% 2`.

Also decompiled: page 5 (three On/Off options and a value from 0 upwards), page 7 (sound: output mode
0..3, three volumes 0..15, an On/Off option, a sound test that plays the chosen track; leaving puts
the menu music, track 0x1C, back), page 9 (settings of the pad chosen on page 6: three On/Off
options, button set-up, OK) and page 10 (button set-up: eight slots; choosing a value for a slot
swaps it with the slot that had it; a reset button restores the defaults). Page 10's 8 "unreachable"
blocks are again `%` fix-ups for negative values. If the value is in no slot, page 10 writes a ninth
word past the slots: kept as in the original.

The settings helpers (`0x001E3300`..`0x001E3CD0`, 12 functions) are decompiled too: they copy the
live settings at `0x00669D8C` (button map of each pad, pad flags, display flags at `0x669DB0`, sound
flags and volumes at `0x669DB1`..`DB4`, screen offset at `0x669DB5`/`DB6`) to the menu's working copies
and back, apply them, and compare them. A small bug: the pad comparison (`0x001E39F0`) tests one pad
option the opposite way to how it is read, so page 9 always sees the pad settings as changed.

All 11 page handlers are decompiled. The page drawers (`0x002B6450`...) are not decompiled yet.

## Scene 0x0D: the Treasures gallery (`src/scene_treasures.c`)

Original source file `StateTreasures.c`. The scene is a set of sub-screens ("modes", `0x00731334`,
0 to 14), named from their button help lines: 0 main menu, 5 "Select Officer / Skills", 6 "Select
Officer", 7 "Select Mount", 11 "Select Skill", 12 "Turn Page / Enlarge" (an art book?), 13
"Category / Play" (a player?), and screens shared with other code (1, 2, 4, 8, 9, 10, 14).
`func_001E7110` requests a mode: it starts a transition (phase 4), prepares the screen and moves
two layout layers; mode 15 leaves the gallery. The update function (`0x001E8EB0`) handles the
phases (0 opening, 2 leaving, 4 changing mode) and otherwise runs the mode's handler; the draw
function (`0x001E9150`) runs the mode's drawer, then its help line.

All of the scene's code (`0x001E7110`..`0x001E9150`, 24 functions) is decompiled: enter, leave,
update, step, draw, the mode request and the end of a transition, and every mode handler. The main
menu has 10 entries (entry n opens mode n + 1), skipping those not unlocked yet; mode 3 is a
sub-menu opening modes 12 to 14; mode 7 lists 4 mounts (locked ones skipped); mode 11 shows an
officer's skills in 4 columns of 10. Original quirks kept: a dead test in the main menu (cursor
0x10), a missing `break` that runs `func_003BD540` twice for mode 9, and held Up/Down in the mount
list that can stop on a locked mount. The functions after `0x001E95F0` seem to belong to the next
source file.

## Scene 0x0E: the shop (`src/scene_shop.c`)

Original source file `StateShop.c`. The shop has a mode (`0x00773148`, what the player is doing,
0 to 16) and a screen (`0x00773144`, what is drawn, 0 to 9). `func_0029FE50` applies a requested
mode (`0x0077314C`) and picks its screen; mode 16 leaves the shop. Screens, from their help lines:
1 buy skills for an officer (modes 5-8 = slots 0-3), 2 hire guards, 3 and 4 buy mounts, 5 sell, 6
dismiss, 9 skill list. At enter the shopkeeper is picked with the game's random generator
(`seed = seed * 0x41C64E6D + 0x3039` on the scratchpad word `0x7000015C`): 0xB9 (50 %) or 0xB8
(25 %) when their conditions hold, otherwise 0xB5 or 0xB6. Shop music: track 0x2C.

Decompiled: enter, leave, leave_alt, update, step, draw, the mode switch and two helpers. Not yet:
the mode handlers (`0x002A0B40`...`0x002A3DB0`) and the list builders (`0x002A01D0`...).

## Sony libraries and C runtime (compiled with another compiler)

Besides the game's own code (CodeWarrior), the executable links Sony's EE libraries, release 3.0
(version strings `PsIIlibcdvd 3000`, `libdma 3000`, `libgraph 3000`, `libipu 3000`, `libkernl 3000`,
`libmc 3020`, `libpad 3020`, `libvu0 3000`), a C library (`vfprintf`, the `SceStdio...` semaphores of
Sony's stdio) and one sound module (`sd_call.c`). Their code is not written like the game's: they
save callee-saved registers with 64-bit `sd`, where CodeWarrior code uses 128-bit `sq`. Sony built
these libraries with its GCC (ee-gcc 2.9x), so they could be matched locally with that compiler
(GPL, no license); not verified yet.

Functions grouped by that save style (leaf functions counted with their neighbours):

| Range | Size | Contents |
|---|---|---|
| `0x107578`-`0x114C10` | 54 KB | few strings; `sd_call.c` (sound RPC, `0x10FAC8`), probably maths and runtime code |
| `0x118E98`-`0x1206AC` | 29 KB | libcdvd (`0x1194A0`...), libdma (`0x11AEF8`) |
| `0x120E00`-`0x143964` | 128 KB | C library (printf family), libkernl (TTY, SIF RPC `0x12B880`, `rom0:UDNL` `0x131510`), libgraph (`0x126178`, `0x126908`), libipu (`0x13A878`, `0x13C0C8`), libmc (`0x141348`, `0x142038`) |
| `0x1708A8`-`0x171FA4` | 4.5 KB | libpad (`0x1708A8`, `0x170D00`), linked among the game's files |
| `0x403D30`-`0x405028` | 2.7 KB | end of the code, no strings (compiler runtime?) |

In all, about 218 KB, 6.9 % of the code. The ranges are estimates from the register-save style.

## Where each source file is

The game's code names 68 source files in assertion strings; 66 of them are referenced by
code (a `lui`/`addiu` pair building the string's address), which places them in the binary. The
functions below are those that reference the name; a file's code surrounds them.

| Source file | Function(s) referencing it |
|---|---|
| `BgManager.c` | `0x3F8B30` |
| `BriefingCmnParts.c` | `0x2D6890` |
| `Bullet.c` | `0x1AE4F0` |
| `DistantView.c` | `0x22DEC0` |
| `Field.c` | `0x18C490` |
| `FlagModel.c` | `0x2A7AF0` |
| `HorseModel.c` | `0x2AD4C0` |
| `ItemModel.c` | `0x24BCA0` |
| `JapanMap.c` | `0x3A5C40` |
| `MiniMap.c` | `0x20FA70` |
| `ModelManager.c` | `0x1BC8C0`, `0x1BD180`, `0x1BD6D0`, `0x1BD9B0` |
| `MotionManager.c` | `0x17C4A0`, `0x17C6D0`, `0x17CC40` |
| `MovieTelop.c` | `0x1E98E0` |
| `ObjAction.c` | `0x27F610` |
| `RelayCamera.c` | `0x2E6210` |
| `SceneLoading.c` | `0x2F15E0` |
| `ScenePreBattle.c` | `0x28F960` |
| `SceneTitle.c` | `0x278760`, `0x278870` |
| `SceneTutorial.c` | `0x3F4900` |
| `SeManager.c` | `0x23AA60`, `0x23AB20`, `0x23AE30`, `0x23B020` |
| `SeasonAnime.c` | `0x3DA7F0` |
| `SecretSorts.c` | `0x254210`, `0x258130` |
| `Stage.c` | `0x193B90`, `0x194130` |
| `StateBattleInitialize.c` | `0x1D47C0` |
| `StateConfig.c` | `0x1E6860` |
| `StateConquest.c` | `0x2F1950` |
| `StateDemo.c` | `0x1BEAE0` |
| `StateEdit.c` | `0x3767A0` |
| `StateInitialize.c` | `0x160FA0` |
| `StatePostBattle.c` | `0x21C5F0` |
| `StatePreBattle.c` | `0x226380` |
| `StateSetupEmpMogi.c` | `0x390C70` |
| `StateShop.c` | `0x2A4210` |
| `StateStartUp.c` | `0x365530` |
| `StateTreasures.c` | `0x1E7290`, `0x1E8B30` |
| `StationEmp.c` | `0x3B38F0` |
| `StgAmbient.c` | `0x216B40` |
| `StgTexture.c` | `0x1F4B90`, `0x1F4DC0` |
| `Weapon.c` | `0x16CD30` |
| `cmnparts.c` | `0x1A9030`, `0x1A9140`, `0x1AC2A0`, `0x1AC3A0` |
| `effect.c` | `0x1C7620`, `0x1C77D0` |
| `emp_FldBase.c` | `0x34F5A0` |
| `emp_cq_main.c` | `0x30CE90`, `0x30CEF0`, `0x30D820`, `0x30D860`, `0x30D8D0` |
| `emp_cq_text.c` | `0x3907B0` |
| `emp_ending.c` | `0x3B5F70`, `0x3B67F0` |
| `emp_ending_nenpyou.c` | `0x3BB8E0`, `0x3BC450` |
| `emp_ev_predata.c` | `0x32F670` |
| `emp_ev_station.c` | `0x3D36D0`, `0x3D3720`, `0x3D3980`, `0x3D39F0` |
| `emp_ev_still.c` | `0x32B7B0`, `0x32B950` |
| `emp_free_setup.c` | `0x38F4B0` |
| `emp_sc.c` | `0x3E5970`, `0x3E5D80` |
| `emp_war_fix.c` | `0x35ED20` |
| `emp_war_tl.c` | `0x3E3100`, `0x3E4280`, `0x3E4480` |
| `emp_war_wllt.c` | `0x3E7150` |
| `emp_zuroku.c` | `0x3BD2A0` |
| `emp_zuroku_bushou.c` | `0x395330` |
| `emp_zuroku_graph.c` | `0x395E20` |
| `emp_zuroku_movie.c` | `0x3E4CD0` |
| `ev_config.c` | `0x20E8C0`, `0x20EDA0` |
| `ev_main.c` | `0x1D9750` |
| `ev_message.c` | `0x1DB8E0` |
| `file.c` | `0x102410` |
| `font.c` | `0x147580` |
| `sc_ctrl.c` | `0x185D10` |
| `sc_sysmsg.c` | `0x23ED90` |
| `sc_ubase.c` | `0x19A7B0` |

Not referenced by code: `CSecretsScene.c`, `Gsaveload.c`.

## Other finds

- The strings next to the LINKDATA paths include `cdrom0:LINKDATA.DNS;1`: a fourth container that is
  not on the disc (a leftover?), and `file.c`, the source file of the file-loading code.
