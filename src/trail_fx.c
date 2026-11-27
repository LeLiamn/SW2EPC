/*
 * trail_fx.c - weapon trails: six trail records of 0x17C0 bytes at 0x007335E0 (with a count per
 * actor at 0x00733550), their curve weights and GIF packet ends. Original file name unknown
 * (parts of 0x002083E0-0x002093DC).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Trail record: +0x00 (8 bytes) cleared, +0x08 its index, +0x09-0x0B, +0x0C in use, +0x10 on,
 * +0x1C its actor, +0x20 / +0x30 the two blade points.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_007335E0[6][0x17C0];         /* the trails */
extern u8 g_00733550[];                  /* per actor: its trails */
extern u8 g_00574DE0[][0x630];           /* the actors */
extern u32 g_0045D414;                   /* (small data) the first free trail */
extern int g_0045CD98;                   /* (small data) free trails */

/* 0x002083E0, 0x88 bytes. The four Catmull-Rom weights for `t` (0-1). */
void func_002083E0(float t, float *w)
{
    float t2 = t * t, t3 = t * t2;

    w[0] = t * -0.5f + t3 * -0.5f + t2 + 0.0f;
    w[1] = t3 * 1.5f + t2 * -2.5f + 1.0f;
    w[2] = t * 0.5f + t3 * -1.5f + t2 * 2.0f;
    w[3] = t3 * 0.5f + t2 * -0.5f;
}

/* 0x00208530, 0x20 bytes, matching. Ends a GIF packet at `p`; past it. */
u32 *func_00208530(u32 *p)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x17000000;
    return p + 4;
}

/* 0x002087A0, 0x80 bytes. Takes a free trail (0 for none). */
u8 *func_002087A0(void)
{
    u8 *t = 0;

    if (g_0045D414 < 6) {
        t = g_007335E0[g_0045D414];
        g_0045CD98--;
        *(int *)(g_007335E0[g_0045D414] + 0xC) = 1;
        while (g_0045D414 < 6) {
            if (*(int *)(g_007335E0[g_0045D414] + 0xC) == 0)
                return t;
            g_0045D414++;
        }
    }
    return t;
}

/* 0x00208820, 0x98 bytes. Starts trail `t` for actor `k` between points `a` and `b`. */
void func_00208820(u8 *t, u32 *a, u32 *b, u8 k)
{
    if (t == 0)
        return;
    *(u32 *)(t + 0) = 0;
    *(u32 *)(t + 4) = 0;
    t[9] = 0;
    t[10] = 0;
    t[11] = 0;
    ((u32 *)(t + 0x20))[0] = a[0];
    ((u32 *)(t + 0x20))[1] = a[1];
    ((u32 *)(t + 0x20))[2] = a[2];
    ((u32 *)(t + 0x20))[3] = a[3];
    ((u32 *)(t + 0x30))[0] = b[0];
    ((u32 *)(t + 0x30))[1] = b[1];
    ((u32 *)(t + 0x30))[2] = b[2];
    ((u32 *)(t + 0x30))[3] = b[3];
    *(int *)(t + 0x10) = 1;
    t[0x1C] = k;
    g_00733550[k]++;
    g_00574DE0[k][0x19E] = (g_00574DE0[k][0x19E] & 0xDF) | 0x20;
}

/* 0x002088C0, 0xB4 bytes. Frees trail `t` (its actor loses its trail flag with its last one). */
void func_002088C0(u8 *t)
{
    u8 k;

    if (t == 0)
        return;
    *(int *)(t + 0xC) = 0;
    if (t[8] <= g_0045D414)
        g_0045D414 = t[8];
    g_0045CD98++;
    k = t[0x1C];
    if (g_00733550[k] != 0) {
        g_00733550[k]--;
        if (g_00733550[t[0x1C]] == 0)
            g_00574DE0[t[0x1C]][0x19E] &= 0xDF;
    }
}

extern u32 g_0040D020[];
extern int g_0045D378;                   /* (small data) the screen being drawn (two players) */
extern u8 g_00733551;

#define PACKET (*(u32 **)0x70000158)     /* (scratchpad) the current GIF packet */

u32 *func_00208470(u32 *p);
u32 *func_00208270(u32 *p, u8 *t);

/* 0x00208FF0, 0x15C bytes. Draws the trails in use (not the ones hidden on this screen). */
void func_00208FF0(void)
{
    u32 *p = PACKET, k;

    if ((u32)g_0045CD98 >= 6)
        return;
    p[0] = 0x30000002;
    p[1] = (u32)g_0040D020;
    p[2] = 0x13000000;
    p[3] = 0x51000002;
    p = func_00208470(p + 4);
    for (k = 0; k < 6; k++) {
        u8 *t = g_007335E0[k];
        int hidden;

        if (*(int *)(t + 0xC) == 0)
            continue;
        if (g_0045D378 == 0 && (g_00574DE0[t[0x1C]][0x198] & 0x40) != 0)
            hidden = 1;
        else
            hidden = g_0045D378 == 1 && (g_00574DE0[t[0x1C]][0x198] & 0x80) != 0;
        if (!hidden)
            p = func_00208270(p, t);
    }
    PACKET = p;
}

/* 0x00209160, 0x28 bytes. Whether both players' actors have trails. */
int func_00209160(void)
{
    return g_00733550[0] != 0 && g_00733551 != 0;
}

/* 0x00209310, 0xCC bytes. The height of slope box `b` at point `p`, rising toward side `side`
 * (0-3). */
float func_00209310(float *b, int side, float *p)
{
    float t;

    if (side == 0)
        t = (b[4] - p[0]) / (b[0] - b[4]);
    else if (side == 1)
        t = (b[6] - p[2]) / (b[2] - b[6]);
    else if (side == 2)
        t = (p[0] - b[0]) / (b[0] - b[4]);
    else
        t = (p[2] - b[2]) / (b[2] - b[6]);
    return t * (b[5] - b[1]) + b[5] + 0.0f;
}
