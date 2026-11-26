# Event files: in-engine cutscenes

**Status: decoded** (command records with typed parameters, motions).
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

## Command records (from the game code, ev_main.c)

The interpreter (`func_001DA9A0`, `func_001DADC0`) walks the records from the script's base; a
record:

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | offset of the next record from the script's start |
| 0x04 | u8 | command (0xFF = end of the script) |
| 0x05 | u8 | sub-command |
| 0x06 | u8 | number of parameters n |
| 0x07 | n × u8 | type of each parameter |
| 0x07 + n | u8 | offset of the first value, from +0x07 |
| 0x08 + n | n × u8 | step from each value to the next (0 after the last) |
| ... | | the values |

Parameter types (`func_001D6BD0` reads one value): 0 s8, 1 s16, 2 s32, 3 u8, 4 u16, 5 u32, 6 f32,
7 and 8 u32; the other codes are 2-byte values except 13 and 15 (4 bytes), as the steps show.
Checked by `event.check_commands()`: in all 303 files every record holds exactly its values (then
zeros). 60 different (command, sub-command) pairs are used.

## Scenario scripts (LINKDATA.BNS entries 0173-0199)

13 scripts of the scenario battles, loaded by `StateBattleInitialize.c` (entry 0xAD + scenario) in
place of the officers' event entries. They use an older layout of the same records: the first word
is the record's number instead of a link, the bytes after the types repeat n instead of giving the
offset and steps, and the values follow the header (8 + 2n bytes) with natural alignment, records
aligned to 4. Since the game's walker reads links and offsets, it could not run them as they are:
they look like data left from an older tool. Each script ends with command 0xFF, then come its
motions, then zero padding and a −1 word. `event.old_script()` reads them.

## Open questions

- The meaning of each command (camera moves, actor placement, sounds, subtitles...).
- What the value before each motion selects, and how motions are bound to models.
