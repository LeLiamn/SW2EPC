# Smaller files of LINKDATA.BNS

Files without a signature of their own, identified by the code that loads them (the loader
`func_001026D0` is given the source file name and line, which names the reader).

## Decoded

### Sound bank headers (entry 1383, `SeManager.c` side)

203 Sony "HD" headers, the descriptions of the ADPCM sound banks ([SOUNDBANK.md](SOUNDBANK.md)).
Each header is a run of `IECS` chunks (tag stored reversed: `IECSsreV` = Vers, then Head, Vagi,
Smpl, Sset, Prog); the Head chunk gives the header size (+0x0C) and the size of its bank body
(+0x10). Headers follow each other in groups; each group is padded with zeros to a 2048-byte
boundary. Checked by `soundbank.parse_headers()`: all 203 headers, every chunk in place, the
padding all zeros, down to the end of the entry.

### Memory-card icon (entry 0061, `saveload.c`)

The standard PS2 3D save icon: header (version 0x10000, 1 shape, texture type 7 = uncompressed,
1.0, 1,548 vertices), the vertices (per vertex: one s16 x/y/z/w position per shape, a normal, UVs,
a colour), the animation (1 frame, 1 key), then the 128 x 128 16-bit texture, which ends exactly at
the end of the file. `tools/ps2icon.py` checks it and exports the texture to PNG.

### Game state tables (entries 0160-0171, 1309)

- **0160-0170** (`emp_cq_main.c`, `func_0030CE90` loads entry `0xA0 + n`): the starting state of an
  Empire game, 68,240 bytes = three blocks of 500, 3,000 and 64,740 bytes that `func_0030CD80`
  copies whole into the game state (`0x007A3B98`, `0x007A3B9C`, `0x007A3BA0`), then rebuilds the
  officers' derived values.
- **0171** (`emp_ev_predata.c`): 391 records of 0x3C bytes (`func_0032F040` returns record n).
- **1309** (`SecretSorts.c`): 314 records of 0x140 bytes; the one matching a player's choice is
  copied to `0x0076E9C0`.

The fields of these records are the game state's own structures, named as the code using them is
decompiled.

### Officer quotes (entries 0200-0226)

An offset table (the first offset gives its size) of records; each record is two u32, then a text
table ("Your skill on the battlefield is worthy of...", each line ending with `@` and a voice
number). See [TEXT.md](TEXT.md); `text.record_tables()` checks them.

## Identified, not decoded yet

| Entry | Size | Read by | What it is |
|---|---:|---|---|
| 1385 | 156 KB | `SeManager.c` (entry 0x569) | sound effect table |
