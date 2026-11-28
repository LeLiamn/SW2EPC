/*
 * gen13_170000.c - small functions between 0x00173000 and 0x00180000, generated from Ghidra
 * output (access widths from the disassembly) and kept only when their compiled size is within
 * 25 % of the original (calls and return values checked against the machine code). Machine-like
 * (layout cleaned up; names and types still to be done by hand).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_mem.h"
#include "sw2e_protos.h"

#define true 1
#define false 0

extern u8 g_00424D20[0x4];
extern u8 g_00424D90[0x4];
extern u8 g_00424DD0[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_005B4A1C[0x4];
extern int g_0045D2CC;   /* (small data) */
extern int g_0045D2D0;   /* (small data) */
extern int g_0045D2D4;   /* (small data) */
extern int g_0045D2D8;   /* (small data) */

int func_0017DCE0();
int func_0017DD60();
int func_0017DD80();
int func_0017DDA0();
int func_0017DE60();
int func_0017DF10();
int func_0017DF30();

/* 0x00178AC0, 0x1F4 bytes. */
void func_00178AC0(u8 *param_1)
{
    int bVar2;
    float fStack_c;
    float fVar4;
    float fVar5;
    int iVar3;
    u32 uStack_10;
    u32 uStack_4;
    u32 uStack_8;
    u32 uVar1;

    fVar5 = *(float *)(param_1 + 0xE0);
    uStack_10 = *(u32 *)(param_1 + 0x90);
    uStack_8 = *(u32 *)(param_1 + 0x98);
    uStack_4 = *(u32 *)(param_1 + 0x9C);
    fStack_c = *(float *)(param_1 + 0x44) - *(float *)(*(int *)(param_1 + 0x114) + 0x80);
    *(ps2ptr *)(param_1 + 0xD0) = PS2_ADDR(&uStack_10);
    func_001F2BF0(param_1 + 0xD0);
    fVar4 = *(float *)(param_1 + 0xE0);
    if ((*(u8 *)(param_1 + 0x14E) < 2) && (400.0f < fVar4 - fVar5)) {
        iVar3 = (u32)*(u8 *)(param_1 + 0x14E) * 0xF0;
        *(u8 *)(g_005B4A1C + iVar3) = *(u8 *)(g_005B4A1C + iVar3) & 0xFD | 2;
    }
    if (-1 < (long long)*(char *)(param_1 + 0x19E) << 0x39) {
        if ((long long)*(char *)(param_1 + 0x27C) << 0x3E < 0) {
            if (fVar4 < *(float *)(param_1 + 0x44)) {
                *(float *)(param_1 + 0x44) = fVar4;
            }
        }
        else {
            *(u16 *)(param_1 + 0x278) = 0xFFFF;
            uVar1 = *(u32 *)(*(int *)(param_1 + 0x210) + 0x18);
            if ((uVar1 & 0x40000020) == 0) {
                if (*(int *)(param_1 + 0x288) == 0) {
                    if (*(float *)(param_1 + 0xE0) - *(float *)(param_1 + 0x44) < 50.0f) {
                        bVar2 = false;
                    }
                    else if ((uVar1 & 0x440) == 0) {
                        if ((*(int *)(param_1 + 0x11C) == 0) ||
                              (1 < *(u32 *)(*(int *)(param_1 + 0x11C) + 0x204))) {
                            if (*(int *)(param_1 + 0x118) == 0x3C) {
                                *(u16 *)(param_1 + 0x278) = 0x11;
                            }
                            else {
                                *(u16 *)(param_1 + 0x278) = 0xD;
                            }
                            bVar2 = true;
                        }
                        else {
                            bVar2 = false;
                        }
                    }
                    else {
                        if ((uVar1 & 0x1000000) == 0) {
                            *(u16 *)(param_1 + 0x278) = 0x32;
                        }
                        else {
                            *(u16 *)(param_1 + 0x278) = 0x33;
                        }
                        bVar2 = true;
                    }
                }
                else {
                    bVar2 = true;
                }
            }
            else {
                bVar2 = false;
            }
            if (!bVar2) {
                *(float *)(param_1 + 0x44) = fVar4;
            }
        }
    }
}

/* 0x0017D7B0, 0xA4 bytes. */
int func_0017D7B0(void)
{
    int uVar1;

    if (g_0045D2CC != 0) {
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar1 = 0;
        }
        else {
            uVar1 = *(u16 *)g_0050074C;
        }
        if ((uVar1 & 0x800) != 0) {
            func_0023AD10(5, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_00114E30();
            return 1;
        }
    }
    return 0;
}

/* 0x0017D860, 0x3C bytes. */
int func_0017D860(int param_1)
{
    u8 * pbVar2;
    u32 uVar1;

    uVar1 = 0;
    pbVar2 = g_00424D90;
    do {
        if (*pbVar2 == param_1) {
            return uVar1;
        }
        uVar1 = uVar1 + 1;
        pbVar2 = pbVar2 + 1;
    } while (uVar1 < 0x15);
    return 0x4F;
}

/* 0x0017DBC0, 0x3C bytes. */
int func_0017DBC0(int param_1)
{
    u8 * pbVar2;
    u32 uVar1;

    uVar1 = 0;
    pbVar2 = g_00424DD0;
    do {
        if (param_1 == *pbVar2) {
            return uVar1;
        }
        uVar1 = uVar1 + 1;
        pbVar2 = pbVar2 + 1;
    } while (uVar1 < 0x69);
    return 0xFFFFFFFF;
}

/* 0x0017DCF0, 0x54 bytes. */
int func_0017DCF0(int param_1)
{
    long long lVar2;
    int uVar1;

    if ((param_1 < 0) || (lVar2 = func_0017DCE0(), lVar2 <= param_1)) {
        uVar1 = 0;
    }
    else {
        uVar1 = g_00424DD0[(int)param_1];
    }
    return uVar1;
}

/* 0x0017DDE0, 0x68 bytes. */
void func_0017DDE0(void)
{
    long long lVar1;

    if (g_0045D2D0 != 'i') {
        lVar1 = func_0017DDA0();
        if (lVar1 == 0) {
            func_0017DF30(g_0045D2D0, g_0045D2D4);
            g_0045D2D4 = 0;
            g_0045D2D0 = 'i';
        }
        else {
            lVar1 = func_0017DD60();
            if (lVar1 == 0) {
                func_0017DF10();
            }
        }
    }
}

/* 0x0017DE70, 0x28 bytes. */
void func_0017DE70(int param_1)
{
    func_0017DE60(param_1, *(u8 *)(g_00424D20 + param_1));
}

/* 0x0017DEA0, 0x70 bytes. */
int func_0017DEA0(int param_1)
{
    int cVar2;
    long long lVar1;

    cVar2 = g_0045D2D8;
    lVar1 = func_0017DD80();
    if ((lVar1 == 0) || (lVar1 = func_0017DD60(), lVar1 != 0)) {
        if (cVar2 != 'i') {
            cVar2 = 'i';
        }
    }
    else {
        func_001153F0(param_1);
    }
    g_0045D2D8 = 0x69;
    return cVar2;
}

/* 0x0017E010, 0x28 bytes. */
void func_0017E010(int param_1)
{
    func_0017DF30(param_1, *(u8 *)(g_00424D20 + param_1));
}

/* 0x0017E140, 0x58 bytes. */
void func_0017E140(u32 *param_1)
{
    int iVar1;
    u32 * puVar2;

    param_1[1] = 0;
    iVar1 = 0;
    *param_1 = 0;
    puVar2 = param_1 + 4;
    do {
        puVar2[6] = 0;
        iVar1 = iVar1 + 1;
        puVar2[8] = 0;
        puVar2[9] = 0;
        puVar2[10] = 0;
        puVar2[0xB] = 0;
        puVar2 = puVar2 + 0xC;
    } while (iVar1 < 0xA0);
    param_1[0x784] = 0;
    param_1[0x785] = 0;
    param_1[0x786] = 0;
    param_1[0x787] = 0;
    param_1[0x788] = 0;
    param_1[0x789] = 0;
    param_1[0x78A] = 0;
    param_1[0x78B] = 0;
}
