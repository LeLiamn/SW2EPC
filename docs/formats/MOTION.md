# Motions (files starting `51 00 00 00`)

**Status: in progress.** Identified as animations; the key layout is only partly understood.

`LINKDATA.BNS` holds **10,714 motion files** (46 MB), grouped by the hundred in packs (for example
152 in pack 1612), from 56 bytes to 67 KB.

## Header (16 bytes, little-endian)

| Offset | Type | Values seen | Meaning (hypothesis) |
|---:|---|---|---|
| 0x00 | u32 | 81 (`0x51`) | Format id |
| 0x04 | u32 | 87, 147... | Number of tracks? (87 = 29 × 3, 147 = 49 × 3) |
| 0x08 | u32 | 1, 8, 30, 33, 60... | Length in frames (60 = two seconds at 30 fps?) |
| 0x0C | u32 | `0x42000`, `0x4A000` | Flags |

## Data (partial)

The data is mostly 32-bit floats. Frame numbers appear as whole floats (0, 4, 39, 51, 60) and the last
frame always closes a run of values, so the data is made of **tracks of keys**, each key ending on a
frame number:

```
track: u32 type (0 for the first tracks)
       key: f32 end frame, f32 × 4 values     (repeated until the end frame = length)
```

This reading holds for the first three tracks of motion `1074.0.0` (for example a constant track is
a single key at frame 60 holding (3.012, −6.553, 3.587, −112.131), close to the root height of the
characters, −117.5). It breaks on the fourth track: other track types store a different number of
values per key.

## Next step

The game's `MotionManager.c` (its name survives in the executable) reads these files. Finding and
reading that code is the reliable way to finish the format, rather than guessing more track types.
