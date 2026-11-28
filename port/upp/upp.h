/*
 * upp.h - the UPP (UnifiedPortProject) runtime interface, platform version 1.
 *
 * Written on the SW2EPC side from the contract agreed in docs/launcher.md ("Agreed contract,
 * version 1"), so the first PC build can link before the launcher's runtime exists. It is meant
 * to move to the UPP repository as is: nothing in it is specific to one game.
 *
 * A port is one executable linked with upp_runtime. The runtime owns main(), the window, audio,
 * pads, disc access and launch.json; the game exports upp_game_entry() and reaches the outside
 * world only through the upp_platform table it is given.
 *
 * Only basic C types are used, so the interface can be implemented in any language.
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
    UPP_THREADS_PARALLEL = 0,   /* real OS threads, the game has its own locks */
    UPP_THREADS_PS2 = 1         /* one run token: switches only at blocking points, by priority */
};

typedef struct upp_game_api {
    int version;                /* UPP_PLATFORM_VERSION */
    const char *game_id;        /* "sw2e" */
    double frame_rate;          /* the rate the game logic expects (50.0 for a PAL game) */
    int thread_model;           /* enum upp_thread_model */
    /* Called once on the main thread before anything else; 0 = failure (the reason is logged). */
    int (*init)(const upp_platform *platform);
    /* A game fills exactly one of frame() and run():
     *   frame(): one frame per call, returns 0 to quit;
     *   run():   runs on a game thread until platform->vsync() returns 0. */
    int (*frame)(void);
    void (*run)(void);
    void (*shutdown)(void);
} upp_game_api;

/* The one symbol a game exports. */
const upp_game_api *upp_game_entry(void);

/* ---- Release ---------------------------------------------------------------------------------- */

typedef struct upp_release {
    const char *id;             /* the manifest's release id, e.g. "eu-sles-54624-1.00" */
    const char *serial;         /* "SLES-54624" */
    const char *version;        /* "1.00" */
    const char *boot_path;      /* the boot executable on the disc, e.g. "SLES_546.24" */
    uint8_t boot_sha1[20];      /* SHA-1 of the boot executable */
} upp_release;

/* ---- Input ------------------------------------------------------------------------------------ */

/* DualShock 2 buttons, in the PS2 pad report's bit order (active high here). */
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

struct upp_platform {
    int version;                /* UPP_PLATFORM_VERSION */

    /* Logging (debug.log_level decides what is shown). level: 0 error, 1 warning, 2 info, 3 debug */
    void (*log)(int level, const char *fmt, ...);

    /* Release and options */
    const upp_release *(*release)(void);
    int (*option_bool)(const char *key, int fallback);
    double (*option_number)(const char *key, double fallback);
    const char *(*option_string)(const char *key, const char *fallback);

    /* Frame pacing and video (version 1: one finished picture per frame) */
    int (*vsync)(void);                         /* present, wait for the next tick, sample pads;
                                                   0 = the window closes (leave run() within 2 s) */
    void (*video_present)(const void *rgba, int w, int h, int pitch);
    void (*set_frame_rate)(double fps);
    uint64_t (*frame_count)(void);
    int (*vblank_add)(upp_vblank_fn fn, void *arg);     /* returns an id, -1 when full */
    void (*vblank_remove)(int id);
    void (*intr_disable)(void);                 /* DI */
    void (*intr_enable)(void);                  /* EI */

    /* Audio: signed 16-bit stereo at any rate (the runtime resamples) */
    void (*audio_push)(const int16_t *frames, size_t count, int rate);

    /* Input: two pads */
    void (*pad_read)(int port, upp_pad *out);
    void (*pad_rumble)(int port, int small_motor, int big_motor);

    /* Disc: the player's image, read-only. Reads give the run token up while reading. */
    int64_t (*disc_file_size)(const char *iso_path);                       /* -1 = not found */
    int64_t (*disc_read_file)(const char *iso_path, uint64_t offset, void *buf, size_t size);
    int64_t (*disc_file_lsn)(const char *iso_path);                        /* first sector */
    int (*disc_read_sectors)(uint32_t lsn, uint32_t count, void *buf);    /* 2048-byte sectors */

    /* Saves: one memory-card style folder per save, swapped in whole */
    int (*save_list)(upp_save_info *out, int max);
    int64_t (*save_read)(const char *folder, const char *file, void *buf, size_t size);
    int (*save_begin)(const char *folder);
    int (*save_write)(const char *file, const void *data, size_t size);
    int (*save_end)(int commit);
    int (*save_delete)(const char *folder);

    /* Threads (UPP_THREADS_PS2: priority 1 = highest, switches only at blocking calls) */
    int (*thread_create)(upp_thread_fn fn, void *arg, int priority);   /* returns an id */
    void (*thread_join)(int id);
    void (*thread_yield)(void);
    void (*sleep_us)(uint64_t us);
    int (*event_create)(int initial, int max);  /* a counting event, like a PS2 semaphore */
    int (*event_wait)(int id, int64_t timeout_us);   /* 1 = taken, 0 = timeout; -1 = forever */
    void (*event_signal)(int id);
    void (*event_destroy)(int id);
    int (*mutex_create)(void);
    void (*mutex_lock)(int id);
    void (*mutex_unlock)(int id);
    void (*mutex_destroy)(int id);
};

#ifdef __cplusplus
}
#endif

#endif
