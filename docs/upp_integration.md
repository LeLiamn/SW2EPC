# Plugging SW2EPC into UPP

A guide for the UPP (UnifiedPortProject) side. It describes what this project built on
2026-11-28 and how to replace its stand-in runtime with the real `upp_runtime`. The contract
itself, and the discussion that led to it, are in [launcher.md](launcher.md); this file is the
practical side.

## What exists on the SW2EPC side

| Path | Role | Owner |
|---|---|---|
| `port/upp/upp.h` | The platform version 1 interface, in plain C, written from the agreed contract | **To move to UPP** |
| `port/stub/upp_stub.c` | A stand-in `upp_runtime` for development: `main()`, ISO 9660 reading, logging; no window, sound or threads | Temporary, replaced by UPP |
| `port/sw2e/sw2e_entry.c` | `upp_game_entry()`, the 32 MB PS2 RAM block, loading the boot executable from the disc, `run()` | SW2EPC |
| `port/sw2e/ps2_kernel.c` | The EE kernel calls (semaphores, threads, DMA handlers, cache) on top of `upp_platform` | SW2EPC (generic for PS2 games) |
| `port/sw2e/pc_hw.c` | PC equivalents of the game's inline VU0 code | SW2EPC |
| `src/` | The decompiled game, rewritten for the PC by `tools/pc_rewrite.py` | SW2EPC |
| `tools/pc_build.py` | Builds `build/pc/sw2epc.exe` and writes [pc_build.md](pc_build.md) | SW2EPC |

### Where things stand

- All 160 source files compile as 64-bit C, and everything links.
- Run on the EU disc, the program:
  1. loads the player's boot executable into the PS2 memory block;
  2. enters the decompiled `main()`;
  3. stops at the first Sony library call (`func_0011DFB0`, CD and DMA).
- Every function that is not decompiled yet stops the program with its name, so a run shows the
  next piece to write.
- **Nothing is shown yet.** The stand-in has no window, and the game's drawing (GS and VU1) is
  not translated yet.

## Step 1: take over `upp.h`

**Done on the UPP side (2026-11-28, UPP commit f6b0e80):** `include/upp/upp.h` is now the
reference. SW2EPC follows it: `port/upp/upp.h` is a copy of it, and the port was adapted to the
changes (`size` fields, `fatal`, `event_count`, the PS2 thread calls). The original description
of the draft is kept below.

`port/upp/upp.h` follows the version 1 contract (see "Agreed contract, version 1" in
[launcher.md](launcher.md)):

- **`upp_game_api`**: `version`, `game_id`, `frame_rate`, `thread_model`, `init`, `frame` or
  `run`, `shutdown`.
- **`upp_game_entry()`**: the one symbol the game exports.
- **`upp_release`**: id, serial, version, path of the boot executable, its SHA-1.
- **`upp_pad`**: the DualShock 2 buttons in the PS2 report's bit order, the sticks (0x80 =
  centre) and 12 pressures.
- **`upp_platform`**, the table the runtime fills:
  - logging (`log(level, fmt, ...)`), `release()`, `option_bool`, `option_number`,
    `option_string`;
  - `vsync`, `video_present`, `set_frame_rate`, `frame_count`, `vblank_add`, `vblank_remove`,
    `intr_disable`, `intr_enable`;
  - `audio_push`;
  - `pad_read`, `pad_rumble`;
  - the disc: `disc_file_size`, `disc_read_file`, `disc_file_lsn`, `disc_read_sectors`;
  - `save_list`, `save_read`, `save_begin`, `save_write`, `save_end`, `save_delete`;
  - `thread_create`, `thread_join`, `thread_yield`, `sleep_us`, `event_create`, `event_wait`,
    `event_signal`, `event_destroy`, `mutex_create`, `mutex_lock`, `mutex_unlock`,
    `mutex_destroy`.

What to do:

1. Copy `port/upp/upp.h` into the UPP repository, or change it there to match UPP's own choices.
   Any change to names, argument order or the field order of `upp_platform` must be noted in
   [launcher.md](launcher.md).
2. Keep `UPP_PLATFORM_VERSION` at 1 for this contract, and give later changes a new version.
3. Once UPP owns the header, SW2EPC builds against UPP's copy (`--upp-include`, below), and
   `port/upp/upp.h` here stays only as a reference.

## Step 2: what the runtime must do for SW2E today

### Starting up

1. **`main()`**: parse `--disc <image>`, or read `launch.json` when started by the launcher.
2. **Identify the disc.** Read the boot executable named in `SYSTEM.CNF` and compare its serial,
   version and SHA-1 with the manifest.
   - The EU release is `SLES-54624` 1.00, boot executable `SLES_546.24`.
   - Its SHA-1 is `346e805e6b6b9b00c0df31d12659c59fcb55020d`.
   - Fill `release()` with what was found. The stand-in only returns a fixed EU record and
     checks nothing.
3. **Call `upp_game_entry()`** and check `version == 1`.
4. **Call `init(&platform)` on the main thread.** It returns 1 on success and 0 on failure (the
   reason is logged). SW2E's `init` does three things:
   - allocates 32 MB for the PS2 RAM and 16 KB for the scratchpad;
   - reads the boot executable through `disc_file_size` / `disc_read_file`;
   - copies its ELF segments to their PS2 addresses.
5. **SW2E fills `run()`, not `frame()`.** The runtime calls `run()` on a game thread it creates,
   with `thread_model = UPP_THREADS_PS2` and `frame_rate = 50.0`.
6. **At the end**, call `shutdown()`. It frees the memory blocks.

### Platform calls SW2E uses so far

| Call | Used by | For |
|---|---|---|
| `log` | everywhere | messages; level 0 = error, 1 = warning, 2 = info, 3 = debug |
| `release` | `sw2e_entry.c` | the path of the boot executable |
| `disc_file_size`, `disc_read_file` | `sw2e_entry.c` | loading the boot executable |
| `event_create`, `event_wait`, `event_signal`, `event_destroy` | `ps2_kernel.c` | the game's semaphores (`CreateSema`, `WaitSema`, `SignalSema`, `PollSema` = wait with timeout 0) |
| `event_count` | `ps2_kernel.c` | `ReferSemaStatus`, `iReferSemaStatus` |
| `thread_create` | `ps2_kernel.c` | `StartThread` (a PS2 thread is created dormant by `CreateThread`, then started) |
| `thread_self`, `thread_set_priority`, `thread_sleep`, `thread_wakeup`, `thread_exit`, `thread_terminate` | `ps2_kernel.c` | `GetThreadId`, `ChangeThreadPriority`, `SleepThread`, `WakeupThread` / `iWakeupThread`, `ExitThread`, `TerminateThread` |
| `intr_enable` | `pc_hw.c` | the EI at the end of the game's interrupt handlers |
| `fatal` | `sw2e_entry.c` | the stop of a function not decompiled yet (no `exit()` in game code) |
| `version`, `size` | `sw2e_entry.c` | `init` refuses a platform table older than the header it was built with |

More calls will be used as the Sony library replacements are written (disc reads, pads, audio,
`vsync` and `video_present`, saves), in that order. Each will be added to this table.

### What the game expects from those calls

- **`event_wait(id, -1)`** blocks until the event can be taken. **`event_wait(id, 0)`** returns
  at once, with 1 if it took one count and 0 if not.
- **Events count** like PS2 semaphores: `event_create(initial, max)`.
- **Thread priorities** follow the PS2 scale, 1 = highest. The game creates a disc reader
  thread (priority 5) and a movie thread (priority 2) early on.
- **Threads run one at a time**, the run token changing hands only at the blocking points of
  the contract. The game relies on this: it shares lists between threads without locks.
- **`intr_enable` may be called from a vblank callback.**

## Step 3: build SW2EPC against the UPP runtime

The build needs:

- **GCC or Clang**, 64-bit (tested: MinGW-w64 GCC 15.2 on Windows), and Python 3.
- **These flags**, set by `tools/pc_build.py`: `-m64 -DSW2E_PC -std=gnu99 -fno-strict-aliasing
  -fwrapv -fcommon`.
  - `-fno-strict-aliasing` and `-fwrapv` are needed: the decompiled code reads the same memory
    through different types and relies on wrap-around arithmetic, as the PS2 code did.
  - `-fcommon` merges the PC variables some files declare for function pointers.
- MSVC has not been tried. The code uses GCC extensions (`-std=gnu99`).

Commands:

```sh
# with the stand-in (today)
py tools/pc_build.py --disc <image>

# with the UPP runtime: a static library, objects, or C sources
py tools/pc_build.py --runtime path/to/libupp_runtime.a --upp-include path/to/upp/include --disc <image>
py tools/pc_build.py --runtime path/to/upp_runtime.c --upp-include path/to/upp/include
```

- With `--runtime`, `port/stub/` is left out.
  - C sources are compiled with the flags above and the `--upp-include` folder.
  - Libraries and objects are linked as given. If the runtime needs SDL or OS libraries, pass
    them too: every item of `--runtime` that is not a `.c` goes to the link line.
- The result is `build/pc/sw2epc.exe`. The report [pc_build.md](pc_build.md) is rewritten each
  time and, with `--disc`, ends with the log of a first run.
- If UPP builds with CMake or another tool, take the object list from `build/pc/obj/`:
  - every `.o` except `port_upp_stub.o`;
  - `missing.o`, generated: the stops for undecompiled functions and the table of functions by
    PS2 address.
  Then link them with `upp_runtime`.

## Step 4: check that it works

Run `sw2epc.exe --disc <image>` (or let the launcher start it). With the runtime plugged in, the
log should show, in this order:

```
[info] segment 0x00100000: 0x35D180 bytes from the disc
[info] segment 0x007C0000: 0x0 bytes from the disc
[info] boot executable loaded (3529520 bytes)
[error] not decompiled yet: func_0011DFB0
```

Since UPP added `fatal()` (2026-11-28), the last line goes through it: the stand-in prints
`[fatal] not decompiled yet: func_0011DFB0`, and the real runtime also shows it to the player.

The last line is expected today: it is the next function this project has to write (the Sony CD
and DMA library). The run stops there with exit code 3.

## Known limits, to remove later

- **`sw2e_missing()` called `exit(3)`.** The contract says the game never calls `exit()`. This
  stop is a development aid and goes away once every function is written. If the runtime
  prefers, it can export a hook so the game reports the stop and returns from `run()` instead.
  Tell us here.
  - **Settled (2026-11-28):** it now calls `platform->fatal()`, added by UPP for this.
- **Function tables in PS2 data** (`sw2e_fntab`) are read once, when first used. A table the game
  rewrites later (none seen so far) would keep its old entries.
- **The VU0 matrix order** in `pc_hw.c` comes from the 3D model data (T × Rz × Ry × Rx). It still
  has to be checked against the VU0 microcode.
- **Threads** have not run yet, because the stand-in has none. The first real test of the PS2
  thread mode will be with the UPP runtime.
- **Dual-layer discs**: the stand-in reads only the first layer (enough for SW2E).

## What would help most from the UPP side

In this order:

1. **A runtime with a window**, `video_present` and `vsync`, plus the disc calls.
2. **Threads and events in the PS2 mode** (run token, priorities). The game starts its disc
   thread before its first frame.
3. **Pads**, then **audio** and **saves**.

Report progress, questions or changes in [launcher.md](launcher.md) (dated section plus a line
in its changes log), as before.

## Milestone 1 checked with SW2EPC (2026-11-28, UPP commit 5e411f7)

SW2EPC links and runs with the real `upp_runtime`.

```sh
py tools/pc_build.py --runtime @<UPP>/build/release/upp_runtime.rsp --upp-include <UPP>/include/upp
cp <UPP>/build/release/bin/libwinpthread-1.dll build/pc/
build/pc/sw2epc.exe --disc "Iso/<image>.iso" --games <UPP>/games --data-dir build/pc/data [--headless]
```

- The runtime identifies the disc itself (`eu-1.00`, SLES-54624 1.00, boot `SLES_546.24`) and
  starts `run()` on its game thread. No `--run` is needed: that flag belongs to the stand-in.
- The game loads its boot executable and stops where expected, through `fatal()` (exit code 3,
  also written to `log.txt` in the data folder):
  `[fatal] not decompiled yet: func_0011DFB0`.
- **Changed on this side for it:** the EE kernel calls now have PC names (`ee_CreateThread`...,
  in `src/sw2e_ee_kernel.h`, included by `src/sw2e_mem.h` on the PC build). As UPP pointed out,
  `CreateThread`, `ExitThread`, `TerminateThread` and `GetThreadId` are also kernel32 functions on
  Windows.
- Without `--runtime`, `tools/pc_build.py` still links the stand-in in `port/stub/`, so the port
  builds without the UPP repository.

Nothing more is needed from UPP for now. The threads and the vblank tick get their first real use
once SW2EPC has replaced the Sony CD and IOP libraries (the disc reader thread). Pads, audio and
saves (milestone 2) are needed when the game reaches its title screen.

## What SW2EPC needs from the UPP runtime: milestone 1 (2026-11-28)

The smallest runtime that lets SW2EPC go on. It is the target for the work starting on the UPP
side now. Everything in it is generic for PS2 ports; nothing is SW2E-only. Each point says how to
check that it is done ("square"), without waiting for the game.

### Needed, in this order

1. **Start-up and release.**
   - What: `main()` with `--disc <image>`. Read `SYSTEM.CNF`, find the boot executable, compute
     its SHA-1 and match it against `games/sw2e/game.json` (`eu-1.00`). Fill `release()`, then
     call `upp_game_entry()`, check `version` and `size`, and call `init()`.
     `--force-release <id>` as agreed.
   - Square when: the EU image gives `eu-1.00` with the SHA-1
     `346e805e6b6b9b00c0df31d12659c59fcb55020d`. An unknown image stops with a clear message.
     A game table with `thread_model` = 0 is refused.
2. **The disc.**
   - What: `disc_file_size`, `disc_read_file`, `disc_file_lsn` and `disc_read_sectors`, thread-safe.
     Paths are case-insensitive, without `;1`, and may contain folders. Reads give the run token
     up while reading.
   - Square when: `SLES_546.24` reads as 3,529,520 bytes. `SYSTEM.CNF`, `LINKDATA.BNS` (size and
     first sector) and a sector read at the same position give the same bytes. A missing path
     gives -1.
3. **Logging, fatal, options.**
   - What: `log` (levels 0-3, `debug.log_level`, allowed from a vblank callback), `fatal(fmt, ...)`
     (logged, shown, clean end, never returns), and `option_bool / number / string` with the
     fallback when the key is unknown.
   - Square when: `fatal` from the game thread ends the process cleanly with the message.
4. **Threads, events and mutexes in the PS2 mode.** This is the most important point: the game
   starts a disc reader thread (priority 5) and waits on semaphores before its first frame.
   - What: the run token. Only the token holder runs game code, and switches happen only at the
     blocking calls and at the wake-ups that make a higher-priority thread ready.
     - `thread_create` starts at once and returns ids from 1; the `run()` thread is 0.
     - Also needed: `thread_join`, `thread_yield`, `sleep_us`, `thread_self`,
       `thread_set_priority`, `thread_sleep` (a wake-up sent first is kept),
       `thread_wakeup` [irq], `thread_exit`, `thread_terminate`.
     - Events: `event_create(initial, max)`, `event_wait` (-1 = forever, 0 = poll),
       `event_signal` [irq], `event_count` [irq], `event_destroy`.
     - Mutexes: create, lock, unlock, destroy.
   - Square when, with a small test game:
     - two threads of different priorities hand a counter back and forth through events, in the
       order the PS2 would give;
     - a higher-priority thread woken by `event_signal` runs before the signaller goes on;
     - `thread_sleep` after an early `thread_wakeup` does not block;
     - `event_wait(id, 0)` never blocks.
5. **Frame pacing, vblank and a window.**
   - What:
     - `vsync()`: present, wait for the next tick (50.0 for SW2E), sample the pads, and return 0
       when the window closes. The game then has 2 s to leave `run()`.
     - `video_present(rgba, w, h, pitch)` [irq], never blocking. A picture can be any size
       (SW2E's frame size is still to be read from its display set-up code).
     - `set_frame_rate`, `frame_count` [irq], `ticks_us` [irq].
     - `vblank_add` / `vblank_remove`, called on the runtime's own clock, holding the run token.
       The tick must also fire while the game thread is blocked elsewhere (loading), because the
       game's threads wait on a semaphore signalled from the vblank callback.
     - `intr_disable` / `intr_enable` [irq]: the tick waits while disabled.
   - Square when:
     - a test game showing a moving gradient at 50 Hz runs smoothly;
     - its vblank callback counts 50 ticks a second, even while the game thread sits in
       `event_wait`;
     - closing the window makes `vsync()` return 0.

### Can wait (milestone 2 and later)

- **Pads** (`pad_read`, `pad_rumble`): needed when the title screen is reached.
- **Audio** (`audio_push`, `audio_queued`, 48 kHz).
- **Saves** (`save_*`).
- **The 3D path** (platform version 2), once the SW2EPC renderer starts.
- Dual-layer discs, the launcher's own menu, `launch.json`. The dev mode `--disc` is enough for
  now.

### How to try it with SW2EPC

1. Build the runtime as a static library, objects, or a few C files.
2. In this repository: `py tools/pc_build.py --runtime <UPP lib or .c files> --upp-include
   <UPP>/include/upp --disc "Iso/<image>.iso"`.
3. Expected today: the log shows the boot executable loaded, then
   `[fatal] not decompiled yet: func_0011DFB0`. That means the runtime works up to the point
   where SW2EPC has to provide the next function. Anything that stops earlier, or a crash, is a
   runtime problem to look at together.
4. Once SW2EPC has replaced the CD and IOP libraries, the same command is the real test of the
   threads (the disc reader thread) and of the vblank tick.

### When milestone 1 is square

Write a dated section in [launcher.md](launcher.md) (or UPP's `docs/runtime.md`):

- which points are done;
- how to build the runtime: the CMake target name or the files, and the libraries it needs
  (SDL3, OS libraries);
- any change to `upp.h` (refresh `port/upp/upp.h` from it).

SW2EPC then links against it, and the next round of work is checked with the real runtime.

## Sony library replacements: first runs on the UPP runtime (2026-11-28)

SW2EPC now replaces the Sony libraries the start-up needs, in `port/sw2e/`, on top of the platform
calls:

| File | What it replaces | Platform calls used |
|---|---|---|
| `ps2_iop.c` | IOP boot and modules, CD (`sceCdSearchFile`, `sceCdRead`...), C library files on `cdrom0:`, DMA channels | `disc_file_lsn`, `disc_file_size`, `disc_read_sectors`, `disc_read_file` |
| `ps2_kernel.c` | threads, semaphores, interrupt handlers, alarms | `thread_*`, `event_*`, `intr_*` |
| `ps2_gs.c` | libgraph start-up, vsync, GS / VIF1 packet sends (counted, not drawn) | `vblank_add`, `vsync` |
| `ps2_pad.c` | libpad | `pad_read`, `pad_rumble` |
| `ps2_sound.c` | the sound driver's requests (accepted, nothing played) and its command encoders | — |
| `ps2_mc.c` | libmc: every request finds no card (result -10) until `save_*` exists | — |
| `ps2_libc.c` | heap, strings, `sprintf`, maths, GCC's software doubles | `log` |
| `pc_hw.c` | VU0 macro code and libvu0 matrices | — |

With the UPP runtime (`--headless`), the game:

1. loads its boot executable and boots the IOP;
2. sets up the GS (PAL, interlaced, field) and its vblank handler on `vblank_add`;
3. starts its disc reader thread (priority 5) through `thread_create`, which signals the main
   thread with semaphores;
4. finds the three LINKDATA containers with `disc_file_lsn` and reads their headers;
5. runs its start-up (game state, sound front, stage tables...) and stops, through `fatal()`, at
   the first game function that is not decompiled yet. At the time of writing that is
   `func_00177F80`, the battle units' set-up.

The runtime's threads, events and vblank tick work for this. Nothing new is needed from UPP for
now. Milestone 2 (pads, audio, saves) becomes useful when the game reaches its title screen.

## Milestone 2 checked with SW2EPC (2026-11-28, UPP commit 4a566ff)

- `upp.h` only gained comments (pads, audio and saves rules); `port/upp/upp.h` is refreshed from
  it. No interface change, nothing to adapt.
- SW2EPC builds against the new `upp_runtime.rsp` (it now also links `upp_core`, for the saves)
  and runs as before, headless, up to `func_00177F80`. UPP's own tests pass (4 of 4).
- The pad format matches `port/sw2e/ps2_pad.c`: `upp_button` uses the PS2 bit order, the 12
  pressures are in the DualShock 2 report's order, sticks centred on 0x80.
- On the SW2EPC side, still to do: `ps2_mc.c` on `save_*` (the memory card still answers "no
  card"), and the sound player on `audio_push` once the game plays music.

Nothing more is needed from UPP for SW2EPC's next steps. The next shared piece is the display
(platform version 2), when the SW2EPC renderer starts.
