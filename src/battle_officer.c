/*
 * battle_officer.c - officers joining a battle (0x001B92B0-0x001BC8B4, before ModelManager.c; the
 * original file's name is unknown). Written: all but the battle state save / load (0x001BB7F0,
 * 0x001BBEA0).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Battle officers are 0xC0 bytes at 0x006A3A30 (the game state +0x100C0); 15 spare ones at
 * 0x006A95B0 serve as reinforcements. +0x14 their unit, +0x68 their table record, +0x80 life
 * max, +0x82 life, +0x84 life shown, +0x86 / +0x88 musou, +0x8A-+0x8E attack, defence, ...,
 * +0x90 / +0x94 speeds, +0xB8 flags (1 used), +0xBC more flags.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define g_7000015C (*(u32 *)0x7000015C)          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

extern u8 g_006A95B0[15][0xC0];          /* the spare battle officers */
extern u8 *g_006AA580[6];                /* records that can be picked */
extern u32 g_006AA598;                   /* their count */
extern int g_006AA5C8[2], g_006AA5D0[2]; /* per player: a timer and a record */
extern u8 g_00693970[][0x88];

int func_00190610(u8 *cell, int a);
void func_001911A0(u8 *cell, float *pos);
void func_00191200(u8 *out, float *pos);
u8 *func_003DD3C0(u8 kind);
void func_001BA3D0(u8 *b);
void func_00166080(u8 *u, u8 side, u8 kind);
void func_001660C0(u8 *u, u8 *cell);
void func_002071F0(u8 *b, u8 *cell);
void func_0016BD80(u8 *a, u8 *b, int c);
u8 *func_0034AD10(void);
u32 func_003489E0(int a, int b);
void func_001F0CD0(u8 *u, u8 *cell);
void func_00118AC0(void *d, const void *s, u32 n);
void func_00347F20(u8 *rec, u8 *o, u32 k, u32 f);
u32 func_0035DD10(int p);
u8 func_0033B970(u32 a);
void func_001F1A30(u8 *o);
void func_001BAF20(u8 *o);
void func_00180D10(u8 *o);
void func_00180E90(u8 *o);
u8 *func_0034A740(u8 *o);
u8 *func_0033B050(u8 *b);
u8 *func_00338410(int base);
void func_003E18F0(u8 *b);
void func_003E3050(u8 *b);
void func_00182960(u8 *b);
float func_001ECC10(u8 *o, int k);
void func_001F11E0(u8 kind, float *f);
u32 func_0034A570(u8 *o);
u32 func_0034A590(u8 *o);
u32 func_0034A490(u8 *o);
u32 func_0034A4B0(u8 *o);
short func_0034A4D0(u8 *o);
u32 func_0034A4F0(u8 *o);
u32 func_0034A510(u8 *o);
short func_0034A470(u8 *o);
void func_0019BD90(int p);

#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))

/* `v` kept within 1-`max`. */
#define CLAMP1(v, max) ((v) > (max) ? (max) : (v) < 2 ? 1 : (v))

/* `v` / 10 kept within 1-24. */
static inline float speed_of(float f)
{
    f = f < 24.0f ? f : 24.0f;
    return f > 1.0f ? f : 1.0f;
}

/* 0x001B92B0, 0x40 bytes. The number of free spare battle officers. */
int func_001B92B0(void)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 0xF; k++) {
        if ((U32(g_006A95B0[k], 0xB8) & 1) == 0)
            n++;
    }
    return n;
}

/* 0x001B92F0, 0x40 bytes. A free spare battle officer (0 for none). */
u8 *func_001B92F0(void)
{
    u32 k;

    for (k = 0; k < 0xF; k++) {
        if ((U32(g_006A95B0[k], 0xB8) & 1) == 0)
            return g_006A95B0[k];
    }
    return 0;
}

/* 0x001B9330, 0xF4 bytes. A random record of side `side` (on the field, present) among the
 * records that can be picked, starting at a random one (0 for none). */
u8 *func_001B9330(u32 side)
{
    int start = g_006AA598 == 0 ? 0 : (int)RANDOM() % (int)g_006AA598;
    u32 k;

    for (k = 0; k < g_006AA598; k++) {
        u8 *o = g_006AA580[(int)(start + k) % (int)g_006AA598];
        u32 f = U32(o, 0x80);

        if ((f & 1) && (f & 0x8C40002) == 0 && (f & 4) == 0 && side == o[0x79])
            return o;
    }
    return 0;
}

/* 0x001B9430, 0x3A8 bytes. Brings in a spare battle officer for record `o` (at its point) or as
 * a copy of battle officer `from` (at its unit's point): its stats from its troop kind, its unit
 * placed and set up. 0 when none is free or the place is blocked. */
u8 *func_001B9430(u8 *o, u8 *from)
{
    u8 cell[8], *at, *b, *t, *u;
    u32 busy, add;
    u8 kind;
    short v;

    if (from == 0) {
        func_001911A0(cell, (float *)((U32(o, 0x80) & 0x20000) ? o + 0x30 : o + 0x28));
        at = cell;
        busy = 0;
    } else {
        at = *(u8 **)(from + 0x14) + 0x40;
        busy = U32(from, 0xB8) & 0xC;
    }
    if (func_00190610(at, 8) != 0 && busy == 0)
        return 0;
    b = func_001B92F0();
    if (b == 0)
        return 0;
    U32(b, 0xBC) = 0;
    add = 0x401;
    U32(b, 0xB8) = 0;
    if (from == 0)
        kind = *(u8 **)(o + 8) == 0 ? 0 : (*(u8 **)(o + 8))[8];
    else
        kind = (*(u8 **)(from + 0x68))[8];
    t = func_003DD3C0(kind);
    *(u8 **)(b + 0x68) = t;
    S16(b, 0x80) = S16(t, 0xC);
    S16(b, 0x84) = S16(t, 0xC);
    S16(b, 0x82) = S16(t, 0xC);
    v = S16(t, 0xE);
    S16(b, 0x86) = v;
    S16(b, 0x88) = 0;          /* (min(v, 0) clamped at 0 in the original) */
    v = S16(t, 0x10);
    S16(b, 0x8A) = CLAMP1(v, 1000);
    v = S16(t, 0x12);
    S16(b, 0x8C) = CLAMP1(v, 1000);
    v = S16(t, 0x14);
    S16(b, 0x8E) = CLAMP1(v, 0x15E);
    *(float *)(b + 0x90) = speed_of((float)S16(t, 0x16) * 0.1f);
    *(float *)(b + 0x94) = speed_of((float)S16(t, 0x18) * 0.1f);
    func_001BA3D0(b);
    U32(b, 0xBC) &= 0xFFF8003F;
    b[0x7D] = 0;
    u = *(u8 **)(b + 0x14);
    func_00166080(u, o[0x79], kind);
    U32(u, 0x238) = U32(o, 0x20);
    u[0x27C] &= 0xFE;
    U32(u, 0x54) = U32(o, 0x20);
    func_001660C0(u, at);
    func_002071F0(b, at);
    *(u32 *)(b + 0x30) = *(u32 *)(b + 0x18);
    *(u32 *)(b + 0x34) = *(u32 *)(b + 0x1C);
    if (from == 0) {
        if (*(u32 *)(b + 8) != 0)
            U32(b, 0xBC) &= ~2u;
        *(u32 *)(b + 8) = 0;
        U32(b, 0xB8) |= 0x401;
    } else {
        if (U32(from, 0xB8) & 0x800)
            add = 0xC01;
        U32(b, 0xB8) |= add;
        if (func_00190610(at, 8) == 0)
            func_0016BD80(*(u8 **)(from + 0x14), u, 1);
    }
    return b;
}

/* A map coordinate in 100ths, kept within 0-0x63F. */
static inline short map_coord(float v)
{
    short s = (short)(int)v;

    if (s > 0x63F)
        s = 0x63F;
    return s < 1 ? 0 : s;
}

/* 0x001B97E0, 0x25C bytes. Player `p`'s helper (a record found by func_0034AD10) joins the battle
 * next to the player's unit `u`: its record copied with its place, set up, and kept as the
 * player's helper (+0x6AA5D0, with a timer of 1500). Whether one came. */
int func_001B97E0(int p, u8 *u)
{
    u8 *o = func_0034AD10(), cell[2], rec[0x30];
    u32 k;

    if (o == 0)
        return 0;
    k = func_003489E0(0, 0);
    if (k >= 0x25)
        return 0;
    func_001F0CD0(u, cell);
    if (cell[0] == 0 || cell[1] == 0)
        return 0;
    func_00118AC0(rec, *(u8 **)(*(u8 **)(u + 0x10) + 4), 0x20);
    rec[0x17] = 1;
    *(u16 *)(rec + 6) = 500;
    *(short *)(rec + 2) = map_coord(((float)cell[0] * 1000.0f + 500.0f) / 100.0f);
    rec[0x11] = 0;
    *(short *)(rec + 4) = map_coord(((float)cell[1] * 1000.0f + 500.0f) / 100.0f);
    func_00347F20(rec, o, k, 0x200000);
    o[0x7F] = func_0033B970(func_0035DD10(p));
    func_001F1A30(o);
    g_006AA5D0[p] = (o - g_00693970[0]) / 0x88;
    g_006AA5C8[p] = 0x5DC;
    func_001BAF20(o);
    return 1;
}

/* 0x001B9A40, 0x194 bytes. Takes record `o` out of the battle: its musou goes back to its base,
 * its point is kept, and its battle officer and the ones following it are freed. */
void func_001B9A40(u8 *o)
{
    u8 *b = g_00693970[0] + 0x100C0 + U32(o, 0x14) * 0xC0, *x;
    u8 pt[8];

    func_00180D10(o);
    if ((U32(o, 0x80) & 0x800) && (U32(b, 0xB8) & 0x80)) {
        u8 *base = func_0034A740(o);

        if (func_0033B050(base) != 0)
            *(u16 *)(func_00338410((base - (g_00693970[0] + 0xE3E8)) / 0x68) + 0x20) = *(u16 *)(b + 0x88);
    }
    func_00191200(pt, (float *)(*(u8 **)(b + 0x14) + 0x90));
    *(u32 *)(o + 0x30) = *(u32 *)pt;
    *(u32 *)(o + 0x34) = *(u32 *)(pt + 4);
    for (x = b; x != 0; x = *(u8 **)(x + 4)) {
        u8 *y;

        func_003E18F0(x);
        func_003E3050(x);
        y = *(u8 **)(x + 0xC);
        func_00182960(x);
        if (y != 0)
            func_00182960(y);
    }
    func_00180E90(o);
    if ((U32(o, 0x80) & 4) && (U32(o, 0x80) & 2) == 0 && o[0x74] == 0 && o[0x7A] != 3)
        U32(o, 0x80) |= 2;
}

/* 0x001B9BE0, 0x7EC bytes. Battle officer `b`'s stats for record `o` (kind `t` for troops):
 * life `max` / `cur`, musou, attack and defence (scaled by the battle's modifiers and its kind's
 * factor), the rest, kept within their ranges. */
void func_001B9BE0(u8 *b, u8 *o, u8 *t, short max, short cur)
{
    int troop = b[0x7F] != 0;
    float ka, kd, kk, sp1, sp2;
    int at, df;
    short v, c, m;

    if ((U32(b, 0xB8) & 0x6C) == 0) {
        ka = func_001ECC10(o, 2);
        kd = func_001ECC10(o, 3);
    } else {
        ka = 1.0f;
        kd = 1.0f;
    }
    kk = 1.0f;
    if (U32(b, 0xB8) & 0x80)
        func_001F11E0(o[0x7E], &kk);
    if (U32(b, 0xB8) & 0x8000) {
        at = S16(o, 0x54);
        df = S16(o, 0x56);
    } else if (troop) {
        at = (int)(kk * ka * (float)func_0034A570(o));
        df = (int)(kk * kd * (float)func_0034A590(o));
    } else {
        at = (int)(kk * ka * (float)func_0034A490(o));
        df = (int)(kk * kd * (float)func_0034A4B0(o));
    }
    if (at > 1000)
        at = 1000;
    if (df > 1000)
        df = 1000;
    if (troop) {
        v = S16(t, 0x14);
        sp1 = (float)S16(t, 0x16) * 0.1f;
        sp2 = (float)S16(t, 0x18);
    } else {
        v = func_0034A4D0(o);
        sp1 = (float)func_0034A4F0(o) * 0.1f;
        sp2 = (float)func_0034A510(o);
    }
    sp2 = sp2 * 0.1f;
    S16(b, 0x80) = max;
    c = cur < max ? cur : max;
    S16(b, 0x82) = c < 2 ? 1 : c;
    if (S16(b, 0x84) < S16(b, 0x82))
        S16(b, 0x84) = S16(b, 0x82);
    m = S16(b, 0x82) < S16(b, 0x80) ? S16(b, 0x82) : S16(b, 0x80);
    S16(b, 0x84) = m < 1 ? 0 : m;
    S16(b, 0x86) = troop ? S16(t, 0xE) : func_0034A470(o);
    S16(b, 0x88) = 0;          /* (min(musou, 0) clamped at 0 in the original) */
    if ((U32(o, 0x80) & 0x800) && (U32(b, 0xB8) & 0x80)) {
        u8 *base = func_0034A740(o);

        if (func_0033B050(base) != 0) {
            short s = *(short *)(func_00338410((base - (g_00693970[0] + 0xE3E8)) / 0x68) + 0x20);

            s = s < S16(b, 0x86) ? s : S16(b, 0x86);
            S16(b, 0x88) = s < 1 ? 0 : s;
        }
    }
    S16(b, 0x8A) = CLAMP1((short)at, 1000);
    S16(b, 0x8C) = CLAMP1((short)df, 1000);
    S16(b, 0x8E) = CLAMP1(v, 0x15E);
    *(float *)(b + 0x90) = speed_of(sp1);
    *(float *)(b + 0x94) = speed_of(sp2);
}

/* 0x001BA3D0, 0xA4 bytes. Clears battle officer `b`'s skill values (the players' own get theirs
 * back). */
void func_001BA3D0(u8 *b)
{
    int k;

    *(float *)(b + 0x98) = 1.0f;
    *(float *)(b + 0x9C) = 1.0f;
    b[0xA9] = 0;
    b[0xB5] = 0;
    *(u32 *)(b + 0xA0) = 0;
    b[0xA7] = 0;
    b[0xA6] = 0;
    b[0xA8] = 0;
    for (k = 0xAA; k <= 0xB1; k++)
        b[k] = 0;
    b[0xB2] = 0x9F;
    b[0xB3] = 1;
    b[0xB4] = 0;
    *(u16 *)(b + 0xA4) = 0;
    if (U32(b, 0xB8) & 4)
        func_0019BD90(0);
    else if (U32(b, 0xB8) & 8)
        func_0019BD90(1);
}

extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each) */
extern u8 *g_005BA7C8;                   /* the unit records (0x20 bytes each) */
extern u32 g_00669F60[4];
extern int g_00669F6C[4];
extern u8 g_00669D81[0x10];
extern int g_00669F88[4];
extern u8 *g_006AA59C[2];                /* the two sides' leading reinforcements */

int func_003E6F90(u8 *b);
u32 func_001F0540(u8 side);
u8 func_002F6980(u16 k);
void func_001656E0(u8 *u, u8 a, u8 b, u8 c, u32 d, u8 side, u8 f, int g);
void func_00164DA0(u8 *u, int a);
void func_002075A0(u32 a, u8 *b, u8 *cell, int c);
void func_00253B50(u8 *u, u8 kind);
int func_0032E7B0(void);
void func_00355D60(u8 *a, u8 *b, int c);

/* 0x001BA480, 0xAA0 bytes. Sets battle officer `b` up for record `o` with table record `t`
 * (life `max` / `cur`, `troop` for a troop): its links and random think rate, skills cleared,
 * stats, its kind from the table (+0x1C: officers 0-3, troops 5-10), its level (in Empire battles
 * from the record's unit and its base's value), its unit's model and colours, its place on the
 * map, and for officers with followers a reinforcement brought in at its side. */
void func_001BA480(u8 *o, u8 *b, u8 *t, short max, short cur, int troop)
{
    u8 side = o[0x79], *u, *at;
    u8 cell[0x18];
    float pt[2];
    u32 n, kind;
    u8 skin, mk;

    *(u32 *)(b + 4) = 0;
    *(u32 *)b = 0;
    *(u8 **)(b + 0x10) = o;
    *(u8 **)(b + 0x68) = t;
    if (*(u32 *)(b + 8) != 0)
        U32(b, 0xBC) &= ~2u;
    *(u32 *)(b + 8) = 0;
    b[0x7C] = 3;
    if ((g_00669F60[0] & 8) == 0 && (U32(b, 0xB8) & 0x8000) == 0)
        n = (U32(b, 0xB8) & 0x260) == 0 ? RANDOM() & 1 : 2;
    else
        n = 0;
    b[0x42] = 0;
    *(float *)(b + 0x58) = (float)n == 0.0f ? 0.0f : 1.0f / (float)n;
    *(u32 *)(b + 0x6C) = 0;
    *(int *)(b + 0x74) = -1;
    U32(b, 0xBC) &= 0xFFF8003F;
    b[0x7D] = 0;
    *(u16 *)(b + 0x78) = 0;
    b[0x7E] = 0;
    b[0x7F] = (u8)troop;
    func_001BA3D0(b);
    func_001B9BE0(b, o, t, max, cur);
    if ((U32(b, 0xB8) & 0x60) == 0) {
        u8 c = t[0x1C];

        if (c == 1) {
            U32(b, 0xB8) |= 0x1000;
            b[0x7A] = 0;
        } else {
            b[0x7A] = c == 0xB ? 3 : c == 0xA ? 2 : c == 9 ? 1 : 0;
        }
    } else {
        switch (t[0x1C]) {
        case 0xC: b[0x7A] = 5; break;
        case 0xD: b[0x7A] = 6; break;
        case 0xE: b[0x7A] = 7; U32(b, 0xB8) |= 0x1000; break;
        case 0xF: b[0x7A] = 8; break;
        case 0x10: b[0x7A] = 9; break;
        case 0x11: b[0x7A] = 10; break;
        default: b[0x7A] = 5; break;
        }
    }
    if ((U32(b, 0xB8) & 0xC) != 0) {
        b[0x7B] = 0x13;
    } else if (g_00669F60[0] & 8) {
        u32 lv = t[0x1D], unit = *(u8 **)(o + 4) == 0 ? 0xFFFFFFFF
                                                     : (u32)((*(u8 **)(o + 4) - g_005BA7C8) / 0x20);

        if ((g_00669F60[0] & 2) && unit < 0x1B) {
            int k = *(short *)(*(u8 **)(o + 4) + 2) / 400;

            lv = t[0x1D] + (k > 3 ? 3 : k);
        }
        lv &= 0xFF;
        b[0x7B] = lv > 0x13 ? 0x13 : (u8)lv;
    } else {
        int v = 0, lv;

        if (U32(o, 0x10) < 0x47) {
            u8 *base = g_00693970[0] + 0xE3E8 + U32(o, 0x10) * 0x68;

            if ((g_00669F60[0] & 0xC) == 0)
                v = *(int *)(base + 0x4C);
            else
                v = (*(u8 **)base)[0x79] == 0 ? 0x15E : 0x28A;
            v = v - 1;
        }
        if (v < 1)
            v = 0;
        v = g_00669D81[0] == 4 ? v / 0xFA : v / 200 - 2;
        v = v + g_00669F88[0] / 3 - 2;
        if (g_00669D81[0] == 0)
            v = v - 2;
        v = v < -3 ? -4 : v > 4 ? 4 : v;
        lv = func_003E6F90(b);
        lv = lv > 0x13 ? 0x13 : lv < 1 ? 0 : lv & 0xFF;
        b[0x7B] = (u8)lv;
    }
    u = *(u8 **)(b + 0x14);
    kind = (U32(t, 0x28) & 1) == 0 ? 0x11 : func_001F0540(side);
    if (g_005BA6A0[((t - g_005BA6A0) / 0x2C) * 0x2C + 6] < 0x1C)
        skin = 0;
    else if ((U32(o, 0x80) & 0x400) == 0 || (U32(o, 0x80) & 0x800) == 0 || troop != 0)
        skin = o[0x7F];
    else
        skin = func_002F6980(*func_00338410((func_0034A740(o) - (g_00693970[0] + 0xE3E8)) / 0x68));
    mk = t[7];
    if (u[0x14E] >= 2 && mk > 0x19) {
        if (mk >= 0x3E && mk <= 0x48)
            mk = 0x26;
        else if (mk >= 0x49 && mk <= 0x53)
            mk = 0x2A;
        else if (mk >= 0x54 && mk <= 0x5C)
            mk = 0x20;
        else if (mk > 0x5C && mk < 0x68)
            mk = 0x21;
    }
    func_001656E0(u, t[6], mk, t[9], kind, side, skin,
                  (U32(t, 0x28) & 0x10) == 0 && (U32(t, 0x28) & 0x20) == 0);
    if (U32(b, 0xB8) & 0xC)
        func_00164DA0(u, 1);
    U32(u, 0x238) = U32(o, 0x20);
    u[0x27C] &= 0xFE;
    U32(u, 0x54) = U32(o, 0x20);
    if ((g_00669F60[0] & 8) == 0 && (U32(b, 0xB8) & 0x60) == 0) {
        pt[0] = (float)o[0x46] * 1000.0f + 500.0f;
        pt[1] = (float)o[0x47] * 1000.0f + 500.0f;
    } else {
        float *p = (float *)((U32(o, 0x80) & 0x20000) ? o + 0x30 : o + 0x28);

        pt[0] = p[0];
        pt[1] = p[1];
    }
    func_001911A0(cell, pt);
    func_002075A0(U32(o, 0x20), b, cell, 0);
    func_001660C0(u, cell);
    func_002071F0(b, cell);
    *(u32 *)(b + 0x30) = *(u32 *)(b + 0x18);
    *(u32 *)(b + 0x34) = *(u32 *)(b + 0x1C);
    if (U32(b, 0xB8) & 0x80)
        func_00253B50(u, o[0x7E]);
    if (func_0032E7B0() != 0)
        return;
    if (U32(b, 0xB8) & 0x800) {
        if (func_001B9430(o, b) == 0)
            U32(b, 0xB8) &= 0xFFFFD7FF;
    } else if ((U32(b, 0xB8) & 0x80) && (U32(o, 0x80) & 0x80000) && (g_00669F60[0] & 0x10) == 0) {
        if ((U32(b, 0xB8) & 0xC) == 0) {
            func_001B9430(o, b);
        } else if (g_00669F6C[0] != 1) {
            u8 *r = func_001B9430(o, b);

            if (r != 0) {
                int s = (U32(b, 0xB8) & 4) == 0;

                at = cell;
                if (*(u32 *)(b + 0xC) == 0) {
                    func_00355D60(at, at, s);
                    func_001660C0(*(u8 **)(r + 0x14), at);
                }
                if (g_006AA59C[s] != 0) {
                    U32(g_006AA59C[s], 0xB8) &= 0xFFF9FFFF;
                    U32(g_006AA59C[s], 0xBC) &= 0xFEFFFFFF;
                    g_006AA59C[s] = 0;
                }
                U32(r, 0xB8) |= s ? 0x40000 : 0x20000;
                g_006AA59C[s] = r;
            }
        }
    }
}

int func_0034A5F0(u8 *o);
u8 *func_001828C0(void);
void func_003E1880(u8 *b);

/* 0x001BAF20, 0x5BC bytes. Brings record `o`'s group into the battle: its leader (the record's
 * officer table entry +8, with its life +0x4C / +0x4E and flags for players, bases and Empire
 * officers) and its followers (+0x74, of troop kind +0xC, sharing the rest of the life +0x50 /
 * +0x52), linked in a list; all freed again when one cannot be had. A lone reinforcement
 * (flag 0x4000) comes through func_001B9430. */
void func_001BAF20(u8 *o)
{
    u8 *g[10], *lead, *troop;
    u32 n, i, parts;
    short life, cur, max0, max1;
    int many = 0, k;

    if (U32(o, 0x80) & 0x4000) {
        func_001B9430(o, 0);
        return;
    }
    if ((U32(o, 0x80) & 0x80000) && func_001B92F0() == 0)
        return;
    lead = *(u8 **)(o + 8);
    if ((U32(lead, 0x28) & 4) && func_001B92B0() < (u32)o[0x74] + 2)
        return;
    troop = *(u8 **)(o + 0xC);
    life = S16(o, 0x52);
    cur = S16(o, 0x4E);
    max0 = S16(o, 0x4C);
    max1 = S16(o, 0x50);
    k = func_0034A5F0(o);
    n = o[0x74] + 1;
    parts = cur == 0 ? n : o[0x74];
    if (n > 10)
        n = 10;
    for (i = 0; i < n; i++) {
        u8 *b = func_001828C0();

        if (b == 0) {
            u32 j;

            for (j = 0; j < i; j++) {
                U32(g[j], 0xBC) = 0;
                U32(g[j], 0xB8) = 0;
            }
            return;
        }
        g[i] = b;
    }
    for (; i < 10; i++)
        g[i] = 0;
    for (i = 0; i < n && g[i] != 0; i++) {
        u8 *b = g[i], *t = troop;
        u32 f = 0;
        short m, c;

        if (i == 0) {
            if (cur < 1) {
                c = (short)(life / (int)parts);
                m = k < 1 ? c : (short)((max1 - max0) / k);
                if (m < 1 && (m = max0) > 99)
                    m = 100;
                f = 0x100;
            } else {
                u32 of = U32(o, 0x80);

                f = (of & 0x400) ? 0x280 : 0x80;
                if (of & 0x800)
                    f |= 0x100000;
                if (o[0x79] != 0 && ((of & 0x200)
                                     || ((of & 0x400) && (u32)((lead - g_005BA6A0) / 0x2C) < 0x28)))
                    f |= 0x80000;
                t = lead;
                m = max0;
                c = cur;
                if ((U32(lead, 0x28) & 0xFC) && (u32)((k << 2) / 5) <= n)
                    many = 1;
            }
        } else {
            c = (short)((life - cur) / (int)parts);
            m = k < 1 ? c : (short)((max1 - max0) / k);
        }
        if (U32(o, 0x80) & 0x8000)
            f |= 0x8000;
        if (U32(o, 0x80) & 0x200000)
            f |= 0x10000;
        if (U32(t, 0x28) & 0xFC) {
            if (many)
                f |= 0x2000;
            if (U32(t, 0x28) & 4)
                f |= 0x800;
        }
        U32(b, 0xB8) |= f;
        func_001BA480(o, b, t, m, c, i);
        if (i == 0) {
            *(u8 **)(b + 4) = g[1];
        } else if (i == n - 1) {
            *(u8 **)b = g[i - 1];
        } else {
            *(u8 **)b = g[i - 1];
            *(u8 **)(b + 4) = g[i + 1];
        }
    }
    for (i = 0; i < 10; i++) {
        if (g[i] != 0)
            func_003E1880(g[i]);
    }
}

#define g_70000164 (*(int *)0x70000164)    /* (scratchpad) how many units can be in battle */
#define g_7000016C (*(float *)0x7000016C)  /* (scratchpad) the drawing distance */
#define g_70000170 (*(float *)0x70000170)  /* (scratchpad) its square */

extern u32 g_006AA5A0, g_006AA5A4, g_006AA5A8, g_006AA5AC, g_006AA5B0, g_006AA5B4, g_006AA5B8;
extern int g_006AA5D8;
extern float g_006AA5DC;                 /* a difficulty factor */
extern u32 g_006AA5E0;
extern u32 g_00669F84;
extern int g_00669F98[4];

/* A slot keyed by an id (0xFFFF: free). */
typedef struct {
    u32 id;
    u32 pad;
    u32 a, b;
} Slot;

extern Slot g_006AAAE0[0xD6];
extern Slot g_006AA9B0[0x12];
extern Slot g_006AA630[0x38];
extern u8 g_006AAAD0[0x10];

void func_00180EC0(u8 *o, int b);
void func_001D5AC0(int *base);
void func_001817E0(void); void func_00204920(void); void func_001EC790(void);
void func_00347790(void); void func_0034EBE0(void); void func_001827F0(void);
void func_00180BF0(void); void func_001D58C0(void); void func_0033AFB0(void);
void func_0034B9A0(void); void func_0033E820(void); int func_001902A0(void);
void func_001902B0(void); void func_00182C20(void); void func_001D5DA0(void);
void func_00182340(void); void func_0034B980(void); void func_00182350(void);
void func_001D5DC0(void); void func_00182C30(void); void func_0034B8B0(void);
void func_00118850(void *p, u32 n);

/* 0x001BB4F0, 0xD0 bytes. Brings record `o` (a player's officer) in as battle officer `b`: flag
 * 4 or 8 by its side (+0x80 bit 4), a player, in use, linked to the record. */
void func_001BB4F0(u8 *o, u8 *b)
{
    u32 f = (U32(o, 0x80) & 0x10) ? 4 : 8;

    f = (U32(o, 0x80) & 0x40) ? f | 0x290 : f | 0x280;
    U32(b, 0xB8) |= f | 0x100000;
    func_001BA480(o, b, *(u8 **)(o + 8), S16(o, 0x4C), S16(o, 0x4E), 0);
    U32(b, 0xB8) |= 1;
    func_00180EC0(o, (b - (g_00693970[0] + 0x100C0)) / 0xC0);
    func_003E1880(b);
}

/* 0x001BB5C0, 0x114 bytes. Puts record `o` into the first free of the 13 places of base `base`
 * (a base's commander, flags 0x1800, also sets its strength from `t`, 500 without, within
 * 1-1000). */
void func_001BB5C0(u8 *t, u8 *o, int *base)
{
    u32 k;

    if (U32(o, 0x80) & 0x1800) {
        u32 v;

        func_001D5AC0(base);
        v = t == 0 ? 500 : *(u16 *)(t + 6);
        base[0x12] = v > 1000 ? 1000 : v < 2 ? 1 : v;
        base[0x19] |= 1;
    }
    for (k = 0; k < 0xD; k++) {
        if (base[k] == 0) {
            base[k] = (int)o;
            break;
        }
    }
    U32(o, 0x10) = ((u8 *)base - (g_00693970[0] + 0xE3E8)) / 0x68;
}

/* 0x001BB6E0, 0x6C bytes. Sets the drawing distance (by at most 50 a call when `smooth`). */
void func_001BB6E0(float d, int smooth)
{
    if (smooth != 0) {
        if (d < g_7000016C) {
            float m = g_7000016C - 50.0f;

            d = m < d ? d : m;
        } else if (g_7000016C < d) {
            float m = g_7000016C + 50.0f;

            d = d < m ? d : m;
        }
    }
    g_7000016C = d;
    g_70000170 = d * d;
}

/* 0x001BB760, 0x84 bytes, matching. Each frame's battle steps. */
void func_001BB760(void)
{
    func_001817E0();
    func_00204920();
    func_001EC790();
    func_00347790();
    func_0034EBE0();
    func_001827F0();
    func_00180BF0();
    func_001D58C0();
    func_0033AFB0();
    func_0034B9A0();
    func_0033E820();
    if (func_001902A0() != 0)
        func_001902B0();
}

/* 0x001BC280, 0x34 bytes, matching. */
void func_001BC280(void)
{
    func_00182C20();
    func_001D5DA0();
    func_00182340();
    func_0034B980();
}

/* 0x001BC2C0, 0x274 bytes. Resets the battle's officers: the drawing distance (7500), the
 * pickable records, reinforcements and helpers, and by the game mode the number of units in
 * battle and a difficulty factor (Empire stages: more with the stage, at most 5). */
void func_001BC2C0(void)
{
    func_00182350();
    func_001D5DC0();
    func_00182C30();
    func_0034B8B0();
    func_001BB6E0(7500.0f, 0);
    g_006AA598 = 0;
    g_006AA59C[0] = 0;
    g_006AA5C8[0] = 0;
    g_006AA5D0[0] = 0x1AD;
    g_006AA5A0 = 0;
    g_006AA5C8[1] = 0;
    g_006AA5D0[1] = 0x1AD;
    g_006AA5D8 = 0x1AD;
    g_006AA5A4 = 0;
    g_006AA5B0 = 0;
    g_006AA5A8 = 0;
    g_006AA5B4 = 0;
    g_006AA5AC = 0;
    g_006AA5B8 = 0;
    if (g_00669F60[0] & 4) {
        float s = (float)(g_00669F98[0] - 0x3C);

        g_70000164 = 0x8F;
        s = (float)(int)(s >= 0.0f ? s : 0.0f) * 0.01f + 1.0f;
        g_006AA5DC = s > 5.0f ? 5.0f : s;
    } else if (g_00669F60[0] & 8) {
        g_70000164 = 0x8F;
        g_006AA5DC = 1.0f;
    } else if (g_00669D81[0] == 4) {
        float s = (float)g_00669F84 * 0.5f + 1.0f;

        g_70000164 = 0x8F;
        g_006AA5DC = s < 1.0f ? 1.0f : s;
    } else if (g_00669D81[0] == 3) {
        g_70000164 = 0x47;
        g_006AA5DC = 1.0f;
    } else if (g_00669D81[0] == 2) {
        g_70000164 = 0x2F;
        g_006AA5DC = 1.0f;
    } else if (g_00669D81[0] == 1) {
        g_70000164 = 0x23;
        g_006AA5DC = 0.5f;
    } else if (g_00669D81[0] == 0) {
        g_70000164 = 0x23;
        g_006AA5DC = 0.3f;
    } else {
        g_70000164 = 0x8F;
        g_006AA5DC = 1.0f;
    }
    g_006AA5E0 = 1;
}

/* 0x001BC540, 0x104 bytes. Frees the 0xD6 slots at 0x006AAAE0. */
void func_001BC540(void)
{
    int k;

    for (k = 0; k < 0xD6; k++) {
        g_006AAAE0[k].id = 0;
        g_006AAAE0[k].a = 0;
        g_006AAAE0[k].pad = 0xFFFF;
        g_006AAAE0[k].b = 0xFFFF;
    }
}

/* 0x001BC650, 0x3C bytes. The slot whose +4 is `id` (0 for none). */
Slot *func_001BC650(u32 id)
{
    int k;

    for (k = 0; k < 0xD6; k++) {
        if (g_006AAAE0[k].pad == id)
            return &g_006AAAE0[k];
    }
    return 0;
}

/* 0x001BC690, 0x74 bytes. Frees the 0x12 slots at 0x006AA9B0. */
void func_001BC690(void)
{
    int k;

    func_00118850(g_006AAAD0, 0x10);
    for (k = 0; k < 0x12; k++) {
        g_006AA9B0[k].id = 0xFFFF;
        g_006AA9B0[k].a = 0;
        g_006AA9B0[k].b = 0;
    }
}

/* 0x001BC710, 0x84 bytes. Frees the 0x38 slots at 0x006AA630. */
void func_001BC710(void)
{
    int k;

    func_00118850(g_006AAAD0, 0x10);
    for (k = 0; k < 0x38; k++) {
        g_006AA630[k].id = 0xFFFF;
        g_006AA630[k].a = 0;
        g_006AA630[k].b = 0;
    }
}

/* 0x001BC7A0, 0x88 bytes, matching. The slot of id `id` among the 0x12, else a free one (0 for none). */
Slot *func_001BC7A0(u32 id)
{
    int k;

    for (k = 0; k < 0x12; k++) {
        if (id == g_006AA9B0[k].id)
            return &g_006AA9B0[k];
    }
    for (k = 0; k < 0x12; k++) {
        if (g_006AA9B0[k].id == 0xFFFF)
            return &g_006AA9B0[k];
    }
    return 0;
}

/* 0x001BC830, 0x88 bytes, matching. The same among the 0x38. */
Slot *func_001BC830(u32 id)
{
    int k;

    for (k = 0; k < 0x38; k++) {
        if (id == g_006AA630[k].id)
            return &g_006AA630[k];
    }
    for (k = 0; k < 0x38; k++) {
        if (g_006AA630[k].id == 0xFFFF)
            return &g_006AA630[k];
    }
    return 0;
}
