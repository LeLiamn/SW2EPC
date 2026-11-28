/*
 * gen_1e8000.c - small functions between 0x001E8000 and 0x001F0000, generated from Ghidra
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
int func_001EB8C0();
int func_001EE3B0();

extern u8 g_0040CCA0[0x2C];
extern u8 g_005BD738[0x4];
extern u8 g_00669D81[0x1];
extern u8 g_00669F60[0x4];
extern u8 g_00669F9C[0x4];
extern int g_0045D400;   /* (small data) */
extern int g_0045D404;   /* (small data) */
extern int g_0045D408;   /* (small data) */

int func_001E9960();
int func_001EA230();
int func_001EB630();
int func_001EB970();
int func_001ED580();
int func_001EF900();

/* 0x001E97D0, 0x7C bytes. */
void func_001E97D0(void)
{
    if (g_0045D400 != 0) {
        if (g_0045D400 == 2) {
            func_001EA650();
        }
        else if (g_0045D400 == 1) {
            func_001E9960();
        }
        else if (g_0045D400 == 3) {
            func_001E9960();
            func_001EA650();
        }
    }
}

/* 0x001EA650, 0x2C bytes, matching. */
void func_001EA650(void)
{
    func_00102EC0((u8 *)PS2_PTR(g_0045D408));
    g_0045D408 = 0;
    func_00102EC0((u8 *)PS2_PTR(g_0045D404));
    g_0045D404 = 0;
}

/* 0x001EAC00, 0x84 bytes. */
void func_001EAC00(int param_1, int param_2)
{
    int iVar1;
    int lVar2;

    if ((*(u32 *)g_00669F60 & 0x14000008) == 0) {
        iVar1 = *(int *)((int)param_1 + 0x68);
        if (7 < iVar1) {
            *(u32 *)((int)param_1 + 0x68) = 0;
            lVar2 = func_001F0C50(param_2);
            if (lVar2 != 0) {
                if (iVar1 < 0) {
                    iVar1 = iVar1 + 7;
                }
                func_001EA860((u8 *)PS2_PTR(param_1), iVar1 >> 3, 0);
            }
        }
    }
}

/* 0x001EBA60, 0xD8 bytes. */
void func_001EBA60(int param_1, int param_2)
{
    int iVar1;

    iVar1 = (int)param_1;
    if ((*(u32 *)(iVar1 + 0x84) & 0x10) != 0) {
        func_001EB970();
        *(u32 *)(iVar1 + 0x84) = *(u32 *)(iVar1 + 0x84) & 0xFFFFFFCF;
    }
    if ((*(u32 *)(iVar1 + 0x84) & 0x20) == 0) {
        func_001EB8C0(param_1);
        func_001EB860((u8 *)PS2_PTR(param_1));
        *(u32 *)(iVar1 + 0x84) = *(u32 *)(iVar1 + 0x84) | 0x20;
    }
    if (param_2 != 0) {
        func_001EB630(param_1);
    }
    if (((*(short *)(iVar1 + 0x46) == *(short *)(iVar1 + 0x48)) &&
            (*(u32 *)(iVar1 + 0x84) = *(u32 *)(iVar1 + 0x84) & 0xFFFFFFDF,
            *(short *)(iVar1 + 0x40) == *(short *)(iVar1 + 0x44))) && (*(char *)(iVar1 + 0x7A) != 3))
    {
        *(u32 *)(iVar1 + 0x84) = *(u32 *)(iVar1 + 0x84) | 0x10;
    }
}

/* 0x001EBC20, 0x48 bytes. */
void func_001EBC20(int param_1)
{
    if ((*(u32 *)g_00669F60 & 0x14000008) == 0) {
        func_001D4C00((u8 *)PS2_PTR(param_1));
        func_001EE3B0(param_1);
    }
}

/* 0x001EBC70, 0x94 bytes, matching. */
void func_001EBC70(int param_1)
{
    int iVar1;
    int iVar3;
    int lVar2;

    iVar3 = (int)param_1;
    iVar1 = *(int *)(iVar3 + 0x18);
    lVar2 = func_001F02F0((u8 *)PS2_PTR(param_1));
    if (lVar2 == 0) {
        if (iVar1 != 0) {
            func_001ED160(param_1, iVar1, 0);
            *(u32 *)(iVar3 + 0x18) = 0;
            *(u32 *)(iVar3 + 0x84) = *(u32 *)(iVar3 + 0x84) | 0x10;
        }
        *(u8 *)(iVar3 + 0x7A) = 0;
    }
    else if ((*(u32 *)(iVar1 + 0x80) & 0x20000) == 0) {
        *(u8 *)(iVar3 + 0x7A) = 1;
        func_001ED160(param_1, iVar1, 0);
    }
}

/* 0x001EBEE0, 0xD8 bytes. */
void func_001EBEE0(int param_1, int param_2)
{
    int iVar3;
    int lVar2;
    u32 uVar1;

    iVar3 = (int)param_1;
    if (((*(u32 *)(iVar3 + 0x84) & 1) == 0) && (lVar2 = func_001F02F0((u8 *)PS2_PTR(param_1)), lVar2 != 0)) {
        uVar1 = *(u32 *)(iVar3 + 0x18);
        lVar2 = func_001EF900(param_1, uVar1);
        if (lVar2 == 0) {
            func_001EBB40(param_1, 0);
            func_001EBA60(param_1, param_2);
        }
        else {
            *(u8 *)(iVar3 + 0x7A) = 2;
            func_001ED160(param_1, uVar1, 1);
        }
    }
    else {
        *(u8 *)(iVar3 + 0x7A) = 0;
        if (*(int *)(iVar3 + 0x18) != 0) {
            func_001ED160(param_1, *(int *)(iVar3 + 0x18), 0);
            *(u32 *)(iVar3 + 0x18) = 0;
            *(u32 *)(iVar3 + 0x84) = *(u32 *)(iVar3 + 0x84) | 0x10;
        }
    }
}

/* 0x001EC4E0, 0x44 bytes, matching. */
void func_001EC4E0(int param_1)
{
    int lVar1;

    lVar1 = func_001F03E0((u8 *)PS2_PTR(param_1));
    if ((lVar1 == 0) && ((*(u32 *)((int)param_1 + 0x80) & 0x1800) == 0)) {
        func_001ED580(param_1);
    }
}

/* 0x001ECB20, 0xE4 bytes. */
int func_001ECB20(int param_1, int param_2)
{
    int bVar1;
    int iVar4;
    int lVar2;
    int lVar3;

    iVar4 = 2;
    if (((param_2 != 0) && ((*(u32 *)(param_1 + 0x80) & 0x400) != 0)) &&
          (lVar2 = PS2_ADDR(func_0034A740((u8 *)PS2_PTR(param_1))), bVar1 = *(u8 *)g_00669D81, lVar2 != 0)) {
        lVar3 = func_0033B3B0((u8 **)PS2_PTR(lVar2));
        if (lVar3 == 0) {
            lVar3 = func_0033B5E0((u8 **)PS2_PTR(lVar2));
            if (lVar3 == 0) {
                lVar2 = func_0033B630((u8 **)PS2_PTR(lVar2));
                if (lVar2 != 0) {
                    iVar4 = *(int *)((g_0040CCA0 + 0x28) + (u32)bVar1 * 4) + 2;
                }
            }
            else {
                iVar4 = *(int *)((g_0040CCA0 + 0x14) + (u32)bVar1 * 4) + 2;
            }
        }
        else {
            iVar4 = *(int *)(g_0040CCA0 + (u32)bVar1 * 4) + 2;
        }
    }
    return iVar4;
}

/* 0x001ED160, 0xD8 bytes. */
void func_001ED160(int param_1, int param_2, int param_3)
{
    int iVar1;
    int iVar2;
    u32 uVar3;
    u32 uVar4;

    if (((*(u32 *)(param_2 + 0x80) & 0x1800) != 0) && (*(u32 *)(param_2 + 0x10) < 0x47)) {
        iVar1 = *(u32 *)(param_2 + 0x10) * 0x68 + 0x6A1D58;
        if (param_3 == 0) {
            uVar3 = 0;
            iVar2 = iVar1;
            do {
                if (*(int *)(iVar2 + 0x34) == param_1) {
                    *(u32 *)(uVar3 * 4 + iVar1 + 0x34) = 0;
                    return;
                }
                uVar3 = uVar3 + 1;
                iVar2 = iVar2 + 4;
            } while (uVar3 < 5);
        }
        else {
            uVar3 = 5;
            uVar4 = 0;
            iVar2 = iVar1;
            do {
                if (*(int *)(iVar2 + 0x34) == param_1) {
                    return;
                }
                if (*(int *)(iVar2 + 0x34) == 0) {
                    uVar3 = uVar4;
                }
                uVar4 = uVar4 + 1;
                iVar2 = iVar2 + 4;
            } while (uVar4 < 5);
            if (uVar3 < 5) {
                *(int *)(uVar3 * 4 + iVar1 + 0x34) = param_1;
            }
        }
    }
}

/* 0x001EE6B0, 0xA0 bytes. */
void func_001EE6B0(int param_1, int param_2)
{
    int iVar2;
    int uVar1;
    u32 uVar3;

    iVar2 = (int)param_1;
    if (param_2 != *(u8 *)(iVar2 + 0x78)) {
        uVar3 = *(u32 *)(iVar2 + 0x80) & 0x20000;
        if (uVar3 != 0) {
            func_001B9A40((u8 *)PS2_PTR(param_1));
        }
        func_001F1910((u8 *)PS2_PTR(param_1));
        *(u8 *)(iVar2 + 0x78) = param_2;
        if (*(int *)(iVar2 + 4) != 0) {
            *(u16 *)(*(int *)(iVar2 + 4) + 8) = (u16)param_2;
        }
        uVar1 = func_001F0570(param_2);
        *(u8 *)(iVar2 + 0x7F) = uVar1;
        func_001F1A30((u8 *)PS2_PTR(param_1));
        if (uVar3 != 0) {
            func_001BAF20((u8 *)PS2_PTR(param_1));
        }
    }
}

/* 0x001EE750, 0x218 bytes. */
void func_001EE750(int param_1, int param_2)
{
    int iVar1;
    int iVar2;
    int * piVar3;
    int * piVar4;
    u32 uVar5;
    u32 uVar6;

    iVar2 = (int)param_1;
    if (param_2 != *(u8 *)(iVar2 + 0x79)) {
        uVar6 = *(u32 *)(iVar2 + 0x80) & 0x20000;
        if (uVar6 != 0) {
            func_001B9A40((u8 *)PS2_PTR(param_1));
        }
        func_001F1910((u8 *)PS2_PTR(param_1));
        uVar5 = *(u32 *)(iVar2 + 0x80) & 8;
        if ((uVar5 == 0) && ((*(u32 *)(iVar2 + 0x80) & 0x200000) == 0)) {
            piVar3 = (int *)((u32)*(u8 *)(iVar2 + 0x79) * 4 + 0x6AA5BC);
            iVar1 = *piVar3;
            if (0 < iVar1) {
                *piVar3 = iVar1 + -1;
            }
        }
        if (*(char *)(iVar2 + 0x79) == 0) {
            *(u32 *)(iVar2 + 0x84) = *(u32 *)(iVar2 + 0x84) | 0x10000;
        }
        *(u8 *)(iVar2 + 0x79) = param_2;
        if ((*(int *)(iVar2 + 4) != 0) && ((*(u32 *)(iVar2 + 0x80) & 0x800) != 0)) {
            *(u8 *)(*(int *)(iVar2 + 4) + 0x16) = param_2;
        }
        if ((*(u32 *)(iVar2 + 0x80) & 0x400000) != 0) {
            func_001EEB70(param_1);
        }
        if (*(int *)(iVar2 + 0x18) != 0) {
            func_001ED160(param_1, *(int *)(iVar2 + 0x18), 0);
            *(u32 *)(iVar2 + 0x18) = 0;
            *(u32 *)(iVar2 + 0x84) = *(u32 *)(iVar2 + 0x84) | 0x10;
        }
        *(u32 *)(iVar2 + 0x1C) = 0;
        *(u32 *)(iVar2 + 0x84) = *(u32 *)(iVar2 + 0x84) | 0x10;
        *(u8 *)(iVar2 + 0x7A) = 0;
        if (((*(u32 *)(iVar2 + 0x80) & 0x1800) != 0) && (*(u32 *)(iVar2 + 0x10) < 0x47)) {
            *(u32 *)(g_005BD738) = 1;
            iVar2 = *(u32 *)(iVar2 + 0x10) * 0x68;
            *(u32 *)(iVar2 + 0x6A1D8C) = 0;
            *(u32 *)(iVar2 + 0x6A1D90) = 0;
            *(u32 *)(iVar2 + 0x6A1D94) = 0;
            *(u32 *)(iVar2 + 0x6A1D98) = 0;
            *(u32 *)(iVar2 + 0x6A1D9C) = 0;
        }
        if (uVar5 == 0) {
            piVar4 = (int *)((u32)param_2 * 4 + 0x6AA5BC);
            piVar3 = (int *)((u32)param_2 * 4 + 0x6AA5B0);
            iVar2 = *piVar4 + 1;
            *piVar4 = iVar2;
            if (*piVar3 < iVar2) {
                *piVar3 = iVar2;
            }
        }
        func_001F1A30((u8 *)PS2_PTR(param_1));
        if (uVar6 != 0) {
            func_001BAF20((u8 *)PS2_PTR(param_1));
        }
    }
}

/* 0x001EEB70, 0x80 bytes. */
void func_001EEB70(int param_1)
{
    int lVar1;

    if (((*(u32 *)(param_1 + 0x80) & 0x400000) != 0) &&
          (lVar1 = func_00215480(param_1 + 0x40), lVar1 != 0)) {
        if (((*(u32 *)(param_1 + 0x80) & 0x40002) == 0) && ((*(u32 *)(param_1 + 0x84) & 0x400) == 0))
        {
            *(u8 *)((int)lVar1 + 1) = *(u8 *)(param_1 + 0x79);
        }
        else {
            *(u8 *)((int)lVar1 + 1) = 0xFF;
        }
    }
}

/* 0x001EEBF0, 0x60 bytes. */
void func_001EEBF0(int param_1)
{
    int iVar1;

    iVar1 = (int)param_1;
    *(u32 *)(iVar1 + 0x80) = *(u32 *)(iVar1 + 0x80) & 0xFFFBFFFF;
    *(u32 *)(iVar1 + 0x6C) = (*(u32 *)(g_00669F9C));
    func_001F1A30((u8 *)PS2_PTR(param_1));
    if ((*(u32 *)(iVar1 + 0x80) & 0x400000) != 0) {
        func_001EEB70(param_1);
    }
}

/* 0x001EEC50, 0x88 bytes. */
void func_001EEC50(int param_1)
{
    int iVar1;

    iVar1 = (int)param_1;
    if ((*(u32 *)(iVar1 + 0x80) & 0x20000) != 0) {
        func_001B9A40((u8 *)PS2_PTR(param_1));
    }
    func_001F1910((u8 *)PS2_PTR(param_1));
    *(u32 *)(iVar1 + 0x80) = *(u32 *)(iVar1 + 0x80) | 0x40000;
    if (*(int *)(iVar1 + 0x18) != 0) {
        func_001ED160(param_1, *(int *)(iVar1 + 0x18), 0);
    }
    if ((*(u32 *)(iVar1 + 0x80) & 0x400000) != 0) {
        func_001EEB70(param_1);
    }
}

/* 0x001EECE0, 0x100 bytes. */
void func_001EECE0(int param_1, int param_2)
{
    int iVar2;
    int iVar4;
    int sVar1;
    int sVar3;

    if ((*(u32 *)(param_1 + 0x80) & 0x20000) != 0) {
        func_001B9A40((u8 *)PS2_PTR(param_1));
    }
    iVar4 = (int)*(short *)(param_1 + 0x56) + (*(short *)(param_1 + 0x56) * param_2) / 100;
    iVar2 = iVar4;
    if (1000 < iVar4) {
        iVar2 = 1000;
    }
    if (iVar2 < 2) {
        sVar3 = 1;
    }
    else {
        if (1000 < iVar4) {
            iVar4 = 1000;
        }
        sVar3 = (short)iVar4;
    }
    sVar1 = sVar3;
    if (1000 < sVar3) {
        sVar1 = 1000;
    }
    if (sVar1 < 2) {
        *(u16 *)(param_1 + 0x56) = 1;
    }
    else {
        if (1000 < sVar3) {
            sVar3 = 1000;
        }
        *(short *)(param_1 + 0x56) = sVar3;
    }
}

/* 0x001EEDE0, 0x100 bytes. */
void func_001EEDE0(int param_1, int param_2)
{
    int iVar2;
    int iVar4;
    int sVar1;
    int sVar3;

    if ((*(u32 *)(param_1 + 0x80) & 0x20000) != 0) {
        func_001B9A40((u8 *)PS2_PTR(param_1));
    }
    iVar4 = (int)*(short *)(param_1 + 0x54) + (*(short *)(param_1 + 0x54) * param_2) / 100;
    iVar2 = iVar4;
    if (1000 < iVar4) {
        iVar2 = 1000;
    }
    if (iVar2 < 2) {
        sVar3 = 1;
    }
    else {
        if (1000 < iVar4) {
            iVar4 = 1000;
        }
        sVar3 = (short)iVar4;
    }
    sVar1 = sVar3;
    if (1000 < sVar3) {
        sVar1 = 1000;
    }
    if (sVar1 < 2) {
        *(u16 *)(param_1 + 0x54) = 1;
    }
    else {
        if (1000 < sVar3) {
            sVar3 = 1000;
        }
        *(short *)(param_1 + 0x54) = sVar3;
    }
}
