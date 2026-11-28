/*
 * ps2_ipu.c - the IPU (the PS2's MPEG decoder) for the PC build.
 *
 * The game sends coded pictures to the IPU by DMA (channel 4) and receives 16 x 16 tiles of
 * 32-bit pixels (channel 3); the end of that transfer runs a DMAC handler that starts the next
 * decode (src/ipu_picture.c). On the PC, src/ipu_picture.c calls sw2e_ipu_receive() where it
 * starts channel 3; the transfer ends at once.
 *
 * Not decoded yet: the tiles are left black. The format (MPEG intra frames, the "ipu2" files) is
 * documented in docs/formats/IPU.md and decoded by tools/ipu.py; the C decoder comes with the
 * movie player. Generic for PS2 games.
 */
#include <string.h>
#include "upp.h"
#include "sw2e_mem.h"

extern const upp_platform *sw2e_platform;
int (*sw2e_dmac_handler(int channel))(int);

void sw2e_ipu_receive(unsigned int to, unsigned int qwc)
{
    static int logged;
    int (*done)(int) = sw2e_dmac_handler(3);

    if (!logged) {
        logged = 1;
        sw2e_platform->log(2, "IPU: pictures not decoded yet (black tiles)");
    }
    memset(PS2_PTR(to), 0, (size_t)(qwc & 0x3FFFFF) * 0x400);   /* qwc counts tiles of 16 x 16 x 4 bytes */
    if (done)
        done(3);
}
