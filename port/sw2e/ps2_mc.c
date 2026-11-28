/*
 * ps2_mc.c - Sony's memory card library (libmc: sceMc...) for the PC build.
 *
 * The memory card will be made of the platform's save folders (upp_platform's save_* calls,
 * UPP milestone 2): one memory-card style folder per save, the game's own files in it. Until
 * then the library starts up and every request finds no card (result -10). Generic for PS2 games.
 */
#include "upp.h"

extern const upp_platform *sw2e_platform;

/* sceMcInit: 0 = ok */
int func_00141348(void)
{
    return 0;
}

/* ---- requests: until the save folders exist, every request finds no card ----
 * Like the real library, a request only starts the command; sceMcSync gives its result. */

#define MC_NO_CARD (-10)

static int g_cmd;                      /* the command under way (0: none) */
static int g_result;

static int start(int cmd, int result)
{
    if (g_cmd != 0)
        return -0xC8;                  /* busy */
    g_cmd = cmd;
    g_result = result;
    return 0;
}

/* sceMcGetInfo(port, slot, type, free, format) */
int func_00141EB8(int port, int slot, int *type, int *free_, int *format)
{
    (void)port; (void)slot;
    if (type)
        *type = 0;
    if (free_)
        *free_ = 0;
    if (format)
        *format = 0;
    return start(1, MC_NO_CARD);
}

int func_00141758(int port, int slot, const char *name, int mode)    /* sceMcOpen */
{
    (void)port; (void)slot; (void)name; (void)mode;
    return start(2, MC_NO_CARD);
}

int func_00141880(int port, int slot, const char *name)              /* sceMcMkdir */
{
    (void)port; (void)slot; (void)name;
    return start(0xB, MC_NO_CARD);
}

int func_001418B8(int fd) { (void)fd; return start(3, MC_NO_CARD); }                   /* sceMcClose */
int func_00141978(int fd, int offset, int origin)                                       /* sceMcSeek */
{ (void)fd; (void)offset; (void)origin; return start(4, MC_NO_CARD); }
int func_00141B08(int fd, void *buffer, int size)                                       /* sceMcRead */
{ (void)fd; (void)buffer; (void)size; return start(5, MC_NO_CARD); }
int func_00141C20(int fd, const void *buffer, int size)                                 /* sceMcWrite */
{ (void)fd; (void)buffer; (void)size; return start(6, MC_NO_CARD); }
int func_001420A8(int port, int slot, const char *name, unsigned int mode, int max, void *table)   /* sceMcGetDir */
{ (void)port; (void)slot; (void)name; (void)mode; (void)max; (void)table; return start(0xD, MC_NO_CARD); }
int func_001423C8(int port, int slot) { (void)port; (void)slot; return start(0x10, MC_NO_CARD); }  /* sceMcFormat */
int func_001425B8(int fd) { (void)fd; return start(0xA, MC_NO_CARD); }                  /* sceMcFlush */

/* sceMcSync(mode, cmd, result): 1 = the command is over, -1 = none under way */
int func_00141D98(int mode, int *cmd, int *result)
{
    (void)mode;
    if (g_cmd == 0)
        return -1;
    if (cmd)
        *cmd = g_cmd;
    if (result)
        *result = g_result;
    g_cmd = 0;
    return 1;
}
