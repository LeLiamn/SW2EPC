/*
 * emp_cmd_misc.c - Empire mode: small state machines of the command screens and helpers about
 * officers, forces and regions. Original file name unknown (0x003C0060-).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Officers are 0-0x19E, forces 0-func_0030AB90().
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

extern u32 g_007BEAD4;
extern int g_0045D818[2];                /* (small data) a step and a value */
extern int g_0045D81C;
extern int g_0045D894, g_0045D898, g_0045D89C, g_0045D8A0;   /* (small data) scene history */
extern int g_0045D820;
extern u8 g_0069395E;
extern u32 g_007BEBB0[6];

u8 *func_002FC2C0(void);
void func_003A9070(int a);
void func_002DB570(int a);
int func_002DB750(void);
void func_002DB700(void);
void func_002FC560(void);
void func_002FC660(void);
int func_00327E20(void);
void func_0030E090(int k);
void func_002FC2D0(void);
void func_002FC630(void);
int func_0017DDA0(void);
void func_0017DF10(void);
void func_001B8F60(int a, int b, int c);
int func_002F2840(u32 o);
int func_002F34E0(u32 o);
int func_002F33F0(u32 o);
int func_0030C7F0(int a, int k);
u8 *func_003B5E90(void);
u32 func_00337A10(int x);
void func_0032E8A0(int k, u32 o);
u32 func_002F9550(void);
int func_002FB2D0(int a);
void func_0030BBD0(int a, int b);
int func_0030B3B0(u8 *out);
void func_0030B330(void);
int func_003C1850(void);
int func_0030AB90(void);
int func_002F9C90(int f, int g);
int func_00327820(void);
int func_00327AE0(int k);
int func_00327870(void);
int func_0032EB40(int a, int b, int c);
int func_0030AFF0(int r);
int func_002F3BB0(int o);
int func_002F4080(int o);
int func_002F5CC0(int o);
int func_002F3E30(int o);
int func_002F3770(int o);

int func_003C0830(u32 o);
int func_003C0C60(int f, int g);

/* 0x003C0060, 0xC bytes. */
u32 func_003C0060(void)
{
    return g_007BEAD4;
}

/* 0x003C0070, 8 bytes, matching. */
int *func_003C0070(void)
{
    return g_0045D818;
}

/* 0x003C0080, 0xC bytes, matching. Resets a step pair. */
void func_003C0080(int *p)
{
    p[0] = 0;
    p[1] = 0;
}

/* 0x003C0090, 0x3C bytes, matching. Step 0: starts fade 6. */
void func_003C0090(void)
{
    int *st = *(int **)(func_002FC2C0() + 0x6BC);

    func_003A9070(1);
    func_002DB570(6);
    *st = 1;
}

/* 0x003C00D0, 0x38 bytes, matching. Step 1: waits for the fade. */
void func_003C00D0(void)
{
    int *st = *(int **)(func_002FC2C0() + 0x6BC);

    if (func_002DB750() == 0)
        *st = 2;
}

/* 0x003C0110, 0x40 bytes, matching. Step 2 (first kind). */
void func_003C0110(void)
{
    int *p = (int *)func_002FC2C0();

    func_003C0080((int *)p[0x1AF]);
    func_002FC560();
    func_003A9070(0);
    *p = 0;
}

/* 0x003C0150, 0x40 bytes, matching. Step 2 (second kind). */
void func_003C0150(void)
{
    int *p = (int *)func_002FC2C0();

    func_003C0080((int *)p[0x1AF]);
    func_002FC660();
    func_003A9070(0);
    *p = 0;
}

/* 0x003C0190, 0x40 bytes. */
void func_003C0190(void)
{
    if (**(int **)(func_002FC2C0() + 0x6BC) == 1)
        func_002DB700();
}

/* 0x003C01D0, 0x78 bytes. */
int func_003C01D0(void)
{
    int k = **(int **)(func_002FC2C0() + 0x6BC);

    if (k == 2)
        func_003C0110();
    else if (k == 1)
        func_003C00D0();
    else if (k == 0)
        func_003C0090();
    return 5;
}

/* 0x003C0250, 0x40 bytes. */
void func_003C0250(void)
{
    if (**(int **)(func_002FC2C0() + 0x6BC) == 1)
        func_002DB700();
}

/* 0x003C0290, 0x78 bytes. */
int func_003C0290(void)
{
    int k = **(int **)(func_002FC2C0() + 0x6BC);

    if (k == 2)
        func_003C0150();
    else if (k == 1)
        func_003C00D0();
    else if (k == 0)
        func_003C0090();
    return 5;
}

/* 0x003C0310, 0x24 bytes, matching. */
void func_003C0310(void)
{
    func_002DB570(5);
    g_0045D818[0] = 1;
}

/* 0x003C0340, 0x34 bytes. */
void func_003C0340(void)
{
    if (func_002DB750() == 0)
        g_0045D818[0] = 2;
}

/* Pushes `next` into the scene history. */
static void push_scene(void)
{
    if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D8A0;
        g_0045D89C = 0x18;
    } else {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D89C;
        g_0045D89C = g_0045D8A0;
    }
}

/* 0x003C0380, 0x244 bytes. Leaves for the next scene (by func_00327E20's mode). */
void func_003C0380(void)
{
    int m = func_00327E20();

    if (g_0045D81C == 0) {
        if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
            g_0045D89C = 1;
    } else if (m == 0) {
        func_0030E090(0x10);
        func_002FC2D0();
        if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
            g_0045D89C = 0x12;
    } else if (m == 1) {
        func_0030E090(0x15);
        func_002FC630();
        if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
            g_0045D89C = 0x12;
    } else if (m == 2) {
        func_0030E090(0x1F);
        if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
            g_0045D89C = 0x12;
    }
    push_scene();
    func_003C0080(g_0045D818);
}

/* 0x003C05D0, 0x34 bytes. */
void func_003C05D0(void)
{
    if (g_0045D818[0] == 1)
        func_002DB700();
}

/* 0x003C0610, 0x10C bytes. The leaving steps: fade, wait, then the next scene. */
int func_003C0610(void)
{
    int r = 5;

    if (g_0045D818[0] == 4) {
        func_003C0380();
        r = 0;
    } else if (g_0045D818[0] == 3) {
        int busy = g_0069395E != 0 && g_0069395E != 0xFF;

        if (!busy && func_0017DDA0() == 0)
            g_0045D818[0] = 4;
    } else if (g_0045D818[0] == 2) {
        func_0017DF10();
        func_001B8F60(0, 6, 8);
        g_0045D818[0] = 3;
    } else if (g_0045D818[0] == 1) {
        func_003C0340();
    } else if (g_0045D818[0] == 0) {
        func_003C0310();
    }
    return r;
}

/* 0x003C0720, 8 bytes, matching. */
int func_003C0720(void)
{
    return g_0045D820;
}

/* 0x003C0730, 0x38 bytes, matching. */
void func_003C0730(void)
{
    g_007BEBB0[0] = 0x19F;
    g_007BEBB0[1] = 0x19F;
    g_007BEBB0[2] = 0x19F;
    g_007BEBB0[3] = 0x19F;
    g_007BEBB0[4] = 0x19F;
    g_007BEBB0[5] = 0x19F;
}

/* 0x003C0770, 0x1C bytes, matching. */
void func_003C0770(void)
{
    func_003C0730();
}

/* 0x003C0790, 0x40 bytes. */
int func_003C0790(u32 o)
{
    if (o >= 0x19F)
        return 0;
    return func_002F2840(o) != 0;
}

/* 0x003C07D0, 0x5C bytes. Officer `o`'s rank from its merit (-1 for none). */
int func_003C07D0(u32 o)
{
    if (o >= 0x19F)
        return -1;
    return func_002F34E0(o) / 10000 + 2;
}

/* 0x003C0830, 0x60 bytes. Whether officer `o` may rise. */
int func_003C0830(u32 o)
{
    if (o >= 0x19F)
        return 0;
    return func_003C07D0(o) <= func_002F33F0(o);
}

/* 0x003C0890, 0x6C bytes. */
int func_003C0890(int a)
{
    int n = 0, k;

    for (k = 0; k < 8; k++) {
        if (func_0030C7F0(a, k) != 0)
            n++;
    }
    return n;
}

/* 0x003C0900, 0xB0 bytes. The four officers of the screen (defaults 0x28, 0x2E, 0x151, 0x29). */
void func_003C0900(void)
{
    u8 *p = func_003B5E90();
    u32 t[4], *q = t;
    int k;

    t[0] = func_00337A10(0x28);
    t[1] = func_00337A10(0x2E);
    t[2] = func_00337A10(0x151);
    t[3] = func_00337A10(0x29);
    for (k = 0; k < 4; k++, p += 4, q++) {
        if (*(u32 *)(p + 0x72C) < 0x19F)
            *q = *(u32 *)(p + 0x72C);
        func_0032E8A0(k, *q);
    }
}

/* 0x003C09B0, 0x2AC bytes. The rank force `f` may take (by its size and holdings). */
int func_003C09B0(int f)
{
    u8 buf[112];
    u32 v = func_002F9550();
    int n, r;

    func_0030BBD0(func_002FB2D0(f), 1);
    n = func_0030B3B0(buf);
    func_0030B330();
    if (func_003C1850() == 0 && v > 0x37 && v < 0x40 && func_003C0890(f) > 6)
        return 0x40;
    if (func_003C1850() == 0 && v > 0x2F && v < 0x38 && func_003C0890(f) > 5)
        return 0x38;
    if (func_003C1850() == 0 && v > 0x27 && v < 0x30 && func_003C0890(f) > 4)
        return 0x30;
    if (func_003C1850() == 0 && v > 0x1F && v < 0x28 && func_003C0890(f) > 3)
        return 0x28;
    if (func_003C1850() == 0 && v > 0x15 && v < 0x20 && func_003C0890(f) > 2)
        return 0x20;
    if (func_003C1850() == 0 && v > 0xB && v < 0x16 && func_003C0890(f) > 1)
        return 0x16;
    if (func_003C1850() == 0 && v < 0xC && func_003C0890(f) > 1 && n > 2)
        return 0xC;
    if (v != 100)
        return 0;
    if (func_003C1850() == 0) {
        if (func_003C0890(f) > 0)
            return 0;
    } else if (n > 2) {
        return 0;
    }
    r = 100;
    return r;
}

/* 0x003C0C60, 0xBC bytes. Whether forces `f` and `g` are allied (relation 1-3). */
int func_003C0C60(int f, int g)
{
    int r;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    if (g < 0 || g >= func_0030AB90())
        return 0;
    r = func_002F9C90(f, g);
    return r == 3 || r == 2 || r == 1;
}

/* 0x003C0D20, 0x214 bytes. An officer for the player's ruler: one of the five set ones if
 * possible, else the one with the most merit who may rise, else the first possible (0x29 for
 * none). */
int func_003C0D20(int skip)
{
    int me = func_00327820(), best = -1, top = -1, k;
    int a = func_00327AE0(0), b = func_00327AE0(1), c = func_00327AE0(2), d = func_00327AE0(3);
    int e = func_00327870();

    for (k = 0; k < 0x19F; k++) {
        if (k == me || k == skip || func_0032EB40(me, k, 0) == 0)
            continue;
        if (k == a || k == b || k == c || k == d || k == e)
            return k;
        if (func_003C0830(k) != 0) {
            int m = func_002F34E0(k);

            if (top < m) {
                best = k;
                top = m;
            }
        }
    }
    if (best == -1) {
        for (k = 0; k < 0x19F; k++) {
            if (k != me && k != skip && func_0032EB40(me, k, 0) != 0) {
                best = k;
                break;
            }
        }
    }
    if (best == -1)
        best = func_00337A10(0x29);
    return best;
}

/* 0x003C0F40, 0x9C bytes. Whether regions `a` and `b` have the same owner. */
int func_003C0F40(int a, int b)
{
    if (a < 0 || a >= func_0030AB90() || b < 0 || b >= func_0030AB90())
        return 0;
    return func_0030AFF0(a) == func_0030AFF0(b);
}

/* 0x003C0FE0, 0x9C bytes. Whether force `f` is at war (relation 3) with region `r`'s owner. */
int func_003C0FE0(int f, int r)
{
    if (f < 0 || f >= func_0030AB90() || r < 0 || r >= func_0030AB90())
        return 0;
    return func_002F9C90(f, func_0030AFF0(r)) == 3;
}

/* 0x003C1080, 0xA0 bytes. Whether regions `a` and `b`'s owners are allied. */
int func_003C1080(int a, int b)
{
    if (a < 0 || a >= func_0030AB90() || b < 0 || b >= func_0030AB90())
        return 0;
    return func_003C0C60(func_0030AFF0(a), func_0030AFF0(b));
}

/* 0x003C1120, 0xDC bytes. Whether officer `o` serves a force allied to the player's. */
int func_003C1120(u32 o)
{
    int me, f;

    if (o >= 0x19F || func_002F3BB0(o) == 0 || func_002F3BB0(o) == 3)
        return 0;
    if (func_002F4080(o) >= 0x19)
        return 0;
    me = func_00327820();
    f = func_002F4080(me);
    if (o == (u32)me)
        return 0;
    return func_003C0C60(f, func_002F4080(o));
}

/* Officers of region `r`'s owner placed in `r`, of rank kind `kind`, with at least `v`. */
static int count_officers(int r, int v, int kind)
{
    int n = 0, f, k;

    if (r < 0 || r >= func_0030AB90())
        return 0;
    f = func_0030AFF0(r);
    for (k = 0; k < 0x19F; k++) {
        if (func_002F3BB0(k) != 0 && func_002F3BB0(k) != 3 && f == func_002F4080(k)
            && r == func_002F5CC0(k) && func_002F3E30(k) == kind && v <= func_002F3770(k))
            n++;
    }
    return n;
}

/* 0x003C1200, 0x124 bytes. */
int func_003C1200(int r, int v)
{
    return count_officers(r, v, 2);
}

/* 0x003C1330, 0x124 bytes. */
int func_003C1330(int r, int v)
{
    return count_officers(r, v, 1);
}

extern int g_007BEBD0[0x19];             /* a force's connected regions (0x19 ends the list) */

int func_00327C00(void);
int func_00329160(int k, int *a, int *b);
int func_002F8F20(int f);
int func_0030AD20(int r, int k);
int func_0030B240(int r, int k);
int func_0030C280(int a, int b);
int func_002FA790(int f);

/* 0x003C1460, 0x114 bytes. Force `f`'s officers of rank kind `kind` with at least `v`. */
int func_003C1460(int kind, int f, int v)
{
    int n = 0;
    u32 k;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    for (k = 0; (int)k < 0x19F; k++) {
        if (k < 0x19F && func_002F3BB0(k) != 0 && func_002F3BB0(k) != 3 && f == func_002F4080(k)
            && kind == func_002F3E30(k) && v <= func_002F3770(k))
            n++;
    }
    return n;
}

/* 0x003C1580, 0x164 bytes. The same leaving out four officers. */
int func_003C1580(int kind, int f, int v, u32 x1, u32 x2, u32 x3, u32 x4)
{
    int n = 0;
    u32 k;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    for (k = 0; (int)k < 0x19F; k++) {
        if (k < 0x19F && func_002F3BB0(k) != 0 && func_002F3BB0(k) != 3 && f == func_002F4080(k)
            && kind == func_002F3E30(k) && v <= func_002F3770(k) && k != x1 && k != x2 && k != x3
            && k != x4)
            n++;
    }
    return n;
}

/* 0x003C16F0, 0x158 bytes. The same for `f` and its allies. */
int func_003C16F0(int kind, int f, int v)
{
    int n = 0;
    u32 k;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    for (k = 0; (int)k < 0x19F; k++) {
        int g = func_002F4080(k);

        if (g >= 0 && g < func_0030AB90() && k < 0x19F && func_002F3BB0(k) != 0
            && func_002F3BB0(k) != 3 && (func_003C0C60(f, g) != 0 || f == g)
            && kind == func_002F3E30(k) && v <= func_002F3770(k))
            n++;
    }
    return n;
}

/* 0x003C1850, 0x50 bytes, matching. Whether the game mode is 0-5. */
int func_003C1850(void)
{
    switch (func_00327C00()) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return 1;
    default:
        return 0;
    }
}

/* 0x003C18A0, 0xE4 bytes. Whether one of the 12 pending moves goes from region `a` to `b`. */
int func_003C18A0(int a, int b)
{
    int x = 0x19, y = 0x19, k;

    if (a < 0 || a >= func_0030AB90() || b < 0 || b >= func_0030AB90())
        return 0;
    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &x, &y) != 0 && a == x && b == y)
            return 1;
    }
    return 0;
}

/* 0x003C1990, 0x3C bytes. */
void func_003C1990(void)
{
    int k;

    for (k = 0; k < 0x19; k++)
        g_007BEBD0[k] = 0x19;
}

/* 0x003C19D0, 0x1A0 bytes. Force `f`'s regions linked to its ruler's region. */
void func_003C19D0(int f)
{
    int home = func_002F5CC0(func_002F8F20(f)), n = 1, i = 0;

    func_003C1990();
    g_007BEBD0[0] = home;
    do {
        int r = g_007BEBD0[i++], j;

        for (j = 0; j < 6; j++) {
            int x = func_0030AD20(r, j), o, seen = 0, k;

            if (x < 0 || x >= func_0030AB90())
                continue;
            o = func_0030AFF0(x);
            if (o < 0 || o >= func_0030AB90() || x == home || o != f)
                continue;
            for (k = 0; k < n; k++) {
                if (x == g_007BEBD0[k])
                    seen = 1;
            }
            if (!seen)
                g_007BEBD0[n++] = x;
        }
    } while (i != n);
}

/* 0x003C1B70, 0x4C bytes. Whether region `r` is in that list. */
int func_003C1B70(int r)
{
    int *p = g_007BEBD0;

    if (*p == 0x19)
        return 0;
    do {
        if (r == *p)
            return 1;
        p++;
    } while (*p != 0x19);
    return 0;
}

/* 0x003C1BC0, 0x304 bytes. Whether force `f` reaches region `b` from region `a` through regions
 * of forces it is at war with. */
int func_003C1BC0(int f, int a, int b)
{
    int t[28], n = 1, i = 0, k;

    if (f < 0 || f >= func_0030AB90() || a < 0 || a >= func_0030AB90() || b < 0
        || b >= func_0030AB90() || a == b)
        return 0;
    {
        int o = func_0030AFF0(b);

        if (f == o || func_003C0C60(f, o) != 0 || func_0030B240(a, 3) == 2 || func_0030B240(b, 3) == 2)
            return 0;
    }
    for (k = 0; k < 0x19; k++)
        t[k] = 0x19;
    t[0] = a;
    do {
        int r = t[i++], j;

        for (j = 0; j < 6; j++) {
            int x = func_0030AD20(r, j), seen = 0;

            if (x < 0 || x >= func_0030AB90() || x == a || func_0030B240(x, 3) == 2
                || func_003C0FE0(f, x) == 0)
                continue;
            for (k = 0; k < n; k++) {
                if (x == t[k])
                    seen = 1;
            }
            if (!seen)
                t[n++] = x;
        }
    } while (i != n);
    for (k = 1; k < n; k++) {
        if (func_0030C280(t[k], b) != 0)
            return 1;
    }
    return 0;
}

/* 0x003C1ED0, 0x1B8 bytes. Whether region `a`'s owner may attack region `b` from it. */
int func_003C1ED0(int a, int b)
{
    int f = func_0030AFF0(a), reach;

    func_003C19D0(f);
    reach = func_003C1B70(a) != 0 ? func_003C1BC0(f, a, b) : 0;
    if (a < 0 || a >= func_0030AB90() || b < 0 || b >= func_0030AB90())
        return 0;
    if (func_0030B240(a, 3) == 2 || func_0030B240(b, 3) == 2)
        return 0;
    if (func_003C0F40(a, b) != 0 || func_003C1200(a, 0) == 0)
        return 0;
    if (func_003C18A0(b, a) != 0 || func_003C1080(a, b) != 0)
        return 0;
    if (func_002FA790(f) == 0 && func_0030C280(a, b) == 0 && reach == 0)
        return 0;
    return 1;
}

int func_00327D50(void);
int func_002FB3B0(int f);
int func_00329870(void);
int func_003635F0(void);
int func_0036B260(void);
u16 func_003620E0(int s, int k);
int func_0030D370(void);
int func_002F9260(int f);
int func_0032EB00(void);
int func_002F27D0(int v);
int func_0032F7D0(int v);
u8 func_00362570(void);

/* 0x003C2090, 0xE8 bytes. Whether force `f` may attack region `b` from one of its regions. */
int func_003C2090(int f, int b)
{
    int n = func_0030AB90(), r;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    for (r = 0; r < n; r++) {
        if (r >= 0 && r < func_0030AB90() && f == func_0030AFF0(r) && func_003C1ED0(r, b) != 0)
            return 1;
    }
    return 0;
}

/* 0x003C2180, 0x190 bytes. How many regions the player's force may attack. */
int func_003C2180(void)
{
    int n = func_0030AB90(), f = func_00327D50(), own = func_002FB3B0(f), t[28], c = 0, k, j;
    int *p = t;

    for (k = 0; k < 0x19; k++)
        t[k] = n;
    for (k = 0; k < n; k++) {
        if (k >= 0 && k < func_0030AB90() && f == func_0030AFF0(k))
            *p++ = k;
    }
    for (k = 0; k < n; k++) {
        if (k < 0 || k >= func_0030AB90() || f == func_0030AFF0(k))
            continue;
        for (j = 0; j < own; j++) {
            if (func_003C1ED0(t[j], k) != 0) {
                c++;
                break;
            }
        }
    }
    return c;
}

/* 0x003C2320, 0x3C bytes, matching. */
int func_003C2320(void)
{
    if (func_00329870() == 0)
        return 0;
    return func_003635F0() == 0;
}

/* 0x003C2360, 0x38 bytes, matching. */
int func_003C2360(void)
{
    if (func_003C2320() == 0)
        return 0;
    return func_0036B260() != 0;
}

/* 0x003C23A0, 0xF0 bytes. Whether the player's officer knows one of the two commanders. */
int func_003C23A0(void)
{
    u32 a = func_003620E0(0, 0), b = func_003620E0(1, 0);
    int me = func_00327820();

    if (a >= 0x19F || b >= 0x19F || func_00329870() == 0)
        return 0;
    if (func_0032EB40(me, a, 1) == 0 && func_0032EB40(me, b, 1) == 0)
        return 0;
    return 1;
}

/* 0x003C2490, 0xE0 bytes. Whether force `f`'s ruler knows one of the two commanders. */
int func_003C2490(int f)
{
    u32 a = func_003620E0(0, 0), b = func_003620E0(1, 0);
    int r = func_002F8F20(f);

    if (a >= 0x19F || b >= 0x19F)
        return 0;
    if (func_0032EB40(r, a, 1) == 0 && func_0032EB40(r, b, 1) == 0)
        return 0;
    return 1;
}

/* 0x003C2570, 0x6C bytes. */
int func_003C2570(void)
{
    u8 k = func_00362570();

    if (func_00329870() == 0)
        return 0;
    switch (k) {
    case 0:
    case 2:
    case 4:
        return 1;
    default:
        return 0;
    }
}

/* 0x003C25E0, 0xDC bytes. Whether officer `o`'s force fights on the player's side. */
int func_003C25E0(u32 o)
{
    int f = func_002F4080(o);

    if (o >= 0x19F || func_0030D370() == 0 || func_003C2490(f) == 0)
        return 0;
    if (func_003635F0() == 0 && f == func_00327D50())
        return 1;
    if (func_003635F0() == 1 && f != func_00327D50())
        return 1;
    return 0;
}

/* 0x003C26C0, 0xDC bytes. Whether it fights on the other side. */
int func_003C26C0(u32 o)
{
    int f = func_002F4080(o);

    if (o >= 0x19F || func_0030D370() == 0 || func_003C2490(f) == 0)
        return 0;
    if (func_003635F0() == 1 && f == func_00327D50())
        return 1;
    if (func_003635F0() == 0 && f != func_00327D50())
        return 1;
    return 0;
}

/* 0x003C27A0, 0x144 bytes. How many of side `s`'s first six slots hold one of four officers. */
int func_003C27A0(int s, u32 a, u32 b, u32 c, u32 d)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 6; k++) {
        if ((a == func_003620E0(s, k) && a < 0x19F) || (b == func_003620E0(s, k) && b < 0x19F)
            || (c == func_003620E0(s, k) && c < 0x19F) || (d == func_003620E0(s, k) && d < 0x19F))
            n++;
    }
    return n;
}

/* 0x003C28F0, 0xC4 bytes. Side `s`'s officers (slots 6-7 too when `all`). */
int func_003C28F0(int s, int all)
{
    int n = 0;
    u32 k;

    if (all == 0) {
        for (k = 0; k < 6; k++) {
            if (func_003620E0(s, k) < 0x19F)
                n++;
        }
    } else {
        for (k = 0; k < 8; k++) {
            if (func_003620E0(s, k) < 0x19F)
                n++;
        }
    }
    return n;
}

/* 0x003C29C0, 0x9C bytes. How many of side 0's officers the player knows. */
int func_003C29C0(void)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 8; k++) {
        u32 o = func_003620E0(0, k);

        if (o < 0x19F && func_0032EB40(func_00327820(), o, 1) != 0)
            n++;
    }
    return n;
}

/* 0x003C2A60, 0x80 bytes, matching. The first officer the player knows of kind `kind` (-1 for none). */
int func_003C2A60(int kind)
{
    int k;

    for (k = 0; k < 0x19F; k++) {
        if (func_0032EB40(func_00327820(), k, 0) != 0 && kind == func_0032F7D0(func_002F27D0(k)))
            return k;
    }
    return -1;
}

/* 0x003C2AE0, 0x17C bytes. Whether officers `a` and `b` (neither ruler of the player's force or
 * of the other one) face each other as their sides' only one. */
int func_003C2AE0(int a, int b)
{
    int t[2], k;

    t[0] = a;
    t[1] = b;
    for (k = 0; k < 2; k++) {
        if (func_003C0790(t[k]) == 0)
            return 0;
        if (func_002F9260(func_00327D50()) == t[k])
            return 0;
        if (func_002F9260(func_0032EB00()) == t[k])
            return 0;
    }
    if ((func_003C27A0(0, a, 0x19F, 0x19F, 0x19F) == 1 && func_003C27A0(1, b, 0x19F, 0x19F, 0x19F) == 1)
        || (func_003C27A0(1, a, 0x19F, 0x19F, 0x19F) == 1 && func_003C27A0(0, b, 0x19F, 0x19F, 0x19F) == 1))
        return 1;
    return 0;
}

extern int g_0045D0D0[4];                /* (small data) two best scores and officers */
extern int g_0045D834;                   /* (small data) */
extern int g_00669DB8;

int func_002F3DC0(int o);
int func_0036B940(int s, int k);
int func_00362160(int s, int k);
int func_0036BA20(int s, int k);
u32 func_0032EEB0(void);
u32 func_0032EED0(void);
int func_00329540(int k);
int func_0032F2E0(int v);
int func_0032F3D0(int v);
void func_003BA8F0(int a, u32 o, int r, int x, int y);
int func_002F3E70(u32 o);
int func_0030DFA0(void);

/* 0x003C2C60, 0x168 bytes. Whether side 0 has another officer (not the player's, `a` or `b`)
 * that is free (`free`: of no force and kind 0) or of side 1's commander's force. */
int func_003C2C60(u32 a, u32 b, int free)
{
    u32 me = func_00327820(), c = func_003620E0(1, 0), k;
    int f;

    if (c >= 0x19F)
        return 0;
    f = func_002F4080(c);
    if (f < 0 || f >= func_0030AB90())
        return 0;
    for (k = 0; k < 8; k++) {
        u32 o = func_003620E0(0, k);
        int g;

        if (o >= 0x19F || o == me || o == a || o == b)
            continue;
        g = func_002F4080(o);
        if (free == 0) {
            if (g == 0x19 && func_002F3DC0(o) == 0)
                return 1;
        } else if (f == g) {
            return 1;
        }
    }
    return 0;
}

/* 0x003C2DD0, 0xB8 bytes. Whether side 0 has another officer in state 3. */
int func_003C2DD0(u32 a, u32 b)
{
    u32 me = func_00327820(), k;

    for (k = 0; k < 8; k++) {
        u32 o = func_003620E0(0, k);

        if (o < 0x19F && o != me && o != a && o != b && func_002F3BB0(o) == 3)
            return 1;
    }
    return 0;
}

/* 0x003C2E90, 0x138 bytes. Whether officer `o` is side 0's best (or, unless `best`, second best)
 * by func_0036BA20. */
int func_003C2E90(int o, int best)
{
    int s1 = g_0045D0D0[0], s2 = g_0045D0D0[1], o1 = g_0045D0D0[2], o2 = g_0045D0D0[3], k;

    if (func_003C0790(o) == 0)
        return 0;
    for (k = 0; k < 6; k++) {
        if (func_0036B940(0, k) == 0) {
            int x = func_00337A10(func_00362160(0, k)), v = func_0036BA20(0, k);

            if (s1 < v) {
                s2 = s1;
                o2 = o1;
                o1 = x;
                s1 = v;
            } else if (s2 < v) {
                o2 = x;
                s2 = v;
            }
        }
    }
    if (best == 0)
        return o1 == o || o2 == o;
    return o1 == o;
}

/* 0x003C2FD0, 0x64 bytes. The player's force's officers. */
int func_003C2FD0(void)
{
    int f = func_00327D50(), n = 0, k;

    for (k = 0; k < 0x19F; k++) {
        if (f == func_002F4080(k))
            n++;
    }
    return n;
}

/* 0x003C3040, 0x14 bytes. */
int func_003C3040(void)
{
    return g_00669DB8 == 0;
}

/* 0x003C3060, 0x10C bytes. Whether officer `o` serves side 1's commander's force. */
int func_003C3060(u32 o)
{
    u32 c = func_003620E0(1, 0);
    int f, g;

    if (o >= 0x19F || c >= 0x19F)
        return 0;
    f = func_002F4080(c);
    g = func_002F4080(o);
    if (f < 0 || f >= func_0030AB90() || g < 0 || g >= func_0030AB90())
        return 0;
    if (func_0030D370() == 0)
        return 0;
    return f == g;
}

/* 0x003C3170, 0x48 bytes. Side 0's commander is the event's first officer. */
void func_003C3170(void)
{
    int o = (short)func_003620E0(0, 0);

    if (o >= 0 && o < 0x19F)
        func_0032E8A0(0, o);
}

/* 0x003C31C0, 0x198 bytes. The event's first officer: side 0's hidden officer (kinds 1, 3, 5)
 * or one of side 0's officers the player knows. */
void func_003C31C0(void)
{
    int n = func_003C29C0(), r;
    u8 kind = func_00362570();
    u32 o = 0x19F;

    r = n == 0 ? 0 : (int)RANDOM() % n;
    switch (kind) {
    case 1:
    case 3:
    case 5:
        o = func_003620E0(0, 6);
        break;
    default: {
        u32 t[8], *p = t;
        int k;

        for (k = 0; k < 8; k++)
            t[k] = 0x19F;
        for (k = 0; k < 8; k++) {
            u32 x = func_003620E0(0, k);

            if (x < 0x19F && func_0032EB40(func_00327820(), x, 1) != 0)
                *p++ = x;
        }
        if (n != 0)
            o = t[r];
        break;
    }
    }
    if (o < 0x19F)
        func_0032E8A0(0, o);
}

/* 0x003C3360, 0x3C bytes, matching. */
void func_003C3360(void)
{
    g_0045D834 = 0;
    if (func_0030D370() != 0 && func_003C2360() != 0)
        g_0045D834 = 1;
}

/* Event `ev` (once) for an officer of kind `kind`. */
static int officer_event(int ev, int kind)
{
    if (func_00329540(ev) != 0)
        return 0;
    if (func_0032F3D0(func_0032F2E0(func_002F27D0(func_0032EEB0()))) != kind)
        return 0;
    func_003BA8F0(0, func_0032EEB0(), func_002F5CC0(func_0032EEB0()), -1, -1);
    return 1;
}

/* 0x003C33A0, 0x98 bytes. */
int func_003C33A0(void)
{
    return officer_event(0xC, 0);
}

/* 0x003C3440, 0x9C bytes. */
int func_003C3440(void)
{
    return officer_event(0xD, 1);
}

/* 0x003C34E0, 0x9C bytes. */
int func_003C34E0(void)
{
    return officer_event(0xE, 2);
}

/* 0x003C3580, 0xC4 bytes. Side 0's commander when the player knows it and it is a free officer
 * of another force (0x19F otherwise). */
u32 func_003C3580(void)
{
    u32 o = func_0032EED0();

    if (func_003C23A0() == 0 || o >= 0x19F)
        return 0x19F;
    if (func_002F3E70(o) != 0)
        return 0x19F;
    if (o != func_00337A10(func_00362160(0, 0)))
        return 0x19F;
    if (func_00327D50() == func_002F4080(o))
        return 0x19F;
    return o;
}

/* Event with that commander of kind `kind`. */
static int commander_event(int kind)
{
    u32 o = func_003C3580();

    if (o == 0x19F)
        return 0;
    if (func_0032F3D0(func_0032F2E0(func_002F27D0(o))) != kind)
        return 0;
    func_0032E8A0(0, func_003C0D20(o));
    func_0032E8A0(1, o);
    return 1;
}

/* 0x003C3650, 0x84 bytes. */
int func_003C3650(void)
{
    return commander_event(0);
}

/* 0x003C36E0, 0x88 bytes. */
int func_003C36E0(void)
{
    return commander_event(1);
}

/* 0x003C3770, 0x88 bytes. */
int func_003C3770(void)
{
    return commander_event(2);
}

/* 0x003C3800, 0x178 bytes. Event 0x14 (once, three regions or more), or in mode 6 the known
 * officer with the most merit who may rise. */
int func_003C3800(void)
{
    int best = -1, o = func_00337A10(0x29), me = func_00327820(), k;

    if (func_003C1850() == 0) {
        if (func_00329540(0x14) != 0 || g_0045D834 == 0)
            return 0;
        if (func_002FB3B0(func_00327D50()) < 3)
            return 0;
        func_0032E8A0(0, func_003C0D20(0x19F));
        return 1;
    }
    if (func_0030DFA0() != 6)
        return 0;
    for (k = 0; k < 0x19F; k++) {
        int m;

        if (k != me && func_0032EB40(me, k, 0) != 0 && func_003C0830(k) != 0
            && best < (m = func_002F34E0(k))) {
            best = m;
            o = k;
        }
    }
    func_0032E8A0(0, o);
    return 1;
}

/* Event `ev` (once) with at least `n` regions. */
static int regions_event(int ev, int n)
{
    if (func_003C1850() != 0 || func_00329540(ev) != 0 || g_0045D834 == 0)
        return 0;
    if (func_002FB3B0(func_00327D50()) < n)
        return 0;
    func_0032E8A0(0, func_003C0D20(0x19F));
    return 1;
}

/* 0x003C3980, 0x94 bytes. */
int func_003C3980(void)
{
    return regions_event(0x15, 10);
}

/* 0x003C3A20, 0x94 bytes. */
int func_003C3A20(void)
{
    return regions_event(0x16, 0x14);
}
