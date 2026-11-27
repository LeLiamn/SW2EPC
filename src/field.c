/*
 * field.c - the strategic map of the conquest mode (original source file Field.c: its name is
 * passed to the file loader at 0x0018C490). Written so far: simple functions from 0x0018C490.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A map object is 0x5C8 bytes (one at 0x005BD750, five in mode 2): +0x10 the index of each
 * province by id, +0x50 its province records (0x88 bytes each, +0x54 their count, +0x55 the
 * named ones, +0xF9 the gates?), +0x58 / +0x60 / +0x68 three more tables (count, data).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

#pragma opt_unroll_loops on

extern u8 g_005BD750[5][0x5C8];          /* the map objects */
extern u8 *g_0045D2F0;                   /* (small data) the current map */
extern const char g_004251D0[];          /* "Field.c" */
extern u32 g_00424F20[];                 /* the map files by map number */
extern u32 g_00424F30[];                 /* the map files by scenario map */
extern u8 g_00669D60[];                  /* the settings */
extern u32 g_00669DB8[4];                /* (settings) +0: the game mode */
extern u32 g_00669DC0[2];                /* (settings) +0: the scenario */
extern u32 g_00669DD4[5];                /* (settings) the five maps of mode 2 */
extern u32 g_00669F98[2];                /* (settings) +0: a counter */
extern int g_00669F6C[4];                /* (settings) +0: the game mode (1: ?) */
extern u8 *g_005BA694;                   /* the scenario table's entries (100 bytes each) */

void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const void *file, int line);
u32 func_00102680(int which, int entry);
void *func_00102D30(u32 size);           /* allocate */
void func_00118850(void *to, int size);  /* clear */
void func_00118AC0(void *to, const void *from, u32 n);  /* memcpy */
void func_0018CAB0(u8 *map, u32 *data, u32 size);
void func_00102EC0(void *data);          /* free */
void func_0018CDA0(u8 *map);
void func_0018E210(u8 *map, u32 a);
void func_0018E870(void);
int func_0032E7B0(void);
u32 func_0032F780(void);
int func_0032F090(u32 a);
u8 *func_002EFB00(int a);

/* 0x0018C490, 0x70 bytes. Loads map file `entry` into map object `map`. */
void func_0018C490(u8 *map, int entry)
{
    u32 *d = func_001026D0(1, entry, 0, 1, 0, 0, g_004251D0, 0x136);

    func_0018CAB0(map, d, func_00102680(1, entry));
}

/* 0x0018C500, 0x230 bytes. Loads the map for the game: an event's map (func_0032F090, entry
 * 0xB46 + n), the five maps of mode 2, or the scenario's (mode 3: scenario 0x55). */
void func_0018C500(void)
{
    int ev = -1;
    u32 m;

    if (func_0032E7B0() != 0)
        ev = func_0032F090(func_0032F780());
    g_0045D2F0 = g_005BD750[0];
    if (ev != -1) {
        func_0018C490(g_005BD750[0], ev + 0xB46);
        m = g_00669DB8[0] == 2 ? g_00669DD4[g_00669F98[0] % 5] : g_00669DD4[0];
        func_0018E210(g_005BD750[0], m);
        return;
    }
    if (g_00669DB8[0] == 2) {
        u32 k;
        u8 *map = g_005BD750[0];
        u32 *maps = g_00669DD4;

        for (k = 0; k < 5; k++, map += 0x5C8, maps++) {
            func_0018C490(map, g_00424F20[*maps]);
            func_0018E210(map, *maps);
        }
    } else {
        int s = g_00669DB8[0] == 2 ? 0x54 : (g_00669DB8[0] == 3 ? 0x55 : (int)g_00669DC0[0]);

        func_0018C490(g_005BD750[0], g_00424F30[U16(g_005BA694 + s * 100, 2)]);
        m = g_00669DB8[0] == 2 ? g_00669DD4[g_00669F98[0] % 5] : g_00669DD4[0];
        func_0018E210(g_005BD750[0], m);
    }
    func_0018E870();
}

/* 0x0018C730, 0x74 bytes. Frees the map(s). */
void func_0018C730(void)
{
    if (g_00669DB8[0] == 2) {
        u32 k;
        u8 *map = g_005BD750[0];

        for (k = 0; k < 5; k++, map += 0x5C8)
            func_0018CDA0(map);
    } else {
        func_0018CDA0(g_0045D2F0);
    }
    g_0045D2F0 = 0;
}

/* 0x0018C7B0, 0xBC bytes. Splits a pack (a count, then offsets) of `size` bytes into a table of
 * (address, size) pairs (*out); returns the count. */
u32 func_0018C7B0(u32 **out, u32 *pack, int size)
{
    u32 *t = func_00102D30(pack[0] << 3), i;

    size = size - pack[1];
    for (i = 0; i < pack[0]; i++) {
        t[i * 2] = (u32)pack + pack[1 + i];
        if (i != 0) {
            t[i * 2 - 1] = t[i * 2] - t[i * 2 - 2];
            size = size - (t[i * 2] - t[i * 2 - 2]);
        }
    }
    if (i != 0)
        t[i * 2 - 1] = size;
    *out = t;
    return pack[0];
}

/* 0x0018C870, 0x1DC bytes. Sets the provinces up from their 0x40-byte records (`blk`: data,
 * size): one 0x88-byte entry each (the record, its value, its 8 flag bytes, its link in table
 * +0x5C); named provinces (+8) indexed at +0x10; gates (flag 1 of the 4 bytes) counted at
 * +0xF9; in mode 1 the values come from func_002EFB00(4). */
void func_0018C870(u8 *map, u32 *blk)
{
    u8 *d = (u8 *)blk[0];
    u32 n, i;

    U8(map, 0x54) = (u8)(blk[1] >> 6);
    U8(map, 0x55) = 0;
    U8(map, 0xF9) = 0;
    n = U8(map, 0x54) * 0x88;
    PTR(map, 0x50) = func_00102D30(n);
    func_00118850(PTR(map, 0x50), n);
    for (i = 0; i < U8(map, 0x54); i = (i + 1) & 0xFF) {
        u8 *r = d + i * 0x40;
        u8 *e = PTR(map, 0x50) + i * 0x88;
        int k;

        PTR(e, 0) = r;
        U32(e, 0x10) = U32(r, 0);
        func_00118AC0(e + 0x18, PTR(e, 0) + 0x10, 8);
        func_00118850(e + 0x14, 3);
        PTR(e, 4) = PTR(map, 0x5C) + U16(PTR(e, 0), 0x1E) * 0x10;
        if (U8(PTR(e, 0), 8) != 0xFF) {
            U8(map, U8(PTR(e, 0), 8) * 4 + 0x10) = (u8)i;
            U8(map, 0x55) += 1;
        }
        for (k = 0; k < 4; k++) {
            if (U8(e, 0x18 + k) & 1)
                U8(map, 0xF9) += 1;
        }
    }
    if (g_00669F6C[0] == 1) {
        u8 *s = func_002EFB00(4);

        for (i = 0; i < U8(map, 0x54); i = (i + 1) & 0xFF, s += 0x10)
            func_00118AC0(PTR(map, 0x50) + i * 0x88 + 0x10, s, 0x10);
    }
}

/* 0x0018CA50, 0x18 bytes. Table +0x58 (16-byte entries): count and data from `blk`. */
void func_0018CA50(u8 *map, u32 *blk)
{
    U32(map, 0x58) = blk[1] >> 4;
    U32(map, 0x5C) = blk[0];
}

/* 0x0018CA70, 0x18 bytes. Table +0x60 (16-byte entries). */
void func_0018CA70(u8 *map, u32 *blk)
{
    U32(map, 0x60) = blk[1] >> 4;
    U32(map, 0x64) = blk[0];
}

/* 0x0018CA90, 0x18 bytes. Table +0x68 (8-byte entries). */
void func_0018CA90(u8 *map, u32 *blk)
{
    U32(map, 0x68) = blk[1] >> 3;
    U32(map, 0x6C) = blk[0];
}

u32 func_00103000(u32 heap);             /* selects a heap; returns the previous one */

void func_0018D100(u8 *map);
void func_0018D140(u8 *map);
void func_0018D460(u8 *map);
void func_0018D9B0(u8 *map);
void func_0022B950(u8 *map);
void func_00214FC0(u8 *map);
void func_0034FDF0(u8 *map);
void func_003535B0(u8 *map);

/* 0x0018CAB0, 0x2E8 bytes. Opens map file `d` (`size` bytes) into `map`: its four tables (the
 * provinces last), the province tables (+8, +0xC: n x n), a 0x14000-byte work area (+0xF4),
 * the up to three map parts (+0x70: their offsets in 5000-unit cells, from the first province
 * of each), the 32 x 32 grid of provinces by cell (+4), then the map's other parts. */
void func_0018CAB0(u8 *map, u32 *d, u32 size)
{
    u32 *t, h, n2, i;

    PTR(map, 0) = (u8 *)d;
    h = func_00103000(0);
    func_0018C7B0(&t, d, size);
    h = func_00103000(h);
    func_0018CA50(map, t + 2);
    func_0018CA90(map, t + 6);
    func_0018CA70(map, t + 4);
    func_0018C870(map, t);
    h = func_00103000(h);
    func_00102EC0(t);
    func_00103000(h);
    n2 = U8(map, 0x54) * U8(map, 0x54);
    U8(map, 0x56) = 0;
    func_00118850(map + 0xA0, 0x50);
    PTR(map, 8) = func_00102D30(n2 * 4);
    PTR(map, 0xF4) = func_00102D30(0x14000);
    PTR(map, 0xC) = PTR(map, 8) + n2 * 2;
    func_0018D100(map);
    func_00118850(map + 0x70, 0x30);
    for (i = 0; i < U8(map, 0x54); i = (i + 1) & 0xFF) {
        u8 *r = PTR(PTR(map, 0x50) + i * 0x88, 0);
        u8 *p = map + 0x70 + U8(r, 9) * 0x10;

        if (U32(p, 0) == 0) {
            U8(p, 4) = U8(r, 4) - U8(r, 6);
            U8(p, 5) = U8(r, 5) - U8(r, 7);
            U32(p, 0) = 1;
        }
    }
    PTR(map, 4) = func_00102D30(0x1000);
    func_00118850(PTR(map, 4), 0x1000);
    for (i = 0; i < U8(map, 0x54); i = (i + 1) & 0xFF) {
        u8 *e = PTR(map, 0x50) + i * 0x88;
        u8 *r = PTR(e, 0);

        ((u8 **)PTR(map, 4))[U8(r, 4) + U8(r, 5) * 0x20] = e;
    }
    for (i = 0; i < 3; i = (i + 1) & 0xFF) {
        u8 *p = map + 0x70 + i * 0x10;

        if (U32(p, 0) == 0)
            break;
        *(float *)(p + 8) = (float)((char)U8(p, 4) * 5000);
        *(float *)(p + 0xC) = (float)((char)U8(p, 5) * 5000);
        U8(p, 6) = (u8)i;
    }
    U8(map, 0xF8) = (u8)i;
    func_0018D9B0(map);
    func_0022B950(map);
    func_00214FC0(map);
    func_0034FDF0(map);
    func_003535B0(map);
}

/* 0x0018CDA0, 0x60 bytes. Frees a map's tables and file. */
void func_0018CDA0(u8 *map)
{
    func_0018D140(map);
    func_00102EC0(PTR(map, 8));
    PTR(map, 8) = 0;
    func_00102EC0(PTR(map, 0xF4));
    PTR(map, 0xF4) = 0;
    func_00102EC0(PTR(map, 4));
    PTR(map, 4) = 0;
    func_00102EC0(PTR(map, 0x50));
    PTR(map, 0x50) = 0;
    func_00102EC0(PTR(map, 0));
    PTR(map, 0) = 0;
}

/* 0x0018CE00, 0x204 bytes. Saves the map's provinces: the named ones' owners (+0x17 from the
 * index table's second byte) are set first, then each province's 16 bytes (+0x10) are copied to
 * `p`; returns the end. */
u8 *func_0018CE00(u8 *p)
{
    u8 *m = g_0045D2F0;
    u32 n = U8(g_0045D2F0, 0x55), i;

    for (i = 0; i < n; i++)
        U8(PTR(g_0045D2F0, 0x50) + U8(g_0045D2F0, 0x10 + i * 4) * 0x88, 0x17)
            = U8(g_0045D2F0, 0x11 + i * 4);
    n = U8(g_0045D2F0, 0x54);
    for (i = 0; i < n; i++, p += 0x10)
        func_00118AC0(p, PTR(m, 0x50) + i * 0x88 + 0x10, 0x10);
    return p;
}

/* 0x0018D010, 0x88 bytes. A key's hash: the sum of the first two words, minus (one less than)
 * the second's, xored with 0x1895F7C2 for flag 1. */
u32 func_0018D010(u32 **k)
{
    u32 h = k[0][1] + k[0][0] + ~k[1][1] + ~k[1][0];

    if ((u32)k[2] & 1)
        h = h ^ 0x1895F7C2;
    return h;
}

/* 0x0018D0A0, 0x60 bytes. Whether two keys are the same. */
int func_0018D0A0(u32 **a, u32 **b)
{
    if (*(unsigned long long *)a[0] != *(unsigned long long *)b[0])
        return 0;
    if (*(unsigned long long *)a[1] != *(unsigned long long *)b[1])
        return 0;
    return (((u32)a[2] ^ (u32)b[2]) & 1) == 0;
}

/* 0x0018D100, 0x40 bytes. Allocates the map's two work tables (+0x100, +0x104). */
void func_0018D100(u8 *map)
{
    PTR(map, 0x100) = func_00102D30(0x800);
    PTR(map, 0x104) = func_00102D30(0x57);
    func_0018D460(map);
}

/* 0x0018D140, 0x38 bytes. Frees them. */
void func_0018D140(u8 *map)
{
    func_00102EC0(PTR(map, 0x100));
    PTR(map, 0x100) = 0;
    func_00102EC0(PTR(map, 0x104));
    PTR(map, 0x104) = 0;
}
