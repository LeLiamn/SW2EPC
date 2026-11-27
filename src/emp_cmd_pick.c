/*
 * emp_cmd_pick.c - Empire command pieces between 0x00335000 and 0x00336AD4: the officer choice
 * command (block at 0x007B5E70: four records of 7 ints (officer, two kinds, their arguments), +0x70
 * count, +0x74 the chosen one; the command state's +0x69C points at {step, counter, records}), the
 * 0x007B5F00 slots, and helpers picking the best officer of a force or a list (officers are
 * 0..0x19E, 0x19F = none). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"
typedef unsigned long long u64;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
extern u8 g_00500764, g_00500765;
extern u16 g_0050074C, g_0050074E;
extern u32 g_0045D744;                   /* (small data) the highlighted record */
extern char g_007B4E60[];
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;
extern int g_007B5E70[];
extern int g_007B5F00[9][3];
extern int g_007B5F30[];
extern u8 *g_0043C560, *g_0043C578;

#define PAD1_PRESSED() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074C)
#define PAD1_REPEAT() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074E)
#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))

/* The command's block: step, counter, records. */
typedef struct {
    int step;
    int count;
    int *recs;
} PickCmd;

#define PROVINCE_OK_F(p) ((p) >= 0 && (p) < func_0030AB90())
#define PICK() (*(PickCmd **)((u8 *)func_002FC2C0() + 0x69C))
#define REC_COUNT(r) ((r)[0x1C])
#define REC_CHOSEN(r) ((r)[0x1D])

int func_00327D50(void);
void func_002FD490(void);
int func_002F7D90(int a, int fn, int b, int c, int d, int e);
void func_002F82A0(void);
void func_002F8160(void);
void func_002F8340(void);
int *func_002F7B10(void);
void func_002F7C40(int *l, int n);
u32 func_00327870(void);
int func_002F3EC0(u32 o);
int func_0030CB50(int chance);
void func_00304DE0(int *rec, int o, int a);
void func_003DC180(int k, int a, int *out);
void func_002C7310(int x, int y, int a, int w, int h, int c, int d);
void func_002C7A30(int x, int y, int a, int w, int h, int c, int d);
void func_00382690(int x, int y, int a, int w, int h, int b, int o);
char *func_002F2890(int o);
void func_00146B40(char *t, int x, int y, int w, int h, int a, int b);
void func_003B5820(int k, int x, int y, int a, int c, int d, int p6);
u8 *func_002FC2C0(void);
int func_0030D7D0(void);
void func_00334A90(char *out, u32 k, int a, int b);
void func_0037E920(int c, int k, int x, int y, int a, char *t, int b);
int func_00313DB0(int k, int o);
void func_00383050(int c, int x, int y, int a, int b, int v);
void func_001A7DC0(u8 *t, int a, int b);
u32 func_003276A0(void);
void func_002FCF20(void);
void func_003DC090(int k, int *box);
void func_003DC0E0(int k, int a, int b);
int func_003DC2D0(int k);
void func_0023AD10(int a, int b, int c, int d, int e);
int func_003760C0(void);
int func_003760E0(void);
void func_00376100(int a, int b, int c);
int func_0030E1F0(void);
void func_002F4360(u32 o, int v);
void func_002F4510(u32 o, int v);
void func_002F4760(u32 o, int v);
void func_002F4610(u32 o);
int func_002F8F20(int o);
void func_0030E140(int k, int a, int b, int c);
void func_0030E100(void);
void func_002FB320(int o, int *out);
void func_00315510(int *out, int o);
void func_0031BD90(int *rec);
int func_003280E0(void);
void func_003280C0(int v);
void func_0039F960(void);
void func_002FC560(void);
int func_0030D560(int a);
void func_002F44C0(int o);
void func_002F43C0(u32 o, int v);
int func_002F3770(u32 o);
int func_002F34E0(u32 o);
int func_002FB040(int f, int *out);
int func_0030AB90(void);
int func_002FAFA0(int a, int b);
int func_002F4080(u32 o);
int func_002F8CB0(int p);
int func_002FB2A0(void);
int func_002F3E30(u32 o);
int func_002F3E70(u32 o);
u32 func_002F4DD0(u32 o);

/* 0x00335000, 0x50 bytes, matching. Clears the records. */
void func_00335000(int *r)
{
    int k;

    REC_COUNT(r) = 0;
    REC_CHOSEN(r) = 4;
    for (k = 0; k < 4; k++, r += 7) {
        r[0] = 0x19F;
        r[1] = 100;
        r[3] = -1;
        r[5] = -1;
        r[2] = 100;
        r[4] = -1;
        r[6] = -1;
    }
}

/* 0x00335050, 0xC bytes, matching. */
int *func_00335050(void)
{
    return &g_007B5E70[0x1E];
}

/* 0x00335060, 0x30 bytes. */
void func_00335060(PickCmd *c)
{
    c->step = 0;
    c->count = 0;
    c->recs = g_007B5E70;
    func_00335000(g_007B5E70);
}

/* 0x00335090, 0x268 bytes. Fills the records: maybe the player's officer, then up to four of the
 * force's officers. */
void func_00335090(int *r)
{
    int f = func_00327D50(), n, k;
    int *l;
    int list[4];
    u32 c;

    func_00335000(r);
    func_002FD490();
    n = func_002F7D90(0, (int)func_002F82A0, f, 0, 1, 0);
    l = func_002F7B10();
    func_002F7C40(l, n);
    c = func_00327870();
    if (c < 0x19F && func_002F3EC0(c) == 0)
        c = 0x19F;
    REC_COUNT(r) = 0;
    if (c < 0x19F && func_0030CB50(0x32) != 0) {
        list[0] = c;
        REC_COUNT(r)++;
    }
    for (k = 0; k < n; k++, l++) {
        if (REC_COUNT(r) == 0 || list[0] != *l) {
            list[REC_COUNT(r)] = *l;
            if (++REC_COUNT(r) > 3)
                break;
        }
    }
    for (k = 0; k < REC_COUNT(r); k++)
        func_00304DE0(r + k * 7, list[k], 1);
}

/* 0x00335300, 0x1C4 bytes. Draws record `i`: frame, portrait, name and the two kind icons. */
void func_00335300(int c, int o, int k1, int k2, int i, int sel)
{
    int box[4], k, x;
    int y = i * 0x3C;

    func_003DC180(2, i, box);
    if (sel == 0)
        func_002C7310(box[0], y + 0x58, 0, 0xC0, 0x38, 0x80, 1);
    else
        func_002C7A30(box[0], y + 0x58, 0, 0xC0, 0x38, 0x80, 1);
    func_00382690(box[0] + 0xE, y + 0x5D, 0, 0x28, 0x2E, 1, o);
    FONT_COLOUR(6);
    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    func_00146B40(func_002F2890(o), box[0] + 0x3C, y + 0x5D, 0x7A, 0x10, 1, 0);
    g_0056CCC0 = 16.0f;
    g_0056CCC4 = 16.0f;
    FONT_COLOUR(5);
    for (k = 0, x = 0x44; k < 2; k++, x += 0x28)
        func_003B5820(k == 1 ? k2 : k1, box[0] + x, y + 0x73, 0, 0x80, 1, ARG_UNKNOWN);
}

/* 0x003354D0, 0x1F8 bytes. Draws the records and the highlighted one's two texts and cost. */
void func_003354D0(void)
{
    int *r = PICK()->recs, *s = 0, *p;
    int box[4], k, a, b;

    func_003DC180(3, 0, box);
    for (k = 0, p = r; k < REC_COUNT(r); k++, p += 7) {
        int sel = k == (int)g_0045D744;

        if (sel)
            s = p;
        func_00335300(func_0030D7D0(), p[0], p[1], p[2], k, sel);
    }
    if (s != 0) {
        func_00334A90(g_007B4E60, s[1], s[3], s[5]);
        func_0037E920(func_0030D7D0(), s[1], box[0], 0x68, 0x80, g_007B4E60, 1);
        func_00334A90(g_007B4E60, s[2], s[4], s[6]);
        func_0037E920(func_0030D7D0(), s[2], box[0] + 0x9C, 0x68, 0x80, g_007B4E60, 1);
        a = func_00313DB0(s[1], func_00327D50());
        if (a < 0)
            a = 0;
        b = func_00313DB0(s[2], func_00327D50());
        if (b < 0)
            b = 0;
        func_00383050(func_0030D7D0(), 0x141, 0x34, 0, 1, a + b);
        if (REC_COUNT(r) < 2)
            func_001A7DC0(g_0043C560, 0x80, 1);
        else
            func_001A7DC0(g_0043C578, 0x80, 1);
    }
}

/* 0x003356D0, 0xF8 bytes. Step 0: fills the records with a fixed seed and opens the windows. */
void func_003356D0(void)
{
    PickCmd *c = PICK();
    u32 seed = g_7000015C;
    int *r = c->recs;
    int b1[5], b2[5];

    g_7000015C = func_003276A0() | 1;
    func_002FCF20();
    func_00335090(r);
    g_0045D744 = 0;
    c->step = 1;
    b1[1] = 0x58;
    b1[0] = 0;
    b1[2] = 0xC0;
    b1[3] = 0x38;
    b1[4] = 0x80;
    func_003DC090(2, b1);
    func_003DC0E0(2, 1, REC_COUNT(r));
    b2[0] = 0xC0;
    b2[1] = 0x68;
    b2[2] = 0x1CC;
    b2[3] = 0xD8;
    b2[4] = 0x80;
    func_003DC090(3, b2);
    func_003DC0E0(3, 2, 1);
    g_7000015C = seed | 1;
}

/* 0x003357D0, 0x23C bytes. The list input: 1 chosen, 0 cancelled, 2 still choosing. */
int func_003357D0(void)
{
    int *r = PICK()->recs;
    int n;
    u32 pr, rp;

    if (func_003DC2D0(2) != 0 || func_003DC2D0(3) != 0)
        return 2;
    n = REC_COUNT(r);
    pr = PAD1_PRESSED();
    rp = PAD1_REPEAT();
    if (pr & 0x40) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        return 1;
    }
    if (pr & 0x10) {
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        return 0;
    }
    if (n < 2)
        return 2;
    if (rp & 0x4000) {
        if ((int)g_0045D744 < n - 1) {
            g_0045D744++;
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
        } else if (pr & 0x4000) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_0045D744 = 0;
        }
    } else if (rp & 0x1000) {
        if ((int)g_0045D744 < 1) {
            if (pr & 0x1000) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                g_0045D744 = (n - 1) & 0xFF;
            }
        } else {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_0045D744--;
        }
    }
    return 2;
}

/* 0x00335A10, 0x8C bytes, matching. Step 1. */
void func_00335A10(void)
{
    PickCmd *c = PICK();
    int *r = c->recs;
    int a = func_003357D0();

    if (a == 1) {
        func_00376100(func_003760C0(), func_003760E0(), -1);
        REC_CHOSEN(r) = g_0045D744;
        c->step = 2;
    } else if (a == 0) {
        c->step = 4;
    }
}

/* 0x00335AA0, 0x1FC bytes. Step 2: the chosen officer gets the post, the others are released. */
void func_00335AA0(void)
{
    PickCmd *c = PICK();
    int *r = c->recs, *p;
    u32 k;
    int o, buf[0x18];

    if (REC_CHOSEN(r) < REC_COUNT(r)) {
        if (func_0030E1F0() == 0) {
            for (k = 0, p = r; (int)k < REC_COUNT(r); k++, p += 7) {
                if ((u32)p[0] < 0x19F) {
                    if (k == (u32)REC_CHOSEN(r)) {
                        func_002F4360(p[0], 1);
                        func_002F4510(p[0], 0);
                        func_002F4760(p[0], 0x14);
                    } else {
                        func_002F4610(p[0]);
                    }
                }
            }
            o = r[REC_CHOSEN(r) * 7];
            if (func_0030CB50(0x46) == 0)
                func_0030E140(0x1B, o, func_002F8F20(func_00327D50()), -1);
            else
                func_0030E140(0x1C, o, func_002F8F20(func_00327D50()), -1);
            return;
        }
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_002FB320(func_00327D50(), buf);
            c->step = 3;
            return;
        }
    } else {
        for (k = 0, p = r; (int)k < REC_COUNT(r); k++, p += 7) {
            if ((u32)p[0] < 0x19F)
                func_002F4610(p[0]);
        }
    }
    c->step = 4;
}

/* 0x00335CA0, 0xBC bytes. Step 3: applies the chosen record's two effects, then ends. */
void func_00335CA0(void)
{
    PickCmd *c = PICK();
    int *r = c->recs;
    int e[0x19C], *q;

    if (c->count < 2) {
        func_00315510(e, func_00327D50());
        q = r + r[0x1D] * 7 + c->count;
        e[1] = q[1];
        e[2] = q[3];
        e[3] = q[5];
        func_0031BD90(e);
        c->count++;
    } else {
        func_003280C0(func_003280E0() - 1);
        func_0039F960();
        c->step = 4;
    }
}

/* 0x00335D60, 0x38 bytes, matching. Step 4: resets the block and leaves. */
void func_00335D60(void)
{
    int *s = (int *)func_002FC2C0();

    func_00335060((PickCmd *)s[0x1A7]);
    func_002FC560();
    s[0] = 0;
}

/* 0x00335DA0, 0x40 bytes. Draw. */
void func_00335DA0(void)
{
    if (PICK()->step == 1)
        func_003354D0();
}

/* 0x00335DE0, 0xB0 bytes. Update. */
int func_00335DE0(void)
{
    int s = PICK()->step;

    if (s == 4)
        func_00335D60();
    else if (s == 3)
        func_00335CA0();
    else if (s == 2)
        func_00335AA0();
    else if (s == 1)
        func_00335A10();
    else if (s == 0)
        func_003356D0();
    return 5;
}

/* 0x00335E90, 0x4C bytes. Clears the nine slots. */
void func_00335E90(void)
{
    int k;

    for (k = 0; k < 9; k++) {
        g_007B5F00[k][0] = -1;
        g_007B5F00[k][1] = -1;
        g_007B5F00[k][2] = -1;
    }
}

/* 0x00335EE0, 0xC bytes, matching. */
int *func_00335EE0(void)
{
    return g_007B5F30;
}

/* 0x00335EF0, 0x24 bytes, matching. */
void func_00335EF0(int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    func_00335E90();
}

/* 0x00335F20, 0x98 bytes. */
int func_00335F20(int k)
{
    int v;

    if (k == 3)
        return 5;
    if (k == 2) {
        v = 1;
        if (func_0030D560(1) != 0)
            v = 3;
        return v;
    }
    if (k == 1)
        return 4;
    if (k != 0)
        return -1;
    v = 0;
    if (func_0030D560(1) != 0)
        v = 2;
    return v;
}

/* 0x00335FC0, 0x80 bytes. */
void func_00335FC0(void)
{
    int n = func_002F7D90(0, (int)func_002F8160, func_00327D50(), 0, 1, 0);
    int *l = func_002F7B10(), k;

    for (k = 0; k < n; k++, l++)
        func_002F44C0(*l);
}

/* 0x00336040, 0x64 bytes. */
void func_00336040(u32 *l)
{
    int k;

    for (k = 0; k < 9; k++, l++) {
        if (*l < 0x19F)
            func_002F43C0(*l, 0);
    }
}

/* 0x003360B0, 0x174 bytes. Force `f`'s best officer: the first 0x2B first, then by 0x002F3770 and
 * 0x002F34E0, ties at random. */
u32 func_003360B0(int f)
{
    u32 *l = (u32 *)func_002F7B10(), best = 0x19F;
    int n = func_002F7D90(0, (int)func_002F8160, f, 0, 1, 0);
    int top = 0, a = 0, b = 0, k;

    for (k = 0; k < n; k++, l++) {
        u32 o = *l;
        int va = func_002F3770(o), vb = func_002F34E0(o), t = (int)o < 0x2B;

        if (best < 0x19F && t <= top) {
            if (t == top) {
                if (a < va) {
                    b = vb;
                    a = va;
                    best = o;
                } else if (va == a) {
                    if (b < vb) {
                        b = vb;
                        best = o;
                    } else if (vb == b && func_0030CB50(0x32) != 0) {
                        best = o;
                    }
                }
            }
        } else {
            b = vb;
            a = va;
            best = o;
            top = t;
        }
    }
    return best;
}

/* 0x00336230, 0x164 bytes. The same among other officers of `f`, skipping `skip`. */
u32 func_00336230(int f, u32 skip)
{
    u32 *l = (u32 *)func_002F7B10(), best = 0x19F;
    int n = func_002F7D90(0, (int)func_002F8340, f, 0, 0, 0);
    int a = 0, b = 0, k;

    if (n == 0)
        return best;
    for (k = 0; k < n; k++, l++) {
        u32 o = *l;
        int va, vb;

        if (o == skip)
            continue;
        va = func_002F3770(o);
        vb = func_002F34E0(o);
        if (best < 0x19F && va <= a) {
            if (va == a) {
                if (b < vb) {
                    b = vb;
                    best = o;
                } else if (vb == b && func_0030CB50(0x32) != 0) {
                    best = o;
                }
            }
        } else {
            b = vb;
            a = va;
            best = o;
        }
    }
    return best;
}

/* 0x003363A0, 0xAC bytes. The better of two officers. */
u32 func_003363A0(u32 a, u32 b)
{
    if (a < 0x19F && b < 0x19F) {
        if (func_002F3770(a) < func_002F3770(b))
            return b;
        return a;
    }
    return b;
}

/* 0x00336450, 0x108 bytes. The best officer among `f`'s allies (not `x`, not the player, at peace
 * with neither). */
u32 func_00336450(int f, int x)
{
    int me = func_00327D50(), l[0x1C];
    int n = func_002FB040(f, l), k;
    u32 best = 0x19F;

    for (k = 0; k < n; k++) {
        if (x != l[k] && me != l[k]) {
            if ((!(x >= 0 && x < func_0030AB90()) || func_002FAFA0(x, l[k]) == 0)
                && func_002FAFA0(me, l[k]) == 0)
                best = func_003363A0(best, func_003360B0(l[k]));
        }
    }
    return best;
}

/* 0x00336560, 0x160 bytes. The same with officer `o`'s province rule, skipping `o`. */
u32 func_00336560(int f, int x, u32 o)
{
    int me = func_00327D50(), l[0x1C];
    int p = 0x19, n, k;
    u32 best = 0x19F;

    if (o < 0x19F)
        p = func_002F4080(o);
    n = func_002FB040(f, l);
    for (k = 0; k < n; k++) {
        if (x != l[k] && me != l[k]) {
            if ((!(x >= 0 && x < func_0030AB90()) || func_002FAFA0(x, l[k]) == 0)
                && func_002FAFA0(me, l[k]) == 0
                && (func_002F8CB0(p) == 0 || p == l[k]))
                best = func_003363A0(best, func_00336230(l[k], o));
        }
    }
    return best;
}

/* 0x003366C0, 0x2B8 bytes. The best of `n` officers from `l` not in `used` (9), with filters;
 * `want` wins at once. Ties by a key (none, player's, first 0x2B, 0x002F34E0, 0x002F4DD0). */
u32 func_003366C0(int f, int must, int free, u32 *l, int n, u32 *used, u32 want)
{
    u32 me = 0x19F, best = 0x19F;
    int a = 0, k, i;

    if (func_002FB2A0() != 0)
        me = func_00327870();
    for (k = 0; k < n; k++, l++) {
        u32 o = *l;
        int v;

        if (must == 1 && func_002F3E30(o) != 1)
            continue;
        if (free != 0 && func_002F3E70(o) != 0)
            continue;
        for (i = 0; i < 9; i++) {
            if (o == used[i])
                break;
        }
        if (i <= 8)
            continue;
        if (free == 0 && want < 0x19F && o == want)
            return o;
        v = func_002F3770(o);
        if (best < 0x19F && v <= a) {
            if (v == a) {
                u64 kb = (best == 0x19F ? 0xFFFFFFFF80000000ULL : 0)
                    | (best == me ? 0x40000000 : 0) | ((int)best < 0x2B ? 0x20000000 : 0)
                    | (u64)(long long)(func_002F34E0(best) << 8) | func_002F4DD0(best);
                u64 ko = (o == 0x19F ? 0xFFFFFFFF80000000ULL : 0)
                    | (o == me ? 0x40000000 : 0) | ((int)o < 0x2B ? 0x20000000 : 0)
                    | (u64)(long long)(func_002F34E0(o) << 8) | func_002F4DD0(o);

                if (kb < ko || (ko == kb && func_0030CB50(0x32) != 0))
                    best = o;
            }
        } else {
            a = v;
            best = o;
        }
    }
    return best;
}

/* 0x00336980, 0x158 bytes. Sorts officers (up to the first none), best first (free ones +10000). */
void func_00336980(u32 *l, int n)
{
    int k, i, v, w;

    for (k = 0; k < n; k++) {
        u32 o = l[k];

        if (o > 0x19E)
            return;
        v = func_002F3770(o) + (func_002F3E70(o) == 0 ? 0 : 10000);
        for (i = k + 1; i < n; i++) {
            u32 q = l[i];

            if (q > 0x19E)
                break;
            w = func_002F3770(q) + (func_002F3E70(q) == 0 ? 0 : 10000);
            if (v < w) {
                l[k] = q;
                l[i] = o;
                v = w;
                o = q;
            }
        }
    }
}

/* ---- Battle line-ups: 9 officer slots (0-2 and 3-5 two groups, 6 and 7 extra ones), filled from
 * a province's officers and the force's free ones (0x00323CD0 lists them). ---- */

u32 func_002F9260(int f);
int func_00323CD0(int a, int f, int p, int *l);
void func_002F80C0(void);
void func_002F8110(void);

/* 0x00336AE0, 0x4F0 bytes. The defenders of province `p` (force `f`); the lord of `me` is moved
 * out of the first slot. */
void func_00336AE0(int f, int p, int me, u32 *s)
{
    u32 lord = func_002F9260(me), o;
    int n1, n2, k, cnt, *l;
    u32 *src;

    func_002F7B10();
    for (k = 0; k < 9; k++)
        s[k] = 0x19F;
    n1 = func_002F7D90(0, (int)func_002F80C0, p, 0, 1, 0);
    src = (u32 *)func_002F7B10();
    for (k = 0; k < n1; k++)
        s[k] = src[k];
    n2 = func_002F7D90(0, (int)func_002F8110, p, 0, 0, 0);
    src = (u32 *)func_002F7B10();
    for (k = 0; k < n2; k++)
        s[3 + k] = src[k];
    if (n1 < 3 || n2 < 3) {
        l = func_002F7B10();
        cnt = func_00323CD0(1, f, p, l);
        for (k = n1; k < 3; k++) {
            o = func_003366C0(f, 2, 0, (u32 *)l, cnt, s, lord);
            if (o < 0x19F)
                s[n1++] = o;
        }
        for (k = n2; k < 3; k++) {
            o = func_003366C0(f, 1, 0, (u32 *)l, cnt, s, lord);
            if (o < 0x19F)
                s[3 + n2++] = o;
        }
        o = func_003366C0(f, 2, 1, (u32 *)l, cnt, s, lord);
        if (o < 0x19F)
            s[6] = o;
        o = func_003366C0(f, 1, 1, (u32 *)l, cnt, s, lord);
        if (o < 0x19F)
            s[7] = o;
    }
    if (n1 > 1)
        func_00336980(s, n1);
    if (n2 > 1)
        func_00336980(s + 3, n2);
    if (s[0] > 0x19E) {
        s[0] = s[3];
        s[3] = 0x19F;
    }
    if (lord < 0x19F && lord == s[0]) {
        for (k = 1; k < 6; k++) {
            if (s[k] < 0x19F) {
                s[0] = s[k];
                s[k] = lord;
                return;
            }
        }
    }
}

/* 0x00336FD0, 0x254 bytes. The attackers of force `f` toward province `p`. */
void func_00336FD0(int f, int p, int me, u32 *s)
{
    u32 lord = func_002F9260(me), o;
    int *l = func_002F7B10(), cnt, n1, n2;

    for (n1 = 0; n1 < 9; n1++)
        s[n1] = 0x19F;
    cnt = func_00323CD0(0, f, p, l);
    for (n1 = 0; n1 < 3; n1++) {
        o = func_003366C0(f, 2, 0, (u32 *)l, cnt, s, lord);
        if (o > 0x19E)
            break;
        s[n1] = o;
    }
    for (n2 = 0; n2 < 3; n2++) {
        o = func_003366C0(f, 1, 0, (u32 *)l, cnt, s, lord);
        if (o > 0x19E)
            break;
        s[3 + n2] = o;
    }
    o = func_003366C0(f, 2, 1, (u32 *)l, cnt, s, 0x19F);
    if (o < 0x19F)
        s[6] = o;
    o = func_003366C0(f, 1, 1, (u32 *)l, cnt, s, 0x19F);
    if (o < 0x19F)
        s[7] = o;
    if (n1 > 1)
        func_00336980(s, n1);
    if (n2 > 1)
        func_00336980(s + 3, n2);
    if (lord < 0x19F && lord == s[0] && n1 > 1) {
        s[0] = s[1];
        s[1] = lord;
    }
}

void func_0030D010(int side, u32 *s, int n);
void func_00323840(int p);
void func_0030D120(int p, int v);
int func_0030AFF0(int p);
int func_003238D0(int p);
int func_00329220(void);
int func_002F5CC0(u32 o);
void func_00329090(int k, int a, int b);
int func_00327C40(void);
void func_00362590(int a);
int func_002FA5A0(int f);
u32 func_0030D0C0(int side);
void func_0030D0A0(int side, u32 o);
u32 func_0030D100(int side);
void func_0030D0E0(int side, u32 o);
void func_00362550(int a);
void func_003622F0(int a, int b);
void func_0030D2B0(void);
int func_002F8E50(int f);
void func_00362990(int side, int v);
void func_00363E20(void);
void func_00364BF0(void);
void func_00327EA0(int v);

/* 0x00337230, 0x36C bytes. Sets up the player's battle: an attack (`att` != 0, from `from` into
 * `p`) or the defence of `p`, with the player's line-up `mine` (9 slots). */
void func_00337230(int att, int from, int p, u32 *mine, int extra)
{
    int me = func_00327D50(), kind, f, ally;
    u32 s[9], o, sub = 0x19F;

    if (att != 0) {
        kind = 4;
    } else {
        kind = 0;
        from = p;
    }
    func_0030D010(0, mine, 9);
    func_00336040(mine);
    func_00323840(p);
    func_0030D120(p, kind);
    f = func_0030AFF0(from);
    if (att == 0 && func_003238D0(from) != 0) {
        func_00329090(func_00329220(), func_002F5CC0(mine[0]), from);
        func_00362590(func_00327C40());
        return;
    }
    ally = func_002FA5A0(me);
    if (PROVINCE_OK_F(ally) && f != ally) {
        if (func_0030D0C0(0) > 0x19E && (sub = func_003360B0(ally)) < 0x19F)
            func_0030D0A0(0, sub);
        if (func_0030D100(0) > 0x19E && (o = func_00336230(ally, sub)) < 0x19F)
            func_0030D0E0(0, o);
    }
    if (att != 0)
        func_00336FD0(f, p, me, s);
    else
        func_00336AE0(f, from, me, s);
    func_0030D010(1, s, 9);
    o = func_00336450(f, ally);
    if (o < 0x19F)
        func_0030D0A0(1, func_003363A0(o, func_0030D0C0(1)));
    o = func_00336560(f, ally, o);
    if (o < 0x19F)
        func_0030D0E0(1, func_003363A0(o, func_0030D100(1)));
    func_00362550(func_00335F20(att));
    func_003622F0(0, 0);
    if (extra != 0)
        func_003622F0(1, 1);
    func_0030D2B0();
    func_00362590(func_00327C40());
    func_00362990(0, func_002F8E50(me));
    func_00362990(1, func_002F8E50(f));
    func_00363E20();
    func_00364BF0();
}

/* 0x003375A0, 0x300 bytes. Sets up a battle between province `a` attacking `b` (mode 2: the
 * player sides with the defender?). */
void func_003375A0(int mode, int a, int b, u32 *mine)
{
    int side = mode != 2, kind = side ? 5 : 1;
    int fa = func_0030AFF0(a), fb = func_0030AFF0(b);
    u32 s[9], o;

    func_00323840(b);
    func_00336FD0(fa, b, fb, s);
    func_0030D010(side, s, 9);
    if (side) {
        o = func_00336450(fa, fb);
        if (o < 0x19F)
            func_0030D0A0(1, func_003363A0(o, func_0030D0C0(1)));
        o = func_00336560(fa, fb, o);
        if (o < 0x19F)
            func_0030D0E0(1, func_003363A0(o, func_0030D100(1)));
    }
    func_00336AE0(fb, b, fa, s);
    func_0030D010(!side, s, 9);
    if (!side) {
        o = func_00336450(fb, fa);
        if (o < 0x19F)
            func_0030D0A0(1, func_003363A0(o, func_0030D0C0(1)));
        o = func_00336560(fb, fa, o);
        if (o < 0x19F)
            func_0030D0E0(1, func_003363A0(o, func_0030D100(1)));
        if (func_002FAFA0(func_00327D50(), fb) != 0)
            func_00327EA0(-3);
    }
    func_00336040(mine);
    func_0030D0A0(0, mine[0]);
    func_0030D120(b, kind);
    func_00362550(func_00335F20(mode));
    func_003622F0(0, 6);
    func_0030D2B0();
    func_00362590(func_00327C40());
    func_00362990(side, func_002F8E50(fa));
    func_00362990(!side, func_002F8E50(fb));
    func_00363E20();
    func_00364BF0();
}

/* ---- The battle command (command state +0x6A0 = {step, a, b}; slots 0x007B5F00). ---- */

#define BCMD() (*(int **)(func_002FC2C0() + 0x6A0))

void func_00373970(int a, int b, int c);
int func_00327C00(void);
int func_00374250(void);
int func_00337D50(int a);
int func_00374E00(void);
void func_00369BB0(int a, int b);
void func_003A99E0(int a);
int func_0036B120(void);
void func_0036B170(int *out);
int func_0036B1E0(void);
int func_0036B1F0(void);
int func_002F27D0(int o);
void func_00335EF0(int *p);
void func_002FC660(void);

/* 0x003378A0, 0x40 bytes, matching. Step 0: opens the province choice. */
void func_003378A0(void)
{
    int *c = BCMD();

    func_00373970(0, 3, func_00327C00());
    c[0] = 1;
}

/* 0x003378E0, 0xC0 bytes, matching. Step 1: the target province. */
void func_003378E0(void)
{
    u8 *st = func_002FC2C0();
    int *c = *(int **)(st + 0x6A0);
    int a;

    func_00327D50();
    a = func_00374250();
    if (a == 1) {
        func_00376100(5, func_00337D50(*(int *)(st + 8)), 0x159);
        g_007B5F00[0][0] = func_00374E00();
        func_00369BB0(*(int *)(st + 8), g_007B5F00[0][0]);
        c[0] = 2;
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_003A99E0(g_007B5F00[0][0]);
    } else if (a == 0) {
        c[0] = 4;
    }
}

/* 0x003379A0, 0x70 bytes, matching. Step 2: the line-up. */
void func_003379A0(void)
{
    int *c = BCMD();
    int a = func_0036B120();

    if (a == 1) {
        func_0036B170(&g_007B5F00[1][0]);
        c[1] = func_0036B1E0();
        c[2] = func_0036B1F0();
        c[0] = 3;
    } else if (a == 0) {
        c[0] = 4;
    }
}

/* 0x00337A10, 0x58 bytes, matching. The officer whose text record is `k`. */
int func_00337A10(int k)
{
    int o;

    for (o = 0; o < 0x19F; o++) {
        if (k == func_002F27D0(o))
            return o;
    }
    return 0x19F;
}

/* 0x00337A70, 0x38 bytes, matching. Step 4: resets and leaves. */
void func_00337A70(void)
{
    int *s = (int *)func_002FC2C0();

    func_00335EF0((int *)s[0x1A8]);
    func_002FC660();
    s[0] = 0;
}

int func_00323C60(int p);
int func_00323BD0(int p);
void func_00329880(int a);
void func_002F9130(int f, int v);
u32 func_003620E0(int side, int k);
void func_00362840(int side, int k, int v);
void func_003638D0(void);
void func_00388710(void);
void func_003A9010(int a);
void func_003A9110(void);
void func_003890B0(int a);
int func_00389050(void);
int func_00389090(void);
void func_0031DBE0(void);
void func_0036A560(void);
void func_00373B60(void);
extern int g_00448050[];

/* 0x00337AB0, 0x274 bytes. Step 3: sets up the chosen battle (kind = command state +8: 0 defence,
 * 1 attack, 2/3 battles between others) and pays its cost. */
void func_00337AB0(void)
{
    u8 *st = func_002FC2C0();
    int t = g_007B5F00[0][0], from = 0x19, to = 0x19, k;
    int *c = *(int **)(st + 0x6A0);
    u32 kind = *(u32 *)(st + 8), lord, o;
    int s[9];

    for (k = 0; k < 9; k++) {
        int v = (&g_007B5F00[1][0])[k];

        s[k] = -1;
        if (v != -1)
            s[k] = v;
    }
    if (kind == 3 || kind == 2) {
        if (PROVINCE_OK_F(func_00323C60(t))) {
            to = func_00323BD0(t);
            from = t;
        } else {
            from = func_00323BD0(t);
            to = t;
        }
    } else if (kind == 1) {
        from = func_00323BD0(t);
        func_00329880(1);
        to = t;
    } else if (kind == 0) {
        func_00329880(0);
        to = t;
        from = 0x19;
    }
    if (kind < 2) {
        func_00335FC0();
        func_00337230(kind, from, to, (u32 *)s, c[2]);
    } else if (kind - 2 < 2) {
        func_003375A0(kind, from, to, (u32 *)s);
    }
    func_002F9130(func_00327D50(), c[1] / 10);
    lord = func_002F9260(func_00327D50());
    if (lord < 0x19F) {
        for (k = 0; k < 8; k++) {
            o = func_003620E0(1, k);
            if (o < 0x19F && o == lord)
                func_00362840(1, k, 1);
        }
    }
    func_003638D0();
    c[0] = 4;
    func_00337A70();
}

/* 0x00337D30, 0x1C bytes, matching. */
void func_00337D30(void)
{
    func_00388710();
}

/* 0x00337D50, 0x5C bytes, matching. The text of battle kind `k`. */
int func_00337D50(int k)
{
    int v = -1;

    switch (k) {
    case 0:
        v = 0xC;
        break;
    case 1:
        v = 0xD;
        break;
    case 2:
        v = 0xE;
        break;
    case 3:
        v = 0xF;
        break;
    case 4:
        v = 10;
        break;
    case 5:
        v = 0xB;
        break;
    }
    return v;
}

/* 0x00337DB0, 0x50 bytes. */
int func_00337DB0(int k)
{
    int v = -1;

    switch (k) {
    case 0:
        v = 0x15C;
        break;
    case 1:
        v = 0x15C;
        break;
    case 2:
        v = 0x15C;
        break;
    case 3:
        v = 0x15C;
        break;
    }
    return v;
}

/* 0x00337E00, 0xC4 bytes. The battle kind menu. */
int func_00337E00(void)
{
    int *s = (int *)func_002FC2C0(), k;

    func_003A9010(0);
    func_003A9110();
    func_003890B0(1);
    k = func_00389050();
    func_003890B0(0);
    if (k == 1) {
        int t;

        k = func_00389090();
        s[2] = k;
        s[0] = g_00448050[k];
        t = func_00337D50(s[2]);
        func_00376100(5, t, func_00337DB0(s[2]));
        if (s[2] == 4)
            func_0031DBE0();
    }
    return 5;
}

/* 0x00337ED0, 0x5C bytes. Draw. */
void func_00337ED0(void)
{
    if (BCMD()[0] == 2)
        func_0036A560();
    else if (BCMD()[0] == 1)
        func_00373B60();
}

/* 0x00337F30, 0xB8 bytes. Update. */
int func_00337F30(void)
{
    int r = 5, s = BCMD()[0];

    if (s == 4) {
        func_00337A70();
    } else if (s == 3) {
        func_00337AB0();
        r = 0;
    } else if (s == 2) {
        func_003379A0();
    } else if (s == 1) {
        func_003378E0();
    } else {
        if (s != 0)
            return 5;
        func_003378A0();
    }
    return r;
}

/* 0x00337FF0, 0x40 bytes, matching. Step 0 of the other battle command. */
void func_00337FF0(void)
{
    int *c = BCMD();

    func_00373970(1, 3, func_00327C00());
    c[0] = 1;
}
