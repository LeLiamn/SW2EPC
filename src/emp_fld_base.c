/*
 * emp_fld_base.c - the Empire mode's battlefield bases and units (probably the original
 * emp_FldBase.c, which is referenced at 0x0034F5A0; its exact start is unknown). Written so far:
 * parts of 0x0034A430-.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Units are the battle officer records (0x88 bytes each at 0x00693970: 0-0xF bodyguards?,
 * 0x10-0x169 by side and slot, 0x170-0x1A1 ..., 0x1A2-0x1AB reserves); +0x08 a pointer into the
 * table at 0x005BA6A0 (0x2C bytes per entry), +0x10 its soldier group (0x47 = none), +0x40 a
 * position code, +0x75 / +0x79 bytes, +0x80 flags (bit 0 = in use).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00693970[];                  /* the game state (unit records first) */
extern u8 g_006A1D58[][0x68];            /* the soldier groups */
extern int g_005BA6A0;                   /* (pointer) the officer table */

#define UNIT(i) (g_00693970 + (i) * 0x88)
#define UNIT_FLAGS(u) (*(u32 *)((u8 *)(u) + 0x80))
#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)

u8 *func_00347980(void);
u8 *func_00347900(int a, int b);
int func_0034ED90(u8 *u, short *out);
int func_0035D560(int a, int b);
u16 *func_00338410(int g);
u8 *func_0033EFD0(int side, int k);
int func_0034EC80(int k);
int func_0036D310(void);
int func_00362320(int side);
int func_00362160(int a, int b);
int func_0034AF30(u8 *u, int a, int b);

/* 0x0034A430, 8 bytes, matching. */
/* 0x0034A430, 0x8 bytes, matching. */
void func_0034A430(u8 *u, u8 v)
{
    u[0x75] = v;
}

/* 0x0034A440, 8 bytes, matching. */
/* 0x0034A440, 0x8 bytes, matching. */
u8 func_0034A440(u8 *u)
{
    return u[0x75];
}

/* 0x0034A450-0x0034A590, 0x20 bytes each. The halfwords of func_00347980's record. */
/* 0x0034A450, 0x20 bytes, matching. */
u16 func_0034A450(void) { return *(u16 *)(func_00347980() + 4); }
/* 0x0034A470, 0x20 bytes, matching. */
u16 func_0034A470(void) { return *(u16 *)(func_00347980() + 0xC); }
/* 0x0034A490, 0x20 bytes, matching. */
u16 func_0034A490(void) { return *(u16 *)(func_00347980() + 0xE); }
/* 0x0034A4B0, 0x20 bytes, matching. */
u16 func_0034A4B0(void) { return *(u16 *)(func_00347980() + 0x10); }
/* 0x0034A4D0, 0x20 bytes, matching. */
u16 func_0034A4D0(void) { return *(u16 *)(func_00347980() + 0x12); }
/* 0x0034A4F0, 0x20 bytes, matching. */
u16 func_0034A4F0(void) { return *(u16 *)(func_00347980() + 0x14); }
/* 0x0034A510, 0x20 bytes, matching. */
u16 func_0034A510(void) { return *(u16 *)(func_00347980() + 0x16); }
/* 0x0034A530, 0x20 bytes, matching. */
u16 func_0034A530(void) { return *(u16 *)(func_00347980() + 0x18); }
/* 0x0034A550, 0x20 bytes, matching. */
u16 func_0034A550(void) { return *(u16 *)(func_00347980() + 6); }
/* 0x0034A570, 0x20 bytes, matching. */
u16 func_0034A570(void) { return *(u16 *)(func_00347980() + 0x1A); }
/* 0x0034A590, 0x20 bytes, matching. */
u16 func_0034A590(void) { return *(u16 *)(func_00347980() + 0x1C); }

/* 0x0034A5B0, 0x34 bytes. Unit `u`'s record value +0x0A (func_00347900 of its +0x79 / +0x75). */
u16 func_0034A5B0(u8 *u)
{
    return *(u16 *)(func_00347900(u[0x79], func_0034A440(u)) + 10);
}

/* 0x0034A5F0, 0x34 bytes. The same record's byte +8. */
u8 func_0034A5F0(u8 *u)
{
    return func_00347900(u[0x79], func_0034A440(u))[8];
}

/* 0x0034A630, 0x2C bytes. Whether unit `u` has flag 0x400 or 0x10000000. */
int func_0034A630(u8 *u)
{
    return (UNIT_FLAGS(u) & 0x400) != 0 || (UNIT_FLAGS(u) & 0x10000000) != 0;
}

/* 0x0034A660, 0x54 bytes. Whether unit `b`'s position code is unit `a`'s. */
int func_0034A660(u8 *a, u8 *b)
{
    short s[2];

    if (a == 0 || b == 0)
        return 0;
    func_0034ED90(b, s);
    return s[0] == *(short *)(a + 0x40);
}

/* 0x0034A6C0, 0x30 bytes. Whether units `a` and `b` share a position code. */
int func_0034A6C0(u8 *a, u8 *b)
{
    if (a == 0 || b == 0)
        return 0;
    return *(short *)(a + 0x40) == *(short *)(b + 0x40);
}

/* 0x0034A6F0, 0x20 bytes, matching. func_0035D560 of the two units' +0x79 bytes. */
int func_0034A6F0(u8 *a, u8 *b)
{
    return func_0035D560(a[0x79], b[0x79]);
}

/* 0x0034A710, 0x24 bytes. */
int func_0034A710(u8 *a, u8 *b)
{
    return func_0034A6F0(a, b) == 0;
}

/* 0x0034A740, 0x48 bytes. Unit `u`'s soldier group (0 for none). */
u8 *func_0034A740(u8 *u)
{
    int g = *(int *)(u + 0x10);

    if (g == 0x47)
        return 0;
    return g_006A1D58[g];
}

/* 0x0034A790, 0x60 bytes, matching. The officer of unit `u`'s group (0x19F for none). */
u16 func_0034A790(u8 *u)
{
    u8 *g = func_0034A740(u);

    if (g == 0)
        return 0x19F;
    return *func_00338410(GROUP_INDEX(g));
}

/* 0x0034A7F0, 0xA0 bytes. The slot (0-0x13) of unit `u`'s group among both sides' slots;
 * 0x1AD without flag 0x10000000, 0x14 when not found. */
u32 func_0034A7F0(u8 *u)
{
    u8 *g;
    u32 s, k;

    if ((UNIT_FLAGS(u) & 0x10000000) == 0)
        return 0x1AD;
    g = func_0034A740(u);
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 0x14; k++) {
            if (func_0033EFD0(s, k) == g)
                return k;
        }
    }
    return 0x14;
}

/* 0x0034A890, 0x3C bytes, matching. */
int func_0034A890(u8 *u)
{
    u32 k = func_0034A7F0(u);

    return k < 0x14 ? func_0034EC80(k) : 0;
}

/* 0x0034A8D0-0x0034A9C0. Unit numbers: the bodyguards `i`, side `s`'s slot `k` (0x10), its five
 * escorts (0x3A), their sub-slots (0x8A), and three more blocks (0x166, 0x170, 0x184), the
 * reserves (0x1A2). */
/* 0x0034A8D0, 0x8 bytes, matching. */
int func_0034A8D0(int i) { return i; }
/* 0x0034A8E0, 0x18 bytes. */
int func_0034A8E0(int s, int k) { return k + s * 0x14 + 0x10; }
/* 0x0034A900, 0x14 bytes. */
int func_0034A900(int s, int k) { return k + s * 5 + 0x3A; }
/* 0x0034A920, 0x24 bytes. */
int func_0034A920(int s, int k, int j) { return j + (k + s * 0x14) * 5 + 0x8A; }
/* 0x0034A950, 0x18 bytes. */
int func_0034A950(int s, int k, int j) { return (s + k) * 5 + 0x166 + j; }
/* 0x0034A970, 0x24 bytes. */
int func_0034A970(int s, int k, int j) { return j + s * 10 + 0x170 + k * 5; }
/* 0x0034A9A0, 0x20 bytes. */
int func_0034A9A0(int s, int k, int j) { return j + s * 0xF + 0x184 + k * 5; }
/* 0x0034A9C0, 0x8 bytes, matching. */
int func_0034A9C0(int i) { return i + 0x1A2; }

/* 0x0034A9D0-0x0034AB90, 0x34 bytes each. The same as unit records. */
/* 0x0034A9D0, 0x34 bytes, matching. */
u8 *func_0034A9D0(int i) { return UNIT(func_0034A8D0(i)); }
/* 0x0034AA10, 0x34 bytes, matching. */
u8 *func_0034AA10(int s, int k) { return UNIT(func_0034A8E0(s, k)); }
/* 0x0034AA50, 0x34 bytes, matching. */
u8 *func_0034AA50(int s, int k) { return UNIT(func_0034A900(s, k)); }
/* 0x0034AA90, 0x34 bytes, matching. */
u8 *func_0034AA90(int s, int k, int j) { return UNIT(func_0034A920(s, k, j)); }
/* 0x0034AAD0, 0x34 bytes, matching. */
u8 *func_0034AAD0(int s, int k, int j) { return UNIT(func_0034A950(s, k, j)); }
/* 0x0034AB10, 0x34 bytes, matching. */
u8 *func_0034AB10(int s, int k, int j) { return UNIT(func_0034A970(s, k, j)); }
/* 0x0034AB50, 0x34 bytes, matching. */
u8 *func_0034AB50(int s, int k, int j) { return UNIT(func_0034A9A0(s, k, j)); }
/* 0x0034AB90, 0x34 bytes, matching. */
u8 *func_0034AB90(int i) { return UNIT(func_0034A9C0(i)); }

/* 0x0034ABD0, 0x64 bytes. A free escort unit of side `s` (0 for none). */
u8 *func_0034ABD0(int s)
{
    int k;

    for (k = 0; k < 5; k++) {
        u8 *u = func_0034AA50(s, k);

        if ((UNIT_FLAGS(u) & 1) == 0)
            return u;
    }
    return 0;
}

/* 0x0034AC40, 0xC4 bytes. A free sub-slot unit of side `s`'s slot `k` (side 1 may then take any
 * free escort, with func_0036D310). */
u8 *func_0034AC40(int s, int k)
{
    int j;

    for (j = 0; j < 5; j++) {
        u8 *u = func_0034AA90(s, k, j);

        if ((UNIT_FLAGS(u) & 1) == 0)
            return u;
    }
    if (func_0036D310() != 0 && s == 1) {
        for (j = 0; j < 0x10; j++) {
            u8 *u = func_0034ABD0(j);

            if (u != 0)
                return u;
        }
    }
    return 0;
}

/* 0x0034AD10, 0x54 bytes. A free reserve unit (0 for none). */
u8 *func_0034AD10(void)
{
    int k;

    for (k = 0; k < 10; k++) {
        u8 *u = func_0034AB90(k);

        if ((UNIT_FLAGS(u) & 1) == 0)
            return u;
    }
    return 0;
}

/* 0x0034AD70, 0xB0 bytes. Whether unit `u` is officer `i` (side 0 / 1 by flags 0x10 / 0x20 through
 * the side's table, else by its officer table entry). */
int func_0034AD70(u8 *u, int i)
{
    int side, x;

    if (UNIT_FLAGS(u) & 0x10)
        side = 0;
    else if (UNIT_FLAGS(u) & 0x20)
        side = 1;
    else
        side = 2;
    if (side == 2)
        x = (*(int *)(u + 8) - g_005BA6A0) / 0x2C;
    else
        x = func_00362160(u[0x79], func_00362320(side));
    return x == i;
}

/* 0x0034AE20, 0x104 bytes. The units `lo`-`hi` in use (and passing `test` with `a`, `b`) into
 * `out`, at most `max`; their count. */
u32 func_0034AE20(u32 *out, u32 max, int (*test)(u8 *, int, int), u32 lo, u32 hi, int a, int b)
{
    u32 n = 0;
    u8 *u = UNIT(lo);

    for (; lo < hi; lo++, u += 0x88) {
        if (n >= max)
            return n;
        if (u != 0 && (UNIT_FLAGS(u) & 1) != 0 && (test == 0 || test(u, a, b) != 0)) {
            *out++ = lo;
            n++;
        }
    }
    return n;
}

/* 0x0034AFA0, 0x30 bytes, matching. The same for units 0x170-0x183 with func_0034AF30. */
u32 func_0034AFA0(u32 *out, u32 max, int a)
{
    return func_0034AE20(out, max, func_0034AF30, 0x170, 0x184, a, 0);
}

/* 0x0034AFD0, 0xD0 bytes. The first unit `lo`-`hi` in use passing `test` (0 for none). */
u8 *func_0034AFD0(int (*test)(u8 *, int, int), u32 lo, u32 hi, int a, int b)
{
    u8 *u = UNIT(lo);

    for (; lo < hi; lo++, u += 0x88) {
        if (u != 0 && (UNIT_FLAGS(u) & 1) != 0) {
            if (test == 0)
                return u;
            if (test(u, a, b) != 0)
                return u;
        }
    }
    return 0;
}

/* 0x0034B0A0, 0x28 bytes, matching. The same over all units. */
u8 *func_0034B0A0(int (*test)(u8 *, int, int), int a, int b)
{
    return func_0034AFD0(test, 0, 0x1AD, a, b);
}

/* 0x0034B0D0, 0x28 bytes, matching. Officer `i`'s unit. */
u8 *func_0034B0D0(int i)
{
    return func_0034B0A0((int (*)(u8 *, int, int))func_0034AD70, i, 0);
}

/* 0x0034B100, 0x28 bytes, matching. The same over the bodyguards. */
u8 *func_0034B100(int (*test)(u8 *, int, int), int a, int b)
{
    return func_0034AFD0(test, 0, 0x10, a, b);
}

/* 0x0034B130, 0x28 bytes, matching. Officer `i`'s bodyguard unit. */
u8 *func_0034B130(int i)
{
    return func_0034B100((int (*)(u8 *, int, int))func_0034AD70, i, 0);
}

/* 0x0034B160, 0x24 bytes. The index of entry `p` of the 16-byte table at 0x006AA5F4. */
int func_0034B160(int p)
{
    int d = p - 0x6AA5F4;

    if (d < 0)
        d = p - 0x6AA5E5;
    return d >> 4;
}

/* The two sides' 16-byte war states (0x006AA5F4 = game state +0x16C84). */
#define SIDE_STATE(s) (g_00693970 + 0x16C84 + (s) * 0x10)

extern void (*g_004154E0[4])(u8 *g);     /* by side state: what its groups do */
extern u8 g_00669F60;                    /* settings flags */
extern int g_00669F9C, g_00669FA0;
extern int g_006AA624;
#define g_7000015C (*(u32 *)0x7000015C)   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_003385E0(u8 *g, int a, int b);
u8 *func_00347880(u8 *g, int a, int b);
u8 *func_003478A0(u8 *g);
u8 *func_003478C0(u8 *g, int a, int b);
u8 *func_003478E0(u8 *g);
int func_0034ED40(u8 *u);
u8 *func_0033EF80(int k);
void func_00118AC0(void *to, const void *from, int n);
void func_00118850(void *p, int n);
int func_0035D5A0(int a);
void func_00364E40(int a, int g);
void func_00365050(int a);
int func_0033B150(u8 *g);
int func_0033B580(u8 *g);

/* Whether a group's unit is active (in use, none of flags 0x8C40002 and 4). */
#define UNIT_ACTIVE(f) (((f) & 1) != 0 && ((f) & 0x8C40002) == 0 && ((f) & 4) == 0)
/* A group's unit record and info record. */
#define GROUP_UNIT(g) (*(u8 **)(g))
#define GROUP_INFO(g) ((u8 *)func_00338410(GROUP_INDEX(g)))

/* 0x0034B190, 0x154 bytes. Side 0's soldier group `g` picks its order (by its kind: 1 and 2 fixed,
 * else toward a unit found by func_00347880, a group from func_003478A0, or none). */
void func_0034B190(u8 *g)
{
    u8 st = GROUP_INFO(g)[8], kind, *info, *u;

    GROUP_INFO(g);
    kind = GROUP_INFO(g)[2];
    info = GROUP_INFO(g);
    if (st < 2)
        return;
    if (kind == 1) {
        func_003385E0(g, 0, info[3]);
    } else if (kind == 2) {
        func_003385E0(g, 1, info[3]);
    } else {
        u = func_00347880(g, 1, info[3]);
        if (u != 0) {
            func_003385E0(g, 0, func_0034ED40(u));
        } else {
            u = func_003478A0(g);
            if (u == 0)
                func_003385E0(g, 4, 0xFF);
            else
                func_003385E0(g, 1, GROUP_INDEX(u));
        }
    }
}

/* 0x0034B2F0, 0x134 bytes. The same for side 1's groups (kind 3 fixed). */
void func_0034B2F0(u8 *g)
{
    u8 st = GROUP_INFO(g)[8], kind, *info, *u;

    GROUP_INFO(g);
    kind = GROUP_INFO(g)[2];
    info = GROUP_INFO(g);
    if (st == 2)
        return;
    if (kind == 3) {
        func_003385E0(g, 2, info[3]);
    } else {
        u = func_003478C0(g, 2, info[3]);
        if (u != 0) {
            func_003385E0(g, 2, func_0034ED40(u));
        } else {
            u = func_003478E0(g);
            if (u == 0)
                func_003385E0(g, 4, 0xFF);
            else
                func_003385E0(g, 3, GROUP_INDEX(u));
        }
    }
}

/* 0x0034B430, 0x40 bytes. Group `g` follows its side's target (order 3). */
void func_0034B430(u8 *g)
{
    func_003385E0(g, 3, SIDE_STATE(GROUP_UNIT(g)[0x79])[1]);
}

/* 0x0034B470, 0x20 bytes, matching. Group `g` has no order. */
void func_0034B470(u8 *g)
{
    func_003385E0(g, 4, 0xFF);
}

/* 0x0034B490, 0x140 bytes. Side state `st`'s active groups (not flagged 0x30) take its order. */
void func_0034B490(u8 *st)
{
    void (*tbl[4])(u8 *);
    u8 mode = st[0];
    int side, k;

    tbl[0] = g_004154E0[0];
    tbl[1] = g_004154E0[1];
    tbl[2] = g_004154E0[2];
    tbl[3] = g_004154E0[3];
    side = func_0034B160((int)st);
    for (k = 0; k < 0x10; k++) {
        u8 *g = func_0033EF80(k);

        if (g != 0 && (*(int *)(g + 0x64) & 1) != 0) {
            u8 *u = GROUP_UNIT(g);
            u32 f = UNIT_FLAGS(u);

            if (UNIT_ACTIVE(f) && side == u[0x79] && (f & 0x30) == 0 && tbl[mode] != 0)
                tbl[mode](g);
        }
    }
}

/* 0x0034B5D0, 0x90 bytes. Sets side state `st`'s order `a` / `b` (its groups follow; a changed
 * order counts once more, up to 0xFE). */
int func_0034B5D0(u8 *st, int a, int b)
{
    u8 oa = st[0], ob = st[1];

    st[0] = a;
    st[1] = b;
    func_0034B490(st);
    if ((u32)a != oa || (u32)b != ob) {
        if (st[a + 2] != 0xFF)
            st[a + 2]++;
    }
    return 1;
}

/* 0x0034B660, 0x20 bytes. */
int func_0034B660(int k)
{
    return k == 2;
}

/* 0x0034B680, 0x74 bytes. The group side state `st` aims at (order 2), else 0. */
u8 *func_0034B680(u8 *st)
{
    if (st == 0 || func_0034B660(st[0]) == 0)
        return 0;
    return g_006A1D58[st[1]];
}

/* 0x0034B700, 0x10 bytes, matching. */
int func_0034B700(u8 *p)
{
    return (p[6] & 3) + 1;
}

/* 0x0034B710, 0x10 bytes, matching. */
int func_0034B710(u8 *p)
{
    return (p[6] & 3) + 5;
}

/* 0x0034B720, 0x34 bytes. Bit 6 of `p[6]` when settings flag 2 is on. */
u8 func_0034B720(u8 *p)
{
    if ((g_00669F60 & 2) == 0)
        return 0;
    return p[6] >> 6 & 1;
}

/* 0x0034B760, 0x64 bytes. A random delay (60-239, scaled by setting +0x240 / 90000). */
int func_0034B760(void)
{
    return (int)((RANDOM() % 0xB4 + 0x3C) * g_00669FA0) / 90000;
}

/* 0x0034B7D0, 0x6C bytes. Saves both side states to `p`; returns past them. */
u8 *func_0034B7D0(u8 *p)
{
    u32 k;

    for (k = 0; k < 2; k++, p += 0x10)
        func_00118AC0(p, SIDE_STATE(k), 0x10);
    return p;
}

/* 0x0034B840, 0x6C bytes. Loads them back. */
u8 *func_0034B840(u8 *p)
{
    u32 k;

    for (k = 0; k < 2; k++, p += 0x10)
        func_00118AC0(SIDE_STATE(k), p, 0x10);
    return p;
}

/* 0x0034B8B0, 0xCC bytes. Resets both side states (order 3 to none, a random byte, a delay). */
void func_0034B8B0(void)
{
    u32 k;

    for (k = 0; k < 2; k++) {
        u8 *e = SIDE_STATE(k);

        func_00118850(e, 0x10);
        e[0] = 3;
        e[1] = 0xFF;
        e[2] = 0;
        e[3] = 0;
        e[4] = 0;
        e[5] = 0;
        e[6] = RANDOM() % 0xFF;
        e[7] = 0;
        e[8] = 0;
        e[9] = func_0034B760();
        e[10] = 0;
    }
    g_006AA624 = 0;
}

/* 0x0034B980, 8 bytes, matching. */
void func_0034B980(void)
{
}

/* 0x0034B990, 8 bytes, matching. */
void func_0034B990(void)
{
}

/* 0x0034B9A0, 0x60 bytes. Every 50 frames, for sides 0-1 (func_0034B990, empty). */
void func_0034B9A0(void)
{
    if ((u32)(g_00669F9C % 0x32) < 2 && (u32)SIDE_STATE(g_00669F9C % 0x32) != 0)
        func_0034B990();
}

/* 0x0034BA00, 0xA8 bytes. Marks group `g`'s side state (kind 1 groups, or when `force`). */
void func_0034BA00(u8 *g, int force)
{
    if (GROUP_INFO(g)[2] == 1 || force == 1)
        SIDE_STATE(func_0035D5A0(GROUP_UNIT(g)[0x79]))[8] |= 1;
}

/* 0x0034BAB0, 0x2C bytes, matching. Marks both side states. */
void func_0034BAB0(void)
{
    SIDE_STATE(0)[8] |= 1;
    SIDE_STATE(1)[8] |= 1;
}

/* 0x0034BAE0, 0x38 bytes. Marks group `g`'s own side state. */
void func_0034BAE0(u8 *g)
{
    SIDE_STATE(GROUP_UNIT(g)[0x79])[8] |= 1;
}

/* 0x0034BB20, 0x2C bytes, matching. The same as func_0034BAB0. */
void func_0034BB20(void)
{
    SIDE_STATE(0)[8] |= 1;
    SIDE_STATE(1)[8] |= 1;
}

/* 0x0034BB50, 0xE4 bytes, matching. Lists the groups in use passing `test` (with `x`, `y`) into list `a`. */
void func_0034BB50(int a, int (*test)(u8 *, int, int), int x, int y)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 *g = func_0033EF80(k);

        if (g != 0 && (*(u32 *)(g + 100) & 1) != 0 && (test == 0 || test(g, x, y) != 0))
            func_00364E40(a, GROUP_INDEX(g));
    }
    func_00365050(a);
}

/* 0x0034BC40, 0xD8 bytes. Whether group `g` is an active, free group of side `side`. */
int func_0034BC40(u8 *g, u32 side)
{
    u32 f = UNIT_FLAGS(GROUP_UNIT(g));

    if (!UNIT_ACTIVE(f) || (f & 0x30) != 0 || side != GROUP_UNIT(g)[0x79])
        return 0;
    if (func_0033B150(g) != 0)
        return 0;
    return func_0033B580(g) == 0;
}

/* 0x0034BD20, 0x28 bytes, matching. Side `side`'s free groups into list `a`. */
void func_0034BD20(int a, int side)
{
    func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BC40, side, 0);
}

/* 0x0034BD50, 0x128 bytes. Whether group `g` is active, of side `side`, with info bytes +5 / +6
 * matching `key` (high / low halves; low 0xFF = any). */
int func_0034BD50(u8 *g, u32 side, u32 key)
{
    u32 f = UNIT_FLAGS(GROUP_UNIT(g));

    if (!UNIT_ACTIVE(f) || side != GROUP_UNIT(g)[0x79])
        return 0;
    if (key >> 0x10 != GROUP_INFO(g)[5])
        return 0;
    return (key & 0xFFFF) == 0xFF || (key & 0xFFFF) == GROUP_INFO(g)[6];
}

/* 0x0034BE80, 0x30 bytes, matching. Such groups into list `a`. */
void func_0034BE80(int a, int side, int k, u32 j)
{
    func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BD50, side, k << 0x10 | j);
}

/* 0x0034BEB0, 0x128 bytes. The same with info bytes +8 / +9. */
int func_0034BEB0(u8 *g, u32 side, u32 key)
{
    u32 f = UNIT_FLAGS(GROUP_UNIT(g));

    if (!UNIT_ACTIVE(f) || side != GROUP_UNIT(g)[0x79])
        return 0;
    if (key >> 0x10 != GROUP_INFO(g)[8])
        return 0;
    return (key & 0xFFFF) == 0xFF || (key & 0xFFFF) == GROUP_INFO(g)[9];
}

/* 0x0034BFE0, 0x30 bytes, matching. Such groups into list `a`. */
void func_0034BFE0(int a, int side, int k, u32 j)
{
    func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BEB0, side, k << 0x10 | j);
}

void func_00365230(int list);
int func_00365350(int list, int (*score)(int, int), int a, int b);
u32 func_0034EEF0(u8 *b);
u8 *func_0034EF60(u8 *b, u32 k);
int func_0034EDB0(u8 *b);
int func_0034EE50(u8 *b);
int func_0034EE80(u8 *b);
int func_0033C320(u8 *g);
int func_0033C3A0(u8 *g);
int func_0033CB60(u8 *g, u8 *b);
int func_003521B0(u8 *b, int side);
int func_003522F0(u8 *b, int side);
int func_00347800(u8 *g, int b);
int func_00347820(u8 *g, int h);
int func_00347840(u8 *g, int b);
int func_003DCE70(u8 *g, u8 *b);
u32 func_003DCE30(u8 *g, u8 *h);
int func_0035F200(int s);
u32 func_00352B00(u8 *b, int c);

#define BASE(k) ((u8 *)func_0034EC80(k))

/* 0x0034C010, 0xB4 bytes, matching. The bases linked to base `b` not owned by `skip`, into list `l`. */
void func_0034C010(int l, u8 *b, int skip)
{
    u32 n, k;

    func_00365230(l);
    n = func_0034EEF0(b);
    for (k = 0; k < n; k++) {
        u8 *x = func_0034EF60(b, k);

        if (skip != func_0034EDB0(x))
            func_00364E40(l, func_0034ED40(x));
    }
    func_00365050(l);
}

/* 0x0034C0D0, 0x198 bytes. Side `side`'s bases where one of its groups is (a kind 1 group's own
 * base, or a flagged unit's func_0033CB60), into list `l`. */
void func_0034C0D0(int l, int side)
{
    int s = func_0035D5A0(side);
    u32 b, k;

    func_00365230(l);
    for (b = 0; b < 0x14; b++) {
        u8 *B = BASE(b);

        if (B == 0 || func_0034EE50(B) == 0 || func_0034EDB0(B) != side)
            continue;
        for (k = 0; k < 0x10; k++) {
            u8 *g = func_0033EF80(k), *u;

            if (g == 0 || (*(int *)(g + 0x64) & 1) == 0)
                continue;
            u = GROUP_UNIT(g);
            if (s != u[0x79])
                continue;
            if ((UNIT_FLAGS(u) & 0x30) == 0) {
                if (GROUP_INFO(g)[2] == 1 && (u8 *)func_0033C320(g) == B) {
                    func_00364E40(l, b);
                    break;
                }
            } else if (func_0033CB60(g, B) != 0) {
                func_00364E40(l, b);
                break;
            }
        }
    }
    func_00365050(l);
}

/* 0x0034C270, 0xF0 bytes, matching. The bases side `side` does not own and may take (func_003521B0; only
 * unowned ones with `free`), into list `l`. */
void func_0034C270(int l, int side, int free)
{
    u32 b;

    func_00365230(l);
    for (b = 0; b < 0x14; b++) {
        u8 *B = BASE(b);

        if (B == 0 || func_0034EE50(B) == 0 || func_0034EDB0(B) == side)
            continue;
        if (free != 0) {
            func_0034EDB0(B);
            if ((u32)func_0034EDB0(B) < 2)
                continue;
        }
        if (func_0034EE80(B) != side && func_003521B0(B, side) != 0)
            func_00364E40(l, b);
    }
    func_00365050(l);
}

/* 0x0034C360, 0x104 bytes. How much group `g` wants base `B` (0 when it cannot go; kind 1's own
 * base 10001, plus nearness). */
int func_0034C360(u8 *g, u8 *B)
{
    int v, d;

    if (func_00347800(g, func_0034ED40(B)) == 0)
        return 0;
    v = 1;
    if (GROUP_INFO(g)[2] == 1 && (u8 *)func_0033C320(g) == B)
        v = 0x2711;
    d = func_003DCE70(g, B);
    if (d < 0x14)
        v += (0x14 - d) * 1000 / 0x14;
    return v;
}

/* 0x0034C470, 0x118 bytes. How much group `g` wants to go to group `h` (kind 2's own target
 * 10001, plus nearness). */
int func_0034C470(u8 *g, u8 *h)
{
    int v;
    u32 d;

    if (func_00347820(g, GROUP_INDEX(h)) == 0)
        return 0;
    if (func_0033B150(g) != 0)
        return 0;
    v = 1;
    if (GROUP_INFO(g)[2] == 2 && (u8 *)func_0033C3A0(g) == h)
        v = 0x2711;
    d = func_003DCE30(g, h);
    if (d < 0x14)
        v += (20000 - d) / 0x14;
    return v;
}

/* 0x0034C590, 0xFC bytes. The same as func_0034C360 for func_00347840 and kind 3. */
int func_0034C590(u8 *g, u8 *B)
{
    int v;
    u32 d;

    if (func_00347840(g, func_0034ED40(B)) == 0)
        return 0;
    v = 1;
    if (GROUP_INFO(g)[2] == 3 && (u8 *)func_0033C320(g) == B)
        v = 0x2711;
    d = func_003DCE70(g, B);
    if (d < 0x14)
        v += (u32)((0x14 - d) * 1000) / 0x14;
    return v;
}

/* 0x0034C690, 0x58 bytes. func_0034C360 by numbers. */
int func_0034C690(int gi, int b)
{
    return func_0034C360(g_006A1D58[gi], BASE(b));
}

/* 0x0034C6F0, 0x68 bytes. The group of list `l` that most wants base `B`. */
u8 *func_0034C6F0(int l, u8 *B)
{
    return g_006A1D58[func_00365350(l, func_0034C690, func_0034ED40(B), 0)];
}

/* 0x0034C760, 0x60 bytes. func_0034C470 by numbers. */
int func_0034C760(int gi, int hi)
{
    return func_0034C470(g_006A1D58[gi], g_006A1D58[hi]);
}

/* 0x0034C7C0, 0x74 bytes. The group of list `l` that most wants to go to group `h`. */
u8 *func_0034C7C0(int l, u8 *h)
{
    return g_006A1D58[func_00365350(l, func_0034C760, GROUP_INDEX(h), 0)];
}

/* 0x0034C840, 0x58 bytes. func_0034C590 by numbers. */
int func_0034C840(int gi, int b)
{
    return func_0034C590(g_006A1D58[gi], BASE(b));
}

/* 0x0034C8A0, 0x68 bytes. The group of list `l` that most wants base `B` (func_0034C590). */
u8 *func_0034C8A0(int l, u8 *B)
{
    return g_006A1D58[func_00365350(l, func_0034C840, func_0034ED40(B), 0)];
}

/* Side `side`'s distance value (0-100) from base `B` to its own main base. */
static int near_main(u8 *B, int side)
{
    u32 n = func_00352B00(B, func_0034EC80(func_0035F200(func_0035D5A0(side))));

    return n < 3 ? (u32)((3 - n) * 100) / 3 : 0;
}

/* 0x0034C910, 0xCC bytes. How much side `side` wants enemy base `B` (1000 when it can take it,
 * plus nearness to its main base). */
int func_0034C910(u8 *B, int side)
{
    if (side == func_0034EDB0(B))
        return 0;
    if (func_003521B0(B, side) == 0)
        return 0;
    return 1000 + near_main(B, side);
}

/* 0x0034C9E0, 0xCC bytes. How much side `side` wants to hold its base `B` (func_003522F0). */
int func_0034C9E0(u8 *B, int side)
{
    if (side != func_0034EDB0(B))
        return 0;
    if (func_003522F0(B, side) == 0)
        return 0;
    return 1000 + near_main(B, side);
}
