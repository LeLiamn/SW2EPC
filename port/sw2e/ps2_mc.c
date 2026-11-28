/*
 * ps2_mc.c - Sony's memory card library (libmc: sceMc...) for the PC build.
 *
 * The memory card will be made of the platform's save folders (upp_platform's save_* calls,
 * UPP milestone 2): one memory-card style folder per save, the game's own files in it. Until
 * then the library only starts up. Generic for PS2 games.
 */
#include "upp.h"

extern const upp_platform *sw2e_platform;

/* sceMcInit: 0 = ok */
int func_00141348(void)
{
    return 0;
}
