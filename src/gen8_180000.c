/*
 * gen8_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_007B9E74[0x18];
extern u8 g_007B9E84[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_00206080();
int func_00330650();

#define true 1
#define false 0

extern u8 g_0043C120[0x400];
extern u8 g_0043C55C[0x4];
extern u8 g_0043C7DC[0x4];
extern u8 g_00440DA0[0xE4];
extern u8 g_00440FB0[0x1F4];
extern u8 g_004412F0[0x4];
extern u8 g_004415A0[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_00500764[0x4];
extern u8 g_00500765[0x4];
extern u8 g_005BA6A0[0x4];
extern u8 g_00669DB8[0x4];
extern u8 g_00669F60[0x3C];
extern u8 g_00669F70[0x30];
extern u8 g_00669F9C[0x4];
extern u8 g_0068F0F0[0x8];
extern u8 g_00693970[0x10];
extern u8 g_006939DC[0x4];
extern u8 g_006939F0[0x4];
extern u8 g_006A3A40[0x4];
extern u8 g_006A3A44[0x4];
extern u8 g_006A3AA8[0x4];
extern u8 g_006A3AAB[0x4];
extern u8 g_006A3AAD[0x4];
extern u8 g_006A3AB0[0x4];
extern u8 g_006A3AB2[0x4];
extern u8 g_006A3AB4[0x4];
extern u8 g_006A3AB6[0x4];
extern u8 g_006A3AB8[0x4];
extern u8 g_006A3ADC[0x4];
extern u8 g_006A3ADD[0x4];
extern u8 g_006A3ADE[0x4];
extern u8 g_006A3ADF[0x4];
extern u8 g_006A3AE0[0x4];
extern u8 g_006A3AE4[0x4];
extern u8 g_006A3AE8[0x4];
extern u8 g_006A3AEC[0x4];
extern u8 g_006AA574[0x4];
extern u8 g_006AA57C[0x4];
extern u8 g_00730DE0[0x4];
extern u8 g_00730DFC[0x4];
extern u8 g_00730E04[0x4];
extern u8 g_00730E14[0x4];
extern u8 g_00732220[0x10];
extern u8 g_007325FC[0x4];
extern u8 g_00732604[0x4];
extern u8 g_00732608[0x4];
extern u8 g_0073260D[0x4];
extern u8 g_0073260E[0x4];
extern u8 g_0073DCA1[0x4];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_0076F650[0x4];
extern u8 g_0076F6FA[0x4];
extern u8 g_00772674[0x8];
extern u8 g_0077A72C[0x4];
extern u8 g_0077A730[0x4];
extern u8 g_0077A734[0x4];
extern u8 g_0077A738[0x4];
extern u8 g_0077BEF4[0x4];
extern u8 g_0077CFA0[0x4];
extern u8 g_0077CFA4[0x4];
extern u8 g_0078E024[0x4];
extern u8 g_0078E028[0x4];
extern u8 g_0078E02C[0x4];
extern u8 g_0078E030[0x4];
extern u8 g_0078E034[0x4];
extern u8 g_0078E03C[0x4];
extern u8 g_007B9620[0x10];
extern u8 g_007B9624[0x4];
extern u8 g_007B9E70[0xC8];
extern u8 g_007BA83D[0x1];
extern u8 g_007BAE70[0x24];
extern u8 g_007BAEAC[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045CFEC;   /* (small data) */
extern int g_0045D2C0;   /* (small data) */
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D574;   /* (small data) */
extern int g_0045D578;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern int g_700000C0;   /* (small data) */
extern int g_700000C4;   /* (small data) */
extern int g_700000C8;   /* (small data) */
extern int g_700000CC;   /* (small data) */
extern int g_70000154;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */
extern int g_70000164;   /* (small data) */
extern int g_700001D0;   /* (small data) */
extern int g_700001D4;   /* (small data) */
extern int g_70000D60;   /* (small data) */

int func_001204B0();
void *func_0014F810();
int func_0017EAE0();
int func_001806C0();
int func_001809C0();
int func_001EE570();
int func_001FF100();
void *func_001FF140();
void *func_001FF230();
int func_00203C70();
int func_002040C0();
int func_00204300();
int func_00204B60();
int func_0020AFF0();
int func_0020B2B0();
int func_0020B410();
void *func_0021A630();
int func_00271A10();
int func_00279240();
int func_002796A0();
int func_002A6D20();
int func_002AE5B0();
int func_002AE680();
int func_002AE750();
int func_002AE8D0();
int func_002BB490();
int func_002C7310();
void *func_0030D7D0();
int func_0032F420();
void *func_0038C6E0();
int func_003914C0();
int func_00391FA0();
void func_001EDE10(u8 *param_1, int param_2);
void func_001EDFB0(u8 *param_1, int param_2);
void func_002C24B0(int param_1, u8 *param_2);

/* 0x00180BF0, 0x11C bytes. */
void func_00180BF0(void)
{
    int bVar2;
    u8 * iVar1;
    u32 uStack_4;
    unsigned long long uVar3;
    u32 uVar4;
    u32 uVar5;

    uVar4 = *(u32 *)g_00669F60 & 2;
    iVar1 = func_0035DCD0(0);
    if (((*(u32 *)(iVar1 + 0x80) & 0x4000000) == 0) &&
          ((uVar4 == 0 || (iVar1 = func_0035DCD0(1), (*(u32 *)(iVar1 + 0x80) & 0x4000000) == 0)))) {
        uVar3 = 0;
    }
    else {
        uVar3 = 1;
    }
    uStack_4 = 0;
    iVar1 = g_00693970;
    uVar5 = 0;
    do {
        bVar2 = false;
        if (((*(u32 *)(iVar1 + 0x80) & 1) != 0) && ((*(u32 *)(iVar1 + 0x80) & 0x8C40002) == 0)) {
            bVar2 = true;
        }
        if (bVar2) {
            func_001809C0(iVar1);
            func_001806C0(iVar1);
            if ((*(u32 *)(iVar1 + 0x84) & 0x8000) == 0) {
                func_0017EAE0(iVar1, &uStack_4, uVar4, uVar3);
            }
        }
        uVar5 = uVar5 + 1;
        iVar1 = iVar1 + 0x88;
    } while (uVar5 < 0x1AD);
}

/* 0x00184410, 0x13C bytes. */
void func_00184410(void)
{
    int bVar1;
    u8 * iVar2;
    int iVar4;
    int iVar6;
    unsigned long long uVar3;
    u32 uVar5;

    uVar5 = *(u32 *)g_00669F60 & 2;
    if (uVar5 == 0) {
        iVar4 = 1;
    }
    else {
        iVar4 = 2;
    }
    func_00279240();
    iVar6 = 0;
    if (iVar4 != 0) {
        do {
            iVar2 = func_0035DCD0(iVar6);
            func_00279380(*(u8 *)(*(int *)(iVar2 + 8) + 6), iVar6);
            bVar1 = *(u8 *)(*(u32 *)g_005BA6A0 + (iVar6 + 0x24E) * 0x2C + 9);
            func_002795A0(bVar1);
            if ((0x84 < bVar1) && (bVar1 < 0x8D)) {
                uVar3 = func_0016CBD0(bVar1);
                func_002795A0(uVar3);
            }
            iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
    }
    func_002796A0(uVar5);
    iVar6 = 0;
    if (iVar4 != 0) {
        do {
            uVar3 = PS2_ADDR(func_0035DCD0(iVar6));
            func_001BB4F0((u8 *)PS2_PTR(uVar3), (u8 *)PS2_PTR(iVar6 * 0xC0 + 0x6A3A30));
            iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
    }
}

/* 0x00184550, 0x428 bytes. */
void func_00184550(void)
{
    int bVar1;
    int bVar2;
    int iVar12;
    int iVar13;
    int iVar15;
    u8 * iVar3;
    long long lVar10;
    long long lVar11;
    long long lVar4;
    long long lVar8;
    int sVar7;
    int sVar9;
    u32 uVar14;
    unsigned long long uVar5;
    int uVar6;

    uVar14 = *(u32 *)g_00669F60 & 2;
    if (uVar14 == 0) {
        iVar13 = 1;
    }
    else {
        iVar13 = 2;
    }
    if ((*(u32 *)g_00669F60 & 4) == 0) {
        if ((*(u32 *)g_00669F60 & 8) == 0) {
            bVar1 = true;
        }
        else {
            bVar1 = false;
        }
    }
    else {
        bVar1 = *(u32 *)(g_00669F60 + 0x38) % 5 == 0;
    }
    lVar4 = func_0036D310();
    iVar15 = 0;
    if (iVar13 != 0) {
        do {
            iVar12 = *(u32 *)g_005BA6A0 + (iVar15 + 0x24E) * 0x2C;
            iVar3 = func_0035DCD0(iVar15);
            lVar11 = (long long)*(short *)((u8 *)PS2_PTR(iVar12) + 0xC);
            if (lVar11 < 0x3E9) {
                lVar10 = lVar11;
            }
            else {
                lVar10 = 1000;
            }
            if (lVar10 < 1) {
                uVar6 = 0;
                lVar10 = 0;
            }
            else {
                if (lVar11 < 0x3E9) {
                    lVar10 = lVar11;
                }
                else {
                    lVar10 = 1000;
                }
                uVar6 = (u16)lVar10;
                lVar10 = lVar10 << 0x30;
            }
            lVar10 = lVar10 >> 0x30;
            *(u16 *)(iVar3 + 0x4C) = uVar6;
            if (lVar10 < lVar11) {
                lVar8 = lVar10;
            }
            else {
                lVar8 = lVar11;
            }
            if ((short)lVar8 < 1) {
                uVar6 = 0;
            }
            else {
                lVar8 = lVar11;
                if (lVar10 < lVar11) {
                    lVar8 = lVar10;
                }
                uVar6 = (u16)lVar8;
            }
            *(u16 *)(iVar3 + 0x4E) = uVar6;
            if (lVar11 < 0x2711) {
                lVar10 = lVar11;
            }
            else {
                lVar10 = 10000;
            }
            if (lVar10 < 1) {
                uVar6 = 0;
                lVar10 = 0;
            }
            else {
                if (lVar11 < 0x2711) {
                    lVar10 = lVar11;
                }
                else {
                    lVar10 = 10000;
                }
                uVar6 = (u16)lVar10;
                lVar10 = lVar10 << 0x30;
            }
            lVar10 = lVar10 >> 0x30;
            *(u16 *)(iVar3 + 0x50) = uVar6;
            if (lVar10 < lVar11) {
                lVar8 = lVar10;
            }
            else {
                lVar8 = lVar11;
            }
            if ((short)lVar8 < 1) {
                uVar6 = 0;
            }
            else {
                if (lVar10 < lVar11) {
                    lVar11 = lVar10;
                }
                uVar6 = (u16)lVar11;
            }
            *(u16 *)(iVar3 + 0x52) = uVar6;
            sVar9 = *(short *)((u8 *)PS2_PTR(iVar12) + 0x10);
            sVar7 = sVar9;
            if (1000 < sVar9) {
                sVar7 = 1000;
            }
            if (sVar7 < 2) {
                *(u16 *)(iVar3 + 0x54) = 1;
            }
            else {
                if (1000 < sVar9) {
                    sVar9 = 1000;
                }
                *(short *)(iVar3 + 0x54) = sVar9;
            }
            sVar9 = *(short *)((u8 *)PS2_PTR(iVar12) + 0x12);
            sVar7 = sVar9;
            if (1000 < sVar9) {
                sVar7 = 1000;
            }
            if (sVar7 < 2) {
                *(u16 *)(iVar3 + 0x56) = 1;
            }
            else {
                if (1000 < sVar9) {
                    sVar9 = 1000;
                }
                *(short *)(iVar3 + 0x56) = sVar9;
            }
            if ((lVar4 == 0) && (bVar2 = func_003DD680(iVar15), bVar2 < 4)) {
                *(u32 *)((u8 *)PS2_PTR(iVar12) + 0x28) = *(u32 *)((u8 *)PS2_PTR(iVar12) + 0x28) | 0x80000000;
                *(u8 *)((u8 *)PS2_PTR(iVar12) + 8) = bVar2 + 0x10;
                *(u32 *)((u8 *)PS2_PTR(iVar12) + 0x28) = *(u32 *)((u8 *)PS2_PTR(iVar12) + 0x28) & 0x7FFFFFFF;
                *(u32 *)(iVar3 + 0x80) = *(u32 *)(iVar3 + 0x80) | 0x80000;
            }
            iVar15 = iVar15 + 1;
        } while (iVar15 < iVar13);
    }
    if (bVar1) {
        func_00279240();
        iVar15 = 0;
        if (iVar13 != 0) {
            do {
                iVar3 = func_0035DCD0(iVar15);
                func_00279380(*(u8 *)(*(int *)(iVar3 + 8) + 6), iVar15);
                bVar2 = *(u8 *)(*(u32 *)g_005BA6A0 + (iVar15 + 0x24E) * 0x2C + 9);
                func_002795A0(bVar2);
                if ((0x84 < bVar2) && (bVar2 < 0x8D)) {
                    uVar5 = func_0016CBD0(bVar2);
                    func_002795A0(uVar5);
                }
                iVar15 = iVar15 + 1;
            } while (iVar15 < iVar13);
        }
        func_002796A0(uVar14);
    }
    iVar15 = 0;
    if (iVar13 != 0) {
        do {
            uVar5 = PS2_ADDR(func_0035DCD0(iVar15));
            func_001BB4F0((u8 *)PS2_PTR(uVar5), (u8 *)PS2_PTR(iVar15 * 0xC0 + 0x6A3A30));
            iVar15 = iVar15 + 1;
        } while (iVar15 < iVar13);
    }
}

/* 0x001D1360, 0x148 bytes. */
void func_001D1360(u8 *param_1, u8 *param_2)
{
    int bVar1;
    int bVar3;
    int iVar2;
    int iVar4;

    iVar4 = *(short *)(param_1 + 0x178) * 0xC0;
    iVar2 = *(int *)(g_006A3A40 + iVar4);
    if (((iVar2 != 0) && (bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x7C), (*(u32 *)(g_006A3AE8 + iVar4) & 0x180) == 0)
            ) && (bVar1 != 0)) {
        bVar3 = func_002F41E0(*(u32 *)((u32)*(u8 *)(param_2 + 0x14E) * 0x48 + 0x669DE8));
        g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
        if (((g_7000015C >> 0x10) % 100 <
                  (u32)(int)(((float)bVar1 / 30.0 + (float)bVar3 / 49.0) / 3.0)) &&
              ((*(u32 *)(g_006A3AE8 + iVar4) & 0x180) != 0)) {
            func_001EE570(iVar2);
        }
    }
}

/* 0x001D1A40, 0x110 bytes. */
void func_001D1A40(u8 *param_1)
{
    int iVar1;
    int uVar2;
    u32 uVar3;

    if (1 < *(u8 *)(param_1 + 0x14E)) {
        iVar1 = *(short *)(param_1 + 0x178) * 0xC0;
        *(u32 *)(g_006A3AEC + iVar1) = *(u32 *)(g_006A3AEC + iVar1) & 0xFFF8003F;
        *(u8 *)(g_006A3AAD + iVar1) = 2;
        *(u16 *)(g_006A3AB8 + iVar1) = *(u16 *)(g_006A3AB6 + iVar1);
        func_00204B60(iVar1 + 0x6A3A30, 0x20004);
        uVar3 = *(u32 *)(g_006A3AEC + iVar1) & 0xFFF8003F;
        *(u32 *)(g_006A3AEC + iVar1) = uVar3;
        *(u32 *)(g_006A3AEC + iVar1) = uVar3 | 0x100;
        if (*(u16 *)(g_006A3AB8 + iVar1) == 0) {
            *(u16 *)(g_006A3AA8 + iVar1) = 0;
        }
        else {
            uVar3 = ((u32)*(u16 *)(g_006A3AB8 + iVar1) * 0x32) / 0x3C;
            uVar2 = (u16)uVar3;
            if ((uVar3 & 0xFFFF) == 0) {
                uVar2 = 1;
            }
            *(u16 *)(g_006A3AA8 + iVar1) = uVar2;
        }
    }
}

/* 0x001DF470, 0x164 bytes. */
void func_001DF470(int param_1, int param_2, int param_3)
{
    int bVar1;
    int iVar3;
    int * piVar2;
    u32 * puVar6;
    u32 uVar4;
    u32 uVar5;

    uVar5 = param_1 & 0xFFFF;
    iVar3 = g_0045D3E0 * 0x38;
    piVar2 = (int *)(iVar3 + 0x730DE0);
    if ((int)uVar5 < *(int *)(g_00730E14 + iVar3)) {
        bVar1 = *(int *)(*piVar2 + uVar5 * 4) != 0;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        uVar4 = *(u32 *)(*(int *)(g_00730E04 + iVar3) + (param_1 & 0xFFFF) * 4) & 2;
    }
    else {
        uVar4 = 0;
    }
    if (uVar4 == 0) {
        return;
    }
    if ((int)uVar5 < *(int *)(g_00730E14 + iVar3)) {
        bVar1 = *(int *)(*piVar2 + (param_1 & 0xFFFF) * 4) != 0;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        puVar6 = (u32 *)(piVar2[*(u8 *)(*(int *)(g_00730DFC + iVar3) + (param_1 & 0xFFFF)) + 10] +
                                          (param_1 & 0xFFFF) * 8);
        if ((param_3 & 0xFFFF) < *puVar6) {
            bVar1 = *(int *)(puVar6[1] + (param_3 & 0xFFFF) * 0x10) != 0;
            goto LAB_001df574;
        }
    }
    bVar1 = false;
LAB_001df574:
    if ((bVar1) &&
          (iVar3 = *(int *)(piVar2[*(u8 *)(*(int *)(g_00730DFC + iVar3) + (param_1 & 0xFFFF)) + 10] +
                                              (param_1 & 0xFFFF) * 8 + 4) + (param_3 & 0xFFFF) * 0x10,
          *(char *)((u8 *)PS2_PTR(iVar3) + 0xC) != 0)) {
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 8) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 4) = param_2;
    }
}

/* 0x001E1860, 0xA0 bytes. */
int func_001E1860(int param_1)
{
    int bVar1;
    int iVar4;
    u32 uVar2;
    u32 uVar3;

    iVar4 = g_0045D3E0 * 0x38;
    if ((int)(param_1 & 0xFFFF) < *(int *)(g_00730E14 + iVar4)) {
        bVar1 = *(int *)(*(int *)(g_00730DE0 + iVar4) + (param_1 & 0xFFFF) * 4) != 0;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        uVar2 = *(u32 *)(*(int *)(g_00730E04 + iVar4) + (param_1 & 0xFFFF) * 4) & 2;
    }
    else {
        uVar2 = 0;
    }
    if (uVar2 == 0) {
        uVar3 = 0;
    }
    else {
        uVar3 = *(u32 *)(*(int *)(g_00730DE0 + iVar4) + (param_1 & 0xFFFF) * 4);
    }
    return uVar3;
}

/* 0x002015A0, 0x1DC bytes. */
void func_002015A0(u8 *param_1)
{
    int iVar5;
    int iVar6;
    long long lVar7;
    int sVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    unsigned long long uVar8;
    u32 uVar9;

    if (*(short *)(param_1 + 0x78) == 0) {
        iVar6 = (u32)((*(u32 *)(param_1 + 0xB8) & 0x20) == 0) * 0xC0;
        if ((*(u32 *)(g_006A3AE8 + iVar6) & 2) == 0) {
            iVar5 = (int)*(short *)(g_006A3AB0 + iVar6);
            if (*(short *)(g_006A3AB0 + iVar6) < 0) {
                iVar5 = iVar5 + 3;
            }
            lVar7 = (long long)(iVar5 >> 2);
            if (lVar7 < 0x32) {
                sVar1 = *(short *)(g_006A3AB2 + iVar6);
            }
            else {
                lVar7 = 0x32;
                sVar1 = *(short *)(g_006A3AB2 + iVar6);
            }
            if (sVar1 < lVar7) {
                uVar8 = 0;
            }
            else {
                g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                uVar9 = g_7000015C >> 0x10 & 3;
                if (uVar9 == 3) {
                    uVar8 = 0xC;
                }
                else if (uVar9 == 2) {
                    uVar8 = 10;
                }
                else if (uVar9 == 1) {
                    uVar8 = 9;
                }
                else {
                    if (uVar9 != 0) {
                        return;
                    }
                    uVar8 = 8;
                }
            }
            func_0024D380((u8 *)PS2_PTR(uVar8), (u8 *)PS2_PTR(*(u32 *)(g_006A3A44 + iVar6)));
            *(u32 *)(param_1 + 0xBC) = *(u32 *)(param_1 + 0xBC) & 0xFFFBFFFF;
            iVar6 = *(int *)(param_1 + 0x14);
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x13C) = 0;
            uVar4 = g_700000CC;
            uVar3 = g_700000C8;
            uVar2 = g_700000C4;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D0) = g_700000C0;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D4) = uVar2;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D8) = uVar3;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1DC) = uVar4;
            *(u32 *)(param_1 + 0xBC) = *(u32 *)(param_1 + 0xBC) & 0xFFF8003F;
            *(u8 *)(param_1 + 0x7D) = 0;
        }
        else {
            *(u32 *)(param_1 + 0xBC) = *(u32 *)(param_1 + 0xBC) & 0xFFFBFFFF;
            iVar6 = *(int *)(param_1 + 0x14);
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x13C) = 0;
            uVar4 = g_700000CC;
            uVar3 = g_700000C8;
            uVar2 = g_700000C4;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D0) = g_700000C0;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D4) = uVar2;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1D8) = uVar3;
            *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x1DC) = uVar4;
            *(u32 *)(param_1 + 0xBC) = *(u32 *)(param_1 + 0xBC) & 0xFFF8003F;
            *(u8 *)(param_1 + 0x7D) = 0;
        }
    }
}

/* 0x002032F0, 0x1F4 bytes. */
void func_002032F0(u8 *param_1)
{
    int bVar1;
    int iVar3;
    int iVar4;
    int iVar6;
    u8 * iVar7;
    int iVar8;
    int uVar2;
    u32 uVar5;

    iVar7 = param_1;
    iVar8 = *(int *)(iVar7 + 0x14);
    if ((long long)*(char *)((u8 *)PS2_PTR(iVar8) + 0x27C) << 0x3D < 0) {
        if (*(short *)(iVar7 + 0x78) == 0) {
            iVar6 = *(int *)((u8 *)PS2_PTR(iVar8) + 0x280);
            if (iVar6 == 0) {
                iVar6 = *(int *)((u8 *)PS2_PTR(iVar8) + 0x284);
            }
            if (iVar6 == 0) {
                *(u32 *)(iVar7 + 0xBC) = *(u32 *)(iVar7 + 0xBC) & 0xFFF8003F;
                *(u8 *)(iVar7 + 0x7D) = 0;
            }
            else {
                bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar8) + 0x159);
                if ((bVar1 == 0) && (*(u8 *)((u8 *)PS2_PTR(iVar6) + 0x159) == 0)) {
                    uVar5 = 0x32;
                }
                else {
                    uVar5 = (((u32)bVar1 * 4 + (u32)bVar1) * 0x14) /
                                    ((u32)bVar1 + (u32)*(u8 *)((u8 *)PS2_PTR(iVar6) + 0x159));
                }
                iVar8 = 5 - uVar5 / 0x14;
                bVar1 = *(u8 *)(iVar7 + 0x7B);
                if (iVar8 == 0) {
                    iVar8 = 0;
                }
                else {
                    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
                    iVar8 = (int)(g_7000015C >> 0x10) % iVar8;
                }
                iVar3 = func_001F1280();
                iVar4 = func_001F1300(param_1);
                iVar6 = -(u32)bVar1 + 0x14;
                if (iVar6 < 0) {
                    iVar6 = -(u32)bVar1 + 0x15;
                }
                uVar5 = ((iVar6 >> 1) + iVar3 + iVar4) - iVar8 & 0xFFFF;
                if (uVar5 == 0) {
                    *(u16 *)(iVar7 + 0x78) = 0;
                }
                else {
                    uVar5 = (uVar5 * 0x32) / 0x3C;
                    uVar2 = (u16)uVar5;
                    if ((uVar5 & 0xFFFF) == 0) {
                        uVar2 = 1;
                    }
                    *(u16 *)(iVar7 + 0x78) = uVar2;
                }
                func_00204D00(param_1, 1);
            }
        }
    }
    else {
        *(u32 *)(iVar7 + 0xBC) = *(u32 *)(iVar7 + 0xBC) & 0xFFF8003F;
        *(u8 *)(iVar7 + 0x7D) = 0;
    }
}

/* 0x00212790, 0x114 bytes. */
void func_00212790(int param_1, int param_2, int param_3)
{
    int iVar1;
    int iVar2;
    u32 uVar3;

    param_1 = param_1 * 0x290;
    *(u8 *)(g_0073DCA1 + param_1) = param_2;
    iVar1 = *(int *)(param_3 * 4 + param_1 + 0x73DA28);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0xC1A0) = 0x3F80000080808080;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0xC1F0) = 0x3F80000080808080;
    uVar3 = *(u8 *)(g_0073DCA1 + param_1) + 1;
    iVar2 = (uVar3 % 5) * 0x28;
    uVar3 = uVar3 / 5;
    *(long long *)((u8 *)PS2_PTR(iVar1) + 0xC1F8) =
              (long long)(int)((iVar2 + 200) * 0x10 | 8) | (long long)(int)(uVar3 * 0x300 | 8) << 0x10;
    *(long long *)((u8 *)PS2_PTR(iVar1) + 0xC208) =
              (long long)(int)((iVar2 + 0xF0) * 0x10 | 8) |
              (long long)(int)((uVar3 * 0x30 + 0x30) * 0x10 | 8) << 0x10;
}

/* 0x00212910, 0x94 bytes. */
void func_00212910(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar2 = 0;
    iVar3 = param_1 * 0x290 + 0x73DA20;
    iVar1 = iVar3;
    do {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x10) = 0;
        iVar2 = iVar2 + 1;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x14) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x18) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x1C) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x20) = 0xBF800000;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x24) = 0xBF800000;
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x28) = 0;
        iVar1 = iVar1 + 0x1C;
    } while (iVar2 < 0xC);
    iVar1 = 0;
    do {
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x160) = 0;
        iVar1 = iVar1 + 1;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x164) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x168) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x16C) = 0;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x170) = 0xBF800000;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x174) = 0xBF800000;
        *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x178) = 0;
        iVar3 = iVar3 + 0x1C;
    } while (iVar1 < 8);
}

/* 0x00237040, 0x17C bytes. */
void func_00237040(u8 *param_1)
{
    int cVar2;
    float fVar4;
    int iVar1;
    u8 * iVar3;
    long long lVar5;

    iVar3 = func_001F14E0(param_1);
    iVar1 = *(int *)(param_1 + 0x14);
    lVar5 = func_00236F30(param_1);
    if ((lVar5 != 0) &&
          (func_00236ED0(param_1),
          (*(u32 *)(*(int *)(*(int *)(*(int *)(param_1 + 8) + 0x14) + 0x210) + 0x18) & 0x2800) == 0
          )) {
        iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x110);
        if (iVar1 == 0) {
            cVar2 = 'j';
        }
        else {
            cVar2 = *(char *)((u8 *)PS2_PTR(iVar1) + 0x1C);
        }
        if (cVar2 == ',' || cVar2 == 31) {
            fVar4 = 1.0;
        }
        else {
            if (iVar1 == 0) {
                cVar2 = 'j';
            }
            else {
                cVar2 = *(char *)((u8 *)PS2_PTR(iVar1) + 0x1C);
            }
            if (cVar2 == '-' || cVar2 == 30) {
                fVar4 = 0.5;
            }
            else {
                fVar4 = 1.0;
            }
        }
        g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
        if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)*(u8 *)(iVar3 + 8) * fVar4)) {
            func_00236D90(PS2_ADDR(param_1));
        }
        else {
            func_00206080(PS2_ADDR(param_1));
        }
    }
}

/* 0x00239140, 0x18C bytes. */
int func_00239140(u8 *param_1, int param_2)
{
    u8 * iVar1;
    u8 * iVar3;
    u32 uVar2;
    u32 uVar4;

    iVar3 = (u8 *)PS2_PTR(*(int *)(param_1 + 0x14));
    if ((*(u32 *)(*(int *)(iVar3 + 0x210) + 0x18) & 8) == 0) {
        uVar2 = 0;
    }
    else {
        iVar1 = (u8 *)PS2_PTR(*(int *)(param_1 + 8));
        if (((*(u32 *)(*(int *)(*(int *)(iVar1 + 0x14) + 0x210) + 0x18) & 0x20) != 0) ||
              (*(float *)(iVar3 + 0x44) - *(float *)(*(int *)(iVar1 + 0x14) + 0x44) <= 100.0)) {
            iVar3 = func_001F14E0(param_1);
            uVar4 = (u32)*(u8 *)(iVar3 + 7);
            if (param_2 == 0) {
                if (*(char *)(iVar1 + 0x7D) != 3) {
                    return 0;
                }
            }
            else if (*(char *)(iVar1 + 0x7D) == 3) {
                uVar4 = uVar4 << 1;
            }
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            if ((g_7000015C >> 0x10) % 100 < uVar4 >> 1) {
                func_00271A10(param_1, 0x1A);
                uVar2 = 1;
            }
            else {
                uVar2 = 0;
            }
        }
        else {
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            if ((g_7000015C >> 0x10) % 100 < 0x32) {
                func_00204B60(param_1, 0x100020);
            }
            else {
                func_00271A10(param_1, 0x19);
            }
            uVar2 = 1;
        }
    }
    return uVar2;
}

/* 0x00242900, 0x32C bytes. */
int func_00242900(u8 *param_1, int param_2, int param_3)
{
    int bVar5;
    u8 * iVar2;
    int iVar3;
    int iVar4;
    int iVar8;
    int iVar9;
    int sVar1;
    u32 uVar6;
    u32 uVar7;

    iVar2 = (u8 *)PS2_PTR(*(int *)(param_1 + 0x210));
    iVar3 = *(int *)(iVar2 + 0x14);
    iVar4 = *(int *)(*(int *)(*(int *)(param_1 + 0x110) + 4) + 0xC);
    if (*(u32 *)g_00669DB8 == 4) {
        uVar6 = 6;
    }
    else if ((*(float *)(param_1 + 0x168) <= 0.0001) || (*(char *)(param_1 + 0x18B) != 2)) {
        if (*(u8 *)(param_1 + 0x14E) < 2) {
            uVar6 = func_002F41E0(*(u32 *)((u32)*(u8 *)(param_1 + 0x14E) * 0x48 + 0x669DE8));
            uVar6 = uVar6 & 0xFF;
        }
        else if ((long long)*(char *)(param_1 + 0x19C) << 0x38 < 0) {
            uVar6 = func_002F41E0(*(u32 *)((u32)*(u8 *)(param_1 + 0x15B) * 0x48 + 0x669DE8));
            uVar6 = uVar6 & 0xFF;
        }
        else {
            uVar6 = 0x13;
        }
        uVar6 = (int)uVar6 >> 1;
        if (5 < uVar6) {
            uVar6 = 6;
        }
    }
    else {
        uVar6 = 7;
    }
    if (iVar4 != 0) {
        iVar9 = 0;
        iVar8 = *(int *)(*(int *)(param_1 + 0x110) + 0xC) + (iVar4 + -1) * 0x30;
        if (0 < iVar4) {
            uVar7 = 1 << (uVar6 + 0xB & 0x1F);
            do {
                if ((*(short *)((u8 *)PS2_PTR(iVar8) + 0x24) == param_3) && ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x28) & 0x800) != 0)) {
                    if (iVar3 == 0) {
                        sVar1 = *(short *)((u8 *)PS2_PTR(iVar8) + 0x26);
                        if (sVar1 == 0) {
                            if (((*(u32 *)(iVar2 + 0x18) & 4) != 0) && ((*(u32 *)(iVar2 + 0x18) & 0x20) == 0)) {
                                param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                                break;
                            }
                        }
                        else if (sVar1 == 0xB) {
                            if (((*(u32 *)(iVar2 + 0x18) & 4) != 0) && ((*(u32 *)(iVar2 + 0x18) & 0x20) != 0)) {
                                param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                                break;
                            }
                        }
                        else {
                            if (*(u32 *)g_00669DB8 == 4) {
                                bVar5 = true;
                            }
                            else if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & 0x7F000) == 0) {
                                bVar5 = true;
                            }
                            else if ((uVar6 == 0) || ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & uVar7) == 0)) {
                                bVar5 = false;
                            }
                            else {
                                bVar5 = true;
                            }
                            if ((bVar5) && (sVar1 == **(short **)(param_1 + 0x210))) {
                                param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                                break;
                            }
                        }
                    }
                    else {
                        if (*(u32 *)g_00669DB8 == 4) {
                            bVar5 = true;
                        }
                        else if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & 0x7F000) == 0) {
                            bVar5 = true;
                        }
                        else if ((uVar6 == 0) || ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & uVar7) == 0)) {
                            bVar5 = false;
                        }
                        else {
                            bVar5 = true;
                        }
                        if ((bVar5) && (*(short *)((u8 *)PS2_PTR(iVar8) + 0x26) == **(short **)(param_1 + 0x210))) {
                            param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                            break;
                        }
                    }
                }
                iVar9 = iVar9 + 1;
                iVar8 = iVar8 + -0x30;
            } while (iVar9 < iVar4);
        }
    }
    return param_2;
}

/* 0x002431F0, 0x2EC bytes. */
int func_002431F0(u8 *param_1, int param_2, int param_3)
{
    int bVar5;
    u8 * iVar1;
    int iVar2;
    int iVar3;
    int iVar8;
    int iVar9;
    u32 uVar4;
    u32 uVar6;
    u32 uVar7;

    iVar1 = (u8 *)PS2_PTR(*(int *)(param_1 + 0x210));
    iVar2 = *(int *)(iVar1 + 0x14);
    iVar3 = *(int *)(*(int *)(*(int *)(param_1 + 0x110) + 4) + 0xC);
    if (*(u32 *)g_00669DB8 == 4) {
        uVar6 = 6;
    }
    else if ((*(float *)(param_1 + 0x168) <= 0.0001) || (*(char *)(param_1 + 0x18B) != 2)) {
        if (*(u8 *)(param_1 + 0x14E) < 2) {
            uVar6 = func_002F41E0(*(u32 *)((u32)*(u8 *)(param_1 + 0x14E) * 0x48 + 0x669DE8));
            uVar6 = uVar6 & 0xFF;
        }
        else if ((long long)*(char *)(param_1 + 0x19C) << 0x38 < 0) {
            uVar6 = func_002F41E0(*(u32 *)((u32)*(u8 *)(param_1 + 0x15B) * 0x48 + 0x669DE8));
            uVar6 = uVar6 & 0xFF;
        }
        else {
            uVar6 = 0x13;
        }
        uVar6 = (int)uVar6 >> 1;
        if (5 < uVar6) {
            uVar6 = 6;
        }
    }
    else {
        uVar6 = 7;
    }
    if (iVar3 != 0) {
        iVar9 = 0;
        iVar8 = *(int *)(*(int *)(param_1 + 0x110) + 0xC) + (iVar3 + -1) * 0x30;
        if (0 < iVar3) {
            uVar7 = 1 << (uVar6 + 0xB & 0x1F);
            do {
                if (*(short *)((u8 *)PS2_PTR(iVar8) + 0x24) == param_3) {
                    if (iVar2 == 0) {
                        if (*(short *)((u8 *)PS2_PTR(iVar8) + 0x26) == 0) {
                            uVar4 = *(u32 *)(iVar1 + 0x18);
                            if (((uVar4 & 4) != 0) && ((uVar4 & 0x20) == 0)) {
                                param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                                break;
                            }
                        }
                        else {
                            if (*(u32 *)g_00669DB8 == 4) {
                                bVar5 = true;
                            }
                            else if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & 0x7F000) == 0) {
                                bVar5 = true;
                            }
                            else if ((uVar6 == 0) || ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & uVar7) == 0)) {
                                bVar5 = false;
                            }
                            else {
                                bVar5 = true;
                            }
                            if ((bVar5) && (*(short *)((u8 *)PS2_PTR(iVar8) + 0x26) == **(short **)(param_1 + 0x210))) {
                                param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                                break;
                            }
                        }
                    }
                    else {
                        if (*(u32 *)g_00669DB8 == 4) {
                            bVar5 = true;
                        }
                        else if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & 0x7F000) == 0) {
                            bVar5 = true;
                        }
                        else if ((uVar6 == 0) || ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x2C) & uVar7) == 0)) {
                            bVar5 = false;
                        }
                        else {
                            bVar5 = true;
                        }
                        if ((bVar5) && (*(short *)((u8 *)PS2_PTR(iVar8) + 0x26) == **(short **)(param_1 + 0x210))) {
                            param_2 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar8) + 2);
                            break;
                        }
                    }
                }
                iVar9 = iVar9 + 1;
                iVar8 = iVar8 + -0x30;
            } while (iVar9 < iVar3);
        }
    }
    return param_2;
}

/* 0x002545C0, 0x4C bytes. */
float func_002545C0(u8 *param_1)
{
    float fVar2;
    u8 * iVar1;

    if (*(int *)(param_1 + 0x11C) == 0) {
        fVar2 = 45.0;
    }
    else {
        iVar1 = func_0014F810(*(int *)(param_1 + 0x11C), 0xB);
        fVar2 = *(float *)(param_1 + 0x94) - *(float *)(iVar1 + 0x34);
    }
    return fVar2;
}

/* 0x00263630, 0x494 bytes. */
void func_00263630(int param_1)
{
    int iStack_10;
    int iStack_20;
    int iVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    u8 * iVar9;
    unsigned long long uVar10;
    unsigned long long uVar11;
    unsigned long long uVar2;

    iVar3 = (int)param_1 * 0x2C;
    iVar9 = g_00732220;
    iStack_20 = 0;
    if (((*(u32 *)g_00669F60 & 2) != 0) && (param_1 != 0)) {
        iStack_20 = 0xC0;
    }
    *(u32 *)(g_007325FC + iVar3) = 0;
    *(u32 *)(g_00732604 + iVar3) = 0;
    *(u32 *)(g_00732608 + iVar3) = 0;
    *(u8 *)(g_0073260D + iVar3) = 0;
    iVar5 = (int)param_1 * 0x1380;
    iStack_10 = 0;
    *(u8 *)(g_0073260E + iVar3) = 4;
    do {
        iVar3 = *(int *)(iVar9 + 0x2E0) + iVar5;
        uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F02);
        func_001057F0((u8 *)PS2_PTR(iVar3 + 0x1B770), uVar2, 0);
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B790) = 0x3F80000080808080;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B798) = 0x7480008;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7A8) = 0xA480388;
        iVar4 = (int)(((u32)((iStack_20 + 0x99) * 0x280) / 0x1E0) * 0x1C0) >> 9;
        iVar7 = 400;
        iVar8 = 0;
        iVar6 = 0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7A0) = (long long)(iVar4 * 8 + 0x7900) << 0x10 | 0xFFFE00008DD0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7B0) = (long long)((iVar4 + 0x1C) * 8 + 0x7900) << 0x10 | 0xFFFE00008FB0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7A0) = 0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7B0) = 0;
        iVar4 = 0x8900;
        iVar3 = (int)(((u32)((iStack_20 + 0x99) * 0x280) / 0x1E0) * 0x1C0) >> 9;
        uVar10 = (long long)(iVar3 * 8 + 0x7900) << 0x10;
        uVar11 = (long long)((iVar3 + 0x1C) * 8 + 0x7900) << 0x10;
        do {
            iVar3 = *(int *)(iVar9 + 0x2E0) + iVar5 + iVar6;
            uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEF);
            func_001057F0((u8 *)PS2_PTR(iVar3 + 0x1B7C0), uVar2, 0);
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7E0) = 0x3F80000080808080;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7E8) = 0x80C88;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7F8) = 0x3080F08;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7F0) = (long long)iVar4 | uVar10 | 0xFFFE00000000;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B800) = (long long)((iVar7 + 0x15) * 0x10 + 0x7000) | uVar11 | 0xFFFE00000000
            ;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B7F0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B800) = 0;
            iVar3 = *(int *)(iVar9 + 0x2E0) + iVar5 + iVar6;
            uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEF);
            func_001057F0((u8 *)PS2_PTR(iVar3 + 0x1B970), uVar2, 0);
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B990) = 0x3F80000080808080;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B998) = 0x80C88;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B9A8) = 0x3080F08;
            iVar4 = iVar4 + 0x1D0;
            iVar1 = iVar7 + 0x25;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B9A0) = (long long)((iVar7 + 0x10) * 0x10 + 0x7000) | uVar10 | 0xFFFE00000000
            ;
            iVar7 = iVar7 + 0x1D;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B9B0) = (long long)(iVar1 * 0x10 + 0x7000) | uVar11 | 0xFFFE00000000;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B9A0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B9B0) = 0;
            iVar3 = *(int *)(iVar9 + 0x2E0) + iVar5;
            func_001050B0((u8 *)PS2_PTR(iVar3 + 0x1BB00));
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1BB10) = 0x8000000044;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1BB18) = 0x43;
            iVar3 = *(int *)(iVar9 + 0x2E0) + iVar5;
            func_001050B0((u8 *)PS2_PTR(iVar3 + 0x1B950));
            iVar8 = iVar8 + 1;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B960) = 0x8000000044;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1B968) = 0x43;
            iVar6 = iVar6 + 0x50;
        } while (iVar8 < 5);
        iStack_10 = iStack_10 + 1;
        iVar9 = iVar9 + 4;
    } while (iStack_10 < 2);
}

/* 0x0029F3C0, 0x3C4 bytes. */
void func_0029F3C0(u8 *param_1)
{
    int bVar5;
    int cVar1;
    int iVar2;
    u8 * iVar6;
    int iVar7;
    long long lVar4;
    int uVar3;

    iVar6 = param_1;
    iVar2 = *(int *)(*(int *)(iVar6 + 0x210) + 0x14);
    if ((long long)*(char *)(iVar6 + 0x19C) << 0x38 < 0) {
        *(u8 *)(iVar6 + 0x17E) = 0;
        *(u8 *)(iVar6 + 0x17F) = 0;
    }
    else {
        iVar7 = *(short *)(iVar6 + 0x178) * 0xC0;
        cVar1 = *(char *)(g_006A3AE4 + iVar7);
        if (((long long)*(char *)(iVar6 + 0x19E) << 0x3E < 0) && (lVar4 = func_002711F0(param_1), lVar4 != 0)) {
            bVar5 = *(u8 *)(iVar6 + 0x1BF);
            if ((bVar5 == 0) || (5 < bVar5)) {
                if (cVar1 == 0) {
                    *(u8 *)(iVar6 + 0x17E) = 4;
                }
                else {
                    *(char *)(iVar6 + 0x17E) = cVar1;
                }
            }
            else {
                *(u8 *)(iVar6 + 0x17E) = bVar5;
            }
            *(u8 *)(iVar6 + 0x17F) = 2;
        }
        else {
            lVar4 = func_003E2DC0(PS2_ADDR(param_1));
            if (lVar4 == 0) {
                if (((long long)*(char *)(iVar6 + 0x19D) << 0x3A < 0) &&
                      ((long long)*(char *)(iVar6 + 0x19C) << 0x3E < 0)) {
                    *(u8 *)(iVar6 + 0x17E) = 3;
                    if (*(u8 *)(iVar6 + 0x14E) < 2) {
                        *(char *)(iVar6 + 0x17F) = *(char *)(g_006A3ADE + iVar7) + 1;
                    }
                    else {
                        *(u8 *)(iVar6 + 0x17F) = 1;
                    }
                }
                else if ((*(u8 *)(iVar6 + 0x14E) < 2) &&
                                (((long long)*(char *)(iVar6 + 0x19F) << 0x3E < 0 &&
                                  ((long long)*(char *)(iVar6 + 0x19C) << 0x3E < 0)))) {
                    if (*(u8 *)(g_006A3AE0 + iVar7) < 3) {
                        *(u8 *)(iVar6 + 0x17E) = 1;
                    }
                    else {
                        *(u8 *)(iVar6 + 0x17E) = 5;
                    }
                    *(char *)(iVar6 + 0x17F) = *(char *)(g_006A3ADE + iVar7) + 1;
                }
                else if ((iVar2 == 0) || ((bVar5 = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x19), bVar5 == 0 || (5 < bVar5)))) {
                    if ((iVar2 == 0) || (lVar4 = func_002711F0(param_1), lVar4 == 0)) {
                        if ((iVar2 != 0) || ((*(u32 *)(*(int *)(iVar6 + 0x210) + 0x18) & 0x8000000) != 0)) {
                            *(char *)(iVar6 + 0x17E) = cVar1;
                            *(u8 *)(iVar6 + 0x17F) = 0;
                        }
                    }
                    else {
                        *(char *)(iVar6 + 0x17E) = cVar1;
                        if (*(u8 *)(iVar6 + 0x14E) < 2) {
                            if ((*(u32 *)((u8 *)PS2_PTR(iVar2) + 0x28) & 0x4000) == 0) {
                                if ((*(u32 *)((u8 *)PS2_PTR(iVar2) + 0x28) & 0x8000) == 0) {
                                    *(u8 *)(iVar6 + 0x17F) = 0;
                                }
                                else {
                                    *(u8 *)(iVar6 + 0x17F) = *(u8 *)(g_006A3ADD + iVar7);
                                }
                            }
                            else {
                                *(u8 *)(iVar6 + 0x17F) = *(u8 *)(g_006A3ADC + iVar7);
                            }
                        }
                        else {
                            *(char *)(iVar6 + 0x17E) = cVar1;
                            bVar5 = *(u8 *)(g_006A3AAB + iVar7);
                            if (bVar5 < 0xB) {
                                *(u8 *)(iVar6 + 0x17F) = 0;
                            }
                            else if (bVar5 < 0xE) {
                                *(u8 *)(iVar6 + 0x17F) = 1;
                            }
                            else if (bVar5 < 0x11) {
                                *(u8 *)(iVar6 + 0x17F) = 2;
                            }
                            else {
                                *(u8 *)(iVar6 + 0x17F) = 3;
                            }
                        }
                    }
                }
                else {
                    *(u8 *)(iVar6 + 0x17E) = bVar5;
                    if ((*(u32 *)((u8 *)PS2_PTR(iVar2) + 0x28) & 0x4000) == 0) {
                        if ((*(u32 *)((u8 *)PS2_PTR(iVar2) + 0x28) & 0x8000) == 0) {
                            *(u8 *)(iVar6 + 0x17F) = 1;
                        }
                        else {
                            bVar5 = *(u8 *)(g_006A3ADD + iVar7);
                            if (bVar5 < 2) {
                                bVar5 = 1;
                            }
                            *(u8 *)(iVar6 + 0x17F) = bVar5;
                        }
                    }
                    else {
                        bVar5 = *(u8 *)(g_006A3ADC + iVar7);
                        if (bVar5 < 2) {
                            bVar5 = 1;
                        }
                        *(u8 *)(iVar6 + 0x17F) = bVar5;
                    }
                }
            }
            else {
                uVar3 = func_003E2F70(PS2_ADDR(param_1));
                *(u8 *)(iVar6 + 0x17E) = uVar3;
                if (*(u8 *)(iVar6 + 0x14E) < 2) {
                    *(char *)(iVar6 + 0x17F) = *(char *)(g_006A3ADF + iVar7) + 1;
                }
                else {
                    *(u8 *)(iVar6 + 0x17F) = 1;
                }
            }
        }
        if (((*(u32 *)(*(int *)(iVar6 + 0x210) + 0x18) & 0x8000000) != 0) &&
              (*(char *)(iVar6 + 0x17E) != 1)) {
            *(u8 *)(iVar6 + 0x17E) = 0;
        }
    }
}

/* 0x0029F930, 0x1FC bytes. */
void func_0029F930(float param_1, u8 *param_2)
{
    int iVar5;
    u8 * iVar6;
    int sVar1;
    int sVar3;
    int sVar4;
    int sVar7;
    int uVar2;

    if (1.0 < param_1) {
        sVar7 = (short)(int)param_1;
    }
    else {
        sVar7 = 1;
    }
    iVar6 = param_2;
    if (*(u16 *)(iVar6 + 0x15C) != 0) {
        if ((*(u32 *)(*(int *)(iVar6 + 0x210) + 0x18) & 0x800) == 0) {
            *(u16 *)(iVar6 + 0x15C) = 0;
        }
        else {
            iVar5 = *(short *)(iVar6 + 0x178) * 0xC0;
            if ((((*(u32 *)g_00669F60 & 0x14280000) == 0) && ((*(u32 *)(g_006A3AE8 + iVar5) & 2) == 0)) &&
                  ((int)(0x96 - (u32)*(u16 *)(iVar6 + 0x15C)) % (int)*(short *)(iVar6 + 0x170) == 0)) {
                if (0 < *(short *)(g_006A3AB2 + iVar5)) {
                    sVar3 = *(short *)(g_006A3AB2 + iVar5) + -1;
                    if (sVar3 < 1) {
                        sVar3 = 1;
                    }
                    sVar1 = *(short *)(g_006A3AB0 + iVar5);
                    sVar4 = sVar3;
                    if (sVar1 < sVar3) {
                        sVar4 = sVar1;
                    }
                    if (sVar4 < 1) {
                        sVar3 = 0;
                    }
                    else if (sVar1 < sVar3) {
                        sVar3 = sVar1;
                    }
                    *(short *)(g_006A3AB2 + iVar5) = sVar3;
                    if (*(short *)(g_006A3AB4 + iVar5) < sVar3) {
                        *(short *)(g_006A3AB4 + iVar5) = sVar3;
                    }
                }
            }
            if ((long long)sVar7 < (long long)(unsigned long long)*(u16 *)(iVar6 + 0x15C)) {
                *(u16 *)(iVar6 + 0x15C) = *(u16 *)(iVar6 + 0x15C) - sVar7;
            }
            else {
                *(u16 *)(iVar6 + 0x15C) = 0;
            }
        }
    }
    uVar2 = *(u16 *)(iVar6 + 0x172);
    if ((unsigned long long)uVar2 != 0) {
        if ((long long)sVar7 < (long long)(unsigned long long)uVar2) {
            *(u16 *)(iVar6 + 0x172) = uVar2 - sVar7;
        }
        else {
            *(u16 *)(iVar6 + 0x172) = 0;
        }
        if (*(short *)(iVar6 + 0x172) == 0) {
            func_002A6D20(*(u8 *)(iVar6 + 0x14E), 0x234);
            func_001531B0(param_2);
        }
    }
}

/* 0x002A54F0, 0x29C bytes. */
int func_002A54F0(int param_1, int param_2)
{
    int iVar1;
    int iVar3;
    u32 uVar2;
    u32 uVar4;
    u32 uVar5;

    if ((int)(*(u32 *)g_0077BEF4) < 100) {
        uVar2 = 0;
        uVar4 = *(u32 *)g_0077BEF4;
        do {
            iVar1 = uVar4 * 0x3C;
            if (*(int *)(g_0077A72C + iVar1) == 0x107) {
                *(u32 *)(g_0077A72C + iVar1) = param_1;
                iVar3 = (int)param_2 >> 8;
                *(u32 *)(g_0077A730 + iVar1) = param_2;
                param_2 = param_2 & 0xFF;
                if (iVar3 == 0) {
                    uVar5 = *(u32 *)(g_00440DA0 + param_2 * 4);
LAB_002a571c:
                    *(u32 *)(g_0077A734 + iVar1) = uVar5;
                }
                else {
                    if (iVar3 == 1) {
                        uVar5 = *(u32 *)((g_00440DA0 + 0x40) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if (iVar3 == 2) {
                        uVar5 = *(u32 *)((g_00440DA0 + 0xE0) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if ((iVar3 == 4) || ((0x65 < iVar3 && (iVar3 < 0x7E)))) {
                        uVar5 = *(u32 *)((g_00440FB0 + 0x80) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if ((iVar3 == 5) || ((0x7D < iVar3 && (iVar3 < 0x99)))) {
                        uVar5 = *(u32 *)((g_00440FB0 + 0xC0) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if ((iVar3 == 6) || ((0x98 < iVar3 && (iVar3 < 0xB0)))) {
                        uVar5 = *(u32 *)((g_00440FB0 + 0x100) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if ((iVar3 == 7) || ((0xAF < iVar3 && (iVar3 < 0xCB)))) {
                        uVar5 = *(u32 *)((g_00440FB0 + 0x130) + param_2 * 4);
                        goto LAB_002a571c;
                    }
                    if ((iVar3 < 9) || (0x65 < iVar3)) {
                        if (iVar3 == 3) {
                            uVar5 = *(u32 *)(g_00440FB0 + param_2 * 4);
                        }
                        else if (iVar3 == 8) {
                            uVar5 = *(u32 *)((g_00440FB0 + 0x1F0) + param_2 * 4);
                        }
                        else {
                            uVar5 = 0;
                        }
                        goto LAB_002a571c;
                    }
                    *(u32 *)(g_0077A734 + iVar1) = 0x40A00000;
                }
                *(u32 *)(g_0077A738 + iVar1) = 0;
                break;
            }
            uVar4 = uVar4 + 1;
            if (99 < uVar4) {
                uVar4 = 0;
            }
            uVar2 = uVar2 + 1;
        } while (uVar2 < 100);
        if (uVar2 < 100) {
            *(u32 *)(g_0077BEF4) = *(u32 *)(g_0077BEF4) + 1;
            uVar5 = 1;
        }
        else {
            uVar5 = 0;
        }
    }
    else {
        uVar5 = 0;
    }
    return uVar5;
}

/* 0x002A8030, 0x54 bytes. */
void func_002A8030(int param_1)
{
    int iVar2;
    u32 uVar1;

    if (param_1 < 0x30) {
        iVar2 = (int)param_1 * 0x110;
        *(u32 *)(g_0077CFA4 + iVar2) = 0;
        uVar1 = *(u32 *)(g_0077CFA0 + iVar2);
        if (uVar1 <= g_0045D578) {
            g_0045D578 = uVar1;
        }
        g_0045D574 = g_0045D574 + 1;
    }
}

/* 0x002AEE90, 0x1D4 bytes. */
void func_002AEE90(int param_1, int param_2, int param_3)
{
    int iVar1;
    int iVar2;
    int iVar3;
    u32 uVar4;
    unsigned long long uVar5;

    g_70000D60 = 2;
    if (param_2 < 0xFF) {
        iVar3 = (int)param_2 * 0x40;
        if (g_0045D2C0 == 0x5B4BC0) {
            *(u32 *)(g_0078E03C + iVar3) = 0;
            iVar2 = 0;
            *(u32 *)(g_0078E030 + iVar3) = param_3;
        }
        else if (g_0045D2C0 == 0x5B4E00) {
            *(u32 *)(g_0078E034 + iVar3) = param_3;
            iVar2 = 1;
        }
        else {
            *(u32 *)(g_0078E03C + iVar3) = 0;
            iVar2 = 0;
            *(u32 *)(g_0078E030 + iVar3) = param_3;
        }
        *(u32 *)(iVar2 * 4 + iVar3 + 0x78E010 + 0x28) = param_1;
        if (*(int *)(g_0078E02C + iVar3) != 0) {
            iVar2 = *(int *)(g_0078E028 + iVar3);
            if (*(int *)(g_0078E02C + iVar3) == 1) {
                *(u32 *)(g_0078E02C + iVar3) = 0;
            }
            if (*(int *)(g_0078E02C + iVar3) == 3) {
                uVar5 = 0;
                uVar4 = *(u32 *)(g_004415A0 + iVar2 * 4) | 0x1000;
                *(u32 *)(g_0078E02C + iVar3) = 2;
            }
            else if (*(int *)(g_0078E02C + iVar3) == 2) {
                uVar4 = *(u32 *)(g_004415A0 + iVar2 * 4);
                if (iVar2 == 0x13) {
                    uVar5 = 0;
                }
                else {
                    uVar5 = 1;
                }
            }
            else {
                uVar5 = 0;
                uVar4 = *(u32 *)(g_004415A0 + iVar2 * 4);
            }
            if (iVar2 == 0x1B) {
                func_002AE5B0();
            }
            else if (iVar2 == 0x15) {
                func_002AE680();
            }
            else if ((uVar4 & 0x20000000) == 0) {
                iVar1 = *(int *)(g_0078E024 + iVar3);
                if (iVar1 == 0) {
                    if (*(int *)(g_004412F0 + iVar2 * 4) != 0x18B) {
                        func_002AE8D0(iVar3 + 0x78E010, uVar4, uVar5);
                    }
                }
                else {
                    *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) | 3;
                }
            }
            else {
                func_002AE750();
            }
        }
    }
    g_70000D60 = 0;
}

/* 0x002BEC60, 0x1C8 bytes. */
int func_002BEC60(u8 *param_1, int param_2)
{
    float fVar12;
    u8 * iVar5;
    int iVar6;
    u8 * iVar7;
    int iVar9;
    long long lVar8;
    u8 * pbVar4;
    u16 * puVar11;
    int sVar1;
    u32 uVar10;
    u32 uVar2;
    int uVar3;

    iVar7 = param_1;
    uVar3 = func_001FF100(*(u16 *)(iVar7 + 0x54), 10);
    pbVar4 = (u8 *)func_0027F120(uVar3);
    iVar5 = func_001FF140(*(u16 *)(iVar7 + 0x54));
    uVar2 = *(u32 *)(iVar7 + 0x5C);
    puVar11 = (u16 *)(iVar5 + 0x30);
    uVar10 = 0;
    iVar9 = g_700001D4 + (u32)*(u16 *)(iVar7 + 0x56) * 0x20;
    if ((param_2 == 3) || (param_2 == 1)) {
        lVar8 = 0;
    }
    else if ((param_2 == 2) || (param_2 == 0)) {
        lVar8 = 1;
    }
    else {
        lVar8 = 0;
    }
    if ((((*(u8 *)(iVar7 + 0x69) & 8) == 0) && (lVar8 != 0)) ||
          (((*(u8 *)(iVar7 + 0x69) & 8) != 0 && (lVar8 == 0)))) {
        fVar12 = *(float *)((u32)*pbVar4 * 0x10 + 0x799414);
        if (lVar8 == 0) {
            fVar12 = -fVar12;
            sVar1 = *(short *)(iVar5 + 4);
        }
        else {
            sVar1 = *(short *)(iVar5 + 4);
        }
        if (sVar1 != 0) {
            do {
                if ((uVar2 & 1 << (uVar10 & 0x1F)) != 0) {
                    for (iVar6 = func_00207D80(*puVar11); iVar6 != 0; iVar6 = iVar6 + -1) {
                        *(float *)((u8 *)PS2_PTR(iVar9) + 4) = *(float *)((u8 *)PS2_PTR(iVar9) + 4) + fVar12;
                        *(float *)((u8 *)PS2_PTR(iVar9) + 0x14) = *(float *)((u8 *)PS2_PTR(iVar9) + 0x14) + fVar12;
                        iVar9 = iVar9 + 0x20;
                    }
                }
                puVar11 = (u16 *)func_001FF230(puVar11);
                uVar10 = uVar10 + 1;
            } while (uVar10 < *(u16 *)(iVar5 + 4));
        }
        *(u8 *)(iVar7 + 0x68) = 8;
        func_0027E800(param_1, lVar8);
    }
    return 1;
}

/* 0x002CDF40, 0xE4 bytes, matching. */
int func_002CDF40(int param_1)
{
    u8 * iVar2;
    int uVar1;

    if (param_1 < 0x10) {
        switch(param_1) {
        case 0:
            uVar1 = 0;
            break;
        case 1:
            uVar1 = 1;
            break;
        case 2:
            uVar1 = 2;
            break;
        case 3:
            uVar1 = 3;
            break;
        case 4:
            uVar1 = 4;
            break;
        case 5:
            uVar1 = 5;
            break;
        case 6:
            uVar1 = 6;
            break;
        case 7:
            uVar1 = 7;
            break;
        case 8:
            uVar1 = 8;
            break;
        case 9:
            uVar1 = 9;
            break;
        case 10:
            uVar1 = 10;
            break;
        case 0xB:
            uVar1 = 0xB;
            break;
        case 0xC:
            uVar1 = 0xC;
            break;
        case 0xD:
            uVar1 = 0xD;
            break;
        case 0xE:
            uVar1 = 0xF;
            break;
        case 0xF:
            uVar1 = 0xE;
            break;
        default:
            goto switchD_002cdf70_default;
        }
    }
    else {
        if (param_1 < 0x14) {
            iVar2 = func_0019FBC0((int)param_1 + -0x10);
            return *(u8 *)(iVar2 + 5);
        }
switchD_002cdf70_default:
        uVar1 = 0xF;
    }
    return uVar1;
}

/* 0x00329DA0, 0x2A0 bytes. */
void func_00329DA0(int param_1)
{
    u8 auStack_100[256];
    int iVar1;
    long long lVar4;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar5;

    uVar2 = func_0032F420(0);
    uVar2 = func_00337A10(uVar2);
    func_002F4080(uVar2);
    iVar1 = PS2_ADDR(func_0030E0F0());
    uVar3 = PS2_ADDR(func_00390760(param_1));
    if (param_1 == 0x5E) {
        uVar2 = PS2_ADDR(func_002F2A30(*(u32 *)((u8 *)PS2_PTR(iVar1) + 4)));
        func_001204B0(auStack_100, uVar3, uVar2);
    }
    else if (((param_1 == 0x86) || (param_1 == 0x85)) || (param_1 == 0x84)) {
        uVar2 = func_00327CC0();
        uVar2 = PS2_ADDR(func_00372660(uVar2));
        uVar5 = func_00327C80();
        uVar5 = PS2_ADDR(func_0030CB80(uVar5));
        func_001204B0(auStack_100, uVar3, uVar2, uVar5);
    }
    else if (((param_1 == 0x82) || (param_1 == 0x80)) || ((param_1 == 0x81 || (param_1 == 0x83)))) {
        uVar2 = PS2_ADDR(func_002F2890(uVar2));
        func_001204B0(auStack_100, uVar3, uVar2);
    }
    else {
        if (param_1 != 0x45) {
            return;
        }
        lVar4 = func_0032F780();
        if (lVar4 == 0x39) {
            uVar2 = PS2_ADDR(func_002F2890(uVar2));
            uVar5 = PS2_ADDR(func_00372680(0));
            func_001204B0(auStack_100, uVar3, uVar2, uVar5);
        }
        else if (lVar4 == 0x38) {
            uVar2 = PS2_ADDR(func_002F2890(uVar2));
            uVar5 = PS2_ADDR(func_00372680(1));
            func_001204B0(auStack_100, uVar3, uVar2, uVar5);
        }
        else if (lVar4 == 0x37) {
            uVar2 = PS2_ADDR(func_002F2890(uVar2));
            uVar5 = PS2_ADDR(func_00372680(2));
            func_001204B0(auStack_100, uVar3, uVar2, uVar5);
        }
        else if (lVar4 == 0x36) {
            iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 8);
            if ((iVar1 == -1) || (iVar1 == 100)) {
                g_0045CFEC = 0xFFFFFFFF;
                func_00329D80(1);
                return;
            }
            uVar2 = PS2_ADDR(func_002F2890(uVar2));
            uVar5 = PS2_ADDR(func_003725F0(iVar1));
            func_001204B0(auStack_100, uVar3, uVar2, uVar5);
        }
    }
    func_00374EE0(PS2_ADDR(auStack_100));
}

/* 0x0032FC80, 0x14C bytes. */
void func_0032FC80(void)
{
    int aiStack_30[12];
    int iVar6;
    int iVar8;
    int iVar9;
    long long lVar4;
    int * piVar7;
    int uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar5;

    uVar2 = func_0032F780();
    func_0032F670();
    iVar8 = 0;
    piVar7 = aiStack_30;
    do {
        if (iVar8 < 8) {
            uVar3 = func_0032F170(uVar2, iVar8);
            lVar4 = func_0032F420(uVar3);
        }
        else {
            lVar4 = func_0032F1A0(uVar2, iVar8 + -8);
        }
        if (lVar4 != -1) {
            *piVar7 = (int)lVar4;
            piVar7 = piVar7 + 1;
        }
        iVar8 = iVar8 + 1;
    } while (iVar8 < 0xF);
    iVar9 = 0;
    iVar8 = 0;
    piVar7 = aiStack_30;
    do {
        uVar5 = func_00337A10(*piVar7);
        if (uVar5 < 0x19F) {
            iVar6 = *(u32 *)g_005BA6A0 + *piVar7 * 0x2C;
            *(u8 *)(g_0076F650 + iVar9) = *(u8 *)((u8 *)PS2_PTR(iVar6) + 6);
            uVar1 = func_0032F950(*(u8 *)((u8 *)PS2_PTR(iVar6) + 9));
            *(u8 *)(g_0076F6FA + iVar9) = uVar1;
            iVar9 = iVar9 + 1;
        }
        iVar8 = iVar8 + 1;
        piVar7 = piVar7 + 1;
    } while (iVar8 < 9);
    func_00279380(0x22, 2);
    func_0032F640();
}

/* 0x0036BD10, 0x4E4 bytes. */
void func_0036BD10(void)
{
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar13;
    u8 * iVar2;
    int iVar4;
    int iVar9;
    long long lVar7;
    u32 uVar1;
    u32 uVar3;
    unsigned long long uVar5;
    unsigned long long uVar6;
    u32 uVar8;

    iVar13 = 0;
    uVar5 = func_00362570();
    uVar1 = *(u32 *)g_00669F70;
    if (uVar5 == 0x10) {
        iVar13 = 2;
    }
    else if (uVar5 == 0x11) {
        iVar13 = 4;
    }
    else if (uVar5 == 0x12) {
        iVar13 = 6;
    }
    else if (((long long)uVar5 < 6) || (0xF < (long long)uVar5)) {
        if (uVar5 < 3) {
            iVar13 = 0x1E;
        }
        else if ((int)uVar5 - 3U < 3) {
            iVar13 = 0xF;
        }
    }
    else {
        iVar13 = 0x1E;
    }
    iVar12 = 0;
    iVar11 = 0;
    iVar10 = 0;
    iVar9 = 0;
    uVar8 = 0;
    do {
        uVar6 = PS2_ADDR(func_0033EF80(uVar8));
        iVar4 = (int)uVar6;
        if ((*(u32 *)((u8 *)PS2_PTR(iVar4) + 100) & 1) != 0) {
            lVar7 = func_0033B320((u8 **)PS2_PTR(uVar6));
            if (lVar7 == 0) {
                if (uVar8 < 8) {
                    iVar4 = (iVar4 + -0x6A1D58) / 0x68;
                    iVar2 = func_00338410(iVar4);
                    iVar12 = iVar12 + (u32)*(u16 *)(iVar2 + 0x1E);
                    iVar2 = func_00338410(iVar4);
                    if (*(char *)(iVar2 + 0x25) == 'G') {
                        iVar4 = PS2_ADDR(func_00338410(iVar4));
                        uVar3 = (u32)*(u16 *)((u8 *)PS2_PTR(iVar4) + 0x1A);
                    }
                    else {
                        uVar3 = 0;
                    }
                    iVar11 = iVar11 + uVar3;
                }
                else {
                    iVar4 = (iVar4 + -0x6A1D58) / 0x68;
                    iVar2 = func_00338410(iVar4);
                    iVar10 = iVar10 + (u32)*(u16 *)(iVar2 + 0x1E);
                    iVar2 = func_00338410(iVar4);
                    if (*(char *)(iVar2 + 0x25) == 'G') {
                        iVar4 = PS2_ADDR(func_00338410(iVar4));
                        uVar3 = (u32)*(u16 *)((u8 *)PS2_PTR(iVar4) + 0x1A);
                    }
                    else {
                        uVar3 = 0;
                    }
                    iVar9 = iVar9 + uVar3;
                }
            }
            else if (uVar8 < 8) {
                iVar4 = (iVar4 + -0x6A1D58) / 0x68;
                iVar2 = func_00338410(iVar4);
                iVar10 = iVar10 + (u32)*(u16 *)(iVar2 + 0x1E);
                iVar2 = func_00338410(iVar4);
                if (*(char *)(iVar2 + 0x25) == 'G') {
                    iVar4 = PS2_ADDR(func_00338410(iVar4));
                    uVar3 = (u32)*(u16 *)((u8 *)PS2_PTR(iVar4) + 0x1A);
                }
                else {
                    uVar3 = 0;
                }
                iVar9 = iVar9 + uVar3;
            }
            else {
                iVar4 = (iVar4 + -0x6A1D58) / 0x68;
                iVar2 = func_00338410(iVar4);
                iVar12 = iVar12 + (u32)*(u16 *)(iVar2 + 0x1E);
                iVar2 = func_00338410(iVar4);
                if (*(char *)(iVar2 + 0x25) == 'G') {
                    iVar4 = PS2_ADDR(func_00338410(iVar4));
                    uVar3 = (u32)*(u16 *)((u8 *)PS2_PTR(iVar4) + 0x1A);
                }
                else {
                    uVar3 = 0;
                }
                iVar11 = iVar11 + uVar3;
            }
        }
        uVar8 = uVar8 + 1;
    } while (uVar8 < 0x10);
    if (iVar12 < 1) {
        iVar12 = 0;
    }
    else {
        iVar12 = ((iVar12 - iVar11) * 100) / iVar12;
    }
    if (iVar10 < 1) {
        iVar10 = 0;
    }
    else {
        iVar10 = ((iVar10 - iVar9) * 100) / iVar10;
    }
    iVar9 = 6;
    lVar7 = func_0036BB80(uVar1);
    if (lVar7 == 0) {
        if ((iVar12 * 3 < iVar10) && (*(u32 *)(g_00669F70 + 0x2C) <= (int)((u32)(iVar13 * 3000) / 3))) {
            iVar9 = 0;
        }
        else if ((iVar12 < iVar10) || (*(u32 *)(g_00669F70 + 0x2C) < (int)((u32)(iVar13 * 6000) / 3))) {
            iVar9 = 1;
        }
        else {
            iVar9 = 2;
        }
    }
    else {
        lVar7 = func_0036BB80(uVar1);
        if (lVar7 == 1) {
            if ((iVar10 * 3 < iVar12) || (*(u32 *)(g_00669F70 + 0x2C) <= (int)((u32)(iVar13 * 3000) / 5))) {
                iVar9 = 5;
            }
            else if ((iVar12 < iVar10) || (iVar13 * 3000 >> 1 <= *(u32 *)(g_00669F70 + 0x2C))) {
                iVar9 = 3;
            }
            else {
                iVar9 = 4;
            }
        }
    }
    if (iVar9 == 10) {
        iVar9 = 0;
    }
    *(u32 *)(g_007B9624) = iVar9;
}

/* 0x0036C200, 0x2B0 bytes. */
void func_0036C200(void)
{
    int bVar1;
    int bVar6;
    int bVar7;
    u8 * iStack_10;
    int iStack_20;
    u8 * iVar12;
    int iVar3;
    u8 * iVar4;
    int iVar5;
    int * piVar2;
    u16 * puVar11;
    u32 uVar10;
    u32 uVar13;
    u32 uVar8;
    u32 uVar9;

    uVar13 = 0;
    iStack_10 = g_007B9620;
    iStack_20 = 0;
    do {
        uVar8 = 0;
        iVar12 = iStack_10;
        do {
            puVar11 = (u16 *)(iVar12 + 8);
            piVar2 = (int *)func_0033EF80(uVar8 + iStack_20);
            if ((piVar2[0x19] & 1U) == 0) {
                *puVar11 = 0;
                *(u16 *)(iVar12 + 10) = 0;
                *(u16 *)(iVar12 + 0xC) = 0;
                *(u8 *)(iVar12 + 0xE) = 0;
                *(u8 *)(iVar12 + 0xF) = 0;
                *(u8 *)(iVar12 + 0x10) = 0;
                *(u8 *)(iVar12 + 0x11) = 0;
                *(u8 *)(iVar12 + 0x12) = 0;
                *(u8 *)(iVar12 + 0x13) = 0;
                *(u32 *)(iVar12 + 0x14) = 0;
                uVar9 = 0;
                do {
                    *(u8 *)((int)puVar11 + uVar9 + 0x10) = 0;
                    uVar10 = uVar9 + 3;
                    *(u8 *)((int)puVar11 + uVar9 + 0x11) = 0;
                    *(u8 *)((int)puVar11 + uVar9 + 0x12) = 0;
                    uVar9 = uVar10;
                } while (uVar10 < 9);
                *(u8 *)(iVar12 + 0x21) = 0;
            }
            else {
                bVar6 = false;
                bVar7 = 1;
                uVar9 = *(u32 *)(*piVar2 + 0x80);
                bVar1 = false;
                if (((uVar9 & 1) != 0) && ((uVar9 & 0x8C40002) == 0)) {
                    bVar1 = true;
                }
                if ((bVar1) && ((uVar9 & 4) == 0)) {
                    bVar6 = true;
                }
                if (bVar6) {
                    bVar7 = 3;
                }
                iVar5 = (int)(piVar2 + -0x1A8756) / 0x68;
                iVar3 = PS2_ADDR(func_00338410(iVar5));
                if (*(char *)((u8 *)PS2_PTR(iVar3) + 0x25) != 'G') {
                    bVar7 = bVar7 | 4;
                }
                if (uVar13 != *(u8 *)(*piVar2 + 0x79)) {
                    bVar7 = bVar7 | 8;
                }
                iVar3 = (int)(piVar2 + -0x1A8756) / 0x68;
                iVar4 = func_00338410(iVar3);
                *puVar11 = *(u16 *)(iVar4 + 0x1A);
                iVar3 = PS2_ADDR(func_00338410(iVar3));
                *(u16 *)(iVar12 + 10) = *(u16 *)((u8 *)PS2_PTR(iVar3) + 0x1E);
                *(u16 *)(iVar12 + 0xC) = 0;
                *(u8 *)(iVar12 + 0xE) = bVar7;
                uVar9 = 0;
                do {
                    iVar3 = PS2_ADDR(func_00338410(iVar5));
                    uVar10 = uVar9 + 1;
                    *(u8 *)((int)puVar11 + uVar9 + 7) = *(u8 *)((u8 *)PS2_PTR(iVar3) + uVar9 + 0xB);
                    uVar9 = uVar10;
                } while (uVar10 < 5);
                *(int *)(iVar12 + 0x14) = piVar2[0x15];
                uVar9 = 0;
                do {
                    iVar3 = PS2_ADDR(func_00338410(iVar5));
                    uVar10 = uVar9 + 1;
                    *(u8 *)((int)puVar11 + uVar9 + 0x10) = *(u8 *)((u8 *)PS2_PTR(iVar3) + uVar9 + 0x10);
                    uVar9 = uVar10;
                } while (uVar10 < 9);
                iVar5 = PS2_ADDR(func_00338410(iVar5));
                *(u8 *)(iVar12 + 0x21) = *(u8 *)((u8 *)PS2_PTR(iVar5) + 0x19);
            }
            uVar8 = uVar8 + 1;
            iVar12 = iVar12 + 0x1C;
        } while (uVar8 < 8);
        uVar13 = uVar13 + 1;
        iStack_10 = iStack_10 + 0xE0;
        iStack_20 = iStack_20 + 8;
    } while (uVar13 < 2);
}

/* 0x0036E8D0, 0x188 bytes. */
void func_0036E8D0(int param_1)
{
    int bVar6;
    int iVar1;
    long long lVar3;
    long long lVar5;
    int * piVar9;
    u32 uVar10;
    unsigned long long uVar2;
    unsigned long long uVar4;
    int uVar7;
    unsigned long long uVar8;

    uVar2 = func_0034EDB0((u8 *)PS2_PTR(param_1));
    if ((uVar2 < 2) && (lVar3 = func_0034EE60((u8 *)PS2_PTR(param_1)), lVar3 == 0)) {
        uVar8 = func_0035D5A0(uVar2);
        uVar4 = func_0034ED40((u8 *)PS2_PTR(param_1));
        lVar3 = PS2_ADDR(func_0033EFD0(uVar2, uVar4));
        lVar5 = PS2_ADDR(func_0033EFD0(uVar8, uVar4));
        if ((lVar3 != 0) &&
              (((piVar9 = (int *)lVar3, (piVar9[0x19] & 1U) != 0 && (lVar5 != 0)) &&
                ((*(u32 *)((int)lVar5 + 100) & 1) != 0)))) {
            uVar10 = 1;
            do {
                piVar9 = piVar9 + 1;
                iVar1 = *piVar9;
                if (iVar1 != 0) {
                    bVar6 = false;
                    if (((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x80) & 1) != 0) && ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x80) & 0x8C40002) == 0))
                    {
                        bVar6 = true;
                    }
                    if ((bVar6) &&
                          (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 0x10) % 100 < 0x1E
                          )) {
                        uVar7 = func_0033B970((u8 **)PS2_PTR(lVar5));
                        *(u8 *)((u8 *)PS2_PTR(iVar1) + 0x7F) = uVar7;
                        func_001EE750(iVar1, (char)uVar8);
                    }
                }
                uVar10 = uVar10 + 1;
            } while (uVar10 < 0xD);
        }
    }
}

/* 0x00393680, 0x6AC bytes. */
void func_00393680(void)
{
    u8 * iVar1;
    int iVar2;
    long long lVar7;
    int sVar4;
    int sVar5;
    int sVar6;
    int uVar3;

    iVar1 = func_00391250();
    sVar5 = *(short *)(iVar1 + 0x144);
    if ((long long)(*(char *)g_007BA83D) << 0x3F < 0) {
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar3 = 0;
        }
        else {
            uVar3 = *(u16 *)(g_0050074C + 0x2);
        }
        if ((uVar3 & 0x8000) == 0) {
            if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                uVar3 = 0;
            }
            else {
                uVar3 = *(u16 *)(g_0050074C + 0x2);
            }
            if ((uVar3 & 0x2000) == 0) {
                if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                    uVar3 = 0;
                }
                else {
                    uVar3 = *(u16 *)g_0050074C;
                }
                if ((uVar3 & 0x1000) == 0) {
                    if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                        uVar3 = 0;
                    }
                    else {
                        uVar3 = *(u16 *)g_0050074C;
                    }
                    if ((uVar3 & 0x4000) == 0) {
                        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                            uVar3 = 0;
                        }
                        else {
                            uVar3 = *(u16 *)(g_0050074C + 0x2);
                        }
                        if ((uVar3 & 0x1000) == 0) {
                            if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                                uVar3 = 0;
                            }
                            else {
                                uVar3 = *(u16 *)(g_0050074C + 0x2);
                            }
                            if ((uVar3 & 0x4000) == 0) {
                                if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                                    uVar3 = 0;
                                }
                                else {
                                    uVar3 = *(u16 *)g_0050074C;
                                }
                                if ((uVar3 & 0x40) == 0) {
                                    if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                                        uVar3 = 0;
                                    }
                                    else {
                                        uVar3 = *(u16 *)g_0050074C;
                                    }
                                    if ((uVar3 & 0x10) != 0) {
                                        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                                        *(u32 *)(iVar1 + 0x150) = 0;
                                    }
                                }
                                else {
                                    *(u32 *)(iVar1 + 0x94) =
                                              *(u32 *)
                                                (((int)*(short *)(iVar1 + 0x14A) + (int)*(short *)(iVar1 + 0x148)) * 4 +
                                                  iVar1 + 0x38);
                                    func_00391FA0();
                                    func_00391F00();
                                    lVar7 = func_00391C60(*(u32 *)(iVar1 + 0x94));
                                    if (lVar7 == 0) {
                                        *(u32 *)(iVar1 + 4) = 2;
                                    }
                                    else {
                                        *(u32 *)(iVar1 + 4) = 1;
                                        func_00391EB0();
                                        func_003E7470(*(u32 *)(iVar1 + 0x94));
                                    }
                                    func_00391CC0();
                                    func_00391B10(*(u32 *)(iVar1 + 0x94));
                                    func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                                    func_003E9750(1);
                                    func_003E8820(*(u32 *)(iVar1 + 0x94));
                                }
                            }
                            else if ((int)*(short *)(iVar1 + 0x14A) + (int)*(short *)(iVar1 + 0x148) < sVar5 + -1)
                            {
                                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                                sVar6 = *(short *)(iVar1 + 0x148) + 1;
                                *(short *)(iVar1 + 0x148) = sVar6;
                                if (((long long)*(short *)(iVar1 + 0x146) <= (long long)sVar6) || ((long long)sVar5 <= (long long)sVar6)
                                      ) {
                                    if ((long long)((int)*(short *)(iVar1 + 0x14A) + (int)sVar6) < (long long)sVar5) {
                                        *(short *)(iVar1 + 0x148) = *(short *)(iVar1 + 0x148) + -1;
                                        *(short *)(iVar1 + 0x14A) = *(short *)(iVar1 + 0x14A) + 1;
                                    }
                                    else {
                                        *(u16 *)(iVar1 + 0x148) = 0;
                                        *(u16 *)(iVar1 + 0x14A) = 0;
                                    }
                                }
                            }
                        }
                        else if (0 < (int)*(short *)(iVar1 + 0x148) + (int)*(short *)(iVar1 + 0x14A)) {
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                            sVar6 = *(short *)(iVar1 + 0x148);
                            sVar4 = sVar6 + -1;
                            *(short *)(iVar1 + 0x148) = sVar4;
                            if (sVar4 < 0) {
                                if (*(short *)(iVar1 + 0x14A) < 1) {
                                    sVar6 = *(short *)(iVar1 + 0x146);
                                    if ((int)sVar5 / (int)sVar6 < 1) {
                                        *(short *)(iVar1 + 0x148) = sVar5 % sVar6 + -1;
                                        *(u16 *)(iVar1 + 0x14A) = 0;
                                    }
                                    else {
                                        *(short *)(iVar1 + 0x148) = sVar6 + -1;
                                        *(short *)(iVar1 + 0x14A) = sVar5 - *(short *)(iVar1 + 0x146);
                                    }
                                }
                                else {
                                    *(short *)(iVar1 + 0x148) = sVar6;
                                    *(short *)(iVar1 + 0x14A) = *(short *)(iVar1 + 0x14A) + -1;
                                }
                            }
                        }
                    }
                    else {
                        lVar7 = (long long)sVar5;
                        if (1 < lVar7) {
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        }
                        sVar5 = *(short *)(iVar1 + 0x148) + 1;
                        *(short *)(iVar1 + 0x148) = sVar5;
                        if (((long long)*(short *)(iVar1 + 0x146) <= (long long)sVar5) || (lVar7 <= sVar5)) {
                            if ((int)*(short *)(iVar1 + 0x14A) + (int)sVar5 < lVar7) {
                                *(short *)(iVar1 + 0x148) = *(short *)(iVar1 + 0x148) + -1;
                                *(short *)(iVar1 + 0x14A) = *(short *)(iVar1 + 0x14A) + 1;
                            }
                            else {
                                *(u16 *)(iVar1 + 0x148) = 0;
                                *(u16 *)(iVar1 + 0x14A) = 0;
                            }
                        }
                    }
                }
                else {
                    if (1 < sVar5) {
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    }
                    sVar6 = *(short *)(iVar1 + 0x148);
                    sVar4 = sVar6 + -1;
                    *(short *)(iVar1 + 0x148) = sVar4;
                    if (sVar4 < 0) {
                        if (*(short *)(iVar1 + 0x14A) < 1) {
                            sVar6 = *(short *)(iVar1 + 0x146);
                            if ((int)sVar5 / (int)sVar6 < 1) {
                                *(short *)(iVar1 + 0x148) = sVar5 % sVar6 + -1;
                                *(u16 *)(iVar1 + 0x14A) = 0;
                            }
                            else {
                                *(short *)(iVar1 + 0x148) = sVar6 + -1;
                                *(short *)(iVar1 + 0x14A) = sVar5 - *(short *)(iVar1 + 0x146);
                            }
                        }
                        else {
                            *(short *)(iVar1 + 0x148) = sVar6;
                            *(short *)(iVar1 + 0x14A) = *(short *)(iVar1 + 0x14A) + -1;
                        }
                    }
                }
            }
            else if (*(int *)(iVar1 + 0x34) == 0) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                iVar2 = *(int *)(iVar1 + 8) + 1;
                *(int *)(iVar1 + 8) = iVar2;
                if (4 < iVar2) {
                    *(u32 *)(iVar1 + 8) = 0;
                }
                func_003914C0();
                *(u16 *)(iVar1 + 0x148) = 0;
                *(u16 *)(iVar1 + 0x14A) = 0;
            }
        }
        else if (*(int *)(iVar1 + 0x34) == 0) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            iVar2 = *(int *)(iVar1 + 8) + -1;
            *(int *)(iVar1 + 8) = iVar2;
            if (iVar2 < 0) {
                *(u32 *)(iVar1 + 8) = 4;
            }
            func_003914C0();
            *(u16 *)(iVar1 + 0x148) = 0;
            *(u16 *)(iVar1 + 0x14A) = 0;
        }
    }
}

/* 0x0039E020, 0x14C bytes. */
void func_0039E020(void)
{
    int aiStack_20[8];
    int bVar1;
    int iVar2;
    int iVar5;
    int iVar6;
    int iVar7;
    unsigned long long uVar3;
    u32 uVar4;

    iVar2 = PS2_ADDR(func_002FC2C0());
    iVar2 = *(int *)((u8 *)PS2_PTR(iVar2) + 0x6AC);
    bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x26);
    uVar4 = (u32)bVar1;
    func_003DC180(0x10, 0, aiStack_20);
    func_002C7310(aiStack_20[0], 0x58, 0, 0xA6, (u32)bVar1 * 0x18 + 0x10, 0x80, 1);
    iVar7 = 0;
    iVar6 = aiStack_20[0] + 8;
    if (uVar4 != 0) {
        iVar5 = 0x60;
        do {
            uVar3 = PS2_ADDR(func_0030D7D0());
            func_00381FF0(uVar3, iVar6, iVar5, *(u8 *)((u8 *)PS2_PTR(iVar2) + iVar7 + 0x20),
                                      *(int *)((u8 *)PS2_PTR(iVar2) + 0xC) == iVar7);
            iVar7 = iVar7 + 1;
            iVar5 = iVar5 + 0x18;
        } while (iVar7 < (int)uVar4);
    }
    func_003DC180(0x11, 0, aiStack_20);
    uVar3 = PS2_ADDR(func_0030D7D0());
    func_0037E9F0(uVar3, *(u8 *)(*(int *)((u8 *)PS2_PTR(iVar2) + 0xC) + iVar2 + 0x20), aiStack_20[0], 0x68, 0x80, 1
                            );
    if (uVar4 == 1) {
        iVar2 = 0x10F;
    }
    else {
        iVar2 = 0x14A;
    }
    func_001A7DC0((char *)(((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar2]))), 0x80, 1);
}

/* 0x0039E170, 0xD4 bytes. */
void func_0039E170(void)
{
    u32 auStack_20[8];
    int cVar1;
    int iVar2;
    unsigned long long uVar3;

    iVar2 = PS2_ADDR(func_002FC2C0());
    iVar2 = *(int *)((u8 *)PS2_PTR(iVar2) + 0x6AC);
    cVar1 = *(char *)((u8 *)PS2_PTR(iVar2) + 0x26);
    func_003DC180(0x10, 0, auStack_20);
    uVar3 = PS2_ADDR(func_0030D7D0());
    func_003821E0(uVar3, *(u32 *)((u8 *)PS2_PTR(iVar2) + 0xC), auStack_20[0], 0x50, iVar2 + 0x20, cVar1);
    func_003DC180(0x11, 0, auStack_20);
    uVar3 = PS2_ADDR(func_0030D7D0());
    func_0037E950(uVar3, *(u8 *)(*(int *)((u8 *)PS2_PTR(iVar2) + 0xC) + iVar2 + 0x20), auStack_20[0], 0x68, 0x80);
    if (cVar1 == 1) {
        iVar2 = 0x10F;
    }
    else {
        iVar2 = 0x14A;
    }
    func_001A7DC0((char *)(((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar2]))), 0x80, 1);
}

/* 0x0039E250, 0x9C bytes. */
void func_0039E250(void)
{
    int iVar1;
    long long lVar2;

    iVar1 = PS2_ADDR(func_002FC2C0());
    iVar1 = *(int *)(*(int *)((u8 *)PS2_PTR(iVar1) + 0x6AC) + 4);
    if (iVar1 == 1) {
        func_003E0F30();
        lVar2 = func_003E17B0();
        if (lVar2 < 2) {
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C55C))), 0x80, 1);
        }
        else {
            func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C7DC))), 0x80, 1);
        }
    }
    else if (iVar1 == 0) {
        func_00373B60();
    }
}

/* 0x003A9C20, 0xCF4 bytes. */
int func_003A9C20(void)
{
    int iStack_10;
    int iStack_20;
    int iStack_50;
    int iVar1;
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar2;
    int iVar4;
    int iVar9;
    long long lVar6;
    long long lVar7;
    u32 uStack_30;
    u32 uVar3;
    u32 uVar5;
    unsigned long long uVar8;

    iVar1 = PS2_ADDR(func_0021A630());
    iVar2 = func_0036B8C0(0);
    lVar6 = func_0036B8C0(1);
    iVar9 = 0;
    iVar13 = 0;
    do {
        uVar3 = func_0036B9B0(iVar9);
        iVar9 = iVar9 + 1;
        iVar13 = iVar13 + (uVar3 & 0xFF);
    } while (iVar9 < 4);
    iVar9 = 0;
    iVar12 = 0;
    if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
        do {
            iVar10 = 0;
            do {
                iVar4 = func_0035F6B0(iVar9, iVar10);
                iVar12 = iVar12 + iVar4;
                iVar10 = iVar10 + 1;
            } while (iVar10 < 5);
            iVar9 = iVar9 + 1;
        } while (iVar9 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
    }
    if ((iVar13 < 1) && (iVar12 < 1)) {
        iVar1 = 0;
    }
    else {
        iVar12 = 0;
        iVar13 = 0;
        iVar9 = 0;
        do {
            lVar7 = func_003637D0(0, iVar12);
            if ((lVar7 == 0) && (lVar7 = func_00362160(0, iVar12), lVar7 != 0x252)) {
                iVar10 = 0;
                do {
                    lVar7 = func_00362160(0, iVar12);
                    if ((lVar7 != 0x252) && (lVar7 = func_0036B940(0, iVar12), lVar7 == 0)) {
                        uVar3 = func_0036B4D0(0, iVar12, iVar10);
                        iVar9 = iVar9 + (uVar3 & 0xFF);
                    }
                    iVar10 = iVar10 + 1;
                } while (iVar10 < 9);
            }
            iVar12 = iVar12 + 1;
        } while (iVar12 < 8);
        if ((lVar6 < 8) && (lVar7 = func_0036B940(1, lVar6), lVar7 != 0)) {
            iVar12 = 0;
            do {
                uVar3 = func_0036B4D0(1, lVar6, iVar12);
                iVar12 = iVar12 + 1;
                iVar9 = iVar9 + (uVar3 & 0xFF);
            } while (iVar12 < 9);
        }
        iVar12 = 0;
        if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
            do {
                iVar10 = func_0035F6B0(iVar12, 1);
                iVar13 = iVar13 + iVar10;
                iVar12 = iVar12 + 1;
            } while (iVar12 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        uVar3 = func_0036B9B0(0);
        uVar3 = uVar3 & 0xFF;
        if (iVar13 < 1) {
            iVar12 = 0;
        }
        else {
            iVar12 = iVar13;
        }
        if (iVar12 < 0x6FA) {
            if (iVar13 < 1) {
                iVar13 = 0;
            }
        }
        else {
            iVar13 = 0x6F9;
        }
        uVar5 = uVar3;
        if (uVar3 == 0) {
            uVar5 = 0;
        }
        if (uVar5 < 0x100) {
            if (uVar3 == 0) {
                uVar3 = 0;
            }
        }
        else {
            uVar3 = 0xFF;
        }
        if (iVar9 < 1) {
            iVar12 = 0;
        }
        else {
            iVar12 = iVar9;
        }
        if (iVar12 < 0x13) {
            if (iVar9 < 1) {
                iVar9 = 0;
            }
        }
        else {
            iVar9 = 0x12;
        }
        if (((int)(iVar13 + uVar3) < 1) || (iVar9 < (int)(iVar13 + uVar3))) {
            iStack_10 = (iVar9 + 1) * 0x32;
            if (iStack_10 < 0x385) {
                if (iStack_10 < 1) {
                    iStack_10 = 0;
                }
            }
            else {
                iStack_10 = 900;
            }
        }
        else {
            iStack_10 = (iVar9 + 2) * 100;
            if (iStack_10 < 0x7D1) {
                if (iStack_10 < 1) {
                    iStack_10 = 0;
                }
            }
            else {
                iStack_10 = 2000;
            }
        }
        iVar9 = 0;
        iVar12 = 0;
        iVar13 = 0;
        do {
            lVar7 = func_003637D0(0, iVar9);
            if (((lVar7 == 0) && (lVar7 = func_00362160(0, iVar9), lVar7 != 0x252)) &&
                  (lVar7 = func_0036B940(0, iVar9), lVar7 == 0)) {
                uVar3 = func_0036B6C0(0, iVar9);
                iVar13 = iVar13 + (uVar3 & 0xFF);
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 8);
        if ((lVar6 < 8) && (lVar7 = func_0036B940(1, lVar6), lVar7 != 0)) {
            uVar3 = func_0036B6C0(1, lVar6);
            iVar13 = iVar13 + (uVar3 & 0xFF);
        }
        iVar9 = 0;
        if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
            do {
                iVar10 = func_0035F6B0(iVar9, 0);
                iVar12 = iVar12 + iVar10;
                iVar9 = iVar9 + 1;
            } while (iVar9 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        uVar3 = func_0036B9B0(0);
        uVar3 = uVar3 & 0xFF;
        if (iVar12 < 1) {
            iVar9 = 0;
        }
        else {
            iVar9 = iVar12;
        }
        if (iVar9 < 0x6FA) {
            if (iVar12 < 1) {
                iVar12 = 0;
            }
        }
        else {
            iVar12 = 0x6F9;
        }
        uVar5 = uVar3;
        if (uVar3 == 0) {
            uVar5 = 0;
        }
        if (uVar5 < 0x100) {
            if (uVar3 == 0) {
                uVar3 = 0;
            }
        }
        else {
            uVar3 = 0xFF;
        }
        if (iVar13 < 1) {
            iVar9 = 0;
        }
        else {
            iVar9 = iVar13;
        }
        if (iVar9 < 0x13) {
            if (iVar13 < 1) {
                iVar13 = 0;
            }
        }
        else {
            iVar13 = 0x12;
        }
        if (((int)(iVar12 + uVar3) < 1) || (iVar13 < (int)(iVar12 + uVar3))) {
            iStack_20 = (iVar13 + 1) * 0x32;
            if (iStack_20 < 0x385) {
                if (iStack_20 < 1) {
                    iStack_20 = 0;
                }
            }
            else {
                iStack_20 = 900;
            }
        }
        else {
            iStack_20 = (iVar13 + 2) * 100;
            if (iStack_20 < 0x7D1) {
                if (iStack_20 < 1) {
                    iStack_20 = 0;
                }
            }
            else {
                iStack_20 = 2000;
            }
        }
        iVar13 = 0;
        iVar9 = 0;
        do {
            lVar7 = func_003637D0(0, iVar9);
            if (lVar7 == 0) {
                func_00362160(0, iVar9);
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 8);
        iVar9 = 0;
        if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
            do {
                iVar12 = 0;
                do {
                    iVar10 = func_0035F6B0(iVar9, iVar12);
                    iVar13 = iVar13 + iVar10;
                    iVar12 = iVar12 + 1;
                } while (iVar12 < 5);
                iVar9 = iVar9 + 1;
            } while (iVar9 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        if (iVar13 < 1) {
            iVar9 = 0;
        }
        else {
            iVar9 = iVar13;
        }
        if (iVar9 < 0x65) {
            if (iVar13 < 1) {
                iVar13 = 0;
            }
        }
        else {
            iVar13 = 100;
        }
        iStack_50 = 0;
        iVar9 = 0;
        do {
            uVar3 = func_0036B9B0(iVar9);
            iVar9 = iVar9 + 1;
            iStack_50 = iStack_50 + (uVar3 & 0xFF);
        } while (iVar9 < 4);
        if (iStack_50 < 0) {
            iStack_50 = iStack_50 + 3;
        }
        iStack_50 = iStack_50 >> 2;
        if (iStack_50 < 0x65) {
            if (iStack_50 < 1) {
                iStack_50 = 0;
            }
        }
        else {
            iStack_50 = 100;
        }
        iVar9 = 0;
        uStack_30 = 0;
        iVar12 = 0;
        iVar10 = 0;
        if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
            do {
                iVar4 = 0;
                do {
                    uVar8 = func_00362320(iVar9);
                    uVar3 = func_0036B4D0(0, uVar8, iVar4);
                    iVar4 = iVar4 + 1;
                    iVar12 = iVar12 + (uVar3 & 0xFF);
                } while (iVar4 < 9);
                uVar8 = func_00362320(iVar9);
                uVar3 = func_0036B6C0(0, uVar8);
                iVar9 = iVar9 + 1;
                iVar10 = iVar10 + (uVar3 & 0xFF);
            } while (iVar9 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        iVar9 = 0;
        iVar4 = 0;
        iVar14 = 0;
        do {
            lVar7 = func_003637D0(0, iVar9);
            if (((lVar7 == 0) && (lVar7 = func_00362160(0, iVar9), lVar7 != 0x252)) &&
                  (lVar7 = func_0036B940(0, iVar9), lVar7 == 0)) {
                iVar11 = 0;
                do {
                    uVar3 = func_0036B4D0(0, iVar9, iVar11);
                    iVar11 = iVar11 + 1;
                    iVar4 = iVar4 + (uVar3 & 0xFF);
                } while (iVar11 < 9);
                uVar3 = func_0036B6C0(0, iVar9);
                iVar14 = iVar14 + (uVar3 & 0xFF);
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 8);
        if ((lVar6 < 8) && (lVar7 = func_0036B940(1, lVar6), lVar7 != 0)) {
            iVar9 = 0;
            do {
                uVar3 = func_0036B4D0(1, lVar6, iVar9);
                iVar9 = iVar9 + 1;
                iVar4 = iVar4 + (uVar3 & 0xFF);
            } while (iVar9 < 9);
            uVar3 = func_0036B6C0(1, lVar6);
            iVar14 = iVar14 + (uVar3 & 0xFF);
        }
        if ((iVar12 == 0) && (iVar10 == 0)) {
            uStack_30 = 0x640;
        }
        if (iVar12 == 0) {
            uStack_30 = uStack_30 + 600;
        }
        if (iVar10 == 0) {
            uStack_30 = uStack_30 + 800;
        }
        if (iVar12 < iVar4) {
            uStack_30 = uStack_30 + 300;
        }
        if (iVar10 < iVar14) {
            uStack_30 = uStack_30 + 400;
        }
        iVar9 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668);
        iVar12 = 0;
        if (0 < iVar9) {
            do {
                uVar3 = *(u32 *)(iVar12 * 0x48 + 0x669DEC);
                if (uVar3 == 0) {
                    uVar5 = 0;
                }
                else {
                    uVar5 = uVar3;
                }
                if (uVar5 < 10000) {
                    if (uVar3 == 0) {
                        uVar3 = 0;
                    }
                }
                else {
                    uVar3 = 9999;
                }
            } while ((uVar3 < 0x33) && (iVar12 = iVar12 + 1, iVar12 < iVar9));
        }
        if (iVar12 == iVar9) {
            uStack_30 = uStack_30 + 500;
        }
        if (uStack_30 < 0x1069) {
            if (uStack_30 == 0) {
                uStack_30 = 0;
            }
        }
        else {
            uStack_30 = 0x1068;
        }
        iVar12 = 0;
        iVar10 = 0;
        if (0 < iVar9) {
            do {
                iVar9 = func_0035F6B0(iVar12, 2);
                iVar10 = iVar10 + iVar9;
                iVar12 = iVar12 + 1;
            } while (iVar12 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        uVar3 = func_0036B9B0(1);
        iVar12 = 0;
        iVar9 = 0;
        do {
            lVar6 = func_0036B940(1, iVar12);
            if ((lVar6 == 0) && (lVar6 = func_00362160(1, iVar12), lVar6 != 0x252)) {
                uVar5 = func_0036B6C0(1, iVar12);
                iVar9 = iVar9 + (uVar5 & 0xFF);
            }
            iVar12 = iVar12 + 1;
        } while (iVar12 < 8);
        if ((iVar2 < 8) && (lVar6 = func_0036B940(0, iVar2), lVar6 != 0)) {
            uVar5 = func_0036B6C0(0, iVar2);
            iVar9 = iVar9 + (uVar5 & 0xFF);
        }
        if (((int)(iVar10 + (uVar3 & 0xFF)) < 5) || (iVar9 != 0)) {
            iVar9 = 0;
        }
        else {
            iVar9 = 200;
        }
        iVar10 = 0;
        iVar12 = 0;
        if (0 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668)) {
            do {
                iVar4 = func_0035F6B0(iVar10, 3);
                iVar12 = iVar12 + iVar4;
                iVar10 = iVar10 + 1;
            } while (iVar10 < *(int *)((u8 *)PS2_PTR(iVar1) + 0x1668));
        }
        iVar10 = 0;
        iVar1 = 0;
        do {
            lVar6 = func_00362160(1, iVar10);
            if ((lVar6 != 0x252) && (lVar6 = func_0036B940(1, iVar10), lVar6 == 0)) {
                iVar4 = 0;
                do {
                    uVar3 = func_0036B4D0(1, iVar10, iVar4);
                    iVar4 = iVar4 + 1;
                    iVar1 = iVar1 + (uVar3 & 0xFF);
                } while (iVar4 < 9);
            }
            iVar10 = iVar10 + 1;
        } while (iVar10 < 8);
        if ((iVar2 < 8) && (lVar6 = func_0036B940(0, iVar2), lVar6 != 0)) {
            iVar10 = 0;
            do {
                uVar3 = func_0036B4D0(0, iVar2, iVar10);
                iVar10 = iVar10 + 1;
                iVar1 = iVar1 + (uVar3 & 0xFF);
            } while (iVar10 < 9);
        }
        if ((iVar12 < 2) || (iVar1 != 0)) {
            iVar1 = 0;
        }
        else {
            iVar1 = 200;
        }
        iVar1 = iVar1 + iVar9 + uStack_30 + iStack_50 + iVar13 + iStack_10 + iStack_20;
        if (iVar1 < 1) {
            iVar2 = 0;
        }
        else {
            iVar2 = iVar1;
        }
        if (iVar2 < 0x20D1) {
            if (iVar1 < 1) {
                iVar1 = 0;
            }
        }
        else {
            iVar1 = 0x20D0;
        }
    }
    return iVar1;
}

/* 0x003AC220, 0x120 bytes. */
void func_003AC220(void)
{
    int aiStack_60[24];
    u8 * iVar1;
    u8 * iVar3;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    u8 * iVar7;
    int iVar9;
    int * piVar2;
    int * piVar8;

    iVar1 = func_0021A630();
    iVar9 = 0;
    if (0 < *(int *)(iVar1 + 0x1668)) {
        piVar8 = aiStack_60;
        iVar7 = iVar1;
        iVar6 = iVar1;
        do {
            iVar4 = 0;
            *piVar8 = 0x10;
            *(u8 *)(piVar8 + 1) = 0;
            piVar8[2] = 0x10;
            *(u8 *)(piVar8 + 3) = 0;
            piVar8[4] = 0x10;
            *(u8 *)(piVar8 + 5) = 0;
            piVar8[6] = 0x10;
            *(u8 *)(piVar8 + 7) = 0;
            piVar8[8] = 0x10;
            *(u8 *)(piVar8 + 9) = 0;
            piVar8[10] = 0x10;
            *(u8 *)(piVar8 + 0xB) = 0;
            iVar5 = 0;
            if (0 < *(int *)(iVar6 + 0x167C)) {
                piVar2 = piVar8;
                iVar3 = iVar7;
                do {
                    if (*(int *)(iVar3 + 0x16EC) < 0x10) {
                        *piVar2 = *(int *)(iVar3 + 0x16EC);
                        iVar4 = iVar4 + 1;
                        *(u8 *)(piVar2 + 1) = *(u8 *)(iVar3 + 0x16F0);
                        piVar2 = piVar2 + 2;
                    }
                    iVar5 = iVar5 + 1;
                    iVar3 = iVar3 + 8;
                } while (iVar5 < *(int *)(iVar6 + 0x167C));
            }
            *(int *)(iVar6 + 0x167C) = iVar4;
            *(int *)(iVar6 + 0x16E4) = iVar4;
            func_00118AC0((u32 *)(iVar7 + 0x16EC), (u8 *)(piVar8), 0x30);
            iVar9 = iVar9 + 1;
            piVar8 = piVar8 + 0xC;
            iVar7 = iVar7 + 0x30;
            iVar6 = iVar6 + 4;
        } while (iVar9 < *(int *)(iVar1 + 0x1668));
    }
}

/* 0x003AF670, 0x254 bytes. */
void func_003AF670(void)
{
    int iVar3;
    long long lVar5;
    long long lVar6;
    u32 uVar1;
    u32 uVar2;
    unsigned long long uVar4;

    uVar4 = func_00327D50();
    uVar2 = *(u32 *)g_007BAE70;
    uVar1 = *(u32 *)(*(u32 *)(g_007BAE70 + 0xC) * 4 + 0x7BAE94);
    iVar3 = PS2_ADDR(func_00329860());
    if (*(u32 *)(g_007BAE70 + 0x8) == 2) {
        func_0030E390(4, uVar1, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0, 0);
        if ((long long)*(short *)((u8 *)PS2_PTR(iVar3) + 0x18) < 0xFFFF) {
            *(short *)((u8 *)PS2_PTR(iVar3) + 0x18) = *(short *)((u8 *)PS2_PTR(iVar3) + 0x18) + 1;
        }
    }
    else if (*(u32 *)(g_007BAE70 + 0x8) == 1) {
        func_003097D0(uVar1);
    }
    else if (*(u32 *)(g_007BAE70 + 0x8) == 0) {
        func_002F9130(uVar4, *(u32 *)(g_007BAE70 + 0x1C) / 10);
        func_0039F960();
        func_0032E910(uVar1);
        lVar5 = func_00330650(6);
        if (lVar5 != -1) {
            func_0030E390(5, uVar1, lVar5, 0xFFFFFFFFFFFFFFFF, 0, 0);
        }
        lVar5 = func_00309A10(uVar1, uVar2);
        if (lVar5 == 0) {
            *(u32 *)(g_007BAE70 + 0x20) = 1;
        }
        iVar3 = *(u32 *)(g_007BAE70 + 0x14) * 4;
        *(u32 *)(g_007BAE70 + 0x14) = *(u32 *)(g_007BAE70 + 0x14) + 1;
        *(u32 *)(g_007BAEAC + iVar3) = uVar1;
        *(u32 *)(g_007BAE70 + 0x18) = *(u32 *)(g_007BAE70 + 0x18) + -1;
    }
    *(u32 *)(g_007BAE70 + 0x8) = 4;
    func_003DB480(0xD, 2);
    *(u32 *)(g_007BAE70 + 0xC) = *(u32 *)(g_007BAE70 + 0xC) + 1;
    if (*(u32 *)(g_007BAE70 + 0xC) < *(u32 *)(g_007BAE70 + 0x10)) {
        func_003AE8E0(2);
        return;
    }
    *(u32 *)(g_007BAE70 + 0xC) = 0;
    if (*(u32 *)(g_007BAE70 + 0x14) == 0) {
LAB_003af890:
        func_003AE8E0(8);
    }
    else {
        if (*(u32 *)(g_007BAE70 + 0x20) == 0) {
            lVar5 = func_00327E50();
            lVar6 = func_002FB430(uVar4);
            if (lVar6 <= lVar5) goto LAB_003af890;
        }
        func_003AE8E0(5);
    }
}

/* 0x003DFAB0, 0x2CC bytes. */
int func_003DFAB0(u8 *param_1, int param_2)
{
    int bVar1;
    u8 * iVar3;
    int iVar4;
    int uVar2;

    param_2 = param_2 * 0x88;
    if ((*(u8 *)(g_00500764 + param_2) & 1) == 0) {
        bVar1 = false;
    }
    else {
        bVar1 = (*(u8 *)(g_00500765 + param_2) & 1) == 1;
    }
    if (bVar1) {
        uVar2 = *(u16 *)(g_0050074C + param_2);
    }
    else {
        uVar2 = 0;
    }
    if (*(int *)(param_1 + 0x30) == 0) {
        if (*(int *)(param_1 + 0x34) < *(int *)(param_1 + 0x38)) {
            if ((*(u8 *)(param_1 + 0x3C) & 1) == 0) {
                func_0023AD10(3, 0, 0x2CDC, 0x2CDC, 0x1000);
            }
            iVar4 = *(int *)(param_1 + 0x34) + 8;
            if (*(int *)(param_1 + 0x38) < iVar4) {
                *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x38);
            }
            else {
                *(int *)(param_1 + 0x34) = iVar4;
            }
            *(u8 *)(param_1 + 0x3C) = *(char *)(param_1 + 0x3C) + 1U & 1;
        }
        else if (*(int *)(param_1 + 0x40) == 0) {
            *(u32 *)(param_1 + 0x30) = 2;
        }
        else {
            func_0023AD10(7, 0, 0x2CDC, 0x2CDC, 0x1000);
            *(u32 *)(param_1 + 0x30) = 1;
            iVar4 = 0;
            if (0 < *(int *)(param_1 + 0x54)) {
                iVar3 = param_1;
                do {
                    func_002C5AC0(1.0f, iVar3, 0x80, 0x80, 0, 0);
                    iVar4 = iVar4 + 1;
                    iVar3 = iVar3 + 0x18;
                } while (iVar4 < *(int *)(param_1 + 0x54));
            }
        }
    }
    else if (*(int *)(param_1 + 0x30) == 1) {
        *(u8 *)(g_00772674) = 0x40;
        *(u8 *)(g_00772674 + 0x1) = 0x40;
        *(u8 *)(g_00772674 + 0x2) = 0;
        *(u32 *)(g_00772674 + 0x4) = 0;
        *(u32 *)(param_1 + 0x30) = 2;
    }
    if ((uVar2 & 0x40) != 0) {
        if (*(int *)(param_1 + 0x30) == 0) {
            *(u32 *)(param_1 + 0x34) = *(u32 *)(param_1 + 0x38);
            if (*(int *)(param_1 + 0x40) == 0) {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                *(u32 *)(param_1 + 0x30) = 2;
            }
            else {
                func_0023AD10(7, 0, 0x2CDC, 0x2CDC, 0x1000);
                *(u32 *)(param_1 + 0x30) = 1;
                iVar4 = 0;
                if (0 < *(int *)(param_1 + 0x54)) {
                    iVar3 = param_1;
                    do {
                        func_002C5AC0(1.0f, iVar3, 0x80, 0x80, 0, 0);
                        iVar4 = iVar4 + 1;
                        iVar3 = iVar3 + 0x18;
                    } while (iVar4 < *(int *)(param_1 + 0x54));
                    return 0;
                }
            }
        }
        else if (*(int *)(param_1 + 0x30) == 2) {
            return 1;
        }
    }
    return 0;
}

/* 0x003EC970, 0x2B0 bytes. */
void func_003EC970(void)
{
    u8 auStack_70[112];
    u8 auStack_e0[112];
    int iVar1;
    long long lVar6;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;

    iVar1 = PS2_ADDR(func_003EA000());
    uVar2 = func_003EA160();
    uVar3 = func_003EAB60(uVar2, (int *)(auStack_70));
    uVar4 = func_003EA0E0();
    uVar5 = func_003EAB60(uVar4, (int *)(auStack_e0));
    func_0030CF90(0, 0, *(u32 *)((u8 *)PS2_PTR(iVar1) + 8));
    func_003EA880(0, 1, (int *)(auStack_70), uVar3, 1000, 0x41D820, 9);
    func_003EA880(0, 2, (int *)(auStack_70), uVar3, 1000, 0x41D820, 9);
    func_003EA880(0, 3, (int *)(auStack_70), uVar3, 500, 0x41D820, 9);
    func_003EA880(0, 4, (int *)(auStack_70), uVar3, 500, 0x41D820, 9);
    func_003EA880(0, 5, (int *)(auStack_70), uVar3, 500, 0x41D820, 9);
    func_003EA880(0, 6, (int *)(auStack_70), uVar3, 1000, 0x41D820, 9);
    func_003EA880(0, 7, (int *)(auStack_70), uVar3, 500, 0x41D820, 9);
    func_0030CF90(1, 0, 0x10);
    func_0030CF90(1, 1, 0xE);
    func_0030CF90(1, 2, 0xF);
    func_003EA880(1, 3, (int *)(auStack_e0), uVar5, 500, 0x41D850, 6);
    func_003EA880(1, 4, (int *)(auStack_e0), uVar5, 500, 0x41D850, 6);
    func_003EA880(1, 5, (int *)(auStack_e0), uVar5, 500, 0x41D850, 6);
    func_003EA880(1, 6, (int *)(auStack_e0), uVar5, 1000, 0x41D850, 6);
    iVar1 = 0;
    do {
        lVar6 = func_003620E0(0, iVar1);
        if (lVar6 == 0xB5) {
            func_00362840(0, iVar1, 1);
        }
        iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
    uVar2 = func_002F8E50(uVar2);
    func_00362990(0, uVar2);
    uVar2 = func_002F8E50(uVar4);
    func_00362990(1, uVar2);
    func_003EAA50(0xD);
}

/* 0x003ED040, 0x2D0 bytes. */
void func_003ED040(void)
{
    u8 auStack_70[112];
    u8 auStack_e0[112];
    int iVar1;
    long long lVar6;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;

    iVar1 = PS2_ADDR(func_003EA000());
    uVar2 = func_003EA160();
    uVar3 = func_003EAB60(uVar2, (int *)(auStack_70));
    uVar4 = func_003EA0E0();
    uVar5 = func_003EAB60(uVar4, (int *)(auStack_e0));
    func_0030CF90(0, 0, *(u32 *)((u8 *)PS2_PTR(iVar1) + 8));
    func_003EA880(0, 1, (int *)(auStack_e0), uVar5, 1000, 0x41D890, 9);
    func_003EA880(0, 2, (int *)(auStack_e0), uVar5, 1000, 0x41D890, 9);
    func_003EA880(0, 3, (int *)(auStack_e0), uVar5, 500, 0x41D890, 9);
    func_003EA880(0, 4, (int *)(auStack_e0), uVar5, 500, 0x41D890, 9);
    func_003EA880(0, 5, (int *)(auStack_e0), uVar5, 500, 0x41D890, 9);
    func_003EA880(0, 6, (int *)(auStack_e0), uVar5, 1000, 0x41D890, 9);
    func_003EA880(0, 7, (int *)(auStack_e0), uVar5, 500, 0x41D890, 9);
    func_0030CF90(1, 0, 0x11);
    func_0030CF90(1, 1, 0x13);
    func_0030CF90(1, 2, 0xB5);
    func_003EA880(1, 3, (int *)(auStack_70), uVar3, 500, 0x41D870, 6);
    func_003EA880(1, 4, (int *)(auStack_70), uVar3, 500, 0x41D870, 6);
    func_003EA880(1, 5, (int *)(auStack_70), uVar3, 500, 0x41D870, 6);
    func_003EA880(1, 6, (int *)(auStack_70), uVar3, 1000, 0x41D870, 6);
    func_003EA880(1, 7, (int *)(auStack_70), uVar3, 500, 0x41D870, 6);
    iVar1 = 0;
    do {
        lVar6 = func_003620E0(1, iVar1);
        if (lVar6 == 0xB5) {
            func_00362840(1, iVar1, 1);
        }
        iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
    uVar3 = func_002F8E50(uVar4);
    func_00362990(0, uVar3);
    uVar2 = func_002F8E50(uVar2);
    func_00362990(1, uVar2);
    func_003EAA50(0xC);
}

/* 0x003F0630, 0x1CC bytes. */
void func_003F0630(int param_1, int param_2, int param_3)
{
    int iVar2;
    int iVar3;
    int iVar4;
    unsigned long long uVar1;

    uVar1 = PS2_ADDR(func_00105410());
    iVar2 = (int)uVar1;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x18) = 0x3F80000030000000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x20) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x28) = (long long)(0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    func_001054B0((u8 *)PS2_PTR(uVar1), param_3);
    func_002C7310(0xA8, 0x3C, 0, 0xA6, 0x116, 0x80, param_3);
    iVar4 = 0;
    iVar3 = 0x44;
    iVar2 = 0x42;
    do {
        if (iVar4 == param_2) {
            func_002C8500(0xB0, iVar3, 0, 0x96, 0x18, 0x80, param_3);
        }
        else {
            func_002C80A0(0xB0, iVar3, 0, 0x96, 0x18, 0x80, param_3);
        }
        func_001ABEA0((u8 *)PS2_PTR(param_1), 0x14B, 0xD7, iVar2, 0, 0x48, 0x18, 0, 0, 0x48, 0x18, 0x80, 1, 0);
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 0x18;
        iVar2 = iVar2 + 0x18;
    } while (iVar4 < 0xB);
}
