/*
 * battle_units.c - the battlefield's unit and effect managers (original source file unknown;
 * 0x001724C0-0x0017C0CC, between unit_touch.c and the camera shake). Only the simple functions
 * are written so far.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
 */

#define SW2E_FILE_BATTLE_UNITS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

/* The unit's state flags at +0x198, reached as a member (the original reloads it from the unit
 * each time instead of keeping its address). */
typedef struct {
    u8 pad[0x198];
    Bits8 f198;
} UnitFlags;

#define F198(u, n) (((UnitFlags *)(u))->f198.f##n)

float fabsf(float x);

/* A list of units found in an area of the battlefield grid. */
typedef struct {
    Unit *found[0xA0];
    u32 count;               /* +0x280 */
} UnitList;

extern u8 g_00574DE0[][0x630];           /* the units */
extern u8 g_005ADD80[0x40][0xC0];        /* the effect records */
extern u8 g_005B2BB0[];                  /* the battlefield's unit grid */
extern u32 g_0045D2BC;                   /* (small data) the next effect record to try */
extern u32 g_0045D2C0;                   /* (small data) */
extern u8 g_005B4DF0[0x10], g_005B5030[0x10];   /* flag bytes (bit 0) in larger objects */

void func_00173430(Unit *u);
void func_0017E560(u8 *grid, UnitList *out, float *box);
void func_00178250(void);
void func_002A7A50(void);
void func_00178460(void);
void func_00179700(int a);

/* 0x00173970, 0xFC bytes, matching. Runs func_00173430 for every unit on the field (flag 2 of +0x198)
 * that is not hidden (or is a bodyguard of kind 1 or 2), not riding (except actions 0x55, 0x56,
 * 0x60, 0x61), not in states 0x3D-0x3F, with flag 0x10 of +0x198. */
void func_00173970(void)
{
    int k;
    UnitFlags *u = (UnitFlags *)g_00574DE0[0];

    for (k = 0; k < 0x8F; k++, u = (UnitFlags *)((u8 *)u + 0x630)) {
        u16 a;

        if (!u->f198.f1)
            continue;
        if (BIT(u, 0x19C, 7) && (U8(u, 0x15A) == 0 || U8(u, 0x15A) == 3))
            continue;
        if (PTR(u, 0x288) != 0) {
            a = U16(PTR(u, 0x210), 0);
            if (a != 0x55 && a != 0x56 && a != 0x60 && a != 0x61)
                continue;
        }
        if ((u32)(S32(u, 0x118) - 0x3D) > 2 && u->f198.f4)
            func_00173430((Unit *)u);
    }
}

/* 0x001748B0, 0x188 bytes. The first unit on the field near `u` (within `r` flat and `h`
 * high, found in the grid) with a model and mount kind (+0x155) `kind`; 0 for none. */
Unit *func_001748B0(float r, float h, Unit *u, u32 kind)
{
    UnitList list;
    float box[4], e;
    u32 k;

    e = h + F32(PTR(u, 0x114), 0x88);
    box[0] = F32(u, 0x40) - e;
    box[1] = F32(u, 0x40) + e;
    box[2] = F32(u, 0x48) - e;
    list.count = 0;
    box[3] = F32(u, 0x48) + e;
    func_0017E560(g_005B2BB0, &list, box);
    for (k = 0; k < list.count; k++) {
        u8 *v = list.found[k];

        if (BIT(v, 0x198, 1) && PTR(v, 0x11C) != 0 && v != u && kind == U8(v, 0x155)
            && fabsf(F32(u, 0x44) - F32(v, 0x44)) <= h) {
            float x = F32(u, 0x40) - F32(v, 0x40), z = F32(u, 0x48) - F32(v, 0x48);

            if (x * x + z * z < r * r)
                return v;
        }
    }
    return 0;
}

/* 0x00177ED0, 0xA4 bytes. Takes the next effect record not locked (flag 4 of +0x8C), in turn;
 * one still playing (flag 1) is stopped first. */
u8 *func_00177ED0(void)
{
    u8 *r;

    for (;;) {
        r = g_005ADD80[g_0045D2BC];
        if (!BIT(r, 0x8C, 2))
            break;
        g_0045D2BC = g_0045D2BC + 1;
        if (g_0045D2BC > 0x3F)
            g_0045D2BC = 0;
    }
    if (BIT(r, 0x8C, 0))
        func_001AE090(r);
    g_0045D2BC = g_0045D2BC + 1;
    if (g_0045D2BC > 0x3F)
        g_0045D2BC = 0;
    return r;
}

/* 0x001781C0, 0x88 bytes, matching. Shuts the battlefield managers down. */
void func_001781C0(void)
{
    func_00178460();
    func_001BCE60();
    func_0017C5C0();
    func_001AE530();
    func_002A7A50();
    func_0016CE80();
    func_0024BE90();
    g_0045D2C0 = 0;
    BIT(g_005B4DF0, 0, 0) = 0;
    BIT(g_005B5030, 0, 0) = 0;
}

/* 0x00178460, 0x80 bytes, matching. Resets the battlefield managers. */
void func_00178460(void)
{
    func_00178250();
    func_002A7D90();
    func_001BCF00();
    func_0017C640();
    func_0024BF60();
    func_0016CEB0();
    g_0045D2C0 = 0;
    BIT(g_005B4DF0, 0, 0) = 0;
    BIT(g_005B5030, 0, 0) = 0;
}

/* 0x001796D0, 0x2C bytes, matching. func_00179700(0) unless func_0032E7B0 says otherwise. */
void func_001796D0(void)
{
    if (func_0032E7B0() == 0)
        func_00179700(0);
}

typedef unsigned long long u64;

#define g_70000158 PS2_GETP(u32 *, 0x70000158)         /* the DMA chain's write cursor */
#define g_70000158_SET(v) PS2_SETP(0x70000158, v)

extern u32 g_0045D2B8;                   /* (small data) the number of units drawn */
extern Unit *g_00574DA0[];               /* the units to draw */
extern int g_0045D2C8;                   /* (small data) the side in the duel view */
extern int g_0045CC80;                   /* (small data) */

int func_00100FB0(void);                 /* the screen width */
int func_00100FC0(void);                 /* the screen height */
float func_00100FD0(void);
float func_00136D70(float a);            /* tanf? */

/* 0x0017A350, 0xAC bytes, matching. Draws the units of the draw list. */
void func_0017A350(void)
{
    u32 k;
    int mode = func_001F2450();

    func_0014FCB0((unsigned char *)PS2_PTR(g_0045D2C0));
    func_0014FE00();
    func_001500E0(100);
    if (g_0045D2B8 != 0) {
        for (k = 0; k < g_0045D2B8; k++) {
            Unit *u = g_00574DA0[k];

            if (u != 0) {
                func_002AD960(u);
                func_001698D0(u, mode);
            }
        }
    }
}

/* The GS packet setting both scissor registers to `s`. */
static inline void set_scissor(u64 s)
{
    u32 *d = g_70000158;
    u64 *q;

    d[0] = 0x10000003;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x50000003;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008002ULL;
    q[1] = 0xE;
    q[2] = s;
    q[3] = 0x40;
    q[4] = s;
    q[5] = 0x41;
    g_70000158_SET((u32 *)(q + 6));
}

/* 0x0017A400, 0x130 bytes. Limits drawing to the top (`bottom` 0) or bottom half of the
 * screen (the two-player split). */
void func_0017A400(int bottom)
{
    int w = func_00100FB0(), y0, y1;

    if (bottom == 0) {
        y0 = 0;
        y1 = func_00100FC0() / 2;
    } else {
        y0 = func_00100FC0() / 2;
        y1 = func_00100FC0();
    }
    set_scissor((u64)(y1 - 1) << 48 | (u64)(w - 1) << 16 | (u64)y0 << 32);
}

/* 0x0017A530, 0x104 bytes. Draws on the whole screen again. */
void func_0017A530(void)
{
    u32 *d = g_70000158;
    u64 *q;

    d[0] = 0x10000003;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x50000003;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008002ULL;
    q[1] = 0xE;
    q[2] = (u64)(func_00100FB0() - 1) << 16 | (u64)(func_00100FC0() - 1) << 48;
    q[3] = 0x40;
    q[4] = (u64)(func_00100FB0() - 1) << 16 | (u64)(func_00100FC0() - 1) << 48;
    q[5] = 0x41;
    g_70000158_SET((u32 *)(q + 6));
}

/* 0x0017A640, 0x78 bytes. Takes every unit's model away (end of a battle). */
void func_0017A640(void)
{
    u8 *u = g_00574DE0[0];
    int k;

    for (k = 0; k < 0x8F; k++, u += 0x630) {
        if (BIT(u, 0x198, 1) && PTR(u, 0x11C) != 0)
            func_00165560(u);
    }
    g_0045D2C8 = 0;
    g_0045CC80 = 8;
}

/* The identity matrix. */
static inline void identity(float *m)
{
    int i, k;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i * 4 + k] = i == k ? 1.0f : 0.0f;
}

/* 0x0017A6C0, 0x78 bytes. A perspective matrix: screen `w` x `h` at distance `d`, depth from
 * `n` to `f`. */
void func_0017A6C0(float w, float h, float d, float n, float f, float *m)
{
    identity(m);
    m[0] = d / w;
    m[5] = d / h;
    m[10] = (f + n) / (f - n);
    m[14] = f * n * -2.0f / (f - n);
    m[11] = 1.0f;
    m[15] = 0.0f;
}

/* 0x0017A740, 0x64 bytes. The matrix from view space to the screen: scales `sx` x `kx`,
 * `sy` x `ky`, centre (`cx`, `cy`), depth `zf` / `zn` to the middle of the range. */
void func_0017A740(float sx, float sy, float kx, float ky, float cx, float cy, float zf,
                   float zn, float *m)
{
    identity(m);
    m[0] = sx * kx;
    m[5] = sy * ky;
    m[10] = (-zn + zf) * 0.5f;
    m[14] = (zn + zf) * 0.5f;
    m[12] = cx;
    m[13] = cy;
}

/* 0x0017A920, 0x158 bytes. A camera object's defaults: eye 100 behind the origin, the screen
 * centre 2048 x 2048, a 15-degree view angle with its distance for a 224 view height, depth
 * from 64 to 50000, far clip 10000 (4500 with flag 4, just cleared). */
void func_0017A920(u8 *c)
{
    F32(c, 0x1C0) = 0.0f;
    F32(c, 0x1C4) = 0.0f;
    F32(c, 0x1C8) = -100.0f;
    F32(c, 0x1CC) = 1.0f;
    F32(c, 0x1D0) = 0.0f;
    F32(c, 0x1D4) = 0.0f;
    F32(c, 0x1D8) = 0.0f;
    F32(c, 0x1DC) = 1.0f;
    F32(c, 0x1F0) = 0.0f;
    F32(c, 0x1F4) = 0.0f;
    F32(c, 0x1F8) = 512.0f;
    F32(c, 0x1FC) = func_00100FD0();
    F32(c, 0x200) = 2048.0f;
    F32(c, 0x204) = 2048.0f;
    F32(c, 0x208) = 0.8f;
    F32(c, 0x20C) = func_00100FD0() / 480.0f;
    F32(c, 0x210) = 64.0f;
    F32(c, 0x214) = 50000.0f;
    F32(c, 0x218) = 2047.9688f;
    F32(c, 0x21C) = 2047.9688f;
    F32(c, 0x220) = 0.0f;
    F32(c, 0x224) = 0.2617994f;
    BIT(c, 0x230, 1) = 0;
    F32(c, 0x22C) = 112.0f;
    F32(c, 0x228) = F32(c, 0x22C) / func_00136D70(F32(c, 0x224) * 0.5f);
    BIT(c, 0x230, 2) = 0;
    F32(c, 0x238) = 1.0f;
    if (BIT(c, 0x230, 2))
        F32(c, 0x23C) = 4500.0f;
    else
        F32(c, 0x23C) = 10000.0f;
}
