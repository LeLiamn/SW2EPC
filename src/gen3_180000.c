/*
 * gen3_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_00732218[0x18];
extern u8 g_0073221C[0x18];
extern u8 g_00799340[0x18];
extern u8 g_007B9A30[0x18];
extern u8 g_007BBC80[0x18];
extern u8 g_007BBE80[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"
int func_002CCE60();
int func_00397B10();

#define true 1
#define false 0

extern u8 g_00412620[0x38];
extern u8 g_00415E30[0x24];
extern u8 g_0041C160[0x20];
extern u8 g_00426620[0x4];
extern u8 g_00428B79[0x4];
extern u8 g_00441F80[0x1C];
extern u8 g_00448410[0x17];
extern u8 g_0050074C[0xA2];
extern u8 g_00574DE0[0x10];
extern u8 g_00669D60[0x10];
extern u8 g_00669DB8[0x20];
extern u8 g_00669F60[0x4];
extern u8 g_00669F98[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_00732214[0xC];
extern u8 g_007325A8[0x8];
extern u8 g_00752940[0x4];
extern u8 g_0076E9C0[0x10];
extern u8 g_007991C0[0x10];
extern u8 g_0079934C[0x4];
extern u8 g_00799A68[0x4];
extern u8 g_007B95E0[0x18];
extern u8 g_007B99F0[0x40];
extern u8 g_007BA8B0[0xC];
extern u8 g_007BAA64[0x4];
extern int g_0045D460;   /* (small data) */
extern int g_0045D5BC;   /* (small data) */
extern int g_0045D5D8;   /* (small data) */
extern int g_0045D820;   /* (small data) */

int func_0011B758();
int func_0011ED38();
int func_001204B0();
int func_00120928();
int func_00120A40();
int func_0017DF10();
int func_001FF100();
void *func_002153C0();
void *func_00215400();
int func_00217C40();
int func_002456C0();
int func_0029A1C0();
int func_002C5930();
int func_002C7C00();
int func_002CD5E0();
int func_0032F420();
int func_003646A0();
int func_00374250();
int func_003886D0();
int func_00388DA0();
void *func_0038E730();
void *func_0038E750();
int func_0038E770();
int func_0038E880();
int func_00397F40();
int func_003D96A0();
void func_002D2160(int param_1, int param_2, int param_3, int param_4, int param_5);
int func_003B9770(int param_1);

/* 0x001EDAD0, 0x74 bytes. */
int func_001EDAD0(u8 *param_1, u16 *param_2, int param_3)
{
    u8 * lVar1;

    if ((param_3 & 0xFF) < 3) {
        lVar1 = func_00215400(param_1, param_3);
    }
    else {
        lVar1 = func_002153C0();
    }
    if (lVar1 == 0) {
        *param_2 = *(u16 *)param_1;
    }
    else {
        *param_2 = *(u16 *)lVar1;
    }
    return lVar1 != 0;
}

/* 0x001F49A0, 0x16C bytes. */
void func_001F49A0(unsigned long long *param_1, u8 *param_2, int param_3)
{
    u8 auStack_4[4];
    int lVar3;
    u32 uVar1;
    u32 uVar2;
    int uVar4;
    u32 uVar5;

    lVar3 = func_00106E00(param_2);
    uVar2 = *(u32 *)(g_00732214 + 0x8);
    uVar5 = *(u32 *)(g_00732214 + 0x4);
    uVar1 = *(u32 *)g_00732214;
    if (lVar3 != 0) {
        if (*(int *)(param_2 + 0x14) == 0) {
            func_001073E0(param_2, *(u32 *)g_00732214, *(u32 *)(g_00732214 + 0x4), (int *)(g_00732214), (int *)(auStack_4));
        }
        else if (*(char *)(param_2 + 0x23) == 5) {
            func_001073E0(param_2, *(u32 *)g_00732214, *(u32 *)(g_00732214 + 0x8), (int *)(g_00732214), (int *)(g_0073221C));
            uVar5 = uVar2;
        }
        else {
            func_001073E0(param_2, *(u32 *)g_00732214, *(u32 *)(g_00732214 + 0x4), (int *)(g_00732214), (int *)(g_00732218));
            if ((*(u32 *)(g_00732214 + 0x4) & 3) == 0) {
                *(u32 *)(g_00732214 + 0x4) = *(u32 *)(g_00732214 + 0x4) - 8;
            }
        }
        if (param_3 == 0) {
            uVar4 = func_00107480(param_2, uVar1, uVar5);
            *param_1 = uVar4;
            param_1[1] = 0x60;
        }
        else {
            param_1[1] = (param_3 & 0xFFFFFFFF) << 2 | 0x1E8B00080360;
        }
    }
}

/* 0x0020FD50, 0x108 bytes. */
int func_0020FD50(int param_1)
{
    int iVar1;
    int lVar3;
    u32 uVar2;

    lVar3 = PS2_ADDR(func_0034ECA0((u8 *)PS2_PTR(param_1)));
    if (lVar3 == 0) {
        lVar3 = func_00353460((u8 *)PS2_PTR(param_1));
        if (lVar3 < 1) {
            if (lVar3 < 0) {
                iVar1 = (int)((unsigned long long)((int)((int)lVar3 * 0x7F) * -0x51EB851F) >> 0x20);
                uVar2 = ((iVar1 >> 5) - (iVar1 >> 0x1F)) + 0x80U | 0x70808000;
            }
            else {
                uVar2 = 0x70808080;
            }
        }
        else {
            uVar2 = (((int)lVar3 * 0x7F) / 100 + 0x80) * 0x10000 | 0x70008080;
        }
    }
    else {
        lVar3 = func_0034EDB0((u8 *)PS2_PTR(lVar3));
        if (lVar3 == 1) {
            uVar2 = 0x70303080;
        }
        else if (lVar3 == 0) {
            uVar2 = 0x70803030;
        }
        else {
            uVar2 = 0x70404040;
        }
    }
    return uVar2;
}

/* 0x00217BC0, 0x78 bytes. */
void func_00217BC0(void)
{
    u32 uVar1;

    uVar1 = 2;
    if (*(int *)PS2_PTR((g_0045D460 + 0xA0)) == 2) {
        uVar1 = 0;
    }
    else if (*(int *)PS2_PTR((g_0045D460 + 0xA0)) == 3) {
        uVar1 = 0;
    }
    else if (*(int *)PS2_PTR((g_0045D460 + 0x110)) == 2) {
        uVar1 = 1;
    }
    else if (*(int *)PS2_PTR((g_0045D460 + 0x110)) == 3) {
        uVar1 = 1;
    }
    if (uVar1 < 2) {
        func_00217C40();
    }
}

/* 0x00245FC0, 0x5C bytes. */
int func_00245FC0(u8 *param_1, int param_2)
{
    int bVar1;
    u16 * puVar2;

    if (*(u16 *)(param_1 + 0x58) == 0xFFFF) {
        puVar2 = (u16 *)0;
    }
    else {
        puVar2 = (u16 *)PS2_PTR((*(u32 *)g_00752940 + (u32)*(u16 *)(param_1 + 0x58) * 2));
    }
    bVar1 = *puVar2 <= param_2;
    if (bVar1) {
        *puVar2 = 0;
    }
    else {
        *puVar2 = *puVar2 - (short)param_2;
    }
    return bVar1;
}

/* 0x00254210, 0x100 bytes. */
void func_00254210(void)
{
    u8 * iVar4;
    u8 * iVar5;
    u8 * iVar6;
    int iVar7;
    int uVar1;
    int uVar2;
    u32 uVar3;

    uVar2 = PS2_ADDR(func_001026D0(1, 0x51D, 0, 1, 0, 0, (char *)PS2_PTR(0x43F458), 0x206));
    iVar7 = 0;
    iVar6 = g_00669D60;
    iVar5 = g_00574DE0;
    iVar4 = g_0076E9C0;
    do {
        if (*(int *)(iVar6 + 0xA0) != 0) {
            if (*(int *)(iVar5 + 0x110) == 0) {
                uVar1 = 0x6A;
            }
            else {
                uVar1 = *(u8 *)PS2_PTR((*(int *)(iVar5 + 0x110) + 0x1C));
            }
            uVar3 = func_002540D0(*(u32 *)(iVar5 + 0x118), uVar1);
            if (0x139 < uVar3) {
                uVar3 = 0;
            }
            func_00118AC0((u32 *)(iVar4), (u8 *)PS2_PTR((int)uVar2 + (int)uVar3 * 0x140), 0x140);
        }
        iVar7 = iVar7 + 1;
        iVar6 = iVar6 + 0x48;
        iVar5 = iVar5 + 0x630;
        iVar4 = iVar4 + 0x140;
    } while (iVar7 < 2);
    func_00102EC0((u8 *)PS2_PTR(uVar2));
}

/* 0x00263280, 0x2C bytes. */
void func_00263280(int param_1)
{
    if (*(u16 *)(g_007325A8 + 0x2) == param_1) {
        *(u16 *)(g_007325A8 + 0x4) = 0;
        *(u16 *)(g_007325A8) = 0x96;
        *(u16 *)(g_007325A8 + 0x6) = 0;
    }
}

/* 0x00290470, 0xEC bytes. */
int func_00290470(void)
{
    int lVar1;
    int lVar4;
    u32 uVar2;
    int uVar3;

    lVar1 = func_0036D2E0();
    if ((((lVar1 != 0) && (lVar1 = func_00362570(), lVar1 != 1)) &&
            (lVar1 = func_00362570(), lVar1 != 3)) &&
          ((lVar1 = func_00362570(), lVar1 != 5 &&
            ((uVar2 = func_00362570(), uVar2 < 6 || (uVar2 = func_00362570(), 0xF < uVar2)))))) {
        uVar3 = func_00327D50();
        lVar1 = func_002FA5A0(uVar3);
        lVar4 = func_0030AB90();
        if (lVar1 < lVar4) {
            uVar3 = func_00327D50();
            uVar3 = func_002FA5A0(uVar3);
            lVar1 = func_002F8CB0(uVar3);
            if (lVar1 != 0) {
                return 1;
            }
        }
    }
    return 0;
}

/* 0x0029CFB0, 0x48 bytes. */
int func_0029CFB0(u8 *param_1, int param_2)
{
    u32 uVar1;

    if (param_1 != 0) {
        uVar1 = 0;
        do {
            if (*(u8 *)(param_1 + uVar1 + 4) == param_2) {
                return 1;
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < 2);
    }
    return 0;
}

/* 0x0029DE30, 0xBC bytes. */
void func_0029DE30(float param_1, float param_2, float param_3, float *param_4)
{
    float fVar1;

    fVar1 = *param_4;
    if (param_1 < fVar1) {
        *param_4 = fVar1 - param_1;
    }
    else if (fVar1 < -param_1) {
        *param_4 = fVar1 + param_1;
    }
    else {
        *param_4 = 0.0f;
    }
    fVar1 = param_4[1];
    if (param_2 < fVar1) {
        param_4[1] = fVar1 - param_2;
    }
    else if (fVar1 < -param_2) {
        param_4[1] = fVar1 + param_2;
    }
    else {
        param_4[1] = 0.0f;
    }
    fVar1 = param_4[2];
    if (param_3 < fVar1) {
        param_4[2] = fVar1 - param_3;
    }
    else if (fVar1 < -param_3) {
        param_4[2] = fVar1 + param_3;
    }
    else {
        param_4[2] = 0.0f;
    }
}

/* 0x002BFB90, 0x118 bytes. */
void func_002BFB90(u16 *param_1, int param_2)
{
    u8 * iVar2;
    int iVar3;
    u32 uVar1;

    *(u32 *)(g_0079934C) = 0;
    g_0045D5D8 = 0;
    iVar3 = (int)((param_2 & 0xFFFFFFFF) / 0x60);
    iVar2 = g_007991C0;
    do {
        if (iVar3 == 0) {
            return;
        }
        if (*(u32 *)g_00669DB8 == 2) {
            uVar1 = *(u32 *)PS2_PTR(((*(u32 *)g_00669F98 % 5) * 4 + 0x669DD4));
        }
        else {
            uVar1 = *(u32 *)(g_00669DB8 + 0x1C);
        }
        if (*param_1 == uVar1) {
            if (param_1[1] == 0) {
                if (3 < g_0045D5D8) {
                    return;
                }
                func_00118AC0((u32 *)(iVar2), (u8 *)(param_1), 0x60);
                iVar2 = iVar2 + 0x60;
                g_0045D5D8 = g_0045D5D8 + 1;
            }
            else {
                func_00118AC0((u32 *)(g_00799340), (u8 *)(param_1), 0x60);
            }
        }
        iVar3 = iVar3 + -1;
        param_1 = param_1 + 0x30;
    } while( true );
}

/* 0x002C2EE0, 0xE0 bytes. */
int func_002C2EE0(int param_1, int param_2, int param_3)
{
    int bVar1;
    u8 * iVar2;
    int lVar3;
    u32 uVar4;

    lVar3 = PS2_ADDR(func_0027E5F0(param_1));
    uVar4 = param_3 & 0xFF;
    if ((uVar4 == 3) || (uVar4 == 1)) {
        bVar1 = false;
    }
    else if ((uVar4 == 2) || (uVar4 == 0)) {
        bVar1 = true;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        if (lVar3 == 0) {
            if (g_0045D5BC == 0) {
                return false;
            }
            lVar3 = PS2_ADDR(func_0027E8C0(param_1, param_3));
            return lVar3 != 0;
        }
        func_002C2E50((u8 *)PS2_PTR(lVar3));       /* the original reuses v0, which still holds lVar3 */
        *(u32 *)((u8 *)PS2_PTR(lVar3) + 4) = 0;
    }
    else if (lVar3 != 0) {
        func_002C2E50((u8 *)PS2_PTR(lVar3));
        func_0027E610(param_1);
    }
    return true;
}

/* 0x002C80A0, 0x128 bytes. */
void func_002C80A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar5;
    u32 * puVar4;
    u32 uVar1;
    int uVar2;
    u8 * uVar3;

    uVar2 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F5C);
    uVar3 = func_001050F0();
    *(unsigned long long *)(uVar3 + 0x10) = 0x8000000044;
    *(unsigned long long *)(uVar3 + 0x18) = 0x43;
    func_00105230(uVar3, param_7);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        uVar1 = PS2_ADDR(func_00105860(uVar2, 0));
        *puVar4 = uVar1;
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
    func_002C7C00(auStack_10[0], param_1, param_2, param_3, param_4, param_5, 0x45CF54, param_6);
    iVar5 = 0;
    puVar4 = auStack_10;
    do {
        func_00105900((u8 *)PS2_PTR(*puVar4), param_7);
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
    } while (iVar5 < 3);
}

/* 0x002CD480, 0x154 bytes. */
void func_002CD480(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar3 = (int)param_5;
    iVar1 = 1;
    while (iVar3 = iVar3 / 10, 1.0f <= (float)iVar3) {
        iVar1 = iVar1 + 1;
    }
    iVar3 = 0;
    if (0 < param_6 - iVar1) {
        iVar2 = 0;
        do {
            func_002CCE60(0, param_3, param_1 + iVar2, param_2, 0, param_7, param_7, 0x80);
            iVar3 = iVar3 + 1;
            iVar2 = iVar2 + (int)param_7;
        } while (iVar3 < param_6 - iVar1);
    }
    func_002CD5E0(param_5, param_3, param_1 + (int)param_7 * iVar3, param_2, 0, param_7, param_7, 0x80);
}

/* 0x002D83E0, 0xA0 bytes, matching. */
void func_002D83E0(u8 *param_1, int param_2)
{
    int lVar1;
    u32 uVar2;

    lVar1 = func_002D8370();
    if ((lVar1 == 0) && (lVar1 = func_0022DCA0(), lVar1 == 0)) {
        *(u32 *)(param_1 + 0x6C) = 3;
    }
    if (param_2 == 2) {
        uVar2 = func_0022DC40();
        if ((0x2A5 < uVar2) || (*(int *)(param_1 + 0x20) == 2)) {
            *(u32 *)(param_1 + 0x6C) = 1;
        }
    }
    else if (*(int *)(param_1 + 0x20) == 2) {
        *(u32 *)(param_1 + 0x6C) = 1;
    }
}

/* 0x002E0590, 0x2C bytes. */
void func_002E0590(int param_1, int param_2, int param_3)
{
    u32 uStack_4;
    u32 uStack_8;

    uStack_8 = param_2;
    uStack_4 = param_3;
    func_002456C0(param_1, 0x442910, &uStack_8);
}

/* 0x00328D00, 0xD8 bytes. */
void func_00328D00(int param_1, int param_2)
{
    int bVar1;
    int iVar3;
    int lVar2;
    u8 * pbVar5;
    u32 uVar4;

    bVar1 = false;
    if (-1 < (int)param_1) {
        lVar2 = func_0030AB90();
        bVar1 = (int)param_1 < lVar2;
    }
    if (bVar1) {
        iVar3 = (int)param_1;
        if ((int)param_1 < 0) {
            iVar3 = iVar3 + 7;
        }
        pbVar5 = (u8 *)PS2_PTR(((iVar3 >> 3) + 0x68F035));
        if (param_2 == 0) {
            uVar4 = (u32)(param_1 & 7);
            if (((int)param_1 < 0) && ((param_1 & 7) != 0)) {
                uVar4 = uVar4 - 8;
            }
            *pbVar5 = *pbVar5 & ~(u8)(1 << (uVar4 & 0x1F));
        }
        else {
            uVar4 = (u32)(param_1 & 7);
            if (((int)param_1 < 0) && ((param_1 & 7) != 0)) {
                uVar4 = uVar4 - 8;
            }
            *pbVar5 = *pbVar5 | (u8)(1 << (uVar4 & 0x1F));
        }
    }
}

/* 0x00328EC0, 0xD8 bytes. */
void func_00328EC0(int param_1, int param_2)
{
    int bVar1;
    int iVar3;
    int lVar2;
    u8 * pbVar5;
    u32 uVar4;

    bVar1 = false;
    if (-1 < (int)param_1) {
        lVar2 = func_0030AB90();
        bVar1 = (int)param_1 < lVar2;
    }
    if (bVar1) {
        iVar3 = (int)param_1;
        if ((int)param_1 < 0) {
            iVar3 = iVar3 + 7;
        }
        pbVar5 = (u8 *)PS2_PTR(((iVar3 >> 3) + 0x68F039));
        if (param_2 == 0) {
            uVar4 = (u32)(param_1 & 7);
            if (((int)param_1 < 0) && ((param_1 & 7) != 0)) {
                uVar4 = uVar4 - 8;
            }
            *pbVar5 = *pbVar5 & ~(u8)(1 << (uVar4 & 0x1F));
        }
        else {
            uVar4 = (u32)(param_1 & 7);
            if (((int)param_1 < 0) && ((param_1 & 7) != 0)) {
                uVar4 = uVar4 - 8;
            }
            *pbVar5 = *pbVar5 | (u8)(1 << (uVar4 & 0x1F));
        }
    }
}

/* 0x0032FAA0, 0x1DC bytes. */
void func_0032FAA0(void)
{
    u32 auStack_30[12];
    int iVar8;
    int iVar9;
    int lVar3;
    u32 * puVar7;
    int uVar1;
    int uVar2;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;

    uVar1 = func_0032F780();
    func_003630C0();
    iVar9 = 0;
    puVar7 = auStack_30;
    do {
        if (iVar9 < 8) {
            uVar2 = func_0032F170(uVar1, iVar9);
            lVar3 = func_0032F420(uVar2);
        }
        else {
            lVar3 = func_0032F1A0(uVar1, iVar9 + -8);
        }
        if (lVar3 != -1) {
            *puVar7 = (int)lVar3;
            puVar7 = puVar7 + 1;
        }
        iVar9 = iVar9 + 1;
    } while (iVar9 < 0xF);
    lVar3 = func_0032F780();
    if (((lVar3 == 0x12) || (lVar3 == 0x11)) || (lVar3 == 0x10)) {
        func_003622F0(0, 2);
    }
    else {
        func_003622F0(0, 0);
    }
    func_003622F0(1, 8);
    uVar1 = func_0032F060(uVar1);
    func_00362390(uVar1);
    func_00362320(0);
    uVar4 = func_00362320(1);
    iVar8 = 0;
    iVar9 = 0;
    puVar7 = auStack_30;
    do {
        uVar5 = func_00337A10(*puVar7);
        if (uVar5 < 0x19F) {
            uVar1 = func_00337A10(*puVar7);
            func_003620B0(0, iVar8, uVar1);
            iVar8 = iVar8 + 1;
        }
        iVar9 = iVar9 + 1;
        puVar7 = puVar7 + 1;
    } while (iVar9 < 9);
    if (uVar4 < 8) {
        func_003620B0(0, uVar4, 0);
    }
    func_00362550(0);
    func_00362590(1);
    uVar6 = 0;
    do {
        func_00362630(uVar6, 10);
        uVar6 = uVar6 + 1;
    } while (uVar6 < 2);
    func_003627C0(0);
}

/* 0x0032FDD0, 0xE0 bytes. */
void func_0032FDD0(int param_1, u8 *param_2, u32 *param_3)
{
    int bVar1;
    u32 uVar2;
    u32 uVar3;

    uVar2 = func_00120A40((char *)PS2_PTR(param_1));
    if (uVar2 < 0x86) {
        func_0032F6C0((char *)(param_2), (char *)PS2_PTR(param_1));
        bVar1 = *param_2;
        while (bVar1 != 0) {
            bVar1 = *param_2;
            if (((bVar1 < 0x80) || (0x9F < bVar1)) && ((bVar1 < 0xE0 || (0xFC < bVar1)))) {
                if (bVar1 == 0x40) {
                    *param_2 = 0;
                    uVar3 = func_0011B758(param_2 + 1);
                    *param_3 = uVar3;
                    return;
                }
                param_2 = param_2 + 1;
            }
            else {
                param_2 = param_2 + 2;
            }
            bVar1 = *param_2;
        }
    }
    else {
        *param_2 = 0;
        *param_3 = 0;
    }
}

/* 0x00364980, 0x26C bytes. */
void func_00364980(void)
{
    u8 auStack_30[48];
    u32 auStack_50[8];
    u32 auStack_80[4];
    int iVar2;
    int iVar3;
    int iVar4;
    u32 * puVar8;
    u32 uStack_60;
    u32 uStack_64;
    u32 uStack_68;
    u32 uStack_6c;
    u32 uStack_70;
    u32 uVar1;
    u32 uVar10;
    int uVar5;
    u32 uVar6;
    int uVar7;
    u32 uVar9;

    auStack_50[0] = 10;
    auStack_50[1] = 10;
    auStack_50[2] = 10;
    auStack_50[3] = 10;
    auStack_50[4] = 10;
    auStack_50[5] = 10;
    uVar5 = func_0036D500(1);
    uVar5 = func_00364220(uVar5, (u32 *)(auStack_30));
    uVar1 = func_00364410();
    if (5 < uVar1) {
        uVar1 = 5;
    }
    iVar2 = func_00363EA0(1);
    iVar2 = iVar2 * 4;
    uVar10 = 0;
    if ((1 < uVar1) && (uVar6 = func_003646A0(auStack_30, uVar5), uVar6 < 10)) {
        auStack_50[0] = (u32)uVar6;
        uVar10 = 1;
        iVar3 = func_003F7110(uVar6);
        iVar2 = iVar2 - iVar3;
    }
    auStack_80[0] = *(u32 *)g_00415E30;
    auStack_80[1] = *(u32 *)(g_00415E30 + 0x4);
    auStack_80[2] = *(u32 *)(g_00415E30 + 0x8);
    auStack_80[3] = *(u32 *)(g_00415E30 + 0xC);
    uStack_70 = *(u32 *)(g_00415E30 + 0x10);
    uStack_6c = *(u32 *)(g_00415E30 + 0x14);
    uStack_68 = *(u32 *)(g_00415E30 + 0x18);
    uStack_64 = *(u32 *)(g_00415E30 + 0x1C);
    uStack_60 = *(u32 *)(g_00415E30 + 0x20);
    uVar7 = func_003620E0(1, 0);
    iVar3 = func_002F67B0(uVar7);
    if (uVar10 < uVar1) {
        puVar8 = auStack_50 + uVar10;
        do {
            uVar6 = 10;
            uVar9 = uVar10;
            if (uVar10 < uVar10 + 3) {
                do {
                    uVar6 = func_003648C0((u32 *)(auStack_30), uVar5, auStack_80[iVar3 * 3 + (int)uVar9 % 3], iVar2);
                    if (uVar6 < 10) break;
                    uVar9 = uVar9 + 1;
                } while (uVar9 < uVar10 + 3);
            }
            if (9 < uVar6) break;
            *puVar8 = (int)uVar6;
            uVar10 = uVar10 + 1;
            puVar8 = puVar8 + 1;
            iVar4 = func_003F7110(uVar6);
            iVar2 = iVar2 - iVar4;
        } while (uVar10 < uVar1);
    }
    if (5 < uVar10) {
        uVar10 = 5;
    }
    uVar1 = 0;
    puVar8 = auStack_50;
    auStack_50[uVar10] = 0;
    do {
        func_00362BD0(1, uVar1, *puVar8);
        uVar1 = uVar1 + 1;
        puVar8 = puVar8 + 1;
    } while (uVar1 < 6);
    func_00364020(1);
    func_00364080();
}
/* MISSING ['0x415e30', '0x415e34', '0x415e38', '0x415e3c', '0x415e40', '0x415e44', '0x415e48', '0x415e4c', '0x415e50'] */

/* 0x00374EE0, 0x144 bytes. */
void func_00374EE0(int param_1)
{
    u8 auStack_410[1036];
    int iStack_4;
    int iVar1;
    u32 uVar2;

    if (*(u32 *)g_007B99F0 != 1) {
        *(u32 *)(g_007B99F0) = 1;
        *(u32 *)(g_007B99F0 + 0x4) = 1;
        *(u32 *)(g_007B99F0 + 0x14) = 1;
        *(u32 *)(g_007B99F0 + 0xC) = 5;
        *(u32 *)(g_007B99F0 + 0x10) = 5;
        *(u32 *)(g_007B99F0 + 0x8) = 0;
        *(u16 *)(g_007B99F0 + 0x3E) = 0;
        func_00147160((u8 *)PS2_PTR(param_1), auStack_410, 0x1A0, 0, &iStack_4);
        *(u32 *)(g_007B99F0 + 0x18) = 0x18;
        *(u32 *)(g_007B99F0 + 0x1C) = 0x120;
        *(u32 *)(g_007B99F0 + 0x20) = 0x1D0;
        *(u32 *)(g_007B99F0 + 0x24) = 0x52;
        if (iStack_4 < 0x28) {
            *(u32 *)(g_007B99F0 + 0x24) = 0x3E;
        }
        *(u32 *)(g_007B99F0 + 0x30) = 0;
        *(u32 *)(g_007B99F0 + 0x34) = 0x20;
        *(u32 *)(g_007B99F0 + 0x38) = 0x20;
        *(u32 *)(g_007B99F0 + 0x28) = 0xF0;
        iVar1 = *(u32 *)(g_007B99F0 + 0x24) + -0x20;
        if (iVar1 < 0) {
            iVar1 = *(u32 *)(g_007B99F0 + 0x24) + -0x1F;
        }
        *(u32 *)(g_007B99F0 + 0x2C) = (iVar1 >> 1) + 0x120;
        uVar2 = func_00120A40(PS2_PTR(param_1));
        if (uVar2 < 0x403) {
            func_00120928(g_007B9A30, auStack_410);
        }
    }
}

/* 0x00375030, 0x110 bytes. */
void func_00375030(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    u32 uVar2;

    if (*(u32 *)g_007B99F0 != 1) {
        *(u32 *)(g_007B99F0) = 1;
        *(u32 *)(g_007B99F0 + 0x4) = 1;
        *(u32 *)(g_007B99F0 + 0x8) = 1;
        *(u32 *)(g_007B99F0 + 0xC) = 5;
        *(u32 *)(g_007B99F0 + 0x10) = 5;
        iVar1 = param_3 + -0x20;
        *(u32 *)(g_007B99F0 + 0x14) = (u32)(param_5 != 0);
        *(u16 *)(g_007B99F0 + 0x3E) = 0;
        *(u32 *)(g_007B99F0 + 0x30) = 0;
        *(u32 *)(g_007B99F0 + 0x34) = 0x20;
        *(u32 *)(g_007B99F0 + 0x38) = 0x20;
        if (iVar1 < 0) {
            iVar1 = param_3 + -0x1F;
        }
        *(u32 *)(g_007B99F0 + 0x28) = param_1 + (iVar1 >> 1);
        iVar1 = param_4 + -0x20;
        if (iVar1 < 0) {
            iVar1 = param_4 + -0x1F;
        }
        *(u32 *)(g_007B99F0 + 0x2C) = param_2 + (iVar1 >> 1);
        *(u32 *)(g_007B99F0 + 0x18) = param_1;
        *(u32 *)(g_007B99F0 + 0x1C) = param_2;
        *(u32 *)(g_007B99F0 + 0x20) = param_3;
        *(u32 *)(g_007B99F0 + 0x24) = param_4;
        uVar2 = func_00120A40(PS2_PTR(param_6));
        if (uVar2 < 0x403) {
            func_00147160((u8 *)PS2_PTR(param_6), g_007B9A30, param_3 + -0x30, 0, 0);
        }
    }
}

/* 0x00375140, 0x18C bytes. */
void func_00375140(int param_1, int param_2, int param_3, int param_4)
{
    u8 auStack_410[1032];
    int iStack_4;
    int iStack_8;
    int iVar1;
    int iVar3;
    u32 uVar2;

    if (*(u32 *)g_007B99F0 != 1) {
        *(u32 *)(g_007B99F0) = 1;
        *(u32 *)(g_007B99F0 + 0x4) = 1;
        *(u32 *)(g_007B99F0 + 0x8) = 1;
        *(u32 *)(g_007B99F0 + 0xC) = 5;
        *(u32 *)(g_007B99F0 + 0x10) = 5;
        *(u32 *)(g_007B99F0 + 0x14) = (u32)(param_3 != 0);
        *(u16 *)(g_007B99F0 + 0x3E) = 1;
        func_00147160((u8 *)PS2_PTR(param_4), auStack_410, 0x1A0, &iStack_4, &iStack_8);
        *(u32 *)(g_007B99F0 + 0x20) = iStack_4 + 0x20;
        iVar1 = iStack_8 + 0x20;
        iVar3 = *(u32 *)(g_007B99F0 + 0x20);
        if (*(u32 *)(g_007B99F0 + 0x20) < 0) {
            iVar3 = iStack_4 + 0x21;
        }
        *(u32 *)(g_007B99F0 + 0x18) = param_1 - (iVar3 >> 1);
        iVar3 = iVar1;
        if (iVar1 < 0) {
            iVar3 = iStack_8 + 0x21;
        }
        *(u32 *)(g_007B99F0 + 0x1C) = (param_2 - (iVar3 >> 1)) + -0x24;
        *(u32 *)(g_007B99F0 + 0x24) = iStack_8 + 0x44;
        *(u32 *)(g_007B99F0 + 0x30) = 0;
        *(u32 *)(g_007B99F0 + 0x34) = 0x20;
        *(u32 *)(g_007B99F0 + 0x38) = 0x20;
        if (iStack_4 < 0) {
            iStack_4 = iStack_4 + 1;
        }
        *(u32 *)(g_007B99F0 + 0x28) = *(u32 *)(g_007B99F0 + 0x18) + (iStack_4 >> 1);
        iVar3 = iStack_8 + 0x24;
        if (iVar3 < 0) {
            iVar3 = iStack_8 + 0x25;
        }
        *(u32 *)(g_007B99F0 + 0x2C) = *(u32 *)(g_007B99F0 + 0x1C) + (iVar3 >> 1);
        iStack_8 = iVar1;
        iStack_4 = *(u32 *)(g_007B99F0 + 0x20);
        uVar2 = func_00120A40(PS2_PTR(param_4));
        if (uVar2 < 0x403) {
            func_00120928(g_007B9A30, auStack_410);
        }
    }
}

/* 0x003832B0, 0x28 bytes, matching. */
void func_003832B0(int param_1, int param_2, int param_3)
{
    func_003832E0(param_1, 0x10, 0x10, param_2, param_3);
}

/* 0x00389050, 0x34 bytes. */
int func_00389050(void)
{
    int lVar1;
    int uVar2;

    lVar1 = func_003886D0();
    if (lVar1 == 0) {
        uVar2 = func_00388DA0();
    }
    else {
        uVar2 = 2;
    }
    return uVar2;
}

/* 0x0038F5E0, 0x108 bytes, matching. */
void func_0038F5E0(void)
{
    u8 * iVar1;

    iVar1 = func_00390940();
    *(u16 *)(iVar1 + 0x8E70) = 0x10;
    *(u16 *)(iVar1 + 0x8E72) = 0x10;
    *(u16 *)(iVar1 + 0x8E74) = 200;
    *(u16 *)(iVar1 + 0x8E76) = 0x28;
    *(u16 *)(iVar1 + 0x8E78) = 0x10;
    *(u16 *)(iVar1 + 0x8E7A) = 0x10;
    *(u16 *)(iVar1 + 0x8E7C) = 200;
    *(u16 *)(iVar1 + 0x8E7E) = 0x28;
    *(u8 *)(iVar1 + 0x8E82) = 0;
    *(u8 *)(iVar1 + 0x8E83) = 0;
    *(u8 *)(iVar1 + 0x8E80) = 0x80;
    *(u8 *)(iVar1 + 0x8E81) = 0x80;
    *(u16 *)(iVar1 + 0x8E78) = 0x10;
    *(u16 *)(iVar1 + 0x8E7A) = 0x10;
    *(u16 *)(iVar1 + 0x8E7C) = 200;
    *(u16 *)(iVar1 + 0x8E7E) = 0x28;
    *(u8 *)(iVar1 + 0x8E81) = 0x80;
    *(u8 *)(iVar1 + 0x8E82) = 0x19;
}

/* 0x0039ADA0, 0x188 bytes. */
int func_0039ADA0(void)
{
    int iVar1;
    int iVar2;
    u32 uVar3;

    uVar3 = func_00374250();
    iVar2 = *(u32 *)(g_007BA8B0 + 0x4);
    iVar1 = *(u32 *)g_007BA8B0;
    if (uVar3 == 1) {
        if (*(u32 *)(g_007BA8B0 + 0x8) == 0) {
            iVar1 = func_00374E00();
            if (iVar2 == iVar1) {
                func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
                return 2;
            }
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            *(u32 *)(g_007BA8B0) = func_00374E00();
            func_00373F60();
        }
        else if (*(u32 *)(g_007BA8B0 + 0x8) == 7) {
            iVar2 = func_00374E00();
            if (iVar1 == iVar2) {
                func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
                return 2;
            }
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            *(u32 *)(g_007BA8B0 + 0x4) = func_00374E00();
            func_00373F60();
        }
        func_00397F40();
        func_00397B10(4);
        func_003A9480(1);
    }
    else if (uVar3 == 0) {
        func_00397B10(4);
        func_003A9480(1);
    }
    if ((uVar3 < 2) && (*(u32 *)g_007BAA64 == 1)) {
        func_00376100(4, 9, 0xFFFFFFFFFFFFFFFF);
    }
    return 2;
}

/* 0x0039BDC0, 0x11C bytes. */
int func_0039BDC0(void)
{
    int bVar1;
    int lVar3;
    int lVar5;
    int lVar6;
    int uVar2;
    u32 uVar4;
    u32 uVar7;

    func_002FC2C0();
    uVar2 = func_00327D50();
    lVar3 = func_002FA5A0(uVar2);
    uVar4 = func_002F9260(uVar2);
    lVar5 = func_002FA6B0(uVar2);
    uVar7 = 0;
    bVar1 = false;
    if (-1 < lVar3) {
        lVar6 = func_0030AB90();
        bVar1 = lVar3 < lVar6;
    }
    if (bVar1) {
        uVar7 = 1;
    }
    else if (uVar4 < 0x19F) {
        uVar7 = 1;
    }
    else {
        bVar1 = false;
        if (-1 < lVar5) {
            lVar3 = func_0030AB90();
            bVar1 = lVar5 < lVar3;
        }
        if (bVar1) {
            uVar7 = 1;
        }
        else {
            lVar3 = func_002FA790(uVar2);
            if (lVar3 == 0) {
                lVar3 = func_002FA870(uVar2);
                if (lVar3 != 0) {
                    uVar7 = 1;
                }
            }
            else {
                uVar7 = 1;
            }
        }
    }
    return uVar7;
}

/* 0x003A2D20, 0x1A8 bytes. */
void func_003A2D20(void)
{
    int iVar2;
    int iVar3;
    int iVar7;
    int lVar5;
    int uVar1;
    u32 uVar4;
    int uVar6;

    iVar7 = 0;
    do {
        uVar4 = func_0039FBF0(iVar7);
        lVar5 = func_002F57F0(uVar4);
        if (lVar5 == 0) {
            func_003A0D90(iVar7, uVar4);
        }
        else {
            func_003A0D90(iVar7, 0x7F);
        }
        lVar5 = func_002F57F0(uVar4);
        if (lVar5 == 3) {
            iVar2 = func_002F57A0(uVar4 & 0xFF);
            func_003A0E90(uVar4, g_00428B79[iVar2 * 0x13]);
        }
        else {
            func_003A0E90(uVar4, 0);
        }
        uVar6 = func_002F57F0(uVar4);
        uVar1 = func_002F5840(uVar6);
        func_003A0F30(uVar4, uVar1);
        iVar2 = 0;
        do {
            lVar5 = func_002F57F0(uVar4);
            if (lVar5 == 3) {
                iVar3 = func_002F57A0(uVar4 & 0xFF);
                iVar3 = iVar2 + iVar3 * 0x13;
                func_003A1040(uVar4, iVar2, g_00426620[iVar3 + 0x255B]);
                func_003A1150(uVar4, iVar2, g_00426620[iVar3 + 0x2563]);
            }
            else {
                func_003A1040(uVar4, iVar2, 10);
                func_003A1150(uVar4, iVar2, 0);
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < 8);
        func_003A1230(uVar4, 0);
        iVar7 = iVar7 + 1;
    } while (iVar7 < 0x75);
}

/* MISSING ['0x41c160', '0x41c164', '0x41c168', '0x41c16c', '0x41c170', '0x41c174', '0x41c178', '0x41c17c'] */

/* 0x003CE530, 0xBC bytes. */
int func_003CE530(void)
{
    int lVar2;
    int lVar4;
    u32 uVar1;
    u32 uVar3;
    int uVar5;

    lVar2 = func_00329540(0x15D);
    if (lVar2 == 0) {
        uVar3 = func_00327C70();
        if (uVar3 < 0xB) {
            uVar1 = 0;
        }
        else {
            lVar2 = func_00337A10(0x176);
            lVar4 = func_00327820();
            if (lVar2 == lVar4) {
                uVar5 = func_00327820();
                lVar2 = func_0032EB40(uVar5, 8, 0);
                if ((lVar2 == 0) &&
                      ((lVar2 = func_0032EE10(8), lVar2 == 0 || (lVar2 = func_003C1120(8), lVar2 == 0)))) {
                    uVar1 = 0;
                }
                else {
                    uVar1 = 1;
                }
            }
            else {
                uVar1 = 0;
            }
        }
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x003CEB30, 0xB4 bytes. */
int func_003CEB30(void)
{
    int bVar1;
    int lVar2;
    u32 uVar3;
    int uVar4;

    lVar2 = func_00329540(0x168);
    if (lVar2 == 0) {
        uVar3 = func_00327C70();
        if (uVar3 < 0xB) {
            bVar1 = false;
        }
        else {
            uVar4 = func_00327820();
            lVar2 = func_0032EB40(uVar4, 0x1B, 0);
            if (lVar2 == 0) {
                bVar1 = false;
            }
            else {
                uVar4 = func_00327820();
                lVar2 = func_0032EB40(uVar4, 0x14, 0);
                if (lVar2 == 0) {
                    bVar1 = false;
                }
                else {
                    uVar4 = func_00327820();
                    lVar2 = func_0032EB40(uVar4, 0xB, 0);
                    bVar1 = lVar2 != 0;
                }
            }
        }
    }
    else {
        bVar1 = false;
    }
    return bVar1;
}

/* 0x003CEDD0, 0x154 bytes. */
int func_003CEDD0(void)
{
    int lVar3;
    int lVar5;
    u32 uVar1;
    int uVar2;
    u32 uVar4;

    uVar2 = func_00327820();
    lVar3 = func_00329540(0x16B);
    if (lVar3 == 0) {
        uVar4 = func_00327C70();
        if ((uVar4 < 6) && (lVar3 = func_00329540(0x16A), lVar3 == 0)) {
            uVar1 = 0;
        }
        else {
            lVar3 = func_0032EB40(uVar2, 0x1B, 1);
            if (lVar3 == 0) {
                uVar1 = 0;
            }
            else {
                lVar3 = func_0032EB40(uVar2, 5, 0);
                if (lVar3 == 0) {
                    uVar1 = 0;
                }
                else {
                    lVar3 = func_002F5CC0(0x1B);
                    lVar5 = func_002F5CC0(5);
                    if (lVar3 == lVar5) {
                        lVar3 = func_002F3BB0(0x12);
                        if (lVar3 == 0) {
                            uVar1 = 0;
                        }
                        else {
                            lVar3 = func_0032EB40(uVar2, 0x12, 0);
                            if (lVar3 == 0) {
                                lVar3 = func_003C1120(0x12);
                                if (lVar3 == 0) {
                                    lVar3 = func_00328270();
                                    if ((lVar3 == 0) || (lVar3 = func_00328270(), lVar3 == 2)) {
                                        uVar1 = 1;
                                    }
                                    else {
                                        uVar1 = 0;
                                    }
                                }
                                else {
                                    uVar1 = 0;
                                }
                            }
                            else {
                                uVar1 = 0;
                            }
                        }
                    }
                    else {
                        uVar1 = 0;
                    }
                }
            }
        }
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x003CEF30, 0x100 bytes. */
int func_003CEF30(void)
{
    int bVar1;
    int lVar2;
    int lVar4;
    u32 uVar3;
    int uVar5;
    int uVar6;

    lVar2 = func_00329540(0x16C);
    if (lVar2 == 0) {
        uVar3 = func_00327C70();
        if (uVar3 < 6) {
            bVar1 = false;
        }
        else {
            lVar2 = func_00337A10(0x169);
            lVar4 = func_00327820();
            if (lVar2 == lVar4) {
                uVar5 = func_00327820();
                uVar6 = func_00337A10(0x13B);
                lVar2 = func_0032EB40(uVar5, uVar6, 0);
                if (lVar2 == 0) {
                    bVar1 = false;
                }
                else {
                    uVar5 = func_00327820();
                    uVar6 = func_00337A10(0x56);
                    lVar2 = func_0032EB40(uVar5, uVar6, 0);
                    if (lVar2 == 0) {
                        bVar1 = false;
                    }
                    else {
                        uVar5 = func_00327820();
                        uVar6 = func_00337A10(0x178);
                        lVar2 = func_0032EB40(uVar5, uVar6, 0);
                        bVar1 = lVar2 != 0;
                    }
                }
            }
            else {
                bVar1 = false;
            }
        }
    }
    else {
        bVar1 = false;
    }
    return bVar1;
}

/* 0x003CF500, 0xE0 bytes. */
int func_003CF500(void)
{
    int bVar1;
    int lVar4;
    int uVar2;
    u32 uVar3;

    uVar2 = func_00327820();
    uVar3 = func_003620E0(0, 0);
    if (uVar3 < 0x19F) {
        lVar4 = func_00329540(0x186);
        if (lVar4 == 0) {
            lVar4 = func_003C26C0(uVar2);
            if (lVar4 == 0) {
                bVar1 = false;
            }
            else {
                lVar4 = func_003C27A0(0, 0x12, 5, 0x19F, 0x19F);
                if (lVar4 == 2) {
                    if (uVar3 == 0x12) {
                        lVar4 = func_00328270();
                        bVar1 = lVar4 == 1;
                    }
                    else {
                        bVar1 = false;
                    }
                }
                else {
                    bVar1 = false;
                }
            }
        }
        else {
            bVar1 = false;
        }
    }
    else {
        bVar1 = false;
    }
    return bVar1;
}

/* 0x003D18D0, 0x788 bytes. */
int func_003D18D0(void)
{
    int bVar1;
    int lVar10;
    int lVar11;
    int lVar3;
    int lVar4;
    int lVar5;
    int lVar6;
    int lVar7;
    int lVar8;
    int lVar9;
    u32 uVar12;
    int uVar13;
    int uVar2;

    uVar2 = func_00337A10(0xCE);
    lVar3 = func_00329680(0xB);
    if (lVar3 == 0) {
        lVar3 = func_002F4080(2);
        lVar4 = func_002F4080(3);
        lVar5 = func_002F4080(0xD);
        lVar6 = func_002F4080(0x1B);
        bVar1 = false;
        if (-1 < lVar3) {
            lVar7 = func_0030AB90();
            bVar1 = lVar3 < lVar7;
        }
        if (bVar1) {
            bVar1 = false;
            if (-1 < lVar4) {
                lVar7 = func_0030AB90();
                bVar1 = lVar4 < lVar7;
            }
            if (bVar1) {
                bVar1 = false;
                if (-1 < lVar5) {
                    lVar7 = func_0030AB90();
                    bVar1 = lVar5 < lVar7;
                }
                if (bVar1) {
                    bVar1 = false;
                    if (-1 < lVar6) {
                        lVar7 = func_0030AB90();
                        bVar1 = lVar6 < lVar7;
                    }
                    if (bVar1) {
                        lVar7 = func_002F5CC0(2);
                        lVar8 = func_002F5CC0(3);
                        lVar9 = func_002F5CC0(0xD);
                        lVar10 = func_002F5CC0(0x1B);
                        bVar1 = false;
                        if (-1 < lVar7) {
                            lVar11 = func_0030AB90();
                            bVar1 = lVar7 < lVar11;
                        }
                        if (bVar1) {
                            bVar1 = false;
                            if (-1 < lVar8) {
                                lVar11 = func_0030AB90();
                                bVar1 = lVar8 < lVar11;
                            }
                            if (bVar1) {
                                bVar1 = false;
                                if (-1 < lVar9) {
                                    lVar11 = func_0030AB90();
                                    bVar1 = lVar9 < lVar11;
                                }
                                if (bVar1) {
                                    bVar1 = false;
                                    if (-1 < lVar10) {
                                        lVar11 = func_0030AB90();
                                        bVar1 = lVar10 < lVar11;
                                    }
                                    if (bVar1) {
                                        lVar11 = func_0032EB40(2, 3, 0);
                                        if (lVar11 == 0) {
                                            lVar11 = func_0032EE10(3);
                                            if (lVar11 == 0) {
                                                return false;
                                            }
                                            g_0045D820 = 0;
                                        }
                                        else {
                                            g_0045D820 = 1;
                                        }
                                        lVar11 = func_003C3040();
                                        if (lVar11 == 0) {
                                            bVar1 = false;
                                        }
                                        else {
                                            lVar11 = func_003C1850();
                                            if (lVar11 == 0) {
                                                lVar11 = func_00327C00();
                                                if (lVar11 == 10) {
                                                    bVar1 = false;
                                                }
                                                else {
                                                    uVar12 = func_00327C80();
                                                    if (uVar12 < 0x62E) {
                                                        bVar1 = false;
                                                    }
                                                    else {
                                                        uVar12 = func_00327C80();
                                                        if (uVar12 < 0x633) {
                                                            uVar12 = func_00327C70();
                                                            if (uVar12 < 2) {
                                                                bVar1 = false;
                                                            }
                                                            else {
                                                                lVar11 = func_00327820();
                                                                if (lVar11 == 2) {
                                                                    lVar11 = func_002F3770(2);
                                                                    if (lVar11 < 1000) {
                                                                        bVar1 = false;
                                                                    }
                                                                    else {
                                                                        lVar11 = func_002F3770(10);
                                                                        if (lVar11 < 1000) {
                                                                            bVar1 = false;
                                                                        }
                                                                        else {
                                                                            lVar11 = func_002F3770(0xC);
                                                                            if (lVar11 < 1000) {
                                                                                bVar1 = false;
                                                                            }
                                                                            else {
                                                                                lVar11 = func_003C0720();
                                                                                if (lVar11 == 0) {
                                                                                    lVar7 = func_00327C00();
                                                                                    if (lVar7 == 8) {
                                                                                        lVar7 = func_003C1460(2, lVar3, 1000);
                                                                                        if (lVar7 < 4) {
                                                                                            bVar1 = false;
                                                                                        }
                                                                                        else {
                                                                                            lVar7 = func_002F3770(3);
                                                                                            if (lVar7 < 1000) {
                                                                                                bVar1 = false;
                                                                                            }
                                                                                            else {
                                                                                                lVar7 = func_003C1460(2, lVar4, 1000);
                                                                                                if (lVar7 < 3) {
                                                                                                    bVar1 = false;
                                                                                                }
                                                                                                else {
                                                                                                    lVar7 = func_003C1460(1, lVar4, 500);
                                                                                                    if (lVar7 < 3) {
                                                                                                        bVar1 = false;
                                                                                                    }
                                                                                                    else {
                                                                                                        uVar2 = func_00327D50();
                                                                                                        lVar7 = func_002FB3B0(uVar2);
                                                                                                        if (lVar7 < 2) {
                                                                                                            bVar1 = false;
                                                                                                        }
                                                                                                        else {
                                                                                                            lVar7 = func_0030AFF0(0xE);
                                                                                                            if (lVar4 == lVar7) {
                                                                                                                lVar7 = func_0032EE10(0xD);
                                                                                                                if (lVar7 == 0) {
                                                                                                                    bVar1 = false;
                                                                                                                }
                                                                                                                else {
                                                                                                                    lVar7 = func_0030AFF0(0x11);
                                                                                                                    if (lVar5 == lVar7) {
                                                                                                                        lVar5 = func_0032EE10(0x1B);
                                                                                                                        if (lVar5 == 0) {
                                                                                                                            bVar1 = false;
                                                                                                                        }
                                                                                                                        else {
                                                                                                                            lVar5 = func_0030AFF0(7);
                                                                                                                            if (lVar6 == lVar5) {
                                                                                                                                lVar3 = func_003C0C60(lVar3, lVar4);
                                                                                                                                if (lVar3 == 0) {
                                                                                                                                    bVar1 = false;
                                                                                                                                }
                                                                                                                                else {
                                                                                                                                    lVar3 = func_0032EB40(2, 10, 0);
                                                                                                                                    if (lVar3 == 0) {
                                                                                                                                        bVar1 = false;
                                                                                                                                    }
                                                                                                                                    else {
                                                                                                                                        lVar3 = func_0032EB40(2, 0xC, 0);
                                                                                                                                        bVar1 = lVar3 != 0;
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            }
                                                                                                                            else {
                                                                                                                                bVar1 = false;
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                    else {
                                                                                                                        bVar1 = false;
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                            else {
                                                                                                                bVar1 = false;
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                    else {
                                                                                        bVar1 = false;
                                                                                    }
                                                                                }
                                                                                else {
                                                                                    lVar4 = func_00327C00();
                                                                                    if (lVar4 == 8) {
                                                                                        bVar1 = false;
                                                                                    }
                                                                                    else {
                                                                                        lVar4 = func_003C1580(2, lVar3, 1000, 2, 10, 0xC, 3);
                                                                                        if (lVar4 < 3) {
                                                                                            bVar1 = false;
                                                                                        }
                                                                                        else {
                                                                                            lVar4 = func_002F3770(3);
                                                                                            if (lVar4 < 1000) {
                                                                                                bVar1 = false;
                                                                                            }
                                                                                            else {
                                                                                                lVar4 = func_003C1200(lVar8, 1000);
                                                                                                if (lVar4 < 3) {
                                                                                                    bVar1 = false;
                                                                                                }
                                                                                                else {
                                                                                                    lVar4 = func_003C1330(lVar8, 500);
                                                                                                    if (lVar4 < 3) {
                                                                                                        bVar1 = false;
                                                                                                    }
                                                                                                    else {
                                                                                                        lVar4 = func_0030AFF0(0xE);
                                                                                                        if (lVar3 == lVar4) {
                                                                                                            uVar13 = func_00327D50();
                                                                                                            lVar3 = func_002FB3B0(uVar13);
                                                                                                            if (lVar3 < 5) {
                                                                                                                bVar1 = false;
                                                                                                            }
                                                                                                            else {
                                                                                                                lVar3 = func_0032EB40(2, 3, 0);
                                                                                                                if (lVar3 == 0) {
                                                                                                                    bVar1 = false;
                                                                                                                }
                                                                                                                else if (lVar8 == lVar7) {
                                                                                                                    bVar1 = false;
                                                                                                                }
                                                                                                                else if (lVar8 == lVar9) {
                                                                                                                    bVar1 = false;
                                                                                                                }
                                                                                                                else if (lVar8 == lVar10) {
                                                                                                                    bVar1 = false;
                                                                                                                }
                                                                                                                else {
                                                                                                                    lVar3 = func_0032EB40(2, 0xD, 0);
                                                                                                                    if (lVar3 == 0) {
                                                                                                                        bVar1 = false;
                                                                                                                    }
                                                                                                                    else if (lVar9 == lVar7) {
                                                                                                                        bVar1 = false;
                                                                                                                    }
                                                                                                                    else if (lVar9 == lVar10) {
                                                                                                                        bVar1 = false;
                                                                                                                    }
                                                                                                                    else {
                                                                                                                        lVar3 = func_0032EB40(2, 0x1B, 0);
                                                                                                                        if (lVar3 == 0) {
                                                                                                                            bVar1 = false;
                                                                                                                        }
                                                                                                                        else if (lVar10 == lVar7) {
                                                                                                                            bVar1 = false;
                                                                                                                        }
                                                                                                                        else {
                                                                                                                            lVar3 = func_0032EB40(2, 10, 0);
                                                                                                                            if (lVar3 == 0) {
                                                                                                                                bVar1 = false;
                                                                                                                            }
                                                                                                                            else {
                                                                                                                                lVar3 = func_002F5CC0(10);
                                                                                                                                if (lVar8 == lVar3) {
                                                                                                                                    bVar1 = false;
                                                                                                                                }
                                                                                                                                else {
                                                                                                                                    lVar3 = func_0032EB40(2, 0xC, 0);
                                                                                                                                    if (lVar3 == 0) {
                                                                                                                                        bVar1 = false;
                                                                                                                                    }
                                                                                                                                    else {
                                                                                                                                        lVar3 = func_002F5CC0(0xC);
                                                                                                                                        if (lVar8 == lVar3) {
                                                                                                                                            bVar1 = false;
                                                                                                                                        }
                                                                                                                                        else {
                                                                                                                                            lVar3 = func_0032EB40(2, uVar2, 0
                                                                                                                                                                                    );
                                                                                                                                            if ((lVar3 == 0) ||
                                                                                                                                                  (lVar3 = func_002F5CC0(uVar2
                                                                                                    ), lVar8 != lVar3)) {
                                                                                                        func_003EC130(3);
                                                                                                        bVar1 = true;
                                                                                                    }
                                                                                                    else {
                                                                                                        bVar1 = false;
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    }
                                                                                                    else {
                                                                                                        bVar1 = false;
                                                                                                    }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                else {
                                                                    bVar1 = false;
                                                                }
                                                            }
                                                        }
                                                        else {
                                                            bVar1 = false;
                                                        }
                                                    }
                                                }
                                            }
                                            else {
                                                bVar1 = false;
                                            }
                                        }
                                    }
                                    else {
                                        bVar1 = false;
                                    }
                                }
                                else {
                                    bVar1 = false;
                                }
                            }
                            else {
                                bVar1 = false;
                            }
                        }
                        else {
                            bVar1 = false;
                        }
                    }
                    else {
                        bVar1 = false;
                    }
                }
                else {
                    bVar1 = false;
                }
            }
            else {
                bVar1 = false;
            }
        }
        else {
            bVar1 = false;
        }
    }
    else {
        bVar1 = false;
    }
    return bVar1;
}

/* 0x003E9460, 0x168 bytes. */
void func_003E9460(float param_1)
{
    u8 auStack_10[16];
    u8 * iVar3;
    int lVar5;
    u8 * puVar1;
    u8 * puVar4;
    u8 * puVar6;
    int uVar2;

    iVar3 = func_00391250();
    puVar4 = (u8 *)0x10;
    puVar6 = auStack_10;
    puVar1 = puVar6;
    while (puVar1 != (u8 *)0) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
        puVar4 = puVar4 + -1;
        puVar1 = puVar4;
    }
    lVar5 = func_003E96E0();
    if ((((lVar5 == 0) && (lVar5 = func_003E9730(), lVar5 != 0)) &&
            (lVar5 = func_00102960(0), lVar5 != 0)) && (*(char *)(iVar3 + 0x17C) == 0)) {
        func_003E8560();
        func_003E9700(1);
    }
    lVar5 = func_003E96E0();
    if (lVar5 != 0) {
        if (*(int *)(iVar3 + 4) == 2) {
            if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
                uVar2 = 0;
            }
            else {
                uVar2 = *(u16 *)g_0050074C;
            }
            if ((uVar2 & 0x80) != 0) {
                lVar5 = func_003E9780();
                if (lVar5 == 0) {
                    func_003E97A0(1);
                }
                else {
                    func_003E97A0(0);
                }
            }
        }
        lVar5 = func_003E9780();
        if (lVar5 == 0) {
            func_003E8980();
        }
    }
}

/* 0x003ED990, 0x238 bytes. */
void func_003ED990(void)
{
    u8 auStack_70[112];
    u8 * iVar1;
    int uVar2;
    int uVar3;
    int uVar4;

    iVar1 = (u8 *)(func_003EA000());
    uVar2 = func_003EA160();
    uVar3 = func_003EA0E0();
    uVar4 = func_003EAB60(uVar3, (int *)(auStack_70));
    func_0030CF90(0, 0, *(u32 *)(iVar1 + 8));
    func_003EA880(0, 1, (int *)(auStack_70), uVar4, 1000, 0x41D8C0, 8);
    func_003EA880(0, 2, (int *)(auStack_70), uVar4, 1000, 0x41D8C0, 8);
    func_003EA880(0, 3, (int *)(auStack_70), uVar4, 500, 0x41D8C0, 8);
    func_003EA880(0, 4, (int *)(auStack_70), uVar4, 500, 0x41D8C0, 8);
    func_003EA880(0, 5, (int *)(auStack_70), uVar4, 500, 0x41D8C0, 8);
    func_003EA880(0, 6, (int *)(auStack_70), uVar4, 1000, 0x41D8C0, 8);
    func_003EA880(0, 7, (int *)(auStack_70), uVar4, 500, 0x41D8C0, 8);
    func_0030CF90(1, 0, 0x9F);
    func_0030CF90(1, 1, 0);
    func_003EA850(1, 2, uVar2, 1000, 0x41D8E0, 7);
    func_003EA850(1, 3, uVar2, 500, 0x41D8E0, 7);
    func_003EA850(1, 4, uVar2, 500, 0x41D8E0, 7);
    func_003EA850(1, 5, uVar2, 500, 0x41D8E0, 7);
    uVar3 = func_002F8E50(uVar3);
    func_00362990(0, uVar3);
    uVar2 = func_002F8E50(uVar2);
    func_00362990(1, uVar2);
    func_003EAA50(0xE);
}

/* 0x003F1D40, 0x1CC bytes. */
int func_003F1D40(u8 *param_1)
{
    int aiStack_70[28];
    int bVar1;
    int iVar2;
    int iVar5;
    int iVar6;
    int lVar4;
    int * piVar7;
    u32 uVar3;

    func_00320F00();
    *(int *)param_1 = 0;
    iVar5 = 0;
    lVar4 = func_0030AB90();
    bVar1 = false;
    if (0 < lVar4) {
        do {
            lVar4 = func_0030B240(iVar5, 1);
            bVar1 = true;
            if (lVar4 == 1) break;
            iVar5 = iVar5 + 1;
            iVar6 = func_0030AB90();
            bVar1 = false;
        } while (iVar5 < iVar6);
    }
    if (bVar1) {
        bVar1 = false;
        iVar5 = 0;
        lVar4 = func_0030AB90();
        if (0 < lVar4) {
            do {
                lVar4 = func_0030B240(iVar5, 1);
                if (lVar4 == 2) {
                    bVar1 = true;
                    break;
                }
                iVar5 = iVar5 + 1;
                iVar6 = func_0030AB90();
            } while (iVar5 < iVar6);
        }
        if (bVar1) {
            uVar3 = 0;
        }
        else {
            iVar5 = 0;
            iVar6 = 0;
            lVar4 = func_0030AB90();
            if (0 < lVar4) {
                piVar7 = aiStack_70;
                do {
                    iVar6 = iVar6 + 1;
                    *piVar7 = 0x19;
                    piVar7 = piVar7 + 1;
                    iVar2 = func_0030AB90();
                } while (iVar6 < iVar2);
            }
            iVar6 = 0;
            lVar4 = func_0030AB90();
            if (0 < lVar4) {
                piVar7 = aiStack_70;
                do {
                    lVar4 = func_0030B240(iVar6, 1);
                    if (lVar4 == 1) {
                        func_0030B1B0(iVar6, 1, 2);
                        *piVar7 = iVar6;
                        iVar5 = iVar5 + 1;
                        piVar7 = piVar7 + 1;
                    }
                    iVar6 = iVar6 + 1;
                    iVar2 = func_0030AB90();
                } while (iVar6 < iVar2);
            }
            func_003F1810();
            func_0030E390(0xC, 1, 0, 0xFFFFFFFFFFFFFFFF, aiStack_70, iVar5);
            if (*(int *)param_1 != 1) {
                func_003F1900((u32 *)(param_1));
            }
            uVar3 = 1;
        }
    }
    else {
        uVar3 = 0;
    }
    return uVar3;
}
