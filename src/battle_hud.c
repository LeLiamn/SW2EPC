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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

int func_0035DAE0(void);
void func_003DEB40(int k);
void func_003DED10(int k);
void func_003E3270(int x, int y, int a, int b, int c, int t);
int func_0036D310(void);
int func_0036D300(void);
void func_003E3E80(int x, int y, int a, int b, int v);
int func_003F7750(int s);
int func_003F6E60(int s);
void func_003B5CC0(int a, int x, int y, int b, int c, int d);
void func_003DF2F0(int k);
void func_003DE700(void);
void func_003DE8A0(void);
void func_003DEB20(void);
void func_003DE710(void);
void func_003DE8B0(void);
void func_003DE850(void);
void func_003DEAD0(void);
void func_003A80A0(int a);
void func_003A7D90(void);
void func_00118850(void *p, int n);
int func_003E2200(int k);
int func_003E2330(int o);
void func_003E2C60(int k);
int func_003E2E00(int v);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, char *name, int line);
void func_00102960(int a);
void func_00102EC0(u8 *p);
void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_001ABEA0(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_00375C20(int a, u8 *t, int k, int b, int c);
void func_00376490(u8 *t, int k);

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
    func_00118850(g_007BF720, 0x20);
    func_00118850(g_007BF6F0, 0x24);
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
    func_00118850(g_007BF6C0, 0x30);
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

/* 0x003E3220, 0x44 bytes. */
void func_003E3220(int x, int y, int a, int b, int c, int k)
{
    func_001ABE40(g_0045D838, k + 6, x, y, a, 0x78, 0x18, b);
}

/* 0x003E3D70, 0x38 bytes, matching. */
void func_003E3D70(void)
{
    func_00375C20(0, g_0045D838, 0x23, 0, -1);
    func_00376490(g_0045D838, 0x68);
}

/* 0x003E3DB0, 0x40 bytes. */
void func_003E3DB0(int x, int y, int a)
{
    func_001ABE40(g_0045D838, 0x24, x, y, a, 0x40, 0x28, 0x80);
}

/* 0x003E3DF0, 0x40 bytes. */
void func_003E3DF0(int x, int y, int a)
{
    func_001ABE40(g_0045D838, 0x25, x, y, a, 0x40, 0x28, 0x80);
}

/* 0x003E4140, 0x58 bytes. */
void func_003E4140(int x, int y, int a)
{
    func_001ABEA0(g_0045D838, 0x34, x, y, a, 0x50, 0x10, 0);
}

/* 0x003E4220, 0x58 bytes. */
void func_003E4220(int x, int y, int a)
{
    func_001ABEA0(g_0045D838, 0x3A, x, y, a, 0x60, 0x10, 0);
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
