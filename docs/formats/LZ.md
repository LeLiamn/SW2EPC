# LZ-compressed files

**Status: method 2 decoded** (the only one used by data still counted). Tool: `tools/lz.py`.

`SceneTitle.c` decompresses BNS entry 0005 with `func_00279FB0`: it allocates the size given in
the header and calls `func_00279F20`, which picks one of four methods (0-3) by the first word.

## Method 2 (`func_00279D40`)

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | u32 | method (2) |
| 0x04 | u32 | decompressed size |
| 0x08 | u32 | offset of the match stream (u16 tokens) |
| 0x0C | u32 | offset of the literal stream (bytes) |
| 0x10 | u64... | flag words, read from the top bit down |

For each flag: 1 copies the next literal byte; 0 reads a match token: low 12 bits = position in
the current 4 KB window of the output (1-based; when it is above the current position inside the
window, the previous window), high 4 bits = length − 3. A token with position 0 ends the data.

Entry 0005 decompresses to exactly the 1,253,648 bytes its header gives: a LINKDATA container of
TIM2 textures, the title screen's images.
