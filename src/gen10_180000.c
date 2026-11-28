/*
 * gen10_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
 * output (access widths from the disassembly) and kept only when their compiled size is within
 * 25 % of the original (calls and return values checked against the machine code). Machine-like: to be cleaned up by hand later.
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

extern u8 g_00406970[0x28];
extern u8 g_0040CCE0[0x54];
extern u8 g_004160E0[0x10];
extern u8 g_00418E10[0x22];
extern u8 g_00418FD0[0x4];
extern u8 g_00419D10[0x4];
extern u8 g_0041BE30[0x4];
extern u8 g_0041C020[0x34];
extern u8 g_00425CD0[0x24];
extern u8 g_0043C120[0x400];
extern u8 g_0043C168[0x4];
extern u8 g_0043C170[0x4];
extern u8 g_0043C174[0x4];
extern u8 g_0043C188[0x4];
extern u8 g_0043C18C[0x4];
extern u8 g_0043C190[0x4];
extern u8 g_0043C194[0x4];
extern u8 g_0043C1D8[0x4];
extern u8 g_0043C220[0x4];
extern u8 g_0043C228[0x4];
extern u8 g_0043C22C[0x4];
extern u8 g_0043C240[0x4];
extern u8 g_0043C244[0x4];
extern u8 g_0043C248[0x4];
extern u8 g_0043C24C[0x4];
extern u8 g_0043C55C[0x4];
extern u8 g_004420E0[0x10];
extern u8 g_00459B60[0x8];
extern u8 g_0045B4F0[0xC];
extern u8 g_0050074C[0x1A];
extern u8 g_0056CCA4[0x24];
extern u8 g_0056CCC0[0x8];
extern u8 g_00574F58[0x2];
extern u8 g_00575588[0x2];
extern u8 g_005BA690[0x10];
extern u8 g_005BA694[0x10];
extern u8 g_005BA6A0[0x4];
extern u8 g_005BC028[0x4];
extern u8 g_005BC03C[0x28];
extern u8 g_005BC3A0[0x5];
extern u8 g_00669DB0[0x1];
extern u8 g_00669DB2[0x2];
extern u8 g_00669DB8[0x7C];
extern u8 g_00669F60[0x4];
extern u8 g_00669F84[0x14];
extern u8 g_00669F9C[0x8];
extern u8 g_0068F0F0[0x8];
extern u8 g_0068F100[0x8];
extern u8 g_00693388[0x4];
extern u8 g_006934B9[0x1];
extern u8 g_00693703[0x4];
extern u8 g_0069382B[0x1];
extern u8 g_006A1D58[0x4];
extern u8 g_006A1DA4[0x4];
extern u8 g_006A3A34[0x4];
extern u8 g_006A3A44[0x4];
extern u8 g_006A3AB0[0x4];
extern u8 g_006A3AB2[0x4];
extern u8 g_006A3AB4[0x4];
extern u8 g_006C3598[0x4];
extern u8 g_007315A0[0x38];
extern u8 g_00732220[0x10];
extern u8 g_00732508[0x10];
extern u8 g_00732514[0x4];
extern u8 g_00732528[0x4];
extern u8 g_0073253C[0x4];
extern u8 g_00732541[0x4];
extern u8 g_00732546[0x4];
extern u8 g_0073254B[0x4];
extern u8 g_00732550[0x4];
extern u8 g_00732555[0x4];
extern u8 g_0073255B[0x1];
extern u8 g_007325E4[0x4];
extern u8 g_007325EC[0x4];
extern u8 g_007325F0[0x4];
extern u8 g_007325F4[0x4];
extern u8 g_007325FC[0x4];
extern u8 g_00732604[0x4];
extern u8 g_00732608[0x4];
extern u8 g_0073260D[0x4];
extern u8 g_0073260E[0x4];
extern u8 g_00732612[0x4];
extern u8 g_00732644[0x4];
extern u8 g_00732648[0x4];
extern u8 g_0073264C[0x4];
extern u8 g_0073264D[0x4];
extern u8 g_0073264E[0x4];
extern u8 g_0073264F[0x4];
extern u8 g_00732650[0x4];
extern u8 g_0073C79A[0x4];
extern u8 g_0074B808[0x4];
extern u8 g_0074B818[0x1C];
extern u8 g_0075294C[0x4];
extern u8 g_00753190[0x10];
extern u8 g_0076F3A0[0x10];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F3D4[0xC];
extern u8 g_0076F634[0x4];
extern u8 g_0076F7B0[0x8];
extern u8 g_00773418[0x4];
extern u8 g_00773440[0x4];
extern u8 g_00773444[0x4];
extern u8 g_00773448[0x4];
extern u8 g_0077344C[0x4];
extern u8 g_00773450[0x4];
extern u8 g_00773454[0x4];
extern u8 g_0077BEF0[0x4];
extern u8 g_0077CFA4[0x4];
extern u8 g_0077CFA8[0x4];
extern u8 g_0077CFA9[0x4];
extern u8 g_0077CFAA[0x4];
extern u8 g_00799A6C[0x4];
extern u8 g_007B98A4[0xC];
extern u8 g_007BA7DD[0x1];
extern u8 g_007BA81D[0x1];
extern u8 g_007BA8B8[0x10];
extern u8 g_007BAA60[0x4];
extern u8 g_007BACB4[0x14];
extern u8 g_007BAD30[0x1C];
extern u8 g_007BAD58[0x4];
extern u8 g_007BAE7C[0x8];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern u8 g_007BEAD4[0x8];
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D400;   /* (small data) */
extern int g_0045D430;   /* (small data) */
extern int g_0045D434;   /* (small data) */
extern int g_0045D460;   /* (small data) */
extern int g_0045D488;   /* (small data) */
extern int g_0045D48C;   /* (small data) */
extern int g_0045D500;   /* (small data) */
extern int g_0045D574;   /* (small data) */
extern int g_0045D578;   /* (small data) */
extern int g_0045D5EC;   /* (small data) */
extern int g_0045D5F0;   /* (small data) */
extern int g_0045D5F4;   /* (small data) */
extern int g_0045D6EC;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_700000C0 (*(int *)PS2_PTR(0x700000C0))   /* (scratchpad) */
#define g_700000C4 (*(int *)PS2_PTR(0x700000C4))   /* (scratchpad) */
#define g_700000C8 (*(int *)PS2_PTR(0x700000C8))   /* (scratchpad) */
#define g_700000CC (*(int *)PS2_PTR(0x700000CC))   /* (scratchpad) */
#define g_70000150 (*(int *)PS2_PTR(0x70000150))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_7000088C (*(int *)PS2_PTR(0x7000088C))   /* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))   /* (scratchpad) */

int func_001020C0();
int func_00102680();
int func_00102960();
int func_00102EC0();
int func_001050B0();
int func_001057F0();
int func_00105A30();
int func_00106C90();
int func_00114470();
int func_001185B0();
int func_00118850();
int func_00118AC0();
int func_001204B0();
void *func_001206B0();
void *func_00120928();
int func_00143D60();
int func_00146270();
int func_00146D80();
int func_00149620();
int func_0014FCA0();
int func_0017E010();
int func_0017E110();
int func_00183E70();
int func_001904E0();
int func_00190590();
void *func_0019FBC0();
int func_001A7DC0();
void func_001A85D0(float a, float b, float size, int x, int y, int z, int ia, int ib, int w, int layer);
int func_001ABE40();
int func_001ABEA0();
int func_001AFE20();
void *func_001BE5E0();
void *func_001BE630();
void *func_001BE680();
void *func_001BE6D0();
int func_001CCFA0();
int func_001D9BC0();
int func_001DCF10();
void func_001E01D0(float, int);
int func_001E1480();
int func_001E95F0();
int func_001E96D0();
int func_001E96E0();
int func_001E98E0();
int func_001E9980();
int func_001EA220();
int func_001EE9C0();
void *func_001F14E0();
int func_001F45E0();
int func_001F7980();
int func_001FA790();
int func_00204CD0();
int func_00204D00();
int func_00204D20();
int func_00206080();
int func_00207930();
int func_0020E140();
int func_0020E170();
int func_0020E230();
int func_00215850();
void *func_002185B0();
void *func_0021A630();
int func_0022DD50();
int func_0022DD70();
int func_0022DD80();
int func_0022DDC0();
int func_0022DE00();
int func_0022DE50();
int func_0022F730();
int func_00238710();
int func_0023A4F0();
int func_0023A5C0();
int func_0023AA40();
int func_0023AD10();
int func_0023B530();
int func_002431F0();
int func_002492C0();
int func_0024A9B0();
int func_0024BAB0();
int func_0024E440();
int func_00253300();
int func_0025EE30();
int func_00261470();
int func_00262AD0();
int func_00267D10();
int func_002688F0();
int func_00269DF0();
int func_0026CCD0();
int func_0026FF00();
int func_002705B0();
int func_00278150();
int func_0029C8B0();
int func_0029C9E0();
int func_002A59F0();
int func_002A64C0();
int func_002C7310();
int func_002D07E0();
int func_002D82C0();
int func_002D8730();
void *func_002EE540();
int func_002F27D0();
int func_002F3440();
int func_002F3960();
int func_002F3CF0();
int func_002F4080();
int func_002F41E0();
int func_002F4820();
int func_002F4BB0();
int func_002F4D40();
int func_002F4ED0();
int func_002F5060();
int func_002F51F0();
int func_002F5380();
int func_002F5510();
int func_002F56A0();
int func_002F5930();
int func_002F5A10();
int func_002F5DA0();
int func_002F5EF0();
int func_002F6040();
int func_002F6190();
int func_002F62E0();
int func_002F6430();
int func_002F6580();
int func_002F66D0();
int func_002F69F0();
int func_002F6A60();
int func_002F6AD0();
int func_002F6BB0();
int func_002F6C20();
int func_002F6C90();
int func_002F6D10();
int func_002F6D80();
int func_002F6E70();
int func_002F6F60();
int func_002FA790();
int func_002FAFA0();
int func_002FB100();
int func_002FB120();
int func_002FB1A0();
int func_002FB220();
int func_002FB2D0();
int func_002FB3B0();
int func_002FC0C0();
void *func_002FC2C0();
int func_0030AB90();
int func_0030AD80();
int func_0030AE80();
int func_0030AFF0();
int func_0030B2F0();
int func_0030B330();
int func_0030B640();
int func_0030C890();
void *func_0030D7D0();
int func_003239F0();
int func_00327D50();
int func_0032F2A0();
int func_0032F2E0();
int func_0032F420();
int func_0032F7D0();
int func_00334A50();
void *func_00338410();
int func_00362B60();
int func_0036D2E0();
int func_0036D6D0();
int func_0036FD30();
void *func_00372DD0();
void *func_00372DF0();
int func_00375B90();
void *func_003766C0();
void *func_00376810();
int func_00388200();
void *func_00391250();
int func_003914C0();
int func_00391A10();
int func_00391C30();
int func_00391CC0();
int func_00391E60();
int func_00391EB0();
int func_00391F50();
int func_00396530();
int func_00396680();
int func_00397660();
int func_00397B00();
int func_0039A570();
int func_0039A5B0();
int func_0039A630();
int func_0039D5C0();
int func_0039D740();
int func_0039D7E0();
int func_0039E700();
int func_0039E720();
int func_0039E780();
int func_0039E7A0();
int func_0039E7C0();
int func_0039FBF0();
int func_003A0320();
int func_003A0380();
int func_003A0D90();
int func_003A17A0();
int func_003A1830();
int func_003A1FC0();
void *func_003A2050();
int func_003A20D0();
int func_003A2150();
int func_003A21D0();
int func_003A2290();
int func_003A2320();
int func_003A23A0();
int func_003A2450();
int func_003A2500();
int func_003A2580();
int func_003A2600();
int func_003A26E0();
int func_003A64A0();
int func_003A97C0();
int func_003AE8E0();
int func_003B5300();
int func_003B55E0();
int func_003BFD80();
int func_003D3B50();
int func_003D3CD0();
float func_003D3E40(int v, int kind);
int func_003DB220();
int func_003DB460();
int func_003DB480();
int func_003DC090();
int func_003DC0E0();
int func_003DC180();
int func_003DF490();
int func_003E46B0();
void *func_003E46F0();
int func_003E4BE0();
int func_003E74B0();
int func_003E9630();
int func_003E9700();
int func_003E9750();
int func_003E97D0();
int func_003EE4A0();
int func_003F0CE0();
float func_00183840(void);
void func_00184100(void);
int func_00184AE0(u8 *param_1, int param_2, int param_3);
int func_001D9C80(u8 *param_1, int param_2, int param_3, int param_4);
void func_001DD0F0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_001E1680(int param_1, int param_2);
void func_001E96F0(int param_1);
void func_001E9D30(int param_1);
void func_001EA860(u8 *param_1, int param_2, int param_3);
void func_001EC380(u8 *param_1);
float func_001ECC10(u8 *param_1, int param_2);
int func_001ED240(u8 *param_1, int param_2);
void func_001EF190(u8 *param_1, int param_2, int param_3, int param_4);
void func_001F78E0(void);
void func_001FA620(void);
void func_001FAF00(int param_1);
void func_001FB6C0(void);
void func_00200290(u32 *param_1, int param_2);
void func_0020EAA0(int param_1, int param_2);
void func_00215790(void);
int func_0022B890(u8 *param_1, u32 *param_2);
void func_0022EF90(u8 *param_1, int param_2, int param_3);
void func_0022F510(void);
void func_00236ED0(u8 *param_1);
int func_00236F30(u8 *param_1);
int func_00237D00(u8 *param_1);
int func_00238930(u8 *param_1, float *param_2);
int func_00238F50(u8 *param_1);
int func_00243C50(u8 *param_1);
void func_00243DF0(u8 *param_1, u8 *param_2);
void func_00245D60(void);
int func_00245F20(int param_1, u8 *param_2);
void func_00247FA0(int param_1, int param_2, int param_3);
void func_0024BF60(void);
void func_0025C160(u8 *param_1, int param_2);
void func_00269740(int param_1);
void func_00269AF0(int param_1);
int func_00273770(u8 *param_1, int param_2, float *param_3);
void func_00278500(void);
void func_002789C0(void);
void func_0027A040(void);
void func_0029CB20(int param_1, int param_2, u8 *param_3);
void func_002A5A60(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_002A5C40(int param_1);
int func_002A6550(int param_1, int param_2, int param_3);
int func_002A7F20(int param_1, u8 *param_2);
int func_002C1830(int param_1, int param_2, int param_3);
void func_002CCDB0(int param_1, u8 *param_2);
void func_002CDD40(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002CE0C0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002CE110(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002D6930(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002D6BF0(void);
int func_002D6FE0(int param_1);
void func_002D75C0(u8 *param_1);
void func_002D9310(u8 *param_1);
void func_002D9400(u8 *param_1);
void func_002D9EE0(u8 *param_1);
void func_002DB9A0(void);
void func_0032C940(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_003701E0(int param_1, int param_2, int param_3, int param_4);
void func_00373050(void);
int func_003890D0(u8 *param_1);
int func_00389150(u8 *param_1);
int func_00389770(u8 *param_1);
int func_003898F0(u8 *param_1);
int func_003899E0(u8 *param_1);
int func_00393D30(void);
int func_00394100(void);
void func_003967D0(int param_1);
void func_00398C90(int param_1, int param_2, int param_3, int param_4);
void func_00399EE0(void);
void func_0039D770(void);
void func_0039D820(void);
void func_0039EB40(int param_1);
void func_003A0220(int param_1, int param_2);
void func_003A37D0(int param_1, int param_2);
void func_003A6060(int *param_1, int *param_2, int param_3);
int func_003A62E0(int param_1, int *param_2, int *param_3);
void func_003A70D0(void);
void func_003A8130(int *param_1, int *param_2, int *param_3);
int func_003AAF80(int param_1, int param_2, int param_3);
int func_003AEB80(void);
void func_003AF960(void);
int func_003BFDF0(void);
void func_003D47A0(int param_1, int param_2, int param_3, int param_4);
int func_003E4F40(void);
void func_003EEAE0(void);
int func_003F0A00(u8 *param_1);
void func_003F0EC0(int param_1, int param_2, u8 *param_3);

/* 0x00183840, 0x164 bytes. */
float func_00183840(void)
{
    int bVar1;
    float fVar2;

  
  if (((*(u32 *)(g_00669DB8 + 0x0)) == 3) && (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0)) {
    bVar1 = func_002F41E0((*(u32 *)(g_00669DB8 + 0x78)));
    fVar2 = (float)bVar1;
  }
  else {
    bVar1 = func_002F41E0((*(u32 *)(g_00669DB8 + 0x30)));
    fVar2 = (float)bVar1;
    if (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) {
      bVar1 = func_002F41E0((*(u32 *)(g_00669DB8 + 0x78)));
      fVar2 = (fVar2 + (float)bVar1) * 0.5;
    }
  }
  return (fVar2 * 2.0) / 165.0 + 0.9;
}

/* 0x00184100, 0x168 bytes. */
void func_00184100(void)
{
    int aiStack_30[4];
    int iVar1;
    u8 * iVar3;
    int iVar6;
    int * piVar2;
    u16 * puVar4;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    u32 uStack_c;
    u32 uVar5;

  
  iVar6 = 0;
  iVar3 = g_005BA690;
  aiStack_30[0] = (*(u32 *)(g_00406970 + 0x0));
  aiStack_30[1] = (*(u32 *)(g_00406970 + 0x4));
  aiStack_30[2] = (*(u32 *)(g_00406970 + 0x8));
  aiStack_30[3] = (*(u32 *)(g_00406970 + 0xC));
  uStack_20 = (*(u32 *)(g_00406970 + 0x10));
  uStack_1c = (*(u32 *)(g_00406970 + 0x14));
  uStack_18 = (*(u32 *)(g_00406970 + 0x18));
  uStack_14 = (*(u32 *)(g_00406970 + 0x1C));
  uStack_10 = (*(u32 *)(g_00406970 + 0x20));
  uStack_c = (*(u32 *)(g_00406970 + 0x24));
  do {
    uVar5 = 0;
    piVar2 = (int *)(*(int *)(iVar3 + 0x14) + *(int *)(*(int *)(iVar3 + 0x14) + 4));
    iVar1 = *piVar2;
    puVar4 = (u16 *)(piVar2 + 4);
    if (iVar1 != 4) {
      do {
        func_00183E70((*(u32 *)(g_005BA6A0 + 0x0)) + ((u32)*puVar4 * 10 + (u32)*puVar4) * 4);
        uVar5 = uVar5 + 1;
        puVar4 = puVar4 + 0x10;
      } while (uVar5 < iVar1 - 4U);
    }
    iVar6 = iVar6 + 1;
    iVar3 = iVar3 + 4;
  } while (iVar6 < 5);
  uVar5 = 0;
  piVar2 = aiStack_30;
  do {
    func_00183E70((*(u32 *)(g_005BA6A0 + 0x0)) + *piVar2 * 0x2c);
    uVar5 = uVar5 + 1;
    piVar2 = piVar2 + 1;
  } while (uVar5 < 10);
  return;
}
/* MISSING ['0x406970', '0x406974', '0x406978', '0x40697c', '0x406980', '0x406984', '0x406988', '0x40698c', '0x406990', '0x406994'] */

/* 0x00184AE0, 0x2EC bytes. */
int func_00184AE0(u8 *param_1, int param_2, int param_3)
{
    int uVar1;

  
  if (param_2 == 2) {
    if ((((param_3 == 0x7a) || (param_3 == 0x79)) || (param_3 == 0x78)) ||
       ((param_3 == 0x77 || (param_3 == 0x76)))) {
      uVar1 = 0xb;
    }
    else if (((param_3 == 0x7f) || (param_3 == 0x6a)) ||
            ((param_3 == 0x69 || ((param_3 == 0x68 || (param_3 == 0x67)))))) {
      uVar1 = 0x14;
    }
    else if (((((param_3 == 0x83) || (param_3 == 0x82)) || (param_3 == 0x81)) ||
             ((param_3 == 0x80 || (param_3 == 0x31)))) ||
            (((param_3 == 0x30 || ((param_3 == 0x2f || (param_3 == 0x2e)))) || (param_3 == 0x2d))))
    {
      uVar1 = 0x11;
    }
    else if ((((param_3 == 0x93) || (param_3 == 0x92)) || (param_3 == 0x74)) ||
            (((param_3 == 0x73 || (param_3 == 0x2a)) || ((param_3 == 0x29 || (param_3 == 0x28))))))
    {
      uVar1 = 0x13;
    }
    else if (((param_3 == 0x84) || (param_3 == 0x6b)) || ((param_3 == 0x4c || (param_3 == 0x1f)))) {
      uVar1 = 0x15;
    }
    else if ((((param_3 == 0xec) || (param_3 == 0xe5)) || (param_3 == 0xe4)) ||
            ((((param_3 == 0xe3 || (param_3 == 0xe2)) ||
              ((param_3 == 0xe1 || ((param_3 == 0x91 || (param_3 == 0x90)))))) ||
             (((param_3 == 0x8f ||
               (((((param_3 == 0x8e || (param_3 == 0x8d)) || (param_3 == 0x7e)) ||
                 ((param_3 == 0x48 || (param_3 == 0x47)))) || (param_3 == 0x46)))) ||
              (((param_3 == 0x45 || (param_3 == 0x44)) || ((param_3 == 0x1d || (param_3 == 0x1c)))))
              ))))) {
      uVar1 = 0x12;
    }
    else if (((((param_3 == 0x87) || (param_3 == 0x75)) || (param_3 == 0x57)) ||
             ((param_3 == 0x4d || (param_3 == 0x20)))) || (param_3 == 10)) {
      uVar1 = 0x17;
    }
    else {
      uVar1 = *(u8 *)(param_1 + 1);
    }
  }
  else {
    uVar1 = *(u8 *)(param_1 + 1);
  }
  return uVar1;
}

/* 0x001D9C80, 0x578 bytes. */
int func_001D9C80(u8 *param_1, int param_2, int param_3, int param_4)
{
    int bVar5;
    int iVar2;
    long long lVar4;
    u32 uVar1;
    unsigned long long uVar3;

  
  bVar5 = false;
  if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
    uVar1 = 0x54;
  }
  else {
    uVar1 = (u32)(*(u8 *)(g_0073C79A + 0x0));
    if ((*(u32 *)(g_00669DB8 + 0x0)) == 3) {
      uVar1 = 0x55;
    }
  }
  param_2 = param_2 & 0xffff;
  if (param_2 == 0x3e9) {
    if (param_3 == *(u8 *)((*(u8 *)(g_0073C79A + 0x3)) + 0x73c79b)) {
      bVar5 = true;
    }
  }
  else if (param_2 == 1000) {
    uVar1 = func_0032F420(0);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if ((((param_2 == 0x3ba) || (param_2 == 0x3b9)) || (param_2 == 0x3b8)) ||
          ((param_2 == 0x3b7 || (param_2 == 0x3b6)))) {
    uVar3 = func_0032F420(param_2 - 0x3b5);
    uVar1 = func_0032F2E0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 900) {
    uVar1 = func_0032F420(0);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (((param_2 == 0x22) || (param_2 == 0x21)) ||
          ((param_2 == 0x20 || ((param_2 == 0x1f || (param_2 == 0x1e)))))) {
    uVar3 = func_0032F420(param_2 - 0x1d);
    uVar1 = func_0032F2A0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 0x1d) {
    uVar3 = func_0032F420(0);
    uVar1 = func_0032F2A0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 0x1c) {
    uVar1 = func_0020E230(0x41);
    bVar5 = param_3 == *(u8 *)((*(u32 *)(g_005BA694 + 0xC)) + (uVar1 & 0xffff) * 0x2c + 6);
    if ((((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) &&
       (uVar1 = func_0020E230(0x42), param_3 == *(u8 *)((*(u32 *)(g_005BA694 + 0xC)) + (uVar1 & 0xffff) * 0x2c + 6)
       )) {
      bVar5 = true;
    }
  }
  else if ((((param_2 == 0x1b) || (param_2 == 0x1a)) || (param_2 == 0x19)) ||
          ((param_2 == 0x18 || (param_2 == 0x17)))) {
    iVar2 = func_0032F420(param_2 - 0x16);
    if (param_3 == *(u8 *)((*(u32 *)(g_005BA694 + 0xC)) + iVar2 * 0x2c + 6)) {
      bVar5 = true;
    }
  }
  else if (param_2 == 0x16) {
    iVar2 = func_0032F420(0);
    if (param_3 == *(u8 *)((*(u32 *)(g_005BA694 + 0xC)) + iVar2 * 0x2c + 6)) {
      bVar5 = true;
    }
  }
  else if (param_2 == 0x15) {
    lVar4 = func_00334A50();
    if (lVar4 != 0) {
      bVar5 = true;
    }
  }
  else if (((param_2 == 0x14) || (param_2 == 0x13)) ||
          ((param_2 == 0x12 || ((param_2 == 0x11 || (param_2 == 0x10)))))) {
    uVar3 = func_0032F420(param_2 - 0xf);
    uVar1 = func_0032F7D0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 0xf) {
    uVar3 = func_0032F420(0);
    uVar1 = func_0032F7D0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if ((((param_2 == 0xe) || (param_2 == 0xd)) || (param_2 == 0xc)) ||
          ((param_2 == 0xb || (param_2 == 10)))) {
    uVar3 = func_0032F420(param_2 - 9);
    uVar1 = func_0032F2E0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 9) {
    uVar3 = func_0032F420(0);
    uVar1 = func_0032F2E0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (((param_2 == 8) || (param_2 == 7)) ||
          ((param_2 == 6 || ((param_2 == 5 || (param_2 == 4)))))) {
    uVar3 = func_0032F420(param_2 - 3);
    uVar1 = func_001D9BC0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 3) {
    uVar3 = func_0032F420(0);
    uVar1 = func_001D9BC0(uVar3);
    if (param_3 == uVar1) {
      bVar5 = true;
    }
  }
  else if (param_2 == 2) {
    if (param_3 == *(u32 *)(param_1 + 0x18)) {
      bVar5 = true;
    }
  }
  else if (param_2 == 1) {
    if (param_3 == *(u8 *)((*(u32 *)(g_005BA694 + 0x0)) + uVar1 * 100)) {
      bVar5 = true;
    }
  }
  else if ((param_2 == 0) && (param_3 == (*(u8 *)(g_0073C79A + 0x0)))) {
    bVar5 = true;
  }
  if (param_4 == 0) {
    bVar5 = bVar5 != true;
  }
  return bVar5;
}

/* 0x001DD0F0, 0x254 bytes. */
void func_001DD0F0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar2;
    int iVar4;
    int iVar5;
    long long lVar1;
    int * piVar3;
    u32 * puVar7;
    u32 uVar6;

  
  if ((param_3 & 0xffff) != 0x252) {
    func_001DCF10(param_2,param_3,param_5);
    puVar7 = (u32 *)param_2;
    uVar6 = 0;
    if (*puVar7 != 0) {
      iVar4 = 0;
      do {
        piVar3 = (int *)(puVar7[1] + iVar4);
        if (*(u8 *)((int)piVar3 + 0xe) != 0xff) {
          iVar2 = (u32)*(u8 *)((int)piVar3 + 0xe) * 0x30;
          iVar5 = iVar2 + 0x6c3590;
          if (*(int *)(g_006C3598 + iVar2) == 0) {
            return;
          }
          if ((char)piVar3[3] == '\0') {
            lVar1 = func_0020E140();
            if ((lVar1 == 0) && (lVar1 = func_0020E170(), lVar1 == 0)) {
              lVar1 = PS2_ADDR(func_001BE5E0());
            }
            else {
              lVar1 = PS2_ADDR(func_001BE680());
            }
            if (lVar1 == 0) {
              return;
            }
            func_0014FCA0(lVar1,iVar5);
            iVar2 = (int)lVar1;
            *piVar3 = iVar2;
            *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x168) = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x168) & 0xfe | 1;
            *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x165) = *(u8 *)((int)piVar3 + 0xd);
          }
          else {
            lVar1 = func_0020E140();
            if ((lVar1 == 0) && (lVar1 = func_0020E170(), lVar1 == 0)) {
              lVar1 = PS2_ADDR(func_001BE630());
            }
            else {
              lVar1 = PS2_ADDR(func_001BE6D0());
            }
            if (lVar1 == 0) {
              return;
            }
            func_00149620(lVar1,iVar5,0);
            iVar2 = (int)lVar1;
            *piVar3 = iVar2;
            *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x20c) = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x20c) & 0xfe | 1;
            *(u32 *)((u8 *)PS2_PTR(iVar2) + 0x1fc) = param_4;
            *(u8 *)((u8 *)PS2_PTR(iVar2) + 0x201) = *(u8 *)((int)piVar3 + 0xd);
          }
          iVar2 = *(int *)((param_1 & 0xffff) * 8 +
                           *(int *)(g_0045D3E0 * 0x38 +
                                    (u32)*(u8 *)((param_1 & 0xffff) +
                                                   *(int *)(g_0045D3E0 * 0x38 + 0x730dfc)) * 4 +
                                   0x730e08) + 4) + (uVar6 & 0xffff) * 0x10;
          *(u8 *)((u8 *)PS2_PTR(iVar2) + 0xf) = *(u8 *)((u8 *)PS2_PTR(iVar2) + 0xf) | 2;
        }
        uVar6 = uVar6 + 1;
        iVar4 = iVar4 + 0x10;
      } while (uVar6 < *puVar7);
    }
  }
  return;
}

/* 0x001E1680, 0x158 bytes. */
void func_001E1680(int param_1, int param_2)
{
    int cVar3;
    float fVar8;
    int iVar5;
    int iVar6;
    int iVar7;
    u32 * puVar4;
    int uVar1;
    u32 uVar2;

  
  iVar7 = 0;
  cVar3 = '0';
  iVar6 = 0;
  fVar8 = 0.0;
  do {
    cVar3 = cVar3 + -6;
    fVar8 = fVar8 - 0.3;
    uVar1 = *(u16 *)((param_1 & 0xffff) * 8 + *(int *)(g_0045D3E0 * 0x38 + 0x730e10) + iVar6);
    iVar5 = (u32)uVar1 * 4;
    puVar4 = (u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730e04) + iVar5);
    *puVar4 = *puVar4 | 2;
    uVar2 = *(u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730de0) + iVar5);
    func_001E01D0(fVar8,uVar1);
    func_001E1480(uVar1,uVar2,param_2,cVar3);
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 2;
    puVar4 = (u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730e04) + iVar5);
    *puVar4 = *puVar4 & 0xfffffffd;
  } while (iVar7 < 4);
  return;
}

/* 0x001E96F0, 0xDC bytes. */
void func_001E96F0(int param_1)
{
    int iVar1;

  
  func_001E96D0();
  func_001E96E0();
  if (param_1 < 0x47) {
    if ((*(u8 *)(g_00669DB0 + 0x0)) >> 6 == 0) {
      g_0045D400 = 0;
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
      g_0045D400 = 1;
    }
  }
  else {
    g_0045D400 = 0;
    iVar1 = 0;
  }
  if (iVar1 != 0) {
    if (iVar1 == 2) {
      func_001EA220(param_1);
    }
    else if (iVar1 == 1) {
      func_001E98E0(param_1);
    }
    else if (iVar1 == 3) {
      func_001E98E0(param_1);
      func_001EA220(param_1);
    }
  }
  return;
}

/* 0x001E9D30, 0x354 bytes. */
void func_001E9D30(int param_1)
{
    u8 auStack_8[4];
    float fVar9;
    int iStack_4;
    int iVar6;
    int iVar7;
    int iVar8;
    int * piVar2;
    int * piVar3;
    int * piVar4;
    int * piVar5;
    u32 uVar1;

  
  if ((*(u32 *)(g_007315A0 + 0x0)) <= param_1) {
    if ((*(u32 *)(g_007315A0 + 0x4)) < param_1) {
      if (((*(u32 *)(g_007315A0 + 0x4)) < param_1) && ((*(u32 *)(g_007315A0 + 0x34)) <= (*(u32 *)(g_007315A0 + 0x30)))) {
        func_001E9980();
      }
    }
    else {
      if ((float)((*(u32 *)(g_007315A0 + 0x4)) - param_1) <= 5.0) {
        fVar9 = ((float)((*(u32 *)(g_007315A0 + 0x4)) - param_1) / 5.0) * 128.0;
        if (2.1474836e+09 <= fVar9) {
          fVar9 = fVar9 - 2.1474836e+09;
        }
        uVar1 = (int)fVar9 & 0xff;
      }
      else if ((float)(param_1 - (*(u32 *)(g_007315A0 + 0x0))) <= 5.0) {
        fVar9 = ((float)(param_1 - (*(u32 *)(g_007315A0 + 0x0))) / 5.0) * 128.0;
        if (2.1474836e+09 <= fVar9) {
          fVar9 = fVar9 - 2.1474836e+09;
        }
        uVar1 = (int)fVar9 & 0xff;
      }
      else {
        uVar1 = 0x80;
      }
      iVar7 = 0;
      piVar5 = (int *)0x731390;
      piVar4 = piVar5;
      piVar3 = piVar5;
      do {
        if (*piVar5 == 0) {
          return;
        }
        iVar8 = piVar4[0x88];
        iVar6 = 0;
        if ((char)piVar3[0x8c] != '\0') {
          piVar2 = piVar5;
          do {
            func_001E95F0(piVar2,iVar8,piVar4[0x8a],uVar1,0);
            (*(u32 *)(g_0056CCC0 + 0x0)) = 0x41a00000;
            (*(u32 *)(g_0056CCC0 + 0x4)) = 0x41a00000;
            func_00146D80(*piVar2,&iStack_4,auStack_8);
            (*(u32 *)(g_0056CCC0 + 0x0)) = 0x41800000;
            iVar6 = iVar6 + 1;
            piVar2 = piVar2 + 3;
            (*(u32 *)(g_0056CCC0 + 0x4)) = 0x41800000;
            iVar8 = iVar8 + iStack_4;
          } while (iVar6 < (int)(u32)*(u8 *)(piVar3 + 0x8c));
        }
        iVar7 = iVar7 + 1;
        piVar5 = piVar5 + 0x42;
        piVar4 = piVar4 + 1;
        piVar3 = (int *)((int)piVar3 + 1);
      } while (iVar7 < 2);
    }
  }
  return;
}

/* 0x001EA860, 0x37C bytes. */
void func_001EA860(u8 *param_1, int param_2, int param_3)
{
    int bVar1;
    int iVar6;
    long long lVar10;
    long long lVar8;
    long long lVar9;
    int sVar2;
    int sVar3;
    int sVar5;
    int sVar7;
    u32 uVar4;

  
  if (param_3 == 0) {
    if ((*(u32 *)(param_1 + 0x80) & 0x400) == 0) {
      lVar10 = 1;
    }
    else {
      lVar10 = (long long)*(short *)(param_1 + 0x4e);
    }
    lVar8 = (long long)(int)((int)lVar10 + (u32)*(u8 *)(param_1 + 0x74));
  }
  else {
    lVar8 = 0;
    lVar10 = 0;
  }
  if (param_2 < 2) {
    param_2 = 1;
    uVar4 = *(u32 *)(param_1 + 0x80);
  }
  else {
    uVar4 = *(u32 *)(param_1 + 0x80);
  }
  if ((uVar4 & 0x8000) == 0) {
    lVar9 = (long long)((int)*(short *)(param_1 + 0x52) - (int)param_2);
    if (lVar8 < lVar9) {
      sVar3 = *(short *)(param_1 + 0x50);
      lVar8 = lVar9;
    }
    else {
      sVar3 = *(short *)(param_1 + 0x50);
    }
    sVar5 = (short)lVar8;
    sVar2 = sVar5;
    if (sVar3 < sVar5) {
      sVar2 = sVar3;
    }
    if (sVar2 < 1) {
      sVar3 = 0;
    }
    else if (sVar5 <= sVar3) {
      sVar3 = sVar5;
    }
    *(short *)(param_1 + 0x52) = sVar3;
    if (*(char *)(param_1 + 0x74) == '\0') {
      lVar9 = (long long)((int)*(short *)(param_1 + 0x4e) - (int)param_2);
      if (lVar10 < lVar9) {
        sVar3 = *(short *)(param_1 + 0x4c);
        lVar10 = lVar9;
      }
      else {
        sVar3 = *(short *)(param_1 + 0x4c);
      }
      sVar7 = (short)lVar10;
      sVar2 = sVar7;
      if (sVar3 < sVar7) {
        sVar2 = sVar3;
      }
      if (sVar2 < 1) {
        sVar3 = 0;
      }
      else if (sVar7 <= sVar3) {
        sVar3 = sVar7;
      }
      *(short *)(param_1 + 0x4e) = sVar3;
    }
    if (lVar8 < *(short *)(param_1 + 0x4e)) {
      sVar3 = *(short *)(param_1 + 0x4c);
      if (sVar3 < sVar5) {
        sVar2 = sVar3;
      }
      else {
        sVar2 = sVar5;
      }
      if (sVar2 < 1) {
        sVar3 = 0;
      }
      else if (sVar5 <= sVar3) {
        sVar3 = sVar5;
      }
      *(short *)(param_1 + 0x4e) = sVar3;
    }
  }
  else {
    iVar6 = *(int *)(param_1 + 0x14) * 0xc0;
    if (param_2 < *(short *)(g_006A3AB2 + iVar6)) {
      sVar5 = *(short *)(g_006A3AB2 + iVar6) - (short)param_2;
      sVar3 = *(short *)(g_006A3AB0 + iVar6);
      sVar2 = sVar5;
      if (sVar3 < sVar5) {
        sVar2 = sVar3;
      }
      if (sVar2 < 1) {
        sVar3 = 0;
      }
      else if (sVar5 <= sVar3) {
        sVar3 = sVar5;
      }
      *(short *)(g_006A3AB2 + iVar6) = sVar3;
      if (*(short *)(g_006A3AB4 + iVar6) < sVar3) {
        *(short *)(g_006A3AB4 + iVar6) = sVar3;
      }
    }
    else {
      sVar3 = *(short *)(g_006A3AB0 + iVar6);
      sVar2 = sVar3;
      if (-1 < sVar3) {
        sVar2 = 0;
      }
      if (sVar2 < 1) {
        sVar3 = 0;
      }
      else if (-1 < sVar3) {
        sVar3 = 0;
      }
      *(short *)(g_006A3AB2 + iVar6) = sVar3;
      if (*(short *)(g_006A3AB4 + iVar6) < sVar3) {
        *(short *)(g_006A3AB4 + iVar6) = sVar3;
      }
      iVar6 = *(int *)(g_006A3A44 + iVar6);
      func_001CCFA0(iVar6);
      bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar6) + 0x19c);
      *(u8 *)((u8 *)PS2_PTR(iVar6) + 0x19c) = bVar1 & 0xfb | 4;
      *(u8 *)((u8 *)PS2_PTR(iVar6) + 0x19c) = bVar1 & 0xf3 | 4;
      *(u16 *)((u8 *)PS2_PTR(iVar6) + 300) = 1;
      *(u16 *)((u8 *)PS2_PTR(iVar6) + 0x12e) = 1;
    }
  }
  return;
}

/* 0x001EC380, 0x3C bytes. */
void func_001EC380(u8 *param_1)
{
  if (*(float *)(param_1 + 0x38) == 0.0) {
    func_001EE9C0(param_1,0);
  }
  return;
}

/* 0x001ECC10, 0x288 bytes. */
float func_001ECC10(u8 *param_1, int param_2)
{
    float afStack_50[20];
    float afStack_a0[20];
    int cVar1;
    float fVar6;
    float fVar7;
    int iVar3;
    long long lVar2;
    float * pfVar4;
    float * pfVar5;

  
  if ((*(u32 *)(param_1 + 0x80) & 0x800) == 0) {
    fVar7 = 0.9;
    fVar6 = (*(float *)(g_00669F84 + 0x8));
  }
  else {
    if ((param_2 == 3) || (param_2 == 2)) {
      fVar7 = (*(float *)(g_00669F84 + 0x10));
    }
    else if ((param_2 == 1) || (param_2 == 0)) {
      fVar7 = (*(float *)(g_00669F84 + 0xC));
    }
    else {
      fVar7 = 0.9;
    }
    fVar6 = (float)(*(u32 *)(g_00669F84 + 0x0)) * 0.1 + (*(float *)(g_00669F84 + 0x8)) + 0.0;
  }
  if (((param_2 == 3) || (param_2 == 2)) || (param_2 == 1)) {
    fVar7 = fVar7 * fVar6;
  }
  else if (param_2 == 0) {
    fVar7 = fVar7 + fVar6;
  }
  lVar2 = func_0036D2E0();
  if (lVar2 != 0) {
    if ((param_2 != 2) && (param_2 != 1)) {
      cVar1 = *(char *)(param_1 + 0x79);
      goto LAB_001ecd88;
    }
    iVar3 = func_0036D6D0();
    fVar7 = fVar7 * (((float)(iVar3 + -1) / 23.0) / 3.0 + 1.0);
  }
  cVar1 = *(char *)(param_1 + 0x79);
LAB_001ecd88:
  if (((cVar1 == '\x01') &&
      (((*(u32 *)(param_1 + 0x80) & 0x400) != 0 || ((*(u32 *)(param_1 + 0x80) & 0x10000000) != 0))
      )) && (param_2 != 3)) {
    if (param_2 == 2) {
      pfVar4 = afStack_a0;
      pfVar5 = (float *)(g_0040CCE0 + 0x50);
      iVar3 = 10;
      do {
        iVar3 = iVar3 + -1;
        fVar6 = pfVar5[1];
        *pfVar4 = *pfVar5;
        pfVar4[1] = fVar6;
        pfVar5 = pfVar5 + 2;
        pfVar4 = pfVar4 + 2;
      } while (0 < iVar3);
      fVar7 = fVar7 * afStack_a0[(*(u32 *)(g_00669F84 + 0x4))];
    }
    else if (param_2 == 1) {
      pfVar4 = afStack_50;
      pfVar5 = (float *)(g_0040CCE0 + 0x0);
      iVar3 = 10;
      do {
        iVar3 = iVar3 + -1;
        fVar6 = pfVar5[1];
        *pfVar4 = *pfVar5;
        pfVar4[1] = fVar6;
        pfVar5 = pfVar5 + 2;
        pfVar4 = pfVar4 + 2;
      } while (0 < iVar3);
      fVar7 = fVar7 * afStack_50[(*(u32 *)(g_00669F84 + 0x4))];
    }
    else if (param_2 != 0) {
      return fVar7;
    }
  }
  return fVar7;
}
/* MISSING ['0x669f84', '0x669f8c', '0x669f90', '0x669f94'] */

/* 0x001ED240, 0xC4 bytes. */
int func_001ED240(u8 *param_1, int param_2)
{
    int iVar1;

  
  if (*(char *)(param_1 + 0x7a) == '\x02') {
    if (*(int *)(param_1 + 0x18) == param_2) {
      return 1;
    }
    if (((*(u32 *)(param_1 + 0x80) & 0x20000) != 0) && ((*(u32 *)((u8 *)PS2_PTR(param_2) + 0x80) & 0x30) != 0)) {
      for (iVar1 = *(int *)(param_1 + 0x14) * 0xc0 + 0x6a3a30; iVar1 != 0;
          iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 4)) {
        if (*(int *)((u8 *)PS2_PTR(iVar1) + 8) == *(int *)((u8 *)PS2_PTR(param_2) + 0x14) * 0xc0 + 0x6a3a30) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/* 0x001EF190, 0x518 bytes. */
void func_001EF190(u8 *param_1, int param_2, int param_3, int param_4)
{
    int iVar5;
    long long lVar2;
    long long lVar3;
    long long lVar8;
    int sVar1;
    int sVar4;
    int sVar6;
    int sVar7;

  
  if ((param_4 == 0) || ((*(u32 *)(param_1 + 0x80) & 0x20000) == 0)) {
    if ((*(u32 *)(param_1 + 0x80) & 0x20000) == 0) {
      sVar7 = *(short *)(param_1 + 0x4c);
      lVar8 = (long long)sVar7;
      sVar1 = *(short *)(param_1 + 0x4e);
      lVar3 = (long long)((int)sVar1 + (sVar7 * param_2) / 100);
      if (lVar8 < lVar3) {
        lVar2 = lVar8;
      }
      else {
        lVar2 = lVar3;
      }
      if (lVar2 < 2) {
        sVar4 = 1;
      }
      else {
        if (lVar8 < lVar3) {
          lVar3 = lVar8;
        }
        sVar4 = (short)lVar3;
      }
      sVar6 = sVar4;
      if (lVar8 < sVar4) {
        sVar6 = sVar7;
      }
      if (sVar6 < 1) {
        sVar6 = 0;
      }
      else {
        sVar6 = sVar4;
        if (lVar8 < sVar4) {
          sVar6 = sVar7;
        }
      }
      *(short *)(param_1 + 0x4e) = sVar6;
      if (param_3 == 0) {
        sVar6 = *(short *)(param_1 + 0x50);
        sVar7 = ((short)(sVar6 - sVar7) / 9) * (u16)*(u8 *)(param_1 + 0x74);
        lVar3 = (long long)sVar7;
        lVar8 = (long long)(((int)*(short *)(param_1 + 0x52) - (int)sVar1) + (sVar7 * param_2) / 100);
        if (lVar3 < lVar8) {
          lVar2 = lVar3;
        }
        else {
          lVar2 = lVar8;
        }
        if (lVar2 < 2) {
          sVar7 = 1;
        }
        else {
          if (lVar8 <= lVar3) {
            lVar3 = lVar8;
          }
          sVar7 = (short)lVar3;
        }
        sVar4 = sVar4 + sVar7;
        sVar7 = sVar4;
        if (sVar6 < sVar4) {
          sVar7 = sVar6;
        }
        if (sVar7 < 1) {
          sVar6 = 0;
        }
        else if (sVar4 <= sVar6) {
          sVar6 = sVar4;
        }
        *(short *)(param_1 + 0x52) = sVar6;
      }
      else {
        sVar7 = *(short *)(param_1 + 0x50);
        lVar8 = (long long)sVar7;
        lVar3 = (long long)((int)*(short *)(param_1 + 0x52) + ((int)sVar4 - (int)sVar1));
        if (lVar8 < lVar3) {
          lVar2 = lVar8;
        }
        else {
          lVar2 = lVar3;
        }
        if (lVar2 < 2) {
          sVar1 = 1;
        }
        else {
          if (lVar8 < lVar3) {
            lVar3 = lVar8;
          }
          sVar1 = (short)lVar3;
        }
        sVar4 = sVar1;
        if (lVar8 < sVar1) {
          sVar4 = sVar7;
        }
        if (sVar4 < 1) {
          sVar1 = 0;
        }
        else if (lVar8 < sVar1) {
          sVar1 = sVar7;
        }
        *(short *)(param_1 + 0x52) = sVar1;
      }
    }
    else {
      iVar5 = *(int *)(param_1 + 0x14) * 0xc0;
      sVar7 = *(short *)(g_006A3AB0 + iVar5);
      lVar8 = (long long)sVar7;
      lVar3 = (long long)((int)*(short *)(g_006A3AB2 + iVar5) + (sVar7 * param_2) / 100);
      if (lVar8 < lVar3) {
        lVar2 = lVar8;
      }
      else {
        lVar2 = lVar3;
      }
      if (lVar2 < 2) {
        sVar1 = 1;
      }
      else {
        if (lVar8 < lVar3) {
          lVar3 = lVar8;
        }
        sVar1 = (short)lVar3;
      }
      sVar4 = sVar1;
      if (lVar8 < sVar1) {
        sVar4 = sVar7;
      }
      if (sVar4 < 1) {
        sVar1 = 0;
      }
      else if (lVar8 < sVar1) {
        sVar1 = sVar7;
      }
      *(short *)(g_006A3AB2 + iVar5) = sVar1;
      if (*(short *)(g_006A3AB4 + iVar5) < sVar1) {
        *(short *)(g_006A3AB4 + iVar5) = sVar1;
      }
      if ((param_3 == 0) && (iVar5 = *(int *)(g_006A3A34 + iVar5), iVar5 != 0)) {
        do {
          sVar7 = *(short *)((u8 *)PS2_PTR(iVar5) + 0x80);
          lVar8 = (long long)sVar7;
          lVar3 = (long long)((int)*(short *)((u8 *)PS2_PTR(iVar5) + 0x82) + (sVar7 * param_2) / 100);
          if (lVar8 < lVar3) {
            lVar2 = lVar8;
          }
          else {
            lVar2 = lVar3;
          }
          sVar1 = 1;
          if (1 < lVar2) {
            if (lVar8 < lVar3) {
              lVar3 = lVar8;
            }
            sVar1 = (short)lVar3;
          }
          sVar4 = sVar1;
          if (lVar8 < sVar1) {
            sVar4 = sVar7;
          }
          if (sVar4 < 1) {
            sVar1 = 0;
          }
          else if (lVar8 < sVar1) {
            sVar1 = sVar7;
          }
          *(short *)((u8 *)PS2_PTR(iVar5) + 0x82) = sVar1;
          if (*(short *)((u8 *)PS2_PTR(iVar5) + 0x84) < sVar1) {
            *(short *)((u8 *)PS2_PTR(iVar5) + 0x84) = sVar1;
          }
          iVar5 = *(int *)((u8 *)PS2_PTR(iVar5) + 4);
        } while (iVar5 != 0);
      }
    }
  }
  return;
}

/* 0x001F78E0, 0xA0 bytes. */
void func_001F78E0(void)
{
    u8 * iVar1;
    u8 * iVar2;
    u8 * iVar3;
    int iVar4;
    int iVar5;

  
  iVar5 = 0;
  iVar3 = g_00732220;
  do {
    iVar2 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0));
    iVar4 = 0;
    *(unsigned long long *)(iVar2 + 0x1e1e0) = 0;
    *(unsigned long long *)(iVar2 + 0x1e1f0) = 0;
    *(unsigned long long *)(iVar2 + 0x1e200) = 0;
    *(unsigned long long *)(iVar2 + 0x1e210) = 0;
    iVar1 = iVar2;
    do {
      iVar4 = iVar4 + 1;
      *(unsigned long long *)(iVar2 + 0x1def0) = 0;
      *(unsigned long long *)(iVar2 + 0x1df00) = 0;
      iVar2 = iVar2 + 0x50;
      *(unsigned long long *)(iVar1 + 0x1d950) = 0;
      *(unsigned long long *)(iVar1 + 0x1d960) = 0;
      *(unsigned long long *)(iVar1 + 0x1d9a0) = 0;
      *(unsigned long long *)(iVar1 + 0x1d9b0) = 0;
      iVar1 = iVar1 + 0xa0;
    } while (iVar4 < 9);
    iVar5 = iVar5 + 1;
    iVar3 = iVar3 + 4;
  } while (iVar5 < 2);
  return;
}

/* 0x001FA620, 0xF0 bytes. */
void func_001FA620(void)
{
    u8 * iVar1;
    u8 * iVar3;
    int iVar4;
    unsigned long long uVar2;

  
  iVar4 = 0;
  iVar3 = g_00732220;
  (*(u32 *)(g_007325E4 + 0x0)) = 0;
  do {
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0));
    uVar2 = func_00106C90((*(unsigned long long *)(g_0068F100 + 0x0)),0x3f97);
    func_001057F0(iVar1 + 0x1ae60,uVar2,0);
    *(unsigned long long *)(iVar1 + 0x1ae80) = 0x3f80000060808080;
    *(unsigned long long *)(iVar1 + 0x1ae90) = 0;
    *(unsigned long long *)(iVar1 + 0x1aea0) = 0;
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0));
    uVar2 = func_00106C90((*(unsigned long long *)(g_0068F100 + 0x0)),0x3f97);
    func_001057F0(iVar1 + 0x1aeb0,uVar2,0);
    iVar4 = iVar4 + 1;
    *(unsigned long long *)(iVar1 + 0x1aed0) = 0x3f80000060808080;
    iVar3 = iVar3 + 4;
    *(unsigned long long *)(iVar1 + 0x1aee0) = 0;
    *(unsigned long long *)(iVar1 + 0x1aef0) = 0;
  } while (iVar4 < 2);
  return;
}

/* 0x001FAF00, 0x540 bytes. */
void func_001FAF00(int param_1)
{
    int bVar1;
    int bVar2;
    float fVar16;
    int iVar10;
    int iVar14;
    int iVar15;
    int iVar3;
    int iVar9;
    int * piVar13;
    u32 * puVar12;
    u32 uVar11;
    u32 uVar4;
    u32 uVar5;
    unsigned long long uVar6;
    u32 uVar7;
    unsigned long long uVar8;

  
  iVar9 = (int)param_1 * 0x14;
  piVar13 = (int *)(iVar9 + 0x732640);
  iVar10 = *(int *)(g_70000150 * 4 + 0x732500);
  if (*(char *)(g_0073264C + iVar9) == '\0') {
    *piVar13 = 0;
  }
  else {
    if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
      iVar14 = 200;
    }
    else {
      if (param_1 == 0) {
        iVar14 = 0;
      }
      else {
        iVar14 = 0xc0;
      }
      iVar14 = iVar14 + 100;
    }
    *piVar13 = *piVar13 + 1;
    iVar15 = *(int *)(g_00732644 + iVar9) - *(int *)(g_00732648 + iVar9);
    fVar16 = (float)*piVar13 / 12.0;
    fVar16 = (float)((u32)(1.0 < fVar16) * 0x3f800000 | (int)fVar16 * (u32)(1.0 >= fVar16));
    iVar3 = func_001020C0();
    uVar11 = iVar3 / 3 & 1;
    if ((iVar3 / 3 < 0) && (uVar11 != 0)) {
      uVar11 = uVar11 - 2;
    }
    iVar3 = iVar15 + 0xc;
    if (0x17 < iVar3) {
      iVar3 = 0x18;
    }
    if (iVar3 < 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = iVar15 + 0xc;
      if (0x17 < (int)uVar4) {
        uVar4 = 0x18;
      }
    }
    uVar7 = 0xc - iVar15;
    if ((int)uVar7 < 0x18) {
      uVar5 = uVar7;
    }
    else {
      uVar5 = 0x18;
    }
    if ((int)uVar5 < 0) {
      uVar7 = 0;
    }
    else if (0x17 < (int)uVar7) {
      uVar7 = 0x18;
    }
    bVar1 = *(u8 *)(g_0073264D + iVar9);
    bVar2 = *(u8 *)(g_0073264E + iVar9);
    *(char *)(g_0073264D + iVar9) = (char)uVar4;
    *(char *)(g_0073264E + iVar9) = (char)uVar7;
    iVar10 = iVar10 + (int)param_1 * 400;
    iVar15 = (int)(fVar16 * (float)((u32)*(u8 *)(g_0073264D + iVar9) << 3));
    iVar3 = (int)(((u32)(iVar14 * 0x280) / 0x1e0) * 0x1c0) >> 9;
    uVar8 = (long long)(iVar3 * 8 + 0x7900) << 0x10;
    uVar6 = (long long)((iVar3 + 0x12) * 8 + 0x7900) << 0x10;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d630) = uVar8 | 0xfffe000078e0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d640) = uVar6 | 0xfffe000079c0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d680) = uVar8 | 0xfffe000079c0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d690) = uVar6 | 0xfffe00008640;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d6d0) = uVar8 | 0xfffe00008640;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d6e0) = uVar6 | 0xfffe00008720;
    if ((1.0 <= fVar16 && (uVar7 & 0xff) <= (u32)bVar2) || (uVar11 != 1)) {
      puVar12 = (u32 *)((g_00425CD0 + 0x0) + (u32)*(u8 *)(g_00732650 + iVar9) * 4);
    }
    else {
      puVar12 = (u32 *)(g_00425CD0 + 0x20);
    }
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d710) = (unsigned long long)*puVar12 | 0x3f80000000000000;
    iVar14 = (int)(((u32)((iVar14 + 3) * 0x280) / 0x1e0) * 0x1c0) >> 9;
    uVar8 = (long long)(iVar14 * 8 + 0x7900) << 0x10;
    uVar6 = (long long)((iVar14 + 8) * 8 + 0x7900) << 0x10;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d720) = uVar8 | 0xfffe000079c0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d730) =
         (long long)(((int)((float)(200 - iVar15) * fVar16) + 0x9c) * 0x10 + 0x7000) | uVar6 |
         0xfffe00000000;
    if ((1.0 <= fVar16 && (uVar4 & 0xff) <= (u32)bVar1) || (uVar11 != 1)) {
      puVar12 = (u32 *)((g_00425CD0 + 0x0) + (u32)*(u8 *)(g_0073264F + iVar9) * 4);
    }
    else {
      puVar12 = (u32 *)(g_00425CD0 + 0x20);
    }
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d760) = (unsigned long long)*puVar12 | 0x3f80000000000000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d770) = (long long)((0x164 - iVar15) * 0x10 + 0x7000) | uVar8 | 0xfffe00000000
    ;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar10) + 0x1d780) = uVar6 | 0xfffe00008640;
  }
  return;
}

/* 0x001FB6C0, 0x218 bytes. */
void func_001FB6C0(void)
{
    int bVar1;
    int iVar2;

  
  bVar1 = ((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0;
  func_002492C0();
  func_0024BAB0();
  func_0024A9B0();
  if ((*(u32 *)((*(short *)(g_00574F58 + 0x0)) * 0xc0 + 0x6a3ae8) & 1) != 0) {
    if (bVar1) {
      func_00261470(*(int *)(g_70000150 * 4 + 0x732500) + 0x195e0);
    }
    else {
      func_0025EE30(*(int *)(g_70000150 * 4 + 0x732500) + 0x195e0);
    }
  }
  if ((bVar1) && ((*(u32 *)((*(short *)(g_00575588 + 0x0)) * 0xc0 + 0x6a3ae8) & 1) != 0)) {
    func_00261470(*(int *)(g_70000150 * 4 + 0x732500) + 0x1a220);
  }
  if ((!bVar1) && (((*(u32 *)(g_00669F60 + 0x0)) & 0xc) == 0)) {
    func_00262AD0();
  }
  func_001FA790();
  if (bVar1) {
    iVar2 = 0;
    do {
      func_001FAF00(iVar2);
      func_002688F0(iVar2);
      func_0026CCD0(iVar2);
      func_002705B0(iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
  }
  else {
    func_001FAF00(0);
    func_00267D10(0);
    func_00269DF0(0);
    func_0026FF00(0);
  }
  func_001F7980();
  func_003DF490();
  return;
}

/* 0x00200290, 0xC4 bytes. */
void func_00200290(u32 *param_1, int param_2)
{
    int bVar1;
    float fVar3;
    u8 * iVar2;

  
  if (param_2 == 0) {
    iVar2 = func_002185B0(7,0);
    fVar3 = *(float *)(g_7000088C * 4 + 0x45d468);
    bVar1 = *(u8 *)(iVar2 + 3);
    *param_1 = 0x437f0000;
    param_1[1] = 0;
    param_1[2] = 0x3f800000;
    param_1[3] = (1.0 - fVar3) * (255.0 - (float)bVar1);
  }
  else {
    *param_1 = 0x437f0000;
    param_1[1] = 0;
    param_1[2] = 0x3f800000;
    param_1[3] = 0x437f0000;
  }
  return;
}

/* 0x0020EAA0, 0x64 bytes. */
void func_0020EAA0(int param_1, int param_2)
{
    int iVar1;

  
  if (param_2 != 0) {
    if (g_0045D434 <= g_0045D430) {
      g_0045D434 = g_0045D430;
    }
    g_0045D430 = 0;
  }
  iVar1 = func_00102680(1,param_1 + 0xc08);
  g_0045D430 = g_0045D430 + (iVar1 + 0x7ffU & 0xfffff800);
  return;
}

/* 0x00215790, 0xB4 bytes. */
void func_00215790(void)
{
    int bVar1;
    int iVar2;
    int iVar3;

  
  bVar1 = g_0045D48C != *(int *)(g_0045D460 + 0xa0);
  g_0045D488 = (u32)bVar1;
  iVar3 = 0;
  iVar2 = g_0045D460 + (u32)bVar1 * 0x70;
  do {
    if (*(int *)(iVar3 * 4 + 0x740430) != 0) {
      func_00215850(iVar3,iVar2 + 0xa0,0,0);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x1e);
  return;
}

/* 0x0022B890, 0xB4 bytes. */
int func_0022B890(u8 *param_1, u32 *param_2)
{
    int bVar1;
    int iVar3;
    u32 uVar2;
    u32 uVar4;
    u32 uVar5;

  
  uVar5 = *param_2 + 1;
  if (uVar5 < 0x280) {
    uVar4 = uVar5 >> 3;
    iVar3 = 8 - (uVar5 & 7);
    bVar1 = *(u8 *)(param_1 + uVar4) >> (uVar5 & 7);
    while( true ) {
      uVar2 = (u32)bVar1;
      if (uVar2 == 0) {
        uVar5 = uVar5 + iVar3;
      }
      else {
        while (iVar3 != 0) {
          if ((uVar2 & 1) != 0) {
            *param_2 = uVar5;
            return 1;
          }
          uVar2 = uVar2 >> 1;
          uVar5 = uVar5 + 1;
        }
      }
      uVar4 = uVar4 + 1;
      if (0x4f < uVar4) break;
      bVar1 = *(u8 *)(param_1 + uVar4);
      iVar3 = 8;
    }
  }
  return 0;
}

/* 0x0022EF90, 0x190 bytes. */
void func_0022EF90(u8 *param_1, int param_2, int param_3)
{
    long long lVar1;
    u32 uVar2;

  
  if (param_3 == 3) {
    lVar1 = 0;
  }
  else if (param_3 == 2) {
    lVar1 = func_0023A5C0(param_2);
    (*(u32 *)(g_005BC028 + 0x0)) = (int)param_2;
  }
  else if (param_3 == 0) {
    uVar2 = 2;
    if (param_2 != 3) {
      if (param_2 == 2) {
        uVar2 = 1;
      }
      else {
        uVar2 = 3;
        if (param_2 == 1) {
          uVar2 = 0;
        }
      }
    }
    lVar1 = func_0023A5C0(uVar2);
    (*(u32 *)(g_005BC028 + 0x0)) = uVar2;
  }
  else if (param_3 == 1) {
    if (param_2 < 0) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_0023A4F0(param_2);
      (*(u32 *)(g_005BC028 + 0x0)) = (int)param_2;
      func_0017E110((int)((u32)(*(u8 *)(g_00669DB2 + 0x0)) * 3) >> 2);
      func_0023B530(((u32)(*(u8 *)(g_00669DB2 + 0x1)) << 2) / 5);
    }
  }
  else {
    lVar1 = 0;
  }
  if (lVar1 == 0) {
    func_0022F730(0);
    *param_1 = *param_1 | 8;
  }
  else {
    *param_1 = *param_1 | 0x20;
  }
  return;
}

/* 0x0022F510, 0x218 bytes. */
void func_0022F510(void)
{
    int bVar2;
    int cVar1;
    long long lVar3;

  
  if (((*(u8 *)(g_005BC3A0 + 0x0)) & 0x20) == 0) {
    if (((*(u8 *)(g_005BC3A0 + 0x0)) & 8) != 0) {
      if ((*(u32 *)(g_005BC03C + 0x24)) == 2) {
        if ((*(u32 *)(g_00693703 + 0x0)) == '\x03') {
          func_001AFE20();
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
        else if ((*(u32 *)(g_00693703 + 0x0)) == '\0') {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
      }
      else if ((*(u32 *)(g_005BC03C + 0x0)) == 0) {
        if (*(char *)((*(u32 *)(g_005BC03C + 0x24)) * 0x128 + 0x6934b3) == '\0') {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
          (*(u16 *)(g_00693388 + 0x2)) = (*(u16 *)(g_00693388 + 0x2)) | 0x8000;
          (*(u16 *)(g_00693388 + 0x0)) = (*(u16 *)(g_00693388 + 0x0)) | 0x8000;
          func_0017E110((*(u8 *)(g_00669DB2 + 0x0)));
          func_0023B530((*(u8 *)(g_00669DB2 + 0x1)));
        }
      }
      else {
        cVar1 = *(char *)((*(u32 *)(g_005BC03C + 0x24)) * 0x128 + 0x6934b3);
        if ((((cVar1 == '\0') || (bVar2 = true, cVar1 == '\x01')) || (cVar1 == '\b')) ||
           (cVar1 == '\x03')) {
          bVar2 = false;
        }
        if (!bVar2) {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
      }
    }
  }
  else {
    lVar3 = func_00102960(0);
    if (lVar3 != 0) {
      (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xdf;
      func_0022F730(1);
      (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) | 8;
    }
  }
  if ((((*(u8 *)(g_005BC3A0 + 0x4)) & 8) != 0) && ((*(char *)(g_0069382B + 0x0)) == '\x03')) {
    func_001AFE20();
    (*(u8 *)(g_005BC3A0 + 0x4)) = (*(u8 *)(g_005BC3A0 + 0x4)) & 0xf7;
  }
  return;
}
/* MISSING ['0x5bc03c', '0x693703'] */

/* 0x00236ED0, 0x5C bytes. */
void func_00236ED0(u8 *param_1)
{
    u8 * iVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

  
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 0;
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) | 1;
  iVar1 = (u8 *)PS2_PTR(*(int *)(param_1 + 0x14));
  *(u32 *)(iVar1 + 0x13c) = 0;
  uVar4 = g_700000CC;
  uVar3 = g_700000C8;
  uVar2 = g_700000C4;
  *(u32 *)(iVar1 + 0x1d0) = g_700000C0;
  *(u32 *)(iVar1 + 0x1d4) = uVar2;
  *(u32 *)(iVar1 + 0x1d8) = uVar3;
  *(u32 *)(iVar1 + 0x1dc) = uVar4;
  func_00204CD0(param_1,0x40000);
  return;
}

/* 0x00236F30, 0x84 bytes. */
int func_00236F30(u8 *param_1)
{
    u8 * iVar1;
    u8 * iVar6;
    long long lVar5;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

  
  iVar6 = param_1;
  iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x14));
  lVar5 = func_001F45E0(iVar1 + 0x40,*(int *)(*(int *)(iVar6 + 8) + 0x14) + 0x40);
  if (lVar5 == 0) {
    *(u32 *)(iVar1 + 0x13c) = 0;
    uVar4 = g_700000CC;
    uVar3 = g_700000C8;
    uVar2 = g_700000C4;
    *(u32 *)(iVar1 + 0x1d0) = g_700000C0;
    *(u32 *)(iVar1 + 0x1d4) = uVar2;
    *(u32 *)(iVar1 + 0x1d8) = uVar3;
    *(u32 *)(iVar1 + 0x1dc) = uVar4;
    *(u32 *)(iVar6 + 0xbc) = *(u32 *)(iVar6 + 0xbc) & 0xfffffffe;
    func_00207930(param_1);
  }
  return lVar5 != 0;
}

/* 0x00237D00, 0xDC bytes. */
int func_00237D00(u8 *param_1)
{
    float fStack_10;
    float fStack_c;
    u8 * iVar3;
    long long lVar2;
    int uStack_3;
    int uStack_4;
    u32 uVar1;

  
  iVar3 = param_1;
  fStack_10 = (float)*(unsigned long long *)(iVar3 + 0x30);
  fStack_c = (float)((unsigned long long)*(unsigned long long *)(iVar3 + 0x30) >> 0x20);
  uStack_4 = (u8)((int)fStack_10 / 5000);
  uStack_3 = (u8)((int)fStack_c / 5000);
  lVar2 = func_00190590(&uStack_4,8);
  if (lVar2 == 0) {
    uVar1 = 1;
  }
  else {
    func_00206080(param_1);
    if ((*(u32 *)(iVar3 + 0xb8) & 0x800) == 0) {
      func_00204D00(param_1,0x20);
      *(u32 *)(*(int *)(iVar3 + 0x10) + 0x80) =
           *(u32 *)(*(int *)(iVar3 + 0x10) + 0x80) & 0xfff7ffff;
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x00238930, 0x1AC bytes. */
int func_00238930(u8 *param_1, float *param_2)
{
    float fVar7;
    int iVar5;
    int iVar6;
    long long lVar4;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

  
  lVar4 = func_00238710();
  if (lVar4 == 0) {
    uVar3 = 0;
  }
  else {
    if (((*(u32 *)(g_00669F60 + 0x0)) & 8) == 0) {
      uVar1 = *(u32 *)(*(int *)(param_1 + 0x10) + 0x10);
      uVar2 = *(u32 *)(*(int *)(*(int *)(param_1 + 8) + 0x10) + 0x10);
      if (uVar1 < 0x47) {
        iVar5 = uVar1 * 0x68;
        if (((*(u32 *)(g_00669F60 + 0x0)) & 0xc) == 0) {
          iVar5 = *(int *)(g_006A1DA4 + iVar5);
        }
        else if (*(char *)(*(int *)(g_006A1D58 + iVar5) + 0x79) == '\0') {
          iVar5 = 0x15e;
        }
        else {
          iVar5 = 0x28a;
        }
      }
      else {
        iVar5 = 1;
      }
      if (uVar2 < 0x47) {
        iVar6 = uVar2 * 0x68;
        if (((*(u32 *)(g_00669F60 + 0x0)) & 0xc) == 0) {
          iVar6 = *(int *)(g_006A1DA4 + iVar6);
        }
        else if (*(char *)(*(int *)(g_006A1D58 + iVar6) + 0x79) == '\0') {
          iVar6 = 0x15e;
        }
        else {
          iVar6 = 0x28a;
        }
      }
      else {
        iVar6 = 1;
      }
      fVar7 = ((float)iVar5 * 0.5) / ((float)iVar5 + (float)iVar6) + 0.75;
      if ((*(u32 *)(*(int *)(param_1 + 8) + 0xb8) & 0xc) == 0) {
        fVar7 = fVar7 * 2.0;
      }
      *param_2 = fVar7;
    }
    else {
      *param_2 = 1.0;
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* 0x00238F50, 0x1F0 bytes. */
int func_00238F50(u8 *param_1)
{
    int bVar3;
    u8 * iVar1;
    u8 * iVar7;
    u8 * iVar9;
    int sVar4;
    int sVar5;
    u32 uVar2;
    int uVar6;
    u32 uVar8;

  
  if (((*(u32 *)(g_00669F60 + 0x0)) & 0x10) == 0) {
    iVar9 = param_1;
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar9 + 0x14));
    uVar2 = *(u32 *)(*(int *)(iVar1 + 0x210) + 0x18);
    bVar3 = false;
    if (((uVar2 & 8) != 0) && ((uVar2 & 0x20) == 0)) {
      bVar3 = true;
    }
    if (bVar3) {
      iVar7 = func_001F14E0(param_1);
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < (u32)*(u8 *)(iVar7 + 2)) {
        if (*(short *)(iVar9 + 0x88) < *(short *)(iVar9 + 0x86)) {
          uVar8 = 0;
        }
        else {
          *(u32 *)(iVar9 + 0xbc) = *(u32 *)(iVar9 + 0xbc) & 0xfff8003f;
          *(u8 *)(iVar9 + 0x7d) = 2;
          sVar5 = *(short *)(iVar9 + 0x86);
          sVar4 = sVar5;
          if (-1 < sVar5) {
            sVar4 = 0;
          }
          if (sVar4 < 1) {
            sVar5 = 0;
          }
          else if (-1 < sVar5) {
            sVar5 = 0;
          }
          *(short *)(iVar9 + 0x88) = sVar5;
          func_00204CD0(param_1,0x20000);
          iVar7 = func_001F14E0(param_1);
          if (*(u8 *)(iVar7 + 0xe) == 0) {
            *(u16 *)(iVar9 + 0x78) = 0;
          }
          else {
            uVar2 = ((u32)*(u8 *)(iVar7 + 0xe) * 0x32) / 0x3c;
            uVar6 = (u16)uVar2;
            if (uVar2 == 0) {
              uVar6 = 1;
            }
            *(u16 *)(iVar9 + 0x78) = uVar6;
          }
          *(u32 *)(iVar9 + 0xbc) = *(u32 *)(iVar9 + 0xbc) | 0x40;
          g_70000D60 = 0;
          func_00253300(0xb,iVar1);
          uVar8 = 1;
        }
      }
      else {
        uVar8 = 0;
      }
    }
    else {
      uVar8 = 0;
    }
  }
  else {
    uVar8 = 0;
  }
  return uVar8;
}

/* 0x00243C50, 0x19C bytes. */
int func_00243C50(u8 *param_1)
{
    u8 * iVar4;
    int sVar1;
    int sVar3;
    u32 uVar2;

  
  iVar4 = param_1;
  sVar3 = **(short **)(iVar4 + 0x210);
  if ((1 < *(u8 *)(iVar4 + 0x14e)) && (-1 < (long long)*(char *)(iVar4 + 0x19e) << 0x3d)) {
    if ((*(u32 *)(iVar4 + 0x13c) & 0x8000) != 0) {
      sVar3 = func_002431F0(param_1,sVar3,0xffffffffffffffff);
    }
    if ((*(u32 *)(iVar4 + 0x13c) & 1) != 0) {
      sVar3 = func_002431F0(param_1,sVar3,1);
    }
    if ((*(u32 *)(iVar4 + 0x13c) & 0x10000) != 0) {
      sVar3 = func_002431F0(param_1,sVar3,0xfffffffffffffffe);
    }
    if ((*(u32 *)(iVar4 + 0x13c) & 2) != 0) {
      sVar3 = func_002431F0(param_1,sVar3,2);
    }
  }
  sVar1 = **(short **)(iVar4 + 0x210);
  if ((sVar3 == sVar1) &&
     ((((sVar1 == 4 || (sVar1 == 3)) || (sVar1 == 2)) || ((sVar1 == 1 || (sVar1 == 0)))))) {
    uVar2 = *(u32 *)(iVar4 + 0x13c);
    if ((uVar2 & 0x10000000) == 0) {
      if ((uVar2 & 0x20000000) == 0) {
        if ((uVar2 & 0x4000000) == 0) {
          if ((uVar2 & 0x8000000) == 0) {
            sVar3 = 0;
          }
          else {
            sVar3 = 2;
          }
        }
        else {
          sVar3 = 1;
        }
      }
      else {
        sVar3 = 3;
      }
    }
    else {
      sVar3 = 4;
    }
  }
  return sVar3;
}

/* 0x00243DF0, 0x120 bytes. */
void func_00243DF0(u8 *param_1, u8 *param_2)
{
    int bVar1;

  
  *(u8 *)(param_1 + 0x183) = *(u8 *)(param_2 + 0x18);
  if ((*(u32 *)(param_2 + 0x2c) & 1) == 0) {
    bVar1 = *(u8 *)(param_1 + 0x19d);
    *(u8 *)(param_1 + 0x19d) = bVar1 & 0xbf;
    *(u8 *)(param_1 + 0x19d) = bVar1 & 0x3f | 0x80;
  }
  else {
    bVar1 = *(u8 *)(param_1 + 0x19d);
    *(u8 *)(param_1 + 0x19d) = bVar1 & 0xbf | 0x40;
    *(u8 *)(param_1 + 0x19d) = bVar1 & 0x3f | 0x40;
  }
  if ((*(u16 *)(param_2 + 0x1c) & 2) == 0) {
    if ((*(u32 *)(param_2 + 0x2c) & 0x20) == 0) {
      if ((*(u32 *)(param_2 + 0x2c) & 0x10) == 0) {
        *(u16 *)(param_1 + 0x15e) = 0xc3;
      }
      else {
        *(u16 *)(param_1 + 0x15e) = 0x104;
      }
    }
    else {
      *(u16 *)(param_1 + 0x15e) = 0x145;
    }
  }
  else if ((*(u32 *)(param_2 + 0x2c) & 0x20) == 0) {
    if ((*(u32 *)(param_2 + 0x2c) & 0x10) == 0) {
      *(u16 *)(param_1 + 0x15e) = 0x9c;
    }
    else {
      *(u16 *)(param_1 + 0x15e) = 0xea;
    }
  }
  else {
    *(u16 *)(param_1 + 0x15e) = 0x138;
  }
  return;
}

/* 0x00245D60, 0x44 bytes. */
void func_00245D60(void)
{
  (*(u32 *)(g_0075294C + 0x0)) = (*(u32 *)(g_0075294C + 0x0)) ^ 1;
  func_001185B0((*(u32 *)(g_0075294C + 0x0)) * 0x100 + 0x752950,0x10);
  return;
}

/* 0x00245F20, 0x68 bytes. */
int func_00245F20(int param_1, u8 *param_2)
{
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

  
  uVar1 = 1;
  uVar2 = (u32)(*(u16 *)(param_2 + 0x58) >> 3);
  uVar3 = 1 << (*(u16 *)(param_2 + 0x58) & 7) & 0xff;
  if (((*(u8 *)((u8 *)PS2_PTR(uVar2) + param_1 * 0x40 + 0x752950) & uVar3) == 0) &&
     ((*(u8 *)((u8 *)PS2_PTR(uVar2) + param_1 * 0x40 + 0x752a50) & uVar3) == 0)) {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x00247FA0, 0x178 bytes. */
void func_00247FA0(int param_1, int param_2, int param_3)
{
    u8 * iVar2;
    int iVar3;
    u8 * iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    u32 uVar1;

  
  iVar2 = g_00732508;
  iVar3 = 10;
  if (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) {
    iVar3 = 5;
  }
  if ((*(char *)(g_0073255B + 0x0)) != '\x01') {
    iVar7 = 0;
    if (iVar3 != 0) {
      do {
        if (*(char *)(g_00732550 + iVar7) == -1) break;
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar3);
    }
    if (iVar3 <= iVar7) {
      iVar5 = 0;
      iVar7 = 0;
      iVar6 = 0;
      if (iVar3 != 0) {
        iVar4 = iVar2;
        do {
          if (iVar5 < *(int *)(iVar4 + 0xc)) {
            iVar7 = iVar6;
            iVar5 = *(int *)(iVar4 + 0xc);
          }
          iVar6 = iVar6 + 1;
          iVar4 = iVar4 + 4;
        } while (iVar6 < iVar3);
      }
    }
    if (iVar7 < iVar3) {
      iVar3 = iVar7 * 4;
      *(u8 *)(g_00732550 + iVar7) = param_1;
      *(char *)(g_0073253C + iVar7) = (char)param_2;
      uVar1 = (*(u32 *)(g_00669F60 + 0x0));
      *(u32 *)(g_00732514 + iVar3) = 0;
      *(u8 *)(g_00732546 + iVar7) = param_3;
      if ((uVar1 & 2) != 0) {
        *(u32 *)(g_00732528 + iVar3) = *(u32 *)(g_00732514 + iVar3);
        *(u8 *)(g_00732541 + iVar7) = *(u8 *)(g_0073253C + iVar7);
        *(u8 *)(g_0073254B + iVar7) = *(u8 *)(g_00732546 + iVar7);
        *(u8 *)(g_00732555 + iVar7) = *(u8 *)(g_00732550 + iVar7);
      }
      if (param_2 == 0x1c) {
        iVar3 = 0;
        (*(char *)(g_0073255B + 0x0)) = '\x01';
        do {
          if ((*(char *)(g_0073253C + iVar3) != '\x1c') && (*(int *)(iVar2 + 0xc) == 0)) {
            *(u8 *)(g_00732550 + iVar3) = 0xff;
            *(u8 *)(g_0073253C + iVar3) = 0x1d;
            *(u8 *)(g_00732546 + iVar3) = 6;
          }
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 4;
        } while (iVar3 < 10);
      }
    }
  }
  return;
}

/* 0x0024BF60, 0x108 bytes. */
void func_0024BF60(void)
{
    u8 * iVar1;
    int iVar2;

  
  iVar1 = g_00753190;
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 8;
    *(u8 *)(iVar1 + 0x19f) = *(u8 *)(iVar1 + 0x19f) & 0xfe;
    *(u32 *)(iVar1 + 0x198) = 0;
    *(u8 *)(iVar1 + 0x19d) = 0x17;
    *(u8 *)(iVar1 + 0x33f) = *(u8 *)(iVar1 + 0x33f) & 0xfe;
    *(u32 *)(iVar1 + 0x338) = 0;
    *(u8 *)(iVar1 + 0x33d) = 0x17;
    *(u8 *)(iVar1 + 0x4df) = *(u8 *)(iVar1 + 0x4df) & 0xfe;
    *(u32 *)(iVar1 + 0x4d8) = 0;
    *(u8 *)(iVar1 + 0x4dd) = 0x17;
    *(u8 *)(iVar1 + 0x67f) = *(u8 *)(iVar1 + 0x67f) & 0xfe;
    *(u32 *)(iVar1 + 0x678) = 0;
    *(u8 *)(iVar1 + 0x67d) = 0x17;
    *(u8 *)(iVar1 + 0x81f) = *(u8 *)(iVar1 + 0x81f) & 0xfe;
    *(u32 *)(iVar1 + 0x818) = 0;
    *(u8 *)(iVar1 + 0x81d) = 0x17;
    *(u8 *)(iVar1 + 0x9bf) = *(u8 *)(iVar1 + 0x9bf) & 0xfe;
    *(u32 *)(iVar1 + 0x9b8) = 0;
    *(u8 *)(iVar1 + 0x9bd) = 0x17;
    *(u8 *)(iVar1 + 0xb5f) = *(u8 *)(iVar1 + 0xb5f) & 0xfe;
    *(u32 *)(iVar1 + 0xb58) = 0;
    *(u8 *)(iVar1 + 0xb5d) = 0x17;
    *(u8 *)(iVar1 + 0xcff) = *(u8 *)(iVar1 + 0xcff) & 0xfe;
    *(u32 *)(iVar1 + 0xcf8) = 0;
    *(u8 *)(iVar1 + 0xcfd) = 0x17;
    iVar1 = iVar1 + 0xd00;
  } while (iVar2 < 0x10);
  func_0024E440();
  g_0045D500 = 0;
  return;
}

/* 0x0025C160, 0x258 bytes. */
void func_0025C160(u8 *param_1, int param_2)
{
    float fVar2;
    int iVar1;

  
  iVar1 = func_001020C0();
  fVar2 = (float)(u32)(iVar1 % 0x19) / 25.0;
  if (((*(u32 *)(g_00669F60 + 0x0)) & 0x1000000) == 0) {
    if (param_2 < 3) {
      if ((int)param_2 - 1U < 2) {
        *(unsigned long long *)(param_1 + 0x20) =
             (long long)(int)(fVar2 * 32.0 + 62.0) << 0x10 |
             (long long)(int)(fVar2 * 36.0 + 92.0) | (long long)(int)(fVar2 * 47.0 + 38.0) << 8 |
             0x3f80000080000000;
      }
      else {
        *(unsigned long long *)(param_1 + 0x20) = 0x3f800000803e265c;
      }
    }
    else {
      *(unsigned long long *)(param_1 + 0x20) =
           (long long)(int)(fVar2 * 18.0 + 62.0) << 0x10 |
           (long long)(int)(fVar2 * 26.0 + 92.0) | (long long)(int)(fVar2 * 73.0 + 38.0) << 8 |
           0x3f80000080000000;
    }
  }
  else {
    *(unsigned long long *)(param_1 + 0x20) = 0x3f800000803e265c;
  }
  return;
}

/* 0x00269740, 0x78 bytes. */
void func_00269740(int param_1)
{
    int iVar1;
    int iVar2;

  
  iVar2 = param_1 * 0x2c;
  if (((*(u32 *)(g_00669F60 + 0x0)) & 8) == 0) {
    *(u8 *)(g_0073260E + iVar2) = 2;
    iVar1 = *(int *)(param_1 * 0x48 + 0x669dec) - *(int *)(g_00732608 + iVar2);
    *(int *)(g_007325FC + iVar2) = iVar1;
    *(int *)(g_00732604 + iVar2) = iVar1;
    *(u8 *)(g_0073260D + iVar2) = 0x19;
  }
  return;
}

/* 0x00269AF0, 0x300 bytes. */
void func_00269AF0(int param_1)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    int iVar7;
    int iVar8;
    unsigned long long uVar2;

  
  iVar3 = (int)param_1 * 0x2c;
  iVar1 = 0;
  iVar6 = g_00732220;
  if ((((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) && (param_1 != 0)) {
    iVar1 = 0xc0;
  }
  *(u32 *)(g_007325EC + iVar3) = 0;
  *(u32 *)(g_007325F4 + iVar3) = 1;
  *(u32 *)(g_007325F0 + iVar3) = 1;
  *(u8 *)(g_00732612 + iVar3) = 5;
  iVar5 = 0;
  iVar7 = (int)param_1 * 0x1380;
  iVar3 = (int)(((u32)((iVar1 + 0x9d) * 0x280) / 0x1e0) * 0x1c0) >> 9;
  do {
    iVar1 = *(int *)(iVar6 + 0x2e0) + iVar7;
    uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3efe);
    func_001057F0(iVar1 + 0x1bb20,uVar2,0);
    iVar4 = 0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb40) = 0x3f80000080808080;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb48) = 0xb880008;
    iVar8 = 0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb58) = 0xe080308;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb50) = (long long)(iVar3 * 8 + 0x7900) << 0x10 | 0xfffe00008980;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb60) = (long long)((iVar3 + 0x13) * 8 + 0x7900) << 0x10 | 0xfffe00008ac0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb50) = 0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bb60) = 0;
    do {
      iVar1 = *(int *)(iVar6 + 0x2e0) + iVar7 + iVar8;
      uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef1);
      func_00105A30(iVar1 + 0x1bb70,uVar2,0);
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bba0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bbb0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bbc0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bbd0) = 0;
      iVar1 = *(int *)(iVar6 + 0x2e0) + iVar7 + iVar8;
      uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef1);
      func_00105A30(iVar1 + 0x1bdc0,uVar2,0);
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bdf0) = 0;
      iVar4 = iVar4 + 1;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1be00) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1be10) = 0;
      iVar8 = iVar8 + 0x70;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1be20) = 0;
    } while (iVar4 < 5);
    iVar1 = *(int *)(iVar6 + 0x2e0) + iVar7;
    func_001050B0(iVar1 + 0x1bff0);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1c000) = 0x8000000044;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1c008) = 0x43;
    iVar1 = *(int *)(iVar6 + 0x2e0) + iVar7;
    func_001050B0(iVar1 + 0x1bda0);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bdb0) = 0x48;
    iVar5 = iVar5 + 1;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar1) + 0x1bdb8) = 0x43;
    iVar6 = iVar6 + 4;
  } while (iVar5 < 2);
  return;
}

/* 0x00273770, 0x1D0 bytes. */
int func_00273770(u8 *param_1, int param_2, float *param_3)
{
    int bVar3;
    int iVar4;
    int iVar7;
    long long lVar6;
    long long lVar8;
    int sVar1;
    int sVar2;
    u32 uVar5;

  
  if (*(u8 *)(param_1 + 0x14e) < 2) {
    if (*(u8 *)(*(short *)(param_1 + 0x178) * 0xc0 + 0x6a3ae2) < 0x35) {
      lVar6 = func_002F6A60(*(u32 *)((u32)*(u8 *)(param_1 + 0x14e) * 0x48 + 0x669de8));
      if (lVar6 == 0x32) {
        iVar7 = *(short *)(param_1 + 0x178) * 0xc0;
        sVar1 = *(short *)(g_006A3AB0 + iVar7);
        iVar4 = (int)sVar1;
        if (sVar1 < 0) {
          iVar4 = iVar4 + 3;
        }
        lVar6 = (long long)(iVar4 >> 2);
        if (lVar6 < 0x32) {
          sVar2 = *(short *)(g_006A3AB2 + iVar7);
        }
        else {
          lVar6 = 0x32;
          sVar2 = *(short *)(g_006A3AB2 + iVar7);
        }
        lVar8 = (long long)sVar2;
        if (lVar8 < lVar6) {
          *param_3 = (float)param_2 / 1.6;
        }
        else {
          iVar4 = (int)sVar1;
          if (sVar1 < 0) {
            iVar4 = iVar4 + 1;
          }
          if ((long long)(iVar4 >> 1) < 100) {
            bVar3 = lVar8 < iVar4 >> 1;
          }
          else {
            bVar3 = lVar8 < 100;
          }
          if (bVar3) {
            *param_3 = (float)param_2 / 3.2;
          }
          else {
            *param_3 = (float)param_2 / 4.8;
          }
        }
        uVar5 = 1;
      }
      else {
        uVar5 = 0;
      }
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

/* 0x00278500, 0x1AC bytes. */
void func_00278500(void)
{
  if (((*(char *)(g_0076F3D4 + 0x1)) != '\0') && ((*(char *)(g_0076F3D4 + 0x1)) = (*(char *)(g_0076F3D4 + 0x1)) + -1, (*(char *)(g_0076F3D4 + 0x1)) == '\0')) {
    if ((*(u8 *)(g_0076F3D4 + 0x0)) == 1) {
      func_00278150(2);
    }
    else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 2) {
      func_00278150(3);
    }
    else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 3) {
      func_00278150(5);
    }
    else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 5) {
      (*(u8 *)(g_0076F3D4 + 0x2)) = 3;
      (*(char *)(g_0076F3D4 + 0x1)) = '\0';
      (*(u8 *)(g_0076F3D4 + 0x0)) = (*(char *)(g_0076F3D4 + 0x3)) + 6;
      func_00278150(6);
    }
    else if (((*(u8 *)(g_0076F3D4 + 0x0)) < 6) || (10 < (*(u8 *)(g_0076F3D4 + 0x0)))) {
      if ((*(u8 *)(g_0076F3D4 + 0x0)) == 0xb) {
        func_00278150(0xc);
      }
      else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 0xc) {
        if ((*(u32 *)(g_0076F3D4 + 0x8)) == 0) {
          func_00278150(0xd);
        }
        else {
          func_00278150(0xf);
        }
      }
      else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 0xe) {
        func_00278150(0xf);
      }
      else if ((*(u8 *)(g_0076F3D4 + 0x0)) == 0xf) {
        func_00278150(0x10);
      }
    }
  }
  if ((*(float *)(g_0076F634 + 0x0)) <= 0.0) {
    (*(float *)(g_0076F634 + 0x0)) = 407.6;
  }
  else {
    (*(float *)(g_0076F634 + 0x0)) = (*(float *)(g_0076F634 + 0x0)) - 0.4;
  }
  return;
}

/* 0x002789C0, 0x54 bytes. */
void func_002789C0(void)
{
  if ((*(u32 *)(g_0076F3A0 + 0x0)) != 0) {
    func_00143D60((*(u32 *)(g_0076F3A0 + 0x4)));
    func_00102EC0((*(u32 *)(g_0076F3A0 + 0x4)));
    (*(u32 *)(g_0076F3A0 + 0x4)) = 0;
    func_00102EC0((*(u32 *)(g_0076F3A0 + 0xC)));
    (*(u32 *)(g_0076F3A0 + 0xC)) = 0;
    (*(u32 *)(g_0076F3A0 + 0x0)) = 0;
  }
  return;
}

/* 0x0027A040, 0x34 bytes. */
void func_0027A040(void)
{
  if ((*(u32 *)(g_0076F7B0 + 0x4)) < 1) {
    (*(u32 *)(g_0076F7B0 + 0x4)) = 0;
    (*(u32 *)(g_0076F7B0 + 0x0)) = 0;
  }
  else {
    (*(u32 *)(g_0076F7B0 + 0x4)) = (*(u32 *)(g_0076F7B0 + 0x4)) + -1;
  }
  return;
}

/* 0x0029CB20, 0x6C bytes. */
void func_0029CB20(int param_1, int param_2, u8 *param_3)
{
    u8 * iVar1;

  
  iVar1 = param_3;
  func_0029C8B0(param_3);
  if (*(char *)(iVar1 + 0x34) != '\0') {
    func_0029C9E0(param_1,*(u32 *)((u32)*(u8 *)(iVar1 + 0xd) * 4 + iVar1 + 0x10),0,
                 *(u8 *)(iVar1 + 0x59));
  }
  return;
}

/* 0x002A5A60, 0xB0 bytes. */
void func_002A5A60(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;

  
  if (param_6 < 0x107) {
    iVar1 = (int)param_6 * 0x70;
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    *(u32 *)(g_00773448 + iVar1) = (g_7000015C >> 0x10) % 100 - 0x32;
    *(u32 *)(g_00773450 + iVar1) = 0;
    *(u32 *)(g_0077344C + iVar1) = 0;
    *(u32 *)(g_00773454 + iVar1) = 0xff;
    func_00114470(param_2,param_3,param_1,iVar1 + 0x7733f0);
    *(u32 *)(g_00773418 + iVar1) = param_5;
  }
  return;
}

/* 0x002A5C40, 0xC0 bytes. */
int func_002A5C40(int param_1)
{
    int iVar2;
    u32 uVar1;
    u32 uVar3;

  
  if ((int)(*(u32 *)(g_0077BEF0 + 0x0)) < 0x107) {
    uVar3 = 0xf3;
    uVar1 = (*(u32 *)(g_0077BEF0 + 0x0));
    do {
      iVar2 = uVar1 * 0x70;
      if (*(int *)(g_00773440 + iVar2) == 0) {
        *(u32 *)(g_00773440 + iVar2) = param_1;
        *(u32 *)(g_00773444 + iVar2) = 0;
        break;
      }
      uVar1 = uVar1 + 1;
      if (0x106 < uVar1) {
        uVar1 = 0xf3;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < 0x107);
    if (uVar3 < 0x107) {
      (*(u32 *)(g_0077BEF0 + 0x0)) = (*(u32 *)(g_0077BEF0 + 0x0)) + 1;
    }
    else {
      uVar1 = 0x107;
    }
  }
  else {
    uVar1 = 0x107;
  }
  return uVar1;
}

/* 0x002A6550, 0x218 bytes. */
int func_002A6550(int param_1, int param_2, int param_3)
{
    int bVar6;
    int iVar1;
    int iVar4;
    int iVar5;
    unsigned long long * puVar7;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar8;

  
  iVar4 = (int)param_2 >> 8;
  if (((iVar4 == 8) || (iVar4 == 3)) || (iVar4 == 5)) {
    bVar6 = true;
  }
  else if ((param_2 == 0x23c) || (param_2 == 0xb)) {
    bVar6 = true;
  }
  else {
    bVar6 = false;
  }
  if (bVar6) {
    uVar2 = func_002A64C0(param_2);
    func_0023AD10(uVar2,0,0x2cdc,0x2cdc,0x1000);
    return 0;
  }
  uVar3 = param_2 & 0xff;
  if ((param_1 == 0) || (param_1 == 0)) {
    bVar6 = true;
  }
  else {
    bVar6 = false;
  }
  iVar1 = (int)uVar3;
  if (iVar4 == 2) {
    uVar8 = 1L << (param_2 & 0x3f);
    iVar5 = (iVar1 >> 6) * 8;
    puVar7 = (unsigned long long *)(iVar5 + 0x74b7f8);
    uVar3 = *puVar7;
    if (((uVar8 & uVar3) != 0) || ((*(unsigned long long *)(g_0074B808 + iVar5) & uVar8) != 0)) {
      bVar6 = false;
      goto LAB_002a66a4;
    }
    *puVar7 = uVar3 | uVar8;
  }
  else {
    if (iVar4 != 1) {
      bVar6 = true;
      goto LAB_002a66a4;
    }
    if ((!bVar6) && (((*(unsigned long long *)(g_0074B818 + 0x0)) & 1L << uVar3) != 0)) {
      bVar6 = false;
      goto LAB_002a66a4;
    }
    (*(unsigned long long *)(g_0074B818 + 0x0)) = (*(unsigned long long *)(g_0074B818 + 0x0)) | 1L << uVar3;
  }
  bVar6 = true;
LAB_002a66a4:
  if (bVar6) {
    if (param_3 != 0) {
      if (iVar4 == 7) {
        param_2 = (unsigned long long)((*(u32 *)(g_0074B818 + 0x18)) * 0x100 + iVar1);
      }
      else if (iVar4 == 6) {
        param_2 = (unsigned long long)((*(u32 *)(g_0074B818 + 0x14)) * 0x100 + iVar1);
      }
      else if (iVar4 == 5) {
        param_2 = (unsigned long long)((*(u32 *)(g_0074B818 + 0x10)) * 0x100 + iVar1);
      }
      else if (iVar4 == 4) {
        param_2 = (unsigned long long)((*(u32 *)(g_0074B818 + 0xC)) * 0x100 + iVar1);
      }
      else {
        param_2 = (unsigned long long)(iVar4 * 0x100 + iVar1);
      }
    }
    if ((int)param_2 >> 8 < 0xcb) {
      uVar2 = func_002A59F0();
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x002A7F20, 0x110 bytes. */
int func_002A7F20(int param_1, u8 *param_2)
{
    int iVar1;
    u32 * puVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;

  
  uVar3 = 0x30;
  if (g_0045D578 < 0x30) {
    iVar1 = g_0045D578 * 0x110;
    puVar2 = (u32 *)(iVar1 + 0x77cfa0);
    *(u32 *)(g_0077CFA4 + iVar1) = 1;
    if (param_1 < 0x10) {
      if (param_1 == 0) {
        param_1 = 1;
      }
      *(u8 *)(g_0077CFA9 + iVar1) = param_1;
    }
    else {
      *(u8 *)(g_0077CFA9 + iVar1) = 0x10;
    }
    uVar6 = 0;
    *(u8 *)(g_0077CFA8 + iVar1) = 0;
    *(u8 *)(g_0077CFAA + iVar1) = 0;
    g_0045D574 = g_0045D574 + -1;
    if (*(char *)(g_0077CFA9 + iVar1) != '\0') {
      do {
        uVar3 = *(u32 *)(param_2 + 0x34);
        uVar4 = *(u32 *)(param_2 + 0x38);
        uVar5 = *(u32 *)(param_2 + 0x3c);
        puVar2[uVar6 * 4 + 4] = *(u32 *)(param_2 + 0x30);
        puVar2[uVar6 * 4 + 5] = uVar3;
        puVar2[uVar6 * 4 + 6] = uVar4;
        puVar2[uVar6 * 4 + 7] = uVar5;
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(u8 *)(g_0077CFA9 + iVar1));
    }
    uVar3 = *puVar2;
    if (g_0045D578 < 0x30) {
      iVar1 = g_0045D578 * 0x110 + 0x77cfa0;
      do {
        if (*(int *)((u8 *)PS2_PTR(iVar1) + 4) == 0) {
          return uVar3;
        }
        g_0045D578 = g_0045D578 + 1;
        iVar1 = iVar1 + 0x110;
      } while (g_0045D578 < 0x30);
    }
  }
  return uVar3;
}

/* 0x002C1830, 0x48 bytes. */
int func_002C1830(int param_1, int param_2, int param_3)
{
    u32 uStack_10;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;

  
  uStack_4 = 0;
  uStack_10 = param_1;
  uStack_c = param_2;
  uStack_8 = param_3;
  func_001185B0(0x700001e0,0x50);
  func_001904E0(0x2c1880,&uStack_10);
  return uStack_4;
}

/* 0x002CCDB0, 0xA8 bytes. */
void func_002CCDB0(int param_1, u8 *param_2)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;

  
  param_1 = param_1 * 0x10;
  iVar1 = *(int *)((g_004420E0 + 0x4) + param_1);
  iVar2 = *(int *)((g_004420E0 + 0x0) + param_1);
  iVar3 = *(int *)((g_004420E0 + 0x8) + param_1);
  iVar4 = *(int *)((g_004420E0 + 0xC) + param_1);
  *(long long *)(param_2 + 0x28) = (long long)(int)(iVar2 << 4 | 8) | (long long)(int)(iVar1 << 4 | 8) << 0x10;
  *(long long *)(param_2 + 0x38) =
       (long long)(int)((iVar3 + iVar2) * 0x10 | 8) | (long long)(int)((iVar4 + iVar1) * 0x10 | 8) << 0x10;
  return;
}

/* 0x002CDD40, 0x44 bytes. */
void func_002CDD40(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  func_001ABE40(param_1,param_7,param_2,param_3,0,param_4,param_5,0x80);
  return;
}

/* 0x002CE0C0, 0x44 bytes. */
void func_002CE0C0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  func_001ABE40(param_1,param_7,param_2,param_3,0,param_4,param_5,0x80);
  return;
}

/* 0x002CE110, 0x48 bytes. */
void func_002CE110(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  func_001ABE40(param_1,(param_7 & 0xff) + 0x2d,param_2,param_3,0,param_4,param_5,0x80);
  return;
}

/* 0x002D6930, 0x54 bytes. */
void func_002D6930(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
  func_001ABE40((*(u32 *)(g_00799A6C + 0x0)),param_1,param_2,param_3,param_4,param_5,param_6,param_8);
  return;
}

/* 0x002D6BF0, 0x34 bytes. */
void func_002D6BF0(void)
{
  func_0017E110((*(u8 *)(g_00669DB2 + 0x0)));
  (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xef;
  return;
}

/* 0x002D6FE0, 0x9C bytes. */
int func_002D6FE0(int param_1)
{
    long long lVar2;
    unsigned long long uVar1;

  
  uVar1 = func_002F27D0(*(u32 *)(param_1 * 0x48 + 0x669de8));
  lVar2 = func_0032F2A0(uVar1);
  if (0x19 < lVar2) {
    if ((lVar2 == 0x21) || (lVar2 == 0x20)) {
      lVar2 = 0x1c;
    }
    else if (lVar2 == 0x2a) {
      lVar2 = 0x1b;
    }
    else if (lVar2 == 0x26) {
      lVar2 = 0x1a;
    }
    else {
      lVar2 = 0x1a;
    }
  }
  return lVar2;
}

/* 0x002D75C0, 0x70 bytes. */
void func_002D75C0(u8 *param_1)
{
    u8 * iVar1;
    u8 * iVar5;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

  
  iVar5 = param_1;
  if (((*(u32 *)(iVar5 + 0xbc) & 0x100000) == 0) && (*(short *)(iVar5 + 0x78) == 0)) {
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar5 + 0x14));
    *(u32 *)(iVar1 + 0x13c) = 0;
    uVar4 = g_700000CC;
    uVar3 = g_700000C8;
    uVar2 = g_700000C4;
    *(u32 *)(iVar1 + 0x1d0) = g_700000C0;
    *(u32 *)(iVar1 + 0x1d4) = uVar2;
    *(u32 *)(iVar1 + 0x1d8) = uVar3;
    *(u32 *)(iVar1 + 0x1dc) = uVar4;
    func_00204D00(param_1,1);
    *(u16 *)(iVar5 + 0x78) = 0x96;
    func_00204D20(param_1);
  }
  return;
}

/* 0x002D9310, 0xE8 bytes. */
void func_002D9310(u8 *param_1)
{
    u8 * iVar4;
    u8 * puVar1;
    u8 * puVar2;
    u8 * puVar3;

  
  if (g_0045D5EC == 0) {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C18C));
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C174));
    puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C194));
  }
  else {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C244));
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C22C));
    puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C24C));
  }
  iVar4 = param_1;
  func_001204B0(*(u32 *)(iVar4 + 0x24),puVar3,puVar2,0x2a6,puVar1);
  func_001206B0(*(u32 *)(iVar4 + 0x24),0x4427c0);
  if (g_0045D5EC == 0) {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C190));
  }
  else {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C248));
  }
  func_001206B0(*(u32 *)(iVar4 + 0x24),puVar1);
  func_002D82C0(param_1,1);
  *(u32 *)(iVar4 + 0x14) = 0x16;
  *(u32 *)(iVar4 + 0x18) = 0x3b9;
  *(u32 *)(iVar4 + 0x48) = 1;
  *(u32 *)(iVar4 + 0x70) = 4;
  *(u32 *)(iVar4 + 0x4c) = 1;
  return;
}

/* 0x002D9400, 0xE8 bytes. */
void func_002D9400(u8 *param_1)
{
    u8 * iVar4;
    u8 * puVar1;
    u8 * puVar2;
    u8 * puVar3;

  
  if (g_0045D5EC == 0) {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C18C));
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C170));
    puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C194));
  }
  else {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C244));
    puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C228));
    puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C24C));
  }
  iVar4 = param_1;
  func_001204B0(*(u32 *)(iVar4 + 0x24),puVar3,puVar2,0x2a6,puVar1);
  func_001206B0(*(u32 *)(iVar4 + 0x24),0x4427c0);
  if (g_0045D5EC == 0) {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C190));
  }
  else {
    puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C248));
  }
  func_001206B0(*(u32 *)(iVar4 + 0x24),puVar1);
  func_002D82C0(param_1,1);
  *(u32 *)(iVar4 + 0x14) = 0x16;
  *(u32 *)(iVar4 + 0x18) = 0x3b9;
  *(u32 *)(iVar4 + 0x48) = 1;
  *(u32 *)(iVar4 + 0x70) = 4;
  *(u32 *)(iVar4 + 0x4c) = 1;
  return;
}

/* 0x002D9EE0, 0x1B0 bytes. */
void func_002D9EE0(u8 *param_1)
{
    u8 auStack_80[128];
    int iVar1;
    u8 * iVar4;
    u8 * puVar2;
    u8 * puVar3;
    unsigned long long uVar5;

  
  uVar5 = 10;
  iVar4 = param_1;
  iVar1 = *(int *)(iVar4 + 0x10);
  if (iVar1 == 9) {
    uVar5 = 2;
  }
  else if (iVar1 == 7) {
    func_0022DD80(*(u32 *)(iVar4 + 0xc),0x97000);
    uVar5 = 4;
  }
  else if (iVar1 == 5) {
    func_0022DDC0(0,0);
    uVar5 = 3;
  }
  else if (iVar1 == 4) {
    func_002D8730(param_1,2,auStack_80);
    func_0022DE00(1,auStack_80);
    if (g_0045D5EC == 0) {
      puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C188));
      puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C168));
    }
    else {
      puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C240));
      puVar3 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C220));
    }
    func_001204B0(*(u32 *)(iVar4 + 0x24),0x4426b8,puVar3,puVar2);
    func_002D82C0(param_1,0);
    uVar5 = 1;
    (*(u8 *)(g_006934B9 + 0x0)) = 1;
  }
  else if (iVar1 == 1) {
    func_002D8730(param_1,0,auStack_80);
    func_0022DE50(auStack_80);
    uVar5 = 8;
  }
  else if (iVar1 == 0) {
    if (*(int *)(iVar4 + 0x2c) != 2) {
      if (g_0045D5EC == 0) {
        puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C120));
      }
      else {
        puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0043C1D8));
      }
      func_001204B0(*(u32 *)(iVar4 + 0x24),0x4426b0,puVar2);
      func_002D82C0(param_1,0);
      (*(u8 *)(g_006934B9 + 0x0)) = 1;
    }
    uVar5 = 0;
  }
  func_0022DD70(uVar5);
  func_0022DD50();
  return;
}

/* 0x002DB9A0, 0x50 bytes. */
void func_002DB9A0(void)
{
  if ((g_0045D5F0 == 7) && ((g_0045D5F4 == 2 || (g_0045D5F4 == 1)))) {
    func_003BFD80();
  }
  return;
}

/* 0x0032C940, 0x90 bytes. */
void func_0032C940(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar1;

  
  if (param_4 == 0) {
    if (param_5 == 0) {
      iVar1 = param_3 * 4 + g_0045D6EC;
      if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x4ec8) != 3) {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x4ec8) = 2;
      }
    }
    else {
      *(u32 *)(param_3 * 4 + g_0045D6EC + 0x4ec8) = 3;
    }
  }
  else {
    iVar1 = param_3 * 4 + g_0045D6EC;
    if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x4ed0) == param_2) {
      return;
    }
    if (param_5 == 0) {
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x4ec8) = 0;
    }
    else {
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x4ec8) = 1;
    }
    *(int *)((u8 *)PS2_PTR(iVar1) + 0x4ed0) = param_2;
  }
  iVar1 = param_3 * 4 + g_0045D6EC;
  *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x4ec0) = 0;
  *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x4ed8) = param_1;
  return;
}

/* 0x003701E0, 0x1C0 bytes. */
void func_003701E0(int param_1, int param_2, int param_3, int param_4)
{
    u32 auStack_10[4];
    u8 * iVar2;
    int iVar3;
    int iVar4;
    int uVar1;

  
  auStack_10[0] = (*(u32 *)(g_004160E0 + 0x0));
  auStack_10[1] = (*(u32 *)(g_004160E0 + 0x4));
  iVar4 = param_1 * 0x68;
  auStack_10[2] = (*(u32 *)(g_004160E0 + 0x8));
  auStack_10[3] = (*(u32 *)(g_004160E0 + 0xC));
  if (param_3 != 0) {
    iVar3 = iVar4 / 0x68;
    iVar2 = func_00338410(iVar3);
    *(char *)(iVar2 + 0x27) = (char)param_2;
    iVar2 = func_00338410(iVar3);
    *(char *)(iVar2 + 0x29) = (char)param_4;
    uVar1 = *(u8 *)(auStack_10 + (u32)param_2);
    iVar3 = PS2_ADDR(func_00338410(iVar3));
    *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x28) = uVar1;
    if (param_2 == 3) {
      iVar3 = PS2_ADDR(func_00338410((param_4 * 0x68) / 0x68));
      *(char *)((u8 *)PS2_PTR(iVar3) + 0x2a) = (char)param_1;
    }
  }
  func_0036FD30(*(u8 *)(*(int *)(g_006A1D58 + iVar4) + 0x79),0);
  iVar3 = PS2_ADDR(func_00338410(iVar4 / 0x68));
  *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x2b) = *(u8 *)((u8 *)PS2_PTR(iVar3) + 0x2b) | (u8)(1 << ((u32)param_2 & 0x1f));
  iVar4 = PS2_ADDR(func_00338410(iVar4 / 0x68));
  *(u8 *)((u8 *)PS2_PTR(iVar4) + 0x2b) = *(u8 *)((u8 *)PS2_PTR(iVar4) + 0x2b) & 0x7f;
  return;
}
/* MISSING ['0x4160e0', '0x4160e4', '0x4160e8', '0x4160ec'] */

/* 0x00373050, 0x4D8 bytes. */
void func_00373050(void)
{
    int aiStack_70[28];
    int aiStack_e0[28];
    int bVar1;
    int bVar2;
    int iVar10;
    int iVar11;
    int iVar4;
    long long lVar5;
    long long lVar7;
    long long lVar8;
    int * piVar9;
    u32 uVar3;
    unsigned long long uVar6;

  
  uVar3 = (*(u32 *)(g_007B98A4 + 0x8));
  iVar10 = 0;
  lVar5 = func_00327D50();
  if ((uVar3 & 1) != 0) {
    uVar6 = func_002FB2D0(lVar5);
    func_0030B640(uVar6);
  }
  if ((uVar3 & 2) != 0) {
    if ((*(u32 *)(g_007B98A4 + 0x0)) == 1) {
      lVar7 = 1;
    }
    else if ((*(u32 *)(g_007B98A4 + 0x0)) == 2) {
      lVar7 = 2;
    }
    else {
      lVar7 = -1;
      if ((*(u32 *)(g_007B98A4 + 0x0)) == 3) {
        lVar7 = 3;
      }
    }
    if (-1 < lVar7) {
      func_003239F0(aiStack_70);
    }
  }
  iVar11 = 0;
  lVar7 = func_0030AB90();
  if (0 < lVar7) {
    piVar9 = aiStack_e0;
    do {
      bVar2 = false;
      lVar7 = func_0030AFF0(iVar11);
      if ((*(u32 *)(g_007B98A4 + 0x0)) == 0x18) {
        bVar2 = true;
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0x19) {
        uVar6 = func_00327D50();
        lVar7 = func_002FC0C0(uVar6,lVar7);
        if (lVar7 != 0x19) {
          bVar2 = true;
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 9) {
        lVar7 = func_002FB100(lVar7);
        if (lVar7 != 0) {
          bVar2 = true;
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0x11) {
        lVar7 = func_0030AFF0(iVar11);
        lVar8 = func_00327D50();
        if (lVar7 == lVar8) {
          lVar7 = func_0030AD80(iVar11);
          lVar8 = func_0030AE80(iVar11);
          if (lVar7 < lVar8) {
            bVar2 = true;
          }
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0xf) {
        uVar6 = func_00327D50();
        lVar7 = func_0030C890(iVar11,uVar6);
        if (lVar7 != 0) {
          bVar2 = true;
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0x15) {
        bVar1 = false;
        if (-1 < lVar7) {
          lVar8 = func_0030AB90();
          bVar1 = lVar7 < lVar8;
        }
        if ((bVar1) && (lVar7 != lVar5)) {
          lVar8 = func_002FB1A0(lVar7);
          lVar7 = func_002FB220(lVar7);
          if ((lVar7 == 0) && ((lVar8 == 0x19 || (lVar8 == lVar5)))) {
            bVar2 = true;
          }
        }
      }
      else if (((((*(u32 *)(g_007B98A4 + 0x0)) == 0xd) || ((*(u32 *)(g_007B98A4 + 0x0)) == 0x17)) || ((*(u32 *)(g_007B98A4 + 0x0)) == 0x16)) ||
              ((*(u32 *)(g_007B98A4 + 0x0)) == 0x14)) {
        bVar1 = false;
        if (-1 < lVar7) {
          lVar8 = func_0030AB90();
          bVar1 = lVar7 < lVar8;
        }
        if ((bVar1) && (lVar7 != lVar5)) {
          if ((uVar3 & 4) == 0) {
            if ((uVar3 & 8) == 0) {
              bVar2 = true;
            }
            else {
              lVar7 = func_0030B2F0(iVar11);
              if (lVar7 != 0) {
                bVar2 = true;
              }
            }
          }
          else {
            lVar7 = func_002FAFA0(lVar5,lVar7);
            if (lVar7 != 0) {
              bVar2 = true;
            }
          }
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0x13) {
        bVar1 = false;
        if (-1 < lVar7) {
          lVar8 = func_0030AB90();
          bVar1 = lVar7 < lVar8;
        }
        if (((bVar1) && (lVar7 != lVar5)) && (lVar7 = func_002FB120(lVar7), lVar7 == 0)) {
          bVar2 = true;
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 10) {
        if (lVar7 == lVar5) {
          bVar2 = true;
        }
      }
      else if ((((*(u32 *)(g_007B98A4 + 0x0)) == 3) || ((*(u32 *)(g_007B98A4 + 0x0)) == 2)) || ((*(u32 *)(g_007B98A4 + 0x0)) == 1)) {
        if (aiStack_70[iVar11] != 0) {
          bVar2 = true;
        }
      }
      else if ((*(u32 *)(g_007B98A4 + 0x0)) == 0) {
        lVar8 = func_0030B2F0(iVar11);
        if (((lVar8 != 0) || ((lVar8 = func_002FA790(lVar5), lVar8 != 0 && (lVar7 != lVar5)))) &&
           (lVar7 = func_002FAFA0(lVar5,lVar7), lVar7 == 0)) {
          bVar2 = true;
        }
      }
      else if (((uVar3 & 0x80000000) != 0) || (lVar7 = func_0030B2F0(iVar11), lVar7 != 0)) {
        bVar2 = true;
      }
      iVar4 = func_0030AB90();
      if (iVar4 <= iVar11) {
        bVar2 = false;
      }
      if (bVar2) {
        *piVar9 = iVar11;
        piVar9 = piVar9 + 1;
        *(u32 *)(iVar11 * 4 + 0x7b98b8) = 1;
        iVar10 = iVar10 + 1;
      }
      iVar11 = iVar11 + 1;
      iVar4 = func_0030AB90();
    } while (iVar11 < iVar4);
  }
  if ((*(u32 *)(g_007B98A4 + 0x0)) != 6) {
    func_003A97C0(aiStack_e0,iVar10,uVar3 & 2);
  }
  func_0030B330();
  return;
}

/* 0x003890D0, 0x78 bytes. */
int func_003890D0(u8 *param_1)
{
    u8 auStack_20[16];
    int iVar1;
    u32 uStack_10;

  
  iVar1 = *(int *)(param_1 + 0x690);
  if (iVar1 == 2) {
    func_003DB480(0,5);
  }
  else if ((iVar1 != 1) && (iVar1 == 0)) {
    uStack_10 = 0x80;
    func_003DB220(0,auStack_20);
    func_003DB460(0,5);
  }
  return 0;
}

/* 0x00389150, 0x78 bytes. */
int func_00389150(u8 *param_1)
{
    int iVar1;
    u32 uStack_1c;
    u32 uStack_20;

  
  iVar1 = *(int *)(param_1 + 0x690);
  if (iVar1 == 2) {
    func_003DB480(1);
  }
  else if ((iVar1 != 1) && (iVar1 == 0)) {
    uStack_20 = 0x40;
    uStack_1c = 0x50;
    func_003DB220(1,&uStack_20);
    func_003DB460(1,2);
  }
  return 0;
}

/* 0x00389770, 0x74 bytes. */
int func_00389770(u8 *param_1)
{
    u32 uStack_1c;
    u32 uStack_20;

  
  if (*(int *)(param_1 + 0x690) == 1) {
    func_003DB480(5,2);
  }
  else if (*(int *)(param_1 + 0x690) == 0) {
    uStack_20 = 0x80;
    uStack_1c = 0x40;
    func_003DB220(5,&uStack_20);
    func_003DB460(5,2);
  }
  return 0;
}

/* 0x003898F0, 0x6C bytes. */
int func_003898F0(u8 *param_1)
{
    u8 auStack_20[16];
    u32 uStack_10;

  
  if (*(int *)(param_1 + 0x690) == 1) {
    func_003DB480(8,5);
  }
  else if (*(int *)(param_1 + 0x690) == 0) {
    uStack_10 = 0x80;
    func_003DB220(8,auStack_20);
    func_003DB460(8,5);
  }
  return 0;
}

/* 0x003899E0, 0x70 bytes. */
int func_003899E0(u8 *param_1)
{
    u32 uStack_1c;
    u32 uStack_20;

  
  if (*(int *)(param_1 + 0x690) == 2) {
    func_003DB480(9);
  }
  else if (*(int *)(param_1 + 0x690) == 0) {
    uStack_20 = 0x93;
    uStack_1c = 0x48;
    func_003DB220(9,&uStack_20);
    func_003DB460(9,2);
  }
  return 0;
}

/* 0x00393D30, 0x3D0 bytes. */
int func_00393D30(void)
{
    long long lVar3;
    u32 * puVar1;
    u32 uVar2;
    int uVar4;

  
  puVar1 = (u32 *)func_00391250();
  if ((long long)(*(char *)(g_007BA81D + 0x0)) << 0x3f < 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar4 & 0x1000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar4 = 0;
      }
      else {
        uVar4 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar4 & 0x4000) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar4 = 0;
        }
        else {
          uVar4 = (*(u16 *)(g_0050074C + 0x2));
        }
        if ((uVar4 & 0x1000) == 0) {
          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
            uVar4 = 0;
          }
          else {
            uVar4 = (*(u16 *)(g_0050074C + 0x2));
          }
          if ((uVar4 & 0x4000) == 0) {
            if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
              uVar4 = 0;
            }
            else {
              uVar4 = (*(u16 *)(g_0050074C + 0x0));
            }
            if ((uVar4 & 0x40) == 0) {
              if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                uVar4 = 0;
              }
              else {
                uVar4 = (*(u16 *)(g_0050074C + 0x0));
              }
              if ((uVar4 & 0x10) != 0) {
                func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                lVar3 = func_003E9630();
                if (lVar3 == 0) {
                  func_003E9750(0);
                }
                else {
                  func_003E97D0(3);
                }
                func_003E9700(0);
                if (puVar1[0xd] == 0) {
                  func_003914C0();
                  puVar1[1] = 0;
                }
                else {
                  func_00397660();
                  puVar1[1] = 0;
                }
                func_00391E60();
                func_00391CC0();
              }
            }
            else {
              func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
              puVar1[1] = 0;
              if (*puVar1 == 0) {
                puVar1[1] = 2;
              }
              else {
                puVar1[1] = 4;
                func_00391C30();
                func_00391F50();
              }
              func_00391CC0();
            }
          }
          else if (*puVar1 == 0) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *puVar1 = 1;
          }
        }
        else if (*puVar1 == 1) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *puVar1 = 0;
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        uVar2 = *puVar1 + 1 & 1;
        if (((int)(*puVar1 + 1) < 0) && (uVar2 != 0)) {
          uVar2 = uVar2 - 2;
        }
        *puVar1 = uVar2;
      }
    }
    else {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      uVar2 = *puVar1 + 1 & 1;
      if (((int)(*puVar1 + 1) < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 2;
      }
      *puVar1 = uVar2;
    }
  }
  return 0;
}

/* 0x00394100, 0x63C bytes. */
int func_00394100(void)
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
  if ((long long)(*(char *)(g_007BA7DD + 0x0)) << 0x3f < 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar3 = 0;
    }
    else {
      uVar3 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar3 & 0x1000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar3 & 0x4000) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar3 = 0;
        }
        else {
          uVar3 = (*(u16 *)(g_0050074C + 0x2));
        }
        if ((uVar3 & 0x1000) == 0) {
          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
            uVar3 = 0;
          }
          else {
            uVar3 = (*(u16 *)(g_0050074C + 0x2));
          }
          if ((uVar3 & 0x4000) == 0) {
            if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
              uVar3 = 0;
            }
            else {
              uVar3 = (*(u16 *)(g_0050074C + 0x2));
            }
            if ((uVar3 & 0x8000) == 0) {
              if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                uVar3 = 0;
              }
              else {
                uVar3 = (*(u16 *)(g_0050074C + 0x2));
              }
              if ((uVar3 & 0x2000) == 0) {
                if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                  uVar3 = 0;
                }
                else {
                  uVar3 = (*(u16 *)(g_0050074C + 0x0));
                }
                if ((uVar3 & 0x40) == 0) {
                  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                    uVar3 = 0;
                  }
                  else {
                    uVar3 = (*(u16 *)(g_0050074C + 0x0));
                  }
                  if ((uVar3 & 0x10) != 0) {
                    func_0023AA40();
                    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                    *(u32 *)(iVar1 + 4) = 1;
                    func_00391EB0();
                    func_00391CC0();
                  }
                }
                else {
                  func_003E74B0();
                }
              }
              else {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                iVar2 = *(int *)(iVar1 + 0xc) + 1;
                *(int *)(iVar1 + 0xc) = iVar2;
                if (5 < iVar2) {
                  *(u32 *)(iVar1 + 0xc) = 0;
                }
                *(u16 *)(iVar1 + 0x14c) = 0;
                *(u16 *)(iVar1 + 0x14e) = 0;
                func_00391A10();
              }
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              iVar2 = *(int *)(iVar1 + 0xc) + -1;
              *(int *)(iVar1 + 0xc) = iVar2;
              if (iVar2 < 0) {
                *(u32 *)(iVar1 + 0xc) = 5;
              }
              *(u16 *)(iVar1 + 0x14c) = 0;
              *(u16 *)(iVar1 + 0x14e) = 0;
              func_00391A10();
            }
          }
          else if ((int)*(short *)(iVar1 + 0x14e) + (int)*(short *)(iVar1 + 0x14c) < sVar5 + -1) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            sVar6 = *(short *)(iVar1 + 0x14c) + 1;
            *(short *)(iVar1 + 0x14c) = sVar6;
            if ((8 < (long long)sVar6) || ((long long)sVar5 <= (long long)sVar6)) {
              if ((long long)((int)*(short *)(iVar1 + 0x14e) + (int)sVar6) < (long long)sVar5) {
                *(short *)(iVar1 + 0x14c) = *(short *)(iVar1 + 0x14c) + -1;
                *(short *)(iVar1 + 0x14e) = *(short *)(iVar1 + 0x14e) + 1;
              }
              else {
                *(u16 *)(iVar1 + 0x14c) = 0;
                *(u16 *)(iVar1 + 0x14e) = 0;
              }
            }
          }
        }
        else if (0 < (int)*(short *)(iVar1 + 0x14c) + (int)*(short *)(iVar1 + 0x14e)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          sVar6 = *(short *)(iVar1 + 0x14c);
          sVar4 = sVar6 + -1;
          *(short *)(iVar1 + 0x14c) = sVar4;
          if (sVar4 < 0) {
            if (*(short *)(iVar1 + 0x14e) < 1) {
              if ((int)sVar5 / 9 < 1) {
                *(short *)(iVar1 + 0x14c) = sVar5 % 9 + -1;
                *(u16 *)(iVar1 + 0x14e) = 0;
              }
              else {
                *(u16 *)(iVar1 + 0x14c) = 8;
                *(short *)(iVar1 + 0x14e) = sVar5 + -9;
              }
            }
            else {
              *(short *)(iVar1 + 0x14c) = sVar6;
              *(short *)(iVar1 + 0x14e) = *(short *)(iVar1 + 0x14e) + -1;
            }
          }
        }
      }
      else {
        lVar7 = (long long)sVar5;
        if (1 < lVar7) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        }
        sVar5 = *(short *)(iVar1 + 0x14c) + 1;
        *(short *)(iVar1 + 0x14c) = sVar5;
        if ((8 < (long long)sVar5) || (lVar7 <= sVar5)) {
          if ((int)*(short *)(iVar1 + 0x14e) + (int)sVar5 < lVar7) {
            *(short *)(iVar1 + 0x14c) = *(short *)(iVar1 + 0x14c) + -1;
            *(short *)(iVar1 + 0x14e) = *(short *)(iVar1 + 0x14e) + 1;
          }
          else {
            *(u16 *)(iVar1 + 0x14c) = 0;
            *(u16 *)(iVar1 + 0x14e) = 0;
          }
        }
      }
    }
    else {
      if (1 < sVar5) {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      }
      sVar6 = *(short *)(iVar1 + 0x14c);
      sVar4 = sVar6 + -1;
      *(short *)(iVar1 + 0x14c) = sVar4;
      if (sVar4 < 0) {
        if (*(short *)(iVar1 + 0x14e) < 1) {
          if ((int)sVar5 / 9 < 1) {
            *(short *)(iVar1 + 0x14c) = sVar5 % 9 + -1;
            *(u16 *)(iVar1 + 0x14e) = 0;
          }
          else {
            *(u16 *)(iVar1 + 0x14c) = 8;
            *(short *)(iVar1 + 0x14e) = sVar5 + -9;
          }
        }
        else {
          *(short *)(iVar1 + 0x14c) = sVar6;
          *(short *)(iVar1 + 0x14e) = *(short *)(iVar1 + 0x14e) + -1;
        }
      }
    }
  }
  return 0;
}

/* 0x003967D0, 0x98C bytes. */
void func_003967D0(int param_1)
{
    int bVar1;
    u8 * iVar2;
    long long lVar3;
    u32 * puVar6;
    int uVar4;
    u32 uVar5;

  
  iVar2 = func_002EE540();
  if (*(char *)(iVar2 + 0x12) == '\0') {
    bVar1 = false;
  }
  else if (*(char *)(iVar2 + 0x13) == *(char *)(iVar2 + 0x12)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    return;
  }
  puVar6 = (u32 *)param_1;
  if (puVar6[7] == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar4 & 0x8000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar4 = 0;
      }
      else {
        uVar4 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar4 & 0x2000) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar4 = 0;
        }
        else {
          uVar4 = (*(u16 *)(g_0050074C + 0x0));
        }
        if ((uVar4 & 0x1000) == 0) {
          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
            uVar4 = 0;
          }
          else {
            uVar4 = (*(u16 *)(g_0050074C + 0x0));
          }
          if ((uVar4 & 0x4000) == 0) {
            if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
              uVar4 = 0;
            }
            else {
              uVar4 = (*(u16 *)(g_0050074C + 0x2));
            }
            if ((uVar4 & 0x8000) == 0) {
              if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                uVar4 = 0;
              }
              else {
                uVar4 = (*(u16 *)(g_0050074C + 0x2));
              }
              if ((uVar4 & 0x2000) == 0) {
                if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                  uVar4 = 0;
                }
                else {
                  uVar4 = (*(u16 *)(g_0050074C + 0x2));
                }
                if ((uVar4 & 0x1000) == 0) {
                  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                    uVar4 = 0;
                  }
                  else {
                    uVar4 = (*(u16 *)(g_0050074C + 0x2));
                  }
                  if ((uVar4 & 0x4000) == 0) {
                    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                      uVar4 = 0;
                    }
                    else {
                      uVar4 = (*(u16 *)(g_0050074C + 0x2));
                    }
                    if ((uVar4 & 4) == 0) {
                      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                        uVar4 = 0;
                      }
                      else {
                        uVar4 = (*(u16 *)(g_0050074C + 0x2));
                      }
                      if ((uVar4 & 8) == 0) {
                        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                          uVar4 = 0;
                        }
                        else {
                          uVar4 = (*(u16 *)(g_0050074C + 0x0));
                        }
                        if ((uVar4 & 0x40) == 0) {
                          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                            uVar4 = 0;
                          }
                          else {
                            uVar4 = (*(u16 *)(g_0050074C + 0x0));
                          }
                          if ((uVar4 & 0x10) != 0) {
                            puVar6[0xd] = 4;
                            func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                          }
                        }
                        else if ((*puVar6 & 0x10) == 0) {
                          func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
                        }
                        else {
                          lVar3 = func_003A17A0(puVar6[10] + puVar6[0xb] * 5 + puVar6[9] * 0x32);
                          if (lVar3 == 0) {
                            func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
                          }
                          else {
                            puVar6[7] = 1;
                            func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
                          }
                        }
                      }
                      else {
                        uVar5 = puVar6[9];
                        puVar6[9] = uVar5 + 1;
                        if (3 < (int)(uVar5 + 1)) {
                          puVar6[9] = 0;
                        }
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      }
                    }
                    else {
                      uVar5 = puVar6[9];
                      puVar6[9] = uVar5 - 1;
                      if ((int)(uVar5 - 1) < 0) {
                        puVar6[9] = 3;
                      }
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    }
                  }
                  else if ((int)puVar6[0xb] < 9) {
                    puVar6[0xb] = puVar6[0xb] + 1;
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  }
                }
                else if (0 < (int)puVar6[0xb]) {
                  puVar6[0xb] = puVar6[0xb] - 1;
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                }
              }
              else if ((int)puVar6[10] < 4) {
                puVar6[10] = puVar6[10] + 1;
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              }
            }
            else if (0 < (int)puVar6[10]) {
              puVar6[10] = puVar6[10] - 1;
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            }
          }
          else {
            uVar5 = puVar6[0xb];
            puVar6[0xb] = uVar5 + 1;
            if (9 < (int)(uVar5 + 1)) {
              puVar6[0xb] = 0;
            }
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          }
        }
        else {
          uVar5 = puVar6[0xb];
          puVar6[0xb] = uVar5 - 1;
          if ((int)(uVar5 - 1) < 0) {
            puVar6[0xb] = 9;
          }
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        }
      }
      else {
        uVar5 = puVar6[10];
        puVar6[10] = uVar5 + 1;
        if (4 < (int)(uVar5 + 1)) {
          puVar6[10] = 0;
        }
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      }
    }
    else {
      uVar5 = puVar6[10];
      puVar6[10] = uVar5 - 1;
      if ((int)(uVar5 - 1) < 0) {
        puVar6[10] = 4;
      }
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
    }
  }
  else {
    func_003A1830(puVar6[10] + puVar6[0xb] * 5 + puVar6[9] * 0x32,0);
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar4 & 0x8000) != 0) {
      func_00396680(param_1);
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      uVar5 = puVar6[0xb];
      goto LAB_003970d4;
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar4 & 0x2000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar4 = 0;
      }
      else {
        uVar4 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar4 & 0x40) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar4 = 0;
        }
        else {
          uVar4 = (*(u16 *)(g_0050074C + 0x0));
        }
        if ((uVar4 & 0x10) != 0) {
          puVar6[7] = 0;
          func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        }
      }
      else {
        puVar6[7] = 0;
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      }
    }
    else {
      func_00396530(param_1);
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
    }
  }
  uVar5 = puVar6[0xb];
LAB_003970d4:
  puVar6[0xc] = puVar6[10] + uVar5 * 5 + puVar6[9] * 0x32;
  if ((puVar6[7] != 0) && ((int)puVar6[8] < 100)) {
    puVar6[8] = puVar6[8] + 5;
  }
  if ((puVar6[7] == 0) && (0x32 < (int)puVar6[8])) {
    puVar6[8] = puVar6[8] - 5;
  }
  return;
}

/* 0x00398C90, 0xD0 bytes. */
void func_00398C90(int param_1, int param_2, int param_3, int param_4)
{
    unsigned long long uVar1;
    unsigned long long uVar2;

  
  if (param_4 != 4) {
    uVar1 = PS2_ADDR(func_0030D7D0());
    uVar2 = func_00397B00(param_2 + ((g_00459B60 + 0x4))[param_3 * 2] + -4);
    func_001ABEA0(uVar1,0x51,param_1 + ((g_00459B60 + 0x0))[param_3 * 2],uVar2,0,0x28,0x18,0);
  }
  return;
}

/* 0x00399EE0, 0x19C bytes. */
void func_00399EE0(void)
{
    int iVar1;
    long long lVar2;

  
  if ((*(u32 *)(g_007BA8B8 + 0x4)) - 6U < 3) {
    iVar1 = 0x10f;
  }
  else if ((*(u32 *)(g_007BAA60 + 0x0)) == 0) {
    if ((*(u32 *)(g_007BA8B8 + 0xC)) == -1) {
      lVar2 = func_0039A5B0();
      if ((lVar2 == 0) || (lVar2 = func_0039A630(), lVar2 < 0)) {
        lVar2 = func_0039A570();
        if ((lVar2 == 0) || (lVar2 = func_0039A630(), lVar2 < 0)) {
          if ((*(u32 *)(g_007BA8B8 + 0x0)) == 0x14) {
            iVar1 = 0x134;
          }
          else {
            iVar1 = 0x1bb;
          }
        }
        else {
          iVar1 = 0x1bc;
        }
      }
      else {
        iVar1 = 0x1bd;
      }
    }
    else {
      lVar2 = func_0039A630();
      if (lVar2 < 0) {
        iVar1 = 0x146;
      }
      else {
        iVar1 = 0x19d;
      }
    }
  }
  else if ((*(u32 *)(g_007BA8B8 + 0xC)) == -1) {
    lVar2 = func_0039A5B0();
    if ((lVar2 == 0) || (lVar2 = func_0039A630(), lVar2 < 0)) {
      lVar2 = func_0039A570();
      if ((lVar2 == 0) || (lVar2 = func_0039A630(), lVar2 < 0)) {
        if ((*(u32 *)(g_007BA8B8 + 0x0)) == 0x14) {
          iVar1 = 0x116;
        }
        else {
          iVar1 = 0x146;
        }
      }
      else {
        iVar1 = 0x19d;
      }
    }
    else {
      iVar1 = 0x19e;
    }
  }
  else {
    iVar1 = 0x146;
  }
  func_001A7DC0(((u8 *)PS2_PTR(((ps2ptr *)g_0043C120)[iVar1])),0x80,1);
  return;
}

/* 0x0039D770, 0x6C bytes. */
void func_0039D770(void)
{
    int iVar1;

  
  iVar1 = PS2_ADDR(func_002FC2C0());
  iVar1 = *(int *)(*(int *)((u8 *)PS2_PTR(iVar1) + 0x6ac) + 4);
  if (iVar1 == 1) {
    func_0039D740();
    func_001A7DC0(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C55C)),0x80,1);
  }
  else if (iVar1 == 0) {
    func_0039D5C0();
  }
  return;
}

/* 0x0039D820, 0x6C bytes. */
void func_0039D820(void)
{
    int iVar1;

  
  iVar1 = PS2_ADDR(func_002FC2C0());
  iVar1 = *(int *)(*(int *)((u8 *)PS2_PTR(iVar1) + 0x6ac) + 4);
  if (iVar1 == 1) {
    func_0039D7E0();
    func_001A7DC0(((u8 *)PS2_PTR(*(ps2ptr *)g_0043C55C)),0x80,1);
  }
  else if (iVar1 == 0) {
    func_0039D5C0();
  }
  return;
}

/* 0x0039EB40, 0x33C bytes. */
void func_0039EB40(int param_1)
{
    int iVar1;
    int iVar4;
    int iVar5;
    u32 * puVar6;
    unsigned long long uVar2;
    unsigned long long uVar3;

  
  iVar5 = (int)param_1 + 400;
  iVar1 = func_0039E7C0();
  func_002F3440(iVar5,0);
  func_002F3CF0(iVar5,0);
  func_002F5930(iVar5,0);
  func_002F56A0(iVar5,0);
  uVar2 = func_0039E7A0(param_1);
  func_002F5A10(iVar5,uVar2);
  uVar2 = func_0039E700(param_1);
  func_002F69F0(iVar5,uVar2);
  iVar1 = iVar1 * 0x20;
  func_002F3960(iVar5,*(u16 *)((g_00418E10 + 0x0) + iVar1));
  func_002F4BB0(iVar5,*(u16 *)((g_00418E10 + 0x2) + iVar1));
  func_002F4D40(iVar5,*(u16 *)((g_00418E10 + 0x4) + iVar1));
  func_002F4ED0(iVar5,*(u16 *)((g_00418E10 + 0x6) + iVar1));
  func_002F5060(iVar5,*(u16 *)((g_00418E10 + 0x8) + iVar1));
  func_002F51F0(iVar5,*(u16 *)((g_00418E10 + 0xA) + iVar1));
  func_002F5380(iVar5,*(u16 *)((g_00418E10 + 0xC) + iVar1));
  func_002F5510(iVar5,*(u16 *)((g_00418E10 + 0xE) + iVar1));
  func_002F5DA0(iVar5,*(u16 *)((g_00418E10 + 0x10) + iVar1));
  func_002F5EF0(iVar5,*(u16 *)((g_00418E10 + 0x12) + iVar1));
  func_002F6040(iVar5,*(u16 *)((g_00418E10 + 0x14) + iVar1));
  func_002F6190(iVar5,*(u16 *)((g_00418E10 + 0x16) + iVar1));
  func_002F62E0(iVar5,*(u16 *)((g_00418E10 + 0x18) + iVar1));
  func_002F6430(iVar5,*(u16 *)((g_00418E10 + 0x1A) + iVar1));
  func_002F6580(iVar5,*(u16 *)((g_00418E10 + 0x1C) + iVar1));
  func_002F66D0(iVar5,*(u16 *)((g_00418E10 + 0x1E) + iVar1));
  iVar1 = func_0039E720(param_1);
  iVar4 = 0;
  puVar6 = (u32 *)((g_00418FD0 + 0x0) + iVar1 * 0x20);
  do {
    func_002F6C90(iVar5,iVar4,*puVar6);
    func_002F6D80(iVar5,iVar4,puVar6[1]);
    iVar4 = iVar4 + 1;
    puVar6 = puVar6 + 2;
  } while (iVar4 < 4);
  iVar4 = 0;
  puVar6 = (u32 *)((g_00419D10 + 0x0) + iVar1 * 0x50);
  do {
    func_002F6E70(iVar5,iVar4,*puVar6);
    func_002F6F60(iVar5,iVar4,puVar6[1]);
    iVar4 = iVar4 + 1;
    puVar6 = puVar6 + 2;
  } while (iVar4 < 10);
  iVar1 = func_0039E780(param_1);
  func_002F6AD0(iVar5,iVar1 + 0x28);
  iVar1 = func_0039E780(param_1);
  func_002F6BB0(iVar5,*(u32 *)((g_0041BE30 + 0x0) + iVar1 * 4));
  iVar1 = 0;
  do {
    uVar2 = func_002F6C20(iVar5,iVar1);
    uVar3 = func_002F6D10(iVar5,iVar1);
    func_002F4820(iVar5,uVar2,uVar3);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  return;
}

/* 0x003A0220, 0x54 bytes. */
void func_003A0220(int param_1, int param_2)
{
  if ((-1 < param_1) && (param_1 < 0x75)) {
    if (param_2 != 0) {
      func_0039FBF0();
    }
    func_003A0D90();
  }
  return;
}

/* 0x003A37D0, 0x90 bytes. */
void func_003A37D0(int param_1, int param_2)
{
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

  
  uVar1 = func_003A0380();
  uVar2 = (*(u32 *)(g_00669F9C + 0x0));
  if ((int)(*(u32 *)(g_00669F9C + 0x0)) < 1) {
    uVar2 = 0;
  }
  uVar3 = (*(u32 *)(g_00669F9C + 0x4));
  if (uVar2 <= (*(u32 *)(g_00669F9C + 0x4))) {
    uVar3 = uVar2;
  }
  if ((uVar1 == 0xffffffff) || (uVar3 < uVar1)) {
    func_003A0320(param_1,param_2);
  }
  return;
}

/* 0x003A6060, 0x8C bytes. */
void func_003A6060(int *param_1, int *param_2, int param_3)
{
    int iVar1;
    int iVar2;

  
  if (((*(u32 *)(g_007BAD30 + 0x18)) < 0) || (5 < (*(u32 *)(g_007BAD30 + 0x18)))) {
    iVar2 = 6;
    iVar1 = 0x18;
  }
  else {
    iVar1 = (*(u32 *)(g_007BAD30 + 0x18)) << 2;
    iVar2 = (*(u32 *)(g_007BAD30 + 0x18));
  }
  iVar1 = (iVar1 + iVar2) * 0x28;
  iVar2 = *(int *)(param_3 * 8 + iVar1 + 0x45a0e4);
  *param_1 = (*(u32 *)(g_007BAD30 + 0x0)) + *(int *)(param_3 * 8 + iVar1 + 0x45a0e0);
  *param_2 = (*(u32 *)(g_007BAD30 + 0x4)) + iVar2;
  return;
}

/* 0x003A62E0, 0x9C bytes. */
int func_003A62E0(int param_1, int *param_2, int *param_3)
{
    int iVar1;
    int iVar3;
    u32 uVar2;

  
  uVar2 = 1;
  if (((*(u32 *)(g_007BAD30 + 0x18)) < 0) || (iVar3 = (*(u32 *)(g_007BAD30 + 0x18)), 5 < (*(u32 *)(g_007BAD30 + 0x18)))) {
    iVar3 = 6;
  }
  iVar1 = *(int *)(param_1 * 8 + iVar3 * 0x38 + 0x45a6a0);
  iVar3 = *(int *)(param_1 * 8 + iVar3 * 0x38 + 0x45a6a4);
  *param_2 = (*(u32 *)(g_007BAD30 + 0x0)) + iVar1;
  *param_3 = (*(u32 *)(g_007BAD30 + 0x4)) + iVar3;
  if ((iVar1 == -1) && (iVar3 == -1)) {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x003A70D0, 0x288 bytes. */
void func_003A70D0(void)
{
    int iStack_10;
    int iStack_4;
    int iStack_8;
    int iStack_c;
    int * piVar3;
    u32 uVar1;
    u32 uVar2;

  
  uVar2 = (*(u32 *)(g_007BACB4 + 0x8));
  uVar1 = (*(u32 *)(g_007BACB4 + 0x4));
  if ((*(u32 *)(g_007BACB4 + 0x0)) != -1) {
    piVar3 = (int *)((((*(u32 *)(g_007BACB4 + 0x0)) / 5) % 0x14) * 0x28 + ((*(u32 *)(g_007BACB4 + 0xC)) != 0 ^ 1) * 800 + 0x45ada0);
    func_003A6060(&iStack_4,&iStack_8,(*(u32 *)(g_007BACB4 + 0x4)));
    func_003A6060(&iStack_c,&iStack_10,uVar2);
    if (piVar3[8] != -1) {
      func_001ABE40((*(u32 *)(g_007BACB4 + 0x10)),9,iStack_c,iStack_10,0,0x18,0x18,piVar3[9]);
    }
    if (*piVar3 != -1) {
      func_001ABEA0((*(u32 *)(g_007BACB4 + 0x10)),10,iStack_4 + -0x1a,iStack_8 + -0x14,0,0x48,0x48,0);
    }
    if (piVar3[2] != -1) {
      func_001ABEA0((*(u32 *)(g_007BACB4 + 0x10)),0xb,iStack_c + -0x13,iStack_10 + -0xf,0,0x38,0x38,0);
    }
    if (piVar3[4] != -1) {
      func_001ABEA0((*(u32 *)(g_007BACB4 + 0x10)),0xc,iStack_c + -7,iStack_10 + -7,0,0x28,0x28,0);
    }
    if (piVar3[6] != -1) {
      func_003A64A0(uVar1,uVar2,piVar3[6],piVar3[7]);
    }
  }
  return;
}

/* 0x003A8130, 0x110 bytes. */
void func_003A8130(int *param_1, int *param_2, int *param_3)
{
    int iVar1;
    int iVar2;

  
  iVar2 = (*(u32 *)(g_0045B4F0 + 0x8));
  iVar1 = (*(u32 *)(g_0045B4F0 + 0x4));
  if ((*(u32 *)(g_007BAD58 + 0x0)) < 0x20) {
    *param_1 = *param_1 + ((*(u32 *)(g_007BAD58 + 0x0)) * ((*(u32 *)(g_0045B4F0 + 0x0)) - *param_1) >> 5);
    *param_2 = *param_2 + ((*(u32 *)(g_007BAD58 + 0x0)) * (iVar1 - *param_2) >> 5);
    *param_3 = *param_3 + ((*(u32 *)(g_007BAD58 + 0x0)) * (iVar2 - *param_3) >> 5);
  }
  else {
    *param_1 = *param_1 + ((0x40 - (*(u32 *)(g_007BAD58 + 0x0))) * ((*(u32 *)(g_0045B4F0 + 0x0)) - *param_1) >> 5);
    *param_2 = *param_2 + ((0x40 - (*(u32 *)(g_007BAD58 + 0x0))) * (iVar1 - *param_2) >> 5);
    *param_3 = *param_3 + ((0x40 - (*(u32 *)(g_007BAD58 + 0x0))) * (iVar2 - *param_3) >> 5);
  }
  return;
}

/* 0x003AAF80, 0x25C bytes. */
int func_003AAF80(int param_1, int param_2, int param_3)
{
    u8 * iVar1;
    int iVar4;
    int iVar5;
    int iVar7;
    int iVar8;
    int iVar9;
    long long lVar3;
    u8 * pbVar6;
    unsigned long long uVar2;

  
  iVar1 = func_0021A630();
  iVar8 = 7;
  iVar9 = (int)param_2;
  iVar7 = iVar9 * 7;
  if (param_1 == 0) {
    uVar2 = func_002F4080(*(u32 *)(param_3 * 4 + iVar1 + 0x1674));
    lVar3 = func_002FB3B0(uVar2);
    iVar5 = iVar7 + 7;
    if (iVar7 < iVar5) {
      pbVar6 = (g_0041C020 + 0x0) + iVar7;
      do {
        if (((unsigned long long)*pbVar6 != 0) && (lVar3 <= (long long)(unsigned long long)*pbVar6)) {
          iVar8 = iVar7 + iVar9 * -7;
          break;
        }
        iVar7 = iVar7 + 1;
        pbVar6 = pbVar6 + 1;
      } while (iVar7 < iVar5);
    }
  }
  else if (param_1 == 1) {
    iVar5 = func_002F41E0(*(u32 *)(param_3 * 4 + iVar1 + 0x1674));
    iVar4 = iVar7 + 7;
    if (iVar7 < iVar4) {
      pbVar6 = (g_0041C020 + 0x30) + iVar7;
      do {
        if ((*pbVar6 != 0) && (iVar5 + 1 <= (int)(u32)*pbVar6)) {
          iVar8 = iVar7 + iVar9 * -7;
          break;
        }
        iVar7 = iVar7 + 1;
        pbVar6 = pbVar6 + 1;
      } while (iVar7 < iVar4);
    }
  }
  if (*(int *)(iVar1 + 0x1664) == 0) {
    if (iVar8 + -1 < 7) {
      iVar8 = iVar8 + -1;
      if (iVar8 < 1) {
        iVar8 = 0;
      }
    }
    else {
      iVar8 = 6;
    }
  }
  if (((param_1 == 1) && (lVar3 = func_00362B60(3), lVar3 != 0)) && (*(int *)(iVar1 + 0x1664) != 0))
  {
    if (param_2 == 4) {
      if (iVar8 + 1 < 7) {
        iVar8 = iVar8 + 1;
        if (iVar8 < 1) {
          iVar8 = 0;
        }
      }
      else {
        iVar8 = 6;
      }
      return iVar8;
    }
    if (iVar8 + 1 < 6) {
      iVar8 = iVar8 + 1;
      if (iVar8 < 1) {
        iVar8 = 0;
      }
    }
    else {
      iVar8 = 5;
    }
  }
  return iVar8;
}

/* 0x003AEB80, 0xE0 bytes. */
int func_003AEB80(void)
{
    long long lVar1;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;

  
  lVar1 = func_00375B90();
  if (lVar1 == 4) {
    func_003DB480(0xd,2);
  }
  else if (lVar1 == 1) {
    (*(u32 *)(g_007BAE7C + 0x0)) = (*(u32 *)(g_007BAE7C + 0x0)) + 1;
    if ((*(u32 *)(g_007BAE7C + 0x0)) < (*(u32 *)(g_007BAE7C + 0x4))) {
      func_003AE8E0(0);
    }
    else {
      (*(u32 *)(g_007BAE7C + 0x0)) = 0;
      func_00388200(5,0);
      func_003AE8E0(2);
      uStack_20 = 0x10;
      uStack_1c = 0xd6;
      uStack_18 = 0xa2;
      uStack_14 = 0x20;
      uStack_10 = 0x80;
      func_003DC090(9,&uStack_20);
      func_003DC0E0(9,1,2);
    }
  }
  return 2;
}

/* 0x003AF960, 0x8C bytes. */
void func_003AF960(void)
{
    int uVar1;

  
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  if ((uVar1 & 0x10) != 0) {
    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
    func_003AE8E0(2);
  }
  return;
}

/* 0x003BFDF0, 0x26C bytes. */
int func_003BFDF0(void)
{
    int uVar1;
    int uVar2;

  
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
  if ((uVar1 & 0x40) == 0) {
    if ((uVar1 & 0x10) != 0) {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      return 0;
    }
  }
  else {
    if ((*(u32 *)(g_007BEAD4 + 0x4)) == 0) {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      return 1;
    }
    if (*(int *)((*(u32 *)(g_007BEAD4 + 0x0)) * 0x44 + 0x7beadc) != 0) {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      return 1;
    }
    func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
  }
  if ((uVar2 & 0x4000) == 0) {
    if ((uVar2 & 0x1000) != 0) {
      if ((*(u32 *)(g_007BEAD4 + 0x0)) < 1) {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        (*(u32 *)(g_007BEAD4 + 0x0)) = 2;
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        (*(u32 *)(g_007BEAD4 + 0x0)) = (*(u32 *)(g_007BEAD4 + 0x0)) + -1;
      }
    }
  }
  else if ((*(u32 *)(g_007BEAD4 + 0x0)) < 2) {
    (*(u32 *)(g_007BEAD4 + 0x0)) = (*(u32 *)(g_007BEAD4 + 0x0)) + 1;
    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
  }
  else {
    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
    (*(u32 *)(g_007BEAD4 + 0x0)) = 0;
  }
  return 2;
}

/* 0x003D47A0, 0x4C8 bytes. */
void func_003D47A0(int param_1, int param_2, int param_3, int param_4)
{
    int iVar10;
    int iVar11;
    int iVar5;
    int iVar7;
    int iVar8;
    int iVar9;
    int uVar1;
    u32 uVar12;
    int uVar2;
    int uVar3;
    int uVar4;
    unsigned long long uVar6;

  
  iVar5 = PS2_ADDR(func_003766C0());
  iVar7 = iVar5 + param_1 * 0x38;
  if (*(char *)((u8 *)PS2_PTR(iVar7) + 0xbc) != '\0') {
    iVar5 = iVar5 + param_1 * 0x48;
    uVar3 = *(u16 *)((u8 *)PS2_PTR(iVar5) + 0x4b4);
    uVar4 = *(u16 *)((u8 *)PS2_PTR(iVar5) + 0x4b2);
    uVar1 = *(u8 *)((u8 *)PS2_PTR(iVar5) + 0x4b6);
    uVar2 = *(u8 *)((u8 *)PS2_PTR(iVar5) + 0x4b7);
    func_002C7310(param_2,param_3,0,0xec,0xd1,param_4,1);
    iVar11 = (int)param_2;
    iVar8 = (int)param_3;
    func_003D3CD0(iVar7 + 0xbd,iVar7 + 0xc6,iVar11 + 0x11,iVar8 + 0x1d,1,0x14,6);
    func_003D3B50(iVar11 + 0xa4,iVar8 + 4,1,0x40,0x40,*(u8 *)((u8 *)PS2_PTR(iVar7) + 0xea));
    iVar5 = iVar11 + 0x11;
    iVar10 = iVar8 + 0x35;
    iVar9 = 0;
    do {
      uVar6 = PS2_ADDR(func_00376810());
      func_001ABEA0(uVar6,0x32,iVar5,iVar10,0,0x48,0x10,0);
      iVar9 = iVar9 + 1;
      iVar10 = iVar10 + 0x12;
    } while (iVar9 < 3);
    iVar10 = iVar8 + 0x71;
    iVar9 = 0;
    do {
      uVar6 = PS2_ADDR(func_00376810());
      func_001ABEA0(uVar6,0x2f,iVar5,iVar10,0,0x38,0x10,0);
      iVar9 = iVar9 + 1;
      iVar10 = iVar10 + 0x12;
    } while (iVar9 < 4);
    func_003B55E0(iVar5,iVar10,0,1);
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    iVar5 = iVar11 + 0x65;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    uVar6 = PS2_ADDR(func_00372DD0(*(u32 *)((u8 *)PS2_PTR(iVar7) + 0xe0)));
    func_00146270(uVar6,iVar5,iVar8 + 0x35,1,0);
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
    uVar6 = PS2_ADDR(func_00376810());
    func_001ABEA0(uVar6,0x33,iVar5,iVar8 + 0x45,0,0x70,0x14,0);
    uVar6 = PS2_ADDR(func_00376810());
    func_001ABEA0(uVar6,0x34,iVar11 + 0x79,iVar8 + 0x46,0,0x48,0x10,0);
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    uVar6 = PS2_ADDR(func_00372DF0(*(u8 *)((u8 *)PS2_PTR(iVar7) + 0xe9)));
    func_00146270(uVar6,iVar5,iVar8 + 0x59,1,0);
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
    uVar12 = func_003D3E40(uVar4,0);
    func_001A85D0(uVar12,0,1.0f,iVar5,iVar8 + 0x75,0,0xd,0,0x60,1);
    uVar12 = func_003D3E40(uVar3,1);
    func_001A85D0(uVar12,0,1.0f,iVar5,iVar8 + 0x87,0,0xe,0,0x60,1);
    uVar12 = func_003D3E40(uVar1,2);
    func_001A85D0(uVar12,0,1.0f,iVar5,iVar8 + 0x99,0,0xf,0,0x60,1);
    uVar12 = func_003D3E40(uVar2,3);
    func_001A85D0(uVar12,0,1.0f,iVar5,iVar8 + 0xab,0,0x10,0,0x60,1);
    func_003B5300(*(u8 *)((u8 *)PS2_PTR(iVar7) + 0xe8),iVar11 + 100,iVar8 + 0xb7,0,1);
  }
  return;
}

/* 0x003E4F40, 0x628 bytes. */
int func_003E4F40(void)
{
    long long lVar5;
    u32 * puVar3;
    int sVar1;
    int sVar6;
    int uVar2;
    u32 uVar4;

  
  puVar3 = (u32 *)func_003E46F0();
  sVar1 = *(short *)((int)puVar3 + *puVar3 * 2 + 8);
  lVar5 = func_003E46B0();
  if (lVar5 != 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar2 & 0x8000) != 0) {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      uVar4 = *puVar3 + 1 & 1;
      if (((int)(*puVar3 + 1) < 0) && (uVar4 != 0)) {
        uVar4 = uVar4 - 2;
      }
      *puVar3 = uVar4;
      *(u16 *)(puVar3 + 3) = 0;
      *(u16 *)((int)puVar3 + 0xe) = 0;
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar2 & 0x2000) != 0) {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      uVar4 = *puVar3 + 1 & 1;
      if (((int)(*puVar3 + 1) < 0) && (uVar4 != 0)) {
        uVar4 = uVar4 - 2;
      }
      *puVar3 = uVar4;
      *(u16 *)(puVar3 + 3) = 0;
      *(u16 *)((int)puVar3 + 0xe) = 0;
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar2 & 0x1000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar2 = 0;
      }
      else {
        uVar2 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar2 & 0x4000) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar2 = 0;
        }
        else {
          uVar2 = (*(u16 *)(g_0050074C + 0x2));
        }
        if ((uVar2 & 0x1000) == 0) {
          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
            uVar2 = 0;
          }
          else {
            uVar2 = (*(u16 *)(g_0050074C + 0x2));
          }
          if ((uVar2 & 0x4000) == 0) {
            if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
              uVar2 = 0;
            }
            else {
              uVar2 = (*(u16 *)(g_0050074C + 0x0));
            }
            if ((uVar2 & 0x40) == 0) {
              if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                uVar2 = 0;
              }
              else {
                uVar2 = (*(u16 *)(g_0050074C + 0x0));
              }
              if ((uVar2 & 0x10) != 0) {
                func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                puVar3[4] = 4;
              }
            }
            else {
              func_003E4BE0();
              func_0017E010(0x1c);
            }
          }
          else if ((int)*(short *)((int)puVar3 + 0xe) + (int)(short)puVar3[3] < sVar1 + -1) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            sVar6 = (short)puVar3[3] + 1;
            *(short *)(puVar3 + 3) = sVar6;
            if ((5 < (long long)sVar6) || ((long long)sVar1 <= (long long)sVar6)) {
              if ((long long)((int)*(short *)((int)puVar3 + 0xe) + (int)sVar6) < (long long)sVar1) {
                *(short *)(puVar3 + 3) = (short)puVar3[3] + -1;
                *(short *)((int)puVar3 + 0xe) = *(short *)((int)puVar3 + 0xe) + 1;
              }
              else {
                *(u16 *)(puVar3 + 3) = 0;
                *(u16 *)((int)puVar3 + 0xe) = 0;
              }
            }
          }
        }
        else if (0 < (int)(short)puVar3[3] + (int)*(short *)((int)puVar3 + 0xe)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          uVar4 = puVar3[3];
          sVar6 = (short)uVar4 + -1;
          *(short *)(puVar3 + 3) = sVar6;
          if (sVar6 < 0) {
            if (*(short *)((int)puVar3 + 0xe) < 1) {
              if ((int)sVar1 / 6 < 1) {
                *(short *)(puVar3 + 3) = sVar1 % 6 + -1;
                *(u16 *)((int)puVar3 + 0xe) = 0;
              }
              else {
                *(u16 *)(puVar3 + 3) = 5;
                *(short *)((int)puVar3 + 0xe) = sVar1 + -6;
              }
            }
            else {
              *(short *)(puVar3 + 3) = (short)uVar4;
              *(short *)((int)puVar3 + 0xe) = *(short *)((int)puVar3 + 0xe) + -1;
            }
          }
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        sVar6 = (short)puVar3[3] + 1;
        *(short *)(puVar3 + 3) = sVar6;
        if ((5 < sVar6) || (sVar1 <= sVar6)) {
          if ((long long)((int)*(short *)((int)puVar3 + 0xe) + (int)sVar6) < (long long)sVar1) {
            *(short *)(puVar3 + 3) = (short)puVar3[3] + -1;
            *(short *)((int)puVar3 + 0xe) = *(short *)((int)puVar3 + 0xe) + 1;
          }
          else {
            *(u16 *)(puVar3 + 3) = 0;
            *(u16 *)((int)puVar3 + 0xe) = 0;
          }
        }
      }
    }
    else {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      uVar4 = puVar3[3];
      sVar6 = (short)uVar4 + -1;
      *(short *)(puVar3 + 3) = sVar6;
      if (sVar6 < 0) {
        if (*(short *)((int)puVar3 + 0xe) < 1) {
          if ((int)sVar1 / 6 < 1) {
            *(short *)(puVar3 + 3) = sVar1 % 6 + -1;
            *(u16 *)((int)puVar3 + 0xe) = 0;
          }
          else {
            *(u16 *)(puVar3 + 3) = 5;
            *(short *)((int)puVar3 + 0xe) = sVar1 + -6;
          }
        }
        else {
          *(short *)(puVar3 + 3) = (short)uVar4;
          *(short *)((int)puVar3 + 0xe) = *(short *)((int)puVar3 + 0xe) + -1;
        }
      }
    }
  }
  return 0;
}

/* 0x003EEAE0, 0x2F0 bytes. */
void func_003EEAE0(void)
{
    int iVar1;
    u8 * iVar4;
    int iVar5;
    long long lVar6;
    int uVar2;
    int uVar3;

  
  iVar4 = func_002FC2C0();
  iVar4 = (u8 *)PS2_PTR(*(int *)(iVar4 + 0x6ac));
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = (*(u16 *)(g_0050074C + 0x2));
  }
  lVar6 = func_003EE4A0();
  if ((uVar2 & 0x10) == 0) {
    iVar5 = (int)lVar6;
    if ((uVar2 & 0x1000) == 0) {
      if ((uVar2 & 0x4000) == 0) {
        if ((uVar3 & 0x1000) == 0) {
          if (((uVar3 & 0x4000) != 0) && (lVar6 != 1)) {
            iVar1 = *(int *)(iVar4 + 8);
            if ((iVar1 < iVar5 + -1) && (iVar1 != iVar5 + -1)) {
              *(int *)(iVar4 + 8) = iVar1 + 1;
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            }
          }
        }
        else if (((lVar6 != 1) && (iVar5 = *(int *)(iVar4 + 8), 0 < iVar5)) && (iVar5 != 0)) {
          *(int *)(iVar4 + 8) = iVar5 + -1;
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        }
      }
      else if (lVar6 != 1) {
        if (*(int *)(iVar4 + 8) == iVar5 + -1) {
          if ((uVar2 & 0x4000) != 0) {
            *(u32 *)(iVar4 + 8) = 0;
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          }
        }
        else {
          *(int *)(iVar4 + 8) = *(int *)(iVar4 + 8) + 1;
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        }
      }
    }
    else if (lVar6 != 1) {
      if (*(int *)(iVar4 + 8) == 0) {
        if ((uVar2 & 0x1000) != 0) {
          *(int *)(iVar4 + 8) = iVar5 + -1;
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        }
      }
      else {
        *(int *)(iVar4 + 8) = *(int *)(iVar4 + 8) + -1;
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      }
    }
  }
  else {
    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
    *(u32 *)(iVar4 + 8) = 0xffffffff;
    *(u32 *)(iVar4 + 4) = 0;
  }
  return;
}

/* 0x003F0A00, 0x2D8 bytes. */
int func_003F0A00(u8 *param_1)
{
    u8 auStack_1d[29];
    u8 auStack_22[5];
    int bStack_23;
    int bVar1;
    int cStack_2c;
    int iVar10;
    u8 * iVar11;
    int iVar6;
    u8 * iVar8;
    int iVar9;
    long long lVar4;
    u32 * puVar7;
    int uStack_24;
    int uStack_25;
    int uStack_26;
    int uStack_27;
    int uStack_28;
    int uStack_29;
    int uStack_2a;
    int uStack_2b;
    u32 uStack_30;
    u32 uStack_40;
    u32 uStack_44;
    u32 uStack_48;
    u32 uStack_4c;
    u32 uStack_50;
    int uVar2;
    unsigned long long uVar3;
    u32 uVar5;

  
  iVar10 = 0;
  *(u32 *)(param_1 + 0x140) = 0;
  iVar8 = param_1;
  iVar11 = param_1;
  do {
    *(u32 *)(iVar8 + 0x120) = 0;
    func_00118850(iVar11,0x24);
    if (iVar10 < 4) {
      uVar3 = PS2_ADDR(func_0019FBC0(iVar10));
      func_00118AC0(&uStack_30,uVar3,0x24);
      if (cStack_2c != '\x04') {
        iVar9 = *(int *)(param_1 + 0x140);
        *(int *)(param_1 + 0x140) = iVar9 + 1;
        func_00118AC0(param_1 + iVar9 * 0x24,&uStack_30,0x24);
      }
    }
    else {
      iVar9 = iVar10 + -4;
      lVar4 = func_003A1FC0(iVar9);
      if (lVar4 != 4) {
        uStack_30 = func_003A2290(iVar9);
        cStack_2c = func_003A1FC0(iVar9);
        uStack_2b = func_003A20D0(iVar9);
        uStack_2a = func_003A2150(iVar9);
        uStack_29 = func_003A21D0(iVar9);
        uStack_28 = func_003A2320(iVar9);
        uStack_27 = func_003A23A0(iVar9);
        uStack_26 = func_003A2500(iVar9);
        uStack_25 = func_003A2580(iVar9);
        uStack_24 = func_003A2600(iVar9);
        uVar3 = PS2_ADDR(func_003A2050(iVar9));
        func_00120928(auStack_1d,uVar3);
        bStack_23 = 0;
        uVar5 = 0;
        do {
          lVar4 = func_003A26E0(iVar9,uVar5);
          if (lVar4 == 0) {
            bVar1 = 0;
          }
          else {
            bVar1 = (u8)(1 << (uVar5 & 0x1f));
          }
          uVar5 = uVar5 + 1;
          bStack_23 = bStack_23 | bVar1;
        } while ((int)uVar5 < 4);
        iVar6 = 0;
        puVar7 = &uStack_30;
        do {
          uVar2 = func_003A2450(iVar9,iVar6);
          *(u8 *)((int)puVar7 + 0xe) = uVar2;
          iVar6 = iVar6 + 1;
          puVar7 = (u32 *)((int)puVar7 + 1);
        } while (iVar6 < 5);
        *(u32 *)(param_1 + *(int *)(param_1 + 0x140) * 4 + 0x120) = 1;
        iVar9 = *(int *)(param_1 + 0x140);
        *(int *)(param_1 + 0x140) = iVar9 + 1;
        func_00118AC0(param_1 + iVar9 * 0x24,&uStack_30,0x24);
      }
    }
    iVar10 = iVar10 + 1;
    iVar8 = iVar8 + 4;
    iVar11 = iVar11 + 0x24;
  } while (iVar10 < 8);
  if (0 < *(int *)(param_1 + 0x140)) {
    uStack_50 = 8;
    uStack_4c = 0x50;
    uStack_48 = 0x118;
    uStack_44 = 0x18;
    uStack_40 = 0x80;
    func_003DC090(0xd,&uStack_50);
    func_003DC0E0(0xd,1,*(u32 *)(param_1 + 0x140));
    uStack_50 = 0x124;
    uStack_4c = 0x4e;
    uStack_48 = 0xd8;
    uStack_44 = 0xd0;
    uStack_40 = 0x80;
    func_003DC090(0xe,&uStack_50);
    func_003DC0E0(0xe,2,1);
  }
  return *(u32 *)(param_1 + 0x140);
}

/* 0x003F0EC0, 0x100 bytes. */
void func_003F0EC0(int param_1, int param_2, u8 *param_3)
{
    u32 auStack_20[8];
    int iVar1;
    u8 * iVar2;
    int iVar3;
    int iVar4;

  
  iVar2 = param_3;
  iVar1 = *(int *)(iVar2 + 0x140);
  iVar4 = 0;
  if (0 < iVar1) {
    iVar3 = 0x50;
    do {
      func_003DC180(0xd,iVar4,auStack_20);
      func_003F0CE0(param_1,param_2,param_3,auStack_20[0],iVar3,1,iVar4);
      iVar1 = *(int *)(iVar2 + 0x140);
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x18;
    } while (iVar4 < iVar1);
  }
  if (*(int *)(iVar2 + 0x144) < iVar1) {
    func_003DC180(0xe,iVar4,auStack_20);
    func_002D07E0(param_1,param_2,0,auStack_20[0],0x4e,1,0,0);
  }
  return;
}
