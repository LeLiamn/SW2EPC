/*
 * emp_battle_setup.c - the Empire battle's set-up data (0x007B95E0: the battle's kind, its two
 * sides' 8 officer slots of 0x1C bytes, tactics) and the battle voice queue (16 entries at
 * 0x007B9560). Original file name unknown (parts of 0x00369560-0x0036F5E0).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_BATTLE_SETUP_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

void func_00369990(int k);
void func_003698F0(void);
int func_0030D7D0(void);
void func_0032D3C0(int a);
void func_00369FE0(void);
int func_0036DB00(int a, int b);
void func_0011EB80(u8 *to, const u8 *from, int n);

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
u32 func_0036B340(u32 s, u32 k)
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
u32 func_0036B4D0(int s, int k, int j)
{
    return SLOT(s, k)[j + 0x10];
}

/* 0x0036B6C0, 0x30 bytes, matching. */
u8 func_0036B6C0(int s, int k)
{
    return SLOT(s, k)[0x19];
}

/* 0x0036B6F0, 0x28 bytes, matching. */
u8 func_0036B6F0(int p)
{
    return func_0036B6C0(0, func_00362320(p));
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
    int x = func_002F47A0(a, b), y = func_0036DB00(a, b);

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
    int x = func_002F47A0(a, b);

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
    u8 *p = (u8 *)PS2_PTR(func_002EFB00(9));

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

/* The voice queue's player and more battle set-up checks (parts of 0x00369580-0x0036E730). */

extern char g_0045D780;
extern int g_0045D79C, g_0045D7A4;
extern int g_007B9560[0x10][2];          /* the voice queue (voice, delay) */
extern int g_007B95FC[8];                /* the battle's officers */
extern int g_007B9828[2];
extern u8 *g_0045D2F0;
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

int func_0036B880(u32 s, u32 k);
void func_0036D180(u8 o, u8 *p);
extern u8 g_006A1D58[][0x68];

/* 0x00369580, 0x94 bytes. The voice player's frame (a 50-frame pause between voices). */
void func_00369580(void)
{
    if (g_0045D790 >= 1) {
        g_0045D790--;
        return;
    }
    if (g_0045D798 == 0)
        return;
    if (g_0045D794 == 0) {
        g_0045D794 = 1;
        return;
    }
    g_0045D780 = g_0045D780 == 0;
    if (g_0045D780 == 0 && func_00102960(0) != 0) {
        g_0045D794 = 0;
        g_0045D798 = func_0023A630() != 0;
    }
}

/* 0x00369620, 0xB0 bytes. Steps the voice loading (1 load, 2 wait, 4 loaded, 5 ready). */
void func_00369620(void)
{
    if (g_0045D784 != 5) {
        if (g_0045D784 == 4) {
            if (func_00102960(0) != 0)
                g_0045D784 = 5;
        } else if (g_0045D784 == 2) {
            if (func_0023A630() == 0)
                g_0045D784 = 4;
        } else if (g_0045D784 == 1 && func_00102960(0) != 0) {
            g_0045D784 = 2;
        }
    }
    func_00369580();
}

void func_00369750(int v);

/* 0x003696D0, 0x80 bytes. Plays voice `v` once it is ready; whether it started. */
int func_003696D0(int v)
{
    if (v == -1)
        return 1;
    if (g_0045D788 == v) {
        if (g_0045D784 == 5) {
            func_0023A6D0(v);
            g_0045D790 = 0x32;
            g_0045D784 = 0;
            g_0045D798 = 1;
            g_0045D794 = 0;
            g_0045D78C = g_0045D788;
            return 1;
        }
        return 0;
    }
    func_00369750(v);
    return 0;
}

/* 0x00369750, 0x68 bytes. Starts loading voice `v`. */
void func_00369750(int v)
{
    if (v == -1)
        return;
    if (g_0045D788 == v) {
        if (g_0045D784 == 0)
            g_0045D784 = 5;
    } else {
        func_0023A660(v);
        g_0045D784 = 1;
        g_0045D788 = v;
    }
}

/* 0x00369820, 0x58 bytes, matching. Moves to the next queued voice. */
void func_00369820(void)
{
    while (g_0045D7A8 < g_0045D7AC) {
        g_0045D7A8++;
        if (g_007B9560[g_0045D7A8][0] != -1)
            break;
    }
}

/* 0x00369890, 0x60 bytes. Queues voice `v` after `d` frames; its slot. */
int func_00369890(int v, int d)
{
    if (v == -1)
        return 1;
    if (g_0045D7AC < 0x10) {
        g_007B9560[g_0045D7AC][0] = v;
        g_007B9560[g_0045D7AC][1] = d;
        return g_0045D7AC++;
    }
    return 0x10;
}

/* 0x00369C90, 0x6C bytes. Whether the battle's cost fits the player force's means. */
int func_00369C90(void)
{
    int v = g_007B95F0;

    if (func_002F9060(func_00327D50()) * 10 < v)
        return 0;
    return g_007B95FC[0] >= 0 && g_007B95FC[0] < 0x19F;
}

/* 0x0036A9B0, 0x6C bytes. */
void func_0036A9B0(void)
{
    int k;

    for (k = 0; k < 8; k++) {
        int o = g_007B95FC[k];

        if (o >= 0 && o < 0x19F)
            func_002F4760(o, 10);
    }
}

/* 0x0036B170, 0x64 bytes. */
void func_0036B170(int *out)
{
    int k;

    for (k = 0; k < 8; k++)
        out[k] = g_007B95FC[k];
}

/* 0x0036B280, 0x68 bytes. */
int func_0036B280(int s)
{
    u32 m;

    if (s < 0 || s > 1)
        return 0;
    if (s == 1)
        m = 4;
    else
        m = 2;
    return (g_007B9620 & m) != 0;
}

/* 0x0036B400, 0x9C bytes. Slot `k`'s soldiers lost. */
int func_0036B400(u32 s, u32 k)
{
    int d;

    if (s >= 2 || k >= 8)
        return 0;
    d = func_0036B3A0(s, k) - func_0036B340(s, k);
    return d < 0 ? 0 : d;
}

/* 0x0036B510, 0x6C bytes. */
char func_0036B510(int x)
{
    int k;
    char n = 0;

    for (k = 0; k < 8; k++)
        n += func_0036B4D0(0, func_00362320(x), k);
    return n;
}

/* 0x0036C4B0, 0x80 bytes. The slot of side `s`'s lord (8: none). */
int func_0036C4B0(int s)
{
    int l = func_002F8F20(func_002F4080(func_003620E0(s, 0))), k;

    for (k = 0; k < 8; k++) {
        if (l == func_003620E0(s, k))
            return k;
    }
    return 8;
}

/* 0x0036CE50, 0x98 bytes. Both sides' soldier totals. */
void func_0036CE50(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        int n = 0;

        for (k = 0; k < 8; k++) {
            if (func_0036B880(s, k) != 0)
                n += func_0036B340(s, k);
        }
        g_007B9828[s] = n;
    }
}

/* 0x0036CEF0, 0xC4 bytes. Both sides' losses. */
void func_0036CEF0(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        int n = 0;

        for (k = 0; k < 8; k++) {
            u8 **g = func_0033EF80(k + s * 8);

            if (func_0036B880(s, k) != 0 && func_0033B1E0(g) != 0)
                n += func_0036B400(s, k);
        }
        g_007B9830[s] = n;
    }
}

/* 0x0036D230, 0xB0 bytes. Resets the unlock bookkeeping (`v`: from the save instead). */
void func_0036D230(int v)
{
    int k;

    if (v != 0) {
        func_003A5240();
        return;
    }
    for (k = 0; k < 0x79; k++)
        func_0036D180(k, func_00328B30(k));
    for (k = 0; k < 0x1C; k++) {
        func_00328A00(k, 0);
        func_00328AA0(k, 0);
    }
    func_0019FC30();
    for (k = 0; k < 2; k++)
        func_00329450(k, 4);
}

/* 0x0036D400, 0x7C bytes. Whether officer `o` is a player officer (Empire battles). */
int func_0036D400(int o)
{
    int k;

    if (func_0036D2E0() == 0)
        return 0;
    for (k = 0; k < 4; k++) {
        if (o == func_00327AE0(k))
            return 1;
    }
    return 0;
}

/* 0x0036D480, 0x80 bytes. Side `s`'s lord's colour. */
int func_0036D480(int s)
{
    int o = func_003620E0(s, 0), f;

    if (func_0036D2E0() == 0)
        return 0;
    f = func_002F4080(o);
    if (f < 0 || f >= 0x19)
        return 0;
    o = func_002F8F20(f);
    if (o < 0 || o > 0x19E)
        return 0;
    return func_002F6850(o);
}

/* 0x0036D5A0, 0x74 bytes. Side `s`'s province count. */
int func_0036D5A0(u32 s)
{
    int f;

    if (s >= 2)
        return 0;
    f = func_0036D500(s);
    if (f < 0 || f > 0x18)
        return s == 0 ? 10 : 4;
    return func_002FB3B0(f);
}

/* 0x0036D620, 0x78 bytes. */
int func_0036D620(int s)
{
    int f;

    if (func_0036D2E0() == 0)
        return 0;
    if (s == func_0035F0C0())
        return 0;
    f = func_00362490();
    if (f < 0 || f > 0x18)
        return 0;
    return func_0030B090(f);
}

/* 0x0036D780, 0x5C bytes. */
int func_0036D780(void)
{
    if (func_0036D310() != 0)
        return 0;
    if (func_0036D2E0() == 0)
        return 1;
    return func_002FABC0(func_0036D6A0(0)) > 499;
}

/* 0x0036D7E0, 0x68 bytes. */
int func_0036D7E0(void)
{
    int v;

    if (func_0036D2E0() == 0)
        return 0;
    v = func_003623B0();
    if (v == 1 || v == 0)
        return func_00327CC0() != 3;
    return 0;
}

/* 0x0036D970, 0x40 bytes. Whether pairs (a, b) and (c, d) are the same pair. */
int func_0036D970(int a, int b, int c, int d)
{
    if (a == c && b == d)
        return 1;
    return a == d && b == c;
}

/* 0x0036DB00, 0x9C bytes. */
int func_0036DB00(int o, int k)
{
    int f;

    if (func_0032E7B0() != 0 || k < 0 || k >= 0x35 || k >= 0x28)
        return 0;
    f = func_002F4080(o);
    if (f < 0 || f >= 0x19)
        return 0;
    return func_0036D9B0(f, k);
}

/* 0x0036E680, 0xB4 bytes. One of the enemy's officer groups at random. */
u8 **func_0036E680(u32 s)
{
    u32 list[16], n = func_0033F430(func_0035D5A0(s), 1, list, 0x10);

    if (n == 0)
        return 0;
    return (u8 **)g_006A1D58[list[(int)RANDOM() % (int)n]];
}

/* The voice queue's set-up and frame, the battle set-up's officer choices and counts (parts of
 * 0x003698F0-0x0036BD04). */

extern u32 g_007B95E4, g_007B95E8, g_007B95F8;

void func_003697F0(void);
int func_002F7D90(int a, int (*fn)(), int b, int c, int d, int e);
int func_0032D9C0(void);
int func_00369C50(void);
int func_0036AA60(void);

/* 0x003698F0, 0x98 bytes. Clears the voice queue. */
void func_003698F0(void)
{
    int k;

    for (k = 0; k < 0x10; k++) {
        g_007B9560[k][0] = -1;
        g_007B9560[k][1] = 0;
    }
    g_0045D7A0 = 0;
    g_0045D7AC = 0;
    g_0045D7A8 = 0;
    g_0045D7A4 = 0;
    g_0045D79C = 0;
    func_00102960(1);
    func_003697F0();
}

/* 0x00369990, 0xB8 bytes. Drops queued voice `k`. */
void func_00369990(int k)
{
    func_00102960(1);
    if (func_00369570() == 0 || g_0045D7A4 != k) {
        if (func_00369560() == 0 && g_0045D7A8 == k) {
            func_003697C0();
            func_00369820();
        } else {
            g_007B9560[k][0] = -1;
            if (g_0045D7A8 == k)
                func_00369820();
        }
    } else {
        func_0023AA40();
    }
}

/* 0x00369AB0, 0xFC bytes. The queue's frame: the voice started (-1: none). */
int func_00369AB0(void)
{
    int *e, r;

    func_00369620();
    if (g_0045D7AC <= g_0045D7A8)
        return -1;
    e = g_007B9560[g_0045D7A8];
    if (func_00369560() != 0) {
        func_00369750(e[0]);
        g_0045D79C = 0;
    }
    r = -1;
    if (func_00369570() == 0 && g_0045D7A0 != 0) {
        if (e[1] > 0) {
            e[1]--;
            return -1;
        }
        if (func_003696D0(e[0]) != 0) {
            r = g_0045D7A8;
            g_0045D7A4 = g_0045D7A8;
            func_00369820();
            return r;
        }
        if (g_0045D79C < 0x96) {
            g_0045D79C++;
        } else {
            func_003697C0();
            r = g_0045D7A8;
            func_00369820();
        }
    }
    return r;
}

/* 0x00369BB0, 0x80 bytes. Starts a battle set-up of kind `a` for force `b`. */
void func_00369BB0(u32 a, u32 b)
{
    int k;

    g_007B95E0 = a;
    g_007B95E4 = b;
    g_007B95EC = 0;
    g_007B95E8 = 0;
    g_007B95F0 = 0;
    g_007B95F4 = 0;
    g_007B95F8 = 0;
    for (k = 0; k < 8; k++)
        g_007B95FC[k] = -1;
}

/* 0x0036A5B0, 0x108 bytes. The force's officers able to join (kind `b`), not yet chosen. */
int func_0036A5B0(int a, int b, int *out)
{
    int f = func_00327D50(), n = 0, i, j;
    int *l = (int *)func_002F7B10();
    int c = func_00323CD0(a, f, g_007B95E4, l);

    for (i = 0; i < c; i++, l++) {
        for (j = 0; j < 8; j++) {
            if (*l == g_007B95FC[j])
                break;
        }
        if (j == 8 && b == func_002F3E30(*l))
            out[n++] = *l;
    }
    return n;
}

/* 0x0036A6C0, 0xD8 bytes. The force's officers not yet chosen. */
int func_0036A6C0(int a, int *out)
{
    int f = func_00327D50(), n = 0, i, j;
    int *l = (int *)func_002F7B10();
    int c = func_002F7D90(0, func_002F82A0, f, -1, 1, 0);

    for (i = 0; i < c; i++, l++) {
        for (j = 0; j < 8; j++) {
            if (*l == g_007B95FC[j])
                break;
        }
        if (j == 8)
            out[n++] = *l;
    }
    return n;
}

/* 0x0036A7A0, 0xD0 bytes. The battle's cost (ten times the levels / 100). */
void func_0036A7A0(void)
{
    int k;

    g_007B95F0 = 0;
    if (g_007B95E0 != 0)
        return;
    for (k = 0; k < 8; k++) {
        if ((u32)g_007B95FC[k] < 0x19F)
            g_007B95F0 += func_002F3770(g_007B95FC[k]) / 100;
    }
    g_007B95F0 *= 10;
}

/* 0x0036A870, 0x138 bytes. The officer list's answer (1 chosen, 0 cancelled). */
int func_0036A870(void)
{
    u32 v = func_0032D9C0();

    if (v == 1) {
        g_007B95FC[g_007B95E8] = func_0032E760();
        g_007B95EC = 0;
        if (func_00369C50() == 0)
            func_003A99B0(g_007B95E4, 1);
        func_0036A7A0();
    } else if (v == 0) {
        g_007B95EC = 0;
        if (func_00369C50() == 0)
            func_003A99B0(g_007B95E4, 1);
    }
    if (v < 2) {
        if ((int)g_007B95E0 < 0 || (int)g_007B95E0 > 3) {
            if (func_00369C50() != 0)
                func_00376100(func_003760C0(), func_003760E0(), 0x159);
        } else {
            func_00376100(func_003760C0(), func_003760E0(), 0x159);
        }
    }
    return 2;
}

/* 0x0036B120, 0x50 bytes. */
int func_0036B120(void)
{
    int r;                      /* undefined in the other states, as in the original */

    if (g_007B95EC == 0)
        r = func_0036AA60();
    else if (g_007B95EC == 1)
        r = func_0036A870();
    return r;
}

/* 0x0036B580, 0x140 bytes. Side `s`'s count over its slots (and the other side's leader). */
char func_0036B580(int s)
{
    char c = 0;
    int i, j, o;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 9; j++) {
            if (func_00362160(s, i) != 0x252 && func_0036B940(s, i) == 0)
                c += func_0036B4D0(s, i, j);
        }
    }
    o = func_0036B8C0(s == 0);
    if (o < 8 && func_0036B940(s == 0, o) != 0) {
        for (j = 0; j < 9; j++)
            c += func_0036B4D0(s == 0, o, j);
    }
    return c;
}

/* 0x0036B720, 0x100 bytes. */
char func_0036B720(int s)
{
    char c = 0;
    int i, o;

    for (i = 0; i < 8; i++) {
        if (func_00362160(s, i) != 0x252 && func_0036B940(s, i) == 0)
            c += func_0036B6C0(s, i);
    }
    o = func_0036B8C0(s == 0);
    if (o < 8 && func_0036B940(s == 0, o) != 0)
        c += func_0036B6C0(s == 0, o);
    return c;
}

/* 0x0036BA80, 0xF4 bytes, matching. The officers fighting for side `s` (its own and the other side's
 * turncoats); their count. */
int func_0036BA80(int *out, u32 s)
{
    u32 a, k;
    int n = 0;

    for (a = 0; a < 2; a++) {
        for (k = 0; k < 8; k++) {
            if (func_0036B880(a, k) == 0)
                continue;
            if (a == s) {
                if (func_0036B940(a, k) == 0)
                    out[n++] = func_003620E0(a, k);
            } else if (func_0036B940(a, k) != 0) {
                out[n++] = func_003620E0(a, k);
            }
        }
    }
    return n;
}

/* 0x0036BC40, 0xC4 bytes. The battle's flags. */
void func_0036BC40(void)
{
    u32 v = g_007B9620;

    if (func_0036BB80(*(int *)(g_00669D60 + 0x210)) == 0)
        v |= 1;
    if (*(int *)(g_00669D60 + 0xA0) != 0 && *(u32 *)(((u8 *)func_0035DD10(0)) + 0x54) > 1000)
        v |= 2;
    if (*(int *)(g_00669D60 + 0xE8) != 0 && *(u32 *)(((u8 *)func_0035DD10(1)) + 0x54) > 1000)
        v |= 4;
    if (func_00362B60(0) != 0 && *(int *)(g_00669D60 + 0x58) == 1)
        v |= 0x10;
    g_007B9620 = v;
}

void func_0036C9A0(void);
void func_0036C530(void);

/* 0x0036D000, 0x12C bytes. Prepares the battle's set-up data. */
void func_0036D000(void)
{
    int k;

    if (func_0032E7B0() != 0 || *(int *)(g_00669D60 + 0x210) == 7)
        return;
    func_0036BC40();
    func_0036BD10();
    func_0036C200();
    if (*(int *)(g_00669D60 + 0x58) == 0) {
        for (k = 0; k < 8; k++) {
            g_007B97E8[k] = 0;
            g_007B9808[k] = 0;
        }
    }
    if ((u32)func_00362570() < 6 || (u32)func_00362570() > 0x12)
        func_0036C9A0();
    func_0036C530();
    func_0036CE50();
    func_0036CEF0();
    func_0036CFC0();
}

/* 0x0036D180, 0xA4 bytes. An unlock record for officer `o` (0x7F: none yet). */
void func_0036D180(u8 o, u8 *p)
{
    int k;

    p[0] = o;
    p[1] = 0;
    for (k = 2; k < 10; k++) {
        p[k] = 10;
        p[k + 8] = 0;
    }
    p[0x12] = func_002F5840(func_002F57F0(o));
    p[0x13] = 0;
    if (func_002F57F0(o) != 0)
        p[0] = 0x7F;
}

/* 0x0036D850, 0x118 bytes, matching. Whether the pair (`a`, `b`) is one of the special duels. */
int func_0036D850(int a, int b)
{
    if (func_0036D970(a, b, 2, 10) != 0)
        return 1;
    if (func_0036D970(a, b, 0xD, 0x17) != 0)
        return 1;
    if (func_00328270() == 1 && func_0036D970(a, b, 5, 0x12) != 0)
        return 1;
    if (func_00328270() == 3 && func_0036D970(a, b, 5, 0x1B) != 0)
        return 1;
    if (func_003282C0() == 1 && func_0036D970(a, b, 0xF, 0x80) != 0)
        return 1;
    return 0;
}
