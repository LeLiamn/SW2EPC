/*
 * emp_battle_setup.c - the Empire battle's set-up data (0x007B95E0: the battle's kind, its two
 * sides' 8 officer slots of 0x1C bytes, tactics) and the battle voice queue (16 entries at
 * 0x007B9560). Original file name unknown (parts of 0x00369560-0x0036F5E0).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_0045D784, g_0045D788, g_0045D78C, g_0045D790, g_0045D794, g_0045D798;
extern int g_0045D7A0, g_0045D7A8, g_0045D7AC;   /* (small data) the voice queue */
extern u32 g_007B95E0;                   /* the battle's kind */
extern int g_007B95EC, g_007B95F0, g_007B95F4;
extern u32 g_007B9600;
extern u32 g_007B9620;                   /* flags: 1 the second mode, 8, 0x10 */
extern int g_007B9624;
extern u8 g_007B9628[2][8][0x1C];        /* the two sides' officer slots */
extern int g_007B97E8[8], g_007B9808[8], g_007B9830[2];
extern u8 g_007B9838[4];
extern int g_007B983C[][8];
extern u8 g_007B9880[];
extern u8 g_006AA5F6, g_006AA5F7, g_006AA5F8, g_006AA5F9;
extern u8 g_00669D60[];
extern int g_00669F9C;
extern int (*g_00448440[0x1F])(void);

#define SLOT(s, k) g_007B9628[s][k]

void func_00102990(void);
void func_00369990(int k);
void func_003698F0(void);
int func_0030D7D0(void);
void func_0032D3C0(int a);
void func_00369FE0(void);
void func_003A92D0(void);
void func_003A80A0(int a);
void func_003A9060(int a);
void func_003A7D90(void);
int func_00362570(void);
int func_00362320(void);
int func_003620E0(int s, int k);
int func_002F4080(int o);
int func_002F9A90(int f);
int func_00327870(void);
int func_002F8F20(int f);
int func_00363720(int p);
int func_002FB3B0(int f);
char func_00327E90(void);
int func_002F47A0(int a);
int func_0036DB00(int a, int b);
int func_002F6A60(int a);
int func_002F4900(int a, int b);
u8 *func_002EFB00(int k);
void func_0011EB80(u8 *to, const u8 *from, int n);
void func_0036E080(void);
void func_0036E260(void);
void func_0036E310(void);
void func_0036DD90(int a, int b, int c);
int func_0036F520(int s, int k);

/* 0x00369560, 0x10 bytes, matching. */
int func_00369560(void)
{
    return g_0045D784 == 0;
}

/* 0x00369570, 8 bytes, matching. */
int func_00369570(void)
{
    return g_0045D798;
}

/* 0x003697C0, 0x28 bytes, matching. */
void func_003697C0(void)
{
    func_00102990();
    g_0045D784 = 0;
    g_0045D788 = -1;
}

/* 0x003697F0, 0x20 bytes, matching. */
void func_003697F0(void)
{
    g_0045D784 = 0;
    g_0045D798 = 0;
    g_0045D788 = -1;
    g_0045D78C = -1;
    g_0045D794 = 0;
    g_0045D790 = 0;
}

/* 0x00369810, 8 bytes, matching. */
int func_00369810(void)
{
    return g_0045D7A8;
}

/* 0x00369880, 8 bytes, matching. */
void func_00369880(int v)
{
    g_0045D7A0 = v;
}

/* 0x00369A50, 0x58 bytes, matching. Stops all the queued voices. */
void func_00369A50(void)
{
    int k;

    for (k = 0; k < g_0045D7AC; k++)
        func_00369990(k);
    func_003697C0();
    func_003698F0();
}

/* 0x00369C30, 0x14 bytes. */
int func_00369C30(void)
{
    return 1 < g_007B95E0;
}

/* 0x00369C50, 0x34 bytes. Whether the battle is an event one (kinds 6-0x12). */
int func_00369C50(void)
{
    if ((int)g_007B95E0 < 6 || (int)g_007B95E0 > 0x12)
        return 0;
    return 1;
}

/* 0x00369D00, 0x24 bytes. */
int func_00369D00(void)
{
    return g_007B9600 < 0x19F;
}

/* 0x00369FB0, 0x24 bytes, matching. */
void func_00369FB0(void)
{
    func_0032D3C0(func_0030D7D0());
}

/* 0x0036A560, 0x50 bytes. */
void func_0036A560(void)
{
    if (g_007B95EC == 0)
        func_00369FE0();
    else if (g_007B95EC == 1)
        func_00369FB0();
}

/* 0x0036AA20, 0x34 bytes, matching. */
void func_0036AA20(void)
{
    func_003A92D0();
    func_003A80A0(0);
    func_003A9060(-1);
    func_003A7D90();
}

/* 0x0036B1E0, 0xC bytes. */
int func_0036B1E0(void)
{
    return g_007B95F0;
}

/* 0x0036B1F0, 0xC bytes. */
int func_0036B1F0(void)
{
    return g_007B95F4;
}

/* 0x0036B260, 0x14 bytes. Whether the battle runs in the second mode. */
int func_0036B260(void)
{
    return (g_007B9620 & 1) != 0;
}

/* 0x0036B200, 0x5C bytes. */
int func_0036B200(void)
{
    int s = func_00362570();

    if (func_0036B260() == 0 || (s != 0 && s != 4 && s != 2))
        return 1;
    return 0;
}

/* 0x0036B2F0, 0x14 bytes. */
int func_0036B2F0(void)
{
    return (g_007B9620 & 8) != 0;
}

/* 0x0036B310, 0x14 bytes. */
int func_0036B310(void)
{
    return (g_007B9620 & 0x10) != 0;
}

/* 0x0036B330, 0xC bytes. */
int func_0036B330(void)
{
    return g_007B9624;
}

/* 0x0036B340, 0x54 bytes. Slot `k` of side `s`: its officer. */
u16 func_0036B340(u32 s, u32 k)
{
    if (s < 2 && k < 8)
        return *(u16 *)SLOT(s, k);
    return 0;
}

/* 0x0036B3A0, 0x54 bytes. */
u16 func_0036B3A0(u32 s, u32 k)
{
    if (s < 2 && k < 8)
        return *(u16 *)(SLOT(s, k) + 2);
    return 0;
}

/* 0x0036B4A0, 0x30 bytes. */
int func_0036B4A0(int s, int k)
{
    return *(int *)(SLOT(s, k) + 0xC);
}

/* 0x0036B4D0, 0x34 bytes, matching. */
u8 func_0036B4D0(int s, int k, int j)
{
    return SLOT(s, k)[j + 0x10];
}

/* 0x0036B6C0, 0x30 bytes, matching. */
u8 func_0036B6C0(int s, int k)
{
    return SLOT(s, k)[0x19];
}

/* 0x0036B6F0, 0x28 bytes, matching. */
u8 func_0036B6F0(void)
{
    return func_0036B6C0(0, func_00362320());
}

/* 0x0036B820, 0x60 bytes. Whether slot `k` of side `s` has flags `m`. */
int func_0036B820(u32 s, u32 k, u8 m)
{
    if (s < 2 && k < 8)
        return (SLOT(s, k)[6] & m) != 0;
    return 0;
}

/* 0x0036B880, 0x38 bytes. */
int func_0036B880(u32 s, u32 k)
{
    if (s < 2 && k < 8)
        return func_0036B820(s, k, 1);
    return 0;
}

/* 0x0036B940, 0x38 bytes. */
int func_0036B940(u32 s, u32 k)
{
    if (s < 2 && k < 8)
        return func_0036B820(s, k, 8);
    return 0;
}

/* 0x0036B8C0, 0x74 bytes. Side `s`'s first slot with flag 8 (8: none). */
int func_0036B8C0(u32 s)
{
    int k;

    for (k = 0; k < 8; k++) {
        if (func_0036B940(s, k) != 0)
            return k;
    }
    return 8;
}

/* 0x0036B980, 0x30 bytes. */
int func_0036B980(u32 s)
{
    if (s < 2)
        return g_007B9830[s];
    return 0;
}

/* 0x0036B9B0, 0x14 bytes. */
u8 func_0036B9B0(int k)
{
    return g_007B9838[k];
}

/* 0x0036B9D0, 0x50 bytes. */
char func_0036B9D0(void)
{
    int k;
    char n = 0;

    for (k = 0; k < 4; k++)
        n += func_0036B9B0(k);
    return n;
}

/* 0x0036BA20, 0x20 bytes, matching. */
int func_0036BA20(int a, int b)
{
    return g_007B983C[a][b];
}

/* 0x0036BA40, 0x18 bytes, matching. */
int func_0036BA40(int k)
{
    return g_007B97E8[k];
}

/* 0x0036BA60, 0x18 bytes, matching. */
int func_0036BA60(int k)
{
    return g_007B9808[k];
}

/* 0x0036CFC0, 0x3C bytes. */
void func_0036CFC0(void)
{
    g_007B9838[2] = g_006AA5F8;
    g_007B9838[0] = g_006AA5F6;
    g_007B9838[1] = g_006AA5F7;
    g_007B9838[3] = g_006AA5F9;
}

/* 0x0036D130, 0x20 bytes, matching. */
void func_0036D130(int a, int b, int v)
{
    g_007B983C[a][b] = v;
}

/* 0x0036D150, 0x18 bytes. */
void func_0036D150(int v)
{
    g_007B9620 = 0;
    if (v != 0)
        g_007B9620 = 8;
}

/* 0x0036D170, 0xC bytes. */
void func_0036D170(void)
{
    g_007B9620 = 0;
}

/* 0x0036D2E0, 0x14 bytes, matching. Whether this is an Empire battle. */
int func_0036D2E0(void)
{
    return *(int *)(g_00669D60 + 0x58) == 0;
}

/* 0x0036D300, 0x10 bytes, matching. */
u32 func_0036D300(void)
{
    return *(u32 *)(g_00669D60 + 0x200) & 0x10;
}

/* 0x0036D310, 0x38 bytes. Whether the battle is of kind 0x10-0x12. */
int func_0036D310(void)
{
    int ok = 0;

    if ((u32)func_00362570() > 0xF)
        ok = (u32)func_00362570() < 0x13;
    return ok;
}

/* 0x0036D350, 0x24 bytes, matching. The force of slot `k` of side `s`. */
int func_0036D350(int s, int k)
{
    return func_002F4080(func_003620E0(s, k));
}

/* 0x0036D380, 0x24 bytes, matching. */
int func_0036D380(int s, int k)
{
    return func_002F9A90(func_0036D350(s, k));
}

/* 0x0036D3B0, 0x44 bytes. */
int func_0036D3B0(int o)
{
    if (func_0036D2E0() == 0)
        return 0;
    return o == func_00327870();
}

/* 0x0036D500, 0x4C bytes. Side `s`'s force. */
int func_0036D500(int s)
{
    if (func_0036D2E0() == 0)
        return 0x19;
    return func_002F4080(func_003620E0(s, 0));
}

/* 0x0036D550, 0x48 bytes. Side `s`'s lord. */
int func_0036D550(int s)
{
    if (func_0036D2E0() == 0)
        return 0x19F;
    return func_002F8F20(func_0036D500(s));
}

/* 0x0036D6A0, 0x24 bytes, matching. */
int func_0036D6A0(int p)
{
    return func_002F4080(func_00363720(p));
}

/* 0x0036D6D0, 0x24 bytes, matching. */
int func_0036D6D0(void)
{
    return func_002FB3B0(func_0036D6A0(0));
}

/* 0x0036D700, 0x3C bytes. */
int func_0036D700(void)
{
    if (func_0036D2E0() == 0)
        return 0;
    return func_00327E90() > 9;
}

/* 0x0036D740, 0x38 bytes. */
int func_0036D740(void)
{
    if (func_0036D2E0() == 0)
        return 0;
    return func_00327E90() < -9;
}

/* 0x0036DBA0, 0x5C bytes, matching. */
int func_0036DBA0(int a, int b)
{
    int x = func_002F47A0(a), y = func_0036DB00(a, b);

    return y < x ? x : y;
}

/* 0x0036DC00, 0x30 bytes, matching. */
int func_0036DC00(int a)
{
    return func_0036DBA0(a, func_002F6A60(a));
}

/* 0x0036DC30, 0x44 bytes, matching. */
int func_0036DC30(int a, int b)
{
    int x = func_002F47A0(a);

    return x < func_0036DB00(a, b);
}

/* 0x0036DC80, 0x50 bytes, matching. */
int func_0036DC80(int a, int b)
{
    if (func_0036DBA0(a, b) == 0)
        return 0;
    return func_002F4900(a, b) != 0;
}

/* 0x0036DCD0, 0xC bytes, matching. */
u8 *func_0036DCD0(void)
{
    return g_007B9880;
}

/* 0x0036E040, 0x34 bytes. Loads the tactics state from the save image. */
void func_0036E040(void)
{
    u8 *p = func_002EFB00(9);

    func_0011EB80(func_0036DCD0(), p + 0xB5, 9);
}

/* 0x0036E110, 0x1C bytes, matching. */
void func_0036E110(void)
{
    func_0036E040();
}

/* 0x0036E130, 0x40 bytes, matching. */
void func_0036E130(void)
{
    if (*(int *)(g_00669D60 + 0x20C) == 1)
        func_0036E110();
    else
        func_0036E080();
}

/* 0x0036E3C0, 0x40 bytes. Every 50 frames. */
void func_0036E3C0(void)
{
    if (g_00669F9C % 0x32 == 0) {
        func_0036E260();
        func_0036E310();
    }
}

/* 0x0036E400, 0x1C bytes, matching. */
void func_0036E400(int a, int b)
{
    func_0036DD90(a, b, 0x1E);
}

/* 0x0036EEB0, 0x1C bytes, matching. */
void func_0036EEB0(int a, int b)
{
    func_0036DD90(a, b, 0x78);
}

/* 0x0036EEE0, 0x3C bytes, matching. */
void func_0036EEE0(int s, int b)
{
    if (s == 0)
        g_00669D60[0x252] = 1;
    else
        g_00669D60[0x251] = 1;
    func_0036DD90(s, b, 0x78);
}

/* 0x0036EF20, 0x4C bytes, matching. */
void func_0036EF20(int s)
{
    if (func_0036F520(s, 0x1D) == 0) {
        if (s == 0)
            g_00669D60[0x252] = 0;
        else
            g_00669D60[0x251] = 0;
    }
}

/* 0x0036EF70, 0x1C bytes, matching. */
void func_0036EF70(int a, int b)
{
    func_0036DD90(a, b, 0x78);
}

/* 0x0036EFA0, 0x1C bytes, matching. */
int func_0036EFA0(u32 v)
{
    return 0x14 < v && v < 0x1F;
}

/* 0x0036F180, 0x34 bytes. */
int func_0036F180(u32 v)
{
    if (v < 0x1F)
        return g_00448440[v]();
    return 4;
}

/* 0x0036F5C0, 0x20 bytes, matching. */
int func_0036F5C0(int s)
{
    return func_0036F520(s, 0x1C) != 0;
}
