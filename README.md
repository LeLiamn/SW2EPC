# SW2EPC

[![Decompiled](progress/badges/decompiled.svg)](progress/PROGRESS.md)
[![Matching](progress/badges/matching.svg)](progress/PROGRESS.md)
[![Functions](progress/badges/functions.svg)](progress/PROGRESS.md)
[![Data](progress/badges/data.svg)](progress/PROGRESS.md)

Progress is tracked in this repository ([progress/PROGRESS.md](progress/PROGRESS.md), with its
history) and also sent to [decompilati.onl](https://decompilati.onl/projects/samurai-warriors-2-empire).

A preservation project for **Samurai Warriors 2: Empires** (PS2, Omega Force / Koei, 2006):
documentation of its file formats, extraction tools, and a decompilation of the PS2 executable,
with a native PC port as the long-term goal.

**This repository contains no game files.** You need your own disc and an image made from it.

## Status

| Area | State |
|---|---|
| Disc image | Europe SLES-54624 v1.00, verified against [Redump #17102](http://redump.org/disc/17102/) |
| Executable | Analysed: no symbols, CodeWarrior compiler, 70 original source file names recovered |
| Data containers (`LINKDATA`) | Fully understood, all 3,629 entries extractable |
| Packs (nested archives) | Understood (three kinds): 95,654 leaf files in `LINKDATA.BNS` |
| Textures (TIM2) | 16,036 textures, all convertible to PNG |
| Music (`LINKDATA.ANS`) | 105 tracks (2 h 46 min), decoded to WAV |
| Movies (`LINKDATA.CNS`) | 21 movies exported to MKV with stereo and Dolby Digital 5.1 tracks |
| 3D models (`PS2 `) | Skeleton and skinning decoded: characters, soldiers and weapons export to OBJ in bind pose (455 of 476) |
| Animations (10,714 motions) | Format solved from the data: 10,641 read exactly and pose the characters |
| Scene objects (26,623 TMD2) | Geometry decoded; whole battlefield packs export to OBJ |
| tm3 textures (176) | All convert to PNG, one image per palette (characters' textures) |
| Sound effects (1,610) | Bank split and decoded to WAV (17 minutes) |
| Battlefield terrain (186) | Decoded from the game code (Stage.c); terrain exports to OBJ |
| Effects, events, text, save icon... | Read by checked tools; **100% of the data bytes are classified** |
| Decompilation | 10.6% of the code in C (39 files in `src/`), 548 functions matching the original byte for byte ([docs/code.md](docs/code.md), [docs/matching.md](docs/matching.md)) |

## Decompilation

The executable was built with Metrowerks CodeWarrior for PlayStation 2. Its code is being
rewritten in C, one original source file at a time, in `src/`:

- **Non-matching first:** every function gets equivalent C, checked against the disassembly, with
  neutral names (`func_`/`g_` + address) and comments on what is known. The goal is a readable,
  editable source for a native port.
- **Matching where it comes easily:** a function whose C compiles to exactly the game's bytes is
  tagged `matching`. The compiler, settings and the rules learnt so far are in
  [docs/matching.md](docs/matching.md); anyone can check a function on
  [decomp.me](https://decomp.me) (`tools/decompme.py` prepares a scratch).
- **Done so far:** the start-up code and main loop, the scene manager and most of the 24 scenes'
  own code (title, menus, options, shop, treasures, officer editor, battle set-up...), file
  reading, the memory allocator, controllers, GS packets and textures, sound and music streaming,
  the disc reader thread, movies, IPU pictures, text drawing and the first part of the 3D model
  code.
- About 7% of the code is Sony's libraries, built with another compiler; it is left for later.

`py tools/check_src.py` checks that every file in `src/` is valid C (with any GCC or Clang), and
`py tools/check_layout.py` that the structs modelling the game's objects sit at the right
addresses.

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
| `tools/ps2model.py` | Export the 3D models (with skeleton and skinning applied) to OBJ, with a PNG preview |
| `tools/motion.py` | Read the animations and pose a model at any frame (OBJ / PNG) |
| `tools/tmd2.py` | Export the battlefields' static scene objects (TMD2) to OBJ |
| `tools/efb.py` | Check the EFB particle effects and print their layers |
| `tools/ipu.py` | Convert the IPU movies (`ipu2`) to video |
| `tools/battlefield.py` | Check the battlefield terrain files and export a terrain to OBJ |
| `tools/tm3.py` | Convert tm3 textures (GS upload packets) to PNG, one per palette |
| `tools/event.py` | List the commands and motions of the in-engine cutscene (event) files |
| `tools/soundbank.py` | Split the sound-effect bank into 1,610 WAV files |
| `tools/tim2.py` | Convert TIM2 textures to PNG, every texture of the disc at once |
| `tools/elf_info.py` | Sections, symbols, compiler and code size of an executable |
| `tools/find_strings.py` | Readable strings of a binary, with a report of file names |
| `tools/mips_disasm.py` | Minimal MIPS (R5900) disassembler for quick looks |
| `tools/text.py` | Read the text tables (system messages, dialogue lines...) |
| `tools/lz.py` | Decompress the LZ-packed entries |
| `tools/pac0.py` | Read the PAC0 files (one per voice clip of the cutscenes) |
| `tools/ps2icon.py` | Read the 3D memory card save icon |
| `tools/check_src.py` | Syntax and type check of the decompiled C in `src/` |
| `tools/check_layout.py` | Check that the game objects' struct fields sit at their addresses |
| `tools/group_globals.py` | Turn scattered globals into the structs they belong to |
| `tools/decompme.py` | Prepare a function for a decomp.me scratch (assembly, context, C) |
| `tools/progress.py` | Build a progress report in the decompilati.onl format (also runs `tools/badges.py`) |
| `tools/badges.py` | Our own progress badges, history (`progress/history.csv`) and `progress/PROGRESS.md` |

## Documentation

- [docs/disc.md](docs/disc.md): the disc
- [docs/executable.md](docs/executable.md): the `SLES_546.24` executable
- [docs/formats/](docs/formats/README.md): file formats
- [docs/code.md](docs/code.md): the code, module by module
- [docs/matching.md](docs/matching.md): compiler settings and how to write matching C

## Contributing rules

- Never commit game files: no executable, no extracted assets, no disc image. Everyone builds from
  their own disc.
- No copy-protection circumvention, and no links to game files or BIOS downloads.

## Legal

This project distributes its own tools and documentation, and C source reconstructed from the
executable for preservation and interoperability. It contains no game files (no executable,
assets or disc images), and does not circumvent any copy protection. The compiler used to check
matching functions is used with its rights holder's permission and is not distributed.
Samurai Warriors 2: Empires is © Koei Tecmo.
