/*
 * unit_setup.c - setting up battlefield units (original source file unknown; 0x00164680-0x0016CD24,
 * after camera.c, up to Weapon.c at 0x0016CD30).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units (0x630 bytes) are reached by offset as in unit.c:
 * +0x40 position, +0x50 rotation, +0x60 scale, +0x118 state, +0x14E player, +0x290 four motion
 * slots of 0x70, +0x450 ten records of 0x30.
 */

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_002F57F0   /* the original callers here see it this way */
int func_002F57F0(int k);
#endif
#define SW2E_FILE_UNIT_SETUP_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
#include "sw2e_pc.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

typedef u8 Unit;

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)(o) + (off)))->f##n)

float fabsf(float x);
float sqrtf(float x);

extern u32 g_00424B30[10];               /* the ten records' kinds */

void func_00166160(Unit *u);
void func_00165560(Unit *u);
u8 *func_001BE4F0(void);
u8 *func_001BE540(void);
u8 *func_001BE770(void);
void func_001649C0(Unit *u);

/* The matrix of rotation `rot` and position `pos` (VU0 micro subroutine 0x50) into m. */
#ifdef SW2E_PC
#define UNIT_MATRIX(m, rot, pos) sw2e_vu0_matrix((float *)(m), (const float *)(rot), (const float *)(pos))
#else
#define UNIT_MATRIX(m, rot, pos)                                        \
    __asm__ volatile("lqc2 $vf1, 0(%1)\n"                               \
                     "lqc2 $vf2, 0(%2)\n"                               \
                     "vcallms 0x50\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x00(%0)\n"                           \
                     "sqc2 $vf17, 0x10(%0)\n"                           \
                     "sqc2 $vf18, 0x20(%0)\n"                           \
                     "sqc2 $vf19, 0x30(%0)\n"                           \
                     : : "r"(m), "r"(rot), "r"(pos) : "$9", "memory")
#endif

/* 0x00164680, 0x34 bytes, matching. Clears a unit and gives it its defaults. */
void func_00164680(Unit *u)
{
    func_001185E0(u, 0x630, 0);
    func_00150B20(u);
}

/* 0x001646C0, 0x2C4 bytes. Resets a unit for `player`: at the origin, no rotation, scale 1; its
 * matrix (+0, scaled when flag 0x80 of +0x19C is set or +0x1BA > 3 on foot); state 0x40; its
 * counters and links cleared; the four motion slots and the ten records reset. */
void func_001646C0(Unit *u, u8 player)
{
    int i, k;
    u8 *r;

    F32(u, 0x40) = 0.0f;
    F32(u, 0x44) = 0.0f;
    F32(u, 0x48) = 0.0f;
    F32(u, 0x4C) = 1.0f;
    for (k = 0; k < 4; k++)
        F32(u, 0x80 + k * 4) = 0.0f;
    F32(u, 0x90) = 0.0f;
    F32(u, 0x94) = 0.0f;
    F32(u, 0x98) = 0.0f;
    F32(u, 0x9C) = 1.0f;
    F32(u, 0xA0) = 0.0f;
    F32(u, 0xA4) = 0.0f;
    F32(u, 0xA8) = 0.0f;
    F32(u, 0xAC) = 1.0f;
    F32(u, 0xB0) = 0.0f;
    F32(u, 0xB4) = 0.0f;
    F32(u, 0xB8) = 0.0f;
    F32(u, 0xBC) = 1.0f;
    F32(u, 0x60) = 1.0f;
    F32(u, 0x64) = 1.0f;
    F32(u, 0x68) = 1.0f;
    F32(u, 0x6C) = 0.0f;
    if (BIT(u, 0x19C, 7) || (U8(u, 0x1BA) > 3 && S32(u, 0x118) < 0x3C)) {
        float m[4][4], s[4][4];

        UNIT_MATRIX(u, &F32(u, 0x50), &F32(u, 0x40));
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                m[i][k] = F32(u, i * 0x10 + k * 4);
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                s[i][k] = i == k ? (i < 3 ? F32(u, 0x60 + i * 4) : 1.0f) : 0.0f;
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                F32(u, i * 0x10 + k * 4) = m[0][k] * s[i][0] + m[1][k] * s[i][1]
                                           + m[2][k] * s[i][2] + m[3][k] * s[i][3];
    } else {
        UNIT_MATRIX(u, &F32(u, 0x50), &F32(u, 0x40));
    }
    S32(u, 0x118) = 0x40;
    U16(u, 0x12C) = 0;
    U16(u, 0x12E) = 0;
    S32(u, 0x128) = -1;
    U16(u, 0x15E) = 0;
    U8(u, 0x187) = 0;
    U8(u, 0x18A) = 0;
    U8(u, 0x18B) = 0;
    U8(u, 0x157) = 0;
    U16(u, 0x194) = 0;
    U8(u, 0x14D) = 0x80;
    U8(u, 0x185) = 0x17;
    U32(u, 0x120) = 0;
    U32(u, 0x124) = 0;
    U8(u, 0x14C) = 0x40;
    U16(u, 0x188) = 0;
    U16(u, 0x190) = 0;
    U16(u, 0x192) = 0;
    U8(u, 0x1BC) = 0;
    U8(u, 0x1BA) = 7;
    U32(u, 0x19C) = 0;
    U8(u, 0x14E) = player;
    U8(u, 0x14F) = 0;
    BIT(u, 0x198, 0) = 1;
    U16(u, 0x178) = 0xFFFF;
    for (i = 0; i < 4; i++)
        func_0016E2E0(u + 0x290 + i * 0x70);
    r = u + 0x450;
    for (i = 0; i < 10; i++) {
        func_001185E0(r, 0x30, 0);
        U32(r, 0x20) = g_00424B30[i];
        BIT(r, 0x24, 0) = 0;
        r += 0x30;
    }
    func_001649C0(u);
}

/* 0x00164990, 0x2C bytes, matching. Drops a unit's links, then clears it. */
void func_00164990(Unit *u)
{
    func_00166160(u);
    func_00164680(u);
}

/* 0x001649C0, 0xC0 bytes. Turns off the four motion slots (flag 2) and the ten records
 * (flag 1). */
void func_001649C0(Unit *u)
{
    u8 *r = u + 0x450;
    int i;

    BIT(u, 0x2DC, 1) = 0;
    BIT(u, 0x34C, 1) = 0;
    BIT(u, 0x3BC, 1) = 0;
    BIT(u, 0x42C, 1) = 0;
    for (i = 0; i < 10; i += 5) {
        BIT(r, 0x24, 0) = 0;
        BIT(r, 0x54, 0) = 0;
        BIT(r, 0x84, 0) = 0;
        BIT(r, 0xB4, 0) = 0;
        BIT(r, 0xE4, 0) = 0;
        r += 0xF0;
    }
}

/* 0x00164A80, 0x54 bytes, matching. The model actor for state `s`: mounted (0x3C), 0x3D-0x3F,
 * or on foot. */
u8 *func_00164A80(int s)
{
    if (s == 0x3C)
        return func_001BE540();
    else if ((u32)(s - 0x3D) < 3)
        return func_001BE770();
    else
        return func_001BE4F0();
}

/* 0x00164AE0, 0x60 bytes, matching. The same for 0x3C and 0x3D-0x3E; the mounted set otherwise (as in
 * the original). */
u8 *func_00164AE0(int s)
{
    if (s == 0x3C)
        return func_001BE540();
    else if (s == 0x3D || (u32)(s - 0x3D) < 2)
        return func_001BE770();
    else
        return func_001BE540();
}

extern u8 g_006CDF60[][0x150];           /* per unit state: models (+0xA0, +0xD0, variant flag +0xD8) */
extern u32 g_00669DB8;                   /* the game mode */

typedef u8 Actor;
typedef u8 Model;

/* 0x00164B40, 0x244 bytes. Starts the motions of the four slots for set `set` of the unit's
 * kind (+0x158): per slot a motion and a node (-1: none); the set's two modes (+0x13, +0x15)
 * decide the three flags passed for each slot. A slot's object follows the unit's actor. Whether
 * all of them started. In the original, a mode outside its cases keeps the flags of the slot
 * before (undefined for the first). */
int func_00164B40(Unit *u, int set)
{
    u8 *r = func_0016CF30(U8(u, 0x158));
    char *p = (char *)(r + set * 8 + 3);
    u8 *s = u;
    u32 k = 0;
    int a = 0, b = 0, c = 0;

    for (;;) {
        if (p[0] != -1) {
            switch (r[set + 0x13]) {
            case 0:
                a = 1;
                b = 0;
                break;
            case 1:
                a = k != 0;
                b = 0;
                break;
            case 2:
                a = k != 1;
                b = 0;
                break;
            case 3:
                a = !(k == 0 || k == 1);
                b = 0;
                break;
            case 4:
                a = k != 0;
                b = k == 0;
                break;
            case 5:
                a = k != 1;
                b = k == 1;
                break;
            case 6:
                a = !(k == 0 || k == 1);
                b = k == 0 || k == 1;
                break;
            }
            switch ((char)r[set + 0x15]) {
            case 3:
                c = k == 0 || k == 1;
                break;
            case 2:
                c = k == 1;
                break;
            case 1:
                c = k == 0;
                break;
            case 0:
                c = 0;
                break;
            }
            if (func_0016E300(s + 0x290, p[0], p[1], c, b, a) == 0)
                return 0;
            if (BIT(s, 0x2DC, 2)) {
                u8 *o = PTR(s, 0x2D4);

                PTR(o, 0x1FC) = PTR(u, 0x11C);
                U8(o, 0x201) = p[1];
            }
        }
        k++;
        p += 2;
        s += 0x70;
        if ((int)k > 3) {
            func_00150930(u);
            return 1;
        }
    }
}

/* Drops the unit's actor and stops its slots (when its motions could not start). */
static inline int drop_actor(Unit *u)
{
    int k;

    BIT(PTR(u, 0x11C), 0x20C, 0) = 0;
    PTR(u, 0x11C) = 0;
    PTR(u, 0x130) = 0;
    for (k = 0; k < 4; k++) {
        if (BIT(u + k * 0x70, 0x2DC, 0))
            func_0016E910(u + k * 0x70 + 0x290);
    }
    return 0;
}

/* The rest of a unit's model set-up: its weapon model (+0x156, 0x11 = none), its horse (state
 * 0x3C), the transition cleared, the entry pause (+0x12C/+0x12E: 5 or 0x10 frames). */
static inline void setup_rest(Unit *u, int keep, int dispatch)
{
    u8 c;

    if (U8(u, 0x156) < 0x11) {
        u8 *w = (u8 *)PS2_PTR(func_002A7E70());

        PTR(u, 0x134) = w;
        if (w != 0) {
            BIT(w, 0x168, 0) = 1;
            U8(PTR(u, 0x134), 0x165) = 9;
            func_0014FCA0(PTR(u, 0x134), (void *)PS2_PTR(func_002A7E30(U8(u, 0x156))));
        } else {
            U8(u, 0x156) = 0x11;
        }
    }
    if (S32(u, 0x118) == 0x3C)
        func_002AD760(U8(u, 0x180), (unsigned char **)(u + 0x1A0));
    U32(u, 0x16C) = 0;
    U32(u, 0x1B4) = 0;
    if (0.0f < F32(PTR(u, 0x11C), 0x214)) {
        F32(PTR(u, 0x11C), 0x210) = 0.0f;
        F32(PTR(u, 0x11C), 0x214) = 0.0f;
    }
    U8(u, 0x181) = 0;
    if (dispatch && g_00669DB8 != 4 && g_00669DB8 != 2)
        func_00240B30(u);
    c = U8(u, 0x19C);
    if ((c & 4) == 0 && keep == 0 && (U32(PTR(u, 0x210), 0x18) & 0x40020) == 0) {
        U8(u, 0x19C) = (c & ~8) | 8;
        U8(u, 0x19C) = (c & ~0xC) | 8;
        U16(u, 0x12C) = 0;
        U16(u, 0x12E) = (U8(u, 0x1BB) < 5 && 5 < U32(u, 0x138)) ? 5 : 0x10;
        U8(u, 0x14D) = 0;
    }
    func_00149720(PTR(u, 0x11C));
    U8(u, 0x1BB) = 0;
    BIT(u, 0x198, 4) = 1;
}

/* 0x00164DA0, 0x3D8 bytes. Gives a unit its model actor for its state (+0x118), the state's
 * model (and its variant's), its slots' motions, weapon and horse; `keep`: no entry pause.
 * Whether it worked. */
int func_00164DA0(Unit *u, int keep)
{
    u8 *t = g_006CDF60[S32(u, 0x118)];

    if (U32(t, 0xD8) == 0)
        PTR(u, 0x11C) = func_00164A80(S32(u, 0x118));
    else
        PTR(u, 0x11C) = func_00164AE0(S32(u, 0x118));
    if (PTR(u, 0x11C) == 0)
        return 0;
    BIT(PTR(u, 0x11C), 0x20C, 0) = 1;
    PTR(PTR(u, 0x11C), 0x208) = 0;
    BIT(PTR(u, 0x11C), 0x20C, 2) = 1;
    if (U32(t, 0xD8) == 0) {
        func_00149620(PTR(u, 0x11C), t + 0xA0, 0);
    } else {
        u8 *a = PTR(u, 0x11C);

        if (PTR(a, 0x1F4) == 0) {
            BIT(a, 0x20C, 0) = 0;
            PTR(u, 0x11C) = 0;
            return 0;
        }
        func_00149620(a, t + 0xA0, t + 0xD0);
    }
    PTR(u, 0x130) = t;
    if (U8(u, 0x158) < 0x8D) {
        if (func_00164B40(u, 0) == 0)
            return drop_actor(u);
        BIT(u, 0x19D, 0) = 0;
    }
    setup_rest(u, keep, 1);
    return 1;
}

/* 0x00165180, 0x3DC bytes. The same with the model of state +0x118 + `add` (the variant's
 * second model still from the unit's own state), without func_00240B30. */
int func_00165180(Unit *u, int keep, int add)
{
    u8 *t = g_006CDF60[S32(u, 0x118)];
    u8 *t2 = g_006CDF60[S32(u, 0x118) + add];

    if (U32(t, 0xD8) == 0)
        PTR(u, 0x11C) = func_00164A80(S32(u, 0x118));
    else
        PTR(u, 0x11C) = func_00164AE0(S32(u, 0x118));
    if (PTR(u, 0x11C) == 0)
        return 0;
    BIT(PTR(u, 0x11C), 0x20C, 0) = 1;
    PTR(PTR(u, 0x11C), 0x208) = 0;
    BIT(PTR(u, 0x11C), 0x20C, 2) = 1;
    if (U32(t, 0xD8) == 0) {
        func_00149620(PTR(u, 0x11C), t2 + 0xA0, 0);
    } else {
        u8 *a = PTR(u, 0x11C);

        if (PTR(a, 0x1F4) == 0) {
            BIT(a, 0x20C, 0) = 0;
            PTR(u, 0x11C) = 0;
            return 0;
        }
        func_00149620(a, t2 + 0xA0, t + 0xD0);
    }
    PTR(u, 0x130) = t2;
    if (U8(u, 0x158) < 0x8D) {
        if (func_00164B40(u, 0) == 0)
            return drop_actor(u);
        BIT(u, 0x19D, 0) = 0;
    }
    setup_rest(u, keep, 0);
    return 1;
}

/* The state records really start 0x10 bytes before g_006CDF60 (+4: the state's model, 0 = none). */
#define STATE_REC(s) (g_006CDF60[s] - 0x10)

extern u8 g_00693970[];                 /* the game state: the officers at +0x100C0 */
extern u8 g_005B50A0[][0xD0];            /* the unit descriptions (+0x10 flag 1: usable, +0x1C weapon kind) */
extern u8 g_006A3A30[][0xC0];            /* the officers (+0x10 record, +0x82 life, +0xB8 flags) */
#ifdef SW2E_PC
extern ps2ptr g_0045D300_a;                   /* (small data) the state descriptions (0xA0 each) */
#define g_0045D300 ((u8 *)PS2_PTR(g_0045D300_a))
#define g_0045D300_SET(v) (g_0045D300_a = PS2_ADDR(v))
#else
extern u8 *g_0045D300;
#define g_0045D300_a (*(ps2ptr *)&g_0045D300)
#define g_0045D300_SET(v) (g_0045D300 = (v))
#endif
extern float g_004064D0[4][4];           /* the unit colours by player (the first: the default) */
extern float g_00406510[4][4], g_00406550[4][4], g_00406590[4][4];  /* states 0x2E, 0x31, 0x32 */

void func_0016BD30(Unit *u);

/* 0x00165560, 0x17C bytes. Takes a unit's model away: the actor, the partner (+0x270), the
 * grab (+0x280), the slots, the weapon model, the records and the horse. */
void func_00165560(Unit *u)
{
    u8 *a = PTR(u, 0x11C), *v;
    int k;

    PTR(a, 0x1FC) = 0;
    U8(a, 0x201) = 0;
    BIT(PTR(u, 0x11C), 0x20C, 0) = 0;
    PTR(PTR(u, 0x11C), 0x1E8) = 0;
    PTR(u, 0x11C) = 0;
    v = PTR(u, 0x270);
    if (v != 0) {
        PTR(u, 0x270) = 0;
        PTR(v, 0x270) = 0;
    }
    v = PTR(u, 0x280);
    if (v != 0) {
        func_0016BD30(u);
        func_00150A10(v);
        func_00150A10(u);
    }
    BIT(u, 0x19D, 0) = 0;
    for (k = 0; k < 4; k++) {
        if (BIT(u + k * 0x70, 0x2DC, 0))
            func_0016E910(u + k * 0x70 + 0x290);
    }
    PTR(u, 0x130) = 0;
    if (PTR(u, 0x134) != 0) {
        func_0014FCA0(PTR(u, 0x134), 0);
        BIT(PTR(u, 0x134), 0x168, 0) = 0;
        PTR(u, 0x134) = 0;
    }
    func_001649C0(u);
    func_002AD8B0((unsigned char **)(u + 0x1A0));
    U32(u, 0x16C) = 0;
    BIT(u, 0x19E, 5) = 0;
    U32(u, 0x1B4) = 0;
    if (g_00669DB8 != 4 && g_00669DB8 != 2)
        func_002406D0(U8(u, 0x14E));
}

/* The common part of setting a unit up: its fields cleared, its mount kind (+0x155: 1 horse, 2
 * states 0x3D-0x3F), the officer's level (+0x1BA, at most 3; 7 = none), the extra life of kind
 * ':' (+0x1B8, `life8`: an eighth of the officer's, else scaled by func_003E6EC0), the colour
 * (+0x60: by player for a set state with `coloured`). */
static inline void unit_init(Unit *u, int state, u8 slot_kind, u8 weapon, u8 b154, u8 b14f,
                             int coloured, int life8)
{
    u8 *o;
    float *c;

    func_00150B20(u);
    U8(u, 0x156) = weapon;
    U8(u, 0x154) = b154;
    U8(u, 0x14F) = b14f;
    BIT(u, 0x198, 1) = 1;
    BIT(u, 0x19C, 4) = 1;
    if (state == 0x3C)
        U8(u, 0x155) = 1;
    else if ((u32)(state - 0x3D) < 3)
        U8(u, 0x155) = 2;
    else
        U8(u, 0x155) = 0;
    U8(u, 0x158) = slot_kind;
    U32(u, 0x138) = 0;
    U8(u, 0x17D) = 0;
    U16(u, 0x15C) = 0;
    U16(u, 0x172) = 0;
    U16(u, 0x174) = 0;
    U16(u, 0x170) = 0;
    U16(u, 0x176) = 0;
    U8(u, 0x17F) = 0;
    U8(u, 0x17E) = 0;
    U32(u, 0x16C) = 0;
    U16(u, 0x12C) = 0;
    U16(u, 0x12E) = 0;
    S32(u, 0x128) = -1;
    U16(u, 0x15E) = 0;
    U8(u, 0x187) = 0;
    U8(u, 0x18A) = 0;
    U8(u, 0x18B) = 0;
    U8(u, 0x157) = 0;
    U16(u, 0x194) = 0;
    U8(u, 0x185) = 0x17;
    U8(u, 0x14D) = 0x80;
    U32(u, 0x120) = 0;
    U32(u, 0x124) = 0;
    U8(u, 0x14C) = 0x40;
    U16(u, 0x188) = 0;
    U16(u, 0x190) = 0;
    U16(u, 0x192) = 0;
    U8(u, 0x1BC) = 0;
    U8(u, 0x1BB) = 0;
    U32(u, 0x1B4) = 0;
    BIT(u, 0x198, 5) = 0;
    U16(u, 0x1CC) = 0xFFFF;
    U16(u, 0x1CE) = 0xFFFF;
    o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    if (o == 0 || (U32(o, 0xB8) & 0x200) == 0) {
        U8(u, 0x1BA) = 7;
    } else if (PTR(o, 0x10) != 0) {
        U8(u, 0x1BA) = U8(PTR(o, 0x10), 0x7C);
        U8(u, 0x1BA) = U8(u, 0x1BA) < 3 ? U8(u, 0x1BA) : 3;
    } else {
        U8(u, 0x1BA) = 7;
    }
    if (U8(PTR(u, 0x110), 0x1C) == ':') {
        if (life8)
            S16(u, 0x1B8) = S16(o, 0x82) / 8;
        else
            S16(u, 0x1B8) = (short)(int)((float)(int)S16(o, 0x82) * func_003E6EC0(o));
    } else {
        S16(u, 0x1B8) = 0;
    }
    U32(u, 0x19C) = 0;
    if (U8(u, 0x1BA) < 4 || S32(u, 0x118) > 0x3B || coloured == 0)
        c = g_004064D0[0];
    else if (state == 0x2E)
        c = g_00406510[U8(u, 0x14E) & 3];
    else if (state == 0x31)
        c = g_00406550[U8(u, 0x14E) & 3];
    else if (state == 0x32)
        c = g_00406590[U8(u, 0x14E) & 3];
    else
        c = g_004064D0[U8(u, 0x14E) & 3];
    F32(u, 0x60) = c[0];
    F32(u, 0x64) = c[1];
    F32(u, 0x68) = c[2];
    F32(u, 0x6C) = c[3];
    if (S32(u, 0x118) != 0x3C)
        U8(u, 0x180) = 0x10;
    if ((u32)(S32(u, 0x118) - 0x3D) < 3)
        func_001F5370(u);
}

/* 0x001656E0, 0x578 bytes. Sets a unit up in `state` with description `kind`: a state without
 * a model falls back to the first one that has one (0x22-0x37, then 0-0x20; not for
 * 0x3D-0x3F); an unusable description becomes 0x26 or 0x24 (slot kind 0x6F). Returns 1. */
int func_001656E0(Unit *u, int state, int kind, u8 slot_kind, u8 weapon, u8 b154, u8 b14f,
                  int coloured)
{
    S32(u, 0x118) = state;
    if (PTR(STATE_REC(state), 4) == 0) {
        if (state != 0x3D && state != 0x3E && state != 0x3F) {
            int s = state, k;

            for (k = 0x22; k < 0x38; k++) {
                if (PTR(STATE_REC(k), 4) != 0) {
                    s = k;
                    break;
                }
            }
            state = s;
            if (PTR(STATE_REC(s), 4) == 0) {
                for (k = 0; k < 0x21; k++) {
                    if (PTR(STATE_REC(k), 4) != 0) {
                        state = k;
                        break;
                    }
                }
            }
        }
        S32(u, 0x118) = state;
    }
    if ((g_005B50A0[kind][0x10] & 1) == 0) {
        kind = (g_005B50A0[0x26][0x10] & 1) ? 0x26 : 0x24;
        slot_kind = 0x6F;
    }
    PTR(u, 0x114) = g_0045D300 + state * 0xA0;
    PTR(u, 0x110) = g_005B50A0[kind];
    unit_init(u, state, slot_kind, weapon, b154, b14f, coloured, 0);
    return 1;
}

/* 0x00165C60, 0x41C bytes. The same without the fallbacks; the extra life is an eighth of the
 * officer's. */
int func_00165C60(Unit *u, int state, int kind, u32 slot_kind, u32 weapon, u32 b154, u32 b14f,
                  int coloured)
{
    S32(u, 0x118) = state;
    PTR(u, 0x114) = g_0045D300 + state * 0xA0;
    PTR(u, 0x110) = g_005B50A0[kind];
    unit_init(u, state, slot_kind, weapon, b154, b14f, coloured, 1);
    return 1;
}

/* 0x00166080, 0x38 bytes, matching. Sets a unit up as a horse (state 0x3C, description 0x36) of kind
 * `horse`. */
void func_00166080(Unit *u, u8 b154, u8 horse)
{
    U8(u, 0x180) = horse;
    func_001656E0(u, 0x3C, 0x36, 0x8D, 0x11, b154, 0, 0);
}

/* 0x001660C0, 0x98 bytes. Places a unit at `pos`, on the ground (the probe at +0xD0) unless
 * flag 0x40 of +0x19E is set; its offsets cleared and its kept positions set. */
void func_001660C0(Unit *u, float *pos)
{
    int k;

    for (k = 0; k < 4; k++)
        F32(u, 0x40 + k * 4) = pos[k];
    PTR(u, 0xD0) = u + 0x40;
    func_001F2BF0(u + 0xD0);
    if (BIT(u, 0x19E, 6) == 0)
        F32(u, 0x44) = F32(u, 0xE0);
    for (k = 0; k < 4; k++)
        F32(u, 0x80 + k * 4) = 0.0f;
    for (k = 0; k < 4; k++)
        F32(u, 0x90 + k * 4) = F32(u, 0x40 + k * 4) + F32(u, 0x80 + k * 4);
    for (k = 0; k < 4; k++)
        F32(u, 0xB0 + k * 4) = F32(u, 0x90 + k * 4);
    for (k = 0; k < 4; k++)
        F32(u, 0xA0 + k * 4) = F32(u, 0x40 + k * 4);
}

extern u8 g_005ADD80[0x40][0xC0];        /* 64 effect records (+0x88 owner, +0x8C flag 1: on) */
#define g_700000C0 ((float *)PS2_PTR(0x700000C0))  /* (scratchpad) a zero vector */

int func_0016C070(Unit *u);
void func_002A5B10(void);
void func_0016C620(Unit *u);
int func_0016C470(float amount, Unit *u);

/* 0x00166160, 0x3B0 bytes. Takes a unit off the field: its mount links (states 0x3D-0x3F), its
 * hold and grabs, the effects it owns; with flag 2 of +0x198 its model too, and it becomes an
 * empty unit (state 0x40, no description). */
void func_00166160(Unit *u)
{
    u8 *a, *b;
    int k;

    if ((u32)(S32(u, 0x118) - 0x3D) < 3) {
        if (func_0016C070(u) != 0 && PTR(u, 0x11C) != 0)
            func_001F54B0(u);
        else
            func_001F5420(u);
    }
    if (BIT(u, 0x19C, 1))
        func_00151A90(u, 1);
    if (BIT(u, 0x27C, 2))
        func_0015FB70(u);
    a = PTR(u, 0x280);
    b = PTR(u, 0x284);
    if (a != 0) {
        func_0016BD30(u);
        func_00150A10(a);
        func_00150A10(u);
    }
    if (b != 0) {
        func_0016BD30(b);
        func_00150A10(b);
        func_00150A10(u);
    }
    U32(u, 0x13C) = 0;
    for (k = 0; k < 4; k++)
        F32(u, 0x1D0 + k * 4) = g_700000C0[k];
    func_00150BB0(u);
    for (k = 0; k < 0x40; k++) {
        if ((g_005ADD80[k][0x8C] & 1) && PTR(g_005ADD80[k], 0x88) == u)
            func_001AE090(g_005ADD80[k]);
    }
    if (BIT(u, 0x198, 1) == 0)
        return;
    if (PTR(u, 0x11C) != 0)
        func_00165560(u);
    if (g_00669DB8 != 4 && g_00669DB8 != 2)
        func_00253800(u);
    if (BIT(u, 0x19C, 1)) {
        func_00151A90(u, 1);
        BIT(u, 0x19C, 1) = 0;
    }
    PTR(u, 0x114) = 0;
    PTR(u, 0x110) = 0;
    S32(u, 0x118) = 0x40;
    U8(u, 0x156) = 0x11;
    U8(u, 0x154) = 3;
    U8(u, 0x14F) = 0xFF;
    BIT(u, 0x198, 1) = 0;
    BIT(u, 0x19E, 5) = 0;
    U8(u, 0x155) = 4;
    U8(u, 0x158) = 0x8D;
    U32(u, 0x138) = 0;
    U8(u, 0x17D) = 0;
    U16(u, 0x15C) = 0;
    U16(u, 0x172) = 0;
    U16(u, 0x174) = 0;
    U16(u, 0x170) = 0;
    U16(u, 0x176) = 0;
    U8(u, 0x17F) = 0;
    U8(u, 0x17E) = 0;
    U32(u, 0x16C) = 0;
    U8(u, 0x180) = 0x10;
    U16(u, 0x15E) = 0;
    U8(u, 0x187) = 0;
    U8(u, 0x18A) = 0;
    U8(u, 0x18B) = 0;
    U8(u, 0x157) = 0;
    U16(u, 0x194) = 0;
    U32(u, 0x120) = 0;
    U32(u, 0x124) = 0;
    U16(u, 0x188) = 0;
    U16(u, 0x190) = 0;
    U16(u, 0x192) = 0;
    U8(u, 0x1BC) = 0;
    U8(u, 0x1BA) = 7;
    U32(u, 0x1B4) = 0;
    U16(u, 0x1B8) = 0;
    BIT(u, 0x198, 5) = 0;
    U16(u, 0x1CC) = 0xFFFF;
    U16(u, 0x1CE) = 0xFFFF;
    U32(u, 0x19C) = 0;
    if (S32(u, 0x128) != -1) {
        func_002A5B10();
        S32(u, 0x128) = -1;
    }
    func_001649C0(u);
}

/* Ends the unit's appearing / leaving (flags 8 and 4 of +0x19C, timer +0x12C of +0x12E). */
static inline void end_fade(Unit *u)
{
    u8 c = U8(u, 0x19C);

    U8(u, 0x19C) = c & ~8;
    U8(u, 0x19C) = c & ~0xC;
    U16(u, 0x12C) = 0;
    U16(u, 0x12E) = 0;
}

/* 0x00166510, 0x4E8 bytes. A unit's bookkeeping each frame (`dt`, at least one frame counted):
 * an officer under a quarter of its life (at most 50) heals 1 every 8 frames; timers; leaving
 * (flag 4: the timer runs out, then the model is taken away, or func_001CEBC0 for a beaten
 * unit); appearing (flag 8: the timer runs up); the fade (+0x14D, 0-0x80) from them; the frame
 * count +0x138. */
void func_00166510(float dt, Unit *u)
{
    short n = (short)(int)(1.0f < dt ? dt : 1.0f);
    float f;

    func_0016C620(u);
    if (BIT(u, 0x19C, 1) == 0) {
        u8 *o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
        int lim = S16(o, 0x80) / 4;

        if (lim >= 0x32)
            lim = 0x32;
        if (S16(o, 0x82) < lim && (U32(u, 0x138) & 7) == 0)
            func_0016C470(1.0f, u);
    }
    if (U32(PTR(u, 0x210), 0x18) & 0x2014)
        U8(u, 0x17D) = 0;
    if (PTR(u, 0x144) != 0 && U8(PTR(u, 0x144), 0x17D) == 0)
        PTR(u, 0x144) = 0;
    func_0029F930(dt, u);
    if (n < U16(u, 0x176))
        U16(u, 0x176) = U16(u, 0x176) - n;
    else
        U16(u, 0x176) = 0;
    if (BIT(u, 0x19C, 2)) {
        if (S16(u, 0x12C) != 0) {
            short s = S16(u, 0x12C) - n;

            S16(u, 0x12C) = s < 1 ? 0 : s;
        } else if (func_0016C070(u) == 0) {
            if (PTR(u, 0x11C) != 0) {
                end_fade(u);
                func_00165560(u);
            }
        } else {
            end_fade(u);
            func_001CEBC0(u);
        }
    }
    if (S16(u, 0x12E) == 0) {
        if (BIT(u, 0x19C, 7) == 0)
            U8(u, 0x14D) = 0x80;
    } else {
        if (BIT(u, 0x19C, 2) && func_0016C070(u) != 0) {
            f = (float)U16(u, 0x12C) * 128.0f / ((float)U16(u, 0x12E) - 16.0f);
            if (128.0f <= f)
                f = 128.0f;
        } else {
            f = (float)U16(u, 0x12C) * 128.0f / (float)U16(u, 0x12E);
        }
        U8(u, 0x14D) = (int)f < 0x80 ? (u8)(int)f : 0x80;
    }
    if (BIT(u, 0x19C, 3) && PTR(u, 0x11C) != 0) {
        if (U16(u, 0x12C) < U16(u, 0x12E))
            U16(u, 0x12C) += 1;
        if (S16(u, 0x12E) == S16(u, 0x12C))
            end_fade(u);
    }
    U32(u, 0x138) += 1;
    BIT(u, 0x19C, 0) = 1;
    BIT(u, 0x19F, 5) = 0;
}

#ifdef SW2E_PC
extern ps2ptr g_005B5040_a;                  /* (small data) the face motion: header +4 tracks, +0xC the tracks */
#define g_005B5040 ((u32 *)PS2_PTR(g_005B5040_a))
#define g_005B5040_SET(v) (g_005B5040_a = PS2_ADDR(v))
#else
extern u32 *g_005B5040;
#define g_005B5040_a (*(ps2ptr *)&g_005B5040)
#define g_005B5040_SET(v) (g_005B5040 = (v))
#endif
extern u8 g_005B5078[][0xD0];            /* weapon kinds (+0: the kind's motions, +0x50 the mounted ones) */
#ifdef SW2E_PC
extern ps2ptr g_005BA688_a;                   /* (small data) the shared motions */
#define g_005BA688 ((u8 *)PS2_PTR(g_005BA688_a))
#define g_005BA688_SET(v) (g_005BA688_a = PS2_ADDR(v))
#else
extern u8 *g_005BA688;
#define g_005BA688_a (*(ps2ptr *)&g_005BA688)
#define g_005BA688_SET(v) (g_005BA688 = (v))
#endif
extern int g_0045D2C8;                   /* (small data) the side in the duel view */

float *func_0016A170(Unit *u, int node);

/* A track's value at time 0 (`p` on its first key; keys are (end frame, a, b, c, d)). */
static inline float track_at_zero(const float *p, u32 size)
{
    const float *k = p;
    float prev = 0.0f, s;

    if (size == 0)
        return 0.0f;
    if (size == 1)
        return *p;
    while (!(0.0f < *k)) {
        prev = *k;
        k += size;
    }
    s = (0.0f - prev) / (*k - prev);
    return k[4] + s * k[3] + k[1] * s * s * s + k[2] * s * s + 0.0f + 0.0f;
}

/* The motion record of action `act` (its weapon kind's, the mounted set's, or the shared one). */
static inline u8 *act_motion(Unit *u, u8 *act)
{
    u8 *d = PTR(u, 0x110);
    u8 *a = PTR(d, 8) + U16(act, 0) * 0x20;

    if (U32(a, 0x1C) & 0x40000000)
        return g_005BA688 + U16(a, 2) * 0x20;
    if ((U32(a, 0x1C) & 0x80000000) == 0)
        return PTR(g_005B5078[U8(d, 0x1C)], 0) + U16(a, 2) * 0x20;
    return PTR(g_005B5078[U8(d, 0x1C)], 0x50) + U16(a, 2) * 0x20;
}

/* Whether the unit's motion is played this frame: not for the duel view's resting side. */
static inline int plays_motion(Unit *u)
{
    if (S32(u, 0x118) == 0x3C)
        return 1;
    if ((U8(u, 0x14E) & 1) == (g_0045D2C8 & 1) && U8(u, 0x181) > 1
        && (U32(PTR(u, 0x210), 0x18) & 0x20101))
        return 0;
    return 1;
}

/* The actor's root node (the variant's when it has one). */
static inline float *root_node(u8 *a)
{
    if (BIT(a, 0x20C, 1) && PTR(a, 0x1F4) != 0)
        return (float *)PTR(a, 0x1F4);
    return (float *)PTR(a, 0x1F0);
}

/* The rotation matrix of the unit's rotation +0x50 (VU0 micro subroutine 0x40) into m. */
#ifdef SW2E_PC
#define ROT_MATRIX(m, rot) sw2e_vu0_rotation((float *)(m), (const float *)(rot))
#else
#define ROT_MATRIX(m, rot)                                              \
    __asm__ volatile("lqc2 $vf1, 0(%1)\n"                               \
                     "vcallms 0x40\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x00(%0)\n"                           \
                     "sqc2 $vf17, 0x10(%0)\n"                           \
                     "sqc2 $vf18, 0x20(%0)\n"                           \
                     "sqc2 $vf19, 0x30(%0)\n"                           \
                     : : "r"(m), "r"(rot) : "$9", "memory")
#endif

/* The motion's root offset turned with the unit (by the scratchpad matrix at 0x70000080). */
static inline void root_offset(Unit *u)
{
    float r[4][4], m[4][4], *n = (float *)PTR(PTR(u, 0x11C), 0x208), *s = (float *)PS2_PTR(0x70000080);
    int i, k;

    ROT_MATRIX(r, &F32(u, 0x50));
    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i][k] = r[0][k] * s[i * 4] + r[1][k] * s[i * 4 + 1] + r[2][k] * s[i * 4 + 2]
                      + r[3][k] * s[i * 4 + 3];
    for (k = 0; k < 4; k++)
        F32(u, 0x80 + k * 4) = m[0][k] * n[0] + m[1][k] * n[1] + m[2][k] * n[2] + m[3][k] * n[3];
    F32(u, 0x8C) = 0.0f;
    for (k = 0; k < 4; k++)
        F32(u, 0x90 + k * 4) = F32(u, 0x40 + k * 4) + F32(u, 0x80 + k * 4);
}

/* 0x00166A00, 0xD2C bytes. Poses a unit's model this frame: the face (nodes 0x1A-0x2E from the
 * face motion at time 0, for models with more than 0x1A nodes); the action's motion and the
 * extra one (+0x250); the expression (+0x1B4, three parts); the root held in place (flag 0x80
 * of +0x19C with +0x15A = 3, flag 0x80 of +0x19F, modes 2 and 4); the root's height scaled to
 * the state's height (+0x114 +0x80) against the height the motion was made for; a turn of the
 * head node (+0x240); the transition and the matrices; the root offset turned with the unit,
 * or, for a rider, taken from its mount's node +0x274. */
void func_00166A00(Unit *u)
{
    u32 *fm = g_005B5040;
    int still = (U8(u, 0x19C) & 0x80) && U8(u, 0x15A) == 3;
    u8 *a, *act;
    float *r, h;

    if (U8(PTR(PTR(u, 0x11C), 0x1E8), 0x29) > 0x1A) {
        u8 *nodes = PTR(PTR(u, 0x11C), 0x1F0);
        const float *p = (const float *)(fm + 3);
        u32 i;

        for (i = 0; i < fm[1]; i++) {
            u32 w = *(const u32 *)p++;
            u32 node = w & 0xFF, size = w >> 13 & 7;

            if (node > 0x19 && node < 0x2F) {
                float v = track_at_zero(p, size);
                float *n = (float *)(nodes + node * 0x70);

                U8(n, 0x68) = 1;
                switch (w >> 8 & 0x1F) {
                case 0:
                    n[4] = v;
                    break;
                case 1:
                    n[5] = v;
                    break;
                case 2:
                    n[6] = v;
                    break;
                case 3:
                    n[0] = v;
                    break;
                case 4:
                    n[1] = v;
                    break;
                case 5:
                    n[2] = v;
                    break;
                }
            }
            p += size * (w >> 18);
        }
    }
    if (plays_motion(u))
        func_0014D9A0(F32(u, 0x21C), PTR(u, 0x11C), act_motion(u, PTR(u, 0x210)));
    if (PTR(u, 0x250) != 0) {
        u8 *m = act_motion(u, PTR(u, 0x250));
        u8 *b = PTR(u, 0x11C);
        u8 *mdl = (U8(b, 0x20C) & 2) ? PTR(b, 0x1EC) : PTR(b, 0x1E8);

        func_0014D7E0(F32(u, 0x254), PTR(u, 0x11C), m, 8, U16(mdl, 0x24));
    }
    if (PTR(u, 0x1B4) != 0) {
        u8 *rec = g_006CDF60[S32(u, 0x118)] + 0x100;

        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, (void *)PTR(u, 0x1B4), 0);
        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, (void *)PTR(u, 0x1B4), 1);
        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, (void *)PTR(u, 0x1B4), 2);
        PTR(u, 0x1B4) = 0;
    }
    if (still) {
        r = root_node(PTR(u, 0x11C));
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = 0.0f;
        r[3] = 1.0f;
    } else if (BIT(u, 0x19F, 7)) {
        r = root_node(PTR(u, 0x11C));
        r[0] = 0.0f;
        r[2] = 0.0f;
    }
    if (g_00669DB8 == 4 || g_00669DB8 == 2) {
        r = root_node(PTR(u, 0x11C));
        r[0] = 0.0f;
        r[2] = 0.0f;
        r[3] = 1.0f;
    }
    a = PTR(u, 0x11C);
    act = PTR(u, 0x210);
    if (a != 0) {
        r = root_node(a);
        h = F32(PTR(u, 0x114), 0x80);
        if ((U32(act, 0x1C) & 0x40000000) == 0) {
            int s = S32(u, 0x118);

            if (s == 0x30 || s == 0x38 || s == 0x37 || s == 0x36 || s == 0x35 || s == 0x34
                || s == 0x33 || s == 0x21 || s == 0x20 || s == 0x1F || s == 0x1E || s == 0x1D
                || s == 0x1C) {
                u8 k = U8(PTR(u, 0x110), 0x1C);

                if (k < 0x1A)
                    r[1] = r[1] * (h / F32(g_0045D300 + k * 0xA0, 0x80));
                else if ((k >= 0x3E && k <= 0x48) || (k >= 0x49 && k <= 0x53)
                         || (k >= 0x54 && k <= 0x5C))
                    r[1] = r[1] * (h / 114.2966f);
                else if (k > 0x5C && k < 0x68)
                    r[1] = r[1] * (h / 107.5364f);
            } else if (s == 0x1A) {
                u32 f = U32(act, 0x1C);
                int d;

                if (f & 0x80)
                    d = 3;
                else if (f & 0x100)
                    d = 0x12;
                else if (f & 0x200)
                    d = 9;
                else if (f & 0x800)
                    d = 0x13;
                else if (f & 0x4000)
                    d = 0xC;
                else if (f & 0x10000)
                    d = 2;
                else if (f & 0x20000000)
                    d = 1;
                else
                    d = 4;
                r[1] = r[1] * (h / F32(g_0045D300 + d * 0xA0, 0x80));
            } else if (s == 0x1B) {
                u32 f = U32(act, 0x1C);
                int d = (f & 4) ? 0 : (f & 0x100000) ? 0x14 : 1;

                r[1] = r[1] * (h / F32(g_0045D300 + d * 0xA0, 0x80));
            }
        } else {
            r[1] = r[1] * (h / 117.468f);
        }
        if ((U32(act, 0x18) & 0x40020) == 0 && r[1] < h * -1.0f)
            r[1] = h * -1.0f;
    }
    if (U32(PTR(u, 0x210), 0x18) & 0x80000000) {
        u8 *n = PTR(PTR(u, 0x11C), 0x208);
        float y = F32(n, 0x398) + F32(u, 0x240);

        if (3.1415927f < y)
            y -= 6.2831855f;
        else if (y <= -3.1415927f)
            y += 6.2831855f;
        F32(n, 0x398) = y;
    }
    if (0.0f < F32(PTR(u, 0x11C), 0x214))
        func_0014E380(PTR(u, 0x11C));
    if (plays_motion(u))
        func_0014D6C0(PTR(u, 0x11C));
    if (still) {
        u8 *n = PTR(PTR(u, 0x11C), 0x208);

        func_00118850(n + 0x170, 0x40);
        F32(n, 0x1AC) = 1.0f;
        n = PTR(PTR(u, 0x11C), 0x208);
        func_00118850(n + 0x100, 0x40);
        F32(n, 0x13C) = 1.0f;
    }
    {
        u8 *m = PTR(u, 0x288);
        int k;

        if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0 || m == 0 || PTR(m, 0x11C) == 0) {
            root_offset(u);
        } else {
            float *n = (float *)PTR(PTR(u, 0x11C), 0x208);

            for (k = 0; k < 4; k++)
                F32(u, 0x80 + k * 4) = n[k];
            F32(u, 0x8C) = 0.0f;
            if (U32(PTR(m, 0x11C), 0x204) < 3) {
                root_offset(u);
                F32(u, 0x94) = F32(u, 0x94) - F32(PTR(m, 0x114), 0x80);
            } else {
                float *mm = func_0016A170(m, U8(u, 0x274)), v[4];

                F32(u, 0x8C) = 1.0f;
                for (k = 0; k < 4; k++)
                    v[k] = F32(u, 0x80 + k * 4);
                for (k = 0; k < 4; k++)
                    F32(u, 0x90 + k * 4) = mm[k] * v[0] + mm[4 + k] * v[1] + mm[8 + k] * v[2]
                                           + mm[12 + k] * v[3];
            }
        }
    }
}

/* A track's value at frame `t` (`p` on its first key). */
static inline float track_at(const float *p, u32 size, float t)
{
    const float *k = p;
    float prev = 0.0f, s;

    if (size == 0)
        return 0.0f;
    if (size == 1)
        return *p;
    while (!(t < *k)) {
        prev = *k;
        k += size;
    }
    s = (t - prev) / (*k - prev);
    return k[4] + s * k[3] + k[1] * s * s * s + k[2] * s * s;
}

/* Turns the offset +0x80 with the unit (rotation +0x50 by the scratchpad matrix at 0x70000080). */
static inline void turn_offset(Unit *u)
{
    float r[4][4], m[4][4], v[4], *s = (float *)PS2_PTR(0x70000080);
    int i, k;

    ROT_MATRIX(r, &F32(u, 0x50));
    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i][k] = r[0][k] * s[i * 4] + r[1][k] * s[i * 4 + 1] + r[2][k] * s[i * 4 + 2]
                      + r[3][k] * s[i * 4 + 3];
    for (k = 0; k < 4; k++)
        v[k] = F32(u, 0x80 + k * 4);
    for (k = 0; k < 4; k++)
        F32(u, 0x80 + k * 4) = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2] + m[3][k] * v[3];
    F32(u, 0x8C) = 0.0f;
}

/* The root's height (*y) scaled from the height the motion was made for to the state's. */
static inline void scale_root(Unit *u, u8 *act, float *y)
{
    float h = F32(PTR(u, 0x114), 0x80);
    int s = S32(u, 0x118);

    if (U32(act, 0x1C) & 0x40000000) {
        *y = *y * (h / 117.468f);
    } else if (s == 0x30 || s == 0x38 || s == 0x37 || s == 0x36 || s == 0x35 || s == 0x34
               || s == 0x33 || s == 0x21 || s == 0x20 || s == 0x1F || s == 0x1E || s == 0x1D
               || s == 0x1C) {
        u8 k = U8(PTR(u, 0x110), 0x1C);

        if (k < 0x1A)
            *y = *y * (h / F32(g_0045D300 + k * 0xA0, 0x80));
        else if (k >= 0x3E && k <= 0x5C)
            *y = *y * (h / 114.2966f);
        else if (k > 0x5C && k < 0x68)
            *y = *y * (h / 107.5364f);
    } else if (s == 0x1A) {
        u32 f = U32(act, 0x1C);
        int d = (f & 0x80) ? 3 : (f & 0x100) ? 0x12 : (f & 0x200) ? 9 : (f & 0x800) ? 0x13
              : (f & 0x4000) ? 0xC : (f & 0x10000) ? 2 : (f & 0x20000000) ? 1 : 4;

        *y = *y * (h / F32(g_0045D300 + d * 0xA0, 0x80));
    } else if (s == 0x1B) {
        u32 f = U32(act, 0x1C);
        int d = (f & 4) ? 0 : (f & 0x100000) ? 0x14 : 1;

        *y = *y * (h / F32(g_0045D300 + d * 0xA0, 0x80));
    }
    if ((U32(act, 0x18) & 0x40020) == 0 && *y < h * -1.0f)
        *y = h * -1.0f;
}

/* The unit's matrix (+0) from its rotation and position, scaled by +0x60 when flag 0x80 of
 * +0x19C is set or +0x1BA > 3 on foot. */
static inline void unit_matrix(Unit *u)
{
    UNIT_MATRIX(u, &F32(u, 0x50), &F32(u, 0x40));
    if (BIT(u, 0x19C, 7) || (U8(u, 0x1BA) > 3 && S32(u, 0x118) < 0x3C)) {
        float m[4][4];
        int i, k;

        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                m[i][k] = F32(u, i * 0x10 + k * 4);
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                F32(u, i * 0x10 + k * 4) = m[i][k] * (i < 3 ? F32(u, 0x60 + i * 4) : 1.0f);
    }
}

/* 0x00167730, 0x364 bytes. The root offset (+0x80) of a unit without its model: the root
 * node's translation in the action's motion at the frame (turned with the unit), or, standing
 * still, just the state's height; +0x90 the point above the position (150 lower for riders). */
void func_00167730(Unit *u)
{
    u8 *act = PTR(u, 0x210);
    int k;

    if ((U32(act, 0x18) & 0x40020) == 0 && PTR(act, 0x14) == 0) {
        F32(u, 0x80) = 0.0f;
        F32(u, 0x84) = F32(PTR(u, 0x114), 0x80) * -1.0f;
        F32(u, 0x88) = 0.0f;
        F32(u, 0x8C) = 0.0f;
    } else {
        u32 *m = *(u32 **)act_motion(u, act);
        float t = F32(u, 0x21C);
        const float *p = (const float *)(m + 3);

        if (t < (float)(int)m[2]) {
            u32 i, got = 0;

            for (i = 0; i < m[1]; i++) {
                u32 w = *(const u32 *)p++;
                u32 size = w >> 13 & 7;

                if ((w & 0xFF) == 0) {
                    u32 c = w >> 8 & 0x1F;
                    float v = track_at(p, size, t);

                    if (c == 5) {
                        got++;
                        F32(u, 0x88) = v;
                    } else if (c == 4) {
                        got++;
                        F32(u, 0x84) = v;
                    } else if (c == 3) {
                        got++;
                        F32(u, 0x80) = v;
                    }
                    if (got > 2)
                        break;
                }
                p += size * (w >> 18);
            }
        }
        turn_offset(u);
    }
    for (k = 0; k < 4; k++)
        F32(u, 0x90 + k * 4) = F32(u, 0x40 + k * 4) + F32(u, 0x80 + k * 4);
    if (U32(PTR(u, 0x210), 0x18) & 0x8000000)
        F32(u, 0x94) = F32(u, 0x94) - 150.0f;
}

/* 0x00167AB0, 0x6D8 bytes. Poses only the first nodes (6 for state 0x3E, else 8) of a unit's
 * model from the action's motion at its frame (a cheap pose for far units), the root's height
 * scaled, those nodes' matrices; no root offset. */
void func_00167AB0(Unit *u)
{
    u32 n = S32(u, 0x118) == 0x3E ? 6 : 8;
    u32 *m = *(u32 **)act_motion(u, PTR(u, 0x210));
    u8 *nodes = (u8 *)root_node(PTR(u, 0x11C));
    float t = F32(u, 0x21C);
    const float *p = (const float *)(m + 3);
    u32 i;
    int k;

    for (i = 0; i < m[1]; i++) {
        u32 w = *(const u32 *)p++;
        u32 size = w >> 13 & 7;

        if ((w & 0xFF) <= n) {
            float v = track_at(p, size, t);
            float *nd = (float *)(nodes + (w & 0xFF) * 0x70);

            U8(nd, 0x68) = 1;
            switch (w >> 8 & 0x1F) {
            case 0:
                nd[4] = v;
                break;
            case 1:
                nd[5] = v;
                break;
            case 2:
                nd[6] = v;
                break;
            case 3:
                nd[0] = v;
                break;
            case 4:
                nd[1] = v;
                break;
            case 5:
                nd[2] = v;
                break;
            }
        }
        p += size * (w >> 18);
    }
    if (PTR(u, 0x11C) != 0)
        scale_root(u, PTR(u, 0x210), &((float *)root_node(PTR(u, 0x11C)))[1]);
    nodes = (u8 *)root_node(PTR(u, 0x11C));
    PTR(PTR(u, 0x11C), 0x208) = nodes;
    for (i = 0; i < n; i++) {
        if (U8(nodes, 0x68) != 0) {
            U8(nodes, 0x68) = 0;
            UNIT_MATRIX(nodes + 0x20, nodes + 0x10, nodes);
        }
        nodes += 0x70;
    }
    for (k = 0; k < 4; k++) {
        F32(u, 0x80 + k * 4) = 0.0f;
        F32(u, 0x90 + k * 4) = F32(u, 0x40 + k * 4);
    }
}

/* 0x00168190, 0x268 bytes. A unit carried by another: its position and rotation from its mount
 * (+0x288, for riders) or its carrier (+0x284: the carrier's node +0x275, or the carrier itself
 * without a model); then its matrix. */
void func_00168190(Unit *u)
{
    int k;

    if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0) {
        u8 *c = PTR(u, 0x284);

        if (c != 0 && (char)U8(u, 0x275) != -1) {
            if (PTR(c, 0x11C) == 0) {
                for (k = 0; k < 4; k++)
                    F32(u, 0x40 + k * 4) = F32(c, 0x40 + k * 4);
            } else {
                float *m = func_0016A170(c, (char)U8(u, 0x275)), *s = (float *)PS2_PTR(0x70000030);
                float w;

                for (k = 0; k < 4; k++)
                    F32(u, 0x40 + k * 4) = m[k] * s[0] + m[4 + k] * s[1] + m[8 + k] * s[2]
                                           + m[12 + k] * s[3];
                w = F32(u, 0x4C);
                for (k = 0; k < 4; k++)
                    F32(u, 0x40 + k * 4) = F32(u, 0x40 + k * 4) * (1.0f / w);
            }
            for (k = 0; k < 4; k++)
                F32(u, 0x50 + k * 4) = F32(PTR(u, 0x284), 0x50 + k * 4);
        }
    } else {
        for (k = 0; k < 4; k++)
            F32(u, 0x40 + k * 4) = F32(PTR(u, 0x288), 0x40 + k * 4);
        for (k = 0; k < 4; k++)
            F32(u, 0x50 + k * 4) = F32(PTR(u, 0x288), 0x50 + k * 4);
    }
    unit_matrix(u);
    BIT(u, 0x19C, 0) = 0;
}

void func_00209190(float *a, float *b, u8 player, int c);
void func_00208980(u8 *trail, void *m, u8 colour);

/* 0x00168400, 0xB8 bytes. Turns a weapon part's trail (+0x68) on (func_0016F8E0, part flag 4
 * cleared) or off: a trail still drawing (+0xA) is only told to stop (+0x10). */
void func_00168400(float f, int player, u8 *part, int on)
{
    u8 *t = PTR(part, 0x68);

    if (on && t == 0) {
        func_0016F8E0(f, (float *)(part), player);
        BIT(part, 0x60, 2) = 0;
    } else if (!on) {
        if (t != 0) {
            if (U8(t, 10) != 0) {
                U32(t, 0x10) = 0;
            } else {
                func_002088C0(t);
                PTR(part, 0x68) = 0;
            }
        }
    } else if (t != 0 && U32(t, 0x10) == 0) {
        func_002088C0(t);
        PTR(part, 0x68) = 0;
    }
}

/* 0x001684C0, 0x270 bytes. The trails of a weapon `w`'s parts (kind +0x48): one part (+0x5C)
 * for kinds 0x6C-0x6F and 0x3C-0x3F; else the part +0x50 (or the two +0x50 / +0x54, by `mask`)
 * and, except kinds 0x14-0x1B and 0x30-0x37, the two +0x58 / +0x5C. `second` gates the single
 * ones; `link` links new trails to +0x68. Whether a part was handled. */
int func_001684C0(float f, int player, u8 *w, int on, int second, int link, u16 mask)
{
    u8 k = U8(w, 0x48);
    int done = 0;
    u32 i;
    u8 *p;

    if ((u32)(k - 0x6C) < 4 || (u32)(k - 0x3C) < 4) {
        p = PTR(w, 0x5C);
        if (p != 0 && BIT(p, 0x60, 0)) {
            func_00168400(f, player, p, on);
            done = 1;
        }
        return done;
    }
    if (PTR(w, 0x54) == 0 || BIT(PTR(w, 0x54), 0x60, 0) == 0) {
        p = PTR(w, 0x50);
        if (p != 0 && BIT(p, 0x60, 0)) {
            func_00168400(f, player, p, on && second);
            done = 1;
            if (link && PTR(p, 0x68) != 0)
                func_0016EAB0(F32(w, 0x68), (float *)p);
        }
    } else {
        for (i = 0; i < 2; i++) {
            p = PTR(w, 0x50 + i * 4);
            if (p != 0 && BIT(p, 0x60, 0)) {
                func_00168400(f, player, p, on && (mask & 1 << i));
                done = 1;
            }
        }
    }
    k = U8(w, 0x48);
    if ((u32)(k - 0x30) > 7 && (u32)(k - 0x14) > 7) {
        for (i = 0; i < 2; i++) {
            p = PTR(w, 0x58 + i * 4);
            if (p != 0 && BIT(p, 0x60, 0)) {
                func_00168400(f, player, p, on && second);
                done = 1;
                if (link && PTR(p, 0x68) != 0)
                    func_0016EAB0(F32(w, 0x68), (float *)p);
            }
        }
    }
    return done;
}

/* 0x00168730, 0x90 bytes. Starts a trail for a unit's slot (+0x28) between the two points of
 * `c` (func_00209190). Whether it started. */
int func_00168730(Unit *u, u8 *slot, int c)
{
    float a[4], b[4];
    u8 *t;

    if (PTR(u, 0x11C) == 0)
        return 0;
    if (slot == 0)
        return 0;
    func_00209190(a, b, U8(u, 0x14E), c);
    t = func_002087A0();
    PTR(slot, 0x28) = t;
    if (t != 0) {
        func_00208820(t, (unsigned int *)(a), (unsigned int *)(b), U8(u, 0x14E));
        return 1;
    }
    return 0;
}

/* 0x001687C0, 0x10C bytes. Keeps a slot's trail going (`on`) or stops it; while it lives, its
 * points follow `c` and, with `colour`, it gets the unit's colour (+0x184). */
void func_001687C0(Unit *u, u8 *slot, int c, int on, int colour)
{
    u8 *t = PTR(slot, 0x28);

    if (on && t == 0) {
        func_00168730(u, slot, c);
    } else if (!on) {
        if (t != 0) {
            if (U8(t, 10) == 0) {
                func_002088C0(t);
                PTR(slot, 0x28) = 0;
            } else {
                U32(t, 0x10) = 0;
                func_00209190((float *)(t + 0x20), (float *)(t + 0x30), U8(u, 0x14E), c);
                if (colour)
                    func_00208980(t, (void *)PS2_PTR(0x70000000), U8(u, 0x184));
            }
        }
    } else if (t != 0) {
        U32(t, 0x10) = 1;
        func_00209190((float *)(t + 0x20), (float *)(t + 0x30), U8(u, 0x14E), c);
        if (colour)
            func_00208980(t, (void *)PS2_PTR(0x70000000), U8(u, 0x184));
    }
}

extern u32 g_004065D0[12];               /* the nodes the ten records follow (from index 2) */

float func_0016BF10(Unit *u);
int func_0016BE50(Unit *u, float *rate);
u8 *func_0014F810(Actor *a, int node);    /* (u8 node in model.c: callers pass it as is) */
void func_0016EC90(float rate, float f, u8 *slot, u8 *node, u8 colour, int flag, int hit);

/* A node's point (its matrix times the scratchpad's (0, 0, 0, 1), divided by w) into out. */
static inline void node_point(float *out, float *m)
{
    float *s = (float *)PS2_PTR(0x70000030), w;
    int k;

    for (k = 0; k < 4; k++)
        out[k] = m[k] * s[0] + m[4 + k] * s[1] + m[8 + k] * s[2] + m[12 + k] * s[3];
    w = out[3];
    for (k = 0; k < 4; k++)
        out[k] = out[k] * (1.0f / w);
}

/* Writes the identity matrix at m (rows of the vector (0, 0, 0, 1) turned). */
static inline void identity(float *m)
{
    int i, k;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i * 4 + k] = i == k ? 1.0f : 0.0f;
}

/* Shows a slot's weapon (flags 0x20 and 0x40 the first time, then 2). */
static inline void slot_show(u8 *s)
{
    u8 b = U8(s, 0x4C);

    if ((b & 2) == 0) {
        U8(s, 0x4C) = (b & ~0x20) | 0x20;
        U8(s, 0x4C) = (b & ~0x60) | 0x60;
    }
    BIT(s, 0x4C, 1) = 1;
}

/* Sets flag 2 (drawn) of a slot's weapon parts: +0x50 and +0x58 / +0x5C to `a`, +0x54 to `b`. */
static inline void parts_drawn(u8 *s, int a, int b, int both)
{
    int i;

    U8(PTR(s, 0x50), 0x60) = (U8(PTR(s, 0x50), 0x60) & ~2) | a << 1;
    for (i = 0; i < 2; i++) {
        u8 *p = PTR(s, 0x58 + i * 4);

        if (p != 0)
            U8(p, 0x60) = (U8(p, 0x60) & ~2) | a << 1;
    }
    if (both)
        U8(PTR(s, 0x54), 0x60) = (U8(PTR(s, 0x54), 0x60) & ~2) | b << 1;
}

/* Whether the frame is inside the hit's window (+5 to +6). */
static inline int in_hit(Unit *u, u8 *hit)
{
    return hit != 0 && !(F32(u, 0x21C) < (float)U8(hit, 5)) && !((float)U8(hit, 6) < F32(u, 0x21C));
}

/* 0x001688D0, 0xFF0 bytes. A unit's matrices and attached things each frame: its place from
 * its carrier or mount; its matrix; the actor's base matrix (the unit's, or the identity with a
 * parent: the carrier's node +0x275 or the mount's +0x274); the motion's matrices; on foot, the
 * two weapon slots (their own motions, shown by the weapon mask +0x148 bits 0 / 1, placed on the
 * hand nodes, special kinds 0x30-0x37 and 0x14-0x1B held between two nodes during their
 * hits); the ten records following their nodes (mask bits 2-11, previous point kept); the
 * weapon trails during hits with flag 0x2000000 (+0x2C), by the hit's mask +0x12. */
void func_001688D0(Unit *u)
{
    u8 *hit = PTR(PTR(u, 0x210), 0x14);
    u8 *a;
    int k, carried;

    carried = PTR(u, 0x284) != 0 && (char)U8(u, 0x275) != -1;
    if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0) {
        if (carried) {
            node_point(&F32(u, 0x40), func_0016A170(PTR(u, 0x284), (char)U8(u, 0x275)));
            for (k = 0; k < 4; k++)
                F32(u, 0x50 + k * 4) = F32(PTR(u, 0x284), 0x50 + k * 4);
        }
    } else {
        for (k = 0; k < 4; k++) {
            F32(u, 0x40 + k * 4) = F32(PTR(u, 0x288), 0x40 + k * 4);
            F32(u, 0x50 + k * 4) = F32(PTR(u, 0x288), 0x50 + k * 4);
        }
    }
    unit_matrix(u);
    a = PTR(u, 0x11C);
    if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0) {
        if (PTR(u, 0x284) != 0 && (char)U8(u, 0x275) != -1) {
            identity(&F32(a, 0x1A0));
            PTR(PTR(u, 0x11C), 0x1FC) = PTR(PTR(u, 0x284), 0x11C);
            U8(PTR(u, 0x11C), 0x201) = U8(u, 0x275);
        } else {
            for (k = 0; k < 16; k++)
                F32(a, 0x1A0 + k * 4) = F32(u, k * 4);
            PTR(PTR(u, 0x11C), 0x1FC) = 0;
            U8(PTR(u, 0x11C), 0x201) = 0;
        }
    } else {
        identity(&F32(a, 0x1A0));
        PTR(PTR(u, 0x11C), 0x1FC) = PTR(PTR(u, 0x288), 0x11C);
        U8(PTR(u, 0x11C), 0x201) = U8(u, 0x274);
    }
    U8(PTR(u, 0x11C), 0x20C) = (U8(PTR(u, 0x11C), 0x20C) & ~0x10) | (U8(u, 0x19C) & 1) << 4;
    if (plays_motion(u))
        func_0014D390(PTR(u, 0x11C), U8(u, 0x155));
    else
        func_0014D3B0(PTR(u, 0x11C));
    if (S32(u, 0x118) < 0x3C) {
        float ft = func_0016BF10(u);
        int w1 = (U16(u, 0x148) & 1) != 0, w2 = (U16(u, 0x148) & 2) != 0;
        u8 *s = u + 0x290, *r;

        for (k = 0; k < 2; k++, s += 0x70) {
            u8 c;
            int win;

            if (BIT(s, 0x4C, 0) == 0)
                continue;
            if (BIT(s, 0x4C, 2) && PTR(s, 0x44) != 0) {
                u8 *o = PTR(s, 0x44);

                func_0014D9A0(F32(s, 0x64), o, PTR(s, 0x60));
                if (PTR(u, 0x11C) != 0 && 0.0f < F32(PTR(u, 0x11C), 0x214))
                    func_0014E380(o);
                func_0014D6C0(o);
                func_0014D390(o, 3);
            }
            if (BIT(s, 0x4C, 4) == 0) {
                float rate;
                u8 b = U8(s, 0x4C);

                if (b & 8) {
                    if ((b & 2) == 0 && (w1 || w2)) {
                        U8(s, 0x4C) = (b & ~0x20) | 0x20;
                        U8(s, 0x4C) = (b & ~0x60) | 0x60;
                    }
                    U8(s, 0x4C) = (U8(s, 0x4C) & ~2) | (w1 || w2) << 1;
                    parts_drawn(s, w1, w2, 1);
                } else if ((U16(u, 0x148) & 1 << k) == 0) {
                    U8(s, 0x4C) = b & ~2;
                    parts_drawn(s, 0, 0, 0);
                } else {
                    slot_show(s);
                    parts_drawn(s, 1, 0, 0);
                }
                if (func_0016BE50(u, &rate) == 0)
                    rate = 1.0f;
                func_0016EC90(rate, ft, s, func_0014F810(PTR(u, 0x11C), U8(s, 0x49)), U8(u, 0x184),
                              -(U8(u, 0x19C) & 1), PTR(PTR(u, 0x210), 0x14) != 0);
            }
            c = U8(s, 0x48);
            if (c >= '0' && c <= '7') {
                u8 *h = PTR(PTR(u, 0x210), 0x14);
                u32 f = U32(PTR(u, 0x210), 0x1C);

                win = in_hit(u, h);
                if (win && (w1 || w2) && (f & 0x2000)) {
                    slot_show(s);
                    func_001700F0(s, 1, func_0016A170(u, 0x12), func_0016A170(u, 0x14), 1);
                } else if (win && (f & 0x1000)) {
                    slot_show(s);
                    func_001700F0(s, 1, func_0016A170(u, 0x13), func_0016A170(u, 0x15), 0);
                } else {
                    func_001700F0(s, 0, 0, 0, 1);
                }
            }
            c = U8(s, 0x48);
            if (c >= 0x14 && c <= 0x1B) {
                win = in_hit(u, PTR(PTR(u, 0x210), 0x14));
                if (win && w2 && (U32(PTR(u, 0x210), 0x1C) & 0x3000)) {
                    slot_show(s);
                    func_00170510(s, 1, func_0016A170(u, 0x15), func_0016A170(u, 0x14));
                } else {
                    func_00170510(s, 0, 0, 0);
                }
            }
        }
        r = u + 0x450;
        for (k = 2; k < 0xC; k++, r += 0x30) {
            if ((U16(u, 0x148) & 1 << k) == 0) {
                BIT(r, 0x24, 0) = 0;
            } else {
                int i;

                for (i = 0; i < 4; i++)
                    F32(r, 0x10 + i * 4) = F32(r, i * 4);
                node_point((float *)r, func_0016A170(u, g_004065D0[k] & 0xFF));
                if (BIT(r, 0x24, 0) == 0) {
                    for (i = 0; i < 4; i++)
                        F32(r, 0x10 + i * 4) = F32(r, i * 4);
                }
                BIT(r, 0x24, 0) = 1;
            }
        }
        if ((U8(u, 0x181) == 0 || BIT(u, 0x19E, 5))
            && (U8(u, 0x14E) < 2 || func_00209160() != 0 || BIT(u, 0x19E, 5))) {
            int on = hit != 0 && (U32(hit, 0x2C) & 0x2000000) && F32(u, 0x21C) <= (float)U8(hit, 6);

            s = u + 0x290;
            for (k = 0; k < 2; k++, s += 0x70) {
                if (BIT(s, 0x4C, 0) && BIT(s, 0x4C, 4) == 0)
                    func_001684C0(ft, U8(u, 0x14E), s, on, hit == 0 ? 0 : U16(hit, 0x12) & 1 << k,
                                  F32(u, 0x21C) <= 1.0f, hit == 0 ? 0 : U16(hit, 0x12));
            }
            r = u + 0x450;
            for (k = 0; k < 10; k++, r += 0x30) {
                u32 bits = hit == 0 ? 0 : U16(hit, 0x12) & 1 << (k + 2);

                if (!on)
                    bits = 0;
                func_001687C0(u, r, k, (U8(r, 0x24) & 1) && bits, -(U8(u, 0x19C) & 1));
            }
            s = u + 0x290;
            for (k = 0; k < 2; k++, s += 0x70)
                U8(s, 0x4D) = (U8(s, 0x4D) & ~1) | (U8(u, 0x19E) >> 5 & 1);
        }
    }
    BIT(u, 0x19C, 0) = 0;
}

typedef unsigned long long u64;

#define g_70000158 PS2_GETP(u32 *, 0x70000158)         /* the DMA chain's write cursor */
#define g_70000158_SET(v) PS2_SETP(0x70000158, v)

extern int g_0045D2A8;                   /* (small data) slow motion: its timer */
#ifdef SW2E_PC
extern ps2ptr g_005B4A00_a;      /* the two duelling units */
#define g_005B4A00 ((u8 *)PS2_PTR(g_005B4A00_a))
#define g_005B4A00_SET(v) (g_005B4A00_a = PS2_ADDR(v))
#else
extern u8 *g_005B4A00;
#define g_005B4A00_a (*(ps2ptr *)&g_005B4A00)
#define g_005B4A00_SET(v) (g_005B4A00 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005B4A04_a;      /* the two duelling units */
#define g_005B4A04 ((u8 *)PS2_PTR(g_005B4A04_a))
#define g_005B4A04_SET(v) (g_005B4A04_a = PS2_ADDR(v))
#else
extern u8 *g_005B4A04;
#define g_005B4A04_a (*(ps2ptr *)&g_005B4A04)
#define g_005B4A04_SET(v) (g_005B4A04 = (v))
#endif
extern u32 g_0076E700[];                 /* per player: state flags */
extern float g_00574D90[4];              /* the units' colour (w: the brightness) */

void func_0027A210(Unit *u);

/* 0x001698D0, 0x7F4 bytes. Draws a unit (not with flag 8 of +0x19D): its opacity (players
 * always solid; hidden ones (flag 8 of +0x198) faint or invisible; during the slow-motion duel
 * the others fade out; in `mode` hidden others are dropped unless func_003E1F80 says otherwise);
 * a GS packet setting the alpha test (and, for a unit held still, the alpha blend), the colour
 * and brightness (+0x186) for VU1; the model, the weapon slots (two-handed kinds between their
 * nodes during their hits), the weapon model, the horse; the blend set back. */
void func_001698D0(Unit *u, int mode)
{
    int still = (char)U8(u, 0x19C) < 0 && U8(u, 0x15A) == 3;
    u8 p, b;
    u32 alpha, n, *d, k;
    u64 *q;
    float c[4];
    u8 *s;

    if (BIT(u, 0x19D, 3))
        return;
    p = U8(u, 0x14E);
    alpha = p < 2 ? 0x80 : U8(u, 0x14D);
    if (mode == 0) {
        if (g_0045D2A8 == 0) {
            if (BIT(u, 0x198, 3)) {
                if (p < 2)
                    alpha = 0;
                else if (0x20 < alpha)
                    alpha = 0x20;
            }
        } else if (u != g_005B4A00 && u != g_005B4A04
                   && (S32(u, 0x118) != 0x3C
                       || (PTR(u, 0x28C) != g_005B4A00 && PTR(u, 0x28C) != g_005B4A04))) {
            if (BIT(u, 0x198, 3)) {
                u32 lim = S32(u, 0x118) != 0x3C ? 0x20 : 0x40;

                if (lim < alpha)
                    alpha = lim;
            } else if (BIT(u, 0x19F, 2)) {
                float f = 1.0f - (float)g_0045D2A8 / 100.0f;

                if (f < 0.75f) {
                    f = 0.0f;
                } else {
                    float g = (f - 0.75f) / 0.25f;

                    if (1.0f <= g)
                        g = 1.0f;
                    f = 0.0f;
                    if (0.0f <= g)
                        f = g;
                }
                alpha = (u32)((float)alpha * f) & 0xFF;
            }
        }
    } else {
        if (BIT(u, 0x198, 3) && p > 3 && func_003E1F80(PS2_ADDR(u)) == 0)
            alpha = 0;
        if (BIT(u, 0x19C, 7))
            alpha = 0;
    }
    if (mode != 0) {
        if (g_0076E700[U8(u, 0x14E)] & 0x3E640)
            func_002538C0(U8(u, 0x14E), alpha);
        if (alpha == 0 || U8(u, 0x14E) < 2)
            func_001C8ED0(U8(u, 0x14E));
    }
    func_0027A210(u);
    n = still ? 2 : 1;
    d = g_70000158;
    d[0] = (n + 1) | 0x10000000;
    d[1] = 0;
    d[2] = 0;
    d[3] = (n + 1) | 0x50000000;
    q = (u64 *)(d + 4);
    q[0] = n | 0x1000000000008000ULL;
    q[1] = 0xE;
    if (alpha < 0x80)
        q[2] = 0x5001B;
    else
        q[2] = (u64)U8(PTR(PTR(u, 0x11C), 0x1E8), 0x2F) << 4 | 0x5000B;
    q[3] = 0x47;
    q += 4;
    if (still) {
        q[0] = U8(u, 0x186) < 0x80 ? 0x44 : 0x48;
        q[1] = 0x42;
        q += 2;
    }
    b = U8(u, 0x186);
    d = (u32 *)q;
    d[0] = 0x10000001;
    d[1] = 0;
    d[2] = 0;
    d[3] = 0x6C010001;
    g_00574D90[3] = (float)b;
    for (k = 0; k < 4; k++)
        c[k] = g_00574D90[k];
    for (k = 0; k < 4; k++)
        d[4 + k] = (u32)(int)(c[k] * 16.0f);    /* vftoi4 */
    g_70000158_SET(d + 8);
    func_0014F0E0(PTR(u, 0x11C), alpha);
    s = u + 0x290;
    for (k = 0; k < 4; k++, s += 0x70) {
        u32 f = U32(PTR(u, 0x210), 0x1C);

        if ((f & 1 << (k + 0x15)) == 0 && BIT(s, 0x4C, 0)) {
            func_001700A0(s, alpha);
            if ((u32)(U8(s, 0x48) - 0x30) < 8) {
                f = U32(PTR(u, 0x210), 0x1C);
                if (f & 0x2000)
                    func_00170300(s, func_0016A170(u, 0x12), func_0016A170(u, 0x15),
                                  func_0016A170(u, 0x14));
                else if (f & 0x1000)
                    func_00170300(s, func_0016A170(u, 0x13), func_0016A170(u, 0x15),
                                  func_0016A170(u, 0x14));
            }
            if ((u32)(U8(s, 0x48) - 0x14) < 8 && (U32(PTR(u, 0x210), 0x1C) & 0x3000))
                func_001706A0(s, func_0016A170(u, 0x15), func_0016A170(u, 0x14));
        }
    }
    if (PTR(u, 0x134) != 0)
        func_0014F970(PTR(u, 0x134));
    if (S32(u, 0x118) == 0x3C && U8(u, 0x180) < 0x14)
        func_002AD9A0((unsigned char **)(u + 0x1A0));
    if (still) {
        d = g_70000158;
        d[0] = 0x10000002;
        d[1] = 0;
        d[2] = 0;
        d[3] = 0x50000002;
        q = (u64 *)(d + 4);
        q[0] = 0x1000000000008001ULL;
        q[1] = 0xE;
        q[2] = 0x44;
        q[3] = 0x42;
        g_70000158_SET((u32 *)(q + 4));
    }
    d = g_70000158;
    d[0] = 0x10000000;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0;
    g_70000158_SET(d + 4);
}

#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

short func_0034A530(void);

/* 0x0016A0D0, 0x94 bytes. The point of the unit's node `node` (its matrix's translation). */
void func_0016A0D0(Unit *u, float *out, u8 node)
{
    float *m, v[4];
    int k;

    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 1.0f;
    m = (float *)func_0014F810(PTR(u, 0x11C), node);
    for (k = 0; k < 4; k++)
        v[k] = out[k];
    for (k = 0; k < 4; k++)
        out[k] = m[k] * v[0] + m[4 + k] * v[1] + m[8 + k] * v[2] + m[12 + k] * v[3];
    v[3] = 1.0f / out[3];
    for (k = 0; k < 4; k++)
        out[k] = out[k] * v[3];
}

/* 0x0016A170, 0x1C bytes, matching. The world matrix of the unit's node `node`. */
float *func_0016A170(Unit *u, int node)
{
    return (float *)func_0014F810(PTR(u, 0x11C), node);
}

/* 0x0016A190, 0x24 bytes, matching. The local matrix of the unit's node `node`. */
u8 *func_0016A190(Unit *u, u32 node)
{
    return PTR(PTR(u, 0x11C), 0x208) + (node & 0xFF) * 0x70 + 0x20;
}

/* 0x0016A1C0, 0x50 bytes, matching. Clears the unit's weapon mask and its related fields. */
void func_0016A1C0(Unit *u)
{
    BIT(u, 0x19D, 1) = 0;
    U16(u, 0x148) = 0;
    U16(u, 0x14A) = 0;
    U32(u, 0x140) = 0;
    U8(u, 0x14C) = 0x40;
    *(u64 *)(u + 0x120) = 0;
    BIT(u, 0x19F, 7) = 0;
}

/* 0x0016A210, 0x12C bytes. Whether `v` guards a hit from `u` (0 no, 1 yes): its chance is
 * skill² / 8000 + the officer's +0xA7 percent (skill from its record +0x68, or func_0034A530
 * for some officers); 2 for an unguardable hit (+0x2C flag 0x80000000 during an attack). */
int func_0016A210(Unit *u, Unit *v, u8 *hit)
{
    u8 *o;
    short s;
    u32 c;

    if (v == 0)
        return 0;
    o = (g_00693970 + S16(v, 0x178) * 0xC0 + 0x100C0);
    if (PTR(PTR(u, 0x210), 0x14) != 0 && (U32(hit, 0x2C) & 0x80000000))
        return 2;
    s = S16(PTR(o, 0x68), 0x1A);
    if (PTR(o, 0x10) != 0 && U8(o, 0x7F) == 0)
        s = func_0034A530();
    c = (s * s) / 8000 + U8(o, 0xA7);
    if (c == 0)
        c = 1;
    if (c < RANDOM() % 100)
        return 0;
    return 1;
}

/* 0x0016A340, 0x88 bytes, matching. How `v` is hit by `hit`: 5 nobody, 3 hit flag 0x400, 4 a unit whose
 * action has flag 0x8000000 (+0x1C), 1 hit flag 0x40000000 (+0x28), 2 a mounted unit, else 0. */
int func_0016A340(Unit *v, u8 *hit)
{
    u8 *act;

    if (v == 0)
        return 5;
    if (U16(hit, 0x1C) & 0x400)
        return 3;
    act = PTR(v, 0x210);
    if (U32(act, 0x1C) & 0x8000000)
        return 4;
    if (U32(hit, 0x28) & 0x40000000)
        return 1;
    if (U32(act, 0x18) & 0x8000000)
        return 2;
    return 0;
}

#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))          /* (scratchpad) */

float func_003AFF70(u8 *officer);
float func_003AFE50(u8 *officer);
int func_0016C040(Unit *u);
void func_001C7FC0(int kind, float *pos, void *a, u32 flags);

/* 0x0016A3D0, 0x310 bytes. Whether `u` withstands `v`'s hit `hit` (keeps its footing): hits
 * with flag 0x20 during its own attack; officers of rank 2 (+0xAB) against flag 0x20000000,
 * rank 3 during an armoured attack; func_00273620; an officer under a quarter of its life with
 * flag 1 of +0x19E; actions with flag 0x4000000; otherwise when its strength beats the
 * attacker's by 2.2 times (4 times for a minor unit against a major one). */
int func_0016A3D0(Unit *u, Unit *v, u8 *hit)
{
    u32 f;
    u8 *o;

    if (v == 0)
        return 0;
    f = U32(hit, 0x28);
    if ((f & 0x20) && PTR(PTR(u, 0x210), 0x14) != 0)
        return 1;
    if (U32(PTR(v, 0x210), 0x1C) & 0x20)
        return 0;
    o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    if (U8(o, 0xAB) >= 2 && (f & 0x20000000))
        return 1;
    if (U8(o, 0xAB) > 2) {
        u8 *h = PTR(PTR(u, 0x210), 0x14);

        if ((h != 0 ? U32(h, 0x28) & 1 : 0) != 0 && (f & 0x400001D) == 0)
            return 1;
    }
    if (U32(PTR(u, 0x210), 0x18) & 0x200000)
        return 0;
    if (f & 0x400001D)
        return 0;
    if (func_00273620(u, hit) != 0)
        return 1;
    if (BIT(u, 0x19E, 0)) {
        int lim = S16(o, 0x80) / 4;

        if (lim >= 0x32)
            lim = 0x32;
        if (S16(o, 0x82) < lim)
            return 1;
    }
    if (U32(PTR(u, 0x210), 0x18) & 0x420)
        return 0;
    if ((U32(PTR(u, 0x210), 0x1C) & 0x4000000) == 0) {
        float a = func_003AFF70(o);
        u8 rank = U8(u, 0x1BA);
        float b = func_003AFE50((g_00693970 + S16(v, 0x178) * 0xC0 + 0x100C0));
        float r = (float)(int)(short)(int)a / (float)(int)(short)(int)b;

        if (rank < 5 && U8(v, 0x1BA) > 4) {
            if (r < 4.0f)
                return 0;
        } else if (r < 2.2f) {
            return 0;
        }
    }
    return 1;
}

/* 0x0016A6E0, 0x134 bytes. Wears down a struggle (+0x157 by 1-3 per hit, +0x194 by 5 x `n`);
 * when either runs out, the unit breaks free (an effect of kind 6 at its point). */
void func_0016A6E0(Unit *u, u8 *hit, void *a, short n)
{
    u8 *h = PTR(PTR(u, 0x210), 0x14);
    u8 d;

    if ((h != 0 ? U32(h, 0x28) & 0x1C : 0) != 0)
        d = 3;
    else
        d = (U32(hit, 0x28) & 1) ? 2 : 1;
    if (d < U8(u, 0x157))
        U8(u, 0x157) = U8(u, 0x157) - d;
    else
        U8(u, 0x157) = 0;
    if ((short)(n * 5) < U16(u, 0x194))
        U16(u, 0x194) = U16(u, 0x194) - n * 5;
    else
        U16(u, 0x194) = 0;
    if (U8(u, 0x157) == 0 || S16(u, 0x194) == 0) {
        U8(u, 0x157) = 0;
        U16(u, 0x194) = 0;
        func_00151D60(u);
        g_70000D60 = 1;
        func_001C7FC0(6, &F32(u, 0x90), a, func_0016C040(u) != 0 ? 0x200 : 0);
    }
}

/* 0x0016A820, 0x74 bytes. Lowers +0x168 by 5 x `n`; at 0 it ends (+0x18B cleared). */
void func_0016A820(Unit *u, short n)
{
    if ((float)(int)(short)(n * 5) < F32(u, 0x168))
        F32(u, 0x168) = F32(u, 0x168) - (float)(int)(short)(n * 5);
    else
        F32(u, 0x168) = 0.0f;
    if (F32(u, 0x168) <= 0.0001f) {
        F32(u, 0x168) = 0.0f;
        U8(u, 0x18B) = 0;
    }
}

/* 0x0016A8A0, 0x1C0 bytes. Notes that `v` hit `u` with `hit`: the attacker's weapon kind bit in
 * +0x120, flag 8 of +0x27C and the player's hit counter (`counted`; not for kind ':' unless
 * mounted), the last attacker (+0x144); grabs (actions 0x87-0x8A with hit flag 0x400) go on in
 * func_00155140. */
void func_0016A8A0(Unit *u, Unit *v, u8 *hit, int counted, void *x)
{
    u8 *prev = PTR(v, 0x214);
    u16 id;

    if ((U32(hit, 0x28) & 0xC0000000) == 0 && PTR(v, 0x11C) != 0)
        *(u64 *)(u + 0x120) |= (u64)(long long)(1 << U8(PTR(v, 0x11C), 0x202));
    if ((U8(PTR(v, 0x110), 0x1C) != ':' || (U32(PTR(v, 0x210), 0x18) & 0x800)) && counted) {
        BIT(u, 0x27C, 3) = 1;
        if (U8(u, 0x14E) < 2)
            func_001D2260(U8(u, 0x14E), 1);
        else if (BIT(u, 0x19C, 7))
            func_001D2260(U8(u, 0x15B), 1);
    }
    PTR(u, 0x144) = v;
    if (prev != 0 && (U32(prev, 0x1C) & 0x80000))
        func_00151D60(u);
    if (v == 0 || (U32(hit, 0x2C) & 0x400) == 0 || BIT(u, 0x19C, 7))
        return;
    id = U16(PTR(v, 0x210), 0);
    if (0x86 < id && id < 0x8B && PTR(v, 0x280) == 0 && PTR(v, 0x284) == 0
        && BIT(v, 0x19C, 7) == 0)
        func_00155140(u, v, hit, x);
}

extern u8 g_00669E2A[][0x48];            /* per player settings: +0 the pad port */

int func_001D1170(Unit *u, Unit *v, u8 *hit, float *dir);
short func_001CD060(Unit *u, Unit *v, u8 *hit, float *dir, void *pos, int kind, int guard,
                    int stand, int a8, int a9);
Unit *func_0016BE40(Unit *u);
void func_0016CB60(Unit *u, u8 port, int motor, int power, int frames);

/* 0x0016AA60, 0x574 bytes. `u` takes `hit` from `v` (or from the point `pos` without one):
 * clashes (func_00152840: 1 a clash, 2-4 one or both knocked back), counters (func_001D1170),
 * dodges (func_001524D0), guards (func_00152560: a guarded hit only pushes, vibrating 10
 * frames); else a real hit: in a struggle it wears the struggle down, otherwise the damage
 * (func_001CD060, by the guard chance and whether it withstands); the reaction
 * (func_00153E50); the player's pad vibrates. *damage gets the damage; `alpha` the hit's flash
 * (+0x14C) for hits with flag 0x80000000. Whether it was a real hit. */
int func_0016AA60(Unit *u, Unit *v, u8 *hit, void *pos, short *damage, u8 alpha)
{
    float dir[4];
    int r, k, got = 0, guard_kind;

    *damage = 0;
    for (k = 0; k < 4; k++)
        dir[k] = (v == 0 ? ((float *)pos)[k] : F32(v, 0x90 + k * 4)) - F32(u, 0x90 + k * 4);
    r = func_00152840(u, v, hit);
    if (r == 1) {
        if (BIT(u, 0x19C, 1)) {
            func_00151A90(u, 0);      /* a1 is left over from the call before in the original */
            BIT(u, 0x19C, 1) = 0;
        }
        func_00152EE0(u, v);
        PTR(u, 0x140) = v;
    } else {
        if (r == 2) {
            func_00151D60(v);
        } else if (r == 3) {
            func_00151D60(u);
        } else if (r == 4) {
            func_00151D60(v);
            func_00151D60(u);
        } else if (v != 0 && func_001D1170(u, v, hit, dir) != 0) {
            func_00153190(u);
        } else if (func_001524D0(u, v, hit) != 0) {
            func_00153110(u, dir);
        } else if (func_00152560(u, v, hit, dir, &guard_kind) != 0) {
            short d = func_001CCD60(u, PS2_ADDR(v), hit, pos);

            if (func_00153230(u, v, hit, dir, d, guard_kind, 0) != 0) {
                g_70000D60 = 1;
                func_001C8130(5, PS2_ADDR(&F32(u, 0x90)), 0, 8, U8(u, 0x14E));
            }
            if (U8(u, 0x14E) < 2) {
                u8 port = g_00669E2A[U8(u, 0x14E)][0];

                func_0016CB60(u, port, 1, 0x80, 10);
                func_0016CB60(u, port, 0, 1, 10);
            }
        } else {
            int guard = func_0016A210(u, v, hit);
            int stand = func_0016A3D0(u, v, hit);
            int kind;

            if (v != 0 && (U16(hit, 0x1C) & 0x200) && PTR(v, 0x288) != 0)
                func_003DD5B0(U8(PTR(v, 0x288), 0x180), 3);
            kind = func_0016A340(v, hit);
            if (U8(u, 0x157) != 0 || S16(u, 0x194) != 0) {
                short d = func_001CCD60(u, PS2_ADDR(v), hit, pos);

                func_00153230(u, v, hit, dir, d, guard_kind, 1);
                BIT(u, 0x19D, 1) = 0;
                F32(u, 0x22C) = 0.0f;
                g_70000D60 = 1;
                func_001C8130(5, PS2_ADDR(&F32(u, 0x90)), 0, 8, U8(u, 0x14E));
                func_0016A6E0(u, hit, dir, d);
                *damage = 0;
                stand = 1;
            } else {
                *damage = func_001CD060(u, v, hit, dir, pos, kind, guard, stand, 0, 0);
            }
            if (0.0001f < F32(u, 0x168))
                func_0016A820(u, *damage);
            if (func_00153E50(u, v, hit, PS2_ADDR(pos), dir, *damage, stand) != 0 && PTR(u, 0x288) != 0)
                func_001CF2A0(u, func_0016BE40(u), 1);
            U8(u, 0x17D) += 1;
            if (U8(u, 0x14E) < 2) {
                u8 port = g_00669E2A[U8(u, 0x14E)][0];

                if (stand == 0)
                    func_0016CB60(u, port, 1, 0xA0, 0x14);
                else
                    func_0016CB60(u, port, 1, 0, 0);
                func_0016CB60(u, port, 0, 1, 0xF);
            }
            got = 1;
        }
        PTR(u, 0x140) = v;
    }
    if (U32(hit, 0x28) & 0x80000000)
        U8(u, 0x14C) = alpha;
    else
        U8(u, 0x14C) = 0x40;
    return got;
}

extern u32 g_00669DE8[][0x12];           /* per player (0x48 bytes): +0 the officer's item list */
extern u8 g_004282AF;                    /* the item effect's divisor */

void func_002F00F0(u8 player, int kind);
int func_0016C180(float amount, Unit *u);
int func_0016D780(float a, float b, float *part, float *point, float *out);

/* An officer's life raised by `n`, at most its maximum (+0x80) and at least 0; the highest
 * reached is kept (+0x84). */
static inline void officer_heal(u8 *o, short n)
{
    short max = S16(o, 0x80), v = S16(o, 0x82) + n;

    if (max < v)
        v = max;
    if (v < 1)
        v = 0;
    S16(o, 0x82) = v;
    if (S16(o, 0x84) < v)
        S16(o, 0x84) = v;
}

/* 0x0016AFE0, 0x250 bytes. A unit picks up a healing item: its officer heals 50 (more with the
 * players' item 0x1E: 1 + its level / g_004282AF times); not for officers with flag 2. */
void func_0016AFE0(Unit *u, u8 alpha)
{
    u8 *o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    u32 f = U32(o, 0xB8), list = 0x1A;
    int src = 2, msg = 6;
    float k = 1.0f;

    if ((f & 2) == 0) {
        if (f & 4) {
            src = 0;
            list = g_00669DE8[0][0];
        } else if (f & 8) {
            src = 1;
            list = g_00669DE8[1][0];
        }
        if (src != 2 && func_0036DC80(list, 0x1E) != 0) {
            k = (float)func_0036DBA0(list, 0x1E) / (float)g_004282AF + 1.0f;
            msg = func_0036DBA0(list, 0x1E) - 1;
        }
        officer_heal(o, (short)(int)(k * 50.0f));
        func_00247FA0(U8(u, 0x14E), 1, msg);
    }
    U8(u, 0x14C) = alpha;
}

/* 0x0016B230, 0x26C bytes. A unit opens a box: at random 10% heals 50, 40% doubles its attack
 * (+0x98, flag 0x8000000), 40% its defence (+0x9C, flag 0x10000000), 10% +0xA9 (flag
 * 0x20000000), each for 500 frames (+0xA4); a message, and the players' display. */
void func_0016B230(Unit *u, u8 alpha)
{
    u8 *o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    u32 r;

    if ((U32(o, 0xB8) & 2) == 0) {
        r = RANDOM() % 100;
        if (r < 10) {
            officer_heal(o, 0x32);
            func_00247FA0(U8(u, 0x14E), 1, 6);
        } else if (r < 0x32) {
            U32(o, 0xBC) |= 0x8000000;
            F32(o, 0x98) = 2.0f;
            U16(o, 0xA4) = 500;
            func_00247FA0(U8(u, 0x14E), 9, 6);
            if (U8(u, 0x14E) < 2)
                func_002F00F0(U8(u, 0x14E), 0);
        } else if (r < 0x5A) {
            U32(o, 0xBC) |= 0x10000000;
            F32(o, 0x9C) = 2.0f;
            U16(o, 0xA4) = 500;
            func_00247FA0(U8(u, 0x14E), 0xB, 6);
            if (U8(u, 0x14E) < 2)
                func_002F00F0(U8(u, 0x14E), 1);
        } else {
            U32(o, 0xBC) |= 0x20000000;
            U8(o, 0xA9) = 1;
            U16(o, 0xA4) = 500;
            func_00247FA0(U8(u, 0x14E), 0xF, 6);
            if (U8(u, 0x14E) < 2)
                func_002F00F0(U8(u, 0x14E), 2);
        }
    }
    U8(u, 0x14C) = alpha;
}

/* 0x0016B4A0, 0xA4 bytes. A player's unit (not held) gains musou: 21 + the item level / 49. */
void func_0016B4A0(Unit *u)
{
    u8 p = U8(u, 0x14E);

    if (p < 2 && BIT(u, 0x19C, 1) == 0) {
        u8 b = func_002F41E0(g_00669DE8[p][0]);

        func_0016C180((float)b / 49.0f + 1.0f + 20.0f, u);
    }
}

/* 0x0016B550, 0xD8 bytes. Tests a weapon part (its point +0x40, rotation +0x50 and its edge
 * +0x20 to +0x30) against the unit's body (a cylinder from +0x90 up by the state's height,
 * radius / height +0x84 / +0x88 of the state description); *out: the edge's end. Whether it
 * touches. */
int func_0016B550(Unit *u, u8 *part, float *out)
{
    float s[5][4], pt[4];
    int k, r;

    for (k = 0; k < 4; k++) {
        s[0][k] = F32(part, 0x40 + k * 4);
        s[4][k] = F32(part, 0x40 + k * 4);
        s[1][k] = F32(part, 0x50 + k * 4);
        s[2][k] = F32(part, 0x30 + k * 4);
        s[3][k] = F32(part, 0x20 + k * 4);
    }
    pt[0] = F32(u, 0x90);
    pt[2] = F32(u, 0x98);
    pt[3] = F32(u, 0x9C);
    pt[1] = F32(u, 0x94) + F32(PTR(u, 0x114), 0x80);
    r = func_0016D780(F32(PTR(u, 0x114), 0x84), F32(PTR(u, 0x114), 0x88), s[0], pt, out);
    for (k = 0; k < 4; k++) {
        out[k] = F32(part, 0x30 + k * 4) - F32(part, 0x20 + k * 4);
        out[k] = out[k] + F32(part, 0x20 + k * 4);
    }
    return r;
}

/* 0x0016B630, 0xE8 bytes. Whether a drawn part of weapon `w` (+0x50 / +0x54, +0x58 / +0x5C)
 * touches unit `u`. */
int func_0016B630(u8 *w, Unit *u, float *out)
{
    int r = 0, i;

    for (i = 0; i < 2; i++) {
        u8 *p = PTR(w, 0x50 + i * 4);

        if (p != 0 && BIT(p, 0x60, 1))
            r |= func_0016B550(u, p, out);
    }
    for (i = 0; i < 2; i++) {
        u8 *p = PTR(w, 0x58 + i * 4);

        if (p != 0 && BIT(p, 0x60, 1))
            r |= func_0016B550(u, p, out);
    }
    return r;
}

extern u32 g_00669F60;                   /* battle flags */

int func_001BEA70(u8 kind);

/* `p` against the unit's body cylinder (radius +0x88, height +0x84 of the state description):
 * within `up` of half its height and `r` + radius of its axis (flat); *out the point on the body
 * towards `p`, at p's height. */
static inline int body_touch(Unit *u, float *p, float r, float up, float *out)
{
    float R = F32(PTR(u, 0x114), 0x88), d[4], l2, l;
    int k;

    for (k = 0; k < 4; k++)
        d[k] = p[k] - F32(u, 0x90 + k * 4);
    if (!(fabsf(d[1]) < F32(PTR(u, 0x114), 0x84) * 0.5f + up))
        return 0;
    l2 = d[0] * d[0] + d[2] * d[2];
    if (!(l2 < (r + R) * (r + R)))
        return 0;
    l = sqrtf(l2);
    for (k = 0; k < 4; k++)
        out[k] = d[k] / l * R + F32(u, 0x90 + k * 4);
    out[1] = p[1];
    out[3] = 1.0f;
    return 1;
}

/* 0x0016B720, 0x130 bytes. Whether a sphere of radius `r` at `p` touches the unit's body. */
int func_0016B720(float r, Unit *u, float *p, float *out)
{
    return body_touch(u, p, r, r, out);
}

/* 0x0016B850, 0x15C bytes. The same for an ellipsoid (`r` across, `up` high; a sphere when they
 * differ by less than 10). */
int func_0016B850(float r, float up, Unit *u, float *p, void *unused, float *out)
{
    if (fabsf(r - up) < 10.0f)
        return func_0016B720(r, u, p, out);
    return body_touch(u, p, r, up, out);
}

/* 0x0016B9B0, 0x374 bytes. Whether `u` cannot be hit by `v`'s hit `hit` (`alpha`: the hit's
 * flash): held units, players in some battle states, units leaving, units with flag 8 of +0x19D
 * (unless the hit has flag 2), players and their mounts during the duel, grabs on mounts,
 * guarding units (+0x13C flag 0x40), a unit already hit by this attack (flash, or the weapon kind
 * bit in +0x120 of `v`), carried units, actions with flag 0x2000; a mount follows its rider. */
int func_0016B9B0(Unit *u, Unit *v, u8 *hit, u8 alpha)
{
    int k;

    if (BIT(u, 0x19C, 1))
        return 1;
    if (U8(u, 0x14E) < 2 && (g_00669F60 & 0x4000000))
        return 1;
    if (BIT(u, 0x19C, 7))
        return 1;
    if (BIT(u, 0x19D, 3) && (U32(hit, 0x2C) & 2) == 0)
        return 1;
    if (g_0045D2A8 != 0) {
        if (U8(u, 0x14E) < 2)
            return 1;
        k = S32(u, 0x118) == 0x3C || (u32)(S32(u, 0x118) - 0x3D) < 3;
        if (k && PTR(u, 0x28C) != 0 && U8(PTR(u, 0x28C), 0x14E) < 2)
            return 1;
    }
    if ((u32)(S32(u, 0x118) - 0x3D) < 3 && (U32(hit, 0x2C) & 0x400))
        return 1;
    if (U32(u, 0x13C) & 0x40) {
        u8 kind = PTR(u, 0x110) == 0 ? 0x6A : U8(PTR(u, 0x110), 0x1C);

        if (func_001BEA70(kind) == 0
            && (func_002732F0(u) != 0
                || ((U32(PTR(u, 0x210), 0x1C) & 0x400) && (U32(PTR(u, 0x210), 0x18) & 0x20) == 0)))
            return 1;
    }
    if ((U32(hit, 0x28) & 0x80000000) == 0) {
        if ((U32(hit, 0x28) & 0x40000000) == 0 && v != 0) {
            if (BIT(v, 0x19C, 7) && (U32(hit, 0x2C) & 0x400))
                return 1;
            if (PTR(u, 0x11C) != 0
                && (*(u64 *)(v + 0x120) & (u64)(long long)(1 << U8(PTR(u, 0x11C), 0x202))))
                return 1;
        }
    } else if (U8(u, 0x14C) == alpha) {
        return 1;
    }
    if (PTR(u, 0x280) != 0) {
        u8 *g = PTR(u, 0x280);

        if (PTR(g, 0x284) != 0 && (char)U8(g, 0x275) != -1)
            return 1;
    }
    if (PTR(u, 0x284) != 0 && (char)U8(u, 0x275) != -1)
        return 1;
    {
        u32 f = U32(PTR(u, 0x210), 0x18);

        if ((f & 0x2000) == 0 || ((f & 0x40) && (U32(hit, 0x2C) & 2))) {
            u8 *m = PTR(u, 0x28C);

            if (m == 0)
                return S32(u, 0x118) == 0x3C;
            if (m == v)
                return 1;
            return func_0016B9B0(m, v, hit, alpha);
        }
    }
    return 1;
}

/* 0x0016BD30, 0x48 bytes. Lets go of the unit held (+0x280): its kept positions set to where
 * the holder is, the links cleared. */
void func_0016BD30(Unit *u)
{
    u8 *g = PTR(u, 0x280);
    int k;

    for (k = 0; k < 4; k++)
        F32(g, 0xB0 + k * 4) = F32(u, 0x90 + k * 4);
    g = PTR(u, 0x280);
    for (k = 0; k < 4; k++)
        F32(g, 0xA0 + k * 4) = F32(u, 0x40 + k * 4);
    g = PTR(u, 0x280);
    PTR(u, 0x280) = 0;
    PTR(g, 0x284) = 0;
    U8(g, 0x275) = 0xFF;
    U8(g, 0x276) = 0xFF;
}

/* 0x0016BD80, 0xB4 bytes. Puts a rider on mount `m` (seat node `node`): action 0x57, its
 * place and rotation the mount's, its root offset; func_001CF000. */
void func_0016BD80(Unit *u, Unit *m, u8 node)
{
    int k;

    func_00150BB0(u);
    PTR(u, 0x288) = m;
    U8(u, 0x274) = node;
    PTR(m, 0x28C) = u;
    func_0015FB50(u, 0x57);
    for (k = 0; k < 4; k++)
        F32(u, 0x40 + k * 4) = F32(m, 0x40 + k * 4);
    for (k = 0; k < 4; k++)
        F32(u, 0x50 + k * 4) = F32(m, 0x50 + k * 4);
    func_00167730(u);
    func_001CF000(u, m);
    for (k = 0; k < 4; k++)
        F32(u, 0xB0 + k * 4) = F32(u, 0x90 + k * 4);
    for (k = 0; k < 4; k++)
        F32(u, 0xA0 + k * 4) = F32(u, 0x40 + k * 4);
}

/* 0x0016BE40, 0x10 bytes, matching. Gets off the mount; returns it. */
Unit *func_0016BE40(Unit *u)
{
    u8 *m = PTR(u, 0x288);

    PTR(u, 0x288) = 0;
    PTR(m, 0x28C) = 0;
    return m;
}

/* 0x0016BE50, 0xB8 bytes, matching. The unit's speed-up (*rate): 2 during hits with flag 0x1000; on foot
 * while held, 1.5 / 1.7 / 2 by +0x182; else 1. Whether it is sped up. */
int func_0016BE50(Unit *u, float *rate)
{
    u8 *h = PTR(PTR(u, 0x210), 0x14);

    if ((h != 0 ? U32(h, 0x28) & 0x1000 : 0) != 0) {
        *rate = 2.0f;
        return 1;
    }
    if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0 && BIT(u, 0x19C, 1)) {
        if (U8(u, 0x182) == 0)
            *rate = 1.5f;
        else if (U8(u, 0x182) == 1)
            *rate = 1.7f;
        else
            *rate = 2.0f;
        return 1;
    }
    *rate = 1.0f;
    return 0;
}

/* 0x0016BF10, 0xB4 bytes. The unit's weapon reach: the officer's (+0xA0), +30 (+50 with
 * +0x18B) while +0x168 lasts, +20 more with func_00273A20. */
float func_0016BF10(Unit *u)
{
    float r = F32((g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0), 0xA0);

    if (0.0001f < F32(u, 0x168)) {
        if (U8(u, 0x18B) == 0)
            r = r + 30.0f;
        else if (U8(u, 0x18B) != 0)
            r = r + 50.0f;
        if (func_00273A20(u) != 0)
            r = r + 20.0f;
    }
    return r;
}

/* 0x0016BFD0, 0x50 bytes. Forgets the target `x` (its id +0x94) in the unit's target slots
 * (+0x258, +0x260-0x26A). */
void func_0016BFD0(Unit *u, u8 *x)
{
    int k;

    if (U16(x, 0x94) == S16(u, 0x258))
        S16(u, 0x258) = -1;
    for (k = 0; k < 6; k++) {
        if (U16(x, 0x94) == S16(u, 0x260 + k * 2))
            S16(u, 0x260 + k * 2) = -1;
    }
}

/* 0x0016C020, 0x20 bytes, matching. Whether the unit's action can be interrupted. */
int func_0016C020(Unit *u)
{
    return ((U32(PTR(u, 0x210), 0x18) & 0x40000860) != 0) ^ 1;
}

/* 0x0016C040, 0x30 bytes, matching. The officer's flag 0x200 (a major officer). */
int func_0016C040(Unit *u)
{
    return U32(g_00693970 + S16(u, 0x178) * 0xC0, 0x100C0 + 0xB8) & 0x200;
}

/* 0x0016C070, 0x34 bytes, matching. Whether the officer is beaten (flag 2). */
int func_0016C070(Unit *u)
{
    return (U32(g_00693970 + S16(u, 0x178) * 0xC0, 0x100C0 + 0xB8) & 2) != 0;
}

/* 0x0016C0B0, 0xCC bytes. Knocks the last unit hit (+0x140) away from this one: its push
 * direction (+0x1F0, flat), and speed (120 on foot, 5 and 5 in the air). */
void func_0016C0B0(Unit *u)
{
    u8 *v = PTR(u, 0x140);
    float l;
    int k;

    if (v == 0 || BIT(v, 0x19D, 1))
        return;
    BIT(v, 0x19D, 1) = 1;
    for (k = 0; k < 4; k++)
        F32(v, 0x1F0 + k * 4) = F32(v, 0x90 + k * 4) - F32(u, 0x90 + k * 4);
    F32(v, 0x1F4) = 0.0f;
    l = sqrtf(F32(v, 0x1F0) * F32(v, 0x1F0) + F32(v, 0x1F4) * F32(v, 0x1F4) + F32(v, 0x1F8) * F32(v, 0x1F8));
    for (k = 0; k < 4; k++)
        F32(v, 0x1F0 + k * 4) = F32(v, 0x1F0 + k * 4) / l;
    if ((U32(PTR(v, 0x210), 0x18) & 0x20) == 0) {
        F32(v, 0x22C) = 120.0f;
    } else {
        F32(v, 0x224) = 5.0f;
        F32(v, 0x22C) = 5.0f;
    }
}

extern int g_00669F9C;                   /* the battle's frame counter */

void func_002A6D20(u8 player, int sound);

/* 0x0016C180, 0x2F0 bytes. Adds `amount` to the officer's musou gauge (+0x88, at most +0x86),
 * times 1 + its +0xA8 / 10 (and the players' item 8 percent); fractions in sixteenths kept at
 * +0x1BC. A player hears a sound when a bar fills (another one for the last); full bars start
 * func_002539F0. Whether the gauge is full. */
int func_0016C180(float amount, Unit *u)
{
    u8 *o;
    short max, cur, n, v, w;
    float k;

    if (BIT(u, 0x19C, 7))
        return 0;
    o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    if (U32(o, 0xB8) & 2)
        return 0;
    max = S16(o, 0x86);
    cur = S16(o, 0x88);
    k = (float)U8(o, 0xA8) * 0.1f + 1.0f;
    if (U8(u, 0x14E) < 2)
        k = k * ((float)func_0019B410(g_00669DE8[U8(u, 0x14E)][0], 8) * 0.01f + 1.0f);
    n = (short)(int)(amount * k);
    v = cur + n;
    U8(u, 0x1BC) = U8(u, 0x1BC) + (char)(int)((amount * k - (float)(int)n) * 16.0f);
    if (U8(u, 0x1BC) > 0xF) {
        v = v + 1;
        U8(u, 0x1BC) &= 0xF;
    }
    if (max < v)
        v = max;
    w = v < 1 ? 0 : v;
    S16(o, 0x88) = w;
    if (U8(u, 0x14E) < 2) {
        short bar = func_00271210(u);

        if (bar <= v)
            func_002539F0(u);
        if (v / bar != cur / bar)
            func_002A6D20(U8(u, 0x14E), v / bar == max / bar ? 0x23B : 0x248);
    }
    return v == max;
}

/* 0x0016C470, 0x44 bytes, matching. func_0016C180, then func_00253A60 when the gauge is full. */
int func_0016C470(float amount, Unit *u)
{
    int r = func_0016C180(amount, u);

    if (r != 0)
        func_00253A60(u);
    return r;
}

/* 0x0016C4C0, 0x15C bytes. Spends `n` of the musou gauge (not during hits with flag 0x200 or
 * the slow-motion duel). Whether it ran out (then 0). */
int func_0016C4C0(Unit *u, short n)
{
    u8 *h, *o;
    short v;

    if (BIT(u, 0x19C, 7))
        return 0;
    h = PTR(PTR(u, 0x210), 0x14);
    if ((h != 0 ? U32(h, 0x28) & 0x200 : 0) != 0)
        return 0;
    if (g_0045D2A8 != 0)
        return 0;
    o = (g_00693970 + S16(u, 0x178) * 0xC0 + 0x100C0);
    v = S16(o, 0x88) - n;
    if (v < 1) {
        S16(o, 0x88) = 0;
        return 1;
    }
    if (S16(o, 0x86) < v)
        v = S16(o, 0x86);
    S16(o, 0x88) = v < 1 ? 0 : v;
    return 0;
}

/* 0x0016C620, 0x174 bytes. The musou gauge each frame: while the musou attack runs (flag 2 of
 * +0x19C) it drains by 1 (every other frame with func_003E2DC0) and the attack ends when empty
 * (on foot after func_00271610, mounted for actions with flag 0x400000); func_002715C0 ends it at
 * once. Otherwise some hits (+0x28 flags 0x1C) cost 1. */
void func_0016C620(Unit *u)
{
    if (BIT(u, 0x19C, 1) == 0) {
        u8 *h = PTR(PTR(u, 0x210), 0x14);

        if ((h != 0 ? U32(h, 0x28) & 0x1C : 0) != 0)
            func_0016C4C0(u, 1);
        return;
    }
    if (func_003E2DC0(PS2_ADDR(u)) != 0 && g_00669F9C % 2 != 0)
        return;
    if (func_002715C0(u) != 0) {
        func_00151A90(u, 0);
        BIT(u, 0x19C, 1) = 0;
    } else if ((U32(PTR(u, 0x210), 0x18) & 0x8000000) == 0) {
        if (func_0016C4C0(u, 1) != 0 && func_00271610(F32(u, 0x248), u) != 0)
            func_00151C60(u);
    } else if (func_0016C4C0(u, 1) != 0 && (U32(PTR(u, 0x210), 0x18) & 0x400000)
               && (U32(u, 0x13C) & 0x20000) == 0) {
        func_00151C60(u);
    }
}

/* 0x0016C7A0, 0x64 bytes. Clears the 30 records (0x40 bytes) of player `p`'s list at
 * 0x56CCE0 (+0x2C: none). */
void func_0016C7A0(int p)
{
    u8 *r = (u8 *)PS2_PTR(0x56CCE0) + p * 0x780;
    int k;

    for (k = 0; k < 0x1E; k++) {
        func_00118850(r, 0x40);
        S16(r, 0x2C) = -1;
        r += 0x40;
    }
}

extern u8 g_00574DE0[][0x630];           /* the units */

int func_001BEA50(u8 kind);

/* 0x0016C810, 0x16C bytes. Pushes a record at the front of player `p`'s list of 30 (the others
 * move back one; the last drops): points `a`, `b`, `c`, value `t`, `id` and `flag`. */
void func_0016C810(float t, int p, float *a, float *b, float *c, short id, int flag)
{
    u8 *list = (u8 *)PS2_PTR(0x56CCE0) + p * 0x780;
    int k, i;

    for (k = 0x1D; k > 0; k--)
        for (i = 0; i < 0x10; i++)
            ((u32 *)(list + k * 0x40))[i] = ((u32 *)(list + (k - 1) * 0x40))[i];
    for (i = 0; i < 4; i++) {
        F32(list, i * 4) = a[i];
        F32(list, 0x10 + i * 4) = b[i];
        F32(list, 0x30 + i * 4) = c[i];
    }
    S16(list, 0x2C) = id;
    F32(list, 0x20) = t;
    U16(list, 0x2E) = flag != 0;
}

/* 0x0016C980, 0x24 bytes, matching. Record `k` of player `p`'s list. */
extern u8 g_0056CCE0[][0x1E][0x40];      /* the players' lists of 30 records */

u8 *func_0016C980(int p, int k)
{
    return g_0056CCE0[p][k];
}

/* 0x0016C9B0, 0x4C bytes. Stops the unit's sound (+0x128) and plays sound 0x23E. */
void func_0016C9B0(Unit *u)
{
    if (S32(u, 0x128) != -1) {
        func_002A5B10();
        S32(u, 0x128) = -1;
    }
    func_002A6770(U8(u, 0x14E), 0x23E);
}

/* 0x0016CA00, 0x10 bytes, matching. Bit 2 of +0xE8. */
typedef struct {
    u8 low : 2;
    u8 bit2 : 1;
} Bits_E8;

u32 func_0016CA00(u8 *x)
{
    return ((Bits_E8 *)(x + 0xE8))->bit2;
}

/* 0x0016CA10, 0x104 bytes. A bodyguard's share (+0x15A: its kind; +0x15B its leader): 1/3 for
 * kind 3, by the leader's +0x196 for kinds 0 and 1 (1/3, 1/4, else 1/5), else 1; halved when the
 * leader's officer has flag 0x8000000. */
float func_0016CA10(Unit *u)
{
    u8 *l = g_00574DE0[U8(u, 0x15B)];
    char k = U8(u, 0x15A);
    float f = 1.0f;

    if (k == 3) {
        f = 0.33333f;
    } else if (k == 1 || k == 0) {
        if (U8(l, 0x196) == 1)
            f = 0.33333f;
        else if (U8(l, 0x196) == 2)
            f = 0.25f;
        else
            f = 0.2f;
    }
    if (U32((g_00693970 + S16(l, 0x178) * 0xC0 + 0x100C0), 0xBC) & 0x8000000)
        f = f * 0.5f;
    return f;
}

/* 0x0016CB20, 0x34 bytes, matching. func_001BEA50 for the unit's weapon kind (0x6A without one). */
int func_0016CB20(Unit *u)
{
    return func_001BEA50(PTR(u, 0x110) != 0 ? U8(PTR(u, 0x110), 0x1C) : 0x6A);
}

/* 0x0016CB60, 0x70 bytes. Vibrates a pad, unless vibration is off (battle flag 0x10) or flag
 * 0x10 is set on the officer numbered like the player (as in the original). */
void func_0016CB60(Unit *u, u8 port, int motor, int power, int frames)
{
    if ((g_00669F60 & 0x10) == 0 && (U32(g_006A3A30[U8(u, 0x14E)], 0xB8) & 0x10) == 0)
        func_00103630(port, motor, power, frames);
}

/* 0x0016CBD0, 0xA4 bytes, matching. The weapon kind shown for kinds 0x85-0x8C. */
int func_0016CBD0(int k)
{
    if (k == 0x85)
        k = 0x68;
    else if (k == 0x86)
        k = 0x69;
    else if (k == 0x87)
        k = 0x6A;
    else if (k == 0x88)
        k = 0x78;
    else if (k == 0x89)
        k = 0x6C;
    else if (k == 0x8A)
        k = 0x6D;
    else if (k == 0x8B)
        k = 0x6E;
    else if (k == 0x8C)
        k = 0x6F;
    return k;
}

/* 0x0016CC80, 0x58 bytes. The same by arithmetic (0x85-0x87 and 0x89-0x8C minus 0x1D). */
int func_0016CC80(int k)
{
    if (k < 0x85 || k > 0x87) {
        if (k == 0x88)
            k = 0x78;
        else if (k > 0x88 && k < 0x8D)
            k = k - 0x1D;
    } else {
        k = k - 0x1D;
    }
    return k;
}

/* 0x0016CCE0, 0x48 bytes, matching. The kind of an extra weapon: for kinds 0x1B / 0x1A, func_002F57F0
 * of `b` plus 0x89 / 0x85; else `b`. */
int func_0016CCE0(int a, int b)
{
    if (a == 0x1B)
        b = func_002F57F0(b) + 0x89;
    else if (a == 0x1A)
        b = func_002F57F0(b) + 0x85;
    return b;
}
