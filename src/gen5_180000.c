/*
 * gen5_180000.c - small functions between 0x00180000 and 0x003F9680, generated from Ghidra
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

#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

int func_0011ED38();
int func_001204B0();
int func_001EC530();
int func_001F5A60();
int func_001FF100();
int func_001FF140();
int func_002039F0();
int func_00206590();
int func_00206950();
int func_0024B790();
int func_002BC110();
int func_002F7D90();
int func_0030D7D0();
int func_00322C70();
int func_00322E80();
int func_00323040();
int func_0038A010();
int func_0038A330();
int func_0038A3D0();
void func_00325710(void);
void func_00326850(void);

/* 0x001FDC50, 0x138 bytes. */
int func_001FDC50(u8 *param_1)
{
    int bVar1;
    int cVar3;
    int iVar2;
    int lVar4;

    iVar2 = g_70000888;
    cVar3 = func_001FF100(*(u16 *)(param_1 + 0x54), 4);
    bVar1 = false;
    if ((*(u32 *)g_0045D898 == 7) &&
          ((lVar4 = func_0020E140(), lVar4 != 0 || (lVar4 = func_0020E170(), lVar4 != 0)))) {
        bVar1 = true;
    }
    if ((iVar2 == 1) || (bVar1)) {
        if (cVar3 == 1) {
            return false;
        }
        if (cVar3 == 2) {
            return true;
        }
    }
    else {
        if (iVar2 == 4) {
            if ((cVar3 == 3) && ((*(u8 *)(param_1 + 0x69) & 1) == 0)) {
                return (int)2;
            }
            return false;
        }
        if (cVar3 == 2) {
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

    lVar2 = func_00206B80(param_1);
    iVar3 = param_1;
    if (lVar2 == 0) {
        lVar2 = func_00206590(param_1);
        if ((lVar2 == 0) && (lVar2 = func_00206950(param_1), lVar2 == 0)) {
            if ((*(u32 *)(iVar3 + 0xB8) & 0x180) != 0) {
                *(u8 *)(*(int *)(iVar3 + 0x10) + 0x7A) = 1;
            }
            *(u32 *)(iVar3 + 0xBC) = *(u32 *)(iVar3 + 0xBC) & 0xFFF8003F;
            *(u8 *)(iVar3 + 0x7D) = 0;
            return 0;
        }
    }
    else if ((*(u32 *)(*(int *)(iVar3 + 8) + 0xB8) & 0xC) == 0) {
        func_00206950(param_1);
        iVar1 = *(int *)(iVar3 + 8);
        goto LAB_00203c40;
    }
    iVar1 = *(int *)(iVar3 + 8);
LAB_00203c40:
    if (iVar1 != 0) {
        func_002039F0(param_1, *(int *)(iVar3 + 0xC) != 0);
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
    if (*(int *)(iVar3 + 0x11C) != 0) {
        if (0 < *(int *)((u32)*(u8 *)(iVar3 + 0x14E) * 0x70 + 0x74B868)) {
            lVar2 = func_0016C040(param_1);
            if (lVar2 == 0) {
                uVar4 = 0;
            }
            else {
                uVar4 = 0x200;
            }
            if (*(char *)(iVar1 + 0x1C) == 2) {
                lVar5 = func_001C8780(0x1D, PS2_ADDR(param_1), 0x14, uVar4 | 0x10001);
            }
            if (lVar5 != 0) {
                func_001C8E80((u8 *)PS2_PTR(lVar5));
            }
        }
    }
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
    *(u32 *)(g_00732508) = 0;
    do {
        *(u32 *)(iVar5 + 4) = 0;
        iVar6 = 0;
        iVar1 = (u8 *)PS2_PTR(*(int *)(iVar4 + 0x2E0));
        iVar3 = iVar1;
        do {
            func_0024B790(iVar3);
            iVar6 = iVar6 + 1;
            iVar3 = iVar3 + 0x5D0;
        } while (iVar6 < 0x3D);
        func_001050B0(iVar1 + 0x18AD0);
        iVar2 = iVar2 + 1;
        *(unsigned long long *)(iVar1 + 0x18AE0) = 0xDF000001FF0000;
        iVar5 = iVar5 + 4;
        *(unsigned long long *)(iVar1 + 0x18AE8) = 0x41;
        iVar4 = iVar4 + 4;
    } while (iVar2 < 2);
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

    *(unsigned long long *)(g_007A1B40) = 0x1000000000008002;
    *(unsigned long long *)(g_007A1B40 + 0x8) = 0xE;
    *(unsigned long long *)(g_007A1B40 + 0x18) = 6;
    *(unsigned long long *)(g_007A1B40 + 0x10) = *(unsigned long long *)(g_0040C558);
    uVar8 = 0;
    iVar6 = g_007A0640;
    *(unsigned long long *)(g_007A1B40 + 0x20) = 0x8000000048;
    *(unsigned long long *)(g_007A1B40 + 0x28) = 0x42;
    do {
        uVar7 = 0;
        iVar5 = iVar6;
        do {
            func_00118850(iVar5, 0x380);
            uVar3 = 0;
            iVar1 = iVar5;
            do {
                puVar4 = (u32 *)(iVar1 + 0x20);
                if (uVar3 == 1) {
                    *puVar4 = 0x40000000;
                }
                uVar2 = 0;
                do {
                    *(unsigned long long *)(puVar4 + 4) = 0x302E400000008004;
                    *(unsigned long long *)(puVar4 + 6) = 0x412;
                    uVar2 = uVar2 + 1;
                    puVar4[0x11] = 0xC1A00000;
                    puVar4[0x1D] = 0x41A00000;
                    puVar4[0x29] = 0xC1A00000;
                    puVar4[0x35] = 0x41A00000;
                    puVar4[0xC] = 0x80;
                    puVar4[0xD] = 0x40;
                    puVar4[0xE] = 0x40;
                    puVar4[0xF] = 0x80;
                    puVar4[0x18] = 0x80;
                    puVar4[0x19] = 0x40;
                    puVar4[0x1A] = 0x40;
                    puVar4[0x1B] = 0x80;
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
                iVar1 = iVar1 + 0x1B0;
            } while (uVar3 < 2);
            uVar7 = uVar7 + 1;
            iVar5 = iVar5 + 0x380;
        } while (uVar7 < 3);
        uVar8 = uVar8 + 1;
        iVar6 = iVar6 + 0xA80;
    } while (uVar8 < 2);
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
        lVar4 = func_003225E0((int *)(iVar2 + 0x10), (int *)(iVar2 + 0x14), (int *)(iVar2 + 0x18));
        if (lVar4 == 0) {
            *(u32 *)(iVar2 + 8) = 0;
            *(u32 *)(iVar2 + 0xC) = 0;
            return 0;
        }
        func_00322780((int *)PS2_PTR(g_0045D6A4));
        lVar4 = func_00327CC0();
        if (lVar4 == 3) {
            func_00322850((int *)PS2_PTR(g_0045D6A8));
        }
        *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
    }
    else {
        if (iVar1 == 1) {
            uVar7 = *(u32 *)(iVar2 + 0xC);
            lVar4 = func_002F8CB0(uVar7);
            if (lVar4 == 0) {
                func_003223A0((int *)(uVar3));
                return 5;
            }
            lVar4 = func_002FB2A0(uVar7);
            if (lVar4 == 0) {
                uVar5 = func_002F7D90(0, 0x2F8160, uVar7, 0, 0, 0);
                uVar6 = PS2_ADDR(func_002F7B10());
                func_003228F0(uVar7, *(u32 *)(iVar2 + 0x10), *(u32 *)(iVar2 + 0x14),
                                          *(u32 *)(iVar2 + 0x18), uVar5, (u32 *)PS2_PTR(uVar6));
                uVar6 = PS2_ADDR(func_002F7B10());
                func_00322B00(uVar5, (int *)PS2_PTR(uVar6));
                func_00322C70(uVar7, 0x19F, g_0045D6A4);
                func_00323040(uVar7);
                func_003223A0((int *)(uVar3));
                return 5;
            }
            func_003223A0((int *)(uVar3));
            return 5;
        }
        if (iVar1 == 2) {
            uVar7 = *(u32 *)(iVar2 + 0xC);
            lVar4 = func_002F8CB0(uVar7);
            if (lVar4 == 0) {
                func_003223A0((int *)(uVar3));
                return 5;
            }
            lVar4 = func_002FB2A0(uVar7);
            if (lVar4 == 0) {
                func_00322E80(uVar7, 0x19F, g_0045D6A8);
                func_003223A0((int *)(uVar3));
                return 5;
            }
            func_003223A0((int *)(uVar3));
            return 5;
        }
        if (iVar1 == 3) {
            *(u32 *)(iVar2 + 8) = 0;
            uVar7 = 0;
            *(u32 *)(iVar2 + 0xC) = 0;
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
    func_0011ED38(param_1, 0, 100);
    iVar4 = 0;
    do {
        lVar2 = func_00329160(iVar4, (int *)(&uStack_4), &iStack_8);
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
    } while (iVar4 < 0xC);
}

/* 0x0039CA60, 0x3E8 bytes. */
void func_0039CA60(void)
{
    u8 * iVar2;
    int lVar3;
    int sVar1;
    int uVar4;
    int uVar5;

    iVar2 = (u8 *)(func_002FC2C0());
    iVar2 = (u8 *)PS2_PTR(*(int *)(iVar2 + 0x6AC));
    lVar3 = func_003DC2D0(0xC);
    if (lVar3 == 0) {
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar4 = 0;
        }
        else {
            uVar4 = *(u16 *)g_0050074C;
        }
        if ((*(u8 *)(g_0050074C + 0x18) & 1) == 0 || (*(u8 *)(g_0050074C + 0x19) & 1) != 1) {
            uVar5 = 0;
        }
        else {
            uVar5 = *(u16 *)(g_0050074C + 0x2);
        }
        if (*(int *)(iVar2 + 4) == 1) {
            lVar3 = func_0039C9E0();
            if ((uVar4 & 0x10) == 0) {
                if ((uVar5 & 0x1000) == 0) {
                    if (((uVar5 & 0x4000) != 0) && (lVar3 != 1)) {
                        if (*(int *)(iVar2 + 8) == (int)lVar3 + -1) {
                            if ((uVar4 & 0x4000) != 0) {
                                *(u32 *)(iVar2 + 8) = 0;
                                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                            }
                        }
                        else {
                            *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + 1;
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        }
                    }
                }
                else if (lVar3 != 1) {
                    if (*(int *)(iVar2 + 8) == 0) {
                        if ((uVar4 & 0x1000) != 0) {
                            *(int *)(iVar2 + 8) = (int)lVar3 + -1;
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        }
                    }
                    else {
                        *(int *)(iVar2 + 8) = *(int *)(iVar2 + 8) + -1;
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    }
                }
            }
            else {
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                *(u32 *)(iVar2 + 8) = 0xFFFFFFFF;
                *(u32 *)(iVar2 + 4) = 0;
            }
        }
        else if (*(int *)(iVar2 + 4) == 0) {
            if ((uVar4 & 0x40) == 0) {
                if ((uVar4 & 0x10) == 0) {
                    if ((uVar5 & 0x1000) == 0) {
                        if ((uVar5 & 0x4000) != 0) {
                            if ((int)*(short *)(iVar2 + 0x1C) == 0x1D) {
                                if ((uVar4 & 0x4000) != 0) {
                                    *(u16 *)(iVar2 + 0x1E) = 0;
                                    *(u16 *)(iVar2 + 0x1C) = 0;
                                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                                }
                            }
                            else {
                                if (((int)*(short *)(iVar2 + 0x1C) == (int)(*(short *)(iVar2 + 0x1E) + 9)) &&
                                      (sVar1 = *(short *)(iVar2 + 0x1E) + 1, *(short *)(iVar2 + 0x1E) = sVar1,
                                      0x14 < sVar1)) {
                                    *(u16 *)(iVar2 + 0x1E) = 0x14;
                                }
                                *(short *)(iVar2 + 0x1C) = *(short *)(iVar2 + 0x1C) + 1;
                                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                            }
                        }
                    }
                    else if (*(short *)(iVar2 + 0x1C) == 0) {
                        if ((uVar4 & 0x1000) != 0) {
                            *(u16 *)(iVar2 + 0x1E) = 0x14;
                            *(u16 *)(iVar2 + 0x1C) = 0x1D;
                            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                        }
                    }
                    else {
                        if ((*(short *)(iVar2 + 0x1C) == *(short *)(iVar2 + 0x1E)) &&
                              (sVar1 = *(short *)(iVar2 + 0x1E) + -1, *(short *)(iVar2 + 0x1E) = sVar1, sVar1 < 0))
                        {
                            *(u16 *)(iVar2 + 0x1E) = 0;
                        }
                        *(short *)(iVar2 + 0x1C) = *(short *)(iVar2 + 0x1C) + -1;
                        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    }
                }
                else {
                    func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                    *(u32 *)(iVar2 + 8) = 0xFFFFFFFF;
                    *(u16 *)(iVar2 + 0x1E) = 0xFFFF;
                    *(u16 *)(iVar2 + 0x1C) = 0xFFFF;
                    func_0039C740();
                }
            }
            else {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                *(u32 *)(iVar2 + 8) = 0;
                *(u32 *)(iVar2 + 4) = 1;
            }
        }
    }
}
