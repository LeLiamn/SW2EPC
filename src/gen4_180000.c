/*
 * gen4_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_0076EC40[0x18];
extern u8 g_007B4E60[0x18];
extern u8 g_007B9A30[0x18];
#include "sw2e_mem.h"

#define true 1
#define false 0

extern u8 g_0041D028[0xC];
extern u8 g_0045D730[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_0056CCA4[0x24];
extern u8 g_0056CCC0[0xC];
extern u8 g_005B4D80[0x68];
extern u8 g_00669DB8[0x20];
extern u8 g_00669F60[0x4];
extern u8 g_00669F98[0x1C];
extern u8 g_00693970[0x10];
extern u8 g_0076EC60[0x20];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007732B0[0x10];
extern u8 g_007B99F0[0x40];
extern u8 g_007B9F30[0x10];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D374;   /* (small data) */
extern int g_0045D460;   /* (small data) */
extern int g_0045D478;   /* (small data) */
extern int g_0045D47C;   /* (small data) */
extern int g_0045D480;   /* (small data) */
extern int g_0045D484;   /* (small data) */
extern int g_0045D488;   /* (small data) */
extern int g_0045D48C;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */
extern u32 g_70000D60;   /* (scratchpad) */

int func_00114240();
int func_00114410();
int func_00114C90();
int func_001204B0();
int func_00146270();
int func_00146D80();
int func_00147160();
int func_001477C0();
int func_001479C0();
int func_00190590();
int func_00190D60();
int func_001A3460();
int func_001ABE40();
int func_001EE570();
int func_00215790();
int func_0022DD60();
int func_0023AA40();
int func_0023AC70();
int func_0023ACC0();
int func_0023AD10();
int func_00254330();
int func_00255430();
int func_0029A5C0();
int func_0029CFB0();
int func_0029D000();
int func_002A9D10();
int func_002C7310();
int func_002C80A0();
int func_002C8500();
int func_002CE160();
int func_002EA600();
int func_002EA950();
int func_002F2840();
int func_002F3B30();
int func_002F3CF0();
int func_002F3E70();
int func_002F3F70();
int func_002F4080();
int func_002F5BE0();
int func_002F5CC0();
int func_002F7610();
int func_002F7B20();
int func_002FA790();
int func_002FB2A0();
int func_002FB2D0();
int func_0030A030();
int func_0030AB90();
int func_0030AF20();
int func_0030AFF0();
int func_0030C280();
int func_0030C320();
int func_0030C3C0();
int func_0030D7D0();
int func_00323840();
int func_00323F10();
int func_00327820();
int func_00327C00();
int func_00327C70();
int func_00327C80();
int func_003282F0();
int func_00328330();
int func_00329540();
int func_0032EB40();
int func_0032EE10();
int func_003303B0();
int func_00337A10();
int func_0035D210();
int func_0035D5B0();
int func_0035F440();
int func_00362160();
int func_00362570();
int func_003635F0();
int func_0036B260();
int func_0036F1E0();
int func_00374EE0();
int func_00375B90();
int func_00380E80();
void func_00380EB0(float, int, int, int, int, int);
int func_00389D60();
int func_00390760();
void *func_00391250();
int func_00393680();
int func_00393D30();
int func_00394100();
int func_00394740();
int func_00394960();
int func_003A7D90();
int func_003A7ED0();
int func_003A90E0();
int func_003A9170();
int func_003A93B0();
int func_003A9440();
int func_003A9460();
int func_003B3A60();
int func_003B5660();
int func_003B5820();
int func_003C0C60();
int func_003C1850();
int func_003DB900();
int func_003E1F60();
int func_003E2000();
int func_003E2EF0();
int func_003E3990();
int func_003E9460();
int func_003E9690();
int func_003E9750();
int func_003F1A30();
int func_003F1B50();
int func_003F1D40();
int func_003F1F10();
void func_001E95F0(int *param_1, int param_2, int param_3, int param_4, int param_5);
void func_001EE4A0(int param_1);
void func_001F0960(float *param_1, float *param_2, float *param_3);
void func_00216990(void);
void func_00255D00(u8 *param_1);
void func_00255E00(void);
void func_00278FC0(int param_1, u16 *param_2, int param_3);
void func_0029A610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_0029FB30(u8 *param_1);
void func_002A6040(void);
void func_002A62D0(void);
void func_002A6FF0(u8 *param_1, int param_2);
void func_002A73F0(u8 *param_1, int param_2);
void func_002A9EC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002D8CA0(u8 *param_1);
void func_002E63B0(u8 *param_1);
void func_002EB0F0(void);
int func_00323CD0(int param_1, int param_2, int param_3, int *param_4);
int func_003251B0(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_00328470(void);
int func_00333A40(void);
int func_00334000(void);
int func_0036BB80(int param_1);
void func_003752D0(void);
int func_0038A550(u8 *param_1);
void func_0038B830(u8 *param_1);
int func_003955A0(int param_1);
void func_003E2C60(int param_1);
int func_003F2030(void);

/* 0x001E95F0, 0xDC bytes, matching. */
void func_001E95F0(int *param_1, int param_2, int param_3, int param_4, int param_5)
{
    u8 auStack_100[256];

  
  (*(u8 *)(g_0056CCC0 + 0x8)) = param_4;
  (*(u8 *)(g_0056CCC0 + 0x9)) = param_4;
  (*(u8 *)(g_0056CCC0 + 0xA)) = param_4;
  (*(u8 *)(g_0056CCC0 + 0xB)) = param_4;
  param_1[2] = param_5;
  if (*param_1 != 0) {
    func_00147160(*param_1,auStack_100,0x1b8,0,0);
    (*(u32 *)(g_0056CCC0 + 0x0)) = 0x41a00000;
    (*(u32 *)(g_0056CCC0 + 0x4)) = 0x41a00000;
    func_00146270(auStack_100,param_2,param_3,2,param_1 + 2);
  }
  (*(u32 *)(g_0056CCC0 + 0x0)) = 0x41800000;
  (*(u32 *)(g_0056CCC0 + 0x4)) = 0x41800000;
  (*(u8 *)(g_0056CCC0 + 0x8)) = 0x80;
  (*(u8 *)(g_0056CCC0 + 0x9)) = 0x80;
  (*(u8 *)(g_0056CCC0 + 0xA)) = 0x80;
  (*(u8 *)(g_0056CCC0 + 0xB)) = 0x80;
  return;
}

/* 0x001EE4A0, 0xC8 bytes. */
void func_001EE4A0(int param_1)
{
    int bVar2;
    u8 * iVar3;
    u32 uVar1;
    u32 uVar4;

  
  uVar4 = 0;
  iVar3 = g_00693970;
  do {
    uVar1 = *(u32 *)(iVar3 + 0x80);
    bVar2 = false;
    if (((uVar1 & 1) != 0) && ((uVar1 & 0x8c40002) == 0)) {
      bVar2 = true;
    }
    if ((bVar2) && ((uVar1 & 0x30) == 0)) {
      if (param_1 == 0) {
        if (*(char *)(iVar3 + 0x79) != '\0') goto LAB_001ee538;
      }
      else if (*(char *)(iVar3 + 0x79) == '\0') {
LAB_001ee538:
        func_001EE570(iVar3);
      }
    }
    uVar4 = uVar4 + 1;
    iVar3 = iVar3 + 0x88;
    if (0x1ac < uVar4) {
      return;
    }
  } while( true );
}

/* 0x001F0960, 0x2E4 bytes. */
void func_001F0960(float *param_1, float *param_2, float *param_3)
{
    float fVar3;
    int iVar2;
    int lVar1;
    int uStack_3;
    int uStack_4;

  
  if ((0.0 < *param_1) && (0.0 < param_1[1])) {
    uStack_4 = (u8)((int)*param_1 / 5000);
    uStack_3 = (u8)((int)param_1[1] / 5000);
    lVar1 = func_00190590(&uStack_4,0x80);
    if (lVar1 != 0) {
      if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
        iVar2 = *(int *)(((*(u32 *)(g_00669F98 + 0x0)) % 5) * 4 + 0x669dd4);
      }
      else {
        iVar2 = (*(u32 *)(g_00669DB8 + 0x1C));
      }
      if (iVar2 == 6) {
        *param_2 = 27500.0;
        *param_3 = 32500.0;
        return;
      }
      if (iVar2 == 5) {
        *param_2 = 77500.0;
        *param_3 = 37500.0;
        return;
      }
      if (iVar2 == 3) {
        *param_2 = 42500.0;
        *param_3 = 52500.0;
        return;
      }
      if (iVar2 == 2) {
        *param_2 = 35000.0;
        *param_3 = 40000.0;
        lVar1 = func_00190D60(&uStack_4);
        if (lVar1 != 0) {
          if (10000.0 < param_1[1]) {
            return;
          }
          *param_3 = *param_3 - 12500.0;
          return;
        }
        if (30000.0 < param_1[1]) {
          return;
        }
        *param_3 = *param_3 - 12500.0;
        return;
      }
      if (iVar2 == 1) {
        *param_2 = 45000.0;
        *param_3 = 62500.0;
        if ((*(char *)(g_00669F98 + 0x1B)) == '\0') {
          lVar1 = func_00190D60(&uStack_4);
          if (lVar1 != 0) {
            return;
          }
          if (50000.0 < param_1[1]) {
            return;
          }
        }
        *param_3 = *param_3 - 15000.0;
        return;
      }
      fVar3 = *param_1;
      goto LAB_001f0c20;
    }
  }
  fVar3 = *param_1;
LAB_001f0c20:
  *param_2 = fVar3;
  *param_3 = param_1[1];
  return;
}

/* 0x00216990, 0x1AC bytes. */
void func_00216990(void)
{
    int iVar1;
    u32 * puVar2;
    u32 * puVar3;
    u32 * puVar4;
    u32 * puVar5;
    u32 * puVar6;
    u32 uVar7;

  
  uVar7 = 0;
  puVar6 = (u32 *)0x73f8f0;
  puVar5 = (u32 *)0x73e160;
  puVar4 = (u32 *)0x73e0e0;
  puVar3 = (u32 *)0x7404b0;
  puVar2 = (u32 *)0x740430;
  do {
    *puVar6 = 0;
    uVar7 = uVar7 + 1;
    puVar6[1] = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    puVar6[0x78] = 0;
    puVar6[0x79] = 0;
    puVar6[0x7a] = 0;
    puVar6[0x7b] = 0;
    puVar6[0xf0] = 0;
    puVar6[0xf1] = 0;
    puVar6[0xf2] = 0;
    puVar6[0xf3] = 0;
    puVar6[0x168] = 0;
    puVar6[0x169] = 0;
    puVar6[0x16a] = 0;
    puVar6[0x16b] = 0;
    puVar6[0x1e0] = 0;
    puVar6[0x1e1] = 0;
    puVar6[0x1e2] = 0;
    puVar6[0x1e3] = 0;
    puVar6[600] = 0;
    puVar6[0x259] = 0;
    puVar6[0x25a] = 0;
    puVar6[0x25b] = 0;
    *puVar5 = 0x3f800000;
    puVar6 = puVar6 + 4;
    *puVar4 = 0;
    puVar5 = puVar5 + 1;
    *puVar3 = 0;
    puVar4 = puVar4 + 1;
    *puVar2 = 1;
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
  } while (uVar7 < 0x1e);
  g_0045D480 = 3;
  g_0045D484 = 3;
  g_0045D478 = 0;
  g_0045D47C = 0;
  if ((*(u32 *)(g_00669DB8 + 0x0)) - 2U < 2) {
    g_0045D488 = 0;
    iVar1 = 0;
  }
  else {
    if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
      iVar1 = *(int *)(((*(u32 *)(g_00669F98 + 0x0)) % 5) * 4 + 0x669dc0);
    }
    else {
      iVar1 = (*(u32 *)(g_00669DB8 + 0x8));
    }
    if ((iVar1 == 5) || (iVar1 == 4)) {
      iVar1 = 1;
      g_0045D488 = 1;
    }
    else {
      g_0045D488 = 0;
      iVar1 = 0;
    }
  }
  (*(u32 *)(g_00669F98 + 0xC)) = *(u32 *)(iVar1 * 0x70 + g_0045D460 + 0xa0);
  g_0045D48C = (*(u32 *)(g_00669F98 + 0xC));
  func_00215790();
  return;
}

/* 0x00255D00, 0xF8 bytes. */
void func_00255D00(u8 *param_1)
{
    int iVar1;

  
  iVar1 = *(int *)(param_1 + 0x38);
  func_00255430();
  *(u32 *)(param_1 + 0x20) = 0x428c0000;
  func_001477C0(param_1 + 0x70);
  func_001479C0(*(int *)(param_1 + 0x48) + *(int *)(*(int *)(param_1 + 0x48) + 0xc),param_1 + 0x70);
  (*(u32 *)(g_0076EC60 + 0x0)) = (*(u32 *)(g_005B4D80 + 0x0));
  (*(u32 *)(g_0076EC60 + 0x4)) = (*(u32 *)(g_005B4D80 + 0x4));
  (*(u32 *)(g_0076EC60 + 0x8)) = (*(u32 *)(g_005B4D80 + 0x8));
  (*(u32 *)(g_0076EC60 + 0xC)) = (*(u32 *)(g_005B4D80 + 0x10));
  (*(u32 *)(g_0076EC60 + 0x10)) = (*(u32 *)(g_005B4D80 + 0x14));
  (*(u32 *)(g_0076EC60 + 0x14)) = (*(u32 *)(g_005B4D80 + 0x18));
  (*(u32 *)(g_0076EC60 + 0x18)) = (*(u32 *)(g_005B4D80 + 0x64));
  (*(u32 *)(g_0076EC60 + 0x1C)) = (*(u32 *)(g_005B4D80 + 0x60));
  func_00254330(g_0076EC40,0x5b4bc0,iVar1,iVar1 + 0x40);
  g_0045D374 = 3;
  return;
}
/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* 0x00255E00, 0x9C bytes. */
void func_00255E00(void)
{
  g_0045D374 = 0;
  (*(u32 *)(g_005B4D80 + 0x0)) = (*(u32 *)(g_0076EC60 + 0x0));
  (*(u32 *)(g_005B4D80 + 0x4)) = (*(u32 *)(g_0076EC60 + 0x4));
  (*(u32 *)(g_005B4D80 + 0xC)) = 0x3f800000;
  (*(u32 *)(g_005B4D80 + 0x8)) = (*(u32 *)(g_0076EC60 + 0x8));
  (*(u32 *)(g_005B4D80 + 0x10)) = (*(u32 *)(g_0076EC60 + 0xC));
  (*(u32 *)(g_005B4D80 + 0x14)) = (*(u32 *)(g_0076EC60 + 0x10));
  (*(u32 *)(g_005B4D80 + 0x1C)) = 0x3f800000;
  (*(u32 *)(g_005B4D80 + 0x18)) = (*(u32 *)(g_0076EC60 + 0x14));
  (*(u32 *)(g_005B4D80 + 0x64)) = (*(u32 *)(g_0076EC60 + 0x18));
  (*(u32 *)(g_005B4D80 + 0x60)) = (*(u32 *)(g_0076EC60 + 0x1C));
  return;
}
/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* 0x0029FB30, 0x34 bytes. */
int func_0029FB30(u8 *param_1)
{
    u32 uVar1;

  
  if ((int)((u32)*(u16 *)(param_1 + 0x174) - (u32)*(u16 *)(param_1 + 0x172)) < 10) {
    uVar1 = 0x3f800000;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x002A6040, 0x7C bytes. */
void func_002A6040(void)
{
    u8 * iVar1;
    u32 uVar2;

  
  uVar2 = 0;
  iVar1 = g_007732B0;
  do {
    *(u32 *)(iVar1 + 400) = 0;
    *(u32 *)(iVar1 + 0x194) = 0;
    func_00114410(iVar1 + 0x140);
    *(u32 *)(iVar1 + 0x170) = 0x3f800000;
    *(u32 *)(iVar1 + 0x160) = 0x44160000;
    *(u32 *)(iVar1 + 0x164) = 0x453b8000;
    uVar2 = uVar2 + 1;
    *(u32 *)(iVar1 + 0x168) = 0x3f800000;
    iVar1 = iVar1 + 0x70;
  } while (uVar2 < 0x107);
  return;
}

/* 0x002A62D0, 0x70 bytes. */
void func_002A62D0(void)
{
    u8 * iVar1;
    int iVar2;

  
  iVar2 = 0;
  iVar1 = g_007732B0;
  do {
    *(u32 *)(iVar1 + 0x90) = 0;
    func_00114240(iVar1);
    *(u32 *)(iVar1 + 0x50) = 0;
    iVar2 = iVar2 + 1;
    *(u32 *)(iVar1 + 0x54) = 0;
    *(u32 *)(iVar1 + 0x58) = 0x3f800000;
    *(u32 *)(iVar1 + 0x60) = 0;
    *(u32 *)(iVar1 + 100) = 0xbf800000;
    *(u32 *)(iVar1 + 0x68) = 0;
    *(u32 *)(iVar1 + 0x84) = 0x3f800000;
    iVar1 = iVar1 + 0xa0;
  } while (iVar2 < 2);
  return;
}

/* 0x002A6FF0, 0x1A8 bytes. */
void func_002A6FF0(u8 *param_1, int param_2)
{
    int iVar2;
    int iVar4;
    u32 uVar1;
    u32 uVar3;

  
  if (*(int *)(param_1 + 0x5c) != param_2) {
    iVar2 = *(int *)(param_1 + 0x60);
    iVar4 = 0xff;
    uVar3 = 0;
    if (iVar2 == 0xff) {
LAB_002a7048:
      uVar1 = *(u32 *)(param_1 + 0x5c);
    }
    else {
      if (iVar2 == param_2) {
        uVar3 = *(u32 *)(param_1 + 0x68);
        iVar4 = iVar2;
        goto LAB_002a7048;
      }
      func_0023ACC0(iVar2,0);
      uVar1 = *(u32 *)(param_1 + 0x5c);
    }
    *(u32 *)(param_1 + 0x60) = uVar1;
    *(u32 *)(param_1 + 0x68) = *(u32 *)(param_1 + 100);
    if (iVar4 == 0xff) {
      *(int *)(param_1 + 0x5c) = param_2;
    }
    else {
      *(int *)(param_1 + 0x5c) = iVar4;
    }
    *(u32 *)(param_1 + 100) = uVar3;
    if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
      if (*(int *)(param_1 + 0x5c) == *(int *)(param_1 + 0x30) * 0x100 + 3) {
        func_00114C90(2);
        iVar2 = *(int *)(param_1 + 0x5c);
        goto LAB_002a70b8;
      }
      func_00114C90(0);
    }
  }
  iVar2 = *(int *)(param_1 + 0x5c);
LAB_002a70b8:
  if ((iVar2 != 0xff) && (*(int *)(param_1 + 100) < 0x2cdc)) {
    if (*(int *)(param_1 + 100) == 0) {
      func_0023AD10(iVar2,0,0x2cdc,0x2cdc,0x1000);
    }
    iVar2 = *(int *)(param_1 + 100) + 0x2d;
    if (iVar2 < 0x2cdc) {
      *(int *)(param_1 + 100) = iVar2;
    }
    else {
      iVar2 = 0x2cdc;
      *(u32 *)(param_1 + 100) = 0x2cdc;
    }
    func_0023AC70(*(u32 *)(param_1 + 0x5c),0,iVar2,iVar2,0x1000);
  }
  if (0 < *(int *)(param_1 + 0x68)) {
    iVar2 = *(int *)(param_1 + 0x68) + -0x2d;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    *(int *)(param_1 + 0x68) = iVar2;
    func_0023AC70(*(u32 *)(param_1 + 0x60),0,iVar2,iVar2,0x1000);
    if (*(int *)(param_1 + 0x68) == 0) {
      func_0023ACC0(*(u32 *)(param_1 + 0x60),0);
      *(u32 *)(param_1 + 0x60) = 0xff;
    }
  }
  return;
}

/* 0x002A73F0, 0x164 bytes. */
void func_002A73F0(u8 *param_1, int param_2)
{
    int iVar2;
    int iVar4;
    u32 uVar1;
    u32 uVar3;

  
  if (*(int *)(param_1 + 0x4c) == param_2) goto LAB_002a7470;
  iVar2 = *(int *)(param_1 + 0x50);
  iVar4 = 0xff;
  uVar3 = 0;
  if (iVar2 == 0xff) {
LAB_002a7448:
    uVar1 = *(u32 *)(param_1 + 0x4c);
  }
  else {
    if (iVar2 == param_2) {
      uVar3 = *(u32 *)(param_1 + 0x58);
      iVar4 = iVar2;
      goto LAB_002a7448;
    }
    func_0023ACC0(iVar2,0);
    uVar1 = *(u32 *)(param_1 + 0x4c);
  }
  *(u32 *)(param_1 + 0x50) = uVar1;
  *(u32 *)(param_1 + 0x58) = *(u32 *)(param_1 + 0x54);
  if (iVar4 == 0xff) {
    *(int *)(param_1 + 0x4c) = param_2;
  }
  else {
    *(int *)(param_1 + 0x4c) = iVar4;
  }
  *(u32 *)(param_1 + 0x54) = uVar3;
LAB_002a7470:
  if ((*(int *)(param_1 + 0x4c) != 0xff) && (*(int *)(param_1 + 0x54) < 0x2cdc)) {
    if (*(int *)(param_1 + 0x54) == 0) {
      func_0023AD10(*(int *)(param_1 + 0x4c),0,0x2cdc,0x2cdc,0x1000);
    }
    iVar2 = *(int *)(param_1 + 0x54) + 0x2d;
    if (iVar2 < 0x2cdc) {
      *(int *)(param_1 + 0x54) = iVar2;
    }
    else {
      iVar2 = 0x2cdc;
      *(u32 *)(param_1 + 0x54) = 0x2cdc;
    }
    func_0023AC70(*(u32 *)(param_1 + 0x4c),0,iVar2,iVar2,0x1000);
  }
  if (0 < *(int *)(param_1 + 0x58)) {
    iVar2 = *(int *)(param_1 + 0x58) + -0x2d;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    *(int *)(param_1 + 0x58) = iVar2;
    func_0023AC70(*(u32 *)(param_1 + 0x50),0,iVar2,iVar2,0x1000);
    if (*(int *)(param_1 + 0x58) == 0) {
      func_0023ACC0(*(u32 *)(param_1 + 0x50),0);
      *(u32 *)(param_1 + 0x50) = 0xff;
    }
  }
  return;
}

/* 0x002A9EC0, 0x158 bytes. */
void func_002A9EC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iStack_8;
    int iVar1;
    u32 uStack_4;

  
  func_00146D80(param_2,&uStack_4,&iStack_8);
  if (iStack_8 < 0) {
    iStack_8 = iStack_8 + 0xf;
  }
  iVar1 = ((iStack_8 >> 4) + -1) * 0x14;
  iStack_8 = iVar1 + 0xc;
  param_4 = param_4 - (iVar1 + 0x1c);
  func_002A9D10(param_1,param_3,param_4,param_5,uStack_4,iStack_8,param_6,param_7);
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  func_00146270(param_2,(int)param_3 + 0x10,param_4 + 6,param_7,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  return;
}

/* 0x002D8CA0, 0xF8 bytes. */
void func_002D8CA0(u8 *param_1)
{
    int iVar2;
    int lVar1;
    u32 uVar3;

  
  lVar1 = func_0022DD60();
  if (lVar1 != -1) {
    *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + -1;
    *(u32 *)(param_1 + 100) = 4;
    iVar2 = *(int *)(param_1 + 0x5c);
    goto LAB_002d8d74;
  }
  iVar2 = *(int *)(param_1 + 100);
  if (iVar2 == 9) {
    uVar3 = 4;
    *(u32 *)(*(int *)(param_1 + 0x60) * 4 + param_1 + 0x20) = 2;
    *(u32 *)(*(int *)(param_1 + 0x60) * 4 + param_1 + 0x1c) =
         *(u32 *)(*(int *)(param_1 + 0xc) + 0xc);
    *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + -1;
LAB_002d8d50:
    *(u32 *)(param_1 + 100) = uVar3;
  }
  else {
    if (iVar2 == 7) {
      uVar3 = 9;
      goto LAB_002d8d50;
    }
    if (iVar2 == 5) {
      uVar3 = 7;
      goto LAB_002d8d50;
    }
    if (iVar2 == 4) {
      uVar3 = 5;
      goto LAB_002d8d50;
    }
    *(u32 *)(param_1 + 100) = 0x16;
  }
  iVar2 = *(int *)(param_1 + 0x5c);
LAB_002d8d74:
  if (iVar2 < 1) {
    *(u32 *)(param_1 + 0x40) = 0;
    *(u32 *)(param_1 + 0x6c) = 1;
  }
  return;
}

/* 0x002E63B0, 0x58 bytes, matching. */
void func_002E63B0(u8 *param_1)
{
  *(u32 *)(param_1 + 0x200) = 0x450a4ccd;
  *(u32 *)(param_1 + 0x204) = 0x45012666;
  *(u32 *)(param_1 + 0x1f8) = 0x4319999a;
  *(u32 *)(param_1 + 0x1fc) = 0x42333333;
  *(u32 *)(param_1 + 0x218) = 0x44e9989a;
  *(u32 *)(param_1 + 0x21c) = 0x44f4cbcd;
  *(u32 *)(param_1 + 0x22c) = 0x41b33333;
  return;
}

/* 0x002EB0F0, 0x114 bytes. */
void func_002EB0F0(void)
{
    int lVar2;
    u32 * puVar3;
    u32 * puVar6;
    int uVar1;
    u32 uVar4;
    u32 uVar5;

  
  puVar6 = (u32 *)0x7a0640;
  uVar5 = 0;
  g_70000D60 = 0;
  do {
    uVar1 = func_003E2000(uVar5);
    uVar4 = 0;
    puVar3 = puVar6;
    do {
      lVar2 = func_003E1F60(uVar5,uVar4);
      if (lVar2 == 0) {
        if (puVar3[2] != 0) {
          func_002EA950(puVar3);
        }
      }
      else {
        func_002EA600(puVar3,uVar5 * 0x630 + 0x574de0,lVar2,uVar1);
        puVar3[2] = (int)lVar2;
        *puVar3 = 1;
        puVar3[1] = 0x3f800000;
      }
      uVar4 = uVar4 + 1;
      puVar3 = puVar3 + 0xe0;
    } while (uVar4 < 3);
    uVar5 = uVar5 + 1;
    puVar6 = puVar6 + 0x2a0;
  } while (uVar5 < 2);
  return;
}

/* 0x00323CD0, 0x190 bytes. */
int func_00323CD0(int param_1, int param_2, int param_3, int *param_4)
{
    int iVar4;
    int iVar5;
    int lVar1;
    int lVar2;
    int * piVar3;

  
  iVar5 = 0;
  iVar4 = 0;
  piVar3 = param_4;
  do {
    lVar1 = func_002F2840(iVar4);
    if (((lVar1 != 0) && (lVar1 = func_002F4080(iVar4), param_2 == lVar1)) &&
       ((lVar1 = func_002F5CC0(iVar4), param_1 != 1 ||
        (((lVar2 = func_002FB2A0(param_2), lVar2 != 0 || (lVar1 == param_3)) ||
         (lVar2 = func_002F3E70(iVar4), lVar2 == 0)))))) {
      if (((lVar1 != param_3) && (lVar2 = func_002FA790(param_2), lVar2 == 0)) && (param_1 < 2)) {
        lVar2 = func_002FB2A0(param_2);
        if ((lVar2 == 0) || (param_1 != 0)) {
          lVar1 = func_0030C320(lVar1,param_3);
        }
        else {
          lVar1 = func_0030C3C0(lVar1,param_3);
        }
        if (lVar1 == 0) goto LAB_00323e08;
      }
      if (param_4 != (int *)0x0) {
        *piVar3 = iVar4;
      }
      piVar3 = piVar3 + 1;
      iVar5 = iVar5 + 1;
    }
LAB_00323e08:
    iVar4 = iVar4 + 1;
    if (0x19e < iVar4) {
      if (param_4 != (int *)0x0) {
        func_002F7B20(0,param_4,iVar5);
      }
      return iVar5;
    }
  } while( true );
}

/* 0x003251B0, 0x1A8 bytes. */
int func_003251B0(int param_1, int param_2, int param_3, int param_4, u8 *param_5)
{
    int iVar5;
    int lVar1;
    int lVar4;
    int lVar7;
    int * piVar6;
    int uVar2;
    u32 uVar3;
    int uVar8;

  
  uVar8 = 0;
  lVar7 = 0;
  lVar4 = 2;
  lVar1 = func_003635F0();
  piVar6 = (int *)param_4;
  if (lVar1 == 1) {
    lVar1 = func_0036B260();
    if (lVar1 == 0) {
      lVar4 = 1;
      lVar7 = lVar4;
    }
  }
  else {
    if (lVar1 != 0) {
      *piVar6 = 0;
      goto LAB_00325250;
    }
    lVar1 = func_0036B260();
    if (lVar1 != 0) {
      lVar4 = 0;
      lVar7 = 1;
    }
  }
  *piVar6 = 0;
LAB_00325250:
  if (lVar7 != 0) {
    func_0030AF20(param_3,param_1);
    func_00323840(param_3);
    *(int *)(param_5 + *piVar6 * 4) = (int)param_3;
    *piVar6 = *piVar6 + 1;
    lVar7 = func_002FB2D0(param_2);
    if (param_3 == lVar7) {
      uVar8 = func_00323F10(param_1,param_2,param_4,param_5);
    }
    iVar5 = 0;
    do {
      uVar2 = func_00362160(lVar4,iVar5);
      uVar3 = func_00337A10(uVar2);
      if (uVar3 < 0x19f) {
        uVar2 = func_002F4080(uVar3);
        lVar7 = func_002FB2A0(uVar2);
        if (lVar7 != 0) {
          func_002F5BE0(uVar3,param_3);
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 6);
  }
  func_003A7ED0();
  return uVar8;
}

/* 0x00328470, 0xF8 bytes. */
void func_00328470(void)
{
    int iVar1;
    int iVar4;
    int lVar2;
    int lVar3;

  
  iVar4 = 0;
  do {
    lVar2 = func_00328330(iVar4);
    iVar1 = iVar4;
    if ((0x3a < lVar2 && lVar2 < 0x5a) || (lVar2 == 100)) {
      do {
        iVar1 = iVar1 + 1;
        if (4 < iVar1) goto LAB_00328540;
        lVar3 = func_00328330(iVar1);
      } while (((lVar3 < 0x3b || 0x59 < lVar3) && (lVar3 != 100)) || (lVar2 <= lVar3));
      func_003282F0(lVar3,iVar4);
      func_003282F0(lVar2,iVar1);
      iVar4 = iVar4 + -1;
    }
LAB_00328540:
    iVar4 = iVar4 + 1;
    if (4 < iVar4) {
      return;
    }
  } while( true );
}

/* 0x00333A40, 0x5BC bytes. */
int func_00333A40(void)
{
    int bVar1;
    int lVar10;
    int lVar3;
    int lVar4;
    int lVar5;
    int lVar6;
    int lVar8;
    int uVar2;
    u32 uVar7;
    int uVar9;

  
  lVar10 = 0x19;
  lVar3 = lVar10;
  lVar5 = lVar10;
  lVar4 = lVar10;
  if ((*(int *)g_0045D730) < 10) {
    lVar3 = func_0032EE10(2);
    if (lVar3 == 0) {
      return 0;
    }
    lVar4 = func_002F4080(2);
    lVar3 = func_0032EE10(0x10);
    if (lVar3 == 0) {
      return 0;
    }
    lVar5 = func_002F4080(0x10);
    lVar3 = func_0032EE10(0xe8);
    if (lVar3 == 0) {
      return 0;
    }
    lVar3 = func_002F4080(0xe8);
    lVar10 = func_0032EE10(0x12);
    if (lVar10 == 0) {
      return 0;
    }
    lVar10 = func_002F4080(0x12);
    bVar1 = false;
    if (-1 < lVar4) {
      lVar6 = func_0030AB90();
      bVar1 = lVar4 < lVar6;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar5) {
      lVar6 = func_0030AB90();
      bVar1 = lVar5 < lVar6;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar3) {
      lVar6 = func_0030AB90();
      bVar1 = lVar3 < lVar6;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar10) {
      lVar6 = func_0030AB90();
      bVar1 = lVar10 < lVar6;
    }
    if (!bVar1) {
      return 0;
    }
  }
  if ((*(int *)g_0045D730) == 10) {
    func_003752D0();
    lVar3 = func_00375B90();
    if (lVar3 == 1) {
      func_003A9170();
      func_003A7D90();
      (*(int *)g_0045D730) = 0;
      return 0;
    }
  }
  else if ((*(int *)g_0045D730) == 3) {
    uVar9 = func_00390760(0x115);
    func_001204B0(g_007B4E60,uVar9);
    func_00374EE0(g_007B4E60);
    (*(int *)g_0045D730) = 10;
  }
  else if ((*(int *)g_0045D730) == 2) {
    lVar3 = func_003A9460();
    if (lVar3 != 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar2 = 0;
      }
      else {
        uVar2 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar2 & 0x40) == 0) {
        return 5;
      }
    }
    func_0023AA40();
    func_003A9440();
    (*(int *)g_0045D730) = 3;
  }
  else if ((*(int *)g_0045D730) == 1) {
    func_003752D0();
    lVar3 = func_00375B90();
    if (lVar3 == 1) {
      func_003303B0(0x1a4);
      func_003A93B0(0xc,0xd,0);
      (*(int *)g_0045D730) = 2;
    }
  }
  else {
    if ((*(int *)g_0045D730) != 0) {
      return 5;
    }
    lVar6 = func_00327820();
    if (lVar6 == 2) {
      return 0;
    }
    lVar6 = func_00327820();
    if (lVar6 == 0x10) {
      return 0;
    }
    lVar6 = func_00327820();
    if (lVar6 == 0x12) {
      return 0;
    }
    lVar6 = func_00327820();
    if (lVar6 == 0xe8) {
      return 0;
    }
    lVar6 = func_003C1850();
    if (lVar6 != 0) {
      return 0;
    }
    lVar6 = func_00327C00();
    if (lVar6 == 10) {
      return 0;
    }
    lVar6 = func_00329540(0x1a4);
    if (lVar6 != 0) {
      return 0;
    }
    lVar6 = func_00327C80();
    if (lVar6 != 0x622) {
      return 0;
    }
    uVar7 = func_00327C70();
    if (uVar7 < 2) {
      return 0;
    }
    lVar6 = func_0030AFF0(0xc);
    lVar8 = func_002F4080(2);
    if (lVar6 != lVar8) {
      return 0;
    }
    lVar6 = func_0030AFF0(0xb);
    lVar8 = func_002F4080(2);
    if (lVar6 != lVar8) {
      return 0;
    }
    lVar6 = func_0030AFF0(10);
    lVar8 = func_002F4080(0x10);
    if (lVar6 != lVar8) {
      return 0;
    }
    lVar6 = func_0030AFF0(7);
    lVar8 = func_002F4080(0xe8);
    if (lVar6 != lVar8) {
      return 0;
    }
    lVar6 = func_0030AFF0(0xd);
    lVar8 = func_002F4080(0x12);
    if (lVar6 != lVar8) {
      return 0;
    }
    lVar6 = func_003C0C60(lVar4,lVar5);
    if (lVar6 == 0) {
      return 0;
    }
    lVar6 = func_003C0C60(lVar10,lVar3);
    if (lVar6 == 0) {
      return 0;
    }
    lVar6 = func_003C0C60(lVar4,lVar10);
    if (lVar6 != 0) {
      return 0;
    }
    lVar4 = func_003C0C60(lVar4,lVar3);
    if (lVar4 != 0) {
      return 0;
    }
    lVar4 = func_003C0C60(lVar5,lVar10);
    if (lVar4 != 0) {
      return 0;
    }
    lVar3 = func_003C0C60(lVar5,lVar3);
    if (lVar3 != 0) {
      return 0;
    }
    lVar3 = func_0032EB40(0x12,5,0);
    if (lVar3 == 0) {
      return 0;
    }
    uVar9 = func_00390760(0x114);
    func_001204B0(g_007B4E60,uVar9);
    func_00374EE0(g_007B4E60);
    func_003A90E0(0,0xc,0xd);
    (*(int *)g_0045D730) = 1;
  }
  return 5;
}

/* 0x00334000, 0x670 bytes. */
int func_00334000(void)
{
    int aiStack_70[28];
    int bVar1;
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar3;
    int lVar14;
    int lVar4;
    int lVar5;
    int lVar6;
    int lVar7;
    int * piVar10;
    int uVar2;
    u32 uVar8;
    int uVar9;

  
  lVar14 = 0x19;
  lVar4 = lVar14;
  lVar5 = lVar14;
  lVar6 = lVar14;
  if ((*(u32 *)(g_0045D730 + 0x0)) < 10) {
    lVar4 = func_0032EE10(3);
    if (lVar4 == 0) {
      return 0;
    }
    lVar5 = func_002F4080(3);
    lVar4 = func_0032EE10(2);
    if (lVar4 == 0) {
      return 0;
    }
    lVar6 = func_002F4080(2);
    lVar4 = func_0032EE10(0xd);
    if (lVar4 == 0) {
      return 0;
    }
    lVar4 = func_002F4080(0xd);
    lVar14 = func_0032EE10(0x1b);
    if (lVar14 == 0) {
      return 0;
    }
    lVar14 = func_002F4080(0x1b);
    bVar1 = false;
    if (-1 < lVar5) {
      lVar7 = func_0030AB90();
      bVar1 = lVar5 < lVar7;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar6) {
      lVar7 = func_0030AB90();
      bVar1 = lVar6 < lVar7;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar4) {
      lVar7 = func_0030AB90();
      bVar1 = lVar4 < lVar7;
    }
    if (!bVar1) {
      return 0;
    }
    bVar1 = false;
    if (-1 < lVar14) {
      lVar7 = func_0030AB90();
      bVar1 = lVar14 < lVar7;
    }
    if (!bVar1) {
      return 0;
    }
  }
  if ((*(u32 *)(g_0045D730 + 0x0)) == 10) {
    func_003752D0();
    lVar4 = func_00375B90();
    if (lVar4 == 1) {
      func_003A9170();
      (*(u32 *)(g_0045D730 + 0x0)) = 0;
      return 0;
    }
  }
  else if ((*(u32 *)(g_0045D730 + 0x0)) == 3) {
    func_002F7610();
    func_002F7610(0xc);
    func_002F7610(0xc2);
    iVar12 = 0;
    do {
      if ((iVar12 != 2) && (lVar4 = func_0032EB40(2,iVar12,0), lVar4 != 0)) {
        iVar11 = 0;
        iVar13 = 0;
        lVar4 = func_0030AB90();
        if (0 < lVar4) {
          piVar10 = aiStack_70;
          do {
            iVar3 = func_002F5CC0(iVar12);
            if (iVar13 != iVar3) {
              uVar9 = func_002F5CC0(iVar12);
              lVar4 = func_0030C280(iVar13,uVar9);
              if (lVar4 != 0) {
                *piVar10 = iVar13;
                iVar11 = iVar11 + 1;
                piVar10 = piVar10 + 1;
              }
            }
            iVar13 = iVar13 + 1;
            iVar3 = func_0030AB90();
          } while (iVar13 < iVar3);
        }
        func_002F3B30(iVar12,2);
        func_002F3CF0(iVar12,0);
        func_002F3F70(iVar12,0x19);
        if (0 < iVar11) {
          if (iVar11 == 0) {
            iVar11 = 0;
          }
          else {
            g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
            iVar11 = (int)(g_7000015C >> 0x10) % iVar11;
          }
          func_002F5BE0(iVar12,aiStack_70[iVar11]);
        }
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < 0x19f);
    func_002F7610(2);
    func_0030A030(lVar6,lVar5);
    uVar9 = func_00390760(0x117);
    func_001204B0(g_007B4E60,uVar9);
    func_00374EE0(g_007B4E60);
    (*(u32 *)(g_0045D730 + 0x0)) = 10;
  }
  else if ((*(u32 *)(g_0045D730 + 0x0)) == 2) {
    lVar4 = func_003A9460();
    if (lVar4 != 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar2 = 0;
      }
      else {
        uVar2 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar2 & 0x40) == 0) {
        return 5;
      }
    }
    func_0023AA40();
    func_003A9440();
    (*(u32 *)(g_0045D730 + 0x0)) = 3;
  }
  else if ((*(u32 *)(g_0045D730 + 0x0)) == 1) {
    func_003752D0();
    lVar4 = func_00375B90();
    if (lVar4 == 1) {
      func_003303B0(0x182);
      func_003A93B0(0xe,0xd,1);
      (*(u32 *)(g_0045D730 + 0x0)) = 2;
    }
  }
  else {
    if ((*(u32 *)(g_0045D730 + 0x0)) != 0) {
      return 5;
    }
    lVar7 = func_00327820();
    if (lVar7 == 3) {
      return 0;
    }
    lVar7 = func_00327820();
    if (lVar7 == 2) {
      return 0;
    }
    lVar7 = func_003C1850();
    if (lVar7 != 0) {
      return 0;
    }
    lVar7 = func_00327C00();
    if (lVar7 == 10) {
      return 0;
    }
    lVar7 = func_00329540(0x182);
    if (lVar7 != 0) {
      return 0;
    }
    lVar7 = func_00327C80();
    if (lVar7 != 0x62e) {
      return 0;
    }
    uVar8 = func_00327C70();
    if (uVar8 < 2) {
      return 0;
    }
    lVar7 = func_0030AFF0(0xe);
    if (lVar5 != lVar7) {
      return 0;
    }
    lVar6 = func_003C0C60(lVar5,lVar6);
    if (lVar6 == 0) {
      return 0;
    }
    lVar4 = func_003C0C60(lVar5,lVar4);
    if (lVar4 != 0) {
      return 0;
    }
    lVar4 = func_003C0C60(lVar5,lVar14);
    if (lVar4 != 0) {
      return 0;
    }
    lVar4 = func_0032EB40(2,10,0);
    if (lVar4 == 0) {
      return 0;
    }
    lVar4 = func_0032EB40(2,0xc,0);
    if (lVar4 == 0) {
      return 0;
    }
    lVar4 = func_0032EB40(2,0xc2,0);
    if (lVar4 == 0) {
      return 0;
    }
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if (0x13 < (g_7000015C >> 0x10) % 100) {
      return 0;
    }
    uVar9 = func_00390760(0x116);
    func_001204B0(g_007B4E60,uVar9);
    func_00374EE0(g_007B4E60);
    func_003A90E0(0,0xe,0xd);
    (*(u32 *)(g_0045D730 + 0x0)) = 1;
  }
  return 5;
}
/* MISSING ['0x45d730'] */

/* 0x0036BB80, 0xC0 bytes. */
int func_0036BB80(int param_1)
{
    int iVar3;
    int lVar2;
    int uVar1;

  
  iVar3 = 2;
  if (param_1 == 0) {
LAB_0036bbc4:
    iVar3 = 0;
    goto LAB_0036bc18;
  }
  if (param_1 == 4) {
    uVar1 = func_00362570();
    lVar2 = func_0035D5B0(uVar1);
    if (lVar2 == 1) goto LAB_0036bbc4;
  }
  if (((param_1 != 1) && (param_1 != 2)) && (param_1 != 3)) {
    if (param_1 != 4) goto LAB_0036bc18;
    uVar1 = func_00362570();
    lVar2 = func_0035D5B0(uVar1);
    if (lVar2 != 0) goto LAB_0036bc18;
  }
  iVar3 = 1;
LAB_0036bc18:
  if (iVar3 == 2) {
    iVar3 = 0;
  }
  return iVar3;
}

/* 0x003752D0, 0x308 bytes. */
void func_003752D0(void)
{
    int iVar1;
    int iVar2;

  
  if ((((*(u32 *)(g_007B99F0 + 0x0)) == 1) && (0 < (*(u32 *)(g_007B99F0 + 0x4)))) && ((*(u32 *)(g_007B99F0 + 0x4)) < 4)) {
    if ((*(short *)(g_007B99F0 + 0x3E)) == 0) {
      func_003B3A60((*(u32 *)(g_007B99F0 + 0x28)),(*(u32 *)(g_007B99F0 + 0x2C)),(*(u32 *)(g_007B99F0 + 0x30)),5,(*(u32 *)(g_007B99F0 + 0x34)),(*(u32 *)(g_007B99F0 + 0x38)),0);
      if ((*(u32 *)(g_007B99F0 + 0x4)) == 2) {
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146270(g_007B9A30,(*(u32 *)(g_007B99F0 + 0x28)) + 0x18,(*(u32 *)(g_007B99F0 + 0x2C)) + 0xd,5,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        if ((*(u32 *)(g_007B99F0 + 0x8)) == 1) {
          iVar1 = (*(u32 *)(g_007B99F0 + 0x20));
          if ((*(u32 *)(g_007B99F0 + 0x20)) < 0) {
            iVar1 = (*(u32 *)(g_007B99F0 + 0x20)) + 1;
          }
          iVar1 = (*(u32 *)(g_007B99F0 + 0x18)) + (iVar1 >> 1);
          iVar2 = (*(u32 *)(g_007B99F0 + 0x1C)) + (*(u32 *)(g_007B99F0 + 0x24)) + -0x24;
          func_003B5660(iVar1 + -0x50,iVar2,0,0x80,5,1,(*(u32 *)(g_007B99F0 + 0x14)) == 0);
          func_003B5660(iVar1,iVar2,0,0x80,5,0,(*(u32 *)(g_007B99F0 + 0x14)) != 0);
        }
      }
    }
    else {
      func_003B3A60((*(u32 *)(g_007B99F0 + 0x28)),(*(u32 *)(g_007B99F0 + 0x2C)),(*(u32 *)(g_007B99F0 + 0x30)),5,(*(u32 *)(g_007B99F0 + 0x34)),(*(u32 *)(g_007B99F0 + 0x38)),0);
      if ((*(u32 *)(g_007B99F0 + 0x4)) == 2) {
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146270(g_007B9A30,(*(u32 *)(g_007B99F0 + 0x28)) + 0x10,(*(u32 *)(g_007B99F0 + 0x2C)) + 0x10,5,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        if ((*(u32 *)(g_007B99F0 + 0x8)) == 1) {
          iVar1 = (*(u32 *)(g_007B99F0 + 0x20));
          if ((*(u32 *)(g_007B99F0 + 0x20)) < 0) {
            iVar1 = (*(u32 *)(g_007B99F0 + 0x20)) + 1;
          }
          iVar1 = (*(u32 *)(g_007B99F0 + 0x18)) + (iVar1 >> 1);
          iVar2 = (*(u32 *)(g_007B99F0 + 0x1C)) + (*(u32 *)(g_007B99F0 + 0x24)) + -0x2c;
          func_003B5660(iVar1 + -0x50,iVar2,0,0x80,5,1,(*(u32 *)(g_007B99F0 + 0x14)) == 0);
          func_003B5660(iVar1,iVar2,0,0x80,5,0,(*(u32 *)(g_007B99F0 + 0x14)) != 0);
        }
      }
    }
  }
  return;
}

/* 0x0038A550, 0x80 bytes. */
int func_0038A550(u8 *param_1)
{
    int iVar2;
    u32 uVar1;
    int uVar3;

  
  uVar3 = 0x24;
  iVar2 = *(int *)(param_1 + 8);
  param_1 = param_1 + *(int *)(param_1 + 0x68c) * 0x184;
  if (iVar2 == 0x2a) {
    uVar3 = 0x26;
  }
  else if (iVar2 == 0x29) {
    uVar3 = 0x25;
  }
  else if (iVar2 != 0x28) {
    uVar1 = *(u32 *)(param_1 + 0xb8);
    goto LAB_0038a5b8;
  }
  uVar1 = *(u32 *)(param_1 + 0xb8);
LAB_0038a5b8:
  iVar2 = func_00389D60(uVar3,uVar1);
  return iVar2 + 1;
}

/* 0x0038B830, 0x178 bytes. */
void func_0038B830(u8 *param_1)
{
    int iVar1;
    u8 * iVar2;
    int iVar5;
    u32 * puVar3;
    u32 * puVar6;
    int uVar4;

  
  iVar2 = param_1 + *(int *)(param_1 + 0x68c) * 0x184;
  puVar6 = (u32 *)(iVar2 + 0x80);
  puVar3 = (u32 *)func_003DB900(6);
  iVar5 = 0x1e;
  (*(u32 *)(g_007B9F30 + 0xC)) = 0x1e;
  iVar1 = *(int *)(param_1 + 0x690);
  if (iVar1 == 2) {
    (*(u32 *)(g_007B9F30 + 0x8)) = 0x1e;
    (*(u32 *)(g_007B9F30 + 0x0)) = 0;
    uVar4 = func_0030D7D0();
    func_00380EB0(1.0f,uVar4,*puVar6,*puVar3,puVar3[1],*(u32 *)(iVar2 + 0x84));
  }
  else if (iVar1 == 1) {
    (*(u32 *)(g_007B9F30 + 0x0)) = 1;
    (*(u32 *)(g_007B9F30 + 0x8)) = (*(u32 *)(g_007B9F30 + 0x8)) + 1;
    if ((*(u32 *)(g_007B9F30 + 0x8)) < 0x1f) {
      iVar5 = (*(u32 *)(g_007B9F30 + 0x8));
    }
    uVar4 = func_0030D7D0();
    func_00380EB0((float)iVar5 / 30.0,uVar4,*puVar6,*puVar3,puVar3[1],*(u32 *)(iVar2 + 0x84));
  }
  else if (iVar1 == 0) {
    (*(u32 *)(g_007B9F30 + 0x8)) = 0;
    (*(u32 *)(g_007B9F30 + 0x0)) = 0;
    uVar4 = func_0030D7D0();
    func_00380E80(uVar4,*puVar6,*puVar3,puVar3[1]);
  }
  return;
}

/* 0x003955A0, 0x110 bytes. */
int func_003955A0(int param_1)
{
    int cVar1;
    int iVar2;
    u8 * iVar3;

  
  iVar3 = func_00391250();
  iVar2 = *(int *)(iVar3 + 4);
  if (iVar2 == 4) {
    func_00394100();
    func_003E9460(param_1);
  }
  else if (iVar2 == 3) {
    func_00394960();
    func_003E9460(param_1);
  }
  else if (iVar2 == 2) {
    func_00394740();
    func_003E9460(param_1);
  }
  else if (iVar2 == 1) {
    func_00393D30();
    func_003E9460(param_1);
  }
  else {
    if (iVar2 != 0) {
      cVar1 = *(char *)(iVar3 + 0x17c);
      goto LAB_0039566c;
    }
    func_00393680(param_1);
  }
  cVar1 = *(char *)(iVar3 + 0x17c);
LAB_0039566c:
  if ((cVar1 != '\0') && (*(char *)(iVar3 + 0x17c) = cVar1 + -1, *(char *)(iVar3 + 0x17c) == '\0'))
  {
    func_003E9690();
    func_003E9750(0);
  }
  return 1;
}

/* 0x003E2C60, 0xD0 bytes. */
void func_003E2C60(int param_1)
{
    u32 auStack_10[4];
    int lVar1;
    u32 uVar2;
    u32 uVar3;

  
  auStack_10[0] = (*(u32 *)(g_0041D028 + 0x0));
  auStack_10[1] = (*(u32 *)(g_0041D028 + 0x4));
  auStack_10[2] = (*(u32 *)(g_0041D028 + 0x8));
  lVar1 = func_0035F440();
  if (((lVar1 == 0) && (uVar2 = func_003E2EF0(param_1), uVar2 < 3)) &&
     (uVar3 = func_0036F1E0(0,0), uVar3 < 2)) {
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < auStack_10[(int)uVar2]) {
      func_0035D210();
    }
  }
  return;
}
/* MISSING ['0x41d028', '0x41d02c', '0x41d030'] */

/* 0x003F2030, 0x54 bytes, matching. */
int func_003F2030(void)
{
    int lVar1;
    u32 uStack_4;

  
  uStack_4 = 0;
  lVar1 = func_003F1A30(&uStack_4);
  if (((lVar1 == 0) && (lVar1 = func_003F1B50(&uStack_4), lVar1 == 0)) &&
     (lVar1 = func_003F1D40(&uStack_4), lVar1 == 0)) {
    func_003F1F10(&uStack_4);
  }
  return uStack_4;
}
