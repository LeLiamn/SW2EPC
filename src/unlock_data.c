/*
 * unlock_data.c - the gallery and encyclopedia unlock data (the 0x8220-byte block func_0019FBF0
 * gives, saved with the system data): officer, province and event records, bit arrays of what was
 * seen, and their updates after a game or a battle (parts of 0x0039FAB0-0x003A4DE0). Original
 * file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00459EB8[];                  /* "" */

u8 *func_0019FBF0(void);
u8 *func_0039FAB0(int a, int b);
u8 *func_0039FB00(int o);
u8 *func_0039FB40(int p);
u8 *func_0039FB80(void);
u8 *func_0039FBB0(int k);
int func_0039FC30(int x);
int func_0039FBF0(int k);
void func_003A0220(int k, int on);
int func_002F57F0(int x);
u8 func_002F5840(int v);
void func_00120928(u8 *to, const u8 *from);
void func_00118850(void *p, int n);
void func_003A3020(void);
void func_003A2BA0(void);
void func_003A2D20(void);
void func_003A2F10(void);
int func_00327D50(void);
int func_002F4080(int o);
void func_0039FF60(int o, int v);
int func_00328190(int k);
int func_00328C00(int k);
void func_003A3980(int o);
int func_0036BA80(int *list, int a);
int func_00328A60(int k);
u8 func_00328B00(int k);
int func_00329540(int k);
void func_003A48E0(void);
void func_003A4990(int k);
int func_003636F0(int p);
u8 func_003294A0(int p);

/* 0x003A0320, 0x60 bytes. */
void func_003A0320(int a, int b, int v)
{
    if (a >= 0 && a < 0x1E && b >= 0 && b < 2)
        *(int *)(func_0039FAB0(a, b) + 0x4) = v;
}

/* 0x003A0380, 0x54 bytes. */
int func_003A0380(int a, int b)
{
    if (a < 0 || a > 0x1D)
        return -1;
    if (b < 0 || b > 1)
        return -1;
    return *(int *)(func_0039FAB0(a, b) + 0x4);
}

/* 0x003A03E0, 0x5C bytes. */
void func_003A03E0(int a, int b, u16 v)
{
    if (a >= 0 && a < 0x1E && b >= 0 && b < 2)
        *(u16 *)(func_0039FAB0(a, b) + 0x8) = v;
}

/* 0x003A0440, 0x54 bytes. */
u16 func_003A0440(int a, int b)
{
    if (a < 0 || a > 0x1D)
        return 0;
    if (b < 0 || b > 1)
        return 0;
    return *(u16 *)(func_0039FAB0(a, b) + 0x8);
}

/* 0x003A04A0, 0x5C bytes. */
void func_003A04A0(int a, int b, u16 v)
{
    if (a >= 0 && a < 0x1E && b >= 0 && b < 2)
        *(u16 *)(func_0039FAB0(a, b) + 0xA) = v;
}

/* 0x003A0500, 0x54 bytes. */
u16 func_003A0500(int a, int b)
{
    if (a < 0 || a > 0x1D)
        return 0;
    if (b < 0 || b > 1)
        return 0;
    return *(u16 *)(func_0039FAB0(a, b) + 0xA);
}

/* 0x003A0560, 0x44 bytes. */
void func_003A0560(int k, int v)
{
    if (k >= 0 && k < 0x19F)
        *(int *)(func_0039FB00(k) + 0x0) = v;
}

/* 0x003A05B0, 0x38 bytes. */
int func_003A05B0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(int *)(func_0039FB00(k) + 0x0);
}

/* 0x003A05F0, 0x40 bytes. */
void func_003A05F0(int k, u16 v)
{
    if (k >= 0 && k < 0x19F)
        *(u16 *)(func_0039FB00(k) + 0x6) = v;
}

/* 0x003A0630, 0x38 bytes. */
u32 func_003A0630(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u16 *)(func_0039FB00(k) + 0x6);
}

/* 0x003A0670, 0x40 bytes. */
void func_003A0670(int k, u16 v)
{
    if (k >= 0 && k < 0x19F)
        *(u16 *)(func_0039FB00(k) + 0x8) = v;
}

/* 0x003A06B0, 0x38 bytes. */
u32 func_003A06B0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u16 *)(func_0039FB00(k) + 0x8);
}

/* 0x003A06F0, 0x40 bytes. */
void func_003A06F0(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xA) = v;
}

/* 0x003A0730, 0x38 bytes. */
u32 func_003A0730(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xA);
}

/* 0x003A0770, 0x40 bytes. */
void func_003A0770(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xB) = v;
}

/* 0x003A07B0, 0x38 bytes. */
u32 func_003A07B0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xB);
}

/* 0x003A07F0, 0x40 bytes. */
void func_003A07F0(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xC) = v;
}

/* 0x003A0830, 0x38 bytes. */
u32 func_003A0830(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xC);
}

/* 0x003A0870, 0x40 bytes. */
void func_003A0870(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xD) = v;
}

/* 0x003A08B0, 0x38 bytes. */
u32 func_003A08B0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xD);
}

/* 0x003A08F0, 0x40 bytes. */
void func_003A08F0(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xE) = v;
}

/* 0x003A0930, 0x38 bytes. */
u32 func_003A0930(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xE);
}

/* 0x003A0970, 0x40 bytes. */
void func_003A0970(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0xF) = v;
}

/* 0x003A09B0, 0x38 bytes. */
u32 func_003A09B0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0xF);
}

/* 0x003A09F0, 0x40 bytes. */
void func_003A09F0(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0x10) = v;
}

/* 0x003A0A30, 0x38 bytes. */
u32 func_003A0A30(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0x10);
}

/* 0x003A0A70, 0x40 bytes. */
void func_003A0A70(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0x11) = v;
}

/* 0x003A0AB0, 0x38 bytes. */
u8 func_003A0AB0(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0x11);
}

/* 0x003A0D10, 0x40 bytes. */
void func_003A0D10(int k, u8 v)
{
    if (k >= 0 && k < 0x19F)
        *(u8 *)(func_0039FB00(k) + 0x47) = v;
}

/* 0x003A0D50, 0x38 bytes. */
u32 func_003A0D50(int k)
{
    if (k < 0 || k > 0x19E)
        return 0;
    return *(u8 *)(func_0039FB00(k) + 0x47);
}

/* 0x003A0D90, 0x40 bytes. */
void func_003A0D90(int k, u8 v)
{
    if (k >= 0 && k < 0x75)
        *(u8 *)(func_0039FB40(k) + 0x0) = v;
}

/* 0x003A0DD0, 0x38 bytes. */
u8 func_003A0DD0(int k)
{
    if (k < 0 || k > 0x74)
        return 0x7F;
    return *(u8 *)(func_0039FB40(k) + 0x0);
}

/* 0x003A0E10, 0x40 bytes. */
void func_003A0E10(int k, u8 v)
{
    if (k >= 0 && k < 0x75)
        *(u8 *)(func_0039FB40(k) + 0x1) = v;
}

/* 0x003A0E50, 0x38 bytes. */
u8 func_003A0E50(int k)
{
    if (k < 0 || k > 0x74)
        return 0;
    return *(u8 *)(func_0039FB40(k) + 0x1);
}

/* 0x003A0EF0, 0x40 bytes. */
void func_003A0EF0(int k, u8 v)
{
    if (k >= 0 && k < 0x75)
        *(u8 *)(func_0039FB40(k) + 0x2) = v;
}

/* 0x003A11B0, 0x40 bytes. */
void func_003A11B0(int k, u8 v)
{
    if (k >= 0 && k < 0x75)
        *(u8 *)(func_0039FB40(k) + 0x13) = v;
}

/* 0x003A11F0, 0x38 bytes. */
u8 func_003A11F0(int k)
{
    if (k < 0 || k > 0x74)
        return 0;
    return *(u8 *)(func_0039FB40(k) + 0x13);
}

/* 0x003A1F80, 0x40 bytes. */
void func_003A1F80(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x0) = v;
}

/* 0x003A1FC0, 0x38 bytes. */
u8 func_003A1FC0(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x0);
}

/* 0x003A2090, 0x40 bytes. */
void func_003A2090(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x12) = v;
}

/* 0x003A20D0, 0x38 bytes. */
u8 func_003A20D0(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x12);
}

/* 0x003A2110, 0x40 bytes. */
void func_003A2110(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x13) = v;
}

/* 0x003A2150, 0x38 bytes. */
u8 func_003A2150(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x13);
}

/* 0x003A2190, 0x40 bytes. */
void func_003A2190(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x14) = v;
}

/* 0x003A21D0, 0x38 bytes. */
u8 func_003A21D0(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x14);
}

/* 0x003A22E0, 0x40 bytes. */
void func_003A22E0(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x16) = v;
}

/* 0x003A2320, 0x38 bytes. */
u8 func_003A2320(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x16);
}

/* 0x003A2360, 0x40 bytes. */
void func_003A2360(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x17) = v;
}

/* 0x003A23A0, 0x38 bytes. */
u8 func_003A23A0(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x17);
}

/* 0x003A24C0, 0x40 bytes. */
void func_003A24C0(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x1D) = v;
}

/* 0x003A2500, 0x38 bytes. */
u8 func_003A2500(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x1D);
}

/* 0x003A2540, 0x40 bytes. */
void func_003A2540(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x1E) = v;
}

/* 0x003A2580, 0x38 bytes. */
u8 func_003A2580(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x1E);
}

/* 0x003A25C0, 0x40 bytes. */
void func_003A25C0(int k, u8 v)
{
    if (k >= 0 && k < 0x4)
        *(u8 *)(func_0039FBB0(k) + 0x1F) = v;
}

/* 0x003A2600, 0x38 bytes. */
u8 func_003A2600(int k)
{
    if (k < 0 || k > 0x3)
        return 0;
    return *(u8 *)(func_0039FBB0(k) + 0x1F);
}

/* 0x003A0F90, 0x54 bytes. */
void func_003A0F90(int k, int j, u8 v)
{
    if (k >= 0 && k < 0x75)
        func_0039FB40(k)[j + 0x3] = v;
}

/* 0x003A0FF0, 0x4C bytes. */
u8 func_003A0FF0(int k, int j)
{
    if (k < 0 || k > 0x74)
        return 0;
    return func_0039FB40(k)[j + 0x3];
}

/* 0x003A10A0, 0x54 bytes. */
void func_003A10A0(int k, int j, u8 v)
{
    if (k >= 0 && k < 0x75)
        func_0039FB40(k)[j + 0xB] = v;
}

/* 0x003A1100, 0x4C bytes. */
u8 func_003A1100(int k, int j)
{
    if (k < 0 || k > 0x74)
        return 0;
    return func_0039FB40(k)[j + 0xB];
}

/* 0x003A1290, 0x58 bytes. */
void func_003A1290(int k, u8 v)
{
    if (k >= 0 && k < 0x1C)
        func_0019FBF0()[k + 0x8100] = v;
}

/* 0x003A12F0, 0x54 bytes. */
u8 func_003A12F0(int k)
{
    if (k < 0 || k > 0x1B)
        return 0;
    return func_0019FBF0()[k + 0x8100];
}

/* 0x003A1350, 0x58 bytes. */
void func_003A1350(int k, u8 v)
{
    if (k >= 0 && k < 0x1C)
        func_0019FBF0()[k + 0x811C] = v;
}

/* 0x003A13B0, 0x54 bytes. */
u8 func_003A13B0(int k)
{
    if (k < 0 || k > 0x1B)
        return 0;
    return func_0019FBF0()[k + 0x811C];
}

/* 0x003A2750, 0x58 bytes. */
void func_003A2750(int k, u8 v)
{
    if (k >= 0 && k < 0x2)
        func_0019FBF0()[k + 0x821B] = v;
}

/* 0x003A27B0, 0x54 bytes. */
u8 func_003A27B0(int k)
{
    if (k < 0 || k > 0x1)
        return 0;
    return func_0019FBF0()[k + 0x821B];
}

/* 0x003A0040, 0x80 bytes. */
int func_003A0040(int k)
{
    if (k < 0 || k >= 0x190)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x6 + (k >> 3)]) != 0;
}

/* 0x003A00C0, 0xDC bytes. Sets or clears bit `k` of the array at +0x38. */
void func_003A00C0(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x64)
        return;
    b = func_0019FBF0() + 0x38 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A01A0, 0x80 bytes. */
int func_003A01A0(int k)
{
    if (k < 0 || k >= 0x64)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x38 + (k >> 3)]) != 0;
}

/* 0x003A1410, 0xF8 bytes. Sets or clears bit `k` of the array at +0x8138. */
void func_003A1410(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x10)
        return;
    b = func_0019FBF0() + 0x8138 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A1510, 0x88 bytes. */
int func_003A1510(int k)
{
    if (k < 0 || k >= 0x10)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x8138 + (k >> 3)]) != 0;
}

/* 0x003A15A0, 0xF8 bytes. Sets or clears bit `k` of the array at +0x813A. */
void func_003A15A0(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x10)
        return;
    b = func_0019FBF0() + 0x813A + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A16A0, 0xF8 bytes. Sets or clears bit `k` of the array at +0x813C. */
void func_003A16A0(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0xC8)
        return;
    b = func_0019FBF0() + 0x813C + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A17A0, 0x88 bytes. */
int func_003A17A0(int k)
{
    if (k < 0 || k >= 0xC8)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x813C + (k >> 3)]) != 0;
}

/* 0x003A1830, 0xF8 bytes. Sets or clears bit `k` of the array at +0x8155. */
void func_003A1830(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0xC8)
        return;
    b = func_0019FBF0() + 0x8155 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A1930, 0x88 bytes. */
int func_003A1930(int k)
{
    if (k < 0 || k >= 0xC8)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x8155 + (k >> 3)]) != 0;
}

/* 0x003A1B60, 0xF8 bytes. Sets or clears bit `k` of the array at +0x816F. */
void func_003A1B60(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0xE6)
        return;
    b = func_0019FBF0() + 0x816F + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A1C60, 0x88 bytes. */
int func_003A1C60(int k)
{
    if (k < 0 || k >= 0xE6)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x816F + (k >> 3)]) != 0;
}

/* 0x003A1CF0, 0xF8 bytes. Sets or clears bit `k` of the array at +0x818C. */
void func_003A1CF0(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x18)
        return;
    b = func_0019FBF0() + 0x818C + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A1DF0, 0x88 bytes. */
int func_003A1DF0(int k)
{
    if (k < 0 || k >= 0x18)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x818C + (k >> 3)]) != 0;
}

/* 0x003A1E80, 0xF8 bytes. Sets or clears bit `k` of the array at +0x818F. */
void func_003A1E80(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x3E)
        return;
    b = func_0019FBF0() + 0x818F + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x003A0280, 0x40 bytes. Whether province entry `k` is unlocked. */
int func_003A0280(int k)
{
    if (k < 0 || k > 0x74)
        return 0;
    return func_003A0DD0(k) != 0x7F;
}

/* 0x003A02C0, 0x24 bytes. */
void func_003A02C0(int x, int on)
{
    func_003A0220(func_0039FC30(x), on);
}

/* 0x003A02F0, 0x24 bytes, matching. */
int func_003A02F0(int x)
{
    return func_003A0280(func_0039FC30(x));
}

/* 0x003A0AF0, 0x24 bytes. */
void func_003A0AF0(u8 *r, int k, u8 v)
{
    r[k + 0x12] &= 0x80;
    r[k + 0x12] |= v & 0x7F;
}

/* 0x003A0B20, 0x7C bytes. An officer's level `k` (0-4). */
void func_003A0B20(int o, int k, int v)
{
    if (o < 0 || o >= 0x19F)
        return;
    if (v < 0)
        v = 0;
    else if (v > 4)
        v = 4;
    func_003A0AF0(func_0039FB00(o), k, v);
}

/* 0x003A0BA0, 0x70 bytes. */
u32 func_003A0BA0(int o, int k)
{
    u32 v;

    if (o < 0 || o > 0x19E)
        return 0;
    v = func_0039FB00(o)[k + 0x12] & 0x7F;
    if ((int)v < 0)
        v = 0;
    else if (v > 4)
        v = 4;
    return v;
}

/* 0x003A0C10, 0x34 bytes. */
void func_003A0C10(u8 *r, int k, int on)
{
    if (on == 0)
        r[k + 0x12] &= 0x7F;
    else
        r[k + 0x12] |= 0x80;
}

/* 0x003A0C50, 0x5C bytes. */
void func_003A0C50(int o, int k, int on)
{
    if (o >= 0 && o < 0x19F)
        func_003A0C10(func_0039FB00(o), k, on);
}

/* 0x003A0CB0, 0x54 bytes. */
int func_003A0CB0(int o, int k)
{
    if (o < 0 || o > 0x19E)
        return 0;
    return (func_0039FB00(o)[k + 0x12] & 0x80) != 0;
}

/* 0x003A0E90, 0x24 bytes. */
void func_003A0E90(int x, u8 v)
{
    func_003A0E10(func_0039FC30(x), v);
}

/* 0x003A0EC0, 0x24 bytes, matching. */
u8 func_003A0EC0(int x)
{
    return func_003A0E50(func_0039FC30(x));
}

/* 0x003A0F30, 0x24 bytes. */
void func_003A0F30(int x, u8 v)
{
    func_003A0EF0(func_0039FC30(x), v);
}

/* 0x003A0F60, 0x28 bytes. */
u8 func_003A0F60(int x)
{
    return func_002F5840(func_002F57F0(x));
}

/* 0x003A1040, 0x24 bytes. */
void func_003A1040(int x, int j, u8 v)
{
    func_003A0F90(func_0039FC30(x), j, v);
}

/* 0x003A1070, 0x24 bytes. */
u8 func_003A1070(int x, int j)
{
    return func_003A0FF0(func_0039FC30(x), j);
}

/* 0x003A1150, 0x24 bytes. */
void func_003A1150(int x, int j, u8 v)
{
    func_003A10A0(func_0039FC30(x), j, v);
}

/* 0x003A1180, 0x24 bytes. */
u8 func_003A1180(int x, int j)
{
    return func_003A1100(func_0039FC30(x), j);
}

/* 0x003A1230, 0x24 bytes. */
void func_003A1230(int x, u8 v)
{
    func_003A11B0(func_0039FC30(x), v);
}

/* 0x003A1260, 0x24 bytes, matching. */
u8 func_003A1260(int x)
{
    return func_003A11F0(func_0039FC30(x));
}

/* 0x003A19C0, 0x60 bytes. The four gallery sections' flags. */
void func_003A19C0(int b, int on)
{
    if (on == 0)
        *func_0039FB80() &= ~(1 << (b & 0x1F));
    else
        *func_0039FB80() |= 1 << (b & 0x1F);
}

/* 0x003A1A20, 0x3C bytes. */
int func_003A1A20(int b)
{
    return (1 << (b & 0x1F) & 0xFF & *func_0039FB80()) != 0;
}

/* 0x003A1A60, 0x20 bytes, matching. */
void func_003A1A60(int on)
{
    func_003A19C0(0, on);
}

/* 0x003A1A80, 0x1C bytes, matching. */
int func_003A1A80(void)
{
    return func_003A1A20(0);
}

/* 0x003A1AA0, 0x20 bytes, matching. */
void func_003A1AA0(int on)
{
    func_003A19C0(1, on);
}

/* 0x003A1AC0, 0x1C bytes, matching. */
int func_003A1AC0(void)
{
    return func_003A1A20(1);
}

/* 0x003A1AE0, 0x20 bytes, matching. */
void func_003A1AE0(int on)
{
    func_003A19C0(2, on);
}

/* 0x003A1B00, 0x1C bytes, matching. */
int func_003A1B00(void)
{
    return func_003A1A20(2);
}

/* 0x003A1B20, 0x20 bytes, matching. */
void func_003A1B20(int on)
{
    func_003A19C0(3, on);
}

/* 0x003A1B40, 0x1C bytes, matching. */
int func_003A1B40(void)
{
    return func_003A1A20(3);
}

/* 0x003A2000, 0x4C bytes. A save slot's name. */
void func_003A2000(int k, const u8 *s)
{
    if (k >= 0 && k < 4)
        func_00120928(func_0039FBB0(k) + 1, s);
}

/* 0x003A2050, 0x3C bytes. */
u8 *func_003A2050(int k)
{
    if (k < 0 || k > 3)
        return g_00459EB8;
    return func_0039FBB0(k) + 1;
}

/* 0x003A2210, 0x20 bytes, matching. */
u8 *func_003A2210(int k)
{
    return func_0039FAB0(k, 0) + 1;
}

/* 0x003A2230, 0x60 bytes. A 24-bit value. */
void func_003A2230(int k, u32 v)
{
    u8 *p;

    if (k < 0 || k >= 4)
        return;
    p = func_003A2210(k);
    p[0] = v;
    p[1] = v >> 8;
    p[2] = v >> 0x10;
}

/* 0x003A2290, 0x50 bytes. */
u32 func_003A2290(int k)
{
    u8 *p;

    if (k < 0 || k > 3)
        return 0;
    p = func_003A2210(k);
    return p[0] | p[1] << 8 | p[2] << 0x10;
}

/* 0x003A23E0, 0x70 bytes. */
void func_003A23E0(int k, int j, u8 v)
{
    if (k >= 0 && k < 4 && j >= 0 && j < 5)
        func_0039FBB0(k)[j + 0x18] = v;
}

/* 0x003A2450, 0x68 bytes. */
u8 func_003A2450(int k, int j)
{
    if (k < 0 || k > 3)
        return 0;
    if (j < 0 || j > 4)
        return 0;
    return func_0039FBB0(k)[j + 0x18];
}

/* 0x003A2640, 0x98 bytes. */
void func_003A2640(int k, int j, int on)
{
    if (k < 0 || k >= 4 || j < 0 || j >= 4)
        return;
    if (on == 0)
        func_0039FBB0(k)[0x20] &= ~(1 << (j & 0x1F));
    else
        func_0039FBB0(k)[0x20] |= 1 << (j & 0x1F);
}

/* 0x003A26E0, 0x70 bytes. */
int func_003A26E0(int k, int j)
{
    if (k < 0 || k > 3)
        return 0;
    if (j < 0 || j > 3)
        return 0;
    return (1 << (j & 0x1F) & func_0039FBB0(k)[0x20]) != 0;
}

/* 0x003A2810, 0x98 bytes. */
void func_003A2810(int k, int on)
{
    if (k < 0 || k >= 1)
        return;
    if (on == 0)
        func_0019FBF0()[0x821D] &= ~(1 << (k & 0x1F));
    else
        func_0019FBF0()[0x821D] |= 1 << (k & 0x1F);
}

/* 0x003A28B0, 0x60 bytes. */
int func_003A28B0(int k)
{
    if (k < 0 || k > 0)
        return 0;
    return (1 << (k & 0x1F) & 0xFF & func_0019FBF0()[0x821D]) != 0;
}

/* 0x003A2910, 0x28 bytes. */
int func_003A2910(int a, int b)
{
    return func_003A0380(a, b) != -1;
}

/* 0x003A2A00, 0x58 bytes, matching. How many of the 400 entries are seen. */
int func_003A2A00(void)
{
    int k, n = 0;

    for (k = 0; k < 400; k++) {
        if (func_003A0040(k) != 0)
            n++;
    }
    return n;
}

/* 0x003A2A60, 0x58 bytes, matching. How many province entries are unlocked. */
int func_003A2A60(void)
{
    int k, n = 0;

    for (k = 0; k < 0x75; k++) {
        if (func_003A0280(k) != 0)
            n++;
    }
    return n;
}

/* 0x003A2AC0, 0x58 bytes, matching. */
int func_003A2AC0(void)
{
    int k, n = 0;

    for (k = 0; k < 100; k++) {
        if (func_003A01A0(k) != 0)
            n++;
    }
    return n;
}

/* 0x003A2B20, 0x7C bytes, matching. Clears the 0x1E x 2 records. */
void func_003A2B20(void)
{
    int a, b;

    for (a = 0; a < 0x1E; a++) {
        for (b = 0; b < 2; b++) {
            func_003A0320(a, b, -1);
            func_003A03E0(a, b, 0);
            func_003A04A0(a, b, 0);
        }
    }
}

/* 0x003A2ED0, 0x34 bytes, matching. */
void func_003A2ED0(void)
{
    func_003A1A60(0);
    func_003A1AA0(0);
    func_003A1AE0(0);
    func_003A1B20(0);
}

/* 0x003A3260, 0x58 bytes, matching. Resets the whole block. */
void func_003A3260(void)
{
    func_00118850(func_0019FBF0(), 0x8220);
    func_003A3020();
    func_003A2B20();
    func_003A2BA0();
    func_003A2D20();
    func_003A2ED0();
    func_003A2F10();
}

/* 0x003A3690, 0x7C bytes. Marks the player force's officers as met. */
void func_003A3690(void)
{
    int f = func_00327D50(), o;

    for (o = 0; o < 0x19F; o++) {
        if ((o < 400 || o > 0x19E) && f == func_002F4080(o))
            func_0039FF60(o, 1);
    }
}

/* 0x003A3710, 0x50 bytes, matching. */
void func_003A3710(void)
{
    int k;

    for (k = 0; k < 100; k++) {
        if (func_00328190(k) != 0)
            func_003A00C0(k, 1);
    }
}

/* 0x003A3760, 0x64 bytes, matching. */
void func_003A3760(void)
{
    int k;

    for (k = 0; k < 0x75; k++) {
        int p = func_0039FBF0(k);

        if (func_00328C00(p) != 0)
            func_003A02C0(p, 1);
    }
}

/* 0x003A3920, 0x58 bytes. Keeps the best value. */
void func_003A3920(int a, int b, int v)
{
    if (func_003A0500(a, b) < v)
        func_003A04A0(a, b, v);
}

/* 0x003A3C10, 0x5C bytes, matching. */
void func_003A3C10(void)
{
    int f = func_00327D50(), o;

    for (o = 0; o < 0x19F; o++) {
        if (f == func_002F4080(o))
            func_003A3980(o);
    }
}

/* 0x003A3C70, 0x68 bytes, matching. */
void func_003A3C70(void)
{
    int list[16], n = func_0036BA80(list, 0), k;

    for (k = 0; k < n; k++)
        func_003A3980(list[k]);
}

/* 0x003A3E30, 0x78 bytes. */
void func_003A3E30(void)
{
    int k;

    for (k = 0; k < 0x1C; k++) {
        int v = func_00328A60(k);

        if (func_003A12F0(k) < v) {
            func_003A1290(k, v);
            func_003A1350(k, func_00328B00(k));
        }
    }
}

/* 0x003A3EB0, 8 bytes, matching. */
void func_003A3EB0(void)
{
}

/* 0x003A3EC0, 0x58 bytes. */
void func_003A3EC0(int k, int on)
{
    if (on != 0 && func_003A17A0(k) == 0) {
        func_003A1830(k, on);
        func_003A16A0(k, on);
    }
}

/* 0x003A47E0, 0x20 bytes, matching. */
void func_003A47E0(int v)
{
    if (v != 0)
        func_003A1A60(1);
}

/* 0x003A4800, 0x30 bytes. Section 1 opens with 100 entries seen. */
void func_003A4800(void)
{
    if (func_003A2A00() > 99)
        func_003A1AA0(1);
}

/* 0x003A4830, 0x30 bytes. */
void func_003A4830(void)
{
    if (func_003A2AC0() > 0x31)
        func_003A1AE0(1);
}

/* 0x003A4860, 0x30 bytes. */
void func_003A4860(void)
{
    if (func_003A2A60() > 0x31)
        func_003A1B20(1);
}

/* 0x003A4890, 0x50 bytes, matching. */
void func_003A4890(void)
{
    int k;

    for (k = 0; k < 0xE6; k++) {
        if (func_00329540(k + 0x87) != 0)
            func_003A1B60(k, 1);
    }
}

/* 0x003A4970, 8 bytes, matching. */
void func_003A4970(void)
{
}

/* 0x003A4980, 8 bytes, matching. */
void func_003A4980(void)
{
}

/* 0x003A4B00, 0x3C bytes, matching. */
void func_003A4B00(void)
{
    int k;

    for (k = 0; k < 4; k++)
        func_003A4990(k);
}

/* 0x003A4B40, 0x58 bytes, matching. */
void func_003A4B40(void)
{
    int p;

    for (p = 0; p < 2; p++) {
        if (func_003636F0(p) != 0)
            func_003A2750(p, func_003294A0(p));
    }
}

/* 0x003A4BA0, 0x1C bytes, matching. */
void func_003A4BA0(void)
{
    func_003A4970();
}

/* 0x003A4D10, 0x60 bytes, matching. Updates after a free-mode battle. */
void func_003A4D10(int all)
{
    func_003A3C70();
    func_003A3E30();
    func_003A48E0();
    func_003A4970();
    if (all != 0) {
        func_003A4B00();
        func_003A4B40();
    }
    func_003A2810(0, 1);
}

/* 0x003A4D70, 0x30 bytes, matching. */
void func_003A4D70(void)
{
    func_003A3E30();
    func_003A4970();
    func_003A2810(0, 1);
}

/* 0x0039FAB0, 0x4C bytes, matching. */
u8 *func_0039FAB0(int a, int b)
{
    return func_0019FBF0() + (b + a * 2) * 0xC + 0x54;
}

/* 0x0039FB00, 0x38 bytes, matching. Officer `o`'s record (0x48 bytes). */
u8 *func_0039FB00(int o)
{
    return func_0019FBF0() + o * 0x48 + 0x324;
}

/* 0x0039FB40, 0x38 bytes, matching. Province entry `p` (0x14 bytes). */
u8 *func_0039FB40(int p)
{
    return func_0019FBF0() + p * 0x14 + 0x77DC;
}

/* 0x0039FB80, 0x24 bytes, matching. */
u8 *func_0039FB80(void)
{
    return func_0019FBF0() + 0x816E;
}

/* 0x0039FBB0, 0x38 bytes, matching. Save slot record `k` (0x21 bytes). */
u8 *func_0039FBB0(int k)
{
    return func_0019FBF0() + k * 0x21 + 0x8197;
}

/* 0x0039FBF0, 0x34 bytes. Entry -> province (0x74 is province 0x78). */
int func_0039FBF0(int k)
{
    if (k > 0x73)
        k = k == 0x74 ? 0x78 : 0;
    return k;
}

/* 0x0039FC30, 0x34 bytes. Province -> entry. */
int func_0039FC30(int k)
{
    if (k > 0x73)
        k = k == 0x78 ? 0x74 : 0;
    return k;
}

/* 0x0039FC70, 0x2C bytes, matching. */
int func_0039FC70(int k)
{
    if (k < 0x74 || k == 0x78)
        return 1;
    return 0;
}

/* 0x0039FCA0, 0xDC bytes. Sets or clears bit `k` of the array at +0x0. */
void func_0039FCA0(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0xB)
        return;
    b = func_0019FBF0() + 0x0 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x0039FD80, 0x80 bytes. */
int func_0039FD80(int k)
{
    if (k < 0 || k >= 0xB)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x0 + (k >> 3)]) != 0;
}

/* 0x0039FE00, 0xDC bytes. Sets or clears bit `k` of the array at +0x2. */
void func_0039FE00(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x1E)
        return;
    b = func_0019FBF0() + 0x2 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

/* 0x0039FEE0, 0x80 bytes. */
int func_0039FEE0(int k)
{
    if (k < 0 || k >= 0x1E)
        return 0;
    return (1 << (k & 7) & func_0019FBF0()[0x2 + (k >> 3)]) != 0;
}

/* 0x0039FF60, 0xDC bytes. Sets or clears bit `k` of the array at +0x6. */
void func_0039FF60(int k, int on)
{
    u8 *b;

    if (k < 0 || k >= 0x190)
        return;
    b = func_0019FBF0() + 0x6 + (k >> 3);
    if (on == 0)
        *b &= ~(1 << (k & 7));
    else
        *b |= 1 << (k & 7);
}

extern u32 g_00428348[0x14];             /* the rank thresholds */
extern int g_0041BFB0[0x10];
u32 func_002F34E0(int o);
void func_002F40F0(int o, int r);

/* 0x003A4E50, 0xA4 bytes. Sets officer `o`'s rank by his merit. */
void func_003A4E50(int o)
{
    u32 v = func_002F34E0(o), k;

    for (k = 0; (int)k <= 0x12; k++) {
        if (g_00428348[k & 0xFF] <= v && v < g_00428348[(k + 1) & 0xFF])
            break;
    }
    func_002F40F0(o, (int)k > 0x12 ? 0x13 : k & 0xFF);
}

/* 0x003A5290, 0x90 bytes. Marks the special pages of officer `o`. */
void func_003A5290(int o)
{
    int t[16], k;

    for (k = 0; k < 16; k++)
        t[k] = g_0041BFB0[k];
    for (k = 0; k < 0x10; k++) {
        if (o == t[k])
            func_003A1410(k, 1);
    }
}
