# EFB: visual effects

**Status: structure understood, parameters not yet.**

There are **15,682 EFB files** (24 MB), stored in offset+size packs ([PACK.md](PACK.md), variant 2) of
up to 395 files. Their content (colours at 1.0, sizes such as 200.0, small speeds and rates) looks
like **particle effect definitions**: one EFB is an effect made of several layers (emitters?).

All values are little-endian.

## Header

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `EFB\0` |
| 0x04 | u32 | Number of layers N (1 to about 10) |
| 0x08 | u32 × 2 | 0 |
| 0x10 | f32 | A small value (0.003 to 0.03): time step or scale? |
| 0x14 | u32 | 24 (size of this header) |
| 0x18 | N × (u32 type, u32 offset) | One entry per layer: its type (0 or 1) and the offset of its block |

The first block starts right after the table, aligned to 16 bytes.

## Layer blocks

Only two kinds of block exist, each with a fixed size:

| Type | Size | Blocks | First word (examples) |
|---:|---:|---:|---|
| 0 | 336 bytes | 22,303 | `0x00020044`, `0x00020056`, `0x00020050`... |
| 1 | 576 bytes | 27,488 | `0x00020052`, `0x00020056`, `0x00020076`... |

Checks: in all 15,682 files the table is in order, the first block starts right after it, and every
block has the size of its type.

## Open questions

The meaning of the fields inside the blocks (they mix flags, small integers and floats). Comparing
many effects, or reading the game's effect code (`effect.c`), will tell.
