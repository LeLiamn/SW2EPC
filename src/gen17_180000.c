/*
 * gen17_180000.c - a function between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_004174B8[0xC];
extern u8 g_0042D3E0[0x400];
extern u8 g_0056CCA4[0x24];

int func_001204B0();
int func_00146270();
int func_00146B40();
int func_001ABE40();
int func_001ABEA0();
void func_002C5020(float s, char *t, int x, int y, int a, int b, int col);
int func_002C7310();
int func_002CA490();
void *func_002F2890();
int func_002F3DC0();
int func_002F6850();
void *func_002F7B10();
int func_002F7D90();
int func_002F8F20();
int func_0030AB90();
void *func_0030ABF0();
int func_0030AC90();
int func_0030ACE0();
int func_0030AD80();
int func_0030AE80();
int func_0030AFF0();
int func_0030B090();
int func_0030B240();
int func_0030C660();
void *func_0030D7D0();
void *func_0030D7E0();
int func_00327D50();
int func_0032EB10();
void *func_00365480();
void *func_00365490();
void *func_00372E10();
int func_00380990();
int func_00382620();
int func_00383880();
void func_00386900(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);

/* 0x00386900, 0xDBC bytes. */
void func_00386900(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int rows[3];
    u32 auStack_10[4];
    u32 auStack_20[4];
    u8 auStack_40[16];
    int bVar1;
    int iStack_60;
    int iStack_70;
    int iStack_80;
    int iVar10;
    int iVar12;
    int iVar14;
    int iVar15;
    int iVar2;
    int iVar9;
    long long lVar4;
    long long lVar5;
    u32 * puVar11;
    u32 * puVar13;
    u32 * puVar3;
    unsigned long long uVar6;
    unsigned long long uVar7;
    unsigned long long uVar8;

  
  bVar1 = false;
  iVar10 = (int)param_2;
  if ((-1 < param_2) && (iVar2 = func_0030AB90(), iVar10 < iVar2)) {
    bVar1 = true;
  }
  if (!bVar1) {
    return;
  }
  lVar4 = func_0030AFF0(iVar10);
  bVar1 = false;
  if (-1 < lVar4) {
    lVar5 = func_0030AB90();
    bVar1 = lVar4 < lVar5;
  }
  if (!bVar1) {
    return;
  }
  iStack_70 = 0;
  iStack_60 = 0;
  iVar2 = func_0030C660(iVar10);
  puVar3 = (u32 *)func_002F7B10();
  iVar9 = 0;
  if (0 < iVar2) {
    puVar11 = auStack_20;
    puVar13 = auStack_10;
    do {
      lVar4 = func_002F3DC0(*puVar3);
      if (lVar4 == 1) {
        *puVar11 = *puVar3;
        iStack_70 = iStack_70 + 1;
        puVar11 = puVar11 + 1;
      }
      else {
        *puVar13 = *puVar3;
        iStack_60 = iStack_60 + 1;
        puVar13 = puVar13 + 1;
      }
      iVar9 = iVar9 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar9 < iVar2);
  }
  func_002C7310(param_3,param_4,param_5,0xc4,0x114,0x80,param_6);
  uVar6 = func_0030AFF0(iVar10);
  uVar6 = func_002F8F20(uVar6);
  uVar7 = func_00382620(uVar6);
  iVar9 = (int)param_3;
  iVar2 = (int)param_4;
  if (param_7 == 0) {
    uVar8 = PS2_ADDR(func_0030D7E0());
  }
  else {
    uVar8 = PS2_ADDR(func_00365480());
  }
  func_001ABE40(uVar8,uVar7,iVar9 + 0x10,iVar2 + 6,0,0x2a,0x2e,0x80, 1, 0);
  if (param_7 == 0) {
    uVar7 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar7 = PS2_ADDR(func_00365490());
  }
  uVar6 = func_002F6850(uVar6);
  func_00383880(uVar7,uVar6,iVar9 + 0x42,iVar2 + 0xc,0,0x20,0x20,1, 0x80);
  if (param_7 == 0) {
    uVar6 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar6 = PS2_ADDR(func_00365490());
  }
  func_001ABEA0(uVar6,0x51,iVar9 + 0x10,iVar2 + 0x34,param_5,0x28,0x18,0, 0, 0x28, 0x18, 0x80, param_6, 0);
  uVar6 = func_0030AFF0(iVar10);
  uVar6 = func_002F8F20(uVar6);
  uVar6 = PS2_ADDR(func_002F2890(uVar6));
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  func_00146B40(uVar6,iVar9 + 0x38,iVar2 + 0x39,0x7a,0x10,param_6,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  func_002CA490(iVar9 + 8,iVar2 + 0x4d,param_5,0xb4,3,0x80,param_6);
  if (param_7 == 0) {
    uVar6 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar6 = PS2_ADDR(func_00365490());
  }
  func_001ABEA0(uVar6,0x51,iVar9 + 0x10,iVar2 + 0x50,param_5,0x28,0x18,0, 0x18, 0x28, 0x18, 0x80, param_6, 0);
  uVar6 = PS2_ADDR(func_0030ABF0(iVar10));
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  func_00146270(uVar6,iVar9 + 0x38,iVar2 + 0x55,param_6,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  func_002CA490(iVar9 + 8,iVar2 + 0x69,param_5,0xb4,3,0x80,param_6);
  if (param_1 == 0) {
    iStack_80 = iVar2 + 0x7c;
    iVar10 = 0;
    iVar12 = iVar2 + 0x6a;
    puVar3 = auStack_10;
    iVar14 = iVar2 + 0x6c;
    do {
      if (param_7 == 0) {
        uVar6 = PS2_ADDR(func_0030D7D0());
      }
      else {
        uVar6 = PS2_ADDR(func_00365490());
      }
      func_001ABEA0(uVar6,0x51,iVar9 + 0x10,iVar12,param_5,0x28,0x18,0, 0x30, 0x28, 0x18, 0x80, param_6, 0);
      if (iVar10 < iStack_60) {
        uVar6 = PS2_ADDR(func_002F2890(*puVar3));
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146B40(uVar6,iVar9 + 0x38,iVar14,0x7a,0x10,param_6,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        if (param_7 == 0) {
          uVar6 = PS2_ADDR(func_0030D7D0());
        }
        else {
          uVar6 = PS2_ADDR(func_00365490());
        }
        func_00380990(uVar6,*puVar3,iVar9 + 0x38,iStack_80);
      }
      iVar10 = iVar10 + 1;
      iVar12 = iVar12 + 0x1a;
      puVar3 = puVar3 + 1;
      iStack_80 = iStack_80 + 0x1a;
      iVar14 = iVar14 + 0x1a;
    } while (iVar10 < 3);
    func_002CA490(iVar9 + 0x10,iVar2 + 0xbd,param_5,0xa4,3,0x80,param_6);
    iVar12 = iVar2 + 0xc0;
    iVar14 = iVar2 + 0xc2;
    iVar10 = 0;
    puVar3 = auStack_20;
    iVar2 = iVar2 + 0xd2;
    do {
      if (param_7 == 0) {
        uVar6 = PS2_ADDR(func_0030D7D0());
      }
      else {
        uVar6 = PS2_ADDR(func_00365490());
      }
      func_001ABEA0(uVar6,0x51,iVar9 + 0x10,iVar12,param_5,0x28,0x18,0, 0x48, 0x28, 0x18, 0x80, param_6, 0);
      if (iVar10 < iStack_70) {
        uVar6 = PS2_ADDR(func_002F2890(*puVar3));
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146B40(uVar6,iVar9 + 0x38,iVar14,0x7a,0x10,param_6,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        if (param_7 == 0) {
          uVar6 = PS2_ADDR(func_0030D7D0());
        }
        else {
          uVar6 = PS2_ADDR(func_00365490());
        }
        func_00380990(uVar6,*puVar3,iVar9 + 0x38,iVar2);
      }
      iVar10 = iVar10 + 1;
      iVar12 = iVar12 + 0x1a;
      puVar3 = puVar3 + 1;
      iVar14 = iVar14 + 0x1a;
      iVar2 = iVar2 + 0x1a;
    } while (iVar10 < 3);
    return;
  }
  iVar15 = 0;
  iVar12 = iVar2 + 0x68;
  iVar14 = iVar2 + 0x7e;
  do {
    rows[0] = (*(int *)(g_004174B8 + 0x0));
    rows[1] = (*(int *)(g_004174B8 + 0x4));
    rows[2] = (*(int *)(g_004174B8 + 0x8));
    if (param_7 == 0) {
      uVar6 = PS2_ADDR(func_0030D7D0());
    }
    else {
      uVar6 = PS2_ADDR(func_00365490());
    }
    func_001ABEA0(uVar6,0x122,iVar9 + 0x10,iVar12,param_5,0x38,0x18,0, rows[iVar15] * 0x18, 0x38, 0x18, 0x80, param_6, 0);
    func_002CA490(iVar9 + 0x10,iVar14,param_5,0xa4,3,0x80,param_6);
    iVar15 = iVar15 + 1;
    iVar12 = iVar12 + 0x18;
    iVar14 = iVar14 + 0x18;
  } while (iVar15 < 3);
  uVar6 = func_0030AD80(iVar10);
  uVar7 = func_0030AE80(iVar10);
  func_001204B0(auStack_40,0x459638,uVar6,uVar7);
  func_002C5020(16.0f,(char *)(auStack_40),iVar9 + 0xa8,iVar2 + 0x6c,param_6,0,6);
  uVar6 = func_0030B090(iVar10);
  uVar7 = func_0030ACE0(iVar10);
  func_001204B0(auStack_40,0x459638,uVar6,uVar7);
  func_002C5020(16.0f,(char *)(auStack_40),iVar9 + 0xa8,iVar2 + 0x84,param_6,0,6);
  lVar4 = func_0032EB10();
  if (lVar4 == 0) {
    lVar4 = func_00327D50();
    bVar1 = false;
    if (-1 < lVar4) {
      lVar5 = func_0030AB90();
      bVar1 = lVar4 < lVar5;
    }
    if (!bVar1) {
      func_001204B0(auStack_40,0x459648);
      goto LAB_003872bc;
    }
  }
  uVar6 = func_002F7D90(6,0x2f8500,iVar10,0,0,0);
  func_001204B0(auStack_40,0x459640,uVar6);
LAB_003872bc:
  func_002C5020(16.0f,(char *)(auStack_40),iVar9 + 0xa8,iVar2 + 0x9c,param_6,0,6);
  if (param_7 == 0) {
    uVar6 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar6 = PS2_ADDR(func_00365490());
  }
  func_001ABEA0(uVar6,0x122,iVar9 + 0x10,iVar2 + 0xb0,param_5,0x38,0x18,0, 0x60, 0x38, 0x18, 0x80, param_6, 0);
  iVar12 = func_0030AC90(iVar10,0);
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  func_00146B40(((u8 *)PS2_PTR(((ps2ptr *)g_0042D3E0)[iVar12])),iVar9 + 0x48,iVar2 + 0xb6,0x78,0x10,param_6,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  uVar6 = func_0030AC90(iVar10,1);
  uVar6 = PS2_ADDR(func_00372E10(uVar6));
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  func_00146B40(uVar6,iVar9 + 0x48,iVar2 + 0xca,0x6c,0x10,param_6,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  func_002CA490(iVar9 + 0x10,iVar2 + 0xdc,param_5,0xa4,3,0x80,param_6);
  if (param_7 == 0) {
    uVar6 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar6 = PS2_ADDR(func_00365490());
  }
  func_001ABEA0(uVar6,0x122,iVar9 + 0x10,iVar2 + 0xdc,param_5,0x38,0x18,0, 0x78, 0x38, 0x18, 0x80, param_6, 0);
  iVar12 = 0;
  iVar14 = iVar9 + 0x48;
  do {
    lVar4 = func_0030B240(iVar10,iVar12 + 1);
    if (lVar4 == 2) {
      if (param_7 == 0) {
        uVar6 = PS2_ADDR(func_0030D7D0());
      }
      else {
        uVar6 = PS2_ADDR(func_00365490());
      }
      func_001ABE40(uVar6,iVar12 + 0x124,iVar14,iVar2 + 0xdd,param_5,0x18,0x14,0x80, param_6, 0);
      iVar14 = iVar14 + 0x1a;
    }
    iVar12 = iVar12 + 1;
  } while (iVar12 < 4);
  func_002CA490(iVar9 + 0x10,iVar2 + 0xf2,param_5,0xa4,3,0x80,param_6);
  if (param_7 == 0) {
    uVar6 = PS2_ADDR(func_0030D7D0());
  }
  else {
    uVar6 = PS2_ADDR(func_00365490());
  }
  func_001ABEA0(uVar6,0x122,iVar9 + 0x10,iVar2 + 0xf4,param_5,0x38,0x18,0, 0x90, 0x38, 0x18, 0x80, param_6, 0);
  lVar4 = func_0030B240(iVar10,0);
  if (lVar4 == 2) {
    if (param_7 == 0) {
      uVar6 = PS2_ADDR(func_0030D7D0());
    }
    else {
      uVar6 = PS2_ADDR(func_00365490());
    }
    func_001ABE40(uVar6,0x123,iVar9 + 0x48,iVar2 + 0xf5,param_5,0x18,0x14,0x80, param_6, 0);
  }
  return;
}
/* MISSING ['0x4174b8', '0x4174bc', '0x4174c0'] */
