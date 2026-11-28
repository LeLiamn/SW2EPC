/*
 * custom_officer_draw.c - drawing of the officer creation screen between 0x003D3B50 and 0x003D7FF4
 * (screen state 0x003766C0, sprites of the bank 0x00376810): faces, icons, bars, the name header,
 * list pages of buttons (boxes at +0xAB0), slots, and the page frames. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_CUSTOM_OFFICER_DRAW_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern int g_0045D0E0[];                 /* (small data) */
extern int g_0041CBA0[];
extern int g_0041CBD0[0xD];
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;
extern char g_0045C480[];                /* "%s%s"? */

void func_0011ED38(void *p, int v, int n);
int func_001204B0(char *to, const char *f, ...);
void func_002C7310(int x, int y, int a, int w, int h, int c, int d);

#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))

/* 0x003D3B50, 0xB8 bytes, matching. Draws the big face of officer record `k` (0..0x42). */
void func_003D3B50(int x, int y, int a, int b, int c, int k)
{
    if (k >= 0 && k < 0x43)
        func_001ABEA0(func_00376810(), k + 0x7A, x, y, 0, b, c, 0, 0, 0x40, 0x40, 0x80, a, 0);
}

/* 0x003D3C10, 0x44 bytes. */
void func_003D3C10(void)
{
    func_00375C20(0, PS2_ADDR(func_00376810()), 0, PS2_ADDR(g_0045D0E0), 1);
    func_00376100(1, 2, -1);
}

/* 0x003D3C60, 0x64 bytes, matching. The help line of the screen's page. */
void func_003D3C60(void)
{
    u8 *s = func_003766C0();

    if (*(int *)(s + 0xB0) == 0xC)
        func_00376100(-1, -1, -1);
    else
        func_00376100(1, g_0041CBA0[*(int *)(s + 0xB0)], -1);
}

/* 0x003D3CD0, 0x170 bytes. Draws `a` then `b` in width 0x98 at size `size`, colour `col`. */
void func_003D3CD0(char *b, char *a, int x, int y, int al, int size, int col)
{
    char t[0x100];

    func_0011ED38(t, 0, 0xFF);
    func_001204B0(t, g_0045C480, a, b);
    g_0056CCC0 = (float)size;
    g_0056CCC4 = (float)size;
    FONT_COLOUR(col);
    func_00146B40((const unsigned char *)(t), x, y, 0x98, size, al, 0);
    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    FONT_COLOUR(5);
}

/* 0x003D3E40, 0x140 bytes. A stat `v` as a gauge fraction (kinds 0/1 out of 350, 2/3 out of 250);
 * -1 for an unknown kind. */
float func_003D3E40(int v, int kind)
{
    if (kind == 3) {
        if (v < 0 || v > 0xFA)
            v = 0;
        return (float)v / 250.0f;
    }
    if (kind == 2) {
        if (v < 0 || v > 0xFA)
            v = 0;
        return (float)v / 250.0f;
    }
    if (kind == 1) {
        if (v < 0 || v > 0x15E)
            v = 0;
        return (float)v / 350.0f;
    }
    if (kind == 0) {
        if (v < 0 || v > 0x15E)
            v = 0;
        return (float)v / 350.0f;
    }
    return -1.0f;
}

/* 0x003D3F80, 0xFC bytes. Draws icon `k` (0..0x8D), small or large. */
void func_003D3F80(int x, int y, int a, int b, int k, int big)
{
    if (k >= 0 && k < 0x8E) {
        if (big == 0)
            func_001ABEA0(func_00376810(), k + 0xBD, x, y, 0, 0x20, 0x20, 0, 0, 0x20, 0x20, a, b, 0);
        else
            func_001ABEA0(func_00376810(), k + 0x14B, x, y, 0, 0x40, 0x40, 0, 0, 0x40, 0x40, a, b, 0);
    }
}

/* 0x003D43D0, 0x12C bytes. A horizontal bar of width `w` (two caps and a middle). */
void func_003D43D0(int x, int y, int a, int w, int p4, int p5)
{
    func_001ABEA0(func_00376810(), 0x2C, x, y, a, 4, 4, 0, 0, 4, 4, p4, p5, 0);
    func_001ABEA0(func_00376810(), 0x2C, x + 4, y, a, w - 8, 4, 4, 0, 8, 4, p4, p5, 0);
    func_001ABEA0(func_00376810(), 0x2C, x + 4 + w - 8, y, a, 4, 4, 0xC, 0, 4, 4, p4, p5, 0);
}

/* 0x003D4770, 0x30 bytes, matching. */
void func_003D4770(u8 *g)
{
    func_002C5AC0(1.0f, g, 0x80, 0x80, 0x40, 1);
}

/* 0x003D4C70, 0xA4 bytes. Draws the new save's header (name, face). */
void func_003D4C70(int x, int y, int alpha)
{
    u8 *s = func_003766C0();

    func_002C7310(x, y, 0, 0xEC, 0x48, alpha, 1);
    func_003D3CD0((char *)s + 0x405, (char *)s + 0x40E, x + 0x11, y + 0x1D, 1, 0x14, 6);
    func_003D3B50(x + 0xA4, y + 4, 1, 0x40, 0x40, s[0x432]);
}

/* 0x003D58F0, 0x1C8 bytes. Draws the ten slot buttons of the list page. */
void func_003D58F0(void)
{
    u8 *s = func_003766C0();
    int cur = *(int *)(s + 0x30), k;
    short xy[2];
    u8 al;

    for (k = 0; k < 10; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (cur == k + *(int *)(s + 0x34))
            func_002C8500(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        else
            func_002C80A0(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        func_001ABEA0(func_00376810(), 0xF, xy[0] + 0x10, xy[1], 0, 0x30, 0x18, 0,
                      g_0041CBD0[k + *(int *)(s + 0x34)] * 0x18, 0x30, 0x18, al, 1, 0);
    }
    if (*(int *)(s + 0x9A4) == 3)
        func_001A3460(0x58, 0x48, 0, 0x10, 0xF0, al, 0xD, 10, *(int *)(s + 0x34), 1);
}

/* 0x003D5AC0, 0x194 bytes. Draws the ten colour buttons, the chosen one framed. */
void func_003D5AC0(int x, int y, int alpha)
{
    u8 *s = func_003766C0();
    int k;

    for (k = 0; k < 10; k++, x += 0x1A) {
        if (*(int *)(s + 0x38) == k && *(int *)(s + 0x9A4) == 3) {
            func_001ABEA0(func_00376810(), k + 0x10, x + 1, y + 1, 0, 0x18, 0x18, 0, 0, 0x18, 0x18, alpha & 0xFF, 1, 0);
            func_003D4600(x - 6, y - 5, 0x26, 0x24, 1, PS2_ADDR(s + 0x974));
        } else {
            func_001ABEA0(func_00376810(), 0x1A, x, y, 0, 0x18, 0x18, 0, 0, 0x18, 0x18, alpha & 0xFF, 1, 0);
            func_001ABEA0(func_00376810(), k + 0x10, x, y, 0, 0x18, 0x18, 0, 0, 0x18, 0x18, alpha & 0xFF, 1, 0);
        }
    }
}

/* ---- Page drawers: list pages of ten buttons (boxes at +0xAB0, 0x14 bytes each) and the page
 * frames (box +0x9AC holds the officer card). ---- */

typedef struct { int v[0xD]; } Ints13;
typedef struct { int v[0x10]; } Ints16;
typedef struct { int v[0x12]; } Ints18;
typedef struct { int v[0xF]; } Ints15;
extern Ints16 g_0041CC10;
extern Ints18 g_0041CC50;
extern Ints15 g_0041CCA0;

extern int g_0041CDE0[0xC], g_0041CE10[0xC], g_0041CE40[0xC];
extern char *g_0043C120[];               /* screen texts */
#ifdef SW2E_PC
extern ps2ptr g_0043C524_a;
#define g_0043C524 ((char *)PS2_PTR(g_0043C524_a))
#define g_0043C524_SET(v) (g_0043C524_a = PS2_ADDR(v))
#else
extern char *g_0043C524;
#define g_0043C524_a (*(ps2ptr *)&g_0043C524)
#define g_0043C524_SET(v) (g_0043C524 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C534_a;
#define g_0043C534 ((char *)PS2_PTR(g_0043C534_a))
#define g_0043C534_SET(v) (g_0043C534_a = PS2_ADDR(v))
#else
extern char *g_0043C534;
#define g_0043C534_a (*(ps2ptr *)&g_0043C534)
#define g_0043C534_SET(v) (g_0043C534 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C738_a;
#define g_0043C738 ((u8 *)PS2_PTR(g_0043C738_a))
#define g_0043C738_SET(v) (g_0043C738_a = PS2_ADDR(v))
#else
extern u8 *g_0043C738;
#define g_0043C738_a (*(ps2ptr *)&g_0043C738)
#define g_0043C738_SET(v) (g_0043C738 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C750_a;
#define g_0043C750 ((u8 *)PS2_PTR(g_0043C750_a))
#define g_0043C750_SET(v) (g_0043C750_a = PS2_ADDR(v))
#else
extern u8 *g_0043C750;
#define g_0043C750_a (*(ps2ptr *)&g_0043C750)
#define g_0043C750_SET(v) (g_0043C750 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C754_a;
#define g_0043C754 ((u8 *)PS2_PTR(g_0043C754_a))
#define g_0043C754_SET(v) (g_0043C754_a = PS2_ADDR(v))
#else
extern u8 *g_0043C754;
#define g_0043C754_a (*(ps2ptr *)&g_0043C754)
#define g_0043C754_SET(v) (g_0043C754 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C758_a;
#define g_0043C758 ((u8 *)PS2_PTR(g_0043C758_a))
#define g_0043C758_SET(v) (g_0043C758_a = PS2_ADDR(v))
#else
extern u8 *g_0043C758;
#define g_0043C758_a (*(ps2ptr *)&g_0043C758)
#define g_0043C758_SET(v) (g_0043C758 = (v))
#endif

void func_003D47A0(int k, int x, int y, int alpha);
void func_003D54C0(void);
void func_003D5080(int x, int y, int w, int h, int alpha);
void func_003D5F60(int x, int y, int w, int h, int alpha);
void func_003D6510(void);
void func_003D4D20(u8 *h, int k, int x, int y, int a, int w, int hh, int b);

/* 0x003D5C60, 0x2FC bytes. The weapon list page (scroll bar length by weapon kind). */
void func_003D5C60(void)
{
    u8 *s = func_003766C0();
    int kind = *(int *)(s + 0x41C), n = 0;
    const int *rows = 0;                 /* the original leaves it unset for other kinds */
    short xy[4];
    u8 al;
    int k;

    if (kind == 0x30 || kind == 0x21 || kind == 0x20 || kind == 0x1F || kind == 0x1E
        || kind == 0x1D || kind == 0x1C) {
        n = 0xF;
        rows = g_0041CCA0.v;
    } else if (kind == 0x38 || kind == 0x37 || kind == 0x36) {
        n = 0x12;
        rows = g_0041CC50.v;
    } else if (kind == 0x35 || kind == 0x34 || kind == 0x33) {
        n = 0x10;
        rows = g_0041CC10.v;
    }
    for (k = 0; k < 10; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (*(int *)(s + 0x40) == k + *(int *)(s + 0x44))
            func_002C8500(xy[0], xy[1], 0, 0x88, 0x18, al, 1);
        else
            func_002C80A0(xy[0], xy[1], 0, 0x88, 0x18, al, 1);
        func_001ABEA0(func_00376810(), 0x27, xy[0] + 0x10, xy[1], 0, 0x68, 0x18, 0,
                      rows != 0 ? rows[k + *(int *)(s + 0x44)] * 0x18 : 0, 0x68, 0x18, al, 1, 0);
    }
    if (*(int *)(s + 0x9A4) == 3)
        func_001A3460(0x90, 0x48, 0, 0x10, 0xF0, al, n, 10, *(int *)(s + 0x44), 1);
}

/* 0x003D67F0, 0x3A4 bytes. The skill list page. */
void func_003D67F0(void)
{
    u8 *s = func_003766C0();
    int kind = *(int *)(s + 0x424), n;
    short xy[4];
    u8 al;
    int k;

    const int *rows;

    if (kind == 0xF || kind == 7) {
        n = 0xC;
        rows = g_0041CE10;
    } else if (kind == 0x15 || kind == 2) {
        n = 0xC;
        rows = g_0041CDE0;
    } else {
        n = 0xB;
        rows = g_0041CE40;
    }
    for (k = 0; k < 10; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (*(int *)(s + 0x5C) == k + *(int *)(s + 0x60))
            func_002C8500(xy[0], xy[1], 0, 0x68, 0x18, al, 1);
        else
            func_002C80A0(xy[0], xy[1], 0, 0x68, 0x18, al, 1);
        func_001ABEA0(func_00376810(), 0x24, xy[0] + 0x10, xy[1], 0, 0x48, 0x18, 0,
                      rows[k + *(int *)(s + 0x60)] * 0x18, 0x48, 0x18, al, 1, 0);
    }
    if (*(int *)(s + 0x9A4) == 3)
        func_001A3460(0x70, 0x48, 0, 0x10, 0xF0, al, n, 10, *(int *)(s + 0x60), 1);
}

/* 0x003D6BA0, 0x128 bytes. A page of seven buttons. */
void func_003D6BA0(void)
{
    u8 *s = func_003766C0();
    int cur = *(int *)(s + 0x74), k;
    short xy[4];
    u8 al;

    for (k = 0; k < 7; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (cur == k)
            func_002C8500(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        else
            func_002C80A0(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        func_001ABEA0(func_00376810(), 0x23, xy[0] + 0x10, xy[1], 0, 0x30, 0x18, 0, 0, 0x30, 0x18, al, 1, 0);
    }
}

/* 0x003D6CD0, 0x128 bytes. A page of four buttons. */
void func_003D6CD0(void)
{
    u8 *s = func_003766C0();
    int cur = *(int *)(s + 0x6C), k;
    short xy[4];
    u8 al;

    for (k = 0; k < 4; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (cur == k)
            func_002C8500(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        else
            func_002C80A0(xy[0], xy[1], 0, 0x50, 0x18, al, 1);
        func_001ABEA0(func_00376810(), 0xD, xy[0] + 0x10, xy[1], 0, 0x30, 0x18, 0, 0, 0x30, 0x18, al, 1, 0);
    }
}

/* 0x003D6E00, 0x18C bytes. The face grid (0x43 faces, 14 a row), the chosen one framed. */
void func_003D6E00(void)
{
    u8 *s = func_003766C0();
    int cur = *(int *)(s + 0x7C), k, x, sx = 0, sy = 0;
    short xy[4];
    u8 al;

    for (k = 0; k < 0x43; k++) {
        if (k % 0xE == 0)
            func_001AE550(1.0f, (int *)(s + (k / 0xE) * 0x14 + 0xA4C), xy, &al, 0);
        x = xy[0] + (k % 0xE) * 0x22;
        func_001ABEA0(func_00376810(), 0x22, x, xy[1], 0, 0x20, 0x20, 0, 0, 0x20, 0x20, al, 1, 0);
        func_003D3A80(x, xy[1], 1, 0x20, 0x20, al, k);
        if (k == cur) {
            sy = xy[1];
            sx = x;
        }
    }
    if (*(int *)(s + 0x9A4) == 3)
        func_003D4600(sx - 7, sy - 7, 0x2E, 0x2E, 1, PS2_ADDR(s + 0x974));
}

/* 0x003D7400, 0x270 bytes. The two weapon slots and the OK button. */
void func_003D7400(void)
{
    u8 *s = func_003766C0();
    int cur = *(int *)(s + 0x88), k, spr, ic;
    short xy[4];
    u8 al;

    for (k = 0; k < 2; k++) {
        func_001AE550(1.0f, (int *)(s + 0x9E8 + k * 0x14), xy, &al, 0);
        if (cur == k) {
            func_002C8500(xy[0], xy[1], 0, 0xAC, 0x28, al, 1);
            spr = 0x1B;
        } else {
            func_002C80A0(xy[0], xy[1], 0, 0xAC, 0x28, al, 1);
            spr = 0x1C;
        }
        func_001ABEA0(func_00376810(), spr, xy[0] + 0x10, xy[1] + 0x10, 0, 0x5E, 0x18, 0, 0, 0x5e, 0x18, al, 1, 0);
        ic = k == 0 ? s[0x433] : s[0x434];
        func_001ABEA0(func_00376810(), 0x22, xy[0] + 0x78, xy[1] + 3, 0, 0x20, 0x20, 0, 0, 0x20, 0x20, al, 1, 0);
        func_003D3F80(xy[0] + 0x78, xy[1] + 3, al, 1, ic, 0);
    }
    func_001AE550(1.0f, (int *)(s + 0xA10), xy, &al, 0);
    if (cur == 2 && *(int *)(s + 0x9A4) == 3) {
        func_002C6040(-0x3C, xy[1] - 4, 0x100, 0x20, 1, al);
        func_003B4DE0(xy[0], xy[1], 0, al, 1, 1, 0);
    } else {
        func_003B4DE0(xy[0], xy[1], 0, al, 1, 0, 0);
    }
}

/* 0x003D7670, 0x228 bytes. The main menu page: ten entries (some greyed) and the end button. */
void func_003D7670(void)
{
    u8 *s = func_003766C0();
    int k, lit, grey;
    short xy[4];
    u8 al;

    for (k = 0; k < 0xB; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        if (*(int *)(s + 0x9C) == k && *(int *)(s + 0x9A4) == 3) {
            func_002C6040(-0x3C, xy[1] - 4, 0x100, 0x20, 1, al);
            lit = 1;
            grey = 0;
        } else {
            lit = 0;
            if (k == 1 && func_00377D50() == 0)
                grey = 1;
            else if (k == 2 && func_00377D50() == 0)
                grey = 1;
            else if (k == 3 && func_00377D80() == 0)
                grey = 1;
            else if (k == 5 && func_00377D50() == 0)
                grey = 1;
            else if (k == 6 && func_00377DF0() == 0)
                grey = 1;
            else
                grey = 0;
        }
        if (k == 10)
            func_003B4740(xy[0], xy[1], 0, 1, lit, grey);
        else
            func_003D4D20(func_00376810(), 0xE, xy[0], xy[1], 0, 0x78, 0x18, 0);
    }
}

/* 0x003D78B0, 0x154 bytes. A save slot button (with its colour mark when used). */
void func_003D78B0(int x, int y, int alpha, int k, int lit, int used, int col)
{
    if (lit == 0)
        func_002C80A0(x, y, 0, 0x78, 0x18, alpha, 1);
    else
        func_002C8500(x, y, 0, 0x78, 0x18, alpha, 1);
    func_001ABEA0(func_00376810(), 0x21, x + 0x10, y, 0, 0x40, 0x18, 0, k * 0x18, 0x40, 0x18, alpha & 0xFF, 1, 0);
    if (used != 0) {
        func_001ABEA0(func_00376810(), 0x25, x + 0x51, y, 0, 0x18, 0x18, 0, 0, 0x18, 0x18, alpha & 0xFF, 1, 0);
        func_003B3970(x + 0x51, y, 1, col);
    }
}

/* 0x003D7A10, 0xF4 bytes. The slot list page. */
void func_003D7A10(void)
{
    u8 *s = func_003766C0();
    int k, i;
    short xy[4];
    u8 al;

    for (k = 0; k < 10; k++) {
        func_001AE550(1.0f, (int *)(s + 0xAB0 + k * 0x14), xy, &al, 0);
        i = k + *(int *)(s + 0xA8);
        func_003D78B0(xy[0], xy[1], al, i, *(int *)(s + 0xA4) == i, s[i * 0x38 + 0xBC],
                      s[i * 0x38 + 0xEA]);
    }
    if (*(int *)(s + 0x9A4) == 3)
        func_001A3460(0x80, 0x48, 0, 0x10, 0xF0, al, 0xF, 10, *(int *)(s + 0xA8), 1);
}

/* 0x003D7B10, 0xC8 bytes. The help line of the chosen skill (two name the pad button). */
void func_003D7B10(void)
{
    u8 *s = func_003766C0();
    u8 k = s[0x42E];
    char t[0x40];

    if (k == 0)
        func_001204B0(t, g_0043C524, func_002C5980(0, 0));
    else if (k == 4)
        func_001204B0(t, g_0043C534, func_002C5980(0, 1));
    else
        func_001204B0(t, g_0043C120[k + 0x101]);
    func_003838B0(PS2_ADDR(t), 1);
}

/* The officer card (box +0x9AC) under a page. */
static void card(u8 *s)
{
    short xy[4];
    u8 al;

    func_001AE550(1.0f, (int *)(s + 0x9AC), xy, &al, 0);
    func_003D47A0(0xF, xy[0], xy[1], al);
}

/* 0x003D7BE0, 0x5C bytes, matching. Draws the name page. */
void func_003D7BE0(void)
{
    u8 *s = func_003766C0();
    short xy[4];
    u8 al;

    func_003D54C0();
    func_001AE550(1.0f, (int *)(s + 0x9D4), xy, &al, 0);
    func_003D5080(xy[0], xy[1], xy[2], xy[3], al);
}

/* 0x003D7C40, 0x98 bytes. Draws the list page with the colour buttons. */
void func_003D7C40(void)
{
    u8 *s = func_003766C0();
    short xy[4];
    u8 al;

    func_003D58F0();
    func_001AE550(1.0f, (int *)(s + 0xA24), xy, &al, 0);
    func_003D5AC0(xy[0], xy[1], al);
    card(s);
    func_001A7DC0((const char *)(g_0043C750), 0x80, 1);
}

/* 0x003D7CE0, 0x6C bytes. Draws the weapon page. */
void func_003D7CE0(void)
{
    u8 *s = func_003766C0();

    func_003D5C60();
    card(s);
    func_001A7DC0((const char *)(g_0043C738), 0x80, 1);
}

/* 0x003D7D50, 0x64 bytes. */
void func_003D7D50(void)
{
    u8 *s = func_003766C0();
    short xy[4];
    u8 al;

    func_001AE550(1.0f, (int *)(s + 0xA38), xy, &al, 0);
    func_003D5F60(xy[0], xy[1], xy[2], xy[3], al);
    func_001A7DC0((const char *)(g_0043C738), 0x80, 1);
}

/* 0x003D7DC0, 0x6C bytes. */
void func_003D7DC0(void)
{
    u8 *s = func_003766C0();

    func_003D6510();
    card(s);
    func_001A7DC0((const char *)(g_0043C754), 0x80, 1);
}

/* 0x003D7E30, 0x74 bytes. Draws the skill page. */
void func_003D7E30(void)
{
    u8 *s = func_003766C0();

    func_003D67F0();
    card(s);
    func_003D7B10();
    func_001A7DC0((const char *)(g_0043C738), 0x80, 1);
}

/* 0x003D7EB0, 0x6C bytes. */
void func_003D7EB0(void)
{
    u8 *s = func_003766C0();

    func_003D6BA0();
    card(s);
    func_001A7DC0((const char *)(g_0043C738), 0x80, 1);
}

/* 0x003D7F20, 0x6C bytes. */
void func_003D7F20(void)
{
    u8 *s = func_003766C0();

    func_003D6CD0();
    card(s);
    func_001A7DC0((const char *)(g_0043C738), 0x80, 1);
}

/* 0x003D7F90, 0x68 bytes. Draws the face page. */
void func_003D7F90(void)
{
    u8 *s = func_003766C0();
    short xy[4];
    u8 al;

    func_003D6E00();
    func_001AE550(1.0f, (int *)(s + 0x9C0), xy, &al, 0);
    func_003D4C70(xy[0], xy[1], al);
    func_001A7DC0((const char *)(g_0043C758), 0x80, 1);
}
