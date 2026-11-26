# Samurai Warriors 2: Empires file formats

Each file type, identified by its signature (first bytes), then documented on its own page as it
gets understood. All game data is inside the three [LINKDATA](LINKDATA.md) containers.

| Format | Where | Count | Signature | What it is | Status |
|---|---|---:|---|---|---|
| LINKDATA | `LINKDATA.ANS/.BNS/.CNS`, nested in BNS | 3 + 36 | `59 3B 03 00` | Numbered containers, no names. [LINKDATA.md](LINKDATA.md) | ✅ container understood, extraction tool |
| Pack | BNS, nested | many | none (u32 count + offsets) | Koei's offset-table archives, up to 3 levels deep. [PACK.md](PACK.md) | ✅ understood, extraction tool |
| TIM2 | BNS, inside containers and packs | 16,027 | `TIM2` | Textures, standard Sony format. [TIM2.md](TIM2.md) | ✅ understood, PNG export |
| MPEG-2 PS | CNS | 21 | `00 00 01 BA` | Movies, standard Sony PSS | 🟢 standard format |
| Audio streams | ANS | 106 | `00 08 00 00` | 48 kHz stereo streams? (music) | 🔴 to study |
| PAC0 | BNS | 847 | `PAC0` | Archives? | 🔴 to study |
| `PS2 ` | BNS | 247 | `PS2 ` | ? | 🔴 to study |
| `tm3 ` | BNS | 176 | `tm3 ` | ? (texture-like name) | 🔴 to study |
| `TMD2` | BNS | 372 | `TMD2` | ? (model?) | 🔴 to study |
| `ipu2` | BNS | 2 | `ipu2` | PS2 IPU images | 🔴 to study |
| Other leaves | BNS | ~24,000 | none | Geometry packets (`00 C0 04 66`), `51 00 00 00` files, tables... 278 MB: see [PACK.md](PACK.md) | 🔴 to study |

Legend: ✅ understood · 🟢 standard format, already documented elsewhere · 🟡 in progress · 🔴 unknown
