/*
 * gen_200000.c - small functions between 0x00200000 and 0x00280000, generated from Ghidra
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

extern u8 g_00751020[0x18];
#define true 1
#define false 0

extern u8 g_0040D250[0x4];
extern u8 g_0040DAC0[0x34];
extern u8 g_00412C60[0x4];
extern u8 g_00424EF0[0x24];
extern u8 g_0043F428[0x1C];
extern u8 g_0043FA98[0x8];
extern u8 g_0043FCE8[0x8];
extern u8 g_00441D44[0x6];
extern u8 g_0045D2C8[0x4];
extern u8 g_0045D460[0x4];
extern u8 g_0045D470[0x4];
extern u8 g_00574DE0[0x10];
extern u8 g_005BA6A0[0x4];
extern u8 g_00669D60[0x10];
extern u8 g_00669F60[0x4];
extern u8 g_00669F6C[0x4];
extern u8 g_00669FA4[0x4];
extern u8 g_0068F0F0[0x18];
extern u8 g_00732220[0x10];
extern u8 g_00732500[0x8];
extern u8 g_0073C78C[0x20];
extern u8 g_0073C790[0x4];
extern u8 g_0073DA18[0x4];
extern u8 g_0073DF80[0x4];
extern u8 g_0073E1F0[0x10];
extern u8 g_0073EDB0[0x10];
extern u8 g_0073F350[0x10];
extern u8 g_00740530[0x10];
extern u8 g_00749C80[0x10];
extern u8 g_00749D40[0x10];
extern u8 g_0074A000[0x15];
extern u8 g_0074A008[0x4];
extern u8 g_00752940[0xC];
extern u8 g_00752944[0x4];
extern u8 g_0075294C[0x4];
extern u8 g_0076F3A0[0x10];
extern u8 g_0076F3AC[0x4];
extern u8 g_0076F3B8[0xB];
extern u8 g_0076F3D4[0x10];
extern u8 g_0076F588[0x14];
extern int g_0045CDAC;   /* (small data) */
extern int g_0045CDB8;   /* (small data) */
extern int g_0045CDBC;   /* (small data) */
extern int g_0045CE00;   /* (small data) */
extern int g_0045CE04;   /* (small data) */
extern int g_0045CE08;   /* (small data) */
extern int g_0045CE0C;   /* (small data) */
extern int g_0045D1C8;   /* (small data) */
extern int g_0045D2F0;   /* (small data) */
extern int g_0045D374;   /* (small data) */
extern int g_0045D3E0;   /* (small data) */
extern int g_0045D424;   /* (small data) */
extern int g_0045D428;   /* (small data) */
extern int g_0045D42C;   /* (small data) */
extern int g_0045D430;   /* (small data) */
extern int g_0045D434;   /* (small data) */
extern int g_0045D488;   /* (small data) */
extern int g_0045D48C;   /* (small data) */
extern int g_0045D490;   /* (small data) */
extern int g_0045D4A0;   /* (small data) */
extern int g_0045D4A4;   /* (small data) */
extern int g_0045D4A8;   /* (small data) */
extern int g_0045D4E4;   /* (small data) */
extern int g_0045D548;   /* (small data) */
extern int g_0045D54C;   /* (small data) */
extern int g_0045D564;   /* (small data) */
extern u32 g_700000C0;   /* (scratchpad) */
extern u32 g_700000C4;   /* (scratchpad) */
extern u32 g_700000C8;   /* (scratchpad) */
extern u32 g_700000CC;   /* (scratchpad) */
extern u32 g_70000150;   /* (scratchpad) */
extern u32 g_7000015C;   /* (scratchpad) */
extern u32 g_700001D0;   /* (scratchpad) */
extern u32 g_700001D4;   /* (scratchpad) */
extern u32 g_70000708;   /* (scratchpad) */
extern u32 g_70000D60;   /* (scratchpad) */

int func_00101400();
int func_00102680();
int func_001026D0();
int func_00102960();
int func_00102D30();
int func_00102EC0();
int func_00103000();
int func_00104E70();
int func_001050B0();
int func_001053E0();
int func_001057F0();
int func_00105D10();
int func_00105D50();
int func_00106C90();
int func_00118850();
int func_00118AC0();
int func_00120928();
int func_00141348();
int func_00147F70();
int func_0014FCB0();
int func_0014FE00();
int func_001500E0();
int func_001698D0();
int func_0018F650();
int func_00196A10();
int func_0019FBA0();
int func_001BEA90();
int func_001C7FC0();
int func_001C94D0();
int func_001C95C0();
int func_001D0E60();
int func_001F14E0();
int func_001FF100();
int func_001FF120();
int func_001FF140();
int func_001FF230();
int func_001FF260();
int func_001FF290();
int func_00203BA0();
int func_00204B60();
int func_00204BB0();
int func_00204C50();
int func_00204CD0();
int func_00204D00();
int func_00204D20();
int func_00204DB0();
int func_00204EA0();
int func_00204F70();
int func_00206290();
int func_00206590();
int func_00206C70();
int func_00207930();
int func_00207D80();
int func_00207DA0();
int func_0020A710();
int func_0020AD40();
int func_0020AEA0();
int func_0020B410();
int func_0020B530();
int func_0020B600();
int func_0020B8F0();
int func_0020B960();
int func_0020BA50();
int func_0020BDE0();
int func_0020C4D0();
int func_0020CC60();
int func_0020CE90();
int func_0020DFE0();
int func_0020E9D0();
int func_0020ECA0();
int func_0020F130();
int func_0020F190();
int func_0020F1D0();
int func_00214040();
int func_00215790();
int func_00215850();
int func_00219020();
int func_00219680();
int func_0021A630();
int func_00228580();
int func_002287F0();
int func_0022C370();
int func_0022C690();
int func_0022C950();
int func_0022D590();
int func_0022D5D0();
int func_0022D910();
int func_0022D9C0();
int func_00236ED0();
int func_002372A0();
int func_00237800();
int func_00237910();
int func_00237B50();
int func_00237D00();
int func_00238AE0();
int func_00238E80();
int func_00238F50();
int func_00239780();
int func_00239830();
int func_00239F50();
int func_0023A2F0();
int func_0023ACC0();
int func_0023ADA0();
int func_0023AF50();
int func_00240640();
int func_00243F10();
int func_00244260();
int func_00245570();
int func_002456F0();
int func_002457D0();
int func_00247530();
int func_00247A20();
int func_00249D80();
int func_00253300();
int func_00253F30();
int func_002540B0();
int func_00255310();
int func_00271A10();
int func_00273D00();
int func_00273D50();
int func_002743E0();
int func_00274400();
int func_00274550();
int func_002754A0();
int func_00278CF0();
int func_0027AEF0();
int func_0027C550();
int func_0027CC10();
int func_0027EF30();
int func_002A6910();
int func_002AF0F0();
int func_002AFF50();
int func_002D7E30();
int func_002E18C0();
int func_002E6A50();
int func_002E6A60();
int func_002F3E70();
int func_0032E7B0();
int func_003620E0();
int func_003E2B30();
void func_00203E40(int param_1);
void func_00204000(int param_1);
void func_00206080(int param_1);
int func_0020A550(int param_1, int param_2, int param_3);
int func_0020BAC0(int param_1, int param_2, int param_3, int param_4);
void func_0020C3B0(int param_1, int param_2, int param_3);
void func_0020C7E0(int param_1, int param_2, int param_3);
void func_0020CA20(int param_1, int param_2, int param_3);
void func_0020CDC0(int param_1, int param_2, int param_3);
void func_0020D490(int param_1, int param_2);
void func_0020DA70(int param_1, int param_2);
void func_0020DD40(int param_1, int param_2);
int func_0020E0D0(int param_1, int param_2);
int func_0020E230(int param_1);
int func_0020E310(int param_1);
int func_0020E7B0(void);
void func_0020ECE0(void);
void func_0020ED30(void);
int func_0020EDA0(int param_1, int param_2);
void func_0020EE50(void);
void func_0020FEF0(int param_1);
void func_002128B0(int param_1, int param_2);
void func_002129B0(int param_1);
void func_00214E00(int param_1);
int func_00215480(int param_1);
int func_00215550(int param_1, int param_2);
int func_00215660(int param_1, int param_2, int param_3);
void func_00216D60(void);
void func_00217E80(int param_1);
int func_002184D0(int param_1, int param_2);
int func_002185B0(int param_1, int param_2);
void func_00218670(int param_1, int param_2, int param_3);
void func_002186E0(u32 *param_1, u32 *param_2, u32 *param_3, u32 *param_4);
void func_00218FB0(int param_1);
int func_0021A3B0(int param_1, int param_2);
int func_0021A400(int param_1, int param_2, int param_3);
void func_0021A440(void);
int func_0021A640(int param_1);
void func_00228E70(void);
int func_00229050(int param_1);
void func_002290E0(void);
int func_002292F0(int param_1);
void func_00229FC0(int param_1, int param_2, int param_3);
int func_0022B820(int param_1, int *param_2);
int func_0022CC20(int param_1, char *param_2, char *param_3, int param_4);
void func_0022CD40(int param_1, int param_2, int param_3);
void func_0022CD70(int param_1, int param_2);
void func_0022D550(int param_1);
int func_0022D740(int param_1, int param_2);
int func_0022DBB0(void);
int func_0022DC40(void);
int func_0022DC70(void);
int func_0022DCA0(void);
int func_0022DCD0(void);
void func_0022DD80(int param_1, int param_2);
void func_0022DDC0(int param_1, int param_2);
void func_0022DE00(int param_1);
void func_0022DE80(void);
void func_00236D90(int param_1);
void func_00236DD0(int param_1);
void func_00237410(int param_1);
void func_002374B0(int param_1, u8 *param_2);
void func_002377C0(int param_1);
void func_00237B10(int param_1);
void func_00237DE0(int param_1);
void func_00237E90(int param_1);
void func_00237ED0(int param_1);
void func_00237F10(int param_1);
void func_00237F60(int param_1);
void func_00237FA0(int param_1);
int func_00238C90(int param_1, int param_2);
void func_002396B0(int param_1, int param_2);
void func_002399E0(int param_1);
void func_0023A0C0(int param_1);
int func_00240DB0(int param_1);
int func_00240E20(int param_1);
void func_002444B0(int param_1);
void func_00244570(int param_1, int param_2);
void func_00245360(int param_1, int param_2);
void func_002453C0(int param_1, int param_2);
void func_00245520(int *param_1);
void func_002456C0(int param_1, int param_2, int param_3);
int func_00245B00(int param_1);
int func_00245DB0(int param_1, int param_2);
void func_00245E60(int param_1, int param_2, int param_3);
void func_00245ED0(int param_1, int param_2);
int func_00245F90(int param_1);
void func_00246470(int param_1, int param_2);
void func_00246570(int param_1, int param_2);
void func_00246710(int param_1);
void func_00247080(int param_1);
void func_00247970(void);
void func_002479C0(void);
void func_00247B20(void);
int func_00247B50(int param_1);
void func_0024A2A0(int param_1, int param_2, int param_3);
void func_0024A430(int param_1, int param_2, int param_3);
void func_0024A5A0(void);
int func_002540D0(int param_1, int param_2);
int func_00254550(int param_1);
void func_00254580(int param_1, int param_2);
void func_00255430(int param_1);
void func_002555D0(int param_1);
void func_002576A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00258130(void);
void func_00258A40(int param_1);
void func_0025AC60(int param_1, int param_2);
void func_0025E9A0(int param_1, int param_2);
void func_002723B0(u32 *param_1, int param_2);
void func_00277B90(void);
int func_002782D0(int param_1);
void func_002786B0(void);
void func_00278760(void);
void func_002787E0(void);
void func_00278870(void);
void func_002790E0(int param_1, int param_2);
void func_0027F980(void);

/* 0x00203E40, 0x148 bytes. */
void func_00203E40(int param_1)
{
    int iVar1;
    int iVar7;
    int lVar6;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;

  
  iVar7 = (int)param_1;
  iVar1 = *(int *)(iVar7 + 0x10);
  if (((*(u32 *)(iVar7 + 0xb8) & 0x180) == 0) || (lVar6 = func_00204F70(), lVar6 != 0)) {
    if (*(char *)(iVar1 + 0x7a) == '\x02') {
      lVar6 = func_00203BA0(param_1);
      if ((lVar6 == 0) && ((*(u32 *)(iVar7 + 0xb8) & 0x180) != 0)) {
        func_00204EA0(param_1);
      }
    }
    else {
      if (*(int *)(iVar7 + 8) != 0) {
        *(u32 *)(iVar7 + 0xbc) = *(u32 *)(iVar7 + 0xbc) & 0xfffffffd;
      }
      *(u32 *)(iVar7 + 8) = 0;
      if (((*(u32 *)(iVar7 + 0xbc) & 0x210000) != 0) &&
         (uVar2 = *(u32 *)(*(int *)(iVar7 + 0x68) + 0x28), (uVar2 & 0x20) == 0)) {
        if (((*(u32 *)(iVar7 + 0xb8) & 0x180) != 0) &&
           (((uVar2 & 0x10) != 0 || ((uVar2 & 4) != 0)))) {
          func_00204EA0(param_1);
          return;
        }
        *(u32 *)(iVar7 + 0xbc) = *(u32 *)(iVar7 + 0xbc) & 0xffdeffff;
      }
      iVar1 = *(int *)(iVar7 + 0x14);
      *(u32 *)(iVar1 + 0x13c) = 0;
      uVar5 = g_700000CC;
      uVar4 = g_700000C8;
      uVar3 = g_700000C4;
      *(u32 *)(iVar1 + 0x1d0) = g_700000C0;
      *(u32 *)(iVar1 + 0x1d4) = uVar3;
      *(u32 *)(iVar1 + 0x1d8) = uVar4;
      *(u32 *)(iVar1 + 0x1dc) = uVar5;
    }
  }
  else {
    func_00204EA0(param_1);
  }
  return;
}

/* 0x00204000, 0xC0 bytes. */
void func_00204000(int param_1)
{
    int iVar5;
    int lVar4;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

  
  lVar4 = func_00206290();
  iVar5 = (int)param_1;
  if (lVar4 == 0) {
    *(u32 *)(iVar5 + 0xbc) = *(u32 *)(iVar5 + 0xbc) & 0xfff8003f;
    *(u8 *)(iVar5 + 0x7d) = 0;
    func_00204D20(param_1);
  }
  else {
    lVar4 = func_00206C70(param_1);
    if (lVar4 == 0) {
      if ((*(u32 *)(iVar5 + 0xbc) & 0x100000) == 0) {
        func_00207930(param_1);
      }
      else {
        iVar5 = *(int *)(iVar5 + 0x14);
        *(u32 *)(iVar5 + 0x13c) = 0;
        uVar3 = g_700000CC;
        uVar2 = g_700000C8;
        uVar1 = g_700000C4;
        *(u32 *)(iVar5 + 0x1d0) = g_700000C0;
        *(u32 *)(iVar5 + 0x1d4) = uVar1;
        *(u32 *)(iVar5 + 0x1d8) = uVar2;
        *(u32 *)(iVar5 + 0x1dc) = uVar3;
      }
      func_00204DB0(param_1,0);
    }
    else {
      func_002D7E30(param_1);
    }
  }
  return;
}

/* 0x00206080, 0x210 bytes. */
void func_00206080(int param_1)
{
    int iVar4;
    int iVar6;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;
    int uVar5;
    u32 uVar7;

  
  iVar6 = (int)param_1;
  *(u32 *)(iVar6 + 0xbc) = *(u32 *)(iVar6 + 0xbc) & 0xfff8003f;
  *(u8 *)(iVar6 + 0x7d) = 0;
  if ((*(u32 *)(iVar6 + 0xb8) & 0x2000) == 0) {
    iVar4 = func_001F14E0();
    if ((*(u32 *)(iVar6 + 0xb8) & 0x10) == 0) {
      if ((*(int *)(iVar6 + 0x10) == 0) || ((*(u32 *)(*(int *)(iVar6 + 0x10) + 0x84) & 0x200) == 0)
         ) {
        g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
        uVar7 = (u32)*(u8 *)(iVar4 + 0xd) + (g_7000015C >> 0x10) % 0x28;
      }
      else {
        uVar7 = (0x14 - (u32)*(u8 *)(iVar6 + 0x7b)) * 4;
      }
      uVar7 = uVar7 & 0xff;
      if ((*(u32 *)(iVar6 + 0xb8) & 0x1000) == 0) {
        iVar4 = *(int *)(iVar6 + 0x14);
        *(u32 *)(iVar4 + 0x13c) = 0;
        uVar3 = g_700000CC;
        uVar2 = g_700000C8;
        uVar1 = g_700000C4;
        *(u32 *)(iVar4 + 0x1d0) = g_700000C0;
        *(u32 *)(iVar4 + 0x1d4) = uVar1;
        *(u32 *)(iVar4 + 0x1d8) = uVar2;
        *(u32 *)(iVar4 + 0x1dc) = uVar3;
        if (*(char *)(*(int *)(iVar6 + 0x68) + 0x1c) == '\x02') {
          func_00204CD0(param_1,0x80000);
        }
      }
      else {
        func_00236ED0(param_1);
      }
    }
    else {
      uVar7 = (u32)*(u8 *)(iVar4 + 0xd);
      iVar4 = *(int *)(iVar6 + 0x14);
      *(u32 *)(iVar4 + 0x13c) = 0;
      uVar3 = g_700000CC;
      uVar2 = g_700000C8;
      uVar1 = g_700000C4;
      *(u32 *)(iVar4 + 0x1d0) = g_700000C0;
      *(u32 *)(iVar4 + 0x1d4) = uVar1;
      *(u32 *)(iVar4 + 0x1d8) = uVar2;
      *(u32 *)(iVar4 + 0x1dc) = uVar3;
      func_00204D00(param_1,0x10);
    }
  }
  else {
    iVar4 = (u32)*(u8 *)(iVar6 + 0x7b) * 7;
    uVar7 = *(u32 *)(*(int *)(iVar6 + 0x68) + 0x28);
    if ((uVar7 & 0x40) == 0) {
      if ((uVar7 & 0x80) == 0) {
        uVar7 = 0;
      }
      else {
        uVar7 = (u32)(u8)((g_00441D44 + 0x2))[iVar4];
      }
    }
    else {
      uVar7 = (u32)(u8)((g_00441D44 + 0x0))[iVar4];
    }
  }
  if (uVar7 == 0) {
    *(u16 *)(iVar6 + 0x78) = 0;
  }
  else {
    uVar7 = (uVar7 * 0x32) / 0x3c;
    uVar5 = (u16)uVar7;
    if (uVar7 == 0) {
      uVar5 = 1;
    }
    *(u16 *)(iVar6 + 0x78) = uVar5;
  }
  return;
}

/* 0x0020A550, 0x1B4 bytes. */
int func_0020A550(int param_1, int param_2, int param_3)
{
    int bVar2;
    int cVar3;
    int iVar5;
    int iVar6;
    int uVar1;
    u32 uVar4;

  
  if (param_2 == 0) {
    uVar4 = 0;
  }
  else {
    iVar6 = (int)param_1;
    if ((*(u8 *)(iVar6 + 0x65) & 0x80) == 0) {
      uVar4 = 0;
    }
    else {
      uVar1 = *(u16 *)(iVar6 + 0x54);
      bVar2 = func_001FF100(uVar1,0xc);
      if (bVar2 == 1) {
        uVar4 = 0;
      }
      else {
        cVar3 = func_001FF100(uVar1,0xb);
        if (cVar3 == '\x02') {
          uVar4 = 0;
        }
        else {
          iVar5 = (int)param_2;
          if (*(int *)(iVar5 + 0x118) == 0x3c) {
            if (1 < bVar2) {
              if (*(int *)(iVar5 + 0x28c) == 0) {
                return 0;
              }
              if (1 < *(u8 *)(*(int *)(iVar5 + 0x28c) + 0x14e)) {
                return 0;
              }
              if ((*(u32 *)(*(int *)(iVar5 + 0x210) + 0x1c) & 0x8000000) == 0) {
                return 0;
              }
            }
            func_00247530(param_1,param_3,param_2,3);
            uVar4 = 1;
          }
          else {
            if (1 < bVar2) {
              if ((*(u32 *)(*(int *)(iVar5 + 0x210) + 0x1c) & 0x8000000) == 0) {
                return 0;
              }
              if ((1 < *(u8 *)(iVar5 + 0x14e)) &&
                 (bVar2 = func_001FF100(*(u16 *)(iVar6 + 0x54),0xd), 1 < bVar2)) {
                return 0;
              }
            }
            func_00247530(param_1,param_3,param_2,4);
            uVar4 = 1;
          }
        }
      }
    }
  }
  return uVar4;
}

/* 0x0020BAC0, 0x23C bytes. */
int func_0020BAC0(int param_1, int param_2, int param_3, int param_4)
{
    int cVar2;
    int iVar4;
    int lVar6;
    int uVar1;
    int uVar3;
    int uVar5;

  
  uVar1 = *(u16 *)((int)param_3 + 0x54);
  uVar5 = func_001FF100(uVar1,1);
  cVar2 = func_001FF260(param_4,uVar5);
  if (cVar2 == '\x01') {
    uVar5 = func_001FF100(uVar1,0);
    cVar2 = func_001FF290(param_4,uVar5);
    if (cVar2 == '\0') {
      iVar4 = func_0020BA50(param_1,param_2,param_4);
    }
    else if (cVar2 == '\x02') {
      iVar4 = func_0020B8F0(param_1,param_2,param_4);
    }
    else {
      iVar4 = func_0020B960(param_1,param_2,param_3,param_4);
    }
  }
  else if (cVar2 == '\x02') {
    uVar5 = func_001FF100(uVar1,0);
    cVar2 = func_001FF290(param_4,uVar5);
    if (cVar2 == '\x02') {
      iVar4 = func_0020B8F0(param_1,param_2,param_4);
    }
    else {
      iVar4 = func_0020B960(param_1,param_2,param_3,param_4);
    }
  }
  else if (cVar2 == '\x04') {
    iVar4 = func_0020B530(param_1,param_2,param_3,param_4);
  }
  else if (cVar2 == '\x05') {
    iVar4 = func_0020B600(param_1,param_2,param_4);
  }
  else if (cVar2 == '\x06') {
    iVar4 = *(int *)((int)param_1 + 8);
    if ((iVar4 != 0) && (*(u8 *)(iVar4 + 0x14e) < 2)) {
      if (*(int *)(iVar4 + 0x110) == 0) {
        uVar3 = 0x6a;
      }
      else {
        uVar3 = *(u8 *)(*(int *)(iVar4 + 0x110) + 0x1c);
      }
      lVar6 = func_001BEA90(uVar3);
      if (lVar6 != 0) {
        iVar4 = func_00207D80(*(u16 *)param_4);
        return (int)param_2 + iVar4 * 0x20;
      }
    }
    iVar4 = func_0020B530(param_1,param_2,param_3,param_4);
  }
  else {
    iVar4 = func_00207D80(*(u16 *)param_4);
    iVar4 = (int)param_2 + iVar4 * 0x20;
  }
  return iVar4;
}

/* 0x0020C3B0, 0x11C bytes. */
void func_0020C3B0(int param_1, int param_2, int param_3)
{
    int iVar2;
    u16 * puVar6;
    u32 uVar1;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;

  
  iVar2 = func_001FF140(*(u16 *)(param_3 + 0x54));
  uVar1 = *(u32 *)(param_3 + 0x5c);
  puVar6 = (u16 *)(iVar2 + 0x30);
  uVar5 = 0;
  if (*(short *)(iVar2 + 4) != 0) {
    do {
      if ((uVar1 & 1 << (uVar5 & 0x1f)) != 0) {
        uVar3 = func_00207D80(*puVar6);
        if ((*(char *)(param_3 + 0x5b) == '\x04') || (*(char *)(puVar6 + 4) == '\x04')) {
          param_2 = param_2 + uVar3 * 0x20;
        }
        else {
          uVar4 = 0;
          if (uVar3 != 0) {
            do {
              func_0020AD40(param_1,param_2);
              uVar4 = uVar4 + 1;
              param_2 = param_2 + 0x20;
            } while (uVar4 < uVar3);
          }
        }
      }
      uVar5 = uVar5 + 1;
      puVar6 = (u16 *)func_001FF230(puVar6);
    } while (uVar5 < *(u16 *)(iVar2 + 4));
  }
  return;
}

/* 0x0020C7E0, 0x23C bytes. */
void func_0020C7E0(int param_1, int param_2, int param_3)
{
    int bVar11;
    int cVar3;
    int cVar5;
    int iVar10;
    int iVar6;
    int iVar9;
    u16 * puVar12;
    int uVar1;
    u32 uVar13;
    u32 uVar2;
    int uVar4;
    u32 uVar7;
    u32 uVar8;

  
  iVar10 = (int)param_3;
  uVar1 = *(u16 *)(iVar10 + 0x54);
  iVar6 = func_001FF140(uVar1);
  uVar2 = *(u32 *)(iVar10 + 0x5c);
  cVar3 = func_001FF100(uVar1,1);
  if (cVar3 != '\0') {
    uVar4 = func_001FF100(uVar1,0);
    puVar12 = (u16 *)(iVar6 + 0x30);
    uVar13 = 0;
    if (*(short *)(iVar6 + 4) != 0) {
      do {
        if ((uVar2 & 1 << (uVar13 & 0x1f)) != 0) {
          uVar7 = func_001FF260(puVar12,cVar3);
          uVar7 = uVar7 & 0xff;
          uVar8 = func_00207D80(*puVar12);
          if (uVar7 - 1 < 2) {
            cVar5 = func_001FF290(puVar12,uVar4);
            if (cVar5 == '\x02') {
              param_2 = param_2 + uVar8 * 0x20;
            }
            else {
              iVar9 = func_00207DA0(*puVar12);
              uVar7 = 0;
              if (uVar8 != 0) {
                do {
                  if (*(u8 *)(iVar9 + uVar7) < 4) {
                    bVar11 = *(char *)(puVar12 + 4) +
                             *(u8 *)(iVar9 + uVar7) + *(char *)(iVar10 + 0x5b) + 1 & 3;
                    func_002E18C0(param_1,param_2,bVar11);
                    func_002E18C0(param_1,param_2,bVar11 + 2 & 3);
                  }
                  else {
                    func_0020B410(param_1,param_2);
                  }
                  uVar7 = uVar7 + 1;
                  param_2 = param_2 + 0x20;
                } while (uVar7 < uVar8);
              }
            }
          }
          else if ((uVar7 == 4) || (uVar7 == 6)) {
            param_2 = func_0020B530(param_1,param_2,param_3,puVar12);
          }
          else {
            param_2 = param_2 + uVar8 * 0x20;
          }
        }
        uVar13 = uVar13 + 1;
        puVar12 = (u16 *)func_001FF230(puVar12);
      } while (uVar13 < *(u16 *)(iVar6 + 4));
    }
  }
  return;
}

/* 0x0020CA20, 0x234 bytes. */
void func_0020CA20(int param_1, int param_2, int param_3)
{
    int bVar11;
    int cVar3;
    int cVar5;
    int iVar10;
    int iVar6;
    int iVar8;
    int lVar9;
    u16 * puVar13;
    int uVar1;
    u32 uVar12;
    u32 uVar14;
    u32 uVar2;
    int uVar4;
    u32 uVar7;

  
  iVar10 = (int)param_3;
  uVar1 = *(u16 *)(iVar10 + 0x54);
  iVar6 = func_001FF140(uVar1);
  uVar2 = *(u32 *)(iVar10 + 0x5c);
  cVar3 = func_001FF100(uVar1,1);
  if (cVar3 != '\0') {
    uVar4 = func_001FF100(uVar1,0);
    puVar13 = (u16 *)(iVar6 + 0x30);
    uVar14 = 0;
    if (*(short *)(iVar6 + 4) != 0) {
      do {
        if ((uVar2 & 1 << (uVar14 & 0x1f)) != 0) {
          cVar5 = func_001FF260(puVar13,cVar3);
          uVar7 = func_00207D80(*puVar13);
          if ((cVar5 == '\x02') ||
             ((cVar5 == '\x01' && (lVar9 = func_001FF290(puVar13,uVar4), lVar9 == 0)))) {
            iVar8 = func_00207DA0(*puVar13);
            uVar12 = 0;
            if (uVar7 != 0) {
              do {
                if (*(u8 *)(iVar8 + uVar12) < 4) {
                  bVar11 = *(char *)(puVar13 + 4) +
                           *(u8 *)(iVar8 + uVar12) + *(char *)(iVar10 + 0x5b) + 1 & 3;
                  func_002E18C0(param_1,param_2,bVar11);
                  func_002E18C0(param_1,param_2,bVar11 + 2 & 3);
                }
                else {
                  func_0020B410(param_1,param_2);
                }
                uVar12 = uVar12 + 1;
                param_2 = param_2 + 0x20;
              } while (uVar12 < uVar7);
            }
          }
          else if ((cVar5 == '\x04') || (cVar5 == '\x06')) {
            param_2 = func_0020B530(param_1,param_2,param_3,puVar13);
          }
          else {
            param_2 = param_2 + uVar7 * 0x20;
          }
        }
        uVar14 = uVar14 + 1;
        puVar13 = (u16 *)func_001FF230(puVar13);
      } while (uVar14 < *(u16 *)(iVar6 + 4));
    }
  }
  return;
}

/* 0x0020CDC0, 0xC8 bytes. */
void func_0020CDC0(int param_1, int param_2, int param_3)
{
    int iVar2;
    int iVar4;
    u32 uVar1;
    u32 uVar3;

  
  iVar2 = func_001FF140(*(u16 *)((int)param_3 + 0x54));
  uVar1 = *(u32 *)((int)param_3 + 0x5c);
  iVar4 = iVar2 + 0x30;
  uVar3 = 0;
  if (*(short *)(iVar2 + 4) != 0) {
    do {
      if ((uVar1 & 1 << (uVar3 & 0x1f)) != 0) {
        param_2 = func_0020CC60(param_1,param_2,param_3,iVar4);
      }
      uVar3 = uVar3 + 1;
      iVar4 = func_001FF230(iVar4);
    } while (uVar3 < *(u16 *)(iVar2 + 4));
  }
  return;
}

/* 0x0020D490, 0x128 bytes. */
void func_0020D490(int param_1, int param_2)
{
    int bVar1;
    int iVar4;
    int iVar5;
    int lVar2;
    u32 uVar3;

  
  iVar4 = g_700001D0 + param_2 * 0x70;
  bVar1 = false;
  if ((*(u8 *)(iVar4 + 0x65) & 0x20) != 0) {
    bVar1 = (*(u8 *)(iVar4 + 0x69) & 2) == 0;
  }
  if (bVar1) {
    iVar5 = (int)param_1;
    if (*(char *)(iVar4 + 0x66) == '\x05') {
      func_0020BDE0(param_1,g_700001D4 + (u32)*(u16 *)(iVar4 + 0x56) * 0x20,iVar4);
      uVar3 = *(u32 *)(iVar5 + 0x18);
    }
    else {
      if (*(char *)(iVar4 + 0x66) == '\0') {
        return;
      }
      func_0020AD40(param_1,g_700001D4 + (u32)*(u16 *)(iVar4 + 0x56) * 0x20);
      uVar3 = *(u32 *)(iVar5 + 0x18);
    }
    if ((uVar3 & 0xf0) != 0) {
      if ((((uVar3 & 0x200) == 0) && ((g_70000708 & 2) != 0)) &&
         (lVar2 = func_0020A710(iVar5 + 0x20,iVar4), lVar2 != 0)) {
        *(u32 *)(iVar5 + 0x18) = *(u32 *)(iVar5 + 0x18) | 0x200;
      }
      g_70000708 = g_70000708 & 0xfd;
    }
  }
  return;
}

/* 0x0020DA70, 0x158 bytes. */
void func_0020DA70(int param_1, int param_2)
{
    int bVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    u32 uVar2;

  
  iVar4 = g_700001D0 + param_2 * 0x70;
  bVar1 = false;
  if ((*(u8 *)(iVar4 + 0x65) & 0x80) != 0) {
    bVar1 = (*(u8 *)(iVar4 + 0x69) & 2) == 0;
  }
  if (bVar1) {
    iVar3 = g_700001D4 + (u32)*(u16 *)(iVar4 + 0x56) * 0x20;
    iVar5 = (int)param_1;
    if ((g_70000708 & 1) == 0) {
      if (*(char *)(iVar4 + 0x66) == '\0') {
        return;
      }
      if (*(char *)(iVar4 + 0x66) == '\x05') {
        func_0020C3B0(param_1,iVar3,iVar4);
        uVar2 = *(u32 *)(iVar5 + 0x18);
      }
      else {
        func_0020AD40(param_1,iVar3);
        uVar2 = *(u32 *)(iVar5 + 0x18);
      }
      if ((uVar2 & 0xf0) == 0) {
        func_0020C4D0(param_1,iVar4);
      }
      uVar2 = *(u32 *)(iVar5 + 0x18);
    }
    else {
      func_0020C4D0(param_1,iVar4);
      uVar2 = *(u32 *)(iVar5 + 0x18);
    }
    if ((((uVar2 & 0xf0) != 0) && (*(int *)(iVar5 + 8) != 0)) && ((uVar2 & 0x200) == 0)) {
      *(u32 *)(iVar5 + 0x18) = uVar2 | 0x200;
      iVar3 = *(int *)(iVar5 + 8);
      if (*(int *)(iVar3 + 0x288) == 0) {
        func_00247530(iVar4,iVar5 + 0x20,iVar3,0);
      }
      else {
        func_00247530(iVar4,iVar5 + 0x20,iVar3,2);
      }
    }
  }
  return;
}

/* 0x0020DD40, 0xB0 bytes. */
void func_0020DD40(int param_1, int param_2)
{
    int bVar1;
    int iVar2;

  
  iVar2 = g_700001D0 + param_2 * 0x70;
  bVar1 = false;
  if ((*(u8 *)(iVar2 + 0x65) & 8) != 0) {
    bVar1 = (*(u8 *)(iVar2 + 0x69) & 2) == 0;
  }
  if (bVar1) {
    if (*(u8 *)(iVar2 + 0x66) == 5) {
      func_0020CE90(param_1,g_700001D4 + (u32)*(u16 *)(iVar2 + 0x56) * 0x20);
    }
    else if (*(u8 *)(iVar2 + 0x66) - 3 < 2) {
      func_0020AEA0(param_1,g_700001D4 + (u32)*(u16 *)(iVar2 + 0x56) * 0x20);
    }
  }
  return;
}

/* 0x0020E0D0, 0x68 bytes. */
int func_0020E0D0(int param_1, int param_2)
{
    int bVar1;

  
  if (((param_1 < 0x28) || (0x44 < param_1)) && ((param_1 < 0x45 || (0x61 < param_1)))) {
    if ((param_1 < 0x62) || (0xb5 < param_1)) {
      bVar1 = false;
    }
    else {
      bVar1 = param_2 == 0;
    }
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

/* 0x0020E230, 0xE0 bytes. */
int func_0020E230(int param_1)
{
    int iVar1;
    int iVar2;

  
  iVar2 = (int)param_1;
  if (param_1 < 4) {
    iVar1 = 0;
  }
  else if (param_1 < 7) {
    iVar1 = 1;
  }
  else if (param_1 < 0xe) {
    iVar1 = 2;
  }
  else if (param_1 < 0x1a) {
    iVar1 = 3;
  }
  else {
    if (1 < iVar2 - 0x1aU) {
      if ((0x1f < param_1) && (param_1 < 0x41)) {
        return (u32)*(u16 *)((g_0040D250 + 0x0) + iVar2 * 2);
      }
      if (param_1 == 0x41) {
        return 0x24e;
      }
      if (param_1 == 0x42) {
        return 0x24f;
      }
      return 0x252;
    }
    iVar1 = 9;
  }
  return iVar2 + iVar1 & 0xffff;
}

/* 0x0020E310, 0x128 bytes. */
int func_0020E310(int param_1)
{
    int iVar1;

  
  if (param_1 < 5) {
    iVar1 = 0;
  }
  else if (param_1 < 9) {
    iVar1 = 1;
  }
  else if (param_1 < 0x11) {
    iVar1 = 2;
  }
  else if (param_1 < 0x23) {
    iVar1 = 3;
  }
  else {
    if (1 < param_1 - 0x23U) {
      if ((0x27 < param_1) && (param_1 < 0x239)) {
        return *(u8 *)((*(u32 *)(g_005BA6A0 + 0x0)) + param_1 * 0x2c + 6) + 4;
      }
      if ((0x1a3 < param_1) && (param_1 < 0x1b4)) {
        iVar1 = func_0019FBA0(param_1 + -0x1a4);
        return *(int *)(iVar1 + 0x18) + 4;
      }
      if (param_1 == 0x24e) {
        return 0x41;
      }
      if (param_1 == 0x24f) {
        return 0x42;
      }
      return 0x43;
    }
    iVar1 = 9;
  }
  return param_1 - iVar1 & 0xffff;
}

/* 0x0020E7B0, 0xFC bytes. */
int func_0020E7B0(void)
{
    int iVar1;
    int lVar2;

  
  iVar1 = 0;
  lVar2 = func_0032E7B0();
  if (lVar2 == 0) {
    if (g_0045D3E0 == 0) {
      if ((*(u32 *)(g_0073C78C + 0x0)) < 0xb6) {
        iVar1 = *(int *)((*(u32 *)(g_0073C78C + 0x0)) * 4 + 0x73c484);
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = iVar1 + *(int *)((u32)(*(u8 *)(g_0073C78C + 0xC)) * 4 + iVar1 + 4);
      }
    }
    else if (g_0045D3E0 == 1) {
      if ((*(u32 *)(g_0073C78C + 0x4)) < 0xb6) {
        iVar1 = *(int *)((*(u32 *)(g_0073C78C + 0x4)) * 4 + 0x73c484);
      }
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = iVar1 + *(int *)((u32)(*(u8 *)(g_0073C78C + 0xD)) * 4 + iVar1 + 4);
      }
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = (*(u32 *)(g_0073C78C + 0x1C));
  }
  return iVar1;
}

/* 0x0020ECE0, 0x50 bytes. */
void func_0020ECE0(void)
{
  if (g_0045D434 <= g_0045D430) {
    g_0045D434 = g_0045D430;
  }
  if (g_0045D434 != 0) {
    func_0020ECA0();
  }
  g_0045D430 = 0;
  g_0045D434 = 0;
  return;
}

/* 0x0020ED30, 0x68 bytes. */
void func_0020ED30(void)
{
    int iVar2;
    int lVar1;

  
  iVar2 = 0;
  do {
    lVar1 = func_0020DFE0(iVar2);
    if (lVar1 != 0) {
      func_0020E9D0(iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb6);
  if (g_0045D424 != 0) {
    func_00102EC0();
    g_0045D424 = 0;
    g_0045D42C = 0;
    g_0045D428 = 0;
  }
  return;
}

/* 0x0020EDA0, 0xA4 bytes. */
int func_0020EDA0(int param_1, int param_2)
{
    int uVar1;
    u32 uVar2;

  
  uVar2 = g_0045D42C + 0x3f & 0xffffffc0;
  g_0045D42C = uVar2;
  uVar1 = func_00102680(1,param_1);
  func_001026D0(1,param_1,uVar2,param_2,uVar1,0,0x429ac0,0x355);
  g_0045D42C = g_0045D42C + ((int)uVar1 + 0x7ffU & 0xfffff800);
  return uVar2;
}

/* 0x0020EE50, 0x70 bytes. */
void func_0020EE50(void)
{
    int iVar2;
    int iVar3;
    int lVar1;

  
  iVar2 = 0;
  iVar3 = g_0045D428 - g_0045D424;
  do {
    lVar1 = func_0020DFE0(iVar2);
    if (lVar1 != 0) {
      func_0020E9D0(iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb6);
  func_00118850(g_0045D424,iVar3);
  g_0045D42C = g_0045D424;
  return;
}

/* 0x0020FEF0, 0x6C bytes. */
void func_0020FEF0(int param_1)
{
    int iVar1;
    int uVar2;

  
  iVar1 = *(int *)(g_70000150 * 4 + param_1 * 0x290 + 0x73da28);
  uVar2 = func_00104E70((*(u32 *)(g_0073DA18 + 0x0)),0x1320,0x3ffc,1);
  *(unsigned long long *)(iVar1 + 0x1848) = uVar2;
  return;
}

/* 0x002128B0, 0x58 bytes. */
void func_002128B0(int param_1, int param_2)
{
    int iVar1;

  
  *(u8 *)(param_1 * 0x290 + 0x73dca1) = 0xff;
  iVar1 = *(int *)(param_2 * 4 + param_1 * 0x290 + 0x73da28);
  *(unsigned long long *)(iVar1 + 0xc1a0) = 0x3f80000000000000;
  *(unsigned long long *)(iVar1 + 0xc1f0) = 0x3f80000000000000;
  return;
}

/* 0x002129B0, 0x248 bytes. */
void func_002129B0(int param_1)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    unsigned long long * puVar2;
    unsigned long long * puVar6;

  
  puVar2 = (unsigned long long *)(param_1 * 0x290 + 0x73da20);
  iVar5 = 0;
  *(u8 *)(param_1 * 0x290 + 0x73dc9e) = 0;
  puVar6 = puVar2;
  do {
    iVar1 = *(int *)(puVar6 + 1);
    func_001050B0(iVar1);
    *(unsigned long long *)(iVar1 + 0x10) = 0x32001;
    *(unsigned long long *)(iVar1 + 0x18) = 0x48;
    func_001053E0(iVar1 + 0x20);
    iVar4 = 0;
    *(unsigned long long *)(iVar1 + 0x38) = 0x3f80000000000000;
    *(unsigned long long *)(iVar1 + 0x40) = 0;
    *(unsigned long long *)(iVar1 + 0x48) = 0;
    iVar3 = iVar1;
    do {
      func_00105D10(iVar3 + 0x50);
      iVar4 = iVar4 + 1;
      *(unsigned long long *)(iVar3 + 0x68) = 0x3f80000000000000;
      *(unsigned long long *)(iVar3 + 0x78) = 0x3f80000000000000;
      *(unsigned long long *)(iVar3 + 0x70) = 0;
      *(unsigned long long *)(iVar3 + 0x80) = 0;
      *(unsigned long long *)(iVar3 + 0x88) = 0;
      *(unsigned long long *)(iVar3 + 0x90) = 0;
      *(unsigned long long *)(iVar3 + 0x98) = 0;
      *(unsigned long long *)(iVar3 + 0xa0) = 0;
      *(unsigned long long *)(iVar3 + 0xa8) = 0;
      *(unsigned long long *)(iVar3 + 0xb0) = 0;
      *(unsigned long long *)(iVar3 + 0xb8) = 0;
      *(unsigned long long *)(iVar3 + 0xc0) = 0;
      iVar3 = iVar3 + 0x80;
    } while (iVar4 < 5);
    func_001050B0(iVar1 + 0x2d0);
    *(unsigned long long *)(iVar1 + 0x2e0) = 0;
    *(unsigned long long *)(iVar1 + 0x2e8) = 0x41;
    func_001050B0(iVar1 + 0x2f0);
    iVar4 = 0;
    *(unsigned long long *)(iVar1 + 0x300) = 0x7000d;
    *(unsigned long long *)(iVar1 + 0x308) = 0x48;
    iVar3 = iVar1;
    do {
      func_001050B0(iVar3 + 0x310);
      *(unsigned long long *)(iVar3 + 800) = 0;
      *(unsigned long long *)(iVar3 + 0x328) = 9;
      func_001057F0(iVar3 + 0x330,*puVar2,1);
      *(unsigned long long *)(iVar3 + 0x350) = 0x3f80000000000000;
      iVar4 = iVar4 + 1;
      *(unsigned long long *)(iVar3 + 0x358) = 0;
      *(unsigned long long *)(iVar3 + 0x360) = 0;
      *(unsigned long long *)(iVar3 + 0x370) = 0;
      iVar3 = iVar3 + 0x70;
    } while (iVar4 < 0x30);
    func_001050B0(iVar1 + 0x1810);
    *(unsigned long long *)(iVar1 + 0x1820) = 0;
    *(unsigned long long *)(iVar1 + 0x1828) = 9;
    func_001057F0(iVar1 + 0x1830,*puVar2,1);
    *(unsigned long long *)(iVar1 + 0x1850) = 0x3f80000080808080;
    *(unsigned long long *)(iVar1 + 0x1858) = 0;
    *(unsigned long long *)(iVar1 + 0x1860) = 0;
    *(unsigned long long *)(iVar1 + 0x1870) = 0;
    func_001050B0(iVar1 + 0x1880);
    iVar5 = iVar5 + 1;
    *(unsigned long long *)(iVar1 + 0x1890) = 0x5000d;
    *(unsigned long long *)(iVar1 + 0x1898) = 0x48;
    puVar6 = (unsigned long long *)((int)puVar6 + 4);
  } while (iVar5 < 2);
  return;
}

/* 0x00214E00, 0x48 bytes. */
void func_00214E00(int param_1)
{
  func_00214040(0);
  if (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) {
    func_00214040(param_1,1);
  }
  return;
}

/* 0x00215480, 0x98 bytes. */
int func_00215480(int param_1)
{
    int bVar1;
    int bVar2;
    int iVar4;
    int * piVar3;

  
  if (((param_1 == 0) || (bVar1 = *(u8 *)param_1, 0x1f < bVar1)) ||
     (bVar2 = ((u8 *)param_1)[1], 0x1f < bVar2)) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = *(int **)(*(int *)(g_0045D2F0 + 4) + ((u32)bVar1 + (u32)bVar2 * 0x20) * 4);
  }
  if (piVar3 == (int *)0x0) {
    iVar4 = 0;
  }
  else if (*(u8 *)(*piVar3 + 8) == 0xff) {
    iVar4 = 0;
  }
  else {
    iVar4 = g_0045D2F0 + (u32)*(u8 *)(*piVar3 + 8) * 4 + 0x10;
  }
  return iVar4;
}

/* 0x00215550, 0x110 bytes. */
int func_00215550(int param_1, int param_2)
{
    int iVar2;
    u8 * pbVar5;
    int uVar1;
    u32 uVar3;
    int uVar4;

  
  pbVar5 = (u8 *)0x0;
  uVar4 = 0xfff;
  uVar3 = 0;
  if (*(char *)(param_1 + 0x55) != '\0') {
    iVar2 = param_1;
    do {
      *(u16 *)((int)param_2 + 6) =
           *(u16 *)
            (*(int *)(*(int *)(param_1 + 0x50) + (u32)*(u8 *)(iVar2 + 0x10) * 0x88) + 4);
      uVar1 = func_0018F650(param_1,param_2);
      if (uVar1 < uVar4) {
        pbVar5 = (u8 *)(iVar2 + 0x10);
        uVar4 = uVar1;
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 4;
    } while (uVar3 < *(u8 *)(param_1 + 0x55));
  }
  if (pbVar5 != (u8 *)0x0) {
    *(u16 *)((int)param_2 + 6) =
         *(u16 *)(*(int *)(*(int *)(param_1 + 0x50) + (u32)*pbVar5 * 0x88) + 4);
  }
  return pbVar5 != (u8 *)0x0;
}

/* 0x00215660, 0x124 bytes. */
int func_00215660(int param_1, int param_2, int param_3)
{
    int iVar2;
    u8 * pbVar4;
    int uVar1;
    u32 uVar3;
    int uVar5;

  
  uVar5 = 0xfff;
  pbVar4 = (u8 *)0x0;
  uVar3 = 0;
  if (*(char *)(param_1 + 0x55) != '\0') {
    iVar2 = param_1;
    do {
      if (param_3 == *(char *)(iVar2 + 0x11)) {
        *(u16 *)((int)param_2 + 6) =
             *(u16 *)
              (*(int *)(*(int *)(param_1 + 0x50) + (u32)*(u8 *)(iVar2 + 0x10) * 0x88) + 4);
        uVar1 = func_0018F650(param_1,param_2);
        if (uVar1 < uVar5) {
          pbVar4 = (u8 *)(iVar2 + 0x10);
          uVar5 = uVar1;
        }
      }
      uVar3 = uVar3 + 1;
      iVar2 = iVar2 + 4;
    } while (uVar3 < *(u8 *)(param_1 + 0x55));
  }
  if (pbVar4 != (u8 *)0x0) {
    *(u16 *)((int)param_2 + 6) =
         *(u16 *)(*(int *)(*(int *)(param_1 + 0x50) + (u32)*pbVar4 * 0x88) + 4);
  }
  return pbVar4 != (u8 *)0x0;
}

/* 0x00216D60, 0x84 bytes. */
void func_00216D60(void)
{
    u32 * puVar1;
    u32 uVar2;

  
  if ((*(int *)g_0045D460) != 0) {
    func_00103000(1);
    if ((*(u32 *)(g_0073DF80 + 0x0)) == 0) {
      func_00102EC0((*(int *)g_0045D460));
      (*(int *)g_0045D460) = 0;
    }
    else {
      uVar2 = 0;
      puVar1 = (u32 *)0x73df80;
      do {
        func_00102EC0(*puVar1);
        uVar2 = uVar2 + 1;
        *puVar1 = 0;
        puVar1 = puVar1 + 1;
      } while (uVar2 < 6);
      (*(int *)g_0045D460) = 0;
    }
  }
  return;
}

/* 0x00217E80, 0xB4 bytes. */
void func_00217E80(int param_1)
{
    int lVar1;
    u32 * puVar2;
    u32 uVar3;

  
  uVar3 = 0;
  puVar2 = (u32 *)0x740430;
  g_0045D48C = *(int *)(param_1 * 0x70 + g_0045D460 + 0xa0);
  (*(u32 *)(g_00669FA4 + 0x0)) = g_0045D48C;
  do {
    *puVar2 = 1;
    uVar3 = uVar3 + 5;
    puVar2[1] = 1;
    puVar2[2] = 1;
    puVar2[3] = 1;
    puVar2[4] = 1;
    puVar2 = puVar2 + 5;
  } while (uVar3 < 10);
  g_0045D488 = param_1;
  func_00215790();
  if (g_0045D48C - 2U < 2) {
    func_002E6A60(1);
  }
  else {
    lVar1 = func_002E6A50();
    if (lVar1 != 0) {
      func_002E6A60(0);
    }
  }
  return;
}

/* 0x002184D0, 0xD4 bytes. */
int func_002184D0(int param_1, int param_2)
{
    int iVar1;

  
  if (((param_1 < 0) || (5 < param_1)) || (9 < param_2)) {
    iVar1 = (int)g_0073EDB0;
  }
  else {
    if (((((*(u32 *)(g_00669F60 + 0x0)) & 0x100000) == 0) && ((*(u32 *)(g_0045D470 + 0x0)) != 2)) &&
       (*(int *)((*(u32 *)(g_0045D470 + 0x0)) * 4 + 0x45d480) < 3)) {
      if ((*(u32 *)(g_0045D470 + 0x0)) == 0) {
        param_2 = *(int *)((g_0040DAC0 + 0x0) + param_2 * 4);
      }
      else {
        param_2 = *(int *)((g_0040DAC0 + 0x30) + param_2 * 4);
      }
    }
    iVar1 = param_2 * 0x10 + (int)param_1 * 0x1e0 + 0x73e270;
  }
  return iVar1;
}
/* MISSING ['0x45d470'] */

/* 0x002185B0, 0xBC bytes. */
int func_002185B0(int param_1, int param_2)
{
    int iVar1;

  
  if ((param_1 == 7) && (param_2 < 10)) {
    if (((((*(u32 *)(g_00669F60 + 0x0)) & 0x100000) == 0) && ((*(u32 *)(g_0045D470 + 0x0)) != 2)) &&
       (*(int *)((*(u32 *)(g_0045D470 + 0x0)) * 4 + 0x45d480) < 3)) {
      if ((*(u32 *)(g_0045D470 + 0x0)) == 0) {
        param_2 = *(int *)((g_0040DAC0 + 0x0) + param_2 * 4);
      }
      else {
        param_2 = *(int *)((g_0040DAC0 + 0x30) + param_2 * 4);
      }
    }
    iVar1 = param_2 * 4 + 0x73e1f0;
  }
  else {
    iVar1 = (int)g_0073E1F0;
  }
  return iVar1;
}
/* MISSING ['0x45d470'] */

/* 0x00218670, 0x68 bytes. */
void func_00218670(int param_1, int param_2, int param_3)
{
    int iVar1;
    int iVar2;

  
  if (param_2 < 2) {
    iVar1 = (*(u32 *)(g_0045D460 + 0x0)) + (int)param_2 * 0x70 + 0xa0;
  }
  else {
    iVar1 = 0;
  }
  if (param_3 < 3) {
    iVar2 = (*(u32 *)(g_0045D460 + 0x0)) + (int)param_3 * 0x40 + 0x180;
  }
  else {
    iVar2 = 0;
  }
  func_00215850(param_1,iVar1,iVar2);
  return;
}
/* MISSING ['0x45d460'] */

/* 0x002186E0, 0x2C bytes. */
void func_002186E0(u32 *param_1, u32 *param_2, u32 *param_3, u32 *param_4)
{
  *param_1 = (*(u32 *)(g_0073F350 + 0x0));
  *param_2 = (*(u32 *)(g_0073F350 + 0x4));
  *param_3 = (*(u32 *)(g_0073F350 + 0x8));
  *param_4 = (*(u32 *)(g_0073F350 + 0xC));
  return;
}
/* MISSING ['0x73f350', '0x73f354', '0x73f358', '0x73f35c'] */

/* 0x00218FB0, 0x70 bytes. */
void func_00218FB0(int param_1)
{
    u32 * puVar1;

  
  if (param_1 != 0) {
    puVar1 = (u32 *)param_1;
    puVar1[4] = 7;
    if (puVar1[0x12] != 0) {
      func_00240640(*(u8 *)(puVar1[0x12] + 0x14e),param_1);
    }
    puVar1[3] = 0;
    if (*puVar1 <= g_0045D490) {
      g_0045D490 = *puVar1;
    }
    g_0045CDAC = g_0045CDAC + 1;
  }
  return;
}

/* 0x0021A3B0, 0x44 bytes. */
int func_0021A3B0(int param_1, int param_2)
{
    int uVar1;

  
  uVar1 = 0;
  if (param_1 < 7) {
    uVar1 = func_00219020(param_2,0,0,(int)param_1 * 0x80 + 0x40db50);
  }
  return uVar1;
}

/* 0x0021A400, 0x3C bytes. */
int func_0021A400(int param_1, int param_2, int param_3)
{
    int uVar1;

  
  uVar1 = 0;
  if (param_1 < 7) {
    uVar1 = func_00219020(0,param_2,param_3,(int)param_1 * 0x80 + 0x40db50);
  }
  return uVar1;
}

/* 0x0021A440, 0x54 bytes. */
void func_0021A440(void)
{
    int iVar1;
    u32 uVar2;

  
  uVar2 = 0;
  iVar1 = (int)g_00740530;
  do {
    if (*(int *)(iVar1 + 0xc) != 0) {
      func_00219680(iVar1);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x1d00;
  } while (uVar2 < 4);
  return;
}

/* 0x0021A640, 0xD4 bytes. */
int func_0021A640(int param_1)
{
    int iVar1;
    int lVar3;
    int uVar2;
    int uVar4;

  
  iVar1 = func_0021A630();
  uVar4 = 1;
  uVar2 = func_003620E0(1,param_1);
  switch(param_1) {
  case 0:
    if (*(int *)(iVar1 + 0x1654) == 1) {
      uVar4 = 0;
    }
    else {
      lVar3 = func_002F3E70(uVar2);
      if (lVar3 != 0) {
        uVar4 = 0;
      }
    }
    break;
  case 1:
  case 2:
    return 1;
  case 3:
  case 4:
  case 5:
  case 7:
    uVar4 = 2;
    break;
  case 6:
    if ((*(int *)(iVar1 + 0x1654) == 0) && (lVar3 = func_002F3E70(uVar2), lVar3 != 0)) {
      uVar4 = 0;
    }
  }
  return uVar4;
}

/* 0x00228E70, 0x1D8 bytes. */
void func_00228E70(void)
{
    int iVar2;
    unsigned long long * puVar1;
    u32 uVar3;

  
  uVar3 = 0;
  g_0045D4A0 = 0;
  g_0045CDB8 = 2;
  iVar2 = (int)g_00749D40;
  do {
    func_00118850(iVar2,0x160);
    *(u32 *)(iVar2 + 4) = uVar3;
    *(u32 *)(iVar2 + 0x3c) = 0;
    *(unsigned long long *)(iVar2 + 0x40) = 0x1000000000008001;
    *(unsigned long long *)(iVar2 + 0x48) = 0xe;
    *(unsigned long long *)(iVar2 + 0xd0) = 0x1000000000008001;
    *(unsigned long long *)(iVar2 + 0xd8) = 0xe;
    *(unsigned long long *)(iVar2 + 0x60) = 0x30ab400000008002;
    *(unsigned long long *)(iVar2 + 0x68) = 0x413;
    uVar3 = uVar3 + 1;
    *(unsigned long long *)(iVar2 + 0xf0) = 0x30ab400000008002;
    *(unsigned long long *)(iVar2 + 0xf8) = 0x413;
    iVar2 = iVar2 + 0x160;
  } while (uVar3 < 2);
  uVar3 = 0;
  puVar1 = (unsigned long long *)0x749c80;
  do {
    *puVar1 = 0x50af400000008001;
    uVar3 = uVar3 + 1;
    puVar1[1] = 0x43431;
    *(u32 *)(puVar1 + 2) = 0x80;
    *(u32 *)((int)puVar1 + 0x14) = 0x94;
    *(u32 *)(puVar1 + 3) = 0x80;
    *(u32 *)(puVar1 + 4) = 0;
    *(u32 *)((int)puVar1 + 0x24) = 0;
    *(u32 *)(puVar1 + 5) = 0;
    *(u32 *)((int)puVar1 + 0x2c) = 0;
    *(u32 *)(puVar1 + 8) = 0x1ff0;
    *(u32 *)((int)puVar1 + 0x44) = 0xff0;
    *(u32 *)(puVar1 + 9) = 0;
    *(u32 *)((int)puVar1 + 0x4c) = 0;
    *(u32 *)(puVar1 + 7) = 0;
    *(u32 *)((int)puVar1 + 0x3c) = 0;
    *(u32 *)(puVar1 + 0xb) = 0;
    *(u32 *)((int)puVar1 + 0x5c) = 0;
    puVar1 = puVar1 + 0xc;
  } while (uVar3 < 2);
  uVar3 = 0;
  puVar1 = (unsigned long long *)0x749bc0;
  iVar2 = (int)g_00749C80;
  do {
    *puVar1 = 0x50af400000008001;
    uVar3 = uVar3 + 1;
    puVar1[1] = 0x43431;
    *(u32 *)(puVar1 + 2) = 0xc0;
    *(u32 *)((int)puVar1 + 0x14) = 0xc0;
    *(u32 *)(puVar1 + 3) = 0xc0;
    *(u32 *)(puVar1 + 4) = 0;
    *(u32 *)((int)puVar1 + 0x24) = 0;
    *(u32 *)(puVar1 + 5) = 0;
    *(u32 *)((int)puVar1 + 0x2c) = 0;
    *(u32 *)(puVar1 + 9) = 0;
    *(u32 *)((int)puVar1 + 0x4c) = 0;
    *(u32 *)(puVar1 + 7) = 0;
    *(u32 *)((int)puVar1 + 0x3c) = 0;
    *(u32 *)(iVar2 + 0x40) = 0x1ff0;
    *(u32 *)(puVar1 + 0xb) = 0;
    *(u32 *)(iVar2 + 0x44) = 0xff0;
    *(u32 *)((int)puVar1 + 0x5c) = 0;
    iVar2 = iVar2 + 0x60;
    puVar1 = puVar1 + 0xc;
  } while (uVar3 < 2);
  g_0045D4A4 = 0;
  g_0045CDBC = 3;
  g_0045D4A8 = 0;
  return;
}

/* 0x00229050, 0x8C bytes. */
int func_00229050(int param_1)
{
    int * piVar2;
    int uVar1;
    u32 uVar3;

  
  uVar1 = 0;
  if ((param_1 < 0x1f) && (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0)) {
    uVar3 = 0;
    piVar2 = (int *)0x749d40;
    do {
      if ((*piVar2 != 0) && (param_1 == piVar2[0xd])) break;
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 0x58;
    } while (uVar3 < 2);
    if (1 < uVar3) {
      uVar1 = func_00228580(param_1,param_1 * 0x40 + 0x40df60);
    }
  }
  return uVar1;
}

/* 0x002290E0, 0x54 bytes. */
void func_002290E0(void)
{
    int * piVar1;
    u32 uVar2;

  
  uVar2 = 0;
  piVar1 = (int *)0x749d40;
  do {
    if (*piVar1 != 0) {
      func_002287F0(piVar1);
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 0x58;
  } while (uVar2 < 2);
  return;
}

/* 0x002292F0, 0x48 bytes. */
int func_002292F0(int param_1)
{
    int * piVar2;
    u32 uVar1;
    u32 uVar3;

  
  uVar1 = 0;
  uVar3 = 0;
  piVar2 = (int *)0x749d40;
  do {
    if ((*piVar2 != 0) && (param_1 == piVar2[0xd])) {
      uVar1 = 1;
    }
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 0x58;
  } while (uVar3 < 2);
  return uVar1;
}

/* 0x00229FC0, 0x38 bytes. */
void func_00229FC0(int param_1, int param_2, int param_3)
{
    u32 uVar1;

  
  *(int *)(param_1 + 4) = (int)param_2;
  uVar1 = func_0022C950(param_2,param_3);
  *(u32 *)(param_1 + 8) = uVar1;
  *(u32 *)(param_1 + 0xc) = 0;
  return;
}

/* 0x0022B820, 0x68 bytes. */
int func_0022B820(int param_1, int *param_2)
{
    int iVar3;
    u32 uVar1;
    u32 uVar2;

  
  iVar3 = 0;
  uVar2 = 0;
  do {
    uVar1 = (u32)*(u8 *)(param_1 + uVar2);
    if (uVar1 != 0) {
      for (; (uVar1 & 1) == 0; uVar1 = uVar1 >> 1) {
        iVar3 = iVar3 + 1;
      }
      *param_2 = iVar3;
      return 1;
    }
    iVar3 = iVar3 + 8;
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x50);
  return 0;
}

/* 0x0022CC20, 0x44 bytes. */
int func_0022CC20(int param_1, char *param_2, char *param_3, int param_4)
{
    u32 uVar1;

  
  uVar1 = ((g_00424EF0 + 0x20))[param_4];
  *param_2 = *param_3 + (char)((g_00424EF0 + 0x0))[param_4];
  param_2[1] = param_3[1] + (char)uVar1;
  return 1;
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

/* 0x0022D550, 0x38 bytes, matching. */
void func_0022D550(int param_1)
{
  (*(u32 *)(g_0074A000 + 0x0)) = 0xffffffff;
  (*(u32 *)(g_0074A000 + 0x4)) = 0xffffffff;
  (*(u32 *)(g_0074A000 + 0x8)) = param_1;
  (*(u32 *)(g_0074A000 + 0xC)) = 0;
  (*(u32 *)(g_0074A000 + 0x10)) = 0;
  (*(u8 *)(g_0074A000 + 0x14)) = 0;
  return;
}

/* 0x0022D740, 0x30 bytes, matching. */
int func_0022D740(int param_1, int param_2)
{
  func_0022D590(*(u32 *)(param_1 + 8));
  return param_2 == 0;
}

/* 0x0022DBB0, 0x28 bytes. */
int func_0022DBB0(void)
{
  return *(u32 *)((*(u32 *)(g_0074A008 + 0x0)) * 0x14 + 0x74a150);
}

/* 0x0022DC40, 0x28 bytes. */
int func_0022DC40(void)
{
  return *(u32 *)((*(u32 *)(g_0074A008 + 0x0)) * 0x14 + 0x74a148);
}

/* 0x0022DC70, 0x28 bytes. */
int func_0022DC70(void)
{
  return *(u32 *)((*(u32 *)(g_0074A008 + 0x0)) * 0x14 + 0x74a14c);
}

/* 0x0022DCA0, 0x28 bytes. */
int func_0022DCA0(void)
{
  return *(u32 *)((*(u32 *)(g_0074A008 + 0x0)) * 0x14 + 0x74a140);
}

/* 0x0022DCD0, 0x7C bytes. */
int func_0022DCD0(void)
{
    u32 uVar1;

  
  if ((*(u32 *)(g_0074A000 + 0x0)) == 1) {
    func_0022D910(g_0074A000);
  }
  else if ((*(u32 *)(g_0074A000 + 0x0)) == 0) {
    func_0022D9C0(g_0074A000);
  }
  uVar1 = 1;
  if (((*(u32 *)(g_0074A000 + 0x0)) != 2) && ((*(u32 *)(g_0074A000 + 0x0)) != -1)) {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x0022DD80, 0x34 bytes. */
void func_0022DD80(int param_1, int param_2)
{
    int iVar1;

  
  iVar1 = (*(u32 *)(g_0074A008 + 0x0)) * 0x98;
  *(u32 *)(iVar1 + 0x74a0b4) = param_1;
  *(u32 *)(iVar1 + 0x74a0b0) = param_2;
  return;
}

/* 0x0022DDC0, 0x34 bytes. */
void func_0022DDC0(int param_1, int param_2)
{
    int iVar1;

  
  iVar1 = (*(u32 *)(g_0074A008 + 0x0)) * 0x98;
  *(u32 *)(iVar1 + 0x74a0a4) = param_1;
  *(u32 *)(iVar1 + 0x74a0ac) = param_2;
  return;
}

/* 0x0022DE00, 0x48 bytes. */
void func_0022DE00(int param_1)
{
    int iVar1;

  
  iVar1 = (*(u32 *)(g_0074A008 + 0x0)) * 0x98;
  *(u32 *)(iVar1 + 0x74a0a0) = param_1;
  func_00120928(iVar1 + 0x74a0b8);
  return;
}

/* 0x0022DE80, 0x34 bytes, matching. */
void func_0022DE80(void)
{
  func_00141348();
  func_0022D5D0(0);
  func_0022D590(0);
  func_0022D550(0);
  return;
}

/* 0x00236D90, 0x38 bytes, matching. */
void func_00236D90(int param_1)
{
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 2;
  func_00204D00(param_1,1);
  return;
}

/* 0x00236DD0, 0xFC bytes. */
void func_00236DD0(int param_1)
{
    int iVar6;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    int uVar5;

  
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 1;
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfffffffe;
  iVar6 = *(int *)(param_1 + 0x14);
  *(u32 *)(iVar6 + 0x13c) = 0;
  uVar4 = g_700000CC;
  uVar3 = g_700000C8;
  uVar2 = g_700000C4;
  *(u32 *)(iVar6 + 0x1d0) = g_700000C0;
  *(u32 *)(iVar6 + 0x1d4) = uVar2;
  *(u32 *)(iVar6 + 0x1d8) = uVar3;
  *(u32 *)(iVar6 + 0x1dc) = uVar4;
  func_00204C50();
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  iVar6 = (g_7000015C >> 0x10 & 7) * 8 + 0x50;
  if (iVar6 == 0) {
    *(u16 *)(param_1 + 0x78) = 0;
  }
  else {
    uVar1 = (u32)(iVar6 * 0x32) / 0x3c;
    uVar5 = (u16)uVar1;
    if (uVar1 == 0) {
      uVar5 = 1;
    }
    *(u16 *)(param_1 + 0x78) = uVar5;
  }
  return;
}

/* 0x00237410, 0xA0 bytes. */
void func_00237410(int param_1)
{
    int cVar1;
    int lVar2;

  
  cVar1 = *(char *)((int)param_1 + 0x7c);
  if (cVar1 == '\x03') {
    lVar2 = func_00239830();
    if (lVar2 == 0) {
      func_00239780(param_1,0);
    }
  }
  else if (cVar1 == '\x02') {
    func_00239780(param_1,0);
  }
  else if (cVar1 == '\x01') {
    func_0027C550();
  }
  else if (cVar1 == '\0') {
    func_002372A0();
  }
  return;
}

/* 0x002374B0, 0x94 bytes. */
void func_002374B0(int param_1, u8 *param_2)
{
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if (((g_7000015C >> 0x10) % 100 < (u32)*param_2) ||
     (g_7000015C = g_7000015C * 0x41c64e6d + 0x3039,
     (g_7000015C >> 0x10) % 100 < (u32)param_2[1])) {
    func_0027AEF0(param_1,0x1c);
  }
  else {
    func_0027AEF0(param_1,0x1b);
  }
  return;
}

/* 0x002377C0, 0x38 bytes, matching. */
void func_002377C0(int param_1)
{
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 2;
  func_002AFF50(param_1,8);
  return;
}

/* 0x00237B10, 0x34 bytes, matching. */
void func_00237B10(int param_1)
{
    int lVar1;

  
  lVar1 = func_00237800();
  if (lVar1 == 0) {
    func_00204BB0(param_1);
  }
  return;
}

/* 0x00237DE0, 0xAC bytes. */
void func_00237DE0(int param_1)
{
    int cVar1;
    int lVar2;

  
  lVar2 = func_00237D00();
  if (lVar2 != 0) {
    cVar1 = *(char *)((int)param_1 + 0x7c);
    if (cVar1 == '\x03') {
      lVar2 = func_00239830(param_1);
      if (lVar2 == 0) {
        func_00237B50(param_1);
      }
    }
    else if (cVar1 == '\x02') {
      func_00237B50(param_1);
    }
    else if (cVar1 == '\x01') {
      func_00237B10(param_1);
    }
    else if (cVar1 == '\0') {
      func_00237910(param_1);
    }
  }
  return;
}

/* 0x00237E90, 0x3C bytes, matching. */
void func_00237E90(int param_1)
{
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 2;
  func_00204B60(param_1,0x1000001);
  return;
}

/* 0x00237ED0, 0x38 bytes, matching. */
void func_00237ED0(int param_1)
{
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 2;
  func_00271A10(param_1,0x1e);
  return;
}

/* 0x00237F10, 0x50 bytes, matching. */
void func_00237F10(int param_1)
{
    int iVar1;

  
  iVar1 = (int)param_1;
  *(u32 *)(iVar1 + 0xbc) = *(u32 *)(iVar1 + 0xbc) & 0xfff8003f;
  *(u8 *)(iVar1 + 0x7d) = 2;
  func_00204CD0(param_1,0x1000000);
  func_00271A10(param_1,0x1f);
  return;
}

/* 0x00237F60, 0x38 bytes, matching. */
void func_00237F60(int param_1)
{
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 2;
  func_00271A10(param_1,0x20);
  return;
}

/* 0x00237FA0, 0xEC bytes. */
void func_00237FA0(int param_1)
{
    int lVar2;
    u8 * pbVar1;

  
  pbVar1 = (u8 *)func_001F14E0();
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if ((g_7000015C >> 0x10) % 100 < (u32)*pbVar1) {
    func_00237E90(param_1);
  }
  else {
    lVar2 = func_00238F50(param_1);
    if (lVar2 == 0) {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[3]) {
        func_00238AE0(param_1,0x3c);
      }
      else {
        func_00206080(param_1);
      }
    }
  }
  return;
}

/* 0x00238C90, 0x148 bytes. */
int func_00238C90(int param_1, int param_2)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int lVar2;

  
  iVar3 = (int)param_1;
  iVar1 = *(int *)(iVar3 + 8);
  if ((*(u32 *)(iVar3 + 0xb8) & 0x10200) == 0) {
    if (*(int *)(iVar1 + 8) == 0) {
      iVar4 = 1;
    }
    else if (((param_2 == 0) || ((*(u32 *)(iVar1 + 0xb8) & 0xc) != 0)) ||
            ((*(u32 *)(iVar1 + 0xb8) & 0x260) == 0)) {
      if ((*(u32 *)(*(int *)(iVar1 + 8) + 0xb8) & 0x26c) == 0) {
        iVar4 = 1;
      }
      else {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 0;
    }
  }
  else {
    iVar4 = 1;
  }
  if (iVar4 == 0) {
    if (((param_2 != 0) && (*(int *)(*(int *)(iVar3 + 0x10) + 0x18) != 0)) &&
       (lVar2 = func_00206590(param_1), lVar2 == 0)) {
      if (*(int *)(iVar3 + 8) != iVar1) {
        *(u32 *)(iVar3 + 0xbc) = *(u32 *)(iVar3 + 0xbc) & 0xfffffffd;
      }
      *(int *)(iVar3 + 8) = iVar1;
    }
  }
  else if (param_2 == 0) {
    func_00204BB0(param_1);
    *(u32 *)(iVar3 + 0xbc) = *(u32 *)(iVar3 + 0xbc) & 0xfff8003f;
    *(u8 *)(iVar3 + 0x7d) = 1;
  }
  else {
    func_00207930(param_1);
  }
  return iVar4;
}

/* 0x002396B0, 0xCC bytes. */
void func_002396B0(int param_1, int param_2)
{
    int iVar1;
    int lVar2;

  
  iVar1 = func_001F14E0();
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if ((((g_7000015C >> 0x10) % 100 < (u32)*(u8 *)(iVar1 + 6)) &&
      (iVar1 = (int)param_1, *(int *)(*(int *)(iVar1 + 8) + 0xc) == 0)) &&
     (lVar2 = func_00240E20(*(u32 *)(iVar1 + 0x14)), lVar2 != 0)) {
    func_00204B60(param_1,1);
    *(u32 *)(iVar1 + 0xbc) = *(u32 *)(iVar1 + 0xbc) & 0xfff8003f;
    *(u8 *)(iVar1 + 0x7d) = 2;
  }
  else {
    func_00238E80(param_1,param_2);
  }
  return;
}

/* 0x002399E0, 0xEC bytes. */
void func_002399E0(int param_1)
{
    int iVar6;
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    int uVar5;

  
  *(u32 *)(param_1 + 0xbc) = *(u32 *)(param_1 + 0xbc) & 0xfff8003f;
  *(u8 *)(param_1 + 0x7d) = 1;
  iVar6 = *(int *)(param_1 + 0x14);
  *(u32 *)(iVar6 + 0x13c) = 0;
  uVar4 = g_700000CC;
  uVar3 = g_700000C8;
  uVar2 = g_700000C4;
  *(u32 *)(iVar6 + 0x1d0) = g_700000C0;
  *(u32 *)(iVar6 + 0x1d4) = uVar2;
  *(u32 *)(iVar6 + 0x1d8) = uVar3;
  *(u32 *)(iVar6 + 0x1dc) = uVar4;
  func_00204C50();
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  iVar6 = (g_7000015C >> 0x10 & 7) * 8 + 0x50;
  if (iVar6 == 0) {
    *(u16 *)(param_1 + 0x78) = 0;
  }
  else {
    uVar1 = (u32)(iVar6 * 0x32) / 0x3c;
    uVar5 = (u16)uVar1;
    if (uVar1 == 0) {
      uVar5 = 1;
    }
    *(u16 *)(param_1 + 0x78) = uVar5;
  }
  return;
}

/* 0x0023A0C0, 0xA0 bytes. */
void func_0023A0C0(int param_1)
{
    int cVar1;
    int lVar2;

  
  cVar1 = *(char *)((int)param_1 + 0x7c);
  if (cVar1 == '\x03') {
    lVar2 = func_00239830();
    if (lVar2 == 0) {
      func_00239780(param_1,0);
    }
  }
  else if (cVar1 == '\x02') {
    func_00239780(param_1,0);
  }
  else if (cVar1 == '\x01') {
    func_0027CC10();
  }
  else if (cVar1 == '\0') {
    func_00239F50();
  }
  return;
}

/* 0x00240DB0, 0x68 bytes. */
int func_00240DB0(int param_1)
{
    u32 uVar1;
    u32 uVar2;

  
  if ((((*(int *)(param_1 + 0x28c) == 0) ||
       (*(int *)(*(int *)(*(int *)(param_1 + 0x28c) + 0x210) + 0x14) == 0)) &&
      (uVar1 = *(u32 *)(*(int *)(param_1 + 0x210) + 0x18), (uVar1 & 4) != 0)) &&
     ((((uVar1 & 0x20) == 0 && ((uVar1 & 8) != 0)) && (0 < *(int *)(param_1 + 0x220))))) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x00240E20, 0x44 bytes. */
int func_00240E20(int param_1)
{
    int bVar1;

  
  if (*(int *)(param_1 + 0x118) < 0x3c) {
    bVar1 = false;
    if (**(short **)(param_1 + 0x210) == 5) {
      bVar1 = 2 < *(int *)(param_1 + 0x220);
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x002444B0, 0x84 bytes. */
void func_002444B0(int param_1)
{
    int iVar1;

  
  iVar1 = (*(u32 *)(g_0045D2C8 + 0x0)) + 1;
  if ((*(short *)((int)param_1 + 0x1cc) != -1) && (iVar1 % 0xd == 0)) {
    func_00243F10();
  }
  if ((*(short *)((int)param_1 + 0x1ce) != -1) && (iVar1 % 0xd == 0)) {
    func_00244260(param_1);
  }
  return;
}
/* MISSING ['0x45d2c8'] */

/* 0x00244570, 0x2C bytes. */
void func_00244570(int param_1, int param_2)
{
  *(u8 *)(param_1 + 0x19e) = *(u8 *)(param_1 + 0x19e) & 0xfd | 2;
  *(u16 *)(param_1 + 0x15e) = 500;
  *(u8 *)(param_1 + 0x1bf) = *(u8 *)(param_2 + 0x19);
  return;
}

/* 0x00245360, 0x5C bytes. */
void func_00245360(int param_1, int param_2)
{
  if ((*(u32 *)(param_2 + 0x2c) & 0x20) == 0) {
    if ((*(u32 *)(param_2 + 0x2c) & 0x10) == 0) {
      *(u8 *)(param_1 + 0x187) = 100;
      *(u8 *)(param_1 + 0x18a) = 1;
    }
    else {
      *(u8 *)(param_1 + 0x187) = 0x4b;
      *(u8 *)(param_1 + 0x18a) = 2;
    }
  }
  else {
    *(u8 *)(param_1 + 0x187) = 0x32;
    *(u8 *)(param_1 + 0x18a) = 3;
  }
  return;
}

/* 0x002453C0, 0x118 bytes. */
void func_002453C0(int param_1, int param_2)
{
    int bVar3;
    int bVar4;
    int iVar2;
    u32 uVar1;

  
  iVar2 = (int)param_1;
  bVar4 = true;
  uVar1 = *(u32 *)((u32)*(u8 *)(iVar2 + 0x14e) * 4 + 0x76e700);
  bVar3 = bVar4;
  if (((uVar1 & 0x100000) == 0) && ((uVar1 & 0x200000) == 0)) {
    bVar3 = false;
  }
  if ((!bVar3) && ((uVar1 & 0x400000) == 0)) {
    bVar4 = false;
  }
  if (bVar4) {
    func_00253F30(param_1);
  }
  if ((*(u32 *)(param_2 + 0x2c) & 0x20) == 0) {
    if ((*(u32 *)(param_2 + 0x2c) & 0x10) == 0) {
      *(u8 *)(iVar2 + 0x157) = 5;
      *(u16 *)(iVar2 + 0x194) = 0xfa;
      func_00253300(0x14,param_1);
    }
    else {
      *(u8 *)(iVar2 + 0x157) = 10;
      *(u16 *)(iVar2 + 0x194) = 0x177;
      func_00253300(0x15,param_1);
    }
  }
  else {
    *(u8 *)(iVar2 + 0x157) = 0xf;
    *(u16 *)(iVar2 + 0x194) = 500;
    func_00253300(0x16,param_1);
  }
  return;
}

/* 0x00245520, 0x48 bytes. */
void func_00245520(int *param_1)
{
    int iVar2;
    int iVar3;
    int * piVar1;

  
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  iVar2 = 199;
  param_1[7] = 0;
  *param_1 = (int)(param_1 + 8);
  piVar1 = param_1 + 8;
  do {
    iVar3 = (int)piVar1;
    iVar2 = iVar2 + -1;
    *(int *)(iVar3 + 8) = iVar3 + 0x20;
    piVar1 = (int *)(iVar3 + 0x20);
  } while (iVar2 != 0);
  *(u32 *)(iVar3 + 0x28) = 0;
  return;
}

/* 0x002456C0, 0x28 bytes, matching. */
void func_002456C0(int param_1, int param_2, int param_3)
{
  func_002456F0(param_1,0,param_2,param_3);
  return;
}

/* 0x00245B00, 0x25C bytes. */
int func_00245B00(int param_1)
{
    u8 * pbVar5;
    u16 * puVar11;
    int sVar1;
    int sVar2;
    u32 uVar10;
    int uVar3;
    u32 uVar4;
    u32 uVar6;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

  
  sVar1 = *(short *)(param_1 + 0x54);
  uVar4 = func_001FF100(sVar1,0xb);
  uVar4 = *(u32 *)((g_00412C60 + 0x0) + (uVar4 & 0xff) * 4);
  if ((uVar4 & 0x100) == 0) {
    sVar2 = sVar1;
    if ((uVar4 & 0x8000) != 0) {
      sVar2 = func_001FF120(sVar1);
    }
    uVar7 = 0xffff;
    if ((sVar2 != -1) && ((*(u32 *)(g_00752940 + 0x8)) < 0x200)) {
      puVar11 = (u16 *)((*(u32 *)(g_00752940 + 0x0)) + (*(u32 *)(g_00752940 + 0x8)) * 2);
      if ((*(u32 *)(g_00669F6C + 0x0)) == 1) {
        if ((uVar4 & 0x4000) != 0) {
          uVar4 = func_001FF100(sVar1,0xd);
          uVar7 = (u32)*puVar11;
          uVar9 = (u32)(uVar7 << 1 <= (uVar4 & 0xff));
          if (uVar7 << 2 <= (uVar4 & 0xff)) {
            uVar9 = uVar9 + 1;
          }
          uVar4 = 0;
          if (uVar9 != 0) {
            do {
              uVar8 = 0;
              uVar7 = 0;
              do {
                uVar6 = uVar7 & 7;
                if (((int)uVar7 < 0) && (uVar6 != 0)) {
                  uVar6 = uVar6 - 8;
                }
                pbVar5 = (u8 *)((*(u32 *)(g_00752940 + 0x4)) + (*(u32 *)(g_00752940 + 0x8)) * 8 + ((int)uVar7 >> 3));
                uVar10 = (int)(u32)*pbVar5 >> (uVar6 & 0x1f) & 3;
                if ((uVar10 < 2) &&
                   (g_7000015C = g_7000015C * 0x41c64e6d + 0x3039,
                   (g_7000015C >> 0x10) % 100 < 0x19)) {
                  *pbVar5 = *pbVar5 & ~(u8)(3 << (uVar6 & 0x1f));
                  *pbVar5 = *pbVar5 | (u8)(uVar10 + 1 << (uVar6 & 0x1f));
                }
                uVar8 = uVar8 + 1;
                uVar7 = uVar7 + 2;
              } while (uVar8 < 0x20);
              uVar4 = uVar4 + 1;
            } while (uVar4 < uVar9);
          }
          if (uVar9 != 0) {
            *(u8 *)(param_1 + 0x68) = 2;
          }
        }
      }
      else {
        uVar3 = func_001FF100(sVar1,0xd);
        *puVar11 = uVar3 & 0xff;
      }
      uVar7 = (*(u32 *)(g_00752940 + 0x8)) & 0xffff;
      (*(u32 *)(g_00752940 + 0x8)) = (*(u32 *)(g_00752940 + 0x8)) + 1;
    }
  }
  else {
    uVar7 = 0xffff;
  }
  return uVar7;
}

/* 0x00245DB0, 0xA4 bytes. */
int func_00245DB0(int param_1, int param_2)
{
    u32 uVar1;
    u32 uVar2;

  
  uVar1 = func_001FF100(*(u16 *)(param_1 + 0x54),0xb);
  if ((*(u32 *)((g_00412C60 + 0x0) + (uVar1 & 0xff) * 4) & 0x4000) == 0) {
    uVar1 = 0;
  }
  else {
    uVar2 = param_2 << 1;
    uVar1 = uVar2 & 7;
    if (((int)uVar2 < 0) && (uVar1 != 0)) {
      uVar1 = uVar1 - 8;
    }
    uVar1 = (int)(u32)*(u8 *)((*(u32 *)(g_00752944 + 0x0)) + (u32)*(u16 *)(param_1 + 0x58) * 8 +
                                ((int)uVar2 >> 3)) >> (uVar1 & 0x1f) & 3;
  }
  return uVar1;
}

/* 0x00245E60, 0x68 bytes. */
void func_00245E60(int param_1, int param_2, int param_3)
{
    u8 * pbVar2;
    u32 uVar1;
    u32 uVar3;

  
  uVar3 = param_2 << 1;
  uVar1 = uVar3 & 7;
  pbVar2 = (u8 *)((*(u32 *)(g_00752944 + 0x0)) + (u32)*(u16 *)(param_1 + 0x58) * 8 + ((int)uVar3 >> 3));
  if (((int)uVar3 < 0) && (uVar1 != 0)) {
    uVar1 = uVar1 - 8;
  }
  *pbVar2 = *pbVar2 & ~(u8)(3 << (uVar1 & 0x1f));
  *pbVar2 = *pbVar2 | (u8)(param_3 << (uVar1 & 0x1f));
  return;
}

/* 0x00245ED0, 0x4C bytes. */
void func_00245ED0(int param_1, int param_2)
{
    u8 * pbVar1;

  
  pbVar1 = (u8 *)((u32)(*(u16 *)(param_2 + 0x58) >> 3) +
                   param_1 * 0x40 + (*(u32 *)(g_0075294C + 0x0)) * 0x100 + 0x752950);
  *pbVar1 = *pbVar1 | (u8)(1 << (*(u16 *)(param_2 + 0x58) & 7));
  return;
}

/* 0x00245F90, 0x30 bytes, matching. */
int func_00245F90(int param_1)
{
    u16 * puVar1;

  
  if (*(u16 *)(param_1 + 0x58) == 0xffff) {
    puVar1 = (u16 *)0x0;
  }
  else {
    puVar1 = (u16 *)((*(u32 *)(g_00752940 + 0x0)) + (u32)*(u16 *)(param_1 + 0x58) * 2);
  }
  return *puVar1;
}

/* 0x00246470, 0x100 bytes. */
void func_00246470(int param_1, int param_2)
{
    int iVar2;
    int iVar4;
    int lVar3;
    u32 uVar1;

  
  uVar1 = func_001FF100(param_1,7);
  if ((uVar1 & 0xff) == 0) {
    iVar4 = 0x28;
  }
  else {
    iVar4 = (uVar1 & 0xff) - 1;
  }
  iVar2 = func_001FF140(param_1);
  if (*(short *)(iVar2 + 2) == 0) {
    if (((*(u32 *)(g_00669F60 + 0x0)) & 0x100000) == 0) {
      g_70000D60 = 0;
    }
    else {
      g_70000D60 = 0xb;
    }
    if ((iVar4 < 0x28) && (lVar3 = func_002AF0F0(iVar4), lVar3 != 0x18b)) {
      func_001C7FC0(lVar3,param_2,0,0);
      if (lVar3 == 0xb) {
        func_00229050(0x1d);
      }
      else if (lVar3 == 10) {
        func_00229050(0x1c);
      }
    }
  }
  return;
}

/* 0x00246570, 0x94 bytes. */
void func_00246570(int param_1, int param_2)
{
    int iVar2;
    u32 uVar1;

  
  uVar1 = func_001FF100(param_1,8);
  uVar1 = uVar1 & 0xff;
  if (uVar1 == 0) {
    iVar2 = 0xff;
  }
  else if (uVar1 < 0x30) {
    iVar2 = uVar1 + 0x6ff;
  }
  else if (uVar1 < 0x78) {
    iVar2 = uVar1 + 0x1d0;
  }
  else if (uVar1 < 0x84) {
    iVar2 = uVar1 + 0x588;
  }
  else {
    iVar2 = 0xff;
  }
  if (iVar2 != 0xff) {
    func_002A6910(iVar2,0,param_2);
  }
  return;
}

/* 0x00246710, 0x38 bytes. */
void func_00246710(int param_1)
{
  func_002457D0();
  func_002456C0(param_1,0x43d4a0,0);
  return;
}

/* 0x00247080, 0x30 bytes. */
void func_00247080(int param_1)
{
  *(u8 *)(param_1 + 0x69) = *(u8 *)(param_1 + 0x69) | 7;
  func_002456C0(param_1,0x43d4c0,0);
  return;
}

/* 0x00247970, 0x48 bytes. */
void func_00247970(void)
{
  if ((*(u32 *)(g_00752940 + 0x0)) != 0) {
    func_00102EC0();
    (*(u32 *)(g_00752940 + 0x0)) = 0;
    func_00102EC0((*(u32 *)(g_00752940 + 0x4)));
    (*(u32 *)(g_00752940 + 0x4)) = 0;
  }
  return;
}

/* 0x002479C0, 0x54 bytes. */
void func_002479C0(void)
{
  func_00118850(g_00751020,0x1b30);
  (*(u32 *)(g_00752940 + 0x0)) = func_00102D30(0x400);
  (*(u32 *)(g_00752940 + 0x4)) = func_00102D30(0x1000);
  g_0045D4E4 = 0x751020;
  func_00247A20();
  return;
}

/* 0x00247B20, 0x28 bytes. */
void func_00247B20(void)
{
  func_00245570(g_0045D4E4);
  g_0045D4E4 = 0x751020;
  return;
}

/* 0x00247B50, 0x34 bytes, matching. */
int func_00247B50(int param_1)
{
  func_00118AC0(param_1,(*(u32 *)(g_00752940 + 0x0)),0x400);
  return (int)param_1 + 0x400;
}

/* 0x0024A2A0, 0x160 bytes. */
void func_0024A2A0(int param_1, int param_2, int param_3)
{
    int iVar2;
    int iVar3;
    int lVar1;

  
  if ((param_3 & 0xff) == 1) {
    iVar3 = (int)param_1 * 0x250;
    iVar2 = (*(u32 *)(g_00732500 + 0x0)) + iVar3;
    *(unsigned long long *)(iVar2 + 0x18770) = 0;
    *(unsigned long long *)(iVar2 + 0x18780) = 0;
    *(unsigned long long *)(iVar2 + 0x187c0) = 0;
    *(unsigned long long *)(iVar2 + 0x187d0) = 0;
    iVar3 = (*(u32 *)(g_00732500 + 0x4)) + iVar3;
    *(unsigned long long *)(iVar3 + 0x18770) = 0;
    *(unsigned long long *)(iVar3 + 0x18780) = 0;
    *(unsigned long long *)(iVar3 + 0x187c0) = 0;
    *(unsigned long long *)(iVar3 + 0x187d0) = 0;
  }
  else {
    lVar1 = func_00249D80(param_1,(param_2 & 0xff) * 0x630 + 0x574de0,100 - (param_3 & 0xff));
    if (lVar1 == 0) {
      iVar3 = (int)param_1 * 0x250;
      iVar2 = (*(u32 *)(g_00732500 + 0x0)) + iVar3;
      *(unsigned long long *)(iVar2 + 0x18770) = 0;
      *(unsigned long long *)(iVar2 + 0x18780) = 0;
      *(unsigned long long *)(iVar2 + 0x187c0) = 0;
      *(unsigned long long *)(iVar2 + 0x187d0) = 0;
      iVar3 = (*(u32 *)(g_00732500 + 0x4)) + iVar3;
      *(unsigned long long *)(iVar3 + 0x18770) = 0;
      *(unsigned long long *)(iVar3 + 0x18780) = 0;
      *(unsigned long long *)(iVar3 + 0x187c0) = 0;
      *(unsigned long long *)(iVar3 + 0x187d0) = 0;
    }
  }
  return;
}

/* 0x0024A430, 0x164 bytes. */
void func_0024A430(int param_1, int param_2, int param_3)
{
    int iVar2;
    int iVar3;
    int lVar1;

  
  if ((param_3 & 0xff) == 1) {
    iVar3 = (int)param_1 * 0x250;
    iVar2 = (*(u32 *)(g_00732500 + 0x0)) + iVar3;
    *(unsigned long long *)(iVar2 + 0x18810) = 0;
    *(unsigned long long *)(iVar2 + 0x18820) = 0;
    *(unsigned long long *)(iVar2 + 0x18860) = 0;
    *(unsigned long long *)(iVar2 + 0x18870) = 0;
    iVar3 = (*(u32 *)(g_00732500 + 0x4)) + iVar3;
    *(unsigned long long *)(iVar3 + 0x18810) = 0;
    *(unsigned long long *)(iVar3 + 0x18820) = 0;
    *(unsigned long long *)(iVar3 + 0x18860) = 0;
    *(unsigned long long *)(iVar3 + 0x18870) = 0;
  }
  else {
    lVar1 = func_00249D80(param_1,(param_2 & 0xff) * 0x630 + 0x574de0,100 - (param_3 & 0xff),0);
    if (lVar1 == 0) {
      iVar3 = (int)param_1 * 0x250;
      iVar2 = (*(u32 *)(g_00732500 + 0x0)) + iVar3;
      *(unsigned long long *)(iVar2 + 0x18810) = 0;
      *(unsigned long long *)(iVar2 + 0x18820) = 0;
      *(unsigned long long *)(iVar2 + 0x18860) = 0;
      *(unsigned long long *)(iVar2 + 0x18870) = 0;
      iVar3 = (*(u32 *)(g_00732500 + 0x4)) + iVar3;
      *(unsigned long long *)(iVar3 + 0x18810) = 0;
      *(unsigned long long *)(iVar3 + 0x18820) = 0;
      *(unsigned long long *)(iVar3 + 0x18860) = 0;
      *(unsigned long long *)(iVar3 + 0x18870) = 0;
    }
  }
  return;
}

/* 0x0024A5A0, 0x404 bytes. */
void func_0024A5A0(void)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int uVar1;

  
  iVar6 = 0;
  iVar4 = 0;
  do {
    *(u8 *)(iVar4 + 0x73255c) = 0xff;
    iVar3 = 0;
    *(u8 *)(iVar4 + 0x73255e) = 0;
    *(u8 *)(iVar4 + 0x732560) = 0xff;
    *(u8 *)(iVar4 + 0x732562) = 0;
    *(u8 *)(iVar4 + 0x732564) = 0xff;
    *(u8 *)(iVar4 + 0x732566) = 0;
    *(u8 *)(iVar4 + 0x732568) = 0xff;
    *(u8 *)(iVar4 + 0x73256a) = 0;
    *(u8 *)(iVar4 + 0x73256c) = 0xff;
    *(u8 *)(iVar4 + 0x73256e) = 0;
    iVar2 = (int)g_00732220;
    do {
      iVar5 = *(int *)(iVar2 + 0x2e0) + iVar6;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0a);
      func_001057F0(iVar5 + 0x18650,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x18678) = 0x3f6100003e000000;
      *(unsigned long long *)(iVar5 + 0x18688) = 0x3f7f00003e400000;
      *(unsigned long long *)(iVar5 + 0x18680) = 0;
      *(unsigned long long *)(iVar5 + 0x18690) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0a);
      func_001057F0(iVar5 + 100000,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x186d0) = 0;
      *(unsigned long long *)(iVar5 + 0x186e0) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0a);
      func_001057F0(iVar5 + 0x186f0,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x18718) = 0x3f6100003e400000;
      *(unsigned long long *)(iVar5 + 0x18728) = 0x3f7f00003e800000;
      *(unsigned long long *)(iVar5 + 0x18720) = 0;
      *(unsigned long long *)(iVar5 + 0x18730) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0e);
      func_001057F0(iVar5 + 0x187e0,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x18808) = 0x3f6100003f580000;
      *(unsigned long long *)(iVar5 + 0x18818) = 0x3f8000003f778000;
      *(unsigned long long *)(iVar5 + 0x18810) = 0;
      *(unsigned long long *)(iVar5 + 0x18820) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0d);
      func_001057F0(iVar5 + 0x18830,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x18858) = 0x3f6100003f300000;
      *(unsigned long long *)(iVar5 + 0x18868) = 0x3f8000003f578000;
      *(unsigned long long *)(iVar5 + 0x18860) = 0;
      *(unsigned long long *)(iVar5 + 0x18870) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0e);
      func_001057F0(iVar5 + 0x18740,uVar1,1);
      *(unsigned long long *)(iVar5 + 0x18768) = 0x3f6100003f580000;
      *(unsigned long long *)(iVar5 + 0x18778) = 0x3f8000003f778000;
      *(unsigned long long *)(iVar5 + 0x18770) = 0;
      *(unsigned long long *)(iVar5 + 0x18780) = 0;
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f0d);
      func_001057F0(iVar5 + 0x18790,uVar1,1);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 4;
      *(unsigned long long *)(iVar5 + 0x187b8) = 0x3f6100003ef80000;
      *(unsigned long long *)(iVar5 + 0x187c8) = 0x3f8000003f2f8000;
      *(unsigned long long *)(iVar5 + 0x187c0) = 0;
      *(unsigned long long *)(iVar5 + 0x187d0) = 0;
    } while (iVar3 < 2);
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + 0x250;
  } while (iVar4 < 2);
  return;
}

/* 0x002540D0, 0x140 bytes. */
int func_002540D0(int param_1, int param_2)
{
    u8 * pbVar1;
    u32 uVar2;

  
  if ((0x19 < param_1) && (0x1b < param_1)) {
    uVar2 = 0;
    pbVar1 = (g_0043F428 + 0x0);
    do {
      if (*pbVar1 == param_1) break;
      uVar2 = uVar2 + 1;
      pbVar1 = pbVar1 + 1;
    } while (uVar2 < 0xd);
    if (uVar2 == 0xd) {
      uVar2 = 0;
    }
    if ((param_2 < 0x3e) || (0x48 < param_2)) {
      if ((param_2 < 0x49) || (0x53 < param_2)) {
        if ((param_2 < 0x54) || (0x5c < param_2)) {
          if ((0x5c < param_2) && (param_2 < 0x68)) {
            param_2 = 0x21;
          }
        }
        else {
          param_2 = 0x20;
        }
      }
      else {
        param_2 = 0x2a;
      }
    }
    else {
      param_2 = 0x26;
    }
    param_1 = 0;
    pbVar1 = (g_0043F428 + 0x18);
    do {
      if (*pbVar1 == param_2) break;
      param_1 = param_1 + 1;
      pbVar1 = pbVar1 + 1;
    } while (param_1 < 0x16);
    if (param_1 == 0x16) {
      param_1 = 0;
    }
    param_1 = param_1 + uVar2 * 0x16 + 0x1c;
  }
  return param_1;
}

/* 0x00254550, 0x30 bytes, matching. */
int func_00254550(int param_1)
{
    int iVar1;
    u32 uVar2;

  
  iVar1 = 0;
  uVar2 = 0;
  do {
    if (*(int *)(param_1 + 0x38) != 0) {
      iVar1 = iVar1 + 1;
    }
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 4;
  } while (uVar2 < 4);
  return iVar1;
}

/* 0x00254580, 0x40 bytes. */
void func_00254580(int param_1, int param_2)
{
    int iVar1;

  
  if (param_2 < 3) {
    iVar1 = param_1 + param_2 * 4;
    do {
      if (param_2 < 3) {
        *(u32 *)(iVar1 + 0x38) = *(u32 *)(iVar1 + 0x3c);
      }
      param_2 = param_2 + 1;
      iVar1 = iVar1 + 4;
    } while (param_2 < 3);
  }
  *(u32 *)(param_1 + 0x44) = 0;
  return;
}

/* 0x00255430, 0x7C bytes. */
void func_00255430(int param_1)
{
    u32 uVar1;

  
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  *(u32 *)(param_1 + 4) = g_7000015C >> 0x10 & 3;
  uVar1 = func_00255310();
  *(u32 *)(param_1 + 0x34) = uVar1;
  *(u32 *)(param_1 + 0x24) = 0;
  *(u32 *)(param_1 + 0xc) = 0;
  *(u32 *)(param_1 + 0x28) = 0;
  *(u32 *)(param_1 + 0x10) = 0;
  *(u32 *)(param_1 + 0x2c) = 0;
  *(u32 *)(param_1 + 0x14) = 0;
  *(u32 *)(param_1 + 0x30) = 0;
  *(u32 *)(param_1 + 0x18) = 0;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u8 *)(param_1 + 0x6d) = 0;
  func_002540B0();
  return;
}

/* 0x002555D0, 0x48 bytes. */
void func_002555D0(int param_1)
{
  func_001D0E60(*(u32 *)(param_1 + 0x38));
  if (param_1 != -0x150) {
    *(u32 *)(param_1 + 0x188) = *(u32 *)(param_1 + 0x188) | 8;
  }
  g_0045D374 = 2;
  return;
}

/* 0x002576A0, 0x11C bytes. */
void func_002576A0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;

  
  if (g_0045CE00 != 0) {
    func_0020F130();
    func_0020F1D0(0,0,param_2,param_3,0);
    func_0020F190();
  }
  if (g_0045CE04 != 0) {
    func_001C94D0(param_5);
  }
  if (g_0045CE08 != 0) {
    iVar1 = (int)param_1;
    *(u8 *)(iVar1 + 0x198) = *(u8 *)(iVar1 + 0x198) & 0xf7;
    func_0014FCB0(param_4);
    func_0014FE00();
    func_001500E0(100);
    func_00147F70(*(u32 *)(iVar1 + 0x130),*(u8 *)(iVar1 + 0x14f));
    func_001698D0(param_1,0);
  }
  if ((g_0045CE0C != 0) && (param_6 < 4)) {
    func_001C95C0(param_5,param_6);
  }
  return;
}

/* 0x00258130, 0x178 bytes. */
void func_00258130(void)
{
    int iVar10;
    int iVar11;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar8;
    int iVar9;
    int uVar1;
    u32 uVar7;

  
  iVar2 = func_001026D0(1,0x51e,0,1,0,0,0x43f458,0xac2);
  iVar8 = 0;
  iVar10 = (int)g_00669D60;
  iVar6 = (int)g_00574DE0;
  iVar5 = 0;
  do {
    if (*(int *)(iVar10 + 0xa0) != 0) {
      if (*(int *)(iVar6 + 0x110) == 0) {
        uVar1 = 0x6a;
      }
      else {
        uVar1 = *(u8 *)(*(int *)(iVar6 + 0x110) + 0x1c);
      }
      iVar3 = func_002540D0(*(u32 *)(iVar6 + 0x118),uVar1);
      uVar7 = 0;
      iVar4 = iVar5 * 0x20 + 0x76e940;
      iVar9 = iVar5;
      do {
        iVar11 = iVar2 + iVar3 * 0x18;
        func_00118AC0(iVar9 * 0x20 + 0x76e940,iVar11,0xc);
        func_00118AC0(iVar9 * 0x20 + 0x76e950,iVar11 + 0xc,0xc);
        *(u32 *)(iVar4 + 0xc) = 0;
        uVar7 = uVar7 + 1;
        *(u32 *)(iVar4 + 0x1c) = 0;
        iVar3 = iVar3 + 0x13a;
        iVar9 = iVar9 + 1;
        iVar4 = iVar4 + 0x20;
      } while (uVar7 < 2);
    }
    iVar8 = iVar8 + 1;
    iVar10 = iVar10 + 0x48;
    iVar6 = iVar6 + 0x630;
    iVar5 = iVar5 + 2;
  } while (iVar8 < 2);
  func_00102EC0(iVar2);
  return;
}

/* 0x00258A40, 0x78 bytes. */
void func_00258A40(int param_1)
{
    int iVar1;

  
  iVar1 = *(int *)(param_1 + 0x38);
  func_001D0E60(iVar1);
  if (param_1 != -0x150) {
    *(u32 *)(param_1 + 0x188) = *(u32 *)(param_1 + 0x188) | 8;
  }
  if (param_1 != -0x5d0) {
    *(u32 *)(param_1 + 0x608) = *(u32 *)(param_1 + 0x608) | 8;
  }
  g_0045D374 = 2;
  if (iVar1 != 0) {
    func_003E2B30(*(u8 *)(iVar1 + 0x14e));
  }
  return;
}

/* 0x0025AC60, 0x108 bytes. */
void func_0025AC60(int param_1, int param_2)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int uVar1;

  
  uVar1 = (*(unsigned long long *)(g_0068F0F0 + 0x0));
  *(u32 *)(param_1 * 0x1c + 0x732570) = 0;
  iVar6 = param_1 * 0x1c + 0x732570;
  uVar1 = func_00106C90(uVar1,0x3f3c);
  func_001057F0(param_2,uVar1,0);
  *(unsigned long long *)(param_2 + 0x30) = 0;
  iVar5 = 0;
  *(unsigned long long *)(param_2 + 0x40) = 0;
  iVar3 = iVar6;
  do {
    iVar4 = 0;
    *(u8 *)(iVar6 + iVar5 + 0x14) = 0;
    *(u32 *)(iVar3 + 4) = 0;
    iVar2 = param_2;
    do {
      uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f33);
      func_001057F0(iVar2 + 0x50,uVar1,0);
      iVar4 = iVar4 + 1;
      *(unsigned long long *)(iVar2 + 0x80) = 0;
      *(unsigned long long *)(iVar2 + 0x90) = 0;
      iVar2 = iVar2 + 0x50;
    } while (iVar4 < 2);
    iVar5 = iVar5 + 1;
    iVar3 = iVar3 + 4;
    param_2 = param_2 + 0xa0;
  } while (iVar5 < 4);
  return;
}

/* 0x0025E9A0, 0x490 bytes. */
void func_0025E9A0(int param_1, int param_2)
{
    int iVar2;
    int iVar3;
    int uVar1;

  
  uVar1 = (*(unsigned long long *)(g_0068F0F0 + 0x10));
  iVar2 = (int)param_2 * 0x1c;
  *(u8 *)(iVar2 + 0x732588) = 0;
  *(u8 *)(iVar2 + 0x732589) = 0;
  *(u8 *)(iVar2 + 0x73258a) = 0;
  uVar1 = func_00106C90(uVar1,0x3f93);
  func_001057F0(param_1 + 0x870,uVar1,0);
  *(unsigned long long *)(param_1 + 0x8a0) = 0;
  iVar3 = 0;
  *(unsigned long long *)(param_1 + 0x8b0) = 0;
  iVar2 = param_1;
  do {
    uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f2c);
    func_00105D50(iVar2 + 0x9b0,uVar1);
    *(unsigned long long *)(iVar2 + 0x9e0) = 0;
    iVar3 = iVar3 + 1;
    *(unsigned long long *)(iVar2 + 0x9f0) = 0;
    *(unsigned long long *)(iVar2 + 0xa00) = 0;
    *(unsigned long long *)(iVar2 + 0xa10) = 0;
    *(unsigned long long *)(iVar2 + 0xa20) = 0;
    *(unsigned long long *)(iVar2 + 0xa30) = 0;
    iVar2 = iVar2 + 0x90;
  } while (iVar3 < 3);
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x5a0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x5d0) = 0;
  *(unsigned long long *)(param_1 + 0x5e0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x5f0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x620) = 0;
  *(unsigned long long *)(param_1 + 0x630) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x640,uVar1,0);
  *(unsigned long long *)(param_1 + 0x670) = 0;
  *(unsigned long long *)(param_1 + 0x680) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x780,uVar1,0);
  *(unsigned long long *)(param_1 + 0x7b0) = 0;
  *(unsigned long long *)(param_1 + 0x7c0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 2000,uVar1,0);
  *(unsigned long long *)(param_1 + 0x800) = 0;
  *(unsigned long long *)(param_1 + 0x810) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x820,uVar1,0);
  *(unsigned long long *)(param_1 + 0x850) = 0;
  *(unsigned long long *)(param_1 + 0x860) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x690,uVar1,0);
  *(unsigned long long *)(param_1 + 0x6c0) = 0;
  *(unsigned long long *)(param_1 + 0x6d0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x6e0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x710) = 0;
  *(unsigned long long *)(param_1 + 0x720) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef5);
  func_001057F0(param_1 + 0x730,uVar1,0);
  *(unsigned long long *)(param_1 + 0x760) = 0;
  *(unsigned long long *)(param_1 + 0x770) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f2a);
  func_001057F0(param_1 + 0x2d0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x300) = 0;
  *(unsigned long long *)(param_1 + 0x310) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f29);
  func_001057F0(param_1 + 0x410,uVar1,0);
  *(unsigned long long *)(param_1 + 0x440) = 0;
  *(unsigned long long *)(param_1 + 0x450) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f2a);
  func_001057F0(param_1 + 800,uVar1,0);
  *(unsigned long long *)(param_1 + 0x350) = 0;
  *(unsigned long long *)(param_1 + 0x360) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f29);
  func_001057F0(param_1 + 0x460,uVar1,0);
  *(unsigned long long *)(param_1 + 0x490) = 0;
  *(unsigned long long *)(param_1 + 0x4a0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f2a);
  func_001057F0(param_1 + 0x3c0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x3f0) = 0;
  *(unsigned long long *)(param_1 + 0x400) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f2a);
  func_001057F0(param_1 + 0x370,uVar1,0);
  *(unsigned long long *)(param_1 + 0x3a0) = 0;
  *(unsigned long long *)(param_1 + 0x3b0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f29);
  func_001057F0(param_1 + 0x4b0,uVar1,0);
  *(unsigned long long *)(param_1 + 0x4e0) = 0;
  iVar3 = 0;
  *(unsigned long long *)(param_1 + 0x4f0) = 0;
  iVar2 = param_1;
  do {
    uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef8);
    func_001057F0(iVar2 + 0x500,uVar1,0);
    iVar3 = iVar3 + 1;
    *(unsigned long long *)(iVar2 + 0x530) = 0;
    *(unsigned long long *)(iVar2 + 0x540) = 0;
    iVar2 = iVar2 + 0x50;
  } while (iVar3 < 2);
  iVar3 = 0;
  iVar2 = param_1;
  do {
    uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f41);
    func_001057F0(iVar2 + 0x8c0,uVar1,0);
    iVar3 = iVar3 + 1;
    *(unsigned long long *)(iVar2 + 0x8f0) = 0;
    *(unsigned long long *)(iVar2 + 0x900) = 0;
    iVar2 = iVar2 + 0x50;
  } while (iVar3 < 3);
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f40);
  func_001057F0(param_1 + 0xb60,uVar1,0);
  *(unsigned long long *)(param_1 + 0xb90) = 0;
  *(unsigned long long *)(param_1 + 0xba0) = 0;
  uVar1 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f40);
  func_001057F0(param_1 + 0xbd0,uVar1,0);
  *(unsigned long long *)(param_1 + 0xc00) = 0;
  *(unsigned long long *)(param_1 + 0xc10) = 0;
  func_0025AC60(param_2,param_1);
  return;
}

/* 0x002723B0, 0xB0 bytes. */
void func_002723B0(u32 *param_1, int param_2)
{
    int iVar1;
    int iVar3;
    int lVar2;

  
  if ((*param_1 & 0x10) == 0) {
    param_1[0x13] = param_2 & 0xffff;
  }
  else if (((*(u32 *)(g_0073C790 + 0x0)) == 0xb6) && (param_1[0x13] == (param_2 & 0xffff))) {
    iVar3 = g_0045D3E0 * 0x174;
    iVar1 = *(int *)(iVar3 + 0x730a84);
    *(int *)(iVar3 + 0x730a84) = iVar1 + 1;
    param_1[0x13] = *(u32 *)(iVar1 * 4 + iVar3 + 0x730a44);
    lVar2 = func_0023A2F0();
    if (lVar2 == 0) {
      param_1[0x13] = 0x1478;
    }
  }
  return;
}

/* 0x00277B90, 0xCC bytes. */
void func_00277B90(void)
{
  (*(u16 *)(g_0076F3B8 + 0x4)) = (*(u16 *)(g_0043FA98 + 0x4));
  (*(u16 *)(g_0076F3B8 + 0x2)) = (*(u16 *)(g_0043FA98 + 0x2));
  (*(u16 *)(g_0076F3B8 + 0x6)) = (*(u16 *)(g_0043FA98 + 0x6));
  (*(u16 *)(g_0076F3B8 + 0x0)) = (*(u16 *)(g_0043FA98 + 0x0));
  (*(u8 *)(g_0076F3B8 + 0xA)) = 0xc;
  (*(u8 *)(g_0076F3B8 + 0x9)) = 0x80;
  (*(u16 *)(g_0076F588 + 0x6)) = (*(u16 *)(g_0043FCE8 + 0x6));
  (*(u8 *)(g_0076F588 + 0x13)) = 0;
  (*(u16 *)(g_0076F588 + 0x4)) = (*(u16 *)(g_0043FCE8 + 0x4));
  (*(u8 *)(g_0076F588 + 0x10)) = 0x80;
  (*(u16 *)(g_0076F588 + 0xA)) = (*(u16 *)(g_0043FCE8 + 0x2));
  (*(u8 *)(g_0076F588 + 0x11)) = 0x80;
  (*(u16 *)(g_0076F588 + 0xC)) = (*(u16 *)(g_0043FCE8 + 0x4));
  (*(u16 *)(g_0076F588 + 0x2)) = (*(u16 *)(g_0043FCE8 + 0x2));
  (*(u16 *)(g_0076F588 + 0xE)) = (*(u16 *)(g_0043FCE8 + 0x6));
  (*(u16 *)(g_0076F588 + 0x0)) = (*(u16 *)(g_0043FCE8 + 0x0));
  (*(u8 *)(g_0076F588 + 0x12)) = 0xc;
  (*(u16 *)(g_0076F588 + 0x8)) = (*(u16 *)(g_0043FCE8 + 0x0));
  return;
}

/* 0x002782D0, 0x28 bytes. */
int func_002782D0(int param_1)
{
  if ((param_1 < 0) || (4 < param_1)) {
    param_1 = 0;
  }
  return param_1;
}

/* 0x002786B0, 0xA4 bytes. */
void func_002786B0(void)
{
  func_00278CF0();
  if ((*(u8 *)(g_0076F3D4 + 0x0)) != 0) {
    func_00273D00();
  }
  func_00273D50();
  if (4 < (*(u8 *)(g_0076F3D4 + 0x0))) {
    func_002743E0();
    func_002754A0();
    func_00274400();
  }
  if ((((*(u8 *)(g_0076F3D4 + 0x3)) < 2) && ((*(u32 *)(g_0076F3D4 + 0xC)) != 0)) && (0xc < (*(u8 *)(g_0076F3D4 + 0x0)))) {
    func_00274550();
  }
  return;
}

/* 0x00278760, 0x78 bytes. */
void func_00278760(void)
{
  func_0023AF50(3,1);
  if ((*(u32 *)(g_0076F3A0 + 0x8)) == 0) {
    func_00101400(0);
    (*(u32 *)(g_0076F3A0 + 0x8)) = func_001026D0(1,4,0,1,0,0,0x43fd98,0x6d3);
    (*(u32 *)(g_0076F3A0 + 0x0)) = 0;
  }
  return;
}

/* 0x002787E0, 0x88 bytes. */
void func_002787E0(void)
{
    int iVar1;

  
  iVar1 = 0x305;
  do {
    func_0023ACC0(iVar1,1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 799);
  func_0023ACC0(0x302,2);
  func_0023ACC0(0x300,0);
  func_0023ADA0();
  if ((*(u32 *)(g_0076F3A0 + 0x8)) != 0) {
    func_00102EC0();
    (*(u32 *)(g_0076F3A0 + 0x8)) = 0;
    (*(u32 *)(g_0076F3A0 + 0x0)) = 0;
  }
  return;
}

/* 0x00278870, 0x78 bytes. */
void func_00278870(void)
{
  if ((*(u32 *)(g_0076F3A0 + 0xC)) == 0) {
    func_00103000(0);
    (*(u32 *)(g_0076F3A0 + 0xC)) = func_001026D0(1,5,0,0,0,0,0x43fd98,0x6f8);
    func_00103000(1);
    func_00102960(0);
    (*(u32 *)(g_0076F3A0 + 0x0)) = 0;
  }
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

/* 0x0027F980, 0x2D8 bytes. */
void func_0027F980(void)
{
    int bVar1;
    int iVar3;
    int iVar4;
    u32 uVar2;
    u32 uVar5;

  
  func_00247B20();
  uVar5 = 1;
  if (1 < g_0045D564) {
    do {
      func_0027EF30(uVar5);
      uVar5 = uVar5 + 1;
    } while (uVar5 < g_0045D564);
  }
  uVar5 = func_00196A10();
  uVar2 = 0;
  if (uVar5 != 0) {
    if (8 < uVar5) {
      iVar3 = 0;
      do {
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2);
        *(u8 *)(iVar4 + 0x69) = *(u8 *)(iVar4 + 0x69) | bVar1;
        *(u8 *)(iVar4 + 0x69) = *(u8 *)(iVar4 + 0x69) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 1);
        *(u8 *)(iVar4 + 0xd9) = *(u8 *)(iVar4 + 0xd9) | bVar1;
        *(u8 *)(iVar4 + 0xd9) = *(u8 *)(iVar4 + 0xd9) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 2);
        *(u8 *)(iVar4 + 0x149) = *(u8 *)(iVar4 + 0x149) | bVar1;
        *(u8 *)(iVar4 + 0x149) = *(u8 *)(iVar4 + 0x149) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 3);
        *(u8 *)(iVar4 + 0x1b9) = *(u8 *)(iVar4 + 0x1b9) | bVar1;
        *(u8 *)(iVar4 + 0x1b9) = *(u8 *)(iVar4 + 0x1b9) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 4);
        *(u8 *)(iVar4 + 0x229) = *(u8 *)(iVar4 + 0x229) | bVar1;
        *(u8 *)(iVar4 + 0x229) = *(u8 *)(iVar4 + 0x229) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 5);
        *(u8 *)(iVar4 + 0x299) = *(u8 *)(iVar4 + 0x299) | bVar1;
        *(u8 *)(iVar4 + 0x299) = *(u8 *)(iVar4 + 0x299) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 6);
        *(u8 *)(iVar4 + 0x309) = *(u8 *)(iVar4 + 0x309) | bVar1;
        *(u8 *)(iVar4 + 0x309) = *(u8 *)(iVar4 + 0x309) & ~(bVar1 ^ 0x4f);
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2 + 7);
        uVar2 = uVar2 + 8;
        iVar3 = iVar3 + 0x380;
        *(u8 *)(iVar4 + 0x379) = *(u8 *)(iVar4 + 0x379) | bVar1;
        *(u8 *)(iVar4 + 0x379) = *(u8 *)(iVar4 + 0x379) & ~(bVar1 ^ 0x4f);
      } while (uVar2 < uVar5 - 8);
    }
    if (uVar2 < uVar5) {
      iVar3 = uVar2 * 0x70;
      do {
        iVar4 = g_700001D0 + iVar3;
        bVar1 = *(u8 *)(g_0045D54C + uVar2);
        uVar2 = uVar2 + 1;
        iVar3 = iVar3 + 0x70;
        *(u8 *)(iVar4 + 0x69) = *(u8 *)(iVar4 + 0x69) | bVar1;
        *(u8 *)(iVar4 + 0x69) = *(u8 *)(iVar4 + 0x69) & ~(bVar1 ^ 0x4f);
      } while (uVar2 < uVar5);
    }
  }
  g_0045D54C = 0;
  g_0045D548 = 0;
  return;
}
