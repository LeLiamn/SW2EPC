# Battlefield layout files (starting `00 C0 04 66`)

**Status: in progress.** Role identified, structure partly understood.

There are **186 files** (59 MB), each in its own pack together with two `TMD2` objects
([TMD2.md](TMD2.md)) and one `TIM2` texture: `[layout, TMD2, TMD2, TIM2]`. The texture is a **top-down
map of a battlefield** (forest, rivers, paths, cleared base areas), which tells what these files are:
the layout data of the battlefields (grid, zones, navigation, heights...). 124 of them are exactly
150,608 bytes; the others range up to 902,720 bytes.

## What holds for all 186 files

- The file starts with a short VIF prologue (`UNPACK V2-8`, `UNPACK V4-32`, `UNPACK V3-16`, `MSCNT`):
  the first bytes are the command `00 C0 04 66`.
- At 0x98, three u32 offsets split the rest of the file into sections. In all 186 files they are in
  increasing order and inside the file; section 2 (between the first two offsets) is always a whole
  number of 4-byte entries.

## Observed in file 2300.0 (858,656 bytes)

| Range | Content |
|---|---|
| 0x114–0x76C60 | 24,311 records of 20 bytes (u16, u16, −1, 0x2000, 0x40, 0) at the start: cells? This record size does not hold in most other files |
| 0x76C60–0xCCD50 | 88,124 pairs of small u16 values |
| 0xCCD50–0xCCDB0 | 96 bytes of `00 / 7F / FF` patterns (directions? masks?) |
| 0xCCDB0–end | floats (44, 68, 84, 128...): heights or ranges? |

## The common small variant (124 files of 150,608 bytes)

A table at 0x80 gives section offsets: 272, 288, 30,304, 60,320, 90,336, 120,352, 150,368, then two
more near the end. Between 288 and 150,368 there are **five sections of exactly 30,016 bytes**: five
same-sized layers, typical of stacked grids (height, ground type, zones...?). These 124 files are 96%
identical to each other: mostly default values (65535 = none), so they look like nearly empty
layouts or per-battle variants of a shared base.

The large files use the same table position but a different layout (272, zeros, then offsets near
the end of the file), and their sections do not split into regular grids.

## Next steps

Decoding the meaning of the sections needs either the game code that reads them, or a comparison
with the minimap (for example looking for a grid whose cells match the forest/river/path areas).
