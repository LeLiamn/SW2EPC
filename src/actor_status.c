/*
 * actor_status.c - the battle actors' status effects (boosts, auras, elements): each running
 * status is a record whose word 0 is its kind (a bit of the actor's mask at 0x0076E700, 0x19 =
 * none); its handlers start, follow and end the effects that show it. Original file name unknown
 * (0x0024FA00-0x0025407C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. VU0 vector code is written as plain float loops.
 *
 * Status record (u32 words): [0] kind, [2] step, [4] level, [7] / [8] time and speed, [0xA] done,
 * [0xB] the other actor, [0xC-0x19] effects, +0x70 / +0x80 / +0x90 vectors.
 */

#define SW2E_FILE_ACTOR_STATUS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_0076E700[];                 /* per actor: its status bits */
extern u8 g_00755D30[];                  /* per actor: its running statuses */
extern u8 g_00755060[0x40][0x20];        /* the item glows */
extern u8 *g_00755020[0x10];
extern u32 g_0045D344;                   /* (small data) the effects' detail level */
extern float g_0045CDE4;                 /* (small data) */
extern u8 g_00410A40[12], g_00410A50[12], g_00410A60[14], g_00410A70[11];
extern u8 g_00669D60[];

#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))    /* (scratchpad) the effect layer */
#define g_70000030 ((float *)PS2_PTR(0x70000030))   /* (scratchpad) the camera position */
#define g_70000150 (*(int *)PS2_PTR(0x70000150))
#define g_70000158 (*(u32 *)PS2_PTR(0x70000158))
#define SETTINGS_FLAGS (*(u32 *)(g_00669D60 + 0x200))

void func_001C7F30(int k, float *pos, int c, u32 f);
u32 func_0024E790(u32 v, u8 *g);
u32 func_002A81C0(u32 a, u32 b, u8 *c, u32 d);

/* The effect flags of actor `a` (0x200 when it is in view?). */
static u32 fx_flags(u8 *a)
{
    return func_0016C040(a) != 0 ? 0x200 : 0;
}

/* Ends status `st` of actor `a`. */
static void status_end(u8 *a, u32 *st)
{
    g_0076E700[a[0x14E]] &= ~(1 << (st[0] & 0x1F));
    st[0] = 0x19;
    g_00755D30[a[0x14E]]--;
}

/* `out` = halfway between `p` and `q`. */
static void midpoint(float *out, const float *p, const float *q)
{
    int k;

    for (k = 0; k < 4; k++)
        out[k] = (q[k] - p[k]) * 0.5f + p[k];
}

/* `out` = `p` + (`q` - `p`) * `t`. */
static void lerp4(float *out, const float *p, const float *q, float t)
{
    int k;

    for (k = 0; k < 4; k++)
        out[k] = (q[k] - p[k]) * t + p[k];
}

/* Node `n`'s position of actor `a`. */
#define NODE_POS(a, n) ((float *)(((u8 *)func_0016A170((a), (n))) + 0x30))

/* Stops effect `e`. */
#define FX_STOP(e) (*(u32 *)((e) + 0x38) |= 8)

/* 0x0024FA00, 0x7C bytes. Draws the item glows above the ground ones. */
void func_0024FA00(void)
{
    u32 v = g_70000158, k;

    for (k = 0; k < 0x40; k++) {
        u8 *g = g_00755060[k];

        if (g[0x1D] != 0 && *(u32 *)(g + 0x14) > 0x2F)
            v = func_0024E790(v, g);
    }
    g_70000158 = v;
}

/* 0x0024FA80, 0xCC bytes. Draws the glows on actors. */
u32 func_0024FA80(u32 v)
{
    u32 k;

    for (k = 0; k < 0x40; k++) {
        u8 *g = g_00755060[k], *m;

        if (g[0x1D] != 0 && *(u32 *)(g + 0x14) < 0x30 && (m = *(u8 **)(g_00755020[g[0x1F]] + 0x18)) != 0) {
            u32 c = PS2_ADDR(func_001CCD20((unsigned int *)PS2_PTR(v), *(u32 *)(m + 0x27C), *(u32 *)(m + 0x270)));

            v = func_002A81C0(*(u32 *)(g + 8), c, m + g_70000150 * 0x130, *(u32 *)(g + 0x14));
        }
    }
    return v;
}

/* 0x0024FB50, 0x15C bytes. Starts the ring status (hand sparks and a ground ring). */
int func_0024FB50(u8 *a, u32 *st)
{
    u32 f;

    if (g_0045D344 < 3 || (a[0x19C] & 0x80) != 0) {
        g_0076E700[a[0x14E]] &= ~(1 << (st[0] & 0x1F));
        st[0] = 0x19;
        g_00755D30[a[0x14E]]--;
        return 0;
    }
    f = fx_flags(a);
    g_70000D60 = 0;
    func_001C7F30(0xF, NODE_POS(a, 7), 0, f | 8);
    func_001C7F30(0xF, NODE_POS(a, 6), 0, f | 8);
    st[2] = 0;
    st[7] = 0;
    *(float *)&st[8] = 0.2f;
    st[0xE] = (u32)PS2_ADDR(func_001C8340(0x10, (unsigned char *)((float *)(a + 0x40)), 0, f));
    func_0021A3B0(4, PS2_ADDR(a + 0x40));
    return 1;
}

/* 0x0024FCB0, 0x224 bytes. The ring status: sparks run along the body's node chains. */
void func_0024FCB0(u8 *a, u32 *st)
{
    float t = *(float *)&st[7] + *(float *)&st[8];

    *(float *)&st[7] = t;
    if (t < 1.0f)
        return;
    st[7] = 0;
    st[2] = (st[2] + 1) % 0xC;
    if (st[2] >= 0xB) {
        func_0024FB50(a, st);
        return;
    }
    if (g_00410A40[st[2] + 1] != '.') {
        u32 f = fx_flags(a);

        g_70000D60 = 0;
        lerp4((float *)((u8 *)st + 0x70), NODE_POS(a, g_00410A40[st[2]]),
              NODE_POS(a, g_00410A40[(st[2] + 1) % 0xC]), *(float *)&st[7]);
        func_001C7F30(0xF, (float *)((u8 *)st + 0x70), 0, f | 8);
        lerp4((float *)((u8 *)st + 0x80), NODE_POS(a, g_00410A50[st[2]]),
              NODE_POS(a, g_00410A50[(st[2] + 1) % 0xC]), *(float *)&st[7]);
        func_001C7F30(0xF, (float *)((u8 *)st + 0x80), 0, f | 8);
    }
}

int func_0024FF60(u8 *a, u32 *st, int level);

/* 0x0024FEE0, 0x1C bytes, matching. */
int func_0024FEE0(u8 *a, u32 *st, int level)
{
    return func_0024FF60(a, st, level);
}

void func_00250120(u8 *a, u32 *st, int level);
void func_00250190(u8 *a, u32 *st, int level);

/* 0x0024FF00, 0x5C bytes, matching. The level status follows the current level. */
void func_0024FF00(u8 *a, u32 *st)
{
    int v = func_00271280(a);

    func_00250120(a, st, v);
    func_00250190(a, st, v);
}

/* 0x0024FF60, 0x1B4 bytes. Starts the level status (level 1-3: 14 body glows). */
int func_0024FF60(u8 *a, u32 *st, int level)
{
    u32 f, k1, k2, k3, k;

    if (g_0045D344 < 0xE) {
        st[0xA] = 1;
        return 0;
    }
    st[4] = level;
    g_70000D60 = 0;
    f = fx_flags(a);
    if (level == 3) {
        k1 = 0x18;
        k2 = 0x19;
        k3 = 0x1A;
    } else if (level == 2) {
        k1 = 0x15;
        k2 = 0x16;
        k3 = 0x17;
    } else {
        k1 = 0x12;
        k2 = 0x13;
        k3 = 0x14;
    }
    f |= 1;
    for (k = 0; k < 9; k++)
        st[0xC + k] = (u32)PS2_ADDR(func_001C8340(k1, (void *)NODE_POS(a, g_00410A60[k]), 0, f));
    for (k = 9; k < 0xD; k++)
        st[0xC + k] = (u32)PS2_ADDR(func_001C8340(k2, (void *)NODE_POS(a, g_00410A60[k]), 0, f));
    st[0x19] = (u32)PS2_ADDR(func_001C8340(k3, (void *)NODE_POS(a, g_00410A60[0xD]), 0, f));
    return 1;
}

/* 0x00250120, 0x64 bytes. The level status ends at level 0. */
void func_00250120(u8 *a, u32 *st, int level)
{
    if (level < 1)
        status_end(a, st);
}

/* Stops the level status's 14 glows. */
static void stop_glows(u32 *st)
{
    u32 k;

    for (k = 0; k < 0xE; k++) {
        u8 *e = (u8 *)PS2_PTR(st[0xC + k]);

        if (e != 0) {
            FX_STOP(e);
            st[0xC + k] = 0;
        }
    }
}

/* 0x00250190, 0x180 bytes. The level status: the glows follow their nodes, restarted when the
 * level changes. */
void func_00250190(u8 *a, u32 *st, int level)
{
    u32 k;

    if (level < 1) {
        stop_glows(st);
        return;
    }
    if (level == (int)st[4] || (a[0x19C] & 2) != 0) {
        for (k = 0; k < 0xE; k++) {
            if (st[0xC + k] == 0) {
                stop_glows(st);
                st[0xA] = 1;
            } else {
                *(float **)((u8 *)PS2_PTR(st[0xC + k]) + 0xF0) = NODE_POS(a, g_00410A60[k]);
            }
        }
        return;
    }
    stop_glows(st);
    if (func_0024FEE0(a, st, level) == 0)
        st[0xA] = 1;
}

int func_00250350(u8 *a, u32 *st);
void func_00250410(u8 *a, u32 *st);
int func_002504B0(u8 *a, u32 *st);
void func_00250570(u8 *a, u32 *st);

/* 0x00250310, 0x1C bytes, matching. */
int func_00250310(u8 *a, u32 *st)
{
    return func_00250350(a, st);
}

/* 0x00250330, 0x1C bytes, matching. */
void func_00250330(u8 *a, u32 *st)
{
    func_00250410(a, st);
}

/* Starts a head halo `k` turned toward the camera. */
static int halo_start(u8 *a, u32 *st, int k)
{
    float *h = NODE_POS(a, 10), *p = (float *)((u8 *)st + 0x70), *d = (float *)((u8 *)st + 0x90);
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    g_70000D60 = 0;
    p[0] = h[0];
    p[1] = h[1];
    p[2] = h[2];
    p[3] = h[3];
    d[0] = g_70000030[0];
    d[1] = g_70000030[1];
    d[2] = g_70000030[2];
    d[3] = g_70000030[3];
    st[0xC] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), PS2_ADDR(d), f | 1));
    return 1;
}

/* 0x00250350, 0xB8 bytes. Starts the halo status (effect 0xE). */
int func_00250350(u8 *a, u32 *st)
{
    return halo_start(a, st, 0xE);
}

/* 0x00250410, 0x54 bytes. The halo follows the head and turns. */
void func_00250410(u8 *a, u32 *st)
{
    float *h = NODE_POS(a, 10), *p = (float *)((u8 *)st + 0x70);

    p[0] = h[0];
    p[1] = h[1];
    p[2] = h[2];
    p[3] = h[3];
    *(float *)((u8 *)st + 0x94) += 0.0418879f;
}

/* 0x00250470, 0x1C bytes, matching. */
int func_00250470(u8 *a, u32 *st)
{
    return func_002504B0(a, st);
}

/* 0x00250490, 0x1C bytes, matching. */
void func_00250490(u8 *a, u32 *st)
{
    func_00250570(a, st);
}

/* 0x002504B0, 0xB8 bytes. Starts the second halo status (effect 0xD8). */
int func_002504B0(u8 *a, u32 *st)
{
    return halo_start(a, st, 0xD8);
}

/* 0x00250570, 0x64 bytes. The second halo sits a little higher. */
void func_00250570(u8 *a, u32 *st)
{
    float *h = NODE_POS(a, 10), *p = (float *)((u8 *)st + 0x70);

    p[0] = h[0];
    p[1] = h[1];
    p[2] = h[2];
    p[3] = h[3];
    p[1] += g_0045CDE4;
    *(float *)((u8 *)st + 0x94) += 0.0418879f;
}

/* 0x002505E0, 0x14C bytes. Starts effect `k` between the hands. */
int func_002505E0(u8 *a, u32 *st, int k)
{
    float *r = NODE_POS(a, 7), *l = NODE_POS(a, 6), *p = (float *)(st + 0x1C);
    u32 f;

    if (g_0045D344 == 0) {
        status_end(a, st);
        return 0;
    }
    f = fx_flags(a);
    midpoint(p, r, l);
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, f));
    return 1;
}

/* 0x00250730, 0x134 bytes. The effect between the hands follows them (ends with it). */
void func_00250730(u8 *a, u32 *st)
{
    float *r = NODE_POS(a, 7), *l = NODE_POS(a, 6);
    u8 *e = (u8 *)PS2_PTR(st[0xC]);

    if (1.0f <= *(float *)(e + 0x28) && (*(u32 *)(e + 0x34) & 1) == 0) {
        status_end(a, st);
        st[0xC] = 0;
        return;
    }
    midpoint((float *)(st + 0x1C), r, l);
}

/* 0x00250870, 0x1E4 bytes. Starts the weapon status (by weapon kind 0xB / 0x18 / 0x17: effects
 * 0x28-0x2A on 11 nodes). */
int func_00250870(u8 *a, u32 *st)
{
    int w;
    u32 k, f, j;

    if (g_0045D344 < 0xB || (a[0x19C] & 0x80) != 0) {
        status_end(a, st);
        return 0;
    }
    w = *(int *)(a + 0x118);
    if (w == 0xB)
        k = 0x28;
    else if (w == 0x18)
        k = 0x29;
    else if (w == 0x17)
        k = 0x2A;
    else
        k = 0x18B;
    if (k >= 0x18B) {
        status_end(a, st);
        return 0;
    }
    f = fx_flags(a);
    for (j = 0; j < 0xB; j++) {
        float *p = NODE_POS(a, g_00410A70[j]);

        g_70000D60 = 0;
        st[0xC + j] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, f | 8));
    }
    return 1;
}

/* 0x00250A60, 0x164 bytes. The weapon status: its effects follow the nodes (all end with the
 * first). */
void func_00250A60(u8 *a, u32 *st)
{
    u8 *e = (u8 *)PS2_PTR(st[0xC]);
    int over = 0;
    u32 k;

    if (1.0f <= *(float *)(e + 0x28))
        over = (*(u32 *)(e + 0x34) & 1) == 0;
    if (over || (*(u32 *)(e + 0x38) & 0xC) != 0) {
        status_end(a, st);
        for (k = 0; k < 0xB; k++)
            st[0xC + k] = 0;
        return;
    }
    for (k = 0; k < 0xB; k++) {
        if (st[0xC + k] != 0)
            *(float **)((u8 *)PS2_PTR(st[0xC + k]) + 0xF0) = NODE_POS(a, g_00410A70[k]);
    }
}

int func_00250C10(u8 *a, u32 *st);
void func_00250D00(u8 *a, u32 *st);

/* 0x00250BD0, 0x1C bytes, matching. */
int func_00250BD0(u8 *a, u32 *st)
{
    return func_00250C10(a, st);
}

/* 0x00250BF0, 0x1C bytes, matching. */
void func_00250BF0(u8 *a, u32 *st)
{
    func_00250D00(a, st);
}

/* 0x00250C10, 0xEC bytes. Starts the musou status (a ground effect and one by weapon kind). */
int func_00250C10(u8 *a, u32 *st)
{
    float *p = NODE_POS(a, 0);
    int w;
    u32 k;

    if (g_0045D344 < 2) {
        st[0xA] = 1;
        return 0;
    }
    w = *(int *)(a + 0x118);
    if (w == 0xB)
        k = 0x2C;
    else if (w == 0x18)
        k = 0x2D;
    else
        k = 0x2E;
    if ((SETTINGS_FLAGS & 2) == 0) {
        g_70000D60 = 3;
        st[0xC] = (u32)PS2_ADDR(func_001C8340(0x2B, (unsigned char *)(p), 0, 0x209));
    }
    g_70000D60 = 0;
    st[0xD] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, 0x209));
    return 1;
}

/* 0x00250D00, 0xB8 bytes. The musou status follows the root and fades with the gauge. */
void func_00250D00(u8 *a, u32 *st)
{
    float *p = NODE_POS(a, 0);

    if ((SETTINGS_FLAGS & 2) == 0 && st[0xC] != 0) {
        *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = p;
        *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
    if (st[0xD] != 0) {
        *(float **)((u8 *)PS2_PTR(st[0xD]) + 0xF0) = p;
        *(float *)((u8 *)PS2_PTR(st[0xD]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
}

extern u8 g_0045CDE8[7];                 /* (small data) the nodes of the seven-glow statuses */

int func_00250E30(u8 *a, u32 *st);
void func_00251000(u8 *a, u32 *st);
void func_002510F0(u8 *a, u32 *st);

/* 0x00250DC0, 0x1C bytes, matching. */
int func_00250DC0(u8 *a, u32 *st)
{
    return func_00250E30(a, st);
}

/* 0x00250DE0, 0x4C bytes, matching. */
void func_00250DE0(u8 *a, u32 *st)
{
    func_00251000(a, st);
    if (st[0] != 0x19)
        func_002510F0(a, st);
}

/* 0x00250E30, 0x1D0 bytes. Starts the link status between actor `a` and its partner (+0x284):
 * an effect halfway between their chests (0xC with a player, else 0xCD). */
int func_00250E30(u8 *a, u32 *st)
{
    u8 *o = *(u8 **)(a + 0x284);
    float *p = (float *)(st + 0x1C);
    u32 k, f;

    if (o == 0) {
        status_end(a, st);
        return 0;
    }
    if (*(int *)(a + 0x11C) == 0 || *(int *)(o + 0x11C) == 0 || g_0045D344 == 0 || (a[0x27C] & 4) == 0)
        return 0;
    st[0xB] = (u32)PS2_ADDR(o);
    midpoint(p, NODE_POS(o, 1), NODE_POS(a, 1));
    if (a[0x14E] < 2 || ((u8 *)PS2_PTR(st[0xB]))[0x14E] < 2) {
        func_00229050(0);
        k = 0xC;
    } else {
        k = 0xCD;
    }
    f = func_0016C040(a) == 0 && func_0016C040((u8 *)PS2_PTR(st[0xB])) == 0 ? 0 : 0x200;
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, f | 9));
    return 1;
}

/* 0x00251000, 0xF0 bytes. The link status ends when the link breaks or the partner goes. */
void func_00251000(u8 *a, u32 *st)
{
    int linked = (a[0x27C] & 4) != 0;
    u32 k;

    if (linked || st[0xC] != 0 || st[0xD] != 0) {
        if (st[0xB] != 0 && linked && *(int *)((u8 *)PS2_PTR(st[0xB]) + 0x11C) == 0) {
            for (k = 0; k < 2; k++) {
                if (st[0xC + k] != 0) {
                    FX_STOP((u8 *)PS2_PTR(st[0xC + k]));
                    st[0xC + k] = 0;
                }
            }
            st[0xA] = 1;
        }
    } else {
        status_end(a, st);
        st[0xB] = 0;
    }
}

int func_002513D0(u8 *a, u32 *st);
void func_00251470(u8 *a, u32 *st);
void func_002514E0(u8 *a, u32 *st);

/* 0x00251370, 0x1C bytes, matching. */
int func_00251370(u8 *a, u32 *st)
{
    return func_002513D0(a, st);
}

/* 0x00251390, 0x3C bytes, matching. */
void func_00251390(u8 *a, u32 *st)
{
    func_00251470(a, st);
    func_002514E0(a, st);
}

/* 0x002513D0, 0x9C bytes. Starts the head mark status (effect 0x37). */
int func_002513D0(u8 *a, u32 *st)
{
    float *h = NODE_POS(a, 10);
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C8340(0x37, (unsigned char *)(h), 0, f | 1));
    return 1;
}

/* 0x00251470, 0x68 bytes. The head mark ends with its timer (+0x176). */
void func_00251470(u8 *a, u32 *st)
{
    if (*(short *)(a + 0x176) == 0)
        status_end(a, st);
}

/* 0x002514E0, 0x6C bytes. The head mark follows the head. */
void func_002514E0(u8 *a, u32 *st)
{
    float *h = NODE_POS(a, 10);

    if (*(short *)(a + 0x176) == 0) {
        if (st[0xC] != 0) {
            FX_STOP((u8 *)PS2_PTR(st[0xC]));
            st[0xC] = 0;
        }
    } else {
        *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = h;
    }
}

int func_00251590(u8 *a, u32 *st, int k1, int k2);
void func_00251680(u8 *a, u32 *st);

/* 0x00251550, 0x1C bytes, matching. */
int func_00251550(u8 *a, u32 *st, int k1, int k2)
{
    return func_00251590(a, st, k1, k2);
}

/* 0x00251570, 0x1C bytes, matching. */
void func_00251570(u8 *a, u32 *st)
{
    func_00251680(a, st);
}

/* 0x00251590, 0xF0 bytes. Starts a two-part ground status (effects `k1` and `k2`). */
int func_00251590(u8 *a, u32 *st, int k1, int k2)
{
    float *p = NODE_POS(a, 0);
    u32 f;

    if (g_0045D344 < 2) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    if ((SETTINGS_FLAGS & 2) == 0) {
        g_70000D60 = 3;
        st[0xC] = (u32)PS2_ADDR(func_001C8340(k1, (unsigned char *)(p), 0, f | 9));
    }
    g_70000D60 = 0;
    st[0xD] = (u32)PS2_ADDR(func_001C8340(k2, (unsigned char *)(p), 0, f | 9));
    return 1;
}

/* 0x00251680, 0xA8 bytes. It follows the root and fades with the gauge. */
void func_00251680(u8 *a, u32 *st)
{
    float *p = NODE_POS(a, 0);

    if ((SETTINGS_FLAGS & 2) == 0) {
        *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = (float)a[0x14D] / 128.0f;
        *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = p;
    }
    *(float *)((u8 *)PS2_PTR(st[0xD]) + 0x2C) = (float)a[0x14D] / 128.0f;
    *(float **)((u8 *)PS2_PTR(st[0xD]) + 0xF0) = p;
}

/* 0x00251730, 0x124 bytes. Starts effect `k` on seven body nodes. */
int func_00251730(u8 *a, u32 *st, int k)
{
    u32 j;

    if (g_0045D344 < 7) {
        status_end(a, st);
        return 0;
    }
    func_0016C040(a);
    for (j = 0; j < 7; j++) {
        float *p = NODE_POS(a, g_0045CDE8[j]);

        g_70000D60 = 0;
        st[0xC + j] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, 0x208));
    }
    return 1;
}

/* 0x00251860, 0x134 bytes. The seven effects follow their nodes (all end with the first). */
void func_00251860(u8 *a, u32 *st)
{
    u8 *e = (u8 *)PS2_PTR(st[0xC]);
    int over = 0;
    u32 k;

    if (1.0f <= *(float *)(e + 0x28))
        over = (*(u32 *)(e + 0x34) & 1) == 0;
    if (over || (*(u32 *)(e + 0x38) & 0xC) != 0) {
        for (k = 0; k < 7; k++)
            st[0xC + k] = 0;
        status_end(a, st);
        return;
    }
    for (k = 0; k < 7; k++)
        *(float **)((u8 *)PS2_PTR(st[0xC + k]) + 0xF0) = NODE_POS(a, g_0045CDE8[k]);
}

int func_00251A00(u8 *a, u32 *st, int k);
void func_00251AB0(u8 *a, u32 *st);
void func_00251B20(u8 *a, u32 *st);

/* 0x002519A0, 0x1C bytes, matching. */
int func_002519A0(u8 *a, u32 *st, int k)
{
    return func_00251A00(a, st, k);
}

/* 0x002519C0, 0x3C bytes, matching. */
void func_002519C0(u8 *a, u32 *st)
{
    func_00251AB0(a, st);
    func_00251B20(a, st);
}

/* 0x00251A00, 0xAC bytes. Starts a timed root status (effect `k`). */
int func_00251A00(u8 *a, u32 *st, int k)
{
    float *p = NODE_POS(a, 0);
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    st[1] = k;
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, f | 1));
    return 1;
}

/* 0x00251AB0, 0x68 bytes. It ends with its timer (+0x15C). */
void func_00251AB0(u8 *a, u32 *st)
{
    if (*(short *)(a + 0x15C) == 0)
        status_end(a, st);
}

/* 0x00251B20, 0xF8 bytes. It follows the root; in its last 18 counts the effect is left behind to
 * fade; restarted when lost. */
void func_00251B20(u8 *a, u32 *st)
{
    float *p = NODE_POS(a, 0);
    u16 t = *(u16 *)(a + 0x15C);

    if (t == 0) {
        if (st[0xC] != 0) {
            FX_STOP((u8 *)PS2_PTR(st[0xC]));
            st[0xC] = 0;
        }
    } else if (t < 0x12) {
        if (st[0xC] != 0) {
            float *q = (float *)(st + 0x1C);

            *(u32 *)((u8 *)PS2_PTR(st[0xC]) + 0x34) |= 0x800;
            q[0] = p[0];
            q[1] = p[1];
            q[2] = p[2];
            q[3] = p[3];
            *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = q;
            st[0xC] = 0;
        }
    } else if (st[0xC] == 0) {
        func_002519A0(a, st, st[1]);
    } else {
        *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = p;
        *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
}

extern u8 g_005B4D80[], g_005B4FC0[];    /* two screen-corner positions (by player) */
extern u8 g_005755A8;

/* Copies node `n`'s position into the record's first vector. */
static float *copy_node(u8 *a, u32 *st, int n)
{
    float *p = NODE_POS(a, n), *q = (float *)(st + 0x1C);

    q[0] = p[0];
    q[1] = p[1];
    q[2] = p[2];
    q[3] = p[3];
    return q;
}

/* Leaves the first effect where it stands (to fade) and forgets it. */
#define FX_LEAVE(st) (*(u32 *)((u8 *)PS2_PTR((st)[0xC]) + 0x34) |= 0x800, (st)[0xC] = 0)

int func_00251C80(u8 *a, u32 *st, int k);
void func_00251D90(u8 *a, u32 *st);
void func_00251E00(u8 *a, u32 *st);

/* 0x00251C20, 0x1C bytes, matching. */
int func_00251C20(u8 *a, u32 *st, int k)
{
    return func_00251C80(a, st, k);
}

/* 0x00251C40, 0x3C bytes, matching. */
void func_00251C40(u8 *a, u32 *st)
{
    func_00251D90(a, st);
    func_00251E00(a, st);
}

/* 0x00251C80, 0x10C bytes. Starts a charge status (effect `k` between the hands). */
int func_00251C80(u8 *a, u32 *st, int k)
{
    float *r = NODE_POS(a, 7), *l = NODE_POS(a, 6), *p = (float *)(st + 0x1C);
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    midpoint(p, r, l);
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C8340(k, (unsigned char *)(p), 0, f | 9));
    st[3] = 0;
    st[1] = k;
    return 1;
}

/* 0x00251D90, 0x68 bytes. The charge ends with its timer (+0x172). */
void func_00251D90(u8 *a, u32 *st)
{
    if (*(short *)(a + 0x172) == 0)
        status_end(a, st);
}

/* 0x00251E00, 0x294 bytes. The charge: it follows the hands, bursts (0x50 / 0x52) at the root in
 * its last 10 counts or when the timer runs out. */
void func_00251E00(u8 *a, u32 *st)
{
    u16 t = *(u16 *)(a + 0x172);

    if (t == 0) {
        if (st[0xC] != 0) {
            FX_STOP((u8 *)PS2_PTR(st[0xC]));
            st[0xC] = 0;
        }
        if (st[3] == 0) {
            u32 f = fx_flags(a);
            float *p = NODE_POS(a, 0);

            g_70000D60 = 1;
            func_001C8130(st[1] == 0x51 ? 0x52 : 0x50, PS2_ADDR(p), 0, f | 8, a[0x14E]);
        }
    } else if (t < 10) {
        if (st[0xC] != 0) {
            u32 f;
            float *p;

            st[3] = 1;
            f = fx_flags(a);
            midpoint((float *)(st + 0x1C), NODE_POS(a, 7), NODE_POS(a, 6));
            *(u32 *)((u8 *)PS2_PTR(st[0xC]) + 0x34) |= 0x400;
            st[0xC] = 0;
            p = NODE_POS(a, 0);
            g_70000D60 = 1;
            func_001C8130(st[0] == 0x10 ? 0x52 : 0x50, PS2_ADDR(p), 0, f | 8, a[0x14E]);
        }
    } else {
        midpoint((float *)(st + 0x1C), NODE_POS(a, 7), NODE_POS(a, 6));
        if (st[0xC] != 0)
            *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
}

int func_002520E0(u8 *a, u32 *st);
void func_00252190(u8 *a, u32 *st);
int func_00252290(u8 *a, u32 *st);
void func_00252340(u8 *a, u32 *st);

/* 0x002520A0, 0x1C bytes, matching. */
int func_002520A0(u8 *a, u32 *st)
{
    return func_002520E0(a, st);
}

/* 0x002520C0, 0x1C bytes, matching. */
void func_002520C0(u8 *a, u32 *st)
{
    func_00252190(a, st);
}

/* A ground status pair (effects `k1`, `k2` at the root). */
static int ground_pair(u8 *a, u32 *st, int k1, int k2)
{
    float *p = NODE_POS(a, 0);

    if (g_0045D344 < 2) {
        st[0xA] = 1;
        return 0;
    }
    if ((SETTINGS_FLAGS & 2) == 0) {
        g_70000D60 = 3;
        st[0xC] = (u32)PS2_ADDR(func_001C8340(k1, (unsigned char *)(p), 0, 0x209));
    }
    g_70000D60 = 0;
    st[0xD] = (u32)PS2_ADDR(func_001C8340(k2, (unsigned char *)(p), 0, 0x209));
    return 1;
}

/* It follows the root and fades with the gauge. */
static void ground_pair_step(u8 *a, u32 *st)
{
    float *p = NODE_POS(a, 0);

    if ((SETTINGS_FLAGS & 2) == 0 && st[0xC] != 0) {
        *(float **)((u8 *)PS2_PTR(st[0xC]) + 0xF0) = p;
        *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
    if (st[0xD] != 0) {
        *(float **)((u8 *)PS2_PTR(st[0xD]) + 0xF0) = p;
        *(float *)((u8 *)PS2_PTR(st[0xD]) + 0x2C) = (float)a[0x14D] / 128.0f;
    }
}

/* 0x002520E0, 0xB0 bytes. */
int func_002520E0(u8 *a, u32 *st)
{
    return ground_pair(a, st, 0x43, 0x44);
}

/* 0x00252190, 0xB8 bytes. */
void func_00252190(u8 *a, u32 *st)
{
    ground_pair_step(a, st);
}

/* 0x00252250, 0x1C bytes, matching. */
int func_00252250(u8 *a, u32 *st)
{
    return func_00252290(a, st);
}

/* 0x00252270, 0x1C bytes, matching. */
void func_00252270(u8 *a, u32 *st)
{
    func_00252340(a, st);
}

/* 0x00252290, 0xB0 bytes. */
int func_00252290(u8 *a, u32 *st)
{
    return ground_pair(a, st, 0x39, 0x3A);
}

/* 0x00252340, 0xB8 bytes. */
void func_00252340(u8 *a, u32 *st)
{
    ground_pair_step(a, st);
}

/* 0x00252400, 0xA8 bytes. Starts the target status: a marker in the partner player's corner. */
int func_00252400(u8 *a)
{
    u8 *o = *(u8 **)(a + 0x28C);

    if (o != 0 && (o[0x19C] & 2) == 0) {
        g_70000D60 = 0;
        if (o[0x14E] == 1)
            func_001C8340(0x26, (unsigned char *)((float *)g_005B4FC0), 0, 0x2A4);
        else
            func_001C8340(0x26, (unsigned char *)((float *)g_005B4D80), 0, 0x264);
        if ((g_005755A8 & 2) == 0)
            func_00229050(2);
    }
    return 1;
}

/* 0x002524B0, 0xF0 bytes. The target status ends with the partner. */
void func_002524B0(u8 *a, u32 *st)
{
    if (*(u8 **)(a + 0x28C) == 0 || func_00240DB0(PS2_ADDR(a)) == 0)
        status_end(a, st);
}

int func_00252600(u8 *a, u32 *st, int k);
void func_002526C0(u8 *a, u32 *st);
void func_00252740(u8 *a, u32 *st);

/* 0x002525A0, 0x1C bytes, matching. */
int func_002525A0(u8 *a, u32 *st, int k)
{
    return func_00252600(a, st, k);
}

/* 0x002525C0, 0x3C bytes, matching. */
void func_002525C0(u8 *a, u32 *st)
{
    func_002526C0(a, st);
    func_00252740(a, st);
}

/* 0x00252600, 0xB4 bytes. Starts a root status (effect `k`). */
int func_00252600(u8 *a, u32 *st, int k)
{
    float *p;
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    p = copy_node(a, st, 0);
    g_70000D60 = 0;
    st[0xC] = (u32)PS2_ADDR(func_001C84B0(k, (unsigned char *)(p), 0, f | 0x109));
    return 1;
}

/* 0x002526C0, 0x7C bytes. It ends when +0x157 and +0x194 are both clear. */
void func_002526C0(u8 *a, u32 *st)
{
    if (a[0x157] == 0 && *(short *)(a + 0x194) == 0)
        status_end(a, st);
}

/* 0x00252740, 0x64 bytes. It follows the root (left behind once +0x157 clears). */
void func_00252740(u8 *a, u32 *st)
{
    copy_node(a, st, 0);
    if (a[0x157] == 0)
        FX_LEAVE(st);
}

int func_00252810(u8 *a, u32 *st);
void func_002528D0(u8 *a, u32 *st);
void func_00252940(u8 *a, u32 *st);

/* 0x002527B0, 0x1C bytes, matching. */
int func_002527B0(u8 *a, u32 *st)
{
    return func_00252810(a, st);
}

/* 0x002527D0, 0x3C bytes, matching. */
void func_002527D0(u8 *a, u32 *st)
{
    func_002528D0(a, st);
    func_00252940(a, st);
}

/* 0x00252810, 0xB8 bytes. Starts the ground shadow status (effect 0xE4 on the ground). */
int func_00252810(u8 *a, u32 *st)
{
    float *p;
    u32 f;

    if (g_0045D344 == 0) {
        st[0xA] = 1;
        return 0;
    }
    f = fx_flags(a);
    g_70000D60 = 0;
    p = copy_node(a, st, 0);
    p[1] = func_001F2B70((unsigned char *)(p));
    st[0xC] = (u32)PS2_ADDR(func_001C84B0(0xE4, (unsigned char *)(p), 0, f | 0x11));
    return 1;
}

/* 0x002528D0, 0x70 bytes. It ends with bit 3 of +0x19D. */
void func_002528D0(u8 *a, u32 *st)
{
    if ((a[0x19D] & 8) == 0)
        status_end(a, st);
}

/* 0x00252940, 0xC4 bytes. It follows the actor on the ground (left behind in states 0xA5-0xA6). */
void func_00252940(u8 *a, u32 *st)
{
    u16 *s = *(u16 **)(a + 0x210);

    NODE_POS(a, 0);
    if ((a[0x19D] & 8) != 0 && st[0xC] != 0) {
        float *p = copy_node(a, st, 0);

        p[1] = func_001F2B70((unsigned char *)(p));
        if (s != 0 && (u32)(*s - 0xA5) < 2)
            FX_LEAVE(st);
    } else if (st[0xC] != 0) {
        FX_LEAVE(st);
    }
}

/* The status records: 4 of 0xB0 bytes per actor at 0x00755DC0. */
extern u32 g_00755DC0[0x8F][4][0x2C];
extern u8 g_00755CA0[0x8F];
extern u8 g_00410A00[0x19];              /* statuses that wait for the actor to show */
extern u8 g_00410A20[0x19];              /* the statuses' view distance kinds */
extern u32 g_0045D520;                   /* (small data) */
extern u8 g_00574DE0[][0x630];           /* the actors */

/* 0x00252A10, 0x2DC bytes. Starts status record `st` of actor `a`. */
void func_00252A10(u32 *st, u8 *a)
{
    switch (st[0]) {
    case 0: func_0024FB50(a, st); break;
    case 1: func_0024FEE0(a, st, func_00271280(a)); break;
    case 2: func_00250310(a, st); break;
    case 3:
        func_002505E0(a, st, a[0x182] == 1 ? 0x14C : a[0x182] == 2 ? 0x150 : 0x148);
        break;
    case 4:
        func_002505E0(a, st, a[0x182] == 1 ? 0x15A : a[0x182] == 2 ? 0x15F : 0x155);
        break;
    case 5: func_00250870(a, st); break;
    case 6: func_00250BD0(a, st); break;
    case 7: func_00250DC0(a, st); break;
    case 8: func_00251370(a, st); break;
    case 9: func_00251550(a, st, 0x21, 0x22); break;
    case 10: func_00251550(a, st, 0x23, 0x24); break;
    case 0xB: func_00251730(a, st, 0x35); break;
    case 0xC: func_00251730(a, st, 0x36); break;
    case 0xD: func_002519A0(a, st, 0x4B); break;
    case 0xE: func_002519A0(a, st, 0x4C); break;
    case 0xF: func_00251C20(a, st, 0x4F); break;
    case 0x10: func_00251C20(a, st, 0x51); break;
    case 0x11: func_002520A0(a, st); break;
    case 0x12: func_00252250(a, st); break;
    case 0x13: func_00252400(a); break;
    case 0x14: func_002525A0(a, st, 0xCC); break;
    case 0x15: func_002525A0(a, st, 0xCB); break;
    case 0x16: func_002525A0(a, st, 0x9D); break;
    case 0x17: func_002527B0(a, st); break;
    case 0x18: func_00250470(a, st); break;
    }
}

void func_00252F00(u32 *st, u8 *a);

/* 0x00252CF0, 0x210 bytes. Restarts a waiting status once its actor shows (then steps it). */
void func_00252CF0(u32 *st, u8 *a)
{
    int ok;

    switch (st[0]) {
    case 1: ok = func_0024FF60(a, st, func_00271280(a)); break;
    case 2: ok = func_00250350(a, st); break;
    case 6: ok = func_00250C10(a, st); break;
    case 7: ok = func_00250E30(a, st); break;
    case 8: ok = func_002513D0(a, st); break;
    case 9: ok = func_00251590(a, st, 0x21, 0x22); break;
    case 10: ok = func_00251590(a, st, 0x23, 0x24); break;
    case 0xD: ok = func_00251A00(a, st, 0x4B); break;
    case 0xE: ok = func_00251A00(a, st, 0x4C); break;
    case 0xF: ok = func_00251C80(a, st, 0x4F); break;
    case 0x10: ok = func_00251C80(a, st, 0x51); break;
    case 0x11: ok = func_002520E0(a, st); break;
    case 0x12: ok = func_00252290(a, st); break;
    case 0x14: ok = func_00252600(a, st, 0xCC); break;
    case 0x15: ok = func_00252600(a, st, 0xCB); break;
    case 0x16: ok = func_00252600(a, st, 0x9D); break;
    case 0x17: ok = func_00252810(a, st); break;
    case 0x18: ok = func_002504B0(a, st); break;
    default: ok = 0; break;
    }
    if (ok != 0) {
        st[0xA] = 0;
        func_00252F00(st, a);
    }
}

/* 0x00252F00, 0x1A0 bytes, matching. Steps status record `st` of actor `a`. */
void func_00252F00(u32 *st, u8 *a)
{
    switch (st[0]) {
    case 0: func_0024FCB0(a, st); break;
    case 1: func_0024FF00(a, st); break;
    case 2: func_00250330(a, st); break;
    case 3:
    case 4: func_00250730(a, st); break;
    case 5: func_00250A60(a, st); break;
    case 6: func_00250BF0(a, st); break;
    case 7: func_00250DE0(a, st); break;
    case 8: func_00251390(a, st); break;
    case 9:
    case 10: func_00251570(a, st); break;
    case 0xB:
    case 0xC: func_00251860(a, st); break;
    case 0xD:
    case 0xE: func_002519C0(a, st); break;
    case 0xF:
    case 0x10: func_00251C40(a, st); break;
    case 0x11: func_002520C0(a, st); break;
    case 0x12: func_00252270(a, st); break;
    case 0x13: func_002524B0(a, st); break;
    case 0x14:
    case 0x15:
    case 0x16: func_002525C0(a, st); break;
    case 0x17: func_002527D0(a, st); break;
    case 0x18: func_00250490(a, st); break;
    }
}

/* 0x002530A0, 0xD0 bytes. The end checks of a waiting status whose actor is out of view. */
void func_002530A0(u32 *st, u8 *a)
{
    switch (st[0]) {
    case 1:
        func_00250120(a, st, func_00271280(a));
        /* falls through */
    case 7:
        func_00251000(a, st);
        break;
    case 0xD:
    case 0xE:
        func_00251AB0(a, st);
        break;
    case 0xF:
    case 0x10:
        func_00251D90(a, st);
        break;
    case 0x14:
    case 0x15:
    case 0x16:
        func_002526C0(a, st);
        break;
    case 0x17:
        func_002528D0(a, st);
        break;
    }
}

/* 0x00253170, 0xE0 bytes. Stops status `st`'s effects; it ends, or waits when its kind waits. */
void func_00253170(u8 *a, u32 *st)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        if (st[0xC + k] != 0) {
            FX_STOP((u8 *)PS2_PTR(st[0xC + k]));
            st[0xC + k] = 0;
        }
    }
    if (g_00410A00[st[0]] == 0) {
        g_0076E700[a[0x14E]] &= ~(1 << (st[0] & 0x1F));
        g_0076E700[a[0x14E]] &= ~(1 << (st[0] & 0x1F));
        st[0] = 0x19;
        g_00755D30[a[0x14E]]--;
        st[0xA] = 0;
    } else {
        st[0xA] = 1;
    }
}

/* 0x00253250, 0xB0 bytes. Clears all actors' statuses. */
void func_00253250(void)
{
    u32 k, j, i;

    for (k = 0; k < 0x8F; k++) {
        for (j = 0; j < 4; j++) {
            g_00755DC0[k][j][0] = 0x19;
            for (i = 0; i < 0x10; i++)
                g_00755DC0[k][j][0xC + i] = 0;
        }
        g_00755D30[k] = 0;
        g_0076E700[k] = 0;
        g_00755CA0[k] = 0;
    }
    g_0045D520 = 0;
}

/* 0x00253300, 0x180 bytes. Gives status `kind` to actor `a` (in a free record, unless it has it):
 * started now when in view, else waiting when its kind waits. */
void func_00253300(u32 kind, u8 *a)
{
    u32 *st = g_00755DC0[a[0x14E]][0], k;

    for (k = 0; k < 4; k++, st += 0x2C) {
        if (st[0] == 0x19)
            break;
        if (st[0] == kind)
            k = 4;
    }
    if (k >= 4)
        return;
    if (*(int *)(a + 0x11C) == 0 || func_001C8BE0(g_00410A20[kind], PS2_ADDR(a + 0x40)) == 0) {
        if (g_00410A00[kind] == 0)
            return;
        st[0] = kind;
        st[0xA] = 1;
        g_00755D30[a[0x14E]]++;
    } else {
        st[0] = kind;
        st[0xA] = 0;
        g_00755D30[a[0x14E]]++;
        func_00252A10(st, a);
    }
    if (st[0] != 0x19) {
        g_0076E700[a[0x14E]] |= 1 << (kind & 0x1F);
        g_70000D60 = 0;
    }
}

/* 0x00253480, 0x1F8 bytes. Steps every actor's statuses (waiting ones end when not kept, start
 * when their actor shows). */
void func_00253480(void)
{
    u32 k, j;

    for (k = 0; k < 0x8F; k++) {
        u8 *a = g_00574DE0[k];

        if (g_0076E700[k] == 0)
            continue;
        for (j = 0; j < 4; j++) {
            u32 *st = g_00755DC0[k][j];

            if (st[0] == 0x19)
                continue;
            if (*(int *)(a + 0x11C) == 0 || st[0xA] != 0) {
                if (st[0xA] == 0) {
                    u32 kind = st[0], i;
                    u8 n = a[0x14E];

                    st[0] = 0x19;
                    g_0076E700[n] &= ~(1 << (kind & 0x1F));
                    g_00755D30[n]--;
                    for (i = 0; i < 0x10; i++) {
                        u8 *e = (u8 *)PS2_PTR(st[0xC + i]);

                        if (e != 0 && !(1.0f <= *(float *)(e + 0x28) && (*(u32 *)(e + 0x34) & 1) == 0)) {
                            FX_STOP(e);
                            st[0xC + i] = 0;
                        }
                    }
                } else if (*(int *)(a + 0x11C) == 0) {
                    func_002530A0(st, a);
                } else if (func_001C8BE0(g_00410A20[st[0]], PS2_ADDR(a + 0x40)) != 0) {
                    func_00252CF0(st, a);
                }
            } else {
                func_00252F00(st, a);
            }
        }
    }
    g_70000D60 = 0;
}

/* 0x00253690, 0xF8 bytes. Ends status `kind` of actor `a`. */
void func_00253690(u32 kind, u8 *a)
{
    u32 *st = g_00755DC0[a[0x14E]][0], k, i;

    for (k = 0; k < 4; k++, st += 0x2C) {
        if (st[0] == kind) {
            u32 m;

            for (i = 0; i < 0x10; i++) {
                if (st[0xC + i] != 0) {
                    FX_STOP((u8 *)PS2_PTR(st[0xC + i]));
                    st[0xC + i] = 0;
                }
            }
            m = ~(1 << (st[0] & 0x1F));
            g_0076E700[a[0x14E]] &= m;
            st[0] = 0x19;
            g_0076E700[a[0x14E]] &= m;
            st[0xA] = 0;
            g_00755D30[a[0x14E]]--;
        }
    }
}

/* 0x00253790, 0x6C bytes. Stops all of actor `a`'s statuses. */
void func_00253790(u8 *a)
{
    u32 *st = g_00755DC0[a[0x14E]][0], k;

    for (k = 0; k < 4; k++, st += 0x2C) {
        if (st[0] != 0x19)
            func_00253170(a, st);
    }
}

extern u8 g_0045CDF0[3];                 /* (small data) the three element sparks */
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
extern u8 g_006A3A30[][0xC0];            /* the battle officers */

void func_00229E20(int a);
void func_00229E30(void);

/* 0x00253800, 0xB8 bytes. Drops all of actor `a`'s statuses (without stopping their effects). */
void func_00253800(u8 *a)
{
    u32 *st = g_00755DC0[a[0x14E]][0], k;

    for (k = 0; k < 4; k++, st += 0x2C) {
        if (st[0] != 0x19) {
            u32 m = ~(1 << (st[0] & 0x1F));

            g_0076E700[a[0x14E]] &= m;
            st[0] = 0x19;
            g_0076E700[a[0x14E]] &= m;
            st[0xA] = 0;
            g_00755D30[a[0x14E]]--;
        }
    }
}

/* 0x002538C0, 0x118 bytes. Fades actor `k`'s gauge statuses to `v` / 128. */
void func_002538C0(u32 k, u8 v)
{
    u32 *st = g_00755DC0[k & 0xFF][0], j;
    float f = (float)v / 128.0f;

    for (j = 0; j < 4; j++, st += 0x2C) {
        switch (st[0]) {
        case 6:
        case 9:
        case 10:
        case 0x11:
            if (st[0xC] != 0)
                *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = f;
            if (st[0xD] != 0)
                *(float *)((u8 *)PS2_PTR(st[0xD]) + 0x2C) = f;
            break;
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x10:
            if (st[0xC] != 0)
                *(float *)((u8 *)PS2_PTR(st[0xC]) + 0x2C) = f;
            break;
        }
    }
}

/* 0x002539F0, 0x6C bytes. Actor `a` gets the level status (instead of the ring one). */
void func_002539F0(u8 *a)
{
    if ((a[0x19C] & 2) == 0 && (g_0076E700[a[0x14E]] & 2) == 0) {
        func_00253690(0, a);
        func_00253300(1, a);
    }
}

/* 0x00253A60, 0xE8 bytes. The same for a generic officer whose life fell to func_00271210. */
void func_00253A60(u8 *a)
{
    if (*(int *)(a + 0x11C) != 0 && *(int *)(a + 0x118) < 0x1C && (a[0x19C] & 2) == 0) {
        short life = *(short *)(g_006A3A30[*(short *)(a + 0x178)] + 0x88);
        u8 n = a[0x14E];
        short v = func_00271210(a);

        if ((g_0076E700[n] & 2) == 0 && v <= life) {
            func_00253690(0, a);
            func_00253300(1, a);
        }
    }
}

/* 0x00253B50, 0x114 bytes. Actor `a`'s element ground status for element `e` (1-2: 10, 3-4: 9),
 * room made first. */
void func_00253B50(u8 *a, u32 e)
{
    u32 bits;

    if (a == 0)
        return;
    bits = g_0076E700[a[0x14E]];
    if ((bits & 0x200) != 0)
        func_00253690(9, a);
    else if ((bits & 0x400) != 0)
        func_00253690(10, a);
    if (g_00755D30[a[0x14E]] > 3)
        func_00253790(a);
    if (g_00755D30[a[0x14E]] > 3)
        func_00253800(a);
    if ((e & 0xFF) - 1 < 2)
        func_00253300(10, a);
    else if ((e & 0xFF) - 3 < 2)
        func_00253300(9, a);
}

/* 0x00253C70, 0x3C bytes, matching. A burst (effect 0x47) at actor `a`. */
void func_00253C70(u8 *a)
{
    if (*(int *)(a + 0x11C) != 0) {
        g_70000D60 = 0;
        func_001C7F30(0x47, (float *)(a + 0x40), 0, 8);
    }
}

/* 0x00253CB0, 0x6C bytes. Actor `a`'s musou status (kind `k`: 0-1, 2, 3). */
void func_00253CB0(u8 *a, u8 k)
{
    if (k < 2)
        func_00253300(6, a);
    else if (k == 2)
        func_00253300(0x12, a);
    else if (k == 3)
        func_00253300(0x11, a);
}

/* 0x00253D20, 0x114 bytes. Now and then (1%) actor `a` gets one of the three element sparks it
 * lacks. */
void func_00253D20(u8 *a)
{
    u8 *m = &g_00755CA0[a[0x14E]];
    u32 k;

    for (k = 0; k < 3; k = (k + 1) & 0xFF) {
        u32 b = 1 << k;

        if ((*m & b) == 0 && RANDOM() % 100 == 0) {
            u32 f = fx_flags(a);

            *m |= b;
            g_70000D60 = 0;
            func_001C8780(0xF3, PS2_ADDR(a), g_0045CDF0[k], f | 0x80000000);
        }
    }
}

/* 0x00253E40, 0x54 bytes, matching. An element spark `c` of kind `k` at actor `a`. */
void func_00253E40(u8 *a, u8 k, u8 c)
{
    u8 *e = (u8 *)PS2_PTR(func_001C8810(0xF3, PS2_ADDR(a), c, 0x80000001));

    if (e != 0) {
        e[0x105] = k;
        *(u32 *)(e + 0x34) &= ~1;
    }
}

/* 0x00253EA0, 0x8C bytes. Actor `k` loses its spark of colour `c` (0xB, 0xD, 0xC). */
void func_00253EA0(u32 k, char c)
{
    if (c == 0xB)
        g_00755CA0[k & 0xFF] &= 0xFE;
    else if (c == 0xD)
        g_00755CA0[k & 0xFF] &= 0xFD;
    else if (c == 0xC)
        g_00755CA0[k & 0xFF] &= 0xFB;
}

/* 0x00253F30, 0x88 bytes, matching. Ends actor `a`'s root status (0x14-0x16). */
void func_00253F30(u8 *a)
{
    u32 bits = g_0076E700[a[0x14E]];

    if ((bits & 0x100000) != 0)
        func_00253690(0x14, a);
    else if ((bits & 0x200000) != 0)
        func_00253690(0x15, a);
    else if ((bits & 0x400000) != 0)
        func_00253690(0x16, a);
}

/* 0x00253FC0, 0x64 bytes. Shows the player 0 corner marker (effect 0xCF, once). */
void func_00253FC0(void)
{
    if ((g_005755A8 & 2) == 0 && g_0045D520 == 0) {
        g_70000D60 = 0;
        g_0045D520 = (u32)PS2_ADDR(func_001C8340(0xCF, (unsigned char *)((float *)g_005B4D80), 0, 0x265));
        func_00229E20(2);
    }
}

/* 0x00254030, 0x50 bytes. Hides it. */
void func_00254030(void)
{
    if ((g_005755A8 & 2) == 0) {
        if (g_0045D520 != 0) {
            *(u32 *)((u8 *)PS2_PTR(g_0045D520) + 0x34) |= 0x800;
            g_0045D520 = 0;
        }
        func_00229E30();
    }
}
