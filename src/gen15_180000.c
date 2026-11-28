/*
 * gen15_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_0076F3E4[0x18];
extern u8 g_0076F420[0x18];
extern u8 g_0076F434[0x18];
extern u8 g_0076F498[0x18];
extern u8 g_0076F59C[0x18];
extern u8 g_0076F5B0[0x18];
extern u8 g_0076F5C4[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"

#define true 1
#define false 0

extern u8 g_00400001[0x4];
extern u8 g_00411470[0x40];
extern u8 g_00411E70[0x4];
extern u8 g_0041C410[0x40];
extern u8 g_0043FAB8[0x8];
extern u8 g_0056CCA4[0x24];
extern u8 g_00669F60[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_0074A144[0x4];
extern u8 g_0074A150[0x4];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F3D4[0x1];
extern u8 g_0076F634[0x4];
extern u8 g_0077BEF4[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045CEBB;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_70000150 (*(int *)PS2_PTR(0x70000150))   /* (scratchpad) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */

int func_001204B0();
int func_002284E0();
int func_0022D590();
int func_00263AD0();
int func_00278FC0();
int func_00279140();
int func_0029C800();
int func_002A5B10();
int func_002A85F0();
int func_002C7310();
int func_002CB550();
int func_003B4F50();
int func_003E3520();
int func_003E3770();
int func_003E3ED0();
int func_003EF930();

/* 0x002287F0, 0x204 bytes. */
void func_002287F0(int param_1)
{
    float fVar5;
    int iVar1;
    u8 * iVar2;
    int iVar3;
    u32 uVar4;

    iVar2 = (u8 *)PS2_PTR((int)param_1);
    if (param_1 != 0) {
        *(int *)(iVar2 + 0x28) = *(int *)(iVar2 + 0x28) + *(int *)(*(int *)(iVar2 + 0x30) + 0x20);
        *(int *)(iVar2 + 0x2C) = *(int *)(iVar2 + 0x2C) + *(int *)(*(int *)(iVar2 + 0x30) + 0x24);
        iVar1 = *(int *)(iVar2 + 0x28);
        if (iVar1 < 0) {
            iVar1 = iVar1 + 1;
        }
        *(int *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) - (iVar1 >> 1);
        iVar1 = *(int *)(iVar2 + 0x2C);
        if (iVar1 < 0) {
            iVar1 = iVar1 + 3;
        }
        *(int *)(iVar2 + 0x1C) = *(int *)(iVar2 + 0x1C) - (iVar1 >> 2);
        iVar1 = *(int *)(iVar2 + 0x28);
        if (iVar1 < 0) {
            iVar1 = iVar1 + 1;
        }
        *(int *)(iVar2 + 0x20) = *(int *)(iVar2 + 0x20) + (iVar1 >> 1);
        iVar1 = *(int *)(iVar2 + 0x2C);
        if (iVar1 < 0) {
            iVar1 = iVar1 + 3;
        }
        *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x24) + (iVar1 >> 2);
        *(int *)(g_70000150 * 0x90 + iVar2 + 0x90) = *(int *)(iVar2 + 0x18) * 0x10 + 0x7000;
        *(int *)(g_70000150 * 0x90 + iVar2 + 0x94) = *(int *)(iVar2 + 0x1C) * 8 + 0x7900;
        *(int *)(g_70000150 * 0x90 + iVar2 + 0xC0) = *(int *)(iVar2 + 0x20) * 0x10 + 0x7000;
        *(int *)(g_70000150 * 0x90 + iVar2 + 0xC4) = *(int *)(iVar2 + 0x24) * 8 + 0x7900;
        fVar5 = *(float *)(iVar2 + 8) + *(float *)(iVar2 + 0xC);
        *(float *)(iVar2 + 8) = fVar5;
        if (1.0 < fVar5) {
            func_002284E0();
        }
        else if (*(float *)(iVar2 + 0x10) < fVar5) {
            uVar4 = 0;
            iVar1 = 0;
            do {
                iVar3 = *(int *)(iVar2 + (g_70000150 ^ 1) * 0x90 + iVar1 + 0x8C) -
                                (int)*(float *)(iVar2 + 0x14);
                if (iVar3 < 0) {
                    iVar3 = 0;
                }
                uVar4 = uVar4 + 1;
                *(int *)(iVar2 + g_70000150 * 0x90 + iVar1 + 0x8C) = iVar3;
                iVar1 = iVar1 + 0x30;
            } while (uVar4 < 2);
        }
    }
}

/* 0x0022D7C0, 0x14C bytes. */
int func_0022D7C0(u8 *param_1, int param_2)
{
    int iVar1;
    u32 * puVar2;

    iVar1 = *(int *)(param_1 + 8) * 0x14;
    puVar2 = (u32 *)(iVar1 + 0x74A140);
    if (param_2 == 0) {
        *puVar2 = *puVar2 | 2;
    }
    else {
        func_0022D590();
        *puVar2 = 0;
        *(u32 *)(g_0074A150 + iVar1) = 0;
        if (*(int *)(g_0074A144 + iVar1) == 1) {
            *puVar2 = (u32)(g_00400001);
            return 0;
        }
        if (*(int *)(g_0074A144 + iVar1) == 3) {
            *puVar2 = 0x800001;
            return 0;
        }
        if (param_2 != -1) {
            if (param_2 == -2) {
                *puVar2 = 0x401;
            }
            else if (((((param_2 < -0x13) || (-0xB < param_2)) && ((param_2 < -0x31 || (-0x28 < param_2)))
                                ) && ((param_2 < -0x3B || (-0x32 < param_2)))) &&
                            ((param_2 < -0x4F || (-0x46 < param_2)))) {
                *puVar2 = 0x40000001;
            }
            return 0;
        }
        *puVar2 = 1;
    }
    return 1;
}

/* 0x002696B0, 0x88 bytes. */
void func_002696B0(int param_1)
{
    int iVar1;

    iVar1 = param_1 * 0x2C + 0x7325E8;
    if ((*(u32 *)g_00669F60 & 8) == 0) {
        func_00263AD0();
        *(u8 *)((u8 *)PS2_PTR(iVar1) + 0x26) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x1C) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x20) = *(u32 *)(param_1 * 0x48 + 0x669DEC);
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x14) = 0;
        *(u8 *)((u8 *)PS2_PTR(iVar1) + 0x25) = 0x10;
    }
}

/* 0x00273D00, 0x4C bytes. */
void func_00273D00(void)
{
    u8 auStack_10[15];
    int uStack_1;

    func_001AE550(1.0f, g_0076F498, (short int *)(auStack_10), (u8 *)(&uStack_1), 0);
    func_00278FC0(0x29, auStack_10, uStack_1, 0, 1);
}

/* 0x00273D50, 0xF0 bytes. */
void func_00273D50(void)
{
    u8 auStack_10[15];
    u8 auStack_18[8];
    u8 auStack_20[8];
    int uStack_1;

    if (*(char *)g_0076F3D4 == 0) {
        func_001AE550(1.0f, g_0076F434, (short int *)(auStack_10), (u8 *)(&uStack_1), 1);
        func_00278FC0(4, auStack_10, uStack_1, 0, 1);
        func_001AE550(1.0f, g_0076F3E4, (short int *)(auStack_18), (u8 *)(&uStack_1), 1);
        func_00278FC0(0, auStack_18, uStack_1, 0, 1);
        func_00279140(*(u16 *)g_0043FAB8, *(u16 *)(g_0043FAB8 + 0x2), 0, *(u16 *)(g_0043FAB8 + 0x4), *(u16 *)(g_0043FAB8 + 0x6), 1);
        func_001AE550(1.0f, g_0076F420, (short int *)(auStack_20), (u8 *)(&uStack_1), 0);
        func_00278FC0(3, auStack_20, uStack_1, 0, 1);
    }
}

/* 0x00274400, 0xBC bytes. */
void func_00274400(void)
{
    u8 auStack_10[15];
    int uStack_1;

    func_001AE550(1.0f, g_0076F5C4, (short int *)(auStack_10), (u8 *)(&uStack_1), 0);
    func_00278FC0(0x27, auStack_10, uStack_1, 0, 1);
    func_001AE550(1.0f, g_0076F59C, (short int *)(auStack_10), (u8 *)(&uStack_1), 0);
    func_00278FC0(0x28, auStack_10, uStack_1, 0, 1);
    func_001AE550(1.0f, g_0076F5B0, (short int *)(auStack_10), (u8 *)(&uStack_1), 0);
    func_00278FC0(0x28, auStack_10, uStack_1, 0, 1);
}

/* 0x0028FE20, 0x564 bytes. */
void func_0028FE20(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int aiStack_50[16];
    u8 auStack_10[16];
    int iVar10;
    int iVar11;
    int iVar5;
    u8 * iVar6;
    long long lVar1;
    int * piVar12;
    int * piVar13;
    int * piVar7;
    int * piVar8;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;
    u32 uVar9;

    aiStack_50[0xC] = *(u32 *)g_00411470;
    aiStack_50[0xD] = *(u32 *)(g_00411470 + 0x4);
    aiStack_50[0xE] = *(u32 *)(g_00411470 + 0x8);
    aiStack_50[0xF] = *(u32 *)(g_00411470 + 0xC);
    aiStack_50[8] = *(u32 *)(g_00411470 + 0x10);
    aiStack_50[9] = *(u32 *)(g_00411470 + 0x14);
    aiStack_50[10] = *(u32 *)(g_00411470 + 0x18);
    aiStack_50[0xB] = *(u32 *)(g_00411470 + 0x1C);
    aiStack_50[4] = *(u32 *)(g_00411470 + 0x20);
    aiStack_50[5] = *(u32 *)(g_00411470 + 0x24);
    aiStack_50[6] = *(u32 *)(g_00411470 + 0x28);
    aiStack_50[7] = *(u32 *)(g_00411470 + 0x2C);
    aiStack_50[0] = *(u32 *)(g_00411470 + 0x30);
    aiStack_50[1] = *(u32 *)(g_00411470 + 0x34);
    aiStack_50[2] = *(u32 *)(g_00411470 + 0x38);
    aiStack_50[3] = *(u32 *)(g_00411470 + 0x3C);
    lVar1 = func_0036D310();
    if (lVar1 == 0) {
        func_002C7310(param_1, param_2, param_3, 0x108, 0x38, 0x80, param_4);
        uVar2 = PS2_ADDR(func_00105860(4, 0));
        uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F57);
        iVar6 = (u8 *)PS2_PTR((int)uVar2);
        *(unsigned long long *)(iVar6 + 0x18) = uVar3;
        *(unsigned long long *)(iVar6 + 0x20) = (long long)(int)(param_5 & 0xFF) << 0x18 | 0x3F80000000808080;
        *(unsigned long long *)(iVar6 + 0x28) = 0x7880908;
        iVar10 = (int)param_2;
        *(unsigned long long *)(iVar6 + 0x38) = 0x8F80A78;
        uVar4 = (long long)(0xFFFE - (int)param_3) << 0x20;
        iVar5 = (((iVar10 + 8) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar5 < 0) {
            iVar5 = iVar5 + 0x1FF;
        }
        iVar11 = (int)param_1;
        *(unsigned long long *)(iVar6 + 0x30) =
                  uVar4 | (long long)((iVar11 + 0x7A) * 0x10 + 0x7000) |
                                  (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
        iVar5 = (((iVar10 + 0x20) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar5 < 0) {
            iVar5 = iVar5 + 0x1FF;
        }
        *(unsigned long long *)(iVar6 + 0x40) =
                  uVar4 | (long long)((iVar11 + 0x92) * 0x10 + 0x7000) |
                                  (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
        func_00105900((u8 *)PS2_PTR(uVar2), param_4);
        uVar9 = 0;
        piVar8 = aiStack_50 + 0xC;
        piVar7 = aiStack_50 + 8;
        piVar12 = aiStack_50 + 4;
        piVar13 = aiStack_50;
        do {
            iVar5 = *piVar8;
            if (uVar9 == 0) {
                uVar2 = PS2_ADDR(func_00362A20(0));
                func_002C4E40(16.0f, (char *)PS2_PTR(uVar2), iVar11 + iVar5, iVar10 + piVar8[1], 0x68, param_4, 0, 3);
            }
            else {
                if (uVar9 == 0) {
                    *(u32 *)(g_0056CCA4) = 3;
                    *(u32 *)(g_0056CCA4 + 0x4) = 3;
                    *(u32 *)(g_0056CCA4 + 0x8) = 3;
                    *(u32 *)(g_0056CCA4 + 0xC) = 3;
                }
                else {
                    *(u32 *)(g_0056CCA4) = 1;
                    *(u32 *)(g_0056CCA4 + 0x4) = 1;
                    *(u32 *)(g_0056CCA4 + 0x8) = 1;
                    *(u32 *)(g_0056CCA4 + 0xC) = 1;
                }
                *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
                *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
                uVar2 = PS2_ADDR(func_00362A20(uVar9));
                func_00146B40((u8 *)PS2_PTR(uVar2), iVar11 + iVar5, iVar10 + piVar8[1], 0x68, 0x10, param_4, 0);
                *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
                *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
                *(u32 *)(g_0056CCA4) = 5;
                *(u32 *)(g_0056CCA4 + 0x4) = 5;
                *(u32 *)(g_0056CCA4 + 0x8) = 5;
                *(u32 *)(g_0056CCA4 + 0xC) = 5;
            }
            uVar2 = func_0035F2D0(uVar9);
            func_001204B0(auStack_10, 0x440948, uVar2);
            if (uVar9 == 0) {
                func_002C5020(16.0f, (char *)(auStack_10), iVar11 + *piVar7, iVar10 + piVar7[1], param_4, 0, 6);
            }
            else {
                func_002C4F40(16.0f, (char *)(auStack_10), iVar11 + *piVar7, iVar10 + piVar7[1], param_4, 0, 6);
            }
            func_003E3520(iVar11 + *piVar12, iVar10 + piVar12[1], 0, 0x3C, 4, param_4, uVar9, uVar2);
            uVar2 = func_0035F340(uVar9);
            func_003B4F50(uVar9, uVar2, iVar11 + *piVar13, iVar10 + piVar13[1], 0, param_4);
            uVar9 = uVar9 + 1;
            piVar8 = piVar8 + 2;
            piVar7 = piVar7 + 2;
            piVar12 = piVar12 + 2;
            piVar13 = piVar13 + 2;
        } while (uVar9 < 2);
    }
}
/* MISSING ['0x411470', '0x411474', '0x411478', '0x41147c', '0x411480', '0x411484', '0x411488', '0x41148c', '0x411490', '0x411494', '0x411498', '0x41149c', '0x4114a0', '0x4114a4', '0x4114a8', '0x4114ac'] */

/* 0x0029B4D0, 0xC8 bytes. */
void func_0029B4D0(int param_1, int param_2, int param_3, int param_4)
{
    unsigned long long uVar1;

    func_003E3770();
    func_003E3ED0(param_1 + 0xC, param_2 + 0xC, param_3, 0x80, 0x40, param_4, 0, 0x80);
    func_003B58A0(param_1 + 0x10, param_2 + 0x55, 0, 0x80, param_4);
    uVar1 = PS2_ADDR(func_00372D70(0));
    func_002C4C50(16.0f, (char *)PS2_PTR(uVar1), param_1 + 0xB, param_2 + 0x54, 0x54, param_4, 0, 6);
}

/* 0x0029CA20, 0x90 bytes. */
void func_0029CA20(int param_1, u8 *param_2, u8 *param_3)
{
    int bVar1;

    func_0029C800();
    bVar1 = *param_3;
    if ((int)(u32)param_3[1] < *(int *)(param_2 + (u32)bVar1 * 4)) {
        func_0029C9E0(param_1, *(u32 *)
                                                    ((u32)param_3[1] * 4 + ((u32)bVar1 * 0x10 - (u32)bVar1) * 8 + param_2 +
                                                    0x180), param_3[4] == 1, param_3[0x59]);
    }
}

/* 0x002A5080, 0xB0 bytes. */
void func_002A5080(u8 *param_1, u8 *param_2, int param_3)
{
    if (*(int *)(param_2 + 0x30) == *(int *)(param_1 + 100)) {
        *(u32 *)(param_1 + 100) = 0xFF;
    }
    func_0023ACC0(*(u32 *)(param_2 + 0x30), param_3);
    if (0xF2 < *(u32 *)(param_2 + 0x2C)) {
        func_002A5B10();
    }
    *(u32 *)(param_2 + 0x2C) = 0x107;
    if (0 < *(int *)(param_1 + 0x54)) {
        *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + -1;
    }
    if (0 < *(u32 *)g_0077BEF4) {
        *(u32 *)(g_0077BEF4) = *(u32 *)(g_0077BEF4) + -1;
    }
}

/* 0x002AA0C0, 0x88 bytes. */
void func_002AA0C0(int param_1)
{
    int iVar2;
    u8 * puVar1;

    func_002CB550(param_1, 0, 0, 0, 0, 0x200, 0x180, 0);
    iVar2 = 0;
    puVar1 = g_00411E70;
    do {
        func_002CB500(PS2_ADDR(puVar1));
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x1C;
    } while (iVar2 < 2);
}

/* 0x002AAE10, 0x2C8 bytes. */
void func_002AAE10(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    u8 auStack_30[44];
    float fStack_3c;
    float fStack_40;
    int iVar3;
    int iVar7;
    int iVar8;
    float * pfVar1;
    float * pfVar2;
    float * pfVar6;
    int uStack_1;
    int uStack_2;
    int uStack_3;
    int uStack_4;
    unsigned long long uVar4;
    unsigned long long uVar5;

    uVar4 = func_0029FC40(param_6);
    iVar3 = (int)uVar4;
    do {
        iVar3 = iVar3 / 10;
    } while (0 < iVar3);
    if (param_7 == 0) {
        func_002C80A0(param_2, param_3, 0, param_4, param_5, 0x80, param_8);
    }
    else {
        func_002C8500(param_2, param_3, 0, param_4, param_5, 0x80, param_8);
    }
    uStack_4 = 0x80;
    uStack_3 = 0x80;
    pfVar2 = (float *)0x10;
    uStack_1 = g_0045CEBB;
    uStack_2 = 0x80;
    pfVar6 = &fStack_40;
    pfVar1 = pfVar6;
    while (pfVar1 != (float *)0) {
        *(u8 *)pfVar6 = 0;
        pfVar6 = (float *)((int)pfVar6 + 1);
        pfVar2 = (float *)((int)pfVar2 + -1);
        pfVar1 = pfVar2;
    }
    iVar8 = (int)param_2;
    fStack_40 = (float)(iVar8 + 0x10);
    iVar7 = (int)param_3;
    fStack_3c = (float)iVar7;
    iVar3 = PS2_ADDR(func_0019FBC0(param_6));
    uVar5 = func_002D07A0(*(u8 *)((u8 *)PS2_PTR(iVar3) + 5));
    func_001ABCE0(0.3076923191547394f, 0.2750000059604645f, (u8 *)PS2_PTR(param_1), uVar5, &fStack_40, (u32 *)(&uStack_4), param_8, 0);
    *(u32 *)(g_0056CCA4) = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    uVar5 = PS2_ADDR(func_003DD440((int)param_6 + 0x10));
    func_00146B40((u8 *)PS2_PTR(uVar5), iVar8 + 0x34, iVar7 + 3, 0x70, 0x10, param_8, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)(g_0056CCA4) = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
    func_001204B0(auStack_30, 0x441230, uVar4);
    func_002C5020(16.0f, (char *)(auStack_30), iVar8 + 0xD8, iVar7 + 3, param_8, 0, 6);
    func_002A85F0(0x18, iVar8 + 0xD8, iVar7 + 3, 0, param_8, 0x80);
    *(u32 *)(g_0056CCA4 + 0x14) = 1;
}

/* 0x00380EB0, 0x4E0 bytes. */
void func_00380EB0(float param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    u8 auStack_10[16];
    int bVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar7;
    long long lVar6;
    unsigned long long uVar5;

    func_00380A40(param_1, param_2, param_3, param_4, 1, 0, 1);
    iVar2 = func_002F3770(param_3);
    iVar7 = iVar2 + (int)((float)param_6 * param_1);
    if (iVar7 < iVar2) {
        iVar7 = iVar2;
    }
    if (iVar7 < 0) {
        iVar7 = 0;
    }
    iVar3 = func_002F38F0(param_3);
    if (iVar3 <= iVar7) {
        iVar7 = func_002F38F0(param_3);
    }
    iVar3 = func_002F38F0(param_3);
    if (iVar3 <= iVar2 + param_6) {
        func_002F38F0(param_3);
    }
    uVar5 = func_002F38F0(param_3);
    func_001204B0(auStack_10, 0x459568, iVar7, uVar5);
    func_002C4F40(14.0f, (char *)(auStack_10), param_4 + 0x54, param_5 + 0x61, 1, 0, 6);
    iVar3 = func_002F38F0(param_3);
    iVar4 = func_002F38F0(param_3);
    func_001A85D0((float)iVar2 / (float)iVar3, (float)iVar7 / (float)iVar4, 1.0f, param_4 + 0x54,
                              param_5 + 0x70, 0, 4, 0xB, 0x5C, 1);
    iVar7 = func_002F39F0(param_3);
    func_001A85D0((float)iVar7 / 350.0, 0, 1.0f, param_4 + 0x54, param_5 + 0x84, 0, 6, 0, 0x5C, 1);
    uVar5 = func_002F39F0(param_3);
    func_001204B0(auStack_10, 0x459570, uVar5);
    func_002C4F40(14.0f, (char *)(auStack_10), param_4 + 0xB8, param_5 + 0x81, 1, 0, 6);
    iVar7 = func_002F4C40(param_3);
    func_001A85D0((float)iVar7 / 350.0, 0, 1.0f, param_4 + 0x54, param_5 + 0x96, 0, 7, 0, 0x5C, 1);
    uVar5 = func_002F4C40(param_3);
    func_001204B0(auStack_10, 0x459570, uVar5);
    func_002C4F40(14.0f, (char *)(auStack_10), param_4 + 0xB8, param_5 + 0x93, 1, 0, 6);
    iVar7 = func_002F4DD0(param_3);
    func_001A85D0((float)iVar7 / 250.0, 0, 1.0f, param_4 + 0x54, param_5 + 0xA8, 0, 8, 0, 0x5C, 1);
    uVar5 = func_002F4DD0(param_3);
    func_001204B0(auStack_10, 0x459570, uVar5);
    func_002C4F40(14.0f, (char *)(auStack_10), param_4 + 0xB8, param_5 + 0xA5, 1, 0, 6);
    iVar7 = func_002F4F60(param_3);
    func_001A85D0((float)iVar7 / 250.0, 0, 1.0f, param_4 + 0x54, param_5 + 0xBA, 0, 9, 0, 0x5C, 1);
    uVar5 = func_002F4F60(param_3);
    func_001204B0(auStack_10, 0x459570, uVar5);
    func_002C4F40(14.0f, (char *)(auStack_10), param_4 + 0xB8, param_5 + 0xB7, 1, 0, 6);
    bVar1 = false;
    if ((399 < param_3) && (param_3 < 0x19F)) {
        bVar1 = true;
    }
    if ((bVar1) || ((param_3 < 400 || 0x19E < param_3 && (lVar6 = func_003A0040(param_3), lVar6 != 0)))
          ) {
        func_003B5930(param_4 + 0x3C, param_5 + 0x3C, 0, 1);
    }
    lVar6 = func_00327870();
    if (param_3 == lVar6) {
        param_4 = param_4 + 0x54;
        iVar7 = 0;
        do {
            func_003B5300(iVar7, param_4, param_5 + 200, 0, 1);
            iVar7 = iVar7 + 1;
            param_4 = param_4 + 0x16;
        } while (iVar7 < 4);
    }
    else {
        uVar5 = func_002F5AA0(param_3);
        func_003B5300(uVar5, param_4 + 0x54, param_5 + 200, 0, 1);
    }
}

/* 0x003819E0, 0x2B8 bytes. */
void func_003819E0(int param_1, int param_2, int param_3, int param_4)
{
    u8 auStack_20[32];
    int iVar1;
    unsigned long long uVar2;

    func_00380A40(param_1, param_2, param_3, param_4, 1, 0, 0);
    uVar2 = func_002F39F0(param_2);
    func_001204B0(auStack_20, 0x459570, uVar2);
    func_002C4F40(14.0f, (char *)(auStack_20), param_3 + 0xB8, param_4 + 0x81, 1, 0, 6);
    iVar1 = func_002F39F0(param_2);
    func_001A85D0((float)iVar1 / 350.0, 0, 1.0f, param_3 + 0x54, param_4 + 0x84, 0, 6, 0, 0x5C, 1);
    uVar2 = func_002F4C40(param_2);
    func_001204B0(auStack_20, 0x459570, uVar2);
    func_002C4F40(14.0f, (char *)(auStack_20), param_3 + 0xB8, param_4 + 0x93, 1, 0, 6);
    iVar1 = func_002F4C40(param_2);
    func_001A85D0((float)iVar1 / 350.0, 0, 1.0f, param_3 + 0x54, param_4 + 0x96, 0, 7, 0, 0x5C, 1);
    uVar2 = func_002F4DD0(param_2);
    func_001204B0(auStack_20, 0x459570, uVar2);
    func_002C4F40(14.0f, (char *)(auStack_20), param_3 + 0xB8, param_4 + 0xA5, 1, 0, 6);
    iVar1 = func_002F4DD0(param_2);
    func_001A85D0((float)iVar1 / 250.0, 0, 1.0f, param_3 + 0x54, param_4 + 0xA8, 0, 8, 0, 0x5C, 1);
    uVar2 = func_002F4F60(param_2);
    func_001204B0(auStack_20, 0x459570, uVar2);
    func_002C4F40(14.0f, (char *)(auStack_20), param_3 + 0xB8, param_4 + 0xB7, 1, 0, 6);
    iVar1 = func_002F4F60(param_2);
    func_001A85D0((float)iVar1 / 250.0, 0, 1.0f, param_3 + 0x54, param_4 + 0xBA, 0, 9, 0, 0x5C, 1);
    uVar2 = func_002F5AA0(param_2);
    func_003B5300(uVar2, param_3 + 0x54, param_4 + 200, 0, 1);
}

/* 0x003BD940, 0x54C bytes. */
void func_003BD940(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int aiStack_50[16];
    u8 auStack_10[16];
    int iVar4;
    u8 * iVar5;
    int * piVar10;
    int * piVar6;
    int * piVar7;
    int * piVar9;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;
    u32 uVar8;

    aiStack_50[0xC] = *(u32 *)g_0041C410;
    aiStack_50[0xD] = *(u32 *)(g_0041C410 + 0x4);
    aiStack_50[0xE] = *(u32 *)(g_0041C410 + 0x8);
    aiStack_50[0xF] = *(u32 *)(g_0041C410 + 0xC);
    aiStack_50[8] = *(u32 *)(g_0041C410 + 0x10);
    aiStack_50[9] = *(u32 *)(g_0041C410 + 0x14);
    aiStack_50[10] = *(u32 *)(g_0041C410 + 0x18);
    aiStack_50[0xB] = *(u32 *)(g_0041C410 + 0x1C);
    aiStack_50[4] = *(u32 *)(g_0041C410 + 0x20);
    aiStack_50[5] = *(u32 *)(g_0041C410 + 0x24);
    aiStack_50[6] = *(u32 *)(g_0041C410 + 0x28);
    aiStack_50[7] = *(u32 *)(g_0041C410 + 0x2C);
    aiStack_50[0] = *(u32 *)(g_0041C410 + 0x30);
    aiStack_50[1] = *(u32 *)(g_0041C410 + 0x34);
    aiStack_50[2] = *(u32 *)(g_0041C410 + 0x38);
    aiStack_50[3] = *(u32 *)(g_0041C410 + 0x3C);
    func_002C7310();
    uVar1 = PS2_ADDR(func_00105860(4, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F57);
    iVar5 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar5 + 0x18) = uVar2;
    *(unsigned long long *)(iVar5 + 0x20) = (long long)(int)(param_5 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar5 + 0x28) = 0x7880908;
    *(unsigned long long *)(iVar5 + 0x38) = 0x8F80A78;
    uVar3 = (long long)(0xFFFE - param_3) << 0x20;
    iVar4 = (((param_2 + 8) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              uVar3 | (long long)((param_1 + 0x7A) * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar4 = (((param_2 + 0x20) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              uVar3 | (long long)((param_1 + 0x92) * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar1), param_4);
    uVar8 = 0;
    piVar7 = aiStack_50 + 0xC;
    piVar6 = aiStack_50 + 8;
    piVar9 = aiStack_50 + 4;
    piVar10 = aiStack_50;
    do {
        iVar4 = *piVar7;
        if (uVar8 == 0) {
            uVar1 = PS2_ADDR(func_00362A20(0));
            func_002C4E40(16.0f, (char *)PS2_PTR(uVar1), param_1 + iVar4, param_2 + piVar7[1], 0x68, param_4, 0, 3);
        }
        else {
            if (uVar8 == 0) {
                *(u32 *)(g_0056CCA4) = 3;
                *(u32 *)(g_0056CCA4 + 0x4) = 3;
                *(u32 *)(g_0056CCA4 + 0x8) = 3;
                *(u32 *)(g_0056CCA4 + 0xC) = 3;
            }
            else {
                *(u32 *)(g_0056CCA4) = 1;
                *(u32 *)(g_0056CCA4 + 0x4) = 1;
                *(u32 *)(g_0056CCA4 + 0x8) = 1;
                *(u32 *)(g_0056CCA4 + 0xC) = 1;
            }
            *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
            *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
            uVar1 = PS2_ADDR(func_00362A20(uVar8));
            func_00146B40((u8 *)PS2_PTR(uVar1), param_1 + iVar4, param_2 + piVar7[1], 0x68, 0x10, param_4, 0);
            *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
            *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
            *(u32 *)(g_0056CCA4) = 5;
            *(u32 *)(g_0056CCA4 + 0x4) = 5;
            *(u32 *)(g_0056CCA4 + 0x8) = 5;
            *(u32 *)(g_0056CCA4 + 0xC) = 5;
        }
        uVar1 = func_00362290(uVar8);
        func_001204B0(auStack_10, 0x45BC40, uVar1);
        if (uVar8 == 0) {
            func_002C5020(16.0f, (char *)(auStack_10), param_1 + *piVar6, param_2 + piVar6[1], param_4, 0, 6);
        }
        else {
            func_002C4F40(16.0f, (char *)(auStack_10), param_1 + *piVar6, param_2 + piVar6[1], param_4, 0, 6);
        }
        func_003E3520(param_1 + *piVar9, param_2 + piVar9[1], 0, 0x3C, 4, param_4, uVar8, uVar1);
        uVar1 = func_00362660(uVar8);
        func_003B4F50(uVar8, uVar1, param_1 + *piVar10, param_2 + piVar10[1], 0, param_4);
        uVar8 = uVar8 + 1;
        piVar7 = piVar7 + 2;
        piVar6 = piVar6 + 2;
        piVar9 = piVar9 + 2;
        piVar10 = piVar10 + 2;
    } while (uVar8 < 2);
}
/* MISSING ['0x41c410', '0x41c414', '0x41c418', '0x41c41c', '0x41c420', '0x41c424', '0x41c428', '0x41c42c', '0x41c430', '0x41c434', '0x41c438', '0x41c43c', '0x41c440', '0x41c444', '0x41c448', '0x41c44c'] */

/* 0x003EF980, 0x208 bytes. */
void func_003EF980(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int bVar1;
    int iVar3;
    int iVar4;
    u32 uVar2;

    uVar2 = 10000;
    iVar4 = 0;
    bVar1 = false;
    iVar3 = param_4;
    do {
        if (((int)uVar2 <= param_2) || (bVar1)) {
            func_003EF930(param_1, param_2 / (int)uVar2, iVar3, param_5, param_6, param_7);
            bVar1 = true;
        }
        param_2 = param_2 % (int)uVar2;
        uVar2 = (int)uVar2 / 10 + ((int)uVar2 >> 0x1F);
        if (uVar2 < 2) {
            uVar2 = 1;
        }
        if ((iVar4 == 3) && (param_2 == 0)) {
            bVar1 = true;
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 8;
    } while (iVar4 < 5);
    func_003EF930(param_1, 10, param_4 + 0x28, param_5, param_6, param_7);
    uVar2 = 10000;
    bVar1 = false;
    iVar3 = 0;
    param_4 = param_4 + 0x30;
    do {
        if (((int)uVar2 <= param_3) || (bVar1)) {
            func_003EF930(param_1, param_3 / (int)uVar2, param_4, param_5, param_6, param_7);
            bVar1 = true;
        }
        param_3 = param_3 % (int)uVar2;
        uVar2 = (int)uVar2 / 10 + ((int)uVar2 >> 0x1F);
        if (uVar2 < 2) {
            uVar2 = 1;
        }
        if ((iVar3 == 3) && (param_2 == 0)) {
            bVar1 = true;
        }
        iVar3 = iVar3 + 1;
        param_4 = param_4 + 8;
    } while (iVar3 < 5);
}

/* 0x003EFB90, 0x11C bytes. */
void func_003EFB90(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int bVar1;
    int iVar3;
    u32 uVar2;

    uVar2 = 100;
    bVar1 = false;
    iVar3 = 0;
    do {
        if (((int)uVar2 <= param_2) || (bVar1)) {
            func_003EF930(param_1, param_2 / (int)uVar2, param_3, param_4, param_5, param_6);
            bVar1 = true;
        }
        param_2 = param_2 % (int)uVar2;
        uVar2 = (int)uVar2 / 10 + ((int)uVar2 >> 0x1F);
        if (uVar2 < 2) {
            uVar2 = 1;
        }
        if ((iVar3 == 1) && (param_2 == 0)) {
            bVar1 = true;
        }
        iVar3 = iVar3 + 1;
        param_3 = param_3 + 8;
    } while (iVar3 < 3);
}
