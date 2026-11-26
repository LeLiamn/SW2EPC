# Packs: Koei's offset-table archives

**Status: understood.** Tool: `tools/pack.py` (tree, statistics, extraction of the leaves).

Most entries of `LINKDATA.BNS` are not single files but **packs**: small archives with no signature
and no names, nested inside each other (up to 3 levels) and inside LINKDATA containers. Opening
LINKDATA containers and packs recursively gives **41,079 leaf files** in `LINKDATA.BNS`.

## Layout (little-endian)

Three variants, all starting with a u32 count N and with no signature:

| Variant | After the count | Sub-file i | Typical content |
|---|---|---|---|
| 1. Offsets | N × u32 offset from the start of the pack, padded to 16 bytes | `offset[i]` to `offset[i+1]` (the last one to the end) | Models with their textures and motions, nested packs |
| 2. Offset + size | N × (u32 offset, u32 size) | `offset[i]` to `offset[i] + size[i]` | 15,682 `EFB` files (effects?) in packs of up to 395 |
| 3. Sizes | N × u32 size, padded to 16 bytes | One after the other from the end of the table, each aligned to 16 bytes; the last one ends with the pack | `TMD2` descriptors of the battlefields |

Two equal offsets (variant 1) or a size of 0 (variants 2 and 3) mean an empty sub-file.

## Detecting a pack

There is no signature, so `tools/pack.py` accepts a blob as a pack only if all of these hold:

- variant 1: 0 < N < 20,000 and the offset table fits in the blob;
- the first offset falls right after the table (allowing for padding to 16 bytes, plus 16);
- offsets are 4-byte aligned, never decrease, and the last one is inside the blob;
- the blob does not start with a known file signature (`TIM2`, `TMD2`...).

- variant 2: entries inside the blob, in order and without overlap, the first one right after the table;
- variant 3: the aligned sizes must add up exactly to the size of the blob (or end in its padding).

Check of the rules: the 16,036 TIM2 textures found through all three variants convert without a
single error, which would not happen if sub-file boundaries were wrong. With the three variants,
`LINKDATA.BNS` opens into **95,654 leaf files**.

## Leaves in LINKDATA.BNS (by size)

| Leaf format | Count | Size | Share | Status |
|---|---:|---:|---:|---|
| `TIM2` textures | 16,036 | 205 MB | 36.6% | ✅ [TIM2.md](TIM2.md) |
| `TMD2` (static scene objects) | 26,623 | 97 MB | 17.3% | ✅ [TMD2.md](TMD2.md) |
| Battlefield pieces (`00 C0 04 66`) | 186 | 59 MB | 10.4% | to study |
| `PS2 ` models | 476 | 51 MB | 9.1% | ✅ [PS2MODEL.md](PS2MODEL.md) |
| Motions (`51 00 00 00`) | 10,714 | 46 MB | 8.2% | ✅ [MOTION.md](MOTION.md) |
| Starting `10 00 00 00 00 00 01 06` | 447 | 26 MB | 4.6% | to study |
| `EFB` | 15,682 | 24 MB | 4.3% | to study |
| Starting with zeros | 2,051 | 24 MB | 4.3% | to study |
| `tm3 ` | 176 | 13 MB | 2.2% | to study |
| `ipu2` (PS2 IPU images) | 2 | 8 MB | 1.4% | to study |
| Small tables (count + fixed-size records) and others | | ~7 MB | ~1% | to study |

These leaf formats are the next targets.
