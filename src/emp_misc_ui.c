/*
 * emp_misc_ui.c - small pieces of the Empire screens and battle results between 0x003D8000 and
 * 0x003DEB28: page steps, the window table (0x58-byte records at 0x007BEC50), the two players'
 * battle results (0x9C bytes at 0x007BF540), distances between groups and places, and the
 * custom-officer slots. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_MISC_UI_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_007BEC50[][0x58];            /* the windows */
extern u8 g_007BF540[2][0x9C];           /* the players' battle results */
extern u8 *g_007BEC40;
extern int g_007BEC38, g_007BEC3C;
extern u8 *g_0045D830;                   /* (small data) */
extern int g_0045D834;
extern char g_0045C490[];                /* the allocations' source name */
extern void (*g_0041CE70[])(void), (*g_0041CEA0[])(void), (*g_0041CED0[])(void);

void func_003D6F90(void);
void func_00375F90(void);
int func_003DC2D0(int k);
void func_003DA890(void);
void func_00372C80(int a, int b);

/* 0x003D8000, 0x24 bytes, matching. */
void func_003D8000(void)
{
    func_003D7400();
    func_003D6F90();
}

/* 0x003D8230, 0x48 bytes, matching. */
void func_003D8230(void)
{
    u8 *p = func_003766C0();

    func_00375F90();
    g_0041CE70[*(int *)(p + 0xB4)]();
}

/* 0x003D8DF0, 0x4C bytes, matching. */
void func_003D8DF0(void)
{
    u8 *p = func_003766C0();

    g_0041CEA0[*(int *)(p + 0xB0)]();
    *(int *)(p + 0x9A4) = 2;
}

/* 0x003D8F40, 0x28 bytes, matching. */
void func_003D8F40(void)
{
    u8 *p = func_003766C0();

    *(int *)(p + 0x9A8) = 5;
    func_003D83C0();
}

/* 0x003D8FC0, 0x28 bytes, matching. */
void func_003D8FC0(void)
{
    u8 *p = func_003766C0();

    *(int *)(p + 0x9A8) = 5;
    func_003D83C0();
}

/* 0x003D8FF0, 0x28 bytes, matching. */
void func_003D8FF0(void)
{
    u8 *p = func_003766C0();

    *(int *)(p + 0x9A8) = 5;
    func_003D83C0();
}

/* 0x003D9020, 0x28 bytes, matching. */
void func_003D9020(void)
{
    u8 *p = func_003766C0();

    *(int *)(p + 0x9A8) = 5;
    func_003D83C0();
}

/* 0x003D9050, 0x28 bytes, matching. */
void func_003D9050(void)
{
    u8 *p = func_003766C0();

    *(int *)(p + 0x9A8) = 5;
    func_003D83C0();
}

/* 0x003D93F0, 0x54 bytes, matching. */
void func_003D93F0(void)
{
    u8 *p = func_003766C0();

    g_0041CED0[*(int *)(p + 0xB4)]();
    func_003D3C60();
    *(int *)(p + 0x9A4) = 2;
}

/* 0x003D9450, 0x20 bytes, matching. */
u8 *func_003D9450(void)
{
    return (u8 *)((u8 *)func_00390940()) + 0x2C70;
}

/* 0x003D9470, 0x20 bytes, matching. */
u8 *func_003D9470(void)
{
    return (u8 *)((u8 *)func_00390940()) + 0x2C34;
}

/* 0x003D9490, 0x3C bytes, matching. */
int func_003D9490(int v)
{
    if (v == 0xD || v == 0x9F || (u32)(v - 0xA2) < 2)
        return 1;
    return 0;
}

/* 0x003D9E90, 0x34 bytes, matching. */
int func_003D9E90(void)
{
    int on = func_003DC2D0(0x15) != 0;

    if (!on)
        on = func_003DC2D0(0x16) != 0;
    return on;
}

/* 0x003DA7F0, 0x54 bytes. */
void func_003DA7F0(void)
{
    func_003DA890();
    g_007BEC40 = func_001026D0(1, 0x8C, 0, 1, 0, 0, g_0045C490, 0x6D);
    func_00102960(1);
}

/* 0x003DA850, 0x34 bytes. */
void func_003DA850(void)
{
    if (g_007BEC40 != 0) {
        func_00102EC0(g_007BEC40);
        g_007BEC40 = 0;
    }
}

/* 0x003DA890, 0x18 bytes. */
void func_003DA890(void)
{
    g_007BEC3C = 0;
    g_007BEC38 = -1;
}

/* 0x003DA8B0, 0x14 bytes. */
void func_003DA8B0(int v)
{
    g_007BEC38 = 0;
    g_007BEC3C = v;
}

/* 0x003DB0B0, 0xC bytes, matching. */
void func_003DB0B0(void)
{
    g_0045D830 = 0;
    g_0045D834 = 0;
}

/* 0x003DB1B0, 0x30 bytes. */
void func_003DB1B0(void)
{
    if (g_0045D830 != 0) {
        func_00102EC0(g_0045D830);
        g_0045D830 = 0;
        g_0045D834 = 0;
    }
}

/* 0x003DB460, 0x20 bytes, matching. */
void func_003DB460(int a, int b)
{
    func_003DB400(a, 1, b);
}

/* 0x003DB480, 0x20 bytes, matching. */
void func_003DB480(int a, int b)
{
    func_003DB400(a, 0, b);
}

/* 0x003DBB50, 0x38 bytes. */
void func_003DBB50(int k, int a, int b, int c)
{
    func_003DB9F0(g_007BEC50[k], a, b, c);
}

/* 0x003DC030, 0x8 bytes, matching. */
void func_003DC030(void)
{
}

/* 0x003DC080, 0x8 bytes, matching. */
void func_003DC080(void)
{
}

/* 0x003DC0E0, 0x28 bytes. */
void func_003DC0E0(int k, int a, int b)
{
    func_003DBB50(k, 1, a, b);
}

/* 0x003DC2D0, 0x30 bytes. Whether window `k` is busy (not closed). */
int func_003DC2D0(int k)
{
    return *(int *)(g_007BEC50[k] + 0x54) != 2;
}

/* 0x003DCAB0, 0x44 bytes. The battle result of player `p`. */
u8 *func_003DCAB0(int p)
{
    if (p < 0 || p > 1)
        return 0;
    return g_007BF540[p];
}

/* 0x003DCB00, 0x30 bytes, matching. */
u32 func_003DCB00(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x54);
}

/* 0x003DCBB0, 0x30 bytes, matching. */
u32 func_003DCBB0(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u32 *)(r + 0x98);
}

/* 0x003DCBE0, 0x30 bytes, matching. */
u32 func_003DCBE0(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u16 *)(r + 0x4C);
}

/* 0x003DCC10, 0x30 bytes, matching. */
u32 func_003DCC10(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u16 *)(r + 0x4E);
}

/* 0x003DCC40, 0x30 bytes, matching. */
u32 func_003DCC40(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x59);
}

/* 0x003DCC70, 0x30 bytes, matching. */
u32 func_003DCC70(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x5A);
}

/* 0x003DCCA0, 0x30 bytes, matching. */
u32 func_003DCCA0(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x5B);
}

/* 0x003DCCD0, 0x30 bytes, matching. */
u32 func_003DCCD0(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x5C);
}

/* 0x003DCD00, 0x30 bytes, matching. */
u32 func_003DCD00(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x5D);
}

/* 0x003DCD30, 0x30 bytes, matching. */
u32 func_003DCD30(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return *(u8 *)(r + 0x5E);
}

/* 0x003DCB30, 0x38 bytes. */
u32 func_003DCB30(int p, int k)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return r[k + 0x5F] & 0x7F;
}

/* 0x003DCB70, 0x3C bytes, matching. */
u32 func_003DCB70(int p)
{
    u8 *r = func_003DCAB0(p);

    if (r == 0)
        return 0;
    return r[r[0x3F] + 0x5F] & 0x7F;
}

/* 0x003DCD60, 0x28 bytes, matching. Saves the results into save image `p`. */
void func_003DCD60(u8 *p)
{
    func_00118AC0((unsigned int *)(p + 0x870), (unsigned char *)(g_007BF540), 0x138);
}

/* 0x003DCD90, 0x30 bytes, matching. */
void func_003DCD90(void)
{
    func_00118AC0((unsigned int *)(g_007BF540), (unsigned char *)PS2_PTR(func_002EFB00(9) + 0x870), 0x138);
}

/* 0x003DCDC0, 0x2C bytes, matching. */
void func_003DCDC0(void)
{
    func_003535D0();
    func_0034FE90();
    func_00352100();
}

/* 0x003DCDF0, 0x38 bytes, matching. The route length from group `g` to cell `pos`. */
u16 func_003DCDF0(u8 **g, u8 *pos)
{
    return func_0018F6F0((short unsigned int *)(func_0033B730(g)), (short unsigned int *)(pos), 0);
}

/* 0x003DCE30, 0x34 bytes, matching. */
u16 func_003DCE30(u8 **g, u8 **h)
{
    return func_003DCDF0(g, func_0033B730(h));
}

/* 0x003DCE70, 0x38 bytes, matching. */
u16 func_003DCE70(u8 **g, int c)
{
    u8 pos[4];

    func_0034ED90((unsigned char *)PS2_PTR(c), pos);
    return func_003DCDF0(g, pos);
}

/* 0x003DCEB0, 0x24 bytes, matching. */
u16 func_003DCEB0(u8 *u, u8 *pos)
{
    return func_0018F6F0((short unsigned int *)(u + 0x40), (short unsigned int *)(pos), 0);
}

/* 0x003DCEE0, 0x1C bytes, matching. */
u16 func_003DCEE0(u8 *a, u8 *b)
{
    return func_003DCEB0(a, b + 0x40);
}

/* 0x003DCF00, 0x1C bytes, matching. */
int func_003DCF00(int a, int b)
{
    return func_00352B00((unsigned char *)PS2_PTR(a), b);
}

/* 0x003DD4A0, 0x44 bytes, matching. */
u32 func_003DD4A0(int k)
{
    if (k < 0x10)
        return 0;
    if (k < 0x14)
        return *(u32 *)func_0019FBC0(k - 0x10);
    return 0;
}

/* 0x003DD660, 0x1C bytes, matching. */
void func_003DD660(int a, int b)
{
    func_00329450(a, b);
}

/* 0x003DD680, 0x5C bytes. The custom-officer slot of player `s` (4: none). */
int func_003DD680(int s)
{
    int v = func_003294A0(s);

    if (v < 0 || v > 3 || func_0019FBC0(v)[4] == 4)
        v = 4;
    return v;
}

/* 0x003DD6E0, 0x24 bytes, matching. */
void func_003DD6E0(int a, u16 *p)
{
    func_0019B170((char *)PS2_PTR(a), p[0], p[1]);
}

/* 0x003DD710, 0x1C bytes, matching. */
void func_003DD710(int a, u8 *q)
{
    func_003DD6E0(a, *(u16 **)(q + 8));
}

/* 0x003DD730, 0x1C bytes, matching. */
void func_003DD730(int a, u8 **q)
{
    func_003DD710(a, *q);
}

/* 0x003DD750, 0x3C bytes, matching. */
void func_003DD750(int c)
{
    func_00372C80(func_00363B90(), func_0034ED40((unsigned char *)PS2_PTR(c)));
}

/* 0x003DD790, 0x1C bytes, matching. */
char *func_003DD790(int k)
{
    return func_00372B40(k);
}

/* 0x003DD7B0, 0x1C bytes, matching. */
char *func_003DD7B0(int k)
{
    return func_00372B80(k);
}

/* 0x003DD7D0, 0x1C bytes, matching. */
char *func_003DD7D0(int k)
{
    return func_00372250(k + 0x3B);
}

/* 0x003DD7F0, 0x1C bytes, matching. */
void func_003DD7F0(u8 *p)
{
    func_00372580(PS2_ADDR(p + 0x3B));
}

/* 0x003DD970, 0x2C bytes, matching. */
void func_003DD970(void)
{
    func_0019F750((unsigned char *)PS2_PTR(func_002EFB00(8)));
    func_00362E20();
}

/* 0x003DD9A0, 0x54 bytes, matching. */
void func_003DD9A0(void)
{
    func_001A1CD0();
    func_0019F750((unsigned char *)PS2_PTR(func_002EFB00(8)));
    func_00362E20();
    func_0030CE90(10);
    func_0036D230(func_00362B60(0));
    func_003DD880();
}

/* 0x003DE700, 0x8 bytes, matching. */
void func_003DE700(void)
{
}

/* 0x003DE710, 0x8 bytes, matching. */
void func_003DE710(void)
{
}

/* 0x003DE8A0, 0x8 bytes, matching. */
void func_003DE8A0(void)
{
}

/* 0x003DE8B0, 0x8 bytes, matching. */
void func_003DE8B0(void)
{
}

/* 0x003DEB20, 0x8 bytes, matching. */
void func_003DEB20(void)
{
}

/* 0x003DE7F0, 0x1C bytes, matching. */
void func_003DE7F0(void)
{
    func_003DE720(0);
}

/* 0x003DE810, 0x1C bytes, matching. */
void func_003DE810(void)
{
    func_003DE720(1);
}

/* 0x003DE830, 0x1C bytes, matching. */
void func_003DE830(void)
{
    func_003DE720(2);
}

/* 0x003DEA70, 0x1C bytes, matching. */
void func_003DEA70(void)
{
    func_003DE8C0(0);
}

/* 0x003DEA90, 0x1C bytes, matching. */
void func_003DEA90(void)
{
    func_003DE8C0(1);
}

/* 0x003DEAB0, 0x1C bytes, matching. */
void func_003DEAB0(void)
{
    func_003DE8C0(2);
}

/* 0x003DE850, 0x44 bytes. */
void func_003DE850(void)
{
    if (func_0035DAE0() == 0) {
        func_003DE7F0();
    } else {
        func_003DE810();
        func_003DE830();
    }
}

/* 0x003DEAD0, 0x44 bytes. */
void func_003DEAD0(void)
{
    if (func_0035DAE0() == 0) {
        func_003DEA70();
    } else {
        func_003DEA90();
        func_003DEAB0();
    }
}
