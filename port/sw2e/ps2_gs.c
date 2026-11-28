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
