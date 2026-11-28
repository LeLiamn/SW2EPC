/*
 * ps2_gs.c - the Sony graphics library calls (libgraph: sceGs...) for the PC build.
 *
 * The GS itself is not drawn yet: the packets the game builds and sends by DMA are not
 * translated. These calls keep the game's start-up and frame pacing going:
 *   - sceGsResetGraph records the video mode;
 *   - sceGsSyncV waits for the next frame through platform->vsync();
 *   - sceGsSyncPath returns at once (transfers end at once on the PC).
 * Generic for PS2 games.
 */
#include "upp.h"

extern const upp_platform *sw2e_platform;
void sw2e_quit(void);
#define P sw2e_platform

static int g_gs_omode = -1, g_gs_interlace, g_gs_ffmode;

/* sceGsResetGraph(mode, interlace, omode, ffmode): omode 2 = NTSC, 3 = PAL */
void func_001256D0(int mode, int interlace, int omode, int ffmode)
{
    if (omode != g_gs_omode)
        P->log(2, "GS video mode: %s, %s, %s (sceGsResetGraph mode %d)",
               omode == 3 ? "PAL" : omode == 2 ? "NTSC" : "other", interlace ? "interlaced" : "progressive",
               ffmode ? "field" : "frame", mode);
    g_gs_omode = omode;
    g_gs_interlace = interlace;
    g_gs_ffmode = ffmode;
}

/* sceGsSyncV(mode): waits for the next vertical blank; returns the field (0 even, 1 odd) */
int func_00126558(int mode)
{
    (void)mode;
    if (!P->vsync())
        sw2e_quit();                     /* the window closes: the game leaves run() */
    return (int)(P->frame_count() & 1);
}

/* sceGsSyncPath(mode, timeout): waits for the VIF1 and GIF transfers; 0 = done */
int func_001265F0(int mode, int timeout)
{
    (void)mode;
    (void)timeout;
    return 0;
}

/* ---- the rest of the start-up (graphics): to be written with the renderer ----
 * These set up the GS display and drawing environments in PS2 memory (structures the game then
 * edits and sends by DMA). They are left empty until the GS output is translated; each is logged
 * once so the renderer work knows what to fill in. */

static void once(const char *what)
{
    P->log(3, "GS: %s not translated yet", what);
}

/* sceGsSetDefDBuffDc(db, psm, w, h, ztest, zpsm, clear) */
void func_00127000(unsigned char *env, int psm, int w, unsigned short h, int ztest, int zpsm, int clear)
{
    (void)env; (void)psm; (void)w; (void)h; (void)ztest; (void)zpsm; (void)clear;
    once("sceGsSetDefDBuffDc");
}

/* sceGsSetDefDispEnv-like: a display environment */
void func_00125988(unsigned char *env, int a, int w, int h, int b, int c)
{
    (void)env; (void)a; (void)w; (void)h; (void)b; (void)c;
    once("display environment (0x00125988)");
}

void func_00125E88(void *env, int a, unsigned short w, unsigned short h, int b, int c)
{
    (void)env; (void)a; (void)w; (void)h; (void)b; (void)c;
    once("draw environment (0x00125E88)");
}

void func_00126D10(unsigned char *env, int a, int b, unsigned short field) { (void)env; (void)a; (void)b; (void)field; once("0x00126D10"); }
void func_00126F78(unsigned char *env, int a, int b, unsigned short field) { (void)env; (void)a; (void)b; (void)field; once("0x00126F78"); }
void func_001272E8(unsigned char *env, unsigned int field) { (void)env; (void)field; once("sceGsSwapDBuffDc (0x001272E8)"); }

/* sceGsGetGParam: the library's video parameters (a writable block; the game sets a field) */
unsigned char *func_00125860(void)
{
    static unsigned char gparam[64];

    return gparam;
}

/* ---- DMA sends: where the renderer will take the GS packets ---- */

static unsigned long long g_gif_packets, g_vif1_chains;

/* sceDmaSend(channel, data, qwc): a packet of qwc quadwords to the GIF (or another channel) */
void func_0011B3E8(int channel, void *data, unsigned int qwc)
{
    (void)channel; (void)data; (void)qwc;
    if (g_gif_packets++ == 0)
        P->log(2, "GS: first packet sent (not drawn yet)");
}

/* sceDmaSendChain-like (0x0011B380): a DMA chain to VIF1 (the 3D drawing) */
void func_0011B380(unsigned char *channel, unsigned int *chain)
{
    (void)channel; (void)chain;
    if (g_vif1_chains++ == 0)
        P->log(2, "GS: first VIF1 chain sent (not drawn yet)");
}

/* sceDmaSync-like (0x0011B690): waits for a channel; transfers end at once here */
int func_0011B690(unsigned char *channel) { (void)channel; return 0; }

/* ---- interrupts ---- */

/* DIntr: interrupts off; 1 when they were on */
int func_00131EA0(void)
{
    P->intr_disable();
    return 1;
}

/* EIntr */
void func_00131EF0(void)
{
    P->intr_enable();
}

/* 0x0010B198: adds a vertical blank callback int handler(int) to the chain (0x00560840 on the
 * PS2); on the PC the runtime's vblank tick calls it */
static void vblank_tramp(void *arg)
{
    ((int (*)(int))arg)(2);             /* INTC cause 2: the start of the vertical blank */
}

int func_0010B198(int (*handler)(int), int a)
{
    (void)a;
    return P->vblank_add(vblank_tramp, (void *)handler);
}

/* 0x0010B158: clears the vertical blank chain and installs its handler (0x0010B0F0); the
 * runtime's tick plays that role on the PC, and vblank_add holds the chain */
int func_0010B158(void) { return 0; }

int func_00128928(int cause) { (void)cause; return 0; }   /* EnableIntc */
int func_001289F8(int channel) { (void)channel; return 0; }   /* EnableDmac */

/* ---- more of libgraph: to be written with the renderer ---- */

void func_00126178(void *draw) { (void)draw; once("sceGsPutDrawEnv"); }
void func_001264F8(void *db, int field) { (void)db; (void)field; once("sceGsSwapDBuff"); }
void func_00126AF0(void *load, void *data) { (void)load; (void)data; once("sceGsExecLoadImage (texture upload)"); }

/* sceGsSetDefLoadImage(load, dbp, dbw, psm, x, y, w, h): fills the 0x60-byte packet that uploads
 * w x h pixels to GS memory (GIF tag A+D, BITBLTBUF, TRXPOS, TRXREG, TRXDIR, then the GIF tag of
 * the IMAGE data); returns 6, its size in quadwords. 0 when the image is over 0x7FFF quadwords. */
int func_00126908(void *load, short dbp, short dbw, short psm, short x, short y, short w, short h)
{
    unsigned long long *q = (unsigned long long *)load;
    long long qwc;

    switch (psm) {
    case 0x00: case 0x30: qwc = (long long)w * h >> 2; break;              /* 32 bits */
    case 0x01: case 0x31: qwc = (long long)w * h * 3 >> 4; break;          /* 24 bits */
    case 0x02: case 0x0A: case 0x32: case 0x3A: qwc = (long long)w * h >> 3; break;   /* 16 bits */
    case 0x13: case 0x1B: qwc = (long long)w * h >> 4; break;              /* 8 bits */
    case 0x14: case 0x24: case 0x2C: qwc = (long long)w * h >> 5; break;   /* 4 bits */
    default: qwc = 0; break;
    }
    if (qwc > 0x7FFF) {
        P->log(1, "sceGsSetDefLoadImage: image too big (%lld quadwords)", qwc);
        return 0;
    }
    q[0] = 4 | 0x8000ull | (1ull << 60);                          /* NLOOP 4, EOP, NREG 1 */
    q[1] = 0x0E;                                                  /* A+D */
    q[2] = ((unsigned long long)(dbp & 0x3FFF) << 32) | ((unsigned long long)(dbw & 0x3F) << 48)
         | ((unsigned long long)(psm & 0x3F) << 56);
    q[3] = 0x50;                                                  /* BITBLTBUF */
    q[4] = ((unsigned long long)(x & 0x7FF) << 32) | ((unsigned long long)(y & 0x7FF) << 48);
    q[5] = 0x51;                                                  /* TRXPOS */
    q[6] = (unsigned long long)(w & 0xFFF) | ((unsigned long long)(h & 0xFFF) << 32);
    q[7] = 0x52;                                                  /* TRXREG */
    q[8] = 0;                                                     /* host to local */
    q[9] = 0x53;                                                  /* TRXDIR */
    q[10] = (unsigned long long)(qwc & 0x7FFF) | 0x8000ull | (2ull << 58);   /* IMAGE, EOP */
    q[11] = 0;
    return 6;
}

/* sceGsSetDefDBuff(db, psm, w, h, ztest, zpsm, clear): the double buffer set-up; the renderer
 * will take the frame size from here (640 x 512 here) */
void func_00126260(void *db, int psm, int w, int h, int ztest, int zpsm, int clear)
{
    (void)db; (void)ztest; (void)zpsm; (void)clear;
    P->log(0, "GS double buffer: %d x %d, format 0x%X", w, h, psm);
}
