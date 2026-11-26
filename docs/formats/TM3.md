# tm3: textures as ready-made GS packets

**Status: understood.** Tool: `tools/tm3.py` (one PNG per palette).

There are **176 tm3 files** (12.5 MB), often next to the model they belong to (pack 1412 holds the
samurai model, his motion and his tm3 texture). **All 176 convert** (1,077 PNG). Unlike TIM2, a tm3 is
not a picture format but **a packet ready to be sent to the PS2's Graphics Synthesizer**, which is why
it has its own layout.

## Layout (little-endian)

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `tm3 ` |
| 0x04 | u32 | Width |
| 0x08 | u32 | Height (0 in palette-only files) |
| 0x0C | u32 | Height × 16 + 8 |
| 0x10 | u32 | 1, 7 or 10 |
| 0x14 | u32 | 32 or 16 |
| 0x18 | u32 | 16 |
| 0x2C | u32 | A GS register value (`0x50......`) |
| 0x30 | | GS packet |

The packet is a chain of GIF tags, separated by DMA tags (a quadword whose low 64 bits are zero):

1. GIF tag PACKED with A+D register writes: `TEXFLUSH` (0x3F), `BITBLTBUF` (0x50: destination and
   pixel format), `TRXPOS` (0x51), `TRXREG` (0x52: width, height), `TRXDIR` (0x53);
2. GIF tag IMAGE with the pixels: an **8-bit indexed image** (pixel format `PSMT8`, 0x13), stored in
   plain row order;
3. the same again for the **palettes**: format `PSMCT32` (0x00), uploaded as 16×16 blocks of 256
   colours each; a 32×16 upload holds two palettes side by side. Each palette is in CSM1 order (entries
   8–15 and 16–23 swapped in every block of 32, as in [TIM2.md](TIM2.md)); alpha 0x80 = opaque.

The packet ends exactly at the end of the file in all 176 files.

## Several palettes

A texture can carry two or more palettes, and **different parts of the texture use different
palettes**: in the samurai's texture, palette 0 renders the face and skin correctly and palette 1 the
lacquered armour, belts and clan crest. The model's render batches pick the palette, so the tool
writes one PNG per palette. Two files hold only palettes (7 of them): colour variants for a texture
stored elsewhere.

| Image | Palettes | Files |
|---|---|---:|
| 256 × 384 | 32 × 16 (2) | 56 |
| 256 × 192 | 32 × 16 (2) | 56 |
| 256 × 256 or 256 × 128 | 16 × 16 + 16 × 16 (2) | 37 |
| 256 × 256 or 256 × 128 | 32 × 16 + 32 × 16 (4) | 24 |
