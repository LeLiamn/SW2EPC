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

### Battlefield field data and lighting (entries 2859-3078)

- **2859-3044** (`Field.c`, entry from a table at `0x00424F30`): a pack of 3 or 4 parts:
  0x40-byte area records (u16 +0x1E = a record of part 1), 0x10-byte records, 0x10-byte records,
  8-byte records. `battlefield.parse_field()`.
- **3045-3078** (`StgAmbient.c`, entry `0xBE5 + battlefield`, or `0xC00`-`0xC06`): 576 bytes of
  lighting, 36 vectors of 4 floats (light position and direction, colours as 255.0, factors).

### Smaller tables (checked against the code that reads them)

| Entry | Read by | Layout |
|---|---|---|
| 0051 | `sc_ubase.c` | u32 count + 0x2C-byte records |
| 0052 | `Stage.c` | pack whose parts are relocated; part 2 to `func_0027F6D0` |
| 0053 | `sc_ctrl.c` | u32 count + 100-byte records: the battlefield table the code reads at `0x005BA694` |
| 0062 | `RelayCamera.c` | pack |
| 0063 | `ObjAction.c` | 31 (offset, size) parts, each given to a handler of a table at `0x0043FE40` |
| 1194 | `emp_war_fix.c` | pack of 4 relocated parts |
| 1195 | `emp_FldBase.c` | 0x78 bytes per scenario (20 entries of 6 bytes) |
| 1197-1281 | `emp_sc.c` | Empire scenario tables (see EVENT.md / `event.check_emp_sc`) |
| 1282-1308 | `MiniMap.c` | minimaps: a 32 x 32 zone grid and the TIM2 map image (entry from `0x0040D630`) |
| 1310 | `SecretSorts.c` | 0x30-byte records |
| 1385 | `SeManager.c` | u32 count, u32, then 20-byte records: position and size (in sectors) of each sound stream |
| 1386 | `ModelManager.c` | 0xA0-byte records |
| 1387, 1388 | `Weapon.c` | 0x20- and 0x30-byte records |
| 1390 | `Bullet.c` | 16-byte header (u32 count at +4) + 0x48-byte records |
| 2030 | | CLT2 palettes (TIM2 layout without an image), `tim2.is_clt2()` |
| 3079 | `SecretsScene.c` | pack |
| 3262-3387 | `ev_message.c` | PAC0 files behind a 16-byte header (`pac0.parse_wrapped()`) |
| 3388-3458 | `MovieTelop.c` | movie subtitles: count, (start, end) frame pairs, lines (`text.telop()`) |

The record fields of these tables are the game's own structures; they get their names as the code
reading them is decompiled.
