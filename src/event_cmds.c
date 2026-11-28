/*
 * event_cmds.c - event scene commands between 0x001D8170 and 0x001D9C7C. A command reads its
 * arguments from the event reader `p` (+4 the file, +0xC the cursor, +0x10 the argument types,
 * +0x14 their sizes) through func_001D6BD0. Also the event scene's frame and its letterbox.
 * Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EVENT_CMDS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern int g_0045D3E0;                   /* (small data) the player */
extern int g_0045D470;
extern u8 *g_0045D2C0;                   /* (small data) the camera */
extern u8 g_00730570[2][0x240];          /* the players' cameras */
extern u8 g_00730730[];
extern int g_0073C790;                   /* the event file */
extern u8 g_0073C7A4, g_0073C79D;
extern u8 g_0073C460[];
extern u8 *g_0073C7B0[0x34F];            /* the event file cache */
extern u8 *g_0072C870[];                 /* the loaded model files */
extern u16 g_0040C940[];                 /* event model -> model file */
extern u32 g_0040C9F0[];                 /* event model flags */
extern int g_0040CAA0[0x22];
extern u8 *g_005BA6A0;

#define SP_LIST (*(int *)0x70000D60)
#define SP_PKT (*(u32 **)0x70000158)
#define FL38(o) (*(u32 *)((o) + 0x38))

/* Reads the command's next argument into `out`. */
#define ARG(p, out) do {                                                \
    u8 t_ = *(*(u8 **)((p) + 0x10))++;                                  \
    u8 s_ = *(*(u8 **)((p) + 0x14))++;                                  \
    *(u32 *)((p) + 0xC) = func_001D6BD0((unsigned int *)((out)), (unsigned int *)PS2_PTR(*(u32 *)((p) + 0xC)), t_, s_); \
} while (0)

/* The player's draw flags for event models. */
#define PLAYER_FLAGS(f) (g_0045D3E0 == 0 ? (f) | 0x40 : g_0045D3E0 == 1 ? (f) | 0x80 : (f))

u8 *func_001D78D0(u16 k);
u8 *func_001D7870(u16 k);
u8 *func_0014F810(u8 *m, u8 k);
u8 *func_001C7DB0(u16 k, u8 *part, u32 f);
u8 *func_001C7F30(u16 k, u8 *o, int a, u32 f);
void func_001C8CF0(int k);
void func_001E2100(void);
void func_001E1A20(u32 *e, int x);
void func_001D7670(u8 *cam);
void func_001D7470(float dt);
void func_001E2360(float dt, u32 *e);
void func_001DADC0(u8 *e);
void func_0022E5D0(void);
void func_001E29C0(u32 *e, int k);
void func_001DB6B0(u32 *e);
void func_0022ECD0(int k);

/* 0x001D8170, 0x25C bytes. Attaches model `b` to part `d` of event actor `a` (or to the actor
 * itself), as event object `e`. */
void func_001D8170(u8 *p)
{
    u16 a, b, c, d, e;
    short f;
    u8 *o, *m;

    ARG(p, &a);
    ARG(p, &b);
    ARG(p, &c);
    ARG(p, &d);
    ARG(p, &e);
    ARG(p, &f);
    o = func_001D78D0(e);
    m = (u8 *)PS2_PTR(func_001E17E0(a));
    if (m != 0 && o != 0) {
        u8 *part = func_0014F810(m, (u8)d);

        SP_LIST = 0xB;
        if (f == 0)
            *(u8 **)(o + 0x14) = func_001C7DB0(g_0040C940[b], part, PLAYER_FLAGS(g_0040C9F0[c]));
        else
            *(u8 **)(o + 0x18) = (u8 *)PS2_PTR(func_001C8810(g_0040C940[b], PS2_ADDR(m), d, PLAYER_FLAGS(g_0040C9F0[c])));
    }
}

/* 0x001D83D0, 0xB4 bytes. Drops event object `a`'s models. */
void func_001D83D0(u8 *p)
{
    u16 a;
    u8 *o, *m;
    int k;

    ARG(p, &a);
    o = func_001D7870(a);
    if (o == 0)
        return;
    for (k = 0; k < 3; k++) {
        m = *(u8 **)(o + 0x14 + k * 4);
        if (m != 0) {
            FL38(m) |= 8;
            *(u8 **)(o + 0x14 + k * 4) = 0;
        }
    }
}

/* 0x001D8490, 0xF4 bytes. Registers a model embedded in event file 0xB6. */
void func_001D8490(u8 *p)
{
    u16 a;
    int b;
    u8 **slot;

    if (g_0073C790 != 0xB6)
        return;
    ARG(p, &a);
    ARG(p, &b);
    a = g_0040C940[a];
    slot = &g_0072C870[a];
    if (*slot == 0 && a < 0x18B) {
        *slot = *(u8 **)(p + 4) + b + 4;
        func_001C8CF0(a);
    }
}

/* 0x001D8940, 0x80 bytes. Draws `n` frames at once. */
void func_001D8940(u8 *p)
{
    u16 n;
    u32 k;

    ARG(p, &n);
    for (k = 0; k < n; k++)
        func_001C8A00();
}

/* 0x001D89C0, 0x288 bytes. Places event object `e` at part `d` of actor `a` with model `b`. */
void func_001D89C0(u8 *p)
{
    u16 a, b, c, e;
    u8 d[2];
    short f;
    u8 *o, *m;

    ARG(p, &a);
    ARG(p, &b);
    ARG(p, &c);
    ARG(p, d);
    ARG(p, &e);
    ARG(p, &f);
    o = func_001D78D0(e);
    m = (u8 *)PS2_PTR(func_001E17E0(a));
    if (m != 0 && o != 0) {
        u8 *part = func_0014F810(m, d[0]);
        u32 *q = (u32 *)o;

        q[4] = (u32)part;
        q[0] = *(u32 *)(part + 0x30);
        q[1] = *(u32 *)(part + 0x34);
        q[2] = *(u32 *)(part + 0x38);
        q[3] = *(u32 *)(part + 0x3C);
        ((float *)q)[1] = *(float *)(p + 0x34) - 1.0f;
        SP_LIST = 0xB;
        if (f == 0)
            q[5] = (u32)func_001C7F30(g_0040C940[b], o, 0, PLAYER_FLAGS(g_0040C9F0[c]));
        else
            q[7] = (u32)func_001C8340(g_0040C940[b], o, 0, PLAYER_FLAGS(g_0040C9F0[c]));
        o[0x27] = 2;
    }
}

/* 0x001D8C50, 0x15C bytes. A model seen through the player's own camera. */
void func_001D8C50(u8 *p)
{
    u16 a, b, c;
    u8 *o;
    u32 f0, f;

    ARG(p, &a);
    ARG(p, &b);
    ARG(p, &c);
    o = func_001D78D0(c);
    f0 = g_0040C9F0[b];
    SP_LIST = 0xC;
    f = f0 | 0x80024;
    if (o != 0) {
        if (g_0045D3E0 == 0)
            f = f0 | 0x80064;
        else if (g_0045D3E0 == 1)
            f = f0 | 0x800A4;
        *(u8 **)(o + 0x1C) = func_001C8340(g_0040C940[a], g_00730730 + g_0045D3E0 * 0x240, 0, f);
    }
    SP_LIST = 0xB;
}

/* 0x001D8DD0, 0x5C bytes. */
void func_001D8DD0(u8 *p)
{
    u8 v[2];

    ARG(p, v);
    g_0073C7A4 = v[0];
}

/* 0x001D8F90, 0x20C bytes. The letterbox (two black bands). */
void func_001D8F90(void)
{
    u32 *p = SP_PKT;
    u64 *q;

    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0x13000000;
    p[3] = 0;
    SP_PKT = p + 4;
    q = (u64 *)(func_00105190());
    q[2] = 0x8000000044ULL;
    q[3] = 0x43;
    q[4] = 0x3000D;
    q[5] = 0x48;
    q[6] = 0;
    q[7] = 9;
    q[8] = 0x8000008001ULL;
    q[9] = 0x3B;
    p = SP_PKT;
    p[0] = 0x30000005;
    p[1] = (u32)q;
    p[2] = 0x13000000;
    p[3] = 0x51000005;
    SP_PKT = p + 4;
    q = (u64 *)(func_00105410());
    q[3] = 0x3F80000080000000ULL;
    q[4] = 0xFFFE79007000ULL;
    q[5] = 0xFFFE7A809000ULL;
    p = SP_PKT;
    p[0] = 0x30000003;
    p[1] = (u32)q;
    p[2] = 0x13000000;
    p[3] = 0x51000003;
    SP_PKT = p + 4;
    q = (u64 *)(func_00105410());
    q[3] = 0x3F80000080000000ULL;
    q[4] = 0xFFFE84807000ULL;
    q[5] = 0xFFFE87009000ULL;
    p = SP_PKT;
    p[0] = 0x30000003;
    p[1] = (u32)q;
    p[2] = 0x13000000;
    p[3] = 0x51000003;
    SP_PKT = p + 4;
}

/* 0x001D91F0, 0x84 bytes, matching. The event scene's actors' frame. */
void func_001D91F0(u32 *e, int x)
{
    if ((*e & 1) == 0)
        return;
    func_001E2100();
    func_001E1A20(e, x);
    func_001D7670(g_00730570[g_0045D3E0]);
    func_001D8E50((unsigned char *)(e));
    func_001DB8A0((unsigned char *)(e));
    func_00272C80((unsigned char *)(e));
}

/* 0x001D93B0, 0xD8 bytes. The event scene's time; whether it goes on. */
int func_001D93B0(u32 *e, float *dt)
{
    float *f = (float *)e;

    if ((*e & 1) == 0)
        return 0;
    g_0045D2C0 = g_00730570[g_0045D3E0];
    func_001D7470(*dt);
    func_001E2360(*dt, e);
    func_001D8EC0(*dt, (unsigned char *)(e));
    func_00272C60(*dt, (unsigned char *)(e));
    if (f[0x10] < 0.0f)
        f[0x10] = 0.0f;
    else
        f[0x10] += *dt;
    func_001DADC0((u8 *)e);
    return f[0x10] <= f[0x12];
}

/* 0x001D9490, 0x178 bytes. Draws the event scene (`k`: 0 full screen, 1 or 2 a player's half). */
void func_001D9490(u32 *e, int k)
{
    int a = 0, b = 0;

    g_0045D2C0 = g_00730570[g_0045D3E0];
    if (k == 1) {
        a = 2;
        b = 0;
    } else if (k == 2) {
        a = 3;
        b = 1;
    }
    if (k == 0) {
        func_0022E5D0();
        func_00191240(1);
        func_00195C60();
        func_00195CE0();
        func_001F5150();
        func_001F5260();
        func_001E29C0(e, 0);
        func_002E5E10(0, 0);
        func_001D8EF0(PS2_ADDR(e), 0);
        func_001DB6B0(e);
    } else {
        func_0017A400(b);
        func_0022ECD0(b);
        func_0017A400(b);
        g_0045D470 = b;
        func_00191240(a);
        func_00195C60();
        func_00195CE0();
        func_001F5150();
        func_001F5260();
        func_001E29C0(e, b);
        func_002E5E10(b, 0);
        func_001D8EF0(PS2_ADDR(e), b);
    }
    if (g_0073C790 == 0xB6 && (*e & 4) == 0)
        func_001D8F90();
}

/* 0x001D96E0, 0x6C bytes. Clears the event file cache. */
void func_001D96E0(void)
{
    u32 k;

    for (k = 0; k < 0x34F; k++)
        g_0073C7B0[k] = 0;
}

/* 0x001D9850, 0x1E8 bytes. Moves the camera's target (skipped on some maps' other routes). */
void func_001D9850(u8 *p)
{
    int v = func_0032F780();
    u32 x, z, ang, idx, cond;

    ARG(p, &x);
    ARG(p, &z);
    ARG(p, &ang);
    ARG(p, &idx);
    ARG(p, &cond);
    if ((v != 0xC && v != 0xD && v != 0xE && v != 0x14) || cond < 0x50 || cond > 0x61
        || cond - 0x50 == (u32)func_0032F090(v)) {
        *(u32 *)(p + 0x30) = x;
        *(u32 *)(p + 0x38) = z;
        *(u32 *)(p + 0x2C) = ang;
        if (func_00190D50() <= idx)
            idx = func_00190D50();
        *(float *)(p + 0x34) = func_001934E0(idx);
        *(float *)(p + 0x34) = func_001F2B70(p + 0x30);
        *(int *)(p + 0x3C) = 0;
    }
}

/* 0x001D9A40, 0x68 bytes. */
void func_001D9A40(u8 *p)
{
    if (func_00190B90((unsigned int *)(p + 0x30), g_0073C460 + g_0073C79D * 0x10) == 0)
        func_00190C00((unsigned int *)(p + 0x30), 0);
    *(int *)(p + 0x2C) = 0;
    *(float *)(p + 0x34) = func_001F2B70(p + 0x30);
    *(int *)(p + 0x3C) = 0;
}

/* 0x001D9AB0, 0x10C bytes. Sets a position and an angle (in degrees). */
void func_001D9AB0(u8 *p)
{
    ARG(p, p + 0x30);
    ARG(p, p + 0x34);
    ARG(p, p + 0x38);
    ARG(p, p + 0x2C);
    *(float *)(p + 0x2C) = *(float *)(p + 0x2C) * 3.1415927f / 180.0f;
    *(int *)(p + 0x3C) = 0;
}

/* 0x001D9BC0, 0xBC bytes. Officer `o`'s event motion set. */
int func_001D9BC0(int o)
{
    int t[0x22], k;
    u8 b = g_005BA6A0[o * 0x2C + 6];

    for (k = 0; k < 0x22; k++)
        t[k] = g_0040CAA0[k];
    if (b < 0x22)
        return t[b];
    switch (b) {
    case 0x36:
    case 0x37:
    case 0x38:
        return 2;
    default:
        return 0;
    }
}

extern u8 *g_0045D3F8[2];                /* (small data) the players' item model lists */
extern u8 g_00730D10[];
extern u8 g_00730DA0[3][0x10];           /* the effect pairs */
extern u8 g_0073C79B[];

float func_001D6C70(u8 *c);
int func_0032F420(u16 k);
void func_002723B0(u8 *e, int k, int a);
void func_001DC040(void);
void func_002E9840(u8 *p);

/* The next command of event `e` (file + its offset). */
#define EV_SEEK(e, c) do {                                              \
    *(u8 **)((e) + 8) = (c);                                            \
    *(u8 **)((e) + 0xC) = (c) + (c)[(c)[6] + 7] + 7;                    \
    *(u8 **)((e) + 0x10) = (c) + 7;                                     \
    *(u8 **)((e) + 0x14) = (c) + (c)[6] + 8;                            \
} while (0)

/* Tests the word at file offset `off` against the event's value (mode +0x50: 0 bits, 1 equal). */
#define EV_TEST(e, x) ((e)[0x50] == 0 ? *(x) & *(u32 *)((e) + 0x18) :                     \
                       (e)[0x50] == 1 ? *(x) == *(u32 *)((e) + 0x18) : 0)

/* 0x001DA200, 0x140 bytes. Whether every condition of the command holds. */
void func_001DA200(u8 *p)
{
    u32 n = (*(u8 **)(p + 8))[6] / 3, k;
    u8 r = 1;

    for (k = 0; k < n; k = (k + 1) & 0xFF) {
        u16 a, c;
        u32 b;

        ARG(p, &a);
        ARG(p, &b);
        ARG(p, &c);
        if (func_001D9C80(p, a, b, c) != 1) {
            r = 0;
            break;
        }
    }
    p[0x51] = r;
}

/* 0x001DA340, 0x140 bytes. Whether one of them holds. */
void func_001DA340(u8 *p)
{
    u32 n = (*(u8 **)(p + 8))[6] / 3, k;
    u8 r = 0;

    for (k = 0; k < n; k = (k + 1) & 0xFF) {
        u16 a, c;
        u32 b;

        ARG(p, &a);
        ARG(p, &b);
        ARG(p, &c);
        if (func_001D9C80(p, a, b, c) == 1) {
            r = 1;
            break;
        }
    }
    p[0x51] = r;
}

/* 0x001DAD50, 0x68 bytes. Starts event file `f`. */
void func_001DAD50(u32 *e, u8 *f)
{
    u8 *c;

    if (f == 0)
        return;
    e[1] = (u32)f;
    e[2] = (u32)f;
    ((float *)e)[0x12] = 0.5f;
    e[0] |= 1;
    c = (u8 *)e[2];
    e[3] = (u32)(c + c[c[6] + 7] + 7);
    e[4] = (u32)(c + 7);
    e[5] = (u32)(c + c[6] + 8);
}

/* 0x001DADC0, 0xD8 bytes. Runs the commands due (up to a wait not reached or the end). */
void func_001DADC0(u8 *e)
{
    u8 *c = *(u8 **)(e + 8);

    for (;;) {
        if ((signed char)c[4] == -1)
            return;
        if (c[4] == 0 && c[5] == 0 && *(float *)(e + 0x40) < func_001D6C70(c))
            break;
        func_001DA7E0(e);
        c = *(u8 **)(e + 4) + **(int **)(e + 8);
        EV_SEEK(e, c);
        c = *(u8 **)(e + 8);
    }
}

/* 0x001DB0A0, 0xF8 bytes. Jumps after the first of the listed words that passes the test. */
void func_001DB0A0(u8 *p, u32 *x)
{
    u8 i = 0;
    u32 v;

    if ((*(u8 **)(p + 8))[6] == 0)
        return;
    do {
        int off;

        ARG(p, &off);
        x = (u32 *)(*(u8 **)(p + 4) + off);
        v = EV_TEST(p, x);
    } while (v == 0 && (i = i + 1) < (*(u8 **)(p + 8))[6]);
    if (i != (*(u8 **)(p + 8))[6])
        *(u32 **)(p + 0x20) = x + 1;
}

/* 0x001DB1E0, 0xD8 bytes. */
void func_001DB1E0(u8 *p)
{
    u8 a[2];
    int off;
    u32 *x;

    ARG(p, a);
    ARG(p, &off);
    x = (u32 *)(*(u8 **)(p + 4) + off);
    if (EV_TEST(p, x) != 0)
        *(u32 **)(p + 0x24) = x + 1;
}

/* 0x001DB520, 0x138 bytes. Plays officer `b`'s line `c` (and its voice). */
void func_001DB520(u8 *p)
{
    u16 a, b, c;
    int r;

    ARG(p, &a);
    ARG(p, &b);
    ARG(p, &c);
    func_0032FDD0(PS2_ADDR(func_001D9610(func_0032F7D0(func_0032F420(b)), c)), g_00730D10, (unsigned int *)(&r));
    func_002723B0(p, (r - 0xA6) & 0xFFFF, 1);
    *(u8 **)(p + 0x20) = g_00730D10;
    if (r > 0x11CE && r < 0x151E)
        func_001DF1C0((unsigned int *)(p), a, PS2_ADDR(func_001D9670(r)));
}

/* 0x001DBA70, 0x58 bytes. The player's item model shown for `k` (0: none). */
u8 *func_001DBA70(short k)
{
    u8 *r = g_0045D3F8[g_0045D3E0];
    int i = 0;

    while (r[0x17] == 0 || *(short *)(r + 0x14) != k) {
        i++;
        r += 0x18;
        if (i > 3)
            return 0;
    }
    return r;
}

/* 0x001DBB50, 0x70 bytes, matching. */
void func_001DBB50(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        u8 *r = g_0045D3F8[g_0045D3E0] + i * 0x18;

        func_002AD8B0((unsigned char **)(r));
        func_00118850(r, 0x18);
    }
}

/* 0x001DC2B0, 0x7C bytes. Sets up a trail effect. */
void func_001DC2B0(u32 *p)
{
    p[7] = 0x1C;
    p[4] = (u32)func_0020EC50(0x1C0);
    p[5] = (u32)func_0020EC50(p[7] << 4);
    p[0] = 0;
    ((float *)p)[1] = 0.98f;
    p[2] = 0;
    p[3] = 0;
    p[9] = 0x24;
    ((float *)p)[8] = 4.6f;
    p[6] = (u32)func_001DC040;
}

/* 0x001DC330, 0x84 bytes. The three effect pairs of event file 0xB6. */
void func_001DC330(void)
{
    int k;

    if (g_0073C790 != 0xB6)
        return;
    func_001DBCF0();
    for (k = 0; k < 3; k++) {
        u32 *e = (u32 *)g_00730DA0[k];

        e[0] = (u32)func_0020EC50(0x30);
        e[1] = (u32)func_0020EC50(0x30);
        func_001DC2B0((u32 *)e[0]);
        func_001DC2B0((u32 *)e[1]);
    }
}

/* 0x001DC3C0, 0x6C bytes, matching. Draws them. */
void func_001DC3C0(void)
{
    int k;

    for (k = 0; k < 3; k++) {
        u32 *e = (u32 *)g_00730DA0[k];

        if (g_00730DA0[k][0xE] != 0) {
            *(u32 **)(e[0] + 0x28) = e;
            func_002E9840((u8 *)e[0]);
            *(u32 **)(e[1] + 0x28) = e;
            func_002E9840((u8 *)e[1]);
        }
    }
}

/* 0x001DC650, 0x88 bytes. Clears a list of `p[0]` 16-byte records. */
void func_001DC650(u32 *p)
{
    u32 k;

    for (k = 0; k < p[0]; k++) {
        u8 *q = (u8 *)p[1] + k * 0x10;

        *(u32 *)q = 0;
        *(u32 *)(q + 8) = 0;
        *(u32 *)(q + 4) = 0;
        q[0xC] = 0;
        q[0xD] = 0x2E;
        q[0xE] = 0xFF;
        q[0xF] = 0;
    }
}

/* 0x001DCDE0, 0xC4 bytes. An event's actor id: special values for the player, the scene's
 * officers and the force's members. */
u32 func_001DCDE0(u32 v)
{
    v &= 0xFFFF;
    if (v == 1000)
        return g_0045D3E0 == 0 ? 0x41 : 0x42;
    if (v == 0x3E9)
        return g_0073C79B[g_0073C79D];
    if (v == 0x3EA)
        return 0x43;
    if (v == 900)
        return func_0020E310(func_0032F420(0));
    if (v > 0x3B5 && v < 0x3BB)
        return func_0020E310(func_0032F420(v - 0x3B5));
    return v;
}

extern u16 g_0073C794, g_0073C796;       /* the scene's two forces */
extern u8 g_0073C7A2[], g_0073C7A5;
extern u8 *g_0045D3E8;                   /* (small data) the caption buffer */
extern char *g_0042E260[], *g_0042C730[], *g_0043CB80;
extern char g_00428F50[], g_00428F60[], g_00428F70[], g_00428F78[];
extern u8 g_00669D60[];
extern u8 g_00730DE0[2][0x38];
extern float g_0056CCC0, g_0056CCC4;

int func_001204B0(void *buf, const char *fmt, ...);

/* 0x001DB2D0, 0x248 bytes. The caption naming the battle's two forces. */
void func_001DB2D0(u32 *e)
{
    char *army;

    if ((*e & 0x10) == 0)
        return;
    g_0073C794 = func_0019AE90(g_0073C794);
    army = g_0042E260[g_00669D60[0x24E + g_0073C7A2[g_0073C79D]]];
    if (g_0073C7A5 == 0) {
        if (g_0073C794 == g_0073C796)
            func_001204B0(g_0045D3E8, g_00428F78, army, g_0042C730[g_0073C794]);
        else
            func_001204B0(g_0045D3E8, g_00428F70, army, g_0042C730[g_0073C794],
                          g_0042C730[g_0073C796]);
    } else if (g_0073C794 == g_0073C796) {
        func_001204B0(g_0045D3E8, g_00428F60, army, g_0043CB80, g_0042C730[g_0073C794]);
    } else {
        func_001204B0(g_0045D3E8, g_00428F50, army, g_0043CB80, g_0042C730[g_0073C794],
                      g_0042C730[g_0073C796]);
    }
    e[9] = (u32)g_0045D3E8;
}

/* 0x001DB6B0, 0x1F0 bytes. Draws the subtitles (when switched on in the settings). */
void func_001DB6B0(u32 *ev)
{
    u8 *e = (u8 *)ev;
    u8 buf[264];
    int w, h;
    u8 *s;

    if (g_00669D60[0x50] >> 6 == 0)
        return;
    g_0056CCC0 = g_0056CCC4 = 20.0f;
    s = *(u8 **)(e + 0x24);
    if (s != 0) {
        func_00147160(s, buf, 0x200, 0, 0);
        func_001B8920((const char *)(buf), &w, &h);
        func_001B8800((const char *)(buf), (0x200 - w) >> 1,
                      ((((0x330 - (0x1C0 - ((0x330 - h) >> 1))) - h) >> 1 << 9) / 0x280 * 0x1E0)
                          / 0x1C0, 0, h);
    }
    if (*(u8 **)(e + 0x20) != 0) {
        func_00147160(*(u8 **)(e + 0x20), buf, 0x200, 0, 0);
        func_001B8920((const char *)(buf), &w, &h);
        func_001B8800((const char *)(buf), (0x200 - w) >> 1,
                      (s == 0 ? 0 : 4) + (((0x330 - h) >> 1 << 9) / 0x280 * 0x1E0) / 0x1C0, 0,
                      h);   /* not set again by the original: what the first text left */
    }
    g_0056CCC0 = g_0056CCC4 = 16.0f;
}

/* 0x001DC9A0, 0x264 bytes. Allocates the player's particle buffers. */
void func_001DC9A0(void)
{
    u8 *b = g_00730DE0[g_0045D3E0];
    int n = *(int *)(b + 0x34), k;

    if (n == 0)
        return;
    *(void **)(b + 0x00) = func_0020EC50(n << 2);
    *(void **)(b + 0x04) = func_0020EC50(n << 5);
    *(void **)(b + 0x08) = func_0020EC50(n << 4);
    *(void **)(b + 0x0C) = func_0020EC50(n << 2);
    *(void **)(b + 0x10) = func_0020EC50(n << 2);
    *(void **)(b + 0x20) = func_0020EC50(n << 1);
    *(void **)(b + 0x14) = func_0020EC50(n << 2);
    *(void **)(b + 0x18) = func_0020EC50(n << 1);
    *(void **)(b + 0x1C) = func_0020EC50(n);
    *(void **)(b + 0x30) = func_0020EC50(n << 3);
    *(void **)(b + 0x24) = func_0020EC50(n << 2);
    for (k = 0; k < 2; k++)
        *(void **)(b + 0x28 + k * 4) = func_0020EC50(n << 3);
    func_001DC6E0();
}
