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
float vu0_angle(float x, float z);               /* VU0 micro subroutine 0x30 (atan2?) */
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
void func_00156AF0(Unit *u, int action);
void func_001CF000(Unit *u, Unit *v);
void func_00158CD0(Unit *u, int a);
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

/* 0x001523C0, 0x4C bytes. One of four other reactions, at random. */
void func_001523C0(Unit *u)
{
    func_00156AF0(u, g_0045CC60[RANDOM() & 3]);
}

/* 0x00152410, 0xB4 bytes. Reaction `k` (table at 0x004063F8); for the players, the message box
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
int func_00273770(Unit *u, short damage, u32 *out);
void func_0016C180(u32 a, Unit *u);
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
    u32 got;

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

extern u8 g_00574DE0[][0x630];           /* (effect?) objects; the players' from index 0x89 */
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
