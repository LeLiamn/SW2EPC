/*
 * effect.c - the battle's effects (original source file effect.c: its name is passed to the file
 * loader at 0x001C7620 and 0x001C77D0; the file likely starts earlier). Written so far: from
 * 0x001C0250.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The effect pack (0x0045D398) holds 0x18B effects ("EFB" files, see docs/formats/EFB.md) found
 * by offset; 15 effect runners of 0x350 bytes live at 0x0072D120.
 */

#define SW2E_FILE_EFFECT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))    /* (scratchpad) the effect layer being drawn */
#define g_70000D64 (*(int *)PS2_PTR(0x70000D64))
#define g_70000D68 (*(int *)PS2_PTR(0x70000D68))
#define g_70000D6C (*(float *)PS2_PTR(0x70000D6C))  /* (scratchpad) the effects' time scale */

#ifdef SW2E_PC
extern ps2ptr g_0045D398_a;                   /* (small data) the effect pack */
#define g_0045D398 ((u8 *)PS2_PTR(g_0045D398_a))
#define g_0045D398_SET(v) (g_0045D398_a = PS2_ADDR(v))
#else
extern u8 *g_0045D398;
#define g_0045D398_a (*(ps2ptr *)&g_0045D398)
#define g_0045D398_SET(v) (g_0045D398 = (v))
#endif
extern u8 *g_0072C870[0x18B];            /* the effects by number */
extern u8 **g_0040BDC0[0x18B];           /* effects sharing another's (by number) */
extern u32 g_0045D324;                   /* (small data) 1: no sharing */
extern u32 g_0072D0F0[0xF];
extern u8 g_0072D120[0xF][0x350];        /* the effect runners */
extern u32 g_0045D2C0, g_0045D374, g_0045D330, g_0045D380;
extern u8 *g_006D3370[5];
extern u32 g_0072C750[4];
extern u8 g_004084F0[], g_00408540[];

void func_001C8CF0(u32 k);
void func_001C9070(void);
void func_0020F420(void);
void func_001023B0(void (*f)(void));
void func_00208550(void); void func_0021A320(void);
void func_0024F8A0(void);
void func_001C1230(void);
void func_001C3490(u8 *run, u8 *part, u32 k, u8 *shared);

/* 0x001C0250, 0xE8 bytes. Opens the effect pack: its offsets made into addresses; "EFB" entries
 * become effects (and are set up), the others take the effect they share. */
void func_001C0250(void)
{
    u32 *e, k;

    if (g_0045D398 == 0)
        return;
    e = (u32 *)(g_0045D398 + 4);
    for (k = 0; k < 0x18B; k++, e += 2) {
        *e = *e + (u32)PS2_ADDR(g_0045D398);
        if (g_0072C870[k] != 0)
            continue;
        if (*(u32 *)PS2_PTR(*e) == 0x00424645) {              /* "EFB" */
            g_0072C870[k] = (u8 *)PS2_PTR(*e);
            func_001C8CF0(k);
        } else if (g_0045D324 == 0 && g_0040BDC0[k] != 0) {
            g_0072C870[k] = g_0072C870[*(u32 *)g_0040BDC0[k]];
        }
    }
}

/* 0x001C0340, 0x238 bytes. Resets the effects: the 15 runners (their three part lists empty),
 * the effect layers and lights. */
void func_001C0340(void)
{
    u32 k;

    func_001CC500((unsigned int *)(g_004084F0), (unsigned int *)(g_00408540));
    for (k = 0; k < 0xF; k++) {
        u8 *r = g_0072D120[k];

        g_0072D0F0[k] = 0;
        *(u32 *)(r + 0x104) = 0;
        *(u32 *)(r + 0x23C) = 0;
        *(u32 *)(r + 0x34C) = 0;
        *(u32 *)(r + 0x100) = 0;
        *(u32 *)(r + 0x238) = 0;
        *(u32 *)(r + 0x348) = 0;
        PS2_STOREP(u8 *, (r + 0x350), r + 0x10);
        PS2_STOREP(u8 *, (r + 0x354), r + 0x120);
        PS2_STOREP(u8 *, (r + 0x358), r + 0x240);
    }
    func_001CAFF0();
    func_001F1D50();
    if (g_0045D2C0 != 0)
        func_001C9070();
    g_0045D374 = 0;
    g_70000D60 = 0;
    g_70000D64 = 0;
    g_70000D68 = 0;
    g_70000D6C = 1.0f;
    for (k = 0; k < 5; k++)
        g_006D3370[k] = 0;
    for (k = 0; k < 4; k++)
        g_0072C750[k] = 0;
    func_0020F420();
    g_0045D330 = 0;
    func_001023B0(func_001C9390);
}

/* 0x001C0580, 0x5C bytes, matching. Steps every effect kind. */
void func_001C0580(void)
{
    func_002EA9A0();
    func_00208550();
    func_0021A320();
    func_00228E70();
    func_0024EA80();
    func_002A7EC0();
    func_00240360();
    func_002AEBB0();
    func_002F0090();
}

/* 0x001C05E0, 0x2C bytes, matching. */
void func_001C05E0(void)
{
    func_002EB0F0();
    func_0021A440();
    func_002290E0();
}

/* Draws the effects of the given layers in order. */
static inline void draw_layers(const u8 *l, int n)
{
    int k;

    for (k = 0; k < n; k++) {
        g_70000D60 = l[k];
        func_001C1230();
    }
}

/* 0x001C0610, 0xCC bytes. Draws the effects (layers 2, 0, 1, 13, 6, 10, 5, 14, 4, 3). */
void func_001C0610(void)
{
    static const u8 l[] = {2, 0, 1, 0xD, 6, 10, 5, 0xE, 4, 3};

    func_002F03B0();
    g_0045D380 = 0;
    draw_layers(l, sizeof(l));
    func_0024F8A0();
    func_001C05E0();
}

/* 0x001C06E0, 0xB8 bytes. Draws the later layers (5, 9, 4, 3, 6, 10, 14, 7, 8). */
void func_001C06E0(void)
{
    static const u8 l[] = {5, 9, 4, 3, 6, 10, 0xE, 7, 8};

    func_002F03B0();
    g_0045D380 = 0;
    draw_layers(l, sizeof(l));
    func_0024F8A0();
}

/* 0x001C07A0, 0x104 bytes. Draws layers 2, 0, 1, 13, 3 in the first pass, then 5, 9, 4, 6, 10,
 * 14, 7, 8. */
void func_001C07A0(void)
{
    static const u8 a[] = {2, 0, 1, 0xD, 3}, b[] = {5, 9, 4, 6, 10, 0xE, 7, 8};

    func_002F03B0();
    g_0045D380 = 1;
    draw_layers(a, sizeof(a));
    g_0045D380 = 0;
    draw_layers(b, sizeof(b));
    func_001C05E0();
    func_0024F8A0();
}

/* 0x001C08B0, 0x90 bytes. Draws layers 9, 4, 6, 10, 14, 7, 8. */
void func_001C08B0(void)
{
    static const u8 l[] = {9, 4, 6, 10, 0xE, 7, 8};

    g_0045D380 = 0;
    draw_layers(l, sizeof(l));
    func_0024F8A0();
}

/* 0x001C0940, 0x80 bytes. Draws layers 2, 4, 10, 11, 12, 3. */
void func_001C0940(void)
{
    static const u8 l[] = {2, 4, 10, 0xB, 0xC, 3};

    g_0045D380 = 0;
    draw_layers(l, sizeof(l));
    func_001C05E0();
}

/* 0x001C09C0, 0x1B0 bytes. Starts the parts of effect `e` whose start time (+0x1C for kind 0,
 * +0x5C for kind 1) was reached since the last frame by runner `r` (+0x28 its time, +0x3C the
 * parts started, +0x4C their count), with the shared effect's parts when it matches. */
void func_001C09C0(u8 *r, u8 *e)
{
    float step = *(float *)(e + 0x10), t0;
    u32 *p = PS2_LOADP(u32 *, (e + 0x14)), n = *(u32 *)(e + 4), done = *(u32 *)(r + 0x3C), k;
    u8 *shared = g_0045D324 == 0 ? (u8 *)g_0040BDC0[*(int *)(r + 0x24)] : 0;
    float s = step * g_70000D6C;

    t0 = *(float *)(r + 0x28) - (step < s ? s : step);
    if (shared != 0 && *(u32 *)(shared + 4) != n)
        shared = 0;
    for (k = 0; k < n; k++, p += 2) {
        u32 bit = 1 << k;
        float t;

        if (done & bit)
            continue;
        if (p[0] == 0) {
            t = *(float *)((u8 *)PS2_PTR(p[1]) + 0x1C);
            if (t0 < t && t <= *(float *)(r + 0x28)) {
                func_001C3490(r, (u8 *)PS2_PTR(p[1]), k, shared);
                *(u32 *)(r + 0x3C) |= bit;
                *(int *)(r + 0x4C) += 1;
            }
        } else if (p[0] == 1) {
            t = *(float *)((u8 *)PS2_PTR(p[1]) + 0x5C);
            if (t0 < t && t <= *(float *)(r + 0x28)) {
                func_001C4B10(r, (u8 *)PS2_PTR(p[1]), k, PS2_ADDR(shared));
                *(u32 *)(r + 0x3C) |= bit;
                *(int *)(r + 0x4C) += 1;
            }
        }
    }
}

#define g_70000150 (*(int *)PS2_PTR(0x70000150))    /* (scratchpad) the frame's buffer (0 / 1) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))    /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

extern u32 g_0045D2A8;                   /* (small data) the game paused */
extern float g_0045CC7C;                 /* (small data) the battle's slow motion factor */

void func_001C3890(float *p, int *list);
void func_001C4D10(u8 *r, float *p);
void func_001C46F0(u8 *r, float *p);

#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define W32(o, off) (*(u32 *)((u8 *)(o) + (off)))

/* 0x001C0B80, 0xC4 bytes. Steps runner `r`'s sprite parts (list +0): ended ones (past time 1)
 * are finished once (bit 0 of +0x2CC), the others drawn into this frame's list. */
void func_001C0B80(u8 *r)
{
    float *p;

    for (p = PS2_LOADP(float *, r); p != 0; p = PS2_LOADP(float *, (p + 5))) {
        if (*p > 1.0f) {
            if (((u8 *)p)[0x2CC] & 1)
                func_001C39A0(PS2_ADDR(r), PS2_ADDR(p));
            else
                ((u8 *)p)[0x2CC] |= 1;
        } else {
            func_001C3890(p, (int *)r + g_70000150 * 0x14 + 0x18);
        }
    }
}

/* 0x001C0C50, 0x80 bytes. Steps runner `r`'s model parts (list +0x10). */
void func_001C0C50(u8 *r)
{
    float *p;

    for (p = PS2_LOADP(float *, (r + 0x10)); p != 0; p = PS2_LOADP(float *, (p + 7))) {
        if (*p > 1.0f)
            func_001C4F60(PS2_ADDR(r), PS2_ADDR(p));
        else
            func_001C4D10(r, p);
    }
}

/* 0x001C0CE0, 0xAC bytes. Steps runner `r`'s strip parts (list +8). */
void func_001C0CE0(u8 *r)
{
    float *p;

    for (p = PS2_LOADP(float *, (r + 8)); p != 0; p = PS2_LOADP(float *, (p + 6))) {
        if (*p > 1.0f) {
            if (((u8 *)p)[0x2DC] & 1)
                func_001C4A00(r, PS2_ADDR(p));
            else
                ((u8 *)p)[0x2DC] |= 1;
        } else {
            func_001C46F0(r, p);
        }
    }
}

/* 0x001C0D90, 0x138 bytes. At its end: whether runner `r` lives on (it loops when flag 1 of
 * +0x34: time back to 0, its parts restarted; otherwise it waits for its parts to end, then
 * ends with state 4). */
int func_001C0D90(u32 *r)
{
    u32 s = r[0xE];

    if (s & 4)
        return 0;
    if (s & 8) {
        r[0xE] = s | 4;
        return 1;
    }
    if ((r[0xD] & 1) == 0) {
        if (r[4] != 0 || r[2] != 0)
            return 1;
        if (r[0] == 0)
            r[0xE] = s | 4;
        return 1;
    }
    r[10] = 0;
    r[0x10] = r[0x10] + 1;
    r[0xE] &= ~4u;
    if ((r[0xD] & 0x2000000) == 0) {
        r[0xF] = 0;
        r[0x13] = 0;
    } else {
        u32 *p;

        for (p = (u32 *)PS2_PTR(r[0]); p != 0; p = (u32 *)PS2_PTR(p[5]))
            *p = 0;
        for (p = (u32 *)PS2_PTR(r[2]); p != 0; p = (u32 *)PS2_PTR(p[6]))
            *p = 0;
    }
    if (r[0xD] & 2) {
        r[0xD] &= ~1u;      /* (two writes in the original) */
        r[0xD] &= ~3u;
    }
    return 1;
}

/* Sets the effects' time scale. */
static inline void time_scale(int slow, float k)
{
    g_70000D68 = slow;
    g_70000D6C = k;
}

/* 0x001C0ED0, 0x1C8 bytes. Whether runner `r` steps this frame, and its time scale: paused
 * games step only ending runners at a quarter (not runner 0xCF nor in state 4); runners with
 * flag 0x200 or 0x20000000 or in slow motion follow the battle's slow motion in the second
 * pass; plain ones step in the first pass, the others every other frame of the second. */
int func_001C0ED0(u8 *r)
{
    u32 f = W32(r, 0x34);

    if (g_0045D2A8 != 0) {
        if (g_0045D374 == 4 || *(int *)(r + 0x24) == 0xCF)
            time_scale(0, 1.0f);
        else
            time_scale(1, 0.25f);
        return 1;
    }
    if ((f & 0x200) == 0 && (f & 0x20000000) == 0 && (W32(r, 0x38) & 1) == 0 && (f & 1) == 0) {
        int go;

        if (g_0045D380 == 0) {
            W32(r, 0x38) |= 8;
            return 0;
        }
        go = (W32(r, 0x48) & 1) != 0;
        if (go)
            time_scale(1, g_0045CC7C * 2.0f);
        W32(r, 0x48) += 1;
        return go;
    }
    if ((f & 0x200) == 0 && (f & 0x20000000) == 0 && (W32(r, 0x38) & 1) == 0
        && (f & 0x40000000) != 0)
        return 1;
    if (f & 0x200)
        time_scale(0, 1.0f);
    else if (g_0045D380 == 0)
        time_scale(0, 1.0f);
    else
        time_scale(1, g_0045CC7C);
    return 1;
}

/* 0x001C10A0, 0x190 bytes. Steps runner `r`: its fading (flags 0x800 / 0x400), its new parts,
 * its three part lists and its time. Whether it lives on. */
int func_001C10A0(u8 *r)
{
    u8 *e = PS2_LOADP(u8 *, (r + 0x20));

    if (W32(r, 0x34) & 0x800) {
        F32(r, 0x2C) = F32(r, 0x2C) - 0.0626f;
        if (F32(r, 0x2C) <= 0.0f)
            W32(r, 0x38) |= 8;
    } else if ((W32(r, 0x34) & 0x400) && (F32(r, 0x2C) = F32(r, 0x2C) - 0.135f) <= 0.0f) {
        W32(r, 0x38) |= 8;
    }
    if ((W32(r, 0x38) & 0xC) == 0 && func_001C0ED0(r) != 0) {
        if (W32(r, 0x4C) < W32(e, 4))
            func_001C09C0(r, e);
        func_001C0B80(r);
        func_001C0C50(r);
        func_001C0CE0(r);
        if (g_70000D68 == 0)
            F32(r, 0x28) = F32(r, 0x28) + F32(e, 0x10);
        else
            F32(r, 0x28) = F32(e, 0x10) * g_70000D6C + F32(r, 0x28) + 0.0f;
    }
    if (F32(r, 0x28) >= 1.0f || (W32(r, 0x38) & 0xC))
        return func_001C0D90((u32 *)r);
    return 1;
}

void func_001C1360(u8 *e);
void func_001C1440(u8 *e);
void func_001C1530(u8 *e);

/* 0x001C1230, 0x128 bytes. Steps the effects of the current layer (its three kinds of runners,
 * ending those that are done) and notes whether the layer has any. */
void func_001C1230(void)
{
    u8 *l = g_0072D120[g_70000D60] - 0x30;
    u8 *a = PS2_LOADP(u8 *, (l + 0x134)), *b = PS2_LOADP(u8 *, (l + 0x26C)), *c = PS2_LOADP(u8 *, (l + 0x37C));

    g_0072D0F0[g_70000D60] = !(a == 0 && b == 0 && c == 0);
    for (; a != 0; a = PS2_LOADP(u8 *, (a + 0xF4))) {
        if (func_001C10A0(a) == 0)
            func_001C1360(a);
    }
    for (; b != 0; b = PS2_LOADP(u8 *, (b + 0x11C))) {
        if (func_001C10A0(b) == 0)
            func_001C1440(b);
    }
    for (; c != 0; c = PS2_LOADP(u8 *, (c + 0x10C))) {
        if (func_001C10A0(c) == 0)
            func_001C1530(c);
    }
}

/* Frees a runner's three part lists. */
static inline void free_parts(u8 *e)
{
    func_001C3A60(PS2_ADDR(e));
    func_001C4AC0(PS2_ADDR(e));
    func_001C4FF0(PS2_ADDR(e));
}

/* 0x001C1360, 0xDC bytes. Ends a world effect: its sound, its follow slot, out of the layer's
 * list, its parts freed, back to the free list. */
void func_001C1360(u8 *e)
{
    u8 *l = g_0072D120[g_70000D60] - 0x30;

    if (W32(e, 0x100) < 0xFF)
        func_002AF070(W32(e, 0x100));
    if (W32(e, 0x108) < 5 && g_006D3370[W32(e, 0x108)] == e)
        g_006D3370[W32(e, 0x108)] = 0;
    PS2_STOREP(u8 *, (*(u8 **)(e + 0xF0) + 0xF4), *(u8 **)(e + 0xF4));
    if (PS2_LOADP(u8 *, (l + 0x380)) == e)
        PS2_STOREP(u8 *, (l + 0x380), *(u8 **)(e + 0xF0));
    if (PS2_LOADP(u8 *, (e + 0xF4)) != 0)
        PS2_STOREP(u8 *, (*(u8 **)(e + 0xF4) + 0xF0), *(u8 **)(e + 0xF0));
    free_parts(e);
    func_001CB3D0(e);
}

/* 0x001C1440, 0xEC bytes. Ends a unit effect: its two sounds, out of the list, its parts freed,
 * back to the free list (unless flag 0x8000000: only cleared). */
void func_001C1440(u8 *e)
{
    u8 *l = g_0072D120[g_70000D60] - 0x30;

    if (*(int *)(e + 0x110) != 0x40)
        func_0024F850(*(int *)(e + 0x110));
    if (*(int *)(e + 0x114) != 0x40)
        func_0024F850(*(int *)(e + 0x114));
    PS2_STOREP(u8 *, (*(u8 **)(e + 0x118) + 0x11C), *(u8 **)(e + 0x11C));
    if (PS2_LOADP(u8 *, (l + 0x384)) == e)
        PS2_STOREP(u8 *, (l + 0x384), *(u8 **)(e + 0x118));
    if (PS2_LOADP(u8 *, (e + 0x11C)) != 0)
        PS2_STOREP(u8 *, (*(u8 **)(e + 0x11C) + 0x118), *(u8 **)(e + 0x118));
    free_parts(e);
    if ((W32(e, 0x34) & 0x8000000) == 0) {
        func_001CB4A0(e);
    } else {
        *(u32 *)(e + 0xFC) = 0;
        *(u32 *)(e + 0x118) = 0;
        *(u32 *)(e + 0x11C) = 0;
    }
}

/* 0x001C1530, 0xB0 bytes. Ends a weapon effect: its trail, out of the list, freed. */
void func_001C1530(u8 *e)
{
    u8 *l = g_0072D120[g_70000D60] - 0x30;

    if (*(u32 *)(e + 0xFC) != 0)
        func_002404F0((PS2_LOADP(u8 *, (e + 0xF0)))[0x14E], e);
    PS2_STOREP(u8 *, (*(u8 **)(e + 0x108) + 0x10C), *(u8 **)(e + 0x10C));
    if (PS2_LOADP(u8 *, (l + 0x388)) == e)
        PS2_STOREP(u8 *, (l + 0x388), *(u8 **)(e + 0x108));
    if (PS2_LOADP(u8 *, (e + 0x10C)) != 0)
        PS2_STOREP(u8 *, (*(u8 **)(e + 0x10C) + 0x108), *(u8 **)(e + 0x108));
    free_parts(e);
    func_001CB570(e);
}

/* 0x001C15E0, 0x224 bytes. A sprite part's size from its description `d` (+0x38 / +0x3C the
 * size, +0x40 / +0x44 random ranges; flag 0x40 keeps the proportions) and its first frame
 * (flag 0x20: a random one of +8 x +4). */
void func_001C15E0(u8 *p, u8 *d, u32 flags)
{
    if (F32(d, 0x40) > 0.0f || F32(d, 0x44) > 0.0f) {
        F32(p, 0x290) = (F32(d, 0x40) * 0.5f + F32(d, 0x38) + 0.0f)
                        - F32(d, 0x40) / 65535.0f * (float)(RANDOM() % 0xFFFF);
        if ((flags & 0x40) == 0)
            F32(p, 0x294) = (F32(d, 0x44) * 0.5f + F32(d, 0x3C) + 0.0f)
                            - F32(d, 0x44) / 65535.0f * (float)(RANDOM() % 0xFFFF);
        else
            F32(p, 0x294) = (F32(p, 0x290) - F32(d, 0x38)) / F32(d, 0x38) * F32(d, 0x3C)
                            + F32(d, 0x3C) + 0.0f;
    } else {
        F32(p, 0x290) = F32(d, 0x38);
        F32(p, 0x294) = F32(d, 0x3C);
    }
    if ((flags & 0x20) == 0) {
        F32(p, 0x298) = 0.0f;
    } else {
        int n = *(int *)(d + 8) * *(int *)(d + 4);

        F32(p, 0x298) = (float)(n == 0 ? 0 : (int)RANDOM() % n);
    }
    W32(p, 0x280) = W32(p, 0x290);
    W32(p, 0x284) = W32(p, 0x294);
    W32(p, 0x288) = W32(d, 0x28);
    W32(p, 0x28C) = W32(d, 0x2C);
}

/* Copies four words. */
#define COPY16(d, s) do { int i_; for (i_ = 0; i_ < 4; i_++) ((u32 *)(d))[i_] = ((u32 *)(s))[i_]; } while (0)

/* 0x001C1810, 0xE8 bytes. A part's colours and motion from description `d`: four vectors, and
 * two more from the part's colour set (+0x268, entry +0x26C) or the description. */
void func_001C1810(u8 *p, u8 *d)
{
    u8 *set = PS2_LOADP(u8 *, (p + 0x268));

    COPY16(p + 0x2B0, d + 0x50);
    COPY16(p + 0x2C0, d + 0x60);
    COPY16(p + 0x2D0, d + 0xA0);
    COPY16(p + 0x2E0, d + 0xB0);
    if (set == 0 || PS2_LOADP(u8 *, (set + 8)) == 0)
        COPY16(p + 0x2F0, d + 0xF0);
    else
        COPY16(p + 0x2F0, PS2_LOADP(u8 *, (set + 8)) + *(int *)(p + 0x26C) * 0x10);
    set = PS2_LOADP(u8 *, (p + 0x268));
    if (set == 0 || PS2_LOADP(u8 *, (set + 0xC)) == 0)
        COPY16(p + 0x300, d + 0x100);
    else
        COPY16(p + 0x300, PS2_LOADP(u8 *, (set + 0xC)) + *(int *)(p + 0x26C) * 0x10);
}
