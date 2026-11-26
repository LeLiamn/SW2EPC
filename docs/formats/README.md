# Samurai Warriors 2: Empires file formats

Each file type, identified by its signature (first bytes), then documented on its own page as it
gets understood. All game data is inside the three [LINKDATA](LINKDATA.md) containers.

| Format | Where | Count | Signature | What it is | Status |
|---|---|---:|---|---|---|
| LINKDATA | `LINKDATA.ANS/.BNS/.CNS`, nested in BNS | 3 + 36 | `59 3B 03 00` | Numbered containers, no names. [LINKDATA.md](LINKDATA.md) | ✅ container understood, extraction tool |
| Pack | BNS, nested | many | none (u32 count + offsets) | Koei's offset-table archives, up to 3 levels deep. [PACK.md](PACK.md) | ✅ understood, extraction tool |
| TIM2 | BNS, inside containers and packs | 16,027 | `TIM2` | Textures, standard Sony format. [TIM2.md](TIM2.md) | ✅ understood, PNG export |
| PSS movies | CNS | 21 | `00 00 01 BA` | MPEG-2 video + stereo SPU ADPCM + Dolby Digital 5.1 (byte-swapped). [PSS.md](PSS.md) | ✅ understood, MKV export |
| Music streams | ANS | 105 | `00 08 00 00` | Stereo 48 kHz SPU ADPCM, 2 h 46 min with loop points. [ANS.md](ANS.md) | ✅ understood, WAV export |
| PAC0 | BNS | 847 | `PAC0` | Archives? | 🔴 to study |
| `PS2 ` models | BNS, in packs | 476 | `PS2 ` | 3D models: skeleton + skinned VIF/GIF vertex batches (characters, soldiers, weapons). 455 fully decoded, 21 node-less variant left. [PS2MODEL.md](PS2MODEL.md) | ✅ understood, OBJ export in bind pose |
| `tm3 ` | BNS | 176 | `tm3 ` | Textures stored as ready-made GS upload packets: 8-bit image + several palettes. [TM3.md](TM3.md) | ✅ understood, PNG export |
| `EFB` | BNS, in packs | 15,682 | `EFB\0` | Visual effects: layers of two fixed-size block types. [EFB.md](EFB.md) | 🟡 structure known |
| `TMD2` | BNS, in packs | 26,623 | `TMD2` + version `0060` | Static scene objects of the battlefields: VIF batches of UVs, colours, positions, normals. All parse. [TMD2.md](TMD2.md) | ✅ understood, OBJ export |
| `ipu2` | BNS | 2 | `ipu2` | PS2 IPU images | 🔴 to study |
| Motions | BNS, in packs | 10,714 | `51 00 00 00` | Animations: per node and component, cubic curve keys. 10,641 of 10,714 read exactly; poses a model. [MOTION.md](MOTION.md) | ✅ understood, posing tool |
| Battlefield layouts | BNS, in packs | 186 | `00 C0 04 66` | Layout data of the battlefields, packed with their minimap. Sections partly mapped. [BATTLEFIELD.md](BATTLEFIELD.md) | 🟡 in progress |
| Events | BNS | 303 | `10 00 00 00 00 00 01 06` | In-engine cutscenes: command chain + 2,842 motions (97.8% of the bytes). [EVENT.md](EVENT.md) | 🟡 motions done, commands to study |
| Sound bank | BNS entry 1384 + small raw files | 1,610 sounds | none (raw SPU ADPCM) | Sound effects, split on ADPCM end/loop flags, 32,000 Hz (probable). [SOUNDBANK.md](SOUNDBANK.md) | ✅ understood, WAV export |
| Other leaves | BNS | ~13,000 | none | Geometry packets (`00 C0 04 66`), `51 00 00 00` files, tables... 278 MB: see [PACK.md](PACK.md) | 🔴 to study |

Legend: ✅ understood · 🟢 standard format, already documented elsewhere · 🟡 in progress · 🔴 unknown
