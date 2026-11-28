/*
 * text_window.c - the battle's text windows (0x001AE550-0x001B92A4, after Bullet.c; the original file's
 * name is unknown). Complete: the windows, a menu and the screen fade.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Five windows of 0x128 bytes at 0x00693394: 0 and 1 plain, 2 a list (state at 0x00693390),
 * 3 one with two small portraits (0x00692AC0), 4 one with four portraits (0x00692DC0).
 */

#define SW2E_FILE_TEXT_WINDOW_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* A text window. */
typedef struct {
    int x, y, z;          /* -1: centred */
    int w, h;             /* -1: from the text */
    int tw, th;           /* the text's size */
    char text[0xFF];
    u8 pad[4];            /* +0x11B top, bottom, left, right margins */
    u8 state;             /* +0x11F */
    u8 b[8];              /* +0x120: speed, timer, opened, lines, style... */
} TextWindow;

extern TextWindow g_00693394[5];
extern u8 g_00693390[4];                 /* window 2: its mode, kind, a time, a flag */
extern u8 g_00693968;                    /* 1: the half-screen layout */
extern float g_0056CCC0, g_0056CCC4;     /* (font state) the character width and height */

/* Window 2's list (0x006935E8...), window 3's (0x00692DA0...), window 4's (0x00693380...). */
extern int g_006934BC, g_006934C8, g_006934CC;
extern int g_006935E8, g_006935F0, g_006935F4, g_006935F8, g_006935FC;
extern u8 g_006936FF, g_00693700, g_00693701, g_00693706, g_00693708;
extern int g_00693834, g_00693840, g_00693844, g_00693848, g_0069384C;
extern u8 g_0069382E, g_0069394F, g_00693950, g_00693951, g_00693952, g_00693956, g_00693958;
extern u8 g_0069338C;
extern u16 g_00693380[4], g_00693388, g_0069338A;
extern u32 g_00692DA0, g_00692DA4;
extern u16 g_00692DA8, g_00692DAA;
extern u8 g_00692DAC, g_00692DAD, g_00692DAE, g_00692DAF, g_00692DB0;
extern u8 g_00692AC0[2][0x170], g_00692DC0[4][0x170];   /* portrait objects */
extern u32 g_0068F6E0, g_0068F6F0, g_0068F730, g_0068F740;
extern u32 g_0068FA50, g_0068FA60, g_0068FAA0, g_0068FAB0;
extern u8 g_0073DCA3[];
extern float g_0073DC6C;
extern int g_00693710;
extern u64 g_0068F0F0, g_0068F100;     /* TEX0 values of texture sets */
extern u64 g_004053F0, g_004053F8;       /* the names' font pages */
extern u16 g_00405418, g_0040541A;

void func_00120928(char *to, const char *from);

/* A moving rectangle: from, to (x, y, w, h; -1 kept), alpha from / to, frames and frame. */
typedef struct {
    short from[4];
    short to[4];
    u8 a0, a1;
    u8 frames, frame;
} Slide;

/* 0x001AE550, 0x494 bytes. Steps slide `s` (eased unless `linear`: 80% of the way in the first
 * 30% of the time), putting its rectangle (scaled by `k`) in `out` and its alpha in `alpha`.
 * Whether it has ended (then it rests at its end). */
int func_001AE550(float k, Slide *s, short *out, u8 *alpha, int linear)
{
    u32 n, i;
    float t;

    s->frame++;
    n = s->frames;
    i = s->frame;
    if (i >= n) {
        if (out != 0) {
            out[0] = s->to[0];
            out[1] = s->to[1];
            out[2] = s->to[2];
            out[3] = s->to[3];
        }
        s->from[0] = s->to[0];
        s->from[1] = s->to[1];
        s->from[2] = s->to[2];
        s->from[3] = s->to[3];
        s->a0 = s->a1;
        s->frame = 0;
        s->frames = 0;
        if (alpha != 0)
            *alpha = s->a1;
        return 1;
    }
    if (linear == 0) {
        if (n == 0) {
            t = 0.0f;
        } else {
            float e = (float)n * 0.3f;

            if (i < ((u32)(int)e & 0xFF))
                t = (float)i * 0.8f / e;
            else
                t = ((float)i - e) * 0.19999999f / ((float)n - e) + 0.8f;
        }
    } else {
        t = n == 0 ? 0.0f : (float)i / (float)n;
    }
    if (out != 0) {
        int j;

        for (j = 0; j < 4; j++) {
            if (j >= 2 && (s->from[j] == -1 || s->to[j] == -1))
                out[j] = -1;
            else
                out[j] = (short)(int)(k * t * (float)(s->to[j] - s->from[j]) + (float)s->from[j] + 0.0f);
        }
    }
    if (alpha != 0)
        *alpha = (u8)(int)(t * (float)(s->a1 - s->a0) + (float)s->a0 + 0.0f);
    return 0;
}

/* 0x001AE9F0, 0x3B8 bytes. Puts text `s` in window `k` (wrapped to its width with `wrap`),
 * sizing the window from the text and its margins when it has no size, and placing it centred
 * when it has no place; then the special windows' own layouts. */
void func_001AE9F0(int k, const char *s, int wrap)
{
    TextWindow *w = &g_00693394[k];
    int fit = w->w == -1;

    if (fit)
        w->w = 0x1AC;
    w->b[3] = func_00147070((const unsigned char *)(s));
    if (wrap == 0) {
        func_00120928(w->text, s);
        g_0056CCC0 = 16.0f;
        g_0056CCC4 = 16.0f;
        func_00146D80((const unsigned char *)(s), &w->tw, &w->th);
    } else {
        g_0056CCC0 = 16.0f;
        g_0056CCC4 = 16.0f;
        func_00147160((const unsigned char *)(s), (unsigned char *)(w->text), w->w - w->pad[2] - w->pad[3], &w->tw, &w->th);
    }
    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    if (fit)
        w->w = w->pad[3] + w->tw + w->pad[2];
    if (w->h == -1) {
        w->h = w->pad[1] + w->th + w->pad[0];
        if (k == 1)
            g_006934CC = g_006934CC + 0x20;
        else if (k == 2)
            g_006935E8 = (g_00693968 == 1 ? 0xCC : 0x120) - g_006935F4;
    }
    if (w->x == -1)
        w->x = (0x200 - w->w) >> 1;
    if (w->y == -1)
        w->y = (0x180 - w->h) >> 1;
    if (k == 3)
        return;
    if (k == 2) {
        if (g_00693390[1] == 0) {
            int m;

            g_00693701 = (u8)((g_006935F0 - g_006935F8) >> 1);
            m = g_00693700 + g_006935FC + g_006936FF;
            if (g_006935F4 < m)
                g_006935F4 = m;
        } else if ((u32)(g_00693390[1] - 1) < 2) {
            g_00693701 = (u8)((g_006935F0 - g_006935F8) >> 1);
        }
    } else if (k == 4) {
        if (g_0069338C == 0) {
            g_00693951 = 0x10;
            g_00693952 = 0xC;
            g_00693840 = g_00693848 + 0x1C;
            g_00693844 = g_00693950 + g_0069384C + g_0069394F;
            g_00693834 = 0x3E;
        } else {
            g_00693951 = 0xC;
            g_00693952 = 0x10;
            g_00693840 = g_00693848 + 0x1C;
            g_00693844 = g_00693950 + g_0069384C + g_0069394F;
            g_00693834 = 0x1C2 - g_00693840;
        }
    } else if (k == 1) {
        if (g_006934C8 <= 0x1AC)
            g_006934C8 = 0x1AC;
        g_006934BC = (0x200 - g_006934C8) >> 1;
    }
}

/* 0x001AEDB0, 0x30 bytes. */
void func_001AEDB0(int k, int x, int y, int z)
{
    g_00693394[k].x = x;
    g_00693394[k].y = y;
    g_00693394[k].z = z;
}

/* 0x001AEDE0, 0x28 bytes. */
void func_001AEDE0(int k, int y)
{
    g_00693394[k].y = y;
}

/* 0x001AEE10, 0x2C bytes. */
void func_001AEE10(int k, int w, int h)
{
    g_00693394[k].w = w;
    g_00693394[k].h = h;
}

/* 0x001AEE40, 0x34 bytes. */
void func_001AEE40(int k, u8 top, u8 bottom, u8 left, u8 right)
{
    g_00693394[k].pad[0] = top;
    g_00693394[k].pad[1] = bottom;
    g_00693394[k].pad[2] = left;
    g_00693394[k].pad[3] = right;
}

/* Window `k`'s default margins, size and place. */
static inline void window_defaults(TextWindow *w)
{
    w->pad[0] = 0xC;
    w->pad[1] = 0xC;
    w->pad[2] = 0x20;
    w->pad[3] = 0x20;
    w->w = -1;
    w->h = -1;
}

/* 0x001AEE80, 0x408 bytes. Resets window `k` (and the special windows' portraits). */
void func_001AEE80(int k)
{
    TextWindow *w = &g_00693394[k];
    int y;

    window_defaults(w);
    w->tw = -1;
    w->th = -1;
    w->x = -1;
    w->y = -1;
    w->z = 0;
    w->text[0] = 0;
    w->state = 0;
    w->b[0] = 8;
    w->b[1] = 5;
    w->b[2] = 0;
    w->b[3] = 0;
    w->b[4] = 6;
    w->b[5] = 0;
    w->b[6] = 0;
    w->b[7] = 0;
    if (k == 4) {
        g_00693958 = 6;
        g_00693380[0] = 0x2F9;
        g_00693380[1] = 0x2F9;
        g_00693380[2] = 0x2F9;
        g_00693380[3] = 0x2F9;
        g_0069338C = 2;
        g_00693388 = 0x80B1;
        g_0069338A = 0x80B1;
        y = g_00693968 == 1 ? 0xA4 : 0xE6;
        func_001A9450(g_00692DC0[0], 0xC, y, 0, 0x80, 0x32, 0x39, 0, 0);
        func_001A9450(g_00692DC0[1], 0xC, y, 0, 0x80, 0x32, 0x39, 0, 0);
        func_001A9450(g_00692DC0[2], 0x1C2, y, 0, 0x80, 0x32, 0x39, 1, 0);   /* (flip?) */
        func_001A9450(g_00692DC0[3], 0x1C2, y, 0, 0x80, 0x32, 0x39, 1, 0);
    } else if (k == 3) {
        g_00692DA0 = 0;
        g_00692DA4 = 0;
        g_00692DA8 = 0x2F9;
        g_00692DAA = 0x2F9;
        g_00692DAC = 0xB1;
        y = g_00693968 == 1 ? 0xA5 : 0x92;
        func_001A9450(g_00692AC0[0], 0x224, y, 0, 0x20, 0x24, 0x80, 0, 0);
        func_001A9450(g_00692AC0[1], 0x224, y, 0, 0x20, 0x24, 0x80, 0, 0);
        g_00692DAD = 8;
        g_00692DAE = 3;
        g_00692DAF = 0;
        g_00692DB0 = 3;
    } else if (k == 2) {
        g_00693708 = 6;
        g_00693390[0] = 3;
        g_00693390[1] = 0;
        g_00693390[2] = 0x14;
        g_00693390[3] = 0;
    }
}

/* 0x001AF290, 0x18C bytes. Empties window `k` (windows 0 and 1 also lose their size and
 * place). */
void func_001AF290(int k)
{
    TextWindow *w = &g_00693394[k];

    w->state = 0;
    w->b[0] = 0;
    w->text[0] = 0;
    w->b[1] = 5;
    w->b[2] = 0;
    w->b[3] = 0;
    w->b[4] = 6;
    w->tw = -1;
    w->th = -1;
    w->b[7] = 0;
    if (k == 4) {
        g_00693958 = 6;
    } else if (k == 3) {
        g_00692DA0 = 0;
        g_00692DA4 = 0;
        g_00692DA8 = 0x2F9;
        g_00692DAA = 0x2F9;
        g_00692DAC = 0;
        g_00692DAD = 8;
        g_00692DAE = 3;
        g_00692DAF = 0;
        g_00692DB0 = 3;
    } else if (k == 2) {
        g_00693708 = 6;
        g_00693390[0] = 0;
        g_00693390[1] = 0;
        g_00693390[2] = 0x14;
        g_00693390[3] = 0;
    } else if (k == 1 || k == 0) {
        window_defaults(w);
        w->x = -1;
        w->y = -1;
        w->z = 0;
        g_0068F730 = 0;
        g_0068F740 = 0;
        g_0068F6E0 = 0;
        g_0068F6F0 = 0;
        g_0068FAA0 = 0;
        g_0068FAB0 = 0;
        g_0068FA50 = 0;
        g_0068FA60 = 0;
    }
}

/* 0x001AF420, 0xA8 bytes. A window's packets: nine frame parts (texture 0x3EF4) and two arrows
 * (0x3F39, at +0x2D0 and +0x320). */
void func_001AF420(u8 *p)
{
    u64 t = func_00106C90(g_0068F0F0, 0x3EF4);
    int k;

    for (k = 0; k < 9; k++)
        func_001057F0(p + k * 0x50, t, 0);
    t = func_00106C90(g_0068F0F0, 0x3F39);
    func_001057F0(p + 800, t, 0);
    func_001057F0(p + 0x2D0, t, 0);
}

/* The names' font page to use. */
static inline u64 name_page(void)
{
    if (g_004053F8 == (u64)-1 || g_00405418 * g_0040541A != 0)
        return g_004053F0;
    return g_004053F8;
}

/* A sprite packet's fixed part: grey, texels (u0, v0)-(u1, v1), at the screen's corner. */
static inline void plain_sprite(u8 *p, u64 set, int tex, u64 uv0, u64 uv1, int g)
{
    u64 xy = (u64)(long long)(-0xE00 / g + 0x8000) << 16 | 0xFFFE00007000ULL;

    func_001057F0(p, func_00106C90(set, tex), 0);
    *(u64 *)(p + 0x20) = 0x3F80000080808080ULL;
    *(u64 *)(p + 0x28) = uv0;
    *(u64 *)(p + 0x38) = uv1;
    *(u64 *)(p + 0x30) = xy;
    *(u64 *)(p + 0x40) = xy;
}

#define g_70000154 (*(int *)PS2_PTR(0x70000154))    /* (scratchpad) the vertical scale */

/* A gradient packet (blue-grey from top to bottom). */
static inline void gradient(u8 *p)
{
    func_001055E0(p);
    *(u64 *)(p + 0x18) = 0x3F80000080B0BAC1ULL;
    *(u64 *)(p + 0x28) = 0x3F80000080B0BAC1ULL;
    *(u64 *)(p + 0x38) = 0x3F800000806D7A81ULL;
    *(u64 *)(p + 0x48) = 0x3F800000806D7A81ULL;
    *(u64 *)(p + 0x20) = 0;
    *(u64 *)(p + 0x30) = 0;
    *(u64 *)(p + 0x40) = 0;
    *(u64 *)(p + 0x50) = 0;
}

/* 0x001AF4D0, 0x3F8 bytes. The list window's packets: two gradients, two bar ends (0x3F21),
 * sixteen glyphs, a cursor (0x3F0F) and four marks (0x3EED). */
void func_001AF4D0(u8 *p)
{
    int k;

    gradient(p);
    gradient(p + 0x60);
    plain_sprite(p + 0xC0, g_0068F0F0, 0x3F21, 0x9880808, 0xB080E88, g_70000154);
    plain_sprite(p + 0x110, g_0068F0F0, 0x3F21, 0x9880E88, 0xB080EF8, g_70000154);
    for (k = 0; k < 0x10; k++) {
        u8 *q = p + 0x160 + k * 0x50;

        func_001057F0(q, name_page(), 1);
        *(u64 *)(q + 0x20) = 0x3F80000080808080ULL;
        *(u64 *)(q + 0x30) = 0;
        *(u64 *)(q + 0x40) = 0;
    }
    plain_sprite(p + 0x660, g_0068F0F0, 0x3F0F, 0x7480808, 0x9880988, g_70000154);
    for (k = 0; k < 4; k++) {
        u8 *q = p + 0x6B0 + k * 0x50;

        func_001057F0(q, func_00106C90(g_0068F0F0, 0x3EED), 0);
        *(u64 *)(q + 0x20) = 0x3F80000080808080ULL;
        *(u64 *)(q + 0x30) = 0;
        *(u64 *)(q + 0x40) = 0;
    }
}

/* 0x001AF8D0, 0x194 bytes. The portrait window's packets: three gradients with plates, two
 * frames (0x3EE5) and the two alpha settings around them. */
void func_001AF8D0(u8 *p)
{
    u64 t = func_00106C90(g_0068F100, 0x3F97);
    int k;

    for (k = 0; k < 3; k++) {
        func_001055E0(p + k * 0x60);
        func_001057F0(p + 0x120 + k * 0x50, t, 0);
        func_001057F0(p + 0x280 + k * 0x50, t, 0);
    }
    t = func_00106C90(g_0068F0F0, 0x3EE5);
    for (k = 0; k < 2; k++) {
        u8 *q = p + (k == 0 ? 0x210 : 0x370);

        func_001057F0(q, t, 0);
        *(u64 *)(q + 0x20) = 0x3F80000080808080ULL;
        *(u64 *)(q + 0x28) = 0x6080248;
        *(u64 *)(q + 0x38) = 0x7480C88;
        *(u64 *)(q + 0x30) = 0;
        *(u64 *)(q + 0x40) = 0;
    }
    func_001050B0(p + 0x260);
    *(u64 *)(p + 0x270) = 0x48;
    *(u64 *)(p + 0x278) = 0x43;
    func_001050B0(p + 0x3C0);
    *(u64 *)(p + 0x3D0) = 0x8000000044ULL;
    *(u64 *)(p + 0x3D8) = 0x43;
}

/* 0x001AFA70, 0x1D4 bytes. The four-portrait window's packets: header parts (0x3F3E), tabs
 * (0x3EF3) and two lines of sixteen glyphs. */
void func_001AFA70(u8 *p)
{
    u64 tab = func_00106C90(g_0068F0F0, 0x3EF3);
    u64 bar = func_00106C90(g_0068F0F0, 0x3F3E);
    int k;

    for (k = 0; k < 3; k++)
        func_001057F0(p + 0xB40 + k * 0x50, bar, 0);
    for (k = 0; k < 2; k++) {
        func_001057F0(p + k * 0x50, tab, 0);
        func_001057F0(p + 0xA0 + k * 0x50, tab, 0);
    }
    for (k = 0; k < 0x10; k++) {
        u8 *q = p + k * 0x50;

        func_001057F0(q + 0x140, name_page(), 1);
        *(u64 *)(q + 0x160) = 0x3F80000080808080ULL;
        *(u64 *)(q + 0x170) = 0;
        *(u64 *)(q + 0x180) = 0;
        func_001057F0(q + 0x640, name_page(), 1);
        *(u64 *)(q + 0x660) = 0x3F80000080808080ULL;
        *(u64 *)(q + 0x670) = 0;
        *(u64 *)(q + 0x680) = 0;
    }
}

void func_001AFC70(int k, u32 mode);

/* 0x001AFC50, 0x1C bytes, matching. Opens window `k`. */
void func_001AFC50(int k)
{
    func_001AFC70(k, 0);
}

/* 0x001AFC70, 0x1A4 bytes. Opens window `k` in mode `mode` (window 3 also starts its sound and
 * its height from the player's record). */
void func_001AFC70(int k, u32 mode)
{
    TextWindow *w = &g_00693394[k];

    if (k == 4) {
        g_00693956 = 10;
    } else if (k == 3) {
        func_0023AD10(0xC, 0, 0, 0x3FFF, 0x1000);
        g_0069382E = 0;
        if (g_00693968 != 1)
            g_00693710 = (g_0073DCA3[0] & 8) ? 0xAC
                                             : (int)((g_0073DC6C < 100.0f ? g_0073DC6C : 100.0f) + 52.0f);
    } else if (k == 2) {
        g_00693706 = g_00693390[1] == 0 ? 10 : 0x14;
    } else if (k == 1 || k == 0) {
        w->b[2] = 1;
    }
    w->state = 1;
    w->b[7] = mode;
}

/* 0x001AFE20, 0x94 bytes. Closes window `k`. */
void func_001AFE20(int k)
{
    TextWindow *w = &g_00693394[k];

    if (k == 4)
        g_00693956 = 5;
    else if (k == 3)
        g_0069382E = 0;
    else if (k == 2)
        g_00693706 = 10;
    else if (k == 1 || k == 0)
        w->b[2] = 1;
    w->state = 8;
}

/* A 480-line y as one of the 448 drawn. */
static inline int scale_y(int y)
{
    return y * 0x280 / 0x1E0 * 0x1C0 / 0x200;
}

extern u8 g_00693957;
extern u8 g_00500700[][0x88];            /* the pads (+0x4C pressed, +0x4E held, +0x64/+0x65 ready) */
extern int g_0045D1C8;                   /* (small data) 1: half-line drawing */
extern int g_0056CCBC;                   /* (font state) the depth */

/* 0x001AFEC0, 0xF0 bytes. Shows window `k` again (state 2). */
void func_001AFEC0(int k)
{
    TextWindow *w = &g_00693394[k];

    if (k == 4)
        g_00693956 = g_00693957;
    else if (k == 3)
        g_0069382E = 10;
    else if (k == 2)
        g_00693706 = g_00693390[1] == 0 ? 10 : 0x14;
    else if (k == 1 || k == 0)
        w->b[2] = w->b[3];
    w->state = 2;
}

/* 0x001AFFB0, 0x98 bytes. Starts closing window `k` (state 7). */
void func_001AFFB0(int k)
{
    TextWindow *w = &g_00693394[k];

    if (k == 4)
        g_00693956 = 5;
    else if (k == 3)
        g_0069382E = 5;
    else if (k == 2)
        g_00693706 = 5;
    else if (k == 1 || k == 0)
        w->b[2] = 1;
    w->state = 7;
}

/* Pad `p`'s word at `off` when it is ready (else 0). */
static inline u32 pad_word(int p, int off)
{
    u8 *d = g_00500700[p];
    int ready = (d[0x64] & 1) ? (d[0x65] & 1) == 1 : 0;

    return ready ? *(u16 *)(d + off) : 0;
}

/* 0x001B0050, 0x2C0 bytes. Window `w`'s answer from its pad (+0x127): yes / no windows (`k` 1)
 * move between states 5 and 6 with left / right (or up / down) and answer 4 (yes) or 5 (no) with
 * a confirm, plain ones (`k` 0) 1 or 2. 0 while waiting or when input is off (+0x125). */
int func_001B0050(TextWindow *w, int k)
{
    u32 held = pad_word(w->b[7], 0x4E), press = pad_word(w->b[7], 0x4C);
    int r = 0;

    if (w->b[5] != 0)
        return 0;
    if (k == 1) {
        if (press & 0x40) {
            if (w->state == 6) {
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                r = 5;
            } else {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                r = 4;
            }
            w->state = 7;
            w->b[2] = 1;
        } else if (press & 0x10) {
            if (w->state == 5)
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
            r = 3;
            w->state = 6;
        } else if (held & 0x2000) {
            if (w->state == 5)
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            r = 3;
            w->state = 6;
        } else if (held & 0x8000) {
            if (w->state == 6)
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            r = 3;
            w->state = 5;
        }
    } else if (k == 0) {
        if (press & 0x40) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            r = 1;
            w->state = 7;
            w->b[2] = 1;
        } else if (press & 0x10) {
            func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
            r = 2;
            w->state = 7;
            w->b[2] = 1;
        }
    }
    return r;
}

/* 0x001B0310, 0x378 bytes. Each frame: steps the five windows' states (1 opening, 2 shown,
 * 3 idle, 4 waiting, 6 asking, 7 closing, 8 closed) with their timers (+0x122), and their answers
 * (+0x120: 6 / 7 while the opening or closing runs). */
void func_001B0310(void)
{
    u32 k;

    for (k = 0; k < 5; k++) {
        TextWindow *w = &g_00693394[k];
        u32 press = pad_word(w->b[7], 0x4C);
        u8 s = w->state;

        w->b[0] = 0;
        if (s == 0 || (s & 0x80))
            continue;
        w->b[2] = w->b[2] - (w->b[2] > 1 ? 1 : w->b[2]);
        if (w->b[2] != 0) {
            if (w->b[6] != 1 && (k > 1 || press == 0)) {
                if (s == 8 || s == 1)
                    w->b[0] = 6;
                else if (s == 7 || s == 2)
                    w->b[0] = 7;
                continue;
            }
            w->b[2] = 0;
        }
        s = w->state;
        if (s == 1) {
            if (k < 2) {
                w->state = 2;
                w->b[2] = 1;
            } else {
                w->state = 3;
            }
        } else if (s == 2) {
            if (k == 1) {
                w->state = 6;
            } else {
                w->state = 4;
                if (k == 2)
                    w->b[2] = g_00693390[3] == 0 ? 0x96 : 0xFA;
                else if (k == 3)
                    w->b[2] = 0x96;
                else if (k == 4)
                    w->b[2] = 100;
            }
        } else if (s == 4) {
            if (k == 2) {
                if (g_00693390[1] != 1 || func_0023A410() == 0) {
                    w->state = 7;
                    w->b[2] = 5;
                }
            } else if (k == 3 || (k == 4 && func_0023A410() == 0)) {
                w->state = 7;
                w->b[2] = 5;
            }
        } else if (s == 7) {
            if (k < 2) {
                w->state = 8;
                w->b[2] = 1;
            } else if (k == 4) {
                w->state = 8;
                w->b[2] = 5;
            } else {
                w->state = 3;
            }
        } else if (s == 8) {
            func_001AF290(k);
            if (k == 2)
                w->tw = -1;
        }
        if (k < 2 && (u32)(w->state - 4) < 3)
            w->b[0] = (u8)func_001B0050(w, k);
    }
}

/* A glyph to draw: +4 its font, +8 the glyph, +0xC..+0x18 its place and size, +0x1C the layer,
 * +0x20 its colour. */
typedef struct {
    u32 pad;
    u8 *font;
    u32 glyph;
    int x, y, w, h;
    int layer;
    u32 rgba;
} Glyph;

/* The glyph's texels and texture page. */
static inline u64 glyph_texels(Glyph *g, u32 *u, u32 *v)
{
    u8 *f = g->font;
    u32 c = g->glyph;
    u16 cols = *(u16 *)(f + 0x28), rows = *(u16 *)(f + 0x2A);

    if ((c & 0x80000000) == 0) {
        int k = *(u64 *)(f + 8) == (u64)-1 ? (int)c : (int)c % (cols * rows);

        *u = *(u16 *)(f + 0x20) * (k % cols);
        *v = *(u16 *)(f + 0x22) * (k / cols);
        if (*(u64 *)(f + 8) == (u64)-1 || c < (u32)cols * rows)
            return *(u64 *)f;
        return *(u64 *)(f + 8);
    }
    *u = (*(u16 **)(f + 0x10))[c * 2];
    *v = (*(u16 **)(f + 0x10))[c * 2 + 1];
    return (c & 0x7FFFFFFF) <= 400 ? *(u64 *)f : *(u64 *)(f + 8);
}

/* Puts glyph `g` in a packet, its y given by `ys` (scaled or not). */
static inline void draw_glyph(Glyph *g, int scaled)
{
    u32 u, v;
    u64 t = glyph_texels(g, &u, &v);
    u8 *p = func_00105860(t, 0);
    u64 z = (u64)(long long)(0xFFFE - g_0056CCBC) << 32;
    int y0 = scaled ? scale_y(g->y) : g->y, y1 = scaled ? scale_y(g->h + g->y) : g->h + g->y;

    *(u64 *)(p + 0x20) = (u64)g->rgba | 0x3F80000000000000ULL;
    *(u64 *)(p + 0x28) = (u64)(long long)(int)(u << 4 | 8) | (u64)(long long)(int)(v << 4 | 8) << 16;
    *(u64 *)(p + 0x38) = (u64)(long long)(int)((*(u16 *)(g->font + 0x20) + u) * 0x10 | 8)
                         | (u64)(long long)(int)((*(u16 *)(g->font + 0x22) + v) * 0x10 | 8) << 16;
    if (g_0045D1C8 == 1) {
        *(u64 *)(p + 0x30) = z | (u64)(long long)(g->x * 0x10 + 0x7000)
                             | (u64)(long long)(y0 * 8 + 0x7900) << 16;
        *(u64 *)(p + 0x40) = z | (u64)(long long)((g->w + g->x) * 0x10 + 0x7000)
                             | (u64)(long long)(y1 * 8 + 0x7900) << 16;
    } else {
        *(u64 *)(p + 0x30) = z | (u64)(long long)(g->x * 0x10 + 0x7000)
                             | (u64)(long long)(y0 * 0x10 + 0x7200) << 16;
        *(u64 *)(p + 0x40) = z | (u64)(long long)((g->w + g->x) * 0x10 + 0x7000)
                             | (u64)(long long)(y1 * 0x10 + 0x7200) << 16;
    }
    func_00105900(p, g->layer);
}

/* 0x001B06B0, 0x494 bytes. Draws glyph `g` (its y scaled to 448 lines). */
void func_001B06B0(Glyph *g)
{
    draw_glyph(g, 1);
}

/* 0x001B0B50, 0x364 bytes. Draws glyph `g` (its y as given). */
void func_001B0B50(Glyph *g)
{
    draw_glyph(g, 0);
}

/* A float point as a GS one, in half lines (with 1:1 drawing) or full ones. */
static inline u64 win_xyz(float x, float y, float z)
{
    float fy = g_0045D1C8 == 1 ? y * 1.1666666f * 0.5f + 1936.0f : y * 1.1666666f + 1824.0f;
    int ix = (int)((x + 1792.0f) * 16.0f), iy = (int)(fy * 16.0f), iz = (int)((65534.0f - z) * 16.0f);

    return (u64)(long long)(iz >> 4) << 32 | (u64)(long long)ix | (u64)(long long)iy << 16;
}

/* 0x001B0EC0, 0x16D8 bytes. Draws glyph `g` of a window (`g->pad` points at the window's number)
 * as a four-corner strip: whole while it is shown (states 2, 4-6), squeezed towards its middle
 * line by the window's timer (+0x122) while it closes (state 7). */
void func_001B0EC0(Glyph *g)
{
    TextWindow *w = &g_00693394[*(int *)(u32)g->pad];
    u32 u, v;
    u64 t = glyph_texels(g, &u, &v);
    u8 *p = func_00105B40(t, 0);
    u32 du = *(u16 *)(g->font + 0x20) - 1, dv = *(u16 *)(g->font + 0x22) - 1;
    u64 rgba = (u64)g->rgba | 0x3F80000000000000ULL;
    float x = (float)g->x, y0, y1, z = (float)g_0056CCBC;
    int k;

    for (k = 0; k < 4; k++)
        *(u64 *)(p + 0x20 + k * 0x18) = rgba;
    *(u64 *)(p + 0x28) = (u64)(u << 4 | 8) | (u64)(v << 4 | 8) << 16;
    *(u64 *)(p + 0x40) = (u64)((du + u) * 0x10 | 8) | (u64)(v << 4 | 8) << 16;
    *(u64 *)(p + 0x58) = (u64)(u << 4 | 8) | (u64)((dv + v) * 0x10 | 8) << 16;
    *(u64 *)(p + 0x70) = (u64)((du + u) * 0x10 | 8) | (u64)((dv + v) * 0x10 | 8) << 16;
    if (w->state == 2 || (u32)(w->state - 4) <= 2) {
        y0 = (float)g->y;
        y1 = y0 + (float)(u32)g->h;
    } else if (w->state == 7) {
        float f = (float)w->b[2];

        y0 = (float)(g->y + (int)((float)(u32)g->h * (1.0f - f)));
        y1 = (float)(u32)g->h * f + y0 + 0.0f;
    } else {
        return;
    }
    *(u64 *)(p + 0x30) = win_xyz(x, y0, z);
    *(u64 *)(p + 0x48) = win_xyz(x + (float)(u32)g->w, y0, z);
    *(u64 *)(p + 0x60) = win_xyz(x, y1, z);
    *(u64 *)(p + 0x78) = win_xyz(x + (float)(u32)g->w, y1, z);
    func_00105BE0(p, g->layer);
}

#define g_70000150 (*(int *)PS2_PTR(0x70000150))    /* (scratchpad) the frame's buffer (0 / 1) */

extern void (*g_0056CCA0)(Glyph *g);     /* (font state) the glyph drawer */
extern u32 g_0056CCA4, g_0056CCA8, g_0056CCAC, g_0056CCB0, g_0056CCB8;   /* colours, layer */
extern u8 g_0068F3E0[2][0x370], g_0068FAC0[2][0x7F0], g_00690AA0[2][0x3E0], g_00691260[2][0xC30];

/* A yes / no arrow (texture `tex`, texels (u0, v0)-(u1, v1)) at (x0, y)-(x1, y + 32). */
static inline void put_arrow(u8 *q, int tex, u64 uv0, u64 uv1, int x0, int x1, int y, int z)
{
    int sy = scale_y(y);
    u64 d = (u64)(long long)(0xFFFE - z) << 32;

    *(u64 *)(q + 0x18) = func_00106C90(g_0068F0F0, tex);
    *(u64 *)(q + 0x20) = 0x3F80000080808080ULL;
    *(u64 *)(q + 0x28) = uv0;
    *(u64 *)(q + 0x38) = uv1;
    *(u64 *)(q + 0x30) = d | (u64)(long long)(x0 * 0x10 + 0x7000)
                         | (u64)(long long)((sy * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
    *(u64 *)(q + 0x40) = d | (u64)(long long)(x1 * 0x10 + 0x7000)
                         | (u64)(long long)(((sy + 0x20) * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
}

/* 0x001B25A0, 0xAC4 bytes. Draws window `w` (number `k`) with this frame's packets: its frame
 * (growing while it opens, shrinking when closed, at least 32 x 16, centred), its text through
 * the window glyph drawer, and for questions the yes / no arrows (the chosen one lit). */
void func_001B25A0(TextWindow *w, int k)
{
    u8 *p = 0;
    int ww, hh, dx, dy;
    u32 c0, layer;

    if (k == 4)
        p = g_00691260[g_70000150];
    else if (k == 2)
        p = g_00690AA0[g_70000150];
    else if (k == 3)
        p = g_0068FAC0[g_70000150];
    else if (k == 1 || k == 0)
        p = g_0068F3E0[g_70000150];
    if (w->state == 1) {
        ww = w->w * (1 - w->b[2]);
        hh = w->h * (1 - w->b[2]);
        if (w->b[6] == 1) {
            ww = w->w;
            hh = w->h;
        }
    } else if (w->state == 8) {
        ww = w->w * w->b[2];
        hh = w->h * w->b[2];
    } else {
        ww = w->w;
        hh = w->h;
    }
    if (ww < 0x20)
        ww = 0x20;
    if (hh < 0x10)
        hh = 0x10;
    dx = (w->w - ww) / 2;
    dy = (w->h - hh) / 2;
    func_001A3D20(p, w->x + dx, w->y + dy, w->z, ww, hh, 0x80);
    func_00104F60(p, 0x370, w->b[1]);
    layer = g_0056CCB8;
    c0 = g_0056CCA4;
    if (w->state == 2 || (u32)(w->state - 4) < 4) {
        g_0056CCA0 = func_001B0EC0;
        g_0056CCB8 = 5;
        g_0056CCA4 = w->b[4];
        g_0056CCAC = w->b[4];
        g_0056CCA8 = g_0056CCA4;
        g_0056CCB0 = g_0056CCAC;
        func_00146270((const unsigned char *)(w->text), w->x + w->pad[2], w->y + w->pad[0], w->z, 0);
        if (w->state == 5 || w->state == 6) {
            int c = ww / 2, y = w->y + hh - 0x28;

            put_arrow(p + 0x320, w->state == 5 ? 0x3F3A : 0x3F39, 0x81B48, 0x1B81FC8,
                      w->x + c - 0x4C, w->x + c - 4, y, w->z);
            put_arrow(p + 0x2D0, w->state == 5 ? 0x3F39 : 0x3F3A, 0x1C81B48, 0x3781FC8,
                      w->x + c + 4, w->x + c + 0x4C, y, w->z);
        }
        g_0056CCA8 = c0;
        g_0056CCAC = c0;
        g_0056CCB0 = c0;
    }
    g_0056CCA4 = c0;
    g_0056CCB8 = layer;
}

/* A screen point in half lines (y scaled first) at the font's depth. */
static inline u64 half_xyz(int x, int y)
{
    return (u64)(long long)(0xFFFE - g_0056CCBC) << 32 | (u64)(long long)(x * 0x10 + 0x7000)
           | (u64)(long long)(scale_y(y) * 8 + 0x7900) << 16;
}

/* Fills a strip packet's colours and texels for glyph `g`. */
static inline u8 *glyph_strip(Glyph *g)
{
    u32 u, v;
    u64 t = glyph_texels(g, &u, &v);
    u8 *p = func_00105B40(t, 0);
    u32 du = *(u16 *)(g->font + 0x20) - 1, dv = *(u16 *)(g->font + 0x22) - 1;
    u64 rgba = (u64)g->rgba | 0x3F80000000000000ULL;
    int k;

    for (k = 0; k < 4; k++)
        *(u64 *)(p + 0x20 + k * 0x18) = rgba;
    *(u64 *)(p + 0x28) = (u64)(u << 4 | 8) | (u64)(v << 4 | 8) << 16;
    *(u64 *)(p + 0x40) = (u64)((du + u) * 0x10 | 8) | (u64)(v << 4 | 8) << 16;
    *(u64 *)(p + 0x58) = (u64)(u << 4 | 8) | (u64)((dv + v) * 0x10 | 8) << 16;
    *(u64 *)(p + 0x70) = (u64)((du + u) * 0x10 | 8) | (u64)((dv + v) * 0x10 | 8) << 16;
    return p;
}

/* 0x001B3070, 0xA1C bytes. Draws glyph `g` of the list window (`g->pad` points at the window):
 * its top edge slides in from the right while the window opens (state 2, by its timer / 10), the
 * glyph slides out to the left while it closes (state 7, timer / 5), still when waiting
 * (state 4); nothing otherwise. */
void func_001B3070(Glyph *g)
{
    TextWindow *w = (TextWindow *)(u32)g->pad;
    u8 *p = glyph_strip(g);
    int x = g->x, y = g->y, gw = g->w, gh = g->h;

    if (w->state == 2) {
        int x1 = x + (int)((float)w->b[2] / 10.0f * 640.0f);

        *(u64 *)(p + 0x30) = half_xyz(x1, y);
        *(u64 *)(p + 0x48) = half_xyz(x1 + gw, y);
        *(u64 *)(p + 0x60) = half_xyz(x, y + gh);
        *(u64 *)(p + 0x78) = half_xyz(x + gw, y + gh);
    } else if (w->state == 7) {
        float f = 1.0f - (float)w->b[2] / 5.0f;
        int x0 = x - (int)(f * 640.0f);

        if (x0 < -gw)
            x0 = -gw;
        *(u64 *)(p + 0x30) = half_xyz(x0, y + (int)((float)(u32)gh * f));
        *(u64 *)(p + 0x48) = half_xyz(x0 + gw, y + (int)((float)(u32)gh * f));
        *(u64 *)(p + 0x60) = half_xyz(x, y + gh);
        *(u64 *)(p + 0x78) = half_xyz(x + gw, y + gh);
    } else if (w->state == 4) {
        *(u64 *)(p + 0x30) = half_xyz(x, y);
        *(u64 *)(p + 0x48) = half_xyz(x + gw, y);
        *(u64 *)(p + 0x60) = half_xyz(x, y + gh);
        *(u64 *)(p + 0x78) = half_xyz(x + gw, y + gh);
    } else {
        return;
    }
    func_00105BE0(p, g->layer);
}

/* Glyph `g`'s sprite growing to `w2` x `h2` around its place (as in the original, the vertical
 * offset uses the width), with alpha `a`. */
static inline void zoom_glyph(u8 *p, Glyph *g, int w2, int h2, int a)
{
    int x0 = g->x - (w2 - g->w) / 2, y0 = g->y - (h2 - g->w) / 2;

    *(u64 *)(p + 0x20) = (u64)(long long)(int)((u32)a << 24 | (g->rgba & 0xFFFFFF))
                         | 0x3F80000000000000ULL;
    *(u64 *)(p + 0x30) = half_xyz(x0, y0);
    *(u64 *)(p + 0x40) = (u64)(long long)(0xFFFE - g_0056CCBC) << 32
                         | (u64)(long long)((w2 + x0) * 0x10 + 0x7000)
                         | (u64)(long long)((scale_y(h2) + scale_y(y0)) * 8 + 0x7900) << 16;
}

/* 0x001B3A90, 0x9C4 bytes. Draws glyph `g` of the portrait windows (`g->pad` points at the
 * window): it shrinks into place and fades in while the window opens (timer / 20), grows and
 * fades out while it closes (timer / 10), half transparent when waiting. */
void func_001B3A90(Glyph *g)
{
    TextWindow *w = (TextWindow *)(u32)g->pad;
    u32 u, v;
    u64 t = glyph_texels(g, &u, &v);
    u8 *p = func_00105860(t, 0);

    *(u64 *)(p + 0x28) = (u64)(u << 4) | 8 | ((u64)(v << 4) | 8) << 16;
    *(u64 *)(p + 0x38) = (u64)((*(u16 *)(g->font + 0x20) + u) * 0x10) | 8
                         | ((u64)((*(u16 *)(g->font + 0x22) + v) * 0x10) | 8) << 16;
    if (w->state == 2) {
        float f = (float)w->b[2] / 20.0f;

        zoom_glyph(p, g, g->w + (int)(f * (float)(u32)g->w * f), g->h + (int)((float)(u32)g->h * f),
                   (int)((1.0f - f) * 128.0f));
    } else if (w->state == 7) {
        float f = (float)w->b[2] / 10.0f;

        zoom_glyph(p, g, g->w + (int)((float)(u32)g->w * (1.0f - f * f)),
                   (int)((float)(u32)g->h * f), (int)(f * 128.0f));
    } else if (w->state == 4) {
        int sy = scale_y(g->y);

        *(u64 *)(p + 0x20) = (u64)(g->rgba & 0xFFFFFF) | 0x3F80000080000000ULL;
        *(u64 *)(p + 0x30) = (u64)(long long)(0xFFFE - g_0056CCBC) << 32
                             | (u64)(long long)(g->x * 0x10 + 0x7000)
                             | (u64)(long long)(sy * 8 + 0x7900) << 16;
        *(u64 *)(p + 0x40) = (u64)(long long)(0xFFFE - g_0056CCBC) << 32
                             | (u64)(long long)((g->w + g->x) * 0x10 + 0x7000)
                             | (u64)(long long)((scale_y(g->h) + sy) * 8 + 0x7900) << 16;
    } else {
        return;
    }
    func_00105900(p, g->layer);
}

/* Window `k`'s state bytes and this frame's packets. */
static inline u8 *window_state(int k)
{
    return k == 4 ? g_00692DC0[0] : k == 2 ? g_00693390 : k == 3 ? g_00692AC0[0] : 0;
}

static inline u8 *window_packets(int k)
{
    if (k == 4)
        return g_00691260[g_70000150];
    if (k == 2)
        return g_00690AA0[g_70000150];
    if (k == 3)
        return g_0068FAC0[g_70000150];
    if (k == 1 || k == 0)
        return g_0068F3E0[g_70000150];
    return 0;
}

/* Draws window `w`'s text with glyph drawer `draw` (states 2, 7 and 4). */
static inline void window_text(TextWindow *w, void (*draw)(Glyph *g))
{
    u32 layer = g_0056CCB8, c0 = g_0056CCA4;

    if (w->state == 2 || w->state == 7 || w->state == 4) {
        g_0056CCA0 = draw;
        g_0056CCB8 = 5;
        g_0056CCA4 = w->b[4];
        g_0056CCAC = w->b[4];
        g_0056CCA8 = g_0056CCA4;
        g_0056CCB0 = g_0056CCAC;
        func_00146270((const unsigned char *)(w->text), w->x + w->pad[2], w->y + w->pad[0], w->b[1], (int)w);
        g_0056CCA8 = c0;
        g_0056CCAC = c0;
        g_0056CCB0 = c0;
    }
    g_0056CCA4 = c0;
    g_0056CCB8 = layer;
}

/* 0x001B4460, 0x340 bytes. Draws the list window: its gradient (of the window's style) growing
 * up from the bottom while it opens (timer / 10) and shrinking when closed, no bar ends or
 * marks, and its text. */
void func_001B4460(TextWindow *w, int k)
{
    u8 *st = window_state(k), *p = window_packets(k);
    int h = w->h;
    int off;

    if ((u32)(w->state - 1) < 2)
        h = w->h * (10 - w->b[2]) / 10;
    else if (w->state == 8)
        h = w->h * w->b[2] / 10;
    func_001A4440(p, w->x, w->y + (w->h - h), w->z, w->w, h, st[0]);
    for (off = 0x150; off <= 0x240; off += 0x50) {
        *(u64 *)(p + off) = 0;
        *(u64 *)(p + off + 0x10) = 0;
        *(u64 *)(p + off + 0x160) = 0;
        *(u64 *)(p + off + 0x170) = 0;
    }
    func_00104F60(p, 0x3E0, w->b[1]);
    window_text(w, func_001B3070);
}

/* 0x001B47A0, 0x564 bytes. Draws a portrait window's plate: shrinking into place and fading in
 * while it opens (timer / 20), growing and fading out when it closes (timer / 10), and once
 * shown a wider plate fading out over 20 frames; then its text. */
void func_001B47A0(TextWindow *w, int k)
{
    u8 *st = window_state(k), *p = window_packets(k);
    int ww, hh, a;
    int off;

    if ((u32)(w->state - 1) < 2) {
        float f = (float)w->b[2] / 20.0f;

        st[2] = 0;
        a = (int)((1.0f - f) * 96.0f);
        ww = w->w + (int)(f * (float)w->w * f);
        hh = w->h + (int)((float)w->h * f);
    } else if ((u32)(w->state - 7) < 2) {
        float f = (float)w->b[2] / 10.0f;

        a = (int)(f * 96.0f);
        hh = (int)((float)w->h * f);
        ww = w->w + (int)((float)w->w * (1.0f - f * f));
    } else {
        ww = w->w;
        a = 0x60;
        hh = w->h;
    }
    func_001A5060(p + 0x120, w->x - (ww - w->w) / 2, w->y - (hh - w->h) / 2, w->z, ww, hh, a);
    if (w->state == 4 && st[2] < 0x14) {
        float f;
        int w2;

        st[2]++;
        f = (float)st[2] / 20.0f;
        w2 = w->w + (int)((float)w->w * 0.5f * f);
        func_001A5060(p + 0x280, w->x - (w2 - w->w) / 2, w->y, w->z, w2, w->h,
                      (int)((1.0f - f) * 64.0f));
        *(u64 *)(p + 0x240) = 0;
    } else {
        for (off = 0x2B0; off <= 0x350; off += 0x50) {
            *(u64 *)(p + off) = 0;
            *(u64 *)(p + off + 0x10) = 0;
        }
        *(u64 *)(p + 0x240) = 0;
    }
    *(u64 *)(p + 0x250) = 0;
    *(u64 *)(p + 0x3A0) = 0;
    *(u64 *)(p + 0x3B0) = 0;
    for (off = 0x20; off <= 0xE0; off += 0x60) {
        *(u64 *)(p + off) = 0;
        *(u64 *)(p + off + 0x10) = 0;
        *(u64 *)(p + off + 0x20) = 0;
        *(u64 *)(p + off + 0x30) = 0;
    }
    func_00104F60(p, 0x3E0, w->b[1]);
    window_text(w, func_001B3A90);
}

/* 0x001B4D10, 0x6EC bytes. Draws the portrait window with its title frame (0xA4 x 0x14 at
 * (0x18, 0xF0), 0xB4 in the half-screen layout, 20 higher for two-line texts) growing and fading
 * like the plate, and once shown a wider frame fading out. */
void func_001B4D10(TextWindow *w, int k)
{
    u8 *st, *p;
    int two = 0, i, fw, fh, a, x, y;

    for (i = 0; w->text[i] != 0; i++) {
        if (w->text[i] == '\n') {
            two = 1;
            break;
        }
    }
    func_001B47A0(w, k);
    st = window_state(k);
    p = window_packets(k);
    if ((u32)(w->state - 1) < 2) {
        float f = (float)w->b[2] / 20.0f;

        fw = (int)(f * 164.0f * f) + 0xA4;
        a = (int)((1.0f - f) * 128.0f);
        fh = (int)(f * 20.0f) + 0x14;
    } else if ((u32)(w->state - 7) < 2) {
        float f = (float)w->b[2] / 10.0f;

        fh = (int)(f * 20.0f);
        a = (int)(f * 128.0f);
        fw = (int)((1.0f - f * f) * 164.0f) + 0xA4;
    } else {
        fw = 0xA4;
        fh = 0x14;
        a = 0x60;
    }
    x = 0x18 - (fw - 0xA4) / 2;
    y = (g_00693968 == 1 ? 0xB4 : 0xF0) - (fh - 0x14) / 2;
    if (two)
        y -= 0x14;
    *(u64 *)(p + 0x230) = (u64)(long long)a << 24 | 0x3F80000000808080ULL;
    *(u64 *)(p + 0x240) = (u64)(long long)(0xFFFE - w->z) << 32 | (u64)(long long)(x * 0x10 + 0x7000)
                          | (u64)(long long)(scale_y(y) * 8 + 0x7900) << 16;
    *(u64 *)(p + 0x250) = (u64)(long long)(0xFFFE - w->z) << 32
                          | (u64)(long long)((fw + x) * 0x10 + 0x7000)
                          | (u64)(long long)((scale_y(fh) + scale_y(y)) * 8 + 0x7900) << 16;
    if (w->state == 4 && st[2] < 0x14) {
        float f = (float)st[2] / 20.0f;
        int d = (int)(f * 82.0f), x2 = 0x18 - d / 2, y2 = g_00693968 == 1 ? 0xB4 : 0xF0;

        if (two)
            y2 -= 0x14;
        *(u64 *)(p + 0x390) = (u64)(long long)(int)((1.0f - f) * 64.0f) << 24 | 0x3F80000000808080ULL;
        *(u64 *)(p + 0x3A0) = (u64)(long long)(0xFFFE - w->z) << 32
                              | (u64)(long long)(x2 * 0x10 + 0x7000)
                              | (u64)(long long)(scale_y(y2) * 8 + 0x7900) << 16;
        *(u64 *)(p + 0x3B0) = (u64)(long long)(0xFFFE - w->z) << 32
                              | (u64)(long long)((d + 0xA4 + x2) * 0x10 + 0x7000)
                              | (u64)(long long)((scale_y(y2) + 0x16) * 8 + 0x7900) << 16;
    } else {
        *(u64 *)(p + 0x3A0) = 0;
        *(u64 *)(p + 0x3B0) = 0;
    }
}

/* The two players' minimaps (0x290 bytes apart): +0 the zoom, +4 the scale, +0x10 / +0x14 the
 * screen offset, +0x18 / +0x1C the centre; flags in +0x43 (bits 0, 2 off, bit 3 zoomed). */
extern float g_0073DC60[];
extern u8 g_0073DF33[];
extern float g_0073DEF0[];

/* A texture coordinate pair (texel centres). */
#define GS_UV2(u, v) ((u64)(long long)((u) << 4 | 8) | (u64)(long long)((v) << 4 | 8) << 16)

/* A line point in half lines. */
static inline u64 line_xyz(int x, int sy, int z)
{
    return (u64)(long long)(0xFFFE - z) << 32 | (u64)(long long)(x * 0x10 + 0x7000)
           | (u64)(long long)(sy * 8 + 0x7900) << 16;
}

/* The pointer line from the place (mx, mz) on minimap `m` (flags `f`) to the box at (x, y)
 * into the four vertices at `p` (cleared when it is off the map or the map is hidden). */
static inline void map_pointer(u8 *p, const float *m, u8 f, float mx, float mz, int x, int y,
                               int z)
{
    int k;

    if ((f & 1) || (f & 4) || mx < 0.0f || mz < 0.0f
        || ((f & 8) && (mx < m[6] + 0.0f - m[0] * 40.0f * 500.0f
                        || m[0] * 40.0f * 500.0f + m[6] + 0.0f < mx
                        || mz < m[7] + 0.0f - m[0] * 20.0f * 500.0f
                        || m[0] * 20.0f * 500.0f + m[7] + 0.0f < mz))) {
        for (k = 0; k < 4; k++)
            *(u64 *)(p + k * 0x10) = 0;
        return;
    }
    mx = mx * m[1] + m[4] + 0.0f;
    mz = m[5] + 0.0f - mz * m[1];
    *(u64 *)(p + 0x00) = line_xyz((int)mx, scale_y((int)mz), z);
    *(u64 *)(p + 0x10) = line_xyz((int)(mx + 1.0f), scale_y((int)mz), z);
    *(u64 *)(p + 0x20) = line_xyz(x + 0x16, scale_y(y), z);
    *(u64 *)(p + 0x30) = line_xyz(x + 0x1A, scale_y(y), z);
}

/* Clears glyph packets `n`-15 of the box's name line. */
static inline void clear_glyphs(u8 *p, int n)
{
    for (; n < 0x10; n++) {
        *(u64 *)(p + n * 0x50 + 0x190) = 0;
        *(u64 *)(p + n * 0x50 + 0x1A0) = 0;
    }
}

/* 0x001B5400, 0x1E70 bytes. Draws the news box (window `w`, the portrait window's packets):
 * by its kind (+0x2ED; 0, 6, 7 a record's title, 1-4 an officer with a portrait, 5 a count x 50)
 * its width and place on the right, sliding in from the right while it opens (timer / 10) and
 * out when it closes (timer / 5); the pointer lines to the place on each player's minimap, its
 * frame, the name line (16 glyphs), the kind's icon (coloured by +0x2EE) or the count's digits,
 * and the officer's portrait. */
void func_001B5400(TextWindow *w, int k)
{
    u8 *p = window_packets(k), *st = k == 4 ? g_00692DC0[0] : k == 2 ? g_00693390
                                                : k == 3 ? g_00692AC0[0] : 0;
    u8 kind = st[0x2ED];
    int left = 0x28, port = 0, digits = 1, width, x, y, n, col, i;
    float pos[4];

    if (kind == 1 || kind == 2 || kind == 3 || kind == 4) {
        left = 0x48;
        port = 1;
    } else if (kind == 5) {
        int v = st[0x2EF] * 0x32;

        for (i = 0; i < 4; i++) {
            v = v / 10;
            if (v == 0)
                break;
            digits++;
        }
        left = digits * 0x10 + 0x24;
    }
    if (kind == 0 || kind == 6 || kind == 7)
        w->w = func_001AB3A0(16.0f, (u8 *)PS2_PTR(0x4053F0), *(u8 **)(st + 0x2F0));
    else
        w->w = func_0019AF10(16.0f, *(u16 *)(st + 0x2E8), *(u16 *)(st + 0x2EA));
    w->x = 0x1F0 - w->w - left;
    width = w->w + left + 0x10;
    if (width < 0x68)
        width = 0x68;
    y = w->y;
    if (w->state == 2)
        x = w->x + (int)((float)w->b[2] / 10.0f * (float)width);
    else if (w->state == 7)
        x = w->x + (int)((1.0f - (float)w->b[2] / 5.0f) * (float)width);
    else if (w->state == 4)
        x = w->x;
    else
        return;

    if ((g_0073DCA3[0] & 1) == 0 && (g_0073DCA3[0] & 4) == 0)
        map_pointer(p + 0x20, g_0073DC60, g_0073DCA3[0], *(float *)(st + 0x2E0),
                    *(float *)(st + 0x2E4), x, y, w->z);
    else
        map_pointer(p + 0x20, g_0073DC60, 1, 0, 0, 0, 0, 0);
    if (g_00693968 == 1) {
        if ((g_0073DF33[0] & 1) == 0 && (g_0073DF33[0] & 4) == 0)
            map_pointer(p + 0x80, g_0073DEF0, g_0073DF33[0], *(float *)(st + 0x2E0),
                        *(float *)(st + 0x2E4), x, y, w->z);
        else
            map_pointer(p + 0x80, g_0073DEF0, 1, 0, 0, 0, 0, 0);
    }
    *(u64 *)(p + 0xF0) = line_xyz(x, scale_y(y), w->z);
    *(u64 *)(p + 0x100) = line_xyz(x + 0x68, scale_y(y) + 0x1C, w->z);
    *(u64 *)(p + 0x140) = line_xyz(x + 0x68, scale_y(y), w->z);
    *(u64 *)(p + 0x150) = line_xyz(x + width, scale_y(y) + 0x1C, w->z);

    col = st[0x2EE] == 2 ? 4 : st[0x2EE] == 1 ? 1 : 3;
    pos[0] = (float)(x + left);
    pos[1] = (float)(y + 4);
    pos[2] = 0.0f;
    pos[3] = 0.0f;
    if (kind == 0 || kind == 6 || kind == 7)
        n = func_001AB430(16.0f, 16.0f, p + 0x160, *(u8 **)(st + 0x2F0), pos, col, 0x80, 1, 0);
    else
        n = func_001AB1D0(16.0f, 16.0f, p + 0x160, *(u16 *)(st + 0x2E8), *(u16 *)(st + 0x2EA), pos,
                          col, 0x80, 1, 0);
    clear_glyphs(p, n);
    for (i = 0; i < 4; i++) {
        *(u64 *)(p + 0x6E0 + i * 0x50) = 0;
        *(u64 *)(p + 0x6F0 + i * 0x50) = 0;
    }

    if (kind == 5) {
        int dx = x + 10 + digits * 0x10, sy = scale_y(y);
        u32 v = st[0x2EF] * 0x32;

        *(u64 *)(p + 0x678) = func_00106C90(g_0068F0F0, 0x3EF2);
        *(u64 *)(p + 0x688) = 0x7480008;
        *(u64 *)(p + 0x698) = 0xA480388;
        *(u64 *)(p + 0x690) = line_xyz(dx, sy, w->z);
        *(u64 *)(p + 0x6A0) = line_xyz(dx + 0x1C, sy + 0x1C, w->z);
        for (i = 0; i < digits; i++) {
            u8 *q = p + (3 - i) * 0x50;
            int d = v % 10, cx = dx - 0x10 - i * 0x10;
            u64 zz = (u64)(long long)(0xFFFE - w->z) << 32;

            *(u64 *)(q + 0x6D0) = 0x3F80000080808080ULL;
            *(u64 *)(q + 0x6D8) = GS_UV2((d % 5) * 0x28 + 200, d / 5 * 0x30);
            *(u64 *)(q + 0x6E8) = GS_UV2((d % 5) * 0x28 + 0xF0, d / 5 * 0x30 + 0x30);
            v = (int)v / 10;
            *(u64 *)(q + 0x6E0) = zz | (u64)(long long)(cx * 0x10 + 0x7000)
                                  | (u64)(long long)((sy * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
            *(u64 *)(q + 0x6F0) = zz | (u64)(long long)((cx + 0x14) * 0x10 + 0x7000)
                                  | (u64)(long long)(((sy + 0x1C) * 0x10 - 0xE00) / g_70000154 + 0x8000)
                                        << 16;
        }
    } else {
        static const int base[8] = {0x3F17, 0x3F1A, 0x3F14, 0x3F1E, 0x3F1B, 0, 0x3F1E, 0x3F1B};
        static const u32 uv0[8] = {0x7480808, 0x7480988, 0x7480B08, 0x7480C88, 0x7480E08, 0,
                                   0x7480C88, 0x7480E08};
        static const u32 uv1[8] = {0x9880988, 0x9880B08, 0x9880C88, 0x9880E08, 0x9880F88, 0,
                                   0x9880E08, 0x9880F88};
        int sy = scale_y(y - 0xF);

        if (kind < 8) {
            *(u64 *)(p + 0x678) = func_00106C90(g_0068F0F0, kind == 1 ? 0x3F1A
                                                                    : base[kind] + st[0x2EE]);
            *(u64 *)(p + 0x688) = uv0[kind];
            *(u64 *)(p + 0x698) = uv1[kind];
            *(u64 *)(p + 0x690) = line_xyz(x + 10, sy, w->z);
            *(u64 *)(p + 0x6A0) = line_xyz(x + 0x22, sy + 0x2A, w->z);
        }
    }
    func_00104F60(p, 0x7F0, w->b[1]);
    if (port && (signed char)st[0x2EC] != -0x4F) {
        u8 *f = st + g_70000150 * 0x170;
        int sy = scale_y(w->y - 0xF);

        func_001A9B30(f, (int)(signed char)st[0x2EC], 1);
        *(u64 *)(f + 0x150) = line_xyz(x + 0x24, sy, w->z);
        *(u64 *)(f + 0x160) = line_xyz(x + 0x44, sy + 0x2A, w->z);
        func_001AA2C0(f, w->b[1]);
    }
}

/* 0x001B7270, 0xA80 bytes. Draws glyph `g` of the four-portrait window (`g->pad` points at the
 * window; +0x30 of the job is the glyph's number): typed out while the window opens (glyphs up
 * to its lines less its timer), squeezed down while it closes (timer / 5), whole when shown. */
void func_001B7270(Glyph *g)
{
    TextWindow *w = (TextWindow *)(u32)g->pad;
    u8 *p = glyph_strip(g);
    int x = g->x, y = g->y, gw = g->w, gh = g->h;

    if (w->state == 2) {
        if ((u32)(w->b[3] - w->b[2]) < (u32)((int *)g)[0xC])
            return;
    } else if (w->state == 7) {
        float f = (float)w->b[2] / 5.0f;

        y = g->y + (int)((float)(u32)gh * (1.0f - f));
        gh = (int)((float)(u32)gh * f);
    } else if ((u32)(w->state - 4) > 2) {
        return;
    }
    *(u64 *)(p + 0x30) = half_xyz(x, y);
    *(u64 *)(p + 0x48) = half_xyz(x + gw, y);
    *(u64 *)(p + 0x60) = half_xyz(x, y + gh);
    *(u64 *)(p + 0x78) = half_xyz(x + gw, y + gh);
    func_00105BE0(p, g->layer);
}

/* 0x001B7CF0, 0x30 bytes. A side's text colour (1: 0xD, 0: 0xC, others 5). */
int func_001B7CF0(int side)
{
    if (side == 1)
        return 0xD;
    if (side == 0)
        return 0xC;
    return 5;
}

/* Clears the 16 glyph packets of a name line from `p` (xyz at +0x30 / +0x40). */
static inline void clear_name(u8 *p, int n)
{
    for (; n < 0x10; n++) {
        *(u64 *)(p + n * 0x50 + 0x170) = 0;
        *(u64 *)(p + n * 0x50 + 0x180) = 0;
    }
}

/* 0x001B7D20, 0xAD4 bytes. Draws the four-portrait window: the left and right officers' names
 * (+0x5C0 / +0x5C4, bit 15 of their portraits +0x5C8 / +0x5CA meaning none) on tabs coloured by
 * their sides (+0x5CD / +0x5CE), the header bar (from the side +0x5CC, growing while it opens,
 * shrinking when closed), the two portraits and the text (typed out). */
void func_001B7D20(TextWindow *w, int k)
{
    u8 *st = window_state(k), *p = window_packets(k), *f;
    float pos[4], tw;
    int n, bw, sy = g_00693968 == 1 ? 0xAA : 0xEC;
    u32 layer, c0;

    pos[2] = 0.0f;
    pos[3] = 0.0f;
    if ((*(u16 *)(st + 0x5C8) & 0x8000) == 0) {
        pos[0] = 74.0f;
        pos[1] = g_00693968 == 1 ? 173.0f : 239.0f;
        n = func_001AB1D0(16.0f, 16.0f, p + 0x140, *(u16 *)(st + 0x5C2), *(u16 *)(st + 0x5C0), pos,
                          func_001B7CF0(st[0x5CD]), 0x80, 1, &tw);
        clear_name(p, n);
        tw = tw + 6.0f;
        func_001A4C40(p, 0x32, sy, 0, (int)(u32)tw + 0x26, 0x18, 0x80, 0, 0);
    } else {
        *(u64 *)(p + 0x30) = 0;
        *(u64 *)(p + 0x40) = 0;
        *(u64 *)(p + 0x80) = 0;
        *(u64 *)(p + 0x90) = 0;
        clear_name(p, 0);
    }
    if ((*(u16 *)(st + 0x5CA) & 0x8000) == 0) {
        pos[0] = 438.0f - (float)func_0019AF10(16.0f, *(u16 *)(st + 0x5C6), *(u16 *)(st + 0x5C4));
        pos[1] = g_00693968 == 1 ? 173.0f : 239.0f;
        n = func_001AB1D0(16.0f, 16.0f, p + 0x640, *(u16 *)(st + 0x5C6), *(u16 *)(st + 0x5C4), pos,
                          func_001B7CF0(st[0x5CE]), 0x80, 1, &tw);
        clear_name(p + 0x500, n);
        tw = tw + 6.0f;
        bw = (int)(u32)tw + 0x26;
        func_001A4C40(p + 0xA0, 0x1CE - bw, sy, 0, bw, 0x18, 0x80, 0, 0);
    } else {
        clear_name(p + 0x500, 0);
    }
    if (w->state == 1)
        bw = w->w * (10 - w->b[2]) / 10;
    else if (w->state == 8)
        bw = w->w * w->b[2] / 5;
    else
        bw = w->w;
    if (st[0x5CC] == 0)
        func_001A4780(p + 0xB40, w->x, w->y, w->z, bw, w->h, 0x80, 1);
    else
        func_001A4780(p + 0xB40, w->x + (w->w - bw), w->y, w->z, bw, w->h, 0x80, 0);
    func_00104F60(p, 0xC30, w->b[1]);
    f = st + g_70000150 * 0x170;
    if ((*(u16 *)(st + 0x5C8) & 0x8000) == 0) {
        func_001A9B30(f, *(u16 *)(st + 0x5C8) & 0x7FFF, 1);
        func_001A9CE0(f, 0xC, g_00693968 == 1 ? 0xA4 : 0xE6, 0, 0x32, 0x39, 0x80, 0, 1);
        func_001AA2C0(f, w->b[1]);
    } else {
        func_001AA2B0(f);
    }
    f = st + g_70000150 * 0x170 + 0x2E0;
    if ((*(u16 *)(st + 0x5CA) & 0x8000) == 0) {
        func_001A9B30(f, *(u16 *)(st + 0x5CA) & 0x7FFF, 1);
        func_001A9CE0(f, 0x1C2, g_00693968 == 1 ? 0xA4 : 0xE6, 0, 0x32, 0x39, 0x80, 1, 1);
        func_001AA2C0(f, w->b[1]);
    } else {
        func_001AA2B0(f);
    }
    layer = g_0056CCB8;
    c0 = g_0056CCA4;
    if (w->state == 2 || w->state == 7 || w->state == 4) {
        g_0056CCA0 = func_001B7270;
        g_0056CCA8 = w->b[4];
        g_0056CCA4 = w->b[4];
        g_0056CCB8 = 5;
        g_0056CCAC = g_0056CCA8;
        g_0056CCB0 = g_0056CCA4;
        func_00146270((const unsigned char *)(w->text), w->x + w->pad[2], w->y + w->pad[0], w->b[1], (int)w);
        g_0056CCA8 = c0;
        g_0056CCAC = c0;
        g_0056CCB0 = c0;
    }
    g_0056CCA4 = c0;
    g_0056CCB8 = layer;
}

/* A menu line: its normal and chosen parts (packet lists or texts) and its kind (1 packets,
 * 0 a text). */
typedef struct {
    u32 *normal, *chosen;
    u8 kind;
    u8 pad[3];
} MenuLine;

extern MenuLine *g_00693960;             /* the menu's lines */
extern u8 g_00693964, g_00693965, g_00693966, g_00693967;   /* count, chosen, colours */
extern u8 g_0069395C, g_0069395D, g_0069395F;               /* fade: mode, layer, speed */
extern signed char g_0069395E;           /* fade: its alpha (also read by sc_ubase.c) */
extern u32 g_00669F60[4];

/* Draws text `s` at (x, y) with glyph drawer `draw`, its characters 4/5 as wide. */
static inline void narrow_text(void (*draw)(Glyph *g), const char *s, int x, int y, int z, int a)
{
    float cw = g_0056CCC0;
    u32 layer = g_0056CCB8;

    g_0056CCB8 = 5;
    g_0056CCA0 = draw;
    g_0056CCC0 = g_0056CCC0 * 512.0f / 640.0f;
    func_00146270((const unsigned char *)(s), x, y, z, a);
    g_0056CCB8 = layer;
    g_0056CCC0 = cw;
}

/* 0x001B8800, 0x90 bytes. Draws text `s` (y scaled), its characters 4/5 as wide. */
void func_001B8800(const char *s, int x, int y, int z, int a)
{
    narrow_text(func_001B06B0, s, x, y, z, a);
}

/* 0x001B8890, 0x90 bytes. The same with y as given. */
void func_001B8890(const char *s, int x, int y, int z, int a)
{
    narrow_text(func_001B0B50, s, x, y, z, a);
}

/* 0x001B8920, 0x60 bytes. The size of text `s` drawn that way. */
void func_001B8920(const char *s, int *w, int *h)
{
    float cw = g_0056CCC0;

    g_0056CCC0 = g_0056CCC0 * 512.0f / 640.0f;
    func_00146D80((const unsigned char *)(s), w, h);
    g_0056CCC0 = cw;
}

/* 0x001B8980, 0x154 bytes. Draws the five windows (window 2 by its kind: list, plate or titled
 * plate). */
void func_001B8980(void)
{
    int k;

    for (k = 0; k < 5; k++) {
        TextWindow *w = &g_00693394[k];

        if (w->state == 0 || (w->state & 0x80))
            continue;
        if (k == 4)
            func_001B7D20(w, 4);
        else if (k == 3)
            func_001B5400(w, 3);
        else if (k == 2) {
            if (g_00693390[1] == 0)
                func_001B4460(w, 2);
            else if (g_00693390[1] == 1)
                func_001B47A0(w, 2);
            else if (g_00693390[1] == 2)
                func_001B4D10(w, 2);
        } else {
            func_001B25A0(w, k);
        }
    }
}

void func_001B8C20(int half);

/* 0x001B8AF0, 0xC0 bytes, matching. Sets up both frames' window packets and resets the five windows, for
 * one or two players. */
void func_001B8AF0(void)
{
    int k;

    for (k = 0; k < 2; k++) {
        func_001AF420(g_0068F3E0[k]);
        func_001AF4D0(g_0068F3E0[0] + 0x6E0 + k * 0x7F0);
        func_001AF8D0(g_0068F3E0[0] + 0x16C0 + k * 0x3E0);
        func_001AFA70(g_0068F3E0[0] + 0x1E80 + k * 0xC30);
    }
    for (k = 0; k < 5; k++)
        func_001AEE80(k);
    func_001B8C20(g_00669F60[0] & 2);
}

/* 0x001B8BB0, 0x34 bytes. Empties the five windows. */
void func_001B8BB0(void)
{
    int k;

    for (k = 0; k < 5; k++)
        func_001AF290(k);
}

/* 0x001B8BF0, 0x24 bytes, matching. */
void func_001B8BF0(void)
{
    func_001B8BB0();
    func_001B8AF0();
}

/* 0x001B8C20, 0xE8 bytes. The portrait windows' margins, sizes and places for one or two
 * players. */
void func_001B8C20(int half)
{
    g_00693968 = half != 0;
    func_001AEE40(3, 4, 4, 0x28, 0x10);
    func_001AEE10(3, 0xB2, 0x18);
    func_001AEDB0(3, 0x200, g_00693968 == 1 ? 0xB4 : 0xA1, 0);
    func_001AEE40(4, 6, 6, 0x10, 0xC);
    func_001AEDB0(4, 0x3E, g_00693968 == 1 ? 0xC4 : 0x106, 0);
}

/* 0x001B8D10, 0x28 bytes. Empties the menu. */
void func_001B8D10(void)
{
    g_00693966 = 5;
    g_00693960 = 0;
    g_00693967 = 1;
    g_00693964 = 0;
    g_00693965 = 0;
}

/* 0x001B8D40, 0x28 bytes. The same. */
void func_001B8D40(void)
{
    g_00693966 = 5;
    g_00693960 = 0;
    g_00693967 = 1;
    g_00693964 = 0;
    g_00693965 = 0;
}

/* 0x001B8D70, 0x1B4 bytes. Draws the menu's lines, the chosen one in its own colour (texts) or
 * its own packets. */
void func_001B8D70(void)
{
    u32 k;

    for (k = 0; k < g_00693964; k++) {
        MenuLine *l = &g_00693960[k];
        u32 c0 = g_0056CCA4;

        if (l->kind == 1) {
            u32 *e = k == g_00693965 ? l->chosen : l->normal;
            int i;

            for (i = 0; i < ((u8 *)e)[4]; i++)
                func_00105900((u8 *)e[0] + i * 0x50, ((u8 *)e)[5]);
        } else if (l->kind == 0) {
            u32 *t = k == g_00693965 ? l->chosen : l->normal;
            u8 c = k == g_00693965 ? g_00693967 : g_00693966;

            g_0056CCA4 = c;
            g_0056CCAC = c;
            g_0056CCA8 = g_0056CCA4;
            g_0056CCB0 = g_0056CCAC;
            func_00146270((const unsigned char *)((const char *)t[4]), t[0], t[1], 5, 0);
            g_0056CCA8 = c0;
            g_0056CCAC = c0;
            g_0056CCB0 = c0;
            g_0056CCA4 = c0;
        }
    }
}

/* 0x001B8F30, 0x2C bytes. Resets the screen fade (mode 1, layer 6). */
void func_001B8F30(void)
{
    g_0069395C = 1;
    g_0069395D = 6;
    g_0069395E = 0;
    g_0069395F = 0;
}

/* 0x001B8F60, 0x98 bytes. Starts a fade (`mode` 0 / 2 in, 1 / 3 out, 4 cancels one running) on
 * layer `layer` at speed `speed`. Whether none was running. */
int func_001B8F60(u8 mode, u8 layer, u8 speed)
{
    int busy = g_0069395E != 0 && g_0069395E != -1;

    if (busy) {
        if (mode == 4)
            g_0069395E = 0;
        else
            g_0069395C = mode;
    } else if (mode != 4) {
        g_0069395C = mode;
    }
    g_0069395D = layer;
    g_0069395F = speed;
    return !busy;
}

/* 0x001B9000, 0x1FC bytes. Steps the fade and draws it: a full-screen grey sprite whose alpha
 * goes up (modes 0, 2) or down (1, 3), blended by subtraction (0x68, modes 2-3) or addition
 * (0x62). */
void func_001B9000(void)
{
    u64 blend = 0;
    u8 a = (u8)g_0069395E;

    if (g_0069395C == 3 || g_0069395C == 1) {
        a = (int)(a - g_0069395F) < 0 ? 0 : a - g_0069395F;
        blend = (u64)a << 32 | (g_0069395C == 3 ? 0x68 : 0x62);
    } else if (g_0069395C == 2 || g_0069395C == 0) {
        a = a + g_0069395F < 0xFF ? a + g_0069395F : 0xFF;
        blend = (u64)a << 32 | (g_0069395C == 2 ? 0x68 : 0x62);
    }
    g_0069395E = (signed char)a;
    if (a != 0) {
        u8 *s = func_00105410(), *r0 = func_001050F0(), *r1 = func_001050F0();

        *(u64 *)(r0 + 0x10) = blend;
        *(u64 *)(r0 + 0x18) = 0x43;
        func_00105230(r0, g_0069395D);
        *(u64 *)(s + 0x20) = 0xFFFF72007000ULL;
        *(u64 *)(s + 0x28) = 0xFFFF8E009000ULL;
        *(u64 *)(s + 0x18) = (u64)a << 24 | 0x3F80000000808080ULL;
        func_001054B0(s, g_0069395D);
        *(u64 *)(r1 + 0x10) = 0x8000000044ULL;
        *(u64 *)(r1 + 0x18) = 0x43;
        func_00105230(r0, g_0069395D);   /* (as in the original: the first register packet) */
    }
}

/* 0x001B9200, 0x30 bytes. Sets the windows, the menu and the fade up. */
void func_001B9200(void)
{
    g_00693968 = 0;
    func_001B8AF0();
    func_001B8D10();
    func_001B8F30();
}

/* 0x001B9230, 0x24 bytes, matching. Empties the windows and the menu. */
void func_001B9230(void)
{
    func_001B8BB0();
    func_001B8D40();
}

/* 0x001B9260, 0x48 bytes, matching. Each frame (unless paused by flag 0x200): steps and draws the
 * windows, the menu and the fade. */
void func_001B9260(void)
{
    if ((g_00669F60[0] & 0x200) == 0) {
        func_001B0310();
        func_001B8D70();
        func_001B8980();
        func_001B9000();
    }
}
