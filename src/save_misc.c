/*
 * save_misc.c - small pieces between 0x003DC9E0 and 0x003DDBCC: the save image packing (each
 * module's part, then the two player records), map cell checks for unit placement, item records
 * (16 fixed ones then 4 custom ones) and the post-battle report's line slider. Original file
 * names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_SAVE_MISC_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

extern u8 g_00669D60[];
#ifdef SW2E_PC
extern ps2ptr g_0045D2F0_a;                   /* (small data) the map */
#define g_0045D2F0 ((u8 *)PS2_PTR(g_0045D2F0_a))
#define g_0045D2F0_SET(v) (g_0045D2F0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2F0;
#define g_0045D2F0_a (*(ps2ptr *)&g_0045D2F0)
#define g_0045D2F0_SET(v) (g_0045D2F0 = (v))
#endif
extern u8 g_007BF540[2][0x9C];           /* the players' records, saved */
#ifdef SW2E_PC
extern ps2ptr g_005BA6A0_a;
#define g_005BA6A0 ((u8 *)PS2_PTR(g_005BA6A0_a))
#define g_005BA6A0_SET(v) (g_005BA6A0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6A0;
#define g_005BA6A0_a (*(ps2ptr *)&g_005BA6A0)
#define g_005BA6A0_SET(v) (g_005BA6A0 = (v))
#endif
extern u8 *g_0042DF00[];                 /* fixed items' names */
extern u8 g_00428326[][2];               /* fixed items: (kind, level) */
extern u8 g_0045C560[];
extern short g_0045C568[];
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

u8 *func_0021A630(void);
void func_0036FDA0(u8 *p);

/* A map cell's record (0 outside the map). */
#define CELL(c) ((c) == 0 || (c)[0] > 0x1F || (c)[1] > 0x1F ? (u8 *)0 :                    \
                 ((u8 **)*(u8 **)(g_0045D2F0 + 4))[(c)[0] + (c)[1] * 0x20])

/* 0x003DC9E0, 0x4C bytes. */
void func_003DC9E0(int k)
{
    u8 *p = func_0021A630();

    if (k == 9) {
        *(int *)(p + 0x1154) = 0;
        func_001B8F60(0, 6, 8);
    }
}

/* 0x003DCA30, 0x74 bytes, matching. Keeps a copy of the players' records. */
void func_003DCA30(void)
{
    int k;

    for (k = 0; k < 2; k++) {
        if (func_003636F0(k) != 0)
            func_00118AC0((unsigned int *)(g_007BF540[k]), func_002F2720(func_00363720(k)), 0x9C);
    }
}

/* 0x003DCF20, 0x194 bytes. Whether `n` more units fit in cell `c` slot `i` (10 near a player's
 * group, 30 otherwise, 45 in all three slots). */
int func_003DCF20(u8 *c, u8 i, u32 n)
{
    u32 lim = 0x1E, k;
    u8 *r;

    if (func_001F1B90(c) != 0)
        return 0;
    if (i == 0) {
        for (k = 0; k < 2; k++) {
            if (*(int *)(g_00669D60 + 0xA0 + k * 0x48) != 0
                && *(short *)c == *((short *)func_0033B730(func_0035DD10(k)))) {
                lim = 10;
                break;
            }
        }
    }
    r = CELL(c);
    n &= 0xFF;
    if (n + r[i + 0xC] >= lim)
        return 0;
    for (k = 0; k < 3; k++) {
        n += r[(k & 0xFF) + 0xC];
        if (n > 0x2D)
            return 0;
    }
    return 1;
}

/* 0x003DD0C0, 0x108 bytes. Whether unit `o` may enter cell `c`. */
int func_003DD0C0(u8 *c, u8 *o)
{
    u8 *r;

    if (func_001F1B90(c) != 0)
        return 0;
    if ((*(u32 *)(o + 0x84) & 8) == 0
        && ((*(u32 *)(o + 0x80) & 0x9B0) != 0 || (*(u32 *)(o + 0x84) & 4) != 0))
        return 1;
    r = CELL(c);
    if (r[o[0x79] + 8] < 6)
        return func_001F1770(c, o[0x79], (char)o[0x74] + 1) != 0;
    return 0;
}

/* 0x003DD1D0, 0xC0 bytes. */
int func_003DD1D0(u8 *c, u32 i)
{
    u8 *r;

    if (func_001F1B90(c) != 0)
        return 0;
    r = CELL(c) + (i & 0xFF);
    if (r[8] < 6)
        return r[0xC] < 0x1E;
    return 0;
}

/* 0x003DD290, 0x68 bytes. */
u32 func_003DD290(u8 *c, u32 i)
{
    return CELL(c)[(i & 0xFF) + 8];
}

/* 0x003DD300, 0xB4 bytes. One of the eight directions where func_0018F7D0 allows a move, at
 * random (8: none). */
int func_003DD300(int a)
{
    int k, r = 8;

    for (k = 0; k < 8; k++) {
        if (func_0018F7D0((unsigned char *)PS2_PTR(a), k, 0) != 0 && (r == 8 || (int)(RANDOM() % 100) < 0x32))
            r = k;
    }
    return r;
}

/* 0x003DD3C0, 0x74 bytes. Item `k`'s text record. */
u8 *func_003DD3C0(int k)
{
    if (k < 0x10)
        return g_005BA6A0 + (k + 0x23C) * 0x2C;
    if (k < 0x14)
        return g_005BA6A0 + (k + 0x1A3) * 0x2C;
    return 0;
}

/* 0x003DD440, 0x58 bytes, matching. Its name. */
u8 *func_003DD440(int k)
{
    if (k < 0x10)
        return g_0042DF00[k];
    if (k < 0x14)
        return func_0019FBC0(k - 0x10) + 0x13;
    return g_0045C560;
}

/* 0x003DD4F0, 0x54 bytes. Its level. */
u8 func_003DD4F0(int k)
{
    if (k < 0x10)
        return g_00428326[k][1];
    if (k < 0x14)
        return func_0019FBC0(k - 0x10)[8];
    return 0;
}

/* 0x003DD550, 0x54 bytes. Its kind. */
u8 func_003DD550(int k)
{
    if (k < 0x10)
        return g_00428326[k][0];
    if (k < 0x14)
        return func_0019FBC0(k - 0x10)[6];
    return 0;
}

/* 0x003DD5B0, 0xAC bytes. Whether item `k` has property `v`. */
int func_003DD5B0(int k, int v)
{
    if (k < 0x10) {
        if (k == 0xF) {
            if (v == 2)
                return 1;
        } else if (k == 0xD && v == 3) {
            return 1;
        }
        return 0;
    }
    if (k < 0x14)
        return (1 << (v & 0x1F) & func_0019FBC0(k - 0x10)[0xD]) != 0;
    return 0;
}

/* 0x003DD810, 0x6C bytes, matching. Saves the players' records into save image `p`. */
void func_003DD810(u8 *p)
{
    int k;

    for (k = 0; k < 2; k++) {
        if (func_003636F0(k) != 0)
            func_00118AC0((unsigned int *)(p + 0x9A8 + k * 0x9C), func_002F2720(func_00363720(k)), 0x9C);
    }
}

/* 0x003DD880, 0x74 bytes, matching. Loads them back from the save image. */
void func_003DD880(void)
{
    u8 *p = (u8 *)PS2_PTR(func_002EFB00(9));
    int k;

    for (k = 0; k < 2; k++) {
        if (func_003636F0(k) != 0)
            func_00118AC0((unsigned int *)(func_002F2720(func_00363720(k))), p + 0x9A8 + k * 0x9C, 0x9C);
    }
}

/* 0x003DD900, 0x70 bytes, matching. Packs the game into save image `p`; its end. */
u8 *func_003DD900(u8 *p)
{
    func_00362DF0(p);
    func_0035F860(p);
    func_0036FDA0(p);
    func_0036E010(p);
    func_0034F440(p);
    func_00338E90(p);
    func_003DCD60(p);
    func_003DD810(p);
    func_003F5770(p);
    func_003F7030(p);
    return p + 0xB08;
}

#define REPORT_LINE(w, step) do {                                       \
    short y_ = g_0045C568[step];                                        \
    (w)->x0 = -0x80; (w)->y0 = y_ + 0x5A; (w)->w0 = 0x80; (w)->h0 = 0x1C; \
    (w)->x1 = -0x80; (w)->y1 = y_ + 0x5A; (w)->w1 = 0x80; (w)->h1 = 0x1C; \
    (w)->frames = 0; (w)->timer = 0;                                    \
    (w)->alpha0 = 0x80; (w)->alpha1 = 0x80;                             \
    (w)->x1 = 0x32; (w)->y1 = y_ + 0x5A; (w)->w1 = 0x80; (w)->h1 = 0x1C;  \
    (w)->alpha1 = 0x80; (w)->frames = 8;                                \
} while (0)

/* 0x003DDA00, 0x114 bytes. Moves the report's marker to the next line once it has stopped. */
void func_003DDA00(void)
{
    u8 *p = func_0021A630();
    WindowAnim *w = (WindowAnim *)(p + 0x115C);
    int busy, s;

    if (w->frames == 0)
        busy = 0;
    else if (w->timer == w->frames)
        busy = 0;
    else
        busy = 1;
    if (!busy && *(int *)(p + 0x1170) < 6) {
        s = *(int *)(p + 0x1170) + 1;
        if (s == *(int *)(p + *(int *)(p + 0x1C) * 4 + 0x167C)) {
            *(int *)(p + 0x1170) = 6;
        } else {
            *(int *)(p + 0x1170) = s;
            REPORT_LINE(w, *(int *)(p + 0x1170));
        }
    }
}

/* 0x003DDB20, 0xAC bytes. */
void func_003DDB20(void)
{
    u8 *p = func_0021A630();
    WindowAnim *w = (WindowAnim *)(p + 0x115C);

    *(int *)(p + 0x1170) = 0;
    REPORT_LINE(w, 0);
}

extern u8 g_00772670[0xC];               /* a gauge (func_002C5AE0) */

/* 0x003DF970, 0x138 bytes. Sets up the item property window `w` for item `item` (record `rec`):
 * the properties it has, then (when fewer than two) the ones it may get. */
void func_003DF970(int item, u8 *w, int a, int b, u8 *rec)
{
    u32 k;

    g_00772670[4] = 0;
    g_00772670[5] = 0;
    g_00772670[6] = 0;
    g_00772670[8] = 0;
    *(int *)(w + 0x30) = 0;
    *(int *)(w + 0x34) = 0;
    *(int *)(w + 0x38) = a;
    w[0x3C] = 0;
    *(int *)(w + 0x40) = b;
    *(int *)(w + 0x48) = 0;
    for (k = 0; (int)k < 4; k++) {
        if ((rec[0xD] & 1 << (k & 0x1F)) != 0)
            *(u32 *)(w + (*(int *)(w + 0x48))++ * 4 + 0x4C) = k;
    }
    *(int *)(w + 0x54) = 0;
    if (*(int *)(w + 0x48) < 2) {
        for (k = 0; (int)k < 4; k++) {
            if ((1 << (k & 0x1F) & func_0019FBC0(item)[0xD]) != 0
                && (*(int *)(w + 0x48) != 1 || *(u32 *)(w + 0x4C) != k))
                *(u32 *)(w + (*(int *)(w + 0x54))++ * 4 + 0x58) = k;
        }
    }
}
