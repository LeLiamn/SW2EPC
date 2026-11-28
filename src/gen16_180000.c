/*
 * gen16_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

extern u8 g_004106A0[0x4];
extern u8 g_004106A2[0x4];
extern u8 g_004106A4[0x4];
extern u8 g_0045D898[0x4];
extern u8 g_0056CCA4[0x24];
extern u8 g_00574F7C[0x1];
extern u8 g_005755AC[0x1];
extern u8 g_00669E04[0x4];
extern u8 g_00669E0C[0x4];
extern u8 g_00669E10[0x4];
extern u8 g_00669E18[0x4];
extern u8 g_00669F60[0x4];
extern u8 g_00730DE0[0x4];
extern u8 g_00730DF8[0x4];
extern u8 g_00730DFC[0x4];
extern u8 g_0074B82C[0x8];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F634[0x4];
extern u8 g_00773440[0x4];
extern u8 g_00773448[0x4];
extern u8 g_0077344C[0x4];
extern u8 g_00773450[0x4];
extern u8 g_0077A700[0x10];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */

void func_001148D0(float *, int);
int func_001204B0();
int func_00146B40();
int func_0014F0E0();
void *func_0014F810();
int func_0014F970();
void func_001706A0(u8 *slot, float *a, float *b);
void func_001A85D0(float a, float b, float size, int x, int y, int z, int ia, int ib, int w, int layer);
int func_001DC490();
int func_001DD0F0();
int func_0023AC70();
int func_0023AD10();
int func_00247FA0();
int func_002A5080();
void func_002C4F40(float s, char *text, int x, int y, int a, int b, int c);
int func_002C7310();
int func_002D67E0();
int func_002F00F0();
void *func_002F2890();
void *func_002F2970();
int func_002F41E0();
int func_002F4660();
int func_002F5890();
int func_002F59A0();
int func_0030AAD0();
int func_00328B00();
int func_003623B0();
int func_00363620();
int func_0036D3B0();
int func_0036D400();
int func_00382690();
int func_0038D070();
int func_0038D140();
int func_0038D180();
void *func_00390940();
int func_003B4FE0();
int func_003B5070();
int func_003B51E0();
int func_003B5240();
int func_003B52A0();
int func_003B55A0();
int func_003B55E0();
int func_003B5620();
int func_003B56E0();
void *func_003D9470();
void func_001DD350(int param_1, int param_2, int param_3);
void func_001E0B40(int param_1, int param_2);
void func_002445A0(u8 *param_1, u8 *param_2);
void func_002A5130(void);
void func_00380A40(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_003DA010(int param_1, int param_2);

/* 0x001DD350, 0x1EC bytes. */
void func_001DD350(int param_1, int param_2, int param_3)
{
    int bVar3;
    int * piVar2;
    u32 uVar1;
    u32 uVar4;
    u32 uVar5;

  
  uVar4 = (u32)param_2;
  if ((uVar4 != 0x40) && ((*(int *)(uVar4 * 0x150 + 0x6cdf54) != 0 || (uVar4 - 0x3d < 3)))) {
    uVar5 = (u32)param_1 & 0xffff;
    *(u16 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730df8) + uVar5 * 2) = param_2;
    uVar1 = func_001DC490(param_1);
    bVar3 = 0;
    *(u32 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730de0) + uVar5 * 4) = uVar1;
    do {
      *(u8 *)((u8 *)PS2_PTR(uVar5) + *(int *)(g_0045D3E0 * 0x38 + 0x730dfc)) = bVar3;
      piVar2 = (int *)(g_0045D3E0 * 0x38 + 0x730de0);
      func_001DD0F0(param_1,piVar2[*(u8 *)((u8 *)PS2_PTR(uVar5) + *(int *)(g_0045D3E0 * 0x38 + 0x730dfc)) + 10] +
                           uVar5 * 8,param_3,*(u32 *)(uVar5 * 4 + *piVar2));
      bVar3 = bVar3 + 1;
    } while (bVar3 < 2);
    *(u8 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730dfc) + uVar5) = 0;
    if (uVar4 == 0x18) {
      *(u8 *)(*(int *)(g_0045D3E0 * 0x38 + 0x730dfc) + uVar5) = 1;
    }
  }
  return;
}

/* 0x001E0B40, 0x314 bytes. */
void func_001E0B40(int param_1, int param_2)
{
    int bVar10;
    int bVar2;
    int cVar3;
    int iVar12;
    int iVar13;
    int iVar6;
    int iVar8;
    int * piVar7;
    int * piVar9;
    u32 * puVar11;
    u32 uVar1;
    u32 uVar14;
    unsigned long long uVar4;
    unsigned long long uVar5;

  
  param_1 = param_1 & 0xffff;
  iVar13 = param_1 * 8;
  iVar6 = g_0045D3E0 * 0x38;
  piVar9 = (int *)(iVar6 + 0x730de0);
  iVar8 = *(int *)(g_00730DFC + iVar6);
  uVar14 = 0;
  if (*(int *)(piVar9[*(u8 *)((u8 *)PS2_PTR(iVar8) + param_1) + 10] + iVar13) != 0) {
    iVar12 = param_1 * 4;
    do {
      if ((int)param_1 < piVar9[0xd]) {
        bVar2 = *(int *)((u8 *)PS2_PTR(iVar12) + *piVar9) != 0;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        puVar11 = (u32 *)(iVar13 + *(int *)((u32)*(u8 *)((u8 *)PS2_PTR(param_1) + iVar8) * 4 + iVar6 + 0x730e08
                                            ));
        if (*puVar11 <= uVar14) goto LAB_001e0c40;
        bVar2 = *(int *)(puVar11[1] + uVar14 * 0x10) != 0;
      }
      else {
LAB_001e0c40:
        bVar2 = false;
      }
      if (bVar2) {
        bVar10 = *(u8 *)(*(int *)((u8 *)PS2_PTR(iVar13) + *(int *)((u32)*(u8 *)((u8 *)PS2_PTR(param_1) + iVar8) * 4 + iVar6 +
                                                     0x730e08) + 4) + uVar14 * 0x10 + 0xf) & 2;
      }
      else {
        bVar10 = 0;
      }
      if (bVar10 != 0) {
        puVar11 = (u32 *)(iVar13 + *(int *)((u32)*(u8 *)((u8 *)PS2_PTR(param_1) + iVar8) * 4 + iVar6 + 0x730e08
                                            ));
        piVar7 = (int *)(puVar11[1] + uVar14 * 0x10);
        if ((int)param_1 < piVar9[0xd]) {
          bVar2 = *(int *)((u8 *)PS2_PTR(iVar12) + *piVar9) != 0;
        }
        else {
          bVar2 = false;
        }
        if ((bVar2) && (uVar14 < *puVar11)) {
          bVar2 = *piVar7 != 0;
        }
        else {
          bVar2 = false;
        }
        if (bVar2) {
          cVar3 = (char)piVar7[3];
        }
        else {
          cVar3 = '\0';
        }
        if (cVar3 == '\0') {
          *(char *)(*piVar7 + 0x164) = (char)param_2;
          func_0014F970();
        }
        else {
          func_0014F0E0(*piVar7,param_2);
        }
        iVar8 = g_0045D3E0 * 0x38;
        uVar1 = *(u32 *)((u8 *)PS2_PTR(iVar12) + *(int *)(g_00730DE0 + iVar8));
        if ((*(short *)(param_1 * 2 + *(int *)(g_00730DF8 + iVar8)) == 5) &&
           (*(char *)((u8 *)PS2_PTR(param_1) + *(int *)(g_00730DFC + iVar8)) == '\0')) {
          uVar4 = PS2_ADDR(func_0014F810(uVar1,0x15));
          uVar5 = PS2_ADDR(func_0014F810(uVar1,0x14));
          func_001706A0(0,(float *)PS2_PTR(uVar4),(float *)PS2_PTR(uVar5));
        }
      }
      uVar14 = uVar14 + 1 & 0xffff;
      iVar6 = g_0045D3E0 * 0x38;
      piVar9 = (int *)(iVar6 + 0x730de0);
      iVar8 = *(int *)(g_00730DFC + iVar6);
    } while (uVar14 < *(u32 *)((u8 *)PS2_PTR(iVar13) + piVar9[*(u8 *)((u8 *)PS2_PTR(param_1) + iVar8) + 10]));
  }
  return;
}

/* 0x002445A0, 0x518 bytes. */
void func_002445A0(u8 *param_1, u8 *param_2)
{
    int bVar1;
    int iVar3;
    int iVar5;
    u32 * puVar4;
    int sVar2;
    u32 uVar6;

  
  bVar1 = *(u8 *)(param_1 + 0x14e);
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  uVar6 = (g_7000015C >> 0x10) % 100;
  if ((*(u32 *)(param_2 + 0x2c) & 0x20) == 0) {
    if ((*(u32 *)(param_2 + 0x2c) & 0x10) == 0) {
      if (uVar6 < 0xf) {
        iVar3 = 0;
      }
      else if (uVar6 < 0x32) {
        iVar3 = 1;
      }
      else {
        iVar3 = 2;
      }
      iVar5 = 0;
    }
    else {
      if (uVar6 < 0x14) {
        iVar3 = 0;
      }
      else if (uVar6 < 0x46) {
        iVar3 = 1;
      }
      else {
        iVar3 = 2;
      }
      iVar5 = 1;
    }
  }
  else {
    if (uVar6 < 0x32) {
      iVar3 = 0;
    }
    else if (uVar6 < 0x50) {
      iVar3 = 1;
    }
    else if (uVar6 < 0x5f) {
      iVar3 = 2;
    }
    else {
      iVar3 = 3;
    }
    iVar5 = 2;
  }
  if (iVar3 == 3) {
    iVar5 = iVar5 * 8;
    sVar2 = *(short *)(g_004106A0 + iVar5);
    iVar3 = (u32)bVar1 * 0x48;
    puVar4 = (u32 *)(iVar3 + 0x669e04);
    *(u32 *)(g_00669E04 + iVar3) = *(u32 *)(g_00669E04 + iVar3) | 2;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E0C + iVar3) < uVar6) {
      *(u32 *)(g_00669E0C + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),9,6);
    sVar2 = *(short *)(g_004106A2 + iVar5);
    *puVar4 = *puVar4 | 4;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E10 + iVar3) < uVar6) {
      *(u32 *)(g_00669E10 + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),0xb,6);
    sVar2 = *(short *)(g_004106A4 + iVar5);
    *puVar4 = *puVar4 | 0x10;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E18 + iVar3) < uVar6) {
      *(u32 *)(g_00669E18 + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),0xf,6);
    if (*(u8 *)(param_1 + 0x14e) < 2) {
      func_002F00F0(*(u8 *)(param_1 + 0x14e),0);
      func_002F00F0(*(u8 *)(param_1 + 0x14e),1);
      func_002F00F0(*(u8 *)(param_1 + 0x14e),2);
    }
  }
  else if (iVar3 == 2) {
    sVar2 = *(short *)(iVar5 * 8 + 0x4106a4);
    iVar3 = (u32)bVar1 * 0x48;
    *(u32 *)(g_00669E04 + iVar3) = *(u32 *)(g_00669E04 + iVar3) | 0x10;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E18 + iVar3) < uVar6) {
      *(u32 *)(g_00669E18 + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),0xf,6);
    if (*(u8 *)(param_1 + 0x14e) < 2) {
      func_002F00F0(*(u8 *)(param_1 + 0x14e),2);
    }
  }
  else if (iVar3 == 1) {
    sVar2 = *(short *)(iVar5 * 8 + 0x4106a2);
    iVar3 = (u32)bVar1 * 0x48;
    *(u32 *)(g_00669E04 + iVar3) = *(u32 *)(g_00669E04 + iVar3) | 4;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E10 + iVar3) < uVar6) {
      *(u32 *)(g_00669E10 + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),0xb,6);
    if (*(u8 *)(param_1 + 0x14e) < 2) {
      func_002F00F0(*(u8 *)(param_1 + 0x14e),1);
    }
  }
  else if (iVar3 == 0) {
    sVar2 = *(short *)(iVar5 * 8 + 0x4106a0);
    iVar3 = (u32)bVar1 * 0x48;
    *(u32 *)(g_00669E04 + iVar3) = *(u32 *)(g_00669E04 + iVar3) | 2;
    uVar6 = (u32)(((float)(int)sVar2 * 50.0) / 60.0);
    if (*(u32 *)(g_00669E0C + iVar3) < uVar6) {
      *(u32 *)(g_00669E0C + iVar3) = uVar6;
    }
    func_00247FA0(*(u8 *)(param_1 + 0x14e),9,6);
    if (*(u8 *)(param_1 + 0x14e) < 2) {
      func_002F00F0(*(u8 *)(param_1 + 0x14e),0);
    }
  }
  return;
}

/* 0x002A5130, 0x3B4 bytes. */
void func_002A5130(void)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    u32 uVar7;

  
  uVar7 = 0;
  iVar6 = g_0077A700;
  do {
    if (*(int *)(iVar6 + 0x2c) != 0x107) {
      iVar3 = *(int *)(iVar6 + 0x2c) * 0x70;
      if (*(int *)(g_00773440 + iVar3) == 0) {
        *(u32 *)(iVar6 + 0x34) = 0;
      }
      else {
        func_001148D0((float *)(iVar6),iVar3 + 0x7733f0);
        iVar1 = *(int *)(iVar6 + 0x30) >> 8;
        if ((iVar1 != (*(u32 *)(g_0074B82C + 0x0))) && (iVar1 != (*(u32 *)(g_0074B82C + 0x4)))) {
          iVar5 = *(int *)(iVar6 + 0xc);
          iVar4 = *(int *)(iVar6 + 0x10);
          iVar2 = *(int *)(iVar6 + 0x14) + *(int *)(g_00773448 + iVar3);
          if ((((((*(u32 *)(g_00669F60 + 0x0)) & 8) == 0) &&
               (((long long)(*(char *)(g_00574F7C + 0x0)) << 0x3e < 0 ||
                ((((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0 && ((long long)(*(char *)(g_005755AC + 0x0)) << 0x3e < 0)))))) && (0x54 < iVar1)
              ) && (iVar1 < 0x5a)) {
            iVar2 = iVar2 + -0x400;
          }
          if ((((iVar1 == 1) && (iVar1 = *(int *)(iVar6 + 0x30), iVar1 != 0x126)) &&
              (iVar1 != 0x127)) && ((iVar1 != 0x124 && (iVar1 != 0x125)))) {
            if (*(int *)(iVar6 + 0x38) == 0) {
              g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
              *(u32 *)(g_0077344C + iVar3) = (g_7000015C >> 0x10) % 0x600 - 0x200;
              g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
              *(u32 *)(g_00773450 + iVar3) = (g_7000015C >> 0x10) % 0x14 + 0x5a;
            }
            iVar2 = iVar2 + *(int *)(g_0077344C + iVar3);
            iVar5 = (iVar5 * *(int *)(g_00773450 + iVar3)) / 100;
            iVar4 = (iVar4 * *(int *)(g_00773450 + iVar3)) / 100;
          }
          if (iVar5 < 0x4000) {
            iVar1 = iVar5;
          }
          else {
            iVar1 = 0x3fff;
          }
          if (iVar1 < -0x3ffe) {
            iVar5 = -0x3fff;
          }
          else if (0x3fff < iVar5) {
            iVar5 = 0x3fff;
          }
          *(int *)(iVar6 + 0xc) = iVar5;
          if (iVar4 < 0x4000) {
            iVar1 = iVar4;
          }
          else {
            iVar1 = 0x3fff;
          }
          if (iVar1 < -0x3ffe) {
            iVar4 = -0x3fff;
          }
          else if (0x3fff < iVar4) {
            iVar4 = 0x3fff;
          }
          *(int *)(iVar6 + 0x10) = iVar4;
          if (iVar2 < 0x2001) {
            iVar1 = iVar2;
          }
          else {
            iVar1 = 0x2000;
          }
          if (iVar1 < 0x801) {
            *(u32 *)(iVar6 + 0x14) = 0x800;
          }
          else {
            if (0x2000 < iVar2) {
              iVar2 = 0x2000;
            }
            *(int *)(iVar6 + 0x14) = iVar2;
          }
        }
        if (*(int *)(iVar6 + 0x38) == 0) {
          func_0023AD10(*(u32 *)(iVar6 + 0x30),uVar7 + 1,*(u32 *)(iVar6 + 0xc),
                       *(u32 *)(iVar6 + 0x10),*(u32 *)(iVar6 + 0x14));
          *(u32 *)(iVar6 + 0x38) = 1;
        }
        else {
          func_0023AC70(*(u32 *)(iVar6 + 0x30),uVar7 + 1,*(u32 *)(iVar6 + 0xc),
                       *(u32 *)(iVar6 + 0x10),*(u32 *)(iVar6 + 0x14));
        }
        if (*(float *)(iVar6 + 0x34) < 100.0) {
          *(float *)(iVar6 + 0x34) = *(float *)(iVar6 + 0x34) - 0.02;
        }
      }
      if (*(float *)(iVar6 + 0x34) <= 0.0) {
        func_002A5080(iVar3 + 0x7733f0,iVar6,uVar7 + 1);
      }
    }
    uVar7 = uVar7 + 1;
    iVar6 = iVar6 + 0x3c;
  } while (uVar7 < 100);
  return;
}

/* 0x00380A40, 0x43C bytes. */
void func_00380A40(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    u8 auStack_10[16];
    int iVar1;
    int iVar4;
    int iVar5;
    long long lVar3;
    unsigned long long uVar2;

  
  func_002C7310(param_3,param_4,0,0x100,0xe2,0x80,1);
  iVar5 = (int)param_3;
  iVar4 = (int)param_4;
  func_00382690(iVar5 + 0x10,iVar4 + 8,0,0x3c,0x44,1,param_2);
  if ((*(u32 *)(g_0045D898 + 0x0)) == 0x15) {
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41a00000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41a00000;
    uVar2 = PS2_ADDR(func_002F2970(param_2));
    func_00146B40(uVar2,iVar5 + 0x50,iVar4 + 0x16,0x98,0x14,1,0);
  }
  else {
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41a00000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41a00000;
    uVar2 = PS2_ADDR(func_002F2890(param_2));
    func_00146B40(uVar2,iVar5 + 0x50,iVar4 + 0x16,0x98,0x14,1,0);
  }
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  uVar2 = func_002F5890(param_2);
  uVar2 = func_0030AAD0(uVar2);
  func_003B4FE0(uVar2,iVar5 + 0x50,iVar4 + 0x2c,0,1);
  uVar2 = func_002F4660(param_2);
  func_003B5070(uVar2,iVar5 + 0x68,iVar4 + 0x2c,0,1);
  if (param_7 != 0) {
    lVar3 = func_0036D3B0(param_2);
    if (lVar3 == 0) {
      lVar3 = func_0036D400(param_2);
      if (lVar3 != 0) {
        func_003B5240(iVar5 + 0x80,iVar4 + 0x2c,0,1);
      }
    }
    else {
      func_003B51E0(iVar5 + 0x80,iVar4 + 0x2c,0,1);
    }
  }
  lVar3 = func_002F59A0(param_2);
  if (lVar3 != 0) {
    func_003B52A0(iVar5 + 0x98,iVar4 + 0x2c,0,1);
  }
  func_002D67E0(9,iVar5 + 0x10,iVar4 + 0x4e,0,1,0x80);
  iVar1 = func_002F41E0(param_2);
  func_001204B0(auStack_10,0x459558,iVar1 + 1 + param_6);
  func_002C4F40(14.0f,(char *)(auStack_10),iVar5 + 0x54,iVar4 + 0x4f,1,0,6);
  if (param_5 == 0) {
    func_002D67E0(8,iVar5 + 0x10,iVar4 + 0x60,0,1,0x80);
  }
  else {
    func_003B55A0(iVar5 + 0x10,iVar4 + 0x60,0,1);
  }
  func_002D67E0(0,iVar5 + 0x10,iVar4 + 0x82,0,1,0x80);
  func_002D67E0(1,iVar5 + 0x10,iVar4 + 0x94,0,1,0x80);
  func_002D67E0(2,iVar5 + 0x10,iVar4 + 0xa6,0,1,0x80);
  func_002D67E0(3,iVar5 + 0x10,iVar4 + 0xb8,0,1,0x80);
  if (param_1 != 0) {
    if (param_5 == 0) {
      if (param_2 < 0x1c) {
        func_003B5620(iVar5 + 0x10,iVar4 + 200,0,1);
        lVar3 = func_00328B00(param_2);
        func_003B56E0(0,lVar3 == 0,iVar5 + 0x54,iVar4 + 200,0,1);
      }
    }
    else {
      func_003B55E0(iVar5 + 0x10,iVar4 + 0xca,0,1);
    }
  }
  return;
}

/* 0x003DA010, 0x19C bytes. */
void func_003DA010(int param_1, int param_2)
{
    u8 auStack_10[16];
    int iVar1;
    u8 * iVar2;
    int iVar3;
    long long lVar6;
    unsigned long long uVar4;
    unsigned long long uVar5;

  
  iVar1 = PS2_ADDR(func_00390940());
  iVar2 = func_003D9470();
  if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x8e64) == 6) {
    iVar1 = 0;
  }
  else if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x8e64) == 7) {
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  uVar4 = func_0038D140();
  uVar5 = func_00363620(iVar1);
  iVar3 = func_0038D180(uVar4,uVar5);
  lVar6 = func_00363620(iVar1);
  uVar4 = func_003623B0();
  iVar1 = func_0038D070(uVar4,lVar6 != 0,*(u32 *)(iVar1 * 4 + iVar2 + 0x30));
  iVar1 = (iVar1 * iVar3) / 10;
  if (10000 < iVar1) {
    iVar1 = 10000;
  }
  func_001204B0(auStack_10,0x45c488,iVar1,10000);
  func_002C4F40(14.0f,(char *)(auStack_10),param_1 + 0x54,param_2 + 0x61,1,0,6);
  func_001A85D0((float)iVar1 / 10000.0,0,1.0f,param_1 + 0x54,param_2 + 0x70,0,2,0,0x5c,1);
  return;
}
