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
| `PS2 ` models | BNS, in packs | 476 | `PS2 ` | 3D models: skeleton + VIF/GIF vertex batches. Rigid models export correctly; skinned ones not posed yet. [PS2MODEL.md](PS2MODEL.md) | 🟡 in progress, OBJ export |
| `tm3 ` | BNS | 176 | `tm3 ` | ? (texture-like name) | 🔴 to study |
| `TMD2` | BNS | 372 | `TMD2` + version `0060` | Battlefield piece descriptors (world coordinates), two per piece | 🔴 to study |
| `ipu2` | BNS | 2 | `ipu2` | PS2 IPU images | 🔴 to study |
| Other leaves | BNS | ~24,000 | none | Geometry packets (`00 C0 04 66`), `51 00 00 00` files, tables... 278 MB: see [PACK.md](PACK.md) | 🔴 to study |

Legend: ✅ understood · 🟢 standard format, already documented elsewhere · 🟡 in progress · 🔴 unknown
