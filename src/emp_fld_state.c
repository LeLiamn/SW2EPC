/*
 * emp_fld_state.c - the battlefield's set-up data (a file loaded at battle start) and the battle
 * state block at 0x007B6FB0 (sides, main bases, reserves, counts). Original file name unknown
 * (0x0035E9C0-).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The battle state (0x2C bytes; saved at +0x84 of the save image). */
typedef struct {
    u8 side;                 /* +0x00 the player's side */
    u8 level;                /* +0x01 */
    u16 balance;             /* +0x02 1-1000, side 0's share */
    u8 main_base[4];         /* +0x04 per side */
    int count[2];            /* +0x08 per side (>= 0) */
    u8 b10[2];               /* +0x10 per side */
    u8 flags;                /* +0x12 */
    u8 kind;                 /* +0x13 the battle kind */
    u8 b14[2];               /* +0x14 per side */
    u8 reserve_base[2];      /* +0x16 per side (0x14 = none) */
    u8 reserve_wait[2];      /* +0x18 per side (0xFF = none) */
    u8 b1A[2];               /* +0x1A per side */
    u8 tally[2][5];          /* +0x1C per side */
    u16 score[2];            /* +0x26 per side */
    u8 b2A;                  /* +0x2A */
    u8 pad_2B;
} BattleState;

extern BattleState g_007B6FB0;
extern u8 *g_0045D768;                   /* (small data) the set-up data file */
extern int g_0045D088[2];                /* (small data) reserve base list sizes */
extern u32 g_00415CF0[4], g_00415D00[3];
extern u8 g_00669D60[];                  /* the settings */
extern int g_00669F6C;
extern u8 g_00500700[][0x88];            /* the pads */
extern const char g_00448238[];
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define PLAYER_ON(p) (*(int *)(g_00669D60 + (p) * 0x48 + 0xA0))

u8 *func_001026D0(int a, int b, int c, int d, int e, int f, const char *path, int g);
void func_00102EC0(void *p);
int func_0036D300(void);
int func_0036D310(void);
int func_0036D2E0(void);
u32 func_001041B0(u8 pad);
u16 func_0035DCB0(int p);
void func_0035CCE0(u16 g, u16 dir);
void func_0011EB80(void *to, const void *from, int n);
u8 *func_002EFB00(int k);
u8 func_00362660(int s);
int func_00363800(int s, u32 k);
u16 func_00362260(int s, int k);
int func_00362160(int s, int k);
int func_00362F40(int s, u32 k);
int func_00362810(void);
int func_00363770(int s, int k);
int func_002F27D0(int v);
void func_00362F60(void);
int func_003637D0(int s, int k);
u8 func_00362570(void);
void func_00360E80(void);
int func_00363720(int p);
int func_002F5730(int x);
u8 *func_0035DAF0(int x, int y);
int func_003DD680(int p);
int func_003DD5B0(int a, int b);
int func_0036F390(u32 s, int k);
int func_0036D6A0(int a);
int func_0036D500(u32 a);
int func_00327E90(void);
int func_002FA870(int a);
u8 **func_0033EF80(u32 k);
void func_0033EDC0(u8 **g);
int func_0036F420(u32 s, int k);
u8 **func_0033F110(u8 s);
int func_0033B1E0(u8 **g);
int func_0034EC80(int k);
int func_0034EE50(u8 *b);
int func_0034EDB0(u8 *b);
int func_00352240(u8 *b, int side);
void func_0035CC80(void);
void func_00361310(void);
void func_00360700(void);
void func_00361240(void);
void func_003653F0(int l, void *buf, int cap);
void func_00365230(int l);
void func_00364E40(int l, int k);
int func_003653D0(int l);
int func_00365060(int l);
int func_0035D5A0(int side);
int func_0035F060(int p);
int func_0035F2D0(u32 s);
int func_0032E7B0(void);

/* 0x0035E9C0, 0x1C bytes, matching. Set-up record `k` of the first table (0x18 bytes). */
u8 *func_0035E9C0(int k)
{
    return *(u8 **)(g_0045D768 + 4) + k * 0x18;
}

/* 0x0035E9E0, 0x18 bytes, matching. Of the second table (0x134 bytes). */
u8 *func_0035E9E0(int k)
{
    return *(u8 **)(g_0045D768 + 8) + k * 0x134;
}

/* 0x0035EA00, 0x14 bytes, matching. Of the third table (0x20 bytes). */
u8 *func_0035EA00(int k)
{
    return *(u8 **)(g_0045D768 + 0xC) + k * 0x20;
}

/* 0x0035EA20, 0x1C bytes, matching. Of the fourth table (0x50 bytes). */
u8 *func_0035EA20(int k)
{
    return *(u8 **)(g_0045D768 + 0x10) + k * 0x50;
}

/* 0x0035EA40, 0x20 bytes, matching. */
int func_0035EA40(int k)
{
    return *(int *)func_0035E9C0(k);
}

/* 0x0035EA60, 0x20 bytes, matching. */
int func_0035EA60(int k)
{
    return *(int *)(func_0035E9C0(k) + 8);
}

/* 0x0035EA80, 0x20 bytes, matching. */
int func_0035EA80(int k)
{
    return *(int *)(func_0035E9C0(k) + 0x10);
}

/* 0x0035EAA0, 0x20 bytes, matching. */
int func_0035EAA0(int k)
{
    return *(int *)(func_0035E9C0(k) + 0x14);
}

/* 0x0035EAC0, 0x20 bytes, matching. */
int func_0035EAC0(int k)
{
    return *(int *)func_0035E9E0(k);
}

/* 0x0035EAE0, 0x30 bytes. */
int func_0035EAE0(int k, int a, int b)
{
    return *(int *)(func_0035E9E0(k) + a * 0x20 + b * 4 + 0xC);
}

/* 0x0035EB10, 0x30 bytes. */
int func_0035EB10(int k, int a, int b)
{
    return *(int *)(func_0035E9E0(k) + a * 0x20 + b * 4 + 0x4C);
}

/* 0x0035EB40, 0x28 bytes. */
int func_0035EB40(int k, int a)
{
    return *(int *)(func_0035E9E0(k) + a * 4 + 0xCC);
}

/* 0x0035EB70, 0x28 bytes. */
int func_0035EB70(int k, int a)
{
    return *(int *)(func_0035E9E0(k) + a * 4 + 0xD4);
}

/* 0x0035EBA0, 0x30 bytes. */
int func_0035EBA0(int k, int a, int b)
{
    return *(int *)(func_0035E9E0(k) + a * 8 + b * 4 + 0x124);
}

/* 0x0035EBD0, 0x30 bytes. */
int func_0035EBD0(int k, int a, int b)
{
    return *(int *)(func_0035EA00(k) + a * 0x10 + b * 4);
}

/* 0x0035EC00, 0xE4 bytes. One of record `k`'s four values for `a` at random (-1 = unused;
 * `a != 0` when none). */
u32 func_0035EC00(int k, int a)
{
    u32 t[4], j;
    int n = 0;

    for (j = 0; j < 4; j++) {
        int v = func_0035EBD0(k, a, j);

        if (v != -1)
            t[n++] = v;
    }
    if (n == 0)
        return a != 0;
    return t[n == 0 ? 0 : (int)RANDOM() % n];
}

/* 0x0035ECF0, 0x28 bytes. */
int func_0035ECF0(int k, int a)
{
    return *(int *)(func_0035EA20(k) + a * 4);
}

/* 0x0035ED20, 0x70 bytes. Loads the set-up data file and turns its offsets into pointers. */
void func_0035ED20(void)
{
    g_0045D768 = func_001026D0(1, 0x4AA, 0, 1, 0, 0, g_00448238, 0xC2);
    *(int *)(g_0045D768 + 4) += (int)g_0045D768;
    *(int *)(g_0045D768 + 8) += (int)g_0045D768;
    *(int *)(g_0045D768 + 0xC) += (int)g_0045D768;
    *(int *)(g_0045D768 + 0x10) += (int)g_0045D768;
}

/* 0x0035ED90, 0x20 bytes, matching. Frees it. */
void func_0035ED90(void)
{
    func_00102EC0(g_0045D768);
    g_0045D768 = 0;
}

/* Pad `n`'s ready test. */
#define PAD_READY(n) ((g_00500700[n][0x64] & 1) ? (g_00500700[n][0x65] & 1) == 1 : 0)

/* 0x0035EDB0, 0x254 bytes. The players' direction orders (stick or buttons, 4 = none) for their
 * groups. */
void func_0035EDB0(void)
{
    int p;

    if (func_0036D300() != 0 || func_0036D310() != 0)
        return;
    for (p = 0; p < 2; p++) {
        u8 n;
        u32 dir = 4;

        if (PLAYER_ON(p) == 0)
            continue;
        n = g_00669D60[p * 0x48 + 0xCA];
        if (func_0035F060(p) == 0) {
            int pressed = PAD_READY(n) ? *(u16 *)(g_00500700[n] + 0x4C) : 0;
            u8 x = PAD_READY(n) ? g_00500700[n][0xA] : 0x80, y;

            if ((pressed & 0x8000) == 0 || x > 0x3F) {
                if ((pressed & 0x2000) != 0 && x > 0xC0)
                    dir = 3;
            } else {
                dir = 2;
            }
            y = PAD_READY(n) ? g_00500700[n][0xB] : 0x80;
            if ((pressed & 0x1000) == 0 || y > 0x3F) {
                if ((pressed & 0x4000) != 0 && y > 0xC0)
                    dir = 1;
            } else {
                dir = 0;
            }
        } else {
            u32 b = func_001041B0(n);

            if ((b & 0x1000) != 0)
                dir = 0;
            else if ((b & 0x4000) != 0)
                dir = 1;
            else if ((b & 0x8000) != 0)
                dir = 2;
            else if ((b & 0x2000) != 0)
                dir = 3;
        }
        if (dir < 4)
            func_0035CCE0(func_0035DCB0(p), dir);
    }
}

/* 0x0035F020, 8 bytes, matching. */
void func_0035F020(void)
{
}

/* 0x0035F030, 0x24 bytes, matching. */
void func_0035F030(void)
{
    func_0035EDB0();
    func_0035F020();
}

/* 0x0035F060, 0x30 bytes. Whether player `p` uses the stick for orders. */
int func_0035F060(int p)
{
    return (g_00669D60[p * 0x12 + 0x3D] & 7) >> 2 == 0;
}

/* 0x0035F090, 0xC bytes, matching. */
BattleState *func_0035F090(void)
{
    return &g_007B6FB0;
}

/* 0x0035F0A0, 0x20 bytes. */
void func_0035F0A0(u8 v)
{
    func_0035F090()->side = v;
}

/* 0x0035F0C0, 0x20 bytes, matching. The player's side. */
u8 func_0035F0C0(void)
{
    return func_0035F090()->side;
}

/* 0x0035F0E0, 0x20 bytes. */
void func_0035F0E0(u8 v)
{
    func_0035F090()->level = v;
}

/* 0x0035F100, 0x20 bytes, matching. */
u8 func_0035F100(void)
{
    return func_0035F090()->level;
}

/* 0x0035F120, 0x44 bytes. Sets the balance (1-1000). */
void func_0035F120(u32 v)
{
    u16 b = v < 2 ? 1 : v;

    if (v > 1000)
        b = 1000;
    func_0035F090()->balance = b;
}

/* 0x0035F170, 0x20 bytes, matching. */
u16 func_0035F170(void)
{
    return func_0035F090()->balance;
}

/* 0x0035F190, 0x38 bytes. Side `s`'s share of the balance. */
int func_0035F190(int s)
{
    if (s == 0)
        return func_0035F170();
    return 1000 - func_0035F170();
}

/* 0x0035F1D0, 0x28 bytes. */
void func_0035F1D0(int s, u8 b)
{
    func_0035F090()->main_base[s] = b;
}

/* 0x0035F200, 0x28 bytes. Side `s`'s main base. */
u8 func_0035F200(int s)
{
    return func_0035F090()->main_base[s];
}

/* 0x0035F230, 0x44 bytes. */
void func_0035F230(u32 s, int v)
{
    if (s >= 2)
        return;
    if (v < 1)
        v = 0;
    func_0035F090()->count[s] = v;
}

/* 0x0035F280, 0x48 bytes, matching. */
void func_0035F280(u32 s, int d)
{
    if (s < 2)
        func_0035F230(s, d + func_0035F2D0(s));
}

/* 0x0035F2D0, 0x38 bytes. */
int func_0035F2D0(u32 s)
{
    if (s >= 2)
        return 0;
    return func_0035F090()->count[s];
}

/* 0x0035F310, 0x28 bytes. */
void func_0035F310(int s, u8 v)
{
    func_0035F090()->b10[s] = v;
}

/* 0x0035F340, 0x28 bytes. */
u8 func_0035F340(int s)
{
    return func_0035F090()->b10[s];
}

/* 0x0035F370, 0x2C bytes. */
void func_0035F370(u8 f)
{
    func_0035F090()->flags |= f;
}

/* 0x0035F3A0, 0x30 bytes. */
void func_0035F3A0(u8 f)
{
    func_0035F090()->flags &= ~f;
}

/* 0x0035F3D0, 0x2C bytes. */
int func_0035F3D0(u8 f)
{
    return (f & func_0035F090()->flags) != 0;
}

/* 0x0035F400, 0x20 bytes. */
void func_0035F400(u8 v)
{
    func_0035F090()->kind = v;
}

/* 0x0035F420, 0x20 bytes, matching. The battle kind. */
u8 func_0035F420(void)
{
    return func_0035F090()->kind;
}

/* 0x0035F440, 0x38 bytes. Whether it is a kind 6-0xF battle. */
int func_0035F440(void)
{
    int r = 0;

    if (func_0035F420() > 5)
        r = func_0035F420() < 0x10;
    return r;
}

/* 0x0035F480, 0x30 bytes. */
void func_0035F480(u32 s, u8 v)
{
    if (s < 2)
        func_0035F090()->b14[s] = v;
}

/* 0x0035F4B0, 0x38 bytes. */
u8 func_0035F4B0(u32 s)
{
    if (s >= 2)
        return 0xFF;
    return func_0035F090()->b14[s];
}

/* 0x0035F4F0, 0x30 bytes. */
void func_0035F4F0(u32 s, u8 v)
{
    if (s < 2)
        func_0035F090()->reserve_base[s] = v;
}

/* 0x0035F520, 0x38 bytes. Side `s`'s reserve base (0x14 for none). */
u8 func_0035F520(u32 s)
{
    if (s >= 2)
        return 0x14;
    return func_0035F090()->reserve_base[s];
}

/* 0x0035F560, 0x30 bytes. */
void func_0035F560(u32 s, u8 v)
{
    if (s < 2)
        func_0035F090()->reserve_wait[s] = v;
}

/* 0x0035F590, 0x38 bytes. */
u8 func_0035F590(u32 s)
{
    if (s >= 2)
        return 0xFF;
    return func_0035F090()->reserve_wait[s];
}

/* 0x0035F5D0, 0x38 bytes. A reserve wait (3-7). */
int func_0035F5D0(void)
{
    return RANDOM() % 5 + 3;
}

/* 0x0035F610, 0x28 bytes. */
void func_0035F610(int s, u8 v)
{
    func_0035F090()->b1A[s] = v;
}

/* 0x0035F640, 0x28 bytes. */
u8 func_0035F640(int s)
{
    return func_0035F090()->b1A[s];
}

/* 0x0035F670, 0x40 bytes. */
void func_0035F670(int s, int k, u32 v)
{
    if (v > 0xFF)
        v = 0xFF;
    func_0035F090()->tally[s][k] = v;
}

/* 0x0035F6B0, 0x34 bytes. */
u8 func_0035F6B0(int s, int k)
{
    return func_0035F090()->tally[s][k];
}

/* 0x0035F6F0, 0x4C bytes. */
void func_0035F6F0(int s, int k)
{
    u8 v = func_0035F6B0(s, k);

    if (v < 0xFF)
        func_0035F670(s, k, v + 1);
}

/* 0x0035F740, 0x38 bytes. */
void func_0035F740(int s, u32 v)
{
    if (v > 0xFFFF)
        v = 0xFFFF;
    func_0035F090()->score[s] = v;
}

/* 0x0035F780, 0x28 bytes. */
u16 func_0035F780(int s)
{
    return func_0035F090()->score[s];
}

/* 0x0035F7B0, 0x64 bytes. */
void func_0035F7B0(int s, int d)
{
    int v = func_0035F780(s) + d;

    if (v < 1)
        v = 0;
    if (v > 0xFFFF)
        v = 0xFFFF;
    func_0035F740(s, v);
}

/* 0x0035F820, 0x20 bytes. */
void func_0035F820(u8 v)
{
    func_0035F090()->b2A = v;
}

/* 0x0035F840, 0x20 bytes, matching. */
u8 func_0035F840(void)
{
    return func_0035F090()->b2A;
}

/* 0x0035F860, 0x2C bytes. Saves the battle state into save image `p`. */
void func_0035F860(u8 *p)
{
    func_0011EB80(p + 0x84, func_0035F090(), 0x2C);
}

/* 0x0035F890, 0x34 bytes. Loads it from the save image. */
void func_0035F890(void)
{
    u8 *p = func_002EFB00(9);

    func_0011EB80(func_0035F090(), p + 0x84, 0x2C);
}

/* 0x0035F8D0, 0x44 bytes, matching. */
void func_0035F8D0(void)
{
    u32 s;

    for (s = 0; s < 2; s++)
        func_0035F310(s, func_00362660(s));
}

/* 0x0035F920, 0x8C bytes. Each side's count: the sum of its present officers'. */
void func_0035F920(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        int n = 0;

        for (k = 0; k < 8; k++) {
            if (func_00363800(s, k) != 0)
                n += func_00362260(s, k);
        }
        func_0035F230(s, n);
    }
}

/* 0x0035F9B0, 0x1BC bytes. Sides with a hidden officer waiting (slots 6-7) get a random reserve
 * base from their list. */
void func_0035F9B0(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        int found = 0;

        for (k = 6; k < 8; k++) {
            if (func_00362160(s, k) != 0x252 && func_00363800(s, k) == 0 && func_00362F40(s, k) == 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            u32 t0[4], t1[3], *t[2];
            int n[2];

            t0[0] = g_00415CF0[0];
            t0[1] = g_00415CF0[1];
            t0[2] = g_00415CF0[2];
            t0[3] = g_00415CF0[3];
            t1[0] = g_00415D00[0];
            t1[1] = g_00415D00[1];
            t1[2] = g_00415D00[2];
            t[0] = t0;
            t[1] = t1;
            n[0] = g_0045D088[0];
            n[1] = g_0045D088[1];
            func_0035F480(s, t[s][n[s] == 0 ? 0 : (int)RANDOM() % n[s]]);
        }
    }
}

/* 0x0035FB70, 0x100 bytes. Resets the battle state for a new battle. */
void func_0035FB70(void)
{
    u32 kind = func_00362570(), s, k;

    if (func_0035EAC0(kind) == 0)
        func_0035F0A0(1);
    else
        func_0035F0A0(0);
    func_0035F400(kind);
    func_0035F120(500);
    func_0035F3A0(0xFF);
    func_0035F820(0x47);
    for (s = 0; s < 2; s++) {
        func_0035F310(s, 10);
        func_0035F480(s, 0xFF);
        func_0035F4F0(s, 0x14);
        func_0035F560(s, 0xFF);
    }
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 5; k++)
            func_0035F670(s, k, 0);
        func_0035F740(s, 0);
    }
}

/* 0x0035FC70, 0x58 bytes. A new battle's state. */
void func_0035FC70(void)
{
    u32 k;

    for (k = 0; k < 3; k++)
        func_0035F090()->main_base[k] = 0x14;
    func_0035FB70();
    func_0035F8D0();
    func_0035F920();
    func_0035F9B0();
}

/* 0x0035FCD0, 0x1C bytes, matching. */
void func_0035FCD0(void)
{
    func_0035F890();
}

/* 0x0035FCF0, 0x1C bytes, matching. */
void func_0035FCF0(void)
{
    func_00360E80();
}

/* 0x0035FD10, 0x48 bytes. The battle state at battle start (loaded when resuming). */
void func_0035FD10(void)
{
    func_0035FCF0();
    if (g_00669F6C == 1)
        func_0035FCD0();
    else
        func_0035FC70();
}

/* 0x0035FD60, 0xF8 bytes. The level: half the players' item 7 bonuses (+20 with their mounts)
 * plus 5. */
void func_0035FD60(void)
{
    u32 n = 0, k;
    int p;

    for (p = 0; p < 2; p++) {
        int x, m;

        if (PLAYER_ON(p) == 0)
            continue;
        x = func_00363720(p);
        {
            u8 *r = func_0035DAF0(x, func_002F5730(x));

            for (k = 0; k < 8; k++) {
                if (r[k + 2] == 7)
                    n += r[k + 10];
            }
        }
        m = func_003DD680(p);
        if (m >= 0 && m < 4 && func_003DD5B0(m + 0x10, 0) != 0)
            n += 0x14;
    }
    func_0035F0E0((n >> 1) + 5);
}

/* 0x0035FE60, 8 bytes, matching. */
void func_0035FE60(void)
{
}

/* 0x0035FE70, 0x150 bytes. Which sides get reserves (and their wait). */
void func_0035FE70(void)
{
    u32 s;

    for (s = 0; s < 2; s++) {
        int go = 0;

        if (s == func_0035F0C0())
            go = func_0036F390(s, 4) != 0;
        if (func_0036D2E0() != 0 && s == 1) {
            if (func_0036D6A0(0) == func_0036D500(0)) {
                int v = -func_00327E90();

                if ((int)(RANDOM() % 10) < v / 2)
                    go = 1;
            }
        } else if (func_0036D2E0() != 0 && func_002FA870(func_0036D500(s)) != 0) {
            go = 1;
        }
        if (go)
            func_0035F560(s, func_0035F5D0());
    }
}

/* 0x0035FFC0, 0x50 bytes, matching. */
void func_0035FFC0(void)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 **g = func_0033EF80(k);

        if ((((u32 *)g)[0x19] & 1) != 0)
            func_0033EDC0(g);
    }
}

/* 0x00360010, 0x74 bytes. Each side's +0x1A value: twice its event 7 count minus the other
 * side's event 6. */
void func_00360010(void)
{
    u32 s;

    for (s = 0; s < 2; s++) {
        int a = func_0036F420(s, 7), b = func_0036F420(func_0035D5A0(s), 6);

        func_0035F610(s, a * 2 + b * -2);
    }
}

/* 0x00360090, 0x60 bytes. The battle state's set-up after loading. */
void func_00360090(void)
{
    if (func_0032E7B0() != 0 || g_00669F6C == 1)
        return;
    func_0035FD60();
    func_0035FE60();
    func_0035FE70();
    func_0035FFC0();
    func_00360010();
}

/* 0x003600F0, 8 bytes, matching. */
void func_003600F0(void)
{
}

/* 0x00360100, 0x70 bytes. Side 1's commander alert (once): its main base threatened. */
void func_00360100(void)
{
    if (func_0033B1E0(func_0033F110(1)) == 0 && func_0035F3D0(1) == 0) {
        if (func_00352240((u8 *)func_0034EC80(func_0035F200(1)), 0) != 0) {
            func_0035CC80();
            func_0035F370(1);
        }
    }
}

/* 0x00360170, 0x34 bytes, matching. */
void func_00360170(void)
{
    func_00361310();
    func_00360100();
    func_00360700();
    func_00361240();
}

/* 0x003601B0, 0x144 bytes. A random base of side `s` (else any but the enemy's main base;
 * 0x14 for none). */
u32 func_003601B0(u32 s)
{
    u8 buf[80], l[16];
    u32 e, k;

    if (s >= 2)
        return 0x14;
    func_003653F0((int)l, buf, 0x14);
    func_00365230((int)l);
    e = func_0035D5A0(s);
    for (k = 0; k < 0x14; k++) {
        u8 *b = (u8 *)func_0034EC80(k);

        if (b != 0 && func_0034EE50(b) != 0 && s == (u32)func_0034EDB0(b))
            func_00364E40((int)l, k);
    }
    if (func_003653D0((int)l) != 0)
        return func_00365060((int)l);
    for (k = 0; k < 0x14; k++) {
        u8 *b = (u8 *)func_0034EC80(k);

        if (b != 0 && func_0034EE50(b) != 0 && k != func_0035F200(e))
            func_00364E40((int)l, k);
    }
    if (func_003653D0((int)l) == 0)
        return 0x14;
    return func_00365060((int)l);
}

extern int g_00669F9C, g_00669FA0;       /* the battle's frame counter, its time limit */
extern u32 g_00669DEC;
extern int (*g_00415D10[4])(void);       /* the battle end checks */
extern int (*g_0045D090[2])(void);       /* (small data) the battle comment checks */
extern u8 g_0045D76C;                    /* (small data) their wait */
extern u8 g_006A1D58[][0x68];

#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)
#define UNIT_FLAGS(u) (*(u32 *)((u) + 0x80))
#define UNIT_ACTIVE(u) ((UNIT_FLAGS(u) & 1) != 0 && (UNIT_FLAGS(u) & 0x8C40002) == 0 \
                        && (UNIT_FLAGS(u) & 4) == 0)

void func_0035CBF0(u32 s);
void func_0035CB90(u32 s);
void func_0035CBC0(u32 s);
void func_0035CC50(u32 s);
void func_0035CC20(u32 g);
void func_0035C9D0(u16 kind, int won);
void func_0035D2A0(void);
void func_0035CEE0(u16 k, u16 g, u16 h);
u32 func_00361430(u32 s, u16 *out, u32 max);
int func_00361F50(void);
int func_0033F7D0(u32 s, int a);
int func_003531F0(int s);
int func_0033F860(int a, int b, int c);
u8 *func_00338410(u32 g);
int func_0033C320(u8 **g);
int func_0033CB60(u8 **g, int b);
int func_0033D150(u8 **g);
u8 **func_0035DD10(int p);
u32 func_0033F7F0(int b, int side);
u32 func_0033F430(int a, int b, int *out, int max);
u8 **func_0033EFD0(u32 s, u32 k);
int func_00190480(u8 *c);
int func_00353990(u8 *c);
int func_00353A50(u8 *c);
u32 func_003DD290(u8 *c, u32 s);

/* 0x00360300, 0xF8 bytes. Reserves due this count of 3000 frames get a base (or, with the enemy's
 * event 8, are called off). */
void func_00360300(void)
{
    int t = g_00669F9C / 3000;
    u32 s;

    for (s = 0; s < 2; s++) {
        if (t != func_0035F4B0(s) - 1)
            continue;
        func_0035F520(s);
        if (func_0035F520(s) > 0x13) {
            u32 e = func_0035D5A0(s);

            if (func_0036F390(e, 8) != 0) {
                func_0035CBF0(e);
                func_0035F480(s, 0xFF);
                func_0035F4F0(s, 0x14);
                continue;
            }
            func_0035F4F0(s, func_003601B0(s));
        }
        func_0035CB90(s);
    }
}

/* 0x00360400, 0xA4 bytes. Reserves arriving this count. */
void func_00360400(void)
{
    int t = g_00669F9C / 3000;
    u32 s;

    for (s = 0; s < 2; s++) {
        if (t != func_0035F4B0(s))
            continue;
        func_0035F520(s);
        if (func_0035F520(s) > 0x13)
            func_0035F4F0(s, func_003601B0(s));
        func_0035CBC0(s);
    }
}

/* 0x003604B0, 0x24 bytes, matching. Whether side `s` has a contested cell to send reinforcements to. */
int func_003604B0(u32 s)
{
    u16 c[4];

    return func_00361430(s, c, 3) != 0;
}

/* 0x003604E0, 0xE8 bytes. Reinforcements due this count (put off by 1-3 when there is nowhere to
 * go). */
void func_003604E0(void)
{
    int t = g_00669F9C / 3000;
    u32 s;

    for (s = 0; s < 2; s++) {
        if (t != func_0035F590(s))
            continue;
        if (func_003604B0(s) == 0) {
            u32 r = RANDOM();

            func_0035F560(s, func_0035F590(s) + r % 3 + 1);
        } else {
            func_0035CC50(s);
            func_0035F560(s, 0xFF);
        }
    }
}

/* 0x003605D0, 8 bytes, matching. */
void func_003605D0(void)
{
}

/* 0x003605E0, 0x11C bytes. Groups flagged 0x10 whose leader is in state 2 turn against their side
 * (once). */
void func_003605E0(void)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 **g = func_0033EF80(k);
        u32 *f;

        if (g == 0)
            continue;
        f = (u32 *)g + 0x19;
        if ((*f & 1) != 0 && UNIT_ACTIVE(*g) && (*f & 0x10) != 0 && *g != 0 && (*g)[0x7A] == 2) {
            func_0035CC20(GROUP_INDEX(g));
            *f &= ~0x10;
        }
    }
}

/* 0x00360700, 0xF0 bytes. The reserve and reinforcement checks, spread over the counts. */
void func_00360700(void)
{
    if (g_00669F9C % 0x32 == 0x14) {
        int k = (g_00669F9C / 0x32) % 0x3C;

        if (k == 3)
            func_003605D0();
        else if (k == 2)
            func_003604E0();
        else if (k == 1)
            func_00360400();
        else if (k == 0)
            func_00360300();
    } else if (g_00669F9C % 0x32 == 10) {
        func_003605E0();
    }
}

/* 0x003607F0, 0xD4 bytes. Battle end: a side lost its main base. */
int func_003607F0(void)
{
    u32 s;

    if (func_0036D310() != 0)
        return 0;
    for (s = 0; s < 2; s++) {
        u8 *b = (u8 *)func_0034EC80(func_0035F200(s));

        if ((s != 1 || func_0036D2E0() == 0 || func_0035F440() == 0) && s != (u32)func_0034EDB0(b)) {
            func_0035C9D0(0, s == 0 ? 0 : 1);
            return 1;
        }
    }
    return 0;
}

/* 0x003608D0, 0x12C bytes. Battle end: side 1's commander fell (the ending by battle kind). */
int func_003608D0(void)
{
    u8 **g;

    if (func_0036D310() != 0)
        return 0;
    g = func_0033F110(1);
    if (func_0033B1E0(g) == 0 || UNIT_ACTIVE(*g))
        return 0;
    switch (func_00362570()) {
    case 0:
    case 1:
        return 0;
    case 2:
    case 3:
        func_0035C9D0(2, 1);
        return 1;
    case 4:
    case 5:
        func_0035C9D0(1, 1);
        return 1;
    default:
        func_0035C9D0(2, 1);
        return 1;
    }
}

/* 0x00360A00, 0x94 bytes. Battle end: time out. */
int func_00360A00(void)
{
    if (g_00669F9C < g_00669FA0)
        return 0;
    if (func_0036D310() == 0) {
        if (func_0035F0C0() == 0)
            func_0035C9D0(3, 0);
        else
            func_0035C9D0(3, 1);
        return 1;
    }
    func_0035C9D0(3, 0);
    return 1;
}

/* 0x00360AA0, 0x60 bytes. Battle end with func_0036D310: the count reached. */
int func_00360AA0(void)
{
    u32 v = g_00669DEC;

    if (func_0036D310() == 0)
        return 0;
    if (v < func_00361F50())
        return 0;
    func_0035C9D0(3, 1);
    return 1;
}

/* 0x00360B00, 0x84 bytes. Runs the battle end checks (until one ends it). */
void func_00360B00(void)
{
    int (*t[4])(void);
    u32 k;

    t[0] = g_00415D10[0];
    t[1] = g_00415D10[1];
    t[2] = g_00415D10[2];
    t[3] = g_00415D10[3];
    for (k = 0; k < 4; k++) {
        if (t[k]() != 0)
            return;
    }
}

/* 0x00360B90, 0x70 bytes. With func_0036D310: the "one minute left" message (once). */
void func_00360B90(void)
{
    int left;

    if (func_0036D310() == 0 || func_0035F3D0(2) != 0)
        return;
    left = g_00669FA0 - g_00669F9C;
    if (left < 0)
        left = 0;
    if (left == 3000) {
        func_0035D2A0();
        func_0035F370(2);
    }
}

/* 0x00360C00, 0x27C bytes. The battle's balance (-100 side 1 to 100 side 0) from the sides'
 * counts, units and bases. */
int func_00360C00(void)
{
    int bases[2], units[2], count[2], v;
    u32 s;

    for (s = 0; s < 2; s++) {
        count[s] = func_0035F2D0(s);
        units[s] = func_0033F7D0(s, 1);
        bases[s] = func_003531F0(s);
    }
    if (count[1] * 5 < count[0])
        v = 0x32;
    else if (count[0] * 5 < count[1])
        v = -0x32;
    else
        v = count[0] * 0x32 / 90000 - count[1] * 0x32 / 90000;
    if (units[1] * 3 < units[0])
        v += 0x32;
    else if (units[0] * 3 < units[1])
        v -= 0x32;
    else
        v = v + units[0] * 0x32 / 9 - units[1] * 0x32 / 9;
    if (bases[1] * 3 < bases[0])
        v += 0x32;
    else if (bases[0] * 3 < bases[1])
        v -= 0x32;
    else
        v = v + bases[0] * 0x32 / 0x14 - bases[1] * 0x32 / 0x14;
    if (v < -99)
        v = -100;
    if (v > 100)
        v = 100;
    return v;
}

/* 0x00360E80, 8 bytes, matching. */
void func_00360E80(void)
{
    g_0045D76C = 0;
}

/* 0x00360E90, 0xC4 bytes. A side 0 group comments on the balance (comments 7-9). */
int func_00360E90(void)
{
    int v = func_00360C00();
    u8 *g;
    u32 k = 0xD;

    if (v < -0x50)
        k = 7;
    else if (v < -0x1E)
        k = 8;
    else if (v > 0x31)
        k = 9;
    if (k >= 0xD)
        return 0;
    g = (u8 *)func_0033F860(0, 1, 1);
    if (g == 0)
        return 0;
    func_0035CEE0(k, GROUP_INDEX(g), 0x47);
    return 1;
}

/* 0x00360F60, 0x120 bytes. Whether group `g` (of kind 3, strength 30 or more, at its base, near a
 * player) may comment on the player while the battle goes badly. */
int func_00360F60(u8 **g)
{
    u32 gi = GROUP_INDEX(g);
    int b, p;

    if (func_00338410(gi)[2] != 3)
        return 0;
    if (func_00338410(gi)[4] < 0x1E)
        return 0;
    b = func_0033C320(g);
    if (func_0033CB60(g, b) == 0)
        return 0;
    p = func_0033D150(g);
    if (p < 0 || p > 1)
        return 0;
    func_0035DD10(p);
    if (func_00360C00() >= 0x1F)
        return 0;
    return func_0033F7F0(b, func_0035D5A0((*g)[0x79])) > 2;
}

/* 0x00361080, 0x1C0 bytes. Now and then (30%) such a group comments on the player (comment 0xB). */
int func_00361080(void)
{
    int list[16];
    u8 **best = 0, **h;
    u32 n = func_0033F430(0, 1, list, 0x10), k;

    for (k = 0; k < n; k++) {
        u8 **g = (u8 **)g_006A1D58[list[k]];

        if (func_00360F60(g) != 0 && (best == 0 || RANDOM() % 100 < 0x32))
            best = g;
    }
    if (best == 0 || RANDOM() % 100 >= 0x1E)
        return 0;
    h = func_0035DD10(func_0033D150(best));
    if (h == 0)
        return 0;
    func_0035CEE0(0xB, GROUP_INDEX(best), GROUP_INDEX(h));
    return 1;
}

/* 0x00361240, 0xCC bytes. Every 50 frames, the battle comment checks (then a wait of 120-179
 * counts). */
void func_00361240(void)
{
    int (*t[2])(void);
    u32 k;

    t[0] = g_0045D090[0];
    t[1] = g_0045D090[1];
    if (g_00669F9C % 0x32 != 0)
        return;
    if (g_0045D76C != 0) {
        g_0045D76C--;
        return;
    }
    for (k = 0; k < 2; k++) {
        if (t[k]() != 0)
            g_0045D76C = RANDOM() % 0x3C + 'x';
    }
}

/* 0x00361310, 0x114 bytes. The balance from the sides' counts; marks the groups at bases. */
void func_00361310(void)
{
    int a = func_0035F2D0(0), b = func_0035F2D0(1), v;
    u32 s, k;

    v = a * 500 / (b < 2 ? a + 1 : a + b) + 200;
    if (v > 1000)
        v = 1000;
    if (v < 2)
        v = 1;
    func_0035F120(v);
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 0x14; k++) {
            u8 **g;

            if (func_0034EE50((u8 *)func_0034EC80(k)) != 0 && (g = func_0033EFD0(s, k)) != 0
                && (((u32 *)g)[0x19] & 1) != 0)
                ((int *)g)[0x13] = 1;
        }
    }
}

/* 0x00361430, 0x10C bytes. Up to `max` contested cells on the enemy's front (fewer than three of
 * side `s`'s units there) into `out`. */
u32 func_00361430(u32 s, u16 *out, u32 max)
{
    int e = func_0035D5A0(s), x, y;
    u32 n = 0;

    for (y = 0; y < 0x19; y++) {
        for (x = 0; x < 0x19; x++) {
            u8 c[2];

            if (n >= max)
                return n;
            c[0] = x;
            c[1] = y;
            if (func_00190480(c) != 0 && func_00353990(c) != 0 && e == func_00353A50(c)
                && func_003DD290(c, s) < 3) {
                n++;
                *out++ = *(u16 *)c;
            }
        }
    }
    return n;
}

extern int g_00415D20[3], g_00415D30[5];

u8 **func_0033F0C0(u32 s, u32 k);
void func_0033DDC0(u8 **g, u8 *cell);
int func_0033B140(u8 **g);
void func_003385E0(u8 **g, int a, int b);

/* 0x00361540, 0x80 bytes, matching. Sends side `s`'s three reinforcement groups to contested cells; whether
 * there were any. */
int func_00361540(u32 s)
{
    u16 c[4];
    u32 n = func_00361430(s, c, 3), k;

    for (k = 0; k < n; k++)
        func_0033DDC0(func_0033F0C0(s, k), (u8 *)&c[k]);
    return n != 0;
}

/* 0x003615C0, 0x80 bytes. Side `s`'s share of both sides' counts (percent). */
int func_003615C0(u32 s)
{
    int a, b;

    if (s >= 2)
        return 0;
    a = func_0035F2D0(s);
    b = func_0035F2D0(func_0035D5A0(s));
    if (a + b == 0)
        return 0;
    return a * 100 / (a + b);
}

/* Keeps `g` in `*best` at random, or when `*best` is down and `g` is not. */
static void keep_group(u8 ***best, u8 **g)
{
    if (*best == 0 || RANDOM() % 100 < 0x32)
        *best = g;
    else if (!UNIT_ACTIVE(**best) && UNIT_ACTIVE(*g))
        *best = g;
}

/* 0x00361640, 0x5F0 bytes. In kind 6-0xF battles, picks side 1's target group (a generic officer
 * first, then the kinds 400-0x19E, then the named officers, else any active one). */
void func_00361640(void)
{
    u8 **gen = 0, **spec = 0, **named = 0, **any = 0, **g = 0, **pick;
    u32 k;

    if (func_0035F840() < 0x47)
        return;
    if (func_00362570() <= 5 || func_00362570() >= 0x10)
        return;
    for (k = 0; k < 0x10; k++) {
        u16 id;

        g = func_0033EF80(k);
        if ((((u32 *)g)[0x19] & 1) == 0 || func_0033B140(g) != 0 || (*g)[0x79] != 1)
            continue;
        id = *(u16 *)func_00338410(GROUP_INDEX(g));
        if (id < 0x1C)
            keep_group(&gen, g);
        if (id > 399 && id < 0x19F)
            keep_group(&spec, g);
        if (id > 0x1B && id < 400)
            keep_group(&named, g);
        if (any == 0 && UNIT_ACTIVE(*g))
            any = g;
    }
    if (gen != 0)
        pick = gen;
    else if (spec != 0)
        pick = spec;
    else
        pick = named;
    if (pick == 0 || !UNIT_ACTIVE(*pick)) {
        if (any != 0)
            pick = any;
    }
    if (pick != 0) {
        func_0035F820(GROUP_INDEX(pick));
        func_0033EDC0(pick);
        func_003385E0(g, 4, 0xFF);
    }
}

/* 0x00361C30, 0xB0 bytes, matching. The total strength (+0x1E) of side `s`'s groups. */
int func_00361C30(int s)
{
    int list[16], n = 0;
    u32 c = func_0033F430(s, 1, list, 0x10), k;

    for (k = 0; k < c; k++)
        n += *(u16 *)(func_00338410(list[k] * 0x68 / 0x68) + 0x1E);
    return n;
}

/* 0x00361CE0, 0x5C bytes. Side `s`'s count against its groups' strength (percent). */
int func_00361CE0(int s)
{
    int a = func_0035F2D0(s), b = func_00361C30(s);

    if (b == 0)
        return 0;
    return a * 100 / b;
}

/* 0x00361D40, 0xD4 bytes. The average +0x4C value of side `s`'s groups (350 / 650 in the
 * flagged modes). */
int func_00361D40(int s)
{
    int list[16], n = 0;
    u32 c = func_0033F430(s, 1, list, 0x10), k;

    for (k = 0; k < c; k++) {
        int v;

        if ((*(u32 *)(g_00669D60 + 0x200) & 0xC) == 0)
            v = *(int *)(g_006A1D58[list[k]] + 0x4C);
        else if ((*(u8 **)g_006A1D58[list[k]])[0x79] == 0)
            v = 0x15E;
        else
            v = 0x28A;
        n += v;
    }
    if (c != 0)
        n /= (int)c;
    return n;
}

/* 0x00361E20, 0x6C bytes. The players' total score. */
int func_00361E20(void)
{
    int n = 0, p;

    for (p = 0; p < 2; p++) {
        if (PLAYER_ON(p) != 0)
            n += func_0035F780(p);
    }
    return n;
}

/* 0x00361E90, 0xB4 bytes. With func_0036D310: the score to reach (by battle kind 0x10-0x12 and
 * difficulty). */
int func_00361E90(void)
{
    int a[3], b[5];

    a[0] = g_00415D20[0];
    a[1] = g_00415D20[1];
    a[2] = g_00415D20[2];
    b[0] = g_00415D30[0];
    b[1] = g_00415D30[1];
    b[2] = g_00415D30[2];
    b[3] = g_00415D30[3];
    b[4] = g_00415D30[4];
    if (func_0036D310() == 0)
        return 0;
    return a[func_00362570() - 0x10] + b[g_00669D60[0x21]];
}

/* The battle set-up (0x84 bytes at 0x007B6FE0, saved as is). */
typedef struct {
    u16 officer[2][8];       /* +0x00 per side and slot (0x19F = none) */
    u16 life[2][8];          /* +0x20 (at most 10000) */
    u16 troops[2][8];        /* +0x40 (at most 10000) */
    u8 player_slot[2];       /* +0x60 the players' slots (8 = none) */
    u8 map;                  /* +0x62 */
    u8 kind;                 /* +0x63 the battle kind */
    u8 difficulty;           /* +0x64 */
    u8 b65[2][2];            /* +0x65 */
    u8 b69[2];               /* +0x69 */
    u8 hidden;               /* +0x6B bits 0-3: slots 6-7 of each side; 0x80 on */
    u8 present[2];           /* +0x6C one bit per slot */
    u16 name[2];             /* +0x6E (0x2F9 = custom) */
    u8 bits;                 /* +0x72 */
    u8 b73;                  /* +0x73 */
    u8 b74[2][6];            /* +0x74 */
    u8 b80[2];               /* +0x80 */
    u8 b82[2];               /* +0x82 */
} BattleSetup;

extern BattleSetup g_007B6FE0;
extern u8 g_0045D770[2];                 /* (small data) the slots taken out, a bit each */
extern int g_00415D48[3], g_00415D60[30];
extern u8 g_00415DE0[6];
extern const char g_004482D0[];

void func_0035D240(void);
void func_0035D270(void);
int func_00337A10(int x);
char *func_002F2880(void);
void func_0011ED38(void *p, int v, int n);
void func_0019B0E0(char *out, u32 v);
const char *func_00372470(void);
const char *func_00372460(void);
void func_001206B0(char *to, const char *s);
void func_00120928(char *to, const char *from);
u32 func_003F71B0(u32 k);
void func_00118850(void *p, int n);
u32 func_00327C00(void);
u32 func_0035D780(int m);
u32 func_0035D7F0(int m);
u32 func_0035D6E0(int m);
u32 func_0035D730(int m);
int func_0035D5B0(int k);
int func_0035EAE0(int k, int a, int b);
int func_0035EBA0(int k, int a, int b);
u8 func_0036F600(int v);
int func_001E6670(u32 d, u32 a, int m);
int func_003154F0(int a, int *out);
int func_0036F6A0(u32 v, u32 j, int *t, u32 kind);
int func_002F3DC0(int x);
int func_0036D3B0(int x);
int func_0036D400(int x);

/* 0x00361F50, 0x60 bytes. With func_0036D310: the count to reach (by battle kind 0x10-0x12). */
int func_00361F50(void)
{
    int t[3];

    t[0] = g_00415D48[0];
    t[1] = g_00415D48[1];
    t[2] = g_00415D48[2];
    if (func_0036D310() == 0)
        return 0;
    return t[func_00362570() - 0x10];
}

/* 0x00361FB0, 0x64 bytes. The "close to the goal" message when the count passes goal - 100. */
void func_00361FB0(u32 now, u32 before)
{
    u32 g;

    if (func_0036D310() == 0)
        return;
    g = func_00361F50() - 100;
    if (before < g && g <= now)
        func_0035D240();
}

/* 0x00362020, 0x78 bytes. The message each time the count passes a multiple of 50. */
void func_00362020(u32 now, int before)
{
    if (func_0036D310() != 0 && (before + 0x32U) / 0x32 * 0x32 <= now)
        func_0035D270();
}

/* 0x003620A0, 0xC bytes, matching. */
BattleSetup *func_003620A0(void)
{
    return &g_007B6FE0;
}

/* 0x003620B0, 0x30 bytes. */
void func_003620B0(int s, int k, u16 v)
{
    func_003620A0()->officer[s][k] = v;
}

/* 0x003620E0, 0x30 bytes. */
u16 func_003620E0(int s, int k)
{
    return func_003620A0()->officer[s][k];
}

/* 0x00362110, 0x44 bytes. */
void func_00362110(int s, int k, int x)
{
    func_003620B0(s, k, func_00337A10(x));
}

/* 0x00362160, 0x44 bytes. Slot `k` of side `s`'s officer kind (0x252 = none). */
int func_00362160(int s, int k)
{
    int v = (short)func_003620E0(s, k);

    if (v < 0 || v > 0x19E)
        return 0x252;
    return func_002F27D0(v);
}

/* 0x003621B0, 0x3C bytes. */
void func_003621B0(int s, int k, u32 v)
{
    if (v > 10000)
        v = 10000;
    func_003620A0()->life[s][k] = v;
}

/* 0x003621F0, 0x30 bytes. */
u16 func_003621F0(int s, int k)
{
    return func_003620A0()->life[s][k];
}

/* 0x00362220, 0x3C bytes. */
void func_00362220(int s, int k, u32 v)
{
    if (v > 10000)
        v = 10000;
    func_003620A0()->troops[s][k] = v;
}

/* 0x00362260, 0x30 bytes. */
u16 func_00362260(int s, int k)
{
    return func_003620A0()->troops[s][k];
}

/* 0x00362290, 0x5C bytes. Side `s`'s troops. */
int func_00362290(int s)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 8; k++)
        n += func_00362260(s, k);
    return n;
}

/* 0x003622F0, 0x28 bytes. */
void func_003622F0(int p, u8 v)
{
    func_003620A0()->player_slot[p] = v;
}

/* 0x00362320, 0x28 bytes. Player `p`'s slot. */
u8 func_00362320(int p)
{
    return func_003620A0()->player_slot[p];
}

/* 0x00362350, 0x20 bytes. */
void func_00362350(u8 v)
{
    func_003620A0()->map = v;
}

/* 0x00362370, 0x20 bytes, matching. */
u8 func_00362370(void)
{
    return func_003620A0()->map;
}

/* 0x00362390, 0x1C bytes, matching. */
void func_00362390(u8 v)
{
    func_00362350(v);
}

/* 0x003623B0, 0x24 bytes. The battlefield. */
u32 func_003623B0(void)
{
    return func_0035D780(func_00362370());
}

/* 0x003623E0, 0xA8 bytes. With func_0036D2E0: sets map `m` in the set of the current difficulty
 * (6 and up: as is). */
void func_003623E0(int m)
{
    if (func_0036D2E0() == 0)
        return;
    switch (func_00327C00()) {
    case 0: m += 0x1E; break;
    case 1: m += 0x24; break;
    case 2: m += 0x2A; break;
    case 3: m += 0x32; break;
    case 4: m += 0x38; break;
    case 5: m += 0x40; break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        break;
    default:
        return;
    }
    func_00362350(m);
}

/* 0x00362490, 0xBC bytes. The map number within the difficulty's set (0x19 without
 * func_0036D2E0). */
u32 func_00362490(void)
{
    u32 m, r = 0;

    if (func_0036D2E0() == 0)
        return 0x19;
    m = func_00362370();
    switch (func_00327C00()) {
    case 0: r = m - 0x1E; break;
    case 1: r = m - 0x24; break;
    case 2: r = m - 0x2A; break;
    case 3: r = m - 0x32; break;
    case 4: r = m - 0x38; break;
    case 5: r = m - 0x40; break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        r = m < 0x19 ? m : 0x19;
        break;
    }
    return r;
}

/* 0x00362550, 0x20 bytes. */
void func_00362550(u8 v)
{
    func_003620A0()->kind = v;
}

/* 0x00362570, 0x20 bytes, matching. The battle kind. */
u8 func_00362570(void)
{
    return func_003620A0()->kind;
}

/* 0x00362590, 0x20 bytes. */
void func_00362590(u8 v)
{
    func_003620A0()->difficulty = v;
}

/* 0x003625B0, 0x20 bytes, matching. */
u8 func_003625B0(void)
{
    return func_003620A0()->difficulty;
}

/* 0x003625D0, 0x30 bytes. */
void func_003625D0(int s, int k, u8 v)
{
    func_003620A0()->b65[s][k] = v;
}

/* 0x00362600, 0x30 bytes. */
u8 func_00362600(int s, int k)
{
    return func_003620A0()->b65[s][k];
}

/* 0x00362630, 0x28 bytes. */
void func_00362630(int s, u8 v)
{
    func_003620A0()->b69[s] = v;
}

/* 0x00362660, 0x28 bytes. */
u8 func_00362660(int s)
{
    return func_003620A0()->b69[s];
}

/* 0x00362690, 0x94 bytes. Which of the two sides' slots 6-7 are hidden. */
void func_00362690(int a, int b, int c, int d)
{
    func_003620A0()->hidden &= 0x80;
    if (a != 0)
        func_003620A0()->hidden |= 1;
    if (b != 0)
        func_003620A0()->hidden |= 2;
    if (c != 0)
        func_003620A0()->hidden |= 4;
    if (d != 0)
        func_003620A0()->hidden |= 8;
}

/* 0x00362730, 0x88 bytes. Whether side `s`'s slot `k` (6-7) is hidden. */
int func_00362730(u32 s, u32 k)
{
    if (s >= 2 || k >= 8 || func_00362810() == 0)
        return 0;
    return ((1 << (k + s * 2 - 6)) & 0xFF & func_003620A0()->hidden) != 0;
}

/* 0x003627C0, 0x44 bytes. */
void func_003627C0(int on)
{
    if (on == 0)
        func_003620A0()->hidden &= 0x7F;
    else
        func_003620A0()->hidden |= 0x80;
}

/* 0x00362810, 0x28 bytes, matching. */
int func_00362810(void)
{
    return (func_003620A0()->hidden & 0x80) != 0;
}

/* 0x00362840, 0x88 bytes. */
void func_00362840(u32 s, u32 k, int on)
{
    if (s >= 2 || k >= 8)
        return;
    if (on == 0)
        func_003620A0()->present[s] &= ~(1 << k);
    else
        func_003620A0()->present[s] |= 1 << k;
}

/* 0x003628D0, 0x54 bytes. */
int func_003628D0(u32 s, u32 k)
{
    if (s >= 2 || k >= 8)
        return 0;
    return ((1 << k) & func_003620A0()->present[s]) != 0;
}

/* 0x00362930, 0x58 bytes. Side `s`'s first present slot (8 for none). */
u32 func_00362930(u32 s)
{
    u32 k;

    for (k = 0; k < 8; k++) {
        if (func_003628D0(s, k) != 0)
            return k;
    }
    return k;
}

/* 0x00362990, 0x44 bytes. */
void func_00362990(u32 s, u32 v)
{
    if (s < 2 && v < 0x2FA)
        func_003620A0()->name[s] = v;
}

/* 0x003629E0, 0x38 bytes. */
u16 func_003629E0(u32 s)
{
    if (s >= 2)
        return 0;
    return func_003620A0()->name[s];
}

/* 0x00362A20, 0xA8 bytes. Side `s`'s name (a custom one is two parts). */
char *func_00362A20(u32 s)
{
    char *buf = func_002F2880();
    u16 v = func_003629E0(s);

    func_0011ED38(buf, 0, 0x18);
    if (v < 0x2F9) {
        func_0019B0E0(buf, v);
    } else {
        func_00120928(buf, func_00372470());
        func_001206B0(buf, g_004482D0);
        func_001206B0(buf, func_00372460());
    }
    return buf;
}

/* 0x00362AD0, 0x30 bytes. */
void func_00362AD0(u32 k)
{
    func_003620A0()->bits |= 1 << k;
}

/* 0x00362B00, 0x34 bytes. */
void func_00362B00(u32 k)
{
    func_003620A0()->bits &= ~(1 << k);
}

/* 0x00362B40, 0x20 bytes, matching. */
void func_00362B40(void)
{
    func_003620A0()->bits = 0;
}

/* 0x00362B60, 0x30 bytes. */
int func_00362B60(u32 k)
{
    return ((1 << k) & func_003620A0()->bits) != 0;
}

/* 0x00362B90, 0x20 bytes. */
void func_00362B90(u8 v)
{
    func_003620A0()->b73 = v;
}

/* 0x00362BB0, 0x20 bytes, matching. */
u8 func_00362BB0(void)
{
    return func_003620A0()->b73;
}

/* 0x00362BD0, 0x38 bytes. */
void func_00362BD0(int s, int k, u8 v)
{
    func_003620A0()->b74[s][k] = v;
}

/* 0x00362C10, 0x38 bytes. */
u8 func_00362C10(int s, int k)
{
    return func_003620A0()->b74[s][k];
}

/* 0x00362C50, 0x28 bytes. */
void func_00362C50(int s, u8 v)
{
    func_003620A0()->b80[s] = v;
}

/* 0x00362C80, 0x28 bytes. */
u8 func_00362C80(int s)
{
    return func_003620A0()->b80[s];
}

/* 0x00362CB0, 0x28 bytes. */
void func_00362CB0(int s, u8 v)
{
    func_003620A0()->b82[s] = v;
}

/* 0x00362CE0, 0x28 bytes. */
u8 func_00362CE0(int s)
{
    return func_003620A0()->b82[s];
}

/* 0x00362D10, 0x60 bytes. */
int func_00362D10(int s, int k)
{
    u32 v = func_00362C10(s, k);

    if (v >= 10)
        return 0;
    return func_003F71B0(v) <= func_00362CE0(s);
}

/* 0x00362D70, 0x74 bytes. */
int func_00362D70(int s)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 6; k++) {
        func_00362C10(s, k);
        if (func_00362C10(s, k) < 10)
            n++;
    }
    return n;
}

/* 0x00362DF0, 0x28 bytes. Saves the set-up. */
void func_00362DF0(u8 *p)
{
    func_0011EB80(p, func_003620A0(), 0x84);
}

/* 0x00362E20, 0x44 bytes. Loads it. */
void func_00362E20(void)
{
    u8 *p = func_002EFB00(9);

    func_0011EB80(func_003620A0(), p, 0x84);
    func_00118850(g_0045D770, 2);
    func_00362F60();
}

/* 0x00362E70, 0x58 bytes. */
void func_00362E70(int s, u32 k, int on)
{
    if (on == 0)
        g_0045D770[s] &= ~(u8)(1 << k);
    else
        g_0045D770[s] |= (u8)(1 << k);
}

/* 0x00362ED0, 0x6C bytes. Battlefield `m`'s most generic officers (3 fewer with
 * func_0036D300). */
int func_00362ED0(int m)
{
    int t[30], v, k;

    for (k = 0; k < 30; k++)
        t[k] = g_00415D60[k];
    v = t[m];
    if (func_0036D300() != 0)
        v -= 3;
    return v;
}

/* 0x00362F40, 0x20 bytes, matching. Whether side `s`'s slot `k` is taken out. */
int func_00362F40(int s, u32 k)
{
    return (g_0045D770[s] & 1 << k) != 0;
}

/* 0x00362F60, 0x15C bytes. Takes out generic officers (in a fixed slot order) until the
 * battlefield's limit holds. */
void func_00362F60(void)
{
    u32 t[6], m = func_003623B0(), n = 0, s, k, max;

    for (k = 0; k < 6; k++)
        t[k] = g_00415DE0[k];
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            if (func_003620E0(s, k) < 0x1C)
                n++;
        }
    }
    max = func_00362ED0(m);
    for (k = 0; k < 6; k++) {
        u32 a, b;

        if (n <= max)
            return;
        a = t[k] >> 3;
        b = t[k] & 7;
        if (func_00363770(a, b) != 0 && func_003637D0(a, b) == 0) {
            func_00362E70(a, b, 1);
            n--;
        }
    }
}

/* 0x003630C0, 0x18C bytes, matching. Resets the set-up. */
void func_003630C0(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            func_003620B0(s, k, 0x19F);
            func_003621B0(s, k, 0);
            func_00362220(s, k, 0);
            func_00362840(s, k, 0);
        }
        for (k = 0; k < 2; k++)
            func_003625D0(s, k, 0x1F);
        for (k = 0; k < 6; k++)
            func_00362BD0(s, k, 10);
        func_00362BD0(s, 0, 0);
        func_00362C50(s, 0);
        func_00362CB0(s, 0);
        func_00362630(s, 0);
        func_00362990(s, 0x2F9);
    }
    for (s = 0; s < 2; s++)
        func_003622F0(s, 8);
    func_00362350(0x46);
    func_00362550(0x13);
    func_00362590(5);
    func_00362690(0, 0, 0, 0);
    func_003627C0(0);
    func_00362B40();
    func_00362B90(0x69);
    func_00118850(g_0045D770, 2);
}

/* 0x00363250, 0xC0 bytes. The music for the player's officer kinds 6 and 0xE (by a settings
 * bit), else 0x69. */
int func_00363250(void)
{
    int o;

    if (func_00362570() >= 6 && func_00362570() <= 0xF)
        return 0x69;
    o = func_00363720(0);
    if (o == 0xE)
        return (g_00669D60[0x51] & 0x10) != 0 ? 99 : 0x16;
    if (o == 6)
        return (g_00669D60[0x51] & 0x10) != 0 ? 0x4E : 0x12;
    return 0x69;
}

/* 0x00363310, 0x144 bytes. The music for the map (within its difficulty set). */
int func_00363310(void)
{
    u32 d = 10;
    int m;

    if (func_0036D2E0() != 0)
        d = func_00327C00();
    m = func_00362370();
    if ((m < 0 || m > 0x18) && (m < 0x19 || m > 0x1D)) {
        if (m >= 0x1E && m <= 0x23)
            m -= 0x1E;
        else if (m >= 0x24 && m <= 0x29)
            m -= 0x24;
        else if (m >= 0x2A && m <= 0x31)
            m -= 0x2A;
        else if (m >= 0x32 && m <= 0x37)
            m -= 0x32;
        else if (m >= 0x38 && m <= 0x3F)
            m -= 0x38;
        else if (m > 0x3F && m < 0x46)
            m -= 0x40;
    }
    return func_001E6670(d, (g_00669D60[0x51] & 0x1F) >> 4, m);
}

/* 0x00363460, 0x4C bytes. */
void func_00363460(void)
{
    int v = func_00363250();

    if (v == 0x69)
        v = func_00363310();
    if (v < 0x69)
        func_00362B90(v);
}

/* 0x003634B0, 0xA4 bytes. */
void func_003634B0(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 2; k++) {
            int v = func_0035EBA0(func_00362570(), s, k);

            if (v > 0x3A && v < 0x5A)
                func_003625D0(s, k, func_0036F600(v));
        }
    }
}

/* 0x00363560, 0x24 bytes, matching. */
void func_00363560(void)
{
    func_00363460();
    func_003634B0();
}

/* 0x00363590, 8 bytes, matching. */
void func_00363590(void)
{
}

/* 0x003635A0, 0x50 bytes. */
void func_003635A0(void)
{
    if (func_0032E7B0() != 0)
        return;
    if (g_00669F6C == 1)
        func_00363590();
    else
        func_00363560();
}

/* 0x003635F0, 0x24 bytes. */
int func_003635F0(void)
{
    return func_0035D5B0(func_00362570());
}

/* 0x00363620, 0x64 bytes. */
u32 func_00363620(int s)
{
    u32 v = func_003635F0();

    if (s == 0)
        return v;
    if (s == 1)
        return v == 0;
    return 2;
}

/* 0x00363690, 0x60 bytes. The player at side `s`'s slot `k` (2 for none). */
u32 func_00363690(int s, int k)
{
    u32 p;

    if (s != 0)
        return 2;
    for (p = 0; p < 2; p++) {
        if (k == func_00362320(p))
            return p;
    }
    return 2;
}

/* 0x003636F0, 0x24 bytes. Whether player `p` plays. */
int func_003636F0(int p)
{
    return func_00362320(p) != 8;
}

/* 0x00363720, 0x4C bytes. Player `p`'s officer (0x19F for none). */
int func_00363720(int p)
{
    if (func_003636F0(p) == 0)
        return 0x19F;
    return func_003620E0(0, func_00362320(p));
}

/* 0x00363770, 0x5C bytes. Whether side `s`'s slot `k` has an officer. */
int func_00363770(int s, int k)
{
    func_003620E0(s, k);
    return func_003620E0(s, k) < 0x19F;
}

/* 0x003637D0, 0x24 bytes, matching. Whether a player holds it. */
int func_003637D0(int s, int k)
{
    return func_00363690(s, k) != 2;
}

/* 0x00363800, 0x94 bytes. Whether side `s`'s slot `k` takes part at the start. */
int func_00363800(int s, u32 k)
{
    if (func_00362F40(s, k) != 0)
        return 0;
    if (k >= 6 && k <= 7 && func_00362810() != 0)
        return func_00362730(s, k);
    return func_0035EAE0(func_00362570(), s, k);
}

/* 0x003638A0, 0x24 bytes, matching. */
u32 func_003638A0(void)
{
    return func_0035D6E0(func_003623B0());
}

/* 0x003638D0, 0x104 bytes. Copies the set-up into the settings (players' officers, mode flags,
 * battlefield data, difficulty). */
void func_003638D0(void)
{
    u32 m, a;
    int p;

    for (p = 0; p < 2; p++) {
        u32 k;

        *(int *)(g_00669D60 + p * 0x48 + 0x88) = 0x19F;
        k = func_00362320(p);
        if (k < 8)
            *(int *)(g_00669D60 + p * 0x48 + 0x88) = func_003620E0(0, k);
    }
    if (*(int *)(g_00669D60 + 0xD0) < 0 || *(int *)(g_00669D60 + 0xD0) > 0x19E)
        *(u32 *)(g_00669D60 + 0x200) = (*(u32 *)(g_00669D60 + 0x200) & ~2) | 1;
    else
        *(u32 *)(g_00669D60 + 0x200) = (*(u32 *)(g_00669D60 + 0x200) & ~1) | 2;
    m = func_003623B0();
    a = func_0035D6E0(m);
    *(u32 *)(g_00669D60 + 0x60) = func_0035D730(m);
    *(u32 *)(g_00669D60 + 0x74) = a;
    g_00669D60[0x21] = func_003625B0();
    func_00362F60();
}

/* 0x003639E0, 0x68 bytes. Whether side `s` has `v` among its two +0x65 values. */
int func_003639E0(int s, int v)
{
    u32 k;

    for (k = 0; k < 2; k++) {
        if (v == func_00362600(s, k))
            return 1;
    }
    return 0;
}

/* 0x00363A50, 0x64 bytes. Whether either side has. */
int func_00363A50(int v)
{
    u32 s;

    for (s = 0; s < 2; s++) {
        if (func_003639E0(s, v) != 0)
            return 1;
    }
    return 0;
}

/* 0x00363AC0, 0x70 bytes. */
int func_00363AC0(int s, int v)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 2; k++) {
        if (v == func_00362600(s, k))
            n++;
    }
    return n;
}

/* 0x00363B30, 0x5C bytes. */
int func_00363B30(int v)
{
    int n = 0;
    u32 s;

    for (s = 0; s < 2; s++)
        n += func_00363AC0(s, v);
    return n;
}

/* 0x00363B90, 0x24 bytes. */
u32 func_00363B90(void)
{
    return func_0035D7F0(func_00362370());
}

/* 0x00363BC0, 0x78 bytes. Whether officer `v` is in the battle. */
int func_00363BC0(int v)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            if (v == func_003620E0(s, k))
                return 1;
        }
    }
    return 0;
}

/* 0x00363C40, 0xA0 bytes. Side `s`'s number of officers (slots 6-7 only when `all`). */
int func_00363C40(int s, int all)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 8; k++) {
        if (all != 0 || k < 6 || k > 7) {
            func_003620E0(s, k);
            if (func_003620E0(s, k) < 0x19F)
                n++;
        }
    }
    return n;
}

/* 0x00363CE0, 0x40 bytes, matching. */
void func_00363CE0(void)
{
    u32 k;

    for (k = 0; k < 2; k++)
        func_003625D0(0, k, 0x1F);
}

/* 0x00363D20, 0xFC bytes. Side 1's two +0x65 values from its candidates. */
void func_00363D20(void)
{
    int list[102], t[2];
    u32 n, j = 0, k;

    t[0] = 0x1F;
    t[1] = 0x1F;
    n = func_003154F0(func_0036D500(1), list);
    for (k = 0; k < n; k++) {
        u32 v = func_0036F600(list[k]);

        if (func_0036F6A0(v, j, t, func_00362570()) != 0) {
            t[j++] = v;
            if (j > 1)
                break;
        }
    }
    for (k = 0; k < 2; k++)
        func_003625D0(1, k, t[k]);
}

/* 0x00363E20, 0x24 bytes, matching. */
void func_00363E20(void)
{
    func_00363CE0();
    func_00363D20();
}

/* 0x00363E50, 0x50 bytes. Whether the battle kind is below 6 or above 0x12. */
int func_00363E50(void)
{
    u32 k = func_00362570();

    return !((k > 5 && k < 0x10) || (k > 0xF && k < 0x13));
}

/* 0x00363EA0, 0x178 bytes. Side `s`'s rating (20 per officer, +20 for kind 3 ones, +20 for
 * those of func_0036D3B0, 20 per func_0036D400 one; at most 180). */
u32 func_00363EA0(int s)
{
    int n = 0, k3 = 0, a = 0, b = 0;
    u32 k, v;

    for (k = 0; k < 8; k++) {
        int o = (short)func_003620E0(s, k);

        if (o < 0 || o >= 0x19F || (k >= 6 && k <= 7))
            continue;
        n++;
        if (func_0036D2E0() != 0) {
            if (func_002F3DC0(o) == 3)
                k3++;
            if (func_0036D3B0(o) != 0)
                a++;
            if (func_0036D400(o) != 0)
                b++;
        }
    }
    v = n * 0x14 + (k3 != 0 ? 0x14 : 0) + (a != 0 ? 0x14 : 0) + b * 0x14;
    if (v > 0xB4)
        v = 0xB4;
    return v;
}
