/*
 * emp_ev_still.c - the Empire mode's still-picture event scenes: a small script of 0x20-byte
 * commands (two speakers, portraits, text lines, waits) read from an event file. Name from the
 * "emp_ev_still.c" string the code references. Written so far: parts of 0x00329D20-0x0032C040.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_EV_STILL_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The script state at 0x007B5DD0. */
typedef struct {
    int arg;                 /* +0x00 */
    int until;               /* +0x04 */
    int now;                 /* +0x08 */
    u16 *start;              /* +0x0C */
    u16 *pc;                 /* +0x10 */
    int left, right;         /* +0x14 the two speakers (0x37F: none) */
    int other;               /* +0x1C */
    int count;               /* +0x20 */
    u8 *text[2];             /* +0x24 */
    int unknown_2C[6];       /* +0x2C (+0x34: the run state) */
} EvStill;

typedef u16 *(*EvCmd)(u16 *c);

extern EvStill g_007B5DD0;
extern u8 *g_0045D6D0;                   /* (small data) the event file */
extern u8 *g_0045D6D4;                   /* (small data) the current event */
extern int g_0045D6D8, g_0045D6DC, g_0045D6E4;
extern int g_0045CFEC;                   /* (small data) the last message */
extern u8 g_00447A10[];                  /* "" */
extern char g_00447A20[];                /* "emp_ev_still.c" (the allocations' source name) */
extern EvCmd g_00414D70[14], g_00414DB0[14];
extern u8 g_00669D60[];

#define EV g_007B5DD0
#define SPEAKER(s) ((s) == 0 ? EV.left : EV.right)

u32 func_00120A40(const char *s);
int func_0032F420(int v);
void func_0032D270(int v);
u8 *func_0032C9D0(void);
u8 *func_0032C050(void);
void func_0032C8C0(void);
void func_0032CE80(void);
void func_0032CFC0(void);
void func_0017E0C0(int v, int k);
void func_0032D0E0(void);

/* 0x00329D20, 0x14 bytes. The current event's part `k`. */
u8 *func_00329D20(int k)
{
    return *(u8 **)(g_0045D6D4 + k * 8 + 4);
}

/* 0x00329D40, 0x20 bytes, matching. Its script. */
u16 *func_00329D40(void)
{
    return *(u16 **)(func_00329D20(0) + 4);
}

/* 0x00329D60, 0xC bytes, matching. */
EvStill *func_00329D60(void)
{
    return &EV;
}

/* 0x00329D70, 8 bytes, matching. */
void func_00329D70(int v)
{
    g_0045D6E4 = v;
}

/* 0x00329D80, 8 bytes, matching. */
void func_00329D80(int v)
{
    g_0045D6D8 = v;
}

/* 0x00329D90, 8 bytes, matching. */
int func_00329D90(void)
{
    return g_0045D6D8;
}

/* 0x0032A170, 0x58 bytes. */
int func_0032A170(int side, int x)
{
    return func_0032A040(SPEAKER(side), func_0032F420(x)) != 0;
}

/* 0x0032A1D0, 0x50 bytes. */
int func_0032A1D0(int side)
{
    int a = EV.left, b = EV.right;

    if (side != 0) {
        a = EV.right;
        b = EV.left;
    }
    return func_0032A040(a, b) != 0;
}

/* 0x0032A220, 0x38 bytes, matching. Text `k` of the event's second part. */
char *func_0032A220(int k)
{
    u8 *t = func_00329D20(1);

    return (char *)(t + *(int *)(t + k * 4));
}

/* 0x0032A260, 0x54 bytes, matching. Text `b` of group `a` of its third part. */
char *func_0032A260(int a, int b)
{
    u8 *t = func_00329D20(2);

    t += *(int *)(t + a * 4);
    return (char *)(t + *(int *)(t + b * 4));
}

/* 0x0032A2C0, 0x8C bytes. The voice number stored after text `s` (-1: none). */
void func_0032A2C0(char *s, int *out)
{
    *out = -1;
    if (func_00120A40(s) < 0x14A && func_00120A40(s) != 0) {
        int *p = (int *)((u32)(s + func_00120A40(s) + 4) & ~3u);

        *out = p[0] == 0 ? p[1] : p[0];
    }
}

/* 0x0032A350, 0x74 bytes. Command: a speaker by officer number. */
u16 *func_0032A350(u16 *c)
{
    if (c[2] == 0) {
        EV.left = c[1];
        func_0032C940(c[3], c[1], 0, 1, 0);
    } else {
        EV.right = c[1];
        func_0032C940(c[3], c[1], 1, 1, 0);
    }
    return c + 0x10;
}

/* 0x0032A3D0, 0x98 bytes. Command: a speaker by role. */
u16 *func_0032A3D0(u16 *c)
{
    if (c[2] == 0) {
        int v = func_0032F420(c[1]);

        EV.left = v;
        func_0032C940(c[3], v, 0, 1, 0);
    } else {
        int v = func_0032F420(c[1]);

        EV.right = v;
        func_0032C940(c[3], v, 1, 1, 0);
    }
    func_0032D270(func_0032F420(c[1]));
    return c + 0x10;
}

/* 0x0032A470, 0x74 bytes. Command: a speaker leaves. */
u16 *func_0032A470(u16 *c)
{
    if (c[1] == 0) {
        EV.left = 0x37F;
        func_0032C940(c[2], 0x37F, 0, 0, 0);
    } else {
        EV.right = 0x37F;
        func_0032C940(c[2], 0x37F, 1, 0, 0);
    }
    return c + 0x10;
}

/* 0x0032A650, 0xF0 bytes. Copies the first line of `src` (`second`: the rest after "\n");
 * whether the text had more lines (first line only). */
int func_0032A650(char *dst, char *src, int second)
{
    u32 n = func_00120A40(src), o = 0;
    int seen = 0;

    if (n != 0) {
        do {
            int nl = 0;

            if (src[0] == '\\' && src[1] == 'n') {
                if (second == 0) {
                    dst[o] = 0;
                    return 1;
                }
                seen = 1;
                nl = 1;
                src++;
            }
            if (!nl) {
                if (second == 0)
                    dst[o++] = *src;
                else if (seen)
                    dst[o++] = *src;
            }
            src++;
        } while (o < n);
    }
    dst[o] = 0;
    return 0;
}

/* 0x0032A750, 0x9C bytes, matching. Marks force `f`'s provinces on the map. */
void func_0032A750(int f)
{
    int i;

    func_003A7C10();
    for (i = 0; i < func_0030AB90(); i++) {
        if (f == func_0030AFF0(i)) {
            func_003A78E0(i, func_002F9990(func_0030AFF0(i)), 1);
            func_003A80F0(i, 1);
        }
    }
    func_003A80A0(1);
}

/* 0x0032AD20, 0x9C bytes. Command: a system message. */
u16 *func_0032AD20(u16 *c)
{
    u8 *w = func_0032C9D0(), *x = func_0032C050();

    if (g_0045D6E4 == 0) {
        func_00390760(c[1]);
        *(int *)(w + 0xC2C4) = 2;
        *(int *)(x + 0x4EC8) = 2;
        *(int *)(x + 0x4ECC) = 2;
        func_00369880(0);
        func_0023AA10(0);
        g_0045CFEC = c[1];
        func_00329DA0(c[1]);
    } else {
        func_00329D80(1);
    }
    return c + 0x10;
}

/* 0x0032ADC0, 0x9C bytes. Command: a message window. */
u16 *func_0032ADC0(u16 *c)
{
    u8 *x = func_0032C050(), *w = func_0032C9D0();

    *(int *)(w + 0xC2C4) = 2;
    *(int *)(x + 0x4EC8) = 2;
    *(int *)(x + 0x4ECC) = 2;
    if (g_0045D6E4 == 0) {
        func_00369880(0);
        func_0023AA10(0);
        func_001AE9F0(1, (const char *)(func_00390760(c[1])), 1);
        g_0045D6DC = 1;
    } else {
        func_00329D80(1);
    }
    return c + 0x10;
}

/* 0x0032B020, 0x80 bytes. Command: a speaker by special portrait (0x253 + n). */
u16 *func_0032B020(u16 *c)
{
    int v = c[1] + 0x253;

    if (c[2] == 0) {
        EV.left = v;
        func_0032C940(c[3], v, 0, 1, 0);
    } else {
        EV.right = v;
        func_0032C940(c[3], v, 1, 1, 0);
    }
    func_00372540(c[1]);
    return c + 0x10;
}

/* 0x0032B0C0, 0xAC bytes. Resets the script (to the event's start). */
void func_0032B0C0(int arg)
{
    EV.until = 0;
    EV.now = 0;
    EV.arg = arg;
    EV.start = func_00329D40();
    EV.pc = EV.start;
    EV.left = 0x37F;
    EV.right = 0x37F;
    EV.other = 0x37F;
    EV.count = 0;
    EV.text[0] = g_00447A10;
    EV.text[1] = g_00447A10;
    EV.unknown_2C[0] = 0;
    EV.unknown_2C[1] = 0;
    EV.unknown_2C[2] = 0;
    EV.unknown_2C[3] = 0;
    EV.unknown_2C[4] = 0;
    EV.unknown_2C[5] = 0;
}

/* 0x0032B170, 0xC bytes, matching. */
int func_0032B170(void)
{
    return EV.now;
}

/* 0x0032B180, 0x34 bytes, matching. Which text slot is current. */
int func_0032B180(void)
{
    return func_0032B170() % 2;
}

/* 0x0032B1F0, 0x50 bytes. Command: a speaker by role, quietly. */
u16 *func_0032B1F0(u16 *c)
{
    if (c[2] == 0)
        EV.left = func_0032F420(c[1]);
    else
        EV.right = func_0032F420(c[1]);
    return c + 0x10;
}

/* 0x0032B270, 0x50 bytes, matching. Command: a voice of text `c[1]`. */
u16 *func_0032B270(u16 *c)
{
    int v;

    func_0032A2C0(func_0032A220(c[1]), &v);
    if (v != -1)
        func_00369890(v, c[6]);
    return c + 0x10;
}

/* 0x0032B2C0, 0x78 bytes. Command: a voice of the speaker's own text. */
u16 *func_0032B2C0(u16 *c)
{
    int v;

    func_0032A2C0(func_0032A260(func_0032F7D0(SPEAKER(c[2])), c[1]), &v);
    if (v != -1)
        func_00369890(v, c[6]);
    return c + 0x10;
}

/* 0x0032B340, 0xA8 bytes. Command: a voice picked by the speakers' standing. */
u16 *func_0032B340(u16 *c)
{
    char *s = func_0032A220(c[1]);
    int v;

    if (c[5] == 0) {
        if (func_0032A1D0(c[2]) != 0)
            s = func_0032A220(c[7]);
    } else {
        if (func_0032A170(c[2], c[6]) != 0)
            s = func_0032A220(c[7]);
    }
    func_0032A2C0(s, &v);
    if (v != -1)
        func_00369890(v, c[9]);
    return c + 0x10;
}

/* 0x0032B5B0, 0x88 bytes. Runs the whole script at once, then resets it. */
void func_0032B5B0(void)
{
    EvCmd fn[14];
    int k;

    for (k = 0; k < 14; k++)
        fn[k] = g_00414D70[k];
    while (*EV.pc != 0xFFFF)
        EV.pc = fn[*EV.pc](EV.pc);
    func_0032B0C0(EV.arg);
}

/* 0x0032B640, 0x20 bytes, matching. */
void func_0032B640(void)
{
    func_0032B0C0(EV.arg);
}

/* 0x0032B660, 0xC4 bytes. Runs the script up to the current step (run state 2 at its end). */
void func_0032B660(void)
{
    EvCmd fn[14];
    int k;

    for (k = 0; k < 14; k++)
        fn[k] = g_00414DB0[k];
    while (EV.until <= EV.now) {
        if (*EV.pc == 0xFFFF) {
            EV.unknown_2C[2] = 2;
            break;
        }
        EV.pc = fn[*EV.pc](EV.pc);
    }
}

/* 0x0032B730, 0x30 bytes. Selects event `k` of the file. */
void func_0032B730(int k)
{
    g_0045D6D4 = g_0045D6D0 + *(int *)(g_0045D6D0 + k * 8 - 0xD4);
    func_0032B0C0(k);
}

/* 0x0032B760, 0x44 bytes. Frees the event file. */
void func_0032B760(void)
{
    if (g_0045D6D0 != 0) {
        func_00102EC0(g_0045D6D0);
        g_0045D6D0 = 0;
        g_0045D6D4 = 0;
    }
    func_0032C8C0();
    func_0032CE80();
    func_0032CFC0();
}

/* 0x0032B950, 0x40 bytes, matching. Starts loading the event file. */
void func_0032B950(void)
{
    g_0045D6D0 = func_001026D0(1, 0xAC, 0, 0, 0, 0, g_00447A20, 0x787);
}

/* 0x0032BAF0, 0x1C bytes, matching. */
void func_0032BAF0(void)
{
    func_0032B7B0();
}

/* 0x0032BB10, 0x1C bytes, matching. */
void func_0032BB10(void)
{
    func_0032B950();
}

/* 0x0032BB30, 0x34 bytes, matching. Leaves: the music volume back, the file freed. */
void func_0032BB30(void)
{
    func_0023AA40();
    func_0017E0C0(g_00669D60[0x52], 0xF);
    func_0032B760();
}

/* 0x0032BB70, 0x54 bytes. */
int func_0032BB70(void)
{
    if (EV.count == func_00369810()) {
        func_00369880(0);
        func_00369AB0();
        func_0032D0E0();
        func_0032CFF0();
    }
    return 0;
}

/* 0x0032BBD0, 0x5C bytes. Steps the script once. */
void func_0032BBD0(void)
{
    EvStill *e = func_00329D60();

    func_00329D80(0);
    func_00369880(1);
    func_0032B660();
    e->now++;
    if (e->unknown_2C[2] == 0)
        e->unknown_2C[2] = 1;
}

/* 0x0032BFF0, 0x54 bytes. Step `t` of `n` from `a` to `b`. */
int func_0032BFF0(int a, int b, int t, int n)
{
    int over;

    if (n < 2) {
        n = 1;
        over = t > 1;
    } else {
        over = n < t;
    }
    if (over)
        t = n;
    if (t < 0)
        t = 0;
    return a + t * (b - a) / n;
}

/* The portrait and text windows (parts of 0x0032C050-0x0032D9BC): two portraits (state at
 * +0x4EC8: 0 opening, 1 shown, 2 closing, 3 closed; 8 frames each way) and one text window. */

extern u8 *g_0045D6EC;                   /* (small data) the portraits */
extern u8 *g_0045D6F0;                   /* (small data) the text window */
extern u8 *g_0045D6F4;                   /* (small data) */
extern int g_007B5E28, g_007B5E30, g_007B5E34, g_007B5E38;
extern u8 g_007B5E4A, g_007B5E4B;

void func_00120928(u8 *to, const u8 *from);
void func_0032B640(void);
void func_0032CEB0(void);

#define PI(p, o, k) (*(int *)((p) + (o) + (k) * 4))
#define TW(o) (*(int *)(g_0045D6F0 + (o)))

/* 0x0032C050, 8 bytes, matching. */
u8 *func_0032C050(void)
{
    return g_0045D6EC;
}

/* 0x0032C060, 0x18 bytes, matching. */
void func_0032C060(int v)
{
    if (g_0045D6EC != 0)
        *(int *)(g_0045D6EC + 0x4EE0) = v;
}

/* 0x0032C7F0, 0x94 bytes. Steps the two portraits' open and close. */
void func_0032C7F0(void)
{
    int k;

    if (g_0045D6EC == 0)
        return;
    for (k = 0; k < 2; k++) {
        u8 *p = g_0045D6EC;

        if (PI(p, 0x4EC8, k) == 3)
            continue;
        PI(p, 0x4EC0, k)++;
        if (PI(p, 0x4EC8, k) == 0) {
            if (PI(p, 0x4EC0, k) > 7)
                PI(p, 0x4EC8, k) = 1;
        } else if (PI(p, 0x4EC8, k) == 2 && PI(p, 0x4EC0, k) > 7) {
            PI(p, 0x4EC8, k) = 3;
            PI(p, 0x4ED0, k) = 0x37F;
        }
    }
}

/* 0x0032C890, 0x30 bytes, matching. Closes both portraits. */
void func_0032C890(void)
{
    u8 *p = g_0045D6EC;

    *(int *)(p + 0x4EC0) = 0;
    *(int *)(p + 0x4ED8) = 0;
    *(int *)(p + 0x4EC8) = 3;
    *(int *)(p + 0x4ED0) = 0x37F;
    *(int *)(p + 0x4EC4) = 0;
    *(int *)(p + 0x4EDC) = 0;
    *(int *)(p + 0x4ECC) = 3;
    *(int *)(p + 0x4ED4) = 0x37F;
}

/* 0x0032C8C0, 0x2C bytes, matching. */
void func_0032C8C0(void)
{
    if (g_0045D6EC != 0) {
        func_00102EC0(g_0045D6EC);
        g_0045D6EC = 0;
    }
}

/* 0x0032C8F0, 0x30 bytes, matching. */
void func_0032C8F0(void)
{
    if (g_0045D6EC == 0)
        g_0045D6EC = func_00102DB0(0x10, 0x4EF0);
}

/* 0x0032C920, 0x14 bytes. Portrait `k`'s state. */
int func_0032C920(int k)
{
    return PI(g_0045D6EC, 0x4EC8, k);
}

/* 0x0032C9D0, 8 bytes, matching. */
u8 *func_0032C9D0(void)
{
    return g_0045D6F0;
}

/* 0x0032CD60, 0xB0 bytes. Steps the text window's open and close. */
void func_0032CD60(void)
{
    if (TW(0xC2C4) == 3)
        return;
    TW(0xC2C0)++;
    if (TW(0xC2C4) == 0) {
        if (TW(0xC2C0) > 7)
            TW(0xC2C4) = 1;
    } else if (TW(0xC2C4) == 2 && TW(0xC2C0) > 7) {
        TW(0xC2C4) = 3;
    }
}

/* 0x0032CE10, 0x70 bytes. Resets the text window (closed). */
void func_0032CE10(void)
{
    func_0032CEB0();
    TW(0xC2C0) = 0;
    TW(0xC2C4) = 3;
    TW(0xC2C8) = 0x37F;
    g_0045D6F0[0xC2CC] = 0;
    TW(0xC418) = 0;
    TW(0xC41C) = 0;
}

/* 0x0032CE80, 0x2C bytes, matching. */
void func_0032CE80(void)
{
    if (g_0045D6F0 != 0) {
        func_00102EC0(g_0045D6F0);
        g_0045D6F0 = 0;
    }
}

/* 0x0032CEB0, 0x30 bytes, matching. */
void func_0032CEB0(void)
{
    if (g_0045D6F0 == 0)
        g_0045D6F0 = func_00102DB0(0x10, 0xC420);
}

/* 0x0032CEE0, 0x14 bytes, matching. */
int func_0032CEE0(void)
{
    return TW(0xC2C4);
}

/* 0x0032CF00, 0x28 bytes, matching. Sets the speaker name shown. */
void func_0032CF00(const u8 *s)
{
    func_00120928(g_0045D6F0 + 0xC2CC, s);
}

/* 0x0032CFC0, 0x2C bytes, matching. */
void func_0032CFC0(void)
{
    if (g_0045D6F4 != 0) {
        func_00102EC0(g_0045D6F4);
        g_0045D6F4 = 0;
    }
}

/* 0x0032D0E0, 0x24 bytes, matching. */
void func_0032D0E0(void)
{
    func_0032C7F0();
    func_0032CD60();
}

/* 0x0032D110, 0x3C bytes, matching. Opens the windows (all closed, the script reset). */
void func_0032D110(void)
{
    func_0032C8F0();
    func_0032CEB0();
    func_0032B640();
    func_0032C890();
    func_0032CE10();
}

/* 0x0032D150, 0x24 bytes, matching. */
void func_0032D150(void)
{
    func_0032C8C0();
    func_0032CE80();
}

/* 0x0032D2F0, 0xC bytes. */
void func_0032D2F0(int v)
{
    g_007B5E28 = v;
}

/* 0x0032D8B0, 0x48 bytes. The list's first mode (with a sound). */
void func_0032D8B0(void)
{
    func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
    g_007B5E28 = 1;
    g_007B5E30 = 0;
    g_007B5E34 = 0;
}

/* 0x0032D900, 0x48 bytes. Its second mode. */
void func_0032D900(void)
{
    func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
    g_007B5E28 = 0;
    g_007B5E30 = 1;
    g_007B5E34 = 0;
}

/* 0x0032D950, 0x68 bytes. Its third mode. */
void func_0032D950(void)
{
    func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
    g_007B5E28 = 0;
    g_007B5E30 = 0;
    g_007B5E34 = 1;
    g_007B5E38 = 1;
    g_007B5E4A = 0;
    g_007B5E4B = 0;
    func_0028D5D0(0xC);
}
