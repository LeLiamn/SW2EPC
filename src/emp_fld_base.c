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
void func_0034ED90(u8 *b, u8 *out);
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
    func_0034ED90(b, (u8 *)s);
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
int func_00365050(int a);
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
/* 0x0034B980, 0x8 bytes, matching. */
void func_0034B980(void)
{
}

/* 0x0034B990, 8 bytes, matching. */
/* 0x0034B990, 0x8 bytes, matching. */
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
int func_0034BB50(int a, int (*test)(u8 *, int, int), int x, int y)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 *g = func_0033EF80(k);

        if (g != 0 && (*(u32 *)(g + 100) & 1) != 0 && (test == 0 || test(g, x, y) != 0))
            func_00364E40(a, GROUP_INDEX(g));
    }
    return func_00365050(a);
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
int func_0034BD20(int a, int side)
{
    return func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BC40, side, 0);
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
int func_0034BE80(int a, int side, int k, u32 j)
{
    return func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BD50, side, k << 0x10 | j);
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
int func_0034BFE0(int a, int side, int k, u32 j)
{
    return func_0034BB50(a, (int (*)(u8 *, int, int))func_0034BEB0, side, k << 0x10 | j);
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
int func_0034C010(int l, u8 *b, int skip)
{
    u32 n, k;

    func_00365230(l);
    n = func_0034EEF0(b);
    for (k = 0; k < n; k++) {
        u8 *x = func_0034EF60(b, k);

        if (skip != func_0034EDB0(x))
            func_00364E40(l, func_0034ED40(x));
    }
    return func_00365050(l);
}

/* 0x0034C0D0, 0x198 bytes. Side `side`'s bases where one of its groups is (a kind 1 group's own
 * base, or a flagged unit's func_0033CB60), into list `l`. */
int func_0034C0D0(int l, int side)
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
    return func_00365050(l);
}

/* 0x0034C270, 0xF0 bytes, matching. The bases side `side` does not own and may take (func_003521B0; only
 * unowned ones with `free`), into list `l`. */
int func_0034C270(int l, int side, int free)
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
    return func_00365050(l);
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

int func_003653D0(int l);
void func_003651F0(int l, int i);
int func_00365030(int l, int k);
void func_003653F0(int l, void *buf, int cap);
u8 *func_0035DD10(int which);
int func_0036D300(void);
int func_0033CEA0(u8 *g, int side);
int func_00352240(u8 *b, int s);
int func_003531F0(int k);
int func_003519E0(void);
int func_0035F0C0(void);

/* 0x0034CAB0, 0x30 bytes, matching. func_0034C910 by number. */
int func_0034CAB0(int b, int side)
{
    return func_0034C910(BASE(b), side);
}

/* 0x0034CAE0, 0x30 bytes, matching. The base of list `l` side `side` most wants to take. */
u8 *func_0034CAE0(int l, int side)
{
    return BASE(func_00365350(l, func_0034CAB0, side, 0));
}

/* 0x0034CB10, 0x30 bytes, matching. func_0034C9E0 by number. */
int func_0034CB10(int b, int side)
{
    return func_0034C9E0(BASE(b), side);
}

/* 0x0034CB40, 0x30 bytes, matching. The base of list `l` side `side` most wants to hold. */
u8 *func_0034CB40(int l, int side)
{
    return BASE(func_00365350(l, func_0034CB10, side, 0));
}

/* 0x0034CB70, 0xCC bytes. Sends up to `n` groups of list `l` (those wanting it most) to take
 * base `B`; how many. */
u32 func_0034CB70(int l, u8 *B, u32 n)
{
    u32 k;

    for (k = 0; k < n; k++) {
        u8 *g;

        if (func_003653D0(l) == 0)
            return k;
        g = func_0034C6F0(l, B);
        func_003651F0(l, GROUP_INDEX(g));
        func_003385E0(g, 0, func_0034ED40(B));
    }
    return k;
}

/* 0x0034CC40, 0xCC bytes. The same to hold base `B` (order 2). */
u32 func_0034CC40(int l, u8 *B, u32 n)
{
    u32 k;

    for (k = 0; k < n; k++) {
        u8 *g;

        if (func_003653D0(l) == 0)
            return k;
        g = func_0034C8A0(l, B);
        func_003651F0(l, GROUP_INDEX(g));
        func_003385E0(g, 2, func_0034ED40(B));
    }
    return k;
}

/* 0x0034CD10, 0x130 bytes. Sends up to `n` groups of list `l` to group func_0035DD10(`which`)
 * (order 1), unless func_0036D300 or func_0033CEA0. */
u32 func_0034CD10(int l, int which, u32 n)
{
    u8 *h = func_0035DD10(which);
    u32 k;

    if (func_0036D300() != 0 || func_0033CEA0(h, GROUP_UNIT(h)[0x79]) != 0)
        return 0;
    for (k = 0; k < n; k++) {
        u8 *g;

        if (func_003653D0(l) == 0)
            return k;
        g = func_0034C7C0(l, h);
        func_003651F0(l, GROUP_INDEX(g));
        func_003385E0(g, 1, GROUP_INDEX(h));
    }
    return k;
}

/* 0x0034CE40, 0xE0 bytes. Gives up to `n` groups of list `l` no order. */
u32 func_0034CE40(int l, u32 n)
{
    u32 k;

    for (k = 0; k < n; k++) {
        int i;

        if (func_003653D0(l) == 0)
            return k;
        i = func_00365030(l, 0);
        func_003651F0(l, i * 0x68 / 0x68);
        func_003385E0(g_006A1D58[i], 4, 0xFF);
    }
    return k;
}

/* 0x0034CF20, 0x11C bytes. Sends up to `n` groups of list `l`, at most `per` per base, to take
 * the bases of list `bl` side `side` wants most; how many. */
u32 func_0034CF20(int l, u32 n, int bl, u32 per, int side)
{
    u32 k, c;

    for (k = 0; func_003653D0(l) != 0 && func_003653D0(bl) != 0 && k < n; k += c) {
        u8 *B = func_0034CAE0(bl, side);

        c = func_00365050(l);
        if (per < c)
            c = per;
        if (c > n - k)
            c = n - k;
        func_0034CB70(l, B, c);
        func_003651F0(bl, func_0034ED40(B));
    }
    return k;
}

/* 0x0034D040, 0x11C bytes. The same to hold the bases of list `bl`. */
u32 func_0034D040(int l, u32 n, int bl, u32 per, int side)
{
    u32 k, c;

    for (k = 0; func_003653D0(l) != 0 && func_003653D0(bl) != 0 && k < n; k += c) {
        u8 *B = func_0034CB40(bl, side);

        c = func_00365050(l);
        if (per < c)
            c = per;
        if (c > n - k)
            c = n - k;
        func_0034CC40(l, B, c);
        func_003651F0(bl, func_0034ED40(B));
    }
    return k;
}

/* 0x0034D160, 8 bytes, matching. */
/* 0x0034D160, 0x8 bytes, matching. */
u32 func_0034D160(void)
{
    return 1;
}

/* 0x0034D170, 8 bytes, matching. */
/* 0x0034D170, 0x8 bytes, matching. */
void func_0034D170(void)
{
}

/* 0x0034D180, 0xFC bytes. Side state `st`'s plan (+7): 9 when its main base is threatened,
 * 10 when it holds 31% of the bases or more, else by its kind; a change marks it. */
void func_0034D180(u8 *st)
{
    int side = func_0034B160((int)st), s, m;
    u8 *main = BASE(func_0035F200(side)), cur = st[7];

    s = func_0035D5A0(side);
    if (func_00352240(main, s) != 0) {
        m = 9;
    } else if ((u32)(func_003531F0(3) * 100 / func_003519E0()) < 0x1F) {
        m = side == func_0035F0C0() ? func_0034B700(st) : func_0034B710(st);
    } else {
        m = 10;
    }
    if (m != cur) {
        st[7] = m;
        st[8] |= 1;
    }
}

/* 0x0034D280, 0x58 bytes. Plan: all of the side's free groups wait. */
void func_0034D280(u8 *st)
{
    u8 buf[64], list[16];

    func_003653F0((int)list, buf, 0x10);
    func_0034BD20((int)list, func_0034B160((int)st));
    func_0034CE40((int)list, func_00365050((int)list));
}

/* The attack plans: free groups go to the side's target group, hold the bases where they are,
 * take enemy bases (`per` groups each), the rest wait. */
static void attack_plan(u8 *st, u32 per)
{
    u8 b1[64], b2[80], l1[16], l2[16];
    u32 lim = func_0034D160(), c;
    int side = func_0034B160((int)st), w;

    func_003653F0((int)l1, b1, 0x10);
    func_003653F0((int)l2, b2, 0x14);
    func_0034BD20((int)l1, side);
    if (func_003653D0((int)l1) == 0)
        return;
    w = func_0034B720(st);
    if (w >= 0 && w < 2) {
        c = func_00365050((int)l1);
        if (lim < c)
            c = lim;
        func_0034CD10((int)l1, w, c);
    }
    if (func_0034C0D0((int)l2, side) != 0) {
        c = func_00365050((int)l2);
        if (func_00365050((int)l1) < c)
            c = func_00365050((int)l1);
        func_0034D040((int)l1, c, (int)l2, 1, side);
    }
    if (func_0034C270((int)l2, side, 0) != 0)
        func_0034CF20((int)l1, func_00365050((int)l1), (int)l2, per, side);
    if (func_003653D0((int)l1) != 0)
        func_0034CE40((int)l1, func_00365050((int)l1));
}

/* 0x0034D2E0, 0x188 bytes. Attack plan, three groups per base. */
void func_0034D2E0(u8 *st)
{
    attack_plan(st, 3);
}

/* 0x0034D470, 0x0034D490, 0x1C bytes each. */
/* 0x0034D470, 0x1C bytes, matching. */
void func_0034D470(u8 *st)
{
    func_0034D2E0(st);
}

/* 0x0034D490, 0x1C bytes, matching. */
void func_0034D490(u8 *st)
{
    func_0034D2E0(st);
}

/* 0x0034D4B0, 0x1C bytes, matching. */
void func_0034D4B0(u8 *st)
{
    func_0034D280(st);
}

/* 0x0034D4D0, 0x188 bytes. Attack plan, two groups per base. */
void func_0034D4D0(u8 *st)
{
    attack_plan(st, 2);
}

/* 0x0034D660, 0x0034D680, 0x1C bytes each. */
/* 0x0034D660, 0x1C bytes, matching. */
void func_0034D660(u8 *st)
{
    func_0034D4D0(st);
}

/* 0x0034D680, 0x1C bytes, matching. */
void func_0034D680(u8 *st)
{
    func_0034D4D0(st);
}

/* 0x0034D6A0, 0x1C bytes, matching. */
void func_0034D6A0(u8 *st)
{
    func_0034D280(st);
}

/* 0x0034D6C0, 0x198 bytes. Defence plan: a third of the free groups hold the main base, some go
 * to the target group, the rest take the bases linked to the main base. */
void func_0034D6C0(u8 *st)
{
    u8 b1[64], b2[80], l1[16], l2[16], *main;
    u32 lim = func_0034D160(), c;
    int side = func_0034B160((int)st), w;

    func_003653F0((int)l1, b1, 0x10);
    func_003653F0((int)l2, b2, 0x14);
    func_0034BD20((int)l1, side);
    if (func_003653D0((int)l1) == 0)
        return;
    main = BASE(func_0035F200(side));
    c = (u32)(func_00365050((int)l1) * 0x22) / 100;
    if (c < 2)
        c = 1;
    func_0034CC40((int)l1, main, c);
    w = func_0034B720(st);
    if (w >= 0 && w < 2) {
        c = func_00365050((int)l1);
        if (lim < c)
            c = lim;
        func_0034CD10((int)l1, w, c);
    }
    func_0034C010((int)l2, main, side);
    if (func_003653D0((int)l2) != 0)
        func_0034CF20((int)l1, func_00365050((int)l1), (int)l2, 3, side);
    if (func_003653D0((int)l1) != 0)
        func_0034CE40((int)l1, func_00365050((int)l1));
}

extern void (*g_004154F0[11])(u8 *st);   /* by side plan */
extern void (*g_0045D060[2])(u8 *st);    /* (small data) more side steps */
extern u8 g_00669D60[];                  /* the settings */
extern u8 g_006A3A30[];                  /* the officers (0xC0 each) */

int func_0033C160(u8 *g);
int func_0033C4E0(u8 *g);
void func_0033E850(u8 *g, u8 *h);
int func_0036F4B0(int s, int x);
void func_0036F990(int s, int k, int g);
int func_0036F520(int s, int k);
int func_0033C1E0(u8 *g);
int func_0033CC20(u8 *g, int b);
int func_0033D2C0(int b);
u32 func_00361CE0(int s);

/* 0x0034D860, 0xC4 bytes. Plan: the free groups take the unowned bases (one each), the rest
 * wait. */
void func_0034D860(u8 *st)
{
    u8 b1[64], b2[80], l1[16], l2[16];
    int side = func_0034B160((int)st);

    func_003653F0((int)l1, b1, 0x10);
    func_003653F0((int)l2, b2, 0x14);
    func_0034BD20((int)l1, side);
    if (func_003653D0((int)l1) == 0)
        return;
    func_0034C270((int)l2, side, 1);
    if (func_003653D0((int)l2) != 0)
        func_0034CF20((int)l1, func_00365050((int)l1), (int)l2, 1, side);
    if (func_003653D0((int)l1) != 0)
        func_0034CE40((int)l1, func_00365050((int)l1));
}

/* 0x0034D930, 0xEC bytes. Runs side state `st`'s plan once it was marked. */
void func_0034D930(u8 *st)
{
    void (*tbl[12])(u8 *);
    int k;

    for (k = 0; k < 11; k++)
        tbl[k] = g_004154F0[k];
    if ((st[8] & 1) != 0 && st[7] < 0xB) {
        if (tbl[st[7]] != 0)
            tbl[st[7]](st);
        st[8] &= 0xFE;
    }
}

/* 0x0034DA20, 0x17C bytes. The other active groups holding (state 2, kind 3) the same base as
 * group `g`, into list `l`; their count. */
int func_0034DA20(int l, u8 *g)
{
    int b = func_0033C160(g);
    u32 k;

    func_00365230(l);
    for (k = 0; k < 0x10; k++) {
        u8 *h = func_0033EF80(k);

        if (h == 0 || (*(int *)(h + 0x64) & 1) == 0 || !UNIT_ACTIVE(UNIT_FLAGS(GROUP_UNIT(h))) || h == g)
            continue;
        if (GROUP_INFO(h)[8] == 2 && func_0033C4E0(h) == b && GROUP_INFO(h)[5] == 3)
            func_00364E40(l, GROUP_INDEX(h));
    }
    return func_00365050(l);
}

/* 0x0034DBA0, 0x118 bytes. The side's kind 6 groups on a base that others hold hand over to the
 * holder that wants it most. */
void func_0034DBA0(u8 *st)
{
    u8 b1[64], b2[64], l1[16], l2[16];
    int side = func_0034B160((int)st);
    u32 n, k;

    func_003653F0((int)l1, b1, 0x10);
    func_003653F0((int)l2, b2, 0x10);
    if (func_0034BE80((int)l1, side, 6, 0xFF) == 0)
        return;
    n = func_00365050((int)l1);
    for (k = 0; k < n; k++) {
        u8 *g = g_006A1D58[func_00365030((int)l1, k)];
        int b = func_0033C160(g);

        if (func_0033CB60(g, (u8 *)b) != 0 && func_0034DA20((int)l2, g) != 0)
            func_0033E850(g, func_0034C8A0((int)l2, (u8 *)func_0033C160(g)));
    }
}

/* 0x0034DCC0, 0xEC bytes. The side's state 0 groups whose base is no longer threatened stop. */
void func_0034DCC0(u8 *st)
{
    u8 b1[64], l1[16];
    int side = func_0034B160((int)st);
    u32 n, k;

    func_003653F0((int)l1, b1, 0x10);
    if (func_0034BFE0((int)l1, side, 0, 0xFF) == 0)
        return;
    n = func_00365050((int)l1);
    for (k = 0; k < n; k++) {
        u8 *g = g_006A1D58[func_00365030((int)l1, k)];

        if (func_00352240((u8 *)func_0033C4E0(g), side) == 0)
            func_003385E0(g, 4, 0xFF);
    }
}

/* 0x0034DDB0, 0x70 bytes. Runs the two extra side steps. */
void func_0034DDB0(u8 *st)
{
    void (*tbl[2])(u8 *);
    u32 k;

    tbl[0] = g_0045D060[0];
    tbl[1] = g_0045D060[1];
    for (k = 0; k < 2; k++) {
        if (tbl[k] != 0)
            tbl[k](st);
    }
}

/* 0x0034DE20, 0x44 bytes, matching. The computer side's turn: its plan chosen and run, then its steps. */
void func_0034DE20(u8 *st)
{
    if (func_0034B160((int)st) != 0) {
        func_0034D180(st);
        func_0034D930(st);
        func_0034DDB0(st);
    }
}

/* 0x0034DE70, 0x140 bytes. An active group of side state `st` (its own eight first). */
u8 *func_0034DE70(u8 *st)
{
    int sides[2], j, k;

    sides[0] = func_0034B160((int)st);
    sides[1] = func_0035D5A0(func_0034B160((int)st));
    for (j = 0; j < 2; j++) {
        for (k = 0; k < 8; k++) {
            u8 *g = func_0033EF80(sides[j] * 8 + k);

            if ((*(int *)(g + 0x64) & 1) != 0 && UNIT_ACTIVE(UNIT_FLAGS(GROUP_UNIT(g)))
                && GROUP_UNIT(g)[0x79] == (u32)func_0034B160((int)st))
                return g;
        }
    }
    return 0;
}

/* 0x0034DFB0, 0xA4 bytes. A chance growing with the battle's elapsed time (1%, 3%, 5%, 10%). */
int func_0034DFB0(void)
{
    u32 p = (g_00669F9C * 100) / g_00669FA0, pct;

    if (p < 10)
        pct = 1;
    else if (p < 0x1E)
        pct = 3;
    else if (p < 0x32)
        pct = 5;
    else
        pct = 10;
    return RANDOM() % 100 < pct;
}

/* 0x0034E060, 0xC8 bytes. A chance for each player in play, higher with a low officer value
 * (+0x82: 30% below 50, 10% below 100). */
int func_0034E060(void)
{
    int k;

    for (k = 0; k < 2; k++) {
        if (*(int *)(g_00669D60 + k * 0x48 + 0xA0) != 0) {
            u16 v = *(u16 *)(g_006A3A30 + k * 0xC0 + 0x82);
            u32 pct = 0;

            if (v < 0x32)
                pct = 0x1E;
            else if (v < 100)
                pct = 10;
            if (RANDOM() % 100 < pct)
                return 1;
        }
    }
    return 0;
}

/* 0x0034E130, 0x7C bytes, matching. */
void func_0034E130(int x, u8 *g)
{
    int s = GROUP_UNIT(g)[0x79];
    u32 k = func_0036F4B0(s, x);

    if (k < 2)
        func_0036F990(s, k, GROUP_INDEX(g));
}

/* 0x0034E1B0, 0x1B8 bytes. Whether group `g`'s side calls for help: a kind 2 group in trouble
 * (30%), else by the elapsed-time chance; never with func_0036F520 0x15. */
int func_0034E1B0(u8 *g)
{
    u8 s = GROUP_UNIT(g)[0x79];
    u32 k;

    if (func_0036F520(s, 0x15) != 0)
        return 0;
    for (k = 0; k < 0x10; k++) {
        u8 *h = func_0033EF80(k);

        if ((*(int *)(h + 0x64) & 1) == 0 || !UNIT_ACTIVE(UNIT_FLAGS(GROUP_UNIT(h))))
            continue;
        if (s == GROUP_UNIT(h)[0x79] && GROUP_INFO(h)[5] == 2) {
            int b = func_0033C1E0(h);

            if (h != 0 && func_0033CC20(h, b) != 0 && func_0033D2C0(b) != 0 && RANDOM() % 100 < 0x1E)
                return 1;
        }
    }
    return func_0034DFB0() != 0;
}

/* 0x0034E370, 0xB4 bytes. Whether group `g`'s side is weak (below 51; below 30 a 10% chance,
 * else the elapsed-time chance). */
int func_0034E370(u8 *g)
{
    u8 s = GROUP_UNIT(g)[0x79];

    if (func_00361CE0(s) >= 0x33)
        return 0;
    if (func_00361CE0(s) < 0x1E && RANDOM() % 100 < 10)
        return 1;
    return func_0034DFB0() != 0;
}

extern u8 *g_0045D2F0;                   /* (small data) the battle map (bases at +0x110) */

u32 func_00361D40(int s);
u32 func_0033F430(int s, int a, int *out, int max);
u32 func_00361E20(int s);
u32 func_0033F7D0(int s, int a);
int func_003F6C10(int s);
int func_003F7090(int a, int b);
u32 func_003F6CA0(int s, int k);
int func_003F77F0(int s, int k);
void func_003F7920(int s, int k, int g);
void func_0034E760(u8 *st);
u8 func_0034F330(u8 *b, u8 m);
void func_0034F300(u8 *b, u8 m);
void func_0034F310(u8 *b, u8 m);

/* 0x0034E430, 0x0034E450, 0x0034E470, 0x20 bytes each. The elapsed-time chance. */
/* 0x0034E430, 0x20 bytes, matching. */
int func_0034E430(void)
{
    return func_0034DFB0() != 0;
}

/* 0x0034E450, 0x20 bytes, matching. */
int func_0034E450(void)
{
    return func_0034DFB0() != 0;
}

/* 0x0034E470, 0x20 bytes, matching. */
int func_0034E470(void)
{
    return func_0034DFB0() != 0;
}

/* 0x0034E490, 0x110 bytes. Whether group `g`'s side (below 701) has half its groups or fewer
 * threatened, then by the elapsed-time chance. */
int func_0034E490(u8 *g)
{
    u8 s = GROUP_UNIT(g)[0x79];
    int l[16];
    u32 n, m = 0, k;

    if (func_00361D40(s) >= 0x2BD)
        return 0;
    n = func_0033F430(s, 1, l, 0x10);
    for (k = 0; k < n; k++) {
        if (func_0033CEA0(g_006A1D58[l[k]], func_0035D5A0(s)) != 0)
            m++;
    }
    if (n >> 1 < m)
        return 0;
    return func_0034DFB0() != 0;
}

/* 0x0034E5A0, 0x48 bytes, matching. Whether the other side is strong (300 or more), then the chance. */
int func_0034E5A0(u8 *g)
{
    if (func_00361D40(func_0035D5A0(GROUP_UNIT(g)[0x79])) < 300)
        return 0;
    return func_0034DFB0() != 0;
}

/* 0x0034E5F0, 0xD0 bytes. Whether group `g`'s side (unless func_0036F520 0x1C) acts: plan 10 at
 * 10%, else func_0034E060, else the chance. */
int func_0034E5F0(u8 *g)
{
    u8 s = GROUP_UNIT(g)[0x79];

    if (func_0036F520(s, 0x1C) != 0)
        return 0;
    if (SIDE_STATE(s)[7] == 10 && RANDOM() % 100 < 10)
        return 1;
    if (func_0034E060() != 0)
        return 1;
    return func_0034DFB0() != 0;
}

/* 0x0034E6C0, 0x5C bytes. The same for event 0x1D with func_00361E20 at 100 or more. */
int func_0034E6C0(u8 *g)
{
    u8 s = GROUP_UNIT(g)[0x79];

    if (func_0036F520(s, 0x1D) != 0)
        return 0;
    if (func_00361E20(s) < 100)
        return 0;
    return func_0034DFB0() != 0;
}

/* 0x0034E720, 0x40 bytes, matching. The same for event 0x1E. */
int func_0034E720(u8 *g)
{
    if (func_0036F520(GROUP_UNIT(g)[0x79], 0x1E) != 0)
        return 0;
    return func_0034DFB0() != 0;
}

/* 0x0034E910, 0x1C bytes, matching. */
u8 *func_0034E910(u8 *st)
{
    return func_0034DE70(st);
}

/* 0x0034E930, 0x270 bytes. Every 30 counts, a side with three groups or more may change one of
 * its six formation slots for a better one against the enemy's (20%, less when already ahead). */
void func_0034E930(u8 *st)
{
    int side = func_0034B160((int)st);
    u8 *g;

    if (func_0036D300() == 0 && side == 0)
        return;
    if (st[10] == 0)
        return;
    if (--st[10] != 0 || func_0033F7D0(side, 1) <= 2 || (g = func_0034E910(st)) == 0)
        return;
    {
        int e = func_003F6C10(func_0035D5A0(side)), m = func_003F7090(func_003F6C10(side), e);
        u32 best = 6, k;

        if ((m >= 1 && RANDOM() % 100 <= 0x4F) || RANDOM() % 100 >= 0x14)
            return;
        for (k = 0; k < 6; k++) {
            u32 x = func_003F6CA0(side, k);
            int v;

            if (x < 10 && func_003F77F0(side, k) != 0 && (v = func_003F7090(x, e), m < v && v >= 0)
                && (best > 5 || RANDOM() % 100 < 0x32))
                best = k;
        }
        if (best < 6) {
            func_003F7920(side, best, GROUP_INDEX(g));
            st[10] = 0x1E;
        }
    }
}

/* 0x0034EBA0, 0x3C bytes. A side's frame. */
void func_0034EBA0(u8 *st)
{
    func_0034D170();
    func_0034DE20(st);
    func_0034E760(st);
    func_0034E930(st);
}

/* 0x0034EBE0, 0xA0 bytes. After ten counts of 50 frames, one side per frame in turn (of 50). */
void func_0034EBE0(void)
{
    u32 k = g_006AA624;

    if (g_00669F9C / 0x32 > 9) {
        if (k < 2)
            func_0034EBA0(SIDE_STATE(k));
        g_006AA624 = k < 0x31 ? k + 1 : 0;
    }
}

/* 0x0034EC80, 0x1C bytes, matching. Base `k` (0x3C bytes each). */
int func_0034EC80(int k)
{
    return (int)(g_0045D2F0 + k * 0x3C + 0x110);
}

/* 0x0034ECA0, 0x98 bytes. The base at position code `code` (0 for none). */
u8 *func_0034ECA0(u8 *code)
{
    u32 k;

    for (k = 0; k < 0x14; k++) {
        u8 *b = BASE(k), c[2];

        if (func_0034EE50(b) != 0) {
            func_0034ED90(b, c);
            if (c[0] == code[0] && c[1] == code[1])
                return b;
        }
    }
    return 0;
}

/* 0x0034ED40, 0x4C bytes, matching. Base `b`'s number. */
int func_0034ED40(u8 *b)
{
    return ((int)b - func_0034EC80(0)) / 0x3C;
}

/* 0x0034ED90, 0x14 bytes, matching. Base or unit `b`'s position code. */
void func_0034ED90(u8 *b, u8 *out)
{
    out[0] = b[0];
    out[1] = b[1];
}

/* 0x0034EDB0, 0x4C bytes. Base `b`'s owner (0, 1, 2 neutral?, 3 none). */
int func_0034EDB0(u8 *b)
{
    u8 c = b[6];

    if (c == 3)
        return 2;
    if (c == 2)
        return 1;
    if (c == 1)
        return 0;
    return 3;
}

/* 0x0034EE00, 0x4C bytes. Sets base `b`'s owner. */
void func_0034EE00(u8 *b, int o)
{
    if (o == 3)
        b[6] = 4;
    else if (o == 1)
        b[6] = 2;
    else if (o == 0)
        b[6] = 1;
}

/* 0x0034EE50, 0xC bytes, matching. Whether base `b` exists. */
int func_0034EE50(u8 *b)
{
    return b[6] != 0;
}

/* 0x0034EE60-0x0034EEC0, 0x1C bytes each. */
/* 0x0034EE60, 0x1C bytes. */
int func_0034EE60(u8 *b)
{
    return func_0034F330(b, 1);
}

/* 0x0034EE80, 0x1C bytes. */
int func_0034EE80(u8 *b)
{
    return func_0034F330(b, 2);
}

/* 0x0034EEA0, 0x1C bytes, matching. */
void func_0034EEA0(u8 *b)
{
    func_0034F300(b, 2);
}

/* 0x0034EEC0, 0x1C bytes, matching. */
void func_0034EEC0(u8 *b)
{
    func_0034F310(b, 2);
}

/* 0x0034EEE0, 8 bytes, matching. */
/* 0x0034EEE0, 0x8 bytes, matching. */
void func_0034EEE0(u8 *b, u8 v)
{
    b[7] = v;
}

/* 0x0034EEF0, 0x58 bytes. How many bases base `b` links to (up to four). */
u32 func_0034EEF0(u8 *b)
{
    u8 k;

    for (k = 0; k < 4; k++) {
        if (func_0034EF60(b, k) == 0)
            return k;
    }
    return k;
}

/* 0x0034EF50, 0xC bytes, matching. */
u8 func_0034EF50(u8 *b, int k)
{
    return b[k + 2];
}

/* 0x0034EF60, 0x3C bytes. Base `b`'s link `k` (0 for none). */
u8 *func_0034EF60(u8 *b, u32 k)
{
    u8 x = func_0034EF50(b, k);

    return x < 0x14 ? BASE(x) : 0;
}

extern const char g_004480A8[];          /* "emp_FldBase.c" */

u8 *func_0035DCD0(int p);
u8 *func_002EFB00(int k);
void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00102EC0(void *data);
u32 func_003623B0(void);
void func_0011EB80(void *to, const void *from, int size);

/* A base's unit slot `k` (0x1AD = none). */
#define BASE_UNIT(b, k) (*(u16 *)((b) + 8 + (k) * 2))

/* 0x0034EFA0, 0x88 bytes. Adds unit `i` (when func_0034A630) to base `b`'s first free slot. */
void func_0034EFA0(u8 *b, int i)
{
    u32 k;

    if (func_0034A630(UNIT(i)) == 0)
        return;
    for (k = 0; k < 0x14; k++) {
        if (BASE_UNIT(b, k) > 0x1AC) {
            BASE_UNIT(b, k) = i;
            return;
        }
    }
}

/* 0x0034F030, 0x88 bytes. Removes unit `i` from base `b`. */
void func_0034F030(u8 *b, u32 i)
{
    u32 k;

    if (func_0034A630(UNIT(i)) == 0)
        return;
    for (k = 0; k < 0x14; k++) {
        if (BASE_UNIT(b, k) == i) {
            BASE_UNIT(b, k) = 0x1AD;
            return;
        }
    }
}

/* 0x0034F0C0, 0x34 bytes. Empties base `b`'s unit slots. */
void func_0034F0C0(u8 *b)
{
    u32 k;

    for (k = 0; k < 0x14; k++)
        BASE_UNIT(b, k) = 0x1AD;
}

/* 0x0034F100, 0x40 bytes, matching. Empties every base's unit slots. */
void func_0034F100(void)
{
    u32 k;

    for (k = 0; k < 0x14; k++)
        func_0034F0C0(BASE(k));
}

/* 0x0034F140, 0x12C bytes. Side `side`'s active units at base `b` (side 0 also counts the players
 * standing on it). */
int func_0034F140(u8 *b, u32 side)
{
    int n = 0, p;
    u32 k;

    for (k = 0; k < 0x14; k++) {
        u32 i = BASE_UNIT(b, k);

        if (i < 0x1AD) {
            u8 *u = UNIT(i);

            if (UNIT_ACTIVE(UNIT_FLAGS(u)) && side == u[0x79])
                n++;
        }
    }
    if (side == 0) {
        short c[2];

        func_0034ED90(b, (u8 *)c);
        for (p = 0; p < 2; p++) {
            if (*(int *)(g_00669D60 + p * 0x48 + 0xA0) != 0 && c[0] == *(short *)(func_0035DCD0(p) + 0x40))
                n++;
        }
    }
    return n;
}

/* 0x0034F270, 0x10 bytes. */
u16 func_0034F270(u8 *b, int k)
{
    return BASE_UNIT(b, k);
}

/* 0x0034F280, 0x4C bytes, matching. Base `b`'s unit `k` (0 for none). */
u8 *func_0034F280(u8 *b, int k)
{
    u32 i = func_0034F270(b, k) & 0xFFFF;

    return i < 0x1AD ? UNIT(i) : 0;
}

/* 0x0034F2D0-0x0034F3E0. Base fields: a counter (+0x30), flags (+0x31), two halfwords
 * (+0x32, +0x34), a 4-byte value (+0x36) and per-side bytes (+0x3A). */
/* 0x0034F2D0, 0x10 bytes, matching. */
void func_0034F2D0(u8 *b)
{
    b[0x30]++;
}

/* 0x0034F2E0, 0x8 bytes, matching. */
void func_0034F2E0(u8 *b)
{
    b[0x30] = 0;
}

/* 0x0034F2F0, 0x8 bytes, matching. */
u8 func_0034F2F0(u8 *b)
{
    return b[0x30];
}

/* 0x0034F300, 0x10 bytes, matching. */
void func_0034F300(u8 *b, u8 m)
{
    b[0x31] |= m;
}

/* 0x0034F310, 0x1C bytes, matching. */
void func_0034F310(u8 *b, u8 m)
{
    b[0x31] &= ~m;
}

/* 0x0034F330, 0x10 bytes. */
u8 func_0034F330(u8 *b, u8 m)
{
    return b[0x31] & m;
}

/* 0x0034F340, 0x14 bytes, matching. */
void func_0034F340(u8 *b, u16 v)
{
    if (b != 0)
        *(u16 *)(b + 0x32) = v;
}

/* 0x0034F360, 0x1C bytes. */
u16 func_0034F360(u8 *b)
{
    if (b == 0)
        return 0;
    return *(u16 *)(b + 0x32);
}

/* 0x0034F380, 0x1C bytes, matching. */
void func_0034F380(u8 *b)
{
    if (b != 0)
        (*(short *)(b + 0x32))--;
}

/* 0x0034F3A0, 0x8 bytes, matching. */
void func_0034F3A0(u8 *b, u16 v)
{
    *(u16 *)(b + 0x34) = v;
}

/* 0x0034F3B0, 0x8 bytes. */
u16 func_0034F3B0(u8 *b)
{
    return *(u16 *)(b + 0x34);
}

/* 0x0034F3C0, 0x8 bytes, matching. */
u8 *func_0034F3C0(u8 *b)
{
    return b + 0x36;
}

/* 0x0034F3D0, 0xC bytes, matching. */
void func_0034F3D0(u8 *b, int k, u8 v)
{
    b[k + 0x3A] = v;
}

/* 0x0034F3E0, 0xC bytes, matching. */
u8 func_0034F3E0(u8 *b, int k)
{
    return b[k + 0x3A];
}

/* 0x0034F3F0, 0x48 bytes. Counts base `b`'s side byte `k` down. */
void func_0034F3F0(u8 *b, int k)
{
    u8 v = func_0034F3E0(b, k);

    if (v != 0)
        func_0034F3D0(b, k, v - 1);
}

/* 0x0034F440, 0x38 bytes, matching. Saves the bases into `p` (+0xBE). */
void func_0034F440(u8 *p)
{
    func_0011EB80(p + 0xBE, BASE(0), 0x4B0);
}

/* 0x0034F480, 0x94 bytes. Loads the bases back from save block 9, empties their units and counts
 * them. */
void func_0034F480(void)
{
    u8 *d = func_002EFB00(9), *map, n = 0;
    u32 k;

    func_0011EB80(BASE(0), d + 0xBE, 0x4B0);
    func_0034F100();
    map = g_0045D2F0;
    for (k = 0; k < 0x14; k++) {
        if (func_0034EE50(BASE(k)) != 0)
            n++;
    }
    map[0x5C0] = n;
}

/* 0x0034F520, 0x7C bytes. Clears battle map `map`'s twenty bases. */
void func_0034F520(u8 *map)
{
    u32 k, j;

    for (k = 0; k < 0x14; k++, map += 0x3C) {
        map[0x116] = 0;
        map[0x117] = 0;
        for (j = 0; j < 0x14; j++)
            *(u16 *)(map + 0x118 + j * 2) = 0x1AD;
        map[0x140] = 0;
        map[0x141] = 0;
        *(u16 *)(map + 0x142) = 0;
        *(u16 *)(map + 0x144) = 0;
        map[0x146] = 0;
        map[0x147] = 0;
        map[0x148] = 0;
        map[0x149] = 0;
    }
}

/* 0x0034F5A0, 0xB4 bytes. Loads the bases' positions and links for the battlefield (LINKDATA
 * entry 0x4AB, 0x78 bytes per field). */
void func_0034F5A0(u8 *map)
{
    u8 *d = func_001026D0(1, 0x4AB, 0, 1, 0, 0, g_004480A8, 0x1FB), *src;
    u32 f = func_003623B0(), k;

    if (f < 0x30) {
        src = d + f * 0x78;
        for (k = 0; k < 0x14; k++, src += 6, map += 0x3C)
            func_0011EB80(map + 0x110, src, 6);
    }
    func_00102EC0(d);
}

/* 0x0034F660, 0xCC bytes. Marks the bases in use (up to the first without links), clears the
 * others and keeps their count. */
void func_0034F660(u8 *map)
{
    u32 k, n = 0x14;

    for (k = 0; k < 0x14; k++) {
        u8 *b = map + k * 0x3C + 0x110;

        b[6] = 5;
        func_0034EF50(b, 0);
        if (func_0034EF50(b, 0) > 0x13) {
            n = k;
            break;
        }
    }
    for (; k < 0x14; k++)
        map[k * 0x3C + 0x116] = 0;
    map[0x5C0] = n;
}

extern int g_00415470[10];               /* the default action weights */
extern u8 g_00448088[12], g_00448098[14];   /* (action, weight) pairs */

int func_0035DB50(int *w, int n);
u32 func_003E6D30(void);
int func_0036F390(u8 *u, int k);
u32 func_0035F100(void);
int func_001EF900(u8 *u, u8 *v);
short *func_0033B730(int x);

/* 0x00348890, 0x98 bytes. A random action by the default weights. */
int func_00348890(u8 *u, int x)
{
    int w[10], k;

    for (k = 0; k < 10; k++)
        w[k] = g_00415470[k];
    return func_0035DB50(w, 5);
}

/* 0x00348930, 0xA4 bytes. Actions 0x11 / 0x12 become 0x17, 0xF / 0x10 become 0x16 (0x15 at
 * 20%); others stay. */
u32 func_00348930(u32 k)
{
    u32 m = 0x25;

    if (k == 0x12 || k == 0x11)
        m = 0x17;
    else if (k == 0x10 || k == 0xF)
        m = 0x16;
    if (m < 0x25) {
        k = m;
        if (RANDOM() % 100 < 0x14)
            k = 0x15;
    }
    return k;
}

u32 func_00348BA0(u8 *u);

/* 0x003489E0, 0xF8 bytes. Unit `u`'s next action: its event action by chance (func_003E6D30%),
 * else a random one (changed by event 0x14); event action 0x1D becomes 0x1E half the time. */
u32 func_003489E0(u8 *u, int x)
{
    u32 p = func_003E6D30(), m = func_00348BA0(u);

    if (m > 0x24 || p <= RANDOM() % 100) {
        m = func_00348890(u, x);
        if (func_0036F390(u, 0x14) != 0)
            m = func_00348930(m);
        return m;
    }
    if (m != 0x1D)
        return m;
    return RANDOM() % 100 < 0x32 ? 0x1E : 0x1D;
}

/* 0x00348AE0, 0xB8 bytes. A random action 9-0xD (with func_0036D310, 0x1B-0x21 at 3%). */
int func_00348AE0(void)
{
    if (func_0036D310() == 0 || RANDOM() % 100 > 2)
        return RANDOM() % 5 + 9;
    return RANDOM() % 7 + 0x1B;
}

/* 0x00348BA0, 0xE4 bytes, matching. Unit `u`'s event action (events 0xD-0x13), else 0x25. */
u32 func_00348BA0(u8 *u)
{
    if (func_0036F390(u, 0xD) != 0)
        return 0x1B;
    if (func_0036F390(u, 0xE) != 0)
        return 0x1C;
    if (func_0036F390(u, 0xF) != 0)
        return 0x1D;
    if (func_0036F390(u, 0x10) != 0)
        return 0x1F;
    if (func_0036F390(u, 0x11) != 0)
        return 0x20;
    if (func_0036F390(u, 0x12) != 0)
        return 0x21;
    if (func_0036F390(u, 0x13) != 0)
        return 0x22;
    return 0x25;
}

/* 0x00348C90, 0x8C bytes. The same, the event action half the time. */
u32 func_00348C90(u8 *u)
{
    u32 m = func_003489E0(u, 0), b;

    if (RANDOM() % 100 < 0x32 && (b = func_00348BA0(u)) < 0x25)
        m = b;
    return m;
}

/* 0x00348D20, 0x154 bytes. A unit's random move (by weights: the strong table by chance from
 * func_0035F100, else the weak one); 0x17 without a side or with flag 0x400. */
u8 func_00348D20(u8 *u)
{
    u8 *tbl = 0;
    u32 n = 0, r, k;

    if (u[0x79] != 0 && (UNIT_FLAGS(u) & 0x400) == 0) {
        u32 p = func_0035F100();

        if (func_0036D310() != 0)
            p *= 10;
        if (p > 100)
            p = 100;
        if (RANDOM() % 100 < p) {
            n = 7;
            tbl = g_00448098;
        } else {
            n = 6;
            tbl = g_00448088;
        }
    }
    if (tbl != 0) {
        r = RANDOM() % 100;
        for (k = 0; k < n; k++) {
            if (r < tbl[k * 2 + 1])
                return tbl[k * 2];
            r -= tbl[k * 2 + 1];
        }
    }
    return 0x17;
}

/* 0x00348E80, 0x2C bytes. Whether unit `u` has flag 0x20000 without 0x800. */
int func_00348E80(u8 *u)
{
    return (UNIT_FLAGS(u) & 0x800) == 0 && (UNIT_FLAGS(u) & 0x20000) != 0;
}

/* 0x00348EB0, 0xE0 bytes. Whether unit `u` (flag 0x20000) may follow flagged unit `v`: its
 * group not of kinds 6, 8, 9 and below 50. */
int func_00348EB0(u8 *u, u8 *v)
{
    u8 *g = func_0034A740(u), k;

    if ((UNIT_FLAGS(u) & 0x20000) == 0)
        return 0;
    if ((UNIT_FLAGS(v) & 0x30) == 0)
        return 0;
    k = GROUP_INFO(g)[5];
    if (k == 9 || k == 8 || k == 6)
        return 0;
    return GROUP_INFO(g)[10] < 0x32;
}

/* 0x00348F90, 0x58 bytes, matching. Whether unit `u` (flag 0x20000) faces flagged unit `v`. */
int func_00348F90(u8 *u, u8 *v)
{
    func_0034A740(u);
    if ((UNIT_FLAGS(u) & 0x20000) == 0)
        return 0;
    return (UNIT_FLAGS(v) & 0x30) != 0;
}

/* 0x00348FF0, 0x1C bytes, matching. */
int func_00348FF0(u8 *u, u8 *v)
{
    return func_001EF900(u, v);
}

/* 0x00349010, 0x38 bytes, matching. Whether unflagged unit `u` passes func_00348E80. */
int func_00349010(u8 *u)
{
    if ((UNIT_FLAGS(u) & 0x30) != 0)
        return 0;
    return func_00348E80(u) != 0;
}

/* Whether units `u` and `v` both stand on the base of `u`'s group, else whether the group is
 * below `lim` or `u` passes func_00348E80. */
static int on_base_or(u8 *u, u8 *v, int lim)
{
    u8 *g = func_0034A740(u);
    int b = func_0033C160(g);

    if (func_0034A660(u, (u8 *)b) != 0 && func_0034A660(v, (u8 *)b) != 0)
        return 1;
    if (GROUP_INFO(g)[10] < lim)
        return 1;
    return func_00348E80(u) != 0;
}

/* The same with the group's func_0033C1E0 position. */
static int at_spot_or(u8 *u, u8 *v, int lim)
{
    u8 *g = func_0034A740(u);
    int x = func_0033C1E0(g);

    if (*(short *)(u + 0x40) == *func_0033B730(x) && *(short *)(v + 0x40) == *func_0033B730(x))
        return 1;
    if (GROUP_INFO(g)[10] < lim)
        return 1;
    return func_00348E80(u) != 0;
}

/* 0x00349050, 0xD0 bytes. */
int func_00349050(u8 *u, u8 *v)
{
    return on_base_or(u, v, 0x1E);
}

/* 0x00349120, 0xE0 bytes. */
int func_00349120(u8 *u, u8 *v)
{
    return at_spot_or(u, v, 0x1E);
}

/* 0x00349200, 0xD0 bytes. */
int func_00349200(u8 *u, u8 *v)
{
    return on_base_or(u, v, 10);
}

/* 0x003492D0, 0xE0 bytes. */
int func_003492D0(u8 *u, u8 *v)
{
    return at_spot_or(u, v, 10);
}

/* 0x003493C0, 0x90 bytes. Whether both stand on the group's base, else func_00348E80. */
int func_003493C0(u8 *u, u8 *v)
{
    u8 *g = func_0034A740(u);
    int b = func_0033C160(g);

    if (func_0034A660(u, (u8 *)b) != 0 && func_0034A660(v, (u8 *)b) != 0)
        return 1;
    return func_00348E80(u) != 0;
}

extern int (*g_004154A0[13])(u8 *u, u8 *v);   /* by group kind: whether a unit may act */

int func_0033B050(u8 *g);
int func_0033B090(u8 *g);
int func_001EFD50(u8 *u, u8 *v);
void func_001EABE0(u8 *u, int v, int a);
int func_003F7780(int s, int k);
void func_001F11E0(int w, float *out);
void func_00253B50(int a, int w);
int func_0018C160(u8 *cell);

#define OFFICER(i) (g_006A3A30 + (i) * 0xC0)

/* 0x00349450, 0x90 bytes. The same as func_003493C0. */
int func_00349450(u8 *u, u8 *v)
{
    u8 *g = func_0034A740(u);
    int b = func_0033C160(g);

    if (func_0034A660(u, (u8 *)b) != 0 && func_0034A660(v, (u8 *)b) != 0)
        return 1;
    return func_00348E80(u) != 0;
}

/* 0x003494E0, 0x78 bytes. Whether unit `v` belongs to the group unit `u`'s group follows. */
int func_003494E0(u8 *u, u8 *v)
{
    int x = func_0033C1E0(func_0034A740(u));

    if (x == 0)
        return 0;
    if ((int)func_0034A740(v) == x) {
        func_00348E80(u);
        return 1;
    }
    return 0;
}

/* 0x00349560, 0x90 bytes. The same as func_003493C0. */
int func_00349560(u8 *u, u8 *v)
{
    u8 *g = func_0034A740(u);
    int b = func_0033C160(g);

    if (func_0034A660(u, (u8 *)b) != 0 && func_0034A660(v, (u8 *)b) != 0)
        return 1;
    return func_00348E80(u) != 0;
}

/* 0x00349600, 0xD0 bytes. The same as func_00349050. */
int func_00349600(u8 *u, u8 *v)
{
    return on_base_or(u, v, 0x1E);
}

/* 0x003496E0, 0x11C bytes. Whether unit `u` may act on unit `v` (by its group's kind; with
 * func_0036D310 only func_00348F90), then func_00348FF0. */
int func_003496E0(u8 *u, u8 *v)
{
    int (*tbl[16])(u8 *, u8 *);
    u8 *g;
    int k;

    for (k = 0; k < 13; k++)
        tbl[k] = g_004154A0[k];
    g = func_0034A740(u);
    if (func_0036D310() == 0) {
        if (func_00348EB0(u, v) != 0)
            return 1;
        k = GROUP_INFO(g)[5];
        if (tbl[k] != 0 && tbl[k](u, v) == 0)
            return 0;
    } else if (func_00348F90(u, v) == 0) {
        return 0;
    }
    return func_00348FF0(u, v);
}

/* 0x00349800, 0xAC bytes. Whether units `u` and `v` both stand on `u`'s group's base, or `v` is
 * flagged and shares `u`'s position. */
int func_00349800(u8 *u, u8 *v)
{
    u8 *b = (u8 *)func_0034A890(u);

    if (b == 0)
        return 0;
    if (func_0034A660(u, b) != 0 && func_0034A660(v, b) != 0)
        return 1;
    return (UNIT_FLAGS(v) & 0x30) != 0 && func_0034A6C0(u, v) != 0;
}

/* 0x003498B0, 0xA8 bytes. Whether unit `u` may act on unit `v` (by its group's state), then
 * func_001EFD50. */
int func_003498B0(u8 *u, u8 *v)
{
    u8 *g = func_0034A740(u);

    if (g != 0) {
        if (func_0033B050(g) == 0) {
            if (func_0033B090(g) != 0 && func_00349800(u, v) == 0)
                return 0;
        } else if (func_003496E0(u, v) == 0) {
            return 0;
        }
    }
    return func_001EFD50(u, v);
}

/* 0x00349960, 0x118 bytes. The officers of unit `u` lose `pct`% of their soldiers (+0x82, at
 * least one when any, at most their +0x80); +0x84 keeps the highest. */
void func_00349960(u8 *u, int pct)
{
    u32 k;

    for (k = 0; k < 0x8F; k++) {
        u8 *o = OFFICER(k);

        if ((*(u32 *)(o + 0xB8) & 1) != 0 && *(int *)(o + 0x10) == (int)u) {
            short v = *(short *)(o + 0x82) * pct / 100, cur = *(short *)(o + 0x80), m;

            if (pct > 0 && v < 2)
                v = 1;
            m = cur < v ? cur : v;
            *(short *)(o + 0x82) = m < 1 ? 0 : m;
            if (*(short *)(o + 0x84) < *(short *)(o + 0x82))
                *(short *)(o + 0x84) = *(short *)(o + 0x82);
        }
    }
}

/* 0x00349A80, 0x68 bytes. Unit `u` loses `pct`% of its strength (+0x52, at least one). */
void func_00349A80(u8 *u, int pct)
{
    int v = *(short *)(u + 0x52) * pct / 100;

    if (pct > 0 && v < 2)
        v = 1;
    func_001EABE0(u, *(short *)(u + 0x52) - v, 0);
}

/* 0x00349AF0, 0x40 bytes. The same through its officers for flag 0x20000 units. */
void func_00349AF0(u8 *u, int pct)
{
    if ((UNIT_FLAGS(u) & 0x20000) == 0)
        func_00349A80(u, pct);
    else
        func_00349960(u, pct);
}

/* 0x00349B30, 0xB0 bytes. Unit `u`'s +0x54 value (tripled in a held group of +0x27 kind 0). */
short func_00349B30(u8 *u)
{
    short v = *(short *)(u + 0x54);
    u8 *g = func_0034A740(u);

    if (g != 0 && func_0033B050(g) != 0 && GROUP_INFO(g)[0x27] == 0)
        v = (short)(int)((float)v * 3.0f);
    return v;
}

/* 0x00349BE0, 0xB4 bytes. Its +0x56 value (tripled for +0x27 kind 1). */
short func_00349BE0(u8 *u)
{
    short v = *(short *)(u + 0x56);
    u8 *g = func_0034A740(u);

    if (g != 0 && func_0033B050(g) != 0 && GROUP_INFO(g)[0x27] == 1)
        v = (short)(int)((float)v * 3.0f);
    return v;
}

/* 0x00349CA0, 0x144 bytes, matching. Unit `u`'s +0x24 rate, raised by its side's formation boosts 7-9,
 * halved by the enemy's event 0x1C, tripled for +0x27 kind 2. */
float func_00349CA0(u8 *u)
{
    float f = *(float *)(u + 0x24);
    u8 s = u[0x79], *g;

    if (func_003F7780(s, 7) != 0)
        f *= 2.0f;
    if (func_003F7780(s, 8) != 0)
        f *= 4.0f;
    if (func_003F7780(s, 9) != 0)
        f *= 6.0f;
    if (func_0036F520(func_0035D5A0(s), 0x1C) != 0)
        f *= 0.5f;
    g = func_0034A740(u);
    if (g != 0 && func_0033B050(g) != 0 && GROUP_INFO(g)[0x27] == 2)
        f *= 3.0f;
    return f;
}

/* Clamps `v` to 1-1000. */
static short clamp1000(int v)
{
    short s = (short)(v > 1000 ? 1000 : v), m = s > 1000 ? 1000 : s;

    return m < 2 ? 1 : m;
}

/* 0x0034A020, 0x1A0 bytes. Unit `u` changes weapon to `w`; its officer's two values (+0x8A,
 * +0x8C) scale with the weapons' ratings (when flag 0x80). */
void func_0034A020(u8 *u, u8 w)
{
    u8 old = u[0x7E];
    float a, b;

    u[0x7E] = w;
    if ((UNIT_FLAGS(u) & 0x20000) == 0)
        return;
    func_001F11E0(old, &a);
    func_001F11E0(w, &b);
    {
        u8 *o = OFFICER(*(int *)(u + 0x14));

        if ((*(u32 *)(o + 0xB8) & 0x80) != 0) {
            int x = (int)(b * ((float)*(short *)(o + 0x8A) / a));
            int y = (int)(b * ((float)*(short *)(o + 0x8C) / a));

            *(short *)(o + 0x8A) = clamp1000(x);
            *(short *)(o + 0x8C) = clamp1000(y);
        }
        func_00253B50(*(int *)(o + 0x14), w);
    }
}

/* 0x0034A1C0, 0x38 bytes, matching. Unit `u`'s side (0 / 1 by flags 0x10 / 0x20, else 2). */
int func_0034A1C0(u8 *u)
{
    if (UNIT_FLAGS(u) & 0x10)
        return 0;
    if (UNIT_FLAGS(u) & 0x20)
        return 1;
    return 2;
}

/* 0x0034A200, 0x44 bytes. Unit `u`'s strength in percent of its most. */
int func_0034A200(u8 *u)
{
    u32 m = *(short *)(u + 0x50);

    if (m < 2)
        m = 1;
    return *(short *)(u + 0x52) * 100 / (int)m;
}

/* 0x0034A250, 0x1E0 bytes. A free spot of map cell `cell` (5x5 sub-cells, starting by unit
 * `u`'s number) into `out`; the cell's centre when none. */
void func_0034A250(u8 *u, u8 *cell, float *out)
{
    u32 k;
    int i = cell[1] + cell[0] * 0x19 + (u - g_00693970) / 0x88;

    for (k = 0; k < 0x19; k++) {
        u32 j = i % 0x19;
        u8 c[2];

        c[0] = (int)j % 5 + cell[0] * 5;
        c[1] = j / 5 + cell[1] * 5;
        if (func_0018C160(c) != 0) {
            out[0] = (float)c[0] * 1000.0f + 500.0f;
            out[1] = (float)c[1] * 1000.0f + 500.0f;
            return;
        }
        i = j + 1;
    }
    out[0] = (float)cell[0] * 5000.0f + 2500.0f;
    out[1] = (float)cell[1] * 5000.0f + 2500.0f;
}

extern int g_00669F6C;                   /* settings: 1 = load a saved battle */

int func_0035ECF0(u32 f, u32 k);
void func_00350820(u8 *b);
void func_0034F730(u8 *map);
void func_003516B0(void);
int func_00190480(u8 *cell);
u32 func_00353390(u8 *cell);
u8 *func_00353400(u8 *cell, u32 k);
u32 func_0035DC70(int p);

/* 0x0034FCA0, 0x80 bytes. Sets each base's plan byte from the battlefield table (2 becomes 1). */
void func_0034FCA0(u8 *map)
{
    u32 f = func_003623B0(), k;

    for (k = 0; k < 0x14; k++, map += 0x3C) {
        int v = func_0035ECF0(f, k);

        if (v == 2)
            v = 1;
        func_0034EEE0(map + 0x110, v);
    }
}

/* 0x0034FD20, 0x60 bytes. func_00350820 for each base in use. */
void func_0034FD20(u8 *map)
{
    u32 k;

    for (k = 0; k < 0x14; k++, map += 0x3C) {
        if (func_0034EE50(map + 0x110) != 0)
            func_00350820(map + 0x110);
    }
}

/* 0x0034FD80, 0x4C bytes, matching. Sets up battle map `map`'s bases. */
void func_0034FD80(u8 *map)
{
    func_0034F520(map);
    func_0034F5A0(map);
    func_0034F660(map);
    func_0034F730(map);
    func_0034FCA0(map);
    func_0034FD20(map);
}

/* 0x0034FDD0, 0x1C bytes, matching. */
void func_0034FDD0(void)
{
    func_0034F480();
}

/* 0x0034FDF0, 0x48 bytes. The bases at a battle's start (loaded back from a save, or set up). */
void func_0034FDF0(u8 *map)
{
    if (g_00669F6C == 1)
        func_0034FDD0();
    else
        func_0034FD80(map);
    func_003516B0();
}

/* 0x0034FE40, 0x44 bytes, matching. The same set-up without loading the positions. */
void func_0034FE40(u8 *map)
{
    func_0034F520(map);
    func_0034F660(map);
    func_0034F730(map);
    func_0034FCA0(map);
    func_0034FD20(map);
}

/* 0x0034FE90, 0x124 bytes, matching. Each base's area: the bounding box of the map cells (32x32) that
 * belong to it, into its +0x36 bytes (left, bottom, right, top). */
void func_0034FE90(void)
{
    int x, y;

    for (y = 0; y < 0x20; y++) {
        for (x = 0; x < 0x20; x++) {
            u8 c[2];
            u32 n, k;

            c[0] = x;
            c[1] = y;
            if (func_00190480(c) == 0)
                continue;
            n = func_00353390(c);
            for (k = 0; k < n; k++) {
                u8 *r = func_0034F3C0(func_00353400(c, k));

                r[0] = x < r[0] ? x : r[0];
                r[3] = y < r[3] ? y : r[3];
                r[2] = x < r[2] ? r[2] : x;
                r[1] = y < r[1] ? r[1] : y;
            }
        }
    }
}

/* 0x0034FFC0, 0x20 bytes, matching. Whether side `side` has units at base `b`. */
int func_0034FFC0(u8 *b, u32 side)
{
    return func_0034F140(b, side) != 0;
}

/* 0x0034FFE0, 0xAC bytes, matching. Whether base `b` links to a base of side `side` without flag 2. */
int func_0034FFE0(u8 *b, int side)
{
    u32 n = func_0034EEF0(b), k;

    for (k = 0; k < n; k++) {
        u8 *x = func_0034EF60(b, k);

        if (x != 0 && side == func_0034EDB0(x) && func_0034EE80(x) == 0)
            return 1;
    }
    return 0;
}

/* 0x00350090, 0x9C bytes. Whether base `b` (flag 1) is a main base taken from its side. */
int func_00350090(u8 *b)
{
    if (func_0034EE60(b) != 0) {
        int o = func_0034EDB0(b), i = func_0034ED40(b);

        if (i == func_0035F200(0)) {
            if (o != 0)
                return 1;
        } else if (i == func_0035F200(1) && o != 1) {
            return 1;
        }
    }
    return 0;
}

/* 0x00350130, 0x174 bytes. Who holds base `b` now: a side's base falls to the enemy standing
 * alone on it (unless flag 1 keeps it); a neutral base goes to the side standing on it (one at
 * random when both). */
u32 func_00350130(u8 *b)
{
    u32 o = func_0034EDB0(b), r = o;

    if (o < 2) {
        u32 e = func_0035D5A0(o);

        if (func_0034FFC0(b, e) != 0 && func_0034FFC0(b, o) == 0) {
            r = e;
            if (func_0034EE60(b) != 0 && func_00350090(b) == 0 && func_0034FFE0(b, e) == 0)
                r = o;
        }
    } else {
        u32 m = 3, s;

        for (s = 0; s < 2; s++) {
            if (func_0034FFC0(b, s) != 0) {
                if (m < 2) {
                    if (RANDOM() % 100 < 0x32)
                        m = s;
                } else {
                    m = s;
                }
            }
        }
        if (m < 2)
            r = m;
    }
    return r;
}

/* 0x003502B0, 0x158 bytes. The unit that takes base `b` for side `side`: a player standing on
 * it, else the side's lowest numbered unit there, else player 0's. */
u8 *func_003502B0(u8 *b, u32 side)
{
    short c[2];
    u32 best = 0x1AD, k;
    int p;

    func_0034EDB0(b);
    func_0034ED90(b, (u8 *)c);
    for (p = 0; p < 2; p++) {
        if (*(int *)(g_00669D60 + p * 0x48 + 0xA0) != 0 && c[0] == *(short *)(func_0035DCD0(p) + 0x40))
            best = func_0035DC70(p) & 0xFFFF;
    }
    if (best == 0x1AD) {
        for (k = 0; k < 0x14; k++) {
            u8 *u = func_0034F280(b, k);

            if (u != 0 && side == u[0x79]) {
                u32 i = (u - g_00693970) / 0x88;

                if (i < best)
                    best = i;
            }
        }
    }
    if (best == 0x1AD)
        best = func_0035DC70(0) & 0xFFFF;
    return UNIT(best);
}
