/*
 * battle_hud.c - pieces of the battle screen's overlay (parts of 0x003DEB30-0x003E44FC): each
 * piece has an init and a free hook and a drawer for one screen (0) or the two halves (1, 2) in
 * two-player mode; the battle timer, the tactics gauges, the officer markers lists (0x007BF6C0,
 * 0x007BF6F0, 0x007BF720) and the overlay textures. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_BATTLE_HUD_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern u8 g_00669D60[];
extern int g_007BF680;
extern short g_007BF69E;
extern u16 g_007BF6A0;
extern u8 g_007BF6A4[];
extern u8 g_007BF6C0[2][0x18];
extern int g_007BF6F0[9];
extern int g_007BF720[2][4];
extern u8 *g_0045D838, *g_0045D83C, *g_0045D840;   /* (small data) the overlay textures */
extern char g_0045C5A0[];                /* the allocations' source name */

void func_003DEB40(int k);
void func_003DED10(int k);
void func_003E3270(int x, int y, int a, int b, int c, u32 t);
void func_003E3E80(int x, int y, int a, int b, int v);
void func_003B5CC0(int a, int x, int y, int b, int c, int d);
void func_003DF2F0(int k);
int func_003E2200(int k);
int func_003E2330(int o);
int func_003E2E00(int v);

/* 0x003DEB30, 0x8 bytes, matching. */
void func_003DEB30(void)
{
}

/* 0x003DEC40, 0x1C bytes, matching. */
void func_003DEC40(void)
{
    func_003DEB40(0);
}

/* 0x003DEC60, 0x1C bytes, matching. */
void func_003DEC60(void)
{
    func_003DEB40(1);
}

/* 0x003DEC80, 0x1C bytes, matching. */
void func_003DEC80(void)
{
    func_003DEB40(2);
}

/* 0x003DECA0, 0x44 bytes. One screen, or the two halves. */
void func_003DECA0(void)
{
    if (func_0035DAE0() == 0) {
        func_003DEC40();
    } else {
        func_003DEC60();
        func_003DEC80();
    }
}

/* 0x003DECF0, 0x8 bytes, matching. */
void func_003DECF0(void)
{
}

/* 0x003DED00, 0x8 bytes, matching. */
void func_003DED00(void)
{
}

/* 0x003DEE10, 0x1C bytes, matching. */
void func_003DEE10(void)
{
    func_003DED10(0);
}

/* 0x003DEE30, 0x1C bytes, matching. */
void func_003DEE30(void)
{
    func_003DED10(1);
}

/* 0x003DEE50, 0x1C bytes, matching. */
void func_003DEE50(void)
{
    func_003DED10(2);
}

/* 0x003DEE70, 0x44 bytes. One screen, or the two halves. */
void func_003DEE70(void)
{
    if (func_0035DAE0() == 0) {
        func_003DEE10();
    } else {
        func_003DEE30();
        func_003DEE50();
    }
}

/* 0x003DEEC0, 0x8 bytes, matching. */
void func_003DEEC0(void)
{
}

/* 0x003DEED0, 0x8 bytes, matching. */
void func_003DEED0(void)
{
}

/* 0x003DEEE0, 0x44 bytes, matching. The battle timer (the time left). */
void func_003DEEE0(int x, int y)
{
    int t = *(int *)(g_00669D60 + 0x240) - *(int *)(g_00669D60 + 0x23C);

    if (t < 0)
        t = 0;
    func_003E3270(x, y, 0, 0x80, 2, t);
}

/* 0x003DEF30, 0x20 bytes, matching. */
void func_003DEF30(void)
{
    func_003DEEE0(0x168, 0x28);
}

/* 0x003DEF50, 0x20 bytes, matching. */
void func_003DEF50(void)
{
    func_003DEEE0(0x168, 0x28);
}

/* 0x003DEF70, 0x20 bytes, matching. */
void func_003DEF70(void)
{
    func_003DEEE0(0x168, 0xE8);
}

/* 0x003DEF90, 0x20 bytes, matching. */
void func_003DEF90(void)
{
    func_003DEEE0(0x188, 0x18);
}

/* 0x003DEFB0, 0x64 bytes. */
void func_003DEFB0(void)
{
    if (func_0036D310() == 0) {
        if (func_0035DAE0() == 0) {
            func_003DEF30();
        } else {
            func_003DEF50();
            func_003DEF70();
        }
    } else {
        func_003DEF90();
    }
}

/* 0x003DF020, 0x8 bytes, matching. */
void func_003DF020(void)
{
}

/* 0x003DF030, 0x8 bytes, matching. */
void func_003DF030(void)
{
}

/* 0x003DF040, 0x24 bytes, matching. */
void func_003DF040(int x, int y, int v)
{
    func_003E3E80(x, y, 0, 2, v);
}

/* 0x003DF070, 0x44 bytes, matching. */
void func_003DF070(void)
{
    func_003DF040(0x141, 0x10, func_003F7750(0));
    func_003DF040(0x1DD, 0x10, func_003F7750(1));
}

/* 0x003DF0C0, 0x44 bytes, matching. */
void func_003DF0C0(void)
{
    func_003DF040(0x141, 0x10, func_003F7750(0));
    func_003DF040(0x1DD, 0x10, func_003F7750(1));
}

/* 0x003DF110, 0x44 bytes, matching. */
void func_003DF110(void)
{
    func_003DF040(0x141, 0xD0, func_003F7750(0));
    func_003DF040(0x1DD, 0xD0, func_003F7750(1));
}

/* 0x003DF160, 0x44 bytes. One screen, or the two halves. */
void func_003DF160(void)
{
    if (func_0035DAE0() == 0) {
        func_003DF070();
    } else {
        func_003DF0C0();
        func_003DF110();
    }
}

/* 0x003DF1B0, 0x8 bytes, matching. */
void func_003DF1B0(void)
{
}

/* 0x003DF1C0, 0x8 bytes, matching. */
void func_003DF1C0(void)
{
}

/* 0x003DF1D0, 0x50 bytes, matching. */
void func_003DF1D0(int x, int y)
{
    func_003B5CC0(func_003F6E60(0), x, y, 0, 0x80, 2);
}

/* 0x003DF220, 0x20 bytes, matching. */
void func_003DF220(void)
{
    func_003DF1D0(0x105, 0x12);
}

/* 0x003DF240, 0x20 bytes, matching. */
void func_003DF240(void)
{
    func_003DF1D0(0x105, 0x12);
}

/* 0x003DF260, 0x20 bytes, matching. */
void func_003DF260(void)
{
    func_003DF1D0(0x105, 0xD2);
}

/* 0x003DF280, 0x44 bytes. One screen, or the two halves. */
void func_003DF280(void)
{
    if (func_0035DAE0() == 0) {
        func_003DF220();
    } else {
        func_003DF240();
        func_003DF260();
    }
}

/* 0x003DF2D0, 0x8 bytes, matching. */
void func_003DF2D0(void)
{
}

/* 0x003DF2E0, 0x8 bytes, matching. */
void func_003DF2E0(void)
{
}

/* 0x003DF380, 0x1C bytes, matching. */
void func_003DF380(void)
{
    func_003DF2F0(0);
}

/* 0x003DF3A0, 0x1C bytes, matching. */
void func_003DF3A0(void)
{
    func_003DF2F0(1);
}

/* 0x003DF3C0, 0x1C bytes, matching. */
void func_003DF3C0(void)
{
    func_003DF2F0(2);
}

/* 0x003DF3E0, 0x44 bytes. One screen, or the two halves. */
void func_003DF3E0(void)
{
    if (func_0035DAE0() == 0) {
        func_003DF380();
    } else {
        func_003DF3A0();
        func_003DF3C0();
    }
}

/* 0x003DF430, 0x54 bytes, matching. Inits the pieces. */
void func_003DF430(void)
{
    func_003DE700();
    func_003DE8A0();
    func_003DEB20();
    func_003DECF0();
    func_003DEEC0();
    func_003DF020();
    func_003DF1B0();
    func_003DF2D0();
}

/* 0x003DF490, 0x54 bytes, matching. Frees them. */
void func_003DF490(void)
{
    func_003DE710();
    func_003DE8B0();
    func_003DEB30();
    func_003DED00();
    func_003DEED0();
    func_003DF030();
    func_003DF1C0();
    func_003DF2E0();
}

/* 0x003DF4F0, 0x64 bytes. Draws them. */
void func_003DF4F0(void)
{
    if (func_0036D300() != 0)
        return;
    func_003DE850();
    func_003DEAD0();
    func_003DECA0();
    func_003DEE70();
    func_003DF160();
    func_003DF280();
    func_003DEFB0();
    func_003DF3E0();
}

/* 0x003DF560, 0x1C bytes, matching. */
void func_003DF560(void)
{
    func_003DEFB0();
}

/* 0x003DF580, 0x3C bytes. */
void func_003DF580(void)
{
    if (func_0036D310() == 0)
        func_003DF4F0();
    else
        func_003DF560();
}

/* 0x003E1260, 0x34 bytes. */
void func_003E1260(void)
{
    func_003A80A0(0);
    if (g_007BF680 == 0)
        func_003A7D90();
}

/* 0x003E1790, 0x1C bytes. */
u8 func_003E1790(void)
{
    return g_007BF6A4[g_007BF69E];
}

/* 0x003E17B0, 0xC bytes. */
u16 func_003E17B0(void)
{
    return g_007BF6A0;
}

/* 0x003E17C0, 0x34 bytes, matching. */
void func_003E17C0(void)
{
    func_00118850((unsigned char *)(g_007BF720), 0x20);
    func_00118850((unsigned char *)(g_007BF6F0), 0x24);
}

/* 0x003E18F0, 0x38 bytes. */
void func_003E18F0(int p)
{
    u32 k;

    for (k = 0; k < 9; k++) {
        if (g_007BF6F0[k] == p)
            g_007BF6F0[k] = 0;
    }
}

/* 0x003E1F60, 0x20 bytes, matching. */
int func_003E1F60(int a, int b)
{
    return g_007BF720[a][b];
}

/* 0x003E1F80, 0x78 bytes. */
int func_003E1F80(int v)
{
    int a;
    u32 b;

    for (a = 0; a < 2; a++) {
        for (b = 0; b < 3; b++) {
            if (func_003E1F60(a, b) == v)
                return 1;
        }
    }
    return 0;
}

/* 0x003E2000, 0x18 bytes, matching. */
int func_003E2000(int a)
{
    return g_007BF720[a][3];
}

/* 0x003E2390, 0x28 bytes, matching. */
int func_003E2390(u8 *p)
{
    if (p == 0)
        return 0x169;
    return func_003E2200(*(int *)(p + 0x118));
}

/* 0x003E23C0, 0x20 bytes, matching. */
int func_003E23C0(int o)
{
    return func_003E2330(o) + 0x6C0;
}

/* 0x003E2770, 0x24 bytes, matching. */
void func_003E2770(void)
{
    func_00118850((unsigned char *)(g_007BF6C0), 0x30);
}

/* 0x003E2D90, 0x28 bytes, matching. */
int func_003E2D90(int a, int b)
{
    return ((int *)g_007BF6C0[a])[b];
}

/* 0x003E2D30, 0x58 bytes, matching. */
void func_003E2D30(int k)
{
    if (func_003E2D90(k, 0) != 0) {
        func_003E2C60(k);
        func_00118850(g_007BF6C0[k], 0x10);
    }
}

/* 0x003E2DC0, 0x40 bytes. */
int func_003E2DC0(int v)
{
    int ok = 0;

    if (func_003E2E00(v) >= 0)
        ok = func_003E2E00(v) < 2;
    return ok;
}

/* 0x003E2E80, 0x64 bytes, matching. */
int func_003E2E80(int a)
{
    u32 b;
    int n = 0;

    for (b = 0; b < 4; b++) {
        if (func_003E2D90(a, b) != 0)
            n++;
    }
    return n;
}

/* 0x003E2EF0, 0x20 bytes, matching. */
u8 func_003E2EF0(int a)
{
    return g_007BF6C0[a][0x10];
}

/* 0x003E2F10, 0x5C bytes. */
float func_003E2F10(int v)
{
    int s = func_003E2E00(v);

    if (s < 0 || s > 1)
        return 1.0f;
    return *(float *)(g_007BF6C0[s] + 0x14);
}

/* 0x003E30D0, 0x24 bytes, matching. */
void func_003E30D0(void)
{
    func_003E17C0();
    func_003E2770();
}

/* 0x003E3100, 0x48 bytes, matching. */
void func_003E3100(void)
{
    g_0045D838 = func_001026D0(1, 0x8E, 0, 1, 0, 0, g_0045C5A0, 0x59);
    func_00102960(1);
}

/* 0x003E3150, 0x2C bytes, matching. */
void func_003E3150(void)
{
    if (g_0045D838 != 0) {
        func_00102EC0(g_0045D838);
        g_0045D838 = 0;
    }
}

/* 0x003E3220, 0x44 bytes, matching. */
void func_003E3220(int x, int y, int a, int b, int c, int k)
{
    func_001ABE40(g_0045D838, k + 6, x, y, a, 0x78, 0x18, b, c, 0);
}

/* 0x003E3D70, 0x38 bytes, matching. */
void func_003E3D70(void)
{
    func_00375C20(0, PS2_ADDR(g_0045D838), 0x23, 0, -1);
    func_00376490(PS2_ADDR(g_0045D838), 0x68);
}

/* 0x003E3DB0, 0x40 bytes, matching. */
void func_003E3DB0(int x, int y, int a, int p3)
{
    func_001ABE40(g_0045D838, 0x24, x, y, a, 0x40, 0x28, 0x80, p3, 0);
}

/* 0x003E3DF0, 0x40 bytes, matching. */
void func_003E3DF0(int x, int y, int a, int p3)
{
    func_001ABE40(g_0045D838, 0x25, x, y, a, 0x40, 0x28, 0x80, p3, 0);
}

/* 0x003E4140, 0x58 bytes, matching. */
void func_003E4140(int x, int y, int a, int p3)
{
    func_001ABEA0(g_0045D838, 0x34, x, y, a, 0x50, 0x10, 0, 0, 0x50, 0x10, 0x80, p3, 0);
}

/* 0x003E4220, 0x58 bytes, matching. */
void func_003E4220(int x, int y, int a, int p3)
{
    func_001ABEA0(g_0045D838, 0x3A, x, y, a, 0x60, 0x10, 0, 0, 0x60, 0x10, 0x80, p3, 0);
}

/* 0x003E4280, 0x48 bytes, matching. */
void func_003E4280(void)
{
    g_0045D83C = func_001026D0(1, 0x8F, 0, 1, 0, 0, g_0045C5A0, 0x36C);
    func_00102960(1);
}

/* 0x003E42D0, 0x2C bytes, matching. */
void func_003E42D0(void)
{
    if (g_0045D83C != 0) {
        func_00102EC0(g_0045D83C);
        g_0045D83C = 0;
    }
}

/* 0x003E4480, 0x48 bytes, matching. */
void func_003E4480(void)
{
    g_0045D840 = func_001026D0(1, 0x90, 0, 1, 0, 0, g_0045C5A0, 0x3D8);
    func_00102960(1);
}

/* 0x003E44D0, 0x2C bytes, matching. */
void func_003E44D0(void)
{
    if (g_0045D840 != 0) {
        func_00102EC0(g_0045D840);
        g_0045D840 = 0;
    }
}

/* More overlay pieces, the battle's difficulty values and set-up (parts of 0x003E0A50-
 * 0x003E6DEC). */

extern u8 *g_005BA6A0;
extern u8 g_006A3A30[][0xC0];
extern int g_0041D028[3], g_0041D038[3], g_0041D048[3], g_0041D350[4], g_0041D4E0[0x30];
extern int g_0041D5A0[5], g_0041D5C0[5], g_0041D5E0[5], g_0041D600[5];
extern u8 g_007BF780[];
extern u8 g_007BF74D, g_007BF76D;
extern float g_007BF748, g_007BF768;
extern char g_0045C610[], g_0045C628[];
extern int *g_0045D844;                  /* (small data) */
extern u8 *g_005BBF18, *g_005BBF1C;

int func_003E2200(int k);
u8 func_003E2EF0(int a);
int func_003E5830(void);
void func_003E5ED0(void);
void func_003E63B0(void);
int func_003E6940(void);

/* 0x003E0A50, 0x88 bytes. Marks force func_003E1790's provinces on the map. */
void func_003E0A50(void)
{
    int f = func_003E1790(), p;

    for (p = 0; p < func_0030AB90(); p++)
        func_003A80F0(p, f == func_0030AFF0(p));
}

/* 0x003E1800, 0x78 bytes. Whether battle officer `o` is a first-side commander in play. */
int func_003E1800(u8 *o)
{
    u32 f;
    u8 *u;

    if (o == 0)
        return 0;
    f = *(u32 *)(o + 0xB8);
    if ((f & 1) == 0 || (f & 2) != 0 || (f & 0x200) == 0)
        return 0;
    u = *(u8 **)(o + 0x10);
    if (u == 0)
        return 0;
    return u[0x79] == 0;
}

/* 0x003E2330, 0x5C bytes. */
int func_003E2330(int o)
{
    if (o < 0 || o > 0x19E)
        return 0x169;
    return func_003E2200(g_005BA6A0[func_002F27D0(o) * 0x2C + 6]);
}

/* 0x003E27A0, 0xC8 bytes. */
void func_003E27A0(int a, int k)
{
    u32 j;

    if (k < 0 || k >= 3)
        return;
    for (j = 0; j < 4; j++) {
        int m = func_003E2D90(a, j);

        if (m != 0) {
            if (k == 2)
                func_0024D380(0xC, m);
            else if (k == 1)
                func_0024D380(9, m);
            else if (k == 0)
                func_0024D380(8, m);
        }
    }
}

/* 0x003E2E00, 0x78 bytes. The marker list holding `v` (2: none). */
int func_003E2E00(int v)
{
    int a;
    u32 b;

    for (a = 0; a < 2; a++) {
        for (b = 0; b < 4; b++) {
            if (func_003E2D90(a, b) == v)
                return a;
        }
    }
    return 2;
}

/* 0x003E2F70, 0x6C bytes. */
int func_003E2F70(int v)
{
    int s = func_003E2E00(v);

    if (s < 0 || s > 1)
        return 0;
    return g_0041D038[func_003E2EF0(s)];
}

/* 0x003E2FE0, 0x6C bytes. */
int func_003E2FE0(int v)
{
    int s = func_003E2E00(v);

    if (s < 0 || s > 1)
        return 0;
    return g_0041D048[func_003E2EF0(s)];
}

/* 0x003E3050, 0x80 bytes. Drops battle officer `o` from the marker lists. */
void func_003E3050(u8 *o)
{
    int a;
    u32 b;

    for (a = 0; a < 2; a++) {
        for (b = 0; b < 4; b++) {
            u8 **e = (u8 **)g_007BF6C0[a] + b;

            if (*e != 0 && g_006A3A30[*(short *)(*e + 0x178)] == o)
                *e = 0;
        }
    }
}

/* 0x003E3180, 0x50 bytes, matching. */
void func_003E3180(int x, int y, int a, int b, int c, int sel)
{
    func_001ABE40(g_0045D838, sel == 0 ? 4 : 5, x, y, a, 0x10, 0x10, b, c, 0);
}

/* 0x003E31D0, 0x50 bytes, matching. */
void func_003E31D0(int x, int y, int a, int b, int c, int sel)
{
    func_001ABE40(g_0045D838, sel == 0 ? 2 : 3, x, y, a, 0x10, 0xC, b, c, 0);
}

/* 0x003E3CE0, 0x8C bytes. */
void func_003E3CE0(int x, int y, int a, int b, int s, int sel)
{
    if (s >= 0 && s < 2)
        func_001ABEA0(g_0045D838, sel == 0 ? 0x21 : 0x22, x, y, a, 0x58, 0x20, 0, s * 0x20, 0x58, 0x20, 0x80, b, 0);
}

/* 0x003E3E30, 0x50 bytes. */
void func_003E3E30(int x, int y, int a, int b, int sel)
{
    func_001ABE40(g_0045D838, sel == 0 ? 0x26 : 0x30, x, y, a, 0x10, 0xC, 0x80, b, 0);
}

/* 0x003E3E80, 0x50 bytes. */
void func_003E3E80(int x, int y, int a, int b, int sel)
{
    func_001ABE40(g_0045D838, sel == 0 ? 0x31 : 0x32, x, y, a, 0x18, 0x10, 0x80, b, 0);
}

/* 0x003E4500, 0x40 bytes, matching. */
void func_003E4500(int x, int y, int a, int p3)
{
    func_001ABE40(g_0045D840, 0xC, x, y, a, 0x60, 0x28, 0x80, p3, 0);
}

/* 0x003E4610, 0x94 bytes. */
void func_003E4610(int x, int y, int a, int b, int k)
{
    int t[4], j;

    for (j = 0; j < 4; j++)
        t[j] = g_0041D350[j];
    if (k >= 0 && k < 4)
        func_001ABE40(g_0045D840, t[k], x, y, a, 0x80, 0x18, 0x80, b, 0);
}

/* 0x003E46B0, 0x38 bytes. */
int func_003E46B0(void)
{
    return (g_007BF76D & 1) != 0 && (g_007BF74D & 1) != 0;
}

/* 0x003E46F0, 0xC bytes, matching. The gallery picture viewer. */
u8 *func_003E46F0(void)
{
    return g_007BF780;
}

/* 0x003E4700, 0x40 bytes, matching. */
void func_003E4700(void)
{
    u8 *p = func_003E46F0();

    *(int *)p = 0;
    *(short *)(p + 8) = 0xE;
    *(short *)(p + 0xA) = 3;
    *(short *)(p + 0xC) = 0;
    *(short *)(p + 0xE) = 0;
    *(int *)(p + 0x10) = 5;
}

/* 0x003E4740, 0x38 bytes, matching. */
void func_003E4740(u8 *p)
{
    if (*(u8 **)(p + 4) != 0) {
        func_00102EC0(*(u8 **)(p + 4));
        *(u8 **)(p + 4) = 0;
    }
}

/* 0x003E4780, 0x4C bytes, matching. Whether picture `k` is unlocked. */
int func_003E4780(int k)
{
    if (k < 0xE)
        return func_003A1510(k);
    if (k == 0xF)
        return func_003A1510(0xF);
    return 1;
}

/* 0x003E47D0, 0xC8 bytes, matching. Draws picture `k` (`big`: full size; a lock when not unlocked). */
void func_003E47D0(int k, int x, int y, int big)
{
    u8 *p = func_003E46F0();
    int w = 0x20, h = 0x18, t = k + 0x12;

    if (big != 0) {
        w = 0xC0;
        h = 0x90;
    }
    if (func_003E4780(k) == 0)
        t = 0x24;
    func_001ABE40(*(u8 **)(p + 4), t, x, y, 0, w, h, 0x80, 2, 0);
}

/* 0x003E4CD0, 0xAC bytes. */
void func_003E4CD0(void)
{
    u8 *p = func_003E46F0();

    func_00118850(p, 0x14);
    *(u8 **)(p + 4) = func_001026D0(1, 0x87, 0, 1, 0, 0, g_0045C610, 0x118);
    func_003E4700();
    g_007BF768 = 1.0f;
    g_007BF76D &= 0xFE;
    g_007BF748 = 1.0f;
    g_007BF74D &= 0xFE;
}

/* 0x003E4D80, 0x20 bytes, matching. */
void func_003E4D80(void)
{
    func_003E4740(g_007BF780);
}

void func_003E68A0(void);

/* 0x003E55F0, 0x1C bytes, matching. */
void func_003E55F0(void)
{
    func_003E68A0();
}

/* 0x003E57D0, 0x60 bytes. */
void func_003E57D0(void)
{
    int v = func_003623B0();

    if (v == 0x1B || v == 0x10 || v == 0xC || v == 1)
        func_0027F160(7, 3);
}

/* 0x003E58C0, 0x6C bytes. The stage's music (other modes). */
int func_003E58C0(void)
{
    int t[0x30], k;
    u32 v;

    for (k = 0; k < 0x30; k++)
        t[k] = g_0041D4E0[k];
    v = func_003623B0();
    if (v < 0x30)
        return t[v];
    return 0x4AF;
}

/* 0x003E5930, 0x3C bytes. The stage's music. */
int func_003E5930(void)
{
    if (func_0036D310() == 0)
        return func_003E5830();
    return func_003E58C0();
}

/* 0x003E5D80, 0x60 bytes. Loads the battle message file. */
void func_003E5D80(void)
{
    g_0045D844 = (int *)func_001026D0(1, 0x4AC, 0, 1, 0, 0, g_0045C628, 0x15C);
    g_005BBF18 = (u8 *)g_0045D844 + g_0045D844[0];
    g_005BBF1C = (u8 *)g_0045D844 + g_0045D844[1];
}

/* 0x003E5DE0, 0x20 bytes, matching. */
void func_003E5DE0(void)
{
    func_00102EC0((u8 *)g_0045D844);
    g_0045D844 = 0;
}

/* 0x003E68A0, 0x24 bytes, matching. */
void func_003E68A0(void)
{
    func_003E5ED0();
    func_003E63B0();
}

#define SET_I(o) (*(int *)(g_00669D60 + (o)))

/* 0x003E68D0, 0x6C bytes. The battle's enemy level (by difficulty and turn level, 19 at most). */
void func_003E68D0(void)
{
    SET_I(0x228) = (int)(((float)g_00669D60[0x21] * 6.0f + (float)SET_I(0x224) * 2.0f) * 0.6f);
    if (SET_I(0x228) > 0x13)
        SET_I(0x228) = 0x13;
}

/* 0x003E6BB0, 0x5C bytes. */
int func_003E6BB0(void)
{
    return g_0041D5A0[g_00669D60[0x21]];
}

/* 0x003E6C10, 0x44 bytes. */
void func_003E6C10(void)
{
    if (func_0036D2E0() == 0)
        SET_I(0x224) = func_003E6BB0();
    else
        SET_I(0x224) = func_003E6940();
}

/* 0x003E6C60, 0x40 bytes, matching. */
void func_003E6C60(void)
{
    *(float *)(g_00669D60 + 0x22C) = (float)(SET_I(0x228) + 0x1A) * (float)(SET_I(0x228) + 0x1A) / 1000.0f;
}

/* 0x003E6CA0, 0x2C bytes. */
void func_003E6CA0(void)
{
    SET_I(0x230) = func_00183840();
    SET_I(0x234) = SET_I(0x230);
}

/* 0x003E6CD0, 0x5C bytes. */
int func_003E6CD0(void)
{
    return g_0041D5C0[g_00669D60[0x21]];
}

/* 0x003E6D30, 0x5C bytes. */
int func_003E6D30(void)
{
    return g_0041D5E0[g_00669D60[0x21]];
}

/* 0x003E6D90, 0x5C bytes. */
int func_003E6D90(void)
{
    return g_0041D600[g_00669D60[0x21]];
}

/* HUD marks placed from position tables (parts of 0x003DE720-0x003DF37C). */

typedef struct { int v[6]; } Pos3;
typedef struct { int v[12]; } Pos6;

extern Pos3 g_0041CF40, g_0041CFF0;
extern Pos6 g_0041CF60, g_0041CF90, g_0041CFC0;
extern int g_0045D0E8[2];                /* (small data) */
extern u8 g_006AA5F4;

void func_003E3520(int x, int y, int a, int b, int c, int d, u32 k, int v);
void func_003B4F50(u32 k, int v, int x, int y, int a, int b);

/* 0x003DE720, 0xD0 bytes. */
void func_003DE720(int p)
{
    Pos3 t = g_0041CF40;
    u8 *g = func_0034ECA0(func_0035DCD0(p == 2) + 0x40);
    u32 v;

    if (g != 0 && (v = func_0034EDB0(g)) < 2)
        func_003E3180(t.v[p * 2], t.v[p * 2 + 1], 0, 0x80, 2, v);
}

/* 0x003DE8C0, 0x1A8 bytes. Up to five marks for each of the two counts. */
void func_003DE8C0(int p)
{
    Pos6 t = g_0041CF60;
    int step[2];
    u8 *g;
    u32 j, n, i;

    step[0] = g_0045D0E8[0];
    step[1] = g_0045D0E8[1];
    g = func_0034ECA0(func_0035DCD0(p == 2) + 0x40);
    if (g == 0)
        return;
    for (j = 0; j < 2; j++) {
        int *q = &t.v[p * 4 + j * 2];

        n = func_0034F140(g, j);
        if (n != 0) {
            if (n > 5)
                n = 5;
            for (i = 0; i < n; i++)
                func_003E31D0(q[0] + i * step[j], q[1], 0, 0x80, 2, j);
        }
    }
}

/* 0x003DEB40, 0x100 bytes. */
void func_003DEB40(int p)
{
    Pos6 t = g_0041CF90;
    u32 j;

    for (j = 0; j < 2; j++)
        func_003E3520(t.v[p * 4 + j * 2], t.v[p * 4 + j * 2 + 1], 0, 0x3C, 4, 2, j, func_0035F2D0(j));
}

/* 0x003DED10, 0xF8 bytes. */
void func_003DED10(int p)
{
    Pos6 t = g_0041CFC0;
    u32 j;

    for (j = 0; j < 2; j++)
        func_003B4F50(j, func_0035F340(j), t.v[p * 4 + j * 2], t.v[p * 4 + j * 2 + 1], 0, 2);
}

/* 0x003DF2F0, 0x8C bytes. */
void func_003DF2F0(int p)
{
    Pos3 t = g_0041CFF0;

    if (g_006AA5F4 < 4)
        func_003E3220(t.v[p * 2], t.v[p * 2 + 1], 0, 0x80, 2, g_006AA5F4);
}

/* Combination attacks: the units near each player (0x007BF720) and the linked groups of up to
 * four (0x007BF6C0, 0x18 bytes per player: units, count - 2, bonus), parts of 0x003E1DD0-
 * 0x003E2DEC. */

extern int g_00425F30[0x1A];
extern u8 g_00425FA0[0x1A], g_00425FC0[0x1A], g_00425FE0[0x1A];
extern float g_0041D018[3];

u32 func_003E1930(float r, u8 *u, u32 *out);
void func_003E27A0(int a, int k);

#define UNIT_OFF(u) g_006A3A30[*(short *)((u) + 0x178)]
#define LINKABLE(u) ((*(u32 *)(*(u8 **)((u) + 0x210) + 0x18) & 0x8000000) == 0)
#define COMBO_FLAG(u) ((*(u32 *)(*(u8 **)((u) + 0x210) + 0x18) & 0x400000) != 0)

/* 0x003E1DD0, 0x18C bytes. Finds the units near each player (up to three, within 300). */
void func_003E1DD0(void)
{
    int p;

    for (p = 0; p < 2; p++) {
        if (*(int *)(g_00669D60 + 0xA0 + p * 0x48) != 0) {
            u32 t[3], n, j = 0;

            func_00118850((unsigned char *)(t), 0xC);
            n = func_003E1930(300.0f, (u8 *)0x574DE0 + p * 0x630, t);
            for (; j < n; j++)
                g_007BF720[p][j] = t[j];
            for (; j < 3; j++)
                g_007BF720[p][j] = 0;
            g_007BF720[p][3] = n;
        }
    }
}

/* 0x003E2020, 0x110 bytes. Whether units `u` and `w` can link. */
int func_003E2020(u8 *u, u8 *w)
{
    return w != 0 && *(int *)(u + 0x11C) != 0 && *(int *)(w + 0x11C) != 0 && func_00271300(u) != 0
        && (u[0x19C] & 2) == 0 && (w[0x19C] & 2) == 0 && LINKABLE(u) && LINKABLE(w)
        && COMBO_FLAG(u) && COMBO_FLAG(w);
}

/* 0x003E2130, 0xC8 bytes. */
int func_003E2130(u8 *u, u8 *w)
{
    u8 **g;

    if (func_003E2020(u, w) == 0)
        return 0;
    func_003B0340(UNIT_OFF(u));
    g = (u8 **)PS2_PTR(func_003B0340(UNIT_OFF(w)));
    if ((*(u32 *)(*g + 0x80) & 0x30) == 0 && func_0033BA60(g) == 0)
        return 0;
    return 1;
}

/* 0x003E2200, 0x12C bytes. Unit kind `k`'s portrait. */
int func_003E2200(int k)
{
    if (k >= 0 && k <= 0x19)
        return g_00425F30[k];
    if (k == 0x38)
        return 0x18A;
    if (k == 0x37)
        return 0x189;
    if (k == 0x36)
        return 0x188;
    if (k == 0x30 || k == 0x21 || k == 0x1E || k == 0x35)
        return 0x187;
    if (k == 0x20 || k == 0x1D || k == 0x34)
        return 0x186;
    if (k == 0x1F || k == 0x1C || k == 0x33)
        return 0x185;
    if (k == 0x1B)
        return 0x184;
    if (k == 0x1A)
        return 0x183;
    return 0x169;
}

/* 0x003E23E0, 0x12C bytes. */
u8 func_003E23E0(u8 *u)
{
    int k = *(int *)(u + 0x118);

    if (k >= 0 && k <= 0x19)
        return g_00425FA0[k];
    if (k == 0x38 || k == 0x37 || k == 0x36 || k == 0x30 || k == 0x21 || k == 0x1E || k == 0x35
        || k == 0x20 || k == 0x1D || k == 0x34 || k == 0x1F || k == 0x1C || k == 0x33 || k == 0x1B)
        return 1;
    return 0;
}

/* 0x003E2510, 0x12C bytes. */
u8 func_003E2510(u8 *u)
{
    int k = *(int *)(u + 0x118);

    if (k >= 0 && k <= 0x19)
        return g_00425FC0[k];
    if (k == 0x38 || k == 0x37 || k == 0x36 || k == 0x1A)
        return 1;
    return 0;
}

/* 0x003E2640, 0x12C bytes. */
u8 func_003E2640(u8 *u)
{
    int k = *(int *)(u + 0x118);

    if (k >= 0 && k <= 0x19)
        return g_00425FE0[k];
    return 0;
}

/* 0x003E2870, 0x2BC bytes. Player `p`'s combination bonus (0.1 more for each kind of link). */
void func_003E2870(int p)
{
    u32 n = func_003E2E80(p), i, j;
    u8 **list = (u8 **)g_007BF6C0[p];
    int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
    float f;

    if (n < 2)
        return;
    f = g_0041D018[n - 2];
    for (i = 0; i < 4; i++) {
        if (list[i] != 0) {
            u8 **g = (u8 **)PS2_PTR(func_003B0340(UNIT_OFF(list[i])));

            if (func_0033B4E0(g) != 0)
                b5 = 1;
            for (j = i + 1; j < 4; j++) {
                if (list[j] != 0) {
                    u8 **h = (u8 **)PS2_PTR(func_003B0340(UNIT_OFF(list[j])));

                    if (func_0033BBD0(g, h) != 0)
                        b1 = 1;
                    if (func_0033BBF0(g, h) != 0)
                        b2 = 1;
                    if (func_0033BC10(g, h) != 0)
                        b4 = 1;
                    if (func_0033BCF0(g, h) != 0)
                        b3 = 1;
                }
            }
        }
    }
    if (b1 || b2 || b3) {
        f += 0.1f;
        func_003E27A0(p, 0);
    }
    if (b4) {
        f += 0.1f;
        func_003E27A0(p, 1);
    }
    if (b5) {
        f += 0.1f;
        func_003E27A0(p, 2);
    }
    *(float *)(g_007BF6C0[p] + 0x14) = f;
}

/* 0x003E2B30, 0x12C bytes. Collects player `p`'s linked units. */
void func_003E2B30(int p)
{
    u8 **list = (u8 **)g_007BF6C0[p];
    u32 n = 0, j;

    for (j = 0; j < 4; j++) {
        u8 *e = (u8 *)0x574DE0 + p * 0x630;

        if (j != 0)
            e = (u8 *)func_003E1F60(p, j - 1);
        if (e != 0 && (e[0x19C] & 2) != 0)
            list[n++] = e;
    }
    if (n < 2) {
        func_00118850((unsigned char *)(list), 0x10);
    } else {
        func_003E2870(p);
        g_007BF6C0[p][0x10] = n - 2;
    }
    func_003E1DD0();
}

/* HUD numbers and plates, the gallery list (parts of 0x003E3270-0x003E4BD8). */

extern char g_0045C5B0[];
extern int g_0041D2F0[7], g_0041D310[7], g_0041D330[8];
extern short g_007BF760, g_007BF764;
extern u8 *g_007BF770;
extern u8 g_0056CCC8[4];

int func_001204B0(char *buf, const char *fmt, ...);
void func_002C7310(int x, int y, int a, int w, int h, int b, int c);

/* 0x003E3270, 0x1F0 bytes. Draws time `t` (in 50 Hz frames) as mm:ss:cc. */
void func_003E3270(int x, int y, int a, int b, int c, u32 t)
{
    char buf[16], *s = buf;
    int i;

    func_001204B0(buf, g_0045C5B0, (int)(t / 0x32 / 0x3C), t / 0x32 % 0x3C,
                  (u32)((int)t % 0x32 * 100) / 0x32);
    for (i = 0; i < 8; i++, x += 0xC) {
        if (i == 2) {
            func_001ABEA0(g_0045D838, 1, x, y, a, 0xC, 0xC, 0, 0, 0xc, 0xb, b, c, 0);
        } else if (i == 5) {
            func_001ABEA0(g_0045D838, 1, x, y, a, 0xC, 0xC, 0xC, 0, 0xc, 0xb, b, c, 0);
        } else {
            int d = *s++ - '0';

            if (d >= 0 && d < 10)
                func_001ABEA0(g_0045D838, 0, x, y, a, 0xC, 0xC, d * 0xC, 0, 0xc, 0xc, b, c, 0);
        }
    }
}

/* 0x003E3470, 0xA8 bytes. A plain rectangle of colour (r, g, b, alpha). */
void func_003E3470(int x, int y, int a, int w, int h, u8 r, u8 g, u8 b, u8 alpha, int layer)
{
    u8 c[4];

    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    c[3] = alpha;
    c[0] = r;
    c[1] = g;
    c[2] = b;
    func_001ABB00(g_0045D838, 10, 10, x, y, a, w, h, 0, 0, 8, 0x10, (const u32 *)c, layer, 0);
}

/* 0x003E3990, 0xB4 bytes. */
void func_003E3990(u8 *o, int x, int y, int p3, int p4)
{
    int v = func_00313CB0(PS2_ADDR(o));
    int row = func_0037E1B0(PS2_ADDR(o));

    if (v > 6)
        func_001ABEA0(g_0045D838, v + 0x34, x, y, 0, 0x60, 0x18, 0, row * 0x18, 0x60, 0x18, p4, p3, 0);
}

/* 0x003E41A0, 0x7C bytes. */
void func_003E41A0(int x, int y, int a, int b, int k)
{
    if (k >= 0 && k < 3)
        func_001ABEA0(g_0045D838, 0x39, x, y, a, 0x78, 0x10, 0, k * 0x10, 0x78, 0xf, 0x80, b, 0);
}

/* 0x003E4300, 0xB8 bytes. */
void func_003E4300(int x, int y, int a, int b, int k)
{
    int t[7], j;

    for (j = 0; j < 7; j++)
        t[j] = g_0041D2F0[j];
    if (k >= 0 && k < 7)
        func_001ABE40(g_0045D83C, t[k], x, y, a, 0xA8, 0x20, 0x80, b, 0);
}

/* 0x003E43C0, 0xB8 bytes. */
void func_003E43C0(int x, int y, int a, int b, int k)
{
    int t[7], j;

    for (j = 0; j < 7; j++)
        t[j] = g_0041D310[j];
    if (k >= 0 && k < 4)
        func_001ABE40(g_0045D83C, t[k], x, y, a, 0x80, 0x18, 0x80, b, 0);
}

/* 0x003E4540, 0xC4 bytes. */
void func_003E4540(int x, int y, int a, int b, int k)
{
    int t[8], j;

    for (j = 0; j < 8; j++)
        t[j] = g_0041D330[j];
    if (k >= 0 && k < 8)
        func_001ABE40(g_0045D840, t[k], x, y, a, 0xA8, 0x20, 0x80, b, 0);
}

/* 0x003E48A0, 0x230 bytes. Draws the gallery list (six lines sliding in). */
void func_003E48A0(void)
{
    u8 *p = func_003E46F0();
    int n = *(short *)(p + *(int *)p * 2 + 8), shown = n < 7 ? n : 6;
    int first = *(short *)(p + 0xE), i, y = 0x6C;

    if (*(int *)p == 1)
        first = *(short *)(p + 0xE) + 0xE;
    if (n != 0) {
        for (i = 0; i < 6; i++, y += 0x24) {
            if (*(short *)(p + 0xE) + i < n) {
                int x = g_007BF760 - g_007BF764 * (i * 2 - (g_007BF770[0x13] - 10)) / 10, k;

                if (x > 8)
                    x = 8;
                func_002C80A0(x, y, 0, 0x108, 0x24, 0x80, 0);
                k = first + i;
                if (func_003E4780(k) != 0)
                    func_001ABE40(*(u8 **)(p + 4), k, x + 0x2C, y + 6, 0, 0xD0, 0x18, 0x80, 1, 0);
                func_003E47D0(k, x + 8, y + 6, 0);
                if (i == *(short *)(p + 0xC))
                    func_002C8500(x, y, 0, 0x108, 0x24, 0x80, 0);
            }
        }
    }
    if (func_003E46B0() != 0 && n > 5)
        func_001A3460(0x110, 100, 0, 0x10, 0xE8, 0x80, n, shown, *(short *)(p + 0xE), 1);
}

/* 0x003E4B30, 0xA8 bytes. The gallery's title. */
void func_003E4B30(void)
{
    u8 *p = func_003E46F0();
    char *s = func_003729C0(*(int *)p);
    int x;

    g_0056CCC8[1] = 0x80;
    x = g_007BF760;
    g_0056CCC8[0] = 0x80;
    g_0056CCC8[2] = 0x80;
    g_0056CCC8[3] = 0x80;
    func_002C7310(x + 0x32, 0x46, 0, 0xA4, 0x18, 0x80, 0);
    func_002C4C50(20.0f, s, x + 0x46, 0x48, 0x7C, 1, 0, 6);
}

/* The gallery viewer's frame, battle start lists, the stage's script file and the battle time
 * (parts of 0x003E4DA0-0x003E5EC4). */

extern short g_007BF740[2];
extern u8 g_007BF74C, g_007BF76C;
extern u8 *g_007BF750;
extern int g_0041D360[0x30][2];
extern u32 *g_005BA7CC;                  /* the stage's script file */
extern u32 g_005BA7D0, g_005BA7D4, g_005BA7D8;
extern u8 **g_005BA7DC, **g_005BA7E0;

u8 *func_002EE590(void);
u8 *func_002EE5A0(void);
int func_002ED160(void);
void func_003E4AD0(void);
void func_003E30D0(void);
void func_003AFD90(void);
void func_00254310(void);
void func_002582B0(void);

/* 0x003E4DA0, 0x1A0 bytes. The gallery viewer's frame. */
void func_003E4DA0(void)
{
    u8 *p = func_003E46F0();
    int b, k;

    if (p == 0)
        return;
    if (*(int *)(p + 0x10) == 5) {
        u8 *w = func_002EE590();

        g_007BF770 = w;
        b = func_001AE550(g_007BF768, w, &g_007BF760, &g_007BF76C, 0);
        g_007BF76D = (g_007BF76D & 0xFE) | (b & 1);
        if ((b & 1) != 0) {
            k = func_002ED160();
            if (k < 0x14) {
                g_007BF76D &= 0xFE;
                g_007BF770[0x13] = k;
            } else {
                g_007BF770[0x13] = 0x16;
            }
        }
    }
    func_003E4AD0();
    func_003E48A0();
    func_003E4B30();
    g_007BF750 = func_002EE5A0();
    b = func_001AE550(g_007BF748, g_007BF750, g_007BF740, &g_007BF74C, 0);
    g_007BF74D = (g_007BF74D & 0xFE) | (b & 1);
    k = *(short *)(p + 0xE) + *(short *)(p + 0xC);
    if (*(int *)p == 1)
        k += 0xE;
    func_003E47D0(k, g_007BF740[0], 0x6C, 1);
}

/* 0x003E5570, 0x78 bytes, matching. Saves the battle's results into the game. */
void func_003E5570(void)
{
    func_003DCDC0();
    func_00339760();
    func_0036FEA0();
    func_0036E130();
    func_003F7E20();
    func_003F65F0();
    func_003E30D0();
    func_0020FC40();
    if (*(int *)(g_00669D60 + 0x20C) == 1) {
        func_003DCD90();
        func_003AFD90();
    }
}

/* 0x003E5610, 0x80 bytes. */
void func_003E5610(void)
{
    if (func_0032E7B0() == 0) {
        func_0035E010();
        if (*(int *)(g_00669D60 + 0x20C) != 1) {
            func_003554D0();
            func_0035D0C0();
            func_0035D0F0();
            func_0035D120();
        }
    }
    func_003F8100();
    func_003F6630();
    func_00254310();
    func_002582B0();
}

/* 0x003E5690, 0x134 bytes. Closes every cell's open sides (two fixed on stage 0xC). */
void func_003E5690(void)
{
    u8 c[2];
    int x, y, s;

    for (y = 0; y < 0x20; y++) {
        for (x = 0; x < 0x20; x++) {
            for (s = 0; s < 4; s++) {
                c[0] = x;
                c[1] = y;
                if (func_0018F800(c, s * 2) != 0)
                    func_0018F890(c, s * 2, 2);
            }
        }
    }
    if (func_003623B0() == 0xC) {
        c[0] = 10;
        c[1] = 4;
        func_0018F890(c, 0, 3);
        c[0] = 0xB;
        c[1] = 4;
        func_0018F890(c, 4, 3);
    }
    while (func_001902A0() != 0)
        func_001902B0();
}

/* 0x003E5830, 0x90 bytes. The stage's music (Empire battles, by side). */
int func_003E5830(void)
{
    int t[0x30][2], k;
    u32 a, b;

    for (k = 0; k < 0x30; k++) {
        t[k][0] = g_0041D360[k][0];
        t[k][1] = g_0041D360[k][1];
    }
    a = func_003623B0();
    b = func_003635F0();
    if (a < 0x30 && b < 2)
        return t[a][b];
    return 0x4AD;
}

/* 0x003E5970, 0x3B0 bytes. Loads the stage's script file and indexes its events (each: flags,
 * condition count at +4, conditions from +6 then commands, 0x12 bytes each). */
void func_003E5970(void)
{
    u32 n, k;

    g_005BA7CC = (u32 *)func_001026D0(1, func_003E5930(), 0, 1, 0, 0, g_0045C628, 0x121);
    n = g_005BA7CC[0];
    g_005BA7D4 = g_005BA7CC[1];
    g_005BA7D8 = g_005BA7CC[2];
    g_005BA7D0 = n;
    if (n == 0) {
        g_005BA7E0 = 0;
        g_005BA7DC = 0;
        return;
    }
    if (n * 4 != 0) {
        g_005BA7DC = (u8 **)(func_00102DB0(0x10, n * 4));
        g_005BA7E0 = (u8 **)(func_00102DB0(0x10, n * 4));
    }
    for (k = 0; k < n; k++) {
        u8 *b = (u8 *)g_005BA7CC + g_005BA7CC[3 + k];

        b[0] &= 0xFC;
        g_005BA7DC[k] = b + 6;
        g_005BA7E0[k] = b + 6 + b[4] * 0x12;
    }
}

/* 0x003E5D20, 0x54 bytes. */
void func_003E5D20(void)
{
    if (g_005BA7DC != 0)
        func_00102EC0((u8 *)g_005BA7DC);
    if (g_005BA7E0 != 0)
        func_00102EC0((u8 *)g_005BA7E0);
    func_00102EC0((u8 *)g_005BA7CC);
}

/* 0x003E5E00, 0xC4 bytes. The battle's time limit (in 50 Hz frames). */
void func_003E5E00(void)
{
    int v;

    if ((*(u32 *)(g_00669D60 + 0x200) & 0x10) != 0) {
        *(int *)(g_00669D60 + 0x240) = 3000;
        return;
    }
    if (func_0036D310() == 0) {
        v = func_003635F0() == 0 ? 90000 : 45000;
        v += func_00363B30(2) * 30000 - func_00363B30(3) * 15000;
    } else {
        v = func_00361E90() * 3000;
    }
    if (v < 0x1771)
        v = 6000;
    *(int *)(g_00669D60 + 0x240) = v;
}

/* The enemy's level by the player's progress, battle multipliers and the player's horse model
 * (parts of 0x003E6940-0x003E74AC). */

extern float g_0041D620[6];
extern int g_0041D640[6], g_0041D660[6], g_0041D680[];
extern u8 *g_0045D848[2];                /* (small data) the horse model files */
extern u8 *g_007BFB00[6];
extern u32 g_007BF7D8;
extern u8 *g_0072C860, *g_0072C868;
extern u8 g_007BF8C0[], g_007BF7A0[], g_007BFA80[];
extern u8 g_00693703, g_0069382B, g_00693953;
extern char g_0045C6E0[];
extern u8 *g_0045D2C0;
extern int g_0045D378;

/* 0x003E6940, 0x270 bytes. The enemy level by the player's provinces and turn (0-7, halved on
 * the lowest difficulty). */
int func_003E6940(void)
{
    int a, b;
    u32 v;

    if (func_0032E7B0() != 0)
        return 0;
    a = func_0036D6D0();
    b = func_0036D5A0(1);
    v = b > 1;
    if (b > 2)
        v++;
    if (b > 3)
        v++;
    if (b > 4)
        v += 2;
    if (b > 5)
        v += 2;
    if (b > 6)
        v += 2;
    if (b > 7)
        v += 2;
    if (a > 1)
        v += 2;
    if (a > 3)
        v += 2;
    if (a > 5)
        v += 2;
    if (a > 7)
        v += 2;
    if (a > 9)
        v += 2;
    if (a > 0xC)
        v += 2;
    if (a > 0xF)
        v += 2;
    if (a > 0x12)
        v += 2;
    if (a > 0x14)
        v += 2;
    if (a > 0x17)
        v += 2;
    if (v < 3)
        v = 0;
    else if (v < 5)
        v = 1;
    else if (v < 7)
        v = 2;
    else if (v < 10)
        v = 3;
    else if (v < 0xD)
        v = 4;
    else if (v < 0x10)
        v = 5;
    else if (v < 0x13)
        v = 6;
    else
        v = 7;
    if (a < 10) {
        if (v > 4)
            v = 4;
    } else if (a < 0xF) {
        if (v > 5)
            v = 5;
    } else if (a < 0x14 && v > 6) {
        v = 6;
    }
    if (g_00669D60[0x21] == 0)
        v = (int)v >> 1;
    return v;
}

/* 0x003E6DF0, 0xC8 bytes. Officer `o`'s damage factor (half for the troop kind 1). */
float func_003E6DF0(u8 *o)
{
    int *g;
    int v;

    if (o == 0 || (*(u32 *)(o + 0xB8) & 1) == 0)
        return 1.0f;
    g = (int *)func_003B0340(o);
    if (g == 0 || (g[0x19] & 1) == 0)
        return 1.0f;
    if ((*(u32 *)(g_00669D60 + 0x200) & 0xC) == 0)
        v = g[0x13];
    else if (((u8 *)g[0])[0x79] == 0)
        v = 0x15E;
    else
        v = 0x28A;
    return v == 1 ? 0.5f : 1.0f;
}

/* 0x003E6EC0, 0xCC bytes. */
float func_003E6EC0(u8 *o)
{
    float t[6];
    int k;
    u32 s;

    for (k = 0; k < 6; k++)
        t[k] = g_0041D620[k];
    if (o == 0 || (*(u32 *)(o + 0xB8) & 1) == 0)
        return 0.125f;
    s = func_003B0430(o);
    if (s < 2)
        return t[func_0036D620(s)] * 0.125f;
    return 0.125f;
}

/* 0x003E6F90, 0xBC bytes. */
int func_003E6F90(u8 *o)
{
    int t[6], k;
    u32 s;

    for (k = 0; k < 6; k++)
        t[k] = g_0041D640[k];
    if (o == 0 || (*(u32 *)(o + 0xB8) & 1) == 0)
        return 0;
    s = func_003B0430(o);
    if (s < 2 && s == 1)
        return t[func_0036D620(1)];
    return 0;
}

/* 0x003E7050, 0xFC bytes. The second side's strength against the first's (0.7 to 2). */
float func_003E7050(void)
{
    u32 a = func_0035F2D0(0), b;
    float f;

    if (a < 2)
        a = 1;
    b = func_0035F2D0(1);
    f = (float)b / (float)a;
    if (f <= 0.7f)
        f = 0.7f;
    return f <= 2.0f ? f : 2.0f;
}

/* 0x003E7150, 0x110 bytes. Loads the horse models. */
void func_003E7150(void)
{
    int t[6], k;

    for (k = 0; k < 6; k++)
        t[k] = g_0041D660[k];
    for (k = 0; k < 2; k++)
        g_0045D848[k] = func_001026D0(1, k + 0x8DB, 0, 1, 0, 0, g_0045C6E0, 0x19);
    for (k = 0; k < 6; k++)
        g_007BFB00[k] = func_001026D0(1, t[k], 0, 1, 0, 0, g_0045C6E0, 0x1E);
    func_00102960(1);
}

/* 0x003E7260, 0xB0 bytes. */
void func_003E7260(void)
{
    int k;

    for (k = 0; k < 2; k++) {
        if (g_0045D848[k] != 0) {
            func_00102EC0(g_0045D848[k]);
            g_0045D848[k] = 0;
        }
    }
    for (k = 0; k < 6; k++) {
        if (g_007BFB00[k] != 0) {
            func_00102EC0(g_007BFB00[k]);
            g_007BFB00[k] = 0;
        }
    }
    g_007BF7D8 |= 8;
}

/* 0x003E7310, 0x120 bytes. Sets up the horse model for list `k`. */
void func_003E7310(int k)
{
    int s = func_0036B330();

    g_0072C860 = g_0045D848[s >= 3];
    g_0072C868 = g_007BFB00[s];
    *(int *)0x70000D60 = k == 0 ? 5 : 0xC;
    func_0017A920(g_007BF8C0);
    func_001CB810(g_007BF7A0, 0x30);
    func_001C8620(g_007BF7A0, s < 3 ? 0xF5 : 0xF6, g_007BFA80, 0, 0x80024);
    g_00693703 |= 0x80;
    g_0069382B |= 0x80;
    g_00693953 |= 0x80;
}

/* 0x003E7430, 0x40 bytes, matching. Draws it with its own camera. */
void func_003E7430(void)
{
    u8 *keep = g_0045D2C0;

    g_0045D378 = 0;
    g_0045D2C0 = g_007BF8C0;
    func_001CAF50(g_007BF7A0);
    g_0045D2C0 = keep;
}

/* 0x003E7470, 0x40 bytes, matching. */
void func_003E7470(int k)
{
    int v = g_0041D680[k];

    func_0023C160();
    func_0023AF50(v, 1);
}
