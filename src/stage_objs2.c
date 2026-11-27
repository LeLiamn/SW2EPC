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

extern u8 g_005B4DF0[];                  /* the players' cameras' flags (0x240 apart) */
extern u8 g_00799920[0x100];
extern u8 *g_0045D5E8;                   /* (small data) the free list */

void func_001ABE40(u8 *t, int k, int x, int y, int a, int w, int h, int b);
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
    func_001ABE40(t, 0x35, 0x58, 0x48, 0, 0x150, 0x90, 0x80);
    func_002C7310(0x58, 0xF2, 0, 0x150, 0x5C, 0x80, 2);
    func_001ABE40(t, 0x2A, 0x60, 0xF4, 0, 0x140, 0x54, 0x80);
    func_001ABE40(t, 0x37, 0xB, 0xB, 0, 0x40, 0x40, 0x80);
    func_001ABE40(t, 0x38, 0x1B5, 0xB, 0, 0x40, 0x40, 0x80);
    func_001ABE40(t, 0x39, 0xB, 0x135, 0, 0x40, 0x40, 0x80);
    func_001ABE40(t, 0x3A, 0x1B5, 0x135, 0, 0x40, 0x40, 0x80);
    func_001ABE40(t, 0x3B, 0xE0, 0xA0, 0, 0x40, 0x40, 0x80);
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

/* 0x002BA740, 0x4C bytes, matching. Its matrix (cached). */
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

/* 0x002BC660, 0x1C bytes, matching. */
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
