/*
 * emp_cmd_steps.c - the Empire commands' step handlers and their drawers (parts of 0x00380810-
 * 0x0038BA98): each command menu `m` (+0x08 its kind, +0x68C the current entry, +0x690 the step,
 * entries of 0x184 bytes from +0x80) runs a notice step 0, a message step 1 and a window step 2.
 * Also the selection list (0x007B9E58) and a few value drawers. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char g_00459540[];
extern int g_00459650[0xB][4];
extern u8 g_00459724[][0x18];            /* the selection list layouts (+0 count, +4 x, +6 y) */
extern int g_00417650[];
extern u8 g_007B9E58;                    /* the selection list's layout */
extern u8 g_007B9E5D[];                  /* its entries' availability */
extern int g_0045D898;                   /* (small data) the scene */

#define STEP(m) (*(int *)((m) + 0x690))
#define ENTRY(m) ((m) + *(int *)((m) + 0x68C) * 0x184)
#define E32(m, o) (*(int *)(ENTRY(m) + (o)))
#define LAYOUT_COUNT() (*(int *)g_00459724[g_007B9E58])

int func_0030B090(int o);
int func_0030ACE0(int o);
void func_0030B030(int o, int v);
void func_0037FD50(int a, int x, int y, int o);
int func_0030AD80(int o);
int func_0030AE80(int o);
void func_0030ADC0(int o, int v);
int func_002F3770(int a, int o);
void func_001A85D0(float v, int a, float b, int x, int y, int c, int d, int e, int f, int g);
void func_002C80A0(int x, int y, int a, int w, int h, int b, int c);
void func_002C8500(int x, int y, int a, int w, int h, int b, int c);
void func_003B5820(int k, int x, int y, int a, int b, int c);
void func_00381CA0(int a, int x, int y, int k, int b);
void func_003B5480(int x, int y, int a, int w, int b, int c);
void func_001204B0(char *buf, char *fmt, int v);
void func_002C4F40(float s, char *text, int x, int y, int a, int b, int c);
void func_003B53C0(int x, int y, int a, int b, int c, int k);
void func_002CD780(int v, int a, int x, int y, int b, int w, int h, int c);
void func_001ABEA0(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
u8 *func_00365480(void);
u8 *func_0030D7E0(void);
int func_00382620(int k);
u8 *func_00365470(void);
void func_003DC090(int k, int *r);
void func_003DC0E0(int k, int a, int b);
void func_003DB480(int k, int a);
int func_0030E1F0(void);
void func_0030E100(void);
void func_003DB220(int k, int *r);
void func_003DB460(int k, int a);
void func_0032E910(int o);
int func_00330650(int k);
void func_0030E140(int k, int a, int b, int c);
void func_0038B5C0(void);
int *func_003DB900(int k);
int func_0030D7D0(void);
void func_00380E80(int a, int o, int x, int y);
void func_0037FB60(int a, int x, int y, int o, int v);

/* 0x00380810, 0xBC bytes. Draws officer `o` with value func_0030B090 raised by `d` (at most
 * func_0030ACE0), then puts it back. */
void func_00380810(int a, int x, int y, int o, int d)
{
    int v = func_0030B090(o);

    d += v;
    if (func_0030ACE0(o) < d)
        d = func_0030ACE0(o);
    func_0030B030(o, d);
    func_0037FD50(a, x, y, o);
    func_0030B030(o, v);
}

/* 0x003808D0, 0xBC bytes. The same with func_0030AD80. */
void func_003808D0(int a, int x, int y, int o, int d)
{
    int v = func_0030AD80(o);

    d += v;
    if (func_0030AE80(o) < d)
        d = func_0030AE80(o);
    func_0030ADC0(o, d);
    func_0037FD50(a, x, y, o);
    func_0030ADC0(o, v);
}

/* 0x00380990, 0xA4 bytes. Draws officer `o`'s gauge (func_002F3770 out of 10000). */
void func_00380990(int a, int o, int x, int y)
{
    if (o >= 0 && o < 0x19F) {
        float v = (float)func_002F3770(0, o) / 10000.0f;

        func_001A85D0(v, 0, 1.0f, x, y, 0, 2, 0, 0x5C, 1);
    }
}

/* 0x00381FF0, 0xC4 bytes. Draws an item row (`sel`: highlighted). */
void func_00381FF0(int a, int x, int y, int item, int sel)
{
    if (sel == 0)
        func_002C80A0(x, y, 0, 0x96, 0x18, 0x80, 1);
    else
        func_002C8500(x, y, 0, 0x96, 0x18, 0x80, 1);
    func_003B5820(item, x + 10, y, 0, 0x80, 1);
    func_00381CA0(a, x + 0x2C, y, item, 0);
}

/* 0x00382310, 0x9C bytes, matching. */
void func_00382310(int a, int v, int w)
{
    char buf[16];

    func_003B5480(0x158, 0x2E, 0, 200, 0x80, 1);
    func_001204B0(buf, g_00459540, v);
    func_002C4F40(16.0f, buf, 0x178, 0xE, 1, 0, 6);
    func_003B53C0(0x1AC, 8, 0, 0x80, 1, w);
}

/* 0x00382590, 0x90 bytes. */
void func_00382590(u8 *t, int v)
{
    func_002CD780(v, 0, 0x1E2, 0x23, 0, 0xC, 0xC, 0x80);
    func_001ABEA0(t, 7, 0x1E2, 0x1D, 0, 0x80, 0x18, 0);
}

/* 0x00382690, 0xD8 bytes. */
void func_00382690(int x, int y, int a, int w, int h, int b, int k)
{
    u8 *t = g_0045D898 == 0x13 ? func_00365480() : func_0030D7E0();

    if (t != 0)
        func_001ABE40(t, func_00382620(k), x, y, a, w, h, 0x80);
}

/* 0x00383B30, 0x7C bytes. */
int func_00383B30(int k)
{
    switch (k) {
    case 0:
        return 0x359;
    case 1:
        return 0x35E;
    case 2:
        return 0x363;
    case 3:
        return 0x368;
    case 4:
        return 0x36D;
    case 5:
        return 0x372;
    case 6:
        return 0x377;
    case 7:
        return 0x37F;
    case 8:
        return 0x387;
    case 9:
        return 0x38E;
    }
    return 0x395;
}

/* 0x00387A10, 0xAC bytes. */
void func_00387A10(int k, int unused, u8 b)
{
    if (k < 0xB)
        func_001ABE40(func_00365470(), k + 0x11, g_00459650[k][0], g_00459650[k][1], 0,
                      g_00459650[k][2], g_00459650[k][3], b);
}

/* 0x00388140, 0xBC bytes. Opens the selection list window `k`. */
void func_00388140(int k)
{
    int r[5];
    u8 *l = g_00459724[g_007B9E58];

    r[1] = 0x58;
    r[0] = 0;
    r[4] = 0x80;
    r[2] = *(short *)(l + 4) + 0x10;
    r[3] = *(short *)(l + 6);
    func_003DC090(g_00417650[k], r);
    func_003DC0E0(g_00417650[k], 1, *(int *)l);
}

/* 0x003882C0, 0x80 bytes. Sets the entries' availability. */
void func_003882C0(int *v)
{
    int j;

    for (j = 0; j < LAYOUT_COUNT(); j++)
        g_007B9E5D[j] = *v++;
}

/* 0x00388BB0, 0xB4 bytes. The first and last available entries. */
void func_00388BB0(u8 *first, u8 *last)
{
    int a = -1, b = -1, n = LAYOUT_COUNT(), j;

    for (j = 0; j < n; j++) {
        if (g_007B9E5D[j] != 0 && a < 0)
            a = j;
    }
    for (j = n - 1; j >= 0; j--) {
        if (g_007B9E5D[j] != 0 && b < 0)
            b = j;
    }
    *first = a;
    *last = b;
}

/* 0x003891D0, 0xF0 bytes. */
int func_003891D0(u8 *m)
{
    int o = E32(m, 0x80);

    if (STEP(m) == 2) {
        func_003DB480(2, 2);
    } else if (STEP(m) == 1) {
        if (func_0030E1F0() == 2) {
            int r[2];

            func_0030E100();
            r[0] = 0x80;
            r[1] = 0x40;
            func_003DB220(2, r);
            func_003DB460(2, 2);
        }
    } else if (STEP(m) == 0) {
        int v;

        func_0032E910(o);
        v = func_00330650(6);
        if (v != -1)
            func_0030E140(v, o, -1, -1);
    }
    return 0;
}

/* 0x003895B0, 0x8C bytes. */
int func_003895B0(u8 *m)
{
    if (STEP(m) == 1) {
        if (func_0030E1F0() == 2)
            func_0030E100();
    } else if (STEP(m) == 0) {
        func_0030E140(0x2B, E32(m, 0x88), -1, -1);
    }
    return 0;
}

/* 0x00389640, 0x98 bytes. */
int func_00389640(u8 *m)
{
    if (STEP(m) == 1) {
        if (func_0030E1F0() == 2)
            func_0030E100();
    } else if (STEP(m) == 0 && E32(m, 0x84) != 0) {
        func_0030E140(0x2D, E32(m, 0x88), -1, -1);
    }
    return 0;
}

/* A command's window step: closes window `k` at step 2, opens it at (`x`, `y`) at step 0. */
static void window_step(u8 *m, int k, int x, int y)
{
    if (STEP(m) == 2) {
        func_003DB480(k, 2);
    } else if (STEP(m) != 1 && STEP(m) == 0) {
        int r[2];

        r[0] = x;
        r[1] = y;
        func_003DB220(k, r);
        func_003DB460(k, 2);
    }
}

/* 0x003896E0, 0x84 bytes. */
int func_003896E0(u8 *m)
{
    window_step(m, 4, 0x80, 0x40);
    if (STEP(m) == 0)
        func_0038B5C0();
    return 0;
}

/* 0x003897F0, 0x7C bytes. */
int func_003897F0(u8 *m)
{
    window_step(m, 6, 0x80, 0x40);
    return 0;
}

/* 0x00389870, 0x7C bytes. */
int func_00389870(u8 *m)
{
    window_step(m, 7, 0x40, 0x50);
    return 0;
}

/* 0x00389960, 0x7C bytes. */
int func_00389960(u8 *m)
{
    window_step(m, 7, 0x40, 0x50);
    return 0;
}

/* 0x0038AA30, 0x7C bytes. */
int func_0038AA30(u8 *m)
{
    if (STEP(m) != 2) {
        if (STEP(m) == 1) {
            if (func_0030E1F0() == 2)
                func_0030E100();
        } else if (STEP(m) == 0) {
            func_0030E140(0x44, -1, -1, -1);
        }
    }
    return 0;
}

/* 0x0038AAB0, 0xB4 bytes. */
int func_0038AAB0(u8 *m)
{
    if (STEP(m) == 2) {
        func_003DB480(9, 2);
    } else if (STEP(m) == 1) {
        if (func_0030E1F0() == 2) {
            int r[2];

            func_0030E100();
            r[0] = 0x93;
            r[1] = 0x48;
            func_003DB220(9, r);
            func_003DB460(9, 2);
        }
    } else if (STEP(m) == 0) {
        func_0030E140(0x45, -1, -1, -1);
    }
    return 0;
}

/* 0x0038B1E0, 0xBC bytes. */
void func_0038B1E0(u8 *m)
{
    int o = E32(m, 0x80);
    int *p = func_003DB900(2);

    if (STEP(m) == 2)
        func_00380E80(func_0030D7D0(), o, p[0], p[1]);
    else if (STEP(m) == 1)
        func_00380E80(func_0030D7D0(), o, p[0], p[1]);
}

/* 0x0038B2A0, 0xD0 bytes. */
void func_0038B2A0(u8 *m)
{
    int o = E32(m, 0x80);
    int *p = func_003DB900(3);

    if (STEP(m) == 2)
        func_0037FB60(func_0030D7D0(), p[0], p[1], o, E32(m, 0x84));
    else if (STEP(m) == 1)
        func_0037FB60(func_0030D7D0(), p[0], p[1], o, E32(m, 0x84));
}

/* 0x0038B780, 0xB0 bytes. */
void func_0038B780(u8 *m)
{
    int *p = func_003DB900(5);

    if (STEP(m) == 1)
        func_00380E80(func_0030D7D0(), E32(m, 0x80), p[0], p[1]);
    else if (STEP(m) == 0)
        func_00380E80(func_0030D7D0(), E32(m, 0x80), p[0], p[1]);
}

/* 0x0038B9B0, 0xE8 bytes. */
void func_0038B9B0(u8 *m)
{
    int *p = func_003DB900(7);

    if (STEP(m) == 2)
        func_00380810(func_0030D7D0(), p[0], p[1], E32(m, 0x80), E32(m, 0x84));
    else if (STEP(m) == 1)
        func_00380810(func_0030D7D0(), p[0], p[1], E32(m, 0x80), E32(m, 0x84));
    else if (STEP(m) == 0)
        func_0037FD50(func_0030D7D0(), p[0], p[1], E32(m, 0x80));
}

/* More command drawers, the officer list screen and the save screen texts (parts of
 * 0x0038BAA0-0x00392AE8). */

extern u8 g_007B9EA0[], g_007B9ED0[];
extern int g_007B9F3C;
extern void (*g_004176D0[0x16])(void);
extern u8 *g_0045D7D4, *g_0045D7D8;      /* (small data) the list screen textures */
extern char g_00459A10[];                /* the allocations' source name */
extern u8 *g_0043C120[];                 /* message texts ("Checking the memory card ...") */
extern short g_007BA830, g_007BA7F0, g_007BA7D0, g_007BA7D4;
extern u8 *g_007BA7E0;

void func_0037E9F0(int a, int k, int x, int y, int b, int c);
u8 *func_0019FBC0(int k);
int func_001A11F0(int a, int b, int c, int d, u8 *e);
void func_003DF970(int a, u8 *b, int c, int d, u8 *e);
int func_0030D810(void);
void func_003DFD80(int a, int b, int c, int x, int y, int d, u8 *e, u8 *f);
u8 *func_0038C6E0(void);
int func_0030AB90(void);
void func_003A9510(int *list, int n, int a);
void func_003A9010(int v);
int func_003635F0(void);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, char *name, int line);
int func_00102960(int a);
void func_003A5C40(int k);
void func_003A5FA0(int a, int b, int c, int d);
void func_003A9AF0(int v);
void func_0038FA80(int k, int on);
int func_0039FEE0(int k);
u8 *func_00390940(void);
u8 *func_0038FB10(void);
void func_003B24F0(void);
void func_003BCDD0(void);
void func_003BD230(void);
u8 *func_00391250(void);
void func_00376100(int a, int b, int c);
void func_001A7DC0(u8 *text, int a, int b);
char *func_00372780(int k);
void func_002C7310(int x, int y, int a, int w, int h, int b, int c);
void func_002C4C50(float s, char *text, int x, int y, int w, int a, int b, int c);
char *func_002F2970(int o);
char *func_003727B0(int k);
char *func_003728A0(int k);

/* 0x0038BAA0, 0xA4 bytes. */
void func_0038BAA0(u8 *m)
{
    int k = *(int *)(m + 8);
    u8 *p = (u8 *)func_003DB900(8);

    if (STEP(m) == 1)
        func_0037E9F0(func_0030D7D0(), k, 0xB4, 0x4A, *(int *)(p + 0x10), 1);
    else if (STEP(m) == 0)
        func_0037E9F0(func_0030D7D0(), k, 0xB4, 0x4A, *(int *)(p + 0x10), 1);
}

/* 0x0038BE00, 0x90 bytes, matching. */
void func_0038BE00(int a, int b, int c)
{
    int v = *(int *)func_0019FBC0(a);
    int *q = (int *)func_0019FBC0(a);
    int r = func_001A11F0(b, a, c + *q, v, g_007B9EA0);

    func_003DF970(a, g_007B9ED0, c, r, g_007B9EA0);
}

/* 0x0038C240, 0x108 bytes. */
void func_0038C240(u8 *m)
{
    int *p = func_003DB900(9);

    g_007B9F3C = 0x1E;
    if (STEP(m) == 2)
        func_003DFD80(E32(m, 0x84), func_0030D7D0(), func_0030D810(), p[0], p[1], 1, g_007B9EA0, g_007B9ED0);
    else if (STEP(m) == 1)
        func_003DFD80(E32(m, 0x84), func_0030D7D0(), func_0030D810(), p[0], p[1], 1, g_007B9EA0, g_007B9ED0);
}

/* 0x0038C370, 0x8C bytes. */
int func_0038C370(int v)
{
    if (v == 0xF || v == 0x13 || v == 0x12 || v == 0x11 || v == 5 || v == 7 || v == 6 || v == 2
        || v == 4 || v == 3)
        return 1;
    return 0;
}

/* 0x0038C800, 0x68 bytes. Draws the current command's page. */
void func_0038C800(void)
{
    u8 *m = func_0038C6E0();
    int k = E32(m, 0x7C);

    if (k < 0x16)
        g_004176D0[k]();
}

/* 0x0038C870, 0x9C bytes. Shows the provinces flagged in `p` on the map. */
void func_0038C870(u8 *p)
{
    int list[28], n = 0, f;

    for (f = 0; f < func_0030AB90(); f++) {
        if (*(int *)(p + 0x14 + f * 4) != 0)
            list[n++] = f;
    }
    func_003A9510(list, n, 0);
    func_003A9010(1);
}

/* 0x0038D180, 0xD4 bytes. */
int func_0038D180(int a, int b)
{
    if (a == 2) {
        if (func_003635F0() == 0)
            return b == 0 ? 8 : 0xD;
        return b == 0 ? 0xD : 8;
    }
    if (a == 1)
        return 10;
    if (a == 0) {
        if (func_003635F0() == 0)
            return b == 0 ? 0xD : 8;
        return b == 0 ? 8 : 0xD;
    }
    return 10;
}

/* 0x0038F4B0, 0xA8 bytes, matching. Loads the officer list screen. */
void func_0038F4B0(void)
{
    g_0045D7D4 = 0;
    g_0045D7D8 = 0;
    g_0045D7D4 = func_001026D0(1, 0x81, 0, 1, 0, 0, g_00459A10, 0x2F);
    func_00102960(1);
    g_0045D7D8 = func_001026D0(1, 0x82, 0, 1, 0, 0, g_00459A10, 0x33);
    func_00102960(1);
    func_003A5C40(10);
    func_003A5FA0(1, 1, 0, 1);
    func_003A9AF0(0);
}

/* 0x0038F9D0, 0x84 bytes. */
void func_0038F9D0(void)
{
    int k;

    for (k = 0; k < 0x1E; k++) {
        if (k < 0x19)
            func_0038FA80(k, 1);
        else if (func_0039FEE0(k) == 0)
            func_0038FA80(k, 0);
        else
            func_0038FA80(k, 1);
    }
}

/* 0x003906F0, 0x6C bytes, matching. */
void func_003906F0(void)
{
    u8 *m = func_00390940();

    func_0038FB10();
    func_003B24F0();
    if (*(int *)(m + 0x8E6C) == 3)
        func_003BCDD0();
    else if (*(int *)(m + 0x8E6C) == 4)
        func_003BD230();
}

/* 0x00391CC0, 0xD8 bytes. The save screen's title and help. */
void func_00391CC0(void)
{
    u8 *s = func_00391250();
    int v = *(int *)(s + 0x94), a, b, c = -1, w;

    if (v < 0x1C) {
        a = 5;
        b = 0xF;
    } else if (v < 0x1B || v > 0x32) {
        a = -1;
        b = -1;
    } else {
        a = 6;
        b = 0x10;
    }
    w = *(int *)(s + 4);
    if (w == 4)
        c = 0x16;
    else if (w == 3 || w == 2)
        c = 0x15;
    else if (w != 1 && w == 0)
        b = -1;
    func_00376100(a, b, c);
}

/* 0x00391DA0, 0xB8 bytes. The save screen's help line. */
void func_00391DA0(void)
{
    u8 *s = func_00391250();
    int w = *(int *)(s + 4), k = 0x116;

    if (w == 4)
        k = 0x194;
    else if (w == 3)
        k = 0x193;
    else if (w == 2)
        k = 0x192;
    else if (w != 1 && w == 0 && *(int *)(s + 0x34) == 0)
        k = 0x191;
    func_001A7DC0(g_0043C120[k], 0x80, 2);
}

/* 0x003923A0, 0x94 bytes. */
void func_003923A0(void)
{
    u8 *s = func_00391250();
    char *t = func_00372780(*(int *)(s + 8));
    int x = g_007BA830;

    if (x > 0x10)
        x = 0x10;
    func_002C7310(x + 10, 0x3C, 0, 0xA4, 0x18, 0x80, 0);
    func_002C4C50(20.0f, t, x + 0x1C, 0x3F, 0x80, 1, 0, 6);
}

/* 0x00392790, 0xB4 bytes. */
void func_00392790(int alt)
{
    u8 *s = func_00391250();
    int o = *(int *)(s + 0x94);
    char *t;

    func_002C7310(g_007BA7F0, 0x24, 0, 0xA8, 0x18, 0x80, 0);
    if (alt == 0)
        t = func_002F2970(o);
    else
        t = func_003727B0(*(int *)(s + 0x94) - 0x1C);
    func_002C4C50(20.0f, t, g_007BA7F0 + 8, 0x28, 0x98, 2, 0, 6);
}

/* 0x00392A10, 0xD8 bytes. */
void func_00392A10(void)
{
    u8 *s = func_00391250();
    char *t = func_003728A0(*(int *)(s + 0xC));
    int x = g_007BA7D0 - (-(g_007BA7E0[0x13] - 10) * g_007BA7D4) / 10;

    if (x > 0x10)
        x = 0x10;
    func_002C7310(x + 0x18, 0x58, 0, 0xB8, 0x18, 0x80, 0);
    func_002C4C50(20.0f, t, x + 0x30, 0x5A, 0x88, 1, 0, 6);
}

/* Item rows, gauges and two more command steps (0x00381DF0, 0x00382410, 0x00383050,
 * 0x00389E40, 0x0038A8F0, 0x0038AB80). */

extern int g_0056CCA4[4];                /* the text style: colours */
extern float g_0056CCC0[2];              /* the text style: sizes */
extern char g_00459590[], g_00459500[];
extern u32 g_00459910, g_00459914;
extern u8 g_00459870[][0x14];
extern int g_007B9F30, g_007B9F38;

int *func_002FC2C0(void);
char *func_002F8DE0(int f);
char *func_002F2890(int o);
void func_00120B78(char *to, const char *from, int n);
void func_00146B40(char *text, int x, int y, int w, int h, int a, int b);
void func_00146270(char *text, int x, int y, int a, int b);
void func_003DC180(int k, int a, int *r);
u8 *func_001050F0(void);
void func_00105230(u8 *p, int a);
void func_003B5970(int x, int y, int a, int w, int h, int b, int c);
u8 *func_00106F10(u8 *t);
u8 func_003A60F0(u32 v);
int func_002FB2A0(int o);
int func_002F9060(int f);
int func_002F8F20(int f);
void func_0037DDD0(int a, int b, int c, int d);

static void text_style(int col, float size)
{
    g_0056CCA4[0] = col;
    g_0056CCA4[1] = col;
    g_0056CCA4[2] = col;
    g_0056CCA4[3] = col;
    g_0056CCC0[0] = size;
    g_0056CCC0[1] = size;
}

/* 0x00381DF0, 0x1F8 bytes. Draws an item row with its target's name (items 0x2D, 0x34, 0x37). */
void func_00381DF0(int a, int x, int y, int item, int sel, int w)
{
    u8 *m = (u8 *)func_002FC2C0()[0x1AB];
    char buf[64];

    if (sel == 0)
        func_002C80A0(x, y, 0, 0x118, 0x18, 0x80, 1);
    else
        func_002C8500(x, y, 0, 0x118, 0x18, 0x80, 1);
    func_003B5820(item, x + 10, y, 0, 0x80, 1);
    func_00381CA0(a, x + 0x2C, y, item, w);
    buf[0] = 0;
    if (item == 0x2D)
        func_00120B78(buf, func_002F8DE0(*(int *)(m + 0x10)), 0x40);
    else if (item == 0x34)
        func_00120B78(buf, func_002F2890(*(int *)(m + 0x14)), 0x40);
    else if (item == 0x37)
        func_00120B78(buf, func_002F8DE0(*(int *)(m + 0x18)), 0x40);
    text_style(6, 16.0f);
    func_00146B40(buf, x + 0x90, y + 4, 0x7A, 0x10, 1, 0);
    text_style(5, 16.0f);
}

/* 0x00382410, 0x180 bytes. Draws window 1's rank stars (`n` of 5 lit). */
void func_00382410(u8 *t, int n)
{
    int r[2], j;
    u8 *p;

    func_003DC180(1, 0, r);
    func_003B5480(r[0] - 0x14, r[1] + 0x16, 0, 0xB8, 0x80, 1);
    func_001ABEA0(t, 7, r[0], r[1], 0, 0x80, 0x18, 0);
    p = func_001050F0();
    *(unsigned long long *)(p + 0x10) = 0x13C00000009ULL;
    *(unsigned long long *)(p + 0x18) = 9;
    func_00105230(p, 1);
    r[0] += 0x4A;
    for (j = 0; j < 5; j++) {
        func_001ABEA0(t, n <= j ? 0xD2 : 0xD3, r[0], r[1] + 4, 0, 0x10, 0x10, 0);
        r[0] += 0xC;
    }
    p = func_001050F0();
    *(unsigned long long *)(p + 0x10) = 0;
    *(unsigned long long *)(p + 0x18) = 9;
    func_00105230(p, 1);
}

/* 0x00383050, 0x1E4 bytes. Draws a value box (`v` -1: the empty text). */
void func_00383050(u8 *t, int x, int y, int a, int b, int v)
{
    char buf[16];

    func_003B5970(x, y, a, 0xD0, 0x14, 0x80, b);
    func_001ABEA0(t, 7, x + 0x18, y - 2, a, 0x80, 0x18, 0);
    if (v == -1) {
        func_001204B0(buf, g_00459590, 0);
        text_style(5, 12.0f);
        func_00146270(buf, x + 0xA1, y + 4, 1, 0);
        text_style(5, 16.0f);
    } else {
        func_001204B0(buf, g_00459500, v);
        func_002CD780(v, 0, x + 0xA1, y + 4, 0, 0xC, 0xC, 0x80);
        func_001ABEA0(t, 7, x + 0xA0, y - 2, a, 0x80, 0x18, 0);
    }
}

/* 0x00389E40, 0x150 bytes. Colours the map texture's palette: all provinces (`k` -1), or the
 * first 3-5 provinces of route `k`. */
void func_00389E40(u8 *m, u8 *t, int k)
{
    int n = E32(m, 0xB8), j;
    u8 *img, *pal;

    n = n < 4 ? 3 : n < 6 ? 4 : 5;
    img = func_00106F10(t + *(int *)(t + 8) * *(int *)(t + 0xA78));
    pal = img + *(u16 *)(img + 0xC) + *(int *)(img + 8);
    if (k == -1) {
        u32 v;

        for (v = 1; (int)v < 0x1B; v++)
            *(u32 *)(pal + func_003A60F0(v & 0xFF) * 4) = g_00459910;
    } else {
        for (j = 0; j < n; j++)
            *(u32 *)(pal + func_003A60F0(g_00459870[k][j * 4]) * 4) = g_00459914;
    }
}

/* 0x0038A8F0, 0x138 bytes. A command step (messages 0x36-0x39 by the item, window 1). */
int func_0038A8F0(u8 *m)
{
    int o = E32(m, 0x80), v = E32(m, 0x84), k = 0x36;

    if (v == 0x62)
        k = 0x38;
    else if (v == 0x61)
        k = 0x39;
    else if (v == 99)
        k = 0x37;
    if (STEP(m) == 2) {
        func_003DB480(1, 2);
    } else if (STEP(m) == 1) {
        if (func_0030E1F0() == 2) {
            int r[2];

            func_0030E100();
            r[0] = 0x40;
            r[1] = 0x50;
            func_003DB220(1, r);
            func_003DB460(1, 2);
        }
    } else if (STEP(m) == 0 && func_002FB2A0(o) != 0) {
        func_0030E140(k, func_002F8F20(o), -1, -1);
    }
    return 0;
}

/* 0x0038AB80, 0x1E0 bytes. Draws a gold count moving into the force's purse over 30 frames. */
void func_0038AB80(u8 *m)
{
    int f = *(int *)(m + 4);
    int *e = (int *)(ENTRY(m) + 0x80);
    u8 *p = (u8 *)func_003DB900(0);

    g_007B9F3C = 0x1E;
    if (STEP(m) == 2) {
        g_007B9F38 = 0x1E;
        g_007B9F30 = 0;
        func_0037DDD0(func_0030D7D0(), *(int *)(p + 0x10), 0, e[0] / 10 + func_002F9060(f));
    } else if (STEP(m) == 1) {
        int v = e[0], t;

        g_007B9F30 = 1;
        g_007B9F38++;
        t = v * g_007B9F38 / 0x1E;
        if (t <= v)
            v = t;
        func_0037DDD0(func_0030D7D0(), *(int *)(p + 0x10), e[0] - v, v / 10 + func_002F9060(f));
    } else if (STEP(m) == 0) {
        g_007B9F30 = 0;
        g_007B9F38 = 0;
        func_0037DDD0(func_0030D7D0(), *(int *)(p + 0x10), e[0], func_002F9060(f));
    }
}

/* Rising value drawers and the gallery lists (0x0038BB50, 0x0038BCA0, 0x0038C0F0, 0x0038DE60). */

void func_0037ED80(int a, int x, int y, int f, int *v, int b, int c);
int func_002F9390(int f, int j);
u8 *func_0038DC40(void);
int func_003A0040(int k);
int func_0039E650(int k);

/* 0x0038BB50, 0x148 bytes. Draws an officer value rising by the command's gain over 10 frames. */
void func_0038BB50(u8 *m)
{
    int *e = (int *)(ENTRY(m) + 0x80);
    int *p = func_003DB900(7);

    g_007B9F3C = 10;
    if (STEP(m) == 2) {
        g_007B9F38 = 10;
        g_007B9F30 = 0;
        func_003808D0(func_0030D7D0(), p[0], p[1], e[0], e[1]);
    } else if (STEP(m) == 1) {
        g_007B9F30 = 1;
        g_007B9F38++;
        func_003808D0(func_0030D7D0(), p[0], p[1], e[0], e[1] * g_007B9F38 / g_007B9F3C);
    } else if (STEP(m) == 0) {
        g_007B9F38 = 0;
        g_007B9F30 = 0;
        func_0037FD50(func_0030D7D0(), p[0], p[1], e[0]);
    }
}

/* 0x0038BCA0, 0x154 bytes. */
void func_0038BCA0(u8 *m)
{
    int *p = func_003DB900(9);

    g_007B9F3C = 0x1E;
    if (STEP(m) == 2 || STEP(m) == 1 || STEP(m) == 0)
        func_003DFD80(E32(m, 0x84), func_0030D7D0(), func_0030D810(), p[0], p[1], 1, g_007B9EA0, g_007B9ED0);
}

/* 0x0038C0F0, 0x13C bytes. Draws force `f`'s three values. */
void func_0038C0F0(u8 *m)
{
    int f = E32(m, 0x80), v[8], j;
    int *p = func_003DB900(1);

    if (f < 0 || f >= func_0030AB90())
        return;
    for (j = 0; j < 3; j++) {
        v[j] = func_002F9390(f, j);
        v[j + 3] = 0;
    }
    if (STEP(m) == 2)
        func_0037ED80(func_0030D7D0(), p[0], p[1], f, v, 0, 0);
    else if (STEP(m) == 1)
        func_0037ED80(func_0030D7D0(), p[0], p[1], f, v, 0, 0);
}

/* 0x0038DE60, 0x124 bytes. Builds the gallery's officer lists: the seen officers (then the
 * custom ones), and the seen generic ones. */
void func_0038DE60(void)
{
    u8 *q = func_0038DC40();
    int *n1 = (int *)(q + 0x4E68), *n2 = (int *)(q + 0x54EC);
    u32 o;

    *(int *)(q + 0x5B6C) = 0;
    *n1 = 0;
    for (o = 0; o < 400; o++) {
        if (func_003A0040(o) != 0)
            ((u32 *)(q + 0x47EC))[(*n1)++] = o;
    }
    *n2 = 0;
    for (o = 0; o < 0x19F; o++) {
        if (o > 0x1B && (o < 400 || o > 0x19E) && func_003A0040(o) != 0)
            ((u32 *)(q + 0x4E70))[(*n2)++] = o;
    }
    *(int *)(q + 0x4E6C) = *n1;
    for (o = 400; o < 0x19F; o++) {
        if (func_0039E650(o - 400) != 0)
            ((u32 *)(q + 0x47EC))[(*n1)++] = o;
    }
}

extern int g_004169D0[];
extern u8 *g_005BA6A0;
int func_002F27D0(int o);
char *func_00372580(int k);
void func_0037E480(int a, int k, int x, int y, int z, char *t, int b, int c);

/* 0x0037DA70, 0x40 bytes. Officer `o`'s look kind. */
u8 func_0037DA70(int o)
{
    return g_005BA6A0[func_002F27D0(o) * 0x2C + 6];
}

/* 0x0037DAB0, 0x18 bytes, matching. */
int func_0037DAB0(int k)
{
    return g_004169D0[k];
}

/* 0x0037E950, 0x94 bytes. Draws command `k`'s label (0x65 uses text 0x7F). */
void func_0037E950(int a, int k, int x, int y, int z)
{
    func_0037E480(a, k, x, y, z, func_00372580(k == 0x65 ? 0x7F : k), 0, 0);
}

/* 0x0037EAA0, 0x94 bytes. */
void func_0037EAA0(int a, int k, int x, int y, int z)
{
    func_0037E480(a, k, x, y, z, func_00372580(k == 0x65 ? 0x7F : k), 0, 0);
}
