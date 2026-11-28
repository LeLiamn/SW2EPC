/*
 * sc_ctrl.c - scenario control (original source file sc_ctrl.c: its name is passed to the file
 * loader at 0x00185D10, from line 1922 of the original, so the file starts well before it).
 * Written so far: simple functions from 0x00185CA0.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The officers' records here are the 0x88-byte ones at 0x00693970 (+0x80 flags); id 0x1AD means
 * none, 0x1AE / 0x1AF stand for a player's officer.
 */

#define SW2E_FILE_SC_CTRL_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

#pragma opt_unroll_loops on

/* A table file: a count, then the entries. */
typedef struct {
    u32 *data;
    u32 *entries;            /* data + 1 */
    u32 count;
    u8 pad[0x1B10 - 0xC];
    u32 timers[0x18][2];     /* +0x1B10 */
    int vars[0x10];          /* +0x1BD0 */
} ScTable;

extern ScTable g_005BA690;               /* LINKDATA entry 0x35 */
extern u32 g_005BA6A4[5];
extern u8 g_00693970[][0x88];            /* the officers' records (+0x80 flags) */
extern int g_00669F6C[4];                /* +0: the game mode (1: ?), inside the settings */
extern const char g_00424E40[];          /* "sc_ctrl.c" */

void func_0018A290(u8 *c, u8 v, int x);

/* 0x00185CA0, 0x40 bytes, matching. The scenario's frame: func_00185390 in mode 1, else func_001854C0. */
void func_00185CA0(void)
{
    if (g_00669F6C[0] == 1)
        func_00185390();
    else
        func_001854C0();
}

/* 0x00185CE0, 0x8 bytes, matching. Nothing. */
void func_00185CE0(void)
{
}

/* 0x00185CF0, 0x20 bytes, matching. Frees the table. */
void func_00185CF0(void)
{
    func_00102EC0((unsigned char *)(g_005BA690.data));
}

/* 0x00185D10, 0x5C bytes, matching. Loads the table (LINKDATA entry 0x35). */
void func_00185D10(void)
{
    g_005BA690.data = func_001026D0(1, 0x35, 0, 1, 0, 0, g_00424E40, 0x782);
    g_005BA690.count = *g_005BA690.data;
    g_005BA690.entries = g_005BA690.data + 1;
}

/* 0x00185D70, 0x2C bytes, matching. Shuts the scenario control down. */
void func_00185D70(void)
{
    func_0023ED70();
    func_0019A790();
    func_00185CF0();
}

/* 0x00185DA0, 0x54 bytes, matching. Starts the scenario control. */
void func_00185DA0(void)
{
    func_00185D10();
    func_0019A7B0();
    func_0023ED90();
    g_005BA6A4[0] = 0;
    g_005BA6A4[1] = 0;
    g_005BA6A4[2] = 0;
    g_005BA6A4[3] = 0;
    g_005BA6A4[4] = 0;
}

/* 0x00185EC0, 0xC bytes, matching. Whether `id` is 0x1AF. */
int func_00185EC0(u32 id)
{
    return id == 0x1AF;
}

/* 0x00185ED0, 0x5C bytes, matching. The real officer of `id` (0x1AD / 0x1AE: the players' officers). */
u32 func_00185ED0(u32 id)
{
    if (id <= 0x1AC)
        return id;
    if (id == 0x1AD)
        return func_0035DC70(0) & 0xFFFF;
    if (id == 0x1AE)
        return func_0035DC70(1) & 0xFFFF;
    return id;
}

/* 0x00185E00, 0xC0 bytes. The officer `id` stands for, if it is on the field (flag 1, none of
 * 0x8C40002; with `free`, not flags 0x30 either); 0x1AD for none. */
u32 func_00185E00(u32 id, int free)
{
    u32 f;
    int ok;

    id = func_00185ED0(id);
    if (func_00185EC0(id) != 0)
        return 0x1AD;
    f = U32(g_00693970[id], 0x80);
    ok = 0;
    if ((f & 1) && (((f & 0x8C40002) != 0) ^ 1))
        ok = 1;
    if (ok) {
        if (free != 0 && (f & 0x30))
            id = 0x1AD;
    } else {
        id = 0x1AD;
    }
    return id;
}

/* 0x00185F30, 0x80 bytes. Marks command `a` done (flag 2) and applies its `a[5]` entries
 * (0x10 bytes each, from `c`) with `b[1]`. */
void func_00185F30(u8 *a, u8 *b, u8 *c, int x)
{
    u8 n, v;
    u32 i;

    a[0] |= 2;
    n = a[5];
    v = b[1];
    for (i = 0; i < n; i++, c += 0x10)
        func_0018A290(c, v, x);
}

/* 0x00185FB0, 0x94 bytes, matching. Tests command `a`'s condition `b` (twice with `both`); marks it met
 * (flag 1). Whether it was. */
int func_00185FB0(u8 *a, u8 *b, int both)
{
    if (a[4] > 0) {
        if (both != 0) {
            func_0019A4F0(b, 1);
            if ((b[1] & 3) == 0)
                return 0;
        }
        func_0019A4F0(b, 0);
        if ((b[1] & 3) == 0)
            return 0;
    }
    a[0] |= 1;
    return 1;
}

/* The scenario's commands (0x005BA7CC): command i is at data + the offset at data + 0xC + 4i;
 * each has a list of conditions (0x12 bytes each, +1 its state) and entries. */
typedef struct {
    u8 *data;
    u32 count;
    u32 pad[2];
    u8 **conds;              /* +0x10 */
    u8 **entries;            /* +0x14 */
} ScCommands;

extern ScCommands g_005BA7CC;

#define SC_CMD(i) (g_005BA7CC.data + *(u32 *)(g_005BA7CC.data + (i) * 4 + 0xC))

/* 0x00186050, 0x130 bytes. Each frame (unless func_0032E7B0), the commands not yet met or done
 * and not of the second kind (+2) are tested; met ones run their entries (+3), or ask
 * func_00183410 first and are cleared if refused. */
void func_00186050(void)
{
    ScCommands *t;
    u32 n, i;

    if (func_0032E7B0() != 0)
        return;
    t = &g_005BA7CC;
    n = t->count;
    for (i = 0; i < n; i++) {
        u8 *c = t->data + *(u32 *)(t->data + i * 4 + 0xC);

        if ((c[0] & 3) == 0 && c[2] == 0) {
            u8 *cond = t->conds[i];

            if (func_00185FB0(c, cond, 1) != 0) {
                if (c[3] == 0) {
                    if (func_00183410(0, i, cond[1], c[1], 0) == 0)
                        c[0] &= ~3;
                } else {
                    func_00185F30(c, cond, t->entries[i], 0);
                }
            }
        }
    }
}

/* 0x00186190, 0xEC bytes. Runs the commands of the second kind (+2) whose conditions are met
 * (func_0027DEA0 when there are none). */
void func_00186190(void)
{
    u32 n = g_005BA7CC.count, i;

    if (n == 0) {
        func_0027DEA0(0, 2);
        return;
    }
    for (i = 0; i < n; i++) {
        u8 *c = SC_CMD(i);

        if (c[2] != 0) {
            u8 *cond = g_005BA7CC.conds[i];

            if (func_00185FB0(c, cond, 0) != 0)
                func_00185F30(c, cond, g_005BA7CC.entries[i], 1);
        }
    }
}

/* 0x00186280, 0xF8 bytes. Restores the commands' states from a save (`p`); returns the end. */
u8 *func_00186280(u8 *p)
{
    u32 n = g_005BA7CC.count, i, j;

    for (i = 0; i < n; i++) {
        u8 *cond = g_005BA7CC.conds[i];
        u8 *c = SC_CMD(i);
        u32 m = c[4];

        c[0] = *p++;
        for (j = 0; j < m; j++) {
            cond[1] = *p++;
            cond += 0x12;
        }
    }
    return p;
}

/* 0x00186380, 0xF8 bytes. Saves the commands' states into `p`; returns the end. */
u8 *func_00186380(u8 *p)
{
    u32 n = g_005BA7CC.count, i, j;

    for (i = 0; i < n; i++) {
        u8 *cond = g_005BA7CC.conds[i];
        u8 *c = SC_CMD(i);
        u32 m = c[4];

        *p++ = c[0];
        for (j = 0; j < m; j++) {
            *p++ = cond[1];
            cond += 0x12;
        }
    }
    return p;
}

/* 0x00186480, 0x24 bytes. Whether bit 0 of `x` is clear. */
int func_00186480(int x)
{
    u8 b = x;

    if (b & 1)
        return 0;
    return 1;
}

/* The game state object at 0x00693970 holds the 0x88-byte officer records (+0), 0x68-byte
 * base records (+0xE3E8, 0x47 of them?) and the battle officers (0xC0 each, +0x100C0). */
#define REC88(i) (g_00693970[0] + (i) * 0x88)
#define BASE68(v) (g_00693970[0] + 0xE3E8 + (v) * 0x68)

extern u8 g_006A3A30[][0xC0];            /* the battle officers (game state +0x100C0) */

void func_001EE3A0(u8 *o);
void func_001EE9C0(u8 *o, u8 a);
void func_002075A0(float yaw, u8 *r, float *out, int a);
void func_001EE3B0(u8 *o);

/* 0x001864B0, 0x2C8 bytes. Moves officer record `o` to `pos` facing `yaw` (wrapped to -pi..pi):
 * its map cells (5000 and 1000 units), its links reset; an officer on the field (flag 0x20000)
 * places its units, and their companions, around the point. `keep`: keep its state. */
void func_001864B0(float yaw, u8 *o, float *pos, int keep)
{
    float x, y, a;

    if (keep == 0) {
        if ((U32(o, 0x80) & 2) == 0) {
            if (U32(o, 0x80) & 0x40000)
                func_001EEBF0(PS2_ADDR(o));
            func_001F1910(o);
        } else {
            func_001EE3A0(o);
        }
    } else {
        func_001F1910(o);
    }
    x = pos[0];
    y = pos[1];
    *(float *)(o + 0x28) = pos[0];
    *(float *)(o + 0x2C) = pos[1];
    *(float *)(o + 0x30) = pos[0];
    *(float *)(o + 0x34) = pos[1];
    U8(o, 0x40) = (u8)((int)x / 5000);
    U8(o, 0x41) = (u8)((int)y / 5000);
    U8(o, 0x46) = (u8)((int)x / 1000);
    U8(o, 0x47) = (u8)((int)y / 1000);
    if (3.1415927f < yaw)
        a = yaw - 6.2831855f;
    else if (yaw <= -3.1415927f)
        a = yaw + 6.2831855f;
    else
        a = yaw;
    *(float *)(o + 0x20) = a;
    func_001EE9C0(o, U8(o, 0x7B));
    if (PTR(o, 0x18) != 0) {
        func_001ED160(PS2_ADDR(o), PS2_ADDR(PTR(o, 0x18)), 0);
        PTR(o, 0x18) = 0;
        U32(o, 0x84) |= 0x10;
    }
    PTR(o, 0x1C) = 0;
    U32(o, 0x84) |= 0x10;
    U8(o, 0x42) = 0;
    U8(o, 0x43) = 0;
    U8(o, 0x7A) = 0;
    if (U32(o, 0x80) & 0x20000) {
        u8 *r;

        for (r = g_006A3A30[U32(o, 0x14)]; r != 0; r = PTR(r, 4)) {
            u8 *u;
            float p[4];
            int k;

            func_00207260(r, (unsigned char *)(pos));
            u = PTR(r, 0x14);
            *(float *)(u + 0x238) = yaw;
            U8(u, 0x27C) &= ~1;
            *(float *)(u + 0x54) = yaw;
            for (k = 0; k < 4; k++)
                p[k] = *(float *)(r + 0x20 + k * 4);
            func_002075A0(yaw, r, p, 0);
            func_001660C0(u, p);
            if (PTR(r, 0xC) != 0)
                func_001660C0(PTR(PTR(r, 0xC), 0x14), p);
        }
    }
    func_001F1A30(o);
}

/* 0x00186780, 0xD0 bytes, matching. Command: send officer cmd[1] (if free and on the field) to its base
 * (cmd[0] = 0, a base under 0x47), else func_001EEC50. */
void func_00186780(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[1]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);
        u32 f = U32(o, 0x80);

        if ((f & 0x30) == 0 && (f & 0x840002) == 0) {
            f = U32(o, 0x10);
            if (cmd[0] == 0 && f < 0x47)
                func_001D4C20(BASE68(f), 1);
            else
                func_001EEC50(PS2_ADDR(o));
        }
    }
}

/* 0x001869F0, 0xD4 bytes, matching. Command: the reverse for officer cmd[1] (its base's func_001D4FB0,
 * else func_001D4C00 and func_001EE3B0). */
void func_001869F0(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[1]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);

        if ((U32(o, 0x80) & 0x30) == 0 && (U32(o, 0x80) & 0x840002) == 0) {
            u32 b = U32(o, 0x10);

            if (cmd[0] == 0 && b < 0x47) {
                func_001D4FB0(BASE68(b));
            } else {
                func_001D4C00(o);
                func_001EE3B0(o);
            }
        }
    }
}

extern u8 g_00669D70[];                  /* the scenario's event bits (in the settings) */

void func_001EE570(u8 *o);

/* Whether officer record `o` of side `side` stands in the area of cells x0-x1, z0-z1. */
static inline int in_area(u8 *o, u16 side, int x0, int z0, int x1, int z1)
{
    u16 c;
    int x, z;

    if (side != U8(o, 0x79))
        return 0;
    c = U16(o, 0x40);
    x = ((u8 *)&c)[0];
    z = ((u8 *)&c)[1];
    return !(x < x0) && !(x1 < x) && !(z < z0) && !(z1 < z);
}

/* 0x00186850, 0x194 bytes. Command: the base 0x46 (when active) and the officer 0x1AC, if
 * their officer stands in the area cmd[1]-cmd[4] with side cmd[0], get func_001D4FB0 /
 * func_001EE3B0. */
void func_00186850(u16 *cmd)
{
    int x0 = (u8)cmd[1], z0 = (u8)cmd[2], x1 = (u8)cmd[3], z1 = (u8)cmd[4];
    u8 *b = BASE68(0x46), *o;
    u32 f;
    int ok;

    if (U32(b, 0x64) & 1) {
        o = PTR(b, 0);
        f = U32(o, 0x80);
        ok = 0;
        if ((f & 1) && ((f & 0x8C40002) != 0) ^ 1)
            ok = 1;
        if (ok && in_area(o, cmd[0], x0, z0, x1, z1))
            func_001D4FB0(b);
    }
    o = REC88(0x1AC);
    f = U32(o, 0x80);
    ok = 0;
    if ((f & 1) && ((f & 0x8C40002) != 0) ^ 1)
        ok = 1;
    if (ok && in_area(o, cmd[0], x0, z0, x1, z1))
        func_001EE3B0(o);
}

/* 0x00186AD0, 0x1AC bytes. The same with func_001D5060 / func_001EE570, not for officers
 * with flag 0x8000. */
void func_00186AD0(u16 *cmd)
{
    int x0 = (u8)cmd[1], z0 = (u8)cmd[2], x1 = (u8)cmd[3], z1 = (u8)cmd[4];
    u8 *b = BASE68(0x46), *o;
    u32 f;
    int ok;

    if (U32(b, 0x64) & 1) {
        o = PTR(b, 0);
        f = U32(o, 0x80);
        ok = 0;
        if ((f & 1) && ((f & 0x8C40002) != 0) ^ 1)
            ok = 1;
        if (ok && cmd[0] == U8(o, 0x79) && (f & 0x8000) == 0
            && in_area(o, cmd[0], x0, z0, x1, z1))
            func_001D5060(b);
    }
    o = REC88(0x1AC);
    f = U32(o, 0x80);
    ok = 0;
    if ((f & 1) && ((f & 0x8C40002) != 0) ^ 1)
        ok = 1;
    if (ok && cmd[0] == U8(o, 0x79) && (f & 0x8000) == 0 && in_area(o, cmd[0], x0, z0, x1, z1))
        func_001EE570(o);
}

/* 0x00186C80, 0xD0 bytes, matching. Command: officer cmd[1]'s base (cmd[0] = 0) gets func_001D5060,
 * else the officer func_001EE570. */
void func_00186C80(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[1]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);
        u32 f = U32(o, 0x80);

        if ((f & 0x30) == 0 && (f & 0x840002) == 0) {
            if (cmd[0] == 0 && U32(o, 0x10) < 0x47)
                func_001D5060(BASE68(U32(o, 0x10)));
            else
                func_001EE570(o);
        }
    }
}

/* 0x00186D50, 0xCC bytes, matching. Command: officer cmd[0] (not beaten or away) gets its troops back:
 * +0x52 = +0x4E, at most +0x50; +0x74 cleared. */
void func_00186D50(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);

        if ((U32(o, 0x80) & 6) == 0 && (U32(o, 0x80) & 0x30) == 0) {
            short v, m, w;

            U8(o, 0x74) = 0;
            v = *(short *)(o + 0x4E);
            m = *(short *)(o + 0x50);
            w = m < v ? m : v;
            *(short *)(o + 0x52) = w > 0 ? (m < v ? m : v) : 0;
        }
    }
}

/* 0x00186E20, 0x98 bytes. Command: sets (cmd[1]) or clears event bit cmd[0]. */
void func_00186E20(u16 *cmd)
{
    u32 k = cmd[0];

    if (cmd[1] == 0)
        g_00669D70[(int)k >> 3] &= ~(1 << (k & 7));
    else
        g_00669D70[(int)k >> 3] |= 1 << (k & 7);
}

/* 0x00186EC0, 0x154 bytes. Command: changes value cmd[2] (0, 1, 2) by cmd[3] for officer
 * cmd[1]'s base (cmd[0] = 0) or the officer itself. */
void func_00186EC0(short *cmd)
{
    u32 id = func_00185ED0(cmd[1]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);

        if ((U32(o, 0x80) & 0x30) == 0) {
            if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
                u8 *b = BASE68(U32(o, 0x10));

                if (cmd[2] == 2)
                    func_001D4DE0(b, cmd[3]);
                else if (cmd[2] == 1)
                    func_001D4E40(b, cmd[3]);
                else if (cmd[2] == 0)
                    func_001D4EA0(b, cmd[3]);
            } else {
                if (cmd[2] == 2)
                    func_001EECE0(PS2_ADDR(o), cmd[3]);
                else if (cmd[2] == 1)
                    func_001EEDE0(PS2_ADDR(o), cmd[3]);
                else if (cmd[2] == 0)
                    func_001EEEE0(o, cmd[3]);
            }
        }
    }
}

/* 0x00187020, 0x8 bytes, matching. Nothing. */
void func_00187020(void)
{
}

extern u8 g_005BD740[8];                 /* scenario switches 0, 5, 9 (+0, +1, +2), 4 (+4) */
extern u8 g_00669FA9[0x10];              /* in the settings: switches 2, 3 (+0, +1), 6-8 (+8-+0xA) */
extern u8 g_0073DCA3[], g_0073DF33[];    /* the two players' records (bit 2: no camera follow) */
extern u32 g_00669F60[4];                /* +0: the battle flags */
extern float g_00424EE0[];               /* the eight facing angles */

void func_001EE3B0(u8 *o);

/* 0x00187030, 0x12C bytes. Command: sets scenario switch cmd[0] to (cmd[1] == 1); switch 1 is
 * the players' camera follow (not with battle flag 0x10). */
void func_00187030(u16 *cmd)
{
    u8 on = cmd[1] == 1;

    switch (cmd[0]) {
    case 0:
        g_005BD740[0] = on;
        break;
    case 1:
        if ((g_00669F60[0] & 0x10) == 0) {
            g_0073DCA3[0] = (g_0073DCA3[0] & ~4) | on << 2;
            g_0073DF33[0] = (g_0073DF33[0] & ~4) | on << 2;
        }
        break;
    case 2:
        g_00669FA9[0] = on;
        break;
    case 3:
        g_00669FA9[1] = on;
        break;
    case 4:
        g_005BD740[4] = on;
        break;
    case 5:
        g_005BD740[1] = on;
        break;
    case 6:
        g_00669FA9[8] = on;
        break;
    case 7:
        g_00669FA9[9] = on;
        break;
    case 8:
        g_00669FA9[0xA] = on;
        break;
    case 9:
        g_005BD740[2] = on;
        break;
    }
}

/* 0x00187160, 0x68 bytes. Command: by cmd[2], func_00186780, func_001869F0 or func_00186C80. */
void func_00187160(u16 *cmd)
{
    switch (cmd[2]) {
    case 0:
        func_00186C80(cmd);
        break;
    case 1:
        func_001869F0(cmd);
        break;
    case 2:
        func_00186780(cmd);
        break;
    }
}

/* 0x001871D0, 0x230 bytes. Command: puts officer cmd[1] (on the field; with `any`, even away)
 * in cell (cmd[2], cmd[3]) facing angle cmd[4]; for a base command (cmd[0] = 0) its 12
 * garrison officers go to their places around it (func_0019A800), or leave when there is
 * none. */
void func_001871D0(short *cmd, int any)
{
    u32 id = func_00185ED0(cmd[1]);
    float pos[2], yaw, x, z;
    u8 *o, *b;
    u32 k;

    if (func_00185EC0(id) != 0)
        return;
    o = REC88(id);
    if ((U32(o, 0x80) & 1) == 0 || (any == 0 && (U32(o, 0x80) & 0x30)))
        return;
    pos[0] = (float)*(u8 *)&cmd[2] * 1000.0f + 500.0f;
    pos[1] = (float)*(u8 *)&cmd[3] * 1000.0f + 500.0f;
    yaw = g_00424EE0[(u16)cmd[4]];
    func_001864B0(yaw, o, pos, 0);
    if (cmd[0] != 0 || U32(o, 0x10) >= 0x47)
        return;
    x = pos[0] / 100.0f;
    b = BASE68(U32(o, 0x10));
    z = pos[1] / 100.0f;
    for (k = 0; k < 0xC; k++, b += 4) {
        u8 *g = PTR(b, 4);

        if (g != 0) {
            short out[4];

            if (func_0019A800((unsigned char *)(out), k, (int)x, (int)z) == 0) {
                func_001D4C00(g);
                func_001EE3B0(g);
            } else {
                pos[0] = (float)out[1] * 100.0f;
                pos[1] = (float)out[2] * 100.0f;
                func_001864B0(yaw, g, pos, 0);
            }
        }
    }
}

/* 0x00187410, 0xD0 bytes, matching. Command: officer cmd[1] (not away) leaves its base (cmd[0] = 0) or
 * the map (func_001EEBF0); a beaten one gets func_001EE3A0. */
void func_00187410(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[1]);

    if (func_00185EC0(id) == 0) {
        u8 *o = REC88(id);
        u32 f = U32(o, 0x80);

        if ((f & 0x30) == 0) {
            if (f & 2) {
                func_001EE3A0(o);
            } else {
                if (cmd[0] == 0)
                    func_001D4C20(BASE68(U32(o, 0x10)), 0);
                else
                    func_001EEBF0(PS2_ADDR(o));
            }
        }
    }
}

/* The scenario's message window (0x005BC3A0) and its text (0x005BBF20). */
extern u8 g_005BC3A0[];
extern char g_005BBF20[];
extern char *g_005BC260[];               /* texts by index */
extern u32 g_005BC020, g_005BC028;       /* window kinds */
extern u32 g_005BC02C, g_005BC030, g_005BC034, g_005BC038, g_005BC03C, g_005BC048, g_005BC04C;
extern u32 g_005BC064;
extern u8 *g_005BD724;
extern u32 g_005BD728, g_005BD72C;
extern u8 *g_005BA6A0;                   /* officer table (0x2C bytes each, +6 a portrait?) */
extern u8 g_00669DB0[0x10];              /* in the settings: +0 bit 5 a display flag */
extern u32 g_00669DE8[][0x12];           /* per player settings (+0: the player's officer list) */

void func_002D6FA0(u8 *who, u8 *pos, int a);
void func_0022F4B0(char *to, u16 text);
void func_001204B0(char *to, const char *format, ...);   /* sprintf */
void func_00120928(char *to, const char *from);         /* strcpy */
void func_0018AEB0(u8 a, int b, int c, char *text);
void func_0018ADA0(u8 a, int b);
void func_0018AE70(u8 a, char *text);
void func_0022F450(char *to, u16 text);

/* An officer's record for scenario id `id`, the player's own officer for the player ids. */
static inline u8 *sc_officer(u32 id, int player)
{
    id = func_00185ED0(id);
    if (func_00185EC0(id) != 0)
        id = func_0035DC70(func_00186480(player)) & 0xFFFF;
    return REC88(id);
}

/* 0x001874E0, 0x10C bytes. Command: a speech bubble (text cmd[0] + 1) over officer cmd[1]
 * (unless the display flag 0x20 of the settings is set, for cmd[2] other than 1). */
void func_001874E0(u16 *cmd, int player)
{
    u32 id;
    u8 *o;

    if ((g_00669DB0[0] & 0x20) && cmd[2] != 1)
        return;
    id = func_00185ED0(cmd[1]);
    if (func_00185EC0(id) == 0) {
        o = REC88(id);
        if ((U32(o, 0x80) & 1) == 0)
            return;
    } else {
        o = REC88(func_0035DC70(func_00186480(player)) & 0xFFFF);
    }
    func_002D6FA0(PTR(o, 8), (U32(o, 0x80) & 0x20000) ? o + 0x30 : o + 0x28, cmd[0] + 1);
    g_005BC3A0[0] |= 0x10;
}

/* The text of message `t` with the name `name` and the extra text `extra` by form `f`. */
static inline void sc_format(char *t, char *name, char *extra, short f)
{
    if (f == 4)
        func_001204B0(g_005BBF20, t, extra, name);
    else if (f == 3)
        func_001204B0(g_005BBF20, t, name, extra);
    else if (f == 2)
        func_001204B0(g_005BBF20, t, extra);
    else if (f == 1)
        func_001204B0(g_005BBF20, t, name);
    else
        func_00120928(g_005BBF20, t);
}

/* Opens the message window for `cmd`: with a speaker (+2: 0 a fixed one, 1 or 2 by name). */
static inline void sc_open(u8 *cmd)
{
    u32 kind;

    if (*(short *)(cmd + 2) == 0) {
        func_0018AEB0(cmd[0], 0, 2, g_005BBF20);
        kind = 5;
    } else {
        func_0018ADA0(cmd[0], *(short *)(cmd + 2) == 1);
        kind = *(short *)(cmd + 2) == 1 ? 6 : 2;
    }
    func_0022EF90(g_005BC3A0, kind, 2);
}

/* 0x001875F0, 0x1F0 bytes. Command: a message (text +4) naming officer +6, with extra text
 * +8, by form +0xA. */
void func_001875F0(u8 *cmd)
{
    char t[0x100], name[0x100];
    char *extra;
    u16 *r;

    func_0022F4B0(t, *(u16 *)(cmd + 4));
    g_005BC064 = 2;
    extra = g_005BC260[*(u16 *)(cmd + 8)];
    r = (u16 *)PTR(sc_officer(*(u16 *)(cmd + 6), 0), 8);
    func_0019B170(name, r[0], r[1]);
    sc_format(t, name, extra, *(short *)(cmd + 0xA));
    sc_open(cmd);
}

/* 0x001877E0, 0x138 bytes. Command: a plain message (text +6, the next one for the players'
 * officer 0xD with form 1); speaker kind 3 shows it in the window of +0. */
void func_001877E0(u8 *cmd)
{
    char t[0x100];

    if (*(short *)(cmd + 0xA) == 1 && U8(g_005BD724, 5) != 0
        && (g_00669DE8[0][0] == 0xD || g_00669DE8[1][0] == 0xD))
        *(short *)(cmd + 6) += 1;
    if (*(short *)(cmd + 2) == 3) {
        func_0022F4B0(t, *(u16 *)(cmd + 6));
        func_0018AE70(cmd[0], t);
        return;
    }
    func_0022F4B0(g_005BBF20, *(u16 *)(cmd + 6));
    g_005BC064 = 2;
    if (*(short *)(cmd + 2) == 0) {
        func_0018AEB0(cmd[0], cmd[4], cmd[8], g_005BBF20);
        func_0022EF90(g_005BC3A0, 5, 2);
    } else {
        func_0018ADA0(cmd[0], *(short *)(cmd + 2) == 1);
        func_0022EF90(g_005BC3A0, *(short *)(cmd + 2) == 1 ? 6 : 2, 2);
    }
}

/* 0x00187920, 0x148 bytes. Command: an officer's introduction (officer cmd[0]: 0x25 becomes
 * 0xF for the players' officer 0xD; text cmd[1]) for a special officer, or one on the field. */
void func_00187920(u16 *cmd)
{
    u32 id = cmd[0];
    u8 *o;

    if (id == 0x25 && cmd[2] == 0
        && (g_00669DE8[0][0] == 0xD || ((g_00669F60[0] & 2) && g_00669DE8[1][0] == 0xD)))
        id = 0xF;
    o = func_0034B0D0(id);
    if (id > 0x1A3 || cmd[5] != 0 || o != 0) {
        func_0022F450(g_005BBF20, cmd[1]);
        g_005BC064 = 1;
        g_005BC034 = U8(g_005BA6A0 + id * 0x2C, 6);
        g_005BC038 = cmd[3];
        g_005BC03C = cmd[4] == 1;
        g_005BC030 = cmd[2] != 0;
        if (o != 0)
            g_005BC048 = U8(o, 0x79);
        g_005BC02C = id;
        func_0022EF90(g_005BC3A0, g_005BC028, 1);
    }
}

/* 0x00187A70, 0x21C bytes. Command: a message in the large window (text cmd[0], the next for
 * the players' officer 0xD with cmd[4] = 1) naming officer cmd[1], extra text cmd[2], form
 * cmd[3]. */
void func_00187A70(short *cmd, int player)
{
    char t[0x100], name[0x100];
    u16 *r;
    short k = cmd[0];

    if (cmd[4] == 1 && U8(g_005BD724, 5) != 0
        && (g_00669DE8[0][0] == 0xD || g_00669DE8[1][0] == 0xD))
        k = k + 1;
    func_0022F4B0(t, k);
    r = (u16 *)PTR(sc_officer(cmd[1], player), 8);
    if (r == 0)
        return;
    func_0019B170(name, r[0], r[1]);
    if (cmd[3] == 4)
        func_001204B0(g_005BBF20, t, g_005BC260[(u16)cmd[2]], name);
    else if (cmd[3] == 3 || cmd[3] == 1)
        func_001204B0(g_005BBF20, t, name);   /* form 3 passes no extra text, as in the original */
    else if (cmd[3] == 2)
        func_001204B0(g_005BBF20, t, g_005BC260[(u16)cmd[2]]);
    else
        func_00120928(g_005BBF20, t);
    g_005BC064 = 0;
    g_005BC04C = 0;
    func_002C4AE0((unsigned int *)((u8 *)&g_005BD728), PS2_ADDR(g_005BBF20));
    g_005BD72C = 0;
    g_005BD728 = 0;
    func_0022EF90(g_005BC3A0, g_005BC020, 0);
}

/* The scenario's integer variables (the scenario object's +0x1BD0; the same table as the
 * texts by index). */
#define SC_VAR(i) (*(int *)((u8 *)&g_005BA690 + (i) * 4 + 0x1BD0))

#define g_7000015C (*(u32 *)0x7000015C)          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

extern u32 g_005BD73C;
extern u8 g_00669D60[];                  /* the settings (per player 0x48 bytes from +0x88) */

int func_0017E0A0(void);
int func_0017E0B0(void);
void func_0017DE50(void);

/* 0x00188C00, 0x7C bytes. Command: variable cmd[3] = cmd[0] + or x (cmd[2] 0 / 1) cmd[1]. */
void func_00188C00(u16 *cmd)
{
    int b = SC_VAR(cmd[1]), a = SC_VAR(cmd[0]), r;

    switch (cmd[2]) {
    case 1:
        r = a * b;
        break;
    case 0:
        r = a + b;
        break;
    default:
        return;
    }
    SC_VAR(cmd[3]) = r;
}

/* 0x00188C80, 0x8C bytes. Command: variable cmd[0] = a random number between cmd[1] and cmd[2]. */
void func_00188C80(u16 *cmd)
{
    short a = cmd[1], b = cmd[2];
    int lo, n;

    if (a < b) {
        n = b - a;
        lo = a;
    } else {
        n = a - b;
        lo = b;
    }
    if (n + 1 == 0)
        n = 0;
    else
        n = (int)RANDOM() % (n + 1);
    SC_VAR(cmd[0]) = lo + n;
}

/* 0x00188D10, 0x3C bytes, matching. Command: variable cmd[0] = player cmd[1]'s setting value. */
void func_00188D10(u16 *cmd)
{
    SC_VAR(cmd[0]) = *(short *)(g_00669D60 + cmd[1] * 0x48 + 0x8C);
}

/* 0x00188D50, 0x7C bytes. Command: plays music cmd[0] (not in battle state 0x4000000, nor
 * while the music players are in state 0x16); kept as the scenario's music. */
void func_00188D50(u16 *cmd)
{
    if (g_00669F60[0] & 0x4000000)
        return;
    if (func_0017E0A0() != 0x16 && func_0017E0B0() != 0x16) {
        func_0017DE50();
        func_0017DE70(cmd[0]);
    }
    g_005BD73C = cmd[0];
}

/* 0x00188DD0, 0xBC bytes. Command: marks an area (cells cmd[3]-cmd[4] to cmd[5]-cmd[6]) on the
 * map: kinds 1-3 with colour cmd[1] (bit `kind`), kind 0 the flag 0x8000 (on with cmd[2]). */
void func_00188DD0(u16 *cmd)
{
    u8 a[2], b[2];
    u32 k = cmd[0];

    a[0] = (u8)cmd[3];
    a[1] = (u8)cmd[4];
    b[0] = (u8)cmd[5];
    b[1] = (u8)cmd[6];
    if (k == 3 || k == 2 || k == 1) {
        if (cmd[0] > 7)
            k = 8;
        func_00190860(a, b, (char)cmd[1], 1 << k, cmd[2] == 1);
    } else if (k == 0) {
        func_001906B0(a, b, 0x8000, cmd[2] == 1);
    }
}

/* A strength scaled from one unit kind's factor to another's, between 1 and 1000. */
static inline short scale_stat(short v, float from, float to)
{
    short s = (short)(int)(to * ((float)(int)v / from));

    if (s > 1000)
        s = 1000;
    if (s < 2)
        s = 1;
    return s;
}

/* 0x00188E90, 0x1EC bytes. Command: officer cmd[0] (free) changes its troop kind (+0x7E) to
 * cmd[1]; in battle its two strengths are scaled to the new kind and its unit told. */
void func_00188E90(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 1);
    u8 *o, old, nw;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    old = U8(o, 0x7E);
    U8(o, 0x7E) = (u8)cmd[1];
    nw = U8(o, 0x7E);
    if (U32(o, 0x80) & 0x20000) {
        float a, b;
        u8 *bo;

        func_001F11E0(old, &a);
        func_001F11E0(nw, &b);
        bo = g_006A3A30[U32(o, 0x14)];
        if (U32(bo, 0xB8) & 0x80) {
            *(short *)(bo + 0x8A) = scale_stat(*(short *)(bo + 0x8A), a, b);
            *(short *)(bo + 0x8C) = scale_stat(*(short *)(bo + 0x8C), a, b);
            func_00253B50(PTR(bo, 0x14), nw);
        }
    }
}

void func_001EC900(u8 *o, u16 v, int on);
void func_0018ACA0(u8 *cell);
void func_0018AD30(int id);

/* 0x00189080, 0xD0 bytes. Command: officer cmd[1]'s base (cmd[0] = 0) gets value cmd[2]
 * (func_001D4D90), else the officer's +0x24 becomes cmd[2] kept between 1 and 20. */
void func_00189080(short *cmd)
{
    u32 id = func_00185E00(cmd[1], 1);
    u8 *o;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
        func_001D4D90((float)cmd[2], BASE68(U32(o, 0x10)));
    } else {
        float v = (float)cmd[2];

        v = v < 20.0f ? v : 20.0f;
        *(float *)(o + 0x24) = 1.0f < v ? v : 1.0f;
    }
}

/* 0x00189150, 0xB8 bytes. Command: value cmd[2] for officer cmd[1]'s base (func_001D4CA0) or
 * the officer (func_001EF190, with cmd[3] and cmd[4]). */
void func_00189150(short *cmd)
{
    u32 id = func_00185E00(cmd[1], 1);
    u8 *o;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47)
        func_001D4CA0(BASE68(U32(o, 0x10)), cmd[2], cmd[3] == 1, cmd[4] == 1);
    else
        func_001EF190(o, cmd[2], cmd[3] == 1, cmd[4] == 1);
}

/* 0x00189210, 0x104 bytes. Command: officer cmd[0] (on the field, not beaten nor away) gets
 * cmd[1] (on with cmd[2]) for its base (cmd[3] = 0) or itself. */
void func_00189210(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);
    u8 *o;
    u32 f;

    if (func_00185EC0(id) != 0)
        return;
    o = REC88(id);
    f = U32(o, 0x80);
    if ((f & 1) && (f & 2) == 0 && (f & 4) == 0 && (f & 0x30) == 0) {
        if (cmd[3] == 0 && U32(o, 0x10) < 0x47)
            func_001D4D20(BASE68(U32(o, 0x10)), cmd[1], cmd[2] == 1);
        else
            func_001EC900(o, cmd[1], cmd[2] == 1);
    }
}

/* 0x00189320, 0xC0 bytes, matching. Command: officer cmd[0] (on the field) gets byte cmd[1] for its base
 * (func_001D50C0) or itself (func_001EE6B0). */
void func_00189320(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);
    u8 *o;

    if (func_00185EC0(id) != 0)
        return;
    o = REC88(id);
    if ((U32(o, 0x80) & 1) && (U32(o, 0x80) & 0x30) == 0) {
        if (U32(o, 0x10) < 0x47)
            func_001D50C0(BASE68(U32(o, 0x10)), *(u8 *)&cmd[1]);
        else
            func_001EE6B0(PS2_ADDR(o), *(u8 *)&cmd[1]);
    }
}

/* 0x001893E0, 0xC0 bytes, matching. The same with func_001D5120 / func_001EE750. */
void func_001893E0(u16 *cmd)
{
    u32 id = func_00185ED0(cmd[0]);
    u8 *o;

    if (func_00185EC0(id) != 0)
        return;
    o = REC88(id);
    if ((U32(o, 0x80) & 1) && (U32(o, 0x80) & 0x30) == 0) {
        if (U32(o, 0x10) < 0x47)
            func_001D5120(BASE68(U32(o, 0x10)), *(u8 *)&cmd[1]);
        else
            func_001EE750(PS2_ADDR(o), *(u8 *)&cmd[1]);
    }
}

/* 0x001894A0, 0x38 bytes. Command: command cmd[0] (from the first of this group, +8) may be
 * met again. */
void func_001894A0(u16 *cmd)
{
    u8 *c = g_005BA7CC.data
            + *(u32 *)(g_005BA7CC.data + (cmd[0] + g_005BA7CC.pad[0]) * 4 + 0xC);

    c[0] &= ~3;
}

/* 0x001894E0, 0x108 bytes. Command: one of two rates (cmd[1]) of officer cmd[2]'s base, or of
 * the officer itself (+0x58 / +0x5C), becomes cmd[3] percent. */
void func_001894E0(short *cmd)
{
    u32 id = func_00185E00(cmd[2], 1);
    u8 *o;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
        u8 *b = BASE68(U32(o, 0x10));

        if (cmd[1] == 0)
            func_001D51F0(b, cmd[3]);
        else
            func_001D51A0(b, cmd[3]);
    } else if (cmd[1] == 0) {
        *(float *)(o + 0x58) = (float)cmd[3] * 0.01f;
    } else {
        *(float *)(o + 0x5C) = (float)cmd[3] * 0.01f;
    }
}

/* 0x001895F0, 0x2C bytes, matching. Command: func_0018ACA0 on cell (cmd[0], cmd[1]). */
void func_001895F0(u16 *cmd)
{
    u8 c[2];

    c[0] = (u8)cmd[0];
    c[1] = (u8)cmd[1];
    func_0018ACA0(c);
}

/* 0x00189620, 0xB4 bytes. Command: func_0018AD30 for officer cmd[0] if it is on the field
 * (the player's own for the player ids). */
void func_00189620(u16 *cmd, int player)
{
    u32 id = func_00185ED0(cmd[0]);

    if (func_00185EC0(id) == 0) {
        u32 f = U32(REC88(id), 0x80);
        int ok = 0;

        if ((f & 1) && ((f & 0x8C40002) != 0) ^ 1)
            ok = 1;
        if (!ok)
            return;
    } else {
        id = func_0035DC70(func_00186480(player)) & 0xFFFF;
    }
    func_0018AD30(id);
}

/* 0x001896E0, 0x74 bytes. Command: the point of cell (cmd[0], cmd[2] bytes) for
 * func_00183670, kept at 0x005BD728. */
void func_001896E0(u8 *cmd)
{
    float p[2];

    p[0] = (float)cmd[0] * 1000.0f + 500.0f;
    p[1] = (float)cmd[2] * 1000.0f + 500.0f;
    func_00183670(PS2_ADDR(p));
    ((float *)&g_005BD728)[0] = p[0];
    ((float *)&g_005BD728)[1] = p[1];
}

extern u32 g_005BC1A0[][2];              /* scenario timers (the scenario object's +0x1B10) */
#define SC_TIMER(k) (g_005BA690.timers[k])

u8 *func_001EE150(u8 *o);

/* Whether a record is on the field: flag 1 and none of 0x8C40002. */
static inline int on_field(u32 f)
{
    return (f & 1) && (f & 0x8C40002) == 0;
}

/* 0x00189760, 0x158 bytes. Command: the point of officer cmd[0] (beaten ones too with
 * cmd[1] = 1) for func_00183670, kept at 0x005BD728; (-1, -1) for a hidden officer. */
void func_00189760(u16 *cmd, int player)
{
    u32 id = func_00185ED0(cmd[0]);
    u8 *o;
    float p[2];

    if (func_00185EC0(id) == 0) {
        u32 f;

        o = REC88(id);
        f = U32(o, 0x80);
        if (cmd[1] == 1) {
            if ((f & 1) == 0)
                return;
            if ((f & 0x8C40002) && (f & 2) == 0)
                return;
        } else if ((f & 1) == 0 || (f & 0x8C40002)) {
            return;
        }
    } else {
        o = func_0035DCD0(func_00186480(player));
    }
    if ((U32(o, 0x84) & 0x8000) == 0) {
        float *q = (U32(o, 0x80) & 0x20000) ? (float *)(o + 0x30) : (float *)(o + 0x28);

        p[0] = q[0];
        p[1] = q[1];
        func_00183670(PS2_ADDR(p));
    } else {
        p[0] = -1.0f;
        p[1] = -1.0f;
    }
    ((float *)&g_005BD728)[0] = p[0];
    ((float *)&g_005BD728)[1] = p[1];
}

/* 0x001898C0, 0x19C bytes. Command: officer cmd[1] (free) or its base gets a destination cell
 * (cmd[2], cmd[3]: a map cell, or with `fine` a 1000-unit cell). */
void func_001898C0(short *cmd, int fine)
{
    u32 id = func_00185E00(cmd[1], 1);
    u8 *o, c[2], d[2];
    float pos[2];

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    if (fine == 0) {
        c[0] = (u8)cmd[2];
        c[1] = (u8)cmd[3];
        func_001F1640(c, (short int *)(d));
    } else {
        d[0] = (u8)cmd[2];
        d[1] = (u8)cmd[3];
        c[0] = d[0] / 5;
        c[1] = d[1] / 5;
    }
    pos[0] = (float)d[0] * 1000.0f + 500.0f;
    pos[1] = (float)d[1] * 1000.0f + 500.0f;
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
        func_001D4F00(BASE68(U32(o, 0x10)), (const long long unsigned int *)(pos), (const short unsigned int *)(c));
    } else {
        *(float *)(o + 0x38) = pos[0];
        *(float *)(o + 0x3C) = pos[1];
        U32(o, 0x84) |= 0x10;
        U8(o, 0x44) = c[0];
        U8(o, 0x45) = c[1];
    }
}

/* 0x00189A60, 0x16C bytes. Command: officer cmd[1] (free) or its base targets officer cmd[2]
 * (on the field; one that is away targets func_001EE150's). */
void func_00189A60(short *cmd, int player)
{
    u32 id = func_00185E00(cmd[1], 1), t;
    u8 *o, *target;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    t = func_00185ED0(cmd[2]);
    if (func_00185EC0(t) == 0) {
        u32 f;

        target = REC88(t);
        f = U32(target, 0x80);
        if (!on_field(f))
            return;
        if (f & 0x30)
            target = func_001EE150(target);
    } else {
        target = func_0035DCD0(func_00186480(player));
    }
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47) {
        func_001D4F60(BASE68(U32(o, 0x10)), PS2_ADDR(target));
    } else {
        PTR(o, 0x1C) = target;
        U32(o, 0x84) |= 0x10;
    }
}

/* 0x00189BD0, 0xA0 bytes, matching. Command: byte cmd[2] for officer cmd[1]'s base (func_001D5240) or the
 * officer (func_001EE9C0). */
void func_00189BD0(u16 *cmd)
{
    u32 id = func_00185E00(cmd[1], 1);
    u8 *o;

    if (id >= 0x1AD)
        return;
    o = REC88(id);
    if (cmd[0] == 0 && U32(o, 0x10) < 0x47)
        func_001D5240(BASE68(U32(o, 0x10)), (u8)cmd[2]);
    else
        func_001EE9C0(o, (u8)cmd[2]);
}

/* 0x00189C70, 0x88 bytes, matching. Command: func_0033BDC0 with cmd[1] for officer cmd[0]'s base. */
void func_00189C70(u16 *cmd)
{
    u32 id = func_00185E00(cmd[0], 1);

    if (id < 0x1AD && U32(REC88(id), 0x10) < 0x47)
        func_0033BDC0((void *)BASE68(U32(REC88(id), 0x10)), (short)cmd[1]);
}

/* 0x00189D00, 0x28 bytes, matching. Command: func_0033BE80(cmd[0], cmd[1], 0). */
void func_00189D00(u16 *cmd)
{
    func_0033BE80(cmd[0], (short)cmd[1], 0);
}

/* 0x00189D30, 0xA4 bytes. Command (unless func_0032E7B0): an effect on cell (cmd[0], cmd[1])
 * for 2 x cmd[2] frames: kinds 0-3 (func_0018F890), 4 / 5 (func_0018FC00 off / on). */
void func_00189D30(u16 *cmd)
{
    u8 c[2];
    u16 k;
    int n;

    if (func_0032E7B0() != 0)
        return;
    k = cmd[3];
    n = cmd[2] << 1;
    c[0] = (u8)cmd[0];
    c[1] = (u8)cmd[1];
    if (k < 4)
        func_0018F890(c, n, (u8)k);
    else if (k == 5)
        func_0018FC00(c, n, 1);
    else if (k == 4)
        func_0018FC00(c, n, 0);
}

/* 0x00189DE0, 0x58 bytes. Command: func_0027F160 for the slot of entry cmd[0] (in the scenario
 * header +0x2C) with cmd[1]; func_0032E7B0 when there is none. */
void func_00189DE0(u16 *cmd)
{
    char c = *(char *)(g_005BD724 + 0x2C + cmd[0]);

    if (c == -1)
        func_0032E7B0();
    else
        func_0027F160(c, (char)cmd[1]);
}

/* 0x00189E40, 0x6C bytes. Command: variable cmd[0] += cmd[1] (cmd[2] = 1) or = cmd[1] (0). */
void func_00189E40(u16 *cmd)
{
    if (cmd[2] == 1)
        SC_VAR(cmd[0]) = SC_VAR(cmd[0]) + (short)cmd[1];
    else if (cmd[2] == 0)
        SC_VAR(cmd[0]) = (short)cmd[1];
}

/* 0x00189EB0, 0x5C bytes. Command: pair cmd[0] at 0x005BC1A0: its second word cleared (2), its
 * first cleared (1) or set (0). */
void func_00189EB0(u16 *cmd)
{
    u32 *p = g_005BC1A0[cmd[0]];

    if (cmd[1] == 2)
        p[1] = 0;
    else if (cmd[1] == 1)
        p[0] = 0;
    else if (cmd[1] == 0)
        p[0] = 1;
}

/* 0x00189F10, 0x114 bytes. Command: func_00349AF0 (cmd[5]) for every officer of side cmd[0] on
 * the field standing in cells cmd[1]-cmd[3] x cmd[2]-cmd[4]. */
void func_00189F10(u16 *cmd)
{
    u8 *o = REC88(0);
    u32 k;

    for (k = 0; k < 0x1AD; k++, o += 0x88) {
        u32 f = U32(o, 0x80);

        if (on_field(f) && cmd[0] == U8(o, 0x79) && cmd[1] <= U8(o, 0x40) && U8(o, 0x40) <= cmd[3]
            && cmd[2] <= U8(o, 0x41) && U8(o, 0x41) <= cmd[4])
            func_00349AF0(o, cmd[5]);
    }
}

/* 0x0018A030, 0xFC bytes. Command: for officer cmd[0] in battle, its battle officers (those
 * of the 143 whose record is it, alive) get func_0024D380 with cmd[1]. */
void func_0018A030(u16 *cmd)
{
    u8 *o = REC88(cmd[0]), *b;
    u32 f = U32(o, 0x80), k;

    if (!on_field(f) || (f & 0x20000) == 0)
        return;
    b = g_006A3A30[0];
    for (k = 0; k < 0x8F; k++, b += 0xC0) {
        if ((U32(b, 0xB8) & 1) && PTR(b, 0x10) == o && (U32(b, 0xB8) & 2) == 0)
            func_0024D380(cmd[1], PS2_ADDR(PTR(b, 0x14)));
    }
}

/* The record index of the officer named by scenario officer `n` (func_0034B0D0), or -1. */
static inline int named_index(u16 n)
{
    u8 *o = func_0034B0D0(n);

    if (o == 0)
        return -1;
    return (o - REC88(0)) / 0x88;
}

/* 0x0018A130, 0x70 bytes. func_0018A030 for a named officer. */
void func_0018A130(u16 *cmd)
{
    int i = named_index(cmd[0]);
    u16 c[2];

    if (i >= 0) {
        c[0] = (u16)i;
        c[1] = cmd[1];
        func_0018A030(c);
    }
}

/* 0x0018A1A0, 0x7C bytes. func_00189760 for a named officer. */
void func_0018A1A0(u16 *cmd, int player)
{
    int i = named_index(cmd[0]);
    u16 c[2];

    if (i >= 0) {
        c[0] = (u16)i;
        c[1] = cmd[1];
        func_00189760(c, player);
    }
}

/* 0x0018A220, 0x70 bytes. func_001893E0 for a named officer. */
void func_0018A220(u16 *cmd)
{
    int i = named_index(cmd[0]);
    u16 c[2];

    if (i >= 0) {
        c[0] = (u16)i;
        c[1] = cmd[1];
        func_001893E0(c);
    }
}

/* The scenario's objectives (0x005BA7E8): 16 records of 0x170 bytes ([0] state, [1] id, [2]
 * kind, [3] result, +4 the frame it started, +8 the frame it ended, +0xC its number of points,
 * +0xD its number of officers, +0xE a byte, +0x10 8 points (x, z), +0x50 8 officer ids, +0x70
 * its text); then +0x1700 their count, +0x1704 the 8 map markers in use, +0x1724 the current
 * one, +0x1728 a timer. */
extern u8 g_005BA7E8[];
extern u32 g_005BBEE8;                   /* (= +0x1700) the objectives' count */
extern u8 g_0073DB80[8][0x1C];           /* player 1's map markers */
extern u8 g_0073DE10[8][0x1C];           /* player 2's map markers */
extern u8 *g_0073DA28, *g_0073DA2C;      /* player 1's marker sprites */
extern u8 *g_0073DCB8, *g_0073DCBC;      /* player 2's marker sprites */
extern int g_00669F9C;                   /* the battle's frame counter */

#define OBJ(i) (g_005BA7E8 + (i) * 0x170)

/* A marker's sprite pair cleared. */
static inline void marker_sprite_clear(u8 *s)
{
    *(unsigned long long *)(s + 0xABB0) = 0;
    *(unsigned long long *)(s + 0xABC0) = 0;
    *(unsigned long long *)(s + 0xAC00) = 0;
    *(unsigned long long *)(s + 0xAC10) = 0;
    *(unsigned long long *)(s + 0xAC50) = 0;
    *(unsigned long long *)(s + 0xAC60) = 0;
}

/* A map marker cleared (its point at (-1, -1)). */
static inline void marker_clear(u8 *m)
{
    U32(m, 0) = 0;
    U32(m, 4) = 0;
    U32(m, 8) = 0;
    U32(m, 0xC) = 0;
    *(float *)(m + 0x10) = -1.0f;
    *(float *)(m + 0x14) = -1.0f;
    U32(m, 0x18) = 0;
}

/* 0x0018A870, 0x198 bytes. Takes the objective markers off the map (both players'). */
void func_0018A870(u8 *m)
{
    u32 k;

    for (k = 0; k < 8; k++, m += 4) {
        int s = S32(m, 0x1704);

        if (s != -1) {
            marker_clear(g_0073DB80[s]);
            marker_sprite_clear(g_0073DA28 + s * 0xF0);
            marker_sprite_clear(g_0073DA2C + s * 0xF0);
            if (g_00669F60[0] & 2) {
                marker_clear(g_0073DE10[S32(m, 0x1704)]);
                marker_sprite_clear(g_0073DCB8 + S32(m, 0x1704) * 0xF0);
                marker_sprite_clear(g_0073DCBC + S32(m, 0x1704) * 0xF0);
            }
            S32(m, 0x1704) = -1;
        }
    }
}

/* A free marker (the first unused, else the oldest one), taken. */
static inline int take_marker(u8 (*mk)[0x1C])
{
    int best = 8, age = 0, i;

    for (i = 0; i < 8; i++) {
        int v = S32(mk[i], 0);

        if (v == 0) {
            best = i;
            break;
        }
        if (age < v) {
            best = i;
            age = v;
        }
    }
    S32(mk[best], 0) = 1;
    return best;
}

/* 0x0018AA10, 0x134 bytes. Gives objective `r`'s officers markers on the map. */
void func_0018AA10(u8 *m, u8 *r)
{
    u32 n = U8(r, 0xD), k;

    for (k = 0; k < n; k++, m += 4) {
        if (g_00669F60[0] & 2)
            S32(m, 0x1704) = take_marker(g_0073DE10);
        S32(m, 0x1704) = take_marker(g_0073DB80);
    }
}

/* 0x0018AB50, 0x58 bytes. Makes objective `i` the current one. */
void func_0018AB50(u8 *m, int i)
{
    if (U32(m, 0x1724) < 0x10)
        func_0018A870(m);
    S32(m, 0x1724) = i;
    U32(m, 0x1728) = 0;
    func_0018AA10(m, m + i * 0x170);
}

/* 0x0018ABB0, 0x64 bytes. The next objective after the current one that is not finished
 * (+3); 0x10 for none. */
int func_0018ABB0(u8 *m)
{
    u32 n = U32(m, 0x1700), k;

    for (k = 1; k <= n; k++) {
        int i = (int)(S32(m, 0x1724) + k) % (int)n;

        if (U8(m + i * 0x170, 3) == 0)
            return i;
    }
    return 0x10;
}

/* 0x0018AC20, 0x40 bytes. The objective being added (the next free record); 0 when full. */
u8 *func_0018AC20(void)
{
    if (g_005BBEE8 < 0x10)
        return OBJ(g_005BBEE8);
    return 0;
}

/* 0x0018AC60, 0x3C bytes, matching. The objective with id `id`; 0 for none. */
u8 *func_0018AC60(u32 id)
{
    u8 *r = OBJ(0);
    u32 k;

    for (k = 0; k < 0x10; k++, r += 0x170) {
        if (id == r[1])
            return r;
    }
    return 0;
}

/* 0x0018ACA0, 0x90 bytes. Adds cell `c` as a point of the objective being added. */
void func_0018ACA0(u8 *c)
{
    u8 *r = func_0018AC20();
    float *p = (float *)(r + U8(r, 0xC) * 8 + 0x10);

    p[0] = (float)c[0] * 1000.0f + 500.0f;
    p[1] = (float)c[1] * 1000.0f + 500.0f;
    if (U8(r, 0xC) < 8)
        U8(r, 0xC) += 1;
}

/* 0x0018AD30, 0x70 bytes. Adds officer `id` to the objective being added (not hidden ones,
 * flag 0x4000). */
void func_0018AD30(int id)
{
    if ((U32(REC88(id), 0x84) & 0x4000) == 0) {
        u8 *r = func_0018AC20();

        S32(r + U8(r, 0xD) * 4, 0x50) = id;
        if (U8(r, 0xD) < 8)
            U8(r, 0xD) += 1;
    }
}

/* 0x0018ADA0, 0xCC bytes. Ends objective `id` (1 won, 2 lost); a won one gives the players a
 * reward by its kind (200, 500, 2000), unless battle flag 4. */
void func_0018ADA0(u8 id, int won)
{
    u8 *r = func_0018AC60(id);

    if (r == 0)
        return;
    if (won == 0) {
        r[3] = 2;
    } else {
        r[3] = 1;
        if ((g_00669F60[0] & 4) == 0) {
            u32 v;

            if (r[2] == 2)
                v = 2000;
            else if (r[2] == 1)
                v = 500;
            else if (r[2] == 0)
                v = 200;
            else
                v = 0;
            func_0019B4E0(0, func_001839B0(v));
        }
    }
    S32(r, 8) = g_00669F9C;
}

/* 0x0018AE70, 0x3C bytes, matching. Sets objective `id`'s text. */
void func_0018AE70(u8 id, char *text)
{
    u8 *r = func_0018AC60(id);

    if (r != 0)
        func_00120928((char *)(r + 0x70), text);
}

/* 0x0018AEB0, 0x7C bytes. Adds objective `id` of kind `kind` with its text, and makes it the
 * current one. */
void func_0018AEB0(u8 id, int kind, int e, char *text)
{
    u8 *r = func_0018AC20();
    u32 n;

    if (r == 0)
        return;
    r[0] = 1;
    r[1] = id;
    r[2] = (u8)kind;
    r[0xE] = (u8)e;
    r[3] = 0;
    S32(r, 4) = g_00669F9C;
    func_00120928((char *)(r + 0x70), text);
    n = g_005BBEE8;
    if (n < 0x10)
        g_005BBEE8 = n + 1;
    func_0018AB50(g_005BA7E8, n);
}

/* Two officer lists shown in messages (0x005BC068 and 0x005BC104, 0x9C bytes): six ids, +0x18
 * a byte, +0x19 the list's number, +0x1C its text. */
extern u8 g_005BC068[2][0x9C];
extern u8 g_0045CC98[3];                 /* (small data) the sides' text colours */
extern const char g_00424EA0[];          /* "%c%s"-like: a colour and a name */
extern const char g_00424EB0[];          /* "" */

extern u32 g_005BBF0C, g_005BBF10;       /* (objectives +0x1724, +0x1728) */
extern int g_005BBEEC[8];                /* (objectives +0x1704) the markers in use */

/* 0x0018B810, 0x38 bytes, matching. Restores the objectives from a save; returns the end. */
u8 *func_0018B810(u8 *p)
{
    func_00118AC0((unsigned int *)(g_005BA7E8), p, 0x1730);
    return p + 0x1730;
}

/* 0x0018B850, 0x34 bytes, matching. Saves the objectives; returns the end. */
u8 *func_0018B850(u8 *p)
{
    func_00118AC0((unsigned int *)(p), g_005BA7E8, 0x1730);
    return p + 0x1730;
}

/* 0x0018B890, 0x8 bytes, matching. Nothing. */
void func_0018B890(void)
{
}

/* 0x0018B8A0, 0x15C bytes. Clears the objectives (all of result 3, none current, no
 * markers). */
void func_0018B8A0(void)
{
    u8 *r = OBJ(0);
    u32 k;

    g_005BBF0C = 0x10;
    g_005BBEE8 = 0;
    g_005BBF10 = 0;
    for (k = 0; k < 8; k++)
        g_005BBEEC[k] = -1;
    for (k = 0; k < 0x10; k++, r += 0x170) {
        r[0] = 0;
        r[1] = 0;
        r[2] = 0;
        r[3] = 3;
        S32(r, 4) = 0;
        S32(r, 8) = 0;
        r[0xD] = 0;
        r[0xC] = 0;
    }
}

/* 0x0018BA00, 0x114 bytes. The `i`-th officer of list `l` (*id) and its point for
 * func_001911A0 (for officer kind 0x215 the centre of its 5000-unit cell). */
void func_0018BA00(u8 *l, u32 i, int *id, void *x)
{
    float p[2];
    u8 *o;

    if (i >= U8(l, 0x18))
        return;
    *id = S32(l, i * 4);
    o = REC88(*id);
    if ((PTR(o, 8) - g_005BA6A0) / 0x2C == 0x215) {
        p[0] = (float)U8(o, 0x40) * 5000.0f + 2500.0f;
        p[1] = (float)U8(o, 0x41) * 5000.0f + 2500.0f;
    } else {
        float *q = (U32(o, 0x80) & 0x20000) ? (float *)(o + 0x30) : (float *)(o + 0x28);

        p[0] = q[0];
        p[1] = q[1];
    }
    func_001911A0(x, p);
}

/* 0x0018BB20, 0x198 bytes. Fills officer list `k` (0-0xF the first, 0x10-0x1F the second)
 * with six officers and its text (each name in its side's colour, by text func_00372C00(k)). */
void func_0018BB20(u32 k, u32 *ids, u8 b)
{
    char names[6][0x80], name[0x80];
    u8 col[3], *l;
    u32 j;

    col[0] = g_0045CC98[0];
    col[1] = g_0045CC98[1];
    col[2] = g_0045CC98[2];
    if (k < 0x10)
        l = g_005BC068[0];
    else if (k < 0x20)
        l = g_005BC068[1];
    else
        return;
    l[0x19] = (u8)k;
    for (j = 0; j < 6; j++) {
        u32 id = ids[j];

        if (id < 0x1AD) {
            u8 c;

            S32(l, j * 4) = id;
            c = col[U8(REC88(id), 0x79)];
            if ((U32(REC88(id), 0x80) & 0x8000000) == 0)
                func_003DD710(PS2_ADDR(name), (unsigned char *)PS2_PTR(id));
            else
                func_00120928(name, func_00372C40(U8(REC88(id), 0x79)));
            func_001204B0(names[j], g_00424EA0, c, name);
        }
    }
    l[0x18] = b;
    func_001204B0((char *)(l + 0x1C), func_00372C00(k), names[0], names[1], names[2], names[3],
                  names[4], names[5]);
}

/* 0x0018BCC0, 0x38 bytes, matching. Restores the officer lists; returns the end. */
u8 *func_0018BCC0(u8 *p)
{
    func_00118AC0((unsigned int *)(g_005BC068), p, 0x138);
    return p + 0x138;
}

/* 0x0018BD00, 0x34 bytes, matching. Saves the officer lists; returns the end. */
u8 *func_0018BD00(u8 *p)
{
    func_00118AC0((unsigned int *)(p), (unsigned char *)(g_005BC068), 0x138);
    return p + 0x138;
}

/* 0x0018BD40, 0x8 bytes, matching. Nothing. */
void func_0018BD40(void)
{
}

/* 0x0018BD50, 0x4C bytes, matching. Empties an officer list. */
void func_0018BD50(u8 *l)
{
    int k;

    for (k = 0; k < 6; k++)
        S32(l, k * 4) = 0x1AD;
    l[0x18] = 0;
    l[0x19] = 0x20;
    func_00120928((char *)(l + 0x1C), g_00424EB0);
}

/* 0x0018BDA0, 0x34 bytes. Empties both officer lists. */
void func_0018BDA0(void)
{
    func_0018BD50(g_005BC068[0]);
    func_0018BD50(g_005BC068[1]);
}

/* 0x0018BDE0, 0x50 bytes. Each frame, the 24 running timers (pairs at 0x005BC1A0) count up. */
void func_0018BDE0(void)
{
    u32 *t = g_005BC1A0[0];
    u32 k;

    for (k = 0; k < 0x18; k++, t += 2) {
        if (t[0] != 0 && t[1] != 0x7FFFFFFF)
            t[1] = t[1] + 1;
    }
}

/* 0x0018BE30, 0x64 bytes. Restores the timers; returns the end. */
u8 *func_0018BE30(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x18; k++, p += 8)
        func_00118AC0(SC_TIMER(k), p, 8);
    return p;
}

/* 0x0018BEA0, 0x64 bytes. Saves the timers; returns the end. */
u8 *func_0018BEA0(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x18; k++, p += 8)
        func_00118AC0((unsigned int *)(p), (void *)SC_TIMER(k), 8);
    return p;
}

/* 0x0018BF10, 0x8 bytes, matching. Nothing. */
void func_0018BF10(void)
{
}

/* 0x0018BF20, 0x78 bytes. Resets the timers (the first one running). */
void func_0018BF20(void)
{
    u32 k;

    g_005BC1A0[0][1] = 0;
    g_005BC1A0[0][0] = 1;
    for (k = 1; k < 0x18; k++) {
        g_005BC1A0[k][0] = 0;
        g_005BC1A0[k][1] = 0;
    }
}

/* 0x0018BFA0, 0x64 bytes. Restores the 16 variables; returns the end. */
u8 *func_0018BFA0(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x10; k++, p += 4)
        func_00118AC0((unsigned int *)(&SC_VAR(k)), p, 4);
    return p;
}

/* 0x0018C010, 0x64 bytes. Saves the 16 variables; returns the end. */
u8 *func_0018C010(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x10; k++, p += 4)
        func_00118AC0((unsigned int *)(p), (unsigned char *)(&SC_VAR(k)), 4);
    return p;
}

/* 0x0018C080, 0x8 bytes, matching. Nothing. */
void func_0018C080(void)
{
}

extern u8 *g_0045D2F0;                   /* (small data) the map: +4 its 32 x 32 blocks of 5 x 5 cells */

int func_0011B740(int x);                /* abs */

/* 0x0018C090, 0x44 bytes, matching. Clears the 16 variables. */
void func_0018C090(void)
{
    u32 k;

    for (k = 0; k < 0x10; k++)
        *(int *)&g_005BC260[k] = 0;
}

/* 0x0018C0E0, 0x7C bytes, matching. func_00190480 for the 5000-unit cell of point `p`. */
int func_0018C0E0(float *p)
{
    u8 c[2];

    c[0] = (u8)((int)p[0] / 5000);
    c[1] = (u8)((int)p[1] / 5000);
    return func_00190480(c);
}

/* 0x0018C160, 0x134 bytes. Whether 1000-unit cell `c` is open on the map (its block's bit
 * clear; never while func_00352CA0). */
int func_0018C160(u8 *c)
{
    u8 *m = g_0045D2F0, *b;

    if (func_00352CA0(c) != 0)
        return 0;
    if (c[0] / 5 > 0x1F || c[1] / 5 > 0x1F)
        b = 0;
    else
        b = ((u8 **)PTR(m, 4))[c[0] / 5 + (c[1] / 5) * 0x20];
    if (b == 0)
        return 0;
    return (U8(PTR(b, 0), 0x18 + c[1] % 5) & 1 << (c[0] % 5)) == 0;
}

/* 0x0018C2A0, 0x7C bytes, matching. func_0018C160 for the 1000-unit cell of point `p`. */
int func_0018C2A0(float *p)
{
    u8 c[2];

    c[0] = (u8)((int)p[0] / 1000);
    c[1] = (u8)((int)p[1] / 1000);
    return func_0018C160(c);
}

/* 0x0018C320, 0xD0 bytes, matching. The direction (0-7, 8 for the same cell) from cell `a` to `b`. */
int func_0018C320(u8 *a, u8 *b)
{
    if (a[0] == b[0]) {
        if (a[1] < b[1])
            return 2;
        if (b[1] < a[1])
            return 6;
        return 8;
    }
    if (a[0] < b[0]) {
        if (a[1] < b[1])
            return 1;
        if (b[1] < a[1])
            return 7;
        return 0;
    }
    if (a[1] < b[1])
        return 3;
    if (b[1] < a[1])
        return 5;
    return 4;
}

/* 0x0018C3F0, 0x24 bytes. The squared distance between two points. */
float func_0018C3F0(float *a, float *b)
{
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
}

/* 0x0018C420, 0x6C bytes, matching. The distance in cells between `a` and `b` (the larger of the two
 * differences). */
int func_0018C420(u8 *a, u8 *b)
{
    int x = func_0011B740(a[0] - b[0]);
    int z = func_0011B740(a[1] - b[1]);

    return z < x ? x : z;
}
