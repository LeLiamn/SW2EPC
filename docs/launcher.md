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

## Reply from this project (2026-11-27)

Accepted as proposed: one game per process (no `sw2e_` prefix), `upp_runtime` linked into
`sw2epc.exe` and owning `main()`, `upp_game_entry()`, options read through `platform->option_*`,
the audio, input, files and save folder of the first platform version, and `--disc <image>` for
development.

### Two changes asked for

1. **A blocking frame call next to `frame()`.** The original code is not cut into "one frame per
   call": loading screens, movie playback and fades wait for the next frame inside the function
   itself. Rewriting all of them to return each frame would be large and error-prone.
   - Proposal: the runtime runs the game logic on a thread or fiber of its own.
   - The game calls `platform->vsync()`, which presents the picture, lets the runtime pump its
     events, and returns at the next frame.
   - `frame()` can stay for games that fit it; SW2E needs the `vsync()` mode.
2. **A 3D path early.** `video_present(rgba, ...)` is fine for menus and for the first build.
   Battles would need a full software rasterizer of the PS2 GS, which is a large and slow piece
   of work. The game really draws textured triangles with blending (from VU1 microcode and GS
   packets). A small "draw textured triangles with this blend mode" interface, or a GPU context
   handed to the game, would be simpler and fast from the start. Please plan it for the second
   platform version.

### Answers to the questions

| # | Question | Answer |
|---|---|---|
| 1 | Frame rate | 50 Hz. The game times things at 3000 frames per minute. No 60 Hz mode found so far; still to check in the display set-up code. |
| 2 | Renderer | A software picture first, then a 3D path soon (see change 2). |
| 3 | Audio rate | 48 kHz, the SPU2 output rate. Music streams are 48 kHz and the sound bank 32 kHz, mixed to 48 kHz. |
| 4 | Saves | Memory-card style: one folder per save holding the icon and the game's own data files. The data stays in the game's format, and saves can still be exported to a real card or an emulator. |
| 5 | Threads | Yes. The game has at least a disc reader thread (priority 5) and a movie player thread (priority 2). The platform table needs thread, lock and event calls. |
| 6 | Languages | Only English text has been seen so far. The text tables still have to be checked for other languages before deciding on an option. |

Note for other games: this disc image is single-layer (2.28 GB), but some PS2 discs are
dual-layer. The ISO reader must then also read the second layer's volume descriptor; tools such
as 7-Zip only read the first one.

## Launcher side: both changes accepted (2026-11-27)

The launcher's `docs/runtime.md` is updated and now marked as agreed. What changed there:

1. **Blocking mode.** `upp_game_api` gains `run()` next to `frame()`; a game fills exactly one.
   - SW2E fills `run()`. The runtime calls it on a game thread it creates; the main thread keeps
     the window, OS events, presenting and the audio device.
   - `platform->vsync()` presents the frame, waits for the next one at `frame_rate` (50.0), and
     samples the pads.
   - It returns 0 when the player closes the window; the game should then leave `run()`. If it
     has not within 2 seconds, the runtime ends the process.
   - While paused on focus loss, `vsync()` does not return, so the game needs no pause code.
2. **3D path.** Planned as platform version 2: `texture_create`, `texture_upload` and
   `draw_triangles(state, vertices, count)`, implemented by the runtime with SDL_GPU.
   - The blend fields follow the GS formula `(A - B) * C / 128 + D`, with alpha test, depth test
     and write, filtering and clamping.
   - Coordinates stay in the game's resolution; the runtime applies `display.render_scale`.
   - No raw GPU context is handed to the game, so the game code never includes SDL or a 3D API.
   - To settle when the renderer starts: render-to-texture and frame-buffer effects, CLUT
     textures, fog.

From the answers:

- **Threads** are in platform version 1: `thread_create` (PS2 priority scale, 1 = highest),
  `thread_join`, mutexes, and events that count like PS2 semaphores, with a timeout. Disc reads are
  thread-safe, so the disc reader thread can stream while the game thread runs.
- **Audio:** 48 kHz needs no conversion.
- **Saves:** `save_dir` is `<data_dir>/saves`, with one memory-card style folder per save.
- **Frame rate and language:** `display.refresh` stays "planned" until the 60 Hz check is done,
  and there is no language option until the text tables are checked. Please note the results here
  when known.
- **Dual-layer discs:** noted. The launcher reads only the first layer's volume descriptor today;
  reading the second one is on its list before the first dual-layer game is added. It is not
  needed for SW2E.

Nothing else is open on the launcher side. The runtime will be built when SW2EPC is ready to link.

## Feedback from this project on the agreed interface (2026-11-27)

Agreed overall. Three points to add, and answers to the renderer items left open.

1. **Threads must run one at a time, by priority.** The PS2 runs one game thread at a time: a
   higher-priority thread runs until it blocks, and lower ones only run while it waits. The game
   code relies on this. For example, request lists are shared between the game thread and the
   disc reader thread without locks. Real parallel threads on a PC would create races that never
   happened on the PS2.
   - Proposal: the runtime offers a PS2-like mode where the game's threads share one lock.
   - A thread gives the lock up only in blocking calls: `vsync()`, waiting on an event, sleeping,
     and blocking disc reads.
   - The runtime then wakes the highest-priority thread that is ready.
   - SW2E would use this mode; a game written with real locks could turn it off.
2. **Closing during a save.** Killing the process 2 seconds after close could cut a save in half.
   Two possible fixes:
   - the runtime writes save files atomically (to a temporary name, then renamed), so a killed
     write never damages the previous save; or
   - the game can tell the runtime it is busy saving, so the runtime waits longer.
   The atomic write is enough on its own and needs nothing from the game.
3. **Texture colour scale.** On the GS, a vertex colour of 0x80 means 1.0 when it modulates a
   texture, so the result is `texture * colour / 128` (and can brighten up to 2x). Alpha also uses
   0x80 as 1.0. `draw_triangles` should keep this scale, or the game will convert every colour.

Answers to the renderer items:

- **CLUT textures:** needed. Many textures are 4-bit or 8-bit with palettes (TIM2 and the `tm3`
  files), and the game sometimes draws one picture with different palettes. Palette textures in
  the runtime would be best. Converting to RGBA on upload also works, at the cost of one texture
  per palette.
- **Render-to-texture and frame-buffer effects:** to be confirmed from the drawing code; the
  effect and distant-view code is not decompiled yet. The result will be noted here.
- **Fog:** to be confirmed the same way.

## Changes log

- 2026-11-27: file created. Interface and module boundary are proposals, not final.
- 2026-11-27: answer from the launcher side added (runtime library, `upp_game_entry`, open
  questions). Waiting for this project's agreement.
- 2026-11-27: reply from this project: two changes asked for (blocking `vsync()` mode, early 3D
  path) and answers to the six questions.
- 2026-11-27: launcher side accepted both changes (`run()` + `vsync()` blocking mode, 3D drawing
  interface as platform version 2) and added threads to platform version 1. Agreed.
- 2026-11-27: feedback from this project: PS2-like thread scheduling (one thread at a time, by
  priority), atomic save writes, the GS colour scale, and answers on CLUT, render-to-texture and fog.
- 2026-11-27: launcher side accepted the feedback (PS2 thread model with a run token,
  folder-atomic `save_*` calls, GS colour scale, indexed textures) and asked about interrupt
  handlers.
