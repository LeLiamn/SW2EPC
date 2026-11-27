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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

#pragma opt_unroll_loops on

/* A table file: a count, then the entries. */
typedef struct {
    u32 *data;
    u32 *entries;            /* data + 1 */
    u32 count;
} ScTable;

extern ScTable g_005BA690;               /* LINKDATA entry 0x35 */
extern u32 g_005BA6A4[5];
extern u8 g_00693970[][0x88];            /* the officers' records (+0x80 flags) */
extern int g_00669F6C[4];                /* +0: the game mode (1: ?), inside the settings */
extern const char g_00424E40[];          /* "sc_ctrl.c" */

void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const void *file, int line);
void func_00102EC0(void *data);          /* free */
void func_00185390(void);
void func_001854C0(void);
void func_0023ED70(void);
void func_0019A790(void);
void func_0019A7B0(void);
void func_0023ED90(void);
u32 func_0035DC70(int p);
void func_0018A290(u8 *c, u8 v, int x);
void func_0019A4F0(u8 *b, int a);

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
    func_00102EC0(g_005BA690.data);
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

int func_0032E7B0(void);
int func_00183410(int a, u32 i, u8 state, u8 b, int c);
void func_0027DEA0(int a, int b);

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

void func_001EEBF0(u8 *o);
void func_001F1910(u8 *o);
void func_001EE3A0(u8 *o);
void func_001EE9C0(u8 *o, u8 a);
void func_001ED160(u8 *o, u8 *a, int b);
void func_00207260(u8 *r, float *pos);
void func_002075A0(float yaw, u8 *r, float *out, int a);
void func_001660C0(u8 *u, float *pos);
void func_001F1A30(u8 *o);
void func_001D4C20(u8 *base, int a);
void func_001EEC50(u8 *o);
void func_001D4FB0(u8 *base);
void func_001D4C00(u8 *o);
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
                func_001EEBF0(o);
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
        func_001ED160(o, PTR(o, 0x18), 0);
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

            func_00207260(r, pos);
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
                func_001EEC50(o);
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

void func_001D5060(u8 *base);
void func_001EE570(u8 *o);
void func_001D4DE0(u8 *base, short v);
void func_001D4E40(u8 *base, short v);
void func_001D4EA0(u8 *base, short v);
void func_001EECE0(u8 *o, short v);
void func_001EEDE0(u8 *o, short v);
void func_001EEEE0(u8 *o, short v);



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
                    func_001EECE0(o, cmd[3]);
                else if (cmd[2] == 1)
                    func_001EEDE0(o, cmd[3]);
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
