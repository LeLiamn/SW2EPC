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
int func_002F9550(int f);
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
    u32 v = func_002F9550(f);
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

u32 func_0030D170(int s);
double func_00125450(u32 v);             /* soft-float: int to double */
double func_00124F18(double a, double b);   /* soft-float: multiply */
int func_00143920(double a, double b);   /* soft-float compares */
int func_001438D0(double a, double b);
int func_001438F0(double a, double b);
int func_00143940(double a, double b);
u32 func_0032E950(void);
u32 func_00327C70(void);
int func_00327E90(void);
void func_002F94C0(int f);
int func_0030D150(void);

/* 0x003C4000, 0x50 bytes. Event 0x18 (once). */
int func_003C4000(void)
{
    if (func_003C1850() != 0 || func_00329540(0x18) != 0)
        return 0;
    func_003C0900();
    return 1;
}

/* 0x003C40E0, 0x154 bytes. Now and then (30%) when side 0 has fewer officers and its strength
 * times 1.5 is not below side 1's. */
int func_003C40E0(void)
{
    int a = func_003C28F0(0, 0), b = func_003C28F0(1, 0);
    u32 sa = func_0030D170(0), sb = func_0030D170(1), r = RANDOM();

    if (a < 1 || b < 1 || func_003C23A0() == 0 || a >= b)
        return 0;
    if (func_00143920(func_00124F18(1.5, func_00125450(sa)), func_00125450(sb)) != 0)
        return 0;
    if (r % 100 >= 0x1E)
        return 0;
    func_003C3170();
    return 1;
}

/* 0x003C4240, 0x164 bytes. The same when side 0 has more officers (side 1's strength times
 * 1.2). */
int func_003C4240(void)
{
    int a = func_003C28F0(0, 0), b = func_003C28F0(1, 0);
    u32 sa = func_0030D170(0), sb = func_0030D170(1), r = RANDOM();

    if (a < 1 || b < 1 || func_003C23A0() == 0 || b >= a)
        return 0;
    if (func_001438D0(func_00125450(sa), func_00124F18(1.2, func_00125450(sb))) != 0)
        return 0;
    if (r % 100 >= 0x1E)
        return 0;
    func_003C3170();
    return 1;
}

/* 0x003C43B0, 0x1B4 bytes. The same when the strengths are even for the numbers. */
int func_003C43B0(void)
{
    int a = func_003C28F0(0, 0), b = func_003C28F0(1, 0);
    u32 sa = func_0030D170(0), sb = func_0030D170(1), r = RANDOM();

    if (a < 1 || b < 1 || func_003C23A0() == 0)
        return 0;
    if (a < b && func_001438F0(func_00124F18(1.5, func_00125450(sa)), func_00125450(sb)) != 0)
        return 0;
    if (b < a && func_00143940(func_00125450(sa), func_00124F18(1.2, func_00125450(sb))) != 0)
        return 0;
    if (r % 100 >= 0x1E)
        return 0;
    func_003C3170();
    return 1;
}

/* 0x003C4570, 0x38 bytes. */
int func_003C4570(void)
{
    int r = func_0030D370();

    if (r != 0)
        func_003C31C0();
    return r != 0;
}

/* 0x003C45D0, 0x50 bytes. */
int func_003C45D0(void)
{
    u32 o = func_0032E950();

    if (o < 0x19F)
        func_0032E8A0(0, o);
    return o < 0x19F;
}

/* 0x003C46D0, 0x6C bytes. Event 0x34 (once, after 0x78): late in the game and a low fame. */
int func_003C46D0(void)
{
    if (func_00329540(0x34) != 0 || func_00329540(0x78) == 0)
        return 0;
    if (func_00327C70() < 0x15)
        return 0;
    return func_00327E90() < -9;
}

/* 0x003C4740, 0x70 bytes. Event 0x35 (once, after 0x77): late in the game and a high fame. */
int func_003C4740(void)
{
    if (func_00329540(0x35) != 0 || func_00329540(0x77) == 0)
        return 0;
    if (func_00327C70() < 0x15)
        return 0;
    return func_00327E90() > 9;
}

/* 0x003C47B0, 0xBC bytes. The player's force takes its new rank (when not already at the top
 * ones). */
int func_003C47B0(void)
{
    int f = func_00327D50();
    short v;

    if (f < 0 || f >= func_0030AB90())
        return 0;
    v = func_002F9550(f);
    if (v == 99 || v == 0x62 || v == 0x61)
        return 0;
    if ((short)func_003C09B0(f) == 100)
        return 0;
    func_002F94C0(f);
    return 1;
}

/* 0x003C48A0, 0x6C bytes. Event 0x3A (once) in mode 0xE. */
int func_003C48A0(void)
{
    if (func_003C1850() != 0 || func_00329540(0x3A) != 0 || func_003C2360() == 0)
        return 0;
    return func_0030D150() == 0xE;
}

/* 0x003C4910, 0x78 bytes. */
int func_003C4910(void)
{
    if (func_003C23A0() == 0 || func_0036B260() == 0)
        return 0;
    return RANDOM() % 100 < 0x1E;
}

/* 0x003C4990, 0x100 bytes. Now and then (30%) without func_0036B260 when the player knows side
 * 0's commander. */
int func_003C4990(void)
{
    int me = func_00327820();
    u32 c = func_003620E0(0, 0);

    if (c >= 0x19F || func_003C23A0() == 0 || func_0036B260() != 0)
        return 0;
    if (func_0032EB40(me, c, 1) == 0 || RANDOM() % 100 >= 0x1E)
        return 0;
    func_003C3170();
    return 1;
}

int func_0032EC50(int me, int a, int b, int c);
int func_0030D470(int s);
int func_0032EE10(int o);

/* 0x003C4E30, 0x70 bytes. Event 0x77 (once, before 0x35): from turn 11 with a good fame. */
int func_003C4E30(void)
{
    if (func_00329540(0x77) != 0 || func_00329540(0x35) != 0)
        return 0;
    if (func_00327C70() < 0xB)
        return 0;
    return func_00327E90() > 4;
}

/* 0x003C4EA0, 0x6C bytes. Event 0x78 (once, before 0x34): from turn 11 with a bad fame. */
int func_003C4EA0(void)
{
    if (func_00329540(0x78) != 0 || func_00329540(0x34) != 0)
        return 0;
    if (func_00327C70() < 0xB)
        return 0;
    return func_00327E90() < -4;
}

/* 0x003C4FF0, 0x58 bytes. Event 0x87 (once) for officer 8 with no event officer. */
int func_003C4FF0(void)
{
    if (func_00329540(0x87) != 0 || func_00327820() != 8)
        return 0;
    return func_0032E950() == 0;
}

/* 0x003C5050, 0x138 bytes. Event 0x88 (once): side 1's commander's force holds three regions or
 * more and side 0 has officer 0 and officer 0x8E. */
int func_003C5050(void)
{
    int me = func_00327820(), x = func_00337A10(0x8E), f, n;
    u32 c = func_003620E0(1, 0);

    if (func_003C0790(c) == 0)
        return 0;
    f = func_002F4080(c);
    if (f < 0 || f >= func_0030AB90())
        return 0;
    n = func_002FB3B0(f);
    if (func_00329540(0x88) != 0 || func_0032EC50(me, 0, x, 1) == 0)
        return 0;
    if (func_003C27A0(0, 0, x, 0x19F, 0x19F) != 2 || n < 3)
        return 0;
    return func_0030D470(1) != 0;
}

/* Event `ev` (once): officers 0 and `o` (of different forces) face each other. */
static int duel_event(int ev, int o)
{
    if (func_00329540(ev) != 0 || func_003C23A0() == 0)
        return 0;
    if (func_002F4080(0) == func_002F4080(o))
        return 0;
    return func_003C2AE0(0, o) != 0;
}

/* 0x003C5190, 0x80 bytes. */
int func_003C5190(void)
{
    return duel_event(0x89, 1);
}

/* 0x003C5210, 0x9C bytes. Event 0x8A (once): from turn 31, officer 9 knows officer 0 (rank 20 or
 * more). */
int func_003C5210(void)
{
    if (func_00329540(0x8A) != 0 || func_00327C70() < 0x1F || func_00327820() != 9)
        return 0;
    if (func_0032EB40(func_00327820(), 0, 0) == 0)
        return 0;
    return func_002F33F0(0) > 0x13;
}

/* 0x003C52B0, 0xC4 bytes. Event 0x8B (once): from turn 16, the player knows officers 9 and 0 (both
 * rank 10 or more). */
int func_003C52B0(void)
{
    if (func_00329540(0x8B) != 0 || func_00327C70() < 0x10)
        return 0;
    if (func_0032EB40(func_00327820(), 9, 1) == 0 || func_0032EB40(func_00327820(), 0, 0) == 0)
        return 0;
    if (func_002F33F0(0) < 10)
        return 0;
    return func_002F33F0(9) > 9;
}

/* 0x003C5380, 0xA0 bytes. Event 0x8C (once): officer 0x10 knows 0xB, and 0 faces 0xB. */
int func_003C5380(void)
{
    if (func_00329540(0x8C) != 0 || func_0032EB40(0x10, 0xB, 0) == 0 || func_003C23A0() == 0)
        return 0;
    if (func_002F4080(0) == func_002F4080(0xB))
        return 0;
    return func_003C2AE0(0, 0xB) != 0;
}

/* 0x003C5420, 0x80 bytes. */
int func_003C5420(void)
{
    return duel_event(0x8D, 0x11);
}

/* 0x003C54A0, 0xE0 bytes. Event 0x8E (once): officer 0x10 with officer 0 alone on side 0's
 * front, 0 being side 0's best. */
int func_003C54A0(void)
{
    if (func_00329540(0x8E) != 0 || func_003C23A0() == 0)
        return 0;
    if (func_0032EC50(func_00327820(), 0, 0x10, 1) == 0 || func_00327820() != 0x10)
        return 0;
    if (func_003C27A0(0, 0, 0x19F, 0x19F, 0x19F) != 1 || func_0036B260() == 0)
        return 0;
    return func_003C2E90(0, 1) != 0;
}

/* 0x003C5580, 0x98 bytes. Event 0x8F (once, after 0x8E): 0 faces 0x19. */
int func_003C5580(void)
{
    if (func_00329540(0x8F) != 0 || func_00329540(0x8E) == 0 || func_003C23A0() == 0)
        return 0;
    if (func_002F4080(0) == func_002F4080(0x19))
        return 0;
    return func_003C2AE0(0, 0x19) != 0;
}

/* 0x003C5620, 0x8C bytes. Event 0x90 (once): the player is officer 0xAB, knows 0, and 0xD is in
 * state 3. */
int func_003C5620(void)
{
    if (func_00329540(0x90) != 0 || func_00337A10(0xAB) != func_00327820())
        return 0;
    if (func_0032EB40(func_00327820(), 0, 0) == 0)
        return 0;
    return func_002F3BB0(0xD) == 3;
}

/* 0x003C56B0, 0xB0 bytes. Event 0x91 (once): func_0032EE10 false for 0 and true for 0x10, and 0
 * faces 0x10. */
int func_003C56B0(void)
{
    if (func_00329540(0x91) != 0 || func_0032EE10(0) != 0 || func_0032EE10(0x10) == 0)
        return 0;
    if (func_003C23A0() == 0 || func_002F4080(0) == func_002F4080(0x10))
        return 0;
    return func_003C2AE0(0, 0x10) != 0;
}

int func_00328270(void);
int func_00328230(void);

/* Event `ev` (once): from turn `turn`, the player knows officers `a` and `b` (`how` 0 or 1), both
 * of rank `rank` or more. */
static int bond_event(int ev, u32 turn, int a, int b, int how, int rank)
{
    if (func_00329540(ev) != 0 || func_00327C70() < turn)
        return 0;
    if (func_0032EB40(func_00327820(), a, how) == 0 || func_0032EB40(func_00327820(), b, how) == 0)
        return 0;
    if (func_002F33F0(a) < rank)
        return 0;
    return func_002F33F0(b) >= rank;
}

/* Officers `a` and `b` (of different forces) face each other. */
static int face(int a, int b)
{
    if (func_003C23A0() == 0 || func_002F4080(a) == func_002F4080(b))
        return 0;
    return func_003C2AE0(a, b) != 0;
}

/* 0x003C58B0, 0xC4 bytes. */
int func_003C58B0(void)
{
    return bond_event(0x93, 0x1F, 1, 0x16, 0, 10);
}

/* 0x003C5980, 0xF0 bytes. Event 0x94 (once): from turn 11, officers 1 and 0x17 (rank 5) while
 * officer 0xDD is in play. */
int func_003C5980(void)
{
    int st = func_002F3BB0(func_00337A10(0xDD));

    if (func_00329540(0x94) != 0 || func_00327C70() < 0xB)
        return 0;
    if (func_0032EB40(func_00327820(), 1, 0) == 0 || func_0032EB40(func_00327820(), 0x17, 0) == 0)
        return 0;
    if (st == 0 || func_002F33F0(1) < 5)
        return 0;
    return func_002F33F0(0x17) > 4;
}

/* 0x003C5A70, 0x80 bytes. */
int func_003C5A70(void)
{
    if (func_00329540(0x95) != 0)
        return 0;
    return face(1, 7);
}

/* 0x003C5AF0, 0xC4 bytes. */
int func_003C5AF0(void)
{
    return bond_event(0x96, 0x10, 1, 7, 0, 5);
}

/* 0x003C5BC0, 0xA8 bytes. */
int func_003C5BC0(void)
{
    return bond_event(0x97, 0, 1, 9, 0, 5);
}

/* 0x003C5C70, 0x78 bytes. Event 0x98 (once): officers 1 and 0x14 together on side 0. */
int func_003C5C70(void)
{
    if (func_00329540(0x98) != 0 || func_0032EC50(func_00327820(), 1, 0x14, 1) == 0)
        return 0;
    return func_003C27A0(0, 1, 0x14, 0x19F, 0x19F) == 2;
}

/* 0x003C5CF0, 0xA8 bytes. Event 0x99 (once): officers 1 and 4 together on side 0. */
int func_003C5CF0(void)
{
    if (func_00329540(0x99) != 0 || func_003C23A0() == 0)
        return 0;
    if (func_0032EC50(func_00327820(), 1, 4, 1) == 0 || func_003C27A0(0, 1, 4, 0x19F, 0x19F) != 2)
        return 0;
    return func_0036B260() != 0;
}

/* 0x003C5DA0, 0xC0 bytes. Event 0x9A (once): officers 1 and 0x14 together on side 0. */
int func_003C5DA0(void)
{
    if (func_00329540(0x9A) != 0 || func_003C23A0() == 0)
        return 0;
    if (func_0032EC50(func_00327820(), 1, 0x14, 1) == 0 || func_003C27A0(0, 1, 0x14, 0x19F, 0x19F) != 2)
        return 0;
    if (func_0032EE10(0x14) != 0)
        return 0;
    return func_0036B260() != 0;
}

/* 0x003C5E60, 0xA8 bytes. */
int func_003C5E60(void)
{
    return bond_event(0x9B, 0, 1, 0x15, 1, 5);
}

/* 0x003C5F10, 0xC4 bytes. */
int func_003C5F10(void)
{
    return bond_event(0x9C, 0xB, 1, 0x11, 1, 5);
}

/* 0x003C5FE0, 0xC4 bytes. */
int func_003C5FE0(void)
{
    return bond_event(0x9D, 0x10, 1, 2, 1, 10);
}

/* 0x003C60B0, 0xBC bytes. */
int func_003C60B0(void)
{
    if (func_00329540(0x9E) != 0 || func_0032EB40(0x12, 5, 0) == 0 || func_00328270() != 1)
        return 0;
    return face(2, 5);
}

/* 0x003C6170, 0xD4 bytes. Event 0x9F (once): the player knows officers 2 and 10, in the same
 * region, both of rank 10. */
int func_003C6170(void)
{
    if (func_00329540(0x9F) != 0)
        return 0;
    if (func_0032EB40(func_00327820(), 2, 1) == 0 || func_0032EB40(func_00327820(), 10, 1) == 0)
        return 0;
    if (func_002F5CC0(2) != func_002F5CC0(10) || func_002F33F0(2) < 10)
        return 0;
    return func_002F33F0(10) > 9;
}

/* 0x003C6250, 0x80 bytes. */
int func_003C6250(void)
{
    if (func_00329540(0xA0) != 0)
        return 0;
    return face(2, 10);
}

/* 0x003C62D0, 0xC0 bytes. */
int func_003C62D0(void)
{
    if (func_00329540(0xA1) != 0 || func_002F4080(0x12) != func_002F4080(5) || func_00328270() != 1)
        return 0;
    return face(2, 0x12);
}

/* 0x003C6390, 0xC4 bytes. Event 0xA2 (once): from turn 11, officers 2 (known 1) and 0x14 (known
 * 0), both of rank 5. */
int func_003C6390(void)
{
    if (func_00329540(0xA2) != 0 || func_00327C70() < 0xB)
        return 0;
    if (func_0032EB40(func_00327820(), 2, 1) == 0 || func_0032EB40(func_00327820(), 0x14, 0) == 0)
        return 0;
    if (func_002F33F0(2) < 5)
        return 0;
    return func_002F33F0(0x14) > 4;
}

/* Event `ev` (once): from turn `turn`, the player (officer 2) knows `o` of rank above `rank`. */
static int player2_event(int ev, u32 turn, int o, int rank)
{
    if (func_00329540(ev) != 0 || func_00327C70() < turn || func_00327820() != 2)
        return 0;
    if (func_0032EB40(func_00327820(), o, 0) == 0)
        return 0;
    return func_002F33F0(o) > rank;
}

/* 0x003C6460, 0x9C bytes. */
int func_003C6460(void)
{
    return player2_event(0xA3, 0xB, 0x1B, 9);
}

/* 0x003C6500, 0x9C bytes. */
int func_003C6500(void)
{
    return player2_event(0xA4, 0xB, 0xD, 9);
}

/* 0x003C65A0, 0x9C bytes. */
int func_003C65A0(void)
{
    return player2_event(0xA5, 0x10, 0x10, 0xE);
}

/* 0x003C6640, 0x98 bytes. */
int func_003C6640(void)
{
    if (func_00329540(0xA6) != 0 || func_0032EE10(2) != 0)
        return 0;
    return face(2, 3);
}

/* 0x003C66E0, 0xB0 bytes. */
int func_003C66E0(void)
{
    if (func_00329540(0xA7) != 0 || func_0032EE10(2) != 0 || face(2, 0xD) == 0)
        return 0;
    return func_00328230() != 0;
}

/* 0x003C6790, 0x98 bytes. */
int func_003C6790(void)
{
    if (func_00329540(0xA8) != 0 || func_0032EE10(2) != 0)
        return 0;
    return face(2, 0xC);
}

/* 0x003C6830, 0xB0 bytes. */
int func_003C6830(void)
{
    if (func_00329540(0xA9) != 0 || func_0032EE10(2) != 0 || func_0032EE10(0x10) == 0)
        return 0;
    return face(2, 0x10);
}

/* 0x003C68E0, 0xC4 bytes. */
int func_003C68E0(void)
{
    return bond_event(0xAA, 0x1F, 2, 0x15, 1, 5);
}

/* 0x003C69B0, 0x68 bytes. Event 0xAB (once): the player is officer 2 with officer 0xCE. */
int func_003C69B0(void)
{
    if (func_00329540(0xAB) != 0 || func_00327820() != 2)
        return 0;
    return func_00337A10(0xCE) == func_0032E950();
}

/* 0x003C6A20, 0x98 bytes. Event 0xAC (once, after 0x89). */
int func_003C6A20(void)
{
    if (func_00329540(0xAC) != 0 || func_00329540(0x89) == 0)
        return 0;
    return face(1, 0);
}

/* 0x003C6AC0, 0x80 bytes. */
int func_003C6AC0(void)
{
    if (func_00329540(0xAD) != 0)
        return 0;
    return face(3, 0xB);
}

int func_002F7550(int o);

/* 0x003C6B40, 0xE0 bytes. */
int func_003C6B40(void)
{
    if (func_00329540(0xAE) != 0 || func_00327C70() < 0x15 || func_00327820() != 2)
        return 0;
    return bond_event(0xAE, 0x15, 3, 0xD, 0, 0xF);
}

/* 0x003C6C20, 0xE0 bytes. */
int func_003C6C20(void)
{
    return bond_event(0xAF, 0x15, 3, func_00337A10(0x70), 0, 10);
}

/* 0x003C6D00, 0xE0 bytes. */
int func_003C6D00(void)
{
    if (func_00329540(0xB0) != 0 || func_00327C70() < 0x1F || func_00327820() != 0xD)
        return 0;
    return bond_event(0xB0, 0x1F, 3, 0x17, 0, 0x14);
}

/* Event `ev` (once): from turn 16, player `p` with a known officer of kind 0x1F. */
static int kind_event(int ev, int p)
{
    int o;

    if (func_00329540(ev) != 0 || func_00327C70() < 0x10 || func_00327820() != p)
        return 0;
    o = func_003C2A60(0x1F);
    if (o == -1 || o < 0 || o >= 0x19F)
        return 0;
    func_0032E8A0(0, o);
    return 1;
}

/* 0x003C6DE0, 0xB8 bytes. */
int func_003C6DE0(void)
{
    return kind_event(0xB1, 3);
}

/* 0x003C6EA0, 0xB8 bytes. */
int func_003C6EA0(void)
{
    return kind_event(0xB2, 0xD);
}

/* 0x003C6F60, 0xA8 bytes. Event 0xB3 (once): the player is officer 4 with officer 3, both values
 * of func_002F7550 at 20 or more. */
int func_003C6F60(void)
{
    int a = func_002F7550(4), b = func_002F7550(3);

    if (func_00329540(0xB3) != 0 || func_00327820() != 4 || func_0032E950() != 3)
        return 0;
    if (a < 0x14)
        return 0;
    return b > 0x13;
}

/* 0x003C7010, 0x68 bytes. */
int func_003C7010(void)
{
    if (func_00329540(0xB4) != 0 || func_00327820() != 4)
        return 0;
    return func_00337A10(0x107) == func_0032E950();
}

/* 0x003C7080, 0x58 bytes. */
int func_003C7080(void)
{
    if (func_00329540(0xB5) != 0 || func_00327820() != 4)
        return 0;
    return func_0032E950() == 0x16;
}

/* 0x003C70E0, 0x80 bytes. */
int func_003C70E0(void)
{
    return func_00329540(0xB6) == 0 && face(4, 2);
}

/* 0x003C7160, 0x80 bytes. */
int func_003C7160(void)
{
    return func_00329540(0xB7) == 0 && face(4, 0x18);
}

/* 0x003C71E0, 0x80 bytes. */
int func_003C71E0(void)
{
    return func_00329540(0xB8) == 0 && face(4, 0xB);
}

/* 0x003C7260, 0x80 bytes. */
int func_003C7260(void)
{
    return func_00329540(0xB9) == 0 && face(4, 0xF);
}

/* 0x003C72E0, 0x80 bytes. */
int func_003C72E0(void)
{
    return func_00329540(0xBA) == 0 && face(4, 0x15);
}

/* 0x003C7360, 0x98 bytes. */
int func_003C7360(void)
{
    if (func_00329540(0xBB) != 0 || func_0032EE10(2) != 0)
        return 0;
    return face(4, 2);
}

/* 0x003C7400, 0xC4 bytes. */
int func_003C7400(void)
{
    return bond_event(0xBC, 0xB, 4, 7, 1, 5);
}

/* 0x003C74D0, 0x80 bytes. */
int func_003C74D0(void)
{
    return func_00329540(0xBD) == 0 && face(4, 0x14);
}

int func_00327CC0(void);

#define KNOWS(o, how) (func_0032EB40(func_00327820(), (o), (how)) != 0)

/* 0x003C76C0, 0xE0 bytes. */
int func_003C76C0(void)
{
    if (func_00329540(0xBF) != 0 || func_00327C70() < 6)
        return 0;
    if (!KNOWS(4, 1) || !KNOWS(func_00337A10(0x56), 0))
        return 0;
    if (func_002F33F0(4) < 5)
        return 0;
    return func_002F33F0(func_00337A10(0x56)) > 4;
}

/* 0x003C77A0, 0x168 bytes. Event 0xC0 (once, after 0xEF, before 0xF0). */
int func_003C77A0(void)
{
    int v;

    if (func_00329540(0xC0) != 0 || func_00329540(0xEF) == 0 || func_00329540(0xF0) != 0)
        return 0;
    if (!KNOWS(7, 0) || !KNOWS(5, 0) || !KNOWS(0xD, 0) || KNOWS(0x12, 1) || KNOWS(0x1B, 1))
        return 0;
    v = func_00328270();
    return v == 0 || func_00328270() == 2 || func_00328270() == 4;
}

/* 0x003C7910, 0x138 bytes. */
int func_003C7910(void)
{
    if (func_00329540(0xC1) != 0)
        return 0;
    if (!KNOWS(0x13, 0) || !KNOWS(5, 1) || KNOWS(0x12, 1) || KNOWS(0x1B, 1))
        return 0;
    if (func_002F33F0(0x13) < 5 || func_002F33F0(5) < 5)
        return 0;
    return func_00328270() == 2 || func_00328270() == 4;
}

/* 0x003C7A50, 0xE4 bytes. */
int func_003C7A50(void)
{
    if (func_00329540(0xC2) != 0 || func_00327C70() < 0xB)
        return 0;
    if (!KNOWS(0x12, 1) || !KNOWS(5, 0))
        return 0;
    if (func_00328270() != 0 && func_00328270() != 1)
        return 0;
    return func_00327CC0() != 3;
}

/* 0x003C7B40, 0x12C bytes. */
int func_003C7B40(void)
{
    if (func_00329540(0xC3) != 0)
        return 0;
    if (!KNOWS(5, 0) || !KNOWS(0xC, 0) || KNOWS(0x12, 1))
        return 0;
    if (func_002F33F0(5) < 5 || func_002F33F0(0xC) < 5)
        return 0;
    if (func_00328270() != 0 && func_00328270() != 2 && func_00328270() != 4)
        return 0;
    return func_00327CC0() != 3;
}

/* 0x003C7C70, 0x8C bytes. */
int func_003C7C70(void)
{
    if (func_00329540(0xC4) != 0 || func_00327C70() < 6 || !KNOWS(6, 0))
        return 0;
    return KNOWS(1, 0);
}

/* 0x003C7D00, 0x80 bytes. */
int func_003C7D00(void)
{
    if (func_00329540(0xC5) != 0 || func_003C23A0() == 0 || func_002F4080(6) == func_002F4080(1))
        return 0;
    return func_003C2AE0(1, 6) != 0;
}

/* 0x003C7D80, 0x64 bytes. */
int func_003C7D80(void)
{
    if (func_00329540(0xC6) != 0 || func_00327820() != 0xD)
        return 0;
    return KNOWS(6, 0);
}

/* 0x003C7DF0, 0xE4 bytes. */
int func_003C7DF0(void)
{
    if (func_00329540(199) != 0 || func_00327C70() < 0x10)
        return 0;
    if (!KNOWS(0x12, 1) || !KNOWS(6, 1) || KNOWS(5, 1))
        return 0;
    if (func_002F3BB0(5) == 0)
        return 0;
    return func_00328270() != 0;
}

/* 0x003C7EE0, 0x8C bytes. */
int func_003C7EE0(void)
{
    if (func_00329540(200) != 0 || func_00327C70() < 0xB || !KNOWS(7, 0))
        return 0;
    return KNOWS(0xC, 0);
}

/* 0x003C7F70, 0x8C bytes. */
int func_003C7F70(void)
{
    if (func_00329540(0xC9) != 0 || func_00327C70() < 6 || !KNOWS(7, 1))
        return 0;
    return KNOWS(10, 0);
}

/* 0x003C8000, 0x8C bytes. */
int func_003C8000(void)
{
    if (func_00329540(0xCA) != 0 || func_00327C70() < 0x10 || !KNOWS(7, 1))
        return 0;
    return KNOWS(0x15, 0);
}

/* 0x003C8090, 0x100 bytes. Event 0xCB (once): officers 8 and 4 face each other as the two
 * commanders. */
int func_003C8090(void)
{
    if (func_00329540(0xCB) != 0 || face(8, 4) == 0)
        return 0;
    if (func_003620E0(0, 0) != 4 && func_003620E0(1, 0) != 4)
        return 0;
    return func_003620E0(0, 0) == 8 || func_003620E0(1, 0) == 8;
}

/* 0x003C8190, 0xA4 bytes. Event 0xCC (once; mode 10 or after 0xCD): officers 8 and 4 together on
 * side 0. */
int func_003C8190(void)
{
    if (func_00327C00() != 10 && func_00329540(0xCD) == 0)
        return 0;
    if (func_00329540(0xCC) != 0 || func_0032EC50(func_00327820(), 8, 4, 1) == 0)
        return 0;
    return func_003C27A0(0, 8, 4, 0x19F, 0x19F) == 2;
}

/* Event `ev` (once): officers `a` and `b` together on side 0. */
static int pair_event(int ev, int a, int b)
{
    if (func_00329540(ev) != 0 || func_0032EC50(func_00327820(), a, b, 1) == 0)
        return 0;
    return func_003C27A0(0, a, b, 0x19F, 0x19F) == 2;
}

/* 0x003C8240, 0x94 bytes. Event 0xCD (once, mode 10): officers 8 and 4 together on side 0. */
int func_003C8240(void)
{
    if (func_00327C00() != 10)
        return 0;
    return pair_event(0xCD, 8, 4);
}

/* 0x003C82E0, 0xC8 bytes. */
int func_003C82E0(void)
{
    if (func_00329540(0xCE) != 0 || !KNOWS(8, 1) || func_0032EE10(0x10) == 0)
        return 0;
    if (func_0032EB40(0x10, 0xE, 0) == 0 || func_002F4080(8) == func_002F4080(0xE))
        return 0;
    return func_003C2AE0(8, 0xE) != 0;
}

/* 0x003C83B0, 0x100 bytes. Event 0xCF (once): 8 faces 0x10, and either the player knows 8 or
 * func_0036B260 (not both). */
int func_003C83B0(void)
{
    if (func_00329540(0xCF) != 0 || func_003C2570() == 0)
        return 0;
    if (func_002F4080(8) == func_002F4080(0x10) || func_003C2AE0(8, 0x10) == 0)
        return 0;
    if (KNOWS(8, 1) && func_0036B260() != 0)
        return 0;
    if (!KNOWS(8, 1) && func_0036B260() == 0)
        return 0;
    return 1;
}

/* 0x003C84B0, 0x58 bytes. */
int func_003C84B0(void)
{
    if (func_00329540(0xD0) != 0 || func_00327820() != 8)
        return 0;
    return func_0032E950() == 0x15;
}

/* 0x003C8510, 0x70 bytes. */
int func_003C8510(void)
{
    if (func_00329540(0xD1) != 0 || !KNOWS(8, 1))
        return 0;
    return KNOWS(0x14, 0);
}

/* 0x003C8580, 0x68 bytes. */
int func_003C8580(void)
{
    if (func_00329540(0xD2) != 0 || func_00327820() != 8)
        return 0;
    return func_00337A10(0x7A) == func_0032E950();
}

/* 0x003C85F0, 0x94 bytes. */
int func_003C85F0(void)
{
    if (pair_event(0xD3, 9, 7) == 0)
        return 0;
    return func_00327820() == 9;
}

/* 0x003C8690, 0xC4 bytes. */
int func_003C8690(void)
{
    return bond_event(0xD4, 0x10, 9, 0x11, 0, 10);
}

/* 0x003C8760, 0x80 bytes. */
int func_003C8760(void)
{
    return func_00329540(0xD5) == 0 && face(3, 10);
}

/* 0x003C87E0, 0x80 bytes. */
int func_003C87E0(void)
{
    return func_00329540(0xD6) == 0 && face(10, 7);
}

/* 0x003C8860, 0x98 bytes. */
int func_003C8860(void)
{
    if (func_00329540(0xD7) != 0 || func_0032EE10(0x13) != 0)
        return 0;
    return face(10, 0x13);
}

/* 0x003C8900, 0xD4 bytes. */
int func_003C8900(void)
{
    if (func_00329540(0xD8) != 0 || func_00327C70() < 0xB || !KNOWS(10, 1) || !KNOWS(0x12, 0))
        return 0;
    if (func_002F4080(0x12) != func_002F4080(5))
        return 0;
    return func_00328270() == 1;
}

/* 0x003C89E0, 0x78 bytes. */
int func_003C89E0(void)
{
    return pair_event(0xD9, 10, 0x17);
}

/* 0x003C8A60, 0xE0 bytes. */
int func_003C8A60(void)
{
    if (func_00329540(0xDA) != 0 || func_0032EB40(2, 10, 0) == 0)
        return 0;
    if (func_002F4080(0x12) != func_002F4080(5) || func_00328270() != 1)
        return 0;
    return face(10, 5);
}

/* 0x003C8B40, 0x80 bytes. */
int func_003C8B40(void)
{
    return func_00329540(0xDB) == 0 && face(10, 0x1A);
}

/* 0x003C8BC0, 0x94 bytes. */
int func_003C8BC0(void)
{
    return pair_event(0xDC, 0xB, 0x10) && func_0032EE10(0xB) == 0;
}

/* 0x003C8C60, 0x94 bytes. */
int func_003C8C60(void)
{
    return pair_event(0xDD, 0xB, 0xE) && func_0032EE10(0xB) == 0;
}

/* 0x003C8D00, 0x80 bytes. */
int func_003C8D00(void)
{
    return func_00329540(0xDE) == 0 && face(0xB, 0xE);
}

/* 0x003C8D80, 0x78 bytes. */
int func_003C8D80(void)
{
    return pair_event(0xDF, 0xB, 0x18);
}

/* `a` and `b` of different forces and facing each other (without the commander check). */
static int face2(int a, int b)
{
    if (func_002F4080(a) == func_002F4080(b))
        return 0;
    return func_003C2AE0(a, b) != 0;
}

/* 0x003C8E00, 0x80 bytes. */
int func_003C8E00(void)
{
    return func_00329540(0xE0) == 0 && face(0xB, 0x12);
}

/* 0x003C8E80, 0xA0 bytes. */
int func_003C8E80(void)
{
    if (func_00329540(0xE1) != 0 || func_0032EB40(0x10, 0xB, 0) == 0)
        return 0;
    return face(0xB, 0x1A);
}

/* 0x003C8F20, 0x98 bytes. */
int func_003C8F20(void)
{
    if (func_00329540(0xE2) != 0 || func_0032EB40(2, 0xC, 0) == 0)
        return 0;
    return pair_event(0xE2, 0xC, 2);
}

/* 0x003C8FC0, 0x94 bytes. */
int func_003C8FC0(void)
{
    if (func_00329540(0xE3) != 0 || func_00327820() != 2)
        return 0;
    if (func_0032EC50(func_00327820(), 0xC, 3, 0) == 0)
        return 0;
    return func_003C27A0(0, 0xC, 3, 0x19F, 0x19F) == 2;
}

/* Event `ev` (once): officer 2 knows 0xC, and 0xC faces `o`. */
static int c_event(int ev, int o)
{
    if (func_00329540(ev) != 0 || func_0032EB40(2, 0xC, 0) == 0)
        return 0;
    return face(0xC, o);
}

/* 0x003C9060, 0xA0 bytes. */
int func_003C9060(void)
{
    return c_event(0xE4, 3);
}

/* 0x003C9100, 0xA0 bytes. */
int func_003C9100(void)
{
    return c_event(0xE5, 0xB);
}

/* 0x003C91A0, 0xA0 bytes. */
int func_003C91A0(void)
{
    return c_event(0xE6, 0x18);
}

/* 0x003C9240, 0x100 bytes. */
int func_003C9240(void)
{
    if (func_00329540(0xE7) != 0 || func_0032EB40(2, 0xC, 0) == 0)
        return 0;
    if (func_002F4080(5) == func_002F4080(0x12) || func_002F4080(5) == func_002F4080(0x1B))
        return 0;
    if (func_00328270() != 2 && func_00328270() != 4)
        return 0;
    return face2(0xC, 5);
}

/* 0x003C9340, 0xE0 bytes. */
int func_003C9340(void)
{
    if (func_00329540(0xE8) != 0 || func_0032EB40(2, 0xC, 0) == 0 || func_002F2840(5) == 0)
        return 0;
    if (func_002F4080(5) != func_002F4080(0x12) || func_00328270() != 1)
        return 0;
    return face2(0xC, 0x12);
}

/* 0x003C9420, 0x78 bytes. */
int func_003C9420(void)
{
    return pair_event(0xE9, 0xC, 9);
}

/* 0x003C94A0, 0x58 bytes. */
int func_003C94A0(void)
{
    if (func_00329540(0xEA) != 0 || func_00327820() != 0x10)
        return 0;
    return func_0032E950() == 0xC;
}

/* 0x003C9500, 0xD0 bytes. */
int func_003C9500(void)
{
    if (func_00329540(0xEB) != 0 || func_00327C70() < 0xB)
        return 0;
    if (!KNOWS(0xC, 0) || !KNOWS(0x11, 1) || !KNOWS(0x13, 0))
        return 0;
    return func_0032EE10(0xC) == 0;
}

/* 0x003C95D0, 0xCC bytes. */
int func_003C95D0(void)
{
    if (func_00329540(0xEC) != 0 || func_00329540(0xEB) == 0)
        return 0;
    if (!KNOWS(0xC, 0) || !KNOWS(0x11, 1) || !KNOWS(0x13, 0))
        return 0;
    return func_0032EE10(0xC) == 0;
}

/* 0x003C96A0, 0xDC bytes. */
int func_003C96A0(void)
{
    if (func_00329540(0xED) != 0 || func_00327C70() < 0x10 || func_003C2180() < 1)
        return 0;
    if (!KNOWS(0xC, 0) || !KNOWS(0x16, 0) || func_002F33F0(0xC) < 10)
        return 0;
    return func_002F33F0(0x16) > 9;
}

/* 0x003C9780, 0x7C bytes. */
int func_003C9780(void)
{
    if (func_00329540(0xEE) != 0 || !KNOWS(0xD, 1) || func_002F33F0(0xD) < 1)
        return 0;
    return func_0032E950() == 7;
}

/* The common tail of events 0xC0, 0xEF and 0xF0. */
static int trio_tail(void)
{
    int v;

    if (!KNOWS(7, 0) || !KNOWS(5, 0) || !KNOWS(0xD, 0) || KNOWS(0x12, 1) || KNOWS(0x1B, 1))
        return 0;
    v = func_00328270();
    return v == 0 || func_00328270() == 2 || func_00328270() == 4;
}

/* 0x003C9800, 0x184 bytes. Event 0xEF (once, before 0xC0 and 0xF0, from turn 6). */
int func_003C9800(void)
{
    if (func_00329540(0xEF) != 0 || func_00329540(0xC0) != 0 || func_00329540(0xF0) != 0)
        return 0;
    if (func_00327C70() < 6)
        return 0;
    return trio_tail();
}

/* 0x003C9990, 0x168 bytes. Event 0xF0 (once, after 0xEF and 0xC0). */
int func_003C9990(void)
{
    if (func_00329540(0xF0) != 0 || func_00329540(0xEF) == 0 || func_00329540(0xC0) == 0)
        return 0;
    return trio_tail();
}

int func_0032EAC0(void);

/* 0x003C9B00, 0x13C bytes. */
int func_003C9B00(void)
{
    int v;

    if (func_00329540(0xF1) != 0 || func_00327C70() < 0x10)
        return 0;
    if (!KNOWS(0xD, 0) || !KNOWS(5, 1) || KNOWS(0x12, 1))
        return 0;
    if (func_002F33F0(0xD) < 10 || func_002F33F0(5) < 5)
        return 0;
    v = func_00328270();
    return v == 0 || func_00328270() == 2 || func_00328270() == 4;
}

/* 0x003C9C40, 0x64 bytes. */
int func_003C9C40(void)
{
    if (func_00329540(0xF2) != 0 || func_00327820() != 0xD)
        return 0;
    return KNOWS(9, 0);
}

/* 0x003C9CB0, 0x78 bytes. */
int func_003C9CB0(void)
{
    if (func_00329540(0xF3) != 0 || func_00327820() != 0xD)
        return 0;
    return KNOWS(func_00337A10(0x158), 0);
}

/* 0x003C9D30, 0xA4 bytes. */
int func_003C9D30(void)
{
    int me = func_00327820(), f = func_00327D50();

    if (func_003C1850() != 0 || func_00329540(0xF4) != 0 || me != 0xD)
        return 0;
    if (func_0032EB40(0xD, 0x10, 0) == 0)
        return 0;
    return func_003C2090(f, 0xF) != 0;
}

/* 0x003C9DE0, 0xFC bytes. */
int func_003C9DE0(void)
{
    if (func_00329540(0xF5) != 0 || func_00327C70() < 0x1F || func_00327820() != 0xD)
        return 0;
    return bond_event(0xF5, 0x1F, 0x11, func_00337A10(0xBB), 0, 0xF);
}

/* 0x003C9EE0, 0x80 bytes. */
int func_003C9EE0(void)
{
    if (func_00329540(0xF6) != 0 || func_00327C70() < 0x15 || func_00327820() != 0xD)
        return 0;
    return KNOWS(0x11, 0);
}

/* 0x003C9F60, 0x78 bytes. */
int func_003C9F60(void)
{
    return pair_event(0xF7, 0xD, 0x17);
}

/* 0x003C9FE0, 0x80 bytes. */
int func_003C9FE0(void)
{
    return func_00329540(0xF8) == 0 && face(0xD, 0x16);
}

/* 0x003CA060, 0x80 bytes. */
int func_003CA060(void)
{
    return func_00329540(0xF9) == 0 && face(0xD, 0x18);
}

/* Event `ev` (once): player `p` with officer `x`. */
static int with_event(int ev, int p, int x)
{
    if (func_00329540(ev) != 0 || func_00327820() != p)
        return 0;
    return func_00337A10(x) == func_0032E950();
}

/* 0x003CA0E0, 0x68 bytes. */
int func_003CA0E0(void)
{
    return with_event(0xFA, 0x12, 0xD7);
}

/* 0x003CA150, 0x68 bytes. */
int func_003CA150(void)
{
    return with_event(0xFB, 0xD, 0xD7);
}

/* 0x003CA1C0, 0x68 bytes. */
int func_003CA1C0(void)
{
    return with_event(0xFC, 0xD, 0xAB);
}

/* Whether officer value `v` (or func_0032EAC0) is high enough (always in mode 10 when
 * func_0032EAC0 is 0x29 or more). */
static int late_enough(int v)
{
    if (func_00327C00() != 10 && v <= 0x27 && func_0032EAC0() <= 0x28)
        return 0;
    if (func_00327C00() == 10 && func_0032EAC0() < 0x29)
        return 0;
    return func_00337A10(0xAB) == func_0032E950();
}

/* 0x003CA230, 0x160 bytes. */
int func_003CA230(void)
{
    int v = func_002F7550(0x12), k;

    if (func_00329540(0xFD) != 0 || func_00327820() != 0x12 || late_enough(v) == 0)
        return 0;
    if (func_002F3BB0(5) == 0 || func_002F3BB0(0xD) == 0)
        return 0;
    k = func_00328270();
    return k == 1 || func_00328270() == 2 || func_00328270() == 4;
}

/* 0x003CA390, 0x194 bytes. */
int func_003CA390(void)
{
    int v = func_002F7550(5), k;

    if (func_00329540(0xFE) != 0 || !KNOWS(5, 1) || late_enough(v) == 0)
        return 0;
    if (func_002F3BB0(0x12) == 0 || KNOWS(0x12, 1) || func_002F3BB0(0xD) == 0)
        return 0;
    k = func_00328270();
    return k == 2 || func_00328270() == 3 || func_00328270() == 4;
}

/* 0x003CA530, 0x78 bytes. */
int func_003CA530(void)
{
    return pair_event(0xFF, 0xE, 0);
}

/* 0x003CA5B0, 0x80 bytes. */
int func_003CA5B0(void)
{
    return func_00329540(0x100) == 0 && face(0xE, 1);
}

/* 0x003CA630, 0x70 bytes. */
int func_003CA630(void)
{
    if (func_00329540(0x101) != 0 || !KNOWS(0xE, 0))
        return 0;
    return KNOWS(4, 0);
}

/* Event `ev` (once): player `p` with officer 0xE (with `o`) alone at side 0's front, 0xE being
 * side 0's best. */
static int lead_event(int ev, int o, int p)
{
    if (func_00329540(ev) != 0 || func_003C23A0() == 0)
        return 0;
    if (func_0032EC50(func_00327820(), 0xE, o, 1) == 0)
        return 0;
    if (func_003C27A0(0, 0xE, 0x19F, 0x19F, 0x19F) != 1 || func_00327820() != p)
        return 0;
    if (func_0036B260() == 0)
        return 0;
    return func_003C2E90(0xE, 1) != 0;
}

/* 0x003CA6A0, 0xE0 bytes. */
int func_003CA6A0(void)
{
    return lead_event(0x102, 2, 2);
}

/* 0x003CA780, 0xE0 bytes. */
int func_003CA780(void)
{
    return lead_event(0x103, 0xD, 0xD);
}
