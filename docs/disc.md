# The disc: Samurai Warriors 2: Empires (Europe), SLES-54624

## Redump verification

Image checked on 2026-11-26 with `tools/hash_image.py`. It is an **exact match** for
[redump.org/disc/17102](http://redump.org/disc/17102/):

| Field | Value |
|---|---|
| Media | DVD-5 (single layer) |
| Version | 1.00 |
| Sectors | 1,114,960 |
| Size | 2,283,438,080 bytes |
| CRC32 | `92795049` |
| MD5 | `487e1f8ea43e4e1f929d579b0a66baa3` |
| SHA-1 | `ab3a9a74b848b20c507c5268cbb9f02903c5845e` |
| EXE date (Redump) | 2007-01-16 |

## ISO9660 layout

| LBA | Size (bytes) | File | Role |
|---:|---:|---|---|
| 50000 | 3,529,520 | `SLES_546.24` | Boot executable (MIPS ELF), see [executable.md](executable.md) |
| 51724 | 56 | `SYSTEM.CNF` | `BOOT2 = cdrom0:\SLES_546.24;1`, `VER = 1.00`, `VMODE = PAL` |
| 51725 | 275,345 | `MODULES/IOPRP300.IMG` | IOP kernel replacement image (Sony SDK) |
| 51860 | 348,944 | `MODULES/MODULES.BIN` | IOP modules (an ELF; to study) |
| 52031 | 873,093,120 | `LINKDATA.ANS` | Container: 106 audio streams (probably music) |
| 478346 | 566,034,432 | `LINKDATA.BNS` | Container: 3,502 files (textures, models, archives...) |
| 754730 | 716,763,136 | `LINKDATA.CNS` | Container: 21 MPEG-2 movies |

All game data is in the three [LINKDATA](formats/LINKDATA.md) containers. The executable starts at
sector 50,000, which leaves the first ~100 MB of the disc empty.
