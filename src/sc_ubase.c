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

/* A skill being offered: its id, its level, who gets it (2: none). */
typedef struct {
    int skill;
    u8 level;
    u8 who;
    u8 pad[2];
} SkillOffer;

extern u8 g_00669E78[8][0x15];           /* (settings +0x118) the weapons found (+0x14 who, 2 none) */
extern SkillOffer g_00669F20[8];         /* (settings +0x1C0) the skills learnt in battle */
extern u8 g_004281BC[0x28][8];           /* the skills (+0 group, +1 kind: 3 special) */
extern const int g_004069A0[4];          /* chance by skill level (from 1) */
extern const float g_004069B0[4];        /* by levels missing (from 1) */
extern const float g_004069C0[3];        /* by study time and by study points */
extern const float g_004069D0[4];        /* by the level of skill 0x23 */
extern const float g_004069E0[4];        /* by stat 7 in 50s */
extern u8 g_00669D81[0x10];              /* (settings) +0: a scenario value */

void func_00247FA0(u8 a, int b, int c);

/* 0x0019D480, 0x890 bytes. After beating battle officer `b` while it is studied, player `p`
 * may learn one of its skills (+0x22 ids, +0x25 levels, picked at random): special skills need
 * the right conditions, others at most two levels above the player's; the chance grows with the
 * study time and points, skill 0x23 and stat 7 (at most 100%). Whether one was learnt (it goes
 * into a free slot of the battle's learnt skills). */
int func_0019D480(int b, int p)
{
    u8 *tab = g_005BA6A0, *r;
    SkillOffer offers[3], *o;
    int found = 0, i, k, n, pick;
    u32 id;

    if (g_00669F60[0] & 0x1C)
        return 0;
    for (i = 0; i < 2; i++) {
        if ((int)PSET(i, 0xBC) == -1) {
            PSET(i, 0xBC) = -1;
            U16(g_00669D60, i * 0x48 + 0xC0) = 0;
            U16(g_00669D60, i * 0x48 + 0xC2) = 0;
        } else if ((int)PSET(i, 0xBC) == (*(u8 **)(g_006A3A30[b] + 0x68) - tab) / 0x2C) {
            found = 1;
        }
    }
    if (!found)
        return 0;
    if (p != 0 && p != 1) {
        for (i = 0; i < 2; i++) {
            PSET(i, 0xBC) = -1;
            U16(g_00669D60, i * 0x48 + 0xC0) = 0;
            U16(g_00669D60, i * 0x48 + 0xC2) = 0;
        }
        return 0;
    }
    id = PSET(p, 0x88);
    for (i = 0; i < 8; i++) {
        if (g_00669F20[i].who == 2)
            break;
    }
    if (i >= 8)
        return 0;

    r = *(u8 **)(g_006A3A30[b] + 0x68);
    n = 0;
    o = offers;
    for (k = 0; k < 3; k++) {
        u8 s = r[k + 0x22], lv = r[k + 0x25];

        offers[k].skill = 0x28;
        offers[k].level = 0;
        offers[k].who = 2;
        if (s < 0x28 && func_002F47A0(id, s) < lv) {
            o->skill = s;
            o->level = lv;
            o->who = (u8)p;
            o++;
            n++;
        }
    }
    if (n == 0)
        return 0;
    pick = (int)RANDOM() % n;
    o = &offers[pick];
    if (o->skill >= 0x28)
        return 0;

    if (g_004281BC[o->skill][1] == 3 && o->level == 3 && g_00669D81[0] < 3)
        return 0;
    if (o->skill == 0x21) {
        int c = 0;

        for (k = 0; k < 0x28; k++) {
            if (g_004281BC[k][1] == 3 && o->level <= func_002F47A0(id, k))
                c++;
        }
        if (c < 2)
            return 0;
    } else if (g_004281BC[o->skill][1] == 3) {
        for (k = 0; k < 0x28; k++) {
            if (g_004281BC[o->skill][0] == g_004281BC[k][0] && g_004281BC[k][1] != 3
                && func_002F47A0(id, k) < o->level)
                return 0;
        }
    } else if ((int)(o->level - func_002F47A0(id, o->skill)) > 2) {
        return 0;
    }

    {
        int named = PSET(p, 0xBC) < 0x1D;
        float base = (float)g_004069A0[o->level - 1], f;
        int d = ((o->level - func_002F47A0(id, o->skill)) & 0xFF) - 1;
        u32 t, pt, sk, st, chance;

        f = base * g_004069B0[d < 3 ? d : 3];
        t = named ? U16(g_00669D60, p * 0x48 + 0xC0) / 1000 : U16(g_00669D60, p * 0x48 + 0xC0) / 750;
        if (named || (U32(*(u8 **)(g_006A3A30[b] + 0x10), 0x80) & 0x200))
            pt = U16(g_00669D60, p * 0x48 + 0xC2) / 50;
        else
            pt = U16(g_00669D60, p * 0x48 + 0xC2) / 25;
        pt &= 0xFF;
        base = f * g_004069C0[pt < 2 ? pt : 2] + f * g_004069C0[t < 2 ? t : 2] + f + 0.0f + 0.0f;
        if (func_0036DC80(id, 0x23) != 0) {
            sk = func_0036DBA0(id, 0x23) & 0xFF;
            base = f * g_004069D0[sk < 3 ? sk : 3] + base + 0.0f;
        }
        st = (u32)func_002F55A0(id) / 50 & 0xFF;
        f = f * g_004069E0[st < 3 ? st : 3] + base + 0.0f;
        f = f > 100.0f ? 100.0f : f;
        chance = (u32)f;
        if (RANDOM() % 100 >= chance)
            return 0;
    }
    for (i = 0; i < 8; i++) {
        if (g_00669F20[i].who == 2)
            break;
    }
    g_00669F20[i] = *o;
    func_00247FA0(g_00574DE0[p][0x14E], 0x1C, 6);
    return 1;
}

/* 0x0019DD20, 0x48 bytes. Clears the weapons found. */
void func_0019DD20(void)
{
    int k;

    for (k = 0; k < 8; k++)
        g_00669E78[k][0x14] = 2;
}

/* 0x0019DD70, 0x48 bytes. Clears the battle's learnt skills. */
void func_0019DD70(void)
{
    int k;

    for (k = 0; k < 8; k++)
        g_00669F20[k].who = 2;
}

/* 0x0019DDC0, 0x414 bytes. Sorts a record's eight (rank +2, value +10) pairs: lowest rank first,
 * then the largest value. */
void func_0019DDC0(u8 *r)
{
    int key[8], i, j;

    for (i = 0; i < 8; i++)
        key[i] = r[10 + i] + (10 - r[2 + i]) * 100;
    for (i = 1; i < 8; i++) {
        int v = key[i];

        for (j = i - 1; j >= 0 && key[j] < v; j--)
            key[j + 1] = key[j];
        key[j + 1] = v;
    }
    for (i = 0; i < 8; i++) {
        r[2 + i] = 10 - key[i] / 100;
        r[10 + i] = key[i] % 100;
    }
}

extern u32 g_00669F84, g_00669F88;       /* (settings) the difficulty and a weapon level */
extern u8 g_004069F0[8][2];              /* rank chances by difficulty */
extern u8 g_0045CCA0[5], g_0045CCA8[8], g_0045CCB0[4];   /* kind, rank and attribute chances */
extern u8 g_004282DF, g_004282B7;
extern u32 g_00669DC0[4];                /* (settings) +0: the scenario's stage */
extern u8 g_00428B78[][0x13];            /* the stages' fixed weapons */
extern u8 g_00669D84[4];                 /* (settings) flags: +0 bits 1, 2, 5, 6, 7; +1 bits 0, 1 */
extern u32 g_0045D2A8;
extern signed char g_0069395E;
extern u8 g_00732584[2][0x1C];           /* per player boost icons (+0-+3) */
extern u32 g_00669D6C;                   /* (settings) the time played */
extern u32 g_00669F64[2];                /* (settings) battle flags to set (+0) and clear (+4) */

u32 func_002F57F0(u8 kind);
u8 func_002F5840(u32 w);
void func_002695F0(int p);
void func_00361640(void);
void func_00361FB0(u32 now, u32 before);
void func_003F7C60(u32 now, u32 before);
void func_003276D0(void);

/* Index of the first threshold of `t` (n of them) above `roll` (n when none is). */
static inline int pick_by(const u8 *t, int n, u32 roll)
{
    int k;

    for (k = 0; k < n; k++) {
        if (roll % 100 < t[k])
            break;
    }
    return k;
}

/* 0x0019E1E0, 0x640 bytes. Player `p` finds a weapon: its rank (by the difficulty, raised by
 * skill 0x24 and the beaten officer's luck), kind, number of attributes and their ids and
 * values; it goes into the first free slot of the weapons found. */
void func_0019E1E0(int p)
{
    u8 rank[8][2], kind[5], att[8], na[4], w[0x15];
    u8 *b = g_006A3A30[p != 0];
    int slot, k, same;
    u32 n;

    for (k = 0; k < 8; k++) {
        rank[k][0] = g_004069F0[k][0];
        rank[k][1] = g_004069F0[k][1];
    }
    for (k = 0; k < 5; k++)
        kind[k] = g_0045CCA0[k];
    for (k = 0; k < 8; k++)
        att[k] = g_0045CCA8[k];
    for (k = 0; k < 4; k++)
        na[k] = g_0045CCB0[k];
    for (slot = 0; slot < 8; slot++) {
        if (g_00669E78[slot][0x14] == 2)
            break;
    }
    if (slot >= 8)
        return;

    w[0x14] = (u8)p;
    k = pick_by(rank[g_00669F84], 2, RANDOM());
    if ((k < 2 && g_00669F84 > 1) || (k < 1 && g_00669F84 < 2)) {
        int s = func_0036DBA0(PSET(p, 0x88), 0x24);

        if ((int)(RANDOM() % 100) < *(short *)(*(u8 **)(b + 0x68) + 0x1A) / 10 + s * g_004282DF)
            k++;
    }
    w[0] = (u8)(k + PSET(p, 0x88) * 4);
    w[1] = (u8)pick_by(kind, 5, RANDOM());
    w[0x12] = (u8)pick_by(att, 8, RANDOM());
    if (w[0x12] < 8) {
        int s = func_0036DBA0(PSET(p, 0x88), 0x24);

        if ((int)(RANDOM() % 100) < *(short *)(*(u8 **)(b + 0x68) + 0x1A) / 10 + s * g_004282DF)
            w[0x12]++;
    }
    w[0x12] = func_002F5840(func_002F57F0(w[0]));
    n = pick_by(na, 4, RANDOM());
    if ((int)w[0x12] < (int)n)
        n = w[0x12];
    same = 1;
    for (k = 0; k < 8; k++) {
        if (k < (int)n) {
            u32 v;

            w[2 + k] = RANDOM() % 10;
            if (w[2 + k] != w[2 + (k - 1 < 0 ? 0 : k - 1)])
                same = 0;
            if (k > 2 && same)
                w[2 + k] = (u8)(w[2 + k] + RANDOM() % 9 + 1) % 10;
            v = ((g_00669F88 + 0x12 == 0 ? 0 : (int)RANDOM() % (g_00669F88 + 0x12)) + g_00669F88
                 + 4) >> 1;
            w[10 + k] = v < 0x14 ? v : 0x14;
        } else {
            w[2 + k] = 10;
            w[10 + k] = 0;
        }
    }
    func_0019DDC0(w);
    for (k = 0; k < 0x15; k++)
        g_00669E78[slot][k] = w[k];
}

/* 0x0019E820, 0x37C bytes. In the story mode (scenario value 3 or more), gives the fixed weapon
 * of the current stage (24 stages) into the first free slot. */
void func_0019E820(void)
{
    static const u8 stages[] = {0xC, 0x3D, 0x36, 2, 0x20, 0x27, 0, 0x18, 0x3A, 0x4E, 0x48, 4,
                                0, 0x26, 0x47, 0x14, 0x2A, 7, 0xF, 0x2C, 0x32, 0x1F, 0x1E, 0x23,
                                0x13, 0x4B};
    u8 w[0x15];
    int i, k, slot;

    if (g_00669DB8[0] != 0 || g_00669D81[0] < 3)
        return;
    for (i = 0x19; i >= 0; i--) {
        if (i != 6 && i != 0xC && g_00669DC0[0] == stages[i])
            break;
    }
    if (i < 0)
        return;
    *(u16 *)(w + 0x14) = 0;
    w[0x12] = 8;
    w[0] = g_00428B78[i][0];
    w[1] = g_00428B78[i][1];
    for (k = 0; k < 8; k++) {
        u8 a = g_00428B78[i][k + 3];

        if (a < 10) {
            w[2 + k] = a;
            w[10 + k] = g_00428B78[i][k + 0xB];
        } else {
            w[2 + k] = 10;
            w[10 + k] = 0;
        }
    }
    for (slot = 0; slot < 8; slot++) {
        if (g_00669E78[slot][0x14] == 2)
            break;
    }
    if (slot < 8) {
        func_0019DDC0(w);
        for (k = 0; k < 0x15; k++)
            g_00669E78[slot][k] = w[k];
    }
}

/* 0x0019EBA0, 0x1F8 bytes. Player `p` beats `n` more (+0x8C of its settings, up to 9999): every
 * 100 skill 0x1F gives back life; then the counters and the 300-mark notice. */
void func_0019EBA0(int p, u32 n)
{
    u32 v = n + PSET(p, 0x8C), before;

    if (v > 9999)
        v = 9999;
    PSET(p, 0x8C) = v;
    if ((int)v % 100 == 0) {
        u32 id = PSET(p, 0x88);
        u8 k = g_004282B7;

        if (func_0036DC80(id, 0x1F) != 0) {
            u8 *b = g_006A3A30[p != 0];
            short m = *(short *)(b + 0x80), l = m;

            if (*(short *)(b + 0x82) + func_0036DBA0(id, 0x1F) * k < m)
                l = *(short *)(b + 0x82) + (short)func_0036DBA0(id, 0x1F) * k;
            l = (l > m ? m : l) < 1 ? 0 : l > m ? m : l;
            *(short *)(b + 0x82) = l;
            if (*(short *)(b + 0x84) < l)
                *(short *)(b + 0x84) = l;
        }
    }
    func_002695F0(p);
    before = v - n;
    if (before < 300 && v >= 300)
        func_00361640();
    func_00361FB0(v, before);
    func_003F7C60(v, before);
}

/* 0x0019EDA0, 0x1C bytes. */
int func_0019EDA0(void)
{
    return (g_00669D84[0] & 2) == 0;
}

/* 0x0019EDC0, 0x1C bytes. */
int func_0019EDC0(void)
{
    return (g_00669D84[0] & 4) == 0;
}

/* 0x0019EDE0, 0x1C bytes. */
int func_0019EDE0(void)
{
    return (g_00669D84[0] & 0x20) == 0;
}

/* 0x0019EE00, 0x1C bytes. */
int func_0019EE00(void)
{
    return (g_00669D84[0] & 0x40) == 0;
}

/* 0x0019EE20, 0x50 bytes. Whether (flag 0x80 not yet set) player 1 has skill 9 at level 3+. */
int func_0019EE20(void)
{
    if (g_00669D84[0] & 0x80)
        return 0;
    return (u8)func_002F47A0(PSET(0, 0x88), 9) > 2;
}

/* 0x0019EE70, 0x4C bytes. The same for flag 0x100 and skill 0x13. */
int func_0019EE70(void)
{
    if (g_00669D84[1] & 1)
        return 0;
    return (u8)func_002F47A0(PSET(0, 0x88), 0x13) > 2;
}

/* 0x0019EEC0, 0x50 bytes. The same for flag 0x200 and skill 0x25. */
int func_0019EEC0(void)
{
    if (g_00669D84[1] & 2)
        return 0;
    return (u8)func_002F47A0(PSET(0, 0x88), 0x25) > 2;
}

/* 0x0019EF10, 0xBC bytes. Player `p`'s experience towards the next level (+0x98; 0 for created
 * officers and at the last level). */
void func_0019EF10(int p)
{
    int id = PSET(p, 0x88);

    if (id < 0x1A && func_002F41E0(id) < 0x13) {
        u8 lv = func_002F41E0(id);
        u32 e = func_002F34E0(id) - g_00428348[lv];

        if (e < 100000)
            PSET(p, 0x98) = e;
    } else {
        PSET(p, 0x98) = 0;
    }
}

/* 0x0019EFD0, 0x374 bytes. Each frame: (in battle, not paused) the players' study timers and
 * their timed boosts (+0xA4 bits 0-4 with times at +0xA8: 1 attack x2, 2 defence x2, 3 musou
 * kept, 4 a flag); the time played; the pending battle flags. */
void func_0019EFD0(void)
{
    int p, k;

    if (g_0045D2A8 == 0 && (g_00669F60[0] & 0x2BE0000) == 0
        && (g_0069395E == 0 || g_0069395E == -1)) {
        for (p = 0; p < 2; p++) {
            u8 *b = g_006A3A30[p != 0];

            func_0019D410(p);
            *(float *)(b + 0x98) = 1.0f;
            *(float *)(b + 0x9C) = 1.0f;
            b[0xA9] = 0;
            U32(b, 0xBC) &= 0xC7FFFFFF;
            for (k = 0; k < 5; k++) {
                u32 bit = 1 << k;

                if ((bit & PSET(p, 0xA4)) == 0)
                    continue;
                if (PSET(p, 0xA8 + k * 4) != 0xFFFFFFFF)
                    PSET(p, 0xA8 + k * 4) = PSET(p, 0xA8 + k * 4) < 2 ? 0 : PSET(p, 0xA8 + k * 4) - 1;
                if (PSET(p, 0xA8 + k * 4) == 0) {
                    PSET(p, 0xA4) &= ~bit;
                } else {
                    u8 s = PSET(p, 0xA8 + k * 4) < 0xFA ? 2 : 1;

                    if (k == 1) {
                        g_00732584[p][0] = s;
                        *(float *)(b + 0x98) = 2.0f;
                        U32(b, 0xBC) |= 0x8000000;
                    } else if (k == 2) {
                        g_00732584[p][1] = s;
                        *(float *)(b + 0x9C) = 2.0f;
                        U32(b, 0xBC) |= 0x10000000;
                    } else if (k == 3) {
                        g_00732584[p][3] = s;
                        *(short *)(b + 0x88) = *(short *)(b + 0x86);
                    } else if (k == 4) {
                        g_00732584[p][2] = s;
                        b[0xA9] = 1;
                        U32(b, 0xBC) |= 0x20000000;
                    }
                }
            }
            if ((g_00669F60[0] & 8) && U8(g_00669D60, p * 0x48 + 0xCB) == 9) {
                *(short *)(b + 0x88) = 0;   /* (the original clamps the musou to 0-0) */
            }
        }
    }
    g_00669D6C = g_00669D6C + 1 > 0xCDFE5C4 ? 0xCDFE5C4 : g_00669D6C + 1;
    if (g_00669DB8[0] == 0)
        func_003276D0();
    {
        u32 c = g_00669F64[1];

        g_00669F64[1] = 0;
        g_00669F60[0] = (g_00669F60[0] & ~c) | g_00669F64[0];
        g_00669F64[0] = 0;
    }
}
