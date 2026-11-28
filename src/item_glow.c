/*
 * item_glow.c - pools behind the battle's hit effects and item drops: 0x40 glows of 0x20 bytes at
 * 0x00755060, 0x40 position slots of 0x10 bytes at 0x00755860 (used flags at 0x00755C60), and
 * the saved item drops (16 of 0x20 bytes at 0x00752F90) of the 16 items at 0x00753190 (0x1A0
 * bytes each). Probably part of ItemModel.c (whose name is used at 0x0024BCA0). Written so far:
 * parts of 0x0024BC60-0x0024F89C.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Glow record: +0x00 / +0x04 position pointers, +0x08 scale (1.0), +0x0C / +0x10 position slots
 * (0x40 = none), +0x14 its layer (0x30 = none), +0x1C its index, +0x1D in use, +0x1E fading,
 * +0x1F its effect group (0x10 = none).
 */

#define SW2E_FILE_ITEM_GLOW_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00755060[0x40][0x20];        /* the glows */
extern u8 g_00755860[0x40][0x10];        /* the position slots */
extern u8 g_00755C60[0x40];              /* their used flags */
extern u8 *g_00755020[0x10];             /* the glow effect groups */
extern u8 g_00752F90[0x10][0x20];        /* the saved item drops */
extern u8 g_00753190[0x10][0x1A0];       /* the items */
extern int g_0045D504;                   /* (small data) free glows */
extern u32 g_0045D508;                   /* (small data) the first free glow */
extern int g_0045D50C;                   /* (small data) free position slots */
extern u32 g_0045D510;                   /* (small data) the first free position slot */

void func_0011EB80(void *to, const void *from, int n);
u8 *func_0024CE50(int kind, u32 *pos, u8 *out);
void func_0024F850(u32 k);

/* A ground height query (func_001F2BF0). */
typedef struct {
    u32 *pos;
    u32 unknown_04[3];
    float ground;            /* +0x10 the ground height found */
    u32 unknown_14[11];
} GroundQuery;

/* 0x0024E3C0, 0x74 bytes. Drops item `kind` (value `v`) on the ground at `pos`. */
void func_0024E3C0(u32 v, int kind, u32 *pos)
{
    u32 p[4];
    GroundQuery q;
    u8 out[16];
    u8 *it;

    q.pos = p;
    p[0] = pos[0];
    p[1] = pos[1];
    p[2] = pos[2];
    p[3] = pos[3];
    func_001F2BF0((unsigned char *)(&q));
    *(float *)&p[1] = q.ground - 50.0f;
    it = func_0024CE50(kind, p, out);
    if (it != 0)
        *(u32 *)(it + 0x198) = v;
}

/* 0x0024E440, 0x68 bytes. Clears the saved item drops. */
void func_0024E440(void)
{
    int k;

    for (k = 0; k < 0x10; k++) {
        *(int *)(g_00752F90[k] + 0x10) = 0x17;
        *(int *)(g_00752F90[k] + 0x14) = 0;
    }
}

/* 0x0024E4B0, 0x9C bytes. Saves the items lying around into save image `p`; its end. */
u8 *func_0024E4B0(u8 *p)
{
    int k, n = 0;
    u32 *d = (u32 *)g_00752F90;

    func_0024E440();
    for (k = 0; k < 0x10; k++) {
        u8 *it = g_00753190[k];

        if ((it[0x19F] & 1) != 0) {
            d[4] = it[0x19D];
            d[5] = *(u32 *)(it + 0x198);
            d[0] = *(u32 *)(it + 0x170);
            d[1] = *(u32 *)(it + 0x174);
            d[2] = *(u32 *)(it + 0x178);
            d[3] = *(u32 *)(it + 0x17C);
            n++;
            d += 8;
        }
    }
    func_0011EB80(p, g_00752F90, 0x200);
    func_0024E440();
    return p + 0x200;
}

/* 0x0024E550, 0x64 bytes. Drops again the items of saved list `d`. */
void func_0024E550(u8 *d)
{
    int k;

    for (k = 0; k < 0x10; k++, d += 0x20) {
        int kind = *(int *)(d + 0x10);

        if (kind < 0x17 && kind >= 0)
            func_0024E3C0(*(u32 *)(d + 0x14), kind, (u32 *)d);
    }
}

/* 0x0024E5C0, 0x94 bytes. Takes a position slot (its number into `*k`; 0x40 when none). */
u8 *func_0024E5C0(u32 *k)
{
    u8 *p = 0;

    if (g_0045D510 < 0x40) {
        p = g_00755860[g_0045D510];
        g_00755C60[g_0045D510] = 1;
        g_0045D50C--;
        *k = g_0045D510;
        while (g_0045D510 < 0x40) {
            if (g_00755C60[g_0045D510] == 0)
                return p;
            g_0045D510++;
        }
    } else {
        *k = 0x40;
    }
    return p;
}

/* 0x0024E660, 0x70 bytes. Takes a glow. */
u8 *func_0024E660(void)
{
    u8 *g = 0;

    if (g_0045D508 < 0x40) {
        g = g_00755060[g_0045D508];
        g_00755060[g_0045D508][0x1D] = 1;
        g_0045D504--;
        while (g_0045D508 < 0x40) {
            if (g_00755060[g_0045D508][0x1D] == 0)
                return g;
            g_0045D508++;
        }
    }
    return g;
}

/* 0x0024E6D0, 0xB4 bytes. Frees glow `g` (and its position slots and layer). */
void func_0024E6D0(u8 *g)
{
    if (g == 0 || g[0x1D] == 0)
        return;
    g[0x1D] = 0;
    *(u32 *)(g + 0) = 0;
    *(u32 *)(g + 4) = 0;
    func_0024F850(*(u32 *)(g + 0xC));
    func_0024F850(*(u32 *)(g + 0x10));
    *(u32 *)(g + 0xC) = 0x40;
    *(u32 *)(g + 0x10) = 0x40;
    g[0x1E] = 0;
    *(float *)(g + 8) = 1.0f;
    g[0x1F] = 0x10;
    if (*(u32 *)(g + 0x14) < 0x30) {
        func_002A8030(*(u32 *)(g + 0x14));
        *(u32 *)(g + 0x14) = 0x30;
    }
    if (g[0x1C] <= g_0045D508)
        g_0045D508 = g[0x1C];
    g_0045D504++;
}

/* 0x0024EA80, 0x108 bytes. Resets the pools. */
void func_0024EA80(void)
{
    u32 k;

    g_0045D510 = 0;
    g_0045D50C = 0x40;
    for (k = 0; k < 0x40; k++)
        g_00755C60[k] = 0;
    g_0045D508 = 0;
    g_0045D504 = 0x40;
    for (k = 0; k < 0x40; k++) {
        u8 *g = g_00755060[k];

        func_00118850(g, 0x20);
        g[0x1C] = k;
        *(float *)(g + 8) = 1.0f;
        *(u32 *)(g + 0xC) = 0x40;
        *(u32 *)(g + 0x10) = 0x40;
        g[0x1E] = 0;
        g[0x1F] = 0x10;
        *(u32 *)(g + 0x14) = 0x30;
    }
    for (k = 0; k < 0x10; k++)
        g_00755020[k] = 0;
}

/* 0x0024F850, 0x4C bytes. Frees position slot `k`. */
void func_0024F850(u32 k)
{
    if (k < 0x40 && g_00755C60[k] != 0) {
        g_00755C60[k] = 0;
        if (k <= g_0045D510)
            g_0045D510 = k;
        g_0045D50C++;
    }
}

extern u8 g_006A3A30[][0xC0];            /* the battle officers */
extern u8 *g_00754FE0[0x10];             /* the items' glow effects */
extern u8 g_00754B90[][0x30];            /* the item models */
extern int g_0045D4F8;                   /* (small data) their number */
#ifdef SW2E_PC
extern ps2ptr g_0045D4FC_a;                   /* (small data) the item model data */
#define g_0045D4FC ((u8 *)PS2_PTR(g_0045D4FC_a))
#define g_0045D4FC_SET(v) (g_0045D4FC_a = PS2_ADDR(v))
#else
extern u8 *g_0045D4FC;
#define g_0045D4FC_a (*(ps2ptr *)&g_0045D4FC)
#define g_0045D4FC_SET(v) (g_0045D4FC = (v))
#endif
extern u8 g_00669D60[];
extern int g_00669F6C;

void func_002A6910(int a, int b, u32 *pos);
void func_002A6D20(u8 who, int k);
void func_0024D3A0(u8 *a, u8 *b, int c);

/* 0x0024BC60, 0x38 bytes. Whether item kind `k` is one of 0x11-0x16. */
int func_0024BC60(int k)
{
    switch (k) {
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
        return 1;
    }
    return 0;
}

extern unsigned long long g_0045D4F0;    /* (small data) the item textures (func_00107440) */
extern int g_0045D500;                   /* (small data) */
extern const char g_0043D518[];          /* this file's name, for the loader's messages */
extern float g_00752F50[4][4];           /* the items' turn per frame: 2 degrees about Y */
void vu0_rotate(float out[4][4], float in[4][4], float angle);   /* stand-in for VU0 micro 0x70 */

/* 0x0024BCA0, 0x1EC bytes. Starts the items: their textures (LINKDATA 0x7EB) and models (0x7EA:
 * a count, then each model's offset), the 16 item slots, the saved drops, and the turn matrix
 * (the unit matrix kept in the scratchpad, turned by 2 degrees). */
void func_0024BCA0(void)
{
    u8 *tex;
    u32 *t;
    int k;

    tex = (u8 *)func_001026D0(1, 0x7EB, 0, 1, 0, 0, (const char *)g_0043D518, 0x72);
    g_0045D4F0 = func_00107440(tex, 0x28A0, 0x3FA3);
    func_00102EC0(tex);
    t = (u32 *)func_001026D0(1, 0x7EA, 0, 1, 0, 0, (const char *)g_0043D518, 0x7C);
    g_0045D4F8 = t[0];
    g_0045D4FC_SET((u8 *)t);
    for (k = 0; k < g_0045D4F8; k++) {
        if (func_0024BC60(k) == 0) {
            u32 *m = (u32 *)((u8 *)t + (t[1 + k] & ~3u));

            func_00148130(g_00754B90[k]);
            func_001482F0(m, g_00754B90[k], g_0045D4F0);
        }
    }
    for (k = 0; k < 0x10; k++) {
        u8 *it = g_00753190[k];

        func_0014F850(it);
        func_0014F8B0((u32 *)it, 0);
        it[0x19C] = (u8)k;
        it[0x19F] &= ~1;
        *(u32 *)(it + 0x198) = 0;
        it[0x19D] = 0x17;
        ((u32 *)g_00754FE0)[k] = 0;
    }
    func_0024E440();
    g_0045D500 = 0;
    vu0_rotate(g_00752F50, (float (*)[4])PS2_PTR(0x70000000), 0.034906585f);
}

/* 0x0024BE90, 0x90 bytes. Frees the items and their models. */
void func_0024BE90(void)
{
    int k;

    func_0024E440();
    for (k = 0; k < 0x10; k++)
        func_0014F950(g_00753190[k]);
    for (k = 0; k < g_0045D4F8; k++)
        func_001483B0(g_00754B90[k]);
    func_00102EC0(g_0045D4FC);
    g_0045D4FC_SET(0);
}

/* 0x0024BF20, 0x34 bytes. When resuming, drops the saved items again. */
void func_0024BF20(void)
{
    if (g_00669F6C != 0)
        func_0024E550((u8 *)PS2_PTR(func_002EFB00(3)));
}

/* 0x0024C070, 0x54 bytes. Removes item `k` (`it`). */
void func_0024C070(u8 *it, int k)
{
    *(u32 *)(it + 0x198) = 0;
    it[0x19F] &= 0xFE;
    it[0x19D] = 0x17;
    if (g_00754FE0[k] != 0) {
        *(u32 *)(g_00754FE0[k] + 0x34) |= 0x800;
        g_00754FE0[k] = 0;
    }
}

/* 0x0024C0D0, 0x168 bytes. Removes the items lying on base `b`'s centre. */
void func_0024C0D0(u8 *b)
{
    int k;

    if (b == 0 || func_0034EE50(b) == 0)
        return;
    for (k = 0; k < 0x10; k++) {
        u8 *it = g_00753190[k];

        if ((it[0x19F] & 1) != 0) {
            float xy[2];
            u8 c[2], s[2];

            func_00191200(xy, it + 0x170);
            c[0] = (int)xy[0] / 5000;
            c[1] = (int)xy[1] / 5000;
            if (func_0034ECA0(c) == b) {
                s[0] = (int)xy[0] / 1000;
                s[1] = (int)xy[1] / 1000;
                if (func_00352CA0(s) != 0)
                    func_0024C070(it, k);
            }
        }
    }
}

/* 0x0024D070, 0x94 bytes. Drops item `kind` on the ground at `pos` (not kinds 0x11-0x16, nor in
 * the flagged modes), with a sound. */
void func_0024D070(int kind, u32 *pos)
{
    u32 p[4];
    GroundQuery q;
    u8 out[16];

    if (func_0024BC60(kind) != 0 || (*(u32 *)(g_00669D60 + 0x200) & 0x4000010) != 0)
        return;
    q.pos = p;
    p[0] = pos[0];
    p[1] = pos[1];
    p[2] = pos[2];
    p[3] = pos[3];
    func_001F2BF0((unsigned char *)(&q));
    *(float *)&p[1] = q.ground - 50.0f;
    func_0024CE50(kind, p, out);
    func_002A6910(8, 0, p);
}

/* 0x0024D110, 0xEC bytes. Heals battle officer `k + 2` by `v` (up to its most life). */
void func_0024D110(float v, int k)
{
    u8 *o = g_006A3A30[k + 2];

    if ((*(u32 *)(o + 0xB8) & 1) != 0) {
        short most = *(short *)(o + 0x80);
        int n = (int)v + *(short *)(o + 0x82);

        if (n > most)
            n = most;
        if (n < 1)
            n = 0;
        *(short *)(o + 0x82) = n;
        if (*(short *)(o + 0x84) < n)
            *(short *)(o + 0x84) = n;
    }
}

/* 0x0024D200, 0xD0 bytes. Fills its musou gauge by `v` (up to its most). */
void func_0024D200(float v, int k)
{
    u8 *o = g_006A3A30[k + 2];

    if ((*(u32 *)(o + 0xB8) & 1) != 0) {
        short most = *(short *)(o + 0x86);
        int n = (int)v + *(short *)(o + 0x88);

        if (n > most)
            n = most;
        if (n < 1)
            n = 0;
        *(short *)(o + 0x88) = n;
    }
}

/* 0x0024D2D0, 0xA4 bytes. The gauge sound when actor `a`'s musou crosses a step (0x23B when it
 * reaches the top, else 0x248). */
void func_0024D2D0(short now, short before, short most, u8 *a)
{
    short step;
    int s;

    if (now == before)
        return;
    step = func_00271210(a);
    s = before / step;
    if (s != now / step)
        func_002A6D20(a[0x14E], s == most / step ? 0x23B : 0x248);
}

/* 0x0024D380, 0x1C bytes, matching. */
void func_0024D380(int kind, int model)
{
    func_0024D3A0((u8 *)PS2_PTR(kind), (u8 *)PS2_PTR(model), 1);
}
