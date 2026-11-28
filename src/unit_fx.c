/*
 * unit_fx.c - the effects attached to the battle's actors (weapon trails, auras, glows): each of
 * the 0x8F actors (0x630 bytes at 0x00574DE0) has an effect slot record of 0x70 bytes at
 * 0x0074B868. Original file name unknown (0x0023EF50-0x002409AC).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Slot record: +0x00 free trail places (8 at start), +0x04 free aura places (4), +0x08 the
 * effect bits shown last, +0x0C 4 auras, +0x1C 13 effects by part, +0x50 8 trails.
 */

#define SW2E_FILE_UNIT_FX_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int free_trails;         /* +0x00 */
    int free_auras;          /* +0x04 */
    u32 shown;               /* +0x08 the effect bits last shown */
    u8 *aura[4];             /* +0x0C */
    u8 *part[13];            /* +0x1C */
    u8 *trail[8];            /* +0x50 */
} FxSlots;

extern FxSlots g_0074B868[0x8F];
extern u8 g_00574DE0[][0x630];           /* the actors */
extern u32 g_00410670[12];               /* the weapon element effects, by bit */

#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))  /* (scratchpad) the effect layer */

void func_0021A610(u8 *e);
void func_0023F730(u8 *a, FxSlots *s);
void func_0023FA40(u8 *a, FxSlots *s);
void func_0023FD60(u8 *a, FxSlots *s, u32 bits);

int func_00240000(int k, u8 *a, u8 c, FxSlots *s, int part, u32 bits, u32 bit, u32 f, int keep);
int func_00240120(int k, u8 *a, FxSlots *s, u32 bits, u32 bit, u32 c);
void func_002401C0(u8 *a, FxSlots *s, int part);
int func_00240420(u32 k);
void func_00240450(u32 k, u8 *e);

/* 0x0023EF50, 0x38 bytes. Turns colours 0x14 / 0x15 into 0x12 / 0x13. */
void func_0023EF50(char *c)
{
    if (*c == 0x14)
        *c = 0x12;
    else if (*c == 0x15)
        *c = 0x13;
}

/* 0x0023EF90, 0x32C bytes. Actor `a`'s weapon effects for bits `bits` (0-4) in colours `c1`,
 * `c2` (swapped by weapon kind). */
void func_0023EF90(u8 *a, FxSlots *s, u32 bits, char c1, char c2)
{
    u8 *m = *(u8 **)(a + 0x110);
    u32 f = func_0016C040(a) != 0 ? 0x200 : 0;
    char k = m[0x1C];

    if (k == 0xF) {
        if (c1 == 0x14)
            c1 = 0x15;
        else if (c2 == 0x14)
            c2 = 0x15;
    } else if (k == 0x11 || k == 6 || k == 5) {
        if (c1 == 0x15)
            c1 = 0x14;
        else if (c2 == 0x15)
            c2 = 0x14;
    }
    func_0023EF50(&c1);
    func_0023EF50(&c2);
    if (c1 == '.')
        c1 = 0x12;
    func_001C8BE0(5, PS2_ADDR(a + 0x40));
    f |= 8;
    func_00240000(0x27, a, c1, s, 2, bits, 2, f, 0);
    func_00240000(0xB, a, c1, s, 3, bits, 0x10, f, 0);
    func_00240000(0xB, a, c2, s, 4, bits, 0x10, f, 0);
    func_00240000(0x33, a, c1, s, 3, bits, 4, f, 0);
    func_00240000(0x33, a, c2, s, 4, bits, 4, f, 0);
    func_00240000(0x34, a, c1, s, 3, bits, 8, f, 0);
    func_00240000(0x34, a, c2, s, 4, bits, 8, f, 0);
    func_00240000(10, a, c1, s, 0, bits, 1, f, 0);
    func_00240000(10, a, c2, s, 1, bits, 1, f, 0);
}

/* 0x0023F2C0, 0x460 bytes. Actor `a`'s aura effects for bits `bits` (0x100000-0x1000000) in the
 * two element colours `c`. */
void func_0023F2C0(u8 *a, FxSlots *s, u32 bits, char *c)
{
    u8 *m = *(u8 **)(a + 0x110);
    u32 f[2], k;
    int r;
    char w;

    if (*c == '.')
        *c = 0x14;
    for (k = 0; k < 2; k++) {
        f[k] = func_0016C040(a) != 0 ? 0x200 : 0;
        w = m[0x1C];
        if ((u8)c[k] - 0x14 < 2 && w != 0x18 && w != 5) {
            if (w == 0x14 || w == 0x12 || w == 0x10 || w == 0xE || w == 0xC || w == 6 || w == 1 || w == 0)
                f[k] |= 0x200000;
            else
                f[k] |= 0x100000;
        }
    }
    func_001C8BE0(5, PS2_ADDR(a + 0x40));
    r = func_00240000(0x48, a, c[0], s, 0xB, bits, 0x100000, f[0] | 0x10, 0);
    func_00240000(0x48, a, c[1], s, 0xC, bits, 0x100000, f[1] | 0x10, 0);
    if (r != 0)
        return;
    r = func_00240000(0x49, a, c[0], s, 0xB, bits, 0x400000, f[0] | 0x10, 0);
    func_00240000(0x49, a, c[1], s, 0xC, bits, 0x400000, f[1] | 0x10, 0);
    if (r != 0)
        return;
    r = func_00240000(0x4A, a, c[0], s, 0xB, bits, 0x200000, f[0] | 0x10, 0);
    func_00240000(0x4A, a, c[1], s, 0xC, bits, 0x200000, f[1] | 0x10, 0);
    if (r != 0)
        return;
    w = m[0x1C];
    if (w != 0x19 && w != 0x18 && w != 0x17 && w != 10) {
        if (w == 0x14) {
            if ((*(u32 *)(*(u8 **)(a + 0x210) + 0x18) & 0x8000000) == 0) {
                if (*c == 0x14)
                    *c = 0x15;
                else if (*c == 0x15)
                    *c = 0x14;
            }
        } else if (w == 0xF) {
            if (*c == 0x14)
                *c = 0x15;
        } else if ((w == 0x16 || w == 0x12 || w == 0x11 || w == 0x10 || w == 0xE || w == 0xB
                    || w == 6 || w == 5 || w == 1 || w == 0) && *c == 0x15) {
            *c = 0x14;
        }
    }
    for (k = 0; k < 2; k++) {
        if ((f[k] & 0x300000) == 0)
            func_00240120(2, a, s, bits, 0x800000, c[k]);
        else
            func_00240120(3, a, s, bits, 0x800000, c[k]);
    }
}

/* 0x00240000, 0x114 bytes. Turns effect `k` of part `part` on or off as bit `bit` of `bits`
 * changes against the shown ones; whether it changed. */
int func_00240000(int k, u8 *a, u8 c, FxSlots *s, int part, u32 bits, u32 bit, u32 f, int keep)
{
    if ((bits & bit) == 0 || (s->shown & bit) != 0) {
        if ((bits & bit) == 0 && (s->shown & bit) != 0) {
            if (s->part[part] != 0)
                func_002401C0(a, s, part);
            return 1;
        }
        return 0;
    }
    if (keep != 0 || c >= 0x2E)
        return 0;
    if (s->part[part] != 0)
        func_002401C0(a, s, part);
    g_70000D60 = 0;
    s->part[part] = (u8 *)PS2_PTR(func_001C87B0(k, PS2_ADDR(a), c, f | 1));
    return 1;
}

/* 0x00240120, 0x94 bytes. Starts aura `k` of colour `c` when bit `bit` turns on and no aura of
 * that kind and colour runs. */
int func_00240120(int k, u8 *a, FxSlots *s, u32 bits, u32 bit, u32 c)
{
    int none = 1;
    u32 j;

    if ((bits & bit) == 0 || (s->shown & bit) != 0)
        return 0;
    for (j = 0; j < 4; j++) {
        u8 *e = s->aura[j];

        if (e != 0 && *(int *)(e + 0x10) == k && *(u32 *)(e + 0x4C) == (c & 0xFF))
            none = 0;
    }
    if (none && (c & 0xFF) < 0x2E) {
        func_0021A400(k, PS2_ADDR(a), c);
        return 1;
    }
    return 0;
}

/* 0x002401C0, 0xB8 bytes. Stops part `part`'s effect (kept as a fading trail when there is room). */
void func_002401C0(u8 *a, FxSlots *s, int part)
{
    u8 **p = &s->part[part];

    if (*p == 0)
        return;
    if (func_00240420(a[0x14E]) == 0) {
        if (*p != 0)
            *(u32 *)(*p + 0x38) |= 8;
        *p = 0;
    } else {
        u32 f;

        *(int *)(*p + 0xFC) = 1;
        func_00240450(a[0x14E], *p);
        f = *(u32 *)(*p + 0x34);
        *(u32 *)(*p + 0x34) = f & ~1;
        *(u32 *)(*p + 0x34) = f & ~3;
        *(u32 *)(*p + 0x34) |= 0x800;
        *p = 0;
    }
}

/* 0x00240280, 0x38 bytes, matching. Stops all part effects. */
void func_00240280(FxSlots *s)
{
    u32 k;

    for (k = 0; k < 0xD; k++) {
        if (s->part[k] != 0) {
            *(u32 *)(s->part[k] + 0x38) |= 8;
            s->part[k] = 0;
        }
    }
}

/* 0x002402C0, 0x38 bytes, matching. Stops the trails. */
void func_002402C0(FxSlots *s)
{
    u32 k;

    for (k = 0; k < 8; k++) {
        if (s->trail[k] != 0)
            *(u32 *)(s->trail[k] + 0x38) |= 8;
    }
}

/* 0x00240300, 0x54 bytes, matching. Stops the auras. */
void func_00240300(FxSlots *s)
{
    u32 k;

    for (k = 0; k < 4; k++) {
        if (s->aura[k] != 0)
            func_0021A610(s->aura[k]);
    }
}

/* 0x00240360, 0xB8 bytes. Resets all actors' effect slots. */
void func_00240360(void)
{
    u32 k, j;

    for (k = 0; k < 0x8F; k++) {
        FxSlots *s = &g_0074B868[k];

        s->free_trails = 8;
        s->free_auras = 4;
        s->shown = 0;
        for (j = 0; j < 13; j++)
            s->part[j] = 0;
        for (j = 0; j < 8; j++)
            s->trail[j] = 0;
        for (j = 0; j < 4; j++)
            s->aura[j] = 0;
    }
    func_00253250();
}

/* 0x00240420, 0x28 bytes, matching. Whether actor `k` has a free trail place. */
int func_00240420(u32 k)
{
    return g_0074B868[k & 0xFF].free_trails > 0;
}

/* 0x00240450, 0xA0 bytes. Keeps effect `e` as one of actor `k`'s trails (else ends it). */
void func_00240450(u32 k, u8 *e)
{
    FxSlots *s;
    u32 j;

    if ((k & 0xFF) >= 0x8F)
        return;
    s = &g_0074B868[k & 0xFF];
    for (j = 0; j < 8; j = (j + 1) & 0xFF) {
        if (s->trail[j] == 0)
            break;
    }
    if (j < 8) {
        s->trail[j] = e;
        s->free_trails--;
    } else if (e != 0) {
        *(u32 *)(e + 0x38) |= 8;
    }
}

/* 0x002404F0, 0xAC bytes. Drops trail `e` of actor `k`. */
void func_002404F0(u32 k, u8 *e)
{
    FxSlots *s;
    u32 j;

    if ((k & 0xFF) >= 0x8F)
        return;
    s = &g_0074B868[k & 0xFF];
    for (j = 0; j < 8; j = (j + 1) & 0xFF) {
        if (s->trail[j] == e)
            break;
    }
    if (j < 8) {
        s->trail[j] = 0;
        s->free_trails++;
    }
    if (*(int *)(e + 0x24) == 0xF3)
        func_00253EA0(k, e[0xF8]);
}

/* 0x002405A0, 0xA0 bytes. Keeps aura `e` for actor `k` (else ends it). */
void func_002405A0(u32 k, u8 *e)
{
    FxSlots *s;
    u32 j;

    if ((k & 0xFF) >= 0x8F)
        return;
    s = &g_0074B868[k & 0xFF];
    for (j = 0; j < 4; j = (j + 1) & 0xFF) {
        if (s->aura[j] == 0)
            break;
    }
    if (j < 4) {
        s->aura[j] = e;
        s->free_auras--;
    } else {
        func_0021A610(e);
    }
}

/* 0x00240640, 0x88 bytes. Drops aura `e` of actor `k`. */
void func_00240640(u32 k, u8 *e)
{
    FxSlots *s;
    u32 j;

    if ((k & 0xFF) >= 0x8F)
        return;
    s = &g_0074B868[k & 0xFF];
    for (j = 0; j < 4; j = (j + 1) & 0xFF) {
        if (s->aura[j] == e)
            break;
    }
    if (j < 4) {
        s->aura[j] = 0;
        s->free_auras++;
    }
}

/* 0x002406D0, 0xC0 bytes. Ends all of actor `k`'s effects. */
void func_002406D0(u32 k)
{
    u8 *a;
    u32 j;

    k &= 0xFF;
    if (k >= 0x8F)
        return;
    a = g_00574DE0[k];
    func_00240280(&g_0074B868[k]);
    func_002402C0(&g_0074B868[k]);
    func_00240300(&g_0074B868[k]);
    g_0074B868[k].shown = 0;
    func_00253790(a);
    for (j = 0; j < 10; j++, a += 0x30) {
        if (*(int *)(a + 0x478) != 0) {
            func_002088C0((u8 *)PS2_PTR(*(int *)(a + 0x478)));
            *(int *)(a + 0x478) = 0;
        }
    }
}

/* 0x00240790, 0x220 bytes. Updates actor `k`'s effects to bits `bits` (weapon colours from its
 * weapon's element bits). */
void func_00240790(u32 k, u32 bits)
{
    u8 *a, *wp;
    FxSlots *s;
    char c[2];
    u32 last;

    k &= 0xFF;
    if (k >= 0x8F)
        return;
    a = g_00574DE0[k];
    if (*(int *)(a + 0x11C) == 0)
        return;
    s = &g_0074B868[k];
    wp = *(u8 **)(*(u8 **)(a + 0x210) + 0x14);
    if (wp == 0) {
        c[0] = 0x2E;
        c[1] = 0x2E;
    } else {
        u32 j = 0, n = 0;

        while (j < 0xC && n < 2) {
            if ((*(u16 *)(wp + 0x12) & 1 << j) != 0)
                c[n++] = (char)g_00410670[j];
            j++;
        }
        for (; n < 2; n++)
            c[n] = 0x2E;
    }
    last = s->shown;
    if ((bits & 0x1F) != 0 || (last & 0x1F) != 0)
        func_0023EF90(a, s, bits & 0x1F, c[0], c[1]);
    if ((bits & 0x3E0) != 0 || (last & 0x3E0) != 0)
        func_0023F730(a, s);
    if ((bits & 0x33C00) != 0 || (last & 0x33C00) != 0)
        func_0023FA40(a, s);
    if ((bits & 0xCC000) != 0 || (last & 0xCC000) != 0)
        func_0023FD60(a, s, bits);
    if ((bits & 0x1F00000) != 0 || (last & 0x1F00000) != 0)
        func_0023F2C0(a, s, bits & 0x1F00000, c);
    s->shown = bits;
}
