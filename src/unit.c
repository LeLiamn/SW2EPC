/*
 * unit.c - the characters on the battlefield (original source file unknown; from 0x001508F0,
 * after the model code).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A character (a "unit") is a large object whose layout is still mostly unknown: its fields are
 * reached here by offset (U8 / S16 / U32 / F32 ... below). Known so far:
 * +0x040 position (vec4), +0x054 yaw, +0x110 its description (+0x1C: weapon kind?), +0x118 state,
 * +0x13C direction flags, +0x14E player (0, 1: others), +0x1E0 its model object, +0x210 its
 * current action (+0 id, +8 / +0xA motions, +0x18 flags), +0x224-0x22C speeds, +0x27C flags,
 * +0x280 / +0x288 linked units (rider, mount?).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

#define PI     3.1415927f
#define TWO_PI 6.2831855f

typedef u8 Unit;

float sqrtf(float x);
float vu0_angle(float x, float z);
void vu0_sincos(float a, float *s, float *c);     /* VU0 micro subroutine 0x20 */               /* VU0 micro subroutine 0x30 (atan2?) */
void vu0_rot_y(float m[4][4], float yaw);        /* VU0 micro subroutine 0x70: rotation about Y */

extern u8 g_005B5078[][0xD0];            /* per weapon kind: motion tables (+0, +0x10, +0x20, +0x50) */
extern u8 g_005ADD80[][0xC0];            /* effects in use */
extern int g_0045D374;                   /* (small data) */
extern u32 g_0072C750[][2];
extern u8 g_0072CEB0[][0x120];
extern u8 g_005B4D80[][0x240];

void func_001AE090(u8 *effect);
void func_001185E0(void *to, u32 n, u8 c);
void func_0016BD30(Unit *u);
Unit *func_0016BE40(Unit *u);
void func_001CF2A0(Unit *u, Unit *v, int a);
void func_00156AF0(Unit *u, u16 id);
void func_001CF000(Unit *u, Unit *v);
void func_00158CD0(Unit *u, u32 kind);
u32 func_001C8340(int a, u8 *b, int c, u32 d);
void func_001C8620(u8 *a, int b, u8 *c, int d, u32 e);
void func_001C8780(int a, Unit *u, int b, u32 c);
void func_00253300(int a, Unit *u);
#define g_70000D60 (*(int *)0x70000D60)

/* 0x001508F0, 0x20 bytes, matching. Sets the low direction flags (bits 0-14). */
void func_001508F0(Unit *u, u32 flags)
{
    u32 v = U32(u, 0x13C) & 0x3FFF8000;

    U32(u, 0x13C) = v;
    U32(u, 0x13C) = v | flags;
}

/* 0x00150910, 0x20 bytes, matching. Sets the middle direction flags (bits 15-25). */
void func_00150910(Unit *u, u32 flags)
{
    u32 v = U32(u, 0x13C) & 0x3C007FFF;

    U32(u, 0x13C) = v;
    U32(u, 0x13C) = v | flags;
}

/* 0x00150930, 0xDC bytes. Takes the current action's two extra motions (+0xA, +8; 0xFFFF: none)
 * from the weapon kind's tables, for the two motion slots that want one (+0x2DC, +0x34C). */
void func_00150930(Unit *u)
{
    u16 m;

    if (U8(u, 0x155) != 0)
        return;
    m = U16(PTR(u, 0x210), 0xA);
    if (m != 0xFFFF && (U8(u, 0x2DC) & 4)) {
        u8 kind = U8(PTR(u, 0x110), 0x1C);

        U32(u, 0x2F0) = *(u32 *)(g_005B5078[kind] + 0x20) + m * 0x20;
        U32(u, 0x2F4) = 0;
    }
    m = U16(PTR(u, 0x210), 8);
    if (m != 0xFFFF && (U8(u, 0x34C) & 4)) {
        u8 kind = U8(PTR(u, 0x110), 0x1C);

        U32(u, 0x360) = *(u32 *)(g_005B5078[kind] + 0x10) + m * 0x20;
        U32(u, 0x364) = 0;
    }
}

/* Clears a unit's effect slots and the state that goes with them. */
static inline void unit_clear_effects(Unit *u)
{
    u8 *desc = PTR(u, 0x110);

    func_001185E0(u + 0x1E0, 0xB0, 0);
    S16(u, 0x258) = -1;
    S16(u, 0x260) = -1;
    S16(u, 0x262) = -1;
    S16(u, 0x264) = -1;
    S16(u, 0x266) = -1;
    S16(u, 0x268) = -1;
    S16(u, 0x26A) = -1;
    U8(u, 0x274) = 0xFF;
    U8(u, 0x275) = 0xFF;
    F32(u, 0x234) = 1.0f;
    S16(u, 0x278) = -1;
    if (desc != 0)
        PTR(u, 0x210) = PTR(desc, 8);
}

/* 0x00150A10, 0x104 bytes. Ends a unit's effects (+0x258, +0x260-0x26A), then clears them. */
void func_00150A10(Unit *u)
{
    int i;

    if (S16(u, 0x258) != -1)
        func_001AE090(g_005ADD80[S16(u, 0x258)]);
    for (i = 0; i < 6; i++) {
        if (S16(u, 0x260 + i * 2) != -1)
            func_001AE090(g_005ADD80[S16(u, 0x260 + i * 2)]);
    }
    unit_clear_effects(u);
}

/* 0x00150B20, 0x84 bytes. Clears them without ending them. */
void func_00150B20(Unit *u)
{
    unit_clear_effects(u);
}

/* 0x00150BB0, 0x98 bytes. Unlinks a unit (+0x270 both ways), its rider (+0x280) and what it
 * carries (+0x288), ending their effects. */
void func_00150BB0(Unit *u)
{
    Unit *v = PTR(u, 0x270);

    if (v != 0) {
        PTR(u, 0x270) = 0;
        PTR(v, 0x270) = 0;
    }
    v = PTR(u, 0x280);
    if (v != 0) {
        func_0016BD30(u);
        func_00150A10(v);
    }
    if (PTR(u, 0x288) != 0) {
        v = func_0016BE40(u);
        func_001CF2A0(u, v, 0);
        func_00150A10(v);
    }
    func_00150A10(u);
}

/* The action after a hit while in action `id` (flags `f`): 0 for none. Shared by the two
 * functions below, which differ only in the default (0xE or 0xF). */
static inline int unit_hit(Unit *u, int dflt)
{
    int next;

    if (S32(u, 0x118) == 0x3C) {
        next = (s8)U8(u, 0x27C) < 0 ? 0x1D : 0x12;
    } else {
        u16 *act = (u16 *)PTR(u, 0x210);
        u32 f = *(u32 *)(act + 0xC);

        if ((f & 0x800) == 0) {
            u32 id = act[0];

            if (id == 0x84)
                next = 0x85;
            else if (id - 0xAF < 2)
                next = 0xB1;
            else if (id == 0xB3)
                next = 0xB4;
            else
                next = dflt;
        } else {
            u16 id = act[0];

            if ((u16)(id - 0x76) < 2) {
                F32(u, 0x224) = 0.0f;
                F32(u, 0x228) = 0.0f;
                U8(u, 0x27C) &= ~2;
                return -1;
            }
            if (14.0f <= F32(u, 0x22C) || F32(u, 0x224) <= -20.0f) {
                next = (f & 0x1000000) == 0 ? 0x36 : 0x37;
            } else if (id == 0x34) {
                next = 0x38;
            } else if (id == 0x35) {
                next = 0x39;
            } else {
                next = (f & 0x1000000) != 0 ? 0x35 : 0x34;
                F32(u, 0x224) = 0.0f;
                goto done;
            }
        }
    }
    F32(u, 0x224) = 0.0f;
done:
    F32(u, 0x228) = 0.0f;
    U8(u, 0x27C) &= ~2;
    return next;
}

/* 0x00150C50, 0x1C0 bytes. Reacts to a hit from the front (?): 1, or 0 in the actions 0x76-0x77
 * (which only stop). */
int func_00150C50(Unit *u)
{
    int next = unit_hit(u, 0xE);

    if (next < 0)
        return 0;
    func_00156AF0(u, next);
    return 1;
}

/* 0x00150E10, 0x1C0 bytes. The same from behind (?). */
int func_00150E10(Unit *u)
{
    int next = unit_hit(u, 0xF);

    if (next < 0)
        return 0;
    func_00156AF0(u, next);
    return 1;
}

/* 0x00150FD0, 0x1E8 bytes. Places a unit beside `other`: on its left or right (`side` 0x55:
 * left; -1: the side it already is on), 100 units aside, 2.3 up, 11.9 ahead, facing as it does.
 * Whether it went left (?). */
int func_00150FD0(Unit *u, Unit *other, short side)
{
    float d[4], m[4][4], off[4], v[4];
    int left, i, k;

    for (i = 0; i < 4; i++)
        d[i] = F32(u, 0x40 + i * 4) - F32(other, 0x40 + i * 4);
    if (side == -1) {
        float a = vu0_angle(d[0], d[2]) - F32(other, 0x54);

        if (PI < a)
            a -= TWO_PI;
        else if (a < -PI)
            a += TWO_PI;
        left = !(0.0f <= a);
    } else {
        left = side == 0x55;
    }
    off[0] = left ? -100.0f : 100.0f;
    off[1] = 2.3260002f;
    off[2] = 11.947499f;
    off[3] = 0.0f;
    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i][k] = ((float *)0x70000000)[i * 4 + k];
    vu0_rot_y(m, F32(other, 0x54));
    for (k = 0; k < 4; k++)
        v[k] = m[0][k] * off[0] + m[1][k] * off[1] + m[2][k] * off[2] + m[3][k] * off[3];
    for (k = 0; k < 4; k++)
        F32(u, 0x40 + k * 4) = F32(other, 0x40 + k * 4) + v[k];
    F32(u, 0x54) = F32(other, 0x54);
    F32(u, 0x238) = F32(other, 0x54);
    U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
    return left;
}

/* 0x001511C0, 0x130 bytes. Links a unit with `other` (+0x288 / +0x28C), placed beside it; the
 * unit's action is 0x55 or 0x56 by the side; for the first two units, part of the state is
 * reset. */
int func_001511C0(Unit *u, Unit *other, u8 kind)
{
    int action;

    PTR(u, 0x288) = other;
    U8(u, 0x274) = kind;
    PTR(other, 0x28C) = u;
    action = func_00150FD0(u, other, -1) == 0 ? 0x56 : 0x55;
    func_001CF000(u, other);
    U8(other, 0x154) = U8(u, 0x154);
    if (U8(u, 0x14E) < 2) {
        U8(u, 0x157) = 0;
        S16(u, 0x194) = 0;
        func_00158CD0(u, 4);
        if (U8(u, 0x19E) & 2) {
            u8 b;

            U8(u, 0x19E) &= ~2;
            b = U8(u, 0x19D);
            U8(u, 0x19D) = b & 0xBF;
            U8(u, 0x19D) = b & 0x3F;
            b = U8(u, 0x19E);
            U8(u, 0x19E) = b & 0xFE;
            U8(u, 0x19E) = b & 0xF6;
            S16(u, 0x15E) = 0;
        }
    }
    return action;
}

/* 0x001512F0, 0x1C8 bytes. Starts a player's special effects (+0x182: 0, 1 or 2 levels?): the
 * effects 0x167 / 0x168 into the slots at 0x0072C750, the aura at 0x0072CEB0 and its sound. */
void func_001512F0(Unit *u)
{
    u8 p = U8(u, 0x14E);
    u8 *tab = g_005B4D80[p];
    u32 mask = p == 0 ? 0x40 : 0x80;
    int a, b;

    g_0045D374 = 2;
    g_70000D60 = 0;
    if (U8(u, 0x182) == 2) {
        a = 0x14E;
        b = 0x14F;
        g_0072C750[p][0] = func_001C8340(0x168, tab, 0, mask | 0x4325);
        g_0072C750[p][1] = func_001C8340(0x168, tab, 0, mask | 0x4325);
    } else if (U8(u, 0x182) == 1) {
        a = 0x14A;
        b = 0x14B;
        g_0072C750[p][0] = func_001C8340(0x167, tab, 0, mask | 0x4325);
        g_0072C750[p][1] = 0;
    } else {
        a = 0x146;
        b = 0x147;
    }
    g_70000D60 = 5;
    func_001C8620(g_0072CEB0[p], a, tab, 0, mask | 0x324);
    g_70000D60 = 0;
    func_001C8780(b, u, 0, mask | 0x208);
    func_00253300(3, u);
}

#define g_7000015C (*(u32 *)0x7000015C)          /* the random seed */
#define RANDOM()   (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

extern u8 g_006A3A30[][0xC0];            /* the officers (+0x86 maximum, +0x88 current: life?) */
extern u32 g_0076E700[];
extern u32 g_00669DB8;                   /* the game mode (4: ?) */
extern u32 g_00669F60;                   /* battle flags */
extern int g_0045D2C8;                   /* (small data) */
extern float g_0045CC7C;                 /* (small data) */
extern short g_0045CC58[4];              /* (small data) four reactions */
extern short g_0045CC60[4];              /* (small data) four more */
extern u16 g_004063E8[5];                /* 101, 103, 105, 107, 44 */
extern short g_004063F8[];
extern u8 g_0072CEE8[][0x120];
extern u8 g_005B49E0[][0xF0];

int func_00271210(void);
void func_00253690(int a, Unit *u);
int func_002713A0(Unit *u);
int func_001BE930(int state);
int func_003E2000(void);
Unit *func_003E1F60(u8 player, u32 k);
void func_001D1A40(Unit *u);
void func_00118850(void *to, u32 n);
int func_001F2680(Unit *u);
void func_001F2810(Unit *u);
int func_001F2AD0(void);
void func_001F1EC0(Unit **list, int n, int kind);
void func_001C8950(int a);
void func_001D0E60(Unit *u);
float func_00271380(u8 level);
void func_001D0F20(Unit *u);
void func_00271870(void);
void func_001F20E0(Unit *u, int a);
void func_003E2D30(void);
u32 func_00271540(void);
void func_0029E3C0(u8 *a, u8 b);
void func_0029EDF0(u8 *a);
int func_003E2DC0(Unit *v);
u32 func_003E2FE0(Unit *v);
int func_001D0FF0(Unit *u, Unit *v, u8 *hit, float *dir);
float func_003AFE50(u8 *officer);
float func_003AFF70(u8 *officer);
int func_00272E40(Unit *u);
void func_001512F0(Unit *u);

#define PLAYER(u) U8(u, 0x14E)
#define ACT(u)    PTR(u, 0x210)
#define DESC(u)   PTR(u, 0x110)

/* 0x001514C0, 0x5C4 bytes. A unit is defeated (?): its level from its officer's value, the
 * battle's reaction to it (end-of-battle events, the defeat message, the effects for the
 * players), and the lowest value seen so far for the players. */
void func_001514C0(Unit *u)
{
    u8 *rec = g_006A3A30[S16(u, 0x178)];
    u8 p;

    U8(u, 0x19C) &= ~0x40;
    if (g_00669DB8 != 4) {
        u8 lv = (u8)(S16(rec, 0x88) / func_00271210());

        U8(u, 0x182) = lv;
        lv = U8(u, 0x182);
        if (lv < 2)
            lv = 1;
        else if (lv >= 4)
            lv = 3;
        U8(u, 0x182) = lv;
        U8(u, 0x182) -= 1;
        func_00253690(1, u);
        g_0076E700[PLAYER(u)] &= ~2;
    }
    U8(u, 0x19D) &= ~0x20;
    U8(u, 0x19F) = (U8(u, 0x19F) & ~2)
                   | ((func_002713A0(u) != 0 && (U8(u, 0x19E) & 4) == 0) << 1);
    if (PLAYER(u) < 2 && func_001BE930(S32(u, 0x118)) != 0 && S32(u, 0x11C) != 0)
        S32(u, 0x1B4) = S32(u, 0x118) * 0x150 + 0x6CE080;
    if ((U32(ACT(u), 0x18) & 0x8000000) == 0) {
        Unit *list[4];
        int players = 1, n = 1, with = 0;

        func_00118850(list, 0x10);
        U8(u, 0x19D) &= ~0x10;
        list[0] = u;
        if (PLAYER(u) < 2) {
            u32 cnt = func_003E2000();

            if (cnt != 0) {
                u32 k;

                for (k = 0; k < cnt; k++) {
                    Unit *v = func_003E1F60(PLAYER(u), k);

                    func_001D1A40(v);
                    list[k + 1] = v;
                    if (PLAYER(v) < 2)
                        players++;
                }
                U8(u, 0x19D) = (U8(u, 0x19D) & ~0x20) | 0x20;
            }
            n = cnt + 1;
            with = players;
        }
        if ((g_00669F60 & 0x14000000) == 0 && func_001F2680(u) != 0) {
            func_001F2810(u);
            g_0045D2C8 = 0;
            U8(u, 0x19D) = (U8(u, 0x19D) & ~0x20) | 0x20;
        } else if ((g_00669F60 & 0x14000000) == 0 && (U8(u, 0x19D) & 0x20)
                   && func_001F2AD0() == 0) {
            g_00669F60 |= 0x800000;
            func_001F1EC0(list, n, with == 1 ? 3 : 4);
            g_0045D2C8 = 0;
            func_001C8950(1);
        } else if ((g_00669F60 & 0x14000002) == 0 && func_002713A0(u) != 0
                   && (U8(u, 0x19E) & 4) == 0) {
            if (g_00669DB8 == 4) {
                func_001D0E60(u);
            } else if (PLAYER(u) < 2) {
                g_00669F60 |= 0x800000;
                func_001F1EC0(list, n, 0);
                g_0045D2C8 = 0;
                func_001C8950(1);
            }
        } else if (g_00669DB8 != 4) {
            func_001D0E60(u);
            if (PLAYER(u) < 2)
                func_001512F0(u);
        }
    } else {
        short mx = S16(rec, 0x86);
        short v = (short)(int)((float)S16(rec, 0x88) * 0.7f);
        short t = mx < v ? mx : v;

        U8(u, 0x19D) = (U8(u, 0x19D) & ~0x10) | 0x10;
        if (t < 1)
            v = 0;
        else if (mx < v)
            v = mx;
        S16(rec, 0x88) = v;
        func_001D0E60(u);
        if (PLAYER(u) < 2)
            func_001512F0(u);
    }
    p = PLAYER(u);
    if (p < 2 && (g_00669F60 & 8) == 0 && g_00669DB8 != 4) {
        float f = func_00271380(U8(u, 0x182));

        if (f < g_0045CC7C)
            g_0045CC7C = f;
    }
}

/* 0x00151A90, 0x1D0 bytes. A unit gets up again (?): the end of the defeat state, and the
 * battle's reaction (or, with `quiet`, a flag for the player's aura). */
void func_00151A90(Unit *u, int quiet)
{
    func_001D0F20(u);
    if (PLAYER(u) < 2 && func_001BE930(S32(u, 0x118)) != 0 && S32(u, 0x11C) != 0)
        S32(u, 0x1B4) = S32(u, 0x118) * 0x150 + 0x6CE090;
    if (g_00669DB8 != 4) {
        func_00271870();
        if (quiet == 0) {
            if (((U8(u, 0x19F) & 2) || (U8(u, 0x19D) & 0x20)) && (U8(u, 0x19E) & 4) == 0
                && PLAYER(u) < 2 && (U32(ACT(u), 0x18) & 0x8000000) == 0
                && (g_00669F60 & 0x14080002) == 0) {
                g_00669F60 |= 0x2000000;
                func_001F20E0(u, 1);
                g_0045D2C8 = 0;
                func_001C8950(1);
            }
        } else {
            *(u32 *)(g_0072CEE8[PLAYER(u)]) |= 8;
        }
        if (PLAYER(u) < 2)
            g_0045CC7C = 1.0f;
        U8(u, 0x19C) &= ~0x40;
        if (PLAYER(u) < 2)
            func_003E2D30();
    }
}

/* 0x00151C60, 0x84 bytes. Starts the action the AI chose (when it exists and is not the current
 * one). */
int func_00151C60(Unit *u)
{
    u32 a = func_00271540() & 0xFFFF;
    u8 *d = DESC(u);

    if (a < U32(PTR(d, 4), 8) && S16(PTR(d, 8), a * 0x20 + 2) != -1 && a != U16(ACT(u), 0))
        func_00156AF0(u, a);
    return 1;
}

/* 0x00151CF0, 0x68 bytes. Goes on to the action that follows the current one (the weapon's
 * table of 0x30-byte records: +0x26 the action, +2 the next). */
int func_00151CF0(Unit *u)
{
    short a = S16(ACT(u), 0);
    u8 *r = PTR(DESC(u), 0xC);
    int n = S32(PTR(DESC(u), 4), 0xC), i;

    for (i = 0; i < n; i++, r += 0x30) {
        if (S16(r, 0x26) == a) {
            a = S16(r, 2);
            break;
        }
    }
    func_00156AF0(u, a);
    return 1;
}

/* 0x00151D60, 0x7C bytes. Starts action 100 (guard?) when the current action allows it. */
int func_00151D60(Unit *u)
{
    if ((U32(ACT(u), 0x18) & 0x8000020) == 0) {
        u8 *e = PTR(ACT(u), 0x14);
        u32 f = e == 0 ? 0 : U32(e, 0x2C) & 0x400;

        if (f == 0 && (U8(u, 0x19C) & 2) == 0) {
            func_00156AF0(u, 100);
            return 1;
        }
    }
    return 0;
}

/* 0x00151DE0, 0xC4 bytes. A fall at speed 14 or more in the air: action 0x30 / 0x31, moving
 * along `v`, speed divided by 16. */
int func_00151DE0(Unit *u, const u32 *v)
{
    u32 f = U32(ACT(u), 0x18);

    if ((f & 0x20) == 0 || (f & 0x800) == 0)
        return 0;
    if (F32(u, 0x22C) < 14.0f)
        return 0;
    func_00156AF0(u, (f & 0x1000000) == 0 ? 0x30 : 0x31);
    U32(u, 0x1F0) = v[0];
    U32(u, 0x1F4) = v[1];
    U32(u, 0x1F8) = v[2];
    U32(u, 0x1FC) = v[3];
    F32(u, 0x22C) = F32(u, 0x22C) / 16.0f;
    F32(u, 0x224) = 0.0f;
    return 1;
}

/* Turns a unit to face away from `dir` (flattened and normalised in place), pushed along it. */
static inline void unit_face_hit(Unit *u, float *dir)
{
    float len;
    int i;

    dir[1] = 0.0f;
    len = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2] + dir[3] * dir[3]);
    for (i = 0; i < 4; i++)
        dir[i] = dir[i] / len;
    F32(u, 0x238) = vu0_angle(dir[0], dir[2]);
    U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
}

/* 0x00151EB0, 0x2D8 bytes. Reacts to hit `hit` coming along `dir`: a random reaction among five
 * (the last, 44, knocks the unit back), or the hit's own reaction with its push (+8) and lift
 * (+9); `base` is added to the reaction. */
int func_00151EB0(Unit *u, u8 *hit, u32 base, float *dir)
{
    u16 a = U16(hit, 0xC);
    u8 *act = PTR(DESC(u), 8) + a * 0x20;

    if ((U32(act, 0x18) & 0x400) == 0) {
        u32 r = RANDOM() % 5;

        if (g_004063E8[r] == 44) {
            unit_face_hit(u, dir);
            F32(u, 0x22C) = 10.0f;
        }
        func_00156AF0(u, ((base & 0xFF) + g_004063E8[r]) & 0xFFFF);
        if (g_004063E8[r] == 44) {
            F32(u, 0x224) = 8.0f;
            U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        }
    } else {
        unit_face_hit(u, dir);
        F32(u, 0x22C) = (float)(s8)hit[8];
        func_00156AF0(u, (a + (base & 0xFF)) & 0xFFFF);
        if (hit[9] != 0 && (U32(act, 0x18) & 0x20)) {
            F32(u, 0x224) = (float)(s8)hit[9];
            U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        }
    }
    if (PLAYER(u) < 2)
        func_00158CD0(u, 4);
    return 1;
}

/* 0x00152190, 0xC0 bytes. Knocked down: pushed backwards, action 0x76 / 0x77, 30 frames on the
 * ground, lifted by the hit's +0x14. */
int func_00152190(Unit *u, u8 *act, u8 *hit)
{
    int i;

    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = F32(u, 0x70 + i * 4) * -1.0f;
    F32(u, 0x22C) = 0.0f;
    func_00156AF0(u, (U32(act, 0x18) & 0x1000000) == 0 ? 0x76 : 0x77);
    S16(u, 0x190) = 0x1E;
    if (hit[0x14] != 0) {
        F32(u, 0x224) = (float)(s8)hit[0x14];
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    }
    return 1;
}

void func_001523C0(Unit *u);

/* 0x00152250, 0x170 bytes. Reacts to a hit by the current action's kind (`act` flags +0x18):
 * in the air, knocked down, lifted, or one of four reactions (not the one under way). */
void func_00152250(Unit *u, short *act, u8 *hit, int other, u16 base)
{
    u32 f = *(u32 *)(act + 0xC);

    if ((f & 0x20) == 0) {
        if ((f & 0x40) == 0) {
            if ((f & 0x40000) == 0) {
                if (other == 0) {
                    u32 r = RANDOM() & 3;

                    if (act[0] == g_0045CC58[r])
                        r = (r + 1) & 3;
                    func_00156AF0(u, (base & 0xFF) + g_0045CC58[r]);
                } else {
                    func_001523C0(u);
                }
            } else {
                func_00156AF0(u, 0x2A);
                F32(u, 0x22C) = 0.0f;
                F32(u, 0x224) = 10.0f;
                U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
            }
        } else {
            func_00152190(u, (u8 *)act, hit);
        }
    } else {
        if (act[0] != 0x34 && act[0] != 0x35) {
            func_00156AF0(u, 0x2A);
            F32(u, 0x21C) = 8.0f;
        }
        F32(u, 0x22C) = 0.0f;
        F32(u, 0x224) = 3.0f;
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    }
}

/* 0x001523C0, 0x4C bytes, matching. One of four other reactions, at random. */
void func_001523C0(Unit *u)
{
    func_00156AF0(u, g_0045CC60[RANDOM() & 3]);
}

/* 0x00152410, 0xB4 bytes, matching. Reaction `k` (table at 0x004063F8); for the players, the message box
 * of their weapon (`k` 2) or its closing. */
int func_00152410(Unit *u, int k)
{
    u8 p;

    func_00156AF0(u, g_004063F8[k]);
    p = PLAYER(u);
    if (p < 2) {
        if (k == 2) {
            func_0029E3C0(g_005B49E0[p], U8(DESC(u), 0x1C));
            func_001C8950(1);
        } else {
            func_0029EDF0(g_005B49E0[p]);
        }
    }
    return 1;
}

/* 0x001524D0, 0x88 bytes, matching. Whether `v` can be caught by `u`'s current hit (a unit in states
 * below 0x3C, not protected, the hit not blocked). */
int func_001524D0(Unit *u, Unit *v, u8 *hit)
{
    if (v == 0 || S32(v, 0x118) > 0x3B || (U32(ACT(v), 0x1C) & 0x8000000))
        return 0;
    if (U32(hit, 0x2C) & 0x400)
        return 0;
    if (U32(hit, 0x28) & 0x40000000)
        return 0;
    return (U32(ACT(u), 0x1C) & 0x80000) != 0;
}

/* 0x00152560, 0x2E0 bytes. Whether `u` guards against `v`'s hit coming along `dir`: not while
 * protected or busy; `v`'s guard-break chance; a weapon kind ':' with no guard left; only in a
 * guarding action, facing the hit, and not against a much stronger attacker. *out is set when
 * the guard is a special one (func_00272E40). */
int func_00152560(Unit *u, Unit *v, u8 *hit, float *dir, int *out)
{
    u32 f;
    u8 *rv, *ru;
    float a, b;

    *out = 0;
    if (v == 0 || (U32(ACT(v), 0x1C) & 0x8000000))
        return 0;
    if ((U32(hit, 0x28) & 0x4000000) || (U8(u, 0x19D) & 8))
        return 0;
    if (func_003E2DC0(v) != 0) {
        u32 p = func_003E2FE0(v);

        if (RANDOM() % 100 < p)
            return 0;
    }
    if (func_001D0FF0(u, v, hit, dir) != 0)
        return 1;
    if (U8(DESC(u), 0x1C) == ':' && S16(u, 0x1B8) < 1)
        return 0;
    f = U32(ACT(u), 0x18);
    if (((f & 2) == 0 || (U32(u, 0x13C) & 0x80000) == 0) && (f & 0x10) == 0)
        return 0;
    rv = g_006A3A30[S16(v, 0x178)];
    ru = g_006A3A30[S16(u, 0x178)];
    a = func_003AFE50(rv);
    b = func_003AFF70(ru);
    if (4.0f <= a / b) {
        a = func_003AFE50(rv);
        b = func_003AFF70(ru);
        if ((float)hit[4] * a / b < 80.0f)
            return 0;
    }
    if (func_00272E40(u) != 0) {
        *out = 1;
        return 1;
    }
    return F32(u, 0x70) * dir[0] + F32(u, 0x74) * dir[1] + F32(u, 0x78) * dir[2]
           + F32(u, 0x7C) * dir[3] > 0.0f;
}

extern u8 *g_005BA688;                   /* the shared motion records (+n * 0x20) */
#define OFFICER(u) g_006A3A30[S16(u, 0x178)]

float fabsf(float x);
float func_00136E00(float y, float x);   /* atan2f */
void func_001CEA40(Unit *u);
void func_001CEA60(Unit *u, Unit *v);
void func_001649C0(Unit *u);
void func_0029EE00(u8 *box, Unit *u);
void func_0027A080(float a, u8 *pos, int b, int c);
int func_00272ED0(Unit *u, Unit *v);
int func_0016C040(Unit *u);
void func_001C7FC0(int a, u8 *pos, float *dir, u32 f);
int func_00273770(Unit *u, short damage, float *out);
void func_0016C180(float amount, Unit *u);
void func_001CCFA0(Unit *u);

/* Wraps an angle into (-pi, pi]. */
static inline float wrap_angle(float a)
{
    if (PI < a)
        a -= TWO_PI;
    else if (a < -PI)
        a += TWO_PI;
    return a;
}

/* 0x00152840, 0x6A0 bytes. Whether `u`'s current hit and `v`'s hit `hit` clash: 0 no; 1 they
 * face each other within 200 units (a weapon lock); 2 / 3 one of them wins (by their officers'
 * flags, their attacks' kinds or a special state); 4 neither. */
int func_00152840(Unit *u, Unit *v, u8 *hit)
{
    u8 *e = PTR(ACT(u), 0x14);
    u32 fu, fv;
    float d[4];

    if (g_00669DB8 == 4)
        return 0;
    if (v == 0 || hit == 0)
        return 0;
    if (S32(v, 0x118) > 0x3B || S32(u, 0x118) > 0x3B)
        return 0;
    if (U32(hit, 0x28) & 0x40000000)
        return 0;
    if (e == 0 || (s8)U8(u, 0x19C) < 0 || (s8)U8(v, 0x19C) < 0)
        return 0;
    if ((U8(u, 0x19C) & 2) == 0 && (U8(v, 0x19C) & 2) == 0) {
        u8 *e2;

        if (e == 0 || F32(u, 0x21C) < (float)e[5] || (float)e[6] < F32(u, 0x21C))
            return 0;
        e2 = PTR(ACT(v), 0x14);
        if (e2 == 0 || F32(v, 0x21C) < (float)e2[5] || (float)e2[6] < F32(v, 0x21C))
            return 0;
    }
    if ((U8(u, 0xE8) & 3) >> 1 == 1 || (U8(v, 0xE8) & 3) >> 1 == 1)
        return 0;
    if (U32(hit, 0x2C) & 0x400)
        return 0;
    if (U8(v, 0x27C) & 4)
        return 0;
    if ((U8(u, 0x19E) & 4) || (U8(v, 0x19E) & 4))
        return 0;
    if ((U32(ACT(u), 0x18) & 0x8000020) || (U32(ACT(v), 0x18) & 0x8000020))
        return 2;
    fu = U32(OFFICER(u), 0xB8) & 0x26C;
    fv = U32(OFFICER(v), 0xB8) & 0x26C;
    if (fu != 0 && fv == 0)
        return 2;
    if (fu == 0 && fv != 0)
        return 3;
    if (fu == 0 || fv == 0) {
        if (fu == 0 && fv == 0) {
            u32 ku = U32(e, 0x28) & 0x1C, kv = U32(hit, 0x28) & 0x1C;

            if (ku != 0 && kv == 0)
                return 2;
            if (kv != 0 && ku == 0)
                return 3;
            if (kv == 0 && ku == 0)
                return 4;
        }
    } else {
        if ((U8(u, 0x19C) & 2) && (U8(v, 0x19C) & 2) == 0)
            return 2;
        if ((U8(v, 0x19C) & 2) && (U8(u, 0x19C) & 2) == 0)
            return 3;
    }
    if ((U8(u, 0x19C) & 2) == 0 && (U8(v, 0x19C) & 2) == 0) {
        if ((U32(hit, 0x28) & 2) == 0 || (U32(e, 0x28) & 2) == 0)
            return 0;
        if ((U32(hit, 0x28) & 1) || (U32(e, 0x28) & 1))
            return 0;
    }
    for (fu = 0; fu < 4; fu++)
        d[fu] = F32(v, 0x40 + fu * 4) - F32(u, 0x40 + fu * 4);
    if (fabsf(d[1]) < 20.0f && d[0] * d[0] + d[2] * d[2] < 40000.0f) {
        float a = vu0_angle(d[0], d[2]);
        float f = wrap_angle(a - F32(u, 0x54));

        if (fabsf(f) < 0.7853982f) {
            f = a + PI;
            if (PI < f)
                f -= TWO_PI;
            else if (f <= -PI)
                f += TWO_PI;
            f = wrap_angle(f - F32(v, 0x54));
            if (fabsf(f) < 0.7853982f)
                return 1;
        }
    }
    return 0;
}

/* 0x00152EE0, 0x228 bytes. Two units grab each other (a throw?): both start reaction 0, the
 * player's side holds the other (+0x280 / +0x284), their message boxes, and both leave any
 * defeat state. */
void func_00152EE0(Unit *u, Unit *v)
{
    func_00152410(u, 0);
    func_00152410(v, 0);
    if (PLAYER(v) < 2) {
        PTR(u, 0x284) = v;
        U8(u, 0x275) = 0xFF;
        U8(u, 0x276) = 0xFF;
        PTR(v, 0x280) = u;
    } else {
        PTR(v, 0x284) = u;
        U8(v, 0x275) = 0xFF;
        U8(v, 0x276) = 0xFF;
        PTR(u, 0x280) = v;
    }
    U8(u, 0x27C) = (U8(u, 0x27C) & ~4) | 4;
    U8(v, 0x27C) = (U8(v, 0x27C) & ~4) | 4;
    if (PLAYER(u) < 2)
        func_0029EE00(g_005B49E0[PLAYER(u)], v);
    else if (PLAYER(v) < 2)
        func_0029EE00(g_005B49E0[PLAYER(v)], u);
    if (PTR(u, 0x284) == 0)
        func_001CEA40(v);
    else
        func_001CEA40(u);
    if (U8(u, 0x19C) & 2) {
        func_00151A90(u, 1);
        U8(u, 0x19C) &= ~2;
    }
    func_001649C0(u);
    if (PLAYER(u) < 2)
        func_00158CD0(u, 4);
    if (U8(v, 0x19C) & 2) {
        func_00151A90(v, 1);
        U8(v, 0x19C) &= ~2;
    }
    func_001649C0(v);
    if (PLAYER(v) < 2)
        func_00158CD0(v, 4);
    U8(u, 0x159) = 0;
    U8(v, 0x159) = 0;
    func_001CEA60(u, v);
    func_001CEA60(v, u);
}

/* A direction flattened and normalised in place. */
static inline void flat_normalise(float *dir)
{
    float len;
    int i;

    dir[1] = 0.0f;
    len = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2] + dir[3] * dir[3]);
    for (i = 0; i < 4; i++)
        dir[i] = dir[i] / len;
}

/* 0x00153110, 0x80 bytes. Turns towards `dir` and goes on to the next action. */
void func_00153110(Unit *u, float *dir)
{
    flat_normalise(dir);
    F32(u, 0x238) = func_00136E00(dir[0], dir[2]);
    func_00151CF0(u);
}

/* 0x00153190, 0x1C bytes, matching. */
void func_00153190(Unit *u)
{
    func_00156AF0(u, 0x78);
}

/* 0x001531B0, 0x78 bytes. Lifted and pushed back (action 0x2A). */
void func_001531B0(Unit *u)
{
    int i;

    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = F32(u, 0x70 + i * 4) * -1.0f;
    F32(u, 0x22C) = 3.0f;
    func_00156AF0(u, 0x2A);
    F32(u, 0x224) = 10.0f;
    U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
}

/* 0x00153230, 0x3D4 bytes. Blocks hit `hit` from `v` coming along `dir` for `damage`: the guard
 * sound and spark, the guard action (0x10, or 100 for a guard break), the push, and the hit
 * stop (the animation slowed by the damage). 0 for a guard break. */
int func_00153230(Unit *u, Unit *v, u8 *hit, float *dir, short damage, int keep_dir,
                  int no_action)
{
    int ret = 1, special, action, snd;
    float got;

    flat_normalise(dir);
    if (keep_dir == 0)
        F32(u, 0x238) = func_00136E00(dir[0], dir[2]);
    if (U32(ACT(u), 0x18) & 0x8000000) {
        func_0027A080(500.0f, u + 0x90, 2, 0x10);
        if (no_action == 0)
            func_00156AF0(u, 0x5D);
        goto end;
    }
    special = v == 0 ? 0 : func_00272ED0(u, v);
    if ((U32(hit, 0x28) & 0x8000000) == 0 || U8(u, 0x157) != 0 || S16(u, 0x194) != 0) {
        action = 0x10;
        snd = 2;
    } else {
        action = 100;
        g_70000D60 = 1;
        func_001C7FC0(6, u + 0x90, dir, func_0016C040(u) == 0 ? 0 : 0x200);
        snd = (U32(hit, 0x28) & 0x40000000) == 0 ? 3 : 0;
        ret = 0;
    }
    func_0027A080(500.0f, u + 0x90, snd, 0x10);
    if (no_action == 0)
        func_00156AF0(u, action);
    U8(u, 0x19D) = (U8(u, 0x19D) & ~2) | 2;
    {
        int i;

        for (i = 0; i < 4; i++)
            F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
    }
    F32(u, 0x22C) = (float)(s8)hit[7];
    if (special == 0) {
        u8 *d = DESC(u);
        u8 *a = PTR(d, 8) + U16(ACT(u), 0) * 0x20;
        u8 **r;
        int k;

        if ((U32(a, 0x1C) & 0x40000000) == 0) {
            if ((U32(a, 0x1C) & 0x80000000) == 0)
                r = (u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)]) + U16(a, 2) * 0x20);
            else
                r = (u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)] + 0x50) + U16(a, 2) * 0x20);
        } else {
            r = (u8 **)(g_005BA688 + U16(a, 2) * 0x20);
        }
        k = damage / 2;
        if (k > 10)
            k = 10;
        F32(u, 0x234) = (float)S32(*r, 8) / (float)(S32(*r, 8) + (short)k / 2);
    } else {
        F32(u, 0x234) = 1.5f;
    }
end:
    if (func_00273770(u, damage, &got) != 0)
        func_0016C180(got, u);
    if (U8(DESC(u), 0x1C) == ':')
        S16(u, 0x1B8) -= damage;
    return ret;
}

/* Knocked back along `dir` by hit `hit` (action record `act`). */
static inline void unit_knock(Unit *u, u8 *hit, u8 *act, float *dir)
{
    int i;

    flat_normalise(dir);
    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
    if ((U32(act, 0x18) & 0x20) == 0) {
        F32(u, 0x22C) = 12.0f;
        F32(u, 0x224) = 10.0f;
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    } else {
        F32(u, 0x22C) = (float)(s8)hit[10];
        if (hit[0xB] != 0) {
            F32(u, 0x224) = (float)(s8)hit[0xB];
            U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        }
    }
}

/* 0x00153610, 0x380 bytes. Knocked off (reaction 0x2C + `base`): on foot at once; on a mount
 * (+0x288) only when the attacker's hit (`other`, +0xB8) unseats riders or the mount is spent,
 * else reaction 0x5E (or, with `quiet`, a timer and *out = 1). 1 when knocked off. */
int func_00153610(Unit *u, u8 *hit, u32 base, float *dir, u8 *other, int quiet, int *out)
{
    u8 *act = PTR(DESC(u), 8) + U16(hit, 0xC) * 0x20;

    if ((U32(ACT(u), 0x18) & 0x8000000) == 0) {
        func_00156AF0(u, (base & 0xFF) + 0x2C);
        unit_knock(u, hit, act, dir);
        return 1;
    } else {
        Unit *mount = PTR(u, 0x288);
        u32 f = U32(other, 0xB8) & 0x800;
        int live = 0;

        if (f == 0)
            live = S16(OFFICER(mount), 0x82);
        else
            live = 1;
        if ((U32(other, 0xB8) & 2) == 0 && live != 0) {
            if (quiet == 0) {
                func_00156AF0(u, (base & 0xFF) + 0x5E);
            } else {
                F32(u, 0x244) = 5.0f;
                *out = 1;
            }
            return 0;
        }
        if (f == 0) {
            if ((U32(ACT(mount), 0x18) & 0x40020) == 0)
                func_00156AF0(mount, 8);
        } else {
            func_00156AF0(mount, (RANDOM() & 1) + 0x18);
            func_001CCFA0(mount);
        }
        func_00156AF0(u, (base & 0xFF) + 0x2C);
        unit_knock(u, hit, act, dir);
        return 1;
    }
}

extern u8 g_00574DE0[][0x630];           /* the units (0x630 bytes each); the players' bodyguards from 0x89 */
extern u8 g_005B7120[];                  /* the description used once a unit's guard is broken */

void func_00245360(Unit *u, u8 *hit);
void func_0016E910(u8 *slot);
void func_00164B40(Unit *u, int a);
void func_0016A0D0(Unit *u, float *out, int a);
void func_001C7F30(int a, float *pos, float *dir, int b);
void func_002A6D20(u8 player, int message);
void func_0015EA30(Unit *u, Unit *v, u8 *hit, short damage, int a, int b, int quiet);

/* The current action's motion record (the weapon kind's tables, or the shared ones). */
static inline u8 *unit_motion(Unit *u)
{
    u8 *d = DESC(u);
    u8 *a = PTR(d, 8) + U16(ACT(u), 0) * 0x20;

    if ((U32(a, 0x1C) & 0x40000000) == 0) {
        if ((U32(a, 0x1C) & 0x80000000) == 0)
            return *(u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)]) + U16(a, 2) * 0x20);
        return *(u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)] + 0x50) + U16(a, 2) * 0x20);
    }
    return *(u8 **)(g_005BA688 + U16(a, 2) * 0x20);
}

/* Pushed back along `dir` (flattened and normalised in place), at the hit's speed (+8). */
static inline void unit_push(Unit *u, u8 *hit, float *dir)
{
    int i;

    flat_normalise(dir);
    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
    F32(u, 0x22C) = (float)(s8)hit[8];
}

/* The usual flinch: pushed back, the hit's reaction (+0xC, +1 from behind, some swapped for
 * officers with flag +0xAB, some varied at random), the lift (+9) and the hit stop by damage. */
static inline void unit_flinch(Unit *u, u8 *hit, float *dir, int back, short damage)
{
    short a, b;

    unit_push(u, hit, dir);
    a = S16(hit, 0xC);
    b = a + back;
    if (g_00669DB8 != 4 && U8(OFFICER(u), 0xAB) != 0) {
        if (b == 0x22)
            b = 0x13;
        else if (b == 0x23)
            b = 0x14;
    }
    if (b == a) {
        if (a == 0x1A) {
            if (RANDOM() % 100 < 0x32)
                b = 0x7C;
        } else if (a == 0x20) {
            u32 r = RANDOM() % 100;

            if (r < 0x21)
                b = 0x7E;
            else if (r < 0x42)
                b = 0x90;
        } else if (a == 0x92 && RANDOM() % 100 < 0x32) {
            b = 0x94;
        }
    }
    func_00156AF0(u, b);
    if (hit[9] != 0 && (U32(ACT(u), 0x18) & 0x20)) {
        F32(u, 0x224) = (float)(s8)hit[9];
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    }
    if ((U32(ACT(u), 0x18) & 0x8000420) == 0) {
        u8 *r = unit_motion(u);
        int k = damage / 2;

        if (k > 0x19)
            k = 0x19;
        F32(u, 0x234) = (float)S32(r, 8) / (float)(S32(r, 8) + (short)k);
    }
}

/* 0x00153990, 0x114 bytes. Whether `v`'s charged attack (+0x17E = 2, level +0x17F) stuns `u`:
 * a chance of level x 33% (x 16% against officers with special flags). */
int func_00153990(Unit *u, Unit *v, u8 *rec)
{
    u32 chance;

    if (v == 0)
        return 0;
    if (U8(v, 0x17E) != 2)
        return 0;
    if (U32(ACT(u), 0x18) & 0x8040020)
        return 0;
    if ((U32(rec, 0xB8) & 0x26C) == 0)
        chance = U8(v, 0x17F) * 100 / 3;
    else
        chance = U8(v, 0x17F) * 100 / 6;
    return RANDOM() % 100 < chance;
}

/* 0x00153AB0, 0x78 bytes. Only pushed back (while stunned). */
void func_00153AB0(Unit *u, u8 *hit, float *dir)
{
    unit_push(u, hit, dir);
}

/* 0x00153B30, 0x104 bytes. Stunned by `v` (action 0x13) for its level x 60 frames. */
void func_00153B30(Unit *u, Unit *v, u8 *hit, float *dir)
{
    unit_push(u, hit, dir);
    func_00156AF0(u, 0x13);
    S16(u, 0x15C) = 0;
    U16(u, 0x172) = U8(v, 0x17F) * 0x3C;
    U16(u, 0x174) = U8(v, 0x17F) * 0x3C;
    func_00253300(U8(v, 0x17F) < 3 ? 0xF : 0x10, u);
}

/* 0x00153C40, 0x160 bytes. Hit in the air: the hit's air reaction (+0xE, swapped as above),
 * speed +0xA, lift +0xB. */
void func_00153C40(Unit *u, u8 *hit, float *dir, u16 base)
{
    short b;
    int i;

    flat_normalise(dir);
    for (i = 0; i < 4; i++)
        F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
    F32(u, 0x22C) = (float)(s8)hit[10];
    b = S16(hit, 0xE) + (base & 0xFF);
    if (g_00669DB8 != 4 && U8(OFFICER(u), 0xAB) != 0) {
        if (b == 0x22)
            b = 0x13;
        else if (b == 0x23)
            b = 0x14;
    }
    func_00156AF0(u, b);
    if (hit[0xB] != 0) {
        F32(u, 0x224) = (float)(s8)hit[0xB];
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    }
}

/* 0x00153DA0, 0xA4 bytes. Whether a weapon kind ':' unit's guard breaks: when it has none left,
 * or its officer is below a quarter of its life (+0x82 / +0x80), unless `v` is in a special
 * state. */
int func_00153DA0(Unit *u, Unit *v, u8 *rec)
{
    if (U8(DESC(u), 0x1C) != ':')
        return 0;
    if (v != 0 && (U8(v, 0x19C) & 2))
        return 1;
    if (S16(u, 0x1B8) < 1)
        return 1;
    return !(0.25f < (float)S16(rec, 0x82) / (float)S16(rec, 0x80));
}

/* 0x00153E50, 0x12E8 bytes. Takes hit `hit` from `v` along `dir` for `damage`: guard break
 * (the unit's description changes), stun, the reaction by the unit's state (on a mount, in the
 * air, knocked down, special officers...), the hit stop, the players' effect timers, then the
 * damage itself (func_0015EA30). The mount's result when riding. */
int func_00153E50(Unit *u, Unit *v, u8 *hit, int unused, float *dir, short damage, int quiet)
{
    int stunned = 0, ret = 0, broke = 0, back;
    u8 *act = ACT(u);
    u8 *rec = OFFICER(u);
    u32 f;

    back = !(F32(u, 0x70) * dir[0] + F32(u, 0x74) * dir[1] + F32(u, 0x78) * dir[2]
             + F32(u, 0x7C) * dir[3] > 0.0f);
    if (U32(rec, 0xB8) & 2)
        S16(u, 0x172) = 0;
    if (U32(hit, 0x2C) & 0x400)
        S16(u, 0x172) = 0;
    if (U16(hit, 0x1C) & 8)
        func_00245360(u, hit);
    if (U8(u, 0x19D) & 8)
        U8(u, 0x19D) &= ~8;
    if (func_00153DA0(u, v, rec) != 0) {
        int k;

        broke = 1;
        PTR(u, 0x110) = g_005B7120;
        U8(u, 0x19D) &= ~1;
        for (k = 0; k < 4; k++) {
            if (U8(u, 0x2DC + k * 0x70) & 1)
                func_0016E910(u + 0x290 + k * 0x70);
        }
        U8(u, 0x158) = 0x6C;
        func_00164B40(u, 0);
        if (S32(u, 0x11C) != 0) {
            float pos[4];

            func_0016A0D0(u, pos, 0x15);
            g_70000D60 = 1;
            func_001C7F30(8, pos, dir, 0);
        }
    }
    if ((u32)(S32(u, 0x118) - 0x3D) < 3) {
        func_002A6D20(PLAYER(u), 0x229);
        return 0;
    }
    if (PTR(u, 0x288) == 0) {
        if (S16(u, 0x172) != 0) {
            func_00153AB0(u, hit, dir);
            f = U32(hit, 0x28);
            goto tail;
        }
        if ((U32(rec, 0xB8) & 2) == 0 && func_00153990(u, v, rec) != 0) {
            func_00153B30(u, v, hit, dir);
        } else if ((U32(hit, 0x2C) & 0x400) == 0) {
            u32 af = U32(act, 0x18), f2 = U32(hit, 0x2C);

            if ((af & 0x60) == 0 && broke) {
                func_00151D60(u);
            } else if (U8(u, 0x19C) & 0x20) {
                func_00152250(u, (short *)act, hit, U32(rec, 0xB8) & 2, back);
            } else if ((U32(rec, 0xB8) & 2) == 0) {
                if (quiet == 0) {
                    if ((af & 0x20) == 0) {
                        if ((af & 0x40000) == 0) {
                            if ((af & 0x40) == 0 || (f2 & 2) == 0) {
                                unit_flinch(u, hit, dir, back, damage);
                            } else {
                                func_00152190(u, act, hit);
                                S16(u, 0x190) = 10;
                            }
                        } else if ((U32(PTR(DESC(u), 8) + U16(hit, 0xC) * 0x20, 0x18) & 0x400)
                                   == 0) {
                            int i;

                            flat_normalise(dir);
                            for (i = 0; i < 4; i++)
                                F32(u, 0x1F0 + i * 4) = dir[i] * -1.0f;
                            F32(u, 0x22C) = 3.0f;
                            func_00156AF0(u, back + 0x2C);
                            F32(u, 0x224) = 10.0f;
                            U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
                        } else {
                            unit_flinch(u, hit, dir, back, damage);
                        }
                    } else {
                        func_00153C40(u, hit, dir, back);
                    }
                } else {
                    F32(u, 0x244) = 5.0f;
                    stunned = 1;
                }
            } else if ((af & 0x20) == 0) {
                if ((af & 0x40) == 0 || (f2 & 2) == 0)
                    func_00151EB0(u, hit, back, dir);
                else
                    func_00152190(u, act, hit);
            } else {
                func_00153C40(u, hit, dir, back);
            }
        } else if ((U32(act, 0x18) & 0x20) == 0) {
            unit_flinch(u, hit, dir, back, damage);
        } else {
            func_00153C40(u, hit, dir, back);
        }
    } else {
        ret = func_00153610(u, hit, back, dir, rec, quiet, &stunned);
    }
    f = U32(hit, 0x28);
tail:
    if ((f & 0x10000) && (U32(ACT(u), 0x18) & 0x8000420) == 0 && stunned == 0 && hit[0x15] != 0)
        F32(u, 0x234) = (float)U32(unit_motion(u), 8) / (float)hit[0x15];
    if (PLAYER(u) < 2 && stunned == 0) {
        int k;

        for (k = 0; k < 3; k++) {
            u8 *e = g_00574DE0[k + PLAYER(u) * 3 + 0x89];

            if (e != 0 && (U8(e, 0x198) & 2) && U8(e, 0x15A) != 2 && U8(e, 0x15A) != 3
                && 30.0f < F32(e, 0x160)) {
                F32(e, 0x160) = 30.0f;
                break;
            }
        }
    }
    if ((s8)U8(u, 0x19C) >= 0) {
        int charged = (U8(u, 0x19F) & 0x10) != 0;

        func_0015EA30(u, v, hit, damage, charged ? -1 : 0, (U32(rec, 0xB8) & 2) != 0 && !charged,
                      quiet);
        U8(u, 0x19F) &= ~0x10;
    }
    return ret;
}

extern u8 *g_0045D2FC;                   /* (small data) the effects' resources */

void func_001D0970(Unit *u);
void func_001D0B20(Unit *u);
u32 func_00177ED0(void);
void func_001ACA70(u32 a, u8 *effect, float *pos, u8 *dir, u32 b);
float *func_0016A170(Unit *u, int node);
void func_001CD060(Unit *h, Unit *u, u8 *hit, u8 *dir, u8 *pos, int a, int b, int c);

#define VEC_ZERO ((float *)0x700000C0)   /* (0, 0, 0, 0) in the scratchpad */

/* 0x00155140, 0x118 bytes. Grabs `v` with hit `hit`: the follow-up action, facing `target`
 * (+0x1D0), and the hold (+0x280 / +0x284, the hit's two bytes for the held one). */
void func_00155140(Unit *u, Unit *v, u8 *hit, const float *target)
{
    short a = S16(ACT(u), 0);
    u8 *r = PTR(DESC(u), 0xC);
    int n = S32(PTR(DESC(u), 4), 0xC), i;
    float d[4], len;

    for (i = 0; i < n; i++, r += 0x30) {
        if (S16(r, 0x26) == a) {
            a = S16(r, 2);
            break;
        }
    }
    d[0] = target[0] - F32(u, 0x90);
    d[1] = 0.0f;
    d[2] = target[2] - F32(u, 0x98);
    d[3] = 0.0f;
    len = sqrtf(d[0] * d[0] + d[2] * d[2]);
    for (i = 0; i < 4; i++)
        F32(u, 0x1D0 + i * 4) = d[i] / len;
    func_00156AF0(u, a);
    func_001649C0(u);
    func_001649C0(v);
    PTR(u, 0x280) = v;
    PTR(v, 0x284) = u;
    U8(v, 0x275) = hit[8];
    U8(v, 0x276) = hit[9];
}

/* 0x00155260, 0xAC bytes. Thrown along `v` (the hit's speed +8, lift +9, reaction +0x10). */
void func_00155260(Unit *u, u8 *hit, const u32 *v)
{
    int i;

    U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
    for (i = 0; i < 4; i++)
        U32(u, 0x1F0 + i * 4) = v[i];
    F32(u, 0x22C) = (float)(s8)hit[8];
    for (i = 0; i < 4; i++)
        U32(u, 0x1D0 + i * 4) = U32(u, 0x1F0 + i * 4);
    func_00156AF0(u, S16(hit, 0x10));
    if (hit[9] != 0) {
        F32(u, 0x224) = (float)(s8)hit[9];
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
    }
}

/* 0x00155310, 0x48 bytes. Moves forward (+0x70) at `speed` for `dt`. */
int func_00155310(float dt, float speed, Unit *u)
{
    int i;

    F32(u, 0x228) = speed * dt;
    for (i = 0; i < 4; i++)
        F32(u, 0x40 + i * 4) += F32(u, 0x70 + i * 4) * (speed * dt);
    return 0;
}

/* The jump speed: 14 in mode 4, else the officer's (+0x94), a quarter of it (three quarters
 * close by) in the special state (+0xE8). */
static inline void unit_jump_speed(Unit *u)
{
    if (g_00669DB8 == 4) {
        F32(u, 0x224) = 14.0f;
    } else {
        u8 *rec = OFFICER(u);
        float s;

        if ((U8(u, 0xE8) & 3) >> 1 == 1) {
            float x = F32(u, 0xF0), z = F32(u, 0xF8);

            s = x * x + z * z < 100.0f ? F32(rec, 0x94) * 0.75f : F32(rec, 0x94) * 0.25f;
        } else {
            s = F32(rec, 0x94);
        }
        F32(u, 0x224) = s;
    }
}

/* 0x00155360, 0x614 bytes. Gravity for `dt` (`g`): starts a jump in the jumping actions, falls
 * (at most 30), and lands on the ground (+0xE0): the landing reaction, its dust and the mount's
 * effect. Whether it landed. */
int func_00155360(float dt, float g, Unit *u)
{
    float ground = 0.0f, saved = 0.0f, v;
    int fast, landing;

    if (S32(u, 0x118) < 0x3C && S16(ACT(u), 0) == 0xB) {
        if (U32(u, 0x13C) & 0x100000)
            unit_jump_speed(u);
    } else if (S32(u, 0x118) == 0x3C && S16(ACT(u), 0) == 0xF && (U32(u, 0x13C) & 0x10000)) {
        unit_jump_speed(u);
    }
    if (g_00669DB8 == 4) {
        saved = F32(u, 0x44);
        F32(u, 0x44) = (float)S16(u, 0x25A);
    }
    F32(u, 0x44) = (F32(u, 0x44) + 0.0f) - F32(u, 0x224) * dt;
    v = (F32(u, 0x224) + 0.0f) - g * dt;
    F32(u, 0x224) = v;
    if (v < -25.0f) {
        F32(u, 0x224) = -30.0f < v ? v : -30.0f;
        fast = 1;
    } else {
        fast = 0;
    }
    if (g_00669DB8 != 4)
        ground = F32(u, 0xE0);
    landing = F32(u, 0x224) < -0.0001f && !(F32(u, 0x44) <= ground + 0.0001f);
    if (g_00669DB8 == 4) {
        S16(u, 0x25A) = (short)(int)F32(u, 0x44);
        F32(u, 0x44) = saved;
    }
    if (!landing)
        return 0;
    {
        int hard = 0;
        u32 f = U32(ACT(u), 0x18);

        if (g_00669DB8 != 4)
            F32(u, 0x44) = ground;
        if ((U32(ACT(u), 0x18) & 0x40) == 0) {
            hard = 1;
            if (fast)
                func_00150E10(u);
            else
                func_00150C50(u);
            if (U8(u, 0x181) == 0)
                func_001D0970(u);
        } else {
            F32(u, 0x224) = 0.0f;
            F32(u, 0x228) = 0.0f;
            U8(u, 0x27C) &= ~2;
            if (U8(u, 0x181) == 0)
                func_001D0B20(u);
        }
        if ((f & 0x800) && hard && U32(u, 0x16C) != 0) {
            float *pos = S32(u, 0x11C) == 0 ? &F32(u, 0x40) : &F32(u, 0x90);

            func_001ACA70(func_00177ED0(), g_0045D2FC + 0x5F8, pos, u + 0x70, U32(u, 0x16C));
            U32(u, 0x16C) = 0;
        }
        if (S32(u, 0x118) == 0x3C && S32(u, 0x11C) != 0 && (s8)U8(u, 0x27C) >= 0
            && U32(u, 0x28C) != 0) {
            float *m = func_0016A170(u, 0x11);
            float *t = (float *)0x70000030;
            float p[4];
            int k;

            for (k = 0; k < 4; k++)
                p[k] = m[k] * t[0] + m[4 + k] * t[1] + m[8 + k] * t[2] + m[12 + k] * t[3];
            func_001ACA70(func_00177ED0(), g_0045D2FC + 0x5B0, p, u + 0x70, U32(u, 0x28C));
        }
        U8(u, 0x27C) &= 0x7F;
        return 1;
    }
}

/* 0x00155980, 0x100 bytes. Moves for `dt`: along +0x200 at the speed +0x228, plus the
 * velocity +0x1E0. */
int func_00155980(float dt, Unit *u)
{
    float v[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    int i;

    if (0.0001f < F32(u, 0x228)) {
        for (i = 0; i < 4; i++)
            v[i] = F32(u, 0x200 + i * 4) * (F32(u, 0x228) * dt);
    }
    if (0.0001f < F32(u, 0x1E0) * F32(u, 0x1E0) + F32(u, 0x1E8) * F32(u, 0x1E8)) {
        for (i = 0; i < 4; i++)
            v[i] += F32(u, 0x1E0 + i * 4) * dt;
    }
    for (i = 0; i < 4; i++)
        F32(u, 0x40 + i * 4) += v[i];
    return 1;
}

/* 0x00155A80, 0x98 bytes. The push (+0x1F0 at +0x22C) for `dt`, halved each frame on the
 * ground. */
int func_00155A80(float dt, Unit *u)
{
    int i;

    if (0.0001f <= F32(u, 0x22C)) {
        for (i = 0; i < 4; i++)
            F32(u, 0x40 + i * 4) += F32(u, 0x1F0 + i * 4) * (F32(u, 0x22C) * dt);
        if ((U32(ACT(u), 0x18) & 0x20) == 0)
            F32(u, 0x22C) = F32(u, 0x22C) * 0.5f;
    }
    return 1;
}

/* A direction normalised and scaled to 120 units. */
static inline void at_120(float *d)
{
    float len = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2] + d[3] * d[3]);
    int i;

    for (i = 0; i < 4; i++)
        d[i] = d[i] / len * 120.0f;
}

/* Faces the other way from `d`. */
static inline void face_away(Unit *u, const float *d)
{
    float a = vu0_angle(d[0], d[2]);

    F32(u, 0x238) = a;
    a = a + PI;
    if (PI < a)
        a -= TWO_PI;
    F32(u, 0x238) = a;
    U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
}

/* 0x00155B20, 0x284 bytes. Held 120 units from the one holding it (+0x280; or held by +0x284,
 * from its hand +0xA0 when +0x188 is set), facing it. */
int func_00155B20(Unit *u)
{
    float d[4];
    int i;

    if (PTR(u, 0x280) == 0) {
        Unit *h = PTR(u, 0x284);

        if (h != 0) {
            int hand = S16(h, 0x188) != 0;

            for (i = 0; i < 4; i++)
                d[i] = F32(u, 0x40 + i * 4) - F32(h, (hand ? 0xA0 : 0x40) + i * 4);
            at_120(d);
            if (!hand) {
                for (i = 0; i < 4; i++)
                    d[i] = F32(u, 0x40 + i * 4) - F32(h, 0x40 + i * 4);
            } else {
                for (i = 0; i < 4; i++)
                    F32(u, 0x40 + i * 4) = F32(h, 0xA0 + i * 4) + d[i];
            }
            face_away(u, d);
        }
    } else {
        float *c = &F32(PTR(u, 0x280), 0x40);

        for (i = 0; i < 4; i++)
            d[i] = F32(u, 0x40 + i * 4) - c[i];
        at_120(d);
        for (i = 0; i < 4; i++)
            F32(u, 0x40 + i * 4) = c[i] + d[i];
        face_away(u, d);
    }
    return 1;
}

/* 0x00155DB0, 0x9C bytes. Throws the unit it holds with hit `hit`, then lets go. */
void func_00155DB0(Unit *u, u8 *hit)
{
    Unit *h = PTR(u, 0x280);

    if (h == 0 || PTR(h, 0x284) != u) {
        func_0016BD30(u);
    } else {
        func_001CD060(h, u, hit, u + 0x70, u + 0x90, 0, 0, 0);
        func_00155260(PTR(u, 0x280), hit, (u32 *)(u + 0x70));
        func_0016BD30(u);
    }
}

/* 0x00155E50, 0xA0 bytes. Gets off what it carries (+0x288): placed at its seat, falling, and
 * the carried one's positions kept at +0xA0 / +0xB0. */
void func_00155E50(Unit *u)
{
    Unit *v = func_0016BE40(u);
    int i;

    func_001CF2A0(u, v, U32(ACT(u), 0x18) & 0x800);
    if (S32(v, 0x11C) != 0) {
        for (i = 0; i < 4; i++)
            U32(u, 0x40 + i * 4) = U32(u, 0x90 + i * 4);
        F32(u, 0x44) = F32(u, 0x44) + F32(PTR(u, 0x114), 0x80);
        F32(u, 0x224) = -5.0f;
    }
    for (i = 0; i < 4; i++)
        U32(u, 0xB0 + i * 4) = U32(v, 0x90 + i * 4);
    for (i = 0; i < 4; i++)
        U32(u, 0xA0 + i * 4) = U32(v, 0x40 + i * 4);
}

/* 0x00155EF0, 0x80 bytes. Speeds up by `dt` (at most 12) while a direction is held. */
void func_00155EF0(float dt, Unit *u)
{
    u32 f = U32(u, 0x13C);

    if ((f & 0x4000000) || (f & 0x8000000) || (f & 0x10000000) || (f & 0x20000000)) {
        float s = F32(u, 0x228) + dt;

        F32(u, 0x228) = s;
        F32(u, 0x228) = 12.0f < s ? 12.0f : s;
    }
}

/* 0x00155F70, 0x54 bytes. The motion's root movement (+0x80 times +0x60) applied in x and z,
 * then cleared; the movement in *out. */
void func_00155F70(Unit *u, float *out)
{
    int i;

    for (i = 0; i < 4; i++)
        out[i] = F32(u, 0x80 + i * 4) * F32(u, 0x60);
    F32(u, 0x40) = F32(u, 0x40) + out[0];
    F32(u, 0x48) = F32(u, 0x48) + out[2];
    for (i = 0; i < 4; i++)
        F32(u, 0x80 + i * 4) = VEC_ZERO[i];
}

/* 0x00155FD0, 0x98 bytes. The frame count of a motion pair (+0x30, +0x34): +0x44 for the jump's
 * (0xB / 0xC, mounted 0xF / 0x10), else the first motion's (+6). */
float func_00155FD0(Unit *u, u8 *m)
{
    if (S32(u, 0x118) < 0x3C) {
        if (S16(PTR(m, 0x34), 0) == 0xB && S16(PTR(m, 0x30), 0) == 0xC)
            return F32(m, 0x44);
    } else if (S32(u, 0x118) == 0x3C && S16(PTR(m, 0x34), 0) == 0xF
               && S16(PTR(m, 0x30), 0) == 0x10) {
        return F32(m, 0x44);
    }
    return (float)S16(PTR(m, 0x30), 6);
}

extern u8 g_00669E2A[][0x48];            /* per player: the controller's vibration level? */

float func_00136E18(float x, float y);   /* fmodf */
void func_001CE800(Unit *u);
void func_001CE9A0(Unit *u);
void func_001CEA20(Unit *u);
int func_002A6910(int sound, int a, u8 *pos);
void func_002A5A60(float a, float b, float c, float d, float e, int sound);
void func_002A5B10(int sound);
void func_001489F0(u8 *actor, u8 *model);
void func_001589B0(Unit *u, u8 kind, u8 slot);
void func_0029F3C0(Unit *u);
void func_0016CB60(Unit *u, u8 level, int a, int b, int c);
void func_0016A1C0(Unit *u);
void func_00148B60(u8 *actor, int first, int last);

/* An angle brought into (-pi, pi] after fmodf by 2 pi. */
static inline float angle_mod(float a)
{
    float f = func_00136E18(a, TWO_PI);

    if (PI < f)
        return func_00136E18(a, TWO_PI) - TWO_PI;
    if (f <= -PI)
        return func_00136E18(a, TWO_PI) + TWO_PI;
    return func_00136E18(a, TWO_PI);
}

/* Saves the pose of a model object's nodes for a transition (see model.c, func_0014E380). */
static inline void save_pose(u8 *actor)
{
    float *n = *(float **)(actor + 0x208);
    float *s = *(float **)(actor + 0x218);
    u8 *m = (actor[0x20C] & 2) ? PTR(actor, 0x1EC) : PTR(actor, 0x1E8);
    u32 i, count = m[0x29];

    for (i = 0; i < count; i++, n += 0x1C, s += 8) {
        s[4] = n[0];
        s[5] = n[1];
        s[6] = n[2];
        s[7] = n[3];
        s[0] = angle_mod(n[4]);
        s[1] = angle_mod(n[5]);
        s[2] = angle_mod(n[6]);
    }
}

void func_00156070(Unit *u);

/* 0x00156070, 0x6AC bytes. Starts a transition to the new action: the length from the motion
 * pair, the pose saved (the root at its height only), and the same for the two extra motion
 * slots (+0x290 + 0x44 / +0x300 + 0x44) when the action uses them. */
void func_00156070(Unit *u)
{
    u8 *a = PTR(u, 0x11C);
    float *s;
    float len;

    if (PTR(a, 0x208) == 0)
        return;
    len = func_00155FD0(u, u + 0x1E0);
    F32(a, 0x214) = len;
    F32(a, 0x210) = len;
    U8(a, 0x21D) = (U32(PTR(u, 0x214), 0x18) & 0x40000000) != 0;
    if (g_00669DB8 == 4)
        U8(a, 0x21D) = 0;
    U8(a, 0x21E) = (U32(ACT(u), 0x18) & 0x8000000) != 0;
    save_pose(a);
    s = *(float **)(a + 0x218);
    s[4] = 0.0f;
    s[5] = F32(PTR(PTR(u, 0x11C), 0x208), 4);
    s[6] = 0.0f;
    s[7] = 1.0f;
    if (S16(ACT(u), 0xA) != -1 && (U8(u, 0x2DC) & 4)) {
        u8 *b = PTR(u, 0x2D4);

        F32(b, 0x214) = F32(a, 0x214);
        F32(b, 0x210) = F32(a, 0x214);
        U8(b, 0x21D) = 0;
        U8(b, 0x21E) = 1;
        save_pose(b);
    }
    if (S16(ACT(u), 8) != -1 && (U8(u, 0x34C) & 4)) {
        u8 *b = PTR(u, 0x344);

        F32(b, 0x214) = F32(a, 0x214);
        F32(b, 0x210) = F32(a, 0x214);
        U8(b, 0x21D) = 0;
        U8(b, 0x21E) = 1;
        save_pose(b);
    }
}

/* 0x00156720, 0x3D0 bytes. After an action change: the lift kept or dropped by the hits'
 * flags, entering / leaving the air and the 0x200000 states, the players' looping sound for the
 * actions 0x6D-0x6E, the nodes to rebuild, the hit's messages and effect timers. */
void func_00156720(Unit *u)
{
    u8 *act = ACT(u), *prev = PTR(u, 0x214);
    u8 *hit = PTR(act, 0x14);

    if (hit != 0 && (U32(prev, 0x18) & 0x20)) {
        if ((U32(hit, 0x28) & 1) == 0) {
            if (U32(hit, 0x28) & 0x80)
                F32(u, 0x224) = 0.0f < F32(u, 0x224) ? F32(u, 0x224) * 0.5f : 0.0f;
        } else {
            F32(u, 0x224) = 0.0f;
        }
    }
    if (hit != 0 && PTR(prev, 0x14) != 0 && (U32(PTR(prev, 0x14), 0x28) & 0x80)
        && (U32(hit, 0x28) & 1))
        F32(u, 0x224) = 0.0f;
    if ((U32(prev, 0x18) & 0x40) == 0 && (U32(act, 0x18) & 0x40)) {
        F32(u, 0x22C) = 0.0f;
        func_001CE800(u);
    }
    if ((U32(prev, 0x18) & 0x200000) == 0 && (U32(act, 0x18) & 0x200000))
        func_001CE9A0(u);
    if ((U32(prev, 0x18) & 0x200000) && (U32(act, 0x18) & 0x200000) == 0)
        func_001CEA20(u);
    if (PLAYER(u) < 2) {
        u8 *a;

        if (S32(u, 0x128) == -1) {
            if ((u16)(U16(act, 0) - 0x6D) < 2) {
                int s = func_002A6910(0x23A, 0, u + 0x40);

                S32(u, 0x128) = s;
                if (s != 0x107)
                    func_002A5A60(270.0f, 600.0f, 2000.0f, 2250.0f, 1.0f, s);
            }
        } else if (U16(act, 0) != 0x6D && U16(act, 0) != 0x6E) {
            if (S32(u, 0x128) != 0x107)
                func_002A5B10(S32(u, 0x128));
            S32(u, 0x128) = -1;
        }
        a = PTR(u, 0x11C);
        if (a != 0) {
            if (prev != 0 && PTR(prev, 0x14) != 0 && (U16(PTR(prev, 0x14), 0x1C) & 1))
                func_001489F0(a, PTR(a, 0x1E8));
            if (prev != 0 && (U32(prev, 0x1C) & 0x20000))
                func_001489F0(PTR(u, 0x11C), PTR(PTR(u, 0x11C), 0x1E8));
        }
    }
    if (hit != 0 && (s8)U8(u, 0x19C) >= 0) {
        if ((U32(hit, 0x2C) & 0x1000000) && g_00669DB8 != 4)
            func_002A6D20(PLAYER(u), 0x239);
        if (PLAYER(u) < 2) {
            if (U32(hit, 0x2C) & 0x40000000) {
                u32 k;

                for (k = 0; (int)k < 3; k++) {
                    u8 *e = g_00574DE0[k + PLAYER(u) * 3 + 0x89];

                    if (e != 0 && (U8(e, 0x198) & 2) == 0) {
                        func_001589B0(u, 2, k);
                        U8(u, 0x196) = 1;
                        break;
                    }
                }
            }
            if (U32(hit, 0x2C) & 0x40) {
                U8(u, 0x157) = 0;
                S16(u, 0x194) = 0;
            }
        }
    }
    if ((U32(act, 0x18) & 0x800) == 0)
        U8(u, 0x19F) &= ~8;
    func_0029F3C0(u);
}

/* 0x00156AF0, 0xD60 bytes. Starts action `id` (an index into the unit's description: ignored
 * when out of range, without motion, or a mounted action the weapon kind lacks): the root
 * movement settled, the previous action kept (+0x214), the speeds by the action's kind, getting
 * off or throwing, the turn the action makes (by the direction held or its flags), the model's
 * extra motion slots and the transition, and the action's state reset. */
void func_00156AF0(Unit *u, u16 id)
{
    u8 tmp[16];
    u8 *d = DESC(u);
    u8 *act, *prev, *hit, *oldrec, *newrec;
    float turn = 0.0f;
    int keep = 0, i;
    short aid;

    for (i = 0; i < 16; i++)
        tmp[i] = 0;
    if (U32(PTR(d, 4), 8) <= id)
        return;
    act = PTR(d, 8) + id * 0x20;
    if (S16(act, 2) == -1)
        return;
    if ((U32(act, 0x1C) & 0x80000000) && (U8(g_005B5078[U8(d, 0x1C)], 0x54) & 1) == 0)
        return;
    if (id != 0x55 && id != 0x56)
        func_00155F70(u, (float *)tmp);
    PTR(u, 0x214) = PTR(u, 0x210);
    oldrec = unit_motion(u);
    PTR(u, 0x210) = act;
    prev = PTR(u, 0x214);
    if (prev != 0 && (U32(prev, 0x18) & 0x800) && (U32(prev, 0x18) & 0x40) == 0 && id != 0x45)
        F32(u, 0x228) = F32(u, 0x22C);
    act = ACT(u);
    aid = S16(act, 0);
    hit = PTR(act, 0x14);
    if (aid == 0x34 || aid == 0x35) {
        F32(u, 0x224) = 5.0f;
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        F32(u, 0x228) = F32(u, 0x228) * 0.5f;
        F32(u, 0x22C) = F32(u, 0x22C) * 0.5f;
        if (PLAYER(u) < 2)
            func_0016CB60(u, g_00669E2A[PLAYER(u)][0], 1, 0xFF, 0xF);
    } else if (aid == 0x36 || aid == 0x37) {
        F32(u, 0x224) = 7.0f;
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        F32(u, 0x228) = F32(u, 0x228) * 0.75f;
        F32(u, 0x22C) = F32(u, 0x22C) * 0.75f;
        if (PLAYER(u) < 2)
            func_0016CB60(u, g_00669E2A[PLAYER(u)][0], 1, 0xFF, 0xF);
    }
    prev = PTR(u, 0x214);
    if (prev != 0 && (U32(act, 0x18) & 0x8000000) == 0 && (U32(prev, 0x18) & 0x8000000))
        func_00155E50(u);
    if (hit != 0 && (U32(hit, 0x2C) & 0x800) && PTR(u, 0x280) != 0)
        func_00155DB0(u, hit);
    if ((U32(act, 0x18) & 0x800) == 0)
        U32(u, 0x16C) = 0;
    newrec = unit_motion(u);
    if (((U32(PTR(u, 0x214), 0x18) & 0x40000000) && (U32(ACT(u), 0x18) & 0x20))
        || ((U32(PTR(u, 0x214), 0x18) & 0x40000) && (U32(ACT(u), 0x18) & 0x800)
            && (U32(ACT(u), 0x18) & 0x20))) {
        float y = F32(u, 0x94) - F32(newrec, 0x14);

        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        for (i = 0; i < 4; i++)
            U32(u, 0x200 + i * 4) = U32(u, 0x1D0 + i * 4);
        if (g_00669DB8 != 4)
            F32(u, 0x44) = F32(u, 0xE0) < y ? F32(u, 0xE0) : y;
    }
    if (g_00669DB8 != 4) {
        short a = S16(ACT(u), 0);
        int turned = 0;

        if (a == 1 || a == 2 || a == 3 || a == 4) {
            float x = F32(u, 0x1D0), z = F32(u, 0x1D8);

            if (0.0001f < x * x + z * z && U8(u, 0x155) == 0) {
                turn = wrap_angle(vu0_angle(x, z) - F32(u, 0x54));
                turned = 1;
            }
        }
        if (!turned) {
            u32 f = U32(ACT(u), 0x18);

            if (f & 0x4000) {
                turn = PI;
                keep = U8(u, 0x155) == 1;
            } else if (f & 0x8000) {
                turn = -1.5707964f;
                keep = U8(u, 0x155) == 1;
            } else if (f & 0x10000) {
                turn = 1.5707964f;
                keep = U8(u, 0x155) == 1;
            } else {
                turn = 0.0f;
            }
        }
    }
    {
        float y = F32(u, 0x54) + turn;

        if (PI < y)
            y -= TWO_PI;
        else if (y <= -PI)
            y += TWO_PI;
        F32(u, 0x238) = y;
        F32(u, 0x54) = y;
        F32(u, 0x230) = 0.0f;
        if (S32(u, 0x118) == 0x3C)
            U8(u, 0x27C) &= ~1;
        else
            U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
    }
    if (PTR(u, 0x11C) != 0 && U8(u, 0x155) == 0) {
        u8 *nodes = PTR(PTR(u, 0x11C), 0x208);
        float r = F32(nodes, 0x80) - turn;

        if (PI < r)
            r -= TWO_PI;
        else if (r <= -PI)
            r += TWO_PI;
        F32(nodes, 0x80) = r;
        nodes = PTR(PTR(u, 0x11C), 0x208);
        r = F32(nodes, 0x390) + turn;
        if (PI < r)
            r -= TWO_PI;
        else if (r <= -PI)
            r += TWO_PI;
        F32(nodes, 0x390) = r;
    }
    if (PTR(u, 0x11C) != 0) {
        if ((U32(ACT(u), 0x1C) & 0x2000000) == 0) {
            if (U8(u, 0x19D) & 1) {
                for (i = 0; i < 4; i++) {
                    if (U8(u, 0x2DC + i * 0x70) & 1)
                        func_0016E910(u + 0x290 + i * 0x70);
                }
                func_00164B40(u, 0);
                U8(u, 0x19D) &= ~1;
            }
        } else if ((U8(u, 0x19D) & 1) == 0) {
            for (i = 0; i < 4; i++) {
                if (U8(u, 0x2DC + i * 0x70) & 1)
                    func_0016E910(u + 0x290 + i * 0x70);
            }
            func_00164B40(u, 1);
            U8(u, 0x19D) = (U8(u, 0x19D) & ~1) | 1;
        }
        if (PTR(u, 0x214) != 0 && (U32(PTR(u, 0x214), 0x1C) & 0x10) && PTR(u, 0x11C) != 0)
            func_00148B60(PTR(u, 0x11C), 0xE, 0x15);
    }
    if (PTR(u, 0x11C) != 0) {
        u8 *a = PTR(u, 0x11C);

        if (0.0f < F32(a, 0x214)) {
            F32(a, 0x210) = 0.0f;
            F32(a, 0x214) = 0.0f;
            U8(u, 0x27C) &= ~0x20;
        }
        if (S16(ACT(u), 0xA) != -1 && (U8(u, 0x2DC) & 4)) {
            u8 *b = PTR(u, 0x2D4);

            if (0.0f < F32(b, 0x214)) {
                F32(b, 0x210) = 0.0f;
                F32(b, 0x214) = 0.0f;
            }
        }
        if (S16(ACT(u), 8) != -1 && (U8(u, 0x34C) & 4)) {
            u8 *b = PTR(u, 0x344);

            if (0.0f < F32(b, 0x214)) {
                F32(b, 0x210) = 0.0f;
                F32(b, 0x214) = 0.0f;
            }
        }
        if (!keep) {
            int blend = 0 < S16(ACT(u), 6);

            if (S16(PTR(u, 0x214), 4) == S16(ACT(u), 0) && (U32(PTR(u, 0x214), 0x18) & 0x80000))
                blend = 0;
            if (blend && oldrec != newrec)
                func_00156070(u);
        }
    }
    hit = PTR(ACT(u), 0x14);
    F32(u, 0x21C) = (float)(hit == 0 || (U32(hit, 0x28) & 0x800000) == 0 ? 0 : hit[5]);
    F32(u, 0x23C) = 0.0f;
    F32(u, 0x220) = 0.0f;
    F32(u, 0x234) = 1.0f;
    F32(u, 0x218) = 0.0f;
    {
        u8 b = U8(u, 0x27C);
        u8 was = (b >> 3 & 1) << 4;

        U8(u, 0x27C) = (b & 0xEF) | was;
        U8(u, 0x27C) = (b & 0xE7) | was;
    }
    S16(u, 0x278) = -1;
    U8(u, 0x27C) = (U8(u, 0x27C) & ~0x40) | 0x40;
    if ((U32(ACT(u), 0x18) & 0x800) == 0)
        U8(u, 0x19F) &= ~1;
    if ((U32(ACT(u), 0x18) & 0x8000000) == 0)
        U8(u, 0x19F) &= ~0x40;
    func_00150930(u);
    func_0016A1C0(u);
    func_00156720(u);
}

extern u8 g_005B4BC0[][0x240];           /* per player: the camera (+0 its matrix) */
extern u8 g_00732644[][0x14];            /* per player: the struggle display */
extern float g_00424A58[2];              /* two spread angles */
extern float g_00424A60[4];              /* four spread angles */
extern float g_00406410[4];              /* the forward vector */
extern float g_00406420[4];
extern float g_00424D00[4];              /* the up vector */

void vu0_rot_x(float m[4][4], float a);          /* VU0 micro subroutine 0x60: rotation about X */
void func_001FAA60(u8 player);
void func_001AD090(u8 *e);
void func_001AE1A0(u8 *e);
void func_001AC980(u32 e, u8 *a, u8 *b, float *dir, Unit *u);
void func_00166160(Unit *e);
void func_001656E0(Unit *e, int state, u8 kind, u8 a, u8 b, u8 c, u8 d, int f);
void func_001660C0(Unit *e, u8 *pos);
void func_00253CB0(Unit *e, u8 kind);

/* The unit matrix from the scratchpad. */
static inline void scratch_unit(float m[4][4])
{
    int i, k;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i][k] = ((float *)0x70000000)[i * 4 + k];
}

/* m * v (column vectors). */
static inline void mat_vec(float out[4], float m[4][4], const float v[4])
{
    int k;

    for (k = 0; k < 4; k++)
        out[k] = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2] + m[3][k] * v[3];
}

/* 0x00157850, 0x74 bytes. Whether the unit is on the right of its player's camera. */
int func_00157850(Unit *u)
{
    float v[4];

    mat_vec(v, (float (*)[4])g_005B4BC0[PLAYER(u)], &F32(u, 0x90));
    return 0.0f < v[0];
}

/* 0x001578D0, 0x288 bytes. A struggle between two units (the button presses counted at +0x159):
 * the players' display, and the outcome (*mine / *theirs: 1-4) once one leads by more than 12
 * or the struggle's time is up. Whether it is over. */
int func_001578D0(Unit *u, int *mine, int *theirs)
{
    u8 *hit;
    int end;
    Unit *o;

    if (PLAYER(u) < 2) {
        u8 oc = U8(PTR(u, 0x280), 0x159);
        u8 *e = g_00732644[PLAYER(u)];
        int diff;

        if (func_00157850(u) == 0) {
            e[8] = 1;
            *(u32 *)(e + 0) = oc;
            *(u32 *)(e + 4) = U8(u, 0x159);
            e[0xB] = 1;
            e[0xC] = 0;
        } else {
            e[8] = 1;
            *(u32 *)(e + 0) = U8(u, 0x159);
            *(u32 *)(e + 4) = oc;
            e[0xB] = 0;
            e[0xC] = 1;
        }
        diff = U8(u, 0x159) - oc;
        if (diff > 0xC) {
            *mine = 2;
            *theirs = 4;
            U32(u, 0x270) = U32(u, 0x280);
            return 1;
        }
        if (diff < -0xC) {
            *mine = 4;
            *theirs = 1;
            return 1;
        }
    }
    hit = PTR(ACT(u), 0x14);
    if (hit == 0 || (U32(hit, 0x28) & 0x800000) == 0)
        end = S32(unit_motion(u), 8) - 1;
    else
        end = hit[6];
    if ((int)F32(u, 0x21C) < end)
        return 0;
    o = PTR(u, 0x280);
    if (U8(o, 0x159) < U8(u, 0x159)) {
        *mine = 1;
        *theirs = 3;
    } else if (U8(u, 0x159) < U8(o, 0x159)) {
        *mine = 3;
        *theirs = 1;
    } else {
        *mine = 3;
        *theirs = 3;
    }
    return 1;
}

/* An officer's life set to 0 (as the original computes it from +0x86, always 0). */
static inline void officer_ko(u8 *rec)
{
    short v = S16(rec, 0x86);
    short l = v < 0 ? v : 0;
    short s;

    if (l < 1) {
        s = 0;
    } else {
        s = v;
        if (s >= 0)
            s = 0;
    }
    S16(rec, 0x88) = s;
}

/* 0x00157B60, 0x374 bytes. Ends a struggle with results `mine` / `theirs` (3: knocked out; 2: the
 * winner throws the other 120 units away, facing it), and lets go. */
void func_00157B60(Unit *u, int mine, int theirs)
{
    Unit *o;

    func_00152410(u, mine);
    if (mine == 3)
        officer_ko(OFFICER(u));
    o = PTR(u, 0x280);
    if (U8(o, 0x198) & 2) {
        func_00152410(PTR(u, 0x280), theirs);
        o = PTR(u, 0x280);
        if (PLAYER(u) < 2 && mine == 2) {
            float d[4], a, len;
            int i;

            for (i = 0; i < 4; i++)
                d[i] = F32(o, 0x40 + i * 4) - F32(u, 0x40 + i * 4);
            d[1] = 0.0f;
            len = sqrtf(d[0] * d[0] + d[2] * d[2] + d[3] * d[3]);
            for (i = 0; i < 4; i++)
                d[i] = d[i] / len;
            a = vu0_angle(d[0], d[2]);
            F32(u, 0x54) = a;
            F32(u, 0x238) = a;
            F32(u, 0x230) = 0.0f;
            U8(u, 0x27C) = (U8(u, 0x27C) & ~1) | 1;
            a = F32(u, 0x54) + PI;
            if (PI < a)
                a -= TWO_PI;
            F32(PTR(u, 0x280), 0x54) = a;
            for (i = 0; i < 4; i++)
                F32(PTR(u, 0x280), 0x40 + i * 4) = F32(u, 0x40 + i * 4) + d[i] * 120.0f;
            F32(o, 0x238) = F32(PTR(u, 0x280), 0x54);
            F32(o, 0x230) = 0.0f;
            U8(o, 0x27C) = (U8(o, 0x27C) & ~1) | 1;
        }
        if (theirs == 3)
            officer_ko(OFFICER(PTR(u, 0x280)));
        PTR(o, 0x284) = 0;
        U8(o, 0x275) = 0xFF;
        U8(o, 0x276) = 0xFF;
        U8(PTR(u, 0x280), 0x27C) &= ~4;
    }
    PTR(u, 0x280) = 0;
    U8(u, 0x27C) &= ~4;
    if (PLAYER(u) < 2) {
        func_0029EE00(g_005B49E0[PLAYER(u)], 0);
        func_001FAA60(PLAYER(u));
    }
}

/* 0x00157EE0, 0x1EC bytes. The locked target (+0x270): the angle to it from the unit's facing,
 * and in *turn the turning speed (5 or 10 degrees) while it stays within 60 (or 90) degrees;
 * else the lock is dropped and 0 returned. */
float func_00157EE0(Unit *u, float *turn)
{
    u8 *hit;

    if (PTR(u, 0x270) != 0) {
        hit = PTR(ACT(u), 0x14);
        if (hit != 0 && PTR(u, 0x280) == 0) {
            float lim, speed, a;

            if ((U32(hit, 0x2C) & 4) == 0) {
                lim = 1.0471976f;
                speed = 0.08726646f;
            } else {
                lim = 1.5707964f;
                speed = 0.17453292f;
            }
            a = wrap_angle(vu0_angle(F32(PTR(u, 0x270), 0x90) - F32(u, 0xB0),
                                     F32(PTR(u, 0x270), 0x98) - F32(u, 0xB8))
                           - F32(u, 0x54));
            if ((U32(ACT(u), 0x1C) & 0x20) || fabsf(a) <= lim) {
                *turn = speed;
                return a;
            }
        }
        PTR(u, 0x270) = 0;
    }
    U8(u, 0x27C) &= ~0x10;
    return 0.0f;
}

/* The hit's number of stored projectiles: 6, 4 or 2 (fired 3, 2 or 1 at a time). */
#define STORE_COUNT(hit) ((U32(hit, 0x2C) & 0x20) ? 6 : (U32(hit, 0x2C) & 0x10) ? 4 : 2)

/* 0x001580D0, 0x19C bytes. Stores projectile effect `id` (slots +0x260); when they are full the
 * oldest is dropped. */
void func_001580D0(Unit *u, short id, u8 *hit)
{
    int n = STORE_COUNT(hit), i;
    short *slot = &S16(u, 0x260);

    for (i = 0; i < n; i++) {
        if (slot[i] == -1) {
            slot[i] = id;
            return;
        }
    }
    U8(g_005ADD80[slot[0]], 0x8C) &= ~2;
    for (i = 0; i < n - 1; i++)
        slot[i] = slot[i + 1];
    slot[i] = id;
}

/* 0x00158270, 0x1AC bytes. Fires the stored projectiles (1-3 by the hit), with a sound, then
 * packs the slots. */
void func_00158270(Unit *u, u8 *b, u8 *hit)
{
    short *slot = &S16(u, 0x260);
    int n = (U32(hit, 0x2C) & 0x20) ? 3 : (U32(hit, 0x2C) & 0x10) ? 2 : 1;
    int fired = 0, any = 0, i, j;

    for (i = 0; i < 6; i++) {
        if (slot[i] != -1) {
            u8 *e = g_005ADD80[slot[i]];
            float pos[4], dir[4];
            int k;

            for (k = 0; k < 4; k++) {
                pos[k] = F32(e, 0x30 + k * 4);
                dir[k] = F32(e, 0x20 + k * 4);
            }
            func_002A6910(0x231, 0, (u8 *)pos);
            func_001AD090(e);
            func_001AE1A0(e);
            func_001ACA70((u32)e, b, pos, (u8 *)dir, (u32)u);
            fired++;
            any = 1;
            slot[i] = -1;
            if (fired >= n)
                break;
        }
    }
    if (any) {
        for (i = 0, j = 0; i < 6; i++) {
            if (slot[i] != -1) {
                if (j == i) {
                    j++;
                } else {
                    slot[j++] = slot[i];
                    slot[i] = -1;
                }
            }
        }
    }
}

/* Fires `n` effects spread by `angles` about `dir`. */
static inline void fire_spread(Unit *u, u8 *a, u8 *b, const float *dir, const float *angles, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        float m[4][4], v[4];
        u32 e;

        scratch_unit(m);
        vu0_rot_y(m, angles[i]);
        mat_vec(v, m, dir);
        e = func_00177ED0();
        U8(e, 0x8C) = (U8(e, 0x8C) & ~8) | 8;
        func_001AC980(e, a, b, v, u);
    }
}

/* 0x00158420, 0x114 bytes. Fires two effects spread about `dir`. */
void func_00158420(Unit *u, u8 *a, u8 *b, const float *dir)
{
    fire_spread(u, a, b, dir, g_00424A58, 2);
}

/* 0x00158540, 0x114 bytes. Fires four. */
void func_00158540(Unit *u, u8 *a, u8 *b, const float *dir)
{
    fire_spread(u, a, b, dir, g_00424A60, 4);
}

/* 0x00158660, 0x350 bytes. Fires effect `k` from the weapon (kind 0: weapons ',' and 0x1F, from
 * node 0x13; kind 1: '-' and 0x1E, node 0x14; kind 2: node 0x12; without a model, from the
 * unit's height), aimed by its pitch (+0x240) and yaw. */
void func_00158660(Unit *u, int k)
{
    u8 c = DESC(u) == 0 ? 'j' : U8(DESC(u), 0x1C);
    int kind, i;
    float pos[4], dir[4], m[4][4];

    if (c == ',' || c == 0x1F)
        kind = 0;
    else if (c == '-' || c == 0x1E)
        kind = 1;
    else
        kind = 2;
    if (PTR(u, 0x11C) == 0) {
        for (i = 0; i < 4; i++)
            pos[i] = F32(u, 0x40 + i * 4);
        pos[1] = pos[1] - F32(PTR(u, 0x114), 0x80);
    } else {
        float (*n)[4] = (float (*)[4])func_0016A170(u, kind == 0 ? 0x13 : kind == 1 ? 0x14 : 0x12);

        mat_vec(pos, n, kind == 1 ? g_00406420 : (float *)0x70000030);
        for (i = 0; i < 4; i++)
            pos[i] = pos[i] / pos[3];
    }
    scratch_unit(m);
    vu0_rot_x(m, F32(u, 0x240));
    vu0_rot_y(m, F32(u, 0x54));
    mat_vec(dir, m, g_00406410);
    func_001ACA70(func_00177ED0(), g_0045D2FC + 0x10 + (k + kind) * 0x48, pos, (u8 *)dir, (u32)u);
}


/* 0x001589B0, 0x318 bytes. Calls bodyguard `slot` of the unit's player (units 0x89 + player * 3
 * + slot) as `kind` 0-3: placed at the unit, beside it (left, right, behind or ahead by the
 * slot), with its timer (600, 600, 60 frames copying the unit's action, or 630 at size 1.5). */
void func_001589B0(Unit *u, u8 kind, u8 slot)
{
    Unit *e = g_00574DE0[slot + PLAYER(u) * 3 + 0x89];
    float side[4], len;
    int i;

    if (e == 0)
        return;
    if (U8(e, 0x198) & 2)
        func_00166160(e);
    func_001656E0(e, S32(u, 0x118), U8(DESC(u), 0x1C), U8(u, 0x158), U8(u, 0x156), U8(u, 0x154),
                  U8(u, 0x14F), 0);
    func_001660C0(e, u + 0x40);
    F32(e, 0x238) = F32(u, 0x54);
    U8(e, 0x27C) &= ~1;
    for (i = 0; i < 4; i++)
        U32(e, 0x50 + i * 4) = U32(u, 0x50 + i * 4);
    U8(e, 0x17C) = slot;
    U8(e, 0x15B) = PLAYER(u);
    side[0] = F32(u, 0x74) * g_00424D00[2] - F32(u, 0x78) * g_00424D00[1];
    side[1] = F32(u, 0x78) * g_00424D00[0] - F32(u, 0x70) * g_00424D00[2];
    side[2] = F32(u, 0x70) * g_00424D00[1] - F32(u, 0x74) * g_00424D00[0];
    side[3] = 0.0f;
    len = sqrtf(side[0] * side[0] + side[1] * side[1] + side[2] * side[2]);
    if (U8(e, 0x17C) == 0) {
        for (i = 0; i < 4; i++)
            F32(e, 0xC0 + i * 4) = side[i] / len;
    } else if (U8(e, 0x17C) == 1) {
        for (i = 0; i < 4; i++)
            F32(e, 0xC0 + i * 4) = side[i] / len * -1.0f;
    } else if (U8(e, 0x17C) == 2) {
        for (i = 0; i < 4; i++)
            U32(e, 0xC0 + i * 4) = U32(u, 0x70 + i * 4);
    } else {
        for (i = 0; i < 4; i++)
            F32(e, 0xC0 + i * 4) = F32(e, 0x70 + i * 4) * -1.0f;
    }
    U8(e, 0x19C) = (U8(e, 0x19C) & 0x7F) | 0x80;
    S16(e, 0x178) = S16(u, 0x178);
    U8(e, 0x15A) = kind;
    F32(e, 0x164) = 0.0f;
    func_00253CB0(e, U8(e, 0x15A));
    if (U8(e, 0x15A) == 3) {
        F32(e, 0x160) = 630.0f;
        F32(e, 0x60) = 1.5f;
        F32(e, 0x64) = 1.5f;
        F32(e, 0x68) = 1.5f;
        F32(e, 0x6C) = 0.0f;
    } else if (U8(e, 0x15A) == 2) {
        F32(e, 0x160) = 60.0f;
        func_00156AF0(e, U16(ACT(u), 0));
        F32(e, 0x21C) = F32(u, 0x21C);
        F32(e, 0x234) = 0.0f;
        U8(e, 0x14D) = 0x80;
    } else if (U8(e, 0x15A) == 1) {
        F32(e, 0x160) = 600.0f;
    } else if (U8(e, 0x15A) == 0) {
        F32(e, 0x160) = 600.0f;
    }
}

extern u32 g_00669DE8[][0x12];           /* per player (0x48 bytes): +0 a level */

float func_001F2B70(void);
void func_001F2EF0(void *move);
void func_00161520(float *out, Unit *u);
u8 *func_0016C980(u8 player, int frames_back);
u8 func_002F41E0(u32 level);

/* A player's bodyguard `slot` (units 0x89 + player * 3 + slot), or 0. */
#define BODYGUARD(p, slot) g_00574DE0[(slot) + (p) * 3 + 0x89]

/* 0x00158CD0, 0xB8 bytes. Dismisses the player's bodyguards of kind `kind` (4: all). */
void func_00158CD0(Unit *u, u32 kind)
{
    int i;

    for (i = 0; i < 3; i++) {
        Unit *e = BODYGUARD(PLAYER(u), i);

        if (e != 0 && (U8(e, 0x198) & 2) && (kind == 4 || kind == U8(e, 0x15A)))
            func_00166160(e);
    }
}

/* 0x00158D90, 0x70 bytes. The number of the player's bodyguards present. */
int func_00158D90(Unit *u)
{
    int n = 0, i;

    for (i = 0; i < 3; i++) {
        Unit *e = BODYGUARD(PLAYER(u), i);

        if (e != 0 && (U8(e, 0x198) & 2))
            n++;
    }
    return n;
}

/* A move test (func_001F2EF0): from `from` to `to` for unit `who`. */
typedef struct {
    float *from;
    float *to;
    Unit *who;
    u32 radius;
    u32 a;
    u32 b;
    u8 blocked;
} MoveTest;

/* 0x00158E00, 0x1A8 bytes. A bodyguard's appearance: kind 1 steps out of its player 4 units a
 * frame for 25 frames (on the ground, facing as the player does; it vanishes when blocked);
 * kinds 2 and others only set their alpha. */
void func_00158E00(Unit *e)
{
    Unit *m = g_00574DE0[U8(e, 0x15B)];

    if (U8(e, 0x15A) == 1) {
        if (F32(e, 0x164) < 25.0f) {
            float pos[4], from[4], to[4], h;
            MoveTest t;
            int i;

            for (i = 0; i < 4; i++)
                pos[i] = F32(e, 0x40 + i * 4) + F32(e, 0xC0 + i * 4) * 4.0f;
            pos[1] = func_001F2B70();
            func_001660C0(e, (u8 *)pos);
            F32(e, 0x238) = F32(m, 0x54);
            U8(e, 0x27C) &= ~1;
            for (i = 0; i < 4; i++)
                U32(e, 0x50 + i * 4) = U32(m, 0x50 + i * 4);
            h = F32(PTR(m, 0x114), 0x80);
            for (i = 0; i < 4; i++) {
                from[i] = F32(m, 0x40 + i * 4);
                to[i] = pos[i];
            }
            from[1] = F32(m, 0x44) - h;
            to[1] = pos[1] - h;
            t.from = from;
            t.to = to;
            t.who = m;
            t.radius = U32(PTR(m, 0x114), 0x88);
            t.a = 0;
            func_001F2EF0(&t);
            if (t.blocked)
                F32(e, 0x160) = 0.0f;
            U32(e, 0x13C) = 0;
            for (i = 0; i < 4; i++)
                F32(e, 0x1D0 + i * 4) = VEC_ZERO[i];
        }
    } else if (U8(e, 0x15A) == 2) {
        U8(e, 0x14D) = 0x30;
    } else {
        U8(e, 0x14D) = 0x60;
    }
}

/* Places a unit at `pos` (its points of reference with it), facing `yaw` with angles +0x50. */
static inline void unit_place(Unit *e, const u32 *pos, const u32 *angles)
{
    int i;

    for (i = 0; i < 4; i++) {
        U32(e, 0x40 + i * 4) = pos[i];
        U32(e, 0x80 + i * 4) = 0;
    }
    for (i = 0; i < 4; i++)
        F32(e, 0x90 + i * 4) = F32(e, 0x40 + i * 4) + F32(e, 0x80 + i * 4);
    for (i = 0; i < 4; i++) {
        U32(e, 0xB0 + i * 4) = U32(e, 0x90 + i * 4);
        U32(e, 0xA0 + i * 4) = U32(e, 0x40 + i * 4);
    }
    F32(e, 0x238) = ((float *)angles)[1];
    U8(e, 0x27C) &= ~1;
    for (i = 0; i < 4; i++)
        U32(e, 0x50 + i * 4) = angles[i];
}

/* A bodyguard's timer (+0x160) running down by `dt`, its alpha from it (at most `max`); it is
 * dismissed at 0. */
static inline void bodyguard_timer(Unit *e, float dt, float max, u8 full)
{
    float t;

    F32(e, 0x164) = F32(e, 0x164) + dt;
    t = F32(e, 0x160) - dt;
    F32(e, 0x160) = t;
    if (t < max)
        U8(e, 0x14D) = (u8)(u32)t;
    else
        U8(e, 0x14D) = full;
    if (F32(e, 0x160) < 0.0f)
        func_00166160(e);
}

/* 0x00158FB0, 0x600 bytes. A bodyguard each frame, by kind: 3 copies its player's action 50
 * units behind it; 2 fades out; 1 waits; 0 follows its player's path (the position its player
 * had (slot + 1) x 9 frames before). */
void func_00158FB0(float dt, Unit *e)
{
    u8 kind = U8(e, 0x15A);
    Unit *m = g_00574DE0[U8(e, 0x15B)];

    if (kind == 3) {
        float p[4];
        int i;

        if (S16(ACT(e), 0) != S16(ACT(m), 0)) {
            for (i = 0; i < 4; i++)
                U32(e, 0x1D0 + i * 4) = U32(m, 0x1D0 + i * 4);
            func_00156AF0(e, U16(ACT(m), 0));
        }
        F32(e, 0x21C) = F32(m, 0x21C);
        func_00161520(p, m);
        for (i = 0; i < 4; i++)
            p[i] = p[i] * -50.0f;
        p[1] = p[1] - 20.0f;
        for (i = 0; i < 4; i++)
            p[i] = p[i] + F32(m, 0x90 + i * 4);
        unit_place(e, (u32 *)p, (u32 *)(m + 0x50));
        if (90.0f < F32(e, 0x160) && (U32(ACT(m), 0x18) & 0x440))
            F32(e, 0x160) = 90.0f;
        bodyguard_timer(e, dt, 90.0f, 0x5A);
    } else if (kind == 2) {
        float t;

        F32(e, 0x164) = F32(e, 0x164) + 1.0f;
        t = F32(e, 0x160) - 1.0f;
        F32(e, 0x160) = t;
        if (t < 32.0f) {
            u8 a = (u8)(u32)(t * 4.0f);

            U8(e, 0x14D) = a;
            U8(e, 0x14D) = 0x30 < a ? 0x30 : a;
        }
        if (F32(e, 0x160) < 0.0f)
            func_00166160(e);
    } else if (kind == 1) {
        bodyguard_timer(e, dt, 96.0f, 0x60);
    } else if (kind == 0) {
        u8 *r = func_0016C980(U8(e, 0x15B), (U8(e, 0x17C) + 1) * 9);
        float x = F32(r, 0), y = F32(r, 4), z = F32(r, 8);

        if (1.0f < sqrtf(x * x + y * y + z * z)) {
            int i;

            if (S16(ACT(e), 0) != S16(r, 0x2C)) {
                for (i = 0; i < 4; i++)
                    U32(e, 0x1D0 + i * 4) = U32(r, 0x30 + i * 4);
                func_00156AF0(e, U16(r, 0x2C));
            }
            F32(e, 0x21C) = F32(r, 0x20);
            U8(e, 0x27C) = (U8(e, 0x27C) & ~2) | ((S16(r, 0x2E) != 0) << 1);
            unit_place(e, (u32 *)r, (u32 *)(r + 0x10));
        }
        bodyguard_timer(e, dt, 96.0f, 0x60);
    }
}

/* 0x001595B0, 0x94 bytes. Gives musou (?) for a hit: 30 to 60 by the player's level. */
void func_001595B0(Unit *u)
{
    if ((U8(u, 0x19C) & 2) == 0) {
        u8 b = func_002F41E0(g_00669DE8[PLAYER(u)][0]);

        func_0016C180(((float)b / 49.0f + 1.0f) * 30.0f, u);
    }
}

/* 0x00159650, 0x94 bytes. Collects the hit's flags (+0x12) while within its active frames (+5 to
 * +6) into +0x148, and always into +0x14A (low six bits cleared). */
void func_00159650(float t, Unit *u, u8 *hit)
{
    if ((U8(u, 0x19C) & 0x20) == 0) {
        if ((hit[5] != 0 || hit[6] != 0) && (float)hit[5] <= t && t <= (float)hit[6])
            U16(u, 0x148) |= U16(hit, 0x12);
        U16(u, 0x14A) |= U16(hit, 0x12);
        U16(u, 0x14A) &= 0xFFC0;
    }
}

extern u32 g_00406470[12][4];            /* the body nodes the hits come from (+0) */

void func_001AE1D0(u32 e, u8 *eff);
float (*func_0014F810(u8 *actor, u32 node))[4];

/* Emits attack effect `eff` from node matrix `m` (its offset along the axis the effect names,
 * +0x30 / +0x44), facing along that axis (or the unit's facing), with its spreads, storing and
 * musou gain. */
static inline void attack_effect(Unit *u, u8 *hit, u8 *eff, float (*m)[4])
{
    float off[4], pos[4], dir[4];
    u32 f = U32(eff, 0x30), e;
    int i;

    off[0] = ((float *)0x70000030)[0];
    off[1] = ((float *)0x70000030)[1];
    off[2] = ((float *)0x70000030)[2];
    off[3] = 1.0f;
    if (f & 0x200000)
        off[0] = (float)eff[0x44];
    else if (f & 0x800000)
        off[1] = (float)eff[0x44];
    else if (f & 0x1000000)
        off[2] = (float)eff[0x44];
    else
        off[0] = (float)eff[0x44];
    mat_vec(pos, m, off);
    for (i = 0; i < 4; i++)
        pos[i] = pos[i] / pos[3];
    if (f & 0x200000) {
        float v[4] = { 1.0f, off[1], off[2], 0.0f };

        mat_vec(dir, m, v);
    } else if (f & 0x800000) {
        float v[4] = { off[0], 1.0f, off[2], 0.0f };

        mat_vec(dir, m, v);
    } else if (f & 0x1000000) {
        float v[4] = { off[0], off[1], 1.0f, 0.0f };

        mat_vec(dir, m, v);
    } else {
        for (i = 0; i < 4; i++)
            dir[i] = F32(u, 0x70 + i * 4);
    }
    e = func_00177ED0();
    func_001AC980(e, eff, (u8 *)pos, dir, u);
    if ((s8)U8(u, 0x19C) >= 0)
        func_001AE1D0(e, eff);
    if (U32(eff, 0x30) & 0x20000)
        func_00158420(u, eff, (u8 *)pos, dir);
    else if (U32(eff, 0x30) & 0x800)
        func_00158540(u, eff, (u8 *)pos, dir);
    if ((U32(eff, 0x30) & 8) == 0) {
        if (U32(hit, 0x28) & 0x40000) {
            if (S16(u, 0x258) != -1) {
                func_001AE090(g_005ADD80[S16(u, 0x258)]);
                S16(u, 0x258) = -1;
            }
            S16(u, 0x258) = S16(e, 0x94);
            U32(e, 0x84) = 0;
            U8(e, 0x8C) = (U8(e, 0x8C) & ~2) | 2;
        }
    } else {
        func_001580D0(u, S16(e, 0x94), hit);
    }
    if (PLAYER(u) < 2 && (U32(eff, 0x30) & 0x2000))
        func_001595B0(u);
}

/* The attack effects of hit `hit` at frame `t` (+`dt`): once at its frame +0x16 (or each frame
 * of +0x16 to +0x17), from each body node (bits 0-11 of +0x12) and weapon (bits 12-15) it names,
 * or the stored projectiles. Without a frame (or in mode 4), as `force` says. */
static inline void attack_effects(Unit *u, u8 *hit, float t, float dt, int force)
{
    int fire = force;

    func_00159650(t, u, hit);
    if (g_00669DB8 != 4 && (hit[0x16] != 0xFF || hit[0x17] != 0xFF)) {
        float a = (float)hit[0x16];

        if (hit[0x16] == hit[0x17])
            fire = !(a < t || t + dt <= a);
        else
            fire = (int)(t - dt) != (int)t && a <= t && !((float)hit[0x17] < t);
    }
    if (fire) {
        u8 *eff = g_0045D2FC + 0x10 + hit[0x18] * 0x48;

        if ((U32(hit, 0x2C) & 0x100) == 0) {
            u32 k;

            for (k = 0; (int)k < 0x10; k++) {
                if ((U16(hit, 0x12) & (1 << k)) == 0)
                    continue;
                if ((int)k < 0xC) {
                    attack_effect(u, hit, eff,
                                  (float (*)[4])func_0016A170(u, g_00406470[k][0]));
                } else {
                    int s;

                    for (s = 0; s < 4; s++) {
                        u8 *slot = u + 0x290 + s * 0x70;

                        if ((U8(slot, 0x4C) & 1) && (U8(slot, 0x4C) & 4))
                            attack_effect(u, hit, eff,
                                          func_0014F810(PTR(slot, 0x44), (k - 0xC) & 0xFF));
                    }
                }
            }
        } else {
            func_00158270(u, eff, hit);
        }
    }
}

/* 0x001596F0, 0x14A4 bytes. The attack effects of the unit's actions this frame (the main action
 * and the extra one at +0x250), unless the model is in a transition; the two shots of actions
 * 0x4E / 0x4F at frame 1; the held effect dropped when the hit ends; stored projectiles more
 * than 10000 units away dropped. */
void func_001596F0(float dt, Unit *u, int unused, int force)
{
    u8 *hit = PTR(ACT(u), 0x14);
    u8 *a = PTR(u, 0x11C);
    short *slot = &S16(u, 0x260);
    int any = 0, i, j;

    U16(u, 0x148) = 0;
    U16(u, 0x14A) = 0;
    if (a != 0 && U32(a, 0x204) > 1 && !(F32(a, 0x214) > 0.0f)) {
        if (hit != 0)
            attack_effects(u, hit, F32(u, 0x21C), dt, force);
        if (PTR(u, 0x250) != 0)
            attack_effects(u, PTR(PTR(u, 0x250), 0x14), F32(u, 0x254), dt, force);
    }
    if (PTR(u, 0x11C) == 0 || F32(PTR(u, 0x11C), 0x214) <= 0.0f) {
        float t = F32(u, 0x21C);

        if (S16(ACT(u), 0) == 0x4E) {
            if (!(1.0f < t || t + dt <= 1.0f))
                func_00158660(u, 0);
        } else if (S16(ACT(u), 0) == 0x4F) {
            if (!(1.0f < t || t + dt <= 1.0f))
                func_00158660(u, 7);
        }
    }
    if (S16(u, 0x258) != -1 && (hit == 0 || (U32(hit, 0x28) & 0x40000) == 0)) {
        func_001AE090(g_005ADD80[S16(u, 0x258)]);
        S16(u, 0x258) = -1;
    }
    for (i = 0; i < 6; i++) {
        if (slot[i] != -1) {
            float x = F32(g_005ADD80[slot[i]], 0x30) - F32(u, 0x40);
            float z = F32(g_005ADD80[slot[i]], 0x38) - F32(u, 0x48);

            if (1e+08f < x * x + z * z) {
                func_001AE090(g_005ADD80[slot[i]]);
                any = 1;
                slot[i] = -1;
            }
        }
    }
    if (any) {
        for (i = 0, j = 0; i < 6; i++) {
            if (slot[i] != -1) {
                if (j == i) {
                    j++;
                } else {
                    slot[j++] = slot[i];
                    slot[i] = -1;
                }
            }
        }
    }
}

extern u32 g_00669FA4;                   /* the battle's phase? */
extern int g_0045D37C;                   /* (small data) */
extern u8 g_0074B870[][0x70];            /* per player: the hints shown (+0) */
extern s8 g_00406430[0x1A][2];           /* per weapon kind: two frames of action 0xB4 */

int func_00240C00(Unit *u);
void func_001CF430(float dt, Unit *u, int a);
void func_001D0C20(Unit *u, int a);
int func_00190610(u8 *pos, int a);
void func_00253D20(Unit *u);
void func_00240790(u32 player, u32 flags);
void func_002409B0(Unit *u);
void func_00240A60(Unit *u, u32 flags);
void func_002444A0(Unit *u, u8 *hit);
void func_00244490(Unit *u, u8 *hit);
void func_00245510(Unit *u, u8 *hit);
void func_002453C0(Unit *u, u8 *hit);
void func_002454E0(Unit *u, u8 *hit);
void func_001D1B50(Unit *u);
void func_00244D20(Unit *u, u8 *hit);
void func_00244570(Unit *u, u8 *hit);
void func_00244540(Unit *u);
void func_002445A0(Unit *u, u8 *hit);
void func_00243DF0(Unit *u, u8 *hit);
void func_001D1610(Unit *u);
void func_001CF3E0(Unit *u, int a);

/* Whether frame `x` falls within this frame (t to t + dt). */
#define AT_FRAME(x, t, dt) (!((float)(x) < (t) || (t) + (dt) <= (float)(x)))

/* Calls 1, 2 or 3 bodyguards of `kind` (by the hit's +0x2C bits 0x10 / 0x20). */
static inline void call_bodyguards(Unit *u, u8 *hit, u8 kind)
{
    func_00158CD0(u, 4);
    if ((U32(hit, 0x2C) & 0x20) == 0) {
        if ((U32(hit, 0x2C) & 0x10) == 0) {
            func_001589B0(u, kind, 0);
            U8(u, 0x196) = 1;
        } else {
            func_001589B0(u, kind, 0);
            func_001589B0(u, kind, 1);
            U8(u, 0x196) = 2;
        }
    } else {
        func_001589B0(u, kind, 0);
        func_001589B0(u, kind, 1);
        func_001589B0(u, kind, 2);
        U8(u, 0x196) = 3;
    }
}

/* 0x0015ABD0, 0x12D0 bytes. A unit's action each frame (`dt`): a queued action (+0x278); the
 * mounted states (+0x155); struggles; the locked target's turning; the model's foot / ground
 * contacts; the hints shown to the players by what the hit allows; the hit's special moves at
 * its first frame (bodyguards, musou...); sounds at fixed frames. 0 while the hit stop (+0x244)
 * runs. */
int func_0015ABD0(float dt, Unit *u)
{
    u8 *act = ACT(u), *d = DESC(u), *hit = PTR(act, 0x14);
    u32 flags = 0, p;
    float t;
    u16 id;
    u8 kind;
    char c;

    if (g_00669DB8 == 4 || g_00669DB8 == 2)
        return 1;
    if (S16(u, 0x278) != -1) {
        int i;

        F32(u, 0x224) = -1.0f;
        U8(u, 0x27C) = (U8(u, 0x27C) & ~2) | 2;
        F32(u, 0x228) = 0.0f;
        for (i = 0; i < 4; i++)
            F32(u, 0x200 + i * 4) = VEC_ZERO[i];
        func_00156AF0(u, U16(u, 0x278));
        U8(u, 0x27C) = (U8(u, 0x27C) & 0x7F) | 0x80;
        if (PTR(u, 0x280) != 0) {
            Unit *v = PTR(u, 0x280);

            func_0016BD30(u);
            func_00150A10(v);
        }
    }
    c = U8(u, 0x155);
    if (c == 2)
        goto end;
    if (c == 1) {
        if (U8(u, 0x181) == 0 && PTR(u, 0x11C) != 0 && (s8)U8(u, 0x19C) >= 0) {
            id = U16(act, 0);
            if (id == 0xD || id == 0xC || id == 0xB || id == 10)
                func_001CF430(dt, u, 1);
            else if (id == 0x1C || id == 0x9A || id == 0x99 || id == 0x14 || id == 0x13 || id == 7
                     || id == 6 || id == 5 || id == 4 || id == 3)
                func_001CF430(dt, u, 0);
        }
        goto end;
    }
    if (c != 0)
        goto end;
    if (func_00240C00(u) != 0)
        F32(u, 0x244) = 0.0f;
    if (U8(u, 0x27C) & 4) {
        int a, b;

        if (PTR(u, 0x280) != 0 && func_001578D0(u, &a, &b) != 0)
            func_00157B60(u, a, b);
        F32(u, 0x244) = 0.0f;
    }
    if (PLAYER(u) < 2) {
        float speed, turn;

        if ((U8(u, 0x27C) & 0x10) && (turn = func_00157EE0(u, &speed), PTR(u, 0x270) != 0)) {
            int ok;

            if (hit == 0) {
                ok = 1;
            } else {
                short s = S16(hit, 0x20);

                ok = s >= 0 && (short)(int)F32(u, 0x21C) <= s;
            }
            if (ok) {
                F32(u, 0x238) = wrap_angle(F32(u, 0x54) + turn);
                F32(u, 0x230) = speed;
                U8(u, 0x27C) &= ~1;
            }
        }
    } else {
        PTR(u, 0x270) = 0;
        U8(u, 0x27C) &= ~0x10;
    }
    if (U8(u, 0x181) == 0 && PTR(u, 0x11C) != 0 && (s8)U8(u, 0x19C) >= 0) {
        if (U16(act, 0) != 5) {
            u32 f = U32(act, 0x18);

            if ((f & 0x100) == 0) {
                if ((f & 0x10000000) && (f & 0x80))
                    func_001CF430(dt, u, 2);
            } else {
                func_001CF430(dt, u, 1);
            }
        } else {
            func_001CF430(dt, u, 0);
        }
    }
    id = U16(act, 0);
    if ((u16)(id - 0x6D) < 2 && (int)F32(u, 0x23C) > 0x19)
        func_001D0C20(u, 1);
    else if (g_0076E700[PLAYER(u)] & 1)
        func_001D0C20(u, 0);
    t = F32(u, 0x21C);
    if (PLAYER(u) < 2 && PTR(u, 0x11C) != 0) {
        if ((U32(act, 0x18) & 1) && g_00669FA4 - 2 < 2 && func_00190610(u + 0x40, 0x100) == 0)
            func_00253D20(u);
    } else if (U8(u, 0x181) == 0 && PTR(u, 0x11C) != 0 && g_0045D37C == 0 && (U32(act, 0x18) & 1)
               && g_00669FA4 - 2 < 2 && func_00190610(u + 0x40, 0x100) == 0) {
        func_00253D20(u);
    }
    kind = U8(d, 0x1C);
    if (hit == 0) {
        if (PLAYER(u) < 2) {
            if (0.0001f < F32(u, 0x168)) {
                if (kind == 2)
                    flags = 0x20;
                if (kind == 0x15)
                    flags |= 0x100;
            }
            if (U8(u, 0x19E) & 2)
                flags |= 0x400;
            else if (S16(u, 0x192) != 0)
                flags |= 0x1000;
            if (U8(u, 0x19E) & 1)
                flags |= 0x4000;
            else if (U8(u, 0x19E) & 8)
                flags |= 0x40000;
        }
    } else {
        if ((float)hit[5] <= t || (float)hit[0x16] <= t) {
            if (U16(hit, 0x1C) & 0x100) {
                if (kind == 2) {
                    if (t < (float)hit[6])
                        flags = 0x10000;
                } else if (kind != 8 && kind != 0xF) {
                    flags = 0x20000;
                }
            }
        } else {
            u32 f28 = U32(hit, 0x28);

            flags = (f28 & 1) != 0;
            if (U32(hit, 0x2C) & 0x8000000)
                flags |= 2;
            if (f28 & 0x4000000)
                flags |= 8;
            if (f28 & 0x8000000)
                flags |= 4;
            if (U16(hit, 0x1C) & 0x40)
                flags |= 0x10;
            if (U8(u, 0x17F) > 1 && U8(u, 0x17E) != 0)
                flags |= 0x100000 << (U8(u, 0x17E) - 1);
            if ((U16(hit, 0x1C) & 0x20) && AT_FRAME(1, t, dt) && PLAYER(u) >= 2)
                func_00253300(0xC, u);
        }
        kind = U8(d, 0x1C);
        if (kind == 8 && (U16(hit, 0x1C) & 0x100) == 0 && t < (float)hit[6])
            flags |= 0x80;
        if (PLAYER(u) < 2) {
            if ((U32(hit, 0x2C) & 0x80000) == 0) {
                if (0.0001f < F32(u, 0x168)) {
                    if (kind == 2)
                        flags |= 0x20;
                    if (kind == 0x15)
                        flags |= 0x100;
                }
            } else if ((float)hit[5] <= t) {
                if (kind == 2)
                    flags |= 0x60;
                if (kind == 0x15)
                    flags |= 0x300;
            }
            if ((U32(hit, 0x28) & 0x20000) == 0) {
                if (U8(u, 0x19E) & 2)
                    flags |= 0x400;
                else if ((U16(hit, 0x1C) & 0x80) == 0) {
                    if (S16(u, 0x192) != 0)
                        flags |= 0x1000;
                } else if ((float)hit[5] <= t) {
                    flags |= 0x3000;
                }
            } else if ((float)hit[5] <= t) {
                flags |= 0xC00;
            }
            if ((U32(hit, 0x2C) & 0x80) == 0) {
                if (U8(u, 0x19E) & 1)
                    flags |= 0x4000;
                else if ((U16(hit, 0x1C) & 0x10) == 0) {
                    if (U8(u, 0x19E) & 8)
                        flags |= 0x40000;
                } else if ((float)hit[5] <= t) {
                    flags |= 0xC0000;
                }
            } else if ((float)hit[5] <= t) {
                flags |= 0xC000;
            }
            if (kind == 0xF && (U16(hit, 0x1C) & 0x100))
                flags &= 0xFE0FFFFF;
        }
    }
    p = PLAYER(u);
    if ((flags != 0 || *(u32 *)g_0074B870[p] != 0) && (s8)U8(u, 0x19C) >= 0)
        func_00240790(p, flags);
    if (U8(d, 0x1C) == 0x15)
        func_002409B0(u);
    if (U8(u, 0x19E) & 0x20) {
        if (U8(u, 0x17E) != 0 && U8(u, 0x17F) != 0)
            flags |= 0x100000 << (U8(u, 0x17E) - 1);
        func_00240A60(u, flags);
    }
    if (PLAYER(u) < 2 && hit != 0 && AT_FRAME(hit[5], F32(u, 0x21C), dt)) {
        u32 f2C = U32(hit, 0x2C);
        u16 f1C = U16(hit, 0x1C);

        if (f2C & 0x400000)
            call_bodyguards(u, hit, 0);
        else if (f2C & 0x800000)
            call_bodyguards(u, hit, 1);
        else if (U32(hit, 0x28) & 0x10000000)
            func_001D1610(u);
        else if (f2C & 0x10000000) {
            func_001589B0(u, 3, 0);
            U8(u, 0x196) = 1;
        } else if ((f1C & 2) || (f2C & 1))
            func_00243DF0(u, hit);
        else if (f2C & 0x200)
            func_002445A0(u, hit);
        else if (f2C & 0x80)
            func_00244540(u);
        else if (U32(hit, 0x28) & 0x20000)
            func_00244570(u, hit);
        else if (f1C & 4)
            func_00244D20(u, hit);
        else if (f2C & 0x4000000)
            func_001D1B50(u);
        else if (f1C & 0x10)
            func_002454E0(u, hit);
        else if (f2C & 0x40)
            func_002453C0(u, hit);
        else if (f1C & 0x80)
            func_00245510(u, hit);
        else if (f1C & 0x1000)
            func_00244490(u, hit);
        else if (f1C & 0x2000)
            func_002444A0(u, hit);
    }
    if (hit != 0) {
        if (U32(hit, 0x28) & 0x200000) {
            if (AT_FRAME(hit[5], F32(u, 0x21C), dt)) {
                U8(u, 0x19D) = (U8(u, 0x19D) & ~8) | 8;
                g_70000D60 = 0;
                func_001C7F30(0x65, &F32(u, 0x40), 0, 0);
                func_00253300(0x17, u);
            }
        } else if (U32(hit, 0x28) & 0x400000) {
            if (AT_FRAME(hit[5], F32(u, 0x21C), dt))
                U8(u, 0x19D) &= ~8;
        }
    }
    if (PLAYER(u) < 2) {
        id = U16(act, 0);
        t = F32(u, 0x21C);
        if (id == 0xE || id == 0xF || id == 0xB1) {
            if (AT_FRAME(2, t, dt))
                func_001CF3E0(u, 0);
            else if (AT_FRAME(6, t, dt))
                func_001CF3E0(u, 1);
        } else if (id == 0x79) {
            if (AT_FRAME(20, t, dt))
                func_001CF3E0(u, 0);
            else if (AT_FRAME(23, t, dt))
                func_001CF3E0(u, 1);
        } else if (id == 0xB4) {
            u32 k = DESC(u) == 0 ? 0x6A : U8(DESC(u), 0x1C);

            if (k < 0x1A) {
                if (g_00406430[k][0] >= 0 && AT_FRAME(g_00406430[k][0], t, dt))
                    func_001CF3E0(u, 1);
                if (g_00406430[k][1] >= 0 && AT_FRAME(g_00406430[k][1], t, dt))
                    func_001CF3E0(u, 0);
            }
        }
    }
end:
    if (0.0001f < F32(u, 0x244)) {
        float v = F32(u, 0x244) - dt;

        F32(u, 0x244) = v;
        F32(u, 0x244) = v < 0.0f ? 0.0f : v;
        return 0;
    }
    return 1;
}

u16 func_00241250(Unit *u, int *queue, int late);
u16 func_00242C40(Unit *u, int *queue, int late);
u16 func_002434F0(Unit *u);
u16 func_00243C50(Unit *u);

/* The action the controls (or the AI) ask for, by the unit's state. */
static inline u16 unit_pick(Unit *u, int *queue, int late)
{
    if (S32(u, 0x118) < 0x3C) {
        if ((U32(ACT(u), 0x18) & 0x8000000) == 0)
            return func_00241250(u, queue, late);
        return func_00242C40(u, queue, late);
    }
    if (S32(u, 0x118) == 0x3C)
        return func_002434F0(u);
    return func_00243C50(u);
}

/* 0x0015BEA0, 0x3F8 bytes. Takes the next action from the controls: at once without a cancel
 * frame (+0x22 of the hit), else from that frame on (earlier ones queued at +0x218, played when
 * the hit allows: +0x28 bit 0x2000 and the unit's flag 8). */
void func_0015BEA0(float dt, Unit *u)
{
    u8 *hit = PTR(ACT(u), 0x14);
    short cancel;
    u8 *q;
    int queue;
    u16 next;

    if ((s8)U8(u, 0x19C) < 0 && U8(u, 0x15A) != 1)
        return;
    if (hit == 0 || (cancel = S16(hit, 0x22)) < 1) {
        next = unit_pick(u, &queue, 0);
        if (S16(ACT(u), 0) != (short)next)
            func_00156AF0(u, next);
        return;
    }
    if (U16(hit, 0x1C) & 1) {
        if ((short)(int)(F32(u, 0x21C) + dt) < cancel)
            return;
        next = unit_pick(u, &queue, 0);
        if (S16(ACT(u), 0) != (short)next)
            func_00156AF0(u, next);
        return;
    }
    if ((short)(int)(F32(u, 0x21C) + dt) < cancel) {
        next = unit_pick(u, &queue, 0);
        if (U16(ACT(u), 0) != next) {
            if (queue != 0)
                func_00156AF0(u, next);
            else
                PTR(u, 0x218) = PTR(DESC(u), 8) + next * 0x20;
        }
    } else {
        next = unit_pick(u, &queue, 1);
        if (U16(ACT(u), 0) != next) {
            if (queue != 0)
                func_00156AF0(u, next);
            else
                PTR(u, 0x218) = PTR(DESC(u), 8) + next * 0x20;
        }
    }
    q = PTR(u, 0x218);
    if (q != 0) {
        if (PTR(q, 0x14) == 0 || (U32(PTR(q, 0x14), 0x28) & 0x2000) == 0) {
            func_00156AF0(u, U16(q, 0));
            PTR(u, 0x218) = 0;
        } else {
            if (U8(u, 0x27C) & 8)
                func_00156AF0(u, U16(q, 0));
            PTR(u, 0x218) = 0;
        }
    }
}

extern float g_00406380[0x3E];           /* speed multipliers by weapon kind / item */

float func_003B00A0(void);
short func_001BE9B0(u8 kind);

/* The flat length (squared) of +0x1D0, the direction held. */
#define HELD_LEN2(u) (F32(u, 0x1D0) * F32(u, 0x1D0) + F32(u, 0x1D8) * F32(u, 0x1D8))

/* Whether the hit still allows turning (until its frame +0x20; never when negative). */
static inline int can_turn(Unit *u)
{
    u8 *hit = PTR(ACT(u), 0x14);
    short s;

    if (hit == 0)
        return 1;
    s = S16(hit, 0x20);
    return s >= 0 && (short)(int)F32(u, 0x21C) <= s;
}

/* Aims at the direction held (at `rate` a frame), when it is allowed. */
static inline void aim_held(Unit *u, float rate)
{
    if (can_turn(u) && 0.0001f < HELD_LEN2(u)) {
        F32(u, 0x238) = vu0_angle(F32(u, 0x1D0), F32(u, 0x1D8));
        F32(u, 0x230) = rate;
    } else {
        F32(u, 0x238) = F32(u, 0x54);
        F32(u, 0x230) = 0.0f;
    }
    U8(u, 0x27C) &= ~1;
}

/* Turns towards the aim (+0x238) at its rate (+0x230) for `dt` (at once when flag 1 is set),
 * turning the motion's root offset with the unit. */
static inline void turn_to_aim(Unit *u, float dt)
{
    float d = wrap_angle(F32(u, 0x238) - F32(u, 0x54)), a;

    if (fabsf(d) < 0.008726646f) {
        F32(u, 0x54) = F32(u, 0x238);
        return;
    }
    if (U8(u, 0x27C) & 1) {
        U8(u, 0x27C) &= ~1;
        a = d;
    } else {
        float r = F32(u, 0x230), s = -r;

        if (s <= d) {
            if (r < d) {
                s = r;
            } else {
                F32(u, 0x230) = 0.0f;
                s = d;
            }
        }
        a = s * dt;
        if ((U32(ACT(u), 0x18) & 0x800000) == 0) {
            float off[4], m[4][4], r2[4];
            int i;

            off[0] = F32(u, 0x80);
            off[1] = 0.0f;
            off[2] = F32(u, 0x88);
            off[3] = F32(u, 0x8C);
            scratch_unit(m);
            vu0_rot_y(m, a);
            mat_vec(r2, m, off);
            for (i = 0; i < 4; i++)
                F32(u, 0x40 + i * 4) += off[i] - r2[i];
        }
    }
    a = F32(u, 0x54) + a;
    if (PI < a)
        a -= TWO_PI;
    else if (a <= -PI)
        a += TWO_PI;
    F32(u, 0x54) = a;
}

/* The running speed: the officer's (+0x90) + 1.5 in its special state, else func_003B00A0. */
static inline float run_speed(Unit *u)
{
    u8 *hit = PTR(ACT(u), 0x14);

    if ((U8(u, 0x19C) & 2) && (U32(ACT(u), 0x18) & 0x8000000) == 0
        && (hit == 0 || (U32(hit, 0x28) & 0x1C) == 0))
        return F32(OFFICER(u), 0x90) + 1.5f;
    return func_003B00A0();
}

/* The speed index of an item (0x633-0x665 and 0x433-0x485, 0x4A7, 0x4A9). */
static inline u32 item_speed_index(short id)
{
    if (id >= 0x633 && id <= 0x665 && (id & 1))
        return (id - 0x633) / 2;
    if (id >= 0x433 && id <= 0x485 && (id & 1))
        return (id - 0x433) / 2 + 0x3E;
    if (id == 0x4A7)
        return 0x68;
    if (id == 0x4A9)
        return 0x69;
    return 0;
}

/* Moves at `speed` for `dt` along `dir`. */
static inline void move_along(Unit *u, float speed, float dt, float *dir)
{
    int i;

    F32(u, 0x228) = speed * dt;
    for (i = 0; i < 4; i++)
        F32(u, 0x40 + i * 4) += dir[i] * (speed * dt);
}

/* 0x0015C2A0, 0x1B8C bytes. A unit's movement each frame: aiming at the direction held (10 or
 * 5 degrees a frame on foot, the officer's +0x8E on a mount), turning towards the aim, the
 * facing vector, the run (by the weapon's or item's multiplier, along the held direction or the
 * facing), the push of the mount, jumps, gravity and pushes, being held, and the side placement
 * of actions 0x55 / 0x56. */
void func_0015C2A0(float dt, Unit *u)
{
    u8 *act = ACT(u), *hit = PTR(act, 0x14);
    short aid = S16(act, 0);
    u32 f;
    u8 c;

    if ((U32(act, 0x18) & 0x4000000) == 0) {
        float rate;

        if (hit == 0 || (U32(hit, 0x28) & 0x100)) {
            int follow;

            f = U32(ACT(u), 0x18);
            if ((f & 0x10000000) == 0) {
                u8 *h = PTR(ACT(u), 0x14);

                if ((h == 0 ? 0 : U32(h, 0x28) & 0x100) == 0)
                    follow = (f & 0x80) || (S32(u, 0x118) == 0x3C
                                            && (aid == 3 || aid == 4 || aid == 5 || aid == 6));
                else
                    follow = 0;
            } else {
                follow = 0;
            }
            if (follow) {
                rate = S32(u, 0x118) < 0x3C
                           ? 0.17453294f
                           : (float)S16(OFFICER(u), 0x8E) * PI / 180.0f;
                aim_held(u, rate);
            }
        } else if (0.0001f < HELD_LEN2(u)) {
            rate = S32(u, 0x118) < 0x3C ? 0.08726647f
                                        : (float)S16(OFFICER(u), 0x8E) * PI / 180.0f;
            aim_held(u, rate);
        } else if (PTR(u, 0x270) == 0) {
            F32(u, 0x238) = F32(u, 0x54);
            F32(u, 0x230) = 0.0f;
            U8(u, 0x27C) &= ~1;
        }
    }
    if ((U8(u, 0x27C) & 0x40) == 0) {
        if (!(aid == 1 || aid == 2 || aid == 3 || aid == 4) || U8(u, 0x155) != 0) {
            if (PTR(u, 0x288) == 0)
                turn_to_aim(u, dt);
        } else if (0.0001f < HELD_LEN2(u)) {
            F32(u, 0x238) = vu0_angle(F32(u, 0x1D0), F32(u, 0x1D8));
            F32(u, 0x230) = 0.05235988f;
            U8(u, 0x27C) &= ~1;
            if (PTR(u, 0x288) == 0)
                turn_to_aim(u, dt);
        }
    }
    {
        float y = F32(u, 0x54), s, co;

        if (PI < y)
            y -= TWO_PI;
        else if (y <= -PI)
            y += TWO_PI;
        F32(u, 0x54) = y;
        vu0_sincos(y, &s, &co);
        F32(u, 0x70) = s;
        F32(u, 0x78) = co;
        F32(u, 0x74) = 0.0f;
    }
    f = U32(act, 0x18);
    if ((f & 0x20) == 0 || (f & 0x800))
        F32(u, 0x228) = 0.0f;
    else
        func_00155980(dt, u);
    if (S32(u, 0x118) == 0x3C && PTR(u, 0x28C) != 0 && (U8(PTR(u, 0x28C), 0x19C) & 2)
        && (f & 0x20000000) && (U32(PTR(u, 0x28C), 0x13C) & 0x20000)) {
        func_00155310(dt, 20.0f, u);
        goto tail;
    }
    if (U32(act, 0x1C) & 2) {
        float s;

        if (g_00669DB8 == 4) {
            s = 14.0f;
        } else if ((U8(u, 0xE8) & 3) >> 1 == 1) {
            float x = F32(u, 0xF0), z = F32(u, 0xF8);

            s = x * x + z * z < 100.0f ? F32(OFFICER(u), 0x94) * 0.75f
                                       : F32(OFFICER(u), 0x94) * 0.25f;
        } else {
            s = F32(OFFICER(u), 0x94);
        }
        func_00155310(dt, s, u);
        goto tail;
    }
    if ((f & 0x100) == 0) {
        if (f & 0x80) {
            if (hit == 0) {
                float spd = run_speed(u), cosa;
                int strafe;

                if (S32(u, 0x118) < 0x3C) {
                    if ((f & 0x10000000) == 0) {
                        strafe = 1;
                    } else {
                        u8 k = U8(DESC(u), 0x1C);
                        float mult;

                        if (k < 0x1A || PLAYER(u) > 1) {
                            mult = k < 0x1A ? g_00406380[k] : 1.0f;
                        } else if (func_001BE9B0(k) != -1) {
                            u32 idx = item_speed_index(func_001BE9B0(k));

                            mult = idx < 0x3E ? g_00406380[idx] : g_00406380[0];
                        } else {
                            mult = 1.0f;
                        }
                        spd = spd * mult;
                        strafe = 0;
                    }
                    cosa = F32(u, 0x1D0) * F32(u, 0x70) + F32(u, 0x1D4) * F32(u, 0x74)
                           + F32(u, 0x1D8) * F32(u, 0x78) + F32(u, 0x1DC) * F32(u, 0x7C);
                    if (!strafe || 0.9999f <= fabsf(cosa))
                        move_along(u, spd, dt, &F32(u, 0x1D0));
                    else
                        move_along(u, spd, dt, &F32(u, 0x70));
                } else {
                    cosa = F32(u, 0x1D0) * F32(u, 0x70) + F32(u, 0x1D4) * F32(u, 0x74)
                           + F32(u, 0x1D8) * F32(u, 0x78) + F32(u, 0x1DC) * F32(u, 0x7C);
                    if (fabsf(cosa) < 0.9999f)
                        move_along(u, spd, dt, &F32(u, 0x70));
                    else
                        move_along(u, spd, dt, &F32(u, 0x1D0));
                }
            } else if (g_00669DB8 != 4) {
                func_00155310(dt, run_speed(u) + 3.0f, u);
            }
        }
    } else {
        float k;

        if (S32(u, 0x118) == 0x3C) {
            k = (PTR(u, 0x28C) == 0 || PLAYER(PTR(u, 0x28C)) > 1) ? 0.25f : 0.5f;
        } else {
            u8 kk = U8(DESC(u), 0x1C);

            k = (kk < 0x1A || (0x3D < kk && kk < 0x68) || kk == 'h' || kk == 'i') ? 0.4f : 0.2f;
        }
        k = k * run_speed(u) * dt;
        F32(u, 0x228) = k;
        {
            int i;

            for (i = 0; i < 4; i++)
                F32(u, 0x40 + i * 4) += F32(u, 0x1D0 + i * 4) * k;
        }
    }
tail:
    c = U8(u, 0x27C);
    if (c & 2)
        func_00155360(dt, F32(act, 0x10), u);
    if ((U8(u, 0x19D) & 2) || ((U32(act, 0x18) & 0x800) && (U32(act, 0x18) & 0x40) == 0))
        func_00155A80(dt, u);
    if (S16(ACT(u), 0) == 0x62)
        func_00155B20(u);
    if ((S16(ACT(u), 0) == 0x55 || S16(ACT(u), 0) == 0x56) && PTR(u, 0x288) != 0)
        func_00150FD0(u, PTR(u, 0x288), S16(ACT(u), 0));
}

extern int g_0045CC68[2];                /* (small data) the two extra motion slots: 0, 1 */

/* The last frame of action `act`: its hit's +6, or its motion's length - 1. */
static inline int act_end(Unit *u, u8 *act)
{
    u8 *hit = PTR(act, 0x14);
    u8 *d = DESC(u), *a, *r;

    if (hit != 0 && (U32(hit, 0x28) & 0x800000))
        return hit[6];
    a = PTR(d, 8) + U16(act, 0) * 0x20;
    if ((U32(a, 0x1C) & 0x40000000) == 0) {
        if ((U32(a, 0x1C) & 0x80000000) == 0)
            r = *(u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)]) + U16(a, 2) * 0x20);
        else
            r = *(u8 **)(*(u8 **)(g_005B5078[U8(d, 0x1C)] + 0x50) + U16(a, 2) * 0x20);
    } else {
        r = *(u8 **)(g_005BA688 + U16(a, 2) * 0x20);
    }
    return S32(r, 8) - 1;
}

/* Plays the queued action (+0x218) when the hit allows it; whether one was started. */
static inline int play_queued(Unit *u)
{
    u8 *q = PTR(u, 0x218);
    int r;

    if (q == 0)
        return 0;
    if (PTR(q, 0x14) == 0 || (U32(PTR(q, 0x14), 0x28) & 0x2000) == 0) {
        func_00156AF0(u, U16(q, 0));
        PTR(u, 0x218) = 0;
        return 1;
    }
    r = (U8(u, 0x27C) & 8) != 0;
    if (r)
        func_00156AF0(u, U16(q, 0));
    PTR(u, 0x218) = 0;
    return r;
}

/* Loops the frame back past `end` (counting the loops at +0x220). */
static inline void loop_frame(Unit *u, int end, float dt)
{
    if ((float)end < F32(u, 0x21C)) {
        if ((float)end < dt)
            F32(u, 0x21C) = 0.0f;
        else
            F32(u, 0x21C) = F32(u, 0x21C) - (float)(end + 1);
        S32(u, 0x220) += 1;
    }
}

/* 0x0015DE30, 0xA54 bytes. Advances the animation by `dt` (times the speed +0x234): the
 * transition first; then the frame, and at the end the next action (+4: a random idle among
 * three when mounted, the queued action, or a loop; actions with flag 0x40 loop four times); the
 * extra motion slots; the extra action (+0x250) and its chain; a rider's frame following its
 * mount (action 0x58). */
void func_0015DE30(float dt, Unit *u)
{
    u8 *act = ACT(u);
    float *tr = PTR(u, 0x11C) == 0 ? 0 : &F32(PTR(u, 0x11C), 0x210);
    int blending = tr != 0 && tr[1] > 0.0f;
    int done = 0;

    dt = dt * F32(u, 0x234);
    if (blending) {
        float v = tr[0];

        tr[0] = v - dt;
        if (v - dt < 0.0001f) {
            tr[0] = 0.0f;
            tr[1] = 0.0f;
            U8(u, 0x27C) &= ~0x20;
        }
        if (S16(ACT(u), 0xA) != -1 && (U8(u, 0x2DC) & 4)) {
            u8 *b = PTR(u, 0x2D4);

            F32(b, 0x210) = F32(b, 0x210) - dt;
            if (F32(b, 0x210) < 0.0001f) {
                F32(b, 0x210) = 0.0f;
                F32(b, 0x214) = 0.0f;
            }
        }
        if (S16(ACT(u), 8) != -1 && (U8(u, 0x34C) & 4)) {
            u8 *b = PTR(u, 0x344);

            F32(b, 0x210) = F32(b, 0x210) - dt;
            if (F32(b, 0x210) < 0.0001f) {
                F32(b, 0x210) = 0.0f;
                F32(b, 0x214) = 0.0f;
            }
        }
    }
    if (!blending || (U8(u, 0x27C) & 0x20)) {
        int end = act_end(u, ACT(u));

        F32(u, 0x21C) = F32(u, 0x21C) + dt;
        if ((U32(act, 0x1C) & 0x40) == 0) {
            short next = S16(act, 4);

            if (S32(u, 0x118) == 0x3C && next == 0) {
                if ((float)end < F32(u, 0x21C)) {
                    F32(u, 0x21C) = (float)end;
                    if (!play_queued(u)) {
                        u32 r = RANDOM() % 100;

                        func_00156AF0(u, r < 0x32 ? 0 : r < 0x4B ? 1 : 2);
                    }
                    done = 1;
                }
            } else if (next == -1 || S16(act, 0) == next) {
                if (next == -1) {
                    if ((float)end < F32(u, 0x21C))
                        F32(u, 0x21C) = (float)end;
                } else {
                    loop_frame(u, end, dt);
                }
            } else if ((float)end < F32(u, 0x21C)) {
                F32(u, 0x21C) = (float)end;
                if (!play_queued(u))
                    func_00156AF0(u, next);
                done = 1;
            }
        } else if (S32(u, 0x220) < 4) {
            loop_frame(u, end, dt);
        } else {
            func_00156AF0(u, S16(act, 4));
            done = 1;
        }
        if (!done) {
            u32 k;

            for (k = 0; k < 2; k++) {
                u8 *s = u + g_0045CC68[k] * 0x70;

                if ((U8(s, 0x2DC) & 4) && PTR(s, 0x2F0) != 0) {
                    int n = S32(*(u8 **)PTR(s, 0x2F0), 8);

                    F32(s, 0x2F4) = F32(s, 0x2F4) + dt;
                    if ((float)n <= F32(s, 0x2F4))
                        F32(s, 0x2F4) = (float)(n - 1);
                }
            }
        }
    }
    if (!blending && (U8(u, 0x27C) & 0x20) == 0 && PTR(u, 0x250) != 0) {
        u8 *b = PTR(u, 0x250);
        int end = act_end(u, b);
        u16 nx;

        F32(u, 0x254) = F32(u, 0x254) + dt;
        nx = U16(PTR(u, 0x250), 4);
        if (nx == 0xFFFF || U16(PTR(u, 0x250), 0) == nx) {
            if ((float)end <= F32(u, 0x254))
                F32(u, 0x254) = (float)end;
        } else if ((float)end <= F32(u, 0x254)) {
            PTR(u, 0x250) = PTR(DESC(u), 8) + nx * 0x20;
            F32(u, 0x254) = 0.0f;
            if (U32(PTR(u, 0x250), 0x1C) & 0x10000000)
                PTR(u, 0x250) = 0;
            if (PTR(u, 0x11C) != 0) {
                func_00156070(u);
                U8(u, 0x27C) = (U8(u, 0x27C) & ~0x20) | 0x20;
            }
        }
        if ((U32(ACT(u), 0x1C) & 0x10000000) == 0) {
            PTR(u, 0x250) = 0;
            F32(u, 0x254) = 0.0f;
            if (PTR(u, 0x11C) != 0) {
                func_00156070(u);
                U8(u, 0x27C) = (U8(u, 0x27C) & ~0x20) | 0x20;
            }
        }
    }
    if (PLAYER(u) < 2 && S32(u, 0x118) < 0x3C && S16(ACT(u), 0) == 0x58 && PTR(u, 0x11C) != 0
        && PTR(u, 0x288) != 0
        && (S16(ACT(PTR(u, 0x288)), 0) == 7 || S16(ACT(PTR(u, 0x288)), 0) == 0x13)) {
        int end = act_end(u, ACT(u));
        float f = dt + F32(PTR(u, 0x288), 0x21C);

        F32(u, 0x21C) = f;
        loop_frame(u, end, dt);
    }
    F32(u, 0x23C) = F32(u, 0x23C) + dt;
}

/* 0x0015E890, 0x60 bytes. The text of message `k` (*out: 0x100 + k, 0x1D8 + k from 0x28,
 * 0x664 + k from 0x71); 1 for 0xFF (none). */
int func_0015E890(int *out, int k)
{
    if (k < 0x28) {
        *out = k + 0x100;
        return 0;
    }
    if (k < 0x71) {
        *out = k + 0x1D8;
        return 0;
    }
    if (k == 0xFF)
        return 1;
    *out = k + 0x664;
    return 0;
}

/* 0x0015E8F0, 0x134 bytes. The reaction kind of situation `k` (0-13; some at random); -1 for
 * none. */
int func_0015E8F0(u32 k)
{
    u32 r;

    switch (k) {
    case 0:
    case 1:
        r = RANDOM() % 100;
        if (r < 0x19)
            return -1;
        if (r < 0x32)
            return 1;
        return 0;
    case 2:
        r = RANDOM() % 100;
        return r < 0x32 ? 1 : 0;
    case 3:
        return 2;
    case 4:
        return 3;
    case 5:
        return 1;
    case 6:
        return 4;
    case 7:
        return 5;
    case 8:
        return 6;
    case 9:
        return 7;
    case 10:
        return 8;
    case 11:
        return 9;
    case 12:
        return 10;
    case 13:
        return 11;
    }
    return -1;
}
