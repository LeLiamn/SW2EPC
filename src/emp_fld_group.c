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

/* Formation slots, group set-up and the groups' frame updates (0x00339020-0x0033B024). */

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 g_0045D030[8];                 /* (small data) the default slot of each side */
extern int g_00669F9C;                   /* the battle frame counter */
extern u32 g_00669F60;
extern int g_006AA5F0;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define GFLAGS(g) (((u32 *)(g))[0x19])
#define GSTRENGTH(g) (((int *)(g))[0x13])
#define ACTIVE(f) (((f) & 1) != 0 && ((f) & 0x8C40002) == 0)
#define ALIVE(f) (ACTIVE(f) && ((f) & 4) == 0)
#define OFFICER(i) g_006A3A30[i]

int func_0033B090(u8 **g);
int func_00363770(u32 s, u32 k);
int func_0036D380(u32 s, u32 k);
int func_0036D350(u32 s, u32 k);
int func_0032E7B0(void);
int func_0036D2E0(void);
u16 func_003620E0(u32 s, u32 k);
u16 func_003621F0(u32 s, u32 k);
u16 func_00362260(u32 s, u32 k);
int func_003628D0(u32 s, u32 k);
int func_0035F190(u32 side);
int func_00353A10(u8 *u);
int func_0033CC80(u8 **g, u32 k);
int func_003F7780(int s, int k);
int func_0035F340(u32 side);
void func_0035F310(u32 side, int n);
u8 func_0035D5A0(u32 side);
int func_0035F200(u32 side);
int func_0034EC80(u8 k);
int func_00352690(int c, u8 a);
int func_00352240(int c, u8 a);
void func_0034ED90(int c, u8 *pos);
void func_0033DCA0(u8 **g, u8 *pos);
void func_0035CB30(u32 k);
int func_0033CEA0(u8 **g, u8 a);
int func_0036F390(u32 side, int k);
u16 func_0034A470(void);
u8 **func_0034A740(u8 *u);
void func_0035CB60(u32 k, u32 h);
u32 func_003DCEE0(u8 *a, u8 *b);
void func_0033D920(u8 *u, int a, int b);
void func_001EE3B0(u8 *u);
int func_0036D310(void);
u8 *func_0035DCD0(int p);

/* `v` kept within 1-1000 (an army's strength). */
static int clamp1000(int v)
{
    return v < 2 ? 1 : v > 1000 ? 1000 : v;
}

/* `v` kept within 0-`m`. */
static short clamp0(int v, int m)
{
    int t = v < m ? v : m;

    return t < 1 ? 0 : t;
}

/* 0x00339020, 0x37C bytes. Gives the officers' groups their formation slots (10 slots, shared
 * by both sides: the second side takes the first side's slot of the same kind, else a free one,
 * else one of its own). */
void func_00339020(void)
{
    int slot[2][8], kind[12], owner[12];
    u32 s, k, j;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            slot[s][k] = 10;
            if (func_00363770(s, k) != 0) {
                func_0033EF80(k + s * 8);
                slot[s][k] = func_0036D380(s, k);
            }
        }
    }
    for (j = 0; j < 10; j++) {
        kind[j] = 0x19;
        owner[j] = 3;
    }
    for (k = 0; k < 8; k++) {
        if (func_00363770(0, k) != 0) {
            int v;

            func_0033EF80(k);
            v = slot[0][k];
            if (kind[v] < 0 || kind[v] > 0x18) {
                kind[v] = func_0036D350(0, k);
                owner[v] = 0;
            }
        }
    }
    for (k = 0; k < 8; k++) {
        if (func_00363770(1, k) != 0) {
            int v;

            func_0033EF80(k + 8);
            v = slot[1][k];
            if (kind[v] < 0 || kind[v] > 0x18) {
                kind[v] = func_0036D350(1, k);
                owner[v] = 1;
                continue;
            }
            for (j = 0; j < 10; j++) {
                if (kind[j] == func_0036D350(1, k))
                    break;
            }
            if (j < 10) {
                slot[1][k] = j;
                continue;
            }
            for (j = 0; j < 10; j++) {
                if (kind[j] < 0 || kind[j] > 0x18)
                    break;
            }
            if (j < 10) {
                int n = func_0036D350(1, k);

                slot[1][k] = j;
                kind[j] = n;
                owner[j] = 1;
                continue;
            }
            for (j = 0; j < 10; j++) {
                if (owner[j] == 1)
                    break;
            }
            if (j < 10)
                slot[1][k] = j;
        }
    }
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            if (func_00363770(s, k) != 0) {
                u8 **g = func_0033EF80(k + s * 8);

                INFO(g)[0x26] = slot[s][k];
            }
        }
    }
}

/* 0x003393B0, 0xC0 bytes. Gives every officer group its side's default slot. */
void func_003393B0(void)
{
    u8 t[8];
    u32 s, k;

    *(u32 *)t = *(u32 *)g_0045D030;
    *(u32 *)(t + 4) = *(u32 *)(g_0045D030 + 4);
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++)
            INFO(func_0033EF80(k + s * 8))[0x26] = t[s];
    }
}

/* 0x00339470, 0x5C bytes, matching. Sets the formation slots by the battle's kind. */
void func_00339470(void)
{
    if (func_0032E7B0() != 0)
        func_00338F80();
    else if (func_0036D2E0() != 0)
        func_00339020();
    else
        func_003393B0();
}

/* 0x003394D0, 0x280 bytes. Resets the 16 group records (then the default one and the slots). */
void func_003394D0(void)
{
    u32 k, j;

    for (k = 0; k < 0x10; k++) {
        int n;

        func_00338410(k)[2] = 6;
        func_00338410(k)[3] = 0xFF;
        func_00338410(k)[4] = 0;
        func_00338410(k)[5] = 0xC;
        func_00338410(k)[6] = 0xFF;
        func_00338410(k)[7] = 0;
        func_00338410(k)[8] = 4;
        func_00338410(k)[9] = 0xFF;
        n = func_00338960();
        func_00338410(k)[10] = n == 0 ? 0 : (int)RANDOM() % n;
        for (j = 0; j < 5; j++)
            func_00338410(k)[j + 0xB] = 0;
        for (j = 0; j < 9; j++)
            func_00338410(k)[j + 0x10] = 0;
        func_00338410(k)[0x19] = 0;
        func_00338410(k)[0x25] = 0x47;
        *(u16 *)(func_00338410(k) + 0x1A) = 0;
        *(u16 *)(func_00338410(k) + 0x1C) = 0;
        *(u16 *)(func_00338410(k) + 0x1E) = 0;
        *(u16 *)(func_00338410(k) + 0x20) = 0;
        func_00338410(k)[0x22] = 0;
        func_00338410(k)[0x23] = 0;
        func_00338410(k)[0x24] = 0;
        func_00338410(k)[0x27] = 4;
        func_00338410(k)[0x28] = 0;
        func_00338410(k)[0x29] = 0xFF;
        func_00338410(k)[0x2A] = 0x47;
        func_00338410(k)[0x2C] = 0xFF;
    }
    func_00338450();
    func_00339470();
    g_006AA5F0 = 0;
}

/* 0x00339760, 0x1A4 bytes. Fills the active officer groups' records from the battle set-up
 * (officer, strengths; the side's army strength). */
void func_00339760(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            u8 **g = func_0033EF80(k + s * 8);

            if (g != 0 && (GFLAGS(g) & 1) != 0) {
                u32 i = GI(g);
                u16 v;

                *(u16 *)func_00338410(i) = func_003620E0(s, k);
                *(u16 *)(func_00338410(i) + 0x1C) = func_003621F0(s, k);
                v = func_00362260(s, k);
                *(u16 *)(func_00338410(i) + 0x1E) = v;
                *(u16 *)(func_00338410(i) + 0x1A) = v;
                GSTRENGTH(g) = clamp1000(func_0035F190(s));
                if (func_003628D0(s, k) != 0)
                    GFLAGS(g) |= 0x10;
            }
        }
    }
}

/* 0x00339910, 8 bytes, matching. */
void func_00339910(void)
{
}

/* 0x00339920, 0x410 bytes. Sets group `g`'s army strength (word 0x13: its side's, or a value
 * built from its front, its contacts and the side's tactics while +0x23 is clear; 1 when the
 * leader is down). */
void func_00339920(u8 **g)
{
    u8 side;
    int army;

    if (g == 0 || (GFLAGS(g) & 1) == 0)
        return;
    side = LEADER(g)[0x79];
    if (side >= 2)
        return;
    army = func_0035F190(side);
    if (func_0033B090(g) == 0) {
        u32 f = UNIT_FLAGS(LEADER(g));
        int r;
        u32 k;

        if (!ALIVE(f)) {
            GSTRENGTH(g) = 1;
            return;
        }
        r = func_00353A10(LEADER(g));
        if (r == -100) {
            GSTRENGTH(g) = 1;
            return;
        }
        k = GI(g);
        if (func_00338410(k)[0x23] == 0) {
            int v = r > 0x1E ? 4 : 3, base;
            u32 j;

            if (side == 0) {
                for (j = 0; j < 2; j++) {
                    if (func_0033CC80(g, j) != 0)
                        v += 2;
                }
            }
            if (func_003F7780(side, 7) != 0)
                v = (int)((float)v * 2.0f);
            if (func_003F7780(side, 8) != 0)
                v = (int)((float)v * 4.0f);
            if (func_003F7780(side, 9) != 0)
                v = (int)((float)v * 6.0f);
            if ((g_00669F60 & 0xC) == 0)
                base = GSTRENGTH(g);
            else
                base = LEADER(g)[0x79] == 0 ? 350 : 650;
            GSTRENGTH(g) = clamp1000(v + base);
            if ((g_00669F60 & 0xC) == 0)
                base = GSTRENGTH(g);
            else
                base = LEADER(g)[0x79] == 0 ? 350 : 650;
            if (base > 899) {
                func_00338410(k)[0x23] = func_00338A80(g);
                GSTRENGTH(g) = 1000;
            }
        } else {
            func_00338A00(g);
            if (func_00338410(k)[0x23] == 0)
                GSTRENGTH(g) = clamp1000(army);
            else
                GSTRENGTH(g) = 1000;
        }
    } else {
        GSTRENGTH(g) = clamp1000(army);
    }
}

/* 0x00339D30, 0xC0 bytes. A reinforcement delay for group `g` (60 and up, shorter when strong). */
int func_00339D30(u8 **g)
{
    u8 *r = INFO(g);
    int v = 0x5A - *(u16 *)(r + 0x1A) * 0x3Cu / 10000 + (int)RANDOM() % 0x5A;

    return v < 0x3D ? 0x3C : v;
}

/* 0x00339DF0, 0x1C8 bytes. Counts group `g`'s reinforcement delay down; at 0 sends a
 * reinforcement from its side's base when the way is free (else waits again). */
void func_00339DF0(u8 **g)
{
    u32 k = GI(g);
    u8 side;

    if (func_00338410(k)[0x22] == 0)
        return;
    side = LEADER(g)[0x79];
    if (func_0035F340(side) == 0) {
        func_00338410(k)[0x22] = 0;
        return;
    }
    if (func_00338410(k)[0x22] == 0)
        return;
    func_00338410(k)[0x22] = func_00338410(k)[0x22] - 1;
    if (func_00338410(k)[0x22] != 0 || LEADER(g) == 0 || !ACTIVE(UNIT_FLAGS(LEADER(g))))
        return;
    {
        u8 a = func_0035D5A0(side);
        int c = func_0034EC80(func_0035F200(side));
        u8 pos[4];

        if (func_00352690(c, a) != 0 && func_00352240(c, a) != 0) {
            func_00338410(k)[0x22] = func_00339D30(g);
            return;
        }
        func_0034ED90(c, pos);
        func_0033DCA0(g, pos);
        func_0035CB30(k);
        func_0035F310(side, func_0035F340(side) - 1);
    }
}

/* 0x00339FC0, 0x2EC bytes. Every 500 frames (for 50), a hurt leader standing off its side's
 * front gets back up to 10 life (+0x4E, +0x52) for twice that of its group's strength (once
 * with tactic 0xC). */
void func_00339FC0(u8 **g)
{
    u8 *l;
    u32 f;
    int d;
    short n;

    if (g_00669F9C % 500 >= 0x32)
        return;
    l = LEADER(g);
    f = UNIT_FLAGS(l);
    if (!ALIVE(f) || (f & 0x20000) != 0 || *(short *)(INFO(g) + 0x1A) == 0)
        return;
    if (func_0033CEA0(g, func_0035D5A0(LEADER(g)[0x79])) != 0)
        return;
    d = *(short *)(l + 0x4C) - *(short *)(l + 0x4E);
    if (d <= 0)
        return;
    func_00353A10(l);
    if (d > 10)
        d = 10;
    n = clamp0(*(short *)(l + 0x4E) + d, *(short *)(l + 0x4C));
    *(short *)(l + 0x4E) = n;
    *(short *)(l + 0x52) = clamp0(n < *(short *)(l + 0x52) ? *(short *)(l + 0x52) : n,
                                  *(short *)(l + 0x50));
    d *= 2;
    if (func_0036F390(LEADER(g)[0x79], 0xC) != 0)
        d /= 2;
    func_00338500(g, -d);
}

/* 0x0033A2B0, 0x3AC bytes. Tactics 4-6 heal group `g`'s 13 units a little now and then (their
 * troops' soldiers for officer units). */
void func_0033A2B0(u8 **g)
{
    u8 side;
    int add = 0;
    u32 k;

    if (g_00669F9C % 0x32 >= 0x32)
        return;
    side = LEADER(g)[0x79];
    if (side < 2) {
        if (func_003F7780(side, 4) != 0 && g_00669F9C % 200 < 0x32)
            add = 1;
        if (func_003F7780(side, 5) != 0 && g_00669F9C % 0x96 < 0x32)
            add = 1;
        if (func_003F7780(side, 6) != 0 && g_00669F9C % 100 < 0x32)
            add = 1;
    }
    if (add == 0)
        return;
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u == 0 || !ACTIVE(UNIT_FLAGS(u)))
            continue;
        if ((UNIT_FLAGS(u) & 0x20000) == 0) {
            short n = clamp0(*(short *)(u + 0x4E) + add, *(short *)(u + 0x4C));
            int m = *(short *)(u + 0x52) + add;

            *(short *)(u + 0x4E) = n;
            *(short *)(u + 0x52) = clamp0(n < m ? m : n, *(short *)(u + 0x50));
        } else {
            u8 *o;

            for (o = OFFICER(*(int *)(u + 0x14)); o != 0; o = *(u8 **)(o + 4)) {
                short n = clamp0(*(short *)(o + 0x82) + add, *(short *)(o + 0x80));

                *(short *)(o + 0x82) = n;
                if (*(short *)(o + 0x84) < n)
                    *(short *)(o + 0x84) = n;
            }
        }
    }
}

/* 0x0033A660, 8 bytes, matching. */
void func_0033A660(u8 **g)
{
}

/* 0x0033A670, 0x198 bytes. Counts group `g`'s link timer down; at 0 ends a link of kind 3 (the
 * linked group, when still active, is freed too). */
void func_0033A670(u8 **g)
{
    u32 k = GI(g);

    if (func_00338410(k)[0x28] == 0)
        return;
    func_00338B20(g);
    if (func_00338410(k)[0x28] != 0 || func_00338410(k)[0x27] != 3)
        return;
    {
        u8 **h = GROUP(func_00338410(k)[0x29]);

        if (h != 0 && (GFLAGS(h) & 1) != 0 && ALIVE(UNIT_FLAGS(LEADER(h))))
            INFO(h)[0x2A] = 0x47;
    }
    func_00338410(k)[0x27] = 4;
    func_00338410(k)[0x29] = 0xFF;
}

/* 0x0033A810, 0x250 bytes. Raises group `g`'s leader's musou a little (5 at most for kind 2
 * leaders, else 1 one time in 5): in the record for plain units, in the officer for officers. */
void func_0033A810(u8 **g)
{
    u8 *l = LEADER(g);
    u32 f = UNIT_FLAGS(l);
    int n = 0;

    if (!ALIVE(f) || (f & 0x30) != 0)
        return;
    if (l[0x7A] == 2)
        n = (int)RANDOM() % 5 + 1;
    else if ((int)RANDOM() % 100 < 0x14)
        n = 1;
    if ((UNIT_FLAGS(l) & 0x20000) == 0) {
        u32 v = *(short *)(INFO(g) + 0x20) + n;

        if (func_0034A470() < v)
            v = func_0034A470();
        *(short *)(INFO(g) + 0x20) = v;
    } else {
        u8 *o = OFFICER(*(int *)(l + 0x14));

        *(short *)(o + 0x88) = clamp0(*(short *)(o + 0x88) + n, *(short *)(o + 0x86));
    }
}

/* 0x0033AA60, 0x154 bytes. Group `g`'s meeting timer (+0x2C): a first-side kind 2 leader that
 * meets another group starts it (and tells func_0035CB60); then it counts up to 0xFE. */
void func_0033AA60(u8 **g)
{
    u8 *l = LEADER(g);
    u32 k = GI(g);

    if ((char)func_00338410(k)[0x2C] == -1) {
        u8 **h;

        if (l[0x7A] == 2 && *(u8 **)(l + 0x18) != 0
            && (h = func_0034A740(*(u8 **)(l + 0x18))) != 0
            && func_0033B050(g) != 0 && func_0033B050(h) != 0 && l[0x79] == 0) {
            func_0035CB60(k, GI(h));
            func_00338410(k)[0x2C] = 0;
        }
    } else if (l[0x7A] == 2) {
        u8 v = func_00338410(k)[0x2C];

        if (v < 0xFE)
            func_00338410(k)[0x2C] = v + 1;
    }
}

/* 0x0033ABC0, 0x19C bytes. Now and then, group `g`'s units that strayed from their leader (10
 * and more away, one time in 3) are sent back. */
void func_0033ABC0(u8 **g)
{
    u8 *l;
    u32 k;

    if (g_00669F9C % 0xFA <= 0x31)
        return;
    l = LEADER(g);
    if (!ALIVE(UNIT_FLAGS(l)))
        return;
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u != 0 && ACTIVE(UNIT_FLAGS(u)) && u != l && (UNIT_FLAGS(u) & 0x20000) == 0
            && func_003DCEE0(l, u) > 9 && (int)RANDOM() % 100 < 0x1E) {
            func_0033D920(u, 0, 0);
            func_001EE3B0(u);
        }
    }
}

/* 0x0033AD60, 0x1C bytes, matching. */
void func_0033AD60(u8 **g)
{
    func_00338970(g);
}

/* 0x0033AD80, 0x1C bytes, matching. */
void func_0033AD80(u8 **g)
{
    func_00338880(g);
}

/* 0x0033ADA0, 0x1C bytes, matching. */
void func_0033ADA0(u8 **g)
{
    func_003388F0(g);
}

/* 0x0033ADC0, 0x158 bytes. When func_0036D310, a second-side group turns all its units to face
 * player 0 (their target). */
void func_0033ADC0(u8 **g)
{
    u8 *t;
    u32 k;

    if (g == 0 || func_0036D310() == 0)
        return;
    if (!ALIVE(UNIT_FLAGS(LEADER(g))) || LEADER(g)[0x79] == 0)
        return;
    t = func_0035DCD0(0);
    if (t == 0)
        return;
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u != 0 && ACTIVE(UNIT_FLAGS(u)) && u[0x7A] != 3) {
            *(short *)(u + 0x44) = *(short *)(t + 0x40);
            *(unsigned long long *)(u + 0x38) = 0;
            *(u32 *)(u + 0x84) |= 0x10;
            *(u8 **)(u + 0x1C) = t;
            *(u32 *)(u + 0x84) |= 0x10;
        }
    }
}

/* 0x0033AF20, 0x84 bytes. Group `g`'s frame update. */
void func_0033AF20(u8 **g)
{
    func_00339920(g);
    func_00339DF0(g);
    func_00339FC0(g);
    func_0033A2B0(g);
    func_0033A660(g);
    func_0033A670(g);
    func_0033A810(g);
    func_0033AA60(g);
    func_0033ABC0(g);
    func_0033ADC0(g);
    func_0033AD60(g);
    func_0033AD80(g);
    func_0033ADA0(g);
}

/* 0x0033AFB0, 0x74 bytes. Updates one officer group a frame (in turn over 60 frames). */
void func_0033AFB0(void)
{
    u32 k = g_00669F9C % 0x3C;

    if (k < 0x10 && (GFLAGS(GROUP(k)) & 1) != 0)
        func_0033AF20(GROUP(k));
}

/* Group predicates and accessors (0x0033B030-0x0033D04C). Orders and stances that name a place
 * (a cell: func_0034EC80) or another group (by index). */

int func_00362570(void);
int func_0033B1E0(u8 **g);
int func_0033B690(u8 **g);
extern u8 g_00669D60[];
int func_0034A5B0(u8 *u);
int func_0036F520(u8 a, int k);
int func_002F3DC0(u16 o);
int func_0036D3B0(u16 o);
int func_0036D400(u16 o);
int func_0035F840(void);
int func_002F5AA0(u16 o);
u8 **func_0033F110(u8 side);
int func_002F4660(u16 o);
int func_002F41E0(u16 o);
int func_002F77A0(u16 a, u16 b);
int func_002F77F0(u16 a, u16 b);
int func_0036D850(u16 a, u16 b);
int func_0036D970(u16 a, u16 b, int c, int d);
int func_002F4080(u16 o);
int func_0034ED40(u8 **g);
int func_0035D560(u8 a, u8 b);
u8 func_0034EDB0(int c);
int func_0034ECA0(u8 *pos);
u8 **func_0035DD10(int p);
int func_00353920(u8 *pos, u8 a);
u8 **func_0033F070(u8 s, u32 j);

extern int g_00415210[12][2];            /* officer pairs (?) */
extern u8 g_006AA5F4[2][0x10];           /* per side */

#define REC_OFFICER(g) (*(u16 *)INFO(g))

/* 0x0033B030, 0x1C bytes, matching. */
int func_0033B030(int v)
{
    return v == 0 ? 3 : 4;
}

/* 0x0033B050, 0x40 bytes. Whether `g` is one of the 16 officer groups. */
int func_0033B050(u8 **g)
{
    return GI(g) < 0x10;
}

/* 0x0033B090, 0x14 bytes, matching. */
int func_0033B090(u8 **g)
{
    return UNIT_FLAGS(LEADER(g)) & 0x8000000;
}

/* 0x0033B0B0, 0x90 bytes. Whether `g` is an officer group in play with soldiers left. */
int func_0033B0B0(u8 **g)
{
    if (func_0033B050(g) == 0)
        return 0;
    return func_0033B1E0(g) != 0 && *(short *)(INFO(g) + 0x1A) != 0;
}

/* 0x0033B140, 0x10 bytes, matching. */
int func_0033B140(u8 **g)
{
    return UNIT_FLAGS(LEADER(g)) & 0x200;
}

/* 0x0033B150, 0x88 bytes. */
int func_0033B150(u8 **g)
{
    int v = func_00362570();

    if (v == 0x12 || v == 0x11 || v == 0x10 || v == 1 || v == 0 || LEADER(g)[0x79] != 1
        || func_0033B140(g) == 0)
        return 0;
    return 1;
}

/* 0x0033B1E0, 0x5C bytes. Whether group `g` is in play (its leader not out). */
int func_0033B1E0(u8 **g)
{
    u8 *l;

    if (g == 0 || (GFLAGS(g) & 1) == 0)
        return 0;
    l = LEADER(g);
    if (l == 0 || (UNIT_FLAGS(l) & 1) == 0)
        return 0;
    return (UNIT_FLAGS(l) & 0x40000) == 0;
}

/* 0x0033B240, 0xE0 bytes. Whether group `g` should fall back (weaker than its leader's need, far
 * behind its front or under tactic 0x15); never for the slots 6 and 7. */
int func_0033B240(u8 **g)
{
    u8 *l = LEADER(g);

    if (l == 0 || (UNIT_FLAGS(l) & 1) == 0)
        return 0;
    if (func_0033B690(g) != 0)
        return 0;
    if (func_0034A5B0(l) >= *(u16 *)(INFO(g) + 0x1A))
        return 1;
    if (func_00353A10(l) < -0x32)
        return 1;
    return func_0036F520(func_0035D5A0(l[0x79]), 0x15) != 0;
}

/* 0x0033B320, 0x88 bytes. Whether `g` is an enemy officer group (slots 0-7 of side 1, 8-15 of
 * side 0). */
int func_0033B320(u8 **g)
{
    u32 k = GI(g);

    if (k < 8) {
        if (LEADER(g)[0x79] == 1)
            return 1;
    } else {
        if (k > 0xF)
            return 0;
        if (LEADER(g)[0x79] == 0)
            return 1;
    }
    return 0;
}

/* 0x0033B3B0, 0x88 bytes. */
int func_0033B3B0(u8 **g)
{
    if (func_0036D2E0() == 0 || func_0033B050(g) == 0)
        return 0;
    return func_002F3DC0(REC_OFFICER(g)) == 3;
}

/* 0x0033B440, 0x98 bytes. */
int func_0033B440(u8 **g)
{
    if (func_0036D2E0() == 0 || func_0033B050(g) == 0)
        return 0;
    if (LEADER(g)[0x79] != 0)
        return 0;
    return func_0036D3B0(REC_OFFICER(g));
}

/* 0x0033B4E0, 0x98 bytes. */
int func_0033B4E0(u8 **g)
{
    if (func_0036D2E0() == 0 || func_0033B050(g) == 0)
        return 0;
    if (LEADER(g)[0x79] != 0)
        return 0;
    return func_0036D400(REC_OFFICER(g));
}

/* 0x0033B580, 0x58 bytes. */
int func_0033B580(u8 **g)
{
    return func_0035F840() == GI(g);
}

/* 0x0033B5E0, 0x48 bytes, matching. */
int func_0033B5E0(u8 **g)
{
    u32 k = GI(g) & 7;

    return k < 3 || k == 6;
}

/* 0x0033B630, 0x58 bytes, matching. */
int func_0033B630(u8 **g)
{
    u32 k = GI(g) & 7;

    return (k > 2 && k < 6) || k == 7;
}

/* 0x0033B690, 0x4C bytes, matching. */
int func_0033B690(u8 **g)
{
    u32 k = GI(g) & 7;

    return k == 6 || k == 7;
}

/* 0x0033B6E0, 0x14 bytes, matching. Whether its leader is an officer. */
int func_0033B6E0(u8 **g)
{
    return UNIT_FLAGS(LEADER(g)) & 0x20000;
}

/* 0x0033B700, 0x2C bytes. */
u8 *func_0033B700(u8 **g)
{
    u8 *l = LEADER(g);

    return (UNIT_FLAGS(l) & 0x20000) == 0 ? l + 0x28 : l + 0x30;
}

/* 0x0033B730, 0xC bytes, matching. Its leader's cell. */
u8 *func_0033B730(u8 **g)
{
    return LEADER(g) + 0x40;
}

/* 0x0033B740, 0x70 bytes. Its leader's life. */
short func_0033B740(u8 **g)
{
    u8 *l;

    if (g == 0)
        return 0;
    l = LEADER(g);
    if (l == 0)
        return 0;
    if ((UNIT_FLAGS(l) & 0x20000) == 0)
        return *(short *)(l + 0x4E);
    return *(short *)(OFFICER(*(int *)(l + 0x14)) + 0x82);
}

/* 0x0033B7B0, 0xB0 bytes. Its leader's life in percent. */
int func_0033B7B0(u8 **g)
{
    u8 *l;
    int cur, max;

    if (g == 0)
        return 0;
    l = LEADER(g);
    if (l == 0)
        return 0;
    if ((UNIT_FLAGS(l) & 0x20000) == 0) {
        cur = *(short *)(l + 0x4E);
        max = *(short *)(l + 0x4C);
    } else {
        u8 *o = OFFICER(*(int *)(l + 0x14));

        max = *(short *)(o + 0x80);
        cur = *(short *)(o + 0x82);
    }
    if (max < 2)
        max = 1;
    return cur * 100 / max;
}

/* 0x0033B860, 0x28 bytes. Its side's record. */
u8 *func_0033B860(u8 **g)
{
    return g_006AA5F4[LEADER(g)[0x79]];
}

/* 0x0033B890, 0x3C bytes, matching. */
int func_0033B890(u8 **g)
{
    if ((UNIT_FLAGS(LEADER(g)) & 0x10) != 0)
        return 0;
    if ((UNIT_FLAGS(LEADER(g)) & 0x20) != 0)
        return 1;
    return 2;
}

/* 0x0033B8D0, 0x48 bytes, matching. */
int func_0033B8D0(u8 **g)
{
    return func_002F5AA0(REC_OFFICER(g));
}

/* 0x0033B920, 0x50 bytes, matching. */
int func_0033B920(u8 **g, int v)
{
    if (func_0033B440(g) != 0)
        return 1;
    return v == func_0033B8D0(g);
}

/* 0x0033B970, 0x74 bytes. Its formation slot (its side's main group's for others). */
u8 func_0033B970(u8 **g)
{
    if (func_0033B050(g) == 0)
        g = func_0033F110(LEADER(g)[0x79]);
    return INFO(g)[0x26];
}

/* 0x0033B9F0, 0x68 bytes. */
int func_0033B9F0(u8 **g)
{
    u16 o = REC_OFFICER(g);

    return o < 0x19F ? func_002F4660(o) : 0;
}

/* 0x0033BA60, 0x24 bytes. */
int func_0033BA60(u8 **g)
{
    return func_0033B9F0(g) > 0x4F;
}

/* 0x0033BA90, 0x68 bytes. */
int func_0033BA90(u8 **g)
{
    u16 o = REC_OFFICER(g);

    return o < 0x19F ? func_002F41E0(o) : 0;
}

/* 0x0033BB00, 0xC8 bytes. Test `fn` on the officers of groups `g` and `h` (0 when one has
 * none). */
int func_0033BB00(u8 **g, u8 **h, int (*fn)(u16, u16))
{
    u16 a = REC_OFFICER(g), b = REC_OFFICER(h);

    if (a < 0x19F && b < 0x19F)
        return fn(a, b);
    return 0;
}

/* 0x0033BBD0, 0x20 bytes, matching. */
int func_0033BBD0(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, func_002F77A0);
}

/* 0x0033BBF0, 0x20 bytes, matching. */
int func_0033BBF0(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, func_002F77F0);
}

/* 0x0033BC10, 0x20 bytes, matching. */
int func_0033BC10(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, func_0036D850);
}

/* 0x0033BC30, 0xB4 bytes. Whether officers `a` and `b` make one of the 12 pairs of 0x00415210. */
int func_0033BC30(u16 a, u16 b)
{
    int t[12][2];
    int k;

    for (k = 0; k < 12; k++) {
        t[k][0] = g_00415210[k][0];
        t[k][1] = g_00415210[k][1];
    }
    for (k = 0; k < 12; k++) {
        if (func_0036D970(a, b, t[k][0], t[k][1]) != 0)
            return 1;
    }
    return 0;
}

/* 0x0033BCF0, 0x20 bytes, matching. */
int func_0033BCF0(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, func_0033BC30);
}

/* 0x0033BD10, 0x48 bytes, matching. */
int func_0033BD10(u8 **g)
{
    return func_002F4080(REC_OFFICER(g));
}

/* 0x0033BD60, 0x54 bytes, matching. */
int func_0033BD60(u8 **g)
{
    if ((UNIT_FLAGS(LEADER(g)) & 0x30) != 0)
        return 0;
    if (LEADER(g)[0x79] == 0)
        return 1;
    return func_0036F390(0, 10) != 0;
}

/* 0x0033BDC0, 0xB4 bytes. Sets group `g`'s army strength to its base plus `d` (1-1000). */
void func_0033BDC0(u8 **g, int d)
{
    int base;

    if ((g_00669F60 & 0xC) == 0)
        base = GSTRENGTH(g);
    else
        base = LEADER(g)[0x79] == 0 ? 350 : 650;
    GSTRENGTH(g) = clamp1000(base + d);
}

/* 0x0033BE80, 0x150 bytes. Changes the army strength of all side `side`'s groups in play (by
 * `pct` percent of their base, else by `d`). */
void func_0033BE80(u32 side, int pct, int d)
{
    u32 k;

    for (k = 0; k < 0x47; k++) {
        u8 **g = GROUP(k);
        u8 *l;

        if ((GFLAGS(g) & 1) == 0)
            continue;
        l = LEADER(g);
        if (!ALIVE(UNIT_FLAGS(l)) || side != l[0x79])
            continue;
        if (pct != 0) {
            int base;

            if ((g_00669F60 & 0xC) == 0)
                base = GSTRENGTH(g);
            else
                base = l[0x79] == 0 ? 350 : 650;
            d = pct * base / 100;
        }
        func_0033BDC0(g, d);
    }
}

/* 0x0033BFD0, 0x10 bytes, matching. */
u8 func_0033BFD0(u8 **g)
{
    return (*(u8 **)(LEADER(g) + 8))[5];
}

/* 0x0033BFE0, 0xC bytes, matching. */
u32 func_0033BFE0(u8 **g)
{
    return *(u32 *)(LEADER(g) + 0x70);
}

/* 0x0033BFF0, 0x68 bytes. Second orders that name a place. */
int func_0033BFF0(int v)
{
    if (v == 0xB || v == 9 || v == 7 || v == 6 || v == 5 || v == 3 || v == 1)
        return 1;
    return 0;
}

/* 0x0033C060, 0x38 bytes. Second orders that name a group. */
int func_0033C060(int v)
{
    if (v == 8 || v == 4 || v == 2)
        return 1;
    return 0;
}

/* 0x0033C0A0, 0x2C bytes. Orders that name a place. */
int func_0033C0A0(int v)
{
    if (v == 3 || v == 1)
        return 1;
    return 0;
}

/* 0x0033C0D0, 0x2C bytes. Orders that name a group. */
int func_0033C0D0(int v)
{
    if (v == 4 || v == 2)
        return 1;
    return 0;
}

/* 0x0033C100, 0x28 bytes. Stances that name a place. */
int func_0033C100(int v)
{
    if (v == 2 || v == 0)
        return 1;
    return 0;
}

/* 0x0033C130, 0x2C bytes. Stances that name a group. */
int func_0033C130(int v)
{
    if (v == 3 || v == 1)
        return 1;
    return 0;
}

/* 0x0033C160, 0x80 bytes, matching. The place of group `g`'s second order (0 for none). */
int func_0033C160(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033BFF0(func_00338410(k)[5]) == 0)
        return 0;
    return func_0034EC80(func_00338410(k)[6]);
}

/* 0x0033C1E0, 0xA4 bytes. The group of its second order. */
u8 **func_0033C1E0(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033C060(func_00338410(k)[5]) == 0)
        return 0;
    return GROUP(func_00338410(k)[6]);
}

/* 0x0033C290, 0x90 bytes. The cell its second order aims at, into `out`; whether there is one. */
int func_0033C290(u8 **g, u8 *out)
{
    int c;

    if (g == 0 || out == 0)
        return 0;
    c = func_0033C160(g);
    if (c == 0) {
        u8 **h = func_0033C1E0(g);

        if (h == 0)
            return 0;
        *(u16 *)out = *(u16 *)func_0033B730(h);
        return 1;
    }
    func_0034ED90(c, out);
    return 1;
}

/* 0x0033C320, 0x80 bytes, matching. The place of its order. */
int func_0033C320(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033C0A0(func_00338410(k)[2]) == 0)
        return 0;
    return func_0034EC80(func_00338410(k)[3]);
}

/* 0x0033C3A0, 0xA4 bytes. The group of its order. */
u8 **func_0033C3A0(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033C0D0(func_00338410(k)[2]) == 0)
        return 0;
    return GROUP(func_00338410(k)[3]);
}

/* 0x0033C450, 0x90 bytes. The cell its order aims at. */
int func_0033C450(u8 **g, u8 *out)
{
    int c;

    if (g == 0 || out == 0)
        return 0;
    c = func_0033C320(g);
    if (c == 0) {
        u8 **h = func_0033C3A0(g);

        if (h == 0)
            return 0;
        *(u16 *)out = *(u16 *)func_0033B730(h);
        return 1;
    }
    func_0034ED90(c, out);
    return 1;
}

/* 0x0033C4E0, 0x80 bytes, matching. The place of its stance. */
int func_0033C4E0(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033C100(func_00338410(k)[8]) == 0)
        return 0;
    return func_0034EC80(func_00338410(k)[9]);
}

/* 0x0033C560, 0xA4 bytes. The group of its stance. */
u8 **func_0033C560(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_0033C130(func_00338410(k)[8]) == 0)
        return 0;
    return GROUP(func_00338410(k)[9]);
}

/* 0x0033C610, 0x90 bytes. The cell its stance aims at. */
int func_0033C610(u8 **g, u8 *out)
{
    int c;

    if (g == 0 || out == 0)
        return 0;
    c = func_0033C4E0(g);
    if (c == 0) {
        u8 **h = func_0033C560(g);

        if (h == 0)
            return 0;
        *(u16 *)out = *(u16 *)func_0033B730(h);
        return 1;
    }
    func_0034ED90(c, out);
    return 1;
}

/* 0x0033C6A0, 0x1D4 bytes. Whether group `g`'s order follows from its stance (stance 4 -> order
 * 6, 3 -> 4, 2 -> 3, 1 -> 2, 0 -> 1, with the same target). */
int func_0033C6A0(u8 **g)
{
    u32 k = GI(g);
    char s = func_00338410(k)[8];
    char want;

    if (s == 4)
        return func_00338410(k)[2] == 6;
    if (s == 3)
        want = 4;
    else if (s == 2)
        want = 3;
    else if (s == 1)
        want = 2;
    else if (s == 0)
        want = 1;
    else
        return 1;
    if (func_00338410(k)[2] != want)
        return 0;
    return func_00338410(k)[3] == func_00338410(k)[9];
}

/* 0x0033C880, 0x1A0 bytes. Counts side `side`'s officer groups in play with order `order` (any
 * past 6) on target `target` (0xFF: any). */
int func_0033C880(u32 order, u32 target, u32 side)
{
    int n = 0;
    u32 k;

    if (side >= 2)
        return 0;
    for (k = 0; k < 0x10; k++) {
        u8 **g = func_0033EF80(k);

        if (g != 0 && (GFLAGS(g) & 1) != 0 && ALIVE(UNIT_FLAGS(LEADER(g)))
            && side == LEADER(g)[0x79]
            && (order > 6 || order == INFO(g)[2])
            && (target == 0xFF || target == INFO(g)[3]))
            n++;
    }
    return n;
}

/* 0x0033CA20, 0x34 bytes, matching. */
int func_0033CA20(u8 **g, u32 side)
{
    return func_0033C880(1, func_0034ED40(g), side);
}

/* 0x0033CA60, 0x34 bytes, matching. */
int func_0033CA60(u8 **g, u32 side)
{
    return func_0033C880(3, func_0034ED40(g), side);
}

/* 0x0033CAA0, 0x48 bytes, matching. How many of side `side`'s groups go after group `g`. */
int func_0033CAA0(u8 **g, u32 side)
{
    return func_0033C880(4, GI(g), side);
}

/* 0x0033CAF0, 0x28 bytes, matching. */
int func_0033CAF0(u8 **g, u8 **h)
{
    return func_0035D560(LEADER(g)[0x79], LEADER(h)[0x79]);
}

/* 0x0033CB20, 0x38 bytes, matching. */
int func_0033CB20(u8 **g, int c)
{
    u8 s = LEADER(g)[0x79];

    return func_0035D560(s, func_0034EDB0(c));
}

/* 0x0033CB60, 0x5C bytes. Whether group `g` stands on place `c`. */
int func_0033CB60(u8 **g, int c)
{
    short pos[2];

    if (g == 0 || c == 0)
        return 0;
    func_0034ED90(c, (u8 *)pos);
    return pos[0] == *(short *)func_0033B730(g);
}

/* 0x0033CBC0, 0x5C bytes. Whether the place group `g` stands on belongs to `v`. */
int func_0033CBC0(u8 **g, int v)
{
    int c;

    if (g == 0)
        return 0;
    c = func_0034ECA0(func_0033B730(g));
    if (c == 0)
        return 0;
    return v == func_0034EDB0(c);
}

/* 0x0033CC20, 0x54 bytes. Whether groups `g` and `h` stand on the same cell. */
int func_0033CC20(u8 **g, u8 **h)
{
    short a;

    if (g == 0 || h == 0)
        return 0;
    a = *(short *)func_0033B730(g);
    return a == *(short *)func_0033B730(h);
}

/* 0x0033CC80, 0x98 bytes. Whether group `g` stands with player `p`'s group. */
int func_0033CC80(u8 **g, u32 p)
{
    if (g == 0 || (GFLAGS(g) & 1) == 0 || (int)p < 0 || (int)p > 1)
        return 0;
    if (*(int *)(g_00669D60 + 0xA0 + p * 0x48) == 0)
        return 0;
    return func_0033CC20(g, func_0035DD10(p));
}

/* 0x0033CD20, 0x6C bytes. Whether group `g` stands on unit `u`'s cell. */
int func_0033CD20(u8 **g, u8 *u)
{
    if (g == 0 || (GFLAGS(g) & 1) == 0 || u == 0 || (UNIT_FLAGS(u) & 1) == 0)
        return 0;
    return *(short *)func_0033B730(g) == *(short *)(u + 0x40);
}

/* 0x0033CD90, 0x104 bytes. Whether a friendly officer group in play shares group `g`'s cell. */
int func_0033CD90(u8 **g)
{
    u32 k;

    if (g == 0 || (GFLAGS(g) & 1) == 0)
        return 0;
    for (k = 0; k < 0x10; k++) {
        u8 **h = func_0033EF80(k);

        if ((GFLAGS(h) & 1) != 0 && ALIVE(UNIT_FLAGS(LEADER(h)))
            && LEADER(h)[0x79] == LEADER(g)[0x79] && func_0033CC20(h, g) != 0)
            return 1;
    }
    return 0;
}

/* 0x0033CEA0, 0x30 bytes, matching. */
int func_0033CEA0(u8 **g, u8 a)
{
    return func_00353920(func_0033B730(g), a);
}

/* 0x0033CED0, 0x17C bytes. Whether a unit of the enemy's two main groups stands on group `g`'s
 * cell. */
int func_0033CED0(u8 **g)
{
    u8 s;
    u32 j, k;

    if (g == 0 || (GFLAGS(g) & 1) == 0)
        return 0;
    s = func_0035D5A0(LEADER(g)[0x79]);
    for (j = 0; j < 2; j++) {
        u8 **h = func_0033F070(s, j);

        if ((GFLAGS(h) & 1) == 0 || !ALIVE(UNIT_FLAGS(LEADER(h))))
            continue;
        for (k = 0; k < 0xD; k++) {
            u8 *u = h[k];

            if (u != 0 && ACTIVE(UNIT_FLAGS(u)) && func_0033CD20(g, u) != 0)
                return 1;
        }
    }
    return 0;
}
