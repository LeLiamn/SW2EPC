# SW2EPC

[![Decompiled](https://decompilati.onl/badge/samurai-warriors-2-empire.svg)](https://decompilati.onl/projects/samurai-warriors-2-empire)
[![Matching](https://decompilati.onl/badge/samurai-warriors-2-empire/matching.svg)](https://decompilati.onl/projects/samurai-warriors-2-empire)
[![Data](https://decompilati.onl/badge/samurai-warriors-2-empire/data.svg)](https://decompilati.onl/projects/samurai-warriors-2-empire)

A preservation project for **Samurai Warriors 2: Empires** (PS2, Omega Force / Koei, 2006):
documentation of its file formats, extraction tools, and a decompilation of the PS2 executable.

**This repository contains no game files.** You need your own disc and an image made from it.

## Status

| Area | State |
|---|---|
| Disc image | Europe SLES-54624 v1.00, verified against [Redump #17102](http://redump.org/disc/17102/) |
| Executable | Analysed: no symbols, CodeWarrior compiler, 70 original source file names recovered |
| Data containers (`LINKDATA`) | Fully understood, all 3,629 entries extractable |
| Packs (nested archives) | Understood: 41,079 leaf files in `LINKDATA.BNS` |
| Textures (TIM2) | 16,027 textures, all convertible to PNG |
| Music (`LINKDATA.ANS`) | 105 tracks (2 h 46 min), decoded to WAV |
| Movies (`LINKDATA.CNS`) | 21 movies exported to MKV with stereo and Dolby Digital 5.1 tracks |
| 3D models (`PS2 `) | 476 models export to OBJ; rigid ones (weapons) are correct, characters not posed by their skeleton yet |
| Other formats inside | Signatures identified (battlefield pieces, `TMD2`, `tm3`...) |
| Decompilation | Not started |

## Related projects

- [rbxrootx/samurai_warriors_2_empires_recomp](https://github.com/rbxrootx/samurai_warriors_2_empires_recomp):
  a static recompilation of the **Xbox 360** release with ReXGlue, playable on PC. SW2EPC works on
  the **PS2** release, which is a different executable and engine build.

## Getting started

1. Make an image of your own disc and put it in `Iso/` (ignored by git).
2. Check it against [Redump](http://redump.org/) with `py tools/hash_image.py "Iso/<image>.iso"`.
3. First look at the disc and the executable: `py tools/disc_info.py "Iso/<image>.iso" --extract-exe`.

## Tools (Python 3, no dependencies)

| Tool | Purpose |
|---|---|
| `tools/hash_image.py` | CRC32, MD5 and SHA-1 of an image, to compare with Redump |
| `tools/iso_list.py` | List the ISO with file positions, including the second layer of a DVD-9 |
| `tools/disc_info.py` | Boot executable (from `SYSTEM.CNF`), its hashes, compiler and code size, largest files |
| `tools/linkdata.py` | List and extract the LINKDATA containers straight from the disc image |
| `tools/pack.py` | Open Koei's nested offset-table packs: tree, statistics, extraction |
| `tools/ans.py` | Decode the music streams (`LINKDATA.ANS`) to WAV |
| `tools/pss.py` | Export the movies (`LINKDATA.CNS`) to MKV with both audio tracks (needs ffmpeg) |
| `tools/ps2model.py` | Export the 3D models to OBJ, with a PNG preview |
| `tools/tim2.py` | Convert TIM2 textures to PNG, every texture of the disc at once |
| `tools/elf_info.py` | Sections, symbols, compiler and code size of an executable |
| `tools/find_strings.py` | Readable strings of a binary, with a report of file names |
| `tools/mips_disasm.py` | Minimal MIPS (R5900) disassembler for quick looks |
| `tools/progress.py` | Build a progress report in the decompilati.onl format |

## Documentation

- [docs/disc.md](docs/disc.md): the disc
- [docs/executable.md](docs/executable.md): the `SLES_546.24` executable
- [docs/formats/](docs/formats/README.md): file formats

## Contributing rules

- Never commit game files: no executable, no extracted assets, no disc image. Everyone builds from
  their own disc.
- No copy-protection circumvention, and no links to game files or BIOS downloads.

## Legal

This project only distributes original code and documentation. It contains no game code, assets or
disc images, and does not circumvent any copy protection. Samurai Warriors 2: Empires is © Koei Tecmo.
