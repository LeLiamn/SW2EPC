/*
 * emp_relations.c - Empire screen pieces between 0x003E0290 and 0x003E1258: the after-battle
 * reward cards (state func_0021A630: cards from +0x13E4, 0x24 bytes each, their windows from
 * +0x13E4 too, 0x14 bytes each) and the force relations list (state at 0x007BF680: the force,
 * position, cursor, top line, count and the list of other forces). Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"
typedef unsigned long long u64;

typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

/* The relations list. */
extern struct {
    int a;
    int force;
    int x, y;
    int z;
    int w;
    int flag;
    short cursor, top;
    short count, shown;
    u8 list[0x19];
} g_007BF680;

extern u8 *g_005BA6A0;
extern int g_0056CCA4[4];                /* the text colours */
extern float g_0056CCC0, g_0056CCC4;     /* the text size */
extern char g_0045C588[], g_0045C598[];
extern int g_0045C590[2];

#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))
#define FONT_SIZE(s) (g_0056CCC0 = (s), g_0056CCC4 = (s))

u8 *func_0021A630(void);
int func_003294A0(int k);
u8 *func_0019FBC0(int k);
void func_003DFD80(int k, int a, int b, int x, int y, int c, u8 *d, u8 *e);
int func_001204B0(char *buf, const char *fmt, ...);
void func_002C4F40(float size, char *text, int x, int y, int a, int b, int c);
void func_003B5480(int x, int y, int a, int w, int b, int c);
void func_002C7310(int x, int y, int a, int w, int h, int b, int c);
int func_002F27D0(int o);
u8 *func_001A93A0(int x, int y, int a, int w, int h, int b, int c, int d);
void func_001A9B30(u8 *h, int c, int a);
void func_001AA2C0(u8 *h, int a);
char *func_0019B170(char *buf, int a, int b);
void func_00146B40(char *text, int x, int y, int w, int h, int a, int b);
void func_003B55A0(int x, int y, int a, int b);
void func_002D67E0(int k, int x, int y, int a, int b, int c);
void func_00287A10(int a, int b, int c, int x, int y, int d);
int func_001AE550(float speed, WindowAnim *window, short *pos, u8 *alpha, int a);
void func_00286420(int a, int b, int c, int d, int e, int f, u8 *g, int sel);
void func_002CFF20(int a, int b, int x, int y, int w, int h, int c, u8 *d, int p8, int p9);
int func_002F8CB0(int f);
int func_002F9C90(int f, int g);
void func_003A7C10(void);
int func_0030AB90(void);
int func_0030AFF0(int p);
void func_003A78E0(int p, int k, int a);
void func_003A8000(int p);
void func_003E0A50(void);
void func_003A80A0(int a);
void func_003A9010(int a);
u8 *func_0030D7D0(void);
void func_002C7A30(int x, int y, int a, int w, int h, int b, int c);
char *func_002F8DB0(int f);
int func_002F9D50(int f, int g);
u64 *func_001050F0(void);
void func_00105230(u64 *packet, int a);

/* 0x003E0290, 0x90 bytes. Draws the player's item card. */
void func_003E0290(void)
{
    u8 *p = func_0021A630();
    int k = func_003294A0(*(int *)(p + 0x1C));

    if (k < 4) {
        func_0019FBC0(k);
        func_003DFD80(k, *(int *)(p + 0x38), *(int *)(p + 0x34), 0x96, 0x4E, 0,
                      p + *(int *)(p + 0x1C) * 0x24 + 0x1B10, p + 0x1384);
    }
}

/* 0x003E0320, 0x130 bytes. The cards come in (three per row). */
void func_003E0320(int k)
{
    u8 *p = func_0021A630();
    WindowAnim *w = (WindowAnim *)(p + 0x13E4);
    int i;

    if (k != 1)
        return;
    for (i = 0; i < *(int *)(p + 0x15DC); i++, w++) {
        if (*(int *)(p + 0x13E4 + i * 0x24 + 0xD0) != 0) {
            short x = (short)(i % 3) * 0x9E, y = (short)(i / 3) * 0x5E;

            w->x0 = x + 0x66; w->y0 = y + 0x83; w->w0 = 0; w->h0 = 0;
            w->x1 = x + 0x66; w->y1 = y + 0x83; w->w1 = 0; w->h1 = 0;
            w->frames = 0; w->timer = 0;
            w->alpha0 = 0x80; w->alpha1 = 0x80;
            w->x1 = x + 0x1A; w->y1 = y + 0x67; w->w1 = 0x98; w->h1 = 0x38;
            w->alpha1 = 0x80;
            w->frames = 0xF;
        }
    }
}

/* 0x003E0450, 0xA4 bytes, matching. The screen's title and the gold. */
void func_003E0450(void)
{
    u8 *p = func_0021A630();
    char buf[32];

    func_001ABE40(*(u8 **)(p + 0x24), 0xF, 0x144, 0x20, 0, -1, -1, 0x80, 0, 0);
    func_001204B0(buf, g_0045C588, *(int *)(p + 0x1AEC));
    func_002C4F40(16.0f, buf, 0x1A4, 0x20, 0, 0, 6);
    func_003B5480(0xFC, 0x2E, 0, 0x200, 0x80, 0);
}

/* 0x003E0500, 0x230 bytes. Draws officer `o`'s card (two values) at (x, y). */
void func_003E0500(int o, int a, int b, int x, int y)
{
    char buf[32];
    u8 *r, *h;
    u8 c;

    func_002C7310(x, y, 0, 0x9C, 0x44, 0x80, 0);
    r = g_005BA6A0 + func_002F27D0(o) * 0x2C;
    c = r[6];
    h = func_001A93A0(x + 3, y - 0x1E, 0, 0x28, 0x2D, 0x80, 0, 0);
    func_001A9B30(h, c, 0);
    func_001AA2C0(h, 0);
    func_0019B170(buf, ((short *)r)[0], ((short *)r)[1]);
    FONT_COLOUR(6);
    FONT_SIZE(16.0f);
    func_00146B40(buf, x + 0x10, y + 0xD, 0x7A, 0x10, 0, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
    func_003B55A0(x + 0x18, y + 0x1E, 0, 0);
    func_001204B0(buf, g_0045C588, a);
    func_002C4F40(16.0f, buf, x + 0x50, y + 0x1E, 0, 0, 6);
    func_002D67E0(8, x + 0x18, y + 0x2F, 0, 0, 0x80);
    func_001204B0(buf, g_0045C588, b);
    func_002C4F40(16.0f, buf, x + 0x50, y + 0x2E, 0, 0, 6);
}

/* 0x003E0730, 0x1E0 bytes. Draws the reward screen. */
void func_003E0730(void)
{
    u8 *p = func_0021A630();
    u8 *e = p + 0x13E4, *sel = e + *(int *)(p + 0x1638) * 8;
    int step = *(int *)(p + 0x15E8), i;
    short pos[4];
    u8 alpha;

    func_003E0450();
    if (*(int *)(p + 0x15E8) < 3) {
        for (i = 0; i < *(int *)(p + 0x15DC); i++) {
            u8 *c = e + i * 0x24;

            func_003E0500(*(int *)(c + 0xBC), *(int *)(c + 0xC0), *(int *)(c + 0xC4),
                          i % 3 * 0x9E + 0x18, i / 3 * 0x5E + 0x58);
        }
    }
    step = *(int *)(p + 0x15E8);
    if (step > 2 && step < 7)
        func_00287A10(*(int *)(p + 0x15E0), *(int *)(sel + 0x208), *(int *)(sel + 0x20C), 0xEC,
                      0x20, 0);
    if (*(int *)(p + 0x1654) == 0 && *(int *)(p + 0x15E4) != 0
        && (u32)(*(int *)(p + 0x15E8) - 1) < 2) {
        for (i = 0; i < *(int *)(p + 0x15DC); i++) {
            if (*(int *)(e + i * 0x24 + 0xD0) != 0) {
                func_001AE550(1.0f, (WindowAnim *)(e + i * 0x14), pos, &alpha, 0);
                func_001ABE40(*(u8 **)(p + 0x24), 0, pos[0], pos[1], 0, pos[2], pos[3], 0x80, 2, 0);
            }
        }
    }
}

/* 0x003E0910, 0x134 bytes. The two choice buttons and the description box. */
void func_003E0910(void)
{
    u8 *p = func_0021A630();
    u8 *s = 0;
    int i;

    for (i = 0; i < 2; i++) {
        if (i == 0)
            s = p + 0x1198;
        else if (i == 1)
            s = p + 0x115C + *(int *)(p + 0x1C) * 0x14 + 0x1CC;
        func_00286420(*(int *)(p + 0x28), *(int *)(p + 0x2C), *(int *)(p + 0x20), 0xC,
                      g_0045C590[i], 0, s, *(int *)(p + 0x1380) == i);
    }
    if (*(int *)(p + 0x1380) == 0)
        s = p + 0x1198;
    else if (*(int *)(p + 0x1380) == 1)
        s = p + 0x115C + *(int *)(p + 0x1C) * 0x14 + 0x1CC;
    func_002CFF20(*(int *)(p + 0x28), *(int *)(p + 0x2C), 0x114, 0x4E, 0xDC, 0xD6, 0, s, 0, 0);
}

/* 0x003E0AE0, 0x1A4 bytes. Lists the forces the force has relations with and marks the map. */
void func_003E0AE0(void)
{
    int k, n = 0, prov;

    for (k = 0; k < 0x19; k++) {
        if (func_002F8CB0(k) != 0 && k != g_007BF680.force && func_002F9C90(g_007BF680.force, k) != 0) {
            g_007BF680.list[n] = k;
            n++;
        }
    }
    g_007BF680.count = n;
    if (n > 6)
        n = 7;
    g_007BF680.shown = n;
    func_003A7C10();
    for (prov = 0; prov < func_0030AB90(); prov++) {
        int f = func_0030AFF0(prov), r = func_002F9C90(g_007BF680.force, f);

        if (f == g_007BF680.force)
            func_003A78E0(prov, 0x1A, 1);
        else if (r == 1)
            func_003A78E0(prov, 0x1C, 1);
        else if (r == 2)
            func_003A78E0(prov, 0x1D, 1);
        else if (r == 3)
            func_003A78E0(prov, 0x1B, 1);
        else if (r == 0)
            func_003A8000(prov);
    }
    func_003E0A50();
    func_003A80A0(1);
    func_003A9010(0);
}

/* 0x003E0C90, 0xA8 bytes. Opens the relations list of force `f`. */
void func_003E0C90(int a, int f)
{
    int k;

    g_007BF680.x = 8;
    g_007BF680.y = 0x50;
    g_007BF680.z = 0;
    g_007BF680.w = 0xC0;
    g_007BF680.flag = 1;
    g_007BF680.cursor = 0;
    g_007BF680.top = 0;
    g_007BF680.a = a;
    g_007BF680.force = f;
    for (k = 0; k < 0x19; k++)
        g_007BF680.list[k] = 0xFF;
    func_003E0AE0();
}

/* 0x003E0D40, 0x128 bytes. The legend. */
void func_003E0D40(void)
{
    int i;

    func_002C7310(-0x10, 0x108, 0, 0x84, 0x40, 0x80, 1);
    for (i = 0; i < 3; i++) {
        func_001ABEA0(func_0030D7D0(), 300, 0x18, 0x10A + i * 0x14, 0, 0x38, 0x14, 0, i * 0x14 + 0x28, 0x38, 0x14, 0x80, 1, 0);
        func_001ABEA0(func_0030D7D0(), 0x128, 0x54, 0x10C + i * 0x14, 0, 0x10, 0x10, 0, i * 0x10, 0x10, 0x10, 0x80, 1, 0);
    }
}

/* 0x003E0E70, 0xC0 bytes. A relation's mark (1, 2, 3). */
void func_003E0E70(int k, int x, int y, int a, int b, int p5)
{
    int s = 0;

    if (k == 1)
        s = 0x12A;
    else if (k == 2)
        s = 0x129;
    else if (k == 3)
        s = 299;
    func_001ABE40(func_0030D7D0(), s, x, y, a, -1, -1, b, p5, 0);
}

/* 0x003E0F30, 0x328 bytes. Draws the relations list. */
void func_003E0F30(void)
{
    int x = g_007BF680.x, y = g_007BF680.y, n = g_007BF680.count, i;
    char buf[16];
    u64 *pk;

    if (g_007BF680.shown < g_007BF680.count) {
        func_001A3460(g_007BF680.x + 0xC0, g_007BF680.y - 0x10, g_007BF680.z, g_007BF680.w, 0x9E,
                      0x80, n, 7, g_007BF680.top - g_007BF680.cursor, g_007BF680.flag);
        n = g_007BF680.shown;
    }
    FONT_SIZE(16.0f);
    for (i = 0; i < n; i++, y += 0x12) {
        u8 f = g_007BF680.list[i + (g_007BF680.top - g_007BF680.cursor)];
        int r = func_002F9C90(g_007BF680.force, f);

        func_003E0E70(r, x, y, g_007BF680.z, 0x80, g_007BF680.flag);
        if (g_007BF680.cursor == i)
            func_002C7A30(x, y, g_007BF680.z, 0xC0, 0x10, 0, g_007BF680.flag);
        FONT_COLOUR(6);
        FONT_SIZE(16.0f);
        func_00146B40(func_002F8DB0(f), x + 0x10, y, 0x48, 0x10, g_007BF680.flag, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        if (r == 1) {
            func_001ABEA0(func_0030D7D0(), 300, x + 0x60, y - 2, 0, 0x38, 0x14, 0, 0, 0x38, 0x14, 0x80, 1, 0);
            func_001204B0(buf, g_0045C598, func_002F9D50(g_007BF680.force, f));
            func_002C4F40(16.0f, buf, x + 0x9C, y, g_007BF680.flag, 0, 6);
        }
    }
    pk = func_001050F0();
    pk[2] = 0x8000000044ULL;
    pk[3] = 0x43;
    func_00105230(pk, g_007BF680.flag);
    func_003E0D40();
}
