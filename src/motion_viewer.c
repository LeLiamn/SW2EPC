/*
 * motion_viewer.c - the gallery's officer motion viewer between 0x003E8160 and 0x003E9458: the
 * officer shown (state func_00391250: kind +0x154, set +0x158, model +0x15C, weapon +0x160,
 * colour +0x164, motion set +0x168, the motion list +0x180/+0x184; wait counter +0x1C4, flags
 * +0x1C8) on player unit 1 (0x00574DE0) and the motion steps (each waits for the current motion
 * to end, at most 100 frames when it has no length). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_MOTION_VIEWER_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A3A30[][0xC0];            /* battle officers */
#ifdef SW2E_PC
extern ps2ptr g_0045D2C0_a;                   /* (small data) the camera */
#define g_0045D2C0 ((u8 *)PS2_PTR(g_0045D2C0_a))
#define g_0045D2C0_SET(v) (g_0045D2C0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2C0;
#define g_0045D2C0_a (*(ps2ptr *)&g_0045D2C0)
#define g_0045D2C0_SET(v) (g_0045D2C0 = (v))
#endif
extern u8 g_005B4BC0[];                  /* the viewer's camera */
extern u8 g_005B4DF0;
extern u32 g_0041D7D0[8];

#define UNIT1 ((u8 *)PS2_PTR(0x574DE0))
#define SP_BUF (*(int *)PS2_PTR(0x70000150))
#define WAIT(p) (*(short *)((p) + 0x1C4))
#define VFLAGS(p) ((p)[0x1C8])

void func_001BE4F0(void);
void func_00182C30(void);
void func_003E8770(void);
void func_00279240(void);

/* 0x003E8160, 0x1BC bytes. Officer kind `k`'s model. */
int func_003E8160(int k)
{
    int r;

    if (k < 0x1C) {
        if (k == 0x1A)
            return 0x68;
        if (k == 0x1B)
            k = 0x69;
        return k;
    }
    if (k == 0x1D || k == 0x21)
        return 0x26;
    if (k == 0x1C || k == 0x1E)
        return 0x2A;
    if ((u32)(k - 0x1F) < 2)
        return 0x20;
    if (k == 0x22)
        return 0x24;
    if (k == 0x23 || k == 0x24 || (u32)(k - 0x2B) < 2)
        return 0x28;
    r = 0x25;
    if (k == 0x25)
        r = 0x3A;
    else if (k == 0x26)
        r = 0x2F;
    else if (k == 0x27)
        r = 0x2C;
    else if (k == 0x28)
        r = 0x2D;
    else if (k == 0x29 || k == 0x2A || k == 0x32)
        r = 0x30;
    else if (k != 0x2D) {
        if (k == 0x2E)
            r = 0x32;
        else if (k == 0x2F)
            r = 0x33;
        else if (k == 0x30)
            r = 0x34;
        else {
            r = 0x26;
            if (k == 0x31)
                r = 0x35;
        }
    }
    return r;
}

/* 0x003E8320, 0x104 bytes. Rebuilds the officer on unit 1. */
void func_003E8320(int k, int w, u8 col, int c, int d)
{
    u8 *p = func_00391250();
    u8 f;

    if (func_003E96E0() == 0)
        return;
    if (k < 0x1C)
        col = 0;
    WAIT(p) = 0;
    p[0x1C7] = 0;
    f = VFLAGS(p);
    VFLAGS(p) = f & 0xFE;
    VFLAGS(p) = f & 0xFC;
    func_00166160(UNIT1);
    func_00165C60(UNIT1, k, c, d, 0x11, 0, col, 1);
    func_00165180(UNIT1, 1, w);
}

#define VIEW_ARGS(p) *(int *)((p) + 0x154), *(int *)((p) + 0x160), (p)[0x164], \
                     *(int *)((p) + 0x15C), *(int *)((p) + 0x168)

/* 0x003E8430, 0x40 bytes. Changes the weapon. */
void func_003E8430(int w)
{
    u8 *p = func_00391250();

    *(int *)(p + 0x160) = w;
    func_003E8320(VIEW_ARGS(p));
}

/* 0x003E8470, 0x40 bytes. Changes the colour. */
void func_003E8470(u8 c)
{
    u8 *p = func_00391250();

    p[0x164] = c;
    func_003E8320(VIEW_ARGS(p));
}

/* 0x003E84B0, 0x6C bytes. Changes the motion set. */
void func_003E84B0(int i)
{
    u8 *p = func_00391250();

    *(int *)(p + 0x168) = func_003E7EC0(*(int *)(p + 0x154), *(int *)(p + 0x158), i);
    func_003E8320(*(int *)(p + 0x154), *(int *)(p + 0x160), p[0x164], *(int *)(p + 0x15C),
                  func_003E7EC0(*(int *)(p + 0x154), *(int *)(p + 0x158), i));
}

/* 0x003E8520, 0x34 bytes. */
void func_003E8520(void)
{
    u8 *p = func_00391250();

    func_003E8320(VIEW_ARGS(p));
}

/* 0x003E8560, 0x204 bytes. Sets the viewer up. */
void func_003E8560(void)
{
    u8 *p = func_00391250();
    int *q = (int *)(p + 0x154), k;
    u8 *m;

    func_001BD7F0(*q, 0);
    if (*q < 0x1C)
        func_001BD7F0(*q, 1);
    func_0017C7D0(*(int *)(p + 0x15C));
    func_001BE030();
    for (k = 0; k < 4; k++) {
        func_0016D060(func_003E7EC0(*q, *(int *)(p + 0x158), k), (void *)PS2_PTR(-1), 0);
        if (*q > 0x21 && *q < 0x33)
            break;
    }
    func_001BC540();
    func_001BE1A0();
    func_001BE4F0();
    func_001646C0(UNIT1, 0);
    func_00165C60(UNIT1, *q, *(int *)(p + 0x15C), func_003E7EC0(*q, *(int *)(p + 0x158), 0), 0x11,
                  0, 0, 1);
    func_00165180(UNIT1, 1, 0);
    m = *(u8 **)(UNIT1 + 0x11C);
    if (m != 0) {
        int keep;

        func_00149720(m);
        keep = SP_BUF;
        UNIT1[0x19C] = (UNIT1[0x19C] & 0xFE) | 1;
        *(short *)(UNIT1 + 0x25A) = (short)(int)*(float *)(UNIT1 + 0x44);
        func_00166A00(UNIT1);
        *(int *)(m + 0x204) = 0;
        func_001688D0(UNIT1);
        SP_BUF = keep ^ 1;
        UNIT1[0x19C] = (UNIT1[0x19C] & 0xFE) | 1;
        *(int *)(m + 0x204) = 0;
        func_001688D0(UNIT1);
        SP_BUF = keep;
        func_0014D560(m, 0, 0);
    }
    func_00182C30();
    g_0045D2C0_SET(g_005B4BC0);
    g_005B4DF0 = (g_005B4DF0 & 0xFE) | 1;
    func_003E8770();
}

/* 0x003E8770, 0xA4 bytes. The viewer's camera and the officer's place. */
void func_003E8770(void)
{
    float *c = (float *)(g_005B4BC0 + 0x1C0), *u = (float *)(UNIT1 + 0x40);

    func_0017A920(g_005B4BC0);
    c[0] = 0.0f;
    c[1] = -60.0f;
    c[2] = 500.0f;
    c[3] = 1.0f;
    c[4] = 0.0f;
    c[5] = 0.0f;
    c[6] = 0.0f;
    c[7] = 1.0f;
    u[0] = -50.0f;
    u[1] = 100.0f;
    u[4] = 0.0f;
    u[5] = 0.0f;
    u[6] = 0.0f;
    u[7] = 1.0f;
}

/* 0x003E8820, 0x120 bytes. Shows officer kind `k`. */
void func_003E8820(int k)
{
    u8 *p = func_00391250(), *s = func_00391250();
    int *q = (int *)(p + 0x154), j;

    *q = k;
    *(int *)(p + 0x160) = *(short *)(s + 0x98);
    p[0x164] = (char)*(short *)(s + 0x9A);
    *(int *)(p + 0x158) = func_003E7FA0(k);
    *(int *)(p + 0x168) = func_003E7EC0(*q, *(int *)(p + 0x158), *(int *)(s + 0x24));
    *(int *)(p + 0x15C) = func_003E8160(k);
    *(int *)(p + 0x178) = 0;
    func_00279240();
    func_001BC540();
    func_001BD6D0(*q, 0);
    func_0017C6D0(*(int *)(p + 0x15C), k == 0x28, 0);
    for (j = 0; j < 4; j++) {
        func_0016CFB0(func_003E7EC0(*q, *(int *)(p + 0x158), j), 0);
        if (k > 0x21 && k < 0x33)
            break;
    }
    func_00102960(0);
}

/* The two motions' lengths (-1: none). */
#define MOTION_LEN(u, o) (*(u8 **)((u) + (o)) == 0 ? (u32)-1 : *(u16 *)(*(u8 **)((u) + (o)) + 2))

/* Whether unit `u`'s motion is over (first kind of wait). */
static int motion_over_a(u8 *p, u8 *u)
{
    u32 a = MOTION_LEN(u, 0x210), b = MOTION_LEN(u, 0x214);

    if (b + 1 < 2) {
        WAIT(p) = 0;
        return 1;
    }
    if (a == 0) {
        if (WAIT(p) < 100) {
            WAIT(p)++;
            return 0;
        }
        WAIT(p) = 0;
        return 1;
    }
    return 1;
}

/* The same, clearing the step's flag. */
static int motion_over_b(u8 *p, u8 *u)
{
    u32 a = MOTION_LEN(u, 0x210), b = MOTION_LEN(u, 0x214);

    if (b + 1 < 2) {
        VFLAGS(p) &= 0xFE;
        return 1;
    }
    if (a == 0) {
        if (WAIT(p) < 100) {
            WAIT(p)++;
            return 0;
        }
        VFLAGS(p) &= 0xFE;
        WAIT(p) = 0;
        return 1;
    }
    return 1;
}

/* 0x003E89D0, 0xCC bytes. */
void func_003E89D0(u8 *u)
{
    u8 *p = func_00391250();

    if (motion_over_a(p, u)) {
        func_001508F0(u, 1);
        WAIT(p) = 0;
    }
}

/* 0x003E8AA0, 0xD8 bytes. */
void func_003E8AA0(u8 *u)
{
    u8 *p = func_00391250();

    if (motion_over_a(p, u)) {
        func_001508F0(u, 9);
        func_00150910(u, 0x40000);
        WAIT(p) = 0;
    }
}

/* 0x003E8B80, 0xD8 bytes. */
void func_003E8B80(u8 *u)
{
    u8 *p = func_00391250();

    if (motion_over_a(p, u)) {
        func_001508F0(u, 10);
        func_00150910(u, 0x40000);
        WAIT(p) = 0;
    }
}

/* 0x003E8C60, 0x198 bytes. An attack string `k` (to its last motion, then back). */
void func_003E8C60(u8 *u, int k)
{
    u8 *p = func_00391250();
    u16 *m = *(u16 **)(u + 0x210);
    u32 a0 = m == 0 ? (u32)-1 : m[0], a1 = m == 0 ? (u32)-1 : m[1];
    u32 b = MOTION_LEN(u, 0x214);
    int done;

    if (b + 1 < 2) {
        done = 1;
        VFLAGS(p) &= 0xFE;
    } else if (a1 == 0) {
        if (WAIT(p) < 100) {
            done = 0;
            VFLAGS(p) &= 0xFD;
            WAIT(p)++;
        } else {
            done = 1;
            VFLAGS(p) &= 0xFE;
            WAIT(p) = 0;
        }
    } else {
        done = 1;
    }
    if (!done)
        return;
    if ((VFLAGS(p) & 2) == 0 && a0 == g_0041D7D0[k])
        VFLAGS(p) = (VFLAGS(p) & 0xFD) | 2;
    if ((VFLAGS(p) & 2) != 0) {
        func_001508F0(u, 2);
        WAIT(p) = 0;
    } else {
        func_001508F0(u, 1);
        WAIT(p) = 0;
    }
}

/* 0x003E8E00, 0x1E0 bytes. A jump (alternating two landings). */
void func_003E8E00(u8 *u)
{
    u8 *p = func_00391250();
    int ok;

    if (!motion_over_b(p, u))
        return;
    func_00150910(u, 0x100000);
    ok = (u[0x27C] & 2) != 0 && !(0.0f < *(float *)(u + 0x224));
    if (ok && (VFLAGS(p) & 1) == 0) {
        VFLAGS(p) = (VFLAGS(p) & 0xFE) | 1;
        if ((p[0x1C7] & 1) == 0) {
            func_001508F0(u, 1);
            WAIT(p) = 0;
        } else {
            func_001508F0(u, 2);
            WAIT(p) = 0;
        }
        p[0x1C7]++;
    } else {
        func_001508F0(u, 0x20);
        VFLAGS(p) &= 0xFE;
    }
}

/* 0x003E8FE0, 0x138 bytes. */
void func_003E8FE0(u8 *u)
{
    u8 *p = func_00391250();

    if (!motion_over_b(p, u))
        return;
    *(int *)(u + 0x13C) = 0x4000000;
    if ((VFLAGS(p) & 1) == 0 && func_00240E20(PS2_ADDR(u)) != 0) {
        VFLAGS(p) = (VFLAGS(p) & 0xFE) | 1;
        func_001508F0(u, 1);
    }
}

/* 0x003E9120, 0x128 bytes. */
void func_003E9120(u8 *u)
{
    u8 *p = func_00391250();
    short o = *(short *)(u + 0x178);

    if (motion_over_b(p, u)) {
        g_006A3A30[o][0xB0] = 1;
        func_001508F0(u, 5);
        WAIT(p) = 0;
    }
}

/* 0x003E9250, 0x128 bytes. */
void func_003E9250(u8 *u)
{
    u8 *p = func_00391250();
    short o = *(short *)(u + 0x178);

    if (motion_over_b(p, u)) {
        g_006A3A30[o][0xB0] = 3;
        func_001508F0(u, 5);
        WAIT(p) = 0;
    }
}

/* 0x003E9380, 0xD8 bytes. Runs the current step of the motion list. */
void func_003E9380(u8 *u)
{
    u8 *p = func_00391250();
    int m = *(int *)(p + *(int *)(p + 0x180) * 4 + 0x184);

    switch (m) {
    case 1:
        func_003E89D0(u);
        /* fall through */
    case 2:
        func_003E8AA0(u);
        break;
    case 3:
        func_003E8B80(u);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xB:
        func_003E8C60(u, m - 4);
        break;
    case 0xC:
        func_003E8E00(u);
        break;
    case 0xD:
        func_003E8FE0(u);
        break;
    case 0xE:
        func_003E9120(u);
        break;
    case 0xF:
        func_003E9250(u);
        break;
    }
}
