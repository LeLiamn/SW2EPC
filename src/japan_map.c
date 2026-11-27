/*
 * japan_map.c - the Empire mode's map of Japan (state at 0x007BAC40: the view, the cursor, the
 * province colours and marks, the alliance lines) and the end-of-turn officer records it is
 * shown with. Name from the "JapanMap.c" string the code references. Written so far: parts of
 * 0x003A4E20-0x003AF914.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_007BAC40[];                  /* the map state */
extern u8 g_0045B3F0[], g_0045A940[], g_0041BFF0[];
extern int g_00459F80[][8];
extern int g_007BAE7C, g_007BAE94[];
extern int g_007BAE70, g_007BAE84, g_007BAEAC[];
extern u8 *g_0043C55C, *g_0043C5EC;

#define M32(o) (*(int *)(g_007BAC40 + (o)))
#define M8(o) (g_007BAC40[o])
#define MAP_TEX (*(u8 **)(g_007BAC40 + 0x84))

void func_003A34C0(void);
void func_003A2810(int k, int on);
void func_003A54A0(int o);
void func_003A4F40(void);
void func_003A5010(void);
void func_003A5650(int o);
u8 *func_0039FB00(int o);
void func_00118AC0(void *to, const void *from, int n);
int func_0030AB90(void);
int func_0030AFF0(int p);
void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_001ABEA0(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_003A78E0(int p, int a, int b);
void func_003A80B0(int p, int v);
void func_003A80F0(int p, int v);
void func_003A6110(int p, int v);
int func_002F8F20(int f);
u8 func_002F6850(int o);
int func_002F9990(int f);
int func_00329160(int k, int *a, int *b);
void func_003A97C0(int *list, int n, int x);
void func_003A92D0(void);
int func_0036B980(int s);
int func_003625B0(void);
void func_003ABC80(void);
void func_003AB800(void);
void func_003AC220(void);
void func_003AAD30(void);
int func_00327A60(void);
void func_0039B700(void);
void func_002B7BA0(int o);
void func_001A7DC0(u8 *text, int a, int b);
int *func_003DB900(int k);
int func_0030D7D0(void);
void func_00380E80(int a, int o, int x, int y);
void func_003986E0(int a, int b, int *c, int d);
void func_003AE8E0(int k);

/* 0x003A4E20, 0x28 bytes, matching. */
void func_003A4E20(void)
{
    func_003A34C0();
    func_003A2810(0, 1);
}

/* 0x003A4F00, 0x3C bytes, matching. */
void func_003A4F00(void)
{
    int o;

    for (o = 0; o < 0x19F; o++)
        func_003A54A0(o);
}

/* 0x003A5240, 0x50 bytes, matching. */
void func_003A5240(void)
{
    int o;

    func_003A4F00();
    func_003A4F40();
    func_003A5010();
    for (o = 400; o < 0x19F; o++)
        func_003A5650(o);
}

/* 0x003A5320, 0x38 bytes, matching. Stores officer `o`'s unlock record from `src`. */
void func_003A5320(const u8 *src, int o)
{
    func_00118AC0(func_0039FB00(o), src, 0x48);
}

/* 0x003A5360, 0x38 bytes, matching. */
void func_003A5360(u8 *dst, int o)
{
    func_00118AC0(dst, func_0039FB00(o), 0x48);
}

/* 0x003A5BA0, 0x34 bytes, matching. Keeps the view (before a zoom). */
void func_003A5BA0(void)
{
    M32(0) = M32(0xFC);
    M32(0x6C) = M32(0x110);
    M32(0x70) = M32(0x19C);
}

/* 0x003A5BE0, 0x24 bytes, matching. Gets it back. */
void func_003A5BE0(void)
{
    M32(0xFC) = M32(0);
    M32(0x19C) = M32(0x70);
}

/* 0x003A5C10, 0x2C bytes, matching. */
void func_003A5C10(void)
{
    M32(0x74) = -1;
    M32(0x78) = -1;
    M32(0x7C) = -1;
    M32(0x80) = 1;
}

/* 0x003A60F0, 0x18 bytes, matching. */
u8 func_003A60F0(u32 v)
{
    return g_0045B3F0[v & 0xFF];
}

/* 0x003A61F0, 0x80 bytes. Draws force `f`'s flag. */
void func_003A61F0(int x, int y, int f)
{
    if (f < func_0030AB90())
        func_001ABE40(MAP_TEX, f + 0xD, x, y, 0, 0x18, 0x18, 0x80);
}

/* 0x003A6270, 0x64 bytes. */
void func_003A6270(int x, int y)
{
    func_001ABEA0(MAP_TEX, 5, x, y, 0, 0x18, 0x10, 0);
}

/* 0x003A6380, 0x50 bytes. Draws the cursor. */
void func_003A6380(int x, int y)
{
    func_001ABE40(MAP_TEX, 4, x, y, 0, 0x20, 0x20, M32(0xFC));
}

/* 0x003A7BF0, 0x14 bytes, matching. */
void func_003A7BF0(int p, u8 v)
{
    M8(0x1C9 + p) = v;
}

/* 0x003A7C10, 0x58 bytes, matching. Clears all province marks. */
void func_003A7C10(void)
{
    int p;

    for (p = 0; p < 0x19; p++) {
        func_003A78E0(p, 0x1E, 0);
        func_003A80B0(p, 0);
        func_003A80F0(p, 0);
    }
}

/* 0x003A7D90, 0xC bytes, matching. */
void func_003A7D90(void)
{
    M32(0x1AC) = 0;
}

/* 0x003A7FF0, 0xC bytes, matching. */
void func_003A7FF0(int v)
{
    M32(0x198) = v;
}

/* 0x003A8000, 0x30 bytes, matching. Province `p` without an owner. */
void func_003A8000(int p)
{
    M8(0x1B0 + p) = 0x43;
    func_003A6110(p, 0x19);
}

/* 0x003A8030, 0x64 bytes, matching. Province `p` in its owner's colours. */
void func_003A8030(int p)
{
    int f = func_0030AFF0(p);

    M8(0x1B0 + p) = func_002F6850(func_002F8F20(f));
    func_003A6110(p, func_002F9990(f));
}

/* 0x003A80A0, 0xC bytes, matching. */
void func_003A80A0(int v)
{
    M32(0x188) = v;
}

/* 0x003A80B0, 0x40 bytes. */
void func_003A80B0(int p, int v)
{
    M8(0x1FB + p) = v;
    if (v == 0)
        func_003A78E0(p, M8(0x1E2 + p), 0);
}

/* 0x003A80F0, 0x40 bytes. */
void func_003A80F0(int p, int v)
{
    M8(0x214 + p) = v;
    if (v == 0)
        func_003A78E0(p, M8(0x1E2 + p), 0);
}

/* 0x003A89B0, 0x38 bytes. */
u8 func_003A89B0(int k)
{
    return g_0045A940[k + (M32(0x180) / 5) * 8];
}

/* 0x003A8AD0, 0x28 bytes, matching. */
int func_003A8AD0(int k)
{
    return g_00459F80[M32(0x108)][k * 2];
}

/* 0x003A9010, 0x20 bytes, matching. */
void func_003A9010(int v)
{
    if (M32(0x114) != v)
        M32(0x114) = v;
}

/* 0x003A9030, 0x28 bytes, matching. */
void func_003A9030(int v)
{
    M32(0x110) = v;
    M32(0xF0) = func_003A8AD0(v);
}

/* 0x003A9060, 0xC bytes, matching. */
void func_003A9060(int v)
{
    M32(0x10C) = v;
}

/* 0x003A9070, 0x60 bytes. Zooms in or out. */
void func_003A9070(int on)
{
    if (on == 0) {
        func_003A5BE0();
        M32(0x1A0) = 0;
        func_003A9010(M32(0x6C));
    } else {
        M32(0x1A0) = 1;
        func_003A5BA0();
        M32(0xFC) = 0x33;
        func_003A9010(1);
    }
}

/* 0x003A90D0, 0xC bytes, matching. */
void func_003A90D0(int v)
{
    M32(0x19C) = v;
}

/* 0x003A90E0, 0x28 bytes. Alliance line `k`. */
void func_003A90E0(int k, int a, int b)
{
    M32(0x88 + k * 8) = a;
    M32(0x8C + k * 8) = b;
}

/* 0x003A9110, 0x58 bytes, matching. */
void func_003A9110(void)
{
    int k, a, b;

    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0)
            func_003A90E0(k, a, b);
    }
}

/* 0x003A93A0, 0xC bytes, matching. */
void func_003A93A0(int v)
{
    M32(0xF8) = v;
}

/* 0x003A9440, 0x1C bytes, matching. */
void func_003A9440(void)
{
    func_003A5C10();
}

/* 0x003A9460, 0x14 bytes, matching. */
int func_003A9460(void)
{
    return M32(0x74) != -1;
}

/* 0x003A9480, 0x4C bytes. */
int func_003A9480(int v)
{
    int ch = M32(0x1A0) != v;

    if (ch) {
        func_003A9070(v);
        M32(0x19C) = v;
    }
    return ch;
}

/* 0x003A94D0, 0x3C bytes, matching. */
void func_003A94D0(void)
{
    if (M32(0x1A0) != 0) {
        func_003A5BE0();
        M32(0x1A0) = 0;
        M32(0x19C) = 0;
    }
}

/* 0x003A9610, 0x24 bytes, matching. */
void func_003A9610(void)
{
    func_003A80A0(0);
    func_003A7D90();
}

/* 0x003A99B0, 0x28 bytes, matching. */
void func_003A99B0(int v, int x)
{
    int t = v;

    func_003A97C0(&t, 1, x);
}

/* 0x003A99E0, 0x48 bytes, matching. */
void func_003A99E0(int v)
{
    func_003A92D0();
    func_003A80A0(0);
    func_003A9060(-1);
    M32(0x78) = v;
    M32(0x1AC) = 2;
}

/* 0x003A9AF0, 0xC bytes, matching. */
void func_003A9AF0(int v)
{
    M32(0x1A4) = v;
}

/* 0x003A9BA0, 0x78 bytes. */
int func_003A9BA0(void)
{
    int v = func_0036B980(0) / 10;

    if (v < 1)
        v = 0;
    else if (v >= 1000)
        v = 999;
    return -v;
}

/* 0x003AACB0, 0x74 bytes. */
int func_003AACB0(void)
{
    int v = func_003625B0();

    if (v == 4 || v == 3)
        return 2;
    if (v == 2)
        return 1;
    return 0;
}

/* 0x003AB1E0, 0x14 bytes, matching. */
u8 func_003AB1E0(int k)
{
    return g_0041BFF0[k];
}

/* 0x003AC340, 0x34 bytes, matching. */
void func_003AC340(void)
{
    func_003ABC80();
    func_003AB800();
    func_003AC220();
    func_003AAD30();
}

/* 0x003AE820, 0x1C bytes, matching. */
int func_003AE820(void)
{
    return func_00327A60();
}

/* 0x003AEC60, 0x6C bytes. */
void func_003AEC60(void)
{
    int *p = func_003DB900(0xD);

    func_00380E80(func_0030D7D0(), g_007BAE94[g_007BAE7C], p[0], p[1]);
    func_001A7DC0(g_0043C5EC, 0x80, 1);
}

/* 0x003AF1B0, 0x1C bytes, matching. */
void func_003AF1B0(void)
{
    func_0039B700();
}

/* 0x003AF1D0, 0x48 bytes. */
void func_003AF1D0(void)
{
    func_002B7BA0(g_007BAE94[g_007BAE7C]);
    func_001A7DC0(g_0043C55C, 0x80, 1);
}

/* 0x003AF8D0, 0x44 bytes. */
void func_003AF8D0(void)
{
    func_003986E0(g_007BAE70, -1, g_007BAEAC, g_007BAE84);
    func_003A9480(1);
    func_003AE8E0(6);
}

/* Province colours, alliance lines and blinking provinces (0x003A7A10-0x003A9AE4). */

int func_0030C660(int p);
int func_0030C250(int p);
int func_00327D50(void);
void func_003A9060(int v);
int func_0023A760(int k);
void func_00102960(int a);
void func_0023A7D0(int k);
void func_003A8460(int p, int a, int b);
void func_003A86F0(int p);

/* 0x003A7A10, 0xAC bytes. Every province's base colour (its owner's). */
void func_003A7A10(void)
{
    int p;

    for (p = 0; p < func_0030AB90(); p++) {
        int f;

        func_003A80B0(p, 0);
        func_003A80F0(p, 0);
        f = func_0030AFF0(p);
        if (f >= 0 && f < func_0030AB90())
            func_003A78E0(p, func_002F9990(f), 0);
    }
}

/* 0x003A7AC0, 0x94 bytes. Every province's owner flag. */
void func_003A7AC0(void)
{
    int p;

    for (p = 0; p < func_0030AB90(); p++) {
        int f = func_0030AFF0(p);

        if (f >= 0 && f < func_0030AB90())
            func_003A6110(p, func_002F9990(f));
    }
}

/* 0x003A7B60, 0x84 bytes. Every province's level mark (6 at most). */
void func_003A7B60(void)
{
    int p;

    for (p = 0; p < func_0030AB90(); p++) {
        if (func_0030C660(p) < 6)
            M8(0x1C9 + p) = func_0030C660(p);
        else
            M8(0x1C9 + p) = 6;
    }
}

/* 0x003A7DA0, 0x70 bytes. Province `p`'s colours (`all`: then every province again). */
void func_003A7DA0(int p, int all)
{
    M8(0x1B0 + p) = 0xFF;
    M8(0x1B0 + p) = func_002F6850(func_002F8F20(func_0030AFF0(p)));
    if (all != 0) {
        func_003A7A10();
        func_003A7AC0();
        func_003A7B60();
    }
}

/* 0x003A7E10, 0xBC bytes. Resets the map's provinces. */
void func_003A7E10(void)
{
    int p, v = -1;

    for (p = 0; p < 0x19; p++) {
        M8(0x1B0 + p) = 0xFF;
        M8(0x1B0 + p) = 0x43;
    }
    func_003A7A10();
    func_003A7AC0();
    func_003A7B60();
    if (func_0030AB90() > 0)
        v = 0;
    func_003A9060(v);
}

/* 0x003A9170, 0x78 bytes. Clears the alliance lines. */
void func_003A9170(void)
{
    int k;

    for (k = 0; k < 13; k++) {
        M32(0x88 + k * 8) = -1;
        M32(0x8C + k * 8) = -1;
    }
}

/* 0x003A92D0, 0xC4 bytes. Sets them back from the kept ones. */
void func_003A92D0(void)
{
    int k;

    for (k = 0; k < 13; k++) {
        M32(0x88 + k * 8) = M32(4 + k * 8);
        M32(0x8C + k * 8) = M32(8 + k * 8);
    }
}

/* 0x003A93B0, 0x84 bytes. Starts a province blink. */
void func_003A93B0(int a, int b, int c)
{
    if (func_0023A760(9) != 0) {
        func_00102960(1);
        func_0023A7D0(9);
        M32(0x78) = a;
        M32(0x74) = 0;
        M32(0x7C) = b;
        M32(0x80) = c;
        M32(0x1AC) = 1;
    }
}

/* 0x003A9640, 0xC0 bytes, matching. Whether province `p` is the player's or an ally's (func_0030C250). */
int func_003A9640(int p)
{
    int k, a, b;

    if (func_00327D50() == func_0030AFF0(p))
        return 1;
    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0
            && ((a == p && func_0030C250(b) != 0) || (b == p && func_0030C250(a) != 0)))
            return 1;
    }
    return 0;
}

/* 0x003A9700, 0xB4 bytes. Force `p`'s ally into `out` (its line drawn); whether it has one. */
int func_003A9700(int p, int *out)
{
    int k, a, b;

    func_00327D50();
    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0 && (a == p || b == p))
            break;
    }
    if (k > 0xB)
        return 0;
    *out = a == p ? b : a;
    func_003A90E0(k, a, b);
    return 1;
}

/* 0x003A9A30, 0xB8 bytes. Starts or stops province `p`'s blink. */
void func_003A9A30(int p, int on)
{
    if (p < 0 || p >= func_0030AB90())
        return;
    if (on == 0) {
        func_003A78E0(p, 0x1E, 0);
        M32(0x11C + p * 4) = 0;
    } else if (M32(0x11C + p * 4) == 0) {
        M32(0x11C + p * 4) = 1;
        func_003A8460(p, 5, 1);
        func_003A86F0(p);
    }
}
