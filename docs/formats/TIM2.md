# TIM2: textures

**Status: understood (standard Sony format).** Tool: `tools/tim2.py` (converts to PNG, no
dependencies).

TIM2 is the standard texture format of the PS2 SDK. The game has **16,027 TIM2 textures** in
`LINKDATA.BNS` (205 MB): 500 as direct entries, the rest inside nested LINKDATA containers and
[packs](PACK.md). All of them convert without error.

## What the game uses

The 500 top-level files are version 4, with one picture each and no mipmaps:

| Image type | Bits per pixel | Count (top level) | Palette |
|---|---:|---:|---|
| 5 | 8 (indexed) | 353 | 256 colours, 32-bit RGBA, CSM1 order |
| 4 | 4 (indexed) | 147 | 16 colours, 32-bit RGBA |

Some textures carry several palettes (for example 32 colours = 2 palettes of 16, or 512 colours =
2 palettes of 256): the same image in several colour variants, such as the battle HUD in different
colours. `tools/tim2.py --iso` writes one PNG per palette (`_p0`, `_p1`...).

## Layout (little-endian)

File header (16 bytes): `TIM2`, u8 version, u8 alignment format (0: 16-byte, 1: 128-byte), u16
number of pictures, 8 bytes of padding.

Picture header (48 bytes here):

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | Total size of the picture (header + image + palette) |
| 0x04 | u32 | Palette size in bytes |
| 0x08 | u32 | Image size in bytes |
| 0x0C | u16 | Header size |
| 0x0E | u16 | Number of palette colours |
| 0x10 | u8 | Picture format |
| 0x11 | u8 | Number of mipmaps |
| 0x12 | u8 | Palette type: low bits = colour format (1: 16-bit, 2: 24-bit, 3: 32-bit), bit 7 = CSM2 (linear) order |
| 0x13 | u8 | Image type (1: 16-bit, 2: 24-bit, 3: 32-bit, 4: 4-bit indexed, 5: 8-bit indexed) |
| 0x14 | u16 | Width |
| 0x16 | u16 | Height |
| 0x18 | u64 × 2, u32 × 2 | GS registers (TEX0, TEX1, TEXA, TEXCLUT) |

Then the image data, then the palette.

## Details that matter for a correct conversion

- **Alpha**: the PS2 uses 0x80 for fully opaque; values are doubled (capped at 255).
- **CSM1 palette order**: in 256-colour palettes, within each block of 32 entries, entries 8–15 and
  16–23 are swapped. Without the fix the colours come out banded.
- **4-bit pixels**: the low nibble is the left pixel.

The format is publicly documented by the PS2 homebrew and modding community; this page only records
what this game uses.
