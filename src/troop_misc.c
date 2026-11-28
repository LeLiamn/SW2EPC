/*
 * troop_misc.c - small battle helpers around the troop AI (parts of 0x001F0520-0x001F50BC):
 * difficulty values, the troop chance table, the duel state (0x007315E0), view distances and
 * the stage units' seen bits. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_TROOP_MISC_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 g_00669D60[];
extern u8 g_004296E0[][0x48];            /* troop chance table */
#ifdef SW2E_PC
extern ps2ptr g_00731628_a;
#define g_00731628 ((u8 *)PS2_PTR(g_00731628_a))
#define g_00731628_SET(v) (g_00731628_a = PS2_ADDR(v))
#else
extern u8 *g_00731628;
#define g_00731628_a (*(ps2ptr *)&g_00731628)
#define g_00731628_SET(v) (g_00731628 = (v))
#endif
extern int g_007315E0[];                 /* the duel state (+0x38: its 4 actors) */
extern u8 g_0073164C;
#ifdef SW2E_PC
extern ps2ptr g_0045D410_a;                   /* (small data) the stage units' seen bits */
#define g_0045D410 ((u8 *)PS2_PTR(g_0045D410_a))
#define g_0045D410_SET(v) (g_0045D410_a = PS2_ADDR(v))
#else
extern u8 *g_0045D410;
#define g_0045D410_a (*(ps2ptr *)&g_0045D410)
#define g_0045D410_SET(v) (g_0045D410 = (v))
#endif
extern int (*g_00429410[0x1D])(void);

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define SPAD_INT(a) (*(int *)PS2_PTR(a))
#define SPAD_PTR(a) ((u8 *)PS2_PTR(*(ps2ptr *)PS2_PTR(a)))

void func_001F3150(int a, int b, int c);
void func_001F3FC0(float d, int a, int b, int c);

/* 0x001F0520, 0x1C bytes, matching. */
u8 func_001F0520(u8 *u)
{
    return func_00348D20(u);
}

/* 0x001F0570, 0x34 bytes. */
int func_001F0570(u32 k)
{
    if (k < 0x1D)
        return g_00429410[k]();
    return 8;
}

/* 0x001F0C50, 0x80 bytes. A chance by the flags `f` (2: 40%, 4: 20%, 8: 10%). */
int func_001F0C50(u32 f)
{
    u32 v;

    if ((f & 2) != 0)
        v = 0x28;
    else if ((f & 4) != 0)
        v = 0x14;
    else if ((f & 8) != 0)
        v = 10;
    else
        return 0;
    return RANDOM() % 100 < v;
}

/* 0x001F1060, 0x68 bytes, matching. */
int func_001F1060(u8 k)
{
    switch (k) {
    case 0:
        return 4;
    case 1:
        return 4;
    case 2:
        return 8;
    case 3:
        return 4;
    case 4:
        return 2;
    case 5:
        return 4;
    default:
        return 4;
    }
}

int func_001F15E0(u8 *o);

/* 0x001F1300, 0x58 bytes. */
int func_001F1300(u8 *o)
{
    int v = func_001F15E0(o), r = 2;

    if (v != 2) {
        if (v == 1)
            r = -2;
        else
            r = 0;
    }
    return r;
}

/* 0x001F1360, 0x10 bytes, matching. */
float func_001F1360(u8 *s, int k)
{
    return 500.0f;
}

/* 0x001F15B0, 0x24 bytes, matching. */
u8 *func_001F15B0(int a, int b)
{
    return g_004296E0[a] + b * 8;
}

/* 0x001F15E0, 0x58 bytes. A player troop's level (by the player it follows). */
int func_001F15E0(u8 *o)
{
    int v;

    if ((*(u32 *)(o + 0xB8) & 4) == 0) {
        if ((*(u32 *)(o + 0xB8) & 8) == 0)
            return 0;
        v = *(int *)(g_00669D60 + 0xD0);
    } else {
        v = *(int *)(g_00669D60 + 0x88);
    }
    return func_002F67B0(v);
}

/* 0x001F1770, 0x1C bytes, matching. */
int func_001F1770(u8 *c, u8 i, u32 n)
{
    return func_003DCF20(c, i, n);
}

/* 0x001F1790, 0x1C bytes, matching. */
int func_001F1790(u8 *c, u8 *o)
{
    return func_003DD0C0(c, o);
}

/* 0x001F17B0, 0x1C bytes, matching. */
int func_001F17B0(u8 *c, u32 i)
{
    return func_003DD1D0(c, i);
}

/* 0x001F1E90, 0x28 bytes. */
void func_001F1E90(void)
{
    func_00102EC0(g_00731628);
    g_00731628_SET(0);
}

/* 0x001F27D0, 0x34 bytes. Marks duel actor `k`. */
void func_001F27D0(int k)
{
    if (k < 4)
        g_0073164C |= 1 << (k & 0x1F);
}

/* 0x001F2810, 0x68 bytes. Marks the duel slots of actor `p`. */
void func_001F2810(int p)
{
    int k;

    if (p == 0)
        return;
    for (k = 0; k < 4; k++) {
        if (g_007315E0[0xE + k] == p)
            func_001F27D0(k);
    }
}

/* 0x001F29E0, 0x14 bytes, matching. */
int func_001F29E0(void)
{
    return g_007315E0[0] == 2;
}

/* 0x001F2AD0, 0x14 bytes, matching. */
int func_001F2AD0(void)
{
    return g_007315E0[0] != 5;
}

/* 0x001F3320, 0x1C bytes, matching. */
void func_001F3320(int a, int b)
{
    func_001F3150(a, b, 1);
}

/* 0x001F3340, 0x20 bytes, matching. */
void func_001F3340(int a, int b)
{
    func_001F3150(a, 0, b);
}

/* 0x001F4580, 0x24 bytes, matching. */
void func_001F4580(int a, int b)
{
    func_001F3FC0(45.0f, a, b, 0);
}

/* 0x001F45B0, 0x24 bytes, matching. */
void func_001F45B0(int a, int b)
{
    func_001F3FC0(145.0f, a, b, 3);
}

/* 0x001F4870, 0x28 bytes. */
u8 func_001F4870(u8 *p)
{
    if (p == 0)
        return 0xF;
    return p[SPAD_INT(0x70000B50) + 1];
}

/* 0x001F4FB0, 0x34 bytes. Marks bit `b` of stage unit `a`. */
void func_001F4FB0(int a, int b)
{
    u32 v = a * 2 + b;

    g_0045D410[v >> 3] |= 1 << (v & 7);
}

/* 0x001F4FF0, 0x30 bytes. */
u32 func_001F4FF0(int a, int b)
{
    u32 v = a * 2 + b;

    return g_0045D410[v >> 3] & 1 << (v & 7) & 0xFF;
}

/* 0x001F5020, 0x40 bytes. Clears them. */
void func_001F5020(void)
{
    int n = func_00196A10();

    func_001185B0(g_0045D410, ((n * 2 + 7u) >> 3) + 0xF >> 4);
}

/* 0x001F5060, 0x30 bytes, matching. */
int func_001F5060(int a, int b)
{
    return *(int *)(SPAD_PTR(0x700001DC) + b * 100 + a * 4);
}

/* 0x001F5090, 0x30 bytes, matching. */
void func_001F5090(int a, int b, int v)
{
    *(int *)(SPAD_PTR(0x700001DC) + b * 100 + a * 4) = v;
}

extern int g_00731604, g_00731608;
extern u8 g_0073164D;

/* 0x001F0FC0, 0x90 bytes. A troop's level: its record's for plain troops, else by the
 * difficulty. */
u8 func_001F0FC0(u8 *o)
{
    char d;

    if ((*(u32 *)(o + 0x80) & 0x30) == 0)
        return (*(u8 **)(o + 8))[0x1F];
    d = g_00669D60[0x21];
    if (d == 4)
        return 3;
    if (d == 3)
        return 4;
    if (d == 2)
        return 5;
    if (d == 1)
        return 7;
    if (d == 0)
        return 7;
    return 5;
}

/* 0x001F10D0, 0x70 bytes. */
int func_001F10D0(char k)
{
    if (k == 4)
        return 200;
    if (k == 3)
        return 400;
    if (k == 2)
        return 300;
    if (k == 1)
        return 200;
    if (k == 0)
        return 0;
    return 200;
}

/* 0x001F1140, 0x94 bytes. */
int func_001F1140(char k, int b)
{
    int r;

    if (k == 4)
        return b == 0 ? 2 : 4;
    if (k == 3)
        return 6;
    if (k == 2)
        return 5;
    r = 1;
    if (k == 1)
        r = b == 0 ? 1 : 4;
    return r;
}

/* 0x001F11E0, 0x9C bytes, matching. */
void func_001F11E0(u8 k, float *out)
{
    switch (k) {
    case 0:
        *out = 1.0f;
        break;
    case 1:
        *out = 3.0f;
        break;
    case 2:
        *out = 2.0f;
        break;
    case 3:
        *out = 1.5f;
        break;
    case 4:
        *out = 1.3f;
        break;
    case 5:
        *out = 0.8f;
        break;
    case 6:
        *out = 0.6f;
        break;
    default:
        *out = 1.0f;
        break;
    }
}

/* 0x001F1280, 0x74 bytes. By the difficulty. */
int func_001F1280(void)
{
    char d = g_00669D60[0x21];

    if (d == 4)
        return 7;
    if (d == 3)
        return 9;
    if (d == 2)
        return 0xC;
    if (d == 1)
        return 0x14;
    if (d == 0)
        return 0x1E;
    return 0xC;
}

/* 0x001F2450, 0x6C bytes. */
int func_001F2450(void)
{
    u32 f = *(u32 *)(g_00669D60 + 0x200);
    int on = 0;

    if ((f & 0x800000) != 0 && g_0073164D != 0)
        on = 1;
    if (!on && ((f & 0x2000000) == 0 || g_0073164D == 0))
        return 0;
    return 1;
}

/* 0x001F2A00, 0xC0 bytes. Whether the duel's side in play has state 5 or 6. */
int func_001F2A00(void)
{
    if (g_007315E0[0] == 4)
        return g_00731608 == 5 || g_00731608 == 6;
    if (g_007315E0[0] == 3)
        return g_00731604 == 5 || g_00731604 == 6;
    if (g_007315E0[0] == 2)
        return g_00731608 == 5 || g_00731608 == 6;
    return 0;
}

/* ---- Troop targets, map cell counts and the duel state (parts of 0x001F02F0-0x001F2CDC). Troop
 * records are 0x88 bytes from 0x00693970; the map cells count the troops of each side in their
 * slots (+8) and their soldiers (+0xC). ---- */

#ifdef SW2E_PC
extern ps2ptr g_0045D2F0_a;                   /* (small data) the map */
#define g_0045D2F0 ((u8 *)PS2_PTR(g_0045D2F0_a))
#define g_0045D2F0_SET(v) (g_0045D2F0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2F0;
#define g_0045D2F0_a (*(ps2ptr *)&g_0045D2F0)
#define g_0045D2F0_SET(v) (g_0045D2F0 = (v))
#endif
extern int g_0045D2A8;
extern u8 g_00693970[];
extern u8 g_004295A0[][0xC], g_00429678[0xC], g_00429690[][0xC];
extern u8 g_00429488[], g_00429490[], g_004294A0[], g_004294B0[], g_004294D0[], g_004294F0[];
extern u8 g_00429520[], g_00429530[], g_00429540[], g_00429550[];
extern u8 g_004298D8[];
extern u8 g_005B4DF0;
extern u8 g_0073164D;
extern u8 g_00731730[], g_00731850[], g_00731970[], g_00731A90[], g_00731BB0[], g_00731CD0[];
extern u8 g_00731DF0[], g_00731F10[], g_00732030[];

#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))
#define CELL(c) ((c) == 0 || (c)[0] > 0x1F || (c)[1] > 0x1F ? (u8 *)0 :                    \
                 ((u8 **)*(u8 **)(g_0045D2F0 + 4))[(c)[0] + (c)[1] * 0x20])
#define ALIVE(t) ((*(u32 *)((t) + 0x80) & 1) != 0 && (*(u32 *)((t) + 0x80) & 0x8C40002) == 0)
#define TROOP_INDEX(t) (((t) - g_00693970) / 0x88)
#define DUEL(i) g_007315E0[i]
#define DUELF(i) (((float *)g_007315E0)[i])
#define MAP_ID() (*(int *)(g_00669D60 + 0x58) == 2 ?                                        \
                  *(int *)(g_00669D60 + 0x74 + *(int *)(g_00669D60 + 0x238) % 5 * 4) :      \
                  *(int *)(g_00669D60 + 0x74))

int func_001F1B90(u8 *c);
void func_001F17D0(u8 *c, u32 k, u8 n);
void func_001F1870(u8 *c, u32 k, u32 n);
void func_002554B0(int *d);
void func_00256310(int *d);
void func_00258920(int *d);
void func_00259400(int *d);
void func_00255620(int *d);
void func_00255EA0(int *d);
void func_00256620(int *d);
void func_00258AC0(int *d);
void func_00259740(int *d);
void func_00255B00(int *d);
void func_00256300(int *d);
void func_002577C0(int *d);
void func_00259230(int *d);
void func_0025A550(int *d);
void func_001023B0(int fn);
int func_001F29E0(void);
int func_001F24C0(void);
float func_002E38D0(void);
void func_002E3D90(u8 *p);

/* 0x001F02F0, 0xE4 bytes. Whether troop `t` can attack its target. */
int func_001F02F0(u8 *t)
{
    u8 *e;
    short c;

    if ((*(u32 *)(t + 0x84) & 1) != 0 || (e = *(u8 **)(t + 0x18)) == 0)
        return 0;
    if (ALIVE(e) && (*(u32 *)(e + 0x84) & 2) == 0 && e[0x7A] != 3 && t[0x79] != e[0x79]) {
        c = *(short *)(e + 0x40);
        if (func_001F1B90((u8 *)&c) == 0 && func_003498B0(t, e) != 0)
            return 1;
    }
    return 0;
}

/* 0x001F03E0, 0x140 bytes. Whether troop `t` still has a goal (a place or a troop). */
int func_001F03E0(u8 *t)
{
    u8 *e;

    if (*(float *)(t + 0x38) != 0.0f) {
        u8 c[2];

        c[0] = (int)*(float *)(t + 0x38) / 1000;
        c[1] = (int)*(float *)(t + 0x3C) / 1000;
        if (*(short *)c != *(short *)(t + 0x46))
            return 1;
        if (t[0x7A] == 3)
            return 1;
        *(int *)(t + 0x38) = 0;
        *(int *)(t + 0x3C) = 0;
        *(u32 *)(t + 0x84) |= 0x10;
    }
    e = *(u8 **)(t + 0x1C);
    if (e != 0) {
        if (ALIVE(e) && e[0x7A] != 3)
            return 1;
        *(u8 **)(t + 0x1C) = 0;
        *(u32 *)(t + 0x84) |= 0x10;
    }
    return 0;
}

/* 0x001F0600, 0x358 bytes. The stage's gates near `pos` (up to four pairs of cells into
 * `out`); whether there is one. */
int func_001F0600(u8 *pos, u8 *out)
{
    int map = MAP_ID();
    u32 n = 6, cnt = 0, j;
    u8 *a, *b, *o = out;
    u8 cur[2], p1[2], p2[2], c1[2], c2[2];

    if (map == 6) {
        n = 2;
        a = g_00429540;
        b = g_00429550;
    } else if (map == 5) {
        n = 2;
        a = g_00429520;
        b = g_00429530;
    } else if (map == 3) {
        a = g_004294D0;
        b = g_004294F0;
    } else if (map == 2) {
        n = 3;
        a = g_004294A0;
        b = g_004294B0;
    } else if (map == 1) {
        n = 2;
        a = g_00429488;
        b = g_00429490;
    } else {
        return 0;
    }
    cur[0] = pos[0] / 5;
    cur[1] = pos[1] / 5;
    for (j = 0; j < n; j++, a += 4, b += 8) {
        p1[0] = a[0];
        p1[1] = a[1];
        p2[0] = a[2];
        p2[1] = a[3];
        c1[0] = p1[0] / 5;
        c1[1] = p1[1] / 5;
        c2[0] = p2[0] / 5;
        c2[1] = p2[1] / 5;
        if ((func_0018F6F0((short unsigned int *)(cur), (short unsigned int *)(c1), 0) < 4 && func_0018C420(pos, p1) < 6)
            || (func_0018F6F0((short unsigned int *)(cur), (short unsigned int *)(c2), 0) < 4 && func_0018C420(pos, p2) < 6)) {
            int k;

            cnt += 4;
            for (k = 0; k < 8; k++)
                o[k] = b[k];
            o += 8;
            if (cnt > 7)
                break;
        }
    }
    for (; cnt < 8; cnt++) {
        out[cnt * 2] = 0;
        out[cnt * 2 + 1] = 0;
    }
    return cnt != 0;
}

/* 0x001F1370, 0x100 bytes. Troop `t`'s three view distances. */
void func_001F1370(u8 *t, int k, u32 *out)
{
    u8 *s;

    if ((*(u32 *)(t + 0xB8) & 0x2000) == 0) {
        if (k == 0)
            s = g_004295A0[(*(u8 **)(t + 0x68))[0x1C]];
        else
            s = g_00429678;
    } else {
        u32 f = *(u32 *)(*(u8 **)(t + 0x68) + 0x28);
        int i;

        if ((f & 4) != 0)
            i = 0;
        else if ((f & 8) != 0)
            i = 1;
        else if ((f & 0x10) != 0)
            i = 2;
        else if ((f & 0x20) != 0)
            i = 3;
        else if ((f & 0x40) != 0)
            i = 4;
        else if ((f & 0x80) != 0)
            i = 5;
        else
            i = 0;
        s = g_00429690[i];
    }
    out[0] = ((u32 *)s)[0];
    out[1] = ((u32 *)s)[1];
    out[2] = ((u32 *)s)[2];
}

/* 0x001F1470, 0x70 bytes, matching. Their squares (`add`: 300 farther). */
void func_001F1470(u8 *t, int k, int add, float *out)
{
    u32 j;

    func_001F1370(t, k, (u32 *)out);
    for (j = 0; j < 3; j++, out++) {
        if (add != 0)
            *out += 300.0f;
        *out = *out * *out;
    }
}

/* 0x001F14E0, 0xC8 bytes. Troop `t`'s chance row. */
u8 *func_001F14E0(u8 *t)
{
    u32 s = *(int *)(t + 0xC) == 0 ? t[0x7A] : 4;

    if ((*(u32 *)(t + 0xB8) & 0x10) == 0 || (GAME_FLAGS & 8) == 0)
        return (u8 *)PS2_PTR(0x43E740) + t[0x7B] * 0xF + s * 300;
    return (u8 *)PS2_PTR(0x441890) + t[0x7B] * 0xF + s * 300;
}

/* 0x001F1640, 0x128 bytes. A free cell of the 5x5 block `c`, from a random one. */
void func_001F1640(u8 *c, short *out)
{
    u32 r = RANDOM() % 0x19, j;
    u8 v[2];

    for (j = 0; j < 0x19; j++) {
        v[0] = r % 5 + c[0] * 5;
        v[1] = r / 5 + c[1] * 5;
        if (func_0018C160(v) != 0) {
            *out = *(short *)v;
            return;
        }
        r = (int)(r + 1) % 0x19;
    }
    *out = *(short *)v;
}

/* 0x001F17D0, 0x94 bytes. Removes `n` soldiers of side slot `k` from cell `c`. */
void func_001F17D0(u8 *c, u32 k, u8 n)
{
    u8 *r = CELL(c);

    if (r != 0) {
        r += k & 0xFF;
        r[0xC] = r[0xC] < n ? 0 : r[0xC] - n;
    }
}

/* 0x001F1870, 0x98 bytes. Adds them. */
void func_001F1870(u8 *c, u32 k, u32 n)
{
    u8 *r = CELL(c);

    if (r != 0) {
        u32 v;

        r += k & 0xFF;
        v = r[0xC] + (n & 0xFF);
        r[0xC] = v < 0xFF ? v : 0xFF;
    }
}

/* 0x001F1910, 0x118 bytes. Troop `t` leaves its cell. */
void func_001F1910(u8 *t)
{
    u8 c[2], *r, *g;
    u8 k;

    if ((*(u32 *)(t + 0x80) & 0x1B0) != 0)
        return;
    *(short *)c = *(short *)(t + 0x40);
    r = CELL(c);
    if (r == 0)
        return;
    k = t[0x79];
    r += k;
    if (r[8] != 0) {
        r[8]--;
        func_001F17D0(c, k, t[0x74] + 1);
        if (func_0034A630(t) != 0 && (g = func_0034ECA0(c)) != 0)
            func_0034F030(g, TROOP_INDEX(t));
    }
}

/* 0x001F1A30, 0x154 bytes. Troop `t` enters its cell. */
void func_001F1A30(u8 *t)
{
    u8 c[2], *r, *g;
    u8 k;

    if (!ALIVE(t) || (*(u32 *)(t + 0x80) & 0x1B0) != 0)
        return;
    *(short *)c = *(short *)(t + 0x40);
    r = CELL(c);
    if (r == 0)
        return;
    k = t[0x79];
    r += k;
    if (r[8] != 0xFF) {
        r[8]++;
        func_001F1870(c, k, t[0x74] + 1);
        if (func_0034A630(t) != 0 && (g = func_0034ECA0(c)) != 0)
            func_0034EFA0(g, TROOP_INDEX(t));
    }
}

/* 0x001F1B90, 0x64 bytes. Whether `c` is outside the map. */
int func_001F1B90(u8 *c)
{
    return CELL(c) == 0;
}

/* 0x001F1C00, 0x68 bytes. Side slot `k`'s troop count in cell `c`. */
u32 func_001F1C00(u8 *c, u32 k)
{
    return CELL(c)[(k & 0xFF) + 8];
}

#define DUEL_BUFFERS() do {                                             \
    func_001CB810(g_00731730, 0x30);                                    \
    func_001CB810(g_00731850, 0x30);                                    \
    func_001CB810(g_00731970, 0x30);                                    \
    func_001CB810(g_00731A90, 0x30);                                    \
    func_001CB810(g_00731CD0, 0x30);                                    \
    func_001CB810(g_00731DF0, 0x30);                                    \
    func_001CB810(g_00731F10, 0x30);                                    \
    func_001CB810(g_00732030, 0x30);                                    \
    func_001CB810(g_00731BB0, 0x30);                                    \
} while (0)

/* 0x001F1C70, 0xE0 bytes. Loads the duel's file. */
void func_001F1C70(void)
{
    g_00731628_SET(func_001026D0(1, 0xC07, 0, 1, 0, 0, (const char *)(g_004298D8), 0xC));
    DUEL_BUFFERS();
    DUEL(0) = 5;
}

/* 0x001F1D50, 0x134 bytes, matching. Resets the duel state. */
void func_001F1D50(void)
{
    DUEL(0) = 5;
    DUEL(1) = 4;
    DUEL(2) = 0;
    DUEL(7) = 0;
    DUEL(8) = 0;
    DUEL(3) = 0;
    DUEL(9) = 0;
    DUEL(14) = 0;
    DUEL(4) = 0;
    DUEL(10) = 0;
    DUEL(15) = 0;
    DUEL(5) = 0;
    DUEL(11) = 0;
    DUEL(16) = 0;
    DUEL(6) = 0;
    DUEL(12) = 0;
    DUEL(17) = 0;
    DUEL_BUFFERS();
}

/* 0x001F1EC0, 0x220 bytes. Starts a duel of kind `kind` between `n` actors. */
void func_001F1EC0(u32 *actors, u32 n, int kind)
{
    u32 j = 0;

    DUEL(0) = kind;
    if (n != 0) {
        for (; j < n; j++)
            DUEL(14 + j) = actors[j];
    }
    for (; j < 4; j++)
        DUEL(14 + j) = 0;
    g_0073164C = 0;
    if (DUEL(0) == 0)
        func_002554B0(g_007315E0);
    else if (DUEL(0) == 1)
        func_00255D00((unsigned char *)(g_007315E0));
    else if (DUEL(0) == 2)
        func_00256310(g_007315E0);
    else if (DUEL(0) == 3)
        func_00258920(g_007315E0);
    else if (DUEL(0) == 4)
        func_00259400(g_007315E0);
    g_0045D2A8 = 0;
    func_00254030();
    func_0035D9E0();
    func_001023B0(0x1F23A0);
}

/* 0x001F20E0, 0x50 bytes. */
void func_001F20E0(u32 a, int kind)
{
    u32 t = 0;

    t = a;
    func_001F1EC0(&t, 1, kind);
}

/* 0x001F2130, 0x108 bytes. Ends the duel. */
void func_001F2130(void)
{
    if (DUEL(0) == 0)
        func_002555D0(PS2_ADDR(g_007315E0));
    else if (DUEL(0) == 1)
        func_00255E00(PS2_ADDR(g_007315E0));
    else if (DUEL(0) == 2)
        func_00256580((unsigned char *)(g_007315E0));
    else if (DUEL(0) == 3)
        func_00258A40(PS2_ADDR(g_007315E0));
    else if (DUEL(0) == 4)
        func_00259670(PS2_ADDR(g_007315E0));
    g_0073164D = 0;
    DUEL(9) = 0;
    DUEL(10) = 0;
    DUEL(11) = 0;
    DUEL(12) = 0;
    DUEL(0) = 5;
    GAME_FLAGS &= ~0x200;
    func_001023B0(0x1C9390);
}

/* 0x001F2240, 0x160 bytes. The duel's frame; whether it goes on. */
int func_001F2240(float dt)
{
    DUELF(2) = dt;
    if (DUEL(0) == 0)
        func_00255620(g_007315E0);
    else if (DUEL(0) == 1)
        func_00255EA0(g_007315E0);
    else if (DUEL(0) == 2)
        func_00256620(g_007315E0);
    else if (DUEL(0) == 3)
        func_00258AC0(g_007315E0);
    else if (DUEL(0) == 4)
        func_00259740(g_007315E0);
    g_005B4DF0 = (g_005B4DF0 & 0xFD) | 2;
    DUELF(7) += DUELF(2);
    DUELF(4) += DUELF(2);
    DUELF(3) += DUELF(2);
    DUELF(5) += DUELF(2);
    DUELF(6) += DUELF(2);
    return DUELF(7) < DUELF(8);
}

/* 0x001F23A0, 0xB0 bytes, matching. Draws the duel. */
void func_001F23A0(void)
{
    if (DUEL(0) == 0)
        func_00255B00(g_007315E0);
    else if (DUEL(0) == 1)
        func_00256300(g_007315E0);
    else if (DUEL(0) == 2)
        func_002577C0(g_007315E0);
    else if (DUEL(0) == 3)
        func_00259230(g_007315E0);
    else if (DUEL(0) == 4)
        func_0025A550(g_007315E0);
}

/* 0x001F24C0, 0x1AC bytes. */
int func_001F24C0(void)
{
    if (DUEL(0) == 4)
        return DUEL(10) == 5 || DUEL(10) == 6;
    if (DUEL(0) == 3)
        return (u32)DUEL(9) < 7;
    if (DUEL(0) == 2)
        return DUEL(10) == 5 || DUEL(10) == 6;
    return 0;
}

/* 0x001F2680, 0x144 bytes. Whether actor `a` still takes part. */
int func_001F2680(int a)
{
    u32 j;

    if (DUEL(0) == 4 || DUEL(0) == 3) {
        if ((u32)DUEL(9) < 5) {
            for (j = 1; j < 4; j++) {
                if (DUEL(14 + j) != 0 && DUEL(14 + j) == a && (g_0073164C & 1 << (j & 0x1F)) == 0)
                    return 1;
            }
        }
    } else if (DUEL(0) == 2) {
        if ((u32)DUEL(9) < 5)
            return DUEL(10) == 8;
        return 0;
    }
    return 0;
}

/* 0x001F2880, 0x158 bytes. */
int func_001F2880(u32 side)
{
    u32 s = side != ((u8 *)PS2_PTR(DUEL(14)))[0x14E];

    if (DUEL(0) == 4 || DUEL(0) == 3 || DUEL(0) == 2) {
        if ((u32)DUEL(9) > 5)
            return 1;
        return 0.0f < DUELF(0x2C + s * 12);
    }
    return 1;
}

/* 0x001F2AF0, 0x7C bytes, matching. */
int func_001F2AF0(void)
{
    int r = 0;

    if ((GAME_FLAGS & 0x800000) != 0 && func_001F29E0() != 0 && func_001F24C0() != 0) {
        r = DUEL(15);
        if (r != 0 && ((u8 *)PS2_PTR(r))[0x14E] == 0)
            r = DUEL(14);
    }
    return r;
}

/* 0x001F2B70, 0x3C bytes. */
float func_001F2B70(u8 *u)
{
    float a = func_002E38D0(), b = func_00209E00((float *)(u));

    return a < b ? a : b;    /* min.s */
}

/* 0x001F2BB0, 0x3C bytes. */
float func_001F2BB0(u8 *u)
{
    float a = func_002E38D0(), b = func_0020A2F0(PS2_ADDR(u));

    return a < b ? a : b;    /* min.s */
}

/* 0x001F2BF0, 0x6C bytes. */
void func_001F2BF0(u8 *p)
{
    p[4] = 0xC;
    p[5] = 0xFF;
    *(u32 *)(p + 0x10) = *(u32 *)PS2_PTR(0x700000C0);
    *(u32 *)(p + 0x14) = *(u32 *)PS2_PTR(0x700000C4);
    *(u32 *)(p + 0x18) = *(u32 *)PS2_PTR(0x700000C8);
    *(u32 *)(p + 0x1C) = *(u32 *)PS2_PTR(0x700000CC);
    *(u32 *)(p + 0x30) = *(u32 *)PS2_PTR(0x70000130);
    *(u32 *)(p + 0x34) = *(u32 *)PS2_PTR(0x70000134);
    *(u32 *)(p + 0x38) = *(u32 *)PS2_PTR(0x70000138);
    *(u32 *)(p + 0x3C) = *(u32 *)PS2_PTR(0x7000013C);
    func_002E3D90(p);
    *(u32 *)(p + 0x14) = *(u32 *)(p + 0x10);
    func_002098E0(PS2_ADDR(p));
}

/* 0x001F2C60, 0x80 bytes. */
int func_001F2C60(u8 *u)
{
    if (u == 0)
        return 0;
    if (*(int *)(u + 0x118) == 0x3C) {
        u8 *w = *(u8 **)(u + 0x28C);

        if (w == 0)
            return 1;
        if (w[0x14E] > 1)
            return 0;
    } else if (u[0x185] == 0x17 && u[0x14E] > 1) {
        return 0;
    }
    return 1;
}
