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

## Identified, not decoded yet

| Entry | Size | Read by | What it is |
|---|---:|---|---|
| 0005 | 615 KB | `SceneTitle.c` (`func_00279FB0` turns it into the title screen's data) | title screen data |
| 0050 | 197 KB | `sc_sysmsg.c` | system messages: header with offsets of string tables |
| 0160-0171 | 68 KB each | `emp_cq_main.c` (entry 0x0AA goes to the Empire set-up's work object) | Empire mode tables |
| 0172 | 579 KB | `emp_ev_still.c` | event dialogues: 348 records, each with lines of text and voice numbers |
| 0173-0199 | 2.2 MB | `StateBattleInitialize.c` (entry 0xAD + scenario), in place of the officers' entries 3080+ | battle event scripts (event command chains) |
| 1309 | 100 KB | `SecretSorts.c` | 314 records of 0x140 bytes; the one matching a player's choice is copied to `0x0076E9C0` |
| 1385 | 156 KB | `SeManager.c` (entry 0x569) | sound effect table |
