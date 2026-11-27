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
