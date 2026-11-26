# LINKDATA containers (`LINKDATA.ANS`, `.BNS`, `.CNS`)

**Status: container format understood.** Tool: `tools/linkdata.py` (lists and extracts straight from
the disc image). The formats of the files inside are still to study.

All the game's data lives in three LINKDATA files. They have **no file names**: entries are numbered,
and the game asks for them by index. Checked on all three: 3,629 entries, every entry inside its
container, no overlaps, 99.2–100% of each container covered.

All integers are little-endian.

## Header (16 bytes)

| Offset | Type | Value | Meaning |
|---:|---|---|---|
| 0x00 | u32 | `0x00033B59` | Signature |
| 0x04 | u32 | | Number of entries |
| 0x08 | u32 | `0x800` | Alignment unit of the entry offsets (one DVD sector) |
| 0x0C | u32 | 0 | |

## Entries (8 bytes each, from 0x10)

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | Offset of the entry, in alignment units (× 0x800) |
| 0x04 | u32 | Size in bytes |

## Contents

| Container | Entries | Size | Content (from the first bytes of each entry) |
|---|---:|---:|---|
| `LINKDATA.ANS` | 106 | 873 MB | One kind of file, header starting `00 08 00 00 80 BB 00 00 02 00 00 00`: a 0x800-byte header, 48000 (sample rate?), 2 (channels?). Probably the music streams |
| `LINKDATA.BNS` | 3,502 | 566 MB | Mixed: 847 `PAC0` archives, 500 `TIM2` textures (standard Sony format), 247 files starting `PS2 `, 36 nested LINKDATA containers, many files without a text signature |
| `LINKDATA.CNS` | 21 | 717 MB | 21 MPEG-2 program streams (`00 00 01 BA`): the movies |

Nested LINKDATA containers inside `BNS` use the same layout (offsets relative to the start of the
nested container).

## Related work

The Xbox 360 release uses LINKDATA files too, with separate `.IDX` index files
(`LINKDATA_BNS.IDX/LNK`), as documented by
[rbxrootx/samurai_warriors_2_empires_recomp](https://github.com/rbxrootx/samurai_warriors_2_empires_recomp).
On PS2 the index is at the start of each container.
