/*
 * emp_turn.c - the Empire mode's turn steps after emp_cq_main.c: two small choice menus, the
 * end-of-turn updates (relations, officers, provinces). Original file name unknown (it lies
 * between emp_cq_main.c and emp_ev_still.c). Written so far: parts of 0x00320060-.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 *g_0043C560, *g_0043C730;      /* help texts */
extern u8 g_007B5C90[];                  /* the end-of-turn steps' state */
extern int (*g_00414CC0[5])(void);       /* the end-of-turn steps */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

int *func_002FC2C0(void);
#define MENU() ((u8 *)func_002FC2C0()[0x1A5])
#define MI(o) (*(int *)(MENU() + (o)))

void func_00388710(void);
int func_003DC2D0(int k);
int func_0030D7D0(void);
int func_003890A0(void);
void func_0037EB40(int a, int b, int c);
int func_00327D50(void);
int func_00313DB0(int o, int s);
int func_002F9190(int s);
void func_00320120(void);
void func_001A7DC0(u8 *text, int a, int b);
int func_00389050(void);
void func_003890C0(void);
int func_00389090(void);
void func_0031DF40(int a);
void func_002FC560(void);
void func_0031FF20(void);
void func_0031FDD0(int a);
void func_00320450(void);
void func_00320790(void);
void func_00320B50(void);
void func_003DC090(int k, int *r);
void func_003DC0E0(int k, int a, int b);
int func_00327E50(void);
int func_00309FB0(void);
void func_00327E30(int v);
int func_0030AB90(void);
int func_002F8CB0(int i);
void func_002FA500(int i, int v);
void func_002F91C0(int i, int v);
void func_002FA610(int i, int v);
void func_002FA720(int i, int v);
void func_002FA800(int i, int v);
int func_002FB9D0(int i);
int func_002FA970(int i);
void func_002FA8E0(int i, int v);
void func_003280C0(int v);
int func_0030CB50(int k);
int func_00327F60(void);
int func_0030AD20(int f, int j);
void func_00327F00(int v);

/* 0x00320060, 0x50 bytes, matching. */
void func_00320060(void)
{
    func_00388710();
    if (func_003DC2D0(6) == 0)
        func_0037EB40(func_0030D7D0(), func_003890A0() + 7, -1);
}

/* 0x003200B0, 0x64 bytes. Whether officer `o` fits the current force's limit. */
int func_003200B0(int o)
{
    int s = func_00327D50();
    int v = func_00313DB0(o, s);

    return v == -1 || v <= func_002F9190(s);
}

/* 0x00320260, 0x4C bytes, matching. How many of the entries 7-10 are available. */
int func_00320260(void)
{
    u8 *m = MENU();
    int k, n = 0;

    for (k = 7; k < 0xB; k++) {
        if (*(int *)(m + 0x1E0 + k * 4) > 0)
            n++;
    }
    return n;
}

/* 0x003202B0, 0xEC bytes. Draws the first choice menu and its help line. */
void func_003202B0(void)
{
    u8 *m = MENU();

    if (*(int *)(m + 0x220) == 1) {
        func_00320120();
        if (*(int *)(m + 0x1E0 + *(int *)(m + 0x218) * 4) == 1)
            func_001A7DC0(g_0043C560, 0x80, 2);
        else
            func_001A7DC0(g_0043C730, 0x80, 2);
    } else if (*(int *)(m + 0x220) == 0) {
        func_00320060();
        if (func_00320260() == 1)
            func_001A7DC0(g_0043C560, 0x80, 2);
        else
            func_001A7DC0(g_0043C730, 0x80, 2);
    }
}

/* 0x003203A0, 0xA4 bytes. The first choice menu's step 0: an entry picked opens its page. */
void func_003203A0(void)
{
    int *st = func_002FC2C0();
    u8 *m = (u8 *)st[0x1A5];
    int v = func_00389050();

    if (v == 1) {
        int i;

        func_003890C0();
        i = func_00389090();
        if (*(int *)(m + 0x1E0 + i * 4) != 0) {
            *(int *)(m + 0x214) = 0;
            *(int *)(m + 0x210) = i + 7;
            *(int *)(m + 0x218) = i + 7;
            *(int *)(m + 0x21C) = -1;
            func_0031DF40(1);
        }
    } else if (v == 0) {
        func_002FC560();
        st[0] = 0;
        *(int *)(m + 0x210) = 0;
    }
}

/* 0x003206F0, 0x94 bytes. The first choice menu's update. */
int func_003206F0(void)
{
    int v = MI(0x220);

    if (v == 8)
        func_0031FF20();
    else if (v == 7)
        func_0031FDD0(1);
    else if (v == 1)
        func_00320450();
    else if (v == 0)
        func_003203A0();
    return 5;
}

/* 0x003209D0, 0x84 bytes. Draws the second choice menu. */
void func_003209D0(void)
{
    u8 *m = MENU();

    if (*(int *)(m + 0x220) == 1) {
        func_00320790();
        if (*(int *)(m + 0x20C) == 1)
            func_001A7DC0(g_0043C560, 0x80, 2);
        else
            func_001A7DC0(g_0043C730, 0x80, 2);
    }
}

/* 0x00320A60, 0x98 bytes, matching. Opens the second menu's two windows. */
void func_00320A60(void)
{
    int r[5];

    r[1] = 0x50;
    r[2] = 0xD8;
    r[3] = 0x18;
    r[4] = 0x80;
    r[0] = 0;
    func_003DC090(0x10, r);
    func_003DC0E0(0x10, 1, 1);
    r[0] = 0x154;
    r[1] = 0x68;
    r[2] = 0x98;
    r[3] = 0xD8;
    r[4] = 0x80;
    func_003DC090(0x11, r);
    func_003DC0E0(0x11, 2, 1);
}

/* 0x00320B00, 0x48 bytes, matching. The second menu's step 0. */
void func_00320B00(void)
{
    u8 *m = MENU();

    func_00320A60();
    *(int *)(m + 0x214) = 0;
    *(int *)(m + 0x210) = 0xB;
    *(int *)(m + 0x218) = 0xB;
    *(int *)(m + 0x21C) = -1;
    func_0031DF40(1);
}

/* 0x00320E40, 0x94 bytes. The second choice menu's update. */
int func_00320E40(void)
{
    int v = MI(0x220);

    if (v == 8)
        func_0031FF20();
    else if (v == 7)
        func_0031FDD0(2);
    else if (v == 1)
        func_00320B50();
    else if (v == 0)
        func_00320B00();
    return 5;
}

/* 0x00320EE0, 0x20 bytes, matching. */
void func_00320EE0(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
}

/* 0x00320F00, 0xC bytes, matching. */
u8 *func_00320F00(void)
{
    return g_007B5C90;
}

/* 0x00320F10, 0x50 bytes. Raises func_00327E50's value to func_00309FB0's; whether it did. */
int func_00320F10(void)
{
    int a = func_00327E50(), b = func_00309FB0();

    if (a < b)
        func_00327E30(b);
    return a < b;
}

/* 0x003210E0, 0x9C bytes. Clears every force's war state. */
int func_003210E0(void)
{
    int i;

    for (i = 0; i < func_0030AB90(); i++) {
        if (func_002F8CB0(i) != 0) {
            func_002FA500(i, 0x19);
            func_002F91C0(i, 0x19F);
            func_002FA610(i, 0x19);
            func_002FA720(i, 0);
            func_002FA800(i, 0);
        }
    }
    return 0;
}

/* 0x00321180, 0x80 bytes. Runs the end-of-turn steps (5 while busy, 0 when all are done). */
int func_00321180(void)
{
    u8 *s = func_00320F00();
    int r = 5;

    if (g_00414CC0[*(int *)(s + 4)]() == 0 && ++*(int *)(s + 4) > 4) {
        *(int *)(s + 4) = 0;
        r = 0;
        *(int *)(s + 8) = 0;
    }
    return r;
}

/* 0x00321200, 0x90 bytes. Raises every force's value to func_002FB9D0's. */
int func_00321200(void)
{
    int i;

    for (i = 0; i < func_0030AB90(); i++) {
        if (func_002F8CB0(i) != 0) {
            int a = func_002FB9D0(i);

            if (func_002FA970(i) < a)
                func_002FA8E0(i, a);
        }
    }
    return 0;
}

/* 0x00321290, 0x30 bytes, matching. */
int func_00321290(void)
{
    func_003280C0(func_002FA970(func_00327D50()));
    return 0;
}

/* 0x003214C0, 0x128 bytes. Unless event 0x32, picks one of the 6 neighbours of
 * func_00327F60's province at random (not 0x19). */
int func_003214C0(void)
{
    int f, n, j;

    if (func_0030CB50(0x32) != 0)
        return 0;
    f = func_00327F60();
    if (f >= func_0030AB90())
        return 0;
    for (j = n = 0; j < 6; j++) {
        if (func_0030AD20(f, j) < func_0030AB90())
            n++;
    }
    if (n != 0) {
        int v = func_0030AD20(f, (int)RANDOM() % n);

        if (v != 0x19)
            func_00327F00(v);
    }
    return 0;
}

/* End-of-turn steps (parts of 0x00322030-0x0032367C). */

extern u8 *g_0043CE80;                   /* "New artwork has been added ..." */
extern int (*g_00414CE0[0x17])(void);    /* the turn's steps */

int func_002F8160();
int func_002F8B20();
int func_002F80C0();
int func_002F8110();
int func_002F7D90(int a, int (*fn)(), int b, int c, int d, int e);
int *func_002F7B10(void);
void func_002F87D0(int *list, int n, int (*fn)(), int a, int b);
void func_002F7C40(int *list, int n);
u32 func_003C09B0(int i);
int func_00322720(int v);
void func_002F94C0(int i, u32 v);
void func_00329400(void);
int func_00327C00(void);
int func_00327900(void);
u32 func_00327820(void);
int func_00327C70(void);
void func_0030E390(int k, int a, int b, int c, int d, int e);
int func_003296F0(void);
void func_003DA8B0(int v);
int func_003DAA60(void);
void func_00327C50(int v);
int func_00327140(int a, int b);
int func_00327170(int a);
void func_0039F920(int a, int b);
void func_003137C0(void);
void func_003A7D90(void);
void func_00329740(void);
void func_003236F0(int a);
int func_0030DFA0(void);
int func_00327C40(void);
int func_002FB3B0(int f);
int func_002F41E0(int o);
int func_002F38F0(int o);
void func_002F37E0(int o, int v);
int func_00327CC0(void);
int func_002F4080(int o);
int func_002FABC0(int f);
void func_002F4B70(int o, int v);
int func_002FB120(int f);
int func_002F9C90(int a, int b);
void func_002FAF30(int a, int b);
int func_002F3E70(int o);
void func_002F7410(int o);
int func_002F2840(int o);
int func_002F5CC0(int o);
int func_0030AFF0(int p);
int func_003A3F20(void);
void func_00374EE0(u8 *text);
void func_0023AD10(int a, int b, int c, int d, int e);
int func_00375B90(void);

/* 0x00322030, 0x74 bytes, matching. Sets the other forces' func_003C09B0 values (100: none). */
int func_00322030(void)
{
    int i;

    for (i = 0; i < 0x19; i++) {
        u32 v;

        if (func_002F8CB0(i) != 0 && i != func_00327D50() && (v = func_003C09B0(i)) != 100)
            func_002F94C0(i, v & 0xFFFF);
    }
    return 0;
}

/* 0x003220B0, 0x20 bytes, matching. */
int func_003220B0(void)
{
    func_00329400();
    return 0;
}

/* 0x003220D0, 0x100 bytes. Notice 0x10 for the ruler's age 3, 7 or 11 years before the
 * scenario's end year. */
int func_003220D0(void)
{
    int s = func_00327C00(), d;
    u32 o;

    if (func_00327900() == 0)
        d = s == 7 ? 0x6BC : s == 8 ? 0x68C : s == 9 ? 0x644 : 0x6E0;
    else
        d = 200;
    o = func_00327820();
    if (o < 0x19F) {
        d -= func_00327C70();
        if (d == 0xB || d == 7 || d == 3)
            func_0030E390(0x10, o, d + 1, -1, 0, 0);
    }
    return 0;
}

/* 0x003221D0, 0x58 bytes. The season (year modulo 4). */
int func_003221D0(void)
{
    if (func_003296F0() == 0x13)
        func_003DA8B0(func_00327C70() % 4);
    return 0;
}

/* 0x00322230, 0x50 bytes. */
int func_00322230(void)
{
    int r = 5;

    if (func_003296F0() == 0x13) {
        if (func_003DAA60() != 0)
            r = 0;
    } else {
        r = 0;
    }
    return r;
}

/* 0x00322280, 0x100 bytes. A new year: the date moves on and the yearly updates run. */
int func_00322280(void)
{
    int s = func_003296F0();

    if (s == 0x13) {
        int y;

        func_00327C50(func_00327C70() + 1);
        y = func_00327C70();
        func_0039F920(func_00327140(func_00327C00(), y), func_00327170(y));
        func_003137C0();
        func_003A7D90();
        func_00329740();
        func_003236F0(1);
        if (func_00320F10() != 0)
            func_0030E390(0xF, -1, -1, -1, 0, 0);
    }
    if (func_00327C70() == 1 || s != 0x13)
        return 0xB;
    return func_0030DFA0();
}

/* 0x003223A0, 0x3C bytes. Steps a (phase, force) counter over the 25 forces. */
int func_003223A0(int *p)
{
    int v = ++p[3];

    if (v >= 0x19) {
        p[3] = 0;
        p[2]++;
    }
    return v < 0x19;
}

/* 0x003225E0, 0x138 bytes. The officers' growth values for the player's force: `*a` by the
 * difficulty, `*b` by its size, `*c` its best officers' mean (6 at most); whether it has any. */
int func_003225E0(int *a, int *b, int *c)
{
    int *list = func_002F7B10(), n, k;

    *a = func_00322720(func_00327C40());
    *b = func_002FB3B0(func_00327D50()) / 5 + 1;
    n = func_002F7D90(0, func_002F8160, func_00327D50(), 0, 1, 0);
    if (n == 0)
        return 0;
    func_002F87D0(list, n, func_002F8B20, -1, -1);
    if (n > 5)
        n = 6;
    for (k = 0; k < n; k++)
        *c += func_002F41E0(*list++);
    *c /= n;
    return 1;
}

/* 0x00322720, 0x5C bytes. */
int func_00322720(int v)
{
    if (v == 4 || v == 3)
        return 8;
    if (v == 2)
        return 6;
    return 5;
}

/* 0x00322780, 0xC8 bytes. Lists the 0x19F officers in order, then shuffles the first 0x2C and
 * the rest apart. */
void func_00322780(int *p)
{
    int i;

    for (i = 0; i < 0x19F; i++)
        p[i] = i;
    func_002F7C40(p, 0x2C);
    func_002F7C40(p + 0x2C, 0x173);
}

/* 0x00322850, 0x9C bytes. */
void func_00322850(int *p)
{
    int o;

    for (o = 0; o < 0x19F; o++) {
        int *q = p, n = 0, v;

        for (v = 0; v < 0x14; v++) {
            if (v == func_002F41E0(o)) {
                *q++ = o;
                n++;
            }
        }
        func_002F7C40(p, n);
        p = q;
    }
}

/* 0x00322B00, 0x16C bytes. The yearly pay of officers `list` (5% on the easy levels for a small
 * force, else 10%). */
void func_00322B00(int n, int *list)
{
    int pct, k;

    if (func_002FB3B0(func_00327D50()) < 0xD) {
        int c = func_00327C40();

        pct = c == 2 || c == 1 || c == 0 ? 5 : 10;
    } else {
        pct = 10;
    }
    for (k = 0; k < n; k++) {
        int o = *list++;

        func_002F37E0(o, pct * func_002F38F0(o) / 100);
        if (func_00327CC0() == 0) {
            int f = func_002F4080(o);

            if (func_002F8CB0(f) != 0)
                func_002F4B70(o, func_002FABC0(f) / 0x226 + 1);
        }
    }
}

/* 0x00323150, 0x11C bytes. The player's force ends a truce (state 2) with a smaller force once
 * it has 4 and more provinces. */
int func_00323150(void)
{
    int f = func_00327D50(), i;

    if (func_002FB120(f) == 0)
        return 0;
    for (i = 0; i < 0x19; i++) {
        if (f != i && func_002F8CB0(i) != 0 && func_002F9C90(f, i) == 2)
            break;
    }
    if (i == 0x19)
        return 0;
    if (func_002FB3B0(i) <= func_002FB3B0(f) && func_002FB3B0(f) > 3) {
        func_002FAF30(f, i);
        func_0030E390(0x12, f, i, 0, 0, 0);
    }
    return 0;
}

/* 0x00323270, 0x194 bytes. Each force keeps 3 officers of each list at most (the last ones that
 * pass func_002F3E70 are let go). */
void func_00323270(void)
{
    int *list = func_002F7B10();
    int f;

    for (f = 0; f < func_0030AB90(); f++) {
        int j;

        for (j = 0; j < 2; j++) {
            int n = j == 0 ? func_002F7D90(0, func_002F80C0, f, 0, 1, 0)
                           : func_002F7D90(0, func_002F8110, f, 0, 0, 0);

            while (n > 3) {
                int k, i = n;

                for (k = 0; k < n; k++) {
                    i = n - k - 1;
                    if ((u32)list[i] < 0x19F && func_002F3E70(list[i]) == 0)
                        break;
                }
                if (i < n) {
                    func_002F7410(list[i]);
                    n--;
                    list[i] = 0x19F;
                }
            }
        }
    }
}

/* 0x00323410, 0x84 bytes, matching. Officers serving a force away from their province's owner leave. */
void func_00323410(void)
{
    int o;

    for (o = 0; o < 0x19F; o++) {
        if (func_002F2840(o) != 0) {
            int f = func_002F4080(o);

            if (func_002F8CB0(f) != 0 && f != func_0030AFF0(func_002F5CC0(o)))
                func_002F7410(o);
        }
    }
}

/* 0x003234A0, 0xC4 bytes. Tells the player when new artwork was added to the gallery. */
int func_003234A0(void)
{
    u8 *s = func_00320F00();
    int r = 5;

    if (*(int *)(s + 8) == 0) {
        if (func_003A3F20() == 0) {
            *(int *)(s + 8) = 2;
        } else {
            func_00374EE0(g_0043CE80);
            func_0023AD10(9, 0, 0x2CDC, 0x2CDC, 0x1000);
            *(int *)(s + 8) += 1;
        }
    } else if (*(int *)(s + 8) == 1) {
        if (func_00375B90() == 1)
            *(int *)(s + 8) += 1;
    } else {
        *(int *)(s + 8) = 0;
        r = 0;
    }
    return r;
}

/* 0x00323570, 0x28 bytes, matching. */
int func_00323570(void)
{
    func_00323270();
    func_00323410();
    return 0;
}

/* 0x003235A0, 0xDC bytes. Runs the turn's 0x17 steps (0xB skips to step 0x15; 6, 7 and 10 end
 * the turn at once). */
int func_003235A0(void)
{
    int *p = (int *)func_00320F00();
    int v = g_00414CE0[*p](), r = 5;

    if (v == 0xB) {
        if (*p != 0x15)
            *p = 0x15;
    } else {
        r = v;
        if (v != 6 && v != 7 && v != 10) {
            r = 5;
            if (v == 0 && ++*p > 0x16) {
                *p = 0;
                r = 0;
            }
        }
    }
    return r;
}

/* Alliances and small turn helpers (parts of 0x00323680-0x003256A4). The 12 alliance slots:
 * func_00329160(k, &a, &b) gives the two forces of slot `k`. */

void func_003DA8D0(void);
void func_00328CB0(void);
void func_00328E70(void);
void func_00329030(void);
int func_00328DE0(int i);
int func_00328FA0(int i);
int func_00329160(int k, int *a, int *b);
void func_00329090(int k, int a, int b);
void func_0032EA30(void);
void func_0032E9E0(int o);
int func_002FAFA0(int f, int p);
int func_002F3770(int o);
int func_00362160(int a, int b);
int func_00337A10(int v);
int func_0036B260(void);
void func_003AE9F0(int a, int *b, int c);
int func_0030D370(void);
int func_0030CB00(int n);
int func_00328970(void);
void func_00328670(int v);

/* 0x00323680, 0x1C bytes, matching. */
void func_00323680(void)
{
    func_003DA8D0();
}

/* 0x003236A0, 0x44 bytes, matching. */
int func_003236A0(void)
{
    if (func_00320F10() != 0)
        func_0030E390(0xF, -1, -1, -1, 0, 0);
    return 0;
}

/* 0x003236F0, 0x3C bytes, matching. */
void func_003236F0(int all)
{
    func_00328CB0();
    func_00328E70();
    if (all != 0)
        func_00329030();
}

/* 0x00323730, 0x90 bytes. Whether a force passes func_00328DE0 (`k` 0) or func_00328FA0 (1). */
int func_00323730(int k)
{
    int i;

    for (i = 0; i < 0x19; i++) {
        if (func_002F8CB0(i) != 0
            && ((k == 0 && func_00328DE0(i) != 0) || (k == 1 && func_00328FA0(i) != 0)))
            break;
    }
    return i < 0x19;
}

/* 0x003237C0, 0x74 bytes, matching. Whether an alliance's second force owns the player's force's
 * province. */
int func_003237C0(void)
{
    int f = func_00327D50(), k, a, b;

    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0 && f == func_0030AFF0(b))
            return 1;
    }
    return 0;
}

/* 0x00323840, 0x84 bytes. Ends force `p`'s alliance. */
void func_00323840(int p)
{
    int k, a, b;

    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0 && (a == p || b == p))
            break;
    }
    if (k > 0xB)
        return;
    func_00329090(k, 0x19, 0x19);
}

/* 0x00323BD0, 0x88 bytes. Force `p`'s ally (0x19: none). */
int func_00323BD0(int p)
{
    int r = 0x19, k, a, b;

    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0) {
            if (a == p)
                r = b;
            else if (b == p)
                r = a;
        }
    }
    return r;
}

/* 0x00323C60, 0x6C bytes, matching. The ally force `p` leads (0x19: none). */
int func_00323C60(int p)
{
    int k, a, b;

    for (k = 0; k < 0xC; k++) {
        if (func_00329160(k, &a, &b) != 0 && a == p)
            return b;
    }
    return 0x19;
}

/* 0x00323F00, 0xC bytes, matching. */
u8 *func_00323F00(void)
{
    extern u8 g_007B5D40[];

    return g_007B5D40;
}

/* 0x00324060, 0x70 bytes. */
int func_00324060(int a, int *list, int n)
{
    int k;

    func_0032EA30();
    for (k = 0; k < n; k++)
        func_0032E9E0(*list++);
    return 0;
}

/* 0x003240D0, 0xF0 bytes. Moves the first officer of `list` that passes func_002F3E70 to its
 * end. */
void func_003240D0(u32 *list, int n)
{
    u32 keep = 0x19F;
    int k;

    for (k = 0; k < n - 1; k++) {
        if (keep > 0x19E && func_002F3E70(list[k]) != 0)
            keep = list[k];
        if (keep < 0x19F)
            list[k] = list[k + 1];
    }
    if (keep < 0x19F)
        list[n - 1] = keep;
}

/* 0x003247E0, 0xBC bytes. Whether force `f` has func_002FAFA0 with the owner of one of the
 * provinces `list`. */
int func_003247E0(int f, int *list, int n)
{
    int k;

    for (k = 0; k < n; k++) {
        int p = func_0030AFF0(*list++);

        if (p >= 0 && p < func_0030AB90() && f != p && func_002FAFA0(f, p) != 0)
            return 1;
    }
    return 0;
}

/* 0x003248A0, 0x68 bytes. The sum of func_002F3770 over officers `list`. */
int func_003248A0(int *list, int n)
{
    int k, s = 0;

    for (k = 0; k < n; k++)
        s += func_002F3770(*list++);
    return s;
}

/* 0x00325110, 0x9C bytes. The forces of the battle's two sides (`a` the player's). */
void func_00325110(int *a, int *b)
{
    int x = func_002F4080(func_00337A10(func_00362160(1, 0)));
    int y = func_002F4080(func_00337A10(func_00362160(0, 0)));

    if (func_0036B260() == 0) {
        *a = x;
        *b = y;
    } else {
        *a = y;
        *b = x;
    }
}

/* 0x00325360, 0x44 bytes, matching. Sets the after-battle step (7 starts the province change). */
void func_00325360(int v)
{
    int *p = (int *)func_002FC2C0()[0x1AA];

    p[0] = v;
    if (v == 7)
        func_003AE9F0(p[5], p + 0xD, p[0x13]);
}

/* 0x003253B0, 0x3C bytes, matching. */
void func_003253B0(void)
{
    if (func_0030D370() == 0)
        func_00325360(0xC);
    else
        func_00325360(1);
}

/* 0x00325500, 0xC0 bytes, matching. A reward item kind at random (0x5A-0x62). */
int func_00325500(void)
{
    int v = func_0030CB00(100);

    if (v < 0x11)
        return 0x5A;
    if (v < 0x21)
        return 0x5C;
    if (v < 0x31)
        return 0x5F;
    if (v < 0x3C)
        return 0x60;
    if (v < 0x47)
        return 0x5D;
    if (v < 0x52)
        return 0x5E;
    if (v < 0x58)
        return 0x5B;
    if (v < 0x5E)
        return 0x61;
    return 0x62;
}

/* 0x003255C0, 0xE4 bytes. Gives the battle's reward items (1, or 2 in the second mode, while
 * fewer than 5 are held) and reports them. */
void func_003255C0(void)
{
    int n = 5 - func_00328970(), ids[2], k;

    if (n < 0)
        n = 0;
    if (func_0036B260() == 0) {
        if (n > 0)
            n = 1;
    } else if (n > 1) {
        n = 2;
    }
    if (n == 0)
        return;
    for (k = 0; k < n; k++) {
        ids[k] = func_00325500();
        func_00328670(ids[k]);
    }
    func_0030E390(0x17, 0, -1, -1, (int)ids, n);
    func_00325360(3);
}

/* After-battle steps (parts of 0x003256B0-0x00327708): the province change, the captured
 * officers' notices, the turn date and the game state's first fields. */

extern int g_007B5CB0[];                 /* the second after-battle step */
extern int g_00414D40[];                 /* the scenarios' first years */
extern u32 g_0068EFD8, g_0068EFDC;

#define AFTER() ((int *)func_002FC2C0()[0x1AA])
#define AFTER2() ((int *)func_002FC2C0()[0x1AE])

int func_0036BA60(int x);
int func_0036BA40(int x);
int func_00375B90(void);
int func_0030C4E0(int p, int *list);
int func_0030C250(int p);
int func_002FB320(int f, int *list);
void func_003986E0(int a, int b, int *c, int d);
void func_0030E390(int k, int a, int b, int c, int d, int e);
void func_0039B700(void);
int func_003AF9F0(void);
int func_00390760(int k);
int func_00372660(int v);
int func_00327C80(void);
int func_0030CB80(int v);
int func_002F2A30(int o);
void func_001204B0(char *buf, int fmt, int a, int b, int c);
int func_002FB430(int f);
void func_0030A030(int a, int b);
void func_00323E60(int *p);
void func_003AF220(void);
int func_00120A40(u8 *p);

/* 0x003256B0, 0x60 bytes, matching. */
int func_003256B0(int k, int x)
{
    if (k == 1) {
        if (func_0036BA60(x) == 2)
            return 1;
    } else if (k == 0 && func_0036BA40(x) == 2) {
        return 1;
    }
    return 0;
}

/* 0x00325B10, 0x30 bytes, matching. */
void func_00325B10(void)
{
    if (func_00375B90() == 1)
        func_00325360(5);
}

/* 0x00325B40, 0xB0 bytes. A province for province `p`'s defeated (the first neighbour that
 * passes func_0030C250, else one of the player's at random). */
int func_00325B40(int p)
{
    int list[28], n = func_0030C4E0(p, list), k;

    if (n != 0) {
        for (k = 0; k < n; k++) {
            if (func_0030C250(list[k]) != 0)
                return list[k];
        }
    }
    n = func_002FB320(func_00327D50(), list);
    return list[func_0030CB00(n)];
}

/* 0x00325BF0, 0x68 bytes. */
void func_00325BF0(void)
{
    int *p = AFTER();
    int t = p[5];

    if (func_0030C250(t) == 0) {
        func_003986E0(func_00325B40(t), -1, p + 6, p[0xC]);
        func_00325360(6);
    }
}

/* 0x00325C60, 0x30 bytes, matching. Notice 4 about officer `o`. */
void func_00325C60(int o)
{
    func_0030E390(4, o, -1, -1, 0, 0);
}

/* 0x00325D40, 0x1C bytes, matching. */
void func_00325D40(void)
{
    func_0039B700();
}

/* 0x00325D60, 0x30 bytes, matching. */
void func_00325D60(void)
{
    if (func_003AF9F0() == 1)
        func_00325360(9);
}

/* 0x00325E80, 0x84 bytes, matching. Shows message 0x70 about officer `o` (with the mode, the date). */
void func_00325E80(int o)
{
    char buf[96];
    int fmt = func_00390760(0x70);
    int a = func_00372660(func_00327CC0());
    int b = func_0030CB80(func_00327C80());

    func_001204B0(buf, fmt, a, b, func_002F2A30(o));
    func_00374EE0((u8 *)buf);
}

/* 0x00325F10, 0x78 bytes. The beaten force falls when it has no province (or no officer) left. */
void func_00325F10(void)
{
    int *p = AFTER();

    if (func_002FB3B0(p[3]) == 0 || func_002FB430(p[3]) == 0) {
        func_00325E80(p[4]);
        func_0030A030(p[3], p[2]);
        func_00325360(10);
    } else {
        func_00325360(0xC);
    }
}

/* 0x00325F90, 0x30 bytes, matching. */
void func_00325F90(void)
{
    if (func_00375B90() == 1)
        func_00325360(0xC);
}

/* 0x00325FC0, 0x38 bytes, matching. Leaves the after-battle steps. */
void func_00325FC0(void)
{
    int *st = func_002FC2C0();

    func_00323E60((int *)st[0x1AA]);
    func_002FC560();
    st[0] = 0;
}

/* 0x00326370, 0x1C bytes, matching. */
void func_00326370(void)
{
    func_003AF220();
}

/* 0x00326390, 0x5C bytes. The after-battle steps' drawing. */
void func_00326390(void)
{
    if (*AFTER() == 7)
        func_00326370();
    else if (*AFTER() == 6)
        func_00325D40();
}

/* 0x00326490, 0xC bytes, matching. */
int *func_00326490(void)
{
    return g_007B5CB0;
}

/* 0x003264A0, 0xC bytes, matching. */
void func_003264A0(int v)
{
    g_007B5CB0[0] = v;
}

/* 0x00326660, 0x40 bytes, matching. */
void func_00326660(void)
{
    int *p = AFTER2();

    func_00325E80(p[4]);
    func_0030A030(p[3], p[2]);
    func_003264A0(4);
}

/* 0x00326A20, 0x68 bytes. */
void func_00326A20(void)
{
    int *p = AFTER2();
    int t = p[5];

    if (func_0030C250(t) == 0) {
        func_003986E0(func_00325B40(t), -1, p + 8, p[6]);
        func_003264A0(6);
    }
}

/* 0x00327090, 0x1C bytes, matching. */
void func_00327090(void)
{
    func_0039B700();
}

/* 0x003270B0, 0x40 bytes. */
void func_003270B0(void)
{
    if (*AFTER2() == 6)
        func_00327090();
}

/* 0x003270F0, 0x50 bytes. Whether save image `p` holds a game (an officer and a valid name). */
int func_003270F0(u8 *p)
{
    if (*(u16 *)(p + 0x1204) < 0x19F && func_00120A40(p + 0x125F) != 0)
        return 1;
    return 0;
}

/* 0x00327140, 0x30 bytes. The year of turn `t` in scenario `s` (4 turns a year). */
int func_00327140(int s, int t)
{
    if (t == 0)
        t = 1;
    return g_00414D40[s] + ((t - 1u) >> 2);
}

/* 0x00327170, 0x18 bytes, matching. The season of turn `t`. */
int func_00327170(int t)
{
    if (t == 0)
        t = 1;
    return (t - 1u) & 3;
}

/* 0x003273D0, 8 bytes, matching. */
void func_003273D0(void)
{
}

/* 0x00327690, 0xC bytes. */
void func_00327690(u32 v)
{
    g_0068EFD8 = v;
}

/* 0x003276A0, 0xC bytes. */
u32 func_003276A0(void)
{
    return g_0068EFD8;
}

/* 0x003276B0, 0xC bytes. */
void func_003276B0(u32 v)
{
    g_0068EFDC = v;
}

/* 0x003276C0, 0xC bytes. */
u32 func_003276C0(void)
{
    return g_0068EFDC;
}

/* 0x003276D0, 0x34 bytes. Counts the play time up (to 0xCDFE5C4 at most). */
void func_003276D0(void)
{
    g_0068EFDC++;
    if (g_0068EFDC > 0xCDFE5C4)
        g_0068EFDC = 0xCDFE5C4;
}

/* The yearly officer step (0x00329A00-0x00329D1C; its state at FC2C0()[0x1A6]). */

#define STEP3() ((int *)func_002FC2C0()[0x1A6])

int func_0032D9C0(void);
int func_003760C0(void);
int func_003760E0(void);
void func_00376100(int a, int b, int c);
int func_0032E760(void);
int func_0030E1F0(void);
void func_002F4360(int o, int v);
void func_002F4510(int o, int v);
void func_002F4760(int o, int v);
void func_0030E140(int k, int a, int b, int c);
void func_0030E100(void);
void func_002FCF20(void);
int func_00305040(int o);
int func_002F8F20(int f);
void func_0039F960(void);
void func_003298A0(int *p);
void func_0032D3C0(int a);
void func_003298B0(void);
int func_003280E0(void);

/* 0x00329A00, 0x78 bytes, matching. */
void func_00329A00(void)
{
    int *p = STEP3();
    int v = func_0032D9C0();

    if (v == 1) {
        func_00376100(func_003760C0(), func_003760E0(), -1);
        p[0] = 2;
    } else if (v == 0) {
        p[0] = 4;
    }
}

/* 0x00329A80, 0xDC bytes, matching. */
void func_00329A80(void)
{
    int *p = STEP3();
    int o = func_0032E760();

    if (func_0030E1F0() == 0) {
        func_002F4360(o, 2);
        func_002F4510(o, 0);
        func_002F4760(o, func_003280E0() * 0xF);
        func_0030E140(0x1C, o, func_002F8F20(func_00327D50()), -1);
    } else if (func_0030E1F0() == 2) {
        int list[28];

        func_0030E100();
        func_002FCF20();
        func_002FB320(func_00327D50(), list);
        p[0] = 3;
    }
}

/* 0x00329B60, 0x74 bytes. */
void func_00329B60(void)
{
    int *p = STEP3();

    if (func_00305040(func_0032E760()) == 0) {
        int v = p[1]++;

        if (func_003280E0() <= v + 1) {
            func_003280C0(0);
            func_0039F960();
            p[0] = 4;
        }
    }
}

/* 0x00329BE0, 0x38 bytes, matching. */
void func_00329BE0(void)
{
    int *st = func_002FC2C0();

    func_003298A0((int *)st[0x1A6]);
    func_002FC560();
    st[0] = 0;
}

/* 0x00329C20, 0x48 bytes. */
void func_00329C20(void)
{
    if (*STEP3() == 1)
        func_0032D3C0(func_0030D7D0());
}

/* 0x00329C70, 0xB0 bytes. */
int func_00329C70(void)
{
    int v = *STEP3();

    if (v == 4)
        func_00329BE0();
    else if (v == 3)
        func_00329B60();
    else if (v == 2)
        func_00329A80();
    else if (v == 1)
        func_00329A00();
    else if (v == 0)
        func_003298B0();
    return 5;
}
