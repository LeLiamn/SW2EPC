/*
 * stage_script.c - the battlefield's scripted objects (gates, fires, bridges ...): their data
 * tables loaded from the stage files (0x007954A0-0x00796000), their state machines (driven by
 * the tables at 0x004122D0 and 0x004123A0) and a small free list of pending changes. Original
 * file name unknown (parts of 0x002C03C0-0x002C44EC).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_STAGE_SCRIPT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00796000[], g_00795FC0[], g_00795FA0[], g_00795790[], g_007955E0[], g_007955A0[];
extern u8 g_007954A0[];
extern float g_00795FF0, g_00795FF4, g_00795FF8, g_00795FFC;
extern u8 g_004122D0[], g_004123A0[];
extern u32 g_0045D5C8, g_0045D5C4, g_0045D5A4;
extern u8 *g_0045D5A8;                   /* (small data) the free list */
extern u8 g_0045D5B0[8];
extern int g_0045D5B4;
extern u8 g_0045D5B8[2];

int func_002C0400(void);
void func_002C0750(int a);
void func_001904E0(int (*fn)(u8 *u, int *r), int *r);
void func_002BCC00(u8 *t, int a);
int func_002BCFA0(u8 *t, int a, int b);
u8 *func_001FF140(u16 v);
u32 func_001FF100(u16 v, int k);
void func_001FF450(float f, u8 *u);

/* 0x002C03C0, 0x34 bytes, matching. */
void func_002C03C0(int a)
{
    if (func_002C0400() != 0)
        func_002C0750(a);
}

/* 0x002C1220, 0x34 bytes, matching. Loads the first object table. */
void func_002C1220(const u8 *src, u32 n)
{
    g_0045D5C8 = n >> 2;
    func_00118AC0((unsigned int *)(g_00796000), (u8 *)src, n);
}

/* 0x002C1480, 0x4C bytes, matching. */
int func_002C1480(u8 *u, int *r)
{
    if (func_00190CD0(u, r[0]) != 0)
        func_0018EF10(u, r[1]);
    return 1;
}

/* 0x002C1450, 0x2C bytes, matching. */
void func_002C1450(int a, int b)
{
    int r[2];

    r[0] = a;
    r[1] = b;
    func_001904E0(func_002C1480, r);
}

/* 0x002C14D0, 0x68 bytes. */
int func_002C14D0(int a, int b, char s)
{
    u8 v;

    if (s == 3 || s == 1)
        v = 0;
    else if (s == 2 || s == 0)
        v = 1;
    else
        v = 0;
    func_002C1690(a, (unsigned char *)PS2_PTR(b), v ^ 1);
    return 1;
}

/* 0x002C17E0, 0x20 bytes, matching. */
void func_002C17E0(void)
{
    func_002BC9B0(g_004122D0);
}

/* 0x002C1800, 0x2C bytes, matching. */
void func_002C1800(int a, int b)
{
    func_002BCAE0(g_004122D0, (unsigned char *)PS2_PTR(a), b);
}

/* 0x002C19E0, 0x20 bytes, matching. */
void func_002C19E0(u8 *o, u8 *q)
{
    func_002BCBF0(g_004122D0, q);
}

/* 0x002C1A00, 0x24 bytes, matching. */
void func_002C1A00(int a)
{
    func_002BCC00(g_004122D0, a);
}

/* 0x002C1A30, 0x2C bytes, matching. */
int func_002C1A30(int a, int b)
{
    return func_002BCFA0(g_004122D0, a, b);
}

/* 0x002C1B90, 0x20 bytes. */
void func_002C1B90(void)
{
    func_002BD730(g_004122D0, 0, 0);
}

/* 0x002C1BB0, 0x24 bytes. */
u8 func_002C1BB0(u8 *o, u8 *q)
{
    return func_002BD750(g_004122D0, q);
}

/* 0x002C1BE0, 0x24 bytes, matching. */
void func_002C1BE0(int a, int b, u8 c)
{
    func_002BD730(g_004122D0, (unsigned char *)PS2_PTR(b), c);
}

/* 0x002C1C10, 0x68 bytes. Resets the parts of stage unit `*u`. */
void func_002C1C10(u8 **u)
{
    u8 b = (*u)[0x5A];
    u8 *d = func_001FF140(*(u16 *)(*u + 0x54));
    u32 k;

    for (k = 0; k < *(u16 *)(d + 2); k++)
        func_002AF120(b + k);
}

/* 0x002C1C80, 0xC bytes. */
void func_002C1C80(void)
{
    g_0045D5C4 = 3;
}

/* 0x002C1C90, 0x28 bytes, matching. */
void func_002C1C90(const u8 *src)
{
    func_00118AC0((unsigned int *)(g_00795FC0), (u8 *)src, 0x40);
}

/* 0x002C1E80, 0x70 bytes. The area around the object's box (5000 units wider). */
void func_002C1E80(void)
{
    float a[2], b[2];

    a[0] = g_00795FF0 - 5000.0f;
    b[0] = g_00795FF8 + 5000.0f;
    b[1] = g_00795FFC + 5000.0f;
    a[1] = g_00795FF4 - 5000.0f;
    func_002BBF60(a, b);
}

/* 0x002C2080, 0x74 bytes. */
int func_002C2080(int u, char s)
{
    if (s == 1 || s == 3)
        return 1;
    if (s == 2 || s == 0)
        return func_0027E990(0x12, (unsigned char *)PS2_PTR(u), s) != 0;
    return 0;
}

/* 0x002C2130, 0x58 bytes. */
void func_002C2130(u8 *u)
{
    u8 *r = func_0027E5F0(func_001FF100(*(u16 *)(u + 0x54), 10));

    if (r != 0) {
        r[0xB]--;
        u[0x69] &= 0xF7;
        u[0x67] = 0;
    }
}

/* 0x002C2190, 0x24 bytes, matching. */
int func_002C2190(u32 k)
{
    return func_0027E5F0(k) == 0;
}

/* 0x002C21C0, 0x78 bytes. */
int func_002C21C0(u32 a, int b, char s)
{
    int f;

    if (s == 3 || s == 1)
        f = 0;
    else if (s == 2 || s == 0)
        f = 1;
    else
        f = 0;
    if (f || func_002C2190(a) == 0)
        return 1;
    return 0;
}

/* 0x002C22F0, 0x4C bytes. */
int func_002C22F0(u8 *r)
{
    if (r[0xB] == 0) {
        char c = r[10];

        if (c != -1 && c != 0)
            func_0027F160(c, 0);
        return 1;
    }
    return 0;
}

/* 0x002C2570, 0x28 bytes, matching. */
void func_002C2570(const u8 *src)
{
    func_00118AC0((unsigned int *)(g_00795FA0), (u8 *)src, 0x20);
}

/* 0x002C2A10, 0x20 bytes, matching. */
void func_002C2A10(void)
{
    func_002BC9B0(g_004123A0);
}

/* 0x002C2A30, 0x54 bytes. */
void func_002C2A30(u8 *p, int n)
{
    func_00118AC0((unsigned int *)(g_00795790), (u8 *)p, 0x10);
    func_002BCAE0(g_004123A0, (unsigned char *)PS2_PTR((int)(p + 0x10)), n - 0x10);
}

/* 0x002C2A90, 0x20 bytes, matching. */
void func_002C2A90(u8 *o, u8 *q)
{
    func_002BCBF0(g_004123A0, q);
}

/* 0x002C2AB0, 0x24 bytes, matching. */
void func_002C2AB0(int a)
{
    func_002BCC00(g_004123A0, a);
}

/* 0x002C2AE0, 0x60 bytes. */
int func_002C2AE0(int a, int b)
{
    if (func_002BCFA0(g_004123A0, a, b) == 0)
        return 0;
    return func_002C3560((unsigned char *)PS2_PTR(a), b);
}

/* 0x002C3320, 0x6C bytes. */
void func_002C3320(float f, u8 *u)
{
    u8 *r = func_0027E660(u);

    if (r == 0) {
        u[0x68] = 0;
    } else {
        float v = *(float *)(r + 4);

        if (v < 1.0f)
            f *= v;
        func_001FF450(f, u);
    }
}

/* 0x002C3390, 0x28 bytes, matching. */
void func_002C3390(const u8 *src)
{
    func_00118AC0((unsigned int *)(g_007955E0), (u8 *)src, 0x30);
}

/* 0x002C3540, 0x14 bytes, matching. */
u8 func_002C3540(int k)
{
    return g_007955E0[k];
}

/* 0x002C3620, 0x24 bytes, matching. */
void func_002C3620(const u8 *src)
{
    func_00118AC0((unsigned int *)(g_0045D5B8), (u8 *)src, 2);
}

/* 0x002C3D60, 0x2C bytes. Resets the free list. */
void func_002C3D60(void)
{
    func_00118850(g_0045D5B0, 8);
    g_0045D5A8 = g_0045D5B0;
    g_0045D5B4 = 0;
}

/* 0x002C3D90, 0x2C bytes. Takes an entry for `v` (0 when none is left). */
u8 *func_002C3D90(u8 v)
{
    u8 *p = g_0045D5A8;

    if (p == 0)
        return 0;
    p[0] = v;
    p[1] = 0;
    g_0045D5A8 = *(u8 **)(p + 4);
    return p;
}

/* 0x002C3E00, 0x20 bytes, matching. Gives entry `p` back. */
void func_002C3E00(u8 *p)
{
    if (p != 0) {
        p[0] = 0;
        *(u8 **)(p + 4) = g_0045D5A8;
        g_0045D5A8 = p;
    }
}

/* 0x002C42C0, 0x38 bytes. */
void func_002C42C0(const u8 *src, u32 n)
{
    if (n > 0x3F)
        n = 0x40;
    func_00118AC0((unsigned int *)(g_007955A0), (u8 *)src, n);
}

/* 0x002C4300, 0x7C bytes. Runs the up to 8 effects listed for entry `*p`. */
int func_002C4300(int a, u8 *p, int c)
{
    u8 b = *p;
    u32 k;

    for (k = 0; k < 8; k++) {
        char v = g_007955A0[b * 8 + k];

        if (v == -1)
            return 1;
        func_0027F160(v, c);
    }
    return 1;
}

/* 0x002C4380, 0x34 bytes, matching. */
void func_002C4380(const u8 *src, u32 n)
{
    g_0045D5A4 = n >> 5;
    func_00118AC0((unsigned int *)(g_007954A0), (u8 *)src, n);
}

/* 0x002C44E0, 0xC bytes, matching. */
u8 *func_002C44E0(void)
{
    return g_007954A0;
}
