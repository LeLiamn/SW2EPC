/*
 * sc_sysmsg.c - the battle's system messages: a queue of 0x40 requests of 8 bytes at 0x005BC3A8
 * (u16 kind 1-0x14, 0x15 = free, then three u16 parameters) turned into officer lines and
 * announcements in the message window (original source file sc_sysmsg.c, referenced at
 * 0x0023ED90). Written so far: 0x0023C190-0x0023EF4C.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The message window object (`w`, 0x005BBF18) used here: +0x108 the announcement window kind,
 * +0x110 the officer line window kind, +0x114 the speaking officer, +0x118 / +0x120 / +0x124 line
 * flags, +0x11C the portrait, +0x128 the map marker kind, +0x12C / +0x12E the marker's name ids,
 * +0x130 the side, +0x134, +0x138 / +0x13C the marker position, +0x144 a number, +0x14C the
 * window mode.
 */

#define SW2E_FILE_SC_SYSMSG_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00693970[];                  /* the game state (unit records first, 0x88 bytes) */
extern u8 g_006A1D58[][0x68];            /* the soldier groups */
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
extern ps2ptr g_005BA6BC_a;   /* message text tables */
#define g_005BA6BC ((u8 *)PS2_PTR(g_005BA6BC_a))
#define g_005BA6BC_SET(v) (g_005BA6BC_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6BC;
#define g_005BA6BC_a (*(ps2ptr *)&g_005BA6BC)
#define g_005BA6BC_SET(v) (g_005BA6BC = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005BA6C0_a;   /* message text tables */
#define g_005BA6C0 ((u8 *)PS2_PTR(g_005BA6C0_a))
#define g_005BA6C0_SET(v) (g_005BA6C0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6C0;
#define g_005BA6C0_a (*(ps2ptr *)&g_005BA6C0)
#define g_005BA6C0_SET(v) (g_005BA6C0 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005BA7B0_a;   /* message text tables */
#define g_005BA7B0 ((u8 *)PS2_PTR(g_005BA7B0_a))
#define g_005BA7B0_SET(v) (g_005BA7B0_a = PS2_ADDR(v))
#else
extern u8 *g_005BA7B0;
#define g_005BA7B0_a (*(ps2ptr *)&g_005BA7B0)
#define g_005BA7B0_SET(v) (g_005BA7B0 = (v))
#endif
extern u8 *g_005BA6C4[];                 /* the officers' line texts, by kind */
extern u8 *g_005BA76C[];                 /* more line texts, by func_0023C190's group */
extern u8 g_005BD740[8];                 /* scenario switches */
extern u8 g_005BD742;
extern u8 g_005BBF18[];                  /* the message window */
extern char g_005BBF20[];                /* its text */
extern u16 g_005BC3A8[0x40][4];          /* the message requests */
extern u32 g_005BA7BC;                   /* the last officer kind that spoke */
extern u8 g_00669D60[];                  /* the settings */
extern u8 g_00669FAE[];
extern const char *g_0042E260[];         /* the sides' army names */
extern u32 g_0043D160[0x1A][4], g_0043D300[0x1A][2];
extern short g_0045CDE0;                 /* (small data) the generic officer name */
extern int g_0045D2A8;
extern u16 g_006AA5D8;
extern const char g_0043D3D0[], g_0043D3D8[], g_0043D410[];
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define UNIT(i) (g_00693970 + (i) * 0x88)
#define UNIT_FLAGS(u) (*(u32 *)((u) + 0x80))
#define UNIT_ACTIVE(u) ((UNIT_FLAGS(u) & 1) != 0 && (UNIT_FLAGS(u) & 0x8C40002) == 0)
#define TEXT(t, k) ((char *)(t) + *(int *)((t) + (k) * 4 + 4))
#define W(w, off) (*(int *)((w) + (off)))
#define SETTINGS_FLAGS (*(u32 *)(g_00669D60 + 0x200))

void func_0022F120(u8 *f, char *out, const char *text, u32 ca, u32 cb);
void func_001204B0(char *to, const char *format, ...);
void func_00120928(char *to, const char *from);
int func_002D6F80(u16 a, u16 b);
int func_002D6F90(u16 a, u8 *o, u8 *pos, int side, u32 f);

int func_0023D6C0(short n);

/* Unit `u`'s map position (where it stands or rides). */
static u8 *unit_pos(u8 *u)
{
    return (UNIT_FLAGS(u) & 0x20000) != 0 ? u + 0x30 : u + 0x28;
}

/* Shows the announcement text (window mode 0, +0x134 `b`). */
static void show_sys(u8 *box, u8 *w, int b)
{
    W(w, 0x14C) = 0;
    W(w, 0x134) = b;
    func_0022EF90(box, W(w, 0x108), 0);
}

/* Shows officer `o`'s line (window mode 1). */
static void show_line(u8 *box, u8 *w, u8 *o, int a120, int a118, int side)
{
    W(w, 0x14C) = 1;
    W(w, 0x114) = (o - g_005BA6A0) / 0x2C;
    W(w, 0x11C) = o[6];
    W(w, 0x120) = a120;
    W(w, 0x118) = a118;
    W(w, 0x124) = 0;
    W(w, 0x130) = side;
    func_0022EF90(box, W(w, 0x110), 1);
}

/* Officer `o`'s line kind (0x21 and up shifted down by 9; 0x2A for none). */
static u32 line_kind(u8 *o)
{
    u32 k = o[5];

    if (k > 0x21)
        k -= 9;
    return k;
}

/* 0x0023C190, 0x164 bytes. Officer `o`'s group of reply lines (by its kind). */
u32 func_0023C190(u8 *o)
{
    switch (o[5]) {
    case '*': return 0x10;
    case ')': return 0xF;
    case '(': return 0xE;
    case '\'': return 0xD;
    case '&': return 0xC;
    case '%': return 0xB;
    case '$': return 10;
    case '!': return 9;
    case ' ': return 8;
    case 0x1F: return 7;
    case 0x1E: return 6;
    case 0x1D: return 5;
    case 0x1C: return 4;
    case 0x1B: return 3;
    case 0x1A: return 2;
    case 0xC: return 1;
    case 6: return 0;
    default: return 0xD;
    }
}

/* 0x0023C300, 0x104 bytes. Whether officer `a` has a special line for officer `b` (its line
 * number moves by three for each table step). */
int func_0023C300(int *line, u8 *a, u8 *b)
{
    u32 ka, kb, k;

    if (g_005BD742 != 0)
        return 0;
    ka = a[6];
    kb = b[6];
    if (ka >= 0x1A)
        return 0;
    for (k = 0; k < 4; k++) {
        if (kb == g_0043D160[ka][k]) {
            *line += k * 3;
            return 1;
        }
        if (ka == 7 && k == 0 && (kb == 0x17 || kb == 0x15 || kb == 0xF || kb == 10 || kb == 6 || kb == 5)) {
            *line = *line;
            return 1;
        }
    }
    return 0;
}

/* 0x0023C410, 0x1B4 bytes. A side 0 unit (groups 0x46-) of an officer bound to player `p`'s
 * officer (or whether unit `u` is one). */
u8 *func_0023C410(int p, u8 *u)
{
    u32 kind = *(u32 *)(g_00669D60 + p * 0x48 + 0x88), k;

    if (g_005BD742 != 0 || kind >= 0x1A)
        return 0;
    if (u == 0) {
        u32 r = RANDOM();

        for (k = 0; k < 2; k++) {
            u32 o = g_0043D300[kind][((r & 1) + k) & 1], j;

            if (o >= 0x19F)
                continue;
            for (j = 0x46; j < 0x47; j++) {
                u8 **g = (u8 **)g_006A1D58[j];
                u8 *x;

                if ((((u32 *)g)[0x19] & 1) == 0)
                    continue;
                x = *g;
                if (UNIT_ACTIVE(x) && (UNIT_FLAGS(x) & 4) == 0 && x[0x79] == 0 && o == (PS2_LOADP(u8 *, (x + 8)))[6])
                    return x;
            }
        }
    } else {
        for (k = 0; k < 2; k++) {
            if ((PS2_LOADP(u8 *, (u + 8)))[6] == g_0043D300[kind][k])
                return u;
        }
    }
    return 0;
}

/* 0x0023C5D0, 0xC4 bytes. Request 0x14: a player's group event (kept while it waits). */
int func_0023C5D0(u8 *t, u16 *a)
{
    u8 *u;

    if (g_0045D2A8 != 0 && a[1] == g_006AA5D8)
        return 0;
    u = UNIT(a[1]);
    if ((UNIT_FLAGS(u) & 1) != 0 && func_002D6F80(a[0], a[1]) != 0 && (UNIT_FLAGS(u) & 6) != 0)
        *t |= 0x10;
    return 1;
}

/* 0x0023C6A0, 0xCC bytes. Request 0x13: a side 1 unit's event. */
void func_0023C6A0(u8 *t, u16 *a)
{
    u8 *u = UNIT(a[1]);
    u32 f = UNIT_FLAGS(u);

    if (UNIT_ACTIVE(u) && (f & 4) == 0 && u[0x79] != 0) {
        if (func_002D6F90(a[0], PS2_LOADP(u8 *, (u + 8)), unit_pos(u), u[0x79], f & 0x200) != 0)
            *t |= 0x10;
    }
}

/* 0x0023C770, 0xA4 bytes. Request 0x12: announcement 0x13 with player 0's officer. */
void func_0023C770(u8 *box, u8 *w, char *text)
{
    char fmt[256], name[256];
    u8 *u;

    func_0022F120(w, fmt, TEXT(g_005BA6BC, 0x13), 0, 0);
    u = func_0035DCD0(0);
    func_0019B170(name, *PS2_LOADP(u16 *, (u + 8)), (PS2_LOADP(u16 *, (u + 8)))[1]);
    func_001204B0(text, fmt, name);
    show_sys(box, w, 1);
}

/* 0x0023C820, 0x6C bytes. Request 0x11: announcement 0x12. */
void func_0023C820(u8 *box, u8 *w, char *text)
{
    func_0022F120(w, text, TEXT(g_005BA6BC, 0x12), 0, 0);
    show_sys(box, w, 1);
}

/* 0x0023C890, 0x1B4 bytes. Request 0x10: a side 1 officer's challenge (lines 0xB-0xD). */
void func_0023C890(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *u = UNIT(a[0]), *o;
    u32 k;

    if (!UNIT_ACTIVE(u) || (UNIT_FLAGS(u) & 4) != 0 || u[0x79] == 0)
        return;
    o = PS2_LOADP(u8 *, (u + 8));
    k = line_kind(o);
    if (k < 0x2A) {
        u32 r = RANDOM();

        if (g_005BD740[0] == 0)
            func_0022F120(w, text, TEXT(g_005BA6C4[k], r % 3 + 0xB), 0, 0);
        show_line(box, w, o, 0, 1, u[0x79]);
    }
}

/* 0x0023CA50, 0x200 bytes. Request 0xF: a side 0 officer answers a player (lines 9, 10, 0x10 or a
 * special one). */
void func_0023CA50(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *u = UNIT(a[1]), *o, *p;
    u32 k;
    int line;

    if (!UNIT_ACTIVE(u) || (UNIT_FLAGS(u) & 4) != 0 || u[0x79] != 0)
        return;
    o = PS2_LOADP(u8 *, (u + 8));
    p = PS2_LOADP(u8 *, (func_0035DCD0(a[0]) + 8));
    k = line_kind(o);
    if (k >= 0x2A)
        return;
    if (func_0023C410(a[0], u) == 0)
        line = o[4] < p[4] ? 9 : 10;
    else
        line = 0x10;
    func_0023C300(&line, o, p);
    if (g_005BD740[0] == 0)
        func_0022F120(w, text, TEXT(g_005BA6C4[k], line), 0, 0);
    show_line(box, w, o, 1, 0, u[0x79]);
}

/* 0x0023CC50, 0xE0 bytes. Request 0xE: the narrator's line at unit `a`. */
void func_0023CC50(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *u = UNIT(a[0]);

    func_0022F120(w, text, TEXT(g_005BA7B0, 0), 0, 0);
    func_00183670(PS2_ADDR((float *)unit_pos(u)));
    W(w, 0x14C) = 1;
    W(w, 0x114) = 0x1E4;
    W(w, 0x11C) = g_005BA6A0[0x5336];
    W(w, 0x120) = 0;
    W(w, 0x118) = 0;
    W(w, 0x124) = 0;
    W(w, 0x130) = u[0x79];
    func_0022EF90(box, W(w, 0x110), 1);
}

/* 0x0023CD30, 0x128 bytes. Request 0xD: unit `a`'s officer's reply (one of two). */
void func_0023CD30(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *o = PS2_LOADP(u8 *, (UNIT(a[0]) + 8));
    u8 *t = g_005BA76C[func_0023C190(o)];

    func_0022F120(w, text, TEXT(t, (RANDOM() & 1) != 0), 0, 0);
    W(w, 0x14C) = 1;
    W(w, 0x114) = (o - g_005BA6A0) / 0x2C;
    W(w, 0x11C) = o[6];
    W(w, 0x120) = 3;
    W(w, 0x118) = 0;
    W(w, 0x124) = 0;
    func_0022EF90(box, W(w, 0x110), 1);
}

/* 0x0023CE60, 0x100 bytes. Request 0xC: announcement 5 with unit `a`'s officer. */
void func_0023CE60(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256], name[264];
    u8 *u = UNIT(a[0]);
    u32 pos[2];

    func_0022F120(w, fmt, TEXT(g_005BA6BC, 5), 0, 0);
    func_0019B170(name, *PS2_LOADP(u16 *, (u + 8)), (PS2_LOADP(u16 *, (u + 8)))[1]);
    func_001204B0(text, fmt, name);
    pos[0] = ((u32 *)unit_pos(u))[0];
    pos[1] = ((u32 *)unit_pos(u))[1];
    func_00183670(PS2_ADDR((float *)pos));
    func_002C4AE0(pos, PS2_ADDR(text));
    show_sys(box, w, 1);
}

/* 0x0023CF60, 0x224 bytes. Request 0xB: a player's officer (or a bound one, or player 1's) on its
 * merit `a[1]` (lines 1-3, 0xE). */
void func_0023CF60(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *pu = func_0035DCD0(a[0]), *po = PS2_LOADP(u8 *, (pu + 8)), *o = po;
    int line;
    u32 k;

    if (a[1] % 1000 < 100) {
        if ((SETTINGS_FLAGS & 4) == 0) {
            u8 *x = func_0023C410(a[0], 0);

            if (x != 0) {
                o = PS2_LOADP(u8 *, (x + 8));
                line = 0xE;
                func_0023C300(&line, o, po);
                goto speak;
            }
            {
                u8 *q = func_001B9330(0);

                if (q == 0 || pu == q) {
                    line = 1;
                } else {
                    line = 2;
                    pu = q;
                    o = PS2_LOADP(u8 *, (q + 8));
                }
            }
        } else {
            line = 1;
        }
    } else {
        line = 3;
    }
speak:
    k = line_kind(o);
    if (k >= 0x2A)
        return;
    if (g_005BD740[0] == 0)
        func_0022F120(w, text, TEXT(g_005BA6C4[k], line), 0, 0);
    if ((*(u32 *)(pu + 0x84) & 0x8000) == 0)
        func_00183670(PS2_ADDR((float *)unit_pos(pu)));
    show_line(box, w, o, 1, 0, pu[0x79]);
}

/* 0x0023D190, 0x11C bytes. Request 10: announcement 6 with a player's officer and its count (in
 * hundreds). */
void func_0023D190(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256], name[256];
    u8 *u = func_0035DCD0(a[0]);
    u16 *n = PS2_LOADP(u16 *, (u + 8));

    func_0022F120(w, fmt, TEXT(g_005BA6BC, 6), 0, 0);
    func_0019B170(name, n[0], n[1]);
    func_001204B0(text, fmt, name, a[1] / 100 * 100);
    func_00183670(PS2_ADDR((float *)unit_pos(u)));
    show_sys(box, w, 0);
}

/* 0x0023D2B0, 0x244 bytes. Request 9: a unit's count (in fifties) with a map marker (texts
 * 0x11-0x13 by side). */
void func_0023D2B0(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256], name[256];
    u8 *u = UNIT(a[0]);
    u32 side, pos[2], at[2];
    u16 n0, n1;
    int k, v;

    if (!UNIT_ACTIVE(u))
        return;
    side = u[0x79];
    if (side == 2)
        k = 0x13;
    else if (side == 1)
        k = 0x12;
    else if (side == 0)
        k = 0x11;
    else
        return;
    func_0022F120(w, fmt, TEXT(g_005BA6C0, k), 0, 0);
    n0 = (PS2_LOADP(u16 *, (u + 8)))[0];
    n1 = (PS2_LOADP(u16 *, (u + 8)))[1];
    func_0019B170(name, n0, n1);
    v = a[1] / 0x32 * 0x32;
    func_001204B0(text, fmt, name, v);
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0) {
        pos[0] = ((u32 *)unit_pos(u))[0];
        pos[1] = ((u32 *)unit_pos(u))[1];
        func_001F0960((float *)(pos), (float *)&at[0], (float *)&at[1]);
    } else {
        *(float *)&pos[0] = -1.0f;
        *(float *)&pos[1] = -1.0f;
        *(float *)&at[0] = -1.0f;
        *(float *)&at[1] = -1.0f;
    }
    W(w, 0x128) = 5;
    *(u16 *)(w + 0x12C) = n0;
    *(u16 *)(w + 0x12E) = n1;
    W(w, 0x130) = side;
    W(w, 0x120) = 1;
    W(w, 0x138) = at[0];
    W(w, 0x13C) = at[1];
    W(w, 0x144) = v;
    func_002C4AE0(pos, PS2_ADDR(text));
    W(w, 0x14C) = 3;
    func_0022EF90(box, 0, 3);
}

/* 0x0023D500, 0x1BC bytes. Request 8: a side 0 officer's line 9. */
void func_0023D500(u8 *box, u8 *w, char *text, u16 *a)
{
    u8 *u = UNIT(a[0]), *o;
    u32 k;

    if (!UNIT_ACTIVE(u) || (UNIT_FLAGS(u) & 4) != 0 || u[0x79] != 0)
        return;
    o = PS2_LOADP(u8 *, (u + 8));
    k = line_kind(o);
    if (k >= 0x2A || g_005BD740[0] != 0)
        return;
    func_0022F120(w, text, TEXT(g_005BA6C4[k], 8), 0, 0);
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0)
        func_00183670(PS2_ADDR((float *)unit_pos(u)));
    show_line(box, w, o, 3, 0, u[0x79]);
}

/* 0x0023D6C0, 0x44 bytes. Whether name id `n` is the generic officer's. */
int func_0023D6C0(short n)
{
    return n == g_0045CDE0;
}

/* 0x0023D710, 0x1B4 bytes. Request 7: announcement 4 with a side 0 officer ("A ..." for the
 * generic one). */
void func_0023D710(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256], name[264];
    u8 *u = UNIT(a[0]);
    u16 *n;
    u32 pos[2], f = UNIT_FLAGS(u);

    if (!UNIT_ACTIVE(u) || (f & 4) != 0 || u[0x79] != 0)
        return;
    n = PS2_LOADP(u16 *, (u + 8));
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0) {
        pos[0] = ((u32 *)unit_pos(u))[0];
        pos[1] = ((u32 *)unit_pos(u))[1];
    } else {
        *(float *)&pos[0] = -1.0f;
        *(float *)&pos[1] = -1.0f;
    }
    func_0022F120(w, fmt, TEXT(g_005BA6BC, 4), 0, 0);
    func_0019B170(name, n[0], n[1]);
    func_001204B0(text, fmt, name);
    if (func_0023D6C0(n[0]) != 0) {
        func_001204B0(fmt, g_0043D3D0, text);
        func_00120928(text, fmt);
    }
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0)
        func_00183670(PS2_ADDR((float *)pos));
    func_002C4AE0(pos, PS2_ADDR(text));
    show_sys(box, w, 0);
}

/* 0x0023D8D0, 0x2B0 bytes. Request 6: group `a`'s leader with a map marker (texts 10-0xF by side
 * and `a[1]`). */
void func_0023D8D0(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256], name[256];
    u8 **g = (u8 **)g_006A1D58[a[0]], *u;
    u16 *n;
    u32 side, pos[2], at[2];
    int k;

    if ((((u32 *)g)[0x19] & 1) == 0 || (u = *g) == 0 || !UNIT_ACTIVE(u))
        return;
    side = u[0x79];
    n = PS2_LOADP(u16 *, (u + 8));
    if (side == 2)
        k = a[1] == 0 ? 0xF : 0xC;
    else if (side == 1)
        k = a[1] == 0 ? 0xE : 0xB;
    else if (side == 0)
        k = a[1] == 0 ? 0xD : 10;
    else
        return;
    func_0022F120(w, fmt, TEXT(g_005BA6C0, k), 0, 0);
    func_0019B170(name, n[0], n[1]);
    func_001204B0(text, fmt, name);
    pos[0] = ((u32 *)unit_pos(u))[0];
    pos[1] = ((u32 *)unit_pos(u))[1];
    W(w, 0x11C) = *(u8 *)(n + 3);
    if (a[1] == 0) {
        W(w, 0x128) = 4;
        W(w, 0x120) = 3;
    } else {
        W(w, 0x128) = 3;
        W(w, 0x120) = 1;
    }
    *(u16 *)(w + 0x12C) = n[0];
    *(u16 *)(w + 0x12E) = n[1];
    W(w, 0x130) = side;
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0) {
        func_001F0960((float *)(pos), (float *)&at[0], (float *)&at[1]);
    } else {
        *(float *)&pos[0] = -1.0f;
        *(float *)&pos[1] = -1.0f;
        *(float *)&at[0] = -1.0f;
        *(float *)&at[1] = -1.0f;
    }
    W(w, 0x138) = at[0];
    W(w, 0x13C) = at[1];
    W(w, 0x14C) = 3;
    func_002C4AE0(pos, PS2_ADDR(text));
    func_0022EF90(box, 0, 3);
}

/* 0x0023DB80, 0x54 bytes. Request 5: a map marker only (kind 6 / 7). */
void func_0023DB80(u8 *box, u8 *w, u16 *a)
{
    W(w, 0x128) = a[1] == 0 ? 7 : 6;
    W(w, 0x130) = a[0];
    *(float *)(w + 0x138) = -1.0f;
    *(float *)(w + 0x13C) = -1.0f;
    W(w, 0x14C) = 3;
    func_0022EF90(box, 0, 3);
}

/* 0x0023DBE0, 0x1F8 bytes. Request 4: side `a[2]`'s army at a base (texts 5, 7, 9). */
void func_0023DBE0(u8 *box, u8 *w, char *text, u16 *a)
{
    char fmt[256];
    u8 *b;
    float at[2];
    int k;

    if (a[2] == 2)
        k = 9;
    else if (a[2] == 1)
        k = 5;
    else if (a[2] == 0)
        k = 7;
    else
        return;
    func_0022F120(w, fmt, TEXT(g_005BA6C0, k), 0, 0);
    func_001204B0(text, fmt, g_0042E260[g_00669FAE[a[2]]]);
    W(w, 0x128) = 0;
    W(w, 0x130) = a[2];
    b = (u8 *)PS2_PTR(func_00215480(PS2_ADDR(UNIT(a[0]) + 0x40)));
    if (b == 0) {
        at[0] = -1.0f;
        at[1] = -1.0f;
    } else {
        u8 c[4];

        func_00215520(b, (short unsigned int *)(c));
        at[0] = (float)c[0] * 5000.0f + 2500.0f;
        at[1] = (float)c[1] * 5000.0f + 2500.0f;
    }
    *(float *)(w + 0x138) = at[0];
    *(float *)(w + 0x13C) = at[1];
    func_002C4AE0((unsigned int *)(at), PS2_ADDR(text));
    W(w, 0x14C) = 3;
    func_0022EF90(box, 0, 3);
}

/* 0x0023DDE0, 0x3E8 bytes. Request 3: unit `a[1]` beat (or, `a[0]`, lost to) the unit it was
 * fighting (texts 7-0x11 by side). */
void func_0023DDE0(u8 *box, u8 *w, char *text, short *a)
{
    char tmp[256], fmt[256], nb[256], na[264];
    u8 *u = UNIT((u16)a[1]), *t;
    u16 ti = *(u16 *)(u + 0x4A), *n, *m;
    u32 f800, pos[2];
    int lost, k;
    u8 side;

    if (ti == 0x1AD)
        return;
    t = UNIT(ti);
    f800 = UNIT_FLAGS(t) & 0x800;
    side = u[0x79];
    lost = a[0] != 0;
    if (side == 2) {
        if (f800 == 0)
            k = lost ? 0x11 : 10;
        else
            k = lost ? 0xC : 8;
    } else if (side == 1) {
        if (f800 == 0)
            k = lost ? 0x10 : 9;
        else
            k = lost ? 0xE : 7;
    } else if (side == 0) {
        if (f800 == 0)
            k = 0xF;
        else
            k = a[0] == 1 ? 0xB : 0xD;
    } else {
        return;
    }
    func_0022F120(w, fmt, TEXT(g_005BA6BC, k), 0, 0);
    n = PS2_LOADP(u16 *, (u + 8));
    if ((UNIT_FLAGS(t) & 0x180) != 0)
        t = func_0035DCD0((UNIT_FLAGS(t) & 0x80) == 0);
    m = PS2_LOADP(u16 *, (t + 8));
    func_0019B170(na, n[0], n[1]);
    func_0019B170(nb, m[0], m[1]);
    switch (k) {
    case 7:
    case 8:
        if (func_0023D6C0(n[1]) != 0) {
            func_001204B0(tmp, g_0043D3D8, na);
            func_00120928(na, tmp);
        }
        if (func_0023D6C0(m[1]) != 0) {
            func_001204B0(tmp, g_0043D3D0, nb);
            func_00120928(nb, tmp);
        }
        func_001204B0(text, fmt, nb, na);
        break;
    case 9:
    case 10:
        func_001204B0(text, fmt, na);
        break;
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        if (func_0023D6C0(n[1]) != 0) {
            func_001204B0(tmp, g_0043D3D0, na);
            func_00120928(na, tmp);
        }
        if (func_0023D6C0(m[1]) != 0) {
            func_001204B0(tmp, g_0043D3D8, nb);
            func_00120928(nb, tmp);
        }
        func_001204B0(text, fmt, na, nb);
        break;
    case 0xF:
    case 0x10:
    case 0x11:
        if (func_0023D6C0(n[1]) != 0) {
            func_001204B0(fmt, g_0043D3D0, text);
            func_00120928(text, fmt);
        }
        func_001204B0(text, fmt, na);
        break;
    default:
        return;
    }
    pos[0] = ((u32 *)unit_pos(u))[0];
    pos[1] = ((u32 *)unit_pos(u))[1];
    if ((*(u32 *)(u + 0x84) & 0x8000) == 0)
        func_00183670(PS2_ADDR((float *)pos));
    func_002C4AE0(pos, PS2_ADDR(text));
    show_sys(box, w, 0);
}

/* 0x0023E620, 0x220 bytes. Request 1: officer kind `a[0] + 0x24E` speaks to a player, then the
 * player's reaction above unit `a[1]`. */
void func_0023E620(u8 *box, u8 *w, char *text, u16 *a)
{
    char out[256], fmt[256], name[256];
    u8 f[344];
    u8 *o = g_005BA6A0 + (a[0] + 0x24E) * 0x2C, *p, *u;
    u32 k = line_kind(o), pos[2];

    if (k >= 0x2A || g_005BD740[0] != 0)
        return;
    func_0022F120(w, text, TEXT(g_005BA6C4[k], 0), 0, 0);
    p = func_0035DCD0(a[0]);
    func_00183670(PS2_ADDR((float *)unit_pos(p)));
    u = UNIT(a[1]);
    pos[0] = ((u32 *)unit_pos(u))[0];
    pos[1] = ((u32 *)unit_pos(u))[1];
    func_0022F120(f, fmt, TEXT(g_005BA6C0, u[0x79] != 1), 0, 0);
    func_0019B170(name, (PS2_LOADP(u16 *, (u + 8)))[0], (PS2_LOADP(u16 *, (u + 8)))[1]);
    func_001204B0(out, fmt, name);
    func_002C4AE0(pos, PS2_ADDR(out));
    show_line(box, w, o, 1, 0, p[0x79]);
}

void func_0023E1D0(u8 *box, u8 *w, char *text, u16 *a);

/* 0x0023E840, 0x2C0 bytes. Runs message request `t[2]` (timer `t`); whether it is done. */
int func_0023E840(u8 *t)
{
    u16 *r = g_005BC3A8[t[2]];
    u8 *w = g_005BBF18;
    char *s = g_005BBF20;
    u16 *a = r + 1;

    func_00120928(s, g_0043D410);
    switch (r[0]) {
    case 1:
        func_0023E620(t, w, s, a);
        break;
    case 2:
        func_0023E1D0(t, w, s, a);
        break;
    case 3:
        func_0023DDE0(t, w, s, (short *)a);
        break;
    case 4:
        func_0023DBE0(t, w, s, a);
        break;
    case 5:
        func_0023DB80(t, w, a);
        break;
    case 6:
        func_0023D8D0(t, w, s, a);
        break;
    case 7:
        func_0023D710(t, w, s, a);
        break;
    case 8:
        func_0023D500(t, w, s, a);
        break;
    case 9:
        func_0023D2B0(t, w, s, a);
        break;
    case 10:
        func_0023D190(t, w, s, a);
        break;
    case 0xB:
        func_0023CF60(t, w, s, a);
        break;
    case 0xC:
        func_0023CE60(t, w, s, a);
        break;
    case 0xD:
        func_0023CD30(t, w, s, a);
        break;
    case 0xE:
        func_0023CC50(t, w, s, a);
        break;
    case 0xF:
        func_0023CA50(t, w, s, a);
        break;
    case 0x10:
        func_0023C890(t, w, s, a);
        break;
    case 0x11:
        func_0023C820(t, w, s);
        break;
    case 0x12:
        func_0023C770(t, w, s);
        break;
    case 0x13:
        func_0023C6A0(t, a);
        break;
    case 0x14:
        if (func_0023C5D0(t, a) == 0)
            return 0;
        break;
    }
    r[0] = 0x15;
    return 1;
}

/* 0x0023EB00, 0x40 bytes. The first free request (0x40 for none). */
u32 func_0023EB00(void)
{
    u32 k;

    for (k = 0; k < 0x40; k++) {
        if (g_005BC3A8[k][0] > 0x14)
            return k;
    }
    return 0x40;
}

/* 0x0023EB40, 0xEC bytes. Queues message request `r` to show after `delay` (only some kinds in
 * the flag-4 mode, none in the flag-8 one). */
void func_0023EB40(short *r, int delay, int c)
{
    u32 k;

    if ((SETTINGS_FLAGS & 8) != 0)
        return;
    if ((SETTINGS_FLAGS & 4) != 0 && r[0] != 0x12 && r[0] != 0x11 && r[0] != 0xD && r[0] != 0xC && r[0] != 1)
        return;
    k = func_0023EB00();
    if (k >= 0x40)
        return;
    func_00118AC0((unsigned int *)(g_005BC3A8[k]), (unsigned char *)(r), 8);
    func_00183410(1, k, 3, delay, c);
}

#ifdef SW2E_PC
extern ps2ptr g_005BA6B8_a;                   /* the battle text file */
#define g_005BA6B8 ((u8 *)PS2_PTR(g_005BA6B8_a))
#define g_005BA6B8_SET(v) (g_005BA6B8_a = PS2_ADDR(v))
#else
extern u8 *g_005BA6B8;
#define g_005BA6B8_a (*(ps2ptr *)&g_005BA6B8)
#define g_005BA6B8_SET(v) (g_005BA6B8 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005BA7B4_a;
#define g_005BA7B4 ((u8 *)PS2_PTR(g_005BA7B4_a))
#define g_005BA7B4_SET(v) (g_005BA7B4_a = PS2_ADDR(v))
#else
extern u8 *g_005BA7B4;
#define g_005BA7B4_a (*(ps2ptr *)&g_005BA7B4)
#define g_005BA7B4_SET(v) (g_005BA7B4 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_005BA7B8_a;
#define g_005BA7B8 ((u8 *)PS2_PTR(g_005BA7B8_a))
#define g_005BA7B8_SET(v) (g_005BA7B8_a = PS2_ADDR(v))
#else
extern u8 *g_005BA7B8;
#define g_005BA7B8_a (*(ps2ptr *)&g_005BA7B8)
#define g_005BA7B8_SET(v) (g_005BA7B8 = (v))
#endif
extern const char g_0043D478[];

/* 0x0023EC30, 0x64 bytes. Loads the requests from a save image; its end. */
u8 *func_0023EC30(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x40; k++, p += 8)
        func_00118AC0((unsigned int *)(g_005BC3A8[k]), p, 8);
    return p;
}

/* 0x0023ECA0, 0x64 bytes. Saves them. */
u8 *func_0023ECA0(u8 *p)
{
    u32 k;

    for (k = 0; k < 0x40; k++, p += 8)
        func_00118AC0((unsigned int *)(p), (unsigned char *)(g_005BC3A8[k]), 8);
    return p;
}

/* 0x0023ED10, 8 bytes, matching. */
void func_0023ED10(void)
{
}

/* 0x0023ED20, 0x48 bytes. Empties the requests. */
void func_0023ED20(void)
{
    u32 k;

    for (k = 0; k < 0x40; k++)
        g_005BC3A8[k][0] = 0x15;
}

/* 0x0023ED70, 0x20 bytes. Frees the battle text file. */
void func_0023ED70(void)
{
    func_00102EC0(g_005BA6B8);
}

/* 0x0023ED90, 0x1B8 bytes. Loads the battle text file and finds its text tables (by offsets):
 * announcements, markers, 42 officer kinds' lines, 17 reply groups and three more. */
void func_0023ED90(void)
{
    u8 *f = func_001026D0(1, 0x32, 0, 1, 0, 0, g_0043D478, 0x65E);
    int *t;
    u32 k;

    g_005BA6BC_SET(f + *(int *)(f + 4));
    g_005BA6C0_SET(f + *(int *)(f + 0xC));
    g_005BA6B8_SET(f);
    t = (int *)(f + *(int *)(f + 0x14));
    for (k = 0; k < 0x2A; k++)
        g_005BA6C4[k] = (u8 *)t + t[k * 2];
    t = (int *)(f + *(int *)(f + 0x1C));
    for (k = 0; k < 0x11; k++)
        g_005BA76C[k] = (u8 *)t + t[k * 2];
    g_005BA7B0_SET(f + *(int *)(f + 0x24));
    g_005BA7B4_SET(f + *(int *)(f + 0x2C));
    g_005BA7BC = 0x40;
    g_005BA7B8_SET(f + *(int *)(f + 0x34));
}
