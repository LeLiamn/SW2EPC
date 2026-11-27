/*
 * emp_fld_group.c - the Empire battles' groups: the 0x47 soldier groups (0x68 bytes at
 * 0x006A1D58; word 0 their leader unit, word 0x19 flags) and the 16 officers' group records
 * (0x30 bytes at 0x007B5F70; a default one at 0x007B5F40). Original file name unknown (it lies
 * between emp_ev_predata.c and emp_FldBase.c). Written so far: parts of 0x00338410-.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Group record: +0x00 the officer (0x19F = none), +0x02 / +0x03 its order and target, +0x04 the
 * order's age, +0x05 / +0x06 a second order and target, +0x07 its age, +0x08 / +0x09 the stance
 * and its argument, +0x0A a timer, +0x0B-0x0F five counters, +0x10-0x18 nine contact counts,
 * +0x1A / +0x1C strength and its most, +0x1E, +0x23, +0x26 the formation slot, +0x27, +0x28,
 * +0x2A a linked group (0x47 = none).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A1D58[][0x68];            /* the soldier groups */
extern u8 g_007B5F40[0x30];              /* the default group record */
extern u8 g_007B5F70[0x10][0x30];        /* the officers' group records */
extern u8 g_006A3A30[][0xC0];            /* the battle officers */
extern u8 g_00693970[];                  /* the game state (units first, 0x88 bytes) */

#define GROUP(i) ((u8 **)g_006A1D58[i])
#define GI(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)
#define INFO(g) func_00338410(GI(g))
#define LEADER(g) (*(u8 **)(g))
#define UNIT_FLAGS(u) (*(u32 *)((u) + 0x80))

void func_00118850(void *p, int n);
void func_00118AC0(void *to, const void *from, int n);
void func_0035F280(u32 s, int d);
int func_0033C6A0(u8 **g);
void func_0034BA00(u8 **g, u32 old);
int func_0033B050(u8 **g);
int func_0033B320(u8 **g);
u8 **func_0033EF80(u32 k);
u8 *func_002EFB00(int k);

int func_003386D0(u8 **g, u32 order, u32 target);
int func_003387C0(u8 **g, u32 order, u32 target);

/* 0x00338410, 0x38 bytes, matching. Group record `k` (the default one past 15). */
u8 *func_00338410(u32 k)
{
    return k < 0x10 ? g_007B5F70[k] : g_007B5F40;
}

/* 0x00338450, 0xA4 bytes. Resets the default group record. */
void func_00338450(void)
{
    u8 *r = g_007B5F40;

    func_00118850(r, 0x30);
    *(u16 *)r = 0x19F;
    r[0x26] = 10;
    r[2] = 7;
    r[3] = 0xFF;
    r[5] = 0xD;
    r[6] = 0xFF;
    r[8] = 5;
    r[9] = 0xFF;
    r[0x25] = 0x47;
    r[0x29] = 0xFF;
    r[0x27] = 4;
    r[0x2A] = 0x47;
}

/* 0x00338500, 0xE0 bytes. Changes group `g`'s strength by `d` (0 to its most; the side's count
 * follows); the change. */
int func_00338500(u8 **g, int d)
{
    u32 k = GI(g);
    u16 old = *(u16 *)(func_00338410(k) + 0x1A);
    int v = old + d;

    if (v < 1)
        v = 0;
    if ((int)*(u16 *)(func_00338410(k) + 0x1C) < v)
        v = *(u16 *)(func_00338410(k) + 0x1C);
    *(short *)(func_00338410(k) + 0x1A) = v;
    func_0035F280(LEADER(g)[0x79], v - old);
    return v - old;
}

/* 0x003385E0, 0xF0 bytes. Sets group `g`'s stance (and its argument); whether it changed (the
 * orders reset unless func_0033C6A0). */
int func_003385E0(u8 **g, u32 stance, u32 arg)
{
    u32 k = GI(g);
    u8 old = func_00338410(k)[8];

    if (stance == old && arg == func_00338410(k)[9])
        return 0;
    func_00338410(k)[8] = stance;
    func_00338410(k)[9] = arg;
    if (func_0033C6A0(g) == 0) {
        func_003386D0(g, 6, 0xFF);
        func_003387C0(g, 0xC, 0xFF);
    }
    return 1;
}

/* 0x003386D0, 0xE8 bytes. Sets group `g`'s order; whether it changed (its second order reset). */
int func_003386D0(u8 **g, u32 order, u32 target)
{
    u32 k = GI(g);
    u8 old = func_00338410(k)[2];

    if (order == old && target == func_00338410(k)[3])
        return 0;
    func_00338410(k)[2] = order;
    func_00338410(k)[3] = target;
    func_003387C0(g, 0xC, 0xFF);
    func_00338410(k)[4] = 0;
    func_0034BA00(g, old);
    return 1;
}

/* 0x003387C0, 0xC0 bytes. Sets its second order; whether it changed. */
int func_003387C0(u8 **g, u32 order, u32 target)
{
    u32 k = GI(g);

    if (order == func_00338410(k)[5] && target == func_00338410(k)[6])
        return 0;
    func_00338410(k)[5] = order;
    func_00338410(k)[6] = target;
    func_00338410(k)[7] = 0;
    return 1;
}

/* 0x00338880, 0x70 bytes. Ages its order (up to 0xFF). */
void func_00338880(u8 **g)
{
    u32 k = GI(g);
    char a = func_00338410(k)[4];

    if (a != -1)
        func_00338410(k)[4] = a + 1;
}

/* 0x003388F0, 0x70 bytes. Ages its second order. */
void func_003388F0(u8 **g)
{
    u32 k = GI(g);
    char a = func_00338410(k)[7];

    if (a != -1)
        func_00338410(k)[7] = a + 1;
}

/* 0x00338960, 8 bytes, matching. */
int func_00338960(void)
{
    return 0x3C;
}

/* 0x00338970, 0x84 bytes. Counts its timer down (back to 60 after 0). */
void func_00338970(u8 **g)
{
    u32 k = GI(g);
    u8 *r = func_00338410(k);
    char v = r[10] == 0 ? func_00338960() : r[10] - 1;

    func_00338410(k)[10] = v;
}

/* 0x00338A00, 0x74 bytes. */
void func_00338A00(u8 **g)
{
    u32 k = GI(g);
    char v = func_00338410(k)[0x23];

    if (v != 0)
        func_00338410(k)[0x23] = v - 1;
}

/* 0x00338A80, 0xA0 bytes. Its morale shown: strength / 100 + 0x5F (at most 0xFF). */
int func_00338A80(u8 **g)
{
    u32 k = GI(g);

    if (*(u16 *)(func_00338410(k) + 0x1A) / 100 + 0x5F < 0x100)
        return *(u16 *)(func_00338410(k) + 0x1A) / 100 + 0x5F;
    return 0xFF;
}

/* 0x00338B20, 0x74 bytes. */
void func_00338B20(u8 **g)
{
    u32 k = GI(g);
    char v = func_00338410(k)[0x28];

    if (v != 0)
        func_00338410(k)[0x28] = v - 1;
}

/* 0x00338BA0, 0x80 bytes. Its linked group (0 for none). */
u8 **func_00338BA0(u8 **g)
{
    u8 l = INFO(g)[0x2A];

    return l < 0x47 ? GROUP(l) : 0;
}

/* 0x00338C20, 0x60 bytes. The linked group's +0x27 (4 for none). */
u8 func_00338C20(u8 **g)
{
    u8 **l = func_00338BA0(g);

    return l == 0 ? 4 : INFO(l)[0x27];
}

/* 0x00338C80, 0x128 bytes. Counts a contact of group `g` with group `h` (by `h`'s slot; 8 for
 * the enemy's), up to 0xFF. */
void func_00338C80(u8 **g, u8 **h)
{
    u32 k, slot;
    u8 v;

    if (g == 0 || h == 0 || func_0033B050(g) == 0 || func_0033B050(h) == 0)
        return;
    slot = func_0033B320(h) == 0 ? GI(h) & 7 : 8;
    k = GI(g);
    v = func_00338410(k)[slot + 0x10];
    if (v != 0xFF) {
        u32 n = v + 1;

        if (n > 0xFF)
            n = 0xFF;
        func_00338410(k)[slot + 0x10] = n;
    }
}

/* 0x00338DB0, 0x70 bytes, matching. Clears its five counters. */
void func_00338DB0(u8 **g)
{
    u32 k;

    for (k = 0; k < 5; k++)
        INFO(g)[k + 0xB] = 0;
}

/* 0x00338E20, 0x70 bytes, matching. Clears its contact counts. */
void func_00338E20(u8 **g)
{
    u32 k;

    for (k = 0; k < 9; k++)
        INFO(g)[k + 0x10] = 0;
}

/* 0x00338E90, 0xB8 bytes. Saves the group records into save image `p` (with each officer's
 * current musou). */
void func_00338E90(u8 *p)
{
    u32 k;

    func_00118AC0(p + 0x56E, g_007B5F70, 0x300);
    for (k = 0; k < 0x10; k++, p += 0x30) {
        u8 **g = func_0033EF80(k);

        if ((((u32 *)g)[0x19] & 1) != 0 && (UNIT_FLAGS(LEADER(g)) & 0x20000) != 0)
            *(u16 *)(p + 0x58E) = *(u16 *)(g_006A3A30[*(int *)(LEADER(g) + 0x14)] + 0x88);
    }
}

/* 0x00338F50, 0x30 bytes, matching. Loads them. */
void func_00338F50(void)
{
    func_00118AC0(g_007B5F70, func_002EFB00(9) + 0x56E, 0x300);
}

/* 0x00338F80, 0x98 bytes. Clears every officer group's formation slot. */
void func_00338F80(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++)
            INFO(func_0033EF80(k + s * 8))[0x26] = 0;
    }
}
