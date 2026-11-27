/*
 * ui_misc2.c - small pieces between 0x002C3DC0 and 0x002C5C5C: a list of 16 effect nodes
 * (0x00795060, 0x40 bytes each, free list gp 0x0045D594, used list gp 0x0045D590), the battle's
 * message log (16 records of 0x110 bytes at 0x005BC5A8), pad button lookups and the gauges'
 * set-ups (a speed, three colour bytes, a step). Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_0045D5B0[2];                 /* (small data) */
extern u8 g_007954C0[], g_00795460[0x40];
extern u8 g_00795060[0x10][0x40];
extern u8 **g_0045D590, **g_0045D594;    /* (small data) used and free nodes */
extern int g_0045D598, g_0045D5A0;
extern u8 g_005BC5A8[0x10][0x110];       /* the message log */
extern int g_005BD6A8, g_005BD6AC;
extern u8 g_00669D60[];
extern u8 *g_00412680[];
extern u8 g_00799A20[0x10], g_00799A38[0x10], g_00799A50[0x10];
extern u8 *g_005BA6A0;

void func_00118AC0(void *to, const void *from, u32 n);
void func_0027E610(u8 *o);
u8 *func_0027E8C0(u8 *o, u32 k);
int func_002F27D0(int o);

/* 0x002C3DC0, 0x3C bytes. The record of kind `k` (0: none). */
u8 *func_002C3DC0(u8 k)
{
    if (g_0045D5B0[0] == k)
        return g_0045D5B0;
    return 0;
}

/* 0x002C4220, 0x30 bytes. */
u8 func_002C4220(int a, u8 *p)
{
    u8 *r = func_002C3DC0(*p);

    return r == 0 ? 0 : r[1];
}

/* 0x002C44F0, 0xC bytes, matching. */
u8 *func_002C44F0(void)
{
    return g_007954C0;
}

/* 0x002C4500, 0x28 bytes. Takes a node from the free list. */
void func_002C4500(void)
{
    u8 **n = g_0045D594;

    if (n != 0) {
        g_0045D594 = (u8 **)n[0];
        n[0] = (u8 *)g_0045D590;
        g_0045D590 = n;
    }
}

/* 0x002C4530, 0x40 bytes, matching. Gives back the first node of list `l` (dropping its model). */
void func_002C4530(u8 ***l)
{
    u8 **n = *l;

    if (n != 0) {
        u8 *o = n[1];

        if (o != 0)
            *(u32 *)(o + 0x38) |= 8;
        *l = (u8 **)n[0];
        n[0] = (u8 *)g_0045D594;
        g_0045D594 = n;
    }
}

/* 0x002C4570, 0x48 bytes. */
void func_002C4570(void)
{
    int k;

    g_0045D5A0 = 0;
    g_0045D598 = 0;
    g_0045D594 = (u8 **)g_00795060[0];
    g_0045D590 = 0;
    for (k = 0; k < 0xF; k++)
        *(u8 **)g_00795060[k] = g_00795060[k + 1];
    *(u8 **)g_00795060[0xF] = 0;
}

/* 0x002C45C0, 0x3C bytes, matching. */
void func_002C45C0(void)
{
    while (g_0045D590 != 0)
        func_002C4530(&g_0045D590);
}

/* 0x002C4600, 0x28 bytes, matching. */
void func_002C4600(const void *p)
{
    func_00118AC0(g_00795460, p, 0x40);
}

/* 0x002C4630, 0x7C bytes. */
int func_002C4630(u8 *o, int a, u32 k)
{
    k &= 0xFF;
    if (k == 1 || k == 3) {
        func_002C45C0();
        func_0027E610(o);
        return 1;
    }
    if (k == 2 || k == 0)
        return func_0027E8C0(o, k) != 0;
    return 0;
}

/* 0x002C4B70, 0x38 bytes, matching. Loads the message log from the save image `p`; its end. */
u8 *func_002C4B70(u8 *p)
{
    func_00118AC0(g_005BC5A8, p, 0x1108);
    return p + 0x1108;
}

/* 0x002C4BB0, 0x34 bytes, matching. Saves it. */
u8 *func_002C4BB0(u8 *p)
{
    func_00118AC0(p, g_005BC5A8, 0x1108);
    return p + 0x1108;
}

/* 0x002C4BF0, 8 bytes, matching. */
void func_002C4BF0(void)
{
}

/* 0x002C4C00, 0x50 bytes. Clears it. */
void func_002C4C00(void)
{
    u32 k;

    g_005BD6A8 = 0;
    g_005BD6AC = 0;
    for (k = 0; k < 0x10; k++)
        *(int *)g_005BC5A8[k] = -1;
}

/* 0x002C58E0, 0x50 bytes. Which of player `p`'s 16 pad slots holds button `v`. */
int func_002C58E0(int p, u32 v)
{
    int k;

    for (k = 0; k < 0x10; k++) {
        if (v == g_00669D60[0x2C + p * 0x12 + k])
            return k;
    }
    return k;
}

/* 0x002C5980, 0x70 bytes. The button's icon text. */
u8 *func_002C5980(int p, u32 v)
{
    int k = func_002C58E0(p, v), i = 6;

    if (k == 6)
        i = 5;
    else if (k == 5)
        i = 4;
    else if (k != 4)
        i = k;
    return g_00412680[i];
}

/* A gauge: speed, colour (r, g, b), step, value. */
#define GAUGE_SET(g, f, r, gr, b, s) do {                               \
    (g)[4] = (r);                                                       \
    (g)[5] = (gr);                                                      \
    (g)[6] = (b);                                                       \
    *(int *)((g) + 8) = (s);                                            \
    *(int *)((g) + 0xC) = 0;                                            \
    *(float *)(g) = (f);                                                \
} while (0)

/* 0x002C59F0, 0x3C bytes, matching. */
void func_002C59F0(void)
{
    GAUGE_SET(g_00799A20, 1.0f, 0x40, 0x40, 0, 0);
}

/* 0x002C5A30, 0x2C bytes. */
void func_002C5A30(void)
{
    GAUGE_SET(g_00799A38, 1.0f, 0x40, 0x40, 0, 0);
}

/* 0x002C5A60, 0x2C bytes. */
void func_002C5A60(void)
{
    GAUGE_SET(g_00799A50, 1.0f, 0x40, 0x40, 0, 0);
}

/* 0x002C5A90, 0x28 bytes, matching. */
void func_002C5A90(u8 *g)
{
    GAUGE_SET(g, 1.0f, 0x80, 0x80, 0x80, 1);
}

/* 0x002C5AC0, 0x1C bytes, matching. */
void func_002C5AC0(float f, u8 *g, int a, int b, int c, int d)
{
    GAUGE_SET(g, f, a, b, c, d);
}

/* 0x002C5C10, 0x50 bytes. Officer `o`'s face. */
u8 func_002C5C10(int o)
{
    return g_005BA6A0[func_002F27D0(o) * 0x2C + 6];
}
