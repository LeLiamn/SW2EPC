/*
 * edit_windows.c - the edit screens' sliding windows (parts of 0x003D8030-0x003DFFFF). The edit
 * state (func_003766C0) holds window animation records from +0x9AC (0x14 bytes each: start
 * rectangle, end rectangle, start and end alpha, frames, timer) and the current page's frame
 * count at +0x9A8. Each page has an opening and a closing set-up. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

extern u8 *g_0043C120[];                 /* the edit screens' texts */
extern u8 *g_0043C738;

u8 *func_003766C0(void);
void func_003D7670(void);
void func_003D7A10(void);
void func_003D3C10(void);
int func_001AE550(float speed, WindowAnim *window, short *pos, u8 *alpha, int a);
void func_003D47A0(int k, int x, int y, u8 alpha);
void func_001A7DC0(u8 *text, int a, int b);
void func_002C59F0(void);
void func_002C5A30(void);
void func_001B8F60(int a, int b, int c);

#define EDIT() func_003766C0()
#define WIN(e, o) ((WindowAnim *)((e) + (o)))
#define FRAMES(e) (*(int *)((e) + 0x9A8))

/* Puts window `w` at a rectangle (start = end), alpha `a`. */
#define WIN_SET(w, X, Y, W, H, a) do {                                  \
    (w)->x0 = (X); (w)->y0 = (Y); (w)->w0 = (W); (w)->h0 = (H);         \
    (w)->x1 = (X); (w)->y1 = (Y); (w)->w1 = (W); (w)->h1 = (H);         \
    (w)->frames = 0; (w)->timer = 0;                                    \
    (w)->alpha0 = (a); (w)->alpha1 = (a);                               \
} while (0)

/* Sends window `w` to a rectangle in `f` frames, ending at alpha `a`. */
#define WIN_TO(w, X, Y, W, H, a, f) do {                                \
    (w)->x1 = (X); (w)->y1 = (Y); (w)->w1 = (W); (w)->h1 = (H);         \
    (w)->alpha1 = (a); (w)->frames = (f);                               \
} while (0)

/* 0x003D8030, 0x6C bytes. Draws the help window. */
void func_003D8030(void)
{
    u8 *e = EDIT();
    short pos[2];
    u8 alpha;

    func_003D7670();
    func_001AE550(1.0f, WIN(e, 0x9AC), pos, &alpha, 0);
    func_003D47A0(0xF, pos[0], pos[1], alpha);
    func_001A7DC0(g_0043C738, 0x80, 1);
}

/* 0x003D80A0, 0x184 bytes. Draws the page's side window (or only its help text when the entry
 * has none). */
void func_003D80A0(void)
{
    u8 *e = EDIT();
    short pos[2];
    u8 alpha;
    int t;

    func_003D7A10();
    if (e[*(int *)(e + 0xA4) * 0x38 + 0xBC] == 0) {
        if (*(int *)(e + 0x9A4) == 3) {
            WIN_SET(WIN(e, 0x9AC), 0x200, 0x67, 0xEC, 0xD1, 0);
            WIN_TO(WIN(e, 0x9AC), 0x200, 0x67, 0xEC, 0xD1, 0, 0);
        }
        t = 0x116;
    } else {
        if (*(int *)(e + 0x9A4) == 3) {
            WIN_SET(WIN(e, 0x9AC), 0x104, 0x67, 0xEC, 0xD1, 0x80);
            WIN_TO(WIN(e, 0x9AC), 0x104, 0x67, 0xEC, 0xD1, 0x80, 0);
        }
        func_001AE550(1.0f, WIN(e, 0x9AC), pos, &alpha, 0);
        func_003D47A0(*(int *)(e + 0xA4), pos[0], pos[1], alpha);
        t = 0x185;
    }
    func_001A7DC0(g_0043C120[t], 0x80, 1);
}

/* 0x003D8280, 0x74 bytes, matching. */
void func_003D8280(void)
{
    u8 *e = EDIT();

    func_003D3C10();
    WIN_SET(WIN(e, 0x9AC), 0x2EC, 0x67, 0xEC, 0xD1, 0);
    func_002C59F0();
    func_002C5A30();
}

/* 0x003D8300, 0xBC bytes. The ten list lines slide in from the left, one after the other. */
void func_003D8300(void)
{
    u8 *e = EDIT();
    int k;

    for (k = 0; k < 10; k++) {
        WindowAnim *w = WIN(e, 0xAB0) + k;
        short x = -0xF8 - (short)(k * 0x100 / 10), y = 0x48 + k * 0x18;

        WIN_SET(w, x, y, 0, 0, 0);
        WIN_TO(w, 8, y, 0, 0, 0x80, k + 10);
    }
}

/* 0x003D83C0, 0x94 bytes. They slide out. */
void func_003D83C0(void)
{
    u8 *e = EDIT();
    int k;

    for (k = 0; k < 10; k++) {
        WindowAnim *w = WIN(e, 0xAB0) + k;
        short y = 0x48 + k * 0x18;

        WIN_SET(w, 8, y, 0, 0, 0x80);
        WIN_TO(w, -0xC4, y, 0, 0, 0, 5);
    }
}

/* The side window comes in. */
#define SIDE_IN(e) WIN_TO(WIN(e, 0x9AC), 0x104, 0x67, 0xEC, 0xD1, 0x80, 0xC)

/* 0x003D8460, 0x178 bytes. */
void func_003D8460(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 0xC;
    WIN_SET(WIN(e, 0x9D4), 0x100, 0x112, 0, 0, 0);
    WIN_TO(WIN(e, 0x9D4), 4, 0xC6, 0x1F8, 0x98, 0x80, 0xC);
    for (k = 0; k < 2; k++) {
        WindowAnim *w = WIN(e, 0x9E8) + k;
        short x = -0xF8 - (short)(k * 0x100 / 10), y = 0x48 + k * 0x18;

        WIN_SET(w, x, y, 0, 0, 0);
        WIN_TO(w, 8, y, 0, 0, 0x80, k + 10);
    }
    WIN_SET(WIN(e, 0xA10), -0x147, 0x80, 0, 0, 0);
    WIN_TO(WIN(e, 0xA10), 0x10, 0x80, 0, 0, 0x80, 0xD);
}

/* 0x003D85E0, 0xBC bytes, matching. */
void func_003D85E0(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0x14;
    func_003D8300();
    WIN_SET(WIN(e, 0xA24), 0x200, 0x146, 0xF0, 0x18, 0);
    WIN_TO(WIN(e, 0xA24), 0x7F, 0x146, 0xF0, 0x18, 0x80, 0xC);
    SIDE_IN(e);
}

/* 0x003D86A0, 0x60 bytes, matching. */
void func_003D86A0(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0x14;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D8700, 0xB0 bytes, matching. */
void func_003D8700(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0xC;
    WIN_SET(WIN(e, 0xA38), 0x100, 0xDD, 0, 0, 0);
    WIN_TO(WIN(e, 0xA38), 4, 0x5D, 0x1F8, 0x101, 0x80, 0xC);
    SIDE_IN(e);
}

/* 0x003D87B0, 0x60 bytes, matching. */
void func_003D87B0(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0xE;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D8810, 0x60 bytes, matching. */
void func_003D8810(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0x14;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D8870, 0x60 bytes, matching. */
void func_003D8870(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0x11;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D88D0, 0x60 bytes, matching. */
void func_003D88D0(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0xE;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D8930, 0x134 bytes. The five buttons slide in from the right. */
void func_003D8930(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 0xF;
    WIN_SET(WIN(e, 0x9C0), 0x2EC, 0x67, 0xEC, 0x48, 0);
    WIN_TO(WIN(e, 0x9C0), 0x104, 0x67, 0xEC, 0x48, 0x80, 0xC);
    for (k = 0; k < 5; k++) {
        WindowAnim *w = WIN(e, 0xA4C) + k;
        short y = (k == 1 || k == 0 ? -1 : 0) + 0xB4 + k * 0x22;

        WIN_SET(w, 0x200 + k * 0x40, y, 0, 0, 0);
        WIN_TO(w, 0x13, y, 0, 0, 0x80, k + 10);
    }
}

/* 0x003D8A70, 0x220 bytes. */
void func_003D8A70(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 0xC;
    for (k = 0; k < 2; k++) {
        WindowAnim *w = WIN(e, 0x9E8) + k;
        short x = -0xF8 - (short)(k * 0x100 / 10), y = 0x48 + k * 0x2A;

        WIN_SET(w, x, y, 0, 0, 0);
        WIN_TO(w, 8, y, 0, 0, 0x80, k + 10);
    }
    WIN_SET(WIN(e, 0xA10), -0x147, 0xA4, 0, 0, 0);
    WIN_TO(WIN(e, 0xA10), 0x10, 0xA4, 0, 0, 0x80, 0xD);
    WIN_SET(WIN(e, 0x9C0), 0x2D8, 0x8A, 0xD8, 0x48, 0);
    WIN_TO(WIN(e, 0x9C0), 0xF6, 0x8A, 0xD8, 0x48, 0x80, 0xC);
    for (k = 0; k < 4; k++) {
        WindowAnim *w = WIN(e, 0xA4C) + k;
        short y = (k == 0 ? -1 : 0) + 0xD6 + k * 0x22;

        WIN_SET(w, 0x200 + k * 0x40, y, 0, 0, 0);
        WIN_TO(w, 0x13, y, 0, 0, 0x80, k + 10);
    }
}

/* 0x003D8CA0, 0xE8 bytes. Eleven lines (the last one lower) slide in. */
void func_003D8CA0(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 0xC;
    for (k = 0; k < 11; k++) {
        WindowAnim *w = WIN(e, 0xAB0) + k;
        short y = k == 10 ? 0x148 : 0x37 + k * 0x1A, x = -0x78 - k * 0x40;

        WIN_SET(w, x, y, 0, 0, 0);
        WIN_TO(w, 0x10, y, 0, 0, 0x80, 0xC);
    }
    SIDE_IN(e);
}

/* 0x003D8D90, 0x60 bytes, matching. */
void func_003D8D90(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 0x14;
    func_003D8300();
    SIDE_IN(e);
}

/* 0x003D8E40, 0x9C bytes, matching. Closes func_003D8460's windows. */
void func_003D8E40(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 5;
    WIN_TO(WIN(e, 0x9D4), 0x100, 0x112, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0x9E8), -0xC4, 0x48, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0x9FC), -0xC4, 0x60, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0xA10), -0xC4, 0x80, 0, 0, 0, 5);
}

/* 0x003D8EE0, 0x5C bytes, matching. */
void func_003D8EE0(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 5;
    func_003D83C0();
    WIN_TO(WIN(e, 0xA24), 0x200, 0x146, 0xF0, 0x18, 0, 5);
}

/* 0x003D8F70, 0x44 bytes, matching. */
void func_003D8F70(void)
{
    u8 *e = EDIT();

    FRAMES(e) = 5;
    WIN_TO(WIN(e, 0xA38), 0x100, 0xDD, 0, 0, 0, 5);
}

/* 0x003D9080, 0xBC bytes. */
void func_003D9080(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 5;
    WIN_TO(WIN(e, 0x9C0), 0x2EC, 0x67, 0xEC, 0x48, 0, 5);
    for (k = 0; k < 5; k++)
        WIN_TO(WIN(e, 0xA4C) + k, 0x200, (k == 1 || k == 0 ? -1 : 0) + 0xB4 + k * 0x22, 0, 0, 0, 5);
}

/* 0x003D9140, 0x104 bytes. */
void func_003D9140(void)
{
    u8 *e = EDIT();
    int k;

    FRAMES(e) = 5;
    WIN_TO(WIN(e, 0x9E8), -0xC4, 0x48, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0x9FC), -0xC4, 0x72, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0xA10), -0xC4, 0xA4, 0, 0, 0, 5);
    WIN_TO(WIN(e, 0x9C0), 0x2D8, 0x8A, 0xD8, 0x48, 0, 5);
    for (k = 0; k < 4; k++)
        WIN_TO(WIN(e, 0xA4C) + k, 0x200, (k == 0 ? -1 : 0) + 0xD6 + k * 0x22, 0, 0, 0, 5);
}

/* 0x003D9250, 0x108 bytes. */
void func_003D9250(void)
{
    u8 *e = EDIT();
    int k, v;

    FRAMES(e) = 5;
    for (k = 0; k < 11; k++) {
        WindowAnim *w = WIN(e, 0xAB0) + k;
        short y = k == 10 ? 0x148 : 0x37 + k * 0x1A;

        WIN_SET(w, 0x10, y, 0, 0, 0x80);
        WIN_TO(w, -0xC4, y, 0, 0, 0, 5);
    }
    v = *(int *)(e + 0xB0);
    if (v == 0 || v == 3 || (u32)(v - 8) < 2)
        WIN_TO(WIN(e, 0x9AC), 0x2EC, 0x67, 0xEC, 0xD1, 0, 5);
}

/* 0x003D9360, 0x90 bytes, matching. */
void func_003D9360(void)
{
    u8 *e = EDIT();

    if (*(int *)(e + 0xB0) == 0xC) {
        FRAMES(e) = 5;
        func_003D83C0();
        WIN_TO(WIN(e, 0x9AC), 0x2EC, 0x67, 0xEC, 0xD1, 0, 5);
        func_001B8F60(0, 6, 8);
    } else {
        FRAMES(e) = 5;
        func_003D83C0();
    }
}

/* ---- A picture shown full screen with a fade (state at 0x007BEC38). ---- */

typedef unsigned long long u64;

extern int g_007BEC38;                   /* frames shown (-1: none) */
extern int g_007BEC3C;                   /* its kind (1 and 3: additive) */
extern u8 *g_007BEC40;                   /* its textures */
extern u8 g_00500764, g_00500765;
extern u16 g_0050074C;

u64 *func_001050F0(void);
void func_00105230(u64 *packet, int a);
void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
void func_003DA890(void);

/* 0x003DA8D0, 0x188 bytes. Draws it (fading in over 12 frames, out after 32). */
void func_003DA8D0(void)
{
    int t, base, a;
    u64 *p;

    if (g_007BEC38 == -1 || g_007BEC40 == 0)
        return;
    t = g_007BEC38;
    base = g_007BEC3C * 0xF;
    a = 0x80;
    if (g_007BEC38 < 0xC)
        a = (g_007BEC38 << 7) / 0xC;
    else if (g_007BEC38 > 0x1F)
        a = 0x80 - (g_007BEC38 - 0x20) * 0x80 / 0x18;
    if (a < 0)
        a = 0;
    if (g_007BEC3C == 1 || g_007BEC3C == 3) {
        p = func_001050F0();
        p[2] = 0x48;
        p[3] = 0x43;
        func_00105230(p, 4);
    }
    func_001ABE40(g_007BEC40, t / 4 % 0xF + base, 0, 0, 0, 0x200, 0x180, a);
    p = func_001050F0();
    p[2] = 0x8000000044ULL;
    p[3] = 0x43;
    func_00105230(p, 4);
}

/* 0x003DAA60, 0xC4 bytes. Its frame: whether it is over (one second or the cancel button). */
int func_003DAA60(void)
{
    u16 v = (g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074C;

    if (g_007BEC38 == -1)
        return 1;
    if ((v & 0x40) == 0) {
        g_007BEC38++;
        if (g_007BEC38 < 0x3C)
            return 0;
        func_003DA890();
        return 1;
    }
    func_003DA890();
    return 1;
}

/* 0x003DAC30, 0x6C bytes. */
int func_003DAC30(int k)
{
    if (k == 4)
        return 6;
    if (k == 3)
        return 4;
    if (k == 2)
        return 5;
    if (k == 1)
        return 7;
    if (k == 0)
        return 9;
    return 0;
}

/* ---- Sliding boxes, first kind: a pool of 0x4C-byte records (gp 0x0045D830). ---- */

typedef struct { int x, y, w, h, a; } Box5;

typedef struct {
    Box5 to;                 /* where it rests */
    Box5 from;               /* where it comes from */
    Box5 cur;
    int id;                  /* -1: free */
    int t;
    int kind;                /* 1 left, 2 right, 3 up, 4 down, 5 fade (0: at once) */
    int state;               /* 1 opening, 2 open, 3 closing */
} SlideBox;

extern SlideBox *g_0045D830;             /* (small data) */
extern int g_0045D834;
extern Box5 g_0045C4C0;

void *func_00102DB0(int align, int size);
void func_00102EC0(void *p);

/* 0x003DB0C0, 0x54 bytes, matching. */
void func_003DB0C0(SlideBox *b)
{
    b->to.x = 0; b->to.y = 0; b->to.w = 0; b->to.h = 0; b->to.a = 0;
    b->from.x = 0; b->from.y = 0; b->from.w = 0; b->from.h = 0; b->from.a = 0;
    b->cur.x = 0; b->cur.y = 0; b->cur.w = 0; b->cur.h = 0; b->cur.a = 0;
    b->id = -1;
    b->t = 0;
    b->kind = 0;
    b->state = 0;
}

/* 0x003DB120, 0x88 bytes. Makes a pool of `n` boxes. */
void func_003DB120(int n)
{
    int k;

    if (g_0045D830 != 0) {
        func_00102EC0(g_0045D830);
        g_0045D830 = 0;
    }
    g_0045D834 = n;
    g_0045D830 = func_00102DB0(0x10, n * 0x4C);
    for (k = 0; k < n; k++)
        func_003DB0C0(&g_0045D830[k]);
}

/* 0x003DB1E0, 0x3C bytes, matching. */
void func_003DB1E0(SlideBox *b, int id, Box5 *to)
{
    b->to = *to;
    b->id = id;
    b->t = 0;
    b->kind = 0;
    b->state = 0;
}

/* 0x003DB220, 0x84 bytes. Sets box `id` (or takes a free one). */
void func_003DB220(int id, Box5 *to)
{
    SlideBox *f = 0, *b;
    int k;

    if (g_0045D830 == 0)
        return;
    for (k = 0, b = g_0045D830; k < g_0045D834; k++, b++) {
        if (b->id == -1)
            f = b;
        if (b->id == id) {
            f = b;
            break;
        }
    }
    if (f != 0) {
        func_003DB0C0(f);
        func_003DB1E0(f, id, to);
    }
}

/* Where a box comes from (the original writes x for the vertical kinds too). */
#define BOX_FROM(b, kind) do {                                          \
    (b)->from = (b)->to;                                                \
    if ((kind) == 5)                                                    \
        (b)->from.a = 0;                                                \
    else if ((kind) == 4)                                               \
        (b)->from.x = 0x1C0;                                            \
    else if ((kind) == 3)                                               \
        (b)->from.x = -(b)->to.h;                                       \
    else if ((kind) == 2)                                               \
        (b)->from.x = 0x200;                                            \
    else if ((kind) == 1)                                               \
        (b)->from.x = -(b)->to.w;                                       \
} while (0)

/* 0x003DB2B0, 0x144 bytes. Opens (`open`) or closes a box. */
void func_003DB2B0(SlideBox *b, int open, int kind)
{
    if (open != 0) {
        if (b->state == 1)
            return;
        b->state = 1;
    } else {
        if (b->state == 3)
            return;
        b->state = 3;
    }
    b->t = 0;
    b->kind = kind;
    BOX_FROM(b, kind);
    if (open != 0)
        b->cur = b->from;
    else
        b->cur = b->to;
}

/* 0x003DB400, 0x5C bytes. */
void func_003DB400(int id, int open, int kind)
{
    SlideBox *b;
    int k;

    if (g_0045D830 == 0)
        return;
    for (k = 0, b = g_0045D830; k < g_0045D834; k++, b++) {
        if (b->id == id)
            func_003DB2B0(b, open, kind);
    }
}

/* 0x003DB4A0, 0x264 bytes. An opening box's frame (5 frames). */
void func_003DB4A0(SlideBox *b)
{
    int v;

    switch (b->kind) {
    case 0:
        b->t = 5;
        break;
    case 1:
        v = b->from.x + b->t * (b->to.x - b->from.x) / 5;
        b->cur.x = v < b->to.x ? v : b->to.x;
        break;
    case 2:
        v = b->from.x + b->t * (b->to.x - b->from.x) / 5;
        b->cur.x = v < b->to.x ? b->to.x : v;
        break;
    case 3:
        v = b->from.y + b->t * (b->to.y - b->from.y) / 5;
        b->cur.y = v < b->to.y ? v : b->to.y;
        break;
    case 4:
        v = b->from.y + b->t * (b->to.y - b->from.y) / 5;
        b->cur.y = v < b->to.y ? b->to.y : v;
        break;
    case 5:
        v = b->from.a + b->t * (b->to.a - b->from.a) / 5;
        b->cur.a = v < b->to.a ? v : b->to.a;
        break;
    }
    b->t++;
    if (b->t > 5) {
        b->t = 0;
        b->state = 2;
        b->cur = b->to;
    }
}

/* 0x003DB710, 0x14C bytes. A closing box's frame (freed at the end). */
void func_003DB710(SlideBox *b)
{
    int v;

    switch (b->kind) {
    case 0:
        b->t = 5;
        break;
    case 1:
    case 2:
        b->cur.x = b->to.x - b->t * (b->to.x - b->from.x) / 5;
        break;
    case 3:
    case 4:
        b->cur.y = b->to.y - b->t * (b->to.y - b->from.y) / 5;
        break;
    case 5:
        v = b->to.a - b->t * (b->to.a - b->from.a) / 5;
        b->cur.a = v < b->from.a ? b->from.a : v;
        break;
    }
    b->t++;
    if (b->t > 5)
        func_003DB0C0(b);
}

/* 0x003DB860, 0x94 bytes. Steps every box. */
void func_003DB860(void)
{
    SlideBox *b = g_0045D830;
    int k;

    if (b == 0)
        return;
    for (k = 0; k < g_0045D834; k++, b++) {
        if (b->id != -1) {
            if (b->state == 1)
                func_003DB4A0(b);
            if (b->state == 3)
                func_003DB710(b);
        }
    }
}

/* 0x003DB900, 0x48 bytes. Box `id`'s current rectangle. */
Box5 *func_003DB900(int id)
{
    SlideBox *b = g_0045D830;
    int k;

    for (k = 0; k < g_0045D834; k++, b++) {
        if (b->id == id)
            return &b->cur;
    }
    return &g_0045C4C0;
}

/* ---- Sliding boxes, second kind: 26 records of 0x58 bytes at 0x007BEC50, whose lines come in
 * one after the other (2 frames apart). ---- */

typedef struct {
    Box5 to, from, cur;
    int id;
    int lines;
    int t;
    int end;                 /* last frame (the last line's) */
    int step;                /* frames per line (10) */
    int kind;
    int state;
} LineBox;

extern LineBox g_007BEC50[0x1A];

/* 0x003DB950, 0x60 bytes, matching. */
void func_003DB950(LineBox *b)
{
    b->to.x = 0; b->to.y = 0; b->to.w = 0; b->to.h = 0; b->to.a = 0;
    b->from.x = 0; b->from.y = 0; b->from.w = 0; b->from.h = 0; b->from.a = 0;
    b->cur.x = 0; b->cur.y = 0; b->cur.w = 0; b->cur.h = 0; b->cur.a = 0;
    b->id = -1;
    b->lines = 0;
    b->t = 0;
    b->end = 0;
    b->step = 0;
    b->kind = 0;
    b->state = 0;
}

/* 0x003DB9B0, 0x3C bytes, matching. */
void func_003DB9B0(LineBox *b, int id, Box5 *to)
{
    b->to = *to;
    b->id = id;
    b->t = 0;
    b->kind = 0;
    b->state = 0;
}

/* 0x003DB9F0, 0x160 bytes. Opens (`open`) or closes a box of `n` lines. */
void func_003DB9F0(LineBox *b, int open, int kind, int n)
{
    if (open != 0) {
        if (b->state == 1)
            return;
        b->state = 1;
    } else {
        if (b->state == 3)
            return;
        b->state = 3;
    }
    b->t = 0;
    b->lines = n;
    b->step = 10;
    b->end = (n - 1) * 2 + 10;
    b->kind = kind;
    BOX_FROM(b, kind);
    if (open != 0)
        b->cur = b->from;
    else
        b->cur = b->to;
}

/* 0x003DBB90, 0x1B0 bytes. Box `b` opening at frame `t` of `d`, into `out`. */
void func_003DBB90(Box5 *out, LineBox *b, int t, int d)
{
    int v;

    if (b->kind == 5) {
        v = b->from.a + t * (b->to.a - b->from.a) / d;
        out->a = v < b->to.a ? v : b->to.a;
    } else if (b->kind == 4) {
        v = b->from.y + t * (b->to.y - b->from.y) / d;
        out->y = v < b->to.y ? b->to.y : v;
    } else if (b->kind == 3) {
        v = b->from.y + t * (b->to.y - b->from.y) / d;
        out->y = v < b->to.y ? v : b->to.y;
    } else if (b->kind == 2) {
        v = b->from.x + t * (b->to.x - b->from.x) / d;
        out->x = v < b->to.x ? b->to.x : v;
    } else if (b->kind == 1) {
        v = b->from.x + t * (b->to.x - b->from.x) / d;
        out->x = v < b->to.x ? v : b->to.x;
    }
}

/* 0x003DBD40, 0xB0 bytes. */
void func_003DBD40(LineBox *b)
{
    switch (b->kind) {
    case 0:
        b->t = b->end;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        func_003DBB90(&b->cur, b, b->t, b->step);
        break;
    }
    b->t++;
    if (b->t > b->end) {
        b->t = 0;
        b->state = 2;
        b->cur = b->to;
    }
}

/* 0x003DBDF0, 0x1B0 bytes. Closing. */
void func_003DBDF0(Box5 *out, LineBox *b, int t, int d)
{
    int v;

    if (b->kind == 5) {
        v = b->to.a - t * (b->to.a - b->from.a) / d;
        out->a = v < b->from.a ? b->from.a : v;
    } else if (b->kind == 4) {
        v = b->to.y - t * (b->to.y - b->from.y) / d;
        out->y = v < b->to.y ? v : b->to.y;
    } else if (b->kind == 3) {
        v = b->to.y - t * (b->to.y - b->from.y) / d;
        out->y = v < b->to.y ? b->to.y : v;
    } else if (b->kind == 2) {
        v = b->to.x - t * (b->to.x - b->from.x) / d;
        out->x = v < b->to.x ? v : b->to.x;
    } else if (b->kind == 1) {
        v = b->to.x - t * (b->to.x - b->from.x) / d;
        out->x = v < b->to.x ? b->to.x : v;
    }
}

/* 0x003DBFA0, 0x84 bytes. */
void func_003DBFA0(LineBox *b)
{
    switch (b->kind) {
    case 0:
        b->t = b->end;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        func_003DBDF0(&b->cur, b, b->t, b->step);
        break;
    }
    b->t++;
    if (b->t > b->end)
        func_003DB950(b);
}

/* 0x003DC040, 0x40 bytes. */
void func_003DC040(void)
{
    int k;

    for (k = 0; k < 0x1A; k++)
        func_003DB950(&g_007BEC50[k]);
}

/* 0x003DC090, 0x48 bytes. */
void func_003DC090(int k, Box5 *to)
{
    func_003DB950(&g_007BEC50[k]);
    func_003DB9B0(&g_007BEC50[k], k, to);
}

/* 0x003DC110, 0x64 bytes. */
void func_003DC110(void)
{
    LineBox *b = g_007BEC50;
    int k;

    for (k = 0; k < 0x1A; k++, b++) {
        if (b->state == 1)
            func_003DBD40(b);
        if (b->state == 3)
            func_003DBFA0(b);
    }
}

/* 0x003DC180, 0x14C bytes. Line `line`'s rectangle in box `k` (each line 2 frames late). */
void func_003DC180(int k, int line, Box5 *out)
{
    LineBox *b = &g_007BEC50[k];
    int t = b->t + (line - 1) * -2;

    if (t < 0)
        t = 0;
    if (b->step < t)
        t = b->step;
    *out = b->cur;
    if (b->lines > 1) {
        if (b->state == 1)
            func_003DBB90(out, b, t, b->step);
        else if (b->state == 3)
            func_003DBDF0(out, b, t, b->step);
    }
}

void func_003DC0E0(int k, int open, int kind);

/* 0x003DA750, 0x9C bytes, matching. */
void func_003DA750(void)
{
    Box5 b;

    b.x = 0xC; b.y = 0x32; b.w = 0xD0; b.h = 0x28; b.a = 0x80;
    func_003DC090(0x15, &b);
    func_003DC0E0(0x15, 1, 1);
    b.x = 0xF8; b.y = 0x5C; b.w = 0x100; b.h = 0xE2; b.a = 0x80;
    func_003DC090(0x16, &b);
    func_003DC0E0(0x16, 2, 1);
}
