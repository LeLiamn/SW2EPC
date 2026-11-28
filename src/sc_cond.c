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

#define SW2E_FILE_SC_COND_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

int func_001ED310(u8 *a, u32 b);

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
            r = func_001ED240(oi, PS2_ADDR(oj));
            if (r == 0)
                r = func_001ED240(oj, PS2_ADDR(oi));
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

/* Whether player `k` is in the battle. */
#define PLAYER_ON(k) (U32(g_00669D60, (k) * 0x48 + 0xA0) != 0)

/* A record's map point (its battle point once in battle). */
#define REC_POS(o) ((float *)((U32(o, 0x80) & 0x20000) ? (o) + 0x30 : (o) + 0x28))

/* "is" (`want` 1) or "is not" (0): 3 when `r` agrees. */
#define AGREE(r, want) (((r) && (want) == 1) || (!(r) && (want) == 0) ? 3 : 0)

/* 0x00197F80, 0x1E4 bytes. Condition: officer cmd[0] has (cmd[2] = 1) or has not (0) state
 * cmd[1] (0 in battle, 1-10 and 12-16 its +0x84 flags, 11 its base's flag 4). */
u32 func_00197F80(u16 *cmd)
{
    static const u32 bits[0x11] = {0, 1, 2, 4, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
                                   0x10000, 0, 0x200, 8, 0x40000, 0x80000, 0x100000};
    u32 id = func_00185ED0(cmd[0]), r;
    u8 *o;

    if (func_00185EC0(id) != 0)
        return 0;
    o = g_00693970[id];
    if (cmd[1] > 0x10)
        return 0;
    if (cmd[1] == 0)
        r = U32(o, 0x80) & 0x20000;
    else if (cmd[1] == 0xB)
        r = U32(o, 0x10) < 0x47 ? 0 : U32(BASE68(U32(o, 0x10)), 0x64) & 4;   /* (as in the original) */
    else
        r = U32(o, 0x84) & bits[cmd[1]];
    return AGREE(r, cmd[2]);
}

/* 0x00198170, 0x314 bytes. Condition: officer cmd[0] (or the players' officers for the player
 * ids) is (cmd[4]) within or beyond (by operator cmd[3]) cmd[2] x 100 of officer cmd[1]. */
u32 func_00198170(u16 *cmd)
{
    u32 id = func_00185E00(cmd[1], 0), a, r = 0;
    int d2;
    u8 *t;
    int k;

    if (id >= 0x1AD)
        return 0;
    t = g_00693970[id];
    d2 = (short)cmd[2] * 100 * (short)cmd[2] * 100;
    a = func_00185ED0(cmd[0]);
    if (func_00185EC0(a) == 0) {
        u8 *o = g_00693970[a];
        int c;

        if (!on_field(U32(o, 0x80)))
            return 0;
        c = func_00197A70(cmd[3], (int)func_0018C3F0(REC_POS(o), REC_POS(t)), d2);
        return AGREE(c, cmd[4]);
    }
    if (cmd[4] == 1) {
        for (k = 0; k < 2; k++) {
            if (PLAYER_ON(k)) {
                u8 *o = func_0035DCD0(k);

                if (func_00197A70(cmd[3], (int)func_0018C3F0(REC_POS(o), REC_POS(t)), d2))
                    r |= k == 0 ? 1 : 2;
            }
        }
        return r;
    }
    for (k = 0; k < 2; k++) {
        if (PLAYER_ON(k)) {
            u8 *o = func_0035DCD0(k);

            if (func_00197A70(cmd[3], (int)func_0018C3F0(REC_POS(o), REC_POS(t)), d2))
                return 0;
        }
    }
    return 3;
}

/* 0x00198490, 0x118 bytes. Condition: an officer of side cmd[0] (on the field, present, not of
 * state 3) stands (cmd[5] = 1) or none stands (0) in the area cmd[1]-cmd[4] (5000-unit
 * cells). */
u32 func_00198490(u16 *cmd)
{
    u8 a[2], b[2], *o = g_00693970[0];
    u32 k;

    a[0] = (u8)cmd[1];
    a[1] = (u8)cmd[2];
    b[0] = (u8)cmd[3];
    b[1] = (u8)cmd[4];
    for (k = 0; k < 0x1AD; k++, o += 0x88) {
        u32 f = U32(o, 0x80);

        if (on_field(f) && (f & 4) == 0 && U8(o, 0x7A) != 3 && cmd[0] == U8(o, 0x79)
            && func_00197510(o, a, b, 1) != 0)
            return cmd[5] == 1 ? 3 : 0;
    }
    return cmd[5] == 1 ? 0 : 3;
}

/* 0x001985B0, 0x1E4 bytes. Condition: officer cmd[1] (or the players' officers) or its
 * garrison is (cmd[6]) in the area of func_00197670. */
u32 func_001985B0(short *cmd, int big)
{
    u32 id = func_00185ED0(cmd[1]), r = 0;
    int k;

    if (func_00185EC0(id) == 0) {
        u8 *o = g_00693970[id];
        u32 f = U32(o, 0x80);
        int c;

        if (!on_field(f) || (f & 4))
            return 0;
        c = func_00197670(o, cmd, big);
        return AGREE(c, cmd[6]);
    }
    if (cmd[6] == 1) {
        for (k = 0; k < 2; k++) {
            if (PLAYER_ON(k) && func_00197670(func_0035DCD0(k), cmd, big) != 0)
                r |= k == 0 ? 1 : 2;
        }
        return r;
    }
    for (k = 0; k < 2; k++) {
        if (PLAYER_ON(k) && func_00197670(func_0035DCD0(k), cmd, big) != 0)
            return 0;
    }
    return 3;
}

/* 0x001987A0, 0xA4 bytes. Condition: officer cmd[0] is (cmd[2]) in state cmd[1]
 * (func_001977B0). */
u32 func_001987A0(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);
    u32 r;

    if (func_00185EC0(id) != 0)
        return 0;
    r = func_001977B0(g_00693970[id], cmd[1]);
    return AGREE(r, cmd[2]);
}

#ifdef SW2E_PC
extern ps2ptr g_005BA7CC_a;                   /* the scenario's commands */
#define g_005BA7CC ((u8 *)PS2_PTR(g_005BA7CC_a))
#define g_005BA7CC_SET(v) (g_005BA7CC_a = PS2_ADDR(v))
#else
extern u8 *g_005BA7CC;
#define g_005BA7CC_a (*(ps2ptr *)&g_005BA7CC)
#define g_005BA7CC_SET(v) (g_005BA7CC = (v))
#endif
extern u32 g_005BA7D4;                   /* the commands of the current part start here */
extern int g_005BC260[0x10];             /* the scenario variables (scenario object +0x1BD0) */
extern u8 g_005BD740[8];                 /* scenario switches (+5: a count compared by 198AB0) */
extern int g_00669F98[4];                /* (settings) +0: the stage reached, from 0 */
extern u32 g_00669DE8[4];                /* (settings) +0: the scenario kind */

/* Player `p`'s settings word at `off` (0x48 bytes per player from +0x88). */
#define PSET(p, off) (*(int *)(g_00669D60 + (p) * 0x48 + (off)))

/* 0x00198850, 0x11C bytes. Condition: officer cmd[1] (or the players' officers) met (by
 * func_00197880 with cmd[0], cmd[2]) officer cmd[3]. */
u32 func_00198850(u16 *cmd)
{
    u32 b = func_00185E00(cmd[3], 0), a, r = 0;
    int k;

    if (b >= 0x1AD)
        return 0;
    a = func_00185ED0(cmd[1]);
    if (func_00185EC0(a) == 0)
        return func_00197880(cmd[0], a, cmd[2], b) != 0 ? 3 : 0;
    for (k = 0; k < 2; k++) {
        if (PLAYER_ON(k) && func_00197880(cmd[0], func_0035DC70(k) & 0xFFFF, cmd[2], b) != 0)
            r |= k == 0 ? 1 : 2;
    }
    return r;
}

/* 0x00198970, 0x64 bytes. Condition: item cmd[0]'s +3 is cmd[1] (3 for none). */
u32 func_00198970(u16 *cmd)
{
    u8 *p = func_0018AC60(cmd[0]);

    if (p == 0)
        return cmd[1] == 3 ? 3 : 0;
    return cmd[1] == p[3] ? 3 : 0;
}

/* 0x001989E0, 0x74 bytes. Condition: command cmd[0] (of the current part unless `abs`) has
 * (cmd[1] = 1) or has not (0) flag 2 (done). */
u32 func_001989E0(u16 *cmd, int abs)
{
    u32 i = cmd[0];

    if (abs == 0)
        i = i + g_005BA7D4;
    if ((g_005BA7CC[*(u32 *)(g_005BA7CC + i * 4 + 0xC)] & 2) == 0)
        return cmd[1] == 0 ? 3 : 0;
    return cmd[1] == 1 ? 3 : 0;
}

/* 0x00198A60, 0x50 bytes. Condition: variable cmd[0] compares (operator cmd[2]) with
 * cmd[1]. */
u32 func_00198A60(u16 *cmd)
{
    return func_00197A70(cmd[2], g_005BC260[cmd[0]], cmd[1]) != 0 ? 3 : 0;
}

/* 0x00198AB0, 0x1DC bytes. Condition by kind cmd[0]: 0 switch 5 compares (operator cmd[2])
 * with cmd[1]; 1 never met (a switch on the scenario kind whose cases were all emptied); 2 the
 * stage reached (from 1) lies between cmd[1] and cmd[2] (0: no bound), in mode 4. */
u32 func_00198AB0(short *cmd)
{
    if (cmd[0] == 2) {
        if (g_00669F60[0] & 4) {
            int s = g_00669F98[0] + 1;

            if ((cmd[1] == 0 || cmd[1] <= s) && (cmd[2] == 0 || s <= cmd[2]))
                return 3;
        }
    } else if (cmd[0] == 1) {
        if (g_00669D81[0] >= 3 && g_00669DB8[0] == 0) {
            switch (g_00669DE8[0]) {
            case 0: break;
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            case 11: break;
            case 12: break;
            case 13: break;
            case 14: break;
            case 15: break;
            case 16: break;
            case 17: break;
            case 18: break;
            case 19: break;
            case 20: break;
            case 21: break;
            case 22: break;
            case 23: break;
            case 24: break;
            case 25: break;
            }
        }
    } else if (cmd[0] == 0) {
        if (func_00197A70(cmd[2], g_005BD740[5], cmd[1]) != 0)
            return 3;
    }
    return 0;
}

/* 0x00198C90, 0xB8 bytes. Condition: player cmd[2]'s score (+0x90; 2: the larger of both
 * with two players) compares (operator cmd[1]) with variable cmd[0]. */
u32 func_00198C90(u16 *cmd)
{
    int v;

    if (cmd[2] == 2) {
        v = PSET(0, 0x90);
        if ((g_00669F60[0] & 2) && v < PSET(1, 0x90))
            v = PSET(1, 0x90);
    } else {
        v = PSET(cmd[2], 0x90);
    }
    return func_00197A70(cmd[1], v, g_005BC260[cmd[0]]) != 0 ? 3 : 0;
}

/* 0x00198D50, 0x80 bytes. Condition: variable cmd[0] compares (operator cmd[2]) with cmd[3]
 * percent of variable cmd[1]. */
u32 func_00198D50(u16 *cmd)
{
    return func_00197A70(cmd[2], g_005BC260[cmd[0]], g_005BC260[cmd[1]] * cmd[3] / 100) != 0
               ? 3 : 0;
}

/* 0x00198DD0, 0x90 bytes, matching. Condition: officer cmd[0] holds a base with flag 2. */
u32 func_00198DD0(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 0), b;

    if (id < 0x1AD && (b = U32(g_00693970[id], 0x10)) < 0x47 && (U32(BASE68(b), 0x64) & 2))
        return 3;
    return 0;
}

/* 0x00198E60, 0x90 bytes. Condition: player cmd[0]'s +0x8C less variable cmd[1] compares
 * (operator cmd[3]) with cmd[2]; met for that player alone. */
u8 func_00198E60(u16 *cmd)
{
    u8 r = 0;

    if (func_00197A70(cmd[3], PSET(cmd[0], 0x8C) - g_005BC260[cmd[1]], cmd[2]) != 0)
        r = cmd[0] == 0 ? 1 : 2;
    return r;
}

/* 0x00198EF0, 0x1AC bytes. Condition: officer cmd[0]'s +0x60 (on the field) compares
 * (operator cmd[2]) with cmd[1]; for the players' officers, operators above 1 are met per
 * player, the others only when every player in the battle meets them. */
u32 func_00198EF0(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]), r;
    int k;

    if (func_00185EC0(id) == 0) {
        u8 *o = g_00693970[id];

        if (on_field(U32(o, 0x80)) && func_00197A70(cmd[2], U32(o, 0x60), cmd[1]) != 0)
            return 3;
        return 0;
    }
    if (cmd[2] > 1) {
        r = 0;
        for (k = 0; k < 2; k++) {
            if (PLAYER_ON(k) && func_00197A70(cmd[2], U32(func_0035DCD0(k), 0x60), cmd[1]) != 0)
                r |= k == 0 ? 1 : 2;
        }
        return r;
    }
    for (k = 0; k < 2; k++) {
        if (PLAYER_ON(k) && func_00197A70(cmd[2], U32(func_0035DCD0(k), 0x60), cmd[1]) == 0)
            return 0;
    }
    return 3;
}

/* 0x001990A0, 0x78 bytes, matching. Condition: officer cmd[0]'s level (+0x74, from 1) compares
 * (operator cmd[2]) with cmd[1]. */
u32 func_001990A0(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 0);

    if (id < 0x1AD && func_00197A70(cmd[2], U8(g_00693970[id], 0x74) + 1, cmd[1]) != 0)
        return 3;
    return 0;
}

/* 0x00199120, 0xF4 bytes. Condition: officer cmd[0]'s life in percent (record +0x4E / +0x4C,
 * or its battle officer's +0x82 / +0x80 in battle) compares (operator cmd[2]) with cmd[1]. */
u32 func_00199120(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 0);
    int v;

    if (id >= 0x1AD)
        return 0;
    if ((U32(g_00693970[id], 0x80) & 0x20000) == 0) {
        u8 *o = g_00693970[id];

        v = *(short *)(o + 0x4E) * 100 / *(short *)(o + 0x4C);
    } else {
        u8 *b = g_00693970[0] + 0x100C0 + U32(g_00693970[id], 0x14) * 0xC0;

        v = *(short *)(b + 0x82) * 100 / *(short *)(b + 0x80);
    }
    if (func_00197A70(cmd[2], v, cmd[1]) != 0)
        return 3;
    return 0;
}

extern u8 g_0073DF33[];                  /* the second player's record (bit 2) */
extern u8 g_00669FA9[0x10];              /* (settings) switches 2, 3 (+0, +1), 6-8 (+8-+0xA) */
#ifdef SW2E_PC
extern ps2ptr g_005BD724_a;
#define g_005BD724 ((u8 *)PS2_PTR(g_005BD724_a))
#define g_005BD724_SET(v) (g_005BD724_a = PS2_ADDR(v))
#else
extern u8 *g_005BD724;
#define g_005BD724_a (*(ps2ptr *)&g_005BD724)
#define g_005BD724_SET(v) (g_005BD724 = (v))
#endif
extern u32 g_00669F74;                   /* (settings) a count of the values at +0x18 */
extern int g_00669F78[0x40];
extern int g_005BC1A0[24][2];            /* the scenario timers (+4: the time) */

/* Base number of a base pointer. */
#define BASE_OF(b) (((b) - BASE68(0)) / 0x68)
/* Record number of a record pointer. */
#define REC_OF(o) (((o) - g_00693970[0]) / 0x88)

/* 0x00199220, 0x124 bytes. Condition: officer cmd[1]'s +0x4A (its leader?) is officer cmd[0]
 * (or a player's officer, met per player). */
u32 func_00199220(u16 *cmd)
{
    u32 a = func_00185ED0(cmd[0]), b = func_00185ED0(cmd[1]), r = 0, l;
    int k;

    if (func_00185EC0(b) != 0)
        return 0;
    l = *(u16 *)(g_00693970[b] + 0x4A);
    if (l == 0x1AD)
        return 0;
    if (func_00185EC0(a) == 0)
        return a == l ? 3 : 0;
    for (k = 0; k < 2; k++) {
        if (PLAYER_ON(k) && l == (func_0035DC70(k) & 0xFFFF))
            r |= k == 0 ? 1 : 2;
    }
    return r;
}

/* 0x00199350, 0xF8 bytes. Condition: scenario switch cmd[0] is (cmd[1] = 1) or is not (0)
 * on. */
u32 func_00199350(u16 *cmd)
{
    u8 v;

    switch (cmd[0]) {
    case 0: v = g_005BD740[0]; break;
    case 1: v = (g_0073DF33[0] & 7) >> 2 != 0; break;
    case 2: v = g_00669FA9[0]; break;
    case 3: v = g_00669FA9[1]; break;
    case 4: v = g_005BD740[4]; break;
    case 5: v = g_005BD740[1]; break;
    case 6: v = g_00669FA9[8]; break;
    case 7: v = g_00669FA9[9]; break;
    case 8: v = g_00669FA9[10]; break;
    case 9: v = g_005BD740[2]; break;
    default: return 0;
    }
    return AGREE(v, cmd[1]);
}

/* 0x00199450, 0x70 bytes. Condition: func_0027EA10 of byte cmd[0] of the table at
 * g_005BD724 + 0x2C is (cmd[1]) true. */
u32 func_00199450(u16 *cmd)
{
    u32 r = func_0027EA10(g_005BD724[cmd[0] + 0x2C]);

    return AGREE(r, cmd[1]);
}

/* 0x001994C0, 0x9C bytes. Condition: value cmd[0] (0 past the count) in percent of
 * func_001839D0 compares (operator cmd[2]) with cmd[1]. */
u32 func_001994C0(u16 *cmd)
{
    int v = cmd[0] < g_00669F74 ? g_00669F78[cmd[0]] : 0;

    return func_00197A70(cmd[2], v * 100 / func_001839D0(), cmd[1]) != 0 ? 3 : 0;
}

/* 0x00199560, 0xDC bytes. Condition: officer cmd[0]'s base's +0x4C (in modes 4 / 8: 350, or
 * 650 for an owner of side 1+) compares (operator cmd[2]) with cmd[1]. */
u32 func_00199560(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 0), b;
    int v;

    if (id >= 0x1AD || (b = U32(g_00693970[id], 0x10)) >= 0x47)
        return 0;
    if ((g_00669F60[0] & 0xC) == 0)
        v = U32(BASE68(b), 0x4C);
    else
        v = U8(PTR(BASE68(b), 0), 0x79) == 0 ? 350 : 650;
    if (func_00197A70(cmd[2], v, cmd[1]) != 0)
        return 3;
    return 0;
}

/* 0x00199640, 0x6C bytes. Condition: timer cmd[0] (in 50ths) compares (operator cmd[2]) with
 * cmd[1]. */
u32 func_00199640(u16 *cmd)
{
    return func_00197A70(cmd[2], g_005BC1A0[cmd[0]][1] / 50, cmd[1]) != 0 ? 3 : 0;
}

/* 0x001996B0, 0xA4 bytes. Condition: base func_0033F110(cmd[0])'s kind (func_002F27D0) is
 * (cmd[2] = 1) or is not cmd[1]. */
u32 func_001996B0(u16 *cmd)
{
    u8 *b = (u8 *)(func_0033F110(cmd[0]));
    u16 k;

    if (b == 0)
        return 0;
    k = func_002F27D0(*((u16 *)func_00338410(BASE_OF(b))));
    if (cmd[2] == 1) {
        if (k == cmd[1])
            return 3;
    } else if (k != cmd[1]) {
        return 3;
    }
    return 0;
}

/* 0x00199760, 0xE8 bytes. Condition: one of the 16 bases (func_0033EF80, flag 1) owned by side
 * cmd[0] is of kind cmd[1] (cmd[2] = 1), or none is (0). */
u32 func_00199760(u16 *cmd)
{
    u32 i;

    for (i = 0; i < 0x10; i++) {
        u8 *b = (u8 *)(func_0033EF80(i));

        if ((U32(b, 0x64) & 1) && cmd[0] == U8(PTR(b, 0), 0x79)
            && func_002F27D0(*((u16 *)func_00338410(BASE_OF(b)))) == cmd[1])
            return cmd[2] == 1 ? 3 : 0;
    }
    return cmd[2] == 0 ? 3 : 0;
}

/* 0x00199850, 0x70 bytes. Condition: func_0034EDB0 of func_0034EC80(cmd[0]) is (cmd[2] = 1)
 * or is not cmd[1]. */
u32 func_00199850(u16 *cmd)
{
    u32 h = func_0034EC80(cmd[0]);

    if (cmd[2] == 0) {
        if (cmd[1] != func_0034EDB0((unsigned char *)PS2_PTR(h)))
            return 3;
    } else {
        if (cmd[1] == func_0034EDB0((unsigned char *)PS2_PTR(h)))
            return 3;
    }
    return 0;
}

/* 0x001998C0, 0xE4 bytes. Condition: officer cmd[0] (present, flag 0x400) has a base
 * (func_0034A740) of kind (cmd[2] = 1) or not of kind cmd[1]. */
u32 func_001998C0(u16 *cmd)
{
    u32 f = U32(g_00693970[cmd[0]], 0x80);
    u16 k;

    if ((f & 1) == 0 || (f & 0x400) == 0)
        return 0;
    k = func_002F27D0(*((u16 *)func_00338410(BASE_OF(func_0034A740(g_00693970[cmd[0]])))));
    if (cmd[2] == 1) {
        if (k == cmd[1])
            return 3;
    } else if (k != cmd[1]) {
        return 3;
    }
    return 0;
}

/* 0x001999B0, 0x80 bytes. func_00199120 for the officer func_0034B130(cmd[0]). */
u32 func_001999B0(u16 *cmd)
{
    u8 *o = func_0034B130(cmd[0]);
    u16 c[3];

    if (o == 0)
        return 0;
    c[0] = REC_OF(o);
    c[1] = cmd[1];
    c[2] = cmd[2];
    return func_00199120(c);
}

/* 0x00199A30, 0xC0 bytes, matching. func_00198850 for the officers func_0034B130(cmd[1]) and
 * func_0034B130(cmd[3]). */
u32 func_00199A30(u16 *cmd)
{
    u8 *a = func_0034B130(cmd[1]), *b = func_0034B130(cmd[3]);
    u16 c[5];

    if (a == 0 || b == 0)
        return 0;
    c[0] = cmd[0];
    c[1] = REC_OF(a);
    c[2] = cmd[2];
    c[3] = REC_OF(b);
    c[4] = cmd[4];
    return func_00198850(c);
}

/* 0x00199AF0, 0x88 bytes. func_001987A0 for the officer func_0034B130(cmd[0]). */
u32 func_00199AF0(u16 *cmd)
{
    u8 *o = func_0034B130(cmd[0]);
    u16 c[4];

    if (o == 0)
        return 0;
    c[0] = REC_OF(o);
    c[1] = cmd[1];
    c[2] = cmd[2];
    c[3] = cmd[3];
    return func_001987A0(c);
}

#ifdef SW2E_PC
extern ps2ptr g_005BA6A0_a;                   /* the officer table (0x2C bytes each) */
#define g_005BA6A0 ((u8 *)PS2_PTR(g_005BA6A0_a))
#define g_005BA6A0_SET(v) (g_005BA6A0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6A0;
#define g_005BA6A0_a (*(ps2ptr *)&g_005BA6A0)
#define g_005BA6A0_SET(v) (g_005BA6A0 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005BA69C_a;                   /* the scenario file */
#define g_005BA69C ((u8 *)PS2_PTR(g_005BA69C_a))
#define g_005BA69C_SET(v) (g_005BA69C_a = PS2_ADDR(v))
#else
extern u8 *g_005BA69C;
#define g_005BA69C_a (*(ps2ptr *)&g_005BA69C)
#define g_005BA69C_SET(v) (g_005BA69C = (v))
#endif

int func_0019A4F0(u8 *c, int mode);

/* 0x00199B80, 0xAC bytes. func_001985B0 (big cells) for the officer func_0034B130(cmd[1]). */
u32 func_00199B80(short *cmd)
{
    u8 *o = func_0034B130(cmd[1]);
    short c[8];

    if (o == 0)
        return 0;
    c[0] = cmd[0];
    c[1] = REC_OF(o);
    c[2] = cmd[2];
    c[3] = cmd[3];
    c[4] = cmd[4];
    c[5] = cmd[5];
    c[6] = cmd[6];
    c[7] = cmd[7];
    return func_001985B0(c, 1);
}

/* 0x00199C30, 0xC4 bytes. func_00198170 for the officers func_0034B130(cmd[0]) and
 * func_0034B130(cmd[1]). */
u32 func_00199C30(u16 *cmd)
{
    u8 *a = func_0034B130(cmd[0]), *b = func_0034B130(cmd[1]);
    u16 c[6];

    if (a == 0 || b == 0)
        return 0;
    c[0] = REC_OF(a);
    c[1] = REC_OF(b);
    c[2] = cmd[2];
    c[3] = cmd[3];
    c[4] = cmd[4];
    c[5] = cmd[5];
    return func_00198170(c);
}

/* 0x00199D00, 0xA0 bytes, matching. Conditions 0x23-0x28 of record `c` (arguments from +2). */
u8 func_00199D00(u8 *c, u32 code)
{
    switch (code) {
    case 0x23: return func_00197E40((u16 *)(c + 2));
    case 0x24: return func_00197DB0((short *)(c + 2));
    case 0x25: return func_00197D90((u16 *)(c + 2));
    case 0x26: return func_00197BD0((u16 *)(c + 2));
    case 0x27: return func_00197B70((u16 *)(c + 2));
    case 0x28: return func_00197AF0((u16 *)(c + 2));
    default: return 0;
    }
}

/* 0x00199DA0, 0x150 bytes. Conditions 0x13-0x22. */
u8 func_00199DA0(u8 *c, u32 code)
{
    u16 *a = (u16 *)(c + 2);

    switch (code) {
    case 0x13: return func_00198A60(a);
    case 0x14: return func_001989E0(a, 0);
    case 0x15: return func_001989E0(a, 1);
    case 0x16: return func_00198970(a);
    case 0x17: return func_00198850(a);
    case 0x18: return func_001987A0(a);
    case 0x19: return func_001985B0((short *)a, 1);
    case 0x1A: return func_00198490(a);
    case 0x1B: return func_001985B0((short *)a, 0);
    case 0x1C: return func_00198170(a);
    case 0x1D: return func_00197F80(a);
    case 0x1E: return func_00197E70(a);
    case 0x1F: return func_00199A30(a);
    case 0x20: return func_00199AF0(a);
    case 0x21: return func_00199B80((short *)a);
    case 0x22: return func_00199C30(a);
    default: return 0;
    }
}

/* 0x00199EF0, 0x6C bytes. Conditions 0x00-0x12. */
u8 func_00199EF0(u8 *c, u32 code)
{
    u16 *a = (u16 *)(c + 2);

    switch (code) {
    case 0: return func_00199640(a);
    case 1: return func_00199560(a);
    case 2: return func_001994C0(a);
    case 3: return func_00199450(a);
    case 4: return func_00199350(a);
    case 5: return func_00199220(a);
    case 6: return func_00199120(a);
    case 7: return func_001990A0(a);
    case 8: return func_00198EF0(a);
    case 9: return func_00198E60(a);
    case 10: return func_00198DD0(a);
    case 11: return func_00198D50(a);
    case 12: return func_00198C90(a);
    case 13: return func_00198AB0((short *)a);
    case 14: return func_001996B0(a);
    case 15: return func_00199760(a);
    case 16: return func_00199850(a);
    case 17: return func_001998C0(a);
    case 18: return func_001999B0(a);
    }
    return 0;
}

/* 0x0019A060, 0x94 bytes. Evaluates condition record `c` (+0 its code): the players for
 * whom it is met go to +1. */
void func_0019A060(u8 *c)
{
    u8 code = c[0], r;

    if (code < 0x13)
        r = func_00199EF0(c, code);
    else if (code >= 0x13 && code <= 0x22)
        r = func_00199DA0(c, code);
    else if (code >= 0x23 && code <= 0x28)
        r = func_00199D00(c, code);
    else
        r = 0;
    c[1] = r;
}

/* 0x0019A100, 0x248 bytes. Re-evaluates condition record `c` (codes 0x13-0x22) only when
 * the argument after its own ones is set; codes outside give 0. */
void func_0019A100(u8 *c)
{
    u8 code = c[0], r;
    u16 *a = (u16 *)(c + 2);

    if (code <= 0x12 || code >= 0x23)
        return;
    r = c[1];
    switch (code) {
    case 0x13: if (*(short *)(c + 8) != 0) r = func_00198A60(a); break;
    case 0x14: if (*(short *)(c + 6) != 0) r = func_001989E0(a, 0); break;
    case 0x15: if (*(short *)(c + 6) != 0) r = func_001989E0(a, 1); break;
    case 0x16: if (*(short *)(c + 6) != 0) r = func_00198970(a); break;
    case 0x17: if (*(short *)(c + 10) != 0) r = func_00198850(a); break;
    case 0x18: if (*(short *)(c + 8) != 0) r = func_001987A0(a); break;
    case 0x19: if (*(short *)(c + 0x10) != 0) r = func_001985B0((short *)a, 1); break;
    case 0x1A: if (*(short *)(c + 0xE) != 0) r = func_00198490(a); break;
    case 0x1B: if (*(short *)(c + 0x10) != 0) r = func_001985B0((short *)a, 0); break;
    case 0x1C: if (*(short *)(c + 0xC) != 0) r = func_00198170(a); break;
    case 0x1D: if (*(short *)(c + 8) != 0) r = func_00197F80(a); break;
    case 0x1E: if (*(short *)(c + 8) != 0) r = func_00197E70(a); break;
    case 0x1F: if (*(short *)(c + 10) != 0) r = func_00199A30(a); break;
    case 0x20: if (*(short *)(c + 8) != 0) r = func_00199AF0(a); break;
    case 0x21: if (*(short *)(c + 0x10) != 0) r = func_00199B80((short *)a); break;
    case 0x22: if (*(short *)(c + 0xC) != 0) r = func_00199C30(a); break;
    default: r = 0; break;
    }
    c[1] = r;
}

/* 0x0019A350, 0xEC bytes. An "or" group (+2 its number of conditions, which follow in 0x12-byte
 * records): +1 becomes the first of 1 or 2 met by a part (3 for any other non-zero). Returns the
 * records used. */
int func_0019A350(u8 *g, int mode)
{
    u32 n, k;
    int used = 0;
    u8 *c = g + 0x12;

    g[1] = 0;
    n = *(u16 *)(g + 2);
    for (k = 0; k < n; k++) {
        int m = func_0019A4F0(c, mode);
        u8 r = c[1];

        if (r != 0 && g[1] != 1) {
            if (r == 1)
                g[1] = 1;
            else if (g[1] != 2) {
                if (r == 2)
                    g[1] = 2;
                else
                    g[1] = 3;
            }
        }
        used += m;
        c += m * 0x12;
    }
    return used;
}

/* 0x0019A440, 0xA8 bytes. An "and" group: +1 is the players for whom every part is met. */
int func_0019A440(u8 *g, int mode)
{
    u32 n, k;
    int used = 0;
    u8 *c = g + 0x12;

    g[1] = 3;
    n = *(u16 *)(g + 2);
    for (k = 0; k < n; k++) {
        int m = func_0019A4F0(c, mode);
        u8 *r = c + 1;

        used += m;
        c += m * 0x12;
        g[1] &= *r;
    }
    return used;
}

/* 0x0019A4F0, 0xA8 bytes. Evaluates record `c` (0xFE an "or" group, 0xFF an "and" group;
 * mode 2 re-evaluates, mode 1 keeps a met one as met by both). Returns the records used. */
int func_0019A4F0(u8 *c, int mode)
{
    int used = 1;

    if ((signed char)c[0] == -2)
        used = func_0019A350(c, mode) + 1;
    else if ((signed char)c[0] == -1)
        used = func_0019A440(c, mode) + 1;
    else if (mode == 2)
        func_0019A100(c);
    else if (mode == 1 && (c[1] & 3) != 0)
        c[1] = 3;
    else
        func_0019A060(c);
    return used;
}

/* 0x0019A5A0, 0x108 bytes. Maps an old condition code to the current one (4, 8 and 16 to 0; the
 * others shift down; above 0x1C unchanged). */
u32 func_0019A5A0(u32 code)
{
    switch (code) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 5: return 4;
    case 6: return 5;
    case 7: return 6;
    case 9: return 7;
    case 10: return 8;
    case 11: return 9;
    case 12: return 10;
    case 13: return 11;
    case 14: return 12;
    case 15: return 13;
    case 17: return 14;
    case 18: return 15;
    case 19: return 16;
    case 20: return 17;
    case 21: return 18;
    case 22: return 19;
    case 23: return 20;
    case 24: return 21;
    case 25: return 22;
    case 26: return 23;
    case 27: return 24;
    case 28: return 25;
    case 4:
    case 8:
    case 16: return 0;
    }
    return code;
}

/* 0x0019A6B0, 0x68 bytes. Loads officers 0x24E-0x251 of the officer table from `p`; returns the end. */
u8 *func_0019A6B0(u8 *p)
{
    u32 k;
    u8 *o = g_005BA6A0 + 0x6568;

    for (k = 0x24E; k < 0x252; k++, p += 0x2C, o += 0x2C)
        func_00118AC0((unsigned int *)(o), p, 0x2C);
    return p;
}

/* 0x0019A720, 0x68 bytes. Saves them to `p`; returns the end. */
u8 *func_0019A720(u8 *p)
{
    u32 k;
    u8 *o = g_005BA6A0 + 0x6568;

    for (k = 0x24E; k < 0x252; k++, p += 0x2C, o += 0x2C)
        func_00118AC0((unsigned int *)(p), o, 0x2C);
    return p;
}

/* 0x0019A790, 0x20 bytes. Frees the scenario file. */
void func_0019A790(void)
{
    func_00102EC0(g_005BA69C);
}
