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
