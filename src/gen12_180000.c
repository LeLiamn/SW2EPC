/*
 * gen12_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_007A2034[0x18];
#include "sw2e_mem.h"

#define true 1
#define false 0

extern u8 g_004124E0[0x80];
extern u8 g_0056CCA4[0x24];
extern u8 g_0056CCC8[0x4];
extern u8 g_005B4DF0[0x1];
extern u8 g_005B5030[0x1];
extern u8 g_00669F60[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_00730DE0[0x4];
extern u8 g_00730E04[0x4];
extern u8 g_00730E14[0x4];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_00795054[0x4];
extern u8 g_007A22B8[0x8];
extern u8 g_007BAE7C[0x8];
extern u8 g_007BAE88[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_700001DC (*(int *)PS2_PTR(0x700001DC))   /* (scratchpad) */
#define g_7000088C (*(int *)PS2_PTR(0x7000088C))   /* (scratchpad) */
#define g_70000B98 (*(int *)PS2_PTR(0x70000B98))   /* (scratchpad) */

int func_00104AC0();
int func_00104D00();
void *func_00105860();
int func_00105900();
int func_00106C50();
int func_00106C90();
void *func_00106F10();
int func_001204B0();
void *func_00120928();
int func_00146270();
int func_00146B40();
void func_001A85D0(float a, float b, float size, int x, int y, int z, int ia, int ib, int w, int layer);
int func_001ABEA0();
int func_001AE550(float speed, void *window, short *pos, u8 *alpha, int a);
int func_001CEBC0();
int func_001D6BD0();
int func_001FE3E0();
int func_00236FC0();
int func_00237040();
int func_002371C0();
int func_00239830();
void func_002C4C50(float size, char *text, int x, int y, int w, int a, int b, int c);
void func_002C4F40(float s, char *text, int x, int y, int a, int b, int c);
void func_002C5020(float s, char *t, int x, int y, int a, int b, int col);
int func_002C6040();
int func_002C7310();
int func_002C7A30();
int func_002C80A0();
int func_002C8500();
int func_002CA490();
int func_002D2790();
int func_002ED150();
void *func_002F2890();
int func_002F3770();
int func_002F38F0();
int func_002F39F0();
int func_002F4080();
int func_002F41E0();
int func_002F4660();
int func_002F4C40();
int func_002F4DD0();
int func_002F4F60();
int func_002F5AA0();
int func_002F5CC0();
void *func_002F8DB0();
void *func_002F8DE0();
int func_002F8F20();
int func_002F9060();
int func_0030AB90();
void *func_0030ABF0();
void *func_0030D7D0();
void *func_0030E2C0();
int func_00327870();
int func_00327D50();
void *func_00362A20();
void *func_00372650();
int func_00382690();
int func_003A0040();
int func_003B4740();
int func_003B5070();
int func_003B5300();
int func_003B5930();
int func_003B5970();
void *func_003BD290();
int func_003DC180();
int func_003DD7B0();
int func_003EF980();
int func_003EFB90();
void func_001D1D10(u8 *param_1);
int func_001D6C70(u8 *param_1);
void func_001DFA70(u32 *param_1);
void func_001FE540(int param_1);
void func_00237200(u8 *param_1);
void func_00299F60(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002B4E80(u8 *param_1, int *param_2, u16 *param_3, int param_4, int param_5, int param_6, int param_7);
void func_002D2A80(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002EE610(int param_1, int param_2);
void func_002EEB60(int param_1, int param_2);
void func_0037DAD0(int param_1);
void func_0037DDD0(int param_1, int param_2, int param_3, int param_4);
void func_0037FB60(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_003876C0(int param_1, u32 *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_003AECD0(void);
void func_003AEDC0(void);
void func_003F0020(int param_1, int param_2, int param_3, int param_4, int param_5);

/* 0x001D1D10, 0x170 bytes. */
void func_001D1D10(u8 *param_1)
{
    int bVar1;
    int bVar3;
    u32 uVar2;

    uVar2 = *(u32 *)(*(short *)(param_1 + 0x178) * 0xC0 + 0x6A3AE8);
    if ((((uVar2 & 0x200) == 0) && ((uVar2 & 2) != 0)) &&
          (-1 < (long long)*(char *)(param_1 + 0x19F) << 0x3F)) {
        if (((*(int *)(param_1 + 0x288) == 0) && (*(int *)(param_1 + 0x28C) == 0)) &&
              ((*(int *)(param_1 + 0x280) == 0 && (*(int *)(param_1 + 0x284) == 0)))) {
            bVar3 = false;
        }
        else {
            bVar3 = true;
        }
        if ((((!bVar3) && (-1 < (long long)*(char *)(param_1 + 0x19C) << 0x3A)) &&
                (((*(u32 *)g_00669F60 & 0x2800000) == 0 &&
                  ((-1 < (long long)(*(char *)g_005B4DF0) << 0x3F || (-1 < (long long)(*(char *)g_005B4DF0) << 0x3E)))))) &&
              ((-1 < (long long)(*(char *)g_005B5030) << 0x3F || (-1 < (long long)(*(char *)g_005B5030) << 0x3E)))) {
            bVar1 = *(u8 *)(param_1 + 0x19C);
            *(u8 *)(param_1 + 0x19C) = bVar1 & 0xF7;
            *(u8 *)(param_1 + 0x19C) = bVar1 & 0xF3;
            *(u16 *)(param_1 + 300) = 0;
            *(u16 *)(param_1 + 0x12E) = 0;
            func_001CEBC0();
        }
    }
}

/* 0x001D6C70, 0x3C bytes. */
int func_001D6C70(u8 *param_1)
{
    u32 uStack_4;

    func_001D6BD0(&uStack_4, param_1 + (u32)*(u8 *)(param_1 + (u32)*(u8 *)(param_1 + 6) + 7) + 7,
                              *(u8 *)(param_1 + 7));
    return uStack_4;
}

/* 0x001DFA70, 0x1A8 bytes. */
void func_001DFA70(u32 *param_1)
{
    int bVar3;
    int iVar6;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar7;
    int sStack_4;
    int uStack_2;
    u32 uVar4;
    u32 uVar5;

    puVar1 = (u8 *)param_1[4];
    param_1[4] = (u32)(puVar1 + 1);
    puVar2 = (u8 *)param_1[5];
    param_1[5] = (u32)(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, param_1[3], *puVar1, *puVar2);
    param_1[3] = uVar4;
    puVar1 = (u8 *)param_1[4];
    param_1[4] = (u32)(puVar1 + 1);
    puVar2 = (u8 *)param_1[5];
    param_1[5] = (u32)(puVar2 + 1);
    uVar4 = func_001D6BD0(&sStack_4, param_1[3], *puVar1, *puVar2);
    param_1[3] = uVar4;
    if ((*param_1 & 0x10) == 0) {
        if (sStack_4 != 0) {
            *(u32 *)(g_0045D3E0 * 0x174 + 0x730A88) =
                      *(u32 *)(g_0045D3E0 * 0x174 + 0x730A88) | 1 << (uStack_2 & 0x1F);
        }
    }
    else {
        uVar4 = (u32)uStack_2;
        iVar6 = g_0045D3E0 * 0x38;
        if ((int)uVar4 < *(int *)(g_00730E14 + iVar6)) {
            bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar6) + uVar4 * 4) != 0;
        }
        else {
            bVar3 = false;
        }
        if (bVar3) {
            uVar5 = *(u32 *)(*(int *)(g_00730E04 + iVar6) + uVar4 * 4) & 2;
        }
        else {
            uVar5 = 0;
        }
        if (uVar5 != 0) {
            if (sStack_4 == 0) {
                puVar7 = (u32 *)(*(int *)(g_00730E04 + iVar6) + uVar4 * 4);
                *puVar7 = *puVar7 & 0xFFFFFFEF;
            }
            else {
                puVar7 = (u32 *)(*(int *)(g_00730E04 + iVar6) + uVar4 * 4);
                *puVar7 = *puVar7 | 0x10;
            }
        }
    }
}

/* 0x001FE540, 0x110 bytes. */
void func_001FE540(int param_1)
{
    int iVar1;
    int iVar4;
    u32 * puVar2;
    u32 uVar3;
    u32 uVar5;

    uVar3 = 0;
    iVar1 = g_7000088C * 0x70;
    do {
        if ((1 << (uVar3 & 0x1F) & 0xffU & (u32)(u8)(&g_70000B98)[g_7000088C]) != 0) {
            iVar4 = 0;
            puVar2 = (u32 *)PS2_PTR(g_700001DC);
            do {
                uVar5 = 0;
                do {
                    if ((1 << (uVar5 & 0x1F) & *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x70000C80 + iVar4 * 4)) != 0) {
                        func_001FE3E0(*puVar2, uVar3, param_1);
                    }
                    uVar5 = uVar5 + 1;
                    puVar2 = puVar2 + 1;
                } while ((int)uVar5 < 0x19);
                iVar4 = iVar4 + 1;
            } while (iVar4 < 0x19);
        }
        uVar3 = uVar3 + 1;
    } while ((int)uVar3 < 5);
}

/* 0x00237200, 0x9C bytes. */
void func_00237200(u8 *param_1)
{
    int cVar1;
    long long lVar2;

    cVar1 = *(char *)(param_1 + 0x7C);
    if (cVar1 == 3) {
        lVar2 = func_00239830();
        if (lVar2 == 0) {
            func_002371C0(param_1);
        }
    }
    else if (cVar1 == 2) {
        func_002371C0();
    }
    else if (cVar1 == 1) {
        func_00237040();
    }
    else if (cVar1 == 0) {
        func_00236FC0();
    }
}

/* 0x00299F60, 0x204 bytes. */
void func_00299F60(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    u8 auStack_80[128];
    int iVar2;
    int iVar3;
    unsigned long long uVar1;
    u32 uVar4;

    func_002C80A0();
    uVar1 = PS2_ADDR(func_00362A20(0));
    func_00120928(auStack_80, uVar1);
    func_002C4C50(16.0f, (char *)(auStack_80), param_1 + 0x18, param_2 + 4, 0x90, param_4, 0, 3);
    uVar4 = 0;
    iVar3 = 0;
    do {
        iVar2 = param_2 + iVar3 + 0x18;
        func_002C80A0(param_1 + 8, iVar2, param_3, 0xB0, 0x18, 0x80, param_4);
        if (uVar4 == (param_5 & 0xFF)) {
            func_002C8500(param_1 + 8, iVar2, param_3, 0xB0, 0x18, 0x80, param_4);
        }
        *(u32 *)(g_0056CCA4) = 6;
        *(u32 *)(g_0056CCA4 + 0x4) = 6;
        *(u32 *)(g_0056CCA4 + 0x8) = 6;
        *(u32 *)(g_0056CCA4 + 0xC) = 6;
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        uVar1 = func_003DD7B0(uVar4);
        func_00146B40(uVar1, param_1 + 0x2E, iVar2 + 3, 0x7A, 0x10, param_4, 0);
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        uVar4 = uVar4 + 1;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        iVar3 = iVar3 + 0x18;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
    } while ((int)uVar4 < 5);
}

/* 0x002B4E80, 0x754 bytes. */
void func_002B4E80(u8 *param_1, int *param_2, u16 *param_3, int param_4, int param_5, int param_6, int param_7)
{
    float fVar11;
    float fVar12;
    int iVar10;
    int iVar13;
    int iVar2;
    u8 * iVar3;
    u8 * iVar9;
    u32 uVar1;
    unsigned long long uVar4;
    unsigned long long uVar5;
    u32 uVar6;
    unsigned long long uVar7;
    unsigned long long uVar8;

    uVar6 = (*(u32 *)g_00795054 >> 1) + 1;
    uVar1 = param_4;
    if (uVar6 < param_4) {
        uVar1 = uVar6;
    }
    if (*(u32 *)g_00795054 < param_4 * 2 + 10) {
        *(u32 *)(g_00795054) = *(u32 *)(g_00795054) + 1;
    }
    if ((param_7 == 1) && ((int)(param_5 & 0xFF) < (int)param_4)) {
        func_002C6040(*param_3, param_2[(param_5 & 0xFF) * 3 + 1], param_3[2], 0x1C, param_6, 0x80);
    }
    uVar8 = 0;
    if (((uVar1 & 0xFF) != 0) && ((uVar1 & 0xFF) != 0)) {
        iVar10 = 0;
        do {
            if (uVar8 == (param_5 & 0xFF)) {
                fVar11 = 1.0;
            }
            else {
                fVar11 = 0.675;
            }
            fVar11 = fVar11 * 128.0;
            if (2.1474836e+09 <= fVar11) {
                fVar11 = fVar11 - 2.1474836e+09;
            }
            uVar7 = (long long)(int)fVar11 & 0xFF;
            if (param_2[2] == 0xF) {
                fVar12 = (float)*param_2;
                fVar11 = (((float)*param_2 - -258.0) / 10.0) * (float)(*(u32 *)g_00795054 - iVar10) + -258.0;
                if (fVar11 < fVar12) {
                    iVar2 = *(int *)(param_1 + 8);
                }
                else {
                    iVar2 = *(int *)(param_1 + 8);
                    fVar11 = fVar12;
                }
                iVar13 = (int)fVar11;
                iVar9 = param_1 + iVar2 * *(int *)(param_1 + 0x68);
                iVar2 = PS2_ADDR(func_00106F10(iVar9));
                uVar4 = func_00104AC0(iVar9, 0x1D00, 2);
                uVar5 = func_00104D00(iVar9, 0x3FFC, 2);
                uVar4 = func_00106C50(uVar4, uVar5);
                uVar4 = PS2_ADDR(func_00105860(uVar4, 0));
                iVar9 = (u8 *)PS2_PTR((int)uVar4);
                *(unsigned long long *)(iVar9 + 0x20) = uVar7 << 0x10 | uVar7 | uVar7 << 8 | 0x3F80000080000000;
                *(unsigned long long *)(iVar9 + 0x28) = 0x80008;
                *(long long *)(iVar9 + 0x38) =
                          (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar2) + 0x14) - 1) * 0x10 | 8) |
                          (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar2) + 0x16) - 1) * 0x10 | 8) << 0x10;
                *(unsigned long long *)(iVar9 + 0x30) =
                          (long long)((iVar13 + 0x6C) * 0x10 + 0x7000) | (long long)(-0x40 / g_70000154 + 0x8000) << 0x10
                          | 0xFFFE00000000;
                *(unsigned long long *)(iVar9 + 0x40) =
                          (long long)(int)(((u32)*(u16 *)((u8 *)PS2_PTR(iVar2) + 0x14) + iVar13 + 0x6C) * 0x10 + 0x7000) |
                          (long long)((((int)((((*(u16 *)((u8 *)PS2_PTR(iVar2) + 0x16) + 0xBD) * 0x280) / 0x1E0) * 0x1C0) >> 9) *
                                          0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
                func_00105900(uVar4, 2);
            }
            else {
                fVar12 = (float)*param_2;
                fVar11 = (((float)*param_2 - -168.0) / 10.0) * (float)(*(u32 *)g_00795054 - iVar10) + -168.0;
                if (fVar12 <= fVar11) {
                    fVar11 = fVar12;
                }
                iVar13 = (int)fVar11;
            }
            iVar2 = PS2_ADDR(param_1 + *(int *)(param_1 + 8) * *(int *)(param_1 + 0x10 + param_2[2] * 8));
            iVar9 = func_00106F10(iVar2);
            uVar4 = func_00104AC0(iVar2, 0x1D00, param_6);
            uVar5 = func_00104D00(iVar2, 0x3FFC, param_6);
            uVar4 = func_00106C50(uVar4, uVar5);
            uVar4 = PS2_ADDR(func_00105860(uVar4, 0));
            iVar3 = (u8 *)PS2_PTR((int)uVar4);
            *(unsigned long long *)(iVar3 + 0x20) = uVar7 << 0x10 | uVar7 | uVar7 << 8 | 0x3F80000080000000;
            *(unsigned long long *)(iVar3 + 0x28) = 0x80008;
            *(long long *)(iVar3 + 0x38) =
                      (long long)(int)((*(u16 *)(iVar9 + 0x14) - 1) * 0x10 | 8) |
                      (long long)(int)((*(u16 *)(iVar9 + 0x16) - 1) * 0x10 | 8) << 0x10;
            iVar2 = ((param_2[1] * 0x280) / 0x1E0) * 0x1C0;
            if (iVar2 < 0) {
                iVar2 = iVar2 + 0x1FF;
            }
            *(unsigned long long *)(iVar3 + 0x30) =
                      (long long)(iVar13 * 0x10 + 0x7000) |
                      (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar2 = ((int)(((u32)*(u16 *)(iVar9 + 0x16) + param_2[1]) * 0x280) / 0x1E0) * 0x1C0;
            if (iVar2 < 0) {
                iVar2 = iVar2 + 0x1FF;
            }
            *(unsigned long long *)(iVar3 + 0x40) =
                      (long long)(int)(((u32)*(u16 *)(iVar9 + 0x14) + iVar13) * 0x10 + 0x7000) |
                      (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            func_00105900(uVar4, param_6);
            uVar8 = (unsigned long long)((int)uVar8 + 1);
            param_2 = param_2 + 3;
            iVar10 = iVar10 + 2;
        } while ((long long)uVar8 < (long long)((unsigned long long)uVar1 & 0xFFFFFFFF000000FF));
    }
}

/* 0x002D2A80, 0x830 bytes. */
void func_002D2A80(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int aiStack_20[8];
    int iVar1;
    int iVar10;
    int iVar11;
    int iVar4;
    int iVar7;
    int iVar8;
    int iVar9;
    int * piVar12;
    int * piVar13;
    int * piVar2;
    unsigned long long uVar3;
    unsigned long long uVar5;
    unsigned long long uVar6;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F61);
    aiStack_20[0] = PS2_ADDR(func_00105860(uVar3, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F61);
    iVar10 = 1;
    piVar12 = aiStack_20;
    *(unsigned long long *)(aiStack_20[0] + 0x18) = uVar3;
    do {
        piVar12 = piVar12 + 1;
        uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F61);
        iVar1 = PS2_ADDR(func_00105860(uVar3, 0));
        *piVar12 = iVar1;
        uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F61);
        iVar10 = iVar10 + 1;
        *(unsigned long long *)(*piVar12 + 0x18) = uVar3;
    } while (iVar10 < 8);
    iVar7 = (int)param_5 * 0x20;
    piVar12 = (int *)(g_004124E0 + iVar7);
    iVar10 = *piVar12;
    iVar1 = *(int *)((g_004124E0 + 0x4) + iVar7);
    *(unsigned long long *)(aiStack_20[0] + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(aiStack_20[0] + 0x28) = 0x81988;
    iVar8 = (int)param_1;
    *(unsigned long long *)(aiStack_20[0] + 0x38) = 0x5F819F8;
    uVar5 = (unsigned long long)((iVar8 + 0x200) * 0x10 + 0x7000);
    iVar4 = (((param_2 + iVar10) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    uVar6 = (unsigned long long)(iVar8 * 0x10 + 0x7000);
    *(unsigned long long *)(aiStack_20[0] + 0x30) =
              uVar5 | (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
              0xFFFE00000000;
    iVar10 = (((iVar1 + param_2 + iVar10) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar10 < 0) {
        iVar10 = iVar10 + 0x1FF;
    }
    iVar1 = 1;
    piVar2 = (int *)((g_004124E0 + 0x8) + iVar7);
    piVar13 = aiStack_20;
    *(unsigned long long *)(aiStack_20[0] + 0x40) =
              uVar6 | (long long)(((iVar10 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
              0xFFFE00000000;
    do {
        piVar13 = piVar13 + 1;
        iVar10 = *piVar2;
        iVar4 = piVar2[1];
        iVar9 = *piVar13;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x20) = 0x3F80000080808080;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x28) = 0x1D480608;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x38) = 0x1D780678;
        iVar11 = (((param_2 + iVar10) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar11 < 0) {
            iVar11 = iVar11 + 0x1FF;
        }
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x30) =
                  uVar5 | (long long)(((iVar11 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
        iVar10 = (((iVar4 + param_2 + iVar10) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar10 < 0) {
            iVar10 = iVar10 + 0x1FF;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 2;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x40) =
                  uVar6 | (long long)(((iVar10 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
    } while (iVar1 < 4);
    iVar10 = 0;
    piVar2 = aiStack_20;
    uVar5 = (unsigned long long)((iVar8 + 0x1B0) * 0x10 + 0x7000);
    piVar13 = piVar12;
    do {
        iVar1 = piVar13[4];
        iVar4 = piVar2[4];
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x20) = 0x3F80000080808080;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x28) = 0x1D480008;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x38) = 0x1D7805F8;
        iVar9 = (((param_2 + iVar1 + 0x1C) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar9 < 0) {
            iVar9 = iVar9 + 0x1FF;
        }
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x30) =
                  (long long)((iVar8 + 0x210) * 0x10 + 0x7000) |
                  (long long)(((iVar9 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
        iVar1 = (((param_2 + iVar1 + 0x30) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x1FF;
        }
        iVar9 = piVar2[5];
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x40) =
                  uVar5 | (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
        iVar1 = piVar13[4];
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x20) = 0x3F80000080808080;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x28) = 0x1D480608;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x38) = 0x1D780678;
        iVar4 = (((param_2 + iVar1 + 0x1C) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar4 < 0) {
            iVar4 = iVar4 + 0x1FF;
        }
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x30) =
                  uVar5 | (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
        iVar1 = (((param_2 + iVar1 + 0x30) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar1 < 0) {
            iVar1 = iVar1 + 0x1FF;
        }
        iVar10 = iVar10 + 1;
        piVar13 = piVar13 + 2;
        piVar2 = piVar2 + 2;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar9) + 0x40) =
                  uVar6 | (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
    } while (iVar10 < 2);
    iVar10 = 0;
    piVar13 = aiStack_20;
    do {
        func_00105900(*piVar13, param_4);
        iVar10 = iVar10 + 1;
        piVar13 = piVar13 + 1;
    } while (iVar10 < 8);
    if (param_5 < 2) {
        func_002D2790(param_1, param_2 + *piVar12 + *(int *)((g_004124E0 + 0x4) + iVar7) + -0x28, 0, 0x200, 0x28,
                                  0x4421E0, 0, 0x33);
    }
    else if (param_5 == 2) {
        func_002D2790(param_1, param_2 + *(u32 *)(g_004124E0 + 0x48) + *(u32 *)(g_004124E0 + 0x4C) + -0x28, 0, 0x200, 0x28, 0x4421E4, 0, 0x33)
        ;
    }
    else if (param_5 == 3) {
        func_002D2790(param_1, param_2 + *(u32 *)(g_004124E0 + 0x70) + *(u32 *)(g_004124E0 + 0x74) + -0x28, 0, 0x200, 0x28, 0x4421E8, 0, 0x33)
        ;
        func_002D2790(param_1, param_2 + *(u32 *)(g_004124E0 + 0x78) + *(u32 *)(g_004124E0 + 0x7C) + -0x28, 0, 0x200, 0x28, 0x4421E8, 0, 0x33)
        ;
    }
}
/* MISSING ['0x412528', '0x41252c', '0x412550', '0x412554', '0x412558', '0x41255c'] */

/* 0x002EE610, 0x548 bytes. */
void func_002EE610(int param_1, int param_2)
{
    int bStack_1;
    int bVar1;
    float fVar19;
    float fVar5;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar17;
    int iVar18;
    int iVar20;
    u8 * iVar4;
    u8 * iVar6;
    long long lVar7;
    int * piVar16;
    int * piVar2;
    unsigned long long uVar10;
    unsigned long long uVar15;
    u32 uVar3;
    unsigned long long uVar8;
    unsigned long long uVar9;

    piVar2 = (int *)func_003BD290();
    func_001AE550(1.0f, g_007A2034, 0, (u8 *)(&bStack_1), 0);
    uVar3 = (*(u32 *)g_007A22B8 >> 1) + 1;
    if (9 < uVar3) {
        uVar3 = 10;
    }
    bVar1 = *(u32 *)g_007A22B8 < 0x1E;
    if (bVar1) {
        *(u32 *)(g_007A22B8) = *(u32 *)(g_007A22B8) + 1;
    }
    *(u32 *)(g_007A22B8 + 0x4) = (u32)bVar1;
    lVar7 = func_002ED150();
    if (lVar7 == 0) {
        func_002C6040(0xFFFFFFFFFFFFFFC4, (param_2 & 0xFF) * 0x1C + 0x3E, 0x100, 0x1C, 3, 0x80);
    }
    uVar15 = 0;
    if ((uVar3 & 0xFF) != 0) {
        iVar13 = 0;
        iVar17 = 0;
        iVar18 = 0x17;
        iVar12 = 0x40;
        iVar11 = 0x58;
        piVar16 = piVar2;
        do {
            iVar14 = piVar2[0xC];
            iVar14 = iVar14 + *(int *)((u8 *)PS2_PTR(iVar14) + 8) * *(int *)((u8 *)PS2_PTR(iVar14) + 0xD0);
            iVar4 = func_00106F10(iVar14);
            lVar7 = func_002ED150();
            if ((lVar7 == 0) && (uVar15 == ((unsigned long long)param_2 & 0xFFFFFFFF000000FF))) {
                fVar5 = 1.0;
            }
            else {
                fVar5 = 0.675;
            }
            fVar5 = fVar5 * 128.0;
            if (2.1474836e+09 <= fVar5) {
                fVar5 = fVar5 - 2.1474836e+09;
            }
            fVar19 = (((float)*(u16 *)(iVar4 + 0x14) + 16.0) / 10.0) * (float)(*(u32 *)g_007A22B8 - iVar13) +
                              (float)(int)-(u32)*(u16 *)(iVar4 + 0x14) + 0.0;
            if (fVar19 < 16.0) {
                iVar20 = (int)fVar19;
            }
            else {
                iVar20 = 0x10;
            }
            if (*piVar16 == 0) {
                bStack_1 = 0x50;
            }
            else {
                bStack_1 = 0x80;
            }
            uVar8 = func_00104AC0(iVar14, 0x1D00, 3);
            uVar9 = func_00104D00(iVar14, 0x3FFC, 3);
            uVar8 = func_00106C50(uVar8, uVar9);
            uVar8 = PS2_ADDR(func_00105860(uVar8, 0));
            uVar10 = (unsigned long long)((int)fVar5 & 0xFF);
            iVar6 = (u8 *)PS2_PTR((int)uVar8);
            *(unsigned long long *)(iVar6 + 0x20) =
                      (unsigned long long)bStack_1 << 0x18 | uVar10 << 0x10 | uVar10 | uVar10 << 8 | 0x3F80000000000000;
            *(unsigned long long *)(iVar6 + 0x28) = (long long)(int)(iVar17 << 4 | 8) << 0x10 | 8;
            *(long long *)(iVar6 + 0x38) =
                      (long long)(int)((*(u16 *)(iVar4 + 0x14) - 1) * 0x10 | 8) |
                      (long long)(int)(iVar18 << 4 | 8) << 0x10;
            iVar14 = ((iVar12 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar14 < 0) {
                iVar14 = iVar14 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x30) =
                      (long long)(iVar20 * 0x10 + 0x7000) |
                      (long long)(((iVar14 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar14 = ((iVar11 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar14 < 0) {
                iVar14 = iVar14 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x40) =
                      (long long)(int)(((u32)*(u16 *)(iVar4 + 0x14) + iVar20) * 0x10 + 0x7000) |
                      (long long)(((iVar14 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            func_00105900(uVar8, 3);
            uVar15 = (unsigned long long)((int)uVar15 + 1);
            iVar13 = iVar13 + 2;
            piVar16 = piVar16 + 1;
            iVar17 = iVar17 + 0x18;
            iVar18 = iVar18 + 0x18;
            iVar12 = iVar12 + 0x1C;
            iVar11 = iVar11 + 0x1C;
        } while ((long long)uVar15 < (long long)((unsigned long long)uVar3 & 0xFFFFFFFF000000FF));
    }
}

/* 0x002EEB60, 0x520 bytes. */
void func_002EEB60(int param_1, int param_2)
{
    int bStack_1;
    int bVar1;
    float fVar18;
    float fVar5;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar16;
    int iVar17;
    int iVar19;
    u8 * iVar2;
    u8 * iVar4;
    u8 * iVar6;
    long long lVar7;
    unsigned long long uVar10;
    unsigned long long uVar15;
    u32 uVar3;
    unsigned long long uVar8;
    unsigned long long uVar9;

    iVar2 = func_003BD290();
    func_001AE550(1.0f, g_007A2034, 0, (u8 *)(&bStack_1), 0);
    uVar3 = (*(u32 *)g_007A22B8 >> 1) + 1;
    if (2 < uVar3) {
        uVar3 = 3;
    }
    bVar1 = *(u32 *)g_007A22B8 < 0x10;
    if (bVar1) {
        *(u32 *)(g_007A22B8) = *(u32 *)(g_007A22B8) + 1;
    }
    *(u32 *)(g_007A22B8 + 0x4) = (u32)bVar1;
    lVar7 = func_002ED150();
    if (lVar7 == 0) {
        func_002C6040(0xFFFFFFFFFFFFFFC4, (param_2 & 0xFF) * 0x1C + 0x3E, 0x100, 0x1C, 3, 0x80);
    }
    uVar15 = 0;
    if ((uVar3 & 0xFF) != 0) {
        iVar13 = 0;
        iVar16 = 0;
        iVar17 = 0x17;
        iVar12 = 0x40;
        iVar11 = 0x58;
        do {
            iVar14 = *(int *)(iVar2 + 0x30);
            iVar14 = iVar14 + *(int *)((u8 *)PS2_PTR(iVar14) + 8) * *(int *)((u8 *)PS2_PTR(iVar14) + 0xD8);
            iVar4 = func_00106F10(iVar14);
            lVar7 = func_002ED150();
            if ((lVar7 == 0) && (uVar15 == ((unsigned long long)param_2 & 0xFFFFFFFF000000FF))) {
                fVar5 = 1.0;
            }
            else {
                fVar5 = 0.675;
            }
            fVar5 = fVar5 * 128.0;
            if (2.1474836e+09 <= fVar5) {
                fVar5 = fVar5 - 2.1474836e+09;
            }
            fVar18 = (((float)*(u16 *)(iVar4 + 0x14) + 16.0) / 10.0) * (float)(*(u32 *)g_007A22B8 - iVar13) +
                              (float)(int)-(u32)*(u16 *)(iVar4 + 0x14) + 0.0;
            if (fVar18 < 16.0) {
                iVar19 = (int)fVar18;
            }
            else {
                iVar19 = 0x10;
            }
            uVar8 = func_00104AC0(iVar14, 0x1D00, 3);
            uVar9 = func_00104D00(iVar14, 0x3FFC, 3);
            uVar8 = func_00106C50(uVar8, uVar9);
            uVar8 = PS2_ADDR(func_00105860(uVar8, 0));
            uVar10 = (unsigned long long)((int)fVar5 & 0xFF);
            iVar6 = (u8 *)PS2_PTR((int)uVar8);
            *(unsigned long long *)(iVar6 + 0x20) =
                      (unsigned long long)bStack_1 << 0x18 | uVar10 << 0x10 | uVar10 | uVar10 << 8 | 0x3F80000000000000;
            *(unsigned long long *)(iVar6 + 0x28) = (long long)(int)(iVar16 << 4 | 8) << 0x10 | 8;
            *(long long *)(iVar6 + 0x38) =
                      (long long)(int)((*(u16 *)(iVar4 + 0x14) - 1) * 0x10 | 8) |
                      (long long)(int)(iVar17 << 4 | 8) << 0x10;
            iVar14 = ((iVar12 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar14 < 0) {
                iVar14 = iVar14 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x30) =
                      (long long)(iVar19 * 0x10 + 0x7000) |
                      (long long)(((iVar14 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar14 = ((iVar11 * 0x280) / 0x1E0) * 0x1C0;
            if (iVar14 < 0) {
                iVar14 = iVar14 + 0x1FF;
            }
            *(unsigned long long *)(iVar6 + 0x40) =
                      (long long)(int)(((u32)*(u16 *)(iVar4 + 0x14) + iVar19) * 0x10 + 0x7000) |
                      (long long)(((iVar14 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            func_00105900(uVar8, 3);
            uVar15 = (unsigned long long)((int)uVar15 + 1);
            iVar13 = iVar13 + 2;
            iVar16 = iVar16 + 0x18;
            iVar17 = iVar17 + 0x18;
            iVar12 = iVar12 + 0x1C;
            iVar11 = iVar11 + 0x1C;
        } while ((long long)uVar15 < (long long)((unsigned long long)uVar3 & 0xFFFFFFFF000000FF));
    }
}

/* 0x0037DAD0, 0x2F4 bytes. */
void func_0037DAD0(int param_1)
{
    int aiStack_10[4];
    u8 auStack_20[16];
    int iVar1;
    int iVar4;
    int iVar5;
    int * piVar3;
    unsigned long long uVar2;

    iVar1 = PS2_ADDR(func_0030E2C0());
    uVar2 = func_00327D50();
    func_002F9060(uVar2);
    if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x69C) < 0x30) {
        aiStack_10[0] = *(int *)((u8 *)PS2_PTR(iVar1) + 4);
        if (600000 < aiStack_10[0]) {
            aiStack_10[0] = 600000;
        }
        aiStack_10[1] = *(int *)((u8 *)PS2_PTR(iVar1) + 8);
        if (600000 < aiStack_10[1]) {
            aiStack_10[1] = 600000;
        }
        aiStack_10[2] = *(int *)((u8 *)PS2_PTR(iVar1) + 0xC);
        if (600000 < aiStack_10[2]) {
            aiStack_10[2] = 600000;
        }
    }
    else {
        iVar4 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x69C) + -0x30;
        if (0x1E < iVar4) {
            iVar4 = 0x1E;
        }
        aiStack_10[0] = *(int *)((u8 *)PS2_PTR(iVar1) + 4);
        if (600000 < aiStack_10[0]) {
            aiStack_10[0] = 600000;
        }
        aiStack_10[1] = *(int *)((u8 *)PS2_PTR(iVar1) + 8);
        if (600000 < aiStack_10[1]) {
            aiStack_10[1] = 600000;
        }
        aiStack_10[2] = *(int *)((u8 *)PS2_PTR(iVar1) + 0xC);
        if (600000 < aiStack_10[2]) {
            aiStack_10[2] = 600000;
        }
        iVar1 = (aiStack_10[0] * iVar4) / 0x1E;
        aiStack_10[0] = aiStack_10[0] - iVar1;
        iVar4 = (aiStack_10[1] * iVar4) / 0x1E;
        aiStack_10[1] = aiStack_10[1] - iVar4;
        aiStack_10[2] = aiStack_10[2] + iVar1 + iVar4;
        if (600000 < aiStack_10[2]) {
            aiStack_10[2] = 600000;
        }
    }
    iVar4 = 0x8C;
    func_002C7310(0x88, 0x8C, 0, 0xF0, 0x5E, 0x80, 1);
    iVar5 = 0;
    iVar1 = 0;
    piVar3 = aiStack_10;
    do {
        if (iVar5 == 2) {
            func_002CA490(0x98, iVar4 + 8 + iVar1, 0, 0xD0, 3, 0x80, 1);
            iVar4 = iVar4 + 4;
        }
        func_001ABEA0(param_1, 7, 0xA8, iVar4 + 8 + iVar1, 0, 0x80, 0x16, 0);
        func_001204B0(auStack_20, 0x459500, *piVar3);
        func_002C4F40(16.0f, (char *)(auStack_20), 0x108, iVar4 + 0xD + iVar1, 1, 0, 6);
        iVar5 = iVar5 + 1;
        iVar1 = iVar1 + 0x18;
        piVar3 = piVar3 + 1;
    } while (iVar5 < 3);
}

/* 0x0037DDD0, 0x1B4 bytes. */
void func_0037DDD0(int param_1, int param_2, int param_3, int param_4)
{
    int aiStack_8[2];
    u8 auStack_20[24];
    int iVar1;
    int iVar2;
    int iVar3;
    int * piVar4;

    if (600000 < param_3) {
        param_3 = 600000;
    }
    aiStack_8[1] = param_4 * 10;
    aiStack_8[0] = (int)param_3;
    if (600000 < aiStack_8[1]) {
        aiStack_8[1] = 600000;
    }
    func_002C7310(0x88, 0x8C, 0, 0xF0, 0x42, param_2, 1);
    iVar2 = 0;
    iVar1 = 0x94;
    piVar4 = aiStack_8;
    iVar3 = 0x99;
    do {
        func_001ABEA0(param_1, 7, 0xA8, iVar1, 0, 0x80, 0x16, 0);
        func_001204B0(auStack_20, 0x459500, *piVar4);
        *(u8 *)(g_0056CCC8) = (u8)param_2;
        *(u8 *)(g_0056CCC8 + 0x1) = *(u8 *)(g_0056CCC8);
        *(u8 *)(g_0056CCC8 + 0x2) = *(u8 *)(g_0056CCC8);
        *(u8 *)(g_0056CCC8 + 0x3) = *(u8 *)(g_0056CCC8);
        func_002C4F40(16.0f, (char *)(auStack_20), 0x108, iVar3, 1, 0, 6);
        *(u8 *)(g_0056CCC8) = 0x80;
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x18;
        *(u8 *)(g_0056CCC8 + 0x1) = 0x80;
        piVar4 = piVar4 + 1;
        *(u8 *)(g_0056CCC8 + 0x2) = 0x80;
        *(u8 *)(g_0056CCC8 + 0x3) = 0x80;
        iVar3 = iVar3 + 0x18;
    } while (iVar2 < 2);
}

/* 0x0037FB60, 0x1F0 bytes. */
void func_0037FB60(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    u8 auStack_20[32];
    int iVar2;
    int iVar3;
    unsigned long long uVar1;

    func_002C7310(param_2, param_3, 0, 0xC0, 0xA0, 0x80, 1);
    uVar1 = PS2_ADDR(func_002F8DE0(param_4));
    iVar3 = (int)param_2;
    iVar2 = (int)param_3;
    func_002C4C50(20.0f, (char *)PS2_PTR(uVar1), iVar3 + 0x10, iVar2 + 0x10, 0xA0, 1, 0, 6);
    func_003B5970(iVar3 + 0x14, iVar2 + 0x78, 0, 0x98, 0x18, 0x80, 1);
    func_001ABEA0(param_1, 300, iVar3 + 0x1E, iVar2 + 0x79, 0, 0x38, 0x14, 0);
    func_001204B0(auStack_20, 0x459558, param_5);
    func_002C4F40(16.0f, (char *)(auStack_20), iVar3 + 0x60, iVar2 + 0x7C, 1, 0, 6);
    *(u32 *)(g_0056CCA4) = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    uVar1 = PS2_ADDR(func_00372650());
    func_00146270(uVar1, iVar3 + 0x78, iVar2 + 0x7C, 1, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)(g_0056CCA4) = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
    uVar1 = func_002F8F20(param_4);
    func_00382690(iVar3 + 0x40, iVar2 + 0x2A, 0, 0x40, 0x48, 1, uVar1);
}

/* 0x003876C0, 0x344 bytes. */
void func_003876C0(int param_1, u32 *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    u32 uVar1;
    unsigned long long uVar2;

    iVar5 = 0;
    do {
        uVar1 = *param_2;
        if (iVar5 == param_7) {
            func_002C8500(param_3, param_4, param_5, 0xC4, 0x1A, 0x80, param_6);
        }
        else {
            func_002C80A0(param_3, param_4, param_5, 0xC4, 0x1A, 0x80, param_6);
        }
        iVar6 = (int)param_3;
        iVar3 = iVar6 + 0x12;
        iVar4 = param_4 + -2;
        if (iVar5 == 0) {
            func_001ABEA0(param_1, 0x51, iVar3, iVar4, param_5, 0x28, 0x18, 0);
        }
        else if (iVar5 < 4) {
            func_001ABEA0(param_1, 0x51, iVar3, iVar4, param_5, 0x28, 0x18, 0);
        }
        else {
            func_001ABEA0(param_1, 0x51, iVar3, iVar4, param_5, 0x28, 0x18, 0);
        }
        if (uVar1 < 0x19F) {
            *(u32 *)(g_0056CCA4) = 6;
            *(u32 *)(g_0056CCA4 + 0x4) = 6;
            *(u32 *)(g_0056CCA4 + 0x8) = 6;
            *(u32 *)(g_0056CCA4 + 0xC) = 6;
            *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
            *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
            uVar2 = PS2_ADDR(func_002F2890(uVar1));
            func_00146B40(uVar2, iVar6 + 0x3A, param_4, 0x7A, 0x10, param_6, 0);
            *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
            *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
            *(u32 *)(g_0056CCA4 + 0x4) = 5;
            *(u32 *)(g_0056CCA4) = 5;
            *(u32 *)(g_0056CCA4 + 0xC) = 5;
            *(u32 *)(g_0056CCA4 + 0x8) = 5;
            iVar3 = func_002F3770(uVar1);
            iVar4 = func_002F38F0(uVar1);
            func_001A85D0((float)iVar3 / (float)iVar4, 0, 1.0f, iVar6 + 0x3A, param_4 + 0xE, param_5, 2, 0,
                                      0x60, 1);
        }
        iVar5 = iVar5 + 1;
        param_2 = param_2 + 1;
        param_4 = param_4 + 0x1E;
    } while (iVar5 < 7);
    if (param_7 == 7) {
        func_002C6040(iVar6 + -0x2E, 0x122, 0x100, 0x1C, 1, 0x80);
    }
    func_003B4740(iVar6 + 0xE, 0x124, 0, 1, param_7 == 7, param_8 == 0);
}

/* 0x003AECD0, 0xF0 bytes. */
void func_003AECD0(void)
{
    int aiStack_20[6];
    u8 auStack_8[8];
    int iVar2;
    unsigned long long uVar1;

    func_003DC180(9, 0, aiStack_20);
    func_002C7310(aiStack_20[0], 0xD6, 0, 0xA2, 0x20, 0x80, 1);
    uVar1 = PS2_ADDR(func_0030D7D0());
    func_001ABEA0(uVar1, 0x11E, aiStack_20[0] + 0x10, 0xDE, 0, 0x50, 0x10, 0);
    iVar2 = *(u32 *)g_007BAE88;
    if (5 < *(u32 *)g_007BAE88) {
        iVar2 = 6;
    }
    func_001204B0(auStack_8, 0x45B520, iVar2);
    func_002C5020(14.0f, (char *)(auStack_8), aiStack_20[0] + 0x8A, 0xE0, 1, 0, 6);
}

/* 0x003AEDC0, 0x168 bytes. */
void func_003AEDC0(void)
{
    int aiStack_20[6];
    u8 auStack_8[8];
    int iVar2;
    int iVar3;
    int iVar4;
    unsigned long long uVar1;

    func_003DC180(9, 1, aiStack_20);
    func_002C7310(aiStack_20[0], 0xF8, 0, 0xA2, 0x38, 0x80, 1);
    uVar1 = PS2_ADDR(func_0030D7D0());
    func_001ABEA0(uVar1, 0x11E, aiStack_20[0] + 0x10, 0x100, 0, 0x50, 0x10, 0);
    func_001204B0(auStack_8, 0x45B520, *(u32 *)(g_007BAE7C + 0x4) - (*(u32 *)g_007BAE7C + 1));
    func_002C5020(14.0f, (char *)(auStack_8), aiStack_20[0] + 0x8A, 0x101, 1, 0, 6);
    iVar3 = *(u32 *)g_007BAE7C + 1;
    if (iVar3 < *(u32 *)(g_007BAE7C + 0x4)) {
        iVar2 = aiStack_20[0] + 0x10;
        iVar4 = iVar3 * 4 + 0x7BAE70;
        do {
            func_00382690(iVar2, 0x112, 0, 0x14, 0x16, 1, *(u32 *)((u8 *)PS2_PTR(iVar4) + 0x24));
            iVar3 = iVar3 + 1;
            iVar2 = iVar2 + 0x16;
            iVar4 = iVar4 + 4;
        } while (iVar3 < *(u32 *)(g_007BAE7C + 0x4));
    }
}

/* 0x003F0020, 0x60C bytes. */
void func_003F0020(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    u8 auStack_10[16];
    int bVar1;
    int iVar2;
    int iVar3;
    long long lVar4;
    long long lVar6;
    unsigned long long uVar5;
    unsigned long long uVar7;
    unsigned long long uVar8;

    if ((param_1 != 0) && (param_2 < 0x19F)) {
        param_4 = param_4 * 0x20;
        if (param_5 == 0) {
            func_002C7310(0, param_4 + 0x62, 0, 0x200, 0x1C, 0x80, 1);
        }
        else {
            func_002C7A30(0, param_4 + 0x62, 0, 0x200, 0x1C, 0x80, 1);
        }
        if ((399 < (long long)param_2 && (long long)param_2 < 0x19F) ||
              (((long long)param_2 < 400 || 0x19E < (long long)param_2 && (lVar4 = func_003A0040(param_2), lVar4 != 0)
                ))) {
            func_003B5930(0x10, param_4 + 0x68, 0, 1);
        }
        *(u32 *)(g_0056CCA4) = 6;
        *(u32 *)(g_0056CCA4 + 0x4) = 6;
        *(u32 *)(g_0056CCA4 + 0x8) = 6;
        *(u32 *)(g_0056CCA4 + 0xC) = 6;
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        uVar5 = PS2_ADDR(func_002F2890(param_2));
        func_00146B40(uVar5, 0x20, param_4 + 0x68, 0x7A, 0x10, 1, 0);
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
        if (param_3 == 0) {
            lVar4 = func_002F5CC0(param_2);
            bVar1 = false;
            if ((-1 < lVar4) && (lVar6 = func_0030AB90(), lVar4 < lVar6)) {
                bVar1 = true;
            }
            if (bVar1) {
                uVar5 = PS2_ADDR(func_0030ABF0(lVar4));
                func_002C4C50(16.0f, (char *)PS2_PTR(uVar5), 0xA0, param_4 + 0x68, 0x48, 1, 0, 6);
            }
            lVar4 = func_002F4080(param_2);
            bVar1 = false;
            if ((-1 < lVar4) && (lVar6 = func_0030AB90(), lVar4 < lVar6)) {
                bVar1 = true;
            }
            if (bVar1) {
                uVar5 = PS2_ADDR(func_002F8DB0(lVar4));
                func_002C4C50(16.0f, (char *)PS2_PTR(uVar5), 0xF0, param_4 + 0x68, 0x48, 1, 0, 6);
            }
            uVar5 = func_002F4660(param_2);
            func_003B5070(uVar5, 0x140, param_4 + 0x66, 0, 1);
            uVar5 = func_002F3770(param_2);
            uVar7 = func_002F38F0(param_2);
            func_003EF980(param_1, uVar5, uVar7, 0x168, param_4 + 0x65, 0, 1);
            iVar2 = func_002F3770(param_2);
            iVar3 = func_002F38F0(param_2);
            func_001A85D0((float)iVar2 / (float)iVar3, 0, 1.0f, 0x168, param_4 + 0x71, 0, 2, 0, 0x58, 1);
            iVar2 = func_002F41E0(param_2);
            func_001204B0(auStack_10, 0x45C990, iVar2 + 1);
            func_002C5020(16.0f, (char *)(auStack_10), 0x1E8, param_4 + 0x68, 1, 0, 6);
        }
        else {
            uVar5 = func_002F39F0(param_2);
            func_003EFB90(param_1, uVar5, 0xB8, param_4 + 0x65, 0, 1);
            iVar2 = func_002F39F0(param_2);
            func_001A85D0((float)iVar2 / 350.0, 0, 1.0f, 0xA0, param_4 + 0x71, 0, 6, 0, 0x30, 1);
            uVar5 = func_002F4C40(param_2);
            func_003EFB90(param_1, uVar5, 0xF6, param_4 + 0x65, 0, 1);
            iVar2 = func_002F4C40(param_2);
            func_001A85D0((float)iVar2 / 350.0, 0, 1.0f, 0xDE, param_4 + 0x71, 0, 7, 0, 0x30, 1);
            uVar5 = func_002F4DD0(param_2);
            func_003EFB90(param_1, uVar5, 0x134, param_4 + 0x65, 0, 1);
            iVar2 = func_002F4DD0(param_2);
            func_001A85D0((float)iVar2 / 250.0, 0, 1.0f, 0x11C, param_4 + 0x71, 0, 8, 0, 0x30, 1);
            uVar5 = func_002F4F60(param_2);
            func_003EFB90(param_1, uVar5, 0x172, param_4 + 0x65, 0, 1);
            iVar2 = func_002F4F60(param_2);
            func_001A85D0((float)iVar2 / 250.0, 0, 1.0f, 0x15A, param_4 + 0x71, 0, 9, 0, 0x30, 1);
            uVar8 = func_00327870();
            if (param_2 == uVar8) {
                iVar3 = 0;
                iVar2 = 0x198;
                do {
                    func_003B5300(iVar3, iVar2, param_4 + 0x66, 0, 1);
                    iVar3 = iVar3 + 1;
                    iVar2 = iVar2 + 0x16;
                } while (iVar3 < 4);
            }
            else {
                uVar5 = func_002F5AA0(param_2);
                func_003B5300(uVar5, 0x198, param_4 + 0x66, 0, 1);
            }
        }
    }
}
