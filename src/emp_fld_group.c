/*
 * emp_fld_group.c - the Empire battles' groups: the 0x47 soldier groups (0x68 bytes at
 * 0x006A1D58; word 0 their leader unit, word 0x19 flags) and the 16 officers' group records
 * (0x30 bytes at 0x007B5F70; a default one at 0x007B5F40). Original file name unknown (it lies
 * between emp_ev_predata.c and emp_FldBase.c). Covers 0x00338410-0x00347F1C (some functions still missing).
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

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_00353920   /* the original callers here see it this way */
int func_00353920(unsigned char *, unsigned char);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_0035D560   /* the original callers here see it this way */
int func_0035D560(unsigned char, unsigned char);
#define SW2E_OWN_PROTO_func_0034EDB0   /* the same: a byte result */
unsigned char func_0034EDB0(unsigned char *);
#endif
#define SW2E_FILE_EMP_FLD_GROUP_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

int func_0033C6A0(u8 **g);
int func_0033B050(u8 **g);
int func_0033B320(u8 **g);
u8 **func_0033EF80(u32 k);

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
    func_0034BA00((unsigned char *)(g), old);
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

    func_00118AC0((unsigned int *)(p + 0x56E), (unsigned char *)(g_007B5F70), 0x300);
    for (k = 0; k < 0x10; k++, p += 0x30) {
        u8 **g = func_0033EF80(k);

        if ((((u32 *)g)[0x19] & 1) != 0 && (UNIT_FLAGS(LEADER(g)) & 0x20000) != 0)
            *(u16 *)(p + 0x58E) = *(u16 *)(g_006A3A30[*(int *)(LEADER(g) + 0x14)] + 0x88);
    }
}

/* 0x00338F50, 0x30 bytes, matching. Loads them. */
void func_00338F50(void)
{
    func_00118AC0((unsigned int *)(g_007B5F70), (unsigned char *)PS2_PTR(func_002EFB00(9) + 0x56E), 0x300);
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
int func_0033CC80(u8 **g, u32 k);
void func_0033DCA0(u8 **g, u8 *pos);
int func_0033CEA0(u8 **g, u8 a);
u16 func_0034A470(void);
void func_0033D920(u8 *u, int a, int b);
void func_001EE3B0(u8 *u);

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

        if (func_00352690((unsigned char *)PS2_PTR(c), a) != 0 && func_00352240((unsigned char *)PS2_PTR(c), a) != 0) {
            func_00338410(k)[0x22] = func_00339D30(g);
            return;
        }
        func_0034ED90((unsigned char *)PS2_PTR(c), pos);
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
            && (h = (u8 **)(func_0034A740(*(u8 **)(l + 0x18)))) != 0
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

int func_0033B1E0(u8 **g);
int func_0033B690(u8 **g);
extern u8 g_00669D60[];
u8 **func_0033F110(u8 side);
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
u32 func_0033B740(u8 **g)
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
    return func_0033BB00(g, h, (int (*)(u16,  u16))(func_002F77A0));
}

/* 0x0033BBF0, 0x20 bytes, matching. */
int func_0033BBF0(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, (int (*)(u16,  u16))(func_002F77F0));
}

/* 0x0033BC10, 0x20 bytes, matching. */
int func_0033BC10(u8 **g, u8 **h)
{
    return func_0033BB00(g, h, (int (*)(u16,  u16))(func_0036D850));
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
u32 func_0033BFD0(u8 **g)
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
    func_0034ED90((unsigned char *)PS2_PTR(c), out);
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
    func_0034ED90((unsigned char *)PS2_PTR(c), out);
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
    func_0034ED90((unsigned char *)PS2_PTR(c), out);
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
    return func_0033C880(1, func_0034ED40((unsigned char *)PS2_PTR(c)), side);
}

/* 0x0033CA60, 0x34 bytes, matching. */
int func_0033CA60(int c, u32 side)
{
    return func_0033C880(3, func_0034ED40((unsigned char *)PS2_PTR(c)), side);
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

    return func_0035D560(s, func_0034EDB0((unsigned char *)PS2_PTR(c)));
}

/* 0x0033CB60, 0x5C bytes. Whether group `g` stands on place `c`. */
int func_0033CB60(u8 **g, int c)
{
    short pos[2];

    if (g == 0 || c == 0)
        return 0;
    func_0034ED90((unsigned char *)PS2_PTR(c), (u8 *)pos);
    return pos[0] == *(short *)func_0033B730(g);
}

/* 0x0033CBC0, 0x5C bytes. Whether the place group `g` stands on belongs to `v`. */
int func_0033CBC0(u8 **g, int v)
{
    int c;

    if (g == 0)
        return 0;
    c = PS2_ADDR(func_0034ECA0(func_0033B730(g)));
    if (c == 0)
        return 0;
    return v == func_0034EDB0((unsigned char *)PS2_PTR(c));
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

void func_0033EDC0(u8 **g);
void func_0033DAB0(u8 **g);
void func_0033E1E0(u8 *u);
void func_0033E470(void);
void func_00349DF0(u8 **g, int a, int b, int c);

/* 0x0033D050, 0x5C bytes. The route length between groups `g` and `h`. */
short func_0033D050(u8 **g, u8 **h)
{
    if (g == 0 || h == 0)
        return 0;
    return func_0018F6F0((short unsigned int *)(func_0033B730(g)), (short unsigned int *)(func_0033B730(h)), 0);
}

/* 0x0033D0B0, 0x9C bytes, matching. */
u8 **func_0033D0B0(u8 **g)
{
    int p;
    u8 **h;                     /* undefined when no player is set, as in the original */

    for (p = 0; p < 2; p++) {
        if (*(int *)(g_00669D60 + 0xA0 + p * 0x48) != 0) {
            h = func_0035DD10(p);
            func_0018C3F0((float *)(func_0033B700(g)), (float *)(func_0033B700(g)));   /* g twice in the original */
        }
    }
    return h;
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
    return PS2_ADDR(func_00352610((short int *)(func_0033B730(g)), func_0033BFE0(g)));
}

/* 0x0033D270, 0x4C bytes, matching. */
u8 *func_0033D270(u8 **g, int a)
{
    return func_00352650((short int *)(func_0033B730(g)), a, func_0033BFE0(g));
}

/* 0x0033D2C0, 0x11C bytes. Whether group `g` (its side holding its own base) should stay back:
 * it stands on the enemy's front, or is weak (under 31% life). */
int func_0033D2C0(u8 **g)
{
    u8 side = LEADER(g)[0x79], e;
    u8 pos[4];

    if (func_0034EDB0((unsigned char *)PS2_PTR(func_0034EC80(func_0035F200(side)))) != side)
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
        h = (u8 **)(func_0034A740(r));
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
        h = (u8 **)(func_0034A740(r));
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
    func_0034BAE0((unsigned char *)(g));
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

            func_001F1640(pos, (short int *)(c));
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
    g = (u8 **)(func_0034A740(u));
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
    func_00349DF0(g, a, func_003489E0((unsigned char *)PS2_PTR(LEADER(g)[0x79]), 0), b);
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
    return (u8 **)func_0034A740(*(u8 **)(o + 0x10));
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

int func_00347820(u8 **g, u32 i);
int func_00347860(u8 **g, u32 i);
void func_0036FBE0(int kind, u32 k, u32 h);
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
    return func_0033F220(out, max, (GroupTest)func_0033F470, func_0034ED40((unsigned char *)PS2_PTR(c)), side);
}

/* 0x0033F530, 0x44 bytes, matching. */
int func_0033F530(u8 **g, u32 x)
{
    return func_00347820((u8 **)x, GI(g));
}

/* 0x0033F580, 0x30 bytes, matching. */
u32 func_0033F580(u32 x, u32 *out, u32 max)
{
    return func_0033F220(out, max, (GroupTest)func_0033F530, x, 0);
}

/* 0x0033F5B0, 0x44 bytes, matching. */
int func_0033F5B0(u8 **g, u32 x)
{
    return func_00347860((u8 **)x, GI(g));
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
    if (c == 0 || func_0034EE50((unsigned char *)PS2_PTR(c)) == 0)
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
    if (c == 0 || func_0034EE50((unsigned char *)PS2_PTR(c)) == 0)
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
    if (c == 0 || func_0034EE50((unsigned char *)PS2_PTR(c)) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    if (func_0034EE80((unsigned char *)PS2_PTR(c)) != 0)
        return 0;
    return func_003522F0((unsigned char *)PS2_PTR(c), LEADER(g)[0x79]) != 0;
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
    if (func_0034EE50((unsigned char *)PS2_PTR(c)) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    if (func_0034EE80((unsigned char *)PS2_PTR(c)) != 0)
        return 0;
    if (func_0034EE60((unsigned char *)PS2_PTR(c)) == 0 && func_00352780((unsigned char *)PS2_PTR(c), func_0035D5A0(side)) != 0)
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
    if (func_0034EE50((unsigned char *)PS2_PTR(c)) == 0 || func_0033CB20(g, c) == 0)
        return 0;
    return func_0034EE80((unsigned char *)PS2_PTR(c)) == 0;
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
    return func_00352240((unsigned char *)PS2_PTR(c), LEADER(g)[0x79]) != 0;
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
    if (func_0034EE80((unsigned char *)PS2_PTR(c)) != 0)
        return 0;
    e = func_0035D5A0(func_0034EDB0((unsigned char *)PS2_PTR(c)));
    if (func_00352690((unsigned char *)PS2_PTR(c), e) != 0)
        return 1;
    if (func_0033CA20(c, e) != 0)
        return 1;
    return func_003521B0((unsigned char *)PS2_PTR(c), e) != 0;
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
    if (side == func_0034EDB0((unsigned char *)PS2_PTR(func_0034EC80(b)))) {
        if (func_00352240((unsigned char *)PS2_PTR(c), side) == 0)
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
    if (func_0033B150(g) != 0 && func_0034EE60((unsigned char *)PS2_PTR(c)) != 0)
        return 1;
    if (func_0034EE80((unsigned char *)PS2_PTR(c)) != 0)
        return 0;
    e = func_0035D5A0(func_0034EDB0((unsigned char *)PS2_PTR(c)));
    if (func_00352690((unsigned char *)PS2_PTR(c), e) != 0 || func_0033CA20(c, e) != 0)
        return 1;
    if (func_003521B0((unsigned char *)PS2_PTR(c), e) == 0)
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

        if (func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && func_00340010(g, i) != 0) {
            list[n++] = i;
            if (func_0034EE60((unsigned char *)PS2_PTR(c)) != 0)
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
    if (func_00340010(g, func_0034ED40((unsigned char *)PS2_PTR(c))) != 0)
        return c;
    best = 0;
    min = 0xFFFFFFFF;
    home = func_0034EC80(func_0035F200(func_0035D5A0(LEADER(g)[0x79])));
    n = func_0034EEF0((unsigned char *)PS2_PTR(c));
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50((unsigned char *)PS2_PTR(c), j);
        int cc = func_0034EC80(i);

        if (func_00340010(g, i) != 0) {
            u32 d = func_00352B00((unsigned char *)PS2_PTR(cc), home);

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

        if (func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && func_003400B0(g, i) != 0
            && (u32)func_0033CA60(c, LEADER(g)[0x79]) < 2) {
            list[n++] = i;
            if (func_0034EE60((unsigned char *)PS2_PTR(c)) != 0)
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
    if (func_003400B0(g, func_0034ED40((unsigned char *)PS2_PTR(c))) != 0)
        return c;
    best = 0;
    min = 0xFFFFFFFF;
    home = func_0034EC80(func_0035F200(func_0035D5A0(LEADER(g)[0x79])));
    n = func_0034EEF0((unsigned char *)PS2_PTR(c));
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50((unsigned char *)PS2_PTR(c), j);
        int cc = func_0034EC80(i);

        if (func_003400B0(g, i) != 0) {
            u32 d = func_00352B00((unsigned char *)PS2_PTR(cc), home);

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

        if (c != 0 && func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && func_003401B0(g, i) != 0)
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
    if (func_0033CB60(g, c) == 0 && func_003401B0(g, func_0034ED40((unsigned char *)PS2_PTR(c))) != 0)
        return c;
    r = 0;
    n = func_0034EEF0((unsigned char *)PS2_PTR(c));
    for (j = 0; j < n; j++) {
        u32 i = func_0034EF50((unsigned char *)PS2_PTR(c), j);
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

        if (func_0034EDB0((unsigned char *)PS2_PTR(c)) == LEADER(g)[0x79])
            return c;
    }
    pos = func_0033B730(g);
    best = 0;
    min = 0xFFF;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && func_003401F0(g, i) != 0) {
            u32 d;

            func_0034ED90((unsigned char *)PS2_PTR(c), p);
            d = func_0018F6F0((short unsigned int *)(pos), (short unsigned int *)(p), 0);
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
    func_0034ED90((unsigned char *)PS2_PTR(t), tp);
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (c != 0 && func_00340230(g, i) != 0) {
            int a, b;
            u32 s;

            func_0034ED90((unsigned char *)PS2_PTR(c), p);
            a = 5 - (func_0018F6F0((short unsigned int *)(p), (short unsigned int *)(tp), 0) & 0xFFFF);
            b = 5 - (func_0018F6F0((short unsigned int *)(p), (short unsigned int *)(pos), 0) & 0xFFFF);
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

        if (c != 0 && side == func_0034EDB0((unsigned char *)PS2_PTR(c)))
            return c;
    }
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && side == func_0034EDB0((unsigned char *)PS2_PTR(c))) {
            int v, d, s;

            func_0034ED90((unsigned char *)PS2_PTR(c), p);
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

/* The AI's order choices for the officer groups (parts of 0x00341FA0-0x00344050). Orders: 0
 * none, 1 attack place, 2 chase group, 3 defend place, 4 go after group, 5 roam, 6 idle. */

extern void (*g_0045D050)(u8 **g);       /* (small data) */
extern int (*g_004152E0[5])(u8 **g);     /* stance keepers by stance */
extern int (*g_00415300[7])(u8 **g);     /* order choosers */
extern int (*g_00415320[5])(u8 **g);     /* idle-group choosers */
extern int (*g_00415340[7])(u8 **g);     /* order changers */

/* 0x00341FA0, 0x70 bytes. */
void func_00341FA0(u8 **g)
{
    if (g != 0 && g_0045D050 != 0)
        g_0045D050(g);
}

/* 0x00342010, 0x6C bytes, matching. Whether the place of group `g`'s stance is an enemy one. */
int func_00342010(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033F9E0(g, INFO(g)[9]) != 0;
}

/* 0x00342080, 0x6C bytes, matching. Whether the group of its stance is an enemy. */
int func_00342080(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FA70(g, INFO(g)[9]) != 0;
}

/* 0x003420F0, 0x6C bytes, matching. Whether the place of its stance is a friendly one. */
int func_003420F0(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FBA0(g, INFO(g)[9]) != 0;
}

/* 0x00342160, 0x6C bytes, matching. Whether the group of its stance is a friend. */
int func_00342160(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FC30(g, INFO(g)[9]) != 0;
}

/* 0x003421E0, 0xD0 bytes. Drops group `g`'s stance (to 4) when it no longer holds. */
void func_003421E0(u8 **g)
{
    int (*fn[5])(u8 **);
    u8 s;

    fn[0] = g_004152E0[0];
    fn[1] = g_004152E0[1];
    fn[2] = g_004152E0[2];
    fn[3] = g_004152E0[3];
    fn[4] = g_004152E0[4];
    if (g == 0)
        return;
    s = INFO(g)[8];
    if (s < 5 && fn[s] != 0 && fn[s](g) == 0)
        func_003385E0(g, 4, 0xFF);
}

/* 0x003422B0, 0x38 bytes, matching. */
void func_003422B0(u8 **g)
{
    if (g != 0) {
        func_00341FA0(g);
        func_003421E0(g);
    }
}

/* 0x003422F0, 0x58 bytes, matching. Officer leaders without flag 0x40 get no order. */
int func_003422F0(u8 **g)
{
    u32 f;

    if (g == 0)
        return 0;
    f = UNIT_FLAGS(LEADER(g));
    if ((f & 0x30) == 0 || (f & 0x40) != 0)
        return 0;
    func_003386D0(g, 0, 0xFF);
    return 1;
}

/* 0x00342350, 0xF0 bytes. The second side's lead group chases the player its side's record
 * names. */
int func_00342350(u8 **g)
{
    u8 side;
    int p;

    if (g == 0 || GI(g) != func_0035F840())
        return 0;
    side = LEADER(g)[0x79];
    if (side == 0)
        return 0;
    p = func_0034B720(g_006AA5F4[side]);
    if (p < 0 || p > 1)
        return 0;
    func_003386D0(g, 2, func_0035DCB0(p));
    return 1;
}

/* 0x00342440, 0x11C bytes. The order that follows from group `g`'s stance. */
int func_00342440(u8 **g)
{
    u32 k;
    char s;

    if (g == 0)
        return 0;
    k = GI(g);
    s = func_00338410(k)[8];
    if (s == 3) {
        func_003386D0(g, 4, func_00338410(k)[9]);
        return 1;
    }
    if (s == 2) {
        func_003386D0(g, 3, func_00338410(k)[9]);
        return 1;
    }
    if (s == 1) {
        func_003386D0(g, 2, func_00338410(k)[9]);
        return 1;
    }
    if (s == 0) {
        func_003386D0(g, 1, func_00338410(k)[9]);
        return 1;
    }
    return 0;
}

/* 0x00342560, 0x118 bytes. The order its side's plan asks for (2: after a group, 1: defend,
 * 0: attack). */
int func_00342560(u8 **g)
{
    u8 *r;
    char c;

    if (g == 0)
        return 0;
    r = func_0033B860(g);
    c = r[0];
    if (c == 2) {
        u8 **h = (u8 **)(func_0034B680(r));

        if (h != 0) {
            func_003386D0(g, 4, GI(h));
            return 1;
        }
    } else if (c == 1) {
        int p = func_00340BF0(g);

        if (p != 0) {
            func_003386D0(g, 3, func_0034ED40((unsigned char *)PS2_PTR(p)));
            return 1;
        }
    } else {
        int p;

        if (c != 0)
            return 0;
        p = func_00340860(g);
        if (p != 0) {
            func_003386D0(g, 1, func_0034ED40((unsigned char *)PS2_PTR(p)));
            return 1;
        }
    }
    return 0;
}

/* 0x00342680, 0x274 bytes. Officer leaders with flag 0x40 attack a first-side place under
 * threat (else chase a second-side group), picked at random. */
int func_00342680(u8 **g)
{
    u32 f, i;
    int best = 0;

    if (g == 0)
        return 0;
    f = UNIT_FLAGS(LEADER(g));
    if ((f & 0x30) == 0 || (f & 0x40) == 0)
        return 0;
    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50((unsigned char *)PS2_PTR(c)) != 0 && func_0034EDB0((unsigned char *)PS2_PTR(c)) != 0 && func_003521B0((unsigned char *)PS2_PTR(c), 0) != 0
            && (best == 0 || (int)RANDOM() % 100 < 0x32))
            best = c;
    }
    if (best == 0) {
        u8 **r = 0;

        for (i = 0; i < 0x10; i++) {
            u8 **h = func_0033EF80(i);

            if ((GFLAGS(h) & 1) != 0 && ALIVE(UNIT_FLAGS(LEADER(h))) && LEADER(h)[0x79] != 0
                && (r == 0 || (int)RANDOM() % 100 < 0x32))
                r = h;
        }
        if (r == 0)
            return 0;
        func_003386D0(g, 2, GI(r));
        return 1;
    }
    func_003386D0(g, 1, func_0034ED40((unsigned char *)PS2_PTR(best)));
    return 1;
}

/* 0x00342900, 0x9C bytes. The second side's commander defends its main base while its side
 * holds it. */
int func_00342900(u8 **g)
{
    u8 side;
    u32 b;

    if (g == 0 || func_0033B150(g) == 0)
        return 0;
    side = LEADER(g)[0x79];
    b = func_0035F200(side);
    if (side != func_0034EDB0((unsigned char *)PS2_PTR(func_0034EC80(b))))
        return 0;
    func_003386D0(g, 3, b);
    return 1;
}

/* 0x003429A0, 0x104 bytes. Defends its side's main base when the enemy threatens it (less often
 * the more groups already do). */
int func_003429A0(u8 **g)
{
    u8 side;
    u32 b;
    int c, n;

    if (g == 0)
        return 0;
    side = LEADER(g)[0x79];
    b = func_0035F200(side);
    c = func_0034EC80(b);
    if (func_00352240((unsigned char *)PS2_PTR(c), func_0035D5A0(side)) == 0)
        return 0;
    if (func_003400B0(g, b) == 0)
        return 0;
    n = func_0033CA60(c, side);
    if ((RANDOM() & 3) < n * n - 1u)
        return 0;
    func_003386D0(g, 3, b);
    return 1;
}

/* 0x00342AB0, 0x1B0 bytes. Defends a threatened friendly place near its own (2 away at most,
 * fewer than 2 groups there). */
int func_00342AB0(u8 **g)
{
    u32 list[20], n = 0, i;
    int c;
    u8 side, e;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    func_0034ED40((unsigned char *)PS2_PTR(c));
    side = LEADER(g)[0x79];
    e = func_0035D5A0(side);
    for (i = 0; i < 0x14; i++) {
        int cc = func_0034EC80(i);

        if (cc != 0 && func_0034EE50((unsigned char *)PS2_PTR(cc)) != 0 && func_003400B0(g, i) != 0
            && func_00352780((unsigned char *)PS2_PTR(cc), e) != 0 && func_00352930((unsigned char *)PS2_PTR(cc), (unsigned char *)PS2_PTR(c)) < 3
            && (u32)func_0033CA60(cc, side) < 2)
            list[n++] = i;
    }
    if (n == 0)
        return 0;
    func_003386D0(g, 3, list[(int)RANDOM() % (int)n]);
    return 1;
}

/* 0x00342C60, 0x11C bytes. Defends the friendly place it stands on when the two sides' groups
 * there are about even. */
int func_00342C60(u8 **g)
{
    int c, a, b, d;
    u32 i;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    i = func_0034ED40((unsigned char *)PS2_PTR(c));
    if (func_003400B0(g, i) == 0)
        return 0;
    a = func_0033CA60(c, LEADER(g)[0x79]);
    b = func_0033CA20(c, func_0035D5A0(LEADER(g)[0x79]));
    if (b == 0 || a >= 2)
        return 0;
    d = a - b;
    if (d >= 2 || d < -1)
        return 0;
    func_003386D0(g, 3, i);
    return 1;
}

/* 0x00342D80, 0x10C bytes. Attacks the enemy place it stands on when the groups there are
 * about even. */
int func_00342D80(u8 **g)
{
    int c, a, b, d;
    u32 i;

    if (g == 0)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    i = func_0034ED40((unsigned char *)PS2_PTR(c));
    if (func_00340010(g, i) == 0)
        return 0;
    a = func_0033CA20(c, LEADER(g)[0x79]);
    b = func_0033CA60(c, func_0035D5A0(LEADER(g)[0x79]));
    if (a >= 3)
        return 0;
    d = a - b;
    if (d >= 2 || d < -1)
        return 0;
    func_003386D0(g, 1, i);
    return 1;
}

/* 0x00342E90, 0xF4 bytes. Attacks (`att` in 100), defends (`def` in 100) or roams. */
int func_00342E90(u8 **g, u32 att, int def, int other)
{
    u32 r;

    if (g == 0)
        return 0;
    r = RANDOM() % 100;
    if (r < att) {
        int p = func_00340860(g);

        if (p != 0) {
            func_003386D0(g, 1, func_0034ED40((unsigned char *)PS2_PTR(p)));
            return 1;
        }
    } else if (r < att + def) {
        int p = func_00340BF0(g);

        if (p != 0) {
            func_003386D0(g, 3, func_0034ED40((unsigned char *)PS2_PTR(p)));
            return 1;
        }
    } else {
        func_003386D0(g, 5, 0xFF);
        return 1;
    }
    return 0;
}

/* 0x00342F90, 0x78 bytes, matching. The same with the odds of its side (func_0035F0C0's side attacks
 * more). */
int func_00342F90(u8 **g)
{
    if (g == 0)
        return 0;
    if (LEADER(g)[0x79] == func_0035F0C0())
        return func_00342E90(g, 0x3C, 0x1E, 10);
    return func_00342E90(g, 0x28, 0x28, 0x14);
}

/* 0x00343010, 0xD0 bytes. Gives group `g` an order (the first chooser that gives one). */
int func_00343010(u8 **g)
{
    int (*fn[7])(u8 **);
    u32 k;

    for (k = 0; k < 7; k++)
        fn[k] = g_00415300[k];
    if (g == 0)
        return 0;
    for (k = 0; k < 7; k++) {
        if (fn[k](g) != 0)
            return 1;
    }
    return 0;
}

/* 0x003430E0, 0xE0 bytes. An idle group's choosers. */
void func_003430E0(u8 **g)
{
    int (*fn[5])(u8 **);
    int k;

    for (k = 0; k < 5; k++)
        fn[k] = g_00415320[k];
    if (g == 0 || INFO(g)[2] != 6)
        return;
    for (k = 0; k < 5; k++) {
        if (fn[k] != 0 && fn[k](g) != 0)
            return;
    }
}

/* 0x003431C0, 0x194 bytes. A group without a stance defends its side's threatened main base. */
int func_003431C0(u8 **g)
{
    u8 side, e;
    u32 b, k;
    int c, n;

    if (g == 0)
        return 0;
    side = LEADER(g)[0x79];
    e = func_0035D5A0(side);
    b = func_0035F200(side);
    c = func_0034EC80(b);
    k = GI(g);
    if (func_00338410(k)[8] != 4)
        return 0;
    if (func_00338410(k)[2] == 3 && b == func_00338410(k)[3])
        return 0;
    if (func_00352240((unsigned char *)PS2_PTR(c), e) == 0)
        return 0;
    if (func_003400B0(g, b) == 0)
        return 0;
    n = func_0033CA60(c, side);
    if ((RANDOM() & 3) < n * n - 1u)
        return 0;
    func_003386D0(g, 3, b);
    return 1;
}

/* 0x00343910, 0x150 bytes. A second-side group sometimes (1 in 10) attacks the enemy place it
 * stands on. */
int func_00343910(u8 **g)
{
    int c;
    u32 i, k;

    if (g == 0 || LEADER(g)[0x79] == 0)
        return 0;
    c = PS2_ADDR(func_0034ECA0(func_0033B730(g)));
    if (c == 0)
        return 0;
    i = func_0034ED40((unsigned char *)PS2_PTR(c));
    k = GI(g);
    if (func_00338410(k)[2] == 1 && i == func_00338410(k)[3])
        return 0;
    if (func_00340010(g, i) == 0)
        return 0;
    if ((int)RANDOM() % 100 < 10) {
        func_003386D0(g, 1, i);
        return 1;
    }
    return 0;
}

/* 0x00343A60, 0x150 bytes. A second-side group sometimes (3 in 100) defends the friendly place
 * it stands on. */
int func_00343A60(u8 **g)
{
    int c;
    u32 i, k;

    if (g == 0 || LEADER(g)[0x79] == 0)
        return 0;
    c = PS2_ADDR(func_0034ECA0(func_0033B730(g)));
    if (c == 0)
        return 0;
    i = func_0034ED40((unsigned char *)PS2_PTR(c));
    k = GI(g);
    if (func_00338410(k)[2] == 3 && i == func_00338410(k)[3])
        return 0;
    if (func_003400B0(g, i) == 0)
        return 0;
    if ((int)RANDOM() % 100 < 3) {
        func_003386D0(g, 3, i);
        return 1;
    }
    return 0;
}

/* The odds of giving up an order by its age. */
static u32 give_up_odds(u8 age)
{
    return age < 0x3C ? 0 : age < 0x78 ? 10 : 0x1E;
}

/* 0x00343BB0, 0x130 bytes. A group chasing another (without the matching stance) gives up now
 * and then. */
int func_00343BB0(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[2] != 2 || func_00338410(k)[8] == 1)
        return 0;
    if (RANDOM() % 100 < give_up_odds(func_00338410(k)[4])) {
        func_003386D0(g, 6, 0xFF);
        return 1;
    }
    return 0;
}

/* 0x00343CE0, 0x1B4 bytes. A group going after another gives up now and then (surely when the
 * other is a strong officer's), unless its side's plan names that group. */
int func_00343CE0(u8 **g)
{
    u32 k, p;
    u8 *r;
    u8 **h;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[2] != 4)
        return 0;
    r = func_0033B860(g);
    if (r != 0 && r[0] == 2 && r[1] == func_00338410(k)[3])
        return 0;
    if (func_00338410(k)[8] == 3)
        return 0;
    p = give_up_odds(func_00338410(k)[4]);
    h = func_0033C3A0(g);
    if (h != 0 && (UNIT_FLAGS(LEADER(h)) & 0x30) != 0 && (u32)func_0033B7B0(h) > 0x32)
        p = 100;
    if (RANDOM() % 100 < p) {
        func_003386D0(g, 6, 0xFF);
        return 1;
    }
    return 0;
}

/* 0x00343EA0, 0xF0 bytes. Runs the order changers on group `g` (not the player's). */
void func_00343EA0(u8 **g)
{
    int (*fn[7])(u8 **);
    u32 f;
    int k;

    for (k = 0; k < 7; k++)
        fn[k] = g_00415340[k];
    if (g == 0)
        return;
    f = UNIT_FLAGS(LEADER(g));
    if (((f & 0x30) != 0 && (f & 0x40) == 0) || func_0033B580(g) != 0)
        return;
    for (k = 0; k < 7; k++) {
        if (fn[k] != 0 && fn[k](g) != 0)
            return;
    }
}

/* 0x00343FA0, 0xB4 bytes, matching. Whether group `g`'s attack order still holds. */
int func_00343FA0(u8 **g)
{
    u8 t;

    if (g == 0)
        return 0;
    t = INFO(g)[3];
    if (func_0033F9E0(g, t) == 0)
        return 0;
    if (func_0033C6A0(g) == 0 && func_00340270(g, t) == 0)
        return 0;
    return 1;
}

/* Order checks, second orders and their moves (parts of 0x00344060-0x003460AC). Second
 * orders: 1 attack place, 5 move, 6 fall back, 7 hold, 8 link, 9 guard, 10 fight in place,
 * 0xC none. */

extern int (*g_00415360[7])(u8 **g);     /* order keepers by order */
extern int (*g_00415380[8])(u8 **g);
extern int (*g_0045D054[1])(u8 **g);     /* (small data) */
extern int (*g_004153A0[7])(u8 **g);     /* second order choosers */
extern int (*g_004153C0[13])(u8 **g);    /* second order keepers */
extern int (*g_0045D058)(u8 **g);        /* (small data) */
extern void (*g_00415400[13])(u8 **g);   /* second order movers */
extern int g_00415438[3];

int func_0033D3E0(u8 **g);

/* 0x00344060, 0xB4 bytes, matching. Whether group `g`'s chase still holds. */
int func_00344060(u8 **g)
{
    u8 t;

    if (g == 0)
        return 0;
    t = INFO(g)[3];
    if (func_0033FA70(g, t) == 0)
        return 0;
    if (func_0033C6A0(g) == 0 && func_00340360(g, t) == 0)
        return 0;
    return 1;
}

/* 0x00344120, 0xB4 bytes, matching. Whether its defence still holds. */
int func_00344120(u8 **g)
{
    u8 t;

    if (g == 0)
        return 0;
    t = INFO(g)[3];
    if (func_0033FBA0(g, t) == 0)
        return 0;
    if (func_0033C6A0(g) == 0 && func_003403A0(g, t) == 0)
        return 0;
    return 1;
}

/* 0x003441E0, 0xB4 bytes, matching. Whether going after a friendly group still holds. */
int func_003441E0(u8 **g)
{
    u8 t;

    if (g == 0)
        return 0;
    t = INFO(g)[3];
    if (func_0033FC30(g, t) == 0)
        return 0;
    if (func_0033C6A0(g) == 0 && func_00340550(g, t) == 0)
        return 0;
    return 1;
}

/* 0x003442A0, 0x7C bytes. Whether roaming still holds (ends 1 time in 20 on its own side's
 * ground). */
int func_003442A0(u8 **g)
{
    if (g == 0)
        return 0;
    if (func_0033CBC0(g, LEADER(g)[0x79]) == 0 || (int)RANDOM() % 100 > 4)
        return 1;
    return 0;
}

/* 0x00344330, 0xDC bytes. Drops group `g`'s order (to idle) when it no longer holds. */
void func_00344330(u8 **g)
{
    int (*fn[7])(u8 **);
    int k;

    for (k = 0; k < 7; k++)
        fn[k] = g_00415360[k];
    if (g == 0)
        return;
    if (fn[INFO(g)[2]] != 0 && fn[INFO(g)[2]](g) == 0)
        func_003386D0(g, 6, 0xFF);
}

/* 0x00344410, 0xDC bytes. */
int func_00344410(u8 **g)
{
    int (*fn[8])(u8 **);
    u32 k;

    for (k = 0; k < 8; k++)
        fn[k] = g_00415380[k];
    if (g == 0)
        return 0;
    for (k = 0; k < 8; k++) {
        if (fn[k](g) != 0)
            return 1;
    }
    return 0;
}

/* 0x003444F0, 0x108 bytes. Reports a new order of a first-side group (orders 1-5). */
void func_003444F0(u8 **g, u32 old)
{
    u32 k;
    u8 v;

    if (g == 0)
        return;
    k = GI(g);
    v = func_00338410(k)[2];
    if (v != old && LEADER(g)[0x79] == 0 && (v != 1 || func_0033D3E0(g) != 0)
        && func_00344410(g) == 0 && (v == 5 || v == 4 || v == 2 || v == 3 || v == 1))
        func_0035CE60(k, v);
}

/* 0x00344600, 0x84 bytes. Group `g`'s order update. */
void func_00344600(u8 **g)
{
    u8 old;

    if (g == 0)
        return;
    old = INFO(g)[2];
    func_003430E0(g);
    func_00343EA0(g);
    func_00344330(g);
    func_003444F0(g, old);
}

/* 0x00344690, 0x19C bytes. Sets group `g`'s second order from its order (attacks go through a
 * holding place on the way when one fits). */
int func_00344690(u8 **g)
{
    u32 k, o = 0xD, t = 0;

    if (g == 0)
        return 0;
    k = GI(g);
    switch (func_00338410(k)[2]) {
    case 0:
        o = 0;
        t = 0xFF;
        break;
    case 1:
        if (func_0033D3E0(g) == 0) {
            int c = func_003410C0(g, func_0033C320(g));

            if (c == 0) {
                o = 1;
                t = func_00338410(k)[3];
            } else {
                o = 7;
                t = func_0034ED40((unsigned char *)PS2_PTR(c));
            }
        } else {
            o = 1;
            t = func_00338410(k)[3];
        }
        break;
    case 2:
        o = 2;
        t = func_00338410(k)[3];
        break;
    case 3:
        o = 3;
        t = func_00338410(k)[3];
        break;
    case 4:
        o = 4;
        t = func_00338410(k)[3];
        break;
    case 5: {
        int c = func_00340F00(g);

        if (c != 0) {
            o = 5;
            t = func_0034ED40((unsigned char *)PS2_PTR(c));
        }
        break;
    }
    }
    if (o < 0xD) {
        func_003387C0(g, o, t);
        return 1;
    }
    return 0;
}

/* 0x00344830, 0xB0 bytes. A group without a second order gets one. */
void func_00344830(u8 **g)
{
    int (*fn[1])(u8 **);
    int k;

    fn[0] = g_0045D054[0];
    if (g == 0 || INFO(g)[5] != 0xC)
        return;
    for (k = 0; k < 1; k++) {
        if (fn[k] != 0 && fn[k](g) != 0)
            return;
    }
}

/* 0x00344AC0, 0xD8 bytes, matching. A group falling back to a place it can no longer use picks another. */
int func_00344AC0(u8 **g)
{
    u32 k;
    int c;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[5] != 6)
        return 0;
    if (func_0033FE20(g, func_00338410(k)[6]) != 0)
        return 0;
    c = func_00340F90(g);
    if (c == 0)
        return 0;
    func_003387C0(g, 6, func_0034ED40((unsigned char *)PS2_PTR(c)));
    return 1;
}

/* 0x00344BA0, 0x104 bytes. A group holding on the way to an attack goes on (when ready or after
 * 120 frames). */
int func_00344BA0(u8 **g)
{
    u32 k;
    int ready;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[5] != 7 || func_00338410(k)[2] != 1)
        return 0;
    ready = func_0033D3E0(g);
    if (func_00338410(k)[7] < 0x78 && ready == 0)
        return 0;
    func_003387C0(g, 1, func_00338410(k)[3]);
    return 1;
}

/* 0x00344CB0, 0x220 bytes. A moving group that reached a quiet place moves on now and then (to a
 * neighbour at random). */
int func_00344CB0(u8 **g)
{
    int c, best = 0;
    u32 n, j;

    if (g == 0 || INFO(g)[5] != 5)
        return 0;
    c = func_0033C160(g);
    if (c == 0 || func_0033CB60(g, c) == 0)
        return 0;
    if (func_00352780((unsigned char *)PS2_PTR(c), func_0035D5A0(LEADER(g)[0x79])) != 0)
        return 0;
    if ((int)RANDOM() % 100 >= 5)
        return 0;
    n = func_0034EEF0((unsigned char *)PS2_PTR(c));
    for (j = 0; j < n; j++) {
        int cc = PS2_ADDR(func_0034EF60((unsigned char *)PS2_PTR(c), j));

        if (cc != 0 && func_0034EE50((unsigned char *)PS2_PTR(cc)) != 0 && func_0033FD60(g, func_0034ED40((unsigned char *)PS2_PTR(cc))) != 0
            && (best == 0 || (int)RANDOM() % 100 < 0x32))
            best = cc;
    }
    if (best == 0)
        return 0;
    func_003387C0(g, 5, func_0034ED40((unsigned char *)PS2_PTR(best)));
    return 1;
}

/* 0x00344ED0, 0xE0 bytes. A group linked with kind 3 follows its link. */
int func_00344ED0(u8 **g)
{
    u8 **h;

    if (g == 0)
        return 0;
    if (INFO(g)[5] == 8)
        return 1;
    if (func_00338C20(g) != 3)
        return 0;
    h = func_00338BA0(g);
    if (h == 0)
        return 0;
    func_003387C0(g, 8, GI(h));
    return 1;
}

/* 0x00344FB0, 0xD4 bytes, matching. A group of link kind 3 guards a place. */
int func_00344FB0(u8 **g)
{
    u32 k;
    int c;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[5] == 9)
        return 1;
    if (func_00338410(k)[0x27] != 3)
        return 0;
    c = func_00341270(g);
    if (c == 0)
        return 0;
    func_003387C0(g, 9, func_0034ED40((unsigned char *)PS2_PTR(c)));
    return 1;
}

/* 0x00345090, 0xA0 bytes, matching. A group with enemies on its cell fights in place. */
int func_00345090(u8 **g)
{
    if (g == 0)
        return 0;
    if (INFO(g)[5] == 10)
        return 1;
    if (func_0033CED0(g) == 0)
        return 0;
    func_003387C0(g, 10, 0xFF);
    return 1;
}

/* 0x00345130, 0xD8 bytes. Runs the second order choosers (until one takes). */
void func_00345130(u8 **g)
{
    int (*fn[7])(u8 **);
    u32 f, k;

    for (k = 0; k < 7; k++)
        fn[k] = g_004153A0[k];
    if (g == 0)
        return;
    f = UNIT_FLAGS(LEADER(g));
    if ((f & 0x30) != 0 && (f & 0x40) == 0)
        return;
    for (k = 0; k < 7; k++) {
        if (fn[k](g) != 0)
            return;
    }
}

/* 0x00345210, 0x2C bytes, matching. */
int func_00345210(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033F9D0(g) != 0;
}

/* 0x00345240, 0x6C bytes, matching. Whether the place of its second order is an enemy one. */
int func_00345240(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033F9E0(g, INFO(g)[6]) != 0;
}

/* 0x003452B0, 0x6C bytes, matching. */
int func_003452B0(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FBA0(g, INFO(g)[6]) != 0;
}

/* 0x00345320, 0x6C bytes, matching. */
int func_00345320(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FA70(g, INFO(g)[6]) != 0;
}

/* 0x00345390, 0x6C bytes, matching. */
int func_00345390(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FC30(g, INFO(g)[6]) != 0;
}

/* 0x00345400, 0x6C bytes, matching. */
int func_00345400(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FD60(g, INFO(g)[6]) != 0;
}

/* 0x00345470, 0x9C bytes, matching. Whether falling back still holds (the place still fits and the group
 * stays back or is under 80% life). */
int func_00345470(u8 **g)
{
    if (g == 0)
        return 0;
    if (func_0033FE20(g, INFO(g)[6]) == 0)
        return 0;
    if (func_0033D2C0(g) != 0)
        return 1;
    return (u32)func_0033B7B0(g) < 0x50;
}

/* 0x00345510, 0x6C bytes, matching. */
int func_00345510(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033FF50(g, INFO(g)[6]) != 0;
}

/* 0x00345580, 0x30 bytes. */
int func_00345580(u8 **g)
{
    if (g == 0)
        return 0;
    return func_00338C20(g) == 3;
}

/* 0x003455B0, 0x58 bytes, matching. */
int func_003455B0(u8 **g)
{
    if (g == 0)
        return 0;
    return INFO(g)[0x27] == 3;
}

/* 0x00345610, 0x80 bytes. Whether fighting in place still holds (30 frames at least). */
int func_00345610(u8 **g)
{
    if (g == 0)
        return 0;
    if (INFO(g)[7] < 0x1E)
        return 1;
    return func_0033CED0(g) != 0;
}

/* 0x00345690, 0x4C bytes. Whether a move has not arrived yet. */
int func_00345690(u8 **g)
{
    if (g == 0)
        return 0;
    return func_0033CB60(g, func_0033C160(g)) == 0;
}

/* 0x003456F0, 0xB8 bytes. Drops group `g`'s second order when it no longer holds. */
void func_003456F0(u8 **g)
{
    int (*fn[13])(u8 **);
    int k;

    for (k = 0; k < 13; k++)
        fn[k] = g_004153C0[k];
    if (g == 0)
        return;
    if (fn[INFO(g)[5]] != 0 && fn[INFO(g)[5]](g) == 0)
        func_003387C0(g, 0xC, 0xFF);
}

/* 0x003457B0, 0x80 bytes. */
int func_003457B0(u8 **g)
{
    if (g == 0)
        return 0;
    return g_0045D058(g) != 0;
}

/* 0x00345830, 0xC8 bytes. Reports a new second order 6 or 7 of a first-side group. */
void func_00345830(u8 **g, u32 old)
{
    u32 k;
    u8 v;

    if (g == 0)
        return;
    k = GI(g);
    v = func_00338410(k)[5];
    if (v != old && LEADER(g)[0x79] == 0 && func_003457B0(g) == 0 && (v == 6 || v == 7))
        func_0035CEA0(k, v);
}

/* 0x00345900, 0x84 bytes. Group `g`'s second order update. */
void func_00345900(u8 **g)
{
    u8 old;

    if (g == 0)
        return;
    old = INFO(g)[5];
    func_00344830(g);
    func_00345130(g);
    func_003456F0(g);
    func_00345830(g, old);
}

/* 0x00345990, 0x88 bytes. Sends group `g` to place `c`. */
void func_00345990(u8 **g, int c)
{
    u8 *l;
    u8 pos[4];
    float v[2];

    if (g == 0)
        return;
    l = LEADER(g);
    func_0034ED90((unsigned char *)PS2_PTR(c), pos);
    v[0] = 0.0f;
    v[1] = 0.0f;
    func_001D4F00(g, (const long long unsigned int *)(v), (const short unsigned int *)(pos));
    func_0034A250(l, pos, v);
    l = LEADER(g);
    *(float *)(l + 0x38) = v[0];
    *(float *)(l + 0x3C) = v[1];
    *(u32 *)(l + 0x84) |= 0x10;
    func_001D4F60(g, 0);
}

/* 0x00345A20, 0xE4 bytes. Sends group `g` after group `h`'s leader. */
void func_00345A20(u8 **g, u8 **h)
{
    u8 *u;
    float *p, v[2];
    u8 cell[2];

    if (g == 0)
        return;
    u = LEADER(h);
    p = (UNIT_FLAGS(u) & 0x20000) == 0 ? (float *)(u + 0x28) : (float *)(u + 0x30);
    v[0] = 0.0f;
    v[1] = 0.0f;
    cell[0] = (int)p[0] / 5000;
    cell[1] = (int)p[1] / 5000;
    func_001D4F00(g, (const long long unsigned int *)(v), (const short unsigned int *)(cell));
    func_001D4F60(g, PS2_ADDR(u));
}

/* 0x00345B20, 0x3C bytes, matching. Second order 1: to its place. */
void func_00345B20(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345B60, 0x3C bytes, matching. Second order 2: after its group. */
void func_00345B60(u8 **g)
{
    if (g != 0)
        func_00345A20(g, func_0033C1E0(g));
}

/* 0x00345BA0, 0x3C bytes, matching. */
void func_00345BA0(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345BE0, 0x3C bytes, matching. */
void func_00345BE0(u8 **g)
{
    if (g != 0)
        func_00345A20(g, func_0033C1E0(g));
}

/* 0x00345C20, 0x3C bytes, matching. */
void func_00345C20(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345C60, 0x3C bytes, matching. */
void func_00345C60(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345CA0, 0x3C bytes, matching. */
void func_00345CA0(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345CE0, 0x3C bytes, matching. */
void func_00345CE0(u8 **g)
{
    if (g != 0)
        func_00345A20(g, func_0033C1E0(g));
}

/* 0x00345D20, 0x3C bytes, matching. */
void func_00345D20(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345F50, 0x3C bytes, matching. */
void func_00345F50(u8 **g)
{
    if (g != 0)
        func_00345990(g, func_0033C160(g));
}

/* 0x00345FA0, 0xA0 bytes. Moves group `g` by its second order. */
void func_00345FA0(u8 **g)
{
    void (*fn[13])(u8 **);
    int k;

    for (k = 0; k < 13; k++)
        fn[k] = g_00415400[k];
    if (g == 0)
        return;
    if (fn[INFO(g)[5]] != 0)
        fn[INFO(g)[5]](g);
}

/* 0x00346040, 0x6C bytes. One of three effect kinds at random. */
int func_00346040(void)
{
    int t[3];

    t[0] = g_00415438[0];
    t[1] = g_00415438[1];
    t[2] = g_00415438[2];
    return t[RANDOM() % 3];
}

/* Battle comments, the groups' AI frame and the troop parameters (parts of 0x00346E90-
 * 0x00347F1C). */

extern u8 g_007B6270[2][0x456];          /* troop parameters: 0x25 kinds of 0x1E bytes per side */
extern u8 *g_005BA6A0;                   /* the battle set-up data */
extern int g_006AA5F0;

void func_003460B0(u8 **g);

/* 0x00346E90, 0x148 bytes. Comment 4 (3 in 10): a group defends a place the enemy attacks. */
int func_00346E90(u8 **g)
{
    u32 k;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0 || func_00338410(k)[2] != 3)
        return 0;
    if (func_0033F830(1, func_00338410(k)[3], func_0035D5A0(LEADER(g)[0x79])) == 0)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(4, k, 0x47);
        return 1;
    }
    return 0;
}

/* 0x00346FE0, 0xE8 bytes. Comment 5: a plain group falls back. */
int func_00346FE0(u8 **g)
{
    u32 k;

    if (g == 0 || func_0033B6E0(g) != 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[5] != 6)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(5, k, 0x47);
        return 1;
    }
    return 0;
}

/* 0x003470D0, 0x160 bytes. Comment 6: the group it chases falls back. */
int func_003470D0(u8 **g)
{
    u32 k, h;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0 || func_00338410(k)[2] != 2)
        return 0;
    h = GI(func_0033C3A0(g));
    if (func_00338410(h)[5] != 6)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(6, k, h);
        return 1;
    }
    return 0;
}

/* 0x00347230, 0x19C bytes. Comment 10: a player stands with a group attacking a place that 3
 * and more groups attack. */
int func_00347230(u8 **g)
{
    u32 k;
    int p;
    u8 **h;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_00338410(k)[2] != 1)
        return 0;
    p = func_0033D150(g);
    if (p < 0 || p > 1)
        return 0;
    h = func_0035DD10(p);
    if (func_00360C00() < 0x1E)
        return 0;
    if (func_0033F810(1, func_00338410(k)[3], LEADER(g)[0x79]) < 3)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(10, k, GI(h));
        return 1;
    }
    return 0;
}

/* 0x003473D0, 0x1E8 bytes. Comment 0xC: the same when its side defends more than it attacks. */
int func_003473D0(u8 **g)
{
    u32 k;
    int p;
    u8 **h;
    u8 side;
    u32 a, b, c, d;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_00338410(k)[2] != 1)
        return 0;
    p = func_0033D150(g);
    if (p < 0 || p > 1)
        return 0;
    h = func_0035DD10(p);
    if (func_00360C00() < 0x1E)
        return 0;
    side = LEADER(g)[0x79];
    a = func_0033F810(1, 0xFF, side);
    b = func_0033F810(2, 0xFF, side);
    c = func_0033F810(3, 0xFF, side);
    d = func_0033F810(4, 0xFF, side);
    if (c + d < a + b + 2)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(0xC, k, GI(h));
        return 1;
    }
    return 0;
}

/* 0x003475C0, 0x58 bytes, matching. An officer group's AI frame. */
void func_003475C0(u8 **g)
{
    if (g == 0)
        return;
    func_00341E60(g);
    func_003422B0(g);
    func_00344600(g);
    func_00345900(g);
    func_00345FA0(g);
    func_003460B0(g);
}

/* 0x00347620, 8 bytes, matching. */
void func_00347620(u8 **g)
{
}

/* 0x00347630, 0xD0 bytes. Group `g`'s AI frame (officer groups only). */
void func_00347630(u8 **g)
{
    if (g == 0 || (GFLAGS(g) & 1) == 0 || !ALIVE(UNIT_FLAGS(LEADER(g))))
        return;
    if (func_0033B050(g) != 0)
        func_003475C0(g);
    else if (func_0033B090(g) != 0)
        func_00347620(g);
}

/* 0x00347700, 0x90 bytes. Runs one group's AI a frame (in turn over 50 frames). */
void func_00347700(void)
{
    u32 k = g_006AA5F0;

    if (k < 0x47 && (GFLAGS(GROUP(k)) & 1) != 0)
        func_00347630(GROUP(k));
    g_006AA5F0 = k < 0x31 ? k + 1 : 0;
}

/* 0x00347790, 0x70 bytes. The groups' AI (from the 10th second, or at once with func_0036D300). */
void func_00347790(void)
{
    if ((func_0036D300() != 0 || g_00669F9C / 0x32 > 9) && func_0036D310() == 0)
        func_00347700();
}

/* 0x00347800, 0x1C bytes, matching. */
int func_00347800(u8 **g, u32 i)
{
    return func_0033F9E0(g, i);
}

/* 0x00347820, 0x1C bytes, matching. */
int func_00347820(u8 **g, u32 i)
{
    return func_0033FA70(g, i);
}

/* 0x00347840, 0x1C bytes, matching. */
int func_00347840(u8 **g, u32 i)
{
    return func_0033FBA0(g, i);
}

/* 0x00347860, 0x1C bytes, matching. */
int func_00347860(u8 **g, u32 i)
{
    return func_0033FC30(g, i);
}

/* 0x00347880, 0x1C bytes, matching. */
int func_00347880(u8 **g, int a, int b)
{
    return func_00340860(g);
}

/* 0x003478A0, 0x1C bytes, matching. */
int func_003478A0(u8 **g)
{
    return func_003408F0();
}

/* 0x003478C0, 0x1C bytes, matching. */
int func_003478C0(u8 **g, int a, int b)
{
    return func_00340BF0(g);
}

/* 0x003478E0, 0x1C bytes, matching. */
int func_003478E0(u8 **g)
{
    return func_00340C80();
}

/* 0x00347900, 0x4C bytes. Side `s`'s troop parameters of kind `i` (0 past them). */
u8 *func_00347900(u32 s, u32 i)
{
    if (s < 2 && i < 0x25)
        return g_007B6270[s] + i * 0x1E;
    return 0;
}

/* 0x00347950, 0x28 bytes, matching. */
u8 *func_00347950(int p)
{
    return func_00347900(0, func_00362320(p));
}

/* 0x00347980, 0x74 bytes. Unit `u`'s troop parameters (by its side, or for soldiers 0x400 by
 * their record's eighth). */
u8 *func_00347980(u8 *u)
{
    u32 s;

    if ((UNIT_FLAGS(u) & 0x400) == 0)
        s = u[0x79];
    else
        s = (u32)((u - g_00693970) / 0x88) >> 3;
    return func_00347900(s, func_0034A440(u));
}

/* 0x00347A00, 0xB8 bytes. Fills the second side's troop kinds 9-14 with the set-up's
 * defaults. */
void func_00347A00(void)
{
    u8 *d = g_005BA6A0;
    u32 s, k;

    for (s = 0; s < 2; s++) {
        if (s == 0)
            continue;
        for (k = 9; k < 0xF; k++) {
            u16 *p = (u16 *)(g_007B6270[s] + k * 0x1E);

            p[0] = 0x1EB;
            p[1] = 0x1EB;
            p[2] = 0x32;
            p[3] = 5;
            *(u8 *)(p + 4) = 7;
            p[5] = 10;
            p[6] = *(u16 *)(d + 0x5472);
            p[7] = 5;
            p[8] = 5;
            p[9] = *(u16 *)(d + 0x5478);
            p[10] = *(u16 *)(d + 0x547A);
            p[0xB] = *(u16 *)(d + 0x547C);
            p[0xC] = *(u16 *)(d + 0x547E);
            p[0xD] = 5;
            p[0xE] = 5;
        }
    }
}

/* 0x00347E70, 0xA8 bytes. Copies player `p`'s troop values from the set-up into the first
 * side's current kind. */
void func_00347E70(int p)
{
    u8 *r, *s;

    if (p < 0 || p >= 2)
        return;
    r = func_00347950(p);
    s = g_005BA6A0 + (p + 0x24E) * 0x2C;
    *(u16 *)(r + 4) = *(u16 *)(s + 0xC);
    *(u16 *)(r + 0xC) = *(u16 *)(s + 0xE);
    *(u16 *)(r + 0xE) = *(u16 *)(s + 0x10);
    *(u16 *)(r + 0x10) = *(u16 *)(s + 0x12);
    *(u16 *)(r + 0x12) = *(u16 *)(s + 0x14);
    *(u16 *)(r + 0x14) = *(u16 *)(s + 0x16);
    *(u16 *)(r + 0x16) = *(u16 *)(s + 0x18);
    *(u16 *)(r + 0x18) = *(u16 *)(s + 0x1A);
}

/* More AI choices (0x003448E0, 0x003460B0, 0x00346280). */

/* 0x003448E0, 0x1DC bytes. A plain-led group that should stay back falls back to a place now
 * and then (1 in 10; 1 in 2 for the second side's commander; never off the front under tactic
 * 0xB). */
int func_003448E0(u8 **g)
{
    u32 k, p;
    u8 side;
    int c;

    if (g == 0 || (UNIT_FLAGS(LEADER(g)) & 0x30) != 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[5] == 6)
        return 0;
    if (func_00338410(k)[2] == 3) {
        side = LEADER(g)[0x79];
        if (func_00338410(k)[3] == func_0035F200(side))
            return 0;
    }
    if (func_0033D2C0(g) == 0)
        return 0;
    p = func_0033B150(g) == 0 ? 10 : 0x32;
    if (func_0036F390(func_0035D5A0(LEADER(g)[0x79]), 0xB) != 0 && func_0033B150(g) == 0
        && func_0033CEA0(g, func_0035D5A0(LEADER(g)[0x79])) == 0)
        p = 0;
    if (RANDOM() % 100 >= p)
        return 0;
    c = func_00340F90(g);
    if (c == 0)
        return 0;
    func_003387C0(g, 6, func_0034ED40((unsigned char *)PS2_PTR(c)));
    return 1;
}

/* 0x003460B0, 0x1C8 bytes. Under tactic 0x1E, an officer-led group sometimes sends a heal
 * effect to the players standing with it (more often the lower their life). */
void func_003460B0(u8 **g)
{
    u8 *l, *a;
    u32 f;
    int p;

    if (g == 0 || func_0036F520(LEADER(g)[0x79], 0x1E) == 0)
        return;
    l = LEADER(g);
    f = UNIT_FLAGS(l);
    if ((f & 0x30) != 0 || (f & 0x20000) == 0)
        return;
    a = *(u8 **)(OFFICER(*(int *)(l + 0x14)) + 0x14);
    for (p = 0; p < 2; p++) {
        if (func_0033CC80(g, p) != 0) {
            u8 *o = OFFICER(p);
            short max = *(short *)(o + 0x80), cur = *(short *)(o + 0x82);
            int q = max / 4, h = max / 2;
            u32 m = 1;

            if (q > 0x32)
                q = 0x32;
            if (h > 100)
                h = 100;
            if (cur < q)
                m = 5;
            else if (cur < h)
                m = 3;
            if (RANDOM() % 100 < m)
                func_0024D070(func_00346040(), (unsigned int *)(a + 0x40));
        }
    }
}

/* 0x00346280, 0x2F0 bytes. Comment 0: a group defending a place that fewer than 2 groups defend
 * asks a friendly group going there for help. */
int func_00346280(u8 **g)
{
    u32 list[16], n, j, k;
    u8 **r = 0;
    int c;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0 || func_00338410(k)[2] != 3)
        return 0;
    if (func_0033F810(3, func_00338410(k)[3], LEADER(g)[0x79]) >= 2)
        return 0;
    c = func_0033C320(g);
    n = func_0033F430(LEADER(g)[0x79], 1, list, 0x10);
    for (j = 0; j < n; j++) {
        u8 **h = GROUP(list[j]);

        if (h != g && func_0033B6E0(h) == 0 && (UNIT_FLAGS(LEADER(h)) & 0x30) == 0
            && func_0033D230(h) == c && (INFO(h)[2] != 3 || func_0033C320(h) != c)
            && (r == 0 || (int)RANDOM() % 100 < 0x32))
            r = h;
    }
    if (r == 0)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(0, k, GI(r));
        return 1;
    }
    return 0;
}

/* Comments 1-3 and the chase choice (0x00343360, 0x00346570-0x00346E8C). */

/* 0x00346570, 0x30C bytes. Comment 1: another plain group attacks the same place along with
 * group `g` (both orders fresh). */
int func_00346570(u8 **g)
{
    u32 list[16], n, j, k;
    u8 **r = 0;
    int c;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0 || func_00338410(k)[2] != 1)
        return 0;
    c = func_0033C320(g);
    n = func_0033F430(LEADER(g)[0x79], 1, list, 0x10);
    for (j = 0; j < n; j++) {
        u8 **h = GROUP(list[j]);
        u8 *hr;

        if (h == g || func_0033B6E0(h) != 0 || (UNIT_FLAGS(LEADER(h)) & 0x30) != 0)
            continue;
        hr = INFO(h);
        if (hr[2] == 1 && func_0033C320(h) == c && INFO(h)[4] < 0xB && INFO(h)[5] == 1
            && func_0033C160(h) == c && INFO(h)[7] < 0xB
            && (r == 0 || (int)RANDOM() % 100 < 0x32))
            r = h;
    }
    if (r == 0)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(1, k, GI(r));
        return 1;
    }
    return 0;
}

/* 0x00346880, 0x2E8 bytes. Comment 2: group `g` attacks or chases toward a place a friendly
 * group stands on and defends. */
int func_00346880(u8 **g)
{
    u32 list[16], n, j, k;
    u8 **r = 0;
    int c;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0)
        return 0;
    if (func_00338410(k)[2] != 1 && func_00338410(k)[2] != 2)
        return 0;
    c = func_0033D230(g);
    if (c == 0)
        return 0;
    n = func_0033F430(LEADER(g)[0x79], 1, list, 0x10);
    for (j = 0; j < n; j++) {
        u8 **h = GROUP(list[j]);

        if (h != g && func_0033B6E0(h) == 0 && (UNIT_FLAGS(LEADER(h)) & 0x30) == 0
            && func_0033CB60(h, c) != 0 && INFO(h)[2] == 3 && func_0033C320(h) == c
            && (r == 0 || (int)RANDOM() % 100 < 0x32))
            r = h;
    }
    if (r == 0)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(2, k, GI(r));
        return 1;
    }
    return 0;
}

/* 0x00346B70, 0x320 bytes. Comment 3: another plain group has just been given the same orders
 * as group `g`. */
int func_00346B70(u8 **g)
{
    u32 list[16], n, j, k;
    u8 **r = 0;
    char o, t, o2, t2;

    if (g == 0)
        return 0;
    k = GI(g);
    if (func_00338410(k)[8] != 4 || func_0033B6E0(g) != 0)
        return 0;
    o = func_00338410(k)[2];
    t = func_00338410(k)[3];
    o2 = func_00338410(k)[5];
    t2 = func_00338410(k)[6];
    n = func_0033F430(LEADER(g)[0x79], 1, list, 0x10);
    if (o != 2 && o != 1)
        return 0;
    for (j = 0; j < n; j++) {
        u8 **h = GROUP(list[j]);
        u32 i;

        if (h == g || func_0033B6E0(h) != 0 || (UNIT_FLAGS(LEADER(h)) & 0x30) != 0)
            continue;
        i = GI(h);
        if (o == (char)func_00338410(i)[2] && t == (char)func_00338410(i)[3]
            && func_00338410(i)[4] < 0xB && o2 == (char)func_00338410(i)[5]
            && t2 == (char)func_00338410(i)[6] && func_00338410(i)[7] < 0xB
            && (r == 0 || (int)RANDOM() % 100 < 0x32))
            r = h;
    }
    if (r == 0)
        return 0;
    if ((int)RANDOM() % 100 < 0x1E) {
        func_0035CEE0(3, k, 0x47);
        return 1;
    }
    return 0;
}

/* 0x00343360, 0x310 bytes. Away from its place, group `g` sometimes (1 in 10) chases an enemy
 * group on its cell (the one it chases already surely, one falling back 3 in 10, else 1 in 10). */
int func_00343360(u8 **g)
{
    u8 **list[16], **pick = 0;
    u32 n = 0, k;
    int c;
    u8 e;

    if (g == 0)
        return 0;
    c = func_0033C320(g);
    if (c != 0 && func_0033CB60(g, c) != 0)
        return 0;
    e = func_0035D5A0(LEADER(g)[0x79]);
    for (k = 0; k < 0x10; k++) {
        u8 **h = func_0033EF80(k);

        if (h != 0 && (GFLAGS(h) & 1) != 0 && e == LEADER(h)[0x79] && func_0033CC20(g, h) != 0)
            list[n++] = h;
    }
    if (n == 0)
        return 0;
    for (k = 0; k < n; k++) {
        u8 **h = list[k];
        u32 p = 10;

        if (INFO(g)[2] == 2 && func_0033C3A0(g) == h)
            p = 100;
        else if (INFO(h)[5] == 6)
            p = 0x1E;
        if (RANDOM() % 100 < p)
            pick = h;
    }
    if (pick == 0)
        return 0;
    if ((int)RANDOM() % 100 >= 10)
        return 0;
    if (INFO(g)[2] == 2 && func_0033C3A0(g) == pick)
        return 0;
    func_003386D0(g, 2, GI(pick));
    return 1;
}

/* A fallen leader's revival, the roaming move and the troop parameters' set-up (0x0033DAB0,
 * 0x00345D60, 0x00347AC0). */

extern int g_00415450[5];                /* the troop strength by difficulty (percent) */

void func_00347A00(void);

/* 0x0033DAB0, 0x1E8 bytes. A leader beaten in a duel (flags 2 and 8, its base +0x18 clear) gets
 * up with full life; its group's units are given back to it. */
void func_0033DAB0(u8 **g)
{
    u8 *l = LEADER(g), *b, *list[13];
    u32 f = UNIT_FLAGS(l), n = 0, k;

    if ((f & 2) == 0 || (f & 8) == 0)
        return;
    b = *(u8 **)(l + 4);
    if (b == 0 || b[0x18] != 0)
        return;
    UNIT_FLAGS(l) = f & 0xFFFFFFF9;
    UNIT_FLAGS(l) = f & 0xDFFFFFF9;
    UNIT_FLAGS(l) = (f & 0xDFFFFFF9) | 0x1000000;
    l[0x7A] = 0;
    *(short *)(l + 0x4E) = *(short *)(l + 0x4C) < 1 ? 0 : *(short *)(l + 0x4C);
    *(short *)(l + 0x52) = *(short *)(l + 0x50) < 1 ? 0 : *(short *)(l + 0x50);
    *(u16 *)(l + 0x4A) = 0x1AD;
    *(int *)(l + 0x6C) = g_00669F9C;
    func_00118850((unsigned char *)(list), 0x34);
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k];

        if (u != 0 && u != l && ACTIVE(UNIT_FLAGS(u)))
            list[n++] = u;
    }
    func_001BB5C0(b, l, (int *)(g));
    for (k = 0; k < n; k++)
        func_001BB5C0(b, list[k], (int *)(g));
    func_001F1A30(l);
    *(u32 *)(l + 0x84) &= 0xFFFEFFFF;
}

/* 0x00345D60, 0x1E4 bytes. Second order 5 (move): units without a target (or one out of the
 * 0x170-0x183 records) take one of up to 10 enemy records at random. */
void func_00345D60(u8 **g)
{
    u8 e;
    u32 k;

    if (g == 0)
        return;
    e = func_0035D5A0(LEADER(g)[0x79]);
    for (k = 0; k < 0xD; k++) {
        u8 *u = g[k], *t;

        if (u == 0 || !ACTIVE(UNIT_FLAGS(u)))
            continue;
        t = *(u8 **)(u + 0x18);
        if (t != 0 && func_0034A710(u, t) != 0) {
            u32 r = (t - g_00693970) / 0x88;

            if (r >= 0x170 && r <= 0x183)
                continue;
        }
        if (t == 0)
            continue;
        {
            int list[12], n = func_0034AFA0((unsigned int *)(list), 10, e);
            u8 *b;

            if (n == 0)
                continue;
            b = g_00693970 + list[(int)RANDOM() % n] * 0x88;
            if (b != 0) {
                u16 c = *(u16 *)(b + 0x40);

                *(u8 **)(u + 0x1C) = b;
                *(u32 *)(u + 0x84) |= 0x10;
                *(unsigned long long *)(u + 0x38) = 0;
                *(u32 *)(u + 0x84) |= 0x10;
                *(u16 *)(u + 0x44) = c;
            }
        }
    }
}

/* 0x00347AC0, 0x3A4 bytes. Builds both sides' troop parameters (0x25 kinds) from the set-up
 * data, the battle's officers for the first 8 kinds, and the difficulty's strength. */
void func_00347AC0(void)
{
    int pct[5], m;
    u32 s, k;

    for (k = 0; k < 5; k++)
        pct[k] = g_00415450[k];
    m = pct[g_00669D60[0x21]];
    for (s = 0; s < 2; s++) {
        u16 *p0 = (u16 *)g_007B6270[s];

        for (k = 0; k < 0x25; k++) {
            u16 *p = p0 + k * 0xF;
            u8 *d, *d2;

            p[0] = func_0035EA40(k);
            p[1] = func_0035EA60(k);
            *(u8 *)(p + 4) = func_0035EA80(k);
            p[5] = func_0035EAA0(k);
            d = g_005BA6A0 + p[0] * 0x2C;
            p[6] = *(u16 *)(d + 0xE);
            p[7] = *(u16 *)(d + 0x10);
            p[8] = *(u16 *)(d + 0x12);
            p[9] = *(u16 *)(d + 0x14);
            p[10] = *(u16 *)(d + 0x16);
            p[0xB] = *(u16 *)(d + 0x18);
            p[0xC] = *(u16 *)(d + 0x1A);
            p[2] = *(u16 *)(d + 0xC);
            d2 = g_005BA6A0 + p[1] * 0x2C;
            p[3] = *(u16 *)(d2 + 0xC);
            p[0xD] = *(u16 *)(d2 + 0x10);
            p[0xE] = *(u16 *)(d2 + 0x12);
            if (k > 8 && k < 0xF) {
                *(u32 *)(d + 0x28) |= 0x80000000;
                d[0x1C] = 0;
                *(u32 *)(d + 0x28) &= 0x7FFFFFFF;
            }
        }
        for (k = 0; k < 8; k++) {
            u16 *q = (u16 *)func_00347900(s, k);

            if (func_00362160(s, k) == 0x252) {
                q[0] = 0x252;
                q[1] = 0x252;
                q[2] = 0;
                q[3] = 0;
                *(u8 *)(q + 4) = 0;
                q[6] = 0;
                q[7] = 0;
                q[8] = 0;
                q[9] = 0;
                q[10] = 0;
                q[0xB] = 0;
                q[0xC] = 0;
                q[0xD] = 0;
                q[0xE] = 0;
            } else {
                int v = func_00363690(s, k);

                if (v != 2) {
                    int o = *(int *)(g_00669D60 + 0x9C + v * 0x48);
                    u8 *d = g_005BA6A0 + o * 0x2C;

                    q[0] = o;
                    q[2] = *(u16 *)(d + 0xC);
                    q[6] = *(u16 *)(d + 0xE);
                    q[7] = *(u16 *)(d + 0x10);
                    q[8] = *(u16 *)(d + 0x12);
                    q[9] = *(u16 *)(d + 0x14);
                    q[10] = *(u16 *)(d + 0x16);
                    q[0xB] = *(u16 *)(d + 0x18);
                    q[0xC] = *(u16 *)(d + 0x1A);
                }
            }
        }
        for (k = 0; k < 0x25; k++) {
            u16 *p = p0 + k * 0xF;

            p[3] = p[3] * 0x50u / 100;
            if (k > 0x1A && k < 0x23) {
                p[2] = (u32)(p[2] * m) / 100;
                p[3] = (u32)(p[3] * m) / 100;
            }
        }
    }
    if (func_0036D310() != 0)
        func_00347A00();
}
