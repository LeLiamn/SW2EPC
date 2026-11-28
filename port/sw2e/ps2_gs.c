/*
 * ps2_gs.c - the Sony graphics library calls (libgraph: sceGs...) for the PC build.
 *
 * The GS is the launcher runtime's (the GS level, docs/launcher.md): the packets the game builds
 * and sends by DMA go to platform->gs_packets as they are, and the display registers to
 * platform->gs_privileged. libgraph's set-up functions are written after Sony's code in the
 * executable, so the environments the game sends are the console's. Also here:
 *   - sceGsSyncV waits for the next frame through platform->vsync();
 *   - sceGsSyncPath returns at once (transfers end at once on the PC).
 * The VU1 parts of the VIF1 chains are not run yet (to be rewritten in C).
 * Generic for PS2 games.
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "upp.h"
#include "sw2e_mem.h"

extern const upp_platform *sw2e_platform;
void sw2e_quit(void);
#define P sw2e_platform

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

/* ---- the GS level: what the game sends goes to the runtime (UPP's gs_packets / gs_privileged) ----
 * The runtime keeps the GS memory and draws (docs/launcher.md, "the 3D path is the GS level").
 * Older runtimes without these two calls (the platform table's `size` says) only count. */

typedef unsigned long long u64;

static int has_gs(void)
{
    return P->size >= (uint32_t)(offsetof(upp_platform, gs_privileged) + sizeof(void *))
        && P->gs_packets && P->gs_privileged;
}

static u64 g_gs_qwords, g_gs_sends;

static void gs_send(const void *data, size_t qwords)
{
    if (qwords == 0)
        return;
    if (g_gs_sends++ == 0)
        P->log(2, "GS: first packets to the runtime (%u quadwords)%s", (unsigned)qwords,
               has_gs() ? "" : "; this runtime has no gs_packets, nothing is drawn");
    g_gs_qwords += qwords;
    if (has_gs())
        P->gs_packets(data, qwords);
}

static void gs_priv(uint32_t reg, u64 value)
{
    if (has_gs())
        P->gs_privileged(reg, value);
}

/* ---- sceGsGParam (the library's video parameters, set by sceGsResetGraph) ----
 * shorts: [0] interlace, [1] video mode (2 NTSC, 3 PAL), [2] field mode, [3] GS revision. */
static unsigned short g_gparam[32];

unsigned char *func_00125860(void)                        /* sceGsGetGParam */
{
    return (unsigned char *)g_gparam;
}

/* sceGsResetGraph(mode, interlace, omode, ffmode): mode 0 (and 5) record the video mode; the
 * PC has no CRT to set (SetGsCrt): the display registers sent later describe the picture. */
void func_001256D0(int mode, int interlace, int omode, int ffmode)
{
    if (mode == 0 || mode == 5) {
        g_gparam[0] = (unsigned short)interlace;
        g_gparam[1] = (unsigned short)omode;
        g_gparam[2] = (unsigned short)(ffmode != 0);
        g_gparam[3] = 0;                  /* revision: the DISPFB2 / DISPLAY2 path */
    }
    P->log(2, "GS video mode: %s, %s, %s (sceGsResetGraph mode %d)",
           omode == 3 ? "PAL" : omode == 2 ? "NTSC" : "other", interlace ? "interlaced" : "progressive",
           ffmode ? "field" : "frame", mode);
}

/* 0x00125DC0: the size of a w x h buffer of format psm, in the units of FBP / ZBP */
static int buffer_size(int psm, int w, int h)
{
    int n = ((w + 63) >> 6) * ((psm & 2) ? (h + 63) >> 6 : (h + 31) >> 5);
    u64 gp = (u64)g_gparam[0] | (u64)g_gparam[2] << 32;

    return (short)(gp == 1 ? n : n * 2);
}

/* 0x00125988 sceGsSetDefDispEnv(disp, psm, w, h, dx, dy): PMODE, SMODE2, DISPFB, DISPLAY,
 * BGCOLOR. The console's own screen position offsets (ROM settings) are 0 for PAL and NTSC. */
void func_00125988(unsigned char *env, int psm, int w, int h, int dx, int dy)
{
    u64 *e = (u64 *)env;
    int interlace = (short)g_gparam[0], omode = g_gparam[1], ffmode = g_gparam[2];
    int base, top, mag, dh;

    psm = (short)psm; w = (short)w; h = (short)h; dx = (short)dx; dy = (short)dy;
    e[0] = 0x66;
    e[1] = interlace == 0 ? 2 : ffmode == 0 ? 1 : 3;
    e[2] = ((u64)(psm & 0xF) << 15) | ((u64)(((w + 63) >> 6) & 0x3F) << 9);
    if (omode == 2 || omode == 3) {
        base = omode == 2 ? 0x27C : 0x290;
        mag = w ? (w + 0x9FF) / w : 1;
        if (interlace != 1) {
            top = dy + (omode == 2 ? 0x19 : 0x24);
            dh = h - 1;
        } else {
            top = dy + (omode == 2 ? 0x32 : 0x48);
            dh = ffmode == 0 ? h - 1 : h * 2 - 1;
        }
        e[3] = ((u64)(mag - 1) << 23) | ((u64)(mag * w - 1) << 32) | ((u64)(dx * mag + base) & 0xFFF)
             | ((u64)dh << 44) | (((u64)top & 0xFFF) << 12);
    } else if (omode == 0x50) {
        e[3] = ((u64)(h - 1) << 44) | ((u64)(w * 2 - 1) << 32)
             | ((u64)((0x2D0 - w) / 2 * 2 + dx * 2 + 0xE8) & 0xFFF) | 0x800000
             | (((u64)(dy + 0x23) & 0xFFF) << 12);
    } else {
        P->log(1, "sceGsSetDefDispEnv: video mode 0x%X not handled", omode);
    }
    e[4] = 0;
}

/* sceGsPutDispEnv: the display registers */
static void put_disp_env(const unsigned char *env)
{
    const u64 *e = (const u64 *)env;

    if (g_gparam[3] == 1) {
        gs_priv(UPP_GS_PMODE, e[0]);
        gs_priv(UPP_GS_DISPFB1, e[2]);
        gs_priv(UPP_GS_DISPLAY1, e[3]);
        gs_priv(UPP_GS_EXTDATA, e[4]);
    } else {
        gs_priv(UPP_GS_PMODE, e[0]);
        gs_priv(UPP_GS_SMODE2, e[1]);
        gs_priv(UPP_GS_DISPFB2, e[2]);
        gs_priv(UPP_GS_DISPLAY2, e[3]);
        gs_priv(UPP_GS_BGCOLOR, e[4]);
    }
}

/* 0x00125E88 / 0x00126D98 sceGsSetDefDrawEnv / sceGsSetDefDrawEnv2(draw, psm, w, h, ztest, zpsm):
 * the A+D pairs FRAME, ZBUF, XYOFFSET, SCISSOR, PRMODECONT, COLCLAMP, DTHE, TEST of context 1 / 2;
 * returns 8 (pairs). DTHE, COLCLAMP and PRMODECONT keep their other bits, as the original. */
static int set_draw_env(unsigned char *env, int ctx, int psm, int w, int h, int ztest, int zpsm)
{
    u64 *e = (u64 *)env;

    psm = (short)psm; w = (short)w; h = (short)h; ztest = (short)ztest; zpsm = (short)zpsm;
    e[1] = ctx ? 0x4D : 0x4C;                                   /* FRAME */
    e[0] = ((u64)(((w + 63) >> 6) & 0x3F) << 16) | ((u64)(psm & 0xF) << 24);
    e[3] = ctx ? 0x4F : 0x4E;                                   /* ZBUF */
    e[2] = (u64)(long long)(short)buffer_size(psm, w, h) | ((u64)(zpsm & 0xF) << 24)
         | (ztest == 0 ? 0x100000000ull : 0);
    e[5] = ctx ? 0x19 : 0x18;                                   /* XYOFFSET */
    e[4] = (u64)(0x800 - (w >> 1)) * 0x10 | ((u64)(0x800 - (h >> 1)) << 36);
    e[7] = ctx ? 0x41 : 0x40;                                   /* SCISSOR */
    e[6] = ((u64)(w - 1) << 16) | ((u64)(h - 1) << 48);
    e[9] = 0x1A;                                                /* PRMODECONT */
    e[8] |= 1;
    e[11] = 0x46;                                               /* COLCLAMP */
    e[10] |= 1;
    e[13] = 0x45;                                               /* DTHE */
    e[12] = (psm & 2) ? (e[12] | 1) : (e[12] & ~1ull);
    e[15] = ctx ? 0x48 : 0x47;                                  /* TEST */
    e[14] = ztest == 0 ? 0x30000 : (((u64)(ztest & 3) << 17) | 0x10000);
    return 8;
}

void func_00125E88(void *env, int psm, unsigned short w, unsigned short h, int ztest, int zpsm)
{
    set_draw_env((unsigned char *)env, 0, psm, (short)w, (short)h, ztest, zpsm);
}

int func_00126D98(void *env, int psm, unsigned short w, unsigned short h, int ztest, int zpsm)
{
    return set_draw_env((unsigned char *)env, 1, psm, (short)w, (short)h, ztest, zpsm);
}

/* 0x00126070 sceGsSetDefClear(clear, ztest, x, y, w, h, r, g, b, a, z): TEST, PRIM sprite,
 * RGBAQ, two XYZ2 corners, TEST again; returns 6 (pairs) */
static int set_clear(unsigned char *env, int ztest, int x, int y, int w, int h,
                     unsigned r, unsigned g, unsigned b, unsigned a, unsigned z)
{
    u64 *e = (u64 *)env;

    e[0] = 0x30000; e[1] = 0x47;
    e[2] = 6; e[3] = 0;
    e[4] = (r & 0xFF) | ((u64)(g & 0xFF) << 8) | ((u64)(b & 0xFF) << 16) | ((u64)(a & 0xFF) << 24)
         | 0x3F80000000000000ull;
    e[5] = 1;
    e[6] = (u64)(x << 4) | ((u64)(y << 4) << 16) | ((u64)z << 32); e[7] = 5;
    e[8] = (u64)((x + w) * 0x10) | ((u64)((y + h) * 0x10) << 16) | ((u64)z << 32); e[9] = 5;
    e[10] = ztest == 0 ? 0x30000 : (((u64)(ztest & 3) << 17) | 0x10000); e[11] = 0x47;
    return 6;
}

static void set_giftag(unsigned char *at, int nloop)
{
    u64 *t = (u64 *)at;

    memset(at, 0, 16);
    t[0] = (u64)nloop | 0x8000ull | (1ull << 60);                 /* NLOOP, EOP, NREG 1 */
    t[1] = 0xE;                                                  /* A+D */
}

/* 0x00126260 sceGsSetDefDBuff(db, psm, w, h, ztest, zpsm, clear):
 * disp[0] +0, disp[1] +0x28, giftag0 +0x50, draw0 +0x60, clear0 +0xE0,
 * giftag1 +0x140, draw1 +0x150, clear1 +0x1D0 */
void func_00126260(void *dbv, int psm, int w, int h, int ztest, int zpsm, int clear)
{
    unsigned char *db = (unsigned char *)dbv;
    int fb;

    w = (short)w; h = (short)h;
    func_00125988(db, psm, w, h, 0, 0);
    func_00125988(db + 0x28, psm, w, h, 0, 0);
    set_draw_env(db + 0x60, 0, psm, w, h, ztest, zpsm);
    set_draw_env(db + 0x150, 0, psm, w, h, ztest, zpsm);
    if ((short)clear) {
        set_clear(db + 0xE0, ztest, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0, 0);
        set_clear(db + 0x1D0, ztest, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0, 0);
    }
    set_giftag(db + 0x50, (short)clear ? 14 : 8);
    set_giftag(db + 0x140, (short)clear ? 14 : 8);
    fb = buffer_size(psm, w, h);
    if (((u64)g_gparam[0] | (u64)g_gparam[2] << 32) == 0x100000001ull || g_gparam[0] == 0) {
        *(u64 *)(db + 0x60) = (*(u64 *)(db + 0x60) & ~0x1FFull) | ((u64)(fb >> 1) & 0x1FF);
        *(u64 *)(db + 0x38) = (*(u64 *)(db + 0x38) & ~0x1FFull) | ((u64)(short)(fb >> 1) & 0x1FF);
    }
    P->log(2, "GS double buffer: %d x %d, format 0x%X, Z format 0x%X", w, h, psm, zpsm);
}

/* 0x00127000 sceGsSetDefDBuffDc(db, psm, w, h, ztest, zpsm, clear): both draw contexts per buffer:
 * disp[0] +0, disp[1] +0x28, giftag0 +0x50, draw01 +0x60, draw02 +0xE0, clear0 +0x160,
 * giftag1 +0x1C0, draw11 +0x1D0, draw12 +0x250, clear1 +0x2D0 */
void func_00127000(unsigned char *db, int psm, int w, unsigned short hh, int ztest, int zpsm, int clear)
{
    int h = (short)hh, fb;

    w = (short)w;
    func_00125988(db, psm, w, h, 0, 0);
    func_00125988(db + 0x28, psm, w, h, 0, 0);
    set_draw_env(db + 0x60, 0, psm, w, h, ztest, zpsm);
    set_draw_env(db + 0xE0, 1, psm, w, h, ztest, zpsm);
    set_draw_env(db + 0x1D0, 0, psm, w, h, ztest, zpsm);
    set_draw_env(db + 0x250, 1, psm, w, h, ztest, zpsm);
    if ((short)clear) {
        set_clear(db + 0x160, ztest, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0, 0);
        set_clear(db + 0x2D0, ztest, 0x800 - (w >> 1), 0x800 - (h >> 1), w, h, 0, 0, 0, 0, 0);
    }
    set_giftag(db + 0x50, (short)clear ? 0x16 : 0x10);
    set_giftag(db + 0x1C0, (short)clear ? 0x16 : 0x10);
    fb = buffer_size(psm, w, h);
    if (((u64)g_gparam[0] | (u64)g_gparam[2] << 32) == 0x100000001ull || g_gparam[0] == 0) {
        u64 f = (u64)(fb >> 1) & 0x1FF;

        *(u64 *)(db + 0xE0) = (*(u64 *)(db + 0xE0) & ~0x1FFull) | f;
        *(u64 *)(db + 0x38) = (*(u64 *)(db + 0x38) & ~0x1FFull) | ((u64)(short)(fb >> 1) & 0x1FF);
        *(u64 *)(db + 0x60) = (*(u64 *)(db + 0x60) & ~0x1FFull) | f;
    }
    P->log(2, "GS double buffer (two contexts): %d x %d, format 0x%X, Z format 0x%X", w, h, psm, zpsm);
}

/* 0x00126178 sceGsPutDrawEnv(giftag): the GIF tag and its A+D pairs to the GS */
int func_00126178(void *draw)
{
    gs_send(draw, (size_t)((*(u64 *)draw & 0x7FFF) + 1));
    return 0;
}

/* 0x001264F8 sceGsSwapDBuff(db, field) / 0x001272E8 sceGsSwapDBuffDc(db, field) */
void func_001264F8(void *dbv, int field)
{
    unsigned char *db = (unsigned char *)dbv;

    put_disp_env(db + (field & 1) * 0x28);
    func_00126178(db + ((field & 1) ? 0x140 : 0x50));
}

void func_001272E8(unsigned char *db, unsigned int field)
{
    put_disp_env(db + (field & 1) * 0x28);
    func_00126178(db + ((field & 1) ? 0x1C0 : 0x50));
}

/* 0x00126D10 / 0x00126F78 sceGsSetHalfOffset / sceGsSetHalfOffset2(draw, cx, cy, field): the
 * XYOFFSET of a draw environment centred on (cx, cy), half a line down on odd fields */
static void half_offset(unsigned char *env, int cx, int cy, int field)
{
    u64 sc = *(u64 *)(env + 0x30);
    long long y = (long long)cy - ((((sc >> 48) & 0x7FF) + 1) >> 1);
    long long x = (long long)cx - ((((sc >> 16) & 0x7FF) + 1) >> 1);
    u64 yy = field == 0 ? (u64)y << 36 : (u64)(y * 0x10 + 8) << 32;

    *(u64 *)(env + 0x20) = (u64)(x * 0x10) | yy;
}

void func_00126D10(unsigned char *env, int cx, int cy, unsigned short field)
{
    half_offset(env, (short)cx, (short)cy, (short)field);
}

void func_00126F78(unsigned char *env, int cx, int cy, unsigned short field)
{
    half_offset(env, (short)cx, (short)cy, (short)field);
}

/* 0x00126AF0 sceGsExecLoadImage(load, data): the upload packet (6 quadwords), then the pixels */
int func_00126AF0(void *load, void *data)
{
    gs_send(load, 6);
    gs_send(data, (size_t)(*(u64 *)((unsigned char *)load + 0x50) & 0x7FFF));
    return 0;
}

/* ---- DMA to the GIF and VIF1 ---- */

/* which channel a channel block is (its register address on the PS2) */
static unsigned int chan_addr(const unsigned char *ch)
{
    return 0x10000000u + (unsigned int)(ch - sw2e_hw);
}

/* A VIF1 stream: VIF codes with their data. DIRECT / DIRECTHL data goes to the GS; the VU1
 * parts (MPG, UNPACK, MSCAL...) wait for the C rewrite of the VU1 programs and are only counted. */
static u64 g_vu1_calls, g_vu1_unpacks, g_vu1_mpg;
static int g_vif_cl = 1, g_vif_wl = 1;

static void vif_stream(const unsigned int *w, size_t n)
{
    size_t i = 0;

    while (i < n) {
        unsigned int code = w[i++], cmd = (code >> 24) & 0x7F, imm = code & 0xFFFF, num = (code >> 16) & 0xFF;

        if (cmd == 0x50 || cmd == 0x51) {                     /* DIRECT, DIRECTHL */
            size_t q = imm ? imm : 0x10000;

            i = (i + 3) & ~(size_t)3;                         /* the data starts on a quadword */
            if (i + q * 4 > n)
                q = (n - i) / 4;
            gs_send(w + i, q);
            i += q * 4;
        } else if (cmd == 0x4A) {                             /* MPG: num 64-bit instructions */
            size_t k = num ? num : 256;

            i = (i + 1) & ~(size_t)1;
            i += k * 2;
            g_vu1_mpg++;
        } else if (cmd >= 0x60) {                             /* UNPACK */
            int vn = (cmd >> 2) & 3, vl = cmd & 3;
            size_t k = num ? num : 256, elems, bits;

            if (g_vif_wl <= g_vif_cl)
                elems = k;
            else
                elems = g_vif_cl * (k / g_vif_wl) + (k % g_vif_wl < (size_t)g_vif_cl ? k % g_vif_wl : (size_t)g_vif_cl);
            bits = elems * (size_t)(32 >> vl) * (size_t)(vn + 1);
            i += (bits + 31) / 32;
            g_vu1_unpacks++;
        } else if (cmd == 0x01) {                             /* STCYCL */
            g_vif_cl = imm & 0xFF;
            g_vif_wl = (imm >> 8) & 0xFF;
        } else if (cmd == 0x20) {                             /* STMASK */
            i += 1;
        } else if (cmd == 0x30 || cmd == 0x31) {              /* STROW, STCOL */
            i += 4;
        } else if (cmd == 0x14 || cmd == 0x15 || cmd == 0x17) {   /* MSCAL, MSCALF, MSCNT */
            g_vu1_calls++;
        }
        /* NOP, OFFSET, BASE, ITOP, STMOD, MSKPATH3, MARK, FLUSH*: nothing to do here */
    }
}

/* A source chain (DMA tags) from PS2 address `addr`. With TTE, the tag's upper half goes to the
 * stream as VIF codes (the lower half as two padding words, keeping quadword alignment). */
static void walk_chain(unsigned int addr, int to_vif, int tte)
{
    static unsigned int *buf;
    static size_t cap;
    size_t n = 0;
    unsigned int stack[2], sp = 0, guard = 0;

#define PUT(p, words) do {                                                     \
        size_t m_ = (words);                                                   \
        if (n + m_ > cap) {                                                    \
            cap = (n + m_) * 2 + 1024;                                         \
            buf = (unsigned int *)realloc(buf, cap * 4);                       \
        }                                                                      \
        memcpy(buf + n, (p), m_ * 4);                                          \
        n += m_;                                                               \
    } while (0)

    for (;;) {
        const unsigned int *t = (const unsigned int *)PS2_PTR(addr);
        u64 tag = (u64)t[0] | (u64)t[1] << 32;
        unsigned int qwc = (unsigned int)(tag & 0xFFFF), id = (unsigned int)(tag >> 28) & 7;
        unsigned int a = (unsigned int)(tag >> 32) & 0x7FFFFFF0u, next;
        static const unsigned int pad[2] = { 0, 0 };

        if (++guard > 1000000) {
            P->log(1, "DMA chain at 0x%08X: no end after a million tags", addr);
            break;
        }
        if (tte) {
            PUT(pad, 2);
            PUT(t + 2, 2);
        }
        switch (id) {
        case 0: case 3: case 4:                               /* REFE, REF, REFS: data at ADDR */
            PUT((const unsigned int *)PS2_PTR(a), qwc * 4);
            next = addr + 16;
            break;
        default:                                              /* CNT, NEXT, CALL, RET, END: data follows */
            PUT(t + 4, qwc * 4);
            next = addr + 16 + qwc * 16;
            break;
        }
        if (id == 0 || id == 7)
            break;
        if (id == 2)                                          /* NEXT */
            next = a;
        else if (id == 5) {                                   /* CALL */
            if (sp < 2)
                stack[sp++] = next;
            next = a;
        } else if (id == 6) {                                 /* RET */
            if (sp == 0)
                break;
            next = stack[--sp];
        }
        addr = next;
    }
#undef PUT
    if (to_vif)
        vif_stream(buf, n);
    else
        gs_send(buf, n / 4);
}

/* sceDmaSendN(channel, data, qwc): normal mode, qwc quadwords; the callers pass the channel as
 * its PS2 address */
void func_0011B3E8(unsigned int c, void *data, unsigned int qwc)
{

    if (c == 0x1000A000u)                                     /* GIF */
        gs_send(data, qwc);
    else if (c == 0x10009000u)                                /* VIF1 */
        vif_stream((const unsigned int *)data, (size_t)qwc * 4);
}

/* sceDmaSend(channel, chain): source chain mode; TTE as set in the channel's CHCR (bit 6) */
void func_0011B380(unsigned char *channel, unsigned int *chain)
{
    unsigned int c = chan_addr(channel);
    int tte = (channel[0] & 0x40) != 0;

    if (c == 0x1000A000u)
        walk_chain(PS2_ADDR(chain), 0, tte);
    else if (c == 0x10009000u)
        walk_chain(PS2_ADDR(chain), 1, tte);
    /* VIF0 (VU0 microcode uploads): nothing to send */
}

/* sceDmaSync-like (0x0011B690): waits for a channel; transfers end at once here */
int func_0011B690(unsigned char *channel) { (void)channel; return 0; }

/* how much went to the GS so far (for the logs) */
void sw2e_gs_stats(void)
{
    P->log(2, "GS: %llu sends, %llu quadwords; VU1 (not run yet): %llu calls, %llu unpacks, %llu microcode uploads",
           g_gs_sends, g_gs_qwords, g_vu1_calls, g_vu1_unpacks, g_vu1_mpg);
}
