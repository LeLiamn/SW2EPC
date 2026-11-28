/*
 * gen18_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_007BABE0[0x18];
extern u8 g_007BAC0C[0x18];
extern u8 g_007BFB20[0x18];
extern u8 g_007BFB3C[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_001EC650();

#define true 1
#define false 0

extern u8 g_00411590[0x4];
extern u8 g_004593A8[0x400];
extern u8 g_00669F60[0x4];
extern u8 g_00669F9C[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_006939DC[0x4];
extern u8 g_006939F0[0x4];
extern u8 g_006AA574[0x4];
extern u8 g_00730DE0[0x4];
extern u8 g_00730DE4[0x4];
extern u8 g_00730DE8[0x4];
extern u8 g_00730DF0[0x4];
extern u8 g_00730DF4[0x4];
extern u8 g_00730E14[0x4];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007BA8B0[0x10];
extern u8 g_007BAA64[0x4];
extern u8 g_007BAC00[0x14];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern u8 g_007BFB30[0x14];
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_70000130 (*(int *)PS2_PTR(0x70000130))   /* (scratchpad) */
#define g_70000134 (*(int *)PS2_PTR(0x70000134))   /* (scratchpad) */
#define g_70000138 (*(int *)PS2_PTR(0x70000138))   /* (scratchpad) */
#define g_7000013C (*(int *)PS2_PTR(0x7000013C))   /* (scratchpad) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_700001D0 (*(int *)PS2_PTR(0x700001D0))   /* (scratchpad) */
#define g_700001D4 (*(int *)PS2_PTR(0x700001D4))   /* (scratchpad) */
#define g_700001E0 (*(int *)PS2_PTR(0x700001E0))   /* (scratchpad) */

int func_001EC5C0();
int func_001FF100();
int func_0022A000();
int func_0022A010();
int func_0022A1F0();
int func_00254470();
int func_00254880();
int func_002DCFA0();
int func_002ED150();
int func_002ED160();
int func_002EE5E0();
void *func_0030D7D0();
int func_00347F20();
int func_0037EB40();
int func_00381CA0();
int func_00388710();
int func_003890A0();

/* 0x001EC790, 0x164 bytes. */
void func_001EC790(void)
{
    int bVar2;
    int iStack_4;
    int iVar4;
    int iVar5;
    u32 uVar1;
    unsigned long long uVar3;
    u32 uVar6;
    u32 uVar7;

    iStack_4 = 0;
    uVar3 = func_00102360(48000, (void *)PS2_PTR(0x1BB750), &iStack_4);
    uVar7 = 0;
    uVar6 = *(u32 *)g_006AA574;
    do {
        if (iStack_4 != 0) break;
        iVar4 = uVar6 * 0x88;
        iVar5 = iVar4 + 0x693970;
        if (uVar6 < 0x1AC) {
            uVar6 = uVar6 + 1;
        }
        else {
            uVar6 = 0;
        }
        uVar1 = *(u32 *)(g_006939F0 + iVar4);
        bVar2 = false;
        if (((uVar1 & 1) != 0) && ((uVar1 & 0x8C40002) == 0)) {
            bVar2 = true;
        }
        if (bVar2) {
            if ((uVar1 & 0x10C1B0) == 0) {
                if ((uVar1 & 0x20000) == 0) {
                    func_001EC5C0(iVar5);
                }
                else {
                    func_001EC620(iVar5);
                }
            }
            else if ((uVar1 & 0x40) != 0) {
                func_001EC620(iVar5);
            }
            func_001EC650((unsigned char *)PS2_PTR(iVar5));
            *(u32 *)(g_006939DC + iVar4) = (*(u32 *)(g_00669F9C));
        }
        uVar7 = uVar7 + 1;
    } while (uVar7 < 0x1AD);
    *(u32 *)g_006AA574 = uVar6;
    func_00102340((void *)PS2_PTR(uVar3));
}

/* 0x0020A7E0, 0x184 bytes. */
int func_0020A7E0(int *param_1, float *param_2, int param_3)
{
    float fVar6;
    float fVar7;
    u8 * iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;

    if ((param_3 & 1) == 0) {
        iVar5 = 0;
        iVar2 = 2;
        iVar3 = 2;
    }
    else {
        iVar5 = 2;
        iVar3 = 0;
        iVar2 = 0;
    }
    iVar1 = (u8 *)PS2_PTR(*param_1);
    iVar4 = iVar3 * 4;
    fVar6 = param_2[iVar3];
    fVar7 = *(float *)(iVar1 + iVar4);
    if (fVar7 < fVar6) {
        iVar3 = param_1[1];
        iVar2 = iVar2 + 4;
        fVar6 = (fVar7 - fVar6) / (*(float *)((u8 *)PS2_PTR(iVar3) + iVar4) - fVar7);
    }
    else {
        fVar6 = (param_2 + iVar3)[4];
        if (fVar7 <= fVar6) {
            return 8;
        }
        iVar3 = param_1[1];
        fVar6 = (fVar6 - fVar7) / (*(float *)((u8 *)PS2_PTR(iVar3) + iVar4) - fVar7);
    }
    fVar7 = *(float *)(iVar1 + iVar5 * 4);
    fVar6 = fVar6 * (*(float *)((u8 *)PS2_PTR(iVar3) + iVar5 * 4) - fVar7) + fVar7 + 0.0f;
    if (param_3 == 0) {
        fVar6 = param_2[4] - fVar6;
    }
    else if (param_3 == 1) {
        fVar6 = param_2[6] - fVar6;
    }
    else if (param_3 == 2) {
        fVar6 = fVar6 - *param_2;
    }
    else {
        fVar6 = fVar6 - param_2[2];
    }
    fVar6 = param_2[5] + (fVar6 * (param_2[5] - param_2[1])) / (param_2[iVar5] - (param_2 + iVar5)[4])
    ;
    if ((*(float *)(iVar1 + 4) < fVar6) && (*(float *)((u8 *)PS2_PTR(iVar3) + 4) < fVar6)) {
        iVar2 = 8;
    }
    return iVar2;
}

/* 0x0022A6B0, 0xC4 bytes. */
void func_0022A6B0(int param_1, int param_2)
{
    int bVar1;
    int bVar2;
    int iVar3;
    int * piVar4;
    u32 uVar5;

    piVar4 = (int *)PS2_PTR(param_1);
    if (param_2 != 0) {
        bVar1 = *(u8 *)PS2_PTR(param_2);
        if ((bVar1 < 0x20) && (bVar2 = ((u8 *)PS2_PTR(param_2))[1], bVar2 < 0x20)) {
            uVar5 = *(u32 *)PS2_PTR((*(int *)PS2_PTR((*piVar4 + 4)) + ((u32)bVar1 + (u32)bVar2 * 0x20) * 4));
            goto LAB_0022a718;
        }
    }
    uVar5 = 0;
LAB_0022a718:
    func_0022A000(piVar4 + 0x1C, uVar5);
    func_0022A000(piVar4 + 0x88);
    func_0022A1F0(piVar4 + 0xC, piVar4 + 0x1C, piVar4 + 0x88, 0);
    piVar4[2] = 0;
    piVar4[3] = 0;
    func_0022A200((int *)PS2_PTR(param_1), (unsigned char *)(piVar4 + 0xC));
    iVar3 = func_00229E50(piVar4[3], (unsigned char *)PS2_PTR(0x229F60));
    piVar4[3] = iVar3;
}

/* 0x0022A900, 0xC4 bytes. */
void func_0022A900(int param_1, int param_2)
{
    int bVar1;
    int bVar2;
    int iVar3;
    int * piVar4;
    u32 uVar5;

    piVar4 = (int *)PS2_PTR(param_1);
    if (param_2 != 0) {
        bVar1 = *(u8 *)PS2_PTR(param_2);
        if ((bVar1 < 0x20) && (bVar2 = ((u8 *)PS2_PTR(param_2))[1], bVar2 < 0x20)) {
            uVar5 = *(u32 *)PS2_PTR((*(int *)PS2_PTR((*piVar4 + 4)) + ((u32)bVar1 + (u32)bVar2 * 0x20) * 4));
            goto LAB_0022a968;
        }
    }
    uVar5 = 0;
LAB_0022a968:
    func_0022A000(piVar4 + 0x1C, uVar5);
    func_0022A010(piVar4 + 0xAC);
    func_0022A1F0(piVar4 + 0xC, piVar4 + 0x1C, piVar4 + 0xAC, 0);
    piVar4[2] = 0;
    piVar4[3] = 0;
    func_0022A200((int *)PS2_PTR(param_1), (unsigned char *)(piVar4 + 0xC));
    iVar3 = func_00229E50(piVar4[3], (unsigned char *)PS2_PTR(0x229F60));
    piVar4[3] = iVar3;
}

/* 0x002911C0, 0x484 bytes. */
void func_002911C0(void)
{
    int aiStack_30[12];
    int iVar1;
    int iVar10;
    int iVar13;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    int iVar7;
    int iVar9;
    int * piVar11;
    int * piVar12;
    unsigned long long uVar8;

    iVar13 = 0;
    piVar12 = aiStack_30;
    do {
        uVar8 = PS2_ADDR(func_001050F0());
        *(unsigned long long *)PS2_PTR(((int)uVar8 + 0x10)) = 0x8000000044;
        *(unsigned long long *)PS2_PTR(((int)uVar8 + 0x18)) = 0x43;
        func_00105390((unsigned char *)PS2_PTR(uVar8));
        uVar8 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F55);
        iVar7 = PS2_ADDR(func_00105860(uVar8, 0));
        *piVar12 = iVar7;
        uVar8 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F55);
        iVar13 = iVar13 + 1;
        *(unsigned long long *)PS2_PTR((*piVar12 + 0x18)) = uVar8;
        piVar12 = piVar12 + 1;
    } while (iVar13 < 0xC);
    iVar13 = 0;
    piVar11 = (int *)(g_00411590);
    piVar12 = aiStack_30;
    do {
        if (piVar11[8] == 0) {
            iVar7 = piVar11[7];
            iVar9 = piVar11[5];
            iVar1 = piVar11[6];
            iVar2 = piVar11[1];
            iVar3 = piVar11[4];
            iVar4 = piVar11[3];
            iVar5 = piVar11[2];
            iVar10 = *piVar11;
            iVar6 = (u8 *)PS2_PTR(*piVar12);
            *(unsigned long long *)(iVar6 + 0x20) = 0x3F80000080808080;
            *(long long *)(iVar6 + 0x28) =
                      (long long)(int)(iVar3 << 4 | 8) | (long long)(int)((iVar9 + 0x48) * 0x10 | 8) << 0x10;
            *(long long *)(iVar6 + 0x38) =
                      (long long)(int)((iVar1 + -1 + iVar3) * 0x10 | 8) |
                      (long long)(int)((iVar7 + -1 + iVar9 + 0x48) * 0x10 | 8) << 0x10;
            iVar7 = ((iVar2 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar7 < 0) {
                iVar7 = iVar7 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x30) =
                      (long long)(iVar10 * 0x10 + 0x7000) |
                      (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar7 = (((iVar4 + iVar2) * 0x280) / 0x1E0) * 0x1C0;
            if (iVar7 < 0) {
                iVar7 = iVar7 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x40) =
                      (long long)((iVar5 + iVar10) * 0x10 + 0x7000) |
                      (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
        }
        else {
            iVar7 = piVar11[1];
            iVar9 = piVar11[7];
            iVar1 = piVar11[6];
            iVar2 = piVar11[4];
            iVar3 = piVar11[5];
            iVar4 = piVar11[3];
            iVar5 = piVar11[2];
            iVar10 = *piVar11;
            iVar6 = (u8 *)PS2_PTR(*piVar12);
            *(unsigned long long *)(iVar6 + 0x20) = 0x3F80000080808080;
            *(long long *)(iVar6 + 0x28) =
                      (long long)(int)(iVar2 << 4 | 8) | (long long)(int)((iVar3 + 0x48) * 0x10 | 8) << 0x10;
            *(long long *)(iVar6 + 0x38) =
                      (long long)(int)((iVar1 + -1 + iVar2) * 0x10 | 8) |
                      (long long)(int)((iVar9 + -1 + iVar3 + 0x48) * 0x10 | 8) << 0x10;
            iVar10 = iVar10 + iVar5;
            iVar9 = ((iVar7 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar9 < 0) {
                iVar9 = iVar9 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x30) =
                      (long long)(iVar10 * 0x10 + 0x7000) |
                      (long long)(((iVar9 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar7 = (((iVar4 + iVar7) * 0x280) / 0x1E0) * 0x1C0;
            if (iVar7 < 0) {
                iVar7 = iVar7 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x40) =
                      (long long)((iVar10 - iVar5) * 0x10 + 0x7000) |
                      (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
        }
        iVar13 = iVar13 + 1;
        piVar11 = piVar11 + 10;
        piVar12 = piVar12 + 1;
    } while (iVar13 < 0xC);
    iVar13 = 0;
    piVar12 = aiStack_30;
    do {
        func_001059B0((unsigned char *)PS2_PTR(*piVar12));
        iVar13 = iVar13 + 1;
        piVar12 = piVar12 + 1;
    } while (iVar13 < 0xC);
}

/* 0x002DF670, 0x48 bytes. */
void func_002DF670(u8 *param_1)
{
    u8 * iVar1;
    u32 uVar2;

    iVar1 = (u8 *)PS2_PTR(*(int *)(param_1 + 0x10));
    uVar2 = *(u32 *)(param_1 + 0x14);
    func_002DCFA0();
    func_001FD4B0(*(u32 *)(iVar1 + 0x40), uVar2, *((u16 *)PS2_PTR(*(ps2ptr *)(iVar1 + 0x94))), PS2_ADDR(iVar1 + 0x50));
}

/* 0x003820C0, 0x120 bytes. */
void func_003820C0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar2;
    unsigned long long uVar1;

    iVar2 = (int)param_2;
    if (param_5 == 0) {
        func_002C80A0(param_2, param_3, 0, 0xDA, 0x18, 0x80, 1);
    }
    else {
        func_002C8500(param_2, param_3, 0, 0xDA, 0x18, 0x80, 1);
    }
    func_003B5820(param_4, iVar2 + 0x10, param_3, 0, 0x80, 1);
    func_00381CA0(param_1, iVar2 + 0x29, param_3, param_4, 0);
    if (param_4 != 0x65) {
        func_003B5DF0(PS2_ADDR(((u8 *)PS2_PTR(((ps2ptr *)g_004593A8)[(int)param_4]))), iVar2 + 0x84, (int)param_3 + 3, 0, 0x80, 1);
    }
    uVar1 = func_00313F20(param_4);
    func_003B5CA0(uVar1, iVar2 + 0xA8, (int)param_3 + 8, 0, 0x80, 1);
}

/* 0x003853A0, 0x1118 bytes. */
void func_003853A0(void)
{
    u8 * iVar2;
    int iVar7;
    int iVar8;
    int sStack_6;
    int sVar6;
    int uStack_8;
    int uVar1;
    int uVar3;
    int uVar4;
    int uVar5;
    int uVar9;

    iVar2 = (u8 *)(func_00365450());
    iVar7 = *(int *)(iVar2 + 0x48);
    if (iVar7 == 4) {
        func_003B2390((short unsigned int *)(&uStack_8), 1);
        sVar6 = sStack_6 + -0x30;
        *(u16 *)(iVar2 + 0x100) = uStack_8;
        *(short *)(iVar2 + 0x102) = sStack_6;
        *(u16 *)(iVar2 + 0x104) = 0x98;
        *(u16 *)(iVar2 + 0x106) = 0x30;
        *(u16 *)(iVar2 + 0x108) = uStack_8;
        *(short *)(iVar2 + 0x10A) = sStack_6;
        *(u16 *)(iVar2 + 0x10C) = 0x98;
        *(u16 *)(iVar2 + 0x10E) = 0x30;
        *(u8 *)(iVar2 + 0x112) = 0;
        *(u8 *)(iVar2 + 0x113) = 0;
        *(u8 *)(iVar2 + 0x110) = 0x80;
        *(u8 *)(iVar2 + 0x111) = 0x80;
        *(u16 *)(iVar2 + 0x108) = uStack_8;
        *(short *)(iVar2 + 0x10A) = sStack_6 - sVar6;
        *(u16 *)(iVar2 + 0x10C) = 0x98;
        *(u16 *)(iVar2 + 0x10E) = 0x30;
        *(u8 *)(iVar2 + 0x111) = 0x80;
        *(u8 *)(iVar2 + 0x112) = 0xF;
        func_003B2360((short unsigned int *)(&uStack_8), 1);
        *(u16 *)(iVar2 + 0x60) = uStack_8;
        *(short *)(iVar2 + 0x62) = sStack_6;
        *(u16 *)(iVar2 + 100) = 0xE0;
        *(u16 *)(iVar2 + 0x66) = 0x28;
        *(u16 *)(iVar2 + 0x68) = uStack_8;
        *(short *)(iVar2 + 0x6A) = sStack_6;
        *(u16 *)(iVar2 + 0x6C) = 0xE0;
        *(u16 *)(iVar2 + 0x6E) = 0x28;
        *(u8 *)(iVar2 + 0x72) = 0;
        *(u8 *)(iVar2 + 0x73) = 0;
        *(u8 *)(iVar2 + 0x70) = 0x80;
        *(u8 *)(iVar2 + 0x71) = 0x80;
        *(u16 *)(iVar2 + 0x68) = uStack_8;
        *(short *)(iVar2 + 0x6A) = sStack_6 - sVar6;
        *(u16 *)(iVar2 + 0x6C) = 0xE0;
        *(u16 *)(iVar2 + 0x6E) = 0x28;
        *(u8 *)(iVar2 + 0x71) = 0x80;
        *(u8 *)(iVar2 + 0x72) = 0xF;
        func_00383C10((short unsigned int *)(&uStack_8), 1);
        *(u16 *)(iVar2 + 0xB0) = uStack_8;
        *(short *)(iVar2 + 0xB2) = sStack_6;
        *(u16 *)(iVar2 + 0xB4) = 0x50;
        *(u16 *)(iVar2 + 0xB6) = 0x20;
        *(u16 *)(iVar2 + 0xB8) = uStack_8;
        *(short *)(iVar2 + 0xBA) = sStack_6;
        *(u16 *)(iVar2 + 0xBC) = 0x50;
        *(u16 *)(iVar2 + 0xBE) = 0x20;
        *(u8 *)(iVar2 + 0xC2) = 0;
        *(u8 *)(iVar2 + 0xC3) = 0;
        *(u8 *)(iVar2 + 0xC0) = 0x80;
        *(u8 *)(iVar2 + 0xC1) = 0x80;
        *(u16 *)(iVar2 + 0xB8) = uStack_8;
        *(short *)(iVar2 + 0xBA) = sStack_6 - sVar6;
        *(u16 *)(iVar2 + 0xBC) = 0x50;
        *(u16 *)(iVar2 + 0xBE) = 0x20;
        *(u8 *)(iVar2 + 0xC1) = 0x80;
        *(u8 *)(iVar2 + 0xC2) = 0xF;
    }
    else if (iVar7 == 2) {
        iVar7 = 0;
        do {
            if (iVar7 == 0) {
                iVar8 = 0;
            }
            else {
                iVar8 = iVar7 + -1;
            }
            uVar5 = 0x80;
            if (iVar8 == 3) {
                uVar5 = 0x4C;
            }
            else if (iVar8 == 2) {
                uVar5 = 0x60;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar5 = 0x60;
            }
            uVar9 = 0x80;
            if (iVar7 == 3) {
                uVar9 = 0x4C;
            }
            else if (iVar7 == 2) {
                uVar9 = 0x60;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar9 = 0x60;
            }
            func_003B2390((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0x98;
            if (iVar8 == 3) {
                uVar4 = 0x5B;
            }
            else if (iVar8 == 2) {
                uVar4 = 0x72;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0x72;
            }
            uVar3 = 0x30;
            if (iVar8 == 3) {
                uVar3 = 0x1C;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x24;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x24;
            }
            *(u16 *)(iVar2 + 0xEC) = uStack_8;
            *(short *)(iVar2 + 0xEE) = sStack_6;
            *(u16 *)(iVar2 + 0xF0) = uVar4;
            *(u16 *)(iVar2 + 0xF2) = uVar3;
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFE) = 0;
            *(u8 *)(iVar2 + 0xFF) = 0;
            uVar1 = uVar5;
            if (iVar7 == 0) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0xFC) = uVar1;
            uVar1 = uVar5;
            if (iVar7 == 0) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0xFD) = uVar1;
            func_003B2390((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x98;
            if (iVar7 == 3) {
                uVar4 = 0x5B;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x72;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x72;
            }
            uVar3 = 0x30;
            if (iVar7 == 3) {
                uVar3 = 0x1C;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x24;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x24;
            }
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFD) = uVar9;
            *(u8 *)(iVar2 + 0xFE) = 0xF;
            func_003B2360((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0xE0;
            if (iVar8 == 3) {
                uVar4 = 0x86;
            }
            else if (iVar8 == 2) {
                uVar4 = 0xA8;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0xA8;
            }
            uVar3 = 0x28;
            if (iVar8 == 3) {
                uVar3 = 0x18;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x1E;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x1E;
            }
            *(u16 *)(iVar2 + 0x4C) = uStack_8;
            *(short *)(iVar2 + 0x4E) = sStack_6;
            *(u16 *)(iVar2 + 0x50) = uVar4;
            *(u16 *)(iVar2 + 0x52) = uVar3;
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5E) = 0;
            *(u8 *)(iVar2 + 0x5F) = 0;
            uVar1 = uVar5;
            if (iVar7 == 0) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0x5C) = uVar1;
            uVar1 = uVar5;
            if (iVar7 == 0) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0x5D) = uVar1;
            func_003B2360((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0xE0;
            if (iVar7 == 3) {
                uVar4 = 0x86;
            }
            else if (iVar7 == 2) {
                uVar4 = 0xA8;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0xA8;
            }
            uVar3 = 0x28;
            if (iVar7 == 3) {
                uVar3 = 0x18;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x1E;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x1E;
            }
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5D) = uVar9;
            *(u8 *)(iVar2 + 0x5E) = 0xF;
            func_00383C10((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0x50;
            if (iVar8 == 3) {
                uVar4 = 0x30;
            }
            else if (iVar8 == 2) {
                uVar4 = 0x3C;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0x3C;
            }
            uVar3 = 0x20;
            if (iVar8 == 3) {
                uVar3 = 0x13;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x18;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x18;
            }
            *(u16 *)(iVar2 + 0x9C) = uStack_8;
            *(short *)(iVar2 + 0x9E) = sStack_6;
            *(u16 *)(iVar2 + 0xA0) = uVar4;
            *(u16 *)(iVar2 + 0xA2) = uVar3;
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAE) = 0;
            *(u8 *)(iVar2 + 0xAF) = 0;
            uVar1 = uVar5;
            if (iVar7 == 0) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0xAC) = uVar1;
            if (iVar7 == 0) {
                uVar5 = 0;
            }
            *(u8 *)(iVar2 + 0xAD) = uVar5;
            func_00383C10((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x50;
            if (iVar7 == 3) {
                uVar4 = 0x30;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x3C;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x3C;
            }
            uVar3 = 0x20;
            if (iVar7 == 3) {
                uVar3 = 0x13;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x18;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x18;
            }
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            iVar7 = iVar7 + 1;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAD) = uVar9;
            *(u8 *)(iVar2 + 0xAE) = 0xF;
            iVar2 = iVar2 + 0x14;
        } while (iVar7 < 4);
    }
    else if (iVar7 == 1) {
        iVar7 = 0;
        do {
            iVar8 = 3;
            if (iVar7 != 3) {
                iVar8 = iVar7 + 1;
            }
            uVar5 = 0x80;
            if (iVar8 == 3) {
                uVar5 = 0x4C;
            }
            else if (iVar8 == 2) {
                uVar5 = 0x60;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar5 = 0x60;
            }
            uVar9 = 0x80;
            if (iVar7 == 3) {
                uVar9 = 0x4C;
            }
            else if (iVar7 == 2) {
                uVar9 = 0x60;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar9 = 0x60;
            }
            func_003B2390((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0x98;
            if (iVar8 == 3) {
                uVar4 = 0x5B;
            }
            else if (iVar8 == 2) {
                uVar4 = 0x72;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0x72;
            }
            uVar3 = 0x30;
            if (iVar8 == 3) {
                uVar3 = 0x1C;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x24;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x24;
            }
            *(u16 *)(iVar2 + 0xEC) = uStack_8;
            *(short *)(iVar2 + 0xEE) = sStack_6;
            *(u16 *)(iVar2 + 0xF0) = uVar4;
            *(u16 *)(iVar2 + 0xF2) = uVar3;
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFE) = 0;
            *(u8 *)(iVar2 + 0xFF) = 0;
            uVar1 = uVar5;
            if (iVar7 == 3) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0xFC) = uVar1;
            uVar1 = uVar5;
            if (iVar7 == 3) {
                uVar1 = 0;
            }
            *(u8 *)(iVar2 + 0xFD) = uVar1;
            func_003B2390((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x98;
            if (iVar7 == 3) {
                uVar4 = 0x5B;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x72;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x72;
            }
            uVar3 = 0x30;
            if (iVar7 == 3) {
                uVar3 = 0x1C;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x24;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x24;
            }
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFD) = uVar9;
            *(u8 *)(iVar2 + 0xFE) = 0xF;
            func_003B2360((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0xE0;
            if (iVar8 == 3) {
                uVar4 = 0x86;
            }
            else if (iVar8 == 2) {
                uVar4 = 0xA8;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0xA8;
            }
            uVar3 = 0x28;
            if (iVar8 == 3) {
                uVar3 = 0x18;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x1E;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x1E;
            }
            *(u16 *)(iVar2 + 0x4C) = uStack_8;
            *(short *)(iVar2 + 0x4E) = sStack_6;
            *(u16 *)(iVar2 + 0x50) = uVar4;
            *(u16 *)(iVar2 + 0x52) = uVar3;
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5E) = 0;
            *(u8 *)(iVar2 + 0x5F) = 0;
            *(u8 *)(iVar2 + 0x5C) = uVar5;
            *(u8 *)(iVar2 + 0x5D) = uVar5;
            func_003B2360((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0xE0;
            if (iVar7 == 3) {
                uVar4 = 0x86;
            }
            else if (iVar7 == 2) {
                uVar4 = 0xA8;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0xA8;
            }
            uVar3 = 0x28;
            if (iVar7 == 3) {
                uVar3 = 0x18;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x1E;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x1E;
            }
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5D) = uVar9;
            *(u8 *)(iVar2 + 0x5E) = 0xF;
            func_00383C10((short unsigned int *)(&uStack_8), iVar8);
            uVar4 = 0x50;
            if (iVar8 == 3) {
                uVar4 = 0x30;
            }
            else if (iVar8 == 2) {
                uVar4 = 0x3C;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar4 = 0x3C;
            }
            uVar3 = 0x20;
            if (iVar8 == 3) {
                uVar3 = 0x13;
            }
            else if (iVar8 == 2) {
                uVar3 = 0x18;
            }
            else if ((iVar8 != 1) && (iVar8 == 0)) {
                uVar3 = 0x18;
            }
            *(u16 *)(iVar2 + 0x9C) = uStack_8;
            *(short *)(iVar2 + 0x9E) = sStack_6;
            *(u16 *)(iVar2 + 0xA0) = uVar4;
            *(u16 *)(iVar2 + 0xA2) = uVar3;
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAE) = 0;
            *(u8 *)(iVar2 + 0xAF) = 0;
            *(u8 *)(iVar2 + 0xAC) = uVar5;
            *(u8 *)(iVar2 + 0xAD) = uVar5;
            func_00383C10((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x50;
            if (iVar7 == 3) {
                uVar4 = 0x30;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x3C;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x3C;
            }
            uVar3 = 0x20;
            if (iVar7 == 3) {
                uVar3 = 0x13;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x18;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x18;
            }
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            iVar7 = iVar7 + 1;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAD) = uVar9;
            *(u8 *)(iVar2 + 0xAE) = 0xF;
            iVar2 = iVar2 + 0x14;
        } while (iVar7 < 4);
    }
    else if (iVar7 == 3) {
        iVar7 = 0;
        do {
            uVar5 = 0x80;
            if (iVar7 == 3) {
                uVar5 = 0x4C;
            }
            else if (iVar7 == 2) {
                uVar5 = 0x60;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar5 = 0x60;
            }
            func_003B2390((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x98;
            if (iVar7 == 3) {
                uVar4 = 0x5B;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x72;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x72;
            }
            uVar3 = 0x30;
            if (iVar7 == 3) {
                uVar3 = 0x1C;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x24;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x24;
            }
            *(u16 *)(iVar2 + 0xEC) = uStack_8;
            *(short *)(iVar2 + 0xEE) = sStack_6;
            *(u16 *)(iVar2 + 0xF0) = uVar4;
            *(u16 *)(iVar2 + 0xF2) = uVar3;
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFE) = 0;
            *(u8 *)(iVar2 + 0xFF) = 0;
            *(u8 *)(iVar2 + 0xFC) = 0;
            *(u8 *)(iVar2 + 0xFD) = 0;
            *(u16 *)(iVar2 + 0xF4) = uStack_8;
            *(short *)(iVar2 + 0xF6) = sStack_6;
            *(u16 *)(iVar2 + 0xF8) = uVar4;
            *(u16 *)(iVar2 + 0xFA) = uVar3;
            *(u8 *)(iVar2 + 0xFD) = uVar5;
            *(u8 *)(iVar2 + 0xFE) = 0;
            func_003B2360((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0xE0;
            if (iVar7 == 3) {
                uVar4 = 0x86;
            }
            else if (iVar7 == 2) {
                uVar4 = 0xA8;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0xA8;
            }
            uVar3 = 0x28;
            if (iVar7 == 3) {
                uVar3 = 0x18;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x1E;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x1E;
            }
            *(u16 *)(iVar2 + 0x4C) = uStack_8;
            *(short *)(iVar2 + 0x4E) = sStack_6;
            *(u16 *)(iVar2 + 0x50) = uVar4;
            *(u16 *)(iVar2 + 0x52) = uVar3;
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5E) = 0;
            *(u8 *)(iVar2 + 0x5F) = 0;
            *(u8 *)(iVar2 + 0x5C) = 0;
            *(u8 *)(iVar2 + 0x5D) = 0;
            *(u16 *)(iVar2 + 0x54) = uStack_8;
            *(short *)(iVar2 + 0x56) = sStack_6;
            *(u16 *)(iVar2 + 0x58) = uVar4;
            *(u16 *)(iVar2 + 0x5A) = uVar3;
            *(u8 *)(iVar2 + 0x5D) = uVar5;
            *(u8 *)(iVar2 + 0x5E) = 0;
            func_00383C10((short unsigned int *)(&uStack_8), iVar7);
            uVar4 = 0x50;
            if (iVar7 == 3) {
                uVar4 = 0x30;
            }
            else if (iVar7 == 2) {
                uVar4 = 0x3C;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar4 = 0x3C;
            }
            uVar3 = 0x20;
            if (iVar7 == 3) {
                uVar3 = 0x13;
            }
            else if (iVar7 == 2) {
                uVar3 = 0x18;
            }
            else if ((iVar7 != 1) && (iVar7 == 0)) {
                uVar3 = 0x18;
            }
            *(u16 *)(iVar2 + 0x9C) = uStack_8;
            *(short *)(iVar2 + 0x9E) = sStack_6;
            iVar7 = iVar7 + 1;
            *(u16 *)(iVar2 + 0xA0) = uVar4;
            *(u16 *)(iVar2 + 0xA2) = uVar3;
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAE) = 0;
            *(u8 *)(iVar2 + 0xAF) = 0;
            *(u8 *)(iVar2 + 0xAC) = 0;
            *(u8 *)(iVar2 + 0xAD) = 0;
            *(u16 *)(iVar2 + 0xA4) = uStack_8;
            *(short *)(iVar2 + 0xA6) = sStack_6;
            *(u16 *)(iVar2 + 0xA8) = uVar4;
            *(u16 *)(iVar2 + 0xAA) = uVar3;
            *(u8 *)(iVar2 + 0xAD) = uVar5;
            *(u8 *)(iVar2 + 0xAE) = 0;
            iVar2 = iVar2 + 0x14;
        } while (iVar7 < 4);
    }
}

/* 0x0039F590, 0x24C bytes. */
void func_0039F590(void)
{
    int bVar3;
    int iVar10;
    int iVar4;
    int iVar9;
    long long lVar7;
    u8 * pbVar11;
    int * piVar5;
    int sVar1;
    int sVar2;
    unsigned long long uVar6;
    unsigned long long uVar8;

    iVar4 = PS2_ADDR(func_002FC2C0());
    iVar4 = *(int *)((u8 *)PS2_PTR(iVar4) + 0x694);
    uVar6 = func_002EE5E0();
    *(u32 *)(g_007BAC00 + 0x10) = (int)uVar6;
    bVar3 = func_001AE550(*(u32 *)(g_007BAC00 + 0x8), (void *)PS2_PTR(uVar6), (short int *)(g_007BAC00), g_007BAC0C, 0);
    *(u8 *)(g_007BAC00 + 0xD) = *(u8 *)(g_007BAC00 + 0xD) & 0xFE | bVar3 & 1;
    if ((long long)(char)bVar3 << 0x3F < 0) {
        lVar7 = func_002ED160();
        if (lVar7 < 0x18) {
            *(u8 *)(g_007BAC00 + 0xD) = *(u8 *)(g_007BAC00 + 0xD) & 0xFE;
            *(char *)PS2_PTR(((*(u32 *)(g_007BAC00 + 0x10)) + 0x13)) = (char)lVar7;
        }
        else {
            *(u8 *)PS2_PTR(((*(u32 *)(g_007BAC00 + 0x10)) + 0x13)) = 0x18;
        }
    }
    sVar2 = *(short *)(g_007BAC00 + 0x4);
    sVar1 = *(short *)g_007BAC00;
    if (*(int *)((u8 *)PS2_PTR(iVar4) + 0x220) == 1) {
        func_00388710();
        uVar6 = PS2_ADDR(func_0030D7D0());
        uVar8 = func_003890A0();
        func_0037EB40(uVar6, uVar8, *(u32 *)((u8 *)PS2_PTR(iVar4) + 0x214));
        uVar6 = PS2_ADDR(func_0030D7D0());
        uVar8 = func_0031D690((void *)PS2_PTR(iVar4));
        func_0037EAA0(uVar6, uVar8, 0x154, 0x68, 0x80);
    }
    else if (*(int *)((u8 *)PS2_PTR(iVar4) + 0x220) == 0) {
        iVar9 = 0;
        iVar4 = 0;
        piVar5 = (int *)PS2_PTR(0x7BABE0);
        pbVar11 = (u8 *)PS2_PTR((*(u32 *)(g_007BAC00 + 0x10) + 0x13));
        do {
            iVar10 = (int)sVar1 - (int)((int)sVar2 * (iVar4 - (*pbVar11 - 10))) / 10;
            if (0x10 < iVar10) {
                iVar10 = 0x10;
            }
            iVar9 = iVar9 + 1;
            *piVar5 = 0x10 - iVar10;
            iVar4 = iVar4 + 2;
            piVar5 = piVar5 + 1;
        } while (iVar9 < 7);
        lVar7 = func_002ED150();
        func_003889B0((int *)(g_007BABE0), 7, lVar7 == 0);
        if ((long long)(char)(*(u8 *)(g_007BAC00 + 0xD)) << 0x3F < 0) {
            uVar6 = PS2_ADDR(func_0030D7D0());
            uVar8 = func_003890A0();
            func_0037EB40(uVar6, uVar8, 0xFFFFFFFFFFFFFFFF);
        }
    }
}
/* MISSING ['0x7bac08'] */

/* 0x003E7C10, 0x24C bytes. */
void func_003E7C10(void)
{
    int bVar3;
    int iVar10;
    int iVar4;
    int iVar9;
    long long lVar7;
    u8 * pbVar11;
    int * piVar5;
    int sVar1;
    int sVar2;
    unsigned long long uVar6;
    unsigned long long uVar8;

    iVar4 = PS2_ADDR(func_002FC2C0());
    iVar4 = *(int *)((u8 *)PS2_PTR(iVar4) + 0x694);
    uVar6 = func_002EE5E0();
    *(u32 *)(g_007BFB30 + 0x10) = (int)uVar6;
    bVar3 = func_001AE550(*(u32 *)(g_007BFB30 + 0x8), (void *)PS2_PTR(uVar6), (short int *)(g_007BFB30), g_007BFB3C, 0);
    *(u8 *)(g_007BFB30 + 0xD) = *(u8 *)(g_007BFB30 + 0xD) & 0xFE | bVar3 & 1;
    if ((long long)(char)bVar3 << 0x3F < 0) {
        lVar7 = func_002ED160();
        if (lVar7 < 0x12) {
            *(u8 *)(g_007BFB30 + 0xD) = *(u8 *)(g_007BFB30 + 0xD) & 0xFE;
            *(char *)PS2_PTR(((*(u32 *)(g_007BFB30 + 0x10)) + 0x13)) = (char)lVar7;
        }
        else {
            *(u8 *)PS2_PTR(((*(u32 *)(g_007BFB30 + 0x10)) + 0x13)) = 0x12;
        }
    }
    sVar2 = *(short *)(g_007BFB30 + 0x4);
    sVar1 = *(short *)g_007BFB30;
    if (*(int *)((u8 *)PS2_PTR(iVar4) + 0x220) == 1) {
        func_00388710();
        uVar6 = PS2_ADDR(func_0030D7D0());
        iVar9 = func_003890A0();
        func_0037EB40(uVar6, iVar9 + 7, *(u32 *)((u8 *)PS2_PTR(iVar4) + 0x214));
        uVar6 = PS2_ADDR(func_0030D7D0());
        uVar8 = func_0031D690((void *)PS2_PTR(iVar4));
        func_0037EAA0(uVar6, uVar8, 0x154, 0x68, 0x80);
    }
    else if (*(int *)((u8 *)PS2_PTR(iVar4) + 0x220) == 0) {
        iVar9 = 0;
        iVar4 = 0;
        piVar5 = (int *)PS2_PTR(0x7BFB20);
        pbVar11 = (u8 *)PS2_PTR((*(u32 *)(g_007BFB30 + 0x10) + 0x13));
        do {
            iVar10 = (int)sVar1 - (int)((int)sVar2 * (iVar4 - (*pbVar11 - 10))) / 10;
            if (0x10 < iVar10) {
                iVar10 = 0x10;
            }
            iVar9 = iVar9 + 1;
            *piVar5 = 0x10 - iVar10;
            iVar4 = iVar4 + 2;
            piVar5 = piVar5 + 1;
        } while (iVar9 < 4);
        lVar7 = func_002ED150();
        func_003889B0((int *)(g_007BFB20), 4, lVar7 == 0);
        if ((long long)(char)(*(u8 *)(g_007BFB30 + 0xD)) << 0x3F < 0) {
            uVar6 = PS2_ADDR(func_0030D7D0());
            iVar4 = func_003890A0();
            func_0037EB40(uVar6, iVar4 + 7, 0xFFFFFFFFFFFFFFFF);
        }
    }
}
/* MISSING ['0x7bfb38'] */
