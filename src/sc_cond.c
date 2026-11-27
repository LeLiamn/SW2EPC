/*
 * sc_cond.c - the scenario's conditions (original source file unknown, probably one of the sc_
 * files; from 0x00197510, before sc_ubase.c at 0x0019A7B0). Written so far: the first ones.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A condition returns which players it holds for: bit 0 player 1, bit 1 player 2 (3: both, 0:
 * not met). The officer records are the game state's 0x88-byte ones (0x00693970).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

extern u8 g_00693970[][0x88];            /* the officer records (+0x10 base, +0x80 flags) */
#define BASE68(v) (g_00693970[0] + 0xE3E8 + (v) * 0x68)

extern u8 g_00669D60[];                  /* the settings (per player 0x48 bytes from +0x88) */
extern u8 g_00669D70[];                  /* (settings) the scenario's event bits */
extern u32 g_00669DB8[4];                /* (settings) +0: the game mode */
extern u32 g_00669F60[4];                /* (settings) +0: the battle flags */
extern u8 g_00669D81[0x10];              /* (settings) +0: a scenario value */

u32 func_00185ED0(u32 id);
int func_00185EC0(u32 id);
int func_001ED240(u8 *a, u8 *b);
int func_001ED310(u8 *a, u32 b);
u16 func_002F27D0(u32 a);

/* Whether a record is on the field: flag 1 and none of 0x8C40002. */
static inline int on_field(u32 f)
{
    return (f & 1) && (f & 0x8C40002) == 0;
}

/* 0x00197510, 0x158 bytes. Whether officer record `o` stands in the area of cells a-b (in
 * 1000-unit cells, or with `big` in 5000-unit ones). */
int func_00197510(u8 *o, u8 *a, u8 *b, int big)
{
    float *p = (U32(o, 0x80) & 0x20000) ? (float *)(o + 0x30) : (float *)(o + 0x28);
    u32 x, z;

    if (big == 0) {
        x = (int)p[0] / 1000;
        z = (int)p[1] / 1000;
    } else {
        x = (int)p[0] / 5000;
        z = (int)p[1] / 5000;
    }
    if ((x & 0xFF) < a[0] || b[0] < (x & 0xFF) || (z & 0xFF) < a[1] || b[1] < (z & 0xFF))
        return 0;
    return 1;
}

/* 0x00197670, 0x13C bytes. Whether officer `o` (cmd[0] = 1) or one of the garrison of its base
 * (cmd[0] = 0: the 13 officers on the field, not beaten nor of state 3) stands in the area
 * cmd[2]-cmd[5]. */
int func_00197670(u8 *o, short *cmd, int big)
{
    u8 a[2], b[2];
    int r = 0;

    a[0] = (u8)cmd[2];
    a[1] = (u8)cmd[3];
    b[0] = (u8)cmd[4];
    b[1] = (u8)cmd[5];
    if (cmd[0] == 1) {
        r = func_00197510(o, a, b, big);
    } else if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
        u8 **g = (u8 **)BASE68(U32(o, 0x10));
        u32 k;

        for (k = 0; k < 0xD; k++) {
            u8 *e = g[k];

            if (e != 0) {
                u32 f = U32(e, 0x80);

                if (on_field(f) && (f & 4) == 0 && U8(e, 0x7A) != 3) {
                    r = func_00197510(e, a, b, big);
                    if (r != 0)
                        return r;
                }
            }
        }
    }
    return r;
}

/* 0x001977B0, 0xC4 bytes. Officer state `k` of record `o`: 3 beaten (flag 2), 2 away (4), 1
 * fled or captured (0x140000), 0 on the field and present. */
u32 func_001977B0(u8 *o, short k)
{
    u32 f = U32(o, 0x80);

    if (k == 3)
        return f & 2;
    if (k == 2)
        return f & 4;
    if (k == 1)
        return f & 0x140000;
    if (k == 0)
        return on_field(f) && (f & 4) == 0;
    return 0;
}

/* 0x00197880, 0x1F0 bytes. Whether officers `i` and `j` (both on the field) meet: two
 * officers (both `a` and `b`) by func_001ED240 either way; an officer and a base
 * (func_001ED310); or one of base `i`'s garrison and base `j`. */
int func_00197880(int a, int i, int b, int j)
{
    u8 *oi = g_00693970[i], *oj = g_00693970[j];
    int r;

    if (!on_field(U32(oi, 0x80)) || !on_field(U32(oj, 0x80)))
        return 0;
    if (a != 0) {
        if (b != 0) {
            r = func_001ED240(oi, oj);
            if (r == 0)
                r = func_001ED240(oj, oi);
            return r;
        }
        if (U32(oj, 0x10) < 0x47)
            return func_001ED310(oi, U32(oj, 0x10));
        return 0;
    }
    if (U32(oi, 0x10) > 0x46)
        return 0;
    if (b != 0)
        return func_001ED310(oj, U32(oi, 0x10));
    if (U32(oj, 0x10) > 0x46)
        return 0;
    {
        u8 **g = (u8 **)BASE68(U32(oi, 0x10));
        u32 k;

        r = 0;
        for (k = 0; k < 0xD; k++) {
            u8 *e = g[k];

            if (e != 0 && on_field(U32(e, 0x80))) {
                r = func_001ED310(e, U32(oj, 0x10));
                if (r != 0)
                    return r;
            }
        }
        return r;
    }
}

/* 0x00197A70, 0x78 bytes. Compares `a` with `b` by operator `op` (0 <, 1 <=, 2 ==, 3 >=,
 * 4 >). */
int func_00197A70(int op, int a, int b)
{
    if (op == 4)
        return b < a;
    if (op == 3)
        return b <= a;
    if (op == 2)
        return a == b;
    if (op == 1)
        return a <= b;
    if (op == 0)
        return a < b;
    return 0;
}

/* 0x00197AF0, 0x7C bytes. Condition: event bit cmd[0] is set (cmd[1] = 1) or clear (0). */
u32 func_00197AF0(u16 *cmd)
{
    int on = (g_00669D70[(int)cmd[0] >> 3] & 1 << (cmd[0] & 7)) != 0;

    if ((on && cmd[1] == 1) || (!on && cmd[1] == 0))
        return 3;
    return 0;
}

/* 0x00197B70, 0x60 bytes, matching. Condition: one player (cmd[0] = 1, battle flag 1) or two (2, flag
 * 2). */
u32 func_00197B70(u16 *cmd)
{
    if (cmd[0] == 1) {
        if (g_00669F60[0] & 1)
            return 3;
    } else if (cmd[0] == 2 && (g_00669F60[0] & 2)) {
        return 3;
    }
    return 0;
}

/* 0x00197BD0, 0x1C0 bytes. Condition on the players' officers: which player's officer is
 * cmd[1] (cmd[0] = 2: either player; 0 / 1: that player, in a two-player battle only for
 * player 1), cmd[2] = 1 for "is", 0 for "is not". */
u32 func_00197BD0(u16 *cmd)
{
    u32 r, k;

    if (cmd[0] == 2) {
        if (cmd[2] == 1) {
            r = 0;
            for (k = 0; k < 2; k++) {
                u8 *p = g_00669D60 + k * 0x48;

                if (U32(p, 0xA0) != 0 && cmd[1] == func_002F27D0(U32(p, 0x88)))
                    r |= k == 0 ? 1 : 2;
            }
            return r;
        }
        for (k = 0; k < 2; k++) {
            u8 *p = g_00669D60 + k * 0x48;

            if (U32(p, 0xA0) != 0 && cmd[1] == func_002F27D0(U32(p, 0x88)))
                return 0;
        }
        return 3;
    }
    if ((g_00669F60[0] & 2) == 0 && cmd[0] != 0) {
        return cmd[2] == 0 ? 3 : 0;
    }
    {
        u16 id = func_002F27D0(U32(g_00669D60, cmd[0] * 0x48 + 0x88));

        if ((cmd[1] == id && cmd[2] == 1) || (cmd[1] != id && cmd[2] == 0))
            return cmd[0] == 0 ? 1 : 2;
    }
    return 0;
}

/* 0x00197D90, 0x20 bytes, matching. Condition: cmd[1] is 0. */
u32 func_00197D90(u16 *cmd)
{
    if (cmd[1] == 0)
        return 3;
    return 0;
}

/* 0x00197DB0, 0x84 bytes. Condition: the game mode is cmd[0] (0-3). */
u32 func_00197DB0(short *cmd)
{
    short k = cmd[0];

    if (k == 2)
        return g_00669DB8[0] == 2 ? 3 : 0;
    if (k == 3)
        return g_00669DB8[0] == 3 ? 3 : 0;
    if (k == 1)
        return g_00669DB8[0] == 1 ? 3 : 0;
    if (k == 0 && g_00669DB8[0] == 0)
        return 3;
    return 0;
}

/* 0x00197E40, 0x28 bytes, matching. Condition: the scenario value is cmd[0]. */
u32 func_00197E40(u16 *cmd)
{
    if (cmd[0] == (u16)g_00669D81[0])
        return 3;
    return 0;
}

/* 0x00197E70, 0x104 bytes. Condition: officer cmd[0] (flag 0x400000) belongs (cmd[2] = 1) or not
 * (0) to side cmd[1] (+0x79; never while its base has flag 8). */
u32 func_00197E70(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);
    u8 *o;
    int in;

    if (func_00185EC0(id) != 0)
        return 0;
    o = g_00693970[id];
    if ((U32(o, 0x80) & 0x400000) == 0)
        return 0;
    if ((U32(BASE68(U32(o, 0x10)), 0x64) & 8) == 0)
        in = cmd[1] == U8(o, 0x79);
    else
        in = 0;
    if ((in && cmd[2] == 1) || (!in && cmd[2] == 0))
        return 3;
    return 0;
}
