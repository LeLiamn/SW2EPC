/*
 * ui_parts.c - interface drawing parts: digits, scroll bars, framed windows and fixed sprites
 * (0x001A2970-0x001A9030, just before cmnparts.c; the original file's name is unknown, it may be
 * the start of cmnparts.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The parts are GS sprite packets (0x50 bytes each: +0x18 TEX0, +0x20 RGBAQ, +0x28 UV, +0x30
 * XYZ2, +0x38 UV, +0x40 XYZ2) taken from the packet buffer (func_00105860) and queued on a layer
 * (func_00105900). Screen y values are scaled from 480 to 448 lines first.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"
typedef unsigned long long u64;

#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */

extern void *g_0068F0F0, *g_0068F0F8;     /* texture sets */

u64 func_00106C90(void *set, int tex);
u8 *func_00105860(u64 tex, int a);
void func_00105900(u8 *packet, int layer);

/* A texture coordinate pair (texel centres). */
#define GS_UV(u, v) ((u64)(long long)((u) << 4 | 8) | (u64)(long long)((v) << 4 | 8) << 16)

/* RGBAQ with alpha `a` (grey 0x80, q 1.0). */
#define GS_RGBA(a) ((u64)(long long)(a) << 24 | 0x3F80000000808080ULL)

/* A 480-line y as one of the 448 drawn. */
static inline int scale_y(int y)
{
    return y * 0x280 / 0x1E0 * 0x1C0 / 0x200;
}

/* A screen point at (x, scaled y) with depth `z` (drawn at 0xFFFE - z). */
static inline u64 gs_xyz(int x, int sy, int z)
{
    return (u64)(long long)(x * 0x10 + 0x7000)
           | (u64)(long long)((sy * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16
           | (u64)(long long)(0xFFFE - z) << 32;
}

/* Fills sprite packet `p`: texture `tex`, colour `rgba`, texels (u0, v0)-(u1, v1) on the
 * screen (x0, sy0)-(x1, sy1). */
static inline void put_sprite(u8 *p, u64 tex, u64 rgba, int u0, int v0, int u1, int v1, int x0,
                              int sy0, int x1, int sy1, int z)
{
    u64 *q = (u64 *)p;

    q[3] = tex;
    q[4] = rgba;
    q[5] = GS_UV(u0, v0);
    q[6] = gs_xyz(x0, sy0, z);
    q[7] = GS_UV(u1, v1);
    q[8] = gs_xyz(x1, sy1, z);
}

/* 0x001A2970, 0x48 bytes. The number of digits of `n` (at most 11). */
int func_001A2970(int n)
{
    int d = 1, k;

    for (k = 0; k < 10; k++, d++) {
        n = n / 10;
        if (n == 0)
            return d;
    }
    return d;
}

/* 0x001A29C0, 0xC4 bytes. The texels of large digit `n % 10` (40 x 48, five per row from
 * (200, 0)) on the four corners of packet `p`. */
void func_001A29C0(int n, u8 *p)
{
    int d = n % 10;
    int u0 = (d % 5) * 0x28 + 200, u1 = (d % 5) * 0x28 + 0xF0;
    int v0 = d / 5 * 0x30, v1 = d / 5 * 0x30 + 0x30;

    *(u64 *)(p + 0x28) = GS_UV(u0, v0);
    *(u64 *)(p + 0x38) = GS_UV(u1, v0);
    *(u64 *)(p + 0x48) = GS_UV(u0, v1);
    *(u64 *)(p + 0x58) = GS_UV(u1, v1);
}

/* 0x001A2A90, 0xA8 bytes. The texels of small digit `n % 10` (16 x 16 from (0x168, 0xC0)). */
void func_001A2A90(int n, u8 *p)
{
    int d = n % 10;
    int u = (d % 5) * 0x10, v = d / 5 * 0x10;

    *(u64 *)(p + 0x28) = GS_UV(u + 0x168, v + 0xC0);
    *(u64 *)(p + 0x38) = GS_UV(u + 0x178, v + 0xD0);
}

/* 0x001A2B40, 0x91C bytes. A vertical scroll bar of height `h` at (x, y) into eight packets
 * from `p`: the two arrows, the track (top, middle, bottom) and the thumb (top, middle, bottom)
 * for `shown` of `total` lines from `first`. */
void func_001A2B40(u8 *p, int x, int y, int z, int unused, int h, int alpha, int total,
                   int shown, int first)
{
    int track = h - 0x24;
    int size = track * shown / total;
    int at = y + 0x10 + track * first / total;
    u64 t1 = func_00106C90(g_0068F0F0, 0x3F25);
    u64 t2 = func_00106C90(g_0068F0F0, 0x3F26);
    u64 t3 = func_00106C90(g_0068F0F0, 0x3F27);
    u64 t4 = func_00106C90(g_0068F0F0, 0x3F28);
    u64 c = GS_RGBA(alpha);
    int end = track + y + 0x12;

    put_sprite(p, t1, c, 0x108, 0xB0, 0x117, 0xBF, x, scale_y(y), x + 0x10, scale_y(y + 0x10), z);
    put_sprite(p + 0x50, t2, c, 0x118, 0xB0, 0x127, 0xBF, x, scale_y(y + h - 0x10), x + 0x10,
               scale_y(h + y), z);
    put_sprite(p + 0xA0, t3, c, 0x128, 0xB0, 0x12F, 0xB1, x + 4, scale_y(y + 0x10), x + 0xC,
               scale_y(y + 0x12), z);
    put_sprite(p + 0xF0, t3, c, 0x128, 0xB2, 0x12F, 0xB5, x + 4, scale_y(y + 0x12), x + 0xC,
               scale_y(end), z);
    put_sprite(p + 0x140, t3, c, 0x128, 0xB6, 0x12F, 0xB7, x + 4, scale_y(end), x + 0xC,
               scale_y(end + 2), z);
    put_sprite(p + 0x190, t4, c, 0x128, 0xB8, 0x12F, 0xB9, x + 4, scale_y(at), x + 0xC,
               scale_y(at + 2), z);
    put_sprite(p + 0x1E0, t4, c, 0x128, 0xBA, 0x12F, 0xBD, x + 4, scale_y(at + 2), x + 0xC,
               scale_y(size + at + 2), z);
    put_sprite(p + 0x230, t4, c, 0x128, 0xBE, 0x12F, 0xBF, x + 4, scale_y(size + at + 2), x + 0xC,
               scale_y(size + 4 + at), z);
}

/* 0x001A3460, 0x194 bytes. Draws that scroll bar on layer `layer` (as in the original, its
 * last three packets are taken with the track's texture). */
void func_001A3460(int x, int y, int z, int unused, int h, int alpha, int total, int shown,
                   int first, int layer)
{
    u64 t1 = func_00106C90(g_0068F0F0, 0x3F25);
    u64 t2 = func_00106C90(g_0068F0F0, 0x3F26);
    u64 t3 = func_00106C90(g_0068F0F0, 0x3F27);
    u8 *p[8];
    int k;

    func_00106C90(g_0068F0F0, 0x3F28);
    p[0] = func_00105860(t1, 0);
    p[1] = func_00105860(t2, 0);
    for (k = 2; k < 5; k++)
        p[k] = func_00105860(t3, 0);
    for (k = 5; k < 8; k++)
        p[k] = func_00105860(t3, 0);
    func_001A2B40(p[0], x, y, z, unused, h, alpha, total, shown, first);
    for (k = 0; k < 8; k++)
        func_00105900(p[k], layer);
}

/* A framed window of 3 x 3 parts into nine packets from `p`: texture `tex`, the frame's texels
 * from (u, v) (columns 16, 8 and 16 wide, rows 8 high), at (x, y), `w` x `h` (at least 32 x 16
 * once scaled). */
static inline void put_frame(u8 *p, u64 tex, int alpha, int u, int v, int x, int y, int z, int w,
                             int h)
{
    int sy = scale_y(y), sh = scale_y(h);
    u64 c = GS_RGBA(alpha);
    int xs[4], ys[4], us[4], vs[4], i, j;

    if (w < 0x20)
        w = 0x20;
    if (sh < 0x10)
        sh = 0x10;
    xs[0] = x;
    xs[1] = x + 0x10;
    xs[2] = w - 0x20 + x + 0x10;
    xs[3] = x + 0x20 + w - 0x20;
    ys[0] = sy;
    ys[1] = sy + 8;
    ys[2] = sh - 0x10 + sy + 8;
    ys[3] = sy + sh;
    us[0] = u;
    us[1] = u + 0x10;
    us[2] = u + 0x18;
    us[3] = u + 0x28;
    vs[0] = v;
    vs[1] = v + 8;
    vs[2] = v + 0x10;
    vs[3] = v + 0x18;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++, p += 0x50)
            put_sprite(p, tex, c, us[j], vs[i], us[j + 1], vs[i + 1], xs[j], ys[i], xs[j + 1],
                       ys[i + 1], z);
    }
}

/* 0x001A3600, 0x614 bytes. A window with the frame of texture 0x3F5D (second set) at
 * (0xA8, 0x48). */
void func_001A3600(u8 *p, int x, int y, int z, int w, int h, int alpha)
{
    put_frame(p, func_00106C90(g_0068F0F8, 0x3F5D), alpha, 0xA8, 0x48, x, y, z, w, h);
}

/* 0x001A3C20, 0xF8 bytes. Draws it on layer `layer` (packets taken with texture 0x3EF4). */
void func_001A3C20(int x, int y, int z, int w, int h, int alpha, int layer)
{
    u64 t = func_00106C90(g_0068F0F0, 0x3EF4);
    u8 *p[9];
    int k;

    for (k = 0; k < 9; k++)
        p[k] = func_00105860(t, 0);
    func_001A3600(p[0], x, y, z, w, h, alpha);
    for (k = 0; k < 9; k++)
        func_00105900(p[k], layer);
}

/* 0x001A3D20, 0x614 bytes. A window with the frame of texture 0x3EF4 at (0x58, 0x74). */
void func_001A3D20(u8 *p, int x, int y, int z, int w, int h, int alpha)
{
    put_frame(p, func_00106C90(g_0068F0F0, 0x3EF4), alpha, 0x58, 0x74, x, y, z, w, h);
}

/* 0x001A4340, 0xF8 bytes. Draws it on layer `layer`. */
void func_001A4340(int x, int y, int z, int w, int h, int alpha, int layer)
{
    u64 t = func_00106C90(g_0068F0F0, 0x3EF4);
    u8 *p[9];
    int k;

    for (k = 0; k < 9; k++)
        p[k] = func_00105860(t, 0);
    func_001A3D20(p[0], x, y, z, w, h, alpha);
    for (k = 0; k < 9; k++)
        func_00105900(p[k], layer);
}

extern void *g_0068F100;                 /* a third texture set */
extern const u8 g_00425D20[][8];         /* gradient styles: top colour and alpha, line colour */
extern const u32 g_00425CD0[];           /* gauge colours (RGBA) */
extern float g_0056CCC0, g_0056CCC4;     /* (font state) the character width and height */

u8 *func_00105B40(u64 tex, int a);
void func_00105BE0(u8 *packet, int layer);
u8 *func_001050F0(void);
void func_00105230(u8 *packet, int layer);
int func_00146D80(const char *s, int a, int b);
void func_00146270(const char *s, int x, int y, int z, int a);

/* A screen point at (x, scaled y) with depth `z`, in half lines (y x 8). */
static inline u64 gs_xyz_half(int x, int sy, int z)
{
    return (u64)(long long)(x * 0x10 + 0x7000) | (u64)(long long)(sy * 8 + 0x7900) << 16
           | (u64)(long long)(0xFFFE - z) << 32;
}

/* One gouraud vertex of a strip packet (colour at +0x18 + 0x10 k, point at +0x20 + 0x10 k). */
static inline void put_vertex(u8 *p, int k, u64 rgba, u64 xyz)
{
    *(u64 *)(p + 0x18 + k * 0x10) = rgba;
    *(u64 *)(p + 0x20 + k * 0x10) = xyz;
}

/* 0x001A4440, 0x338 bytes. A gradient bar of style `style` into three strip packets from `p`
 * at (x, y), `w` x `h`: transparent at the top to the style's alpha at the bottom, a line of the
 * style's second colour two lines above the bottom and a dark line below. */
void func_001A4440(u8 *p, int x, int y, int z, int w, int h, int style)
{
    const u8 *s = g_00425D20[style];
    int sy = scale_y(y), sh = scale_y(h);
    u64 top = (u64)(s[0] | s[1] << 8 | s[2] << 16) | 0x3F80000000000000ULL;
    u64 bottom = (u64)(s[0] | s[1] << 8 | s[2] << 16 | (u32)s[3] << 24) | 0x3F80000000000000ULL;
    u64 line = (u64)(s[4] | s[5] << 8 | s[6] << 16 | (u32)s[7] << 24) | 0x3F80000000000000ULL;
    int ly;

    put_vertex(p, 0, top, gs_xyz_half(x, sy, z));
    put_vertex(p, 1, top, gs_xyz_half(w + x, sy, z));
    put_vertex(p, 2, bottom, gs_xyz_half(x, sh + sy, z));
    put_vertex(p, 3, bottom, gs_xyz_half(w + x, sh + sy, z));
    ly = scale_y(y + h - 2);
    put_vertex(p + 0x60, 0, line, gs_xyz_half(x, ly, z));
    put_vertex(p + 0x60, 1, line, gs_xyz_half(w + x, ly, z));
    put_vertex(p + 0x60, 2, line, gs_xyz_half(x, ly + 1, z));
    put_vertex(p + 0x60, 3, line, gs_xyz_half(w + x, ly + 1, z));
    ly = scale_y(y + h);
    put_vertex(p + 0xC0, 0, 0x3F80000040281A1AULL, gs_xyz_half(x, ly, z));
    put_vertex(p + 0xC0, 1, 0x3F80000040281A1AULL, gs_xyz_half(w + x, ly, z));
    put_vertex(p + 0xC0, 2, 0x3F80000040281A1AULL, gs_xyz_half(x, ly + 1, z));
    put_vertex(p + 0xC0, 3, 0x3F80000040281A1AULL, gs_xyz_half(w + x, ly + 1, z));
}

/* 0x001A4780, 0x4BC bytes. A three-part header bar (texture 0x3F3E) into three packets from `p`
 * at (x, y), `w` x `h`: a narrow and a wide end around a middle, the wide end on the right
 * unless `flip`. */
void func_001A4780(u8 *p, int x, int y, int z, int w, int h, int alpha, int flip)
{
    u64 t = func_00106C90(g_0068F0F0, 0x3F3E), c = GS_RGBA(alpha);
    int sy = scale_y(y), sy1 = scale_y(h) + sy;
    int a, b;

    if (flip == 0) {
        a = x + 8;
        put_sprite(p, t, c, 0x1B0, 0, 0x1A8, 0x1C, x, sy, a, sy1, z);
    } else {
        a = x + 0x10;
        put_sprite(p, t, c, 0x190, 0, 0x1A0, 0x1C, x, sy, a, sy1, z);
    }
    b = w - 0x18 + a;
    put_sprite(p + 0x50, t, c, 0x1A0, 0, 0x1A8, 0x1C, a, sy, b, sy1, z);
    if (flip == 0)
        put_sprite(p + 0xA0, t, c, 0x1A0, 0, 0x190, 0x1C, b, sy, b + 0x10, sy1, z);
    else
        put_sprite(p + 0xA0, t, c, 0x1A8, 0, 0x1B0, 0x1C, b, sy, b + 8, sy1, z);
}

/* 0x001A4C40, 0x420 bytes. A two-part tab (texture 0x3EF3, or 0x3F3F with `alt`) into two
 * packets from `p`, its 24-pixel end on the left unless `flip`. */
void func_001A4C40(u8 *p, int x, int y, int z, int w, int h, int alpha, int flip, int alt)
{
    int sy = scale_y(y), sy1 = scale_y(h) + sy;
    u64 t = alt == 0 ? func_00106C90(g_0068F0F0, 0x3EF3) : func_00106C90(g_0068F0F0, 0x3F3F);
    u64 c = GS_RGBA(alpha);

    if (flip == 0) {
        put_sprite(p, t, c, 0x58, 0x74, 0x40, 0x8C, x, sy, x + 0x18, sy1, z);
        put_sprite(p + 0x50, t, c, 0x40, 0x74, 0x38, 0x8C, x + 0x18, sy, w - 0x18 + x + 0x18, sy1,
                   z);
    } else {
        int m = w - 0x18 + x;

        put_sprite(p, t, c, 0x38, 0x74, 0x40, 0x8C, x, sy, m, sy1, z);
        put_sprite(p + 0x50, t, c, 0x40, 0x74, 0x58, 0x8C, m, sy, m + 0x18, sy1, z);
    }
}

/* 0x001A5060, 0x368 bytes. A wide title plate (texture 0x3F97 of the third set) into three
 * packets: two mirrored 0x90-pixel ends around a middle (`w` at least 0x120). */
void func_001A5060(u8 *p, int x, int y, int z, int w, int h, int alpha)
{
    int sy = scale_y(y), sy1 = scale_y(h) + sy;
    u64 c = GS_RGBA(alpha);
    int a = x + 0x90, b;

    if (w <= 0x120)
        w = 0x120;
    b = w - 0x120 + a;
    put_sprite(p, func_00106C90(g_0068F100, 0x3F97), c, 0, 0x4C, 0x48, 0x68, x, sy, a, sy1, z);
    put_sprite(p + 0x50, func_00106C90(g_0068F100, 0x3F97), c, 0x48, 0x4C, 0x4F, 0x68, a, sy, b,
               sy1, z);
    put_sprite(p + 0xA0, func_00106C90(g_0068F100, 0x3F97), c, 0x48, 0x4C, 0, 0x68, b, sy,
               b + 0x90, sy1, z);
}

/* A fixed sprite of texture `tex` with texels (u0, v0)-(u1, v1), drawn at (x, y), `w` x `h`. */
static inline void fixed_sprite(u8 *p, int tex, int u0, int v0, int u1, int v1, int x, int y,
                                int z, int alpha, int w, int h)
{
    put_sprite(p, func_00106C90(g_0068F0F0, tex), GS_RGBA(alpha), u0, v0, u1, v1, x, scale_y(y),
               w + x, scale_y(h) + scale_y(y), z);
}

/* 0x001A53D0, 0x1F8 bytes. Sprite 0x3F03 (0xC8, 0x60)-(0xDC, 0x74) into packet `p`. */
void func_001A53D0(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F03, 0xC8, 0x60, 0xDC, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A55D0, 0xBC bytes. Draws it on layer `layer`. */
void func_001A55D0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F03), 0);

    func_001A53D0(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A5690, 0x1F8 bytes. Sprite 0x3F04 (0xDC, 0x60)-(0xF0, 0x74) into packet `p`. */
void func_001A5690(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F04, 0xDC, 0x60, 0xF0, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A5890, 0xBC bytes. Draws it on layer `layer`. */
void func_001A5890(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F04), 0);

    func_001A5690(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A5950, 0x1F8 bytes. Sprite 0x3F05 (0xF0, 0x60)-(0x104, 0x74) into packet `p`. */
void func_001A5950(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F05, 0xF0, 0x60, 0x104, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A5B50, 0xBC bytes. Draws it on layer `layer`. */
void func_001A5B50(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F05), 0);

    func_001A5950(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A5C10, 0x1F8 bytes. Sprite 0x3F06 (0x104, 0x60)-(0x118, 0x74) into packet `p`. */
void func_001A5C10(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F06, 0x104, 0x60, 0x118, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A5E10, 0xBC bytes. Draws it on layer `layer`. */
void func_001A5E10(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F06), 0);

    func_001A5C10(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A5ED0, 0x1F8 bytes. Sprite 0x3F07 (0x118, 0x60)-(0x12C, 0x74) into packet `p`. */
void func_001A5ED0(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F07, 0x118, 0x60, 0x12C, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A60D0, 0xBC bytes. Draws it on layer `layer`. */
void func_001A60D0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F07), 0);

    func_001A5ED0(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A6190, 0x1F8 bytes. Sprite 0x3F07 (0x12C, 0x60)-(0x140, 0x74) into packet `p`. */
void func_001A6190(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F07, 0x12C, 0x60, 0x140, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A6390, 0xBC bytes. Draws it on layer `layer`. */
void func_001A6390(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F07), 0);

    func_001A6190(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A6450, 0x1F8 bytes. Sprite 0x3F07 (0x140, 0x60)-(0x154, 0x74) into packet `p`. */
void func_001A6450(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F07, 0x140, 0x60, 0x154, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A6650, 0xBC bytes. Draws it on layer `layer`. */
void func_001A6650(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F07), 0);

    func_001A6450(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A6710, 0x1F8 bytes. Sprite 0x3F08 (0x154, 0x60)-(0x168, 0x74) into packet `p`. */
void func_001A6710(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F08, 0x154, 0x60, 0x168, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A6910, 0xBC bytes. Draws it on layer `layer`. */
void func_001A6910(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F08), 0);

    func_001A6710(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A69D0, 0x1F8 bytes. Sprite 0x3F09 (0x168, 0x60)-(0x17C, 0x74) into packet `p`. */
void func_001A69D0(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3F09, 0x168, 0x60, 0x17C, 0x74, x, y, z, alpha, w, h);
}

/* 0x001A6BD0, 0xBC bytes. Draws it on layer `layer`. */
void func_001A6BD0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3F09), 0);

    func_001A69D0(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A6C90, 0x1F8 bytes. Sprite 0x3EF9 (0x0, 0xA4)-(0x14, 0xB8) into packet `p`. */
void func_001A6C90(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3EF9, 0x0, 0xA4, 0x14, 0xB8, x, y, z, alpha, w, h);
}

/* 0x001A6E90, 0xBC bytes. Draws it on layer `layer`. */
void func_001A6E90(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3EF9), 0);

    func_001A6C90(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A6F50, 0x1F8 bytes. Sprite 0x3EFA (0x14, 0xA4)-(0x28, 0xB8) into packet `p`. */
void func_001A6F50(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3EFA, 0x14, 0xA4, 0x28, 0xB8, x, y, z, alpha, w, h);
}

/* 0x001A7150, 0xBC bytes. Draws it on layer `layer`. */
void func_001A7150(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3EFA), 0);

    func_001A6F50(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* 0x001A7210, 0x1F8 bytes. Sprite 0x3EFB (0x28, 0xA4)-(0x50, 0xB8) into packet `p`. */
void func_001A7210(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    fixed_sprite(p, 0x3EFB, 0x28, 0xA4, 0x50, 0xB8, x, y, z, alpha, w, h);
}

/* 0x001A7410, 0xBC bytes. Draws it on layer `layer`. */
void func_001A7410(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, 0x3EFB), 0);

    func_001A7210(p, x, y, z, alpha, w, h);
    func_00105900(p, layer);
}

/* Draws a sprite of texture `tex` (texels (u0, v0)-(u1, v1)) at (x, y), `w` x `h`, on layer
 * `layer`. */
static inline void draw_sprite(int tex, int u0, int v0, int u1, int v1, int x, int y, int z,
                               int alpha, int layer, int w, int h)
{
    u8 *p = func_00105860(func_00106C90(g_0068F0F0, tex), 0);

    put_sprite(p, *(u64 *)(p + 0x18), GS_RGBA(alpha), u0, v0, u1, v1, x, scale_y(y), w + x,
               scale_y(h) + scale_y(y), z);
    func_00105900(p, layer);
}

/* 0x001A74D0, 0x20C bytes. Draws sprite 0x3EFC (0x50, 0xA4)-(0x78, 0xB8). */
void func_001A74D0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    draw_sprite(0x3EFC, 0x50, 0xA4, 0x78, 0xB8, x, y, z, alpha, layer, w, h);
}

/* 0x001A76E0, 0x20C bytes. Draws sprite 0x3F43 (0x17C, 0x60)-(0x1A4, 0x74). */
void func_001A76E0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    draw_sprite(0x3F43, 0x17C, 0x60, 0x1A4, 0x74, x, y, z, alpha, layer, w, h);
}

/* One textured gouraud vertex (+0x20 colour, +0x28 texels, +0x30 point; 0x18 apart). */
static inline void put_tvertex(u8 *p, int k, u64 rgba, int u, int v, u64 xyz)
{
    *(u64 *)(p + 0x20 + k * 0x18) = rgba;
    *(u64 *)(p + 0x28 + k * 0x18) = GS_UV(u, v);
    *(u64 *)(p + 0x30 + k * 0x18) = xyz;
}

/* 0x001A78F0, 0x3E0 bytes. A caption band (texture 0x3EFD) into two strip packets from `p`: a
 * plain part from x + 0xD8 to x + `w` (`w` within 0xF0-0x200) and a part fading in from `x`. */
void func_001A78F0(u8 *p, int x, int y, int z, int alpha, int w, int h)
{
    u64 c = GS_RGBA(alpha);
    int sy = scale_y(y), sy1 = scale_y(h) + sy;

    w = (w <= 0xF0 ? 0xF0 : w) <= 0x200 ? (w <= 0xF0 ? 0xF0 : w) : 0x200;
    *(u64 *)(p + 0x18) = func_00106C90(g_0068F0F0, 0x3EFD);
    put_tvertex(p, 0, c, 0x78, 0xA4, gs_xyz(x + 0xD8, sy, z));
    put_tvertex(p, 1, c, 0x7C, 0xA4, gs_xyz(x + w, sy, z));
    put_tvertex(p, 2, c, 0x78, 0xB8, gs_xyz(x + 0xD8, sy1, z));
    put_tvertex(p, 3, c, 0x7C, 0xB8, gs_xyz(x + w, sy1, z));
    *(u64 *)(p + 0x98) = func_00106C90(g_0068F0F0, 0x3EFD);
    put_tvertex(p + 0x80, 0, 0x3F80000000808080ULL, 0x78, 0xA4, gs_xyz(x, sy, z));
    put_tvertex(p + 0x80, 1, c, 0x7C, 0xA4, gs_xyz(x + 0xD8, sy, z));
    put_tvertex(p + 0x80, 2, 0x3F80000000808080ULL, 0x78, 0xB8, gs_xyz(x, sy1, z));
    put_tvertex(p + 0x80, 3, c, 0x7C, 0xB8, gs_xyz(x + 0xD8, sy1, z));
}

/* 0x001A7CD0, 0xF0 bytes. Draws that band on layer `layer`. */
void func_001A7CD0(int x, int y, int z, int alpha, int layer, int w, int h)
{
    u8 *a = func_00105B40(func_00106C90(g_0068F0F0, 0x3EFD), 0);
    u8 *b = func_00105B40(func_00106C90(g_0068F0F0, 0x3EFD), 0);

    func_001A78F0(a, x, y, z, alpha, w, h);
    func_00105BE0(a, layer);
    func_00105BE0(b, layer);
}

/* 0x001A7DC0, 0x10C bytes. A caption `s` on a band at the bottom right (size 16). */
void func_001A7DC0(const char *s, int alpha, int layer)
{
    float cw = g_0056CCC0, ch = g_0056CCC4;
    int w, a, b;

    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    w = func_00146D80(s, 0, 0);
    a = w + 0xF0 > 0x1FF ? 0x200 : w + 0xF0;
    b = w + 0xF0 > 0x1FF ? 0x200 : w + 0xF0;
    func_001A7CD0(0x200 - b, 0x15C, 0, alpha, layer, a, 0x14);
    func_00146270(s, 0x2D8 - (w + 0xF0), 0x15E, layer, 0);
    g_0056CCC0 = cw;
    g_0056CCC4 = ch;
}

/* A gauge's frame (texture 0x3F23) into three packets from `p`: its two ends and middle, `w`
 * wide at (x, sy), `size` x 16 x 7/6 high, with `c`'s alpha. */
static inline void put_gauge_frame(u8 *p, float size, int x, int sy, int z, const u32 *c, int w)
{
    u64 a = GS_RGBA(((const u8 *)c)[3]);
    int sy1 = (int)(size * 16.0f * 1.1666666f) + sy;

    put_sprite(p, func_00106C90(g_0068F0F0, 0x3F23), a, 0xA8, 0xB0, 0xB0, 0xC0, x - 7, sy, x + 1,
               sy1, z);
    put_sprite(p + 0x50, func_00106C90(g_0068F0F0, 0x3F23), a, 0xB0, 0xB0, 0xB7, 0xC0, x + 1, sy,
               w + x + 1, sy1, z);
    put_sprite(p + 0xA0, func_00106C90(g_0068F0F0, 0x3F23), a, 0xB8, 0xB0, 0xC0, 0xC0, w + x + 1,
               sy, x + 9 + w, sy1, z);
}

/* 0x001A7ED0, 0x5C4 bytes. A gauge into five packets from `p`: its frame, the second value
 * (`b` of the width, colour `cb`) and the first (`a`, colour `ca`) over it. */
void func_001A7ED0(float a, float b, float size, u8 *p, int x, int y, int z, const u32 *ca,
                   const u32 *cb, int w)
{
    int sy = scale_y(y), sy1 = (int)(size * 8.0f * 1.1666666f) + sy;

    put_gauge_frame(p, size, x, sy, z, ca, w);
    put_sprite(p + 0xF0, func_00106C90(g_0068F0F0, 0x3EF7), (u64)*cb | 0x3F80000000000000ULL,
               0x78, 0x94, 0x7F, 0x9C, x, sy, (int)((float)w * b) + x, sy1, z);
    put_sprite(p + 0x140, func_00106C90(g_0068F0F0, 0x3EF7), (u64)*ca | 0x3F80000000000000ULL,
               0x78, 0x94, 0x7F, 0x9C, x, sy, (int)((float)w * a) + x, sy1, z);
}

/* 0x001A84A0, 0x124 bytes. Draws that gauge on layer `layer`. */
void func_001A84A0(float a, float b, float size, int x, int y, int z, const u32 *ca,
                   const u32 *cb, int w, int layer)
{
    u8 *p[5];
    int k;

    for (k = 0; k < 5; k++)
        p[k] = func_00105860(func_00106C90(g_0068F0F0, 0x3EFC), 0);
    func_001A7ED0(a, b, size, p[0], x, y, z, ca, cb, w);
    for (k = 0; k < 5; k++)
        func_00105900(p[k], layer);
}

/* 0x001A85D0, 0x30 bytes. The same with colours `ia` and `ib` of the gauge colours. */
void func_001A85D0(float a, float b, float size, int x, int y, int z, int ia, int ib, int w,
                   int layer)
{
    func_001A84A0(a, b, size, x, y, z, &g_00425CD0[ia], &g_00425CD0[ib], w, layer);
}

/* 0x001A8600, 0x6E8 bytes. A three-value gauge into six packets from `p`: its frame, value `a`
 * (colour `ca`), value `b` after it (colour `cb` with alpha `ab`) and value `c` (colour `cc`
 * with alpha `ac`). */
void func_001A8600(float a, float b, float c, float size, u8 *p, int x, int y, int z,
                   const u32 *ca, const u8 *cb, const u8 *cc, int w, int unused, u8 ab, u8 ac)
{
    int sy = scale_y(y), sy1 = (int)(size * 8.0f * 1.1666666f) + sy;
    int e = (int)((float)w * a) + x;

    put_gauge_frame(p, size, x, sy, z, ca, w);
    put_sprite(p + 0xF0, func_00106C90(g_0068F0F0, 0x3EF7), (u64)*ca | 0x3F80000000000000ULL,
               0x78, 0x94, 0x7F, 0x9C, x, sy, e, sy1, z);
    put_sprite(p + 0x140, func_00106C90(g_0068F0F0, 0x3EF7),
               (u64)(cb[0] | cb[1] << 8 | cb[2] << 16 | (u32)ab << 24) | 0x3F80000000000000ULL,
               0x78, 0x94, 0x7F, 0x9C, e, sy, (int)((float)w * b) + e, sy1, z);
    put_sprite(p + 0x190, func_00106C90(g_0068F0F0, 0x3EF7),
               (u64)(cc[0] | cc[1] << 8 | cc[2] << 16 | (u32)ac << 24) | 0x3F80000000000000ULL,
               0x78, 0x94, 0x7F, 0x9C, x, sy, (int)((float)w * c) + x, sy1, z);
}

/* 0x001A8CF0, 0x1B4 bytes. Draws that gauge on layer `layer`: five packets, then the sixth
 * between two alpha settings (GS register 0x43: 0x48, then back to 0x8000000044). */
void func_001A8CF0(float a, float b, float c, float size, int x, int y, int z, const u32 *ca,
                   const u8 *cb, const u8 *cc, int w, u8 ab, u8 ac, int layer)
{
    u8 *p[6], *r;
    int k;

    for (k = 0; k < 6; k++)
        p[k] = func_00105860(func_00106C90(g_0068F0F0, 0x3EFC), 0);
    func_001A8600(a, b, c, size, p[0], x, y, z, ca, cb, cc, w, layer, ab, ac);
    for (k = 0; k < 5; k++)
        func_00105900(p[k], layer);
    r = func_001050F0();
    *(u64 *)(r + 0x10) = 0x48;
    *(u64 *)(r + 0x18) = 0x43;
    func_00105230(r, layer);
    func_00105900(p[5], layer);
    r = func_001050F0();
    *(u64 *)(r + 0x10) = 0x8000000044ULL;
    *(u64 *)(r + 0x18) = 0x43;
    func_00105230(r, layer);
}

/* 0x001A8EB0, 0x48 bytes. The same with colours `ia`, `ib` and `ic` of the gauge colours. */
void func_001A8EB0(float a, float b, float c, float size, int x, int y, int z, int ia, int ib,
                   int ic, int w, int layer, u8 ab, u8 ac)
{
    func_001A8CF0(a, b, c, size, x, y, z, &g_00425CD0[ia], (const u8 *)&g_00425CD0[ib],
                  (const u8 *)&g_00425CD0[ic], w, ab, ac, layer);
}
