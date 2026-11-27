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
| `0x00` | `0x00161250` | StateInitialize.c | certain (start-up picture, `src/scene_initialize.c`) |
| `0x01` | `0x00160220` | StateInitialize.c | certain (title screen, `src/scene_initialize.c`) |
| `0x02` | `0x001BFFA0` | StateDemo.c | certain (demo, `src/scene_demo.c`) |
| `0x03` | `0x00236D40` |  | empty scene (`src/scene_empty.c`) |
| `0x04` | `0x001D4490` | StateBattleInitialize.c | certain (battle set-up, `src/scene_battle_initialize.c`) |
| `0x05` | `0x001D2A90` | StateBattleInitialize.c | certain (the battle, `src/scene_battle_initialize.c`) |
| `0x06` | `0x001D1F30` | StateBattleInitialize.c | certain (battle tear-down, `src/scene_battle_initialize.c`) |
| `0x07` | `0x001D5F00` | StateBattleInitialize.c | certain (battle intro, `src/scene_battle_initialize.c`) |
| `0x08` | `0x00235A70` |  | probable (menu during a battle, `src/scene_battle_menu.c`) |
| `0x09` | `0x002267F0` | StatePreBattle.c | certain (pre-battle menu, `src/scene_pre_battle.c`) |
| `0x0A` | `0x0021C5F0` | StatePostBattle.c | certain |
| `0x0B` | `0x00236C50` |  | leaves at once (`src/scene_empty.c`) |
| `0x0C` | `0x001E6860` | StateConfig.c | certain |
| `0x0D` | `0x001E8B30` | StateTreasures.c | certain |
| `0x0E` | `0x002A4210` | StateShop.c | certain |
| `0x0F` | `0x002F1790` | SceneLoading.c | certain (loading screen, `src/scene_loading.c`) |
| `0x10` | `0x0015FF70` | StateInitialize.c | probable (after a soft reset, `src/scene_initialize.c`) |
| `0x11` | `0x003F2A50` | SceneTutorial.c | certain (starts a tutorial, `src/scene_tutorial.c`) |
| `0x12` | `0x002F2620` | StateConquest.c | certain (Empire map, `src/scene_conquest.c`) |
| `0x13` | `0x003694B0` | StateStartUp.c | certain (start of an Empire game, `src/scene_start_up.c`) |
| `0x14` | `0x0037D060` | StateEdit.c | probable (officer editor, `src/scene_edit.c`) |
| `0x15` | `0x00390C70` | StateSetupEmpMogi.c | certain |
| `0x16` | `0x003DABC0` | SeasonAnime.c | probable (season animation, `src/scene_season_anime.c`) |
| `0x17` | `0x003F46B0` | SceneTutorial.c | certain (prepared Empire game, `src/scene_tutorial.c`) |

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

`0x0077315C` is the player using the shop (0 or 1): it picks the controller and the player's
records. The whole of `StateShop.c` that the scene uses is decompiled (`0x0029FB70`..`0x002A5000`):
scene functions, mode request and switch, every mode handler, the confirmation boxes, the list
builders and the prices.

What the shop does:
- **Skills** (modes 1, 5-8): four slots per officer, up to 5 offers per slot, sorted by level. A
  skill below level 3 is offered; one suited to the other officer type only 25 % of the time.
  Price = level x 400 (x 500 for kind 3), x 0.8 when the skill suits the officer's type, x 1.2
  when it suits the other type. Skills 9, 0x13 and 0x25 at level 4 cost 10000.
- **Mounts** (mode 3, sell in modes 4 and 11): six mounts with random names; 3000 for a type-3
  mount, else 2000-2200; at most 4 owned (buying a fifth offers to sell one). Selling price 4000 or
  5000 for special types, else (rank + 1) x 100 + 900 (or + 1400).
- **Officers** (mode 2): up to 8 candidates the force has room for; price = (level / 4 + 1) x 400
  + 1000, x 500 for unique officers (0-27 and 400-414).
- **Bargain**: each list has a 50 % chance of one random offer at 20 % off; when the system byte
  `0x00669D82` is 3, every skill offer is a bargain.
- **Shopkeeper**: picked at random on entry and again for the farewell; purchases this visit,
  bargains and special items change which one appears.

Original quirks kept: mode 15 divides by zero on an empty list; hiring writes one record past the
last offer; the mount shuffle starts from 0, 1, 2, 3, 4, 2 (no 5); selling asks "any mount left?"
twice; a final test for kind-3 skills can never succeed.

## Scene 0x0A: after a battle (`src/scene_post_battle.c`)

Original source file `StatePostBattle.c` (`0x0021A720`-`0x0022077C`, 37 functions, **all
decompiled**, non-matching except leave and the empty step). The scene's state is one object at `0x00747930` (0x1C00 bytes); it
reads the battle's results from the game state at `0x00669D60` (one 0x48-byte record per player
at `0x00669DE8`, bit 1 of `0x00669F60` = two players, `0x00669F70` = how the battle ended).

- **enter** loads 7 LINKDATA entries (0x38, 0x8D, 0x36, 0x39, 0x37, 0x81 and one chosen by
  `0x0021BE80`; the loader is given `__FILE__` and the lines 1303 to 1309), saves each side's
  officers' levels and nine stats (`0x00747F5C`, 0xA0 bytes per officer), gives the gold earned
  (sum of `0x00749180` plus `0x00749434`, in tens) when `0x00669DB8` is 0, plays music 0x1A, or
  for results 5 to 7 leaves the scene at once, and builds the list of officers shown
  (`0x00748DC8`, 0x24 bytes each, count `0x00748F0C`).
- **leave** frees the 7 entries.

- **update** (`0x0021F680`) runs a window phase (`0x00747940`: opening, in use, closing, waiting
  for the message boxes) and, while the window is in use, the handler of the page shown
  (`0x00747930`, opened by `0x0021B660`):

  | page | handler | shows |
  |---|---|---|
  | 0 | `0x0021D0D0` | the army's experience: five values counting up by 8 a frame (or "no experience") |
  | 1 | (in update) | an item was earned (message box 0) |
  | 2 | `0x0021D6A0` | the officer's results counting up, then a level-up (experience gauge) |
  | 3, 4 | (in update) | the officer's skills, two at a time |
  | 5 | `0x0021E520` | item screen: apply the player's choices (kind, bonus, attributes in slots) |
  | 6 | `0x0021ED70` | keep the new item or the old one |
  | 7, 8 | `0x003DFAB0`, `0x0021EF50` | the officers' rows slide in, then each officer's level-up |
  | 9 | (in update) | save? (memory card through `0x002DAC30`); "no" keeps the items |

- **draw** (`0x00220150`) draws the background, a darkened band (two GS packets), the page (with
  the four drawing modes at `0x0056CCA4` forced to 3) and the button help line.
- The page state lives in small groups: counters `0x00748A30` (army) and `0x00748A60` (officer),
  item screen `0x00748AA4` (mode, cursor, slot, choices still free) and `0x00748AC8` (the item being
  edited, a 0x14-byte item record) with the replay list `0x00748ADC`, per-player choices
  `0x0074901C` (type, value pairs: 0-9 attribute, 10-14 kind, 15 bonus).

## Small scenes (`src/scene_initialize.c`, `scene_demo.c`, `scene_empty.c`, `scene_tutorial.c`, `scene_season_anime.c`)

All decompiled (2026-11-26); most match.

- **0x00 start-up** (StateInitialize.c): waits for the memory card check (`0x002DAEE0`), sound cue
  0x48, a full-screen picture (LINKDATA entry 3, loaded with `__FILE__` and line 25) for 150
  frames (Start skips it after 50), cues 0x4A and 0x47, then leaves (scene 1 when nothing is
  requested).
- **0x01 title screen** (StateInitialize.c, drawing in SceneTitle.c): phases fade in, "press
  Start", the menu, leave. 1500 frames (25 s) without input start the demo (scene 2). Menu entries
  (`0x00160030`): 0 scene 0x13, 1 scene 0x15 (Empire set-up), 2 treasures (0x0D) and 4 options
  (0x0C) with a return to the title, 3 scene 0x14, 5 the demo. Entries 0 and 1 first check the save
  (`0x0019FB10` / `0x0019FB80`) and can ask a yes / no question (title menu state at `0x0076F3D4`,
  `0x0D` = the question); "yes" starts a new game in scene 0x16 (entry 0) or 9 (entry 1). The game
  mode is written to `0x00669DB8` (0, 1, 2, 4, 6).
- **0x10 after a soft reset**: stops everything, closes the message boxes, re-applies the saved
  music and sound-effect volumes (`0x00669DB2` / `0x00669DB3`) and leaves.
- **Leaving a scene** is an inlined macro everywhere (`LEAVE_SCENE` in `scene_initialize.c`):
  requested scene if any and different, else back to `return_to`; with neither, a fallback
  (scene 1, or 0x12 in the shop).
- **0x02 demo** (StateDemo.c): cycles three entries (`0x0045CCBC`): 0 plays a movie or cue (0x48,
  0x4A, 0x47) and returns to the title; 1 and 2 start a random demo battle (scene 4) with one or two
  armies. The battle set-up (`0x001BF5E0`): a stage (random among 24, or for the first 60 demos a
  shuffled list of 30 read from both ends), two different forces among six officer pools
  (`0x004082B0`-`0x00408430`; pool 5 = any officer), or a fixed pairing (`0x00408450`) on stages
  3, 6, 0x0D, 0x14 and 0x1C during the first 60 demos; random values, weather, formations, morale
  and items. The game state is flagged as a demo (`0x00669F60` bit 4, `0x00669DB8` = 1) and bit 4 of
  `0x00669DB0` is saved and cleared for the demo (`0x001BEAB0` puts it back).
- **0x11** starts the first available tutorial among 0x0C-0x0E; **0x16** opens the conquest map and
  the season animation player; **0x03** is empty and **0x0B** leaves as soon as it is entered.

## Scene 0x0F: the loading screen (`src/scene_loading.c`)

Original source file `SceneLoading.c` (`0x002F0810`-`0x002F1930`, 18 functions, all decompiled;
13 match). Opened by `0x002F15E0(_, stage)` when a battle starts: it loads LINKDATA entry
`0x5E + stage` (a pack of five TIM2 pictures, loaded with `__FILE__` and line 353) into the object
at `0x007A2640` (speed 1.2, six layers of 0x34 bytes, the pack).

- A layer interpolates alpha (clamped to 128), position and scale between two values while its
  time (+1.2 a frame) goes from `start` to `end`. Flags: 0x01 loop, 0x02 rotate (-0.06 rad per unit
  of time), 0x04 256 wide and drawn twice (the second copy mirrored), 0x08 512 wide, 0x20 fade back
  after half the window, 0x40 other blending (GS ALPHA 0x43), 0x80 eased progress (square root).
- Layers 0, 4, 1 and 2 are drawn, in that order, over a black full-screen rectangle; layer 2 runs
  along layer 4's picture (a light sweeping over the stage name?).
- Corners are turned with VU0 micro subroutines 0x10 (cosine) and 0x00 (sine), written as
  `vu0_cos` / `vu0_sin` stand-ins, then converted with `vftoi4` and scaled from 480 to 448 lines.
- The scene waits for the loading (`func_00102960`), fades out and leaves.

## Scenes 0x04, 0x06, 0x07: around a battle (`src/scene_battle_initialize.c`)

Original source file `StateBattleInitialize.c` (`0x001D1E80`-`0x001D6B40`, 67 functions, all
decompiled; 30 match; the intro data is loaded with that name, lines 561 and 563).

- **0x04** (enter only): while data loads, goes to the loading screen (0x0F) and comes back; then
  builds the battle (player units at `0x005B4BC0`, 0x240 bytes each, two with two armies; music
  from the stage record `0x005BA694 + stage * 100 + 2`) and goes to the battle (0x05), or, with an
  intro, loads it (LINKDATA `0xAD + type` and `0xC8 + type`) and goes to 0x07.
- **0x07** the intro: one camera per army (`0x00730480`, 0x60 bytes; shot lists at `0x00730A44`,
  0x174 bytes), played at 1.2 times the frame time, drawn as split views with two armies. Start
  (either controller) skips it unless the camera forbids it. Then on to 0x05 (flag 21 of
  `0x00669F60` set), or 0x06.
- **0x05** the battle (time x 1.2). Phases (`0x00730350`): wait for box 1, the battle (pause with
  Start = scene 8; in a demo Start ends it), special sequences (2-5), leave, and the ending camera
  (7, a 250-frame countdown). The end comes from flags of `0x00669F60` and the ending in
  `0x00669F70` (0 / 3 / 4: a jingle 0x1F or 0x21, then scene 7; 5 / 6: a demo cut short). A
  frame: stage, armies, combos (per player, up to 9999 hits, 90 frames to keep a combo; the best
  goes to the player record +0x94), the right stick turns the camera (dead zone 64), effects, and
  the battle clock `0x00669F9C` (frames, up to 180000 = 50 minutes). The soldier groups
  (`0x006A1D58`, 0x47 of 0x68 bytes: 13 soldiers, 5 leaders, strength, timer, flags) pick
  targets and decide to retreat (facing leaders 200 stronger on average), with events queued
  through `func_0023EB40`. Two armies: split-screen drawing, one view per player.
- **0x06** (enter only): frees all battle systems and goes to the results (0x0A), or on to 0x10
  / 0x12 when `func_0032E7B0` says the series is over. Scene 0x05's on_reset (`0x001D4150`) marks
  the battle as ended by a reset (`0x00669F70` = 7) and runs this tear-down.

## Scene 0x12: the Empire map (`src/scene_conquest.c`)

Original source file `StateConquest.c` (`0x002F1950`-`0x002F2718`, 15 functions, all decompiled;
9 match). The frame of an Empire turn: an animated background (LINKDATA entry 4, its player at
`0x0045D680`, one frame every other frame), the map, and the current Empire screen
(`0x007B4E4C`, 0-0x1F): the update calls that screen's handler (a jump table, case 31 placed after
23), the draw its drawer. Screens that can open on top are run first and return 2 when done
(`0x0030E1F0`, `0x0030E4D0`, `0x0038C7C0`, `0x003F13E0`). Screen 0x1F starts a battle (scene 9,
with `0x00669F6C` = 1). Leaving goes to `0x007B4E50` (reset to 0x12 afterwards).

## Scene 0x09: before a battle (`src/scene_pre_battle.c`)

Original source file `StatePreBattle.c` (`0x00220780`-`0x00228174`, 82 functions, all decompiled;
15 match).

- **enter** opens the loading screen for the battle's stage (picture by battle type, `0x00669DD4`;
  mode 2: picture 0x16), prepares the battle (`func_001D42E0`) and, for a free battle, the menu
  (LINKDATA 0x36, and 0x37 outside mode 2); an Empire battle (`0x00669F6C` = 1) uses scene 0x08's
  screens instead. When a movie plays first, the update builds the battle one step a frame.
- **The menu** (page `0x00749A10`, player `0x00749A1C`; a page change goes through
  `0x002209E0`, which also moves the camera at `0x007A1B70`):

  | page | handler | content |
  |---|---|---|
  | 0 | `0x00221AB0` | main menu, 7 entries (`0x00429E60` -> pages `0x0040DF10`: 1, 10, 11, 3, 2, 13, ready) |
  | 1 | `0x00221F70` | the officer: equipment (6), items (7), mounts (9, needs mounts), bodyguards (5); the extra button switches costume |
  | 2 | `0x00222450` | the map |
  | 3 | `0x00223090` | the army: each side's units (Left / Right), the view (L1 / R1), orders: a unit's target (Empire battles) |
  | 5 | `0x00223120` | bodyguards (view only) |
  | 6 | `0x00223220` | equipment: the player's items (`0x00749A28`, 0x52 bytes per player) |
  | 7 | `0x00223600` | items: 4 columns of 10, use / take off |
  | 9 | `0x00223BB0` | mounts: four mounts, one per player (`0x00749AE4`) |
  | 10 | `0x00224D70` | two slots taking values from a list (changing their kind rebuilds the map state) |
  | 11 | `0x00224E20` | the formation |
  | 12 | `0x002254B0` | values for five slots, kept in the order of the values |
  | 13 | `0x00225950` | the music: on / off, track, play |
  | 14 / 15 | (page change) | to the battle (scene 4) / leave and free the battle |

- With two armies each player declares "ready" (`0x00749B08`); the battle starts when both are.
- Pages 3, 10-13 keep their state in small objects (`0x00749B10`, `0x00749B6C`, `0x00749B96`,
  `0x00749B9E`, `0x00749BB6`) that the code reaches through a pointer to the object.
- Camera calls: `func_002EBD80(distance, camera, direction)` and `func_002EBAA0(distance, camera,
  direction, frames)`, the distance passed in `$f12` (tables per battle type at `0x00443530`).

## Scene 0x13: the start of an Empire game (`src/scene_start_up.c`)

Original source file `StateStartUp.c` (0x00365440-0x00369560). The whole file is decompiled:
55 functions, 26 of which match.

- The scene runs in phases (`g_007B7070`, 0-10):
  - 0: the main menu. A wheel of up to 11 entries: 0-6 are always there, 7-10 once unlocked
    (`func_0039FD80`), and four are shown. OK picks an entry; Cancel goes back to the title.
  - 1: the level (`g_007B7078`, 0-4).
  - 3: the options screen. Six rows of up to five values (table `0x00415EB0`), then OK. Start
    resets the values.
  - 2: the entry list (`func_003748C0`: 1 start, 0 back, 3 delete, 4 edit an existing game's
    officers, 5 choose the officers of a new one).
  - 4 and 5: the officers of seven slots. Slot 0 is the ruler, 1-3 and 4-6 are two groups, and 7
    is OK. A new game with no ruler takes the first officer as its ruler.
  - 6: waits for a dialog.
  - 7: the save / start check, which stops the music and fades out.
  - 8: waits for the fade-out.
  - 9 and 10: leave the scene. When nothing was requested, 9 falls back to scene 0x11.
- The state object at `0x007B7104` holds:
  - the slot and the list mode;
  - one "choosable" byte per officer (0x19F officers; 400-0x19E are edited officers);
  - four officer lists of 0x19F entries: choosable, choosable 0x1C-0x18F, rulers, and the list
    shown;
  - their counts;
  - the officers set free and the slots' officers (with a copy taken when the choice starts).
- The scene loads LINKDATA entries 0x7F, 0x82 and 0x81 through the file loader, passing the
  file name and the line.
- The officers allowed per level are `step * (n - 1) + 6`, capped (table `0x00415E80`: 0/6,
  1/20, 2/50, 4/100, 6/150).

## Scene 0x17: a prepared Empire game (`src/scene_tutorial.c`)

Original source file `SceneTutorial.c`. The scene part (0x003F2B20-0x003F4840) is decompiled:
26 functions, 13 of which match.

- **Enter** allocates five buffers (`g_0045D850`-`g_0045D860`) and copies into them:
  - the game state (`0x00669D60`, 0x25310 bytes);
  - the 0x19F officer records (0x9C bytes each);
  - two per-entry tables (25 x 0x14, 25 x 0x78);
  - a set-up record (0xE0 bytes).
- Then it rebuilds the game around the player's entry:
  - the entries of a list chosen by the main menu entry (`g_0045C9C0`, up to eight, -1 =
    none) are emptied, and their places go to random neighbours;
  - the player's officers are sorted; the best half and the next half are shared out over
    those entries, two and three each, and the first entry gets the ruler `func_00327820`;
  - the counters, the edited officers (400-0x19E) and every officer's state are reset;
  - the player's places are scaled by two ratios (50-100 %).
- **Update** waits for the fade and goes to the Empire map (scene 0x12).
- **Leave** frees the buffers. Nothing in this part restores the copies, so a later step
  probably does.

## Scene 0x08: the menu during a battle (`src/scene_battle_menu.c`)

Probable: the scene fades in when it comes from the battle (scene 5). No source file name is
used in it. The whole file is decompiled (0x0022FF30-0x00236C44, 73 functions, 22 match). Its
start is a guess: the code before it belongs to the message window (`0x005BBF18`).

- **Pages:** there are 19 (`g_0074B724`, 0-0x12) for player `g_0074B734`, shown over the
  battle map.
  - `func_002300B0` requests a page; 0x14 goes back to the battle and 0x15 quits.
  - `func_00230160` applies it: the camera, the window layers (`func_0027FE60`) and the
    page's set-up. It has the same shape as `func_002209E0` of the pre-battle menu.
- **Page 0, the main menu:**
  - a free battle has eight lines (table `0x0042A410`, pages at `0x0040E970`). Entries 0, 1
    and 3 are offered only when `func_0022FF30`, `func_0022FF90` and `func_00230010` allow them;
  - an Empire battle has four lines (`0x0040E990`). With two armies, the first player asking
    to go back waits for the other one.
- **Page 3, orders to the units.** It has four modes (`0x0040E9C0`): choose a unit, an order
  (5), a group, or a target. An order is counted in its record (`func_00338410` +0x0B) and
  given through `func_0035F6F0`. The camera follows the unit, group or cell unless the player
  record's bit 2 is set.
- **Other pages:**
  - 5: 16 battle records of 0x110 bytes, through a pointer to `0x005BC5A8`;
  - 7: save or quit;
  - 8: a 4 x 10 grid;
  - 9 and 10: two lists that go back to the battle once used;
  - 11: a question;
  - 12: a sub-menu of pages 8, 6, 5 and 15;
  - 16: a sub-menu of pages 17 and 18;
  - 17: a dialog;
  - 18: "Exiting game. Proceed?".
- **Enter:** it sets the menu camera up from the battle type, with the same tables as the
  pre-battle menu (`0x00442EA0`-`0x00443640`).
- **Update:** it runs in phases (`g_0074B72C`). 0 opens the menu, 1 runs the page's handler,
  and 2-4 apply the requested page.
- **Draw:** it sets two GS registers, draws the map (not in game mode 2), then the page's
  drawer (`func_00282020`...) and its help line.

## The battle menu's windows and drawers (`src/battle_menu_draw.c`)

The file covers 0x0027FD20-0x002856CC: 35 functions, 7 of which match. Its start is a guess:
the code before it handles object actions (`ObjAction.c`). No source file name is used in it.

- **Window animations:** each window of the menu is a record of 0x14 bytes, kept in two
  tables (`0x00772320`, 34 records; `0x007725F8`, 6 records). A record holds two
  rectangles, two alphas, a frame count and a timer.
  - `func_0027FE60(layer)` sets up the records of a page's windows. Odd layers only close
    windows (`func_0028D5D0`).
  - `func_001AE550` advances a record by one frame and returns its current position and
    alpha.
- **How the drawers draw:** they build GS sprite packets themselves: TEX0, RGBAQ, then a UV
  and XYZ2 pair for each corner.
  - X is written as `x * 16 + 0x7000`. Y is scaled by `640 / 480 * 448 / 512`, then written as
    `(y * 16 - 0xE00) / *(int *)0x70000154 + 0x8000`.
  - Text goes through the font state at `0x0056CCA4`: four corner colours (5 normal, 6
    highlighted, 1 a better value) and a size in points.
- **Menu lines** (tables at `0x00410E60`): each line is x, y and an icon from the icon
  rectangles at `0x00440450`. A line slides in from the left as the frames since the page
  opened (`g_007725E4`) go by; the chosen line is drawn brighter and an unavailable one more
  transparent.
- **Page drawers:**
  - 1: the officer — name, portrait, ten stats, level, experience and weapon kind (names at
    `0x0042DC10`);
  - 5: the records, with a turning 3-D marker (VU0 micro routine 0x70, written as a
    `vu0_rotate` stand-in);
  - 6: the bodyguards;
  - 8: the items, a 4 x 10 grid whose slots are lit above a level;
  - 9 and 10: two lists;
  - 15: a mission text (messages `func_00372CF0` 0-11).

## The tutorial window (`src/scene_tutorial.c`, 0x003F4840-0x003F5550)

The window is the end of `SceneTutorial.c`: 20 functions, 10 of which match. Other scenes
open it with `func_003F4D60(tutorial)`; for example, the Empire start-up opens tutorials 0x12
and 0x13.

- **Its state** is a 0x2C-byte object (`g_0045D864`, created by `func_003F5430`): a window
  animation record, the tutorial (0-0x17), two page buffers, the page shown and the page count.
  The buffers are sized for LINKDATA entry 0x91 and filled in turn.
- **Pages:** a tutorial has up to four. Each page is a LINKDATA entry (-1 = none), and the next
  page is loaded while the current one is shown. The table lookup `func_003F4850` reads below
  its copy of the table at `0x0041DA40` (an original bug, kept as it is).
- **Modes:** 0 closed, 1 open, 2 opening, 3 closing, 4 a page fading in, 5 a page fading out.
  While the window is open, OK turns the page; on the last page it closes the window. The window
  takes the message box and list flags while it is open and gives them back when it closes.
- **Draw:** the screen is darkened, then the frame (`func_001A4340`) and the page picture
  (`func_001ABA70`) are drawn.
- **Update:** `func_003F5120` returns 0 when the window is closed, 2 on the frame it closes,
  and 1 otherwise. The scenes wait while it returns non-zero.

## Missions during a free battle (`src/battle_mission.c`)

The module covers 0x003F5550-0x003F6BA0: 53 functions, 27 of which match. It comes after
`SceneTutorial.c`; its source file name is unknown.

- **The mission** is 8 bytes in small data (`0x0045D868`): the soldier group, the kind (0-7),
  the time limit in minutes (3000 frames a minute, PAL), a target value and a status (0 offered,
  1 running, 2 over, 5 none). An Empire battle keeps the mission in its save, at record +0xAE0.
- **Offer:** when a free battle starts, a mission is offered one time in four. Both sides need
  8 groups or more, and the battle type must not be 6-0x12.
  - The group is the eligible one with the best score: a random part (0-49), bonuses when its
    leader is linked to the other side's leaders, and the difficulty's bonus (table
    `0x0041DA80`).
  - The kind is drawn among the eight whose condition holds (table `0x0041DAA0`). The time is
    5-7 minutes; kinds 0, 1, 3 and 4 also get a target.
- **Check:** each kind's goal is in the table at `0x0041DAC0`. While the group is active and
  time remains, the mission is won once the goal is reached. It is lost when time runs out. If
  the group is gone, it is won for a player's group and lost for an enemy one.
  `func_0035D300` announces the result, and a reminder plays at each of the last three minutes.
- **Display:** the text is message 0x96 + kind, and page 15 of the battle menu shows it.

## Formations during a battle (`src/battle_formation.c`)

The module covers 0x003F6BA0-0x003F84A4: 54 functions, 23 of which match. It comes after the
missions; its source file name is unknown.

- **State:** each side (0 the player, 1 the enemy) has 16 bytes at `0x007BFEF0`:
  - the slot in use;
  - six slots, each holding a formation (0-9, 10 = none) and a "used" bit;
  - points (0-180);
  - three flags: bit 0 the advantage, bit 1 the first change made, bit 2 a warning given;
  - a counter (0-300).
- **Rules:**
  - Changing formation costs points (table `0x0041DC70`).
  - The advantage of one formation over another is a 10 x 10 table (`0x0041DAE0`). After a
    change, the side with the advantage gets a bonus of 10 per point of advantage
    (`func_0033BE80`).
  - Each side gains one point every 100 frames. The player also gains 30 points each time a
    count passes a multiple of 50, and 150 more at each multiple of 1000.
- **Enemy:** at the start of a battle, the enemy picks a formation that is worse than the
  player's 30% of the time, equal 50% of the time, and better 20% of the time.
- **Saving:** an Empire battle keeps this state in its save (record +0xAE8). Page 10 of the
  battle menu changes the player's formation.

## An Empire event: a battle against a chosen officer (`src/empire_challenge.c`)

The module covers 0x003F84B0-0x003F8B2C: 8 functions, 4 of which match. It sits between the
formations and `BgManager.c`; its source file name is unknown. The event's state is the object
that `func_003EA000` returns: +0 holds the step, +8 the player's officer.

- **The opponent** is drawn at random among the officers with the highest value of
  `func_002F34E0` (the level?). It must serve a valid entry, be free, and not be the player's
  ruler.
- **The battle** is set up on stage 0x20E, with the opponent placed in a free entry.
- **After the battle,** the steps run in order:
  1. The reward: message 0x11E, half of `func_00331010`, and a tenth of that to the player's
     entry. When `func_0036B260` holds, message 0x11D is shown instead.
  2. The opponent goes back free once the message is closed.

## Backgrounds (`src/bg_manager.c`)

Original source file `BgManager.c`, whose name is passed to the file loader at `0x003F8B30`.
The file covers 0x003F8B30-0x003F961C: 9 functions, 3 of which match.

- **The background** is LINKDATA entry 0x9B + n, with n from 0 to 4, loaded into
  `g_0045D870`. It is drawn either full-screen (512 x 384) or as one sprite at its own size, in
  the colour `g_0045D128`.
- **The picker** uses the object at `func_002FC2C0() + 0x694`. It holds twelve lists of up to
  ten entries:
  - entries 0-0x58 are sorted into lists by their group (`func_00313CB0`);
  - list 11 is made of the table at `0x0041DD60`, then 0x65;
  - an empty place in a list holds 100.

  The picker is drawn in two sliding windows (`0x007BFF10`, `0x007BFF30`). Up and Down move
  the cursor, and Cancel gives -1.
- **After the file,** from `0x003F9680` to `0x00403D30`, the text section holds VU1
  microprograms (VIF `MPG` packets, command 0x4A), not C code.

## The system layer (`src/system.c`)

This file covers 0x00100410-0x00102410, the rest of the "start-up and main loop" area: 46
functions with those of `main.c`, 25 of which match. Its source file name is unknown. The
start-up code at 0x00100008 is assembly and is not written in C: it sets gp and the stack,
clears the BSS and calls `main`.

- **Shutdown:** `func_00100410` stops the game's systems at the end of the main loop.
- **IOP requests:** a request is four words, and the first word's bit 31 marks a second kind.
  A request is either sent at once (`0x0045D8D0`) or queued (`0x0045D8F0`). The queue is sorted
  by the sum of each request's first two words and sent when the IOP is free; -1 ends it.
- **Display:**
  - The GS has two display environments at `0x00500130`.
  - Mode 0 is full height: 448 lines, vertical scale 1 (`*(int *)0x70000154`). Mode 1 is half
    height: 224 lines, scale 2.
  - The screen offset ranges from -24 to 24 on each axis, written into the DISPLAY registers.
  - The clear packets are prepared in advance (`0x0045E900`, `0x0045FC20`).
- **Frames:**
  - Each frame's GS packets go into one of two buffers (`0x00460130`, `0x004B0130`, 0x50000
    bytes each), as a DMA chain written through `*(u32 **)0x70000158`.
  - `func_001020E0` ends the frame: it closes the chain, waits on the frame semaphore and flips.
  - The vertical blank handler (`func_00102150`) flips when the frame is ready and signals
    the semaphore.
  - A DMA handler (`func_00101C20`) reads the line counter.
- **Timers:** RCNT0 and RCNT1 count with mode 0x83. Constants for 1/60 s, 60 and 3600 are
  set up at start.

For the PC port, this file is to be replaced by the platform layer.

## Reading the containers (`src/file.c`)

Original source file `file.c`, whose name is passed with the line number to its own reads. It
covers 0x00102410-0x00102A00: 10 functions, 6 of which match. `main` (0x00102A20, in `main.c`)
follows, then the memory allocator.

- **The four containers:** 0 ANS, 1 BNS, 2 CNS, 3 DNS. DNS is not on the disc and is never
  opened.
- **At start-up:** each container's first sector is found by name (`\LINKDATA.ANS` ...).
  Then its header is read: 0x800 bytes, or 0x7000 bytes for BNS. A header starts with the magic
  0x33B59, and from +0x10 it holds each entry's offset and size.
- **Reading an entry** (`func_001026D0`): it is read by sectors into a buffer, which is
  allocated when none is given. The read goes through the request queue of `system.c`, either
  queued or at once.
  - A BNS entry can come from a second source (`g_0045CC04`) when `func_00115C70` holds and the
    buffer is aligned: a preloaded or host copy?
  - Other files are read by path (`func_00102880`); the end of the last sector is cleared.

## The memory allocator (`src/heap.c`)

The allocator covers 0x00102A80-0x00103090, right after `main`: 13 functions, 7 of which
match. Its source file name is unknown.

- **The area** runs from `0x007C1000`, after the BSS, to `0x01FFF000`. Two heaps share it:
  heap 0 allocates upwards from the start, and heap 1 downwards from the end. `0x005004D8`
  picks the heap in use; the game sets heap 1.
- **Blocks:** each block has a 16-byte header holding its previous and next blocks, its data
  pointer (0 when free) and its size including the header.
- **Allocating** is first fit, starting from the heap's cursor; the rest of the chosen block is
  split off. `func_00102D30(size)` allocates on a 16-byte boundary, and
  `func_00102DB0(align, size)` on `align`.
- **Freeing** (`func_00102EC0(data)`) searches back from the last block, merges the block with
  its free neighbours and moves the cursor back to it.
- **Saving the state:** `func_00102B80` saves both heaps' state.

## The controllers (`src/pad.c`)

The pad code covers 0x00103090-0x0010424C, after the memory allocator: 22 functions, 4 of
which match. Its source file name is unknown. It is built on Sony's pad library, libpad.

- **Ports:** there are two, at `0x00500700`, 0x88 bytes each.
- **Each frame** (`func_001038D0`), every open pad first goes through libpad's set-up steps:
  the analog mode is locked, then the pressure mode and the actuators are set. Then its data is
  read.
  - The buttons are active low.
  - The sticks are re-centred inside a radius of 64, and the left stick also works as the
    D-pad unless flag 0x10 says otherwise.
  - Pressure values below 0x20 are dropped.
  - The mode must be analog (0x73) or with pressure (0x79). The original compares with 0x73
    twice.
- **Pressed and held:** "pressed" means a button went down this frame (+0x4C). "Held" (+0x4E)
  also repeats every 4 frames once the button has been down for 16 frames.
- **Vibration:** two motors, each with a level and a frame count; the levels are sent when they
  change.
- **Soft reset:** holding Start + Select on any pad for 10 frames sets the soft reset request
  `g_0045D20C` (see `main.c`), when `func_001037F0` allows it.

## The GS packets (`src/gs_packet.c`)

The code at 0x00104250-0x00106414 builds what the Graphics Synthesizer draws: 55 functions, 12
of which match. Its source file name is unknown.

- **Scratch buffers:** each frame has 0x30000 bytes (two buffers at `0x00500810`, picked by the
  frame index in the scratchpad at `0x70000150`). The bytes used are counted at `0x00560810`.
  When a buffer is full, its start is handed out again (the packets then overwrite each other).
- **Two ways to send a packet:**
  - *queued:* a 16-byte node (next, address, quadword count) goes into one of ten layers. The
    layers form one chain with a sentinel per layer, at the start of the buffer. A node is put
    just before its layer's sentinel, so the chain runs through the layers in order (a caller's
    layer `n` is list `n + 1`, at most 9). At the end of the frame, `func_00105F90` turns the
    chain into DMA tags after a header of GS settings, then starts the chain again.
  - *at once:* the same tags are written straight into the DMA chain (cursor at `0x70000158`),
    between a header and a tail.
- **DMA tags:** a "ref" tag for each packet, then two VIF codes: FLUSHA (or NOP, for texture
  data: its node's address has bit 0 set), then DIRECT, which passes the data to the GIF.
- **Packets:** GIF tags in register-list mode for sprites and quads (flat, one colour per
  corner, textured with ST or UV coordinates), A+D register writes, a screen clear (a sprite
  drawn with the depth test set to "always").
- **Textures:** TIM2 pictures and their CLUTs are uploaded as GS transfers (BITBLTBUF, TRXPOS,
  TRXREG, TRXDIR, IMAGE), followed by a TEXFLUSH. The functions return the TEX0 value to draw
  with: 4-bit pictures have 16-colour CLUTs (8 x 2), 8-bit pictures 256-colour CLUTs (16 x 16).

## Starting the IOP (`src/iop_boot.c`)

The code at 0x00106420-0x00106748, just before `main.c`'s game set-up, has 4 functions, 1 of
which matches. It reboots the IOP with the disc's `MODULES\IOPRP300.IMG` and sets the drive to
DVD. Then it loads the game's nine IOP modules from a single file, `MODULES\MODULES.BIN`: the
table at `0x00400C30` gives each module's offset and size in quadwords. The file is read into
the EE's memory, and each module is copied to the IOP by DMA and started there. A module that
fails to start is tried again.

## TIM2 textures (`src/texture.c`)

The code at 0x00106840-0x00107574, after `main.c` and before Sony's libraries, has 22
functions, 11 of which match. The first three are the frame's steps: the start (the random seed
moves on, the pads are read) and the end (the GS packets go out). They may belong to `main.c`'s
file. The rest loads TIM2 files into the GS memory:

- **Check:** `func_00106E00` accepts version 4, format 0, one picture. Pictures with mipmaps
  are not loaded.
- **Loading:** the pixels and every CLUT are loaded straight away by Sony's image transfer; the
  vblank flip is held meanwhile. The CLUTs follow the same layout as in `gs_packet.c`: 8-bit
  pictures have 16 x 16 entries, 4 buffers apart; 4-bit pictures have 8 x 2 entries, 1 apart.
  Their colours are 32-bit or 16-bit.
- **Sizes:** `func_00106AA0` rounds a texture up to the GS memory's layout (blocks while it fits
  in a page, then whole pages), so that callers can place the next texture right after it.
- **TEX0:** the functions return the value to draw with. It holds the base, the buffer width
  (rounded to 128 pixels for 4-bit and 8-bit pictures), the format, the log2 of the size,
  colours with alpha, and the CLUT's base and format.

## Sound and the music stream (`src/sound_stream.c`)

The code at 0x00114B20-0x0011585C has 28 functions, 12 of which match. It sits on a sound
library linked just before it: an IOP sound driver reached by RPC, whose functions start at
0x0010B000. Its source file name is unknown.

- **Volumes** go from 0 to 0x3FFF. Each can fade: a fade is (from, to, frames, frame) and moves
  one step per frame. There are fades for the master volume, for the music stream and for each
  of the 16 sound channels (at `0x00560F60`).
- **Music stream requests:** a request word at `0x00560FE0` holds the bits 1 play, 2 stop, 4 a
  third request and 8 set the volume. `func_001155F0` handles it once per frame, under the sound
  semaphore, and only while the disc reader is idle. A looping stream that stops is started
  again.
- **Set-up:** `func_001151C0` starts the driver and the disc reader. `func_00114FA0` sets up the
  voices, the two sound banks, the reverb and the default volumes.

## The disc reader (`src/disc_reader.c`)

The code at 0x001158A0-0x00116604 has 19 functions, 5 of which match. The reads of `file.c` go
to a thread of their own (priority 5, its stack at `0x00561000`). The thread receives a list of
up to 255 requests, each a sector or a file path, an offset, a sector count and a destination.

- **Chunks:** the thread reads at most 0x400 sectors at a time. Before each chunk it waits until
  the music stream has buffered enough data (from 0x32 up to 0x5F), since music and data come
  from the same disc. It pauses the music meanwhile.
- **File paths:** a path such as `cdrom0:\PATH` becomes `\PATH;1` in upper case for libcdvd.
  Each file is searched for up to 5 times.
- **Destinations:** bit 31 means the IOP's memory, bit 1 a read through the sound driver.
- **Cancel:** `func_00115D40` cancels the reads under way.

## The movies (`src/movie.c`)

The code at 0x00116610-0x0011719C sets up the MPEG movie player and runs it: 15 functions, 5
of which match. The player itself (`func_00107578`) is linked before the sound library.

- **Parameters:** a block at `0x00400C78` gives the player its sizes (640 x 512), its buffers
  and its callbacks: the end of the movie, a stream header, the stop test, each frame, each
  vblank, and the game's allocator.
- **Thread:** the player runs in a thread of its own (priority 2, work area of 0x5014 bytes). The
  scratchpad is saved and restored around it.
- **Display:** the movie has its own double buffer at `0x00562830`. At each vblank the display
  is moved one line down and made one line shorter, for the interlaced field. At the end, the
  game's frame settings are sent again.
- **Caller's callbacks:** one is called with each frame's number (counted from 1); the other
  can stop the movie (the pads are read once, before its first call).

## Sound commands and channels (`src/sound_cmd.c`)

The code at 0x001171A0-0x00117E4C has 28 functions, 18 of which match.

- **Command buffer:** commands for the sound driver are written into a buffer at
  `0x00562A80`, under the sound semaphore. The buffer is sent when it holds more than 0x3F2
  bytes, and otherwise once per frame.
- **Channels:** there are 16 sound channels at `0x00562E80`, 0x40 bytes each. A channel keeps
  its settings, its volume (0-0x7F) and up to 15 sounds; each sound is a pointer to a (size,
  offset) record of the sound bank, which sits in the IOP's memory.
- **Voices:** a second bank holds voices that are played by streaming.

## Run-time helpers (`src/runtime.c`)

The code at 0x00117EB0-0x00118E94, just before libcdvd, has 11 functions, 1 of which matches.

- **Compiler run-time:** the destructor chain run at exit, and the static constructors run
  before main (the game has none). These use branch-likely instructions, which the game's own
  code never uses: they come from a library built with other settings.
- **VU0 set-up:** constant vectors are loaded into vf21-vf31. A unit matrix, two rotations by pi
  and constant vectors are written into the scratchpad.
- **Sorting:** an insertion sort and a quicksort of 16-byte records, keyed by their first
  float. The quicksort leaves runs of 10 or fewer records to the insertion sort.
- **Memory:** a quadword clear, two memory fills and a copy for blocks over 0x1B800 bytes.
  - The copy writes the quadwords from the start of the destination, not after the first bytes,
    so it is only right when the source is 16-aligned.
  - These loops are unrolled by 8 in the original, so this code was built without
    `opt_unroll_loops off`.

## Pictures decoded by the IPU (`src/ipu_picture.c`)

The code at 0x00143970-0x00144070, right after Sony's libraries, has 13 functions, 7 of which
match. It decodes the "ipu2" pictures (MPEG intra frames) with the IPU, into 16 x 16 tiles of
32-bit pixels.

- **Transfer:** the coded data goes to the IPU by DMA channel 4. The tiles come back by channel 3
  into one buffer per frame.
- **Upload:** each tile is then sent to the GS by an upload packet of its own (see
  `gs_packet.c`).
- **Queue:** up to 4 decodes can wait. The end-of-transfer handler of channel 3 starts the next
  one.

## Drawing text (`src/text_draw.c`)

The code at 0x00144080-0x00147574 has 17 functions, 3 of which match. It is probably the start
of `font.c`, whose name the next function passes.

- **The font** (`0x004053C0`) is a texture of fixed-size cells, with an optional table of cell
  positions and of character widths. A second texture holds the cells after the first page.
- **Styles:** each character is one textured sprite, drawn in one of six styles: a colour per
  corner, flat, with a shadow, outlined (two kinds), or by a callback.
- **Text state** (`0x0056CCA0`): the style, the colours (indices into the palette at
  `0x004248F0`, with separate alphas), the scales (20.0 = the font's size), the line height and
  the depth.
- **Codes in a string:**
  - `[NN` sets colour NN, `]` goes back to the state's colours;
  - TAB moves to the next tab stop, LF starts a new line;
  - 0xF0 followed by a letter draws a button icon;
  - the lead byte of a two-byte character is shown as `@`.
- **Helpers:** functions measure a string, count its characters, squeeze it into a box, and
  break its lines at spaces.

## Loading the fonts (`src/font.c`)

`font.c` (0x00147580-0x00147778, 3 functions, 1 of which matches) loads the two fonts at
`0x004053C0` from LINKDATA.BNS entries 1 and 2: TIM2 pictures loaded into the GS memory once.
Font 1's second texture is the same picture with the next CLUT. It then sets the text state's
defaults: flat style, colour 5, opaque, scale 16, lines 20 pixels apart.

## Motion curves, tm3 textures and models (`src/model.c`)

The code at 0x00147780-0x001508E4 handles 3D models: 75 functions, 26 of which match.

- **Motion curves** (see `docs/formats/MOTION.md`):
  - each track is a word (node in bits 0-7, component in bits 8-12, key size in bits 13-15, key
    count from bit 18) followed by its keys;
  - a key size of 0 means the value 0, 1 a constant, more a list of cubic segments;
  - components 9-16 are a camera's (the motions with "atypical" tracks are camera motions, and
    component 15 is halved: an angle?).
- **tm3 textures:** their GS upload packets are patched with the GS buffers given (the pixels in
  8-bit, then 16 palettes), then sent by DMA "ref" tags, followed by a TEXFLUSH.
- **Models:**
  - setting one up turns the file's offsets into pointers and adds the texture's base to each
    part's VIF packets;
  - each part is sent after a VU1 header chosen by its kind (`0x004062F0` or `0x00406310`).
- **Skeletons:** an object drawn with a skeleton (0x220 bytes) has a node per bone (0x70 bytes:
  translation, rotation, local matrix, parent). The local matrices come from the VU0 micro
  subroutine 0x50. The world matrices are brought up to date by walking up each node's parent
  chain (`func_00149730`, 15 KB of VU0 code in the original), for fixed lists of bones by mode
  (body, arms, fingers when the model has more than 26 nodes) and ranges given by the model.
- **Motions:** applied to node ranges at a time, blended from three poses for the face (nodes 47
  and up), or blended back from a saved pose for transitions (angles by the shorter way round).
- **Swing nodes** (a skirt?): they keep last frame's position, are pulled towards their parent at
  their length, and are pushed out of the body by kind (side, front, back, between the legs).
- **Drawing:** each object's packet and node matrices go to VU1, then its parts. Planar shadows
  use a projection matrix. There are lights, cameras (a direction code in eight sectors) and the
  loading of three VU1 microprograms.

## Battlefield units (`src/unit.c`)

The code from 0x001508F0 on handles the characters on the battlefield. A character is a large
object (0x630 bytes, in an array at `0x00574DE0`; the players' bodyguards are units 0x89 +
player * 3 + slot) whose fields are mostly unknown and are reached by offset. The file covers
0x001508F0-0x0015FE58, up to `scene_initialize.c`:

- **Hits:** the main hit handler (`func_00153E50`) picks the reaction by the unit's state: on a
  mount, in the air, knocked down, stunned by a charged attack, or a special officer. The other
  hit functions cover guards and guard breaks with their hit stop (the animation slowed by the
  damage), weapon clashes (two units facing each other within 200 units), and being knocked off
  a mount.
- **Actions:** `func_00156AF0` starts an action. It records the previous action, adjusts the
  speeds, makes the turn the action asks for, and starts the pose transition.
- **Movement:** gravity and landing, the push of a hit, and the motion's root movement.
- **Holds:** grabs, throws and struggles (button presses counted at +0x159; the first to lead
  by more than 12 wins).
- **Other:** the locked target, stored projectiles, spread shots, and calling a player's
  bodyguards.
- **Each frame** (`func_0015EE10`):
  - the unit's time scale: the special state, slow motion, being slowed, the players' boosts and
    stuns, at most 1.44;
  - the action control: hints shown to the players, special moves at a hit's first frame;
  - the next action from the controls, with an action queued until the hit's cancel frame;
  - messages and voices at an action's frames;
  - the animation's frame and its chains (random idles when mounted);
  - the attack effects from the body nodes and weapons a hit names;
  - the movement state machine: aiming at the direction held at a rate per frame, turning,
    running at the weapon's or item's speed multiplier, mounts, jumps;
  - the bodyguards, and the players' camera and path records.

## Scene 0x14: the officer editor (`src/scene_edit.c`)

Original source file `StateEdit.c`: its name is passed to the file loader at `0x003767A0`. The
whole file is decompiled (`0x003766C0`-`0x0037DA64`, 117 functions, 36 match).

- The editor's state is a 0xBA0-byte block (`0x0045D7C8`, plus a 0x780-byte one at
  `0x0045D7CC`): the 15 created officers (copied from the game state at `0x00669D60 + 0x254`,
  0x38 bytes each, at +0xBC), the officer being edited at +0x404 (+0x18 body, +0x1C colour,
  +0x20 weapon, +0x24 and +0x2A-0x2E choices) and its copy at +0x43C (a page's changes are undone
  from it), the page (+0xB4, asked for at +0xB0), per page a cursor and its scroll.
- **Pages:** there are twelve (handlers in the table at `0x004169A0`); 12 leaves for the title
  (scene 1). Changing page goes through phases (in, out, timer).
  - 0 is the two names. Each is typed on a grid of 17 x 6 characters (`0x0045C478`, `@` =
    none) and holds at most 7 characters; L / R move in the name and the extra button deletes.
  - 1 is the body (13) and its colour (10).
  - 2 is the weapon, from a list that depends on the body's group: male (0x1C-0x21, 0x30),
    female (0x36-0x38) or others (0x33-0x35). Changing the body drops the choices the new group
    cannot use.
  - 3, 5, 6 and 7 are other choices (record +0x2B, +0x2A, +0x2D, +0x2C).
  - 4 is the voice, four per group. The extra button plays one of eight samples at random.
  - 8 is a 14-wide grid of 0x43 entries (+0x2E).
  - 9 is two colours, each picked from a grid of 13 x 11 (0x8E colours). The extra button
    picks two different colours at random.
  - 10 is the editor's menu (pages 0-9, then done). Done asks whether to keep the changes
    (messages 0x2D1-0x2D4).
  - 11 is the list of the 15 edited officers. OK edits one or creates one, the extra button
    deletes one (unless it is in use in the battle's sides), and Cancel asks to save. The save
    goes through the memory card dialog (`func_002DAC30`); if it fails, the copies are put back.
- **Lists:** a list page shows its choice on the model at once, restoring the record from the
  backup first. OK keeps the choice. Cancel sets +0xB97 so that the menu restores the record.
- A model of the officer is shown (unit `0x00574DE0`): the weapon gives a model kind (weapons
  0x3E-0x67 share four kinds), the view height comes from `0x00416720` / `0x00416780`.
- The accessors are leaf functions the compiler knows not to touch other registers: Ghidra then
  loses the values kept across their calls; the disassembly shows them.

## Scene 0x15: Empire set-up (`src/scene_setup_emp_mogi.c`)

Original source file `StateSetupEmpMogi.c` (`0x00390940`-`0x00391250`, 8 functions, all decompiled;
6 match). "Mogi" is probably 模擬 (a mock or free game?).

- **enter** (`0x00390C70`) resets both sides (value 10, and 10000 for each of 8 slots), allocates a
  0x8EC4-byte work object (pointer at `0x0045D7E4`, read by `0x00390940`), loads LINKDATA entry 0x88
  (`func_001026D0(..., __FILE__, 206)`: the loader takes the source file name and line), and starts
  the set-up screens, music 0x31 and the fade-in. Coming back from scene 9 skips all of it.
- **update** (`0x00390EE0`) pauses while a message box is open, then runs the set-up screen of the
  current mode (work + 0x8E6C): 0 goes to 2; 2-4, 5, 6-7 and 8 call the screens of the neighbouring
  files (`emp_free_setup.c` and others); 1 leaves once box 1 is closed; 9 waits for
  `func_0017DDA0` (at most 250 frames), picks the computer side (`0x003909A0`: two random values
  below 31, and a check around value 0xB5) and leaves, to scene 9 when nothing else is requested.
- **draw** (`0x003911B0`) draws the current set-up screen.

The file before it, `emp_cq_text.c` (`0x00390760`-`0x00390934`), loads a text table (pointer at
`0x0045D7DC`, handle at `0x0045D7E0`) and turns its offsets into pointers.

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
