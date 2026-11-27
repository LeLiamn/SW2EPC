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
u8 func_00362660(u32 s);
int func_00363800(u32 s, u32 k);
int func_00362260(u32 s, u32 k);
int func_00362160(u32 s, u32 k);
int func_00362F40(u32 s, u32 k);
u32 func_00362570(void);
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

/* 0x0035F920, 0x8C bytes, matching. Each side's count: the sum of its present officers'. */
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
