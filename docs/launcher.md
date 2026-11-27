# Notes for the unified launcher

This project (a decompilation of Samurai Warriors 2: Empires, PS2) is meant to end up inside a
unified launcher together with other decompilation ports. The launcher's design is not fixed yet.
This file lists what the port needs from the launcher and what the launcher can expect from the
port. It will be updated as the port takes shape.

## Status

- Code decompiled (non-matching): see [PROGRESS.md](../progress/PROGRESS.md) (52 % on 2026-11-27).
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

## Answer from the launcher side (2026-11-27)

The launcher project (UnifiedPortProject) replied in its `docs/runtime.md`. Summary, to accept or
amend here:

- **Module boundary:** one game per process. The launcher already starts each port as its own
  executable, so address-named symbols never meet another game's. The `sw2e_` prefix script is
  not needed.
- **Who owns the loop:** a shared library, `upp_runtime`, kept in the launcher repository and
  linked into `sw2epc.exe`. It owns `main()`, the main loop, the window, audio, pads, disc access,
  frame pacing and reading the launcher's `launch.json`. The platform layer is therefore written
  once for every game, and a game crash never takes the launcher down.
- **Entry interface:** as proposed above, with two changes:
  - the game exports one symbol, `upp_game_entry()`, returning a table with `init`, `frame`,
    `shutdown`, the game id and the frame rate the logic expects;
  - `init(platform)` takes no `config`: options are read through `platform->option_bool / _number /
    _string`, so the game never parses JSON.
- **Platform layer (first version):**
  - video: `video_present(rgba, w, h, pitch)`, one finished picture per frame; a 3D path is added
    later if the renderer needs it;
  - audio: push signed 16-bit stereo at any rate; the runtime resamples;
  - input: two pads in DualShock 2 layout (buttons, sticks, pressure, rumble);
  - files: read-only access to the player's image by ISO 9660 path or by 2048-byte sector, with no
    extraction; one writable folder for saves;
  - time and logging.
- **Common options** (window mode, render scale, vsync, volume, pause on focus loss) are handled
  by the runtime; the game only reads the options of its own manifest.
- **Development:** `sw2epc.exe --disc <image>` still works without the launcher.

Questions the launcher side needs answered from here:

1. Frame rate of the EU disc: 50 Hz only, or also a 60 Hz mode?
2. Renderer: a software picture first, or a 3D API from the start?
3. Audio rate after SPU mixing (48 kHz?).
4. Saves: memory-card style files, or the game's own format as plain files?
5. Does the game need threads (streaming, IOP-side work)? If yes, the platform table gets thread
   and lock calls.
6. Languages on the EU disc: is a language option wanted?

## Changes log

- 2026-11-27: file created. Interface and module boundary are proposals, not final.
- 2026-11-27: answer from the launcher side added (runtime library, `upp_game_entry`, open
  questions). Waiting for this project's agreement.
