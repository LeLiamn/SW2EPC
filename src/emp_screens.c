/*
 * emp_screens.c - small pieces of the Empire screens between 0x003AF920 and 0x003BD240: the
 * players' tactic bits, the officer-list screen state (0x007BAF10), the screen textures
 * (0x0045D7FC) and their drawers, and the turn report state (0x007BB510). Original file names
 * unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_SCREENS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_003B4A40();

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"
typedef unsigned long long u64;

extern u8 g_0045D7EC[2];                 /* (small data) the players' tactic bits */
extern int g_0045D7F0, g_0045D7F4;       /* (small data) */
#ifdef SW2E_PC
extern ps2ptr g_0045D7FC_a;                   /* (small data) the screen textures */
#define g_0045D7FC ((u8 *)PS2_PTR(g_0045D7FC_a))
#define g_0045D7FC_SET(v) (g_0045D7FC_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7FC;
#define g_0045D7FC_a (*(ps2ptr *)&g_0045D7FC)
#define g_0045D7FC_SET(v) (g_0045D7FC = (v))
#endif
extern char g_0045B6D8[];                /* the allocations' source name */
extern int (*g_0045B580[0x1D])(void), (*g_0045B620[0x1E])(void);
extern u16 g_0045B600[][2], g_0045B610[][2];
extern int g_0045BBD0[0xC];
extern u8 g_007BAF10[], g_007BB510[];
extern int g_007BAF1C;
extern float g_007BAEF8, g_007BAED8;
extern u8 g_007BAEFD, g_007BAEDD;

#define TEX g_0045D7FC
#define TEX_SET(v) g_0045D7FC_SET(v)

int func_0039B980(void);
void func_003B9D80(void);
void func_003B9E00(void);
void func_003B9ED0(void);
void func_003B9FD0(void);
int func_003BB8E0(u8 k, int a);

/* 0x003AF920, 0x38 bytes, matching. */
void func_003AF920(void)
{
    if (func_0039B980() == 1) {
        func_003A9480(0);
        func_003AE8E0(8);
    }
}

/* 0x003AFAE0, 0x20 bytes, matching. */
void func_003AFAE0(void)
{
    func_00118850(g_0045D7EC, 2);
}

/* 0x003AFB00, 0x44 bytes. */
int func_003AFB00(u32 s, u32 k)
{
    if (s < 2 && k < 5)
        return (g_0045D7EC[s] & 1 << (k & 0x1F)) != 0;
    return 0;
}

/* 0x003AFB50, 0x78 bytes. */
void func_003AFB50(u32 s, u32 k, int on)
{
    if (s >= 2 || k >= 5)
        return;
    if (on == 0)
        g_0045D7EC[s] &= ~(1 << (k & 0x1F));
    else
        g_0045D7EC[s] |= 1 << (k & 0x1F);
}

/* 0x003AFD40, 0x28 bytes, matching. */
int func_003AFD40(u32 s)
{
    return func_0036F5C0(func_0035D5A0(s)) != 0;
}

/* 0x003AFD70, 0x20 bytes, matching. */
int func_003AFD70(int s)
{
    return func_0036F5E0(s) != 0;
}

/* 0x003B0310, 0x30 bytes. */
int func_003B0310(u8 *o)
{
    if (*(int *)(o + 0x10) == 0)
        return 0x19F;
    return func_0034A790(o);
}

/* 0x003B0470, 0x34 bytes. */
int func_003B0470(u32 k, int b)
{
    if (k < 0x1D)
        return g_0045B580[k]();
    return 0;
}

/* 0x003B0B90, 0x38 bytes, matching. */
int func_003B0B90(void)
{
    if (func_0032BC30() != 5) {
        g_0045D7F4 = 1;
        func_0032D150();
    }
    return 1;
}

/* 0x003B0BD0, 0x34 bytes, matching. */
char *func_003B0BD0(int k)
{
    if (k < 0x1C)
        return func_002F2970(k);
    return func_00372740(k);
}

/* 0x003B0DA0, 0x48 bytes. */
void func_003B0DA0(void)
{
    func_002ED190(0x25);
    g_007BAEF8 = 1.0f;
    g_007BAEFD &= 0xFE;
}

/* 0x003B0DF0, 0x48 bytes. */
void func_003B0DF0(void)
{
    func_002ED190(0x26);
    g_007BAED8 = 1.0f;
    g_007BAEDD &= 0xFE;
}

/* 0x003B1470, 0x1C bytes, matching. */
void func_003B1470(void)
{
    func_0032BB70();
}

/* 0x003B2000, 0xC bytes, matching. */
u8 *func_003B2000(void)
{
    return g_007BAF10;
}

/* 0x003B20F0, 0x44 bytes, matching. */
void func_003B20F0(void)
{
    if (*(int *)(func_003B2000() + 0xC) == 0) {
        func_0032E830();
        *(int *)(func_003B2000() + 0xC) = 1;
        g_0045D7F0 = 0;
    }
}

/* 0x003B2140, 0x30 bytes. */
void func_003B2140(void)
{
    func_003B1490(g_007BAF10, g_007BAF1C);
    func_003B0A40();
}

/* 0x003B2170, 0x24 bytes, matching. */
void func_003B2170(void)
{
    func_0032F530();
    func_0032F640();
}

/* 0x003B2200, 0x44 bytes, matching. */
void func_003B2200(void)
{
    if (g_0045D7F0 == 0 && func_00102960(0) != 0) {
        func_0032B990();
        g_0045D7F0 = 1;
        func_001037F0(1);
    }
}

/* 0x003B2250, 0x68 bytes. */
void func_003B2250(void)
{
    if (g_0045D7F4 == 2)
        func_003B1470();
    else if (g_0045D7F4 == 1)
        func_003B1320();
    else if (g_0045D7F4 == 0)
        func_003B0E40();
}

/* 0x003B22C0, 0x74 bytes. */
int func_003B22C0(float dt)
{
    if (g_0045D7F4 == 2)
        func_003B0B90();
    else if (g_0045D7F4 == 1)
        func_003B1A90();
    else if (g_0045D7F4 == 0)
        func_003B14E0();
    func_003B2200();
    return 1;
}

/* 0x003B2340, 0x1C bytes, matching. */
u8 *func_003B2340(void)
{
    return func_00390940();
}

/* 0x003B2360, 0x30 bytes. */
void func_003B2360(u16 *out, int k)
{
    out[0] = g_0045B600[k][0];
    out[1] = g_0045B600[k][1];
}

/* 0x003B2390, 0x30 bytes. */
void func_003B2390(u16 *out, int k)
{
    out[0] = g_0045B610[k][0];
    out[1] = g_0045B610[k][1];
}

/* 0x003B23C0, 0x34 bytes. */
int func_003B23C0(u32 k)
{
    if (k < 0x1E)
        return g_0045B620[k]();
    return 0;
}

/* 0x003B3470, 0x24 bytes. */
void func_003B3470(void)
{
    *(int *)(func_003B2340() + 0x158) = 0x70;
}

/* 0x003B38F0, 0x48 bytes, matching. Loads the screen textures. */
void func_003B38F0(void)
{
    TEX_SET(func_001026D0(1, 0x89, 0, 1, 0, 0, g_0045B6D8, 0x159));
    func_00102960(1);
}

/* 0x003B3940, 0x2C bytes, matching. */
void func_003B3940(void)
{
    if (TEX != 0) {
        func_00102EC0(TEX);
        TEX_SET(0);
    }
}

/* 0x003B3970, 0x24 bytes, matching. */
void func_003B3970(int x, int y, int a, int k)
{
    func_003B39A0(x, y, a, 0x18, 0x18, k);
}

/* 0x003B4720, 0x20 bytes, matching. */
void func_003B4720(int x, int y, int a, int b)
{
    func_003B4740(x, y, a, b, 1, 0);
}

/* 0x003B4DE0, 0x68 bytes, matching. */
void func_003B4DE0(int x, int y, int a, int p3, int p4, int p5, int p6)
{
    func_003B4A40(TEX, 10, x, y, a, 0x78, 0x18, 0, 0, 0x78, 0x18, p3, p4 & 0xFF, p5, p6);
}

/* 0x003B4E50, 0x68 bytes, matching. */
void func_003B4E50(int x, int y, int a, int p3, int p4, int p5, int p6)
{
    func_003B4A40(TEX, 0xC, x, y, a, 0x80, 0x20, 0, p4 * 0x20, 0x80, 0x20, 0x80, p3, p5, p6);
}

/* 0x003B51E0, 0x58 bytes, matching. */
void func_003B51E0(int x, int y, int a, int p3)
{
    func_001ABEA0(TEX, 0x15, x, y, a, 0x14, 0x14, 0, 0, 0x14, 0x14, 0x80, p3, 0);
}

/* 0x003B5240, 0x58 bytes, matching. */
void func_003B5240(int x, int y, int a, int p3)
{
    func_001ABEA0(TEX, 0x16, x, y, a, 0x18, 0x14, 0, 0, 0x18, 0x14, 0x80, p3, 0);
}

/* 0x003B52A0, 0x58 bytes, matching. */
void func_003B52A0(int x, int y, int a, int p3)
{
    func_001ABEA0(TEX, 0x1B, x, y, a, 0x18, 0x14, 0, 0, 0x18, 0x14, 0x80, p3, 0);
}

/* 0x003B5410, 0x64 bytes, matching. */
void func_003B5410(int x, int y, int a, int p3, int p4, int p5)
{
    func_001ABEA0(TEX, 0x23, x, y, a, 0x60, 0x18, 0, p5 * 0x18, 0x60, 0x18, p3, p4, 0);
}

/* 0x003B55A0, 0x40 bytes, matching. */
void func_003B55A0(int x, int y, int a, int p3)
{
    func_001ABE40(TEX, 0x25, x, y, a, 0x30, 0x10, 0x80, p3, 0);
}

/* 0x003B55E0, 0x40 bytes, matching. */
void func_003B55E0(int x, int y, int a, int p3)
{
    func_001ABE40(TEX, 0x26, x, y, a, 0x40, 0xF, 0x80, p3, 0);
}

/* 0x003B5620, 0x40 bytes, matching. */
void func_003B5620(int x, int y, int a, int p3)
{
    func_001ABE40(TEX, 0x27, x, y, a, 0x30, 0x10, 0x80, p3, 0);
}

/* 0x003B5750, 0x60 bytes, matching. */
void func_003B5750(int k, int x, int y, int a, int p4)
{
    func_001ABEA0(TEX, 0x2D, x, y, a, 0x40, 0x10, 0, k * 0x10, 0x40, 0x10, 0x80, p4, 0);
}

/* 0x003B57B0, 0x6C bytes, matching. */
void func_003B57B0(int k, int x, int y, int a, int p4, int p5)
{
    func_001ABEA0(TEX, 0x2E, x, y, a, 0x48, 0x14, 0, k * 0x14, 0x48, 0x14, p5 & 0xFF, p4, 0);
}

/* 0x003B58A0, 0x40 bytes, matching. */
void func_003B58A0(int x, int y, int a, int b, int p4)
{
    func_001ABE40(TEX, 0x46, x, y, a, 0x78, 0x10, b, p4, 0);
}

/* 0x003B58E0, 0x44 bytes, matching. */
void func_003B58E0(int x, int y, int a, int w, int h, int p5)
{
    func_001ABE40(TEX, 0x48, x, y, a, w, h, 0x80, p5, 0);
}

/* 0x003B5930, 0x40 bytes, matching. */
void func_003B5930(int x, int y, int a, int p3)
{
    func_001ABE40(TEX, 0x47, x, y, a, -1, -1, 0x80, p3, 0);
}

/* 0x003B5CA0, 0x1C bytes, matching. */
void func_003B5CA0(int v, int x, int y, int z, int alpha, int layer)
{
    func_003B5B30(v, x, y, z, alpha, layer, 0);
}

/* 0x003B5DF0, 0x1C bytes, matching. */
void func_003B5DF0(int k, int x, int y, int z, int alpha, int layer)
{
    func_003B5D50(k, x, y, z, alpha, layer, 0);
}

/* 0x003B5E90, 0xC bytes, matching. */
u8 *func_003B5E90(void)
{
    return g_007BB510;
}

/* 0x003B6CD0, 0x3C bytes, matching. */
void func_003B6CD0(void)
{
    int *p = (int *)func_003B5E90();

    p[1] = 0;
    p[0x1C3] = 0;
    p[0x1C4] = 0;
    p[0x1C5] = 0;
    p[0x1C7] = 0;
    p[0x1C8] = 0;
    p[0] = 1;
}

/* 0x003B9760, 8 bytes, matching. */
void func_003B9760(void)
{
}

/* 0x003BA160, 0x34 bytes, matching. */
void func_003BA160(void)
{
    func_003B9D80();
    func_003B9E00();
    func_003B9ED0();
    func_003B9FD0();
}

/* 0x003BA790, 0x58 bytes. */
int func_003BA790(int o)
{
    int v = func_002F27D0(o);

    if (v == 0xAF || v == 0xAE || v == 0xAB || v == 0xF)
        return 1;
    return 0;
}

/* 0x003BA8C0, 0x28 bytes, matching. */
void func_003BA8C0(int v)
{
    *(int *)(func_003B5E90() + 0x75C) = v;
}

/* 0x003BAB40, 0x30 bytes, matching. */
int func_003BAB40(int k)
{
    return *(int *)(func_00329850() + k * 0x20);
}

/* 0x003BBFA0, 0x30 bytes, matching. */
void func_003BBFA0(void)
{
    u8 *p = func_003B5E90();

    if (p != 0)
        func_003BB8E0(p[0x763], 2);
}

/* 0x003BCA80, 0x1C bytes, matching. */
u8 *func_003BCA80(void)
{
    return func_00390940();
}

/* 0x003BCAA0, 0x3C bytes. */
int func_003BCAA0(int k)
{
    if (k < 0 || k > 0xB)
        return g_0045BBD0[0];
    return g_0045BBD0[k];
}

/* 0x003BD210, 0x1C bytes, matching. */
u8 *func_003BD210(void)
{
    return func_00390940();
}

/* 0x003AFBD0, 0x80 bytes. Whether side `s` has tactic 1, 2, 3 or 9. */
int func_003AFBD0(int s)
{
    if (func_003F7780(s, 1) != 0 || func_003F7780(s, 2) != 0 || func_003F7780(s, 3) != 0)
        return 1;
    return func_003F7780(s, 9) != 0;
}

/* 0x003AFC50, 0x80 bytes. Tactic 4, 5, 6 or 9. */
int func_003AFC50(int s)
{
    if (func_003F7780(s, 4) != 0 || func_003F7780(s, 5) != 0 || func_003F7780(s, 6) != 0)
        return 1;
    return func_003F7780(s, 9) != 0;
}

/* 0x003AFCD0, 0x64 bytes. Tactic 7, 8 or 9. */
int func_003AFCD0(int s)
{
    if (func_003F7780(s, 7) != 0 || func_003F7780(s, 8) != 0)
        return 1;
    return func_003F7780(s, 9) != 0;
}

/* 0x003B0430, 0x40 bytes, matching. Battle officer `o`'s side (3: none). */
u32 func_003B0430(u8 *o)
{
    u8 *u;

    if (o == 0 || (*(u32 *)(o + 0xB8) & 1) == 0)
        return 3;
    u = PS2_LOADP(u8 *, (o + 0x10));
    if (u == 0)
        return 3;
    return u[0x79];
}

/* 0x003B0C10, 0x5C bytes. An encyclopedia entry's title (hidden until seen). */
char *func_003B0C10(int k)
{
    if (k >= 0x177)
        return 0;
    if (func_003A1C60(k - 0x87) == 0)
        return func_00372470();
    return func_00372990(k - 0x1B);
}

/* Turn report messages, officer counts, report pages and the battle screen glue (parts of
 * 0x003B8090-0x003BD890). */

extern u32 g_7000015C;
extern u8 g_00669D60[];
extern int g_0041C220[5], g_0041C240[5], g_0041C260[6], g_0041C280[0x17], g_0041C2E0[3];
extern int g_0041C2F0[6], g_0041C310[6], g_0041C340[0x2D];
extern u8 g_007BC1A0[];

#define RAND16() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_003BB520(int k);
void func_003BBFD0(void);
void func_003BD2A0(u8 *p);
void func_0039F330(void);
void func_003BA8F0(int a, int b, int c, int d, int e);

static u8 pick(int *t, int n)
{
    return t[RAND16() % n];
}

/* 0x003B8090, 0x84 bytes. */
u8 func_003B8090(void)
{
    return pick(g_0041C220, 5);
}

/* 0x003B8120, 0x84 bytes. */
u8 func_003B8120(void)
{
    return pick(g_0041C240, 5);
}

/* 0x003B81B0, 0x80 bytes. */
int func_003B81B0(u8 k)
{
    switch (k) {
    case 0x16:
        return 0x2A;
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
        return 0x29;
    default:
        return func_00329810() < func_003297D0() ? 0x2B : 0x2C;
    }
}

/* 0x003B8230, 0x90 bytes. */
u8 func_003B8230(void)
{
    return pick(g_0041C260, 6);
}

/* 0x003B82C0, 0x88 bytes. */
int func_003B82C0(void)
{
    char c = func_003B7CF0();

    if (c == 0x11)
        return 0x37;
    if (c == 0x10)
        return 0x36;
    if (c == 0xF)
        return 0x35;
    if (c == 0xE)
        return 0x34;
    if (c == 0xD)
        return 0x33;
    return 0x38;
}

/* 0x003B8350, 0x74 bytes. */
u8 func_003B8350(void)
{
    return pick(g_0041C280, 0x17);
}

/* 0x003B83D0, 0x6C bytes. */
u8 func_003B83D0(void)
{
    return pick(g_0041C2E0, 3);
}

/* 0x003B8530, 0x90 bytes. */
u8 func_003B8530(void)
{
    return pick(g_0041C2F0, 6);
}

/* 0x003B87C0, 0x90 bytes. */
u8 func_003B87C0(void)
{
    return pick(g_0041C310, 6);
}

/* 0x003B8850, 0xAC bytes. Another player-force officer sharing the report officer's tie. */
u32 func_003B8850(void)
{
    u32 r = *(u32 *)(func_003B5E90() + 0x724), o;
    int f = func_00327D50();

    for (o = 0; (int)o <= 0x19E; o++) {
        if (f == func_002F4080(o) && r != o && func_002F2E20(o) == r)
            return o;
    }
    return 0x19F;
}

/* 0x003B8900, 0xBC bytes. */
int func_003B8900(int f, int v)
{
    u32 r = *(u32 *)(func_003B5E90() + 0x724), o;
    int n = 0;

    for (o = 0; (int)o < 0x19F; o++) {
        if (o < 0x19F && f == func_002F4080(o) && r != o && v == func_002F4A70(o))
            n++;
    }
    return n;
}

/* 0x003B89C0, 0xB0 bytes. */
int func_003B89C0(int f)
{
    u32 r = *(u32 *)(func_003B5E90() + 0x724), o;
    int n = 0;

    for (o = 0; (int)o < 0x19F; o++) {
        if (o < 0x19F && f == func_002F4080(o) && r != o && func_002F4660(o) == 0)
            n++;
    }
    return n;
}

/* 0x003B8CD0, 0x98 bytes. */
int func_003B8CD0(int v)
{
    char d = g_00669D60[0x21];
    int k;

    func_003B5E90();
    if (d == 4)
        k = 0x14;
    else if (d == 3 || d == 2)
        k = 0x12;
    else
        k = 0x10;
    return v / k;
}

/* 0x003B9D80, 0x7C bytes, matching. */
void func_003B9D80(void)
{
    u8 *p = func_003B5E90();
    int k;

    for (k = 0; k < 2; k++)
        func_001ABE40(PS2_LOADP(u8 *, (p + 8)), 0x41, 0, k * 0x170, 0, 0x200, 0x10, 0x80, 2, 0);
}

/* 0x003BA4A0, 0x7C bytes. */
void func_003BA4A0(int k, int on)
{
    u8 *q = func_00329860();
    u32 m;

    if (k >= 8)
        return;
    m = 1 << ((k % 32) & 0x1F);
    if (on == 0)
        *(u32 *)(q + 0x30) &= ~m;
    else
        *(u32 *)(q + 0x30) |= m;
}

/* 0x003BACA0, 0x80 bytes, matching. */
void func_003BACA0(void)
{
    int r = func_00327820();

    if (func_003BAB40(8) == 0 && func_00327C00() != 9 && func_003BA790(r) != 0
        && func_00328230() != 0)
        func_003BA8F0(8, r, -1, -1, -1);
}

/* 0x003BAE30, 0x58 bytes. */
int func_003BAE30(int k)
{
    int t[0x2D], j;

    for (j = 0; j < 0x2D; j++)
        t[j] = g_0041C340[j];
    if (k < 0x2D)
        return t[k];
    return 3;
}

/* 0x003BAE90, 0xAC bytes. Draws the report's banner. */
void func_003BAE90(void)
{
    u8 *p = func_003B5E90();
    int v = 0;

    if (p == 0)
        return;
    if (*(int *)(p + 0x75C) == 6) {
        if (func_003C1850() != 0)
            v = 2;
    } else {
        v = func_003C1850() == 0 ? 1 : 3;
    }
    func_001ABE40(PS2_LOADP(u8 *, (p + 8)), v, 0, 0, 0, 0x200, 0x48, 0x80, 2, 0);
}

/* 0x003BB5F0, 0x64 bytes. The next report page (closing after the fifth). */
void func_003BB5F0(void)
{
    u8 *p = func_003B5E90();

    p[0x763]++;
    if (p[0x763] < 5) {
        func_003BB520(p[0x763]);
    } else {
        func_001B8F60(0, 6, 1);
        *(int *)(p + 4) = 8;
    }
}

/* 0x003BB660, 0x8C bytes. */
int func_003BB660(u32 a, u32 b)
{
    u8 *q = func_00329850();
    u32 *x = (u32 *)(q + (b & 0xFF) * 0x20), *y = (u32 *)(q + (a & 0xFF) * 0x20);

    if (x[0] < y[0])
        return 1;
    if (y[0] == x[0] && (u8)x[1] < (u8)y[1])
        return 1;
    return 0;
}

/* 0x003BBEC0, 0x68 bytes. The next page with something to show (0xFF: none). */
u8 func_003BBEC0(u8 v)
{
    do {
        v++;
        if (v > 4)
            return 0xFF;
    } while (func_003BB8E0(v, 0) < 1);
    return v;
}

/* 0x003BBF30, 0x64 bytes. The previous one. */
u32 func_003BBF30(u32 v)
{
    int k;

    for (k = (int)(v & 0xFF) - 1; k >= 0; k--) {
        if (func_003BB8E0(k & 0xFF, 0) > 0)
            return k & 0xFF;
    }
    return 0xFF;
}

/* 0x003BC660, 0x48 bytes, matching. */
void func_003BC660(void)
{
    u8 *p = func_003B5E90();

    if (*(int *)(p + 0x710) != 0) {
        func_003BAE90();
        func_003BBFD0();
        func_003BBFA0();
        func_001B9000();
    }
}

/* 0x003BD290, 0xC bytes, matching. */
u8 *func_003BD290(void)
{
    return g_007BC1A0;
}

/* 0x003BD3F0, 0x3C bytes, matching. */
void func_003BD3F0(u8 *p)
{
    func_0023AA40();
    if (PS2_LOADP(u8 *, (p + 0x30)) != 0) {
        func_00102EC0(PS2_LOADP(u8 *, (p + 0x30)));
        PS2_STOREP(u8 *, (p + 0x30), 0);
    }
}

/* 0x003BD430, 0x70 bytes, matching. Sets up the Empire screens. */
void func_003BD430(void)
{
    func_003BD2A0(g_007BC1A0);
    func_00395330();
    func_00397830();
    func_0039F330();
    func_003E79B0();
    func_003EEE40();
    func_003B2010();
    func_00397170();
    func_003E4CD0();
    func_002FC2D0();
    func_003E96B0();
}

/* 0x003BD540, 0x40 bytes, matching. */
void func_003BD540(void)
{
    if (*(int *)(func_003BD290() + 0x28) == 0) {
        func_0030DB30(1);
        *(int *)(func_003BD290() + 0x28) = 1;
    }
}

/* 0x003BD580, 0x3C bytes, matching. */
void func_003BD580(void)
{
    if (*(int *)(func_003BD290() + 0x28) != 0) {
        func_0030DC10(1);
        *(int *)(func_003BD290() + 0x28) = 0;
    }
}

/* 0x003BD5C0, 0x40 bytes, matching. */
void func_003BD5C0(void)
{
    if (*(int *)(func_003BD290() + 0x2C) == 0) {
        func_0030DB50();
        *(int *)(func_003BD290() + 0x2C) = 1;
    }
}

/* 0x003BD600, 0x3C bytes, matching. */
void func_003BD600(void)
{
    if (*(int *)(func_003BD290() + 0x2C) != 0) {
        func_0030DC10(1);
        *(int *)(func_003BD290() + 0x2C) = 0;
    }
}

/* 0x003BD640, 0xAC bytes. Draws a pair of arrows. */
void func_003BD640(int x1, int x2, int y, int k)
{
    u8 *t = PS2_LOADP(u8 *, (func_003BD290() + 0x30));

    func_001ABE40(t, k, x1, y, 0, 0x10, 0x10, 0x80, 2, 0);
    func_001ABE40(t, k + 2, x2, y, 0, 0x10, 0x10, 0x80, 2, 0);
}

/* 0x003BD6F0, 0x20 bytes, matching. */
u8 *func_003BD6F0(void)
{
    return (u8 *)((u8 *)func_00390940()) + 0x2C04;
}

/* 0x003BD870, 0x20 bytes, matching. */
u8 *func_003BD870(void)
{
    return (u8 *)((u8 *)func_00390940()) + 0x2C34;
}

/* More of the turn report: message pickers by the force's state, the score, the report pages'
 * player (entries of 8 bytes from +0x2C: officer, picture, portrait; state +0x73C, line +0x762,
 * fade +0x764, timer +0x748), parts of 0x003B8440-0x003BA8B4. */

extern u8 g_00500764, g_00500765;
extern u16 g_0050074E;
extern char g_0069395E;
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;
extern u8 g_0056CCC8[4];

#define PAD1_REPEAT() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074E)

void func_003B8E00(void);
int func_0032D180();
char *func_003B9770(void);
void func_002C7310(int x, int y, int a, int w, int h, int b, int c);

/* 0x003B8440, 0xF0 bytes. */
int func_003B8440(void)
{
    int g = func_002FABC0(func_00327D50());

    switch (func_003B7EB0()) {
    case 0x16:
        return g == 1000 ? 0x69 : 0x6A;
    case 0x17:
        return 0x66;
    case 0x18:
        return 0x67;
    case 0x19:
    case 0x1A:
    case 0x1B:
        return 0x68;
    default: {
        u32 r = RAND16() % 3;

        if (r == 1)
            return 0x6C;
        if (r == 0)
            return 0x6B;
        return 0x6D;
    }
    }
}

/* 0x003B85C0, 0xF0 bytes. */
int func_003B85C0(void)
{
    int g = func_002FABC0(func_00327D50());

    switch (func_003B7EB0()) {
    case 0x16:
        return g == 1000 ? 0x80 : 0x7E;
    case 0x17:
        return 0x7C;
    case 0x18:
        return 0x7D;
    case 0x19:
    case 0x1A:
    case 0x1B:
        return 0x7E;
    default: {
        u32 r = RAND16() % 3;

        if (r == 1)
            return 0x81;
        if (r == 0)
            return 0x7F;
        return 0x82;
    }
    }
}

/* 0x003B86B0, 0x104 bytes. */
int func_003B86B0(void)
{
    int g = func_002FABC0(func_00327D50());

    switch (func_003B7EB0()) {
    case 0x16:
        return g == 1000 ? 0x8B : 0x8C;
    case 0x17:
        return 0x88;
    case 0x18:
        return 0x89;
    case 0x19:
    case 0x1A:
    case 0x1B:
        return 0x8A;
    default:
        if (func_0032EB40(func_00327820(), func_00337A10(7), 1) != 0)
            return 0x8D;
        return (RAND16() & 1) == 0 ? 0x8F : 0x8E;
    }
}

/* 0x003B8A70, 0x25C bytes. The turn's score. */
int func_003B8A70(void)
{
    int a = 0, b = 0, c = 0, d = 0, k, n, m, div, base;
    u8 *p = func_003B5E90();
    int single = *(int *)(p + 0x744) != 2;

    for (k = 0; k < 0x19; k++) {
        if (k >= 0 && k < func_0030AB90()) {
            a += func_0030AD80(k);
            b += func_0030AE80(k);
            c += func_0030B090(k);
            d += func_0030ACE0(k);
        }
    }
    n = func_003B8900(func_00327D50(), 7);
    m = func_002FB100(func_00327D50());
    div = single ? 1 : 2;
    switch (g_00669D60[0x21]) {
    case 4:
    case 3:
        base = single ? 100 : 0x50;
        break;
    case 2:
        base = single ? 0x5A : 0x48;
        break;
    case 1:
    case 0:
        base = single ? 0x50 : 0x40;
        break;
    default:
        base = 0x40;
        break;
    }
    return p[0x765] + base + (m * 10 + n / 2 + a * 100 / b + c * 100 / d) / div;
}

/* 0x003B9630, 0x124 bytes. Starts the report pages. */
void func_003B9630(void)
{
    u8 *p = func_003B5E90();
    int k;

    func_003A5FA0(0, 0, 0, 0);
    p[0x762] = 0;
    *(int *)(p + 0x748) = 0;
    p[0x764] = 0;
    *(int *)(p + 0x73C) = 1;
    for (k = 0; k < 0x9D; k++) {
        *(int *)(p + 0x2C + k * 8) = -1;
        p[0x30 + k * 8] = 0xFF;
        p[0x31 + k * 8] = 0xFF;
    }
    func_003B8E00();
    func_001B8F60(1, 6, 1);
}

/* 0x003B9E00, 0xD0 bytes. Draws the line's picture. */
void func_003B9E00(void)
{
    u8 *p = func_003B5E90();
    u8 l = p[0x762], *e = p + l * 8;
    u32 v = e[0x31];
    u8 a = p[0x764];
    int s;

    if (v == 0xFF)
        return;
    s = *(int *)(p + 0x73C);
    if (s == 2 || s == 3) {
        if (l < 0x9C && v == p[l * 8 + 0x39])
            a = 0x80;
    } else if (s == 1 && l != 0 && v == e[0x29]) {
        a = 0x80;
    }
    func_001ABE40(PS2_LOADP(u8 *, (p + 8)), v + 5, 0x118, 0xE0, 0, 0xD8, 0x90, a, 0, 0);
}

/* 0x003B9ED0, 0xFC bytes. Draws the line's officer portrait. */
void func_003B9ED0(void)
{
    u8 *p = func_003B5E90();
    u8 l = p[0x762], *e = p + l * 8;
    int s = *(int *)(p + 0x73C), o = *(int *)(e + 0x2C), k;
    u8 a = p[0x764];

    if (s == 2 || s == 3) {
        if (l < 0x9C && o == *(int *)(p + l * 8 + 0x34))
            a = 0x80;
    } else if (s == 1 && l != 0 && o == *(int *)(e + 0x24)) {
        a = 0x80;
    }
    if (o != -1) {
        k = func_0032D180();
        if (k < 0x32)
            func_001ABE40(func_003D3960(), k << 2, 0x20, 8, 0, 0xA0, 0xA0, a, 0, 0);
    }
}

/* 0x003B9FD0, 0x188 bytes. Draws the line's text box. */
void func_003B9FD0(void)
{
    u8 *p = func_003B5E90();
    u8 l = p[0x762], *e = p + l * 8;
    u8 a = p[0x764];
    int s;
    char *t;

    if ((signed char)e[0x30] == -1)
        return;
    s = *(int *)(p + 0x73C);
    if (s == 2 || s == 3) {
        if (l < 0x9C && *(int *)(e + 0x2C) == *(int *)(p + l * 8 + 0x34))
            a = 0x80;
    } else if (s == 1 && l != 0 && *(int *)(e + 0x2C) == *(int *)(e + 0x24)) {
        a = 0x80;
    }
    t = func_003B9770();
    func_002C7310(0x18, 0x9A, 0, 0x1D0, 0x46, a, 0);
    g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = 6;
    g_0056CCC0 = g_0056CCC4 = 16.0f;
    func_00146270((const unsigned char *)(t), 0x28, 0xA2, 1, 0);
    g_0056CCC0 = g_0056CCC4 = 16.0f;
    g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = 5;
    g_0056CCC8[0] = g_0056CCC8[1] = g_0056CCC8[2] = g_0056CCC8[3] = a;
}

/* 0x003BA1A0, 0x164 bytes. Steps the report pages (1 fade in, 0 shown, 2 fade out, 3 next,
 * 4 over). */
void func_003BA1A0(void)
{
    u8 *p = func_003B5E90();
    int s = *(int *)(p + 0x73C);

    if (s == 3) {
        p[0x762]++;
        *(int *)(p + 0x748) = 0;
        *(int *)(p + 0x73C) = 1;
        if ((signed char)p[p[0x762] * 8 + 0x30] == -1 || p[0x762] > 0x9C) {
            *(int *)(p + 0x73C) = 4;
            func_001B8F60(0, 6, 1);
            func_0017DEA0(0x78);
        }
    } else if (s == 2) {
        p[0x764] -= 2;
        if (p[0x764] > 0x7F)
            p[0x764] = 0;
        if (p[0x764] == 0)
            *(int *)(p + 0x73C) = 3;
    } else if (s == 4) {
        if (g_0069395E == 0 || g_0069395E == -1)
            *(int *)(p + 4) = 10;
    } else if (s == 1) {
        p[0x764] += 2;
        if (p[0x764] > 0x7F)
            *(int *)(p + 0x73C) = 0;
    } else if (s == 0) {
        p[0x764] = 0x80;
    }
}

/* 0x003BA310, 0x184 bytes. The report pages' frame (a line lasts 420 frames). */
int func_003BA310(void)
{
    u8 *p = func_003B5E90();

    if (*(int *)(p + 0x714) == 0) {
        func_003B9630();
        *(int *)(p + 0x714) = 1;
    }
    func_003BA1A0();
    if (*(int *)(p + 0x73C) != 3) {
        if ((PAD1_REPEAT() & 0x40) != 0 || *(int *)(p + 0x748) > 0x1A3) {
            if (*(int *)(p + 0x748) < 0x1A4)
                *(int *)(p + 0x748) = 0x1A4;
            *(int *)(p + 0x73C) = 2;
        }
        if ((PAD1_REPEAT() & 0x800) != 0) {
            *(int *)(p + 0x748) = 0x1A4;
            *(int *)(p + 0x73C) = 4;
            p[p[0x762] * 8 + 0x38] = 0xFF;
            func_001B8F60(0, 6, 1);
            func_0017DEA0(0x78);
        }
    }
    *(int *)(p + 0x748) += 1;
    return 0;
}

/* 0x003BA700, 0x90 bytes, matching. Copies force record `a` to `b`. */
void func_003BA700(int a, int b)
{
    u8 *q = func_00329850();
    u32 *s = (u32 *)(q + a * 0x20), *d = (u32 *)(q + b * 0x20);

    d[0] = s[0];
    ((u8 *)d)[4] = ((u8 *)s)[4];
    ((u8 *)d)[5] = ((u8 *)s)[5];
    ((u8 *)d)[6] = ((u8 *)s)[6];
    ((u8 *)d)[7] = ((u8 *)s)[7];
    d[2] = s[2];
    d[4] = s[4];
    d[5] = s[5];
    d[6] = s[6];
    d[7] = s[7];
}

/* 0x003BA7F0, 0xC4 bytes. */
int func_003BA7F0(int k)
{
    switch (k) {
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
        return 4;
    default:
        if (func_003C1850() == 0) {
            if (func_00329540(0x14) == 0)
                return 0;
            if (func_00329540(0x15) == 0)
                return 1;
            if (func_00329540(0x16) == 0)
                return 2;
            return 3;
        }
        return func_00329540(0x16D) == 0 ? 0 : 1;
    }
}

/* The turn's records (0x20 bytes each from func_00329850, five map snapshots of 0x18 bytes from
 * +0x5A0: turn, season, officer, 2 bits per province), their pages and portraits (parts of
 * 0x003BA8F0-0x003BC88C). */

extern char g_007BC080[];
extern char g_0045BA88[], g_0045BA90[];
extern u8 g_007B4E60[], g_007B4E6A[];
extern char g_0045BB50[];
extern int g_0045D800, g_0045D804;       /* (small data) */

int func_003BAB40(int k);
int func_001204B0(char *buf, const char *fmt, ...);
void func_0011EB80(void *to, const void *from, int n);
void func_00120928(char *to, const char *from);
u32 func_00120A40(const char *s);
void func_003BC150(void);

/* 0x003BA8F0, 0x24C bytes. Records event `k` of this turn (kinds 0xD and 4-7 take the next free
 * one; the others only once). */
void func_003BA8F0(int k, int a, int b, int c, int d)
{
    u8 *q = func_00329850(), *r;
    u32 t = func_00327C80();
    int s = func_00327CC0(), o = func_00327820(), w = func_00328230(), i;
    u8 f = func_002F5CC0(o), m = func_003BA7F0(k);

    if (k == 0xE || k == 0xD) {
        if (func_003BAB40(0xD) != 0)
            k = 0xE;
    } else if (k == 7 || k == 6 || k == 5 || k == 4) {
        k = 0x2D;
        for (i = 0; i < 4; i++) {
            if (func_003BAB40(i + 4) == 0) {
                k = i + 4;
                break;
            }
        }
        if (k == 0x2D) {
            func_003BA700(7, 6);
            k = 7;
        }
    } else if ((k == 0x21 || k == 0x1F || k == 0x1E || k == 0x18 || k == 0x17 || k == 0x16
                || k == 0x15 || k == 0x14 || k == 0x13 || k == 3 || k == 1 || k == 0)
               && func_003BAB40(k) != 0) {
        return;
    }
    r = q + k * 0x20;
    *(u32 *)r = t;
    r[4] = s;
    r[5] = m;
    r[6] = f;
    *(int *)(r + 8) = o;
    r[7] = w != 0;
    *(int *)(r + 0x10) = a;
    *(int *)(r + 0x14) = b;
    *(int *)(r + 0x18) = c;
    *(int *)(r + 0x1C) = d;
}

/* 0x003BAB70, 0x130 bytes. Takes map snapshot `k` (owned, allied). */
void func_003BAB70(int k)
{
    u8 *q = func_00329850(), *r;
    int v = func_00327140(func_00327C00(), func_00327C70() + 1);
    int s = func_00327CC0(), o = func_00327820(), f = func_00327D50(), p;

    r = q + k * 0x18 + 0x5A0;
    *(int *)r = v;
    r[4] = s;
    *(int *)(r + 8) = o;
    for (p = 0; p < func_0030AB90(); p++) {
        u64 b = func_0030C250(p) != 0;

        if (func_002F9C90(f, func_0030AFF0(p)) == 3)
            b = 2;
        *(u64 *)(q + k * 0x18 + 0x5B0) |= b << (p * 2);
    }
}

/* 0x003BAD20, 0x104 bytes, matching. Records the turn's battle (won 0x1E or lost 0x1F). */
void func_003BAD20(void)
{
    u32 v = func_00362370();

    if ((v < 0x19 || func_00362370() > 0x1D) && func_00362370() != 0x46) {
        if (func_003BAB40(0x1E) == 0 && func_0036B260() != 0
            && func_0035D5B0(func_00362570()) == 0)
            func_003BA8F0(0x1E, func_0030D150(), 1, -1, -1);
        if (func_003BAB40(0x1F) == 0 && func_0036B260() != 0
            && func_0035D5B0(func_00362570()) == 1)
            func_003BA8F0(0x1F, func_0030D150(), -1, -1, -1);
    }
}

/* 0x003BAF40, 0x118 bytes. Officer `o`'s name for the report (some with a title). */
char *func_003BAF40(u32 o, int k)
{
    int c = func_002F27D0(o);

    if (o >= 0x19F)
        return g_0045BA88;
    if (c == 0xAF || c == 0xAE || c == 0xAB || c == 0xF) {
        func_001204B0(g_007BC080, g_0045BA90, func_002F2BB0(o), func_0019B0C0(k == 0 ? 0x18 : 0x17));
        return g_007BC080;
    }
    return func_002F2890(o);
}

/* 0x003BB520, 0xCC bytes. Shows map snapshot `k`. */
void func_003BB520(int k)
{
    int n = func_0030AB90(), p;
    u8 *q = func_00329850();

    func_002F4080(func_00327820());
    func_003A7C10();
    for (p = 0; p < n; p++)
        func_003A9A30(p, (*(u64 *)(q + k * 0x18 + 0x5B0) >> (p * 2) & 3) != 0);
}

/* 0x003BB6F0, 0xBC bytes. Splits a report line into its 5-byte head and its text; the box's
 * height. */
int func_003BB6F0(char *s, u8 **a, u8 **b)
{
    u8 tmp[4];
    int h = 0;

    func_0011EB80(g_007B4E60, s, 5);
    g_007B4E60[5] = 0;
    func_00120928((char *)g_007B4E6A, g_0045BA88);
    if (func_00120A40(s) > 6)
        func_00147160((const unsigned char *)(s + 6), g_007B4E6A, 0x160, (int *)(tmp), &h);
    *a = g_007B4E60;
    *b = g_007B4E6A;
    return h + 0x10;
}

/* 0x003BB7B0, 0x12C bytes. A box of height `h` (top, middle, bottom). */
void func_003BB7B0(int x, int y, int h, int alpha)
{
    u8 *p = func_003B5E90();

    func_001ABEA0(PS2_LOADP(u8 *, (p + 8)), 4, x, y, 0, 0x1C0, 8, 0, 0, 0x1c0, 8, alpha & 0xFF, 2, 0);
    func_001ABEA0(PS2_LOADP(u8 *, (p + 8)), 4, x, y + 8, 0, 0x1C0, h - 0x10, 0, 8, 0x1c0, 0x10, alpha & 0xFF, 2, 0);
    func_001ABEA0(PS2_LOADP(u8 *, (p + 8)), 4, x, y + 8 + h - 0x10, 0, 0x1C0, 8, 0, 0x18, 0x1c0, 8, alpha & 0xFF, 2, 0);
}

/* 0x003BBFD0, 0x17C bytes. Draws the page's officer portrait. */
void func_003BBFD0(void)
{
    u8 *q = func_00329850(), *p = func_003B5E90(), *t;
    int *r, s;
    u8 l, a;
    u32 v;

    if (p == 0)
        return;
    l = p[0x763];
    t = PS2_LOADP(u8 *, (p + l * 4 + 0xC));
    if (t == 0)
        return;
    r = (int *)(q + l * 0x18 + 0x5A8);
    func_0032D180(func_002F27D0(*r));
    s = *(int *)(p + 0x73C);
    a = p[0x764];
    if (s == 1) {
        if (l != 0) {
            v = func_003BBF30(l);
            if ((v & 0xFF) != 0xFF && *r == *(int *)(q + (v & 0xFF) * 0x18 + 0x5A8))
                a = 0x80;
        }
    } else if (s == 2 || s == 3) {
        v = func_003BBEC0(l);
        if ((v & 0xFF) != 0xFF && *r == *(int *)(q + (v & 0xFF) * 0x18 + 0x5A8))
            a = 0x80;
    }
    func_001ABA70(t, 0x28, 0x30, 0, 0xC0, 0xC0, a, 0, 0);
}

/* 0x003BC450, 0x188 bytes. Opens the report. */
void func_003BC450(void)
{
    u8 *p = func_003B5E90(), *q = func_00329850();
    u32 k;

    g_0045D800 = 0;
    g_0045D804 = 0;
    p[0x763] = 0;
    *(int *)(p + 0x748) = 0;
    *(int *)(p + 0x74C) = 0;
    PS2_STOREP(u8 *, (p + 8), func_001026D0(1, 0xD83, 0, 1, 0, 0, g_0045BB50, 0x432));
    for (k = 1; k < 5; k++) {
        u8 *r = q + k * 0x18;

        if (*(u64 *)(r + 0x5B0) == 0)
            *(u64 *)(r + 0x5B0) = *(u64 *)(r + 0x598);
    }
    func_003A7C10();
    func_003A5FA0(1, 1, 0, 1);
    func_003A9010(0);
    func_003A9170();
    func_003A93A0(1);
    func_003A9AF0(0);
    func_003BC150();
    func_003BB520(p[0x763]);
    for (k = 0; k < 5; k++) {
        *(int *)(p + k * 4 + 0xC) = 0;
        func_003BB8E0(k, 1);
    }
    func_00102960(1);
    func_001B8F60(1, 6, 1);
    if (*(int *)(p + 0x75C) == 6 && func_003C1850() == 0)
        func_0017E010(0x2F);
    else
        func_0017E010(0x31);
}

/* 0x003BC5E0, 0x7C bytes. Closes it. */
void func_003BC5E0(void)
{
    u8 *p = func_003B5E90();
    int k;

    if (PS2_LOADP(u8 *, (p + 8)) != 0) {
        func_00102EC0(PS2_LOADP(u8 *, (p + 8)));
        PS2_STOREP(u8 *, (p + 8), 0);
    }
    for (k = 0; k < 5; k++) {
        if (PS2_LOADP(u8 *, (p + 0xC + k * 4)) != 0) {
            func_00102EC0(PS2_LOADP(u8 *, (p + 0xC + k * 4)));
            PS2_STOREP(u8 *, (p + 0xC + k * 4), 0);
        }
    }
    func_003A93A0(0);
    func_003A9AF0(1);
}

/* 0x003BC760, 0x12C bytes. Steps the report's pages. */
void func_003BC760(void)
{
    u8 *p = func_003B5E90();
    int s = *(int *)(p + 0x73C), v;

    if (s == 3) {
        do {
            func_003BB5F0();
            v = func_003BB8E0(p[0x763], 0);
            if (v > 0 || p[0x763] > 4)
                break;
        } while (v == 0);
        *(int *)(p + 0x748) = 0;
        *(int *)(p + 0x73C) = 1;
    } else if (s == 4) {
        p[0x764] = 0x80;
    } else if (s == 2) {
        p[0x764] -= 2;
        if (p[0x764] > 0x7F)
            p[0x764] = 0;
        if (p[0x764] == 0 && *(int *)(p + 0x73C) == 2)
            *(int *)(p + 0x73C) = 3;
    } else if (s == 1) {
        p[0x764] += 2;
        if (p[0x764] > 0x7F)
            *(int *)(p + 0x73C) = 0;
    } else if (s == 0) {
        p[0x764] = 0x80;
    }
}

/* The report's frame, the Empire screens' state and their glue, an idle timer and two buffers
 * (parts of 0x003BC890-0x003BF9DC). */

typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

typedef struct { int x, y, w, h, a; } Box5;

extern char g_0045BC08[];
extern int g_007BC2A0, g_007BC2A4, g_007BC2A8, g_007BC2AC;
extern u8 g_007BC1E0[0xC][0x10];
extern u8 g_007BC2B0[2][0x1410];
extern int g_0045D810, g_0045D0C8, g_0045D808;   /* (small data) */

void func_0039F580(void);
void func_003B2170(void);
void func_003BF5F0(float dt, int k);
int func_003BF8F0(void);

/* 0x003BC890, 0x1EC bytes. The report's frame (pages last 210 frames more each, or until a
 * button). */
int func_003BC890(void)
{
    u8 *p = func_003B5E90();
    int l = *(int *)(p + 0x74C), min = l * 0x78 + 0x3C, extra = g_0045D804 == 0 ? 0 : 0xB4;

    if (*(int *)(p + 0x710) == 0) {
        func_003BC450();
        *(int *)(p + 0x710) = 1;
    }
    func_003BC760();
    if (*(int *)(p + 0x73C) != 3) {
        if (extra + l * 0x96 + 0xD2 <= *(int *)(p + 0x748))
            *(int *)(p + 0x73C) = 2;
        if ((PAD1_REPEAT() & 0x40) != 0) {
            if (min < *(int *)(p + 0x748))
                *(int *)(p + 0x73C) = 2;
            else
                *(int *)(p + 0x748) = min;
        }
        if ((PAD1_REPEAT() & 0x800) != 0) {
            p[0x763] = 5;
            func_003BB5F0();
            *(int *)(p + 0x73C) = 4;
        }
    }
    if (g_0069395E == 0 || g_0069395E == -1)
        *(int *)(p + 0x748) += 1;
    return 0;
}

/* 0x003BD2A0, 0x14C bytes. Sets up the Empire screens' state (which menus have content). */
void func_003BD2A0(u8 *b)
{
    int *p = (int *)b, k;

    func_00118850((unsigned char *)(p), 0x34);
    p[10] = 0;
    p[11] = 0;
    p[12] = (int)PS2_ADDR(func_001026D0(1, 0x85, 0, 1, 0, 0, g_0045BC08, 0x28));
    for (k = 0; k < 10; k++)
        p[k] = 1;
    p[6] = 0;
    for (k = 0; k < 4; k++) {
        if (func_003A1FC0(k) != 4) {
            p[6] = 1;
            break;
        }
    }
    p[7] = 0;
    for (k = 0; k < 0x3A; k++) {
        if (func_003A01A0(k) != 0) {
            p[7] = 1;
            break;
        }
    }
    p[8] = 0;
    for (k = 0x3B; k < 0x59; k++) {
        if (func_003A01A0(k) != 0)
            p[8] = 1;
    }
}

/* 0x003BD4A0, 0x98 bytes. Closes the Empire screens. */
void func_003BD4A0(void)
{
    func_003BD3F0(g_007BC1A0);
    func_00395420();
    func_003978F0();
    func_0039F580();
    func_003E7C00();
    func_003EEF50();
    func_003B2170();
    func_00397230();
    func_003E4D80();
    if (func_003E9730() != 0) {
        if (func_003E96E0() == 0)
            func_003E9630();
        else
            func_003E9690();
    }
}

/* 0x003BD710, 0x84 bytes, matching. The banner window comes in. */
void func_003BD710(void)
{
    u8 *p = func_003BD6F0();
    WindowAnim *w = (WindowAnim *)(p + 0xC);

    p[0x20] = 0;
    w->x0 = 0x100; w->y0 = 0xC0; w->w0 = 0; w->h0 = 0;
    w->x1 = 0x100; w->y1 = 0xC0; w->w1 = 0; w->h1 = 0;
    w->frames = 0; w->timer = 0;
    w->alpha0 = 0; w->alpha1 = 0;
    w->x1 = 0; w->y1 = 0x8A; w->w1 = 0x200; w->h1 = 0x6C;
    w->alpha1 = 0x80;
    w->frames = 10;
}

/* 0x003BD890, 0x6C bytes. (Every case empty.) */
void func_003BD890(int k)
{
    switch (k) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    }
}

/* 0x003BD900, 0x34 bytes, matching. Whether boxes 0x13 or 0x14 are moving. */
int func_003BD900(void)
{
    return func_003DC2D0(0x13) != 0 || func_003DC2D0(0x14) != 0;
}

/* 0x003BE6B0, 0x9C bytes, matching. */
void func_003BE6B0(void)
{
    Box5 b;

    b.x = 8; b.y = 0x67; b.w = 0xB8; b.h = 0x12; b.a = 0x80;
    func_003DC090(0x13, &b);
    func_003DC0E0(0x13, 1, 0xB);
    b.x = 0xF0; b.y = 0x34; b.w = 0x108; b.h = 0x38; b.a = 0x80;
    func_003DC090(0x14, &b);
    func_003DC0E0(0x14, 2, 1);
}

/* 0x003BF6F0, 0xE4 bytes. An idle timer: on (g_007BC2AC) for a random while every 5-10
 * seconds. */
void func_003BF6F0(void)
{
    g_007BC2A0++;
    if (g_007BC2A0 < g_007BC2A4) {
        g_007BC2AC = 0;
    } else if (g_007BC2A8 < g_007BC2A0) {
        g_007BC2A8 = g_007BC2A4 + 200 + RAND16() % 200;
        g_007BC2A0 = 0;
        g_007BC2AC = 0;
        g_007BC2A4 = RAND16() % 0xFA + 0xFA;
    } else {
        g_007BC2AC = 1;
    }
}

/* 0x003BF7E0, 0x3C bytes. */
void func_003BF7E0(void)
{
    int k;

    for (k = 0; k < 0xC; k++)
        g_007BC1E0[k][0xC] = 0;
}

/* 0x003BF820, 0x90 bytes. Drops the entries not kept this frame, then steps. */
void func_003BF820(void)
{
    int k;

    for (k = 0; k < 0xC; k++) {
        u32 *e = (u32 *)g_007BC1E0[k];

        if (e[1] != 0 && g_007BC1E0[k][0xC] == 0) {
            e[0] = 0;
            e[1] = 0;
            e[2] = 0;
        }
    }
    for (k = 0; k < 2; k++)
        func_003BF5F0(1.0f / 60.0f, k);
    func_003BF6F0();
}

/* 0x003BF8B0, 0x40 bytes. The next of two buffers. */
u8 *func_003BF8B0(void)
{
    int v = g_0045D810;

    g_0045D810++;
    if (g_0045D810 > 1)
        g_0045D810 = 0;
    return g_007BC2B0[v];
}

/* 0x003BF990, 0x24 bytes, matching. */
void func_003BF990(void)
{
    g_0045D0C8 = func_003BF8F0();
    g_0045D808 = 0;
}

/* 0x003BF9C0, 0xC bytes, matching. */
void func_003BF9C0(void)
{
    g_0045D0C8 = 0xC;
}

/* 0x003BF9D0, 0x10 bytes, matching. */
int func_003BF9D0(void)
{
    return g_0045D0C8 != 0xC;
}
