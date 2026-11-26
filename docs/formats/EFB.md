# EFB: visual effects

**Status: decoded** (structure checked on all files, main parameters mapped from the game code).
Tool: `tools/efb.py` (prints an effect, checks every file of the disc).

There are **15,682 EFB files** (24 MB) in LINKDATA.BNS entries 2031 to 2122, stored in offset+size
packs ([PACK.md](PACK.md), variant 2). One EFB is a particle effect made of layers. The game's
effect code (source file `effect.c`, around `0x001C0000`-`0x001CC000`) loads the packs in
`func_001C77D0` (entry `0x7F0`, `0x7F1` + battlefield number, `0x80E` + number in two-player games,
and the officers' effect entries), and an effect instance keeps a pointer to its EFB (instance
+0x20). All values are little-endian.

## Header

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `EFB\0` |
| 0x04 | u32 | number of layers N (1 to about 10) |
| 0x08 | u32 × 2 | 0 |
| 0x10 | f32 | time step: how far the effect's clock moves each frame (0.0056 = 1/180...) |
| 0x14 | u32 | offset of the layer table (always 0x18; the game turns it into a pointer) |
| 0x18 | N × (u32 type, u32 offset) | one entry per layer: its type and the offset of its block |

The first block starts right after the table, aligned to 16 bytes; blocks follow each other.

## Layers

`func_001C09C0` runs every frame: a layer starts when the effect's clock passes its start time
(type 0: block +0x1C, type 1: block +0x5C), once (a bit per layer in the instance).

### Type 0: sprite (336 bytes)

Started by `func_001C3490`, which creates one particle. The parameters start at block +0x10
(offsets below are from the start of the block):

| Offset | Type | Meaning (reader) |
|---:|---|---|
| 0x00 | u32 | first word: settings (`0x0002xxxx`) |
| 0x04 | u32 | flags (bits tested by the update code) |
| 0x10 | u32 | texture number (mapped through tables at `0x00426000` / `0x00426070`) |
| 0x14, 0x18 | u32 × 2 | texture animation grid: frames across, frames down (random start frame when flag 0x20) |
| 0x1C | f32 | start time |
| 0x20 | f32 | clock step of the particle (`func_001C3890`) |
| 0x24 | f32 | lifetime (below 1.0, the particle stops early) |
| 0x28-0x30 | f32 × 3 | motion parameters read by `func_001C2540` |
| 0x34 | f32 | read by `func_001C2740` |
| 0x38, 0x3C | f32 × 2 | values copied at start (`func_001C15E0`) |
| 0x40, 0x44 | f32 × 2 | read by `func_001C27C0` |
| 0x48, 0x4C | f32 × 2 | width and height |
| 0x50, 0x54 | f32 × 2 | random range of width and height |
| 0x60 | f32 × 4 | position (x, y, z, 1) |
| 0x70 | f32 × 4 | speed |
| 0x80 | f32 × 4 | acceleration, added to the speed every frame |
| 0x90, 0xA0 | f32 × 4 | random ranges of position and speed |
| 0xB0-0xCC | f32 × 8 | copied to the particle at start (`func_001C1810`) |
| 0xD0 | f32 × 4 | rotation speed, added to the angle every frame (angles wrap at ±π) |
| 0xE0, 0xF0 | f32 × 4 | random ranges |
| 0x100-0x11C | f32 × 8 | copied at start (`func_001C1810`); 0x10C also read by `func_001C2540` |
| 0x120 | f32 × 4 | added every frame (`func_001C2270`) |
| 0x130, 0x140 | f32 × 4 | random ranges (`func_001C1900`) |

### Type 1: emitter (576 bytes)

Started by `func_001C4B10`, which creates an emitter:

| Offset | Type | Meaning |
|---:|---|---|
| 0x04 | u32 | flags (bit 0x100000: delay from 0x1C) |
| 0x0C | u32 | number of particles |
| 0x10 | u32 | random range of the number of particles (half added or removed) |
| 0x1C | s32 | delay, in frames, when flag 0x100000 is set |
| 0x20 | u32 | copied to the emitter |
| 0x5C | f32 | start time |

The rest of the block holds the parameters of the emitted particles, read by the emitter update
code (`func_001C4D10` and neighbours); not mapped field by field yet.

## Checked

`py tools/efb.py --check image.iso`: the 15,682 files parse (header, table, block positions and
sizes, nothing after the last block, start times positive, animation grids at most 256 frames).
Typical values: animation grids 1×1, 1×4, 4×4; sizes 1 to 2,500 units; start times in seconds
(0.133 = 8 frames at 60 Hz); emitters of 2 to 20 particles.

Not mapped yet: the meaning of each flag bit, a few parameter fields named only by their reader,
and the emitted particles' parameters inside type 1 blocks.
