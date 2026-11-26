# LINKDATA.ANS: music streams

**Status: understood.** Tool: `tools/ans.py` (decodes to WAV, no dependencies).

`LINKDATA.ANS` holds 106 entries: **105 stereo music streams** (2 h 46 min in total, about two minutes
each, every one with a loop point) and one empty entry (entry 105, all zeros). The audio is standard
PS2 SPU ADPCM, the same codec as Sony's VAG files.

## Header (0x800 bytes, little-endian)

| Offset | Type | Value | Meaning |
|---:|---|---|---|
| 0x00 | u32 | 2048 | Header size; the ADPCM data starts here |
| 0x04 | u32 | 48000 | Sample rate (Hz) |
| 0x08 | u32 | 2 | Channels |
| 0x0C | u32 | 16 | Channel interleave in bytes (one ADPCM frame) |
| 0x10 | u32 | | Number of ADPCM frames per channel (× 28 = samples) |
| 0x14 | u32 | | Loop start, in frames |
| 0x18 | | 0 | Rest of the header is zero |

## Data

Frames of 16 bytes alternate between channels (left, right, left...). Each frame is 2 header bytes
(shift and filter in byte 0, flags in byte 1) and 14 bytes of 4-bit samples = 28 samples, decoded
with the standard SPU coefficients (0,0), (60,0), (115,-52), (98,-55), (122,-60) / 64.

## How the interleave was checked

Decoding with an interleave of 16 bytes gives left/right channels with a correlation of 0.58 and no
clipping; 256, 2048, 4096 or 8192 bytes give a correlation around 0 and clipped samples. The frame
count field matches the file size exactly (frames × 16 × 2 + 0x800, rounded up to a sector).
