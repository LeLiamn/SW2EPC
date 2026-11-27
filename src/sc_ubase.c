/*
 * sc_ubase.c - scenario units and bases (original source file sc_ubase.c: its name is passed to
 * the file loader at 0x0019A7B0, where it opens LINKDATA entry 0x33, the officer table).
 * Written so far: functions from 0x0019A7B0.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Officer ids: below 0x2D3 the named officers (names table at 0x0042C730), 0x2D3-0x2F0 the
 * created officers (two per slot), 0x2F1-0x2F8 the items' wearers; 0x2D2 stands for the player.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))

#define g_7000015C (*(u32 *)0x7000015C)          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

extern u8 *g_005BA69C;                   /* the officer table's file */
extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each, from +4) */
extern u32 *g_005BA7C4;                  /* +0: the number of 0x20-byte unit records */
extern u8 *g_005BA7C8;                   /* the unit records */
extern u32 g_00669DB8[4];                /* (settings) +0: the game mode */
extern const char g_00425688[];          /* "sc_ubase.c" */
extern const char g_00425740[];          /* "" */
extern const char g_00425748[];          /* the "name (title)" format */
extern const char *g_0042C730[0x2D3];    /* the named officers' names */
extern const char *g_0042EE20[];         /* the troop kinds' names (6 per kind) */
extern float g_00424EC0[8];              /* the eight facing angles */
extern float g_004256A0[12], g_004256D0[12];   /* offsets around a unit (sides, ahead) */
extern int g_00425700[8], g_00425720[8]; /* the eight directions (x, z) */
extern u8 g_00428138[];

void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00118AC0(void *d, const void *s, u32 n);
void func_00120928(char *to, const char *from);
void func_001204B0(char *to, const char *format, ...);
void vu0_sincos(float a, float *s, float *c);    /* VU0 micro subroutine 0x20 */
int func_0018C0E0(float *p);
int func_0018C2A0(float *p);
int func_00215480(u8 *cell);
short func_0018F6F0(u8 *from, u8 *to, int side);
int func_00328230(void);
int func_001AA320(float size, const void *font, u32 id);
const char *func_0039E680(void);
const char *func_0039E6A0(u32 slot);
u8 *func_0019FBC0(int item);
u32 func_002F27D0(u32 id);
u32 func_0019A5A0(u32 code);
u8 func_002F41E0(u32 kind);
u32 func_002F5730(u32 id);
u8 *func_0035DEC0(u32 a, u32 b);

/* 0x0019A7B0, 0x50 bytes. Loads the officer table (LINKDATA entry 0x33). */
void func_0019A7B0(void)
{
    g_005BA69C = func_001026D0(1, 0x33, 0, 1, 0, 0, g_00425688, 0xF5);
    g_005BA6A0 = g_005BA69C + 4;
}

/* A map coordinate in 100ths, kept within 0-0x63F. */
static inline short map_coord(float v)
{
    short s = (short)(int)(v / 100.0f);

    if (s > 0x63F)
        s = 0x63F;
    return s < 1 ? 0 : s;
}

/* Whether the point `p` (cell `c`) can be stood on and reached from cell `from`. */
static inline int can_place(float *p, u8 *c, u8 *from)
{
    c[0] = (u8)((int)p[0] / 5000);
    c[1] = (u8)((int)p[1] / 5000);
    return func_0018C0E0(p) != 0 && func_0018C2A0(p) != 0 && func_00215480(c) == 0
           && func_0018F6F0(from, c, 0) != 0xFFF;
}

/* 0x0019A800, 0x588 bytes. Places unit `u` (+0xE its facing) at spot `k` around the point
 * (x, z) x 100: the spot itself if it can be stood on and reached, else the first good one of
 * five rings of eight directions (in a random order). Its point goes to +2 / +4. Whether one was
 * found. */
int func_0019A800(u8 *u, int k, int x, int z)
{
    float cx = (float)x * 100.0f, cz = (float)z * 100.0f;
    float p[2], s, c;
    u8 from[2], cell[2];
    int i, j;
    u32 r1, r2;

    from[0] = (u8)((int)cx / 5000);
    from[1] = (u8)((int)cz / 5000);
    vu0_sincos(g_00424EC0[u[0xE]], &s, &c);
    p[0] = (s * g_004256D0[k] + c * g_004256A0[k]) * 1000.0f + cx + 0.0f;
    p[1] = (c * g_004256D0[k] - s * g_004256A0[k]) * 1000.0f + cz + 0.0f;
    if (can_place(p, cell, from)) {
        *(short *)(u + 2) = map_coord(p[0]);
        *(short *)(u + 4) = map_coord(p[1]);
        return 1;
    }
    r1 = RANDOM();
    for (i = 0; i < 5; i++) {
        int ring = (int)(r1 % 5 + i) % 5;

        r2 = RANDOM();
        for (j = 0; j < 8; j++) {
            int d = ((r2 & 7) + j) % 8;

            p[0] = cx + (float)(ring * g_00425700[d] * 1000);
            p[1] = cz + (float)(ring * g_00425720[d] * 1000);
            if (can_place(p, cell, from)) {
                *(short *)(u + 2) = map_coord(p[0]);
                *(short *)(u + 4) = map_coord(p[1]);
                return 1;
            }
        }
    }
    return 0;
}

/* 0x0019AD90, 0x80 bytes. Loads the unit records from `p`; returns the end. */
u8 *func_0019AD90(u8 *p)
{
    u32 n = *g_005BA7C4, k;
    u8 *r = g_005BA7C8;

    for (k = 0; k < n; k++, p += 0x20, r += 0x20)
        func_00118AC0(r, p, 0x20);
    return p;
}

/* 0x0019AE10, 0x80 bytes. Saves them to `p`; returns the end. */
u8 *func_0019AE10(u8 *p)
{
    u32 n = *g_005BA7C4, k;
    u8 *r = g_005BA7C8;

    for (k = 0; k < n; k++, p += 0x20, r += 0x20)
        func_00118AC0(p, r, 0x20);
    return p;
}

/* 0x0019AE90, 0x60 bytes. The title shown for title `t` (0x2D2, the player's: 0x17, or 0x18
 * outside mode 1 when func_00328230 says no). */
u32 func_0019AE90(u32 t)
{
    if (t == 0x2D2) {
        if (g_00669DB8[0] == 1)
            t = 0x17;
        else if (func_00328230() == 0)
            t = 0x18;
        else
            t = 0x17;
    }
    return t;
}

/* 0x0019AEF0, 0x20 bytes. The same, always 0x17. */
u32 func_0019AEF0(u32 t)
{
    if (t == 0x2D2)
        t = 0x17;
    return t;
}

/* 0x0019AF10, 0xB4 bytes. Width at size `size` of name `n` with title `t` (when they differ,
 * both and a gap). */
int func_0019AF10(float size, u32 t, u32 n)
{
    u32 a = func_0019AE90(t);
    int w = func_001AA320(size, (const void *)0x4053F0, a);

    if (a != n)
        w = w + func_001AA320(size, (const void *)0x4053F0, n) + (int)(size * 8.0f / 20.0f);
    return w + 1;
}

/* 0x0019AFD0, 0xE8 bytes. Officer `id`'s name ("" for created officers and wearers when
 * `blank`). */
const char *func_0019AFD0(u32 id, int blank)
{
    if (id < 0x2D3)
        return g_0042C730[id];
    if (id < 0x2F1) {
        if (blank != 0)
            return g_00425740;
        if (((id - 0x2D3) & 1) == 0)
            return func_0039E680();
        return func_0039E6A0((id - 0x2D3) >> 1);
    }
    if (id < 0x2F9) {
        u8 *it = func_0019FBC0(((int)id - 0x2F1) / 2);

        if (blank != 0)
            return g_00425740;
        return (const char *)(it + 0x13);
    }
    return g_00425740;
}

/* 0x0019B0C0, 0x1C bytes. */
void func_0019B0C0(u32 id)
{
    func_0019AFD0(id, 0);
}

/* 0x0019B0E0, 0x48 bytes. Copies title `t`'s name to `out`. */
char *func_0019B0E0(char *out, u32 t)
{
    func_00120928(out, func_0019AFD0(func_0019AE90(t), 0));
    return out;
}

/* 0x0019B130, 0x3C bytes. Copies officer `id`'s name to `out`. */
char *func_0019B130(char *out, u32 id)
{
    func_00120928(out, func_0019AFD0(id, 0));
    return out;
}

/* 0x0019B170, 0x8C bytes. Writes name `n` with title `t` ("name (title)" when they differ). */
char *func_0019B170(char *out, u32 t, u32 n)
{
    u32 a = func_0019AE90(t);

    func_00120928(out, func_0019AFD0(n, 0));
    if (a != n)
        func_001204B0(out, g_00425748, out, func_0019AFD0(a, 0));
    return out;
}

/* 0x0019B200, 0x38 bytes. The same with the player's title as 0x17. */
char *func_0019B200(char *out, u32 t, u32 n)
{
    func_0019B170(out, func_0019AEF0(t), n);
    return out;
}

/* 0x0019B240, 0x38 bytes. */
char *func_0019B240(char *out, u32 t)
{
    func_0019B0E0(out, func_0019AEF0(t));
    return out;
}

/* 0x0019B280, 0x58 bytes. Officer `id`'s name and title (from its table record). */
void func_0019B280(char *out, u32 id)
{
    u16 *r = (u16 *)(g_005BA6A0 + func_002F27D0(id) * 0x2C);

    func_0019B170(out, r[0], r[1]);
}

/* 0x0019B2E0, 0x58 bytes. The same with the player's title as 0x17. */
void func_0019B2E0(char *out, u32 id)
{
    u16 *r = (u16 *)(g_005BA6A0 + func_002F27D0(id) * 0x2C);

    func_0019B200(out, r[0], r[1]);
}

/* 0x0019B340, 0xC8 bytes. The name of officer `id`'s troop kind (0 outside 0-0x19; the 6th
 * name for kind 0x13 lists). */
const char *func_0019B340(int id)
{
    u32 k, i;

    if (id < 0 || id > 0x19)
        k = 0;
    else
        k = func_0019A5A0(func_002F27D0(id));
    if (func_002F41E0(k) == 0x13)
        i = k * 6 + 5;
    else
        i = k * 6;
    return g_0042EE20[i & 0xFF];
}

/* 0x0019B410, 0xC8 bytes. Sum of the bonuses of kind `kind` in record func_0035DEC0(a,
 * func_002F5730()) (eight kinds at +2 and values at +10; kind 2 adds the table's value for
 * byte 0). */
short func_0019B410(u32 a, u32 kind)
{
    u8 rec[20];
    u8 *s = func_0035DEC0(a, func_002F5730(a));
    short sum = 0;
    int k;

    for (k = 0; k < 20; k++)
        rec[k] = s[k];
    for (k = 0; k < 8; k++) {
        if (kind == rec[2 + k])
            sum += rec[10 + k];
    }
    if (kind == 2)
        sum += g_00428138[rec[0]];
    return sum;
}

/* 0x0019B4E0, 0x8 bytes. */
int func_0019B4E0(void)
{
    return 0;
}

extern u8 g_00669D60[];                  /* the settings (per player 0x48 bytes from +0x88) */
extern u8 g_006A3A30[][0xC0];            /* the battle officers (game state +0x100C0) */
extern u8 g_004281C7, g_00428207, g_0042825F, g_00428267;   /* skill bonuses per level */

short func_001A2070(u32 id);
short func_001A2120(u32 id);
short func_001A21D0(u32 id);
short func_001A2270(u32 id);
short func_001A2310(u32 id);
short func_001A23B0(u32 id);
short func_001A2450(u32 id);
short func_001A24F0(u32 id);
int func_002F5E80(u32 id);
int func_002F4C40(u32 id);
int func_0036DC80(u32 id, u32 skill);
int func_0036DBA0(u32 id, u32 skill);
u8 func_0016CCE0(u32 id, u8 weapon);
void func_00347E70(int p);
u32 func_002F6A60(u32 id);
u8 func_0035DE00(u32 id);

/* Player `p`'s settings word at `off`. */
#define PSET(p, off) (*(u32 *)(g_00669D60 + (p) * 0x48 + (off)))

/* `v` kept within 1-`max`. */
#define CLAMP1(v, max) ((v) > (max) ? (max) : (v) < 2 ? 1 : (v))

/* `v` / 10 kept within 1-24. */
static inline float speed_of(short v)
{
    float f = (float)v * 0.1f;

    f = f < 24.0f ? f : 24.0f;
    return f > 1.0f ? f : 1.0f;
}

/* 0x0019B4F0, 0x89C bytes. Player `p`'s officer stats: life, musou, attack, defence, two
 * speeds, two more (into its officer table record 0x24E + p, +0xC-+0x1A, and with `battle`
 * into its battle officer), its weapon and a gauge value (its settings +0x3C). */
void func_0019B4F0(int p, int battle)
{
    u8 *b = g_006A3A30[p != 0];
    u32 id = PSET(p, 0x88);
    u8 *r = g_005BA6A0 + (p + 0x24E) * 0x2C;
    u8 rec[20];
    u8 *s;
    short v;
    int m, step, k;

    U32(r, 0x28) |= 0x80000000;
    v = func_001A2070(id);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0xC) = CLAMP1(v, 0x1CC);
    if (battle != 0)
        *(short *)(b + 0x80) = v;

    if (func_002F4C40(id) < func_002F5E80(id) / 3)
        m = func_002F4C40(id);
    else
        m = func_002F5E80(id) / 3;
    step = func_002F4C40(id) / m;
    if (func_0036DC80(id, 9) != 0)
        m += (short)(func_0036DBA0(id, 9) * g_00428207 / step);
    v = (short)m;
    if (func_0036DC80(id, 1) != 0)
        v += (short)(func_0036DBA0(id, 1) * g_004281C7 / step);
    *(short *)(g_00669D60 + p * 0x48 + 0xC4) = v + (short)(func_0019B410(id, 1) / step);

    v = func_001A2120(id);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0xE) = CLAMP1(v, 0x1CC);
    if (battle != 0)
        *(short *)(b + 0x86) = v;

    v = func_001A21D0(id);
    v = v - (short)((400 - v) / 8);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x10) = CLAMP1(v, 400);
    if (battle != 0)
        *(short *)(b + 0x8A) = CLAMP1(v, 1000);

    v = func_001A2270(id);
    v = v - (short)((350 - v) / 7);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x12) = v < 2 ? 1 : v > 350 ? 350 : v;
    if (battle != 0)
        *(short *)(b + 0x8C) = CLAMP1(v, 1000);

    v = func_001A2310(id);
    v = v - (short)((350 - v) / 7);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x14) = v < 2 ? 1 : v > 350 ? 350 : v;
    if (battle != 0)
        *(short *)(b + 0x8E) = CLAMP1(v, 350);

    v = func_001A23B0(id) / 3 + 0x50;
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x16) = CLAMP1(v, 350);
    if (battle != 0)
        *(float *)(b + 0x90) = speed_of(v);

    v = func_001A2450(id) / 3 + 0x50;
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x18) = CLAMP1(v, 350);
    if (battle != 0)
        *(float *)(b + 0x94) = speed_of(v);

    v = func_001A24F0(id);
    v = v - (short)((350 - v) / 7);
    if (U32(r, 0x28) & 0x80000000)
        *(short *)(r + 0x1A) = v < 2 ? 1 : v > 350 ? 350 : v;

    s = func_0035DEC0(id, func_002F5730(id));
    for (k = 0; k < 20; k++)
        rec[k] = s[k];
    k = func_0016CCE0(id, rec[0]);
    if (U32(r, 0x28) & 0x80000000)
        r[9] = (u8)k;
    U32(r, 0x28) &= 0x7FFFFFFF;
    func_00347E70(p);
}

/* A skill's level (0 without it). */
#define SKILL(id, k) (func_0036DC80(id, k) == 0 ? 0 : func_0036DBA0(id, k))

/* 0x0019BD90, 0x3D8 bytes. Player `p`'s battle officer's skill values (+0x98-+0xB4), a flag
 * (bit 0 of its settings +0x1C, skill 0x27), its element and two record bytes. */
void func_0019BD90(int p)
{
    u32 id = PSET(p, 0x88);
    u8 *b = g_006A3A30[p != 0];
    u8 rec[20];
    u8 *s;
    int k;

    *(float *)(b + 0x98) = 1.0f;
    *(float *)(b + 0x9C) = 1.0f;
    b[0xA9] = 0;
    if (func_0036DC80(id, 0x14) == 0)
        *(float *)(b + 0xA0) = (float)func_0019B410(id, 9);
    else
        *(float *)(b + 0xA0) = (float)(func_0036DBA0(id, 0x14) * g_0042825F
                                       + func_0019B410(id, 9));
    b[0xA7] = func_0036DC80(id, 0x15) == 0 ? 0 : (u8)(func_0036DBA0(id, 0x15) * g_00428267);
    b[0xA8] = SKILL(id, 0x16);
    b[0xAA] = SKILL(id, 0x17);
    b[0xAB] = SKILL(id, 0x18);
    b[0xAC] = SKILL(id, 0x19);
    b[0xAD] = SKILL(id, 0x1A);
    b[0xAE] = SKILL(id, 0x1B);
    b[0xAF] = SKILL(id, 0x1C);
    b[0xB0] = SKILL(id, 0x1D);
    b[0xA6] = SKILL(id, 8);
    b[0xB1] = SKILL(id, 0x21);
    if (func_0036DC80(id, 0x27) == 0)
        PSET(p, 0xA4) &= ~1u;
    else
        PSET(p, 0xA4) |= 1;
    if (func_0036DC80(id, func_002F6A60(id)) == 0)
        b[0xB2] = 0x35;
    else
        b[0xB2] = (u8)func_002F6A60(id);
    b[0xB3] = func_0035DE00(id);
    s = func_0035DEC0(id, func_002F5730(id));
    for (k = 0; k < 20; k++)
        rec[k] = s[k];
    b[0xB4] = rec[1];
}

extern u32 g_00669F60[4];                /* (settings) +0: the battle flags */
extern u32 g_00669F94;
extern u8 g_00574DE0[][0x630];           /* the units */
extern u32 g_00428348[0x14];             /* the experience needed per level */
extern u8 g_00428257, g_004282EF;        /* skill bonuses per level */

void func_002F67B0(void);
void func_002F40F0(u32 id, u32 level);
u32 func_00183840(void);
int func_002F7040(u32 id, int stat);
int func_002F59A0(u32 id);
int func_002F6E00(u32 id, int k);
u32 func_002F6EF0(u32 id, int k);
int func_002F47A0(u32 id, int skill);
void func_002F4820(u32 id, int skill, u32 level);
u32 func_002F6B40(u32 id);
u32 func_002F34E0(u32 id);
void func_002F3440(u32 id, u32 exp);
void func_001D1980(u8 *unit);
void func_0025CD50(int p);
void func_001F9AC0(int p, u32 level, int even, u32 learnt);
void func_001C8780(int a, u8 *unit, int b, int c);


int func_002F39F0(u32 id); int func_002F5D30(u32 id); void func_002F3960(u32 id, int v);
int func_002F4C40(u32 id); int func_002F5E80(u32 id); void func_002F4BB0(u32 id, int v);
int func_002F4DD0(u32 id); int func_002F5FD0(u32 id); void func_002F4D40(u32 id, int v);
int func_002F4F60(u32 id); int func_002F6120(u32 id); void func_002F4ED0(u32 id, int v);
int func_002F50F0(u32 id); int func_002F6270(u32 id); void func_002F5060(u32 id, int v);
int func_002F5280(u32 id); int func_002F63C0(u32 id); void func_002F51F0(u32 id, int v);
int func_002F5410(u32 id); int func_002F6510(u32 id); void func_002F5380(u32 id, int v);
int func_002F55A0(u32 id); int func_002F6660(u32 id); void func_002F5510(u32 id, int v);

/* Raises an officer's stat by `add`, up to its maximum (or, with func_002F59A0, up to `cap`). */
static inline void raise_stat(u32 id, u32 add, int (*get)(u32), int (*max)(u32),
                              void (*set)(u32, int), u32 cap)
{
    if (func_002F59A0(id) == 0)
        set(id, (u32)max(id) < add + get(id) ? max(id) : add + get(id));
    else
        set(id, add + get(id) <= cap ? add + get(id) : cap);
}

/* 0x0019C170, 0xA18 bytes. Officer `id` reaches level `level`: its eight stats grow (by the
 * level's table plus skills 0xA-0x11); with `learn`, odd levels may raise a skill and its own
 * level may teach its element. Whether a skill was learnt. */
int func_0019C170(u32 id, u32 level, int learn)
{
    int learnt = 0;
    u32 add;

    func_002F67B0();
    level &= 0xFF;
    func_002F40F0(id, level);
    if (g_00669DB8[0] != 3 && g_00669DB8[0] != 0)
        g_00669F94 = func_00183840();
    add = (func_0036DC80(id, 10) == 0 ? 0 : func_0036DBA0(id, 10)) + func_002F7040(id, 0);
    raise_stat(id, add, func_002F39F0, func_002F5D30, func_002F3960, 350);
    add = (func_0036DC80(id, 11) == 0 ? 0 : func_0036DBA0(id, 11)) + func_002F7040(id, 1);
    raise_stat(id, add, func_002F4C40, func_002F5E80, func_002F4BB0, 350);
    add = (func_0036DC80(id, 12) == 0 ? 0 : func_0036DBA0(id, 12)) + func_002F7040(id, 2);
    raise_stat(id, add, func_002F4DD0, func_002F5FD0, func_002F4D40, 250);
    add = (func_0036DC80(id, 13) == 0 ? 0 : func_0036DBA0(id, 13)) + func_002F7040(id, 3);
    raise_stat(id, add, func_002F4F60, func_002F6120, func_002F4ED0, 250);
    add = (func_0036DC80(id, 14) == 0 ? 0 : func_0036DBA0(id, 14)) + func_002F7040(id, 4);
    raise_stat(id, add, func_002F50F0, func_002F6270, func_002F5060, 250);
    add = (func_0036DC80(id, 15) == 0 ? 0 : func_0036DBA0(id, 15)) + func_002F7040(id, 5);
    raise_stat(id, add, func_002F5280, func_002F63C0, func_002F51F0, 250);
    add = (func_0036DC80(id, 16) == 0 ? 0 : func_0036DBA0(id, 16)) + func_002F7040(id, 6);
    raise_stat(id, add, func_002F5410, func_002F6510, func_002F5380, 250);
    add = (func_0036DC80(id, 17) == 0 ? 0 : func_0036DBA0(id, 17)) + func_002F7040(id, 7);
    raise_stat(id, add, func_002F55A0, func_002F6660, func_002F5510, 250);
    if (learn != 0) {
        if (((level + 1) & 1) == 0) {
            int k = ((int)(level + 1) >> 1) - 1;
            int skill = func_002F6E00(id, k);

            if (skill < 0x28) {
                u32 lv = func_002F6EF0(id, k) & 0xFF;

                if (func_002F47A0(id, skill) < (int)lv) {
                    func_002F4820(id, skill, lv);
                    learnt = 1;
                }
            }
        }
        if (level == func_002F6B40(id)) {
            func_002F4820(id, func_002F6A60(id), 1);
            learnt = 1;
        }
    }
    return learnt;
}

/* 0x0019CB90, 0x1D4 bytes. Fills player `p`'s four gauges (+0xAC-+0xB8 of its settings, flags
 * 2, 4, 8, 0x10) to at least 250 (more with skill 0x26). */
void func_0019CB90(int p)
{
    u32 id = PSET(p, 0x88), v;
    float f = 1.0f;

    if (func_0036DC80(id, 0x26) != 0)
        f = (float)func_0036DBA0(id, 0x26) / (float)g_004282EF + 1.0f;
    f = f * 250.0f;
    PSET(p, 0xA4) |= 2;
    v = (u32)f;
    if (PSET(p, 0xAC) < v)
        PSET(p, 0xAC) = v;
    PSET(p, 0xA4) |= 4;
    if (PSET(p, 0xB0) < v)
        PSET(p, 0xB0) = v;
    PSET(p, 0xA4) |= 0x10;
    if (PSET(p, 0xB8) < v)
        PSET(p, 0xB8) = v;
    PSET(p, 0xA4) |= 8;
    if (PSET(p, 0xB4) < v)
        PSET(p, 0xB4) = v;
    func_001D1980(g_00574DE0[p]);
}

/* 0x0019CD70, 0x464 bytes. Player `p` gains `exp` experience (more with skill 0x13; not in
 * modes 8 / 0x10): into +0x98 (up to 99999), +0xC6 (up to 5000) and the officer's own; on
 * reaching the next level it levels up (unless `quiet`: stats, skills, full gauges, the
 * level-up display). Past level 19 half a level's worth fills the gauges. Whether it levelled
 * up. */
int func_0019CD70(int p, u32 exp, int quiet)
{
    u32 id = PSET(p, 0x88), need, v;
    u8 level;

    func_002F34E0(id);
    level = func_002F41E0(id);
    need = level < 0x13 ? g_00428348[(u8)(level + 1)] : 100000;
    level = func_002F41E0(id);
    if (g_00669F60[0] & 0x18)
        return 0;
    if (func_0036DC80(PSET(p, 0x88), 0x13) != 0)
        exp = exp + (int)((float)(int)exp * (float)(func_0036DBA0(PSET(p, 0x88), 0x13)
                                                   * g_00428257) * 0.1f);
    v = (int)exp + PSET(p, 0x98);
    PSET(p, 0x98) = v > 99999 ? 99999 : v;
    v = (int)exp + U16(g_00669D60, p * 0x48 + 0xC6);
    U16(g_00669D60, p * 0x48 + 0xC6) = (u16)(v > 5000 ? 5000 : v);
    func_002F3440(id, exp + func_002F34E0(id) < 100000 ? exp + func_002F34E0(id) : 99999);
    if (level < 0x13) {
        u32 learnt;

        if (func_002F34E0(id) < need)
            return 0;
        level = level + 1;
        learnt = func_0019C170(PSET(p, 0x88), level, 1);
        if (quiet == 0) {
            u8 *b = g_006A3A30[p != 0];
            short g0 = *(short *)(g_00669D60 + p * 0x48 + 0xC4);
            short m0 = *(short *)(b + 0x86);

            func_0019B4F0(p, 1);
            if (m0 / g0 < *(short *)(b + 0x86) / *(short *)(g_00669D60 + p * 0x48 + 0xC4))
                func_0025CD50(p);
            func_0019BD90(p);
            func_0019CB90(p);
            PSET(p, 0x98) = need < PSET(p, 0x98) ? PSET(p, 0x98) - need : 0;
            func_001F9AC0(p, level, (level & 1) == 0 && level < 0xD, learnt);
            *(u32 *)0x70000D60 = 0;
            func_001C8780(0x25, g_00574DE0[p], 0, 0x204);
        }
        return 1;
    }
    v = (g_00428348[19] - g_00428348[18]) >> 1;
    if (PSET(p, 0x98) < v)
        return 0;
    PSET(p, 0x98) = v < PSET(p, 0x98) ? PSET(p, 0x98) - v : 0;
    if (quiet == 0)
        func_0019CB90(p);
    return 0;
}

/* 0x0019D1E0, 0x17C bytes. When player `p`'s battle officer `b` (life at 80% or more; not in
 * modes 4 / 8 / 0x10) has a table record with a skill (one of three at +0x22 / +0x25) the
 * player lacks, it becomes the officer being studied (+0xBC; counters +0xC0 / +0xC2 reset). */
void func_0019D1E0(int p, int b)
{
    u8 *o = g_006A3A30[b], *r;
    int i, k;

    if (g_00669F60[0] & 0x1C)
        return;
    if ((*(short *)(o + 0x80) * 0x50) / 100 > *(short *)(o + 0x84))
        return;
    r = *(u8 **)(o + 0x68);
    i = (r - g_005BA6A0) / 0x2C;
    if (i == (int)PSET(p, 0xBC))
        return;
    for (k = 0; k < 3; k++) {
        u32 lv = r[k + 0x25];

        if (lv != 0 && r[k + 0x22] < 0x28 && func_002F47A0(PSET(p, 0x88), r[k + 0x22]) < (int)lv)
            break;
    }
    if (k < 3) {
        PSET(p, 0xBC) = i;
        U16(g_00669D60, p * 0x48 + 0xC0) = 0;
        U16(g_00669D60, p * 0x48 + 0xC2) = 0;
    }
}

/* 0x0019D360, 0xA8 bytes. Adds `n` to player `p`'s study points while officer `b` is the one
 * studied. */
void func_0019D360(int p, int b, short n)
{
    if (g_00669F60[0] & 0x1C)
        return;
    if ((int)PSET(p, 0xBC) != -1
        && (int)PSET(p, 0xBC) == (*(u8 **)(g_006A3A30[b] + 0x68) - g_005BA6A0) / 0x2C)
        U16(g_00669D60, p * 0x48 + 0xC2) += n;
}

/* 0x0019D410, 0x6C bytes. Counts player `p`'s study time; after 9000 frames it stops. */
void func_0019D410(int p)
{
    if (g_00669F60[0] & 0x1C)
        return;
    if ((int)PSET(p, 0xBC) != -1) {
        U16(g_00669D60, p * 0x48 + 0xC0) += 1;
        if (U16(g_00669D60, p * 0x48 + 0xC0) >= 9000) {
            PSET(p, 0xBC) = -1;
            U16(g_00669D60, p * 0x48 + 0xC0) = 0;
            U16(g_00669D60, p * 0x48 + 0xC2) = 0;
        }
    }
}
