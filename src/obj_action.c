/*
 * obj_action.c - the battlefield's objects and their actions (gates, traps, switches): each map
 * object is 3 bytes (kind, side, data) in the list at (small data) 0x0045D540; running actions are
 * 50 records of 12 bytes at 0x007720C0 (owner, time, kind, argument; kind 0x1F = free). The kinds'
 * handlers are records of 0x30 bytes at 0x0043FE40. Probably the original ObjAction.c (whose name
 * is used at 0x0027F610). Written so far: 0x0027E460-0x0027F608.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_OBJ_ACTION_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 *owner;               /* +0x00 the object's unit (0 = a map object) */
    float time;              /* +0x04 */
    u8 kind;                 /* +0x08 0x1F = free */
    u8 arg;                  /* +0x09 */
    u8 pad_0A[2];
} ObjAct;

/* A kind's handlers (0x30 bytes). */
typedef struct {
    u32 unknown_00;
    int (*can)(int k);                                       /* +0x04 */
    int (*before)(int k, u8 *data, int how);                 /* +0x08 */
    int (*after)(int k, u8 *data, int how);                  /* +0x0C */
    u32 flags;                                               /* +0x10 */
    int (*each)(u8 *data, int (*f)(int, int *), int *arg);   /* +0x14 for each unit concerned */
    int (*step)(ObjAct *a);                                  /* +0x18 */
    int (*apply)(u8 *u, int how);                            /* +0x1C */
    u32 unknown_20;
    void (*reset)(int k, u8 *data, u8 v);                    /* +0x24 */
    void (*event)(int k, u8 *data, int v);                   /* +0x28 */
    void (*end)(ObjAct *a);                                  /* +0x2C */
} ObjKind;

extern ObjAct g_007720C0[50];
extern ObjKind g_0043FE40[];
extern u8 *g_0045D540;                   /* (small data) the map objects (3 bytes each) */
extern u8 g_0045D544[3];
extern u8 *g_0045D548, *g_0045D54C;      /* (small data) per object values */
extern u32 g_0045D550;
extern float g_0045D554;                 /* (small data) the action time step */
extern u8 *g_0045D558, *g_0045D55C;      /* (small data) object bit sets */
extern ObjAct **g_0045D560;              /* (small data) each object's running action */
extern u32 g_0045D564;                   /* (small data) the number of objects */
extern u8 *g_0045D2F0;                   /* (small data) the battlefield map */
extern u8 g_0073DC98[], g_0073DF28[];
extern u8 g_00669D60[];
extern int g_00669DB8, g_00669F6C;

#define UNITS (*(u8 **)0x700001D0)       /* (scratchpad) the stage units (0x70 bytes each) */
#define g_70000874 (*(u32 *)0x70000874)
#define g_70000878 (*(float *)0x70000878)
#define SETTINGS_FLAGS (*(u32 *)(g_00669D60 + 0x200))

u32 func_001FF100(u16 v, int k);
void func_0027F6F0(void);
void func_0027F610(void);

void func_0027E800(u8 *u, int on);
int func_0027EB10(int k, int *arg);
int func_0027EC40(int k, int *arg);
void func_0027EFE0(int k, int how);

/* The kind of map object `k`. */
#define OBJ_KIND(k) (&g_0043FE40[g_0045D540[(k) * 3]])

/* 0x0027E460, 0x10 bytes, matching. */
u8 func_0027E460(int k)
{
    return g_0045D544[k];
}

/* 0x0027E470, 0x17C bytes. Steps the running actions (frees those that end). */
void func_0027E470(void)
{
    ObjAct *a = g_007720C0;
    u32 slow = SETTINGS_FLAGS & 0x100000;
    int k;

    for (k = 0; k < 0x32; k++, a++) {
        ObjKind *t;

        if (a->kind == 0x1F)
            continue;
        t = &g_0043FE40[a->kind];
        if (slow != 0 && (t->flags & 8) != 0)
            continue;
        if ((t->flags & 0x10) == 0) {
            g_0045D554 = g_70000878;
            g_0045D550 = g_70000874;
        } else {
            g_0045D554 = 0.02f;
            g_0045D550 = 0x42480000;
        }
        a->time += g_0045D554;
        if (t->step(a) != 0) {
            if (a->owner == 0) {
                u32 j;

                for (j = 0; j < g_0045D564; j++) {
                    if (a == g_0045D560[j]) {
                        g_0045D560[j] = 0;
                        break;
                    }
                }
            } else {
                a->owner[0x6A] = 0xFF;
            }
            a->kind = 0x1F;
        } else if (t->end != 0) {
            t->end(a);
        }
    }
}

/* 0x0027E5F0, 0x14 bytes, matching. Map object `k`'s running action. */
ObjAct *func_0027E5F0(int k)
{
    return g_0045D560[k];
}

/* 0x0027E610, 0x44 bytes, matching. Stops it. */
void func_0027E610(int k)
{
    ObjAct *a = func_0027E5F0(k);

    if (a != 0) {
        a->kind = 0x1F;
        g_0045D560[k] = 0;
    }
}

/* 0x0027E660, 0x38 bytes, matching. Stage unit `u`'s running action. */
ObjAct *func_0027E660(u8 *u)
{
    if (u[0x6A] == 0xFF)
        return 0;
    return &g_007720C0[u[0x6A]];
}

/* 0x0027E6A0, 0x3C bytes, matching. Stops it. */
void func_0027E6A0(u8 *u)
{
    ObjAct *a = func_0027E660(u);

    if (a != 0) {
        u[0x6A] = 0xFF;
        a->kind = 0x1F;
    }
}

/* 0x0027E6E0, 0x4C bytes. */
void func_0027E6E0(u8 *u, int f, int off)
{
    if (off != 0)
        func_0027E800(u, off);
    else if (f == 0)
        u[0x69] |= 0x40;
    else
        func_0027E800(u, 1);
}

/* Whether bit `k` of set `s` is on. */
static int bit_on(u8 *s, u32 k)
{
    if ((k & 0xFF) == 0)
        return 0;
    return (1 << (k & 7) & s[(int)(k & 0xFF) >> 3]) != 0;
}

/* 0x0027E730, 0xD0 bytes. Stage unit `u`'s object flags (by its object's bit). */
void func_0027E730(u8 *u, int off)
{
    u32 k = func_001FF100(*(u16 *)(u + 0x54), 10);

    if (bit_on(g_0045D55C, k))
        func_0027E6E0(u, u[0x69] & 2, off);
    else if (off == 0)
        u[0x69] |= 0x46;
    else
        u[0x69] &= 0xB9;
}

/* 0x0027E800, 0xB8 bytes. */
void func_0027E800(u8 *u, int on)
{
    u32 k = func_001FF100(*(u16 *)(u + 0x54), 10);

    if (!bit_on(g_0045D558, k))
        on = on == 0;
    if (on == 0)
        u[0x69] |= 0x40;
    else
        u[0x69] &= 0xBF;
}

/* 0x0027E8C0, 0xC8 bytes. Starts map object `k`'s action (argument `arg`). */
ObjAct *func_0027E8C0(int k, u8 arg)
{
    u8 kind = g_0045D540[k * 3];
    u32 j;

    if (func_0027E5F0(k) != 0)
        return 0;
    for (j = 0; j < 0x32; j = (j + 1) & 0xFF) {
        ObjAct *a = &g_007720C0[j];

        if (a->kind == 0x1F) {
            a->owner = 0;
            a->time = 0;
            a->kind = kind;
            a->arg = arg;
            g_0045D560[k] = a;
            return a;
        }
    }
    return 0;
}

/* 0x0027E990, 0x80 bytes. Starts action `kind` for stage unit `u`. */
ObjAct *func_0027E990(u8 kind, u8 *u, u8 arg)
{
    u32 j;

    if ((char)u[0x6A] != -1)
        return 0;
    for (j = 0; j < 0x32; j = (j + 1) & 0xFF) {
        ObjAct *a = &g_007720C0[j];

        if (a->kind == 0x1F) {
            a->owner = u;
            a->time = 0;
            a->kind = kind;
            a->arg = arg;
            u[0x6A] = j;
            return a;
        }
    }
    return 0;
}

/* 0x0027EA10, 0x5C bytes, matching. Whether map object `k` may act. */
int func_0027EA10(int k)
{
    ObjKind *t = OBJ_KIND(k);

    if (t->can == 0)
        return 0;
    return t->can(k);
}

/* 0x0027EA70, 0x94 bytes. Whether map object `k`'s kind applies to stage unit `u`. */
int func_0027EA70(u32 k, u8 *u, u32 flags)
{
    u8 *o = g_0045D540 + (int)k * 3;

    if ((flags & 4) != 0 && k != (func_001FF100(*(u16 *)(u + 0x54), 10) & 0xFF))
        return 0;
    return g_0043FE40[*o].apply != 0;
}

/* 0x0027EB10, 0x12C bytes. Applies map object `arg[0]`'s action (`arg[1]`) to stage unit `n`. */
int func_0027EB10(int n, int *arg)
{
    u8 *u = UNITS + n * 0x70;
    ObjKind *t = OBJ_KIND(arg[0]);
    u32 f;

    if (func_0027EA70(arg[0], u, t->flags) == 0)
        return 0;
    f = t->flags;
    if (t->apply(u, (char)arg[1]) == 0)
        return 0;
    if ((f & 1) != 0) {
        char c = (char)arg[1];
        int open;

        if (c == 3 || c == 1)
            open = 0;
        else
            open = c == 2 || c == 0;
        if (open)
            u[0x69] |= 8;
        else
            u[0x69] &= 0xF7;
    }
    return 1;
}

/* 0x0027EC40, 0x144 bytes. Applies it again when the unit's open flag and the object's differ. */
int func_0027EC40(int n, int *arg)
{
    u8 *u = UNITS + n * 0x70;
    ObjKind *t = OBJ_KIND(arg[0]);
    char c;
    int on, open;

    if (func_0027EA70(arg[0], u, t->flags) == 0)
        return 0;
    c = (char)arg[1];
    on = (g_0045D54C[n] & 8) != 0;
    if (c == 3 || c == 1)
        open = 0;
    else
        open = c == 2 || c == 0;
    if (open) {
        if ((u[0x69] & 8) == 0 && on)
            return t->apply(u, c);
    } else if ((u[0x69] & 8) != 0 && !on) {
        return t->apply(u, c);
    }
    return 0;
}

/* 0x0027ED90, 0x70 bytes. The three side gates (`how` 0-3, else 4). */
int func_0027ED90(int k, char how)
{
    int v;

    if (how == 3)
        v = 3;
    else if (how == 2)
        v = 2;
    else if (how == 1)
        v = 1;
    else if (how == 0)
        v = 0;
    else
        v = 4;
    func_0027DEA0(k, v);
    return 0;
}

/* 0x0027EE00, 0x124 bytes. Map object `k` acts (`how`) on its units. */
int func_0027EE00(int k, int how)
{
    u8 *o = g_0045D540 + k * 3;
    ObjKind *t = &g_0043FE40[o[0]];
    int arg[2];

    arg[0] = k;
    *(u8 *)&arg[1] = how;
    if (t->before != 0 && t->before(k, o + 2, how) == 0)
        return 0;
    if (t->each == 0)
        return 0;
    if (t->each(o + 2, func_0027EB10, arg) == 0)
        return 0;
    if (t->after != 0 && t->after(k, o + 2, how) == 0)
        return 0;
    return 1;
}

/* 0x0027EF30, 0xA4 bytes, matching. Refreshes map object `k` (its two-way kinds, then its reset). */
void func_0027EF30(int k)
{
    u8 *o = g_0045D540 + k * 3;
    ObjKind *t = &g_0043FE40[o[0]];

    if ((t->flags & 1) != 0) {
        func_0027EFE0(k, 2);
        func_0027EFE0(k, 3);
    }
    if (t->reset != 0)
        t->reset(k, o + 2, g_0045D548[k]);
}

/* 0x0027EFE0, 0xD4 bytes. Applies map object `k`'s state again (`how`) where it changed. */
void func_0027EFE0(int k, int how)
{
    u8 *o = g_0045D540 + k * 3;
    ObjKind *t = &g_0043FE40[o[0]];
    int arg[2];

    arg[0] = k;
    *(u8 *)&arg[1] = how;
    if (t->before != 0 && t->before(k, o + 2, how) == 0)
        return;
    if (t->each != 0 && t->each(o + 2, func_0027EC40, arg) != 0 && t->after != 0)
        t->after(k, o + 2, how);
}

/* 0x0027F0C0, 0x54 bytes. Whether map object `k`'s bit is set. */
int func_0027F0C0(int k)
{
    if (k == 0)
        return 0;
    return (1 << (k % 8 & 0x1F) & g_0045D55C[k / 8]) != 0;
}

/* 0x0027F120, 0x18 bytes, matching. Map object `k`'s data. */
u8 *func_0027F120(int k)
{
    return g_0045D540 + k * 3 + 2;
}

/* 0x0027F140, 0x18 bytes, matching. Its kind. */
u32 func_0027F140(int k)
{
    return g_0045D540[k * 3];
}

/* 0x0027F160, 0xE8 bytes. Map object `k` acts (`how`; reversed for objects of the other side). */
void func_0027F160(int k, char how)
{
    if (k < 0)
        return;
    if (k < 3) {
        func_0027ED90(k, how);
    } else if ((u32)k < g_0045D564) {
        char side = g_0045D540[k * 3 + 1];
        int other = g_00669DB8 == 2 ? side != 0 : side == 1;

        if (other) {
            if (how == 3)
                how = 2;
            else if (how == 1)
                how = 0;
            else if (how == 2)
                how = 3;
            else if (how == 0)
                how = 1;
        }
        func_0027EE00(k, how);
    }
}

/* 0x0027F250, 0x58 bytes, matching. Map object `k`'s event `v`. */
void func_0027F250(int k, int v)
{
    u8 *o = g_0045D540 + k * 3;
    ObjKind *t = &g_0043FE40[o[0]];

    if (t->event != 0)
        t->event(k, o + 2, v);
}

/* 0x0027F2B0, 8 bytes. */
u32 func_0027F2B0(void)
{
    return g_0045D550;
}

/* 0x0027F2C0, 0x168 bytes. Sets the objects for the battle start (or loads them when resuming). */
void func_0027F2C0(void)
{
    if (g_00669F6C == 1) {
        func_0027F6F0();
    } else {
        u32 n = func_00196A10(), k;

        for (k = 0; k < n; k++)
            func_0027E800(UNITS + k * 0x70, 0);
        for (k = 1; k < g_0045D564; k++) {
            u8 *o = g_0045D540 + k * 3;
            int other = g_00669DB8 == 2 ? o[1] != 0 : o[1] == 1;

            if (other)
                func_0027EE00(k, 2);
            else if ((g_0043FE40[o[0]].flags & 0x20) != 0)
                func_0027EE00(k, 3);
        }
    }
    if (g_00669F6C == 1)
        func_0027F980();
    func_001F5870();
}

/* 0x0027F430, 0x24 bytes, matching. Frees the objects. */
void func_0027F430(void)
{
    func_002C45C0();
    func_00102EC0((unsigned char *)(g_0045D560));
}

/* 0x0027F460, 0x16C bytes. Resets the objects: the map's gates marked, no actions, every kind's
 * own reset. */
void func_0027F460(void)
{
    u8 n = g_0045D2F0[0x10A];
    u32 k;

    for (k = 0; k < n; k++) {
        if ((char)(*(u8 **)(g_0045D2F0 + 0x10C))[k * 0xC + 0xB] != -1) {
            u8 b = 1 << (k & 7);

            g_0073DC98[(int)k >> 3] |= b;
            g_0073DF28[(int)k >> 3] |= b;
        }
    }
    func_00118850((unsigned char *)(g_0045D560), g_0045D564 << 2);
    func_00118850((unsigned char *)(g_007720C0), 600);
    for (k = 0; k < 0x32; k++)
        g_007720C0[k].kind = 0x1F;
    func_001185E0(g_0045D544, 1, 3);
    func_002BBE70();
    func_002BCA70();
    func_002C17E0();
    func_002C1C80();
    func_002BF990();
    func_002C2A10();
    func_002C3D60();
    func_002C4570();
}

/* 0x0027F5D0, 0x38 bytes, matching. Sets up the objects. */
void func_0027F5D0(void)
{
    g_0045D54C = 0;
    g_0045D548 = 0;
    g_0045D560 = (ObjAct **)(func_00102D30(g_0045D564 << 2));
    func_0027F460();
    func_0027F610();
}
