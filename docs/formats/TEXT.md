# Text tables

**Status: decoded.** Tool: `tools/text.py` (prints a table's strings).

The game's English texts (system messages, battle messages with a voice number after `@`, event
dialogue lines...) are stored in small tables, in three layouts. Each is recognised only when every
offset points at a printable, NUL-terminated string inside the table:

| Layout | Content |
|---|---|
| count + offsets | u32 count, `count` u32 offsets from the table's start, then the strings |
| offsets only | u32 offsets (the first one gives the size of the offset table), then the strings |
| (offset, length) pairs | u32 pairs (the first offset gives the size of the pair table), then the texts |

Examples: `sc_sysmsg.c`'s entry 0050 (system messages: 195 strings, then battle messages such as
"Our luck has run out... The allied commander... has retreated!@0171"), the text parts of entry 0128.

## Event dialogues (entry 0172, `emp_ev_still.c`)

A pack of 348 records (`count`, then `(offset, size)` pairs). Each record is itself such a pack of
3 parts: a table of offsets (relocated by the game when it loads the entry, `func_0032B7B0`),
16 bytes, and the lines: an offset table, then lines made of a length, the text ("Yes!",
"Okay.", "Alright!"...) and a voice number. `func_0032B730` picks record `n − 26` for event `n`.
Checked by `event.check_dialogues()` on all 348 records.
