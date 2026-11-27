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
