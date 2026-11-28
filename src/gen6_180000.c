/*
 * gen6_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_00799A20[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_001ECEA0();

#define true 1
#define false 0

extern u8 g_00442420[0x10];
extern u8 g_00447848[0x4];
extern u8 g_004479E0[0x4];
extern u8 g_00459B60[0x8];
extern u8 g_0045D898[0x4];
extern u8 g_0056CCA4[0x24];
extern u8 g_00669DB8[0x4];
extern u8 g_00669F60[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_00693703[0x1];
extern u8 g_0069382B[0x1];
extern u8 g_00693953[0x1];
extern u8 g_0073C79D[0x1];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_00799A74[0x4];
extern u8 g_007BA8B0[0x10];
extern u8 g_007BA8C8[0x4];
extern u8 g_007BAC0D[0x1];
extern u8 g_007BAE74[0x1C];
extern u8 g_007BAE7C[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D5F0;   /* (small data) */
extern int g_0045D5F4;   /* (small data) */
extern int g_0045D5FC;   /* (small data) */
extern int g_0045D6DC;   /* (small data) */
extern int g_0045D6E0;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern int g_70000150;   /* (small data) */
extern int g_70000154;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */

int func_001204B0();
int func_001BEA30();
int func_001FF100();
void *func_001FF140();
int func_001FF230();
int func_0022DD50();
int func_0022DD60();
int func_0022DD70();
int func_00243F10();
int func_00244260();
int func_002F7D90();
int func_0030D7D0();
int func_0032F420();
int func_00388DA0();
int func_00389090();
int func_003F55E0();

/* 0x001DEFB0, 0x15C bytes. */
void func_001DEFB0(int param_1, int param_2)
{
    int iVar1;
    long long lVar4;
    u16 * puVar2;
    u32 uVar3;
    unsigned long long uVar5;
    u32 uVar6;
    unsigned long long uVar7;

    uVar7 = 0x19F;
    uVar6 = 0;
    lVar4 = func_0020E1F0();
    if (lVar4 != 0) {
        uVar6 = (u32)(*(u8 *)g_0073C79D);
    }
    if ((param_1 & 0xFFFF) < 0x20) {
        if ((((param_2 == 0x3BA) || (param_2 == 0x3B9)) || (param_2 == 0x3B8)) ||
              ((param_2 == 0x3B7 || (param_2 == 0x3B6)))) {
            uVar5 = func_0032F420((int)param_2 + -0x3B5);
            uVar7 = func_00337A10(uVar5);
        }
        else if (param_2 == 900) {
            uVar5 = func_0032F420(0);
            uVar7 = func_00337A10(uVar5);
        }
        else if (param_2 == 1000) {
            iVar1 = PS2_ADDR(func_0035DD10(uVar6));
            puVar2 = (u16 *)func_00338410((iVar1 + -0x6A1D58) / 0x68);
            uVar7 = (unsigned long long)*puVar2;
        }
        if (uVar7 != 0x19F) {
            uVar3 = func_002F6980(uVar7);
            *(u32 *)PS2_PTR((((param_1 & 0xFFFF) + uVar6) * 4 + 0x730E50)) = uVar3;
        }
    }
}

/* 0x001EA680, 0x1DC bytes. */
int func_001EA680(u8 *param_1, u32 *param_2)
{
    int iVar3;
    u8 * iVar6;
    int sVar1;
    int sVar2;
    int sVar5;
    u32 uVar10;
    unsigned long long uVar11;
    int uVar4;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    uVar11 = 0;
    iVar6 = param_1;
    uVar8 = (u32)*(u8 *)(iVar6 + 0x74);
    sVar5 = *(short *)(iVar6 + 0x4E);
    uVar9 = 0;
    uVar10 = 0;
    if (uVar8 == 0) {
        if (sVar5 == 0) {
            uVar8 = *(u32 *)(iVar6 + 0x80);
            *(u32 *)(iVar6 + 0x80) = uVar8 | 2;
            uVar10 = 1;
            if ((uVar8 & 4) == 0) {
                uVar11 = 1;
            }
        }
        *param_2 = uVar10;
    }
    else {
        uVar10 = (int)*(short *)(iVar6 + 0x52) - (int)sVar5;
        iVar3 = func_001ECEA0(param_1, 0);
        if (uVar8 == 0) {
            uVar7 = 0;
        }
        else {
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            uVar7 = (g_7000015C >> 0x10) % uVar8;
        }
        if (uVar7 == 0) {
            uVar7 = uVar8 - 1;
            if ((int)uVar10 <= (int)(iVar3 * uVar7)) {
                uVar4 = (u8)uVar7;
                uVar9 = 1;
                if (9 < (uVar7 & 0xFF)) {
                    uVar4 = 9;
                }
                *(u8 *)(iVar6 + 0x74) = uVar4;
                uVar8 = uVar7;
            }
        }
        if ((int)uVar10 < (int)uVar8) {
            uVar4 = (u8)uVar10;
            if (9 < (uVar10 & 0xFF)) {
                uVar4 = 9;
            }
            *(u8 *)(iVar6 + 0x74) = uVar4;
            uVar9 = uVar9 + (uVar8 - uVar10);
        }
        else if ((int)(iVar3 * uVar8) < (int)uVar10) {
            sVar5 = sVar5 + (short)(iVar3 * uVar8);
            sVar2 = *(short *)(iVar6 + 0x50);
            sVar1 = sVar5;
            if (sVar2 < sVar5) {
                sVar1 = sVar2;
            }
            if (sVar1 < 1) {
                sVar2 = 0;
            }
            else if (sVar5 <= sVar2) {
                sVar2 = sVar5;
            }
            *(short *)(iVar6 + 0x52) = sVar2;
        }
        func_001F17D0(iVar6 + 0x40, *(u8 *)(iVar6 + 0x79), uVar9 & 0xFF);
        *param_2 = uVar9;
    }
    return uVar11;
}

/* 0x001FA790, 0x2C8 bytes. */
void func_001FA790(void)
{
    u8 * iVar1;
    int iVar2;
    int iVar5;
    int iVar7;
    int iVar8;
    long long lVar3;
    unsigned long long uVar4;
    unsigned long long uVar6;

    iVar1 = (u8 *)PS2_PTR(*(int *)PS2_PTR((g_70000150 * 4 + 0x732500)));
    func_003F55E0();
    func_003F5620();
    lVar3 = func_003F5650();
    if (lVar3 == 0) {
        func_001FA710();
    }
    else if (((*(u32 *)g_00669F60 & 2) == 0) ||
                    (((*(char *)g_00693703 == 0 && (*(char *)g_0069382B == 0)) && (*(char *)g_00693953 == 0)))) {
        uVar4 = PS2_ADDR(func_003F5760());
        iVar2 = func_00146D80((u8 *)PS2_PTR(uVar4), 0, 0);
        *(u32 *)(g_0056CCA4) = 6;
        *(u32 *)(g_0056CCA4 + 0x4) = 6;
        *(u32 *)(g_0056CCA4 + 0x8) = 6;
        *(u32 *)(g_0056CCA4 + 0xC) = 6;
        if ((*(u32 *)g_00669F60 & 2) == 0) {
            iVar8 = 0x1F0 - iVar2;
            func_00146270((u8 *)PS2_PTR(uVar4), iVar8, 0x122, 1, 0);
            iVar5 = 0x14D;
        }
        else {
            iVar8 = 0x1F0 - iVar2;
            func_00146270((u8 *)PS2_PTR(uVar4), iVar8, 0xB8, 1, 0);
            iVar5 = 0xD2;
        }
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
        iVar7 = iVar5 * 0x10 + -0xE00;
        uVar6 = (unsigned long long)(iVar8 * 0x10 + 0x7000);
        iVar5 = (iVar5 + 0x20) * 0x10 + -0xE00;
        *(unsigned long long *)(iVar1 + 0x1AE90) =
                  uVar6 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
        *(unsigned long long *)(iVar1 + 0x1AEA0) = (long long)(iVar5 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
        *(unsigned long long *)(iVar1 + 0x1AE88) = 0x4C80488;
        *(unsigned long long *)(iVar1 + 0x1AE98) = 0x68804F8;
        *(unsigned long long *)(iVar1 + 0x1AEE0) =
                  (long long)((0x1A8 - iVar2) * 0x10 + 0x7000) | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10 |
                  0xFFFE00000000;
        *(unsigned long long *)(iVar1 + 0x1AEF0) =
                  uVar6 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
        *(unsigned long long *)(iVar1 + 0x1AED8) = 0x4C80008;
        *(unsigned long long *)(iVar1 + 0x1AEE8) = 0x6880488;
    }
    else {
        func_001FA710();
    }
}

/* 0x0020BF50, 0x124 bytes. */
void func_0020BF50(int param_1, int param_2, u8 *param_3)
{
    int cVar4;
    u8 * iVar5;
    int iVar6;
    long long lVar7;
    u16 * puVar9;
    int uVar1;
    u32 uVar2;
    int uVar3;
    u32 uVar8;

    uVar1 = *(u16 *)(param_3 + 0x54);
    iVar5 = func_001FF140(uVar1);
    uVar2 = *(u32 *)(param_3 + 0x5C);
    uVar3 = func_001FF100(uVar1, 2);
    cVar4 = func_001FF100(uVar1, 1);
    if (cVar4 != 0) {
        puVar9 = (u16 *)(iVar5 + 0x30);
        uVar8 = 0;
        if (*(short *)(iVar5 + 4) != 0) {
            do {
                if ((uVar2 & 1 << (uVar8 & 0x1F)) != 0) {
                    lVar7 = func_001FF2C0(puVar9, uVar3);
                    if (lVar7 == 1) {
                        param_2 = func_0020BAC0(param_1, param_2, PS2_ADDR(param_3), PS2_ADDR(puVar9));
                    }
                    else {
                        iVar6 = func_00207D80(*puVar9);
                        param_2 = param_2 + iVar6 * 0x20;
                    }
                }
                uVar8 = uVar8 + 1;
                puVar9 = (u16 *)PS2_PTR(func_001FF230(puVar9));
            } while (uVar8 < *(u16 *)(iVar5 + 4));
        }
    }
}

/* 0x00240A60, 0xC8 bytes. */
void func_00240A60(u8 *param_1, int param_2)
{
    if ((long long)*(char *)(param_1 + 0x19C) << 0x3E < 0) {
        *(u8 *)(param_1 + 0x184) = 1;
    }
    else if ((param_2 & 0x1F00000) == 0) {
        *(u8 *)(param_1 + 0x184) = 0;
    }
    else if ((param_2 & 0x100000) == 0) {
        if ((param_2 & 0x400000) == 0) {
            if ((param_2 & 0x200000) == 0) {
                if ((param_2 & 0x800000) == 0) {
                    if ((param_2 & 0x1000000) != 0) {
                        *(u8 *)(param_1 + 0x184) = 6;
                    }
                }
                else {
                    *(u8 *)(param_1 + 0x184) = 5;
                }
            }
            else {
                *(u8 *)(param_1 + 0x184) = 4;
            }
        }
        else {
            *(u8 *)(param_1 + 0x184) = 3;
        }
    }
    else {
        *(u8 *)(param_1 + 0x184) = 2;
    }
}

/* 0x00240C00, 0xA0 bytes. */
int func_00240C00(u8 *param_1)
{
    long long lVar2;
    u32 uVar1;

    if ((long long)*(char *)(param_1 + 0x19C) << 0x38 < 0) {
        uVar1 = 0;
    }
    else if ((*(u32 *)(param_1 + 0x13C) & 4) == 0) {
        uVar1 = 0;
    }
    else if ((*(u32 *)g_00669DB8 == 4) || (lVar2 = func_002711F0(param_1), lVar2 != 0)) {
        if ((*(u32 *)PS2_PTR((*(int *)(param_1 + 0x210) + 0x18)) & 0x400000) == 0) {
            uVar1 = 0;
        }
        else {
            uVar1 = 1;
        }
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x00242C40, 0x5AC bytes. */
int func_00242C40(u8 *param_1, u32 *param_2, int param_3)
{
    int iVar3;
    u8 * iVar8;
    long long lVar7;
    short * psVar2;
    short * psVar4;
    int sVar1;
    int sVar6;
    u32 uVar5;

    iVar8 = param_1;
    psVar2 = *(short **)(iVar8 + 0x210);
    sVar6 = *psVar2;
    iVar3 = *(int *)(psVar2 + 10);
    lVar7 = func_001BEA30(*(u8 *)PS2_PTR((*(int *)(iVar8 + 0x110) + 0x1C)));
    *param_2 = 0;
    psVar4 = *(short **)PS2_PTR((*(int *)(iVar8 + 0x288) + 0x210));
    if (sVar6 != 0x60) {
        uVar5 = *(u32 *)(iVar8 + 0x13C);
        if (((uVar5 & 0x20) != 0) && ((*(u32 *)(psVar2 + 0xC) & 2) != 0)) {
            sVar6 = 0x60;
        }
        if ((param_3 == 0) && (((uVar5 & 0x1000000) == 0 || (*(u8 *)(iVar8 + 0x14E) < 2)))) {
            if ((uVar5 & 0x8000) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 0xFFFFFFFFFFFFFFFF);
            }
            if ((*(u32 *)(iVar8 + 0x13C) & 1) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 1);
            }
            if ((*(u32 *)(iVar8 + 0x13C) & 0x10000) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 0xFFFFFFFFFFFFFFFE);
            }
            if ((*(u32 *)(iVar8 + 0x13C) & 2) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 2);
            }
            if ((*(u32 *)(iVar8 + 0x13C) & 0x100000) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 0xFFFFFFFFFFFFFFE0);
            }
            if ((*(u32 *)(iVar8 + 0x13C) & 0x20) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 0x20);
            }
        }
        if (lVar7 == 0) {
            if ((long long)*(char *)(iVar8 + 0x19C) << 0x3E < 0) {
                if ((*(u32 *)(iVar8 + 0x13C) & 0x20000) != 0) {
                    sVar6 = func_00242900(param_1, sVar6, 0xFFFFFFFFFFFFFFFC);
                }
            }
            else {
                lVar7 = func_00240C00(param_1);
                if (lVar7 == 0) {
                    if ((((iVar3 == 0) && (lVar7 = func_00271300(param_1), lVar7 == 0)) &&
                            ((*(u32 *)(psVar2 + 0xC) & 4) != 0)) &&
                          (((*(u32 *)(psVar4 + 0xC) & 0x20) == 0 && ((*(u32 *)(iVar8 + 0x13C) & 0x20000) != 0))
                          )) {
                        sVar6 = 0x6E;
                    }
                }
                else {
                    *(u8 *)(iVar8 + 0x19C) = *(u8 *)(iVar8 + 0x19C) & 0xFD | 2;
                    *(u32 *)(iVar8 + 0x244) = 0;
                    *param_2 = 1;
                    func_001514C0(param_1);
                    sVar6 = func_00271440(param_1);
                }
            }
        }
        else {
            if ((*(u32 *)(iVar8 + 0x13C) & 0x20000) != 0) {
                sVar6 = func_00242900(param_1, sVar6, 0xFFFFFFFFFFFFFFFC);
            }
            lVar7 = func_00240C00(param_1);
            if (lVar7 != 0) {
                sVar6 = func_00242900(param_1, sVar6, 4);
                *(u8 *)(iVar8 + 0x182) = 0;
            }
        }
        if (sVar6 != **(short **)(iVar8 + 0x210)) {
            *(u32 *)(iVar8 + 0x228) = 0;
        }
        if (sVar6 == 0x6E) {
            lVar7 = func_00271300(param_1);
            if ((lVar7 == 0) && ((*(u32 *)(iVar8 + 0x13C) & 0x20000) != 0)) {
                return 0x6E;
            }
            sVar6 = **(short **)(iVar8 + 0x210);
        }
        if ((((sVar6 == **(short **)(iVar8 + 0x210)) && (iVar3 == 0)) &&
                ((*(u32 *)(psVar2 + 0xC) & 0x800) == 0)) && (**(short **)(iVar8 + 0x210) != 0x5D)) {
            sVar1 = *psVar4;
            if (((sVar1 == 0x9A) || (sVar1 == 0x99)) || (sVar1 == 0x98)) {
                sVar6 = 0x58;
            }
            else if (sVar1 == 0x97) {
                sVar6 = 0x5C;
            }
            else if (((sVar1 == 0x1B) || (sVar1 == 0x1A)) || ((sVar1 == 0x19 || (sVar1 == 0x18)))) {
                sVar6 = 0x57;
            }
            else if (sVar1 == 0x17) {
                sVar6 = 0x5F;
            }
            else if (sVar1 == 0x16) {
                sVar6 = 0x5E;
            }
            else if (sVar1 == 0x15) {
                sVar6 = 0x59;
            }
            else if ((((sVar1 == 0xD) || (sVar1 == 0xC)) || (sVar1 == 0xB)) || (sVar1 == 10)) {
                sVar6 = 0x5A;
            }
            else if ((sVar1 == 0xE) || (sVar1 == 9)) {
                sVar6 = 0x5C;
            }
            else if (sVar1 == 8) {
                sVar6 = 0x57;
            }
            else if ((((((sVar1 == 0x1C) || (sVar1 == 0x13)) ||
                                  ((sVar1 == 0x1D || (((sVar1 == 0x12 || (sVar1 == 0x11)) || (sVar1 == 0x10)))))) ||
                                ((sVar1 == 0xF || (sVar1 == 7)))) || (sVar1 == 6)) ||
                            (((sVar1 == 5 || (sVar1 == 4)) || (sVar1 == 3)))) {
                sVar6 = 0x58;
            }
            else {
                if ((((sVar1 != 0x14) && (sVar1 != 2)) && (sVar1 != 1)) && (sVar1 != 0)) {
                    return sVar6;
                }
                sVar6 = 0x57;
            }
        }
    }
    return sVar6;
}

/* 0x00244430, 0x58 bytes. */
void func_00244430(u8 *param_1)
{
    if ((u32)*(u16 *)(param_1 + 0x15E) % 0xD == 0) {
        if ((long long)*(char *)(param_1 + 0x19D) << 0x39 < 0) {
            func_00243F10(param_1, *(u8 *)(param_1 + 0x183));
        }
        else {
            func_00244260(param_1, *(u8 *)(param_1 + 0x183));
        }
    }
}

/* 0x00244AC0, 0x120 bytes. */
int func_00244AC0(u8 *param_1)
{
    int iVar1;
    u32 uVar2;
    u32 uVar3;

    if ((long long)*(char *)(param_1 + 0x19C) << 0x38 < 0) {
        uVar2 = 1;
    }
    else {
        iVar1 = *(int *)(param_1 + 0x118);
        if ((((iVar1 == 0x27) || (iVar1 == 0x28)) || (iVar1 == 0x2F)) || (iVar1 - 0x39U < 7)) {
            uVar2 = 1;
        }
        else {
            if (*(int *)(param_1 + 0x110) == 0) {
                uVar3 = 0x6A;
            }
            else {
                uVar3 = (u32)*(u8 *)PS2_PTR((*(int *)(param_1 + 0x110) + 0x1C));
            }
            if ((((uVar3 == 0x1C) || (uVar3 == 0x1D)) ||
                    ((uVar3 == 0x22 || ((uVar3 == 0x23 || (uVar3 == 0x2E)))))) ||
                  ((uVar3 == 0x2F ||
                    (((((uVar3 == 0x1E || (uVar3 == 0x1F)) || (uVar3 == 0x2C)) ||
                        ((uVar3 == 0x2D || (uVar3 == 0x33)))) || (uVar3 - 0x36 < 4)))))) {
                uVar2 = 1;
            }
            else {
                uVar2 = 0;
            }
        }
    }
    return uVar2;
}

/* 0x002CBE60, 0x58 bytes. */
void func_002CBE60(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar2 = (param_4 & 0xFF) << 0x10 | param_2 & 0xFF | (param_3 & 0xFF) << 8;
    uVar1 = (param_5 & 0xFF) << 0x18 | uVar2 | 0x3F80000000000000;
    uVar2 = (param_6 & 0xFF) << 0x18 | uVar2 | 0x3F80000000000000;
    *(unsigned long long *)(param_1 + 0x20) = uVar1;
    *(unsigned long long *)(param_1 + 0x38) = uVar1;
    *(unsigned long long *)(param_1 + 0x50) = uVar2;
    *(unsigned long long *)(param_1 + 0x68) = uVar2;
}

/* 0x002D6560, 0x27C bytes. */
void func_002D6560(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int iVar2;
    int iVar4;
    int iVar6;
    unsigned long long uVar3;
    unsigned long long uVar5;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F6D);
    param_2 = param_2 * 0x10;
    *(unsigned long long *)(param_1 + 0x18) = uVar3;
    iVar4 = *(int *)((g_00442420 + 0x4) + param_2);
    *(unsigned long long *)(param_1 + 0x20) = (long long)(int)(param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    iVar6 = *(int *)(g_00442420 + param_2);
    iVar1 = *(int *)((g_00442420 + 0xC) + param_2);
    *(long long *)(param_1 + 0x28) = (long long)(int)(iVar6 << 4 | 8) | (long long)(int)(iVar4 << 4 | 8) << 0x10;
    iVar2 = *(int *)((g_00442420 + 0x8) + param_2);
    *(long long *)(param_1 + 0x38) =
              (long long)(int)((iVar2 + iVar6) * 0x10 | 8) | (long long)(int)((iVar1 + iVar4) * 0x10 | 8) << 0x10;
    iVar4 = ((param_4 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    uVar5 = (long long)(0xFFFE - param_5) << 0x20;
    *(unsigned long long *)(param_1 + 0x30) =
              uVar5 | (long long)(param_3 * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar6 = ((iVar1 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar6 < 0) {
        iVar6 = iVar6 + 0x1FF;
    }
    *(unsigned long long *)(param_1 + 0x40) =
              uVar5 | (long long)((iVar2 + param_3) * 0x10 + 0x7000) |
                              (long long)((((iVar6 >> 9) + (iVar4 >> 9)) * 0x10 + -0xE00) / g_70000154 + 0x8000) <<
                              0x10;
}

/* 0x002D8370, 0x64 bytes. */
int func_002D8370(void)
{
    long long lVar1;

    lVar1 = func_0022DD60();
    if (lVar1 == -1) {
        func_0022DD70(0);
        func_0022DD50();
    }
    func_0022DCD0();
    lVar1 = func_0022DD60();
    return lVar1 != 2;
}

/* 0x002DB680, 0x7C bytes. */
void func_002DB680(void)
{
    u8 auStack_d0[208];
    u8 * iVar1;
    long long lVar2;

    iVar1 = (u8 *)(func_003C0070());
    lVar2 = func_002DAC30();
    if (lVar2 == 2) {
        g_0045D5FC = 4;
    }
    else if (lVar2 == 1) {
        g_0045D5FC = 4;
        func_002DB3C0((u32 *)(auStack_d0));
        func_003BFCF0((u32 *)(auStack_d0));
        *(u32 *)(iVar1 + 4) = 1;
    }
}

/* 0x002DB8A0, 0x5C bytes. */
void func_002DB8A0(void)
{
    long long lVar1;

    lVar1 = func_003BFDF0();
    if (lVar1 == 1) {
        *(u32 *)(g_00799A74) = func_003C0060();
        g_0045D5F4 = 2;
    }
    else if (lVar1 == 0) {
        g_0045D5F4 = 3;
    }
}

/* 0x002DB900, 0x8C bytes. */
void func_002DB900(void)
{
    u8 auStack_d0[208];
    u8 * iVar1;
    long long lVar2;

    iVar1 = (u8 *)(func_003C0070());
    lVar2 = func_002DAC30();
    if (lVar2 == 2) {
        g_0045D5F4 = 3;
    }
    else if ((lVar2 == 1) && (g_0045D5F4 = 3, g_0045D5F0 == 7)) {
        func_002DB3C0((u32 *)(auStack_d0));
        func_003BFCF0((u32 *)(auStack_d0));
        *(u32 *)(iVar1 + 4) = 1;
    }
}

/* 0x002E5F80, 0xE8 bytes. */
void func_002E5F80(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = PS2_ADDR(func_00105E10());
    func_00105EB0((u8 *)PS2_PTR(uVar1), param_5);
    uVar2 = (long long)(int)param_5 << 0x20;
    *(unsigned long long *)PS2_PTR(((int)uVar1 + 0x40)) =
              uVar2 | (long long)(param_1 * 0x10 + 0x7000) | (long long)(param_2 * 0x10 + 0x7900) << 0x10;
    *(unsigned long long *)PS2_PTR(((int)uVar1 + 0x48)) =
              uVar2 | (long long)((param_1 + param_3) * 0x10 + 0x7000) |
                              (long long)((param_2 + param_4) * 0x10 + 0x7900) << 0x10;
    func_00105F70((u8 *)PS2_PTR(uVar1));
}

/* 0x003253F0, 0x108 bytes. */
void func_003253F0(void)
{
    u8 auStack_70[108];
    u8 * iVar1;
    long long lVar3;
    u32 uStack_4;
    u32 uStack_74;
    u32 uStack_78;
    u32 uStack_7c;
    u32 uStack_80;
    u32 uVar2;
    unsigned long long uVar4;
    unsigned long long uVar5;

    func_002FC2C0();
    iVar1 = (u8 *)(func_002FC2C0());
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar1 + 0x6A8));
    lVar3 = func_003296F0();
    if (lVar3 == 0x13) {
        func_00325110((int *)(iVar1 + 8), (int *)(iVar1 + 0xC));
        lVar3 = func_002F8CB0(*(u32 *)(iVar1 + 0xC));
        if (lVar3 != 0) {
            uVar2 = func_002F8F20(*(u32 *)(iVar1 + 0xC));
            *(u32 *)(iVar1 + 0x10) = uVar2;
        }
        uVar4 = func_0030D150();
        *(int *)(iVar1 + 0x14) = (int)uVar4;
        func_0030AFF0(uVar4);
        uVar2 = func_003251B0(*(u32 *)(iVar1 + 8), *(u32 *)(iVar1 + 0xC),
                                                  *(u32 *)(iVar1 + 0x14), (int *)&uStack_4, auStack_70);
        func_00324060(*(u32 *)(iVar1 + 8), (int *)(auStack_70), uStack_4);
        uStack_80 = *(u32 *)(iVar1 + 8);
        uStack_7c = *(u32 *)(iVar1 + 0xC);
        uStack_78 = *(u32 *)(iVar1 + 0x14);
        uStack_74 = uVar2;
        uVar4 = func_00362570();
        uVar5 = func_0036B260();
        func_0030E390(9, uVar4, uVar5, 0, (int *)(&uStack_80), 4);
        func_00325360(2);
    }
    else {
        func_00325360(0xC);
    }
}

/* 0x00328820, 0x150 bytes. */
void func_00328820(void)
{
    int iVar1;
    int iVar2;
    int iVar4;
    long long lVar3;

    iVar4 = 0;
    do {
        lVar3 = func_00328640(iVar4);
        if ((0x59 < lVar3 && lVar3 < 99 || lVar3 == 0x65) || (lVar3 == 100)) {
            iVar1 = *(int *)(g_00447848 + (int)lVar3 * 4);
            iVar2 = iVar4;
            do {
                iVar2 = iVar2 + 1;
                if (4 < iVar2) goto LAB_00328948;
                lVar3 = func_00328640(iVar2);
            } while ((((lVar3 < 0x5A || 0x62 < lVar3) && lVar3 != 0x65) && (lVar3 != 100)) ||
                            (iVar1 <= *(int *)(g_00447848 + (int)lVar3 * 4)));
            func_00328600(*(u32 *)(g_004479E0 + *(int *)(g_00447848 + (int)lVar3 * 4) * 4),
                                      iVar4);
            func_00328600(*(u32 *)(g_004479E0 + iVar1 * 4), iVar2);
            iVar4 = iVar4 + -1;
        }
LAB_00328948:
        iVar4 = iVar4 + 1;
        if (4 < iVar4) {
            return;
        }
    } while( true );
}

/* 0x0032AE60, 0x19C bytes. */
int func_0032AE60(int param_1)
{
    u8 auStack_410[1040];
    u8 * iVar1;
    u8 * iVar2;
    long long lVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;

    lVar3 = func_0032EAA0();
    iVar1 = func_0032C050();
    iVar2 = func_0032C9D0();
    *(u32 *)(iVar2 + 0xC2C4) = 2;
    *(u32 *)(iVar1 + 0x4EC8) = 2;
    *(u32 *)(iVar1 + 0x4ECC) = 2;
    func_00369880(0);
    func_0023AA10(0);
    if (lVar3 == 4) {
        *(u32 *)(iVar1 + 0x4ECC) = 2;
        func_00329D80(1);
    }
    else if (lVar3 == 3) {
        *(u32 *)(iVar1 + 0x4ECC) = 2;
        func_00329D80(1);
    }
    else {
        if (lVar3 == 2) {
            uVar4 = PS2_ADDR(func_00390760(0x5E));
        }
        else if (lVar3 == 1) {
            uVar4 = PS2_ADDR(func_00390760(0x5D));
        }
        else {
            if (lVar3 != 0) goto LAB_0032afe8;
            uVar4 = PS2_ADDR(func_00390760(0x5C));
        }
        uVar5 = func_0032E8E0(0);
        if (uVar5 < 0x19F) {
            uVar6 = func_0032E8E0(0);
            uVar6 = PS2_ADDR(func_002F2890(uVar6));
            func_001204B0(auStack_410, PS2_PTR(uVar4), uVar6);
            func_001AE9F0(1, (char *)(auStack_410), 1);
            g_0045D6DC = 2;
            uVar4 = func_0032E8E0(0);
            uVar4 = func_002F4080(uVar4);
            func_0032A750(uVar4);
            g_0045D6E0 = 0x3C;
        }
    }
LAB_0032afe8:
    return param_1 + 0x20;
}

/* 0x00396530, 0x14C bytes. */
void func_00396530(u8 *param_1)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    long long lVar1;

    iVar2 = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2C) * 5 + *(int *)(param_1 + 0x24) * 0x32;
    iVar5 = iVar2;
    do {
        iVar5 = iVar5 + 1;
        iVar4 = iVar2;
        if (199 < iVar5) goto LAB_003965c0;
        lVar1 = func_003A17A0(iVar5);
    } while (lVar1 == 0);
    iVar4 = iVar5;
LAB_003965c0:
    iVar5 = iVar4;
    if ((iVar4 == iVar2) && (iVar3 = 0, 0 < iVar2)) {
        do {
            lVar1 = func_003A17A0(iVar3);
            iVar5 = iVar3;
            if (lVar1 != 0) break;
            iVar3 = iVar3 + 1;
            iVar5 = iVar4;
        } while (iVar3 < iVar2);
    }
    *(int *)(param_1 + 0x24) = iVar5 / 0x32;
    *(int *)(param_1 + 0x28) = iVar5 % 5;
    *(int *)(param_1 + 0x2C) = (iVar5 % 0x32) / 5;
}

/* 0x00396680, 0x14C bytes. */
void func_00396680(u8 *param_1)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    long long lVar1;

    iVar2 = *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x2C) * 5 + *(int *)(param_1 + 0x24) * 0x32;
    iVar4 = iVar2;
    do {
        iVar4 = iVar4 + -1;
        iVar3 = iVar2;
        if (iVar4 < 0) goto LAB_00396708;
        lVar1 = func_003A17A0(iVar4);
    } while (lVar1 == 0);
    iVar3 = iVar4;
LAB_00396708:
    iVar4 = iVar3;
    if ((iVar3 == iVar2) && (iVar5 = 199, iVar2 < 199)) {
        do {
            lVar1 = func_003A17A0(iVar5);
            iVar4 = iVar5;
            if (lVar1 != 0) break;
            iVar5 = iVar5 + -1;
            iVar4 = iVar3;
        } while (iVar2 < iVar5);
    }
    *(int *)(param_1 + 0x24) = iVar4 / 0x32;
    *(int *)(param_1 + 0x28) = iVar4 % 5;
    *(int *)(param_1 + 0x2C) = (iVar4 % 0x32) / 5;
}

/* 0x0039AC20, 0x130 bytes. */
void func_0039AC20(void)
{
    u8 * iVar3;
    int iVar4;
    u8 * iVar5;
    int iVar6;
    int iVar7;
    long long lVar1;
    unsigned long long uVar2;

    iVar7 = 0;
    *(u32 *)(g_007BA8C8) = 0;
    lVar1 = func_0030AB90();
    if (0 < lVar1) {
        iVar5 = g_007BA8B0;
        do {
            iVar6 = 0;
            uVar2 = func_0030AFF0(iVar7);
            lVar1 = func_002FB2A0(uVar2);
            if (lVar1 != 0) {
                iVar4 = 0;
                iVar3 = iVar5;
                do {
                    if (*(u16 *)(iVar3 + 0x78) < 0x19F) {
                        iVar6 = iVar6 + 1;
                        *(u32 *)(g_007BA8C8) = *(u32 *)(g_007BA8C8) + 1;
                    }
                    iVar4 = iVar4 + 1;
                    iVar3 = iVar3 + 2;
                } while (iVar4 < 3);
                iVar4 = 0;
                iVar3 = iVar5;
                do {
                    if (*(u16 *)(iVar3 + 0x10E) < 0x19F) {
                        iVar6 = iVar6 + 1;
                        *(u32 *)(g_007BA8C8) = *(u32 *)(g_007BA8C8) + 1;
                    }
                    iVar4 = iVar4 + 1;
                    iVar3 = iVar3 + 2;
                } while (iVar4 < 3);
                func_003A7BF0(iVar7, iVar6);
            }
            iVar5 = iVar5 + 6;
            iVar7 = iVar7 + 1;
            iVar6 = func_0030AB90();
        } while (iVar7 < iVar6);
    }
}

/* 0x0039F040, 0xA4 bytes. */
int func_0039F040(void)
{
    int bVar1;
    u8 * iVar2;
    long long lVar4;
    u32 uVar3;

    iVar2 = (u8 *)(func_002FC2C0());
    iVar2 = (u8 *)PS2_PTR(*(int *)(iVar2 + 0x694));
    if ((long long)(*(char *)g_007BAC0D) << 0x3F < 0) {
        lVar4 = func_00388DA0();
        if (lVar4 == 1) {
            uVar3 = func_00389090();
            *(u32 *)(iVar2 + 0x214) = 0;
            *(u32 *)(iVar2 + 0x210) = uVar3;
            *(u32 *)(iVar2 + 0x218) = uVar3;
            *(u32 *)(iVar2 + 0x21C) = 0xFFFFFFFF;
            func_0039EF80(1);
            bVar1 = false;
        }
        else {
            bVar1 = lVar4 == 0;
            if (bVar1) {
                func_0039EF80(9);
            }
        }
    }
    else {
        bVar1 = false;
    }
    return bVar1;
}

/* 0x003A48E0, 0x90 bytes. */
void func_003A48E0(void)
{
    int iVar2;
    long long lVar1;

    iVar2 = 0;
    do {
        lVar1 = func_003A0A30(iVar2);
        if (lVar1 == 0) {
            return;
        }
        iVar2 = iVar2 + 1;
    } while (iVar2 < 0x1C);
    iVar2 = 0;
    do {
        func_003A1B60(iVar2, 1);
        iVar2 = iVar2 + 1;
    } while (iVar2 < 0xE6);
    iVar2 = 0x38;
    do {
        func_003A3EC0(iVar2, 1);
        iVar2 = iVar2 + 1;
    } while (iVar2 < 0x8C);
}

/* 0x003AE8E0, 0x104 bytes. */
void func_003AE8E0(int param_1)
{
    long long lVar2;
    u32 uStack_10;
    u32 uStack_2c;
    u32 uStack_30;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;
    u32 uVar1;

    if (param_1 == 2) {
        *(u32 *)(g_007BAE74 + 0x4) = 4;
        *(u32 *)(g_007BAE74 + 0x18) = 0;
        uVar1 = *(u32 *)PS2_PTR((*(u32 *)(g_007BAE74 + 0x8) * 4 + 0x7BAE94));
        *(u32 *)(g_007BAE74 + 0x18) = func_002F7160(uVar1);
        lVar2 = func_003AE840(uVar1);
        if (lVar2 != 0) {
            *(u32 *)(g_007BAE74 + 0x18) = 0;
        }
        uStack_10 = 1;
        uStack_c = 1;
        uStack_8 = 1;
        uStack_4 = 1;
        lVar2 = func_003AE790();
        if (lVar2 == 0) {
            uStack_10 = 0;
        }
        lVar2 = func_003AE820();
        if (lVar2 == 0) {
            uStack_8 = 0;
        }
        func_003882C0((int *)(&uStack_10));
        uStack_30 = 0xF0;
        uStack_2c = 0x4E;
        func_003DB220(0xD, &uStack_30);
        func_003DB460(0xD, 2);
        func_003F1070(0xC);
    }
    *(u32 *)(g_007BAE74) = param_1;
}

/* 0x003AEAE0, 0x9C bytes. */
int func_003AEAE0(void)
{
    u8 auStack_60[96];
    u32 uStack_78;
    u32 uStack_7c;
    u32 uStack_80;
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = PS2_ADDR(func_00390760(0xBC));
    uVar2 = PS2_ADDR(func_002F2890(*(u32 *)PS2_PTR((*(u32 *)g_007BAE7C * 4 + 0x7BAE94))));
    func_001204B0(auStack_60, PS2_PTR(uVar1), uVar2);
    func_00374EE0(PS2_ADDR(auStack_60));
    uStack_80 = 0x80;
    uStack_7c = 0x40;
    uStack_78 = 0x100;
    func_003DB220(0xD, &uStack_80);
    func_003DB460(0xD, 1);
    func_003AE8E0(1);
    return 2;
}

/* 0x003AF5B0, 0xB8 bytes. */
int func_003AF5B0(void)
{
    long long lVar1;

    lVar1 = func_00375B90();
    if (*(u32 *)(g_007BAE74 + 0x4) == 2) {
        if (lVar1 == 2) {
            func_003AE8E0(4);
        }
        else if (lVar1 == 3) {
            *(u32 *)(g_007BAE74) = 2;
        }
    }
    else if (*(u32 *)(g_007BAE74 + 0x4) == 0) {
        if (lVar1 == 1) {
            *(u32 *)(g_007BAE74) = 2;
        }
        else if (lVar1 == 2) {
            func_003AE8E0(4);
        }
        else if (lVar1 == 3) {
            *(u32 *)(g_007BAE74) = 2;
        }
    }
    return 2;
}

/* 0x003EC130, 0xE8 bytes. */
void func_003EC130(int param_1)
{
    u32 auStack_20[8];
    int iVar1;
    int iVar5;
    int iVar6;
    u32 * puVar2;
    u32 * puVar4;
    unsigned long long uVar3;

    uVar3 = func_002F5CC0(param_1);
    iVar6 = 0;
    iVar1 = func_002F7D90(0, 0x2F7F80, uVar3, 0, 0, 0);
    puVar2 = (u32 *)func_002F7B10();
    iVar5 = 0;
    if (0 < iVar1) {
        puVar4 = auStack_20;
        do {
            if ((*puVar2 < 0x19F) && (param_1 != *puVar2)) {
                *puVar4 = *puVar2;
                iVar6 = iVar6 + 1;
                puVar4 = puVar4 + 1;
            }
            iVar5 = iVar5 + 1;
            puVar2 = puVar2 + 1;
        } while (iVar5 < iVar1);
    }
    func_0030A870(1, param_1, uVar3, auStack_20, iVar6, 1);
    func_002F4080(param_1);
}
