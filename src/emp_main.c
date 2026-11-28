/*
 * emp_main.c - the Empire mode's turn menus and command budget (0x002FC220-..., before
 * emp_cq_main.c; the original file's name is unknown). Written so far: from 0x002FC220.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The turn state (0x007A2D60): +0 the page shown (0-9 commands, 0xA-0xE reports, 0xF leaving),
 * then 0x197 words of choices (-1: none), then the pages' own states.
 */

#define SW2E_FILE_EMP_MAIN_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern int g_007A2D60[0x1B2];            /* the turn state (+0 the page) */
extern u8 g_007A2CF0[], g_007A3AF0[];
extern u32 g_007A33F4[0xD];              /* each page's state block */
#ifdef SW2E_PC
extern ps2ptr g_0043C5F0_a;           /* a caption */
#define g_0043C5F0 ((const char *)PS2_PTR(g_0043C5F0_a))
#define g_0043C5F0_SET(v) (g_0043C5F0_a = PS2_ADDR(v))
#else
extern const char *g_0043C5F0;
#define g_0043C5F0_a (*(ps2ptr *)&g_0043C5F0)
#define g_0043C5F0_SET(v) (g_0043C5F0 = (v))
#endif
extern int g_007A3AD0[8], g_007A3AB0[8]; /* two short lists of officers */
extern int g_0045D688, g_0045D68C, g_0045D690, g_0045D69C, g_0045D6A0;   /* (small data) */

int func_0030AB90(void);
int func_0030C1C0(int f, int g);
int func_0030AD80(int f);
int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort, int p5);

/* 0x002FC220, 0x8C bytes. The sum of func_0030AD80 over the forces func_0030C1C0 lists for
 * `g`. */
int func_002FC220(int g)
{
    int s = 0, f = 0;

    while (f < func_0030AB90()) {
        int h = func_0030C1C0(f, g);

        if (h >= func_0030AB90())
            return s;
        s += func_0030AD80(h);
        f = h + 1;
    }
    return s;
}

/* 0x002FC2B0, 0xC bytes, matching. */
u8 *func_002FC2B0(void)
{
    return g_007A2CF0;
}

/* 0x002FC2C0, 0xC bytes, matching. The turn state. */
int *func_002FC2C0(void)
{
    return g_007A2D60;
}

void func_002FC560(void);
u32 func_002FCD60(void); void func_002FCD20(u32 *s);
u32 func_00307230(void); void func_003071E0(u32 s);

/* 0x002FC2D0, 0x1C4 bytes. Resets the turn: page 0, the choices cleared, each page's state
 * block found and reset, then the command list. */
void func_002FC2D0(void)
{
    int k;

    g_007A2D60[0] = 0;
    g_007A2D60[1] = 0;
    g_007A2D60[2] = 0;
    g_007A2D60[0x1B1] = 0;
    for (k = 0; k < 0x19F; k++)
        g_007A2D60[3 + k] = -1;
    g_007A33F4[0] = PS2_ADDR(func_0031D6C0());
    func_0031D830((void *)PS2_PTR(g_007A33F4[0]));
    g_007A33F4[1] = PS2_ADDR(func_00329890());
    func_003298A0((int *)PS2_PTR(g_007A33F4[1]));
    g_007A33F4[2] = PS2_ADDR(func_00335050());
    func_00335060((void *)PS2_PTR(g_007A33F4[2]));
    g_007A33F4[3] = PS2_ADDR(func_00335EE0());
    func_00335EF0((int *)PS2_PTR(g_007A33F4[3]));
    g_007A33F4[5] = PS2_ADDR(func_00323F00());
    func_00323E60((unsigned int *)PS2_PTR(g_007A33F4[5]));
    g_007A33F4[4] = PS2_ADDR(func_0039BA50());
    func_0039BA60((int *)PS2_PTR(g_007A33F4[4]));
    g_007A33F4[6] = PS2_ADDR(func_0039BC10());
    func_0039BC20((unsigned int *)PS2_PTR(g_007A33F4[6]));
    g_007A33F4[10] = PS2_ADDR(func_003C0070());
    func_003C0080((int *)PS2_PTR(g_007A33F4[10]));
    g_007A33F4[7] = func_002FCD60();
    func_002FCD20((u32 *)PS2_PTR(g_007A33F4[7]));
    g_007A33F4[8] = func_00307230();
    func_003071E0(g_007A33F4[8]);
    g_007A33F4[9] = PS2_ADDR(func_00326490());
    func_003263F0((unsigned int *)PS2_PTR(g_007A33F4[9]));
    g_007A33F4[11] = PS2_ADDR(func_00320F00());
    func_00320EE0((int *)PS2_PTR(g_007A33F4[11]));
    func_002FC560();
}

/* 0x002FC4A0, 0x54 bytes. Whether one of events 0x3B-0x59 is on. */
int func_002FC4A0(void)
{
    int k;

    for (k = 0x3B; k < 0x5A; k++) {
        if (func_00328190(k) != 0)
            return 1;
    }
    return 0;
}

/* 0x002FC500, 0x54 bytes. Whether one of events 0x5A-0x62 is on. */
int func_002FC500(void)
{
    int k;

    for (k = 0x5A; k < 99; k++) {
        if (func_00328190(k) != 0)
            return 1;
    }
    return 0;
}

/* 0x002FC560, 0xC8 bytes. The command menu: nine entries, only the first three and, by the
 * events, entries 4 and 5 outside the first turn. */
void func_002FC560(void)
{
    int *st = func_002FC2C0();
    u32 on[9];
    int k;

    func_00388200(0, st[1]);
    for (k = 0; k < 9; k++)
        on[k] = 1;
    if (func_003280E0() == 0) {
        on[0] = 0;
        on[1] = 0;
        on[2] = 0;
        on[3] = 0;
        on[4] = 0;
    }
    if (func_002FC4A0() == 0)
        on[3] = 0;
    if (func_002FC500() == 0)
        on[4] = 0;
    func_003882C0((int *)(on));
    if (st[0x1B1] == 0)
        func_00376100(4, -1, -1);
}

void func_002FC660(void);

/* 0x002FC630, 0x24 bytes, matching. */
void func_002FC630(void)
{
    func_002FC2D0();
    func_002FC660();
}

/* 0x002FC660, 0x90 bytes. The report menu: seven entries, three of them by what happened. */
void func_002FC660(void)
{
    u32 on[7];
    int k;

    func_00388200(3, 0);
    for (k = 0; k < 7; k++)
        on[k] = 1;
    if (func_003237C0() == 0)
        on[1] = 0;
    if (func_00323730(0) == 0)
        on[2] = 0;
    if (func_00323730(1) == 0)
        on[3] = 0;
    func_003882C0((int *)(on));
    func_00376100(5, -1, -1);
}

void func_0039E380(void);

/* 0x002FC6F0, 0xE0 bytes. Draws the current command page (page 0 also the caption, and as in
 * the original it falls through into page 1). */
void func_002FC6F0(void)
{
    switch (g_007A2D60[0]) {
    case 0:
        func_0031DA90();
        func_001A7DC0(g_0043C5F0, 0x80, 1);
    case 1:
        func_00335DA0();
        break;
    case 2:
        func_00329C20();
        break;
    case 3:
        func_0031EA10();
        break;
    case 4:
        func_003202B0();
        break;
    case 5:
        func_003209D0();
        break;
    case 6:
        func_0039BB40();
        break;
    case 7:
        func_0039E380();
        break;
    case 8:
        func_003C0190();
        break;
    }
}

/* 0x002FC7D0, 0x30 bytes, matching. Leaves the commands for the reports. */
int func_002FC7D0(void)
{
    func_003762C0();
    func_002FC630();
    func_003A9010(1);
    return 0;
}

/* 0x002FC800, 0x58 bytes, matching. The "end the turn?" question: yes leaves, no goes back. */
int func_002FC800(void)
{
    int r = 5, a = func_00375B90();

    if (a == 2)
        r = func_002FC7D0();
    else if (a == 3)
        g_007A2D60[0] = 0;
    return r;
}

int func_0039D4A0(void);

/* 0x002FC860, 0x138 bytes. Steps the current command page; page 9 ends the turn (asking
 * first when commands are left). */
int func_002FC860(void)
{
    int r = 5;

    switch (g_007A2D60[0]) {
    case 0: r = func_0031DDB0(); break;
    case 1: r = func_00335DE0(); break;
    case 2: r = func_00329C70(); break;
    case 3: r = func_0031FF80(); break;
    case 4: r = func_003206F0(); break;
    case 5: r = func_00320E40(); break;
    case 6: r = func_0039BB80(); break;
    case 7: r = func_0039D4A0(); break;
    case 8: r = func_003C01D0(); break;
    case 9:
        if (func_003280E0() == 0) {
            r = func_002FC7D0();
        } else {
            func_00375140(0x100, 200, 1, PS2_ADDR(func_00390760(0x111)));
            g_007A2D60[0] = 0xF;
        }
        break;
    case 0xF:
        r = func_002FC800();
        break;
    }
    return r;
}

void func_0039E470(void);

/* 0x002FC9A0, 0x118 bytes. Draws the current report page. */
void func_002FC9A0(void)
{
    int pg = g_007A2D60[0];

    if (pg == 0xE || pg == 9)
        return;
    if (pg == 8)
        func_003C0250();
    else if (pg == 7)
        func_0039E470();
    else if (pg == 0xD)
        func_003383B0();
    else if (pg == 0xC)
        func_00338250();
    else if (pg == 0xB)
        func_003380F0();
    else if (pg == 10)
        func_00337ED0();
    else if (pg == 0) {
        func_00337D30();
        if (func_003F1160(1) == 0)
            func_001A7DC0(g_0043C5F0, 0x80, 1);
    }
}

/* 0x002FCAC0, 0x30 bytes, matching. Leaves the reports for the commands. */
int func_002FCAC0(void)
{
    func_003762C0();
    func_002FC2D0();
    func_003A9010(1);
    return 0;
}

/* 0x002FCAF0, 0x58 bytes, matching. The "leave the reports?" question. */
int func_002FCAF0(void)
{
    int r = 5, a = func_00375B90();

    if (a == 2)
        r = func_002FCAC0();
    else if (a == 3)
        g_007A2D60[0] = 0;
    return r;
}

int func_0039E500(void);

/* 0x002FCB50, 0x1C8 bytes. Steps the current report page. */
int func_002FCB50(void)
{
    int r = 5, pg = g_007A2D60[0];

    if (pg == 0xE) {
        r = func_002FCAF0();
    } else if (pg == 9) {
        if (func_003237C0() == 0) {
            r = func_002FCAC0();
        } else {
            func_00375140(0x100, 200, 1, PS2_ADDR(func_00390760(0xA9)));
            g_007A2D60[0] = 0xE;
        }
    } else if (pg == 8) {
        r = func_003C0290();
    } else if (pg == 7) {
        r = func_0039E500();
    } else if (pg == 0xD) {
        r = func_003382F0();
    } else if (pg == 0xC) {
        r = func_00338190();
    } else if (pg == 0xB) {
        r = func_00338030();
    } else if (pg == 10) {
        r = func_00337F30();
    } else if (pg == 0) {
        if (func_00323730(0) == 0) {
            if (func_00323730(1) != 0)
                func_003F1070(5);
        } else if (func_003F1070(4) == 0 && func_00323730(1) != 0) {
            func_003F1070(5);
        }
        r = func_00337E00();
        if (r == 0)
            func_003A9170();
    }
    return r;
}

void func_002FD490(void);

/* 0x002FCD20, 0x40 bytes, matching. Resets a page state block. */
void func_002FCD20(u32 *s)
{
    s[0] = 0;
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;
    s[4] = 0;
    s[5] = (u32)PS2_ADDR(func_002FC2B0());
    func_002FD490();
}

/* 0x002FCD60, 0xC bytes, matching. */
u32 func_002FCD60(void)
{
    return (u32)PS2_ADDR(g_007A3AF0);
}

/* 0x002FCD70, 0xC8 bytes, matching. Sorts officer list `l` of `n` by soldiers, most first. */
void func_002FCD70(u32 *l, int n)
{
    int x, y;

    for (x = 0; x < n; x++) {
        int s = func_002F3770(l[x]);

        for (y = x + 1; y < n; y++) {
            int t = func_002F3770(l[y]);

            if (s < t) {
                u32 u = l[x];

                l[x] = l[y];
                l[y] = u;
                s = t;
            }
        }
    }
}

/* 0x002FCE40, 0xD4 bytes. Force `f`'s upkeep: a tenth of the soldiers of its eight largest
 * units, rounded down to tens. */
int func_002FCE40(int f)
{
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0), s = 0, k;
    u32 *l = func_002F7B10();

    func_002FCD70(l, n);
    if (n > 7)
        n = 8;
    for (k = 0; k < n; k++)
        s += func_002F3770(l[k]);
    return s / 100 * 10;
}

/* 0x002FCF20, 0x8C bytes. The player's spendable gold this turn: its gold less the upkeep
 * and 500 (at least 0). */
void func_002FCF20(void)
{
    int f = func_00327D50(), g = func_002F9190(f), u = func_002FCE40(f);
    int m = u < g ? g : u;

    if (m - u - 500 < 1)
        g_0045D688 = 0;
    else
        g_0045D688 = (u < g ? g - u : 0) - 500;
}

/* 0x002FCFB0, 0xC bytes, matching. Empties the two short lists. */
void func_002FCFB0(void)
{
    g_0045D68C = 0;
    g_0045D690 = 0;
}

/* 0x002FCFC0, 0x34 bytes, matching. Adds officer `i` to the first list (at most 8). */
void func_002FCFC0(int i)
{
    if (g_0045D68C < 8)
        g_007A3AD0[g_0045D68C++] = i;
}

/* 0x002FD000, 0x44 bytes, matching. Whether officer `i` is in the first list. */
int func_002FD000(int i)
{
    int k;

    for (k = 0; k < g_0045D68C; k++) {
        if (i == g_007A3AD0[k])
            return 1;
    }
    return 0;
}

/* 0x002FD050, 0x8C bytes. Whether more than two officers of the first list share officer `i`'s
 * func_00313B30. */
int func_002FD050(int i)
{
    int a = func_00313B30(i), n = 0, k;

    for (k = 0; k < g_0045D68C; k++) {
        if (a == func_00313B30(g_007A3AD0[k]))
            n++;
    }
    return n > 2;
}

/* 0x002FD0E0, 0x34 bytes, matching. Adds officer `i` to the second list. */
void func_002FD0E0(int i)
{
    if (g_0045D690 < 8)
        g_007A3AB0[g_0045D690++] = i;
}

/* 0x002FD120, 0x44 bytes, matching. Whether officer `i` is in the second list. */
int func_002FD120(int i)
{
    int k;

    for (k = 0; k < g_0045D690; k++) {
        if (i == g_007A3AB0[k])
            return 1;
    }
    return 0;
}

/* 0x002FD170, 0x10 bytes, matching. No command cost and no command chosen. */
void func_002FD170(void)
{
    g_0045D69C = 0;
    g_0045D6A0 = 100;
}

/* 0x002FD180, 0x48 bytes, matching. Command `c` (for `a`) is chosen: its cost for the player. */
void func_002FD180(int c, int a)
{
    g_0045D6A0 = c;
    g_0045D69C = func_00313FC0(c, a, func_00327D50());
}

/* 0x002FD1D0, 0xB0 bytes. Whether force `f` can pay for command `c` (`a`): the computer's
 * forces on the first two turns always, else from its gold; the player within this turn's
 * budget. */
int func_002FD1D0(int f, int c, int a)
{
    if (func_002FB2A0(f) == 0) {
        if (func_00327C40() < 2)
            return 1;
        return func_00313FC0(c, a, f) <= func_002F9190(f);
    }
    return g_0045D69C + func_00313FC0(c, a, f) <= g_0045D688;
}

/* 0x002FD280, 0x84 bytes. Whether force `f` may give command `c` (the player cannot give two
 * commands of 0x3B-0x59 past the third use). */
int func_002FD280(int f, int c)
{
    if (func_002FB2A0(f) == 0)
        return 1;
    if (g_0045D6A0 < 0x3B || g_0045D6A0 > 0x59 || c < 0x3B || c > 0x59)
        return 1;
    return func_00328570() < 4;
}

extern int g_00446500[4][2];             /* pairs of commands that cannot follow each other */
extern int g_0045D6A4, g_0045D6A8;       /* (small data) two command counts */

void func_0030B540(int f);
void func_0030B330(void);
int func_0030B2F0(int f);
int func_0030AFF0(int f);
int func_0030C7F0(int f, int k);
int func_0030AC50(int k);
int func_0030CB50(int pct);
int func_0011B740(int v);
int func_0030C6E0(int *out, int f, int n);

/* Whether `f` is a force in play. */
#define IS_FORCE(f) ((f) >= 0 && (f) < func_0030AB90())

/* 0x002FD310, 0xA8 bytes. Whether the player may give command `c` after the one chosen (not
 * one of four forbidden pairs). */
int func_002FD310(int f, int c)
{
    int k;

    if (func_002FB2A0(f) == 0 || g_0045D6A0 == 100)
        return 1;
    for (k = 0; k < 4; k++) {
        if (g_0045D6A0 == g_00446500[k][0] && c == g_00446500[k][1])
            return 0;
        if (g_0045D6A0 == g_00446500[k][1] && c == g_00446500[k][0])
            return 0;
    }
    return 1;
}

/* 0x002FD3C0, 0x6C bytes. Whether command `c` is of the same group as the one chosen. */
int func_002FD3C0(int c)
{
    if ((u32)g_0045D6A0 < 100 && func_00313CB0(g_0045D6A0) == func_00313CB0(c))
        return 1;
    return 0;
}

/* 0x002FD430, 0x2C bytes. The count of commands 0x2B-0x2F (0 for others). */
int func_002FD430(int c)
{
    if (c < 0x2B || c > 0x2F)
        return 0;
    return g_0045D6A8;
}

/* 0x002FD460, 0x2C bytes. The count of commands 0x34-0x3A. */
int func_002FD460(int c)
{
    if (c < 0x34 || c > 0x3A)
        return 0;
    return g_0045D6A4;
}

/* 0x002FD490, 0x2C bytes, matching. Resets the turn's command bookkeeping. */
void func_002FD490(void)
{
    func_002FCFB0();
    func_002FD170();
    g_0045D6A8 = 0;
    g_0045D6A4 = 0;
}

/* 0x002FD4C0, 0xC0 bytes. The bordering forces of force `f` that belong to no region (into
 * `out`); returns how many. */
int func_002FD4C0(int f, int *out)
{
    int n = 0, g;

    func_0030B540(func_002FB2D0(f));
    for (g = 0; g < 0x19; g++) {
        if (func_0030B2F0(g) != 0 && !IS_FORCE(func_0030AFF0(g))) {
            *out++ = g;
            n++;
        }
    }
    func_0030B330();
    return n;
}

/* 0x002FD580, 0x1C bytes, matching. */
int func_002FD580(int f)
{
    int tmp[28];

    return func_002FD4C0(f, tmp);
}

/* 0x002FD5A0, 0xBC bytes. Splits force `f`'s eight traits into those it has (`yes`, count in
 * `ny`) and those it lacks (`no`, `nn`). */
void func_002FD5A0(int f, int *yes, int *no, int *ny, int *nn)
{
    int k;

    *nn = 0;
    *ny = 0;
    for (k = 0; k < 8; k++) {
        if (func_0030C7F0(f, k) == 0)
            no[(*nn)++] = k;
        else
            yes[(*ny)++] = k;
    }
}

/* 0x002FD660, 0x80 bytes. The other forces in play (into `out`); returns how many. */
int func_002FD660(int f, int *out)
{
    int g, n = 0;

    for (g = 0; g < 0x19; g++) {
        if (func_002F8CB0(g) != 0 && f != g) {
            *out++ = g;
            n++;
        }
    }
    return n;
}

/* 0x002FD6E0, 0x50 bytes. Whether force `f` can attack force `g` (no relation, a border). */
int func_002FD6E0(int f, int g)
{
    if (func_002FAFA0(f, g) != 0)
        return 0;
    return func_002FB500(f, g) != 0;
}

/* 0x002FD730, 0x90 bytes. The forces `f` can attack (into `out`); returns how many. */
int func_002FD730(int f, int *out)
{
    int g, n = 0;

    for (g = 0; g < 0x19; g++) {
        if (func_002F8CB0(g) != 0 && f != g && func_002FD6E0(f, g) != 0) {
            *out++ = g;
            n++;
        }
    }
    return n;
}

/* 0x002FD7C0, 0xEC bytes. The forces `f` can attack that hold a region of kind `kind`. */
int func_002FD7C0(int f, int kind, int *out)
{
    int g, n = 0, r[28];

    for (g = 0; g <= 0x18; g++) {
        if (func_002F8CB0(g) != 0 && f != g && func_002FD6E0(f, g) != 0) {
            int m = func_002FB320(g, r), k;

            for (k = 0; k < m; k++) {
                if (kind == func_0030AC50(k)) {
                    *out++ = g;
                    n++;
                    break;
                }
            }
        }
    }
    return n;
}

/* 0x002FD8B0, 0x13C bytes. Of forces `l` (`n`), the one with the most regions, then the
 * lowest +0x75, then a named leader, then at random (0x19 for none). */
int func_002FD8B0(int *l, int n)
{
    int best = 0x19, most = 0x19, k;

    for (k = 0; k < n; k++, l++) {
        int m = func_002FB3B0(*l);

        if (IS_FORCE(best) && most > m)
            continue;
        if (IS_FORCE(best) && m == most) {
            int a = func_002FA490(best), b = func_002FA490(*l);

            if (b < a) {
                best = *l;
            } else if (a == b) {
                int la = func_002F8F20(best) < 0x1C, lb = func_002F8F20(*l) > 0x1C;

                if (lb < la || (la == lb && func_0030CB50(0x32) != 0))
                    best = *l;
            }
        } else {
            best = *l;
            most = m;
        }
    }
    return best;
}

/* 0x002FD9F0, 0x1A8 bytes. Of forces `l` (`n`), the one closest in size to force `f`, then the
 * larger, then the closest in +0x75, then the lower +0x75, then at random. */
int func_002FD9F0(int f, int *l, int n)
{
    int best = 0x19, gap = 0, mine = func_002FB3B0(f), my75 = func_002FA490(f), k;

    for (k = 0; k < n; k++, l++) {
        int d = func_0011B740(mine - func_002FB3B0(*l));

        if (IS_FORCE(best) && gap > d)
            continue;
        if (IS_FORCE(best) && d == gap) {
            int a = func_002FB3B0(best), b = func_002FB3B0(*l);

            if (a < b) {
                best = *l;
            } else if (a == b) {
                int x = func_002FA490(best), y = func_002FA490(*l);
                int dx = func_0011B740(my75 - x), dy = func_0011B740(my75 - y);

                if (dy < dx || (dx == dy && (y < x || (x == y && func_0030CB50(0x32) != 0))))
                    best = *l;
            }
        } else {
            best = *l;
        }
        gap = d;
    }
    return best;
}

/* 0x002FDBA0, 0x104 bytes. Of forces `l` (`n`), the one with the fewest active officers, then
 * the most regions, then at random. */
int func_002FDBA0(int *l, int n)
{
    int best = 0x19, low = 0, k;

    for (k = 0; k < n; k++, l++) {
        int m = func_002FB430(*l);

        if (!IS_FORCE(best) || m < low) {
            best = *l;
            low = m;
        } else if (m == low) {
            int a = func_002FB3B0(best), b = func_002FB3B0(*l);

            if (a < b || (a == b && func_0030CB50(0x32) != 0))
                best = *l;
        }
    }
    return best;
}

/* 0x002FDCB0, 0xE0 bytes. Of forces `l`, those `f` can attack with less than half its
 * regions: the best by func_002FD8B0 (0x19 for none). */
int func_002FDCB0(int f, int *l, int n)
{
    int c[28], m = 0, mine = func_002FB3B0(f), k;

    for (k = 0; k < n; k++, l++) {
        if (func_002FD6E0(f, *l) != 0 && func_002FB3B0(*l) * 2 < mine)
            c[m++] = *l;
    }
    return m == 0 ? 0x19 : func_002FD8B0(c, m);
}

/* 0x002FDD90, 0xE4 bytes. Of forces `l`, those `f` can attack within two regions of its
 * size: the best by func_002FD9F0. */
int func_002FDD90(int f, int *l, int n)
{
    int c[28], m = 0, mine = func_002FB3B0(f), k;

    for (k = 0; k < n; k++, l++) {
        if (func_002FD6E0(f, *l) != 0 && func_0011B740(mine - func_002FB3B0(*l)) < 3)
            c[m++] = *l;
    }
    return m == 0 ? 0x19 : func_002FD9F0(f, c, m);
}

/* 0x002FDE80, 0xBC bytes. Whether one of force `g`'s eight neighbours is free or attackable by
 * force `f`. */
int func_002FDE80(int f, int g)
{
    int l[28], n = func_0030C6E0(l, g, 8), k;

    for (k = 0; k < n; k++) {
        int r = func_0030AFF0(l[k]);

        if (!IS_FORCE(r) || func_002FD6E0(f, r) != 0)
            return 1;
    }
    return 0;
}

/* 0x002FDF40, 0x34 bytes, matching. Force `f`'s plan becomes 3 (no target). */
void func_002FDF40(int f)
{
    func_002F9E10(f, 3);
    func_002F9F40(f, 0xFF);
}

extern int g_00446520[][4];              /* per region kind: the traits wanted in order */

int func_0030C7A0(int a, int b);
int func_0030CB00(int n);
int func_0030B090(int f);
int func_0030ACE0(int f);
int func_0030C440(int a, int f);
int func_0030C9C0(int r);

/* 0x002FDF80, 0x2B4 bytes. A computer force picks its next trait to gain: a missing one that
 * goes with those it has, else one of its regions' kinds, else at random; force plans above 4
 * stop, and in the early years the forces of regions 1 and 14 hold back. */
void func_002FDF80(int f)
{
    int have[10], lack[8], reg[28], nh, nl, pick = 8, k, j;

    if (func_002F9EA0(f) > 4)
        func_002FDF40(f);
    if (func_00327C00() > 5 && func_002F9EA0(f) != 2 && func_0030C7F0(f, func_002FA060(f)) == 0) {
        func_002FD5A0(f, have, lack, &nh, &nl);
        if (nh < 3) {
            for (k = 0; k < nl; k++) {
                for (j = 0; j < nh; j++) {
                    if (func_0030C7A0(lack[k], have[j]) != 0)
                        break;
                }
                if (j != nh && (pick == 8 || func_0030CB50(0x32) != 0))
                    pick = lack[k];
            }
            if (pick >= 8) {
                int n = func_002FB320(f, reg);

                for (k = 0; k < n; k++) {
                    int t = func_0030AC50(reg[k]);

                    for (j = 0; j < nl; j++) {
                        if (t == lack[j] && (pick == 8 || func_0030CB50(0x32) != 0))
                            pick = lack[j];
                    }
                }
                if (pick >= 8)
                    pick = lack[func_0030CB00(nl)];
            }
            func_002F9F40(f, pick);
        }
    }
    if (func_002F9EA0(f) == 4) {
        if (func_00327C00() < 6) {
            if (func_00327C00() == 3 && f == func_0030AFF0(1))
                func_002FDF40(f);
        } else if (f == func_0030AFF0(0xE)) {
            func_002FDF40(f);
        }
    }
}

/* 0x002FE240, 0xA4 bytes. The officers of list `l` (`n`): their average soldiers in percent of
 * their maximum. */
int func_002FE240(u32 *l, int n)
{
    int s = 0, k;

    if (n == 0)
        return 0;
    for (k = 0; k < n; k++)
        s += func_002F3770(l[k]) * 100 / func_002F38F0(l[k]);
    return s / n;
}

/* 0x002FE2F0, 0x1B0 bytes. Whether computer force `f` is ready to attack: its leader's region's
 * officers at 80% or more, the others' at 60% or more, three or more officers per region, and
 * its regions' forces more than 60% full. */
int func_002FE2F0(int f)
{
    int home = func_002FB2D0(f), reg[28], nr, n0, n = 0, k, s;
    u32 *l;

    n0 = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, home, 0, 1, 0);
    l = func_002F7B10();
    if (func_002FE240(l, n0) < 0x50)
        return 0;
    nr = func_002FB320(f, reg);
    for (k = 0; k < nr; k++) {
        if (reg[k] != home)
            n += func_002F7D90(n, (int (*)(u32, int, int))func_002F7EC0, reg[k], 0, 1, 0);
    }
    if (n != 0 && func_002FE240(l, n) <= 0x3B)
        return 0;
    if (nr != 0 && (n0 + n) / nr <= 2)
        return 0;
    for (s = 0, k = 0; k < nr; k++)
        s += func_0030B090(reg[k]) * 100 / func_0030ACE0(reg[k]);
    return s > 0x3B;
}

/* 0x002FE4A0, 0x164 bytes. A plan of kind 1 for force `f`: against the weaker of regions 3 and
 * 4's forces (by size, +0x75, func_0030C9C0, then at random), or region 1. */
int func_002FE4A0(int f)
{
    int t;

    if (func_0030C440(1, f) != 0) {
        func_002FA0D0(f, 1);
        func_002FA220(f, 1);
        return 1;
    }
    func_002FA0D0(f, 1);
    {
        int a = func_0030AFF0(3), b = func_0030AFF0(4);
        int sa = func_002FB3B0(a), sb = func_002FB3B0(b);

        if (sa < sb) {
            t = 3;
        } else if (sb < sa) {
            t = 4;
        } else {
            sa = func_002FA490(a);
            sb = func_002FA490(b);
            if (sa < sb) {
                t = 3;
            } else if (sb < sa) {
                t = 4;
            } else {
                int ca = func_0030C9C0(3), cb = func_0030C9C0(4);

                if (ca == 0 && cb != 0)
                    t = 3;
                else if (ca == 0 || cb != 0)
                    t = func_0030CB00(2) + 3;
                else
                    t = 4;
            }
        }
    }
    func_002FA220(f, t);
    return 1;
}

/* 0x002FE610, 0xB0 bytes. A plan of kind 2 for force `f`: the first trait of its home's region
 * kind it lacks (4 when it has them all). */
int func_002FE610(int f)
{
    int *w = g_00446520[func_0030AC50(func_002FB2D0(f))], t = 4, k;

    for (k = 0; k < 4; k++) {
        t = w[k];
        if (t == 8) {
            t = 4;
            break;
        }
        if (func_0030C7F0(f, t) == 0)
            break;
    }
    func_002FA0D0(f, 2);
    func_002FA220(f, t);
    return 1;
}

/* 0x002FE6C0, 0x16C bytes. Force `f`'s plan when it cannot attack: by its kind and the year
 * (kind 4: early regions, later traits; kind 3 waits; kinds 1-2 a trait; kind 0 its home). */
void func_002FE6C0(int f)
{
    int done = 0, k = func_002F9EA0(f);

    if (k == 4) {
        if (func_00327C00() == 3)
            done = func_002FE4A0(f);
        else if (func_00327C00() > 5)
            done = func_002FE610(f);
    } else if (k == 3) {
        func_002FA0D0(f, 7);
        func_002FA220(f, 0xFF);
        done = 1;
    } else if (k == 2 || k == 1) {
        int t = func_002FA060(f);

        if (func_0030C7F0(f, t) == 0) {
            func_002FA0D0(f, 2);
            func_002FA220(f, t);
            done = 1;
        }
    } else if (k == 0) {
        func_002FA0D0(f, 0);
        func_002FA220(f, func_002FB2D0(f));
        done = 1;
    }
    if (done == 0) {
        func_002FA0D0(f, 0);
        func_002FA220(f, func_002FB2D0(f));
    }
}

/* Plans to take one of the free bordering forces `l` (`n`). */
static inline void take_free(int f, int *l, int n)
{
    func_002FA0D0(f, 1);
    func_002FA220(f, l[func_0030CB00(n)]);
}

/* 0x002FE830, 0x468 bytes. Force `f`'s plan when it is ready to attack, by its kind: free
 * bordering forces first; kind 1 / 2 the traits they want; others a weaker or a similar
 * neighbour (5 or 6), else waiting (7). */
void func_002FE830(int f)
{
    int free[26], others[28], have[8], lack[8], nh, nl, n, k, t, o, no;

    if (func_002FE2F0(f) == 0)
        return;
    k = func_002F9EA0(f);
    if (k == 0) {
        if ((n = func_002FD4C0(f, free)) == 0) {
            func_002FA0D0(f, 0);
            func_002FA220(f, func_002FB2D0(f));
        } else {
            take_free(f, free, n);
        }
    } else if (k == 1) {
        t = func_002FA060(f);
        if (func_0030C7F0(f, t) == 0) {
            func_002FA0D0(f, 2);
            func_002FA220(f, t);
        } else if ((n = func_002FD4C0(f, free)) == 0) {
            func_002FA0D0(f, 3);
            func_002FA220(f, t);
        } else {
            take_free(f, free, n);
        }
    } else if (k == 2) {
        t = func_002FA060(f);
        o = func_0030AC50(func_002FB2D0(f));
        if (func_0030C7F0(f, t) == 0) {
            func_002FA0D0(f, 2);
            func_002FA220(f, t);
        } else if (func_0030C7F0(f, o) == 0) {
            func_002FA0D0(f, 2);
            func_002FA220(f, o);
        } else if ((n = func_002FD4C0(f, free)) == 0) {
            func_002FA0D0(f, 3);
            func_002FA220(f, t);
        } else {
            take_free(f, free, n);
        }
    } else if (k != 3) {
        o = func_0030AC50(func_002FB2D0(f));
        func_002FD5A0(f, have, lack, &nh, &nl);
        no = func_002FD660(f, others);
        if ((n = func_002FD4C0(f, free)) != 0) {
            take_free(f, free, n);
        } else if (func_0030C7F0(f, o) == 0) {
            func_002FA0D0(f, 2);
            func_002FA220(f, o);
        } else if (nh < 4) {
            int g = func_002FDCB0(f, others, no);

            if (no + 1 > 9 && IS_FORCE(g)) {
                func_002FA0D0(f, 4);
                func_002FA220(f, g);
            } else if (IS_FORCE(g = func_002FDD90(f, others, no))) {
                func_002FA0D0(f, 5);
                func_002FA220(f, g);
            }
        } else if (IS_FORCE(t = func_002FDD90(f, others, no))) {
            func_002FA0D0(f, 6);
            func_002FA220(f, t);
        } else {
            func_002FA0D0(f, 7);
            func_002FA220(f, 0xFF);
        }
    }
}

/* 0x002FECA0, 0x94 bytes. Plan 0 kept while its target is the force's own region, else
 * replanned. */
void func_002FECA0(int f)
{
    int t = func_002FA390(f);

    if (IS_FORCE(t) && f == func_0030AFF0(t)) {
        func_002FA0D0(f, 0);
        func_002FA220(f, func_002FB2D0(f));
    } else {
        func_002FE6C0(f);
    }
}

/* 0x002FED40, 0x60 bytes. Plan 2 done once the trait is had. */
void func_002FED40(int f)
{
    int t = func_002FA390(f);

    if (t < 8 && func_0030C7F0(f, t) != 0)
        func_002FA0D0(f, 3);
    else
        func_002FE6C0(f);
}

/* 0x002FEDA0, 0x98 bytes. Plan 1 kept while its target force can still be reached. */
void func_002FEDA0(int f)
{
    int t = func_002FA390(f);

    if (func_002FE2F0(f) == 0)
        return;
    if (t < 8 && func_002FDE80(f, t) != 0) {
        func_002FA0D0(f, 2);
        func_002FA220(f, t);
    } else {
        func_002FE6C0(f);
    }
}

extern void (*g_004147C0[7])(int f);     /* the plan steppers by plan kind */
extern int g_004147E0[];                 /* command base values */
extern int g_00414800[][2], g_00414830[][2];   /* by officer kind group: two values each */

int func_0030AD80(int f);
int func_0030AE80(int f);
int func_0030AAD0(int g);
int func_002FD000(int i);
int func_002FD3C0(int c);
int func_002FD050(int i);
int func_002FD1D0(int f, int c, int a);

/* Keeps force `f`'s plan target `pick` of its home region kind's candidates (replans when
 * none). */
static inline void keep_target(int f, int (*pick)(int *, int), int (*pick2)(int, int *, int))
{
    int l[28], t = func_002FA390(f), n;

    if (IS_FORCE(t) && func_002F8CB0(t) != 0)
        return;
    n = func_002FD7C0(f, func_0030AC50(func_002FB2D0(f)), l);
    t = pick != 0 ? pick(l, n) : pick2(f, l, n);
    if (IS_FORCE(t))
        func_002FA220(f, t);
    else
        func_002FE6C0(f);
}

/* 0x002FEE40, 0xD4 bytes. Plan 4: a new target when the old one is gone (the largest). */
void func_002FEE40(int f)
{
    keep_target(f, func_002FD8B0, 0);
}

/* 0x002FEF20, 0xD8 bytes. Plan 5: the same, the most similar. */
void func_002FEF20(int f)
{
    keep_target(f, 0, func_002FD9F0);
}

/* 0x002FF000, 0xD4 bytes. Plan 6: the same, the fewest officers. */
void func_002FF000(int f)
{
    keep_target(f, func_002FDBA0, 0);
}

/* 0x002FF0E0, 0x4C bytes, matching. Steps force `f`'s plan. */
void func_002FF0E0(int f)
{
    int k = func_002FA160(f);

    if (k < 7)
        g_004147C0[k](f);
}

/* 0x002FF130, 0x7C bytes. Officer `i`'s kind's row (0-5). */
int func_002FF130(u32 i)
{
    switch (func_002F2EA0(i)) {
    case 0: case 1: case 2: return 0;
    case 3: case 4: case 5: return 1;
    case 6: case 7: case 8: return 2;
    case 9: case 10: case 11: return 3;
    case 12: return 4;
    case 13: return 5;
    }
    return 6;
}

/* 0x002FF1B0, 0x74 bytes. Officer `i`'s kind's column (0-4). */
int func_002FF1B0(u32 i)
{
    switch (func_002F2EA0(i)) {
    case 0: case 3: case 6: case 9: return 1;
    case 1: case 4: case 7: case 10: return 0;
    case 2: case 5: case 8: case 11: return 2;
    case 12: return 3;
    case 13: return 4;
    }
    return 5;
}

/* 0x002FF230, 0xF8 bytes. How much officer `i` wants command `c`: its base plus its kind's
 * values (the second pair for commands of one sort). */
int func_002FF230(int c, u32 i)
{
    int r = func_002FF130(i), col = func_002FF1B0(i), v = g_004147E0[func_00313BF0(c)];

    if (func_00313F40(c) == 0) {
        if (func_00313F80(c) != 0)
            v = v + g_00414800[r][1] + g_00414830[col][1];
        else
            v = v + g_00414800[r][0] + g_00414830[col][0];
    }
    return v;
}

/* 0x002FF330, 0x110 bytes. Sorts commands `c` by their values `v` (`n`), highest first, ties at
 * random. */
void func_002FF330(int *c, int *v, int n)
{
    int x, y;

    for (x = 0; x < n; x++) {
        int a = v[x];

        for (y = x + 1; y < n; y++) {
            if (a < v[y] || (a == v[y] && func_0030CB50(0x32) != 0)) {
                int t = c[x];

                c[x] = c[y];
                c[y] = t;
                a = v[y];
            }
        }
    }
}

/* 0x002FF440, 0x150 bytes. Force `f`'s region that lacks the most (more than its power / 200 +
 * 5 for kind 4); -1 for none. */
int func_002FF440(int f, int kind)
{
    int reg[28], n = func_002FB320(f, reg), best = 0x19, most = 0, k;

    for (k = 0; k < n; k++) {
        int have = func_0030AD80(reg[k]);

        if (have != func_0030AE80(reg[k])) {
            int lack = func_0030AE80(reg[k]) - have;

            if (kind != 4 || func_002FAD90(f) / 200 + 5 < lack) {
                if (!IS_FORCE(best) || most < lack) {
                    best = reg[k];
                    most = lack;
                }
            }
        }
    }
    if (!IS_FORCE(best))
        best = -1;
    return best;
}

/* 0x002FF590, 0xA8 bytes. 0 when force `f` (two regions or more) has three regions lacking,
 * else -1. */
int func_002FF590(int f)
{
    int reg[28], n = func_002FB320(f, reg), m = 0, k;

    if (n < 2)
        return -1;
    for (k = 0; k < n; k++) {
        if (func_0030AD80(reg[k]) < func_0030AE80(reg[k]))
            m++;
    }
    return m < 3 ? -1 : 0;
}

/* 0x002FF640, 0x80 bytes, matching. 0 when the player's force can pay a fifth of `a`'s cost, else -1
 * (the computer: -1). */
int func_002FF640(int f, int a)
{
    if (func_002FB2A0(f) == 0)
        return -1;
    return func_00313DB0(a, f) / 5 < func_002F9190(f) ? 0 : -1;
}

/* 0x002FF6C0, 0x44 bytes, matching. -1 for command 9 of a computer force, else 0. */
int func_002FF6C0(int f, int c)
{
    if (func_002FB2A0(f) == 0 && c == 9)
        return -1;
    return 0;
}

/* 0x002FF710, 0x274 bytes. Officer `i`'s first ten commands it may give this turn, sorted by
 * how much it wants them; the first one with a target goes into slot `k` of `out`. */
void func_002FF710(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c, j;

    for (c = 0; c < 10; c++) {
        if (func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
            && func_002FD050(c) == 0 && func_002FD1D0(f, c, 0) != 0
            && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0
            && (c != 5 || func_00327C00() == 1 || func_00328190(5) != 0)) {
            cmd[n] = c;
            val[n] = func_002FF230(c, i);
            n++;
        }
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t = -1;

        if (cmd[j] != 6 && func_002F9060(f) >= 60000)
            continue;
        switch (cmd[j]) {
        case 0: case 1: case 2: t = 0; break;
        case 3: case 4: t = func_002FF440(f, cmd[j]); break;
        case 5: t = func_002FF590(f); break;
        case 6: case 8: t = func_002FF640(f, cmd[j]); break;
        case 7: case 9: t = func_002FF6C0(f, cmd[j]); break;
        }
        if (t != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

/* 0x002FF990, 0xE0 bytes. 0 when force `f` may raise its value for command 10-12 (below grade
 * 5 and one of officers `l` (`n`) has the weapon group of that value), else -1. */
int func_002FF990(int f, int c, u32 *l, int n)
{
    int v = c == 10 ? 0 : c == 11 ? 1 : c == 12 ? 2 : 3, k;

    if (v != 3 && func_002F9480(f, v) < 5) {
        for (k = 0; k < n; k++) {
            if (v == func_0030AAD0(func_002F5890(l[k])))
                return 0;
        }
    }
    return -1;
}

int func_0030C4E0(int r, int *out);
void func_0030BBD0(int f, int a);
void func_0030B440(int f);

/* 0x002FFA70, 0xF8 bytes. How many of region `r`'s neighbours its force can attack. */
int func_002FFA70(int r)
{
    int f = func_0030AFF0(r), l[8], n, m = 0, k;

    if (!IS_FORCE(f))
        return 0;
    n = func_0030C4E0(r, l);
    for (k = 0; k < n; k++) {
        int g = func_0030AFF0(l[k]);

        if (IS_FORCE(g) && func_002FD6E0(f, g) != 0)
            m++;
    }
    return m;
}

/* 0x002FFB70, 0x1E8 bytes. Force `f`'s region that most needs troops (for command 0xF only
 * those lacking two or more): the largest lack, then the most threatened, then its home, then
 * the largest, then at random; -1 for none. */
int func_002FFB70(int f, int c)
{
    int reg[28], n = func_002FB320(f, reg), home = func_002FB2D0(f), best = 0x19, lack = 0, k;
    int thr = -1, isHome = -1, size = -1;

    for (k = 0; k < n; k++) {
        int have = func_0030B090(reg[k]), d;

        if (have == func_0030ACE0(reg[k]))
            continue;
        d = func_0030ACE0(reg[k]) - have;
        if (c == 0xF && d <= 1)
            continue;
        if (IS_FORCE(best) && d <= lack) {
            if (d == lack) {
                int t = func_002FFA70(reg[k]);

                if (thr < t) {
                    thr = t;
                    best = reg[k];
                } else if (t == thr) {
                    int h = home == reg[k];

                    if (isHome < h) {
                        isHome = h;
                        best = reg[k];
                    } else if (h == isHome) {
                        int s = func_0030ACE0(reg[k]);

                        if (size < s || (s == size && func_0030CB50(0x32) != 0)) {
                            best = reg[k];
                            size = s;
                        }
                    }
                }
            }
        } else {
            lack = d;
            best = reg[k];
        }
    }
    if (!IS_FORCE(best))
        best = -1;
    return best;
}

/* 0x002FFD60, 0xA8 bytes. 0 when force `f` (two regions or more) has three regions short of
 * troops, else -1. */
int func_002FFD60(int f)
{
    int reg[28], n = func_002FB320(f, reg), m = 0, k;

    if (n < 2)
        return -1;
    for (k = 0; k < n; k++) {
        if (func_0030B090(reg[k]) < func_0030ACE0(reg[k]))
            m++;
    }
    return m < 3 ? -1 : 0;
}

/* 0x002FFE10, 0x28 bytes. 0 when a stable slot is free, else -1. */
int func_002FFE10(void)
{
    return func_001A06D0() != 0 ? 0 : -1;
}

/* 0x002FFE40, 0xB8 bytes. A random horse of the stable below level 9 (-1 for none). */
int func_002FFE40(void)
{
    u8 st[8];
    int ok[6], n = 0, k;

    func_002CAD90(st);
    for (k = 0; k < st[4]; k++) {
        if (func_0019FBC0(st[k])[8] < 9)
            ok[n++] = k;
    }
    if (n == 0)
        return -1;
    return ok[func_0030CB00(n)];
}

/* 0x002FFF00, 0x2B0 bytes. The same as func_002FF710 for commands 10-18. */
void func_002FFF00(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c, j;

    for (c = 10; c < 0x13; c++) {
        if (func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
            && func_002FD1D0(f, c, 0) != 0 && func_002FD050(c) == 0
            && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0
            && (c != 0x12 || (g_0045D6A0 != 8 && g_0045D6A0 != 0x32 && g_0045D6A0 != 0x33))) {
            cmd[n] = c;
            val[n] = func_002FF230(c, i);
            n++;
        }
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t = -1, g, m;

        switch (cmd[j]) {
        case 10: case 11: case 12:
            t = func_002FF990(f, cmd[j], (u32 *)PS2_PTR(a), b);
            break;
        case 0xD:
            for (m = 0, g = 0; g < 3; g++) {
                if (func_002F9480(f, g) > 4)
                    m++;
            }
            if (m < 2)
                t = 0;
            break;
        case 0xE: case 0xF:
            t = func_002FFB70(f, cmd[j]);
            break;
        case 0x10:
            t = func_002FFD60(f);
            break;
        case 0x11:
            t = func_002FFE10();
            break;
        case 0x12:
            t = func_002FFE40();
            break;
        }
        if (t != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

/* 0x003001C0, 0xB0 bytes. Whether one of the forces bordering the player's home has five
 * active officers or fewer. */
int func_003001C0(void)
{
    int g, r = 0;

    func_0030BBD0(func_002FB2D0(func_00327D50()), 1);
    for (g = 0; g <= 0x18; g++) {
        if (func_0030B2F0(g) != 0
            && func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, g, 0, 1, 0) <= 5) {
            r = 1;
            break;
        }
    }
    func_0030B330();
    return r;
}

/* 0x00300270, 0x150 bytes. Whether force `f`'s neighbours lack officers of role 2 or more
 * (`a`, the first in `fa`) or of role 0-1 (`b`, the first in `fb`). */
void func_00300270(int f, int *a, int *fa, int *b, int *fb)
{
    int g;

    *b = 0;
    *a = 0;
    if (fa != 0)
        *fa = 0x19;
    if (fb != 0)
        *fb = 0x19;
    func_0030BBD0(func_002FB2D0(f), 1);
    for (g = 0; g < 0x19; g++) {
        if (func_0030B2F0(g) == 0)
            continue;
        if (*a == 0 && func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, g, 0, 1, 0) < 3) {
            *a = 1;
            if (fa != 0)
                *fa = g;
        }
        if (*b == 0 && func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, g, 0, 0, 0) < 3) {
            *b = 1;
            if (fb != 0)
                *fb = g;
        }
    }
    func_0030B330();
}

/* 0x003003C0, 0x1A0 bytes. How many officers the player's force may still take (its limit less
 * its officers), and the neighbours short of officers of each kind with how many each needs. */
int func_003003C0(int *fa, int *fb, int *na, int *nb)
{
    int f = func_00327D50(), have = func_002FB430(f), lim = func_00327E50(), g;

    if (fa != 0)
        *fa = 0x19;
    if (fb != 0)
        *fb = 0x19;
    if (na != 0)
        *na = 0;
    if (nb != 0)
        *nb = 0;
    func_0030BBD0(func_002FB2D0(f), 1);
    for (g = 0; g < 0x19; g++) {
        int m;

        if (func_0030B2F0(g) == 0)
            continue;
        m = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, g, 0, 1, 0);
        if (m < 3) {
            if (fa != 0)
                *fa = g;
            if (na != 0)
                *na += 3 - m;
        }
        m = func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, g, 0, 0, 0);
        if (m < 3) {
            if (fb != 0)
                *fb = g;
            if (nb != 0)
                *nb += 3 - m;
        }
    }
    func_0030B330();
    return lim - have;
}

/* 0x00300560, 0x20 bytes, matching. */
int func_00300560(int *fa, int *fb)
{
    return func_003003C0(fa, fb, 0, 0);
}

/* 0x00300580, 0x40 bytes, matching. 0 when region `r` has officers of rank 1, else -1. */
int func_00300580(int r)
{
    return func_002F7D90(0, (int (*)(u32, int, int))func_002F8740, r, 0, 0, 0) == 0 ? -1 : 0;
}

/* 0x003005C0, 0x40 bytes, matching. 0 when there are officers of rank 1, else -1. */
int func_003005C0(int r)
{
    return func_002F7D90(0, (int (*)(u32, int, int))func_002F8710, r, 0, 0, 0) == 0 ? -1 : 0;
}

/* 0x00300600, 0xE8 bytes. The first free officer near force `f` (named ones only when `named`,
 * others only when `other`); -1 for none. */
int func_00300600(int f, int named, int other)
{
    int n, k;
    u32 *l;

    func_0030B440(func_002FB2D0(f));
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8570, 0, 0, 0, 0);
    l = func_002F7B10();
    for (k = 0; k < n; k++) {
        if ((func_002F3F20(l[k]) != 0 ? named : other) != 0)
            break;
    }
    return k < n ? (int)func_002F7B10()[k] : -1;
}

int func_00308980(u32 i, int f);
void func_002F87D0(u32 *l, int n, int (*less)(u32, u32, int, int), int a, int b);

/* Whether officer `i` is named or created (not a generic one). */
#define SPECIAL(i) ((int)(i) < 0x1C || (int)(i) > 399)

/* 0x003006F0, 0x228 bytes. The officer of list `l` (`n`) force `f` would recruit: of the
 * computer's or free officers (named ones when `named`, others when `other`, below level 19),
 * by a random rule (most soldiers, highest level or a special one), if func_00308980 allows;
 * -1 for none. */
int func_003006F0(int f, int named, int other, u32 *l, int n)
{
    u32 best = 0x19F;
    int top = 0, rule, k;

    if (n == 0)
        return -1;
    rule = func_0030CB00(3);
    for (k = 0; k < n; k++, l++) {
        int g = func_002F4080(*l), v, lv;

        if (IS_FORCE(g) && func_002FB2A0(g) != 0)
            continue;
        if ((func_002F3F20(*l) != 0 ? named : other) == 0)
            continue;
        lv = func_002F41E0(*l);
        if (lv >= 0x13)
            continue;
        v = 0;
        if (rule == 2)
            v = func_002F3770(*l);
        else if (rule == 1)
            v = lv;
        else if (rule == 0 && SPECIAL(*l))
            v = 1;
        if (best > 0x19E || top < v || (v == top && func_0030CB50(0x32) != 0)) {
            best = *l;
            top = v;
        }
    }
    if (best < 0x19F && func_00308980(best, f) == 0)
        return best;
    return -1;
}

/* 0x00300920, 0xBC bytes. The officer force `f` would recruit among the free officers of its
 * region and its neighbours. */
int func_00300920(int f, int named, int other)
{
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8630, f, 0, 0, 0), m;

    func_0030B540(func_002FB2D0(f));
    m = func_002F7D90(n, (int (*)(u32, int, int))func_002F8480, 0, 0, 1, 0);
    func_0030B330();
    return func_003006F0(f, named, other, func_002F7B10(), n + m);
}

/* 0x003009E0, 0xA4 bytes. The same among all free officers and the other forces' officers. */
int func_003009E0(int f, int named, int other)
{
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F85E0, 0, 0, 0, 0);
    int m = func_002F7D90(n, (int (*)(u32, int, int))func_002F8430, f, 0, 0, 0);

    return func_003006F0(f, named, other, func_002F7B10(), n + m);
}

/* 0x00300A90, 0x2EC bytes. The same as func_002FF710 for the recruiting commands 0x1D-0x22
 * (the player's force only while it has room for officers or a neighbour lacks them). */
void func_00300A90(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c, j, na, nb, ok = 1;

    if (func_002FB2A0(f) != 0) {
        if (b < func_00327E50()) {
            if (func_003001C0() == 0)
                ok = 0;
        } else {
            ok = 0;
        }
    }
    for (c = 0x1D; c < 0x23; c++) {
        if (ok && func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
            && func_002FD050(c) == 0 && func_002FD1D0(f, c, 0) != 0
            && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0
            && (c != 0x22 || func_00327C00() == 2 || func_00328190(0x22) != 0)) {
            cmd[n] = c;
            val[n] = func_002FF230(c, i);
            n++;
        }
    }
    if (n == 0)
        return;
    func_00300270(f, &na, 0, &nb, 0);
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t = -1;

        switch (cmd[j]) {
        case 0x1D: t = func_00300580(f); break;
        case 0x1E: t = func_003005C0(f); break;
        case 0x1F: t = func_00300920(f, na, nb); break;
        case 0x20: t = func_003009E0(f, na, nb); break;
        case 0x21: t = func_00300600(f, na, nb); break;
        case 0x22: t = func_00300920(f, na, nb); break;
        }
        if (t != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

/* 0x00300D80, 0x168 bytes. An officer of list `l` (`n`, below level 19) by a random rule (at
 * random, highest level or a special one); -1 for none. */
int func_00300D80(u32 *l, int n)
{
    u32 best = 0x19F;
    int top = 0, rule = func_0030CB00(3), k;

    for (k = 0; k < n; k++, l++) {
        int lv = func_002F41E0(*l), v = 0;

        if (lv >= 0x13)
            continue;
        if (rule == 2)
            v = func_0030CB00(0x19F);
        else if (rule == 1)
            v = lv;
        else if (rule == 0 && SPECIAL(*l))
            v = 1;
        if (best > 0x19E || top < v || (v == top && func_0030CB50(0x32) != 0)) {
            best = *l;
            top = v;
        }
    }
    if ((int)best < 0 || (int)best > 0x19E)
        return -1;
    return best;
}

/* 0x00300EF0, 0x88 bytes. Order: special officers first, else at random. */
int func_00300EF0(int i, int j)
{
    if (SPECIAL(i) && !SPECIAL(j))
        return 1;
    if (SPECIAL(j) && !SPECIAL(i))
        return 0;
    return func_0030CB00(2);
}

/* 0x00300F80, 0x60 bytes, matching. Order: lower level first, else at random. */
int func_00300F80(u32 i, u32 j)
{
    int a = func_002F41E0(i), b = func_002F41E0(j);

    if (a < b)
        return 1;
    if (b < a)
        return 0;
    return func_0030CB00(2);
}

/* 0x00300FE0, 0x60 bytes, matching. Order: higher level first, else at random. */
int func_00300FE0(u32 i, u32 j)
{
    int a = func_002F41E0(i), b = func_002F41E0(j);

    if (b < a)
        return 1;
    if (a < b)
        return 0;
    return func_0030CB00(2);
}

/* 0x00301040, 0x248 bytes. For the training commands 0x24-0x2A: the pair of officers of list
 * `l` (`n`, two or more) to train, sorted by a random rule, when force `f` has twice the cost
 * and the trained value is below 1000; the first is returned (-1 when not) and the second goes
 * into `second`. */
int func_00301040(int f, int c, u32 *l, int n, u32 *second)
{
    int rule = func_0030CB00(3), first;

    if (n < 2)
        return -1;
    if (func_002F9190(f) <= func_00313FC0(c, 0, f) / 2)
        return -1;
    switch (c) {
    case 0x24: case 0x28:
        if (func_003297D0() >= 1000)
            return -1;
        break;
    case 0x25: case 0x29:
        if (func_00329810() >= 1000)
            return -1;
        break;
    case 0x26: case 0x2A:
        if (func_00329790() > 999)
            return -1;
        break;
    case 0x27:
        if (func_003297D0() > 999 && func_00329810() > 999 && func_00329790() > 999)
            return -1;
        break;
    }
    if (rule == 0)
        func_002F87D0(l, n, (int (*)(u32, u32, int, int))func_00300EF0, 0, 0);
    else if (rule == 1)
        func_002F87D0(l, n, (int (*)(u32, u32, int, int))func_00300F80, 0, 0);
    else
        func_002F87D0(l, n, (int (*)(u32, u32, int, int))func_00300FE0, 0, 0);
    first = l[0];
    *second = l[1];
    if (first < 0 || first >= 0x19F || *second > 0x19E)
        return -1;
    return first;
}

/* 0x00301290, 0x23C bytes. The same as func_002FF710 for commands 0x23-0x2A (training). */
void func_00301290(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c, j;
    u32 second;

    for (c = 0x23; c < 0x2B; c++) {
        if (func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
            && func_002FD050(c) == 0 && func_002FD1D0(f, c, 0) != 0
            && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0
            && (c != 0x27 || func_00327C00() == 3 || func_00328190(0x27) != 0)) {
            cmd[n] = c;
            val[n] = func_002FF230(c, i);
            n++;
        }
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t = -1;

        if (cmd[j] == 0x23)
            t = func_00300D80((u32 *)PS2_PTR(a), b);
        else if (cmd[j] >= 0x24 && cmd[j] <= 0x27)
            t = func_00301040(f, cmd[j], (u32 *)PS2_PTR(a), b, &second);
        if (t != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            out[k + 5] = second;
            return;
        }
    }
}

/* 0x003014E0, 0xD0 bytes, matching. Whether computer force `f` is at peace with the player and every
 * other computer force is not. */
int func_003014E0(int f)
{
    int l[28], p, n, k;

    if (func_002FB2A0(f) != 0)
        return 0;
    p = func_00327D50();
    if (func_002FAFA0(f, p) == 0)
        return 0;
    n = func_002FD660(f, l);
    for (k = 0; k < n; k++) {
        if (func_002FB2A0(l[k]) == 0 && func_002FAFA0(l[k], p) == 0)
            return 0;
    }
    return 1;
}

/* 0x003015B0, 0x80 bytes, matching. Whether force `f` has a relation with every other force. */
int func_003015B0(int f)
{
    int l[28], n = func_002FD660(f, l), k;

    for (k = 0; k < n; k++) {
        if (func_002FAFA0(f, l[k]) == 0)
            return 0;
    }
    return 1;
}

int func_002FD120(int i);
int func_002FC220(int g);

/* The value of force `g` by random rule `rule` (2: a leader with a low number, 1: +0x75,
 * 0: its regions). */
static inline int force_value(int g, int rule)
{
    if (rule == 2)
        return 0x19F - func_002F8F20(g);
    if (rule == 1)
        return func_002FA490(g);
    if (rule == 0)
        return func_002FB3B0(g);
    return 0;
}

/* 0x00301630, 0x358 bytes. The force computer force `f` would ally with (diplomacy): only while
 * it has no kind 2 relation and fewer than three, at least two other forces, most neighbours not
 * yet allied, from year 188 on scaled by the player's size, and two or more regions bordered;
 * then the best by a random rule among the free neighbours (not its plan's target, not the
 * second list). -1 for none. */
int func_00301630(int f)
{
    int l[28], n, m = 0, k, plan = func_002FA160(f), cpu = func_002FB2A0(f) == 0;
    int best = 0x19, top = 0, rule, tgt = 0x19, y;

    if (cpu && (u32)(plan - 1) < 2)
        return -1;
    if (func_002FB120(f) != 0 || func_002FB100(f) >= 3 || func_002FD660(f, l) < 2)
        return -1;
    n = func_002FB5A0(f, l);
    if (n == 0)
        return -1;
    for (k = 0; k < n; k++) {
        if (func_002FAFA0(f, l[k]) != 0)
            m++;
    }
    if (m * 10 / n >= 6)
        return -1;
    y = (u32)func_00327C70() < 0xBC ? 0xBC : func_00327C70();
    if ((u32)(y - func_00327C70()) < (u32)(0x19 - func_002FB3B0(func_00327D50())))
        return -1;
    if (func_002FB6D0(f) < 2 || n - m == 1)
        return -1;
    if (cpu && func_002FA210(plan) != 0)
        tgt = func_002FA390(f);
    rule = func_0030CB00(3);
    for (k = 0; k < n; k++) {
        int g = l[k], v;

        if (func_002FB120(g) != 0 || func_002FAFA0(f, g) != 0 || tgt == g || func_002FD120(g) != 0)
            continue;
        v = force_value(g, rule);
        if (!IS_FORCE(best) || top < v || (v == top && func_0030CB50(0x32) != 0)) {
            best = g;
            top = v;
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x00301990, 0x1DC bytes. The force computer force `f` (without an ally) would make its ally,
 * among the computer forces it has a relation with (when it has an attackable neighbour). */
int func_00301990(int f)
{
    int l[28], n, best = 0x19, top = 0, rule, k;

    if (IS_FORCE(func_002FA5A0(f)))
        return -1;
    if (func_002FD660(f, l) < 2 || func_002FD730(f, l) == 0)
        return -1;
    n = func_002FB040(f, l);
    rule = func_0030CB00(3);
    for (k = 0; k < n; k++) {
        int v;

        if (func_002FB2A0(l[k]) != 0)
            continue;
        v = force_value(l[k], rule);
        if (!IS_FORCE(best) || top < v || (v == top && func_0030CB50(0x32) != 0)) {
            best = l[k];
            top = v;
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x00301B70, 0x220 bytes. The small computer force (a seventh of `f`'s regions or less, a
 * neighbour without a kind 3 relation and free or tied to the player) large force `f` (eight
 * regions or more, four forces or more, one of them small) would swallow, 30% of the time. */
int func_00301B70(int f)
{
    int l[28], n = func_002FD660(f, l), mine, best = 0x19, top = 0, k;

    if (n + 1 < 4 || func_002FB120(f) != 0)
        return -1;
    for (k = 0; k < n; k++) {
        if (func_002FB3B0(l[k]) < 4)
            break;
    }
    if (k == n)
        return -1;
    mine = func_002FB3B0(f);
    if (mine < 8)
        return -1;
    for (k = 0; k < n; k++) {
        int g = l[k], s, a;

        if (func_002FB2A0(g) != 0)
            continue;
        s = func_002FB3B0(g);
        if (s * 7 >= mine || func_002FB500(f, g) == 0 || func_002FB220(g) != 0)
            continue;
        a = func_002FB1A0(g);
        if (a != 0x19 && func_002FB2A0(a) == 0)
            continue;
        if (!IS_FORCE(best) || top < s || (s == top && func_0030CB50(0x32) != 0)) {
            best = g;
            top = s;
        }
    }
    if (!IS_FORCE(best))
        return -1;
    return func_0030CB50(0x1E) != 0 ? best : -1;
}

/* 0x00301D90, 0x32C bytes. The force computer force `f` would break with: the player when only
 * tied by kind 2 and the player cannot attack; otherwise, when all its borders are tied, the
 * largest tied force it borders (by chance from its policy and sizes). -1 for none. */
int func_00301D90(int f)
{
    int l[28], p = func_00327D50(), plan, n, k, best, top, pct, pol;

    if (func_002F9C90(p, f) == 2 && func_002FD730(p, l) == 0)
        return p;
    plan = func_002FA160(f);
    if (func_002FB2A0(f) == 0) {
        if (plan == 0 || plan == 3)
            return -1;
        if (func_002F9C90(f, p) != 2)
            return -1;
    }
    n = func_002FB5A0(f, l);
    for (k = 0; k < n; k++) {
        if (func_002FAFA0(f, l[k]) == 0)
            return -1;
    }
    if (func_002FB2A0(f) == 0 && func_002FB3B0(f) <= func_002FB3B0(p)
        && (short)func_002F95C0(f) <= (short)func_002F95C0(p)) {
        pol = (short)func_002F95C0(f);
        if (pol > 0xD || pol < 2)
            pol = 0;
        pct = (100 - pol * 7) / 2;
        if (pct < 4)
            pct = 4;
        if (func_0030CB50(pct) == 0)
            return -1;
    }
    n = func_002FB040(f, l);
    if (n == 0)
        return -1;
    best = 0x19;
    top = 0;
    for (k = 0; k < n; k++) {
        int g = l[k];

        if ((func_002F9C90(f, g) == 2 || func_002F9D50(f, g) > 1 || func_002FB500(f, g) != 0)
            && func_002FD120(g) == 0) {
            int s = func_002FB3B0(g);

            if (!IS_FORCE(best) || top < s || (s == top && func_0030CB50(0x32) != 0)) {
                best = g;
                top = s;
            }
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x003020C0, 0x230 bytes. Whether force `f` can buy a better policy (it can pay command 0x30,
 * the next policy kind is free and affordable, and for the computer a tied ally of similar
 * policy and size); returns `f` or -1. */
int func_003020C0(int f)
{
    int pol = (short)func_002F95C0(f), gold, ok[27], n = 0, g, tmp;

    if (func_002F9060(f) <= func_00313DB0(0x30, f))
        return -1;
    if ((short)func_002F9550(f) == 100)
        return -1;
    if (pol >= 0xE)
        return -1;
    gold = func_002FC220(f);
    for (g = 0; g < 0x19; g++) {
        if (func_002F8CB0(g) != 0 && g != f && g != func_00327D50() && func_002FAFA0(f, g) != 0) {
            int p2 = (short)func_002F95C0(g);

            if ((short)func_002F9690(p2 + 1, &tmp) <= func_002FC220(g) && pol - p2 < 4
                && func_002FB3B0(f) / 3 <= func_002FB3B0(g))
                ok[n++] = g;
        }
    }
    if (func_002F9730(f, func_002F9550(f), gold) == 100)
        return -1;
    if (func_002FB2A0(f) != 0)
        return -1;
    if (n == 0)
        return -1;
    if (gold < (short)func_002F9690(pol + 1, &tmp) && func_0030CB50(0x32) != 0)
        return -1;
    return f;
}

/* 0x00302300, 0x60 bytes, matching. 0 when force `f` has three times command 0x32's cost, else -1. */
int func_00302300(int f)
{
    return func_00313FC0(0x32, 0, f) / 3 < func_002F9190(f) ? 0 : -1;
}

extern int (*g_00414860[9])(int f, u32 i);   /* targets of commands 0x2B-0x33 */
extern int (*g_00414890[7])(int f);          /* targets of commands 0x34-0x3A */

int func_002FD430(int c);
int func_002FD460(int c);
int func_0030C660(int r);
int func_00308BF0(u32 i, int f);
int func_00309780(int f);

/* Whether a computer force may give diplomacy or war commands this year (early in the game
 * only); the player's force always may. */
static inline int may_plan(int player)
{
    u32 lim;

    if (player != 0)
        return 1;
    lim = func_00327C40() < 3 ? 4 : 2;
    return (u32)func_00327C70() <= lim;
}

/* 0x00302360, 0x2CC bytes. The same as func_002FF710 for the diplomacy commands 0x2B-0x33
 * (computer forces only in the early years; 0x2F not against a kind 3 relation with the player;
 * 0x2F wanted more at peace). */
void func_00302360(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), player = func_002FB2A0(f), cmd[100], val[100], n = 0, c, j;

    if (!may_plan(player))
        return;
    for (c = 0x2B; c < 0x34; c++) {
        if (func_002FD000(c) != 0 || func_002FD3C0(c) != 0 || func_002FD310(f, c) == 0
            || func_002FD050(c) != 0 || func_002FD1D0(f, c, 0) == 0 || func_002FD430(c) != 0
            || func_002FD460(c) != 0)
            continue;
        if (c == 0x2F && player == 0 && func_002F9C90(f, func_00327D50()) == 3)
            continue;
        if (func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) == 0)
            continue;
        cmd[n] = c;
        val[n] = func_002FF230(c, i);
        if (c == 0x2F) {
            if (func_003014E0(f) != 0)
                val[n] += 10;
            else if (func_003015B0(f) != 0)
                val[n] += 5;
        }
        n++;
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t;

        if ((u32)(cmd[j] - 0x2B) < 9 && (t = g_00414860[cmd[j] - 0x2B](f, i)) != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

/* 0x00302630, 0x2CC bytes. The enemy officer (of an attackable neighbour's regions near force
 * `f`'s home, the most soldiers) force `f` would try to win over, while it has no envoy yet,
 * by chance from func_00308BF0; -1 for none. */
int func_00302630(int f)
{
    int l[28], reg[28], player, plan, n, m, c, x, y, z, top = 0;
    u32 best = 0x19F, *o;

    func_002F7B10();
    if ((u32)func_002F9260(f) <= 0x19E)
        return -1;
    player = func_002FB2A0(f);
    if (player == 0) {
        plan = func_002FA160(f);
        if (plan == 0 || plan == 3)
            return -1;
    }
    n = func_002FD730(f, l);
    func_0030B540(func_002FB2D0(f));
    for (x = 0; x < n; x++) {
        if (player == 0 && func_002FB2A0(l[x]) == 0)
            continue;
        m = func_002FB320(l[x], reg);
        for (y = 0; y < m; y++) {
            if (func_0030B2F0(reg[y]) == 0)
                continue;
            c = func_002F7D90(0, (int (*)(u32, int, int))func_002F8070, reg[y], 0, 1, 0);
            o = func_002F7B10();
            for (z = 0; z < c; z++, o++) {
                int v = func_002F3770(*o);

                if (v != 0 && (best > 0x19E || top < v || (v == top && func_0030CB50(0x32) != 0))) {
                    best = *o;
                    top = v;
                }
            }
        }
    }
    func_0030B330();
    if (best < 0x19F) {
        int pct = func_00308BF0(best, f) * 0x82 / 100;

        if (pct >= 100)
            pct = 100;
        if (func_0030CB50(pct) == 0)
            return -1;
        return best;
    }
    return -1;
}

/* 0x00302900, 0x204 bytes. The weakly held region (under half its troops) of an attackable
 * neighbour that force `f` can reach: the one with the highest func_0030C660, then the force
 * with the lowest func_002FB470 value; -1 for none. */
int func_00302900(int f)
{
    int l[28], reg[28], player = func_002FB2A0(f), best = 0x19, top = 0, sz = 0, n, m, x, y;

    n = func_002FD730(f, l);
    for (x = 0; x < n; x++) {
        int s;

        if (player == 0 && func_002FB2A0(l[x]) == 0)
            continue;
        m = func_002FB320(l[x], reg);
        s = func_002FB470(l[x]);
        for (y = 0; y < m; y++) {
            int v;

            if (func_0030C440(reg[y], f) == 0)
                continue;
            if (func_0030B090(reg[y]) * 10 / func_0030ACE0(reg[y]) >= 5)
                continue;
            v = 0x19F - func_0030C660(reg[y]);
            if (!IS_FORCE(best) || v < top || (v == top && (s < sz || (s == sz && func_0030CB50(0x32) != 0)))) {
                best = reg[y];
                sz = s;
                top = v;
            }
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x00302B10, 0x134 bytes. Whether region `r` (not its force's home) holds an officer with no
 * tie to its force's leader. */
int func_00302B10(int r)
{
    int g = func_0030AFF0(r), n, k;
    u32 *o = func_002F7B10(), lead;

    if (!IS_FORCE(g) || r == func_002FB2D0(g))
        return 0;
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, r, 0, 1, 0);
    if (n == 0)
        return 0;
    lead = func_002F8F20(g);
    for (k = 0; k < n; k++, o++) {
        u32 i = *o;

        if (func_002F77A0(lead, i) == 0 && func_002F77F0(lead, i) == 0 && func_002F78C0(lead, i) == 0)
            return 1;
    }
    return 0;
}

/* 0x00302C50, 0x1D4 bytes. The region of an attackable neighbour (not its home, with an
 * officer not tied to its leader) force `f` would stir up, those it can reach first; by chance
 * (60% for the player). -1 for none. */
int func_00302C50(int f)
{
    int l[28], reg[28], player = func_002FB2A0(f), best = 0x19, n, m, x, y, pct;
    u32 top = 0;

    n = func_002FD730(f, l);
    for (x = 0; x < n; x++) {
        int home;

        if (player == 0 && func_002FB2A0(l[x]) == 0)
            continue;
        home = func_002FB2D0(l[x]);
        m = func_002FB320(l[x], reg);
        for (y = 0; y < m; y++) {
            u32 v;

            if (home == reg[y] || func_00302B10(reg[y]) == 0)
                continue;
            v = func_0030C440(reg[y], f) != 0 ? 10 : 0;
            if (!IS_FORCE(best) || top < v || (v == top && func_0030CB50(0x32) != 0)) {
                best = reg[y];
                top = v;
            }
        }
    }
    pct = player != 0 ? 0x3C : 100;
    if (!IS_FORCE(best))
        return -1;
    return func_0030CB50(pct) != 0 ? best : -1;
}

/* 0x00302E30, 0x238 bytes. The attackable neighbour force `f` would attack (no ally, three
 * officers per region, its officers at 80% of their soldiers): the one with the fewest
 * officers, then the smallest; -1 for none. */
int func_00302E30(int f)
{
    int l[28], nr, c, s = 0, mx = 0, k, n, best, a, b;
    u32 *o = func_002F7B10();

    if (IS_FORCE(func_002FA6B0(f)))
        return -1;
    nr = func_002FB3B0(f);
    c = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
    if (c / nr < 3)
        return -1;
    for (k = 0; k < c; k++, o++) {
        s += func_002F3770(*o);
        mx += func_002F38F0(*o);
    }
    if (s * 10 / mx < 8)
        return -1;
    n = func_002FD730(f, l);
    best = 0x19;
    a = 0;
    b = 0;
    for (k = 0; k < n; k++) {
        int oa = func_002FB430(l[k]), ob = func_002FB3B0(l[k]);

        if (!IS_FORCE(best) || oa < a || (oa == a && (ob < b || (ob == b && func_0030CB50(0x32) != 0)))) {
            best = l[k];
            b = ob;
            a = oa;
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x00303070, 0x48 bytes. 0 when officer `f` has no func_002FA790 link and func_00309780 allows, else
 * -1. */
int func_00303070(int f)
{
    if (func_002FA790(f) != 0)
        return -1;
    return func_00309780(f) != 0 ? 0 : -1;
}

/* 0x003030C0, 0x34C bytes. The enemy officer force `f` would recruit away (as func_00302630,
 * only in regions with an officer not tied to its leader; the player's force needs room; the
 * computer takes the first of each region's sorted list and has double chance). */
int func_003030C0(int f)
{
    int l[28], reg[28], player, plan, n, m, c, x, y, z, top = 0;
    u32 best = 0x19F, *o;

    func_002F7B10();
    if (func_002FB2A0(f) != 0 && func_002FB430(f) >= func_00327E50())
        return -1;
    player = func_002FB2A0(f);
    if (player == 0) {
        plan = func_002FA160(f);
        if (plan == 0 || plan == 3)
            return -1;
    }
    n = func_002FD730(f, l);
    func_0030B540(func_002FB2D0(f));
    for (x = 0; x < n; x++) {
        if (player == 0 && func_002FB2A0(l[x]) == 0)
            continue;
        m = func_002FB320(l[x], reg);
        for (y = 0; y < m; y++) {
            if (func_0030B2F0(reg[y]) == 0 || func_00302B10(reg[y]) == 0)
                continue;
            c = func_002F7D90(0, (int (*)(u32, int, int))func_002F8070, reg[y], 0, 1, 0);
            o = func_002F7B10();
            if (player == 0) {
                func_002F87D0(o, c, (int (*)(u32, u32, int, int))func_002F8B60, -1, -1);
                if (best == 0x19F || func_0030CB50(0x32) != 0) {
                    best = *o;
                    top = 0;
                }
                continue;
            }
            for (z = 0; z < c; z++, o++) {
                int v = func_002F3770(*o);

                if (v != 0 && (best > 0x19E || top < v || (v == top && func_0030CB50(0x32) != 0))) {
                    best = *o;
                    top = v;
                }
            }
        }
    }
    func_0030B330();
    if (best < 0x19F) {
        int pct = func_00308BF0(best, f);

        if (player == 0)
            pct <<= 1;
        pct = pct * 0x82 / 100;
        if (pct >= 100)
            pct = 100;
        if (func_0030CB50(pct) == 0)
            return -1;
        return best;
    }
    return -1;
}

/* 0x00303420, 0x284 bytes. The force (free of kind 2 relations, not tied to `f`, not its plan's
 * target, not in the second list) that is at odds with three other forces or at war with two,
 * the best by a random rule: the one force `f` would ask to join a war. -1 for none. */
int func_00303420(int f)
{
    int tgt = 0x19, best = 0x19, top = 0, rule, g, h;

    if (func_002FB2A0(f) == 0 && func_002FA210(func_002FA160(f)) != 0)
        tgt = func_002FA390(f);
    rule = func_0030CB00(3);
    for (g = 0; g < 0x19; g++) {
        int a = 0, w = 0;

        if (func_002F8CB0(g) == 0 || g == f || func_002FB120(g) != 0 || func_002FAFA0(f, g) != 0
            || tgt == g)
            continue;
        for (h = 0; h < 0x19; h++) {
            if (func_002F8CB0(h) != 0 && g != h && f != h && func_002FAFA0(f, h) == 0) {
                if (func_002F9D50(g, h) > 3)
                    a++;
                if (func_002F9C90(g, h) == 3)
                    w++;
            }
        }
        if ((a > 2 || w > 1) && func_002FD120(g) == 0) {
            int v = force_value(g, rule);

            if (!IS_FORCE(best) || top < v || (v == top && func_0030CB50(0x1E) != 0)) {
                best = g;
                top = v;
            }
        }
    }
    return IS_FORCE(best) ? best : -1;
}

/* 0x003036B0, 0x280 bytes. The same as func_00302360 for the war commands 0x34-0x3A. */
void func_003036B0(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c, j;

    if (!may_plan(func_002FB2A0(f)))
        return;
    for (c = 0x34; c < 0x3B; c++) {
        if (func_002FD000(c) != 0 || func_002FD3C0(c) != 0 || func_002FD310(f, c) == 0
            || func_002FD050(c) != 0 || func_002FD1D0(f, c, 0) == 0 || func_002FD430(c) != 0
            || func_002FD460(c) != 0 || func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) == 0)
            continue;
        cmd[n] = c;
        val[n] = func_002FF230(c, i);
        if (c == 0x2F) {
            if (func_003014E0(f) != 0)
                val[n] += 10;
            else if (func_003015B0(f) != 0)
                val[n] += 5;
        }
        n++;
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t;

        if ((u32)(cmd[j] - 0x34) < 7 && (t = g_00414890[cmd[j] - 0x34](f)) != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

extern void (*g_004148B0[12])(int *out, u32 i, int k, int a, int b);   /* command group choosers */
extern int g_004148E0[][12];             /* by officer mood: the groups to try in order (-1 end) */

int func_002FD280(int f, int c);

/* Whether force `f`'s officer `i` may give command `c` now (lists `a`, `b`). */
static inline int command_ok(int f, u32 i, int c, int a, int b)
{
    return func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
        && func_002FD050(c) == 0 && func_002FD1D0(f, c, 0) != 0 && func_002FD280(f, c) != 0
        && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0;
}

/* 0x00303930, 0x184 bytes. For the reinforcing commands 0x14-0x16: the officer of list `l`
 * (`n`) missing more than 0 / 1000 / 2000 soldiers with the fewest soldiers, then the highest
 * func_002F3DC0; -1 for none. */
int func_00303930(int c, u32 *l, int n)
{
    int need, top = 0, t2 = 0, k;
    u32 best;

    if (n == 0)
        return -1;
    need = c == 0x14 ? 0 : c == 0x15 ? 1000 : 2000;
    best = 0x19F;
    for (k = 0; k < n; k++, l++) {
        int s = func_002F3770(*l);

        if (need < func_002F38F0(*l) - s) {
            int v = func_002F3DC0(*l);

            if (best >= 0x19F || s < top || (s == top && (t2 < v || (v == t2 && func_0030CB50(0x32) != 0)))) {
                best = *l;
                t2 = v;
                top = s;
            }
        }
    }
    if ((int)best < 0 || (int)best > 0x19E)
        return -1;
    return best;
}

/* 0x00303AC0, 0x21C bytes. For commands 0x17-0x1A: 0 when enough officers of list `l` (`n`)
 * lack soldiers (0x1A: six missing over 200 and at most 80% filled overall), else -1. */
int func_00303AC0(int c, u32 *l, int n)
{
    int cnt, big = 0, many = 0, s = 0, mx = 0, k;

    if (n == 0)
        return -1;
    cnt = c == 0x19 ? 6 : 0;
    for (k = 0; k < n; k++, l++) {
        int d = func_002F38F0(*l) - func_002F3770(*l);

        s += func_002F3770(*l);
        mx += func_002F38F0(*l);
        if (c == 0x1A || c == 0x19) {
            if (c == 0x19 && d > 2000)
                big++;
            if (d > 200)
                many++;
        } else if (c == 0x18) {
            if (d < 2000 && d > 500)
                cnt++;
            if (d > 1000)
                big++;
        } else if (c == 0x17) {
            if (d < 1000 && d > 10)
                cnt++;
            if (d > 500)
                big++;
        }
    }
    if (c == 0x1A)
        return many < 6 || s * 10 / mx > 8 ? -1 : 0;
    return cnt > 5 && big >= 3 ? 0 : -1;
}

/* 0x00303CF0, 0xA0 bytes. 0 when all of the six or more officers `l` (`n`) are 90% full. */
int func_00303CF0(u32 *l, int n)
{
    int k;

    if (n < 6)
        return -1;
    for (k = 0; k < n; k++, l++) {
        if (func_002F3770(*l) * 10 / func_002F38F0(*l) < 9)
            break;
    }
    return k != n ? -1 : 0;
}

/* 0x00303D90, 0xC8 bytes. 0 when none of officers `l` (`n`) is over 70% full and six of them
 * lack more than 2000 soldiers. */
int func_00303D90(u32 *l, int n)
{
    int m = 0, k;

    for (k = 0; k < n; k++, l++) {
        int s = func_002F3770(*l), mx = func_002F38F0(*l);

        if (s * 10 / mx > 7)
            break;
        if (mx - s > 2000)
            m++;
    }
    return k == n && m >= 6 ? 0 : -1;
}

/* 0x00303E60, 0x298 bytes. The same as func_002FF710 for the troop commands 0x14-0x1C (those
 * for soldiers wanted more when the officers are under 80% full). */
void func_00303E60(int *out, u32 i, int k, int a, int b)
{
    int avg = func_002FE240((u32 *)PS2_PTR(a), b), f = func_002F4080(i), cmd[100], val[100], n = 0, c, j;

    for (c = 0x14; c < 0x1D; c++) {
        if (func_002FD000(c) == 0 && func_002FD3C0(c) == 0 && func_002FD310(f, c) != 0
            && func_002FD050(c) == 0 && func_002FD1D0(f, c, 0) != 0
            && func_00314C40(c, i, (unsigned int *)PS2_PTR(a), b) != 0
            && (c != 0x1A || func_00327C00() == 4 || func_00328190(0x1A) != 0)) {
            cmd[n] = c;
            val[n] = func_002FF230(c, i);
            if (c > 0x16 && c < 0x1B && avg < 0x50)
                val[n] += 5;
            n++;
        }
    }
    if (n == 0)
        return;
    func_002FF330(cmd, val, n);
    for (j = 0; j < n; j++) {
        int t = -1;

        switch (cmd[j]) {
        case 0x14: case 0x15: case 0x16:
            t = func_00303930(cmd[j], (u32 *)PS2_PTR(a), b);
            break;
        case 0x17: case 0x18: case 0x19: case 0x1A:
            t = func_00303AC0(cmd[j], (u32 *)PS2_PTR(a), b);
            break;
        case 0x1B:
            t = func_00303CF0((u32 *)PS2_PTR(a), b);
            break;
        case 0x1C:
            t = func_00303D90((u32 *)PS2_PTR(a), b);
            break;
        }
        if (t != -1) {
            out[k + 1] = cmd[j];
            out[k + 3] = t;
            return;
        }
    }
}

/* The player's officer's most wanted command of `first`..`last`, without a target. */
#define PLAYER_CHOICE(cond)                                                        \
    int f = func_002F4080(i), cmd[100], val[100], n = 0, c;                       \
                                                                                   \
    if (func_002FB2A0(f) == 0)                                                    \
        return;                                                                    \
    for (c = FIRST; c < LAST; c++) {                                               \
        if (!(cond) || !command_ok(f, i, c, a, b))                                 \
            continue;                                                              \
        cmd[n] = c;                                                                \
        val[n] = func_002FF230(c, i);                                              \
        n++;                                                                       \
    }                                                                              \
    if (n != 0) {                                                                  \
        func_002FF330(cmd, val, n);                                                \
        out[k + 1] = cmd[0];                                                       \
    }

/* 0x00304110, 0x18C bytes. For the player's officers: commands 0x3B-0x40. */
void func_00304110(int *out, u32 i, int k, int a, int b)
{
#define FIRST 0x3B
#define LAST 0x41
    PLAYER_CHOICE(1)
#undef FIRST
#undef LAST
}

/* 0x003042A0, 0x1B8 bytes. Commands 0x41-0x47 (0x43 not while the force holds all regions but
 * one). */
void func_003042A0(int *out, u32 i, int k, int a, int b)
{
#define FIRST 0x41
#define LAST 0x48
    PLAYER_CHOICE(c != 0x43 || func_002FB3B0(f) != func_0030AB90() - 1)
#undef FIRST
#undef LAST
}

/* 0x00304460, 0x1C4 bytes. Commands 0x48-0x4F (0x4F only in year kind 5 or when unlocked). */
void func_00304460(int *out, u32 i, int k, int a, int b)
{
#define FIRST 0x48
#define LAST 0x50
    PLAYER_CHOICE(c != 0x4F || func_00327C00() == 5 || func_00328190(0x4F) != 0)
#undef FIRST
#undef LAST
}

/* 0x00304630, 0x1BC bytes. Commands 0x50-0x59 (0x58 only in year kind 0 or when unlocked). */
void func_00304630(int *out, u32 i, int k, int a, int b)
{
#define FIRST 0x50
#define LAST 0x5A
    PLAYER_CHOICE(c != 0x58 || func_00327C00() == 0 || func_00328190(0x58) != 0)
#undef FIRST
#undef LAST
}

/* 0x003047F0, 0x18C bytes. Commands 0x5A-0x62. */
void func_003047F0(int *out, u32 i, int k, int a, int b)
{
#define FIRST 0x5A
#define LAST 99
    PLAYER_CHOICE(1)
#undef FIRST
#undef LAST
}

/* 0x00304980, 0x64 bytes, matching. 1 with `a`% chance, 2 with `b`%, else 3. */
int func_00304980(int a, int b)
{
    int r = func_0030CB00(100);

    if (r < a)
        return 1;
    if (r < a + b)
        return 2;
    return 3;
}

/* 0x003049F0, 0x88 bytes. 0 with `a`% chance, 1 with `b`%, 2 with `c`%, else 3. */
int func_003049F0(int a, int b, int c)
{
    int r = func_0030CB00(100);

    if (r < a)
        return 0;
    if (r < a + b)
        return 1;
    if (r < c + a + b)
        return 2;
    return 3;
}

/* 0x00304A80, 0x1BC bytes. Officer `i`'s mood this turn (the row of command groups it tries):
 * 4 for a waiting computer force short of officers, otherwise drawn by its kind's row. */
int func_00304A80(u32 i)
{
    int m = 2, f = func_002F4080(i);

    if (func_002FB2A0(f) == 0) {
        int plan = func_002FA160(f);

        if (plan == 0 || plan == 3) {
            if (func_002FB430(f) / func_002FB3B0(f) < 3)
                m = 4;
            else
                m = func_00304980(0x32, 0x28);
        } else {
            switch (func_002FF130(i)) {
            case 0: case 5: m = func_00304980(0x55, 5); break;
            case 1: case 4: m = func_00304980(0x3C, 0x19); break;
            case 2: m = func_00304980(0x41, 10); break;
            case 3: m = func_00304980(0x46, 0xF); break;
            }
        }
    } else {
        switch (func_002FF130(i)) {
        case 0: case 5: m = func_003049F0(0x28, 0x1E, 0x14); break;
        case 1: case 4: m = func_003049F0(10, 0x1E, 0x28); break;
        case 2: m = func_003049F0(0x14, 10, 0x1E); break;
        case 3: m = func_003049F0(0x19, 0x19, 0x19); break;
        }
    }
    return m;
}

/* 0x00304C40, 0x3C bytes. Whether force `f` is short of gold (its func_002FCE40 + 500 or less). */
int func_00304C40(int f)
{
    return func_002F9190(f) <= func_002FCE40(f) + 500;
}

/* 0x00304C80, 0x15C bytes. Officer `i`'s command into slot `k` of `out`: the command groups of
 * its mood (mood 2 when short of gold) in order until one gives a command (below 100);
 * clamped to 99. */
void func_00304C80(int *out, u32 i, int k, int a, int b)
{
    int f = func_002F4080(i), m = 2, j;

    if (func_00304C40(f) == 0)
        m = func_00304A80(i);
    if (m < 5) {
        int *g = g_004148E0[m];

        for (j = 0; j < 12; j++, g++) {
            if (*g != -1) {
                g_004148B0[*g](out, i, k, a, b);
                if ((u32)out[k + 1] < 100)
                    break;
            }
        }
    }
    if ((u32)out[k + 1] > 99)
        out[k + 1] = 99;
}

extern u32 g_007A3430[];                 /* copy of the officer list for the command choice */
extern int g_0045D694, g_0045D698;       /* (small data) the player was targeted this turn */

int func_0030C250(int f);
void func_002FD180(int c, int a);
void func_002FCFC0(int i);
void func_002FD0E0(int i);
void func_002FD170(void);

/* 0x00304DE0, 0x254 bytes. Officer `i`'s command record `out` for this turn (one command, two
 * when `two`; with two, the first one's target and the diplomacy targets are marked as used,
 * and "none" (99) becomes command 0). */
void func_00304DE0(int *out, u32 i, int two)
{
    int f, n, slots, j, c;
    u32 *l;

    func_002F7B10();
    out[1] = 100;
    out[3] = -1;
    out[5] = -1;
    out[2] = 100;
    out[4] = -1;
    out[6] = -1;
    func_002FD170();
    f = func_002F4080(i);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
    l = func_002F7B10();
    for (j = 0; j < n; j++)
        g_007A3430[j] = l[j];
    slots = two == 0 ? 1 : 2;
    out[0] = i;
    for (j = 0; j < slots; j++) {
        func_00304C80(out, i, j, (int)PS2_ADDR(g_007A3430), n);
        if (two != 0) {
            if (j == 0)
                func_002FD180(out[1], out[3]);
            func_002FCFC0(out[j + 1]);
            c = out[j + 1];
            if (c == 0x2B || c == 0x2C || c == 0x2F)
                func_002FD0E0(out[j + 3]);
        }
    }
    if (two != 0 && out[1] == 99)
        out[1] = 0;
}

/* 0x00305040, 0x164 bytes. Computer officer `i` gives its command: the record is built, the
 * player-targeting flags set, and the command run. */
int func_00305040(u32 i)
{
    int f = func_002F4080(i), player = func_002FB2A0(f), cmd[0x1A4], rec[8];

    func_00304DE0(rec, i, 0);
    if (player != 0)
        func_002FCFC0(rec[1]);
    if (rec[1] > 0x2A && rec[1] < 0x30 && func_002FB2A0(rec[3]) != 0)
        g_0045D698 = 1;
    if (rec[1] == 0x35 && func_0030C250(rec[3]) != 0)
        g_0045D694 = 1;
    if (rec[1] == 0x36 && func_0030C250(rec[3]) != 0)
        g_0045D694 = 1;
    if (rec[1] == 0x39 && rec[3] >= 0 && rec[3] < 0x19F && func_002FB2A0(func_002F4080(rec[3])) != 0)
        g_0045D694 = 1;
    func_00315510(cmd, f);
    cmd[1] = rec[1];
    cmd[2] = rec[3];
    cmd[3] = rec[5];
    func_0031BD90(cmd, 0);
    return func_0030DFA0();
}

/* 0x003051B0, 0x2C4 bytes. Marks force `f`'s regions `r` (`n`) in `mark`: 0 at the front (a
 * neighbour it can attack, or from year 3 on the player's), 1 bordering another force, 2 next to
 * those, 3 deep inside (4 for regions not its own). */
void func_003051B0(int f, int *r, int n, int *mark)
{
    int nb[8], k, j, m;

    for (k = 0; k < 0x19; k++)
        mark[k] = 4;
    for (k = 0; k < n; k++) {
        m = func_0030C4E0(r[k], nb);
        for (j = 0; j < m; j++) {
            int g = func_0030AFF0(nb[j]);

            if (IS_FORCE(g) && (func_002FD6E0(f, g) != 0 || (func_00327C40() > 2 && func_002FB2A0(g) != 0))) {
                mark[r[k]] = 0;
                break;
            }
        }
    }
    for (k = 0; k < n; k++) {
        int *p = &mark[r[k]];

        if (*p != 4)
            continue;
        m = func_0030C4E0(r[k], nb);
        for (j = 0; j < m; j++) {
            int g = func_0030AFF0(nb[j]);

            if (!IS_FORCE(g) || f != g) {
                *p = 1;
                break;
            }
        }
    }
    for (k = 0; k < n; k++) {
        int *p = &mark[r[k]];

        if (*p != 4)
            continue;
        m = func_0030C4E0(r[k], nb);
        for (j = 0; j < m; j++) {
            if (mark[nb[j]] < 2) {
                *p = 2;
                break;
            }
        }
        if (j == m)
            *p = 3;
    }
}

/* 0x00305480, 0x1A0 bytes. Moves officer `i` to region `r`; when `r` already has three officers
 * of role 2 or more, the one of them with the lowest func_002F33F0 (then the highest level)
 * goes to `i`'s old region. */
void func_00305480(u32 i, int r)
{
    int old, n, top = 0, k;
    u32 best, *o;

    func_002F4080(i);
    func_002F7B10();
    old = func_002F5CC0(i);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, r, 0, 1, 0);
    o = func_002F7B10();
    if (n < 3) {
        func_002F5BE0(i, r);
        return;
    }
    best = 0x19F;
    for (k = 0; k < n; k++, o++) {
        int v = func_002F33F0(*o);

        if (best >= 0x19F || v < top) {
            best = *o;
            top = v;
        } else if (v == top) {
            int a = func_002F41E0(best), b = func_002F41E0(*o);

            if (b < a || (b == a && func_0030CB50(0x32) != 0))
                best = *o;
        }
    }
    if (best < 0x19F) {
        func_002F5BE0(i, r);
        func_002F5BE0(best, old);
    }
}

/* 0x00305630, 0x23C bytes. A computer force whose leader sits at the front moves its leader
 * back to a neighbouring second-line region (one of its wanted traits first, then the most
 * troops, then the largest). */
void func_00305630(int f, int player, int *mark)
{
    int nb[8], home, best = 0x19, m, j;
    u32 top = 0;

    if (player != 0)
        return;
    home = func_002FB2D0(f);
    if (mark[home] >= 2)
        return;
    m = func_0030C4E0(home, nb);
    for (j = 0; j < m; j++) {
        u32 v = 0;
        int k;

        if (mark[nb[j]] != 2)
            continue;
        k = func_002F9EA0(f);
        if (func_002F9F10(k) != 0 && nb[j] == func_002FA060(f))
            v = 10;
        else if (func_002F9F20(k) != 0 && func_0030AC50(nb[j]) == func_002FA060(f))
            v = 10;
        if (!IS_FORCE(best) || top < v) {
            best = nb[j];
            top = v;
        } else if (v == top) {
            int a = func_0030B090(best), b = func_0030B090(nb[j]);

            if (a < b) {
                best = nb[j];
            } else if (a == b) {
                a = func_0030ACE0(best);
                b = func_0030ACE0(nb[j]);
                if (a < b || (a == b && func_0030CB50(0x32) != 0))
                    best = nb[j];
            }
        }
    }
    if (IS_FORCE(best))
        func_00305480(func_002F8F20(f), best);
}

/* 0x00305870, 0x78 bytes. The officers wanted in a region marked `mark` (0 front, 1 border,
 * 2 second line, 3 inside); `large` for a large force. */
static int func_00305870(int mark, int large)
{
    if (mark == 3)
        return 0;
    if (mark == 2)
        return large == 0 ? 4 : 2;
    if (mark == 1)
        return 4;
    if (mark == 0)
        return large == 0 ? 4 : 6;
    return 0;
}

/* 0x003058F0, 0x78 bytes. The same scaled by `have` / `total` officers, at most 6. */
static int func_003058F0(int mark, int large, int total, int have)
{
    int n = have * (func_00305870(mark, large) * 100 / total) / 100;

    return n > 5 ? 6 : n;
}

/* 0x00305970, 0x14C bytes. Whether officer `i` is needed in its group `l` (`n`): fewer than
 * three of kind 2 or named ones (counting generic ones past three), or for a generic officer
 * fewer than three others or generic ones. */
int func_00305970(u32 i, u32 *l, int n)
{
    int k2 = 0, oth = 0, named = 0, gen = 0, k;

    for (k = 0; k < n; k++, l++) {
        if (func_002F3E30(*l) == 2)
            k2++;
        else
            oth++;
        if (func_002F3F20(*l) == 0)
            gen++;
        else
            named++;
    }
    if (gen > 2)
        named += gen - 3;
    if (named < k2)
        k2 = named;
    if (k2 < 3)
        return 1;
    if (func_002F3F20(i) == 0) {
        if (gen < oth)
            oth = gen;
        if (oth < 3)
            return 1;
    }
    return 0;
}

/* 0x00305AC0, 0x94 bytes. Whether one of officers `o` (`m`) is needed in group `l` (`n`). */
int func_00305AC0(u32 *o, int m, u32 *l, int n)
{
    int k;

    for (k = 0; k < m; k++, o++) {
        if (func_00305970(*o, l, n) != 0)
            return 1;
    }
    return 0;
}

int func_00309130(u32 i, int f, int r, int a);

#define IS_OFFICER(i) ((int)(i) >= 0 && (int)(i) < 0x19F)

/* 0x00305B60, 0x370 bytes. Sends officers of force `f` from region `from` to region `to` (marks
 * `mark`) until `to` has the officers it wants: those `from` can spare (all but its wanted ones
 * kept, sorted first when `from` is the home or at the front), not busy and needed in group
 * `out` (`cnt`, up to six moved officers recorded there), at random. */
void func_00305B60(int f, int large, int *mark, int total, int have, u32 *out, int cnt, int to,
                   int from)
{
    u32 l[8], *o, *p, best;
    int need, keep, n, start, k, at;

    func_002F7B10();
    l[0] = 0x19F;
    l[1] = 0x19F;
    l[2] = 0x19F;
    l[3] = 0x19F;
    l[4] = 0x19F;
    l[5] = 0x19F;
    need = func_003058F0(mark[to], large, total, have);
    if (cnt >= need)
        return;
    need -= cnt;
    keep = func_003058F0(mark[from], large, total, have);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, from, 0, 1, 0);
    o = func_002F7B10();
    if (keep >= n)
        return;
    for (k = 0; k < n; k++)
        l[k] = o[k];
    if (n - keep < need)
        need = n - keep;
    start = 0;
    if (func_002FB2D0(f) == from || mark[from] < 2) {
        func_002FCD70(l, n);
        start = keep;
    }
    p = &out[cnt];
    for (; need != 0; need--) {
        best = 0x19F;
        at = 0;
        for (k = start; k < n; k++) {
            if (IS_OFFICER(l[k]) && func_002F3E70(l[k]) == 0 && func_00305970(l[k], out, cnt) != 0
                && (!IS_OFFICER(best) || func_0030CB50(0x32) != 0)) {
                best = l[k];
                at = k;
            }
        }
        if (!IS_OFFICER(best) || func_00309130(best, f, to, 0) == 0)
            return;
        if (cnt < 6) {
            cnt++;
            *p++ = best;
        }
        l[at] = 0x19F;
    }
}

/* 0x00305ED0, 0x26C bytes. The index in `r` (`n`) of force `f`'s region that most lacks the
 * officers it wants (the home first, then the front, then the fewest officers); `n` for none. */
int func_00305ED0(int f, int large, int *r, int n, int *mark, int total, int have)
{
    int home = func_002FB2D0(f), best = 0x19, low = 6, idx = n, k;
    u32 top = 0;

    for (k = 0; k < n; k++, r++) {
        int g = *r, want, c;
        int *p;
        u32 v;

        if (!IS_FORCE(g) || func_0030AFF0(g) != f)
            continue;
        p = &mark[g];
        want = func_003058F0(*p, large, total, have);
        c = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, g, 0, 1, 0);
        if (c >= want)
            continue;
        v = g == home ? 10 : 0;
        if (!IS_FORCE(best) || top < v) {
            low = c;
            top = v;
            idx = k;
            best = g;
        } else if (v == top) {
            u32 a = mark[best] == 0 ? 10 : 0, b = *p == 0 ? 10 : 0;

            if (a < b || (a == b && (c < low || (c == low && func_0030CB50(0x32) != 0)))) {
                low = c;
                idx = k;
                best = g;
            }
        }
    }
    if (!IS_FORCE(best))
        idx = n;
    return idx;
}

/* 0x00306140, 0x3D8 bytes. Force `f`'s region with officers to spare, one of them needed in
 * group `l` (`m`): inside regions first, then (large forces) second-line ones, then the most
 * officers, then the most troops; 0x19 for none. */
int func_00306140(int f, int large, int *r, int n, int *mark, int total, int have, u32 *l, int m)
{
    u32 o8[8], top = 0;
    int best = 0x19, cnt = 0, k, j;

    func_002F7B10();
    o8[0] = 0x19F;
    o8[1] = 0x19F;
    o8[2] = 0x19F;
    o8[3] = 0x19F;
    o8[4] = 0x19F;
    o8[5] = 0x19F;
    for (k = 0; k < n; k++, r++) {
        int g = *r, want, c;
        int *p;
        u32 v, *o;

        if (!IS_FORCE(g) || func_0030AFF0(g) != f)
            continue;
        p = &mark[g];
        want = func_003058F0(*p, large, total, have);
        c = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, g, 0, 1, 0);
        func_002F7B10();
        if (want >= c)
            continue;
        o = func_002F7B10();
        for (j = 0; j < c; j++)
            o8[j] = o[j];
        if (func_00305AC0(o8, c, l, m) == 0)
            continue;
        v = *p == 3 ? 10 : 0;
        if (!IS_FORCE(best) || top < v) {
            top = v;
            best = g;
            cnt = c;
        } else if (v == top) {
            u32 a = large == 0 ? 0 : mark[best] == 2 ? 10 : 0;
            u32 b = large == 0 ? 0 : *p == 2 ? 10 : 0;

            if (a < b) {
                best = g;
                cnt = c;
            } else if (a == b) {
                if (cnt < c) {
                    best = g;
                    cnt = c;
                } else if (c == cnt) {
                    int x = func_0030B090(best), y = func_0030B090(g);

                    if (x < y || (x == y && func_0030CB50(0x32) != 0))
                        best = g;
                }
            }
        }
    }
    return best;
}

#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) the random seed */

extern int g_007A3B10[];                 /* the computer turn's state block */

void func_002FD490(void);
void func_002FCFB0(void);
int func_002FD580(int f);

/* The computer turn's state block: 0 step, 1 command, 2 force index, 3 commands, 4 forces,
 * 5 force list. */
#define CPU_TURN() ((int *)PS2_PTR(func_002FC2C0()[0x1AC]))

/* 0x00306520, 0x74 bytes. The average soldiers of officers `l` (`n`). */
int func_00306520(u32 *l, int n)
{
    int s = 0, k;

    if (n == 0)
        return 0;
    for (k = 0; k < n; k++, l++)
        s += func_002F3770(*l);
    return s / n;
}

/* 0x003065A0, 0x3CC bytes. Balances the roles in force `f`'s regions: when one role group's
 * officers have more than twice the other's soldiers, a generic officer changes role (then
 * again for regions with a lopsided count of officers). */
void func_003065A0(int f)
{
    int reg[28], nr, a, b, k, x, y, j;
    u32 *o = func_002F7B10(), *o2 = o + 6;

    nr = func_002FB320(f, reg);
    for (k = 0; k < nr; k++) {
        a = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, reg[k], 0, 1, 0);
        b = func_002F7D90(6, (int (*)(u32, int, int))func_002F8110, reg[k], 0, 0, 0);
        if (b < 2)
            continue;
        for (j = 0; j < a; j++) {
            if (func_002F3F20(o[j]) == 0)
                break;
        }
        if (j == a)
            continue;
        x = func_00306520(o, a);
        y = func_00306520(o2, b);
        if (y * 2 < x) {
            func_002FCD70(o, a);
            func_002FCD70(o2, b);
            for (j = 0; j < a; j++) {
                if (func_002F3F20(o[j]) == 0)
                    break;
            }
            if (j < a) {
                func_002F3CF0(o[j], 1);
                func_002F3CF0(o2[b - 1], 2);
            }
        } else if (x * 2 < y) {
            func_002FCD70(o, a);
            func_002FCD70(o2, b);
            if (a < 3) {
                func_002F3CF0(o2[0], 2);
            } else {
                int last = a;

                for (j = 0; j < a; j++) {
                    if (func_002F3F20(o[j]) == 0)
                        last = j;
                }
                if (last < a) {
                    func_002F3CF0(o[last], 1);
                    func_002F3CF0(o2[0], 2);
                }
            }
        }
    }
    for (k = 0; k < nr; k++) {
        a = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, reg[k], 0, 1, 0);
        b = func_002F7D90(6, (int (*)(u32, int, int))func_002F8110, reg[k], 0, 0, 0);
        if (a <= 1 && b <= 1)
            continue;
        if (b * 2 < a) {
            int idx = a;

            func_002FCD70(o, a);
            for (j = 0; j < a; j++) {
                if (func_002F3F20(o[a - 1 - j]) == 0)
                    idx = a - j - 1;
            }
            if (idx < a)
                func_002F3CF0(o[idx], 1);
        } else if (a * 2 < b) {
            func_002FCD70(o2, b);
            func_002F3CF0(o2[b - 1], 2);
        }
    }
}

/* 0x00306970, 0x2FC bytes. A computer force's officer moves at the start of its turn: regions
 * marked, its leader moved back, then each region lacking officers gets them from the region
 * best able to spare them; then the roles are balanced. */
void func_00306970(int f)
{
    int plan = func_002FA160(f), reg[28], mark[28], nr, large, total, have, idx, k;
    u32 l[8];

    func_002F7B10();
    l[0] = 0x19F;
    l[1] = 0x19F;
    l[2] = 0x19F;
    l[3] = 0x19F;
    l[4] = 0x19F;
    l[5] = 0x19F;
    nr = func_002FB320(f, reg);
    if (nr < 2)
        return;
    large = plan != 0 && plan != 3;
    func_003051B0(f, reg, nr, mark);
    total = 0;
    for (k = 0; k < nr; k++)
        total += func_00305870(mark[reg[k]], large);
    if (total == 0)
        return;
    have = func_002FB430(f);
    func_00305630(f, large, mark);
    while ((idx = func_00305ED0(f, large, reg, nr, mark, total, have)) < nr) {
        int to = reg[idx], c, from;
        u32 *o;

        reg[idx] = 0x19;
        c = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, to, 0, 1, 0);
        o = func_002F7B10();
        for (k = 0; k < c; k++)
            l[k] = o[k];
        from = func_00306140(f, large, reg, nr, mark, total, have, l, c);
        if (IS_FORCE(from))
            func_00305B60(f, large, mark, total, have, l, c, to, from);
    }
    func_003065A0(f);
}

/* 0x00306C70, 0x6C bytes. Whether all forces `l` (`n`) are of kind 2 or less. */
int func_00306C70(int *l, int n)
{
    int k;

    for (k = 0; k < n; k++, l++) {
        if (func_002F9EA0(*l) > 2)
            return 0;
    }
    return 1;
}

/* 0x00306CE0, 0xF0 bytes. With few forces left, late in the game or only small kinds left, the
 * largest forces become kind 3 with no trait wanted. */
void func_00306CE0(int *l, int n)
{
    int top = 0, k;

    if (n >= 5 && (u32)func_00327C70() <= 0x95 && func_00306C70(l, n) == 0)
        return;
    for (k = 0; k < n; k++) {
        int s = func_002FB3B0(l[k]);

        if (top < s)
            top = s;
    }
    for (k = 0; k < n; k++, l++) {
        if (top == func_002FB3B0(*l)) {
            func_002F9E10(*l, 3);
            func_002F9F40(*l, 0xFF);
        }
    }
}

/* 0x00306DD0, 0x58 bytes, matching. Computer turn step 0: the forces listed. */
void func_00306DD0(void)
{
    int *p = CPU_TURN();

    p[4] = func_002FBAC0((int *)PS2_PTR(p[5]));
    p[2] = 0;
    p[3] = 0;
    p[1] = 0;
    func_00306CE0((int *)PS2_PTR(p[5]), p[4]);
    func_002FD490();
    p[0] = 1;
}

/* 0x00306E30, 0x14C bytes. Step 1: the next force's traits and plan, and how many commands it
 * gives (doubled or halved again by the difficulty), with its own random seed. */
void func_00306E30(void)
{
    u32 seed = g_7000015C;
    int *p = CPU_TURN(), g = ((int *)PS2_PTR(p[5]))[p[2]], d;

    if (!IS_FORCE(g)) {
        p[0] = 5;
        return;
    }
    if (func_002F8CB0(g) == 0) {
        p[0] = 5;
        return;
    }
    g_7000015C = (g + func_003276A0()) | 1;
    func_002FDF80(g);
    func_002FF0E0(g);
    p[3] = func_002FB9D0(g);
    d = func_00327C40();
    if (d == 4)
        p[3] <<= 1;
    else if (d == 3)
        p[3] = p[3] * 3 / 2;
    func_002FCFB0();
    g_7000015C = seed | 1;
    p[0] = 2;
}

/* 0x00306F80, 0xBC bytes. Step 2: the force's leader gives a command (step 3 once it is
 * done). */
int func_00306F80(void)
{
    int *p = CPU_TURN(), g = ((int *)PS2_PTR(p[5]))[p[2]];

    if (!IS_FORCE(g) || func_002F8CB0(g) == 0)
        p[0] = 5;
    else if (func_00305040(func_002F8F20(g)) == 0)
        p[0] = 3;
    return 5;
}

/* 0x00307040, 0x50 bytes. Step 3: the next command, or step 4. */
void func_00307040(void)
{
    int *p = CPU_TURN();

    if (++p[1] < p[3])
        p[0] = 2;
    else
        p[0] = 4;
}

/* 0x00307090, 0x88 bytes. Step 4: the force's officers move, then the next force (or the
 * end). */
int func_00307090(void)
{
    int *p = CPU_TURN(), r;

    func_00306970(((int *)PS2_PTR(p[5]))[p[2]]);
    r = func_0030DFA0();
    if (r == 0) {
        if (++p[2] < p[4])
            p[0] = 1;
        else
            p[0] = 5;
        r = 5;
    }
    return r;
}

/* 0x00307120, 0xAC bytes. Runs the computer turn; 0 once over. */
int func_00307120(void)
{
    int r = 5;

    switch (CPU_TURN()[0]) {
    case 0:
        func_00306DD0();
        return 5;
    case 1:
        func_00306E30();
        break;
    case 2:
        r = func_00306F80();
        break;
    case 3:
        func_00307040();
        break;
    case 4:
        r = func_00307090();
        break;
    case 5:
        r = 0;
        break;
    }
    return r;
}

/* 0x003071D0, 0x8 bytes, matching. */
void func_003071D0(void)
{
}

/* 0x003071E0, 0x44 bytes, matching. Resets the computer turn's state block `s`. */
void func_003071E0(u32 s)
{
    int *p = (int *)PS2_PTR(s);

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = -1;
    p[4] = 0;
    p[5] = 0;
    p[6] = (int)PS2_ADDR(func_002FC2B0());
}

/* 0x00307230, 0xC bytes, matching. The computer turn's state block. */
u32 func_00307230(void)
{
    return (u32)PS2_ADDR(g_007A3B10);
}

/* 0x00307240, 0xF0 bytes. An ally of force `f` without a relation with it (the player's force
 * first, else one at random); 0x19 for none. */
int func_00307240(int f)
{
    int l[28], n = 0, g;

    for (g = 0; g < func_0030AB90(); g++) {
        if (func_002F8CB0(g) != 0 && g != f && func_002FA6B0(g) == f && func_002FAFA0(g, f) == 0) {
            if (func_002FB2A0(g) != 0)
                return g;
            l[n++] = g;
        }
    }
    if (n == 0)
        return 0x19;
    return l[func_0030CB00(n)];
}

/* 0x00307330, 0xF4 bytes. The chance force `f` accepts a proposal: 100 with such an ally or an
 * envoy, else by its plan (30-60, 0 for others) unless func_002FD580. */
int func_00307330(int f)
{
    int g = func_00307240(f);

    if (IS_FORCE(g))
        return 100;
    if ((u32)func_002F9260(f) < 0x19F)
        return 100;
    if (func_002FD580(f) != 0)
        return 100;
    switch (func_002FA160(f)) {
    case 1: return 0x1E;
    case 2: case 5: return 0x28;
    case 4: case 6: return 0x32;
    case 7: return 0x3C;
    }
    return 0;
}

/* 0x00307430, 0x9C bytes. Whether one of the twelve event slots involves a region of the
 * player's force. */
int func_00307430(void)
{
    int a, r, k, g;

    for (k = 0; k < 12; k++) {
        if (func_00329160(k, &a, &r) != 0) {
            g = func_0030AFF0(r);
            if (IS_FORCE(g) && func_002FB2A0(g) != 0)
                return 1;
        }
    }
    return 0;
}

/* 0x003074D0, 0x78 bytes, matching. Whether one of the twelve event slots involves region `r`. */
int func_003074D0(int r)
{
    int a, b, k;

    for (k = 0; k < 12; k++) {
        if (func_00329160(k, &a, &b) != 0 && (a == r || b == r))
            return 1;
    }
    return 0;
}

/* 0x00307550, 0xBC bytes, matching. Whether region `r` is force `f`'s plan target (the region, its kind
 * or its force, by the plan kind). */
int func_00307550(int f, int r)
{
    int t = func_002FA390(f), plan = func_002FA160(f);

    if (func_002FA1D0(plan) != 0 && r == t)
        return 1;
    if (func_002FA1F0(plan) != 0 && t == func_0030AC50(r))
        return 1;
    if (func_002FA210(plan) != 0 && t == func_0030AFF0(r))
        return 1;
    return 0;
}

extern int g_004149D0[];                 /* by difficulty: the chance (in %) a raid is let through */

int func_0030B240(int r, int a);
int func_0030B3B0(int *out);
int func_0030C590(int r);
int func_0030C320(int r, int t);
void func_001204B0(char *out, const char *format, ...);   /* sprintf */

/* The computer attacks' state block: 0 step, 1 force index, 2 forces, 3 event slot, 4 and 5
 * the player's tied forces involved, 6 force list. */
#define CPU_ATTACK() ((int *)PS2_PTR(func_002FC2C0()[0x1AD]))

/* 0x00307610, 0x34C bytes. The region force `f` would attack this turn among those near its
 * home not already in an event: an unowned one, its ally's or its envoy's first, then its plan
 * target, then the weakest; not the player's ally's regions, nor tied forces'. */
int func_00307610(int f)
{
    int reg[28], ev = func_00307430(), n, ally, env, er = 0x19, best = 0x19, k;
    u32 top = 0;

    func_0030B540(func_002FB2D0(f));
    n = func_0030B3B0(reg);
    func_0030B330();
    ally = func_00307240(f);
    env = func_002F9260(f);
    if ((u32)env < 0x19F)
        er = func_002F5CC0(env);
    for (k = 0; k < n; k++) {
        int r = reg[k], pa, g;
        u32 v;

        if (func_003074D0(r) != 0 || func_0030B240(r, 3) == 2)
            continue;
        pa = func_002FA6B0(func_00327D50());
        if (pa != 0x19 && !((func_0030C250(r) == 0 || pa == f) && pa != func_0030AFF0(r)))
            continue;
        v = 0;
        g = func_0030AFF0(r);
        if (IS_FORCE(g)) {
            if ((ev != 0 && func_002FB2A0(g) != 0 && g != ally) || func_002FAFA0(f, g) != 0)
                continue;
        } else {
            v = 10000;
        }
        if (IS_FORCE(ally) && g == ally)
            v += 50000;
        if (r == er)
            v += 20000;
        if (v == 0 && func_00307550(f, r) != 0)
            v = 9000;
        if (!IS_FORCE(best) || top < v) {
            top = v;
            best = r;
        } else if (v == top) {
            int a = func_0030C590(best), b = func_0030C590(r);

            if (b < a) {
                best = r;
            } else if (b == a) {
                a = func_0030B090(best);
                b = func_0030B090(r);
                if (b < a) {
                    best = r;
                } else if (b == a) {
                    a = func_0030C660(best);
                    b = func_0030C660(r);
                    if (b < a || (b == a && func_0030CB50(0x32) != 0))
                        best = r;
                }
            }
        }
    }
    return best;
}

/* 0x00307970, 0x15C bytes. Force `f`'s region to attack region `t` from (bordering it, not in
 * an event): the highest func_0030C590, then func_0030C660. */
int func_00307970(int f, int t)
{
    int reg[28], n = func_002FB320(f, reg), best = 0x19, top = 0, k;

    for (k = 0; k < n; k++) {
        int r = reg[k], v;

        if (func_0030C320(r, t) == 0 || func_003074D0(r) != 0 || func_0030B240(r, 3) == 2)
            continue;
        v = func_0030C590(r);
        if (!IS_FORCE(best) || top < v) {
            top = v;
            best = r;
        } else if (v == top) {
            int a = func_0030C660(best), b = func_0030C660(r);

            if (a < b || (b == a && func_0030CB50(0x32) != 0))
                best = r;
        }
    }
    return best;
}

/* 0x00307AD0, 0x17C bytes. Whether force `f` may attack region `to` from region `from`: not a
 * tied force's; strong enough unless it is its ally's or its envoy's region; two officers of
 * role 2 or more in `from`. */
int func_00307AD0(int f, int from, int to)
{
    int g = func_0030AFF0(to), env = func_002F9260(f), er = 0x19;

    if ((u32)env < 0x19F)
        er = func_002F5CC0(env);
    if (IS_FORCE(g)) {
        if (func_002FAFA0(f, g) != 0)
            return 0;
        g = func_002FA6B0(g);
    }
    if (f == g || er == to) {
        if (func_0030C660(from) == 0)
            return 0;
    } else {
        if (func_0030C660(from) + 1 < func_0030C660(to))
            return 0;
        if (func_0030C590(from) < func_0030C590(to))
            return 0;
    }
    if (func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, from, 0, 1, 0) < 2)
        return 0;
    return 1;
}

/* 0x00307C50, 0x1B0 bytes. Whether force `f` starts an attack this turn (computer forces in the
 * early years only with an ally; a free event slot; by chance from func_00307330): the event is
 * set up in a slot. */
int func_00307C50(int f)
{
    int *q = CPU_ATTACK(), slot, to, from;

    if (func_002FB2A0(f) == 0 && (u32)func_00327C70() <= (u32)(func_00327C40() < 3 ? 4 : 2)
        && !IS_FORCE(func_00307240(f)))
        return 0;
    slot = func_00329220();
    if (slot >= 12)
        return 0;
    if (func_0030CB50(func_00307330(f)) == 0)
        return 0;
    to = func_00307610(f);
    if (!IS_FORCE(to))
        return 0;
    from = func_00307970(f, to);
    if (!IS_FORCE(from))
        return 0;
    if (func_00307AD0(f, from, to) == 0)
        return 0;
    func_00329090(slot, from, to);
    q[3] = slot;
    return 1;
}

/* 0x00307E00, 0x100 bytes. Raids on the player's regions by forces other than its ally are
 * cancelled by chance (by difficulty). */
void func_00307E00(void)
{
    int reg[28], p = func_00327D50(), pct = g_004149D0[func_00327C40()], n, k;

    n = func_002FB320(p, reg);
    for (k = 0; k < n; k++) {
        int e = func_00323BD0(reg[k]);

        if (IS_FORCE(e) && func_0030AFF0(e) != func_002FA6B0(p) && func_0030CB50(pct) == 0)
            func_00323840(e);
    }
}

/* 0x00307F00, 0x4C bytes, matching. Attack step 0: the forces listed. */
void func_00307F00(void)
{
    int *q = CPU_ATTACK();

    q[2] = func_002FBAC0((int *)PS2_PTR(q[6]));
    q[1] = 0;
    q[3] = -1;
    q[4] = 0;
    q[5] = 0;
    q[0] = 1;
}

/* 0x00307F50, 0x100 bytes. Step 1: the next force tries an attack (with its own random seed). */
void func_00307F50(void)
{
    u32 seed = g_7000015C;
    int *q = CPU_ATTACK(), g = ((int *)PS2_PTR(q[6]))[q[1]];

    if (!IS_FORCE(g) || func_002F8CB0(g) == 0) {
        q[0] = 2;
        return;
    }
    g_7000015C = (g + func_003276A0()) | 1;
    if (func_00307C50(g) == 0) {
        q[3] = -1;
        q[4] = 0;
        q[5] = 0;
        q[0] = 8;
    } else {
        q[0] = 3;
    }
    g_7000015C = seed | 1;
}

/* 0x00308050, 0x190 bytes. Step 3: whether the attack involves forces tied to the player
 * (attacker: step 4, defender: step 6, none: step 8). */
void func_00308050(void)
{
    int *q = CPU_ATTACK(), a, b, ga, gb, p;

    if (q[3] == -1) {
        q[0] = 8;
        return;
    }
    func_00329160(q[3], &a, &b);
    ga = func_0030AFF0(a);
    gb = func_0030AFF0(b);
    p = func_00327D50();
    if (func_003238D0(b) == 0) {
        if (IS_FORCE(ga) && func_002FAFA0(p, ga) != 0 && func_00328DE0(ga) == 0 && IS_FORCE(gb))
            q[4] = 1;
        if (IS_FORCE(gb) && func_002FAFA0(p, gb) != 0 && func_00328FA0(gb) == 0)
            q[5] = 1;
    }
    if (q[4] != 0)
        q[0] = 4;
    else if (q[5] != 0)
        q[0] = 6;
    else
        q[0] = 8;
}

/* 0x003081E0, 0xE8 bytes, matching. Step 4: the attacker tied to the player asks for help (command 0x2F
 * message); once answered "no" (2), message 0x5F with its name. */
void func_003081E0(void)
{
    int *q = CPU_ATTACK(), a, b, ga;
    char text[1032];

    func_00329160(q[3], &a, &b);
    ga = func_0030AFF0(a);
    func_0030AFF0(b);
    if (func_0030E1F0() == 0) {
        func_00328D00(ga, 1);
        func_0032EA80(3);
        func_0030E140(0x2F, func_002F8F20(ga), ga, -1);
    } else if (func_0030E1F0() == 2) {
        func_0030E100();
        func_001204B0(text, (const char *)func_00390760(0x5F), func_002F8DB0(ga));
        func_00374EE0(PS2_ADDR(text));
        q[0] = 5;
    }
}

/* 0x003082D0, 0xE4 bytes, matching. Step 6: the defender tied to the player asks for help (message 0x60
 * once answered "no"). */
void func_003082D0(void)
{
    int *q = CPU_ATTACK(), a, b, gb;
    char text[1032];

    func_00329160(q[3], &a, &b);
    func_0030AFF0(a);
    gb = func_0030AFF0(b);
    if (func_0030E1F0() == 0) {
        func_00328EC0(gb, 1);
        func_0032EA80(4);
        func_0030E140(0x2F, func_002F8F20(gb), gb, -1);
    } else if (func_0030E1F0() == 2) {
        func_0030E100();
        func_001204B0(text, (const char *)func_00390760(0x60), func_002F8DB0(gb));
        func_00374EE0(PS2_ADDR(text));
        q[0] = 7;
    }
}

/* 0x003083C0, 0x5C bytes. Step 5: once the message is closed, step 6 or 8. */
void func_003083C0(void)
{
    int *q = CPU_ATTACK();

    if (func_00375B90() == 1) {
        func_0030E4E0(0);
        q[0] = q[5] == 0 ? 8 : 6;
    }
}

/* 0x00308420, 0x44 bytes, matching. Step 7: once the message is closed, step 8. */
void func_00308420(void)
{
    int *q = CPU_ATTACK();

    if (func_00375B90() == 1) {
        func_0030E4E0(0);
        q[0] = 8;
    }
}

/* 0x00308470, 0x30 bytes, matching. Step 2: raids filtered, then the end. */
void func_00308470(void)
{
    int *q = CPU_ATTACK();

    func_00307E00();
    q[0] = 9;
}

/* 0x003084A0, 0x60 bytes. Step 8: the next force (step 1) or step 2. */
void func_003084A0(void)
{
    int *q = CPU_ATTACK();

    q[3] = -1;
    q[4] = 0;
    q[5] = 0;
    if (++q[1] < q[2])
        q[0] = 1;
    else
        q[0] = 2;
}

/* 0x00308500, 0xEC bytes. Runs the computer attacks; 0 once over. */
int func_00308500(void)
{
    int r = 5;

    switch (CPU_ATTACK()[0]) {
    case 0:
        func_00307F00();
        return 5;
    case 1: func_00307F50(); break;
    case 2: func_00308470(); break;
    case 3: func_00308050(); break;
    case 4: func_003081E0(); break;
    case 5: func_003083C0(); break;
    case 6: func_003082D0(); break;
    case 7: func_00308420(); break;
    case 8: func_003084A0(); break;
    case 9: r = 0; break;
    }
    return r;
}

/* 0x003085F0, 0x8 bytes, matching. */
void func_003085F0(void)
{
}

/* 0x00308600, 0xBC bytes. Officer `i` stops being anyone's envoy (forces, the event slots, the
 * player's). */
void func_00308600(u32 i)
{
    int g, k;

    for (g = 0; g < func_0030AB90(); g++) {
        if (func_002F8CB0(g) != 0 && func_002F9260(g) == (int)i)
            func_002F91C0(g, 0x19F);
    }
    k = func_00327B10(i);
    if (k < 4)
        func_00327A80(0x19F, k);
    if (func_00327870() == (int)i)
        func_00327830(0x19F);
}

/* Whether officers `i` and `j` are tied (func_002F77A0, func_002F78C0 or func_002F7900). */
#define TIED(i, j) (func_002F77A0(i, j) != 0 || func_002F78C0(i, j) != 0 || func_002F7900(i, j) != 0)

/* 0x003086C0, 0x1C8 bytes. Officer `i` and force `f`: 0 when tied to one of its own force's
 * officers, 100 when tied to one of `f`'s, else -1 (to be drawn). */
int func_003086C0(u32 i, int f)
{
    u32 *o = func_002F7B10();
    int g, n = 0, k;

    if (i >= 0x19F)
        return 0;
    g = func_002F4080(i);
    if (IS_FORCE(g))
        n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, g, 0, 1, 0);
    for (k = 0; k < n; k++, o++) {
        u32 x = *o;

        if (i != x && TIED(x, i))
            return 0;
    }
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
    o = func_002F7B10();
    for (k = 0; k < n; k++, o++) {
        if (TIED(*o, i))
            return 100;
    }
    return -1;
}

/* The player's fame grade for officer chances (0 none or computer, 1 for 1-9, 2 for 10-15). */
static inline int fame_grade(int f)
{
    int m = func_002FB2A0(f) == 0 ? 0 : func_00327E90(), k = 0;

    if (m < 1 || m > 9) {
        if (m > 9 && m < 0x10)
            k = 2;
    } else {
        k = 1;
    }
    return k;
}

/* 0x00308890, 0xEC bytes. Whether free officer `i` joins force `f`: drawn from its liking and
 * `f`'s size (42-100%) unless tied. */
int func_00308890(u32 i, int f)
{
    int v = func_003086C0(i, f);

    if (v == -1) {
        v = func_002F6FE0(i, fame_grade(f)) + func_002FB3B0(f) * 2;
        v = v < 0x2B ? 0x2A : v;
        v = v > 100 ? 100 : v;
    }
    return func_0030CB50(v);
}

/* 0x00308980, 0x1B8 bytes. The chance (18-100%) officer `i` joins force `f`: its liking, `f`'s
 * size, its values, less a quarter of its years in service and its loyalty grade. */
int func_00308980(u32 i, int f)
{
    int v = func_003086C0(i, f), x, s, a, b, y, e;

    if (v != -1)
        return v;
    x = func_002F6FE0(i, fame_grade(f));
    s = func_002FB3B0(f);
    a = func_002F4450(i);
    b = func_002F45A0(i);
    y = (u32)(func_00327C70() - func_002F3380(i)) < 100 ? func_00327C70() - func_002F3380(i) : 100;
    e = func_002F4A70(i);
    v = (7 - e) * 10 + (s + x * 8 / 10 + a * b) - y / 4;
    v = v < 0x13 ? 0x12 : v;
    return v > 100 ? 100 : v;
}

/* 0x00308B40, 0x24 bytes, matching. Draws func_00308980. */
int func_00308B40(u32 i, int f)
{
    return func_0030CB50(func_00308980(i, f));
}

/* 0x00308B70, 0x80 bytes. `v` cut by the player's fame: 0 from 10, a third from 5, half from
 * 1, kept below. */
int func_00308B70(int v)
{
    int m = func_00327E90();

    if (m >= 10)
        return 0;
    if (m >= 5)
        return v / 3;
    if (m > 0)
        return v / 2;
    return v;
}

int func_0030C280(int r, int home);
void func_0030C920(int *l, int n);

/* 0x00308F80, 0x19C bytes. The officer of list `l` (`n`, not busy; generic ones only unless
 * `any`) with the lowest func_002F33F0, then func_002F34E0, then soldiers, then the highest
 * number. */
u32 func_00308F80(u32 *l, int n, int any)
{
    int a = 0xFFFF, b = 99999, c = 0, k;
    u32 best = 0x19F;

    func_002F7C40(l, n);
    for (k = 0; k < n; k++, l++) {
        u32 x = *l;
        int v1, v2, v3;

        if (func_002F3E70(x) != 0)
            continue;
        if (any == 0 && func_002F3F20(x) != 0)
            continue;
        v1 = func_002F33F0(x);
        v2 = func_002F34E0(x);
        v3 = func_002F3770(x);
        if (v1 < a || best > 0x19E) {
            c = v3;
            b = v2;
            a = v1;
            best = x;
        } else if (v1 == a) {
            if (v2 < b) {
                c = v3;
                b = v2;
                best = x;
            } else if (v2 == b) {
                if (v3 < c) {
                    c = v3;
                    best = x;
                }
                if (v3 == c && (int)best < (int)x)
                    best = x;
            }
        }
    }
    return best;
}

/* 0x00309540, 0x1E8 bytes. Splits regions `l` (`n`) into connected groups: `st[2 + r]` is
 * region `r`'s group (-1 for none), `st[1]` the number of groups and `st[0]` the one chosen. */
void func_00309540(int *st, int *l, int n)
{
    int cnt[28], grp = 0, best, x, y;

    for (x = 0; x < 0x19; x++) {
        st[x + 2] = -1;
        cnt[x] = 0;
    }
    for (x = 0; x < n; x++) {
        if (st[l[x] + 2] != -1)
            continue;
        func_0030BBD0(l[x], 1);
        for (y = 0; y < n; y++) {
            if (st[l[y] + 2] == -1 && func_0030B2F0(l[y]) != 0) {
                st[l[y] + 2] = grp;
                cnt[grp]++;
            }
        }
        func_0030B330();
        grp++;
    }
    best = grp == 1 ? 0 : -1;
    for (x = 0; x < grp; x++) {
        if (best == -1 || cnt[x] > 0 || (cnt[x] == 0 && func_0030CB00(2) != 0))
            best = x;
    }
    st[0] = best;
    st[1] = grp;
}

/* 0x00309730, 0x48 bytes. The regions of group `grp` of `st` into `out`; their count. */
int func_00309730(int *st, int grp, int *out)
{
    int n = 0, r;

    for (r = 0; r < 0x19; r++) {
        if (st[r + 2] == grp)
            out[n++] = r;
    }
    return n;
}

/* 0x00309780, 0x48 bytes. Whether force `f`'s regions are split. */
int func_00309780(int f)
{
    int st[28], l[28], n = func_002FB320(f, l);

    if (n == 0)
        return 0;
    func_00309540(st, l, n);
    return st[1] > 1;
}

/* 0x003097D0, 0x23C bytes. Officer `i` leaves its region (when that region keeps enough
 * officers of its role): to its home (when connected), else to a region of the chosen group
 * (player's force), else it is set free; 1 when done. */
int func_003097D0(u32 i)
{
    int st[28], l[28], f = func_002F4080(i), r = func_002F5CC0(i), home, n, k;

    if (f == func_0030AFF0(r)) {
        if (func_002F3F20(i) != 0) {
            if (func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, r, 0, 1, 0) < 4)
                return 1;
        } else {
            if (func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, r, 0, 0, 0) < 4)
                return 1;
        }
        if (func_002FB2A0(f) != 0)
            return 0;
    }
    home = func_002FB2D0(f);
    if (IS_FORCE(home) && f == func_0030AFF0(home) && func_0030C280(r, home) != 0
        && func_00309130(i, f, home, 0) != 0)
        return 1;
    n = func_002FB320(f, l);
    if (n == 0) {
        func_002F7410(i);
        return 1;
    }
    if (func_002FB2A0(f) != 0) {
        func_00309540(st, l, n);
        n = func_00309730(st, st[0], l);
        func_0030C920(l, n);
        for (k = 0; k < n; k++) {
            if (func_00309130(i, f, l[k], 0) != 0)
                return 1;
        }
    }
    if (func_002FB2A0(f) == 0) {
        func_002F7410(i);
        return 1;
    }
    return 0;
}

/* 0x00309A10, 0xB0 bytes, matching. Officer `i` joins the player's force in region `r` (no region unless
 * func_002F76B0 gives 1 or 2); whether it got one. */
int func_00309A10(u32 i, int r)
{
    int k;

    if (func_002F3E70(i) != 0)
        func_002F3CF0(i, 2);
    k = func_002F76B0(i, r);
    if (k != 2 && k != 1)
        r = 0x19;
    func_002F7300(i, func_00327D50(), r, k);
    return IS_FORCE(r);
}

/* 0x00309130, 0x410 bytes. Places officer `i` of force `f` in its region `r` with a role (its
 * own, else 2 for named and 1 for generic ones) where there is room (three per role; a named
 * officer may push a generic one down, a busy computer officer may push one out); with `msg`
 * only the order is given. 1 when placed. */
int func_00309130(u32 i, int f, int r, int msg)
{
    u32 l[16], *o;
    int res = 0, role, a, b, cnt, k;
    u32 x;

    func_002F7B10();
    if (f != func_0030AFF0(r))
        return 0;
    role = func_002F3DC0(i);
    if (role == 0)
        role = func_002F3F20(i) == 0 ? 1 : 2;
    a = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, r, 0, 0, 0);
    o = func_002F7B10();
    for (k = 0; k < a; k++)
        l[k] = o[k];
    b = func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, r, 0, 0, 0);
    o = func_002F7B10();
    for (k = 0; k < b; k++)
        l[k + 3] = o[k];
    cnt = role > 1 ? a : b;
    if (cnt < 3) {
        res = 1;
    } else if (role == 1) {
        if (a < 3) {
            res = 1;
            role = 2;
        }
    } else if (role > 1 && b < 3) {
        if (func_002F3F20(i) == 0) {
            res = 1;
            role = 1;
        } else {
            x = func_00308F80(l, a, 0);
            if (x < 0x19F) {
                func_002F3CF0(x, 1);
                res = 1;
            }
        }
    }
    if (res == 0 && func_002F3E70(i) != 0 && func_002FB2A0(f) == 0) {
        func_002F7410(func_00308F80(l, a, 1));
        res = 1;
    }
    if (res != 0) {
        if (msg != 0) {
            func_002F7300(i, f, r, role);
            return res;
        }
        func_002F5BE0(i, r);
        if (func_002F3E70(i) == 0 && func_002F3DC0(i) != role)
            func_002F3CF0(i, role);
    }
    return res;
}

/* 0x00308BF0, 0x35C bytes. The chance (0-95%) force `f` wins over officer `i` of another force:
 * 0 when `i` is tied to an officer of its own force; drawn from 80 / 60 when tied to one of
 * `f`'s; else from its liking (by `f`'s infamy grade), `f`'s size, its values (doubled for the
 * player with an envoy), less a quarter of func_002F33F0, over its loyalty grade + 1 (cut by
 * the player's fame when `i` serves the player). The original keeps walking the officer list
 * of the first loop in the second one (kept). */
int func_00308BF0(u32 i, int f)
{
    u32 *o = func_002F7B10();
    int g, n, v = 0, m, k, x, s, a, b, y, e, mul;

    if (i >= 0x19F)
        return 0;
    g = func_002F4080(i);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, g, 0, 1, 0);
    for (k = 0; k < n; k++, o++) {
        u32 j = *o;

        if (i != j && TIED(j, i))
            return 0;
    }
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
    for (k = 0; k < n; k++, o++) {
        u32 j = *o;

        if (func_002F77A0(j, i) != 0) {
            v = 0x50;
            break;
        }
        if (func_002F78C0(j, i) != 0) {
            v = 0x3C;
            break;
        }
        if (func_002F7900(j, i) != 0) {
            v = 0x50;
            break;
        }
    }
    if (v != 0)
        return func_0030CB50(v);
    m = func_002FB2A0(f) != 0 ? func_00327E90() : 0;
    k = 0;
    if (m >= -10 && m < 0)
        k = 1;
    else if (m >= -15 && m < -10)
        k = 2;
    x = func_002F6FE0(i, k);
    s = func_002FB3B0(f);
    a = func_002F4450(i);
    b = func_002F45A0(i);
    y = func_002F33F0(i);
    mul = 1;
    if (func_002FB2A0(f) != 0 && (u32)func_00327870() < 0x19F)
        mul = 2;
    e = func_002F4A70(i);
    v = (x / 3 + s / 2 + mul * a * b - y / 4) / (e + 1);
    if (func_002FB2A0(g) != 0)
        v = func_00308B70(v);
    if (v <= 0)
        v = 0;
    return v > 0x5F ? 0x5F : v;
}

/* 0x00308F50, 0x24 bytes, matching. Draws func_00308BF0. */
int func_00308F50(u32 i, int f)
{
    return func_0030CB50(func_00308BF0(i, f));
}

extern struct { int step, most; } g_004149F0[];   /* by level: officers per region, at most */

void func_003986E0(int r, int a, u32 *l, int n);
void func_0030AF20(int r, int f);

/* 0x00309AC0, 0x84 bytes, matching. Officer `i` joins the player's force in region `r` (shown with the
 * join message). */
int func_00309AC0(u32 i, int r)
{
    u32 v = i;
    int p = func_00327D50();

    func_003986E0(r, -1, &v, 1);
    func_002F7300(v, p, r, func_002F3DC0(v));
    func_0030E390(1, -1, -1, -1, 0, 0);
    return 0;
}

/* 0x00309B50, 0xD4 bytes. Officer `i` joins the player's force: placed in a region connected to
 * `r` (nearest first), else in `r` with the message. */
int func_00309B50(u32 i, int r)
{
    int l[28], p = func_00327D50(), n, k;

    func_0030BBD0(r, 1);
    n = func_0030B3B0(l);
    func_0030B330();
    func_0030C920(l, n);
    for (k = 0; k < n; k++) {
        if (func_00309130(i, p, l[k], 1) != 0)
            break;
    }
    if (k < n)
        return 0;
    return func_00309AC0(i, r);
}

/* 0x00309C30, 0x358 bytes. Officer `i` joins force `f`, in region `r` if possible: given a role
 * (2 named, 1 generic) and a region (its home when it had none); the player's full force sends it
 * to a region of its own with the message; else region `r`, its own region, the force's home, any
 * of its regions, or it is set free. */
int func_00309C30(u32 i, int f, int r)
{
    u32 v = i;
    int l[28], role, cur, n, k, home;

    role = func_002F3F20(v) == 0 ? 1 : 2;
    func_002F3CF0(v, role);
    cur = func_002F5CC0(v);
    if (!IS_FORCE(cur)) {
        int h = func_002F3070(v);

        if (IS_FORCE(h))
            func_002F5BE0(v, h);
    }
    if (func_002FB2A0(f) != 0 && func_00327E50() <= func_002FB430(f)) {
        if (!IS_FORCE(r) || f != func_0030AFF0(r)) {
            r = func_002F5CC0(v);
            if (!IS_FORCE(r) || f != func_0030AFF0(r))
                r = func_002FB2D0(f);
        }
        func_003986E0(r, -1, &v, 1);
        func_002F7300(v, f, r, role);
        func_0030E390(1, -1, -1, -1, 0, 0);
        return 0;
    }
    if (IS_FORCE(r) && func_00309130(v, f, r, 1) != 0)
        return 0;
    cur = func_002F5CC0(v);
    if (IS_FORCE(cur)) {
        if (func_00309130(v, f, cur, 1) != 0)
            return 0;
        if (func_002FB2A0(f) != 0 && func_0030AFF0(cur) == f)
            return func_00309B50(v, cur);
    }
    home = func_002FB2D0(f);
    if (func_00309130(v, f, home, 1) != 0)
        return 0;
    if (func_002FB2A0(f) != 0)
        return func_00309B50(v, home);
    n = func_002FB320(f, l);
    func_0030C920(l, n);
    for (k = 0; k < n; k++) {
        if (func_00309130(v, f, l[k], 1) != 0)
            break;
    }
    if (k == n)
        func_002F7410(v);
    return 0;
}

/* 0x00309F90, 0x20 bytes, matching. Sets officer `i` free. */
int func_00309F90(u32 i)
{
    func_002F7410(i);
    return 0;
}

/* 0x00309FB0, 0x78 bytes. How many officers the player's force may have (by level and size). */
int func_00309FB0(void)
{
    int p = func_00327D50(), lv = func_00327A10();
    int n = g_004149F0[lv].step * (func_002FB3B0(p) - 1) + 6;

    if (n >= g_004149F0[lv].most)
        n = g_004149F0[lv].most;
    return n;
}

/* 0x0030A030, 0x288 bytes. Force `f` is destroyed: its officers set free, its regions given to
 * force `to` (when it still exists) or to a random neighbouring force (any force when none), its
 * leader cleared. */
int func_0030A030(int f, int to)
{
    int reg[28], nb[28], cand[28], n, k, j, m, c;
    u32 *o = func_002F7B10();

    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
    for (k = 0; k < n; k++, o++)
        func_002F7410(*o);
    func_002FAFC0(f);
    func_002FB7C0(f);
    n = func_002FB320(f, reg);
    for (k = 0; k < n; k++) {
        if (IS_FORCE(to) && func_002F8CB0(to) != 0) {
            func_0030AF20(reg[k], to);
        } else {
            m = func_0030C4E0(reg[k], nb);
            c = 0;
            for (j = 0; j < m; j++) {
                int g = func_0030AFF0(nb[j]);

                if (IS_FORCE(g) && func_002F8CB0(g) != 0 && g != f)
                    cand[c++] = g;
            }
            if (c == 0) {
                for (j = 0; j < 0x19; j++) {
                    if (func_002F8CB0(j) != 0 && j != f)
                        cand[c++] = j;
                }
            }
            to = cand[func_0030CB00(c)];
            func_0030AF20(reg[k], to);
        }
        func_00323840(reg[k]);
    }
    func_002F8D20(f);
    if (func_002FB2A0(f) == 0)
        func_002F8E80(f, 0x19F);
    func_003A7D90();
    return 0;
}

/* The order value of officer `i` for func_0030A2C0: leaders, then named ones, then level. */
static inline int officer_rank(u32 i)
{
    return (func_002F3DC0(i) == 3 ? 100000 : 0) + ((int)i < 0x2B ? 10000 : 0) + func_002F41E0(i) * 10;
}

/* 0x0030A2C0, 0x1A0 bytes. Sorts officers `l` (`n`) by rank, highest first (ties at random). */
void func_0030A2C0(u32 *l, int n)
{
    int x, y;

    for (x = 0; x < n; x++) {
        u32 a = l[x];
        int va = officer_rank(a);

        for (y = x + 1; y < n; y++) {
            u32 b = l[y];
            int vb = officer_rank(b);

            if (va < vb || (va == vb && func_0030CB50(0x32) != 0)) {
                l[x] = b;
                l[y] = a;
                va = vb;
                a = b;
            }
        }
    }
}

/* 0x0030A470, 0x3D8 bytes. Force `a` takes force `b`: `b`'s regions go to `a`; a computer `a`
 * keeps `b`'s officers; the player keeps its best six (asked through the join list) when there
 * is room, the others set free; otherwise `b` is destroyed in `a`'s favour. */
int func_0030A470(int a, int b)
{
    u32 l[8], *o;
    int reg[28], home, n, m, k, r = 0, bad;

    o = func_002F7B10();
    home = func_002FB2D0(b);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, b, 0, 1, 0);
    m = func_002FB320(b, reg);
    for (k = 0; k < m; k++) {
        func_0030AF20(reg[k], a);
        func_00323840(reg[k]);
    }
    if (func_002FB2A0(a) == 0) {
        o = func_002F7B10();
        for (k = 0; k < n; k++, o++) {
            u32 x = *o;

            func_002F7300(x, a, func_002F5CC0(x), func_002F3DC0(x) < 2 ? 1 : 2);
        }
        func_003A7D90();
    } else {
        func_00320F10();
        func_0030A2C0(o, n);
        if (n > 6) {
            o = func_002F7B10() + 6;
            for (k = 6; k < n; k++, o++) {
                r = func_00309F90(*o);
                if (r != 0)
                    break;
            }
        }
        if (r == 0) {
            bad = 0;
            if (n > 6)
                n = 6;
            o = func_002F7B10();
            for (k = 0; k < n; k++) {
                l[k] = -1;
                l[k] = o[k];
            }
            for (k = 0; k < n; k++) {
                if (func_00309A10(l[k], func_002F5CC0(l[k])) == 0)
                    bad = 1;
            }
            func_003A7D90();
            if (bad || func_002FB430(a) > func_00327E50()) {
                for (k = 0; k < n; k++)
                    func_002F5BE0(l[k], 0x19);
                func_003986E0(home, -1, l, n);
                func_0030E390(2, b, a, -1, 0, 0);
                return 0;
            }
        }
    }
    if (r == 0)
        r = func_0030A030(b, a);
    return r;
}

/* A region record (0x14 bytes, the table returned by func_0030CCD0; record 0x19 = none). */
typedef struct {
    u8 kind;                 /* +0x00 region kind (traits) */
    u8 unknown_1;
    u8 extra[2];             /* +0x02 */
    u8 next[6];              /* +0x04 neighbouring regions (0x19 = none) */
    u8 most;                 /* +0x0A troops wanted at most */
    u8 cap;                  /* +0x0B troop capacity */
    u32 flags;               /* +0x0C 2-bit fields 0-4, bit 15 = mark */
    short owner;             /* +0x10 force */
    u8 wanted;               /* +0x12 */
    u8 troops;               /* +0x13 */
} Region;

extern int g_00414A20[];                 /* by weapon kind: its group */
extern int g_004467C0[];                 /* by scenario: number of regions */
extern char *(*g_00414AA0[])(int a);     /* region names, by scenario */
extern int g_00414AD0[][4];              /* per region kind: the traits that go with it */
extern char g_004467F0[];                /* number format */
extern char g_007A3B30[10][10];          /* ten number strings, used in turn */
extern int g_0045D6AC;                   /* (small data) the next one */
extern int g_007B4E48, g_007B4E4C, g_007B4E50;

void func_0030B030(int r, int v);
void func_0011ED38(void *to, int value, int size);
void func_0017DF10(void);
int func_0017DDA0(void);

#define REGIONS ((Region *)func_0030CCD0())   /* the region table */
#define REGION(r) (&REGIONS[r])

/* 0x0030A850, 0x1C bytes, matching. */
void func_0030A850(int f)
{
    func_002F9A00(f, 7);
}

/* 0x0030A870, 0x258 bytes. A new force led by officer `i` rises in region `r` (kind 1: with a
 * policy from func_002FB910; kinds 1-2 halve the region's troops), with officers `l` (`n`);
 * shown when `show`. */
void func_0030A870(int kind, u32 i, int r, u32 *l, int n, int show)
{
    int g, k;

    func_0030AFF0(r);
    g = func_002FB8B0();
    func_002F8E80(g, i);
    func_0030AF20(r, g);
    func_002F7300(i, g, r, 3);
    func_002F94C0(g, 100);
    func_002F8F90(g, 1000);
    if (kind == 1)
        func_002F9900(g, func_002FB910());
    func_0030A850(g);
    func_002FAFC0(g);
    func_002F9E10(g, 3);
    func_002F9F40(g, 0xFF);
    func_002FA0D0(g, 0);
    func_002FA220(g, func_002FB2D0(g));
    func_002FA400(g, 1);
    func_002FA500(g, 0x19);
    func_002FA610(g, 0x19);
    func_002FA720(g, 0);
    func_002FA800(g, 0);
    func_002F91C0(g, 0x19F);
    func_002FA8E0(g, 1);
    for (k = 0; k < 3; k++)
        func_002F92D0(g, k, 0);
    if (l != 0) {
        for (k = 0; k < n; k++, l++) {
            if (*l < 0x19F)
                func_002F7300(*l, g, r, func_002F3DC0(*l));
        }
    }
    func_00323840(r);
    if (kind != 0)
        func_0030B030(r, func_0030ACE0(r) / 2);
    if (show != 0) {
        if (kind == 2)
            func_003A7DA0(r, 0);
        else
            func_003A7D90();
    }
}

/* 0x0030AAD0, 0x44 bytes, matching. The group of weapon kind `k` (3 for 0x1E and above). */
int func_0030AAD0(int k)
{
    if (k == 0x1E)
        return 3;
    if (k < 0x1E)
        return g_00414A20[k];
    return 3;
}

/* 0x0030AB20, 0x24 bytes, matching. The group of weapon `w`. */
int func_0030AB20(u8 w)
{
    return func_0030AAD0(func_002F57A0(w));
}

/* 0x0030AB50, 0x38 bytes, matching. 4 for kinds 9, 0x13 and 0x25, else 3. */
int func_0030AB50(int k)
{
    if (k == 9 || k == 0x13 || k == 0x25)
        return 4;
    return 3;
}

/* 0x0030AB90, 0x30 bytes, matching. The number of regions of the scenario. */
int func_0030AB90(void)
{
    return g_004467C0[func_00327C00()];
}

/* 0x0030ABC0, 0x24 bytes. Region 0x19 (none) belongs to no force. */
void func_0030ABC0(void)
{
    REGIONS[0x19].owner = 0x19;
}

char *func_0030AC20(int a, int k);

/* 0x0030ABF0, 0x30 bytes, matching. Region `a`'s name. */
char *func_0030ABF0(int a)
{
    return func_0030AC20(a, func_00327C00());
}

/* 0x0030AC20, 0x30 bytes, matching. Region `a`'s name in scenario `k`. */
char *func_0030AC20(int a, int k)
{
    return g_00414AA0[k](a);
}

/* 0x0030AC50, 0x38 bytes, matching. Region `r`'s kind. */
int func_0030AC50(int r)
{
    return REGION(r)->kind;
}

/* 0x0030AC90, 0x4C bytes. */
int func_0030AC90(int r, int k)
{
    return REGION(r)->extra[k];
}

/* 0x0030ACE0, 0x38 bytes, matching. Region `r`'s troop capacity. */
int func_0030ACE0(int r)
{
    return REGION(r)->cap;
}

/* 0x0030AD20, 0x58 bytes. Region `r`'s neighbour `k` (0x19 past six). */
int func_0030AD20(int r, int k)
{
    Region *g = REGIONS;

    if (k < 6)
        return g[r].next[k];
    return 0x19;
}

/* 0x0030AD80, 0x38 bytes, matching. */
int func_0030AD80(int r)
{
    return REGION(r)->wanted;
}

/* 0x0030ADC0, 0x80 bytes. Sets region `r`'s +0x12 value (0 to its most). */
void func_0030ADC0(int r, int v)
{
    if (func_0030AE80(r) < v)
        v = func_0030AE80(r);
    if (v < 1)
        v = 0;
    REGION(r)->wanted = v;
}

/* 0x0030AE80, 0x38 bytes, matching. */
int func_0030AE80(int r)
{
    return REGION(r)->most;
}

/* 0x0030AEC0, 0x60 bytes. Sets the owner of region record `g` (a force or 0x19). */
void func_0030AEC0(Region *g, int f)
{
    if (IS_FORCE(f) || f == 0x19)
        g->owner = f;
}

/* 0x0030AF20, 0x48 bytes, matching. Region `r` goes to force `f`. */
void func_0030AF20(int r, int f)
{
    func_0030AEC0(REGION(r), f);
}

/* 0x0030AF70, 0x7C bytes. The owner of region record `g` (0x19 for none). */
int func_0030AF70(Region *g)
{
    int r = g - REGIONS;

    if (r < 0)
        return 0x19;
    if (r < func_0030AB90())
        return (u16)g->owner;
    return 0x19;
}

/* 0x0030AFF0, 0x38 bytes, matching. Region `r`'s force. */
int func_0030AFF0(int r)
{
    return func_0030AF70(REGION(r));
}

/* 0x0030B030, 0x60 bytes. Sets region `r`'s troops (0-5). */
void func_0030B030(int r, int v)
{
    if (v >= 0 && v < 6)
        REGION(r)->troops = v;
}

/* 0x0030B090, 0x38 bytes, matching. Region `r`'s troops. */
int func_0030B090(int r)
{
    return REGION(r)->troops;
}

/* 0x0030B0D0, 0x78 bytes. Adds `d` troops (up to the capacity). */
void func_0030B0D0(int r, int d)
{
    if (d + func_0030B090(r) < func_0030ACE0(r))
        d = d + func_0030B090(r);
    else
        d = func_0030ACE0(r);
    func_0030B030(r, d);
}

/* 0x0030B150, 0x5C bytes. Takes `d` troops away (down to 0). */
void func_0030B150(int r, int d)
{
    func_0030B030(r, d < func_0030B090(r) ? func_0030B090(r) - d : 0);
}

/* 0x0030B1B0, 0x90 bytes. Sets 2-bit field `k` (0-4) of region `r`'s flags. */
void func_0030B1B0(int r, int k, int v)
{
    if (k >= 0 && k < 5) {
        Region *g = REGION(r);
        u32 s = k << 1, f = g->flags & ~(3 << s);

        g->flags = f;
        g->flags = f | v << s;
    }
}

/* 0x0030B240, 0x6C bytes. 2-bit field `k` of region `r`'s flags (0 out of range). */
int func_0030B240(int r, int k)
{
    if (k < 0 || k > 4)
        return 0;
    return REGION(r)->flags >> ((k & 0xF) << 1) & 3;
}

/* 0x0030B2B0, 0x40 bytes, matching. Marks region `r`. */
void func_0030B2B0(int r)
{
    REGION(r)->flags |= 0x8000;
}

/* 0x0030B2F0, 0x3C bytes, matching. Whether region `r` is marked. */
int func_0030B2F0(int r)
{
    return REGION(r)->flags & 0x8000;
}

/* 0x0030B330, 0x78 bytes. Clears every region's mark. */
void func_0030B330(void)
{
    Region *g = REGIONS;
    int k;

    for (k = 0; k < 0x19; k++, g++)
        g->flags &= 0xFFFF7FFF;
}

/* 0x0030B3B0, 0x84 bytes. The marked regions into `out`; their count. */
int func_0030B3B0(int *out)
{
    int n = 0, r;

    for (r = 0; r < func_0030AB90(); r++) {
        if (func_0030B2F0(r) != 0) {
            *out++ = r;
            n++;
        }
    }
    return n;
}

/* 0x0030B440, 0xF4 bytes. Marks the regions of region `r`'s force and their neighbours. */
void func_0030B440(int r)
{
    int g, x, k;

    func_0030B330();
    g = func_0030AFF0(r);
    for (x = 0; x < func_0030AB90(); x++) {
        x = func_0030C1C0(x, g);
        if (x >= func_0030AB90())
            return;
        func_0030B2B0(x);
        for (k = 0; k < 6; k++) {
            int n = func_0030AD20(x, k);

            if (IS_FORCE(n))
                func_0030B2B0(n);
        }
    }
}

/* 0x0030B540, 0xFC bytes. Marks the regions bordering region `r`'s force. */
void func_0030B540(int r)
{
    int g, x, k;

    func_0030B330();
    g = func_0030AFF0(r);
    for (x = 0; x < func_0030AB90(); x++) {
        x = func_0030C1C0(x, g);
        if (x >= func_0030AB90())
            return;
        for (k = 0; k < 6; k++) {
            int n = func_0030AD20(x, k);

            if (IS_FORCE(n) && g != func_0030AFF0(n))
                func_0030B2B0(n);
        }
    }
}

/* Whether region `x` is already in `q` (`n`). */
static inline int in_list(int x, int *q, int n)
{
    int k, found = 0;

    for (k = 0; k < n; k++) {
        if (x == q[k])
            found = 1;
    }
    return found;
}

/* 0x0030B640, 0x2AC bytes. Spreads from region `r` over its force's regions and those of forces
 * at war with it (the original tests the same condition twice, leaving its other branch dead),
 * then marks the regions bordering the force. */
void func_0030B640(int r)
{
    int q[28], g, head = 0, cnt = 1, x, k;

    func_0030B330();
    g = func_0030AFF0(r);
    q[0] = r;
    do {
        int cur = q[head++];

        for (k = 0; k < 6; k++) {
            int n = func_0030AD20(cur, k), o;

            if (!IS_FORCE(n))
                continue;
            o = func_0030AFF0(n);
            if (!IS_FORCE(o) || n == r)
                continue;
            if (o == g || func_002F9C90(g, o) == 3) {
                if (!in_list(n, q, cnt))
                    q[cnt++] = n;
            }
        }
    } while (head != cnt);
    g = func_0030AFF0(r);
    for (x = 0; x < func_0030AB90(); x++) {
        x = func_0030C1C0(x, g);
        if (x >= func_0030AB90())
            return;
        for (k = 0; k < 6; k++) {
            int n = func_0030AD20(x, k);

            if (IS_FORCE(n) && g != func_0030AFF0(n))
                func_0030B2B0(n);
        }
    }
}

/* 0x0030B8F0, 0x2DC bytes. Force `f`'s regions reachable from region `r` through regions of `f`
 * or of forces at war with it (not those with flag field 3 = 2), into `out`; their count. */
int func_0030B8F0(int r, int f, int *out)
{
    int q[28], cnt = 1, head = 0, n = 0, found = 0, k;

    for (k = 0; k < 0x19; k++)
        q[k] = 0x19;
    q[0] = r;
    do {
        int cur = q[head++];

        if (!IS_FORCE(cur))
            return n;
        for (k = 0; k < 6; k++) {
            int x = func_0030AD20(cur, k), o;

            if (!IS_FORCE(x))
                continue;
            o = func_0030AFF0(x);
            if (!IS_FORCE(o) || x == r || func_0030B240(x, 3) == 2)
                continue;
            if (o != f && func_002F9C90(f, o) != 3)
                continue;
            if (o != f && !in_list(x, q, cnt))
                q[cnt++] = x;
            if (o == f) {
                if (!in_list(x, out, n))
                    out[n++] = x;
                found = 1;
            }
        }
    } while (head != cnt || !found);
    return n;
}

/* 0x0030BBD0, 0x1D8 bytes. Marks the regions of region `r`'s force connected to `r` (through
 * its own regions and those of forces at war with it); `r` itself when `self`. */
void func_0030BBD0(int r, int self)
{
    int q[28], g, head = 0, cnt = 1, k;

    func_0030B330();
    g = func_0030AFF0(r);
    q[0] = r;
    if (self != 0)
        func_0030B2B0(r);
    do {
        int cur = q[head++];

        for (k = 0; k < 6; k++) {
            int n = func_0030AD20(cur, k), o;

            if (!IS_FORCE(n))
                continue;
            o = func_0030AFF0(n);
            if (!IS_FORCE(o) || !(o == g || func_002F9C90(g, o) == 3) || n == r || func_0030B2F0(n) != 0)
                continue;
            if (o == g)
                func_0030B2B0(n);
            if (!in_list(n, q, cnt))
                q[cnt++] = n;
        }
    } while (head != cnt);
}

/* 0x0030BDB0, 0x124 bytes. Marks the regions of the forces bordering region `r`'s force without a
 * tie to it; whether any. */
int func_0030BDB0(int r)
{
    int l[28], g, n, x, k, any = 0;

    func_0030B330();
    g = func_0030AFF0(r);
    n = func_002FB5A0(g, l);
    for (x = 0; x < func_0030AB90(); x++) {
        int o = func_0030AFF0(x);

        if (!IS_FORCE(o))
            continue;
        for (k = 0; k < n; k++) {
            if (o == l[k])
                break;
        }
        if (k < n && func_002FAFA0(g, o) == 0) {
            func_0030B2B0(x);
            any = 1;
        }
    }
    return any;
}

/* 0x0030BEE0, 0x140 bytes. Marks the other forces' regions with officers that are not a home;
 * whether any. */
int func_0030BEE0(int r)
{
    int home[25], g, f, x, any = 0;

    func_0030B330();
    g = func_0030AFF0(r);
    func_0011ED38(home, 0, 100);
    for (f = 0; f < 0x19; f++) {
        if (func_002F8CB0(f) != 0)
            home[func_002FB2D0(f)] = 1;
    }
    for (x = 0; x < func_0030AB90(); x++) {
        if (home[x] == 0) {
            int o = func_0030AFF0(x);

            if (IS_FORCE(o) && g != o && func_0030C660(x) != 0) {
                func_0030B2B0(x);
                any = 1;
            }
        }
    }
    return any;
}

/* 0x0030C020, 0x19C bytes. Marks the other forces' regions with officers (two or more at a home)
 * of forces having func_002F8250 officers; whether any. */
int func_0030C020(int r)
{
    int has[25], g, f, x, any = 0;

    func_0011ED38(has, 0, 100);
    for (f = 0; f < 0x19; f++) {
        if (func_002F8CB0(f) != 0 && func_002F7D90(0, (int (*)(u32, int, int))func_002F8250, f, 0, 1, 0) != 0)
            has[f] = 1;
    }
    func_0030B330();
    g = func_0030AFF0(r);
    for (x = 0; x < func_0030AB90(); x++) {
        int o = func_0030AFF0(x), c;

        if (!IS_FORCE(o) || g == o)
            continue;
        c = func_0030C660(x);
        if (((x == func_002FB2D0(o) && c > 1) || (x != func_002FB2D0(o) && c > 0)) && has[o] != 0) {
            func_0030B2B0(x);
            any = 1;
        }
    }
    return any;
}

/* 0x0030C1C0, 0x84 bytes. The first region from `x` on owned by force `g` (the count when none). */
int func_0030C1C0(int x, int g)
{
    Region *p = REGION(x);

    for (; x < func_0030AB90(); x++, p++) {
        if (g == func_0030AF70(p))
            return x;
    }
    return x;
}

/* 0x0030C250, 0x24 bytes, matching. Whether region `r` is the player's. */
int func_0030C250(int r)
{
    return func_002FB2A0(func_0030AFF0(r));
}

/* 0x0030C280, 0x98 bytes. Whether region `t` borders region `r`. */
int func_0030C280(int r, int t)
{
    int k;

    for (k = 0; k < 6; k++) {
        int n = func_0030AD20(r, k);

        if (IS_FORCE(n) && n == t)
            return 1;
    }
    return 0;
}

/* 0x0030C320, 0x98 bytes. The same. */
int func_0030C320(int r, int t)
{
    int k;

    for (k = 0; k < 6; k++) {
        int n = func_0030AD20(r, k);

        if (IS_FORCE(n) && n == t)
            return 1;
    }
    return 0;
}

/* 0x0030C3C0, 0x78 bytes, matching. Whether region `t` is reachable from region `r` by `t`'s force. */
int func_0030C3C0(int t, int r)
{
    int l[28], n = func_0030B8F0(r, func_0030AFF0(t), l), k;

    for (k = 0; k < n; k++) {
        if (t == l[k])
            return 1;
    }
    return 0;
}

/* 0x0030C440, 0xA0 bytes. Whether region `r` borders a region of force `f`. */
int func_0030C440(int r, int f)
{
    int k;

    for (k = 0; k < 6; k++) {
        int n = func_0030AD20(r, k);

        if (IS_FORCE(n) && f == func_0030AFF0(n))
            return 1;
    }
    return 0;
}

/* 0x0030C4E0, 0xA4 bytes. Region `r`'s neighbours into `out`; their count. */
int func_0030C4E0(int r, int *out)
{
    int n = 0, k;

    for (k = 0; k < 6; k++) {
        int x = func_0030AD20(r, k);

        if (IS_FORCE(x)) {
            *out++ = x;
            n++;
        }
    }
    return n;
}

/* 0x0030C590, 0xC8 bytes. The soldiers of region `r`'s officers (0 when unowned). */
int func_0030C590(int r)
{
    int g = func_0030AFF0(r), n, s = 0, k;
    u32 *o;

    if (!IS_FORCE(g))
        return 0;
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, r, 0, 1, 0);
    o = func_002F7B10();
    for (k = 0; k < n; k++, o++)
        s += func_002F3770(*o);
    return s;
}

/* 0x0030C660, 0x34 bytes, matching. Region `r`'s officers. */
int func_0030C660(int r)
{
    return func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, r, 0, 1, 0);
}

/* 0x0030C6A0, 0x34 bytes, matching. Region `r`'s officers of role 2 or more. */
int func_0030C6A0(int r)
{
    return func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, r, 0, 1, 0);
}

/* 0x0030C6E0, 0xB8 bytes. The regions of kind `a` or `b` (into `out` when given); their count. */
int func_0030C6E0(int *out, int a, int b)
{
    int n = 0, r, *p = out;

    for (r = 0; r < func_0030AB90(); r++) {
        int k = func_0030AC50(r);

        if (k == a || k == b) {
            if (out != 0)
                *p++ = r;
            n++;
        }
    }
    return n;
}

/* 0x0030C7A0, 0x44 bytes, matching. Whether trait `x` goes with trait `t`. */
int func_0030C7A0(int t, int x)
{
    int *p = g_00414AD0[t], k;

    for (k = 0; k < 4; k++, p++) {
        if (x == *p)
            return 1;
    }
    return 0;
}

int func_0030C810(int f, int a, int b);

/* 0x0030C7F0, 0x1C bytes, matching. Whether force `f` holds every region of kind `t`. */
int func_0030C7F0(int f, int t)
{
    return func_0030C810(f, t, 8);
}

/* 0x0030C810, 0x80 bytes, matching. Whether force `f` holds every region of kind `a` or `b`. */
int func_0030C810(int f, int a, int b)
{
    int l[28], n = func_0030C6E0(l, a, b), k;

    for (k = 0; k < n; k++) {
        if (f != func_0030AFF0(l[k]))
            return 0;
    }
    return 1;
}

/* 0x0030C890, 0x90 bytes. Whether region `r` is force `f`'s and short of troops. */
int func_0030C890(int r, int f)
{
    int g = func_0030AFF0(r);

    if (IS_FORCE(f) && f == g)
        return func_0030B090(r) < func_0030ACE0(r);
    return 0;
}

/* 0x0030C920, 0x94 bytes, matching. Shuffles `l` (`n`). */
void func_0030C920(int *l, int n)
{
    int k;

    for (k = 0; k < n; k++) {
        int a = func_0030CB00(n), b = func_0030CB00(n);

        if (a != b) {
            int t = l[a];

            l[a] = l[b];
            l[b] = t;
        }
    }
}

/* 0x0030C9C0, 0x90 bytes. Whether region `r` is where its force's leader is. */
int func_0030C9C0(int r)
{
    int g;

    if (r >= func_0030AB90())
        return 0;
    g = func_0030AFF0(r);
    if (!IS_FORCE(g))
        return 0;
    return r == func_002F5CC0(func_002F8F20(g));
}

/* 0x0030CA50, 0xAC bytes. The number of distinct region owners. */
int func_0030CA50(void)
{
    int l[28], n = 0, r, k;

    for (r = 0; r < func_0030AB90(); r++) {
        int o = func_0030AFF0(r);

        for (k = 0; k < n; k++) {
            if (o == l[k])
                break;
        }
        if (k >= n)
            l[n++] = o;
    }
    return n;
}

/* 0x0030CB00, 0x48 bytes. A random number below `n` (the game's generator). */
int func_0030CB00(int n)
{
    if (n == 0)
        return 0;
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    return (int)(g_7000015C >> 0x10) % n;
}

/* 0x0030CB50, 0x2C bytes, matching. True with `pct`% chance. */
int func_0030CB50(int pct)
{
    return func_0030CB00(100) < pct;
}

/* 0x0030CB80, 0x7C bytes. `v` as text, in the next of ten buffers. */
char *func_0030CB80(int v)
{
    if (++g_0045D6AC > 9)
        g_0045D6AC = 0;
    func_001204B0(g_007A3B30[g_0045D6AC], g_004467F0, v);
    return g_007A3B30[g_0045D6AC];
}

/* 0x0030CC00, 0x20 bytes. */
void func_0030CC00(void)
{
    g_007B4E4C = 0;
    g_007B4E48 = 0;
    g_007B4E50 = 0x12;
}

/* 0x0030CC20, 0x5C bytes. */
void func_0030CC20(int v)
{
    func_001B8F60(0, 6, 8);
    if (func_0017DDA0() != 0)
        func_0017DF10();
    g_007B4E48 = 2;
    g_007B4E50 = v;
}

/* 0x0030CC80, 0x2C bytes, matching. */
void func_0030CC80(void)
{
    func_0030CCE0();
    func_0030CF70();
    func_0030CC00();
}
