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

u8 *func_001F14E0(void);
void func_00204D00(u8 *s, int a);
void func_00236DD0(u8 *s);
int func_00236F30(u8 *s);
void func_00236ED0(u8 *s);
void func_00206080(u8 *s);
void func_00239780(u8 *s, int a);
void func_002396B0(u8 *s);
void func_002B0180(u8 *s, int a);
void func_002AFC20(u8 *s);
void func_00204B60(u8 *s, u32 f);
void func_00271A10(u8 *s, int a);
void func_00238AE0(u8 *s, int t);
void func_00204BB0(u8 *s);
void func_0024D380(int kind, u8 *a);
u32 func_001FF100(u16 v, int k);
void func_001185B0(void *p, int n);
u32 *func_001945E0(int a, u32 x, u32 y);
u32 func_00196A10(void);
void func_00190060(int v);
int func_0027D6B0(u8 *u, int v);
void func_0027D960(void);
void func_00239830(u8 *s);

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
    u8 *t = func_001F14E0();

    order2(s);
    if (RANDOM() % 100 < t[1])
        func_00204D00(s, 0);
    else
        func_00204D00(s, 1);
}

/* 0x0027B6B0, 0x7C bytes. */
void func_0027B6B0(u8 *s)
{
    u8 *t = func_001F14E0();

    if (RANDOM() % 100 < t[3])
        func_00236DD0(s);
    else
        func_0027B730(s);
}

/* 0x0027B730, 0x238 bytes. Soldier `s` with a target: charges by chance (more when its side's
 * commander is hurt; half for some weapon kinds). */
void func_0027B730(u8 *s)
{
    u8 *t = func_001F14E0(), *a, *m;
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
    u8 *t = func_001F14E0();

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
        func_002396B0(s);
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
    t = func_001F14E0();
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
    func_00271A10(s, 7);
}

/* 0x0027C460, 0xF0 bytes. A spearman's choice: thrust, attack, close in or wait. */
void func_0027C460(u8 *s)
{
    u8 *t = func_001F14E0();

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
    u8 *t = func_001F14E0();

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
    u8 *t = func_001F14E0();

    if (RANDOM() % 100 < t[4]) {
        order2(s);
        func_00271A10(s, 0);
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
    u8 *t = func_001F14E0();

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
    t = func_001F14E0();
    if (*(int *)(l + 0xC) == 0 && RANDOM() % 100 < t[6]) {
        order2(s);
        func_00271A10(s, 0);
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
    func_0024D380((RANDOM() & 1) == 0 ? 8 : 9, *(u8 **)(s + 0x14));
    func_00206080(s);
    return 1;
}

/* 0x0027D1A0, 0x114 bytes. A supply soldier's choice. */
void func_0027D1A0(u8 *s)
{
    u8 *t = func_001F14E0();

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
        func_002396B0(s);
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

            for (p = func_001945E0(0, x, y); p != 0; p = (u32 *)p[1]) {
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

u32 func_001F1360(u8 *s, int a);
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
    func_00271A10(s, k);
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
    func_0024D380(0xC, *(u8 **)(s + 0x14));
    func_00206080(s);
    return 1;
}

/* 0x0027B1B0, 0x118 bytes. The healer's attack choice. */
void func_0027B1B0(u8 *s)
{
    u8 *t = func_001F14E0();

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
        func_002396B0(s);
    else if (st == 0)
        func_0027B1B0(s);
}
