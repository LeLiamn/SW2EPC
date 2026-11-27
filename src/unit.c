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

float vu0_angle(float x, float z);               /* VU0 micro subroutine 0x30 (atan2?) */
void vu0_rot_y(float m[4][4], float yaw);        /* VU0 micro subroutine 0x70: rotation about Y */

extern u8 g_005B5088[][0xD0];            /* per weapon kind: motion tables (+0, +0x10) */
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

        U32(u, 0x2F0) = *(u32 *)(g_005B5088[kind] + 0x10) + m * 0x20;
        U32(u, 0x2F4) = 0;
    }
    m = U16(PTR(u, 0x210), 8);
    if (m != 0xFFFF && (U8(u, 0x34C) & 4)) {
        u8 kind = U8(PTR(u, 0x110), 0x1C);

        U32(u, 0x360) = *(u32 *)(g_005B5088[kind] + 0) + m * 0x20;
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
