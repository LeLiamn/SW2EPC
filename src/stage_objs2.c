/*
 * stage_objs2.c - pieces between 0x002B8790 and 0x002BCADC: a map screen's frame, cached
 * values of scripted objects (+0x11C their class, +0x128/+0x80 the cached results, +0x12C what
 * is cached), stage switches (players in a box, falling distances, sounds) and a free list of
 * 16 records. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern u8 g_005B4DF0[];                  /* the players' cameras' flags (0x240 apart) */
extern u8 g_00799920[0x100];
extern u8 *g_0045D5E8;                   /* (small data) the free list */

void func_002C7310(int x, int y, int a, int w, int h, int b, int c);
u32 *func_00177ED0(void);
void func_001ACA70(u32 *o, int a, int b, int c, int d);
u8 *func_001FF140(short k);
void func_00118AC0(void *to, const void *from, u32 n);
void func_00118850(void *p, int n);
u8 *func_0027E660(u8 *o);
u8 *func_002BBF40(u8 k);
void func_002A5B10(u32 h);
void func_002BBF00(u8 k);
void func_0027E6A0(u8 *o);
void func_0027E990(u32 s, u8 *o, u32 k);
void func_002BC110(int a, u8 b);
int func_00190C40(short *c, u8 k);

/* 0x002B8790, 0x248 bytes. Draws a map screen's frame and corners. */
int func_002B8790(u8 *t)
{
    func_001ABE40(t, 0x35, 0x58, 0x48, 0, 0x150, 0x90, 0x80, 2, 0);
    func_002C7310(0x58, 0xF2, 0, 0x150, 0x5C, 0x80, 2);
    func_001ABE40(t, 0x2A, 0x60, 0xF4, 0, 0x140, 0x54, 0x80, 2, 0);
    func_001ABE40(t, 0x37, 0xB, 0xB, 0, 0x40, 0x40, 0x80, 2, 0);
    func_001ABE40(t, 0x38, 0x1B5, 0xB, 0, 0x40, 0x40, 0x80, 2, 0);
    func_001ABE40(t, 0x39, 0xB, 0x135, 0, 0x40, 0x40, 0x80, 2, 0);
    func_001ABE40(t, 0x3A, 0x1B5, 0x135, 0, 0x40, 0x40, 0x80, 2, 0);
    func_001ABE40(t, 0x3B, 0xE0, 0xA0, 0, 0x40, 0x40, 0x80, 2, 0);
    return 0;
}

/* 0x002BA6E0, 0x60 bytes. The object's scale (at least 1, cached). */
float func_002BA6E0(u8 *o)
{
    if ((*(u32 *)(o + 0x12C) & 1) == 0) {
        float f = (*(float (**)(u8 *))(*(u8 **)(o + 0x11C) + 4))(o);

        *(float *)(o + 0x128) = f < 1.0f ? 1.0f : f;
        *(u32 *)(o + 0x12C) |= 1;
    }
    return *(float *)(o + 0x128);
}

/* 0x002BA740, 0x4C bytes. Its matrix (cached). */
u8 *func_002BA740(u8 *o)
{
    if ((*(u32 *)(o + 0x12C) & 2) == 0) {
        (*(void (**)(u8 *, u8 *))(*(u8 **)(o + 0x11C) + 8))(o, o + 0x80);
        *(u32 *)(o + 0x12C) |= 2;
    }
    return o + 0x80;
}

/* 0x002BBC60, 0x98 bytes. A new projectile at `pos`. */
u32 *func_002BBC60(int a, int b, u32 *pos, int c)
{
    u32 *o = func_00177ED0();
    int k;

    if (o != 0) {
        func_001ACA70(o, a, b, c, 0);
        for (k = 0; k < 4; k++) {
            o[k] = pos[k];
            o[0xC + k] = pos[k];
            o[0x10 + k] = pos[k];
        }
    }
    return o;
}

/* 0x002BBF60, 0xC4 bytes. Whether a player stands in the box (`lo`, `hi`). */
int func_002BBF60(float *lo, float *hi)
{
    int k;

    for (k = 0; k < 2; k++) {
        if ((g_005B4DF0[k * 0x240] & 1) != 0) {
            float x = *(float *)(0x574E20 + k * 0x630), z = *(float *)(0x574E28 + k * 0x630);

            if (lo[0] <= x && x <= hi[0] && lo[1] <= z && z <= hi[1])
                break;
        }
    }
    return k != 2;
}

/* 0x002BC2B0, 0xFC bytes. Whether the moving object `b` has covered the distance of switch `a`
 * (s = v t + a t / 2 per frame count). */
int func_002BC2B0(u8 *a, int *b)
{
    float d, v, acc, t;
    char c = ((u8 *)b)[9];
    int fwd;

    if (a[3] == 0) {
        d = *(float *)(a + 4);
    } else {
        u8 *r = func_001FF140(*(short *)(b[0] + 0x54));

        d = *(float *)(r + 0x24) - *(float *)(r + 0x14);
    }
    if (c == 3 || c == 1)
        fwd = 0;
    else
        fwd = c == 2 || c == 0;
    if (fwd) {
        v = *(float *)(a + 0x10);
        acc = *(float *)(a + 0x14);
    } else {
        v = *(float *)(a + 0x18);
        acc = *(float *)(a + 0x1C);
    }
    t = (float)b[1];
    d = d < 0 ? -d : d;
    v = t * (acc * 0.5f * t + v + 0.0f);
    return d <= (v < 0 ? -v : v);
}

/* 0x002BC660, 0x1C bytes. */
void func_002BC660(void *a, const void *b)
{
    func_00118AC0(a, b, 0x30);
}

/* 0x002BC680, 0xEC bytes. Stops object `b` when it has arrived (sound off, next state). */
int func_002BC680(u8 *a, int *b)
{
    char c;
    int i;
    u8 *q;

    if (func_002BC2B0(a, b) == 0)
        return 0;
    c = ((u8 *)b)[9];
    i = (c == 2 || c == 0) ? 1 : 3;
    (*(u8 **)b)[0x68] = 0;
    if ((signed char)((u8 *)b)[10] != -1 && (q = func_002BBF40(((u8 *)b)[10])) != 0) {
        func_002A5B10(*(u32 *)(q + 4));
        func_002BBF00(((u8 *)b)[10]);
    }
    func_002BC110(b[0], a[i + 8]);
    return 1;
}

/* 0x002BC770, 0x108 bytes. Sets object `o` moving (`k`: 3 stop, 2 go, 1/0 along a path). */
int func_002BC770(u8 *o, u32 k, u32 s, u8 v)
{
    u8 *r = func_0027E660(o), *q;

    if (r != 0 && r[8] == s && (signed char)r[10] != -1 && (q = func_002BBF40(r[10])) != 0) {
        func_002A5B10(*(u32 *)(q + 4));
        func_002BBF00(r[10]);
    }
    func_0027E6A0(o);
    k &= 0xFF;
    if (k == 3) {
        o[0x68] = 0;
        return 1;
    }
    if (k == 2) {
        o[0x68] = v;
        return 1;
    }
    if (k == 1 || k == 0) {
        func_0027E990(s, o, k);
        o[0x68] = v;
        return 1;
    }
    return 0;
}

/* 0x002BC9B0, 0x3C bytes. */
void func_002BC9B0(u8 *p)
{
    int k;

    for (k = 0; k < 4; k++) {
        p[0x10 + k * 0x30] = 0;
        p[0x11 + k * 0x30] = 3;
        p[0x21 + k * 0x30] = 0xFF;
    }
}

/* 0x002BC9F0, 0x78 bytes. Adds cell `c` to list `l` (21 at most) when it is in the area. */
int func_002BC9F0(short *c, int *l)
{
    if (func_00190C40(c, (*(u8 **)l)[0x13]) != 0) {
        u16 n = *(u16 *)(l + 1);

        if (n == 0x15)
            return 0;
        *(short *)((u8 *)l + n * 2 + 6) = *c;
        *(short *)(l + 1) = n + 1;
    }
    return 1;
}

/* 0x002BCA70, 0x6C bytes. Builds the free list. */
void func_002BCA70(void)
{
    u8 *p = g_00799920;
    int k;

    func_00118850(g_00799920, 0x100);
    g_0045D5E8 = g_00799920;
    for (k = 0; k < 0xF; k++, p += 0x10)
        *(u8 **)p = p + 0x10;
    *(u8 **)p = 0;
}

/* ---- Moving stage objects: their switch records by map (0x007994E0, 0x20 bytes each), their
 * sounds and paths (parts of 0x002BCAE0-0x002BFD2C). ---- */

extern u8 g_00669D60[];
extern u8 g_007994E0[][0x20];
extern u8 g_00799410[4][0x10];
extern u8 g_00796040[][0xC60];
extern u32 g_0045D5DC;
extern int g_0045D5CC, g_0045D5D0;

#define MAP_ID() (*(int *)(g_00669D60 + 0x58) == 2 ?                                        \
                  *(u32 *)(g_00669D60 + 0x74 + *(int *)(g_00669D60 + 0x238) % 5 * 4) :      \
                  *(u32 *)(g_00669D60 + 0x74))

char func_001FF100(short k, int a);
u8 *func_0027F120(char v);
u8 *func_0027E5F0(u8 *o, int a);
void func_0027E610(u8 *o);
u8 *func_0027E8C0(u8 *o, u32 k);
int func_002A6910(int v, int a, u8 *p);
void func_002A5A60(u32 a, u32 b, u32 c, u32 d, u32 e);
short func_001FF120(short k);
void func_001FD4B0(float f, u8 *o, short m, u8 *s);
short *func_001FF230(short *m);

/* Whether the object moves forward (its direction byte). */
#define FORWARD(b) (((u8 *)(b))[9] == 2 || ((u8 *)(b))[9] == 0)

/* 0x002BCAE0, 0x108 bytes. Loads the map's switch records into `p` (falling heights). */
void func_002BCAE0(u8 *p, u8 *rec, u32 size)
{
    u32 n, k;

    for (n = size >> 5; n != 0; n--, rec += 0x20) {
        if (rec[0] == MAP_ID())
            func_00118AC0(p + rec[1] * 0x30 + 0x20, rec, 0x20);
    }
    for (k = 0; k < 4; k++, p += 0x30) {
        if (p[0x21] == k) {
            float f = *(float *)(p + 0x3C) * 50.0f;

            *(float *)(p + 0x14) = f * 0.5f * f;
        }
    }
}

/* 0x002BDC40, 0xCC bytes. Whether moving object `b` has covered its distance. */
int func_002BDC40(int *b)
{
    int fwd = FORWARD(b);
    u8 *r = func_0027F120(func_001FF100(*(short *)(b[0] + 0x54), 10));

    return *(float *)(g_007994E0[r[0]] + 4)
        <= (float)b[1] * *(float *)(g_007994E0[r[0]] + 8 + !fwd * 4);
}

/* 0x002BDD10, 0x114 bytes. Stops it when it arrives. */
int func_002BDD10(int *b)
{
    u8 *o, *r, *q;
    u8 n;
    int i;

    if (func_002BDC40(b) == 0)
        return 0;
    o = (u8 *)b[0];
    r = func_0027F120(func_001FF100(*(short *)(o + 0x54), 10));
    n = r[0];
    if (FORWARD(b)) {
        i = 1;
    } else {
        o[0x68] = 0;
        i = 3;
    }
    if ((signed char)((u8 *)b)[10] != -1 && (q = func_002BBF40(((u8 *)b)[10])) != 0) {
        func_002A5B10(*(u32 *)(q + 4));
        func_002BBF00(((u8 *)b)[10]);
    }
    func_002BC110((int)o, g_007994E0[n][0x10 + i]);
    return 1;
}

/* 0x002BE2C0, 0x84 bytes. Starts the object's sound at `pos`. */
void func_002BE2C0(u8 *a, u32 *pos)
{
    u8 *q = func_002BBF40(a[0xB]);

    if (q != 0 && *(int *)(q + 4) == 0x107) {
        int h = func_002A6910(*(u16 *)(q + 8), 1, q + 0x10);

        *(int *)(q + 4) = h;
        if (h != 0x107)
            func_002A5A60(pos[0], pos[1], pos[2], pos[3], pos[4]);
    }
}

/* 0x002BE350, 0x50 bytes. Stops it. */
void func_002BE350(u8 *a)
{
    u8 *q = func_002BBF40(a[0xB]);

    if (q != 0 && *(int *)(q + 4) != 0x107) {
        func_002A5B10(*(u32 *)(q + 4));
        *(int *)(q + 4) = 0x107;
    }
}

/* 0x002BE3A0, 0x78 bytes. */
int func_002BE3A0(u8 *o, int a, char c)
{
    if (func_0027E5F0(o, a) != 0)
        return 1;
    if (c == 3 || c == 1)
        return 0;
    return c == 2 || c == 0;
}

/* 0x002BE420, 0xC8 bytes. */
int func_002BE420(u8 *o, int a, char c)
{
    u8 *r = func_0027E5F0(o, a);

    if (r != 0 && r[10] == 0) {
        func_002BE350(r);
        func_002BBF00(r[0xB]);
        func_0027E610(o);
        r = 0;
    }
    if (c == 2 || c == 0)
        return r != 0;
    return r == 0;
}

/* 0x002BEAE0, 0xE0 bytes. Loads the map's four path records. */
void func_002BEAE0(int *rec, u32 size)
{
    u32 n = size >> 4, k = 0;
    u8 *d = g_00799410[0];

    g_0045D5DC = 0;
    while (n != 0 && k < 4) {
        if ((u32)rec[0] == MAP_ID()) {
            func_00118AC0(d, rec, 0x10);
            d += 0x10;
            k = ++g_0045D5DC;
        }
        rec += 4;
        n--;
    }
}

/* 0x002BEE30, 0xA4 bytes. */
int func_002BEE30(u8 *o, u8 *v, u32 k)
{
    u8 *r;

    func_0027E610(o);
    k &= 0xFF;
    if (k == 3 || k == 2)
        return 1;
    if (k == 1 || k == 0) {
        r = func_0027E8C0(o, k);
        if (r == 0)
            return 0;
        r[10] = *v;
        return 1;
    }
    return 0;
}

/* 0x002BFAB0, 0xDC bytes. Moves the object's parts along their paths. */
void func_002BFAB0(float dt, u8 *o)
{
    u8 *r = func_0027E660(o), *s = g_00796040[r[10]];
    u8 *b = func_001FF140(func_001FF120(*(short *)(o + 0x54)));
    float f = *(float *)(r + 4);
    short *m = (short *)(b + 0x30);
    u16 n = *(u16 *)(b + 4), j;

    for (j = 0; j < n; j++) {
        func_001FD4B0(dt * (1.0f - f), o, *m, s + 0x60);
        m = func_001FF230(m);
        s += 0x60;
    }
}

/* 0x002BFCC0, 0x6C bytes. */
int func_002BFCC0(u8 *o, int a, u32 k)
{
    k &= 0xFF;
    if (k == 3 || k == 1)
        return func_0027E8C0(o, k) != 0;
    if (k == 2 || k == 0) {
        func_0027E610(o);
        g_0045D5D0 = 0;
        g_0045D5CC = 0;
        return 1;
    }
    return 0;
}

/* ---- More stage object switches (parts of 0x002C1540-0x002C4AD4). ---- */

extern int g_00441EB0[];
extern u8 g_00795690[][0x40], g_00795610[][0x20];
extern u32 g_0045D5BC;
extern int *g_00412470[];
extern u8 g_0073E020[10];
extern u8 g_004123A5;
extern u8 g_004123B0[][0x30];
extern u8 *g_0045D5A0;

int func_0027F0C0(char k);
int func_0027F140(char k);
int func_002C33C0(u8 *o, int a);
void func_002AF120(u32 k);
void func_002AEE00(u32 k, char s);
u32 func_00196A10(void);

/* 0x002C1540, 0xB4 bytes. */
int func_002C1540(u8 *o, int a)
{
    short id = *(short *)(o + 0x54);
    char k = func_001FF100(id, 10);
    u8 t = func_001FF100(id, 2);

    if (g_00441EB0[t] == 0 && (func_0027F0C0(k) == 0 || func_0027F140(k) != 10))
        return func_002C33C0(o, a);
    return 0;
}

/* 0x002C2240, 0xA4 bytes. */
int func_002C2240(u8 *o, int a, char c)
{
    u8 *r = func_0027E5F0(o, a);

    if (r == 0)
        return 0;
    if (!(c == 2 || c == 0) || r[0xB] == 0)
        func_0027E610(o);
    return 1;
}

/* 0x002C2D80, 0xC8 bytes. Loads the map's breakable object records. */
void func_002C2D80(int *rec, u32 size)
{
    u32 n = size >> 6;
    u8 *d = g_00795690[0];

    g_0045D5BC = 0;
    while (n != 0) {
        n--;
        if ((u32)rec[0] == MAP_ID()) {
            func_00118AC0(d, rec, 0x40);
            d += 0x40;
            g_0045D5BC++;
        }
        rec += 0x10;
    }
}

/* 0x002C2E50, 0x90 bytes. Drops the models of the objects at the height of `u`. */
void func_002C2E50(u8 *u)
{
    u32 k;

    for (k = 0; k < g_0045D5BC; k++) {
        u8 *a = g_00795690[k], *b = g_00795610[k];
        float y = *(float *)(u + 4);

        if (*(float *)(a + 0x10) < y && y <= *(float *)(a + 0x10) + *(float *)(a + 0x14)) {
            u8 *o = *(u8 **)(b + 8);

            if (o != 0)
                *(u32 *)(o + 0x38) |= 8;
            o = *(u8 **)(b + 0xC);
            if (o != 0)
                *(u32 *)(o + 0x38) |= 8;
        }
    }
}

/* 0x002C3560, 0xB8 bytes. Sets the state of object `o`'s effects. */
int func_002C3560(u8 *o, u32 k)
{
    u8 *b = func_001FF140(*(short *)(o + 0x54));
    u8 s = o[0x5A];
    u32 j;

    if (s >= 0xFF)
        return 0;
    for (j = 0; j < *(u16 *)(b + 2); j++) {
        if ((k & 0xFF) == 3)
            func_002AF120(s + j);
        func_002AEE00(s + j, k);
    }
    return 1;
}

/* 0x002C3AD0, 0x8C bytes. Whether all the switches of group `k` are on (2) or not (3). */
int func_002C3AD0(int k)
{
    int *l = g_00412470[k];

    if (l == 0)
        return 3;
    for (; *l < 0x1E; l++) {
        char c = *l < 10 ? g_0073E020[*l] : 0;

        if (c == 0)
            return 3;
    }
    return 2;
}

/* 0x002C3E20, 0xC4 bytes. Counts the stage objects of kind `*kind` that `fn` accepts. */
int func_002C3E20(char *kind, int (*fn)(u32, int), int a)
{
    u8 *o = *(u8 **)0x700001D0;
    u32 n = func_00196A10(), k;
    int c = 0;

    for (k = 0; k < n; k++, o += 0x70) {
        if (func_001FF100(*(short *)(o + 0x54), 10) == *kind && fn(k, a) != 0)
            c++;
    }
    return c;
}

/* 0x002C49D0, 0x108 bytes. Whether object `o` is the current target switch (it becomes the
 * active one going forward). */
int func_002C49D0(u8 *o, char c)
{
    u8 *r = g_004123B0[g_004123A5];
    u32 v;

    if (r[0x11] != g_004123A5)
        r = 0;
    v = func_001FF100(*(short *)(o + 0x54), 7) & 0xFF;
    v = v == 0 ? 0x28 : v - 1;
    if (r == 0 || v != r[0x14])
        return 0;
    g_0045D5A0 = (c == 2 || c == 0) ? o : 0;
    return 1;
}
