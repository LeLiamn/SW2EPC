/*
 * unit_setup.c - setting up battlefield units (original source file unknown; from 0x00164680,
 * after camera.c, up to Weapon.c at 0x0016CD30).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units (0x630 bytes) are reached by offset as in unit.c:
 * +0x40 position, +0x50 rotation, +0x60 scale, +0x118 state, +0x14E player, +0x290 four motion
 * slots of 0x70, +0x450 ten records of 0x30.
 */

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

extern u32 g_00424B30[10];               /* the ten records' kinds */

void func_001185E0(void *p, int size, int value);  /* memset */
void func_00150B20(Unit *u);
void func_00166160(Unit *u);
void func_00165560(Unit *u);
void func_0016E2E0(u8 *slot);
u8 *func_001BE4F0(void);
u8 *func_001BE540(void);
u8 *func_001BE770(void);
void func_001649C0(Unit *u);

/* The matrix of rotation `rot` and position `pos` (VU0 micro subroutine 0x50) into m. */
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
    if ((U8(u, 0x19C) & 0x80) || (U8(u, 0x1BA) > 3 && S32(u, 0x118) < 0x3C)) {
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
    U8(u, 0x198) = (U8(u, 0x198) & ~1) | 1;
    U16(u, 0x178) = 0xFFFF;
    for (i = 0; i < 4; i++)
        func_0016E2E0(u + 0x290 + i * 0x70);
    r = u + 0x450;
    for (i = 0; i < 10; i++) {
        func_001185E0(r, 0x30, 0);
        U32(r, 0x20) = g_00424B30[i];
        U8(r, 0x24) &= ~1;
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

    U8(u, 0x2DC) &= ~2;
    U8(u, 0x34C) &= ~2;
    U8(u, 0x3BC) &= ~2;
    U8(u, 0x42C) &= ~2;
    for (i = 0; i < 10; i += 5) {
        U8(r, 0x24) &= ~1;
        U8(r, 0x54) &= ~1;
        U8(r, 0x84) &= ~1;
        U8(r, 0xB4) &= ~1;
        U8(r, 0xE4) &= ~1;
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

u8 *func_0016CF30(u8 kind);
int func_0016E300(u8 *slot, char motion, char node, int c, int b, int a);
void func_0016E910(u8 *slot);
void func_001F2BF0(u8 *probe);
void func_00150930(Unit *u);
void func_00149620(Actor *a, Model *m, Model *m2);
void func_00149720(Actor *a);
u8 *func_002A7E70(void);
Model *func_002A7E30(u8 kind);
void func_0014FCA0(u8 *o, Model *m);
void func_002AD760(u8 kind, u8 *out);
void func_00240B30(Unit *u);

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
            if (U8(s, 0x2DC) & 4) {
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

    U8(PTR(u, 0x11C), 0x20C) &= ~1;
    PTR(u, 0x11C) = 0;
    PTR(u, 0x130) = 0;
    for (k = 0; k < 4; k++) {
        if (U8(u + k * 0x70, 0x2DC) & 1)
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
        u8 *w = func_002A7E70();

        PTR(u, 0x134) = w;
        if (w != 0) {
            U8(w, 0x168) = (U8(w, 0x168) & ~1) | 1;
            U8(PTR(u, 0x134), 0x165) = 9;
            func_0014FCA0(PTR(u, 0x134), func_002A7E30(U8(u, 0x156)));
        } else {
            U8(u, 0x156) = 0x11;
        }
    }
    if (S32(u, 0x118) == 0x3C)
        func_002AD760(U8(u, 0x180), u + 0x1A0);
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
    U8(u, 0x198) = (U8(u, 0x198) & ~0x10) | 0x10;
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
    U8(PTR(u, 0x11C), 0x20C) = (U8(PTR(u, 0x11C), 0x20C) & ~1) | 1;
    PTR(PTR(u, 0x11C), 0x208) = 0;
    U8(PTR(u, 0x11C), 0x20C) = (U8(PTR(u, 0x11C), 0x20C) & ~4) | 4;
    if (U32(t, 0xD8) == 0) {
        func_00149620(PTR(u, 0x11C), t + 0xA0, 0);
    } else {
        u8 *a = PTR(u, 0x11C);

        if (PTR(a, 0x1F4) == 0) {
            U8(a, 0x20C) &= ~1;
            PTR(u, 0x11C) = 0;
            return 0;
        }
        func_00149620(a, t + 0xA0, t + 0xD0);
    }
    PTR(u, 0x130) = t;
    if (U8(u, 0x158) < 0x8D) {
        if (func_00164B40(u, 0) == 0)
            return drop_actor(u);
        U8(u, 0x19D) &= ~1;
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
    U8(PTR(u, 0x11C), 0x20C) = (U8(PTR(u, 0x11C), 0x20C) & ~1) | 1;
    PTR(PTR(u, 0x11C), 0x208) = 0;
    U8(PTR(u, 0x11C), 0x20C) = (U8(PTR(u, 0x11C), 0x20C) & ~4) | 4;
    if (U32(t, 0xD8) == 0) {
        func_00149620(PTR(u, 0x11C), t2 + 0xA0, 0);
    } else {
        u8 *a = PTR(u, 0x11C);

        if (PTR(a, 0x1F4) == 0) {
            U8(a, 0x20C) &= ~1;
            PTR(u, 0x11C) = 0;
            return 0;
        }
        func_00149620(a, t2 + 0xA0, t + 0xD0);
    }
    PTR(u, 0x130) = t2;
    if (U8(u, 0x158) < 0x8D) {
        if (func_00164B40(u, 0) == 0)
            return drop_actor(u);
        U8(u, 0x19D) &= ~1;
    }
    setup_rest(u, keep, 0);
    return 1;
}

/* The state records really start 0x10 bytes before g_006CDF60 (+4: the state's model, 0 = none). */
#define STATE_REC(s) (g_006CDF60[s] - 0x10)

extern u8 g_005B50A0[][0xD0];            /* the unit descriptions (+0x10 flag 1: usable, +0x1C weapon kind) */
extern u8 g_006A3A30[][0xC0];            /* the officers (+0x10 record, +0x82 life, +0xB8 flags) */
extern u8 *g_0045D300;                   /* (small data) the state descriptions (0xA0 each) */
extern float g_004064D0[4][4];           /* the unit colours by player (the first: the default) */
extern float g_00406510[4][4], g_00406550[4][4], g_00406590[4][4];  /* states 0x2E, 0x31, 0x32 */

void func_0016BD30(Unit *u);
void func_00150A10(Unit *u);
void func_002AD8B0(u8 *horse);
void func_002406D0(u8 player);
float func_003E6EC0(void);
void func_001F5370(Unit *u);

/* 0x00165560, 0x17C bytes. Takes a unit's model away: the actor, the partner (+0x270), the
 * grab (+0x280), the slots, the weapon model, the records and the horse. */
void func_00165560(Unit *u)
{
    u8 *a = PTR(u, 0x11C), *v;
    int k;

    PTR(a, 0x1FC) = 0;
    U8(a, 0x201) = 0;
    U8(PTR(u, 0x11C), 0x20C) &= ~1;
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
    U8(u, 0x19D) &= ~1;
    for (k = 0; k < 4; k++) {
        if (U8(u + k * 0x70, 0x2DC) & 1)
            func_0016E910(u + k * 0x70 + 0x290);
    }
    PTR(u, 0x130) = 0;
    if (PTR(u, 0x134) != 0) {
        func_0014FCA0(PTR(u, 0x134), 0);
        U8(PTR(u, 0x134), 0x168) &= ~1;
        PTR(u, 0x134) = 0;
    }
    func_001649C0(u);
    func_002AD8B0(u + 0x1A0);
    U32(u, 0x16C) = 0;
    U8(u, 0x19E) &= ~0x20;
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
    U8(u, 0x198) = (U8(u, 0x198) & ~2) | 2;
    U8(u, 0x19C) = (U8(u, 0x19C) & ~0x10) | 0x10;
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
    U8(u, 0x198) &= ~0x20;
    U16(u, 0x1CC) = 0xFFFF;
    U16(u, 0x1CE) = 0xFFFF;
    o = g_006A3A30[S16(u, 0x178)];
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
            S16(u, 0x1B8) = (short)(int)((float)(int)S16(o, 0x82) * func_003E6EC0());
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
int func_00165C60(Unit *u, int state, int kind, u8 slot_kind, u8 weapon, u8 b154, u8 b14f,
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
    if ((U8(u, 0x19E) & 0x40) == 0)
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
#define g_700000C0 ((float *)0x700000C0)  /* (scratchpad) a zero vector */

int func_0016C070(Unit *u);
void func_001F54B0(Unit *u);
void func_001F5420(Unit *u);
void func_00151A90(Unit *u, int a);
void func_0015FB70(Unit *u);
void func_00150BB0(Unit *u);
void func_001AE090(u8 *rec);
void func_00253800(Unit *u);
void func_002A5B10(void);
void func_0016C620(Unit *u);
void func_0016C470(float amount, Unit *u);
void func_0029F930(float dt, Unit *u);
void func_001CEBC0(Unit *u);

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
    if (U8(u, 0x19C) & 2)
        func_00151A90(u, 1);
    if (U8(u, 0x27C) & 4)
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
    if ((U8(u, 0x198) & 2) == 0)
        return;
    if (PTR(u, 0x11C) != 0)
        func_00165560(u);
    if (g_00669DB8 != 4 && g_00669DB8 != 2)
        func_00253800(u);
    if (U8(u, 0x19C) & 2) {
        func_00151A90(u, 1);
        U8(u, 0x19C) &= ~2;
    }
    PTR(u, 0x114) = 0;
    PTR(u, 0x110) = 0;
    S32(u, 0x118) = 0x40;
    U8(u, 0x156) = 0x11;
    U8(u, 0x154) = 3;
    U8(u, 0x14F) = 0xFF;
    U8(u, 0x198) &= ~2;
    U8(u, 0x19E) &= ~0x20;
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
    U8(u, 0x198) &= ~0x20;
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
    if ((U8(u, 0x19C) & 2) == 0) {
        u8 *o = g_006A3A30[S16(u, 0x178)];
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
    if (U8(u, 0x19C) & 4) {
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
        if ((U8(u, 0x19C) & 0x80) == 0)
            U8(u, 0x14D) = 0x80;
    } else {
        if ((U8(u, 0x19C) & 4) && func_0016C070(u) != 0) {
            f = (float)U16(u, 0x12C) * 128.0f / ((float)U16(u, 0x12E) - 16.0f);
            if (128.0f <= f)
                f = 128.0f;
        } else {
            f = (float)U16(u, 0x12C) * 128.0f / (float)U16(u, 0x12E);
        }
        U8(u, 0x14D) = (int)f < 0x80 ? (u8)(int)f : 0x80;
    }
    if ((U8(u, 0x19C) & 8) && PTR(u, 0x11C) != 0) {
        if (U16(u, 0x12C) < U16(u, 0x12E))
            U16(u, 0x12C) += 1;
        if (S16(u, 0x12E) == S16(u, 0x12C))
            end_fade(u);
    }
    U32(u, 0x138) += 1;
    U8(u, 0x19C) = (U8(u, 0x19C) & ~1) | 1;
    U8(u, 0x19F) &= ~0x20;
}

extern u32 *g_005B5040;                  /* (small data) the face motion: header +4 tracks, +0xC the tracks */
extern u8 g_005B5078[][0xD0];            /* weapon kinds (+0: the kind's motions, +0x50 the mounted ones) */
extern u8 *g_005BA688;                   /* (small data) the shared motions */
extern int g_0045D2C8;                   /* (small data) the side in the duel view */

void func_00118850(void *to, int size);  /* clear */
void func_0014D9A0(float t, Actor *a, u8 *motion);
void func_0014D7E0(float t, Actor *a, u8 *motion, u32 first, u32 last);
void func_0014DFC0(float t, Actor *a, u8 *rec, u8 *expr, int part);
void func_0014E380(Actor *a);
void func_0014D6C0(Actor *a);
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
    if ((U8(a, 0x20C) & 2) && PTR(a, 0x1F4) != 0)
        return (float *)PTR(a, 0x1F4);
    return (float *)PTR(a, 0x1F0);
}

/* The rotation matrix of the unit's rotation +0x50 (VU0 micro subroutine 0x40) into m. */
#define ROT_MATRIX(m, rot)                                              \
    __asm__ volatile("lqc2 $vf1, 0(%1)\n"                               \
                     "vcallms 0x40\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x00(%0)\n"                           \
                     "sqc2 $vf17, 0x10(%0)\n"                           \
                     "sqc2 $vf18, 0x20(%0)\n"                           \
                     "sqc2 $vf19, 0x30(%0)\n"                           \
                     : : "r"(m), "r"(rot) : "$9", "memory")

/* The motion's root offset turned with the unit (by the scratchpad matrix at 0x70000080). */
static inline void root_offset(Unit *u)
{
    float r[4][4], m[4][4], *n = (float *)PTR(PTR(u, 0x11C), 0x208), *s = (float *)0x70000080;
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

        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, PTR(u, 0x1B4), 0);
        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, PTR(u, 0x1B4), 1);
        func_0014DFC0(0.0f, PTR(u, 0x11C), rec, PTR(u, 0x1B4), 2);
        PTR(u, 0x1B4) = 0;
    }
    if (still) {
        r = root_node(PTR(u, 0x11C));
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = 0.0f;
        r[3] = 1.0f;
    } else if (U8(u, 0x19F) & 0x80) {
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
