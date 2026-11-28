/*
 * officer_sort.c - the Empire screens' list sorts: a bubble sort of officer numbers with one
 * comparison per column (stats, province, force, ...), and small list helpers (parts of
 * 0x003EE4A0-0x003EF92C). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_OFFICER_SORT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_003EEAE0();

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef int (*OfficerCmp)(int a, int b);

extern int g_007BFB60[];
extern int g_0045C870[0x46];
#ifdef SW2E_PC
extern ps2ptr g_0043C648_a;
#define g_0043C648 ((u8 *)PS2_PTR(g_0043C648_a))
#define g_0043C648_SET(v) (g_0043C648_a = PS2_ADDR(v))
#else
extern u8 *g_0043C648;
#define g_0043C648_a (*(ps2ptr *)&g_0043C648)
#define g_0043C648_SET(v) (g_0043C648 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0043C578_a;
#define g_0043C578 ((u8 *)PS2_PTR(g_0043C578_a))
#define g_0043C578_SET(v) (g_0043C578_a = PS2_ADDR(v))
#else
extern u8 *g_0043C578;
#define g_0043C578_a (*(ps2ptr *)&g_0043C578)
#define g_0043C578_SET(v) (g_0043C578 = (v))
#endif

/* 0x003EE4A0, 0x3C bytes. */
int func_003EE4A0(void)
{
    u8 *m = (u8 *)PS2_PTR(func_002FC2C0()[0x1AB]);

    return g_007BFB60[func_003EE460(*(u16 *)(m + 0x1C))];
}

/* 0x003EEDD0, 0x70 bytes. The page's help line. */
void func_003EEDD0(void)
{
    int v = *(int *)((u8 *)PS2_PTR(func_002FC2C0()[0x1AB]) + 4);

    if (v == 1)
        func_001A7DC0((const char *)(g_0043C648), 0x80, 2);
    else if (v == 0)
        func_001A7DC0((const char *)(g_0043C578), 0x80, 2);
}

/* 0x003EEE40, 0x8 bytes, matching. */
void func_003EEE40(void)
{
}

/* 0x003EEF50, 0x8 bytes, matching. */
void func_003EEF50(void)
{
}

/* 0x003EF070, 0x60 bytes. */
int func_003EF070(void)
{
    int v = *(int *)((u8 *)PS2_PTR(func_002FC2C0()[0x1AB]) + 4);

    if (v == 1) {
        func_003EEAE0();
        return 0;
    }
    if (v != 0)
        return 0;
    return func_003EE840();
}

/* 0x003EF0D0, 0x30 bytes. */
int func_003EF0D0(int v)
{
    if (v < 0x46)
        return g_0045C870[v];
    return 0xD8;
}

/* 0x003EF100, 0xC4 bytes, matching. Bubble-sorts `n` officers `list` (`cmp`: whether its first goes first). */
void func_003EF100(int *list, int n, OfficerCmp cmp)
{
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = n - 1; i < j; j--) {
            if (cmp(list[j], list[j - 1]) != 0) {
                int t = list[j];

                list[j] = list[j - 1];
                list[j - 1] = t;
            }
        }
    }
}

/* 0x003EF3E0, 0x20 bytes, matching. By name. */
void func_003EF3E0(int *list, int n)
{
    func_003EF100(list, n, func_003EF290);
}

/* 0x003EF550, 0x20 bytes, matching. By reading. */
void func_003EF550(int *list, int n)
{
    func_003EF100(list, n, func_003EF400);
}

/* 0x003EF570, 0x34 bytes, matching. Higher func_002F41E0 first. */
int func_003EF570(int a, int b)
{
    int x = func_002F41E0(a);

    return func_002F41E0(b) < x;
}

/* 0x003EF5B0, 0x20 bytes, matching. */
void func_003EF5B0(int *list, int n)
{
    func_003EF100(list, n, func_003EF570);
}

/* 0x003EF5D0, 0x34 bytes, matching. Higher func_002F5CC0 first. */
int func_003EF5D0(int a, int b)
{
    int x = func_002F5CC0(a);

    return func_002F5CC0(b) < x;
}

/* 0x003EF610, 0x20 bytes, matching. */
void func_003EF610(int *list, int n)
{
    func_003EF100(list, n, func_003EF5D0);
}

/* 0x003EF630, 0x34 bytes, matching. Higher func_002F4080 first. */
int func_003EF630(int a, int b)
{
    int x = func_002F4080(a);

    return func_002F4080(b) < x;
}

/* 0x003EF670, 0x20 bytes, matching. */
void func_003EF670(int *list, int n)
{
    func_003EF100(list, n, func_003EF630);
}

/* 0x003EF690, 0x34 bytes, matching. Higher func_002F4660 first. */
int func_003EF690(int a, int b)
{
    int x = func_002F4660(a);

    return func_002F4660(b) < x;
}

/* 0x003EF6D0, 0x20 bytes, matching. */
void func_003EF6D0(int *list, int n)
{
    func_003EF100(list, n, func_003EF690);
}

/* 0x003EF6F0, 0x34 bytes, matching. Higher func_002F3770 first. */
int func_003EF6F0(int a, int b)
{
    int x = func_002F3770(a);

    return func_002F3770(b) < x;
}

/* 0x003EF730, 0x20 bytes, matching. */
void func_003EF730(int *list, int n)
{
    func_003EF100(list, n, func_003EF6F0);
}

/* 0x003EF750, 0x34 bytes, matching. Higher func_002F39F0 first. */
int func_003EF750(int a, int b)
{
    int x = func_002F39F0(a);

    return func_002F39F0(b) < x;
}

/* 0x003EF790, 0x20 bytes, matching. */
void func_003EF790(int *list, int n)
{
    func_003EF100(list, n, func_003EF750);
}

/* 0x003EF7B0, 0x34 bytes, matching. Higher func_002F4C40 first. */
int func_003EF7B0(int a, int b)
{
    int x = func_002F4C40(a);

    return func_002F4C40(b) < x;
}

/* 0x003EF7F0, 0x20 bytes, matching. */
void func_003EF7F0(int *list, int n)
{
    func_003EF100(list, n, func_003EF7B0);
}

/* 0x003EF810, 0x34 bytes, matching. Higher func_002F4DD0 first. */
int func_003EF810(int a, int b)
{
    int x = func_002F4DD0(a);

    return func_002F4DD0(b) < x;
}

/* 0x003EF850, 0x20 bytes, matching. */
void func_003EF850(int *list, int n)
{
    func_003EF100(list, n, func_003EF810);
}

/* 0x003EF870, 0x34 bytes, matching. Higher func_002F4F60 first. */
int func_003EF870(int a, int b)
{
    int x = func_002F4F60(a);

    return func_002F4F60(b) < x;
}

/* 0x003EF8B0, 0x20 bytes, matching. */
void func_003EF8B0(int *list, int n)
{
    func_003EF100(list, n, func_003EF870);
}

/* 0x003EF8D0, 0x34 bytes, matching. Higher func_002F5AA0 first. */
int func_003EF8D0(int a, int b)
{
    int x = func_002F5AA0(a);

    return func_002F5AA0(b) < x;
}

/* 0x003EF910, 0x20 bytes, matching. */
void func_003EF910(int *list, int n)
{
    func_003EF100(list, n, func_003EF8D0);
}
