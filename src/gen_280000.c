/*
 * gen_280000.c - small functions between 0x00280000 and 0x00300000, generated from Ghidra
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

#include "sw2e_draw.h"

extern u8 g_00772688[0x18];
extern u8 g_00772940[0x18];
extern u8 g_007A05A0[0x18];
#define true 1
#define false 0

extern u8 g_00411950[0x4];
extern u8 g_00411E20[0x6];
extern u8 g_00412470[0x4];
extern u8 g_00413960[0x6];
extern u8 g_00413961[0x5];
extern u8 g_005BA7C8[0x4];
extern u8 g_005BD6A8[0x8];
extern u8 g_005BD6B0[0x8];
extern u8 g_00669D60[0x10];
extern u8 g_00669DB8[0x20];
extern u8 g_00669E28[0x13C];
extern u8 g_00669E48[0x4];
extern u8 g_00669F60[0x40];
extern u8 g_00669F98[0x4];
extern u8 g_00669F9C[0x4];
extern u8 g_00669FA4[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_006934B9[0x1];
extern u8 g_006A3A30[0x10];
extern u8 g_006A3A44[0x118];
extern u8 g_0073C460[0x20];
extern u8 g_0073C79B[0x5];
extern u8 g_0074B824[0x10];
extern u8 g_0076F615[0x1];
extern u8 g_0077268C[0xC];
extern u8 g_007729B0[0x50];
extern u8 g_007729BC[0x44];
extern u8 g_007729EC[0x14];
extern u8 g_00773340[0x4];
extern u8 g_00779D00[0x10];
extern u8 g_0077BE70[0x10];
extern u8 g_0077BEF0[0x8];
extern u8 g_0077C040[0x10];
extern u8 g_0077CEA0[0x10];
extern u8 g_00799A6C[0x4];
extern u8 g_00799A70[0x4];
extern u8 g_00799A74[0x4];
extern u8 g_00799A78[0x28];
extern u8 g_00799A7C[0x4C];
extern u8 g_00799D90[0x10];
extern u8 g_0079A090[0x10];
extern u8 g_007A05B8[0x4];
extern u8 g_007A22C0[0x10];
extern int g_0045CFB4;   /* (small data) */
extern int g_0045CFD8;   /* (small data) */
extern int g_0045D2F0;   /* (small data) */
extern int g_0045D570;   /* (small data) */
extern int g_0045D574;   /* (small data) */
extern int g_0045D578;   /* (small data) */
extern int g_0045D5F4;   /* (small data) */
extern int g_0045D5F8;   /* (small data) */
extern int g_0045D5FC;   /* (small data) */
extern int g_0045D604;   /* (small data) */
extern int g_0045D608;   /* (small data) */
extern int g_0045D674;   /* (small data) */
extern u32 g_700000C0;   /* (scratchpad) */
extern u32 g_700000C4;   /* (scratchpad) */
extern u32 g_700000C8;   /* (scratchpad) */
extern u32 g_700000CC;   /* (scratchpad) */
extern u32 g_7000015C;   /* (scratchpad) */
extern u32 g_70000D60;   /* (scratchpad) */

int func_001026D0();
int func_00102DB0();
int func_00102EC0();
int func_00103000();
int func_001037F0();
int func_001050F0();
int func_00105230();
int func_001055E0();
int func_00105620();
int func_001056C0();
int func_00105770();
int func_00105860();
int func_00105900();
int func_00106C90();
int func_00107440();
int func_00118850();
int func_00118AC0();
int func_0011EB80();
int func_0011ED38();
int func_00120928();
int func_001251A0();
int func_00125450();
int func_00125508();
int func_001265F0();
int func_00136DE8();
int func_00148130();
int func_001482F0();
int func_00148370();
int func_0014F850();
int func_0014F8B0();
int func_0018EA60();
int func_00190610();
int func_00194480();
int func_00194560();
int func_0019EBA0();
int func_0019FBC0();
int func_0019FC20();
int func_001A1840();
int func_001A1BE0();
int func_001A2970();
int func_001AE9F0();
int func_001AEDB0();
int func_001AEE10();
int func_001AFC50();
int func_001AFE20();
int func_001B8BF0();
int func_001F14E0();
int func_001F2B70();
int func_001F2BB0();
int func_001F4870();
int func_001FBFB0();
int func_001FF100();
int func_001FF450();
int func_00204B60();
int func_00204BB0();
int func_00206080();
int func_0020E440();
int func_0020E5A0();
int func_0020E5C0();
int func_0020E740();
int func_0020E960();
int func_0020EB60();
int func_0020ECE0();
int func_00217F40();
int func_00218070();
int func_002180F0();
int func_0021A630();
int func_0022DC70();
int func_0022DCD0();
int func_0022DD60();
int func_00238AE0();
int func_002396B0();
int func_0023ACC0();
int func_0023AD10();
int func_0023B5C0();
int func_00240E20();
int func_002456C0();
int func_0027E660();
int func_0027E730();
int func_00286AC0();
int func_00287280();
int func_002872B0();
int func_00289640();
int func_0028C310();
int func_0028C330();
int func_002974A0();
int func_00297530();
int func_00297890();
int func_00297C00();
int func_00298670();
int func_00299F60();
int func_0029C930();
int func_0029CFB0();
int func_002A5080();
int func_002A5130();
int func_002A5790();
int func_002A5880();
int func_002A5B10();
int func_002A5D00();
int func_002A5ED0();
int func_002A5FD0();
int func_002A6040();
int func_002A60C0();
int func_002A6290();
int func_002A62B0();
int func_002A62D0();
int func_002A6470();
int func_002A6D20();
int func_002A6FF0();
int func_002AFA20();
int func_002B08F0();
int func_002B0910();
int func_002B7320();
int func_002BC110();
int func_002BFAB0();
int func_002C1450();
int func_002C33C0();
int func_002C3DC0();
void func_002C5A90(u8 *g);
void func_002C5AC0(float f, u8 *g, int a, int b, int c, int d);
int func_002C63A0();
int func_002C7310();
int func_002C99F0();
int func_002CAE90();
int func_002CC190();
int func_002CCE60();
int func_002CD920();
int func_002D6560();
int func_002D6930();
int func_002D6FE0();
int func_002D8CA0();
int func_002D8DA0();
int func_002DB4F0();
int func_002DB550();
int func_002DB680();
int func_002DB800();
int func_002DB880();
int func_002DB8A0();
int func_002DB900();
int func_002DBAA0();
int func_002DF7C0();
int func_002E52E0();
int func_002E52F0();
int func_002E5300();
int func_002E5810();
int func_002E6370();
int func_002E6E40();
int func_002E74E0();
int func_002E7570();
int func_002E7FC0();
int func_002E8830();
int func_002E88F0();
int func_002E8980();
int func_002E94F0();
int func_002EFA70();
int func_002EFC80();
int func_002F2890();
int func_002F34E0();
int func_002F39F0();
int func_002F41E0();
int func_002F4C40();
int func_002F4DD0();
int func_002F4F60();
int func_002F50F0();
int func_002F5280();
int func_002F5410();
int func_002F55A0();
int func_002F5730();
int func_002F8F20();
int func_002F9260();
int func_002FA5A0();
int func_002FA870();
int func_0030CE90();
int func_003270F0();
int func_00327140();
int func_00327170();
int func_00327C00();
int func_00327D50();
int func_00338410();
int func_0033C160();
int func_0033C320();
int func_0033C3A0();
int func_0033C4E0();
int func_0033C560();
int func_0035DEC0();
int func_0035F0C0();
int func_00362570();
int func_00363B90();
int func_0036D2E0();
int func_0036D310();
int func_0036EFC0();
int func_00372250();
int func_00383240();
int func_003832B0();
int func_00383330();
int func_0039FF60();
int func_003A0040();
int func_003A1290();
int func_003A16A0();
int func_003A1830();
int func_003A2810();
int func_003B5930();
int func_003BFDF0();
int func_003C0060();
int func_003C0070();
int func_003DD680();
int func_003EF0D0();
int func_00285CD0(int param_1, int param_2);
void func_00285D50(int param_1, int param_2, int param_3, int param_4);
int func_002863E0();
void func_002868B0(int param_1, int param_2, u16 *param_3, int param_4, int param_5, int param_6);
void func_002872E0(int param_1, int param_2);
void func_002885A0(void);
void func_002885E0(int param_1);
void func_0028A3D0(void);
void func_0028A420(int param_1, int param_2, u32 *param_3, int param_4);
void func_0028A510(void);
void func_0028EFC0(int *param_1);
void func_0028F960(u32 *param_1);
void func_0028FB40(int param_1);
void func_00290560(int param_1);
void func_002905A0(int param_1);
int func_002905F0(void);
void func_00290630(int param_1);
void func_00290670(int param_1);
int func_002906B0(void);
void func_00290710(int param_1);
void func_00297620(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00298950(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
int func_0029A5C0(int param_1);
int func_0029AB60(int param_1);
void func_0029BDC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
void func_0029C9B0(int param_1, int param_2, int param_3);
void func_0029C9E0(int param_1, int param_2, int param_3, int param_4);
void func_0029CB90(int param_1, int param_2, int param_3);
int func_0029D000(int param_1, int param_2, int param_3);
void func_0029DEF0(int param_1, int param_2);
int func_0029E370(int param_1);
void func_002A5BE0(void);
void func_002A6340(void);
int func_002A6430();
int func_002A64C0(int param_1);
void func_002A6770(int param_1, int param_2);
int func_002A72B0(int param_1, int param_2, int param_3);
void func_002A77F0(void);
void func_002A7870(void);
void func_002A78B0(void);
void func_002A7970(void);
void func_002A79C0(void);
int func_002A7AF0(int param_1, int param_2);
int func_002A7BF0(void);
void func_002A7CE0(void);
void func_002A7D90(void);
int func_002A7E30(int param_1);
void func_002A7EC0(void);
int func_002A9610();
void func_002AB450(int param_1, int param_2, int param_3, int param_4);
void func_002AFB80(int param_1);
void func_002B5990(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002B7BA0(int param_1);
int func_002BC880(int param_1, int param_2, int param_3);
void func_002BF9E0(int param_1, int param_2);
void func_002C1690(int param_1, u8 *param_2, int param_3);
int func_002C3260(int param_1, int param_2);
int func_002C3980(int param_1, u8 *param_2, int param_3);
int func_002C4030(int param_1, int param_2);
void func_002C4AE0(u32 *param_1);
int func_002C5220(int param_1, u8 *param_2, u8 *param_3, int param_4, int param_5);
int func_002C54F0(int param_1, u8 *param_2, u8 *param_3, int param_4, int param_5);
void func_002C65C0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002CA590(int param_1, int *param_2);
int func_002CA640(int param_1, int param_2);
void func_002CAC30(u8 *param_1, int param_2);
void func_002CAD60(u8 *param_1);
void func_002CAD90(u8 *param_1);
void func_002CB4B0(int param_1);
void func_002CB500(int param_1);
int func_002CD5E0();
int func_002CD780();
int func_002CE160();
int func_002D07A0(int param_1);
void func_002D0DC0(int param_1);
void func_002D67E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_002D6890(void);
void func_002D68F0(void);
void func_002D6C30(int param_1);
void func_002D7080(int param_1, int param_2);
int func_002D78E0(int param_1);
void func_002D7EE0(int param_1);
void func_002D7F90(void);
void func_002D8160(void);
void func_002D8280(int param_1);
void func_002D82C0(int param_1, int param_2);
void func_002D8910(int param_1);
int func_002D8C30(int param_1, int param_2);
void func_002D8EE0(int param_1);
int func_002DAE60(u8 *param_1, int param_2);
void func_002DB3C0(u32 *param_1);
void func_002DB580(void);
void func_002DB600(void);
void func_002DB640(void);
int func_002DB750(void);
int func_002DB9F0(void);
void func_002DBAC0(int param_1);
void func_002DD0F0(void);
void func_002DDCF0(void);
void func_002DFEE0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002DFF10(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002DFF40(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002DFF70(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002DFFA0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002DFFD0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002E0540(int param_1);
void func_002E1510(int param_1, int param_2);
void func_002E15A0(int param_1);
void func_002E16A0(int param_1);
void func_002E3CD0(int param_1, int param_2);
void func_002E5C80(int param_1);
void func_002E5D20(void);
void func_002E5DA0(int param_1);
void func_002E5E10(int param_1, int param_2);
void func_002E5ED0(void);
void func_002E6210(void);
void func_002E67B0(void);
void func_002EA950(u32 *param_1);
int func_002EF080();
int func_002EFB00(int param_1);
void func_002EFB70(int param_1);
void func_002EFC40(int param_1);
void func_002F0090(void);
void func_002F03B0(void);

/* 0x00285CD0, 0x74 bytes, matching. */
int func_00285CD0(int param_1, int param_2)
{
    int iVar1;

    iVar1 = 0;
    switch(param_2) {
    case 0:
        iVar1 = 0x18;
        break;
    case 1:
        iVar1 = param_1 + 0x19;
        break;
    case 2:
        iVar1 = param_1 + 0x1B;
        break;
    case 3:
        iVar1 = param_1 + 0x1D;
        break;
    case 4:
        iVar1 = param_1 + 0x1F;
        break;
    case 5:
        iVar1 = param_1 + 0x21;
        break;
    case 6:
        iVar1 = param_1 + 0x23;
        break;
    case 7:
        iVar1 = param_1 + 0x25;
        break;
    case 8:
        iVar1 = 0x27;
    }
    return iVar1;
}

/* 0x00285D50, 0x100 bytes. */
void func_00285D50(int param_1, int param_2, int param_3, int param_4)
{
    int iVar4;
    int iVar5;
    int lVar1;
    int uVar2;
    int uVar3;

    iVar4 = func_0021A630();
    func_00383240(*(u32 *)(iVar4 + 0x38), param_4);
    lVar1 = func_0036D310();
    if (lVar1 == 0) {
        iVar5 = func_00363B90();
        func_003832B0(*(u32 *)(iVar4 + 0x38), iVar5 + 0xB, param_4);
    }
    else {
        func_003832B0(*(u32 *)(iVar4 + 0x38), 0x44, param_4);
    }
    lVar1 = func_0036D310();
    if (lVar1 == 0) {
        uVar2 = func_00285CD0(*(u32 *)(iVar4 + 0x1C), param_2);
        uVar3 = func_00363B90();
        uVar3 = func_003EF0D0(uVar3);
        func_00383330(*(u32 *)(iVar4 + 0x38), uVar2, uVar3, 0x12, 0, param_4);
    }
    else {
        uVar2 = func_00285CD0(*(u32 *)(iVar4 + 0x1C), param_2);
        func_00383330(*(u32 *)(iVar4 + 0x38), uVar2, 0xC0, 0x12, 0, param_4);
    }
}

/* 0x002868B0, 0x3C bytes. */
void func_002868B0(int param_1, int param_2, u16 *param_3, int param_4, int param_5, int param_6)
{
    func_001ABE40((u8 *)param_1, param_2, *param_3, param_3[1], param_6, param_3[2], param_3[3], param_4, param_6, param_5);
}

/* 0x002872E0, 0x7C bytes. */
void func_002872E0(int param_1, int param_2)
{
    u32 uVar1;

    if (*(int *)(param_1 + 0x9C) != 0) {
        func_0028C310();
        func_00287280();
    }
    uVar1 = func_002CA640(*(u8 *)(param_2 * 0x48 + 0x669DE8), 8);
    *(u32 *)(param_1 + 0x50) = uVar1;
    func_00286AC0();
    *(u32 *)(g_007729B0) = 8;
}

/* 0x002885A0, 0x38 bytes, matching. */
void func_002885A0(void)
{
    *(u32 *)(g_007729B0) = 0;
    *(u8 *)(g_007729B0 + 0x3F) = 5;
    func_002872B0();
    func_0028C330(0x12E, 0x44);
}

/* 0x002885E0, 0x7C bytes. */
void func_002885E0(int param_1)
{
    int iVar1;

    *(u32 *)(g_007729B0) = 1;
    iVar1 = *(int *)(param_1 + 0x80) / 0x1E + 1;
    if (iVar1 < 1) {
        iVar1 = 1;
    }
    func_002CD920(g_00772940, 0, *(int *)(param_1 + 0x80), iVar1);
    *(u32 *)(g_007729B0 + 0x4C) = 1;
}

/* 0x0028A3D0, 0x44 bytes, matching. */
void func_0028A3D0(void)
{
    *(u32 *)(g_007729BC + 0x8) = 2;
    *(u32 *)(g_007729BC) = 2;
    *(u32 *)(g_007729BC + 0x4) = 2;
    *(u8 *)(g_007729BC + 0x32) = 0x19;
    *(u8 *)(g_007729BC + 0x30) = 0x19;
    *(u8 *)(g_007729BC + 0x31) = 0x19;
    *(u32 *)(g_007729BC + 0x40) = 0;
}

/* 0x0028A420, 0xF0 bytes. */
void func_0028A420(int param_1, int param_2, u32 *param_3, int param_4)
{
    if (param_4 == 1) {
        func_00289640(param_1, param_2, 0, *param_3, *(u8 *)((int)param_3 + 5), 2,
                                  *(u8 *)(param_3 + 1));
        if (0x17 < *(u8 *)(g_007729EC + 0x2)) {
            *(u32 *)(g_007729EC + 0x10) = 0;
        }
    }
    else if (((param_4 == 2) &&
                      (func_00289640(param_1, param_2, 0, *param_3, *(u8 *)((int)param_3 + 5), 0,
                                                  *(u8 *)(param_3 + 1)), 0x17 < (*(u8 *)(g_007729EC)))) &&
                    (func_00289640(param_1, param_2, 0, param_3[2], *(u8 *)((int)param_3 + 0xD), 1,
                                                *(u8 *)(param_3 + 3)), 0x17 < (*(u8 *)(g_007729EC + 0x1)))) {
        *(u32 *)(g_007729EC + 0x10) = 0;
    }
}

/* 0x0028A510, 0x68 bytes. */
void func_0028A510(void)
{
    func_002C5A90(g_00772688);
    func_002C5AC0(1.0f, g_00772688, 0x40, 0x40, 0, 0);
    *(u32 *)(g_0077268C + 0x4) = 1;
    *(u8 *)(g_0077268C) = *(u8 *)(g_0077268C + 0x2);
    *(u32 *)(g_0077268C + 0x8) = 0;
}

/* 0x0028EFC0, 0x4F4 bytes. */
void func_0028EFC0(int *param_1)
{
    int bVar1;
    int bVar3;
    int bVar4;
    int bVar5;
    int bVar6;
    int iVar12;
    int iVar16;
    int iVar2;
    int iVar20;
    int iVar21;
    int * piVar11;
    int * piVar13;
    int * piVar14;
    int * piVar15;
    int * piVar17;
    int * piVar18;
    int * piVar22;
    int * piVar23;
    int * piVar9;
    u32 * puVar10;
    u32 uVar19;
    u32 uVar7;
    u32 uVar8;

    iVar21 = 0;
    *param_1 = 0;
    param_1[3] = 0;
    param_1[1] = 0;
    param_1[4] = 0;
    param_1[2] = 0;
    param_1[5] = 0;
    do {
        piVar9 = (int *)(iVar21 * 0x68 + 0x6A1D58);
        iVar2 = *piVar9;
        if (iVar2 != 0) {
            bVar1 = *(u8 *)(iVar2 + 0x79);
            uVar7 = (u32)bVar1;
            if ((((((*(char *)(uVar7 + 0x669FA8) == 0) &&
                          (uVar19 = *(u32 *)(iVar2 + 0x80), (uVar19 & 1) != 0)) && ((uVar19 & 2) == 0)) &&
                      (((uVar19 & 4) == 0 && ((uVar19 & 0x40000) == 0)))) &&
                    (((uVar19 & 0x100000) == 0 && (((uVar19 & 0x800000) == 0 && ((uVar19 & 0x80) == 0)))))) &&
                  ((uVar19 & 0x100) == 0)) {
                if ((uVar19 & 0x10) != 0) {
                    param_1[0xBA] = iVar2;
                }
                if ((*(u32 *)(iVar2 + 0x80) & 0x20) != 0) {
                    param_1[0xBB] = iVar2;
                }
                if ((*(u32 *)(iVar2 + 0x80) & 0x800) != 0) {
                    puVar10 = (u32 *)(param_1 + uVar7);
                    uVar19 = *puVar10;
                    if (0x1D < (int)uVar19) break;
                    iVar12 = *(int *)(iVar2 + 4) - *(u32 *)g_005BA7C8;
                    if (iVar12 < 0) {
                        iVar12 = iVar12 + 0x1F;
                    }
                    iVar20 = 0;
                    uVar8 = (u32)bVar1;
                    if (0 < (int)uVar19) {
                        piVar13 = param_1 + uVar8 * 0x1E;
                        do {
                            iVar16 = *(int *)(piVar13[0x60] + 4) - *(u32 *)g_005BA7C8;
                            if (iVar16 < 0) {
                                iVar16 = iVar16 + 0x1F;
                            }
                            if ((iVar16 >> 5 != iVar12 >> 5) && ((u32)(iVar12 >> 5) < (u32)(iVar16 >> 5)))
                            break;
                            iVar20 = iVar20 + 1;
                            piVar13 = piVar13 + 1;
                        } while (iVar20 < (int)*puVar10);
                    }
                    if (iVar20 < (int)uVar19) {
                        if (8 < (int)(uVar19 - iVar20)) {
                            bVar6 = false;
                            bVar5 = false;
                            bVar4 = false;
                            bVar3 = false;
                            if ((iVar20 <= (int)*puVar10) && (-0x80000000 < iVar20)) {
                                bVar3 = true;
                            }
                            if ((bVar3) && (-0x80000000 < (int)*puVar10)) {
                                bVar4 = true;
                            }
                            if ((bVar4) && (iVar20 != -0x80000000)) {
                                bVar5 = true;
                            }
                            if (bVar5) {
                                bVar3 = true;
                                if (((*puVar10 & 0x80000000) == (-iVar20 & 0x80000000U)) &&
                                      ((*puVar10 & 0x80000000) != (param_1[uVar7] - iVar20 & 0x80000000U))) {
                                    bVar3 = false;
                                }
                                if (bVar3) {
                                    bVar6 = true;
                                }
                            }
                            if (bVar6) {
                                piVar18 = param_1 + uVar8 * 0x1E + uVar19;
                                piVar17 = piVar18 + -1;
                                piVar23 = piVar18 + -2;
                                piVar22 = piVar18 + -3;
                                piVar15 = piVar18 + -4;
                                piVar14 = piVar18 + -5;
                                piVar11 = piVar18 + -6;
                                piVar13 = piVar18 + -7;
                                do {
                                    uVar19 = uVar19 - 8;
                                    piVar18[0x60] = piVar18[0x5F];
                                    piVar18[6] = piVar18[5];
                                    piVar18 = piVar18 + -8;
                                    piVar17[0x60] = piVar17[0x5F];
                                    piVar17[6] = piVar17[5];
                                    piVar17 = piVar17 + -8;
                                    piVar23[0x60] = piVar23[0x5F];
                                    piVar23[6] = piVar23[5];
                                    piVar23 = piVar23 + -8;
                                    piVar22[0x60] = piVar22[0x5F];
                                    piVar22[6] = piVar22[5];
                                    piVar22 = piVar22 + -8;
                                    piVar15[0x60] = piVar15[0x5F];
                                    piVar15[6] = piVar15[5];
                                    piVar15 = piVar15 + -8;
                                    piVar14[0x60] = piVar14[0x5F];
                                    piVar14[6] = piVar14[5];
                                    piVar14 = piVar14 + -8;
                                    piVar11[0x60] = piVar11[0x5F];
                                    piVar11[6] = piVar11[5];
                                    piVar11 = piVar11 + -8;
                                    piVar13[0x60] = piVar13[0x5F];
                                    piVar13[6] = piVar13[5];
                                    piVar13 = piVar13 + -8;
                                } while (iVar20 + 8 < (int)uVar19);
                            }
                        }
                        if (iVar20 < (int)uVar19) {
                            piVar13 = param_1 + uVar8 * 0x1E + uVar19;
                            do {
                                uVar19 = uVar19 - 1;
                                piVar13[0x60] = piVar13[0x5F];
                                piVar13[6] = piVar13[5];
                                piVar13 = piVar13 + -1;
                            } while (iVar20 < (int)uVar19);
                        }
                    }
                    if ((*(u32 *)g_00669F60 & 0xC) == 0) {
                        iVar12 = *(int *)(iVar21 * 0x68 + 0x6A1DA4);
                    }
                    else if (*(char *)(*piVar9 + 0x79) == 0) {
                        iVar12 = 0x15E;
                    }
                    else {
                        iVar12 = 0x28A;
                    }
                    param_1[uVar8 * 0x1E + iVar20 + 6] = iVar12;
                    param_1[uVar8 * 0x1E + iVar20 + 0x60] = iVar2;
                    *puVar10 = *puVar10 + 1;
                }
            }
        }
        iVar21 = iVar21 + 1;
    } while (iVar21 < 0x47);
    *(u8 *)(param_1 + 0xBE) = 0;
    iVar21 = 0;
    piVar9 = param_1;
    do {
        if ((*(char *)(iVar21 + 0x669FA8) == 0) && (0 < *piVar9)) {
            *(char *)((int)param_1 + *(u8 *)(param_1 + 0xBE) + 0x2F9) = (char)iVar21;
            *(char *)(param_1 + 0xBE) = (char)param_1[0xBE] + 1;
        }
        iVar21 = iVar21 + 1;
        piVar9 = piVar9 + 1;
    } while (iVar21 < 3);
}
/* MISSING ['0x5ba7c8'] */

/* 0x0028F960, 0x1E0 bytes. */
void func_0028F960(u32 *param_1)
{
    int iVar10;
    int iVar11;
    int iVar3;
    int iVar6;
    int iVar7;
    int lVar5;
    u8 * pbVar2;
    u32 * puVar8;
    u32 * puVar9;
    u32 uVar1;
    int uVar4;

    if ((*(u32 *)g_00669F60 & 2) == 0) {
        iVar3 = 1;
    }
    else {
        iVar3 = 2;
    }
    iVar6 = 0;
    puVar9 = param_1;
    do {
        iVar10 = 0;
        puVar8 = puVar9;
        do {
            uVar1 = func_00102DB0(0x10, 0x24C0);
            *puVar8 = uVar1;
            iVar10 = iVar10 + 1;
            puVar8 = puVar8 + 1;
        } while (iVar10 < 4);
        iVar6 = iVar6 + 1;
        puVar9 = puVar9 + 4;
    } while (iVar6 < 2);
    uVar4 = func_001026D0(1, 0x39, 0, 1, 0, 0, 0x440930, 0x3CC);
    iVar6 = (int)uVar4;
    iVar10 = 0;
    if (iVar3 != 0) {
        iVar11 = (int)g_00669D60;
        puVar9 = param_1;
        do {
            uVar1 = *(u32 *)(iVar11 + 0x88);
            iVar7 = 0;
            puVar8 = puVar9;
            do {
                pbVar2 = (u8 *)func_0035DEC0(uVar1, iVar7);
                if (*pbVar2 < 0x7F) {
                    func_00118AC0(*puVar8, iVar6 + *(int *)(iVar6 + 8) *
                                                                              *(int *)(iVar6 + 0x10 + (u32)*pbVar2 * 8),0x24C0);
                }
                iVar7 = iVar7 + 1;
                puVar8 = puVar8 + 1;
            } while (iVar7 < 4);
            iVar10 = iVar10 + 1;
            iVar11 = iVar11 + 0x48;
            puVar9 = puVar9 + 4;
        } while (iVar10 < iVar3);
    }
    func_00102EC0(uVar4);
    lVar5 = func_0036D310();
    if (lVar5 == 0) {
        iVar3 = func_00363B90();
        iVar3 = iVar3 + 0x525;
    }
    else {
        iVar3 = 0x55E;
    }
    uVar1 = func_001026D0(1, iVar3, 0, 1, 0, 0, 0x440930, 0x3EA);
    param_1[8] = uVar1;
}

/* 0x0028FB40, 0x84 bytes. */
void func_0028FB40(int param_1)
{
    int iVar2;
    int iVar3;
    int * piVar1;

    func_00102EC0(*(u32 *)(param_1 + 0x20));
    param_1 = param_1 + 0x10;
    iVar3 = 1;
    do {
        iVar2 = 3;
        piVar1 = (int *)(param_1 + 0xC);
        do {
            if (*piVar1 != 0) {
                func_00102EC0();
            }
            iVar2 = iVar2 + -1;
            piVar1 = piVar1 + -1;
        } while (-1 < iVar2);
        iVar3 = iVar3 + -1;
        param_1 = param_1 + -0x10;
    } while (-1 < iVar3);
}

/* 0x00290560, 0x34 bytes, matching. */
void func_00290560(int param_1)
{
    int uVar1;

    uVar1 = func_00372250(0x2D);
    func_00120928(param_1, uVar1);
}

/* 0x002905A0, 0x48 bytes, matching. */
void func_002905A0(int param_1)
{
    int uVar1;

    uVar1 = func_00327D50();
    uVar1 = func_002FA5A0(uVar1);
    uVar1 = func_002F8F20(uVar1);
    uVar1 = func_002F2890(uVar1);
    func_00120928(param_1, uVar1);
}

/* 0x002905F0, 0x40 bytes, matching. */
int func_002905F0(void)
{
    int bVar1;
    int lVar2;
    int uVar3;

    lVar2 = func_0036D2E0();
    if (lVar2 == 0) {
        bVar1 = false;
    }
    else {
        uVar3 = func_00327D50();
        lVar2 = func_002F9260(uVar3);
        bVar1 = lVar2 < 0x19F;
    }
    return bVar1;
}

/* 0x00290630, 0x34 bytes, matching. */
void func_00290630(int param_1)
{
    int uVar1;

    uVar1 = func_00372250(0x34);
    func_00120928(param_1, uVar1);
}

/* 0x00290670, 0x40 bytes, matching. */
void func_00290670(int param_1)
{
    int uVar1;

    uVar1 = func_00327D50();
    uVar1 = func_002F9260(uVar1);
    uVar1 = func_002F2890(uVar1);
    func_00120928(param_1, uVar1);
}

/* 0x002906B0, 0x54 bytes, matching. */
int func_002906B0(void)
{
    int lVar1;
    int uVar2;

    lVar1 = func_0036D2E0();
    if (lVar1 == 0) {
        uVar2 = 0;
    }
    else {
        lVar1 = func_0035F0C0();
        if (lVar1 == 0) {
            uVar2 = 0;
        }
        else {
            uVar2 = func_00327D50();
            uVar2 = func_002FA870(uVar2);
        }
    }
    return uVar2;
}

/* 0x00290710, 0x34 bytes, matching. */
void func_00290710(int param_1)
{
    int uVar1;

    uVar1 = func_00372250(100);
    func_00120928(param_1, uVar1);
}

/* 0x00297620, 0x260 bytes. */
void func_00297620(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int bVar1;
    int cVar2;
    int iVar3;
    int iVar4;
    int uVar5;

    bVar1 = *(char *)(*(int *)param_1 + 0x79) != 0;
    iVar4 = (int)((int *)param_1 + -0x1A8756) / 0x68;
    iVar3 = func_00338410(iVar4);
    cVar2 = *(char *)(iVar3 + 8);
    if ((cVar2 == 3) || (cVar2 == 1)) {
        uVar5 = func_0033C560(param_1);
        func_002974A0(uVar5, param_2, param_3, param_4, param_5, bVar1, param_6);
    }
    else if ((cVar2 == 2) || (cVar2 == 0)) {
        uVar5 = func_0033C4E0(param_1);
        func_00297530(uVar5, param_2, param_3, param_4, param_5, bVar1, param_6);
    }
    else {
        iVar3 = func_00338410(iVar4);
        cVar2 = *(char *)(iVar3 + 2);
        if (cVar2 == 5) {
            iVar4 = func_00338410(iVar4);
            if (*(char *)(iVar4 + 5) == 5) {
                uVar5 = func_0033C160(param_1);
                func_00297530(uVar5, param_2, param_3, param_4, param_5, bVar1, param_6);
            }
        }
        else if ((cVar2 == 4) || (cVar2 == 2)) {
            uVar5 = func_0033C3A0(param_1);
            func_002974A0(uVar5, param_2, param_3, param_4, param_5, bVar1, param_6);
        }
        else if ((cVar2 == 3) || (cVar2 == 1)) {
            uVar5 = func_0033C320(param_1);
            func_00297530(uVar5, param_2, param_3, param_4, param_5, bVar1, param_6);
        }
        else {
            func_002974A0(param_1, param_2, param_3, param_4, param_5, bVar1, param_6);
        }
    }
}

/* 0x00298950, 0x84 bytes. */
void func_00298950(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    if (param_6 == 0) {
        if (param_8 == 0) {
            func_00297C00(param_2, 0xFA, 0xCD, param_5, 0, param_7);
        }
        else if (param_8 == 1) {
            func_00298670(param_1, param_2, 0x120, 0xEA);
        }
    }
    else if (param_8 != 2) {
        func_00297890(param_2, 0x11A, 0xF8, param_5);
    }
}

/* 0x0029A5C0, 0x48 bytes. */
int func_0029A5C0(int param_1)
{
    int iVar1;
    u32 uVar2;

    iVar1 = 0;
    uVar2 = 0;
    if (*(u8 *)(param_1 + 0x25) != 0) {
        do {
            if (*(u8 *)(param_1 + uVar2 + 6) < 0x1F) {
                iVar1 = iVar1 + 1;
            }
            uVar2 = uVar2 + 1;
        } while (uVar2 < *(u8 *)(param_1 + 0x25));
    }
    return iVar1;
}

/* 0x0029AB60, 0x38 bytes. */
int func_0029AB60(int param_1)
{
    u32 uVar1;

    if ((param_1 < 0) || (9 < param_1)) {
        uVar1 = 0x5A;
    }
    else {
        uVar1 = *(u32 *)(g_00411950 + (int)param_1 * 4);
    }
    return uVar1;
}

/* 0x0029BDC0, 0xFC bytes. */
void func_0029BDC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    int iVar1;

    func_002C7310();
    if (param_9 == 0) {
        func_002C99F0(param_1 + 0x18, param_2 + 0x20 + (param_8 & 0xFF) * 0x14, param_3, 0x60, 0x10, 0x80,
                                  param_6);
        func_002D6930(0x30, param_1 + 0x20, param_2 + 0xC, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, param_6,
                                  0x80);
        param_2 = param_2 + 0x20;
        iVar1 = 0;
        do {
            func_002D6930(iVar1 + 0x25, param_1 + 0x20, param_2, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF,
                                      param_6, 0x80);
            iVar1 = iVar1 + 1;
            param_2 = param_2 + 0x14;
        } while (iVar1 < 0xB);
    }
}

/* 0x0029C9B0, 0x2C bytes, matching. */
void func_0029C9B0(int param_1, int param_2, int param_3)
{
    func_00299F60(0, 0x3C, 0, 0, *(u8 *)(param_3 + 8));
}

/* 0x0029C9E0, 0x34 bytes, matching. */
void func_0029C9E0(int param_1, int param_2, int param_3, int param_4)
{
    func_00298950(param_1, param_2, 0, 0, 0, *(u32 *)(param_2 + 0x80) & 0x30, param_3, param_4);
}

/* 0x0029CB90, 0x74 bytes. */
void func_0029CB90(int param_1, int param_2, int param_3)
{
    u8 * pbVar1;

    func_0029C930(param_3);
    pbVar1 = (u8 *)param_3;
    func_0029C9E0(param_1, *(u32 *)((u32)pbVar1[1] * 4 + (u32)*pbVar1 * 0x78 + param_2 + 0x180)
                              , 0, pbVar1[0x59]);
}

/* 0x0029D000, 0x1E4 bytes. */
int func_0029D000(int param_1, int param_2, int param_3)
{
    int bVar1;
    int bVar2;
    int cVar3;
    int lVar5;
    u32 uVar4;
    u32 uVar6;
    u32 uVar7;

    if ((param_3 == 0) || (lVar5 = func_0029CFB0(), lVar5 == 0)) {
        bVar1 = *(u8 *)(param_2 + param_1 + 6);
        if (bVar1 < 0x1F) {
            uVar7 = (u32)*(u8 *)(param_1 + 1);
            if ((0xC < bVar1) && (bVar1 < 0x14)) {
                uVar6 = 0;
                do {
                    if ((((uVar6 != uVar7) && (bVar2 = *(u8 *)(param_1 + uVar6 + 4), bVar2 < 0x1F)) &&
                            (bVar2 = *(u8 *)(param_1 + (u32)bVar2 + 6), 0xC < bVar2)) && (bVar2 < 0x14)) {
                        return 0;
                    }
                    uVar6 = uVar6 + 1;
                } while (uVar6 < 2);
            }
            if (bVar1 < 2) {
                uVar6 = 0;
                do {
                    if ((uVar6 != uVar7) && (bVar2 = *(u8 *)(param_1 + uVar6 + 4), bVar2 < 0x1F)) {
                        cVar3 = *(char *)(param_1 + (u32)bVar2 + 6);
                        if ((cVar3 == 0) && (bVar1 == 1)) {
                            return 0;
                        }
                        if ((cVar3 == 1) && (bVar1 == 0)) {
                            return 0;
                        }
                    }
                    uVar6 = uVar6 + 1;
                } while (uVar6 < 2);
            }
            if (((bVar1 == 4) && (lVar5 = func_00362570(), lVar5 != 2)) && (lVar5 != 0)) {
                uVar4 = 0;
            }
            else {
                lVar5 = func_0036EFC0(bVar1);
                if (lVar5 == 0) {
                    uVar6 = 0;
                    do {
                        if (((uVar6 != uVar7) && (bVar2 = *(u8 *)(param_1 + uVar6 + 4), bVar2 < 0x1F)) &&
                              (*(u8 *)(param_1 + (u32)bVar2 + 6) == bVar1)) {
                            return 0;
                        }
                        uVar6 = uVar6 + 1;
                    } while (uVar6 < 2);
                }
                uVar4 = 1;
            }
        }
        else {
            uVar4 = 0;
        }
    }
    else {
        uVar4 = 0;
    }
    return uVar4;
}

/* 0x0029DEF0, 0x30 bytes. */
void func_0029DEF0(int param_1, int param_2)
{
    if (param_2 == 0) {
        func_001F2BB0();
    }
    else {
        func_001F2B70();
    }
}

/* 0x0029E370, 0x4C bytes. */
int func_0029E370(int param_1)
{
    if ((param_1 < 0x3E) || (0x67 < param_1)) {
        if (param_1 == 0x68) {
            param_1 = 0x44;
        }
        else if (param_1 == 0x69) {
            param_1 = 0x45;
        }
    }
    else {
        param_1 = param_1 + -0x24;
    }
    return param_1;
}

/* 0x002A5BE0, 0x54 bytes. */
void func_002A5BE0(void)
{
    int iVar1;
    u32 uVar2;

    uVar2 = 0xF3;
    iVar1 = (int)g_00779D00;
    do {
        if (*(int *)(iVar1 + 400) != 0) {
            func_002A5B10(uVar2);
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 0x70;
    } while (uVar2 < 0x107);
}

/* 0x002A6340, 0x9C bytes. */
void func_002A6340(void)
{
    int iVar2;
    int iVar3;
    int iVar4;
    u32 uVar1;

    iVar4 = 0;
    iVar3 = (int)g_0077BE70;
    do {
        if ((0 < *(int *)(iVar3 + 0x18)) &&
              (iVar2 = *(int *)(iVar3 + 0x18) + -1, *(int *)(iVar3 + 0x18) = iVar2, iVar2 < 1)) {
            uVar1 = *(u32 *)(iVar3 + 0x10);
            if (uVar1 < 0x107) {
                if (*(int *)(uVar1 * 0x70 + 0x773440) == 0) {
                    *(u32 *)(iVar3 + 0x18) = 0;
                }
                else {
                    func_002A6D20(uVar1, *(u32 *)(iVar3 + 0x14));
                }
            }
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 0x20;
    } while (iVar4 < 4);
}

/* 0x002A64C0, 0x90 bytes. */
int func_002A64C0(int param_1)
{
    int iVar1;
    u32 uVar2;

    uVar2 = param_1 & 0xFF;
    iVar1 = (int)param_1 >> 8;
    if (iVar1 == 7) {
        iVar1 = *(u32 *)(g_0074B824 + 0xC) * 0x100 + uVar2;
    }
    else if (iVar1 == 6) {
        iVar1 = *(u32 *)(g_0074B824 + 0x8) * 0x100 + uVar2;
    }
    else if (iVar1 == 5) {
        iVar1 = *(u32 *)(g_0074B824 + 0x4) * 0x100 + uVar2;
    }
    else if (iVar1 == 4) {
        iVar1 = *(u32 *)g_0074B824 * 0x100 + uVar2;
    }
    else {
        iVar1 = iVar1 * 0x100 + uVar2;
    }
    return iVar1;
}

/* 0x002A6770, 0x1A0 bytes. */
void func_002A6770(int param_1, int param_2)
{
    int bVar1;
    int iVar2;
    int iVar4;
    u32 uVar3;

    if (param_1 < 0x107) {
        iVar4 = (int)(u32)param_2 >> 8;
        if (((iVar4 == 8) || (iVar4 == 3)) || (iVar4 == 5)) {
            bVar1 = true;
        }
        else if ((param_2 == 0x23C) || (param_2 == 0xB)) {
            bVar1 = true;
        }
        else {
            bVar1 = false;
        }
        if (bVar1) {
            func_0023ACC0(param_2, 0);
        }
        else {
            uVar3 = (u32)param_2 & 0xFF;
            if (iVar4 == 7) {
                iVar4 = *(u32 *)(g_0074B824 + 0xC) * 0x100 + uVar3;
            }
            else if (iVar4 == 6) {
                iVar4 = *(u32 *)(g_0074B824 + 0x8) * 0x100 + uVar3;
            }
            else if (iVar4 == 5) {
                iVar4 = *(u32 *)(g_0074B824 + 0x4) * 0x100 + uVar3;
            }
            else if (iVar4 == 4) {
                iVar4 = *(u32 *)g_0074B824 * 0x100 + uVar3;
            }
            else {
                iVar4 = iVar4 * 0x100 + uVar3;
            }
            uVar3 = 0;
            do {
                iVar2 = uVar3 * 0x3C;
                if ((*(u32 *)(iVar2 + 0x77A72C) == param_1) && (*(int *)(iVar2 + 0x77A730) == iVar4)) {
                    *(u32 *)(iVar2 + 0x77A734) = 0;
                    func_002A5080(*(int *)(iVar2 + 0x77A72C) * 0x70 + 0x7733F0, iVar2 + 0x77A700, uVar3 + 1);
                }
                uVar3 = uVar3 + 1;
            } while (uVar3 < 100);
        }
    }
}

/* 0x002A72B0, 0x134 bytes. */
int func_002A72B0(int param_1, int param_2, int param_3)
{
    int iVar2;
    int lVar1;
    u32 uVar3;

    if (*(u32 *)g_00669FA4 == 5) {
        uVar3 = 0x50D;
    }
    else if (*(u32 *)g_00669FA4 == 3) {
        uVar3 = 0x507;
    }
    else {
        if (*(u32 *)g_00669FA4 != 2) {
            return param_3;
        }
        uVar3 = 0x506;
    }
    lVar1 = func_00190610(*(u32 *)(param_2 + 0x90), 0x100);
    if (lVar1 == 0) {
        iVar2 = (int)uVar3 >> 8;
        uVar3 = uVar3 & 0xFF;
        if (iVar2 == 7) {
            iVar2 = *(u32 *)(g_0074B824 + 0xC) * 0x100 + uVar3;
        }
        else if (iVar2 == 6) {
            iVar2 = *(u32 *)(g_0074B824 + 0x8) * 0x100 + uVar3;
        }
        else if (iVar2 == 5) {
            iVar2 = *(u32 *)(g_0074B824 + 0x4) * 0x100 + uVar3;
        }
        else if (iVar2 == 4) {
            iVar2 = *(u32 *)g_0074B824 * 0x100 + uVar3;
        }
        else {
            iVar2 = iVar2 * 0x100 + uVar3;
        }
        func_002A6FF0(param_1, iVar2);
        param_3 = 1;
    }
    return param_3;
}

/* 0x002A77F0, 0x4C bytes. */
void func_002A77F0(void)
{
    if (*(u32 *)g_00773340 != 0) {
        func_002A6340();
        func_002A60C0();
        func_002A5880();
        func_002A5130();
        func_0023B5C0();
    }
}

/* 0x002A7870, 0x34 bytes, matching. */
void func_002A7870(void)
{
    func_002A5BE0();
    func_002A5ED0();
    func_002A5D00();
    func_002A6290();
}

/* 0x002A78B0, 0xC0 bytes. */
void func_002A78B0(void)
{
    int iVar1;
    u32 uVar2;

    func_002A62B0(0, *(u32 *)g_006A3A44 + 0x40);
    if ((*(u32 *)g_00669F60 & 2) != 0) {
        if (*(u32 *)g_00669E48 == 0) {
            func_002A62B0(1, *(u32 *)g_006A3A44 + 0x40);
        }
        else {
            func_002A62B0(1, *(u32 *)(g_006A3A44 + 0xC0) + 0x40);
        }
    }
    uVar2 = 0;
    iVar1 = (int)g_006A3A30;
    do {
        func_002A5FD0(uVar2, *(int *)(iVar1 + 0x14) + 0x40);
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 0xC0;
    } while (uVar2 < 0x8F);
    func_002A5BE0();
}

/* 0x002A7970, 0x44 bytes. */
void func_002A7970(void)
{
    *(u32 *)(g_0077BEF0) = 0xF3;
    *(u32 *)(g_0077BEF0 + 0x4) = 0;
    func_002A6470();
    func_002A62D0();
    func_002A6040();
    func_002A5790();
}

/* 0x002A79C0, 0x90 bytes. */
void func_002A79C0(void)
{
    int iVar2;
    int iVar3;
    u32 * puVar1;

    iVar2 = 0;
    g_0045D570 = 0;
    puVar1 = (u32 *)0x77CEA0;
    do {
        func_00148130(puVar1 + 4);
        iVar2 = iVar2 + 1;
        puVar1[2] = 0x11;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[3] = 0;
        puVar1 = puVar1 + 0x10;
    } while (iVar2 < 4);
    iVar2 = 0;
    iVar3 = (int)g_0077C040;
    do {
        func_0014F850(iVar3);
        func_0014F8B0(iVar3, 0);
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 0x170;
    } while (iVar2 < 10);
}

/* 0x002A7AF0, 0x100 bytes. */
int func_002A7AF0(int param_1, int param_2)
{
    int iVar2;
    int iVar3;
    u32 uVar1;

    if ((param_1 < 0) || (0x10 < param_1)) {
        uVar1 = 0;
    }
    else {
        iVar2 = g_0045D570 * 0x40;
        func_00103000(0);
        iVar3 = (int)param_1 * 4;
        uVar1 = func_001026D0(1, *(u16 *)(g_00411E20 + iVar3), 0, param_2, 0, 0, 0x4411B8, 0x6B);
        *(u32 *)(iVar2 + 0x77CEA0) = uVar1;
        func_00103000(1);
        uVar1 = func_001026D0(1, *(u16 *)((g_00411E20 + 0x2) + iVar3), 0, param_2, 0, 0, 0x4411B8, 0x70);
        *(u32 *)(iVar2 + 0x77CEA4) = uVar1;
        *(int *)(iVar2 + 0x77CEA8) = (int)param_1;
        uVar1 = 1;
        g_0045D570 = g_0045D570 + 1;
    }
    return uVar1;
}

/* 0x002A7BF0, 0xE8 bytes. */
int func_002A7BF0(void)
{
    int iVar1;
    int iVar2;
    int iVar4;
    int * piVar5;
    int uVar3;

    iVar4 = 0;
    piVar5 = (int *)0x77CEA0;
    do {
        if ((piVar5[2] != 0x11) && (piVar5[3] == 0)) {
            iVar1 = *piVar5;
            iVar2 = iVar4 * (u32)*(u16 *)(iVar1 + 0x24) * (u32)*(u16 *)(iVar1 + 0x26);
            if (iVar2 < 0) {
                iVar2 = iVar2 + 0xFF;
            }
            uVar3 = func_00107440(iVar1, (iVar2 >> 8) + 0x1820, (iVar4 + 0xC5) * 0x20);
            func_00103000(0);
            func_00102EC0(iVar1);
            func_00103000(1);
            *piVar5 = 0;
            func_001482F0(piVar5[1], piVar5 + 4, uVar3);
            piVar5[1] = 0;
            piVar5[3] = 1;
        }
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 0x10;
    } while (iVar4 < 4);
    return 1;
}

/* 0x002A7CE0, 0xA4 bytes. */
void func_002A7CE0(void)
{
    int iVar1;
    int * piVar2;

    iVar1 = 0;
    piVar2 = (int *)0x77CEA0;
    do {
        if ((piVar2[2] != 0x11) && (piVar2[3] == 0)) {
            if (*piVar2 != 0) {
                func_00103000(0);
                func_00102EC0(*piVar2);
                func_00103000(1);
                *piVar2 = 0;
            }
            if (piVar2[1] != 0) {
                func_00102EC0();
                piVar2[1] = 0;
            }
            piVar2[2] = 0x11;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 0x10;
    } while (iVar1 < 4);
}

/* 0x002A7D90, 0x98 bytes. */
void func_002A7D90(void)
{
    int iVar1;
    int iVar2;

    iVar2 = 0;
    iVar1 = (int)g_0077CEA0;
    do {
        if (*(int *)(iVar1 + 8) != 0x11) {
            func_00148370(iVar1 + 0x10);
            *(u32 *)(iVar1 + 8) = 0x11;
            *(u32 *)(iVar1 + 0xC) = 0;
        }
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x40;
    } while (iVar2 < 4);
    iVar1 = 0;
    iVar2 = (int)g_0077C040;
    do {
        *(u32 *)(iVar2 + 0x160) = 0;
        iVar1 = iVar1 + 5;
        *(u32 *)(iVar2 + 0x2D0) = 0;
        *(u32 *)(iVar2 + 0x440) = 0;
        *(u32 *)(iVar2 + 0x5B0) = 0;
        *(u32 *)(iVar2 + 0x720) = 0;
        iVar2 = iVar2 + 0x730;
    } while (iVar1 < 10);
    g_0045D570 = 0;
}

/* 0x002A7E30, 0x3C bytes. */
int func_002A7E30(int param_1)
{
    int iVar1;
    int iVar2;

    iVar2 = 0;
    iVar1 = (int)g_0077CEA0;
    do {
        if (param_1 == *(int *)(iVar1 + 8)) {
            return iVar1 + 0x10;
        }
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 0x40;
    } while (iVar2 < 4);
    return 0;
}

/* 0x002A7EC0, 0x5C bytes. */
void func_002A7EC0(void)
{
    u32 * puVar1;
    u32 uVar2;

    uVar2 = 0;
    g_0045D578 = 0;
    g_0045D574 = 0x30;
    puVar1 = (u32 *)0x77CFA0;
    do {
        func_00118850(puVar1, 0x110);
        *puVar1 = uVar2;
        uVar2 = uVar2 + 1;
        puVar1 = puVar1 + 0x44;
    } while (uVar2 < 0x30);
}

/* 0x002AB450, 0x90 bytes. */
void func_002AB450(int param_1, int param_2, int param_3, int param_4)
{
    int lVar1;

    if ((399 < param_3 && param_3 < 0x19F) ||
          ((param_3 < 400 || 0x19E < param_3 && (lVar1 = func_003A0040(param_3), lVar1 != 0)))) {
        func_003B5930(param_1, param_2, 0, param_4);
    }
}

/* 0x002AFB80, 0x9C bytes. */
void func_002AFB80(int param_1)
{
    int cVar1;
    int lVar2;

    cVar1 = *(char *)((int)param_1 + 0x7C);
    if (cVar1 == 3) {
        lVar2 = func_002B0910();
        if (lVar2 == 0) {
            func_002B08F0(param_1);
        }
    }
    else if (cVar1 == 2) {
        func_002B08F0();
    }
    else if (cVar1 == 1) {
        func_002396B0();
    }
    else if (cVar1 == 0) {
        func_002AFA20();
    }
}

/* 0x002B5990, 0x34 bytes, matching. */
void func_002B5990(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    func_002C7310(param_2, param_3, param_4, param_5, param_6, param_7, param_8);
}

/* 0x002B7BA0, 0x8C bytes. */
void func_002B7BA0(int param_1)
{
    int iVar1;
    int lVar2;
    int uVar3;
    u32 uVar4;

    lVar2 = func_002F41E0();
    iVar1 = (int)lVar2;
    if (lVar2 < 0) {
        iVar1 = iVar1 + 1;
    }
    if ((iVar1 >> 1 & 0xffU) < 7) {
        lVar2 = func_002F41E0(param_1);
        iVar1 = (int)lVar2;
        if (lVar2 < 0) {
            iVar1 = iVar1 + 1;
        }
        uVar4 = iVar1 >> 1 & 0xFF;
    }
    else {
        uVar4 = 6;
    }
    uVar3 = func_002F2890(param_1);
    func_002B7320(uVar3, uVar4, param_1, 0);
}

/* 0x002BC880, 0x128 bytes. */
int func_002BC880(int param_1, int param_2, int param_3)
{
    int bVar1;
    int lVar3;
    int uVar2;

    if (*(char *)(param_1 + 2) != 0) {
        if ((param_3 == 3) || (param_3 == 1)) {
            bVar1 = 0;
        }
        else if ((param_3 == 2) || (param_3 == 0)) {
            bVar1 = 1;
        }
        else {
            bVar1 = 0;
        }
        func_0027E730(param_2, bVar1 ^ 1);
    }
    if (param_3 != 3) {
        if (param_3 == 1) {
            lVar3 = func_0027E660(param_2);
            if (lVar3 != 0) {
                uVar2 = func_002BC110(param_2, *(u8 *)(param_1 + 10));
                *(u8 *)((int)lVar3 + 10) = uVar2;
            }
        }
        else if (param_3 != 2) {
            if (param_3 != 0) {
                return 0;
            }
            lVar3 = func_0027E660(param_2);
            if (lVar3 != 0) {
                uVar2 = func_002BC110(param_2, *(u8 *)(param_1 + 8));
                *(u8 *)((int)lVar3 + 10) = uVar2;
            }
        }
    }
    return 1;
}

/* 0x002BF9E0, 0xD0 bytes. */
void func_002BF9E0(int param_1, int param_2)
{
    int cVar1;
    int lVar2;

    if ((*(u32 *)g_00669F60 & 0x100000) == 0) {
        lVar2 = func_0027E660();
        if (lVar2 != 0) {
            cVar1 = *(char *)((u32)*(u8 *)((int)lVar2 + 10) * 0xC60 + 0x796044);
            if (cVar1 == 3) {
                func_002BFAB0(param_1, param_2);
            }
            else {
                if (cVar1 != 2) {
                    if (cVar1 != 1) {
                        return;
                    }
                    func_001FBFB0(param_1, param_2);
                }
                func_001FF450(param_1, param_2);
            }
        }
    }
}

/* 0x002C1690, 0x144 bytes. */
void func_002C1690(int param_1, u8 *param_2, int param_3)
{
    int bVar1;
    int iVar3;
    u32 uVar2;
    u32 uVar4;

    uVar4 = 0;
    if (*(u8 *)(g_0045D2F0 + 0x10A) != 0) {
        iVar3 = *(int *)(g_0045D2F0 + 0x10C);
        do {
            if (*(u8 *)(iVar3 + 0xB) == *param_2) {
                iVar3 = (int)uVar4 >> 3;
                if (param_3 == 1) {
                    uVar2 = uVar4 & 7;
                    if (((int)uVar4 < 0) && (uVar2 != 0)) {
                        uVar2 = uVar2 - 8;
                    }
                    bVar1 = (u8)(1 << (uVar2 & 0x1F));
                    *(u8 *)(iVar3 + 0x73DC98) = *(u8 *)(iVar3 + 0x73DC98) | bVar1;
                    *(u8 *)(iVar3 + 0x73DF28) = *(u8 *)(iVar3 + 0x73DF28) | bVar1;
                }
                else {
                    uVar2 = uVar4 & 7;
                    if (((int)uVar4 < 0) && (uVar2 != 0)) {
                        uVar2 = uVar2 - 8;
                    }
                    bVar1 = ~(u8)(1 << (uVar2 & 0x1F));
                    *(u8 *)(iVar3 + 0x73DC98) = *(u8 *)(iVar3 + 0x73DC98) & bVar1;
                    *(u8 *)(iVar3 + 0x73DF28) = *(u8 *)(iVar3 + 0x73DF28) & bVar1;
                }
                break;
            }
            uVar4 = uVar4 + 1;
            iVar3 = iVar3 + 0xC;
        } while (uVar4 < *(u8 *)(g_0045D2F0 + 0x10A));
    }
    func_002C1450(*(u32 *)((u32)*param_2 * 4 + 0x796000), param_3 == 1);
    func_0018EA60();
}

/* 0x002C3260, 0xB4 bytes. */
int func_002C3260(int param_1, int param_2)
{
    int bVar1;
    u32 uVar2;

    if ((param_2 == 3) || (param_2 == 1)) {
        bVar1 = false;
    }
    else if ((param_2 == 2) || (param_2 == 0)) {
        bVar1 = true;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
        if ((g_7000015C >> 0x10) % 100 < 0x32) {
            func_002C33C0();
        }
        uVar2 = 1;
    }
    else {
        func_002C33C0();
        uVar2 = 0;
    }
    return uVar2;
}

/* 0x002C3980, 0x150 bytes. */
int func_002C3980(int param_1, u8 *param_2, int param_3)
{
    int cVar2;
    int iVar1;
    int * piVar4;
    u32 uVar3;

    piVar4 = *(int **)(g_00412470 + (u32)*param_2 * 4);
    if (piVar4 == (int *)0) {
        uVar3 = 0;
    }
    else {
        iVar1 = *piVar4;
        while (iVar1 < 0x1E) {
            if ((param_3 == 3) || (param_3 == 1)) {
                cVar2 = 0;
                if (*piVar4 < 10) {
                    cVar2 = *(char *)(*piVar4 + 0x73E020);
                }
                if (cVar2 != 0) {
                    func_002180F0();
                }
            }
            else if (param_3 == 2) {
                cVar2 = 0;
                if (*piVar4 < 10) {
                    cVar2 = *(char *)(*piVar4 + 0x73E020);
                }
                if (cVar2 == 0) {
                    func_00218070();
                }
            }
            else if (param_3 == 0) {
                cVar2 = 0;
                if (*piVar4 < 10) {
                    cVar2 = *(char *)(*piVar4 + 0x73E020);
                }
                if (cVar2 == 0) {
                    func_00217F40();
                }
            }
            piVar4 = piVar4 + 1;
            iVar1 = *piVar4;
        }
        uVar3 = 1;
    }
    return uVar3;
}

/* 0x002C4030, 0x1E8 bytes. */
int func_002C4030(int param_1, int param_2)
{
    int bVar1;
    int iVar3;
    int iVar5;
    int lVar4;
    int uVar2;

    iVar5 = (int)param_1;
    uVar2 = func_001FF100(*(u16 *)(iVar5 + 0x54), 10);
    iVar3 = func_002C3DC0(uVar2);
    if ((param_2 == 3) || (param_2 == 1)) {
        bVar1 = false;
    }
    else if ((param_2 == 2) || (param_2 == 0)) {
        bVar1 = true;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        if ((*(u8 *)(iVar5 + 0x69) & 1) != 0) {
            return false;
        }
    }
    else if ((*(u8 *)(iVar5 + 0x69) & 1) == 0) {
        return false;
    }
    if (param_2 != 3) {
        if (param_2 != 1) {
            if ((param_2 != 2) && (param_2 != 0)) {
                return false;
            }
            lVar4 = func_002C33C0(param_1, 2);
            if (lVar4 == 0) {
                return false;
            }
            *(char *)(iVar3 + 1) = *(char *)(iVar3 + 1) + 1;
            return true;
        }
        iVar5 = (u32)*(u8 *)(iVar3 + 1) - (u32)*(u8 *)(iVar3 + 2);
        if (iVar5 < 0) {
            return false;
        }
        if (iVar5 == 0) {
            return false;
        }
        if (iVar5 == 0) {
            iVar5 = 0;
        }
        else {
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            iVar5 = (int)(g_7000015C >> 0x10) % iVar5;
        }
        if (iVar5 != 0) {
            *(char *)(iVar3 + 2) = *(char *)(iVar3 + 2) + 1;
            return false;
        }
    }
    lVar4 = func_002C33C0(param_1, 3);
    if (lVar4 != 0) {
        *(char *)(iVar3 + 1) = *(char *)(iVar3 + 1) + -1;
        *(u8 *)(iVar3 + 2) = *(u8 *)(iVar3 + 1);
    }
    return lVar4 != 0;
}

/* 0x002C4AE0, 0x84 bytes. */
void func_002C4AE0(u32 *param_1)
{
    int iVar1;

    iVar1 = *(u32 *)(g_005BD6A8 + 0x4) * 0x110;
    *(u32 *)(iVar1 + 0x5BC5A8) = (*(u32 *)(g_00669F9C));
    *(u32 *)(iVar1 + 0x5BC5B0) = *param_1;
    *(u32 *)(iVar1 + 0x5BC5B4) = param_1[1];
    func_00120928(iVar1 + 0x5BC5B8);
    if (*(u32 *)g_005BD6A8 < 0x10) {
        *(u32 *)(g_005BD6A8) = *(u32 *)(g_005BD6A8) + 1;
    }
    *(u32 *)(g_005BD6A8 + 0x4) = *(u32 *)(g_005BD6A8 + 0x4) + 1 & 0xF;
}

/* 0x002C5220, 0x2D0 bytes. */
int func_002C5220(int param_1, u8 *param_2, u8 *param_3, int param_4, int param_5)
{
    int bVar1;
    int uVar2;
    int uVar3;
    u32 uVar4;

    param_1 = param_1 * 0x88;
    if ((*(u8 *)(param_1 + 0x500764) & 1) == 0) {
        bVar1 = false;
    }
    else {
        bVar1 = (*(u8 *)(param_1 + 0x500765) & 1) == 1;
    }
    if (bVar1) {
        uVar2 = *(u16 *)(param_1 + 0x50074C);
    }
    else {
        uVar2 = 0;
    }
    if ((*(u8 *)(param_1 + 0x500764) & 1) == 0) {
        bVar1 = false;
    }
    else {
        bVar1 = (*(u8 *)(param_1 + 0x500765) & 1) == 1;
    }
    if (bVar1) {
        uVar3 = *(u16 *)(param_1 + 0x50074E);
    }
    else {
        uVar3 = 0;
    }
    if (param_5 < 2) {
        uVar4 = 0;
    }
    else if ((uVar2 & 0x4000) == 0) {
        if ((uVar3 & 0x4000) == 0) {
            if ((uVar2 & 0x1000) != 0) {
                if (*param_3 == 0) {
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    *param_3 = param_5 - 1;
                    *param_2 = param_4 - 1;
                    return 1;
                }
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                *param_3 = *param_3 - 1;
                if (*param_2 != 0) {
                    *param_2 = *param_2 - 1;
                }
                return 1;
            }
            if (((uVar3 & 0x1000) != 0) && (*param_3 != 0)) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                *param_3 = *param_3 - 1;
                if (*param_2 != 0) {
                    *param_2 = *param_2 - 1;
                }
                return 1;
            }
        }
        else if ((int)(u32)*param_3 < (int)(param_5 - 1)) {
            *param_3 = *param_3 + 1;
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            if ((int)(u32)*param_2 < (int)(param_4 - 1)) {
                *param_2 = *param_2 + 1;
            }
            return 1;
        }
        uVar4 = 0;
    }
    else {
        if ((int)(u32)*param_3 < (int)(param_5 - 1)) {
            *param_3 = *param_3 + 1;
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            if ((int)(u32)*param_2 < (int)(param_4 - 1)) {
                *param_2 = *param_2 + 1;
            }
        }
        else {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            *param_2 = 0;
            *param_3 = 0;
        }
        uVar4 = 1;
    }
    return uVar4;
}

/* 0x002C54F0, 0x3E8 bytes. */
int func_002C54F0(int param_1, u8 *param_2, u8 *param_3, int param_4, int param_5)
{
    int bVar1;
    int uVar2;
    int uVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;
    u32 uVar7;

    param_1 = param_1 * 0x88;
    if ((*(u8 *)(param_1 + 0x500764) & 1) == 0) {
        bVar1 = false;
    }
    else {
        bVar1 = (*(u8 *)(param_1 + 0x500765) & 1) == 1;
    }
    if (bVar1) {
        uVar2 = *(u16 *)(param_1 + 0x50074C);
    }
    else {
        uVar2 = 0;
    }
    if ((*(u8 *)(param_1 + 0x500764) & 1) == 0) {
        bVar1 = false;
    }
    else {
        bVar1 = (*(u8 *)(param_1 + 0x500765) & 1) == 1;
    }
    if (bVar1) {
        uVar3 = *(u16 *)(param_1 + 0x50074E);
    }
    else {
        uVar3 = 0;
    }
    uVar6 = (u32)param_5;
    if (uVar6 < 2) {
        uVar4 = 0;
    }
    else {
        uVar7 = (u32)param_5;
        if ((uVar2 & 0x1000) == 0) {
            if ((uVar3 & 0x1000) == 0) {
                if ((uVar2 & 0x4000) != 0) {
                    if (*param_3 == 0) {
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        *param_3 = param_5 - 1;
                        *param_2 = param_4 - 1;
                        return 1;
                    }
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    *param_3 = *param_3 - 1;
                    if (*param_2 != 0) {
                        *param_2 = *param_2 - 1;
                    }
                    return 1;
                }
                if ((uVar3 & 0x4000) != 0) {
                    if (uVar6 <= param_4) {
                        if (*param_3 == 0) {
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                            *param_3 = param_5 - 1;
                            *param_2 = param_4 - 1;
                            return 1;
                        }
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        *param_3 = *param_3 - 1;
                        if (*param_2 != 0) {
                            *param_2 = *param_2 - 1;
                        }
                        return 1;
                    }
                    if (*param_3 != 0) {
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        *param_3 = *param_3 - 1;
                        if (*param_2 != 0) {
                            *param_2 = *param_2 - 1;
                        }
                        return 1;
                    }
                }
            }
            else {
                uVar5 = (u32)param_4;
                if (uVar6 <= uVar5) {
                    if ((int)(uVar7 - 1) <= (int)(u32)*param_3) {
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        *param_2 = 0;
                        *param_3 = 0;
                        return 1;
                    }
                    *param_3 = *param_3 + 1;
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    if ((int)(u32)*param_2 < (int)(uVar5 - 1)) {
                        *param_2 = *param_2 + 1;
                    }
                    return 1;
                }
                if ((int)(u32)*param_3 < (int)(uVar7 - 1)) {
                    *param_3 = *param_3 + 1;
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    if ((int)(u32)*param_2 < (int)(uVar5 - 1)) {
                        *param_2 = *param_2 + 1;
                    }
                    return 1;
                }
            }
            uVar4 = 0;
        }
        else {
            if ((int)(u32)*param_3 < (int)(uVar7 - 1)) {
                *param_3 = *param_3 + 1;
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                if ((int)(u32)*param_2 < (int)(param_4 - 1)) {
                    *param_2 = *param_2 + 1;
                }
            }
            else {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                *param_2 = 0;
                *param_3 = 0;
            }
            uVar4 = 1;
        }
    }
    return uVar4;
}

/* 0x002C65C0, 0xD4 bytes. */
void func_002C65C0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int uVar1;

    func_002C63A0();
    uVar1 = func_001050F0();
    *(unsigned long long *)((int)uVar1 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar1 + 0x18) = 0x43;
    func_00105230(uVar1, param_5);
    func_002C63A0(param_1, param_2, param_3, param_4, param_5, param_6);
    uVar1 = func_001050F0();
    *(unsigned long long *)((int)uVar1 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar1 + 0x18) = 0x43;
    func_00105230(uVar1, param_5);
}

/* 0x002CA590, 0xA8 bytes, matching. */
void func_002CA590(int param_1, int *param_2)
{
    int iVar2;
    u32 uVar1;

    uVar1 = func_002F41E0();
    *param_2 = (uVar1 & 0xFF) + 1;
    iVar2 = func_002F34E0(param_1);
    param_2[1] = iVar2;
    iVar2 = func_002F39F0(param_1);
    param_2[2] = iVar2;
    iVar2 = func_002F4C40(param_1);
    param_2[3] = iVar2;
    iVar2 = func_002F4DD0(param_1);
    param_2[4] = iVar2;
    iVar2 = func_002F4F60(param_1);
    param_2[5] = iVar2;
    iVar2 = func_002F50F0(param_1);
    param_2[6] = iVar2;
    iVar2 = func_002F5280(param_1);
    param_2[7] = iVar2;
    iVar2 = func_002F5410(param_1);
    param_2[8] = iVar2;
    iVar2 = func_002F55A0(param_1);
    param_2[9] = iVar2;
}

/* 0x002CA640, 0xE4 bytes. */
int func_002CA640(int param_1, int param_2)
{
    int iVar2;
    u32 uVar1;

    switch(param_2) {
    case 0:
        iVar2 = func_002F39F0(param_1);
        break;
    case 1:
        iVar2 = func_002F4C40(param_1);
        break;
    case 2:
        iVar2 = func_002F4DD0(param_1);
        break;
    case 3:
        iVar2 = func_002F4F60(param_1);
        break;
    case 4:
        iVar2 = func_002F50F0(param_1);
        break;
    case 5:
        iVar2 = func_002F5280(param_1);
        break;
    case 6:
        iVar2 = func_002F5410(param_1);
        break;
    case 7:
        iVar2 = func_002F55A0(param_1);
        break;
    case 8:
        iVar2 = func_002F34E0(param_1);
        break;
    case 9:
        uVar1 = func_002F41E0(param_1);
        iVar2 = (uVar1 & 0xFF) + 1;
        break;
    default:
        iVar2 = 0;
    }
    return iVar2;
}

/* 0x002CAC30, 0x12C bytes. */
void func_002CAC30(u8 *param_1, int param_2)
{
    int iVar4;
    u8 * puVar2;
    u8 * puVar5;
    u8 * puVar6;
    int uVar1;
    u32 uVar3;
    u32 uVar7;

    uVar7 = 0;
    param_1[0x51] = 4;
    param_1[0x50] = 0;
    puVar5 = param_1;
    do {
        *puVar5 = 0x7F;
        puVar6 = param_1 + (u32)(u8)param_1[0x50] * 0x14;
        puVar2 = (u8 *)func_0035DEC0(param_2, uVar7);
        iVar4 = 10;
        do {
            iVar4 = iVar4 + -1;
            uVar1 = puVar2[1];
            *puVar6 = *puVar2;
            puVar2 = puVar2 + 2;
            puVar6[1] = uVar1;
            puVar6 = puVar6 + 2;
        } while (0 < iVar4);
        if ((u8)param_1[(u32)(u8)param_1[0x50] * 0x14] < 0x7F) {
            uVar3 = func_002F5730(param_2);
            if (uVar7 == (uVar3 & 0xFF)) {
                param_1[0x51] = param_1[0x50];
            }
            param_1[0x50] = param_1[0x50] + 1;
        }
        uVar7 = uVar7 + 1;
        puVar5 = puVar5 + 0x14;
    } while ((int)uVar7 < 4);
    if ((param_1[0x51] == 4) || ((u8)param_1[0x50] <= (u8)param_1[0x51])) {
        param_1[0x51] = 0;
    }
}

/* 0x002CAD60, 0x2C bytes, matching. */
void func_002CAD60(u8 *param_1)
{
    *param_1 = 0x36;
    param_1[1] = 0x36;
    param_1[2] = 0x36;
    param_1[3] = 0x36;
    param_1[4] = 0x36;
    param_1[5] = 0x36;
    param_1[6] = 0x36;
    param_1[7] = 0x36;
    param_1[8] = 0;
}

/* 0x002CAD90, 0xF4 bytes. */
void func_002CAD90(u8 *param_1)
{
    int iVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

    uVar3 = 0;
    param_1[6] = 4;
    param_1[5] = 4;
    param_1[4] = 0;
    param_1[4] = 0;
    *param_1 = 4;
    param_1[1] = 4;
    param_1[2] = 4;
    param_1[3] = 4;
    param_1[4] = 0;
    do {
        iVar1 = func_0019FBC0(uVar3);
        if (*(char *)(iVar1 + 4) != 4) {
            uVar4 = 0;
            do {
                uVar2 = func_003DD680(uVar4);
                if (uVar3 == uVar2) {
                    param_1[uVar4 + 5] = (char)uVar2;
                    break;
                }
                uVar4 = uVar4 + 1 & 0xFF;
            } while (uVar4 < 2);
            param_1[(u8)param_1[4]] = (char)uVar3;
            param_1[4] = param_1[4] + 1;
        }
        uVar3 = uVar3 + 1 & 0xFF;
        if (3 < uVar3) {
            return;
        }
    } while( true );
}

/* 0x002CB4B0, 0x50 bytes, matching. */
void func_002CB4B0(int param_1)
{
    int uVar1;

    uVar1 = func_00105620();
    func_001055E0(uVar1);
    func_002CAE90(uVar1, param_1);
    func_001056C0(uVar1, 0);
}

/* 0x002CB500, 0x4C bytes, matching. */
void func_002CB500(int param_1)
{
    int uVar1;

    uVar1 = func_00105620();
    func_001055E0(uVar1);
    func_002CAE90(uVar1, param_1);
    func_00105770(uVar1);
}

/* 0x002D07A0, 0x34 bytes, matching. */
int func_002D07A0(int param_1)
{
    if ((param_1 < 0) || (0xE < param_1)) {
        if (param_1 == 0xF) {
            param_1 = 0xE;
        }
        else {
            param_1 = 0;
        }
    }
    return param_1;
}

/* 0x002D0DC0, 0x150 bytes. */
void func_002D0DC0(int param_1)
{
    int iVar1;
    int iVar2;

    *(u8 *)(param_1 + 0x68) = 0;
    iVar2 = 0;
    do {
        iVar1 = iVar2;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1;
        iVar2 = iVar1 + 8;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 1;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 2;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 3;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 4;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 5;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 6;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
        *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 7;
        *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
    } while (iVar2 < 0x12);
    *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar2;
    *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
    *(int *)(param_1 + (u32)*(u8 *)(param_1 + 0x68) * 4) = iVar1 + 9;
    *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + 1;
}

/* 0x002D67E0, 0xAC bytes. */
void func_002D67E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int uVar1;

    uVar1 = func_00106C90(*(unsigned long long *)g_0068F0F8, 0x3F6D);
    uVar1 = func_00105860(uVar1, 0);
    func_002D6560(uVar1, param_1, param_2, param_3, param_4, param_6);
    func_00105900(uVar1, param_5);
}

/* 0x002D6890, 0x60 bytes. */
int func_002D6890(void)
{
    int bVar1;

    bVar1 = *(u32 *)g_00799A6C == 0;
    if (bVar1) {
        *(u32 *)(g_00799A6C) = func_001026D0(1, 0x3C, 0, 1, 0, 0, 0x442630, 0x15DB);
    }
    return bVar1;
}

/* 0x002D68F0, 0x34 bytes. */
void func_002D68F0(void)
{
    if (*(u32 *)g_00799A6C != 0) {
        func_00102EC0();
    }
    *(u32 *)(g_00799A6C) = 0;
}

/* 0x002D6C30, 0x140 bytes. */
void func_002D6C30(int param_1)
{
    int iVar1;
    int iVar2;
    u32 * puVar3;

    iVar1 = *(u32 *)g_006A3A44;
    puVar3 = (u32 *)(*(u32 *)g_006A3A44 + 0x40);
    *(u32 *)(g_0073C79B) = func_0020E440(*(u8 *)(*(u32 *)(g_006A3A44 + 0x54) + 6));
    iVar2 = *(u32 *)(g_006A3A44 + 0xC0);
    *(u8 *)(g_0073C79B + 0x2) = 0;
    if (puVar3 != (u32 *)0) {
        *(u32 *)(g_0073C460) = *puVar3;
        *(u32 *)(g_0073C460 + 0x4) = *(u32 *)(iVar1 + 0x44);
        *(u32 *)(g_0073C460 + 0x8) = *(u32 *)(iVar1 + 0x48);
        *(u32 *)(g_0073C460 + 0xC) = *(u32 *)(iVar1 + 0x4C);
    }
    if ((*(u32 *)g_00669F60 & 2) == 0) {
        func_0020E5C0(param_1, *(u32 *)g_005BD6B0, 0);
    }
    else {
        puVar3 = (u32 *)(*(u32 *)(g_006A3A44 + 0xC0) + 0x40);
        *(u32 *)(g_0073C79B + 0x1) = func_0020E440(*(u8 *)(*(u32 *)(g_006A3A44 + 0x114) + 6));
        *(u8 *)(g_0073C79B + 0x2) = 1;
        if (puVar3 != (u32 *)0) {
            *(u32 *)(g_0073C460 + 0x10) = *puVar3;
            *(u32 *)(g_0073C460 + 0x14) = *(u32 *)(iVar2 + 0x44);
            *(u32 *)(g_0073C460 + 0x18) = *(u32 *)(iVar2 + 0x48);
            *(u32 *)(g_0073C460 + 0x1C) = *(u32 *)(iVar2 + 0x4C);
        }
        func_0020E740(param_1, *(u32 *)g_005BD6B0, 0, *(u32 *)(g_005BD6B0 + 0x4), 0);
    }
}
/* MISSING ['0x73c460', '0x73c464', '0x73c468', '0x73c46c', '0x73c470', '0x73c474', '0x73c478', '0x73c47c', '0x73c79b', '0x73c79c'] */

/* 0x002D7080, 0x1AC bytes. */
void func_002D7080(int param_1, int param_2)
{
    int iVar2;
    int iVar3;
    int uVar1;
    u32 uVar4;

    func_0020E5A0(param_2);
    uVar1 = *(u16 *)(g_00669E28 + 0x48);
    if (param_1 < 2) {
        iVar2 = func_002D6FE0(0);
        if ((*(u32 *)(g_00669E28 + 0x138) & 2) == 0) {
            func_0020EB60(iVar2 + 0x28, 1, 0);
            func_0020EB60(iVar2 + 0x45, 1, 0);
        }
        else {
            iVar3 = func_002D6FE0(1);
            func_0020EB60(iVar2 + 0x28, 1, 0);
            func_0020EB60(iVar3 + 0x28, 0, 0);
            func_0020EB60(iVar2 + 0x45, 1, 0);
            func_0020EB60(iVar3 + 0x45, 0, 0);
        }
    }
    else if (param_1 == 2) {
        func_0020EB60(*(u16 *)g_00669E28 + 0x45, 1, 0);
    }
    else {
        if (param_1 != 3) {
            return;
        }
        if ((*(u32 *)(g_00669E28 + 0x138) & 2) == 0) {
            uVar4 = (u32)(*(u16 *)g_00669E28);
            func_0020EB60(uVar4 + 0x28, 1, 0);
            func_0020EB60(uVar4 + 0x45, 1, 0);
        }
        else {
            uVar4 = (u32)(*(u16 *)g_00669E28);
            func_0020EB60(uVar4 + 0x28, 1, 0);
            func_0020EB60(uVar1 + 0x28, 0, 0);
            func_0020EB60(uVar4 + 0x45, 1, 0);
            func_0020EB60(uVar1 + 0x45, 0, 0);
        }
    }
    func_0020ECE0();
    func_0020E960(0, 1);
}

/* 0x002D78E0, 0x88 bytes. */
int func_002D78E0(int param_1)
{
    int iVar2;
    u32 uVar1;

    if (*(u32 *)g_00669DB8 == 2) {
        iVar2 = *(int *)((*(u32 *)g_00669F98 % 5) * 4 + 0x669DD4);
    }
    else {
        iVar2 = *(u32 *)(g_00669DB8 + 0x1C);
    }
    if (iVar2 == 5) {
        if (*(u8 *)(*(int *)(param_1 + 0x10) + 0x41) < 8) {
            uVar1 = 0x21;
        }
        else {
            uVar1 = 0x22;
        }
    }
    else {
        uVar1 = 0x21;
    }
    return uVar1;
}

/* 0x002D7EE0, 0x98 bytes, matching. */
void func_002D7EE0(int param_1)
{
    int iVar1;

    func_002DBAA0();
    iVar1 = 0;
    *(u32 *)(param_1 + 0x70) = 3;
    do {
        func_0039FF60(iVar1, 1);
        func_003A1290(iVar1, 1);
        iVar1 = iVar1 + 1;
    } while (iVar1 < 0x1C);
    iVar1 = 0;
    do {
        func_003A16A0(iVar1, 1);
        func_003A1830(iVar1, 1);
        iVar1 = iVar1 + 1;
    } while (iVar1 < 0x38);
    func_003A2810(0, 1);
}

/* 0x002D7F90, 0x60 bytes. */
void func_002D7F90(void)
{
    func_00118850(g_00799A70, 0x80);
    *(u32 *)(g_00799A78) = func_001026D0(1, 0x3D, 0, 1, 0, 0, 0x4426A0, 0x8C);
    *(u32 *)(g_00799A78 + 0x24) = 3;
}

/* 0x002D8160, 0x64 bytes. */
void func_002D8160(void)
{
    func_00102EC0(*(u32 *)(g_00799A7C + 0x18));
    *(u32 *)(g_00799A7C + 0x18) = 0;
    if (*(u32 *)(g_00799A7C + 0x20) != 0) {
        func_00102EC0(*(u32 *)g_00799A7C);
    }
    *(u32 *)(g_00799A7C) = 0;
    *(u32 *)(g_00799A7C + 0x20) = 3;
    func_001B8BF0();
    func_001037F0(*(u32 *)(g_00799A7C + 0x48));
}

/* 0x002D8280, 0x38 bytes. */
void func_002D8280(int param_1)
{
    if (*(int *)(param_1 + 0x78) != 5) {
        func_001AFE20();
    }
    *(u8 *)(g_006934B9) = 0;
    func_001B8BF0();
}

/* 0x002D82C0, 0xAC bytes. */
void func_002D82C0(int param_1, int param_2)
{
    func_001265F0(0, 1);
    func_002D8280(param_1);
    func_001AEDB0(param_2, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0);
    func_001AEE10(param_2, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    func_001AE9F0(param_2, *(u32 *)((int)param_1 + 0x24), 1);
    func_001AFC50(param_2);
    *(int *)((int)param_1 + 0x78) = (int)param_2;
    *(u8 *)((int)param_2 * 0x128 + 0x6934BA) = 1;
}

/* 0x002D8910, 0x40 bytes, matching. */
void func_002D8910(int param_1)
{
    u32 uVar1;

    *(u32 *)(param_1 + 0x40) = 1;
    uVar1 = func_0022DC70();
    *(u32 *)(param_1 + 0x5C) = uVar1;
    *(u32 *)(param_1 + 100) = 4;
    *(u32 *)(param_1 + 0x1C) = 0;
    *(u32 *)(param_1 + 0x20) = 0;
}

/* 0x002D8C30, 0x68 bytes. */
int func_002D8C30(int param_1, int param_2)
{
    if (*(int *)(param_1 + 0x28) - 1U < 2) {
        *(u32 *)(param_1 + 0x10) = 0x16;
        *(u32 *)(param_1 + 0x7C) = 0;
        *(u32 *)(param_1 + 0x4C) = 0;
        if (*(int *)(param_1 + 0x30) == 0) {
            if (*(int *)(param_1 + 0x2C) == 2) {
                *(u32 *)(param_1 + 0x10) = 0;
                *(u32 *)(param_1 + 0x70) = 0;
                *(u32 *)(param_1 + 0x34) = 0;
                *(u32 *)(param_1 + 0x58) = 0;
            }
            else {
                param_2 = 2;
            }
        }
        else {
            param_2 = 1;
        }
    }
    return param_2;
}

/* 0x002D8EE0, 0x80 bytes, matching. */
void func_002D8EE0(int param_1)
{
    int iVar2;
    int lVar1;

    lVar1 = func_0022DD60();
    if ((lVar1 == -1) || (lVar1 == 2)) {
        func_002D8DA0(param_1);
    }
    lVar1 = func_0022DCD0();
    if (lVar1 != 0) {
        func_002D8CA0(param_1);
    }
    iVar2 = (int)param_1;
    if (*(int *)(iVar2 + 0x5C) < 1) {
        func_002D8280(param_1);
        *(u32 *)(iVar2 + 0x78) = 5;
        *(u32 *)(iVar2 + 0x10) = 0x14;
    }
}

/* 0x002DAE60, 0x78 bytes. */
int func_002DAE60(u8 *param_1, int param_2)
{
    int iVar2;
    int iVar3;
    u8 * pbVar1;

    iVar2 = 0;
    iVar3 = 0;
    pbVar1 = param_1;
    do {
        iVar3 = iVar3 + 8;
        iVar2 = iVar2 + (u32)pbVar1[8] + (u32)pbVar1[9] + (u32)pbVar1[10] + (u32)pbVar1[0xB] +
                        (u32)pbVar1[0xC] + (u32)pbVar1[0xD] + (u32)pbVar1[0xE] + (u32)pbVar1[0xF];
        pbVar1 = pbVar1 + 8;
    } while (iVar3 < 0x50);
    if (param_2 != 0) {
        *(int *)param_1 = iVar2;
    }
    return *(int *)param_1 == iVar2;
}

/* 0x002DB3C0, 0x128 bytes. */
void func_002DB3C0(u32 *param_1)
{
    int bVar1;
    int iVar7;
    int iVar8;
    int lVar5;
    u32 * puVar6;
    int uVar2;
    u32 uVar3;
    int uVar4;

    iVar7 = 0;
    puVar6 = param_1;
    do {
        *puVar6 = 0;
        func_0011ED38(puVar6 + 10, 0, 0x19);
        puVar6[1] = 0;
        iVar7 = iVar7 + 1;
        puVar6[2] = 0;
        puVar6[3] = 0;
        puVar6[4] = 0;
        puVar6[5] = 0;
        puVar6[6] = 0;
        puVar6[7] = 0;
        puVar6[8] = 0;
        puVar6[9] = 0;
        puVar6 = puVar6 + 0x11;
    } while (iVar7 < 3);
    iVar7 = 0;
    do {
        uVar4 = func_001A1840(iVar7);
        lVar5 = func_003270F0(uVar4);
        if (lVar5 != 0) {
            *param_1 = 1;
            iVar8 = (int)uVar4;
            func_0011EB80(param_1 + 10, iVar8 + 0x125F, 0x19);
            param_1[4] = (u32)*(u8 *)(iVar8 + 0x121E);
            bVar1 = *(u8 *)(iVar8 + 0x121A);
            param_1[1] = (u32)bVar1;
            uVar3 = func_00327140(bVar1, *(u16 *)(iVar8 + 0x1208));
            param_1[2] = uVar3;
            uVar3 = func_00327170(*(u16 *)(iVar8 + 0x1208));
            param_1[3] = uVar3;
            uVar2 = *(u16 *)(iVar8 + 0x1200);
            param_1[5] = (u32)uVar2;
            param_1[5] = ((u32)uVar2 * 4 + (u32)uVar2) * 2;
            param_1[9] = (u32)*(u16 *)(iVar8 + 0x1202);
            param_1[6] = (u32)*(u8 *)(iVar8 + 0x121D);
            param_1[7] = (u32)*(u8 *)(iVar8 + 0x121B);
            param_1[8] = *(u32 *)(iVar8 + 0x11FC);
        }
        iVar7 = iVar7 + 1;
        param_1 = param_1 + 0x11;
    } while (iVar7 < 3);
}

/* 0x002DB580, 0x80 bytes. */
void func_002DB580(void)
{
    int lVar1;

    lVar1 = func_003BFDF0();
    if (lVar1 == 1) {
        *(u32 *)(g_00799A74) = func_003C0060();
        if (g_0045D5F8 == 6) {
            g_0045D5FC = 2;
        }
        else if (g_0045D5F8 == 5) {
            g_0045D5FC = 3;
        }
    }
    else if (lVar1 == 0) {
        g_0045D5FC = 4;
    }
}

/* 0x002DB600, 0x3C bytes. */
void func_002DB600(void)
{
    int uVar1;

    func_001A1BE0(*(u32 *)g_00799A74);
    uVar1 = func_00327C00();
    func_0030CE90(uVar1);
    func_001A1BE0(*(u32 *)g_00799A74);
}

/* 0x002DB640, 0x38 bytes, matching. */
void func_002DB640(void)
{
    int iVar1;

    iVar1 = func_003C0070();
    func_002DB600();
    *(u32 *)(iVar1 + 4) = 1;
    g_0045D5FC = 4;
}

/* 0x002DB750, 0xB0 bytes. */
int func_002DB750(void)
{
    int uVar1;

    uVar1 = 5;
    if (g_0045D5FC == 4) {
        uVar1 = func_002DB550();
    }
    else if (g_0045D5FC == 3) {
        func_002DB640();
    }
    else if (g_0045D5FC == 2) {
        func_002DB680();
    }
    else if (g_0045D5FC == 1) {
        func_002DB580();
    }
    else {
        if (g_0045D5FC != 0) {
            return 5;
        }
        func_002DB4F0();
    }
    return uVar1;
}

/* 0x002DB9F0, 0x94 bytes. */
int func_002DB9F0(void)
{
    u32 uVar1;

    uVar1 = 0;
    if (g_0045D5F4 == 3) {
        func_002DB880();
        uVar1 = 1;
    }
    else if (g_0045D5F4 == 2) {
        func_002DB900();
    }
    else if (g_0045D5F4 == 1) {
        func_002DB8A0();
    }
    else {
        if (g_0045D5F4 != 0) {
            return 0;
        }
        func_002DB800();
    }
    return uVar1;
}

/* 0x002DBAC0, 0x28 bytes. */
void func_002DBAC0(int param_1)
{
    if (param_1 == 0) {
        *(u32 *)(g_00799A70) = 8;
    }
    else {
        *(u32 *)(g_00799A70) = 9;
    }
}

/* 0x002DD0F0, 0x40 bytes. */
void func_002DD0F0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar3 = 3;
    g_0045D608 = 0x79A090;
    iVar1 = (int)g_0079A090;
    do {
        iVar2 = iVar1;
        iVar3 = iVar3 + -1;
        *(int *)(iVar2 + 0xDC) = iVar2 + 0xE0;
        iVar1 = iVar2 + 0xE0;
    } while (iVar3 != 0);
    *(u32 *)(iVar2 + 0x1BC) = 0;
}

/* 0x002DDCF0, 0x40 bytes. */
void func_002DDCF0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar3 = 3;
    g_0045D604 = 0x799D90;
    iVar1 = (int)g_00799D90;
    do {
        iVar2 = iVar1;
        iVar3 = iVar3 + -1;
        *(int *)(iVar2 + 0xBC) = iVar2 + 0xC0;
        iVar1 = iVar2 + 0xC0;
    } while (iVar3 != 0);
    *(u32 *)(iVar2 + 0x17C) = 0;
}

/* 0x002DFEE0, 0x28 bytes. */
void func_002DFEE0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442A20, param_1, param_3, param_5);
}

/* 0x002DFF10, 0x28 bytes. */
void func_002DFF10(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442A60, param_1, param_3, param_5);
}

/* 0x002DFF40, 0x28 bytes. */
void func_002DFF40(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442AA0, param_1, param_3, param_5);
}

/* 0x002DFF70, 0x28 bytes. */
void func_002DFF70(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442AE0, param_1, param_3, param_5);
}

/* 0x002DFFA0, 0x28 bytes. */
void func_002DFFA0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442B20, param_1, param_3, param_5);
}

/* 0x002DFFD0, 0x28 bytes. */
void func_002DFFD0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    func_002DF7C0(0x442B60, param_1, param_3, param_5);
}

/* 0x002E0540, 0x50 bytes. */
void func_002E0540(int param_1)
{
    int lVar1;

    *(u8 *)(param_1 + 0x69) = *(u8 *)(param_1 + 0x69) & 0xFE;
    lVar1 = func_002456C0(param_1, 0x442950, 0);
    if (lVar1 == 0) {
        *(u8 *)(param_1 + 0x69) = *(u8 *)(param_1 + 0x69) | 1;
    }
}

/* 0x002E1510, 0x90 bytes. */
void func_002E1510(int param_1, int param_2)
{
    int iVar5;
    int lVar4;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

    iVar5 = (int)param_1;
    *(u32 *)(iVar5 + 0xBC) = *(u32 *)(iVar5 + 0xBC) & 0xFFF8003F;
    *(u8 *)(iVar5 + 0x7D) = 2;
    if (param_2 == 0) {
        lVar4 = func_00240E20(*(u32 *)(iVar5 + 0x14));
        if (lVar4 == 0) {
            func_00204B60(param_1, 1);
        }
        else {
            iVar5 = *(int *)(iVar5 + 0x14);
            *(u32 *)(iVar5 + 0x13C) = 0;
            uVar3 = g_700000CC;
            uVar2 = g_700000C8;
            uVar1 = g_700000C4;
            *(u32 *)(iVar5 + 0x1D0) = g_700000C0;
            *(u32 *)(iVar5 + 0x1D4) = uVar1;
            *(u32 *)(iVar5 + 0x1D8) = uVar2;
            *(u32 *)(iVar5 + 0x1DC) = uVar3;
        }
    }
    else {
        func_00204B60(param_1, 2);
    }
}

/* 0x002E15A0, 0xF8 bytes. */
void func_002E15A0(int param_1)
{
    u8 * pbVar1;

    pbVar1 = (u8 *)func_001F14E0();
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)*pbVar1) {
        func_002E1510(param_1, 0);
    }
    else {
        g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
        if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[1]) {
            func_002E1510(param_1, 1);
        }
        else {
            g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
            if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[3]) {
                func_00238AE0(param_1, 0x3C);
            }
            else {
                func_00206080(param_1);
            }
        }
    }
}

/* 0x002E16A0, 0x60 bytes. */
void func_002E16A0(int param_1)
{
    int iVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

    *(u32 *)(param_1 + 0xBC) = *(u32 *)(param_1 + 0xBC) & 0xFFF8003F;
    *(u8 *)(param_1 + 0x7D) = 0;
    iVar1 = *(int *)(param_1 + 0x14);
    *(u32 *)(iVar1 + 0x13C) = 0;
    uVar4 = g_700000CC;
    uVar3 = g_700000C8;
    uVar2 = g_700000C4;
    *(u32 *)(iVar1 + 0x1D0) = g_700000C0;
    *(u32 *)(iVar1 + 0x1D4) = uVar2;
    *(u32 *)(iVar1 + 0x1D8) = uVar3;
    *(u32 *)(iVar1 + 0x1DC) = uVar4;
    if (*(int *)(param_1 + 8) != 0) {
        func_00204BB0();
    }
}

/* 0x002E3CD0, 0xC0 bytes. */
void func_002E3CD0(int param_1, int param_2)
{
    int iVar2;
    int iVar4;
    int lVar3;
    int uVar1;

    lVar3 = func_00194480(param_2, *(u8 *)(param_1 + 0x1E), *(u8 *)(param_1 + 0x1F));
    if (lVar3 != 0) {
        iVar4 = (int)lVar3;
        if (*(short *)(iVar4 + 4) != -1) {
            iVar2 = func_00194560();
            uVar1 = func_001F4870(*(u16 *)(iVar2 + (u32)*(u16 *)(iVar4 + 4) * 0xC));
            *(u8 *)(param_1 + 4) = uVar1;
        }
        *(u8 *)(param_1 + 0x1D) = *(u8 *)(iVar4 + 6) & 0x7F;
        *(char *)(param_1 + 0x1C) = (char)param_2;
        *(u8 *)(param_1 + 0x18) = *(u8 *)(param_1 + 0x18) & 0xFB | (*(u8 *)(iVar4 + 6) >> 7) << 2;
    }
}

/* 0x002E5C80, 0x98 bytes. */
void func_002E5C80(int param_1)
{
    int iVar1;

    if ((param_1 < 0xBA) && (-1 < param_1)) {
        g_0045CFB4 = (int)param_1;
        iVar1 = g_0045CFB4 * 4;
        if (((g_00413960 + 0x2))[iVar1] != 1) {
            func_002E8830();
        }
        if (((g_00413960 + 0x1))[iVar1] != 2) {
            func_002E6E40();
        }
        func_002E5ED0();
        if (g_00413960[iVar1] != 6) {
            func_002E52E0();
        }
    }
}

/* 0x002E5D20, 0x80 bytes. */
void func_002E5D20(void)
{
    int iVar1;

    iVar1 = g_0045CFB4 * 4;
    if (((g_00413960 + 0x2))[iVar1] != 1) {
        func_002E88F0();
    }
    if (((g_00413960 + 0x1))[iVar1] != 2) {
        func_002E74E0();
    }
    if (g_00413960[iVar1] != 6) {
        func_002E52F0();
    }
    g_0045CFB4 = 0xBA;
}

/* 0x002E5DA0, 0x68 bytes. */
void func_002E5DA0(int param_1)
{
    int iVar1;

    iVar1 = g_0045CFB4 * 4;
    if (((g_00413961 + 0x1))[iVar1] != 1) {
        func_002E8980();
    }
    if (g_00413961[iVar1] != 2) {
        func_002E7570(param_1);
    }
}

/* 0x002E5E10, 0xB8 bytes. */
void func_002E5E10(int param_1, int param_2)
{
    int iVar1;

    iVar1 = g_0045CFB4 * 4;
    if (((g_00413960 + 0x2))[iVar1] != 1) {
        func_002E94F0();
    }
    if (((g_00413960 + 0x1))[iVar1] != 2) {
        func_002E7FC0(param_1);
    }
    if ((param_2 == 0) && (g_00413960[iVar1] != 6)) {
        if ((*(u32 *)g_00669F60 & 2) == 0) {
            func_002E5300();
        }
        else {
            func_002E5810();
        }
    }
}

/* 0x002E5ED0, 0xA4 bytes. */
void func_002E5ED0(void)
{
    int iVar1;
    int iVar2;

    iVar1 = g_0045CFB4 * 4;
    if (((g_00413961 + 0x1))[iVar1] != 1) {
        iVar2 = 0;
        do {
            func_002E8980(0x40A00000);
            iVar2 = iVar2 + 1;
        } while (iVar2 < 0x80);
    }
    if (g_00413961[iVar1] != 2) {
        iVar1 = 0;
        do {
            func_002E7570(0x40A00000);
            iVar1 = iVar1 + 1;
        } while (iVar1 < 0x80);
    }
}

/* 0x002E6210, 0x50 bytes. */
void func_002E6210(void)
{
    func_002E6370(g_007A05A0);
    *(u32 *)(g_007A05B8) = func_001026D0(1, 0x3E, 0, 1, 0, 0, 0x442DF0, 0x4F);
}

/* 0x002E67B0, 0x44 bytes. */
void func_002E67B0(void)
{
    if ((*(u32 *)(g_00669F60 + 0x3C) < 0x5DC) && ((*(u32 *)g_00669F60 & 2) != 0)) {
        func_0019EBA0();
    }
}

/* 0x002EA950, 0x48 bytes. */
void func_002EA950(u32 *param_1)
{
    u32 * puVar1;
    u32 uVar2;

    param_1[2] = 0;
    uVar2 = 0;
    puVar1 = param_1;
    do {
        if (puVar1[4] != 0) {
            *(u32 *)(puVar1[4] + 0x2C) = 0;
            *(u32 *)(puVar1[4] + 0x38) = *(u32 *)(puVar1[4] + 0x38) | 8;
            puVar1[4] = 0;
        }
        uVar2 = uVar2 + 1;
        puVar1 = puVar1 + 1;
    } while (uVar2 < 4);
    *param_1 = 0;
}

/* 0x002EFB00, 0x38 bytes. */
int func_002EFB00(int param_1)
{
    int iVar1;

    iVar1 = func_0019FC20();
    return iVar1 + *(int *)(param_1 * 4 + iVar1 + 4) + 0x30;
}

/* 0x002EFB70, 0x3C bytes. */
void func_002EFB70(int param_1)
{
    func_002EFA70(param_1, 0x443790);
    *(u32 *)param_1 = 1;
    *(u8 *)(g_0076F615) = 1;
}

/* 0x002EFC40, 0x38 bytes. */
void func_002EFC40(int param_1)
{
    u32 uVar1;

    if (param_1 != 0) {
        *(u32 *)param_1 = 0;
        uVar1 = (u32)*(u8 *)((int)(u32 *)param_1 + 0x1E);
        if (uVar1 <= g_0045D674) {
            g_0045D674 = uVar1;
        }
        g_0045CFD8 = g_0045CFD8 + 1;
    }
}

/* 0x002F0090, 0x60 bytes. */
void func_002F0090(void)
{
    int iVar1;
    u32 uVar2;

    uVar2 = 0;
    iVar1 = (int)g_007A22C0;
    do {
        func_00118850(iVar1, 0x70);
        *(char *)(iVar1 + 0x1E) = (char)uVar2;
        *(u8 *)(iVar1 + 0x1C) = 2;
        uVar2 = uVar2 + 1;
        *(u8 *)(iVar1 + 0x1D) = 5;
        iVar1 = iVar1 + 0x70;
    } while (uVar2 < 8);
}

/* 0x002F03B0, 0x5C bytes. */
void func_002F03B0(void)
{
    int * piVar1;
    u32 uVar2;

    uVar2 = 0;
    piVar1 = (int *)0x7A22C0;
    do {
        if (*piVar1 != 0) {
            func_002EFC80(piVar1);
        }
        uVar2 = uVar2 + 1;
        piVar1 = piVar1 + 0x1C;
    } while (uVar2 < 8);
    g_70000D60 = 0;
}
