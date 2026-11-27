/*
 * item_glow.c - pools behind the battle's hit effects and item drops: 0x40 glows of 0x20 bytes at
 * 0x00755060, 0x40 position slots of 0x10 bytes at 0x00755860 (used flags at 0x00755C60), and
 * the saved item drops (16 of 0x20 bytes at 0x00752F90) of the 16 items at 0x00753190 (0x1A0
 * bytes each). Probably part of ItemModel.c (whose name is used at 0x0024BCA0). Written so far:
 * parts of 0x0024E3C0-0x0024F89C.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Glow record: +0x00 / +0x04 position pointers, +0x08 scale (1.0), +0x0C / +0x10 position slots
 * (0x40 = none), +0x14 its layer (0x30 = none), +0x1C its index, +0x1D in use, +0x1E fading,
 * +0x1F its effect group (0x10 = none).
 */

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

void func_00118850(void *p, int n);
void func_0011EB80(void *to, const void *from, int n);
void func_001F2BF0(void *q);
u8 *func_0024CE50(int kind, u32 *pos, u8 *out);
void func_002A8030(void);
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
    func_001F2BF0(&q);
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
        func_002A8030();
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
