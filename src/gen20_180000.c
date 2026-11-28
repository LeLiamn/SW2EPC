/*
 * gen20_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
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
int func_002CD2C0();

#define true 1
#define false 0

extern u8 g_00424EF0[0x24];
extern u8 g_004281BD[0x4];
extern u8 g_0043C120[0x400];
extern u8 g_0043C524[0x4];
extern u8 g_0043C534[0x4];
extern u8 g_00441F60[0x4];
extern u8 g_0056CCA4[0x24];
extern u8 g_00669DB8[0x4];
extern u8 g_00669FA4[0x4];
extern u8 g_0068F0F0[0x8];
extern u8 g_0068F0F8[0x8];
extern u8 g_00730A20[0x4];
extern u8 g_00730A40[0x4];
extern u8 g_0073C79A[0x4];
extern u8 g_0076F62F[0x1];
extern u8 g_00799A68[0x4];
extern u8 g_007B4E60[0x10];
extern u8 g_007BAE74[0x4];
extern int g_0045D1C8;   /* (small data) */
extern int g_0045D3E0;   /* (small data) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))   /* (scratchpad) */

int func_001204B0();
void func_001C7F30(int k, float *pos, int c, u32 f);
int func_001FF100();
int func_0027C210();
int func_002F7D90();
int func_0039C490();

/* 0x001D0970, 0x1AC bytes. */
void func_001D0970(u8 *param_1)
{
    u8 * iVar2;
    int iVar4;
    long long lVar1;
    u32 uStack_10;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;
    unsigned long long uVar3;

    iVar2 = param_1;
    if ((((*(int *)(iVar2 + 0x11C) != 0) && (*(char *)(iVar2 + 0x181) == 0)) &&
            (2 < *(int *)(iVar2 + 0x118) - 0x3dU)) && (-1 < (long long)*(char *)(iVar2 + 0x19C) << 0x38)) {
        iVar4 = 0x18B;
        if ((*(u32 *)g_00669DB8 == 4) || (*(u32 *)g_00669DB8 == 2)) {
            iVar4 = 0xDB;
        }
        else {
            if ((*(u32 *)g_00669FA4 - 2U < 2) && (lVar1 = func_00190610(iVar2 + 0x40, 0x100), lVar1 == 0)) {
                iVar4 = 0xDD;
            }
            if (iVar4 == 0x18B) {
                switch(*(u8 *)(iVar2 + 0xD4)) {
                case 0:
                case 7:
                case 8:
                case 10:
                case 0xE:
                    iVar4 = 0xDB;
                    break;
                case 1:
                    iVar4 = 0xDC;
                    break;
                case 2:
                    iVar4 = 0xDF;
                    break;
                case 4:
                    iVar4 = 0xDE;
                    break;
                case 5:
                case 0xB:
                    iVar4 = 0xE1;
                    break;
                case 6:
                    iVar4 = 0xE0;
                }
            }
        }
        lVar1 = func_0016C040(param_1);
        if (lVar1 == 0) {
            uVar3 = 0;
        }
        else {
            uVar3 = 0x200;
        }
        if (iVar4 != 0x18B) {
            if (iVar4 - 0xe1U < 2) {
                uStack_10 = *(u32 *)(iVar2 + 0x40);
                uStack_8 = *(u32 *)(iVar2 + 0x48);
                uStack_4 = *(u32 *)(iVar2 + 0x4C);
                uStack_c = *(u32 *)(iVar2 + 0xE4);
                g_70000D60 = 0;
                func_001C7F30(iVar4, (float *)(&uStack_10), 0, uVar3);
            }
            else {
                g_70000D60 = 0;
                func_001C7F30(iVar4, (float *)(iVar2 + 0x40), 0, uVar3);
            }
        }
    }
}

/* 0x001DA490, 0x324 bytes. */
void func_001DA490(u32 *param_1)
{
    u8 auStack_2[2];
    int iVar3;
    int iVar6;
    long long lVar5;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_4;
    u32 uStack_8;
    u32 uVar4;

    puVar1 = (u8 *)PS2_PTR(param_1[4]);
    param_1[4] = (u32)PS2_ADDR((puVar1 + 1));
    puVar2 = (u8 *)PS2_PTR(param_1[5]);
    param_1[5] = (u32)PS2_ADDR((puVar2 + 1));
    uVar4 = func_001D6BD0((unsigned int *)(auStack_2), (unsigned int *)PS2_PTR(param_1[3]), *puVar1, *puVar2);
    param_1[3] = uVar4;
    puVar1 = (u8 *)PS2_PTR(param_1[4]);
    param_1[4] = (u32)PS2_ADDR((puVar1 + 1));
    puVar2 = (u8 *)PS2_PTR(param_1[5]);
    param_1[5] = (u32)PS2_ADDR((puVar2 + 1));
    uVar4 = func_001D6BD0((unsigned int *)(&uStack_4), (unsigned int *)PS2_PTR(param_1[3]), *puVar1, *puVar2);
    param_1[3] = uVar4;
    puVar1 = (u8 *)PS2_PTR(param_1[4]);
    param_1[4] = (u32)PS2_ADDR((puVar1 + 1));
    puVar2 = (u8 *)PS2_PTR(param_1[5]);
    param_1[5] = (u32)PS2_ADDR((puVar2 + 1));
    uVar4 = func_001D6BD0(&uStack_8, (unsigned int *)PS2_PTR(param_1[3]), *puVar1, *puVar2);
    param_1[3] = uVar4;
    *(u8 *)(param_1 + 0x14) = auStack_2[0];
    switch(uStack_4) {
    case 0:
        param_1[6] = 1 << (*(u8 *)PS2_PTR((*(u8 *)(g_0073C79A + 0x3) + 0x73C79E)) & 0x1F);
        break;
    case 1:
        param_1[6] = 1 << (*(u8 *)PS2_PTR((*(u8 *)(g_0073C79A + 0x3) + 0x73C79B)) & 0x1F);
        break;
    case 2:
        param_1[6] = 0xFFFFFFFF;
        break;
    case 3:
        param_1[6] = (u32)(*(u8 *)g_0073C79A);
        break;
    case 4:
        if ((*param_1 & 0x10) == 0) {
            lVar5 = func_001D6CB0(uStack_8);
            if (lVar5 == 0) {
                uVar4 = 0;
            }
            else {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar4 = (int)(g_7000015C >> 0x10) % (int)lVar5;
            }
            uVar4 = 1 << (uVar4 & 0x1F);
            param_1[6] = uVar4;
            iVar6 = g_0045D3E0 * 0x174;
            iVar3 = *(int *)(g_00730A40 + iVar6);
            *(int *)(g_00730A40 + iVar6) = iVar3 + 1;
            *(u32 *)(g_00730A20 + iVar6 + iVar3 * 4) = uVar4;
        }
        else {
            iVar6 = g_0045D3E0 * 0x174;
            iVar3 = *(int *)(g_00730A40 + iVar6);
            *(int *)(g_00730A40 + iVar6) = iVar3 + 1;
            param_1[6] = *(u32 *)(g_00730A20 + iVar6 + iVar3 * 4);
        }
        break;
    case 5:
        if ((*param_1 & 0x10) == 0) {
            if (uStack_8 + 1 == 0) {
                uVar4 = 0;
                param_1[6] = 0;
            }
            else {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar4 = (int)(g_7000015C >> 0x10) % (int)(uStack_8 + 1);
                param_1[6] = uVar4;
            }
            iVar6 = g_0045D3E0 * 0x174;
            iVar3 = *(int *)(g_00730A40 + iVar6);
            *(int *)(g_00730A40 + iVar6) = iVar3 + 1;
            *(u32 *)(g_00730A20 + iVar6 + iVar3 * 4) = uVar4;
        }
        else {
            iVar6 = g_0045D3E0 * 0x174;
            iVar3 = *(int *)(g_00730A40 + iVar6);
            *(int *)(g_00730A40 + iVar6) = iVar3 + 1;
            param_1[6] = *(u32 *)(g_00730A20 + iVar6 + iVar3 * 4);
        }
        break;
    case 6:
        param_1[6] = uStack_8;
    }
}

/* 0x001F63A0, 0x144 bytes. */
void func_001F63A0(u8 *param_1, int param_2, int param_3, int param_4, int param_5)
{
    int bVar2;
    int cVar1;
    int iVar6;
    int iVar7;
    long long lVar4;
    int uVar3;
    u32 uVar5;

    cVar1 = func_001FF100(*(u16 *)(param_1 + 0x54), 3);
    if (cVar1 == -1) {
        switch(param_5) {
        case 5:
            param_5 = 1;
            break;
        case 6:
            param_5 = 2;
            break;
        case 7:
            param_5 = 3;
            break;
        case 9:
            param_5 = 0;
        }
    }
    *(u8 *)(param_1 + 0x61) = param_5;
    if ((*(u32 *)g_00669DB8 != 2) && (param_2 == 0)) {
        bVar2 = func_00194950(param_3, param_4);
        uVar5 = (u32)bVar2;
        if (uVar5 != 8) {
            iVar7 = (int)param_3 + (g_00424EF0)[uVar5];
            iVar6 = (int)param_4 + ((g_00424EF0 + 0x20))[uVar5];
            lVar4 = func_001942E0(iVar7, iVar6);
            if (lVar4 != 0) {
                *(u8 *)(param_1 + 0x62) = bVar2;
                uVar3 = func_00194990(iVar7, iVar6);
                *(u8 *)(param_1 + 99) = uVar3;
            }
        }
    }
}

/* 0x00201F80, 0x80 bytes, matching. */
void func_00201F80(u8 *param_1)
{
    switch(*(u8 *)PS2_PTR((*(int *)(param_1 + 0x68) + 0x1C))) {
    case 8:
    case 0xC:
    case 0xD:
    case 0xF:
        func_002B0180(param_1, 0);
        return;
    case 9:
    case 10:
    case 0xB:
        func_002B1040(param_1, 0);
        break;
    case 0x10:
        func_0027CA60(param_1, 0);
        break;
    case 0x11:
        func_0027C210(param_1, 1);
    }
}

/* 0x00287360, 0x158 bytes. */
void func_00287360(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    u8 auStack_20[32];
    float fVar3;
    int iVar1;
    int iVar2;

    func_002CD2C0(0, 0);
    iVar2 = (int)param_6;
    func_002CD2C0(2, 0, param_3 + iVar2, param_4, param_5, param_6, param_7, param_8);
    func_001204B0(auStack_20, PS2_PTR(0x4407C8), param_1);
    if ((long long)param_6 < 0) {
        fVar3 = (float)(param_6 & 0xFFFFFFFF);
    }
    else {
        fVar3 = (float)iVar2;
    }
    func_002C4F40(fVar3, (char *)(auStack_20), param_3 + iVar2 * 2, param_4, param_9, 0, 6);
    iVar1 = func_001A2970(param_1);
    func_002CD2C0(1, 0, param_3 + iVar2 * (iVar1 + 2), param_4, param_5, param_6, param_7, param_8);
}

/* 0x002B5870, 0x120 bytes. */
void func_002B5870(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    int aiStack_10[4];
    u8 * iVar1;
    int iVar4;
    int * piVar3;
    unsigned long long uVar2;

    uVar2 = (u32)(func_00104E70(param_1 + *(int *)(param_1 + 8) *
                                                                  *(int *)(((u32)param_2 & 0xFF) * 8 + param_1 + 0x10),0x1D00,0x3FFC
                                              , param_9));
    iVar4 = 0;
    piVar3 = aiStack_10;
    do {
        iVar1 = func_00105860(uVar2, 0);
        *piVar3 = PS2_ADDR(iVar1);
        iVar4 = iVar4 + 1;
        *(unsigned long long *)(iVar1 + 0x18) = uVar2;
        piVar3 = piVar3 + 1;
    } while (iVar4 < 3);
    func_002B55E0((unsigned char *)PS2_PTR(aiStack_10[0]), param_2, param_3, param_4, param_5, param_6, param_7, param_8);
    iVar4 = 0;
    piVar3 = aiStack_10;
    do {
        func_00105900((unsigned char *)PS2_PTR(*piVar3), param_9);
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
    } while (iVar4 < 3);
}

/* 0x002CC190, 0x3C8 bytes. */
void func_002CC190(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10)
{
    u8 * iVar1;
    int iVar2;
    int iVar3;
    int iVar6;
    int iVar7;
    int iVar8;
    unsigned long long uVar4;
    unsigned long long uVar5;

    uVar4 = PS2_ADDR(func_00105860(param_2, 0));
    iVar1 = (u8 *)PS2_PTR((int)uVar4);
    *(unsigned long long *)(iVar1 + 0x20) = (long long)param_8 << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar1 + 0x28) = 0x80008;
    *(long long *)(iVar1 + 0x38) =
              (long long)(int)((*(u16 *)(param_1 + 0x14) - 1) * 0x10 | 8) |
              (long long)(int)((*(u16 *)(param_1 + 0x16) - 1) * 0x10 | 8) << 0x10;
    if (param_6 == 0xFFFFFFFFFFFFFFFF) {
        param_6 = (unsigned long long)*(u16 *)(param_1 + 0x14);
    }
    if (param_7 == 0xFFFFFFFFFFFFFFFF) {
        param_7 = (unsigned long long)*(u16 *)(param_1 + 0x16);
    }
    iVar6 = (int)param_7;
    iVar8 = (int)param_6;
    if (param_10 == 0) {
        uVar5 = (long long)(0xFFFE - param_5) << 0x20;
        iVar2 = ((param_4 * 0x280) / 0x1E0) * 0x1C0;
        if (iVar2 < 0) {
            iVar2 = iVar2 + 0x1FF;
        }
        *(unsigned long long *)(iVar1 + 0x30) =
                  uVar5 | (long long)(param_3 * 0x10 + 0x7000) |
                                  (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
        iVar6 = (((iVar6 + param_4) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar6 < 0) {
            iVar6 = iVar6 + 0x1FF;
        }
        *(unsigned long long *)(iVar1 + 0x40) =
                  uVar5 | (long long)((iVar8 + param_3) * 0x10 + 0x7000) |
                                  (long long)(((iVar6 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    }
    else {
        iVar2 = iVar6;
        if ((long long)param_7 < 0) {
            iVar2 = iVar6 + 1;
        }
        iVar3 = iVar8;
        if ((long long)param_6 < 0) {
            iVar3 = iVar8 + 1;
        }
        uVar5 = (long long)(0xFFFE - param_5) << 0x20;
        iVar7 = (((param_4 - (iVar2 >> 1)) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar7 < 0) {
            iVar7 = iVar7 + 0x1FF;
        }
        *(unsigned long long *)(iVar1 + 0x30) =
                  uVar5 | (long long)((param_3 - (iVar3 >> 1)) * 0x10 + 0x7000) |
                                  (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
        iVar6 = ((((iVar6 + param_4) - (iVar2 >> 1)) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar6 < 0) {
            iVar6 = iVar6 + 0x1FF;
        }
        *(unsigned long long *)(iVar1 + 0x40) =
                  uVar5 | (long long)(((iVar8 + param_3) - (iVar3 >> 1)) * 0x10 + 0x7000) |
                                  (long long)(((iVar6 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    }
    func_00105900((unsigned char *)PS2_PTR(uVar4), param_9);
}

/* 0x002CD080, 0x23C bytes. */
void func_002CD080(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    int iVar1;
    int iVar5;
    u8 * iVar6;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    iVar1 = *(int *)(g_00441F60 + param_2 * 4);
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F0, iVar1 + 0x3EE3);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F0, iVar1 + 0x3EE3);
    iVar6 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar6 + 0x18) = uVar3;
    *(unsigned long long *)(iVar6 + 0x20) = (long long)param_8 << 0x18 | 0x3F80000000808080;
    func_002CCDB0(param_1, (unsigned char *)PS2_PTR(uVar2));
    iVar1 = ((param_4 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    uVar4 = (long long)(0xFFFE - param_5) << 0x20;
    *(unsigned long long *)(iVar6 + 0x30) =
              uVar4 | (long long)(param_3 * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar5 = ((param_7 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar6 + 0x40) =
              uVar4 | (long long)((param_6 + param_3) * 0x10 + 0x7000) |
                              (long long)((((iVar5 >> 9) + (iVar1 >> 9)) * 0x10 + -0xE00) / g_70000154 + 0x8000) <<
                              0x10;
    func_00105900((unsigned char *)PS2_PTR(uVar2), param_9);
}

/* 0x002D0540, 0x25C bytes. */
void func_002D0540(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12, int param_13, int param_14)
{
    int iVar2;
    int iVar5;
    int iVar6;
    long long lVar4;
    int uVar1;
    unsigned long long uVar3;

    if (param_14 != 0) {
        param_11 = param_11 + 0x10;
    }
    func_002C80A0(param_4, param_5, param_6, param_7, param_8, param_9, param_10);
    if (param_13 == 1) {
        func_002C8500(param_4, param_5, param_6, param_7, param_8, param_9, param_10);
    }
    iVar6 = (int)param_4;
    iVar5 = (int)param_5;
    if (param_12 == 1) {
        func_002CE160(param_1, iVar6 + 8, iVar5 + 1, 0x18, 0x18, param_9, 0);
    }
    if (param_3 == 0) {
        func_002CE030(param_2, iVar6 + 0x20, param_5, 0x20, 0x16, 0, param_11 & 0xFF);
    }
    else if (param_3 == 1) {
        iVar2 = func_002CDF40(param_11);
        func_002CBEC0((int)param_2 + iVar2, iVar6 + 0x20, iVar5 + 1, 0, 0x20, 0x16, param_10, 0x80);
    }
    *(u32 *)g_0056CCA4 = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    uVar3 = PS2_ADDR(func_003DD440(param_11));
    func_00146B40((const unsigned char *)PS2_PTR(uVar3), iVar6 + 0x44, iVar5 + 3, 0x70, 0x10, 0, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)g_0056CCA4 = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
    uVar1 = func_003DD550(param_11);
    func_002CE110(param_1, iVar6 + 0xB8, iVar5 + 1, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0, uVar1);
    lVar4 = func_003DD4F0(param_11);
    if (3 < lVar4) {
        *(u32 *)(g_0056CCA4 + 0x14) = 1;
    }
}

/* 0x00324340, 0x370 bytes. */
void func_00324340(int param_1, int param_2, u32 *param_3, int param_4, u8 *param_5, int *param_6, u32 *param_7, u8 *param_8, int *param_9, u8 *param_10, int *param_11)
{
    int bVar2;
    int iStack_40;
    int iStack_60;
    int iVar3;
    int iVar4;
    int iVar5;
    long long lVar10;
    long long lVar11;
    long long lVar7;
    long long lVar9;
    u32 * puStack_10;
    u32 uVar1;
    unsigned long long uVar12;
    unsigned long long uVar13;
    unsigned long long uVar6;
    unsigned long long uVar8;

    uVar6 = func_00327D50();
    lVar7 = func_002FB3B0(uVar6);
    *param_9 = 0;
    iVar3 = -1;
    iStack_60 = 0;
    iStack_40 = 0;
    *param_11 = 0;
    *param_7 = 0x19F;
    puStack_10 = param_3;
    if (0 < param_4) {
        do {
            bVar2 = false;
            uVar1 = *puStack_10;
            uVar8 = func_002F4080(uVar1);
            lVar9 = func_002FB2A0(uVar8);
            if ((lVar9 != 0) && (iVar3 == -1)) {
                iVar3 = func_002FB430((int)uVar6);
            }
            lVar10 = func_002F3E70(uVar1);
            if (lVar10 == 0) {
                uVar12 = func_002F7160(uVar1);
                uVar13 = func_002F9190(param_1);
                if (uVar13 < uVar12) {
                    bVar2 = true;
                }
                else {
                    if (lVar9 != 0) {
                        iVar4 = param_4;
                        if (param_4 < iVar3) {
                            iVar4 = iVar3;
                        }
                        if (iStack_60 + (iVar4 - param_4) < 3) {
                            bVar2 = true;
                            goto LAB_003245c0;
                        }
                    }
                    iVar4 = func_002F7D90(0, 0x2F80C0, param_2, 0, 1, 0);
                    iVar5 = func_002F7D90(0, 0x2F8110, param_2, 0, 0, 0);
                    lVar10 = func_002F3F20(uVar1);
                    if ((lVar10 == 0) && (iVar5 < iVar4)) {
                        iVar4 = iVar5;
                    }
                    if (iVar4 < 3) {
                        func_00309C30(uVar1, param_1, param_2);
                        func_002F9130(param_1, (u32)uVar12 / 10);
                        if (lVar9 != 0) {
                            *(u32 *)(param_8 + *param_9 * 4) = uVar1;
                            *param_9 = *param_9 + 1;
                        }
                    }
                    else {
                        bVar2 = true;
                    }
                }
            }
            else {
                lVar10 = func_0030CB00(3);
                if (((lVar9 == 0) || (lVar11 = func_00327A60(), lVar11 == 0)) || (lVar10 < 2)) {
                    bVar2 = true;
                }
                else {
                    *param_7 = uVar1;
                }
            }
LAB_003245c0:
            if (bVar2) {
                if (lVar9 == 0) {
                    func_003097D0(uVar1);
                }
                else {
                    *(u32 *)(param_10 + *param_11 * 4) = uVar1;
                    *param_11 = *param_11 + 1;
                    lVar9 = func_003097D0(uVar1);
                    if (lVar9 == 0) {
                        if (lVar7 == 0) {
                            func_002F7410(uVar1);
                        }
                        else {
                            iVar4 = *param_6;
                            *param_6 = iVar4 + 1;
                            *(u32 *)(param_5 + iVar4 * 4) = uVar1;
                        }
                    }
                    iStack_60 = iStack_60 + 1;
                }
            }
            puStack_10 = puStack_10 + 1;
            iStack_40 = iStack_40 + 1;
        } while (iStack_40 < param_4);
    }
}

/* 0x0032F8A0, 0xB0 bytes. */
void func_0032F8A0(void)
{
    long long lVar1;
    unsigned long long uVar2;

    uVar2 = 0;
    lVar1 = func_0032F780();
    if (lVar1 < 0x1B) {
        switch((int)lVar1) {
        case 0xC:
        case 0xD:
        case 0xE:
        case 0x10:
        case 0x11:
        case 0x12:
            uVar2 = 0x26;
            break;
        case 0x14:
            lVar1 = func_003C1850();
            if (lVar1 == 0) {
                uVar2 = 0x25;
            }
            else {
                uVar2 = 0x2A;
            }
            break;
        case 0x15:
        case 0x16:
            uVar2 = 0x25;
            break;
        case 0x17:
            uVar2 = 0x27;
            break;
        case 0x18:
            uVar2 = 0x2A;
            break;
        case 0x19:
            uVar2 = 0x17;
            break;
        case 0x1A:
            uVar2 = 0xD;
        }
        func_0017E010(uVar2);
    }
}

/* 0x003315E0, 0x130 bytes. */
void func_003315E0(int param_1)
{
    unsigned long long uVar1;
    unsigned long long uVar2;
    u8 * uVar3;

    uVar3 = g_007B4E60;
    switch(param_1) {
    case 6:
        uVar3 = func_00390760(0xCE);
        break;
    case 7:
        uVar3 = func_00390760(0xD4);
        break;
    case 8:
        uVar3 = func_00390760(0xDA);
        break;
    case 9:
        uVar3 = func_00390760(0xE0);
        break;
    case 10:
        uVar3 = func_00390760(0xE6);
        break;
    case 0xB:
        uVar3 = func_00390760(0xEC);
        break;
    case 0xC:
        uVar3 = func_00390760(0xFA);
        break;
    case 0xD:
        uVar3 = func_00390760(0xF4);
        break;
    case 0xE:
        uVar3 = func_00390760(0x100);
        break;
    case 0xF:
        uVar3 = func_00390760(0x106);
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        uVar1 = PS2_ADDR(func_00390760(0x119));
        uVar2 = func_00331010();
        uVar2 = PS2_ADDR(func_0030CB80(uVar2));
        func_001204B0(g_007B4E60, PS2_PTR(uVar1), uVar2);
        break;
    default:
        goto switchD_00331618_default;
    }
    func_00374EE0(PS2_ADDR(uVar3));
switchD_00331618_default:
    ;
}

/* 0x00331720, 0x130 bytes. */
void func_00331720(int param_1)
{
    unsigned long long uVar1;
    unsigned long long uVar2;
    u8 * uVar3;

    uVar3 = g_007B4E60;
    switch(param_1) {
    case 6:
        uVar3 = func_00390760(0xD0);
        break;
    case 7:
        uVar3 = func_00390760(0xD6);
        break;
    case 8:
        uVar3 = func_00390760(0xDC);
        break;
    case 9:
        uVar3 = func_00390760(0xE2);
        break;
    case 10:
        uVar3 = func_00390760(0xE8);
        break;
    case 0xB:
        uVar3 = func_00390760(0xEE);
        break;
    case 0xC:
        uVar3 = func_00390760(0xFC);
        break;
    case 0xD:
        uVar3 = func_00390760(0xF6);
        break;
    case 0xE:
        uVar3 = func_00390760(0x102);
        break;
    case 0xF:
        uVar3 = func_00390760(0x108);
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        uVar1 = PS2_ADDR(func_00390760(0x11C));
        uVar2 = PS2_ADDR(func_00372480(param_1 + -0x10));
        func_001204B0(g_007B4E60, PS2_PTR(uVar1), uVar2);
        break;
    default:
        goto switchD_0033175c_default;
    }
    func_00374EE0(PS2_ADDR(uVar3));
switchD_0033175c_default:
    ;
}

/* 0x00331860, 0x130 bytes. */
void func_00331860(int param_1)
{
    unsigned long long uVar1;
    unsigned long long uVar2;
    u8 * uVar3;

    uVar3 = g_007B4E60;
    switch(param_1) {
    case 6:
        uVar3 = func_00390760(0xD1);
        break;
    case 7:
        uVar3 = func_00390760(0xD7);
        break;
    case 8:
        uVar3 = func_00390760(0xDD);
        break;
    case 9:
        uVar3 = func_00390760(0xE3);
        break;
    case 10:
        uVar3 = func_00390760(0xE9);
        break;
    case 0xB:
        uVar3 = func_00390760(0xEF);
        break;
    case 0xC:
        uVar3 = func_00390760(0xFD);
        break;
    case 0xD:
        uVar3 = func_00390760(0xF7);
        break;
    case 0xE:
        uVar3 = func_00390760(0x103);
        break;
    case 0xF:
        uVar3 = func_00390760(0x109);
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        uVar1 = PS2_ADDR(func_00390760(0x11B));
        uVar2 = func_00331010();
        uVar2 = PS2_ADDR(func_0030CB80(uVar2));
        func_001204B0(g_007B4E60, PS2_PTR(uVar1), uVar2);
        break;
    default:
        goto switchD_00331898_default;
    }
    func_00374EE0(PS2_ADDR(uVar3));
switchD_00331898_default:
    ;
}

/* 0x003319A0, 0x138 bytes. */
void func_003319A0(int param_1)
{
    unsigned long long uVar1;
    unsigned long long uVar2;
    u8 * uVar3;

    uVar3 = g_007B4E60;
    switch(param_1) {
    case 6:
        uVar3 = func_00390760(0xCF);
        break;
    case 7:
        uVar3 = func_00390760(0xD5);
        break;
    case 8:
        uVar3 = func_00390760(0xDB);
        break;
    case 9:
        uVar3 = func_00390760(0xE1);
        break;
    case 10:
        uVar3 = func_00390760(0xE7);
        break;
    case 0xB:
        uVar3 = func_00390760(0xED);
        break;
    case 0xC:
        uVar3 = func_00390760(0xFB);
        break;
    case 0xD:
        uVar3 = func_00390760(0xF5);
        break;
    case 0xE:
        uVar3 = func_00390760(0x101);
        break;
    case 0xF:
        uVar3 = func_00390760(0x107);
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        uVar1 = PS2_ADDR(func_00390760(0x11A));
        uVar2 = PS2_ADDR(func_00372480(param_1 + -0x10));
        func_001204B0(g_007B4E60, PS2_PTR(uVar1), uVar2);
        break;
    default:
        goto switchD_003319dc_default;
    }
    func_00375140(0x100, 200, 0, PS2_ADDR(uVar3));
switchD_003319dc_default:
    ;
}

/* 0x00391A10, 0xF0 bytes. */
void func_00391A10(void)
{
    u8 * iVar1;
    u8 * iVar2;
    int iVar3;

    iVar1 = func_00391250();
    iVar3 = 0;
    iVar2 = iVar1;
    do {
        *(u16 *)(iVar2 + 0x9C) = 0xFFFF;
        iVar3 = iVar3 + 7;
        *(u16 *)(iVar2 + 0xF0) = 0xFFFF;
        *(u16 *)(iVar2 + 0x9E) = 0xFFFF;
        *(u16 *)(iVar2 + 0xF2) = 0xFFFF;
        *(u16 *)(iVar2 + 0xA0) = 0xFFFF;
        *(u16 *)(iVar2 + 0xF4) = 0xFFFF;
        *(u16 *)(iVar2 + 0xA2) = 0xFFFF;
        *(u16 *)(iVar2 + 0xF6) = 0xFFFF;
        *(u16 *)(iVar2 + 0xA4) = 0xFFFF;
        *(u16 *)(iVar2 + 0xF8) = 0xFFFF;
        *(u16 *)(iVar2 + 0xA6) = 0xFFFF;
        *(u16 *)(iVar2 + 0xFA) = 0xFFFF;
        *(u16 *)(iVar2 + 0xA8) = 0xFFFF;
        *(u16 *)(iVar2 + 0xFC) = 0xFFFF;
        iVar2 = iVar2 + 0xE;
    } while (iVar3 < 0x2A);
    *(u16 *)(iVar1 + 0x144) = 0;
    switch(*(u32 *)(iVar1 + 0xC)) {
    case 0:
        *(u16 *)(iVar1 + 0x144) = 0xC;
        break;
    case 1:
        *(u16 *)(iVar1 + 0x144) = 0x15;
        break;
    case 2:
        *(u16 *)(iVar1 + 0x144) = 0x14;
        break;
    case 3:
        *(u16 *)(iVar1 + 0x144) = 9;
        break;
    case 4:
        *(u16 *)(iVar1 + 0x144) = 0x29;
        break;
    case 5:
        *(u16 *)(iVar1 + 0x144) = 1;
        break;
    default:
        goto switchD_00391a9c_default;
    }
    func_00391910();
switchD_00391a9c_default:
    ;
}

/* 0x0039C540, 0xE8 bytes, matching. */
void func_0039C540(int param_1)
{
    u8 * iVar2;
    u32 * puVar1;

    iVar2 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar2 + 0x6AC));
    *puVar1 = (int)param_1;
    puVar1[1] = 0;
    switch(param_1) {
    case 1:
        func_0039BC80();
        goto LAB_0039c610;
    case 2:
        func_0039BCB0();
        break;
    case 3:
        func_0039BCE0();
        break;
    case 4:
        func_0039BD40();
        break;
    case 5:
        func_0039C410();
        break;
    case 6:
        func_0039BFC0();
        break;
    case 7:
        func_0039C1A0();
        break;
    case 8:
        func_0039C2C0();
        break;
    case 9:
        func_0039C3E0();
    }
LAB_0039c610:
    func_0039C490(param_1);
}

/* 0x003AF220, 0x7C bytes. */
void func_003AF220(void)
{
    switch(*(u32 *)g_007BAE74) {
    case 1:
        func_003AEC60();
        return;
    case 2:
    case 3:
    case 4:
        func_003AF040();
        break;
    case 6:
        func_003AF1B0();
        break;
    case 7:
        func_003AF1D0();
    }
}

/* 0x003BC6B0, 0x9C bytes. */
void func_003BC6B0(int param_1, int param_2)
{
    unsigned long long uVar1;

    switch(param_1) {
    case 6:
    case 7:
        uVar1 = 0x19;
        break;
    case 8:
    case 9:
        uVar1 = 0x1A;
        break;
    case 10:
    case 0xB:
        uVar1 = 0x1B;
        break;
    case 0xC:
    case 0xD:
        uVar1 = 0x1C;
        break;
    case 0xE:
    case 0xF:
        uVar1 = 0x1D;
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        func_003BA8F0(3, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    default:
        goto switchD_003bc6dc_default;
    }
    func_003BA8F0(uVar1, param_1 + -6, param_2 != 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
switchD_003bc6dc_default:
    ;
}
