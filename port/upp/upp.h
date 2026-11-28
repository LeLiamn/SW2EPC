/*
 * upp.h - the UPP (UnifiedPortProject) runtime interface, platform version 1.
 *
 * [SW2EPC] A copy of UPP's include/upp/upp.h (commit 4a566ff, 2026-11-28), kept here so the port
 * builds without the UPP repository. UPP's file is the reference: refresh this copy from it, or
 * build with `tools/pc_build.py --upp-include <UPP>/include/upp`.
 *
 * This is the reference copy. It started as SW2EPC's port/upp/upp.h (2026-11-28), written from
 * the contract agreed in docs/runtime.md, and was taken over here with the changes listed in
 * docs/runtime.md ("Changes from the SW2EPC draft").
 *
 * A port is one executable linked with upp_runtime. The runtime owns main(), the window, audio,
 * pads, disc access and launch.json; the game exports upp_game_entry() and reaches the outside
 * world only through the upp_platform table it is given.
 *
 * Only basic C types are used, so the interface can be implemented or used from any language.
 * Rules for later versions: fields are only ever added at the end of a structure, and `size`
 * tells either side which fields the other one knows.
 */
#ifndef UPP_H
#define UPP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UPP_PLATFORM_VERSION 1

/* ---- Game side ------------------------------------------------------------------------------ */

typedef struct upp_platform upp_platform;

enum upp_thread_model {
    /* 0 is not a model: a table that leaves the field unset is refused. */
    UPP_THREADS_PS2 = 1,        /* one run token: switches only at blocking points, by priority */
    UPP_THREADS_PARALLEL = 2    /* real OS threads, the game has its own locks */
};

typedef struct upp_game_api {
    int version;                /* UPP_PLATFORM_VERSION */
    int size;                   /* sizeof(upp_game_api) */
    const char *game_id;        /* the manifest id, e.g. "sw2e" */
    double frame_rate;          /* the starting tick rate (50.0 for a PAL game) */
    int thread_model;           /* enum upp_thread_model */
    /* Called once on the main thread before anything else: 1 = ok, 0 = failure (reason logged). */
    int (*init)(const upp_platform *platform);
    /* A game fills exactly one of frame() and run():
     *   frame(): one frame per call, on the main thread; returns 0 to quit;
     *   run():   runs on a game thread until it returns; leave it when platform->vsync()
     *            returns 0 (within 2 s, or the runtime ends the process). */
    int (*frame)(void);
    void (*run)(void);
    /* Called once on the main thread at the end. */
    void (*shutdown)(void);
} upp_game_api;

/* The one symbol a game exports. */
const upp_game_api *upp_game_entry(void);

/* ---- Release ---------------------------------------------------------------------------------- */

typedef struct upp_release {
    const char *id;             /* the manifest's release id, e.g. "eu-1.00" */
    const char *serial;         /* "SLES-54624" */
    const char *version;        /* "1.00" */
    const char *boot_path;      /* the boot executable on the disc, e.g. "SLES_546.24" */
    uint8_t boot_sha1[20];      /* SHA-1 of the boot executable */
    const char *region;         /* "Europe" */
} upp_release;

/* ---- Input ------------------------------------------------------------------------------------ */

/* DualShock 2 buttons, in the PS2 pad report's bit order (active high here: 1 = pressed). */
enum upp_button {
    UPP_BTN_SELECT = 1 << 0, UPP_BTN_L3 = 1 << 1, UPP_BTN_R3 = 1 << 2, UPP_BTN_START = 1 << 3,
    UPP_BTN_UP = 1 << 4, UPP_BTN_RIGHT = 1 << 5, UPP_BTN_DOWN = 1 << 6, UPP_BTN_LEFT = 1 << 7,
    UPP_BTN_L2 = 1 << 8, UPP_BTN_R2 = 1 << 9, UPP_BTN_L1 = 1 << 10, UPP_BTN_R1 = 1 << 11,
    UPP_BTN_TRIANGLE = 1 << 12, UPP_BTN_CIRCLE = 1 << 13, UPP_BTN_CROSS = 1 << 14,
    UPP_BTN_SQUARE = 1 << 15
};

typedef struct upp_pad {
    int connected;
    uint16_t buttons;           /* enum upp_button */
    uint8_t lx, ly, rx, ry;     /* sticks, 0x80 = centre */
    uint8_t pressure[12];       /* analog buttons: right, left, up, down, triangle, circle,
                                   cross, square, L1, R1, L2, R2 (0-255) */
} upp_pad;

/* ---- Saves ------------------------------------------------------------------------------------ */

typedef struct upp_save_info {
    char folder[64];            /* memory-card style folder name */
    uint64_t size;              /* bytes, all files */
    int64_t mtime;              /* seconds since 1970 */
} upp_save_info;

/* ---- Platform table (filled by the runtime) --------------------------------------------------- */

typedef void (*upp_thread_fn)(void *arg);
typedef void (*upp_vblank_fn)(void *arg);   /* runs in interrupt context: must not block */

/*
 * Calls marked [irq] may also be made in interrupt context (a vblank callback). Every other
 * call made there is an error, reported in the log.
 *
 * Thread ids: the thread running run() has id 0; thread_create returns ids from 1.
 */
struct upp_platform {
    int version;                /* UPP_PLATFORM_VERSION */
    int size;                   /* sizeof(upp_platform) as the runtime knows it */

    /* Logging (debug.log_level decides what is kept). level: 0 error, 1 warning, 2 info, 3 debug */
    void (*log)(int level, const char *fmt, ...);                           /* [irq] */

    /* Release and options */
    const upp_release *(*release)(void);
    int (*option_bool)(const char *key, int fallback);
    double (*option_number)(const char *key, double fallback);
    const char *(*option_string)(const char *key, const char *fallback);

    /* Frame pacing and video (version 1: one finished picture per frame) */
    int (*vsync)(void);                         /* present, wait for the next tick, sample pads;
                                                   0 = the window closes (leave run() within 2 s) */
    void (*video_present)(const void *rgba, int w, int h, int pitch);       /* [irq], never blocks */
    void (*set_frame_rate)(double fps);
    uint64_t (*frame_count)(void);                                          /* [irq] */
    int (*vblank_add)(upp_vblank_fn fn, void *arg);     /* returns an id, -1 when full (16) */
    void (*vblank_remove)(int id);
    void (*intr_disable)(void);                 /* DI: the tick waits */          /* [irq] */
    void (*intr_enable)(void);                  /* EI */                          /* [irq] */

    /* Audio: signed 16-bit stereo at any rate (the runtime resamples; 48000 needs no conversion).
       count is in frames (left + right pairs). Any thread. Past a second of sound queued, the
       queue is dropped: pace the pushes with audio_queued(). */
    void (*audio_push)(const int16_t *frames, size_t count, int rate);

    /* Input: two pads (port 0 and 1), state sampled at each tick, so a frame sees one state.
       Port 0 is the keyboard and the first gamepad, port 1 the second gamepad. Another port gives
       a pad that is not connected. Both calls: any thread. small_motor: 0 or 1; big_motor: 0-255;
       a motor runs until set to 0, as on the PS2. */
    void (*pad_read)(int port, upp_pad *out);
    void (*pad_rumble)(int port, int small_motor, int big_motor);

    /* Disc: the player's image, read-only, thread-safe. Reads give the run token up while
       reading. ISO 9660 paths are case-insensitive, without the ";1" version suffix. */
    int64_t (*disc_file_size)(const char *iso_path);                       /* -1 = not found */
    int64_t (*disc_read_file)(const char *iso_path, uint64_t offset, void *buf, size_t size);
    int64_t (*disc_file_lsn)(const char *iso_path);                        /* first sector */
    int (*disc_read_sectors)(uint32_t lsn, uint32_t count, void *buf);    /* 2048-byte sectors */

    /* Saves: one memory-card style folder per save, swapped in whole. Names (folders and files):
       1-63 bytes, no '/', '\' or other character Windows refuses. 1 = done, 0 = failed (logged).
       save_list: returns how many saves there are, fills up to max (out may be NULL).
       save_read: bytes read, -1 = no such save or file; buf NULL gives the file's size.
       save_begin: one save open at a time; it starts as a copy of the folder's current files.
       save_write: the first write of a file in an open save replaces it, later ones append.
       save_end: 1 swaps the new folder in, 0 drops it; after a failed write, 1 fails and the
       previous save stays. A crash at any point leaves the previous save or the new one. */
    int (*save_list)(upp_save_info *out, int max);
    int64_t (*save_read)(const char *folder, const char *file, void *buf, size_t size);
    int (*save_begin)(const char *folder);
    int (*save_write)(const char *file, const void *data, size_t size);
    int (*save_end)(int commit);
    int (*save_delete)(const char *folder);

    /* Threads (UPP_THREADS_PS2: priority 1 = highest, switches only at blocking calls) */
    int (*thread_create)(upp_thread_fn fn, void *arg, int priority);   /* returns an id, from 1 */
    void (*thread_join)(int id);
    void (*thread_yield)(void);                 /* let an equal-priority thread run */
    void (*sleep_us)(uint64_t us);
    int (*event_create)(int initial, int max);  /* a counting event, like a PS2 semaphore */
    int (*event_wait)(int id, int64_t timeout_us);   /* 1 = taken, 0 = timeout; -1 = forever */
    void (*event_signal)(int id);                                           /* [irq] */
    void (*event_destroy)(int id);
    int (*mutex_create)(void);
    void (*mutex_lock)(int id);
    void (*mutex_unlock)(int id);
    void (*mutex_destroy)(int id);

    /* ---- Added when UPP took the header over (still version 1) ---- */

    /* Stop the game with a message: logged, shown to the player, then the process ends.
       Never returns. Replaces exit() in game code. */
    void (*fatal)(const char *fmt, ...);

    /* Time: microseconds since start, monotonic. */
    uint64_t (*ticks_us)(void);                                             /* [irq] */

    /* Audio frames pushed but not played yet, to keep the mix in step with the ticks. */
    int (*audio_queued)(void);

    /* Count of an event right now (ReferSemaStatus); -1 = no such event. */
    int (*event_count)(int id);                                             /* [irq] */

    /* Threads, PS2 semantics */
    int (*thread_self)(void);                   /* id of the calling thread (0 = the run() thread) */
    void (*thread_set_priority)(int id, int priority);  /* takes effect at once (ChangeThreadPriority) */
    void (*thread_sleep)(void);                 /* SleepThread: blocks until woken; a wake-up sent
                                                   before the sleep is counted and not lost */
    void (*thread_wakeup)(int id);              /* WakeupThread / iWakeupThread */  /* [irq] */
    void (*thread_exit)(void);                  /* ExitThread: ends the calling thread, never returns */
    void (*thread_terminate)(int id);           /* TerminateThread: the thread never runs again */
};

#ifdef __cplusplus
}
#endif

#endif
