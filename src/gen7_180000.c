/*
 * gen7_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
 * output (access widths from the disassembly) and kept only when their compiled size is within
 * 10 % of the original. Machine-like
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

extern u8 g_004124F0[0xC];
extern u8 g_0043C120[0x400];
extern u8 g_0043C55C[0x4];
extern u8 g_0043C648[0x4];
extern u8 g_0043C6D4[0x4];
extern u8 g_0043C7D8[0x4];
extern u8 g_0043C808[0x4];
extern u8 g_0043C828[0x4];
extern u8 g_0043C83C[0x4];
extern u8 g_004593A8[0x400];
extern u8 g_0056CCA4[0x24];
extern u8 g_005BA6A0[0x4];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007B98A4[0xDE];
extern u8 g_007BA85D[0x1];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */

int func_001204B0();
int func_002C7310();
int func_0030D7D0();
int func_0030D800();
int func_0030D810();
int func_0032D3C0();
int func_00373A70();
int func_0037F610();
int func_0037FD50();
int func_00381CA0();

/* 0x002D32B0, 0x1DC bytes. */
void func_002D32B0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar2;
    int iVar3;
    int uVar1;

    iVar2 = func_002F27D0(param_5);
    uVar1 = *(u8 *)(*(u32 *)g_005BA6A0 + iVar2 * 0x2C + 7);
    iVar2 = func_0017CA50(uVar1, 0);
    iVar3 = func_0017CA50(uVar1, 1);
    *(u32 *)(g_0056CCA4) = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    func_00146B40(((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar2 + 0x21F])), param_1 + 0x90,
                              param_2 + *(int *)(g_004124F0 + param_6 * 0x20) + 0x1E, 0x160, 0x10, param_4, 0);
    *(u32 *)(g_0056CCA4) = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    func_00146B40(((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar3 + 0x21F])), param_1 + 0x90,
                              param_2 + *(int *)((g_004124F0 + 0x8) + param_6 * 0x20) + 0x1E, 0x160, 0x10, param_4, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)(g_0056CCA4) = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
}

/* 0x00373B60, 0x290 bytes. */
void func_00373B60(void)
{
    u32 auStack_20[8];
    int bVar1;
    int iVar7;
    long long lVar3;
    u32 * puVar6;
    u32 uVar2;
    unsigned long long uVar4;
    unsigned long long uVar5;

    bVar1 = *(u32 *)g_007B98A4 == 6;
    if (*(u32 *)(g_007B98A4 + 0x10) == 1) {
        lVar3 = func_00373A10();
        if (lVar3 == 0) {
            if (bVar1) {
                uVar4 = PS2_ADDR(func_00365490());
            }
            else {
                uVar4 = func_0030D7D0();
            }
            uVar5 = func_00374E00();
            func_0037FD50(uVar4, 0x40, 100, uVar5);
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C7D8))), 0x80, 1);
        }
        else {
            if (bVar1) {
                uVar4 = PS2_ADDR(func_00365490());
            }
            else {
                uVar4 = func_0030D7D0();
            }
            uVar5 = func_00374E00();
            uVar5 = func_0030AFF0(uVar5);
            func_0039D610((u8 *)PS2_PTR(uVar4), uVar5, bVar1);
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C7D8))), 0x80, 1);
        }
    }
    else if (*(u32 *)(g_007B98A4 + 0x10) == 2) {
        if (bVar1) {
            uVar4 = PS2_ADDR(func_00365490());
        }
        else {
            uVar4 = func_0030D7D0();
        }
        func_0032D3C0(uVar4);
    }
    else {
        if (*(u32 *)g_007B98A4 == 8) {
            uVar4 = func_00374E00();
            uVar4 = func_0030AFF0(uVar4);
            iVar7 = 0;
            puVar6 = auStack_20;
            do {
                uVar2 = func_002F9390(uVar4, iVar7);
                *puVar6 = uVar2;
                iVar7 = iVar7 + 1;
                puVar6[3] = 0;
                puVar6 = puVar6 + 1;
            } while (iVar7 < 3);
            uVar5 = func_0030D7D0();
            func_0037F610(uVar5, 0x140, 0x3A, uVar4, auStack_20);
        }
        else {
            func_00386900(*(u32 *)(g_007B98A4 + 0xC), *(u16 *)(g_007B98A4 + 0xDC), 0x140, 0x34, 0, 1, bVar1);
        }
        func_00373A70();
        if (bVar1) {
            func_00368CB0();
        }
        else if (*(u32 *)g_007B98A4 == 8) {
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C83C))), 0x80, 1);
        }
        else if (*(u32 *)g_007B98A4 == 7) {
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C828))), 0x80, 1);
        }
        else {
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C808))), 0x80, 1);
        }
    }
}

/* 0x00395C90, 0x18C bytes. */
void func_00395C90(void)
{
    u8 auStack_80[128];
    int iVar1;
    unsigned long long uVar2;

    if ((long long)(*(char *)g_007BA85D) << 0x3F < 0) {
        func_002C7310(0xE8, 0x126, 0, 0x110, 0x2C, 0x80, 0);
        *(u32 *)(g_0056CCA4) = 6;
        *(u32 *)(g_0056CCA4 + 0x4) = 6;
        *(u32 *)(g_0056CCA4 + 0x8) = 6;
        *(u32 *)(g_0056CCA4 + 0xC) = 6;
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41A00000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41A00000;
        uVar2 = PS2_ADDR(func_00372A00());
        func_00146270((u8 *)PS2_PTR(uVar2), 0xF0, 0x12A, 1, 0);
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
        iVar1 = func_003956B0();
        func_001204B0(auStack_80, ((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar1 + 0x2FF])));
        *(u32 *)(g_0056CCA4) = 6;
        *(u32 *)(g_0056CCA4 + 0x4) = 6;
        *(u32 *)(g_0056CCA4 + 0x8) = 6;
        *(u32 *)(g_0056CCA4 + 0xC) = 6;
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        func_00146B40(auStack_80, 0xF0, 0x13E, 0x100, 0x10, 1, 0);
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
    }
}

/* 0x0039DF30, 0xE4 bytes. */
void func_0039DF30(void)
{
    int aiStack_20[8];
    int bVar1;
    u8 * iVar2;
    int iVar4;
    int iVar5;
    unsigned long long uVar3;

    iVar2 = (u8 *)(func_002FC2C0());
    iVar2 = (u8 *)PS2_PTR(*(int *)(iVar2 + 0x6AC));
    bVar1 = *(u8 *)(iVar2 + 0x26);
    func_003DC180(0xF, 0, aiStack_20);
    func_002C7310(aiStack_20[0], 0x58, 0, 0x128, (u32)bVar1 * 0x18 + 0x10, 0x80, 1);
    iVar5 = 0;
    if (bVar1 != 0) {
        iVar4 = 0x60;
        do {
            uVar3 = func_0030D7D0();
            func_00381DF0(uVar3, aiStack_20[0] + 8, iVar4, *(u8 *)(iVar2 + iVar5 + 0x20), 0, 1);
            iVar5 = iVar5 + 1;
            iVar4 = iVar4 + 0x18;
        } while (iVar5 < (int)(u32)bVar1);
    }
    func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C55C))), 0x80, 1);
}

/* 0x0039E2F0, 0x8C bytes. */
void func_0039E2F0(void)
{
    u8 * iVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    iVar1 = (u8 *)(func_002FC2C0());
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar1 + 0x6AC));
    uVar2 = func_0030D800();
    uVar3 = func_0030D810();
    func_003F0EC0(uVar2, uVar3, iVar1 + 0x28);
    if (*(int *)(iVar1 + 0x168) < 2) {
        func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C55C))), 0x80, 1);
    }
    else {
        func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C648))), 0x80, 1);
    }
}

/* 0x003BD230, 0x60 bytes. */
void func_003BD230(void)
{
    u8 * iVar1;
    u8 * iVar2;

    iVar1 = func_00390940();
    iVar2 = func_003BD210();
    func_003B3DD0(1, *(u32 *)(iVar2 + 0x18));
    if (*(int *)(iVar1 + 0x8E6C) == 4) {
        func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C6D4))), 0x80, 2);
    }
}
