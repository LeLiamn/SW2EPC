# Event files: in-engine cutscenes

**Status: structure understood; the motions inside are decoded, the commands are not yet.**
Tool: `tools/event.py` (lists the commands and the motions, checks every file).

There are **303 event files** (26 MB) in `LINKDATA.BNS`. Each one is a chain of command records
followed by the **motions** the cutscene plays (in the [motion format](MOTION.md)). The motions make
up **97.8% of the bytes**: 2,842 motions in all.

All values are little-endian.

## Command chain

Records follow each other from offset 0; each starts with the offset of the next one:

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | Offset of the next record (0 for the last one) |
| 0x04 | u32 | Command: the high 16 bits look like a command family (`0x0601`, `0x0402`, `0x0403`, `0x0801`, `0x1303`, `0x0406`, `0x1306`...) |
| 0x08 | ... | Parameters up to the next record (small integers, floats such as 905.0, 18500.0, 32000.0) |

The first record is always `10 00 00 00 00 00 01 06`, which identifies these files. Checks: in all
303 files the chain is in order and ends with a 0 link: 16,286 commands in all.

## Motions

After the chain come the motions, each preceded by a 32-bit value: −1 for 2,612 of them, 1, 2 or 4
for the others (an actor number?). They all parse with the motion reader.

## Open questions

- The meaning of each command family (camera moves, actor placement, sounds, subtitles...).
- What the value before each motion selects, and how motions are bound to models.
