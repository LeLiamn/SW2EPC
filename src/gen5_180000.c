/*
 * gen5_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

#include "sw2e_mem.h"

#define true 1
#define false 0

extern u8 g_0040C558[0x8];
extern u8 g_0045D898[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_00732220[0x10];
extern u8 g_00732508[0x10];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007A0640[0x10];
extern u8 g_007A1B40[0x30];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D6A4;   /* (small data) */
extern int g_0045D6A8;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern u32 g_700000C0;   /* (scratchpad) */
extern u32 g_700000C4;   /* (scratchpad) */
extern u32 g_700000C8;   /* (scratchpad) */
extern u32 g_700000CC;   /* (scratchpad) */
extern u32 g_7000015C;   /* (scratchpad) */
extern u32 g_70000888;   /* (scratchpad) */

int func_001050B0();
int func_00118850();
int func_0011ED38();
int func_001204B0();
int func_0016C040();
int func_0018F680();
int func_00190590();
int func_001907E0();
int func_001C8780();
int func_001C8E80();
int func_001EAC00();
int func_001EC210();
int func_001EC530();
int func_001F1790();
int func_001F5A60();
int func_001FF100();
int func_001FF140();
int func_002039F0();
int func_00204D00();
int func_00204D20();
int func_00204DB0();
int func_00206590();
int func_00206950();
int func_00206B80();
int func_0020E140();
int func_0020E170();
int func_0023AD10();
int func_0024B790();
void *func_0027E660();
int func_0027E6A0();
int func_0027E730();
void *func_0027E990();
int func_0027F120();
int func_0027F140();
int func_0027F160();
int func_002A5B10();
int func_002BBF00();
void *func_002BBF40();
int func_002BC110();
int func_002D78E0();
int func_002F2890();
int func_002F5CC0();
int func_002F7410();
int func_002F7B10();
int func_002F7D90();
int func_002F8CB0();
int func_002FB2A0();
int func_002FB3B0();
int func_002FB430();
void *func_002FC2C0();
int func_0030AB90();
int func_0030AFF0();
int func_0030D7D0();
int func_0030E100();
int func_0030E140();
int func_0030E1F0();
int func_0030E390();
int func_00313DB0();
int func_00314030();
int func_0031D690();
int func_0031DFE0();
void *func_00320F00();
int func_003223A0();
int func_003225E0();
int func_00322780();
int func_00322850();
int func_003228F0();
int func_00322B00();
int func_00322C70();
int func_00322E80();
int func_00323040();
int func_003238D0();
int func_003241C0();
int func_00324340();
int func_00325360();
int func_003256B0();
int func_00325C60();
int func_003264A0();
int func_00327CC0();
int func_00327D50();
int func_00328DE0();
int func_00328FA0();
int func_00329160();
int func_00337A10();
int func_00362160();
int func_0036B260();
int func_0036B940();
int func_003725A0();
int func_00374EE0();
int func_0037E9F0();
int func_003821E0();
int func_00383050();
int func_003838B0();
int func_00389B40();
int func_00389D20();
int func_00389E40();
int func_0038A010();
int func_0038A330();
int func_0038A3D0();
int func_00390760();
int func_0039C740();
int func_0039C9E0();
int func_003BA8F0();
int func_003DB220();
int func_003DB460();
int func_003DB480();
int func_003DC180();
int func_003DC2D0();
void func_001EB8C0(u8 *param_1);
void func_001EC5C0(u8 *param_1);
void func_001F5EB0(u8 *param_1, int param_2);
int func_001FDC50(u8 *param_1);
int func_00203BA0(u8 *param_1);
void func_00240B30(u8 *param_1);
void func_0024B940(void);
int func_002BDE30(u8 *param_1, int param_2);
void func_002D7970(u8 *param_1);
void func_002EA9A0(void);
void func_00320790(void);
int func_003223E0(void);
void func_003239F0(u8 *param_1, int param_2);
void func_00325710(void);
void func_00326850(void);
int func_0038A5D0(u8 *param_1);
void func_0039CA60(void);

/* 0x001EB8C0, 0xA4 bytes. */
void func_001EB8C0(u8 *param_1)
{
    short asStack_4[2];
    short asStack_8[2];
    short asStack_c[2];
    u8 * iVar2;
    int lVar1;

  
  iVar2 = param_1;
  asStack_4[0] = *(short *)(iVar2 + 0x40);
  asStack_8[0] = *(short *)(iVar2 + 0x42);
  asStack_c[0] = *(short *)(iVar2 + 0x44);
  func_0018F680(asStack_8,asStack_4,asStack_c,*(u32 *)(iVar2 + 0x70));
  if ((((asStack_c[0] != asStack_8[0]) && ((*(u32 *)(iVar2 + 0x84) & 1) == 0)) &&
      (lVar1 = func_001F1790(asStack_8,param_1), lVar1 == 0)) &&
     (lVar1 = func_00190590(asStack_4,2), lVar1 == 0)) {
    asStack_8[0] = asStack_4[0];
  }
  *(short *)(iVar2 + 0x42) = asStack_8[0];
  return;
}

/* 0x001EC5C0, 0x60 bytes. */
void func_001EC5C0(u8 *param_1)
{
    u16 auStack_4[2];
    u8 * iVar2;
    int lVar1;

  
  func_001EC530();
  func_001EC210(param_1);
  iVar2 = param_1;
  auStack_4[0] = *(u16 *)(iVar2 + 0x40);
  lVar1 = func_001907E0(auStack_4,*(u8 *)(iVar2 + 0x79));
  if (lVar1 == 0) {
    *(u32 *)(iVar2 + 0x68) = 0;
  }
  else {
    func_001EAC00(param_1);
  }
  return;
}

/* 0x001F5EB0, 0x1BC bytes. */
void func_001F5EB0(u8 *param_1, int param_2)
{
    int bVar1;
    int cVar3;
    int iVar4;
    u8 * iVar6;
    int uVar2;
    u32 uVar5;

  
  iVar6 = param_1;
  uVar2 = *(u16 *)(iVar6 + 0x54);
  iVar4 = func_001FF140(uVar2);
  cVar3 = func_001FF100(uVar2,10);
  if (*(int *)(iVar6 + 0x5c) == 0) {
    cVar3 = func_001FF100(uVar2,2);
    if (cVar3 == '\x04') {
      func_001F5A60(param_1,0,iVar4 + 0x10,0);
      *(u8 *)(iVar6 + 0x66) = 1;
      *(u8 *)(iVar6 + 0x65) = *(u8 *)(iVar6 + 0x65) | 0x10;
    }
  }
  else if ((*(char *)(iVar6 + 0x5b) == '\x04') || (param_2 == 0)) {
    *(u8 *)(iVar6 + 0x66) = 5;
  }
  else if ((cVar3 == '\0') || (uVar5 = func_0027F140(), 1 < uVar5)) {
    bVar1 = *(u8 *)(iVar6 + 0x65);
    if (bVar1 != 0) {
      if ((bVar1 & 2) == 0) {
        if ((bVar1 & 4) == 0) {
          if ((bVar1 & 1) == 0) {
            if ((*(u8 *)(iVar6 + 100) & 1) == 0) {
              *(u8 *)(iVar6 + 0x66) = 1;
            }
            else {
              *(u8 *)(iVar6 + 0x66) = 0;
            }
          }
          else if ((*(u8 *)(iVar6 + 100) & 1) == 0) {
            *(u8 *)(iVar6 + 0x66) = 1;
          }
          else {
            *(u8 *)(iVar6 + 0x66) = 2;
          }
        }
        else if ((bVar1 & 1) == 0) {
          *(u8 *)(iVar6 + 0x66) = 4;
        }
        else {
          *(u8 *)(iVar6 + 0x66) = 3;
        }
      }
      else {
        *(u8 *)(iVar6 + 0x66) = 2;
      }
    }
    if (*(u8 *)(iVar6 + 100) != 0) {
      *(u8 *)(iVar6 + 100) = *(u8 *)(iVar6 + 100) | 4;
    }
  }
  else {
    *(u8 *)(iVar6 + 0x66) = 5;
  }
  return;
}

/* 0x001FDC50, 0x138 bytes. */
int func_001FDC50(u8 *param_1)
{
    int bVar1;
    int cVar3;
    int iVar2;
    int lVar4;

  
  iVar2 = g_70000888;
  cVar3 = func_001FF100(*(u16 *)(param_1 + 0x54),4);
  bVar1 = false;
  if (((*(u32 *)(g_0045D898 + 0x0)) == 7) &&
     ((lVar4 = func_0020E140(), lVar4 != 0 || (lVar4 = func_0020E170(), lVar4 != 0)))) {
    bVar1 = true;
  }
  if ((iVar2 == 1) || (bVar1)) {
    if (cVar3 == '\x01') {
      return false;
    }
    if (cVar3 == '\x02') {
      return true;
    }
  }
  else {
    if (iVar2 == 4) {
      if ((cVar3 == '\x03') && ((*(u8 *)(param_1 + 0x69) & 1) == 0)) {
        return (int)2;
      }
      return false;
    }
    if (cVar3 == '\x02') {
      return false;
    }
  }
  return (*(u8 *)(param_1 + 0x69) & 1) == 0;
}

/* 0x00203BA0, 0xD0 bytes. */
int func_00203BA0(u8 *param_1)
{
    int iVar1;
    u8 * iVar3;
    int lVar2;

  
  lVar2 = func_00206B80();
  iVar3 = param_1;
  if (lVar2 == 0) {
    lVar2 = func_00206590(param_1);
    if ((lVar2 == 0) && (lVar2 = func_00206950(param_1), lVar2 == 0)) {
      if ((*(u32 *)(iVar3 + 0xb8) & 0x180) != 0) {
        *(u8 *)(*(int *)(iVar3 + 0x10) + 0x7a) = 1;
      }
      *(u32 *)(iVar3 + 0xbc) = *(u32 *)(iVar3 + 0xbc) & 0xfff8003f;
      *(u8 *)(iVar3 + 0x7d) = 0;
      return 0;
    }
  }
  else if ((*(u32 *)(*(int *)(iVar3 + 8) + 0xb8) & 0xc) == 0) {
    func_00206950(param_1);
    iVar1 = *(int *)(iVar3 + 8);
    goto LAB_00203c40;
  }
  iVar1 = *(int *)(iVar3 + 8);
LAB_00203c40:
  if (iVar1 != 0) {
    func_002039F0(param_1,*(int *)(iVar3 + 0xc) != 0);
  }
  return 1;
}

/* 0x00240B30, 0xC4 bytes. */
void func_00240B30(u8 *param_1)
{
    u8 * iVar1;
    u8 * iVar3;
    int lVar2;
    int lVar5;
    u32 uVar4;

  
  iVar3 = param_1;
  iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x110));
  lVar5 = 0;
  if (*(int *)(iVar3 + 0x11c) != 0) {
    if (0 < *(int *)((u32)*(u8 *)(iVar3 + 0x14e) * 0x70 + 0x74b868)) {
      lVar2 = func_0016C040();
      if (lVar2 == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = 0x200;
      }
      if (*(char *)(iVar1 + 0x1c) == '\x02') {
        lVar5 = func_001C8780(0x1d,param_1,0x14,uVar4 | 0x10001);
      }
      if (lVar5 != 0) {
        func_001C8E80(lVar5);
      }
    }
  }
  return;
}

/* 0x0024B940, 0xCC bytes. */
void func_0024B940(void)
{
    u8 * iVar1;
    int iVar2;
    u8 * iVar3;
    u8 * iVar4;
    u8 * iVar5;
    int iVar6;

  
  iVar5 = g_00732508;
  iVar4 = g_00732220;
  iVar2 = 0;
  (*(u32 *)(g_00732508 + 0x0)) = 0;
  do {
    *(u32 *)(iVar5 + 4) = 0;
    iVar6 = 0;
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar4 + 0x2e0));
    iVar3 = iVar1;
    do {
      func_0024B790(iVar3);
      iVar6 = iVar6 + 1;
      iVar3 = iVar3 + 0x5d0;
    } while (iVar6 < 0x3d);
    func_001050B0(iVar1 + 0x18ad0);
    iVar2 = iVar2 + 1;
    *(unsigned long long *)(iVar1 + 0x18ae0) = 0xdf000001ff0000;
    iVar5 = iVar5 + 4;
    *(unsigned long long *)(iVar1 + 0x18ae8) = 0x41;
    iVar4 = iVar4 + 4;
  } while (iVar2 < 2);
  return;
}

/* 0x002BDE30, 0x1BC bytes. */
int func_002BDE30(u8 *param_1, int param_2)
{
    int bVar1;
    u8 * iVar7;
    u8 * iVar8;
    u8 * lVar5;
    u8 * pbVar3;
    int uVar2;
    u32 uVar4;
    u32 uVar6;

  
  iVar7 = param_1;
  uVar2 = func_001FF100(*(u16 *)(iVar7 + 0x54),10);
  pbVar3 = (u8 *)func_0027F120(uVar2);
  lVar5 = func_0027E660(param_1);
  if ((((lVar5 != 0) && (iVar8 = lVar5, *(char *)(iVar8 + 8) == '\0')) &&
      (*(char *)(iVar8 + 10) != -1)) && (lVar5 = func_002BBF40(), lVar5 != 0)) {
    func_002A5B10(*(u32 *)(lVar5 + 4));
    func_002BBF00(*(u8 *)(iVar8 + 10));
  }
  bVar1 = *pbVar3;
  func_0027E6A0(param_1);
  uVar6 = param_2 & 0xff;
  if (uVar6 == 3) {
    func_0027E730(param_1,1);
    *(u8 *)(iVar7 + 0x68) = 0;
    uVar4 = 1;
  }
  else if (uVar6 == 2) {
    func_0027E730(param_1,0);
    uVar4 = 1;
    *(u8 *)(iVar7 + 0x68) = 4;
  }
  else if (uVar6 == 1) {
    func_0027E730(param_1);
    lVar5 = func_0027E990(0,param_1,param_2);
    if (lVar5 == 0) {
      uVar4 = 0;
    }
    else {
      uVar2 = func_002BC110(param_1,*(u8 *)((u32)bVar1 * 0x20 + 0x7994f2));
      *(u8 *)(lVar5 + 10) = uVar2;
      uVar4 = 1;
    }
  }
  else if (uVar6 == 0) {
    func_0027E730(param_1,0);
    lVar5 = func_0027E990(0,param_1,param_2);
    if (lVar5 == 0) {
      uVar4 = 0;
    }
    else {
      *(u8 *)(iVar7 + 0x68) = 4;
      uVar2 = func_002BC110(param_1,*(u8 *)((u32)bVar1 * 0x20 + 0x7994f0));
      *(u8 *)(lVar5 + 10) = uVar2;
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

/* 0x002D7970, 0x160 bytes. */
void func_002D7970(u8 *param_1)
{
    u8 * iVar1;
    u8 * iVar7;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    int uVar6;

  
  iVar7 = param_1;
  if ((*(u32 *)(iVar7 + 0xbc) & 0x100000) == 0) {
    if (*(short *)(iVar7 + 0x78) == 0) {
      iVar1 = (u8 *)PS2_PTR(*(int *)(iVar7 + 0x14));
      *(u32 *)(iVar1 + 0x13c) = 0;
      uVar5 = g_700000CC;
      uVar4 = g_700000C8;
      uVar3 = g_700000C4;
      *(u32 *)(iVar1 + 0x1d0) = g_700000C0;
      *(u32 *)(iVar1 + 0x1d4) = uVar3;
      *(u32 *)(iVar1 + 0x1d8) = uVar4;
      *(u32 *)(iVar1 + 0x1dc) = uVar5;
      uVar2 = *(u32 *)(iVar7 + 0xbc);
      if ((uVar2 & 0x10000) == 0) {
        func_00204D00(param_1,1);
        *(u32 *)(iVar7 + 0xbc) = *(u32 *)(iVar7 + 0xbc) | 0x210000;
        *(u16 *)(iVar7 + 0x78) = 0x96;
        func_00204D20(param_1);
        func_00204DB0(param_1,1);
      }
      else if ((uVar2 & 0x200000) != 0) {
        *(u32 *)(iVar7 + 0xbc) = uVar2 & 0xffdfffff;
        *(u8 *)(iVar1 + 0x19e) = *(u8 *)(iVar1 + 0x19e) & 0x7f | 0x80;
        *(u8 *)(iVar1 + 0x198) = *(u8 *)(iVar1 + 0x198) & 0xdf | 0x20;
        *(u8 *)(iVar1 + 0x19e) = *(u8 *)(iVar1 + 0x19e) & 0xbf | 0x40;
        uVar6 = func_002D78E0();
        func_0027F160(uVar6,0);
        *(u32 *)(iVar7 + 0xbc) = *(u32 *)(iVar7 + 0xbc) | 0x4000000;
        *(u32 *)(*(int *)(iVar7 + 0x10) + 0x84) =
             *(u32 *)(*(int *)(iVar7 + 0x10) + 0x84) | 0x40002;
        func_00204D20(param_1);
      }
    }
    else {
      func_00204DB0(param_1,1);
    }
  }
  return;
}

/* 0x002EA9A0, 0x1A4 bytes. */
void func_002EA9A0(void)
{
    u8 * iVar1;
    u8 * iVar5;
    u8 * iVar6;
    u32 * puVar4;
    u32 uVar2;
    u32 uVar3;
    u32 uVar7;
    u32 uVar8;

  
  (*(unsigned long long *)(g_007A1B40 + 0x0)) = 0x1000000000008002;
  (*(unsigned long long *)(g_007A1B40 + 0x8)) = 0xe;
  (*(unsigned long long *)(g_007A1B40 + 0x18)) = 6;
  (*(unsigned long long *)(g_007A1B40 + 0x10)) = (*(unsigned long long *)(g_0040C558 + 0x0));
  uVar8 = 0;
  iVar6 = g_007A0640;
  (*(unsigned long long *)(g_007A1B40 + 0x20)) = 0x8000000048;
  (*(unsigned long long *)(g_007A1B40 + 0x28)) = 0x42;
  do {
    uVar7 = 0;
    iVar5 = iVar6;
    do {
      func_00118850(iVar5,0x380);
      uVar3 = 0;
      iVar1 = iVar5;
      do {
        puVar4 = (u32 *)(iVar1 + 0x20);
        if (uVar3 == 1) {
          *puVar4 = 0x40000000;
        }
        uVar2 = 0;
        do {
          *(unsigned long long *)(puVar4 + 4) = 0x302e400000008004;
          *(unsigned long long *)(puVar4 + 6) = 0x412;
          uVar2 = uVar2 + 1;
          puVar4[0x11] = 0xc1a00000;
          puVar4[0x1d] = 0x41a00000;
          puVar4[0x29] = 0xc1a00000;
          puVar4[0x35] = 0x41a00000;
          puVar4[0xc] = 0x80;
          puVar4[0xd] = 0x40;
          puVar4[0xe] = 0x40;
          puVar4[0xf] = 0x80;
          puVar4[0x18] = 0x80;
          puVar4[0x19] = 0x40;
          puVar4[0x1a] = 0x40;
          puVar4[0x1b] = 0x80;
          puVar4[0x24] = 0x80;
          puVar4[0x25] = 0x40;
          puVar4[0x26] = 0x40;
          puVar4[0x27] = 0x80;
          puVar4[0x30] = 0x80;
          puVar4[0x31] = 0x40;
          puVar4[0x32] = 0x40;
          puVar4[0x33] = 0x80;
          puVar4 = puVar4 + 0x34;
        } while (uVar2 < 2);
        uVar3 = uVar3 + 1;
        iVar1 = iVar1 + 0x1b0;
      } while (uVar3 < 2);
      uVar7 = uVar7 + 1;
      iVar5 = iVar5 + 0x380;
    } while (uVar7 < 3);
    uVar8 = uVar8 + 1;
    iVar6 = iVar6 + 0xa80;
  } while (uVar8 < 2);
  return;
}

/* 0x00320790, 0x23C bytes. */
void func_00320790(void)
{
    u8 auStack_10[16];
    u32 auStack_30[8];
    int bVar2;
    int iVar1;
    u8 * iVar3;
    u8 * iVar8;
    int iVar9;
    int lVar6;
    u8 * puVar7;
    int uVar4;
    int uVar5;

  
  iVar3 = func_002FC2C0();
  iVar3 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x694));
  uVar4 = func_0031D690(iVar3);
  uVar5 = func_00327D50();
  lVar6 = func_00314030(uVar4,uVar5);
  iVar1 = *(int *)(iVar3 + 0x20c);
  iVar9 = 0;
  if (0 < iVar1) {
    if (8 < iVar1) {
      bVar2 = false;
      if ((-1 < iVar1) && (iVar1 < 0x7fffffff)) {
        bVar2 = true;
      }
      if (bVar2) {
        puVar7 = auStack_10;
        iVar8 = iVar3;
        do {
          iVar9 = iVar9 + 8;
          *puVar7 = (char)*(u32 *)(iVar8 + 0x1b8);
          puVar7[1] = (char)*(u32 *)(iVar8 + 0x1bc);
          puVar7[2] = (char)*(u32 *)(iVar8 + 0x1c0);
          puVar7[3] = (char)*(u32 *)(iVar8 + 0x1c4);
          puVar7[4] = (char)*(u32 *)(iVar8 + 0x1c8);
          puVar7[5] = (char)*(u32 *)(iVar8 + 0x1cc);
          puVar7[6] = (char)*(u32 *)(iVar8 + 0x1d0);
          puVar7[7] = (char)*(u32 *)(iVar8 + 0x1d4);
          iVar8 = iVar8 + 0x20;
          puVar7 = puVar7 + 8;
        } while (iVar9 < iVar1 + -8);
      }
    }
    if (iVar9 < iVar1) {
      iVar8 = iVar3 + iVar9 * 4;
      puVar7 = auStack_10 + iVar9;
      do {
        iVar9 = iVar9 + 1;
        *puVar7 = (char)*(u32 *)(iVar8 + 0x1b8);
        iVar8 = iVar8 + 4;
        puVar7 = puVar7 + 1;
      } while (iVar9 < iVar1);
    }
  }
  func_003DC180(0x10,0,auStack_30);
  uVar4 = func_0030D7D0();
  func_003821E0(uVar4,*(u32 *)(iVar3 + 0x214),auStack_30[0],0x50,auStack_10,iVar1);
  func_003DC180(0x11,0,auStack_30);
  uVar4 = func_0030D7D0();
  uVar5 = func_0031D690(iVar3);
  func_0037E9F0(uVar4,uVar5,auStack_30[0],0x68,0x80,lVar6 != 0);
  uVar4 = func_0031D690(iVar3);
  uVar5 = func_00327D50();
  lVar6 = func_00313DB0(uVar4,uVar5);
  if (lVar6 < 0) {
    lVar6 = 0;
  }
  uVar4 = func_0030D7D0();
  func_00383050(uVar4,0x141,0x34,0,1,lVar6);
  uVar4 = func_0031D690(iVar3);
  uVar5 = func_00327D50();
  lVar6 = func_0031DFE0(uVar4,uVar5);
  if (-1 < lVar6) {
    uVar4 = func_003725A0();
    func_003838B0(uVar4,1);
  }
  return;
}

/* 0x003223E0, 0x200 bytes. */
int func_003223E0(void)
{
    int iVar1;
    u8 * iVar2;
    int lVar4;
    u8 * uVar3;
    int uVar5;
    int uVar6;
    u32 uVar7;

  
  uVar7 = 5;
  func_002F7B10();
  uVar3 = func_00320F00();
  iVar2 = uVar3;
  iVar1 = *(int *)(iVar2 + 8);
  if (iVar1 == 0) {
    lVar4 = func_003225E0(iVar2 + 0x10,iVar2 + 0x14,iVar2 + 0x18);
    if (lVar4 == 0) {
      *(u32 *)(iVar2 + 8) = 0;
      *(u32 *)(iVar2 + 0xc) = 0;
      return 0;
    }
    func_00322780(g_0045D6A4);
    lVar4 = func_00327CC0();
    if (lVar4 == 3) {
      func_00322850(g_0045D6A8);
    }
    *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
  }
  else {
    if (iVar1 == 1) {
      uVar7 = *(u32 *)(iVar2 + 0xc);
      lVar4 = func_002F8CB0(uVar7);
      if (lVar4 == 0) {
        func_003223A0(uVar3);
        return 5;
      }
      lVar4 = func_002FB2A0(uVar7);
      if (lVar4 == 0) {
        uVar5 = func_002F7D90(0,0x2f8160,uVar7,0,0,0);
        uVar6 = func_002F7B10();
        func_003228F0(uVar7,*(u32 *)(iVar2 + 0x10),*(u32 *)(iVar2 + 0x14),
                     *(u32 *)(iVar2 + 0x18),uVar5,uVar6);
        uVar6 = func_002F7B10();
        func_00322B00(uVar5,uVar6);
        func_00322C70(uVar7,0x19f,g_0045D6A4);
        func_00323040(uVar7);
        func_003223A0(uVar3);
        return 5;
      }
      func_003223A0(uVar3);
      return 5;
    }
    if (iVar1 == 2) {
      uVar7 = *(u32 *)(iVar2 + 0xc);
      lVar4 = func_002F8CB0(uVar7);
      if (lVar4 == 0) {
        func_003223A0(uVar3);
        return 5;
      }
      lVar4 = func_002FB2A0(uVar7);
      if (lVar4 == 0) {
        func_00322E80(uVar7,0x19f,g_0045D6A8);
        func_003223A0(uVar3);
        return 5;
      }
      func_003223A0(uVar3);
      return 5;
    }
    if (iVar1 == 3) {
      *(u32 *)(iVar2 + 8) = 0;
      uVar7 = 0;
      *(u32 *)(iVar2 + 0xc) = 0;
    }
  }
  return uVar7;
}

/* 0x003239F0, 0x1D0 bytes. */
void func_003239F0(u8 *param_1, int param_2)
{
    int bVar1;
    int iStack_8;
    int iVar4;
    u8 * iVar5;
    int lVar2;
    int lVar3;
    u32 uStack_4;

  
  func_00327D50();
  func_0011ED38(param_1,0,100);
  iVar4 = 0;
  do {
    lVar2 = func_00329160(iVar4,&uStack_4,&iStack_8);
    if (lVar2 != 0) {
      iVar5 = param_1;
      if (param_2 == 3) {
        lVar2 = func_0030AFF0(iStack_8);
        bVar1 = false;
        if (-1 < lVar2) {
          lVar3 = func_0030AB90();
          bVar1 = lVar2 < lVar3;
        }
        if (((bVar1) && (lVar2 = func_00328FA0(lVar2), lVar2 != 0)) &&
           (lVar2 = func_003238D0(iStack_8), lVar2 == 0)) {
          *(u32 *)(iVar5 + iStack_8 * 4) = 1;
        }
      }
      else if (param_2 == 2) {
        lVar2 = func_0030AFF0(uStack_4);
        bVar1 = false;
        if (-1 < lVar2) {
          lVar3 = func_0030AB90();
          bVar1 = lVar2 < lVar3;
        }
        if (((bVar1) && (lVar2 = func_00328DE0(lVar2), lVar2 != 0)) &&
           (lVar2 = func_003238D0(iStack_8), lVar2 == 0)) {
          *(u32 *)(iVar5 + iStack_8 * 4) = 1;
        }
      }
      else if (param_2 == 1) {
        lVar2 = func_0030AFF0(iStack_8);
        bVar1 = false;
        if (-1 < lVar2) {
          lVar3 = func_0030AB90();
          bVar1 = lVar2 < lVar3;
        }
        if ((bVar1) && (lVar2 = func_002FB2A0(lVar2), lVar2 != 0)) {
          *(u32 *)(iVar5 + iStack_8 * 4) = 1;
        }
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0xc);
  return;
}

/* 0x0038A5D0, 0x320 bytes. */
int func_0038A5D0(u8 *param_1)
{
    u8 * iVar1;
    int iVar2;
    u8 * iVar6;
    int lVar4;
    u32 uStack_10;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    u32 uStack_4;
    u32 uStack_8;
    int uVar3;
    int uVar5;

  
  iVar6 = param_1;
  iVar2 = *(int *)(iVar6 + 0x690);
  iVar1 = iVar6 + *(int *)(iVar6 + 0x68c) * 0x184;
  if (iVar2 == 0) {
    uVar3 = func_00389D20(*(u32 *)(iVar6 + 8));
    func_0030E140(uVar3,0xffffffffffffffff,0xffffffffffffffff,1);
    return 0;
  }
  if (iVar2 == 1) {
    lVar4 = func_0030E1F0();
    if (lVar4 == 2) {
      func_0030E100();
    }
    iVar2 = func_00389D20(*(u32 *)(iVar6 + 8));
    func_0030E140(iVar2 + 1,0xffffffffffffffff,0xffffffffffffffff,1);
    return 0;
  }
  if (iVar2 == 2) {
    lVar4 = func_0030E1F0();
    if (lVar4 == 2) {
      func_0030E100();
    }
    uStack_20 = 0;
    uStack_1c = 0x40;
    uStack_10 = 0x80;
    uStack_18 = 0x200;
    uVar3 = func_0030D7D0();
    func_00389E40(param_1,uVar3,0xffffffffffffffff);
    func_003DB220(0xc,&uStack_20);
    func_003DB460(0xc,1);
    return 0;
  }
  if (iVar2 == 3) {
    func_003DB480(0xc);
    return 0;
  }
  lVar4 = func_0038A010(param_1,&uStack_4,&uStack_8,iVar1 + 0x80);
  if (lVar4 != 0) {
    func_00389B40(uStack_4,uStack_8,iVar1 + 0x80);
    return 0;
  }
  lVar4 = func_0038A330(param_1);
  if (lVar4 != 0) {
    lVar4 = func_0030E1F0();
    if (lVar4 == 2) {
      func_0030E100();
    }
    uStack_1c = 0x40;
    uStack_20 = 0;
    uStack_10 = 0x80;
    uStack_18 = 0x200;
    func_003DB220(0xc,&uStack_20);
    func_003DB460(0xc,1);
    if (*(int *)(iVar1 + 0xb8) == 6) {
      uVar3 = func_00390760(0x31);
      uVar5 = func_002F2890(*(u32 *)(iVar1 + 0xd4));
      func_001204B0(iVar1 + 0xfc,uVar3,uVar5);
      func_0030E390(0x13,*(u32 *)(iVar6 + 8),0xffffffffffffffff,0xffffffffffffffff,0,0);
      return 0;
    }
    return 0;
  }
  lVar4 = func_0038A3D0(param_1);
  if (lVar4 == 0) {
    return 0;
  }
  func_003DB480(0xc,2);
  iVar2 = *(int *)(iVar1 + 0xb8) + 1;
  *(int *)(iVar1 + 0xb8) = iVar2;
  if (6 < iVar2) {
    iVar2 = *(int *)(iVar6 + 8);
    if (iVar2 == 0x2a) {
      func_003BA8F0(0x14,*(u32 *)(iVar1 + 0xd4),0xffffffffffffffff,0xffffffffffffffff,
                   0xffffffffffffffff);
    }
    else if (iVar2 == 0x29) {
      func_003BA8F0(0x16,*(u32 *)(iVar1 + 0xd4),0xffffffffffffffff,0xffffffffffffffff,
                   0xffffffffffffffff);
    }
    else {
      if (iVar2 != 0x28) {
        *(u32 *)(iVar1 + 0xb8) = 0;
        goto LAB_0038a8c0;
      }
      func_003BA8F0(0x15,*(u32 *)(iVar1 + 0xd4),0xffffffffffffffff,0xffffffffffffffff,
                   0xffffffffffffffff);
    }
    *(u32 *)(iVar1 + 0xb8) = 0;
  }
LAB_0038a8c0:
  *(u32 *)(iVar1 + 0x88) = 0x19f;
  *(u32 *)(iVar1 + 0x8c) = 0x19f;
  return 0;
}

/* 0x0039CA60, 0x3E8 bytes. */
void func_0039CA60(void)
{
    u8 * iVar2;
    int lVar3;
    int sVar1;
    int uVar4;
    int uVar5;

  
  iVar2 = func_002FC2C0();
  iVar2 = (u8 *)PS2_PTR(*(int *)(iVar2 + 0x6ac));
  lVar3 = func_003DC2D0(0xc);
  if (lVar3 == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x0));
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = (*(u16 *)(g_0050074C + 0x2));
    }
    if (*(int *)(iVar2 + 4) == 1) {
      lVar3 = func_0039C9E0();
      if ((uVar4 & 0x10) == 0) {
        if ((uVar5 & 0x1000) == 0) {
          if (((uVar5 & 0x4000) != 0) && (lVar3 != 1)) {
            if (*(int *)(iVar2 + 8) == (int)lVar3 + -1) {
              if ((uVar4 & 0x4000) != 0) {
                *(u32 *)(iVar2 + 8) = 0;
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              }
            }
            else {
              *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            }
          }
        }
        else if (lVar3 != 1) {
          if (*(int *)(iVar2 + 8) == 0) {
            if ((uVar4 & 0x1000) != 0) {
              *(int *)(iVar2 + 8) = (int)lVar3 + -1;
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            }
          }
          else {
            *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + -1;
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          }
        }
      }
      else {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        *(u32 *)(iVar2 + 8) = 0xffffffff;
        *(u32 *)(iVar2 + 4) = 0;
      }
    }
    else if (*(int *)(iVar2 + 4) == 0) {
      if ((uVar4 & 0x40) == 0) {
        if ((uVar4 & 0x10) == 0) {
          if ((uVar5 & 0x1000) == 0) {
            if ((uVar5 & 0x4000) != 0) {
              if ((int)*(short *)(iVar2 + 0x1c) == 0x1d) {
                if ((uVar4 & 0x4000) != 0) {
                  *(u16 *)(iVar2 + 0x1e) = 0;
                  *(u16 *)(iVar2 + 0x1c) = 0;
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                }
              }
              else {
                if (((int)*(short *)(iVar2 + 0x1c) == (int)(*(short *)(iVar2 + 0x1e) + 9)) &&
                   (sVar1 = *(short *)(iVar2 + 0x1e) + 1, *(short *)(iVar2 + 0x1e) = sVar1,
                   0x14 < sVar1)) {
                  *(u16 *)(iVar2 + 0x1e) = 0x14;
                }
                *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) + 1;
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              }
            }
          }
          else if (*(short *)(iVar2 + 0x1c) == 0) {
            if ((uVar4 & 0x1000) != 0) {
              *(u16 *)(iVar2 + 0x1e) = 0x14;
              *(u16 *)(iVar2 + 0x1c) = 0x1d;
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            }
          }
          else {
            if ((*(short *)(iVar2 + 0x1c) == *(short *)(iVar2 + 0x1e)) &&
               (sVar1 = *(short *)(iVar2 + 0x1e) + -1, *(short *)(iVar2 + 0x1e) = sVar1, sVar1 < 0))
            {
              *(u16 *)(iVar2 + 0x1e) = 0;
            }
            *(short *)(iVar2 + 0x1c) = *(short *)(iVar2 + 0x1c) + -1;
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          }
        }
        else {
          func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
          *(u32 *)(iVar2 + 8) = 0xffffffff;
          *(u16 *)(iVar2 + 0x1e) = 0xffff;
          *(u16 *)(iVar2 + 0x1c) = 0xffff;
          func_0039C740();
        }
      }
      else {
        func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
        *(u32 *)(iVar2 + 8) = 0;
        *(u32 *)(iVar2 + 4) = 1;
      }
    }
  }
  return;
}
