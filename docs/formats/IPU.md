# IPU movies (`ipu2`)

**Status: decoded.** Tool: `tools/ipu.py` (to an `ipum` stream or, with FFmpeg, to a video).

Two files in LINKDATA.BNS: entry 0004 (256 x 192, 225 frames: an animated menu background) and
entry 0131 (512 x 384, 200 frames: an officer presentation, e.g. Ieyasu Tokugawa). They are made of
PS2 IPU frames: intra pictures coded like MPEG-1 I-frames, decoded by the PS2's image processing
unit. FFmpeg decodes these frames (its `ipu` decoder) once they are in its expected `ipum` layout.

## Layout

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `ipu2` |
| 0x04 | u32 | file size |
| 0x08 | u16 × 2 | width, height |
| 0x0C | u32 | number of frames N |
| 0x10 | N × (u32 offset, u32 size) | one entry per frame |

Frames follow the table (aligned to 16 bytes). Each frame starts with the IPU picture flags byte
(e.g. `0x60`: q-scale type 1, intra VLC format 1) and ends with the end code `00 00 01 B0`, then
zeros up to a 16-byte boundary. After the last frame: the sequence end code `00 00 01 B1` and zeros.

## Conversion

The `ipum` layout FFmpeg reads is `ipum`, u32 size, u16 width, u16 height, u32 frame count, then the
frames one after the other. The zero padding after each end code must be cut: FFmpeg splits frames
at the end code, and the zeros would become the first byte (the flags) of the next frame, which is
what made the decoder fail before ("ac-tex damaged"). With the padding cut, all 425 frames decode.
