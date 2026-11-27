# What is left to decompile

Snapshot of 2026-11-27, from the functions Ghidra found (`ghidra_project/out_r5900/all.c`) and
the address tags in `src/`. Each remaining function is placed in the nearest original source
file named in the executable (the same estimate as `progress/code_map.json`), so the per-file
numbers are approximate; the totals are not.

| | Bytes | Share of the code |
|---|---:|---:|
| Code in the executable | 3,166,376 | 100% |
| Decompiled (`src/`) | 524,700 | 16.6% |
| Sony libraries (left out: a PC port replaces them) | 238,596 | 7.5% |
| VU1 microcode (left out: rewritten for the port) | 42,672 | 1.3% |
| Left to decompile | ~2,283,000 | ~72% |
| Not in Ghidra's function list (gaps, padding, missed functions) | ~77,000 | ~2.4% |

## By theme

| Theme | Left |
|---|---:|
| Empire mode (conquest campaign, events, encyclopedia, endings) | 699 KB |
| Scenes (title, pre-battle, editor, conquest, shop, loading...) | 398 KB |
| Events and scripts (briefings, event configuration, messages, telops) | 346 KB |
| Battlefield (stage textures, effects, bullets, relay camera, distant view...) | 312 KB |
| Interface and system (common parts, secret sorts, Japan map, sound manager) | 228 KB |
| Models and motion (horses, items, flags, model manager) | 202 KB |
| Large functions skipped in files already started | 45 KB |

The largest single files left: `emp_cq_main.c` (121 KB), `BriefingCmnParts.c` (113 KB),
`SecretSorts.c` (100 KB), `HorseModel.c` (94 KB), `emp_FldBase.c` (94 KB), `SceneTitle.c`
(78 KB), `ScenePreBattle.c` (75 KB), `StgTexture.c` (74 KB). The largest functions are around
12 KB (`0x0026CCD0`, `0x00269DF0` in `SceneTitle.c`).

## Plan

1. **Battle core** (~600 KB): the rest of `Stage.c`, `sc_ubase.c`, `sc_sysmsg.c`, `effect.c`,
   `Bullet.c`, `ModelManager.c`, `ObjAction.c`, `RelayCamera.c`, `StgTexture.c`,
   `StgAmbient.c`, `DistantView.c`, `MiniMap.c`, the horse, item and flag models, and the large
   functions skipped so far. With what is already done (units, camera, weapons, scenario,
   strategic map), this is what a battle needs to run.
2. **First PC build** once the battle core is in: compile `src/` for the PC with stand-ins for
   the missing functions, Sony libraries and VU0/VU1 code, and fix what the 64-bit build shows
   (pointers kept in 32-bit fields, scratchpad addresses).
3. **Scenes and events** (~740 KB): menus, pre-battle, briefings, messages.
4. **Empire mode and the rest** (~930 KB).

Short matching passes in between keep turning non-matching C into proven C.
