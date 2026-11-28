/*
 * gen14_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

#define true 1
#define false 0

extern u8 g_0043D490[0x4];
extern u8 g_0045D890[0x14];
extern u8 g_00574DE0[0x10];
extern u8 g_005BA688[0x4];
extern u8 g_005BA6A0[0x4];
extern u8 g_00669DB8[0x4];
extern u8 g_00669F60[0x4];
extern u8 g_006A3A40[0x4];
extern u8 g_006A3A44[0x4];
extern u8 g_006A3A98[0x4];
extern u8 g_006A3AB0[0x4];
extern u8 g_006A3AB2[0x4];
extern u8 g_006A3AB4[0x4];
extern u8 g_006A3AB8[0x4];
extern u8 g_006A3AE8[0x4];
extern u8 g_00730DE0[0x4];
extern u8 g_00730DF8[0x4];
extern u8 g_00730DFC[0x4];
extern u8 g_00730E00[0x4];
extern u8 g_00730E04[0x4];
extern u8 g_00730E14[0x4];
extern u8 g_007325A8[0x10];
extern u8 g_0073C78C[0xD];
extern u8 g_0073C79D[0x1];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045CDA4;   /* (small data) */
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */

void *func_0014F810();
int func_001523C0();
int func_0017DEA0();
int func_001CCFA0();
int func_001D68E0();
int func_001D6BD0();
void *func_001DBA70();
int func_001DBBC0();
void *func_001DBC60();
void *func_001DBCA0();
int func_001DC3C0();
int func_001DF470();
void func_001E01D0(float, int);
int func_0020E0D0();
int func_0020E140();
int func_0020E170();
int func_00240DB0();
int func_002431F0();
int func_00253300();
int func_0027F160();
int func_002E9FA0();
void func_001D7040(u8 *param_1);
void func_001D70F0(u8 *param_1);
void func_001D7340(u8 *param_1);
void func_001DDD80(u8 *param_1);
void func_001DDE50(u8 *param_1);
void func_001DE080(u8 *param_1);
void func_001DE250(u8 *param_1);
void func_001DE360(u8 *param_1);
void func_001DE8B0(u8 *param_1);
void func_001DE980(u8 *param_1);
void func_001DEC30(u8 *param_1);
void func_001DF890(u8 *param_1);
void func_001DF9C0(u8 *param_1);
void func_001DFC20(u8 *param_1);
void func_0020E5C0(int param_1, int param_2, int param_3);
int func_002434F0(u8 *param_1);
void func_00263180(int param_1);
int func_00271610(float param_1, u8 *param_2);
void func_00271870(void);
void func_00272A70(u8 *param_1);
void func_002D7FF0(u8 *param_1);

/* 0x001D7040, 0xA4 bytes. */
void func_001D7040(u8 *param_1)
{
    int iVar3;
    u8 * puVar1;
    u8 * puVar2;
    u32 uVar4;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    iVar3 = g_0045D3E0 * 0x240;
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(iVar3 + 0x730780, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(iVar3 + 0x730784, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
}

/* 0x001D70F0, 0x8C bytes. */
void func_001D70F0(u8 *param_1)
{
    u8 auStack_2[2];
    u8 auStack_4[2];
    u8 * puVar1;
    u8 * puVar2;
    u32 uVar3;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(auStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(auStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    func_0027F160(auStack_2[0], auStack_4[0]);
}

/* 0x001D7340, 0x58 bytes. */
void func_001D7340(u8 *param_1)
{
    u8 * puVar1;
    u8 * puVar2;
    u32 uStack_4;
    u32 uVar3;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    g_0045CDA4 = uStack_4;
}

/* 0x001DDD80, 0xC4 bytes. */
void func_001DDD80(u8 *param_1)
{
    int bVar3;
    int iVar5;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar6;
    int uStack_2;
    u32 uVar4;
    u32 uVar7;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    uVar7 = (u32)uStack_2;
    iVar5 = g_0045D3E0 * 0x38;
    if ((int)uVar7 < *(int *)(g_00730E14 + iVar5)) {
        bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar5) + uVar7 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        puVar6 = (u32 *)(*(int *)(g_00730E04 + iVar5) + uVar7 * 4);
        *puVar6 = *puVar6 & 0xFFFFFFFD;
    }
}

/* 0x001DDE50, 0x22C bytes. */
void func_001DDE50(u8 *param_1)
{
    char acStack_6[2];
    int bVar3;
    int iVar6;
    int * piVar7;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar9;
    int uStack_2;
    int uStack_4;
    u32 uVar4;
    u32 uVar5;
    u32 uVar8;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(acStack_6, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    uVar8 = (u32)uStack_2;
    iVar6 = g_0045D3E0 * 0x38;
    piVar7 = (int *)(iVar6 + 0x730DE0);
    if ((int)uVar8 < *(int *)(g_00730E14 + iVar6)) {
        bVar3 = *(int *)(*piVar7 + uVar8 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        uVar5 = (u32)uStack_4;
        if ((int)uVar8 < *(int *)(g_00730E14 + iVar6)) {
            bVar3 = *(int *)(*piVar7 + uVar8 * 4) != 0;
        }
        else {
            bVar3 = false;
        }
        if ((bVar3) &&
              (puVar9 = (u32 *)(piVar7[*(u8 *)(*(int *)(g_00730DFC + iVar6) + uVar8) + 10] + uVar8 * 8),
              uVar5 < *puVar9)) {
            bVar3 = *(int *)(puVar9[1] + uVar5 * 0x10) != 0;
        }
        else {
            bVar3 = false;
        }
        if (bVar3) {
            if (acStack_6[0] == 0) {
                iVar6 = *(int *)(piVar7[*(u8 *)(*(int *)(g_00730DFC + iVar6) + uVar8) + 10] + uVar8 * 8 + 4)
                                + uVar5 * 0x10;
                *(u8 *)((u8 *)PS2_PTR(iVar6) + 0xF) = *(u8 *)((u8 *)PS2_PTR(iVar6) + 0xF) & 0xFD;
            }
            else {
                iVar6 = *(int *)(piVar7[*(u8 *)(*(int *)(g_00730DFC + iVar6) + uVar8) + 10] + uVar8 * 8 + 4)
                                + uVar5 * 0x10;
                *(u8 *)((u8 *)PS2_PTR(iVar6) + 0xF) = *(u8 *)((u8 *)PS2_PTR(iVar6) + 0xF) | 2;
            }
        }
    }
}

/* 0x001DE080, 0x1CC bytes. */
void func_001DE080(u8 *param_1)
{
    int bVar3;
    int iVar5;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar6;
    int sStack_4;
    int sStack_6;
    int uStack_2;
    u32 uVar4;
    u32 uVar7;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&sStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&sStack_6, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    uVar7 = (u32)uStack_2;
    iVar5 = g_0045D3E0 * 0x38;
    if ((int)uVar7 < *(int *)(g_00730E14 + iVar5)) {
        bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar5) + uVar7 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        if (sStack_4 == 0) {
            puVar6 = (u32 *)(*(int *)(g_00730E04 + iVar5) + uVar7 * 4);
            *puVar6 = *puVar6 | 4;
        }
        else {
            puVar6 = (u32 *)(*(int *)(g_00730E04 + iVar5) + uVar7 * 4);
            *puVar6 = *puVar6 & 0xFFFFFFFB;
        }
        if (sStack_6 == 0) {
            puVar6 = (u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730E04) + uVar7 * 4);
            *puVar6 = *puVar6 & 0xFFFFFFF7;
        }
        else {
            puVar6 = (u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730E04) + uVar7 * 4);
            *puVar6 = *puVar6 | 8;
        }
    }
}

/* 0x001DE250, 0x10C bytes. */
void func_001DE250(u8 *param_1)
{
    int bVar3;
    int iVar5;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    int uStack_4;
    u32 uVar4;
    u32 uVar6;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    uVar6 = (u32)uStack_2;
    iVar5 = g_0045D3E0 * 0x38;
    if ((int)uVar6 < *(int *)(g_00730E14 + iVar5)) {
        bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar5) + uVar6 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        bVar3 = *(short *)(*(int *)(g_00730DF8 + iVar5) + uVar6 * 2) == 0x3C;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
        *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
        puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
        *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
        uVar4 = func_001D6BD0(&uStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
        *(u32 *)(param_1 + 0xC) = uVar4;
        func_001DBBC0(uStack_2, uStack_4);
    }
}

/* 0x001DE360, 0x108 bytes. */
void func_001DE360(u8 *param_1)
{
    int bVar3;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    int uStack_4;
    u32 uVar4;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    if ((int)(u32)uStack_2 < *(int *)(g_0045D3E0 * 0x38 + 0x730E14)) {
        bVar3 = *(int *)(*(int *)(g_0045D3E0 * 0x38 + 0x730DE0) + (u32)uStack_2 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
        *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
        puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
        *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
        uVar4 = func_001D6BD0(&uStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
        *(u32 *)(param_1 + 0xC) = uVar4;
        *(u16 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730E00) + (u32)uStack_2 * 2) = uStack_4;
    }
}

/* 0x001DE8B0, 0xD0 bytes. */
void func_001DE8B0(u8 *param_1)
{
    int bVar3;
    int iVar5;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    u32 uVar4;
    u32 uVar6;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    uVar6 = (u32)uStack_2;
    iVar5 = g_0045D3E0 * 0x38;
    if ((int)uVar6 < *(int *)(g_00730E14 + iVar5)) {
        bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar5) + uVar6 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        *(u16 *)(*(int *)(g_00730E00 + iVar5) + uVar6 * 2) = (u16)*(u8 *)((*(u8 *)(g_0073C79D)) + 0x73C7A0)
        ;
    }
}

/* 0x001DE980, 0x2AC bytes. */
void func_001DE980(u8 *param_1)
{
    int bVar3;
    int iVar10;
    int iVar13;
    long long lVar6;
    int * piVar14;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar5;
    u32 * puVar9;
    int uStack_2;
    u32 uVar11;
    u32 uVar12;
    u32 uVar4;
    unsigned long long uVar7;
    unsigned long long uVar8;

    lVar6 = PS2_ADDR(func_001DBC60());
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    piVar14 = (int *)lVar6;
    uVar4 = func_001D6BD0(piVar14 + 3, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar4 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar4;
    iVar10 = g_0045D3E0 * 0x38;
    if ((int)(u32)uStack_2 < *(int *)(g_00730E14 + iVar10)) {
        bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar10) + (u32)uStack_2 * 4) != 0;
    }
    else {
        bVar3 = false;
    }
    if (bVar3) {
        bVar3 = *(short *)(*(int *)(g_00730DF8 + iVar10) + (u32)uStack_2 * 2) == 0x3C;
    }
    else {
        bVar3 = false;
    }
    if ((bVar3) && (lVar6 != 0)) {
        if ((int)(u32)*(u16 *)(piVar14 + 3) < *(int *)(g_00730E14 + iVar10)) {
            bVar3 = *(int *)(*(int *)(g_00730DE0 + iVar10) + (u32)*(u16 *)(piVar14 + 3) * 4) != 0;
        }
        else {
            bVar3 = false;
        }
        if (bVar3) {
            iVar10 = PS2_ADDR(func_001DBA70());
            piVar14[2] = iVar10;
            *(u8 *)((int)piVar14 + 0xE) = 1;
            *(u8 *)((int)piVar14 + 0xF) = 0;
            func_001E01D0(0, (short)piVar14[3]);
            func_001E01D0(0, *(u16 *)(piVar14[2] + 0x14));
            uVar7 = PS2_ADDR(func_0014F810(*(u32 *)
                                                        (*(int *)(g_0045D3E0 * 0x38 + 0x730DE0) +
                                                        (u32)*(u16 *)(piVar14 + 3) * 4), 0x15));
            uVar8 = PS2_ADDR(func_0014F810(*(u32 *)
                                                        (*(int *)(g_0045D3E0 * 0x38 + 0x730DE0) +
                                                        (u32)*(u16 *)(piVar14[2] + 0x14) * 4), 0x11));
            func_002E9FA0(*piVar14, piVar14[1], uVar7, uVar8);
            iVar10 = *piVar14;
            iVar13 = 0;
            if (0 < *(int *)((u8 *)PS2_PTR(iVar10) + 0x1C)) {
                do {
                    puVar9 = (u32 *)(*(int *)((u8 *)PS2_PTR(iVar10) + 0x14) + iVar13 * 0x10);
                    puVar5 = (u32 *)(*(int *)((u8 *)PS2_PTR(iVar10) + 0x10) + iVar13 * 0x10);
                    uVar4 = puVar5[1];
                    uVar11 = puVar5[2];
                    uVar12 = puVar5[3];
                    *puVar9 = *puVar5;
                    puVar9[1] = uVar4;
                    puVar9[2] = uVar11;
                    puVar9[3] = uVar12;
                    iVar10 = *piVar14;
                    iVar13 = iVar13 + 1;
                } while (iVar13 < *(int *)((u8 *)PS2_PTR(iVar10) + 0x1C));
            }
            iVar10 = piVar14[1];
            iVar13 = 0;
            if (0 < *(int *)((u8 *)PS2_PTR(iVar10) + 0x1C)) {
                do {
                    puVar9 = (u32 *)(*(int *)((u8 *)PS2_PTR(iVar10) + 0x14) + iVar13 * 0x10);
                    puVar5 = (u32 *)(*(int *)((u8 *)PS2_PTR(iVar10) + 0x10) + iVar13 * 0x10);
                    uVar4 = puVar5[1];
                    uVar11 = puVar5[2];
                    uVar12 = puVar5[3];
                    *puVar9 = *puVar5;
                    puVar9[1] = uVar4;
                    puVar9[2] = uVar11;
                    puVar9[3] = uVar12;
                    iVar10 = piVar14[1];
                    iVar13 = iVar13 + 1;
                } while (iVar13 < *(int *)((u8 *)PS2_PTR(iVar10) + 0x1C));
            }
            func_001DC3C0();
        }
    }
}

/* 0x001DEC30, 0x68 bytes. */
void func_001DEC30(u8 *param_1)
{
    long long lVar4;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    u32 uVar3;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    lVar4 = PS2_ADDR(func_001DBCA0(uStack_2));
    if (lVar4 != 0) {
        *(u8 *)((int)lVar4 + 0xE) = 0;
        *(u8 *)((int)lVar4 + 0xF) = 0;
    }
}

/* 0x001DF890, 0x124 bytes. */
void func_001DF890(u8 *param_1)
{
    int iStack_8;
    u8 * puVar1;
    u8 * puVar2;
    u32 * puVar5;
    int uStack_2;
    int uStack_4;
    u32 uVar3;
    u32 uVar4;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    if (2 < *(u8 *)(*(int *)(param_1 + 8) + 6)) {
        puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
        *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
        puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
        *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
        uVar3 = func_001D6BD0(&iStack_8, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
        *(u32 *)(param_1 + 0xC) = uVar3;
        puVar5 = (u32 *)(*(int *)(param_1 + 4) + iStack_8);
        if (*(char *)(param_1 + 0x50) == 0) {
            uVar4 = *puVar5 & *(u32 *)(param_1 + 0x18);
        }
        else if (*(char *)(param_1 + 0x50) == 1) {
            uVar4 = (u32)(*puVar5 == *(u32 *)(param_1 + 0x18));
        }
        else {
            uVar4 = 0;
        }
        if (uVar4 == 0) {
            return;
        }
    }
    func_001DF470(uStack_2, 0, uStack_4);
}

/* 0x001DF9C0, 0xB0 bytes. */
void func_001DF9C0(u8 *param_1)
{
    u8 auStack_4[2];
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    u32 uVar3;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(auStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    *(u8 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730DFC) + (u32)uStack_2) = auStack_4[0];
}

/* 0x001DFC20, 0x108 bytes. */
void func_001DFC20(u8 *param_1)
{
    u8 abStack_4[2];
    int bVar4;
    int iVar3;
    int * piVar6;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    u32 uVar5;
    u32 uVar7;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar5 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar5;
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar5 = func_001D6BD0(abStack_4, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar5;
    uVar7 = (u32)uStack_2;
    piVar6 = (int *)(g_0045D3E0 * 0x38 + 0x730DE0);
    if ((int)uVar7 < *(int *)(g_0045D3E0 * 0x38 + 0x730E14)) {
        bVar4 = *(int *)(*piVar6 + uVar7 * 4) != 0;
    }
    else {
        bVar4 = false;
    }
    if (bVar4) {
        iVar3 = *(int *)(*piVar6 + uVar7 * 4);
        *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x20C) = *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x20C) & 0xFB | (abStack_4[0] & 1) << 2;
    }
}

/* 0x0020E5C0, 0x180 bytes. */
void func_0020E5C0(int param_1, int param_2, int param_3)
{
    int iVar3;
    long long lVar2;
    u32 * puVar1;

    iVar3 = (int)param_2;
    puVar1 = ((u32 *)PS2_PTR(*(ps2ptr *)(iVar3 * 4 + 0x73C484)));
    if ((puVar1 == (u32 *)0) || (param_3 < *puVar1)) {
        *(u8 *)(g_0073C78C + 0xC) = (u8)param_3;
        *(u32 *)(g_0073C78C) = iVar3;
        if (param_1 != 0) {
            lVar2 = func_0020E0D0(param_2, param_3);
            if (lVar2 == 0) {
                *(u32 *)(g_00669F60) = *(u32 *)(g_00669F60) | 0x10080000;
                func_001D68E0();
            }
            else {
                *(u32 *)(g_00669F60) = *(u32 *)(g_00669F60) | 0x10100000;
                lVar2 = func_0020E140();
                if ((lVar2 != 0) || (lVar2 = func_0020E170(), lVar2 != 0)) {
                    *(u32 *)(g_0045D890) = 1;
                }
                if ((0x17 < *(u32 *)(g_0045D890 + 0xC)) && (0x17 < *(u32 *)(g_0045D890 + 0x10))) {
                    *(u32 *)(g_0045D890 + 0xC) = 7;
                }
                if ((*(u32 *)(g_0045D890 + 0x10) < 0x18) && (*(u32 *)(g_0045D890 + 0x8) != *(u32 *)(g_0045D890 + 0x10))) {
                    *(u32 *)(g_0045D890 + 0x4) = *(u32 *)(g_0045D890 + 0x8);
                    *(u32 *)(g_0045D890 + 0x8) = *(u32 *)(g_0045D890 + 0x10);
                    *(u32 *)(g_0045D890 + 0xC) = 0x18;
                }
                else {
                    *(u32 *)(g_0045D890 + 0x4) = *(u32 *)(g_0045D890 + 0x8);
                    *(u32 *)(g_0045D890 + 0x8) = *(u32 *)(g_0045D890 + 0xC);
                    *(u32 *)(g_0045D890 + 0xC) = *(u32 *)(g_0045D890 + 0x10);
                }
            }
        }
    }
}

/* 0x002434F0, 0x760 bytes. */
int func_002434F0(u8 *param_1)
{
    int bVar3;
    int iVar2;
    u8 * iVar6;
    long long lVar5;
    u16 * puVar7;
    int uVar1;
    int uVar4;
    u32 uVar8;

    iVar6 = param_1;
    puVar7 = ((u16 *)PS2_PTR(*(ps2ptr *)(iVar6 + 0x210)));
    iVar2 = *(int *)(iVar6 + 0x28C);
    uVar4 = *puVar7;
    if (iVar2 != 0) {
        if ((*(u32 *)(((short *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x210))) + 0xC) & 0x800) != 0) {
            return uVar4;
        }
        if (*((short *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x210))) == 0x60) {
            return uVar4;
        }
    }
    if ((((iVar2 != 0) && (*(u8 *)((u8 *)PS2_PTR(iVar2) + 0x14E) < 2)) &&
            ((*(u32 *)((u32)*(u8 *)(iVar6 + 0x14E) * 4 + 0x76E700) & 0x80000) == 0)) &&
          (lVar5 = func_00240DB0(param_1), lVar5 != 0)) {
        func_00253300(0x13, param_1);
    }
    if (iVar2 != 0) {
        if (((long long)*(char *)((u8 *)PS2_PTR(iVar2) + 0x19C) << 0x3E < 0) && ((*(u32 *)(iVar6 + 0x13C) & 0x20000) != 0))
        {
            if ((*(u32 *)(puVar7 + 0xC) & 0x40020) == 0) {
                return 0x1C;
            }
            return uVar4;
        }
        if (*((short *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x210))) == 0x6E) {
            uVar8 = *(u32 *)(puVar7 + 0xC);
            if ((uVar8 & 0x20) != 0) {
                return uVar4;
            }
            if ((uVar8 & 0x80) != 0) {
                return 8;
            }
            if ((uVar8 & 0x100) == 0) {
                return uVar4;
            }
            return 0;
        }
    }
    if ((uVar4 == 0x15) || (uVar4 - 10 < 4)) {
        bVar3 = true;
    }
    else {
        bVar3 = false;
    }
    if (((!bVar3) && ((*(u32 *)(puVar7 + 0xC) & 2) != 0)) &&
          ((*(u32 *)(iVar6 + 0x13C) & 0x80000) != 0)) {
        if (((uVar4 == 7) || (uVar4 == 0x13)) || (uVar4 == 0x1C)) {
            uVar4 = 8;
        }
        else {
            uVar4 = 0x15;
        }
    }
    if (((((*(u32 *)(iVar6 + 0x13C) & 2) != 0) &&
              ((iVar2 == 0 || (*(int *)(*(int *)((u8 *)PS2_PTR(iVar2) + 0x210) + 0x14) == 0)))) &&
            (uVar8 = *(u32 *)(puVar7 + 0xC), (uVar8 & 4) != 0)) && ((uVar8 & 0x20) == 0)) {
        if ((uVar8 & 8) == 0) {
            uVar4 = 0x14;
        }
        else if (*(int *)(iVar6 + 0x220) < 1) {
            uVar4 = 0x14;
        }
        else {
            *(u32 *)(iVar6 + 0x200) = *(u32 *)(iVar6 + 0x70);
            *(u32 *)(iVar6 + 0x204) = *(u32 *)(iVar6 + 0x74);
            *(u32 *)(iVar6 + 0x208) = *(u32 *)(iVar6 + 0x78);
            *(u32 *)(iVar6 + 0x20C) = *(u32 *)(iVar6 + 0x7C);
            uVar4 = 0xF;
            *(u8 *)(iVar6 + 0x27C) = *(u8 *)(iVar6 + 0x27C) & 0xFD | 2;
            *(u32 *)(iVar6 + 0x224) = 0;
            *(u32 *)(iVar6 + 0x228) = 0x41A00000;
        }
    }
    if (iVar2 != 0) {
        if (*((u16 *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x210))) - 0x55 < 2) {
            bVar3 = false;
            uVar8 = 0;
            puVar7 = (u16 *)(g_0043D490);
            do {
                if (uVar4 != *puVar7) {
                    bVar3 = true;
                }
                uVar8 = uVar8 + 1;
                puVar7 = puVar7 + 1;
            } while (uVar8 < 3);
            if (!bVar3) {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar4 = g_0043D490[(g_7000015C >> 0x10) % 3];
            }
        }
        if (((1 < *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x14E)) && ((*(u32 *)(iVar6 + 0x13C) & 0x1000000) != 0)) &&
              (-1 < (long long)*(char *)(iVar6 + 0x19E) << 0x3D)) {
            if ((*(u32 *)(iVar6 + 0x13C) & 0x8000) != 0) {
                uVar4 = func_002431F0(param_1, uVar4, 0xFFFFFFFFFFFFFFBF);
            }
            if ((*(u32 *)(iVar6 + 0x13C) & 1) != 0) {
                uVar4 = func_002431F0(param_1, uVar4, 0x41);
            }
        }
    }
    uVar1 = *((u16 *)PS2_PTR(*(ps2ptr *)(iVar6 + 0x210)));
    if (uVar4 == uVar1) {
        if (((uVar1 == 0xD) || (uVar1 == 0xC)) || ((uVar1 == 0xB || ((uVar1 == 10 || (uVar1 == 0x15)))))
              ) {
            uVar8 = *(u32 *)(iVar6 + 0x13C);
            if ((uVar8 & 0x4000000) == 0) {
                if ((uVar8 & 0x8000000) == 0) {
                    if ((uVar8 & 0x10000000) == 0) {
                        if ((uVar8 & 0x20000000) == 0) {
                            uVar4 = 0x15;
                        }
                        else {
                            uVar4 = 0xD;
                        }
                    }
                    else {
                        uVar4 = 0xC;
                    }
                }
                else {
                    uVar4 = 0xB;
                }
            }
            else {
                uVar4 = 10;
            }
            if ((uVar8 & 0x80000) == 0) {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar4 = g_0043D490[(g_7000015C >> 0x10) % 3];
            }
        }
        else if (uVar1 == 0x12) {
            uVar8 = *(u32 *)(iVar6 + 0x13C);
            if (((((uVar8 & 0x4000000) == 0) && ((uVar8 & 0x8000000) == 0)) && ((uVar8 & 0x10000000) == 0)
                    ) && ((uVar8 & 0x20000000) == 0)) {
                uVar4 = 9;
            }
        }
        else if (uVar1 == 0xF) {
            if ((*(u32 *)(iVar6 + 0x13C) & 0x10000) == 0) {
                uVar4 = 0x10;
            }
        }
        else if (((uVar1 == 0x1C) || (uVar1 == 0x13)) || (uVar1 == 7)) {
            uVar8 = *(u32 *)(iVar6 + 0x13C);
            if ((((uVar8 & 0x4000000) == 0) && ((uVar8 & 0x8000000) == 0)) &&
                  (((uVar8 & 0x10000000) == 0 && ((uVar8 & 0x20000000) == 0)))) {
                uVar4 = 8;
            }
            else if (((uVar1 == 0x1C) && (iVar2 != 0)) && (-1 < (long long)*(char *)((u8 *)PS2_PTR(iVar2) + 0x19C) << 0x3E)) {
                uVar4 = 0x13;
            }
        }
        else if (((uVar1 == 6) || (uVar1 == 5)) || ((uVar1 == 4 || (uVar1 == 3)))) {
            uVar8 = *(u32 *)(iVar6 + 0x13C);
            if (((((uVar8 & 0x4000000) == 0) && ((uVar8 & 0x8000000) == 0)) && ((uVar8 & 0x10000000) == 0)
                    ) && ((uVar8 & 0x20000000) == 0)) {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar4 = g_0043D490[(g_7000015C >> 0x10) % 3];
            }
        }
        else if (((uVar1 == 2) || (uVar1 == 1)) || (uVar1 == 0)) {
            uVar8 = *(u32 *)(iVar6 + 0x13C);
            if ((uVar8 & 0x4000000) == 0) {
                if ((uVar8 & 0x8000000) == 0) {
                    if ((uVar8 & 0x10000000) == 0) {
                        if ((uVar8 & 0x20000000) != 0) {
                            uVar4 = 6;
                        }
                    }
                    else {
                        uVar4 = 5;
                    }
                }
                else {
                    uVar4 = 4;
                }
            }
            else {
                uVar4 = 3;
            }
        }
    }
    return uVar4;
}

/* 0x00263180, 0xF4 bytes. */
void func_00263180(int param_1)
{
    u16 * puVar1;

    param_1 = param_1 * 0xC0;
    if ((((*(u32 *)(g_006A3AE8 + param_1) & 2) == 0) && ((*(u32 *)(g_006A3AE8 + param_1) & 0x80) != 0))
          && ((*(u32 *)(*(int *)(g_006A3A40 + param_1) + 0x80) & 0x800) != 0)) {
        *(u16 *)(g_007325A8 + 0x6) = *(u16 *)(g_006A3AB4 + param_1);
        *(u16 *)(g_007325A8) = 0x96;
        *(u16 *)(g_007325A8 + 0x4) = *(u16 *)(g_006A3AB2 + param_1);
        puVar1 = ((u16 *)PS2_PTR(*(ps2ptr *)(g_006A3A98 + param_1)));
        *(u16 *)(g_007325A8 + 0x8) = *(u16 *)(g_006A3AB0 + param_1);
        *(u16 *)(g_007325A8 + 0x2) = (u16)(((int)puVar1 - *(u32 *)(g_005BA6A0)) / 0x2C);
        *(u16 *)(g_007325A8 + 0xC) = puVar1[1];
        *(u16 *)(g_007325A8 + 0xA) = *puVar1;
        *(u8 *)(g_007325A8 + 0xE) = *(u8 *)(*(int *)(g_006A3A40 + param_1) + 0x79);
        *(u8 *)(g_007325A8 + 0xF) = (u8)*(u32 *)(*(int *)(g_006A3A44 + param_1) + 0x118);
        if ((0x238 < *(u16 *)(g_007325A8 + 0x2)) && (*(u16 *)(g_007325A8 + 0x2) < 0x23C)) {
            *(u8 *)(g_007325A8 + 0xF) = 0x23;
        }
    }
}

/* 0x00271610, 0x254 bytes. */
int func_00271610(float param_1, u8 *param_2)
{
    int bVar4;
    float fVar9;
    int iVar2;
    u8 * iVar3;
    int iVar7;
    int iVar8;
    int * piVar6;
    u16 * puVar1;
    u32 uVar5;

    puVar1 = ((u16 *)PS2_PTR(*(ps2ptr *)(param_2 + 0x210)));
    fVar9 = *(float *)(param_2 + 0x21C);
    iVar2 = *(int *)(puVar1 + 10);
    iVar7 = *(short *)(param_2 + 0x178) * 0xC0;
    if ((((*(u32 *)(puVar1 + 0xC) & 0x400000) != 0) || (*puVar1 - 0xD4 < 2)) &&
          (*(short *)(g_006A3AB8 + iVar7) < 1)) {
        if (*puVar1 - 0xD4 < 2) {
            if ((fVar9 <= (float)(int)*(short *)((u8 *)PS2_PTR(iVar2) + 0x22)) &&
                  ((float)(int)*(short *)((u8 *)PS2_PTR(iVar2) + 0x22) < fVar9 + param_1)) {
                return true;
            }
        }
        else {
            if (iVar2 == 0) {
                return *(u32 *)g_00669DB8 != 4;
            }
            if ((iVar2 == 0) || ((*(u32 *)((u8 *)PS2_PTR(iVar2) + 0x28) & 0x800000) == 0)) {
                iVar3 = (u8 *)PS2_PTR(*(int *)(param_2 + 0x110));
                iVar8 = *(int *)(iVar3 + 8) + (u32)*puVar1 * 0x20;
                if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x1C) & 0x40000000) == 0) {
                    if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x1C) & 0x80000000) == 0) {
                        piVar6 = (int *)(*(int *)(((u32)*(u8 *)(iVar3 + 0x1C) * 0xC +
                                                                            (u32)*(u8 *)(iVar3 + 0x1C)) * 0x10 + 0x5B5078) +
                                                        (u32)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2) * 0x20);
                    }
                    else {
                        piVar6 = (int *)(*(int *)(((u32)*(u8 *)(iVar3 + 0x1C) * 0xC +
                                                                            (u32)*(u8 *)(iVar3 + 0x1C)) * 0x10 + 0x5B50C8) +
                                                        (u32)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2) * 0x20);
                    }
                }
                else {
                    piVar6 = (int *)(*(u32 *)g_005BA688 + (u32)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2) * 0x20);
                }
                uVar5 = *(int *)(*piVar6 + 8) - 1;
            }
            else {
                uVar5 = (u32)*(u8 *)((u8 *)PS2_PTR(iVar2) + 6);
            }
            if ((float)(int)uVar5 - 1.0 <= fVar9) {
                return true;
            }
        }
    }
    if ((((*puVar1 != 0xD5) || ((float)(int)*(short *)((u8 *)PS2_PTR(iVar2) + 0x22) < fVar9)) ||
            (fVar9 + param_1 <= (float)(int)*(short *)((u8 *)PS2_PTR(iVar2) + 0x22))) ||
          ((0 < *(short *)(g_006A3AB8 + iVar7) && ((*(u32 *)(param_2 + 0x13C) & 0x20000) != 0)))) {
        bVar4 = false;
    }
    else {
        bVar4 = true;
    }
    return bVar4;
}

/* 0x00271870, 0x19C bytes. */
void func_00271870(void)
{
    int bVar1;
    int iVar3;
    u8 * iVar4;
    u32 uVar2;

    iVar3 = 0;
    iVar4 = g_00574DE0;
    do {
        if ((long long)*(char *)(iVar4 + 0x198) << 0x3E < 0) {
            if (*((u16 *)PS2_PTR(*(ps2ptr *)(iVar4 + 0x210))) - 0x13 < 7) {
                if (1 < *(u8 *)(iVar4 + 0x14E)) {
                    func_001523C0(iVar4);
                }
            }
            else if ((*(short *)(*(short *)(iVar4 + 0x178) * 0xC0 + 0x6A3AB2) == 0) &&
                            (*(int *)(iVar4 + 0x118) < 0x3C)) {
                uVar2 = *(u32 *)(((u16 *)PS2_PTR(*(ps2ptr *)(iVar4 + 0x210))) + 0xC);
                if (((uVar2 & 0x8000060) == 0) && ((long long)*(char *)(iVar4 + 0x19C) << 0x3A < 0)) {
                    func_001523C0(iVar4);
                }
                else if (((uVar2 & 0x20) != 0) && ((uVar2 & 0x800) == 0)) {
                    func_001CCFA0(iVar4);
                    bVar1 = *(u8 *)(iVar4 + 0x19C);
                    *(u8 *)(iVar4 + 0x19C) = bVar1 & 0xFB | 4;
                    *(u8 *)(iVar4 + 0x19C) = bVar1 & 0xF3 | 4;
                    *(u16 *)(iVar4 + 300) = 0x20;
                    *(u16 *)(iVar4 + 0x12E) = 0x20;
                    if (*(u8 *)(iVar4 + 0x14E) < 2) {
                        *(u32 *)(g_00669F60) = *(u32 *)(g_00669F60) | 0x20000000;
                    }
                }
            }
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x630;
    } while (iVar3 < 0x8F);
}

/* 0x00272A70, 0xF0 bytes. */
void func_00272A70(u8 *param_1)
{
    float fVar4;
    u8 * puVar1;
    u8 * puVar2;
    int uStack_2;
    u32 uVar3;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10)));
    *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1 + 1);
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x14)));
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar2 + 1);
    uVar3 = func_001D6BD0(&uStack_2, *(u32 *)(param_1 + 0xC), *puVar1, *puVar2);
    *(u32 *)(param_1 + 0xC) = uVar3;
    fVar4 = ((float)uStack_2 * 50.0) / 60.0;
    if (2.1474836e+09 <= fVar4) {
        fVar4 = fVar4 - 2.1474836e+09;
    }
    func_0017DEA0((int)fVar4 & 0xFFFF);
}

/* 0x002D7FF0, 0x38 bytes. */
void func_002D7FF0(u8 *param_1)
{
    u8 * puVar1;
    u32 uVar2;

    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)(param_1 + 0xC)));
    uVar2 = 0;
    do {
        uVar2 = uVar2 + 1;
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
    } while (uVar2 < 0x97000);
    *(u32 *)(*(int *)(param_1 + 0xC) + 0xC) = 0;
}
