/*
 * text_window.c - the battle's text windows (0x001AE550-..., after Bullet.c; the original file's
 * name is unknown). Written so far: from 0x001AE550.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Five windows of 0x128 bytes at 0x00693394: 0 and 1 plain, 2 a list (state at 0x00693390),
 * 3 one with two small portraits (0x00692AC0), 4 one with four portraits (0x00692DC0).
 */

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
extern void *g_0068F0F0, *g_0068F100;
extern u64 g_004053F0, g_004053F8;       /* the names' font pages */
extern u16 g_00405418, g_0040541A;

u8 func_00147070(const char *s);
void func_00120928(char *to, const char *from);
void func_00146D80(const char *s, int *w, int *h);
void func_00147160(const char *s, char *out, int w, int *tw, int *th);
void func_001A9450(u8 *f, int x, int y, int z, int w, int h, int alpha, int flip, int half);
u64 func_00106C90(void *set, int tex);
void func_001057F0(u8 *p, u64 tex0, int a);
void func_001055E0(u8 *p);
void func_001050B0(u8 *p);
void func_0023AD10(int a, int b, int c, int d, int e);

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
    w->b[3] = func_00147070(s);
    if (wrap == 0) {
        func_00120928(w->text, s);
        g_0056CCC0 = 16.0f;
        g_0056CCC4 = 16.0f;
        func_00146D80(s, &w->tw, &w->th);
    } else {
        g_0056CCC0 = 16.0f;
        g_0056CCC4 = 16.0f;
        func_00147160(s, w->text, w->w - w->pad[2] - w->pad[3], &w->tw, &w->th);
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
static inline void plain_sprite(u8 *p, void *set, int tex, u64 uv0, u64 uv1, int g)
{
    u64 xy = (u64)(long long)(-0xE00 / g + 0x8000) << 16 | 0xFFFE00007000ULL;

    func_001057F0(p, func_00106C90(set, tex), 0);
    *(u64 *)(p + 0x20) = 0x3F80000080808080ULL;
    *(u64 *)(p + 0x28) = uv0;
    *(u64 *)(p + 0x38) = uv1;
    *(u64 *)(p + 0x30) = xy;
    *(u64 *)(p + 0x40) = xy;
}

#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */

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

void func_001AFC70(int k, u8 mode);

/* 0x001AFC50, 0x1C bytes, matching. Opens window `k`. */
void func_001AFC50(int k)
{
    func_001AFC70(k, 0);
}

/* 0x001AFC70, 0x1A4 bytes. Opens window `k` in mode `mode` (window 3 also starts its sound and
 * its height from the player's record). */
void func_001AFC70(int k, u8 mode)
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
