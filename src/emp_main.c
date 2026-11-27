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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_007A2D60[0x1B2];            /* the turn state (+0 the page) */
extern u8 g_007A2CF0[], g_007A3AF0[];
extern u32 g_007A33F4[0xD];              /* each page's state block */
extern const char *g_0043C5F0;           /* a caption */
extern int g_007A3AD0[8], g_007A3AB0[8]; /* two short lists of officers */
extern int g_0045D688, g_0045D68C, g_0045D690, g_0045D69C, g_0045D6A0;   /* (small data) */

int func_0030AB90(void);
int func_0030C1C0(int f, int g);
int func_0030AD80(int f);
int func_00328190(int k);
int func_003280E0(void);
void func_00388200(int a, u32 b);
void func_003882C0(u32 *on);
void func_00376100(int a, int b, int c);
int func_003237C0(void);
int func_00323730(int k);
void func_001A7DC0(const char *s, int alpha, int layer);
void func_003762C0(void);
void func_003A9010(int a);
int func_00375B90(void);
u32 func_00390760(int k);
void func_00375140(int a, int b, int c, u32 d);
int func_003F1160(int a);
int func_003F1070(int a);
int func_00337E00(void);
void func_003A9170(void);
int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort);
int func_002F8160(u32 i, int f);
u32 *func_002F7B10(void);
int func_002F3770(u32 i);
int func_00327D50(void);
int func_002F9190(int f);
int func_00313B30(int i);
int func_00313FC0(int a, int b, int f);
int func_002FB2A0(int f);
int func_00327C40(void);
int func_00328570(void);

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
u32 func_0031D6C0(void); void func_0031D830(u32 s);
u32 func_00329890(void); void func_003298A0(u32 s);
u32 func_00335050(void); void func_00335060(u32 s);
u32 func_00335EE0(void); void func_00335EF0(u32 s);
u32 func_00323F00(void); void func_00323E60(u32 s);
u32 func_0039BA50(void); void func_0039BA60(u32 s);
u32 func_0039BC10(void); void func_0039BC20(u32 s);
u32 func_003C0070(void); void func_003C0080(u32 s);
u32 func_002FCD60(void); void func_002FCD20(u32 *s);
u32 func_00307230(void); void func_003071E0(u32 s);
u32 func_00326490(void); void func_003263F0(u32 s);
u32 func_00320F00(void); void func_00320EE0(u32 s);

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
    g_007A33F4[0] = func_0031D6C0();
    func_0031D830(g_007A33F4[0]);
    g_007A33F4[1] = func_00329890();
    func_003298A0(g_007A33F4[1]);
    g_007A33F4[2] = func_00335050();
    func_00335060(g_007A33F4[2]);
    g_007A33F4[3] = func_00335EE0();
    func_00335EF0(g_007A33F4[3]);
    g_007A33F4[5] = func_00323F00();
    func_00323E60(g_007A33F4[5]);
    g_007A33F4[4] = func_0039BA50();
    func_0039BA60(g_007A33F4[4]);
    g_007A33F4[6] = func_0039BC10();
    func_0039BC20(g_007A33F4[6]);
    g_007A33F4[10] = func_003C0070();
    func_003C0080(g_007A33F4[10]);
    g_007A33F4[7] = func_002FCD60();
    func_002FCD20((u32 *)g_007A33F4[7]);
    g_007A33F4[8] = func_00307230();
    func_003071E0(g_007A33F4[8]);
    g_007A33F4[9] = func_00326490();
    func_003263F0(g_007A33F4[9]);
    g_007A33F4[11] = func_00320F00();
    func_00320EE0(g_007A33F4[11]);
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
    func_003882C0(on);
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
    func_003882C0(on);
    func_00376100(5, -1, -1);
}

void func_0031DA90(void); void func_00335DA0(void); void func_00329C20(void);
void func_0031EA10(void); void func_003202B0(void); void func_003209D0(void);
void func_0039BB40(void); void func_0039E380(void); void func_003C0190(void);

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

int func_0031DDB0(void); int func_00335DE0(void); int func_00329C70(void);
int func_0031FF80(void); int func_003206F0(void); int func_00320E40(void);
int func_0039BB80(void); int func_0039D4A0(void); int func_003C01D0(void);

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
            func_00375140(0x100, 200, 1, func_00390760(0x111));
            g_007A2D60[0] = 0xF;
        }
        break;
    case 0xF:
        r = func_002FC800();
        break;
    }
    return r;
}

void func_003C0250(void); void func_0039E470(void); void func_003383B0(void);
void func_00338250(void); void func_003380F0(void); void func_00337ED0(void);
void func_00337D30(void);

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

int func_003C0290(void); int func_0039E500(void); int func_003382F0(void);
int func_00338190(void); int func_00338030(void); int func_00337F30(void);

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
            func_00375140(0x100, 200, 1, func_00390760(0xA9));
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
    s[5] = (u32)func_002FC2B0();
    func_002FD490();
}

/* 0x002FCD60, 0xC bytes, matching. */
u32 func_002FCD60(void)
{
    return (u32)g_007A3AF0;
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
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1), s = 0, k;
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
