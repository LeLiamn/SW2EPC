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

/* A 480-line y as one of the 448 drawn. */
static inline int scale_y(int y)
{
    return y * 0x280 / 0x1E0 * 0x1C0 / 0x200;
}

extern u8 g_00693957;
extern u8 g_00500700[][0x88];            /* the pads (+0x4C pressed, +0x4E held, +0x64/+0x65 ready) */
extern int g_0045D1C8;                   /* (small data) 1: half-line drawing */
extern int g_0056CCBC;                   /* (font state) the depth */

int func_0023A410(void);
u8 *func_00105860(u64 tex, int a);
void func_00105900(u8 *p, int layer);

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

u8 *func_00105B40(u64 tex, int a);
void func_00105BE0(u8 *p, int layer);

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

#define g_70000150 (*(int *)0x70000150)    /* (scratchpad) the frame's buffer (0 / 1) */

extern void (*g_0056CCA0)(Glyph *g);     /* (font state) the glyph drawer */
extern u32 g_0056CCA4, g_0056CCA8, g_0056CCAC, g_0056CCB0, g_0056CCB8;   /* colours, layer */
extern u8 g_0068F3E0[2][0x370], g_0068FAC0[2][0x7F0], g_00690AA0[2][0x3E0], g_00691260[2][0xC30];

void func_001A3D20(u8 *p, int x, int y, int z, int w, int h, int alpha);
void func_00104F60(u8 *p, u32 n, int layer);
void func_00146270(const char *s, int x, int y, int z, int a);

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
        func_00146270(w->text, w->x + w->pad[2], w->y + w->pad[0], w->z, 0);
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
