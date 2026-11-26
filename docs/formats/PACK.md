# Packs: Koei's offset-table archives

**Status: understood.** Tool: `tools/pack.py` (tree, statistics, extraction of the leaves).

Most entries of `LINKDATA.BNS` are not single files but **packs**: small archives with no signature
and no names, nested inside each other (up to 3 levels) and inside LINKDATA containers. Opening
LINKDATA containers and packs recursively gives **41,079 leaf files** in `LINKDATA.BNS`.

## Layout (little-endian)

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | Number of sub-files N |
| 0x04 | u32 × N | Offset of each sub-file, from the start of the pack |
| ... | | Padding to a 16-byte boundary, then the data |

Sub-file *i* runs from `offset[i]` to `offset[i+1]`; the last one runs to the end of the pack.
Two equal offsets mean an empty sub-file. Offsets are 16- or 32-byte aligned in practice.

## Detecting a pack

There is no signature, so `tools/pack.py` accepts a blob as a pack only if all of these hold:

- 0 < N < 20,000 and the offset table fits in the blob;
- the first offset falls right after the table (allowing for padding to 16 bytes, plus 16);
- offsets are 4-byte aligned, never decrease, and the last one is inside the blob;
- the blob does not start with a known file signature (`TIM2`, `TMD2`...).

Check of the rule: the 16,027 TIM2 textures it finds convert without a single error, which would
not happen if sub-file boundaries were wrong.

## Leaves in LINKDATA.BNS (by size)

| Leaf format | Count | Size | Share |
|---|---:|---:|---:|
| `TIM2` textures | 16,027 | 205 MB | 36.5% |
| Starting `00 C0 04 66` (VIF UNPACK command: GS geometry packets? models) | 186 | 59 MB | 10.4% |
| `PS2 ` | 476 | 51 MB | 9.1% |
| Starting `51 00 00 00` | 10,714 | 46 MB | 8.2% |
| Starting with a large count (e.g. `8B 01 00 00`) followed by a size-like table | ~300 | ~110 MB | ~20% |
| `tm3 ` | 176 | 13 MB | 2.2% |
| `TMD2` | 372 | 7 MB | 1.3% |
| `ipu2` (PS2 IPU images) | 2 | 8 MB | 1.4% |
| Others | | | |

These leaf formats are the next targets.
