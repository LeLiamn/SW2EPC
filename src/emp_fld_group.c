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
int func_0034ED40(int c);
int func_0035D560(u8 a, u8 b);
u8 func_0034EDB0(int c);
int func_0034ECA0(u8 *pos);
u8 **func_0035DD10(int p);
int func_00353920(u8 *pos, u8 a);
u8 **func_0033F070(u32 s, u32 j);

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
int func_0033CA20(int c, u32 side)
{
    return func_0033C880(1, func_0034ED40(c), side);
}

/* 0x0033CA60, 0x34 bytes, matching. */
int func_0033CA60(int c, u32 side)
{
    return func_0033C880(3, func_0034ED40(c), side);
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

/* Group moves, losses and lookups (parts of 0x0033D050-0x0033F428). */

extern u8 g_00415270[5][4];
extern int (*g_00415290[6])(u8 **g);     /* the musou-level choosers */
extern int g_004152B0[5];

int func_0018F6F0(u8 *a, u8 *b, int c);
void func_0018C3F0(u8 *a, u8 *b);
int func_00352610(u8 *pos, u32 v);
void func_00352650(u8 *pos, int a, u32 v);
void func_0035CA90(u32 h, u32 k);
void func_0035CAC0(u32 h, u32 k);
void func_0034BB20(u8 **g);
void func_003F7D20(u32 k);
void func_0034BAE0(u8 **g);
void func_003F7D00(u32 k);
void func_0033EDC0(u8 **g);
void func_0033DAB0(u8 **g);
void func_001F1910(u8 *u);
void func_001F1A30(u8 *u);
void func_001F1640(u8 *pos, u8 *cell);
void func_001D4C20(u8 **g, int a);
void func_001D5120(u8 **g, u8 side);
void func_0033E1E0(u8 *u);
void func_0033E470(void);
int func_003489E0(u8 side, int a);
void func_00349DF0(u8 **g, int a, int b, int c);
int func_0036D5A0(int s);
void func_0034A020(u8 *u, int v);

/* 0x0033D050, 0x5C bytes. The route length between groups `g` and `h`. */
short func_0033D050(u8 **g, u8 **h)
{
    if (g == 0 || h == 0)
        return 0;
    return func_0018F6F0(func_0033B730(g), func_0033B730(h), 0);
}

/* 0x0033D0B0, 0x9C bytes. */
void func_0033D0B0(u8 **g)
{
    int p;

    for (p = 0; p < 2; p++) {
        if (*(int *)(g_00669D60 + 0xA0 + p * 0x48) != 0) {
            u8 **h = func_0035DD10(p);

            func_0018C3F0(func_0033B700(g), func_0033B700(h));
        }
    }
}

/* 0x0033D150, 0xE0 bytes. The player whose group shares group `g`'s cell (one of them at random
 * when both do; 2 for none). */
int func_0033D150(u8 **g)
{
    int p, best = 2;

    for (p = 0; p < 2; p++) {
        if (*(int *)(g_00669D60 + 0xA0 + p * 0x48) != 0
            && func_0033CC20(g, func_0035DD10(p)) != 0
            && (best < 0 || best > 1 || (int)RANDOM() % 100 < 0x32))
            best = p;
    }
    return best;
}

/* 0x0033D230, 0x3C bytes, matching. */
int func_0033D230(u8 **g)
{
    return func_00352610(func_0033B730(g), func_0033BFE0(g));
}

/* 0x0033D270, 0x4C bytes, matching. */
void func_0033D270(u8 **g, int a)
{
    func_00352650(func_0033B730(g), a, func_0033BFE0(g));
}

/* 0x0033D2C0, 0x11C bytes. Whether group `g` (its side holding its own base) should stay back:
 * it stands on the enemy's front, or is weak (under 31% life). */
int func_0033D2C0(u8 **g)
{
    u8 side = LEADER(g)[0x79], e;
    u8 pos[4];

    if (func_0034EDB0(func_0034EC80(func_0035F200(side))) != side)
        return 0;
    e = func_0035D5A0(LEADER(g)[0x79]);
    if (func_0033CEA0(g, e) != 0) {
        if (LEADER(g)[0x79] != 0)
            return 1;
        if (func_0033C610(g, pos) == 0)
            return 1;
        if (func_00353920(pos, e) == 0)
            return 1;
    }
    if (*(short *)(INFO(g) + 0x1A) == 0)
        return 0;
    return (u32)func_0033B7B0(g) < 0x1F;
}

/* 0x0033D440, 0x90 bytes. Starts group `g`'s reinforcement delay (when its side has some and it
 * has soldiers). */
void func_0033D440(u8 **g)
{
    u32 k;

    if (func_0035F340(LEADER(g)[0x79]) == 0)
        return;
    k = GI(g);
    if (*(short *)(func_00338410(k) + 0x1A) != 0)
        func_00338410(k)[0x22] = func_00339D30(g);
}

/* 0x0033D4D0, 0x124 bytes. The group of the unit that beat group `g`'s leader (its side's main
 * group when not an officer group; 0x47 for none). */
int func_0033D4D0(u8 **g)
{
    u8 *l = LEADER(g);
    u8 **h = 0;

    if (l == 0 || (UNIT_FLAGS(l) & 1) == 0)
        return 0x47;
    if (*(u16 *)(l + 0x4A) != 0x1AD) {
        u8 *r = g_00693970 + *(u16 *)(l + 0x4A) * 0x88;

        if (r == 0 || (*(u32 *)(r + 0x80) & 1) == 0)
            return 0x47;
        h = func_0034A740(r);
        if (h == 0 || (GFLAGS(h) & 1) == 0)
            return 0x47;
    }
    /* (h is read even when 0: the original does so too) */
    if (h == 0 || func_0033B050(h) == 0)
        h = func_0033F110(LEADER(h)[0x79]);
    if (h == 0 || (GFLAGS(h) & 1) == 0)
        return 0x47;
    return GI(h);
}

/* 0x0033D600, 0x88 bytes, matching. Group `g` is routed: its soldiers lost, the winner noted. */
void func_0033D600(u8 **g)
{
    u32 k = GI(g);

    func_00338500(g, -*(u16 *)(func_00338410(k) + 0x1A));
    GSTRENGTH(g) = 1;
    func_00338410(k)[0x25] = func_0033D4D0(g);
}

/* 0x0033D690, 0xC0 bytes. Whether group `g` is routed when its leader falls (no soldiers, far
 * behind its front or tactic 0x15; never the slots 6 and 7). */
int func_0033D690(u8 **g)
{
    if (g == 0)
        return 0;
    if (func_0033B690(g) != 0)
        return 0;
    if (*(short *)(INFO(g) + 0x1A) == 0)
        return 1;
    if (func_00353A10(LEADER(g)) < -0x32)
        return 1;
    return func_0036F520(func_0035D5A0(LEADER(g)[0x79]), 0x15) != 0;
}

/* 0x0033D750, 0x1D0 bytes. Group `g`'s leader has fallen: the group's orders reset; then it
 * waits for reinforcements or is routed (the winner's group told). */
void func_0033D750(u8 **g)
{
    u8 *l = LEADER(g);
    u32 k;
    char c;
    u8 *r = 0;
    u8 **h = 0;

    GFLAGS(g) = 0;
    GFLAGS(g) = 1;
    if (func_0033B050(g) == 0)
        return;
    k = GI(g);
    c = func_00338410(k)[0x24];
    if (c != -1)
        func_00338410(k)[0x24] = c + 1;
    func_003386D0(g, 6, 0xFF);
    func_003387C0(g, 0xC, 0xFF);
    if (*(u16 *)(l + 0x4A) != 0x1AD)
        r = g_00693970 + *(u16 *)(l + 0x4A) * 0x88;
    if (r != 0)
        h = func_0034A740(r);
    if (func_0033D690(g) == 0) {
        func_0033D440(g);
        if (r != 0)
            func_0035CA90(GI(h), k);
    } else {
        func_0033D600(g);
        if (r != 0)
            func_0035CAC0(GI(h), k);
    }
    if (h != 0)
        func_00338C80(h, g);
    func_0034BB20(g);
    func_003F7D20(k);
}

/* 0x0033D920, 0xDC bytes. Takes unit `u` out of its group (`count`: its loss counts; `fall`:
 * a fallen leader ends the group's leadership). */
void func_0033D920(u8 *u, int count, int fall)
{
    u8 **g;
    u32 k;

    if (*(int *)(u + 0x10) == 0x47)
        return;
    g = GROUP(*(int *)(u + 0x10));
    if (count != 0)
        func_0033E1E0(u);
    if (u == LEADER(g)) {
        if (fall != 0)
            func_0033D750(g);
    } else {
        for (k = 0; k < 0xD; k++) {
            if (g[k] == u) {
                g[k] = 0;
                break;
            }
        }
    }
    *(int *)(u + 0x10) = 0x47;
}

/* 0x0033DA00, 0xAC bytes. Group `g` (re)enters: its side's army strength, its musou level. */
void func_0033DA00(u8 **g)
{
    GSTRENGTH(g) = clamp1000(func_0035F190(LEADER(g)[0x79]));
    func_0033EDC0(g);
    func_0034BAE0(g);
    func_003F7D00(GI(g));
}

/* 0x0033DCA0, 0x118 bytes. Places group `g`'s leader in the middle of cell `pos` (5000 units a
 * cell). */
void func_0033DCA0(u8 **g, u8 *pos)
{
    u8 *l = LEADER(g);
    float x, z;

    func_0033DAB0(g);
    func_001F1910(l);
    x = (float)pos[0] * 5000.0f + 2500.0f;
    z = (float)pos[1] * 5000.0f + 2500.0f;
    *(float *)(l + 0x28) = x;
    *(float *)(l + 0x2C) = z;
    *(float *)(l + 0x30) = x;
    *(float *)(l + 0x34) = z;
    *(u16 *)(l + 0x40) = *(u16 *)pos;
    l[0x46] = (int)x / 1000;
    l[0x47] = (int)z / 1000;
    *(int *)(l + 0x20) = 0;
    func_001F1A30(l);
    func_0033DA00(g);
}

/* 0x0033DDC0, 0x148 bytes. Places all group `g`'s units on cell `pos` (at a free spot each). */
void func_0033DDC0(u8 **g, u8 *pos)
{
    u32 k;

    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u != 0) {
            u8 c[2];
            float x, z;

            func_001F1640(pos, c);
            x = (float)c[0] * 1000.0f + 500.0f;
            z = (float)c[1] * 1000.0f + 500.0f;
            *(float *)(u + 0x28) = x;
            *(float *)(u + 0x2C) = z;
            *(float *)(u + 0x30) = x;
            *(float *)(u + 0x34) = z;
            *(u16 *)(u + 0x40) = *(u16 *)pos;
            u[0x46] = c[0];
            u[0x47] = c[1];
            *(int *)(u + 0x20) = 0;
        }
    }
    func_001D4C20(g, 0);
    if (func_0033B050(g) != 0)
        func_0035F280(LEADER(g)[0x79], *(u16 *)(INFO(g) + 0x1A));
    func_0033DA00(g);
}

/* 0x0033DF10, 0x164 bytes. Group `g` changes to side `side` (its soldiers move to that side's
 * count; its counters cleared). */
void func_0033DF10(u8 **g, u32 side)
{
    u8 old;
    u32 k;

    if (g == 0 || (GFLAGS(g) & 1) == 0 || side >= 2 || (UNIT_FLAGS(LEADER(g)) & 0x30) != 0
        || func_0033B050(g) == 0)
        return;
    old = LEADER(g)[0x79];
    func_001D5120(g, side);
    if (side == old)
        return;
    {
        u16 s = *(u16 *)(INFO(g) + 0x1A);

        func_0035F280(old, -s);
        func_0035F280(side, s);
    }
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u != 0 && (UNIT_FLAGS(u) & 1) != 0)
            *(int *)(u + 0x60) = 0;
    }
    func_00338DB0(g);
    func_00338E20(g);
    INFO(g)[0x19] = 0;
}

/* 0x0033E080, 0x154 bytes. Shares a loss of `total` soldiers among side `side`'s officer groups
 * in play; how much of it they could not take. */
int func_0033E080(u32 side, int total)
{
    int list[16], left = total;
    u32 n = 0, k;

    for (k = 0; k < 0x10; k++) {
        u8 **g = func_0033EF80(k);

        if ((GFLAGS(g) & 1) != 0 && func_0033B0B0(g) != 0 && side == LEADER(g)[0x79])
            list[n++] = GI(g);
    }
    if (n == 0)
        return total - left;
    for (k = 0; k < n; k++)
        left += func_00338500(GROUP(list[k]), -(total / (int)n));
    return total - left;
}

/* 0x0033E1E0, 0xAC bytes. Counts unit `u`'s fall once: its group (else its side's groups) loses
 * the soldiers it led. */
void func_0033E1E0(u8 *u)
{
    u8 side;
    int n;
    u8 **g;

    if ((UNIT_FLAGS(u) & 0x20000000) != 0)
        return;
    side = u[0x79];
    n = func_0034A5B0(u);
    g = func_0034A740(u);
    if (g != 0 && func_0033B0B0(g) != 0) {
        n += func_00338500(g, -n);
        if (n > 0)
            func_0033E080(side, n);
    }
    UNIT_FLAGS(u) |= 0x20000000;
}

/* 0x0033E290, 0x168 bytes. Player `p`'s musou costs his group up to `d` soldiers (by the life he
 * misses; halved by tactic 0xC; side 0 shares the rest). */
void func_0033E290(int p, int d)
{
    u8 **g = func_0035DD10(p);
    int v = *(short *)(OFFICER(p) + 0x80) - *(short *)(OFFICER(p) + 0x82);

    if (d < v)
        v = d;
    v = v * ((int)RANDOM() % 10 + 100) / 100 * 2;
    if (func_0036F390(LEADER(g)[0x79], 0xC) != 0)
        v /= 2;
    if (*(short *)(INFO(g) + 0x1A) != 0) {
        v += func_00338500(g, -v);
        if (v > 0)
            func_0033E080(0, v);
    }
}

/* 0x0033E400, 0x60 bytes, matching. */
int func_0033E400(u8 **g, int a, int b)
{
    func_00349DF0(g, a, func_003489E0(LEADER(g)[0x79], 0), b);
    return 1;
}

/* 0x0033E460, 8 bytes, matching. */
int func_0033E460(void)
{
    return 0x32;
}

/* 0x0033E820, 0x2C bytes, matching. */
void func_0033E820(void)
{
    if (func_0036D310() == 0)
        func_0033E470();
}

/* 0x0033E850, 0x114 bytes. Groups `g` and `h` swap their stances. */
void func_0033E850(u8 **g, u8 **h)
{
    u8 s, a, hs, ha;

    if (g == 0 || (GFLAGS(g) & 1) == 0 || h == 0 || (GFLAGS(h) & 1) == 0)
        return;
    s = INFO(g)[8];
    a = INFO(g)[9];
    ha = INFO(h)[9];
    hs = INFO(h)[8];
    func_003385E0(g, hs, ha);
    func_003385E0(h, s, a);
}

/* 0x0033E970, 0x110 bytes. A level 1-4 from the two func_0036D5A0 counts. */
int func_0033E970(void)
{
    int a = func_0036D5A0(0), b = func_0036D5A0(1);
    u32 n = 1 < b;

    if (b > 2)
        n++;
    if (b > 3)
        n++;
    if (b > 4)
        n += 2;
    if (b > 5)
        n += 2;
    if (b > 6)
        n += 2;
    if (a > 4)
        n++;
    if (a > 9)
        n++;
    if (a > 0xE)
        n++;
    if (a > 0x13)
        n++;
    if (n < 2)
        return 1;
    if (n < 4)
        return 2;
    if (n < 9)
        return 3;
    return 4;
}

/* 0x0033EA80, 0x8C bytes. */
int func_0033EA80(u8 **g)
{
    if (func_00362570() == 2 || func_00362570() == 3) {
        if (LEADER(g)[0x79] == 1)
            return func_0033B140(g) == 0 ? 0 : func_0033E970();
        return 0;
    }
    return 0;
}

/* 0x0033EB10, 0x3C bytes. */
int func_0033EB10(u8 **g)
{
    if (LEADER(g)[0x79] == 1)
        return func_0033B140(g) != 0;
    return 0;
}

/* 0x0033EB50, 0x8C bytes. */
int func_0033EB50(u8 **g)
{
    if ((u32)func_00362570() < 6 || (u32)func_00362570() > 0xF)
        return 0;
    if (LEADER(g)[0x79] == 1)
        return func_0033B140(g) == 0 ? 0 : func_0033E970();
    return 0;
}

/* 0x0033EBF0, 0xD0 bytes. By the difficulty, for the second side's lead group. */
int func_0033EBF0(u8 **g)
{
    int t[5];

    t[0] = *(int *)g_00415270[0];
    t[1] = *(int *)g_00415270[1];
    t[2] = *(int *)g_00415270[2];
    t[3] = *(int *)g_00415270[3];
    t[4] = *(int *)g_00415270[4];
    if (GI(g) == func_0035F840()) {
        if (LEADER(g)[0x79] == 1)
            return t[g_00669D60[0x21]];
        return 0;
    }
    return 0;
}

/* 0x0033ECC0, 0x50 bytes. */
int func_0033ECC0(u8 **g)
{
    if (func_0036D310() == 0)
        return 0;
    return func_0033B140(g) == 0 ? 0 : 3;
}

/* 0x0033ED10, 0xA8 bytes. Level `v` kept within the difficulty's bounds. */
int func_0033ED10(int v)
{
    char d = g_00669D60[0x21];

    if (d == 0) {
        if (v > 2)
            v = 2;
    } else if (d == 1) {
        if (v > 3)
            v = 3;
    } else if (d == 3) {
        if (v < 3)
            v = 2;
    } else if (d == 4 && v < 4) {
        v = 3;
    }
    return v;
}

/* 0x0033EDC0, 0x144 bytes. Sets group `g`'s leader's level: the best of the six choosers, kept
 * within the difficulty's bounds. */
void func_0033EDC0(u8 **g)
{
    int (*fn[6])(u8 **);
    int val[5];
    int best = 0;
    u32 k;

    for (k = 0; k < 6; k++)
        fn[k] = g_00415290[k];
    for (k = 0; k < 5; k++)
        val[k] = g_004152B0[k];
    if ((UNIT_FLAGS(LEADER(g)) & 0x30) != 0)
        return;
    for (k = 0; k < 6; k++) {
        int v = fn[k](g);

        if (v >= 0 && best < v)
            best = v;
    }
    if (best < 1)
        func_0034A020(LEADER(g), 0);
    else
        func_0034A020(LEADER(g), val[func_0033ED10(best)]);
}

/* 0x0033EF10, 8 bytes, matching. The officer groups by index: groups 0-15. */
u32 func_0033EF10(u32 k)
{
    return k;
}

/* 0x0033EF20, 0x18 bytes. Side `s`'s group `k` of the first kind: groups 0x10 + s * 0x14. */
int func_0033EF20(int s, int k)
{
    return k + s * 0x14 + 0x10;
}

/* 0x0033EF40, 0xC bytes, matching. */
int func_0033EF40(int s, int k)
{
    return s + 0x3A + k;
}

/* 0x0033EF50, 0x10 bytes. Side `s`'s main groups (two each): groups 0x3C-0x3F. */
int func_0033EF50(int s, int k)
{
    return k + s * 2 + 0x3C;
}

/* 0x0033EF60, 0x14 bytes. Side `s`'s groups 0x40 + s * 3. */
int func_0033EF60(int s, int k)
{
    return k + s * 3 + 0x40;
}

/* 0x0033EF80, 0x44 bytes. */
u8 **func_0033EF80(u32 k)
{
    return GROUP(func_0033EF10(k));
}

/* 0x0033EFD0, 0x44 bytes. */
u8 **func_0033EFD0(int s, int k)
{
    return GROUP(func_0033EF20(s, k));
}

/* 0x0033F020, 0x44 bytes. */
u8 **func_0033F020(int s, int k)
{
    return GROUP(func_0033EF40(s, k));
}

/* 0x0033F070, 0x44 bytes. */
u8 **func_0033F070(u32 s, u32 k)
{
    return GROUP(func_0033EF50(s, k));
}

/* 0x0033F0C0, 0x44 bytes. */
u8 **func_0033F0C0(int s, int k)
{
    return GROUP(func_0033EF60(s, k));
}

/* 0x0033F110, 0x88 bytes. Side `side`'s commander group (leader flag 0x200; 0 for none). */
u8 **func_0033F110(u8 side)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 **g = func_0033EF80(k);

        if (g != 0 && (GFLAGS(g) & 1) != 0 && (UNIT_FLAGS(LEADER(g)) & 0x200) != 0
            && side == LEADER(g)[0x79])
            return g;
    }
    return 0;
}

/* 0x0033F1A0, 0x74 bytes. The group of actor `a`'s battle officer (0 for none). */
u8 **func_0033F1A0(u8 *a)
{
    u8 *o;

    if (a == 0)
        return 0;
    o = OFFICER(*(short *)(a + 0x178));
    if (o == 0 || *(u8 **)(o + 0x10) == 0)
        return 0;
    return func_0034A740(*(u8 **)(o + 0x10));
}

/* 0x0033F350, 0xD8 bytes. Whether group `g` is an officer group of side `side` (any past 1;
 * `alive`: its leader must be up). */
int func_0033F350(u8 **g, u32 side, u32 alive)
{
    if (alive != 0 && !ALIVE(UNIT_FLAGS(LEADER(g))))
        return 0;
    if (func_0033B050(g) == 0)
        return 0;
    if (side < 2 && side != LEADER(g)[0x79])
        return 0;
    return 1;
}

/* Group lists, place choices and the AI's battle requests (0x0033F220-0x00341F9C). The 20
 * places are func_0034EC80(0-19) (cells, bases). */

typedef int (*GroupTest)(u8 **g, u32 a, u32 b);

extern int (*g_0045D038[2])(u8 **g);     /* (small data) place choosers, first kind */
extern int (*g_0045D040[2])(u8 **g);     /* second kind */
extern int (*g_0045D048[2])(u8 **g);     /* third kind */
extern void (*g_004152D0[4])(u8 **g);    /* request makers by officer temper */

void func_00347820(u32 x, u32 k);
void func_00347860(u32 x, u32 k);
int func_0034EE50(int c);
int func_0034EE60(int c);
int func_0034EE80(int c);
int func_003522F0(int c, u8 side);
int func_00352780(int c, u8 e);
int func_0035F2D0(u8 side);
int func_003521B0(int c, u8 e);
u32 func_0034EEF0(int c);
u32 func_0034EF50(int c, u32 j);
u32 func_00352B00(int c, int home);
int func_003539D0(u8 *pos, u8 side);
int func_003DCE70(u8 **g, int c);
u32 func_003DCE30(u8 **g, u8 **h);
u32 func_003DCDF0(u8 **g, u8 *pos);
void func_0036FBE0(int kind, u32 k, u32 h);
int func_0036FC90(void);
u32 func_0036FD70(u8 side);

/* 0x0033F240, 0x10C bytes. Lists the groups `from`-`to` in use that pass `fn` (none: all) into
 * `out`, `max` at most; their count. */
u32 func_0033F240(u32 *out, u32 max, GroupTest fn, u32 a, u32 b, u32 from, u32 to)
{
    u32 n = 0;

    for (; from < to; from++) {
        u8 **g = GROUP(from);

        if (n >= max)
            return n;
        if ((GFLAGS(g) & 1) != 0 && (fn == 0 || fn(g, a, b) != 0)) {
            *out++ = from;
            n++;
        }
    }
    return n;
}

/* 0x0033F220, 0x20 bytes, matching. The same over all 0x47 groups. */
u32 func_0033F220(u32 *out, u32 max, GroupTest fn, u32 a, u32 b)
{
    return func_0033F240(out, max, fn, a, b, 0, 0x47);
}

/* 0x0033F430, 0x34 bytes, matching. Lists side `side`'s officer groups. */
u32 func_0033F430(u32 side, u32 alive, u32 *out, u32 max)
{
    return func_0033F220(out, max, func_0033F350, side, alive);
}

/* 0x0033F470, 0x60 bytes. Whether group `g` is a live officer group of side `side` on place
 * `i`. */
int func_0033F470(u8 **g, u32 i, u32 side)
{
    if (func_0033F350(g, side, 1) == 0)
        return 0;
    return func_0033CB60(g, func_0034EC80(i));
}

/* 0x0033F4D0, 0x58 bytes, matching. Lists side `side`'s live officer groups on place `c`. */
u32 func_0033F4D0(int c, u32 side, u32 *out, u32 max)
{
    return func_0033F220(out, max, (GroupTest)func_0033F470, func_0034ED40(c), side);
}

/* 0x0033F530, 0x44 bytes. */
int func_0033F530(u8 **g, u32 x)
{
    func_00347820(x, GI(g));
    return 0;
}

/* 0x0033F580, 0x30 bytes, matching. */
u32 func_0033F580(u32 x, u32 *out, u32 max)
{
    return func_0033F220(out, max, (GroupTest)func_0033F530, x, 0);
}

/* 0x0033F5B0, 0x44 bytes. */
int func_0033F5B0(u8 **g, u32 x)
{
    func_00347860(x, GI(g));
    return 0;
}

/* 0x0033F600, 0x30 bytes, matching. */
u32 func_0033F600(u32 x, u32 *out, u32 max)
{
    return func_0033F220(out, max, (GroupTest)func_0033F5B0, x, 0);
}

/* 0x0033F630, 0x154 bytes. Whether group `g` is a live officer group of side `side` with order
 * `ot` (low half; high half its target, 0xFF: any). */
int func_0033F630(u8 **g, u32 ot, u32 side)
{
    if (!ALIVE(UNIT_FLAGS(LEADER(g))))
        return 0;
    if (func_0033B050(g) == 0)
        return 0;
    if (side != LEADER(g)[0x79])
        return 0;
    if ((ot & 0xFFFF) != INFO(g)[2])
        return 0;
    return (ot >> 0x10) == 0xFF || (ot >> 0x10) == INFO(g)[3];
}

/* 0x0033F790, 0x3C bytes, matching. Lists side `side`'s groups with order `order` on `target`. */
u32 func_0033F790(u32 order, u32 target, u32 side, u32 *out, u32 max)
{
    return func_0033F220(out, max, func_0033F630, order | target << 0x10, side);
}

/* 0x0033F7D0, 0x20 bytes, matching. Counts side `side`'s officer groups. */
u32 func_0033F7D0(u32 side, u32 alive)
{
    u32 list[16];

    return func_0033F430(side, alive, list, 0x10);
}

/* 0x0033F7F0, 0x20 bytes, matching. Counts side `side`'s groups on place `c`. */
u32 func_0033F7F0(int c, u32 side)
{
    u32 list[16];

    return func_0033F4D0(c, side, list, 0x10);
}

/* 0x0033F810, 0x20 bytes, matching. */
u32 func_0033F810(u32 order, u32 target, u32 side)
{
    u32 list[16];

    return func_0033F790(order, target, side, list, 0x10);
}

/* 0x0033F830, 0x24 bytes, matching. Whether any group has that order. */
int func_0033F830(u32 order, u32 target, u32 side)
{
    u32 one;

    return func_0033F790(order, target, side, &one, 1) != 0;
}

/* 0x0033F860, 0x16C bytes. One of side `side`'s officer groups at random (`plain`: only those
 * with a plain leader). */
u8 **func_0033F860(u32 side, u32 alive, int plain)
{
    u32 list[16], n = func_0033F430(side, alive, list, 0x10), k;
    u8 **r;

    if (n == 0)
        return 0;
    if (plain == 0)
        return GROUP(list[(int)RANDOM() % (int)n]);
    r = 0;
    for (k = 0; k < n; k++) {
        u8 **h = GROUP(list[k]);

        if ((UNIT_FLAGS(LEADER(h)) & 0x30) == 0) {
            if (r != 0 && (int)RANDOM() % 100 > 0x31)
                continue;
            r = h;
        }
    }
    return r;
}

/* 0x0033F9D0, 8 bytes, matching. */
int func_0033F9D0(u8 **g)
{
    return g != 0;
}

/* 0x0033F9E0, 0x88 bytes. Whether place `i` is a place group `g`'s side does not hold. */
int func_0033F9E0(u8 **g, u32 i)
{
    int c;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0034EE50(c) == 0)
        return 0;
    return func_0033CB20(g, c) == 0;
}

/* 0x0033FA70, 0x124 bytes. Whether group `i` is a live enemy officer group of group `g`. */
int func_0033FA70(u8 **g, u32 i)
{
    u8 **h;

    if (g == 0 || i > 0x46)
        return 0;
    h = GROUP(i);
    if (h == 0 || (GFLAGS(h) & 1) == 0 || !ALIVE(UNIT_FLAGS(LEADER(h))))
        return 0;
    if (func_0033B050(h) == 0)
        return 0;
    return func_0033CAF0(g, h) == 0;
}

/* 0x0033FBA0, 0x84 bytes. Whether place `i` is held by group `g`'s side. */
int func_0033FBA0(u8 **g, u32 i)
{
    int c;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0034EE50(c) == 0)
        return 0;
    return func_0033CB20(g, c) != 0;
}

/* 0x0033FC30, 0x130 bytes. Whether group `i` is another live friendly officer group. */
int func_0033FC30(u8 **g, u32 i)
{
    u8 **h;

    if (g == 0 || i > 0x46)
        return 0;
    h = GROUP(i);
    if (h == 0 || (GFLAGS(h) & 1) == 0 || !ALIVE(UNIT_FLAGS(LEADER(h))))
        return 0;
    if (func_0033B050(h) == 0 || g == h)
        return 0;
    return func_0033CAF0(g, h) != 0;
}

/* 0x0033FD60, 0xBC bytes. */
int func_0033FD60(u8 **g, u32 i)
{
    int c;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0034EE50(c) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    if (func_0034EE80(c) != 0)
        return 0;
    return func_003522F0(c, LEADER(g)[0x79]) != 0;
}

/* 0x0033FE20, 0x130 bytes. */
int func_0033FE20(u8 **g, u32 i)
{
    int c;
    u8 side;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0)
        return 0;
    side = LEADER(g)[0x79];
    if (*(short *)(INFO(g) + 0x1A) == 0)
        return 0;
    if (func_0034EE50(c) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    if (func_0034EE80(c) != 0)
        return 0;
    if (func_0034EE60(c) == 0 && func_00352780(c, func_0035D5A0(side)) != 0)
        return 0;
    return 1;
}

/* 0x0033FF50, 0xBC bytes. */
int func_0033FF50(u8 **g, u32 i)
{
    int c;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0035F2D0(LEADER(g)[0x79]) == 0)
        return 0;
    if (func_0034EE50(c) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    return func_0034EE80(c) == 0;
}

/* 0x00340010, 0x98 bytes. An enemy place group `g` may attack. */
int func_00340010(u8 **g, u32 i)
{
    int c;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0033F9E0(g, i) == 0)
        return 0;
    return func_00352240(c, LEADER(g)[0x79]) != 0;
}

/* 0x003400B0, 0xF8 bytes. A friendly place group `g` may defend (the enemy near it or about to
 * come). */
int func_003400B0(u8 **g, u32 i)
{
    int c;
    u8 e;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0033FBA0(g, i) == 0)
        return 0;
    if (func_0034EE80(c) != 0)
        return 0;
    e = func_0035D5A0(func_0034EDB0(c));
    if (func_00352690(c, e) != 0)
        return 1;
    if (func_0033CA20(c, e) != 0)
        return 1;
    return func_003521B0(c, e) != 0;
}

/* 0x003401B0, 0x38 bytes. */
int func_003401B0(u8 **g, u32 i)
{
    if (g == 0 || i > 0x13)
        return 0;
    return func_0033FD60(g, i) != 0;
}

/* 0x003401F0, 0x38 bytes. */
int func_003401F0(u8 **g, u32 i)
{
    if (g == 0 || i > 0x13)
        return 0;
    return func_0033FE20(g, i) != 0;
}

/* 0x00340230, 0x38 bytes. */
int func_00340230(u8 **g, u32 i)
{
    if (g == 0 || i > 0x13)
        return 0;
    return func_0033FF50(g, i) != 0;
}

/* 0x00340270, 0xE8 bytes. An enemy place group `g` may attack while its side holds its own main
 * base (else only that base). */
int func_00340270(u8 **g, u32 i)
{
    int c;
    u8 side;
    u32 b;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0)
        return 0;
    side = LEADER(g)[0x79];
    if (func_0033F9E0(g, i) == 0)
        return 0;
    b = func_0035F200(side);
    if (side == func_0034EDB0(func_0034EC80(b))) {
        if (func_00352240(c, side) == 0)
            return 0;
    } else if (i != b) {
        return 0;
    }
    return 1;
}

/* 0x00340360, 0x38 bytes. */
int func_00340360(u8 **g, u32 i)
{
    if (g == 0 || i > 0x46)
        return 0;
    return func_0033FA70(g, i) != 0;
}

/* 0x003403A0, 0x1A4 bytes. A friendly place group `g` should stay at (or come back to). */
int func_003403A0(u8 **g, u32 i)
{
    int c;
    u8 e;

    if (g == 0 || i > 0x13)
        return 0;
    c = func_0034EC80(i);
    if (c == 0 || func_0033FBA0(g, i) == 0)
        return 0;
    if (func_0033B150(g) != 0 && func_0034EE60(c) != 0)
        return 1;
    if (func_0034EE80(c) != 0)
        return 0;
    e = func_0035D5A0(func_0034EDB0(c));
    if (func_00352690(c, e) != 0 || func_0033CA20(c, e) != 0)
        return 1;
    if (func_003521B0(c, e) == 0)
        return 0;
    if (INFO(g)[4] < 0x3C)
        return 1;
    return (int)RANDOM() % 100 < 0x5A;
}

/* 0x00340550, 0x38 bytes. */
int func_00340550(u8 **g, u32 i)
{
    if (g == 0 || i > 0x46)
        return 0;
    return func_0033FC30(g, i) != 0;
}

/* 0x00340590, 0x180 bytes. A place for group `g` to attack (a main one half the time, else any
 * at random). */
int func_00340590(u8 **g)
{
    u32 list[20], n = 0, main = 0x14, i;

    if (g == 0)
        return 0;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50(c) != 0 && func_00340010(g, i) != 0) {
            list[n++] = i;
            if (func_0034EE60(c) != 0)
                main = i;
        }
    }
    if (n == 0)
        return 0;
    if (main == 0x14 || (int)RANDOM() % 100 > 0x31)
        return func_0034EC80(list[(int)RANDOM() % (int)n]);
    return func_0034EC80(main);
}

/* 0x00340710, 0x148 bytes. The place group `g` attacks next: its current one, else the
 * neighbour nearest the enemy's main base. */
int func_00340710(u8 **g)
{
    int c, best, home;
    u32 min, n, j;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    if (func_00340010(g, func_0034ED40(c)) != 0)
        return c;
    best = 0;
    min = 0xFFFFFFFF;
    home = func_0034EC80(func_0035F200(func_0035D5A0(LEADER(g)[0x79])));
    n = func_0034EEF0(c);
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50(c, j);
        int cc = func_0034EC80(i);

        if (func_00340010(g, i) != 0) {
            u32 d = func_00352B00(cc, home);

            if (d < min) {
                min = d;
                best = cc;
            }
        }
    }
    return best;
}

/* Runs choosers `fn` until one gives a place. */
static int first_choice(u8 **g, int (**tab)(u8 **))
{
    int (*fn[2])(u8 **);
    u32 k;

    fn[0] = tab[0];
    fn[1] = tab[1];
    if (g == 0)
        return 0;
    for (k = 0; k < 2; k++) {
        int r;

        if (fn[k] != 0 && (r = fn[k](g)) != 0)
            return r;
    }
    return 0;
}

/* 0x00340860, 0x8C bytes. */
int func_00340860(u8 **g)
{
    return first_choice(g, g_0045D038);
}

/* 0x003408F0, 8 bytes, matching. */
int func_003408F0(void)
{
    return 0;
}

/* 0x00340900, 0x1A0 bytes. A place for group `g` to defend (where fewer than 2 groups go). */
int func_00340900(u8 **g)
{
    u32 list[20], n = 0, main = 0x14, i;

    if (g == 0)
        return 0;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50(c) != 0 && func_003400B0(g, i) != 0
            && (u32)func_0033CA60(c, LEADER(g)[0x79]) < 2) {
            list[n++] = i;
            if (func_0034EE60(c) != 0)
                main = i;
        }
    }
    if (n == 0)
        return 0;
    if (main == 0x14 || (int)RANDOM() % 100 > 0x31)
        return func_0034EC80(list[(int)RANDOM() % (int)n]);
    return func_0034EC80(main);
}

/* 0x00340AA0, 0x148 bytes. The place group `g` defends next. */
int func_00340AA0(u8 **g)
{
    int c, best, home;
    u32 min, n, j;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    if (func_003400B0(g, func_0034ED40(c)) != 0)
        return c;
    best = 0;
    min = 0xFFFFFFFF;
    home = func_0034EC80(func_0035F200(func_0035D5A0(LEADER(g)[0x79])));
    n = func_0034EEF0(c);
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50(c, j);
        int cc = func_0034EC80(i);

        if (func_003400B0(g, i) != 0) {
            u32 d = func_00352B00(cc, home);

            if (d < min) {
                min = d;
                best = cc;
            }
        }
    }
    return best;
}

/* 0x00340BF0, 0x8C bytes. */
int func_00340BF0(u8 **g)
{
    return first_choice(g, g_0045D040);
}

/* 0x00340C80, 8 bytes, matching. */
int func_00340C80(void)
{
    return 0;
}

/* 0x00340C90, 0x104 bytes. A friendly place at random for group `g` (func_003401B0). */
int func_00340C90(u8 **g)
{
    u32 list[20], n = 0, i;

    if (g == 0)
        return 0;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (c != 0 && func_0034EE50(c) != 0 && func_003401B0(g, i) != 0)
            list[n++] = i;
    }
    if (n == 0)
        return 0;
    return func_0034EC80(list[(int)RANDOM() % (int)n]);
}

/* 0x00340DA0, 0x158 bytes. The same next to the place group `g` is going to. */
int func_00340DA0(u8 **g)
{
    int c, r;
    u32 n, j;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    if (func_0033CB60(g, c) == 0 && func_003401B0(g, func_0034ED40(c)) != 0)
        return c;
    r = 0;
    n = func_0034EEF0(c);
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50(c, j);
        int cc = func_0034EC80(i);

        if (func_003401B0(g, i) != 0) {
            if (r != 0 && (int)RANDOM() % 100 > 0x31)
                continue;
            r = cc;
        }
    }
    return r;
}

/* 0x00340F00, 0x8C bytes. */
int func_00340F00(u8 **g)
{
    return first_choice(g, g_0045D048);
}

/* 0x00340F90, 0x130 bytes. Where group `g` falls back to: its side's main base for the second
 * side's commander, else the nearest fitting friendly place. */
int func_00340F90(u8 **g)
{
    u8 *pos, p[4];
    int best;
    u32 min, i;

    if (g == 0)
        return 0;
    if (func_0033B150(g) != 0) {
        int c = func_0034EC80(func_0035F200(LEADER(g)[0x79]));

        if (func_0034EDB0(c) == LEADER(g)[0x79])
            return c;
    }
    pos = func_0033B730(g);
    best = 0;
    min = 0xFFF;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50(c) != 0 && func_003401F0(g, i) != 0) {
            u32 d;

            func_0034ED90(c, p);
            d = func_0018F6F0(pos, p, 0);
            if (d < min) {
                best = c;
                min = d;
            }
        }
    }
    return best;
}

/* 0x003410C0, 0x1A4 bytes. The friendly place best placed between group `g` and place `t`
 * (near both, a little at random). */
int func_003410C0(u8 **g, int t)
{
    u8 *pos, tp[4], p[4];
    int best = 0;
    u32 top = 0, i;

    if (g == 0 || t == 0)
        return 0;
    pos = func_0033B730(g);
    func_0034ED90(t, tp);
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (c != 0 && func_00340230(g, i) != 0) {
            int a, b;
            u32 s;

            func_0034ED90(c, p);
            a = 5 - (func_0018F6F0(p, tp, 0) & 0xFFFF);
            b = 5 - (func_0018F6F0(p, pos, 0) & 0xFFFF);
            s = a * 5 * 0x14 + b * 5 * 2 + (int)RANDOM() % 10;
            if (top < s) {
                best = c;
                top = s;
            }
        }
    }
    return best;
}

/* 0x00341270, 0x190 bytes. The friendly place group `g` should guard: its side's main base for
 * a commander, else the one most threatened and nearest. */
int func_00341270(u8 **g)
{
    u8 side, p[4];
    int best = 0, top = 0;
    u32 i;

    if (g == 0)
        return 0;
    side = LEADER(g)[0x79];
    if (func_0033B140(g) != 0) {
        int c = func_0034EC80(func_0035F200(side));

        if (c != 0 && side == func_0034EDB0(c))
            return c;
    }
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50(c) != 0 && side == func_0034EDB0(c)) {
            int v, d, s;

            func_0034ED90(c, p);
            v = func_003539D0(p, side);
            if (v < 1)
                v = 0;
            d = 5 - func_003DCE70(g, c);
            if (d < 1)
                d = 0;
            s = v * 5 * 2 + d;
            if (top < s) {
                best = c;
                top = s;
            }
        }
    }
    if (best == 0)
        best = func_0034EC80(func_0035F200(side));
    return best;
}

/* 0x00341400, 0xE4 bytes. Whether group `g` may make a battle request (+0x23 set, +0x2B bit 7
 * clear, its second order not 6-9 or 0xC). */
int func_00341400(u8 **g)
{
    u32 k;
    char o;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[0x23] == 0)
        return 0;
    if ((func_00338410(k)[0x2B] & 0x80) != 0)
        return 0;
    o = func_00338410(k)[5];
    if (o == 0xC || o == 9 || o == 8 || o == 7 || o == 6)
        return 0;
    return 1;
}

/* 0x003414F0, 0x18C bytes. Request 0 (once, +0x2B bit 0): reached its place or near the group it
 * goes after. */
int func_003414F0(u8 **g)
{
    u32 k;
    u8 *r;

    if (g == 0)
        return 0;
    k = GI(g);
    if ((func_00338410(k)[0x2B] & 1) != 0 || func_00341400(g) == 0)
        return 0;
    if ((int)RANDOM() % 100 >= 0x3C)
        return 0;
    r = func_00338410(k);
    if (r[2] == 2) {
        if (func_003DCE30(g, func_0033C3A0(g)) > 1)
            return 0;
    } else {
        if (r[2] != 1)
            return 0;
        if (func_0033CB60(g, func_0033C320(g)) == 0)
            return 0;
    }
    if (LEADER(g)[0x7A] != 2)
        return 0;
    func_0036FBE0(0, k, 0xFF);
    return 1;
}

/* 0x00341680, 0x1DC bytes. Request 1 (+0x2B bit 1): the same for orders 3-5. */
int func_00341680(u8 **g)
{
    u32 k;
    char o;

    if (g == 0)
        return 0;
    k = GI(g);
    if ((func_00338410(k)[0x2B] & 2) != 0 || func_00341400(g) == 0)
        return 0;
    if ((int)RANDOM() % 100 >= 0x3C)
        return 0;
    o = func_00338410(k)[2];
    if (o == 5) {
        if (func_00338410(k)[5] != 5)
            return 0;
        if (func_0033CB60(g, func_0033C160(g)) == 0)
            return 0;
    } else if (o == 4) {
        if (func_003DCE30(g, func_0033C3A0(g)) > 1)
            return 0;
    } else {
        if (o != 3)
            return 0;
        if (func_0033CB60(g, func_0033C320(g)) == 0)
            return 0;
    }
    if (LEADER(g)[0x7A] != 2)
        return 0;
    func_0036FBE0(1, k, 0xFF);
    return 1;
}

/* 0x00341860, 0x1C0 bytes. Request 2 (+0x2B bit 2): still 3 and more from where it goes. */
int func_00341860(u8 **g)
{
    u32 k;
    char o;
    u8 pos[4];

    if (g == 0)
        return 0;
    k = GI(g);
    if ((func_00338410(k)[0x2B] & 4) != 0 || func_00341400(g) == 0)
        return 0;
    if ((int)RANDOM() % 100 >= 0x3C)
        return 0;
    o = func_00338410(k)[2];
    if (o == 5) {
        if (func_00338410(k)[5] != 5)
            return 0;
        if (func_0033C290(g, pos) == 0)
            return 0;
    } else {
        if (o != 4 && o != 2 && o != 3 && o != 1)
            return 0;
        if (func_0033C450(g, pos) == 0)
            return 0;
    }
    if (func_003DCDF0(g, pos) < 3)
        return 0;
    func_0036FBE0(2, k, 0xFF);
    return 1;
}

/* 0x00341A20, 0x1AC bytes. Lists the live enemy officer groups that hold a place of their own
 * without a link (`max` at most). */
u32 func_00341A20(u8 **g, u8 ***out, u32 max)
{
    u32 n = 0, k;
    char side;

    if (g == 0 || out == 0)
        return 0;
    side = LEADER(g)[0x79];
    for (k = 0; k < 0x10 && n < max; k++) {
        u8 **h = func_0033EF80(k);
        u32 f;

        if ((GFLAGS(h) & 1) == 0)
            continue;
        f = UNIT_FLAGS(LEADER(h));
        if (!ALIVE(f) || (f & 0x30) != 0 || side == (char)LEADER(h)[0x79])
            continue;
        if (INFO(h)[0x2A] > 0x46 && INFO(h)[5] == 1
            && func_0033CB60(h, func_0033C160(h)) != 0) {
            *out++ = h;
            n++;
        }
    }
    return n;
}

/* 0x00341BD0, 0x1C8 bytes. Request 3 (+0x2B bit 3): a group of 3 and more asks to go after one
 * of those enemy groups. */
int func_00341BD0(u8 **g)
{
    u8 **list[16];
    u32 k, n, i;

    if (g == 0)
        return 0;
    k = GI(g);
    if ((func_00338410(k)[0x2B] & 8) != 0 || func_00341400(g) == 0)
        return 0;
    for (i = n = 0; i < 0xD; i++) {
        if (g[i] != 0)
            n++;
    }
    if (n < 3)
        return 0;
    if ((int)RANDOM() % 100 >= 0x3C)
        return 0;
    n = func_00341A20(g, list, 0x10);
    if (n == 0)
        return 0;
    func_0036FBE0(3, k, GI(list[(int)RANDOM() % (int)n]));
    return 1;
}

/* 0x00341DA0, 0xB8 bytes. Makes group `g`'s request by its officer's temper (at random for
 * func_0033B440). */
void func_00341DA0(u8 **g)
{
    void (*fn[4])(u8 **);
    u32 v;

    fn[0] = g_004152D0[0];
    fn[1] = g_004152D0[1];
    fn[2] = g_004152D0[2];
    fn[3] = g_004152D0[3];
    if (g == 0)
        return;
    if (func_0033B440(g) == 0)
        v = func_0033B8D0(g);
    else
        v = RANDOM() & 3;
    if (v < 4)
        fn[v](g);
}

/* 0x00341E60, 0x128 bytes. Now and then (more often as the battle goes on and the more it lost
 * its leader), group `g` makes a request. */
void func_00341E60(u8 **g)
{
    int t;
    u8 b;

    if (g == 0 || (UNIT_FLAGS(LEADER(g)) & 0x30) != 0)
        return;
    if (INFO(g)[0x28] != 0 || func_0036FC90() != 0)
        return;
    t = g_00669F9C;
    b = INFO(g)[0x24];
    if ((u32)(0xB4 - (t / 500 + b * 0x32)) <= func_0036FD70(LEADER(g)[0x79]))
        func_00341DA0(g);
}
