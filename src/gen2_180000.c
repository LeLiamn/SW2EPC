/*
 * gen2_180000.c - small functions between 0x00180000 and 0x00400000, generated from Ghidra
 * output (access widths from the disassembly) and kept only when their compiled size is within
 * 10 % of the original. Machine-like: to be cleaned up by hand later.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00772A74[0x18];
extern u8 g_00772D1C[0x18];
extern u8 g_00772D30[0x18];
extern u8 g_00772D5C[0x18];
extern u8 g_00772D70[0x18];
extern u8 g_00772D84[0x18];
extern u8 g_00772DAC[0x18];
extern u8 g_00772DC0[0x18];
extern u8 g_00772DD4[0x18];
extern u8 g_00780310[0x18];
extern u8 g_007B4E60[0x18];
#include "sw2e_mem.h"

#define true 1
#define false 0

extern u8 g_00411380[0x4];
extern u8 g_00417650[0x4];
extern u8 g_0045D73C[0x4];
extern u8 g_0045D898[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_005BA6A0[0x4];
extern u8 g_005BC080[0x9D];
extern u8 g_005BC3A0[0x1];
extern u8 g_005BD6B0[0x8];
extern u8 g_00669F60[0x14];
extern u8 g_00669F84[0x4];
extern u8 g_0068DDE0[0x10];
extern u8 g_0068EFF0[0x6E];
extern u8 g_0068F0F8[0x8];
extern u8 g_006A3A98[0xC4];
extern u8 g_0075294C[0x4];
extern u8 g_0076F3AC[0x4];
extern u8 g_00772D48[0x4];
extern u8 g_00772D54[0x4];
extern u8 g_0077BE70[0x10];
extern u8 g_00799A70[0x7C];
extern u8 g_00799A80[0x6C];
extern u8 g_007B9890[0x10];
extern u8 g_007B98B0[0xD2];
extern u8 g_007B9980[0x2];
extern u8 g_007B9E58[0x1];
extern u8 g_007B9F30[0x10];
extern u8 g_007BACC4[0x78];
extern u8 g_007BF69C[0x8];
extern int g_0045CE40;   /* (small data) */
extern int g_0045CE41;   /* (small data) */
extern int g_0045CE42;   /* (small data) */
extern int g_0045D028;   /* (small data) */
extern int g_0045D02C;   /* (small data) */
extern int g_0045D1C8;   /* (small data) */
extern int g_0045D2F0;   /* (small data) */
extern int g_0045D5C8;   /* (small data) */
extern int g_0045D5F0;   /* (small data) */
extern int g_0045D5F4;   /* (small data) */
extern int g_0045D5F8;   /* (small data) */
extern int g_0045D5FC;   /* (small data) */
extern u32 g_700000C0;   /* (scratchpad) */
extern u32 g_7000015C;   /* (scratchpad) */

int func_001026D0();
int func_00102960();
int func_00104AC0();
int func_00104D00();
int func_00104E70();
int func_00105860();
int func_00105900();
int func_00105B40();
int func_00105BE0();
int func_00106C50();
int func_00106C90();
int func_00106F10();
int func_00118AC0();
int func_0011ED38();
int func_001204B0();
int func_001206B0();
int func_001207E0();
int func_00120928();
int func_001251A0();
int func_00125450();
int func_00125508();
int func_00136DE8();
int func_00147160();
int func_0017DF10();
int func_00182F50();
int func_00183010();
int func_00183050();
int func_00186D50();
int func_00186E20();
int func_00186EC0();
int func_00187020();
int func_00187030();
int func_00187160();
int func_001871D0();
int func_00187410();
int func_001874E0();
int func_001875F0();
int func_001877E0();
int func_00187920();
int func_00187A70();
int func_00187C90();
int func_00187CE0();
int func_00187DA0();
int func_00187F20();
int func_001882F0();
int func_00188740();
int func_001887A0();
int func_00188C00();
int func_00188C80();
int func_00188D10();
int func_00188D50();
int func_00188DD0();
int func_00188E90();
int func_00189080();
int func_00189150();
int func_00189210();
int func_00189320();
int func_001893E0();
int func_001894A0();
int func_001894E0();
int func_001895F0();
int func_00189620();
int func_001896E0();
int func_00189760();
int func_001898C0();
int func_00189A60();
int func_00189BD0();
int func_00189C70();
int func_00189D00();
int func_00189D30();
int func_00189DE0();
int func_00189E40();
int func_00189EB0();
int func_00189F10();
int func_0018A030();
int func_0018A130();
int func_0018A1A0();
int func_0018A220();
int func_0018BA00();
int func_001904E0();
int func_001911A0();
int func_00191200();
int func_0019B0E0();
int func_0019B130();
int func_0019B240();
int func_0019FB00();
int func_001A1960();
int func_001A2970();
int func_001ABE40();
int func_001AE550();
int func_001B9A40();
int func_001EBC20();
int func_001EBD10();
int func_001EBEE0();
int func_001EBFC0();
int func_001F1640();
int func_001FF100();
int func_001FF120();
int func_001FF160();
int func_00206DF0();
int func_0020DFC0();
int func_0020E960();
int func_0020EB40();
int func_0020EB60();
int func_0020EDA0();
int func_0020EE50();
int func_0020FF60();
int func_00229FC0();
int func_0022BC70();
int func_0022C370();
int func_0022C690();
int func_0022DCD0();
int func_0022DD60();
int func_00236DD0();
int func_00237040();
int func_00239830();
int func_0023A760();
int func_0023A7D0();
int func_0023AA40();
int func_0023AD10();
int func_002456F0();
int func_002470B0();
int func_0028EED0();
int func_0028FBD0();
int func_0028FE20();
int func_00290390();
int func_00290770();
int func_00294760();
int func_00295070();
int func_0029A540();
int func_0029A610();
int func_0029A8F0();
int func_0029ABA0();
int func_0029B1C0();
int func_0029B4D0();
int func_0029B5A0();
int func_0029C9B0();
int func_0029C9E0();
int func_0029D210();
int func_0029D430();
int func_0029D4B0();
int func_0029FB70();
int func_002A9EC0();
int func_002AA1C0();
int func_002C5AE0();
int func_002C5C60();
int func_002C65C0();
int func_002C7310();
int func_002C7C00();
int func_002C92A0();
int func_002C9D30();
int func_002CA160();
int func_002CC190();
int func_002CCE60();
int func_002D8060();
int func_002D83E0();
int func_002D8480();
int func_002D8950();
int func_002D8C30();
int func_002D8EE0();
int func_002D9640();
int func_002D9EE0();
int func_002DA2D0();
int func_002DA8C0();
int func_002DAE60();
int func_002DB3C0();
int func_002DED90();
int func_002DFEE0();
int func_002DFF40();
int func_002DFF70();
int func_002E15A0();
int func_002E16A0();
int func_002E1700();
int func_002F27D0();
int func_002F2870();
int func_002F2890();
int func_002F2970();
int func_002F34E0();
int func_002F3B30();
int func_002F4080();
int func_002F4AE0();
int func_002F56A0();
int func_002F57F0();
int func_002F5CC0();
int func_002F7300();
int func_002F7410();
int func_002F75C0();
int func_002F7610();
int func_002F7B10();
int func_002F7B20();
int func_002F7D90();
int func_002F8CB0();
int func_002F8D20();
int func_002F8E80();
int func_002F8F20();
int func_002F8F90();
int func_002F9390();
int func_002F9C90();
int func_002F9D50();
int func_002FA790();
int func_002FA8E0();
int func_002FA970();
int func_002FA9E0();
int func_002FABC0();
int func_002FAEA0();
int func_002FAF30();
int func_002FAFC0();
int func_002FB2A0();
int func_002FB2D0();
int func_002FB320();
int func_002FB3B0();
int func_002FB430();
int func_002FB7C0();
int func_002FB9D0();
int func_00309FB0();
int func_0030AB50();
int func_0030AB90();
int func_0030AC50();
int func_0030AC90();
int func_0030AD80();
int func_0030ADC0();
int func_0030AF20();
int func_0030AFF0();
int func_0030B030();
int func_0030B090();
int func_0030B1B0();
int func_0030B240();
int func_0030B8F0();
int func_0030C250();
int func_0030C280();
int func_0030C4E0();
int func_0030C6A0();
int func_0030C6E0();
int func_0030C920();
int func_0030CA50();
int func_0030CB00();
int func_0030CB50();
int func_0030CC80();
int func_0030D7D0();
int func_0030E100();
int func_0030E140();
int func_0030E1F0();
int func_0030E390();
int func_00314960();
int func_00320F00();
int func_00323840();
int func_00327190();
int func_003273D0();
int func_00327690();
int func_003276B0();
int func_00327710();
int func_00327750();
int func_00327780();
int func_00327820();
int func_00327830();
int func_00327880();
int func_003278B0();
int func_003278D0();
int func_00327920();
int func_00327970();
int func_003279B0();
int func_003279D0();
int func_00327A30();
int func_00327A60();
int func_00327A80();
int func_00327BD0();
int func_00327C00();
int func_00327C10();
int func_00327C40();
int func_00327C50();
int func_00327CC0();
int func_00327CF0();
int func_00327D50();
int func_00327DC0();
int func_00327DF0();
int func_00327E30();
int func_00327E50();
int func_00327E60();
int func_00327F00();
int func_00327F70();
int func_00327FE0();
int func_00328050();
int func_003280C0();
int func_003280F0();
int func_003281F0();
int func_00328240();
int func_00328270();
int func_00328290();
int func_003282E0();
int func_003282F0();
int func_00328600();
int func_00328B30();
int func_00328BA0();
int func_00328CB0();
int func_00328E70();
int func_00329030();
int func_00329450();
int func_00329540();
int func_003297A0();
int func_003297E0();
int func_00329820();
int func_00329D60();
int func_0032B180();
int func_0032C060();
int func_0032C080();
int func_0032C9E0();
int func_0032CF00();
int func_0032D300();
int func_0032D9C0();
int func_0032E8A0();
int func_0032E960();
int func_0032EB40();
int func_0032ED30();
int func_0032F1D0();
int func_0032FEF0();
int func_0032FF10();
int func_0032FF20();
int func_00337A10();
int func_0033B700();
int func_0034EC80();
int func_0034ED90();
int func_0034EE50();
int func_00352FE0();
int func_0035D510();
int func_0035D5A0();
int func_00362C10();
int func_00362D10();
int func_0036B260();
int func_0036D780();
int func_0036E8D0();
int func_003704C0();
int func_00370A00();
int func_003710C0();
int func_003710F0();
int func_00371310();
int func_00371520();
int func_003717A0();
int func_00372540();
int func_00372C40();
int func_00372E30();
int func_003736B0();
int func_00373720();
int func_00373DF0();
int func_00373F60();
int func_00374E00();
int func_00374EE0();
int func_00375B90();
int func_00375BF0();
int func_0037ED80();
int func_00389A50();
int func_00389AC0();
int func_0038C6F0();
int func_0038C750();
int func_00390760();
int func_0039D930();
int func_0039E650();
int func_003A01A0();
int func_003A2940();
int func_003A5240();
int func_003A78E0();
int func_003A7C10();
int func_003A8000();
int func_003A8030();
int func_003A80B0();
int func_003A9010();
int func_003A91F0();
int func_003A9480();
int func_003A9640();
int func_003A9700();
int func_003B4740();
int func_003BFC30();
int func_003C1200();
int func_003D2F80();
int func_003DB220();
int func_003DB460();
int func_003DB480();
int func_003DB900();
int func_003DC2D0();
int func_003DD710();
int func_003E0A50();
int func_003E1260();
int func_003EA000();
int func_003EA0C0();
int func_003EA0E0();
int func_003EA140();
int func_003EA160();
int func_003EA180();
int func_003EA1A0();
int func_003EA1C0();
int func_003EA310();
int func_003EA330();
int func_003EAB60();
int func_003ED680();
int func_003EF1D0();
int func_003F15C0();
int func_003F2780();
int func_003F2950();
void func_00183240(void);
void func_0018A290(short *param_1, int param_2, int param_3);
void func_001EB860(u8 *param_1);
void func_001EC210(u8 *param_1);
void func_001EEEE0(u8 *param_1, int param_2);
int func_001FF1B0(int param_1);
int func_00207190(int param_1, int param_2);
void func_00207260(u8 *param_1, u8 *param_2);
void func_0020E8C0(int param_1, int param_2, int param_3);
void func_0020FC40(void);
void func_0022A120(int *param_1, int param_2);
void func_0022B950(u8 *param_1);
void func_0022CD40(int param_1, int param_2, int param_3);
void func_0022CD70(int param_1, int param_2);
void func_00236FC0(void);
void func_002456C0(int param_1, int param_2, int param_3);
void func_00245ED0(int param_1, u8 *param_2);
void func_002790E0(int param_1, int param_2);
void func_002863E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_0028F4C0(u8 *param_1);
void func_00296930(int param_1, u8 *param_2, u8 *param_3);
void func_002974A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
int func_0029A170(u8 *param_1, int param_2);
int func_0029AB10(u8 *param_1, int param_2);
void func_0029B900(int param_1, int param_2, int param_3, int param_4, int *param_5);
void func_0029CAB0(int param_1, int param_2, u8 *param_3);
void func_0029CEB0(int param_1, int param_2, int param_3, int param_4);
void func_0029D230(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_0029D310(int param_1, int param_2, u8 *param_3);
void func_0029D520(int param_1, int param_2, int param_3);
void func_002A6430(void);
void func_002A9610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002AA020(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002AA150(int param_1);
int func_002C1260(u8 *param_1, int param_2, int param_3);
void func_002C7FA0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002C98E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
void func_002CA060(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002CA490(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002CD5E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002CD780(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002CE160(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002D6D70(void);
void func_002D8240(u32 *param_1);
int func_002DA090(void);
int func_002DAC30(void);
void func_002DB4F0(void);
void func_002DB800(void);
void func_002E0000(int param_1);
void func_002E0040(int param_1);
void func_002E0640(u8 *param_1, int param_2, int param_3);
void func_002E14E0(int param_1, int param_2, int param_3);
void func_002E1820(u8 *param_1);
void func_002EF080(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_00320F60(void);
int func_003217D0(void);
int func_00323F10(int param_1, int param_2, int *param_3, u8 *param_4);
void func_003246C0(int param_1, u32 *param_2);
int func_00326000(int param_1, int *param_2, u8 *param_3, int *param_4, u8 *param_5);
void func_003273E0(void);
void func_0032CFF0(void);
void func_0032D270(int param_1);
void func_0032FF70(int param_1);
int func_00330650(int param_1);
int func_0036D9B0(int param_1, int param_2);
void func_0036EB40(void);
void func_00371850(void);
void func_00373540(void);
int func_00374040(int param_1);
int func_003748C0(int param_1, int param_2, int param_3);
void func_00383270(int param_1, int param_2, int param_3);
void func_003832E0(int param_1, int param_2, int param_3, int param_4);
void func_00383610(int param_1, int param_2, int param_3, int param_4);
void func_00383AB0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_00383E00(int param_1);
void func_003886D0(void);
int func_003892C0(u8 *param_1);
void func_00389B40(int param_1, int param_2, u8 *param_3);
void func_0038AD60(u8 *param_1);
int func_0038C6B0(int param_1);
void func_0039D950(int param_1);
void func_0039D990(int param_1);
void func_003A63D0(int param_1);
void func_003A97C0(int *param_1, int param_2, int param_3);
int func_003CBBB0(void);
int func_003E12A0(void);
void func_003EBE60(void);
void func_003ECD90(void);
void func_003ECEB0(void);
void func_003ED480(void);
void func_003ED7F0(void);
void func_003EDD00(void);
void func_003EE2E0(void);
int func_003EF290(int param_1, int param_2);
int func_003EF400(int param_1, int param_2);
int func_003F16C0(u32 *param_1);
int func_003F17D0(void);
int func_003F1900(u32 *param_1);
int func_003F2090(u32 *param_1);
int func_003F2200(u32 *param_1);
int func_003F2400(void);
int func_003F2440(u32 *param_1);
int func_003F2610(u32 *param_1);
int func_003F2740(void);
int func_003F2810(u32 *param_1);
int func_003F2A00(void);

/* 0x00183240, 0x174 bytes. */
void func_00183240(void)
{
    int lVar1;
    u8 * pbVar2;
    u32 uVar3;

  
  do {
    while( true ) {
      if (((*(u32 *)(g_00669F60 + 0x0)) & 0x8000000) != 0) {
        return;
      }
      if (((*(u8 *)(g_005BC3A0 + 0x0)) & 0x38) != 0) {
        return;
      }
      if (((*(u8 *)(g_005BC3A0 + 0x0)) & 1) == 0) break;
      if (((*(u8 *)(g_005BC3A0 + 0x0)) & 2) == 0) {
        func_00182F50(0x5bc3a0);
      }
      else {
        lVar1 = func_0035D510(0x5bc3a0);
        if (lVar1 == 0) {
          return;
        }
      }
    }
    if (((*(u8 *)(g_005BC3A0 + 0x0)) & 0x40) != 0) {
      if (((*(u32 *)(g_00669F60 + 0x0)) & 8) == 0) {
        func_002D6D70();
        return;
      }
      return;
    }
    uVar3 = 0;
    pbVar2 = (u8 *)0x5bc2a0;
    do {
      if (pbVar2[3] != 1) break;
      uVar3 = uVar3 + 1;
      pbVar2 = pbVar2 + 4;
    } while (uVar3 < 0x40);
    if (0x3f < uVar3) {
      return;
    }
    if ((*pbVar2 & 1) == 0) {
      return;
    }
    if ((*pbVar2 & 2) == 0) {
      func_00183050(pbVar2);
    }
    else {
      func_00183010(pbVar2,0);
    }
    for (; uVar3 < 0x3f; uVar3 = uVar3 + 1) {
      func_00118AC0(pbVar2,pbVar2 + 4,4);
      pbVar2 = pbVar2 + 4;
    }
    *pbVar2 = 0;
    pbVar2[3] = 0;
  } while( true );
}

/* 0x0018A290, 0x5DC bytes. */
void func_0018A290(short *param_1, int param_2, int param_3)
{
    int sVar1;

  
  sVar1 = *param_1;
  if (sVar1 != 0xff) {
    if (sVar1 == 0x33) {
      func_00186D50(param_1 + 1);
    }
    else if (sVar1 == 0x32) {
      func_00186E20(param_1 + 1);
    }
    else if (sVar1 == 0x31) {
      func_00186EC0(param_1 + 1);
    }
    else if (sVar1 == 0x30) {
      func_00187020(param_1 + 1);
    }
    else if (sVar1 == 0x2f) {
      func_00187030(param_1 + 1);
    }
    else if (sVar1 == 0x2e) {
      func_00187160(param_1 + 1);
    }
    else if (sVar1 == 0x2d) {
      func_001871D0(param_1 + 1,param_3);
    }
    else if (sVar1 == 0x2c) {
      func_00187410(param_1 + 1);
    }
    else if (sVar1 == 0x2b) {
      func_001874E0(param_1 + 1);
    }
    else if (sVar1 == 0x2a) {
      func_001875F0(param_1 + 1);
    }
    else if (sVar1 == 0x29) {
      func_001877E0(param_1 + 1);
    }
    else if (sVar1 == 0x28) {
      func_00187920(param_1 + 1);
    }
    else if (sVar1 == 0x27) {
      func_00187A70(param_1 + 1);
    }
    else if (sVar1 == 0x26) {
      func_0018A220(param_1 + 1);
    }
    else if (sVar1 == 0x25) {
      func_0018A1A0(param_1 + 1);
    }
    else if (sVar1 == 0x24) {
      func_0018A130(param_1 + 1);
    }
    else if (sVar1 == 0x23) {
      func_0018A030(param_1 + 1);
    }
    else if (sVar1 == 0x22) {
      func_00189F10(param_1 + 1);
    }
    else if (sVar1 == 0x21) {
      func_00187C90(param_1 + 1);
    }
    else if (sVar1 == 0x20) {
      func_00187CE0(param_1 + 1);
    }
    else if (sVar1 == 0x1f) {
      func_00187DA0(param_1 + 1);
    }
    else if (sVar1 == 0x1e) {
      func_00187F20(param_1 + 1);
    }
    else if (sVar1 == 0x1d) {
      func_001882F0(param_1 + 1);
    }
    else if (sVar1 == 0x1c) {
      func_00188740(param_1 + 1);
    }
    else if (sVar1 == 0x1b) {
      func_001887A0(param_1 + 1);
    }
    else if (sVar1 == 0x1a) {
      func_00188C00(param_1 + 1);
    }
    else if (sVar1 == 0x19) {
      func_00188C80(param_1 + 1);
    }
    else if (sVar1 == 0x18) {
      func_00188D10(param_1 + 1);
    }
    else if (sVar1 == 0x17) {
      func_00188D50(param_1 + 1);
    }
    else if (sVar1 == 0x16) {
      func_00188DD0(param_1 + 1);
    }
    else if (sVar1 == 0x15) {
      func_00188E90(param_1 + 1);
    }
    else if (sVar1 == 0x14) {
      func_00189080(param_1 + 1);
    }
    else if (sVar1 == 0x13) {
      func_00189150(param_1 + 1);
    }
    else if (sVar1 == 0x12) {
      func_00189210(param_1 + 1);
    }
    else if (sVar1 == 0x11) {
      func_00189320(param_1 + 1);
    }
    else if (sVar1 == 0x10) {
      func_001893E0(param_1 + 1);
    }
    else if (sVar1 == 0xf) {
      func_001894A0(param_1 + 1);
    }
    else if (sVar1 == 0xe) {
      func_001894E0(param_1 + 1);
    }
    else if (sVar1 == 0xd) {
      func_001895F0(param_1 + 1);
    }
    else if (sVar1 == 0xc) {
      func_00189620(param_1 + 1);
    }
    else if (sVar1 == 0xb) {
      func_001896E0(param_1 + 1);
    }
    else if (sVar1 == 10) {
      func_00189760(param_1 + 1);
    }
    else if (sVar1 == 9) {
      func_001898C0(param_1 + 1,1);
    }
    else if (sVar1 == 8) {
      func_001898C0(param_1 + 1,0);
    }
    else if (sVar1 == 7) {
      func_00189A60(param_1 + 1);
    }
    else if (sVar1 == 6) {
      func_00189BD0(param_1 + 1);
    }
    else if (sVar1 == 5) {
      func_00189C70(param_1 + 1);
    }
    else if (sVar1 == 4) {
      func_00189D00(param_1 + 1);
    }
    else if (sVar1 == 3) {
      func_00189D30(param_1 + 1);
    }
    else if (sVar1 == 2) {
      func_00189DE0(param_1 + 1);
    }
    else if (sVar1 == 1) {
      func_00189E40(param_1 + 1);
    }
    else if (sVar1 == 0) {
      func_00189EB0(param_1 + 1);
    }
  }
  return;
}

/* 0x001EB860, 0x58 bytes. */
void func_001EB860(u8 *param_1)
{
    short asStack_8[4];
    u16 auStack_c[2];

  
  asStack_8[0] = *(short *)(param_1 + 0x42);
  if (asStack_8[0] == *(short *)(param_1 + 0x40)) {
    *(u8 *)(param_1 + 0x48) = 0;
    *(u8 *)(param_1 + 0x49) = 0;
  }
  else {
    auStack_c[0] = *(u16 *)(param_1 + 0x48);
    func_001F1640(asStack_8,auStack_c);
    *(u16 *)(param_1 + 0x48) = auStack_c[0];
  }
  return;
}

/* 0x001EC210, 0x84 bytes. */
void func_001EC210(u8 *param_1)
{
    int cVar1;

  
  cVar1 = *(char *)(param_1 + 0x7a);
  if (cVar1 == '\x03') {
    func_001EBC20();
  }
  else if (cVar1 == '\x02') {
    func_001EBD10();
  }
  else if (cVar1 == '\x01') {
    func_001EBEE0();
  }
  else if (cVar1 == '\0') {
    func_001EBFC0();
  }
  return;
}

/* 0x001EEEE0, 0x2AC bytes. */
void func_001EEEE0(u8 *param_1, int param_2)
{
    int lVar3;
    int lVar6;
    int lVar7;
    int sVar2;
    int sVar4;
    int sVar5;
    int uVar1;

  
  if ((*(u32 *)(param_1 + 0x80) & 0x20000) != 0) {
    func_001B9A40();
  }
  lVar7 = (int)((int)*(short *)(param_1 + 0x4c) + (*(short *)(param_1 + 0x4c) * param_2) / 100);
  if (lVar7 < 0x3e9) {
    lVar6 = lVar7;
  }
  else {
    lVar6 = 1000;
  }
  if (lVar6 < 1) {
    sVar4 = 0;
    lVar7 = 0;
  }
  else {
    if (1000 < lVar7) {
      lVar7 = 1000;
    }
    sVar4 = (short)lVar7;
    lVar7 = lVar7 << 0x30;
  }
  lVar7 = lVar7 >> 0x30;
  if (lVar7 < 0x3e9) {
    lVar6 = lVar7;
  }
  else {
    lVar6 = 1000;
  }
  if (lVar6 < 1) {
    uVar1 = 0;
    lVar6 = 0;
  }
  else {
    if (lVar7 < 0x3e9) {
      lVar6 = lVar7;
    }
    else {
      lVar6 = 1000;
    }
    uVar1 = (u16)lVar6;
    lVar6 = lVar6 << 0x30;
  }
  lVar6 = lVar6 >> 0x30;
  *(u16 *)(param_1 + 0x4c) = uVar1;
  if (lVar6 < lVar7) {
    lVar3 = lVar6;
  }
  else {
    lVar3 = (int)sVar4;
  }
  if ((short)lVar3 < 1) {
    uVar1 = 0;
  }
  else {
    if (lVar7 <= lVar6) {
      lVar6 = (int)sVar4;
    }
    uVar1 = (u16)lVar6;
  }
  *(u16 *)(param_1 + 0x4e) = uVar1;
  lVar7 = (int)((int)*(short *)(param_1 + 0x50) + (*(short *)(param_1 + 0x50) * param_2) / 100);
  if (lVar7 < 0x2711) {
    lVar6 = lVar7;
  }
  else {
    lVar6 = 10000;
  }
  if (lVar6 < 1) {
    lVar7 = 0;
  }
  else {
    if (10000 < lVar7) {
      lVar7 = 10000;
    }
    lVar7 = lVar7 << 0x30;
  }
  lVar7 = lVar7 >> 0x30;
  if (lVar7 < 0x2711) {
    lVar6 = lVar7;
  }
  else {
    lVar6 = 10000;
  }
  if (lVar6 < 1) {
    sVar4 = 0;
    *(u16 *)(param_1 + 0x50) = 0;
  }
  else {
    if (10000 < lVar7) {
      lVar7 = 10000;
    }
    sVar4 = (short)lVar7;
    *(short *)(param_1 + 0x50) = sVar4;
  }
  sVar5 = *(short *)(param_1 + 0x52) + (short)((*(short *)(param_1 + 0x52) * param_2) / 100);
  sVar2 = sVar5;
  if (sVar4 < sVar5) {
    sVar2 = sVar4;
  }
  if (sVar2 < 1) {
    sVar4 = 0;
  }
  else if (sVar5 <= sVar4) {
    sVar4 = sVar5;
  }
  *(short *)(param_1 + 0x52) = sVar4;
  return;
}

/* 0x001FF1B0, 0x4C bytes. */
int func_001FF1B0(int param_1)
{
    int bVar2;
    int cVar1;
    int lVar3;

  
  lVar3 = func_001FF160();
  if (lVar3 == 0) {
    cVar1 = func_001FF100(param_1,10);
    bVar2 = cVar1 == '6';
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}

/* 0x00207190, 0x5C bytes. */
int func_00207190(int param_1, int param_2)
{
    u8 auStack_10[8];
    u8 auStack_8[8];
    int lVar1;

  
  func_00191200(auStack_8,param_1);
  lVar1 = func_00206DF0(auStack_8,auStack_10);
  if (lVar1 != 0) {
    func_001911A0(param_2,auStack_10);
  }
  return lVar1 != 0;
}

/* 0x00207260, 0x5C bytes. */
void func_00207260(u8 *param_1, u8 *param_2)
{
    int lVar1;
    int uStack_8;

  
  lVar1 = func_00206DF0(param_2,&uStack_8);
  if (lVar1 == 0) {
    uStack_8 = *(unsigned long long *)param_2;
  }
  func_001911A0(param_1 + 0x20,&uStack_8);
  *(unsigned long long *)(param_1 + 0x18) = uStack_8;
  return;
}

/* 0x0020E8C0, 0x9C bytes. */
void func_0020E8C0(int param_1, int param_2, int param_3)
{
    int iVar1;
    int * piVar2;

  
  iVar1 = (int)param_1;
  piVar2 = (int *)(iVar1 * 4 + 0x73c484);
  if (*piVar2 == 0) {
    if (param_3 == 0) {
      iVar1 = func_001026D0(1,iVar1 + 0xc08,0,param_2,0,0,0x429ac0,0x282);
      *piVar2 = iVar1;
    }
    else {
      iVar1 = func_0020EDA0(iVar1 + 0xc08);
      *piVar2 = iVar1;
    }
    func_0020DFC0(param_1,param_3);
  }
  return;
}

/* 0x0020FC40, 0xA4 bytes. */
void func_0020FC40(void)
{
    int iVar3;
    int iVar4;
    int lVar2;
    int uStack_3;
    int uStack_4;
    int uVar1;
    u32 uVar5;

  
  iVar3 = 0;
  do {
    iVar4 = 0;
    do {
      uStack_4 = (u8)iVar4;
      uStack_3 = (u8)iVar3;
      func_0020FF60(&uStack_4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x19);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x19);
  uVar5 = 0;
  do {
    uVar1 = func_0034EC80(uVar5);
    lVar2 = func_0034EE50(uVar1);
    if (lVar2 != 0) {
      func_0034ED90(uVar1,&uStack_4);
      func_0020FF60(&uStack_4);
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x14);
  return;
}

/* 0x0022A120, 0xD0 bytes. */
void func_0022A120(int *param_1, int param_2)
{
    int iVar2;
    int * piVar1;
    int * piVar3;
    int * piVar4;
    u32 uVar5;
    u32 uVar6;

  
  if ((param_1[2] == 0) && ((int *)*param_1 != (int *)0x0)) {
    piVar4 = param_1 + 1;
    uVar6 = (u32)*(u8 *)(*(int *)*param_1 + 0x1d);
    uVar5 = 0;
    if (uVar6 != 0) {
      iVar2 = 0;
      piVar1 = param_1;
      piVar3 = piVar4;
      do {
        piVar4 = piVar1 + 4;
        func_00229FC0(piVar4,*(int *)(*param_1 + 4) + iVar2,param_2);
        uVar5 = uVar5 + 1;
        *piVar3 = (int)piVar4;
        iVar2 = iVar2 + 0x10;
        piVar1 = piVar1 + 4;
        piVar3 = piVar4;
      } while (uVar5 < uVar6);
    }
    *piVar4 = 0;
    param_1[2] = 1;
  }
  return;
}

/* 0x0022B950, 0x54 bytes. */
void func_0022B950(u8 *param_1)
{
    u32 uVar1;

  
  uVar1 = 0;
  if (*(char *)(param_1 + 0x54) != '\0') {
    do {
      func_0022BC70(param_1,uVar1);
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(u8 *)(param_1 + 0x54));
  }
  return;
}

/* 0x0022CD40, 0x2C bytes, matching. */
void func_0022CD40(int param_1, int param_2, int param_3)
{
  func_0022C370(g_0045D2F0,param_1,param_2,param_3);
  return;
}

/* 0x0022CD70, 0x28 bytes, matching. */
void func_0022CD70(int param_1, int param_2)
{
  func_0022C690(g_0045D2F0,param_1,param_2);
  return;
}

/* 0x00236FC0, 0x7C bytes. */
void func_00236FC0(void)
{
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if ((g_7000015C >> 0x10) % 100 < (u32)(((*(u32 *)(g_00669F84 + 0x0)) + 0xb) * 3)) {
    func_00236DD0();
  }
  else {
    func_00237040();
  }
  return;
}

/* 0x002456C0, 0x28 bytes, matching. */
void func_002456C0(int param_1, int param_2, int param_3)
{
  func_002456F0(param_1,0,param_2,param_3);
  return;
}

/* 0x00245ED0, 0x4C bytes. */
void func_00245ED0(int param_1, u8 *param_2)
{
    u8 * pbVar1;

  
  pbVar1 = (u8 *)((u32)(*(u16 *)(param_2 + 0x58) >> 3) +
                   param_1 * 0x40 + (*(u32 *)(g_0075294C + 0x0)) * 0x100 + 0x752950);
  *pbVar1 = *pbVar1 | (u8)(1 << (*(u16 *)(param_2 + 0x58) & 7));
  return;
}

/* 0x002790E0, 0x5C bytes. */
void func_002790E0(int param_1, int param_2)
{
    int uVar1;

  
  if (g_0045D1C8 == 1) {
    uVar1 = 0x1320;
  }
  else {
    uVar1 = 0x1d00;
  }
  func_00104E70((*(u32 *)(g_0076F3AC + 0x0)) +
               *(int *)((*(u32 *)(g_0076F3AC + 0x0)) + 8) * *(int *)((*(u32 *)(g_0076F3AC + 0x0)) + 0x10 + param_1 * 8),uVar1,0x3ffc
               ,param_2);
  return;
}

/* 0x002863E0, 0x3C bytes. */
void func_002863E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
  func_002CC190(param_2,param_1,param_3,param_4,0,param_5,param_6,0x80);
  return;
}

/* 0x0028F4C0, 0x3A0 bytes. */
void func_0028F4C0(u8 *param_1)
{
    u8 auStack_20[28];
    int iStack_4;
    int iVar2;
    u8 * iVar3;
    u32 uVar1;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;
    u32 uVar7;
    u32 uVar8;

  
  uVar8 = 0;
  *(u32 *)(param_1 + 0x1b0) = 0x5bc084;
  *(u32 *)(param_1 + 0x1b4) = 0x5bc120;
  uVar7 = (u32)(*(u8 *)(g_005BC080 + 0x0));
  uVar6 = (u32)(*(u8 *)(g_005BC080 + 0x9C));
  *(u32 *)(param_1 + 0x180) = 0;
  *(u32 *)(param_1 + 0x198) = 0;
  *(u32 *)(param_1 + 0x184) = 0;
  *(u32 *)(param_1 + 0x19c) = 0;
  *(u32 *)(param_1 + 0x188) = 0;
  *(u32 *)(param_1 + 0x1a0) = 0;
  *(u32 *)(param_1 + 0x18c) = 0;
  *(u32 *)(param_1 + 0x1a4) = 0;
  *(u32 *)(param_1 + 400) = 0;
  *(u32 *)(param_1 + 0x1a8) = 0;
  *(u32 *)(param_1 + 0x194) = 0;
  *(u32 *)(param_1 + 0x1ac) = 0;
  *(u8 *)(param_1 + 0x1b8) = 0;
  if (uVar7 != 0) {
    do {
      func_0018BA00(0x5bc068,uVar8,&iStack_4,auStack_20);
      iVar2 = iStack_4 * 0x88 + 0x693970;
      if ((iVar2 != 0) && (*(char *)(iStack_4 * 0x88 + 0x6939e9) == '\0')) {
        uVar1 = (u32)*(u8 *)(param_1 + 0x1b8);
        uVar5 = 0;
        if (uVar1 != 0) {
          iVar3 = param_1;
          do {
            if (*(int *)(iVar3 + 0x180) == iVar2) break;
            uVar5 = uVar5 + 1;
            iVar3 = iVar3 + 4;
          } while (uVar5 < uVar1);
        }
        if (uVar5 == uVar1) {
          *(int *)(param_1 + uVar1 * 4 + 0x180) = iVar2;
          *(char *)(param_1 + 0x1b8) = *(char *)(param_1 + 0x1b8) + '\x01';
        }
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar7);
  }
  uVar8 = 0;
  if (uVar6 != 0) {
    do {
      func_0018BA00(0x5bc104,uVar8,&iStack_4,auStack_20);
      iVar2 = iStack_4 * 0x88 + 0x693970;
      if ((iVar2 != 0) && (*(char *)(iStack_4 * 0x88 + 0x6939e9) == '\0')) {
        uVar1 = (u32)*(u8 *)(param_1 + 0x1b8);
        uVar5 = 0;
        if (uVar1 != 0) {
          iVar3 = param_1;
          do {
            if (*(int *)(iVar3 + 0x180) == iVar2) break;
            uVar5 = uVar5 + 1;
            iVar3 = iVar3 + 4;
          } while (uVar5 < uVar1);
        }
        if (uVar5 == uVar1) {
          *(int *)(param_1 + uVar1 * 4 + 0x180) = iVar2;
          *(char *)(param_1 + 0x1b8) = *(char *)(param_1 + 0x1b8) + '\x01';
        }
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar6);
  }
  *(u8 *)(param_1 + 0x1b9) = 0;
  uVar8 = 1;
  do {
    uVar1 = 0;
    if (uVar7 != 0) {
      do {
        func_0018BA00(0x5bc068,uVar1,&iStack_4,auStack_20);
        iVar2 = iStack_4 * 0x88 + 0x693970;
        if ((iVar2 != 0) && (uVar8 == *(u8 *)(iStack_4 * 0x88 + 0x6939e9))) {
          uVar5 = (u32)*(u8 *)(param_1 + 0x1b9);
          uVar4 = 0;
          if (uVar5 != 0) {
            iVar3 = param_1;
            do {
              if (*(int *)(iVar3 + 0x198) == iVar2) break;
              uVar4 = uVar4 + 1;
              iVar3 = iVar3 + 4;
            } while (uVar4 < uVar5);
          }
          if (uVar4 == uVar5) {
            *(int *)(param_1 + uVar5 * 4 + 0x198) = iVar2;
            *(char *)(param_1 + 0x1b9) = *(char *)(param_1 + 0x1b9) + '\x01';
          }
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < uVar7);
    }
    uVar1 = 0;
    if (uVar6 != 0) {
      do {
        func_0018BA00(0x5bc104,uVar1,&iStack_4,auStack_20);
        iVar2 = iStack_4 * 0x88 + 0x693970;
        if ((iVar2 != 0) && (uVar8 == *(u8 *)(iStack_4 * 0x88 + 0x6939e9))) {
          uVar5 = (u32)*(u8 *)(param_1 + 0x1b9);
          uVar4 = 0;
          if (uVar5 != 0) {
            iVar3 = param_1;
            do {
              if (*(int *)(iVar3 + 0x198) == iVar2) break;
              uVar4 = uVar4 + 1;
              iVar3 = iVar3 + 4;
            } while (uVar4 < uVar5);
          }
          if (uVar4 == uVar5) {
            *(int *)(param_1 + uVar5 * 4 + 0x198) = iVar2;
            *(char *)(param_1 + 0x1b9) = *(char *)(param_1 + 0x1b9) + '\x01';
          }
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < uVar6);
    }
    uVar8 = uVar8 + 1;
    if (2 < uVar8) {
      return;
    }
  } while( true );
}

/* 0x00296930, 0x7C bytes. */
void func_00296930(int param_1, u8 *param_2, u8 *param_3)
{
    u8 auStack_4[4];
    int bVar1;
    int uVar2;

  
  auStack_4[0] = g_0045CE40;
  auStack_4[1] = g_0045CE41;
  bVar1 = *(u8 *)(param_2 + 0x79);
  auStack_4[2] = g_0045CE42;
  *param_3 = auStack_4[bVar1];
  if ((*(u32 *)(param_2 + 0x80) & 0x8000000) == 0) {
    func_003DD710();
  }
  else {
    uVar2 = func_00372C40(bVar1);
    func_00120928(param_1,uVar2);
  }
  return;
}

/* 0x002974A0, 0x90 bytes, matching. */
void func_002974A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u8 auStack_10[16];
    int uVar1;

  
  uVar1 = func_0033B700();
  func_0028EED0(auStack_10,uVar1);
  func_00295070(param_2,param_3,param_4,auStack_10,param_5,param_6,param_7,1);
  return;
}

/* 0x0029A170, 0x48 bytes. */
int func_0029A170(u8 *param_1, int param_2)
{
    int iVar1;
    u32 uVar2;

  
  iVar1 = 0;
  uVar2 = 0;
  if (param_2 != 0) {
    do {
      if (*(u8 *)(param_1 + uVar2) < 0x1f) {
        iVar1 = iVar1 + 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_2);
  }
  return iVar1;
}

/* 0x0029AB10, 0x48 bytes. */
int func_0029AB10(u8 *param_1, int param_2)
{
    int iVar1;
    u32 uVar2;

  
  iVar1 = 0;
  uVar2 = 0;
  if (param_2 != 0) {
    do {
      if (*(u8 *)(param_1 + uVar2) < 10) {
        iVar1 = iVar1 + 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < param_2);
  }
  return iVar1;
}

/* 0x0029B900, 0x2C0 bytes. */
void func_0029B900(int param_1, int param_2, int param_3, int param_4, int *param_5)
{
    int bStack_1;
    int bVar1;
    int lVar3;
    u8 * pbVar5;
    u8 * puVar4;
    int uStack_10;
    int uStack_e;
    u32 uVar2;

  
  lVar3 = func_0036D780();
  if (lVar3 == 0) {
    puVar4 = (u8 *)0x4113e0;
  }
  else {
    puVar4 = (g_00411380 + 0x0);
  }
  uVar2 = ((*(u32 *)(g_00772D48 + 0x0)) >> 1) + 1;
  if (6 < uVar2) {
    uVar2 = 7;
  }
  if ((*(u32 *)(g_00772D48 + 0x0)) < 0x18) {
    (*(u32 *)(g_00772D48 + 0x0)) = (*(u32 *)(g_00772D48 + 0x0)) + 1;
  }
  bVar1 = func_002C5AE0(g_00772D30);
  pbVar5 = (u8 *)param_2;
  if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
    func_002C65C0(0xffffffffffffffc4,*(int *)(puVar4 + (u32)*pbVar5 * 0xc + 4) + -2,0x100,0x1c,0,
                 bVar1);
  }
  else {
    bStack_1 = bVar1;
    if (*param_5 != 0) {
      bStack_1 = 0;
    }
    func_002C5C60(0xffffffffffffffc4,*(int *)(puVar4 + (u32)*pbVar5 * 0xc + 4) + -2,0x100,0x1c,0,
                 0x9e,*(int *)(puVar4 + (u32)*pbVar5 * 0xc + 4),0);
    if (param_5[1] != 0) {
      bVar1 = 0;
    }
    bStack_1 = bVar1;
    func_002C5C60(0xffffffffffffffc4,*(int *)(puVar4 + (u32)pbVar5[1] * 0xc + 4) + -2,0x100,0x1c,1,
                 0xbe,*(int *)(puVar4 + (u32)pbVar5[1] * 0xc + 4),0);
  }
  func_00294760(param_1,puVar4,uVar2 & 0xff,param_2,0);
  func_001AE550(0x3f800000,g_00772A74,&uStack_10,&bStack_1,0);
  func_0028FBD0(uStack_10,uStack_e,0,0,bStack_1);
  func_001AE550(0x3f800000,g_00772D5C,&uStack_10,&bStack_1,0);
  func_0028FE20(uStack_10,uStack_e,0,0,bStack_1);
  func_001AE550(0x3f800000,g_00772D70,&uStack_10,&bStack_1,0);
  func_00290390(uStack_10,uStack_e,0,0);
  func_001AE550(0x3f800000,g_00772D84,&uStack_10,&bStack_1,0);
  func_00290770(uStack_10,uStack_e,0,0);
  return;
}

/* 0x0029CAB0, 0x70 bytes. */
void func_0029CAB0(int param_1, int param_2, u8 *param_3)
{
  func_0029C9B0();
  func_0029C9E0(param_1,*(u32 *)
                        ((u32)param_3[1] * 4 + (u32)*param_3 * 0x78 + param_2 + 0x180),0,
               param_3[0x59]);
  return;
}

/* 0x0029CEB0, 0xFC bytes. */
void func_0029CEB0(int param_1, int param_2, int param_3, int param_4)
{
    int bVar3;
    int lVar1;
    char * pcVar4;
    int uStack_1;
    int uStack_10;
    int uStack_e;
    u32 uVar2;

  
  (*(u32 *)(g_00772D54 + 0x0)) = 0;
  lVar1 = func_001AE550(0x3f800000,g_00772D1C,&uStack_10,&uStack_1,0);
  uVar2 = lVar1 != 0 ^ 1;
  if (uVar2 == 0) {
    uVar2 = (u32)((*(u32 *)(g_00772D54 + 0x0)) != 0);
  }
  (*(u32 *)(g_00772D54 + 0x0)) = uVar2;
  func_0029A540(uStack_10,uStack_e,0,0,param_3);
  func_0029A610(0xa8,0x50,0,0,param_3,param_4);
  pcVar4 = (char *)param_3;
  uVar2 = 0xff;
  if (*pcVar4 != '\0') {
    uVar2 = (u32)(u8)pcVar4[2];
  }
  if (uVar2 == 0xff) {
    bVar3 = 0x1f;
  }
  else {
    bVar3 = pcVar4[uVar2 + 6];
  }
  if (bVar3 < 0x1f) {
    func_0029A8F0(0x154,0x68,0,0,bVar3,0);
  }
  return;
}

/* 0x0029D310, 0x118 bytes. */
void func_0029D310(int param_1, int param_2, u8 *param_3)
{
    int lVar1;
    int sStack_10;
    int sStack_e;
    int uStack_1;
    int uVar2;
    u32 uVar3;

  
  (*(u32 *)(g_00772D54 + 0x0)) = 0;
  lVar1 = func_001AE550(0x3f800000,g_00772DC0,&sStack_10,&uStack_1,0);
  uVar3 = lVar1 != 0 ^ 1;
  if (uVar3 == 0) {
    uVar3 = (u32)((*(u32 *)(g_00772D54 + 0x0)) != 0);
  }
  (*(u32 *)(g_00772D54 + 0x0)) = uVar3;
  func_0029D230(sStack_10,sStack_e,0,0,*param_3);
  func_001AE550(0x3f800000,g_00772DD4,&sStack_10,&uStack_1,0);
  func_0029B5A0(sStack_10,sStack_e,0,0,1);
  uVar2 = func_00362C10(0,*param_3);
  func_0029B1C0(sStack_10 + 0xc,sStack_e + 0x30,0,0,uVar2,0,1,1);
  func_0029B4D0(sStack_10 + 0xac,sStack_e + 0x30,0,0);
  return;
}

/* 0x002A6430, 0x38 bytes. */
void func_002A6430(void)
{
    int iVar1;
    u8 * iVar2;

  
  iVar1 = 0;
  iVar2 = g_0077BE70;
  do {
    if (*(int *)(iVar2 + 0x18) < 1) {
      return;
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 0x20;
  } while (iVar1 < 4);
  return;
}

/* 0x002A9610, 0x44 bytes. */
void func_002A9610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
  func_001ABE40(param_1,1,param_2,param_3,0,param_4,param_5,param_6);
  return;
}

/* 0x002AA020, 0x94 bytes, matching. */
void func_002AA020(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    u8 auStack_200[512];

  
  func_00147160(param_2,auStack_200,param_5,0,0);
  func_002A9EC0(param_1,auStack_200,param_3,param_4,param_6,param_7,param_8);
  return;
}

/* 0x002AA150, 0x6C bytes. */
void func_002AA150(int param_1)
{
    int uStack_1;
    int uStack_10;
    int uStack_a;
    int uStack_c;
    int uStack_e;
    int uVar1;

  
  func_001AE550(0x3f800000,g_00780310,&uStack_10,&uStack_1,0);
  uVar1 = func_0029FB70();
  func_002AA1C0(param_1,0x30,uStack_10,uStack_e,uStack_c,uStack_a,uVar1,1);
  return;
}

/* 0x002C1260, 0x54 bytes. */
int func_002C1260(u8 *param_1, int param_2, int param_3)
{
    u8 * pbStack_10;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;

  
  if (*param_1 < g_0045D5C8) {
    uStack_4 = 0;
    pbStack_10 = param_1;
    uStack_c = param_2;
    uStack_8 = param_3;
    func_001904E0(0x2c12c0,&pbStack_10);
  }
  else {
    uStack_4 = 0;
  }
  return uStack_4;
}

/* 0x002C7FA0, 0x100 bytes. */
void func_002C7FA0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    u32 auStack_10[4];
    int iVar4;
    u32 * puVar3;
    u32 uVar1;
    int uVar2;

  
  uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5c);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    uVar1 = func_00105860(uVar2,0);
    *puVar3 = uVar1;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  func_002C7C00(auStack_10[0],param_1,param_2,param_3,param_4,param_5,param_7,param_6);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    func_00105900(*puVar3,param_8);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  return;
}

/* 0x002CA060, 0xF8 bytes. */
void func_002CA060(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar4;
    u32 * puVar3;
    u32 uVar1;
    int uVar2;

  
  uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f62);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    uVar1 = func_00105860(uVar2,0);
    *puVar3 = uVar1;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  func_002C9D30(auStack_10[0],param_1,param_2,param_3,param_4,param_5,param_6);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    func_00105900(*puVar3,param_7);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  return;
}

/* 0x002CA490, 0xF8 bytes. */
void func_002CA490(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u32 auStack_10[4];
    int iVar4;
    u32 * puVar3;
    u32 uVar1;
    int uVar2;

  
  uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f62);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    uVar1 = func_00105860(uVar2,0);
    *puVar3 = uVar1;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  func_002CA160(auStack_10[0],param_1,param_2,param_3,param_4,param_5,param_6);
  iVar4 = 0;
  puVar3 = auStack_10;
  do {
    func_00105900(*puVar3,param_7);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 3);
  return;
}

/* 0x002CE160, 0x44 bytes. */
void func_002CE160(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
  func_001ABE40(param_1,0x28,param_2,param_3,0,param_4,param_5,param_6);
  return;
}

/* 0x002D6D70, 0x200 bytes. */
void func_002D6D70(void)
{
    u32 auStack_8[2];
    int iVar4;
    int iVar6;
    int lVar2;
    u32 * puVar5;
    u32 uVar1;
    u32 uVar3;

  
  if (((*(u32 *)(g_00669F60 + 0x0)) & 0x8000000) == 0) {
    uVar3 = (*(u32 *)(g_00669F60 + 0x0)) | 0x8000000;
    uVar1 = (*(u32 *)(g_00669F60 + 0x0)) & 2;
    if (uVar1 == 0) {
      iVar4 = 1;
    }
    else {
      iVar4 = 2;
    }
    auStack_8[0] = (u32)*(u8 *)((*(u32 *)(g_006A3A98 + 0x0)) + 7);
    if (uVar1 == 0) {
      auStack_8[1] = 0;
    }
    else {
      auStack_8[1] = (u32)*(u8 *)((*(u32 *)(g_006A3A98 + 0xC0)) + 7);
    }
    iVar6 = 0;
    (*(u32 *)(g_00669F60 + 0x0)) = uVar3;
    if (iVar4 != 0) {
      puVar5 = auStack_8;
      do {
        lVar2 = func_0032F1D0(*puVar5);
        *puVar5 = (u32)lVar2;
        if (0x19 < lVar2) {
          if ((lVar2 == 0x21) || (lVar2 == 0x20)) {
            *puVar5 = 0x1c;
          }
          else if (lVar2 == 0x2a) {
            *puVar5 = 0x1b;
          }
          else if (lVar2 == 0x26) {
            *puVar5 = 0x1a;
          }
          else {
            *puVar5 = 0;
          }
        }
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar6 < iVar4);
    }
    func_0020EE50();
    func_0020EB40();
    if ((*(u32 *)(g_00669F60 + 0x10)) == 0) {
      (*(u32 *)(g_005BD6B0 + 0x4)) = 0x28;
      (*(u32 *)(g_005BD6B0 + 0x0)) = 0x28;
      func_0017DF10();
    }
    else if ((*(u32 *)(g_00669F60 + 0x10)) == 3) {
      (*(u32 *)(g_005BD6B0 + 0x4)) = 0x45;
      (*(u32 *)(g_005BD6B0 + 0x0)) = 0x45;
      func_0017DF10();
    }
    else {
      if ((*(u32 *)(g_00669F60 + 0x10)) != 4) {
        return;
      }
      (*(u32 *)(g_005BD6B0 + 0x4)) = 0x45;
      (*(u32 *)(g_005BD6B0 + 0x0)) = 0x45;
      func_0017DF10();
    }
    (*(u32 *)(g_005BD6B0 + 0x0)) = (*(u32 *)(g_005BD6B0 + 0x0)) + auStack_8[0];
    (*(u32 *)(g_005BD6B0 + 0x4)) = (*(u32 *)(g_005BD6B0 + 0x4)) + auStack_8[1];
    func_0020EB60((*(u32 *)(g_005BD6B0 + 0x0)),1,1);
    if (uVar1 != 0) {
      func_0020EB60((*(u32 *)(g_005BD6B0 + 0x4)),0,1);
    }
    func_0020E960(0,1);
    func_00102960(0);
  }
  return;
}

/* 0x002D8240, 0x3C bytes, matching. */
void func_002D8240(u32 *param_1)
{
    u32 uVar1;

  
  uVar1 = param_1[3];
  func_001A1960(*param_1,uVar1,param_1[1]);
  func_002DAE60(uVar1,1);
  return;
}

/* 0x002DA090, 0x228 bytes. */
int func_002DA090(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  (*(u32 *)(g_00799A70 + 0x0)) = 1;
  lVar3 = 0;
  if ((*(u32 *)(g_00799A70 + 0x78)) == 5) {
    (*(u32 *)(g_00799A70 + 0x28)) = 0;
  }
  else {
    (*(u32 *)(g_00799A70 + 0x28)) = (u32)*(u8 *)((*(u32 *)(g_00799A70 + 0x78)) * 0x128 + 0x6934b4);
  }
  if ((*(u32 *)(g_00799A70 + 0x40)) == 0) {
    if ((*(u32 *)(g_00799A70 + 0x10)) == 0x14) {
      if ((*(u32 *)(g_00799A70 + 0x78)) == 1) {
        func_002D8950(g_00799A70);
      }
      else if ((*(u32 *)(g_00799A70 + 0x78)) == 0) {
        lVar3 = func_002D8C30(g_00799A70,0);
      }
      else if ((*(u32 *)(g_00799A70 + 0x6C)) == 0) {
        func_002D83E0(g_00799A70);
      }
      else {
        lVar2 = func_0022DCD0();
        if (lVar2 != 0) {
          func_002D8480(g_00799A70);
        }
      }
    }
    else if ((*(u32 *)(g_00799A70 + 0x10)) == 0x16) {
      if ((*(u32 *)(g_00799A70 + 0x30)) == 0) {
        lVar3 = 2;
      }
      else {
        lVar3 = 1;
      }
    }
    else {
      lVar2 = func_0022DD60();
      if ((lVar2 == -1) || (lVar2 == 2)) {
        func_002D9EE0(g_00799A70);
      }
      lVar2 = func_0022DCD0();
      if (lVar2 != 0) {
        func_002D9640(g_00799A70);
      }
    }
  }
  else {
    func_002D8EE0(g_00799A70);
  }
  if ((*(u32 *)(g_00799A70 + 0x78)) == 5) {
    bVar1 = false;
  }
  else {
    bVar1 = false;
    if (lVar3 != 0) {
      bVar1 = *(char *)((*(u32 *)(g_00799A70 + 0x78)) * 0x128 + 0x6934b3) != '\0';
    }
  }
  if (bVar1) {
    lVar3 = 0;
    (*(u32 *)(g_00799A70 + 0x10)) = 0x16;
  }
  return lVar3;
}

/* 0x002DAC30, 0x220 bytes. */
int func_002DAC30(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar3 = 0;
  if ((*(u32 *)(g_00799A80 + 0x68)) == 5) {
    (*(u32 *)(g_00799A80 + 0x18)) = 0;
  }
  else {
    (*(u32 *)(g_00799A80 + 0x18)) = (u32)*(u8 *)((*(u32 *)(g_00799A80 + 0x68)) * 0x128 + 0x6934b4);
  }
  if ((*(u32 *)(g_00799A80 + 0x30)) == 0) {
    if ((*(u32 *)(g_00799A80 + 0x0)) == 0x14) {
      if ((*(u32 *)(g_00799A80 + 0x68)) == 1) {
        func_002D8950(g_00799A70);
      }
      else if ((*(u32 *)(g_00799A80 + 0x68)) == 0) {
        lVar3 = func_002D8C30(g_00799A70,0);
      }
      else if ((*(u32 *)(g_00799A80 + 0x5C)) == 0) {
        func_002D83E0(g_00799A70,2);
      }
      else {
        lVar2 = func_0022DCD0();
        if (lVar2 != 0) {
          func_002D8480(g_00799A70);
        }
      }
    }
    else if ((*(u32 *)(g_00799A80 + 0x0)) == 0x16) {
      if ((*(u32 *)(g_00799A80 + 0x20)) == 0) {
        lVar3 = 2;
      }
      else {
        lVar3 = 1;
      }
    }
    else {
      lVar2 = func_0022DD60();
      if ((lVar2 == -1) || (lVar2 == 2)) {
        func_002DA8C0(g_00799A70);
      }
      lVar2 = func_0022DCD0();
      if (lVar2 != 0) {
        func_002DA2D0(g_00799A70);
      }
    }
  }
  else {
    func_002D8EE0(g_00799A70);
  }
  if ((*(u32 *)(g_00799A80 + 0x68)) == 5) {
    bVar1 = false;
  }
  else {
    bVar1 = false;
    if (lVar3 != 0) {
      bVar1 = *(char *)((*(u32 *)(g_00799A80 + 0x68)) * 0x128 + 0x6934b3) != '\0';
    }
  }
  if (bVar1) {
    lVar3 = 0;
    (*(u32 *)(g_00799A80 + 0x0)) = 0x16;
  }
  return lVar3;
}

/* 0x002DB4F0, 0x60 bytes. */
void func_002DB4F0(void)
{
    u8 auStack_d0[208];
    int uVar1;

  
  uVar1 = func_0019FB00();
  func_002DB3C0(auStack_d0);
  func_003BFC30(auStack_d0,uVar1,g_0045D5F8 == 5);
  func_002D8060(0);
  g_0045D5FC = 1;
  (*(u32 *)(g_00799A70 + 0x0)) = g_0045D5F8;
  return;
}

/* 0x002DB800, 0x78 bytes, matching. */
void func_002DB800(void)
{
    u8 auStack_d0[208];
    int uVar1;

  
  uVar1 = func_0019FB00();
  func_002DB3C0(auStack_d0);
  func_003BFC30(auStack_d0,uVar1,0);
  func_002D8060(0);
  (*(u32 *)(g_00799A70 + 0x0)) = g_0045D5F0;
  if (g_0045D5F0 == 4) {
    g_0045D5F4 = 2;
  }
  else if (g_0045D5F0 == 7) {
    g_0045D5F4 = 1;
  }
  return;
}

/* 0x002E0000, 0x3C bytes. */
void func_002E0000(int param_1)
{
  func_002DFF70();
  func_002456C0(param_1,0x442a00,0x442ba0);
  return;
}

/* 0x002E0040, 0x3C bytes. */
void func_002E0040(int param_1)
{
  func_002DFF40();
  func_002456C0(param_1,0x442a00,0x442ba8);
  return;
}

/* 0x002E0640, 0xAC bytes. */
void func_002E0640(u8 *param_1, int param_2, int param_3)
{
    int cVar1;
    u32 * puVar3;
    int uVar2;

  
  uVar2 = *(u16 *)(param_1 + 0x54);
  cVar1 = func_001FF100(uVar2,10);
  if (cVar1 == 'f') {
    func_002DED90(param_1,0x33);
    func_002470B0(param_1);
  }
  else {
    uVar2 = func_001FF120(uVar2);
    if (param_2 == 0) {
      puVar3 = &g_700000C0;
    }
    else {
      puVar3 = (u32 *)((int)param_2 + 0x90);
    }
    func_002DFEE0(param_1,param_3,puVar3,0,uVar2);
  }
  return;
}

/* 0x002E14E0, 0x28 bytes. */
void func_002E14E0(int param_1, int param_2, int param_3)
{
    u32 uStack_4;

  
  uStack_4 = param_3;
  func_002456F0(param_1,param_2,0x4428a0,&uStack_4);
  return;
}

/* 0x002E1820, 0x9C bytes. */
void func_002E1820(u8 *param_1)
{
    int cVar1;
    int lVar2;

  
  cVar1 = *(char *)(param_1 + 0x7c);
  if (cVar1 == '\x03') {
    lVar2 = func_00239830();
    if (lVar2 == 0) {
      func_002E1700(param_1);
    }
  }
  else if (cVar1 == '\x02') {
    func_002E1700();
  }
  else if (cVar1 == '\x01') {
    func_002E16A0();
  }
  else if (cVar1 == '\0') {
    func_002E15A0();
  }
  return;
}

/* 0x002EF080, 0xCC bytes. */
void func_002EF080(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int iVar2;

  
  func_002C7310(param_2,param_3,0,param_4,param_5,0x80);
  iVar1 = (int)param_4;
  if (param_4 < 0) {
    iVar1 = iVar1 + 1;
  }
  iVar2 = (int)param_5;
  if (param_5 < 0) {
    iVar2 = iVar2 + 1;
  }
  func_001ABE40(param_1,0x3c,(int)param_2 + (iVar1 >> 1),(int)param_3 + (iVar2 >> 1),0,
               0xffffffffffffffff,0xffffffffffffffff,param_6);
  return;
}

/* 0x00320F60, 0x178 bytes. */
int func_00320F60(void)
{
    int aiStack_70[28];
    int iVar1;
    int iVar4;
    int iVar5;
    int iVar6;
    int lVar2;
    int * piVar3;

  
  iVar6 = 0;
  iVar4 = 0;
  lVar2 = func_0030AB90();
  if (0 < lVar2) {
    piVar3 = aiStack_70;
    do {
      lVar2 = func_002F8CB0(iVar6);
      if (lVar2 != 0) {
        iVar5 = iVar6 + 1;
        iVar1 = func_0030AB90();
        if (iVar5 < iVar1) {
          do {
            lVar2 = func_002F9C90(iVar6,iVar5);
            if (lVar2 == 1) {
              iVar1 = func_002F9D50(iVar6,iVar5);
              iVar1 = iVar1 + -1;
              func_002FAEA0(iVar6,iVar5,iVar1,1);
              if (iVar1 < 1) {
                func_002FAF30(iVar6,iVar5);
              }
              if ((iVar1 == 0) &&
                 ((lVar2 = func_002FB2A0(iVar6), lVar2 != 0 ||
                  (lVar2 = func_002FB2A0(iVar5), lVar2 != 0)))) {
                lVar2 = func_002FB2A0(iVar6);
                iVar1 = iVar6;
                if (lVar2 != 0) {
                  iVar1 = iVar5;
                }
                *piVar3 = iVar1;
                iVar4 = iVar4 + 1;
                piVar3 = piVar3 + 1;
              }
            }
            iVar5 = iVar5 + 1;
            iVar1 = func_0030AB90();
          } while (iVar5 < iVar1);
        }
      }
      iVar6 = iVar6 + 1;
      iVar1 = func_0030AB90();
    } while (iVar6 < iVar1);
  }
  if (iVar4 != 0) {
    func_0030E390(10,0,0xffffffffffffffff,0xffffffffffffffff,aiStack_70,iVar4);
  }
  return 0;
}

/* 0x003217D0, 0x250 bytes. */
int func_003217D0(void)
{
    u32 auStack_680[416];
    int bVar1;
    int iVar10;
    int iVar3;
    int iVar6;
    int iVar8;
    int iVar9;
    int lVar4;
    u32 * puVar2;
    u32 * puVar7;
    int uVar5;

  
  puVar2 = (u32 *)func_002F7B10();
  lVar4 = func_00327CC0();
  if (((lVar4 == 0) && (lVar4 = func_00327A60(), lVar4 != 0)) &&
     (lVar4 = func_00327C00(), lVar4 != 10)) {
    iVar10 = 0;
    iVar3 = func_002F7D90(0,0x2f85e0,0,0,0,0);
    iVar8 = 0;
    if (0 < iVar3) {
      puVar7 = auStack_680;
      do {
        lVar4 = func_002F75C0(*puVar2);
        if (lVar4 != 0) {
          iVar10 = iVar10 + 1;
          *puVar7 = *puVar2;
          puVar7 = puVar7 + 1;
        }
        iVar8 = iVar8 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar8 < iVar3);
    }
    iVar3 = 0;
    do {
      bVar1 = false;
      if (-1 < iVar3) {
        iVar8 = func_0030AB90();
        bVar1 = iVar3 < iVar8;
      }
      if ((bVar1) && (lVar4 = func_002F8CB0(iVar3), lVar4 != 0)) {
        iVar9 = 0;
        iVar8 = func_002F7D90(0,0x2f8250,iVar3,0,1,0);
        puVar2 = (u32 *)func_002F7B10();
        iVar6 = 0;
        if (0 < iVar8) {
          puVar7 = auStack_680 + iVar10;
          do {
            lVar4 = func_002F75C0(*puVar2);
            if (lVar4 != 0) {
              iVar10 = iVar10 + 1;
              iVar9 = iVar9 + 1;
              *puVar7 = *puVar2;
              puVar7 = puVar7 + 1;
            }
            iVar6 = iVar6 + 1;
            puVar2 = puVar2 + 1;
          } while (iVar6 < iVar8);
        }
        lVar4 = func_002FB2A0(iVar3);
        if ((lVar4 == 0) && (iVar8 != iVar9)) {
          uVar5 = func_002F8F20(iVar3);
          lVar4 = func_002F75C0(uVar5);
          if (lVar4 != 0) {
            auStack_680[iVar10] = (int)uVar5;
            iVar10 = iVar10 + 1;
          }
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
    if (iVar10 != 0) {
      func_002F7B20(0,auStack_680,iVar10);
      func_0030E390(3,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,auStack_680,iVar10);
    }
  }
  return 0;
}

/* 0x00323F10, 0x144 bytes. */
int func_00323F10(int param_1, int param_2, int *param_3, u8 *param_4)
{
    u32 auStack_70[28];
    int iVar1;
    int iVar6;
    int lVar3;
    u32 * puVar5;
    u32 uVar2;
    int uVar4;

  
  lVar3 = func_003279B0();
  if (lVar3 == 2) {
    uVar2 = 0;
  }
  else {
    iVar1 = func_002FB320(param_2,auStack_70);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar4 = func_002FB2D0(param_2);
      if ((lVar3 == 1) && (iVar6 = 0, 0 < iVar1)) {
        puVar5 = auStack_70;
        do {
          lVar3 = func_0030C280(uVar4,*puVar5);
          if (lVar3 != 0) {
            return 0;
          }
          iVar6 = iVar6 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar6 < iVar1);
      }
      iVar6 = 0;
      if (0 < iVar1) {
        puVar5 = auStack_70;
        do {
          func_0030AF20(*puVar5,param_1);
          func_00323840(*puVar5);
          iVar6 = iVar6 + 1;
          uVar2 = *puVar5;
          puVar5 = puVar5 + 1;
          *(u32 *)(param_4 + *param_3 * 4) = uVar2;
          *param_3 = *param_3 + 1;
        } while (iVar6 < iVar1);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}

/* 0x003246C0, 0x11C bytes. */
void func_003246C0(int param_1, u32 *param_2)
{
    int bVar1;
    int iVar3;
    int iVar5;
    u32 * puVar2;
    u32 * puVar4;

  
  puVar2 = (u32 *)func_002F7B10();
  iVar3 = func_002F7D90(0,0x2f7ec0,param_1,0,1,0);
  iVar5 = 0;
  if (0 < iVar3) {
    if (8 < iVar3) {
      bVar1 = false;
      if ((-1 < iVar3) && (iVar3 < 0x7fffffff)) {
        bVar1 = true;
      }
      if (bVar1) {
        puVar4 = param_2;
        do {
          iVar5 = iVar5 + 8;
          *puVar4 = *puVar2;
          puVar4[1] = puVar2[1];
          puVar4[2] = puVar2[2];
          puVar4[3] = puVar2[3];
          puVar4[4] = puVar2[4];
          puVar4[5] = puVar2[5];
          puVar4[6] = puVar2[6];
          puVar4[7] = puVar2[7];
          puVar2 = puVar2 + 8;
          puVar4 = puVar4 + 8;
        } while (iVar5 < iVar3 + -8);
      }
    }
    if (iVar5 < iVar3) {
      param_2 = param_2 + iVar5;
      do {
        iVar5 = iVar5 + 1;
        *param_2 = *puVar2;
        puVar2 = puVar2 + 1;
        param_2 = param_2 + 1;
      } while (iVar5 < iVar3);
    }
  }
  return;
}

/* 0x00326000, 0x1BC bytes. */
int func_00326000(int param_1, int *param_2, u8 *param_3, int *param_4, u8 *param_5)
{
    u8 auStack_20[32];
    u8 auStack_40[32];
    int bVar1;
    int iVar3;
    int lVar4;
    u32 uVar2;
    int uVar5;

  
  lVar4 = func_00375BF0();
  if (lVar4 == 0) {
    if ((*param_2 == 0) && (*param_4 == 0)) {
      uVar2 = 1;
    }
    else {
      if (*param_2 == 0) {
        if (*param_4 != 0) {
          iVar3 = *param_4 + -1;
          *param_4 = iVar3;
          iVar3 = *(int *)(param_5 + iVar3 * 4);
          bVar1 = false;
          if ((-1 < iVar3) && (iVar3 < 0x19f)) {
            bVar1 = true;
          }
          if (!bVar1) {
            return 0;
          }
          uVar5 = func_002F2890();
          func_00120928(auStack_20,uVar5);
          uVar5 = func_00390760(0xc4);
          func_001204B0(g_007B4E60,uVar5,auStack_20);
        }
      }
      else {
        iVar3 = *param_2;
        *param_2 = iVar3 + -1;
        iVar3 = *(int *)(param_3 + (iVar3 + -1) * 4);
        bVar1 = false;
        if ((-1 < iVar3) && (iVar3 < 0x19f)) {
          bVar1 = true;
        }
        if (!bVar1) {
          return 0;
        }
        uVar5 = func_002F2890();
        func_00120928(auStack_20,uVar5);
        uVar5 = func_002F8F20(param_1);
        uVar5 = func_002F2890(uVar5);
        func_00120928(auStack_40,uVar5);
        uVar5 = func_00390760(0xc3);
        func_001204B0(g_007B4E60,uVar5,auStack_20,auStack_40);
      }
      func_00374EE0(g_007B4E60);
      uVar2 = 0;
    }
  }
  else {
    func_00375B90();
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x003273E0, 0x2B0 bytes. */
void func_003273E0(void)
{
    u8 * iVar2;
    int iVar3;
    int uVar1;

  
  func_003273D0();
  iVar2 = g_0068DDE0;
  (*(u16 *)(g_0068EFF0 + 0x0)) = 0;
  func_0011ED38(0x68f007,0,0xd);
  func_0011ED38(0x68f014,0,5);
  func_0011ED38(0x68f058,0,5);
  func_0011ED38(0x68f019,0,0x1c);
  func_0011ED38(0x68e5ec,0,0x9ec);
  func_0011ED38(0x68de40,0,0x110);
  func_0011ED38(0x68dfa0,0,0x618);
  func_0011ED38(0x68e5b8,0,0x34);
  func_00327690(g_7000015C);
  func_003276B0(0);
  func_00327710(0);
  func_00327750(0);
  func_00327780(0x19f);
  func_00327830(0x19f);
  func_00327BD0(6);
  func_00327C10(2);
  func_00327C50(0);
  func_00327CF0(0x19);
  func_00327DC0(0);
  func_00327DF0(3);
  func_00327E30(6);
  func_00327E60(0);
  func_00327F00(0x19);
  func_00327F70(0x19);
  func_00327FE0(0x19);
  func_00328050(0x19);
  func_003280C0(5);
  func_003297A0(0);
  func_003297E0(0);
  func_00329820(0);
  func_003282E0();
  func_00327880(1);
  func_003278D0(1);
  func_00327920(1);
  func_00327970(0);
  func_003279D0(2);
  func_00327A30(0);
  iVar3 = 0;
  do {
    func_003282F0(100,iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 5);
  iVar3 = 0;
  do {
    func_00328600(100,iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 5);
  iVar3 = 0;
  do {
    uVar1 = func_00328B30(iVar3);
    func_00327190(iVar3,uVar1);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x79);
  iVar3 = 0;
  do {
    func_00327A80(0x19f,iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  iVar3 = 0;
  do {
    func_00329450(iVar3,4);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 2);
  func_00328CB0();
  func_00328E70();
  func_00329030();
  iVar3 = 0;
  do {
    *(u32 *)(iVar2 + 0x170) = 0xffffffff;
    iVar3 = iVar3 + 5;
    *(u32 *)(iVar2 + 0x174) = 0;
    *(u32 *)(iVar2 + 0x178) = 0xffffffff;
    *(u32 *)(iVar2 + 0x17c) = 0;
    *(u32 *)(iVar2 + 0x180) = 0xffffffff;
    *(u32 *)(iVar2 + 0x184) = 0;
    *(u32 *)(iVar2 + 0x188) = 0xffffffff;
    *(u32 *)(iVar2 + 0x18c) = 0;
    *(u32 *)(iVar2 + 400) = 0xffffffff;
    *(u32 *)(iVar2 + 0x194) = 0;
    iVar2 = iVar2 + 0x28;
  } while (iVar3 < 10);
  func_0030CC80();
  (*(u8 *)(g_0068EFF0 + 0x6D)) = 0;
  return;
}

/* 0x0032CFF0, 0xF0 bytes. */
void func_0032CFF0(void)
{
    u8 auStack_150[336];
    u8 * iVar1;
    int iVar2;
    int lVar3;

  
  lVar3 = func_00329D60();
  if (lVar3 != 0) {
    iVar1 = (u8 *)func_00329D60();
    iVar2 = func_0032B180();
    func_00120928(auStack_150,*(u32 *)(iVar1 + iVar2 * 4 + 0x24));
    iVar1 = (u8 *)func_00329D60();
    iVar2 = func_0032B180();
    lVar3 = func_001207E0(*(u32 *)(iVar1 + iVar2 * 4 + 0x24),0x447a30);
    if (lVar3 != 0) {
      func_001206B0(auStack_150,0x447a38);
    }
    lVar3 = func_0032B180();
    iVar1 = (u8 *)func_00329D60();
    func_001206B0(auStack_150,*(u32 *)(iVar1 + (lVar3 != 0 ^ 1) * 4 + 0x24));
    func_0032CF00(auStack_150);
  }
  lVar3 = func_00329D60();
  if (lVar3 != 0) {
    iVar1 = (u8 *)func_00329D60();
    func_0032C060(*(int *)(iVar1 + 0x2c) != 0);
  }
  func_0032C080();
  func_0032C9E0();
  return;
}

/* 0x0032D270, 0x74 bytes. */
void func_0032D270(int param_1)
{
    int uVar1;

  
  if ((param_1 < 0x253) || (0x25b < param_1)) {
    if ((*(u32 *)(g_0045D898 + 0x0)) == 0xd) {
      uVar1 = func_00337A10();
      func_002F2970(uVar1);
    }
    else {
      uVar1 = func_00337A10();
      func_002F2890(uVar1);
    }
  }
  else {
    func_00372540((int)param_1 + -0x253);
  }
  return;
}

/* 0x0032FF70, 0x150 bytes. */
void func_0032FF70(int param_1)
{
    int aiStack_10[4];
    int bVar1;
    int iVar2;
    int iVar5;
    int iVar6;
    int lVar3;
    int * piVar4;
    u32 uVar7;

  
  aiStack_10[0] = g_0045D028;
  aiStack_10[1] = g_0045D02C;
  aiStack_10[2] = func_00337A10(0x28);
  aiStack_10[3] = func_00337A10(0x29);
  func_0032E8A0(0,param_1);
  uVar7 = 0;
  do {
    iVar6 = -1;
    bVar1 = false;
    if ((-1 < (int)uVar7) && ((int)uVar7 < 0x19f)) {
      bVar1 = true;
    }
    if (((bVar1) && (uVar7 != param_1)) && (lVar3 = func_0032EB40(param_1,uVar7,0), lVar3 != 0)) {
      iVar2 = func_002F34E0(uVar7);
      iVar5 = 0;
      piVar4 = aiStack_10;
      do {
        if (*piVar4 < iVar2) {
          iVar6 = iVar5;
          break;
        }
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar5 < 2);
      if (iVar6 == 1) {
        aiStack_10[1] = iVar2;
        aiStack_10[3] = uVar7;
      }
      else if (iVar6 == 0) {
        aiStack_10[3] = aiStack_10[2];
        aiStack_10[1] = aiStack_10[0];
        aiStack_10[0] = iVar2;
        aiStack_10[2] = uVar7;
      }
    }
    uVar7 = uVar7 + 1;
    if (0x19e < uVar7) {
      func_0032E8A0(1,aiStack_10[2]);
      func_0032E8A0(2,aiStack_10[3]);
      return;
    }
  } while( true );
}

/* 0x00330650, 0x9C0 bytes. */
int func_00330650(int param_1)
{
    int aiStack_200[128];
    int iVar3;
    int lVar1;
    int * piVar2;

  
  (*(u32 *)(g_0045D73C + 0x0)) = func_0032FF20();
  iVar3 = 0;
  piVar2 = aiStack_200;
  do {
    *piVar2 = -1;
    iVar3 = iVar3 + 8;
    piVar2[1] = -1;
    piVar2[2] = -1;
    piVar2[3] = -1;
    piVar2[4] = -1;
    piVar2[5] = -1;
    piVar2[6] = -1;
    piVar2[7] = -1;
    piVar2 = piVar2 + 8;
  } while (iVar3 < 0x80);
  switch(param_1) {
  case 0:
    aiStack_200[0] = 0xc;
    aiStack_200[1] = 0xd;
    aiStack_200[2] = 0xe;
    break;
  case 1:
    aiStack_200[0] = 0x14;
    aiStack_200[1] = 0x15;
    aiStack_200[2] = 0x16;
    break;
  case 2:
    aiStack_200[0] = 0x36;
    aiStack_200[1] = 0x17;
    break;
  case 3:
    aiStack_200[0] = 0x35;
    aiStack_200[1] = 0x34;
    aiStack_200[2] = 0x77;
    aiStack_200[3] = 0x78;
    break;
  case 4:
    aiStack_200[0] = 0x10;
    aiStack_200[1] = 0x11;
    aiStack_200[2] = 0x12;
    break;
  case 5:
    aiStack_200[0] = 0x10b;
    aiStack_200[1] = 0x122;
    aiStack_200[2] = 0x16b;
    aiStack_200[3] = 0x1b6;
    aiStack_200[4] = 0x1bc;
    aiStack_200[5] = 0xf2;
    aiStack_200[6] = 0xf3;
    aiStack_200[7] = 0x8a;
    aiStack_200[8] = 0x8b;
    aiStack_200[9] = 0x90;
    aiStack_200[10] = 0x93;
    aiStack_200[0xb] = 0x94;
    aiStack_200[0xc] = 0x96;
    aiStack_200[0xd] = 0x97;
    aiStack_200[0xe] = 0x9b;
    aiStack_200[0xf] = 0x9c;
    aiStack_200[0x10] = 0x9d;
    aiStack_200[0x11] = 0x9f;
    aiStack_200[0x12] = 0xa2;
    aiStack_200[0x13] = 0xa3;
    aiStack_200[0x14] = 0xa4;
    aiStack_200[0x15] = 0xa5;
    aiStack_200[0x16] = 0xaa;
    aiStack_200[0x17] = 0xae;
    aiStack_200[0x18] = 0xaf;
    aiStack_200[0x19] = 0xb0;
    aiStack_200[0x1a] = 0xb1;
    aiStack_200[0x1b] = 0xb2;
    aiStack_200[0x1c] = 0xbc;
    aiStack_200[0x1d] = 0xbf;
    aiStack_200[0x1e] = 0xef;
    aiStack_200[0x1f] = 0xc0;
    aiStack_200[0x20] = 0xf0;
    aiStack_200[0x21] = 0xc1;
    aiStack_200[0x22] = 0xc2;
    aiStack_200[0x23] = 0xc3;
    aiStack_200[0x24] = 0xc4;
    aiStack_200[0x25] = 0xc6;
    aiStack_200[0x26] = 199;
    aiStack_200[0x27] = 200;
    aiStack_200[0x28] = 0xc9;
    aiStack_200[0x29] = 0xca;
    aiStack_200[0x2a] = 0xd1;
    aiStack_200[0x2b] = 0xd4;
    aiStack_200[0x2c] = 0xd8;
    aiStack_200[0x2d] = 0xeb;
    aiStack_200[0x2e] = 0xec;
    aiStack_200[0x2f] = 0xed;
    aiStack_200[0x30] = 0xf1;
    aiStack_200[0x31] = 0xf4;
    aiStack_200[0x32] = 0xf5;
    aiStack_200[0x33] = 0xf6;
    aiStack_200[0x34] = 0x101;
    aiStack_200[0x35] = 0x104;
    aiStack_200[0x36] = 0x105;
    aiStack_200[0x37] = 0x106;
    aiStack_200[0x38] = 0x108;
    aiStack_200[0x39] = 0x109;
    aiStack_200[0x3a] = 0x10a;
    aiStack_200[0x3b] = 0x10d;
    aiStack_200[0x3c] = 0x110;
    aiStack_200[0x3d] = 0x111;
    aiStack_200[0x3e] = 0x112;
    aiStack_200[0x3f] = 0x115;
    aiStack_200[0x40] = 0x116;
    aiStack_200[0x41] = 0x117;
    aiStack_200[0x42] = 0x119;
    aiStack_200[0x43] = 0x11b;
    aiStack_200[0x44] = 0x11c;
    aiStack_200[0x45] = 0x11d;
    aiStack_200[0x46] = 0x11e;
    aiStack_200[0x47] = 0x11f;
    aiStack_200[0x48] = 0x121;
    aiStack_200[0x49] = 0x123;
    aiStack_200[0x4a] = 0x12e;
    aiStack_200[0x4b] = 0x12f;
    aiStack_200[0x4c] = 0x132;
    aiStack_200[0x4d] = 0x137;
    aiStack_200[0x4e] = 0x138;
    aiStack_200[0x4f] = 0x13c;
    aiStack_200[0x50] = 0x13b;
    aiStack_200[0x51] = 0x142;
    aiStack_200[0x52] = 0x143;
    aiStack_200[0x53] = 0x145;
    aiStack_200[0x54] = 0x146;
    aiStack_200[0x55] = 0x148;
    aiStack_200[0x56] = 0x149;
    aiStack_200[0x57] = 0x14a;
    aiStack_200[0x58] = 0x14e;
    aiStack_200[0x59] = 0x14f;
    aiStack_200[0x5a] = 0x154;
    aiStack_200[0x5b] = 0x155;
    aiStack_200[0x5c] = 0x157;
    aiStack_200[0x5d] = 0x158;
    aiStack_200[0x5e] = 0x159;
    aiStack_200[0x5f] = 0x15b;
    aiStack_200[0x60] = 0x15c;
    aiStack_200[0x61] = 0x15d;
    aiStack_200[0x62] = 0x168;
    aiStack_200[99] = 0x169;
    aiStack_200[100] = 0x16a;
    aiStack_200[0x65] = 0x16c;
    break;
  case 6:
    aiStack_200[0] = 0x87;
    aiStack_200[1] = 0x92;
    aiStack_200[2] = 0xab;
    aiStack_200[3] = 0xb3;
    aiStack_200[4] = 0xb4;
    aiStack_200[5] = 0xb5;
    aiStack_200[6] = 0xd0;
    aiStack_200[7] = 0xd2;
    aiStack_200[8] = 0xea;
    aiStack_200[9] = 0xee;
    aiStack_200[10] = 0xfa;
    aiStack_200[0xb] = 0xfb;
    aiStack_200[0xc] = 0xfc;
    aiStack_200[0xd] = 0xfd;
    aiStack_200[0xe] = 0xfe;
    aiStack_200[0xf] = 0x10f;
    aiStack_200[0x10] = 0x114;
    aiStack_200[0x11] = 0x11a;
    aiStack_200[0x12] = 300;
    aiStack_200[0x13] = 0x141;
    aiStack_200[0x14] = 0x28;
    break;
  case 7:
    aiStack_200[0] = 0x1a0;
    aiStack_200[1] = 0x178;
    aiStack_200[2] = 0x186;
    aiStack_200[3] = 0x196;
    aiStack_200[4] = 0x1ad;
    aiStack_200[5] = 0x89;
    aiStack_200[6] = 0x8c;
    aiStack_200[7] = 0x8d;
    aiStack_200[8] = 0x8f;
    aiStack_200[9] = 0x91;
    aiStack_200[10] = 0x95;
    aiStack_200[0xb] = 0x9e;
    aiStack_200[0xc] = 0xa0;
    aiStack_200[0xd] = 0xa1;
    aiStack_200[0xe] = 0xa6;
    aiStack_200[0xf] = 0xa7;
    aiStack_200[0x10] = 0xa8;
    aiStack_200[0x11] = 0xa9;
    aiStack_200[0x12] = 0xac;
    aiStack_200[0x13] = 0xad;
    aiStack_200[0x14] = 0xb6;
    aiStack_200[0x15] = 0xb7;
    aiStack_200[0x16] = 0xb8;
    aiStack_200[0x17] = 0xb9;
    aiStack_200[0x18] = 0xba;
    aiStack_200[0x19] = 0xbb;
    aiStack_200[0x1a] = 0xbd;
    aiStack_200[0x1b] = 0xbe;
    aiStack_200[0x1c] = 0xc5;
    aiStack_200[0x1d] = 0xcb;
    aiStack_200[0x1e] = 0xce;
    aiStack_200[0x1f] = 0xd5;
    aiStack_200[0x20] = 0xd6;
    aiStack_200[0x21] = 0xd7;
    aiStack_200[0x22] = 0xda;
    aiStack_200[0x23] = 0xdb;
    aiStack_200[0x24] = 0xde;
    aiStack_200[0x25] = 0xe0;
    aiStack_200[0x26] = 0xe1;
    aiStack_200[0x27] = 0xe4;
    aiStack_200[0x28] = 0xe5;
    aiStack_200[0x29] = 0xe6;
    aiStack_200[0x2a] = 0xe7;
    aiStack_200[0x2b] = 0xe8;
    aiStack_200[0x2c] = 0xf8;
    aiStack_200[0x2d] = 0xf9;
    aiStack_200[0x2e] = 0x100;
    aiStack_200[0x2f] = 0x107;
    aiStack_200[0x30] = 0x10c;
    aiStack_200[0x31] = 0x10e;
    aiStack_200[0x32] = 0x113;
    aiStack_200[0x33] = 0x120;
    aiStack_200[0x34] = 0x125;
    aiStack_200[0x35] = 0x127;
    aiStack_200[0x36] = 0x128;
    aiStack_200[0x37] = 0x129;
    aiStack_200[0x38] = 0x12a;
    aiStack_200[0x39] = 299;
    aiStack_200[0x3a] = 0x130;
    aiStack_200[0x3b] = 0x131;
    aiStack_200[0x3c] = 0x13a;
    aiStack_200[0x3d] = 0x13d;
    aiStack_200[0x3e] = 0x13e;
    aiStack_200[0x3f] = 0x13f;
    aiStack_200[0x40] = 0x147;
    aiStack_200[0x41] = 0x14b;
    aiStack_200[0x42] = 0x14c;
    aiStack_200[0x43] = 0x14d;
    aiStack_200[0x44] = 0x156;
    aiStack_200[0x45] = 0x15a;
    aiStack_200[0x46] = 0x15e;
    aiStack_200[0x47] = 0x15f;
    aiStack_200[0x48] = 0x160;
    aiStack_200[0x49] = 0x161;
    aiStack_200[0x4a] = 0x162;
    aiStack_200[0x4b] = 0x163;
    aiStack_200[0x4c] = 0x164;
    aiStack_200[0x4d] = 0x165;
    aiStack_200[0x4e] = 0x167;
    aiStack_200[0x4f] = 0x88;
    aiStack_200[0x50] = 0x98;
    aiStack_200[0x51] = 0xcc;
    aiStack_200[0x52] = 0xcd;
    aiStack_200[0x53] = 0xd3;
    aiStack_200[0x54] = 0xd9;
    aiStack_200[0x55] = 0xdc;
    aiStack_200[0x56] = 0xdd;
    aiStack_200[0x57] = 0xdf;
    aiStack_200[0x58] = 0xe2;
    aiStack_200[0x59] = 0xe3;
    aiStack_200[0x5a] = 0xe9;
    aiStack_200[0x5b] = 0xf7;
    aiStack_200[0x5c] = 0xff;
    aiStack_200[0x5d] = 0x118;
    aiStack_200[0x5e] = 0x124;
    aiStack_200[0x5f] = 0x126;
    aiStack_200[0x60] = 0x134;
    aiStack_200[0x61] = 0x136;
    aiStack_200[0x62] = 0x139;
    aiStack_200[99] = 0x144;
    aiStack_200[100] = 0x150;
    aiStack_200[0x65] = 0x151;
    aiStack_200[0x66] = 0x152;
    aiStack_200[0x67] = 0x153;
    aiStack_200[0x68] = 0x166;
    aiStack_200[0x69] = 0x22;
    aiStack_200[0x6a] = 0x23;
    aiStack_200[0x6b] = 0x24;
    aiStack_200[0x6c] = 0x25;
    break;
  case 8:
    aiStack_200[0] = 0x3b;
    aiStack_200[1] = 0x3c;
    break;
  case 9:
    aiStack_200[0] = 0x3a;
    break;
  case 10:
    aiStack_200[0] = 0x19c;
    aiStack_200[1] = 0x8e;
    aiStack_200[2] = 0x99;
    aiStack_200[3] = 0x9a;
    aiStack_200[4] = 0x102;
    aiStack_200[5] = 0x103;
    aiStack_200[6] = 0x12d;
    aiStack_200[7] = 0x133;
    break;
  case 0xb:
    aiStack_200[0] = 0x135;
    aiStack_200[1] = 0xcf;
    aiStack_200[2] = 0x140;
    break;
  case 0xe:
    aiStack_200[0] = 0x18;
    aiStack_200[1] = 0x14;
  }
  if (aiStack_200[0] != -1) {
    iVar3 = aiStack_200[(*(u32 *)(g_0045D73C + 0x0))];
    while (iVar3 != -1) {
      iVar3 = -1;
      lVar1 = func_003D2F80();
      if (lVar1 != 0) {
        iVar3 = aiStack_200[(*(u32 *)(g_0045D73C + 0x0))];
      }
      (*(u32 *)(g_0045D73C + 0x0)) = (*(u32 *)(g_0045D73C + 0x0)) + 1;
      func_0032FF10();
      if (iVar3 != -1) {
        if (param_1 == 6) {
          func_0032FF10(0);
          return iVar3;
        }
        return iVar3;
      }
      if (0x7f < (*(u32 *)(g_0045D73C + 0x0))) break;
      iVar3 = aiStack_200[(*(u32 *)(g_0045D73C + 0x0))];
    }
  }
  func_0032FF10(0);
  func_0032FEF0(0);
  return -1;
}
/* MISSING ['0x45d73c'] */

/* 0x0036D9B0, 0x148 bytes. */
int func_0036D9B0(int param_1, int param_2)
{
    u32 auStack_70[28];
    int iVar1;
    int iVar6;
    int lVar2;
    int lVar3;
    int lVar5;
    u32 * puVar4;

  
  if ((param_2 < 0) || (0x34 < param_2)) {
    lVar2 = 0;
  }
  else {
    lVar5 = 0;
    iVar1 = func_002FB320(param_1,auStack_70);
    iVar6 = 0;
    if (0 < iVar1) {
      puVar4 = auStack_70;
      do {
        lVar2 = func_0030AC90(*puVar4,0);
        if (param_2 == lVar2) break;
        iVar6 = iVar6 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar6 < iVar1);
    }
    if (iVar6 < iVar1) {
      lVar2 = func_002FABC0(param_1);
      if (lVar2 < 300) {
        lVar5 = 1;
      }
      else if (lVar2 < 1000) {
        lVar5 = 2;
      }
      else {
        lVar5 = 3;
      }
    }
    lVar3 = 0;
    if (param_2 < 0x28) {
      lVar3 = func_002FA9E0(param_1,param_2);
    }
    lVar2 = func_0030AB50(param_2);
    if (param_2 == 0x27) {
      lVar2 = 1;
    }
    if (lVar3 < lVar5) {
      lVar3 = lVar5;
    }
    if (lVar3 <= lVar2) {
      lVar2 = lVar3;
    }
  }
  return lVar2;
}

/* 0x0036EB40, 0xC8 bytes. */
void func_0036EB40(void)
{
    u32 auStack_50[20];
    int iVar1;
    int lVar3;
    int uVar2;

  
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if ((g_7000015C >> 0x10) % 100 < 3) {
    uVar2 = func_0035D5A0();
    lVar3 = func_00352FE0(uVar2,auStack_50,0x14);
    if (lVar3 != 0) {
      if (lVar3 == 0) {
        iVar1 = 0;
      }
      else {
        g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
        iVar1 = (int)(g_7000015C >> 0x10) % (int)lVar3 << 2;
      }
      uVar2 = func_0034EC80(*(u32 *)((int)auStack_50 + iVar1));
      func_0036E8D0(uVar2);
    }
  }
  return;
}

/* 0x00371850, 0x69C bytes. */
void func_00371850(void)
{
    int aiStack_270[28];
    u32 auStack_190[100];
    u32 auStack_200[28];
    u32 auStack_2e0[28];
    u32 auStack_350[28];
    int iVar13;
    int iVar14;
    int iVar2;
    int iVar3;
    int iVar7;
    int iVar8;
    int lVar4;
    int lVar5;
    int * piVar11;
    int * piVar15;
    u32 * puVar10;
    u32 * puVar12;
    u32 * puVar9;
    u32 uVar1;
    int uVar6;

  
  lVar4 = func_00327C00();
  lVar5 = func_00327C00();
  if (lVar5 == 10) {
    func_003710C0();
  }
  uVar6 = func_00309FB0();
  func_00327E30(uVar6);
  lVar5 = func_003278B0();
  if (lVar5 != 0) {
    iVar7 = 0;
    do {
      uVar6 = func_003A01A0(iVar7);
      func_003280F0(iVar7,uVar6);
      iVar7 = iVar7 + 1;
    } while (iVar7 < 100);
  }
  iVar7 = func_00314960(auStack_190);
  iVar8 = 0;
  if (0 < iVar7) {
    puVar10 = auStack_190;
    do {
      func_003280F0(*puVar10,1);
      iVar8 = iVar8 + 1;
      puVar10 = puVar10 + 1;
    } while (iVar8 < iVar7);
  }
  uVar6 = func_0030AB90();
  uVar6 = func_0030CB00(uVar6);
  func_00327F00(uVar6);
  uVar6 = func_0030AB90();
  uVar6 = func_0030CB00(uVar6);
  func_00327FE0(uVar6);
  uVar6 = func_0030AB90();
  uVar6 = func_0030CB00(uVar6);
  func_00327F70(uVar6);
  lVar5 = func_003278B0();
  if (lVar5 != 0) {
    iVar7 = 0;
    do {
      if ((iVar7 < 0x74) || (0x77 < iVar7)) {
        uVar6 = func_00328B30(iVar7);
        func_003A2940(iVar7,uVar6);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 0x79);
  }
  if (lVar4 == 9) {
    func_003281F0(1);
  }
  else {
    func_003281F0(0);
  }
  if (lVar4 == 7) {
    func_00328240(1);
  }
  else if (lVar4 == 8) {
    func_00328240(2);
  }
  else if (lVar4 == 9) {
    func_00328240(4);
  }
  else {
    func_00328240(0);
  }
  if (lVar4 == 9) {
    func_00328290(1);
  }
  else {
    func_00328290(0);
  }
  iVar7 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    do {
      lVar4 = func_002F8CB0(iVar7);
      if (lVar4 != 0) {
        lVar4 = func_002FB2A0(iVar7);
        if (lVar4 == 0) {
          iVar8 = func_00327C40();
          func_002F8F90(iVar7,(iVar8 + 1) * 200 + 1000);
        }
        else {
          iVar8 = func_00327C40();
          func_002F8F90(iVar7,iVar8 * -0x96 + 800);
        }
        uVar6 = func_002FB9D0(iVar7);
        func_002FA8E0(iVar7,uVar6);
      }
      iVar7 = iVar7 + 1;
      iVar8 = func_0030AB90();
    } while (iVar7 < iVar8);
  }
  uVar6 = func_00327D50();
  uVar6 = func_002FA970(uVar6);
  func_003280C0(uVar6);
  func_002F7B10();
  iVar7 = func_003704C0(auStack_200);
  if (iVar7 != 0) {
    lVar4 = func_0030CA50();
    if (lVar4 < 3) {
      func_00370A00();
    }
    else {
      iVar14 = 0;
      iVar8 = 0;
      lVar4 = func_0030AB90();
      if (0 < lVar4) {
        piVar15 = aiStack_270;
        do {
          lVar4 = func_0030AFF0(iVar8);
          if (lVar4 < 0x19) {
            iVar13 = 0;
            if (0 < iVar14) {
              piVar11 = aiStack_270;
              do {
                iVar3 = *piVar11;
                iVar2 = func_002F8F20(lVar4);
                if (iVar3 == iVar2) break;
                iVar13 = iVar13 + 1;
                piVar11 = piVar11 + 1;
              } while (iVar13 < iVar14);
            }
            if ((iVar14 <= iVar13) && (lVar5 = func_002FB2A0(lVar4), lVar5 == 0)) {
              iVar13 = func_002F8F20(lVar4);
              *piVar15 = iVar13;
              iVar14 = iVar14 + 1;
              piVar15 = piVar15 + 1;
            }
          }
          iVar8 = iVar8 + 1;
          iVar13 = func_0030AB90();
        } while (iVar8 < iVar13);
      }
      iVar8 = 0;
      if (0 < iVar7) {
        puVar10 = auStack_200;
        do {
          iVar3 = func_0030C4E0(*puVar10,auStack_2e0);
          iVar13 = 0;
          iVar2 = 0;
          if (0 < iVar3) {
            puVar12 = auStack_2e0;
            puVar9 = auStack_350;
            do {
              uVar1 = *puVar12;
              lVar4 = func_0030AFF0(uVar1);
              if ((lVar4 < 0x19) && (lVar4 = func_002FB2A0(lVar4), lVar4 == 0)) {
                *puVar9 = uVar1;
                iVar13 = iVar13 + 1;
                puVar9 = puVar9 + 1;
              }
              iVar2 = iVar2 + 1;
              puVar12 = puVar12 + 1;
            } while (iVar2 < iVar3);
          }
          if (iVar13 < 1) {
            if (iVar14 == 0) {
              uVar6 = func_00327D50();
              func_0030AF20(*puVar10,uVar6);
            }
            else {
              iVar13 = func_0030CB00(iVar14);
              uVar6 = func_002F4080(aiStack_270[iVar13]);
              func_0030AF20(*puVar10,uVar6);
            }
          }
          else if (iVar13 == 1) {
            uVar6 = func_0030AFF0(auStack_350[0]);
            func_0030AF20(*puVar10,uVar6);
          }
          else {
            if (iVar13 == 0) {
              iVar13 = 0;
            }
            else {
              g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
              iVar13 = (int)(g_7000015C >> 0x10) % iVar13;
            }
            uVar6 = func_0030AFF0(auStack_350[iVar13]);
            func_0030AF20(*puVar10,uVar6);
          }
          iVar8 = iVar8 + 1;
          puVar10 = puVar10 + 1;
        } while (iVar8 < iVar7);
      }
    }
  }
  iVar7 = 400;
  do {
    lVar4 = func_002F2870(iVar7);
    if ((lVar4 == 0) || (lVar4 = func_0039E650(iVar7 + -400), lVar4 == 0)) {
      func_002F3B30(iVar7,3);
    }
    else {
      func_003710F0(iVar7);
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x19f);
  lVar4 = func_003278B0();
  if (lVar4 != 0) {
    func_003A5240();
  }
  iVar7 = 0;
  do {
    lVar4 = func_002F57F0(iVar7);
    func_00328BA0(iVar7,lVar4 == 0);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x79);
  iVar7 = 0;
  do {
    func_002F56A0(iVar7,0);
    uVar6 = func_002F4080(iVar7);
    lVar4 = func_002F8CB0(uVar6);
    if (lVar4 != 0) {
      func_002F4AE0(iVar7,7);
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x19f);
  func_00371310();
  func_00371520();
  func_003717A0();
  return;
}

/* 0x00373540, 0xF8 bytes. */
void func_00373540(void)
{
    int iVar1;
    u8 * iVar3;
    int iVar6;
    int lVar2;
    int lVar4;
    int uVar5;

  
  uVar5 = 1;
  func_003A7C10();
  iVar6 = 0;
  lVar2 = func_0030AB90();
  if (0 < lVar2) {
    iVar3 = g_007B9890;
    do {
      if (*(int *)(iVar3 + 0x28) == 0) {
        uVar5 = 0;
      }
      func_003A78E0(iVar6,*(u32 *)(iVar3 + 0x8c),uVar5);
      iVar3 = iVar3 + 4;
      iVar6 = iVar6 + 1;
      iVar1 = func_0030AB90();
    } while (iVar6 < iVar1);
  }
  func_003A78E0((*(short *)(g_007B9980 + 0x0)),0x1f,1);
  lVar4 = 0;
  lVar2 = func_0030AB90();
  if (0 < lVar2) {
    do {
      if ((*(short *)(g_007B9980 + 0x0)) == lVar4) {
        func_003A80B0(lVar4,1);
      }
      else {
        func_003A80B0(lVar4,0);
      }
      lVar4 = (int)((int)lVar4 + 1);
      lVar2 = func_0030AB90();
    } while (lVar4 < lVar2);
  }
  return;
}

/* 0x00374040, 0xAC bytes. */
int func_00374040(int param_1)
{
    u32 auStack_70[28];
    int iVar2;
    int iVar6;
    int lVar4;
    u32 * puVar5;
    u32 uVar1;
    int uVar3;

  
  uVar3 = func_00327D50();
  lVar4 = func_002FA790(uVar3);
  if (lVar4 == 0) {
    iVar2 = func_0030B8F0(param_1,uVar3,auStack_70);
    iVar6 = 0;
    if (0 < iVar2) {
      puVar5 = auStack_70;
      do {
        lVar4 = func_0030C250(*puVar5);
        if ((lVar4 != 0) && (lVar4 = func_0030C6A0(*puVar5), 0 < lVar4)) {
          return 1;
        }
        iVar6 = iVar6 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar6 < iVar2);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 0x00383270, 0x40 bytes. */
void func_00383270(int param_1, int param_2, int param_3)
{
  func_001ABE40(param_1,0xd1,param_2,param_3,0,0x160,0x38,0x80);
  return;
}

/* 0x003832E0, 0x44 bytes. */
void func_003832E0(int param_1, int param_2, int param_3, int param_4)
{
  func_001ABE40(param_1,param_4 + 0x5f,param_2,param_3,0,200,0x28,0x80);
  return;
}

/* 0x00383610, 0x40 bytes. */
void func_00383610(int param_1, int param_2, int param_3, int param_4)
{
  func_001ABE40(param_1,0x14d,param_2,param_3,0,0xe0,0x98,param_4);
  return;
}

/* 0x00383AB0, 0x40 bytes. */
void func_00383AB0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
  func_001ABE40(param_1,0xda,param_2,param_3,0,param_4,param_5,0x80);
  return;
}

/* 0x00383E00, 0x38 bytes. */
void func_00383E00(int param_1)
{
    u32 uVar1;

  
  uVar1 = 1;
  do {
    uVar1 = uVar1 << 1;
    if ((param_1 & 0xffff) <= uVar1) {
      return;
    }
  } while (uVar1 < 0x1fffe);
  return;
}

/* 0x003886D0, 0x34 bytes. */
void func_003886D0(void)
{
  func_003DC2D0(*(u32 *)((g_00417650 + 0x0) + (u32)(*(u8 *)(g_007B9E58 + 0x0)) * 4));
  return;
}

/* 0x003892C0, 0xFC bytes. */
int func_003892C0(u8 *param_1)
{
    int iVar1;
    int lVar3;
    u32 uStack_1c;
    u32 uStack_20;
    u32 uVar2;
    int uVar4;

  
  iVar1 = *(int *)(param_1 + 0x690);
  uVar2 = *(u32 *)(param_1 + *(int *)(param_1 + 0x68c) * 0x184 + 0x80);
  if (iVar1 == 2) {
    func_003DB480(3);
  }
  else if (iVar1 == 1) {
    lVar3 = func_0030E1F0();
    if (lVar3 == 2) {
      func_0030E100();
    }
    uStack_20 = 0xa0;
    uStack_1c = 0x60;
    func_003DB220(3,&uStack_20);
    func_003DB460(3,2);
  }
  else if ((iVar1 == 0) && (lVar3 = func_002FB2A0(*(u32 *)(param_1 + 4)), lVar3 != 0)) {
    func_0032E960(uVar2);
    uVar4 = func_002F8F20(uVar2);
    func_0030E140(0x30,uVar4,0xffffffffffffffff,0xffffffffffffffff);
  }
  return 0;
}

/* 0x00389B40, 0x190 bytes. */
void func_00389B40(int param_1, int param_2, u8 *param_3)
{
    int iVar2;
    int lVar3;
    int * piVar1;
    u32 uStack_10;
    u32 uStack_1c;
    u32 uStack_20;
    int uVar4;

  
  if (param_1 == 0x27) {
    param_1 = *(int *)(param_3 + 0x18);
  }
  if (param_1 == 0x24) {
    uVar4 = 7;
  }
  else if (param_1 == 0x25) {
    uVar4 = 8;
  }
  else {
    uVar4 = 6;
  }
  piVar1 = (int *)func_00389A50(param_1,param_2);
  lVar3 = func_0030E1F0();
  if (lVar3 == 2) {
    func_0030E100();
  }
  if (param_2 == 1) {
    lVar3 = func_0023A760(uVar4);
    if (lVar3 != 0) {
      func_00102960(1);
      func_0023A7D0(uVar4);
    }
    uStack_20 = 0x94;
    uStack_1c = 0x78;
    uStack_10 = 0x80;
    func_003DB220(0xb,&uStack_20);
    func_003DB460(0xb,5);
  }
  else if (param_2 == 2) {
    func_0023AA40();
    func_003DB480(0xb,5);
  }
  else {
    lVar3 = func_00389AC0(param_1);
    if (param_2 < lVar3) {
      iVar2 = 0;
      if (1 < piVar1[2]) {
        iVar2 = func_0030CB00();
      }
      if (*piVar1 != -1) {
        func_0030E140(*piVar1 + iVar2,*(u32 *)(param_3 + piVar1[1] * 4),0xffffffffffffffff,1);
      }
    }
  }
  return;
}

/* 0x0038AD60, 0x47C bytes. */
void func_0038AD60(u8 *param_1)
{
    int aiStack_20[8];
    int aiStack_40[8];
    int bVar2;
    int bVar3;
    int iVar1;
    int iVar5;
    int iVar6;
    int iVar7;
    int * piVar11;
    int * piVar12;
    int * piVar9;
    u32 * puVar4;
    u32 uVar10;
    int uVar8;

  
  iVar1 = *(int *)(param_1 + 4);
  piVar12 = (int *)(param_1 + *(int *)(param_1 + 0x68c) * 0x184 + 0x80);
  puVar4 = (u32 *)func_003DB900(1);
  bVar3 = false;
  bVar2 = false;
  if (-1 < iVar1) {
    iVar5 = func_0030AB90();
    bVar2 = iVar1 < iVar5;
  }
  if (bVar2) {
    iVar5 = 0;
    (*(u32 *)(g_007B9F30 + 0xC)) = 0;
    piVar9 = piVar12;
    do {
      if ((*(u32 *)(g_007B9F30 + 0xC)) < *piVar9) {
        (*(u32 *)(g_007B9F30 + 0xC)) = *piVar9;
      }
      iVar5 = iVar5 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar5 < 3);
    iVar5 = *(int *)(param_1 + 0x690);
    if (iVar5 == 2) {
      (*(u32 *)(g_007B9F30 + 0x8)) = (*(u32 *)(g_007B9F30 + 0xC));
    }
    else if (iVar5 == 1) {
      (*(u32 *)(g_007B9F30 + 0x0)) = 1;
      (*(u32 *)(g_007B9F30 + 0x8)) = (*(u32 *)(g_007B9F30 + 0x8)) + 1;
    }
    else if (iVar5 == 0) {
      (*(u32 *)(g_007B9F30 + 0x8)) = 0;
      (*(u32 *)(g_007B9F30 + 0x0)) = 0;
    }
    iVar5 = 0;
    piVar11 = aiStack_20;
    piVar9 = aiStack_40;
    do {
      iVar6 = func_002F9390(iVar1,iVar5);
      *piVar11 = iVar6;
      piVar11[3] = 0;
      if (*piVar12 < (*(u32 *)(g_007B9F30 + 0x8))) {
        iVar6 = *piVar12;
      }
      else {
        iVar6 = (*(u32 *)(g_007B9F30 + 0x8));
      }
      iVar7 = func_002F9390(iVar1,iVar5);
      if (iVar7 + iVar6 < 400) {
        if (*piVar12 < (*(u32 *)(g_007B9F30 + 0x8))) {
          iVar7 = *piVar12;
        }
        else {
          iVar7 = (*(u32 *)(g_007B9F30 + 0x8));
        }
        iVar6 = func_002F9390(iVar1,iVar5);
        iVar6 = iVar6 + iVar7;
      }
      else {
        iVar6 = 400;
      }
      *piVar9 = iVar6;
      iVar6 = (*(u32 *)(g_007B9F30 + 0x8)) + -1;
      if (iVar6 < 0) {
        iVar7 = 0;
      }
      else {
        iVar7 = iVar6;
      }
      if (*piVar12 < iVar7) {
        iVar6 = *piVar12;
      }
      else if (iVar6 < 0) {
        iVar6 = 0;
      }
      iVar7 = func_002F9390(iVar1,iVar5);
      if (iVar7 + iVar6 < 400) {
        iVar7 = (*(u32 *)(g_007B9F30 + 0x8)) + -1;
        if (iVar7 < 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = iVar7;
        }
        if (*piVar12 < iVar6) {
          iVar7 = *piVar12;
        }
        else if (iVar7 < 0) {
          iVar7 = 0;
        }
        iVar6 = func_002F9390(iVar1,iVar5);
        iVar6 = iVar6 + iVar7;
      }
      else {
        iVar6 = 400;
      }
      uVar10 = (u32)(0 < *piVar9 / 100 - *piVar11 / 100);
      piVar11[3] = uVar10;
      piVar9[3] = uVar10;
      if (((((*(u32 *)(g_007B9F30 + 0x0)) != 0) && (0 < (*(u32 *)(g_007B9F30 + 0x8)))) && ((*(u32 *)(g_007B9F30 + 0x8)) <= (*(u32 *)(g_007B9F30 + 0xC)))) &&
         ((!bVar3 && (0 < *piVar9 / 100 - iVar6 / 100)))) {
        func_0023AD10(7,0,0x2cdc,0x2cdc,0x1000);
        bVar3 = true;
      }
      iVar5 = iVar5 + 1;
      piVar11 = piVar11 + 1;
      piVar12 = piVar12 + 1;
      piVar9 = piVar9 + 1;
    } while (iVar5 < 3);
    iVar5 = *(int *)(param_1 + 0x690);
    if (iVar5 == 2) {
      (*(u32 *)(g_007B9F30 + 0x0)) = 0;
      uVar8 = func_0030D7D0();
      func_0037ED80(uVar8,*puVar4,puVar4[1],iVar1,aiStack_20,aiStack_40,0);
    }
    else if (iVar5 == 1) {
      uVar8 = func_0030D7D0();
      func_0037ED80(uVar8,*puVar4,puVar4[1],iVar1,aiStack_20,aiStack_40,0);
    }
    else if (iVar5 == 0) {
      uVar8 = func_0030D7D0();
      func_0037ED80(uVar8,*puVar4,puVar4[1],iVar1,aiStack_20,0,0);
    }
  }
  return;
}

/* 0x0038C6B0, 0x30 bytes, matching. */
int func_0038C6B0(int param_1)
{
  func_0038C6F0();
  func_0038C750(param_1);
  return 0;
}

/* 0x0039D950, 0x40 bytes. */
void func_0039D950(int param_1)
{
    int uVar1;

  
  if (param_1 - 0x1aU < 3) {
    func_00372E30(param_1 - 0x1aU);
  }
  else {
    uVar1 = func_0039D930();
    func_002F2890(uVar1);
  }
  return;
}

/* 0x0039D990, 0x40 bytes. */
void func_0039D990(int param_1)
{
    int uVar1;

  
  if (param_1 - 0x1aU < 3) {
    func_00372E30(param_1 - 0x1aU);
  }
  else {
    uVar1 = func_0039D930();
    func_002F2970(uVar1);
  }
  return;
}

/* 0x003A63D0, 0x7C bytes. */
void func_003A63D0(int param_1)
{
    int iVar3;
    int uVar1;
    int uVar2;

  
  iVar3 = (*(u32 *)(g_007BACC4 + 0x0)) + *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 8) * *(int *)(param_1 * 8 + (*(u32 *)(g_007BACC4 + 0x0)) + 0x10);
  func_00106F10(iVar3);
  uVar1 = func_00104AC0(iVar3,0x1d00,(*(u32 *)(g_007BACC4 + 0x74)));
  uVar2 = func_00104D00(iVar3,0x3ffc,(*(u32 *)(g_007BACC4 + 0x74)));
  func_00106C50(uVar1,uVar2);
  return;
}

/* 0x003A97C0, 0x1E4 bytes. */
void func_003A97C0(int *param_1, int param_2, int param_3)
{
    int aiStack_70[27];
    int aiStack_e0[28];
    int bVar1;
    int iStack_4;
    int iVar2;
    int iVar7;
    int lVar3;
    int lVar4;
    int * piVar5;
    int * piVar6;

  
  lVar3 = func_00327D50();
  func_003A91F0();
  iVar7 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    piVar6 = aiStack_70;
    piVar5 = aiStack_e0;
    do {
      *piVar5 = 0;
      *piVar6 = 1;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
      iVar7 = iVar7 + 1;
      iVar2 = func_0030AB90();
    } while (iVar7 < iVar2);
  }
  iVar7 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    piVar5 = aiStack_70;
    do {
      bVar1 = false;
      iVar2 = 0;
      if (0 < param_2) {
        piVar6 = param_1;
        do {
          if (iVar7 == *piVar6) {
            bVar1 = true;
            break;
          }
          iVar2 = iVar2 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar2 < param_2);
      }
      if (((bVar1) || (lVar4 = func_0030AFF0(iVar7), lVar3 == lVar4)) ||
         (((param_3 == 0 || (lVar4 = func_003A9640(iVar7), lVar4 != 0)) && (param_3 != 0)))) {
        if ((param_3 != 0) && (lVar4 = func_003A9700(iVar7,&iStack_4), lVar4 != 0)) {
          aiStack_e0[iStack_4] = 1;
        }
      }
      else {
        *piVar5 = 0;
      }
      piVar5 = piVar5 + 1;
      iVar7 = iVar7 + 1;
      iVar2 = func_0030AB90();
    } while (iVar7 < iVar2);
  }
  iVar7 = 0;
  lVar3 = func_0030AB90();
  if (0 < lVar3) {
    piVar6 = aiStack_70;
    piVar5 = aiStack_e0;
    do {
      if ((*piVar6 == 0) && (*piVar5 == 0)) {
        func_003A8000(iVar7);
      }
      else {
        func_003A8030(iVar7);
      }
      piVar6 = piVar6 + 1;
      piVar5 = piVar5 + 1;
      iVar7 = iVar7 + 1;
      iVar2 = func_0030AB90();
    } while (iVar7 < iVar2);
  }
  return;
}

/* 0x003CBBB0, 0x234 bytes. */
int func_003CBBB0(void)
{
    int bVar1;
    int iStack_4;
    int iStack_8;
    int iVar4;
    int iVar5;
    int iVar6;
    int lVar10;
    int lVar11;
    int lVar9;
    int * piVar12;
    int * piVar2;
    int * piVar3;
    u32 uVar7;
    int uVar8;

  
  uVar8 = func_00327820();
  lVar9 = func_002F4080(0x12);
  lVar10 = func_002F5CC0(0x12);
  piVar3 = (int *)0x8;
  piVar12 = &iStack_8;
  piVar2 = piVar12;
  while (piVar2 != (int *)0x0) {
    *(u8 *)piVar12 = 0;
    piVar12 = (int *)((int)piVar12 + 1);
    piVar3 = (int *)((int)piVar3 + -1);
    piVar2 = piVar3;
  }
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
      iVar4 = func_002FB430(lVar9);
      iVar5 = func_003C1200(lVar10,0);
      lVar11 = func_00327D50();
      if (lVar9 == lVar11) {
        iVar6 = func_00327E50();
      }
      else {
        iVar6 = func_002FB3B0(lVar9);
        iVar6 = iVar6 * 6;
      }
      lVar9 = func_00329540(0x122);
      if (lVar9 == 0) {
        lVar9 = func_0032EB40(uVar8,0x12,1);
        if (((lVar9 != 0) && (lVar9 = func_0032EB40(uVar8,5,0), lVar9 != 0)) &&
           (lVar9 = func_002F5CC0(5), lVar10 == lVar9)) {
          iStack_8 = 1;
        }
        lVar9 = func_0032ED30(uVar8,0x12,5,1);
        if (((lVar9 != 0) && (lVar9 = func_0032EB40(2,0x12,0), lVar9 == 0)) &&
           ((lVar9 = func_0032EB40(2,5,0), lVar9 != 0 && ((iVar4 < iVar6 && (0 < 3 - iVar5)))))) {
          iStack_4 = 1;
        }
        if ((iStack_8 == 0) && (iStack_4 == 0)) {
          uVar7 = 0;
        }
        else {
          lVar9 = func_00328270();
          if (lVar9 == 0) {
            uVar7 = 1;
          }
          else {
            uVar7 = 0;
          }
        }
      }
      else {
        uVar7 = 0;
      }
    }
    else {
      uVar7 = 0;
    }
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}

/* 0x003E12A0, 0x4E4 bytes. */
int func_003E12A0(void)
{
    int uVar1;
    int uVar2;
    u32 uVar3;

  
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(u16 *)(g_0050074C + 0x2));
  }
  if ((uVar1 & 0x10) == 0) {
    if ((*(short *)(g_007BF69C + 0x4)) < 2) {
      uVar3 = 2;
    }
    else if ((uVar1 & 0x4000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        if ((uVar1 & 0x1000) != 0) {
          if ((short)(*(u16 *)(g_007BF69C + 0x2)) < 1) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u16 *)(g_007BF69C + 0x2)) = (*(short *)(g_007BF69C + 0x4)) - 1U & 0xff;
            (*(u16 *)(g_007BF69C + 0x0)) = (*(short *)(g_007BF69C + 0x6)) - 1U & 0xff;
            func_003E0A50();
            return 2;
          }
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + -1;
          if (0 < (short)(*(u16 *)(g_007BF69C + 0x0))) {
            (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + -1;
          }
          func_003E0A50();
          return 2;
        }
        if ((uVar2 & 0x1000) != 0) {
          if ((*(short *)(g_007BF69C + 0x4)) <= (*(short *)(g_007BF69C + 0x6))) {
            if ((short)(*(u16 *)(g_007BF69C + 0x2)) < 1) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              (*(u16 *)(g_007BF69C + 0x2)) = (*(short *)(g_007BF69C + 0x4)) - 1U & 0xff;
              (*(u16 *)(g_007BF69C + 0x0)) = (*(short *)(g_007BF69C + 0x6)) - 1U & 0xff;
              func_003E0A50();
              return 2;
            }
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + -1;
            if (0 < (short)(*(u16 *)(g_007BF69C + 0x0))) {
              (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + -1;
            }
            func_003E0A50();
            return 2;
          }
          if (0 < (short)(*(u16 *)(g_007BF69C + 0x2))) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + -1;
            if (0 < (short)(*(u16 *)(g_007BF69C + 0x0))) {
              (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + -1;
            }
            func_003E0A50();
            return 2;
          }
        }
      }
      else {
        if ((*(short *)(g_007BF69C + 0x4)) <= (*(short *)(g_007BF69C + 0x6))) {
          if ((int)((*(short *)(g_007BF69C + 0x4)) + -1) <= (int)(short)(*(u16 *)(g_007BF69C + 0x2))) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u16 *)(g_007BF69C + 0x0)) = 0;
            (*(u16 *)(g_007BF69C + 0x2)) = 0;
            func_003E0A50();
            return 2;
          }
          (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + 1;
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          if ((int)(short)(*(u16 *)(g_007BF69C + 0x0)) < (int)((*(short *)(g_007BF69C + 0x6)) + -1)) {
            (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + 1;
          }
          func_003E0A50();
          return 2;
        }
        if ((int)(short)(*(u16 *)(g_007BF69C + 0x2)) < (int)((*(short *)(g_007BF69C + 0x4)) + -1)) {
          (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + 1;
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          if ((int)(short)(*(u16 *)(g_007BF69C + 0x0)) < (int)((*(short *)(g_007BF69C + 0x6)) + -1)) {
            (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + 1;
          }
          func_003E0A50();
          return 2;
        }
      }
      uVar3 = 2;
    }
    else {
      if ((int)(short)(*(u16 *)(g_007BF69C + 0x2)) < (int)((*(short *)(g_007BF69C + 0x4)) + -1)) {
        (*(u16 *)(g_007BF69C + 0x2)) = (*(u16 *)(g_007BF69C + 0x2)) + 1;
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        if ((int)(short)(*(u16 *)(g_007BF69C + 0x0)) < (int)((*(short *)(g_007BF69C + 0x6)) + -1)) {
          (*(u16 *)(g_007BF69C + 0x0)) = (*(u16 *)(g_007BF69C + 0x0)) + 1;
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        (*(u16 *)(g_007BF69C + 0x0)) = 0;
        (*(u16 *)(g_007BF69C + 0x2)) = 0;
      }
      func_003E0A50();
      uVar3 = 2;
    }
  }
  else {
    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
    func_003E1260();
    uVar3 = 0;
  }
  return uVar3;
}

/* 0x003EBE60, 0x18C bytes. */
void func_003EBE60(void)
{
    u32 auStack_70[28];
    int bVar2;
    int iVar1;
    int iVar3;
    int iVar8;
    int lVar6;
    int lVar7;
    int * piVar4;
    u32 * puVar9;
    int uVar5;

  
  uVar5 = func_003EA0C0();
  lVar6 = func_003EA140();
  iVar3 = func_002F7D90(0,0x2f8160,uVar5,0,0,0);
  piVar4 = (int *)func_002F7B10();
  iVar8 = 0;
  if (0 < iVar3) {
    do {
      iVar1 = *piVar4;
      if (iVar1 == 2) {
        func_002F7610();
      }
      else if (iVar1 == 10) {
        func_002F7610();
      }
      else if (iVar1 == 0xc) {
        func_002F7610();
      }
      else {
        func_002F7410();
      }
      iVar8 = iVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar8 < iVar3);
  }
  func_002FAFC0(uVar5);
  func_002FB7C0(uVar5);
  iVar3 = func_002FB320(uVar5,auStack_70);
  iVar8 = 0;
  if (0 < iVar3) {
    puVar9 = auStack_70;
    do {
      bVar2 = false;
      if (-1 < lVar6) {
        lVar7 = func_0030AB90();
        bVar2 = lVar6 < lVar7;
      }
      if ((bVar2) && (lVar7 = func_002F8CB0(lVar6), lVar7 != 0)) {
        func_0030AF20(*puVar9,lVar6);
      }
      func_00323840(*puVar9);
      iVar8 = iVar8 + 1;
      puVar9 = puVar9 + 1;
    } while (iVar8 < iVar3);
  }
  func_002F8D20(uVar5);
  func_002F8E80(uVar5,0x19f);
  return;
}

/* 0x003ECD90, 0x118 bytes. */
void func_003ECD90(void)
{
    int aiStack_70[28];
    int bVar1;
    int iVar2;
    int iVar7;
    int iVar8;
    int lVar3;
    int lVar4;
    int * piVar6;
    int uVar5;

  
  lVar3 = func_002F4080(0);
  lVar4 = func_00327D50();
  if (lVar3 != lVar4) {
    uVar5 = func_003EA160();
    iVar2 = func_002FB320(uVar5,aiStack_70);
    iVar7 = 0x19;
    iVar8 = 0;
    if (0 < iVar2) {
      piVar6 = aiStack_70;
      do {
        lVar4 = func_0030C6A0(*piVar6);
        if (lVar4 < 3) {
          iVar7 = aiStack_70[iVar8];
          break;
        }
        iVar8 = iVar8 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar8 < iVar2);
    }
    if (iVar7 != 0x19) {
      bVar1 = false;
      if (-1 < lVar3) {
        lVar4 = func_0030AB90();
        bVar1 = lVar3 < lVar4;
      }
      if ((bVar1) && (lVar3 = func_002F8CB0(lVar3), lVar3 != 0)) {
        func_002F7410(0);
      }
      func_002F7300(0,uVar5,iVar7,2);
    }
  }
  return;
}

/* 0x003ECEB0, 0x10C bytes. */
void func_003ECEB0(void)
{
    u32 auStack_70[28];
    int iVar2;
    int iVar8;
    int lVar6;
    u32 * puVar1;
    u32 * puVar7;
    int uVar3;
    int uVar4;
    int uVar5;

  
  puVar1 = (u32 *)func_003EA000();
  uVar3 = func_003EA160();
  uVar4 = func_003EA180();
  uVar5 = func_003EA0E0();
  iVar2 = func_003EAB60(uVar5,auStack_70);
  lVar6 = func_00375BF0();
  if ((lVar6 != 0) && (lVar6 = func_00375B90(), lVar6 == 1)) {
    func_002FAF30(uVar3,uVar4);
    lVar6 = func_0036B260();
    if (lVar6 == 0) {
      func_003ECD90();
      iVar8 = 0;
      if (0 < iVar2) {
        puVar7 = auStack_70;
        do {
          func_003EA310(*puVar7);
          func_003EA1C0(*puVar7);
          iVar8 = iVar8 + 1;
          puVar7 = puVar7 + 1;
        } while (iVar8 < iVar2);
      }
    }
    else {
      iVar8 = 0;
      if (0 < iVar2) {
        puVar7 = auStack_70;
        do {
          func_003EA330(*puVar7);
          iVar8 = iVar8 + 1;
          puVar7 = puVar7 + 1;
        } while (iVar8 < iVar2);
      }
    }
    *puVar1 = 3;
  }
  return;
}

/* 0x003ED480, 0x1F0 bytes. */
void func_003ED480(void)
{
    u32 auStack_150[28];
    u32 auStack_70[28];
    u32 auStack_e0[28];
    int bVar1;
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar2;
    int iVar4;
    int lVar5;
    int lVar6;
    int lVar7;
    int * piVar3;
    u32 * puVar13;
    u32 * puVar8;
    u32 * puVar9;

  
  lVar5 = func_003EA1A0();
  iVar2 = func_002F7D90(0,0x2f8160,lVar5,0,0,0);
  piVar3 = (int *)func_002F7B10();
  iVar10 = 0;
  if (0 < iVar2) {
    do {
      if (*piVar3 == 0x11) {
        func_002F7610();
      }
      else if (*piVar3 == 0x13) {
        func_002F7610();
      }
      else {
        func_002F7410();
      }
      iVar10 = iVar10 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar10 < iVar2);
  }
  func_002FAFC0(lVar5);
  func_002FB7C0(lVar5);
  iVar2 = func_002FB320(lVar5,auStack_70);
  iVar10 = 0;
  if (0 < iVar2) {
    puVar13 = auStack_70;
    do {
      iVar4 = func_0030C4E0(*puVar13,auStack_e0);
      iVar11 = 0;
      iVar12 = 0;
      if (0 < iVar4) {
        puVar9 = auStack_e0;
        puVar8 = auStack_150;
        do {
          lVar6 = func_0030AFF0(*puVar9);
          bVar1 = false;
          if (-1 < lVar6) {
            lVar7 = func_0030AB90();
            bVar1 = lVar6 < lVar7;
          }
          if (((bVar1) && (lVar7 = func_002F8CB0(lVar6), lVar7 != 0)) && (lVar6 != lVar5)) {
            *puVar8 = (int)lVar6;
            iVar11 = iVar11 + 1;
            puVar8 = puVar8 + 1;
          }
          iVar12 = iVar12 + 1;
          puVar9 = puVar9 + 1;
        } while (iVar12 < iVar4);
      }
      iVar4 = func_0030CB00(iVar11);
      func_0030AF20(*puVar13,auStack_150[iVar4]);
      func_00323840(*puVar13);
      iVar10 = iVar10 + 1;
      puVar13 = puVar13 + 1;
    } while (iVar10 < iVar2);
  }
  func_002F8D20(lVar5);
  func_002F8E80(lVar5,0x19f);
  return;
}

/* 0x003ED7F0, 0x114 bytes. */
void func_003ED7F0(void)
{
    u32 auStack_70[28];
    int iVar2;
    int iVar7;
    int lVar4;
    u32 * puVar1;
    u32 * puVar6;
    int uVar3;
    int uVar5;

  
  puVar1 = (u32 *)func_003EA000();
  uVar3 = func_003EA160();
  iVar2 = func_003EAB60(uVar3,auStack_70);
  lVar4 = func_00375BF0();
  if ((lVar4 != 0) && (lVar4 = func_00375B90(), lVar4 == 1)) {
    lVar4 = func_0036B260();
    if (lVar4 == 0) {
      iVar7 = 0;
      if (0 < iVar2) {
        puVar6 = auStack_70;
        do {
          func_003EA310(*puVar6);
          func_003EA1C0(*puVar6);
          iVar7 = iVar7 + 1;
          puVar6 = puVar6 + 1;
        } while (iVar7 < iVar2);
      }
    }
    else {
      uVar3 = func_003EA160();
      uVar5 = func_003EA180();
      func_002FAF30(uVar3,uVar5);
      func_003ED480();
      func_003ED680();
      iVar7 = 0;
      if (0 < iVar2) {
        puVar6 = auStack_70;
        do {
          func_003EA330(*puVar6);
          iVar7 = iVar7 + 1;
          puVar6 = puVar6 + 1;
        } while (iVar7 < iVar2);
      }
    }
    *puVar1 = 3;
  }
  return;
}

/* 0x003EDD00, 0x134 bytes. */
void func_003EDD00(void)
{
    u32 auStack_70[28];
    int iVar1;
    int iVar5;
    int * piVar2;
    u32 * puVar6;
    int uVar3;
    int uVar4;

  
  uVar3 = func_003EA160();
  uVar4 = func_003EA0E0();
  iVar1 = func_002F7D90(0,0x2f8160,uVar3,0,0,0);
  piVar2 = (int *)func_002F7B10();
  iVar5 = 0;
  if (0 < iVar1) {
    do {
      if (*piVar2 == 0x9f) {
        func_002F7610();
      }
      else if (*piVar2 == 0) {
        func_002F7610();
      }
      else {
        func_002F7410();
      }
      iVar5 = iVar5 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar5 < iVar1);
  }
  func_002FAFC0(uVar3);
  func_002FB7C0(uVar3);
  iVar1 = func_002FB320(uVar3,auStack_70);
  iVar5 = 0;
  if (0 < iVar1) {
    puVar6 = auStack_70;
    do {
      func_0030AF20(*puVar6,uVar4);
      func_00323840(*puVar6);
      iVar5 = iVar5 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar5 < iVar1);
  }
  func_002F8D20(uVar3);
  func_002F8E80(uVar3,0x19f);
  return;
}

/* 0x003EE2E0, 0xC0 bytes. */
void func_003EE2E0(void)
{
    u32 auStack_70[28];
    int iVar2;
    int iVar6;
    int lVar4;
    u32 * puVar1;
    u32 * puVar5;
    int uVar3;

  
  puVar1 = (u32 *)func_003EA000();
  uVar3 = func_003EA0E0();
  iVar2 = func_003EAB60(uVar3,auStack_70);
  lVar4 = func_00375BF0();
  if ((lVar4 != 0) && (lVar4 = func_00375B90(), lVar4 == 1)) {
    lVar4 = func_0036B260();
    if (lVar4 == 0) {
      func_003EDD00();
    }
    else {
      iVar6 = 0;
      if (0 < iVar2) {
        puVar5 = auStack_70;
        do {
          func_003EA330(*puVar5);
          iVar6 = iVar6 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar6 < iVar2);
      }
    }
    *puVar1 = 3;
  }
  return;
}

/* 0x003EF290, 0x144 bytes. */
int func_003EF290(int param_1, int param_2)
{
    u8 auStack_20[32];
    u8 auStack_40[32];
    u8 auStack_60[32];
    u8 auStack_80[32];
    int bVar1;
    int iVar2;
    int lVar5;
    u16 * puVar6;
    u16 * puVar7;
    int uVar3;
    int uVar4;

  
  if (param_1 < 400) {
    if (param_2 < 400) {
      iVar2 = func_002F27D0();
      puVar6 = (u16 *)((*(u32 *)(g_005BA6A0 + 0x0)) + iVar2 * 0x2c);
      iVar2 = func_002F27D0(param_2);
      puVar7 = (u16 *)((*(u32 *)(g_005BA6A0 + 0x0)) + iVar2 * 0x2c);
      uVar3 = func_0019B0E0(auStack_60,*puVar6);
      uVar4 = func_0019B130(auStack_80,puVar6[1]);
      func_001204B0(auStack_20,0x45c988,uVar3,uVar4);
      uVar3 = func_0019B0E0(auStack_60,*puVar7);
      uVar4 = func_0019B130(auStack_80,puVar7[1]);
      func_001204B0(auStack_40,0x45c988,uVar3,uVar4);
      func_003EF1D0(auStack_20,auStack_20);
      func_003EF1D0(auStack_40,auStack_40);
      lVar5 = func_001207E0(auStack_20,auStack_40);
      bVar1 = lVar5 < 0;
    }
    else {
      bVar1 = true;
    }
  }
  else {
    bVar1 = 399 < param_2 && param_1 < param_2;
  }
  return bVar1;
}

/* 0x003EF400, 0x144 bytes. */
int func_003EF400(int param_1, int param_2)
{
    u8 auStack_20[32];
    u8 auStack_40[32];
    u8 auStack_60[32];
    u8 auStack_80[32];
    int bVar1;
    int iVar2;
    int lVar5;
    u16 * puVar6;
    u16 * puVar7;
    int uVar3;
    int uVar4;

  
  if (param_1 < 400) {
    if (param_2 < 400) {
      iVar2 = func_002F27D0();
      puVar6 = (u16 *)((*(u32 *)(g_005BA6A0 + 0x0)) + iVar2 * 0x2c);
      iVar2 = func_002F27D0(param_2);
      puVar7 = (u16 *)((*(u32 *)(g_005BA6A0 + 0x0)) + iVar2 * 0x2c);
      uVar3 = func_0019B240(auStack_60,*puVar6);
      uVar4 = func_0019B130(auStack_80,puVar6[1]);
      func_001204B0(auStack_20,0x45c988,uVar3,uVar4);
      uVar3 = func_0019B240(auStack_60,*puVar7);
      uVar4 = func_0019B130(auStack_80,puVar7[1]);
      func_001204B0(auStack_40,0x45c988,uVar3,uVar4);
      func_003EF1D0(auStack_20,auStack_20);
      func_003EF1D0(auStack_40,auStack_40);
      lVar5 = func_001207E0(auStack_20,auStack_40);
      bVar1 = lVar5 < 0;
    }
    else {
      bVar1 = true;
    }
  }
  else {
    bVar1 = 399 < param_2 && param_1 < param_2;
  }
  return bVar1;
}

/* 0x003F16C0, 0x110 bytes. */
int func_003F16C0(u32 *param_1)
{
    int aiStack_70[28];
    int iVar1;
    int iVar4;
    int iVar6;
    int lVar3;
    int * piVar5;
    u32 uVar2;

  
  func_00320F00();
  *param_1 = 0;
  lVar3 = func_00327CC0();
  if (lVar3 == 2) {
    iVar4 = 0;
    iVar6 = 0;
    lVar3 = func_0030AB90();
    if (0 < lVar3) {
      piVar5 = aiStack_70;
      do {
        iVar6 = iVar6 + 1;
        *piVar5 = 0x19;
        piVar5 = piVar5 + 1;
        iVar1 = func_0030AB90();
      } while (iVar6 < iVar1);
    }
    iVar6 = 0;
    lVar3 = func_0030AB90();
    if (0 < lVar3) {
      piVar5 = aiStack_70;
      do {
        lVar3 = func_0030B240(iVar6,0);
        if (lVar3 == 1) {
          func_0030B1B0(iVar6,0,2);
          *piVar5 = iVar6;
          iVar4 = iVar4 + 1;
          piVar5 = piVar5 + 1;
        }
        iVar6 = iVar6 + 1;
        iVar1 = func_0030AB90();
      } while (iVar6 < iVar1);
    }
    if (0 < iVar4) {
      func_0030E390(0xc,0,0xffffffffffffffff,0xffffffffffffffff,aiStack_70,iVar4);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x003F17D0, 0x34 bytes, matching. */
int func_003F17D0(void)
{
    int lVar1;
    u32 uStack_4;

  
  uStack_4 = 0;
  lVar1 = func_003F15C0(&uStack_4);
  if (lVar1 == 0) {
    func_003F16C0(&uStack_4);
  }
  return uStack_4;
}

/* 0x003F1900, 0x124 bytes. */
int func_003F1900(u32 *param_1)
{
    u32 auStack_20[8];
    int iVar1;
    int iVar2;
    int iVar6;
    int iVar7;
    int lVar4;
    u32 * puVar5;
    u32 uVar3;

  
  *param_1 = 0;
  lVar4 = func_00327CC0();
  if (lVar4 == 3) {
    uVar3 = 0;
  }
  else {
    iVar7 = 0;
    lVar4 = func_0030AB90();
    if (0 < lVar4) {
      do {
        lVar4 = func_0030B240(iVar7,1);
        if (lVar4 == 2) {
          iVar1 = func_0030C4E0(iVar7,auStack_20);
          func_0030C920(auStack_20,iVar1);
          iVar6 = 0;
          if (0 < iVar1) {
            puVar5 = auStack_20;
            do {
              iVar2 = func_0030B240(*puVar5,1);
              lVar4 = func_0030CB50(*(u32 *)(iVar2 * 4 + 0x45c9a0));
              if (lVar4 != 0) {
                func_0030B1B0(auStack_20[iVar6],1,1);
                break;
              }
              iVar6 = iVar6 + 1;
              puVar5 = puVar5 + 1;
            } while (iVar6 < iVar1);
          }
        }
        iVar7 = iVar7 + 1;
        iVar1 = func_0030AB90();
      } while (iVar7 < iVar1);
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* 0x003F2090, 0x164 bytes. */
int func_003F2090(u32 *param_1)
{
    int aiStack_20[8];
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar6;
    int iVar8;
    int lVar5;
    int * piVar7;
    u32 uVar4;

  
  *param_1 = 0;
  lVar5 = func_00327CC0();
  if (lVar5 == 2) {
    iVar6 = 0;
    lVar5 = func_0030AB90();
    if (0 < lVar5) {
      do {
        func_0030B1B0(iVar6,2,0);
        iVar6 = iVar6 + 1;
        iVar2 = func_0030AB90();
      } while (iVar6 < iVar2);
    }
    lVar5 = func_0030CB50(0xf);
    if (lVar5 != 0) {
      iVar6 = func_0030CB00(2);
      aiStack_20[2] = 2;
      aiStack_20[1] = 1;
      aiStack_20[4] = 4;
      aiStack_20[3] = 3;
      aiStack_20[6] = 6;
      aiStack_20[5] = 5;
      aiStack_20[7] = 7;
      aiStack_20[0] = 0;
      func_0030C920(aiStack_20,8);
      iVar2 = 0;
      if (0 < iVar6 + 1) {
        piVar7 = aiStack_20;
        do {
          iVar1 = *piVar7;
          iVar8 = 0;
          lVar5 = func_0030AB90();
          if (0 < lVar5) {
            do {
              iVar3 = func_0030AC50(iVar8);
              if (iVar1 == iVar3) {
                func_0030B1B0(iVar8,2,1);
              }
              iVar8 = iVar8 + 1;
              iVar3 = func_0030AB90();
            } while (iVar8 < iVar3);
          }
          iVar2 = iVar2 + 1;
          piVar7 = piVar7 + 1;
        } while (iVar2 < iVar6 + 1);
      }
    }
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

/* 0x003F2200, 0x1F4 bytes. */
int func_003F2200(u32 *param_1)
{
    int aiStack_70[28];
    int bVar1;
    int iVar2;
    int iVar3;
    int iVar7;
    int iVar8;
    int lVar5;
    int * piVar6;
    u32 uVar4;

  
  bVar1 = false;
  func_00320F00();
  *param_1 = 0;
  lVar5 = func_00327CC0();
  if (lVar5 == 1) {
    iVar7 = 0;
    iVar8 = 0;
    lVar5 = func_0030AB90();
    if (0 < lVar5) {
      piVar6 = aiStack_70;
      do {
        lVar5 = func_0030B240(iVar8,2);
        if (lVar5 == 1) {
          *piVar6 = iVar8;
          piVar6 = piVar6 + 1;
          iVar7 = iVar7 + 1;
          bVar1 = true;
        }
        iVar8 = iVar8 + 1;
        iVar2 = func_0030AB90();
      } while (iVar8 < iVar2);
    }
    if (bVar1) {
      iVar8 = 0;
      if (0 < iVar7) {
        do {
          piVar6 = aiStack_70 + iVar8;
          func_0030B1B0(*piVar6,2,2);
          iVar2 = func_0030B090(*piVar6);
          if (iVar2 + -1 < 1) {
            iVar2 = 0;
          }
          else {
            iVar2 = func_0030B090(*piVar6);
            iVar2 = iVar2 + -1;
          }
          func_0030B030(*piVar6,iVar2);
          iVar3 = func_0030AD80(*piVar6);
          iVar2 = 10;
          if (10 < (iVar3 * 7) / 10) {
            iVar2 = func_0030AD80(*piVar6,10);
            iVar2 = (iVar2 * 7) / 10;
          }
          func_0030ADC0(*piVar6,iVar2);
          lVar5 = func_0030B240(*piVar6,0);
          if (lVar5 == 1) {
            func_0030B1B0(*piVar6,0,0);
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 < iVar7);
      }
      func_0030E390(0xc,2,0xffffffffffffffff,0xffffffffffffffff,aiStack_70,iVar7);
      uVar4 = 1;
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

/* 0x003F2400, 0x34 bytes, matching. */
int func_003F2400(void)
{
    int lVar1;
    u32 uStack_4;

  
  uStack_4 = 0;
  lVar1 = func_003F2090(&uStack_4);
  if (lVar1 == 0) {
    func_003F2200(&uStack_4);
  }
  return uStack_4;
}

/* 0x003F2440, 0x1CC bytes. */
int func_003F2440(u32 *param_1)
{
    int aiStack_8[2];
    u32 auStack_70[26];
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar7;
    int lVar5;
    int * piVar6;
    u32 uVar4;

  
  iVar1 = func_00327C00();
  *param_1 = 0;
  lVar5 = func_00327CC0();
  if (lVar5 == 0) {
    if (iVar1 - 3U < 3) {
      uVar4 = 0;
    }
    else {
      iVar1 = 0;
      lVar5 = func_0030AB90();
      if (0 < lVar5) {
        do {
          func_0030B1B0(iVar1,3,0);
          iVar1 = iVar1 + 1;
          iVar2 = func_0030AB90();
        } while (iVar1 < iVar2);
      }
      lVar5 = func_0030CB50(0x3c);
      if (lVar5 != 0) {
        iVar1 = func_0030CB00(2);
        iVar1 = iVar1 + 1;
        lVar5 = func_0030CB00(2);
        if (lVar5 == 0) {
          aiStack_8[0] = 2;
        }
        else {
          aiStack_8[0] = 0;
        }
        if (1 < iVar1) {
          if (aiStack_8[0] == 0) {
            lVar5 = func_0030CB50(0x50);
            if (lVar5 == 0) {
              aiStack_8[1] = 1;
            }
            else {
              aiStack_8[1] = 2;
            }
          }
          else {
            lVar5 = func_0030CB50(0x50);
            if (lVar5 == 0) {
              lVar5 = func_0030CB00(2);
              if (lVar5 == 0) {
                aiStack_8[1] = 3;
              }
              else {
                aiStack_8[1] = 1;
              }
            }
            else {
              aiStack_8[1] = 0;
            }
          }
        }
        iVar2 = 0;
        if (0 < iVar1) {
          piVar6 = aiStack_8;
          do {
            iVar3 = func_0030C6E0(auStack_70,*piVar6,*piVar6);
            iVar7 = 0;
            if (0 < iVar3) {
              do {
                func_0030B1B0(auStack_70[iVar7],3,1);
                iVar7 = iVar7 + 1;
              } while (iVar7 < iVar3);
            }
            iVar2 = iVar2 + 1;
            piVar6 = piVar6 + 1;
          } while (iVar2 < iVar1);
        }
      }
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

/* 0x003F2610, 0x124 bytes. */
int func_003F2610(u32 *param_1)
{
    int aiStack_70[28];
    int bVar1;
    int iVar2;
    int iVar5;
    int iVar7;
    int lVar4;
    int * piVar6;
    u32 uVar3;

  
  bVar1 = false;
  func_00320F00();
  *param_1 = 0;
  lVar4 = func_00327CC0();
  if (lVar4 == 3) {
    iVar5 = 0;
    iVar7 = 0;
    lVar4 = func_0030AB90();
    if (0 < lVar4) {
      piVar6 = aiStack_70;
      do {
        lVar4 = func_0030B240(iVar7,3);
        if (lVar4 == 1) {
          *piVar6 = iVar7;
          piVar6 = piVar6 + 1;
          iVar5 = iVar5 + 1;
          bVar1 = true;
        }
        iVar7 = iVar7 + 1;
        iVar2 = func_0030AB90();
      } while (iVar7 < iVar2);
    }
    if (bVar1) {
      iVar7 = 0;
      if (0 < iVar5) {
        do {
          func_0030B1B0(aiStack_70[iVar7],3,2);
          iVar7 = iVar7 + 1;
        } while (iVar7 < iVar5);
      }
      func_0030E390(0xc,3,0xffffffffffffffff,0xffffffffffffffff,aiStack_70,iVar5);
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* 0x003F2740, 0x34 bytes, matching. */
int func_003F2740(void)
{
    int lVar1;
    u32 uStack_4;

  
  uStack_4 = 0;
  lVar1 = func_003F2440(&uStack_4);
  if (lVar1 == 0) {
    func_003F2610(&uStack_4);
  }
  return uStack_4;
}

/* 0x003F2810, 0x134 bytes. */
int func_003F2810(u32 *param_1)
{
    int aiStack_70[28];
    int bVar1;
    int iVar2;
    int iVar5;
    int iVar7;
    int lVar4;
    int * piVar6;
    u32 uVar3;

  
  bVar1 = false;
  func_00320F00();
  *param_1 = 0;
  iVar7 = 0;
  iVar5 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    piVar6 = aiStack_70;
    do {
      lVar4 = func_0030B240(iVar7,4);
      if (lVar4 == 1) {
        *piVar6 = iVar7;
        piVar6 = piVar6 + 1;
        iVar5 = iVar5 + 1;
        bVar1 = true;
      }
      iVar7 = iVar7 + 1;
      iVar2 = func_0030AB90();
    } while (iVar7 < iVar2);
  }
  if (bVar1) {
    iVar7 = 0;
    if (0 < iVar5) {
      piVar6 = aiStack_70;
      do {
        func_0030B1B0(*piVar6,4,2);
        iVar2 = func_0030B090(*piVar6);
        if (iVar2 + -2 < 1) {
          iVar2 = 0;
        }
        else {
          iVar2 = func_0030B090(*piVar6);
          iVar2 = iVar2 + -2;
        }
        func_0030B030(*piVar6,iVar2);
        iVar7 = iVar7 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar7 < iVar5);
    }
    func_0030E390(0xc,4,0xffffffffffffffff,0xffffffffffffffff,aiStack_70,iVar5);
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* 0x003F2A00, 0x44 bytes, matching. */
int func_003F2A00(void)
{
    int lVar1;
    u32 uStack_4;

  
  uStack_4 = 0;
  lVar1 = func_003F2780(&uStack_4);
  if ((lVar1 == 0) && (lVar1 = func_003F2810(&uStack_4), lVar1 == 0)) {
    func_003F2950(&uStack_4);
  }
  return uStack_4;
}
