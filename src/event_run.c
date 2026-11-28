/*
 * event_run.c - pieces of the event scene runtime (parts of 0x001D8140-0x001DF160): the event
 * scene's frame (set-up, drawing by scene kind 4), the command dispatchers by kind (tables at
 * 0x0040CA30-0x0040CB70), the event file cache (0x0073C7B0), the camera shake records and the
 * three effect pairs (0x00730DA0). Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EVENT_RUN_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef void (*EvFn)(u8 *p);

extern int g_0045D374;                   /* (small data) the scene kind */
extern u8 g_0045D3D4;                    /* (small data) the scene kind kept */
extern int g_0045D3E0;                   /* (small data) the player */
#ifdef SW2E_PC
extern ps2ptr g_0045D3E4_a;
#define g_0045D3E4 ((u8 *)PS2_PTR(g_0045D3E4_a))
#define g_0045D3E4_SET(v) (g_0045D3E4_a = PS2_ADDR(v))
#else
extern u8 *g_0045D3E4;
#define g_0045D3E4_a (*(ps2ptr *)&g_0045D3E4)
#define g_0045D3E4_SET(v) (g_0045D3E4 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0045D3E8_a;
#define g_0045D3E8 ((u8 *)PS2_PTR(g_0045D3E8_a))
#define g_0045D3E8_SET(v) (g_0045D3E8_a = PS2_ADDR(v))
#else
extern u8 *g_0045D3E8;
#define g_0045D3E8_a (*(ps2ptr *)&g_0045D3E8)
#define g_0045D3E8_SET(v) (g_0045D3E8 = (v))
#endif
extern u8 *g_0045D3F0[2];                /* (small data) the players' shake records */
#ifdef SW2E_PC
extern ps2ptr g_0045D2C0_a;                   /* (small data) the camera */
#define g_0045D2C0 ((u8 *)PS2_PTR(g_0045D2C0_a))
#define g_0045D2C0_SET(v) (g_0045D2C0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2C0;
#define g_0045D2C0_a (*(ps2ptr *)&g_0045D2C0)
#define g_0045D2C0_SET(v) (g_0045D2C0 = (v))
#endif
extern u8 g_00730570[2][0x240];          /* the players' cameras */
extern u8 g_00730A20[2][0x174];
extern u8 g_00730DA0[3][0x10];           /* the effect pairs */
extern int g_00730E50[];
extern u8 *g_0073C7B0[0x34F];            /* the event file cache */
extern u8 g_0073C7A4, g_0073C7A5;
extern char g_00428EE8[];                /* the allocations' source name */
#ifdef SW2E_PC
extern ps2ptr g_005BA6A0_a;
#define g_005BA6A0 ((u8 *)PS2_PTR(g_005BA6A0_a))
#define g_005BA6A0_SET(v) (g_005BA6A0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6A0;
#define g_005BA6A0_a (*(ps2ptr *)&g_005BA6A0)
#define g_005BA6A0_SET(v) (g_005BA6A0 = (v))
#endif
extern EvFn g_0040CA30[0xD], g_0040CA70[9], g_0040CB30[5], g_0040CB48[3], g_0040CB58[3];
extern EvFn g_0040CB70[8];

#define CMD(p) PS2_LOADP(u8 *, ((p) + 8))
#define CMD_SET(p, v) PS2_STOREP(u8 *, ((p) + 8), v)

void func_001D7760(void);
void func_001D7BD0(void);
void func_001D7920(void);
void func_001D79D0(float dt, u8 *e);
void func_001DA940(u8 *p);
void func_001DB8C0(void);
void func_001DA980(u8 *p);
void func_001D76F0(u8 *c);
void func_001E2150(u8 *p);
void func_001D9750(int k);
void func_001DAEB0(u8 *p);
void func_002E9B70(u8 *p);

/* 0x001D8140, 0x28 bytes, matching. */
void func_001D8140(void)
{
    if (g_0045D3E0 == 0)
        func_003E7310(1);
}

/* 0x001D8DB0, 0x1C bytes, matching. */
void func_001D8DB0(void)
{
    func_00217BC0();
}

/* 0x001D8E30, 0x1C bytes, matching. */
void func_001D8E30(void)
{
    func_002E5ED0();
}

/* 0x001D8E50, 0x34 bytes, matching. Switches the drawing to the event scene kind (4). */
void func_001D8E50(u8 *e)
{
    func_001D7760();
    if (g_0045D374 != 4) {
        g_0045D3D4 = g_0045D374;
        g_0045D374 = 4;
    }
}

/* 0x001D8E90, 0x2C bytes, matching. */
void func_001D8E90(void)
{
    func_001D7BD0();
    func_001D7920();
    func_001C8B30();
}

/* 0x001D8EC0, 0x24 bytes, matching. */
void func_001D8EC0(float dt, u8 *e)
{
    func_001D79D0(dt, e);
    func_001C8A00();
}

/* 0x001D8EF0, 0x1C bytes, matching. */
void func_001D8EF0(int a, int b)
{
    func_001C92D0(b);
}

/* 0x001D8F10, 0x2C bytes, matching. Back to the kept scene kind. */
void func_001D8F10(void)
{
    func_001C8870(0xB);
    func_001C8870(0xC);
    g_0045D374 = g_0045D3D4;
}

/* 0x001D8F40, 0x4C bytes, matching. Runs command `p` by its kind (+5). */
void func_001D8F40(u8 *p)
{
    u8 b = CMD(p)[5];

    if (b < 0xD && g_0040CA30[b] != 0)
        g_0040CA30[b](p);
}

/* 0x001D91A0, 0x50 bytes, matching. */
void func_001D91A0(u8 *p, int b)
{
    func_001DA940(p);
    func_001DAD50((unsigned int *)(p), (unsigned char *)PS2_PTR(func_0020E7B0()));
    func_001DA9A0(PS2_ADDR(p), b);
}

/* 0x001D9280, 0x54 bytes, matching. Starts the event for the current player. */
void func_001D9280(u8 *p)
{
    func_001D91A0(p, (int)PS2_ADDR(g_00730A20[g_0045D3E0]));
    func_001D91F0((unsigned int *)(p), 1);
}

/* 0x001D92E0, 0x6C bytes. Ends it. */
void func_001D92E0(u8 *p)
{
    func_001DB8C0();
    func_00272C00(p);
    func_001D8F10();
    func_001DA980(p);
    func_001D76F0(g_00730570[g_0045D3E0]);
    func_001E3010(PS2_ADDR(p));
    g_0073C7A4 = 0;
}

/* 0x001D9350, 0x5C bytes. */
void func_001D9350(u8 *p)
{
    g_0045D2C0_SET(g_00730570[g_0045D3E0]);
    func_001D75D0();
    func_001E2150(p);
    func_001D8E90();
    func_00272B60(p);
}

/* 0x001D9610, 0x58 bytes. Entry `b` of block `a` of the event data. */
u8 *func_001D9610(int a, int b)
{
    u8 *t = func_0020E8B0();
    int *p = (int *)(t + *(int *)(t + a * 4));

    return (u8 *)p + *(int *)((u8 *)p + b * 4 + *p) + *p;
}

/* 0x001D9750, 0x5C bytes, matching. Loads event file `k`. */
void func_001D9750(int k)
{
    g_0073C7B0[k] = func_001026D0(1, k + 0xE3, 0, 1, 0, 0, g_00428EE8, 0x166);
}

/* 0x001D9670, 0x64 bytes, matching. Event file `v` (0x11CF-0x151D), loaded on first use. */
u8 *func_001D9670(int v)
{
    int k = v - 0x11CF;

    if (v < 0x11CF || v > 0x151D)
        return 0;
    if (g_0073C7B0[k] == 0)
        func_001D9750(k);
    return g_0073C7B0[k];
}

/* 0x001D97B0, 0x5C bytes. Frees the cached event files. */
void func_001D97B0(void)
{
    int k;

    for (k = 0; k < 0x34F; k++) {
        if (g_0073C7B0[k] != 0) {
            func_00102EC0(g_0073C7B0[k]);
            g_0073C7B0[k] = 0;
        }
    }
}

/* 0x001D9810, 0x38 bytes. */
void func_001D9810(u8 *p)
{
    u8 *q = CMD(p);

    func_001D6BD0((unsigned int *)(p + 0x48), (unsigned int *)(q + q[q[6] + 7] + 7), q[7], q[q[6] + 7]);
}

/* 0x001DA7E0, 0x6C bytes, matching. */
void func_001DA7E0(u8 *p)
{
    u8 b;

    if (p[0x51] == 0 && CMD(p)[4] != 8)
        return;
    b = CMD(p)[4];
    if (b < 9 && g_0040CA70[b] != 0)
        g_0040CA70[b](p);
}

/* 0x001DA850, 0x4C bytes, matching. */
void func_001DA850(u8 *p)
{
    u8 b = CMD(p)[5];

    if (b < 5 && g_0040CB30[b] != 0)
        g_0040CB30[b](p);
}

/* 0x001DA8A0, 0x4C bytes, matching. */
void func_001DA8A0(u8 *p)
{
    u8 b = CMD(p)[5];

    if (b < 3 && g_0040CB48[b] != 0)
        g_0040CB48[b](p);
}

/* 0x001DA8F0, 0x4C bytes, matching. */
void func_001DA8F0(u8 *p)
{
    u8 b = CMD(p)[5];

    if (b < 3 && g_0040CB58[b] != 0)
        g_0040CB58[b](p);
}

/* 0x001DA940, 0x40 bytes, matching. Resets an event runner. */
void func_001DA940(u8 *p)
{
    func_00118850(p, 0x60);
    *(int *)(p + 0x18) = -1;
    p[0x51] = 1;
    *(float *)(p + 0x40) = -1.0f;
}

/* 0x001DA980, 0x14 bytes, matching. */
void func_001DA980(u8 *p)
{
    *(u32 *)p &= 0xFFFFFFFE;
}

/* 0x001DAEA0, 0xC bytes, matching. */
int func_001DAEA0(int v)
{
    return v > 0x1B;
}

/* 0x001DB1B0, 0x28 bytes, matching. */
void func_001DB1B0(u8 *p)
{
    if (*(int *)(p + 0x20) == 0)
        func_001DAEB0(p);
}

/* 0x001DB660, 0x4C bytes, matching. */
void func_001DB660(u8 *p)
{
    u8 b = CMD(p)[5];

    if (b < 8 && g_0040CB70[b] != 0)
        g_0040CB70[b](p);
}

/* 0x001DB8A0, 0x20 bytes, matching. */
void func_001DB8A0(u8 *e)
{
    g_0045D3E8_SET(func_0020EC50(0x100));
}

/* 0x001DB8C0, 0xC bytes. */
void func_001DB8C0(void)
{
    g_0073C7A5 = 0;
}

/* 0x001DB8D0, 8 bytes, matching. */
u8 *func_001DB8D0(void)
{
    return g_0045D3E4;
}

/* 0x001DB9F0, 0x2C bytes, matching. */
void func_001DB9F0(void)
{
    if (g_0045D3E4 != 0) {
        func_00102EC0(g_0045D3E4);
        g_0045D3E4_SET(0);
    }
}

/* 0x001DBA20, 0x48 bytes, matching. */
int func_001DBA20(int v)
{
    if (v < 0x39)
        return 0;
    if (v < 0x3D)
        return 1;
    if (v < 0x40)
        return 2;
    return 0;
}

/* 0x001DBC00, 0x30 bytes, matching. */
void func_001DBC00(void)
{
    func_00118850(g_0045D3F0[g_0045D3E0], 0x30);
}

/* 0x001DBC30, 0x30 bytes, matching. */
void func_001DBC30(float f)
{
    u8 *p = g_0045D3F0[g_0045D3E0];

    *(float *)(p + 0x14) = *(float *)(p + 0x18) * f + *(float *)(p + 0x14) + 0.0f;
}

/* 0x001DBC60, 0x3C bytes. A free effect pair. */
u8 *func_001DBC60(void)
{
    int k;

    for (k = 0; k < 3; k++) {
        if (g_00730DA0[k][0xE] == 0)
            return g_00730DA0[k];
    }
    return 0;
}

/* 0x001DBCA0, 0x4C bytes. The effect pair with id `v`. */
u8 *func_001DBCA0(short v)
{
    int k;

    for (k = 0; k < 3; k++) {
        if (g_00730DA0[k][0xE] != 0 && *(short *)(g_00730DA0[k] + 0xC) == v)
            return g_00730DA0[k];
    }
    return 0;
}

/* 0x001DBCF0, 0x54 bytes. */
void func_001DBCF0(void)
{
    int k;

    for (k = 0; k < 3; k++) {
        *(int *)(g_00730DA0[k] + 8) = 0;
        *(short *)(g_00730DA0[k] + 0xC) = 0;
        g_00730DA0[k][0xE] = 0;
        g_00730DA0[k][0xF] = 0;
    }
}

/* 0x001DC430, 0x5C bytes, matching. */
void func_001DC430(void)
{
    int k;

    for (k = 0; k < 3; k++) {
        if (g_00730DA0[k][0xE] != 0) {
            func_002E9B70(PS2_LOADP(u8 *, g_00730DA0[k]));
            func_002E9B70(PS2_LOADP(u8 *, (g_00730DA0[k] + 4)));
        }
    }
}

/* 0x001DCEB0, 0x58 bytes. The current speaker's look kind (0x40 for the narrator). */
u8 func_001DCEB0(int k)
{
    u32 v = func_0020E230(k) & 0xFFFF;

    if (v == 0x252)
        return 0x40;
    return g_005BA6A0[v * 0x2C + 6];
}

/* 0x001DF110, 0x58 bytes. */
int func_001DF110(u32 k, int j)
{
    k &= 0xFFFF;
    if (k < 0x20 && g_00730E50[k] < 10)
        return g_00730E50[k + j];
    return 0;
}
