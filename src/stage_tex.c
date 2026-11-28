/*
 * stage_tex.c - battle stage pieces between 0x001F44E0 and 0x001F556C: the stage's texture
 * sets (a file of TIM2 pairs per scenario, scratchpad 0x70000760 table of GS packets, lord
 * colour variants), the stage's frame set-up and the gate objects (0x70-byte stage objects
 * from scratchpad 0x700001D0, kind +0x68, owner +0x6B: 0x8F open, 0x90 shut). Original file
 * name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_STAGE_TEX_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define SPAD(off) ((u8 *)0x70000000 + (off))
#define SP32(off) (*(u32 *)SPAD(off))
#define SPP(off)  (*(u8 **)SPAD(off))
#define SP_PKT    (*(u32 **)SPAD(0x158))
#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))

extern u8 g_00669D60[];
extern u8 *g_0045D2C0;                   /* (small data) the camera */
extern u8 *g_00732210;                   /* the stage's texture file */
extern u32 g_00732214, g_00732218, g_0073221C;   /* GS memory cursors */
extern u8 *g_005BA694;                   /* the scenario table's entries (100 bytes each) */
extern u8 g_004298E8[];
extern float g_0045D468[];               /* (small data) */

void func_001F4280(u8 *pos, u8 *cam);
char func_001FF100(short a, int b);
void func_001FD9A0(int a, int b);
void func_001FD5F0(int a);
void func_001FD7C0(void);
void func_001FD8F0(void);
void func_001FEE00(int a);
void func_002477B0(void);
void func_001FBED0(void);
void func_001FDB70(void);
void func_00247530(u8 *o, u8 *pos, u8 *u, int k);

/* 0x001F44E0, 0xA0 bytes. Moves the view's focus to player 1 (or 2), and to the duel. */
void func_001F44E0(int k)
{
    u8 *u, *b;

    if ((GAME_FLAGS & 0x100000) != 0 || k == 4)
        return;
    u = (u8 *)PS2_PTR(func_001F2AF0());
    if (u == 0) {
        b = k == 3 ? (u8 *)0x575410 : (u8 *)0x574DE0;
    } else {
        func_001F4280(u + 0x90, g_0045D2C0 + 0x1C0);
        b = (u8 *)0x574DE0;
    }
    func_001F4280(b + 0x90, g_0045D2C0 + 0x1C0);
}

/* 0x001F48A0, 0xA0 bytes. A GS packet setting TEX0 and CLAMP (`v`: TEX0, CLAMP). */
void func_001F48A0(u64 *v)
{
    u32 *p = SP_PKT;

    p[0] = 0x10000003;
    p[1] = 0;
    p[2] = 0x11000000;
    p[3] = 0x50000003;
    *(u64 *)(p + 4) = 0x1000000000008002ULL;
    *(u64 *)(p + 6) = 0xE;
    *(u64 *)(p + 8) = v[1];
    *(u64 *)(p + 10) = 0x14;
    *(u64 *)(p + 12) = v[0];
    *(u64 *)(p + 14) = 6;
    SP_PKT = p + 16;
}

/* 0x001F4940, 0x54 bytes. Frees the stage's texture set. */
void func_001F4940(void)
{
    if (SPP(0x760) != 0) {
        func_00102EC0(SPP(0x760));
        SPP(0x760) = 0;
    }
    if (g_00732210 != 0) {
        func_00102EC0(g_00732210);
        g_00732210 = 0;
    }
}

/* 0x001F4B10, 0x74 bytes. Starts a texture set of `n` entries (file `f`). */
void func_001F4B10(u8 *f, int n)
{
    g_00732214 = 0x1920;
    g_0073221C = 0x3DD0;
    g_00732218 = 0x3ECC;
    SP32(0x768) = 0;
    if (n != 0) {
        SP32(0x764) = n;
        g_00732210 = f;
        SPP(0x760) = func_00102D30(SP32(0x764) << 4);
        func_00118850(SPP(0x760), SP32(0x764) << 4);
    }
}

/* 0x001F4B90, 0x128 bytes. Replaces the last two textures of set `f` by the two sides' lord
 * colours. */
void func_001F4B90(u8 *f)
{
    u8 *d, *a, *b;
    int e;
    u32 j;
    int *pa, *pb;

    if (func_0032E7B0() != 0)
        return;
    e = SP32(0x764) - 2;
    d = func_001026D0(1, 0xB2A, 0, 1, 0, 0, (const char *)(g_004298E8), 0xD7);
    for (j = 0; j < 2; j++) {
        int c = func_0036D480(j);

        a = f + *(int *)(f + (e + j) * 4 + 4);
        a += *(int *)(a + 4);
        pa = (int *)(func_00106F10(a));
        b = d + *(int *)(d + (j + c * 2) * 4 + 4);
        b += *(int *)(b + 4);
        pb = (int *)(func_00106F10(b));
        if (*pb == *pa)
            func_00118AC0((unsigned int *)(a), b, *pb + 0x10);
    }
    func_00102EC0(d);
}

/* 0x001F4CC0, 0xFC bytes. Uploads texture set `f` (0: the stage's own). */
void func_001F4CC0(u8 *f)
{
    u32 k;

    if (f == 0) {
        func_001F4B10(0, 0);
        f = g_00732210 + *(int *)(g_00732210 + 4);
    } else {
        func_001F4B90(f);
    }
    for (k = 0; k < SP32(0x764); k++) {
        int *e = (int *)(f + *(int *)(f + k * 4 + 4));
        u8 *out = SPP(0x760) + k * 0x10;

        func_001F49A0((long long unsigned int *)(out), (u8 *)e + e[1], 0);
        if (e[0] == 2)
            func_001F49A0((long long unsigned int *)(out), (u8 *)e + e[2], 1);
    }
}

/* 0x001F4DC0, 0x1F0 bytes. Loads the scenario's stage textures. */
void func_001F4DC0(void)
{
    int v = -1, mode, k, s, h;
    u8 *d;

    if (func_0032E7B0() != 0)
        v = func_0032F090(func_0032F780());
    mode = *(int *)(g_00669D60 + 0x58);
    k = mode == 2 ? 0x54 : *(int *)(g_00669D60 + 0x60);
    if (mode == 3)
        k = 0x55;
    s = *(u16 *)(g_005BA694 + k * 100 + 2);
    if (v != -1)
        s = v;
    if (*(int *)(g_00669D60 + 0x58) == 3) {
        d = func_001026D0(1, s + 0xA70, 0, 1, 0, 0, (const char *)(g_004298E8), 0x182);
        func_001F4B10(d, *(int *)(*(int *)(d + 4) + d));
        return;
    }
    h = func_00103000(0);
    if (v == -1)
        d = func_001026D0(1, s + 0xA70, 0, 1, 0, 0, (const char *)(g_004298E8), 0x171);
    else
        d = func_001026D0(1, s + 0xA8B, 0, 1, 0, 0, (const char *)(g_004298E8), 0x16E);
    func_00103000(h);
    func_001F4B10(0, *(int *)d);
    func_001F4CC0(d);
    h = func_00103000(0);
    func_00102EC0(d);
    func_00103000(h);
}

/* 0x001F50C0, 0x88 bytes. The first object of list `l` of kind 0x18 (its +0x5A; 0xFF none). */
u8 func_001F50C0(int *l)
{
    for (; l != 0; l = (int *)l[1]) {
        u8 *o = SPP(0x1D0) + l[0] * 0x70;
        char c = func_001FF100(*(short *)(o + 0x54), 7);

        if (c != 0 && c == 0x18)
            return o[0x5A];
    }
    return 0xFF;
}

/* 0x001F5150, 0x108 bytes. The stage's frame set-up. */
void func_001F5150(void)
{
    u32 k = SP32(0x888);
    int a = 0;

    if ((0xC >> (k & 0x1F) & 1) == 0 && g_0045D468[SP32(0x88C)] < 1.0f)
        a = 1;
    func_003BF7E0();
    func_001F44E0(k);
    func_001185B0(SPAD(0x1E0), 0x50);
    SP32(0x768) = 0;
    func_001FD9A0(1, a);
    func_001FD5F0(a);
    func_001FE540(a);
    func_001FD7C0();
    func_001FEE00(a);
    func_00196EA0();
    if ((0xD >> (k & 0x1F) & 1) == 0)
        func_002477B0();
    func_001FDB70();
}

/* 0x001F5260, 0x6C bytes. */
void func_001F5260(void)
{
    SP32(0x768) = 0;
    func_001FD9A0(0, 0);
    func_001FD5F0(1);
    func_001FD8F0();
    if ((0xD >> (SP32(0x888) & 0x1F) & 1) != 0) {
        func_002477B0();
        func_001FBED0();
    }
    func_001FDB70();
}

/* 0x001F52D0, 0x9C bytes. Shuts the first open gate. */
int func_001F52D0(void)
{
    u32 n = func_00196A10(), j;
    u8 *o = SPP(0x1D0);

    for (j = 0; j < n; j++, o += 0x70) {
        if (o[0x68] > 0xC && (signed char)o[0x6B] == -0x71) {
            if (func_00196D70(PS2_ADDR(o)) == 0)
                return 0;
            o[0x69] &= 0xF8;
            o[0x6B] = 0x90;
            return 1;
        }
    }
    return 0;
}

/* 0x001F5370, 0xA8 bytes. Gives the first open gate to unit `u`'s side. */
int func_001F5370(u8 *u)
{
    u32 n = func_00196A10(), j;
    u8 *o = SPP(0x1D0);

    for (j = 0; j < n; j++, o += 0x70) {
        if (o[0x68] > 0xC && (signed char)o[0x6B] == -0x71) {
            if (func_00196D70(PS2_ADDR(o)) == 0)
                return 0;
            o[0x69] &= 0xF8;
            o[0x6B] = u[0x14E];
            return 1;
        }
    }
    return 0;
}

/* 0x001F5420, 0x8C bytes. Opens the first shut gate. */
int func_001F5420(u8 *u)
{
    u32 n = func_00196A10(), j;
    u8 *o = SPP(0x1D0);

    for (j = 0; j < n; j++, o += 0x70) {
        if (o[0x68] > 0xC && (signed char)o[0x6B] != -0x71) {
            func_00196DC0(PS2_ADDR(o));
            o[0x69] |= 7;
            o[0x6B] = 0x8F;
            return 1;
        }
    }
    return 0;
}

/* 0x001F54B0, 0xC0 bytes. Opens it, by unit `u` (an effect at the gate). */
int func_001F54B0(u8 *u)
{
    u32 n = func_00196A10(), j;
    u8 *o = SPP(0x1D0);

    for (j = 0; j < n; j++, o += 0x70) {
        if (o[0x68] > 0xC && (signed char)o[0x6B] != -0x71) {
            if (u != 0 && *(int *)(u + 0x11C) != 0)
                func_00247530(o, u + 0x90, u, 5);
            func_00196DC0(PS2_ADDR(o));
            o[0x69] |= 7;
            o[0x6B] = 0x8F;
            return 1;
        }
    }
    return 0;
}

void func_001F5570(u8 *o, int a);

/* 0x001F5870, 0x90 bytes. */
void func_001F5870(void)
{
    u32 n = func_00196A10(), j;
    u8 *o = SPP(0x1D0);

    for (j = 0; j < n; j++, o += 0x70) {
        u8 c = func_001FF100(*(short *)(o + 0x54), 10);

        if (c != 0 && func_0027F140(c) == 0)
            func_001F5570(o, o[0x69] & 8);
    }
}

/* 0x001F5BC0, 0x1CC bytes. Stage object `o`'s state flags against entry `e`. */
u8 func_001F5BC0(u8 *o, u8 *e)
{
    short id = *(short *)(o + 0x54);
    char c2 = func_001FF260((short unsigned int *)(e), func_001FF100(id, 1));
    char c3 = func_001FF290((short unsigned int *)(e), func_001FF100(id, 0));
    char c4 = func_001FF2C0((short unsigned int *)(e), func_001FF100(id, 2));
    char c5 = func_001FF100(id, 5);
    char c6 = func_001FF100(id, 4);
    char c7 = func_001FF100(id, 10);
    u8 b;

    if (c6 == 2) {
        b = 0;
    } else {
        b = c2 != 0;
        if (c2 == 2)
            b = 3;
    }
    if (c7 != 0) {
        int r = func_0027F140(c7);

        if (r == 0)
            b |= 0x12;
        else if (r == 1)
            b |= 2;
    }
    if (c3 == 2)
        b |= 4;
    if (c4 == 1)
        b |= 8;
    if (c4 == 2)
        b |= 0x10;
    if (c5 != 0)
        b |= 0x20;
    if (*(short *)(o + 0x58) != -1)
        b |= 0x80;
    return b;
}

/* 0x001F5D90, 0x118 bytes. */
u8 func_001F5D90(u8 *o, u8 *e)
{
    short id = *(short *)(o + 0x54);
    char c2 = func_001FF260((short unsigned int *)(e), func_001FF100(id, 1));
    char c3 = func_001FF290((short unsigned int *)(e), func_001FF100(id, 0));
    char c4 = func_001FF2C0((short unsigned int *)(e), func_001FF100(id, 2));
    char c5 = func_001FF100(id, 6);
    char c6 = func_001FF100(id, 4);
    u8 b = 0;

    if (c6 != 2) {
        if (c3 == 1) {
            b = c2 != 2;
            if (c4 == 1)
                b |= 0x40;
        }
        if (c5 != 0xF)
            b |= 2;
    }
    return b;
}
