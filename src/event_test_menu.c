/*
 * event_test_menu.c - a menu listing the Empire story events by officer and playing one (from
 * 0x003B0340; a test menu?). State block 0x003B2000 (0x600 bytes at 0x007BAF10: +0 officer, +4
 * event, +8 result, +0xC, +0x10 the officers (0x1D), +0x84 the events of the chosen officer,
 * +0x5F4/+0x5F6 cursor and first line of the officer list, +0x5F8/+0x5FA of the event list,
 * +0x5FC/+0x5FE their counts). Sliding windows at 0x007BAEF0 and 0x007BAED0. Original file name
 * unknown. From 0x003B24F0: the event scene's choice windows and tabs, sprites of the bank gp
 * 0x0045D7FC, and the Empire ending (0x003B5EA0-0x003B7084).
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

/* ---- The event scene's choice windows (state 0x003B2340: +0x98 mode, +4 the four choices, boxes
 * at +0x9C and +0xEC, 0x14 bytes each: from (x, y, w, h), to (x, y, w, h), alphas, steps, step). */

extern u32 g_0045D7FC;                   /* (small data) the sprite bank */
extern short g_0045B6A0[5][2];
extern u8 *g_0043C5A8;

u8 *func_003B2340(void);
void func_003B2360(short *xy, int k);
void func_003B2390(short *xy, int k);
int func_003B23C0(int k);
u8 *func_00390940(void);
void func_001ABE40(u32 h, int k, int a, int b, int c, int d, int e, int f);
void func_001ABEA0(u32 h, int k, int a, int b, int c, int d, int e, int f);
void func_00383D80(u8 *p);
void func_00384870(u8 *p, int a);
void func_003B5480(int x, int y, int a, int w, int b, int c);
void func_003B34A0(int a);
void func_001A3C20(int x, int y, int a, int w, int h, int b, int c);

static void box_from(u8 *r, short *xy, short w, short h, u8 a0, u8 a1)
{
    ST_SHORT(r, 0) = xy[0];
    ST_SHORT(r, 2) = xy[1];
    ST_SHORT(r, 4) = w;
    ST_SHORT(r, 6) = h;
    ST_SHORT(r, 8) = xy[0];
    ST_SHORT(r, 0xA) = xy[1];
    ST_SHORT(r, 0xC) = w;
    ST_SHORT(r, 0xE) = h;
    r[0x12] = 0;
    r[0x13] = 0;
    r[0x10] = a0;
    r[0x11] = a1;
}

static void box_to(u8 *r, short x, short y, short w, short h, u8 a1, u8 steps)
{
    ST_SHORT(r, 8) = x;
    ST_SHORT(r, 0xA) = y;
    ST_SHORT(r, 0xC) = w;
    ST_SHORT(r, 0xE) = h;
    r[0x11] = a1;
    r[0x12] = steps;
}

/* The choice windows' sizes and alphas by place (0 and 2 middle, 3 far, 1 front). */
static int place_alpha(int i)
{
    return i == 3 ? 0x4C : i == 2 ? 0x60 : i == 1 ? 0x80 : i == 0 ? 0x60 : 0x80;
}
#define W1(i) ((i) == 3 ? 0x5B : (i) == 2 || (i) == 0 ? 0x72 : 0x98)
#define H1(i) ((i) == 3 ? 0x1C : (i) == 2 || (i) == 0 ? 0x24 : 0x30)
#define W2(i) ((i) == 3 ? 0x78 : (i) == 2 || (i) == 0 ? 0x96 : 200)
#define H2(i) ((i) == 3 ? 0x18 : (i) == 2 || (i) == 0 ? 0x1E : 0x28)

/* 0x003B24F0, 0x2E4 bytes. Draws the choices and the chosen one's arrows. */
void func_003B24F0(void)
{
    u8 *g = func_00390940(), *s = func_003B2340();
    int i, lit = 0, v;
    short b[4];
    u8 al;

    if (ST_INT(g, 0x8E6C) != 2)
        return;
    for (i = 0; i < 4; i++) {
        int k = ST_INT(s, 4 + i * 4);

        if (k == -1)
            continue;
        func_001AE550(1.0f, s + 0xEC + i * 0x14, (Slide *)b, &al, 0);
        if (ST_INT(s, 0x98) == 4 && i != 1)
            al = 0;
        func_001ABE40(ST_INT(g, 0x8EBC), func_003B23C0(k), b[0], b[1], 0, b[2], b[3], al);
        if (i == 1)
            lit = func_001AE550(1.0f, s + 0x9C + i * 0x14, (Slide *)b, &al, 0);
        else
            func_001AE550(1.0f, s + 0x9C + i * 0x14, (Slide *)b, &al, 0);
        if (ST_INT(s, 0x98) == 4 && i != 1)
            al = 0;
        func_001ABE40(ST_INT(g, 0x8EBC), k + 0xE, b[0], b[1], 0, b[2], b[3], al);
    }
    al = ST_INT(s, 0x98) == 4 ? 0 : 0x80;
    if (lit == 0) {
        ST_INT(s, 0x154) = 0;
    } else {
        v = ST_INT(s, 0x154) + 1;
        if (v > 8)
            v = 8;
        ST_INT(s, 0x154) = v & 0xFF;
        if ((v & 0xFF) == 8) {
            func_00383D80(g + 0x8E84);
            func_00384870(g + 0x8E84, 1);
        }
        func_003B5480(ST_INT(s, 0x154) * 0x110 / 8 - 0x130, 0x52, 0, 0x110, al, 1);
        func_003B5480(ST_INT(s, 0x154) * 0x18A / 8 - 0x1AA, 0x86, 0, 0x18A, al, 1);
    }
    func_003B34A0(1);
    if (ST_INT(g, 0x8E6C) == 2)
        func_001A7DC0(g_0043C5A8, 0x80, 2);
}

/* 0x003B27E0, 0xC48 bytes. Sets the windows' moves for mode +0x98: 4 open, 2 / 1 turn one way or
 * the other, 3 show. */
void func_003B27E0(void)
{
    u8 *s = func_003B2340(), *r;
    int m = ST_INT(s, 0x98), i, j;
    short p[2];
    u8 a, b;

    if (m == 4) {
        func_003B2390(p, 1);
        box_from(s + 0x100, p, 0x98, 0x30, 0x80, 0x80);
        box_to(s + 0x100, p[0], 0x30, 0x98, 0x30, 0x80, 0xF);
        func_003B2360(p, 1);
        box_from(s + 0xB0, p, 200, 0x28, 0x80, 0x80);
        box_to(s + 0xB0, p[0], 0x30, 200, 0x28, 0x80, 0xF);
    } else if (m == 2) {
        for (i = 0, r = s; i < 4; i++, r += 0x14) {
            j = i == 0 ? 0 : i - 1;
            a = place_alpha(j);
            b = place_alpha(i);
            func_003B2390(p, j);
            box_from(r + 0xEC, p, W1(j), H1(j), i == 0 ? 0 : a, i == 0 ? 0 : a);
            func_003B2390(p, i);
            box_to(r + 0xEC, p[0], p[1], W1(i), H1(i), b, 0xF);
            func_003B2360(p, j);
            box_from(r + 0x9C, p, W2(j), H2(j), i == 0 ? 0 : a, i == 0 ? 0 : a);
            func_003B2360(p, i);
            box_to(r + 0x9C, p[0], p[1], W2(i), H2(i), b, 0xF);
        }
    } else if (m == 1) {
        for (i = 0, r = s; i < 4; i++, r += 0x14) {
            j = i != 3 ? i + 1 : 3;
            a = place_alpha(j);
            b = place_alpha(i);
            func_003B2390(p, j);
            box_from(r + 0xEC, p, W1(j), H1(j), i == 3 ? 0 : a, i == 3 ? 0 : a);
            func_003B2390(p, i);
            box_to(r + 0xEC, p[0], p[1], W1(i), H1(i), b, 0xF);
            func_003B2360(p, j);
            box_from(r + 0x9C, p, W2(j), H2(j), a, a);
            func_003B2360(p, i);
            box_to(r + 0x9C, p[0], p[1], W2(i), H2(i), b, 0xF);
        }
    } else if (m == 3) {
        for (i = 0, r = s; i < 4; i++, r += 0x14) {
            a = place_alpha(i);
            func_003B2390(p, i);
            box_from(r + 0xEC, p, W1(i), H1(i), 0, 0);
            box_to(r + 0xEC, p[0], p[1], W1(i), H1(i), a, 0);
            func_003B2360(p, i);
            box_from(r + 0x9C, p, W2(i), H2(i), 0, 0);
            box_to(r + 0x9C, p[0], p[1], W2(i), H2(i), a, 0);
        }
    }
}

/* 0x003B39A0, 0xC0 bytes. Draws face `k` (0..0x43; 0x43 is face 0) from the face sheet. */
void func_003B39A0(int x, int y, int a, int w, int h, int k)
{
    if (k >= 0 && k < 0x44) {
        if (k == 0x43)
            k = 0;
        else
            k++;
        func_001ABEA0(g_0045D7FC, 0, x, y, 0, w, h, (k % 0x15) * 0x18);
    }
}

/* 0x003B3D50, 0x78 bytes. Draws tab `k` (lit or not). */
void func_003B3D50(int k, int x, int y, int a, int b, int lit)
{
    func_001ABEA0(g_0045D7FC, lit == 0 ? 8 : 9, x, y, a, 0x48, 0x20, 0);
}

/* 0x003B3DD0, 0x98 bytes, matching. Draws the five tabs, `cur` lit. */
void func_003B3DD0(int alpha, int cur)
{
    int k;

    func_001A3C20(0, 0xA0, 0, 0x200, 0x40, 0x80, alpha);
    for (k = 0; k < 5; k++)
        func_003B3D50(k, g_0045B6A0[k][0], g_0045B6A0[k][1], 0, alpha + 1, cur == k);
}

/* ---- Sprites of the bank gp 0x0045D7FC: digits, marks, icons. ---- */

int func_00313B30(int k);
void func_001AB4E0(u8 *a, u8 *b, int x, int y, int z, int w, int h, int u);

#define BANK_SPR(k) ((u8 *)g_0045D7FC + *(int *)((u8 *)g_0045D7FC + 8) * *(int *)((u8 *)g_0045D7FC + 0x10 + (k) * 8))

/* 0x003B4FE0, 0x90 bytes. */
void func_003B4FE0(int k, int x, int y, int z)
{
    int s;

    if (k == 2)
        s = 0x1E;
    else if (k == 1)
        s = 0x1D;
    else if (k == 0)
        s = 0x1C;
    else
        s = x;
    func_001ABEA0(g_0045D7FC, s, x, y, z, 0x14, 0x14, 0);
}

/* 0x003B5070, 0x16C bytes. A level mark by value (< 20, < 50, < 80, more). */
void func_003B5070(int v, int x, int y, int z)
{
    if (v < 0x14)
        func_001ABEA0(g_0045D7FC, 0x17, x, y, z, 0x14, 0x14, 0);
    else if (v < 0x32)
        func_001ABEA0(g_0045D7FC, 0x18, x, y, z, 0x14, 0x14, 0);
    else if (v < 0x50)
        func_001ABEA0(g_0045D7FC, 0x19, x, y, z, 0x14, 0x14, 0);
    else
        func_001ABEA0(g_0045D7FC, 0x1A, x, y, z, 0x14, 0x14, 0);
}

/* 0x003B5300, 0xB4 bytes. */
void func_003B5300(int k, int x, int y, int z)
{
    int s;

    if (k == 3)
        s = 0x14;
    else if (k == 2)
        s = 0x13;
    else if (k == 1)
        s = 0x12;
    else if (k == 0)
        s = 0x11;
    else
        return;
    func_001ABEA0(g_0045D7FC, s, x, y, z, 0x14, 0x14, 0);
}

/* 0x003B53C0, 0x44 bytes. */
void func_003B53C0(int x, int y, int z, int a, int b, int k)
{
    func_001ABE40(g_0045D7FC, k + 0x1F, x, y, z, 0x40, 0x20, a);
}

/* 0x003B5480, 0x114 bytes. A bar of width `w` (two caps and a middle). */
void func_003B5480(int x, int y, int z, int w, int b, int c)
{
    func_001ABEA0(g_0045D7FC, 3, x, y, z, 0x18, 8, 0);
    func_001ABEA0(g_0045D7FC, 3, x + 0x18, y, z, w - 0x30, 8, 0x18);
    func_001ABEA0(g_0045D7FC, 3, x + 0x18 + w - 0x30, y, z, 0x18, 8, 0x20);
}

/* 0x003B5820, 0x80 bytes. The icon of kind `k`. */
void func_003B5820(int k, int x, int y, int z, int a, int b)
{
    func_001ABE40(g_0045D7FC, func_00313B30(k) + 0x2F, x, y, z, 0x20, 0x18, a);
}

/* 0x003B5970, 0x124 bytes. A frame of width `w` (at least 0x20). */
void func_003B5970(int x, int y, int z, int w)
{
    if (w < 0x20)
        w = 0x20;
    func_001ABEA0(g_0045D7FC, 0x49, x, y, z, 0x10, 0x18, 0);
    func_001ABEA0(g_0045D7FC, 0x49, x + 0x10, y, z, w - 0x20, 0x18, 0x10);
    func_001ABEA0(g_0045D7FC, 0x49, x + 0x10 + w - 0x20, y, z, 0x10, 0x18, 0x18);
}

/* 0x003B5AA0, 0x8C bytes. Digit sprite `d` (0..9 = 1..9, 0). */
void func_003B5AA0(int d, int x, int y, int z)
{
    u8 *p = BANK_SPR(0x4A);

    func_001AB4E0(p, p, x, y, z, 0x10, 0x10, d << 4);
}

/* 0x003B5B30, 0x168 bytes. A number up to 999. */
void func_003B5B30(int v, int x, int y, int z)
{
    int r = v, d;

    if (v > 99) {
        d = v / 100 - 1;
        if (v / 100 == 0)
            d = 9;
        func_003B5AA0(d, x, y, z);
        r = v % 100;
    }
    if (v > 9) {
        d = r / 10 - 1;
        if (r / 10 == 0)
            d = 9;
        func_003B5AA0(d, x + 0xC, y, z);
        r = r % 10;
    }
    d = r - 1;
    if (r == 0)
        d = 9;
    func_003B5AA0(d, x + 0x18, y, z);
}

/* 0x003B5D50, 0x98 bytes. */
void func_003B5D50(int k, int x, int y, int z)
{
    u8 *p = BANK_SPR(0x4B + k);

    func_001AB4E0(p, p, x, y, z, 0x20, 0x14, 0);
}

/* 0x003B5E10, 0x78 bytes. */
void func_003B5E10(int k, int x, int y, int z)
{
    if (k >= 0 && k < 3)
        func_001ABEA0(g_0045D7FC, 0x54, x, y, z, 0x38, 0x10, 0);
}

/* ---- The Empire ending (state 0x003B5E90: +4 step, +0x20.. loaded files, +0x514 the cleared
 * player officers (8 x 0x24), +0x634 their marks, +0x654 count, +0x658 cursor, +0x760 timer). ---- */

extern char g_0045B6E8[];                /* this source file's name */
extern char *g_0043C31C;
extern char g_006935DB, g_006935DC;
extern u8 g_0056CCC8[4];

u8 *func_003B5E90(void);
void func_003A5FA0(int a, int b, int c, int d);
void func_001B8F60(int a, int b, int c);
void func_001ABA70(u32 h, int a, int x, int y, int w, int hh, int al, int b);
u32 func_001026D0(int a, int k, int b, int c, int d, int e, const char *file, int line);
void func_0017E010(int m);
void func_0019FC30(void);
u8 *func_0019FBC0(int k);
char *func_00120928(char *to, const char *from);
int func_003294A0(int k);
void func_00329450(int k, int v);
void func_001AE9F0(int a, char *t, int b);
void func_001AFC50(int a);
void func_001037F0(int a);
void func_002DBAC0(int a);
void func_002D8060(int a);
void func_001AFFB0(int a);
int func_002DAC30(void);
void func_002D8160(void);
void func_00118AC0(void *to, const void *from, u32 n);
int func_003F0A00(u8 *p);
void func_003F0800(u8 *p);
int func_003C1850(void);
int func_00327C00(void);
void func_0039FCA0(int a, int b);
int func_00327820(void);
void func_0011ED38(void *p, int v, int n);
void func_003B69A0(void);
int func_0032EEB0(void);
void func_003BA8F0(int k, int a, int b, int c, int d);
int func_0023A9B0(int a, int b);
void func_0023A960(int a);
void func_003BC5E0(void);
void func_003B9760(void);
void func_00102EC0(u32 h);
int func_0030DFA0(void);
char *func_00390760(int k);
char *func_002F2890(int o);
char *func_00372410(int k);
void func_001AEDB0(int a, int b, int c, int d);
void func_001AFEC0(int a);
int func_001204B0(char *to, const char *f, ...);
extern u32 g_7000015C;

/* 0x003B5EA0, 0xCC bytes. Draws the ending picture, fading out over the last 160 frames. */
void func_003B5EA0(void)
{
    u8 *s = func_003B5E90();
    int al = 0x80, t;

    if (ST_INT(s, 0x718) == 0)
        return;
    t = 600 - ST_SHORT(s, 0x760);
    if (t < 0xA0)
        al = (t * 0x80) / 0xA0 & 0xFF;
    if (ST_SHORT(s, 0x760) == 200) {
        func_003A5FA0(0, 0, 0, 0);
        func_001B8F60(0, 6, 1);
    }
    func_001ABA70(ST_INT(s, 0x20), 0, 0, 0, 0x200, 0x180, al, 2);
}

/* 0x003B5F70, 0x104 bytes. Its step: loads it, counts down (start skips to the end). */
int func_003B5F70(void)
{
    u8 *s = func_003B5E90();
    short t;

    if (ST_INT(s, 0x718) == 0) {
        ST_INT(s, 0x20) = func_001026D0(1, 0xD84, 0, 1, 0, 0, g_0045B6E8, 0x44);
        ST_INT(s, 0x718) = 1;
        func_0017E010(0x22);
    }
    t = --ST_SHORT(s, 0x760);
    if (t < 1)
        ST_INT(s, 4) = 0x12;
    if ((PAD1_REPEAT() & 0x800) && ST_SHORT(s, 0x760) > 200)
        ST_SHORT(s, 0x760) = 200;
    return 0;
}

/* 0x003B6080, 0x184 bytes. Copies the marked officers (up to 4) into the four player slots. */
void func_003B6080(void)
{
    u8 *s = func_003B5E90(), *r, *o;
    int n = 0, k, i;

    func_0019FC30();
    for (k = 0; k < 8; k++) {
        if (ST_INT(s, 0x634 + k * 4) == 0)
            continue;
        r = s + k * 0x24;
        func_0019FBC0(n)[4] = r[0x518];
        func_00120928((char *)func_0019FBC0(n) + 0x13, (char *)r + 0x527);
        func_0019FBC0(n)[5] = r[0x519];
        func_0019FBC0(n)[6] = r[0x51A];
        func_0019FBC0(n)[7] = r[0x51B];
        *(int *)func_0019FBC0(n) = ST_INT(r, 0x514);
        func_0019FBC0(n)[8] = r[0x51C];
        func_0019FBC0(n)[9] = r[0x51D];
        for (i = 0; i < 5; i++) {
            o = func_0019FBC0(n);
            o[i + 0xE] = r[i + 0x522];
        }
        func_0019FBC0(n)[10] = r[0x51E];
        func_0019FBC0(n)[0xB] = r[0x51F];
        func_0019FBC0(n)[0xC] = r[0x520];
        o = func_0019FBC0(n);
        n++;
        o[0xD] = r[0x521];
        if (n > 3)
            return;
    }
}

/* 0x003B6210, 0x50 bytes. The number of marked officers. */
int func_003B6210(void)
{
    u8 *s = func_003B5E90();
    int n = 0, k;

    for (k = 0; k < ST_INT(s, 0x654); k++) {
        if (ST_INT(s, 0x634 + k * 4) != 0)
            n++;
    }
    return n;
}

/* 0x003B6260, 0x3BC bytes. Marking the officers to keep (up to 4; the last line is OK). */
void func_003B6260(void)
{
    u8 *s = func_003B5E90();
    int n = 0, k, mv;

    if (ST_INT(s, 0x750) < 1)
        ST_INT(s, 4) = 0xC;
    if (PAD1_REPEAT() & 0x1000) {
        mv = 1;
        if (ST_INT(s, 0x658) == 0) {
            mv = 0;
            if (PAD1_PRESSED() & 0x1000)
                mv = 1;
        }
        if (mv) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            if (--ST_INT(s, 0x658) < 0)
                ST_INT(s, 0x658) = ST_INT(s, 0x654);
        }
    } else if (PAD1_REPEAT() & 0x4000) {
        mv = 1;
        if (ST_INT(s, 0x654) == ST_INT(s, 0x658)) {
            mv = 0;
            if (PAD1_PRESSED() & 0x4000)
                mv = 1;
        }
        if (mv) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            if (ST_INT(s, 0x654) < ++ST_INT(s, 0x658))
                ST_INT(s, 0x658) = 0;
        }
    } else if (PAD1_PRESSED() & 0x40) {
        if (ST_INT(s, 0x654) == ST_INT(s, 0x658)) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_003B6080();
            for (k = 0; k < 8; k++) {
                if (ST_INT(s, 0x634 + k * 4) != 0)
                    n++;
            }
            for (k = 0; k < 2; k++) {
                if (func_003294A0(k) != 4 && n <= func_003294A0(k))
                    func_00329450(k, 4);
            }
            ST_INT(s, 4) = 0xC;
        } else {
            int *m = (int *)(s + 0x634 + ST_INT(s, 0x658) * 4);

            if (*m == 0) {
                if (func_003B6210() < 4) {
                    func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                    *(int *)(s + 0x634 + ST_INT(s, 0x658) * 4) = 1;
                } else {
                    func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
                }
            } else {
                *m = 0;
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
            }
        }
    }
}

/* 0x003B6620, 0x138 bytes. Asks whether to save the cleared data. */
void func_003B6620(void)
{
    u8 *s = func_003B5E90();
    char t[0x100];

    if (ST_INT(s, 0x71C) == 0) {
        g_0056CCC8[0] = g_0056CCC8[1] = g_0056CCC8[2] = g_0056CCC8[3] = 0x80;
        func_001204B0(t, g_0043C31C);
        func_001AE9F0(1, t, 1);
        func_001AFC50(1);
        g_006935DB = 5;
        ST_INT(s, 0x71C) = 1;
    }
    if (g_006935DC == 4) {
        func_001037F0(0);
        if (ST_INT(s, 0x75C) == 6) {
            func_002DBAC0(0);
        } else if (ST_INT(s, 0x75C) == 7) {
            func_002DBAC0(1);
        } else {
            ST_INT(s, 4) = 0xE;
            return;
        }
        func_002D8060(0);
        ST_INT(s, 0x740) = 0;
        ST_INT(s, 4) = 0xD;
    } else if (g_006935DC == 5) {
        ST_INT(s, 4) = 0xE;
    }
    if (ST_INT(s, 4) != 0xC)
        func_001AFFB0(1);
}

/* 0x003B6760, 0x84 bytes, matching. Saving (1 done, 2 failed: asks again). */
void func_003B6760(void)
{
    u8 *s = func_003B5E90();

    if (ST_INT(s, 0x740) == 0)
        ST_INT(s, 0x740) = func_002DAC30();
    if (ST_INT(s, 0x740) == 1) {
        ST_INT(s, 4) = 0xE;
        func_002D8160();
        func_001037F0(1);
    }
    if (ST_INT(s, 0x740) == 2) {
        ST_INT(s, 0x71C) = 0;
        ST_INT(s, 4) = 0xC;
        func_002D8160();
        func_001037F0(1);
    }
}

/* 0x003B67F0, 0x130 bytes. Loads the screen's files and keeps a copy of the player slots. */
void func_003B67F0(void)
{
    u8 *s = func_003B5E90();
    int k;

    ST_INT(s, 0x24) = func_001026D0(1, 0x36, 0, 1, 0, 0, g_0045B6E8, 0x132);
    ST_INT(s, 0x28) = func_001026D0(1, 0x37, 0, 1, 0, 0, g_0045B6E8, 0x133);
    for (k = 0; k < 4; k++)
        func_00118AC0(s + 0x65C + k * 0x24, func_0019FBC0(k), 0x24);
    ST_INT(s, 0x750) = func_003F0A00(s + 0x514);
    func_003F0800(s + 0x514);
    for (k = 0; k < 8; k++)
        ST_INT(s, 0x6EC + k * 4) = ST_INT(s, 0x634 + k * 4);
    for (k = 0; k < 2; k++)
        ST_INT(s, 0x754 + k * 4) = func_003294A0(k);
}

/* 0x003B6920, 0x80 bytes. Unlocks the ending's gallery item. */
void func_003B6920(void)
{
    if (func_003C1850() == 0) {
        if (func_00327C00() == 6)
            func_0039FCA0(8, 1);
        else if (func_00327C00() == 8)
            func_0039FCA0(9, 1);
    } else {
        func_0039FCA0(7, 1);
    }
}

/* 0x003B6D10, 0x168 bytes. Starts the ending. */
void func_003B6D10(void)
{
    int *s = (int *)func_003B5E90();
    int k;

    s[0x1C9] = func_00327820();
    s[0x1C6] = 0;
    s[2] = 0;
    *(short *)(s + 0x1D8) = 600;
    s[0x1D2] = 0;
    s[0x1CF] = 1;
    *(u8 *)(s + 0x1D9) = 0;
    s[0x1D0] = -1;
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    ((u8 *)s)[0x765] = (g_7000015C >> 0x10) % 3;
    s[0] = 1;
    s[0x1C8] = 0;
    s[0x1D4] = 0;
    func_0011ED38(s + 0x145, 0, 0x148);
    func_003B69A0();
    if (s[0x1D7] == 6) {
        k = 0x22;
        switch (func_00327C00()) {
        case 0:
            k = 0x23;
            break;
        case 1:
            k = 0x25;
            break;
        case 2:
            k = 0x24;
            break;
        case 3:
            k = 0x26;
            break;
        case 4:
            k = 0x27;
            break;
        case 5:
            k = 0x28;
            break;
        }
        func_003BA8F0(k, func_0032EEB0(), -1, -1, -1);
    }
    if (s[0x1D7] == 6 && func_0023A9B0(6, 1) != 0)
        func_0023A960(6);
}

/* 0x003B6E80, 0x9C bytes. Ends it: frees the files. */
void func_003B6E80(void)
{
    u8 *s = func_003B5E90();

    func_003BC5E0();
    func_003B9760();
    if (ST_INT(s, 0x20) != 0) {
        func_00102EC0(ST_INT(s, 0x20));
        ST_INT(s, 0x20) = 0;
    }
    if (ST_INT(s, 0x24) != 0) {
        func_00102EC0(ST_INT(s, 0x24));
        ST_INT(s, 0x24) = 0;
    }
    if (ST_INT(s, 0x28) != 0) {
        func_00102EC0(ST_INT(s, 0x28));
        ST_INT(s, 0x28) = 0;
    }
    g_0056CCC8[0] = g_0056CCC8[1] = g_0056CCC8[2] = g_0056CCC8[3] = 0x80;
}

/* 0x003B6F20, 0x164 bytes. The ending's message (by how the game was won). */
void func_003B6F20(void)
{
    int o = func_00327820(), k = func_0030DFA0();
    char t[0x100];

    if (k == 10) {
        func_001204B0(t, func_00390760(0x7D), func_002F2890(o));
    } else if (k == 7) {
        func_001204B0(t, func_00390760(0x7E), func_002F2890(o));
    } else {
        if (k != 6)
            return;
        if (func_003C1850() == 0)
            func_001204B0(t, func_00390760(0x7B), func_002F2890(o));
        else
            func_001204B0(t, func_00390760(0x7C), func_002F2890(o),
                          func_00372410(func_00327C00()));
    }
    func_001AEDB0(0, -1, 0x116, 0);
    func_001AE9F0(0, t, 1);
    func_001AFEC0(0);
}
