/*
 * emp_menus.c - Empire mode menu pieces between 0x00398630 and 0x0039D768: the province command
 * menu (state at 0x007BA8B0: +0x08 the page, +0x0C its kind, +0x14 the selected entry, +0x1C
 * a timer, +0x20 a result, +0x24 the entries' availability), the item and gift menus (state at
 * FC2C0()[0x1AB]) and their small drawers. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern int g_007BA8B8, g_007BA8BC, g_007BA8C4, g_007BA8CC, g_007BA8D0;
extern int g_007BA8D4[];
extern short g_007BAA54[6];
extern int g_007BAA64;
extern u8 g_007BAA70[], g_0045D7E8[];
extern int g_00459B60[][2];
extern u8 *g_0043C5A8;
extern u8 g_00500764, g_00500765;
extern u16 g_0050074C;

#define PAD1_PRESSED() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074C)

int *func_002FC2C0(void);
void func_00376100(int a, int b, int c);
void func_00373B60(void);
u8 *func_0030D7D0(void);
int func_00397B00(int v);
void func_0039A880(int a);
void func_00397B10(int k);
int *func_003DB900(int k);
int func_0039A630(void);
void func_00380E80(u8 *a, int o, int x, int y);
void func_00398ED0(void);
void func_002FC560(void);
void func_003A9480(int v);
int func_00327C00(void);
void func_00373970(int k, int a, int b);
int func_00327D50(void);
int func_002F8160();
int func_002F7D90(int a, int (*fn)(), int b, int c, int d, int e);
int *func_002F7B10(void);
void func_0032D300(int a, int *list, int n);
u8 func_00328330(int k);
u8 func_00328640(int k);
int func_00389050(void);
int func_00389090(void);
void func_0039C540(int k);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_0039C490(int k);
void func_00388140(int k);
void func_00373790(int v);
int func_00374250(void);
void func_00373F60(void);
int func_00328C00(int k);
void func_0039CE50(void);
void func_00388710(void);
void func_001A7DC0(u8 *text, int a, int b);
void func_0032D3C0(u8 *a);
int func_002F9390(int f, int j);
void func_0037ED80(u8 *a, int x, int y, int f, int *v, int b, int c);

#define MENU2() ((int *)func_002FC2C0()[0x1AB])

/* 0x00398630, 0x20 bytes. Whether the current entry is available. */
int func_00398630(void)
{
    return g_007BA8D4[g_007BA8B8];
}

/* 0x00398650, 0x44 bytes. */
void func_00398650(int v)
{
    g_007BAA64 = v;
    if (v == 1 && g_007BA8BC == 1)
        func_00376100(4, 9, 0x15C);
}

/* 0x003986A0, 0x3C bytes, matching. Whether `v` is in `list`. */
int func_003986A0(int v, int *list, int n)
{
    int k;

    for (k = 0; k < n; k++) {
        if (v == list[k])
            return 1;
    }
    return 0;
}

/* 0x00398A80, 0x1C bytes, matching. */
void func_00398A80(void)
{
    func_00373B60();
}

/* 0x00398BD0, 0xC0 bytes. Draws entry `k`'s plate (dimmed when not available). */
void func_00398BD0(int x, int y, int k)
{
    int a = g_007BA8D4[k] == 0 ? 0x40 : 0x80;

    func_001ABE40(func_0030D7D0(), 0x5D, x + g_00459B60[k][0], func_00397B00(y + g_00459B60[k][1]),
                  0, 0x98, 0x14, a, 1, 0);
}

/* 0x0039A080, 0x34 bytes. */
int func_0039A080(void)
{
    if (g_007BA8C4 < 0xE || g_007BA8C4 > 0x13)
        return 0;
    return 1;
}

/* 0x0039A0C0, 0x48 bytes. */
int func_0039A0C0(void)
{
    if ((g_007BA8C4 < 1 || g_007BA8C4 > 3) && (g_007BA8C4 < 8 || g_007BA8C4 > 10))
        return 0;
    return 1;
}

/* 0x0039A110, 0x4C bytes. */
int func_0039A110(void)
{
    if ((g_007BA8C4 < 4 || g_007BA8C4 > 6) && (g_007BA8C4 < 0xB || g_007BA8C4 > 0xD))
        return 0;
    return 1;
}

/* 0x0039A540, 0x30 bytes. */
int func_0039A540(void)
{
    if (g_007BA8B8 == 0 || g_007BA8B8 == 7)
        return 1;
    return 0;
}

/* 0x0039A570, 0x34 bytes. */
int func_0039A570(void)
{
    if (g_007BA8B8 < 0xE || g_007BA8B8 > 0x13)
        return 0;
    return 1;
}

/* 0x0039A5B0, 0x78 bytes. */
int func_0039A5B0(void)
{
    int v = g_007BA8B8;

    if ((v < 1 || v > 3) && (v < 8 || v > 10) && (v < 4 || v > 6) && (v < 0xB || v > 0xD))
        return 0;
    return 1;
}

/* 0x0039AF30, 0x3C bytes. The first free slot (from 0xE; -1: none). */
int func_0039AF30(void)
{
    int k;

    for (k = 0; k < 6; k++) {
        if (g_007BAA54[k] == -1)
            return k + 0xE;
    }
    return -1;
}

/* 0x0039AF70, 0x30 bytes. */
void func_0039AF70(void)
{
    func_0039A880(1);
    g_007BA8D0 = 1;
    func_00397B10(5);
}

/* 0x0039B6B0, 0x50 bytes, matching. */
void func_0039B6B0(void)
{
    int *p = func_003DB900(0xD);

    func_00380E80(func_0030D7D0(), func_0039A630(), p[0], p[1]);
}

/* 0x0039B700, 0x74 bytes. The command menu's drawing. */
void func_0039B700(void)
{
    switch (g_007BA8BC) {
    case 1:
        func_00398A80();
        /* fall through */
    case 2:
    case 3:
    case 4:
    case 5:
    case 9:
        func_00398ED0();
        break;
    case 6:
    case 7:
    case 8:
        func_00398ED0();
        func_0039B6B0();
        break;
    }
}

/* 0x0039B820, 0x70 bytes. */
void func_0039B820(void)
{
    g_007BA8CC++;
    if (g_007BA8CC > 5) {
        g_007BA8CC = 0;
        if (g_007BA8BC == 6)
            func_00397B10(7);
        else if (g_007BA8BC == 8)
            func_00397B10(3);
    }
}

/* 0x0039B890, 0x8C bytes. */
void func_0039B890(void)
{
    if ((PAD1_PRESSED() & 0x10) != 0) {
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_00397B10(8);
    }
}

/* 0x0039BA50, 8 bytes. */
u8 *func_0039BA50(void)
{
    return g_0045D7E8;
}

/* 0x0039BA60, 8 bytes, matching. */
void func_0039BA60(int *p)
{
    *p = 0;
}

/* 0x0039BB00, 0x40 bytes, matching. Leaves the command menu. */
void func_0039BB00(void)
{
    int *st = func_002FC2C0();

    func_0039BA60((int *)st[0x1A9]);
    func_002FC560();
    st[0] = 0;
    func_003A9480(0);
}

/* 0x0039BB40, 0x40 bytes. */
void func_0039BB40(void)
{
    if (*(int *)func_002FC2C0()[0x1A9] == 1)
        func_0039B700();
}

/* 0x0039BC10, 0xC bytes, matching. */
u8 *func_0039BC10(void)
{
    return g_007BAA70;
}

/* 0x0039BC80, 0x2C bytes, matching. */
void func_0039BC80(void)
{
    func_00373970(8, (int)0x80000000, func_00327C00());
}

/* 0x0039BCB0, 0x2C bytes, matching. */
void func_0039BCB0(void)
{
    func_00373970(7, (int)0x80000000, func_00327C00());
}

/* 0x0039BCE0, 0x58 bytes, matching. Opens the list of the player force's officers. */
void func_0039BCE0(void)
{
    int n = func_002F7D90(0, func_002F8160, func_00327D50(), 0, 1, 0);

    func_0032D300(2, func_002F7B10(), n);
}

/* 0x0039BEE0, 0x64 bytes. Whether an item is held. */
int func_0039BEE0(void)
{
    int k;

    func_002FC2C0();
    for (k = 0; k < 5; k++) {
        if (func_00328330(k) < 100)
            return 1;
    }
    return 0;
}

/* 0x0039BF50, 0x64 bytes. Whether a reward item is held. */
int func_0039BF50(void)
{
    int k;

    func_002FC2C0();
    for (k = 0; k < 5; k++) {
        if (func_00328640(k) < 100)
            return 1;
    }
    return 0;
}

/* 0x0039C3E0, 0x2C bytes, matching. */
void func_0039C3E0(void)
{
    func_00373970(9, (int)0x80000000, func_00327C00());
}

/* 0x0039C630, 0x60 bytes, matching. The item menu's step 0. */
void func_0039C630(void)
{
    int *st = func_002FC2C0();
    int v = func_00389050();

    if (v == 1) {
        func_0039C540(func_00389090() + 1);
    } else if (v == 0) {
        func_002FC560();
        st[0] = 0;
    }
}

/* 0x0039C690, 0xA4 bytes. A yes (0), no (1) or nothing (2) from the pad. */
int func_0039C690(void)
{
    u16 v = PAD1_PRESSED();

    if ((v & 0x40) != 0)
        return 1;
    if ((v & 0x10) == 0)
        return 2;
    func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
    return 0;
}

/* 0x0039C740, 0x34 bytes, matching. */
void func_0039C740(void)
{
    *MENU2() = 0;
    func_0039C490(0);
    func_00388140(4);
}

/* Waits for the message box: closed goes back to the menu. */
static void box_step(void)
{
    int *m = MENU2();
    int v;

    func_00373790(1);
    v = func_00374250();
    func_00373790(0);
    if (v == 0) {
        m[2] = -1;
        func_0039C740();
        func_00373F60();
    } else if (v == 1) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_00373F60();
    }
}

/* 0x0039C780, 0x94 bytes. */
void func_0039C780(void)
{
    box_step();
}

/* 0x0039C820, 0x94 bytes. */
void func_0039C820(void)
{
    box_step();
}

/* 0x0039C960, 0x38 bytes. */
int func_0039C960(int a, int b)
{
    if (a == 0x1D)
        return b == 3 ? 0x78 : b + 0x68;
    return b + a * 4;
}

/* 0x0039C9A0, 0x38 bytes. */
int func_0039C9A0(int v)
{
    if (v == 0x1A)
        v = 0x1D;
    else if (v > 0x1A && v < 0x1E)
        v--;
    return v;
}

/* 0x0039C9E0, 0x74 bytes. The first of the four entries not yet unlocked (4: none). */
int func_0039C9E0(void)
{
    int a = func_0039C9A0(*(u16 *)((u8 *)MENU2() + 0x1C)), k;

    for (k = 0; k < 4; k++) {
        if (func_00328C00(func_0039C960(a, k)) == 0)
            return k;
    }
    return 4;
}

/* 0x0039D060, 0x1C bytes, matching. */
void func_0039D060(void)
{
    func_0039CE50();
}

/* 0x0039D590, 0x30 bytes. */
void func_0039D590(void)
{
    func_00388710();
    func_001A7DC0(g_0043C5A8, 0x80, 1);
}

/* 0x0039D5C0, 0x1C bytes, matching. */
void func_0039D5C0(void)
{
    func_00373B60();
}

/* 0x0039D5E0, 0x24 bytes, matching. */
void func_0039D5E0(void)
{
    func_0032D3C0(func_0030D7D0());
}

/* 0x0039D610, 0x94 bytes, matching. Draws force `f`'s three values. */
void func_0039D610(u8 *a, int f, int c)
{
    int v[8], j;

    for (j = 0; j < 3; j++) {
        v[j] = func_002F9390(f, j);
        v[j + 3] = 0;
    }
    func_0037ED80(a, 0x40, 0x50, f, v, 0, c);
}

/* 0x0039D6B0, 0x84 bytes, matching. */
void func_0039D6B0(int f)
{
    int v[8], j;

    for (j = 0; j < 3; j++) {
        v[j] = func_002F9390(f, j);
        v[j + 3] = 0;
    }
    func_0037ED80(func_0030D7D0(), 0x40, 0x50, f, v, 0, 0);
}

/* 0x0039D740, 0x28 bytes, matching. */
void func_0039D740(void)
{
    func_0039D6B0(MENU2()[2]);
}

/* ---- The officer list by group (FC2C0()[0x1A5]: 12 groups of up to 10 officers from +0,
 * counts at +0x1E0, the counts' flags at +0x1FC, group +0x210, line +0x214, the group chosen
 * +0x218, its step +0x220) and a voice player (parts of 0x003E74B0-0x003E7C08). ---- */

extern u8 g_007BFB3D;
extern float g_007BFB38;
extern int g_0041D680[], g_0041D710[], g_0041D740[];
extern u16 g_0050074E;

#define PAD1_REPEAT() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074E)
#define MENU5() ((u8 *)func_002FC2C0()[0x1A5])

u8 *func_00391250(void);
void func_0023AA40(void);
void func_0023AC40(void);
void func_0023AB00(int v, int a);
void func_0023A180(int v, int a, int b);
void func_00388200(int a, int k);
void func_003882C0(u32 *t);
int func_00388DA0(void);
void func_0011ED38(void *p, int v, int n);
int func_003A01A0(int o);
int func_00313CB0(int o);

/* 0x003E74B0, 0x118 bytes. Plays the current line's voice. */
void func_003E74B0(void)
{
    u8 *p = func_00391250();
    int s = -1, i = *(int *)(p + 0x94);
    int j = *(short *)(p + 0x14C) + *(short *)(p + 0x14E), v = g_0041D680[i];

    switch (*(int *)(p + 0xC)) {
    case 0:
        func_0023AA40();
        func_0023AC40();
        func_0023AD10(v * 0x100 + g_0041D710[j], 0, 0x2CDC, 0x2CDC, 0x1000);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        s = *(short *)(p + 0xF0 + j * 2) + g_0041D740[i];
        if (s != -1) {
            func_0023AC40();
            func_0023AB00(s, 1);
            func_0023A180(s, 0, 0);
        }
        break;
    }
}

/* 0x003E75D0, 0x2C bytes, matching. */
void func_003E75D0(int v)
{
    *(int *)(MENU5() + 0x220) = v;
}

/* 0x003E7600, 0xB4 bytes. Opens the group list on group `k` (or the next one with
 * officers). */
void func_003E7600(int k)
{
    u8 *m = MENU5();
    u32 t[4];
    int r = k, i;

    t[0] = *(int *)(m + 0x1FC) > 0;
    t[1] = *(int *)(m + 0x200) > 0;
    t[2] = *(int *)(m + 0x204) > 0;
    t[3] = *(int *)(m + 0x208) > 0;
    if (k < 4) {
        for (i = k; i < 4; i++) {
            if (t[i] != 0) {
                r = i;
                break;
            }
        }
    }
    func_00388200(2, r);
    func_003882C0(t);
}

/* 0x003E76C0, 0xA8 bytes. The group list's frame; whether it closed. */
int func_003E76C0(void)
{
    u8 *m = MENU5();
    int v;

    if ((g_007BFB3D & 1) == 0)
        return 0;
    v = func_00388DA0();
    if (v == 1) {
        int s = func_00389090();

        *(int *)(m + 0x214) = 0;
        *(int *)(m + 0x210) = s + 7;
        *(int *)(m + 0x218) = s + 7;
        *(int *)(m + 0x21C) = -1;
        func_003E75D0(1);
        return 0;
    }
    if (v == 0) {
        func_003E75D0(9);
        return 1;
    }
    return 0;
}

/* 0x003E7770, 0x23C bytes. The officer list's frame (up/down, wrapping with the pad). */
void func_003E7770(void)
{
    u8 *m = MENU5();
    int n = *(int *)(m + *(int *)(m + 0x210) * 4 + 0x1E0);
    u16 a = PAD1_PRESSED(), b = PAD1_REPEAT();
    int *line = (int *)(m + 0x214);

    if ((a & 0x10) != 0) {
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_003E7600(*(int *)(m + 0x218) - 7);
        *line = *(int *)(m + 0x210);
        *(int *)(m + 0x218) = -1;
        func_003E75D0(0);
    } else if ((a & 0x4000) != 0) {
        if (n > 1) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            *line = *line == n - 1 ? 0 : *line + 1;
        }
    } else if ((a & 0x1000) != 0) {
        if (n > 1) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            *line = *line == 0 ? n - 1 : *line - 1;
        }
    } else if ((b & 0x4000) != 0) {
        if (*line < n - 1) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            (*line)++;
        }
    } else if ((b & 0x1000) != 0 && *line > 0) {
        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
        (*line)--;
    }
}

/* 0x003E79B0, 8 bytes, matching. */
void func_003E79B0(void)
{
}

/* 0x003E79C0, 0x23C bytes. Sorts the officers into the 12 groups (100: none). */
void func_003E79C0(void)
{
    u8 *m = MENU5();
    int *cnt = (int *)(m + 0x1E0), o, c, j;

    func_0011ED38(m + 0x1E0, 0, 0x30);
    for (o = 0; o < 100; o++) {
        if (o != 0x13 && func_003A01A0(o) != 0 && (c = func_00313CB0(o)) < 0xC) {
            *(int *)(m + c * 0x28 + cnt[c] * 4) = o;
            cnt[c]++;
        }
    }
    for (c = 0; c < 0xC; c++) {
        for (j = cnt[c]; j < 10; j++)
            *(int *)(m + c * 0x28 + j * 4) = 100;
    }
    func_003E7600(0);
    func_003E75D0(0);
    g_007BFB38 = 1.0f;
    g_007BFB3D &= 0xFE;
}

/* 0x003E7C00, 8 bytes, matching. */
void func_003E7C00(void)
{
}
