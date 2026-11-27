/*
 * troop_misc.c - small battle helpers around the troop AI (parts of 0x001F0520-0x001F50BC):
 * difficulty values, the troop chance table, the duel state (0x007315E0), view distances and
 * the stage units' seen bits. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 g_00669D60[];
extern u8 g_004296E0[][0x48];            /* troop chance table */
extern u8 *g_00731628;
extern int g_007315E0[];                 /* the duel state (+0x38: its 4 actors) */
extern u8 g_0073164C;
extern u8 *g_0045D410;                   /* (small data) the stage units' seen bits */
extern int (*g_00429410[0x1D])(void);

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define SPAD_INT(a) (*(int *)(a))
#define SPAD_PTR(a) (*(u8 **)(a))

void func_00348D20(void);
int func_002F67B0(int v);
void func_003DCF20(void);
void func_003DD0C0(void);
void func_003DD1D0(void);
void func_00102EC0(u8 *p);
void func_001F3150(int a, int b, int c);
void func_001F3FC0(float d, int a, int b, int c);
int func_00196A10(void);
void func_001185B0(void *p, int n);

/* 0x001F0520, 0x1C bytes, matching. */
void func_001F0520(void)
{
    func_00348D20();
}

/* 0x001F0570, 0x34 bytes. */
int func_001F0570(u32 k)
{
    if (k < 0x1D)
        return g_00429410[k]();
    return 8;
}

/* 0x001F0C50, 0x80 bytes. A chance by the flags `f` (2: 40%, 4: 20%, 8: 10%). */
int func_001F0C50(u32 f)
{
    u32 v;

    if ((f & 2) != 0)
        v = 0x28;
    else if ((f & 4) != 0)
        v = 0x14;
    else if ((f & 8) != 0)
        v = 10;
    else
        return 0;
    return RANDOM() % 100 < v;
}

/* 0x001F1060, 0x68 bytes, matching. */
int func_001F1060(u8 k)
{
    switch (k) {
    case 0:
        return 4;
    case 1:
        return 4;
    case 2:
        return 8;
    case 3:
        return 4;
    case 4:
        return 2;
    case 5:
        return 4;
    default:
        return 4;
    }
}

int func_001F15E0(u8 *o);

/* 0x001F1300, 0x58 bytes. */
int func_001F1300(u8 *o)
{
    int v = func_001F15E0(o), r = 2;

    if (v != 2) {
        if (v == 1)
            r = -2;
        else
            r = 0;
    }
    return r;
}

/* 0x001F1360, 0x10 bytes, matching. */
float func_001F1360(void)
{
    return 500.0f;
}

/* 0x001F15B0, 0x24 bytes, matching. */
u8 *func_001F15B0(int a, int b)
{
    return g_004296E0[a] + b * 8;
}

/* 0x001F15E0, 0x58 bytes. A player troop's level (by the player it follows). */
int func_001F15E0(u8 *o)
{
    int v;

    if ((*(u32 *)(o + 0xB8) & 4) == 0) {
        if ((*(u32 *)(o + 0xB8) & 8) == 0)
            return 0;
        v = *(int *)(g_00669D60 + 0xD0);
    } else {
        v = *(int *)(g_00669D60 + 0x88);
    }
    return func_002F67B0(v);
}

/* 0x001F1770, 0x1C bytes, matching. */
void func_001F1770(void)
{
    func_003DCF20();
}

/* 0x001F1790, 0x1C bytes, matching. */
void func_001F1790(void)
{
    func_003DD0C0();
}

/* 0x001F17B0, 0x1C bytes, matching. */
void func_001F17B0(void)
{
    func_003DD1D0();
}

/* 0x001F1E90, 0x28 bytes. */
void func_001F1E90(void)
{
    func_00102EC0(g_00731628);
    g_00731628 = 0;
}

/* 0x001F27D0, 0x34 bytes. Marks duel actor `k`. */
void func_001F27D0(int k)
{
    if (k < 4)
        g_0073164C |= 1 << (k & 0x1F);
}

/* 0x001F2810, 0x68 bytes. Marks the duel slots of actor `p`. */
void func_001F2810(int p)
{
    int k;

    if (p == 0)
        return;
    for (k = 0; k < 4; k++) {
        if (g_007315E0[0xE + k] == p)
            func_001F27D0(k);
    }
}

/* 0x001F29E0, 0x14 bytes, matching. */
int func_001F29E0(void)
{
    return g_007315E0[0] == 2;
}

/* 0x001F2AD0, 0x14 bytes, matching. */
int func_001F2AD0(void)
{
    return g_007315E0[0] != 5;
}

/* 0x001F3320, 0x1C bytes, matching. */
void func_001F3320(int a, int b)
{
    func_001F3150(a, b, 1);
}

/* 0x001F3340, 0x20 bytes, matching. */
void func_001F3340(int a, int b)
{
    func_001F3150(a, 0, b);
}

/* 0x001F4580, 0x24 bytes, matching. */
void func_001F4580(int a, int b)
{
    func_001F3FC0(45.0f, a, b, 0);
}

/* 0x001F45B0, 0x24 bytes, matching. */
void func_001F45B0(int a, int b)
{
    func_001F3FC0(145.0f, a, b, 3);
}

/* 0x001F4870, 0x28 bytes. */
u8 func_001F4870(u8 *p)
{
    if (p == 0)
        return 0xF;
    return p[SPAD_INT(0x70000B50) + 1];
}

/* 0x001F4FB0, 0x34 bytes. Marks bit `b` of stage unit `a`. */
void func_001F4FB0(int a, int b)
{
    u32 v = a * 2 + b;

    g_0045D410[v >> 3] |= 1 << (v & 7);
}

/* 0x001F4FF0, 0x30 bytes. */
u32 func_001F4FF0(int a, int b)
{
    u32 v = a * 2 + b;

    return g_0045D410[v >> 3] & 1 << (v & 7) & 0xFF;
}

/* 0x001F5020, 0x40 bytes. Clears them. */
void func_001F5020(void)
{
    int n = func_00196A10();

    func_001185B0(g_0045D410, ((n * 2 + 7u) >> 3) + 0xF >> 4);
}

/* 0x001F5060, 0x30 bytes, matching. */
int func_001F5060(int a, int b)
{
    return *(int *)(SPAD_PTR(0x700001DC) + b * 100 + a * 4);
}

/* 0x001F5090, 0x30 bytes, matching. */
void func_001F5090(int a, int b, int v)
{
    *(int *)(SPAD_PTR(0x700001DC) + b * 100 + a * 4) = v;
}
