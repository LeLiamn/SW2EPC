/*
 * emp_force.c - the Empire mode's forces (0x002F8C80-..., after the officer records; the
 * original file's name is unknown). Written so far: from 0x002F8B20.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Force records: 0x78 bytes each (func_0030CCC0 gives the first; numbers outside the forces
 * in play, func_0030AB90, use record 0x19). +0 its leader, +2 its gold (x 10), +4 its heir?,
 * +6 three values, +0x10 its policy (100: none), +0x12 a number, +0x14 / +0x2D its relations
 * with each force (value and kind), +0x6F a target.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

extern short g_00414630[100][2];         /* the policies: kind and cost */
extern short g_004145F0[15][2];          /* per policy kind: two values */
extern char g_00446470[];                /* a separator for names */

u8 *func_0030CCC0(void);
int func_0030AB90(void);
int func_002F41E0(u32 i);
int func_002F4A70(u32 i);
int func_002F3380(u32 i);
int func_002F4450(u32 i);
int func_002F45A0(u32 i);
int func_002F3770(u32 i);
char *func_002F2A30(u32 i);
u16 func_002F2C50(u32 i);
char *func_002F2880(void);
char *func_00120928(char *to, const char *from);
char *func_001206B0(char *to, const char *from);
const char *func_00372450(void);

/* Whether `f` is a force in play. */
static inline int is_force(int f)
{
    return f >= 0 && f < func_0030AB90();
}

/* Force `f`'s record (record 0x19 for others). */
static inline u8 *frc(int f)
{
    if (!is_force(f))
        f = 0x19;
    return func_0030CCC0() + f * 0x78;
}

/* 0x002F8B20, 0x34 bytes. Whether officer `i`'s level is above officer `j`'s. */
int func_002F8B20(u32 i, u32 j)
{
    return func_002F41E0(j) < func_002F41E0(i);
}

/* 0x002F8B60, 0x120 bytes. Officer order: lower +0x97, then earlier +0x48, then larger
 * +0x56 x +0x57, then more soldiers. */
int func_002F8B60(u32 i, u32 j)
{
    int a = func_002F4A70(i), b = func_002F4A70(j);

    if (a < b)
        return 1;
    if (b < a)
        return 0;
    a = func_002F3380(i);
    b = func_002F3380(j);
    if (a < b)
        return 1;
    if (b < a)
        return 0;
    a = func_002F4450(i) * func_002F45A0(i);
    b = func_002F4450(j) * func_002F45A0(j);
    if (b < a)
        return 1;
    if (a < b)
        return 0;
    return func_002F3770(j) < func_002F3770(i);
}

/* 0x002F8C80, 0x24 bytes. Record 0x19 has no leader. */
void func_002F8C80(void)
{
    *(u16 *)(func_0030CCC0() + 3000) = 0x19F;
}

u16 func_002F8F20(int f);

/* 0x002F8CB0, 0x6C bytes. Whether force `f` is in play and has a leader. */
int func_002F8CB0(int f)
{
    if (!is_force(f))
        return 0;
    return func_002F8F20(f) < 0x19F;
}

/* 0x002F8D20, 0x8C bytes. Force `f` loses its leader. */
void func_002F8D20(int f)
{
    if (is_force(f))
        *(u16 *)frc(f) = 0x19F;
}

/* 0x002F8DB0, 0x24 bytes. Writes force `f`'s leader's title. */
char *func_002F8DB0(int f)
{
    return func_002F2A30(func_002F8F20(f));
}

/* 0x002F8DE0, 0x64 bytes, matching. Force `f`'s name: its leader's title, a separator and a word. */
char *func_002F8DE0(int f)
{
    char *s = func_002F2880();

    func_00120928(s, func_002F8DB0(f));
    func_001206B0(s, g_00446470);
    func_001206B0(s, func_00372450());
    return s;
}

/* 0x002F8E50, 0x24 bytes. Force `f`'s leader's shown name. */
u16 func_002F8E50(int f)
{
    return func_002F2C50(func_002F8F20(f));
}

/* 0x002F8E80, 0x98 bytes. Sets force `f`'s leader. */
void func_002F8E80(int f, u32 i)
{
    if (i < 0x1A0)
        *(short *)frc(f) = (short)i;
}

/* 0x002F8F20, 0x64 bytes, matching. Force `f`'s leader. */
u16 func_002F8F20(int f)
{
    return *(u16 *)frc(f);
}

/* 0x002F8F90, 0xD0 bytes. Sets force `f`'s gold (0-60000; out of range reads it). */
u32 func_002F8F90(int f, u32 g)
{
    if ((int)g < 0 || (int)g > 60000)
        return *(u16 *)(frc(f) + 2);
    *(short *)(frc(f) + 2) = (short)g;
    return g;
}

int func_002F9060(u32 f);

/* 0x002F9130, 0x5C bytes. Takes `n` gold from force `f`. */
void func_002F9130(int f, int n)
{
    func_002F8F90(f, n < (int)func_002F9060(f) ? func_002F9060(f) - n : 0);
}

/* 0x002F9190, 0x28 bytes, matching. Force `f`'s gold in coins. */
int func_002F9190(int f)
{
    return func_002F9060(f) * 10;
}

/* 0x002F91C0, 0x98 bytes. Sets force `f`'s +4 (an officer). */
void func_002F91C0(int f, u32 i)
{
    if (i < 0x1A0)
        *(short *)(frc(f) + 4) = (short)i;
}

/* 0x002F92D0, 0xB4 bytes. Sets force `f`'s value `k` of three (0-400). */
int func_002F92D0(int f, int k, int v)
{
    if (k < 0 || k > 2 || v < 0 || v > 400)
        return 0;
    *(short *)(frc(f) + 6 + k * 2) = (short)v;
    return v;
}

/* 0x002F9390, 0x74 bytes. */
u16 func_002F9390(int f, int k)
{
    return *(u16 *)(frc(f) + 6 + k * 2);
}

/* 0x002F9410, 0x70 bytes. Adds `n` to it (up to 400). */
void func_002F9410(int f, int k, int n)
{
    func_002F92D0(f, k, n + func_002F9390(f, k) < 400 ? n + func_002F9390(f, k) : 400);
}

/* 0x002F9480, 0x3C bytes. Its grade (per 100, from 1). */
int func_002F9480(int f, int k)
{
    return func_002F9390(f, k) / 100 + 1;
}

/* 0x002F94C0, 0x90 bytes. Sets force `f`'s policy (0-100). */
void func_002F94C0(int f, u16 p)
{
    if (p < 0x65)
        *(u16 *)(frc(f) + 0x10) = p;
}

int func_002F9550(u32 f);

/* 0x002F95C0, 0x5C bytes. Force `f`'s policy kind (0xFFFF without). */
u16 func_002F95C0(int f)
{
    if ((short)func_002F9550(f) == 100)
        return 0xFFFF;
    return g_00414630[func_002F9550(f) & 0xFFFF][0];
}

/* 0x002F9620, 0x6C bytes. Whether some force in play follows policy `p`. */
int func_002F9620(u32 p)
{
    int f;

    for (f = 0; f <= 0x18; f++) {
        if (func_002F8CB0(f) != 0 && p == (func_002F9550(f) & 0xFFFF))
            return 1;
    }
    return 0;
}

/* 0x002F9690, 0x9C bytes. The first free policy of kind `kind` (its number in `out`, 100 and
 * 9999 for none); returns its cost. */
u16 func_002F9690(short kind, int *out)
{
    int k;

    for (k = 0; k < 100; k++) {
        if (kind == g_00414630[k][0] && func_002F9620(k) == 0) {
            *out = k;
            return g_00414630[k][1];
        }
    }
    *out = 100;
    return 9999;
}

/* 0x002F9730, 0xEC bytes. The best policy from `k` on of the same kind, free and costing at
 * most `gold`, better than force `f`'s (100 for none). */
int func_002F9730(int f, int k, short gold)
{
    int best = 100, j;

    for (j = 0; j < 100; j++) {
        if (k <= j && g_00414630[j][0] == g_00414630[k][0] && func_002F9620(j) == 0
            && g_00414630[j][1] <= gold) {
            u32 cur = func_002F9550(f) & 0xFFFF;

            if (cur == 100 || (int)cur < j)
                best = j;
        }
    }
    return best;
}

/* 0x002F9820, 0x68 bytes. Force `f`'s policy kind's second value (0 without). */
u16 func_002F9820(int f)
{
    u32 p = func_002F9550(f) & 0xFFFF;

    if (p < 100 && g_00414630[p][0] < 0xF)
        return g_004145F0[g_00414630[p][0]][1];
    return 0;
}

/* 0x002F9890, 0x68 bytes. Its first value. */
u16 func_002F9890(int f)
{
    u32 p = func_002F9550(f) & 0xFFFF;

    if (p < 100 && g_00414630[p][0] < 0xF)
        return g_004145F0[g_00414630[p][0]][0];
    return 0;
}

int func_002FA6B0(u32 f);
void func_002FA610(int f, int g);

/* 0x002F9B00, 0x184 bytes. Sets force `f`'s relation with force `g`: value `v` (at most 12)
 * and kind `kind` (at most 3; kind 0 has value 0); a force losing its relation with its
 * target drops it. Returns the value (0 when refused). */
int func_002F9B00(int f, int g, int v, int kind)
{
    if (!is_force(f) || !is_force(g) || v > 0xC || kind > 3)
        return 0;
    if (kind == 0)
        v = 0;
    frc(f)[g + 0x14] = (u8)v;
    frc(f)[g + 0x2D] = (u8)kind;
    if (g == func_002FA6B0(f))
        func_002FA610(f, 0x19);
    return v;
}

/* 0x002F9C90, 0xC0 bytes, matching. Force `f`'s relation kind with force `g`. */
u8 func_002F9C90(int f, int g)
{
    if (!is_force(f) || !is_force(g))
        return 0;
    return frc(f)[g + 0x2D];
}

/* 0x002F9D50, 0xC0 bytes, matching. Force `f`'s relation value with force `g`. */
u8 func_002F9D50(int f, int g)
{
    if (!is_force(f) || !is_force(g))
        return 0;
    return frc(f)[g + 0x14];
}

/* 0x002F9F10, 0xC bytes, matching. */
int func_002F9F10(int k)
{
    return k == 0;
}

/* 0x002F9F20, 0x20 bytes, matching. */
int func_002F9F20(int k)
{
    return k == 1 || k == 2;
}

int func_002F9EA0(u32 f);

/* 0x002F9F40, 0x114 bytes. Sets force `f`'s +0x6F by its kind: none for kind 0, a small value
 * (at most 7) for kinds 1-2, else a byte, a force or 0x19. */
void func_002F9F40(int f, int v)
{
    int k = func_002F9EA0(f), ok;

    if (func_002F9F10(k) != 0)
        return;
    if ((u32)(k - 1) < 2) {
        if (v > 7)
            return;
    } else if (v > 0xFF) {
        return;
    }
    ok = is_force(v) || v == 0x19;
    if (!ok)
        return;
    frc(f)[0x6F] = (u8)v;
}

/* 0x002FA1D0, 0x20 bytes. */
int func_002FA1D0(u32 k)
{
    return k < 2;
}

/* 0x002FA1F0, 0x20 bytes, matching. */
int func_002FA1F0(int k)
{
    return k == 2 || k == 3;
}

/* 0x002FA210, 0xC bytes, matching. */
int func_002FA210(int k)
{
    return (u32)(k - 4) < 3;
}

/* GENERATED */
/* PROTOS */
int func_002F9260(u32 i);
void func_002F9900(u32 i, int v);
void func_002F9A00(u32 i, int v);
int func_002F9A90(u32 i);
void func_002F9E10(u32 i, int v);
int func_002FA060(u32 i);
void func_002FA0D0(u32 i, int v);
void func_002FA400(u32 i, int v);
int func_002FA490(u32 i);
void func_002FA720(u32 i, int v);
int func_002FA790(u32 i);
void func_002FA800(u32 i, int v);
int func_002FA870(u32 i);
void func_002FA8E0(u32 i, int v);
int func_002FA970(u32 i);
void func_002FA220(int f, int v);
void func_002FA500(int f, int g);
int func_002FA9E0(int f, int k);
void func_002FAA50(int f, int k, u8 v);
void func_002FAB40(int f, int v);
int func_002FABC0(int f);
void func_002FAEA0(int f, int g, int v, int kind);
void func_002FAF30(int f, int g);
int func_002FAFA0(int f, int g);
void func_002FAFC0(int f);
int func_002FB040(int f, int *out);
int func_002FB100(int f);
int func_002FB120(int f);
int func_002FB1A0(int f);
int func_002FB220(int f);
int func_002FB2A0(int f);
int func_002FB2D0(int f);
int func_002FB320(int r, int *out);
int func_002FB3B0(int r);
int func_002FB430(int f);
int func_002FB470(int f);
int func_002FB500(int f, int r);
int func_002FB5A0(int f, int *out);
int func_002FB6D0(int f);
int func_002FB6F0(int f);
void func_002FB7C0(int f);
int func_002FB8B0(void);
int func_002FB910(void);
int func_002FB9D0(int r);
int func_002FBA40(int g);
int func_002FBAC0(int *out);
int func_002FBC90(int r, int kind);
int func_002FBF20(int r, int kind, int *out);
int func_002FC000(int r);
int func_002FC0C0(int f, int g);
int func_00327D50(void);
int func_00329790(void);
int func_003297D0(void);
int func_00329810(void);
int func_002FBD80(int f);
int func_002FBDA0(int f);
int func_002F5CC0(u32 i);
int func_0030AFF0(int f);
int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort, int p5);
int func_002F8160(u32 i, int f);
u32 *func_002F7B10(void);
int func_002F34E0(u32 i);
void func_0030B540(int f);
void func_0030B330(void);
int func_0030B2F0(int f);
void func_0011ED38(void *p, int c, u32 n);
int func_0030C890(int f, int g);
int func_0030CB50(int pct);
int func_0030AC90(int f, int k);
int func_0030AD80(int f);
int func_0030AE80(int f);
int func_002FBD60();
int func_002FBDC0();
int func_002FBDE0();
int func_002FBE00();
int func_002FBE20();
int func_002FBE40();
int func_002FBE60();
int func_002FBE80();
int func_002FBEA0();
int func_002FBEC0();
int func_002FBEE0();
int func_002FBF00();
/* END PROTOS */

/* 0x002F9060, 0x64 bytes, matching. */
int func_002F9060(u32 i)
{
    return *(u16 *)(frc(i) + 0x2);
}

/* 0x002F9260, 0x64 bytes, matching. */
int func_002F9260(u32 i)
{
    return *(u16 *)(frc(i) + 0x4);
}

/* 0x002F9550, 0x64 bytes, matching. */
int func_002F9550(u32 i)
{
    return *(u16 *)(frc(i) + 0x10);
}

/* 0x002F9900, 0x8C bytes. */
void func_002F9900(u32 i, int v)
{
    if (v >= 0 && v < 0x1B)
        *(u8 *)(frc(i) + 0x12) = (u8)v;
}

/* 0x002F9990, 0x64 bytes, matching. */
int func_002F9990(u32 i)
{
    return *(u8 *)(frc(i) + 0x12);
}

/* 0x002F9A00, 0x8C bytes. */
void func_002F9A00(u32 i, int v)
{
    if (v >= 0 && v < 0xB)
        *(u8 *)(frc(i) + 0x13) = (u8)v;
}

/* 0x002F9A90, 0x64 bytes, matching. */
int func_002F9A90(u32 i)
{
    return *(u8 *)(frc(i) + 0x13);
}

/* 0x002F9E10, 0x8C bytes. */
void func_002F9E10(u32 i, int v)
{
    if (v >= 0 && v < 0x5)
        *(u8 *)(frc(i) + 0x6E) = (u8)v;
}

/* 0x002F9EA0, 0x64 bytes, matching. */
int func_002F9EA0(u32 i)
{
    return *(u8 *)(frc(i) + 0x6E);
}

/* 0x002FA060, 0x64 bytes, matching. */
int func_002FA060(u32 i)
{
    return *(u8 *)(frc(i) + 0x6F);
}

/* 0x002FA0D0, 0x8C bytes. */
void func_002FA0D0(u32 i, int v)
{
    if (v >= 0 && v < 0x8)
        *(u8 *)(frc(i) + 0x70) = (u8)v;
}

/* 0x002FA160, 0x64 bytes, matching. */
int func_002FA160(u32 i)
{
    return *(u8 *)(frc(i) + 0x70);
}

/* 0x002FA390, 0x64 bytes, matching. */
int func_002FA390(u32 i)
{
    return *(u8 *)(frc(i) + 0x71);
}

/* 0x002FA400, 0x8C bytes. */
void func_002FA400(u32 i, int v)
{
    if (v >= 0 && v < 0x3)
        *(u8 *)(frc(i) + 0x72) = (u8)v;
}

/* 0x002FA490, 0x64 bytes, matching. */
int func_002FA490(u32 i)
{
    return *(u8 *)(frc(i) + 0x72);
}

/* 0x002FA5A0, 0x64 bytes, matching. */
int func_002FA5A0(u32 i)
{
    return *(u8 *)(frc(i) + 0x73);
}

/* 0x002FA6B0, 0x64 bytes, matching. */
int func_002FA6B0(u32 i)
{
    return *(u8 *)(frc(i) + 0x74);
}

/* 0x002FA720, 0x6C bytes, matching. */
void func_002FA720(u32 i, int v)
{
    *(u8 *)(frc(i) + 0x75) = (u8)v;
}

/* 0x002FA790, 0x64 bytes, matching. */
int func_002FA790(u32 i)
{
    return *(u8 *)(frc(i) + 0x75);
}

/* 0x002FA800, 0x6C bytes, matching. */
void func_002FA800(u32 i, int v)
{
    *(u8 *)(frc(i) + 0x76) = (u8)v;
}

/* 0x002FA870, 0x64 bytes, matching. */
int func_002FA870(u32 i)
{
    return *(u8 *)(frc(i) + 0x76);
}

/* 0x002FA8E0, 0x8C bytes. */
void func_002FA8E0(u32 i, int v)
{
    if (v >= 0 && v < 0x6)
        *(u8 *)(frc(i) + 0x77) = (u8)v;
}

/* 0x002FA970, 0x64 bytes, matching. */
int func_002FA970(u32 i)
{
    return *(u8 *)(frc(i) + 0x77);
}

/* 0x002FAAD0, 0x64 bytes, matching. */
int func_002FAAD0(u32 i)
{
    return *(u16 *)(frc(i) + 0xC);
}

/* 0x002FAD20, 0x64 bytes, matching. */
int func_002FAD20(u32 i)
{
    return *(u16 *)(frc(i) + 0xE);
}


int func_002FA160(u32 f);
int func_002FA5A0(u32 f);
int func_002FAAD0(u32 f);
int func_002FAD20(u32 f);
int func_00327D50(void);
int func_00329790(void);
int func_003297D0(void);
int func_00329810(void);
int func_002FBD80(int f);
int func_002FBDA0(int f);
int func_002F5CC0(u32 i);
int func_0030AFF0(int f);

/* Whether `v` is a force or 0x19. */
#define FORCE_OR_NONE(v) (is_force(v) || (v) == 0x19)

/* 0x002FA220, 0x170 bytes. Sets force `f`'s +0x71 by its +0x70 kind: kinds 0-1 a force or
 * none, 2-3 at most 7, 4-6 a force or none, others a byte. */
void func_002FA220(int f, int v)
{
    int k = func_002FA160(f);

    if (func_002FA1D0(k) == 0) {
        if (func_002FA1F0(k) != 0) {
            if (v > 7)
                return;
        } else if (func_002FA210(k) == 0) {
            if (v > 0xFF)
                return;
        } else if (!FORCE_OR_NONE(v)) {
            return;
        }
    } else if (!FORCE_OR_NONE(v)) {
        return;
    }
    frc(f)[0x71] = (u8)v;
}

/* 0x002FA500, 0xA0 bytes. Sets force `f`'s ally (+0x73: a force or none). */
void func_002FA500(int f, int g)
{
    if (FORCE_OR_NONE(g))
        frc(f)[0x73] = (u8)g;
}

/* 0x002FA610, 0xA0 bytes. Sets force `f`'s target (+0x74). */
void func_002FA610(int f, int g)
{
    if (FORCE_OR_NONE(g))
        frc(f)[0x74] = (u8)g;
}

/* 0x002FA9E0, 0x70 bytes, matching. Force `f`'s byte `k` of +0x46. */
int func_002FA9E0(int f, int k)
{
    return frc(f)[0x46 + k];
}

/* 0x002FAA50, 0x7C bytes, matching. */
void func_002FAA50(int f, int k, u8 v)
{
    frc(f)[0x46 + k] = v;
}

/* 0x002FAB40, 0x80 bytes. Sets force `f`'s +0xC (at most 1000). */
void func_002FAB40(int f, int v)
{
    if (v > 1000)
        v = 1000;
    *(short *)(frc(f) + 0xC) = (short)v;
}

/* Clamps into 0-`max`. */
#define CLAMP0(v, max) ((v) > (max) ? (max) : (v) < 1 ? 0 : (v))

int func_002FAD90(int f);

/* 0x002FABC0, 0x160 bytes. Force `f`'s strength (0-1000): its base, its policy's first value
 * (at most 600), for the player's force a tenth of three counts (at most 300), and 2/5 of its
 * power (at most 400). */
int func_002FABC0(int f)
{
    int base = func_002FAAD0(f), pol = (short)func_002F9890(f), pl = 0, pw;

    pol = CLAMP0(pol, 600);
    if (f == func_00327D50()) {
        pl = (func_00329810() + func_00329790() + func_003297D0()) / 10;
        pl = CLAMP0(pl, 300);
    }
    pw = func_002FAD90(f) * 2 / 5;
    pw = CLAMP0(pw, 400);
    pw = pw + pl + base + pol;
    return CLAMP0(pw, 1000);
}

/* 0x002FAD90, 0x104 bytes. Force `f`'s power (0-1000): its base, 7/10 of its three values (at
 * most 840) and 40 per two counts. */
int func_002FAD90(int f)
{
    int base = func_002FAD20(f);
    int v = (func_002F9390(f, 2) + func_002F9390(f, 0) + func_002F9390(f, 1)) * 7 / 10;

    v = CLAMP0(v, 0x348);
    v = base + v + (func_002FBD80(f) + func_002FBDA0(f)) * 0x28;
    return CLAMP0(v, 1000);
}

/* 0x002FAEA0, 0x8C bytes. Sets the relation of forces `f` and `g` both ways (kinds 2 and 3 are
 * each other's mirror). */
void func_002FAEA0(int f, int g, int v, int kind)
{
    int back = kind == 2 ? 3 : kind == 3 ? 2 : kind;

    func_002F9B00(f, g, v, kind);
    func_002F9B00(g, f, v, back);
}

/* 0x002FAF30, 0x70 bytes, matching. Ends any relation between forces `f` and `g` (and their alliance). */
void func_002FAF30(int f, int g)
{
    func_002FAEA0(f, g, 0, 0);
    if (g == func_002FA5A0(f))
        func_002FA500(f, 0x19);
    if (f == func_002FA5A0(g))
        func_002FA500(g, 0x19);
}

/* 0x002FAFA0, 0x20 bytes. Whether forces `f` and `g` have a relation. */
int func_002FAFA0(int f, int g)
{
    return func_002F9C90(f, g) != 0;
}

/* 0x002FAFC0, 0x7C bytes. Ends force `f`'s relations with every force in play. */
void func_002FAFC0(int f)
{
    int g;

    for (g = 0; g < func_0030AB90(); g++) {
        if (f != g && func_002F8CB0(g) != 0)
            func_002FAF30(f, g);
    }
}

/* 0x002FB040, 0xBC bytes. The forces in play force `f` has a relation with (into `out` when
 * given); returns how many. */
int func_002FB040(int f, int *out)
{
    int g, n = 0;

    for (g = 0; g < func_0030AB90(); g++) {
        if (f != g && func_002F8CB0(g) != 0 && func_002F9C90(f, g) != 0) {
            if (out != 0)
                *out++ = g;
            n++;
        }
    }
    return n;
}

/* 0x002FB100, 0x1C bytes, matching. */
int func_002FB100(int f)
{
    return func_002FB040(f, 0);
}

/* 0x002FB120, 0x80 bytes. Whether force `f` has a relation of kind 2 with a force in play. */
int func_002FB120(int f)
{
    int g;

    for (g = 0; g <= 0x18; g++) {
        if (f != g && func_002F8CB0(g) != 0 && func_002F9C90(f, g) == 2)
            return 1;
    }
    return 0;
}

/* 0x002FB1A0, 0x80 bytes. That force (0x19 for none). */
int func_002FB1A0(int f)
{
    int g;

    for (g = 0; g <= 0x18; g++) {
        if (f != g && func_002F8CB0(g) != 0 && func_002F9C90(f, g) == 2)
            return g;
    }
    return 0x19;
}

/* 0x002FB220, 0x80 bytes. Whether force `f` has a relation of kind 3. */
int func_002FB220(int f)
{
    int g;

    for (g = 0; g <= 0x18; g++) {
        if (f != g && func_002F8CB0(g) != 0 && func_002F9C90(f, g) == 3)
            return 1;
    }
    return 0;
}

/* 0x002FB2A0, 0x2C bytes, matching. Whether `f` is the player's force. */
int func_002FB2A0(int f)
{
    return f == func_00327D50();
}

/* 0x002FB2D0, 0x4C bytes. Force `f`'s leader's second force (0x19 without a leader). */
int func_002FB2D0(int f)
{
    int l = func_002F8F20(f);

    if (l < 0 || l > 0x19E)
        return 0x19;
    return func_002F5CC0(l);
}

/* 0x002FB320, 0x90 bytes. The forces of region `r` (into `out`); returns how many. */
int func_002FB320(int r, int *out)
{
    int f, n = 0;

    for (f = 0; f < func_0030AB90(); f++) {
        if (r == func_0030AFF0(f)) {
            *out++ = f;
            n++;
        }
    }
    return n;
}

/* 0x002FB3B0, 0x7C bytes. How many forces region `r` has. */
int func_002FB3B0(int r)
{
    int f, n = 0;

    for (f = 0; f < func_0030AB90(); f++) {
        if (r == func_0030AFF0(f))
            n++;
    }
    return n;
}

int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort, int p5);
int func_002F8160(u32 i, int f);
u32 *func_002F7B10(void);
int func_002F34E0(u32 i);
void func_0030B540(int f);
void func_0030B330(void);
int func_0030B2F0(int f);
void func_0011ED38(void *p, int c, u32 n);
int func_002FA390(u32 f);
int func_002FA6B0(u32 f);
int func_002F9990(u32 f);
int func_0030C890(int f, int g);
int func_0030CB50(int pct);
int func_0030AC90(int f, int k);
int func_0030AD80(int f);
int func_0030AE80(int f);
int func_002F9EA0(u32 f);

/* 0x002FB430, 0x34 bytes, matching. Lists force `f`'s active officers (sorted); returns how many. */
int func_002FB430(int f)
{
    return func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0);
}

/* 0x002FB470, 0x90 bytes. Force `f`'s soldiers. */
int func_002FB470(int f)
{
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0), s = 0, k;
    u32 *l = func_002F7B10();

    for (k = 0; k < n; k++)
        s += func_002F3770(l[k]);
    return s;
}

/* 0x002FB500, 0x9C bytes. Whether force `f` borders region `r` (through its leader's second
 * force's neighbours). */
int func_002FB500(int f, int r)
{
    int yes = 0, g;

    func_0030B540(func_002FB2D0(f));
    for (g = 0; g < func_0030AB90(); g++) {
        if (func_0030B2F0(g) != 0 && r == func_0030AFF0(g)) {
            yes = 1;
            break;
        }
    }
    func_0030B330();
    return yes;
}

/* 0x002FB5A0, 0x128 bytes. The regions force `f` borders (other than its own, into `out` when
 * given); returns how many. */
int func_002FB5A0(int f, int *out)
{
    int seen[25], n = 0, g;

    func_0011ED38(seen, 0, 100);
    func_0030B540(func_002FB2D0(f));
    for (g = 0; g < func_0030AB90(); g++) {
        if (func_0030B2F0(g) != 0) {
            int r = func_0030AFF0(g);

            if (r >= 0 && r < func_0030AB90() && f != r && seen[r] == 0) {
                seen[r] = 1;
                if (out != 0)
                    *out++ = r;
                n++;
            }
        }
    }
    func_0030B330();
    return n;
}

/* 0x002FB6D0, 0x1C bytes, matching. */
int func_002FB6D0(int f)
{
    return func_002FB5A0(f, 0);
}

/* 0x002FB6F0, 0xCC bytes. Force `f`'s most experienced active officer (0x19F for none). */
int func_002FB6F0(int f)
{
    u32 *l = func_002F7B10(), best = 0x19F;
    int n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1, 0), e = 0, k;

    for (k = 0; k < n; k++) {
        int x = func_002F34E0(l[k]);

        if (e < x || best > 0x19E) {
            best = l[k];
            e = x;
        }
    }
    return best;
}

/* 0x002FB7C0, 0xE4 bytes. Force `f` disappears from the others' targets and alliances. */
void func_002FB7C0(int f)
{
    int g;

    for (g = 0; g < func_0030AB90(); g++) {
        if (f == g || func_002F8CB0(g) == 0)
            continue;
        if (func_002FA210(func_002FA160(g)) != 0 && f == func_002FA390(g))
            func_002FA220(g, 0x19);
        if (f == func_002FA5A0(g))
            func_002FA500(g, 0x19);
        if (f == func_002FA6B0(g))
            func_002FA610(g, 0x19);
    }
}

/* 0x002FB8B0, 0x5C bytes. The first free force number (0x19 for none). */
int func_002FB8B0(void)
{
    int f;

    for (f = 0; f < 0x19; f++) {
        if (func_002F8CB0(f) == 0)
            return f;
    }
    return 0x19;
}

/* 0x002FB910, 0xB8 bytes. The highest number (from 0x18 down) no force in play has as its
 * +0x12 (0x19 for none). */
int func_002FB910(void)
{
    int k, f;

    for (k = 0; k <= 0x18; k++) {
        for (f = 0; f < 0x19; f++) {
            if (func_002F8CB0(f) != 0 && 0x18 - k == func_002F9990(f))
                break;
        }
        if (!is_force(f))
            return 0x18 - k;
    }
    return 0x19;
}

/* 0x002FB9D0, 0x6C bytes. A region's size class by its number of forces (1-5). */
int func_002FB9D0(int r)
{
    int n = func_002FB3B0(r);

    if (n < 2)
        return 1;
    if (n < 4)
        return 2;
    if (n < 10)
        return 3;
    if (n < 0x10)
        return 4;
    return 5;
}

/* 0x002FBA40, 0x78 bytes. Whether some force has func_0030C890 with `g`. */
int func_002FBA40(int g)
{
    int f;

    for (f = 0; f < func_0030AB90(); f++) {
        if (func_0030C890(f, g) != 0)
            return 1;
    }
    return 0;
}

/* 0x002FBAC0, 0x1C4 bytes. Lists the computer's forces in play into `out`, sorted by kind,
 * regions and number (ties broken at random); returns how many. */
int func_002FBAC0(int *out)
{
    int n = 0, f, x, y;

    for (f = 0; f < func_0030AB90(); f++) {
        if (func_002F8CB0(f) != 0 && func_002FB2A0(f) == 0)
            out[n++] = f;
    }
    for (x = 0; x < n; x++) {
        int a = out[x];
        int ka = func_002F9EA0(a) * 10000 + func_002FB3B0(a) * 100 + (0x19 - a);

        for (y = x + 1; y < n; y++) {
            int b = out[y];
            int kb = func_002F9EA0(b) * 10000 + func_002FB3B0(b) * 100 + (0x19 - b);

            if (ka < kb || (ka == kb && func_0030CB50(0x32) != 0)) {
                out[x] = b;
                out[y] = a;
                ka = kb;
                a = b;
            }
        }
    }
    return n;
}

/* 0x002FBC90, 0xC4 bytes. How many forces of region `r` have `kind` as their first trait. */
int func_002FBC90(int r, int kind)
{
    int f, n = 0;

    for (f = 0; f < func_0030AB90(); f++) {
        if (is_force(f) && r == func_0030AFF0(f) && kind == func_0030AC90(f, 1))
            n++;
    }
    return n;
}

/* 0x002FBD60, 0x1C bytes, matching. */
int func_002FBD60(int r) { return func_002FBC90(r, 1); }

/* 0x002FBD80, 0x1C bytes, matching. */
int func_002FBD80(int r) { return func_002FBC90(r, 4); }

/* 0x002FBDA0, 0x1C bytes, matching. */
int func_002FBDA0(int r) { return func_002FBC90(r, 5); }

/* 0x002FBDC0, 0x20 bytes, matching. */
int func_002FBDC0(int r) { return func_002FBD60(r) != 0; }

/* 0x002FBDE0, 0x20 bytes, matching. */
int func_002FBDE0(int r) { return func_002FBC90(r, 9) != 0; }

/* 0x002FBE00, 0x20 bytes, matching. */
int func_002FBE00(int r) { return func_002FBC90(r, 6) != 0; }

/* 0x002FBE20, 0x1C bytes, matching. */
int func_002FBE20(int r) { return func_002FBC90(r, 2); }

/* 0x002FBE40, 0x20 bytes, matching. */
int func_002FBE40(int r) { return func_002FBE20(r) != 0; }

/* 0x002FBE60, 0x1C bytes, matching. */
int func_002FBE60(int r) { return func_002FBC90(r, 3); }

/* 0x002FBE80, 0x20 bytes, matching. */
int func_002FBE80(int r) { return func_002FBE60(r) != 0; }

/* 0x002FBEA0, 0x1C bytes, matching. */
int func_002FBEA0(int r) { return func_002FBC90(r, 7); }

/* 0x002FBEC0, 0x20 bytes, matching. */
int func_002FBEC0(int r) { return func_002FBEA0(r) != 0; }

/* 0x002FBEE0, 0x1C bytes, matching. */
int func_002FBEE0(int r) { return func_002FBC90(r, 8); }

/* 0x002FBF00, 0x20 bytes, matching. */
int func_002FBF00(int r) { return func_002FBEE0(r) != 0; }

/* 0x002FBF20, 0xD8 bytes. The forces of region `r` with first trait `kind` (into `out`);
 * returns how many. */
int func_002FBF20(int r, int kind, int *out)
{
    int f, n = 0;

    for (f = 0; f < func_0030AB90(); f++) {
        if (is_force(f) && r == func_0030AFF0(f) && kind == func_0030AC90(f, 1)) {
            *out++ = f;
            n++;
        }
    }
    return n;
}

/* 0x002FC000, 0xBC bytes. Whether a force of region `r` has its +0x.. below its maximum. */
int func_002FC000(int r)
{
    int f;

    for (f = 0; f < func_0030AB90(); f++) {
        if (is_force(f) && r == func_0030AFF0(f) && func_0030AD80(f) < func_0030AE80(f))
            return 1;
    }
    return 0;
}

/* 0x002FC0C0, 0x158 bytes. The weakest force (by regions, officers, soldiers and strength)
 * force `g` has a relation with, other than `f` and `g` (0x19 for none). */
int func_002FC0C0(int f, int g)
{
    int best = 0x19, low = 0x7FFFFFFF, h;

    if (f == g)
        return 0x19;
    for (h = 0; h < 0x19; h++) {
        if (func_002F8CB0(h) != 0 && h != g && h != f && func_002F9C90(g, h) != 0) {
            int v = (func_002FB3B0(h) + func_002FB430(h)) * 100 + func_002FB470(h) / 100
                    + func_002FABC0(h) / 10;

            if (v < low) {
                low = v;
                best = h;
            }
        }
    }
    return best;
}
