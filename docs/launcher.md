# Notes for the unified launcher

This project (a decompilation of Samurai Warriors 2: Empires, PS2) is meant to end up inside a
unified launcher together with other decompilation ports. The launcher's design is not fixed yet.
This file lists what the port needs from the launcher and what the launcher can expect from the
port. It will be updated as the port takes shape.

## Status

- Code decompiled (non-matching): see [PROGRESS.md](../PROGRESS.md) (52 % on 2026-11-27).
- No PC build yet: the C in `src/` is checked file by file, but nothing is linked together yet.
- Data formats are fully documented in [docs/formats/](formats/), with readers in `tools/`.

## What the launcher should expect from this port

### One self-contained module per game

Every decompilation in this family names unknown symbols after their address (`func_00102A20`,
`g_00669D60`). Two games in one process would therefore clash. The plan is to build each game as
its own module that exports only a small interface:

- **Preferred:** each game as its own module (DLL or separate executable), so its internal
  symbols stay private.
- **Fallback:** a per-game symbol prefix (`sw2e_`), applied by script.

### Entry interface (planned)

A small C interface, so the launcher can be written in any language:

| Call | Role |
|---|---|
| `init(platform, config)` | Start the game with the launcher's platform layer and settings. |
| `frame()` | Run one frame; returns whether the game wants to keep running. |
| `shutdown()` | Free everything and return to the launcher. |

The game code will not call `exit()`, will not hard-code paths and will not own the main loop.

## What the port needs from the launcher (platform layer)

The game code will only reach the outside world through an interface that the launcher provides,
so it is written once for every game:

- **Video:** a surface or graphics context. The PS2 GS and VU1 drawing will be translated by the
  port. It will need a frame buffer or a 3D API, depending on the renderer chosen.
- **Audio:** an output stream. SPU ADPCM decoding, music streams and movies are done by the port.
- **Input:** pad state, mapped to a PS2 DualShock 2 layout (two players are possible).
- **Files:** read access to the player's own disc image (the game data is never shipped), and a
  folder for save data.
- **Time:** frame pacing (rate to confirm from the code: the disc is the PAL release).

## Legal constraints the launcher must keep

- No game files are distributed. The player supplies their own disc image (SLES-54624, Europe).
- The compiler used for matching work is never shipped or needed at run time.

## Changes log

- 2026-11-27: file created. Interface and module boundary are proposals, not final.
