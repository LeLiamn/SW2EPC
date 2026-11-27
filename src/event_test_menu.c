/*
 * event_test_menu.c - a menu listing the Empire story events by officer and playing one (from
 * 0x003B0340; a test menu?). State block 0x003B2000 (0x600 bytes at 0x007BAF10: +0 officer, +4
 * event, +8 result, +0xC, +0x10 the officers (0x1D), +0x84 the events of the chosen officer,
 * +0x5F4/+0x5F6 cursor and first line of the officer list, +0x5F8/+0x5FA of the event list,
 * +0x5FC/+0x5FE their counts). Sliding windows at 0x007BAEF0 and 0x007BAED0. Original file name
 * unknown. From 0x003B24F0: the event scene's choice windows and tabs.
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
