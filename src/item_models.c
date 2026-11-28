/*
 * item_models.c - pieces between 0x002AAC50 and 0x002AD9F4: officer stat maxima for the
 * status screens, small framed buttons and the item models (17 model files at 0x0078DC40,
 * 0x30 bytes each, and 150 model actors at 0x007804A0, 0x170 bytes each, bit 0 of +0x168:
 * in use; each item shows up to five parts). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_ITEM_MODELS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern u8 g_0078DF70[];                  /* the item models' shared skeleton? */
extern u8 g_0078DC40[0x11][0x30];        /* the item model files */
extern u8 g_007804A0[0x96][0x170];       /* the model actors */
extern u16 g_00411F70[0x11];            /* the models' LINKDATA entries */
extern u8 g_00411F10[0x10], g_00411F20[0x10][5];
extern u8 g_004412D8[];
#ifdef SW2E_PC
extern ps2ptr g_0045D310_a;      /* (small data) */
#define g_0045D310 ((u8 *)PS2_PTR(g_0045D310_a))
#define g_0045D310_SET(v) (g_0045D310_a = PS2_ADDR(v))
#else
extern u8 *g_0045D310;
#define g_0045D310_a (*(ps2ptr *)&g_0045D310)
#define g_0045D310_SET(v) (g_0045D310 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0045D318_a;      /* (small data) */
#define g_0045D318 ((u8 *)PS2_PTR(g_0045D318_a))
#define g_0045D318_SET(v) (g_0045D318_a = PS2_ADDR(v))
#else
extern u8 *g_0045D318;
#define g_0045D318_a (*(ps2ptr *)&g_0045D318)
#define g_0045D318_SET(v) (g_0045D318 = (v))
#endif

void func_002C7310(int x, int y, int a, int w, int h, int b, int c);

/* 0x002AB820, 0xD4 bytes, matching. Officer `o`'s stat `k`. */
int func_002AB820(int o, int k)
{
    int v = 0;

    switch (k) {
    case 0:
        v = func_002F39F0(o);
        break;
    case 1:
        v = func_002F4C40(o);
        break;
    case 2:
        v = func_002F4DD0(o);
        break;
    case 3:
        v = func_002F4F60(o);
        break;
    case 4:
        v = func_002F50F0(o);
        break;
    case 5:
        v = func_002F5280(o);
        break;
    case 6:
        v = func_002F5410(o);
        break;
    case 7:
        v = func_002F55A0(o);
        break;
    case 8:
        v = func_002F34E0(o);
        break;
    case 9:
        v = func_002F41E0(o);
        break;
    }
    return v;
}

/* 0x002AB900, 0x164 bytes. The stat as a fraction of its maximum (gauge length). */
float func_002AB900(int o, int k)
{
    float f = (float)func_002AB820(o, k);

    switch (k) {
    case 0:
    case 1:
        f = f / 350.0f;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        f = f / 250.0f;
        break;
    case 8:
        f = f / 99999.0f;
        break;
    }
    return f;
}

/* 0x002ABA70, 0xCC bytes. Whether the stat is at its maximum. */
int func_002ABA70(int o, int k)
{
    int v = func_002AB820(o, k), r = 0;

    switch (k) {
    case 0:
    case 1:
        r = v == 0x15E;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        r = v == 0xFA;
        break;
    case 8:
        r = v == 99999;
        break;
    case 9:
        r = v == 0x14;
        break;
    }
    return r;
}

/* 0x002AAC50, 0xE4 bytes. A button (lit when `sel`) with its mark in the middle. */
void func_002AAC50(u8 *t, int x, int y, int w, int h, int sel, int p6)
{
    if (sel == 1)
        func_002C8500(x, y, 0, w, h, 0x80, 0);
    else
        func_002C80A0(x, y, 0, w, h, 0x80, 0);
    func_001ABE40(t, 0x14, x + w / 2, y + h / 2, 0, -1, -1, 0x80, p6, 1);
}

/* 0x002AAD40, 0xC4 bytes, matching. */
void func_002AAD40(u8 *t, int x, int y, int w, int h, int c)
{
    func_002C7310(x, y, 0, w, h, 0x80, c);
    func_001ABE40(t, 0x14, x + w / 2, y + h / 2, 0, -1, -1, 0x80, c, 1);
}

/* 0x002AD4C0, 0x14C bytes. Loads the item models and clears the actors. */
void func_002AD4C0(void)
{
    u8 *f = func_001026D0(1, 0x571, 0, 1, 0, 0, (const char *)(g_004412D8), 0x68);
    int k;

    func_00147D20((unsigned int *)(g_0078DF70));
    func_00147D30((unsigned int *)(f), g_0078DF70, 0x2920, 0x3CE4);
    for (k = 0; k < 0x11; k++) {
        func_00148130(g_0078DC40[k]);
        f = func_001026D0(1, g_00411F70[k], 0, 1, 0, 0, (const char *)(g_004412D8), 0x74);
        if (k == 9 || (u32)(k - 0xE) < 3)
            func_001482F0((unsigned int *)(f), g_0078DC40[k], PS2_ADDR(g_0045D318));
        else
            func_001482F0((unsigned int *)(f), g_0078DC40[k], PS2_ADDR(g_0045D310));
    }
    for (k = 0; k < 0x96; k++) {
        func_0014F850(g_007804A0[k]);
        func_0014F8B0((unsigned int *)(g_007804A0[k]), 0);
    }
}

/* 0x002AD610, 0x80 bytes, matching. */
void func_002AD610(void)
{
    int k;

    func_00147F40((unsigned int *)(g_0078DF70));
    for (k = 0; k < 0x11; k++)
        func_00148370(g_0078DC40[k]);
    for (k = 0; k < 0x96; k++)
        func_0014F950(g_007804A0[k]);
}

/* 0x002AD690, 0x64 bytes. Frees every actor. */
void func_002AD690(void)
{
    int k;

    for (k = 0; k < 0x96; k++) {
        g_007804A0[k][0x168] &= 0xFE;
        func_0014FCA0(g_007804A0[k], 0);
    }
}

/* 0x002AD700, 0x58 bytes. Item `k`'s model colour? */
u8 func_002AD700(int k)
{
    if (k < 0 || k > 0xF) {
        if (k < 0x14)
            return func_0019FBC0(k - 0x10)[9];
        return 0;
    }
    return g_00411F10[k];
}

/* 0x002AD760, 0x148 bytes. Takes actors for item `k`'s five parts. */
void func_002AD760(int k, u8 **out)
{
    int j, i;

    for (j = 0; j < 5; j++, out++) {
        u32 m = 0x11;
        u8 *model, *a = 0;

        if (k < 0x10)
            m = g_00411F20[k][j];
        else if (k < 0x14)
            m = func_0019FBC0(k - 0x10)[j + 0xE];
        model = m < 0x11 ? g_0078DC40[m] : 0;
        if (model == 0) {
            *out = 0;
            continue;
        }
        for (i = 0; i < 0x96; i++) {
            if ((g_007804A0[i][0x168] & 1) == 0) {
                a = g_007804A0[i];
                break;
            }
        }
        *out = a;
        if (a != 0) {
            func_0014FCA0(a, model);
            (*out)[0x168] = ((*out)[0x168] & 0xFE) | 1;
        }
    }
}

/* 0x002AD8B0, 0x6C bytes. Gives them back. */
void func_002AD8B0(u8 **l)
{
    int j;

    for (j = 0; j < 5; j++, l++) {
        if (*l != 0) {
            func_0014FCA0(*l, 0);
            (*l)[0x168] &= 0xFE;
        }
    }
}

/* 0x002AD920, 0x34 bytes, matching. */
void func_002AD920(u8 *m, int v)
{
    func_00148070(m, v);
    func_00148070(g_0078DF70, v);
}

/* 0x002AD960, 0x34 bytes. */
void func_002AD960(u8 *p)
{
    func_002AD920(PS2_LOADP(u8 *, (p + 0x130)), func_002AD700(p[0x180]));
}

/* 0x002AD9A0, 0x54 bytes. Draws them. */
void func_002AD9A0(u8 **l)
{
    int j;

    for (j = 0; j < 5; j++, l++) {
        if (*l != 0)
            func_0014F970(*l);
    }
}
