/*
 * gen11_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_00799A20[0x18];
extern u8 g_00799A38[0x18];
extern u8 g_00799A50[0x18];
extern u8 g_007A05A0[0x18];
extern u8 g_007BABE0[0x18];
extern u8 g_007BAC0C[0x18];
extern u8 g_007BFB20[0x18];
extern u8 g_007BFB3C[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"

#define true 1
#define false 0

extern u8 g_0040D630[0x4];
extern u8 g_0040E9E0[0x4];
extern u8 g_004114F0[0x4];
extern u8 g_00411540[0x4];
extern u8 g_004117B0[0x4];
extern u8 g_004118D0[0x4];
extern u8 g_00412040[0x4];
extern u8 g_004120D0[0x4];
extern u8 g_00412130[0x4];
extern u8 g_00412C60[0x4];
extern u8 g_00414F10[0x4];
extern u8 g_00414F80[0x4];
extern u8 g_004160A0[0x4];
extern u8 g_004174D0[0x104];
extern u8 g_0041D920[0x4];
extern u8 g_0042A390[0x4];
extern u8 g_0043C120[0x400];
extern u8 g_0043C5EC[0x4];
extern u8 g_0043C5F0[0x4];
extern u8 g_0043C730[0x4];
extern u8 g_0043C780[0x4];
extern u8 g_0043C784[0x4];
extern u8 g_0043C7BC[0x4];
extern u8 g_0043F530[0x4];
extern u8 g_0043F540[0x4];
extern u8 g_00441DD0[0x4];
extern u8 g_00442030[0xC];
extern u8 g_00442300[0x8];
extern u8 g_00447A10[0x4];
extern u8 g_0044E580[0x400];
extern u8 g_0044E5D0[0x4];
extern u8 g_00458BA0[0x400];
extern u8 g_004593A8[0x400];
extern u8 g_0045A830[0x10B];
extern u8 g_0045C998[0x4];
extern u8 g_0045CDB8[0x4];
extern u8 g_0045D1C8[0x4];
extern u8 g_0045D488[0x4];
extern u8 g_0045D4A0[0x4];
extern u8 g_0045D610[0x4];
extern u8 g_0045D7FC[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_0056CCA4[0x24];
extern u8 g_0056CCC0[0x8];
extern u8 g_00574F58[0x2];
extern u8 g_00575588[0x2];
extern u8 g_005BA690[0x10];
extern u8 g_005BA6A0[0x4];
extern u8 g_005BA7C8[0x4];
extern u8 g_005BC3A0[0x5];
extern u8 g_005BD740[0x4];
extern u8 g_00669DB0[0x1];
extern u8 g_00669DB3[0x1];
extern u8 g_00669DB8[0x4];
extern u8 g_00669F60[0x4];
extern u8 g_00669F9C[0x8];
extern u8 g_0068F0F0[0x8];
extern u8 g_0068F0F8[0x8];
extern u8 g_00693970[0x10];
extern u8 g_006A1CD0[0x10];
extern u8 g_006A3A30[0x4];
extern u8 g_006A3A34[0x4];
extern u8 g_006A3A40[0x4];
extern u8 g_006A3AB0[0x4];
extern u8 g_006A3AB2[0x4];
extern u8 g_006A3AB4[0x4];
extern u8 g_006A3AE8[0x4];
extern u8 g_006A3AEC[0x4];
extern u8 g_006A3D30[0x10];
extern u8 g_006AA598[0x4];
extern u8 g_006AA5D0[0x4];
extern u8 g_0072D224[0x4];
extern u8 g_0072D35C[0x4];
extern u8 g_0072D46C[0x4];
extern u8 g_0072D478[0x4];
extern u8 g_00732220[0x10];
extern u8 g_00732500[0xE8];
extern u8 g_00732508[0x10];
extern u8 g_0073253C[0x4];
extern u8 g_00732546[0x4];
extern u8 g_00732550[0x4];
extern u8 g_0073255A[0x5];
extern u8 g_007325B8[0x2C];
extern u8 g_007325FC[0x4];
extern u8 g_00732604[0x4];
extern u8 g_00732608[0x4];
extern u8 g_0073260D[0x4];
extern u8 g_0073260E[0x4];
extern u8 g_0073DCA0[0x4];
extern u8 g_0073DCA3[0x1];
extern u8 g_0073DF30[0x4];
extern u8 g_0073DF33[0x1];
extern u8 g_0073E020[0x4];
extern u8 g_0073E0E0[0x4];
extern u8 g_0073E160[0x4];
extern u8 g_007404B0[0x4];
extern u8 g_0074A008[0x4];
extern u8 g_0074B7D0[0x1C];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_00772D48[0x4];
extern u8 g_0077C040[0x10];
extern u8 g_007A05AC[0x4];
extern u8 g_007B5DE4[0x30];
extern u8 g_007B9E58[0x1];
extern u8 g_007B9E5D[0x4];
extern u8 g_007BA8B0[0x18];
extern u8 g_007BAC00[0x14];
extern u8 g_007BACC4[0x4];
extern u8 g_007BAD38[0x4];
extern u8 g_007BAE22[0x4];
extern u8 g_007BAE74[0x1C];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern u8 g_007BEAD0[0x10];
extern u8 g_007BEAD4[0x4];
extern u8 g_007BFB30[0x14];
extern u8 g_007BFDCD[0x1];
extern u8 g_007BFDD8[0x9];
extern int g_0045CDAC;   /* (small data) */
extern int g_0045CED2;   /* (small data) */
extern int g_0045CED8;   /* (small data) */
extern int g_0045CEDC;   /* (small data) */
extern int g_0045CEE2;   /* (small data) */
extern int g_0045CEE6;   /* (small data) */
extern int g_0045CEE8;   /* (small data) */
extern int g_0045CEEC;   /* (small data) */
extern int g_0045CEF2;   /* (small data) */
extern int g_0045CEF6;   /* (small data) */
extern int g_0045CEF8;   /* (small data) */
extern int g_0045CEFC;   /* (small data) */
extern int g_0045CFD8;   /* (small data) */
extern int g_0045D2A4;   /* (small data) */
extern int g_0045D2C0;   /* (small data) */
extern int g_0045D2F0;   /* (small data) */
extern int g_0045D374;   /* (small data) */
extern int g_0045D37C;   /* (small data) */
extern int g_0045D470;   /* (small data) */
extern int g_0045D490;   /* (small data) */
extern int g_0045D4E8;   /* (small data) */
extern int g_0045D600;   /* (small data) */
extern int g_0045D60C;   /* (small data) */
extern int g_0045D614;   /* (small data) */
extern int g_0045D620;   /* (small data) */
extern int g_0045D674;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern int g_0045D838;   /* (small data) */
#define g_700000C0 (*(int *)PS2_PTR(0x700000C0))   /* (scratchpad) */
#define g_700000C4 (*(int *)PS2_PTR(0x700000C4))   /* (scratchpad) */
#define g_700000C8 (*(int *)PS2_PTR(0x700000C8))   /* (scratchpad) */
#define g_700000CC (*(int *)PS2_PTR(0x700000CC))   /* (scratchpad) */
#define g_70000150 (*(int *)PS2_PTR(0x70000150))   /* (scratchpad) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_700001D0 (*(int *)PS2_PTR(0x700001D0))   /* (scratchpad) */
#define g_700001D8 (*(int *)PS2_PTR(0x700001D8))   /* (scratchpad) */
#define g_700001E0 (*(int *)PS2_PTR(0x700001E0))   /* (scratchpad) */
#define g_7000088C (*(int *)PS2_PTR(0x7000088C))   /* (scratchpad) */
#define g_70000B90 (*(int *)PS2_PTR(0x70000B90))   /* (scratchpad) */
#define g_70000B91 (*(int *)PS2_PTR(0x70000B91))   /* (scratchpad) */
#define g_70000B92 (*(int *)PS2_PTR(0x70000B92))   /* (scratchpad) */
#define g_70000B93 (*(int *)PS2_PTR(0x70000B93))   /* (scratchpad) */
#define g_70000BA0 (*(int *)PS2_PTR(0x70000BA0))   /* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))   /* (scratchpad) */

int func_001204B0();
int func_001207E0();
int func_00174A40(float r, u8 *a, u8 *b);
int func_0017AC50();
int func_00180D10();
int func_001C6010();
int func_001C66C0();
int func_001C7560();
void func_001C7F30(int k, float *pos, int c, u32 f);
int func_001EE570();
int func_001F5A60();
int func_001FDD90();
int func_001FE030();
int func_001FF100();
void *func_001FF140();
void *func_001FF230();
int func_00202000();
int func_00202410();
int func_00202610();
int func_00204B60();
int func_002054C0();
int func_002071F0();
void func_002075A0(float yaw, u8 *r, float *out, int a);
int func_00210ED0();
int func_00229E50();
int func_0022A200();
int func_0022A480();
int func_0022A5E0();
int func_00238AE0();
int func_00246610();
int func_0024B330();
int func_00290F90();
int func_002911C0();
void func_0029D9F0(float, float, float, float, u8 *, u8 *, u8 *, u8 *);
int func_002B20A0();
int func_002B29B0();
int func_002B3940();
int func_002BAE40();
int func_002BAF90();
int func_002C7310();
void func_002CD940(float, int, int, int, int, int);
int func_002D73D0();
int func_002D7AD0();
int func_002E6280();
int func_002ED150();
int func_002ED160();
int func_002EE5E0();
void *func_0030D7D0();
int func_00325710();
int func_00325D90();
int func_003264B0();
int func_003266D0();
int func_00326850();
int func_0034A450();
int func_0034A550();
int func_0037EB40();
int func_00380E80();
int func_00382770();
int func_00388710();
int func_003890A0();
int func_003986E0();
int func_0039A160();
int func_0039A3B0();
int func_0039B980();
int func_003AEF30();
int func_003B4180();
int func_003B4EC0();
int func_00207830(u8 *param_1);
void func_0039F590(void);
void func_003E7C10(void);

/* 0x001820F0, 0x244 bytes. */
int func_001820F0(int *param_1)
{
    int iVar1;
    int iVar2;
    u8 * iVar3;
    u32 uVar4;

    uVar4 = 0;
    iVar3 = g_00693970;
    do {
        func_00118AC0((u32 *)(param_1), iVar3, 0x88);
        if ((param_1[0x20] & 1U) != 0) {
            if (*param_1 == 0) {
                iVar1 = -1;
            }
            else {
                iVar1 = (*param_1 + -0x693970) / 0x88;
            }
            *param_1 = iVar1;
            if (param_1[1] == 0) {
                iVar1 = -1;
LAB_001821b0:
                param_1[1] = iVar1;
            }
            else {
                iVar2 = param_1[1] - *(u32 *)g_005BA7C8;
                iVar1 = iVar2 >> 5;
                if (-1 < iVar2) goto LAB_001821b0;
                param_1[1] = iVar2 + 0x1F >> 5;
            }
            if (param_1[2] == 0) {
                iVar1 = -1;
            }
            else {
                iVar1 = (param_1[2] - *(u32 *)g_005BA6A0) / 0x2C;
            }
            param_1[2] = iVar1;
            if (param_1[3] == 0) {
                iVar1 = -1;
            }
            else {
                iVar1 = (param_1[3] - *(u32 *)g_005BA6A0) / 0x2C;
            }
            param_1[3] = iVar1;
            if (param_1[6] == 0) {
                iVar1 = -1;
            }
            else {
                iVar1 = (param_1[6] + -0x693970) / 0x88;
            }
            param_1[6] = iVar1;
            if (param_1[7] == 0) {
                iVar1 = -1;
            }
            else {
                iVar1 = (param_1[7] + -0x693970) / 0x88;
            }
            param_1[7] = iVar1;
            if (((param_1[0x20] & 0x20000U) != 0) &&
                  (func_00180D10(param_1), (param_1[0x20] & 0x1b0U) == 0)) {
                param_1[5] = 0x8F;
                param_1[0x20] = param_1[0x20] & 0xFFFDFFFF;
            }
        }
        uVar4 = uVar4 + 1;
        param_1 = param_1 + 0x22;
        iVar3 = iVar3 + 0x88;
        if (0x1AC < uVar4) {
            return PS2_ADDR(param_1);
        }
    } while( true );
}

/* 0x00183670, 0x1D0 bytes. */
void func_00183670(int param_1)
{
    int iStack_4;
    int iStack_8;
    int iVar1;
    int iVar2;
    int iVar3;
    int * piVar4;
    int * piVar5;
    int * piVar6;

    func_001F0960((float *)((u32 *)PS2_PTR(param_1)), (float *)(&iStack_4), (float *)(&iStack_8));
    piVar6 = (int *)0x73DA30;
    piVar4 = (int *)0;
    iVar2 = 200;
    iVar3 = 0;
    do {
        iVar1 = *piVar6;
        piVar5 = piVar6;
        if (iVar1 == 0) break;
        if (iVar1 < iVar2) {
            iVar2 = iVar1;
            piVar4 = piVar6;
        }
        iVar3 = iVar3 + 1;
        piVar6 = piVar6 + 7;
        piVar5 = piVar4;
    } while (iVar3 < 0xC);
    if (piVar5 != (int *)0) {
        *piVar5 = 200;
        piVar5[4] = iStack_4;
        piVar5[5] = iStack_8;
        piVar5[1] = 0;
        piVar5[2] = 0;
        piVar5[3] = 0;
        if ((*(u8 *)(g_0073DCA0 + 0x3) & 1) == 0) {
            if (*(char *)g_0073DCA0 != 0) {
                *(char *)(g_0073DCA0) = -0x38;
            }
        }
        else {
            *(char *)(g_0073DCA0) = -0x38;
            if (((unsigned long long)(*(u8 *)g_00669DB0) & 0xF) >> 1 == 0) {
                func_00210ED0(0, 0);
            }
        }
    }
    piVar6 = (int *)0x73DCC0;
    piVar4 = (int *)0;
    iVar2 = 200;
    if ((*(u32 *)g_00669F60 & 2) != 0) {
        iVar3 = 0;
        do {
            iVar1 = *piVar6;
            piVar5 = piVar6;
            if (iVar1 == 0) break;
            if (iVar1 < iVar2) {
                iVar2 = iVar1;
                piVar4 = piVar6;
            }
            iVar3 = iVar3 + 1;
            piVar6 = piVar6 + 7;
            piVar5 = piVar4;
        } while (iVar3 < 0xC);
        if (piVar5 != (int *)0) {
            *piVar5 = 200;
            piVar5[4] = iStack_4;
            piVar5[5] = iStack_8;
            piVar5[1] = 0;
            piVar5[2] = 0;
            piVar5[3] = 0;
            if ((*(u8 *)(g_0073DF30 + 0x3) & 1) == 0) {
                if (*(char *)g_0073DF30 != 0) {
                    *(char *)(g_0073DF30) = -0x38;
                }
            }
            else {
                *(char *)(g_0073DF30) = -0x38;
                if (((unsigned long long)(*(u8 *)g_00669DB0) & 0xF) >> 1 == 0) {
                    func_00210ED0(1, 0);
                }
            }
        }
    }
}

/* 0x001C4B10, 0x200 bytes. */
void func_001C4B10(u8 *param_1, u8 *param_2, int param_3, int param_4)
{
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar7;
    long long lVar2;
    u32 * puVar1;
    u32 uVar6;

    uVar6 = *(u32 *)(param_2 + 4);
    lVar2 = PS2_ADDR(func_001CB740());
    puVar1 = (u32 *)lVar2;
    if (lVar2 == 0) {
        return;
    }
    puVar1[6] = 0;
    puVar1[7] = 0;
    if (*(int *)(param_1 + 0x14) == 0) {
        *(ps2ptr *)(param_1 + 0x10) = PS2_ADDR(puVar1);
    }
    else {
        *(ps2ptr *)(*(int *)(param_1 + 0x14) + 0x1C) = PS2_ADDR(puVar1);
        puVar1[6] = *(u32 *)(param_1 + 0x14);
    }
    *(ps2ptr *)(param_1 + 0x14) = PS2_ADDR(puVar1);
    puVar1[5] = PS2_ADDR(param_2);
    *puVar1 = 0;
    iVar3 = *(int *)(param_2 + 0xC);
    puVar1[4] = *(u32 *)(param_2 + 0x20);
    puVar1[10] = param_3;
    puVar1[0xB] = param_4;
    if ((uVar6 & 0x100000) == 0) {
        puVar1[3] = 0;
    }
    else {
        puVar1[3] = (float)*(int *)(param_2 + 0x1C);
    }
    iVar7 = *(int *)(param_2 + 0x10);
    if (iVar7 != 0) {
        if (iVar7 == 0) {
            iVar7 = 0;
        }
        else {
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            iVar7 = (int)(g_7000015C >> 0x10) % iVar7;
        }
        g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
        iVar5 = iVar7 >> 1;
        if ((g_7000015C >> 0x10 & 1) != 0) {
            iVar4 = iVar5;
            if (iVar7 < 0) {
                iVar4 = iVar7 + 1 >> 1;
            }
            if (iVar4 < iVar3) {
                iVar3 = iVar3 - iVar4;
                goto LAB_001c4c68;
            }
        }
        if (iVar7 < 0) {
            iVar5 = iVar7 + 1 >> 1;
        }
        iVar3 = iVar3 + iVar5;
    }
LAB_001c4c68:
    if ((*(u32 *)(param_1 + 0x34) & 0x1000) != 0) {
        uVar6 = *(u32 *)(param_1 + 0x40);
        if (4 < uVar6) {
            uVar6 = 4;
        }
        iVar3 = (int)((float)iVar3 * ((float)(int)uVar6 / 4.0));
    }
    puVar1[2] = iVar3;
    puVar1[1] = iVar3;
    if ((g_0045D37C != 0) && (g_70000D60 == 1)) {
        puVar1[2] = 1;
        puVar1[1] = 1;
    }
}

/* 0x001C6830, 0x124 bytes. */
void func_001C6830(void)
{
    int iVar1;
    int iVar2;

    iVar2 = g_70000D60 * 0x350;
    for (iVar1 = *(int *)(g_0072D224 + iVar2); iVar1 != 0; iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 0xF4)) {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) & 0xFFFFFFEE;
        func_001C5F50((int *)PS2_PTR(iVar1));
    }
    for (iVar1 = *(int *)(g_0072D35C + iVar2); iVar1 != 0; iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x11C)) {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) & 0xFFFFFFEE;
        func_001C5F50((int *)PS2_PTR(iVar1));
        if (((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) & 0xC) == 0) && ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) & 0x20000000) == 0)) {
            func_001C6010(iVar1);
        }
    }
    for (iVar1 = *(int *)(g_0072D46C + iVar2); iVar1 != 0; iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x10C)) {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) & 0xFFFFFFEE;
        func_001C5F50((int *)PS2_PTR(iVar1));
        if ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) & 0xC) == 0) {
            func_001C66C0(iVar1);
        }
    }
}

/* 0x001C7060, 0x290 bytes. */
int func_001C7060(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int bVar2;
    int iVar1;
    int iVar10;
    u8 * iVar24;
    int iVar3;
    int iVar6;
    long long lVar23;
    long long lVar4;
    u32 uVar11;
    u32 uVar12;
    u32 uVar13;
    u32 uVar14;
    u32 uVar15;
    u32 uVar16;
    u32 uVar17;
    u32 uVar18;
    u32 uVar19;
    u32 uVar20;
    u32 uVar21;
    u32 uVar22;
    u32 uVar5;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    lVar23 = 0;
    iVar1 = g_70000D60 * 0x350;
    lVar4 = 1;
    if ((param_4 < 0x2E) && (*(int *)(param_1 * 4 + 0x72C870) != 0)) {
        iVar24 = (u8 *)PS2_PTR((int)param_2);
        if ((param_6 != 0) && (param_2 != 0)) {
            lVar4 = func_00240420(*(u8 *)(iVar24 + 0x14E));
        }
        if (param_2 == 0) {
            if (param_3 == 0) {
                lVar4 = 0;
            }
        }
        else if (*(int *)(iVar24 + 0x11C) == 0) {
            lVar4 = 0;
        }
        if (lVar4 != 0) {
            if ((param_2 != 0) && (param_6 != 0)) {
                uVar5 = 0;
                iVar10 = (u32)*(u8 *)(iVar24 + 0x14E) * 0x70 + 0x74B868;
                do {
                    iVar3 = *(int *)((u8 *)PS2_PTR(iVar10) + 0x50);
                    if ((((iVar3 != 0) && (*(u32 *)((u8 *)PS2_PTR(iVar3) + 0xF8) == param_4)) &&
                            (*(int *)((u8 *)PS2_PTR(iVar3) + 0x24) == param_1)) && ((*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x38) & 0xC) == 0)) {
                        bVar2 = true;
                        if (((*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x34) & 0x400) == 0) && ((*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x34) & 0x800) == 0)
                              ) {
                            bVar2 = false;
                        }
                        if (!bVar2) {
                            lVar4 = 0;
                        }
                    }
                    uVar5 = uVar5 + 1;
                    iVar10 = iVar10 + 4;
                } while (uVar5 < 8);
            }
            lVar23 = 0;
            if ((lVar4 != 0) && (lVar23 = PS2_ADDR(func_001CB4C0()), lVar23 != 0)) {
                iVar10 = (int)lVar23;
                *(int *)((u8 *)PS2_PTR(iVar10) + 0xF0) = PS2_ADDR(iVar24);
                *(int *)((u8 *)PS2_PTR(iVar10) + 0xF4) = (int)param_3;
                *(u32 *)((u8 *)PS2_PTR(iVar10) + 0xF8) = param_4;
                *(int *)((u8 *)PS2_PTR(iVar10) + 0xFC) = (int)param_6;
                *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x34) = param_5;
                func_001C7560(param_1, lVar23, param_5 & 0x10);
                if ((param_5 & 0x4000) != 0) {
                    *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x3C) = 0xFFFFFFFF;
                    *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x34) = *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x34) & 0xFFFFBFFF;
                }
                func_001C66C0(lVar23);
                iVar6 = iVar10 + g_70000150 * 0x50;
                iVar3 = iVar10 + (g_70000150 ^ 1) * 0x50;
                uVar7 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 100);
                uVar8 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x68);
                uVar9 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x6C);
                uVar11 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x70);
                uVar12 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x74);
                uVar13 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x78);
                uVar14 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x7C);
                uVar15 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x80);
                uVar16 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x84);
                uVar17 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x88);
                uVar18 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x8C);
                uVar19 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x90);
                uVar20 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x94);
                uVar21 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x98);
                uVar22 = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x9C);
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x60) = *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x60);
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 100) = uVar7;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x68) = uVar8;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x6C) = uVar9;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x70) = uVar11;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x74) = uVar12;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x78) = uVar13;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x7C) = uVar14;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x80) = uVar15;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x84) = uVar16;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x88) = uVar17;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x8C) = uVar18;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x90) = uVar19;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x94) = uVar20;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x98) = uVar21;
                *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x9C) = uVar22;
                *(int *)(*(int *)(g_0072D478 + iVar1) + 0x10C) = iVar10;
                *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x108) = *(u32 *)(g_0072D478 + iVar1);
                *(int *)(g_0072D478 + iVar1) = iVar10;
                *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x10C) = 0;
                if (param_6 != 0) {
                    func_00240450(*(u8 *)(iVar24 + 0x14E), (u8 *)PS2_PTR(lVar23));
                }
            }
        }
    }
    return lVar23;
}

/* 0x001CCD60, 0x240 bytes. */
int func_001CCD60(u8 *param_1, int param_2, u8 *param_3)
{
    int iVar5;
    int iVar7;
    u8 * iVar8;
    int sVar1;
    int sVar3;
    int sVar4;
    u32 uStack_4;
    int uVar2;
    unsigned long long uVar6;

    uStack_4 = 0;
    iVar5 = *(short *)(param_1 + 0x178) * 0xC0;
    iVar8 = (u8 *)PS2_PTR((int)param_2);
    if (param_2 == 0) {
        iVar7 = 0;
    }
    else {
        iVar7 = *(short *)(iVar8 + 0x178) * 0xC0 + 0x6A3A30;
    }
    if (iVar7 == 0) {
        uVar6 = 5;
    }
    else {
        uVar6 = 0;
    }
    uVar2 = func_002054C0(iVar7, iVar5 + 0x6A3A30, param_3, uVar6, 0, 0, 0, &uStack_4);
    if ((*(u32 *)(param_3 + 0x2C) & 0x20000000) == 0) {
        *(u32 *)(g_006A3AEC + iVar5) = *(u32 *)(g_006A3AEC + iVar5) & 0xFFF7FFFF;
    }
    else {
        *(u32 *)(g_006A3AEC + iVar5) = *(u32 *)(g_006A3AEC + iVar5) | 0x80000;
    }
    if ((*(u32 *)g_00669F60 & 0x14280000) == 0) {
        if (((param_2 != 0) && (*(char *)(iVar8 + 0x17E) == 4)) &&
              ((*(u32 *)((u8 *)PS2_PTR(iVar7) + 0xB8) & 2) == 0)) {
            sVar3 = *(short *)(g_006A3AB2 + iVar5) + (u16)*(u8 *)(iVar8 + 0x17F) * -2;
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
    else {
        g_70000D60 = 1;
        func_001C8130(5, PS2_ADDR((float *)(param_1 + 0x90)), 0, 8, *(u8 *)(param_1 + 0x14E));
    }
    return uVar2;
}

/* 0x001CEBC0, 0x434 bytes. */
void func_001CEBC0(u8 *param_1)
{
    int bVar6;
    int cVar1;
    int cVar10;
    int cVar5;
    u8 * iVar12;
    int iVar13;
    int iVar3;
    int iVar8;
    int iVar9;
    long long lVar7;
    int * piVar11;
    int * piVar2;
    int * piVar4;

    iVar9 = PS2_ADDR(param_1);
    if (1 < *(u8 *)((u8 *)PS2_PTR(iVar9) + 0x14E)) {
        iVar8 = *(short *)((u8 *)PS2_PTR(iVar9) + 0x178) * 0xC0;
        iVar13 = *(int *)(g_006A3A30 + iVar8);
        piVar2 = (int *)PS2_PTR(*(ps2ptr *)(g_006A3A34 + iVar8));
        *(u32 *)(g_006A3A34 + iVar8) = 0;
        *(int *)(g_006A3A30 + iVar8) = 0;
        iVar3 = *(int *)(g_006A3A40 + iVar8);
        if (iVar3 == 0) {
            func_00166160(param_1);
            *(u32 *)(g_006A3AEC + iVar8) = 0;
            *(u32 *)(g_006A3AE8 + iVar8) = 0;
        }
        else {
            if (*(u8 *)((u8 *)PS2_PTR(iVar9) + 0x185) < 0x17) {
                func_0024D070(*(u8 *)((u8 *)PS2_PTR(iVar9) + 0x185), (u32 *)PS2_PTR(iVar9 + 0xB0));
                *(u8 *)((u8 *)PS2_PTR(iVar9) + 0x185) = 0x17;
            }
            else if ((((long long)*(char *)((u8 *)PS2_PTR(iVar9) + 0x19E) << 0x3B < 0) && ((*(u32 *)g_00669F60 & 8) == 0)) &&
                            (lVar7 = func_001CEB30(), lVar7 < 0x17)) {
                func_0024D070(lVar7, (u32 *)PS2_PTR(iVar9 + 0xB0));
            }
            *(u8 *)((u8 *)PS2_PTR(iVar9) + 0x19E) = *(u8 *)((u8 *)PS2_PTR(iVar9) + 0x19E) & 0xEF;
            func_00166160(param_1);
            if ((*(u32 *)(g_006A3AE8 + iVar8) & 0x180) == 0) {
                if ((*(u32 *)(g_006A3AE8 + iVar8) & 0x8400) == 0) {
                    if (*(char *)((u8 *)PS2_PTR(iVar3) + 0x74) != 0) {
                        *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) = *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) + -1;
                    }
                    func_001F17D0((u8 *)PS2_PTR(iVar3 + 0x40), *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x79), 1);
                }
            }
            else {
                cVar1 = *(char *)((u8 *)PS2_PTR(iVar3) + 0x74);
                if (cVar1 == 0) {
                    if ((*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x80) & 0x200000) != 0) {
                        *(u32 *)((u32)((*(u32 *)(g_006AA5D0)) != (iVar3 + -0x693970) / 0x88) * 4 + 0x6AA5D0) =
                                  0x1AD;
                    }
                    func_001D4C00((u8 *)PS2_PTR(iVar3));
                    func_001EE3B0(iVar3);
                    *(u32 *)(g_006A3AEC + iVar8) = 0;
                    *(u32 *)(g_006A3AE8 + iVar8) = 0;
                    return;
                }
                if (((*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x80) & 0x200000) == 0) && ((*(u32 *)g_00669F60 & 8) == 0)) {
                    lVar7 = func_001ED900((u8 *)PS2_PTR(iVar3));
                    if (lVar7 == 0) {
                        *(int *)((u8 *)PS2_PTR(iVar3) + 0x14) = (int)(piVar2 + -0x1A8E8C) / 0xC0;
                        piVar2[0x2E] = piVar2[0x2E] | 0x100;
                        if (*(char *)((u8 *)PS2_PTR(iVar3) + 0x74) != 0) {
                            *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) = *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) + -1;
                        }
                        func_001F17D0((u8 *)PS2_PTR(iVar3 + 0x40), *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x79), 1);
                        func_001EE570(iVar3);
                        for (piVar4 = piVar2; piVar4 != (int *)0; piVar4 = (int *)piVar4[1]) {
                            if (piVar4[2] != 0) {
                                piVar4[0x2F] = piVar4[0x2F] & 0xFFFFFFFD;
                            }
                            piVar4[2] = 0;
                        }
                    }
                    else {
                        iVar12 = (u8 *)PS2_PTR((int)lVar7);
                        iVar9 = *(int *)(iVar12 + 0x14) * 0xC0;
                        iVar13 = iVar9 + 0x6A3A30;
                        piVar4 = piVar2;
                        cVar10 = 1;
                        do {
                            piVar11 = piVar4;
                            piVar11[4] = PS2_ADDR(iVar12);
                            cVar5 = cVar10 + 1;
                            *(char *)((int)piVar11 + 0x7F) = cVar10;
                            piVar4 = (int *)piVar11[1];
                            cVar10 = cVar5;
                        } while ((int *)piVar11[1] != (int *)0);
                        piVar4 = (int *)PS2_PTR(*(ps2ptr *)(g_006A3A34 + iVar9));
                        if (piVar4 != (int *)0) {
                            *piVar4 = (int)piVar11;
                            piVar11[1] = (int)piVar4;
                            for (; piVar4 != (int *)0; piVar4 = (int *)piVar4[1]) {
                                *(char *)((int)piVar4 + 0x7F) = cVar5;
                                cVar5 = cVar5 + 1;
                            }
                        }
                        func_001D4C00((u8 *)PS2_PTR(iVar3));
                        func_001EE3B0(iVar3);
                        bVar6 = cVar1 + *(char *)(iVar12 + 0x74);
                        if (9 < bVar6) {
                            bVar6 = 9;
                        }
                        *(u8 *)(iVar12 + 0x74) = bVar6;
                        func_001F1870(iVar12 + 0x40, *(u8 *)(iVar12 + 0x79), cVar1);
                    }
                }
                else {
                    *(int *)((u8 *)PS2_PTR(iVar3) + 0x14) = (int)(piVar2 + -0x1A8E8C) / 0xC0;
                    piVar2[0x2E] = piVar2[0x2E] | 0x100;
                    if (*(char *)((u8 *)PS2_PTR(iVar3) + 0x74) != 0) {
                        *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) = *(char *)((u8 *)PS2_PTR(iVar3) + 0x74) + -1;
                    }
                }
            }
            if (iVar13 != 0) {
                *(ps2ptr *)((u8 *)PS2_PTR(iVar13) + 4) = PS2_ADDR(piVar2);
            }
            if (piVar2 != (int *)0) {
                *piVar2 = iVar13;
            }
            *(u32 *)(g_006A3AEC + iVar8) = 0;
            *(u32 *)(g_006A3AE8 + iVar8) = 0;
        }
    }
}

/* 0x001D0B20, 0xF0 bytes. */
void func_001D0B20(u8 *param_1)
{
    u8 * iVar1;
    long long lVar2;
    long long lVar4;
    unsigned long long uVar3;

    iVar1 = param_1;
    if ((((*(int *)(iVar1 + 0x11C) != 0) && (*(char *)(iVar1 + 0x181) == 0)) &&
            (2 < *(int *)(iVar1 + 0x118) - 0x3dU)) && (-1 < (long long)*(char *)(iVar1 + 0x19C) << 0x38)) {
        if ((*(char *)(iVar1 + 0xD4) == '\v') || (*(char *)(iVar1 + 0xD4) == 5)) {
            lVar4 = 0xE2;
        }
        else {
            lVar4 = 0x18B;
        }
        lVar2 = func_0016C040(param_1);
        if (lVar2 == 0) {
            uVar3 = 0;
        }
        else {
            uVar3 = 0x200;
        }
        if (lVar4 != 0x18B) {
            iVar1 = (u8 *)(func_0016A170(param_1, 8));
            g_70000D60 = 0;
            func_001C7F30(lVar4, (float *)(iVar1 + 0x30), 0, uVar3);
        }
    }
}

/* 0x001D6BD0, 0xA0 bytes. */
int func_001D6BD0(u32 *param_1, u32 *param_2, int param_3, int param_4)
{
    switch(param_3) {
    case 0:
        *(u8 *)param_1 = *(u8 *)param_2;
        break;
    case 1:
        *(u16 *)param_1 = *(u16 *)param_2;
        break;
    case 2:
        *param_1 = *param_2;
        break;
    case 3:
        *(u8 *)param_1 = *(u8 *)param_2;
        break;
    case 4:
        *(u16 *)param_1 = *(u16 *)param_2;
        break;
    case 5:
        *param_1 = *param_2;
        break;
    case 6:
        *param_1 = *param_2;
        break;
    case 7:
    case 8:
        *param_1 = *param_2;
        break;
    default:
        *(u16 *)param_1 = *(u16 *)param_2;
    }
    return PS2_ADDR((u8 *)((int)param_2 + (param_4 & 0xFF)));
}

/* 0x001EA090, 0x190 bytes. */
void func_001EA090(void)
{
    char acStack_10f[263];
    int bVar2;
    int cStack_110;
    int cVar1;
    int iStack_4;
    int iStack_8;
    int iVar7;
    int iVar8;
    int iVar9;
    char * pcVar4;
    int * piVar10;
    int * piVar3;
    int * piVar5;
    int * piVar6;

    bVar2 = false;
    iVar9 = 0;
    piVar6 = (int *)0x731390;
    pcVar4 = (char *)(&cStack_110);
    piVar10 = piVar6;
    piVar5 = piVar6;
    do {
        if (*piVar6 == 0) {
            return;
        }
        iVar8 = 0;
        iVar7 = 0;
        if ((char)piVar5[0x8C] != 0) {
            piVar3 = piVar6;
            do {
                func_00147160((u8 *)PS2_PTR(*piVar3), (u8 *)(&cStack_110), 0x1B8, 0, 0);
                *(u32 *)(g_0056CCC0) = 0x41A00000;
                *(u32 *)(g_0056CCC0 + 0x4) = 0x41A00000;
                func_00146D80((u8 *)(&cStack_110), &iStack_4, &iStack_8);
                *(u32 *)(g_0056CCC0) = 0x41800000;
                iVar7 = iVar7 + 1;
                piVar3 = piVar3 + 3;
                *(u32 *)(g_0056CCC0 + 0x4) = 0x41800000;
                iVar8 = iVar8 + iStack_4;
            } while (iVar7 < (int)(u32)*(u8 *)(piVar5 + 0x8C));
        }
        cVar1 = *pcVar4;
        while (cVar1 != 0) {
            if (cVar1 == '\n') {
                bVar2 = true;
                break;
            }
            pcVar4 = pcVar4 + 1;
            cVar1 = *pcVar4;
        }
        iVar7 = -iVar8 + 0x280;
        if (iVar7 < 0) {
            iVar7 = -iVar8 + 0x281;
        }
        piVar10[0x88] = iVar7 >> 1;
        if (bVar2) {
            iVar7 = 10;
        }
        else {
            iVar7 = 0;
        }
        piVar6 = piVar6 + 0x42;
        piVar5 = (int *)((int)piVar5 + 1);
        iVar8 = iStack_8 * iVar9;
        iVar9 = iVar9 + 1;
        piVar10[0x8A] = (iVar8 + 0x1D8) - iVar7;
        piVar10 = piVar10 + 1;
        if (1 < iVar9) {
            return;
        }
    } while( true );
}

/* 0x001ECEA0, 0x164 bytes. */
int func_001ECEA0(u8 *param_1, int param_2)
{
    int cVar1;
    float fVar6;
    float fVar7;
    u8 * iVar3;
    int iVar8;
    long long lVar4;
    long long lVar5;
    unsigned long long uVar2;

    iVar8 = PS2_ADDR(param_1);
    if (param_2 == 0) {
        iVar3 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(iVar8) + 0xC));
    }
    else {
        iVar3 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(iVar8) + 8));
    }
    if ((*(u32 *)((u8 *)PS2_PTR(iVar8) + 0x80) & 0x1B0) == 0) {
        fVar6 = (float)func_001ECC10(param_1, 0);
        if (param_2 == 0) {
            uVar2 = func_0034A550(param_1);
            if ((long long)uVar2 < 0) {
                fVar7 = (float)(uVar2 & 0xFFFFFFFF);
            }
            else {
                fVar7 = (float)(int)uVar2;
            }
            cVar1 = *(char *)((u8 *)PS2_PTR(iVar8) + 0x79);
        }
        else {
            uVar2 = func_0034A450(param_1);
            if ((long long)uVar2 < 0) {
                fVar7 = (float)(uVar2 & 0xFFFFFFFF);
            }
            else {
                fVar7 = (float)(int)uVar2;
            }
            cVar1 = *(char *)((u8 *)PS2_PTR(iVar8) + 0x79);
        }
        iVar8 = (int)(fVar6 * 0.5 * fVar7);
        lVar4 = (long long)iVar8;
        if (cVar1 == 1) {
            fVar6 = (float)func_003E7050();
            lVar4 = (long long)(int)((float)iVar8 * fVar6);
        }
    }
    else {
        lVar4 = (long long)*(short *)(iVar3 + 0xC);
    }
    lVar5 = lVar4;
    if (lVar4 < 2) {
        lVar5 = 1;
    }
    if (1000 < lVar4) {
        lVar5 = 1000;
    }
    return lVar5;
}

/* 0x001ED010, 0xE4 bytes. */
int func_001ED010(u8 *param_1, int *param_2)
{
    float fVar3;
    float fVar6;
    int iVar1;
    int iVar4;
    unsigned long long * puVar2;
    unsigned long long uStack_10;
    unsigned long long uStack_8;
    u32 uVar5;

    if ((*(u32 *)(param_1 + 0x80) & 0x20000) == 0) {
        puVar2 = (unsigned long long *)(param_1 + 0x28);
    }
    else {
        puVar2 = (unsigned long long *)(param_1 + 0x30);
    }
    uStack_8 = *puVar2;
    iVar4 = 0;
    uVar5 = 0;
    fVar3 = 1.5625e+10;
    do {
        iVar1 = *param_2;
        if (iVar1 != 0) {
            if ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x80) & 0x20000) == 0) {
                puVar2 = (unsigned long long *)(iVar1 + 0x28);
            }
            else {
                puVar2 = (unsigned long long *)(iVar1 + 0x30);
            }
            uStack_10 = *puVar2;
            fVar6 = (float)func_0018C3F0((float *)(&uStack_8), (float *)(&uStack_10));
            if (fVar6 < fVar3) {
                fVar3 = fVar6;
                iVar4 = iVar1;
            }
        }
        uVar5 = uVar5 + 1;
        param_2 = param_2 + 1;
    } while (uVar5 < 0xD);
    return iVar4;
}

/* 0x001ED900, 0x1C4 bytes. */
int func_001ED900(u8 *param_1)
{
    int bVar2;
    int iVar1;
    u8 * iVar3;
    u32 uVar4;
    u32 uVar5;

    if (*(char *)(param_1 + 0x79) != 0) {
        iVar3 = g_006A1CD0;
        uVar5 = 0x1AC;
        do {
            if (param_1 != iVar3) {
                uVar4 = *(u32 *)(iVar3 + 0x80);
                bVar2 = false;
                if (((uVar4 & 1) != 0) && ((uVar4 & 0x8C40002) == 0)) {
                    bVar2 = true;
                }
                if ((((bVar2) && ((uVar4 & 0x20000) != 0)) && ((uVar4 & 0xC000) == 0)) &&
                      ((((*(char *)(param_1 + 0x79) == *(char *)(iVar3 + 0x79) &&
                            (iVar1 = *(int *)(iVar3 + 8), (*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x28) & 0xFC) == 0)) &&
                          ((*(char *)(*(int *)(param_1 + 0xC) + 9) == *(char *)(*(int *)(iVar3 + 0xC) + 9) &&
                            (((uVar4 & 4) == 0 && (*(char *)(iVar3 + 0x7A) != 3)))))) &&
                        (*(short *)(param_1 + 0x40) == *(short *)(iVar3 + 0x40))))) {
                    uVar4 = (u32)*(u8 *)((u8 *)PS2_PTR(iVar1) + 0x1E) << 1;
                    if (9 < uVar4) {
                        uVar4 = 9;
                    }
                    if (((((int)(u32)*(u8 *)(param_1 + 0x74) <= (int)(uVar4 - *(u8 *)(iVar3 + 0x74))) &&
                              (iVar1 = (iVar1 - *(u32 *)g_005BA6A0) / 0x2C, iVar1 != 0x214)) && (iVar1 != 0x1E2)) &&
                          ((iVar1 != 0x215 && (iVar1 != 0x21D)))) {
                        return PS2_ADDR(iVar3);
                    }
                }
            }
            uVar5 = uVar5 + 1;
            iVar3 = iVar3 + 0x88;
        } while (uVar5 < 0x1AD);
    }
    return 0;
}

/* 0x001F6070, 0x24C bytes. */
int func_001F6070(u8 *param_1)
{
    int bVar2;
    int bVar3;
    u8 * iVar4;
    u8 * iVar6;
    u8 * iVar7;
    u8 * iVar9;
    long long lVar13;
    long long lVar8;
    u16 * puStack_10;
    u16 * puVar11;
    int uVar1;
    u32 uVar10;
    u32 uVar12;
    u32 uVar5;

    iVar9 = param_1;
    uVar1 = *(u16 *)(iVar9 + 0x54);
    iVar4 = func_001FF140(uVar1);
    puVar11 = (u16 *)(iVar4 + 0x30);
    lVar13 = 0xFFFF;
    puStack_10 = (u16 *)0;
    uVar12 = 0;
    if (*(short *)(iVar4 + 4) != 0) {
        do {
            lVar8 = func_0032E7B0();
            if (((((lVar8 != 0) || (lVar8 = func_001FF200(uVar1), lVar8 == 0)) || (uVar12 < 0x19)) ||
                    ((0x1A < uVar12 || (lVar8 = PS2_ADDR(func_00353280(param_1)), lVar8 == 0)))) ||
                  (lVar8 = func_0034EE60((u8 *)PS2_PTR(lVar8)), lVar8 != 0)) {
                uVar5 = func_00207D80(*puVar11);
                bVar2 = func_001F5D90(param_1, (u8 *)(puVar11));
                bVar3 = func_001F5BC0(param_1, (u8 *)(puVar11));
                if (uVar5 != 0) {
                    *(u8 *)(iVar9 + 0x65) = *(u8 *)(iVar9 + 0x65) | bVar3;
                    *(u8 *)(iVar9 + 100) = *(u8 *)(iVar9 + 100) | bVar2;
                    if ((bVar2 != 0) || ((bVar3 & 0x7F) != 0)) {
                        iVar6 = func_00207D60(*puVar11);
                        iVar7 = func_00207DA0(*puVar11);
                        uVar10 = 0;
                        if (uVar5 != 0) {
                            do {
                                *(u32 *)(iVar9 + 0x5C) = *(u32 *)(iVar9 + 0x5C) | 1 << (uVar12 & 0x1F);
                                if ((*(char *)(iVar7 + uVar10) == 4) && (lVar13 == 0xFFFF)) {
                                    lVar13 = func_001F5A60(param_1, puVar11, iVar6, bVar2 != 0 || (bVar3 & 4) != 0);
                                    puStack_10 = puVar11;
                                }
                                else {
                                    func_001F5A60(param_1, puVar11, iVar6, bVar2 != 0 || (bVar3 & 4) != 0);
                                    puStack_10 = (u16 *)0;
                                }
                                uVar10 = uVar10 + 1;
                                iVar6 = iVar6 + 0x20;
                            } while (uVar10 < uVar5);
                        }
                    }
                }
            }
            uVar12 = uVar12 + 1;
            puVar11 = (u16 *)func_001FF230(puVar11);
        } while (uVar12 < *(u16 *)(iVar4 + 4));
    }
    return PS2_ADDR(puStack_10);
}

/* 0x001F64F0, 0x1C0 bytes. */
int func_001F64F0(u8 *param_1, int param_2, int param_3, int param_4, int param_5)
{
    int bVar7;
    int iVar1;
    int iVar2;
    int iVar4;
    long long lVar6;
    u32 * puVar8;
    int uVar3;
    u32 uVar5;

    bVar7 = *(u8 *)(param_1 + 100);
    lVar6 = func_00196B00();
    if (lVar6 == 0) {
        iVar4 = func_00196A40();
        puVar8 = (u32 *)(g_700001D8 + iVar4 * 8);
        iVar4 = PS2_ADDR(func_001945E0(param_2, param_3, param_4));
        if (*(char *)(param_1 + 0x65) != 0) {
            bVar7 = bVar7 | 0x80;
        }
        uVar5 = func_00196A10();
        *puVar8 = uVar5;
        if (iVar4 == 0) {
            if ((param_2 == 0) && (*(u32 *)g_00669DB8 != 2)) {
                uVar3 = func_001947C0(param_3, param_4, PS2_ADDR(puVar8), bVar7, param_5);
            }
            else {
                uVar3 = func_00194840(param_2, param_3, param_4, PS2_ADDR(puVar8), bVar7);
            }
        }
        else {
            iVar2 = *(int *)((u8 *)PS2_PTR(iVar4) + 4);
            while (iVar1 = iVar2, iVar1 != 0) {
                iVar4 = iVar1;
                iVar2 = *(int *)((u8 *)PS2_PTR(iVar1) + 4);
            }
            *(ps2ptr *)((u8 *)PS2_PTR(iVar4) + 4) = PS2_ADDR(puVar8);
            if ((param_2 == 0) && (*(u32 *)g_00669DB8 != 2)) {
                uVar3 = func_001947C0(param_3, param_4, 0, bVar7, param_5);
            }
            else {
                uVar3 = func_00194840(param_2, param_3, param_4, 0, bVar7);
            }
        }
        func_00196A50();
    }
    else {
        func_00196A50();
        uVar3 = 0;
    }
    return uVar3;
}

/* 0x001F66B0, 0xF8 bytes. */
void func_001F66B0(u8 *param_1, int param_2, int param_3)
{
    int bVar3;
    int iVar1;
    int iVar2;
    int iVar4;
    long long lVar6;
    u32 * puVar7;
    u32 uVar5;

    bVar3 = func_001FF100(*(u16 *)(param_1 + 0x54), 3);
    if (9 < bVar3) {
        lVar6 = func_00196B00();
        if (lVar6 == 0) {
            iVar4 = func_00196A40();
            puVar7 = (u32 *)(g_700001D8 + iVar4 * 8);
            iVar4 = func_001F5060(param_2, param_3);
            uVar5 = func_00196A10();
            *puVar7 = uVar5;
            if (iVar4 == 0) {
                func_001F5090(param_2, param_3, PS2_ADDR(puVar7));
            }
            else {
                iVar2 = *(int *)((u8 *)PS2_PTR(iVar4) + 4);
                while (iVar1 = iVar2, iVar1 != 0) {
                    iVar4 = iVar1;
                    iVar2 = *(int *)((u8 *)PS2_PTR(iVar1) + 4);
                }
                *(ps2ptr *)((u8 *)PS2_PTR(iVar4) + 4) = PS2_ADDR(puVar7);
            }
            func_00196A50();
        }
        else {
            func_00196A50();
        }
    }
}

/* 0x001F71C0, 0x71C bytes. */
void func_001F71C0(void)
{
    u8 * iStack_20;
    int iStack_30;
    u8 * iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    u8 * iVar7;
    u8 * iVar8;
    unsigned long long uVar1;

    iVar2 = g_007325B8;
    iVar3 = 0;
    *(u32 *)(g_007325B8) = 0;
    iStack_20 = g_00732220;
    *(u8 *)(g_007325B8 + 0x28) = 0;
    *(u8 *)(g_007325B8 + 0x29) = 0;
    *(u8 *)(g_007325B8 + 0x2A) = 0;
    *(u8 *)(g_007325B8 + 0x2B) = 0;
    do {
        *(u16 *)(iVar2 + 4) = 0;
        iVar3 = iVar3 + 3;
        *(u16 *)(iVar2 + 0x16) = 0;
        *(u16 *)(iVar2 + 6) = 0;
        *(u16 *)(iVar2 + 0x18) = 0;
        *(u16 *)(iVar2 + 8) = 0;
        *(u16 *)(iVar2 + 0x1A) = 0;
        iVar2 = iVar2 + 6;
    } while (iVar3 < 9);
    iStack_30 = 0;
    do {
        iVar2 = (u8 *)PS2_PTR(*(int *)(iStack_20 + 0x2E0));
        func_001050B0(iVar2 + 0x1E220);
        *(unsigned long long *)(iVar2 + 0x1E230) = 0x8000000044;
        *(unsigned long long *)(iVar2 + 0x1E238) = 0x43;
        func_001050B0(iVar2 + 0x1E190);
        *(unsigned long long *)(iVar2 + 0x1E1A0) = 0x48;
        *(unsigned long long *)(iVar2 + 0x1E1A8) = 0x43;
        uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F2B);
        func_00105A30(iVar2 + 0x1E1B0, uVar1, 1);
        iVar5 = 0;
        *(unsigned long long *)(iVar2 + 0x1E1D0) = 0x3F80000040404040;
        *(unsigned long long *)(iVar2 + 0x1E1D8) = 0x3F4000003EA80000;
        *(unsigned long long *)(iVar2 + 0x1E1E8) = 0x3F4000003EC80000;
        *(unsigned long long *)(iVar2 + 0x1E1F8) = 0x3F6000003EA80000;
        *(unsigned long long *)(iVar2 + 0x1E208) = 0x3F6000003EC80000;
        *(unsigned long long *)(iVar2 + 0x1E1E0) = 0;
        *(unsigned long long *)(iVar2 + 0x1E1F0) = 0;
        *(unsigned long long *)(iVar2 + 0x1E200) = 0;
        *(unsigned long long *)(iVar2 + 0x1E210) = 0;
        iVar3 = PS2_ADDR(iVar2);
        iVar8 = iVar2;
        do {
            if (iVar5 < 7) {
                uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F0B);
                func_001057F0(iVar8 + 0x1DEC0, uVar1, 0);
            }
            else {
                uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEE);
                func_001057F0(iVar8 + 0x1DEC0, uVar1, 0);
            }
            iVar4 = 0;
            *(unsigned long long *)(iVar8 + 0x1DEE0) = 0x3F80000080808080;
            *(unsigned long long *)(iVar8 + 0x1DEE8) = 0xE080808;
            *(unsigned long long *)(iVar8 + 0x1DEF8) = 0xFF80988;
            iVar6 = 0;
            *(unsigned long long *)(iVar8 + 0x1DEF0) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
            *(unsigned long long *)(iVar8 + 0x1DF00) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
            *(unsigned long long *)(iVar8 + 0x1DEF0) = 0;
            *(unsigned long long *)(iVar8 + 0x1DF00) = 0;
            iVar7 = (u8 *)PS2_PTR(iVar3);
            do {
                if (iVar5 < 7) {
                    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F0B);
                    func_001057F0(iVar7 + 0x1D920, uVar1, 0);
                }
                else {
                    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEE);
                    func_001057F0(iVar7 + 0x1D920, uVar1, 0);
                }
                *(unsigned long long *)(iVar7 + 0x1D940) = (long long)(0x40 - iVar6) << 0x18 | 0x3F80000000808080;
                *(unsigned long long *)(iVar7 + 0x1D948) = 0xE080808;
                *(unsigned long long *)(iVar7 + 0x1D958) = 0xFF80988;
                iVar4 = iVar4 + 1;
                iVar6 = iVar6 + 0x20;
                *(unsigned long long *)(iVar7 + 0x1D950) =
                          (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
                *(unsigned long long *)(iVar7 + 0x1D960) =
                          (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
                *(unsigned long long *)(iVar7 + 0x1D950) = 0;
                *(unsigned long long *)(iVar7 + 0x1D960) = 0;
                iVar7 = iVar7 + 0x50;
            } while (iVar4 < 2);
            iVar5 = iVar5 + 1;
            iVar8 = iVar8 + 0x50;
            iVar3 = iVar3 + 0xA0;
        } while (iVar5 < 9);
        *(unsigned long long *)(iVar2 + 0x1DEE8) = 0xE080808;
        *(unsigned long long *)(iVar2 + 0x1DEF8) = 0xFF80988;
        *(unsigned long long *)(iVar2 + 0x1D948) = *(unsigned long long *)(iVar2 + 0x1DEE8);
        *(unsigned long long *)(iVar2 + 0x1D958) = *(unsigned long long *)(iVar2 + 0x1DEF8);
        *(unsigned long long *)(iVar2 + 0x1D998) = *(unsigned long long *)(iVar2 + 0x1DEE8);
        *(unsigned long long *)(iVar2 + 0x1D9A8) = *(unsigned long long *)(iVar2 + 0x1DEF8);
        *(unsigned long long *)(iVar2 + 0x1DF38) = 0xE080988;
        *(unsigned long long *)(iVar2 + 0x1DF48) = 0xFF80B08;
        *(unsigned long long *)(iVar2 + 0x1D9E8) = *(unsigned long long *)(iVar2 + 0x1DF38);
        *(unsigned long long *)(iVar2 + 0x1D9F8) = *(unsigned long long *)(iVar2 + 0x1DF48);
        *(unsigned long long *)(iVar2 + 0x1DA38) = *(unsigned long long *)(iVar2 + 0x1DF38);
        *(unsigned long long *)(iVar2 + 0x1DA48) = *(unsigned long long *)(iVar2 + 0x1DF48);
        *(unsigned long long *)(iVar2 + 0x1DF88) = 0xE080B08;
        *(unsigned long long *)(iVar2 + 0x1DF98) = 0xFF80C88;
        *(unsigned long long *)(iVar2 + 0x1DA88) = *(unsigned long long *)(iVar2 + 0x1DF88);
        *(unsigned long long *)(iVar2 + 0x1DA98) = *(unsigned long long *)(iVar2 + 0x1DF98);
        iStack_20 = iStack_20 + 4;
        iStack_30 = iStack_30 + 1;
        *(unsigned long long *)(iVar2 + 0x1DAD8) = *(unsigned long long *)(iVar2 + 0x1DF88);
        *(unsigned long long *)(iVar2 + 0x1DAE8) = *(unsigned long long *)(iVar2 + 0x1DF98);
        *(unsigned long long *)(iVar2 + 0x1DFD8) = 0xE080988;
        *(unsigned long long *)(iVar2 + 0x1DFE8) = 0xFF80B08;
        *(unsigned long long *)(iVar2 + 0x1DB28) = *(unsigned long long *)(iVar2 + 0x1DFD8);
        *(unsigned long long *)(iVar2 + 0x1DB38) = *(unsigned long long *)(iVar2 + 0x1DFE8);
        *(unsigned long long *)(iVar2 + 0x1DB78) = *(unsigned long long *)(iVar2 + 0x1DFD8);
        *(unsigned long long *)(iVar2 + 0x1DB88) = *(unsigned long long *)(iVar2 + 0x1DFE8);
        *(unsigned long long *)(iVar2 + 0x1E028) = 0xE080808;
        *(unsigned long long *)(iVar2 + 0x1E038) = 0xFF80988;
        *(unsigned long long *)(iVar2 + 0x1DBC8) = *(unsigned long long *)(iVar2 + 0x1E028);
        *(unsigned long long *)(iVar2 + 0x1DBD8) = *(unsigned long long *)(iVar2 + 0x1E038);
        *(unsigned long long *)(iVar2 + 0x1DC18) = *(unsigned long long *)(iVar2 + 0x1E028);
        *(unsigned long long *)(iVar2 + 0x1DC28) = *(unsigned long long *)(iVar2 + 0x1E038);
        *(unsigned long long *)(iVar2 + 0x1E078) = 0xE080C88;
        *(unsigned long long *)(iVar2 + 0x1E088) = 0xFF80E08;
        *(unsigned long long *)(iVar2 + 0x1DC68) = *(unsigned long long *)(iVar2 + 0x1E078);
        *(unsigned long long *)(iVar2 + 0x1DC78) = *(unsigned long long *)(iVar2 + 0x1E088);
        *(unsigned long long *)(iVar2 + 0x1DCB8) = *(unsigned long long *)(iVar2 + 0x1E078);
        *(unsigned long long *)(iVar2 + 0x1DCC8) = *(unsigned long long *)(iVar2 + 0x1E088);
        *(unsigned long long *)(iVar2 + 0x1E0C8) = 0xE080E08;
        *(unsigned long long *)(iVar2 + 0x1E0D8) = 0xFF80F88;
        *(unsigned long long *)(iVar2 + 0x1DD08) = *(unsigned long long *)(iVar2 + 0x1E0C8);
        *(unsigned long long *)(iVar2 + 0x1DD18) = *(unsigned long long *)(iVar2 + 0x1E0D8);
        *(unsigned long long *)(iVar2 + 0x1DD58) = *(unsigned long long *)(iVar2 + 0x1E0C8);
        *(unsigned long long *)(iVar2 + 0x1DD68) = *(unsigned long long *)(iVar2 + 0x1E0D8);
    } while (iStack_30 < 2);
}

/* 0x001FA710, 0x74 bytes. */
void func_001FA710(void)
{
    u8 * iVar1;

    iVar1 = (u8 *)PS2_PTR(*(u32 *)g_00732500);
    *(u32 *)(g_00732500 + 0xE4) = 0;
    *(unsigned long long *)((*(u32 *)(g_00732500)) + 0x1AE90) = 0;
    *(unsigned long long *)(iVar1 + 0x1AEA0) = 0;
    iVar1 = (u8 *)PS2_PTR(*(u32 *)g_00732500);
    *(unsigned long long *)((*(u32 *)(g_00732500)) + 0x1AEE0) = 0;
    *(unsigned long long *)(iVar1 + 0x1AEF0) = 0;
    iVar1 = (u8 *)PS2_PTR(*(u32 *)(g_00732500 + 0x4));
    *(unsigned long long *)((*(u32 *)(g_00732500 + 0x4)) + 0x1AE90) = 0;
    *(unsigned long long *)(iVar1 + 0x1AEA0) = 0;
    iVar1 = (u8 *)PS2_PTR(*(u32 *)(g_00732500 + 0x4));
    *(unsigned long long *)((*(u32 *)(g_00732500 + 0x4)) + 0x1AEE0) = 0;
    *(unsigned long long *)(iVar1 + 0x1AEF0) = 0;
}

/* 0x001FE3E0, 0x150 bytes. */
void func_001FE3E0(u32 *param_1, int param_2, int param_3)
{
    int cVar2;
    long long lVar3;
    u8 * pbVar5;
    u32 uVar1;
    u32 uVar4;

    do {
        if (param_1 == (u32 *)0) {
            return;
        }
        uVar1 = *param_1;
        uVar4 = 1 << (uVar1 & 7);
        pbVar5 = (u8 *)(&g_700001E0 + (uVar1 >> 3));
        if (((uVar4 & 0xFF & (u32)*pbVar5) == 0) &&
              (((param_3 != 0 ||
                  (cVar2 = func_001FF100(*(u16 *)(g_700001D0 + uVar1 * 0x70 + 0x54), 3), cVar2 == -1))
                && (param_2 == *(u8 *)(g_700001D0 + uVar1 * 0x70 + 0x60))))) {
            lVar3 = func_001F4FF0(uVar1, g_7000088C);
            if (lVar3 == 0) {
                if (param_3 == 0) {
                    func_001FDD90(uVar1, 1);
                }
                else {
                    lVar3 = func_001FE030(uVar1, param_2);
                    if (lVar3 == 0) goto LAB_001fe500;
                }
            }
            *pbVar5 = *pbVar5 | (u8)uVar4;
        }
LAB_001fe500:
        param_1 = (u32 *)param_1[1];
    } while( true );
}

/* 0x001FE650, 0x3C0 bytes. */
void func_001FE650(int param_1)
{
    int bVar1;
    int iVar11;
    int iVar2;
    int iVar6;
    long long lVar4;
    u8 * pbVar13;
    u32 uVar10;
    u32 uVar12;
    unsigned long long uVar3;
    unsigned long long uVar5;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    iVar2 = g_7000088C * 4;
    pbVar13 = (u8 *)(&g_70000B90 + iVar2);
    uVar3 = PS2_ADDR(func_001912B0(0));
    uVar8 = (u32)*pbVar13;
    uVar7 = (u32)(u8)(&g_70000B91)[iVar2];
    uVar12 = (u32)(u8)(&g_70000B92)[iVar2];
    bVar1 = (&g_70000B93)[iVar2];
    uVar10 = (u32)bVar1;
    uVar9 = (u32)(u8)(&g_70000B92)[iVar2];
    if (*(float *)(g_0045D2C0 + 0x1E8) < 0.0) {
        if (*(float *)(g_0045D2C0 + 0x1E0) < 0.0) {
            if (uVar7 < uVar10) {
                iVar11 = g_7000088C * 0x60;
                do {
                    uVar9 = uVar8;
                    if (uVar8 < uVar12) {
                        do {
                            if (((1 << (uVar9 - *pbVar13 & 0x1F) &
                                      *(u32 *)(&g_70000BA0 + (uVar7 - (u8)(&g_70000B91)[iVar2]) * 4 + iVar11))
                                      != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar9, uVar7), lVar4 != 0)) {
                                uVar5 = func_00194590(uVar9, uVar7);
                                func_001FE330((u32 *)PS2_PTR(uVar5), param_1);
                            }
                            uVar9 = uVar9 + 1;
                        } while ((int)uVar9 < (int)uVar12);
                    }
                    uVar7 = uVar7 + 1;
                } while ((int)uVar7 < (int)uVar10);
            }
        }
        else if (uVar7 < uVar10) {
            iVar11 = g_7000088C * 0x60;
            uVar12 = uVar9;
            do {
                while (uVar12 = uVar12 - 1, (int)uVar8 <= (int)uVar12) {
                    if (((1 << (uVar12 - *pbVar13 & 0x1F) &
                              *(u32 *)(&g_70000BA0 + (uVar7 - (u8)(&g_70000B91)[iVar2]) * 4 + iVar11)) != 0)
                          && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar12, uVar7), lVar4 != 0)) {
                        uVar5 = func_00194590(uVar12, uVar7);
                        func_001FE330((u32 *)PS2_PTR(uVar5), param_1);
                    }
                }
                uVar7 = uVar7 + 1;
                uVar12 = uVar9;
            } while ((int)uVar7 < (int)uVar10);
        }
    }
    else if (*(float *)(g_0045D2C0 + 0x1E0) < 0.0) {
        iVar11 = bVar1 - 1;
        if ((int)uVar7 <= iVar11) {
            iVar6 = g_7000088C * 0x60;
            do {
                uVar10 = uVar8;
                if (uVar8 < uVar12) {
                    do {
                        if (((1 << (uVar10 - *pbVar13 & 0x1F) &
                                  *(u32 *)(&g_70000BA0 + (iVar11 - (u32)(u8)(&g_70000B91)[iVar2]) * 4 + iVar6
                                                    )) != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar10, iVar11), lVar4 != 0)) {
                            uVar5 = func_00194590(uVar10, iVar11);
                            func_001FE330((u32 *)PS2_PTR(uVar5), param_1);
                        }
                        uVar10 = uVar10 + 1;
                    } while ((int)uVar10 < (int)uVar12);
                }
                iVar11 = iVar11 + -1;
            } while ((int)uVar7 <= iVar11);
        }
    }
    else {
        iVar11 = bVar1 - 1;
        if ((int)uVar7 <= iVar11) {
            iVar6 = g_7000088C * 0x60;
            uVar10 = uVar9;
            do {
                while (uVar10 = uVar10 - 1, (int)uVar8 <= (int)uVar10) {
                    if (((1 << (uVar10 - *pbVar13 & 0x1F) &
                              *(u32 *)(&g_70000BA0 + (iVar11 - (u32)(u8)(&g_70000B91)[iVar2]) * 4 + iVar6))
                              != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar10, iVar11), lVar4 != 0)) {
                        uVar5 = func_00194590(uVar10, iVar11);
                        func_001FE330((u32 *)PS2_PTR(uVar5), param_1);
                    }
                }
                iVar11 = iVar11 + -1;
                uVar10 = uVar9;
            } while ((int)uVar7 <= iVar11);
        }
    }
}

/* 0x001FEA10, 0x3F0 bytes. */
void func_001FEA10(int param_1, int param_2)
{
    int bVar1;
    int iVar10;
    int iVar2;
    int iVar6;
    long long lVar4;
    u8 * pbVar13;
    u32 uVar11;
    u32 uVar12;
    unsigned long long uVar3;
    unsigned long long uVar5;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    iVar2 = g_7000088C * 4;
    pbVar13 = (u8 *)(&g_70000B90 + iVar2);
    uVar3 = PS2_ADDR(func_001912B0(param_1));
    uVar11 = (u32)*pbVar13;
    uVar7 = (u32)(u8)(&g_70000B91)[iVar2];
    uVar12 = (u32)(u8)(&g_70000B92)[iVar2];
    bVar1 = (&g_70000B93)[iVar2];
    uVar9 = (u32)bVar1;
    uVar8 = (u32)(u8)(&g_70000B92)[iVar2];
    if (*(float *)(g_0045D2C0 + 0x1E8) < 0.0) {
        if (*(float *)(g_0045D2C0 + 0x1E0) < 0.0) {
            if (uVar7 < uVar9) {
                iVar10 = g_7000088C * 0x60;
                do {
                    uVar8 = uVar11;
                    if (uVar11 < uVar12) {
                        do {
                            if (((1 << (uVar8 - *pbVar13 & 0x1F) &
                                      *(u32 *)(&g_70000BA0 + (uVar7 - (u8)(&g_70000B91)[iVar2]) * 4 + iVar10))
                                      != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar8, uVar7), lVar4 != 0)) {
                                uVar5 = func_001945B0(param_1, uVar8, uVar7);
                                func_001FE330((u32 *)PS2_PTR(uVar5), param_2);
                            }
                            uVar8 = uVar8 + 1;
                        } while ((int)uVar8 < (int)uVar12);
                    }
                    uVar7 = uVar7 + 1;
                } while ((int)uVar7 < (int)uVar9);
            }
        }
        else if (uVar7 < uVar9) {
            iVar10 = g_7000088C * 0x60;
            uVar12 = uVar8;
            do {
                while (uVar12 = uVar12 - 1, (int)uVar11 <= (int)uVar12) {
                    if (((1 << (uVar12 - *pbVar13 & 0x1F) &
                              *(u32 *)(&g_70000BA0 + (uVar7 - (u8)(&g_70000B91)[iVar2]) * 4 + iVar10)) != 0)
                          && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar12, uVar7), lVar4 != 0)) {
                        uVar5 = func_001945B0(param_1, uVar12, uVar7);
                        func_001FE330((u32 *)PS2_PTR(uVar5), param_2);
                    }
                }
                uVar7 = uVar7 + 1;
                uVar12 = uVar8;
            } while ((int)uVar7 < (int)uVar9);
        }
    }
    else if (*(float *)(g_0045D2C0 + 0x1E0) < 0.0) {
        iVar10 = bVar1 - 1;
        if ((int)uVar7 <= iVar10) {
            iVar6 = g_7000088C * 0x60;
            do {
                uVar9 = uVar11;
                if (uVar11 < uVar12) {
                    do {
                        if (((1 << (uVar9 - *pbVar13 & 0x1F) &
                                  *(u32 *)(&g_70000BA0 + (iVar10 - (u32)(u8)(&g_70000B91)[iVar2]) * 4 + iVar6
                                                    )) != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar9, iVar10), lVar4 != 0)) {
                            uVar5 = func_001945B0(param_1, uVar9, iVar10);
                            func_001FE330((u32 *)PS2_PTR(uVar5), param_2);
                        }
                        uVar9 = uVar9 + 1;
                    } while ((int)uVar9 < (int)uVar12);
                }
                iVar10 = iVar10 + -1;
            } while ((int)uVar7 <= iVar10);
        }
    }
    else {
        iVar10 = bVar1 - 1;
        if ((int)uVar7 <= iVar10) {
            iVar6 = g_7000088C * 0x60;
            uVar9 = uVar8;
            do {
                while (uVar9 = uVar9 - 1, (int)uVar11 <= (int)uVar9) {
                    if (((1 << (uVar9 - *pbVar13 & 0x1F) &
                              *(u32 *)(&g_70000BA0 + (iVar10 - (u32)(u8)(&g_70000B91)[iVar2]) * 4 + iVar6))
                              != 0) && (lVar4 = func_001912E0((u8 *)PS2_PTR(uVar3), uVar9, iVar10), lVar4 != 0)) {
                        uVar5 = func_001945B0(param_1, uVar9, iVar10);
                        func_001FE330((u32 *)PS2_PTR(uVar5), param_2);
                    }
                }
                iVar10 = iVar10 + -1;
                uVar9 = uVar8;
            } while ((int)uVar7 <= iVar10);
        }
    }
}

/* 0x001FF6E0, 0x80 bytes. */
void func_001FF6E0(int param_1, u32 *param_2)
{
    int iVar4;
    int iVar5;
    u16 * puVar1;
    u32 * puVar2;
    u32 * puVar3;

    iVar5 = 1;
    if (1 < param_1) {
        puVar3 = param_2;
        do {
            puVar3 = puVar3 + 1;
            iVar4 = iVar5 + -1;
            puVar1 = (u16 *)*puVar3;
            if (-1 < iVar4) {
                puVar2 = param_2 + iVar4;
                do {
                    puVar2[1] = *puVar2;
                    if (*(u16 *)*puVar2 <= *puVar1) break;
                    iVar4 = iVar4 + -1;
                    puVar2 = puVar2 + -1;
                } while (-1 < iVar4);
            }
            iVar5 = iVar5 + 1;
            param_2[iVar4 + 1] = PS2_ADDR(puVar1);
        } while (iVar5 < param_1);
    }
}

/* 0x002045E0, 0x338 bytes. */
void func_002045E0(u8 *param_1)
{
    int bVar1;
    int bVar9;
    u8 * iVar2;
    u8 * iVar8;
    long long lVar6;
    unsigned long long uStack_8;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar7;

    iVar8 = param_1;
    iVar2 = (u8 *)PS2_PTR(*(int *)(iVar8 + 0x14));
    bVar1 = *(u8 *)(iVar8 + 0x7D);
    if (*(short *)(iVar8 + 0x78) != 0) {
        *(short *)(iVar8 + 0x78) = *(short *)(iVar8 + 0x78) + -1;
    }
    if ((*(u32 *)(iVar8 + 0xB8) & 0xC) == 0) {
        func_002036F0(param_1);
    }
    uVar7 = *(u32 *)(iVar8 + 0xBC);
    if ((uVar7 & 0x10) == 0) {
        if ((uVar7 & 0x20) != 0) {
            *(u32 *)(iVar8 + 0xBC) = uVar7 & 0xFFFFFFDF;
            *(u32 *)(iVar2 + 0x13C) = 0;
            uVar5 = g_700000CC;
            uVar4 = g_700000C8;
            uVar3 = g_700000C4;
            *(u32 *)(iVar2 + 0x1D0) = g_700000C0;
            *(u32 *)(iVar2 + 0x1D4) = uVar3;
            *(u32 *)(iVar2 + 0x1D8) = uVar4;
            *(u32 *)(iVar2 + 0x1DC) = uVar5;
        }
    }
    else {
        *(u32 *)(iVar8 + 0xBC) = uVar7 & 0xFFFFFFEF;
        *(u32 *)(iVar8 + 0xBC) = uVar7 & 0xFFFFFFEF | 0x20;
    }
    if (*(short *)(iVar8 + 0x82) < *(short *)(iVar8 + 0x84)) {
        *(short *)(iVar8 + 0x84) = *(short *)(iVar8 + 0x84) + -1;
    }
    if (bVar1 == 1) {
        if (*(u16 *)(iVar2 + 0x188) < 0x96) {
            if ((*(u16 *)(iVar2 + 0x188) == 0xFA) && (lVar6 = func_0016CB20(iVar2), lVar6 == 0)) {
                func_00204B60(param_1, 0x100020);
            }
        }
        else {
            func_00191200((float *)((u8 *)(&uStack_8)), (float *)PS2_PTR(*(int *)(iVar8 + 0x14) + 0x40));
            *(unsigned long long *)(iVar8 + 0x30) = uStack_8;
            *(u16 *)(iVar2 + 0x188) = 0;
            uVar7 = *(u32 *)(iVar8 + 0xBC) & 0xFFFFFFFD;
            *(u32 *)(iVar8 + 0xBC) = uVar7;
            *(u32 *)(iVar8 + 0xBC) = uVar7 | 4;
        }
    }
    if ((*(u32 *)(iVar8 + 0xB8) & 0x8400) != 0) {
        if ((*(u32 *)(iVar8 + 0xB8) & 0x8000) == 0) {
            return;
        }
        func_002D7AD0(param_1);
        return;
    }
    if (2 < bVar1) {
        func_00203660(param_1);
        return;
    }
    lVar6 = func_00202610(param_1);
    if (lVar6 == 0) {
        if ((*(u32 *)(iVar8 + 0xBC) & 0x100000) == 0) {
            if ((*(u32 *)(iVar8 + 0xB8) & 0x60) == 0) {
                bVar1 = *(u8 *)(*(int *)(iVar8 + 0x68) + 0x1C);
                bVar9 = false;
                if ((7 < bVar1) && (bVar1 < 0xC)) {
                    bVar9 = true;
                }
                if (!bVar9) goto LAB_00204800;
                lVar6 = func_00202EB0(param_1);
            }
            else {
                lVar6 = func_00202F40(param_1);
            }
            if (lVar6 != 0) {
                return;
            }
            goto LAB_00204800;
        }
        func_00238630(param_1, bVar1);
        uVar7 = *(u32 *)(iVar8 + 0xB8);
    }
    else {
LAB_00204800:
        uVar7 = *(u32 *)(iVar8 + 0xB8);
    }
    if ((uVar7 & 0x2000) == 0) {
        if ((((*(int *)(iVar8 + 0xC) == 0) && ((*(u32 *)(iVar8 + 0xBC) & 0x200) == 0)) &&
                (uVar7 = *(u32 *)(*(int *)(iVar2 + 0x210) + 0x18), (uVar7 & 0x800) == 0)) &&
              (((uVar7 & 0x20) == 0 &&
                ((*(char *)(iVar8 + 0x7D) == 0 || ((*(u32 *)(iVar8 + 0xBC) & 1) != 0)))))) {
            func_00202000(param_1);
        }
    }
    else {
        uVar7 = *(u32 *)(*(int *)(iVar8 + 0x68) + 0x28);
        if ((uVar7 & 0x20) != 0) {
            func_002B1BB0(param_1);
            uVar7 = *(u32 *)(iVar8 + 0xB8);
            goto LAB_002048ec;
        }
        if ((uVar7 & 8) == 0) {
            if ((uVar7 & 0x40) == 0) {
                if ((uVar7 & 0x80) != 0) {
                    func_002B29B0(param_1);
                }
            }
            else {
                func_002B20A0(param_1);
            }
        }
        else {
            func_002B3940(param_1);
        }
    }
    uVar7 = *(u32 *)(iVar8 + 0xB8);
LAB_002048ec:
    if ((uVar7 & 0x1000) == 0) {
        func_00202410(param_1);
    }
}

/* 0x0020FA20, 0x48 bytes. */
int func_0020FA20(int param_1)
{
    u32 auStack_c0[48];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 uVar1;

    puVar3 = auStack_c0;
    puVar4 = (u32 *)(g_0040D630);
    iVar2 = 0x18;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    return auStack_c0[param_1];
}

/* 0x00218070, 0x7C bytes. */
void func_00218070(int param_1)
{
    int iVar1;

    func_00218670(param_1, *(u32 *)g_0045D488, 3);
    iVar1 = (int)param_1 * 4;
    *(u32 *)(g_0073E0E0 + iVar1) = 0;
    *(u32 *)(g_0073E160 + iVar1) = 0x3F800000;
    *(u32 *)(g_007404B0 + iVar1) = 0;
    *(u8 *)(g_0073E020 + param_1) = 1;
}
/* MISSING ['0x45d488'] */

/* 0x00218F30, 0x80 bytes. */
int func_00218F30(void)
{
    int iVar1;
    u8 * iVar2;

    iVar1 = 0;
    if (g_0045D490 < 4) {
        iVar1 = g_0045D490 * 0x1D00 + 0x740530;
        g_0045CDAC = g_0045CDAC + -1;
        *(u32 *)(g_0045D490 * 0x1D00 + 0x74053C) = 1;
        if (g_0045D490 < 4) {
            iVar2 = (u8 *)PS2_PTR(iVar1);
            do {
                if (*(int *)(iVar2 + 0xC) == 0) {
                    return iVar1;
                }
                g_0045D490 = g_0045D490 + 1;
                iVar2 = iVar2 + 0x1D00;
            } while (g_0045D490 < 4);
        }
    }
    return iVar1;
}

/* 0x00228460, 0x80 bytes. */
int func_00228460(void)
{
    int bVar1;
    int * piVar2;
    int * piVar3;

    piVar2 = (int *)0;
    if (*(u32 *)g_0045D4A0 < 2) {
        bVar1 = *(u32 *)g_0045D4A0 < 2;
        piVar2 = (int *)(*(u32 *)g_0045D4A0 * 0x160 + 0x749D40);
        *piVar2 = 1;
        if (bVar1) {
            piVar3 = piVar2;
            do {
                if (*piVar3 == 0) {
                    *(u32 *)(g_0045CDB8) = *(u32 *)(g_0045CDB8) + -1;
                    return PS2_ADDR(piVar2);
                }
                *(u32 *)(g_0045D4A0) = *(u32 *)(g_0045D4A0) + 1;
                piVar3 = piVar3 + 0x58;
            } while (*(u32 *)g_0045D4A0 < 2);
        }
    }
    return PS2_ADDR(piVar2);
}
/* MISSING ['0x45cdb8', '0x45d4a0'] */

/* 0x0022B3C0, 0x438 bytes. */
int func_0022B3C0(u8 *param_1, unsigned long long *param_2)
{
    int iVar1;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    long long lVar3;
    int * piVar9;
    u32 * puVar10;
    u32 * puVar7;
    u32 uVar11;
    u32 uVar2;
    u32 uVar8;

    uVar11 = 0;
    iVar5 = 0;
    puVar10 = (u32 *)0;
    iVar6 = param_1;
    *(u32 *)(iVar6 + 0x20) = 0;
    *(u32 *)(iVar6 + 0x24) = 0;
    do {
        if (4 < uVar11) {
            return 0;
        }
        piVar9 = (int *)PS2_PTR(*(ps2ptr *)(iVar6 + 0xC));
        if (piVar9 != (int *)0) {
            uVar8 = 0;
            do {
                if (0x80 < uVar8) {
                    return 0;
                }
                puVar10 = (u32 *)piVar9[1];
                lVar3 = func_0022A480(param_1, piVar9);
                if (lVar3 != 0) {
                    iVar5 = 1;
                    iVar1 = *(int *)(puVar10[1] + (u32)*(u8 *)(piVar9 + 3) * 0x10 + 0x14);
                    iVar4 = *(int *)(puVar10[2] + (u32)*(u8 *)((int)piVar9 + 0xD) * 0x10 + 0x14);
                    *(u8 *)(param_2 + 3) = *(u8 *)(param_2 + 3) & 0xFE;
                    *(u32 *)((int)param_2 + 0xC) = 0;
                    *(int *)((int)param_2 + 0x14) = iVar1;
                    if (iVar1 == iVar4) {
                        *(u32 *)(param_2 + 2) = 0;
                    }
                    else {
                        *(int *)(param_2 + 2) = iVar4;
                        *(u8 *)((int)param_2 + 0xB) =
                                  *(u8 *)((int)param_2 + 0xB) & 0xF0 | *(u8 *)((int)piVar9 + 0xE) & 0xF;
                        iVar4 = iVar4 - *(int *)(*(int *)puVar10[2] + 4);
                        if (iVar4 < 0) {
                            iVar4 = iVar4 + 0xF;
                        }
                        *(u8 *)((int)param_2 + 0xB) =
                                  *(u8 *)((int)param_2 + 0xB) & 0xF | (u8)((iVar4 >> 4 & 0xfU) << 4);
                    }
                    *(char *)(param_2 + 1) = (char)((int)*(float *)(iVar6 + 0x18) / 5000);
                    *(char *)((int)param_2 + 9) = (char)((int)*(float *)(iVar6 + 0x1C) / 5000);
                    *param_2 = *(unsigned long long *)(iVar6 + 0x18);
                    break;
                }
                piVar9 = (int *)*piVar9;
                uVar8 = uVar8 + 1;
            } while (piVar9 != (int *)0);
        }
        if ((iVar5 != 0) || (*(int *)(iVar6 + 8) == 0)) {
            if ((iVar5 == 0) && (puVar10 != (u32 *)0)) {
                *(u32 *)((int)param_2 + 0xC) = 0;
                if (*(int *)(iVar6 + 0x20) == 0) {
                    for (puVar7 = (u32 *)((u32 *)puVar10[1])[1];
                            (puVar7 != (u32 *)0 && (puVar7[3] == 1)); puVar7 = (u32 *)*puVar7) {
                    }
                    if (puVar7 == (u32 *)0) {
                        uVar2 = func_0022A5E0(*(u32 *)puVar10[1], iVar6 + 0x10);
                        *(u32 *)((int)param_2 + 0x14) = uVar2;
                    }
                    else {
                        *(u32 *)((int)param_2 + 0x14) = puVar7[1];
                    }
                    for (puVar7 = (u32 *)PS2_PTR(*(ps2ptr *)(puVar10[2] + 4));
                            (puVar7 != (u32 *)0 && (puVar7[3] == 1)); puVar7 = (u32 *)*puVar7) {
                    }
                }
                else {
                    *(int *)((int)param_2 + 0x14) = *(int *)(iVar6 + 0x20);
                    puVar7 = (u32 *)0;
                    puVar10 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar6 + 0x24));
                }
                if (puVar7 != (u32 *)0) {
                    *(u32 *)(param_2 + 2) = puVar7[1];
                }
                else {
                    uVar2 = func_0022A5E0(*(u32 *)puVar10[2], iVar6 + 0x18);
                    *(u32 *)(param_2 + 2) = uVar2;
                }
                *(u8 *)(param_2 + 3) = *(u8 *)(param_2 + 3) & 0xFE;
                if (*(int *)((int)param_2 + 0x14) == *(int *)(param_2 + 2)) {
                    *(u32 *)(param_2 + 2) = 0;
                    if (puVar7 == (u32 *)0) {
                        *(u8 *)(param_2 + 3) = *(u8 *)(param_2 + 3) & 0xFE | 1;
                    }
                }
                else {
                    *(u8 *)((int)param_2 + 0xB) =
                              *(u8 *)((int)param_2 + 0xB) & 0xF0 | (u8)puVar10[3] & 0xF;
                    iVar5 = *(int *)(param_2 + 2) - *(int *)(*(int *)puVar10[2] + 4);
                    if (iVar5 < 0) {
                        iVar5 = iVar5 + 0xF;
                    }
                    *(u8 *)((int)param_2 + 0xB) =
                              *(u8 *)((int)param_2 + 0xB) & 0xF | (u8)((iVar5 >> 4 & 0xfU) << 4);
                }
                iVar5 = 1;
                *(char *)(param_2 + 1) = (char)((int)*(float *)(iVar6 + 0x18) / 5000);
                *(char *)((int)param_2 + 9) = (char)((int)*(float *)(iVar6 + 0x1C) / 5000);
                *param_2 = *(unsigned long long *)(iVar6 + 0x18);
            }
            return iVar5;
        }
        *(u32 *)(iVar6 + 4) = 0;
        *(u32 *)(iVar6 + 0xC) = 0;
        puVar10 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar6 + 8));
        func_0022A200(param_1, puVar10);
        *(u32 *)(iVar6 + 8) = *puVar10;
        uVar2 = func_00229E50(*(u32 *)(iVar6 + 0xC), 0x229F60);
        *(u32 *)(iVar6 + 0xC) = uVar2;
        uVar11 = uVar11 + 1;
    } while( true );
}

/* 0x0022DBE0, 0x60 bytes. */
int func_0022DBE0(int param_1)
{
    long long lVar2;
    u8 * puVar1;

    lVar2 = func_0022DC70();
    if (param_1 < lVar2) {
        puVar1 = (u8 *)((int)param_1 * 0x40 + *(u32 *)g_0074A008 * 0x40 + 0x74A1A0);
    }
    else {
        puVar1 = g_0042A390;
    }
    return PS2_ADDR(puVar1);
}

/* 0x002371C0, 0x34 bytes. */
void func_002371C0(int param_1)
{
    long long lVar1;

    lVar1 = func_00236F30((u8 *)PS2_PTR(param_1));
    if (lVar1 != 0) {
        func_00236ED0((u8 *)PS2_PTR(param_1));
    }
}

/* 0x00238E80, 0xC8 bytes. */
void func_00238E80(u8 *param_1, int param_2)
{
    u8 * iVar2;
    long long lVar1;
    long long lVar3;

    iVar2 = param_1;
    if ((*(u32 *)(iVar2 + 0xB8) & 0x10200) == 0) {
        if (param_2 == 0) {
            lVar3 = 2;
        }
        else {
            lVar3 = 5;
        }
        lVar1 = func_00174A40(300.0f, (u8 *)PS2_PTR(*(int *)(iVar2 + 0x14) + 0x40), iVar2 + 0x20);
        if (lVar3 <= lVar1) goto LAB_00238ef4;
    }
    lVar3 = func_00238C90(PS2_ADDR(param_1), 0);
    if (lVar3 != 0) {
        return;
    }
LAB_00238ef4:
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    func_00238AE0(param_1, (g_7000015C >> 0x10) % 0x3C + 0x3C);
}

/* 0x0023B020, 0x2F0 bytes. */
void func_0023B020(void)
{
    int iVar1;
    int iVar5;
    int iVar6;
    int * piVar4;
    unsigned long long uVar2;
    u32 uVar3;

    uVar2 = func_00117B90();
    *(u32 *)(g_0074B7D0) = (int)uVar2;
    func_001026D0(1, 0x567, (void *)PS2_PTR(uVar2 | 3), 1, 0, 0, (char *)PS2_PTR(0x43D070), 0x35A);
    *(u32 *)(g_0074B7D0) = *(u32 *)(g_0074B7D0) + 0x2A800;
    *(u32 *)(g_0074B7D0 + 0x4) = 0;
    func_0023B530(*(u8 *)g_00669DB3);
    func_0023ABC0();
    iVar5 = 0;
    piVar4 = (int *)(g_0040E9E0);
    iVar6 = 0;
    do {
        if (iVar6 == 0) {
            uVar3 = 0;
        }
        else {
            uVar3 = 1;
            if ((iVar6 != 1) && (uVar3 = 2, iVar6 != 2)) {
                if ((iVar6 == 3) || (iVar6 == 8)) {
                    uVar3 = 4;
                }
                else if ((iVar6 == 4) || ((0x65 < iVar6 && (iVar6 < 0x7E)))) {
                    uVar3 = 5;
                }
                else if ((iVar6 == 5) || ((0x7D < iVar6 && (iVar6 < 0x99)))) {
                    uVar3 = 6;
                }
                else if ((iVar6 == 6) || ((0x98 < iVar6 && (iVar6 < 0xB0)))) {
                    uVar3 = 7;
                }
                else if ((iVar6 == 7) || ((0xAF < iVar6 && (iVar6 < 0xCB)))) {
                    uVar3 = 8;
                }
                else if ((iVar6 < 9) || (0x32 < iVar6)) {
                    if ((iVar6 < 0x4F) || (0x54 < iVar6)) {
                        if ((iVar6 < 0x55) || (0x59 < iVar6)) {
                            if (((iVar6 < 0x33) || ((0x65 < iVar6 || ((0x4E < iVar6 && (iVar6 < 0x55)))))) ||
                                  ((0x54 < iVar6 && (iVar6 < 0x5A)))) {
                                uVar3 = 0;
                            }
                            else {
                                uVar3 = 10;
                            }
                        }
                        else {
                            uVar3 = 3;
                        }
                    }
                    else {
                        uVar3 = 10;
                    }
                }
                else {
                    uVar3 = 9;
                }
            }
        }
        piVar4[7] = uVar3;
        if (uVar3 < 4) {
            iVar1 = func_00117B20(uVar3, (u32 *)(piVar4));
            piVar4[8] = iVar1;
            *piVar4 = iVar5 + 0x7010;
            iVar5 = iVar5 + piVar4[6];
            func_0023AE30(iVar6, 1);
        }
        else {
            piVar4[8] = 0xF;
        }
        iVar6 = iVar6 + 1;
        piVar4 = piVar4 + 9;
    } while (iVar6 < 0xCB);
    *(u32 *)(g_0074B7D0 + 0x18) = 0;
    *(u32 *)(g_0074B7D0 + 0x14) = 0x110000;
}

/* 0x00246750, 0x40 bytes. */
void func_00246750(void)
{
    int iVar2;
    u32 * puVar1;
    u32 * puVar3;

    iVar2 = 0x7F;
    g_0045D4E8 = 0x752B50;
    puVar3 = (u32 *)0x752B50;
    do {
        puVar1 = puVar3 + 2;
        iVar2 = iVar2 + -1;
        *puVar3 = PS2_ADDR(puVar1);
        puVar3 = puVar1;
    } while (iVar2 != 0);
    *puVar1 = 0;
}

/* 0x002467D0, 0x84 bytes. */
void func_002467D0(u8 *param_1)
{
    u32 * puVar1;
    u32 uVar2;

    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(param_1 + 0x10));
    uVar2 = func_001FF100(*(u16 *)(*(int *)(param_1 + 0x14) + 0x54), 0xB);
    if ((*(u32 *)(g_00412C60 + (uVar2 & 0xFF) * 4) & 0x4000) == 0) {
        *(u8 *)(*(int *)(param_1 + 0x14) + 0x68) = 0;
    }
    else {
        *(u8 *)(*(int *)(param_1 + 0x14) + 0x68) = 2;
    }
    *puVar1 = g_0045D4E8;
    g_0045D4E8 = PS2_ADDR(puVar1);
}

/* 0x00248EB0, 0x1F0 bytes. */
void func_00248EB0(void)
{
    u8 * iVar2;
    u8 * iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    u8 * iVar8;
    int iVar9;
    unsigned long long uVar1;

    iVar8 = g_00732508;
    iVar9 = 0;
    iVar7 = 0;
    *(u32 *)(g_0073255A) = 0;
    *(u32 *)(g_0073255A + 0x1) = 0;
    do {
        iVar4 = 0;
        iVar3 = g_00732220;
        *(u8 *)(g_00732550 + iVar7) = 0xFF;
        *(u8 *)(g_0073253C + iVar7) = 0x1D;
        *(u32 *)(iVar8 + 0xC) = 0xFFFFFFFF;
        *(u8 *)(g_00732546 + iVar7) = 6;
        do {
            iVar2 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2E0) + iVar9);
            func_001050B0(iVar2 + 0x16290);
            iVar5 = 0;
            *(unsigned long long *)(iVar2 + 0x162A0) = 0xDF000001FF0000;
            *(unsigned long long *)(iVar2 + 0x162A8) = 0x41;
            iVar6 = PS2_ADDR(iVar2);
            do {
                uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EE4);
                func_001057F0((u8 *)PS2_PTR(iVar6 + 0x162B0), uVar1, 1);
                iVar5 = iVar5 + 1;
                *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x162E0) = 0;
                *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x162F0) = 0;
                iVar6 = iVar6 + 0x50;
            } while (iVar5 < 2);
            iVar5 = 0;
            iVar6 = PS2_ADDR(iVar2);
            do {
                uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EE5);
                func_001057F0((u8 *)PS2_PTR(iVar6 + 0x16350), uVar1, 1);
                iVar5 = iVar5 + 1;
                *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x16380) = 0;
                *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x16390) = 0;
                iVar6 = iVar6 + 0x50;
            } while (iVar5 < 5);
            iVar6 = 0;
            do {
                uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EE6);
                func_001057F0(iVar2 + 0x164E0, uVar1, 1);
                iVar6 = iVar6 + 1;
                *(unsigned long long *)(iVar2 + 0x16510) = 0;
                *(unsigned long long *)(iVar2 + 0x16520) = 0;
                iVar2 = iVar2 + 0x50;
            } while (iVar6 < 4);
            iVar4 = iVar4 + 1;
            iVar3 = iVar3 + 4;
        } while (iVar4 < 2);
        iVar7 = iVar7 + 1;
        iVar8 = iVar8 + 4;
        iVar9 = iVar9 + 0x390;
    } while (iVar7 < 10);
}
/* MISSING ['0x73255a', '0x73255b'] */

/* 0x0024BAB0, 0x1A4 bytes. */
void func_0024BAB0(void)
{
    int iVar1;
    u8 * iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int uVar2;
    int uVar3;

    uVar3 = *(u16 *)g_00575588;
    uVar2 = *(u16 *)g_00574F58;
    g_0045D2C0 = 0x5B4BC0;
    iVar5 = *(int *)(g_70000150 * 4 + 0x732500);
    *(u32 *)(g_00732508) = 0;
    if ((*(u32 *)g_00669F60 & 2) == 0) {
        func_0024BA10(2);
    }
    else {
        func_0024BA10(0);
        func_0024B330(0, uVar3);
        g_0045D2C0 = 0x5B4E00;
        func_0024BA10(1);
        func_0024B330(1, uVar2);
    }
    iVar1 = *(int *)(g_70000150 * 4 + 0x73250C);
    if (*(u32 *)g_00732508 < iVar1) {
        iVar5 = iVar5 + *(u32 *)g_00732508 * 0x5D0;
        iVar7 = *(u32 *)g_00732508;
        do {
            iVar6 = 0;
            iVar4 = (u8 *)PS2_PTR(iVar5);
            do {
                *(unsigned long long *)(iVar4 + 0x100) = 0;
                *(unsigned long long *)(iVar4 + 0x110) = 0;
                iVar6 = iVar6 + 8;
                *(unsigned long long *)(iVar4 + 0x150) = 0;
                *(unsigned long long *)(iVar4 + 0x160) = 0;
                *(unsigned long long *)(iVar4 + 0x1A0) = 0;
                *(unsigned long long *)(iVar4 + 0x1B0) = 0;
                *(unsigned long long *)(iVar4 + 0x1F0) = 0;
                *(unsigned long long *)(iVar4 + 0x200) = 0;
                *(unsigned long long *)(iVar4 + 0x240) = 0;
                *(unsigned long long *)(iVar4 + 0x250) = 0;
                *(unsigned long long *)(iVar4 + 0x290) = 0;
                *(unsigned long long *)(iVar4 + 0x2A0) = 0;
                *(unsigned long long *)(iVar4 + 0x2E0) = 0;
                *(unsigned long long *)(iVar4 + 0x2F0) = 0;
                *(unsigned long long *)(iVar4 + 0x330) = 0;
                *(unsigned long long *)(iVar4 + 0x340) = 0;
                iVar4 = iVar4 + 0x280;
            } while (iVar6 < 0x10);
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0xB0) = 0;
            iVar7 = iVar7 + 1;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0xC0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x40) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x50) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x60) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x70) = 0;
            iVar5 = iVar5 + 0x5D0;
        } while (iVar7 < iVar1);
    }
    *(int *)(g_70000150 * 4 + 0x73250C) = (*(u32 *)(g_00732508));
}

/* 0x0025A890, 0x3C8 bytes. */
void func_0025A890(int param_1, u8 *param_2, int param_3, int param_4)
{
    u8 * iStack_10;
    u8 * iStack_40;
    int iVar3;
    int iVar4;
    int iVar6;
    u8 * iVar7;
    int iVar8;
    int iVar9;
    short * psVar10;
    int sVar1;
    int sVar2;
    unsigned long long uVar5;

    uVar5 = *(unsigned long long *)g_0068F0F0;
    *(u32 *)(param_1 * 0x1C + 0x732570) = 0;
    iVar3 = param_1 * 0x1C + 0x732570;
    uVar5 = func_00106C90(uVar5, 0x3F3C);
    func_001057F0(param_2, uVar5, 0);
    *(unsigned long long *)(param_2 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(param_2 + 0x28) = 0x3881B08;
    *(unsigned long long *)(param_2 + 0x38) = 0x7081E88;
    iVar6 = (((param_4 + 0x128) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar6 < 0) {
        iVar6 = iVar6 + 0x1FF;
    }
    iVar9 = 0;
    psVar10 = (short int *)(g_0043F530);
    *(unsigned long long *)(param_2 + 0x30) =
              (long long)((param_3 + 0x1F) * 0x10 + 0x7000) |
              (long long)(((iVar6 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFD00000000;
    *(unsigned long long *)(param_2 + 0x40) =
              (long long)((param_3 + 0x57) * 0x10 + 0x7000) |
              (long long)((((iVar6 >> 9) + 0x40) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
              0xFFFD00000000;
    iStack_40 = (u8 *)PS2_PTR(iVar3);
    iStack_10 = param_2;
    do {
        iVar8 = 0;
        sVar1 = psVar10[1];
        sVar2 = *psVar10;
        *(u8 *)((u8 *)PS2_PTR(iVar3) + iVar9 + 0x14) = 0;
        *(u32 *)(iStack_40 + 4) = 0;
        iVar4 = param_3 + 0x1F + (int)sVar2;
        iVar6 = (((param_4 + 0x128 + (int)sVar1) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar6 < 0) {
            iVar6 = iVar6 + 0x1FF;
        }
        iVar7 = iStack_10;
        do {
            uVar5 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F33);
            func_001057F0(iVar7 + 0x50, uVar5, 0);
            *(unsigned long long *)(iVar7 + 0x70) = 0x3F80000080808080;
            *(unsigned long long *)(iVar7 + 0x78) = 0xD081088;
            *(unsigned long long *)(iVar7 + 0x88) = 0xE081188;
            *(unsigned long long *)(iVar7 + 0x80) =
                      (long long)(iVar4 * 0x10 + 0x7000) |
                      (long long)(((iVar6 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFD00000000;
            *(unsigned long long *)(iVar7 + 0x90) =
                      (long long)((iVar4 + 0x10) * 0x10 + 0x7000) |
                      (long long)((((iVar6 >> 9) + 0x12) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                      0xFFFD00000000;
            if (iVar8 == 1) {
                *(unsigned long long *)(iVar7 + 0x80) = 0;
                *(unsigned long long *)(iVar7 + 0x90) = 0;
            }
            iVar8 = iVar8 + 1;
            iVar7 = iVar7 + 0x50;
        } while (iVar8 < 2);
        iVar9 = iVar9 + 1;
        iStack_40 = iStack_40 + 4;
        iStack_10 = iStack_10 + 0xA0;
        psVar10 = psVar10 + 2;
    } while (iVar9 < 4);
}

/* 0x0025B4C0, 0x3B8 bytes. */
void func_0025B4C0(u8 *param_1, int param_2, int param_3, int param_4)
{
    u8 * iStack_30;
    int iVar2;
    int iVar4;
    u8 * iVar5;
    int iVar6;
    int iVar7;
    short * psStack_40;
    int sVar1;
    unsigned long long uVar3;

    uVar3 = *(unsigned long long *)g_0068F0F0;
    *(u32 *)(param_2 * 0x1C + 0x732570) = 0;
    iVar2 = param_2 * 0x1C + 0x732570;
    uVar3 = func_00106C90(uVar3, 0x3F3C);
    func_001057F0(param_1, uVar3, 0);
    *(unsigned long long *)(param_1 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(param_1 + 0x28) = 0x3881B08;
    *(unsigned long long *)(param_1 + 0x38) = 0x7081E88;
    iVar4 = (((param_4 + 0x85) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    iVar7 = 0;
    psStack_40 = (short int *)(g_0043F540);
    *(unsigned long long *)(param_1 + 0x30) =
              (long long)(param_3 * 0x10 + 0x7000) |
              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFD00000000;
    *(unsigned long long *)(param_1 + 0x40) =
              (long long)((param_3 + 0x38) * 0x10 + 0x7000) |
              (long long)((((iVar4 >> 9) + 0x40) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
              0xFFFD00000000;
    *(unsigned long long *)(param_1 + 0x30) = 0;
    *(unsigned long long *)(param_1 + 0x40) = 0;
    iStack_30 = (u8 *)PS2_PTR(iVar2);
    do {
        iVar6 = 0;
        *(u8 *)((u8 *)PS2_PTR(iVar2) + iVar7 + 0x14) = 0;
        *(u32 *)(iStack_30 + 4) = 0;
        sVar1 = *psStack_40;
        iVar4 = (((param_4 + psStack_40[1]) * 0x280) / 0x1E0) * 0x1C0;
        if (iVar4 < 0) {
            iVar4 = iVar4 + 0x1FF;
        }
        iVar5 = param_1;
        do {
            uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F33);
            func_001057F0(iVar5 + 0x50, uVar3, 0);
            *(unsigned long long *)(iVar5 + 0x70) = 0x3F80000080808080;
            *(unsigned long long *)(iVar5 + 0x78) = 0xD081088;
            *(unsigned long long *)(iVar5 + 0x88) = 0xE081188;
            *(unsigned long long *)(iVar5 + 0x80) =
                      (long long)((param_3 + sVar1) * 0x10 + 0x7000) |
                      (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFD00000000;
            *(unsigned long long *)(iVar5 + 0x90) =
                      (long long)((param_3 + sVar1 + 0x10) * 0x10 + 0x7000) |
                      (long long)((((iVar4 >> 9) + 0x12) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 |
                      0xFFFD00000000;
            if (iVar6 == 1) {
                *(unsigned long long *)(iVar5 + 0x80) = 0;
                *(unsigned long long *)(iVar5 + 0x90) = 0;
            }
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + 0x50;
        } while (iVar6 < 2);
        iVar7 = iVar7 + 1;
        iStack_30 = iStack_30 + 4;
        psStack_40 = psStack_40 + 2;
        param_1 = param_1 + 0xA0;
    } while (iVar7 < 4);
}

/* 0x002632B0, 0x378 bytes. */
void func_002632B0(int param_1)
{
    u8 * iVar1;
    int iVar2;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    unsigned long long uVar3;

    iVar4 = param_1 * 0x2C;
    iVar9 = 0;
    iVar6 = g_00732220;
    param_1 = param_1 * 0x1380;
    *(u32 *)(g_007325FC + iVar4) = 0;
    *(u32 *)(g_00732604 + iVar4) = 0;
    *(u32 *)(g_00732608 + iVar4) = 0;
    *(u8 *)(g_0073260D + iVar4) = 0;
    *(u8 *)(g_0073260E + iVar4) = 4;
    do {
        iVar4 = *(int *)(iVar6 + 0x2E0) + param_1;
        uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3F02);
        func_001057F0((u8 *)PS2_PTR(iVar4 + 0x1B770), uVar3, 0);
        iVar7 = 0x124;
        iVar8 = 0;
        iVar5 = 0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B790) = 0x3F80000080808080;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B798) = 0x7480008;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B7A8) = 0xA480388;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B7A0) = 0xFFFE84608BF0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B7B0) = 0xFFFE86388FB0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B7A0) = 0;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x1B7B0) = 0;
        iVar4 = 0x8240;
        do {
            iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2E0) + param_1 + iVar5);
            uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEF);
            func_001057F0(iVar1 + 0x1B7C0, uVar3, 0);
            *(unsigned long long *)(iVar1 + 0x1B7E0) = 0x3F80000080808080;
            *(unsigned long long *)(iVar1 + 0x1B7E8) = 0x80C88;
            *(unsigned long long *)(iVar1 + 0x1B7F8) = 0x3080F08;
            *(unsigned long long *)(iVar1 + 0x1B7F0) = (long long)iVar4 | 0xFFFE84600000;
            *(unsigned long long *)(iVar1 + 0x1B800) = (long long)((iVar7 + 0x2B) * 0x10 + 0x7000) | 0xFFFE86380000;
            *(unsigned long long *)(iVar1 + 0x1B7F0) = 0;
            *(unsigned long long *)(iVar1 + 0x1B800) = 0;
            iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2E0) + param_1 + iVar5);
            uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F0, 0x3EEF);
            func_001057F0(iVar1 + 0x1B970, uVar3, 0);
            *(unsigned long long *)(iVar1 + 0x1B990) = 0x3F80000080808080;
            *(unsigned long long *)(iVar1 + 0x1B998) = 0x80C88;
            *(unsigned long long *)(iVar1 + 0x1B9A8) = 0x3080F08;
            iVar4 = iVar4 + 0x3B0;
            iVar2 = iVar7 + 0x4B;
            *(unsigned long long *)(iVar1 + 0x1B9A0) = (long long)((iVar7 + 0x20) * 0x10 + 0x7000) | 0xFFFE84600000;
            iVar7 = iVar7 + 0x3B;
            *(unsigned long long *)(iVar1 + 0x1B9B0) = (long long)(iVar2 * 0x10 + 0x7000) | 0xFFFE86380000;
            *(unsigned long long *)(iVar1 + 0x1B9A0) = 0;
            *(unsigned long long *)(iVar1 + 0x1B9B0) = 0;
            iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2E0) + param_1);
            func_001050B0(iVar1 + 0x1BB00);
            *(unsigned long long *)(iVar1 + 0x1BB10) = 0x8000000044;
            *(unsigned long long *)(iVar1 + 0x1BB18) = 0x43;
            iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2E0) + param_1);
            func_001050B0(iVar1 + 0x1B950);
            iVar8 = iVar8 + 1;
            *(unsigned long long *)(iVar1 + 0x1B960) = 0x8000000044;
            *(unsigned long long *)(iVar1 + 0x1B968) = 0x43;
            iVar5 = iVar5 + 0x50;
        } while (iVar8 < 5);
        iVar9 = iVar9 + 1;
        iVar6 = iVar6 + 4;
    } while (iVar9 < 2);
}

/* 0x0028FBD0, 0x248 bytes. */
void func_0028FBD0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar4;
    u8 * iVar5;
    int iVar6;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    iVar6 = *(u32 *)(g_00669F9C + 0x4) - *(u32 *)g_00669F9C;
    uVar1 = PS2_ADDR(func_00105860(4, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F57);
    iVar5 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar5 + 0x18) = uVar2;
    *(unsigned long long *)(iVar5 + 0x20) = (long long)(int)(param_5 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar5 + 0x28) = 0x7880288;
    *(unsigned long long *)(iVar5 + 0x38) = 0x8F808F8;
    uVar3 = (long long)(0xFFFE - param_3) << 0x20;
    iVar4 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              uVar3 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar4 = (((param_2 + 0x18) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              uVar3 | (long long)((param_1 + 0x68) * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar1), param_4);
    func_002CD940((float)iVar6, param_1 + 0x6C, param_2 + 6, 0x10, param_4, 0);
}

/* 0x00290C10, 0x78 bytes. */
int func_00290C10(int param_1)
{
    u32 auStack_50[20];
    int iVar2;
    long long lVar1;
    u32 * puVar3;
    u32 * puVar4;
    u32 uVar5;

    puVar4 = (u32 *)(g_004114F0);
    puVar3 = auStack_50;
    iVar2 = 9;
    do {
        iVar2 = iVar2 + -1;
        uVar5 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar5;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    uVar5 = auStack_50[(int)param_1];
    if ((param_1 == 3) && (lVar1 = func_0036D780(), lVar1 == 0)) {
        uVar5 = 5;
    }
    return uVar5;
}

/* 0x00290C90, 0x48 bytes. */
int func_00290C90(int param_1)
{
    u32 auStack_50[20];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 uVar1;

    puVar3 = auStack_50;
    puVar4 = (u32 *)(g_00411540);
    iVar2 = 9;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    return auStack_50[param_1];
}

/* 0x00291650, 0x25C bytes. */
void func_00291650(u8 *param_1)
{
    u8 * iVar3;
    u8 * iVar4;
    int uVar1;
    int uVar2;
    unsigned long long uVar5;
    unsigned long long uVar6;

    func_00290F90(0x411350);
    param_1 = param_1 + *(int *)(param_1 + 8) * *(int *)(param_1 + 0x78);
    iVar3 = func_00106F10(param_1);
    uVar5 = func_00104ED0(param_1, 0x1320, 0x3FFC);
    uVar6 = PS2_ADDR(func_00105860(uVar5, 0));
    iVar4 = (u8 *)PS2_PTR((int)uVar6);
    *(unsigned long long *)(iVar4 + 0x18) = uVar5;
    uVar1 = *(u16 *)(iVar3 + 0x14);
    uVar2 = *(u16 *)(iVar3 + 0x16);
    *(unsigned long long *)(iVar4 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0x80008;
    *(long long *)(iVar4 + 0x38) =
              (long long)(int)((uVar1 - 1) * 0x10 | 8) | (long long)(int)((uVar2 - 1) * 0x10 | 8) << 0x10;
    *(unsigned long long *)(iVar4 + 0x30) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00008280;
    *(unsigned long long *)(iVar4 + 0x40) = (long long)(0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    func_001059B0((u8 *)PS2_PTR(uVar6));
    uVar5 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F63);
    uVar5 = PS2_ADDR(func_00105860(uVar5, 0));
    uVar6 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F63);
    iVar3 = (u8 *)PS2_PTR((int)uVar5);
    *(unsigned long long *)(iVar3 + 0x18) = uVar6;
    *(unsigned long long *)(iVar3 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(iVar3 + 0x28) = 0xB081708;
    *(unsigned long long *)(iVar3 + 0x38) = 0x10F81CF8;
    *(unsigned long long *)(iVar3 + 0x30) = (long long)(-0xA70 / g_70000154 + 0x8000) << 0x10 | 0xFFFE000070D0;
    *(unsigned long long *)(iVar3 + 0x40) = (long long)(0xC0 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007A60;
    func_001059B0((u8 *)PS2_PTR(uVar5));
    func_002911C0();
    func_00290F90(0x411360);
    func_00290F90(0x411370);
}

/* 0x002918B0, 0x220 bytes. */
void func_002918B0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar3;
    u8 * iVar4;
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    iVar4 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar4 + 0x18) = uVar2;
    *(unsigned long long *)(iVar4 + 0x20) = (long long)(int)(param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0xB081588;
    *(unsigned long long *)(iVar4 + 0x38) = 0xBF816F8;
    iVar3 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x30) =
              (long long)(param_1 * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar3 = (((param_4 + param_2) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x40) =
              (long long)((param_3 + param_1) * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar1), param_5);
}

/* 0x00291AD0, 0x220 bytes. */
void func_00291AD0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar3;
    u8 * iVar4;
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    iVar4 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar4 + 0x18) = uVar2;
    *(unsigned long long *)(iVar4 + 0x20) = (long long)(int)(param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0x4880F88;
    *(unsigned long long *)(iVar4 + 0x38) = 0x5F81078;
    iVar3 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x30) =
              (long long)(param_1 * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar3 = (((param_4 + param_2) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x40) =
              (long long)((param_3 + param_1) * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar1), param_5);
}

/* 0x00291CF0, 0x220 bytes. */
void func_00291CF0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar3;
    u8 * iVar4;
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F56);
    iVar4 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar4 + 0x18) = uVar2;
    *(unsigned long long *)(iVar4 + 0x20) = (long long)(int)(param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0x15081E08;
    *(unsigned long long *)(iVar4 + 0x38) = 0x16F81FF8;
    iVar3 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x30) =
              (long long)(param_1 * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar3 = (((param_4 + param_2) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x40) =
              (long long)((param_3 + param_1) * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar1), param_5);
}

/* 0x00293750, 0x90 bytes. */
int func_00293750(int param_1)
{
    int aiStack_70[28];
    int iVar1;
    int * piVar2;
    int * piVar3;
    u32 uVar4;

    piVar3 = (int *)(g_004117B0);
    iVar1 = 0x1B;
    piVar2 = aiStack_70;
    do {
        iVar1 = iVar1 + -1;
        *piVar2 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar2 = piVar2 + 1;
    } while (0 < iVar1);
    iVar1 = func_003623B0();
    uVar4 = 0;
    piVar2 = aiStack_70;
    while ((*piVar2 != iVar1 || (piVar2[1] != param_1))) {
        uVar4 = uVar4 + 1;
        piVar2 = piVar2 + 3;
        if (8 < uVar4) {
            return 0;
        }
    }
    return piVar2[2];
}

/* 0x00294760, 0x4C8 bytes. */
void func_00294760(u8 *param_1, int *param_2, int param_3, u8 *param_4, int param_5)
{
    float fVar11;
    float fVar12;
    float fVar13;
    u8 * iVar1;
    u8 * iVar2;
    int iVar7;
    int iVar9;
    long long lVar10;
    long long lVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar8;

    uVar8 = 0;
    if (((param_3 & 0xFF) != 0) && ((param_3 & 0xFF) != 0)) {
        iVar9 = 0;
        do {
            if ((*(u32 *)g_00669F60 & 2) == 0) {
                if (uVar8 == *param_4) {
                    fVar11 = 1.0;
                }
                else {
                    fVar11 = 0.675;
                }
            }
            else if ((uVar8 == *param_4) || (uVar8 == param_4[1])) {
                fVar11 = 1.0;
            }
            else {
                fVar11 = 0.675;
            }
            fVar11 = fVar11 * 128.0;
            if (2.1474836e+09 <= fVar11) {
                fVar11 = fVar11 - 2.1474836e+09;
            }
            lVar10 = 0x80;
            if (param_2[2] == 0xB) {
                lVar3 = func_002207F0();
                if (lVar3 == 0) {
                    lVar10 = 0x50;
                }
            }
            else if ((param_2[2] == 5) && (lVar3 = func_00220780(), lVar3 == 0)) {
                lVar10 = 0x50;
            }
            fVar13 = (float)*param_2;
            fVar12 = (((float)*param_2 + 160.0) / 10.0) * (float)(u32)(*(u32 *)g_00772D48 - iVar9) + -160.0;
            if (fVar13 <= fVar12) {
                fVar12 = fVar13;
            }
            iVar7 = PS2_ADDR(param_1 + *(int *)(param_1 + 8) * *(int *)(param_1 + 0x10 + param_2[2] * 8));
            iVar1 = func_00106F10((u8 *)PS2_PTR(iVar7));
            uVar4 = func_00104AC0((u8 *)PS2_PTR(iVar7), 0x1320, param_5);
            uVar5 = func_00104D00((u8 *)PS2_PTR(iVar7), 0x3FFC, param_5);
            uVar4 = func_00106C50(uVar4, uVar5);
            uVar4 = PS2_ADDR(func_00105860(uVar4, 0));
            uVar6 = (unsigned long long)((int)fVar11 & 0xFF);
            iVar2 = (u8 *)PS2_PTR((int)uVar4);
            *(unsigned long long *)(iVar2 + 0x20) =
                      lVar10 << 0x18 | uVar6 << 0x10 | uVar6 | uVar6 << 8 | 0x3F80000000000000;
            *(unsigned long long *)(iVar2 + 0x28) = 0x80008;
            *(long long *)(iVar2 + 0x38) =
                      (long long)(int)((*(u16 *)(iVar1 + 0x14) - 1) * 0x10 | 8) |
                      (long long)(int)((*(u16 *)(iVar1 + 0x16) - 1) * 0x10 | 8) << 0x10;
            iVar7 = ((param_2[1] * 0x280) / 0x1E0) * 0x1C0;
            if (iVar7 < 0) {
                iVar7 = iVar7 + 0x1FF;
            }
            *(unsigned long long *)(iVar2 + 0x30) =
                      (long long)((int)fVar12 * 0x10 + 0x7000) |
                      (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            iVar7 = ((int)(((u32)*(u16 *)(iVar1 + 0x16) + param_2[1]) * 0x280) / 0x1E0) * 0x1C0;
            if (iVar7 < 0) {
                iVar7 = iVar7 + 0x1FF;
            }
            *(unsigned long long *)(iVar2 + 0x40) =
                      (long long)(int)(((u32)*(u16 *)(iVar1 + 0x14) + (int)fVar12) * 0x10 + 0x7000) |
                      (long long)(((iVar7 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
            func_00105900((u8 *)PS2_PTR(uVar4), param_5);
            uVar8 = (unsigned long long)((int)uVar8 + 1);
            param_2 = param_2 + 3;
            iVar9 = iVar9 + 2;
        } while ((long long)uVar8 < (long long)((unsigned long long)param_3 & 0xFFFFFFFF000000FF));
    }
}

/* 0x00298470, 0x1FC bytes. */
void func_00298470(int param_1, int param_2, int param_3, int param_4)
{
    int iVar4;
    u8 * iVar5;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F7F);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F7F);
    iVar5 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar5 + 0x18) = uVar2;
    *(unsigned long long *)(iVar5 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(iVar5 + 0x28) = 0x15081908;
    *(unsigned long long *)(iVar5 + 0x38) = 0x16081A08;
    uVar3 = (long long)(0xFFFE - param_3) << 0x20;
    iVar4 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              uVar3 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar4 = (((param_2 + 0x10) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              uVar3 | (long long)((param_1 + 0x10) * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar1), param_4);
}

/* 0x0029A890, 0x58 bytes. */
int func_0029A890(int param_1)
{
    u32 auStack_80[32];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 uVar1;

    puVar3 = auStack_80;
    puVar4 = (u32 *)(g_004118D0);
    iVar2 = 0x1F;
    do {
        iVar2 = iVar2 + -1;
        *puVar3 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar3 = puVar3 + 1;
    } while (0 < iVar2);
    if (param_1 < 0x1F) {
        uVar1 = auStack_80[(int)param_1];
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x0029B5A0, 0x358 bytes. */
void func_0029B5A0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar1;
    u8 * iVar5;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    func_002C7310();
    uVar2 = PS2_ADDR(func_00362A20(0));
    func_002C4E40(20.0f, (char *)PS2_PTR(uVar2), param_1 + 0x9C, param_2 + 8, 0x88, param_4, 0, 3);
    *(u32 *)(g_0056CCA4) = 1;
    *(u32 *)(g_0056CCA4 + 0x4) = 1;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41A00000;
    *(u32 *)(g_0056CCA4 + 0x8) = 1;
    *(u32 *)(g_0056CCA4 + 0xC) = 1;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41A00000;
    uVar2 = PS2_ADDR(func_00362A20(1));
    func_00146B40((u8 *)PS2_PTR(uVar2), param_1 + 0xB4, param_2 + 8, 0x88, 0x14, param_4, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)(g_0056CCA4) = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
    func_003E4140(param_1 + 0x18, param_2 + 0x20, 0, param_4);
    if (param_5 == 0) {
        uVar2 = func_003F6E60(0);
    }
    else {
        uVar2 = func_00362CE0(0);
    }
    func_003B5CA0();
    func_003E4220(param_1 + 0xC4, param_2 + 0x20, 0, param_4);
    if (param_5 == 0) {
        uVar2 = func_003F7B70(1);
        uVar2 = PS2_ADDR(func_0030CB80(uVar2));
        func_002C4F40(16.0f, (char *)PS2_PTR(uVar2), param_1 + 0x128, param_2 + 0x20, param_4, 0, 1);
    }
    else {
        uVar2 = PS2_ADDR(func_00372D70(1));
        func_002C4F40(16.0f, (char *)PS2_PTR(uVar2), param_1 + 0x128, param_2 + 0x20, param_4, 0, 1);
    }
    uVar2 = PS2_ADDR(func_00105860(4, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F57);
    iVar5 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar5 + 0x18) = uVar3;
    *(unsigned long long *)(iVar5 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(iVar5 + 0x28) = 0x7880908;
    *(unsigned long long *)(iVar5 + 0x38) = 0x9080A88;
    iVar1 = (((param_2 + 0xC) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    uVar4 = (long long)(0xFFFE - (int)param_3) << 0x20;
    *(unsigned long long *)(iVar5 + 0x30) =
              uVar4 | (long long)((param_1 + 0x9C) * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar5 + 0x40) =
              uVar4 | (long long)((param_1 + 0xB4) * 0x10 + 0x7000) |
                              (long long)((((iVar1 >> 9) + 0x1C) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar2), param_4);
}

/* 0x0029DD40, 0x48 bytes. */
void func_0029DD40(float param_1, float param_2, int param_3, int param_4, int param_5, int param_6)
{
    func_0029D9F0(param_1 / param_2, 4.0f, 0.25f, 0, (u8 *)PS2_PTR(param_3), (u8 *)PS2_PTR(param_6), (u8 *)PS2_PTR(param_4), (u8 *)PS2_PTR(param_5));
}

/* 0x002A7E70, 0x44 bytes. */
int func_002A7E70(void)
{
    u8 * iVar1;
    int iVar2;

    iVar2 = 0;
    iVar1 = g_0077C040;
    do {
        if (-1 < (long long)*(char *)(iVar1 + 0x168) << 0x3F) {
            return PS2_ADDR(iVar1);
        }
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x170;
    } while (iVar2 < 10);
    return 0;
}

/* 0x002B5C60, 0x10C bytes. */
void func_002B5C60(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int aiStack_10[4];
    u8 * iVar1;
    int iVar4;
    int * piVar3;
    unsigned long long uVar2;

    uVar2 = PS2_ADDR(func_00104E70(param_1 + *(int *)(param_1 + 8) * *(int *)(param_1 + 0x238), 0x1D00, 0x3FFC,
                                              param_8));
    iVar4 = 0;
    piVar3 = aiStack_10;
    do {
        iVar1 = func_00105860(uVar2, 0);
        *piVar3 = PS2_ADDR(iVar1);
        iVar4 = iVar4 + 1;
        *(unsigned long long *)(iVar1 + 0x18) = uVar2;
        piVar3 = piVar3 + 1;
    } while (iVar4 < 3);
    func_002B59D0((u8 *)PS2_PTR(aiStack_10[0]), param_2, param_3, param_4, param_5, param_6, param_7);
    iVar4 = 0;
    piVar3 = aiStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*piVar3), param_8);
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
    } while (iVar4 < 3);
}

/* 0x002B6450, 0x7C bytes. */
int func_002B6450(int param_1, int param_2)
{
    u32 auStack_70[26];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 uStack_4;
    int uStack_6;
    int uStack_8;
    u32 uVar1;

    puVar4 = (u32 *)(g_00412040);
    puVar3 = auStack_70;
    iVar2 = 0xC;
    uStack_6 = g_0045CED2;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    uStack_4 = g_0045CEDC;
    uStack_8 = g_0045CED8;
    func_002B4E80((u8 *)PS2_PTR(param_1), (int *)(auStack_70), (u16 *)(&uStack_8), 3, param_2, 2, 1);
    return 0;
}

/* 0x002B7DA0, 0x88 bytes. */
int func_002B7DA0(int param_1, int param_2)
{
    u32 auStack_70[26];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    int sStack_2;
    int uStack_4;
    int uStack_6;
    int uStack_8;
    u32 uVar1;

    puVar4 = (u32 *)(g_004120D0);
    puVar3 = auStack_70;
    iVar2 = 0xC;
    sStack_2 = g_0045CEE6 + 4;
    uStack_6 = g_0045CEE2;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    uStack_4 = g_0045CEEC;
    uStack_8 = g_0045CEE8;
    func_002B4E80((u8 *)PS2_PTR(param_1), (int *)(auStack_70), (u16 *)(&uStack_8), 3, param_2, 2, 1);
    return 0;
}

/* 0x002B7E30, 0x88 bytes. */
int func_002B7E30(int param_1, int param_2)
{
    u32 auStack_70[26];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    int sStack_2;
    int uStack_4;
    int uStack_6;
    int uStack_8;
    u32 uVar1;

    puVar4 = (u32 *)(g_00412130);
    puVar3 = auStack_70;
    iVar2 = 0xC;
    sStack_2 = g_0045CEF6 + 4;
    uStack_6 = g_0045CEF2;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    uStack_4 = g_0045CEFC;
    uStack_8 = g_0045CEF8;
    func_002B4E80((u8 *)PS2_PTR(param_1), (int *)(auStack_70), (u16 *)(&uStack_8), 2, param_2, 2, 1);
    return 0;
}

/* 0x002B9E40, 0xF8 bytes. */
void func_002B9E40(float param_1, int param_2, int param_3)
{
    int iVar3;
    long long lVar1;
    float * pfVar2;

    iVar3 = 0;
    pfVar2 = (float *)(g_00441DD0);
    do {
        if (param_1 < *pfVar2) break;
        iVar3 = iVar3 + 1;
        pfVar2 = pfVar2 + 1;
    } while (iVar3 < 3);
    if ((-1 < iVar3 + -1) &&
          (iVar3 = *(int *)((iVar3 + -1) * 4 + param_2 * 0xC + 0x441DE0), iVar3 < 0x18B)) {
        if ((*(u32 *)g_00669F60 & 0x100000) == 0) {
            if (g_0045D2A4 != 0) {
                return;
            }
            lVar1 = func_00246610();
            if (lVar1 == 0) {
                return;
            }
            g_70000D60 = 0;
        }
        else {
            g_70000D60 = 0xB;
        }
        func_001C7F30(iVar3, (float *)PS2_PTR(param_3), 0, 0);
    }
}

/* 0x002C6040, 0x358 bytes. */
void func_002C6040(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar4;
    int iVar7;
    u8 * iVar8;
    u32 uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar5;
    unsigned long long uVar6;

    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    iVar8 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar8 + 0x18) = uVar3;
    *(unsigned long long *)(iVar8 + 0x20) = 0x3F80000080808080;
    *(unsigned long long *)(iVar8 + 0x28) = 0x9080008;
    *(unsigned long long *)(iVar8 + 0x38) = 0xAE80FE8;
    iVar4 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    iVar7 = (iVar4 >> 9) * 0x10 + -0xE00;
    uVar6 = (unsigned long long)(param_1 * 0x10 + 0x7000);
    *(unsigned long long *)(iVar8 + 0x30) = uVar6 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar4 = (((param_4 + param_2) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    iVar4 = (iVar4 >> 9) * 0x10 + -0xE00;
    uVar5 = (unsigned long long)((param_3 + param_1) * 0x10 + 0x7000);
    *(unsigned long long *)(iVar8 + 0x40) = uVar5 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar2), param_5);
    uVar2 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar2 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar2 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar2), param_5);
    uVar1 = func_002C5AE0(g_00799A20);
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    iVar8 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar8 + 0x18) = uVar3;
    *(unsigned long long *)(iVar8 + 0x20) = (long long)(int)(uVar1 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar8 + 0x28) = 0x9080008;
    *(unsigned long long *)(iVar8 + 0x38) = 0xAE80FE8;
    *(unsigned long long *)(iVar8 + 0x30) = uVar6 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    *(unsigned long long *)(iVar8 + 0x40) = uVar5 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar2), param_5);
    uVar2 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar2 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar2 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar2), param_5);
}

/* 0x002C63A0, 0x220 bytes. */
void func_002C63A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar3;
    u8 * iVar4;
    unsigned long long uVar1;
    unsigned long long uVar2;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5A);
    iVar4 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar4 + 0x18) = uVar2;
    *(unsigned long long *)(iVar4 + 0x20) = (long long)(int)(param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0x9080008;
    *(unsigned long long *)(iVar4 + 0x38) = 0xAE80FE8;
    iVar3 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x30) =
              (long long)(param_1 * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar3 = (((param_4 + param_2) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x40) =
              (long long)((param_3 + param_1) * 0x10 + 0x7000) |
              (long long)(((iVar3 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar1), param_5);
}

/* 0x002C69D0, 0x1CC bytes. */
void func_002C69D0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar6;
    u32 * puVar5;
    int uVar1;
    u8 * uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5B);
    uVar1 = func_002C5AE0(g_00799A20);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_002C66A0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, 0x80);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_002C66A0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, uVar1);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    uVar3 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar3 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar3 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar3), param_7);
}

/* 0x002C7A30, 0x1D0 bytes. */
void func_002C7A30(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_30[12];
    int iVar6;
    u32 * puVar5;
    int uVar1;
    u8 * uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5F);
    uVar1 = func_002C5AE0(g_00799A38);
    iVar6 = 0;
    puVar5 = auStack_30;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 9);
    func_002C7410((u8 *)PS2_PTR(auStack_30[0]), param_1, param_2, param_3, param_4, param_5, param_6);
    iVar6 = 0;
    puVar5 = auStack_30;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 9);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    iVar6 = 0;
    puVar5 = auStack_30;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 9);
    func_002C7410((u8 *)PS2_PTR(auStack_30[0]), param_1, param_2, param_3, param_4, param_5, uVar1);
    iVar6 = 0;
    puVar5 = auStack_30;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 9);
    uVar3 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar3 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar3 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar3), param_7);
}

/* 0x002C8500, 0x21C bytes. */
void func_002C8500(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar6;
    u32 * puVar5;
    u32 uVar1;
    u8 * uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5E);
    uVar1 = func_002C5AE0(g_00799A38);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_002C81D0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, param_6);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    param_6 = (uVar1 & 0xFF) * param_6;
    if (param_6 < 0) {
        param_6 = param_6 + 0x7F;
    }
    func_002C81D0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, param_6 >> 7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_001050F0();
    uVar3 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar3 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar3 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar3), param_7);
}

/* 0x002C8EF0, 0x1F0 bytes. */
void func_002C8EF0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar6;
    u32 * puVar5;
    u32 uVar1;
    u8 * uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5E);
    uVar1 = func_002C5AE0(g_00799A38);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_002C8BC0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, param_6);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        uVar2 = func_00105860(uVar3, 0);
        *puVar5 = PS2_ADDR(uVar2);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    param_6 = (uVar1 & 0xFF) * param_6;
    if (param_6 < 0) {
        param_6 = param_6 + 0x7F;
    }
    func_002C8BC0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, param_6 >> 7);
    iVar6 = 0;
    puVar5 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar5), param_7);
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
    } while (iVar6 < 3);
    func_001050F0();
    uVar3 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar3 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar3 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar3), param_7);
}

/* 0x002C90E0, 0x1C0 bytes. */
void func_002C90E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar5;
    u32 * puVar4;
    u8 * uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5E);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        uVar1 = func_00105860(uVar2, 0);
        *puVar4 = PS2_ADDR(uVar1);
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
    func_002C81D0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, param_6);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar4), param_7);
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
    uVar3 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar3 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar3 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar3), param_7);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        uVar1 = func_00105860(uVar2, 0);
        *puVar4 = PS2_ADDR(uVar1);
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
    func_002C81D0((u8 *)PS2_PTR(auStack_10[0]), param_1, param_2, param_3, param_4, param_5, 0x14);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar4), param_7);
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
    func_001050F0();
    uVar2 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar2 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar2 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar2), param_7);
}

/* 0x002C99F0, 0x340 bytes. */
void func_002C99F0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u8 * iVar1;
    int iVar5;
    int iVar6;
    int iVar9;
    unsigned long long uVar10;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar7;
    unsigned long long uVar8;

    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F77);
    uVar3 = func_002C5AE0(g_00799A50);
    uVar4 = PS2_ADDR(func_00105860(uVar2, 0));
    iVar5 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    iVar6 = ((param_5 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar6 < 0) {
        iVar6 = iVar6 + 0x1FF;
    }
    iVar9 = (iVar5 >> 9) * 0x10 + -0xE00;
    iVar1 = (u8 *)PS2_PTR((int)uVar4);
    *(unsigned long long *)(iVar1 + 0x18) = uVar2;
    iVar6 = ((iVar6 >> 9) + (iVar5 >> 9)) * 0x10 + -0xE00;
    uVar8 = (unsigned long long)(param_1 * 0x10 + 0x7000);
    uVar10 = (unsigned long long)((param_4 + param_1) * 0x10 + 0x7000);
    *(unsigned long long *)(iVar1 + 0x20) = (long long)param_6 << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar1 + 0x28) = 0x7881088;
    *(unsigned long long *)(iVar1 + 0x38) = 0x8781578;
    uVar7 = (long long)(0xFFFE - param_3) << 0x20;
    *(unsigned long long *)(iVar1 + 0x30) = uVar7 | uVar8 | (long long)(iVar9 / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar1 + 0x40) = uVar7 | uVar10 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar4), param_7);
    uVar4 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar4 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar4 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar4), param_7);
    uVar4 = PS2_ADDR(func_00105860(uVar2, 0));
    iVar5 = (int)uVar4;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x18) = uVar2;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x20) = (uVar3 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x28) = 0x7881088;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x38) = 0x8781578;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x30) = uVar7 | uVar8 | (long long)(iVar9 / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x40) = uVar7 | uVar10 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar4), param_7);
    uVar2 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar2 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar2 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar2), param_7);
}

/* 0x002CBEC0, 0x26C bytes. */
void func_002CBEC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar1;
    u8 * iVar4;
    unsigned long long uVar2;
    unsigned long long uVar3;

    uVar2 = PS2_ADDR(func_00104E70((u8 *)PS2_PTR(param_1), 0x1320, 0x3FFC, param_7));
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    iVar1 = PS2_ADDR(func_00106F10((u8 *)PS2_PTR(param_1)));
    iVar4 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar4 + 0x20) = (param_8 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(unsigned long long *)(iVar4 + 0x28) = 0x80008;
    *(long long *)(iVar4 + 0x38) =
              (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x14) - 1) * 0x10 | 8) |
              (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x16) - 1) * 0x10 | 8) << 0x10;
    if (param_5 == 0xFFFFFFFFFFFFFFFF) {
        param_5 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x14);
    }
    if (param_6 == 0xFFFFFFFFFFFFFFFF) {
        param_6 = (unsigned long long)*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x16);
    }
    uVar3 = (long long)(0xFFFE - param_4) << 0x20;
    iVar1 = ((param_3 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x30) =
              uVar3 | (long long)(param_2 * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar1 = ((((int)param_6 + param_3) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar4 + 0x40) =
              uVar3 | (long long)(((int)param_5 + param_2) * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar2), param_7);
}

/* 0x002CC9B0, 0x3FC bytes. */
void func_002CC9B0(int *param_1, int *param_2, int param_3)
{
    int iVar2;
    u8 * iVar3;
    unsigned long long uVar1;

    uVar1 = PS2_ADDR(func_00105620());
    func_001055E0((u8 *)PS2_PTR(uVar1));
    iVar2 = ((param_1[1] * 0x280) / 0x1E0) * 0x1C0;
    if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1FF;
    }
    iVar3 = (u8 *)PS2_PTR((int)uVar1);
    *(long long *)(iVar3 + 0x20) =
              (long long)(0xFFFE - param_1[2]) << 0x20 |
              (long long)(*param_1 * 0x10 + 0x7000) |
              (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar2 = ((param_2[1] * 0x280) / 0x1E0) * 0x1C0;
    if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1FF;
    }
    *(long long *)(iVar3 + 0x30) =
              (long long)(0xFFFE - param_2[2]) << 0x20 |
              (long long)(*param_2 * 0x10 + 0x7000) |
              (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar2 = (((param_1[1] + param_3) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1FF;
    }
    *(long long *)(iVar3 + 0x40) =
              (long long)(0xFFFE - param_2[2]) << 0x20 |
              (long long)(*param_1 * 0x10 + 0x7000) |
              (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar2 = (((param_2[1] + param_3) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar2 < 0) {
        iVar2 = iVar2 + 0x1FF;
    }
    *(long long *)(iVar3 + 0x50) =
              (long long)(0xFFFE - param_2[2]) << 0x20 |
              (long long)(*param_2 * 0x10 + 0x7000) |
              (long long)(((iVar2 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar3 + 0x18) = (unsigned long long)(u32)param_1[3] | 0x3F80000000000000;
    *(unsigned long long *)(iVar3 + 0x28) = (unsigned long long)(u32)param_2[3] | 0x3F80000000000000;
    *(unsigned long long *)(iVar3 + 0x38) = (unsigned long long)(u32)param_1[3] | 0x3F80000000000000;
    *(unsigned long long *)(iVar3 + 0x48) = (unsigned long long)(u32)param_2[3] | 0x3F80000000000000;
    func_001056C0((u8 *)PS2_PTR(uVar1), 0);
}

/* 0x002D2790, 0x2E8 bytes. */
void func_002D2790(int param_1, int param_2, int param_3, int param_4, int param_5, int *param_6, int param_7, int param_8)
{
    int iVar1;
    int iVar4;
    u8 * iVar9;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar7;
    unsigned long long uVar8;

    uVar2 = PS2_ADDR(func_00105620());
    func_001055E0((u8 *)PS2_PTR(uVar2));
    iVar4 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    iVar1 = (iVar4 >> 9) * 0x10 + -0xE00;
    uVar8 = (unsigned long long)(param_1 * 0x10 + 0x7000);
    uVar7 = (long long)(0xFFFE - param_3) << 0x20;
    uVar6 = (unsigned long long)((param_1 + param_4) * 0x10 + 0x7000);
    iVar9 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar9 + 0x20) = uVar7 | uVar8 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
    iVar4 = (((param_2 + param_5) * 0x280) / 0x1E0) * 0x1C0;
    *(unsigned long long *)(iVar9 + 0x30) = uVar7 | uVar6 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    iVar4 = (iVar4 >> 9) * 0x10 + -0xE00;
    uVar5 = (param_7 & 0xFF) << 0x18;
    uVar3 = (param_8 & 0xFF) << 0x18;
    *(unsigned long long *)(iVar9 + 0x40) = uVar7 | uVar8 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar9 + 0x50) = uVar7 | uVar6 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar9 + 0x18) = uVar5 | *param_6 | 0x3F80000000000000;
    *(unsigned long long *)(iVar9 + 0x28) = uVar5 | *param_6 | 0x3F80000000000000;
    *(unsigned long long *)(iVar9 + 0x38) = uVar3 | *param_6 | 0x3F80000000000000;
    *(unsigned long long *)(iVar9 + 0x48) = uVar3 | *param_6 | 0x3F80000000000000;
    func_001056C0((u8 *)PS2_PTR(uVar2), 0);
}

/* 0x002D5FE0, 0x318 bytes. */
void func_002D5FE0(float param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar4;
    int iVar5;
    u8 * iVar6;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F64);
    uVar1 = PS2_ADDR(func_00105860(uVar1, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F64);
    iVar6 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar6 + 0x18) = uVar2;
    iVar4 = (param_8 & 0xFF) * 8;
    iVar5 = *(int *)(g_00442300 + iVar4);
    iVar4 = *(int *)((g_00442300 + 0x4) + iVar4);
    *(unsigned long long *)(iVar6 + 0x20) = (long long)(int)((u32)param_6 & 0xFF) << 0x18 | 0x3F80000000808080;
    *(long long *)(iVar6 + 0x28) = (long long)(int)(iVar5 << 4 | 8) | (long long)(int)(iVar4 << 4 | 8) << 0x10;
    *(long long *)(iVar6 + 0x38) =
              (long long)(int)((iVar5 + 0x47) * 0x10 | 8) | (long long)(int)((iVar4 + 0xF) * 0x10 | 8) << 0x10;
    uVar3 = (long long)(0xFFFE - param_4) << 0x20;
    iVar5 = ((param_3 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar6 + 0x30) =
              uVar3 | (long long)(param_2 * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar5 = ((((int)(param_1 * 16.0) + param_3) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    param_5 = param_5 & 0xFF;
    *(unsigned long long *)(iVar6 + 0x40) =
              uVar3 | (long long)(((int)(param_1 * 72.0) + param_2) * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    *(unsigned long long *)(iVar6 + 0x20) =
              (param_6 & 0xFF) << 0x18 | param_5 << 0x10 | param_5 | param_5 << 8 | 0x3F80000000000000;
    func_00105900((u8 *)PS2_PTR(uVar1), param_7);
}

/* 0x002D6300, 0x25C bytes. */
void func_002D6300(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar4;
    u8 * iVar5;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

    uVar1 = PS2_ADDR(func_001050F0());
    *(unsigned long long *)((int)uVar1 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar1 + 0x18) = 0x43;
    func_00105230((u8 *)PS2_PTR(uVar1), param_8);
    uVar1 = PS2_ADDR(func_00105860(0x17, 0));
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F6A);
    iVar5 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar5 + 0x18) = uVar2;
    param_6 = param_6 & 0xFF;
    *(unsigned long long *)(iVar5 + 0x20) =
              (param_7 & 0xFF) << 0x18 | param_6 << 0x10 | param_6 | param_6 << 8 | 0x3F80000000000000;
    *(unsigned long long *)(iVar5 + 0x28) = 0xD880708;
    *(unsigned long long *)(iVar5 + 0x38) = 0xEC80E08;
    uVar3 = (long long)(0xFFFE - param_3) << 0x20;
    iVar4 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              uVar3 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar4 = (((param_2 + param_5) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              uVar3 | (long long)((param_1 + param_4) * 0x10 + 0x7000) |
                              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar1), param_8);
}

/* 0x002D6B60, 0x90 bytes. */
void func_002D6B60(int param_1, int param_2, u32 *param_3)
{
    float fStack_4;
    float fStack_8;
    u16 * puVar1;

    puVar1 = (u16 *)(*(int *)(g_0045D2F0 + 0x6C) + param_1 * 8);
    fStack_8 = (float)(((u32)*puVar1 * 0x7C + (u32)*puVar1) * 4 + 0xFA);
    fStack_4 = (float)(((u32)puVar1[1] * 0x7C + (u32)puVar1[1]) * 4 + 0xFA);
    *param_3 = (u32)puVar1[2];
    func_001911A0((float *)PS2_PTR(param_2), (float *)((u8 *)(&fStack_8)));
}

/* 0x002DBB70, 0x40 bytes. */
void func_002DBB70(void)
{
    int iVar3;
    u32 * puVar1;
    u32 * puVar2;

    iVar3 = 0x7F;
    g_0045D614 = 0x79CE10;
    puVar2 = (u32 *)0x79CE10;
    do {
        puVar1 = puVar2 + 0x18;
        iVar3 = iVar3 + -1;
        *puVar2 = PS2_ADDR(puVar1);
        puVar2 = puVar1;
    } while (iVar3 != 0);
    *puVar1 = 0;
}

/* 0x002DC4D0, 0x40 bytes. */
void func_002DC4D0(void)
{
    int iVar3;
    u32 * puVar1;
    u32 * puVar2;

    iVar3 = 0x1F;
    *(u32 *)(g_0045D610) = 0x79CC10;
    puVar2 = (u32 *)0x79CC10;
    do {
        puVar1 = puVar2 + 4;
        iVar3 = iVar3 + -1;
        *puVar2 = PS2_ADDR(puVar1);
        puVar2 = puVar1;
    } while (iVar3 != 0);
    *puVar1 = 0;
}
/* MISSING ['0x45d610'] */

/* 0x002DCD40, 0x40 bytes. */
void func_002DCD40(void)
{
    int iVar3;
    u32 * puVar1;
    u32 * puVar2;

    iVar3 = 0x7F;
    g_0045D60C = 0x79A410;
    puVar2 = (u32 *)0x79A410;
    do {
        puVar1 = puVar2 + 0x14;
        iVar3 = iVar3 + -1;
        *puVar2 = PS2_ADDR(puVar1);
        puVar2 = puVar1;
    } while (iVar3 != 0);
    *puVar1 = 0;
}

/* 0x002DCE20, 0xD4 bytes. */
int func_002DCE20(float param_1, u8 *param_2)
{
    u8 auStack_130[272];
    float fStack_c;
    float fVar3;
    float fVar4;
    int iStack_20;
    u8 * iVar1;
    u32 * puVar2;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u8 * uStack_1c;
    u32 uStack_4;

    iVar1 = (u8 *)PS2_PTR(*(int *)(param_2 + 0x10));
    puVar2 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar1 + 0xC));
    fVar3 = *(float *)(iVar1 + 8) + param_1;
    *(float *)(iVar1 + 8) = fVar3;
    fVar4 = (float)puVar2[1];
    if (fVar4 > fVar3) {
        iStack_20 = PS2_ADDR(iVar1 + 0x10);
        uStack_1c = func_00207DC0(*(u16 *)(iVar1 + 4));
        uStack_18 = puVar2[2];
        uStack_14 = puVar2[3];
        fStack_c = 1.0 - *(float *)(iVar1 + 8) / (float)puVar2[1];
        uStack_10 = *puVar2;
        uStack_4 = 0;
        func_002BAE40(param_1, auStack_130);
        func_002BAF90(param_1, auStack_130, 0);
        func_002BAF70(param_1, auStack_130);
    }
    return fVar4 <= fVar3;
}

/* 0x002DF6C0, 0x40 bytes. */
void func_002DF6C0(void)
{
    int iVar3;
    u32 * puVar1;
    u32 * puVar2;

    iVar3 = 0x1F;
    g_0045D600 = 0x799AF0;
    puVar2 = (u32 *)0x799AF0;
    do {
        puVar1 = puVar2 + 4;
        iVar3 = iVar3 + -1;
        *puVar2 = PS2_ADDR(puVar1);
        puVar2 = puVar1;
    } while (iVar3 != 0);
    *puVar1 = 0;
}

/* 0x002E6570, 0x58 bytes. */
void func_002E6570(void)
{
    func_002E6280(g_007A05A0);
    func_0017AC50(*(u32 *)g_007A05AC);
    g_0045D470 = 2;
    func_001938B0(4, (float *)PS2_PTR(*(u32 *)g_007A05AC));
    g_0045D620 = g_0045D2C0;
    g_0045D2C0 = *(u32 *)g_007A05AC;
}

/* 0x002EFBC0, 0x78 bytes. */
int func_002EFBC0(void)
{
    int * piVar1;
    int * piVar2;

    piVar1 = (int *)0;
    if (g_0045D674 < 8) {
        piVar1 = (int *)(g_0045D674 * 0x70 + 0x7A22C0);
        *piVar1 = 1;
        g_0045CFD8 = g_0045CFD8 + -1;
        if (g_0045D674 < 8) {
            piVar2 = piVar1;
            do {
                if (*piVar2 == 0) {
                    return PS2_ADDR(piVar1);
                }
                g_0045D674 = g_0045D674 + 1;
                piVar2 = piVar2 + 0x1C;
            } while (g_0045D674 < 8);
        }
    }
    return PS2_ADDR(piVar1);
}

/* 0x0032A4F0, 0x158 bytes. */
int func_0032A4F0(u8 *param_1)
{
    int iStack_4;
    int iVar4;
    long long lVar3;
    u32 uVar1;
    unsigned long long uVar2;

    if (*(short *)(param_1 + 4) == 0) {
        uVar1 = *(u32 *)g_007B5DE4;
    }
    else {
        uVar1 = *(u32 *)(g_007B5DE4 + 0x4);
    }
    uVar2 = PS2_ADDR(func_0032A220(*(u16 *)(param_1 + 2)));
    func_0032A2C0((char *)PS2_PTR(uVar2), &iStack_4);
    iVar4 = 0;
    if (0 < *(u32 *)(g_007B5DE4 + 0xC)) {
        do {
            func_00369990(iVar4);
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(u32 *)(g_007B5DE4 + 0xC));
    }
    func_0032CF30(*(u16 *)(param_1 + 8), uVar1, *(u16 *)(param_1 + 4), 1);
    lVar3 = func_0032B180();
    *(ps2ptr *)((lVar3 != 0 ^ 1) * 4 + 0x7B5DF4) = PS2_ADDR((g_00447A10));
    iVar4 = func_0032B180();
    *(int *)(iVar4 * 4 + 0x7B5DF4) = (int)uVar2;
    *(u32 *)(g_007B5DE4 + 0x18) = (u32)*(u16 *)(param_1 + 4);
    *(u32 *)(g_007B5DE4 + 0x1C) = (u32)*(u16 *)(param_1 + 6);
    *(u32 *)(g_007B5DE4 + 0x8) = uVar1;
    if (*(u16 *)(param_1 + 4) == 0) {
        *(u32 *)(g_007B5DE4 + 0x28) = (u32)*(u16 *)(param_1 + 10);
    }
    else {
        *(u32 *)(g_007B5DE4 + 0x2C) = (u32)*(u16 *)(param_1 + 10);
    }
    if (iStack_4 != -1) {
        *(u32 *)(g_007B5DE4 + 0xC) = *(u32 *)(g_007B5DE4 + 0xC) + 1;
    }
    return PS2_ADDR(param_1 + 0x20);
}

/* 0x0032A7F0, 0x1A8 bytes. */
int func_0032A7F0(u8 *param_1)
{
    u8 auStack_150[332];
    u8 auStack_2a0[336];
    int iStack_4;
    int iVar4;
    long long lVar3;
    u32 uVar1;
    unsigned long long uVar2;

    if (*(short *)(param_1 + 4) == 0) {
        uVar1 = *(u32 *)g_007B5DE4;
    }
    else {
        uVar1 = *(u32 *)(g_007B5DE4 + 0x4);
    }
    uVar2 = func_0032F7D0(uVar1);
    uVar2 = PS2_ADDR(func_0032A260(uVar2, *(u16 *)(param_1 + 2)));
    lVar3 = func_0032A650((char *)(auStack_150), (char *)PS2_PTR(uVar2), 0);
    if (lVar3 != 0) {
        func_0032A650((char *)(auStack_2a0), (char *)PS2_PTR(uVar2), 1);
        func_001204B0(uVar2, 0x447A18, auStack_150, auStack_2a0);
    }
    func_0032A2C0((char *)PS2_PTR(uVar2), &iStack_4);
    iVar4 = 0;
    if (0 < *(u32 *)(g_007B5DE4 + 0xC)) {
        do {
            func_00369990(iVar4);
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(u32 *)(g_007B5DE4 + 0xC));
    }
    func_0032CF30(*(u16 *)(param_1 + 8), uVar1, *(u16 *)(param_1 + 4), 1);
    lVar3 = func_0032B180();
    *(ps2ptr *)((lVar3 != 0 ^ 1) * 4 + 0x7B5DF4) = PS2_ADDR((g_00447A10));
    iVar4 = func_0032B180();
    *(int *)(iVar4 * 4 + 0x7B5DF4) = (int)uVar2;
    *(u32 *)(g_007B5DE4 + 0x18) = (u32)*(u16 *)(param_1 + 4);
    *(u32 *)(g_007B5DE4 + 0x1C) = (u32)*(u16 *)(param_1 + 6);
    *(u32 *)(g_007B5DE4 + 0x8) = uVar1;
    if (*(u16 *)(param_1 + 4) == 0) {
        *(u32 *)(g_007B5DE4 + 0x28) = (u32)*(u16 *)(param_1 + 10);
    }
    else {
        *(u32 *)(g_007B5DE4 + 0x2C) = (u32)*(u16 *)(param_1 + 10);
    }
    if (iStack_4 != -1) {
        *(u32 *)(g_007B5DE4 + 0xC) = *(u32 *)(g_007B5DE4 + 0xC) + 1;
    }
    return PS2_ADDR(param_1 + 0x20);
}

/* 0x0032A9A0, 0x1A8 bytes. */
int func_0032A9A0(u8 *param_1)
{
    int iStack_4;
    int iVar4;
    long long lVar3;
    u32 uVar1;
    unsigned long long uVar2;

    if (*(short *)(param_1 + 4) == 0) {
        uVar1 = *(u32 *)g_007B5DE4;
    }
    else {
        uVar1 = *(u32 *)(g_007B5DE4 + 0x4);
    }
    uVar2 = PS2_ADDR(func_0032A220(*(u16 *)(param_1 + 2)));
    if (*(short *)(param_1 + 10) == 0) {
        lVar3 = func_0032A1D0(*(u16 *)(param_1 + 4));
        if (lVar3 != 0) {
            uVar2 = PS2_ADDR(func_0032A220(*(u16 *)(param_1 + 0xE)));
        }
    }
    else {
        lVar3 = func_0032A170(*(u16 *)(param_1 + 4), *(u16 *)(param_1 + 0xC));
        if (lVar3 != 0) {
            uVar2 = PS2_ADDR(func_0032A220(*(u16 *)(param_1 + 0xE)));
        }
    }
    func_0032A2C0((char *)PS2_PTR(uVar2), &iStack_4);
    iVar4 = 0;
    if (0 < *(u32 *)(g_007B5DE4 + 0xC)) {
        do {
            func_00369990(iVar4);
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(u32 *)(g_007B5DE4 + 0xC));
    }
    func_0032CF30(*(u16 *)(param_1 + 8), uVar1, *(u16 *)(param_1 + 4), 1);
    lVar3 = func_0032B180();
    *(ps2ptr *)((lVar3 != 0 ^ 1) * 4 + 0x7B5DF4) = PS2_ADDR((g_00447A10));
    iVar4 = func_0032B180();
    *(int *)(iVar4 * 4 + 0x7B5DF4) = (int)uVar2;
    *(u32 *)(g_007B5DE4 + 0x18) = (u32)*(u16 *)(param_1 + 4);
    *(u32 *)(g_007B5DE4 + 0x1C) = (u32)*(u16 *)(param_1 + 6);
    *(u32 *)(g_007B5DE4 + 0x8) = uVar1;
    if (*(u16 *)(param_1 + 4) == 0) {
        *(u32 *)(g_007B5DE4 + 0x28) = (u32)*(u16 *)(param_1 + 0x10);
    }
    else {
        *(u32 *)(g_007B5DE4 + 0x2C) = (u32)*(u16 *)(param_1 + 0x10);
    }
    if (iStack_4 != -1) {
        *(u32 *)(g_007B5DE4 + 0xC) = *(u32 *)(g_007B5DE4 + 0xC) + 1;
    }
    return PS2_ADDR(param_1 + 0x20);
}

/* 0x0032AB50, 0x1C8 bytes. */
int func_0032AB50(u8 *param_1)
{
    int iStack_4;
    int iVar4;
    long long lVar3;
    u32 uVar1;
    unsigned long long uVar2;

    if (*(short *)(param_1 + 4) == 0) {
        uVar1 = *(u32 *)g_007B5DE4;
    }
    else {
        uVar1 = *(u32 *)(g_007B5DE4 + 0x4);
    }
    uVar2 = func_0032F7D0(uVar1);
    uVar2 = PS2_ADDR(func_0032A260(uVar2, *(u16 *)(param_1 + 2)));
    if (*(short *)(param_1 + 10) == 0) {
        lVar3 = func_0032A1D0(*(u16 *)(param_1 + 4));
        if (lVar3 != 0) {
            uVar2 = func_0032F7D0(uVar1);
            uVar2 = PS2_ADDR(func_0032A260(uVar2, *(u16 *)(param_1 + 0xE)));
        }
    }
    else {
        lVar3 = func_0032A170(*(u16 *)(param_1 + 4), *(u16 *)(param_1 + 0xC));
        if (lVar3 != 0) {
            uVar2 = func_0032F7D0(uVar1);
            uVar2 = PS2_ADDR(func_0032A260(uVar2, *(u16 *)(param_1 + 0xE)));
        }
    }
    func_0032A2C0((char *)PS2_PTR(uVar2), &iStack_4);
    iVar4 = 0;
    if (0 < *(u32 *)(g_007B5DE4 + 0xC)) {
        do {
            func_00369990(iVar4);
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(u32 *)(g_007B5DE4 + 0xC));
    }
    func_0032CF30(*(u16 *)(param_1 + 8), uVar1, *(u16 *)(param_1 + 4), 1);
    lVar3 = func_0032B180();
    *(ps2ptr *)((lVar3 != 0 ^ 1) * 4 + 0x7B5DF4) = PS2_ADDR((g_00447A10));
    iVar4 = func_0032B180();
    *(int *)(iVar4 * 4 + 0x7B5DF4) = (int)uVar2;
    *(u32 *)(g_007B5DE4 + 0x18) = (u32)*(u16 *)(param_1 + 4);
    *(u32 *)(g_007B5DE4 + 0x1C) = (u32)*(u16 *)(param_1 + 6);
    *(u32 *)(g_007B5DE4 + 0x8) = uVar1;
    if (*(u16 *)(param_1 + 4) == 0) {
        *(u32 *)(g_007B5DE4 + 0x28) = (u32)*(u16 *)(param_1 + 0x10);
    }
    else {
        *(u32 *)(g_007B5DE4 + 0x2C) = (u32)*(u16 *)(param_1 + 0x10);
    }
    if (iStack_4 != -1) {
        *(u32 *)(g_007B5DE4 + 0xC) = *(u32 *)(g_007B5DE4 + 0xC) + 1;
    }
    return PS2_ADDR(param_1 + 0x20);
}

/* 0x0032B3F0, 0x12C bytes. */
int func_0032B3F0(u8 *param_1)
{
    int iStack_4;
    long long lVar4;
    int uVar1;
    u32 uVar2;
    unsigned long long uVar3;

    uVar1 = *(u16 *)(param_1 + 2);
    if (*(short *)(param_1 + 4) == 0) {
        uVar2 = *(u32 *)g_007B5DE4;
    }
    else {
        uVar2 = *(u32 *)(g_007B5DE4 + 0x4);
    }
    uVar3 = func_0032F7D0(uVar2);
    uVar3 = PS2_ADDR(func_0032A260(uVar3, uVar1));
    if (*(short *)(param_1 + 10) == 0) {
        lVar4 = func_0032A1D0(*(u16 *)(param_1 + 4));
        if (lVar4 != 0) {
            if (*(short *)(param_1 + 4) == 0) {
                uVar2 = *(u32 *)g_007B5DE4;
            }
            else {
                uVar2 = *(u32 *)(g_007B5DE4 + 0x4);
            }
            uVar3 = func_0032F7D0(uVar2);
            uVar3 = PS2_ADDR(func_0032A260(uVar3, *(u16 *)(param_1 + 0xE)));
        }
    }
    else {
        lVar4 = func_0032A170(*(u16 *)(param_1 + 4), *(u16 *)(param_1 + 0xC));
        if (lVar4 != 0) {
            if (*(short *)(param_1 + 4) == 0) {
                uVar2 = *(u32 *)g_007B5DE4;
            }
            else {
                uVar2 = *(u32 *)(g_007B5DE4 + 0x4);
            }
            uVar3 = func_0032F7D0(uVar2);
            uVar3 = PS2_ADDR(func_0032A260(uVar3, *(u16 *)(param_1 + 0xE)));
        }
    }
    func_0032A2C0((char *)PS2_PTR(uVar3), &iStack_4);
    if (iStack_4 != -1) {
        func_00369890(iStack_4, *(u16 *)(param_1 + 0x12));
    }
    return PS2_ADDR(param_1 + 0x20);
}

/* 0x0032F2E0, 0xF0 bytes. */
int func_0032F2E0(int param_1)
{
    u32 auStack_70[28];
    int iVar3;
    long long lVar2;
    u32 * puVar4;
    u32 * puVar5;
    u32 uVar1;

    lVar2 = func_0032F2A0(param_1);
    puVar4 = auStack_70;
    puVar5 = (u32 *)(g_00414F10);
    iVar3 = 0xD;
    do {
        iVar3 = iVar3 + -1;
        uVar1 = puVar5[1];
        *puVar4 = *puVar5;
        puVar4[1] = uVar1;
        puVar5 = puVar5 + 2;
        puVar4 = puVar4 + 2;
    } while (0 < iVar3);
    if (lVar2 < 0x1A) {
        uVar1 = auStack_70[(int)lVar2];
    }
    else if (param_1 == 0x24) {
        uVar1 = 0;
    }
    else if (param_1 == 0x23) {
        uVar1 = 5;
    }
    else if (lVar2 == 0x21) {
        uVar1 = 0x16;
    }
    else if (lVar2 == 0x20) {
        uVar1 = 0x15;
    }
    else if (lVar2 == 0x2A) {
        uVar1 = 0;
    }
    else if (lVar2 == 0x26) {
        uVar1 = 5;
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x0032F7D0, 0xD0 bytes. */
int func_0032F7D0(int param_1)
{
    u32 auStack_d0[52];
    int bVar1;
    int iVar3;
    u32 * puVar4;
    u32 * puVar5;
    u32 uVar2;

    puVar5 = (u32 *)(g_00414F80);
    puVar4 = auStack_d0;
    iVar3 = 0x33;
    do {
        iVar3 = iVar3 + -1;
        *puVar4 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (0 < iVar3);
    if ((param_1 < 0x253) || (0x25B < param_1)) {
        if ((param_1 < 0x1A4) || (0x1B3 < param_1)) {
            bVar1 = *(u8 *)(*(u32 *)g_005BA6A0 + (int)param_1 * 0x2C + 5);
        }
        else {
            iVar3 = PS2_ADDR(func_0019FBA0((int)param_1 + -0x1A4));
            bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x24);
        }
        if (bVar1 < 0x33) {
            uVar2 = auStack_d0[bVar1];
        }
        else {
            uVar2 = 0x2D;
        }
    }
    else {
        uVar2 = 0x2D;
    }
    return uVar2;
}

/* 0x00338150, 0x40 bytes. */
void func_00338150(void)
{
    u8 * iVar3;
    u32 * puVar1;
    unsigned long long uVar2;

    iVar3 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar3 + 0x6A0));
    uVar2 = func_00327C00();
    func_00373970(2, 3, uVar2);
    *puVar1 = 1;
}

/* 0x003382B0, 0x40 bytes. */
void func_003382B0(void)
{
    u8 * iVar3;
    u32 * puVar1;
    unsigned long long uVar2;

    iVar3 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar3 + 0x6A0));
    uVar2 = func_00327C00();
    func_00373970(3, 3, uVar2);
    *puVar1 = 1;
}

/* 0x00369D30, 0x27C bytes. */
void func_00369D30(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    int iVar4;
    u8 * iVar5;
    unsigned long long uVar2;
    unsigned long long uVar3;

    param_1 = param_1 * 0xC;
    iVar4 = *(int *)((g_00442030 + 0x8) + param_1);
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, iVar4 + 0x3F53);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, iVar4 + 0x3F53);
    iVar5 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar5 + 0x18) = uVar3;
    iVar4 = *(int *)((g_00442030 + 0x4) + param_1);
    iVar1 = *(int *)(g_00442030 + param_1);
    *(unsigned long long *)(iVar5 + 0x20) = 0x3F80000080808080;
    *(long long *)(iVar5 + 0x28) = (long long)(int)(iVar1 << 4 | 8) | (long long)(int)(iVar4 << 4 | 8) << 0x10;
    *(long long *)(iVar5 + 0x38) =
              (long long)(int)((iVar1 + 0x1E) * 0x10 | 8) | (long long)(int)((iVar4 + 0x16) * 0x10 | 8) << 0x10;
    iVar4 = ((param_3 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              (long long)(param_2 * 0x10 + 0x7000) |
              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar4 = (((param_3 + 0x18) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              (long long)((param_2 + 0x20) * 0x10 + 0x7000) |
              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar2), param_4 + 1);
}

/* 0x0036FEF0, 0x128 bytes. */
int func_0036FEF0(int param_1, int param_2)
{
    int aiStack_40[16];
    int iVar2;
    int iVar3;
    int * piVar4;
    int * piVar5;
    u16 * puVar1;

    piVar5 = (int *)(g_004160A0);
    piVar4 = aiStack_40;
    iVar3 = 8;
    do {
        iVar3 = iVar3 + -1;
        iVar2 = piVar5[1];
        *piVar4 = *piVar5;
        piVar4[1] = iVar2;
        piVar5 = piVar5 + 2;
        piVar4 = piVar4 + 2;
    } while (0 < iVar3);
    puVar1 = (u16 *)func_00338410((param_1 * 0x68) / 0x68);
    iVar3 = func_002F2EA0(*puVar1);
    iVar3 = aiStack_40[iVar3];
    puVar1 = (u16 *)func_00338410((param_2 * 0x68) / 0x68);
    iVar2 = func_002F2EA0(*puVar1);
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    return (int)((g_7000015C >> 0x10) % 10) < (iVar3 + 6) - aiStack_40[iVar2];
}

/* 0x00372830, 0x5C bytes. */
int func_00372830(int param_1, int param_2)
{
    u8 * puVar1;

    if (param_1 < 0x10) {
        if (((param_2 == 0) || (param_1 < 4)) || (0xB < param_1)) {
            puVar1 = ((u8 *)PS2_PTR(((ps2ptr *)g_0044E580)[(int)param_1]));
        }
        else {
            puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0044E5D0));
        }
    }
    else {
        puVar1 = (u8 *)0;
    }
    return PS2_ADDR(puVar1);
}

/* 0x00372E60, 0x184 bytes. */
void func_00372E60(u32 *param_1, int param_2)
{
    u8 abStack_40[64];
    int bVar1;
    u8 * iVar2;
    int iVar7;
    int iVar9;
    long long lVar3;
    u8 * pbVar4;
    u8 * puVar8;
    u32 uVar5;
    u32 uVar6;

    pbVar4 = abStack_40;
    uVar5 = 0;
    do {
        *pbVar4 = (u8)uVar5;
        uVar5 = uVar5 + 1;
        pbVar4 = pbVar4 + 1;
    } while (uVar5 < 0x3D);
    uVar5 = 0;
    do {
        uVar5 = uVar5 + 1;
        uVar6 = g_7000015C * 0x41C64E6D + 0x3039;
        g_7000015C = uVar6 * 0x41C64E6D + 0x3039;
        bVar1 = abStack_40[(uVar6 >> 0x10) % 0x3D];
        abStack_40[(uVar6 >> 0x10) % 0x3D] = abStack_40[(g_7000015C >> 0x10) % 0x3D];
        abStack_40[(g_7000015C >> 0x10) % 0x3D] = bVar1;
    } while (uVar5 < 0x7A);
    iVar7 = 0;
    uVar5 = 0;
    pbVar4 = abStack_40;
    do {
        iVar9 = 0;
        puVar8 = ((u8 *)PS2_PTR(((ps2ptr *)g_00458BA0)[*pbVar4]));
        do {
            iVar2 = func_0019FBC0(iVar9);
            lVar3 = func_001207E0(puVar8, iVar2 + 0x13);
            if (lVar3 == 0) {
                puVar8 = (u8 *)0;
                break;
            }
            iVar9 = iVar9 + 1;
        } while (iVar9 < 4);
        if (puVar8 != (u8 *)0) {
            iVar7 = iVar7 + 1;
            *param_1 = PS2_ADDR(puVar8);
            param_1 = param_1 + 1;
            if (param_2 <= iVar7) {
                return;
            }
        }
        uVar5 = uVar5 + 1;
        pbVar4 = pbVar4 + 1;
        if (0x3C < uVar5) {
            return;
        }
    } while( true );
}

/* 0x0037DF90, 0x21C bytes. */
void func_0037DF90(int param_1, int param_2, int param_3, int param_4)
{
    int iVar3;
    int iVar4;
    u8 * iVar6;
    unsigned long long uVar1;
    unsigned long long uVar2;
    unsigned long long uVar5;

    uVar1 = PS2_ADDR(func_00105620());
    func_001055E0((u8 *)PS2_PTR(uVar1));
    iVar3 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    iVar4 = (iVar3 >> 9) * 0x10 + -0xE00;
    uVar5 = (unsigned long long)(param_1 * 0x10 + 0x7000);
    uVar2 = (unsigned long long)((param_1 + param_3) * 0x10 + 0x7000);
    iVar6 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar6 + 0x20) = uVar5 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar3 = (((param_2 + param_4) * 0x280) / 0x1E0) * 0x1C0;
    *(unsigned long long *)(iVar6 + 0x30) = uVar2 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    if (iVar3 < 0) {
        iVar3 = iVar3 + 0x1FF;
    }
    iVar3 = (iVar3 >> 9) * 0x10 + -0xE00;
    *(unsigned long long *)(iVar6 + 0x40) = uVar5 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    *(unsigned long long *)(iVar6 + 0x50) = uVar2 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    *(unsigned long long *)(iVar6 + 0x18) = 0x3F80000030000000;
    *(unsigned long long *)(iVar6 + 0x28) = 0x3F80000030000000;
    *(unsigned long long *)(iVar6 + 0x38) = 0x3F80000030000000;
    *(unsigned long long *)(iVar6 + 0x48) = 0x3F80000030000000;
    func_001056C0((u8 *)PS2_PTR(uVar1), 1);
}

/* 0x0037E1B0, 0x78 bytes. */
int func_0037E1B0(int param_1)
{
    int bVar1;
    int bVar2;
    u8 * puVar3;

    puVar3 = (u8 *)func_00313D50(param_1);
    bVar2 = true;
    bVar1 = false;
    if ((0x59 < param_1) && (param_1 < 99)) {
        bVar1 = true;
    }
    if ((!bVar1) && (param_1 != 0x65)) {
        bVar2 = false;
    }
    if (bVar2) {
        puVar3 = ((u8 *)PS2_PTR(((ps2ptr *)g_004593A8)[(int)param_1]));
    }
    return PS2_ADDR(puVar3);
}

/* 0x003838B0, 0x1C8 bytes. */
void func_003838B0(int param_1, int param_2)
{
    u8 * iVar2;
    unsigned long long uVar1;

    uVar1 = PS2_ADDR(func_00105620());
    func_001055E0((u8 *)PS2_PTR(uVar1));
    iVar2 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar2 + 0x20) = (long long)(0xA10 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
    *(unsigned long long *)(iVar2 + 0x30) = (long long)(0xA10 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    *(unsigned long long *)(iVar2 + 0x40) = (long long)(0xB30 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
    *(unsigned long long *)(iVar2 + 0x50) = (long long)(0xB30 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    *(unsigned long long *)(iVar2 + 0x18) = 0x3F80000040F8F8F8;
    *(unsigned long long *)(iVar2 + 0x28) = 0x3F80000040F8F8F8;
    *(unsigned long long *)(iVar2 + 0x38) = 0x3F80000040F8F8F8;
    *(unsigned long long *)(iVar2 + 0x48) = 0x3F80000040F8F8F8;
    func_001056C0((u8 *)PS2_PTR(uVar1), param_2);
    *(u32 *)(g_0056CCA4) = 6;
    *(u32 *)(g_0056CCA4 + 0x4) = 6;
    *(u32 *)(g_0056CCA4 + 0x8) = 6;
    *(u32 *)(g_0056CCA4 + 0xC) = 6;
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    func_00146B40((u8 *)PS2_PTR(param_1), 0x10, 0x14A, 0x1E0, 0x10, param_2, 0);
    *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
    *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
    *(u32 *)(g_0056CCA4) = 5;
    *(u32 *)(g_0056CCA4 + 0x4) = 5;
    *(u32 *)(g_0056CCA4 + 0x8) = 5;
    *(u32 *)(g_0056CCA4 + 0xC) = 5;
}

/* 0x00387BC0, 0x1C4 bytes. */
void func_00387BC0(void)
{
    int aiStack_100[32];
    int aiStack_180[32];
    u32 auStack_80[32];
    int iVar2;
    u8 * iVar3;
    int iVar4;
    int * piStack_1a0;
    int * piVar10;
    int * piVar6;
    int * piVar8;
    u32 * puStack_190;
    u32 * puVar5;
    u32 * puVar7;
    u32 uVar1;
    u32 uVar11;
    u32 uVar12;
    unsigned long long uVar9;

    iVar3 = func_00365460();
    puVar7 = (u32 *)(g_004174D0);
    puVar5 = auStack_80;
    iVar4 = 0xF;
    do {
        iVar4 = iVar4 + -1;
        uVar1 = puVar7[1];
        *puVar5 = *puVar7;
        puVar5[1] = uVar1;
        puVar7 = puVar7 + 2;
        puVar5 = puVar5 + 2;
    } while (0 < iVar4);
    piVar6 = aiStack_100;
    piVar8 = (int *)((g_004174D0 + 0x80));
    iVar4 = 0xF;
    do {
        iVar4 = iVar4 + -1;
        iVar2 = piVar8[1];
        *piVar6 = *piVar8;
        piVar6[1] = iVar2;
        piVar8 = piVar8 + 2;
        piVar6 = piVar6 + 2;
    } while (0 < iVar4);
    piVar6 = aiStack_180;
    piVar8 = (int *)((g_004174D0 + 0x100));
    iVar4 = 0xF;
    do {
        iVar4 = iVar4 + -1;
        iVar2 = piVar8[1];
        *piVar6 = *piVar8;
        piVar6[1] = iVar2;
        piVar8 = piVar8 + 2;
        piVar6 = piVar6 + 2;
    } while (0 < iVar4);
    puStack_190 = auStack_80;
    uVar12 = 0;
    piVar6 = aiStack_100;
    piStack_1a0 = aiStack_180;
    iVar4 = 100;
    do {
        uVar11 = 0;
        piVar8 = piVar6;
        puVar5 = puStack_190;
        piVar10 = piStack_1a0;
        do {
            if (-1 < *piVar8) {
                uVar9 = 1;
                if ((*(char *)(iVar3 + uVar12 + 0x1D) == 1) || (*piVar10 != 0)) {
                    uVar9 = 0;
                }
                func_003B4EC0(*puVar5, iVar4, 0, 1, *piVar8, *(u8 *)(iVar3 + uVar12 + 0x17) == uVar11, uVar9);
            }
            uVar11 = uVar11 + 1;
            piVar8 = piVar8 + 1;
            puVar5 = puVar5 + 1;
            piVar10 = piVar10 + 1;
        } while (uVar11 < 5);
        uVar12 = uVar12 + 1;
        piVar6 = piVar6 + 5;
        puStack_190 = puStack_190 + 5;
        piStack_1a0 = piStack_1a0 + 5;
        iVar4 = iVar4 + 0x20;
    } while (uVar12 < 6);
}

/* 0x00388340, 0x390 bytes. */
void func_00388340(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    float fVar7;
    int iVar1;
    u8 * iVar2;
    long long lVar6;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;

    lVar6 = 0x80;
    if (*(char *)(g_007B9E5D + param_6) == 0) {
        lVar6 = 0x50;
    }
    if (param_8 == 0) {
        fVar7 = 0.675;
    }
    else {
        fVar7 = 1.0;
    }
    iVar1 = PS2_ADDR(func_0030D7D0());
    iVar1 = iVar1 + *(int *)((u8 *)PS2_PTR(iVar1) + 8) * *(int *)(param_7 * 8 + iVar1 + 0x10);
    func_00106F10((u8 *)PS2_PTR(iVar1));
    uVar3 = func_00104AC0((u8 *)PS2_PTR(iVar1), 0x1D00, 1);
    uVar4 = func_00104D00((u8 *)PS2_PTR(iVar1), 0x3FFC, 1);
    uVar3 = func_00106C50(uVar3, uVar4);
    uVar3 = PS2_ADDR(func_00105860(uVar3, 0));
    fVar7 = fVar7 * 128.0;
    if (2.1474836e+09 <= fVar7) {
        fVar7 = fVar7 - 2.1474836e+09;
    }
    uVar5 = (long long)(int)fVar7 & 0xFF;
    iVar2 = (u8 *)PS2_PTR((int)uVar3);
    *(unsigned long long *)(iVar2 + 0x20) = lVar6 << 0x18 | uVar5 << 0x10 | uVar5 | uVar5 << 8 | 0x3F80000000000000
    ;
    uVar5 = (long long)(0xFFFE - param_3) << 0x20;
    *(unsigned long long *)(iVar2 + 0x28) =
              (long long)(int)(param_5 * (u32)*(u8 *)((u8 *)PS2_PTR(param_6) + (u32)(*(u8 *)g_007B9E58) * 0x18 + 0x45972C) * 0x10
                                    | 8) << 0x10 | 8;
    iVar1 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    *(long long *)(iVar2 + 0x38) =
              (long long)(int)((param_4 + -1) * 0x10 | 8) |
              (long long)(int)((param_5 * (*(u8 *)((u8 *)PS2_PTR(param_6) + (u32)(*(u8 *)g_007B9E58) * 0x18 + 0x45972C) + 1) + -1)
                                      * 0x10 | 8) << 0x10;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar2 + 0x30) =
              uVar5 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar1 = (((param_2 + param_5) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar2 + 0x40) =
              uVar5 | (long long)((param_1 + param_4) * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar3), 1);
}

/* 0x00399CD0, 0x20C bytes. */
void func_00399CD0(void)
{
    u8 auStack_40[64];
    int bVar1;
    int iVar2;
    int iVar3;
    long long lVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar7;

    func_00118850(auStack_40, 0x40);
    iVar2 = *(u32 *)g_007BA8B0;
    if (*(u32 *)(g_007BA8B0 + 0x14) == -1) {
        bVar1 = false;
        if (-1 < *(u32 *)g_007BA8B0) {
            iVar3 = func_0030AB90();
            bVar1 = iVar2 < iVar3;
        }
        if (bVar1) {
            lVar4 = func_0039A540();
            if ((lVar4 == 0) || (*(int *)(*(u32 *)(g_007BA8B0 + 0x8) * 4 + 0x7BA8D4) == 0)) {
                uVar5 = PS2_ADDR(func_003725A0(0x1C));
                func_001204B0(auStack_40, uVar5);
            }
            else {
                uVar5 = PS2_ADDR(func_003725A0(0x1B));
                func_001204B0(auStack_40, uVar5);
            }
        }
        else {
            uVar5 = PS2_ADDR(func_003725A0(0x1B));
            func_001204B0(auStack_40, uVar5);
        }
    }
    else {
        lVar4 = func_0039A160();
        if (lVar4 == -1) {
            lVar4 = func_0039A080();
            if (lVar4 == 0) {
                uVar5 = func_0039A3B0();
                lVar4 = func_0039A0C0();
                if (lVar4 == 0) {
                    lVar4 = func_0039A110();
                    if (lVar4 != 0) {
                        uVar6 = PS2_ADDR(func_003725A0(0x1E));
                        uVar7 = PS2_ADDR(func_00373010(1));
                        uVar5 = PS2_ADDR(func_0030ABF0(uVar5));
                        func_001204B0(auStack_40, uVar6, uVar7, uVar5);
                    }
                }
                else {
                    uVar6 = PS2_ADDR(func_003725A0(0x1E));
                    uVar7 = PS2_ADDR(func_00373010(0));
                    uVar5 = PS2_ADDR(func_0030ABF0(uVar5));
                    func_001204B0(auStack_40, uVar6, uVar7, uVar5);
                }
            }
            else {
                uVar5 = PS2_ADDR(func_003725A0(0x1A));
                func_001204B0(auStack_40, uVar5);
            }
        }
        else {
            uVar5 = PS2_ADDR(func_003725A0(0x1D));
            uVar6 = PS2_ADDR(func_002F2A10(lVar4));
            func_001204B0(auStack_40, uVar5, uVar6);
        }
    }
    func_003838B0(PS2_ADDR(auStack_40), 1);
}

/* 0x0039BA70, 0x50 bytes. */
void func_0039BA70(void)
{
    u8 * iVar3;
    u32 * puVar1;
    unsigned long long uVar2;

    iVar3 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar3 + 0x6A4));
    uVar2 = func_00327D60();
    func_003986E0(uVar2, 0xFFFFFFFFFFFFFFFF, 0, 0);
    func_00398650(1);
    *puVar1 = 1;
    func_003A9480(1);
}

/* 0x0039BAC0, 0x38 bytes. */
void func_0039BAC0(void)
{
    u8 * iVar3;
    long long lVar2;
    u32 * puVar1;

    iVar3 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar3 + 0x6A4));
    lVar2 = func_0039B980();
    if (lVar2 != 2) {
        *puVar1 = 2;
    }
}

/* 0x0039BFC0, 0x1D8 bytes. */
void func_0039BFC0(void)
{
    int bVar2;
    int bVar3;
    int bVar4;
    u8 * iVar5;
    long long lVar10;
    long long lVar7;
    long long lVar8;
    long long lVar9;
    u32 * puVar1;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    u32 uVar11;
    unsigned long long uVar6;

    iVar5 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar5 + 0x6AC));
    uVar6 = func_00327D50();
    lVar7 = func_002FA5A0(uVar6);
    lVar8 = func_002F9260(uVar6);
    lVar9 = func_002FA6B0(uVar6);
    bVar2 = false;
    if ((-1 < lVar7) && (lVar10 = func_0030AB90(), lVar7 < lVar10)) {
        bVar2 = true;
    }
    bVar3 = false;
    if ((-1 < lVar8) && (lVar8 < 0x19F)) {
        bVar3 = true;
    }
    bVar4 = false;
    if ((-1 < lVar9) && (lVar10 = func_0030AB90(), lVar9 < lVar10)) {
        bVar4 = true;
    }
    if (bVar2) {
        *(u8 *)(puVar1 + 8) = 0x2D;
        puVar1[4] = (int)lVar7;
    }
    uVar11 = (u32)bVar2;
    if (bVar3) {
        *(u8 *)((int)puVar1 + uVar11 + 0x20) = 0x34;
        uVar11 = uVar11 + 1;
        puVar1[5] = (int)lVar8;
    }
    if (bVar4) {
        *(u8 *)((int)puVar1 + uVar11 + 0x20) = 0x37;
        uVar11 = uVar11 + 1;
        puVar1[6] = (int)lVar9;
    }
    lVar7 = func_002FA790(uVar6);
    if (lVar7 != 0) {
        *(u8 *)((int)puVar1 + uVar11 + 0x20) = 0x38;
        uVar11 = uVar11 + 1;
    }
    lVar7 = func_002FA870(uVar6);
    if (lVar7 != 0) {
        *(u8 *)((int)puVar1 + uVar11 + 0x20) = 8;
        uVar11 = uVar11 + 1;
    }
    if (uVar11 == 0) {
        *puVar1 = 0;
    }
    else {
        *(char *)((int)puVar1 + 0x26) = (char)uVar11;
        puVar1[3] = 0;
        uStack_20 = 0x10;
        uStack_1c = 0x58;
        uStack_18 = 0x128;
        uStack_14 = 0x18;
        uStack_10 = 0x80;
        func_003DC090(0xF, &uStack_20);
        func_003DC0E0(0xF, 1, 1);
    }
}

/* 0x0039C1A0, 0x11C bytes. */
void func_0039C1A0(void)
{
    int iVar2;
    int iVar4;
    u32 * puVar1;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    unsigned long long uVar3;

    iVar2 = PS2_ADDR(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x6AC));
    iVar4 = 0;
    iVar2 = 0;
    do {
        uVar3 = func_00328330(iVar2);
        if (uVar3 < 100) {
            *(char *)((int)puVar1 + iVar4 + 0x20) = (char)uVar3;
            iVar4 = iVar4 + 1;
        }
        iVar2 = iVar2 + 1;
    } while (iVar2 < 5);
    if (iVar4 == 0) {
        *puVar1 = 0;
    }
    else {
        *(char *)((int)puVar1 + 0x26) = (char)iVar4;
        puVar1[3] = 0;
        uStack_1c = 0x60;
        uStack_20 = 0x18;
        uStack_18 = 0x96;
        uStack_14 = 0x18;
        uStack_10 = 0x80;
        func_003DC090(0x10, &uStack_20);
        func_003DC0E0(0x10, 1, 1);
        uStack_20 = 0x154;
        uStack_1c = 0x68;
        uStack_18 = 0x98;
        uStack_14 = 0xD8;
        uStack_10 = 0x80;
        func_003DC090(0x11, &uStack_20);
        func_003DC0E0(0x11, 2, 1);
    }
}

/* 0x0039C2C0, 0x11C bytes. */
void func_0039C2C0(void)
{
    int iVar2;
    int iVar4;
    u32 * puVar1;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    unsigned long long uVar3;

    iVar2 = PS2_ADDR(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar2) + 0x6AC));
    iVar4 = 0;
    iVar2 = 0;
    do {
        uVar3 = func_00328640(iVar2);
        if (uVar3 < 100) {
            *(char *)((int)puVar1 + iVar4 + 0x20) = (char)uVar3;
            iVar4 = iVar4 + 1;
        }
        iVar2 = iVar2 + 1;
    } while (iVar2 < 5);
    if (iVar4 == 0) {
        *puVar1 = 0;
    }
    else {
        *(char *)((int)puVar1 + 0x26) = (char)iVar4;
        puVar1[3] = 0;
        uStack_1c = 0x50;
        uStack_18 = 0xD8;
        uStack_14 = 0x18;
        uStack_10 = 0x80;
        uStack_20 = 0;
        func_003DC090(0x10, &uStack_20);
        func_003DC0E0(0x10, 1, 1);
        uStack_20 = 0x154;
        uStack_1c = 0x68;
        uStack_18 = 0x98;
        uStack_14 = 0xD8;
        uStack_10 = 0x80;
        func_003DC090(0x11, &uStack_20);
        func_003DC0E0(0x11, 2, 1);
    }
}

/* MISSING ['0x7bac08'] */

/* 0x003A4DA0, 0x74 bytes, matching. */
void func_003A4DA0(int param_1, int param_2, int param_3, int param_4)
{
    if (param_4 != 0) {
        func_003A37D0(param_1, param_2);
        func_003A3860(param_1, param_2);
        func_003A3920(param_1, param_2, param_3);
    }
    func_003A3DB0();
    func_003A2810(0, 1);
}

/* 0x003A5A80, 0x120 bytes. */
void func_003A5A80(void)
{
    u8 * iVar2;
    unsigned long long uVar1;

    uVar1 = PS2_ADDR(func_00105620());
    func_001055E0((u8 *)PS2_PTR(uVar1));
    iVar2 = (u8 *)PS2_PTR((int)uVar1);
    *(unsigned long long *)(iVar2 + 0x20) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
    *(unsigned long long *)(iVar2 + 0x30) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    *(unsigned long long *)(iVar2 + 0x40) = (long long)(0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
    *(unsigned long long *)(iVar2 + 0x50) = (long long)(0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
    *(unsigned long long *)(iVar2 + 0x18) = 0x3F80000020000000;
    *(unsigned long long *)(iVar2 + 0x28) = 0x3F80000020000000;
    *(unsigned long long *)(iVar2 + 0x38) = 0x3F80000020000000;
    *(unsigned long long *)(iVar2 + 0x48) = 0x3F80000020000000;
    func_001056C0((u8 *)PS2_PTR(uVar1), *(u32 *)g_007BAD38);
}

/* 0x003A8240, 0x15C bytes. */
void func_003A8240(int param_1)
{
    int cVar1;
    u8 * iVar3;
    int iVar5;
    long long lVar7;
    u8 * pbVar6;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;
    int uVar2;
    u32 uVar4;

    cVar1 = *(char *)(g_007BAE22 + param_1);
    iVar3 = func_00106F10((u8 *)PS2_PTR(*(u32 *)g_007BACC4 + *(int *)(*(u32 *)g_007BACC4 + 8) * *(int *)(*(u32 *)g_007BACC4 + 0x28)));
    uVar2 = *(u16 *)(iVar3 + 0xC);
    iVar5 = *(int *)(iVar3 + 8);
    uVar4 = func_003A60F0((param_1 & 0x1F) << 3);
    lVar7 = (long long)(int)(iVar3 + (u32)uVar2 + iVar5 + (uVar4 & 0xFF) * 4);
    uVar4 = *(u32 *)(g_0045A830 + cVar1 * 4);
    uStack_4 = uVar4 & 0xFF;
    uStack_8 = uVar4 >> 8 & 0xFF;
    uStack_c = uVar4 >> 0x10 & 0xFF;
    func_003A8130((int *)(&uStack_4), (int *)(&uStack_8), (int *)(&uStack_c));
    pbVar6 = (g_0045A830 + 0x100);
    iVar5 = 0;
    uStack_4 = uStack_4 | uStack_c << 0x10 | uStack_8 << 8;
    do {
        if (cVar1 == 30) {
            uVar4 = 0;
        }
        else if ((cVar1 == 26) || (cVar1 == 31)) {
            uVar4 = (u32)(u8)((g_0045A830 + 0x107))[-iVar5] << 0x18;
        }
        else {
            uVar4 = (u32)*pbVar6 << 0x18;
        }
        iVar5 = iVar5 + 1;
        uStack_4 = uStack_4 & 0xFFFFFF | uVar4;
        pbVar6 = pbVar6 + 1;
        *(u32 *)lVar7 = uStack_4;
        lVar7 = (long long)(int)((u32 *)lVar7 + 1);
    } while (iVar5 < 8);
}

/* 0x003B4740, 0x2FC bytes. */
void func_003B4740(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    float fVar7;
    u8 * iVar1;
    int iVar5;
    long long lVar6;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    lVar6 = 0x80;
    if (param_6 != 0) {
        lVar6 = 0x50;
    }
    if (param_5 == 0) {
        fVar7 = 0.675;
    }
    else {
        fVar7 = 1.0;
    }
    fVar7 = fVar7 * 128.0;
    if (2.1474836e+09 <= fVar7) {
        fVar7 = fVar7 - 2.1474836e+09;
    }
    uVar4 = (long long)(int)fVar7 & 0xFF;
    iVar5 = *(u32 *)g_0045D7FC + *(int *)(*(u32 *)g_0045D7FC + 8) * *(int *)(*(u32 *)g_0045D7FC + 0x68);
    func_00106F10((u8 *)PS2_PTR(iVar5));
    if (*(u32 *)g_0045D1C8 == 1) {
        uVar2 = func_00104AC0((u8 *)PS2_PTR(iVar5), 0x1320, param_4);
    }
    else {
        uVar2 = func_00104AC0((u8 *)PS2_PTR(iVar5), 0x1D00, param_4);
    }
    uVar3 = func_00104D00((u8 *)PS2_PTR(iVar5), 0x3FFC, param_4);
    uVar2 = func_00106C50(uVar2, uVar3);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    iVar1 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar1 + 0x20) = lVar6 << 0x18 | uVar4 << 0x10 | uVar4 | uVar4 << 8 | 0x3F80000000000000
    ;
    *(unsigned long long *)(iVar1 + 0x28) = 0x80008;
    *(unsigned long long *)(iVar1 + 0x38) = 0x1780778;
    uVar4 = (long long)(0xFFFE - param_3) << 0x20;
    iVar5 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar1 + 0x30) =
              uVar4 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar5 = (((param_2 + 0x18) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar1 + 0x40) =
              uVar4 | (long long)((param_1 + 0x78) * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar2), param_4);
}
/* MISSING ['0x45d1c8', '0x45d7fc'] */

/* 0x003BCB30, 0x29C bytes. */
void func_003BCB30(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar1;
    u8 * iVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;

    if (param_8 == 0) {
        uVar3 = 0x56;
    }
    else {
        uVar3 = 0x80;
    }
    param_1 = param_1 + *(int *)((u8 *)PS2_PTR(param_1) + 8) * *(int *)(param_2 * 8 + param_1 + 0x10);
    iVar1 = PS2_ADDR(func_00106F10((u8 *)PS2_PTR(param_1)));
    uVar4 = func_00104AC0((u8 *)PS2_PTR(param_1), 0x1D00, 1);
    uVar5 = func_00104D00((u8 *)PS2_PTR(param_1), 0x3FFC, 1);
    uVar4 = func_00106C50(uVar4, uVar5);
    uVar4 = PS2_ADDR(func_00105860(uVar4, 0));
    iVar2 = (u8 *)PS2_PTR((int)uVar4);
    *(unsigned long long *)(iVar2 + 0x20) = uVar3 << 0x10 | uVar3 | uVar3 << 8 | 0x3F80000080000000;
    *(unsigned long long *)(iVar2 + 0x28) = 0x80008;
    uVar3 = (long long)(0xFFFE - param_5) << 0x20;
    *(long long *)(iVar2 + 0x38) =
              (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x14) - 1) * 0x10 | 8) |
              (long long)(int)((*(u16 *)((u8 *)PS2_PTR(iVar1) + 0x16) - 1) * 0x10 | 8) << 0x10;
    iVar1 = ((param_4 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar2 + 0x30) =
              uVar3 | (long long)(param_3 * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar1 = (((param_4 + param_7) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0x1FF;
    }
    *(unsigned long long *)(iVar2 + 0x40) =
              uVar3 | (long long)((param_3 + param_6) * 0x10 + 0x7000) |
                              (long long)(((iVar1 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar4), 1);
}

/* 0x003BDE90, 0x27C bytes. */
void func_003BDE90(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    int iVar4;
    u8 * iVar5;
    unsigned long long uVar2;
    unsigned long long uVar3;

    param_1 = param_1 * 0xC;
    iVar4 = *(int *)((g_00442030 + 0x8) + param_1);
    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, iVar4 + 0x3F53);
    uVar2 = PS2_ADDR(func_00105860(uVar2, 0));
    uVar3 = func_00106C90(*(unsigned long long *)g_0068F0F8, iVar4 + 0x3F53);
    iVar5 = (u8 *)PS2_PTR((int)uVar2);
    *(unsigned long long *)(iVar5 + 0x18) = uVar3;
    iVar4 = *(int *)((g_00442030 + 0x4) + param_1);
    iVar1 = *(int *)(g_00442030 + param_1);
    *(unsigned long long *)(iVar5 + 0x20) = 0x3F80000080808080;
    *(long long *)(iVar5 + 0x28) = (long long)(int)(iVar1 << 4 | 8) | (long long)(int)(iVar4 << 4 | 8) << 0x10;
    *(long long *)(iVar5 + 0x38) =
              (long long)(int)((iVar1 + 0x1E) * 0x10 | 8) | (long long)(int)((iVar4 + 0x16) * 0x10 | 8) << 0x10;
    iVar4 = ((param_3 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x30) =
              (long long)(param_2 * 0x10 + 0x7000) |
              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    iVar4 = (((param_3 + 0x18) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar4 < 0) {
        iVar4 = iVar4 + 0x1FF;
    }
    *(unsigned long long *)(iVar5 + 0x40) =
              (long long)((param_2 + 0x20) * 0x10 + 0x7000) |
              (long long)(((iVar4 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10 | 0xFFFE00000000;
    func_00105900((u8 *)PS2_PTR(uVar2), param_4 + 1);
}

/* 0x003BFD80, 0x70 bytes. */
void func_003BFD80(void)
{
    u8 * iVar1;
    int iVar2;

    iVar2 = 0;
    iVar1 = g_007BEAD0;
    do {
        func_00382770(iVar2, *(u32 *)g_007BEAD4 == iVar2, iVar1 + 0xC);
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x44;
    } while (iVar2 < 3);
    func_001A7DC0((char *)(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C730))), 0x80, 1);
}

/* 0x003E3A50, 0x284 bytes. */
void func_003E3A50(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    u8 * iVar1;
    int iVar5;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

    if (param_6 == 0) {
        uVar2 = 0x48;
    }
    else {
        uVar2 = 0x80;
    }
    iVar5 = g_0045D838 + *(int *)(g_0045D838 + 8) * *(int *)(g_0045D838 + 0x110);
    func_00106F10((u8 *)PS2_PTR(iVar5));
    uVar3 = func_00104AC0((u8 *)PS2_PTR(iVar5), 0x1320, param_4);
    uVar4 = func_00104D00((u8 *)PS2_PTR(iVar5), 0x3FFC, param_4);
    uVar3 = func_00106C50(uVar3, uVar4);
    uVar3 = PS2_ADDR(func_00105860(uVar3, 0));
    iVar1 = (u8 *)PS2_PTR((int)uVar3);
    *(unsigned long long *)(iVar1 + 0x20) = uVar2 << 0x10 | uVar2 | uVar2 << 8 | 0x3F80000080000000;
    *(unsigned long long *)(iVar1 + 0x28) = (long long)(int)(param_5 << 9 | 8) << 0x10 | 8;
    *(unsigned long long *)(iVar1 + 0x38) = (long long)(int)((param_5 * 0x20 + 0x1F) * 0x10 | 8) << 0x10 | 0x978;
    uVar2 = (long long)(0xFFFE - param_3) << 0x20;
    iVar5 = ((param_2 * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar1 + 0x30) =
              uVar2 | (long long)(param_1 * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    iVar5 = (((param_2 + 0x20) * 0x280) / 0x1E0) * 0x1C0;
    if (iVar5 < 0) {
        iVar5 = iVar5 + 0x1FF;
    }
    *(unsigned long long *)(iVar1 + 0x40) =
              uVar2 | (long long)((param_1 + 0x98) * 0x10 + 0x7000) |
                              (long long)(((iVar5 >> 9) * 0x10 + -0xE00) / g_70000154 + 0x8000) << 0x10;
    func_00105900((u8 *)PS2_PTR(uVar3), param_4);
}

/* MISSING ['0x7bfb38'] */

/* 0x003EE840, 0x29C bytes. */
int func_003EE840(void)
{
    u8 * iVar5;
    u32 * puVar1;
    int sVar4;
    int uVar2;
    int uVar3;
    u32 uVar6;

    iVar5 = (u8 *)(func_002FC2C0());
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar5 + 0x6AC));
    uVar6 = 0;
    if ((long long)(*(char *)g_007BFDCD) << 0x3F < 0) {
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar2 = 0;
        }
        else {
            uVar2 = *(u16 *)g_0050074C;
        }
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar3 = 0;
        }
        else {
            uVar3 = *(u16 *)(g_0050074C + 0x2);
        }
        if ((uVar2 & 0x40) == 0) {
            if ((uVar2 & 0x10) == 0) {
                if ((uVar3 & 0x1000) == 0) {
                    if ((uVar3 & 0x4000) != 0) {
                        if ((long long)*(short *)(puVar1 + 7) == 0x1D) {
                            if ((uVar2 & 0x4000) != 0) {
                                *(u16 *)((int)puVar1 + 0x1E) = 0;
                                *(u16 *)(puVar1 + 7) = 0;
                                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                            }
                        }
                        else {
                            if (((long long)*(short *)(puVar1 + 7) == (long long)(*(short *)((int)puVar1 + 0x1E) + 9)) &&
                                  (sVar4 = *(short *)((int)puVar1 + 0x1E) + 1, *(short *)((int)puVar1 + 0x1E) = sVar4
                                  , 0x14 < sVar4)) {
                                *(u16 *)((int)puVar1 + 0x1E) = 0x14;
                            }
                            *(short *)(puVar1 + 7) = *(short *)(puVar1 + 7) + 1;
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        }
                    }
                }
                else if (*(short *)(puVar1 + 7) == 0) {
                    if ((uVar2 & 0x1000) != 0) {
                        *(u16 *)((int)puVar1 + 0x1E) = 0x14;
                        *(u16 *)(puVar1 + 7) = 0x1D;
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        return 0;
                    }
                }
                else {
                    if ((*(short *)(puVar1 + 7) == *(short *)((int)puVar1 + 0x1E)) &&
                          (sVar4 = *(short *)((int)puVar1 + 0x1E) + -1, *(short *)((int)puVar1 + 0x1E) = sVar4,
                          sVar4 < 0)) {
                        *(u16 *)((int)puVar1 + 0x1E) = 0;
                    }
                    *(short *)(puVar1 + 7) = *(short *)(puVar1 + 7) + -1;
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                }
            }
            else {
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                uVar6 = 1;
                puVar1[2] = 0xFFFFFFFF;
                *(u16 *)((int)puVar1 + 0x1E) = 0xFFFF;
                *(u16 *)(puVar1 + 7) = 0xFFFF;
                *puVar1 = 0;
            }
        }
        else {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            puVar1[2] = 0;
            puVar1[1] = 1;
        }
    }
    else {
        uVar6 = 0;
    }
    return uVar6;
}

/* 0x003F0FC0, 0x5C bytes. */
int func_003F0FC0(int param_1, int param_2)
{
    u32 auStack_120[72];
    int iVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 uVar1;

    puVar3 = auStack_120;
    puVar4 = (u32 *)(g_0041D920);
    iVar2 = 0x24;
    do {
        iVar2 = iVar2 + -1;
        uVar1 = puVar4[1];
        *puVar3 = *puVar4;
        puVar3[1] = uVar1;
        puVar4 = puVar4 + 2;
        puVar3 = puVar3 + 2;
    } while (0 < iVar2);
    return auStack_120[param_1 * 3 + (param_2 & 0xFF)];
}

/* 0x003F11D0, 0x20C bytes. */
void func_003F11D0(void)
{
    u8 auStack_410[1032];
    int iStack_4;
    int iStack_8;
    int iVar1;
    int iVar2;
    u8 * iVar3;
    long long lVar4;
    u8 * puVar6;
    unsigned long long uVar5;

    if (0 < *(u32 *)g_007BFDD8) {
        lVar4 = func_003F0FC0(*(u32 *)(g_007BFDD8 + 0x4), *(u8 *)(g_007BFDD8 + 0x8));
        if (lVar4 == -1) {
            puVar6 = g_0045C998;
        }
        else {
            puVar6 = ((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[(int)lVar4 + 0x2E0]));
        }
        func_00147160(puVar6, auStack_410, 0x154, &iStack_4, &iStack_8);
        iVar1 = -iStack_4 + 0x200;
        if (iVar1 < 0) {
            iVar1 = -iStack_4 + 0x201;
        }
        iVar2 = -iStack_8 + 0x180;
        if (iVar2 < 0) {
            iVar2 = -iStack_8 + 0x181;
        }
        uVar5 = PS2_ADDR(func_00105410());
        iVar3 = (u8 *)PS2_PTR((int)uVar5);
        *(unsigned long long *)(iVar3 + 0x18) = 0x3F80000020000000;
        *(unsigned long long *)(iVar3 + 0x20) = (long long)(-0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00007000;
        *(unsigned long long *)(iVar3 + 0x28) = (long long)(0xE00 / g_70000154 + 0x8000) << 0x10 | 0xFFFE00009000;
        func_001054B0((u8 *)PS2_PTR(uVar5), 3);
        func_001A4340((iVar1 >> 1) + -0x10, (iVar2 >> 1) + -0x10, 0, iStack_4 + 0x20, iStack_8 + 0x20, 0x80, 3)
        ;
        *(u32 *)(g_0056CCA4) = 3;
        *(u32 *)(g_0056CCA4 + 0x4) = 3;
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x8) = 3;
        *(u32 *)(g_0056CCA4 + 0xC) = 3;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        func_00146270(auStack_410, iVar1 >> 1, iVar2 >> 1, 3, 0);
        *(u32 *)(g_0056CCA4 + 0x1C) = 0x41800000;
        *(u32 *)(g_0056CCA4 + 0x20) = 0x41800000;
        *(u32 *)(g_0056CCA4) = 5;
        *(u32 *)(g_0056CCA4 + 0x4) = 5;
        *(u32 *)(g_0056CCA4 + 0x8) = 5;
        *(u32 *)(g_0056CCA4 + 0xC) = 5;
    }
}
