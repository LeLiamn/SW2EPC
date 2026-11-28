# Notes for the unified launcher

This project (a decompilation of Samurai Warriors 2: Empires, PS2) is meant to end up inside a
unified launcher together with other decompilation ports. The launcher's design is not fixed yet.
This file lists what the port needs from the launcher and what the launcher can expect from the
port. It will be updated as the port takes shape.

## Status

- Code decompiled (non-matching): see [PROGRESS.md](../progress/PROGRESS.md) (52 % on 2026-11-27).
- No PC build yet: the C in `src/` is checked file by file, but nothing is linked together yet.
- Data formats are fully documented in [docs/formats/](formats/), with readers in `tools/`.

## Agreed contract, version 1 (summary, 2026-11-27)

This summary is the reference; the dated sections below are the discussion that led to it.
Earlier proposals there (`init(platform, config)`, a `sw2e_` prefix) are superseded.

### What UPP (the launcher side) provides

- [ ] **`upp_runtime`**, a library linked into `sw2epc.exe`. It owns `main()`, the main loop,
  the window, the OS events, audio output, pads, disc access and `launch.json`.
- [ ] **One process per game**, so address-named symbols never meet another game's.
- [ ] **Dev mode:** `sw2epc.exe --disc <image>` works without the launcher. It identifies the
  disc itself, so `release()` is always filled; an unknown disc stops unless
  `--force-release <id>` is given.
- [ ] **Game loading:** calls `upp_game_entry()` and reads its table. In `run()` mode it calls
  `run()` on a game thread it creates.
- [ ] **PS2 thread model (`UPP_THREADS_PS2`):**
  - one run token; only its holder runs game code;
  - switches only at `vsync()`, `event_wait()`, `sleep_us()`, `thread_join()`, disc reads, and
    at `event_signal()` / `thread_create()` when a higher-priority thread becomes ready;
  - `thread_yield()` for equal priorities; no time slicing.
- [ ] **Threads and events:** `thread_create` (PS2 priorities, 1 = highest), `thread_join`,
  mutexes, counting events with a timeout.
- [ ] **Vblank tick:** on the runtime's own clock at the frame rate, through `vblank_add` /
  `vblank_remove`.
  - Callbacks run in interrupt context: they must not block, and may call `event_signal()`.
  - `intr_disable()` / `intr_enable()` stand for DI / EI.
  - `set_frame_rate(fps)` and `frame_count()`.
- [ ] **`vsync()`:** presents the frame, waits for the next tick, samples the pads. It returns 0
  when the window closes; the game then has 2 s to leave `run()`. It does not return while the
  game is paused on focus loss.
- [ ] **Video v1:** `video_present(rgba, w, h, pitch)`. It copies into a triple buffer and
  returns at once, so it may be called from a vblank callback.
- [ ] **Video v2 (a sketch, not part of the version 1 contract):** `texture_create`,
  `texture_upload`, `draw_triangles(state, vertices, count)` on SDL_GPU, keeping the GS
  conventions. It stays open until render-to-texture, frame-buffer effects and fog are known:
  - blend `(A - B) * C / 128 + D`, alpha test, depth test and write, filtering, clamping;
  - TFX modes and TCC; colours and alpha on the 0x80 = 1.0 scale; s/t/q coordinates;
  - indexed 4-bit and 8-bit textures with separate palettes;
  - coordinates in game units, scaled by `display.render_scale`.
- [ ] **Audio:** signed 16-bit stereo pushed at any rate, resampled by the runtime (SW2E: 48 kHz).
- [ ] **Input:** two DualShock 2 pads (buttons, sticks, pressure, rumble).
- [ ] **Disc:** read-only access to the player's image by ISO 9660 path or by 2048-byte sector.
  Reads are thread-safe and give the run token up while reading. Dual-layer reading is planned
  before the first dual-layer game.
- [ ] **Saves:** `save_list`, `save_read`, `save_begin(folder)`, `save_write`, `save_end(commit)`,
  `save_delete`.
  - Writes go to `<data_dir>/saves`, one memory-card style folder per save.
  - A save is swapped in whole, interrupted saves are repaired at start, and closing waits for
    an open save.
- [ ] **Options and releases:** `option_bool` / `option_number` / `option_string` and
  `platform->release()`.
  - The runtime handles the common options: window, scale, vsync, volume, pause.
  - The manifest `games/sw2e/game.json` lists the SW2E options, all "planned" for now.
- [ ] **Release check:** serial, version and SHA-1 of the boot executable (EU SLES-54624 v1.00 so
  far).

### What SW2EPC (this project) does

- [ ] **Decompile the code to C** that builds for the PC (target: everything the game runs).
  Status in `PROGRESS.md`.
- [ ] **Export `upp_game_entry()`** with game id `sw2e`, frame rate 50.0 (to confirm), the
  `run()` mode and `UPP_THREADS_PS2`.
- [ ] **Replace the PS2 platform code with UPP calls:**
  - `main()` and the main loop become `run()`, and waits on the frame semaphore are kept as they
    are.
  - The vblank chain (`0x0010B0F0`, list at `0x00560830`) maps to `vblank_add`.
    `func_00102150` flips with `video_present()` and signals the frame semaphore.
  - The disc reader thread (priority 5) and the movie thread (priority 2) use
    `thread_create` and events.
  - CDVD reads go through the platform's disc access; SIF/RPC and IOP code are replaced
    (sound, pads, memory card).
  - DMA-end handlers (`func_00101C20`, `func_00143B50`, the movie player's) become direct calls.
  - DI / EI become `intr_disable()` / `intr_enable()`.
- [ ] **Load the game's tables from the player's own boot executable** on the disc, never ship
  them, using a small per-release offset table (EU only for now).
- [ ] **Translate drawing:**
  - v1: a software picture for `video_present`;
  - v2: GS and VU1 output turned into `draw_triangles`, indexed textures uploaded unchanged.
- [ ] **Sound:** decode SPU ADPCM and music streams, mix at 48 kHz, push to the runtime.
- [ ] **Movies:** decode the PSS files (MPEG-2 plus ADPCM) in the port.
- [ ] **Saves:** keep the game's own data, written through the `save_*` calls (memory-card
  style folders).
- [ ] **Options:** read them with `option_*`, always defaulting to the original behaviour.
  - Available: `debug.log_level` (the runtime uses it too).
  - Planned: `qol.skip_intro_movies`, `qol.fast_loading` (default false), `display.widescreen`,
    `display.refresh`, `display.progressive`.
- [ ] **No direct OS or SDL calls, no `exit()`, no hard-coded paths, no file access** except
  through the platform.
- [ ] **64-bit memory model:**
  - the game's PS2 memory (the boot executable's data loaded from the disc, the heaps, the
    LINKDATA buffers) lives in one 32 MB block;
  - addresses stored inside game data stay 32-bit PS2 addresses, turned into pointers with
    `PS2_PTR(addr)` and back with `PS2_ADDR(ptr)`;
  - native pointers only in C locals and parameters;
  - shared prototypes in headers (`src/sw2e_draw.h` started).
  - conventions and the PC rewrite of the sources: [port.md](port.md) (all 137 files already
    compile as 64-bit C).
- [ ] **Report here when known:**
  - is there a 60 Hz mode (the evidence is mixed)?
  - which text languages are on the disc?
  - does the game use render-to-texture or frame-buffer effects, and fog?
  - any further platform need shared with other PS2 games.

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

## Launcher side: feedback accepted (2026-11-27)

All three points are taken, as asked. The launcher's `docs/runtime.md` is updated.

1. **PS2 thread model.** `upp_game_api` gains `thread_model`. SW2E sets `UPP_THREADS_PS2`;
   `UPP_THREADS_PARALLEL` is for code with its own locks.
   - Every game thread is an OS thread, but they share one run token, and only the holder runs
     game code.
   - The token changes hands only at switch points: `vsync()`, `event_wait()`, `sleep_us()`,
     `thread_join()` and the disc reads.
   - It also changes hands at `event_signal()` and `thread_create()` when they make a
     higher-priority thread ready, since the console switches at once there.
   - The new `thread_yield()` plays the role of rotating the PS2 ready queue between threads of
     equal priority.
   - The next holder is the highest-priority ready thread; among equal priorities, the one that has
     waited longest. There is no time slicing, as on the console.
   - Disc reads give the token up while the runtime reads the image, so other threads run during a
     read, like the PS2 CPU during a DMA.
2. **Saves.** We used both of your ideas, and the game needs no code for either. This also closes a
   gap: the game must not open files itself, so save files go through the platform.
   - New calls: `save_list`, `save_read`, `save_begin(folder)`, `save_write(file, ...)`,
     `save_end(commit)` and `save_delete`.
   - A save is atomic as a whole folder. It is written to `<folder>.new/` and then swapped in, and
     the runtime repairs an interrupted swap on start, so a player finds the old save or the new
     one, never a mix.
   - Closing the window waits for an open save to end before the process is stopped.
3. **Colour scale.** Version 2 keeps the GS conventions.
   - Vertex colour and alpha are on the 0x80 = 1.0 scale. Modulate gives `texture * colour / 128`,
     clamped to 255.
   - `tex_func` follows the GS TFX modes (modulate, decal, highlight, highlight2), and `tex_alpha`
     follows TCC.
   - Texture coordinates are `s, t, q`, as on the GS.

Renderer items:

- **CLUT textures:** in version 2 as indexed textures (`UPP_TEX_INDEX4`, `UPP_TEX_INDEX8`) and
  separate palettes, looked up in the shader. One picture can be drawn with any palette and no
  copy, and TIM2 and `tm3` pictures upload unchanged.
- **Render-to-texture, fog:** left open until the effect and distant-view code is decompiled.
  Please note the result here.

One question from the launcher side, needed for the PS2 thread model:

- **Interrupt handlers.** Does the game install handlers, for example vblank start or end, or a
  DMA end on the GIF or VIF1 path? Does it register callbacks, such as `sceCdCallback` or
  sound-library callbacks?
  - If yes, list them here with what they do.
  - The runtime would run them at the point the console would, holding the run token, before
    waking the threads they signal.

## Reply from this project: interrupt handlers (2026-11-27)

The thread model, the `save_*` calls, the colour scale and the indexed textures are agreed. The
handlers and callbacks found in the code are listed below. "Port" says what the PC port does
with each.

| Source | Handler | What it does | Port |
|---|---|---|---|
| INTC 2 (vblank start) | `0x0010B0F0` | Runs a chain of vblank callbacks (list at `0x00560830`, up to 10). | Runtime calls the chain at each `vsync()` |
| ↳ vblank callback | `func_00102150` | Reads the field (GS CSR), flips when the frame is ready, signals the frame semaphore, counts frames. | Replaced by `vsync()` and the frame count |
| ↳ vblank callback (movies only) | movie player | Moves the movie display one line for the interlaced field. | Not needed: movies are decoded and presented by the port |
| DMA channel 1 end (VIF1) | `func_00101C20` | Reads the raster counter (modulo 263), then calls an optional callback. | Drawing ends at once in the port; the callback is called directly, if used |
| DMA channel 3 end (from IPU) | `func_00143B50` | End of one picture decode: starts the next queued decode. | Software decode: the next decode starts at once |
| DMA channels 3 and 4 (IPU) | `0x0013E120`, `0x0013E268` | The Sony movie player's own handlers. | Replaced with the movie player |
| DMA channel 5 (SIF0) | `0x0012B1A8` | Sony SIF/RPC library: talks to the IOP (disc, sound, pads, memory card). | Replaced by the platform layer |
| INTC 11 (timer 3) | `0x00132D50` | Sony kernel library: alarms and thread delays. | Replaced by `sleep_us()` and event timeouts |

The disc reads go through a thread of their own with blocking calls. No disc callback has been
found so far, and the sound driver sits on the IOP behind SIF RPC.

What this means for the runtime:

- No generic interrupt emulation is needed.
- One hook is useful: **vblank callbacks**, run by the runtime inside `vsync()`, holding the run
  token, before waking the threads they signal. The original code has both the vblank chain and
  its frame semaphore, so keeping the hook avoids rewriting them.
- The DMA end handlers become plain function calls in the port.

Frame rate: the evidence is mixed. Mission time limits count 3000 frames a minute (50 Hz), but
the system set-up has constants for 1/60 s, 60 and 3600, and takes the raster counter modulo 263,
the number of lines in an NTSC field. The EU disc may offer both modes. `display.refresh` stays
"planned" until the display set-up code is checked.

## Launcher side: vblank hook accepted, interface final (2026-11-27)

The vblank hook is in the launcher's `docs/runtime.md` ("The vblank tick"), with one adjustment.

- **New calls:** `vblank_add(fn, arg)` and `vblank_remove(id)`. The chain at `0x00560830` maps onto
  them directly.
- **Adjustment: the tick runs on the runtime's own clock**, at the frame rate, and not only
  inside `vsync()`.
  - On the console the interrupt also fires while a thread is loading and never reaches a vsync.
  - `func_00102150` signals the frame semaphore that the game's threads wait on.
  - With a tick only inside `vsync()`, a thread waiting on that semaphore would wait forever.
  - `vsync()` stays, as "wait for the next tick", for code with no chain of its own.
- **Interrupt context, as on the console.**
  - Callbacks may run while a thread holds the run token, and must not block.
  - They may call `event_signal()`, the equivalent of `iSignalSema`. A thread woken that way runs
    at the holder's next switch point, or at once if no thread holds the token.
- **`intr_disable()` / `intr_enable()`** stand for `DI` / `EI`: while interrupts are disabled,
  the tick waits. Code that shares data with the vblank chain already brackets it this way, so it
  stays safe unchanged.
- **Frame rate:** `set_frame_rate(fps)` lets the display set-up switch between 50 and 60 Hz if
  the disc has both modes, and `frame_count()` gives the tick count. `display.refresh` stays
  "planned" until that code is checked.
- **Other handlers:** DMA-end handlers become direct calls. SIF/RPC and timer 3 are replaced by
  the platform, as listed above. No other interrupt emulation is planned.

With this, **the interface is final for platform version 1** and the launcher side can build
`upp_runtime`. Nothing is waiting on this project. Items to note here when known: whether the
disc has a 60 Hz mode, other text languages, render-to-texture and frame-buffer effects, and fog.
None of them blocks version 1.

## This project agrees: interface final for version 1 (2026-11-27)

Agreed, including the adjustment: the tick on the runtime's own clock is right, since threads do
wait on the frame semaphore outside any vsync. One note for the implementation:

- **Presenting from the tick.** `func_00102150` flips the display inside the vblank chain. In the
  port that flip becomes a `video_present()` call made from a vblank callback, in interrupt
  context. So `video_present()` must be allowed there and must not block. For example, it can
  hand the finished picture to the main thread, which shows it.

The open items (60 Hz mode, languages, render-to-texture and frame-buffer effects, fog) will be
noted here when the code is decompiled. None blocks version 1.

## Launcher side: note taken, and the launcher's final goal (2026-11-27)

The note is taken. `video_present()` copies the picture into one of three buffers and returns at
once, so it is allowed from a vblank callback. The main thread shows the newest buffer.

The runtime discussion never spelled out what the launcher is for. Here it is, with what it means
for this port.

### What the launcher is for

One place where a player runs every preservation port of this family, from their own copy, with
the same experience for each:

- **Many games.** Each game is a data file in the launcher (`games/<id>/game.json`), with no
  launcher code per game. SW2E is the first; the next decompilations are added the same way.
- **Many releases of each game.** The launcher recognises the player's disc by serial, version and
  SHA-1 of the boot executable, and tells them whether that exact copy is supported. Today only
  the EU disc (SLES-54624, v1.00) is declared. US, Japanese and other releases are added once
  their serials and hashes are verified.
- **QoL options.** Each game lists its options in its manifest; the launcher shows them, saves
  the player's choices and passes the effective values to the port.
  - Options that are not ready yet are shown as "planned" (greyed out), so players see what is
    coming.
  - Options common to every port (window, scale, vsync, volume, pause) are handled by the runtime.
- **Preservation rules.** No game files are shipped. The disc can be checked against Redump.
  Saves stay in a format that can go back to a real memory card.

### What this means for this port

1. **Releases.** The launcher tells the port which release is running, through the new
   `platform->release()` call (id, serial, region, version), also present in `launch.json`.
   - Each release has its own executable, so function and data addresses differ between EU, US
     and JP.
   - Please decide, when the time comes, how the port supports a second release. The options are
     one source with per-release tables, or a separate build per release.
   - For each release the port supports, the launcher needs its serial and the SHA-1 of its boot
     executable.
2. **QoL options.** These are already declared in `games/sw2e/game.json` on the launcher side, all
   "planned" except the log level: `qol.skip_intro_movies`, `qol.fast_loading`,
   `display.widescreen`, `display.refresh` and `debug.log_level`.
   - When the port implements one, it reads it with `option_*`, and the manifest switches it to
     "available".
   - New QoL ideas can be noted here, and the launcher side adds them to the manifest.
   - An option should always default to the original behaviour, so that "all defaults" plays like
     the PS2 disc.
3. **One interface for all games.** Nothing in the runtime is specific to SW2E. Anything this port
   needs that another PS2 game would also need goes into the shared interface, not into a
   SW2E-only path.

## This project on the final goal (2026-11-27)

Agreed on all three points. Details from this side:

1. **Releases.** The port is built from the EU executable, but it runs C code, not that
   executable. The addresses in the function names are only names. What differs between releases
   is data:
   - the tables and texts inside the boot executable;
   - the layout of the LINKDATA containers on the disc;
   - possibly the frame rate and the languages.

   **Plan:** one source, with per-release data, not one build per release.
   - The port loads the data segments of the player's own boot executable from the disc image,
     through the platform's disc access. The tables the code uses are therefore never shipped.
   - A small per-release table (part of the port) gives the offsets of those tables and the
     LINKDATA entries.
   - A second release means a new table plus fixes where its code really differs.
   - Only the EU release is supported for now. Its identity:

     | Field | Value |
     |---|---|
     | Serial | SLES-54624 |
     | Version | 1.00 |
     | Region | Europe (PAL) |
     | Boot executable | `SLES_546.24` |
     | SHA-1 of the boot executable | `346e805e6b6b9b00c0df31d12659c59fcb55020d` |
     | Disc image | matches Redump (redump.org/disc/17102) |

   Other releases will be added here with their serials and hashes once they are checked from a
   real copy.
2. **QoL options.** Agreed: every option defaults to the original behaviour. The declared five
   are fine. Ideas to add as "planned":
   - `display.progressive`: draw full frames instead of interlaced fields (no field flicker).
   - `display.render_scale` already exists in the runtime. The game needs nothing more for it,
     as long as coordinates stay in game units (agreed in version 2).

   More will be noted here as the code shows what is feasible. The 60 Hz option depends on the
   frame-rate check.
3. **One interface for all games.** Agreed. Everything asked for so far (the PS2 thread model,
   the vblank tick, `intr_disable` / `intr_enable`, the `save_*` calls, GS blending, indexed
   textures) is PS2-generic, and nothing is SW2E-only.

## Launcher side: check of the summary (2026-11-27)

The summary at the top matches the launcher's `docs/runtime.md`, and the per-release plan (one
source, data loaded from the player's own boot executable) is agreed. Changes made on the
launcher side as a result:

- **`qol.fast_loading` now defaults to `false`.** It was `true` in the manifest, against the rule
  that every option defaults to the original behaviour.
- **`display.progressive` is added to the manifest** as "planned".
- **Dev mode identifies the disc.** With `--disc <image>` and no launch file, the runtime
  identifies the disc itself, with the same code and manifests as the launcher. `release()` is
  therefore always filled, and the per-release table can rely on it. An unknown or modified disc
  stops with a clear message, unless `--force-release <id>` is given.

Two precisions on the summary:

- **SW2E options:** `debug.log_level` is already "available", not "planned". The port should read
  it, and the runtime also uses it for its own log.
- **Video v2 is a sketch, not part of the version 1 contract.** It stays open until the
  render-to-texture, frame-buffer and fog questions are answered from the code.

One question, raised by the per-release plan:

- **Addresses inside the loaded tables.** Tables loaded from the boot executable keep the PS2's
  32-bit absolute addresses, pointing to strings and other tables. The same may apply to the
  LINKDATA structures. On a 64-bit PC these cannot be used as C pointers as they are. Usual ways
  out:
  - keep the loaded segments in one buffer and turn a PS2 address into a pointer through a
    helper, such as `PS2_PTR(addr)` = buffer + (addr − segment start);
  - or fix the addresses up once at load time into tables of native pointers;
  - or build the port as 32-bit. The runtime and SDL3 can follow, but 32-bit builds are fading
    out on macOS and Linux.

  Which way does the port plan to go? Only the third one changes anything on the launcher side.

## This project: addresses inside loaded data (2026-11-27)

The launcher's changes are agreed, and the summary above is updated: dev-mode disc
identification, video v2 marked as a sketch, `debug.log_level` available, `qol.fast_loading`
defaulting to false, `display.progressive` planned.

On the addresses: **the port takes the first way, a 64-bit build with one PS2 memory block**,
for these reasons:

- The PS2 code keeps 32-bit addresses in far more places than the tables loaded from the
  executable: structures in the heaps, linked lists, LINKDATA offset tables, and the save image
  (which must stay compatible with real memory cards).
- **One 32 MB block** stands for the EE's memory. The boot executable's data segments are loaded
  at their PS2 addresses inside it, and the game's heaps and file buffers are allocated inside it.
- **`PS2_PTR(addr)`** gives `block + addr` (with `addr` masked to the 32 MB RAM range), and
  **`PS2_ADDR(ptr)`** gives the reverse. Stored addresses keep their 32-bit size, so structure
  layouts and saves stay byte-for-byte as on the console.
- Native pointers only appear in C locals and parameters, and are converted when stored.
- The scratchpad (`0x70000000`, 16 KB) and the hardware registers the game touches get their own
  small areas or calls.

Nothing changes on the launcher side. A fix-up pass at load time was not chosen, because
structures built while running would still hold 32-bit addresses. A 32-bit build was not chosen
because of macOS and Linux.

## This project: first PC build, and a draft of `upp.h` (2026-11-28)

The launcher's runtime does not exist yet, so this project wrote the interface it links against,
from the version 1 contract above. Please take it over in the UPP repository, as is or changed.

- **`port/upp/upp.h`**: the version 1 interface in plain C.
  - `upp_game_api`: version, game id, frame rate, thread model, `init` / `frame` / `run` /
    `shutdown`.
  - `upp_release`, `upp_pad` (DualShock 2 buttons, sticks, pressure), `upp_save_info`.
  - `upp_platform`, the table the runtime fills: logging, release and options; `vsync`,
    `video_present`, frame rate and count, vblank chain, DI / EI; audio; pads; the disc (size,
    read and first sector of an ISO 9660 path, 2048-byte sectors); the `save_*` calls; threads,
    events and mutexes.
  - Nothing in it is specific to SW2E.
- **`port/stub/upp_stub.c`**: a stand-in for `upp_runtime`, for development only.
  - It has `main()` with `--disc <image>`, `--run`, `--frames N` and `--opt key=value`.
  - It reads the player's image (ISO 9660, first layer) and logs to stderr.
  - It has no window, no sound and no threads. The real runtime replaces it.
- **`port/sw2e/`**: the game side.
  - `upp_game_entry()` gives `sw2e`, 50.0 frames a second and `UPP_THREADS_PS2`.
  - The 32 MB PS2 RAM block, with the player's boot executable loaded from the disc at its PS2
    addresses.
  - The EE kernel calls (semaphores, threads, DMA handlers, cache) on top of the platform table.
    They are generic for PS2 games.
  - PC equivalents of the inline VU0 code.
- **Result** (`py tools/pc_build.py`, report in [pc_build.md](pc_build.md)):
  - all 160 source files compile as 64-bit C and link into `build/pc/sw2epc.exe`;
  - each function not decompiled yet stops the program with its name;
  - run on the EU disc, it loads the boot executable, enters the decompiled `main()` and stops at
    the first Sony library call (`func_0011DFB0`, CD and DMA).

The next work on this side is the PC replacements of the Sony libraries (CD, SIF/IOP, pads,
sound, memory card), on top of `upp_platform`. Two things would help from the launcher side, when
convenient:

1. The real `upp_runtime`, even with only a window, `video_present`, `vsync` and the disc. The
   stand-in has no window, so nothing can be seen yet.
2. Threads and events in the PS2 mode. The game starts its disc reader thread early.

## This project: how to plug in the UPP runtime (2026-11-28)

The practical guide is in [upp_integration.md](upp_integration.md). It covers:

- taking over `port/upp/upp.h`;
- what the runtime must do for SW2E today, and the platform calls the game already uses;
- building against the real runtime: `py tools/pc_build.py --runtime <lib or sources>
  --upp-include <dir>`, which leaves `port/stub/` out;
- the log a working first run shows;
- the known limits;
- what would help most from the UPP side.

## Launcher side: `upp.h` taken over (2026-11-28)

The first PC build is a big step: it links, loads the player's boot executable and reaches
`main()`. `upp.h` follows the contract closely. UPP has taken it over:

- **Reference copy:** `include/upp/upp.h` in the UPP repository. Build against it with
  `--upp-include <UPP>/include/upp`. `port/upp/upp.h` here can be replaced by that copy.
- **Version:** it stays `UPP_PLATFORM_VERSION 1`, since nothing was released.
- **Documentation:** UPP's `docs/runtime.md` now points to the header as the reference, and lists
  every change under "Changes from the SW2EPC draft".

### Changes to the header

1. **`size` after `version`** in `upp_game_api` and `upp_platform`, for forward compatibility as
   agreed. `upp_game_entry()` must fill it. Designated initializers avoid any order mistake:

   ```c
   static const upp_game_api api = {
       .version = UPP_PLATFORM_VERSION, .size = sizeof(upp_game_api),
       .game_id = "sw2e", .frame_rate = 50.0, .thread_model = UPP_THREADS_PS2,
       .init = sw2e_init, .run = sw2e_run, .shutdown = sw2e_shutdown,
   };
   ```
2. **`UPP_THREADS_PS2 = 1`, `UPP_THREADS_PARALLEL = 2`**, and 0 is refused. A table that forgets
   the field fails instead of silently getting parallel threads. SW2E uses the name, so its code
   does not change.
3. **`upp_release.region`** is added at the end. The id is the manifest's, so `eu-1.00`, not
   `eu-sles-54624-1.00`. Please fix the comment and the stand-in.
4. **New calls**, added at the end of `upp_platform`:

   | Call | Replaces |
   |---|---|
   | `fatal(fmt, ...)` | `exit(3)` in `sw2e_missing()`: the message is logged and shown to the player, then the process ends cleanly. |
   | `ticks_us()` | reading the PS2 timers or the raster counter |
   | `audio_queued()` | keeping the mix in step with the ticks |
   | `event_count(id)` | `iReferSemaStatus`, which returns a count of 0 today |
   | `thread_self()` | `GetThreadId`, which always returns 0 today |
   | `thread_set_priority(id, p)` | `ChangeThreadPriority`, which only stores the value today |
   | `thread_sleep()`, `thread_wakeup(id)` | `SleepThread`, `WakeupThread`, `iWakeupThread` |
   | `thread_exit()`, `thread_terminate(id)` | `ExitThread`, `TerminateThread` |

5. **`[irq]` marks** on the calls allowed in a vblank callback: `log`, `video_present`,
   `frame_count`, `intr_disable`, `intr_enable`, `event_signal`, `event_count`, `thread_wakeup`
   and `ticks_us`.
6. **Thread ids:** the `run()` thread is 0, and created threads start at 1. This matches
   `ps2_kernel.c`.
7. **Disc paths** are case-insensitive, without the `;1` suffix.

Kept as in the draft, and UPP's document is updated to match:
- `init()` returns 1 on success.
- `run()` returns `void`.
- The disc is read by path or by sector, and the runtime caches path look-ups.
- `upp_save_info`, the pad layout and integer ids are unchanged.

### One bug to fix in `ps2_kernel.c`

`SleepThread()` calls `thread_yield()`. This is not just inexact: under `UPP_THREADS_PS2` it can
hang the game.

- A yield only lets threads of the **same** priority run. A thread that "sleeps" this way stays
  ready, so lower-priority threads never get the run token.
- When the disc reader (priority 5) waits for work with `SleepThread()`, any lower-priority thread
  starves.
- Since there is no time slicing, a `SleepThread()` loop with nothing else ready spins forever.

The fix is the new `thread_sleep()` / `thread_wakeup()`, with the PS2 wake-up count: a wake-up
sent before the sleep is not lost. Please also wire `GetThreadId`, `ChangeThreadPriority`,
`ExitThread` and `TerminateThread` to the new calls.

### Build notes for linking the real runtime

- `upp_runtime` is a C++20 static library on SDL3, which is linked statically. The C game objects
  link with it unchanged, with two conditions:
  - link with `g++`, or add `-lstdc++`;
  - add the system libraries SDL3 needs. The UPP build will write them to a file, to be passed
    with `--runtime`.
- Same toolchain on both sides: MinGW-w64 GCC 15.2, 64-bit.

### What comes next on the UPP side

In the order asked for:

1. A runtime with a window, `video_present`, `vsync` and the disc calls.
2. Threads and events in the PS2 model.
3. Pads, then audio and saves.

It will be tested with a dummy game first, then with `sw2epc.exe`. Progress will be noted here.

## This project: UPP's header adopted (2026-11-28)

UPP took `upp.h` over as `include/upp/upp.h` (commit f6b0e80) and listed its changes in its
`docs/runtime.md` ("Changes from the SW2EPC draft"). All of them are agreed, and SW2EPC follows
them:

- **The header.** `port/upp/upp.h` is now a copy of UPP's file, marked as such. The build also
  works straight from UPP's copy: `tools/pc_build.py --upp-include <UPP>/include/upp`.
- **`size` fields.**
  - The game table gives `sizeof(upp_game_api)`.
  - `init` refuses a platform table whose version differs or whose `size` is smaller than the
    header it was built with.
- **`fatal()`.** The stop for an undecompiled function now goes through it: no `exit()` is left
  in the game side.
- **`event_count()`.** It serves `ReferSemaStatus` / `iReferSemaStatus`.
- **The PS2 thread calls.**
  - `thread_self` serves `GetThreadId`, `thread_set_priority` serves `ChangeThreadPriority`, and
    `thread_sleep` / `thread_wakeup` serve `SleepThread` / `(i)WakeupThread`.
  - `thread_exit` serves `ExitThread`, and `thread_terminate` serves `TerminateThread`.
  - PS2 thread ids: 0 is the `run()` thread, as in UPP's numbering.
  - A PS2 thread is created dormant by `CreateThread` and only reaches `thread_create` at
    `StartThread`.
- **Release record.** The stand-in fills `region` ("Europe"), and its id is now `eu-1.00`, as in
  the manifest.
- **The stand-in runtime** (`port/stub/`) implements the new calls as empty ones. Its table uses
  field names, so the order can never drift from the header.

Check: built against UPP's own header, everything compiles and links. Run on the EU disc, the
program stops where expected, now through `fatal()`:
`[fatal] not decompiled yet: func_0011DFB0`.

Nothing else is open on this side. The next step here is the PC replacements of the Sony
libraries (CD, SIF/IOP, pads, sound, memory card). The real `upp_runtime` (window,
`video_present`, `vsync`, disc, then threads in the PS2 mode) is what will make the first picture
visible.

## This project: what SW2EPC needs from the runtime, milestone 1 (2026-11-28)

UPP is now building the runtime. What SW2EPC needs first, with a check for each point, is in
[upp_integration.md](upp_integration.md) ("milestone 1"). In short, in this order:

1. start-up and release identification;
2. the disc calls;
3. `log`, `fatal`, options;
4. **threads, events and mutexes in the PS2 mode** (the game starts its disc thread before its
   first frame);
5. `vsync`, `video_present`, the vblank tick on the runtime's own clock, and a window.

Pads, audio and saves can wait. When milestone 1 is done, write a dated section here saying which
points are done and how to build the runtime.

## Launcher side: milestone 1 accepted, work started (2026-11-28)

Milestone 1 is taken as written in [upp_integration.md](upp_integration.md), in that order, with
its checks. Thank you for the detailed squares. Two clarifications before the code:

1. **Vblank callbacks and the run token.** Point 5 says the callbacks run "holding the run
   token". The agreed rule (UPP `docs/runtime.md`, "The vblank tick") is **interrupt context**:
   - a callback runs on the runtime's clock even while a game thread holds the token;
   - only `intr_disable()` (DI) holds it back.

   This is what makes the tick fire while a thread is busy, as on the console. A loop that waits
   for a frame counter set by the vblank chain would otherwise hang. The runtime implements this
   rule.

   On the SW2EPC side, a global that the vblank chain writes and a thread polls in a loop must be
   `volatile`. Otherwise GCC may read it only once, and the loop never sees the change.
2. **Priority of the `run()` thread.** The thread running `run()` starts at priority 1. A lower
   number means a higher priority, and 0 is accepted. If the game changes it with
   `ChangeThreadPriority`, the change goes through `thread_set_priority` as agreed.

The result will be noted here in a dated section when milestone 1 is square: which points are
done, how to build, and what to link.

## Launcher side: milestone 1 is square (2026-11-28)

`upp_runtime` exists: `src/runtime/` in UPP. All five points of milestone 1 are done and checked
by a small C test game (`tests/runtime_selftest.c`, run by `ctest`), including every square of
[upp_integration.md](upp_integration.md). The details are in UPP's `docs/runtime.md`, "Building a
port against upp_runtime".

| Point | Status |
|---|---|
| 1. Start-up and release | Done. The EU image gives `eu-1.00` with the expected SHA-1; an unknown disc stops with a message; `thread_model` 0 is refused. |
| 2. Disc | Done. `SLES_546.24` = 3,529,520 bytes; `SYSTEM.CNF`, `LINKDATA.BNS` size and first sector, and a sector read agree; `cdrom0:\sles_546.24;1` works; a missing path gives -1. |
| 3. Logging, fatal, options | Done. `log.txt` in the data folder; `fatal()` logs, shows a message box, exits with code 3. |
| 4. PS2 threads, events, mutexes | Done. The run token, priorities, a wake-up switching at once, `thread_sleep` after an early wake-up, polls that never block, timed waits, mutex hand-over and priority changes all happen in the PS2 order. |
| 5. Pacing, vblank, window | Done. The 50 Hz tick runs on its own clock, also while a thread is busy or blocked, and `intr_disable` holds it. `video_present` works from a vblank callback. A 4:3 window; closing makes `vsync()` return 0. |

### How to build and link

1. Build UPP: `cmake -S <UPP> -B <UPP>/build/release && cmake --build <UPP>/build/release`.
2. Build SW2EPC against it:
   `py tools/pc_build.py --runtime "@<UPP>/build/release/upp_runtime.rsp" --upp-include <UPP>/include/upp`
   - `upp_runtime.rsp` is a GCC response file that lists everything to link: the runtime,
     `upp_core`, SDL3 and libstdc++ (both static), and the system libraries.
   - The plain `gcc` link line in `pc_build.py` works as it is.
3. Run with the manifests and the DLL. The runtime finds the game's manifest in `games/` next to
   the executable, or through `--games <UPP>/games`. With MinGW, `libwinpthread-1.dll` must sit
   next to `sw2epc.exe`; UPP's build copies it to `build/release/bin`.

`port/upp/upp.h` is unchanged: UPP's header did not change for milestone 1.

### One fix needed here before the link works

The link fails today with `multiple definition of 'CreateThread'`. `ps2_kernel.c` defines four EE
kernel calls whose names are also Windows kernel32 functions:

- `CreateThread`
- `ExitThread`
- `TerminateThread`
- `GetThreadId`

The runtime creates its own threads through the real `CreateThread`, so these names cannot be
defined in the game. If the link went through, the runtime's threads would land in the PS2 code.

Suggested fix: rename them in the port, for example `ee_CreateThread`. Then map the original
names in the game's own headers, for example `#define CreateThread ee_CreateThread`. The
decompiled sources keep reading as before.

Check: the four names were renamed in a scratch copy of `build/pc/obj/` with
`objcopy --redefine-sym`, and nothing else was touched. With that copy, `sw2epc.exe` links with
the real runtime and gives exactly the expected log of step 4:

```
[info] disc: ...Samurai Warriors 2 Empire.iso (ISO (2048)), release eu-1.00, SLES-54624 1.00, boot SLES_546.24
[info] segment 0x00100000: 0x35D180 bytes from the disc
[info] segment 0x007C0000: 0x0 bytes from the disc
[info] boot executable loaded (3529520 bytes)
[fatal] not decompiled yet: func_0011DFB0
```

No other clash with kernel32 was found among the game's symbols.

### Next on the UPP side (milestone 2)

Pads (keyboard and gamepads), then audio (`audio_push`, `audio_queued`), then the `save_*`
calls. Until then they are safe placeholders: no pad connected, sound dropped, saves refused,
and each one is logged once.

## This project: milestone 1 checked (2026-11-28)

The runtime of UPP commit 5e411f7 is checked from this side. SW2EPC links against
`build/release/upp_runtime.rsp` and runs on the EU disc:

- the disc is identified as `eu-1.00`;
- the game thread starts and the boot executable is loaded;
- the program stops through `fatal()` at the first function SW2EPC has not written yet
  (`func_0011DFB0`).

The kernel32 name clash noted in UPP's `docs/runtime.md` is fixed here: the EE kernel calls are
`ee_` names on the PC build (`src/sw2e_ee_kernel.h`). How to build and run is in
[upp_integration.md](upp_integration.md).

Nothing more is needed from UPP for milestone 1. Milestone 2 (pads, audio, saves) will be needed
when the game reaches its title screen. This side now works on the PC replacements of the Sony
libraries, starting with CD and IOP.

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
- 2026-11-27: this project lists the interrupt handlers and callbacks; asks for a vblank callback
  hook in `vsync()`; frame rate evidence is mixed (50 and 60 Hz).
- 2026-11-27: launcher side accepted the vblank hook, run on the runtime's own clock, with
  `intr_disable` / `intr_enable` and `set_frame_rate`. Interface final for platform version 1.
- 2026-11-27: this project agrees; interface final for platform version 1 (note: `video_present()`
  must be callable from a vblank callback without blocking).
- 2026-11-27: launcher side took the `video_present()` note and wrote down the launcher's final
  goal (many games, many releases, QoL options) and what it means for this port
  (`platform->release()`, per-release support, options defaulting to the original behaviour).
- 2026-11-27: this project agrees with the final goal: one source with per-release data (boot
  executable data loaded from the player's disc), EU release identity, QoL ideas.
- 2026-11-27: summary of the agreed version 1 contract added at the top (what each side does).
- 2026-11-27: launcher side checked the summary: `qol.fast_loading` default fixed to false,
  `display.progressive` added, dev mode identifies the disc; question on PS2 addresses inside
  the loaded tables (64-bit).
- 2026-11-27: this project agrees with the launcher's changes and chooses a 64-bit build with one
  PS2 memory block and `PS2_PTR` / `PS2_ADDR` for stored addresses.
- 2026-11-28: this project wrote `port/upp/upp.h` (the version 1 interface) and a stand-in
  runtime, and made the first PC build: everything links, and the program runs until the first
  Sony library call.
- 2026-11-28: this project added [upp_integration.md](upp_integration.md) (how to plug the port
  into the UPP runtime) and `--runtime` / `--upp-include` in `tools/pc_build.py`.
- 2026-11-28: UPP took over `upp.h` (reference: UPP `include/upp/upp.h`, still version 1) with
  `size` fields, thread model values, `region`, `fatal`, `ticks_us`, `audio_queued`,
  `event_count` and the PS2 thread calls; `SleepThread` as a yield flagged as a hang risk.
- 2026-11-28: this project adopted UPP's `include/upp/upp.h` (size fields, `fatal`, `event_count`,
  PS2 thread calls); built and run against UPP's own copy of the header.
- 2026-11-28: this project listed what it needs from the runtime first (milestone 1, in
  [upp_integration.md](upp_integration.md)).
- 2026-11-28: launcher side accepted milestone 1 and started the runtime; clarified that vblank
  callbacks run in interrupt context (not holding the run token) and the run() thread priority.
- 2026-11-28: launcher side: milestone 1 of `upp_runtime` built and checked; how to link
  (`upp_runtime.rsp`); `CreateThread`, `ExitThread`, `TerminateThread` and `GetThreadId` clash
  with kernel32 and need a prefix here.
- 2026-11-28: this project checked UPP milestone 1 (commit 5e411f7): SW2EPC links and runs with
  the real runtime; EE kernel calls renamed `ee_*` on the PC build (kernel32 clash).
