/*
 * troop_ai.c - the foot soldiers' choices in battle (attack, guard, back off, use an item), drawn
 * from the chance table of their kind (func_001F14E0), and the map objects that act on the stage
 * units around them. Original file name unknown (parts of 0x0027B610-0x0027DF8C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Soldier (`s`): +0x08 its target link, +0x14 its actor, +0x78 a wait (u16), +0x7C its stance
 * (0 attack, 1 guard, 2-3 flee), +0x7D its order, +0xA4, +0xB8 flags (0x20: side 1), +0xBC its
 * order bits (bits 6-18 the current order).
 */

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_001F0520   /* the original callers here see it this way */
unsigned int func_001F0520(unsigned char *);
#endif
#define SW2E_FILE_TROOP_AI_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_00271A10();

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A3A30[][0xC0];            /* the battle officers (0 and 1: the commanders) */
extern u8 g_00753190[0x10][0x1A0];       /* the items */
extern u8 g_00440418[];
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define UNITS (*(u8 **)0x700001D0)       /* (scratchpad) the stage units (0x70 bytes each) */
#define g_700001E0 ((u8 *)0x700001E0)    /* (scratchpad) a unit bit set */

void func_00204D00(u8 *s, int a);
void func_00206080(u8 *s);
void func_002AFC20(u8 *s);
void func_00204B60(u8 *s, u32 f);
void func_00238AE0(u8 *s, int t);
void func_00204BB0(u8 *s);
u32 func_001FF100(u16 v, int k);
int func_0027D6B0(u8 *u, int v);
void func_0027D960(void);

void func_0027B730(u8 *s);
void func_0027C030(u8 *s);
void func_0027C210(u8 *s, int f);

/* Sets soldier `s`'s order to 2 (its order bits cleared). */
static void order2(u8 *s)
{
    *(u32 *)(s + 0xBC) &= 0xFFF8003F;
    s[0x7D] = 2;
}

/* The commander of soldier `s`'s side. */
#define SIDE_CMD(s) (g_006A3A30[(*(u32 *)((s) + 0xB8) & 0x20) == 0])

/* 0x0027B610, 0x9C bytes. Soldier `s` charges (alone or with others, by chance). */
void func_0027B610(u8 *s)
{
    u8 *t = func_001F14E0(s);

    order2(s);
    if (RANDOM() % 100 < t[1])
        func_00204D00(s, 0);
    else
        func_00204D00(s, 1);
}

/* 0x0027B6B0, 0x7C bytes. */
void func_0027B6B0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < t[3])
        func_00236DD0(PS2_ADDR(s));
    else
        func_0027B730(s);
}

/* 0x0027B730, 0x238 bytes. Soldier `s` with a target: charges by chance (more when its side's
 * commander is hurt; half for some weapon kinds). */
void func_0027B730(u8 *s)
{
    u8 *t = func_001F14E0(s), *a, *m;
    short *life;
    u32 f;
    float k, hurt;
    int c;
    char w;

    if (func_00236F30(s) == 0)
        return;
    func_00236ED0(s);
    f = *(u32 *)(*(u8 **)(*(u8 **)(*(u8 **)(s + 8) + 0x14) + 0x210) + 0x18);
    if ((f & 0x800) != 0 || (f & 0x2000) != 0)
        return;
    a = *(u8 **)(s + 0x14);
    m = *(u8 **)(a + 0x110);
    w = m == 0 ? 'j' : m[0x1C];
    if (w == ',' || w == 0x1F) {
        k = 1.0f;
    } else {
        w = m == 0 ? 'j' : m[0x1C];
        k = (w == '-' || w == 0x1E) ? 0.5f : 1.0f;
    }
    life = (short *)(a[0x14E] == 3 ? g_006A3A30[1] + 0x80 : g_006A3A30[0] + 0x80);
    if (life[0] / 2 < life[1])
        hurt = 0.0f;
    else
        hurt = (50.0f - (float)life[1] / (float)life[0] * 100.0f) / 50.0f;
    c = (int)((float)t[8] * k);
    if (RANDOM() % 100 < (u32)(c + (int)((float)c * hurt)))
        func_0027B610(s);
    else
        func_00206080(s);
}

/* 0x0027B970, 0x74 bytes. A soldier's choice by stance (target kind 1). */
void func_0027B970(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_0027B730(s);
    else if (st == 0)
        func_0027B6B0(s);
}

/* 0x0027B9F0, 0xF4 bytes. An archer's choice: shoot, volley, step back or wait. */
void func_0027B9F0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < t[0])
        func_002B0180(s, 0);
    else if (RANDOM() % 100 < t[1])
        func_002B0180(s, 1);
    else if (RANDOM() % 100 < t[3])
        func_002AFC20(s);
    else
        func_00206080(s);
}

/* 0x0027BAF0, 0x74 bytes. */
void func_0027BAF0(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_002396B0(PS2_ADDR(s), 1);
    else if (st == 0)
        func_0027B9F0(s);
}

/* 0x0027BE70, 0x1C0 bytes. Whether soldier `s` goes for a healing item (its commander below half
 * life, no item of kind 5 already lying around). */
int func_0027BE70(u8 *s)
{
    u8 *c = SIDE_CMD(s);
    float life = (float)*(short *)(c + 0x82), most = (float)*(short *)(c + 0x80);
    u8 *t;
    u32 k;

    if (most < life * 2.0f)
        return 0;
    t = func_001F14E0(s);
    if (RANDOM() % 100 >= (u32)(int)(((50.0f - life / most * 100.0f) * 0.01f + 1.0f) * (float)t[9]))
        return 0;
    for (k = 0; k < 0x10; k++) {
        if ((g_00753190[k][0x19F] & 1) != 0 && g_00753190[k][0x19D] == 5)
            return 0;
    }
    return 1;
}

/* 0x0027C1D0, 0x34 bytes. */
void func_0027C1D0(u8 *s)
{
    order2(s);
    func_00204B60(s, 0);
}

/* 0x0027C3E0, 0x38 bytes. */
void func_0027C3E0(u8 *s)
{
    order2(s);
    func_00204B60(s, 0x200);
}

/* 0x0027C420, 0x38 bytes. */
void func_0027C420(u8 *s)
{
    order2(s);
    func_00271A10(PS2_ADDR(s), 7);
}

/* 0x0027C460, 0xF0 bytes. A spearman's choice: thrust, attack, close in or wait. */
void func_0027C460(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < t[0])
        func_0027C210(s, 1);
    else if (RANDOM() % 100 < t[1])
        func_0027C1D0(s);
    else if (RANDOM() % 100 < t[3])
        func_0027C030(s);
    else
        func_00206080(s);
}

/* 0x0027C550, 0xB4 bytes. Its guard choice. */
void func_0027C550(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < t[0])
        func_0027C420(s);
    else if (RANDOM() % 100 < t[1])
        func_0027C3E0(s);
    else
        func_00239830(s);
}

/* 0x0027C610, 0x74 bytes. */
void func_0027C610(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_0027C550(s);
    else if (st == 0)
        func_0027C460(s);
}

/* 0x0027C910, 0xB0 bytes. Chance `c` raised when the soldier's life is below half (at most 50). */
int func_0027C910(u8 *s, int c)
{
    float life = (float)*(short *)(s + 0x82), most = (float)*(short *)(s + 0x80);

    if (life * 2.0f < most) {
        c += (int)((float)c * (50.0f - life / most * 100.0f) * 0.02f);
        if (c > 0x32)
            c = 0x32;
    }
    return c;
}

/* 0x0027C9C0, 0x9C bytes. */
void func_0027C9C0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < t[4]) {
        order2(s);
        func_00271A10(PS2_ADDR(s), 0);
    } else {
        func_00238AE0(s, 0x28);
    }
}

/* 0x0027CA60, 0x88 bytes. An attack (`strong`: 0x1000001; else 1 or 2 at random). */
void func_0027CA60(u8 *s, int strong)
{
    u32 f = 2;

    order2(s);
    if (strong == 0) {
        if (RANDOM() % 100 < 0x32)
            f = 1;
    } else {
        f = 0x1000001;
    }
    func_00204B60(s, f);
}

/* 0x0027CAF0, 0x120 bytes. A swordsman's choice (bolder when hurt). */
void func_0027CAF0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (RANDOM() % 100 < (u32)func_0027C910(s, t[0]))
        func_0027CA60(s, 0);
    else if (RANDOM() % 100 < (u32)func_0027C910(s, t[1]))
        func_0027CA60(s, 1);
    else if (RANDOM() % 100 < t[3])
        func_0027C9C0(s);
    else
        func_00206080(s);
}

/* 0x0027CC10, 0xD8 bytes. Its guard choice. */
void func_0027CC10(u8 *s)
{
    u8 *l = *(u8 **)(s + 8), *t;

    if (l == 0)
        return;
    t = func_001F14E0(s);
    if (*(int *)(l + 0xC) == 0 && RANDOM() % 100 < t[6]) {
        order2(s);
        func_00271A10(PS2_ADDR(s), 0);
    } else {
        func_00204BB0(s);
        *(u32 *)(s + 0xBC) &= 0xFFF8003F;
        s[0x7D] = 1;
    }
}

/* 0x0027CCF0, 0x74 bytes. */
void func_0027CCF0(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_0027CC10(s);
    else if (st == 0)
        func_0027CAF0(s);
}

/* 0x0027D050, 0x14C bytes. Now and then a soldier drops a healing item (8 or 9) for its
 * commander below a quarter of its life (or 50). */
int func_0027D050(u8 *s, u8 *t)
{
    u8 *c;
    int lim;

    if (RANDOM() % 100 >= t[9] || *(short *)(s + 0xA4) != 0)
        return 0;
    c = SIDE_CMD(s);
    lim = *(short *)(c + 0x80) / 4;
    if (lim > 0x31)
        lim = 0x32;
    if (*(short *)(c + 0x82) >= lim)
        return 0;
    func_0024D380((RANDOM() & 1) == 0 ? 8 : 9, PS2_ADDR(*(u8 **)(s + 0x14)));
    func_00206080(s);
    return 1;
}

/* 0x0027D1A0, 0x114 bytes. A supply soldier's choice. */
void func_0027D1A0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (func_0027D050(s, t) != 0)
        return;
    if (RANDOM() % 100 < t[0])
        func_002B0180(s, 0);
    else if (RANDOM() % 100 < t[1])
        func_002B0180(s, 1);
    else if (RANDOM() % 100 < t[3])
        func_002AFC20(s);
    else
        func_00206080(s);
}

/* 0x0027D2C0, 0x74 bytes. */
void func_0027D2C0(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_002396B0(PS2_ADDR(s), 1);
    else if (st == 0)
        func_0027D1A0(s);
}

/* 0x0027DC00, 0x40 bytes, matching. */
int func_0027DC00(u8 *u, u8 *c)
{
    if (func_0027D6B0(u, c[0]) != 0)
        c[1]++;
    return 1;
}

/* 0x0027DC40, 0x48 bytes. Stage units of object 0x6E get flag 0x40. */
void func_0027DC40(u8 *u)
{
    if ((char)func_001FF100(*(u16 *)(u + 0x54), 10) == 'n')
        u[0x69] |= 0x40;
}

/* 0x0027DC90, 0x14C bytes. The same for the stage units in map cell `c` (once each). */
void func_0027DC90(u8 *c)
{
    u32 x0 = c[0] * 10 + 2, x1 = c[0] * 10 + 8, y = c[1] * 10 + 2, y1 = c[1] * 10 + 8;

    func_001185B0(g_700001E0, 0x50);
    for (; y < y1; y++) {
        u32 x;

        for (x = x0; (int)x < (int)x1; x++) {
            u32 *p;

            for (p = (u32 *)PS2_PTR(func_001945E0(0, x, y)); p != 0; p = (u32 *)p[1]) {
                u32 b = 1 << (*p & 7);

                if ((b & 0xFF & g_700001E0[*p >> 3]) == 0) {
                    g_700001E0[*p >> 3] |= b;
                    func_0027DC40(UNITS + *p * 0x70);
                }
            }
        }
    }
}

/* 0x0027DDE0, 0x68 bytes. The same for all stage units. */
void func_0027DDE0(void)
{
    u32 n = func_00196A10(), k;

    for (k = 0; k < n; k++)
        func_0027DC40(UNITS + k * 0x70);
}

/* 0x0027DEA0, 0xF0 bytes. The gate objects' state `v` (0: both kinds, 1: the map, 2: the stage
 * units of object 2). */
void func_0027DEA0(int k, int v)
{
    if (k == 1 || k == 0)
        func_00190060(v);
    if (k == 2 || k == 0) {
        u32 n = func_00196A10(), j;

        for (j = 0; j < n; j++) {
            u8 *u = UNITS + j * 0x70;

            if ((char)func_001FF100(*(u16 *)(u + 0x54), 10) == 2)
                func_0027D6B0(u, g_00440418[v & 0xFF]);
        }
    }
}

void func_0027B350(u32 t, u8 *s, u8 *cmd);

/* 0x0027AE70, 0x7C bytes. A healer soldier goes to its commander. */
void func_0027AE70(u8 *s)
{
    u8 *c = SIDE_CMD(s);

    func_0027B350(func_001F1360(s, 1), s, c);
}

/* 0x0027AEF0, 0x34 bytes. Soldier `s` takes order `k`. */
void func_0027AEF0(u8 *s, int k)
{
    order2(s);
    func_00271A10(PS2_ADDR(s), k);
}

/* 0x0027AF30, 0x114 bytes. A healer's choice (orders 0x1B-0x1D or going to its commander). */
void func_0027AF30(u8 *s, u8 *t)
{
    if (RANDOM() % 100 < t[0])
        func_0027AEF0(s, 0x1C);
    else if (RANDOM() % 100 < t[1])
        func_0027AEF0(s, 0x1D);
    else if (RANDOM() % 100 < t[2])
        func_0027AE70(s);
    else if (RANDOM() % 100 < t[3])
        func_0027AEF0(s, 0x1B);
    else
        func_0027AE70(s);
}

/* 0x0027B050, 0x158 bytes. Now and then a hurt soldier drops a healing item (0xC) for itself. */
int func_0027B050(u8 *s, u8 *t)
{
    float life, most;

    if (*(short *)(s + 0xA4) != 0)
        return 0;
    life = (float)*(short *)(s + 0x82);
    most = (float)*(short *)(s + 0x80);
    if (most < life * 2.0f)
        return 0;
    if (RANDOM() % 100 >= (u32)(int)(((50.0f - life / most * 100.0f) * 0.01f + 1.0f) * (float)t[9]))
        return 0;
    func_0024D380(0xC, PS2_ADDR(*(u8 **)(s + 0x14)));
    func_00206080(s);
    return 1;
}

/* 0x0027B1B0, 0x118 bytes. The healer's attack choice. */
void func_0027B1B0(u8 *s)
{
    u8 *t = func_001F14E0(s);

    if (func_0027B050(s, t) != 0)
        return;
    if (RANDOM() % 100 < t[0])
        func_002B0180(s, 0);
    else if (RANDOM() % 100 < t[3])
        func_0027AF30(s, t);
    else if (RANDOM() % 100 < t[1])
        func_002B0180(s, 1);
    else
        func_00206080(s);
}

/* 0x0027B2D0, 0x74 bytes. */
void func_0027B2D0(u8 *s)
{
    char st = s[0x7C];

    if (st == 3 || st == 2)
        func_00239780(s, 1);
    else if (st == 1)
        func_002396B0(PS2_ADDR(s), 1);
    else if (st == 0)
        func_0027B1B0(s);
}

/* The soldiers' basic orders (0x00204BB0-0x002054B8): soldiers here are battle officer records
 * (0xC0 bytes at 0x006A3A30) of foot soldiers; +0x04 the next in the group, +0x10 the unit,
 * +0x68 its officer table entry. */

extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each) */
extern u8 g_00669D60[];

void func_002A6D20(int k, int snd);

/* 0x00204BB0, 0x40 bytes. Soldier `s` turns towards its target point (+0x20), on the ground
 * plane (a VU0 vector subtraction in the original). */
void func_00204BB0(u8 *s)
{
    u8 *m = *(u8 **)(s + 0x14);
    float d[4];
    int k;

    for (k = 0; k < 4; k++)
        d[k] = ((float *)(s + 0x20))[k] - ((float *)(m + 0x40))[k];
    d[1] = 0.0f;
    func_001505B0(m, d);
}

/* 0x00204C50, 0x40 bytes. The same, turning away from it. */
void func_00204C50(u8 *s)
{
    u8 *m = *(u8 **)(s + 0x14);
    float d[4];
    int k;

    for (k = 0; k < 4; k++)
        d[k] = ((float *)(m + 0x40))[k] - ((float *)(s + 0x20))[k];
    d[1] = 0.0f;
    func_001505B0(m, d);
}

/* 0x00204C90, 0x1C bytes, matching. */
void func_00204C90(u8 *s, void *pos, u32 f)
{
    func_00150290(*(u8 **)(s + 0x14), pos, f);
}

/* 0x00204CB0, 0x1C bytes, matching. */
void func_00204CB0(u8 *s, const float *dir)
{
    func_001505B0(*(u8 **)(s + 0x14), dir);
}

/* 0x00204CD0, 0x28 bytes, matching. Soldier `s`'s attack flags. */
void func_00204CD0(u8 *s, u32 f)
{
    func_00150910(*(u8 **)(s + 0x14), f & 0x3FFF8000);
}

/* 0x00204D00, 0x20 bytes, matching. Its charge. */
void func_00204D00(u8 *s, int f)
{
    func_001508F0(*(u8 **)(s + 0x14), f & 0x7FFF);
}

/* 0x00204D20, 0x90 bytes, matching. Stops soldier `s`'s marching sounds. */
void func_00204D20(u8 *s)
{
    if ((*(u32 *)(s + 0xBC) & 0x40000000) != 0) {
        int k = (s - g_006A3A30[0]) / 0xC0;

        func_002A6770(k, 0x717);
        func_002A6770(k, 0x719);
        *(u32 *)(s + 0xBC) &= ~0x40000000;
    }
}

/* 0x00204DB0, 0xF0 bytes. Starts them (for the drum and horn soldiers, kinds 0x239-0x23B). */
void func_00204DB0(u8 *s, int alt)
{
    int k, o;

    if ((*(u32 *)(s + 0xBC) & 0x40000000) != 0)
        return;
    k = (s - g_006A3A30[0]) / 0xC0;
    o = (*(u8 **)(s + 0x68) - g_005BA6A0) / 0x2C;
    if (o == 0x23B || o == 0x23A)
        func_002A6D20(k, 0x717);
    else if (o == 0x239)
        func_002A6D20(k, alt == 0 ? 0x717 : 0x719);
    *(u32 *)(s + 0xBC) |= 0x40000000;
}

/* 0x00204EA0, 0xC8 bytes. Soldier `s`'s whole group stops and forgets its target. */
void func_00204EA0(u8 *s)
{
    u8 *p;

    if ((*(u32 *)(s + 0xB8) & 0x180) != 0)
        return;
    for (p = g_006A3A30[*(int *)(*(u8 **)(s + 0x10) + 0x14)]; p != 0; p = *(u8 **)(p + 4)) {
        u8 *a;

        *(u32 *)(p + 0xB8) &= 0xFFFF9FFF;
        *(u32 *)(p + 0xBC) &= 0xFFDEFFFF;
        func_00206080(p);
        a = *(u8 **)(p + 0x14);
        *(u32 *)(a + 0x13C) = 0;
        *(u32 *)(a + 0x1D0) = *(u32 *)0x700000C0;
        *(u32 *)(a + 0x1D4) = *(u32 *)0x700000C4;
        *(u32 *)(a + 0x1D8) = *(u32 *)0x700000C8;
        *(u32 *)(a + 0x1DC) = *(u32 *)0x700000CC;
    }
}

/* 0x002051A0, 0x4C bytes, matching. Soldier `s`'s formation slot (0x17 for none). */
u32 func_002051A0(u8 *s)
{
    if ((*(u32 *)(s + 0xB8) & 0x80) == 0 || (*(u32 *)(g_00669D60 + 0x200) & 0x4000000) != 0)
        return 0x17;
    return func_001F0520(*(u8 **)(s + 0x10));
}

/* 0x002051F0, 0x16C bytes. Soldier `s`'s guard chance (`hit`: when struck), less when hurt for
 * kind 0x10, a third for kinds below 8. */
int func_002051F0(u8 *s, int hit)
{
    u8 kind = (*(u8 **)(s + 0x68))[0x1C];
    u32 c;
    int v;

    if (kind == 2) {
        c = (hit != 0 ? 3 : 2) * (s[0x7B] + 2);
    } else {
        u8 *t = func_001F14E0(s);

        c = hit == 0 ? t[0xB] : t[0xC];
        if (kind == 0x10) {
            float life = (float)*(short *)(s + 0x82), most = (float)*(short *)(s + 0x80);

            if (life < most * 0.5f) {
                c -= (int)((float)c * ((50.0f - life / most * 100.0f) / 100.0f));
                if ((int)c < 1)
                    c = 0;
            }
        }
    }
    v = (int)(c * func_003E6D90()) / 100;
    if (kind < 8)
        v /= 3;
    return v;
}

/* 0x00205360, 0x120 bytes. Whether a hit of kind `k` (power `p`) on soldier `t` knocks it down
 * (`*down` set). */
int func_00205360(int a, int k, int p, u8 *o, u8 *t, int *down)
{
    u32 n;
    int lim;

    if ((*(u32 *)(t + 0xB8) & 0x846C) != 0)
        return 0;
    if ((*(u32 *)(t + 0xB8) & 0x80) != 0 && (*(u32 *)(*(u8 **)(t + 0x10) + 0x80) & 0x800) != 0)
        return 0;
    if (a == 2)
        return 1;
    if (k != 5 || p <= 0)
        return 0;
    n = g_00669D60[0x21] + 4;
    lim = *(short *)(o + 0x80) / 4;
    if (lim > 0x31)
        lim = 0x32;
    if (lim <= *(short *)(o + 0x82))
        n *= 2;
    n = n == 0 ? 0 : RANDOM() % n;
    if (n > (u32)(p - 1))
        return 0;
    *down = 1;
    return 1;
}

/* 0x00205480, 0x38 bytes. Whether soldier `s` is in a formation that holds. */
int func_00205480(u8 *s)
{
    if ((*(u32 *)(s + 0xB8) & 0x80) == 0)
        return 0;
    return (*(u32 *)(*(u8 **)(s + 0x10) + 0x84) & 0x800) != 0;
}

/* The soldiers' running orders (0x002018B0-0x00201F7C). */

int func_00271E70(u8 *s);
void func_00237B70(u8 *s);
void func_00201990(u8 *s);

/* Soldier `s`'s actor forgets its move target. */
static void stop_target(u8 *a)
{
    *(u32 *)(a + 0x13C) = 0;
    *(u32 *)(a + 0x1D0) = *(u32 *)0x700000C0;
    *(u32 *)(a + 0x1D4) = *(u32 *)0x700000C4;
    *(u32 *)(a + 0x1D8) = *(u32 *)0x700000C8;
    *(u32 *)(a + 0x1DC) = *(u32 *)0x700000CC;
}

/* 0x002018B0, 0x60 bytes. Order 0x10000 (wait): ends with its timer. */
void func_002018B0(u8 *s)
{
    if (*(short *)(s + 0x78) == 0) {
        *(u32 *)(s + 0xBC) &= ~0x10000;
        stop_target(*(u8 **)(s + 0x14));
    } else {
        func_00204C50(s);
    }
}

/* 0x00201910, 0x78 bytes. Order 0x4000 (follow): ends with its timer or its target. */
void func_00201910(u8 *s)
{
    u8 *a = *(u8 **)(s + 0x14);

    if (*(short *)(s + 0x78) == 0 || func_00271E70(s) == 0) {
        *(u32 *)(s + 0xBC) &= ~0x4000;
        *(u32 *)(s + 0x6C) = 0;
        *(int *)(s + 0x74) = -1;
        stop_target(a);
    }
}

/* 0x00201780, 0x124 bytes. Order 0x20000 (rest): a healing item at its end; called off when
 * struck. */
void func_00201780(u8 *s)
{
    u8 *a = *(u8 **)(s + 0x14);

    if ((*(u32 *)(*(u8 **)(a + 0x210) + 0x18) & 0x800) != 0) {
        *(u32 *)(s + 0xBC) &= ~0x20000;
        func_00253690(0xB, a);
        stop_target(a);
        order2(s);
        s[0x7D] = 0;
    } else if (*(short *)(s + 0x78) == 0 || *(short *)(s + 0x86) <= *(short *)(s + 0x88)) {
        *(u32 *)(s + 0xBC) &= ~0x20000;
        func_00253690(0xB, a);
        stop_target(a);
        func_0024D380((RANDOM() & 1) == 0 ? 8 : 9, PS2_ADDR(a));
    }
}

/* 0x00201C30, 0x70 bytes. Order 0x100: keeps pushing. */
void func_00201C30(u8 *s)
{
    func_00204B60(s, 0x20004);
    if (((*(u8 **)(s + 0x14))[0x19C] & 2) == 0) {
        *(u32 *)(s + 0xBC) &= ~0x100;
        stop_target(*(u8 **)(s + 0x14));
    }
}

/* 0x00201CA0, 0x88 bytes. Order 0x80: at its end (when the actor holds) fills its gauge and
 * pushes. */
void func_00201CA0(u8 *s)
{
    if (*(short *)(s + 0x78) != 0)
        return;
    if ((*(u32 *)(*(u8 **)(*(u8 **)(s + 0x14) + 0x210) + 0x18) & 0x400000) == 0) {
        *(u32 *)(s + 0xBC) &= ~0x80;
    } else {
        *(u32 *)(s + 0xBC) &= ~0x80;
        *(short *)(s + 0x88) = *(short *)(s + 0x86);
        func_00204B60(s, 0x20004);
        *(u32 *)(s + 0xBC) |= 0x100;
    }
}

/* 0x00201D30, 0xF4 bytes. Order 0x40 (charge up): turns into order 0x80 at its end; called off
 * when struck. */
void func_00201D30(u8 *s)
{
    u8 *a = *(u8 **)(s + 0x14);

    if ((*(u32 *)(*(u8 **)(a + 0x210) + 0x18) & 0x800) != 0) {
        *(u32 *)(s + 0xBC) &= ~0x40;
        func_00253690(0xB, a);
        stop_target(a);
        order2(s);
        s[0x7D] = 0;
    } else if (*(short *)(s + 0x78) == 0 || *(short *)(s + 0x86) <= *(short *)(s + 0x88)) {
        *(u32 *)(s + 0xBC) &= ~0x40;
        func_00253690(0xB, a);
        stop_target(a);
        *(u32 *)(s + 0xBC) |= 0x80;
        *(short *)(s + 0x78) = 1;
    }
}

/* 0x00201E30, 0x150 bytes. Steps soldier `s`'s running order (or waits without a target). */
void func_00201E30(u8 *s)
{
    u32 f = *(u32 *)(s + 0xBC);

    if ((f & 0x7FFC0) == 0) {
        if (*(int *)(*(u8 **)(*(u8 **)(s + 0x14) + 0x210) + 0x14) == 0)
            func_00206080(s);
    } else if ((f & 0x200) != 0) {
        func_00201990(s);
    } else if ((f & 0x4000) != 0) {
        func_00201910(s);
    } else if ((f & 0x10000) != 0) {
        func_002018B0(s);
    } else if ((f & 0x40) != 0) {
        func_00201D30(s);
    } else if ((f & 0x80) != 0) {
        func_00201CA0(s);
    } else if ((f & 0x100) != 0) {
        func_00201C30(s);
    } else if ((f & 0x8000) != 0) {
        func_00237B70(s);
    } else if ((f & 0x20000) != 0) {
        func_00201780(s);
    } else if ((f & 0x40000) != 0) {
        func_002015A0(s);
    }
}

/* More soldier steps (0x00202B00-0x00203FFC). */

int func_00202C50(u8 *s);
int func_002027F0(u8 *s);
void func_00201F80(u8 *s);
void func_00202F60(u8 *s);
void func_00203C70(u8 *s);
void func_00237200(u8 *s); void func_002E1820(u8 *s);
void func_00237550(u8 *s); void func_0023A0C0(u8 *s); void func_00239E60(u8 *s);
void func_00237410(u8 *s);
void func_002AFB80(u8 *s);
void func_002B31A0(u8 *s); void func_002B27F0(u8 *s);

/* 0x00202B00, 0x14C bytes. Whether soldier `s` counters its attacker (by the difficulty). */
int func_00202B00(u8 *s)
{
    u8 *a = *(u8 **)(s + 0x14), *st = *(u8 **)(a + 0x210), *o;

    if (2.0f <= *(float *)(a + 0x23C) || (st != 0 && (*(u32 *)(st + 0x18) & 0x10) != 0))
        return 0;
    if (*(u8 **)(a + 0x214) != 0 && (*(u32 *)(*(u8 **)(a + 0x214) + 0x18) & 0x10) == 0)
        return 0;
    if ((*(u32 *)(s + 0xBC) & 0x80000) == 0)
        return 0;
    o = *(u8 **)(s + 8);
    if (o == 0 || (*(u32 *)(o + 0xB8) & 0xC) == 0)
        return 0;
    if ((*(u8 **)(s + 0x10))[0x79] == (*(u8 **)(o + 0x10))[0x79])
        return 0;
    if ((*(u32 *)(st + 0x18) & 4) == 0)
        return 0;
    if (RANDOM() % 100 >= (u32)(g_00669D60[0x21] + 1) * 0x14)
        return 0;
    func_00201F80(s);
    return 1;
}

/* 0x00202EB0, 0x8C bytes, matching. Soldier `s`'s reactions in turn; whether one took it. */
int func_00202EB0(u8 *s)
{
    if (func_00202C50(s) != 0)
        return 1;
    if ((*(u32 *)(g_00669D60 + 0x200) & 8) == 0 || (*(u32 *)(s + 0xB8) & 0x10) != 0) {
        if (func_00202B00(s) != 0)
            return 1;
        if (func_002027F0(s) != 0)
            return 1;
    }
    return 0;
}

/* 0x00202F40, 0x20 bytes, matching. */
int func_00202F40(u8 *s)
{
    return func_00202C50(s) != 0;
}

/* 0x002034F0, 0x10C bytes. Order 4 (keep running) while the actor runs; a new run length of
 * 80-175 frames over the soldier's rank each time it ends. */
void func_002034F0(u8 *s)
{
    if ((*(u32 *)(*(u8 **)(*(u8 **)(s + 0x14) + 0x210) + 0x18) & 0x200000) == 0) {
        order2(s);
        s[0x7D] = 0;
    } else if (*(short *)(s + 0x78) == 0) {
        u32 n = ((RANDOM() % 0x14) * 5 + 0x50) / (s[0x7B] + 1);

        if (n == 0) {
            *(short *)(s + 0x78) = 0;
        } else {
            n = n * 0x32 / 0x3C;
            *(short *)(s + 0x78) = n == 0 ? 1 : n;
        }
        func_00204D00(s, 0x783F);
    }
}

/* 0x00203600, 0x5C bytes. Order 3 (keep walking) while the actor walks. */
void func_00203600(u8 *s)
{
    if ((*(u32 *)(*(u8 **)(*(u8 **)(s + 0x14) + 0x210) + 0x18) & 0x40) == 0) {
        order2(s);
        s[0x7D] = 0;
    } else if (*(short *)(s + 0x78) == 0) {
        func_00204D00(s, 0x783F);
    }
}

/* 0x00203660, 0x88 bytes. Steps soldier `s`'s order 3-6. */
void func_00203660(u8 *s)
{
    char o = s[0x7D];

    if (o == 6)
        func_00202F60(s);
    else if (o == 5)
        func_002032F0(s);
    else if (o == 4)
        func_002034F0(s);
    else if (o == 3)
        func_00203600(s);
}

/* 0x002036F0, 0xD8 bytes. Soldier `s`'s timed boosts run out (+0xA4: attack 0x8000000, defence
 * 0x10000000, 0x20000000). */
void func_002036F0(u8 *s)
{
    u32 f;

    if (*(short *)(s + 0xA4) != 0)
        (*(short *)(s + 0xA4))--;
    f = *(u32 *)(s + 0xBC);
    if ((f & 0x8000000) != 0) {
        if (*(short *)(s + 0xA4) == 0) {
            *(float *)(s + 0x98) = 1.0f;
            *(u32 *)(s + 0xBC) &= 0xF7FFFFFF;
        }
    } else if ((f & 0x10000000) != 0) {
        if (*(short *)(s + 0xA4) == 0) {
            *(float *)(s + 0x9C) = 1.0f;
            *(u32 *)(s + 0xBC) &= 0xEFFFFFFF;
        }
    } else if ((f & 0x20000000) != 0 && *(short *)(s + 0xA4) == 0) {
        s[0xA9] = 0;
        *(u32 *)(s + 0xBC) &= 0xDFFFFFFF;
    }
}

/* 0x002037D0, 0x15C bytes, matching. Soldier `s`'s choice by its kind. */
void func_002037D0(u8 *s)
{
    switch ((*(u8 **)(s + 0x68))[0x1C]) {
    case 0: func_002398A0(s); break;
    case 1: func_00237200(s); break;
    case 2: func_002E1820(s); break;
    case 3: func_00237550(s); break;
    case 4: func_0023A0C0(s); break;
    case 5: func_00239E60(s); break;
    case 6: func_00238570(s); break;
    case 7: func_00237410(s); break;
    case 8: func_002B0980(s); break;
    case 9: func_002B1350(s); break;
    case 10: func_002AFB80(s); break;
    case 0xB: func_002B0E40(s); break;
    case 0xC: func_0027D2C0(s); break;
    case 0xD: func_0027B2D0(s); break;
    case 0xE: func_0027B970(s); break;
    case 0xF: func_0027BAF0(s); break;
    case 0x10: func_0027CCF0(s); break;
    case 0x11: func_0027C610(s); break;
    }
}

/* 0x00203930, 0xBC bytes, matching. The special soldiers' step by their officer's kind bits. */
void func_00203930(u8 *s)
{
    u32 f = *(u32 *)(*(u8 **)(s + 0x68) + 0x28);

    if ((f & 4) != 0)
        func_002B3820(s);
    else if ((f & 8) != 0)
        func_002B3C30(s);
    else if ((f & 0x10) != 0)
        func_002B18D0(s);
    else if ((f & 0x20) != 0)
        func_002B1F90(s);
    else if ((f & 0x40) != 0)
        func_002B27F0(s);
    else if ((f & 0x80) != 0)
        func_002B31A0(s);
}

/* 0x00203F90, 0x70 bytes. */
void func_00203F90(u8 *s)
{
    u32 f = *(u32 *)(g_00669D60 + 0x200);

    if ((f & 0x10) != 0)
        func_00203C70(s);
    else if ((f & 8) != 0 && (f & 0x4000000) != 0)
        stop_target(*(u8 **)(s + 0x14));
}

/* Target distances (0x00206480-0x00206DE8). */

/* The squared ground distance between actors `a` and `b` (?: the VU0 code uses x and z). */
static float dist2(u8 *a, u8 *b)
{
    float dx = *(float *)(b + 0x40) - *(float *)(a + 0x40);
    float dz = *(float *)(b + 0x48) - *(float *)(a + 0x48);

    return dx * dx + dz * dz;
}

/* 0x00206480, 0x108 bytes. Soldier `s`'s stance toward its target by distance (3 when the target
 * is a friend; `far` doubles the distance). */
void func_00206480(u8 *s, u8 *t, int far)
{
    u8 *o = *(u8 **)(s + 8);
    float d, lim[4];
    u32 k;

    if (o == 0)
        return;
    if ((*(u8 **)(s + 0x10))[0x79] == (*(u8 **)(o + 0x10))[0x79]) {
        s[0x7C] = 3;
        return;
    }
    d = dist2(*(u8 **)(s + 0x14), *(u8 **)(o + 0x14));
    if (far != 0)
        d *= 2.0f;
    func_001F1470(s, PS2_ADDR(t), *(u32 *)(o + 0xB8) & 0x8000, lim);
    for (k = 0; k < 3; k++) {
        if (d < lim[k])
            break;
    }
    s[0x7C] = k;
}

/* 0x00206B80, 0xE4 bytes. Whether soldier `s`'s target is a live one it can reach (its group
 * active and not in state 3, the target not in the way of kind 2). */
int func_00206B80(u8 *s)
{
    u8 *o = *(u8 **)(s + 8), *g;

    if (o == 0 || (*(u32 *)(o + 0xB8) & 1) == 0 || (*(u32 *)(o + 0xB8) & 2) != 0)
        return 0;
    g = *(u8 **)(*(u8 **)(s + 0x10) + 0x18);
    if (g == 0 || (*(u32 *)(g + 0x80) & 1) == 0 || (*(u32 *)(g + 0x80) & 0x8C40002) != 0)
        return 0;
    if (g[0x7A] == 3)
        return 0;
    return func_00190610(*(u8 **)(o + 0x14) + 0x40, 2) == 0;
}

/* 0x00206C70, 0x178 bytes. Whether soldier `s`'s target is within its reach (by its kind and
 * order). */
int func_00206C70(u8 *s)
{
    u32 f = *(u32 *)(s + 0xB8);
    float r;

    if ((*(u32 *)(g_00669D60 + 0x200) & 8) != 0) {
        r = 22500.0f;
    } else if ((f & 0x60) != 0) {
        r = (*(u32 *)(s + 0xBC) & 0x2000000) == 0 ? 90000.0f : (float)func_001F1360(s, 0);
    } else if ((f & 0x400) != 0) {
        r = (*(u32 *)(s + 0xBC) & 0x1000000) == 0 ? 160000.0f : 640000.0f;
    } else if (*(int *)(s + 0xC) != 0) {
        r = 360000.0f;
    } else {
        r = (f & 0x8000) == 0 ? 90000.0f : 10000.0f;
    }
    return dist2(*(u8 **)(s + 0x14), *(u8 **)(*(u8 **)(s + 8) + 0x14)) < r;
}
