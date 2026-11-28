/*
 * sound_front.c - the game's sound front end between 0x0023A160 and 0x0023AE2C: voices and
 * streamed sounds from the sound table file (0x0074B7D8: a count, then five words per sound),
 * two stream buffers in IOP memory (0x0074B7EC, switched by 0x0074B7F4), the effects banks
 * table (0x0040E9E0, nine words per sound group) and the volumes. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#ifndef SW2E_PC
/* The original code here sees func_00117C90 as returning an int: it does not mask the result
 * (which the function itself masks to a byte). */
#define SW2E_OWN_PROTO_func_00117C90
int func_00117C90(int a);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_00117280   /* the original callers here see it this way */
void func_00117280(int, int, unsigned int, int, int, int, int);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_00117360   /* the original callers here see it this way */
void func_00117360(int, int, unsigned int, int);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_00117410   /* the original callers here see it this way */
void func_00117410(int, int, unsigned int, int, int, int, int);
#endif
#define SW2E_FILE_SOUND_FRONT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#ifdef SW2E_PC
extern ps2ptr g_0074B7D8_a;                  /* the sound table */
#define g_0074B7D8 ((int *)PS2_PTR(g_0074B7D8_a))
#define g_0074B7D8_SET(v) (g_0074B7D8_a = PS2_ADDR(v))
#else
extern int *g_0074B7D8;
#define g_0074B7D8_a (*(ps2ptr *)&g_0074B7D8)
#define g_0074B7D8_SET(v) (g_0074B7D8 = (v))
#endif
extern int g_0074B7EC[2];                /* the two stream buffers */
extern u32 g_0074B7F4;                   /* the one in use */
extern int g_0074B7D4, g_0074B7E8;
extern int g_0045D4C4, g_0045D4C8, g_0045D4CC;   /* (small data) */
extern u8 g_00669D60[];                  /* settings: +0x53, +0x54 volumes */
extern int g_00500474;
#ifdef SW2E_PC
extern ps2ptr g_00500478_a;
#define g_00500478 ((u8 *)PS2_PTR(g_00500478_a))
#define g_00500478_SET(v) (g_00500478_a = PS2_ADDR(v))
#else
extern u8 *g_00500478;
#define g_00500478_a (*(ps2ptr *)&g_00500478)
#define g_00500478_SET(v) (g_00500478 = (v))
#endif
extern int g_0040E9E0[][9];              /* the effects banks */
extern int g_0043D010[0xB], g_0043D040[0xB];
extern char g_0043D070[];

void func_002A7840(void);

void func_0023AA60(int k, u32 dst, int a);
void func_0023AB00(int k, int a);
void func_0023AB70(u32 v);

/* 0x0023A160, 8 bytes, matching. */
int func_0023A160(void)
{
    return g_0045D4C4;
}

/* 0x0023A170, 8 bytes, matching. */
void func_0023A170(int v)
{
    g_0045D4C4 = v;
}

/* 0x0023A180, 0xE0 bytes. Plays sound `k` on channel `ch` (some voices lower the music). */
void func_0023A180(int k, int ch, int off)
{
    int *e, v;

    if (k >= *g_0074B7D8 || ch >= 4)
        return;
    e = g_0074B7D8 + k * 5 + 2;
    if (k > 0x1E61 && k < 0x1E71) {
        func_0023AB70(g_00669D60[0x53]);
        func_0023A170(1);
    }
    v = g_00500474 == 0 ? 0 : *(int *)(g_00500478 + 0x348);
    func_00117D00((unsigned int *)(e), ch, v, 0, off + func_00117DE0(), 0);
}

/* 0x0023A260, 0x24 bytes, matching. Whether channel 0 is playing. */
int func_0023A260(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A290, 0x58 bytes, matching. */
void func_0023A290(int k)
{
    if (func_00102960(0) != 0 && k < 0xA6) {
        func_0023AB00(k, 1);
        func_0023A180(k, 0, 0);
    }
}

/* 0x0023A2F0, 0xDC bytes. Plays streamed sound `a` and preloads `b` in the other buffer. */
int func_0023A2F0(int a, int b, int big)
{
    int lim = big == 0 ? 0xEC : 0x1478;

    if (func_00102960(0) == 0)
        return 0;
    if (a < lim) {
        func_0023A180(a + 0xA6, 0, g_0074B7EC[g_0074B7F4] - func_00117DE0());
        g_0074B7F4 = g_0074B7F4 == 0;
    }
    if (b < lim) {
        func_0023AA60(b + 0xA6, g_0074B7EC[g_0074B7F4], 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A3D0, 0x40 bytes. */
void func_0023A3D0(void)
{
    g_0074B7EC[0] = func_00117DE0();
    g_0074B7EC[1] = g_0074B7EC[0] + 0x28000;
    g_0074B7F4 = 0;
}

/* 0x0023A410, 0x68 bytes, matching. Whether the voice still plays (stopped after 750 ticks). */
int func_0023A410(void)
{
    int r = func_00117C90(0) == 1;

    if (r && (u32)(func_001020C0() - g_0045D4C8) > 0x2EE) {
        g_0045D4CC = 1;
        r = 0;
        func_00117CE0(0);
    }
    return r;
}

/* 0x0023A480, 0x6C bytes. Plays voice `k`. */
int func_0023A480(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xDF8) {
        func_0023A180(k + 0x199, 0, 0);
        g_0045D4C8 = func_001020C0();
    }
    return 1;
}

/* 0x0023A4F0, 0x64 bytes. Loads voice `k`. */
int func_0023A4F0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xDF8) {
        func_0023AB00(k + 0x199, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A560, 0x60 bytes. */
int func_0023A560(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 7)
        func_0023A180(k + 0x192, 0, 0);
    return 1;
}

/* 0x0023A5C0, 0x64 bytes. */
int func_0023A5C0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 7) {
        func_0023AB00(k + 0x192, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A630, 0x24 bytes, matching. */
int func_0023A630(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A660, 0x70 bytes. Loads sound `k` into the free stream buffer. */
int func_0023A660(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0x1E62) {
        func_0023AA60(k, g_0074B7EC[g_0074B7F4], 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A6D0, 0x90 bytes. Plays it from there. */
int func_0023A6D0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0x1E62)
        func_0023A180(k, 0, g_0074B7EC[g_0074B7F4] - func_00117DE0());
    g_0074B7F4 = g_0074B7F4 == 0;
    return 1;
}

/* 0x0023A760, 0x64 bytes. */
int func_0023A760(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xF) {
        func_0023AB00(k + 0x1E62, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A7D0, 0x60 bytes. */
int func_0023A7D0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xF)
        func_0023A180(k + 0x1E62, 0, 0);
    return 1;
}

/* 0x0023A830, 0x24 bytes, matching. */
int func_0023A830(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A860, 0x48 bytes, matching. Puts the music volume back once the voice is over. */
void func_0023A860(void)
{
    if (func_0023A830() == 0 && func_0023A160() != 0) {
        func_0023AB70(g_00669D60[0x54]);
        func_0023A170(0);
    }
}

/* 0x0023A8B0, 0x4C bytes. */
int func_0023A8B0(int k)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023A180(k, 0, 0);
    return r != 0;
}

/* 0x0023A900, 0x54 bytes. */
int func_0023A900(int k, int a)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023AB00(k, a);
    return r != 0;
}

/* 0x0023A960, 0x4C bytes, matching. */
void func_0023A960(int k)
{
    if (func_00102960(0) != 0 && k < 7)
        func_0023A180(k + 0x192, 0, 0);
}

/* 0x0023A9B0, 0x54 bytes. */
int func_0023A9B0(int k, int a)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023AB00(k + 0x192, a);
    return r != 0;
}

/* 0x0023AA10, 0x24 bytes, matching. Stops channel `ch`. */
void func_0023AA10(int ch)
{
    if (ch < 4)
        func_00117CE0(ch);
}

/* 0x0023AA40, 0x1C bytes, matching. */
void func_0023AA40(void)
{
    func_00117CC0();
}

/* 0x0023AA60, 0x9C bytes. Loads sound `k` to IOP address `dst` (0: the default buffer). */
void func_0023AA60(int k, u32 dst, int a)
{
    int *t = g_0074B7D8;

    if (k >= *t)
        return;
    if (dst == 0)
        dst = func_00117DE0();
    func_001026D0(0, 0x69, (void *)PS2_PTR((dst | 0x80000001)), a, t[k * 5 + 4] << 0xB, t[k * 5 + 3] << 0xB,
                  g_0043D070, 0x284);
}

/* 0x0023AB00, 0x20 bytes, matching. */
void func_0023AB00(int k, int a)
{
    func_0023AA60(k, 0, a);
}

/* 0x0023AB20, 0x44 bytes. Loads the sound table. */
void func_0023AB20(void)
{
    g_0074B7D8_SET(func_001026D0(1, 0x569, 0, 1, 0, 0, g_0043D070, 0x290));
}

/* 0x0023AB70, 0x48 bytes. Sets the music volume (0-15). */
void func_0023AB70(u32 v)
{
    func_00117C70((v & 0xFF) * 0x2CDC / 0xF);
}

/* 0x0023ABC0, 0x74 bytes, matching. The eleven effects groups' volumes and pans. */
void func_0023ABC0(void)
{
    int k;

    for (k = 0; k < 0xB; k++) {
        func_00117A90(k, 100 - g_0043D010[k]);
        func_00117A40(k, g_0043D040[k]);
    }
}

/* 0x0023AC40, 0x2C bytes, matching. */
void func_0023AC40(void)
{
    func_001178A0();
    func_002A7840();
    func_0023ABC0();
}

/* 0x0023AC70, 0x50 bytes, matching. Plays effect `s` (bank by the high byte). */
void func_0023AC70(u32 s, int a, int b, int c, int d)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117280(g[7], g[8], s & 0xFF, a, b, c, d);
}

/* 0x0023ACC0, 0x44 bytes, matching. */
void func_0023ACC0(u32 s, int a)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117360(g[7], g[8], s & 0xFF, a);
}

/* 0x0023AD10, 0x50 bytes, matching. */
void func_0023AD10(u32 s, int a, int b, int c, int d)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117410(g[7], g[8], s & 0xFF, a, b, c, d);
}

/* 0x0023AD60, 0x38 bytes. */
void func_0023AD60(int i)
{
    func_00117650(g_0040E9E0[i][7], g_0040E9E0[i][8]);
}

/* 0x0023ADA0, 0x8C bytes. Frees the battle's effects banks. */
void func_0023ADA0(void)
{
    int k;

    for (k = 0; k < 0xCB; k++) {
        int *e = g_0040E9E0[k];

        if (e[7] > 3 && e[7] < 0xB && e[8] < 0xF) {
            func_00117AE0(e[7], e[8]);
            e[8] = 0xF;
        }
    }
    g_0074B7E8 = 0;
    g_0074B7D4 = 0;
}

/* ---- Effects banks loading (rows of g_0040E9E0: SPU address, IOP address, -, body offset,
 * body size, head offset, head size, group, slot 0xF none), the battle's stage banks and the
 * stage objects' sounds (parts of 0x0023AE30-0x0023BC48). ---- */

extern int g_0074B7D0, g_0074B7E4;       /* IOP and SPU memory cursors */
extern int g_0074B7F8, g_0074B800, g_0074B808, g_0074B810, g_0074B818, g_0074B820;
extern int g_0074B824, g_0074B828, g_0074B82C, g_0074B830;   /* the stage's four banks */
#ifdef SW2E_PC
extern ps2ptr g_0074B834_a;
#define g_0074B834 ((u8 *)PS2_PTR(g_0074B834_a))
#define g_0074B834_SET(v) (g_0074B834_a = PS2_ADDR(v))
#else
extern u8 *g_0074B834;
#define g_0074B834_a (*(ps2ptr *)&g_0074B834)
#define g_0074B834_SET(v) (g_0074B834 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0074B838_a;
#define g_0074B838 ((int *)PS2_PTR(g_0074B838_a))
#define g_0074B838_SET(v) (g_0074B838_a = PS2_ADDR(v))
#else
extern int *g_0074B838;
#define g_0074B838_a (*(ps2ptr *)&g_0074B838)
#define g_0074B838_SET(v) (g_0074B838 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0074B83C_a;
#define g_0074B83C ((u8 *)PS2_PTR(g_0074B83C_a))
#define g_0074B83C_SET(v) (g_0074B83C_a = PS2_ADDR(v))
#else
extern u8 *g_0074B83C;
#define g_0074B83C_a (*(ps2ptr *)&g_0074B83C)
#define g_0074B83C_SET(v) (g_0074B83C = (v))
#endif
extern int g_0074B840, g_0074B844, g_0074B848, g_0074B84C, g_0074B850;
extern int g_0074B854, g_0074B858, g_0074B85C, g_0074B860;
extern u8 g_006A3A30[][0xC0];
#ifdef SW2E_PC
extern ps2ptr g_005BD724_a;
#define g_005BD724 ((u8 *)PS2_PTR(g_005BD724_a))
#define g_005BD724_SET(v) (g_005BD724_a = PS2_ADDR(v))
#else
extern u8 *g_005BD724;
#define g_005BD724_a (*(ps2ptr *)&g_005BD724)
#define g_005BD724_SET(v) (g_005BD724 = (v))
#endif
extern int g_0043D080[];
extern u8 g_0043D0F0[];

#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))

u32 func_002D6B50(void);
void func_002A5D70(u32 idx, u8 *e, int v);

/* 0x0023AE30, 0x11C bytes. Loads bank `k` (head to SPU memory, body to IOP memory). */
void func_0023AE30(int k, int wait)
{
    int *e = g_0040E9E0[k], n = e[4];
    u32 dst = 0;

    if (n != 0) {
        e[1] = g_0074B7D4 + 0x2A800;
        dst = g_0074B7D0 + g_0074B7D4;
        g_0074B7D4 += e[4] * 0x800;
    }
    func_001026D0(1, 0x568, (void *)PS2_PTR((e[0] | 2)), wait, e[6] << 0xB, e[5] << 0xB, g_0043D070, 0x327);
    if (n != 0)
        func_001026D0(1, 0x567, (void *)PS2_PTR((dst | 3)), wait, e[4] << 0xB, (e[3] + 0x55) * 0x800,
                      g_0043D070, 0x32B);
    if (wait != 0)
        func_0023AD60(k);
}

/* 0x0023AF50, 0xC4 bytes. Opens bank `k` (once) and loads it while SPU memory lasts. */
void func_0023AF50(int k, int wait)
{
    int *e = g_0040E9E0[k];

    if (e[8] == 0xF) {
        int r = func_00117B20(e[7], (unsigned int *)(e)), base = g_0074B7E4;

        e[8] = r;
        if (r < 0xF) {
            e[0] = base + g_0074B7E8;
            g_0074B7E8 += e[6];
            if ((u32)(base + g_0074B7E8) < 0x1FE0BF)
                func_0023AE30(k, wait);
        }
    }
}

/* 0x0023B320, 0x9C bytes. */
void func_0023B320(void)
{
    int k;

    for (k = 0; k < 0x8F; k++) {
        u8 *u = (u8 *)PS2_PTR(0x574DE0) + k * 0x630;

        if ((u[0x198] & 2) != 0) {
            func_0016C9B0(u);
            if ((u32)(*(int *)(u + 0x118) - 0x3D) < 3)
                func_00204D20(g_006A3A30[*(short *)(u + 0x178)]);
        }
    }
}

/* 0x0023B3C0, 0x168 bytes. Switches the stage's ambient banks on or off. */
void func_0023B3C0(int on, int all)
{
    int v = on == 0 ? 0 : g_00669D60[0x53] * 0x3FFF / 0xF;

    if (all == 0)
        func_001174F0(g_0040E9E0[2][7], v, 0);
    if (g_0074B824 != 0xCB)
        func_001174F0(g_0040E9E0[g_0074B824][7], v, 0);
    if (g_0074B828 != 0xCB)
        func_001174F0(g_0040E9E0[g_0074B828][7], v, 0);
    if (g_0074B82C != 0xCB)
        func_001174F0(g_0040E9E0[g_0074B82C][7], v, 0);
    if (g_0074B830 != 0xCB)
        func_001174F0(g_0040E9E0[g_0074B830][7], v, 0);
}

/* 0x0023B530, 0x44 bytes. Sets the effects volume (0-15). */
void func_0023B530(u32 v)
{
    func_00117620((v & 0xFF) * 0x3FFF / 0xF);
}

/* 0x0023B580, 0x40 bytes, matching. Starts the sound system. */
void func_0023B580(void)
{
    func_00114FA0(0x32000, 0x59800);
    func_0023B020();
    func_0023AB20();
    func_002A7970();
}

/* 0x0023B5C0, 0x2C bytes. */
void func_0023B5C0(void)
{
    g_0074B820 = 0;
    g_0074B808 = g_0074B7F8;
    g_0074B818 = g_0074B7F8;
    g_0074B810 = g_0074B800;
    g_0074B800 = 0;
    g_0074B7F8 = 0;
}

/* 0x0023B5F0, 0x60 bytes. */
void func_0023B5F0(void)
{
    if (g_0074B834 != 0)
        func_00102EC0(g_0074B834);
    if (g_0074B838 != 0)
        func_00102EC0((unsigned char *)(g_0074B838));
    if (g_0074B83C != 0)
        func_00102EC0(g_0074B83C);
}

/* 0x0023B650, 0x230 bytes. The stage objects' sounds (their kinds 0-4, banks from the stage's
 * four). */
int func_0023B650(void)
{
    u8 *kinds = g_0074B83C, *e = g_0074B834;
    int *out = g_0074B838;
    u32 idx = 0x8F, n = func_002D6B50(), j;

    for (j = 0; j < n; j++, e += 0x10, out++, kinds++) {
        int v, b;

        if (idx > 0xF2)
            return 0;
        func_002D6B60(j, PS2_ADDR(e), (unsigned int *)(out));
        func_002A5D70(idx, e, *out);
        v = *out;
        if (v == 0x60B)
            *kinds = 4;
        else if (v == 0x40F || v == 0x40D || v == 0x409 || v == 0x408 || v == 0x401 || v == 0x400)
            *kinds = 3;
        else if (v == 0x40C || v == 0x40B || v == 0x40A)
            *kinds = 2;
        else if (v == 0x407 || v == 0x405 || v == 0x404)
            *kinds = 1;
        else
            *kinds = 0;
        b = *out >> 8;
        if (b == 7)
            b = g_0074B830;
        else if (b == 6)
            b = g_0074B82C;
        else if (b == 5)
            b = g_0074B828;
        else if (b == 4)
            b = g_0074B824;
        idx++;
        *out = b * 0x100 + (*out & 0xFF);
    }
    return 1;
}

/* 0x0023B8A0, 0x178 bytes. Loads the stage's banks and its objects' sounds. */
void func_0023B8A0(void)
{
    u32 v, n;

    if ((GAME_FLAGS & 4) != 0)
        v = 0x1C;
    else if ((GAME_FLAGS & 8) != 0)
        v = 0x1B;
    else
        v = *(u16 *)(g_005BD724 + 2);
    g_0074B828 = v + 0x7E;
    g_0074B830 = v + 0xB0;
    g_0074B824 = g_0043D080[v];
    g_0074B82C = g_0043D0F0[v];
    if (g_0074B824 != 0xCB)
        func_0023AF50(g_0074B824, 1);
    func_0023AF50(g_0074B828, 1);
    if (g_0074B82C != 0xCB)
        func_0023AF50(g_0074B82C, 1);
    func_0023AF50(g_0074B830, 1);
    g_0074B850 = 0;
    g_0074B848 = 0xFF;
    g_0074B844 = 0xFF;
    g_0074B84C = 0;
    g_0074B858 = 0xFF;
    g_0074B854 = 0xFF;
    g_0074B860 = 0;
    g_0074B85C = 0;
    g_0074B834_SET(0);
    g_0074B838_SET(0);
    g_0074B83C_SET(0);
    if ((GAME_FLAGS & 4) != 0)
        return;
    n = func_002D6B50();
    if (n > 100)
        n = 100;
    g_0074B840 = n;
    if (n != 0) {
        g_0074B834_SET(func_00102DB0(0x10, n << 4));
        g_0074B838_SET((int *)(func_00102DB0(0x10, n << 2)));
        g_0074B83C_SET(func_00102DB0(0x10, n));
        func_0023B650();
    }
}

/* 0x0023BBE0, 8 bytes, matching. */
void func_0023BBE0(void)
{
}

/* 0x0023BBF0, 0x28 bytes. Officer kind `k`'s voice bank. */
int func_0023BBF0(int k)
{
    return (k < 0 || k > 0x32 ? 0xCB : k + 0x33) - 0x2A;
}

/* 0x0023BC20, 0x28 bytes. */
int func_0023BC20(int k)
{
    return (k < 0 || k > 0x32 ? 0xCB : k + 0x33) - 0x33;
}

void func_0023BC50(void);
void func_0023BA20(void);
void func_0017DF10(void);
void func_0017DE50(void);
void func_002A7560(void);

/* 0x0023BF10, 0x38 bytes. */
void func_0023BF10(void)
{
    g_0074B810 = 0;
    g_0074B808 = 0;
    g_0074B800 = 0;
    g_0074B7F8 = 0;
    g_0074B818 = 0;
    g_0074B820 = 0;
    g_0074B830 = 0xCB;
    g_0074B82C = 0xCB;
    g_0074B828 = 0xCB;
    g_0074B824 = 0xCB;
}

/* 0x0023BF50, 0x44 bytes, matching. Loads the battle's banks. */
void func_0023BF50(void)
{
    func_0023ADA0();
    func_0023BF10();
    func_0023BC50();
    func_0023BBE0();
    func_0023BA20();
    func_0023B8A0();
}

/* 0x0023BFA0, 0x4C bytes, matching. Stops the battle's sounds. */
void func_0023BFA0(void)
{
    func_0017DF10();
    func_0023AC40();
    func_0023AA40();
    func_0023ADA0();
    func_0023B5F0();
    func_002A7870();
    func_00114C90(0);
}

/* 0x0023BFF0, 0x5C bytes. Starts them. */
void func_0023BFF0(void)
{
    func_00114C90(0);
    func_002A78B0();
    func_0023BF50();
    func_0023A3D0();
    func_0017DE50();
    if (func_0032E7B0() == 0)
        func_0035DAA0();
    func_00114E30();
}

/* 0x0023C050, 0x7C bytes. The speaker set-up (3 mono .. 0 surround?). */
void func_0023C050(int k)
{
    if (k == 3)
        func_00114D30(0);
    else if (k == 2)
        func_00114D30(1);
    else if (k == 1)
        func_00114D30(2);
    else if (k == 0)
        func_00114D30(3);
}

/* 0x0023C0D0, 0x24 bytes, matching. */
void func_0023C0D0(void)
{
    func_002A7560();
    func_002A77F0();
}

/* 0x0023C100, 0x1C bytes, matching. */
void func_0023C100(void)
{
    func_0017DDE0();
}

/* 0x0023C120, 0x24 bytes, matching. */
void func_0023C120(void)
{
    func_0023B580();
    func_0017E130();
}

/* 0x0023C150, 8 bytes, matching. */
void func_0023C150(void)
{
}

/* 0x0023C160, 0x24 bytes, matching. */
void func_0023C160(void)
{
    func_0023AC40();
    func_0023ADA0();
}
