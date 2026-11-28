/*
 * unit_gauges.c - unit helpers between 0x002711F0 and 0x002723AC: the musou gauge (players'
 * maxima in the game settings, the others' in their battle officer record), low life, motion
 * picks by the unit's state, and the event scene's sound slots (16 of 0x20 bytes per player).
 * Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_UNIT_GAUGES_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00669D60[];
extern u8 g_006A3A30[][0xC0];
extern int g_00410B30[], g_00410B40[];
extern u16 g_00410B50[][5];
extern int g_0045D3E0;                   /* (small data) the player */
extern u8 *g_0045D530[2], *g_0045D538[2];

#define OFF(u) g_006A3A30[*(short *)((u) + 0x178)]
#define KIND_FLAGS(u, o) (*(u32 *)(*(u8 **)((u) + 0x210) + (o)))

int func_002A6910(int v, int a, u8 *r);
void func_002A5B10(u32 h);

/* 0x00271210, 0x64 bytes. Unit `u`'s musou gauge maximum. */
u32 func_00271210(u8 *u)
{
    if (u[0x14E] < 2)
        return *(short *)(g_00669D60 + 0xC4 + u[0x14E] * 0x48);
    return *(short *)(OFF(u) + 0x86);
}

/* 0x00271280, 0x80 bytes. How many times full it is. */
int func_00271280(u8 *u)
{
    u8 *o = OFF(u);
    short m;

    if (u[0x14E] < 2)
        m = *(short *)(g_00669D60 + 0xC4 + u[0x14E] * 0x48);
    else
        m = *(short *)(o + 0x86);
    if (m < 1)
        return 0;
    return *(short *)(o + 0x88) / m;
}

/* 0x002711F0, 0x20 bytes, matching. */
int func_002711F0(u8 *u)
{
    return func_00271280(u) > 0;
}

/* 0x00271300, 0x58 bytes. Whether the gauge is full. */
int func_00271300(u8 *u)
{
    short v = *(short *)(OFF(u) + 0x88);

    return func_00271210(u) <= v;
}

/* 0x00271360, 0x18 bytes. */
int func_00271360(int k)
{
    return g_00410B30[k];
}

/* 0x00271380, 0x18 bytes. */
int func_00271380(int k)
{
    return g_00410B40[k];
}

/* 0x002713A0, 0x94 bytes. Whether the unit's officer is at low life (under a quarter, at most
 * 50). */
int func_002713A0(u8 *u)
{
    u8 *o = OFF(u);

    if (o[0xB0] < 2) {
        int q = *(short *)(o + 0x80) / 4, lim = q < 0x32 ? q : 0x32;

        return *(short *)(o + 0x82) < lim;
    }
    return 1;
}

/* 0x00271440, 0x100 bytes. The unit's idle motion by its state. */
u16 func_00271440(u8 *u)
{
    int low = func_002713A0(u);
    u16 *t = g_00410B50[u[0x182]];

    if ((KIND_FLAGS(u, 0x18) & 0x8000000) == 0) {
        if ((u[0x19D] & 0x20) != 0)
            return t[2];
        return low == 0 ? t[0] : t[1];
    }
    return low == 0 ? t[3] : t[4];
}

/* 0x00271540, 0x74 bytes. */
int func_00271540(u8 *u)
{
    int b = (u[0x19F] & 2) != 0;

    if ((KIND_FLAGS(u, 0x18) & 0x8000000) == 0) {
        if ((u[0x19D] & 0x20) != 0)
            return 0xDE;
        return b ? 0xDB : 0xC6;
    }
    return b ? 0xC4 : 0xC2;
}

/* 0x002715C0, 0x48 bytes. */
int func_002715C0(u8 *u)
{
    if ((KIND_FLAGS(u, 0x1C) & 0x20000) == 0 || (int)*(float *)(u + 0x21C) < 0x1E)
        return 0;
    return 1;
}

/* 0x00272110, 0x4C bytes, matching. The player's sound slots. */
void func_00272110(void)
{
    g_0045D538[g_0045D3E0] = func_0020EC50(0x200);
    g_0045D530[g_0045D3E0] = func_0020EC50(0x20);
}

/* 0x00272160, 0x40 bytes. A free slot (0: none). */
u8 *func_00272160(void)
{
    u8 *r = g_0045D538[g_0045D3E0];
    int i;

    for (i = 0; i < 0x10; i++, r += 0x20) {
        if (r[0x1C] == 0)
            return r;
    }
    return 0;
}

/* 0x002721A0, 0x50 bytes. The slot playing sound `k` (0: none). */
u8 *func_002721A0(int k)
{
    u8 *r = g_0045D538[g_0045D3E0];
    int i = 0;

    while (r[0x1C] == 0 || *(int *)(r + 0x18) != k) {
        i++;
        r += 0x20;
        if (i > 0xF)
            return 0;
    }
    return r;
}

/* 0x002721F0, 0x68 bytes. Starts sound `s` in slot `r` (for 60 frames). */
void func_002721F0(u8 *r, u32 s)
{
    int v, h;

    *(int *)(r + 0x18) = s & 0xFFFF;
    v = func_002A64C0(s & 0xFFFF);
    *(int *)(r + 0x18) = v;
    h = func_002A6910(v, 0, r);
    *(int *)(r + 0x14) = h;
    r[0x1C] = h != 0x107;
    *(float *)(r + 0x10) = 60.0f;
}

/* 0x00272260, 0x60 bytes, matching. Frees the slots whose time is over. */
void func_00272260(void)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0 && *(float *)(r + 0x10) <= 0.0f)
            r[0x1C] = 0;
    }
}

/* 0x002722C0, 0x50 bytes, matching. */
void func_002722C0(float dt)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0)
            *(float *)(r + 0x10) -= dt;
    }
}

/* 0x00272310, 0x94 bytes. Stops every slot's sound. */
void func_00272310(void)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0) {
            u32 h = *(u32 *)(r + 0x14);

            if (h < 0xF3 || h > 0x106)
                func_0023ACC0(*(u32 *)(r + 0x18), 0);
            else
                func_002A5B10(h);
        }
    }
}

/* ---- Event sound commands and the sound listener (gp 0x0045D530 per player: position, the
 * position followed, its mode), parts of 0x00272780-0x00272ECC. ---- */

extern u8 g_00730730[2][0x240];          /* the players' cameras, from +0x1C0 */
extern void (*g_00410CE0[9])(u8 *p);

#define ARG(p, out) do {                                                \
    u8 t_ = *(*(u8 **)((p) + 0x10))++;                                  \
    u8 s_ = *(*(u8 **)((p) + 0x14))++;                                  \
    *(u32 *)((p) + 0xC) = func_001D6BD0((void *)(out), (unsigned int *)PS2_PTR(*(u32 *)((p) + 0xC)), t_, s_); \
} while (0)

#define LISTENER() g_0045D530[g_0045D3E0]

/* 0x00272780, 0x64 bytes. Sets what the listener follows. */
void func_00272780(u8 *p)
{
    u8 *l = LISTENER();

    ARG(p, l + 0x14);
}

/* 0x002727F0, 0x20 bytes, matching. */
void func_002727F0(void)
{
    func_0023B3C0(0, 1);
}

/* 0x00272810, 0x88 bytes. Lets sound `k` play on (100 seconds). */
void func_00272810(u8 *p)
{
    u16 k;
    u8 *r;

    ARG(p, &k);
    r = func_002721A0(k);
    if (r != 0)
        *(float *)(r + 0x10) = 6000.0f;
}

/* 0x002728A0, 0x8C bytes. Stops sound `k`. */
void func_002728A0(u8 *p)
{
    u16 k;
    u8 *r;

    ARG(p, &k);
    r = func_002721A0(k);
    if (r != 0) {
        func_002A5B10(*(u32 *)(r + 0x14));
        r[0x1C] = 0;
    }
}

/* 0x00272930, 0xB0 bytes. Plays effect `s`. */
void func_00272930(u8 *p)
{
    u16 s;
    u8 *r;

    ARG(p, &s);
    r = func_00272160();
    if (r != 0) {
        *(int *)(r + 0x18) = func_002A64C0(s);
        *(int *)(r + 0x14) = 0x107;
        r[0x1C] = 1;
        *(float *)(r + 0x10) = 60.0f;
        func_0023AD10(*(u32 *)(r + 0x18), 0x107, 0x2CDC, 0x2CDC, 0x1000);
    }
}

/* 0x002729E0, 0x90 bytes. Stops effect `k`. */
void func_002729E0(u8 *p)
{
    u16 k;
    u8 *r;

    ARG(p, &k);
    r = func_002721A0(k);
    if (r != 0) {
        func_0023ACC0(*(u32 *)(r + 0x18), *(int *)(r + 0x14));
        r[0x1C] = 0;
    }
}

/* 0x00272B60, 0xA0 bytes. The listener's frame (on the camera or its target). */
void func_00272B60(u8 *p)
{
    u8 *l = LISTENER();
    u32 *t = *(u32 **)(l + 0x10), *s = 0;

    if (*(short *)(l + 0x14) == 0)
        s = (u32 *)(g_00730730[g_0045D3E0] + 0);
    else if (*(short *)(l + 0x14) == 1)
        s = (u32 *)(g_00730730[g_0045D3E0] + 0x10);
    if (s != 0) {
        t[0] = s[0];
        t[1] = s[1];
        t[2] = s[2];
        t[3] = s[3];
    }
    func_00272260();
}

/* 0x00272C00, 0x5C bytes. Ends the event scene's sounds (the listener's place back). */
void func_00272C00(u8 *p)
{
    u32 *l = (u32 *)LISTENER(), *t = (u32 *)l[4];

    if (t != 0) {
        t[0] = l[0];
        t[1] = l[1];
        t[2] = l[2];
        t[3] = l[3];
        l[4] = 0;
    }
    func_00272310();
    func_0023AA40();
    func_0023B3C0(1, 0);
}

/* 0x00272C60, 0x1C bytes, matching. */
void func_00272C60(float dt, u8 *e)
{
    func_002722C0(dt);
}

/* 0x00272C80, 0x7C bytes. Starts them (keeping the player's place). */
void func_00272C80(u8 *e)
{
    u32 *l, *t;

    func_00272110();
    l = (u32 *)LISTENER();
    *(short *)(l + 5) = 0;
    if (l[4] == 0)
        l[4] = (u32)(*(u8 **)(g_006A3A30[g_0045D3E0 == 0 ? 0 : 1] + 0x14) + 0x40);
    t = (u32 *)l[4];
    l[0] = t[0];
    l[1] = t[1];
    l[2] = t[2];
    l[3] = t[3];
}

/* 0x00272D00, 0x4C bytes, matching. Runs the event command by its kind. */
void func_00272D00(u8 *p)
{
    u8 k = (*(u8 **)(p + 8))[5];

    if (k < 9 && g_00410CE0[k] != 0)
        g_00410CE0[k](p);
}

/* 0x00272D50, 0xEC bytes. Whether the player unit uses weapon kind 0x28's special attack. */
int func_00272D50(u8 *u)
{
    short s;

    if (u[0x14E] >= 2 || OFF(u)[0xB2] >= 0x35)
        return 0;
    if (func_002F6A60(*(u32 *)(g_00669D60 + 0x88 + u[0x14E] * 0x48)) != 0x28)
        return 0;
    s = **(short **)(u + 0x210);
    if (s == 0x10 || s == 0x11 || s == 0x12)
        return (KIND_FLAGS(u, 0x18) & 0x8000000) == 0;
    return 0;
}

/* 0x00272E40, 0x90 bytes. */
int func_00272E40(u8 *u)
{
    if (u[0x14E] >= 2 || OFF(u)[0xB2] >= 0x35)
        return 0;
    return func_002F6A60(*(u32 *)(g_00669D60 + 0x88 + u[0x14E] * 0x48)) == 0x29;
}

/* ---- Special weapon checks: whether player unit `u` holds special weapon kind `k` and is in
 * the state its extra attack needs (parts of 0x00272ED0-0x00274A1C). ---- */

extern u8 g_0076F62F, g_0076F630, g_0076F614, g_0076F3D5;
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_00273E40(void);

/* Player unit `u`'s special weapon (-1: none). */
static int player_weapon(u8 *u)
{
    if (u[0x14E] >= 2 || OFF(u)[0xB2] >= 0x35)
        return -1;
    return func_002F6A60(*(u32 *)(g_00669D60 + 0x88 + u[0x14E] * 0x48));
}

/* Whether the motion's hit window holds the current frame. */
#define IN_WINDOW(u, m) ((int)*(float *)((u) + 0x21C) >= (m)[5] &&                        \
                         (int)*(float *)((u) + 0x21C) <= (m)[6] + 1)

/* 0x00272ED0, 0x140 bytes. */
int func_00272ED0(u8 *u, u8 *w)
{
    u8 *m;
    u32 f;

    if (player_weapon(u) != 0x2A)
        return 0;
    m = *(u8 **)(u + 0x214);
    if (m == 0)
        return 0;
    f = *(u32 *)(m + 0x18);
    if ((f & 0x10) != 0 || (f & 0x20000) != 0)
        return 0;
    if (20.0f < *(float *)(u + 0x23C))
        return 0;
    f = KIND_FLAGS(w, 0x18);
    return (f & 0x8000000) == 0 && (f & 0x20) == 0;
}

/* 0x00273010, 0xD0 bytes. */
int func_00273010(u8 *u)
{
    u32 f;

    if (player_weapon(u) != 0x2B)
        return 0;
    f = KIND_FLAGS(u, 0x18);
    return (f & 0x20) != 0 && (f & 0x800) != 0;
}

/* 0x002730E0, 0xF8 bytes. */
int func_002730E0(u8 *u)
{
    u32 f;

    if (player_weapon(u) != 0x2C)
        return 0;
    f = KIND_FLAGS(u, 0x18);
    if ((f & 0x800) == 0 || (f & 0x400) != 0 || (f & 0x20) != 0)
        return 0;
    return (f & 0x8000000) == 0;
}

/* 0x002731E0, 0x108 bytes. */
int func_002731E0(u8 *u)
{
    u8 *m;

    if (player_weapon(u) != 0x2D || (u[0x27C] & 8) == 0 || (KIND_FLAGS(u, 0x18) & 0x400000) == 0)
        return 0;
    m = *(u8 **)(*(u8 **)(u + 0x210) + 0x14);
    return m != 0 && (*(u32 *)(m + 0x28) & 1) != 0;
}

/* 0x002732F0, 0x128 bytes. */
int func_002732F0(u8 *u)
{
    u8 *m;

    if (player_weapon(u) != 0x2E)
        return 0;
    m = *(u8 **)(*(u8 **)(u + 0x210) + 0x14);
    if ((KIND_FLAGS(u, 0x18) & 0x400000) == 0)
        return 0;
    if (m == 0 || (*(u32 *)(m + 0x28) & 1) == 0)
        return 0;
    return IN_WINDOW(u, m);
}

/* 0x00273420, 0x140 bytes. */
int func_00273420(u8 *u)
{
    u8 *m;
    u32 f;

    if (player_weapon(u) != 0x2F)
        return 0;
    m = *(u8 **)(*(u8 **)(u + 0x210) + 0x14);
    f = KIND_FLAGS(u, 0x18);
    if ((f & 0x400000) == 0 || (f & 0x40000) != 0)
        return 0;
    if (m == 0 || (*(u32 *)(m + 0x28) & 1) == 0)
        return 0;
    return IN_WINDOW(u, m);
}

/* 0x00273560, 0xB4 bytes. */
int func_00273560(u8 *u, u8 *w)
{
    if (player_weapon(u) != 0x30)
        return 0;
    return (*(u32 *)(w + 0x28) & 0x20000000) != 0;
}

/* 0x00273620, 0x150 bytes. */
int func_00273620(u8 *u, u8 *w)
{
    u8 *o;
    u32 f;

    if (player_weapon(u) != 0x31)
        return 0;
    o = OFF(u);
    if (*(short *)(o + 0x88) < *(short *)(o + 0x86))
        return 0;
    f = KIND_FLAGS(u, 0x18);
    if ((f & 0x400) != 0 || (f & 0x20) != 0)
        return 0;
    f = *(u32 *)(w + 0x28);
    return (f & 1) == 0 && (f & 4) == 0 && (f & 8) == 0 && (f & 0x10) == 0
        && (f & 0x4000000) == 0;
}

/* 0x00273940, 0xDC bytes. */
int func_00273940(u8 *u)
{
    short s;

    if (player_weapon(u) != 0x33)
        return 0;
    s = **(short **)(u + 0x210);
    return s == 0x10 || s == 0x11 || s == 0x12;
}

/* 0x00273A20, 0x90 bytes. */
int func_00273A20(u8 *u)
{
    return player_weapon(u) == 0x34;
}

/* 0x00273AB0, 0x58 bytes. */
void func_00273AB0(void)
{
    if (g_0076F62F == 0)
        g_0076F630 = 0;
    else
        g_0076F630 = RANDOM() % g_0076F62F;
}

/* 0x002743E0, 0x1C bytes, matching. */
void func_002743E0(void)
{
    func_00273E40();
}

/* 0x002744C0, 0x84 bytes. A 75-frame cycle: frames 0-6 in its first third, else 0. */
u32 func_002744C0(void)
{
    u32 v = (g_0076F614 + 1) % 0x4B, r = 0;

    g_0076F614 = v;
    if (g_0076F614 < 0x1A) {
        r = v / 3;
        if ((int)r < 0)
            r = 0;
        else if (r > 6)
            r = 6;
    }
    return r;
}

/* 0x00274A10, 0x10 bytes. */
void func_00274A10(void)
{
    g_0076F3D5 = 0xC;
}
