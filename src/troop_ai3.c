/*
 * troop_ai3.c - battle officer AI steps between 0x002B00D0 and 0x002B3CEC (officers are the
 * 0xC0-byte records at 0x006A3A30: +0x04 the next one of the group, +0x08 the target, +0x10 the
 * troop, +0x14 the unit, +0x78 a timer, +0x7B the kind, +0x7C the behaviour, +0x7D the state,
 * +0x80/+0x82 life and its maximum?, +0xB8/+0xBC flags): attack choices by the chance table of
 * the officer's kind (0x001F14E0), guard breaks, and groups facing their target. Original file
 * name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_TROOP_AI3_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A3A30[][0xC0];
extern u32 g_7000015C;
extern u32 g_70000D60;                   /* (scratchpad) */
extern u32 g_700000C0[4];                /* (scratchpad) a zero vector */
extern u32 g_00669F60;                   /* settings flags */
extern u8 g_00669D81;                    /* the difficulty */
extern int g_00441660[][4];

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define FL_B8(o) (*(u32 *)((o) + 0xB8))
#define FL_BC(o) (*(u32 *)((o) + 0xBC))
#define TARGET(o) (*(u8 **)((o) + 8))
#define UNIT(o) (*(u8 **)((o) + 0x14))
#define NEXT(o) (*(u8 **)((o) + 4))
#define S16(o, k) (*(short *)((o) + (k)))
#define SET_STATE(o, s) do { FL_BC(o) &= 0xFFF8003F; (o)[0x7D] = (s); } while (0)
/* The officer leading `o`'s troop (itself when it is a leader). */
#define LEADER(o) ((FL_B8(o) & 0x180) == 0 ? g_006A3A30[*(int *)(*(u8 **)((o) + 0x10) + 0x14)] : (o))

/* Stops the unit's move. */
#define STOP_MOVE(u) do {                                               \
    *(int *)((u) + 0x13C) = 0;                                          \
    ((u32 *)((u) + 0x1D0))[0] = g_700000C0[0];                          \
    ((u32 *)((u) + 0x1D0))[1] = g_700000C0[1];                          \
    ((u32 *)((u) + 0x1D0))[2] = g_700000C0[2];                          \
    ((u32 *)((u) + 0x1D0))[3] = g_700000C0[3];                          \
} while (0)

/* A timer of `n` frames at 50 per 60. */
#define TIMER_SET(o, n) do {                                            \
    if ((n) == 0) {                                                     \
        S16(o, 0x78) = 0;                                               \
    } else {                                                            \
        u32 t_ = (u32)((n) * 0x32) / 0x3C;                              \
        S16(o, 0x78) = t_ == 0 ? 1 : t_;                                \
    }                                                                   \
} while (0)

void func_00271A10(u8 *o, int k);
void func_002AFF50(u8 *o, int k);
void func_002AFDD0(u8 *o);
void func_002AFC20(u8 *o);
void func_00206080(u8 *o);
void func_00207930(u8 *o);
void func_00204B60(u8 *o, int k);
int func_002B13F0(u8 *o, u8 *l);
void func_002B3BF0(u8 *o);
float func_002B19A0(u8 *o);
void func_002B1D00(u8 *o, u8 *l);

int func_002B00D0(u8 *o);
int func_002B0210(u8 *o, int a, int b);
void func_002B1040(u8 *o, int a);

#define CHANCE(v) (RANDOM() % 100 < (u32)(v))

/* 0x002B00D0, 0xAC bytes. A counter attack (action 0x19) when the unit can and the dice say so. */
int func_002B00D0(u8 *o)
{
    if ((*(u32 *)(*(u8 **)(UNIT(o) + 0x210) + 0x18) & 8) && *(int *)(TARGET(o) + 0xC) == 0) {
        u8 *c = func_001F14E0(o);

        if (CHANCE(c[7] >> 1)) {
            func_00271A10(o, 0x19);
            return 1;
        }
    }
    return 0;
}

/* 0x002B0180, 0x8C bytes. Attacks (combo or charge). */
void func_002B0180(u8 *o, int b)
{
    SET_STATE(o, 2);
    if (func_00239140(o, 1) == 0 && func_002B00D0(o) == 0) {
        if (b == 0)
            func_002AFF50(o, 8);
        else
            func_002AFDD0(o);
    }
}

/* 0x002B0210, 0x104 bytes. The guard chance: higher when `a` is small next to `b`. */
int func_002B0210(u8 *o, int a, int b)
{
    u8 *c = func_001F14E0(o);

    return RANDOM() % 100
        < (u32)(int)(((50.0f - ((float)a * 100.0f) / (float)b) * 0.01f + 1.0f) * (float)c[9] * 0.5f);
}

/* 0x002B0320, 0x13C bytes. Maybe uses an item (kinds 1-4 by the difficulty's table). */
void func_002B0320(u8 *o)
{
    u32 k;
    int *t, d;

    if ((g_00669F60 & 8) || TARGET(o) == 0 || (FL_B8(TARGET(o)) & 0xC) == 0)
        return;
    if (S16(o, 0x82) * 2 > S16(o, 0x80) || func_002B0210(o, S16(o, 0x82), S16(o, 0x80)) == 0)
        return;
    d = RANDOM() % 100 + 1;
    t = g_00441660[g_00669D81];
    for (k = 0; k < 4; k++) {
        if (d <= t[k])
            break;
    }
    if (k == 3)
        k = 4;
    else if (k == 2)
        k = 3;
    else if (k == 1)
        k = 2;
    else if (k == 0)
        k = 1;
    else
        return;
    func_0024D380(k, PS2_ADDR(UNIT(o)));
}

/* 0x002B0460, 0x210 bytes. A guard (state 2, flag 0x20000) against the target's attack. */
int func_002B0460(u8 *o)
{
    u8 *u, *c;
    u32 f;

    if (g_00669F60 & 8)
        return 0;
    if (TARGET(o) == 0)
        return 0;
    if ((FL_B8(TARGET(o)) & 0xC) == 0)
        return 0;
    if (S16(o, 0xA4) != 0)
        return 0;
    u = UNIT(o);
    f = *(u32 *)(*(u8 **)(u + 0x210) + 0x18);
    if (!((f & 8) && !(f & 0x20)))
        return 0;
    if (S16(o, 0x80) < S16(o, 0x82) * 2)
        return 0;
    if (func_002B0210(o, S16(o, 0x82), S16(o, 0x80)) == 0)
        return 0;
    SET_STATE(o, 2);
    S16(o, 0x88) = 0;
    func_00204CD0(o, 0x20000);
    c = func_001F14E0(o);
    TIMER_SET(o, c[0xE]);
    FL_BC(o) |= 0x20000;
    g_70000D60 = 0;
    func_00253300(0xB, u);
    return 1;
}

/* 0x002B0670, 0x280 bytes. Chooses an attack (kind A). */
void func_002B0670(u8 *o)
{
    float f;
    u8 *c;

    if (func_002B0460(o) != 0)
        return;
    if (func_00238930(o, &f) == 0)
        return;
    c = func_001F14E0(o);
    if (!(g_00669F60 & 8) || !(FL_B8(o) & 0x10)) {
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B0180(o, 0);
            return;
        }
        if (CHANCE((int)((float)c[1] * f))) {
            func_002B0180(o, 1);
            return;
        }
        if (func_00238F50(o) != 0)
            return;
    } else {
        if (func_00238F50(o) != 0)
            return;
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B0180(o, 0);
            return;
        }
        if (CHANCE((int)((float)c[1] * f))) {
            func_002B0180(o, 1);
            return;
        }
    }
    if (CHANCE(c[3]))
        func_002AFC20(o);
    else
        func_00206080(o);
}

/* 0x002B08F0, 0x1C bytes, matching. */
void func_002B08F0(u8 *o)
{
    func_00207930(o);
}

/* 0x002B0910, 0x6C bytes. */
int func_002B0910(u8 *o)
{
    func_002B0320(o);
    if (TARGET(o) == 0 || (FL_B8(TARGET(o)) & 0xC) == 0) {
        if (func_00238DE0(o, 1) == 0)
            func_00206080(o);
        return 1;
    }
    return 0;
}

/* 0x002B0980, 0x9C bytes. The behaviour step (kind A). */
void func_002B0980(u8 *o)
{
    char b = o[0x7C];

    if (b == 3) {
        if (func_002B0910(o) == 0)
            func_002B08F0(o);
    } else if (b == 2) {
        func_002B08F0(o);
    } else if (b == 1) {
        func_002396B0(PS2_ADDR(o), 1);
    } else if (b == 0) {
        func_002B0670(o);
    }
}

/* 0x002B0A20, 0x94 bytes. A special attack (actions 0x15-0x18). */
void func_002B0A20(u8 *o, u8 *c)
{
    u32 r1, hit;

    SET_STATE(o, 2);
    r1 = (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039);
    hit = RANDOM() % 100 < c[1];
    func_00271A10(o, ((r1 >> 0x10) & 1) == 0 ? hit + 0x15 : hit + 0x17);
}

/* float to unsigned as the original does it. */
static u32 f2u(float f)
{
    if (f < 2147483648.0f)
        return (u32)(int)f;
    return (u32)(int)(f - 2147483648.0f) | 0x80000000;
}

/* 0x002B0AC0, 0x374 bytes. Chooses an attack (kind B). */
void func_002B0AC0(u8 *o)
{
    float f;
    u8 *c;

    if (func_002B0460(o) != 0 || func_00238930(o, &f) == 0)
        return;
    c = func_001F14E0(o);
    if (CHANCE((int)((float)c[1] * f))) {
        func_002B0A20(o, c);
        return;
    }
    if (!(g_00669F60 & 8) || !(FL_B8(o) & 0x10)) {
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B1040(o, 0);
            return;
        }
        f = (float)c[1] * f;
        if (RANDOM() % 100 < f2u(f)) {
            func_002B0180(o, 1);
            return;
        }
        if (func_00238F50(o) != 0)
            return;
    } else {
        if (func_00238F50(o) != 0)
            return;
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B1040(o, 0);
            return;
        }
        f = (float)c[1] * f;
        if (RANDOM() % 100 < f2u(f)) {
            func_002B0180(o, 1);
            return;
        }
    }
    if (CHANCE(c[3]))
        func_002AFC20(o);
    else
        func_00206080(o);
}

/* 0x002B0E40, 0x9C bytes. The behaviour step (kind B). */
void func_002B0E40(u8 *o)
{
    char b = o[0x7C];

    if (b == 3) {
        if (func_002B0910(o) == 0)
            func_002B08F0(o);
    } else if (b == 2) {
        func_002B08F0(o);
    } else if (b == 1) {
        func_002396B0(PS2_ADDR(o), 1);
    } else if (b == 0) {
        func_002B0AC0(o);
    }
}

/* 0x002B0EE0, 0x158 bytes. A combo: its length by two dice rows of the chance table. */
void func_002B0EE0(u8 *o)
{
    u8 *c = func_001F14E0(o), *u;
    int a = 0, b = 0, k;

    for (k = 0; k < 3; k++, a++) {
        if (c[4] <= RANDOM() % 100)
            break;
    }
    for (k = 0; k < 2; k++, b++) {
        if (c[5] <= RANDOM() % 100)
            break;
    }
    if (a == 0) {
        if (b == 0) {
            func_00204B60(o, 2);
            return;
        }
        b += 6;
    } else if (a == 1) {
        b += 0xD;
    } else {
        b += 0x11;
    }
    if (func_00240E20(PS2_ADDR(UNIT(o))) == 0) {
        func_00271A10(o, b);
    } else {
        u = UNIT(o);
        STOP_MOVE(u);
    }
}

/* 0x002B1040, 0x8C bytes. Attacks (combo or charge, kind B). */
void func_002B1040(u8 *o, int b)
{
    SET_STATE(o, 2);
    if (func_00239140(o, 1) == 0 && func_002B00D0(o) == 0) {
        if (b == 0)
            func_002AFF50(o, 6);
        else
            func_002B0EE0(o);
    }
}

/* 0x002B10D0, 0x280 bytes. Chooses an attack (kind C). */
void func_002B10D0(u8 *o)
{
    float f;
    u8 *c;

    if (func_002B0460(o) != 0)
        return;
    if (func_00238930(o, &f) == 0)
        return;
    c = func_001F14E0(o);
    if (!(g_00669F60 & 8) || !(FL_B8(o) & 0x10)) {
        if (CHANCE((int)((float)c[1] * f))) {
            func_002B1040(o, 1);
            return;
        }
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B1040(o, 0);
            return;
        }
        if (func_00238F50(o) != 0)
            return;
    } else {
        if (func_00238F50(o) != 0)
            return;
        if (CHANCE((int)((float)c[1] * f))) {
            func_002B1040(o, 1);
            return;
        }
        if (CHANCE((int)((float)c[0] * f))) {
            func_002B1040(o, 0);
            return;
        }
    }
    if (CHANCE(c[3]))
        func_002AFC20(o);
    else
        func_00206080(o);
}

/* 0x002B1350, 0x9C bytes. The behaviour step (kind C). */
void func_002B1350(u8 *o)
{
    char b = o[0x7C];

    if (b == 3) {
        if (func_002B0910(o) == 0)
            func_002B08F0(o);
    } else if (b == 2) {
        func_002B08F0(o);
    } else if (b == 1) {
        func_002396B0(PS2_ADDR(o), 1);
    } else if (b == 0) {
        func_002B10D0(o);
    }
}

/* 0x002B1630, 0x29C bytes. A group member's move while its leader `l` acts (flag 0x200000: on the
 * way, 0x10000: in place). */
void func_002B1630(u8 *o, u8 *l)
{
    u8 *u;

    if (!(FL_BC(o) & 0x200000)) {
        if ((FL_B8(o) & 0x180) == 0 && !(FL_BC(l) & 0x200000)) {
            u = UNIT(o);
            STOP_MOVE(u);
        } else {
            u32 fl = 0x200000;
            int n, t;

            if (func_002B13F0(o, l) == 0) {
                n = 0x14;
            } else {
                n = 10;
                fl = 0x210000;
            }
            FL_BC(o) |= fl;
            t = n == 0 ? 1 : (int)(RANDOM() % n + 1);
            TIMER_SET(o, t);
        }
    } else if ((FL_B8(o) & 0x180) == 0 && !(FL_BC(l) & 0x200000)) {
        u = UNIT(o);
        STOP_MOVE(u);
    } else if (!(FL_BC(o) & 0x10000)) {
        func_00204D00(o, 1);
        func_00204CD0(o, 0x1008000);
    } else if (*(int *)(UNIT(o) + 0x13C) == 0) {
        func_00204D00(o, 1);
        func_00204CD0(o, 0x1008000);
        S16(o, 0x78) = 100;
    } else if (func_00206C70(o) == 0 && (FL_BC(l) & 0x10000)) {
        u = UNIT(o);
        STOP_MOVE(u);
        func_00204D00(o, 2);
        func_00204CD0(o, 0x1010000);
    } else {
        u = UNIT(o);
        STOP_MOVE(u);
    }
}

/* 0x002B18D0, 0xD0 bytes. A group member's step. */
void func_002B18D0(u8 *o)
{
    u8 *l = LEADER(o);
    char b;

    if (!(FL_BC(o) & 0x10000))
        SET_STATE(o, 0);
    b = l[0x7C];
    if (b == 3 || b == 2)
        func_002B3BF0(o);
    else if (b == 1 || b == 0)
        func_002B1630(o, l);
}

/* 0x002B1BB0, 0x140 bytes. A leader turns toward its target; its group follows the angle (and
 * swaps sides when it has to turn far). */
void func_002B1BB0(u8 *o)
{
    u8 *u, *m;
    float d, a;
    u8 s;

    if ((FL_B8(o) & 0x180) == 0)
        return;
    u = UNIT(o);
    if (!(FL_BC(o) & 0x10000)) {
        if (TARGET(o) == 0)
            return;
        d = func_002B19A0(o);
        a = *(float *)(u + 0x54);
        for (m = NEXT(o); m != 0; m = NEXT(m)) {
            if (!(FL_BC(m) & 0x10000)) {
                u8 *mu = UNIT(m);

                *(float *)(mu + 0x238) = a;
                mu[0x27C] &= 0xFE;
                *(float *)(mu + 0x54) = a;
            }
            if (d > 1.5707964f) {
                s = m[0x7F];
                if (s > 1)
                    s = (s & 1) == 0 ? s + 1 : s - 1;
                m[0x7F] = s;
            }
        }
    } else if ((*(u32 *)(*(u8 **)(u + 0x210) + 0x18) & 1) && *(int *)(u + 0x13C) == 0) {
        func_00204EA0(o);
    }
}

/* 0x002B1F90, 0x10C bytes. A group member's step (archers?). */
void func_002B1F90(u8 *o)
{
    u8 *l = LEADER(o), *u;
    char b;

    if (!(FL_BC(o) & 0x10000)) {
        SET_STATE(o, 0);
        b = l[0x7C];
        if (b == 3 || b == 2)
            func_002B3BF0(o);
        else if (b == 1 || b == 0)
            func_002B1D00(o, l);
    } else if (func_00206C70(o) != 0) {
        u = UNIT(o);
        STOP_MOVE(u);
    }
}

/* 0x002B27A0, 0x4C bytes, matching. */
void func_002B27A0(u8 *o)
{
    if (func_00236F30(o) != 0) {
        func_00204CD0(o, 0x40000);
        FL_BC(o) |= 1;
        func_00206080(o);
    }
}

/* ---- Group members following a mounted leader (+0x0C the horse?). ---- */

void func_002B3360(u8 *o, u8 *l);
void func_002B3740(u8 *o, u8 *l);

#define HORSE_READY(o) (*(u32 *)(*(u8 **)(*(u8 **)(*(u8 **)((o) + 0xC) + 0x14) + 0x210) + 0x18) & 1)

/* 0x002B3740, 0xD8 bytes. */
void func_002B3740(u8 *o, u8 *l)
{
    u8 *u;

    if (!(FL_BC(o) & 0x200000)) {
        if (func_00206C70(o) != 0 || (FL_BC(l) & 0x200000)) {
            u = UNIT(o);
            STOP_MOVE(u);
            FL_BC(o) |= 0x200000;
        }
    } else if (HORSE_READY(o) && HORSE_READY(l)) {
        FL_BC(o) &= 0xFFDEFFFF;
    }
}

/* 0x002B3820, 0x118 bytes. A mounted group member's step. */
void func_002B3820(u8 *o)
{
    u8 *l;
    char b;

    if (*(int *)(o + 0xC) == 0) {
        FL_B8(o) &= 0xFFFF9FFF;
        FL_BC(o) &= 0xFFDEFFFF;
        return;
    }
    l = LEADER(o);
    if (!(FL_BC(o) & 0x10000)) {
        SET_STATE(o, 0);
        b = l[0x7C];
        if (b == 3 || b == 2)
            func_002B3BF0(o);
        else if (b == 1 || b == 0)
            func_002B3360(o, l);
    } else {
        func_002B3740(o, l);
    }
}

/* 0x002B3B00, 0xE8 bytes. Waits a random time (1-20), then moves on. */
void func_002B3B00(u8 *o)
{
    int t;

    if (!(FL_BC(o) & 0x200000)) {
        FL_BC(o) |= 0x200000;
        t = RANDOM() % 0x14 + 1;
        TIMER_SET(o, t);
    } else {
        func_00204D00(o, 1);
        func_00204CD0(o, 0x1008000);
    }
}

/* 0x002B3BF0, 0x34 bytes. Stops. */
void func_002B3BF0(u8 *o)
{
    u8 *u = UNIT(o);

    STOP_MOVE(u);
    FL_BC(o) &= 0xFFDEFFFF;
}

/* 0x002B3C30, 0xC0 bytes. A group member's step (waiting kind). */
void func_002B3C30(u8 *o)
{
    u8 *l = LEADER(o);
    char b;

    SET_STATE(o, 0);
    b = l[0x7C];
    if (b == 3 || b == 2)
        func_002B3BF0(o);
    else if (b == 1 || b == 0)
        func_002B3B00(o);
}
