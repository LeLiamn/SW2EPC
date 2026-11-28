/*
 * emp_fld_main.c - battlefield helpers that follow the event commands: sides, the battle frame,
 * player lookups, weighted random picks and the items that bases hand out. Original file name
 * unknown (0x0035D560-0x0035E9BC).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_FLD_MAIN_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A base's item drop (20 of them, 0x20 bytes each at 0x007B6D30). */
typedef struct {
    u32 pos[4];              /* +0x00 where it appears */
    int (*drop)(u32 k);      /* +0x10 */
    int on;                  /* +0x14 */
    int timer;               /* +0x18 counts of 50 frames */
    int period;              /* +0x1C 0 = never */
} BaseDrop;

/* A weighted pick (`weight` percent). */
typedef struct {
    u32 id;
    int weight;
} Pick;

/* A ranged pick (`lo`-`hi`). */
typedef struct {
    u32 id;
    int lo, hi;
} RangePick;

extern BaseDrop g_007B6D30[0x14];
extern u8 g_00693970[];
extern u8 g_006A1D58[][0x68];
#ifdef SW2E_PC
extern ps2ptr g_005BA6A0_a;                   /* the officer table (0x2C bytes each) */
#define g_005BA6A0 ((u8 *)PS2_PTR(g_005BA6A0_a))
#define g_005BA6A0_SET(v) (g_005BA6A0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6A0;
#define g_005BA6A0_a (*(ps2ptr *)&g_005BA6A0)
#define g_005BA6A0_SET(v) (g_005BA6A0 = (v))
#endif
extern u8 g_00669D60[];                  /* the settings */
extern int g_00669F9C;                   /* the battle's frame counter */
extern u32 g_0076E700[];                 /* per model kind flags */
extern int (*g_0045D080)(u32 k);         /* (small data) the default drop */
extern u32 g_00415850[48], g_00415910[48], g_004159D0[70], g_00415AF0[70], g_00415C10[28];
extern Pick g_00415C80[2], g_00415C90[3], g_00415CB0[3];
extern u32 g_00415CD0[5];
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define UNIT(i) (g_00693970 + (i) * 0x88)
#define GROUP(i) ((u8 **)g_006A1D58[i])
#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)
#define UNIT_FLAGS(u) (*(u32 *)((u) + 0x80))
#define SETTINGS_FLAGS (*(u32 *)(g_00669D60 + 0x200))
#define PLAYER_ON(p) (*(int *)(g_00669D60 + (p) * 0x48 + 0xA0))

void func_0035E0E0(void);
void func_0035D8E0(void);
u8 *func_0034A9D0(u32 k);
void func_0017E060(void);
int func_0034A8D0(int i);

int func_0035D5A0(int side);
int func_0035D5E0(int k);
void func_0035E210(u32 k);
u16 func_0035DC70(int p);

/* 0x0035D560, 0xC bytes, matching. */
int func_0035D560(int a, int b)
{
    return a == b;
}

/* 0x0035D570, 0x24 bytes. */
int func_0035D570(int a, int b)
{
    return func_0035D560(a, b) == 0;
}

/* 0x0035D5A0, 0xC bytes, matching. The other side. */
int func_0035D5A0(int side)
{
    return side == 0;
}

/* 0x0035D5B0, 0x30 bytes. */
int func_0035D5B0(int k)
{
    return func_0035D5E0(k) == 0;
}

/* 0x0035D5E0, 0x7C bytes. Whether `k` is one of 0-3, 6, 8, 10, 12, 14. */
int func_0035D5E0(int k)
{
    if (k == 0xE || k == 0xC || k == 10 || k == 8 || k == 6 || k == 3 || k == 2 || k == 1 || k == 0)
        return 1;
    return 0;
}

/* 0x0035D660, 0x74 bytes, matching. The battlefield's frame (when not paused). */
void func_0035D660(void)
{
    if (func_0032E7B0() != 0)
        return;
    func_00351960();
    func_00360170();
    func_0035E0E0();
    func_003701B0();
    func_0036E3C0();
    func_003F8480();
    func_003F6A90();
    func_003E1DD0();
    func_0035D8E0();
    func_0035F030();
}

/* 0x0035D6E0, 0x48 bytes. */
u32 func_0035D6E0(int k)
{
    u32 t[48];
    int i;

    for (i = 0; i < 48; i++)
        t[i] = g_00415850[i];
    return t[k];
}

/* 0x0035D730, 0x48 bytes. */
u32 func_0035D730(int k)
{
    u32 t[48];
    int i;

    for (i = 0; i < 48; i++)
        t[i] = g_00415910[i];
    return t[k];
}

/* 0x0035D780, 0x64 bytes. */
u32 func_0035D780(int k)
{
    u32 t[72];
    int i;

    for (i = 0; i < 70; i++)
        t[i] = g_004159D0[i];
    if (k < 0 || k > 0x45)
        return 0x1E;
    return t[k];
}

/* 0x0035D7F0, 0x64 bytes. */
u32 func_0035D7F0(int k)
{
    u32 t[72];
    int i;

    for (i = 0; i < 70; i++)
        t[i] = g_00415AF0[i];
    if (k < 0 || k > 0x45)
        return 0x39;
    return t[k];
}

/* 0x0035D860, 0x74 bytes, matching. Whether group `g` shows its marker. */
int func_0035D860(u8 **g)
{
    u32 f;

    if (func_001F2AD0() != 0)
        return 0;
    f = UNIT_FLAGS(*g);
    if ((f & 0x30) != 0)
        return 0;
    if (*g != 0 && (f & 4) != 0)
        return 0;
    return func_0033B240(g);
}

/* The model of unit `u`'s officer. */
#define UNIT_MODEL(u) PS2_LOADP(u8 *, (g_00693970 + 0x100C0 + 0x14 + *(int *)((u) + 0x14) * 0xC0))
#define UNIT_MODEL_SET(u, v) PS2_STOREP(u8 *, (g_00693970 + 0x100C0 + 0x14 + *(int *)((u) + 0x14) * 0xC0), v)

/* 0x0035D8E0, 0xF8 bytes. Shows or hides the markers of the 16 officers' groups. */
void func_0035D8E0(void)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 *u = func_0034A9D0(k), *m;

        if ((UNIT_FLAGS(u) & 1) == 0 || (UNIT_FLAGS(u) & 0x20000) == 0)
            continue;
        m = UNIT_MODEL(u);
        if (*(int *)(m + 0x11C) == 0)
            continue;
        if (func_0035D860(func_0033EF80(k)) == 0)
            func_00253690(0x18, m);
        else if ((g_0076E700[m[0x14E]] & 0x1000000) == 0)
            func_00253300(0x18, m);
    }
}

/* 0x0035D9E0, 0xC0 bytes, matching. Hides them all. */
void func_0035D9E0(void)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 *u = func_0034A9D0(k), *m;

        if ((UNIT_FLAGS(u) & 1) == 0 || (UNIT_FLAGS(u) & 0x20000) == 0)
            continue;
        m = UNIT_MODEL(u);
        if (*(int *)(m + 0x11C) != 0 && (g_0076E700[m[0x14E]] & 0x1000000) != 0)
            func_00253690(0x18, m);
    }
}

/* 0x0035DAA0, 0x34 bytes. */
void func_0035DAA0(void)
{
    if (func_00362BB0() < 0x69)
        func_0017E060();
}

/* 0x0035DAE0, 0x10 bytes, matching. */
u32 func_0035DAE0(void)
{
    return SETTINGS_FLAGS & 2;
}

/* 0x0035DAF0, 0x24 bytes, matching. */
u8 *func_0035DAF0(int a, int b)
{
    return func_00328B30(func_00328C80(a, b));
}

/* 0x0035DB20, 0x30 bytes. */
u8 func_0035DB20(int a, int b)
{
    u8 *p = func_0035DAF0(a, b);

    return p == 0 ? 0x7F : *p;
}

/* 0x0035DB50, 0x78 bytes. Picks one of the `n` entries of `t` by weight. */
u32 func_0035DB50(Pick *t, int n)
{
    int s = 0, k = 0;
    u32 r = RANDOM();

    for (; k < n; k++) {
        s += t[k].weight;
        if ((int)(r % 100) < s)
            break;
    }
    return t[k].id;
}

/* 0x0035DBD0, 0x98 bytes. Picks the entry of `t` whose range holds a random number below
 * `total`. */
u32 func_0035DBD0(RangePick *t, int n, int total)
{
    int r = total == 0 ? 0 : (int)RANDOM() % total, k;

    for (k = 0; k < n; k++) {
        if (t[k].lo <= r && r <= t[k].hi)
            break;
    }
    return t[k].id;
}

/* 0x0035DC70, 0x3C bytes, matching. Player `p`'s unit (0x1AD for none). */
u16 func_0035DC70(int p)
{
    u32 k = func_00362320(p);

    if (k < 8)
        return func_0034A8D0(k);
    return 0x1AD;
}

/* 0x0035DCB0, 0x1C bytes, matching. */
u16 func_0035DCB0(int p)
{
    return func_0035DC70(p);
}

/* 0x0035DCD0, 0x38 bytes, matching. */
u8 *func_0035DCD0(int p)
{
    return UNIT(func_0035DC70(p) & 0xFFFF);
}

/* 0x0035DD10, 0x48 bytes. Player `p`'s group. */
u8 **func_0035DD10(int p)
{
    return GROUP(func_0035DCB0(p) & 0xFFFF);
}

/* 0x0035DD60, 0xA0 bytes. Officer `x`'s portrait (by side). */
int func_0035DD60(int x, int side)
{
    int v = func_00363720(x);

    if (v < 0x1C)
        return side + v * 2;
    if (v < 400)
        return side + g_005BA6A0[func_002F27D0(v) * 0x2C + 6] * 2;
    if (side == 0)
        return func_0039E7E0(v - 400);
    return func_0039E800(v - 400);
}

/* 0x0035DE00, 0xC0 bytes. Officer `v`'s weapon kind. */
u32 func_0035DE00(int v)
{
    u32 t[28];
    int i;
    u8 k;

    for (i = 0; i < 28; i++)
        t[i] = g_00415C10[i];
    if (v < 0x1C)
        return t[v];
    k = g_005BA6A0[func_002F27D0(v) * 0x2C + 7];
    if (k < 0x1A)
        return t[k];
    if (k == 0x3E)
        return 2;
    return 0;
}

/* 0x0035DEC0, 0x1C bytes, matching. */
u8 *func_0035DEC0(int a, int b)
{
    return func_0035DAF0(a, b);
}

/* 0x0035DEE0, 0x130 bytes. Sets up base `k`'s drop (every `period` counts). */
void func_0035DEE0(u32 k, int kind, int period)
{
    u8 *b, c[4];
    float xy[2];
    u32 v[4];

    if (k >= 0x14 || kind != 0 || (b = (u8 *)PS2_PTR(func_0034EC80(k))) == 0 || func_0034EE50(b) == 0)
        return;
    g_007B6D30[k].on = 1;
    g_007B6D30[k].drop = g_0045D080;
    g_007B6D30[k].timer = period;
    g_007B6D30[k].period = period;
    func_0034ED90(b, c);
    xy[0] = (float)c[0] * 5000.0f + 2500.0f;
    xy[1] = (float)c[1] * 5000.0f + 2500.0f;
    func_001911A0((float *)(v), xy);
    g_007B6D30[k].pos[0] = v[0];
    g_007B6D30[k].pos[1] = v[1];
    g_007B6D30[k].pos[2] = v[2];
    g_007B6D30[k].pos[3] = v[3];
}

/* 0x0035E010, 0xB4 bytes. Sets up all bases' drops. */
void func_0035E010(void)
{
    u32 k;

    for (k = 0; k < 0x14; k++)
        g_007B6D30[k].on = 0;
    for (k = 0; k < 0x14; k++) {
        u8 *b = (u8 *)PS2_PTR(func_0034EC80(k)), c[4];

        if (b != 0 && func_0034EE50(b) != 0) {
            func_0034ED90(b, c);
            func_0035DEE0(k, 0, 0x3C);
            func_0035E210(k);
        }
    }
}

/* 0x0035E0D0, 8 bytes, matching. */
void func_0035E0D0(void)
{
}

/* 0x0035E0E0, 0xAC bytes. Every 50 frames, the drops whose time came (again after one count
 * when nothing dropped). */
void func_0035E0E0(void)
{
    BaseDrop *d = g_007B6D30;
    u32 k;

    if (g_00669F9C % 0x32 != 0)
        return;
    for (k = 0; k < 0x14; k++, d++) {
        if (d->on != 0 && d->period != 0 && --d->timer < 1) {
            if (d->drop(k) == 0)
                d->timer = 1;
            else
                d->timer = d->period;
        }
    }
}

/* 0x0035E190, 0x38 bytes. Base `k` drops every 60 counts. */
void func_0035E190(u32 k)
{
    if (k < 0x14 && g_007B6D30[k].on != 0)
        g_007B6D30[k].period = 0x3C;
}

/* 0x0035E1D0, 0x34 bytes. Base `k` stops dropping. */
void func_0035E1D0(u32 k)
{
    if (k < 0x14 && g_007B6D30[k].on != 0)
        g_007B6D30[k].period = 0;
}

/* 0x0035E210, 0x7C bytes. Only side 0's bases drop. */
void func_0035E210(u32 k)
{
    u8 *b;

    if (k < 0x14 && (b = (u8 *)PS2_PTR(func_0034EC80(k))) != 0 && func_0034EE50(b) != 0) {
        if (func_0034EDB0(b) == 0)
            func_0035E190(k);
        else
            func_0035E1D0(k);
    }
}

/* 0x0035E290, 0x38 bytes. Base `k` drops on the next count. */
void func_0035E290(u32 k)
{
    if (k < 0x14 && g_007B6D30[k].on != 0)
        g_007B6D30[k].timer = 1;
}

/* 0x0035E2D0, 0x9C bytes. Whether base `k` may drop: not cut off, no enemy in its cell. */
int func_0035E2D0(u32 k)
{
    u8 *b;

    if (k >= 0x14 || (b = (u8 *)PS2_PTR(func_0034EC80(k))) == 0 || func_0034EE50(b) == 0)
        return 0;
    if (func_0034EE80(b) != 0)
        return 0;
    return func_00352780(b, func_0035D5A0(func_0034EDB0(b))) == 0;
}

/* 0x0035E370, 0x104 bytes. Drops one of the `n` items of `t` by weight at base `k` (one better
 * with event 5 when `better`). */
int func_0035E370(u32 k, Pick *t, u32 n, int better)
{
    u32 s = 0, i = 0, r = RANDOM();

    for (; i < n; i++) {
        s += t[i].weight;
        if (r % 100 < s)
            break;
    }
    if (better != 0 && func_0036F390(0, 5) != 0) {
        i++;
        if (i > n - 1)
            i = n - 1;
    }
    func_0024D070(t[i].id, (unsigned int *)(&g_007B6D30[k]));
    return 1;
}

/* 0x0035E480, 0x54 bytes. */
int func_0035E480(u32 k)
{
    Pick t[2];

    t[0] = g_00415C80[0];
    t[1] = g_00415C80[1];
    return func_0035E370(k, t, 2, 0);
}

/* 0x0035E4E0, 0x6C bytes. */
int func_0035E4E0(u32 k)
{
    Pick t[3];

    t[0] = g_00415C90[0];
    t[1] = g_00415C90[1];
    t[2] = g_00415C90[2];
    return func_0035E370(k, t, 3, 0);
}

/* 0x0035E550, 0x6C bytes. */
int func_0035E550(u32 k)
{
    Pick t[3];

    t[0] = g_00415CB0[0];
    t[1] = g_00415CB0[1];
    t[2] = g_00415CB0[2];
    return func_0035E370(k, t, 3, 1);
}

/* 0x0035E5C0, 0x334 bytes. Drops a healing item at base `k`, its size from the players' average
 * strength and chance (1.5 times with event 7, two better with event 5). */
int func_0035E5C0(u32 k)
{
    u32 t[8], n = 0, r, v;
    float mul = 1.0f, s = 0.0f, x;
    int p;

    t[0] = g_00415CD0[0];
    t[1] = g_00415CD0[1];
    t[2] = g_00415CD0[2];
    t[3] = g_00415CD0[3];
    t[4] = g_00415CD0[4];
    if (k >= 0x14)
        return 0;
    if (func_0036F390(0, 7) != 0)
        mul = 1.5f;
    for (p = 0; p < 2; p++) {
        if (PLAYER_ON(p) != 0) {
            s += (float)*(u16 *)(func_00338410(GROUP_INDEX(func_0035DD10(p))) + 0x1A);
            n++;
        }
    }
    if (n == 0)
        return 0;
    r = RANDOM();
    s = s / (float)n * mul / 2.0f;
    v = func_0035F100();
    x = (s + ((float)v * 50.0f + 1000.0f / mul + 0.0f) * (float)(r % 0xFFFF) / 65536.0f) / 1000.0f;
    n = (u32)x;
    if (func_0036F390(0, 5) != 0)
        n += 2;
    if (n > 4)
        n = 4;
    func_0024D070(t[n], (unsigned int *)(&g_007B6D30[k]));
    return 1;
}

/* 0x0035E900, 0xC0 bytes. Base `k`'s drop: 5% one kind, 25% another, else a healing item. */
int func_0035E900(u32 k)
{
    u32 r;

    if (func_0035E2D0(k) == 0)
        return 0;
    r = RANDOM() % 100;
    if (r < 5)
        return func_0035E480(k);
    if (r < 5)
        return func_0035E4E0(k);
    if (r < 0x1E)
        return func_0035E550(k);
    return func_0035E5C0(k);
}
