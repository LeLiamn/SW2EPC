/*
 * unit_states.c - battle unit state changes between 0x001CE800 and 0x001CF428: knock-downs,
 * officer states (byte +0x7D of the 0xC0-byte battle officer records at 0x006A3A30, timer at
 * +0x78), duels (partners at +0x0C, the two duelling officers at 0x006AA59C/0x006AA5A0) and their
 * end. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_UNIT_STATES_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A3A30[][0xC0];            /* battle officers */
extern u8 g_00669D60[];
#ifdef SW2E_PC
extern ps2ptr g_006AA59C_a;      /* the duelling officers (first, second side) */
#define g_006AA59C ((u8 *)PS2_PTR(g_006AA59C_a))
#define g_006AA59C_SET(v) (g_006AA59C_a = PS2_ADDR(v))
#else
extern u8 *g_006AA59C;
#define g_006AA59C_a (*(ps2ptr *)&g_006AA59C)
#define g_006AA59C_SET(v) (g_006AA59C = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_006AA5A0_a;      /* the duelling officers (first, second side) */
#define g_006AA5A0 ((u8 *)PS2_PTR(g_006AA5A0_a))
#define g_006AA5A0_SET(v) (g_006AA5A0_a = PS2_ADDR(v))
#else
extern u8 *g_006AA5A0;
#define g_006AA5A0_a (*(ps2ptr *)&g_006AA5A0)
#define g_006AA5A0_SET(v) (g_006AA5A0 = (v))
#endif
extern short g_0040C790[][2];
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))
#define OFF(u) g_006A3A30[*(short *)((u) + 0x178)]
#define FL_B8(o) (*(u32 *)((o) + 0xB8))
#define FL_BC(o) (*(u32 *)((o) + 0xBC))
#define LIFE_MAX(o) (*(short *)((o) + 0x80))
#define LIFE(o) (*(short *)((o) + 0x82))
#define LIFE_SHOWN(o) (*(short *)((o) + 0x84))

/* Sets officer `o`'s state `s` (clearing the state bits). */
#define SET_STATE(o, s) do {                                            \
    FL_BC(o) &= 0xFFF8003F;                                             \
    (o)[0x7D] = (s);                                                    \
} while (0)

/* A timer of `v` frames at 60 Hz in 50 Hz frames (at least 1). */
#define SET_TIMER(o, v) do {                                            \
    u32 v_ = (v) & 0xFFFF;                                              \
    if (v_ == 0) {                                                      \
        *(short *)((o) + 0x78) = 0;                                     \
    } else {                                                            \
        u32 t_ = v_ * 0x32 / 0x3C;                                      \
        *(short *)((o) + 0x78) = (t_ & 0xFFFF) == 0 ? 1 : t_;           \
    }                                                                   \
} while (0)

void func_002A6D20(u8 side, int v);

/* 0x001CE800, 0x19C bytes. Unit `u` is knocked down. */
void func_001CE800(u8 *u)
{
    u8 *o;
    u32 v;
    int h;

    if ((signed char)u[0x19C] < 0)
        return;
    o = OFF(u);
    SET_STATE(o, 3);
    v = 0x32 - o[0x7B];
    h = (int)v / 2;
    if (h != 0)
        v += (int)RANDOM() % h;
    SET_TIMER(o, v);
    if ((FL_B8(o) & 2) != 0) {
        u8 b = u[0x19C];

        u[0x19C] = (b & 0xFB) | 4;
        u[0x19C] = (b & 0xF3) | 4;
        *(short *)(u + 0x12C) = 0x20;
        *(short *)(u + 0x12E) = 0x20;
        if (u[0x14E] < 2)
            GAME_FLAGS |= 0x20000000;
    }
}

/* 0x001CE9A0, 0x80 bytes. */
void func_001CE9A0(u8 *u)
{
    u8 *o;

    if ((signed char)u[0x19C] < 0)
        return;
    o = OFF(u);
    SET_STATE(o, 4);
    if (*(int *)(u + 0x11C) != 0)
        func_00253300(2, u);
}

/* 0x001CEA20, 0x20 bytes, matching. */
void func_001CEA20(u8 *u)
{
    func_00253690(2, u);
}

/* 0x001CEA40, 0x20 bytes, matching. */
void func_001CEA40(u8 *u)
{
    func_00253300(7, u);
}

/* 0x001CEA60, 0xCC bytes. */
void func_001CEA60(u8 *u, u8 *v)
{
    u8 *o = OFF(u);

    SET_STATE(o, 5);
    SET_TIMER(o, func_001F1280() * 3);
}

/* 0x001CEB30, 0x8C bytes. A random item drop (0x17: none; 0x10 rarest). */
int func_001CEB30(void)
{
    u32 v = RANDOM() % 1000;

    if (v < 3)
        return 0x10;
    if (v < 0xD)
        return 0xF;
    if (v < 0x3F)
        return 0xE;
    if (v < 0x14D)
        return 0xD;
    return 0x17;
}

#define LIFE_CLAMP(o, v) (((v) > LIFE_MAX(o) ? LIFE_MAX(o) : (v)) < 1 ? 0 :                \
                          ((v) > LIFE_MAX(o) ? LIFE_MAX(o) : (v)))

/* Lets a duelling officer go. */
#define DUEL_RELEASE(o) do {                                            \
    FL_B8(o) &= 0xFFF9FFFF;                                             \
    FL_BC(o) &= 0xFEFFFFFF;                                             \
} while (0)

/* 0x001CF000, 0x298 bytes. Units `u` and `w` start a duel (`w`'s officer at full life). */
void func_001CF000(u8 *u, u8 *w)
{
    u8 *a = OFF(u), *b = OFF(w);
    short m = LIFE_MAX(b);

    *(u8 **)(a + 0xC) = b;
    *(u8 **)(b + 0xC) = a;
    LIFE(b) = m < 1 ? 0 : m;
    if (LIFE_SHOWN(b) < LIFE(b))
        LIFE_SHOWN(b) = LIFE(b);
    LIFE_SHOWN(b) = LIFE_CLAMP(b, m);
    SET_STATE(b, 0);
    if ((FL_B8(a) & 0xC) != 0) {
        if ((FL_B8(a) & 4) == 0) {
            if (g_006AA59C == b && g_006AA59C != 0) {
                DUEL_RELEASE(g_006AA59C);
                g_006AA59C_SET(0);
            }
            if (g_006AA5A0 != 0)
                DUEL_RELEASE(g_006AA5A0);
            FL_B8(b) |= 0x40000;
            g_006AA5A0_SET(b);
        } else {
            if (g_006AA5A0 == b && g_006AA5A0 != 0) {
                DUEL_RELEASE(g_006AA5A0);
                g_006AA5A0_SET(0);
            }
            if (g_006AA59C != 0)
                DUEL_RELEASE(g_006AA59C);
            FL_B8(b) |= 0x20000;
            g_006AA59C_SET(b);
        }
    }
    b[0xA6] = a[0xA6];
}

/* 0x001CF2A0, 0x140 bytes. Ends the duel between units `u` and `w`. */
void func_001CF2A0(u8 *u, u8 *w, int k)
{
    u8 *a, *b;

    if ((signed char)u[0x19C] < 0)
        return;
    a = OFF(u);
    b = OFF(w);
    if ((FL_B8(a) & 0xC) != 0)
        b[0xA6] = 0;
    *(u8 **)(a + 0xC) = 0;
    *(u8 **)(b + 0xC) = 0;
    SET_STATE(b, 1);
    *(short *)(b + 0x78) = 0xFA;
    if (*(int *)(b + 8) != 0) {
        FL_BC(b) &= ~2;
        *(int *)(b + 8) = 0;
    }
    LIFE_SHOWN(b) = LIFE_MAX(b);
    LIFE(b) = LIFE_MAX(b);
    SET_STATE(a, 0);
    FL_BC(a) &= 0xFFF8003F;
    *(short *)(a + 0x78) = 0xFA;
    if (k != 0)
        *(u32 *)(*(u8 **)(a + 0x10) + 0x80) &= ~0x80000;
    *(int *)(u + 0x13C) = 0;
    *(u32 *)(u + 0x1D0) = *(u32 *)PS2_PTR(0x700000C0);
    *(u32 *)(u + 0x1D4) = *(u32 *)PS2_PTR(0x700000C4);
    *(u32 *)(u + 0x1D8) = *(u32 *)PS2_PTR(0x700000C8);
    *(u32 *)(u + 0x1DC) = *(u32 *)PS2_PTR(0x700000CC);
    *(int *)(w + 0x13C) = 0;
    *(u32 *)(w + 0x1D0) = *(u32 *)PS2_PTR(0x700000C0);
    *(u32 *)(w + 0x1D4) = *(u32 *)PS2_PTR(0x700000C4);
    *(u32 *)(w + 0x1D8) = *(u32 *)PS2_PTR(0x700000C8);
    *(u32 *)(w + 0x1DC) = *(u32 *)PS2_PTR(0x700000CC);
}

/* 0x001CF3E0, 0x48 bytes. Plays unit `u`'s voice `k`. */
void func_001CF3E0(u8 *u, int k)
{
    if (u[0xD4] < 0x11)
        func_002A6D20(u[0x14E], g_0040C790[u[0xD4]][k]);
}
