/*
 * target_gauge.c - the life gauges shown over the actors the players fight (10 slots: 5 per
 * player in two-player mode), drawn into the two screens' packet buffers. Original file name
 * unknown (parts of 0x00248120-0x0024A424).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_TARGET_GAUGE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The gauge state at 0x00732508. */
typedef struct {
    u32 unknown_00[3];
    int shown[10];           /* +0x0C -1: cleared */
    u8 b34[10];              /* +0x34 */
    u8 b3E[10];              /* +0x3E */
    u8 actor[10];            /* +0x48 0xFF = none */
    u8 busy;                 /* +0x52 */
    u8 b53;                  /* +0x53 */
    u8 b54[0x1C];            /* +0x54 */
} Gauges;

extern Gauges g_00732508;
extern u8 *g_00732500[2];                /* the two screens' packet buffers */
extern u8 g_00574DE0[][0x630];           /* the actors */
#ifdef SW2E_PC
extern ps2ptr g_0045D2C0_a;                   /* (small data) the camera */
#define g_0045D2C0 ((u8 *)PS2_PTR(g_0045D2C0_a))
#define g_0045D2C0_SET(v) (g_0045D2C0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2C0;
#define g_0045D2C0_a (*(ps2ptr *)&g_0045D2C0)
#define g_0045D2C0_SET(v) (g_0045D2C0 = (v))
#endif
extern u8 g_005B4BC0[], g_005B4E00[];    /* the two players' cameras */
extern u8 g_00669D60[];

#define SCREEN (*(int *)PS2_PTR(0x70000150))      /* (scratchpad) the screen being drawn */

void func_00248D10(int how, int k, Gauges *g, u8 *buf);

/* 0x00248120, 0xA0 bytes. A gauge's fade (0-0x80) at step `v` of 100 from `start`. */
int func_00248120(int v, int start)
{
    if (v < start)
        return 0;
    if (v < 0x56) {
        if (start + 0xF < v)
            return 0x80;
        return (v - start) * 0x80 / 0xF;
    }
    return (100 - v) * 0x80 / 0xF;
}

/* 0x002490A0, 0x218 bytes. Updates gauge `k` (`how`: which screens): cleared once when it has no
 * actor, dropped when its actor is gone. */
void func_002490A0(int k, int how)
{
    u8 a = g_00732508.actor[k];

    if (a == 0xFF) {
        int s;

        if (g_00732508.shown[k] == -1)
            return;
        g_00732508.shown[k] = -1;
        for (s = 0; s < 2; s++) {
            u8 *b = g_00732500[s] + k * 0x390;
            int j;

            *(u64 *)(b + 0x162A0) = 0xDF000001FF0000ULL;
            *(u64 *)(b + 0x162A8) = 0x41;
            for (j = 0; j < 11; j++) {
                *(u64 *)(b + 0x162E0 + j * 0x50) = 0;
                *(u64 *)(b + 0x162F0 + j * 0x50) = 0;
            }
        }
    } else if (*(int *)(g_00574DE0[a] + 0x11C) == 0 || (g_00574DE0[a][0x198] & 2) == 0) {
        g_00732508.actor[k] = 0xFF;
        g_00732508.shown[k] = 0;
    } else {
        func_00248D10(how, k, &g_00732508, g_00732500[SCREEN]);
    }
}

/* 0x002492C0, 0xD0 bytes. Updates all the gauges (in two-player mode, five per player's camera). */
void func_002492C0(void)
{
    int k;

    g_00732508.b53 = 0;
    if (g_00732508.busy == 1)
        return;
    if ((*(u32 *)(g_00669D60 + 0x200) & 2) == 0) {
        for (k = 0; k < 10; k++)
            func_002490A0(k, 2);
    } else {
        g_0045D2C0_SET(g_005B4BC0);
        for (k = 0; k < 5; k++)
            func_002490A0(k, 0);
        g_0045D2C0_SET(g_005B4E00);
        for (k = 5; k < 10; k++)
            func_002490A0(k, 1);
    }
}

/* 0x00249390, 0x1C bytes. */
void func_00249390(int k, u8 v)
{
    g_00732508.b54[k] = v;
    g_00732508.b54[k + 2] = 10;
}

/* 0x00249AD0, 0x1C bytes. */
void func_00249AD0(int k, u8 v)
{
    g_00732508.b54[k + 8] = v;
    g_00732508.b54[k + 10] = 10;
}

/* 0x0024A270, 0x24 bytes. */
void func_0024A270(int k, u8 v)
{
    g_00732508.b54[k + 0xC] = v;
    g_00732508.b54[k + 0xE] = 100;
    g_00732508.busy = 1;
}

/* 0x0024A400, 0x24 bytes. */
void func_0024A400(int k, u8 v)
{
    g_00732508.b54[k + 0x10] = v;
    g_00732508.b54[k + 0x12] = 100;
    g_00732508.busy = 1;
}

extern u64 g_0068F0F0;                   /* the TEX0 value of a texture set */
extern u8 g_006A3A30[][0xC0];            /* the battle officers */

void func_0024B330(int a, int k);

/* 0x00249670, 0x198 bytes. Gauge `k`'s second bar (texture 0x3F0A; `alt`: its other half). */
void func_00249670(int k, u8 v, int alt)
{
    u64 t;
    int s;

    g_00732508.b54[k + 4] = v;
    g_00732508.b54[k + 6] = 10;
    t = func_00106C90(g_0068F0F0, 0x3F0A);
    for (s = 0; s < 2; s++) {
        u8 *b = g_00732500[s] + k * 0x250;

        *(u64 *)(b + 0x186B8) = t;
        if (alt == 0) {
            *(u64 *)(b + 0x186C8) = 0x3F61000000000000ULL;
            *(u64 *)(b + 0x186D8) = 0x3F7F00003D800000ULL;
        } else {
            *(u64 *)(b + 0x186C8) = 0x3F6100003D800000ULL;
            *(u64 *)(b + 0x186D8) = 0x3F7F00003E000000ULL;
        }
    }
}

/* 0x0024BA10, 0x94 bytes. Draws the markers of the battle officers in play. */
void func_0024BA10(int a)
{
    int k;

    for (k = 0; k < 0x8F; k++) {
        u32 f = *(u32 *)(g_006A3A30[k] + 0xB8);

        if ((f & 0xC) == 0 && (f & 1) != 0 && (f & 0x8400) == 0)
            func_0024B330(a, k);
    }
}
