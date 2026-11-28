/*
 * gen_180000.c - small functions between 0x00180000 and 0x00200000, generated from Ghidra
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

extern u8 g_00730560[0x18];
extern u8 g_00730564[0x18];
extern u8 g_00730568[0x18];
extern u8 g_0073056C[0x18];
#define true 1
#define false 0

extern u8 g_00426230[0x34];
extern u8 g_0045D3E0[0x4];
extern u8 g_005BA690[0x10];
extern u8 g_005BA694[0x4];
extern u8 g_005BA6A0[0x4];
extern u8 g_005BA6A4[0x4];
extern u8 g_005BA7C8[0x4];
extern u8 g_005BA7CC[0x14];
extern u8 g_005BC39C[0x10];
extern u8 g_005BC3A0[0x5];
extern u8 g_005BD724[0x22];
extern u8 g_005BD740[0x4];
extern u8 g_00669D60[0x10];
extern u8 g_00669D7F[0x45];
extern u8 g_00669DB8[0x7C];
extern u8 g_00669DE8[0x4C];
extern u8 g_00669F60[0x4];
extern u8 g_00669F70[0x2C];
extern u8 g_00669F74[0x40];
extern u8 g_00669F98[0x4];
extern u8 g_00693968[0x1];
extern u8 g_00693970[0x10];
extern u8 g_006A1D49[0xB];
extern u8 g_006AA598[0x4];
extern u8 g_0072CEA0[0x10];
extern u8 g_0072CEC4[0x10];
extern u8 g_00732220[0x10];
extern u8 g_0073C790[0x4];
extern u8 g_0073DCA3[0x1];
extern u8 g_0073DF33[0x1];
extern int g_0045D2C0;   /* (small data) */
extern int g_0045D2FC;   /* (small data) */
extern int g_0045D324;   /* (small data) */
extern int g_0045D32C;   /* (small data) */
extern int g_0045D374;   /* (small data) */
extern int g_0045D384;   /* (small data) */
extern int g_0045D388;   /* (small data) */
extern int g_0045D38C;   /* (small data) */
extern int g_0045D390;   /* (small data) */
extern int g_0045D394;   /* (small data) */
extern int g_0045D398;   /* (small data) */
extern int g_0045D3D0;   /* (small data) */
extern int g_0045D470;   /* (small data) */
extern u32 g_70000150;   /* (scratchpad) */
extern u32 g_7000015C;   /* (scratchpad) */
extern u32 g_700001E0;   /* (scratchpad) */
extern u32 g_70000768;   /* (scratchpad) */
extern u32 g_7000088C;   /* (scratchpad) */
extern u32 g_70000B98;   /* (scratchpad) */
extern u32 g_70000D60;   /* (scratchpad) */

int func_00102680();
int func_001026D0();
int func_00102DB0();
int func_00102EC0();
int func_00103000();
int func_00104F60();
int func_001050F0();
int func_00105230();
int func_00107440();
int func_00118850();
int func_00118AC0();
int func_001477C0();
int func_00147BB0();
int func_00147BD0();
int func_00147F70();
int func_00149620();
int func_00149720();
int func_0014F0C0();
int func_0014F0E0();
int func_0014F970();
int func_0016A170();
int func_0016CB60();
int func_00177ED0();
int func_0017A920();
int func_0017AA80();
int func_0017AC50();
int func_00182E30();
int func_00182E70();
int func_00182F00();
int func_00182FF0();
int func_00183010();
int func_001839B0();
int func_00183A40();
int func_00184300();
int func_00184AE0();
int func_00186190();
int func_00186280();
int func_00186850();
int func_00186AD0();
int func_0018B810();
int func_0018B8A0();
int func_0018BCC0();
int func_0018BDA0();
int func_0018BE30();
int func_0018BF20();
int func_0018BFA0();
int func_0018C090();
int func_0018F6F0();
int func_00190590();
int func_00191570();
int func_00191830();
int func_00191DE0();
int func_001924E0();
int func_001929D0();
int func_001938B0();
int func_00194260();
int func_001942A0();
int func_00196E10();
int func_00196E80();
int func_00197010();
int func_00197080();
int func_0019A4F0();
int func_0019A6B0();
int func_0019AD90();
int func_0019B4F0();
int func_0019EDA0();
int func_0019EDC0();
int func_0019EDE0();
int func_0019EE00();
int func_0019EE20();
int func_0019EE70();
int func_0019EEC0();
int func_001AA2C0();
int func_001AC2A0();
int func_001ACA70();
int func_001B8C20();
int func_001B97E0();
int func_001B9A40();
int func_001BB7F0();
int func_001BC2C0();
int func_001BE4F0();
int func_001BE540();
int func_001BE590();
int func_001BE770();
int func_001C0250();
int func_001C0340();
int func_001C0580();
int func_001C5E20();
int func_001C7DB0();
int func_001C8CF0();
int func_001CB640();
int func_001CB720();
int func_001CB7F0();
int func_001CB9E0();
int func_001CBCE0();
int func_001DA7E0();
int func_001DA940();
int func_001DAD50();
int func_001DBA70();
int func_001DBB50();
int func_001DBC00();
int func_001DBCF0();
int func_001E0B40();
int func_001EAC90();
int func_001EBA60();
int func_001EBC70();
int func_001EBEE0();
int func_001EBFC0();
int func_001EC530();
int func_001ED100();
int func_001ED160();
int func_001ED580();
int func_001EDB50();
int func_001EE750();
int func_001EE9C0();
int func_001EEB70();
int func_001EF900();
int func_001F02F0();
int func_001F1910();
int func_001F4FF0();
int func_001F5900();
int func_001F5EB0();
int func_001F6070();
int func_001F71C0();
int func_001FA620();
int func_001FAA60();
int func_001FB6C0();
int func_001FC840();
int func_001FCB10();
int func_001FCCB0();
int func_001FCF10();
int func_001FD0B0();
int func_001FD5F0();
int func_001FD9A0();
int func_001FDD90();
int func_001FE650();
int func_001FEA10();
int func_001FF100();
int func_001FF140();
int func_001FF1B0();
int func_001FF230();
int func_00207CC0();
int func_00207CE0();
int func_00207D00();
int func_00207D40();
int func_00207D80();
int func_00207DA0();
int func_0020E140();
int func_0020E170();
int func_002181A0();
int func_00218350();
int func_002186E0();
int func_00229E30();
int func_0022FF10();
int func_0023EC30();
int func_0023ED20();
int func_00248EB0();
int func_0024A5A0();
int func_0024B940();
int func_00253300();
int func_0025CD80();
int func_0025E9A0();
int func_0025FF80();
int func_002622C0();
int func_00263BD0();
int func_002641B0();
int func_00264840();
int func_002696B0();
int func_00269740();
int func_002698A0();
int func_00269AF0();
int func_0026FC90();
int func_002A6D20();
int func_002A8030();
int func_002AD700();
int func_002AD920();
int func_002C4B70();
int func_002C4C00();
int func_002D6BF0();
int func_002D6D70();
int func_002D7080();
int func_002EFB00();
int func_002F00F0();
int func_002F27D0();
int func_0032E7B0();
int func_00347AC0();
int func_003498B0();
int func_0034A9D0();
int func_00354500();
int func_00355490();
int func_00355FE0();
int func_00356090();
int func_00357770();
int func_00357810();
int func_0035DCD0();
int func_0035DD60();
int func_0036D000();
int func_003DF430();
int func_003DF580();
int func_003E2330();
int func_003E23C0();
int func_003E5570();
int func_003E55F0();
int func_003E5690();
int func_003E5970();
int func_003E5D80();
int func_003E5E00();
int func_003E68D0();
int func_003E6C10();
int func_003E6C60();
int func_003E6CA0();
int func_00181F20(int param_1);
void func_00183050(int param_1);
void func_00183130(void);
int func_00183410(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_001849F0(void);
void func_00184DD0(void);
void func_00185210(void);
void func_00185390(void);
void func_001854C0(void);
void func_00187C90(u16 *param_1);
void func_00188740(int param_1);
int func_00192F50(int param_1, int param_2, int param_3);
void func_001C39A0(int param_1, int param_2);
void func_001C3A60(int param_1);
void func_001C4A00(int param_1, int param_2);
void func_001C4AC0(int param_1);
void func_001C4F60(int param_1, int param_2);
void func_001C4FF0(int param_1);
void func_001C5040(int param_1, int param_2);
void func_001C51A0(int param_1, int param_2);
void func_001C5F50(int *param_1);
void func_001C7620(void);
void func_001C7730(void);
void func_001C77D0(int param_1);
void func_001C7B80(void);
void func_001C7CE0(void);
void func_001CBBA0(void);
void func_001D0E60(int param_1);
void func_001D0F20(int param_1);
void func_001D14B0(int param_1, int param_2);
int func_001D1540(void);
void func_001D1980(int param_1);
void func_001D1B50(int param_1);
void func_001D6B90(void);
int func_001D6CB0(int param_1);
void func_001D75D0(void);
void func_001D7670(int param_1);
void func_001DA9A0(int param_1, int param_2);
int func_001DC490(int param_1, int param_2);
void func_001DC6E0(void);
void func_001DF170(void);
void func_001DF1C0(u32 *param_1, int param_2, int param_3);
void func_001E1380(int param_1);
void func_001E1480(int param_1, int param_2, int param_3, int param_4);
int func_001E17E0(int param_1);
int func_001E1930(int param_1);
int func_001E1970(int param_1);
void func_001E3010(void);
int func_001EBB40(int param_1, int param_2);
void func_001EBD10(int param_1);
void func_001EC180(int param_1);
void func_001EC2A0(int param_1);
void func_001EC620(int param_1);
int func_001EDE10();
int func_001EDFB0();
int func_001EE210(int param_1);
void func_001EE3B0(int param_1);
void func_001EE970(int param_1);
int func_001EF850(int param_1, int param_2, int param_3, int param_4);
int func_001F62C0(int param_1);
void func_001F6B60(int param_1);
void func_001FB440(void);
void func_001FB660(void);
void func_001FB8E0(void);
int func_001FBE60(int param_1, int param_2);
void func_001FCAA0(int param_1, int param_2);
void func_001FCAE0(void);
void func_001FCC50(void);
void func_001FD4B0(int param_1, int param_2, int param_3, int param_4);
void func_001FE330(u32 *param_1, int param_2);
void func_001FEE00(int param_1);
int func_001FF160(int param_1);
int func_001FF200(int param_1);
int func_001FF260(u16 *param_1, int param_2);
int func_001FF290(u16 *param_1, int param_2);
int func_001FF2C0(u16 *param_1, int param_2);

/* 0x00181F20, 0x1C4 bytes. */
int func_00181F20(int param_1)
{
    int iVar1;
    int * piVar2;
    u32 uVar3;

    uVar3 = 0;
    piVar2 = (int *)0x693970;
    do {
        func_00118AC0(piVar2, param_1, 0x88);
        if ((piVar2[0x20] & 1U) != 0) {
            if (*piVar2 == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = *piVar2 * 0x88 + 0x693970;
            }
            *piVar2 = iVar1;
            if (piVar2[1] == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = *(u32 *)g_005BA7C8 + piVar2[1] * 0x20;
            }
            piVar2[1] = iVar1;
            if (piVar2[2] == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = *(u32 *)g_005BA6A0 + piVar2[2] * 0x2C;
            }
            piVar2[2] = iVar1;
            if (piVar2[3] == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = *(u32 *)g_005BA6A0 + piVar2[3] * 0x2C;
            }
            piVar2[3] = iVar1;
            if (piVar2[6] == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = piVar2[6] * 0x88 + 0x693970;
            }
            piVar2[6] = iVar1;
            if (piVar2[7] == -1) {
                iVar1 = 0;
            }
            else {
                iVar1 = piVar2[7] * 0x88 + 0x693970;
            }
            piVar2[7] = iVar1;
        }
        uVar3 = uVar3 + 1;
        param_1 = param_1 + 0x88;
        piVar2 = piVar2 + 0x22;
    } while (uVar3 < 0x1AD);
    return param_1;
}

/* 0x00183050, 0xDC bytes. */
void func_00183050(int param_1)
{
    int bVar2;
    int iVar1;
    u8 * pbVar3;
    u8 * pbVar4;

    pbVar3 = (u8 *)param_1;
    iVar1 = *(int *)(*(u32 *)(g_005BA7CC + 0x10) + (u32)pbVar3[2] * 4);
    pbVar4 = (u8 *)(*(u32 *)g_005BA7CC + *(int *)(*(u32 *)g_005BA7CC + (u32)pbVar3[2] * 4 + 0xC));
    if (pbVar3[3] < 7) {
        func_0019A4F0(iVar1, 2);
    }
    if ((*(u8 *)(iVar1 + 1) & 3) == 0) {
        *pbVar4 = *pbVar4 & 0xFC;
    }
    else {
        if (pbVar4[5] == 0) {
            if ((*pbVar3 & 0x40) != 0) {
                func_002D6D70();
            }
            bVar2 = *pbVar4;
        }
        else {
            func_00182FF0(0x5BC3A0, param_1);
            bVar2 = *pbVar4;
        }
        *pbVar4 = bVar2 | 2;
    }
}

/* 0x00183130, 0x108 bytes. */
void func_00183130(void)
{
    u8 * pbVar1;
    u32 uVar2;

    if ((*(u8 *)g_005BC3A0 & 0x20) == 0) {
        while ((*(u8 *)(g_005BC3A0 + 0x4) & 8) == 0) {
            if ((*(u8 *)(g_005BC3A0 + 0x4) & 1) == 0) {
                pbVar1 = (u8 *)0x5BC2A0;
                uVar2 = 0;
                do {
                    if (pbVar1[3] == 1) break;
                    uVar2 = uVar2 + 1;
                    pbVar1 = pbVar1 + 4;
                } while (uVar2 < 0x40);
                if (0x3F < uVar2) {
                    return;
                }
                if ((*pbVar1 & 1) == 0) {
                    return;
                }
                func_00183010(pbVar1, 1);
                for (; uVar2 < 0x3F; uVar2 = uVar2 + 1) {
                    func_00118AC0(pbVar1, pbVar1 + 4, 4);
                    pbVar1 = pbVar1 + 4;
                }
                *pbVar1 = 0;
                pbVar1[3] = 0;
            }
            else {
                func_00182F00(0x5BC3A4);
            }
        }
    }
}

/* 0x00183410, 0x1D0 bytes. */
int func_00183410(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int bVar7;
    int iVar3;
    int lVar2;
    u8 * pbVar4;
    u32 uVar1;
    u32 uVar5;
    u32 uVar6;

    bVar7 = param_4;
    if (param_4 == 7) {
        param_4 = 2;
    }
    else if (param_5 != 0) {
        bVar7 = 6;
    }
    pbVar4 = (u8 *)0x5BC2A0;
    uVar6 = 0;
    do {
        if (((*pbVar4 & 1) == 0) || (pbVar4[3] < param_4)) break;
        uVar6 = uVar6 + 1;
        pbVar4 = pbVar4 + 4;
    } while (uVar6 < 0x40);
    if (uVar6 < 0x40) {
        iVar3 = (int)g_005BC39C;
        uVar5 = 0x3F;
        if (uVar6 < 0x3F) {
            do {
                func_00118AC0(iVar3, iVar3 + -4, 4);
                uVar5 = uVar5 - 1;
                iVar3 = iVar3 + -4;
            } while (uVar6 < uVar5);
        }
        *pbVar4 = 0;
        if (param_1 == 0) {
            *pbVar4 = *pbVar4 | 5;
        }
        else {
            *pbVar4 = *pbVar4 | 3;
        }
        uVar6 = (u32)bVar7;
        if (uVar6 == 7) {
            func_00182E70();
            *pbVar4 = *pbVar4 | 0x40;
        }
        else if (uVar6 == 8) {
            func_00182E30();
            *pbVar4 = *pbVar4 | 0x40;
        }
        pbVar4[1] = param_3;
        pbVar4[2] = param_2;
        pbVar4[3] = bVar7;
        if ((uVar6 - 7 < 2) && (lVar2 = func_0032E7B0(), *(u32 *)g_00669F70 != 7 && lVar2 == 0)) {
            func_0036D000();
        }
        uVar1 = 1;
    }
    else {
        uVar1 = 0;
    }
    return uVar1;
}

/* 0x001849F0, 0xE8 bytes. */
void func_001849F0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;

    iVar4 = 0;
    iVar2 = (int)g_00669D60;
    do {
        *(u32 *)(iVar2 + 0xA0) = 1;
        if ((iVar4 == 1) && ((*(u32 *)g_00669F60 & 2) == 0)) {
            *(u32 *)(iVar2 + 0xA0) = 0;
        }
        else {
            iVar3 = *(u32 *)g_005BA6A0 + (iVar4 + 0x24E) * 0x2C;
            iVar1 = func_002F27D0(*(u32 *)(iVar2 + 0x88));
            func_00118AC0(iVar3, *(u32 *)g_005BA6A0 + iVar1 * 0x2C, 0x2C);
            *(u16 *)(iVar2 + 200) = (u16)*(u8 *)(iVar3 + 6);
            *(int *)(iVar2 + 0x9C) = iVar4 + 0x24E;
            func_0019B4F0(iVar4, 0);
        }
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + 0x48;
    } while (iVar4 < 2);
}

/* 0x00184DD0, 0x1CC bytes. */
void func_00184DD0(void)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int uVar2;
    u32 uVar5;

    uVar2 = func_002EFB00(1);
    uVar2 = func_0019AD90(uVar2);
    uVar2 = func_00186280(uVar2);
    uVar2 = func_0019A6B0(uVar2);
    uVar2 = func_0018B810(uVar2);
    uVar2 = func_0018BCC0(uVar2);
    uVar2 = func_0018BE30(uVar2);
    iVar1 = func_0018BFA0(uVar2);
    uVar5 = 0;
    iVar4 = (int)g_005BA690;
    do {
        iVar3 = iVar1;
        func_00118AC0(iVar4 + 0x1C10, iVar3, 4);
        uVar5 = uVar5 + 1;
        iVar4 = iVar4 + 4;
        iVar1 = iVar3 + 4;
    } while (uVar5 < 0x40);
    func_00118AC0(0x5BC3A0, iVar3 + 4, 4);
    func_00118AC0(0x5BC3A4, iVar3 + 8, 4);
    uVar2 = func_0023EC30(iVar3 + 0xC);
    uVar2 = func_00356090(uVar2);
    uVar2 = func_00357810(uVar2);
    uVar2 = func_002C4B70(uVar2);
    func_00118AC0(0x5BD728, uVar2, 8);
    iVar1 = (int)uVar2;
    func_00118AC0(0x5BD730, iVar1 + 8, 4);
    func_00118AC0(0x5BD734, iVar1 + 0xC, 4);
    func_00118AC0(0x5BD738, iVar1 + 0x10, 4);
    func_00118AC0(0x5BD73C, iVar1 + 0x14, 4);
    *(u8 *)(g_005BD740) = *(u8 *)(iVar1 + 0x18);
    *(u8 *)(g_005BD740 + 0x1) = *(u8 *)(iVar1 + 0x19);
    *(u8 *)(g_005BD740 + 0x2) = *(u8 *)(iVar1 + 0x1A);
    *(u8 *)(g_005BD740 + 0x3) = *(u8 *)(iVar1 + 0x1B);
    *(u8 *)(g_0073DCA3) = *(u8 *)(g_0073DCA3) & 0xFB | (*(char *)(iVar1 + 0x1C) != 0) << 2;
    *(u8 *)(g_0073DF33) = *(u8 *)(g_0073DF33) & 0xFB | (*(char *)(iVar1 + 0x1D) != 0) << 2;
}

/* 0x00185210, 0xEC bytes. */
void func_00185210(void)
{
    int iVar1;
    u32 uVar2;

    if (*(u32 *)g_00669DB8 == 2) {
        if ((((*(u32 *)g_00669F70 == 7) || (*(u32 *)g_00669F70 == 4)) || (*(u32 *)g_00669F70 == 1)) ||
              ((*(u32 *)g_00669F70 == 3 || (*(u32 *)(g_00669F70 + 0x28) % 5 == 4)))) {
            uVar2 = 0;
            iVar1 = (int)g_005BA690;
            do {
                if (*(int *)(iVar1 + 0x14) != 0) {
                    func_00102EC0();
                    *(u32 *)(iVar1 + 0x14) = 0;
                }
                uVar2 = uVar2 + 1;
                iVar1 = iVar1 + 4;
            } while (uVar2 < 5);
        }
    }
    else if (*(u32 *)g_005BA6A4 != 0) {
        func_00102EC0();
        *(u32 *)(g_005BA6A4) = 0;
    }
}

/* 0x00185390, 0x128 bytes. */
void func_00185390(void)
{
    int iVar1;
    int iVar2;

    if (*(u32 *)g_00669DB8 == 2) {
        iVar1 = *(int *)((*(u32 *)g_00669F98 % 5) * 4 + 0x669DC0);
    }
    else {
        iVar1 = *(u32 *)(g_00669DB8 + 0x8);
    }
    func_00354500();
    func_003E5970();
    func_003E5D80();
    if (*(u32 *)g_00669DB8 == 2) {
        iVar2 = 0x54;
    }
    else {
        iVar2 = iVar1;
        if (*(u32 *)g_00669DB8 == 3) {
            iVar2 = 0x55;
        }
    }
    *(u32 *)(g_005BD724) = *(u32 *)(g_005BA694) + iVar2 * 100;
    func_0022FF10();
    func_001BC2C0();
    func_00184DD0();
    func_00347AC0();
    func_003E5570();
    func_001BB7F0(1);
    func_003E55F0();
    iVar2 = *(u32 *)g_00669DB8;
    func_00184300(*(u32 *)g_00669DB8);
    func_002D7080(iVar2, iVar1);
}

/* 0x001854C0, 0x7D8 bytes. */
void func_001854C0(void)
{
    int iVar1;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar2;
    int iVar6;
    int lVar4;
    u8 * pbVar5;
    u32 uVar10;
    u32 uVar3;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    iVar2 = *(u32 *)(g_00669D7F + 0x39);
    if (*(u32 *)(g_00669D7F + 0x39) == 2) {
        iVar13 = *(u32 *)(g_00669F74 + 0x24) % 5;
        iVar1 = *(int *)((*(u32 *)(g_00669F74 + 0x24) % 5) * 4 + 0x669DC0);
    }
    else {
        iVar13 = 0;
        iVar1 = *(u32 *)(g_00669D7F + 0x41);
    }
    func_00354500();
    func_003E5970();
    func_003E5D80();
    if (*(u32 *)(g_00669D7F + 0x39) == 2) {
        iVar12 = 0x54;
    }
    else {
        iVar12 = iVar1;
        if (*(u32 *)(g_00669D7F + 0x39) == 3) {
            iVar12 = 0x55;
        }
    }
    iVar12 = *(u32 *)g_005BA694 + iVar12 * 100;
    uVar3 = 0;
    uVar9 = (u32)*(u8 *)(iVar12 + 7);
    *(u32 *)(g_00669F74) = (u32)*(u8 *)(iVar12 + 7);
    *(u32 *)(g_005BD724) = iVar12;
    if (uVar9 != 0) {
        uVar8 = *(u32 *)g_00669F74 - 8;
        if (8 < uVar9) {
            iVar11 = (int)g_00669D60;
            do {
                iVar6 = iVar12 + uVar3;
                *(u8 *)(iVar11 + 0x248) = 0;
                uVar3 = uVar3 + 8;
                *(u8 *)(iVar11 + 0x24E) = *(u8 *)(iVar6 + 8);
                *(u8 *)(iVar11 + 0x249) = 0;
                *(u8 *)(iVar11 + 0x24F) = *(u8 *)(iVar6 + 9);
                *(u8 *)(iVar11 + 0x24A) = 0;
                *(u8 *)(iVar11 + 0x250) = *(u8 *)(iVar6 + 10);
                *(u8 *)(iVar11 + 0x24B) = 0;
                *(u8 *)(iVar11 + 0x251) = *(u8 *)(iVar6 + 0xB);
                *(u8 *)(iVar11 + 0x24C) = 0;
                *(u8 *)(iVar11 + 0x252) = *(u8 *)(iVar6 + 0xC);
                *(u8 *)(iVar11 + 0x24D) = 0;
                *(u8 *)(iVar11 + 0x253) = *(u8 *)(iVar6 + 0xD);
                *(u8 *)(iVar11 + 0x24E) = 0;
                *(u8 *)(iVar11 + 0x254) = *(u8 *)(iVar6 + 0xE);
                *(u8 *)(iVar11 + 0x24F) = 0;
                *(u8 *)(iVar11 + 0x255) = *(u8 *)(iVar6 + 0xF);
                iVar11 = iVar11 + 8;
            } while (uVar3 < uVar8);
        }
        if (uVar3 < uVar9) {
            iVar11 = uVar3 + 0x669D60;
            do {
                iVar6 = iVar12 + uVar3;
                *(u8 *)(iVar11 + 0x248) = 0;
                uVar3 = uVar3 + 1;
                *(u8 *)(iVar11 + 0x24E) = *(u8 *)(iVar6 + 8);
                iVar11 = iVar11 + 1;
            } while (uVar3 < uVar9);
        }
    }
    if (uVar3 < 3) {
        iVar11 = uVar3 + 0x669D60;
        do {
            uVar3 = uVar3 + 1;
            *(u8 *)(iVar11 + 0x248) = 1;
            iVar11 = iVar11 + 1;
        } while (uVar3 < 3);
    }
    *(u32 *)(g_005BD724 + 0x10) = 300;
    func_003E6C10();
    func_003E68D0();
    func_003E6C60();
    func_003E6CA0();
    *(u32 *)(g_005BD724 + 0x8) = 0;
    *(u32 *)(g_005BD724 + 0x4) = 0;
    *(u8 *)(g_005BD724 + 0x1C) = 0;
    *(u8 *)(g_005BD724 + 0x1D) = 0;
    *(u8 *)(g_005BD724 + 0x1E) = 0;
    *(u8 *)(g_005BD724 + 0x1F) = 0;
    *(u8 *)(g_005BD724 + 0x20) = 0;
    *(u8 *)(g_005BD724 + 0x21) = 0;
    *(u8 *)(g_00669F74 + 0x3D) = 0;
    *(u8 *)(g_00669F74 + 0x3E) = 0;
    *(u8 *)(g_00669F74 + 0x3F) = 0;
    *(u8 *)(g_0073DCA3) = *(u8 *)(g_0073DCA3) & 0xFB;
    *(u8 *)(g_0073DF33) = *(u8 *)(g_0073DF33) & 0xFB;
    if (iVar13 == 0) {
        uVar3 = 0;
        do {
            uVar8 = uVar3 + 1;
            uVar9 = uVar8 & 7;
            *(u8 *)(((int)uVar3 >> 3) + 0x669D70) = *(u8 *)(((int)uVar3 >> 3) + 0x669D70) & 0xFE;
            if (((int)uVar8 < 0) && (uVar9 != 0)) {
                uVar9 = uVar9 - 8;
            }
            uVar10 = uVar3 + 2;
            uVar7 = uVar10 & 7;
            *(u8 *)(((int)uVar8 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar8 >> 3) + 0x669D70) & ~(u8)(1 << (uVar9 & 0x1F));
            if (((int)uVar10 < 0) && (uVar7 != 0)) {
                uVar7 = uVar7 - 8;
            }
            uVar8 = uVar3 + 3;
            uVar9 = uVar8 & 7;
            *(u8 *)(((int)uVar10 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar10 >> 3) + 0x669D70) & ~(u8)(1 << (uVar7 & 0x1F));
            if (((int)uVar8 < 0) && (uVar9 != 0)) {
                uVar9 = uVar9 - 8;
            }
            uVar10 = uVar3 + 4;
            uVar7 = uVar10 & 7;
            *(u8 *)(((int)uVar8 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar8 >> 3) + 0x669D70) & ~(u8)(1 << (uVar9 & 0x1F));
            if (((int)uVar10 < 0) && (uVar7 != 0)) {
                uVar7 = uVar7 - 8;
            }
            uVar8 = uVar3 + 5;
            uVar9 = uVar8 & 7;
            *(u8 *)(((int)uVar10 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar10 >> 3) + 0x669D70) & ~(u8)(1 << (uVar7 & 0x1F));
            if (((int)uVar8 < 0) && (uVar9 != 0)) {
                uVar9 = uVar9 - 8;
            }
            uVar10 = uVar3 + 6;
            uVar7 = uVar10 & 7;
            *(u8 *)(((int)uVar8 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar8 >> 3) + 0x669D70) & ~(u8)(1 << (uVar9 & 0x1F));
            if (((int)uVar10 < 0) && (uVar7 != 0)) {
                uVar7 = uVar7 - 8;
            }
            uVar8 = uVar3 + 7;
            uVar9 = uVar8 & 7;
            *(u8 *)(((int)uVar10 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar10 >> 3) + 0x669D70) & ~(u8)(1 << (uVar7 & 0x1F));
            if (((int)uVar8 < 0) && (uVar9 != 0)) {
                uVar9 = uVar9 - 8;
            }
            uVar3 = uVar3 + 8;
            *(u8 *)(((int)uVar8 >> 3) + 0x669D70) =
                      *(u8 *)(((int)uVar8 >> 3) + 0x669D70) & ~(u8)(1 << (uVar9 & 0x1F));
        } while (uVar3 < 0x79);
        pbVar5 = (u8 *)(((int)uVar3 >> 3) + 0x669D70);
        *pbVar5 = *pbVar5 & 0xFE;
    }
    if ((iVar2 == 2) && (iVar13 % 5 == 0)) {
        *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 1;
        lVar4 = func_0019EDA0();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xFD;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 2;
        }
        lVar4 = func_0019EDC0();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xFB;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 4;
        }
        lVar4 = func_0019EDE0();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xF7;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 8;
        }
        lVar4 = func_0019EE00();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xEF;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 0x10;
        }
        lVar4 = func_0019EE20();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xDF;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 0x20;
        }
        lVar4 = func_0019EE70();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0xBF;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 0x40;
        }
        lVar4 = func_0019EEC0();
        if (lVar4 == 0) {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) & 0x7F;
        }
        else {
            *(u8 *)(g_00669D7F) = *(u8 *)(g_00669D7F) | 0x80;
        }
    }
    func_0018BF20();
    func_0018C090();
    func_0018B8A0();
    func_0022FF10();
    func_0023ED20();
    func_00355FE0();
    func_00357770();
    func_002C4C00();
    func_0018BDA0();
    func_003E5E00();
    *(u32 *)(g_005BD724 + 0x18) = func_00184AE0(iVar12, iVar2, iVar1);
    func_001BC2C0();
    func_001849F0();
    func_00347AC0();
    func_003E5690();
    func_00355490();
    func_00186190();
    func_003E5570();
    func_003E55F0();
    *(u32 *)(g_005BD724 + 0x14) = 1;
    func_00183A40();
    if (iVar13 == 0) {
        if (iVar2 != 3) {
            func_00184300(iVar2);
        }
        func_002D7080(iVar2, iVar1);
    }
}

/* 0x00187C90, 0x44 bytes. */
void func_00187C90(u16 *param_1)
{
    if ((*(u32 *)g_00669F60 & 0x10) == 0) {
        func_001839B0(*(u32 *)((u32)*param_1 * 4 + 0x5BC260));
    }
}

/* 0x00188740, 0x58 bytes. */
void func_00188740(int param_1)
{
    int sVar1;

    sVar1 = *(short *)(param_1 + 10);
    if (sVar1 != 2) {
        if (sVar1 == 1) {
            func_00186850();
        }
        else if (sVar1 == 0) {
            func_00186AD0();
        }
    }
}

/* 0x00192F50, 0x180 bytes. */
int func_00192F50(int param_1, int param_2, int param_3)
{
    int lVar3;
    u32 uVar1;
    int uVar2;

    uVar2 = 0;
    if (*(u32 *)g_00669DB8 == 2) {
        uVar1 = *(u32 *)((*(u32 *)g_00669F98 % 5) * 4 + 0x669DD4);
    }
    else {
        uVar1 = *(u32 *)(g_00669DB8 + 0x1C);
    }
    lVar3 = func_00194260(1, uVar1);
    if (lVar3 == 0) {
        lVar3 = func_00194260(2, uVar1);
        if (lVar3 == 0) {
            lVar3 = func_00194260(3, uVar1);
            if (lVar3 == 0) {
                lVar3 = func_00194260(5, uVar1);
                if (lVar3 == 0) {
                    lVar3 = func_00194260(6, uVar1);
                    if (lVar3 != 0) {
                        uVar2 = func_001929D0(param_1, param_2, param_3);
                    }
                }
                else {
                    uVar2 = func_001924E0(param_1, param_2, param_3);
                }
            }
            else {
                uVar2 = func_00191DE0(param_1, param_2, param_3);
            }
        }
        else {
            uVar2 = func_00191830(param_1, param_2, param_3);
        }
    }
    else {
        uVar2 = func_00191570(param_1, param_2, param_3);
    }
    return uVar2;
}

/* 0x001C39A0, 0xC0 bytes. */
void func_001C39A0(int param_1, int param_2)
{
    int iVar1;
    int * piVar2;

    func_001C51A0(param_1, param_2 + 0x20);
    if (*(int *)(param_2 + 0x2C4) != 0x30) {
        func_002A8030();
    }
    piVar2 = (int *)param_1;
    if (*piVar2 == param_2) {
        *piVar2 = *(int *)(param_2 + 0x14);
        if (*(int *)(param_2 + 0x14) != 0) {
            *(u32 *)(*(int *)(param_2 + 0x14) + 0x10) = 0;
        }
        if (piVar2[1] == param_2) {
            piVar2[1] = 0;
        }
    }
    else if (piVar2[1] == param_2) {
        iVar1 = *(int *)(param_2 + 0x10);
        piVar2[1] = iVar1;
        *(u32 *)(iVar1 + 0x14) = 0;
    }
    else {
        *(u32 *)(*(int *)(param_2 + 0x10) + 0x14) = *(u32 *)(param_2 + 0x14);
        *(u32 *)(*(int *)(param_2 + 0x14) + 0x10) = *(u32 *)(param_2 + 0x10);
    }
    func_001CB640(param_2);
}

/* 0x001C3A60, 0x4C bytes, matching. */
void func_001C3A60(int param_1)
{
    int iVar1;

    for (iVar1 = *(int *)param_1; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
        func_001C39A0(param_1, iVar1);
    }
}

/* 0x001C4A00, 0xC0 bytes. */
void func_001C4A00(int param_1, int param_2)
{
    int iVar1;
    int iVar2;

    func_001C51A0(param_1, param_2 + 0x30);
    if (*(int *)(param_2 + 0x2D4) != 0x30) {
        func_002A8030();
    }
    iVar2 = (int)param_1;
    if (*(int *)(iVar2 + 8) == param_2) {
        *(u32 *)(iVar2 + 8) = *(u32 *)(param_2 + 0x18);
        if (*(int *)(param_2 + 0x18) != 0) {
            *(u32 *)(*(int *)(param_2 + 0x18) + 0x14) = 0;
        }
        if (*(int *)(iVar2 + 0xC) == param_2) {
            *(u32 *)(iVar2 + 0xC) = 0;
        }
    }
    else if (*(int *)(iVar2 + 0xC) == param_2) {
        iVar1 = *(int *)(param_2 + 0x14);
        *(int *)(iVar2 + 0xC) = iVar1;
        *(u32 *)(iVar1 + 0x18) = 0;
    }
    else {
        *(u32 *)(*(int *)(param_2 + 0x14) + 0x18) = *(u32 *)(param_2 + 0x18);
        *(u32 *)(*(int *)(param_2 + 0x18) + 0x14) = *(u32 *)(param_2 + 0x14);
    }
    func_001CB720(param_2);
}

/* 0x001C4AC0, 0x4C bytes, matching. */
void func_001C4AC0(int param_1)
{
    int iVar1;

    for (iVar1 = *(int *)((int)param_1 + 8); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
        func_001C4A00(param_1, iVar1);
    }
}

/* 0x001C4F60, 0x88 bytes. */
void func_001C4F60(int param_1, int param_2)
{
    int iVar1;

    if (*(int *)(param_1 + 0x10) == param_2) {
        *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x1C);
        if (*(int *)(param_2 + 0x1C) != 0) {
            *(u32 *)(*(int *)(param_2 + 0x1C) + 0x18) = 0;
        }
        if (*(int *)(param_1 + 0x14) == param_2) {
            *(u32 *)(param_1 + 0x14) = 0;
        }
    }
    else if (*(int *)(param_1 + 0x14) == param_2) {
        iVar1 = *(int *)(param_2 + 0x18);
        *(int *)(param_1 + 0x14) = iVar1;
        *(u32 *)(iVar1 + 0x1C) = 0;
    }
    else {
        *(u32 *)(*(int *)(param_2 + 0x18) + 0x1C) = *(u32 *)(param_2 + 0x1C);
        *(u32 *)(*(int *)(param_2 + 0x1C) + 0x18) = *(u32 *)(param_2 + 0x18);
    }
    func_001CB7F0(param_2);
}

/* 0x001C4FF0, 0x4C bytes, matching. */
void func_001C4FF0(int param_1)
{
    int iVar1;

    for (iVar1 = *(int *)((int)param_1 + 0x10); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1C)) {
        func_001C4F60(param_1, iVar1);
    }
}

/* 0x001C5040, 0x158 bytes. */
void func_001C5040(int param_1, int param_2)
{
    int iVar1;
    int iVar2;

    *(u32 *)(param_2 + 0x260) = 0;
    *(u32 *)(param_2 + 0x264) = 0;
    if (*(int *)(param_1 + 0x1C) == 0) {
        *(int *)(param_1 + 0x18) = param_2;
        *(int *)(param_1 + 0x1C) = param_2;
        *(u8 *)(param_2 + 0x2AC) = *(u8 *)(param_2 + 0x2AC) & 0xFB | 4;
    }
    else {
        if ((*(u32 *)(param_1 + 0x34) & 0x100) == 0) {
            iVar1 = *(int *)(param_1 + 0x18);
            iVar2 = iVar1;
            if (iVar1 != 0) {
                do {
                    if ((*(u32 *)(param_2 + 0x270) & 0x10) == (*(u32 *)(iVar2 + 0x270) & 0x10)) break;
                    iVar2 = *(int *)(iVar2 + 0x264);
                } while (iVar2 != 0);
            }
            if (iVar2 != 0) {
                do {
                    if (*(int *)(param_2 + 0x27C) == *(int *)(iVar2 + 0x27C)) break;
                    iVar2 = *(int *)(iVar2 + 0x264);
                } while (iVar2 != 0);
            }
            if (iVar2 != 0) {
                do {
                    if ((*(u32 *)(param_2 + 0x270) & 0x3FF0000) == (*(u32 *)(iVar2 + 0x270) & 0x3FF0000))
                    break;
                    iVar2 = *(int *)(iVar2 + 0x264);
                } while (iVar2 != 0);
            }
        }
        else {
            iVar1 = *(int *)(param_1 + 0x18);
            for (iVar2 = iVar1; (iVar2 != 0 && ((*(u32 *)(iVar2 + 0x270) & 0x40000) == 0));
                    iVar2 = *(int *)(iVar2 + 0x264)) {
            }
        }
        if (iVar2 == 0) {
            *(int *)(*(int *)(param_1 + 0x1C) + 0x264) = param_2;
            *(u32 *)(param_2 + 0x260) = *(u32 *)(param_1 + 0x1C);
            *(int *)(param_1 + 0x1C) = param_2;
        }
        else if (iVar2 == iVar1) {
            *(int *)(iVar1 + 0x260) = param_2;
            *(u32 *)(param_2 + 0x264) = *(u32 *)(param_1 + 0x18);
            *(int *)(param_1 + 0x18) = param_2;
        }
        else {
            iVar1 = *(int *)(iVar2 + 0x260);
            *(int *)(iVar2 + 0x260) = param_2;
            *(int *)(param_2 + 0x264) = iVar2;
            *(int *)(param_2 + 0x260) = iVar1;
            *(int *)(iVar1 + 0x264) = param_2;
        }
    }
}

/* 0x001C51A0, 0x90 bytes. */
void func_001C51A0(int param_1, int param_2)
{
    int bVar2;
    int bVar3;
    int iVar1;

    bVar2 = param_2 == *(int *)(param_1 + 0x18);
    bVar3 = param_2 == *(int *)(param_1 + 0x1C);
    if ((bVar2) || (bVar3)) {
        if ((bVar2) && (bVar3)) {
            *(u32 *)(param_1 + 0x18) = 0;
            *(u32 *)(param_1 + 0x1C) = 0;
        }
        else if (bVar2) {
            iVar1 = *(int *)(param_2 + 0x264);
            *(int *)(param_1 + 0x18) = iVar1;
            *(u32 *)(iVar1 + 0x260) = 0;
        }
        else if (bVar3) {
            iVar1 = *(int *)(param_2 + 0x260);
            *(int *)(param_1 + 0x1C) = iVar1;
            *(u32 *)(iVar1 + 0x264) = 0;
        }
    }
    else {
        *(u32 *)(*(int *)(param_2 + 0x260) + 0x264) = *(u32 *)(param_2 + 0x264);
        *(u32 *)(*(int *)(param_2 + 0x264) + 0x260) = *(u32 *)(param_2 + 0x260);
    }
}

/* 0x001C5F50, 0xB4 bytes. */
void func_001C5F50(int *param_1)
{
    int iVar1;

    if ((param_1[0xE] & 0xcU) == 0) {
        for (iVar1 = *param_1; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x14)) {
            func_001C5E20(iVar1 + 0x20 + g_70000150 * 0x130);
        }
        for (iVar1 = param_1[2]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x18)) {
            func_001C5E20(iVar1 + 0x30 + g_70000150 * 0x130);
        }
    }
}

/* 0x001C7620, 0x10C bytes. */
void func_001C7620(void)
{
    u32 uVar1;

    g_0045D398 = 0;
    g_0045D394 = 0;
    g_0045D390 = 0;
    g_0045D38C = 0;
    g_0045D388 = 0;
    g_0045D384 = 0;
    g_0045D32C = 0;
    func_00103000(0);
    g_0045D38C = func_001026D0(1, 0x7EC, 0, 1, 0, 0, 0x425F20, 0x11FB);
    g_0045D388 = func_001026D0(1, 0x7ED, 0, 1, 0, 0, 0x425F20, 0x11FC);
    g_0045D384 = func_001026D0(1, 0x7EE, 0, 1, 0, 0, 0x425F20, 0x11FD);
    func_00103000(1);
    uVar1 = 0;
    do {
        if ((int)uVar1 < 0x3F) {
            *(u32 *)(uVar1 * 4 + 0x72C760) = 0;
        }
        uVar1 = uVar1 + 1;
    } while (uVar1 < 0x3F);
    func_001CB9E0();
    func_001CBCE0();
}

/* 0x001C7730, 0x9C bytes. */
void func_001C7730(void)
{
    int * piVar1;
    u32 uVar2;

    func_00103000(0);
    if (g_0045D38C != 0) {
        func_00102EC0();
        g_0045D38C = 0;
    }
    uVar2 = 0;
    piVar1 = (int *)0x72CEA0;
    do {
        if (*piVar1 != 0) {
            func_00102EC0();
            *piVar1 = 0;
        }
        uVar2 = uVar2 + 1;
        piVar1 = piVar1 + 1;
    } while (uVar2 < 4);
    func_00103000(1);
    if (g_0045D398 != 0) {
        func_00102EC0();
        g_0045D398 = 0;
    }
}

/* 0x001C77D0, 0x3B0 bytes. */
void func_001C77D0(int param_1)
{
    int iVar1;
    int iVar11;
    int iVar3;
    int iVar7;
    int iVar9;
    int lVar10;
    u32 uVar2;
    int uVar4;
    int uVar5;
    int uVar6;
    u32 uVar8;

    lVar10 = 0;
    if (g_0045D32C == 0) {
        *(u32 *)(g_0072CEA0) = 0;
        g_0045D324 = 0;
        *(u32 *)(g_0072CEA0 + 0x4) = 0;
        *(u32 *)(g_0072CEA0 + 0x8) = 0;
        *(u32 *)(g_0072CEA0 + 0xC) = 0;
        func_00103000(0);
        if (*(u32 *)g_00669DB8 != 3) {
            uVar8 = 9;
            iVar7 = (int)g_0072CEC4;
            do {
                if (uVar8 == 0xB) {
                    lVar10 = 1;
                }
                if ((lVar10 == 0) || ((*(u32 *)g_00669F60 & 2) != 0)) {
                    iVar1 = func_0035DD60(lVar10, uVar8 - 9 & 1);
                    uVar2 = func_001026D0(1, iVar1 + 0x84B, 0, param_1, 0, 0, 0x425F20, 0x1255);
                    *(u32 *)(iVar7 + -0x24) = uVar2;
                }
                uVar8 = uVar8 + 1;
                iVar7 = iVar7 + 4;
            } while (uVar8 < 0xD);
        }
        func_00103000(1);
        if (*(u32 *)g_00669DB8 == 2) {
            g_0045D398 = func_001026D0(1, 0x7F0, 0, param_1, 0, 0, 0x425F20, 0x127A);
            g_0045D394 = 0;
            g_0045D390 = 0;
        }
        else {
            if (*(u32 *)g_00669DB8 == 2) {
                iVar7 = 0x54;
            }
            else {
                iVar7 = *(u32 *)(g_00669DB8 + 0x8);
                if (*(u32 *)g_00669DB8 == 3) {
                    iVar7 = 0x55;
                }
            }
            uVar8 = (u32)*(u16 *)(*(u32 *)g_005BA694 + iVar7 * 100 + 2);
            if ((*(u32 *)g_00669F60 & 2) == 0) {
                iVar11 = uVar8 + 0x7F1;
                iVar1 = func_00102680(1, iVar11);
                iVar7 = iVar1 + 0x7FF;
                if (iVar7 < 0) {
                    iVar7 = iVar1 + 0xFFE;
                }
            }
            else {
                iVar11 = uVar8 + 0x80E;
                iVar1 = func_00102680(1, iVar11);
                iVar7 = iVar1 + 0x7FF;
                if (iVar7 < 0) {
                    iVar7 = iVar1 + 0xFFE;
                }
                g_0045D324 = 1;
            }
            iVar9 = (iVar7 >> 0xB) * 0x800;
            uVar4 = func_003E23C0(*(u32 *)(g_00669DB8 + 0x30));
            iVar1 = func_00102680(1, uVar4);
            iVar7 = iVar1 + 0x7FF;
            if (iVar7 < 0) {
                iVar7 = iVar1 + 0xFFE;
            }
            iVar7 = (iVar7 >> 0xB) * 0x800;
            if ((*(u32 *)g_00669F60 & 2) == 0) {
                uVar5 = 0xDAE;
                iVar1 = 0;
            }
            else {
                uVar5 = func_003E23C0(*(u32 *)(g_00669DB8 + 0x78));
                iVar3 = func_00102680(1, uVar5);
                iVar1 = iVar3 + 0x7FF;
                if (iVar1 < 0) {
                    iVar1 = iVar3 + 0xFFE;
                }
                iVar1 = (iVar1 >> 0xB) << 0xB;
            }
            uVar6 = func_00102DB0(0x40, iVar1 + iVar9 + iVar7);
            g_0045D398 = (int)uVar6;
            g_0045D394 = g_0045D398 + iVar9;
            if (iVar1 != 0) {
                g_0045D390 = g_0045D394 + iVar7;
            }
            func_001026D0(1, iVar11, uVar6, param_1, 0, 0, 0x425F20, 0x12B8);
            func_001026D0(1, uVar4, g_0045D394, param_1, 0, 0, 0x425F20, 0x12B9);
            if (iVar1 == 0) {
                g_0045D390 = 0;
            }
            else {
                func_001026D0(1, uVar5, g_0045D390, param_1, 0, 0, 0x425F20, 0x12BD);
            }
        }
    }
    func_001C0580();
}

/* 0x001C7B80, 0x160 bytes. */
void func_001C7B80(void)
{
    int iVar1;
    int lVar2;
    int uVar3;
    u32 uVar4;

    func_001C0340();
    if (g_0045D32C == 0) {
        uVar4 = 0xD;
        do {
            if ((0xC < (int)uVar4) && ((int)uVar4 < 0x11)) {
                *(u32 *)(uVar4 * 4 + 0x72C82C) = 0;
            }
            uVar4 = uVar4 + 1;
        } while (uVar4 < 0x11);
        func_001CBBA0();
        uVar4 = 0;
        do {
            if ((int)uVar4 < 0x18B) {
                *(u32 *)(uVar4 * 4 + 0x72C870) = 0;
            }
            uVar4 = uVar4 + 1;
        } while (uVar4 < 0x18B);
        func_001C0250();
        iVar1 = g_0045D394;
        if (g_0045D394 != 0) {
            lVar2 = func_003E2330(*(u32 *)g_00669DE8);
            if (lVar2 < 0x18B) {
                *(int *)((int)lVar2 * 4 + 0x72C870) = iVar1;
            }
            uVar3 = func_003E2330(*(u32 *)g_00669DE8);
            func_001C8CF0(uVar3);
            g_0045D394 = 0;
        }
        iVar1 = g_0045D390;
        if (g_0045D390 != 0) {
            lVar2 = func_003E2330(*(u32 *)(g_00669DE8 + 0x48));
            if (lVar2 < 0x18B) {
                *(int *)((int)lVar2 * 4 + 0x72C870) = iVar1;
            }
            uVar3 = func_003E2330(*(u32 *)(g_00669DE8 + 0x48));
            func_001C8CF0(uVar3);
            g_0045D390 = 0;
        }
        g_0045D32C = 1;
    }
}

/* 0x001C7CE0, 0xC8 bytes. */
void func_001C7CE0(void)
{
    int * piVar1;
    u32 uVar2;

    func_00103000(0);
    uVar2 = 0;
    piVar1 = (int *)0x72CEA0;
    do {
        if (*piVar1 != 0) {
            func_00102EC0();
            *piVar1 = 0;
        }
        uVar2 = uVar2 + 1;
        piVar1 = piVar1 + 1;
    } while (uVar2 < 4);
    func_00103000(1);
    if (g_0045D398 != 0) {
        func_00102EC0();
        g_0045D398 = 0;
    }
    g_0045D394 = 0;
    uVar2 = 0;
    g_0045D390 = 0;
    do {
        if ((int)uVar2 < 0x18B) {
            *(u32 *)(uVar2 * 4 + 0x72C870) = 0;
        }
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0x18B);
    g_0045D32C = 0;
}

/* 0x001CBBA0, 0x134 bytes. */
void func_001CBBA0(void)
{
    int iVar1;
    int iVar3;
    u32 uVar2;

    func_00103000(0);
    if ((*(u32 *)g_00669F60 & 2) == 0) {
        if (*(u32 *)g_0072CEA0 != 0) {
            func_00107440(*(u32 *)g_0072CEA0, *(u32 *)(g_00426230 + 0x30) << 5, 0);
        }
        if (*(u32 *)(g_0072CEA0 + 0x4) != 0) {
            func_00107440(*(u32 *)(g_0072CEA0 + 0x4), *(u32 *)(g_00426230 + 0x2C) << 5, 0);
        }
    }
    uVar2 = 9;
    iVar3 = (int)g_0072CEC4;
    do {
        if (*(int *)(iVar3 + -0x24) != 0) {
            iVar1 = 0x169;
            if ((int)uVar2 < 0x11) {
                iVar1 = *(int *)(g_00426230 + uVar2 * 4);
            }
            func_00107440(*(int *)(iVar3 + -0x24), iVar1 << 5, 0);
            func_00102EC0(*(u32 *)(iVar3 + -0x24));
            *(u32 *)(iVar3 + -0x24) = 0;
        }
        uVar2 = uVar2 + 1;
        iVar3 = iVar3 + 4;
    } while (uVar2 < 0xD);
    uVar2 = 0xD;
    do {
        if ((0xC < (int)uVar2) && ((int)uVar2 < 0x11)) {
            *(u32 *)(uVar2 * 4 + 0x72C82C) = 0;
        }
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0x11);
    func_00103000(1);
}

/* 0x001D0E60, 0xB8 bytes. */
void func_001D0E60(int param_1)
{
    int iVar2;
    int uVar1;

    if (*(u32 *)g_00669DB8 != 4) {
        iVar2 = (int)param_1;
        if (*(u8 *)(iVar2 + 0x14E) < 2) {
            func_002181A0(*(u8 *)(iVar2 + 0x14E), *(u8 *)(iVar2 + 0x182));
            func_002696B0(*(u8 *)(iVar2 + 0x14E));
            if (*(u8 *)(iVar2 + 0x14E) < 2) {
                uVar1 = *(u8 *)((u32)*(u8 *)(iVar2 + 0x14E) * 0x48 + 0x669E2A);
                func_0016CB60(param_1, uVar1, 1, 0xFF, 0x28);
                func_0016CB60(param_1, uVar1, 0, 1, 0x3C);
            }
        }
    }
}

/* 0x001D0F20, 0xAC bytes. */
void func_001D0F20(int param_1)
{
    int iVar1;
    int iVar2;
    u32 uVar3;

    if (*(u8 *)(param_1 + 0x14E) < 2) {
        func_00218350();
        func_00229E30();
        uVar3 = 0;
        iVar2 = 0;
        do {
            iVar1 = *(int *)(iVar2 + (u32)*(u8 *)(param_1 + 0x14E) * 8 + 0x72C750);
            if (iVar1 != 0) {
                *(u32 *)(iVar1 + 0x34) = *(u32 *)(iVar1 + 0x34) | 0x800;
                *(u32 *)(iVar2 + (u32)*(u8 *)(param_1 + 0x14E) * 8 + 0x72C750) = 0;
            }
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + 4;
        } while (uVar3 < 2);
        g_0045D374 = 0;
        func_00269740(*(u8 *)(param_1 + 0x14E));
    }
}

/* 0x001D14B0, 0x90 bytes. */
void func_001D14B0(int param_1, int param_2)
{
    int iVar1;
    int iVar2;

    *(u16 *)((int)param_1 + 0x176) = 0x5DC;
    iVar1 = *(short *)((int)param_1 + 0x178) * 0xC0;
    iVar2 = *(short *)(param_2 + 0x178) * 0xC0 + 0x6A3A30;
    if (*(int *)(iVar1 + 0x6A3A38) != iVar2) {
        *(u32 *)(iVar1 + 0x6A3AEC) = *(u32 *)(iVar1 + 0x6A3AEC) & 0xFFFFFFFD;
    }
    *(int *)(iVar1 + 0x6A3A38) = iVar2;
    func_00253300(8, param_1);
}

/* 0x001D1540, 0xC4 bytes. */
int func_001D1540(void)
{
    int bVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    int * piVar2;
    u32 uVar6;

    uVar6 = 0;
    iVar4 = 0;
    do {
        if ((*(u32 *)(iVar4 + 0x6A9668) & 1) != 0) {
            bVar1 = false;
            iVar5 = 0;
            iVar3 = (int)g_00669D60;
            piVar2 = (int *)0x6AA59C;
            do {
                if (((*(int *)(iVar3 + 0xA0) != 0) && (*piVar2 != 0)) && (*piVar2 == iVar4 + 0x6A95B0)) {
                    bVar1 = true;
                    break;
                }
                iVar5 = iVar5 + 1;
                iVar3 = iVar3 + 0x48;
                piVar2 = piVar2 + 1;
            } while (iVar5 < 2);
            if (!bVar1) {
                return iVar4 + 0x6A95B0;
            }
        }
        uVar6 = uVar6 + 1;
        iVar4 = iVar4 + 0xC0;
        if (0xE < uVar6) {
            return 0;
        }
    } while( true );
}

/* 0x001D1980, 0xB8 bytes. */
void func_001D1980(int param_1)
{
    int iVar2;
    int iVar3;
    int uVar1;

    iVar2 = g_0045D2FC + 0x4030;
    uVar1 = func_00177ED0();
    iVar3 = (int)param_1;
    func_001ACA70(uVar1, iVar2, iVar3 + 0x90, iVar3 + 0x70, param_1);
    if (*(u8 *)(iVar3 + 0x14E) < 2) {
        func_002F00F0(*(u8 *)(iVar3 + 0x14E), 4);
    }
    if ((*(u8 *)(iVar3 + 0x14E) < 2) &&
          (iVar2 = *(short *)(iVar3 + 0x178) * 0xC0,
          *(short *)(iVar2 + 0x6A3AB8) < *(short *)(iVar2 + 0x6A3AB6))) {
        func_002A6D20(*(u8 *)(iVar3 + 0x14E), 0x23B);
    }
}

/* 0x001D1B50, 0x1B8 bytes. */
void func_001D1B50(int param_1)
{
    int bVar1;
    int iVar6;
    int iVar9;
    int lVar4;
    int * piVar7;
    u32 uVar2;
    u32 uVar3;
    int uVar5;
    int uVar8;

    if ((*(u32 *)g_00669F60 & 0x14000008) == 0) {
        iVar9 = (int)param_1;
        uVar2 = *(u32 *)(*(short *)(iVar9 + 0x178) * 0xC0 + 0x6A3AE8);
        if ((uVar2 & 0xC) != 0) {
            bVar1 = (uVar2 & 4) == 0;
            piVar7 = (int *)((u32)bVar1 * 4 + 0x6AA5D0);
            if (*piVar7 == 0x1AD) {
                lVar4 = func_001B97E0(bVar1);
                if (lVar4 == 0) {
                    return;
                }
            }
            else {
                *(u32 *)((u32)bVar1 * 4 + 0x6AA5C8) = 0x5DC;
            }
            iVar6 = *piVar7 * 0x88;
            *(u8 *)(iVar6 + 0x6939EA) = 0;
            *(u32 *)(iVar6 + 0x6939F4) = *(u32 *)(iVar6 + 0x6939F4) | 0x101;
            if (*(int *)(iVar6 + 0x693988) != 0) {
                func_001ED160(iVar6 + 0x693970, *(int *)(iVar6 + 0x693988), 0);
                *(u32 *)(iVar6 + 0x693988) = 0;
                *(u32 *)(iVar6 + 0x6939F4) = *(u32 *)(iVar6 + 0x6939F4) | 0x10;
            }
            *(u32 *)(iVar6 + 0x6939A8) = 0;
            *(u32 *)(iVar6 + 0x6939AC) = 0;
            *(u32 *)(iVar6 + 0x6939F4) = *(u32 *)(iVar6 + 0x6939F4) | 0x10;
            uVar3 = func_0035DCD0(bVar1);
            *(u32 *)(iVar6 + 0x69398C) = uVar3;
            *(u32 *)(iVar6 + 0x6939F4) = *(u32 *)(iVar6 + 0x6939F4) | 0x10;
            if (*(int *)(iVar9 + 0x11C) != 0) {
                if (*(u8 *)(iVar9 + 0x14E) < 2) {
                    uVar8 = 0x200;
                }
                else {
                    uVar8 = 0;
                }
                g_70000D60 = 0;
                uVar5 = func_0016A170(param_1, 0);
                func_001C7DB0(200, uVar5, uVar8);
            }
        }
    }
}

/* 0x001D6B90, 0x38 bytes. */
void func_001D6B90(void)
{
    func_002D6BF0();
    *(u32 *)(g_00669F60) = *(u32 *)(g_00669F60) & 0xEFFFFFFF;
}

/* 0x001D6CB0, 0x30 bytes. */
int func_001D6CB0(int param_1)
{
    u32 uVar1;

    uVar1 = 0x1F;
    do {
        if ((param_1 & 1 << (uVar1 & 0x1F)) != 0) break;
        uVar1 = uVar1 - 1;
    } while (-1 < (int)uVar1);
    return uVar1 + 1;
}

/* 0x001D75D0, 0xA0 bytes. */
void func_001D75D0(void)
{
    int iVar1;

    iVar1 = *(int *)g_0045D3E0 * 0x240 + 0x730570;
    func_0017AC50(iVar1);
    g_0045D470 = 2;
    if (*(u32 *)g_0073C790 == 0xB6) {
        func_001938B0(1, iVar1);
    }
    else if (*(int *)g_0045D3E0 == 0) {
        func_001938B0(2, iVar1);
    }
    else if (*(int *)g_0045D3E0 == 1) {
        func_001938B0(3, iVar1);
    }
}

/* 0x001D7670, 0x78 bytes. */
void func_001D7670(int param_1)
{
    if (*(u32 *)g_0073C790 == 0xB6) {
        func_0017A920();
    }
    else {
        func_0017AA80(param_1, *(int *)g_0045D3E0);
    }
    g_0045D3D0 = g_0045D2C0;
    g_0045D2C0 = (int)param_1;
    func_002186E0(g_00730560, g_00730564, g_00730568, g_0073056C);
}

/* 0x001DA9A0, 0x3A4 bytes. */
void func_001DA9A0(int param_1, int param_2)
{
    int bVar1;
    int bVar11;
    int bVar7;
    int bVar9;
    int iVar10;
    int iVar13;
    int iVar4;
    int iVar8;
    int * piVar12;
    u32 * puVar5;
    u32 uVar2;
    u32 uVar3;
    u32 uVar6;

    puVar5 = (u32 *)param_1;
    uVar2 = puVar5[1];
    func_00118850(param_2, 0x174);
    iVar4 = 0;
    iVar13 = *(int *)g_0045D3E0 * 0x174 + 0x730A20;
    piVar12 = (int *)(*(int *)g_0045D3E0 * 0x174 + 0x730A84);
    do {
        iVar8 = *piVar12;
        iVar4 = iVar4 + 8;
        *piVar12 = iVar8 + 1;
        *(u32 *)(iVar13 + iVar8 * 4 + 0x24) = 0x1478;
        iVar8 = *piVar12;
        iVar10 = iVar8 + 1;
        *piVar12 = iVar10;
        iVar8 = iVar13 + iVar8 * 4;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
        *piVar12 = iVar10;
        *(u32 *)(iVar8 + 0x24) = 0x1478;
    } while (iVar4 < 0x10);
    *(u32 *)((*(int *)g_0045D3E0) * 0x174 + 0x730A40) = 0;
    *(u32 *)((*(int *)g_0045D3E0) * 0x174 + 0x730A84) = 0;
    puVar5[0x13] = 0x1478;
    if ((*puVar5 & 1) != 0) {
        uVar6 = puVar5[1];
        puVar5[2] = uVar6;
        puVar5[3] = uVar6 + *(u8 *)(uVar6 + *(u8 *)(uVar6 + 6) + 7) + 7;
        puVar5[4] = puVar5[2] + 7;
        puVar5[5] = puVar5[2] + (u32)*(u8 *)(puVar5[2] + 6) + 8;
        uVar6 = puVar5[2];
        bVar1 = *(u8 *)(uVar6 + 4);
        while (uVar3 = (u32)bVar1, uVar3 != 0xFF) {
            bVar11 = true;
            bVar7 = false;
            if ((uVar3 < 9) && ((1 << (uVar3 & 0x1F) & 0x121U) != 0)) {
                bVar7 = bVar11;
            }
            bVar9 = bVar11;
            if (!bVar7) {
                bVar7 = false;
                if (uVar3 == 3) {
                    bVar7 = *(char *)(uVar6 + 5) == 0;
                }
                if (!bVar7) {
                    bVar9 = false;
                }
            }
            if (!bVar9) {
                bVar7 = false;
                if (uVar3 == 4) {
                    bVar7 = *(char *)(uVar6 + 5) == 5;
                }
                if ((!bVar7) && (bVar7 = false, uVar3 == 4)) {
                    bVar7 = *(char *)(uVar6 + 5) == 1;
                }
                if (!bVar7) {
                    bVar11 = false;
                }
            }
            if (bVar11) {
                func_001DA7E0(param_1);
            }
            bVar7 = false;
            if (*(char *)(puVar5[2] + 4) == 0) {
                bVar7 = *(char *)(puVar5[2] + 5) == 0;
            }
            if ((bVar7) && (uVar6 = puVar5[0x13], uVar6 != 0x1478)) {
                iVar13 = *(int *)g_0045D3E0 * 0x174;
                iVar4 = *(int *)(iVar13 + 0x730A84);
                *(int *)(iVar13 + 0x730A84) = iVar4 + 1;
                *(u32 *)(iVar13 + iVar4 * 4 + 0x730A44) = uVar6;
                puVar5[0x13] = 0x1478;
            }
            uVar6 = puVar5[1] + *(int *)puVar5[2];
            puVar5[2] = uVar6;
            puVar5[3] = uVar6 + *(u8 *)(uVar6 + *(u8 *)(uVar6 + 6) + 7) + 7;
            puVar5[4] = puVar5[2] + 7;
            puVar5[5] = puVar5[2] + (u32)*(u8 *)(puVar5[2] + 6) + 8;
            uVar6 = puVar5[2];
            bVar1 = *(u8 *)(uVar6 + 4);
        }
        uVar6 = puVar5[0x13];
        if (uVar6 != 0x1478) {
            iVar13 = *(int *)g_0045D3E0 * 0x174;
            iVar4 = *(int *)(iVar13 + 0x730A84);
            *(int *)(iVar13 + 0x730A84) = iVar4 + 1;
            *(u32 *)(iVar4 * 4 + iVar13 + 0x730A44) = uVar6;
        }
        func_001DA940(param_1);
        func_001DAD50(param_1, uVar2);
        *puVar5 = *puVar5 | 0x10;
        *(u32 *)((*(int *)g_0045D3E0) * 0x174 + 0x730A40) = 0;
        *(u32 *)((*(int *)g_0045D3E0) * 0x174 + 0x730A84) = 0;
    }
}

/* 0x001DC490, 0x1C0 bytes. */
int func_001DC490(int param_1, int param_2)
{
    int bVar1;
    int iVar4;
    int iVar5;
    int lVar2;
    int lVar3;

    param_2 = param_2 & 0xFFFF;
    if (param_2 == 0x3C) {
        lVar2 = func_001BE4F0();
    }
    else if (param_2 - 0x3D < 3) {
        lVar2 = func_001BE770();
    }
    else if (*(int *)(param_2 * 0x150 + 0x6CE038) == 0) {
        lVar2 = func_001BE4F0();
    }
    else {
        lVar2 = func_001BE540();
    }
    iVar4 = param_2 * 0x150;
    lVar3 = func_0020E140();
    if ((lVar3 != 0) || (lVar3 = func_0020E170(), lVar3 != 0)) {
        lVar2 = func_001BE590();
    }
    if (lVar2 == 0) {
        lVar2 = 0;
    }
    else {
        iVar5 = (int)lVar2;
        if (param_2 - 0x3D < 3) {
            *(u32 *)(iVar5 + 0x208) = *(u32 *)(iVar5 + 0x1F0);
            func_00196E10(lVar2);
            bVar1 = *(u8 *)(iVar5 + 0x20C);
        }
        else {
            if (*(int *)(iVar4 + 0x6CE038) == 0) {
                func_00149620(lVar2, iVar4 + 0x6CE000, 0);
            }
            else {
                func_00149620(lVar2, iVar4 + 0x6CE000, iVar4 + 0x6CE030);
            }
            bVar1 = *(u8 *)(iVar5 + 0x20C);
        }
        *(u8 *)(iVar5 + 0x20C) = bVar1 & 0xFE | 1;
        func_00149720(lVar2);
        *(u8 *)(iVar5 + 0x20C) = *(u8 *)(iVar5 + 0x20C) & 0xFB | 4;
    }
    return lVar2;
}

/* 0x001DC6E0, 0x2BC bytes. */
void func_001DC6E0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;

    iVar1 = *(u32 *)g_0045D3E0 * 0x38;
    iVar6 = 0;
    if (0 < *(int *)(iVar1 + 0x730E14)) {
        iVar5 = 0;
        iVar7 = 0;
        iVar4 = 0;
        iVar3 = 0;
        iVar2 = 0;
        do {
            func_001477C0(*(int *)(iVar1 + 0x730DE4) + iVar5);
            func_00147BB0(*(int *)(*(u32 *)g_0045D3E0 * 0x38 + 0x730DE8) + iVar7);
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DE0) + iVar4) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DF0) + iVar4) = 0;
            *(u16 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E00) + iVar3) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DF4) + iVar4) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DEC) + iVar4) = 0;
            *(u16 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DF8) + iVar3) = 0x40;
            *(u8 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730DFC) + iVar6) = 0;
            func_00118850(*(int *)(*(u32 *)g_0045D3E0 * 0x38 + 0x730E10) + iVar2, 8);
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + 0x20;
            iVar7 = iVar7 + 0x10;
            iVar3 = iVar3 + 2;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E04) + iVar4) = 0;
            iVar4 = iVar4 + 4;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E08) + iVar2 + 4) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E08) + iVar2) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E0C) + iVar2 + 4) = 0;
            *(u32 *)(*(int *)((*(u32 *)(g_0045D3E0)) * 0x38 + 0x730E0C) + iVar2) = 0;
            iVar1 = *(u32 *)g_0045D3E0 * 0x38;
            iVar2 = iVar2 + 8;
        } while (iVar6 < *(int *)(iVar1 + 0x730E14));
    }
    func_001DBB50();
    func_001DBC00();
    func_001DBCF0();
}
/* MISSING ['0x45d3e0'] */

/* 0x001DF170, 0x48 bytes. */
void func_001DF170(void)
{
    int iVar2;
    u32 * puVar1;

    iVar2 = 0;
    puVar1 = (u32 *)0x730E50;
    do {
        *puVar1 = 0xFFFFFFFF;
        iVar2 = iVar2 + 8;
        puVar1[1] = 0xFFFFFFFF;
        puVar1[2] = 0xFFFFFFFF;
        puVar1[3] = 0xFFFFFFFF;
        puVar1[4] = 0xFFFFFFFF;
        puVar1[5] = 0xFFFFFFFF;
        puVar1[6] = 0xFFFFFFFF;
        puVar1[7] = 0xFFFFFFFF;
        puVar1 = puVar1 + 8;
    } while (iVar2 < 0x20);
}

/* 0x001DF1C0, 0x168 bytes. */
void func_001DF1C0(u32 *param_1, int param_2, int param_3)
{
    int bVar1;
    int iVar2;
    u32 * puVar4;
    u32 uVar3;

    if ((*param_1 & 0x10) == 0) {
        uVar3 = 1 << (param_2 & 0x1F);
        iVar2 = *(int *)g_0045D3E0 * 0x174;
        if ((uVar3 & *(u32 *)(iVar2 + 0x730A8C)) == 0) {
            *(u32 *)(iVar2 + 0x730A8C) = *(u32 *)(iVar2 + 0x730A8C) | uVar3;
            *(int *)((param_2 & 0xFFFF) * 4 + iVar2 + 0x730A90) = (int)param_3;
        }
    }
    else {
        iVar2 = *(int *)g_0045D3E0 * 0x38;
        if ((int)(param_2 & 0xFFFF) < *(int *)(iVar2 + 0x730E14)) {
            bVar1 = *(int *)(*(int *)(iVar2 + 0x730DE0) + (param_2 & 0xFFFF) * 4) != 0;
        }
        else {
            bVar1 = false;
        }
        if (bVar1) {
            iVar2 = *(int *)(iVar2 + 0x730DE8) + (param_2 & 0xFFFF) * 0x10;
            func_00147BB0(iVar2);
            func_00147BD0(param_3, iVar2);
            iVar2 = (param_2 & 0xFFFF) * 4;
            *(u32 *)(*(int *)((*(int *)g_0045D3E0) * 0x38 + 0x730DF4) + iVar2) = 0;
            puVar4 = (u32 *)(*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730E04) + iVar2);
            *puVar4 = *puVar4 & 0xFFFFFFDF;
        }
    }
}

/* 0x001E1380, 0xF4 bytes. */
void func_001E1380(int param_1)
{
    int iVar3;
    int * piVar1;
    int uVar2;

    piVar1 = (int *)func_001DBA70();
    if (piVar1 != (int *)0) {
        uVar2 = func_002AD700(*(u8 *)((int)piVar1 + 0x16));
        func_002AD920((u32)*(u16 *)(*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DF8) + (param_1 & 0xFFFF) * 2)
                                  * 0x150 + 0x6CDF60,uVar2);
        func_0014F0C0(*(u32 *)(*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DE0) + (param_1 & 0xFFFF) * 4));
        iVar3 = 0;
        do {
            if (*piVar1 != 0) {
                func_0014F970();
            }
            iVar3 = iVar3 + 1;
            piVar1 = piVar1 + 1;
        } while (iVar3 < 5);
    }
}

/* 0x001E1480, 0xAC bytes. */
void func_001E1480(int param_1, int param_2, int param_3, int param_4)
{
    func_00147F70((u32)*(u16 *)
                                            (*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DF8) + ((u32)param_1 & 0xFFFF) * 2) *
                              0x150 + 0x6CDF60, param_3);
    func_0014F0E0(param_2, param_4);
    func_001E0B40(param_1, param_4);
}

/* 0x001E17E0, 0x78 bytes. */
int func_001E17E0(int param_1)
{
    int bVar1;
    int * piVar3;
    u32 uVar2;

    piVar3 = (int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DE0);
    if ((int)(param_1 & 0xFFFF) < *(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730E14)) {
        bVar1 = *(int *)(*piVar3 + (param_1 & 0xFFFF) * 4) != 0;
    }
    else {
        bVar1 = false;
    }
    if (bVar1) {
        uVar2 = *(u32 *)(*piVar3 + (param_1 & 0xFFFF) * 4);
    }
    else {
        uVar2 = 0;
    }
    return uVar2;
}

/* 0x001E1930, 0x34 bytes. */
int func_001E1930(int param_1)
{
    return *(u16 *)(*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DF8) + (param_1 & 0xFFFF) * 2);
}

/* 0x001E1970, 0x34 bytes. */
int func_001E1970(int param_1)
{
    return *(u32 *)(*(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DF0) + (param_1 & 0xFFFF) * 4);
}

/* 0x001E3010, 0x240 bytes. */
void func_001E3010(void)
{
    int bVar1;
    int bVar5;
    int iVar2;
    int * piVar4;
    int * piVar8;
    u32 * puVar9;
    u32 uVar3;
    u32 uVar6;
    u32 uVar7;

    piVar4 = (int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DE0);
    iVar2 = *(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730E14);
    uVar7 = 0;
    if (0 < iVar2) {
        do {
            if ((int)uVar7 < iVar2) {
                bVar1 = *(int *)(*piVar4 + uVar7 * 4) != 0;
            }
            else {
                bVar1 = false;
            }
            if (bVar1) {
                bVar5 = 0;
                iVar2 = *(int *)(*piVar4 + uVar7 * 4);
                *(u8 *)(iVar2 + 0x20C) = *(u8 *)(iVar2 + 0x20C) & 0xFE;
                *(u32 *)(iVar2 + 0x1E8) = 0;
                do {
                    *(u8 *)(uVar7 + *(int *)((*(int *)g_0045D3E0) * 0x38 + 0x730DFC)) = bVar5;
                    piVar4 = (int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DE0);
                    puVar9 = (u32 *)(uVar7 * 8 +
                                                      piVar4[*(u8 *)(uVar7 + *(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DFC)) + 10]);
                    uVar3 = *puVar9;
                    uVar6 = 0;
                    if (uVar3 != 0) {
                        do {
                            piVar8 = (int *)(puVar9[1] + uVar6 * 0x10);
                            if ((int)uVar7 < *(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730E14)) {
                                bVar1 = *(int *)(uVar7 * 4 + *piVar4) != 0;
                            }
                            else {
                                bVar1 = false;
                            }
                            if ((bVar1) && (uVar6 < uVar3)) {
                                bVar1 = *piVar8 != 0;
                            }
                            else {
                                bVar1 = false;
                            }
                            if (bVar1) {
                                if ((char)piVar8[3] == 0) {
                                    iVar2 = *piVar8;
                                    *(u32 *)(iVar2 + 0x160) = 0;
                                    *(u8 *)(iVar2 + 0x168) = *(u8 *)(iVar2 + 0x168) & 0xFE;
                                }
                                else {
                                    iVar2 = *piVar8;
                                    *(u32 *)(iVar2 + 0x1E8) = 0;
                                    *(u8 *)(iVar2 + 0x20C) = *(u8 *)(iVar2 + 0x20C) & 0xFE;
                                }
                            }
                            uVar6 = uVar6 + 1 & 0xFFFF;
                            piVar4 = (int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DE0);
                            puVar9 = (u32 *)(uVar7 * 8 +
                                                              piVar4[*(u8 *)(uVar7 + *(int *)(*(int *)g_0045D3E0 * 0x38 + 0x730DFC)) +
                                                                            10]);
                            uVar3 = *puVar9;
                        } while (uVar6 < uVar3);
                    }
                    bVar5 = bVar5 + 1;
                } while (bVar5 < 2);
            }
            iVar2 = piVar4[0xD];
            uVar7 = uVar7 + 1 & 0xFFFF;
        } while ((int)uVar7 < iVar2);
    }
    func_001DBB50();
    func_00196E80();
}

/* 0x001EBB40, 0xDC bytes. */
int func_001EBB40(int param_1, int param_2)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar3 = (int)param_1;
    if (((param_2 != 0) || ((*(u32 *)(iVar3 + 0x80) & 0x20000) != 0)) ||
          (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 0x10) % 10 == 7)) {
        iVar1 = *(int *)(iVar3 + 0x18);
        iVar2 = func_001EDB50(param_1);
        if (iVar2 != iVar1) {
            if (iVar1 != 0) {
                func_001ED160(param_1, iVar1, 0);
            }
            *(int *)(iVar3 + 0x18) = iVar2;
            *(u32 *)(iVar3 + 0x84) = *(u32 *)(iVar3 + 0x84) | 0x10;
        }
        if (iVar2 != 0) {
            return 1;
        }
        *(u8 *)(iVar3 + 0x7A) = 0;
    }
    return 0;
}

/* 0x001EBD10, 0x1D0 bytes. */
void func_001EBD10(int param_1)
{
    int iVar1;
    int iVar4;
    int lVar3;
    u32 uVar2;

    iVar4 = (int)param_1;
    iVar1 = *(int *)(iVar4 + 0x18);
    uVar2 = *(u32 *)(iVar1 + 0x80);
    if ((uVar2 & 0x8000) == 0) {
        if ((uVar2 & 0x20000) != 0) {
            *(u8 *)(iVar4 + 0x7A) = 1;
            func_001ED160(param_1, iVar1, 0);
            return;
        }
    }
    else if ((uVar2 & 0x10000) != 0) {
        *(u8 *)(iVar4 + 0x7A) = 1;
        func_001ED160(param_1, iVar1, 0);
        return;
    }
    lVar3 = func_001F02F0(param_1);
    if (lVar3 == 0) {
        *(u8 *)(iVar4 + 0x7A) = 0;
        func_001ED160(param_1, iVar1, 0);
        *(u32 *)(iVar4 + 0x18) = 0;
        *(u32 *)(iVar4 + 0x84) = *(u32 *)(iVar4 + 0x84) | 0x10;
    }
    else {
        lVar3 = func_001EF900(param_1, iVar1);
        if (lVar3 == 0) {
            if ((*(char *)(iVar4 + 0x7D) == 3) || (*(char *)(iVar4 + 0x7D) == 2)) {
                *(u32 *)(iVar4 + 0x18) = 0;
                *(u32 *)(iVar4 + 0x84) = *(u32 *)(iVar4 + 0x84) | 0x10;
                *(u8 *)(iVar4 + 0x7A) = 0;
            }
            else {
                *(u8 *)(iVar4 + 0x7A) = 1;
            }
            func_001ED160(param_1, iVar1, 0);
        }
        else {
            lVar3 = func_001EAC90(param_1, iVar1);
            if (((lVar3 != 0) &&
                    (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 0x10) % 100 < 0x32))
                  && ((*(u32 *)(iVar1 + 0x80) & 0xC000) == 0)) {
                if (*(int *)(iVar1 + 0x18) != 0) {
                    func_001ED160(iVar1, *(int *)(iVar1 + 0x18), 0);
                }
                *(int *)(iVar1 + 0x18) = iVar4;
                *(u32 *)(iVar1 + 0x84) = *(u32 *)(iVar1 + 0x84) | 0x10;
                func_001ED160(iVar1, param_1, 1);
            }
        }
    }
}

/* 0x001EC180, 0x84 bytes. */
void func_001EC180(int param_1)
{
    int cVar1;

    cVar1 = *(char *)(param_1 + 0x7A);
    if (cVar1 == 3) {
        func_001EBA60(param_1, 0);
    }
    else if (cVar1 == 2) {
        func_001EBC70();
    }
    else if (cVar1 == 1) {
        func_001EBEE0(param_1, 0);
    }
    else if (cVar1 == 0) {
        func_001EBFC0(param_1, 0);
    }
}

/* 0x001EC2A0, 0xD4 bytes. */
void func_001EC2A0(int param_1)
{
    int bVar6;
    int iVar1;
    int iVar5;
    int lVar3;
    unsigned long long * puVar4;
    u32 uVar2;

    iVar5 = (int)param_1;
    if ((*(u32 *)(iVar5 + 0x80) & 0x1800) == 0) {
        lVar3 = func_001ED580();
        if (lVar3 == 0) {
            func_001EE9C0(param_1, 0);
        }
    }
    else {
        iVar1 = *(int *)(iVar5 + 0x1C);
        if (iVar1 != 0) {
            uVar2 = *(u32 *)(iVar1 + 0x80);
            bVar6 = false;
            if (((uVar2 & 1) != 0) && ((uVar2 & 0x8C40002) == 0)) {
                bVar6 = true;
            }
            if (bVar6) {
                if ((uVar2 & 0x20000) == 0) {
                    puVar4 = (unsigned long long *)(iVar1 + 0x28);
                }
                else {
                    puVar4 = (unsigned long long *)(iVar1 + 0x30);
                }
                *(unsigned long long *)(iVar5 + 0x38) = *puVar4;
                *(u32 *)(iVar5 + 0x84) = *(u32 *)(iVar5 + 0x84) | 0x10;
                return;
            }
        }
        func_001EE9C0(param_1, 0);
    }
}

/* 0x001EC620, 0x30 bytes, matching. */
void func_001EC620(int param_1)
{
    func_001EC530();
    func_001EC180(param_1);
    *(u32 *)((int)param_1 + 0x68) = 0;
}

/* 0x001EE210, 0x190 bytes. */
int func_001EE210(int param_1)
{
    int bVar3;
    int cVar1;
    int iVar2;
    int iVar5;
    u32 uVar4;
    u32 uVar6;

    cVar1 = *(char *)(param_1 + 0x79);
    uVar6 = 0;
    if (*(u32 *)g_006AA598 != 0) {
        iVar5 = (int)g_00693970;
        do {
            iVar2 = *(int *)(iVar5 + 0x16C10);
            bVar3 = false;
            if (((*(u32 *)(iVar2 + 0x80) & 1) != 0) && ((*(u32 *)(iVar2 + 0x80) & 0x8C40002) == 0)) {
                bVar3 = true;
            }
            if ((bVar3) && (cVar1 != *(char *)(iVar2 + 0x79))) {
                if (((*(u32 *)(iVar2 + 0x84) & 2) == 0) && (*(char *)(iVar2 + 0x7A) != 3)) {
                    bVar3 = true;
                }
                else {
                    bVar3 = false;
                }
                if (bVar3) {
                    return iVar2;
                }
            }
            uVar6 = uVar6 + 1;
            iVar5 = iVar5 + 4;
        } while (uVar6 < *(u32 *)g_006AA598);
    }
    uVar6 = 0;
    do {
        iVar5 = func_0034A9D0(uVar6);
        if (iVar5 != 0) {
            uVar4 = *(u32 *)(iVar5 + 0x80) & 1;
            if (((uVar4 != 0) && (uVar4 != 0 && (*(u32 *)(iVar5 + 0x80) & 0x8C40002) == 0)) &&
                  (cVar1 != *(char *)(iVar5 + 0x79))) {
                if (((*(u32 *)(iVar5 + 0x84) & 2) == 0) && (*(char *)(iVar5 + 0x7A) != 3)) {
                    bVar3 = true;
                }
                else {
                    bVar3 = false;
                }
                if (bVar3) {
                    return iVar5;
                }
            }
        }
        uVar6 = uVar6 + 1;
        if (0xF < uVar6) {
            return 0;
        }
    } while( true );
}

/* 0x001EE3B0, 0xF0 bytes. */
void func_001EE3B0(int param_1)
{
    int iVar2;
    int iVar3;
    int * piVar4;
    u32 uVar1;

    iVar3 = (int)param_1;
    if ((*(u32 *)(iVar3 + 0x80) & 0x400000) == 0) {
        func_001F1910();
        if ((*(u32 *)(iVar3 + 0x80) & 0x20000) != 0) {
            func_001B9A40(param_1);
        }
        uVar1 = *(u32 *)(iVar3 + 0x80);
        if ((uVar1 & 8) == 0) {
            if ((uVar1 & 0x200000) == 0) {
                piVar4 = (int *)((u32)*(u8 *)(iVar3 + 0x79) * 4 + 0x6AA5BC);
                iVar2 = *piVar4;
                if (0 < iVar2) {
                    *piVar4 = iVar2 + -1;
                }
            }
            *(u32 *)(iVar3 + 0x84) = 0;
            *(u32 *)(iVar3 + 0x80) = 0;
        }
        else {
            *(u32 *)(iVar3 + 0x80) = uVar1 | 6;
        }
        if (*(int *)(iVar3 + 0x18) != 0) {
            func_001ED160(param_1, *(int *)(iVar3 + 0x18), 0);
            *(u32 *)(iVar3 + 0x18) = 0;
            *(u32 *)(iVar3 + 0x84) = *(u32 *)(iVar3 + 0x84) | 0x10;
        }
    }
    else {
        *(u32 *)(iVar3 + 0x80) = *(u32 *)(iVar3 + 0x80) | 6;
        func_001EEB70();
    }
}

/* 0x001EE970, 0x44 bytes. */
void func_001EE970(int param_1)
{
    if (((*(u32 *)(g_006A1D49 + 0x7) & 1) != 0) && (param_1 == *(char *)g_006A1D49)) {
        func_001EE750();
    }
}

/* 0x001EF850, 0xA8 bytes. */
int func_001EF850(int param_1, int param_2, int param_3, int param_4)
{
    int bVar1;
    int lVar3;
    int uVar2;

    lVar3 = func_00190590(param_2, 0x20);
    if (lVar3 == 0) {
        bVar1 = false;
    }
    else {
        lVar3 = func_00190590(param_3, 0x20);
        if ((lVar3 == 0) || (lVar3 = func_00190590(param_4, 0x20), lVar3 == 0)) {
            bVar1 = false;
        }
        else {
            uVar2 = func_0018F6F0(param_2, param_4, *(u32 *)(param_1 + 0x70));
            bVar1 = uVar2 < 4;
        }
    }
    return bVar1;
}

/* 0x001F62C0, 0xDC bytes. */
int func_001F62C0(int param_1)
{
    int cVar1;
    int iVar5;
    int lVar3;
    u32 uVar2;
    int uVar4;

    iVar5 = (int)param_1;
    lVar3 = func_001FF1B0(*(u16 *)(iVar5 + 0x54));
    if (lVar3 == 0) {
        lVar3 = func_001FF200(*(u16 *)(iVar5 + 0x54));
        if (lVar3 != 0) {
            *(u8 *)(iVar5 + 0x68) = 0xC;
        }
        func_001F5900(param_1);
        uVar4 = func_001F6070();
        func_001F5EB0(param_1, uVar4);
        uVar2 = 1;
    }
    else {
        cVar1 = func_001FF100(*(u16 *)(iVar5 + 0x54), 10);
        if (cVar1 == 28) {
            *(u8 *)(iVar5 + 0x68) = 0xF;
        }
        else if (cVar1 == '#') {
            *(u8 *)(iVar5 + 0x68) = 0xD;
        }
        else if (cVar1 == '@') {
            *(u8 *)(iVar5 + 0x68) = 0xE;
        }
        else {
            *(u8 *)(iVar5 + 0x68) = 0x10;
        }
        uVar2 = 0;
        *(u8 *)(iVar5 + 0x69) = *(u8 *)(iVar5 + 0x69) | 7;
    }
    return uVar2;
}

/* 0x001F6B60, 0x134 bytes. */
void func_001F6B60(int param_1)
{
    int cVar3;
    int iVar4;
    int iVar5;
    u16 * puVar8;
    int uVar1;
    u32 uVar2;
    u32 uVar6;
    u32 uVar7;

    uVar1 = *(u16 *)((int)param_1 + 0x54);
    iVar4 = func_001FF140(uVar1);
    cVar3 = func_001FF100(uVar1, 9);
    puVar8 = (u16 *)(iVar4 + 0x30);
    if (*(u32 *)g_00669DB8 != 3) {
        if ((*(u32 *)g_00669DB8 == 2) && (uVar7 = 0, *(short *)(iVar4 + 4) != 0)) {
            do {
                uVar2 = func_00207D80(*puVar8);
                iVar5 = func_00207DA0(*puVar8);
                uVar6 = 0;
                if (uVar2 != 0) {
                    do {
                        if (*(u8 *)(iVar5 + uVar6) < 4) {
                            func_00197010(param_1);
                            break;
                        }
                        uVar6 = uVar6 + 1;
                    } while (uVar6 < uVar2);
                }
                if (uVar6 < uVar2) break;
                uVar7 = uVar7 + 1;
                puVar8 = (u16 *)func_001FF230(puVar8);
            } while (uVar7 < *(u16 *)(iVar4 + 4));
        }
        if ((cVar3 != 0) && (cVar3 != 3)) {
            func_00197080(param_1);
        }
    }
}

/* 0x001FB440, 0x218 bytes. */
void func_001FB440(void)
{
    int bVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    u32 uVar2;

    iVar7 = (int)g_00732220;
    bVar1 = (*(u32 *)g_00669F60 & 2) != 0;
    func_001B8C20(bVar1);
    if (!bVar1) {
        func_001AC2A0(*(u32 *)g_00669DE8);
    }
    iVar6 = 0;
    iVar4 = iVar7;
    do {
        uVar2 = func_00102DB0(0x10, 0x1E240);
        *(u32 *)(iVar7 + 0x2E0) = uVar2;
        if (bVar1) {
            iVar5 = 0;
            iVar3 = 0;
            do {
                func_0025FF80(*(int *)(iVar7 + 0x2E0) + iVar3 + 0x195E0, iVar5);
                iVar5 = iVar5 + 1;
                iVar3 = iVar3 + 0xC40;
            } while (iVar5 < 2);
            func_002622C0(*(int *)(iVar7 + 0x2E0) + 0x18AF0, iVar4);
        }
        else {
            func_0025CD80(*(int *)(iVar7 + 0x2E0) + 0x195E0, 0);
            func_0025CD80(*(int *)(iVar7 + 0x2E0) + 0x1A220, 1);
            func_0025E9A0(*(int *)(iVar7 + 0x2E0) + 0x1A220, 1);
            func_002622C0(*(int *)(iVar7 + 0x2E0) + 0x18AF0, iVar4);
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 4;
        iVar4 = iVar4 + 0x170;
    } while (iVar6 < 2);
    func_001FA620();
    func_00248EB0();
    func_0024B940();
    func_0024A5A0();
    iVar7 = 0;
    do {
        if (bVar1) {
            func_002641B0(iVar7, 0);
            func_00269AF0(iVar7);
        }
        else {
            func_00263BD0(iVar7, 0);
            func_002698A0(iVar7);
        }
        func_0026FC90(iVar7);
        func_001FAA60(iVar7);
        iVar7 = iVar7 + 1;
    } while (iVar7 < 2);
    func_001F71C0();
    if ((*(u32 *)g_00669F60 & 2) == 0) {
        func_00264840(1);
    }
    func_003DF430();
}

/* 0x001FB660, 0x54 bytes. */
void func_001FB660(void)
{
    int iVar1;
    int iVar2;

    iVar2 = 0;
    iVar1 = (int)g_00732220;
    do {
        func_00102EC0(*(u32 *)(iVar1 + 0x2E0));
        iVar2 = iVar2 + 1;
        *(u32 *)(iVar1 + 0x2E0) = 0;
        iVar1 = iVar1 + 4;
    } while (iVar2 < 2);
    *(u8 *)(g_00693968) = 0;
}

/* 0x001FB8E0, 0xF0 bytes. */
void func_001FB8E0(void)
{
    int lVar2;
    u32 uVar1;
    int uVar3;

    uVar1 = *(u32 *)(g_70000150 * 4 + 0x732500);
    if (((*(u32 *)g_00669F60 & 0x200) == 0) && (lVar2 = func_0032E7B0(), lVar2 == 0)) {
        func_001FB6C0();
        uVar3 = func_001050F0();
        *(unsigned long long *)((int)uVar3 + 0x10) = 0x5000D;
        *(unsigned long long *)((int)uVar3 + 0x18) = 0x48;
        func_00105230(uVar3, 0);
        func_00104F60(uVar1, 0x1E240, 0);
        if ((*(u32 *)g_00669F60 & 2) == 0) {
            func_001AA2C0(g_70000150 * 0x170 + 0x732220, 0);
        }
        func_003DF580();
    }
}

/* 0x001FBE60, 0x64 bytes. */
int func_001FBE60(int param_1, int param_2)
{
    int iVar2;
    int iVar3;
    u32 uVar1;

    iVar3 = g_7000088C * 0x750;
    uVar1 = *(u32 *)(iVar3 + 0x732674);
    if (uVar1 < 200) {
        *(u32 *)(uVar1 * 4 + iVar3 + 0x732670 + 8) = param_2;
        iVar2 = *(int *)(iVar3 + 0x732674);
        *(int *)(iVar3 + 0x732674) = iVar2 + 1;
        *(u32 *)(iVar2 * 4 + iVar3 + 0x732670 + 0x328) = param_1;
    }
    return uVar1 < 200;
}

/* 0x001FCAA0, 0x38 bytes. */
void func_001FCAA0(int param_1, int param_2)
{
    int uVar1;

    uVar1 = func_00207D40();
    func_001FC840(0x3F800000, uVar1, param_2);
}

/* 0x001FCAE0, 0x30 bytes. */
void func_001FCAE0(void)
{
    int uVar1;

    uVar1 = func_001942A0();
    func_001FC840(0x3F800000, uVar1, 0x70000000);
}

/* 0x001FCC50, 0x40 bytes. */
void func_001FCC50(void)
{
    g_70000768 = 0;
    func_001FD9A0(1, 1);
    func_001FD5F0(1);
    func_001FCAE0();
    func_001FCB10();
}

/* 0x001FD4B0, 0x13C bytes. */
void func_001FD4B0(int param_1, int param_2, int param_3, int param_4)
{
    int cVar2;
    int iVar3;
    int lVar4;
    int uVar1;

    uVar1 = *(u8 *)(param_2 + 0x61);
    cVar2 = *(char *)(param_2 + 0x62);
    iVar3 = g_7000088C * 0x750;
    if ((*(u8 *)(param_2 + 0x69) & 0x20) == 0) {
        lVar4 = func_00207CE0(param_3);
    }
    else {
        lVar4 = func_00207D00(param_3);
        if (lVar4 == 0) {
            lVar4 = func_00207CE0(param_3);
        }
    }
    if (lVar4 != 0) {
        if (*(int *)(iVar3 + 0x732670) == 0) {
            if ((cVar2 == '\b') || ((*(u8 *)((int)lVar4 + 0x2F) & 1) != 0)) {
                func_001FCCB0(param_1, lVar4, param_4, uVar1);
            }
            else {
                func_001FCF10(param_1, lVar4, param_4, uVar1, *(u8 *)(param_2 + 99), cVar2);
            }
        }
        else {
            func_001FD0B0(param_1, lVar4, param_4, uVar1, *(u8 *)(param_2 + 99), cVar2);
        }
    }
}

/* 0x001FE330, 0xA8 bytes. */
void func_001FE330(u32 *param_1, int param_2)
{
    int bVar1;
    int lVar3;
    u32 uVar2;
    u32 uVar4;

    for (; param_1 != (u32 *)0; param_1 = (u32 *)param_1[1]) {
        uVar2 = *param_1;
        uVar4 = 1 << (uVar2 & 7);
        bVar1 = (&g_700001E0)[uVar2 >> 3];
        if ((uVar4 & 0xFF & (u32)bVar1) == 0) {
            (&g_700001E0)[uVar2 >> 3] = bVar1 | (u8)uVar4;
            lVar3 = func_001F4FF0(uVar2, g_7000088C);
            if (lVar3 == 0) {
                func_001FDD90(uVar2, param_2);
            }
        }
    }
}

/* 0x001FEE00, 0xBC bytes. */
void func_001FEE00(int param_1)
{
    u32 uVar1;

    if (((&g_70000B98)[g_7000088C] & 0x41) != 0) {
        if (*(u32 *)g_00669DB8 == 2) {
            func_001FEA10(0, param_1);
            return;
        }
        func_001FE650();
    }
    uVar1 = 1;
    do {
        if ((1 << (uVar1 & 0x1F) & 0xffU & (u32)(u8)(&g_70000B98)[g_7000088C]) != 0) {
            func_001FEA10(uVar1, param_1);
        }
        uVar1 = uVar1 + 1;
    } while ((int)uVar1 < 5);
}

/* 0x001FF160, 0x50 bytes. */
int func_001FF160(int param_1)
{
    int bVar2;
    int cVar1;

    cVar1 = func_001FF100(param_1, 10);
    if (cVar1 == 28) {
        bVar2 = true;
    }
    else if (cVar1 == '#') {
        bVar2 = true;
    }
    else {
        bVar2 = cVar1 == '@';
    }
    return bVar2;
}

/* 0x001FF200, 0x28 bytes. */
int func_001FF200(int param_1)
{
    int cVar1;

    cVar1 = func_001FF100(param_1, 10);
    return cVar1 == 'p';
}

/* 0x001FF260, 0x30 bytes. */
int func_001FF260(u16 *param_1, int param_2)
{
    if (param_2 == 3) {
        param_2 = func_00207CC0(*param_1, 1);
    }
    return param_2;
}

/* 0x001FF290, 0x30 bytes. */
int func_001FF290(u16 *param_1, int param_2)
{
    if (param_2 == 3) {
        param_2 = func_00207CC0(*param_1, 0);
    }
    return param_2;
}

/* 0x001FF2C0, 0x48 bytes. */
int func_001FF2C0(u16 *param_1, int param_2)
{
    if (param_2 == 6) {
        func_00207CC0(*param_1, 1);
        param_2 = func_00207CC0(*param_1, 3);
    }
    return param_2;
}
