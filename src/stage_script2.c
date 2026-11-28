/*
 * stage_script2.c - more of the battlefield's scripted objects (parts of 0x002B9D70-0x002BF9DC):
 * four object kinds sharing one set of handlers (their states at 0x007993E0, 0x00799450,
 * 0x00799480 and 0x007994B0), the 32-entry effect slot list (0x00799520), and small helpers.
 * Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_STAGE_SCRIPT2_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 g_007993E0[], g_00799450[], g_00799480[], g_007994B0[];
extern u8 g_00799520[0x20][0x20];        /* the effect slots */
extern u8 g_007994E0[], g_007993A0[], g_00796040[];
extern float g_007993C4, g_007993C8, g_007993CC;
#ifdef SW2E_PC
extern ps2ptr g_0045D5E4_a;                   /* (small data) the free effect slots */
#define g_0045D5E4 ((u8 *)PS2_PTR(g_0045D5E4_a))
#define g_0045D5E4_SET(v) (g_0045D5E4_a = PS2_ADDR(v))
#else
extern u8 *g_0045D5E4;
#define g_0045D5E4_a (*(ps2ptr *)&g_0045D5E4)
#define g_0045D5E4_SET(v) (g_0045D5E4 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0045D5D4_a;
#define g_0045D5D4 ((u8 *)PS2_PTR(g_0045D5D4_a))
#define g_0045D5D4_SET(v) (g_0045D5D4_a = PS2_ADDR(v))
#else
extern u8 *g_0045D5D4;
#define g_0045D5D4_a (*(ps2ptr *)&g_0045D5D4)
#define g_0045D5D4_SET(v) (g_0045D5D4 = (v))
#endif
extern u32 g_0045D5E0;
extern u8 g_00412290[];
extern int g_00412294;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_002BC3B0(u8 *t, int a);

/* 0x002BDFF0, 0x24 bytes, matching. */
void func_002BDFF0(int a)
{
    func_002BC3B0(g_007994B0, a);
}

/* 0x002BE020, 0x2C bytes, matching. */
void func_002BE020(int a, int b)
{
    func_002BC660(g_007994B0, (const void *)PS2_PTR(a), b);
}

/* 0x002BE050, 0x24 bytes, matching. */
void func_002BE050(int a)
{
    func_002BC680(g_007994B0, (int *)PS2_PTR(a));
}

/* 0x002BE080, 0x60 bytes. */
int func_002BE080(int a, int b)
{
    if (func_002BC770((unsigned char *)PS2_PTR(a), b, 1, 5) == 0)
        return 0;
    return func_002BC880(PS2_ADDR(g_007994B0), a, b);
}

/* 0x002BE0E0, 0x24 bytes, matching. */
void func_002BE0E0(int a)
{
    func_002BC3B0(g_00799480, a);
}

/* 0x002BE110, 0x2C bytes, matching. */
void func_002BE110(int a, int b)
{
    func_002BC660(g_00799480, (const void *)PS2_PTR(a), b);
}

/* 0x002BE140, 0x24 bytes, matching. */
void func_002BE140(int a)
{
    func_002BC680(g_00799480, (int *)PS2_PTR(a));
}

/* 0x002BE170, 0x60 bytes. */
int func_002BE170(int a, int b)
{
    if (func_002BC770((unsigned char *)PS2_PTR(a), b, 2, 6) == 0)
        return 0;
    return func_002BC880(PS2_ADDR(g_00799480), a, b);
}

/* 0x002BE1D0, 0x24 bytes, matching. */
void func_002BE1D0(int a)
{
    func_002BC3B0(g_00799450, a);
}

/* 0x002BE200, 0x2C bytes, matching. */
void func_002BE200(int a, int b)
{
    func_002BC660(g_00799450, (const void *)PS2_PTR(a), b);
}

/* 0x002BE230, 0x24 bytes, matching. */
void func_002BE230(int a)
{
    func_002BC680(g_00799450, (int *)PS2_PTR(a));
}

/* 0x002BE260, 0x60 bytes. */
int func_002BE260(int a, int b)
{
    if (func_002BC770((unsigned char *)PS2_PTR(a), b, 4, 7) == 0)
        return 0;
    return func_002BC880(PS2_ADDR(g_00799450), a, b);
}

/* 0x002BEEE0, 0x24 bytes, matching. */
void func_002BEEE0(int a)
{
    func_002BC3B0(g_007993E0, a);
}

/* 0x002BEF10, 0x2C bytes, matching. */
void func_002BEF10(int a, int b)
{
    func_002BC660(g_007993E0, (const void *)PS2_PTR(a), b);
}

/* 0x002BEF40, 0x24 bytes, matching. */
void func_002BEF40(int a)
{
    func_002BC680(g_007993E0, (int *)PS2_PTR(a));
}

/* 0x002BEF70, 0x60 bytes. */
int func_002BEF70(int a, int b)
{
    if (func_002BC770((unsigned char *)PS2_PTR(a), b, 11, 9) == 0)
        return 0;
    return func_002BC880(PS2_ADDR(g_007993E0), a, b);
}

/* 0x002B9D70, 0x44 bytes. */
void func_002B9D70(int t)
{
    func_00375C20(0, t, 0x4A, (int)PS2_ADDR(g_00412290), 7);
    func_00376100(g_00412294, -1, -1);
}

/* 0x002B9DC0, 0x80 bytes. A random value between `a` and `b`. */
float func_002B9DC0(float a, float b)
{
    u32 r = RANDOM();

    return a + (b - a) * (float)r / 65535.0f;
}

/* 0x002BAF70, 0x20 bytes, matching. */
void func_002BAF70(float f, u8 *p)
{
    float *v = (float *)(PS2_LOADP(u8 *, (p + 0x110)) + 0x24);

    *v = *(float *)(p + 0x120) * f + *v + 0.0f;
}

/* 0x002BBD00, 0x8C bytes. Counts the stage units passing `fn`. */
int func_002BBD00(int a, int (*fn)(u32 k, int b), int b)
{
    u32 n = func_00196A10(), k;
    int c = 0;

    for (k = 0; k < n; k++) {
        if (fn(k, b) != 0)
            c++;
    }
    return c;
}

/* 0x002BBD90, 0x1C bytes, matching. */
void func_002BBD90(int k)
{
    func_0027F160(k, 3);
}

/* 0x002BBE70, 0x40 bytes. Chains the free effect slots. */
void func_002BBE70(void)
{
    int k;

    g_0045D5E4_SET(g_00799520[0]);
    for (k = 0; k < 0x1F; k++)
        PS2_STOREP(u8 *, g_00799520[k], g_00799520[k + 1]);
    PS2_STOREP(u8 *, g_00799520[0x1F], 0);
}

/* 0x002BBF00, 0x34 bytes, matching. Gives slot `k` back. */
void func_002BBF00(u32 k)
{
    if ((k & 0xFF) != 0xFF) {
        u8 *e = g_00799520[k & 0xFF];

        PS2_STOREP(u8 *, e, g_0045D5E4);
        g_0045D5E4_SET(e);
    }
}

/* 0x002BBF40, 0x18 bytes, matching. */
u8 *func_002BBF40(u32 k)
{
    return g_00799520[k & 0xFF];
}

/* 0x002BCBF0, 0x10 bytes, matching. */
int func_002BCBF0(u8 *p, u8 *q)
{
    p[5] = *q;
    return 1;
}

/* 0x002BD730, 0x1C bytes. */
void func_002BD730(u8 *p, u8 *q, u32 v)
{
    p[*q * 0x30 + 0x11] = v;
}

/* 0x002BD750, 0x1C bytes. */
u8 func_002BD750(u8 *p, u8 *q)
{
    return p[*q * 0x30 + 0x11];
}

/* 0x002BD820, 0x34 bytes, matching. */
void func_002BD820(const u8 *src, u32 n)
{
    g_0045D5E0 = n >> 5;
    func_00118AC0((unsigned int *)(g_007994E0), (u8 *)src, n);
}

/* 0x002BEFD0, 0x28 bytes, matching. */
void func_002BEFD0(const u8 *src)
{
    func_00118AC0((unsigned int *)(g_007993A0), (u8 *)src, 0x40);
}

/* 0x002BF000, 0x50 bytes. A rise then fall curve. */
float func_002BF000(float f)
{
    if (f < g_007993C4 / g_007993CC)
        return g_007993CC * f;
    return g_007993C4 + 0.0f - g_007993C8 * (f - g_007993C4 / g_007993CC);
}

/* 0x002BF990, 0x4C bytes. Chains the four 0xC60-byte object slots. */
void func_002BF990(void)
{
    func_00118850(g_00796040, 0x3180);
    g_0045D5D4_SET(g_00796040);
    PS2_STOREP(u8 *, g_00796040, g_00796040 + 0xC60);
    *(int *)(g_00796040 + 0x2520) = 0;
    PS2_STOREP(u8 *, (g_00796040 + 0xC60), g_00796040 + 0x18C0);
    PS2_STOREP(u8 *, (g_00796040 + 0x18C0), g_00796040 + 0x2520);
}
