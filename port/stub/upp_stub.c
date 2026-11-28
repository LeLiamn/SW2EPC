/*
 * upp_stub.c - a minimal stand-in for upp_runtime, so the port can be linked and started before
 * the launcher's runtime exists. It implements the version 1 table of port/upp/upp.h only as far
 * as a first build needs:
 *   - main(): `--disc <image>` (and `--run` to start the game's run() on the main thread);
 *   - logging to stderr, options from `--opt key=value`;
 *   - the disc: ISO 9660 paths and 2048-byte sectors of the player's image (first layer);
 *   - frame pacing without a window, video / audio / pads / saves / threads as empty calls.
 * It is not the real runtime: no window, no sound, no threads. The UPP repository replaces it.
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "upp.h"

/* ---- logging and options ---------------------------------------------------------------------- */

static int g_log_level = 2;
static struct { char key[64]; char value[192]; } g_opts[32];
static int g_nopts;

static void stub_log(int level, const char *fmt, ...)
{
    static const char *names[] = { "error", "warning", "info", "debug" };
    va_list ap;

    if (level > g_log_level)
        return;
    fprintf(stderr, "[%s] ", names[level < 0 ? 0 : level > 3 ? 3 : level]);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

static const char *opt_find(const char *key)
{
    int i;

    for (i = 0; i < g_nopts; i++)
        if (strcmp(g_opts[i].key, key) == 0)
            return g_opts[i].value;
    return NULL;
}

static int stub_option_bool(const char *key, int fallback)
{
    const char *v = opt_find(key);

    return v ? (strcmp(v, "1") == 0 || strcmp(v, "true") == 0) : fallback;
}

static double stub_option_number(const char *key, double fallback)
{
    const char *v = opt_find(key);

    return v ? atof(v) : fallback;
}

static const char *stub_option_string(const char *key, const char *fallback)
{
    const char *v = opt_find(key);

    return v ? v : fallback;
}

/* ---- the disc (ISO 9660, first layer) --------------------------------------------------------- */

static FILE *g_disc;

static int stub_disc_read_sectors(uint32_t lsn, uint32_t count, void *buf)
{
    if (!g_disc || _fseeki64(g_disc, (long long)lsn * 2048, SEEK_SET) != 0)
        return 0;
    return fread(buf, 2048, count, g_disc) == count;
}

/* the directory record of `iso_path` ("SLES_546.24", "DIR/FILE.EXT"): its extent and size */
static int iso_find(const char *iso_path, uint32_t *lsn, uint32_t *size)
{
    uint8_t sec[2048];
    uint32_t dir_lsn, dir_size;
    char part[64];
    const char *p = iso_path;

    if (!stub_disc_read_sectors(16, 1, sec) || memcmp(sec + 1, "CD001", 5) != 0)
        return 0;
    dir_lsn = sec[156 + 2] | sec[156 + 3] << 8 | sec[156 + 4] << 16 | (uint32_t)sec[156 + 5] << 24;
    dir_size = sec[156 + 10] | sec[156 + 11] << 8 | sec[156 + 12] << 16 | (uint32_t)sec[156 + 13] << 24;
    while (*p == '/' || *p == '\\')
        p++;
    for (;;) {
        size_t n = strcspn(p, "/\\");
        uint32_t off, s;
        int found = 0, last = p[n] == 0;

        if (n == 0 || n >= sizeof(part))
            return 0;
        memcpy(part, p, n);
        part[n] = 0;
        for (s = 0; s < (dir_size + 2047) / 2048 && !found; s++) {
            if (!stub_disc_read_sectors(dir_lsn + s, 1, sec))
                return 0;
            for (off = 0; off < 2048 && sec[off] != 0; off += sec[off]) {
                const uint8_t *r = sec + off;
                int len = r[32];
                char name[64];
                int k;

                if (len >= (int)sizeof(name))
                    continue;
                for (k = 0; k < len; k++)
                    name[k] = (char)toupper(r[33 + k]);
                name[len] = 0;
                if (strchr(name, ';'))
                    *strchr(name, ';') = 0;
                for (k = 0; part[k]; k++)
                    part[k] = (char)toupper((unsigned char)part[k]);
                if (strcmp(name, part) == 0) {
                    dir_lsn = r[2] | r[3] << 8 | r[4] << 16 | (uint32_t)r[5] << 24;
                    dir_size = r[10] | r[11] << 8 | r[12] << 16 | (uint32_t)r[13] << 24;
                    found = 1;
                    break;
                }
            }
        }
        if (!found)
            return 0;
        if (last) {
            *lsn = dir_lsn;
            *size = dir_size;
            return 1;
        }
        p += n + 1;
    }
}

static int64_t stub_disc_file_size(const char *iso_path)
{
    uint32_t lsn, size;

    return iso_find(iso_path, &lsn, &size) ? (int64_t)size : -1;
}

static int64_t stub_disc_file_lsn(const char *iso_path)
{
    uint32_t lsn, size;

    return iso_find(iso_path, &lsn, &size) ? (int64_t)lsn : -1;
}

static int64_t stub_disc_read_file(const char *iso_path, uint64_t offset, void *buf, size_t n)
{
    uint32_t lsn, size;

    if (!iso_find(iso_path, &lsn, &size) || offset > size)
        return -1;
    if (n > size - offset)
        n = (size_t)(size - offset);
    if (_fseeki64(g_disc, (long long)lsn * 2048 + (long long)offset, SEEK_SET) != 0)
        return -1;
    return (int64_t)fread(buf, 1, n, g_disc);
}

/* ---- the rest: frame pacing without a window, empty calls ------------------------------------- */

static uint64_t g_frames;
static int g_frame_limit = 1;      /* --frames N: vsync() returns 0 after N frames */

static const upp_release *stub_release(void)
{
    static const upp_release r = { "eu-1.00", "SLES-54624", "1.00", "SLES_546.24",
        { 0x34, 0x6e, 0x80, 0x5e, 0x6b, 0x6b, 0x9b, 0x00, 0xc0, 0xdf,
          0x31, 0xd1, 0x26, 0x59, 0xc5, 0x9f, 0xcb, 0x55, 0x02, 0x0d },     /* not checked here */
        "Europe" };
    return &r;
}

static int stub_vsync(void) { return ++g_frames < (uint64_t)g_frame_limit; }
static void stub_video_present(const void *rgba, int w, int h, int pitch) { (void)rgba; (void)w; (void)h; (void)pitch; }
static void stub_set_frame_rate(double fps) { (void)fps; }
static uint64_t stub_frame_count(void) { return g_frames; }
static int stub_vblank_add(upp_vblank_fn fn, void *arg) { (void)fn; (void)arg; return 0; }
static void stub_vblank_remove(int id) { (void)id; }
static void stub_nop(void) {}
static void stub_audio_push(const int16_t *f, size_t n, int rate) { (void)f; (void)n; (void)rate; }
static void stub_pad_read(int port, upp_pad *out) { (void)port; memset(out, 0, sizeof(*out)); }
static void stub_pad_rumble(int port, int a, int b) { (void)port; (void)a; (void)b; }
static int stub_save_list(upp_save_info *out, int max) { (void)out; (void)max; return 0; }
static int64_t stub_save_read(const char *d, const char *f, void *b, size_t n) { (void)d; (void)f; (void)b; (void)n; return -1; }
static int stub_save_begin(const char *d) { (void)d; return 0; }
static int stub_save_write(const char *f, const void *d, size_t n) { (void)f; (void)d; (void)n; return 0; }
static int stub_save_end(int c) { (void)c; return 0; }
static int stub_save_delete(const char *d) { (void)d; return 0; }
static int stub_thread_create(upp_thread_fn fn, void *arg, int prio)
{
    (void)fn; (void)arg; (void)prio;
    stub_log(1, "thread_create: no threads in the stand-in runtime");
    return -1;
}
static void stub_thread_join(int id) { (void)id; }
static void stub_sleep_us(uint64_t us) { (void)us; }
static int stub_event_create(int initial, int max) { (void)initial; (void)max; return 0; }
static int stub_event_wait(int id, int64_t t) { (void)id; (void)t; return 1; }
static void stub_int_nop(int id) { (void)id; }
static int stub_mutex_create(void) { return 0; }

/* Calls added when UPP took the header over */
static void stub_fatal(const char *fmt, ...)
{
    va_list ap;

    fprintf(stderr, "[fatal] ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(3);
}
static uint64_t stub_ticks_us(void) { return (uint64_t)clock() * 1000000u / CLOCKS_PER_SEC; }
static int stub_audio_queued(void) { return 0; }
static int stub_event_count(int id) { (void)id; return 0; }
static int stub_thread_self(void) { return 0; }
static void stub_thread_set_priority(int id, int prio) { (void)id; (void)prio; }
static void stub_thread_wakeup(int id) { (void)id; }
static void stub_thread_exit(void) { stub_log(1, "thread_exit: no threads in the stand-in runtime"); }
static void stub_thread_terminate(int id) { (void)id; }

static const upp_platform g_platform = {
    .version = UPP_PLATFORM_VERSION,
    .size = sizeof(upp_platform),
    .log = stub_log,
    .release = stub_release,
    .option_bool = stub_option_bool,
    .option_number = stub_option_number,
    .option_string = stub_option_string,
    .vsync = stub_vsync,
    .video_present = stub_video_present,
    .set_frame_rate = stub_set_frame_rate,
    .frame_count = stub_frame_count,
    .vblank_add = stub_vblank_add,
    .vblank_remove = stub_vblank_remove,
    .intr_disable = stub_nop,
    .intr_enable = stub_nop,
    .audio_push = stub_audio_push,
    .pad_read = stub_pad_read,
    .pad_rumble = stub_pad_rumble,
    .disc_file_size = stub_disc_file_size,
    .disc_read_file = stub_disc_read_file,
    .disc_file_lsn = stub_disc_file_lsn,
    .disc_read_sectors = stub_disc_read_sectors,
    .save_list = stub_save_list,
    .save_read = stub_save_read,
    .save_begin = stub_save_begin,
    .save_write = stub_save_write,
    .save_end = stub_save_end,
    .save_delete = stub_save_delete,
    .thread_create = stub_thread_create,
    .thread_join = stub_thread_join,
    .thread_yield = stub_nop,
    .sleep_us = stub_sleep_us,
    .event_create = stub_event_create,
    .event_wait = stub_event_wait,
    .event_signal = stub_int_nop,
    .event_destroy = stub_int_nop,
    .mutex_create = stub_mutex_create,
    .mutex_lock = stub_int_nop,
    .mutex_unlock = stub_int_nop,
    .mutex_destroy = stub_int_nop,
    .fatal = stub_fatal,
    .ticks_us = stub_ticks_us,
    .audio_queued = stub_audio_queued,
    .event_count = stub_event_count,
    .thread_self = stub_thread_self,
    .thread_set_priority = stub_thread_set_priority,
    .thread_sleep = stub_nop,
    .thread_wakeup = stub_thread_wakeup,
    .thread_exit = stub_thread_exit,
    .thread_terminate = stub_thread_terminate,
};

int main(int argc, char **argv)
{
    const upp_game_api *game = upp_game_entry();
    const char *disc = NULL;

    if (game->version != UPP_PLATFORM_VERSION || game->size < (int)sizeof(upp_game_api)
        || (game->thread_model != UPP_THREADS_PS2 && game->thread_model != UPP_THREADS_PARALLEL)) {
        fprintf(stderr, "the game's table is not platform version %d\n", UPP_PLATFORM_VERSION);
        return 1;
    }
    int run = 0, i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--disc") == 0 && i + 1 < argc)
            disc = argv[++i];
        else if (strcmp(argv[i], "--run") == 0)
            run = 1;
        else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc)
            g_frame_limit = atoi(argv[++i]);
        else if (strcmp(argv[i], "--opt") == 0 && i + 1 < argc && g_nopts < 32) {
            const char *eq = strchr(argv[++i], '=');
            if (eq) {
                snprintf(g_opts[g_nopts].key, sizeof(g_opts[0].key), "%.*s", (int)(eq - argv[i]), argv[i]);
                snprintf(g_opts[g_nopts].value, sizeof(g_opts[0].value), "%s", eq + 1);
                g_nopts++;
            }
        }
    }
    g_log_level = (int)stub_option_number("debug.log_level", 2);
    if (!disc) {
        fprintf(stderr, "usage: %s --disc <image> [--run] [--frames N] [--opt key=value]\n", argv[0]);
        return 2;
    }
    g_disc = fopen(disc, "rb");
    if (!g_disc) {
        stub_log(0, "cannot open the disc image %s", disc);
        return 1;
    }
    stub_log(2, "%s, platform version %d (stand-in runtime)", game->game_id, UPP_PLATFORM_VERSION);
    if (!game->init(&g_platform)) {
        stub_log(0, "the game's init failed");
        return 1;
    }
    if (run) {
        if (game->run)
            game->run();
        else
            while (game->frame())
                ;
    }
    if (game->shutdown)
        game->shutdown();
    fclose(g_disc);
    return 0;
}
