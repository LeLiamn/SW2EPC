/*
 * event_test_menu.c - a menu listing the Empire story events by officer and playing one (from
 * 0x003B0340; a test menu?). State block 0x003B2000 (0x600 bytes at 0x007BAF10: +0 officer, +4
 * event, +8 result, +0xC, +0x10 the officers (0x1D), +0x84 the events of the chosen officer,
 * +0x5F4/+0x5F6 cursor and first line of the officer list, +0x5F8/+0x5FA of the event list,
 * +0x5FC/+0x5FE their counts). Sliding windows at 0x007BAEF0 and 0x007BAED0. Original file name
 * unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A sliding window: position, size, speed, alpha, flags (bit 0 sliding), its animation. */
typedef struct {
    short x, y, w, h;
    float speed;
    u8 alpha;
    u8 flags;
    u8 pad[2];
    u8 *anim;
} Slide;

extern Slide g_007BAEF0, g_007BAED0;
extern u8 g_007BAF10[0x600];
extern int g_0045D7F0, g_0045D7F4, g_0045D7F8;   /* (small data) */
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;
extern u8 g_00500764, g_00500765;
extern u16 g_0050074C, g_0050074E;
extern u8 *g_0043C77C;

#define PAD1_PRESSED() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074C)
#define PAD1_REPEAT() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074E)
#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))

#define ST_INT(s, o) (*(int *)((s) + (o)))
#define ST_SHORT(s, o) (*(short *)((s) + (o)))

int func_0034A740(void);
void func_0034ED90(int o, short *out);
void func_00191200(float *out, int p);
u8 *func_003B2000(void);
int func_003B0470(int o, int k);
char *func_003B0BD0(int o);
char *func_003B0C10(int k);
void func_00146B40(char *t, int x, int y, int w, int h, int a, int b);
u8 *func_002EE5B0(void);
u8 *func_002EE5C0(void);
int func_001AE550(float f, u8 *anim, Slide *box, u8 *alpha, int a);
int func_002ED160(void);
void func_002C80A0(int x, int y, int a, int w, int h, int c, int d);
void func_002C8500(int x, int y, int a, int w, int h, int c, int d);
void func_002C7310(int x, int y, int a, int w, int h, int c, int d);
void func_001A3460(int x, int y, int a, int b, int c, int d, int e, int f);
void func_002C4C50(float s, char *t, int x, int y, int w, int a, int b, int col);
void func_00118850(void *p, int n);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_00102990(void);
void func_003B0DF0(void);
void func_003B0DA0(void);
int func_003A1C60(int k);
void func_0032EFC0(void);
int func_00330320(int k, int a);
void func_0023A3D0(void);
void func_0032F670(void);
void func_0032F5A0(void);
void func_001A7DC0(u8 *t, int a, int b);
void func_00102960(int a);
void func_001265F0(int a, int b);
void func_0032E870(void);

/* 0x003B0340, 0x30 bytes. */
int func_003B0340(u8 *o)
{
    if (*(int *)(o + 0x10) == 0)
        return 0;
    return func_0034A740();
}

/* 0x003B0370, 0xBC bytes. Whether unit `u` stands in the map cell of `o` (5000-unit cells). */
int func_003B0370(u8 *o, int u)
{
    short cell[2];
    float pos[3];
    u8 c[2];

    if (o == 0 || u == 0)
        return 0;
    func_0034ED90(u, cell);
    func_00191200(pos, *(int *)(o + 0x14) + 0x40);
    c[0] = (char)((int)pos[0] / 5000);
    c[1] = (char)((int)pos[1] / 5000);
    return cell[0] == (short)(c[0] | c[1] << 8);
}

/* 0x003B0A40, 0x7C bytes. The officer list: 0..0x1C. */
void func_003B0A40(void)
{
    u8 *s = func_003B2000();
    int k;

    for (k = 0; k < 0x1D; k++)
        ST_INT(s, 0x10 + k * 4) = k;
    ST_SHORT(s, 0x5FC) = 0x1D;
}

/* 0x003B0AC0, 0xD0 bytes. The event list of officer `o`. */
void func_003B0AC0(int o)
{
    u8 *s = func_003B2000();
    int k;

    ST_SHORT(s, 0x5FE) = 0;
    for (k = 0; k < 0x15C; k++)
        ST_INT(s, 0x84 + k * 4) = 0;
    for (k = 0x1B; k < 0x177; k++) {
        if (func_003B0470(o, k) != 0) {
            ST_INT(s, 0x84 + ST_SHORT(s, 0x5FE) * 4) = k;
            ST_SHORT(s, 0x5FE)++;
        }
    }
}

/* The x of line `i` of a sliding list (lines slide in one after another). */
#define LINE_X(sl, i) ((sl).x - (sl).w * ((i) - ((sl).anim[0x13] - 10)) / 10)

/* 0x003B0C70, 0x124 bytes. Draws officer line `i`. */
void func_003B0C70(int o, int i)
{
    int x = LINE_X(g_007BAEF0, i * 2);

    if (x > 0x10)
        x = 0x10;
    FONT_COLOUR(6);
    g_0056CCC0 = 20.0f;
    g_0056CCC4 = 20.0f;
    func_00146B40(func_003B0BD0(o), x + 0x10, i * 0x18 + 0x5A, 0x98, 0x14, 2, 0);
    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    FONT_COLOUR(5);
}

/* Steps a sliding window; when it has arrived, keeps its step at 0x1C. */
static void slide_step(Slide *w, u8 *anim)
{
    int b;

    w->anim = anim;
    b = func_001AE550(w->speed, anim, w, &w->alpha, 0);
    w->flags = (w->flags & 0xFE) | (b & 1);
    if (b & 1) {
        int t = func_002ED160();

        if (t < 0x1C) {
            w->flags &= 0xFE;
            w->anim[0x13] = t;
        } else {
            w->anim[0x13] = 0x1C;
        }
    }
}

/* 0x003B0E40, 0x27C bytes. Draws the officer list. */
void func_003B0E40(void)
{
    u8 *s = func_003B2000();
    short n = ST_SHORT(s, 0x5FC), shown = n > 9 ? 9 : n;
    int i, x, y;

    slide_step(&g_007BAEF0, func_002EE5B0());
    for (i = 0, y = 0x58; i < 9; i++, y += 0x18) {
        int o;

        x = LINE_X(g_007BAEF0, i * 2);
        if (x > 0x10)
            x = 0x10;
        o = ST_INT(s, 0x10 + (ST_SHORT(s, 0x5F6) + i) * 4);
        func_002C80A0(x, y, 0, 0xB8, 0x18, 0x80, 0);
        func_003B0C70(o, i);
        if (i == ST_SHORT(s, 0x5F4))
            func_002C8500(x, ST_SHORT(s, 0x5F4) * 0x18 + 0x58, 0, 0xB8, 0x18, 0x80, 1);
    }
    if (g_007BAEF0.flags & 1)
        func_001A3460(200, 0x50, 0, 0x10, 0xEA, 0x80, n, shown);
}

/* 0x003B10C0, 0x25C bytes. Draws the event list. */
void func_003B10C0(void)
{
    u8 *s = func_003B2000();
    short n = ST_SHORT(s, 0x5FE), shown = n > 9 ? 9 : n;
    int i, x, y;

    for (i = 0, y = 0x74; i < 9; i++, y += 0x18) {
        int k;

        x = LINE_X(g_007BAED0, i * 2);
        if (x > 0x10)
            x = 0x10;
        k = ST_INT(s, 0x84 + (ST_SHORT(s, 0x5FA) + i) * 4);
        if (k != 0) {
            func_002C80A0(x, y, 0, 0x118, 0x18, 0x80, 0);
            FONT_COLOUR(6);
            g_0056CCC0 = 20.0f;
            g_0056CCC4 = 20.0f;
            func_00146B40(func_003B0C10(k), x + 8, y + 2, 0x108, 0x14, 2, 0);
            g_0056CCC0 = 16.0f;
            g_0056CCC4 = 16.0f;
            FONT_COLOUR(5);
            if (i == ST_SHORT(s, 0x5F8))
                func_002C8500(x, y, 0, 0x118, 0x18, 0x80, 1);
        }
    }
    if ((g_007BAED0.flags & 1) && n > 9)
        func_001A3460(0x128, 0x6C, 0, 8, 0xE8, 0x80, n, shown);
}

/* 0x003B1320, 0x14C bytes. Draws the event page: the officer's name and the event list. */
void func_003B1320(void)
{
    u8 *s = func_003B2000();
    int x;

    slide_step(&g_007BAED0, func_002EE5C0());
    x = g_007BAED0.x;
    func_002C7310(x + 0x14, 0x50, 0, 0xA8, 0x18, 0x80, 0);
    func_002C4C50(20.0f, func_003B0BD0(ST_INT(s, 0)), x + 0x1C, 0x52, 0x98, 1, 0, 6);
    func_003B10C0();
}

/* 0x003B1490, 0x48 bytes, matching. */
void func_003B1490(u8 *s, int a)
{
    func_00118850(s, 0x600);
    ST_INT(s, 4) = 0x1B;
    ST_INT(s, 8) = 5;
    ST_INT(s, 0xC) = a;
}

/* Moves a 9-line list cursor up (wrapping to the end). */
static void list_up(u8 *s, int cur, int top, short n)
{
    short c = ST_SHORT(s, cur);

    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
    ST_SHORT(s, cur) = c - 1;
    if ((short)(c - 1) < 0) {
        if (ST_SHORT(s, top) < 1) {
            if (n / 9 < 1) {
                ST_SHORT(s, cur) = n % 9 - 1;
                ST_SHORT(s, top) = 0;
            } else {
                ST_SHORT(s, cur) = 8;
                ST_SHORT(s, top) = n - 9;
            }
        } else {
            ST_SHORT(s, cur) = c;
            ST_SHORT(s, top)--;
        }
    }
}

/* Moves it down (wrapping to the start). */
static void list_down(u8 *s, int cur, int top, short n)
{
    short c;

    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
    c = ++ST_SHORT(s, cur);
    if (c > 8 || n <= c) {
        if (ST_SHORT(s, top) + c < n) {
            ST_SHORT(s, cur)--;
            ST_SHORT(s, top)++;
        } else {
            ST_SHORT(s, cur) = 0;
            ST_SHORT(s, top) = 0;
        }
    }
}

/* The list keys: 1 confirm, 2 cancel, 0 otherwise (moving the cursor). */
static int list_keys(u8 *s, int cur, int top, short n)
{
    u32 pr = PAD1_PRESSED(), rp = PAD1_REPEAT();

    if (pr & 0x1000) {
        list_up(s, cur, top, n);
    } else if (pr & 0x4000) {
        list_down(s, cur, top, n);
    } else if (rp & 0x1000) {
        if (0 < ST_SHORT(s, cur) + ST_SHORT(s, top))
            list_up(s, cur, top, n);
    } else if (rp & 0x4000) {
        if (ST_SHORT(s, cur) + ST_SHORT(s, top) < n - 1)
            list_down(s, cur, top, n);
    } else if (pr & 0x40) {
        return 1;
    } else if (pr & 0x10) {
        return 2;
    }
    return 0;
}

/* 0x003B14E0, 0x5A8 bytes. The officer list's input. */
void func_003B14E0(void)
{
    u8 *s = func_003B2000();
    int k;

    ST_INT(s, 8) = 5;
    if (!(g_007BAEF0.flags & 1))
        return;
    k = list_keys(s, 0x5F4, 0x5F6, ST_SHORT(s, 0x5FC));
    if (k == 1) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        ST_INT(s, 0) = ST_INT(s, 0x10 + (ST_SHORT(s, 0x5F6) + ST_SHORT(s, 0x5F4)) * 4);
        ST_INT(s, 4) = -1;
        for (k = 0x1B; k < 0x177; k++) {
            if (func_003B0470(ST_INT(s, 0), k) != 0) {
                ST_INT(s, 4) = k;
                break;
            }
        }
        if (ST_INT(s, 4) == -1)
            ST_INT(s, 4) = 0x1B;
        g_0045D7F8 = 1;
        g_0045D7F4 = 1;
        func_003B0AC0(ST_INT(s, 0));
        ST_SHORT(s, 0x5F8) = 0;
        ST_SHORT(s, 0x5FA) = 0;
        func_003B0DF0();
    } else if (k == 2) {
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        if (g_0045D7F0 == 0)
            func_00102990();
        ST_INT(s, 8) = 0;
    }
}

/* 0x003B1A90, 0x570 bytes. The event list's input: plays the chosen event. */
void func_003B1A90(void)
{
    u8 *s = func_003B2000();
    int k, e;

    if (!(g_007BAED0.flags & 1))
        return;
    k = list_keys(s, 0x5F8, 0x5FA, ST_SHORT(s, 0x5FE));
    if (k == 1) {
        if (g_0045D7F0 == 0) {
            func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
            return;
        }
        e = ST_INT(s, 0x84 + (ST_SHORT(s, 0x5FA) + ST_SHORT(s, 0x5F8)) * 4);
        if (func_003A1C60(e - 0x87) == 0) {
            func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
        } else {
            ST_INT(s, 4) = e;
            func_0032EFC0();
            func_00330320(ST_INT(s, 4), 1);
            g_0045D7F4 = 2;
        }
    } else if (k == 2) {
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        g_0045D7F4 = 0;
        func_003B0DA0();
    }
}

/* 0x003B2010, 0x94 bytes. Opens the menu. */
void func_003B2010(void)
{
    g_0045D7F4 = 0;
    func_003B1490(g_007BAF10, 0);
    func_003B0A40();
    func_0023A3D0();
    func_0032F670();
    func_0032F5A0();
    g_007BAEF0.speed = 1.0f;
    g_007BAEF0.flags &= 0xFE;
    g_007BAED0.speed = 1.0f;
    g_007BAED0.flags &= 0xFE;
}

/* 0x003B20B0, 0x34 bytes. Draws the help line unless an event plays. */
void func_003B20B0(void)
{
    if (g_0045D7F4 != 2)
        func_001A7DC0(g_0043C77C, 0x80, 2);
}

/* 0x003B21A0, 0x58 bytes. */
void func_003B21A0(void)
{
    u8 *s = func_003B2000();

    if (ST_INT(s, 0xC) != 0) {
        func_00102990();
        func_00102960(1);
        func_001265F0(0, 1);
        func_0032E870();
        ST_INT(func_003B2000(), 0xC) = 0;
    }
}
