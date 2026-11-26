# Samurai Warriors 2: Empires file formats

Each file type, identified by its signature (first bytes), then documented on its own page as it
gets understood. All game data is inside the three [LINKDATA](LINKDATA.md) containers.

| Format | Where | Count | Signature | What it is | Status |
|---|---|---:|---|---|---|
| LINKDATA | `LINKDATA.ANS/.BNS/.CNS`, nested in BNS | 3 + 36 | `59 3B 03 00` | Numbered containers, no names. [LINKDATA.md](LINKDATA.md) | ✅ container understood, extraction tool |
| TIM2 | BNS | 500 | `TIM2` | Textures, standard Sony format | 🟢 standard format |
| MPEG-2 PS | CNS | 21 | `00 00 01 BA` | Movies, standard Sony PSS | 🟢 standard format |
| Audio streams | ANS | 106 | `00 08 00 00` | 48 kHz stereo streams? (music) | 🔴 to study |
| PAC0 | BNS | 847 | `PAC0` | Archives? | 🔴 to study |
| `PS2 ` | BNS | 247 | `PS2 ` | ? | 🔴 to study |
| Others | BNS | ~1,800 | none | Models, motions, scripts, text...? | 🔴 to study |

Legend: ✅ understood · 🟢 standard format, already documented elsewhere · 🟡 in progress · 🔴 unknown
