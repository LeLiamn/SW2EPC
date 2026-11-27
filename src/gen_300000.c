/*
 * gen_300000.c - small functions between 0x00300000 and 0x00380000, generated from Ghidra
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

extern u8 g_007B4E60[0x18];
extern u8 g_007B9A30[0x18];
#define true 1
#define false 0

extern u8 g_00428348[0x4];
extern u8 g_00428B79[0x15];
extern u8 g_0045D898[0x4];
extern u8 g_0050074C[0x1A];
extern u8 g_00669DB2[0x1];
extern u8 g_006935DC[0x1];
extern u8 g_007B5A40[0x8];
extern u8 g_007B5E20[0x30];
extern u8 g_007B9890[0xF3];
extern u8 g_007B98A8[0x4];
extern u8 g_007B98B0[0xD2];
extern u8 g_007B99F0[0x40];
extern u8 g_007B99F4[0x3A];
extern int g_0045CFEC;   /* (small data) */
extern int g_0045D6D0;   /* (small data) */
extern int g_0045D6DC;   /* (small data) */
extern int g_0045D6E0;   /* (small data) */
extern int g_0045D6E8;   /* (small data) */
extern int g_0045D6F0;   /* (small data) */
extern int g_0045D6F8;   /* (small data) */
extern int g_0045D7C0;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */

int func_001026D0();
int func_00102960();
int func_0011ED38();
int func_001204B0();
int func_0017E0C0();
int func_001AFC50();
int func_001AFFB0();
int func_0023AA10();
int func_0023AA40();
int func_0023AD10();
int func_002F2840();
int func_002F2890();
int func_002F2970();
int func_002F2DA0();
int func_002F2E20();
int func_002F3070();
int func_002F31F0();
int func_002F32F0();
int func_002F3380();
int func_002F3440();
int func_002F34E0();
int func_002F3550();
int func_002F3660();
int func_002F3B30();
int func_002F3CF0();
int func_002F3DC0();
int func_002F3E70();
int func_002F3EC0();
int func_002F4080();
int func_002F40F0();
int func_002F41E0();
int func_002F4250();
int func_002F43C0();
int func_002F4510();
int func_002F56A0();
int func_002F57A0();
int func_002F57F0();
int func_002F5840();
int func_002F5930();
int func_002F5BE0();
int func_002F5CC0();
int func_002F70A0();
int func_002F7410();
int func_002F7550();
int func_002F77F0();
int func_002F7B10();
int func_002F7C40();
int func_002F7D90();
int func_002FA490();
int func_002FAFA0();
int func_002FB2A0();
int func_002FB2D0();
int func_002FB3B0();
int func_002FB430();
int func_002FC2C0();
int func_002FC560();
int func_003097D0();
int func_0030AB90();
int func_0030AD20();
int func_0030AFF0();
int func_0030B240();
int func_0030CB00();
int func_0030CB50();
int func_0030CB80();
int func_0030E0F0();
int func_0030E390();
int func_00313D10();
int func_00314030();
int func_0031BD90();
int func_0031D690();
int func_0031D830();
int func_0031DAB0();
int func_0031DB50();
int func_0031DF40();
int func_0031EB20();
int func_0031EBC0();
int func_0031ECE0();
int func_003200B0();
int func_00323BD0();
int func_00323CD0();
int func_003240D0();
int func_00324340();
int func_00325360();
int func_00325C60();
int func_003264A0();
int func_00327820();
int func_00327950();
int func_00327C70();
int func_00327D50();
int func_00327E50();
int func_003280C0();
int func_003280E0();
int func_00328270();
int func_003282C0();
int func_00328360();
int func_003283D0();
int func_00328570();
int func_00328670();
int func_003286E0();
int func_00328970();
int func_00329D60();
int func_00329D80();
int func_00329D90();
int func_0032BBD0();
int func_0032C050();
int func_0032C920();
int func_0032C940();
int func_0032C9D0();
int func_0032CEE0();
int func_0032D9C0();
int func_0032E760();
int func_0032E790();
int func_003378E0();
int func_003379A0();
int func_00337A10();
int func_00337A70();
int func_00337AB0();
int func_00337FF0();
int func_00338150();
int func_003382B0();
int func_0033B1E0();
int func_0033B730();
int func_0033DCA0();
int func_0033DDC0();
int func_0033F070();
int func_00348C90();
int func_00349DF0();
int func_0034AB10();
int func_00369880();
int func_0036A560();
int func_0036E680();
int func_00371230();
int func_003712C0();
int func_00372540();
int func_00372580();
int func_00373050();
int func_00373540();
int func_00373640();
int func_003736B0();
int func_00373720();
int func_003737A0();
int func_00373B60();
int func_00373F60();
int func_00374040();
int func_00374250();
int func_00374E00();
int func_00374EE0();
int func_003752D0();
int func_00375B90();
int func_00375CF0();
int func_0037E920();
int func_003890C0();
int func_00390760();
int func_0039B980();
int func_0039E650();
int func_0039E760();
int func_0039E7C0();
int func_0039F960();
int func_003A7C10();
int func_003A7ED0();
int func_003A80A0();
int func_003A9010();
int func_003A90D0();
int func_003A9440();
int func_003A9460();
int func_003A9480();
int func_003DC2D0();
void func_0031F480(void);
void func_0031F720(void);
void func_0031F8B0(void);
void func_0031FA00(void);
void func_0031FB40(void);
void func_0031FDD0(int param_1);
void func_0031FF20(void);
int func_0031FF80(void);
void func_00320450(void);
void func_00320B50(void);
int func_003215F0(void);
void func_00321A20(int param_1, int param_2, int param_3);
void func_003228F0(int param_1, int param_2, int param_3, int param_4, int param_5, u32 *param_6);
int func_003238D0(int param_1);
void func_00323E60(u32 *param_1);
int func_003241C0(int param_1, int param_2, int param_3, int param_4, u32 *param_5, u32 *param_6, int param_7, u32 *param_8, int *param_9);
int func_003246C0();
void func_00325C90(void);
void func_003263F0(u32 *param_1);
void func_003266A0(void);
int func_00326850();
void func_00326A90(void);
void func_00326BD0(void);
void func_00326D30(void);
void func_00327190(int param_1, u8 *param_2);
int func_0032A040(int param_1, int param_2);
void func_0032B7B0(void);
void func_0032B990(void);
int func_0032BC30(void);
void func_0032CF30(int param_1, int param_2, int param_3, int param_4);
int func_0032D270();
void func_0032D300(int param_1, int param_2, int param_3);
int func_00338030(void);
void func_003380F0(void);
int func_00338190(void);
void func_00338250(void);
int func_003382F0(void);
void func_003383B0(void);
void func_0036E740(int param_1);
int func_00370570(int *param_1, int param_2);
void func_003710F0(int param_1);
void func_00371310(void);
void func_00371520(void);
int func_00371F00(void);
void func_003737E0(int param_1, int param_2, int param_3, int param_4);
int func_00373DF0(int param_1, int param_2);
int func_00373FB0(int param_1);
int func_003740F0(int param_1);
int func_003748C0();
void func_00374E20(void);
void func_003755E0(void);
void func_00375760(void);
void func_003758F0(void);
int func_00375B00(void);
void func_00375C20(int param_1, int param_2, int param_3, int param_4, int param_5);
int func_00375D90(void);
void func_00376100(int param_1, int param_2, int param_3);
void func_003762F0(void);
void func_0037E9F0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);

/* 0x0031F480, 0x29C bytes. */
void func_0031F480(void)
{
    int iVar1;
    int iVar2;
    int lVar6;
    u32 uVar3;
    int uVar4;
    int uVar5;
    int uVar7;
    int uVar8;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x210) * 4 + iVar2 + 0x1e0);
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar7 = 0;
  }
  else {
    uVar7 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar8 = 0;
  }
  else {
    uVar8 = (*(u16 *)(g_0050074C + 0x2));
  }
  if ((uVar7 & 0x40) == 0) {
    if ((uVar7 & 0x10) == 0) {
      if ((uVar8 & 0x4000) == 0) {
        if ((uVar8 & 0x1000) != 0) {
          if (*(int *)(iVar2 + 0x214) == 0) {
            if (((uVar7 & 0x1000) != 0) && (iVar1 != 1)) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(int *)(iVar2 + 0x214) = iVar1 + -1;
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + -1;
          }
        }
      }
      else if (*(int *)(iVar2 + 0x214) == iVar1 + -1) {
        if (((uVar7 & 0x4000) != 0) && (*(int *)(iVar2 + 0x214) != 0)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(u32 *)(iVar2 + 0x214) = 0;
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + 1;
      }
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      *(u32 *)(iVar2 + 0x218) = 0xffffffff;
      *(u32 *)(iVar2 + 0x214) = 0;
      func_0031DAB0();
      func_0031DF40(0);
      func_003890C0(0);
    }
  }
  else {
    uVar4 = func_0031D690(iVar2);
    uVar5 = func_00327D50();
    lVar6 = func_00314030(uVar4,uVar5);
    if (lVar6 == 0) {
      func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
    }
    else {
      *(u32 *)(iVar2 + 0x21c) = *(u32 *)(iVar2 + 0x214);
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      *(int *)(*(int *)(iVar2 + 0x230) + 4) = (int)uVar4;
      *(u32 *)(iVar2 + 0x22c) = 1;
      uVar3 = func_00313D10(*(u32 *)(*(int *)(iVar2 + 0x230) + 4));
      *(u32 *)(iVar2 + 0x224) = uVar3;
      func_0031DF40(2);
    }
  }
  return;
}

/* 0x0031F720, 0x18C bytes. */
void func_0031F720(void)
{
    int iVar1;
    int iVar2;
    int lVar4;
    u32 uVar3;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(iVar2 + 0x230);
  lVar4 = func_0032E790();
  if (lVar4 == 0) {
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x228) = 0x19f;
        func_0031DF40(2);
      }
      else {
        *(u32 *)(iVar1 + 8) = 0x19f;
        func_0031DF40(7);
      }
    }
    else {
      *(u32 *)(iVar1 + 8) = 0x19f;
      func_0031DF40(7);
    }
  }
  lVar4 = func_0032D9C0();
  if (lVar4 == 1) {
    uVar3 = func_0032E760();
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x228) = uVar3;
        func_0031DF40(2);
      }
      else {
        *(u32 *)(iVar1 + 8) = uVar3;
        func_0031DF40(7);
      }
    }
    else {
      *(u32 *)(iVar1 + 8) = uVar3;
      func_0031DF40(7);
    }
  }
  else if (lVar4 == 0) {
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x214) = 0;
        *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(1);
      }
      else {
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(2);
      }
    }
    else {
      *(u32 *)(iVar2 + 0x214) = 0;
      *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
      *(u32 *)(iVar2 + 0x228) = 0xffffffff;
      func_0031DF40(1);
    }
  }
  return;
}

/* 0x0031F8B0, 0x150 bytes. */
void func_0031F8B0(void)
{
    int iVar1;
    int iVar2;
    int lVar4;
    u32 uVar3;
    int uVar5;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(iVar2 + 0x230);
  lVar4 = func_00374250();
  if (lVar4 == 1) {
    func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
    func_00373F60();
    uVar5 = func_00374E00();
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        uVar3 = func_0030AFF0(uVar5);
        *(u32 *)(iVar2 + 0x228) = uVar3;
        func_0031DF40(2);
      }
      else {
        uVar3 = func_0030AFF0(uVar5);
        *(u32 *)(iVar1 + 8) = uVar3;
        func_0031DF40(7);
      }
    }
    else {
      uVar3 = func_0030AFF0(uVar5);
      *(u32 *)(iVar1 + 8) = uVar3;
      func_0031DF40(7);
    }
  }
  else if (lVar4 == 0) {
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x214) = 0;
        *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(1);
      }
      else {
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(2);
      }
    }
    else {
      *(u32 *)(iVar2 + 0x214) = 0;
      *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
      *(u32 *)(iVar2 + 0x228) = 0xffffffff;
      func_0031DF40(1);
    }
  }
  return;
}

/* 0x0031FA00, 0x138 bytes. */
void func_0031FA00(void)
{
    int iVar1;
    int iVar2;
    int lVar4;
    u32 uVar3;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(iVar2 + 0x230);
  lVar4 = func_00374250();
  if (lVar4 == 1) {
    func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
    func_00373F60();
    uVar3 = func_00374E00();
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x228) = uVar3;
        func_0031DF40(2);
      }
      else {
        *(u32 *)(iVar1 + 8) = uVar3;
        func_0031DF40(7);
      }
    }
    else {
      *(u32 *)(iVar1 + 8) = uVar3;
      func_0031DF40(7);
    }
  }
  else if (lVar4 == 0) {
    lVar4 = func_0031EBC0();
    if (lVar4 == 0) {
      if (*(int *)(iVar2 + 0x228) == -1) {
        *(u32 *)(iVar2 + 0x214) = 0;
        *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(1);
      }
      else {
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(2);
      }
    }
    else {
      *(u32 *)(iVar2 + 0x214) = 0;
      *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
      *(u32 *)(iVar2 + 0x228) = 0xffffffff;
      func_0031DF40(1);
    }
  }
  return;
}

/* 0x0031FB40, 0x290 bytes. */
void func_0031FB40(void)
{
    int iVar1;
    int iVar2;
    int lVar3;
    int uVar4;
    int uVar5;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(iVar2 + 0x230);
  lVar3 = func_003DC2D0(0xd);
  if (lVar3 == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x2));
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar5 & 0x40) == 0) {
      if ((uVar5 & 0x10) == 0) {
        if ((uVar4 & 0x1000) == 0) {
          if ((uVar4 & 0x4000) != 0) {
            if ((*(u32 *)(g_007B5A40 + 0x4)) == (*(u32 *)(g_007B5A40 + 0x0)) + -1) {
              if ((0 < (*(u32 *)(g_007B5A40 + 0x0))) && ((uVar5 & 0x4000) != 0)) {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007B5A40 + 0x4)) = ((*(u32 *)(g_007B5A40 + 0x4)) + 1) % (*(u32 *)(g_007B5A40 + 0x0));
              }
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              (*(u32 *)(g_007B5A40 + 0x4)) = ((*(u32 *)(g_007B5A40 + 0x4)) + 1) % (*(u32 *)(g_007B5A40 + 0x0));
            }
          }
        }
        else if ((*(u32 *)(g_007B5A40 + 0x4)) == 0) {
          if ((0 < (*(u32 *)(g_007B5A40 + 0x0))) && ((uVar5 & 0x1000) != 0)) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u32 *)(g_007B5A40 + 0x4)) = ((*(u32 *)(g_007B5A40 + 0x4)) + (*(u32 *)(g_007B5A40 + 0x0)) + -1) % (*(u32 *)(g_007B5A40 + 0x0));
          }
        }
        else {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          (*(u32 *)(g_007B5A40 + 0x4)) = ((*(u32 *)(g_007B5A40 + 0x4)) + (*(u32 *)(g_007B5A40 + 0x0)) + -1) % (*(u32 *)(g_007B5A40 + 0x0));
        }
      }
      else {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        *(u32 *)(iVar2 + 0x214) = 0;
        *(u32 *)(iVar2 + 0x21c) = 0xffffffff;
        *(u32 *)(iVar2 + 0x228) = 0xffffffff;
        func_0031DF40(1);
      }
    }
    else {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      *(int *)(iVar1 + 8) = (*(u32 *)(g_007B5A40 + 0x4));
      func_0031DF40(7);
    }
  }
  return;
}

/* 0x0031FDD0, 0x144 bytes, matching. */
void func_0031FDD0(int param_1)
{
    int bVar2;
    int iVar1;
    int iVar3;
    int iVar4;
    int lVar5;

  
  iVar3 = func_002FC2C0();
  iVar1 = *(int *)(iVar3 + 0x694);
  *(u32 *)(*(int *)(iVar1 + 0x230) + 0xc) = *(u32 *)(iVar1 + 0x228);
  func_0031BD90(*(u32 *)(iVar1 + 0x230),0);
  iVar4 = func_003280E0();
  func_003280C0(iVar4 + -1);
  func_0039F960();
  *(u32 *)(iVar1 + 0x218) = 0xffffffff;
  bVar2 = false;
  *(u32 *)(iVar1 + 0x210) = 0;
  *(u32 *)(iVar1 + 0x214) = 0;
  *(u32 *)(*(int *)(iVar1 + 0x230) + 4) = 100;
  *(u32 *)(iVar1 + 0x22c) = 0;
  if (param_1 == 1) {
    lVar5 = func_00328570();
    if (lVar5 == 4) {
      bVar2 = true;
      func_00328360(0x59);
    }
  }
  else if ((param_1 == 2) && (lVar5 = func_00328970(), lVar5 == 4)) {
    bVar2 = true;
    func_00328670(0x5a);
  }
  *(u32 *)(iVar3 + 0x6c4) = 1;
  func_002FC560();
  if (bVar2) {
    if (param_1 == 1) {
      func_003283D0(0x59);
    }
    else if (param_1 == 2) {
      func_003286E0(0x5a);
    }
  }
  func_0031DF40(8);
  return;
}

/* 0x0031FF20, 0x54 bytes, matching. */
void func_0031FF20(void)
{
    u32 * puVar1;

  
  puVar1 = (u32 *)func_002FC2C0();
  if (puVar1[0x1b1] == 1) {
    func_00376100(4,0xffffffffffffffff,0xffffffffffffffff);
    puVar1[0x1b1] = 0;
  }
  func_0031DF40(0);
  *puVar1 = 0;
  return;
}

/* 0x0031FF80, 0xD8 bytes, matching. */
int func_0031FF80(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  switch(*(u32 *)(*(int *)(iVar1 + 0x694) + 0x220)) {
  case 0:
    func_0031EB20();
    break;
  case 1:
    func_0031F480();
    break;
  case 2:
    func_0031ECE0();
    break;
  case 3:
    func_0031F720();
    break;
  case 4:
    func_0031F8B0();
    break;
  case 5:
    func_0031FA00();
    break;
  case 6:
    func_0031FB40();
    break;
  case 7:
    func_0031FDD0(0);
    break;
  case 8:
    func_0031FF20();
  }
  return 5;
}

/* 0x00320450, 0x2A0 bytes. */
void func_00320450(void)
{
    int iVar1;
    int iVar2;
    int lVar5;
    u32 uVar3;
    int uVar4;
    int uVar6;
    int uVar7;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x210) * 4 + iVar2 + 0x1e0);
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar6 = 0;
  }
  else {
    uVar6 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar7 = 0;
  }
  else {
    uVar7 = (*(u16 *)(g_0050074C + 0x2));
  }
  if ((uVar6 & 0x40) == 0) {
    if ((uVar6 & 0x10) == 0) {
      if ((uVar7 & 0x4000) == 0) {
        if ((uVar7 & 0x1000) != 0) {
          if (*(int *)(iVar2 + 0x214) == 0) {
            if (((uVar6 & 0x1000) != 0) && (iVar1 != 1)) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(int *)(iVar2 + 0x214) = iVar1 + -1;
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + -1;
          }
        }
      }
      else if (*(int *)(iVar2 + 0x214) == iVar1 + -1) {
        if (((uVar6 & 0x4000) != 0) && (*(int *)(iVar2 + 0x214) != 0)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(u32 *)(iVar2 + 0x214) = 0;
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + 1;
      }
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      *(u32 *)(iVar2 + 0x218) = 0xffffffff;
      *(u32 *)(iVar2 + 0x214) = 0;
      *(int *)(iVar2 + 0x210) = *(int *)(iVar2 + 0x210) + -7;
      func_0031DB50();
      func_0031DF40(0);
      func_003890C0(0);
    }
  }
  else {
    uVar4 = func_0031D690(iVar2);
    lVar5 = func_003200B0(uVar4);
    if (lVar5 == 0) {
      func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
    }
    else {
      *(u32 *)(iVar2 + 0x21c) = *(u32 *)(iVar2 + 0x214);
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      *(int *)(*(int *)(iVar2 + 0x230) + 4) = (int)uVar4;
      *(u32 *)(iVar2 + 0x22c) = 1;
      uVar3 = func_00313D10(*(u32 *)(*(int *)(iVar2 + 0x230) + 4));
      *(u32 *)(iVar2 + 0x224) = uVar3;
      func_0031DF40(7);
    }
  }
  return;
}

/* 0x00320B50, 0x2E4 bytes. */
void func_00320B50(void)
{
    int iVar1;
    int iVar2;
    int lVar5;
    u32 * puVar3;
    u32 uVar4;
    int uVar6;
    int uVar7;
    int uVar8;
    int uVar9;

  
  puVar3 = (u32 *)func_002FC2C0();
  iVar1 = puVar3[0x1a5];
  iVar2 = *(int *)(*(int *)(iVar1 + 0x210) * 4 + iVar1 + 0x1e0);
  lVar5 = func_003DC2D0(0x10);
  if ((lVar5 == 0) && (lVar5 = func_003DC2D0(0x11), lVar5 == 0)) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar8 = 0;
    }
    else {
      uVar8 = (*(u16 *)(g_0050074C + 0x0));
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar9 = 0;
    }
    else {
      uVar9 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar8 & 0x40) == 0) {
      if ((uVar8 & 0x10) == 0) {
        if (1 < iVar2) {
          if ((uVar9 & 0x4000) == 0) {
            if ((uVar9 & 0x1000) != 0) {
              if (*(int *)(iVar1 + 0x214) == 0) {
                if ((uVar8 & 0x1000) != 0) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  *(int *)(iVar1 + 0x214) = iVar2 + -1;
                }
              }
              else {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                *(int *)(iVar1 + 0x214) = *(int *)(iVar1 + 0x214) + -1;
              }
            }
          }
          else if (*(int *)(iVar1 + 0x214) == iVar2 + -1) {
            if ((uVar8 & 0x4000) != 0) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(u32 *)(iVar1 + 0x214) = 0;
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar1 + 0x214) = *(int *)(iVar1 + 0x214) + 1;
          }
        }
      }
      else {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        *(u32 *)(iVar1 + 0x21c) = 0xffffffff;
        *(u32 *)(iVar1 + 0x218) = 0xffffffff;
        *(u32 *)(iVar1 + 0x214) = 0;
        *(int *)(iVar1 + 0x210) = *(int *)(iVar1 + 0x210) + -7;
        func_0031D830(iVar1);
        func_0031DF40(0);
        func_002FC560();
        *puVar3 = 0;
        *(u32 *)(iVar1 + 0x210) = 0;
      }
    }
    else {
      uVar6 = func_0031D690(iVar1);
      uVar7 = func_00327D50();
      lVar5 = func_00314030(uVar6,uVar7);
      if (lVar5 == 0) {
        func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
      }
      else {
        *(u32 *)(iVar1 + 0x21c) = *(u32 *)(iVar1 + 0x214);
        func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
        *(int *)(*(int *)(iVar1 + 0x230) + 4) = (int)uVar6;
        *(u32 *)(iVar1 + 0x22c) = 1;
        uVar4 = func_00313D10(*(u32 *)(*(int *)(iVar1 + 0x230) + 4));
        *(u32 *)(iVar1 + 0x224) = uVar4;
        func_0031DF40(7);
      }
    }
  }
  return;
}

/* 0x003215F0, 0x1D0 bytes. */
int func_003215F0(void)
{
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar9;
    int lVar6;
    int lVar8;
    u32 * puVar2;
    u32 uVar1;
    int uVar7;

  
  puVar2 = (u32 *)func_002F7B10();
  iVar3 = func_002F7D90(0,0x2f85e0,0,0,0,0);
  iVar9 = 0;
  if (0 < iVar3) {
    do {
      uVar1 = *puVar2;
      if (uVar1 < 0x19f) {
        iVar4 = func_00327C70();
        iVar5 = func_002F3380(uVar1);
        if (((2 < iVar4 - iVar5) && (lVar6 = func_0030CB50(0x32), lVar6 == 0)) &&
           (lVar6 = func_002F2840(uVar1), lVar6 != 0)) {
          iVar4 = 0;
          iVar5 = 0;
          do {
            uVar7 = func_002F5CC0(uVar1);
            lVar6 = func_0030AD20(uVar7,iVar5);
            lVar8 = func_0030AB90();
            if (lVar6 < lVar8) {
              iVar4 = iVar4 + 1;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 < 6);
          if (iVar4 != 0) {
            if (iVar4 == 0) {
              iVar4 = 0;
            }
            else {
              g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
              iVar4 = (int)(g_7000015C >> 0x10) % iVar4;
            }
            uVar7 = func_002F5CC0(uVar1);
            lVar6 = func_0030AD20(uVar7,iVar4);
            if (lVar6 != 0x19) {
              func_002F5BE0(uVar1,lVar6);
              uVar7 = func_00327C70();
              func_002F32F0(uVar1,uVar7);
            }
          }
        }
      }
      iVar9 = iVar9 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar9 < iVar3);
  }
  return 0;
}

/* 0x00321A20, 0xF0 bytes. */
void func_00321A20(int param_1, int param_2, int param_3)
{
    int bVar1;
    int iVar3;
    u32 uVar2;
    int uVar4;

  
  func_002F3B30(param_1,1);
  func_002F3CF0(param_1,0);
  uVar4 = func_00327C70();
  func_002F32F0(param_1,uVar4);
  if (param_3 == 0) {
    uVar2 = func_002F3070(param_1);
    bVar1 = false;
    if (-1 < (int)uVar2) {
      iVar3 = func_0030AB90();
      bVar1 = (int)uVar2 < iVar3;
    }
    if (!bVar1) {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      uVar2 = (g_7000015C >> 0x10) % 0x19;
    }
    func_002F5BE0(param_1,uVar2);
  }
  else {
    uVar4 = func_002F5CC0(param_2);
    func_002F5BE0(param_1,uVar4);
  }
  return;
}

/* 0x003228F0, 0x200 bytes. */
void func_003228F0(int param_1, int param_2, int param_3, int param_4, int param_5, u32 *param_6)
{
    int iVar10;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar9;
    int lVar6;
    u32 uVar1;
    u32 uVar5;
    u32 uVar7;
    u32 uVar8;

  
  iVar2 = func_002FA490();
  iVar10 = 0;
  if (0 < param_5) {
    iVar9 = (iVar2 + 2) * 10 + param_2 * param_3;
    do {
      uVar1 = *param_6;
      iVar3 = func_002F41E0(uVar1);
      if (param_4 < iVar3 + 1) {
        if (param_4 == iVar3) {
          iVar4 = iVar9 + 5;
        }
        else {
          iVar4 = iVar9;
          if (param_4 != iVar3 + -1) {
            iVar4 = 0;
          }
        }
      }
      else {
        iVar4 = iVar9 + 10;
      }
      if ((iVar4 != 0) && (lVar6 = func_0030CB50(), lVar6 != 0)) {
        uVar8 = param_4 + 1;
        if (0x13 < (int)uVar8) {
          uVar8 = 0x13;
        }
        iVar4 = func_002F34E0(uVar1);
        iVar4 = ((*(int *)((g_00428348 + 0x0) + (uVar8 & 0xff) * 4) - iVar4) * 10) / (iVar2 + 2);
        if (3000 < iVar4) {
          iVar4 = 3000;
        }
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        func_002F3550(uVar1,iVar4);
        uVar5 = func_002F34E0(uVar1);
        uVar8 = 0;
        uVar7 = 0;
        do {
          if ((*(u32 *)((g_00428348 + 0x0) + (uVar7 & 0xff) * 4) <= uVar5) &&
             (uVar5 < *(u32 *)((g_00428348 + 0x0) + (uVar7 + 1 & 0xff) * 4))) {
            uVar8 = uVar7 & 0xff;
            break;
          }
          uVar7 = uVar7 + 1;
        } while ((int)uVar7 < 0x13);
        if (0x12 < (int)uVar7) {
          uVar8 = 0x13;
        }
        func_002F70A0(uVar1,uVar8,iVar3);
      }
      iVar10 = iVar10 + 1;
      param_6 = param_6 + 1;
    } while (iVar10 < param_5);
  }
  return;
}

/* 0x003238D0, 0x114 bytes. */
int func_003238D0(int param_1)
{
    int bVar1;
    int iVar4;
    int iVar7;
    int lVar5;
    int lVar6;
    u32 * puVar2;
    u32 uVar3;

  
  lVar5 = func_0030AFF0();
  puVar2 = (u32 *)func_002F7B10();
  bVar1 = false;
  if (-1 < lVar5) {
    lVar6 = func_0030AB90();
    bVar1 = lVar5 < lVar6;
  }
  if (bVar1) {
    lVar6 = func_002F7D90(0,0x2f7ec0,param_1,0,1,0);
    if (lVar6 == 0) {
      iVar4 = func_00323CD0(1,lVar5,param_1,puVar2);
      if (iVar4 != 0) {
        lVar5 = func_002FB2A0(lVar5);
        if (lVar5 == 0) {
          return 0;
        }
        iVar7 = 0;
        if (0 < iVar4) {
          do {
            lVar5 = func_002F3EC0(*puVar2);
            if (lVar5 != 0) {
              return 0;
            }
            iVar7 = iVar7 + 1;
            puVar2 = puVar2 + 1;
          } while (iVar7 < iVar4);
        }
      }
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

/* 0x00323E60, 0x94 bytes, matching. */
void func_00323E60(u32 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0xffffffff;
  param_1[2] = 0xffffffff;
  param_1[3] = 0xffffffff;
  param_1[4] = 0x19f;
  param_1[5] = 0xffffffff;
  param_1[6] = 0xffffffff;
  param_1[0x14] = 0xffffffff;
  param_1[0x1b] = 0xffffffff;
  param_1[7] = 0xffffffff;
  param_1[0x15] = 0xffffffff;
  param_1[0x1c] = 0xffffffff;
  param_1[8] = 0xffffffff;
  param_1[0x16] = 0xffffffff;
  param_1[0x1d] = 0xffffffff;
  param_1[9] = 0xffffffff;
  param_1[0x17] = 0xffffffff;
  param_1[0x1e] = 0xffffffff;
  param_1[10] = 0xffffffff;
  param_1[0x18] = 0xffffffff;
  param_1[0x1f] = 0xffffffff;
  param_1[0xb] = 0xffffffff;
  param_1[0x19] = 0xffffffff;
  param_1[0x20] = 0xffffffff;
  param_1[0xc] = 0;
  param_1[0x1a] = 0;
  param_1[0x21] = 0;
  param_1[0xd] = 0xffffffff;
  param_1[0xe] = 0xffffffff;
  param_1[0xf] = 0xffffffff;
  param_1[0x10] = 0xffffffff;
  param_1[0x11] = 0xffffffff;
  param_1[0x12] = 0xffffffff;
  param_1[0x13] = 0;
  return;
}

/* 0x003241C0, 0x17C bytes. */
int func_003241C0(int param_1, int param_2, int param_3, int param_4, u32 *param_5, u32 *param_6, int param_7, u32 *param_8, int *param_9)
{
    int iVar4;
    int iVar6;
    int lVar2;
    int lVar3;
    u32 * puVar5;
    u32 uVar1;

  
  lVar2 = func_002FB3B0(param_2);
  func_003240D0(param_4,*param_5);
  *param_9 = 0;
  iVar6 = 0;
  if (0 < param_7) {
    do {
      lVar3 = func_003097D0(*param_6);
      if (lVar3 == 0) {
        if (lVar2 == 0) {
          func_002F7410(*param_6);
        }
        else {
          iVar4 = *param_9;
          uVar1 = *param_6;
          *param_9 = iVar4 + 1;
          param_8[iVar4] = uVar1;
        }
      }
      iVar6 = iVar6 + 1;
      param_6 = param_6 + 1;
    } while (iVar6 < param_7);
  }
  iVar6 = *param_9;
  if (iVar6 != 0) {
    while (6 < iVar6) {
      iVar4 = 0;
      if (0 < iVar6) {
        puVar5 = param_8;
        do {
          lVar2 = func_002F3E70(*puVar5);
          if (lVar2 == 0) break;
          iVar4 = iVar4 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar4 < *param_9);
      }
      if (iVar4 < *param_9) {
        func_002F7410(param_8[iVar4]);
        param_8[iVar4] = param_8[*param_9 + -1];
        *param_9 = *param_9 + -1;
      }
      iVar6 = *param_9;
    }
  }
  return 0;
}

/* 0x00325C90, 0xAC bytes. */
void func_00325C90(void)
{
    int iVar1;
    int lVar2;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(iVar1 + 0x6a8);
  lVar2 = func_0039B980();
  if (lVar2 == 1) {
    *(u32 *)(iVar1 + 0x30) = 0;
    if (*(int *)(iVar1 + 0x4c) == 0) {
      if (*(u32 *)(iVar1 + 4) < 0x19f) {
        func_00325C60();
        *(u32 *)(iVar1 + 4) = 0xffffffff;
      }
      func_00325360(9);
    }
    else {
      lVar2 = func_002FB2A0(*(u32 *)(iVar1 + 8));
      if (lVar2 == 0) {
        func_00325360(8);
      }
      else {
        func_00325360(7);
      }
    }
  }
  return;
}

/* 0x003263F0, 0x9C bytes, matching. */
void func_003263F0(u32 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0xffffffff;
  param_1[3] = 0xffffffff;
  param_1[2] = 0xffffffff;
  param_1[4] = 0x19f;
  param_1[5] = 0xffffffff;
  param_1[7] = 0;
  param_1[0xe] = 0xffffffff;
  param_1[0xf] = 0xffffffff;
  param_1[0x10] = 0xffffffff;
  param_1[0x11] = 0xffffffff;
  param_1[0x12] = 0xffffffff;
  param_1[0x13] = 0xffffffff;
  param_1[0x14] = 0xffffffff;
  param_1[0x15] = 0xffffffff;
  param_1[6] = 0;
  param_1[0x1c] = 0;
  param_1[0x23] = 0;
  param_1[8] = 0xffffffff;
  param_1[0x16] = 0xffffffff;
  param_1[0x1d] = 0xffffffff;
  param_1[9] = 0xffffffff;
  param_1[0x17] = 0xffffffff;
  param_1[0x1e] = 0xffffffff;
  param_1[10] = 0xffffffff;
  param_1[0x18] = 0xffffffff;
  param_1[0x1f] = 0xffffffff;
  param_1[0xb] = 0xffffffff;
  param_1[0x19] = 0xffffffff;
  param_1[0x20] = 0xffffffff;
  param_1[0xc] = 0xffffffff;
  param_1[0x1a] = 0xffffffff;
  param_1[0x21] = 0xffffffff;
  param_1[0xd] = 0xffffffff;
  param_1[0x1b] = 0xffffffff;
  param_1[0x22] = 0xffffffff;
  return;
}

/* 0x003266A0, 0x30 bytes. */
void func_003266A0(void)
{
    int lVar1;

  
  lVar1 = func_00375B90();
  if (lVar1 == 1) {
    func_003264A0();
  }
  return;
}

/* 0x00326A90, 0x138 bytes. */
void func_00326A90(void)
{
    int bVar2;
    int iVar1;
    int iVar4;
    int iVar5;
    int lVar3;

  
  iVar5 = func_002FC2C0();
  iVar5 = *(int *)(iVar5 + 0x6b8);
  lVar3 = func_0039B980();
  if (lVar3 == 1) {
    *(u32 *)(iVar5 + 0x18) = 0;
    if (*(u32 *)(iVar5 + 4) < 0x19f) {
      func_00325C60();
      *(u32 *)(iVar5 + 4) = 0xffffffff;
      iVar1 = *(int *)(iVar5 + 0xc);
      bVar2 = false;
      if (-1 < iVar1) {
        iVar4 = func_0030AB90();
        bVar2 = iVar1 < iVar4;
      }
      if ((bVar2) &&
         ((lVar3 = func_002FB3B0(*(u32 *)(iVar5 + 0xc)), lVar3 == 0 ||
          (lVar3 = func_002FB430(*(u32 *)(iVar5 + 0xc)), lVar3 == 0)))) {
        func_003264A0(3);
      }
      else {
        func_003264A0(1);
      }
    }
    else {
      iVar1 = *(int *)(iVar5 + 0xc);
      bVar2 = false;
      if (-1 < iVar1) {
        iVar4 = func_0030AB90();
        bVar2 = iVar1 < iVar4;
      }
      if ((bVar2) &&
         ((lVar3 = func_002FB3B0(*(u32 *)(iVar5 + 0xc)), lVar3 == 0 ||
          (lVar3 = func_002FB430(*(u32 *)(iVar5 + 0xc)), lVar3 == 0)))) {
        func_003264A0(3);
      }
      else {
        func_003264A0(1);
      }
    }
  }
  return;
}

/* 0x00326BD0, 0x15C bytes. */
void func_00326BD0(void)
{
    int bVar2;
    int iVar1;
    int iVar4;
    int iVar5;
    int lVar6;
    int uVar3;

  
  iVar4 = func_002FC2C0();
  iVar4 = *(int *)(iVar4 + 0x6b8);
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = (*(u16 *)(g_0050074C + 0x0));
  }
  lVar6 = func_003A9460();
  if ((lVar6 == 0) || ((uVar3 & 0x40) != 0)) {
    func_0023AA40();
    func_003A9440();
    func_003A7ED0();
    if (*(int *)(iVar4 + 0x1c) == 0) {
      iVar1 = *(int *)(iVar4 + 0xc);
      bVar2 = false;
      if (-1 < iVar1) {
        iVar5 = func_0030AB90();
        bVar2 = iVar1 < iVar5;
      }
      if ((bVar2) &&
         ((lVar6 = func_002FB3B0(*(u32 *)(iVar4 + 0xc)), lVar6 == 0 ||
          (lVar6 = func_002FB430(*(u32 *)(iVar4 + 0xc)), lVar6 == 0)))) {
        func_003264A0(3);
      }
      else if (*(int *)(iVar4 + 0x18) == 0) {
        func_003264A0(1);
      }
      else {
        func_0030E390(0xd,199,0xffffffffffffffff,0xffffffffffffffff,0,0);
        func_003264A0(5);
      }
    }
    else {
      func_003264A0(2);
    }
  }
  return;
}

/* 0x00326D30, 0x100 bytes. */
void func_00326D30(void)
{
    int bVar2;
    int iVar1;
    int iVar4;
    int iVar5;
    int lVar6;
    int uVar3;

  
  iVar4 = func_002FC2C0();
  iVar4 = *(int *)(iVar4 + 0x6b8);
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = (*(u16 *)(g_0050074C + 0x0));
  }
  lVar6 = func_003A9460();
  if ((lVar6 == 0) || ((uVar3 & 0x40) != 0)) {
    func_0023AA40();
    func_003A9440();
    iVar1 = *(int *)(iVar4 + 0xc);
    bVar2 = false;
    if (-1 < iVar1) {
      iVar5 = func_0030AB90();
      bVar2 = iVar1 < iVar5;
    }
    if ((bVar2) &&
       ((lVar6 = func_002FB3B0(*(u32 *)(iVar4 + 0xc)), lVar6 == 0 ||
        (lVar6 = func_002FB430(*(u32 *)(iVar4 + 0xc)), lVar6 == 0)))) {
      func_003264A0(3);
    }
    else {
      func_003264A0(1);
    }
  }
  return;
}

/* 0x00327190, 0x23C bytes. */
void func_00327190(int param_1, u8 *param_2)
{
    int iVar3;
    int lVar6;
    int uVar1;
    int uVar2;
    int uVar4;
    int uVar5;

  
  *param_2 = param_1;
  param_2[1] = 0;
  param_2[2] = 10;
  param_2[10] = 0;
  param_2[3] = 10;
  param_2[0xb] = 0;
  param_2[4] = 10;
  param_2[0xc] = 0;
  param_2[5] = 10;
  param_2[0xd] = 0;
  param_2[6] = 10;
  param_2[0xe] = 0;
  param_2[7] = 10;
  param_2[0xf] = 0;
  param_2[8] = 10;
  param_2[0x10] = 0;
  param_2[9] = 10;
  param_2[0x11] = 0;
  uVar5 = func_002F57F0();
  uVar4 = func_002F5840(uVar5);
  param_2[0x12] = uVar4;
  param_2[0x13] = 0;
  lVar6 = func_002F57F0(param_1);
  if (lVar6 != 0) {
    *param_2 = 0x7f;
  }
  lVar6 = func_002F57F0(param_1);
  if ((lVar6 == 3) && (lVar6 = func_002F57A0(param_1), lVar6 < 0x1e)) {
    iVar3 = (int)lVar6 * 0x13;
    uVar4 = ((g_00428B79 + 0x2))[iVar3];
    uVar1 = ((g_00428B79 + 0xA))[iVar3];
    param_2[1] = ((g_00428B79 + 0x0))[iVar3];
    param_2[2] = uVar4;
    param_2[10] = uVar1;
    uVar4 = ((g_00428B79 + 0xB))[iVar3];
    uVar1 = ((g_00428B79 + 0x4))[iVar3];
    param_2[3] = ((g_00428B79 + 0x3))[iVar3];
    param_2[0xb] = uVar4;
    param_2[4] = uVar1;
    uVar4 = ((g_00428B79 + 0x5))[iVar3];
    uVar1 = ((g_00428B79 + 0xD))[iVar3];
    param_2[0xc] = ((g_00428B79 + 0xC))[iVar3];
    uVar2 = ((g_00428B79 + 0x6))[iVar3];
    param_2[5] = uVar4;
    uVar4 = ((g_00428B79 + 0xE))[iVar3];
    param_2[0xd] = uVar1;
    uVar1 = ((g_00428B79 + 0x7))[iVar3];
    param_2[6] = uVar2;
    uVar2 = ((g_00428B79 + 0xF))[iVar3];
    param_2[0xe] = uVar4;
    uVar4 = ((g_00428B79 + 0x8))[iVar3];
    param_2[7] = uVar1;
    uVar1 = ((g_00428B79 + 0x10))[iVar3];
    param_2[0xf] = uVar2;
    param_2[8] = uVar4;
    param_2[0x10] = uVar1;
    uVar4 = ((g_00428B79 + 0x11))[iVar3];
    param_2[9] = ((g_00428B79 + 0x9))[iVar3];
    param_2[0x11] = uVar4;
  }
  return;
}

/* 0x0032A040, 0x124 bytes. */
int func_0032A040(int param_1, int param_2)
{
    int lVar2;
    int lVar3;
    int lVar4;
    int uVar1;

  
  uVar1 = func_00337A10();
  lVar2 = func_002F3DC0(uVar1);
  uVar1 = func_00337A10(param_2);
  lVar3 = func_002F3DC0(uVar1);
  uVar1 = func_00337A10(param_1);
  lVar4 = func_002F31F0(uVar1);
  if ((0x27 < param_1) && (param_1 < 0x1a4)) {
    if (lVar4 == 2) {
      return 1;
    }
    if (lVar4 == 1) {
      return 0;
    }
  }
  if (lVar2 < 3) {
    if (2 < lVar3) {
      return 1;
    }
  }
  else if (lVar2 == lVar3) {
    uVar1 = func_00337A10(param_1);
    lVar2 = func_002F7550(uVar1);
    uVar1 = func_00337A10(param_2);
    lVar3 = func_002F7550(uVar1);
    if (lVar2 < lVar3) {
      return 1;
    }
  }
  return 0;
}

/* 0x0032B7B0, 0x19C bytes. */
void func_0032B7B0(void)
{
    int bVar2;
    int iVar3;
    int iVar5;
    int iVar6;
    int iVar7;
    int * piVar1;
    int * piVar4;

  
  g_0045CFEC = 0xffffffff;
  g_0045D6DC = 0;
  g_0045D6D0 = func_001026D0(1,0xac,0,1,0,0,0x447a20,0x768);
  func_00102960(1);
  iVar7 = 0;
  iVar5 = 0;
  do {
    iVar3 = g_0045D6D0 + *(int *)(g_0045D6D0 + iVar5 + 4);
    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + iVar3;
    *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0xc) + iVar3;
    *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + iVar3;
    piVar1 = *(int **)(iVar3 + 4);
    iVar3 = *piVar1;
    iVar6 = 0;
    if (0 < iVar3) {
      if (8 < iVar3) {
        bVar2 = false;
        if ((-1 < iVar3) && (iVar3 < 0x7fffffff)) {
          bVar2 = true;
        }
        if (bVar2) {
          piVar4 = piVar1;
          do {
            iVar6 = iVar6 + 8;
            piVar4[1] = piVar4[1] + (int)piVar1;
            piVar4[2] = piVar4[2] + (int)piVar1;
            piVar4[3] = piVar4[3] + (int)piVar1;
            piVar4[4] = piVar4[4] + (int)piVar1;
            piVar4[5] = piVar4[5] + (int)piVar1;
            piVar4[6] = piVar4[6] + (int)piVar1;
            piVar4[7] = piVar4[7] + (int)piVar1;
            piVar4[8] = piVar4[8] + (int)piVar1;
            piVar4 = piVar4 + 8;
          } while (iVar6 < iVar3 + -8);
        }
      }
      if (iVar6 < iVar3) {
        piVar4 = piVar1 + iVar6;
        do {
          iVar6 = iVar6 + 1;
          piVar4[1] = piVar4[1] + (int)piVar1;
          piVar4 = piVar4 + 1;
        } while (iVar6 < iVar3);
      }
    }
    iVar7 = iVar7 + 1;
    iVar5 = iVar5 + 8;
  } while (iVar7 < 0x15c);
  return;
}

/* 0x0032B990, 0x158 bytes. */
void func_0032B990(void)
{
    int bVar2;
    int iVar3;
    int iVar5;
    int iVar6;
    int iVar7;
    int * piVar1;
    int * piVar4;

  
  g_0045D6DC = 0;
  iVar7 = 0;
  g_0045CFEC = 0xffffffff;
  iVar5 = 0;
  do {
    iVar3 = g_0045D6D0 + *(int *)(g_0045D6D0 + iVar5 + 4);
    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + iVar3;
    *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0xc) + iVar3;
    *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + iVar3;
    piVar1 = *(int **)(iVar3 + 4);
    iVar3 = *piVar1;
    iVar6 = 0;
    if (0 < iVar3) {
      if (8 < iVar3) {
        bVar2 = false;
        if ((-1 < iVar3) && (iVar3 < 0x7fffffff)) {
          bVar2 = true;
        }
        if (bVar2) {
          piVar4 = piVar1;
          do {
            iVar6 = iVar6 + 8;
            piVar4[1] = piVar4[1] + (int)piVar1;
            piVar4[2] = piVar4[2] + (int)piVar1;
            piVar4[3] = piVar4[3] + (int)piVar1;
            piVar4[4] = piVar4[4] + (int)piVar1;
            piVar4[5] = piVar4[5] + (int)piVar1;
            piVar4[6] = piVar4[6] + (int)piVar1;
            piVar4[7] = piVar4[7] + (int)piVar1;
            piVar4[8] = piVar4[8] + (int)piVar1;
            piVar4 = piVar4 + 8;
          } while (iVar6 < iVar3 + -8);
        }
      }
      if (iVar6 < iVar3) {
        piVar4 = piVar1 + iVar6;
        do {
          iVar6 = iVar6 + 1;
          piVar4[1] = piVar4[1] + (int)piVar1;
          piVar4 = piVar4 + 1;
        } while (iVar6 < iVar3);
      }
    }
    iVar7 = iVar7 + 1;
    iVar5 = iVar5 + 8;
  } while (iVar7 < 0x15c);
  return;
}

/* 0x0032BC30, 0x3B8 bytes. */
int func_0032BC30(void)
{
    int iVar2;
    int iVar3;
    int lVar4;
    int uVar1;
    u32 uVar5;

  
  uVar5 = 5;
  iVar2 = func_0032C050();
  if (g_0045D6E8 == 0) {
    func_0032BBD0();
    g_0045D6E8 = 1;
    func_003A90D0();
    func_0017E0C0(((u32)(*(u8 *)(g_00669DB2 + 0x0)) * 0x41) / 100 & 0xff,0xf);
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  lVar4 = func_0032CEE0();
  if ((((lVar4 == 1) || (lVar4 = func_0032CEE0(), lVar4 == 3)) &&
      ((lVar4 = func_0032C920(1), lVar4 == 1 || (lVar4 = func_0032C920(), lVar4 == 3)))) &&
     ((lVar4 = func_0032C920(0), lVar4 == 1 || (lVar4 = func_0032C920(0), lVar4 == 3)))) {
    if (g_0045D6DC == 2) {
      g_0045D6E0 = g_0045D6E0 + -1;
      if (g_0045D6E0 < 1) {
        g_0045D6DC = 1;
      }
    }
    else if (g_0045D6DC == 0) {
      if (g_0045CFEC == -1) {
        iVar2 = func_00329D60();
        if (*(int *)(iVar2 + 0x34) == 2) {
          if ((uVar1 & 0x40) != 0) {
            func_00329D80(1);
          }
          lVar4 = func_00329D90();
          if (lVar4 != 0) {
            func_0023AA10(0);
            func_00369880(0);
            iVar2 = func_0032C050();
            func_0032C940(*(u32 *)(iVar2 + 0x4ed8),0x37f,0,0,0);
            iVar2 = func_0032C050();
            func_0032C940(*(u32 *)(iVar2 + 0x4edc),0x37f,1,0,0);
            iVar2 = func_0032C9D0();
            iVar3 = func_00329D60();
            func_0032CF30(*(u32 *)(iVar2 + 0xc41c),0x37f,*(u32 *)(iVar3 + 0x2c),0);
            func_003A90D0(0);
            func_0017E0C0((*(u8 *)(g_00669DB2 + 0x0)),0xf);
          }
        }
        else if ((uVar1 & 0x40) != 0) {
          func_0032BBD0();
        }
      }
      else {
        func_00375B00();
        func_003752D0();
        lVar4 = func_00375B90();
        if (lVar4 == 1) {
          g_0045CFEC = -1;
          func_00329D80();
        }
      }
    }
    else {
      iVar3 = func_0030E0F0();
      if (g_0045D6DC == 1) {
        func_001AFC50();
        g_0045D6DC = 3;
      }
      if ((*(char *)(g_006935DC + 0x0)) == '\x04') {
        *(u32 *)(iVar3 + 0x10) = 1;
        g_0045D6DC = 0;
      }
      else if ((*(char *)(g_006935DC + 0x0)) == '\x05') {
        *(u32 *)(iVar3 + 0x10) = 0;
        g_0045D6DC = 0;
      }
      if (g_0045D6DC == 0) {
        func_001AFFB0(1);
        *(u32 *)(iVar2 + 0x4ecc) = 2;
        func_003A7C10();
        func_00329D80(1);
      }
    }
  }
  lVar4 = func_0032CEE0();
  if ((((lVar4 == 3) && (lVar4 = func_0032C920(1), lVar4 == 3)) &&
      (lVar4 = func_0032C920(0), lVar4 == 3)) && ((g_0045D6DC == 0 && (g_0045CFEC == -1)))) {
    g_0045D6E8 = 0;
    uVar5 = 0;
  }
  return uVar5;
}

/* 0x0032CF30, 0x8C bytes. */
void func_0032CF30(int param_1, int param_2, int param_3, int param_4)
{
  if (param_4 == 0) {
    if (*(int *)(g_0045D6F0 + 0xc2c4) != 3) {
      *(u32 *)(g_0045D6F0 + 0xc2c4) = 2;
    }
  }
  else {
    if (*(int *)(g_0045D6F0 + 0xc2c8) == param_2) {
      return;
    }
    *(u32 *)(g_0045D6F0 + 0xc2c4) = 0;
    *(int *)(g_0045D6F0 + 0xc2c8) = param_2;
  }
  *(u32 *)(g_0045D6F0 + 0xc2c0) = 0;
  *(u32 *)(g_0045D6F0 + 0xc418) = param_3;
  *(u32 *)(g_0045D6F0 + 0xc41c) = param_1;
  return;
}

/* 0x0032D300, 0xBC bytes. */
void func_0032D300(int param_1, int param_2, int param_3)
{
  (*(u16 *)(g_007B5E20 + 0x26)) = (u16)param_3;
  (*(u32 *)(g_007B5E20 + 0x4)) = 0;
  (*(u8 *)(g_007B5E20 + 0x2A)) = 0;
  (*(u32 *)(g_007B5E20 + 0x8)) = 0;
  (*(u32 *)(g_007B5E20 + 0x1C)) = 0;
  (*(u32 *)(g_007B5E20 + 0xC)) = 0;
  (*(u16 *)(g_007B5E20 + 0x24)) = 0;
  (*(u32 *)(g_007B5E20 + 0x10)) = 0;
  (*(u32 *)(g_007B5E20 + 0x14)) = 0;
  (*(u32 *)(g_007B5E20 + 0x18)) = 1;
  (*(u8 *)(g_007B5E20 + 0x2B)) = 0;
  (*(u16 *)(g_007B5E20 + 0x22)) = 0;
  if (param_3 < 7) {
    (*(u16 *)(g_007B5E20 + 0x28)) = (*(u16 *)(g_007B5E20 + 0x26));
  }
  else {
    (*(u16 *)(g_007B5E20 + 0x28)) = 7;
  }
  (*(u32 *)(g_007B5E20 + 0x0)) = param_1;
  (*(u32 *)(g_007B5E20 + 0x2C)) = param_2;
  if (0 < param_3) {
    (*(u32 *)(g_007B5E20 + 0x1C)) = func_003A9480(1);
  }
  g_0045D6F8 = 0;
  return;
}

/* 0x00338030, 0xB8 bytes. */
int func_00338030(void)
{
    int iVar1;
    u32 uVar2;

  
  uVar2 = 5;
  iVar1 = func_002FC2C0();
  iVar1 = **(int **)(iVar1 + 0x6a0);
  if (iVar1 == 4) {
    func_00337A70();
  }
  else if (iVar1 == 3) {
    func_00337AB0();
    uVar2 = 0;
  }
  else if (iVar1 == 2) {
    func_003379A0();
  }
  else if (iVar1 == 1) {
    func_003378E0();
  }
  else {
    if (iVar1 != 0) {
      return 5;
    }
    func_00337FF0();
  }
  return uVar2;
}

/* 0x003380F0, 0x5C bytes. */
void func_003380F0(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  if (**(int **)(iVar1 + 0x6a0) == 2) {
    func_0036A560();
  }
  else if (**(int **)(iVar1 + 0x6a0) == 1) {
    func_00373B60();
  }
  return;
}

/* 0x00338190, 0xB8 bytes. */
int func_00338190(void)
{
    int iVar1;
    u32 uVar2;

  
  uVar2 = 5;
  iVar1 = func_002FC2C0();
  iVar1 = **(int **)(iVar1 + 0x6a0);
  if (iVar1 == 4) {
    func_00337A70();
  }
  else if (iVar1 == 3) {
    func_00337AB0();
    uVar2 = 0;
  }
  else if (iVar1 == 2) {
    func_003379A0();
  }
  else if (iVar1 == 1) {
    func_003378E0();
  }
  else {
    if (iVar1 != 0) {
      return 5;
    }
    func_00338150();
  }
  return uVar2;
}

/* 0x00338250, 0x5C bytes. */
void func_00338250(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  if (**(int **)(iVar1 + 0x6a0) == 2) {
    func_0036A560();
  }
  else if (**(int **)(iVar1 + 0x6a0) == 1) {
    func_00373B60();
  }
  return;
}

/* 0x003382F0, 0xB8 bytes. */
int func_003382F0(void)
{
    int iVar1;
    u32 uVar2;

  
  uVar2 = 5;
  iVar1 = func_002FC2C0();
  iVar1 = **(int **)(iVar1 + 0x6a0);
  if (iVar1 == 4) {
    func_00337A70();
  }
  else if (iVar1 == 3) {
    func_00337AB0();
    uVar2 = 0;
  }
  else if (iVar1 == 2) {
    func_003379A0();
  }
  else if (iVar1 == 1) {
    func_003378E0();
  }
  else {
    if (iVar1 != 0) {
      return 5;
    }
    func_003382B0();
  }
  return uVar2;
}

/* 0x003383B0, 0x5C bytes. */
void func_003383B0(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  if (**(int **)(iVar1 + 0x6a0) == 2) {
    func_0036A560();
  }
  else if (**(int **)(iVar1 + 0x6a0) == 1) {
    func_00373B60();
  }
  return;
}

/* 0x0036E740, 0x178 bytes. */
void func_0036E740(int param_1)
{
    int bVar1;
    int bVar2;
    int lVar3;
    int uVar4;
    int uVar5;
    int uVar6;
    int uVar7;
    u32 uVar8;
    u32 uVar9;

  
  lVar3 = func_0036E680();
  if (lVar3 != 0) {
    uVar4 = func_0033B730();
    uVar8 = 0;
    do {
      uVar5 = func_0033F070(param_1,uVar8);
      lVar3 = func_0033B1E0(uVar5);
      if (lVar3 == 0) {
        func_0033DDC0(uVar5,uVar4);
      }
      else {
        bVar2 = false;
        uVar9 = *(u32 *)(*(int *)uVar5 + 0x80);
        bVar1 = false;
        if (((uVar9 & 1) != 0) && ((uVar9 & 0x8c40002) == 0)) {
          bVar1 = true;
        }
        if ((bVar1) && ((uVar9 & 4) == 0)) {
          bVar2 = true;
        }
        if (!bVar2) {
          func_0033DCA0(uVar5,uVar4);
        }
      }
      uVar9 = 0;
      do {
        uVar6 = func_0034AB10(param_1,uVar8,uVar9);
        if ((*(u32 *)((int)uVar6 + 0x80) & 1) == 0) {
          uVar7 = func_00348C90(param_1);
          func_00349DF0(uVar5,uVar6,uVar7,uVar4);
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < 5);
      uVar8 = uVar8 + 1;
    } while (uVar8 < 2);
  }
  return;
}

/* 0x00370570, 0x230 bytes. */
int func_00370570(int *param_1, int param_2)
{
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar7;
    int lVar5;
    int * piVar1;
    int * piVar6;
    int * piVar8;

  
  piVar1 = (int *)func_002F7B10();
  iVar2 = func_002F7D90(0,0x2f85e0,0,0,0,0);
  if (iVar2 == 0) {
    iVar4 = 0;
  }
  else {
    iVar3 = param_2;
    if (param_2 < 0) {
      iVar3 = param_2 + 1;
    }
    iVar4 = func_0030CB00(3);
    if ((iVar3 >> 1) + iVar4 < param_2) {
      iVar4 = func_0030CB00(3);
      iVar3 = (iVar3 >> 1) + iVar4;
    }
    else {
      iVar3 = param_2;
    }
    func_002F7C40(piVar1,iVar2);
    iVar4 = 0;
    iVar7 = 0;
    if (0 < iVar2) {
      piVar6 = param_1;
      piVar8 = piVar1;
      do {
        if (iVar3 <= iVar4) break;
        if (*piVar8 < 0x1c) {
          *piVar6 = *piVar8;
          iVar4 = iVar4 + 1;
          piVar6 = piVar6 + 1;
        }
        iVar7 = iVar7 + 1;
        piVar8 = piVar8 + 1;
      } while (iVar7 < iVar2);
    }
    if ((0 < param_2 - iVar4) && (iVar3 = 0, 0 < iVar2)) {
      piVar8 = param_1 + iVar4;
      piVar6 = piVar1;
      do {
        if (param_2 <= iVar4) break;
        if (((399 < *piVar6 && *piVar6 < 0x19f) && (lVar5 = func_0030CB50(0x1e), lVar5 != 0)) &&
           (lVar5 = func_0039E650(*piVar6 + -400), lVar5 != 0)) {
          iVar4 = iVar4 + 1;
          *piVar8 = *piVar6;
          piVar8 = piVar8 + 1;
        }
        iVar3 = iVar3 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar3 < iVar2);
    }
    if ((0 < param_2 - iVar4) && (iVar3 = 0, 0 < iVar2)) {
      param_1 = param_1 + iVar4;
      do {
        if (param_2 <= iVar4) {
          return iVar4;
        }
        iVar7 = *piVar1;
        if ((0x1b < iVar7) && (iVar7 < 400 || 0x19e < iVar7)) {
          *param_1 = iVar7;
          iVar4 = iVar4 + 1;
          param_1 = param_1 + 1;
        }
        iVar3 = iVar3 + 1;
        piVar1 = piVar1 + 1;
      } while (iVar3 < iVar2);
    }
  }
  return iVar4;
}

/* 0x003710F0, 0x134 bytes. */
void func_003710F0(int param_1)
{
    int bVar1;
    int iVar2;
    int iVar5;
    int lVar3;
    int lVar4;

  
  iVar5 = (int)param_1 + -400;
  func_0039E7C0(iVar5);
  lVar3 = func_002F4080(param_1);
  bVar1 = false;
  if (-1 < lVar3) {
    lVar4 = func_0030AB90();
    bVar1 = lVar3 < lVar4;
  }
  if (!bVar1) {
    lVar3 = func_00327950();
    if (lVar3 == 0) {
      func_002F3B30(param_1,3);
      return;
    }
    func_002F3B30(param_1,2);
    func_002F3CF0(param_1,0);
    iVar5 = func_0039E760(iVar5);
    iVar2 = func_0030AB90();
    func_002F5BE0(param_1,iVar5 % iVar2);
  }
  func_002F32F0(param_1,1);
  func_002F3440(param_1,0);
  func_002F40F0(param_1,0);
  func_002F3660(param_1,2000);
  func_002F4250(param_1,0);
  func_002F43C0(param_1,0);
  func_002F4510(param_1,0);
  func_002F56A0(param_1,0);
  func_002F5930(param_1,0);
  return;
}

/* 0x00371310, 0x204 bytes, matching. */
void func_00371310(void)
{
    int iVar4;
    int lVar1;
    int lVar3;
    int uVar2;

  
  lVar1 = func_00327820();
  func_00371230(lVar1,0x50);
  uVar2 = func_002F2E20(lVar1);
  func_00371230(uVar2,0x50);
  iVar4 = 0;
  do {
    lVar3 = func_002F2E20(iVar4);
    if (lVar1 == lVar3) {
      func_00371230(iVar4,0x50);
    }
    lVar3 = func_002F77F0(iVar4,lVar1);
    if (lVar3 != 0) {
      func_00371230(iVar4,0x50);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x19f);
  func_003712C0(lVar1,2,10,0x50);
  func_003712C0(lVar1,0xd,0x17,0x50);
  lVar3 = func_00328270();
  if (lVar3 == 1) {
    func_003712C0(lVar1,5,0x12,0x50);
  }
  lVar3 = func_00328270();
  if (lVar3 == 3) {
    func_003712C0(lVar1,5,0x1b,0x50);
  }
  lVar3 = func_003282C0();
  if (lVar3 == 1) {
    func_003712C0(lVar1,0xf,0x80,0x50);
  }
  func_003712C0(lVar1,0x87,9,0x50);
  func_003712C0(lVar1,0x155,0x11d,0x50);
  func_003712C0(lVar1,0x62,0x114,0x50);
  func_003712C0(lVar1,0x107,0x128,0x50);
  func_003712C0(lVar1,2,0x13d,0x50);
  func_003712C0(lVar1,0x67,0x148,0x50);
  func_003712C0(lVar1,0x67,0x14b,0x50);
  func_003712C0(lVar1,0x15a,0x168,0x50);
  func_003712C0(lVar1,0x15d,0xb9,0x50);
  func_003712C0(lVar1,0x15d,0xb3,0x50);
  return;
}

/* 0x00371520, 0x278 bytes, matching. */
void func_00371520(void)
{
    int iVar4;
    int lVar2;
    int lVar3;
    int uVar1;

  
  uVar1 = func_00327820();
  iVar4 = 0;
  do {
    lVar2 = func_002F2DA0(iVar4);
    lVar3 = func_002F2DA0(uVar1);
    if (lVar2 == lVar3) {
      func_00371230(iVar4,0x32);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x19f);
  func_003712C0(uVar1,2,0x1b,0x32);
  func_003712C0(uVar1,2,0xd,0x32);
  func_003712C0(uVar1,2,3,0x32);
  func_003712C0(uVar1,2,0xc,0x32);
  func_003712C0(uVar1,2,1,0x32);
  func_003712C0(uVar1,0xd,0x11,0x32);
  func_003712C0(uVar1,0xd,0x91,0x32);
  func_003712C0(uVar1,0xd,0xa6,0x32);
  func_003712C0(uVar1,0x10,0xb,0x32);
  func_003712C0(uVar1,0x10,0xe,0x32);
  func_003712C0(uVar1,0x10,0xf,0x32);
  func_003712C0(uVar1,8,0,0x32);
  func_003712C0(uVar1,0x6e,0,0x32);
  func_003712C0(uVar1,4,0x16,0x32);
  func_003712C0(uVar1,0xfb,0x16,0x32);
  func_003712C0(uVar1,0xfb,1,0x32);
  func_003712C0(uVar1,0x15a,0x18,0x32);
  func_003712C0(uVar1,0x168,0x18,0x32);
  func_003712C0(uVar1,0x11,0x13,0x32);
  func_003712C0(uVar1,9,0x118,0x32);
  func_003712C0(uVar1,0x13b,0x68,0x32);
  func_003712C0(uVar1,0x13b,0x15,0x32);
  func_003712C0(uVar1,0x15e,0xa1,0x32);
  func_003712C0(uVar1,0x157,0x13,0x32);
  func_003712C0(uVar1,0x166,0x18b,0x32);
  func_003712C0(uVar1,0x15b,0xff,0x32);
  return;
}

/* 0x00371F00, 0x2F8 bytes. */
int func_00371F00(void)
{
    int iVar1;
    int iVar12;
    int iVar13;
    int iVar16;
    int iVar17;
    int iVar18;
    int iVar19;
    int iVar3;
    int iVar4;
    int iVar5;
    int lVar10;
    int lVar8;
    int lVar9;
    int * piVar14;
    int * piVar15;
    int * piVar2;
    int uVar11;
    u32 uVar6;
    int uVar7;

  
  uVar7 = func_00327D50();
  iVar1 = func_00327E50();
  piVar2 = (int *)func_002F7B10();
  iVar3 = func_002F7D90(0,0x2f8160,uVar7,0,1,0);
  if (iVar1 < iVar3) {
    lVar8 = func_002FB2D0(uVar7);
    iVar17 = 0;
    if (0 < iVar3) {
      piVar15 = piVar2;
      do {
        iVar19 = *piVar15;
        lVar9 = func_002F3DC0(iVar19);
        if (lVar9 == 3) {
          iVar18 = 100000;
        }
        else {
          iVar18 = 0;
        }
        if (iVar19 < 0x1c) {
          iVar12 = 10000;
        }
        else {
          iVar12 = 0;
        }
        iVar4 = func_002F41E0(iVar19);
        lVar10 = func_002F5CC0(iVar19);
        iVar16 = iVar17 + 1;
        iVar18 = iVar18 + iVar12 + (int)lVar9 * 1000 + iVar4 * 10 + (u32)(lVar8 == lVar10);
        if (iVar16 < iVar3) {
          piVar14 = piVar2 + iVar16;
          do {
            iVar12 = *piVar14;
            lVar9 = func_002F3DC0(iVar12);
            if (lVar9 == 3) {
              iVar4 = 100000;
            }
            else {
              iVar4 = 0;
            }
            if (iVar12 < 0x1c) {
              iVar13 = 10000;
            }
            else {
              iVar13 = 0;
            }
            iVar5 = func_002F41E0(iVar12);
            lVar10 = func_002F5CC0(iVar12);
            iVar4 = iVar4 + iVar13 + (int)lVar9 * 1000 + iVar5 * 10 + (u32)(lVar8 == lVar10);
            if ((iVar18 < iVar4) || ((iVar18 == iVar4 && (lVar9 = func_0030CB50(0x32), lVar9 != 0))))
            {
              *piVar15 = iVar12;
              *piVar14 = iVar19;
              iVar18 = iVar4;
              iVar19 = iVar12;
            }
            iVar16 = iVar16 + 1;
            piVar14 = piVar14 + 1;
          } while (iVar16 < iVar3);
        }
        iVar17 = iVar17 + 1;
        piVar15 = piVar15 + 1;
      } while (iVar17 < iVar3);
    }
    if (iVar1 < iVar3) {
      piVar2 = piVar2 + iVar1;
      iVar17 = iVar1;
      do {
        func_002F7410(*piVar2);
        iVar17 = iVar17 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar17 < iVar3);
    }
    uVar7 = func_00390760(0x94);
    uVar11 = func_0030CB80(iVar3 - iVar1);
    func_001204B0(g_007B4E60,uVar7,uVar11);
    func_00374EE0(g_007B4E60);
    uVar6 = 5;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}

/* 0x003737E0, 0x18C bytes. */
void func_003737E0(int param_1, int param_2, int param_3, int param_4)
{
    int iVar2;
    int iVar3;
    int lVar1;

  
  (*(u8 *)(g_007B9890 + 0xF2)) = param_1 == 6;
  (*(u32 *)(g_007B9890 + 0x0)) = 0;
  (*(u32 *)(g_007B9890 + 0x4)) = 0x2d;
  (*(u32 *)(g_007B9890 + 0x8)) = 0;
  (*(u32 *)(g_007B9890 + 0xC)) = 0x98;
  (*(u32 *)(g_007B9890 + 0x10)) = 1;
  (*(u32 *)(g_007B9890 + 0x14)) = param_1;
  (*(u32 *)(g_007B9890 + 0x18)) = param_3;
  (*(u32 *)(g_007B9890 + 0x1C)) = param_2;
  (*(u16 *)(g_007B9890 + 0xF0)) = param_4;
  lVar1 = func_003737A0();
  (*(u32 *)(g_007B9890 + 0x20)) = (u32)(lVar1 != 0);
  iVar3 = 0;
  (*(u32 *)(g_007B9890 + 0x24)) = 0;
  iVar2 = (int)g_007B9890;
  do {
    *(u32 *)(iVar2 + 0x28) = 0;
    iVar3 = iVar3 + 5;
    *(u32 *)(iVar2 + 0x8c) = 0x1e;
    *(u32 *)(iVar2 + 0x2c) = 0;
    *(u32 *)(iVar2 + 0x90) = 0x1e;
    *(u32 *)(iVar2 + 0x30) = 0;
    *(u32 *)(iVar2 + 0x94) = 0x1e;
    *(u32 *)(iVar2 + 0x34) = 0;
    *(u32 *)(iVar2 + 0x98) = 0x1e;
    *(u32 *)(iVar2 + 0x38) = 0;
    *(u32 *)(iVar2 + 0x9c) = 0x1e;
    iVar2 = iVar2 + 0x14;
  } while (iVar3 < 0x19);
  func_00373050();
  iVar2 = 0;
  iVar3 = (int)g_007B9890;
  do {
    if (*(int *)(iVar3 + 0x28) == 0) {
      *(u32 *)(iVar3 + 0x8c) = 0x19;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
  } while (iVar2 < 0x19);
  func_003A7C10();
  func_00373540();
  func_003A80A0(1);
  if (param_1 != 6) {
    func_003A9010(2);
    lVar1 = func_00373640();
    if (lVar1 != 0) {
      func_003A9010(3);
    }
  }
  func_003A90D0(0);
  return;
}

/* 0x00373DF0, 0x168 bytes. */
int func_00373DF0(int param_1, int param_2)
{
    int bVar1;
    int iVar2;
    int iVar3;

  
  switch((*(u32 *)(g_007B98A8 + 0x0))) {
  case 0:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x458f80);
    break;
  case 1:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x458fe0);
    break;
  case 2:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x459040);
    break;
  case 3:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x4590c0);
    break;
  case 4:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x459120);
    break;
  case 5:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x4591a0);
    break;
  default:
    iVar3 = *(int *)(param_2 * 4 + param_1 * 0x10 + 0x459200);
  }
  bVar1 = false;
  if ((-1 < iVar3) && (iVar2 = func_0030AB90(), iVar3 < iVar2)) {
    bVar1 = true;
  }
  if (!bVar1) {
    iVar3 = param_1;
  }
  return iVar3;
}

/* 0x00373FB0, 0x84 bytes. */
int func_00373FB0(int param_1)
{
    int bVar1;
    int lVar2;
    int lVar3;
    int lVar4;
    u32 uVar5;

  
  lVar2 = func_00327D50();
  uVar5 = 1;
  lVar3 = func_00323BD0(param_1);
  bVar1 = false;
  if (-1 < lVar3) {
    lVar4 = func_0030AB90();
    bVar1 = lVar3 < lVar4;
  }
  if ((bVar1) && (lVar3 = func_0030AFF0(lVar3), lVar2 == lVar3)) {
    uVar5 = 0;
  }
  return uVar5;
}

/* 0x003740F0, 0x154 bytes. */
int func_003740F0(int param_1)
{
    int bVar1;
    int bVar2;
    int lVar3;
    int lVar4;
    int uVar5;
    int uVar6;

  
  bVar2 = true;
  lVar3 = func_0030AFF0();
  bVar1 = false;
  if (-1 < lVar3) {
    lVar4 = func_0030AB90();
    bVar1 = lVar3 < lVar4;
  }
  if (bVar1) {
    uVar5 = func_00327D50();
    uVar6 = func_0030AFF0(param_1);
    lVar3 = func_002FAFA0(uVar5,uVar6);
    if (lVar3 == 0) {
      lVar3 = func_00373FB0(param_1);
      if (lVar3 == 0) {
        func_0030E390(0xd,0x9c,0xffffffffffffffff,0xffffffffffffffff,0,0);
        bVar2 = false;
      }
      else {
        lVar3 = func_0030B240(param_1,3);
        if (lVar3 == 2) {
          func_0030E390(0xd,0x9e,0xffffffffffffffff,0xffffffffffffffff,0,0);
          bVar2 = false;
        }
      }
    }
    else {
      func_0030E390(0xd,0x9b,0xffffffffffffffff,0xffffffffffffffff,0,0);
      bVar2 = false;
    }
  }
  if ((bVar2) && (lVar3 = func_00374040(param_1), lVar3 == 0)) {
    func_0030E390(0xd,0x9f,0xffffffffffffffff,0xffffffffffffffff,0,0);
    bVar2 = false;
  }
  return bVar2;
}

/* 0x00374E20, 0xB8 bytes. */
void func_00374E20(void)
{
  (*(u32 *)(g_007B99F0 + 0x0)) = 0;
  (*(u32 *)(g_007B99F0 + 0xC)) = 5;
  (*(u32 *)(g_007B99F0 + 0x4)) = 0;
  (*(u32 *)(g_007B99F0 + 0x8)) = 0;
  (*(u32 *)(g_007B99F0 + 0x10)) = 5;
  (*(u32 *)(g_007B99F0 + 0x14)) = 1;
  (*(u32 *)(g_007B99F0 + 0x18)) = 0;
  (*(u32 *)(g_007B99F0 + 0x1C)) = 0;
  (*(u32 *)(g_007B99F0 + 0x20)) = 0;
  (*(u32 *)(g_007B99F0 + 0x24)) = 0;
  (*(u32 *)(g_007B99F0 + 0x28)) = 0;
  (*(u32 *)(g_007B99F0 + 0x2C)) = 0;
  (*(u32 *)(g_007B99F0 + 0x30)) = 0;
  (*(u32 *)(g_007B99F0 + 0x34)) = 0;
  (*(u32 *)(g_007B99F0 + 0x38)) = 0;
  (*(u16 *)(g_007B99F0 + 0x3C)) = 0;
  (*(u16 *)(g_007B99F0 + 0x3E)) = 0;
  func_0011ED38(g_007B9A30,0,0x404);
  return;
}

/* 0x003755E0, 0x178 bytes. */
void func_003755E0(void)
{
    int iVar1;

  
  if ((((*(u32 *)(g_007B99F4 + 0x1C)) + -0x20) * (int)(*(short *)(g_007B99F4 + 0x38))) / 5 + 0x20 < (*(u32 *)(g_007B99F4 + 0x1C))) {
    (*(u32 *)(g_007B99F4 + 0x30)) = (((*(u32 *)(g_007B99F4 + 0x1C)) + -0x20) * (int)(*(short *)(g_007B99F4 + 0x38))) / 5 + 0x20;
  }
  else {
    (*(u32 *)(g_007B99F4 + 0x30)) = (*(u32 *)(g_007B99F4 + 0x1C));
  }
  (*(u32 *)(g_007B99F4 + 0x34)) = (((*(u32 *)(g_007B99F4 + 0x20)) + -0x20) * (int)(*(short *)(g_007B99F4 + 0x38))) / 5 + 0x20;
  if ((*(u32 *)(g_007B99F4 + 0x20)) <= (*(u32 *)(g_007B99F4 + 0x34))) {
    (*(u32 *)(g_007B99F4 + 0x34)) = (*(u32 *)(g_007B99F4 + 0x20));
  }
  iVar1 = (*(u32 *)(g_007B99F4 + 0x1C)) - (*(u32 *)(g_007B99F4 + 0x30));
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  (*(u32 *)(g_007B99F4 + 0x24)) = (*(u32 *)(g_007B99F4 + 0x14)) + (iVar1 >> 1);
  iVar1 = (*(u32 *)(g_007B99F4 + 0x20)) - (*(u32 *)(g_007B99F4 + 0x34));
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  (*(short *)(g_007B99F4 + 0x38)) = (*(short *)(g_007B99F4 + 0x38)) + 1;
  (*(u32 *)(g_007B99F4 + 0x28)) = (*(u32 *)(g_007B99F4 + 0x18)) + (iVar1 >> 1);
  if (5 < (*(short *)(g_007B99F4 + 0x38))) {
    (*(u32 *)(g_007B99F4 + 0x28)) = (*(u32 *)(g_007B99F4 + 0x18));
    (*(u32 *)(g_007B99F4 + 0x0)) = 2;
    (*(u32 *)(g_007B99F4 + 0x8)) = 5;
    (*(u32 *)(g_007B99F4 + 0xC)) = 5;
    (*(short *)(g_007B99F4 + 0x38)) = 0;
    (*(u32 *)(g_007B99F4 + 0x24)) = (*(u32 *)(g_007B99F4 + 0x14));
    (*(u32 *)(g_007B99F4 + 0x30)) = (*(u32 *)(g_007B99F4 + 0x1C));
    (*(u32 *)(g_007B99F4 + 0x34)) = (*(u32 *)(g_007B99F4 + 0x20));
  }
  return;
}

/* 0x00375760, 0x188 bytes. */
void func_00375760(void)
{
    int iVar1;

  
  if ((((*(u32 *)(g_007B99F4 + 0x1C)) + -0x20) * (5 - (*(short *)(g_007B99F4 + 0x38)))) / 5 + 0x20 < (*(u32 *)(g_007B99F4 + 0x1C))) {
    (*(u32 *)(g_007B99F4 + 0x30)) = (((*(u32 *)(g_007B99F4 + 0x1C)) + -0x20) * (5 - (*(short *)(g_007B99F4 + 0x38)))) / 5 + 0x20;
  }
  else {
    (*(u32 *)(g_007B99F4 + 0x30)) = (*(u32 *)(g_007B99F4 + 0x1C));
  }
  (*(u32 *)(g_007B99F4 + 0x34)) = (((*(u32 *)(g_007B99F4 + 0x20)) + -0x20) * (5 - (*(short *)(g_007B99F4 + 0x38)))) / 5 + 0x20;
  if ((*(u32 *)(g_007B99F4 + 0x20)) <= (*(u32 *)(g_007B99F4 + 0x34))) {
    (*(u32 *)(g_007B99F4 + 0x34)) = (*(u32 *)(g_007B99F4 + 0x20));
  }
  iVar1 = (*(u32 *)(g_007B99F4 + 0x1C)) - (*(u32 *)(g_007B99F4 + 0x30));
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  (*(u32 *)(g_007B99F4 + 0x24)) = (*(u32 *)(g_007B99F4 + 0x14)) + (iVar1 >> 1);
  iVar1 = (*(u32 *)(g_007B99F4 + 0x20)) - (*(u32 *)(g_007B99F4 + 0x34));
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  (*(short *)(g_007B99F4 + 0x38)) = (*(short *)(g_007B99F4 + 0x38)) + 1;
  (*(u32 *)(g_007B99F4 + 0x28)) = (*(u32 *)(g_007B99F4 + 0x18)) + (iVar1 >> 1);
  if (5 < (*(short *)(g_007B99F4 + 0x38))) {
    (*(short *)(g_007B99F4 + 0x38)) = 0;
    (*(u32 *)(g_007B99F4 + 0x24)) = 0;
    (*(u32 *)(g_007B99F4 + 0x28)) = 0;
    (*(u32 *)(g_007B99F4 + 0x30)) = 0;
    (*(u32 *)(g_007B99F4 + 0x34)) = 0;
    (*(u32 *)(g_007B99F4 + 0x0)) = 0;
    (*(u32 *)(g_007B99F4 + 0x8)) = (*(u32 *)(g_007B99F4 + 0xC));
    (*(u32 *)(g_007B99F4 + 0xC)) = 5;
  }
  return;
}

/* 0x003758F0, 0x20C bytes. */
void func_003758F0(void)
{
    int uVar1;
    int uVar2;

  
  (*(u16 *)(g_007B99F4 + 0x38)) = 0;
  (*(u32 *)(g_007B99F4 + 0x24)) = (*(u32 *)(g_007B99F4 + 0x14));
  (*(u32 *)(g_007B99F4 + 0x28)) = (*(u32 *)(g_007B99F4 + 0x18));
  (*(u32 *)(g_007B99F4 + 0x34)) = (*(u32 *)(g_007B99F4 + 0x20));
  (*(u32 *)(g_007B99F4 + 0x30)) = (*(u32 *)(g_007B99F4 + 0x1C));
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
  if ((uVar1 & 0x40) != 0) {
    if ((*(u32 *)(g_007B99F4 + 0x4)) == 0) {
      (*(u32 *)(g_007B99F4 + 0xC)) = 1;
      (*(u32 *)(g_007B99F4 + 0x8)) = 4;
    }
    else if ((*(u32 *)(g_007B99F4 + 0x4)) == 1) {
      if ((*(u32 *)(g_007B99F4 + 0x10)) == 0) {
        (*(u32 *)(g_007B99F4 + 0xC)) = 2;
      }
      else {
        (*(u32 *)(g_007B99F4 + 0xC)) = 3;
      }
      (*(u32 *)(g_007B99F4 + 0x8)) = 4;
    }
    func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
    (*(u32 *)(g_007B99F4 + 0x0)) = 3;
  }
  if ((*(u32 *)(g_007B99F4 + 0x4)) == 1) {
    if ((uVar2 & 0x8000) == 0) {
      if ((uVar2 & 0x2000) != 0) {
        (*(u32 *)(g_007B99F4 + 0x10)) = (u32)((*(u32 *)(g_007B99F4 + 0x10)) == 0);
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      }
    }
    else {
      (*(u32 *)(g_007B99F4 + 0x10)) = (u32)((*(u32 *)(g_007B99F4 + 0x10)) == 0);
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
    }
  }
  return;
}

/* 0x00375B00, 0x8C bytes. */
int func_00375B00(void)
{
    u32 uVar1;

  
  if ((*(u32 *)(g_007B99F0 + 0x0)) == 1) {
    if ((*(u32 *)(g_007B99F0 + 0x4)) == 2) {
      func_003758F0();
    }
    else if ((*(u32 *)(g_007B99F0 + 0x4)) == 3) {
      func_00375760();
    }
    else {
      if ((*(u32 *)(g_007B99F0 + 0x4)) != 1) {
        return 1;
      }
      func_003755E0();
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x00375C20, 0xD0 bytes. */
void func_00375C20(int param_1, int param_2, int param_3, int param_4, int param_5)
{
  g_0045D7C0 = (int)param_1;
  if (param_1 == 0) {
    param_1 = 0x7b9990;
    g_0045D7C0 = 0x7b9990;
  }
  *(u32 *)param_1 = param_2;
  *(u32 *)(g_0045D7C0 + 4) = 0;
  *(u32 *)(g_0045D7C0 + 8) = param_3;
  *(u32 *)(g_0045D7C0 + 0xc) = param_4;
  *(u32 *)(g_0045D7C0 + 0x10) = param_5;
  *(u32 *)(g_0045D7C0 + 0x14) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x18) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x1c) = 0xfffffea0;
  *(u32 *)(g_0045D7C0 + 0x20) = 0;
  *(u32 *)(g_0045D7C0 + 0x24) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x28) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x2c) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x30) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x34) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x38) = 0xffffffff;
  *(u32 *)(g_0045D7C0 + 0x3c) = 0xfffffea0;
  *(u32 *)(g_0045D7C0 + 0x40) = 0;
  *(u32 *)(g_0045D7C0 + 0x44) = 1;
  *(u32 *)(g_0045D7C0 + 0x4c) = 0xfffffea0;
  *(u32 *)(g_0045D7C0 + 0x50) = 0;
  *(u32 *)(g_0045D7C0 + 0x54) = 1;
  return;
}

/* 0x00375D90, 0x6C bytes. */
int func_00375D90(void)
{
    int iVar1;
    int iVar2;

  
  if ((-1 < *(int *)(g_0045D7C0 + 0x24)) && (iVar2 = 0, 0 < *(int *)(g_0045D7C0 + 0x10))) {
    iVar1 = *(int *)(g_0045D7C0 + 0xc);
    do {
      if (*(int *)(g_0045D7C0 + 0x24) == *(int *)(iVar1 + 4)) {
        return *(u32 *)(*(int *)(g_0045D7C0 + 0xc) + iVar2 * 8);
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 8;
    } while (iVar2 < *(int *)(g_0045D7C0 + 0x10));
  }
  return 0;
}

/* 0x00376100, 0x1B4 bytes, matching. */
void func_00376100(int param_1, int param_2, int param_3)
{
  if (g_0045D7C0 == 0) {
    func_00375CF0();
  }
  if (*(int *)(g_0045D7C0 + 0x54) == 1) {
    *(u32 *)(g_0045D7C0 + 0x54) = 2;
    *(int *)(g_0045D7C0 + 0x38) = param_3;
  }
  else if (*(int *)(g_0045D7C0 + 0x54) == 0) {
    if (*(int *)(g_0045D7C0 + 0x2c) != param_3) {
      *(u32 *)(g_0045D7C0 + 0x54) = 4;
      *(int *)(g_0045D7C0 + 0x38) = param_3;
    }
  }
  else {
    *(u32 *)(g_0045D7C0 + 0x4c) = 0xfffffea0;
    *(u32 *)(g_0045D7C0 + 0x54) = 2;
    *(u32 *)(g_0045D7C0 + 0x2c) = 0xffffffff;
    *(int *)(g_0045D7C0 + 0x38) = param_3;
  }
  if (*(int *)(g_0045D7C0 + 0x44) == 1) {
    *(u32 *)(g_0045D7C0 + 0x44) = 2;
    *(u32 *)(g_0045D7C0 + 0x54) = 2;
  }
  else if (*(int *)(g_0045D7C0 + 0x44) == 0) {
    if (((*(int *)(g_0045D7C0 + 0x24) == param_1) && (*(int *)(g_0045D7C0 + 0x28) == param_2)) &&
       (*(int *)(g_0045D7C0 + 0x2c) == param_3)) {
      return;
    }
    if (((*(int *)(g_0045D7C0 + 0x24) == param_1) && (*(int *)(g_0045D7C0 + 0x28) == param_2)) &&
       (*(int *)(g_0045D7C0 + 0x2c) != param_3)) {
      *(u32 *)(g_0045D7C0 + 0x54) = 4;
    }
    else {
      *(u32 *)(g_0045D7C0 + 0x44) = 4;
      *(u32 *)(g_0045D7C0 + 0x54) = 4;
    }
  }
  else {
    *(u32 *)(g_0045D7C0 + 0x3c) = 0xfffffea0;
    *(u32 *)(g_0045D7C0 + 0x44) = 2;
    *(u32 *)(g_0045D7C0 + 0x4c) = 0xfffffea0;
    *(u32 *)(g_0045D7C0 + 0x54) = 2;
    *(u32 *)(g_0045D7C0 + 0x24) = 0xffffffff;
    *(u32 *)(g_0045D7C0 + 0x14) = 0xffffffff;
    *(u32 *)(g_0045D7C0 + 0x28) = 0xffffffff;
    *(u32 *)(g_0045D7C0 + 0x2c) = 0xffffffff;
  }
  *(int *)(g_0045D7C0 + 0x30) = param_1;
  *(int *)(g_0045D7C0 + 0x34) = param_2;
  *(int *)(g_0045D7C0 + 0x38) = param_3;
  return;
}

/* 0x003762F0, 0x78 bytes, matching. */
void func_003762F0(void)
{
  if (*(int *)(g_0045D7C0 + 0x24) != *(int *)(g_0045D7C0 + 0x30)) {
    *(int *)(g_0045D7C0 + 0x24) = *(int *)(g_0045D7C0 + 0x30);
  }
  if (*(int *)(g_0045D7C0 + 0x14) != *(int *)(g_0045D7C0 + 0x18)) {
    *(int *)(g_0045D7C0 + 0x14) = *(int *)(g_0045D7C0 + 0x18);
  }
  if (*(int *)(g_0045D7C0 + 0x28) != *(int *)(g_0045D7C0 + 0x34)) {
    *(int *)(g_0045D7C0 + 0x28) = *(int *)(g_0045D7C0 + 0x34);
  }
  if (*(int *)(g_0045D7C0 + 0x2c) != *(int *)(g_0045D7C0 + 0x38)) {
    *(int *)(g_0045D7C0 + 0x2c) = *(int *)(g_0045D7C0 + 0x38);
  }
  return;
}

/* 0x0037E9F0, 0xA4 bytes, matching. */
void func_0037E9F0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int lVar2;
    int uVar1;

  
  lVar2 = param_2;
  if (param_2 == 99) {
    lVar2 = 0x7e;
  }
  if (param_2 == 0x65) {
    lVar2 = 0x7f;
  }
  uVar1 = func_00372580(lVar2);
  func_0037E920(param_1,param_2,param_3,param_4,param_5,uVar1,param_6);
  return;
}
