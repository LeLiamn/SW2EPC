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

u32 func_001D6BD0(void *out, u32 cur, u8 t, u8 s);

/* Reads the command's next argument into `out`. */
#define ARG(p, out) do {                                                \
    u8 t_ = *(*(u8 **)((p) + 0x10))++;                                  \
    u8 s_ = *(*(u8 **)((p) + 0x14))++;                                  \
    *(u32 *)((p) + 0xC) = func_001D6BD0((out), *(u32 *)((p) + 0xC), t_, s_); \
} while (0)

/* The player's draw flags for event models. */
#define PLAYER_FLAGS(f) (g_0045D3E0 == 0 ? (f) | 0x40 : g_0045D3E0 == 1 ? (f) | 0x80 : (f))

u8 *func_001D78D0(u16 k);
u8 *func_001D7870(u16 k);
u8 *func_001E17E0(u16 k);
u8 *func_0014F810(u8 *m, u8 k);
u8 *func_001C7DB0(u16 k, u8 *part, u32 f);
u8 *func_001C8810(u16 k, u8 *m, u16 a, u32 f);
u8 *func_001C7F30(u16 k, u8 *o, int a, u32 f);
u8 *func_001C8340(u16 k, u8 *m, int a, u32 f);
void func_001C8CF0(int k);
void func_001C8A00(void);
u64 *func_00105190(void);
u64 *func_00105410(void);
void func_001E2100(void);
void func_001E1A20(u32 *e, int x);
void func_001D7670(u8 *cam);
void func_001D8E50(u32 *e);
void func_001DB8A0(u32 *e);
void func_00272C80(u32 *e);
void func_001D7470(float dt);
void func_001E2360(float dt, u32 *e);
void func_001D8EC0(float dt, u32 *e);
void func_00272C60(float dt, u32 *e);
void func_001DADC0(u32 *e);
void func_0022E5D0(void);
void func_00191240(int k);
void func_00195C60(void);
void func_00195CE0(void);
void func_001F5150(void);
void func_001F5260(void);
void func_001E29C0(u32 *e, int k);
void func_002E5E10(int a, int b);
void func_001D8EF0(u32 *e, int k);
void func_001DB6B0(u32 *e);
void func_0017A400(int k);
void func_0022ECD0(int k);
int func_0032F780(void);
int func_0032F090(int v);
u32 func_00190D50(void);
int func_001934E0(u32 k);
int func_001F2B70(u8 *u);
int func_00190B90(u8 *a, u8 *b);
void func_00190C00(u8 *a, int b);

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
    m = func_001E17E0(a);
    if (m != 0 && o != 0) {
        u8 *part = func_0014F810(m, (u8)d);

        SP_LIST = 0xB;
        if (f == 0)
            *(u8 **)(o + 0x14) = func_001C7DB0(g_0040C940[b], part, PLAYER_FLAGS(g_0040C9F0[c]));
        else
            *(u8 **)(o + 0x18) = func_001C8810(g_0040C940[b], m, d, PLAYER_FLAGS(g_0040C9F0[c]));
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
    m = func_001E17E0(a);
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
    q = func_00105190();
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
    q = func_00105410();
    q[3] = 0x3F80000080000000ULL;
    q[4] = 0xFFFE79007000ULL;
    q[5] = 0xFFFE7A809000ULL;
    p = SP_PKT;
    p[0] = 0x30000003;
    p[1] = (u32)q;
    p[2] = 0x13000000;
    p[3] = 0x51000003;
    SP_PKT = p + 4;
    q = func_00105410();
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
    func_001D8E50(e);
    func_001DB8A0(e);
    func_00272C80(e);
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
    func_001D8EC0(*dt, e);
    func_00272C60(*dt, e);
    if (f[0x10] < 0.0f)
        f[0x10] = 0.0f;
    else
        f[0x10] += *dt;
    func_001DADC0(e);
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
        func_001D8EF0(e, 0);
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
        func_001D8EF0(e, b);
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
        *(int *)(p + 0x34) = func_001934E0(idx);
        *(int *)(p + 0x34) = func_001F2B70(p + 0x30);
        *(int *)(p + 0x3C) = 0;
    }
}

/* 0x001D9A40, 0x68 bytes. */
void func_001D9A40(u8 *p)
{
    if (func_00190B90(p + 0x30, g_0073C460 + g_0073C79D * 0x10) == 0)
        func_00190C00(p + 0x30, 0);
    *(int *)(p + 0x2C) = 0;
    *(int *)(p + 0x34) = func_001F2B70(p + 0x30);
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
