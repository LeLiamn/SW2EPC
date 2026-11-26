# Motions (files starting `51 00 00 00`)

**Status: understood.** Tool: `tools/motion.py` (lists tracks, checks every motion, poses a model at
any frame and exports it to OBJ / PNG).

`LINKDATA.BNS` holds **10,714 motion files** (46 MB), grouped in packs, often right next to the model
they animate (pack 1412 holds the samurai model `1412.1` and its motion `1412.2`). **10,641 parse
exactly** (to the last byte, or to zero padding below 16 bytes); 73 use a rarer track type or have a
few trailing bytes and are still to study.

Solved from the data alone: the track layout below makes 10,641 files end exactly, and 679,397 of
679,433 animated tracks end exactly on the motion's last frame.

All values are little-endian.

## Header (12 bytes)

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | `0x51`: format id |
| 0x04 | u32 | Number of tracks (87, 117, 147, 111...: depends on the skeleton) |
| 0x08 | u32 | Length in frames |

The tracks follow immediately (the first track header is at 0x0C).

## Tracks

Each track animates one component of one skeleton node. It starts with a u32 header:

| Bits | Meaning |
|---|---|
| 0–7 | Node index in the model's skeleton |
| 8–11 | Component: 0, 1, 2 = rotation x, y, z (radians); 3, 4, 5 = translation x, y, z; 9–15 rare, unknown |
| 13 (`0x2000`) | Constant track: values follow |
| 15 (`0x8000`) | Animated track: keys follow |
| 18–31 | Number of keys (or of values) |

Then:

- **Animated track**: N keys of 5 floats: end frame, then a, b, c, d. Key k covers the frames after
  key k−1 (or frame 0) up to its end frame, with value = a·t³ + b·t² + c·t + d, t going from 0 to 1
  over the segment. The last key always ends on the motion's last frame.
- **Constant track** with bit 13: N floats (always one in practice).
- **Constant track** without bit 13: no data, the value is 0.

Rotations (components 0–2) are animated on most nodes; translations (3–5) only on a few (the root
and the like), which is why they are about ten times rarer.

## Checks

- The layout above reads 10,641 of 10,714 files exactly.
- Consecutive cubic segments join with a median gap of 0.011 radian (0.6°): the export tool fitted
  each segment within a tolerance. Other readings of the four values (reversed polynomial, time in
  frames) give large jumps.
- Applying motion `1412.2` (114 frames) to the samurai `1412.1` gives coherent human poses, and
  frames 0 and 114 are identical: a looping animation.

## Open questions

- Components 9–15 and bit 12 (`0x1000`), used by 194 tracks.
- The 73 atypical files.
