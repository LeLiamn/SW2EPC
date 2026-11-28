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

float fabsf(float x);

#pragma opt_unroll_loops on

extern u8 g_005BD750[5][0x5C8];          /* the map objects */
extern u8 *g_0045D2F0;                   /* (small data) the current map */
extern const char g_004251D0[];          /* "Field.c" */
extern u32 g_00424F20[];                 /* the map files by map number */
extern u32 g_00424F30[];                 /* the map files by scenario map */
extern u8 g_00669D60[];                  /* the settings */
extern u32 g_00669F60[4];                /* (settings) +0: the battle flags */
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
void func_0018E210(u8 *map, int m);
void func_0018E870(void);
int func_0032E7B0(void);
u32 func_0032F780(void);
int func_0032F090(u32 a);
u8 *func_002EFB00(int a);

/* 0x0018C490, 0x70 bytes, matching. Loads map file `entry` into map object `map`. */
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

/* 0x0018C730, 0x74 bytes, matching. Frees the map(s). */
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

/* 0x0018CA50, 0x18 bytes, matching. Table +0x58 (16-byte entries): count and data from `blk`. */
void func_0018CA50(u8 *map, u32 *blk)
{
    U32(map, 0x58) = blk[1] >> 4;
    U32(map, 0x5C) = blk[0];
}

/* 0x0018CA70, 0x18 bytes, matching. Table +0x60 (16-byte entries). */
void func_0018CA70(u8 *map, u32 *blk)
{
    U32(map, 0x60) = blk[1] >> 4;
    U32(map, 0x64) = blk[0];
}

/* 0x0018CA90, 0x18 bytes, matching. Table +0x68 (8-byte entries). */
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

/* 0x0018D0A0, 0x60 bytes, matching. Whether two keys are the same. */
int func_0018D0A0(u32 **a, u32 **b)
{
    if (*(unsigned long long *)a[0] != *(unsigned long long *)b[0])
        return 0;
    if (*(unsigned long long *)a[1] != *(unsigned long long *)b[1])
        return 0;
    return (((u32)a[2] ^ (u32)b[2]) & 1) == 0;
}

/* 0x0018D100, 0x40 bytes, matching. Allocates the map's two work tables (+0x100, +0x104). */
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

void func_001185E0(void *p, int size, int value);  /* memset */
void func_0018DA60(u8 *map, u8 *e, int side);

/* 0x0018D460, 0x98 bytes. Resets the map's route cache: 64 entries of 0x20 bytes (+0x100) in a
 * list from +0x108 (head 0, tail 0x3F; +0xD the next one, +4 the link pointing at it), 0x57
 * hash buckets (+0x104) empty. */
void func_0018D460(u8 *map)
{
    u8 *e;
    int k;

    func_00118850(PTR(map, 0x100), 0x800);
    func_001185E0(PTR(map, 0x104), 0x57, 0xFF);
    U8(map, 0x108) = 0;
    U8(map, 0x109) = 0x3F;
    e = PTR(map, 0x100);
    PTR(e, 4) = map + 0x108;
    for (k = 1; k < 0x40; k++, e += 0x20) {
        U8(e, 0xD) = (u8)k;
        PTR(e, 0x24) = e + 0xD;
    }
    U8(e, 0xD) = 0xFF;
}

/* 0x0018D9B0, 0xA4 bytes. Builds both sides' data (func_0018DA60) for every province. */
void func_0018D9B0(u8 *map)
{
    u32 i;

    for (i = 0; i < U8(map, 0x54); i = (i + 1) & 0xFF) {
        int s;

        for (s = 0; s < 2; s++)
            func_0018DA60(map, PTR(map, 0x50) + i * 0x88, s);
    }
}

extern short g_004251E0[];               /* the route cost added per link kind */
extern u32 g_0042A2C0[];                 /* the first step per link kind */
extern u8 g_00446310[0x14];              /* mode 2: the maps that have gates */
extern u8 g_00446330[0x14];              /* their gate counts */
extern u8 *g_00414180[0x14];             /* their gate tables (12 bytes each) */
extern u8 g_00445AA0[0x27];              /* the other maps' gate counts */
extern u8 *g_004140B0[0x27];             /* their gate tables */

/* 0x0018E060, 0x1A8 bytes. Relaxes both sides' route tables (+8, +0xC: n x n entries of a
 * 12-bit cost, 0xFFF none, and a 4-bit first step) through the link from province `from` to
 * `via` of kind `kind` (its cost g_004251E0, its first step g_0042A2C0). */
void func_0018E060(u8 *map, u32 from, u32 via, int kind)
{
    short add = g_004251E0[kind];
    u32 step0 = g_0042A2C0[kind];
    int side;

    for (side = 0; side < 2; side++) {
        u32 n = U8(map, 0x54), i;
        u16 *row = (u16 *)PTR(map, 8 + side * 4);
        u16 *rv = row + (via & 0xFF) * U8(map, 0x54);

        for (i = 0; i < n; i = (i + 1) & 0xFF) {
            u16 *e = row + (from & 0xFF);
            u32 step = (from & 0xFF) == i ? step0 : (u32)(((u8 *)e)[1] >> 4);
            u32 c = *e & 0xFFF;

            if (c != 0xFFF) {
                u32 j;

                for (j = 0; j < n; j = (j + 1) & 0xFF) {
                    u16 *t = row + j;
                    u32 d = rv[j] & 0xFFF;

                    if (d != 0xFFF) {
                        d = d + c + add;
                        if (d < (*t & 0xFFF)) {
                            *t = (*t & 0xF000) | (d & 0xFFF);
                            ((u8 *)t)[1] = (((u8 *)t)[1] & 0xF) | (u8)((step & 0xF) << 4);
                        }
                    }
                    n = U8(map, 0x54);
                }
            }
            row += n;
        }
    }
}

/* 0x0018E210, 0x13C bytes. The map's gates (+0x10A their count, +0x10C their table) for map
 * `m` (in mode 2 found by (m - 0x20) % 0x46). */
void func_0018E210(u8 *map, int m)
{
    if (g_00669DB8[0] == 2) {
        int k;

        for (k = 0; k < 0x14; k++) {
            if ((u32)((m - 0x20) % 0x46) == g_00446310[k])
                break;
        }
        if (k < 0 || k > 0x13) {
            U8(map, 0x10A) = 0;
            PTR(map, 0x10C) = 0;
        } else {
            U8(map, 0x10A) = g_00446330[k];
            PTR(map, 0x10C) = g_00414180[k];
        }
    } else if (m < 0 || m > 0x26) {
        U8(map, 0x10A) = 0;
        PTR(map, 0x10C) = 0;
    } else {
        U8(map, 0x10A) = g_00445AA0[m];
        PTR(map, 0x10C) = g_004140B0[m];
    }
}

/* The map's gates (+0x10C, +0x10A of them): 12 bytes each, +8 / +9 their cell, +10 flags (1 the
 * direction, 0x20 shown, 0x40 a door, 0x80 open when blocked), +0xB their owner (-1 none).
 * Their open states are kept as bits in both players' records. */
extern u8 g_0073DC98[], g_0073DF28[];
extern char g_00424EF0[], g_00424F10[];  /* cell steps by direction (x, z) */

int func_0018F730(u8 *map, u8 *cell, int dir, int a);
void func_0027DC90(u8 *cell);
int func_0018EC60(u8 *g);
int func_0018ED40(u8 *g);
int func_0018ECA0(u8 *g);

/* The map's province entry at `cell` (0 outside the map). */
static inline u8 *province_at(u8 *map, u8 *cell)
{
    if (cell == 0 || cell[0] > 0x1F || cell[1] > 0x1F)
        return 0;
    return ((u8 **)PTR(map, 4))[cell[0] + cell[1] * 0x20];
}

/* Sets (or clears) gate `k`'s open bit for both players. */
static inline void gate_bit(u32 k, int on)
{
    u8 b = 1 << (k & 7);

    if (on) {
        g_0073DC98[k >> 3] |= b;
        g_0073DF28[k >> 3] |= b;
    } else {
        g_0073DC98[k >> 3] &= ~b;
        g_0073DF28[k >> 3] &= ~b;
    }
}

/* 0x0018E6C0, 0x1B0 bytes. Opens (`open`) or closes the free doors (flags 0x60): their
 * province blocked (0x1000000) or back to its file state; their bits. */
void func_0018E6C0(int open)
{
    u8 *m = g_0045D2F0;
    u32 n = U8(g_0045D2F0, 0x10A), k;

    for (k = 0; k < n; k++) {
        u8 *g = PTR(m, 0x10C) + k * 0xC;

        if ((char)U8(g, 0xB) == -1 && (U8(g, 10) & 0x60) == 0x60) {
            u8 *e = province_at(m, g + 8);

            if (e != 0) {
                if (open == 0)
                    U32(e, 0x10) = (U32(e, 0x10) & ~0x1000000) | U32(PTR(e, 0), 0);
                else
                    U32(e, 0x10) |= 0x1000000;
            }
            gate_bit(k, open);
        }
    }
}

/* Updates the free gates whose test (`test`) changed (shown ones open the doors). */
static inline void gates_update(int doors_too)
{
    u8 *m = g_0045D2F0;
    u32 n = U8(g_0045D2F0, 0x10A), k;

    for (k = 0; k < n; k++) {
        u8 *g = PTR(m, 0x10C) + k * 0xC;
        int r, t;

        if ((char)U8(g, 0xB) != -1 || U8(g, 8) >= 0x20 || U8(g, 9) >= 0x20)
            continue;
        if (!doors_too && (U8(g, 10) & 0x40))
            continue;
        r = doors_too ? func_0018EC60(g) : func_0018ED40(g);
        if ((U8(PTR(g_0045D2F0, 0x10C) + k * 0xC, 10) & 0x20) == 0) {
            gate_bit(k, r);
        } else {
            t = (g_0073DC98[k >> 3] & 1 << (k & 7)) ? (r != 0) ^ 1 : r;
            if (t)
                func_0018E6C0(r);
        }
    }
}

/* 0x0018E870, 0x1DC bytes. Updates all the free gates. */
void func_0018E870(void)
{
    gates_update(1);
}

/* 0x0018EA60, 0x1EC bytes. Updates the free gates that are not doors. */
void func_0018EA60(void)
{
    gates_update(0);
}

/* 0x0018EC60, 0x3C bytes, matching. A gate's state: a door's (func_0018ECA0) or a passage's. */
int func_0018EC60(u8 *g)
{
    if (U8(g, 10) & 0x40)
        return func_0018ECA0(g);
    return func_0018ED40(g);
}

/* 0x0018ECA0, 0x98 bytes. Whether a door's province is blocked. */
int func_0018ECA0(u8 *g)
{
    u8 *e = province_at(g_0045D2F0, g + 8);

    if (e == 0)
        return 0;
    return (U32(e, 0x10) & 0x1000000) != 0;
}

/* 0x0018ED40, 0x1C8 bytes. Whether a passage gate is open: both provinces on its two sides
 * exist, neither cut off (0x2000000), not two blocked towns (0x40 without 0x1000000), and the
 * route across (func_0018F730) agrees with flag 0x80. */
int func_0018ED40(u8 *g)
{
    u8 f = U8(g, 10), c[2], d[2];
    int dir = (f & 1) ? 2 : 0;
    u8 *a, *b;
    u32 o;
    int r;

    c[0] = U8(g, 8);
    c[1] = U8(g, 9);
    d[0] = c[0] + g_00424EF0[dir];
    d[1] = c[1] + g_00424F10[dir];
    a = province_at(g_0045D2F0, c);
    b = province_at(g_0045D2F0, d);
    if (a == 0 || b == 0)
        return 0;
    o = U32(a, 0x10) | U32(b, 0x10);
    if (o & 0x2000000)
        return 0;
    if ((U32(a, 0x10) & U32(b, 0x10) & 0x40) && (o & 0x1000000) == 0)
        return 0;
    r = func_0018F730(g_0045D2F0, c, dir, 0);
    if ((f & 0x80) == 0)
        r = (r != 0) ^ 1;
    return r;
}

/* 0x0018EF10, 0xB0 bytes. Cuts the province at `cell` off (0x2000000), or (`back`) puts it
 * back to its file state. */
void func_0018EF10(u8 *cell, int back)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return;
    if (back == 0)
        U32(e, 0x10) |= 0x2000000;
    else
        U32(e, 0x10) = (U32(e, 0x10) & ~0x2000000) | U32(PTR(e, 0), 0);
}

/* 0x0018EFC0, 0xC0 bytes. Blocks the province at `cell` (0x1000000); for a town (0x40) the gates
 * are updated and the map told (func_0027DC90). */
void func_0018EFC0(u8 *cell)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e != 0 && (U32(e, 0x10) & 0x1000000) == 0) {
        U32(e, 0x10) |= 0x1000000;
        if (U32(e, 0x10) & 0x40) {
            func_0018E870();
            func_0027DC90(cell);
        }
    }
}

/* A route query: the side (0 / 1), the cell it leaves from, the cell it goes to. */
typedef struct {
    u32 side;
    u8 from[2];              /* +4 */
    u8 to[2];                /* +6 */
} RouteQuery;

/* A step of a route: moves `cell` one step (by its own way, with `arg`); whether it could. */
typedef int (*StepFn)(u8 *map, u16 *in, u16 *out, u32 arg);

extern int g_0042A290[];                 /* per first step: the province flag byte it needs (0-7, else none) */
extern u8 g_004251F0[];                  /* per side: the flag bit of a link */
extern struct {
    StepFn fn;
    u32 arg;
} g_0042A2E0[];                          /* the step functions */

void func_0027DDE0(void);

/* The index of a province entry. */
#define PROV_INDEX(map, e) ((((e) - PTR(map, 0x50)) / 0x88) & 0xFF)

/* 0x0018F080, 0x13C bytes. Blocks every province, then updates the gates and the map. */
void func_0018F080(void)
{
    u32 n = U8(g_0045D2F0, 0x54), i;

    for (i = 0; i < n; i++)
        U32(PTR(g_0045D2F0, 0x50) + i * 0x88, 0x10) |= 0x1000000;
    func_0018E870();
    func_0027DDE0();
}

/* 0x0018F1C0, 0x1C bytes, matching. Resets the current map's route cache. */
void func_0018F1C0(void)
{
    func_0018D460(g_0045D2F0);
}

/* 0x0018F1E0, 0x320 bytes. The next cell of the route `q` (*next; the start when there is no
 * route), and its first-step kind (*kind, with `kind` given). Whether there is a next step
 * the side may take (sides barred by +0x56 have none). */
int func_0018F1E0(u8 *map, RouteQuery *q, u16 *next, u32 *kind)
{
    u32 side = q->side, step = 0;
    u8 *a, *b;
    int ok = 1;

    if (U8(map, 0x56) & 1 << side) {
        *next = *(u16 *)q->from;
        if (kind != 0)
            *kind = 0;
        return 0;
    }
    a = province_at(map, q->from);
    b = province_at(map, q->to);
    if (a == 0 || b == 0) {
        *next = *(u16 *)q->from;
        if (kind != 0)
            *kind = 0;
        return 0;
    }
    if (a == b) {
        *next = *(u16 *)q->from;
    } else {
        u16 *t = (u16 *)PTR(map, 8 + side * 4) + PROV_INDEX(map, a) * U8(map, 0x54)
                 + PROV_INDEX(map, b);
        int need;
        u16 c;

        if ((*t & 0xFFF) == 0xFFF) {
            *next = *(u16 *)q->from;
            if (kind != 0)
                *kind = 0;
            return 0;
        }
        step = ((u8 *)t)[1] >> 4;
        need = g_0042A290[step];
        if (need >= 0 && need < 8 && (U8(a, need + 0x18) & g_004251F0[side]) == 0)
            ok = 0;
        c = U16(PTR(a, 0), 4);
        if (g_0042A2E0[step].fn(map, &c, &c, g_0042A2E0[step].arg) == 0)
            a = 0;
        else
            a = province_at(map, (u8 *)&c);
        *next = U16(PTR(a, 0), 4);
    }
    if (kind != 0)
        *kind = step;
    return ok;
}

/* 0x0018F500, 0x14C bytes. The cost of route `q` (0xFFF for none). */
u16 func_0018F500(u8 *map, RouteQuery *q)
{
    u8 *a = province_at(map, q->from), *b = province_at(map, q->to);

    if (a == 0 || b == 0)
        return 0xFFF;
    return ((u16 *)PTR(map, 8 + q->side * 4))[PROV_INDEX(map, a) * U8(map, 0x54)
                                              + PROV_INDEX(map, b)] & 0xFFF;
}

/* 0x0018F650, 0x30 bytes, matching. The same, 0xFFF past 0x100. */
u32 func_0018F650(u8 *map, RouteQuery *q)
{
    int c = func_0018F500(map, q);

    if (c > 0x100)
        c = 0xFFF;
    return c;
}

/* 0x0018F680, 0x64 bytes, matching. The next cell from `from` towards `to` for side `side` on the
 * current map (*next = `from` when there is none). */
void func_0018F680(u16 *next, u16 *from, u16 *to, u32 side)
{
    RouteQuery q;

    *(u16 *)q.from = *from;
    *(u16 *)q.to = *to;
    q.side = side;
    if (func_0018F1E0(g_0045D2F0, &q, next, 0) == 0)
        *next = *from;
}

/* 0x0018F6F0, 0x34 bytes, matching. The cost from `from` to `to` for side `side` on the current map. */
u32 func_0018F6F0(u16 *from, u16 *to, u32 side)
{
    RouteQuery q;

    *(u16 *)q.from = *from;
    *(u16 *)q.to = *to;
    q.side = side;
    return func_0018F650(g_0045D2F0, &q);
}

/* 0x0018F730, 0x94 bytes. Whether the province at `cell` has link `dir` for side `side`. */
int func_0018F730(u8 *map, u8 *cell, int dir, int side)
{
    u8 *e = province_at(map, cell);

    if (e == 0)
        return 0;
    return (g_004251F0[side] & U8(e, dir + 0x18)) != 0;
}

/* 0x0018F7D0, 0x2C bytes, matching. The same on the current map. */
int func_0018F7D0(u8 *cell, int dir, int side)
{
    return func_0018F730(g_0045D2F0, cell, dir, side);
}

/* 0x0018F800, 0x84 bytes. Whether the province at `cell` has link `dir` at all (bit 0). */
int func_0018F800(u8 *cell, int dir)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return (U8(e, dir + 0x18) & 1) != 0;
}

#define g_7000015C (*(u32 *)0x7000015C)          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)



void func_0027DE50(u8 a, u16 *p, u16 *q);
void func_0022B9B0(u8 *map, u8 *cell, u8 *next);
void func_0018E350(u8 *cell, int dir);
void func_0027DF90(u8 a, u16 *p, u16 *q, float *pos, float *dir);
void func_002E6410(float yaw, float *pos, u8 a);
void func_0018F9A0(u8 *cell, u32 dir);
int func_0018FC00(u8 *cell, int dir, char kind);
void func_0018FF30(u8 *cell, int dir, float *pos, float *v);
void func_001902D0(int a);

/* The current map number (mode 2: one of five by the counter). */
#define CUR_MAP() (g_00669DB8[0] == 2 ? (int)g_00669DD4[g_00669F98[0] % 5] : (int)g_00669DD4[0])

/* 0x0018F890, 0x10C bytes. Opens or closes (`kind`) the link `dir` of `cell`; on the first 39
 * maps an opening (kinds 0, 1) is shown (func_0018F9A0). Whether it changed. */
int func_0018F890(u8 *cell, int dir, char kind)
{
    int show;

    if (func_0018FC00(cell, dir, kind) == 0)
        return 0;
    show = CUR_MAP() < 0x27 && (kind == 1 || kind == 0);
    if (show)
        func_0018F9A0(cell, dir);
    return 1;
}

/* 0x0018F9A0, 0x260 bytes. Shows the gate at link `dir` of `cell` opening (once: battle flag
 * 0x400000): the camera looks at it along the link's direction. */
void func_0018F9A0(u8 *cell, u32 dir)
{
    u8 c[2], c2[2], *e, b;
    float pos[4], v[4], yaw;

    if (g_00669F60[0] & 0x400000)
        return;
    if ((int)dir < 4) {
        c[0] = cell[0];
        c[1] = cell[1];
    } else {
        c[0] = cell[0] + g_00424EF0[dir];
        c[1] = cell[1] + g_00424F10[dir];
        dir = (dir + 4) & 7;
    }
    e = province_at(g_0045D2F0, c);
    b = U8(PTR(e, 0), dir + 0x28);
    if (b & 0x40) {
        c2[0] = c[0] + g_00424EF0[dir];
        c2[1] = c[1] + g_00424F10[dir];
        func_0018FF30(c2, (dir + 4) & 7, pos, v);
    } else {
        func_0018FF30(c, dir, pos, v);
    }
    if (fabsf(v[2] - 1.0f) < 0.0001f)
        yaw = 0.0f;
    else if (fabsf(v[0] - 1.0f) < 0.0001f)
        yaw = 1.5707964f;
    else if (fabsf(v[2] + 1.0f) < 0.0001f)
        yaw = 3.1415927f;
    else if (fabsf(v[0] + 1.0f) < 0.0001f)
        yaw = -1.5707964f;
    else
        yaw = 0.0f;
    g_00669F60[0] |= 0x400000;
    func_002E6410(yaw, pos, b & 0x3F);
}

/* 0x0018FC00, 0x32C bytes. Opens (`kind` 0 or 2) or closes (1 or 3) the link `dir` between
 * `cell` and its neighbour (flags 0x18 of both sides); an opening relaxes the route tables, a
 * closing restores the links' file state and marks the routes to be rebuilt (+0x56). Whether
 * it changed. */
int func_0018FC00(u8 *cell, int dir, char kind)
{
    u8 *m = g_0045D2F0, *a, *b, d[2];
    int open;
    u16 pa, pb;
    u32 back = (dir + 4) & 7;

    d[0] = cell[0] + g_00424EF0[dir];
    d[1] = cell[1] + g_00424F10[dir];
    a = province_at(g_0045D2F0, cell);
    b = province_at(g_0045D2F0, d);
    if (a == 0 || b == 0)
        return 0;
    open = !(kind == 3 || kind == 1) && (kind == 2 || kind == 0);
    pa = U16(PTR(a, 0), 6);
    pb = U16(PTR(b, 0), 6);
    if ((U8(a, dir + 0x18) & 0x18) == 0) {
        if (!open)
            return 0;
        func_0027DE50(U8(PTR(b, 0), 9), &pa, &pb);
        U8(a, dir + 0x18) |= 0x18;
        U8(b, back + 0x18) |= 0x18;
        func_0018E060(m, PROV_INDEX(m, a), PROV_INDEX(m, b), dir);
        func_0018E060(m, PROV_INDEX(m, b), PROV_INDEX(m, a), back);   /* (the reverse link?) */
    } else {
        if (open)
            return 0;
        func_0027DE50(U8(PTR(b, 0), 9), &pa, &pb);
        U8(a, dir + 0x18) = (U8(a, dir + 0x18) & ~0x18) | U8(PTR(a, 0), dir + 0x10);
        U8(b, back + 0x18) = (U8(b, back + 0x18) & ~0x18) | U8(PTR(b, 0), back + 0x10);
        U8(m, 0x56) |= 3;
        U8(m, 0x57) = 0;
    }
    func_0018E350(cell, dir);
    func_0022B9B0(m, cell, d);
    return 1;
}

/* 0x0018FF30, 0x12C bytes. The position and direction of the gate at link `dir` of `cell`
 * (func_0027DF90). */
void func_0018FF30(u8 *cell, int dir, float *pos, float *v)
{
    u8 d[2], *a, *b;
    u16 pa, pb;

    d[0] = cell[0] + g_00424EF0[dir];
    d[1] = cell[1] + g_00424F10[dir];
    a = province_at(g_0045D2F0, cell);
    b = province_at(g_0045D2F0, d);
    pa = U16(PTR(a, 0), 6);
    pb = U16(PTR(b, 0), 6);
    func_0027DF90(U8(PTR(b, 0), 9), &pa, &pb, pos, v);
}

/* 0x00190060, 0x240 bytes. Opens or closes (`kind`) every gate link of the map; on the first
 * 39 maps one of the opened ones, at random, is shown. */
void func_00190060(u32 kind)
{
    u8 *m = g_0045D2F0;
    u32 n = U8(g_0045D2F0, 0xF9), i;
    u16 *cells;
    u8 *dirs;
    int found = 0;

    if (n == 0)
        return;
    cells = func_00102D30(n << 1);
    dirs = func_00102D30(n);
    for (i = 0; i < U8(m, 0x54); i++) {
        u8 *e = PTR(m, 0x50) + i * 0x88;
        int d;

        for (d = 0; d < 4; d++) {
            u16 c = U16(PTR(e, 0), 4);

            if ((U8(e, d + 0x18) & 1) && func_0018FC00((u8 *)&c, d, (char)kind) != 0) {
                dirs[found] = (u8)d;
                cells[found] = c;
                found++;
            }
        }
    }
    if (CUR_MAP() < 0x27 && ((kind & 0xFF) == 1 || (kind & 0xFF) == 0)) {
        int k = found == 0 ? 0 : (int)RANDOM() % found;

        func_0018F9A0((u8 *)&cells[k], dirs[k]);
    }
    func_00102EC0(cells);
    func_00102EC0(dirs);
}

/* 0x001902A0, 0x10 bytes, matching. Whether the routes must be rebuilt. */
int func_001902A0(void)
{
    return U8(g_0045D2F0, 0x56) != 0;
}

/* 0x001902B0, 0x20 bytes, matching. func_001902D0(480000). */
void func_001902B0(void)
{
    func_001902D0(480000);
}

u32 func_00102360(int budget, void *fn, int *stop);  /* starts a time budget (a callback sets *stop) */
void func_00102340(u32 t);
void func_0022BC70(u8 *map, u32 a);
int func_0022B890(u8 *bits, u32 *next);
void func_00191200(float *out, void *p);

/* 0x001902D0, 0x1A8 bytes. Rebuilds the routes marked at +0x56 one province at a time (+0x57),
 * then the work marked by flag 0x80 (the bits at +0xA0 from +0xF0), within the time budget
 * `budget` (none for 0): stops when the budget runs out. */
void func_001902D0(int budget)
{
    u8 *m = g_0045D2F0;
    u32 side = 0, t = (u32)-1;
    int stop = 0;

    if (budget != 0)
        t = func_00102360(480000, (void *)0x191230, &stop);
    while ((int)side < 2 && stop == 0) {
        u8 bit = 1 << side;

        if ((U8(m, 0x56) & bit) == 0) {
            side++;
        } else if (U8(m, 0x57) == U8(m, 0x54)) {
            side++;
            U8(m, 0x56) &= ~bit;
            U8(m, 0x57) = 0;
        } else {
            func_0018DA60(m, PTR(m, 0x50) + U8(m, 0x57) * 0x88, side);
            U8(m, 0x57) += 1;
        }
    }
    if (U8(m, 0x56) & 0x80) {
        do {
            if (stop != 0)
                goto out;
            func_0022BC70(m, U32(m, 0xF0));
            U8(m, 0xA0 + (U32(m, 0xF0) >> 3)) &= ~(1 << (U32(m, 0xF0) & 7));
        } while (func_0022B890(m + 0xA0, (u32 *)(m + 0xF0)) != 0);
        U8(m, 0x56) &= 0x7F;
    }
out:
    if (budget != 0)
        func_00102340(t);
}

/* 0x00190480, 0x60 bytes. Whether `cell` is on the map. */
int func_00190480(u8 *cell)
{
    return province_at(g_0045D2F0, cell) != 0;
}

/* 0x001904E0, 0xA4 bytes. Whether `fn` holds for every province's cell. */
int func_001904E0(int (*fn)(u16 *cell, void *a), void *a)
{
    u8 *m = g_0045D2F0;
    u32 i;

    for (i = 0; i < U8(m, 0x54); i++) {
        u16 c = U16(PTR(PTR(m, 0x50) + i * 0x88, 0), 4);

        if (fn(&c, a) == 0)
            return 0;
    }
    return 1;
}

/* 0x00190590, 0x7C bytes. Whether the province at `cell` has one of `flags`. */
int func_00190590(u8 *cell, u32 flags)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return (flags & U32(e, 0x10)) != 0;
}

/* 0x00190610, 0x94 bytes, matching. The same for the 5000-unit cell of a point (func_00191200). */
int func_00190610(void *a, u32 flags)
{
    float p[2];
    u8 c[2];

    func_00191200(p, a);
    c[0] = (u8)((int)p[0] / 5000);
    c[1] = (u8)((int)p[1] / 5000);
    return func_00190590(c, flags);
}

/* 0x001906B0, 0x128 bytes. Sets (`on`) or puts back to the file state `flags` of the provinces
 * in cells `a` to `b`. */
void func_001906B0(u8 *a, u8 *b, u32 flags, int on)
{
    u8 c[2];

    for (c[1] = a[1]; c[1] <= b[1]; c[1]++) {
        for (c[0] = a[0]; c[0] <= b[0]; c[0]++) {
            u8 *e = province_at(g_0045D2F0, c);

            if (e != 0) {
                if (on == 0)
                    U32(e, 0x10) = (U32(e, 0x10) & ~flags) | U32(PTR(e, 0), 0);
                else
                    U32(e, 0x10) |= flags;
            }
        }
    }
}

/* 0x001907E0, 0x7C bytes. Byte `k` of +0x14 of the province at `cell` (0 outside). */
u8 func_001907E0(u8 *cell, u32 k)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return U8(e, (k & 0xFF) + 0x14);
}

/* 0x00190860, 0x12C bytes. Sets (`on`) or clears bits `mask` of byte `k` of +0x14 for the
 * provinces in cells `a` to `b` (the map areas of the scenario). */
void func_00190860(u8 *a, u8 *b, u32 k, u8 mask, int on)
{
    u8 c[2];

    for (c[1] = a[1]; c[1] <= b[1]; c[1]++) {
        for (c[0] = a[0]; c[0] <= b[0]; c[0]++) {
            u8 *e = province_at(g_0045D2F0, c);

            if (e != 0) {
                if (on == 0)
                    U8(e, (k & 0xFF) + 0x14) &= ~mask;
                else
                    U8(e, (k & 0xFF) + 0x14) |= mask;
            }
        }
    }
}

/* 0x00190990, 0x180 bytes. The terrain of the province at `cell` (+0xC, 0xF none); a named
 * province without one takes the first linked neighbour's (links 0, 2, 4, 6 with flags 0x11). */
char func_00190990(u8 *cell)
{
    u8 *e = province_at(g_0045D2F0, cell), *r;
    char t;
    int k;

    if (e == 0)
        return 0xF;
    r = PTR(e, 0);
    t = (char)U8(r, 0xC);
    if (t == 0xF && (char)U8(r, 8) != -1) {
        for (k = 0; k < 4; k++) {
            if (U8(e, k * 2 + 0x18) & 0x11) {
                u8 c[2], *n;

                c[0] = U8(r, 4) + g_00424EF0[k * 2];
                c[1] = U8(r, 5) + g_00424F10[k * 2];
                n = province_at(g_0045D2F0, c);
                if (n == 0)
                    return 0xF;
                return (char)U8(PTR(n, 0), 0xC);
            }
        }
    }
    return t;
}

float func_001F2B70(float *p);           /* the ground height under p */
float func_001934E0(u8 part);
u32 func_00193570(float *p);
char func_00190990(u8 *cell);

/* 0x00190B10, 0x80 bytes, matching. The terrain at a point (func_00191200's 5000-unit cell). */
char func_00190B10(void *a)
{
    float p[2];
    u8 c[2];

    func_00191200(p, a);
    c[0] = (u8)((int)p[0] / 5000);
    c[1] = (u8)((int)p[1] / 5000);
    return func_00190990(c);
}

/* 0x00190B90, 0x6C bytes. The first entry of table +0x64 for a point with a terrain. */
int func_00190B90(u32 *out, void *a)
{
    u8 *m = g_0045D2F0;
    u32 *e;

    if (func_00190B10(a) == 0xF)
        return 0;
    if (U32(m, 0x60) == 0)
        return 0;
    e = (u32 *)PTR(m, 0x64);
    out[0] = e[0];
    out[1] = e[1];
    out[2] = e[2];
    out[3] = e[3];
    return 1;
}

/* 0x00190C00, 0x30 bytes. Entry `i` of table +0x64. */
void func_00190C00(u32 *out, u32 i)
{
    if (i < U32(g_0045D2F0, 0x60)) {
        u32 *e = (u32 *)(PTR(g_0045D2F0, 0x64) + i * 0x10);

        out[0] = e[0];
        out[1] = e[1];
        out[2] = e[2];
        out[3] = e[3];
    }
}

/* 0x00190C30, 0xC bytes, matching. The size of table +0x64. */
u32 func_00190C30(void)
{
    return U32(g_0045D2F0, 0x60);
}

/* 0x00190C40, 0x88 bytes. Bit `k` of the file record's +0x24 of the province at `cell`. */
int func_00190C40(u8 *cell, u32 k)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return (U32(PTR(e, 0), 0x24) & 1 << (k & 0x1F)) != 0;
}

/* 0x00190CD0, 0x80 bytes. Whether that word has one of `mask`. */
int func_00190CD0(u8 *cell, u32 mask)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return (U32(PTR(e, 0), 0x24) & mask) != 0;
}

/* 0x00190D50, 0xC bytes, matching. The number of map parts. */
u8 func_00190D50(void)
{
    return U8(g_0045D2F0, 0xF8);
}

/* 0x00190D60, 0x78 bytes. The map part of the province at `cell`. */
u8 func_00190D60(u8 *cell)
{
    u8 *e = province_at(g_0045D2F0, cell);

    if (e == 0)
        return 0;
    return U8(PTR(e, 0), 9);
}

/* 0x00190DE0, 0x68 bytes. `cell` in its part's own cells. */
void func_00190DE0(char *out, u8 *cell)
{
    u8 *p = g_0045D2F0 + func_00190D60(cell) * 0x10;

    out[0] = cell[0] - (char)U8(p, 0x74);
    out[1] = cell[1] - (char)U8(p, 0x75);
}

/* The map part of a point (by its 5000-unit cell). */
static inline u8 *part_of(u8 *map, float *p)
{
    u8 c[2], *e;

    c[0] = (u8)((int)p[0] / 5000);
    c[1] = (u8)((int)p[1] / 5000);
    e = province_at(map, c);
    return map + (e == 0 ? 0 : U8(PTR(e, 0), 9)) * 0x10;
}

/* 0x00190E50, 0x180 bytes. A map point (x, z) as a 3D point on the ground (out: x, height, z,
 * 1), in its map part's own space when the map has several. */
void func_00190E50(u8 *map, float *out, float *p)
{
    if (U8(map, 0xF8) < 2) {
        out[0] = p[0];
        out[2] = p[1];
        out[3] = 1.0f;
        out[1] = func_001F2B70(out);
    } else {
        u8 *part = part_of(map, p);

        out[0] = p[0] - *(float *)(part + 0x78);
        out[1] = func_001934E0(U8(part, 0x76));
        out[2] = p[1] - *(float *)(part + 0x7C);
        out[3] = 1.0f;
        out[1] = func_001F2B70(out);
    }
}

/* 0x00190FD0, 0x13C bytes. The same at height 0. */
void func_00190FD0(u8 *map, float *out, float *p)
{
    if (U8(map, 0xF8) < 2) {
        out[0] = p[0];
        out[1] = 0.0f;
        out[2] = p[1];
        out[3] = 1.0f;
    } else {
        u8 *part = part_of(map, p);

        out[0] = p[0] - *(float *)(part + 0x78);
        out[1] = 0.0f;
        out[2] = p[1] - *(float *)(part + 0x7C);
        out[3] = 1.0f;
    }
}

/* 0x00191110, 0x8C bytes. A 3D point back to a map point (x, z), adding its part's offset. */
void func_00191110(u8 *map, float *out, float *p)
{
    if (U8(map, 0xF8) < 2) {
        out[0] = p[0];
        out[1] = p[2];
    } else {
        u8 *part = map + (func_00193570(p) & 0xFF) * 0x10;

        out[0] = p[0] + *(float *)(part + 0x78);
        out[1] = p[2] + *(float *)(part + 0x7C);
    }
}

/* 0x001911A0, 0x28 bytes, matching. func_00190E50 on the current map. */
void func_001911A0(float *out, float *p)
{
    func_00190E50(g_0045D2F0, out, p);
}

/* 0x001911D0, 0x28 bytes, matching. func_00190FD0 on the current map. */
void func_001911D0(float *out, float *p)
{
    func_00190FD0(g_0045D2F0, out, p);
}

/* 0x00191200, 0x28 bytes, matching. func_00191110 on the current map. */
void func_00191200(float *out, void *p)
{
    func_00191110(g_0045D2F0, out, (float *)p);
}

#define g_70000888 (*(u32 *)0x70000888)          /* (scratchpad) the current layer */
#define g_7000088C (*(u32 *)0x7000088C)          /* (scratchpad) its bank (layers 3, 4: 1) */

/* 0x00191240, 0x1C bytes, matching. Selects layer `k`. */
void func_00191240(u32 k)
{
    g_70000888 = k;
    g_7000088C = 0x18 >> k & 1;
}

/* 0x00191260, 0x44 bytes. Sets colour `i` of the scratchpad table at 0x70000B90. */
u8 *func_00191260(int i, u8 r, u8 g, u8 b, u8 a)
{
    u8 *c = (u8 *)0x70000B90 + i * 4;

    c[0] = r;
    c[1] = g;
    c[2] = b;
    c[3] = a;
    return c;
}

/* 0x001912B0, 0x2C bytes. Bit grid `i` of the current bank (0x1E90 bytes each). */
u8 *func_001912B0(int i)
{
    return (u8 *)0x5BF440 + i * 0x1E90 + g_7000088C * 0x98D0;
}

/* 0x001912E0, 0x44 bytes. Whether cell (x, z) of a 250-wide bit grid is clear. */
int func_001912E0(u8 *grid, int x, int z)
{
    u32 k = x + z * 0xFA;

    return ((grid[(int)k >> 3] & (u8)(1 << (k & 7))) != 0) ^ 1;
}

/* 0x00191330, 0x78 bytes. Whether cell `c` is in rectangle `r` (x0, z0, x1, z1; the ends
 * excluded). */
int func_00191330(u8 *r, u8 *c)
{
    int in = 0, a = 0, b = 0;

    if (c[0] < r[2] && c[1] < r[3])
        a = 1;
    if (a && r[0] <= c[0])
        b = 1;
    if (b && r[1] <= c[1])
        in = 1;
    return in;
}

/* 0x001913B0, 0x98 bytes, matching. Sets the bits of rectangle `r` in a 250-wide grid. */
void func_001913B0(u8 *grid, u8 *r)
{
    u32 z, x;

    for (z = r[1]; (int)z < (int)r[3]; z++) {
        for (x = r[0]; (int)x < (int)r[2]; x++) {
            u32 k = x + z * 0xFA;

            grid[(int)k >> 3] |= 1 << (k & 7);
        }
    }
}

/* 0x00191450, 0xA0 bytes, matching. Clears them. */
void func_00191450(u8 *grid, u8 *r)
{
    u32 z, x;

    for (z = r[1]; (int)z < (int)r[3]; z++) {
        for (x = r[0]; (int)x < (int)r[2]; x++) {
            u32 k = x + z * 0xFA;

            grid[(int)k >> 3] &= ~(1 << (k & 7));
        }
    }
}
