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
