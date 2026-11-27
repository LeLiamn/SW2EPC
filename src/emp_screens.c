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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_0045D7EC[2];                 /* (small data) the players' tactic bits */
extern int g_0045D7F0, g_0045D7F4;       /* (small data) */
extern u8 *g_0045D7FC;                   /* (small data) the screen textures */
extern char g_0045B6D8[];                /* the allocations' source name */
extern int (*g_0045B580[0x1D])(void), (*g_0045B620[0x1E])(void);
extern u16 g_0045B600[][2], g_0045B610[][2];
extern int g_0045BBD0[0xC];
extern u8 g_007BAF10[], g_007BB510[];
extern int g_007BAF1C;
extern float g_007BAEF8, g_007BAED8;
extern u8 g_007BAEFD, g_007BAEDD;

#define TEX g_0045D7FC

int func_0039B980(void);
int func_003A9480(int v);
void func_003AE8E0(int k);
void func_00118850(void *p, int n);
u8 func_0035D5A0(u32 s);
int func_0036F5C0(int s);
int func_0036F5E0(int s);
int func_0034A790(u8 *o);
int func_0032BC30(void);
void func_0032D150(void);
void func_002F2970(int k);
void func_00372740(int k);
void func_002ED190(int k);
void func_0032BB70(void);
void func_0032E830(void);
void func_003B1490(u8 *p, int v);
void func_003B0A40(void);
void func_0032F530(void);
void func_0032F640(void);
int func_00102960(int a);
void func_0032B990(void);
void func_001037F0(void);
void func_003B1320(void);
void func_003B0E40(void);
void func_003B1A90(void);
void func_003B14E0(void);
u8 *func_00390940(void);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, char *name, int line);
void func_00102EC0(u8 *p);
void func_003B39A0(void);
void func_003B4740(void);
void func_003B4A40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_001ABEA0(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_003B5B30(void);
void func_003B5D50(void);
void func_003B9D80(void);
void func_003B9E00(void);
void func_003B9ED0(void);
void func_003B9FD0(void);
int func_002F27D0(int o);
u8 *func_00329850(void);
void func_003BB8E0(u8 k, int a);

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

/* 0x003AFD40, 0x28 bytes. */
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
int func_003B0470(u32 k)
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
void func_003B0BD0(int k)
{
    if (k < 0x1C)
        func_002F2970(k);
    else
        func_00372740(k);
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

/* 0x003B2200, 0x44 bytes. */
void func_003B2200(void)
{
    if (g_0045D7F0 == 0 && func_00102960(0) != 0) {
        func_0032B990();
        g_0045D7F0 = 1;
        func_001037F0();
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
int func_003B22C0(void)
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
    TEX = func_001026D0(1, 0x89, 0, 1, 0, 0, g_0045B6D8, 0x159);
    func_00102960(1);
}

/* 0x003B3940, 0x2C bytes, matching. */
void func_003B3940(void)
{
    if (TEX != 0) {
        func_00102EC0(TEX);
        TEX = 0;
    }
}

/* 0x003B3970, 0x24 bytes. */
void func_003B3970(void)
{
    func_003B39A0();
}

/* 0x003B4720, 0x20 bytes. */
void func_003B4720(void)
{
    func_003B4740();
}

/* 0x003B4DE0, 0x68 bytes. */
void func_003B4DE0(int x, int y, int a)
{
    func_003B4A40(TEX, 10, x, y, a, 0x78, 0x18, 0);
}

/* 0x003B4E50, 0x68 bytes. */
void func_003B4E50(int x, int y, int a)
{
    func_003B4A40(TEX, 0xC, x, y, a, 0x80, 0x20, 0);
}

/* 0x003B51E0, 0x58 bytes. */
void func_003B51E0(int x, int y, int a)
{
    func_001ABEA0(TEX, 0x15, x, y, a, 0x14, 0x14, 0);
}

/* 0x003B5240, 0x58 bytes. */
void func_003B5240(int x, int y, int a)
{
    func_001ABEA0(TEX, 0x16, x, y, a, 0x18, 0x14, 0);
}

/* 0x003B52A0, 0x58 bytes. */
void func_003B52A0(int x, int y, int a)
{
    func_001ABEA0(TEX, 0x1B, x, y, a, 0x18, 0x14, 0);
}

/* 0x003B5410, 0x64 bytes. */
void func_003B5410(int x, int y, int a)
{
    func_001ABEA0(TEX, 0x23, x, y, a, 0x60, 0x18, 0);
}

/* 0x003B55A0, 0x40 bytes. */
void func_003B55A0(int x, int y, int a)
{
    func_001ABE40(TEX, 0x25, x, y, a, 0x30, 0x10, 0x80);
}

/* 0x003B55E0, 0x40 bytes. */
void func_003B55E0(int x, int y, int a)
{
    func_001ABE40(TEX, 0x26, x, y, a, 0x40, 0xF, 0x80);
}

/* 0x003B5620, 0x40 bytes. */
void func_003B5620(int x, int y, int a)
{
    func_001ABE40(TEX, 0x27, x, y, a, 0x30, 0x10, 0x80);
}

/* 0x003B5750, 0x60 bytes. */
void func_003B5750(int k, int x, int y, int a)
{
    func_001ABEA0(TEX, 0x2D, x, y, a, 0x40, 0x10, 0);
}

/* 0x003B57B0, 0x6C bytes. */
void func_003B57B0(int k, int x, int y, int a)
{
    func_001ABEA0(TEX, 0x2E, x, y, a, 0x48, 0x14, 0);
}

/* 0x003B58A0, 0x40 bytes. */
void func_003B58A0(int x, int y, int a, int b)
{
    func_001ABE40(TEX, 0x46, x, y, a, 0x78, 0x10, b);
}

/* 0x003B58E0, 0x44 bytes. */
void func_003B58E0(int x, int y, int a, int w, int h)
{
    func_001ABE40(TEX, 0x48, x, y, a, w, h, 0x80);
}

/* 0x003B5930, 0x40 bytes. */
void func_003B5930(int x, int y, int a)
{
    func_001ABE40(TEX, 0x47, x, y, a, -1, -1, 0x80);
}

/* 0x003B5CA0, 0x1C bytes. */
void func_003B5CA0(void)
{
    func_003B5B30();
}

/* 0x003B5DF0, 0x1C bytes. */
void func_003B5DF0(void)
{
    func_003B5D50();
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
