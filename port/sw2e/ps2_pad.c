/*
 * ps2_pad.c - Sony's pad library (libpad: pad...) for the PC build, on platform->pad_read().
 *
 * A pad the platform reports as connected is "stable" at once, already in DualShock 2 mode with
 * pressures (0x79): the game's set-up steps (analog mode locked, pressure mode, actuators)
 * succeed at the first try. padRead fills the 32-byte report in the PS2 format:
 *   [0] 0 = ok, [1] 0x79 (analog, pressure), [2..3] buttons, active low (PS2 bit order),
 *   [4] right X, [5] right Y, [6] left X, [7] left Y, [8..19] the 12 pressures.
 * Generic for PS2 games.
 */
#include <string.h>
#include "upp.h"

extern const upp_platform *sw2e_platform;
#define P sw2e_platform

enum { PAD_STATE_DISCONN = 0, PAD_STATE_STABLE = 6 };
enum { PAD_RSTAT_COMPLETE = 0 };

static int connected(int port)
{
    upp_pad p;

    if (port < 0 || port > 1)
        return 0;
    P->pad_read(port, &p);
    return p.connected;
}

int func_001708A8(int a) { (void)a; return 1; }                     /* padInit */
void func_00171E18(int a) { (void)a; }                              /* (after padInit) */
int func_00170B38(void) { return 1; }                               /* padEnd */
int func_00170D00(int port, int slot, unsigned char *buffer) { (void)port; (void)slot; (void)buffer; return 1; }   /* padPortOpen */
int func_00170EE8(int port, int slot) { (void)port; (void)slot; return 1; }      /* padPortClose */

/* padGetState(port, slot) */
int func_001711C8(int port, int slot)
{
    (void)slot;
    return connected(port) ? PAD_STATE_STABLE : PAD_STATE_DISCONN;
}

int func_00171330(int port, int slot) { (void)port; (void)slot; return PAD_RSTAT_COMPLETE; }   /* padGetReqState */
int func_00171728(int port, int slot, int mode, int lock) { (void)port; (void)slot; (void)mode; (void)lock; return 1; }   /* padSetMainMode */
int func_00171AE0(int port, int slot) { (void)port; (void)slot; return 1; }      /* padInfoPressMode: supported */
int func_00171B60(int port, int slot) { (void)port; (void)slot; return 1; }      /* padEnterPressMode */
int func_001718A8(int port, int slot, unsigned char *align) { (void)port; (void)slot; (void)align; return 1; }   /* padSetActAlign */

/* padSetActDirect(port, slot, levels): motor 0 (small, on/off) and motor 1 (big, 0-255) */
int func_001717E0(int port, int slot, unsigned char *levels)
{
    (void)slot;
    P->pad_rumble(port, levels[0] != 0, levels[1]);
    return 1;
}

/* padRead(port, slot, data): the 32-byte report; its size, or 0 without a pad */
int func_00171150(int port, int slot, unsigned char *data)
{
    upp_pad p;
    unsigned int raw;

    (void)slot;
    memset(data, 0, 32);
    if (port < 0 || port > 1)
        return 0;
    P->pad_read(port, &p);
    if (!p.connected)
        return 0;
    raw = ~(unsigned int)p.buttons & 0xFFFF;
    data[0] = 0;
    data[1] = 0x79;
    data[2] = raw & 0xFF;
    data[3] = raw >> 8;
    data[4] = p.rx;
    data[5] = p.ry;
    data[6] = p.lx;
    data[7] = p.ly;
    memcpy(data + 8, p.pressure, 12);
    return 32;
}
