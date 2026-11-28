/*
 * gen9_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_00669D81[0x1];
extern u8 g_00669DB8[0x4];
extern u8 g_0068F0F8[0x8];
extern u8 g_0072D0F0[0x3C];
extern u8 g_0072D0F8[0x2C];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D410;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_700001D0 (*(int *)PS2_PTR(0x700001D0))   /* (scratchpad) */
#define g_700001D4 (*(int *)PS2_PTR(0x700001D4))   /* (scratchpad) */
#define g_700001D8 (*(int *)PS2_PTR(0x700001D8))   /* (scratchpad) */
#define g_700001DC (*(int *)PS2_PTR(0x700001DC))   /* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))   /* (scratchpad) */

void *func_00102D30();
void *func_00102DB0();
int func_00102EC0();
int func_00106C90();
void *func_00106F10();
int func_00118850();
int func_001C6830();
void *func_001F14E0();
int func_00206080();
int func_00238AE0();
int func_00239980();
int func_002399E0();
int func_00253480();
void func_001C6960(void);
void func_001C6AC0(void);
void func_001C6C80(void);
void func_001C6E40(void);
void func_001C6FA0(void);
void func_001F6FF0(void);
void func_001F70A0(int param_1, int param_2, int param_3);
void func_00239AD0(u8 *param_1);
void func_002A9660(int param_1, u8 *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002B55E0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002B59D0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002B5D70(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002C66A0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002C7410(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002C81D0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002C8BC0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002C9D30(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002CA160(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);

/* 0x001C6960, 0x158 bytes, matching. */
void func_001C6960(void)
{
  func_00253480();
  if ((*(u32 *)(g_0072D0F0 + 0x14)) != 0) {
    g_70000D60 = 5;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x8)) != 0) {
    g_70000D60 = 2;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x0)) != 0) {
    g_70000D60 = 0;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x4)) != 0) {
    g_70000D60 = 1;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x34)) != 0) {
    g_70000D60 = 0xd;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x18)) != 0) {
    g_70000D60 = 6;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x28)) != 0) {
    g_70000D60 = 10;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x38)) != 0) {
    g_70000D60 = 0xe;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x10)) != 0) {
    g_70000D60 = 4;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0xC)) != 0) {
    g_70000D60 = 3;
    func_001C6830();
  }
  return;
}

/* 0x001C6AC0, 0x1B8 bytes, matching. */
void func_001C6AC0(void)
{
  func_00253480();
  if ((*(u32 *)(g_0072D0F0 + 0x14)) != 0) {
    g_70000D60 = 5;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x1C)) != 0) {
    g_70000D60 = 7;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x24)) != 0) {
    g_70000D60 = 9;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x20)) != 0) {
    g_70000D60 = 8;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x8)) != 0) {
    g_70000D60 = 2;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x0)) != 0) {
    g_70000D60 = 0;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x4)) != 0) {
    g_70000D60 = 1;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x34)) != 0) {
    g_70000D60 = 0xd;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x18)) != 0) {
    g_70000D60 = 6;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x28)) != 0) {
    g_70000D60 = 10;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x38)) != 0) {
    g_70000D60 = 0xe;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x10)) != 0) {
    g_70000D60 = 4;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0xC)) != 0) {
    g_70000D60 = 3;
    func_001C6830();
  }
  return;
}

/* 0x001C6C80, 0x1B8 bytes, matching. */
void func_001C6C80(void)
{
  func_00253480();
  if ((*(u32 *)(g_0072D0F0 + 0x1C)) != 0) {
    g_70000D60 = 7;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x20)) != 0) {
    g_70000D60 = 8;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x8)) != 0) {
    g_70000D60 = 2;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x0)) != 0) {
    g_70000D60 = 0;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x4)) != 0) {
    g_70000D60 = 1;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x34)) != 0) {
    g_70000D60 = 0xd;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x14)) != 0) {
    g_70000D60 = 5;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x24)) != 0) {
    g_70000D60 = 9;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x18)) != 0) {
    g_70000D60 = 6;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x28)) != 0) {
    g_70000D60 = 10;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x38)) != 0) {
    g_70000D60 = 0xe;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x10)) != 0) {
    g_70000D60 = 4;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0xC)) != 0) {
    g_70000D60 = 3;
    func_001C6830();
  }
  return;
}

/* 0x001C6E40, 0x158 bytes, matching. */
void func_001C6E40(void)
{
  func_00253480();
  if ((*(u32 *)(g_0072D0F0 + 0x24)) != 0) {
    g_70000D60 = 9;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x8)) != 0) {
    g_70000D60 = 2;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x0)) != 0) {
    g_70000D60 = 0;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x4)) != 0) {
    g_70000D60 = 1;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x34)) != 0) {
    g_70000D60 = 0xd;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x18)) != 0) {
    g_70000D60 = 6;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x28)) != 0) {
    g_70000D60 = 10;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x38)) != 0) {
    g_70000D60 = 0xe;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0x10)) != 0) {
    g_70000D60 = 4;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F0 + 0xC)) != 0) {
    g_70000D60 = 3;
    func_001C6830();
  }
  return;
}

/* 0x001C6FA0, 0xB4 bytes, matching. */
void func_001C6FA0(void)
{
  if ((*(u32 *)(g_0072D0F8 + 0x0)) != 0) {
    g_70000D60 = 2;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F8 + 0x8)) != 0) {
    g_70000D60 = 4;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F8 + 0x20)) != 0) {
    g_70000D60 = 10;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F8 + 0x24)) != 0) {
    g_70000D60 = 0xb;
    func_001C6830();
  }
  if ((*(u32 *)(g_0072D0F8 + 0x28)) != 0) {
    g_70000D60 = 0xc;
    func_001C6830();
  }
  return;
}

/* 0x001F6FF0, 0xAC bytes. */
void func_001F6FF0(void)
{
  if (g_0045D410 != 0) {
    func_00102EC0();
    g_0045D410 = 0;
  }
  if (g_700001DC != 0) {
    func_00102EC0();
    g_700001DC = 0;
  }
  if (g_700001D8 != 0) {
    func_00102EC0();
    g_700001D8 = 0;
  }
  if (g_700001D4 != 0) {
    func_00102EC0();
    g_700001D4 = 0;
  }
  if (g_700001D0 != 0) {
    func_00102EC0();
    g_700001D0 = 0;
  }
  return;
}

/* 0x001F70A0, 0x118 bytes. */
void func_001F70A0(int param_1, int param_2, int param_3)
{
    u32 uVar1;

  
  uVar1 = (param_1 * 2 + 7U >> 3) + 0xf & 0xfffffff0;
  if ((*(u32 *)(g_00669DB8 + 0x0)) != 2) {
    g_700001D0 = PS2_ADDR(func_00102D30(param_1 * 0x70));
    g_700001D4 = PS2_ADDR(func_00102DB0(0x10,param_3 << 5));
    g_700001D8 = PS2_ADDR(func_00102D30(param_2 << 3));
    g_700001DC = PS2_ADDR(func_00102D30(0x9c4));
    g_0045D410 = PS2_ADDR(func_00102DB0(0x10,uVar1));
  }
  func_00118850(g_700001D0,param_1 * 0x70);
  func_00118850(g_700001D8,param_2 << 3);
  func_00118850(g_700001D4,param_3 << 5);
  func_00118850(g_700001DC,0x9c4);
  func_00118850(g_0045D410,uVar1);
  return;
}

/* 0x00239AD0, 0x1A4 bytes. */
void func_00239AD0(u8 *param_1)
{
    u8 * iVar2;
    u8 * pbVar1;

  
  pbVar1 = (u8 *)func_001F14E0();
  iVar2 = param_1;
  if ((long long)*(char *)(*(int *)(iVar2 + 0x14) + 0x19d) << 0x3c < 0) {
    if ((*(u8 *)(*(int *)(iVar2 + 0x14) + 0xe8) & 1) != 0) {
      func_00239980(param_1);
      return;
    }
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[1]) {
      func_00239980(param_1);
      return;
    }
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if (((g_7000015C >> 0x10) % 100 < (u32)*pbVar1) ||
       (g_7000015C = g_7000015C * 0x41c64e6d + 0x3039,
       (g_7000015C >> 0x10) % 100 < (u32)pbVar1[3])) {
      func_00238AE0(param_1,0x5a);
      *(u32 *)(iVar2 + 0x90) = 0x41c00000;
      *(u8 *)(iVar2 + 0xa9) = 1;
      return;
    }
  }
  else {
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < ((*(u8 *)(g_00669D81 + 0x0)) + 2) * ((*(u8 *)(g_00669D81 + 0x0)) + 2) * 2) {
      func_002399E0(param_1);
      return;
    }
  }
  func_00206080(param_1);
  return;
}

/* 0x002A9660, 0x6AC bytes. */
void func_002A9660(int param_1, u8 *param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar2;
    int iVar5;
    int iVar8;
    unsigned long long uVar1;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar6;
    unsigned long long uVar7;
    unsigned long long uVar9;

  
  func_00106F10();
  uVar9 = (long long)param_8 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_2 + 0x20) = uVar9;
  *(unsigned long long *)(param_2 + 0x28) = 0x80008;
  *(unsigned long long *)(param_2 + 0x38) = 0x880108;
  iVar2 = ((param_4 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar8 = (iVar2 >> 9) * 0x10 + -0xe00;
  uVar7 = (unsigned long long)(param_3 * 0x10 + 0x7000);
  uVar6 = (long long)(0xfffe - param_5) << 0x20;
  *(unsigned long long *)(param_2 + 0x30) = uVar6 | uVar7 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  iVar2 = (((param_4 + 8) * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar5 = (iVar2 >> 9) * 0x10 + -0xe00;
  uVar4 = (unsigned long long)((param_3 + 0x10) * 0x10 + 0x7000);
  uVar3 = (unsigned long long)((param_3 + 0x10 + param_6) * 0x10 + 0x7000);
  uVar1 = (unsigned long long)((param_3 + 0x18 + param_6) * 0x10 + 0x7000);
  *(unsigned long long *)(param_2 + 0x40) = uVar6 | uVar4 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x70) = uVar9;
  *(unsigned long long *)(param_2 + 0x78) = 0x80108;
  *(unsigned long long *)(param_2 + 0x88) = 0x880188;
  *(unsigned long long *)(param_2 + 0x80) = uVar6 | uVar4 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x90) = uVar6 | uVar3 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0xc0) = uVar9;
  *(unsigned long long *)(param_2 + 200) = 0x80188;
  *(unsigned long long *)(param_2 + 0xd8) = 0x880208;
  *(unsigned long long *)(param_2 + 0xd0) = uVar6 | uVar3 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0xe0) = uVar6 | uVar1 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x110) = uVar9;
  *(unsigned long long *)(param_2 + 0x118) = 0x880008;
  *(unsigned long long *)(param_2 + 0x128) = 0x1480108;
  iVar2 = (((param_4 + -4 + param_7) * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  *(unsigned long long *)(param_2 + 0x120) =
       uVar6 | uVar7 | (long long)(((iVar2 >> 9) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  iVar2 = (((param_4 + 8 + param_7) * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar8 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_2 + 0x130) = uVar6 | uVar4 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x160) = uVar9;
  *(unsigned long long *)(param_2 + 0x168) = 0x880108;
  *(unsigned long long *)(param_2 + 0x178) = 0x1480188;
  *(unsigned long long *)(param_2 + 0x170) = uVar6 | uVar4 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x180) = uVar6 | uVar3 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x1b0) = uVar9;
  *(unsigned long long *)(param_2 + 0x1b8) = 0x880188;
  *(unsigned long long *)(param_2 + 0x1c8) = 0x1480208;
  *(unsigned long long *)(param_2 + 0x1c0) = uVar6 | uVar3 | (long long)(iVar5 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x1d0) = uVar6 | uVar1 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x200) = uVar9;
  *(unsigned long long *)(param_2 + 0x208) = 0x1480008;
  *(unsigned long long *)(param_2 + 0x218) = 0x1c80108;
  iVar2 = (((param_4 + 0x10 + param_7) * 0x280) / 0x1e0) * 0x1c0;
  *(unsigned long long *)(param_2 + 0x210) = uVar6 | uVar7 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar2 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_2 + 0x220) = uVar6 | uVar4 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x250) = uVar9;
  *(unsigned long long *)(param_2 + 600) = 0x1480108;
  *(unsigned long long *)(param_2 + 0x268) = 0x1c80188;
  *(unsigned long long *)(param_2 + 0x260) = uVar6 | uVar4 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x270) = uVar6 | uVar3 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x2a0) = uVar9;
  *(unsigned long long *)(param_2 + 0x2a8) = 0x1480188;
  *(unsigned long long *)(param_2 + 0x2b8) = 0x1c80208;
  *(unsigned long long *)(param_2 + 0x2b0) = uVar6 | uVar3 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_2 + 0x2c0) = uVar6 | uVar1 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002B55E0, 0x288 bytes. */
void func_002B55E0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar1;
    int iVar2;
    int iVar6;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar7;

  
  iVar1 = ((param_4 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1ff;
  }
  iVar2 = ((param_7 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar6 = (iVar1 >> 9) * 0x10 + -0xe00;
  iVar1 = ((iVar2 >> 9) + (iVar1 >> 9)) * 0x10 + -0xe00;
  uVar7 = (long long)param_8 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar7;
  *(unsigned long long *)(param_1 + 0x28) = 0x80008;
  *(unsigned long long *)(param_1 + 0x38) = 0x880188;
  uVar5 = (long long)(0xfffe - param_5) << 0x20;
  *(unsigned long long *)(param_1 + 0x30) =
       uVar5 | (long long)(param_3 * 0x10 + 0x7000) | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  uVar4 = (unsigned long long)((param_3 + 0x18) * 0x10 + 0x7000);
  uVar3 = (unsigned long long)((param_6 + -0x30 + param_3 + 0x18) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x40) = uVar5 | uVar4 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x70) = uVar7;
  *(unsigned long long *)(param_1 + 0x78) = 0x80188;
  *(unsigned long long *)(param_1 + 0x88) = 0x880208;
  *(unsigned long long *)(param_1 + 0x80) = uVar5 | uVar4 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar5 | uVar3 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xc0) = uVar7;
  *(unsigned long long *)(param_1 + 200) = 0x80208;
  *(unsigned long long *)(param_1 + 0xd8) = 0x880388;
  *(unsigned long long *)(param_1 + 0xd0) = uVar5 | uVar3 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar5 | (long long)((param_3 + 0x30 + param_6 + -0x30) * 0x10 + 0x7000) |
               (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002B59D0, 0x288 bytes. */
void func_002B59D0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar1;
    int iVar2;
    int iVar6;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar7;

  
  iVar1 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1ff;
  }
  iVar2 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar6 = (iVar1 >> 9) * 0x10 + -0xe00;
  iVar1 = ((iVar2 >> 9) + (iVar1 >> 9)) * 0x10 + -0xe00;
  uVar7 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar7;
  *(unsigned long long *)(param_1 + 0x28) = 0x80008;
  *(unsigned long long *)(param_1 + 0x38) = 0x3f80208;
  uVar5 = (long long)(0xfffe - param_4) << 0x20;
  uVar4 = (unsigned long long)((param_2 + 0x20) * 0x10 + 0x7000);
  uVar3 = (unsigned long long)((param_5 + -0x40 + param_2 + 0x20) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar5 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar5 | uVar4 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x70) = uVar7;
  *(unsigned long long *)(param_1 + 0x78) = 0x80208;
  *(unsigned long long *)(param_1 + 0x88) = 0x3f804e8;
  *(unsigned long long *)(param_1 + 0x80) = uVar5 | uVar4 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar5 | uVar3 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xc0) = uVar7;
  *(unsigned long long *)(param_1 + 200) = 0x804e8;
  *(unsigned long long *)(param_1 + 0xd8) = 0x3f806e8;
  *(unsigned long long *)(param_1 + 0xd0) = uVar5 | uVar3 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar5 | (long long)((param_2 + 0x40 + param_5 + -0x40) * 0x10 + 0x7000) |
               (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002B5D70, 0x288 bytes. */
void func_002B5D70(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar1;
    int iVar2;
    int iVar6;
    unsigned long long uVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar7;

  
  iVar1 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1ff;
  }
  iVar2 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar6 = (iVar1 >> 9) * 0x10 + -0xe00;
  iVar1 = ((iVar2 >> 9) + (iVar1 >> 9)) * 0x10 + -0xe00;
  uVar7 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar7;
  *(unsigned long long *)(param_1 + 0x28) = 0x80008;
  *(unsigned long long *)(param_1 + 0x38) = 0x1c80088;
  uVar5 = (long long)(0xfffe - param_4) << 0x20;
  uVar4 = (unsigned long long)((param_2 + 8) * 0x10 + 0x7000);
  uVar3 = (unsigned long long)((param_5 + -0x10 + param_2 + 8) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar5 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar5 | uVar4 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x70) = uVar7;
  *(unsigned long long *)(param_1 + 0x78) = 0x80088;
  *(unsigned long long *)(param_1 + 0x88) = 0x1c80108;
  *(unsigned long long *)(param_1 + 0x80) = uVar5 | uVar4 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar5 | uVar3 | (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xc0) = uVar7;
  *(unsigned long long *)(param_1 + 200) = 0x80108;
  *(unsigned long long *)(param_1 + 0xd8) = 0x1c80188;
  *(unsigned long long *)(param_1 + 0xd0) = uVar5 | uVar3 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar5 | (long long)((param_2 + 0x10 + param_5 + -0x10) * 0x10 + 0x7000) |
               (long long)(iVar1 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002C66A0, 0x32C bytes. */
void func_002C66A0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar7;
    unsigned long long uVar1;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar8;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5b);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0x20) {
    param_5 = 0x20;
  }
  if (iVar3 < 0x10) {
    iVar3 = 0x10;
  }
  iVar7 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  iVar3 = (iVar3 + (iVar2 >> 9)) * 0x10 + -0xe00;
  iVar2 = (int)param_5 + -0x20;
  uVar8 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar8;
  *(unsigned long long *)(param_1 + 0x28) = 0x7880008;
  *(unsigned long long *)(param_1 + 0x38) = 0x9080108;
  uVar6 = (long long)(0xfffe - param_4) << 0x20;
  uVar5 = (unsigned long long)((param_2 + 0x10) * 0x10 + 0x7000);
  uVar4 = (unsigned long long)((iVar2 + param_2 + 0x10) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar6 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar6 | uVar5 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar8;
  *(unsigned long long *)(param_1 + 0x78) = 0x7880108;
  *(unsigned long long *)(param_1 + 0x88) = 0x9080188;
  *(unsigned long long *)(param_1 + 0x80) = uVar6 | uVar5 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar6 | uVar4 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar8;
  *(unsigned long long *)(param_1 + 200) = 0x7880188;
  *(unsigned long long *)(param_1 + 0xd8) = 0x9080288;
  *(unsigned long long *)(param_1 + 0xd0) = uVar6 | uVar4 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar6 | (long long)((param_2 + 0x20 + iVar2) * 0x10 + 0x7000) |
               (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002C7410, 0x614 bytes. */
void func_002C7410(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar13;
    int iVar2;
    int iVar3;
    int iVar6;
    int iVar8;
    int iVar9;
    unsigned long long uVar1;
    unsigned long long uVar10;
    unsigned long long uVar11;
    unsigned long long uVar12;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar7;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5f);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar2 = iVar2 >> 9;
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0x20) {
    param_5 = 0x20;
  }
  if (iVar3 < 0x10) {
    iVar3 = 0x10;
  }
  iVar13 = (iVar2 + 8) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  uVar7 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar7;
  *(unsigned long long *)(param_1 + 0x28) = 0x4880d08;
  iVar8 = (int)param_5 + -0x20;
  *(unsigned long long *)(param_1 + 0x38) = 0x5080e08;
  iVar6 = iVar2 * 0x10 + -0xe00;
  uVar5 = (unsigned long long)(param_2 * 0x10 + 0x7000);
  uVar4 = (long long)(0xfffe - param_4) << 0x20;
  uVar12 = (unsigned long long)((param_2 + 0x10) * 0x10 + 0x7000);
  uVar11 = (unsigned long long)((iVar8 + param_2 + 0x10) * 0x10 + 0x7000);
  uVar10 = (unsigned long long)((param_2 + 0x20 + iVar8) * 0x10 + 0x7000);
  iVar9 = (iVar3 + -0x10 + iVar2 + 8) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x30) = uVar4 | uVar5 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  iVar8 = (iVar2 + iVar3 + -8) * 0x10 + -0xe00;
  iVar2 = (iVar2 + iVar3) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x40) = uVar4 | uVar12 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar7;
  *(unsigned long long *)(param_1 + 0x78) = 0x4880e08;
  *(unsigned long long *)(param_1 + 0x88) = 0x5080e88;
  *(unsigned long long *)(param_1 + 0x80) = uVar4 | uVar12 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar4 | uVar11 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar7;
  *(unsigned long long *)(param_1 + 200) = 0x4880e88;
  *(unsigned long long *)(param_1 + 0xd8) = 0x5080f88;
  *(unsigned long long *)(param_1 + 0xd0) = uVar4 | uVar11 | (long long)(iVar6 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) = uVar4 | uVar10 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x108) = uVar1;
  *(unsigned long long *)(param_1 + 0x110) = uVar7;
  *(unsigned long long *)(param_1 + 0x118) = 0x5080d08;
  *(unsigned long long *)(param_1 + 0x128) = 0x5880e08;
  *(unsigned long long *)(param_1 + 0x120) = uVar4 | uVar5 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x130) = uVar4 | uVar12 | (long long)(iVar9 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x158) = uVar1;
  *(unsigned long long *)(param_1 + 0x160) = uVar7;
  *(unsigned long long *)(param_1 + 0x168) = 0x5080e08;
  *(unsigned long long *)(param_1 + 0x178) = 0x5880e88;
  *(unsigned long long *)(param_1 + 0x170) = uVar4 | uVar12 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x180) = uVar4 | uVar11 | (long long)(iVar9 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x1a8) = uVar1;
  *(unsigned long long *)(param_1 + 0x1b0) = uVar7;
  *(unsigned long long *)(param_1 + 0x1b8) = 0x5080e88;
  *(unsigned long long *)(param_1 + 0x1c8) = 0x5880f88;
  *(unsigned long long *)(param_1 + 0x1c0) = uVar4 | uVar11 | (long long)(iVar13 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x1d0) = uVar4 | uVar10 | (long long)(iVar9 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x1f8) = uVar1;
  *(unsigned long long *)(param_1 + 0x200) = uVar7;
  *(unsigned long long *)(param_1 + 0x208) = 0x5880d08;
  *(unsigned long long *)(param_1 + 0x218) = 0x6080e08;
  *(unsigned long long *)(param_1 + 0x210) = uVar4 | uVar5 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x220) = uVar4 | uVar12 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x248) = uVar1;
  *(unsigned long long *)(param_1 + 0x250) = uVar7;
  *(unsigned long long *)(param_1 + 600) = 0x5880e08;
  *(unsigned long long *)(param_1 + 0x268) = 0x6080e88;
  *(unsigned long long *)(param_1 + 0x260) = uVar4 | uVar12 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x270) = uVar4 | uVar11 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x298) = uVar1;
  *(unsigned long long *)(param_1 + 0x2a0) = uVar7;
  *(unsigned long long *)(param_1 + 0x2a8) = 0x5880e88;
  *(unsigned long long *)(param_1 + 0x2b8) = 0x6080f88;
  *(unsigned long long *)(param_1 + 0x2b0) = uVar4 | uVar11 | (long long)(iVar8 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x2c0) = uVar4 | uVar10 | (long long)(iVar2 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002C81D0, 0x32C bytes. */
void func_002C81D0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar7;
    unsigned long long uVar1;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar8;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5e);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0x20) {
    param_5 = 0x20;
  }
  if (iVar3 < 0x18) {
    iVar3 = 0x18;
  }
  iVar7 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  iVar3 = (iVar3 + (iVar2 >> 9)) * 0x10 + -0xe00;
  iVar2 = (int)param_5 + -0x20;
  uVar8 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar8;
  *(unsigned long long *)(param_1 + 0x28) = 0x6080808;
  *(unsigned long long *)(param_1 + 0x38) = 0x7780908;
  uVar6 = (long long)(0xfffe - param_4) << 0x20;
  uVar5 = (unsigned long long)((param_2 + 0x10) * 0x10 + 0x7000);
  uVar4 = (unsigned long long)((iVar2 + param_2 + 0x10) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar6 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar6 | uVar5 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar8;
  *(unsigned long long *)(param_1 + 0x78) = 0x6080908;
  *(unsigned long long *)(param_1 + 0x88) = 0x7780988;
  *(unsigned long long *)(param_1 + 0x80) = uVar6 | uVar5 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar6 | uVar4 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar8;
  *(unsigned long long *)(param_1 + 200) = 0x6080988;
  *(unsigned long long *)(param_1 + 0xd8) = 0x7780a88;
  *(unsigned long long *)(param_1 + 0xd0) = uVar6 | uVar4 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar6 | (long long)((param_2 + 0x20 + iVar2) * 0x10 + 0x7000) |
               (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002C8BC0, 0x32C bytes. */
void func_002C8BC0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar7;
    unsigned long long uVar1;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar8;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5e);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0x20) {
    param_5 = 0x20;
  }
  if (iVar3 < 0x18) {
    iVar3 = 0x18;
  }
  iVar7 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  iVar3 = (iVar3 + (iVar2 >> 9)) * 0x10 + -0xe00;
  iVar2 = (int)param_5 + -0x20;
  uVar8 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar8;
  *(unsigned long long *)(param_1 + 0x28) = 0x6080808;
  *(unsigned long long *)(param_1 + 0x38) = 0x7580908;
  uVar6 = (long long)(0xfffe - param_4) << 0x20;
  uVar5 = (unsigned long long)((param_2 + 0x10) * 0x10 + 0x7000);
  uVar4 = (unsigned long long)((iVar2 + param_2 + 0x10) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar6 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar6 | uVar5 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar8;
  *(unsigned long long *)(param_1 + 0x78) = 0x6080908;
  *(unsigned long long *)(param_1 + 0x88) = 0x7580988;
  *(unsigned long long *)(param_1 + 0x80) = uVar6 | uVar5 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar6 | uVar4 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar8;
  *(unsigned long long *)(param_1 + 200) = 0x6080988;
  *(unsigned long long *)(param_1 + 0xd8) = 0x7580a88;
  *(unsigned long long *)(param_1 + 0xd0) = uVar6 | uVar4 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar6 | (long long)((param_2 + 0x20 + iVar2) * 0x10 + 0x7000) |
               (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  return;
}

/* 0x002C9D30, 0x32C bytes. */
void func_002C9D30(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar4;
    unsigned long long uVar1;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar7;
    unsigned long long uVar8;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f62);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar2 = iVar2 >> 9;
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0) {
    param_5 = 0;
  }
  if (iVar3 < 0x1a) {
    iVar3 = 0x1a;
  }
  uVar8 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  *(unsigned long long *)(param_1 + 0x20) = uVar8;
  *(unsigned long long *)(param_1 + 0x28) = 0x9081008;
  *(unsigned long long *)(param_1 + 0x38) = 0xa081088;
  uVar6 = (long long)(0xfffe - param_4) << 0x20;
  uVar7 = (unsigned long long)(param_2 * 0x10 + 0x7000);
  uVar5 = (unsigned long long)(((int)param_5 + param_2) * 0x10 + 0x7000);
  iVar4 = (iVar3 + -0x20 + iVar2 + 0x10) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x30) =
       uVar6 | uVar7 | (long long)((iVar2 * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) =
       uVar6 | uVar5 | (long long)(((iVar3 + iVar2) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar8;
  *(unsigned long long *)(param_1 + 0x78) = 0xa081008;
  *(unsigned long long *)(param_1 + 0x88) = 0xa881088;
  *(unsigned long long *)(param_1 + 0x80) =
       uVar6 | uVar7 | (long long)(((iVar2 + 0x10) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar6 | uVar5 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar8;
  *(unsigned long long *)(param_1 + 200) = 0xa881008;
  *(unsigned long long *)(param_1 + 0xd8) = 0xb881088;
  *(unsigned long long *)(param_1 + 0xd0) = uVar6 | uVar7 | (long long)(iVar4 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar6 | uVar5 | (long long)(((iVar2 + 0x20 + iVar3 + -0x20) * 0x10 + -0xe00) / g_70000154 +
                             0x8000) << 0x10;
  return;
}

/* 0x002CA160, 0x32C bytes. */
void func_002CA160(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar7;
    unsigned long long uVar1;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar8;

  
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f62);
  iVar2 = ((param_3 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1ff;
  }
  iVar3 = ((param_6 * 0x280) / 0x1e0) * 0x1c0;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0x1ff;
  }
  iVar3 = iVar3 >> 9;
  if (param_5 < 0x20) {
    param_5 = 0x20;
  }
  if (iVar3 < 2) {
    iVar3 = 2;
  }
  iVar7 = (iVar2 >> 9) * 0x10 + -0xe00;
  *(unsigned long long *)(param_1 + 0x18) = uVar1;
  iVar3 = (iVar3 + (iVar2 >> 9)) * 0x10 + -0xe00;
  iVar2 = (int)param_5 + -0x20;
  uVar8 = (long long)param_7 << 0x18 | 0x3f80000000808080;
  *(unsigned long long *)(param_1 + 0x20) = uVar8;
  *(unsigned long long *)(param_1 + 0x28) = 0x1a080008;
  *(unsigned long long *)(param_1 + 0x38) = 0x1a880108;
  uVar6 = (long long)(0xfffe - param_4) << 0x20;
  uVar5 = (unsigned long long)((param_2 + 0x10) * 0x10 + 0x7000);
  uVar4 = (unsigned long long)((iVar2 + param_2 + 0x10) * 0x10 + 0x7000);
  *(unsigned long long *)(param_1 + 0x30) =
       uVar6 | (long long)(param_2 * 0x10 + 0x7000) | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x40) = uVar6 | uVar5 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x68) = uVar1;
  *(unsigned long long *)(param_1 + 0x70) = uVar8;
  *(unsigned long long *)(param_1 + 0x78) = 0x1a080108;
  *(unsigned long long *)(param_1 + 0x88) = 0x1a880188;
  *(unsigned long long *)(param_1 + 0x80) = uVar6 | uVar5 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0x90) = uVar6 | uVar4 | (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xb8) = uVar1;
  *(unsigned long long *)(param_1 + 0xc0) = uVar8;
  *(unsigned long long *)(param_1 + 200) = 0x1a080188;
  *(unsigned long long *)(param_1 + 0xd8) = 0x1a880288;
  *(unsigned long long *)(param_1 + 0xd0) = uVar6 | uVar4 | (long long)(iVar7 / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(param_1 + 0xe0) =
       uVar6 | (long long)((param_2 + 0x20 + iVar2) * 0x10 + 0x7000) |
               (long long)(iVar3 / g_70000154 + 0x8000) << 0x10;
  return;
}
