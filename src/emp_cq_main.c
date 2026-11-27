/*
 * emp_cq_main.c - the Empire mode's conquest main loop: the game state blocks, loading and
 * leaving, the turn's scene steps, end checks and the notices shown to the player
 * (0x0030CCD0-...). Written so far: from 0x0030CCD0.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. The file was built with the loop unroller on.
 */

#pragma opt_unroll_loops on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define IS_FORCE(f) ((f) >= 0 && (f) < func_0030AB90())

/* A notice to the player (0x007A3BC0, returned by func_0030E2C0). */
typedef struct {
    int kind;                /* +0x000 (-1 = none) */
    int a, b, c;             /* +0x004 */
    int list[0x19F];         /* +0x010 officers (-1 = none) */
    int count;               /* +0x68C */
    int unknown_690;         /* +0x690 */
    int step;                /* +0x694 */
    int phase;               /* +0x698 */
    int unknown_69C;         /* +0x69C */
    int ready;               /* +0x6A0 */
} Notice;

extern Notice g_007A3BC0;
extern int g_007A4270[6];                /* a pending event command (func_0030E0F0) */
extern u8 *g_007A3B98, *g_007A3B9C, *g_007A3BA0;   /* the three game state blocks */
extern u8 g_007B4C40[500], g_007B4010[3000], g_007A4290[0xFCE4];
extern int g_007A3BA8, g_007A3BAC, g_007A3BB0;
extern int g_007B4E48, g_007B4E4C, g_007B4E50;      /* the turn's scene step (+4) */
extern void *g_0045D6B0, *g_0045D6B4, *g_0045D6B8, *g_0045D6BC, *g_0045D6C0;   /* (small data) */
extern void *g_0045D6A4, *g_0045D6A8;    /* (small data) two 0x67C-byte buffers */
extern const char g_004467F8[];          /* "emp_cq_main.c" */
extern const char *g_0043C5EC, *g_0043C5F0;   /* help lines */

int func_0030AB90(void);
int func_0030AFF0(int r);
int func_0030B090(int r);
void func_0030ABC0(void);
int func_002FB3B0(int f);
int func_002F9C90(int f, int g);
int func_002F9060(u32 f);
int func_002F4080(u32 i);
int func_002F3770(u32 i);
int func_002F38F0(u32 i);
int func_002F3E70(u32 i);
int func_002F27D0(u32 i);
int func_002F2840(u32 i);
void func_002F3660(u32 i, int v);
void func_002F4980(u32 i, int k, int v);
void func_002F8C80(void);
void func_002F26F0(void);
int func_002F7D90(int n, int (*keep)(u32, int, int), int a, int b, int c);
int func_002F8160(u32 i, int f);
int func_00327D50(void);
int func_00327C00(void);
u32 func_00327C70(void);
int func_00327B70(int f);
void func_00327750(int n);
void func_00327DC0(int n);
void func_00327710(int n);
int func_00327820(void);
int func_00327900(void);
u32 func_00327140(int a, u32 b);
void *func_0030CCC0(void);
void func_0011ED38(void *to, int value, int size);
void func_0011EB80(void *to, const void *from, int size);
void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
int func_00102960(int value);
void func_00102EC0(void *data);
void *func_00102DB0(int align, int size);
int func_0039E650(int k);
void func_0039EB40(int k);
u8 *func_00390940(void);
float sqrtf(float x);        /* (VU0 vsqrt) */
u32 func_003620E0(int side, int k);
void func_00362110(int side, int k, int v);
void func_00362220(int side, int k, int v);
void func_003621B0(int side, int k, int v);
int func_00362260(int side, int k);
void func_003623E0(int a);
void func_00362550(int b);
int func_00362490(void);
u32 func_00362570(void);
void func_00362630(int side, int v);
void func_002D6890(void);
void func_002D68F0(void);
void func_00374E20(void);
void func_0038C6F0(void);
void func_003907B0(void);
void func_00390780(void);
void func_003A5C40(int k);
void func_003A5FA0(int a, int b, int c, int d);
void func_003A5E20(void);
void func_003A7A10(void);
void func_003A7D90(void);
void func_003DA7F0(void);
void func_003DA850(void);
void func_00375CF0(void);
void func_0039F840(void);
void func_0039F960(void);
void func_003DB120(int k);
void func_003DB1B0(void);
void func_003DC040(void);
void func_003DC080(void);
void func_002FC630(void);
void func_002FC2D0(void);
void func_002FC560(void);
void func_002FC660(void);
void func_003236F0(int a);
void func_001AFFB0(int a);
void func_003BA8C0(int k);
void func_003BAB70(int k);
void func_003BA8F0(int k, int a, int b, int c, int d);
void func_003B6CD0(void);
void func_003A9170(void);
int func_0023A760(int k);
void func_0023A7D0(int k);
void func_0032E8A0(int k, int v);
void func_00330320(int c, int a);
void func_003D32C0(int c);
int func_0032FF00(void);
void func_0032BB70(void);
int func_0032BC30(void);
void func_0032FEF0(int a);
void func_0032F770(int a);
void func_00369A50(void);
void func_0032D150(void);
void func_0037FB60(void *pic, int x, int y, int a, int b);
void func_0039B700(void);
void func_0032D3C0(void *pic);
int *func_003DB900(int k);
void func_00380E80(void *pic, int a, int x, int y);
void func_003D38A0(int a, int x, int y, int b, int c, int d, int e, int f);
void func_001A7DC0(const char *text, int a, int b);
int func_00372580(int i);
void func_0037E480(void *pic, int i, int x, int y, int a, int b, int c, int d);
void func_003DC180(int k, int a, int *out);
void func_002C7310(int a, int x, int y, int w, int h, int b, int c);
void func_00381FF0(void *pic, int a, int y, int i, int on);
void func_0037E9F0(void *pic, int i, int a, int y, int b, int c);
void func_003821E0(void *pic, int sel, int a, int y, u8 *l, int n);
void func_0037E950(void *pic, int i, int a, int y, int b);
int func_003725A0(int k);
void func_003838B0(int a, int b);

int func_0030D150(void);
int func_0030D530(int side);
int func_0030DFA0(void);
void func_0030E090(int s);
void func_0030E100(void);
void func_0030E2D0(void);
void func_0030E200(int v);
void func_0030D8D0(void);
void func_0030DB70(void);
void func_0030EA60(void);
void func_0030EBB0(void);

/* 0x0030CCD0, 0xC bytes. The region table. */
u8 *func_0030CCD0(void)
{
    return g_007A3B98;
}

/* 0x0030CCE0, 0x78 bytes. Clears the three game state blocks (regions, forces, officers). */
void func_0030CCE0(void)
{
    g_007A3B98 = g_007B4C40;
    g_007A3B9C = g_007B4010;
    g_007A3BA0 = g_007A4290;
    func_0011ED38(g_007B4C40, 0, 500);
    func_0011ED38(g_007A3B9C, 0, 3000);
    func_0011ED38(g_007A3BA0, 0, 0xFCE4);
}

/* 0x0030CD60, 0x1C bytes, matching. */
void func_0030CD60(void)
{
    func_0030CCE0();
}

/* 0x0030CD80, 0x104 bytes. Loads the game state from `data` (scenario or save), then resets the
 * officers' per-kind values and the edited officers. */
void func_0030CD80(u8 *data)
{
    int i, k;

    func_0011EB80(g_007A3B98, data, 500);
    func_0011EB80(g_007A3B9C, data + 500, 3000);
    func_0011EB80(g_007A3BA0, data + 0xDAC, 0xFCE4);
    func_0030ABC0();
    func_002F8C80();
    func_002F26F0();
    for (i = 0; i < 0x19F; i++) {
        for (k = 0; k < 0x35; k++)
            func_002F4980(i, k, 1);
    }
    for (i = 400; i < 0x19F; i++) {
        if (func_0039E650(i - 400) != 0)
            func_0039EB40(i - 400);
    }
}

/* 0x0030CE90, 0x60 bytes, matching. Loads scenario `k`'s state (LINKDATA entry 0xA0 + `k`). */
void func_0030CE90(int k)
{
    u8 *d = func_001026D0(1, k + 0xA0, 0, 1, 0, 0, g_004467F8, 0x131);

    func_00102960(1);
    func_0030CD80(d);
    func_00102EC0(d);
}

/* 0x0030CEF0, 0x60 bytes, matching. Loads LINKDATA entry 0xAA for func_00390940's block. */
void func_0030CEF0(void)
{
    void *d = func_001026D0(1, 0xAA, 0, 1, 0, 0, g_004467F8, 0x143);

    *(void **)(func_00390940() + 0x8EC0) = d;
    func_00102960(1);
}

/* 0x0030CF50, 0x1C bytes, matching. */
void func_0030CF50(u8 *data)
{
    func_0030CD80(data);
}

/* 0x0030CF70, 0x1C bytes. */
void func_0030CF70(void)
{
    g_007A3BA8 = 0;
    g_007A3BAC = 0;
    g_007A3BB0 = 0;
}

/* 0x0030CF90, 0x80 bytes. Sets side `side`'s slot `k` to officer `i` (weapon, soldiers, most). */
void func_0030CF90(int side, int k, u32 i)
{
    func_00362110(side, k, func_002F27D0(i));
    func_00362220(side, k, func_002F3770(i));
    func_003621B0(side, k, func_002F38F0(i));
}

/* 0x0030D010, 0x84 bytes. Sets side `side`'s slots from officers `l` (`n`). */
void func_0030D010(int side, u32 *l, int n)
{
    int k;

    for (k = 0; k < n; k++, l++) {
        if (*l < 0x19F)
            func_0030CF90(side, k, *l);
    }
}

/* 0x0030D0A0, 0x20 bytes, matching. Slot 6 (the leader?). */
void func_0030D0A0(int side, u32 i)
{
    func_0030CF90(side, 6, i);
}

/* 0x0030D0C0, 0x1C bytes, matching. */
u32 func_0030D0C0(int side)
{
    return func_003620E0(side, 6);
}

/* 0x0030D0E0, 0x20 bytes, matching. Slot 7. */
void func_0030D0E0(int side, u32 i)
{
    func_0030CF90(side, 7, i);
}

/* 0x0030D100, 0x1C bytes, matching. */
u32 func_0030D100(int side)
{
    return func_003620E0(side, 7);
}

/* 0x0030D120, 0x2C bytes, matching. */
void func_0030D120(int a, int b)
{
    func_003623E0(a);
    func_00362550(b);
}

/* 0x0030D150, 0x1C bytes, matching. The battle's region. */
int func_0030D150(void)
{
    return func_00362490();
}

/* 0x0030D170, 0x5C bytes. The soldiers of side `side`'s six slots. */
int func_0030D170(int side)
{
    int s = 0, k;

    for (k = 0; k < 6; k++)
        s += func_00362260(side, k);
    return s;
}

/* 0x0030D1D0, 0xD4 bytes. A side's strength (0-10): its troops when attacking (`att`), plus the
 * square root of its soldiers in thousands (at most 10), doubled with `bonus`. */
int func_0030D1D0(int att, int bonus, int troops, int soldiers)
{
    int mul, s;

    if (att == 0)
        troops = 0;
    mul = bonus == 0 ? 1 : 2;
    s = (int)sqrtf((float)(soldiers / 1000));
    if (s < 10)
        troops += (int)sqrtf((float)(soldiers / 1000));
    else
        troops += 10;
    mul *= troops;
    return mul > 9 ? 10 : mul;
}

/* 0x0030D2B0, 0xBC bytes. Sets both sides' strengths. */
void func_0030D2B0(void)
{
    u32 v = func_00362570();
    int side;

    for (side = 0; side < 2; side++) {
        int b = func_0030D530(side);
        int t = func_0030B090(func_0030D150());

        func_00362630(side, func_0030D1D0((v < 4) == side, b, t, func_0030D170(side)));
    }
}

/* 0x0030D370, 0x78 bytes. Whether both sides have a leader. */
int func_0030D370(void)
{
    if (func_003620E0(0, 0) < 0x19F && func_003620E0(1, 0) < 0x19F)
        return 1;
    return 0;
}

/* 0x0030D3F0, 0x7C bytes. Whether only side 0 has a leader. */
int func_0030D3F0(void)
{
    if (func_003620E0(0, 0) < 0x19F && func_003620E0(1, 0) > 0x19E)
        return 1;
    return 0;
}

/* 0x0030D470, 0xB8 bytes. Whether side `side` has a busy officer of its leader's force. */
int func_0030D470(int side)
{
    int f = func_002F4080(func_003620E0(side, 0)), k;

    for (k = 0; k < 8; k++) {
        u32 o = func_003620E0(side, k);

        if (o < 0x19F && func_002F4080(o) == f && func_002F3E70(o) != 0)
            return 1;
    }
    return 0;
}

/* 0x0030D530, 0x30 bytes. Whether side `side`'s force has func_00327B70. */
int func_0030D530(int side)
{
    return func_00327B70(func_002F4080(func_003620E0(side, 0))) != 0;
}

/* 0x0030D560, 0x1C bytes, matching. */
int func_0030D560(int side)
{
    return func_0030D470(side);
}

/* 0x0030D580, 0x128 bytes. Loads the battle results from `p`: region flags, officers' records,
 * the force table, then clamps soldiers to their most. */
void func_0030D580(u8 *p)
{
    u8 *g = func_0030CCD0();
    int k;

    for (k = 0; k < 0x19; k++, p += 8, g += 0x14)
        func_0011EB80(g + 0xC, p, 8);
    for (k = 0; k < 0x19F; k++, p += 0x54, g += 0x9C)
        func_0011EB80(g + 0x48, p, 0x54);
    func_0011EB80(func_0030CCC0(), p, 3000);
    for (k = 0; k < 0x19F; k++) {
        if (func_002F2840(k) != 0 && func_002F38F0(k) < func_002F3770(k))
            func_002F3660(k, func_002F38F0(k));
    }
}

/* 0x0030D6B0, 0x114 bytes. Saves the same into `p`, then the player's counts. */
void func_0030D6B0(u8 *p)
{
    u8 *g = func_0030CCD0();
    int k, f;

    for (k = 0; k < 0x19; k++, p += 8, g += 0x14)
        func_0011EB80(p, g + 0xC, 8);
    for (k = 0; k < 0x19F; k++, p += 0x54, g += 0x9C)
        func_0011EB80(p, g + 0x48, 0x54);
    func_0011EB80(p, func_0030CCC0(), 3000);
    f = func_00327D50();
    func_00327750(func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1));
    func_00327DC0(func_002FB3B0(f));
    func_00327710(func_002F9060(f));
}

/* 0x0030D7D0-0x0030D810, 8 bytes each. The loaded picture files. */
void *func_0030D7D0(void) { return g_0045D6B0; }
void *func_0030D7E0(void) { return g_0045D6B4; }
void *func_0030D7F0(void) { return g_0045D6B8; }
void *func_0030D800(void) { return g_0045D6BC; }
void *func_0030D810(void) { return g_0045D6C0; }

/* 0x0030D820, 0x40 bytes, matching. Loads LINKDATA entry 0x81. */
void func_0030D820(void)
{
    g_0045D6B0 = func_001026D0(1, 0x81, 0, 1, 0, 0, g_004467F8, 0x392);
}

/* 0x0030D860, 0x6C bytes, matching. Loads entries 0x81 and 0x39. */
void func_0030D860(void)
{
    g_0045D6B0 = func_001026D0(1, 0x81, 0, 1, 0, 0, g_004467F8, 0x39A);
    g_0045D6B8 = func_001026D0(1, 0x39, 0, 1, 0, 0, g_004467F8, 0x39C);
}

/* 0x0030D8D0, 0x10C bytes, matching. Loads entries 0x81, 0x82, 0x39, 0x36 and 0x37. */
void func_0030D8D0(void)
{
    g_0045D6B0 = func_001026D0(1, 0x81, 0, 1, 0, 0, g_004467F8, 0x3A5);
    func_00102960(1);
    g_0045D6B4 = func_001026D0(1, 0x82, 0, 1, 0, 0, g_004467F8, 0x3A9);
    func_00102960(1);
    g_0045D6B8 = func_001026D0(1, 0x39, 0, 1, 0, 0, g_004467F8, 0x3AD);
    func_00102960(1);
    g_0045D6BC = func_001026D0(1, 0x36, 0, 1, 0, 0, g_004467F8, 0x3B0);
    g_0045D6C0 = func_001026D0(1, 0x37, 0, 1, 0, 0, g_004467F8, 0x3B1);
    func_002D6890();
}

/* 0x0030D9E0, 0x144 bytes, matching. Enters the conquest screens: everything when neither `a` nor `b`,
 * else the lighter set-ups. */
void func_0030D9E0(int a, int b)
{
    func_00374E20();
    func_0030E100();
    func_0030E2D0();
    func_0038C6F0();
    g_0045D6A4 = func_00102DB0(0x10, 0x67C);
    g_0045D6A8 = func_00102DB0(0x10, 0x67C);
    g_0045D6B0 = 0;
    g_0045D6B4 = 0;
    g_0045D6B8 = 0;
    g_0045D6BC = 0;
    g_0045D6C0 = 0;
    if (a == 0 && b == 0) {
        func_0030D8D0();
        func_003907B0();
        func_003A5C40(func_00327C00());
        func_003A5FA0(0, 1, 1, 1);
        func_003A7A10();
        func_003A7D90();
        func_003DA7F0();
        func_00375CF0();
        func_0039F840();
        func_0039F960();
        func_003DB120(10);
        func_003DC040();
    } else {
        if (a != 0)
            func_0030D820();
        if (b != 0)
            func_0030D860();
        func_003907B0();
        func_0039F840();
        func_003DB120(10);
        func_003DC040();
    }
}

/* 0x0030DB30, 0x1C bytes, matching. */
void func_0030DB30(int a)
{
    func_0030D9E0(a, 0);
}

/* 0x0030DB50, 0x20 bytes, matching. */
void func_0030DB50(void)
{
    func_0030D9E0(0, 1);
}

/* Frees a loaded file kept in `p`. */
#define FREE_FILE(p) do {               \
        if ((p) != 0) {                 \
            func_00102EC0(p);           \
            (p) = 0;                    \
        }                               \
    } while (0)

/* 0x0030DB70, 0x94 bytes, matching. Frees the picture files. */
void func_0030DB70(void)
{
    func_002D68F0();
    FREE_FILE(g_0045D6C0);
    FREE_FILE(g_0045D6BC);
    FREE_FILE(g_0045D6B8);
    FREE_FILE(g_0045D6B4);
    FREE_FILE(g_0045D6B0);
}

/* 0x0030DC10, 0xFC bytes, matching. Leaves the conquest screens (`light` for the lighter set-up). */
void func_0030DC10(int light)
{
    func_003DB1B0();
    func_003DC080();
    if (light == 0) {
        func_003DA850();
        func_003A5E20();
        func_00390780();
        func_0030DB70();
    } else {
        func_00390780();
        FREE_FILE(g_0045D6B8);
        FREE_FILE(g_0045D6B4);
        FREE_FILE(g_0045D6B0);
    }
    FREE_FILE(g_0045D6A8);
    FREE_FILE(g_0045D6A4);
    func_00374E20();
    func_0030E100();
    func_0030E2D0();
    func_0038C6F0();
}

/* 0x0030DD10, 0x58 bytes. */
void func_0030DD10(int a)
{
    if (g_007B4E4C == 0x15)
        func_002FC630();
    else
        func_002FC2D0();
    func_003236F0(a);
    g_007B4E48 = 0;
}

/* 0x0030DD70, 0x34 bytes. 8 when both sides have a leader, else 0. */
int func_0030DD70(void)
{
    return func_0030D370() != 0 ? 8 : 0;
}

/* 0x0030DDB0, 0x158 bytes. Next turn step: an ending (6 win, 7 time out, 10 loss) shows its
 * event; else the step after the current one (wrapping after 0x1D). */
void func_0030DDB0(void)
{
    int end = func_0030DFA0();

    if (end == 6 || end == 7 || end == 10) {
        func_001AFFB0(0);
        func_003BA8C0(end);
        func_003BAB70(4);
        if (end == 7)
            func_003BA8F0(0x29, func_00327820(), -1, -1, -1);
        else if (end == 10)
            func_003BA8F0(0x2B, func_00327820(), -1, -1, -1);
        func_003B6CD0();
        g_007B4E4C = 0x1E;
        return;
    }
    func_0030E090(g_007B4E4C + 1);
    if (g_007B4E4C > 0x1D) {
        g_007B4E4C = 0;
        func_003A9170();
    }
    if (g_007B4E4C == 0x10) {
        func_0039F960();
        if (func_0023A760(0xC) != 0) {
            func_00102960(1);
            func_0023A7D0(0xC);
        }
    }
}

/* 0x0030DF10, 0x88 bytes. Whether every region is the player's or at war with it. */
int func_0030DF10(void)
{
    int p = func_00327D50(), r;

    for (r = 0; r < func_0030AB90(); r++) {
        int g = func_0030AFF0(r);

        if (g != p && func_002F9C90(p, g) != 3)
            return 0;
    }
    return 1;
}

/* 0x0030DFA0, 0xE8 bytes. The game's end: 10 the player has no region left, 6 it holds them all
 * (or all others are at war with it), 7 time is up (2000 turns, or 200 with func_00327900). */
int func_0030DFA0(void)
{
    int end = 0, p = func_00327D50(), n = func_002FB3B0(p);

    if (n == 0)
        end = 10;
    else if (n == func_0030AB90())
        end = 6;
    else if (func_0030DF10() != 0)
        end = 6;
    if (end == 0) {
        u32 t = func_00327140(func_00327C00(), func_00327C70());

        if (t > 2000 || (func_00327900() != 0 && func_00327C70() > 200))
            end = 7;
    }
    return end;
}

/* 0x0030E090, 0x58 bytes. Sets the turn step (0-0x20); steps 0x10 and 0x15 set up their menus. */
void func_0030E090(int s)
{
    if (s >= 0x21)
        return;
    g_007B4E4C = s;
    if (s == 0x10)
        func_002FC560();
    if (s == 0x15)
        func_002FC660();
}

/* 0x0030E0F0, 0xC bytes, matching. */
int *func_0030E0F0(void)
{
    return g_007A4270;
}

/* 0x0030E100, 0x38 bytes, matching. Clears the pending event command. */
void func_0030E100(void)
{
    g_007A4270[0] = -1;
    g_007A4270[1] = -1;
    g_007A4270[2] = -1;
    g_007A4270[3] = -1;
    g_007A4270[4] = -1;
    g_007A4270[5] = 0;
}

/* 0x0030E140, 0xA4 bytes. Starts event command `c` (officer `i`, values `a` and `b`). */
void func_0030E140(int c, u32 i, int a, int b)
{
    g_007A4270[0] = c;
    g_007A4270[2] = a;
    g_007A4270[3] = b;
    g_007A4270[4] = -1;
    g_007A4270[5] = 1;
    g_007A4270[1] = i;
    func_0032E8A0(0, i);
    func_0032E8A0(1, a);
    func_0032E8A0(2, b);
    func_00330320(c, 0);
    func_003D32C0(c);
}

/* 0x0030E1F0, 0xC bytes, matching. The pending command's state (0 none, 1 running, 2 answered). */
int func_0030E1F0(void)
{
    return g_007A4270[5];
}

/* 0x0030E200, 0xC bytes, matching. */
void func_0030E200(int v)
{
    g_007A4270[5] = v;
}

/* 0x0030E210, 0x30 bytes, matching. */
void func_0030E210(void)
{
    if (func_0032FF00() == 3)
        func_0032BB70();
}

/* 0x0030E240, 0x80 bytes, matching. Runs the pending command until it answers. */
void func_0030E240(void)
{
    int r = 5;

    func_0030E0F0();
    if (func_0032FF00() == 3)
        r = func_0032BC30();
    if (r != 5) {
        func_0032FEF0(0);
        func_0032F770(-1);
        func_00369A50();
        func_0032D150();
        func_0032FEF0(0);
        func_0030E200(2);
    }
}

/* 0x0030E2C0, 0xC bytes, matching. The notice. */
Notice *func_0030E2C0(void)
{
    return &g_007A3BC0;
}

/* 0x0030E2D0, 0xC0 bytes, matching. Clears the notice. */
void func_0030E2D0(void)
{
    int k;

    g_007A3BC0.kind = -1;
    g_007A3BC0.a = -1;
    g_007A3BC0.b = -1;
    g_007A3BC0.c = -1;
    g_007A3BC0.unknown_690 = -1;
    g_007A3BC0.step = 0;
    g_007A3BC0.phase = 0;
    g_007A3BC0.ready = 0;
    g_007A3BC0.count = 0;
    g_007A3BC0.unknown_69C = 0;
    for (k = 0; k < 0x19F; k++)
        g_007A3BC0.list[k] = -1;
}

/* 0x0030E390, 0x138 bytes. Shows notice `kind` (values `a`-`c`, officers `l` (`n`) when given). */
void func_0030E390(int kind, int a, int b, int c, int *l, int n)
{
    int k;

    g_007A3BC0.step = 0;
    g_007A3BC0.unknown_690 = -1;
    g_007A3BC0.phase = 0;
    g_007A3BC0.ready = 1;
    g_007A3BC0.unknown_69C = 0;
    g_007A3BC0.kind = kind;
    g_007A3BC0.a = a;
    g_007A3BC0.b = b;
    g_007A3BC0.c = c;
    if (l != 0) {
        g_007A3BC0.count = n;
        for (k = 0; k < n; k++)
            g_007A3BC0.list[k] = l[k];
    }
}

/* 0x0030E4D0, 0xC bytes, matching. */
int func_0030E4D0(void)
{
    return g_007A3BC0.ready;
}

/* 0x0030E4E0, 0xC bytes, matching. */
void func_0030E4E0(int v)
{
    g_007A3BC0.ready = v;
}

/* 0x0030E4F0, 0x0030E500, 0x0030E510, 8 bytes each. Empty notice steps. */
void func_0030E4F0(void)
{
}

void func_0030E500(void)
{
}

void func_0030E510(void)
{
}

/* 0x0030E520, 0x34 bytes, matching. Draws the notice picture `a` / `b` at (0xA0, 0x60). */
void func_0030E520(void)
{
    Notice *n = func_0030E2C0();

    func_0037FB60(g_0045D6B0, 0xA0, 0x60, n->a, n->b);
}

/* 0x0030E560, 8 bytes, matching. */
void func_0030E560(void)
{
}

/* 0x0030E570, 0x1C bytes, matching. */
void func_0030E570(void)
{
    func_0039B700();
}

/* 0x0030E590, 0x1C bytes, matching. */
void func_0030E590(void)
{
    func_0039B700();
}

/* 0x0030E5B0, 0x3C bytes, matching. Draws the picture file in phase 4. */
void func_0030E5B0(void)
{
    if (func_0030E2C0()->phase == 4)
        func_0032D3C0(func_0030D7D0());
}

/* 0x0030E5F0, 0x3C bytes, matching. The same. */
void func_0030E5F0(void)
{
    if (func_0030E2C0()->phase == 4)
        func_0032D3C0(func_0030D7D0());
}

/* 0x0030E630, 0xCC bytes. Draws notice picture `a` (style 4, 0xC with `b`) at position 3, in
 * steps 3 and 4. */
void func_0030E630(void)
{
    Notice *n = func_0030E2C0();
    int a = n->a, b = n->b, *pos = func_003DB900(3), style;

    style = b == 0 ? 4 : 0xC;
    if (n->step == 4)
        func_0037FB60(func_0030D7D0(), pos[0], pos[1], a, style);
    else if (n->step == 3)
        func_0037FB60(func_0030D7D0(), pos[0], pos[1], a, style);
}

/* 0x0030E700, 8 bytes, matching. */
void func_0030E700(void)
{
}

/* 0x0030E710, 0x7C bytes. Draws value `a` at position 2 in steps 0-2. */
void func_0030E710(void)
{
    Notice *n = func_0030E2C0();
    int *pos = func_003DB900(2), s = n->step;

    if (s == 2 || s == 1 || s == 0)
        func_00380E80(func_0030D7D0(), n->a, pos[0], pos[1]);
}

/* 0x0030E790, 0x84 bytes. Draws region `a` at position 0xE in steps 0-1, with a help line. */
void func_0030E790(void)
{
    Notice *n = func_0030E2C0();
    int *pos = func_003DB900(0xE);

    if (n->step == 1 || n->step == 0) {
        func_003D38A0(n->a, pos[0], pos[1], 0, pos[2], pos[3], pos[4], 1);
        func_001A7DC0(g_0043C5EC, 0x80, 1);
    }
}

/* 0x0030E820, 0x98 bytes. Draws officer `a`'s portrait at (0xB4, 0x4A) in steps 0-1. */
void func_0030E820(void)
{
    Notice *n = func_0030E2C0();
    int *pos = func_003DB900(0xF);

    if (n->step == 1 || n->step == 0)
        func_0037E480(func_0030D7D0(), n->a, 0xB4, 0x4A, pos[4], func_00372580(n->a), 1, 1);
}

/* 0x0030E8C0, 0x34 bytes, matching. */
void func_0030E8C0(void)
{
    if (func_0030E2C0()->step == 7)
        func_0039B700();
}

/* 0x0030E900, 0x15C bytes. Draws officer `list[a]`'s portrait at (0xB4, 0x4A) in steps 0-2
 * (with a help line in step 1). */
void func_0030E900(void)
{
    Notice *n = func_0030E2C0();
    int *pos = func_003DB900(8), s = n->step, i = n->list[n->a];

    if (s == 1) {
        func_0037E480(func_0030D7D0(), i, 0xB4, 0x4A, pos[4], func_00372580(i), 0, 0);
        func_001A7DC0(g_0043C5EC, 0x80, 1);
    } else if (s == 2) {
        func_0037E480(func_0030D7D0(), i, 0xB4, 0x4A, pos[4], func_00372580(i), 0, 0);
    } else if (s == 0) {
        func_0037E480(func_0030D7D0(), i, 0xB4, 0x4A, pos[4], func_00372580(i), 0, 0);
    }
}

/* 0x0030EA60, 0x144 bytes. Draws the notice's officer list (one row each, `b` selected) and the
 * selected officer's portrait. */
void func_0030EA60(void)
{
    Notice *n = func_0030E2C0();
    int cnt = n->count, pos[8], box, k, y;

    func_003DC180(0x10, 0, pos);
    func_002C7310(pos[0], 0x58, 0, 0xA6, cnt * 0x18 + 0x10, 0x80, 1);
    box = pos[0];
    for (k = 0, y = 0x60; k < cnt; k++, y += 0x18)
        func_00381FF0(func_0030D7D0(), box, y, n->list[k], n->b == k);
    func_003DC180(0x11, 0, pos);
    func_0037E9F0(func_0030D7D0(), n->list[n->b], pos[0], 0x68, 0x80, 1);
    func_001A7DC0(g_0043C5F0, 0x80, 1);
    func_003838B0(func_003725A0(0x60), 1);
}

/* 0x0030EBB0, 0x19C bytes. The same as a compact list (officer numbers as bytes). */
void func_0030EBB0(void)
{
    Notice *n = func_0030E2C0();
    int cnt = n->count, pos[6], k;
    u8 l[8];

    for (k = 0; k < cnt; k++)
        l[k] = n->list[k];
    func_003DC180(0x10, 0, pos);
    func_003821E0(func_0030D7D0(), n->b, pos[0], 0x50, l, cnt);
    func_003DC180(0x11, 0, pos);
    func_0037E950(func_0030D7D0(), n->list[n->b], pos[0], 0x68, 0x80);
    func_001A7DC0(g_0043C5F0, 0x80, 1);
    func_003838B0(func_003725A0(0x61), 1);
}

/* 0x0030ED50, 0x70 bytes. In step 1, the officer list (full rows for commands 0x3B-0x59, else
 * compact). */
void func_0030ED50(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 1) {
        if (n->a > 0x3A && n->a < 0x5A)
            func_0030EA60();
        else
            func_0030EBB0();
    }
}

/* The first controller (0x00500700, see scene_config.c). */
typedef struct {
    u8 unknown_00[0x4C];
    unsigned short pressed;  /* +0x4C */
    unsigned short held;     /* +0x4E */
    u8 unknown_50[0x14];
    u8 ready;                /* +0x64 bit 0 */
    u8 connected;            /* +0x65 bit 0 */
    u8 unknown_66[0x22];
} PadState;

extern PadState g_00500700[2];
#define pad1_ready() ((g_00500700[0].ready & 1) ? (g_00500700[0].connected & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_00500700[0].pressed : 0))

extern char g_007B4E60[];                /* the message text */
extern const char g_00446808[];          /* "%s" */

void func_0037DAD0(void *pic);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_0039F950(int v);
void func_00376100(int a, int b, int c);
int func_0039B980(void);
const char *func_00390760(int id);
int func_00327CC0(void);
const char *func_00372660(int k);
int func_00327C80(void);
char *func_0030CB80(int v);
const char *func_002F8DB0(int f);
void func_001204B0(char *out, const char *format, ...);   /* sprintf */
void func_00120928(char *to, const char *from);          /* strcpy */
void func_00374EE0(const char *text);
int func_00375B90(void);
int func_00375BF0(void);
int func_0030A030(int f, int to);
void func_002F3CF0(u32 i, int r);
void func_002F8E80(int f, u32 i);
int func_002FB2A0(int f);
void func_00327780(u32 i);
void func_002F43C0(u32 i, int v);
void func_002F4510(u32 i, int v);
void func_00308600(u32 i);
int func_002F5CC0(u32 i);
int func_002F80C0(u32 i, int f);
void func_002F5BE0(u32 i, int r);
int func_00309130(u32 i, int f, int r, int msg);
const char *func_002F2890(u32 i);
u32 *func_002F7B10(void);
int func_002F77A0(u32 i, u32 j);
int func_002F77F0(u32 i, u32 j);
int func_002F78C0(u32 i, u32 j);
int func_002F3DC0(u32 i);
int func_002F7550(u32 i);
int func_002F34E0(u32 i);
int func_002F82F0(u32 i, int f);
int func_002F8340(u32 i, int f);
void func_0032D300(int k, u32 *l, int n);
const char *func_0030ABF0(int r);
void func_0023AA40(void);
u32 func_002F8F20(int f);
void func_002F7610(u32 i);
int func_0032D9C0(void);
u32 func_0032E760(void);
void func_003DB480(int a, int b);
void func_002FAEA0(int f, int g, int k, int v);
void func_003DB220(int k, int *pos);
void func_003DB460(int a, int b);
void func_0032EA80(int k);
void func_002FAFC0(int f);

/* 0x0030EDC0, 0x228 bytes. Draws the notice by its kind. */
void func_0030EDC0(void)
{
    switch (func_0030E2C0()->kind) {
    case 0x1D: func_0030E560(); break;
    case 0x1C: func_0030E520(); break;
    case 0x1B: func_0030E510(); break;
    case 0x1A: func_0030E500(); break;
    case 0x19: func_0030E4F0(); break;
    case 0x18: func_0030ED50(); break;
    case 0x17: func_0030E900(); break;
    case 0x16: func_0030E8C0(); break;
    case 0xE: func_0030E820(); break;
    case 0xC: func_0030E790(); break;
    case 8: func_0030E710(); break;
    case 7: func_0030E700(); break;
    case 6: func_0030E630(); break;
    case 4: func_0030E5F0(); break;
    case 3: func_0030E5B0(); break;
    case 2: func_0030E590(); break;
    case 1: func_0030E570(); break;
    case 0:
        func_0037DAD0(g_0045D6B0);
        func_001A7DC0(g_0043C5EC, 0x80, 2);
        break;
    }
}

/* 0x0030EFF0, 0x158 bytes, matching. Notice 0 (the turn's income?): a sound every other frame after 0x30
 * frames; OK skips to the end, then closes (kind 0 updates the gold shown). */
void func_0030EFF0(void)
{
    Notice *n = func_0030E2C0();
    u32 pressed = pad1_pressed();
    int t = ++n->unknown_69C;

    if (t < 0x4E) {
        if (t > 0x30 && t % 2 == 0)
            func_0023AD10(3, 0, 0x2CDC, 0x2CDC, 0x1000);
        if (pressed & 0x40) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            n->unknown_69C = 0x4E;
        }
    } else if (pressed & 0x40) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_0030E4E0(0);
        if (n->kind == 0) {
            func_0039F950(func_002F9060(func_00327D50()));
            func_00376100(4, -1, -1);
        }
    }
}

/* 0x0030F150, 0x1C bytes, matching. */
void func_0030F150(void)
{
    func_0030EFF0();
}

/* 0x0030F170, 0x38 bytes, matching. Closes once func_0039B980 is not 2. */
void func_0030F170(void)
{
    func_0030E2C0();
    if (func_0039B980() != 2)
        func_0030E4E0(0);
}

/* 0x0030F1B0, 0x84 bytes, matching. Message 0x70 about force `f` (with the date). */
void func_0030F1B0(int f)
{
    char text[96];

    func_001204B0(text, func_00390760(0x70), func_00372660(func_00327CC0()),
                  func_0030CB80(func_00327C80()), func_002F8DB0(f));
    func_00374EE0(text);
}

/* 0x0030F240, 0xA0 bytes. Notice: force `a` is destroyed (by `b`) once its message closes. */
void func_0030F240(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 1) {
        if (func_00375B90() == 1) {
            func_0030E4E0(0);
            func_0030A030(n->a, n->b);
            n->step++;
        }
    } else if (n->step == 0 && func_0039B980() != 2) {
        func_0030F1B0(n->a);
        n->step++;
    }
}

/* 0x0030F2E0, 0x218 bytes. Officer `i` succeeds dead leader `old`: made leader (records and
 * envoy roles cleared, placed again if its region is full), with event command 0x2A, then
 * message 0x6E / 0x6F. 0 once shown, else 5. */
int func_0030F2E0(u32 i, u32 old)
{
    char a[32], b[32];
    int f = func_002F4080(i), r;

    if (func_0030E1F0() == 0) {
        func_002F3CF0(i, 3);
        func_002F8E80(f, i);
        if (func_002FB2A0(f) != 0)
            func_00327780(i);
        func_002F43C0(i, 0);
        func_002F4510(i, 0);
        func_00308600(i);
        r = func_002F5CC0(i);
        if (func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, r, 0, 1) > 3) {
            func_002F5BE0(i, 0x19);
            func_00309130(i, f, r, 0);
        }
        func_0030E140(0x2A, i, -1, -1);
        return 5;
    }
    if (func_0030E1F0() == 2) {
        func_0030E100();
        if (func_002FB2A0(f) == 0) {
            func_001204B0(a, g_00446808, func_002F2890(old));
            func_001204B0(b, g_00446808, func_002F2890(i));
            func_001204B0(g_007B4E60, func_00390760(0x6F), a, b);
        } else {
            func_001204B0(a, g_00446808, func_002F2890(i));
            func_001204B0(b, g_00446808, func_002F2890(old));
            func_001204B0(g_007B4E60, func_00390760(0x6E), a, b);
        }
        func_00374EE0(g_007B4E60);
        return 0;
    }
    return 5;
}

/* 0x0030F500, 0x250 bytes. The heir of dead leader `dead` for force `f`: for the computer the
 * officer most tied to him (then func_002F7550, then func_002F34E0, then the lowest number);
 * for the player the choice list opens (0x19F). -100 when there is no one. */
u32 func_0030F500(int f, u32 dead)
{
    u32 *o = func_002F7B10(), best = 0x19F, top = 0;
    int n, k;

    if (func_002FB2A0(f) == 0) {
        n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1);
        if (n == 0)
            return -100;
        for (k = 0; k < n; k++, o++) {
            u32 x = *o, v;

            v = (func_002F77A0(x, dead) != 0 ? 0x80000000 : 0)
                + (func_002F77F0(x, dead) != 0 ? 0x40000000 : 0)
                + (func_002F78C0(x, dead) != 0 ? 0x20000000 : 0)
                + (func_002F3DC0(x) == 2 ? 0x10000000 : 0)
                + (func_002F7550(x) << 20) + func_002F34E0(x);
            if (best > 0x19E || top < v || (top == v && (int)x < (int)best)) {
                top = v;
                best = x;
            }
        }
        return best;
    }
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F82F0, f, 0, 1);
    if (n == 0)
        n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8340, f, 0, 0);
    if (n == 0)
        return -100;
    func_0032D300(0xC, o, n);
    return 0x19F;
}

/* 0x0030F750, 0x444 bytes. An officer's death, step `step` (returns the next; 8 = done):
 * 0 event command 0x29 (when `ask`), 1 its message (0x69-0x6C, or 0xC1 / 0xC2 when `quiet`),
 * 2 the officer is removed; a leader's force (3) gets an heir (4 the player's choice, 5 the
 * succession, 6 its message) or 7 falls. */
int func_0030F750(int step, u32 i, int quiet, int ask)
{
    Notice *n = func_0030E2C0();
    char a[32], b[32];

    switch (step) {
    case 0:
        if (func_0030E1F0() == 0) {
            if (func_002F2840(i) == 0) {
                step = 8;
            } else if (ask == 0) {
                step = 1;
            } else {
                func_0030E140(0x29, i, -1, -1);
                step = 1;
            }
        }
        break;
    case 1:
        if (func_0030E1F0() == 2 || ask == 0) {
            func_0030E100();
            if (quiet == 0) {
                if (func_002F3DC0(i) == 0) {
                    func_001204B0(g_007B4E60, func_00390760(0x69), func_002F2890(i),
                                  func_0030ABF0(func_002F5CC0(i)));
                } else if (func_002F4080(i) == func_00327D50()) {
                    func_001204B0(g_007B4E60, func_00390760(0x6A), func_002F2890(i),
                                  func_0030ABF0(func_002F5CC0(i)));
                    if (func_0023A760(10) != 0) {
                        func_00102960(1);
                        func_0023A7D0(10);
                    }
                } else if (func_002F3E70(i) == 0) {
                    func_00120928(b, func_002F8DB0(func_002F4080(i)));
                    func_00120928(a, func_002F2890(i));
                    func_001204B0(g_007B4E60, func_00390760(0x6C), a, b);
                } else {
                    func_001204B0(g_007B4E60, func_00390760(0x6B), func_002F2890(i));
                }
            } else {
                int m = func_002FB2A0(func_002F4080(i)) == 0 ? 0xC1 : 0xC2;

                func_001204B0(g_007B4E60, func_00390760(m), func_002F2890(i));
                if (func_0023A760(0xB) != 0) {
                    func_00102960(1);
                    func_0023A7D0(0xB);
                }
            }
            func_00374EE0(g_007B4E60);
            step = 2;
        }
        break;
    case 2:
        if (func_00375B90() == 1) {
            int g, lead = 0;

            func_0023AA40();
            g = func_002F4080(i);
            n->b = g;
            if (IS_FORCE(g) && i == func_002F8F20(g))
                lead = func_002FB3B0(g) != 0;
            func_002F7610(i);
            step = lead ? 3 : 8;
        }
        break;
    case 3: {
        u32 h = func_0030F500(n->b, i);

        if (h == (u32)-100) {
            step = 7;
        } else if (h < 0x19F) {
            n->c = h;
            step = 5;
        } else {
            step = 4;
        }
        break;
    }
    case 4:
        if (func_0032D9C0() == 1) {
            n->c = func_0032E760();
            step = 5;
        }
        break;
    case 5:
        if (func_0030F2E0(n->c, i) == 0)
            step = 6;
        break;
    case 6:
        if (func_00375B90() == 1)
            step = 8;
        break;
    case 7:
        func_0030A030(n->b, 0x19);
        step = 8;
        break;
    }
    return step;
}

/* 0x0030FBA0, 0x70 bytes. Notice: the listed officers die, last first. */
void func_0030FBA0(void)
{
    Notice *n = func_0030E2C0();

    n->phase = func_0030F750(n->phase, n->list[n->count - 1], 0, 1);
    if (n->phase == 8) {
        n->phase = 0;
        if (--n->count < 1)
            func_0030E4E0(0);
    }
}

/* 0x0030FC10, 0x50 bytes, matching. Notice: officer `a` dies (with the short message). */
void func_0030FC10(void)
{
    Notice *n = func_0030E2C0();

    n->phase = func_0030F750(n->phase, n->a, 1, 1);
    if (n->phase == 8) {
        n->phase = 0;
        func_0030E4E0(0);
    }
}

/* 0x0030FC60, 0x98 bytes. Notice: event command `b` for officer `a`, closed once answered. */
void func_0030FC60(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 1) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_0030E4E0(0);
        }
    } else if (n->step == 0 && func_0030E1F0() == 0) {
        func_0030E140(n->b, n->a, -1, -1);
        n->step++;
    }
}

/* 0x0030FD00, 0x270 bytes. Notice: force `a` proposes a tie (`b` 0 alliance, else a truce?):
 * its leader asks (0x2E), the player answers (0x20 no / 0x1D yes); on yes the tie is made and
 * message 0x3C / 0x3D shown with the map. */
void func_0030FD00(void)
{
    Notice *n = func_0030E2C0();
    int a = n->a, b = n->b, pos[2], k, m;
    u32 lead = func_002F8F20(a);

    switch (n->step) {
    case 4:
        if (++n->c > 5)
            func_0030E4E0(0);
        break;
    case 3:
        if (func_00375BF0() != 0 && func_00375B90() == 1) {
            func_003DB480(3, 2);
            n->c = 0;
            n->step++;
        }
        break;
    case 2:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            if (n->c == 0) {
                func_0030E4E0(0);
            } else {
                if (b == 0) {
                    k = 4;
                    m = 0x3C;
                } else {
                    k = 0xC;
                    m = 0x3D;
                }
                func_002FAEA0(a, func_00327D50(), k, 1);
                pos[0] = 0xA0;
                pos[1] = 0x60;
                func_003DB220(3, pos);
                func_003DB460(3, 2);
                func_001204B0(g_007B4E60, func_00390760(m), func_002F8DB0(a));
                func_00374EE0(g_007B4E60);
                n->step++;
            }
        }
        break;
    case 1:
        if (func_0030E1F0() == 2) {
            int yes = func_0030E0F0()[4];

            n->c = yes;
            func_0030E100();
            func_0030E140(yes == 0 ? 0x20 : 0x1D, lead, a, -1);
            n->step++;
        }
        break;
    case 0:
        func_0032EA80(b);
        func_0030E140(0x2E, lead, a, -1);
        n->step++;
        break;
    }
}

/* 0x0030FF70, 0x164 bytes. Notice: force `a` asks to break its tie with the player; on yes the
 * player's ties are cleared and the tie with `a` set to kind 3. */
void func_0030FF70(void)
{
    Notice *n = func_0030E2C0();
    int a = n->a;
    u32 lead = func_002F8F20(a);

    if (n->step == 2) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            if (n->c != 0) {
                func_002FAFC0(func_00327D50());
                func_002FAEA0(a, func_00327D50(), 0, 3);
            }
            func_0030E4E0(0);
        }
    } else if (n->step == 1) {
        if (func_0030E1F0() == 2) {
            int yes;

            func_0030E100();
            yes = func_0030E0F0()[4];
            n->c = yes;
            func_0030E140(yes == 0 ? 0x20 : 0x1D, lead, a, -1);
            n->step++;
        }
    } else if (n->step == 0) {
        func_0032EA80(2);
        func_0030E140(0x2E, lead, a, -1);
        n->step++;
    }
}

void func_00375030(int x, int y, int w, int h, int a, const char *text);
void func_00321A20(u32 i, u32 j, int c);
void func_002F3B30(u32 i, int v);
void func_0032E910(u32 i);
int func_00330650(int k);
int func_00309C30(u32 i, int f, int r);
int func_0036B260(void);
int func_0036BA20(int side, int k);
int func_00120A40(const char *text);       /* strlen */
void func_003A9510(int *r, int n, int a);
void func_003A9010(int a);
void func_003A9610(void);
void func_002F90D0(int f, int v);
int func_00320F10(void);
int func_00327E50(void);
void func_003A7C10(void);
int func_002F9990(int f);
void func_003A78E0(int r, int c, int a);
void func_003A80F0(int r, int a);
void func_003A8000(int r);
void func_003A80A0(int a);

/* Shows the message text once built. */
#define SHOW() func_00374EE0(g_007B4E60)
/* Whether the message box was closed with OK. */
#define CLOSED_OK() (func_00375BF0() != 0 && func_00375B90() == 1)

/* 0x003100E0, 0x2F8 bytes. Notice: officer `b` asks to bring officer `a` over (message 0x71 as
 * a yes / no question); on yes event 6's command runs and `a` joins the player (message 0x72),
 * on no func_00321A20 records the refusal. */
void func_003100E0(void)
{
    Notice *n = func_0030E2C0();
    char a[32], b[32];
    int pos[2], r;

    switch (n->step) {
    case 0:
        pos[0] = 0x80;
        pos[1] = 0x38;
        func_003DB220(2, pos);
        func_003DB460(2, 2);
        func_00120928(b, func_002F2890(n->b));
        func_00120928(a, func_002F2890(n->a));
        func_001204B0(g_007B4E60, func_00390760(0x71), a, b);
        func_00375030(0x38, 0x11C, 400, 0x54, 0, g_007B4E60);
        n->step++;
        break;
    case 1:
        if (func_00375BF0() != 0) {
            r = func_00375B90();
            if (r == 2) {
                func_003DB480(2, 2);
                n->unknown_690 = 1;
                n->count = 0;
                n->step++;
            } else if (r == 3) {
                func_003DB480(2, 2);
                n->unknown_690 = 0;
                n->count = 0;
                n->step++;
            }
        }
        break;
    case 2:
        if (++n->count > 5) {
            if (n->unknown_690 == 1) {
                n->step++;
            } else {
                func_00321A20(n->a, n->b, n->c);
                func_002F3B30(n->a, 2);
                func_0030E4E0(0);
            }
        }
        break;
    case 3:
        func_0032E910(n->a);
        r = func_00330650(6);
        if (r != -1) {
            func_0030E140(r, n->a, -1, -1);
            n->step++;
        }
        break;
    case 4:
        if (func_0030E1F0() == 2) {
            u32 lead;

            func_0030E100();
            lead = func_002F8F20(func_002F4080(n->b));
            func_00120928(b, func_002F2890(n->a));
            func_00120928(a, func_002F8DB0(func_002F4080(lead)));
            func_001204B0(g_007B4E60, func_00390760(0x72), b, a);
            SHOW();
            n->step++;
        }
        break;
    case 5:
        if (CLOSED_OK()) {
            u32 i = n->a, j = n->b;

            func_0030E4E0(0);
            func_00309C30(i, func_00327D50(), func_002F5CC0(j));
        }
        break;
    }
}

/* 0x003103E0, 0xE8 bytes. The gold won by the player's officers of side 0 in the last battle. */
int func_003103E0(void)
{
    int s = 0, k;

    if (func_0036B260() == 0)
        return 0;
    for (k = 0; k < 8; k++) {
        u32 o = func_003620E0(0, k);

        if ((int)o >= 0 && (int)o < 0x19F) {
            int g = func_002F4080(o);

            if (IS_FORCE(g) && func_002FB2A0(g) != 0)
                s += func_0036BA20(0, k);
        }
    }
    return s;
}

/* 0x003104D0, 0x7A4 bytes. Notice: the battle's result for the player (kind `a`, won `b`,
 * forces list[0] / list[1], region list[2]; messages 0xB1-0xBA, a capture (0xC0), the gold won
 * (0xBB, list[4] bonus) and the officers' limit (0x78)). */
void func_003104D0(void)
{
    Notice *n = func_0030E2C0();
    int c8 = n->c, kind = n->a, won = n->b, f1 = n->list[0], f2 = n->list[1];
    int region = n->list[2], taken = n->list[3], gold = n->list[4], p = func_00327D50();
    char a[32], b[32], c[32];

    g_007B4E60[0] = 0;
    switch (n->step) {
    case 0: {
        int bonus = 0;

        switch (kind) {
        case 0: case 2:
            if (won == 0) {
                func_001204B0(g_007B4E60, func_00390760(0xB3), func_002F8DB0(p), func_0030ABF0(region));
            } else {
                func_00120928(a, func_002F8DB0(p));
                func_00120928(b, func_002F8DB0(p));
                func_001204B0(g_007B4E60, func_00390760(0xB1), a, func_0030ABF0(region), b);
            }
            break;
        case 1: case 3:
            if (won == 0) {
                func_00120928(a, func_002F8DB0(f2));
                func_00120928(b, func_002F8DB0(p));
                func_001204B0(g_007B4E60, func_00390760(0xB6), a, b);
            } else {
                func_00120928(a, func_002F8DB0(f1));
                func_00120928(b, func_002F8DB0(p));
                func_001204B0(g_007B4E60, func_00390760(0xB5), a, b, a, func_0030ABF0(region));
                bonus = 3000;
            }
            break;
        case 4:
            if (won == 0) {
                func_00120928(a, func_002F8DB0(p));
                func_00120928(b, func_002F8DB0(f1));
                func_001204B0(g_007B4E60, func_00390760(0xB4), a, b, func_0030ABF0(region));
            } else {
                func_001204B0(g_007B4E60, func_00390760(0xB2), func_002F8DB0(p), func_0030ABF0(region));
            }
            break;
        case 5:
            if (won == 0) {
                func_00120928(a, func_002F8DB0(f1));
                func_00120928(b, func_002F8DB0(f2));
                func_00120928(c, func_002F8DB0(p));
                func_001204B0(g_007B4E60, func_00390760(0xB8), b, c, a, func_0030ABF0(region));
            } else {
                func_00120928(a, func_002F8DB0(f1));
                func_00120928(b, func_002F8DB0(p));
                func_001204B0(g_007B4E60, func_00390760(0xB7), a, b, func_0030ABF0(region));
                bonus = 1000;
            }
            break;
        default:
            func_00120928(a, func_002F8DB0(f1));
            func_00120928(b, func_002F8DB0(f2));
            if (c8 == 0)
                func_001204B0(g_007B4E60, func_00390760(0xBA), a, b, func_0030ABF0(region));
            else
                func_001204B0(g_007B4E60, func_00390760(0xB9), a, b, func_0030ABF0(region), a);
            break;
        }
        n->list[4] = bonus;
        if (func_00120A40(g_007B4E60) == 0) {
            n->step += 2;
        } else {
            SHOW();
            n->step++;
        }
        func_003A9510(&n->list[2], 1, 0);
        func_003A9010(1);
        break;
    }
    case 1:
        if (CLOSED_OK()) {
            n->step++;
            func_003A9610();
        }
        break;
    case 2:
        if (taken == 0) {
            n->step += 2;
        } else {
            func_00120928(a, func_002F8DB0(f1));
            func_00120928(b, func_002F8DB0(f2));
            func_001204B0(g_007B4E60, func_00390760(0xC0), b, a);
            SHOW();
            func_003A9510(&n->list[2], 1, 0);
            func_003A9010(1);
            n->step++;
        }
        break;
    case 3:
        if (CLOSED_OK()) {
            func_003A9610();
            n->step++;
        }
        break;
    case 4:
        if (gold == 0) {
            n->step += 2;
        } else {
            int s = func_003103E0() / 100 * 100;

            gold += s < 2000 ? s : 2000;
            func_002F90D0(p, gold / 10);
            func_001204B0(g_007B4E60, func_00390760(0xBB), func_002F8DB0(f1), func_0030CB80(gold));
            SHOW();
            n->step++;
        }
        break;
    case 5:
        if (CLOSED_OK()) {
            func_0039F960();
            n->step++;
        }
        break;
    case 6:
        if (func_00320F10() == 0) {
            n->step += 2;
        } else {
            int lim = func_00327E50();

            func_001204B0(g_007B4E60, func_00390760(0x78), func_002F8DB0(func_00327D50()), func_0030CB80(lim));
            SHOW();
            n->step++;
        }
        break;
    case 7:
        if (CLOSED_OK())
            n->step++;
        break;
    case 8:
        func_0030E4E0(0);
        break;
    }
}

/* 0x00310C80, 0x10C bytes. Notice: message 0x61 for each listed force in turn. */
void func_00310C80(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 2) {
        func_0030E4E0(0);
    } else if (n->step == 1) {
        if (CLOSED_OK()) {
            if (++n->a < n->count)
                n->step = 0;
            else
                n->step++;
        }
    } else if (n->step == 0) {
        func_001204B0(g_007B4E60, func_00390760(0x61), func_002F8DB0(n->list[n->a]));
        SHOW();
        n->step++;
    }
}

/* 0x00310D90, 0xC4 bytes. Notice: message `a`. */
void func_00310D90(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 2) {
        func_0030E4E0(0);
    } else if (n->step == 1) {
        if (CLOSED_OK())
            n->step++;
    } else if (n->step == 0) {
        func_001204B0(g_007B4E60, func_00390760(n->a));
        SHOW();
        n->step++;
    }
}

/* 0x00310E60, 0x1AC bytes. The season's notice (season `a`, 0-4): its sound, the map window
 * and its message (0x62-0x68). */
void func_00310E60(void)
{
    Notice *n = func_0030E2C0();
    int s = n->a, pos[5], m = 0;

    if (func_0023A760(s) != 0) {
        func_00102960(1);
        func_0023A7D0(s);
    }
    pos[1] = 0x60;
    pos[0] = 0x80;
    pos[2] = 0x100;
    pos[4] = 0x80;
    pos[3] = 0xC0;
    func_003DB220(0xE, pos);
    func_003DB460(0xE, 5);
    switch (n->a) {
    case 3: m = 0x68; break;
    case 0: m = 0x67; break;
    case 2: m = 0x66; break;
    case 1: m = n->b == 0 ? 0x65 : 0x64; break;
    case 4: m = 0x62; break;
    }
    func_001204B0(g_007B4E60, func_00390760(m));
    SHOW();
    n->step = 1;
}

/* 0x00311010, 0xE0 bytes. Colours the map: the listed regions in their force's colour, the
 * others plain. */
void func_00311010(void)
{
    Notice *n = func_0030E2C0();
    int r, k;

    func_003A7C10();
    for (r = 0; r < func_0030AB90(); r++) {
        int found = 0;

        for (k = 0; k < n->count; k++) {
            if (n->list[k] == r)
                found = 1;
        }
        if (found) {
            func_003A78E0(r, func_002F9990(func_0030AFF0(r)), 1);
            func_003A80F0(r, 1);
        } else {
            func_003A8000(r);
        }
    }
    func_003A80A0(1);
}

/* 0x00311100, 0x68 bytes, matching. Season notice step 1: once closed, the map. */
void func_00311100(void)
{
    Notice *n = func_0030E2C0();

    if (CLOSED_OK()) {
        func_003DB480(0xE, 5);
        func_0023AA40();
        func_00311010();
        n->step = 2;
    }
}

/* 0x00311170, 0xF0 bytes. The season notice. */
void func_00311170(void)
{
    int s = func_0030E2C0()->step;

    if (s == 2) {
        if (pad1_pressed() & 0x40) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_003A80A0(0);
            func_003A7D90();
            func_0030E4E0(0);
        }
    } else if (s == 1) {
        func_00311100();
    } else if (s == 0) {
        func_00310E60();
    }
}

extern int g_00414B50[3][3];             /* by training command: the three stats it may raise */
extern int g_00414B80[];                 /* by stat: the skill that helps it */
extern int g_00446900[3][12];            /* by training command: the skills it cannot teach */
extern const char *g_0042D3E0[];         /* skill names ("Vitality", ...) */
extern char *g_0045CFE8;                 /* (small data) a text buffer */

void func_002F3A60(u32 i, int v);
void func_002F4CB0(u32 i, int v);
void func_002F5480(u32 i, int v);
void func_002F4FD0(u32 i, int v);
void func_002F52F0(u32 i, int v);
void func_002F5610(u32 i, int v);
void func_002F4E40(u32 i, int v);
void func_002F5160(u32 i, int v);
int func_002F39F0(u32 i);
int func_002F4C40(u32 i);
int func_002F5410(u32 i);
int func_002F4F60(u32 i);
int func_002F5280(u32 i);
int func_002F55A0(u32 i);
int func_002F4DD0(u32 i);
int func_002F50F0(u32 i);
int func_002F59A0(u32 i);
int func_002F5D30(u32 i);
int func_002F5E80(u32 i);
int func_002F6510(u32 i);
int func_002F6120(u32 i);
int func_002F63C0(u32 i);
int func_002F6660(u32 i);
int func_002F5FD0(u32 i);
int func_002F6270(u32 i);
int func_002F47A0(u32 i, int k);
void func_002F4820(u32 i, int k, int v);
int func_002FABC0(int f);
int func_002FA9E0(int f, int k);
int func_002FBE80(int f);
int func_0030AB50(int k);
const char *func_00372FF0(int stat);
int func_0030CB00(int n);
int func_0030CB50(int pct);

/* 0x00311260, 0x118 bytes. Notice: the command's help message (0xAB for commands 0x3B-0x59,
 * 0x12F for 0x5A-0x62 and 0x65, else 0xAA) in the window. */
void func_00311260(void)
{
    Notice *n = func_0030E2C0();
    int pos[5], a, m;

    if (n->step == 1) {
        if (CLOSED_OK()) {
            func_003DB480(0xF, 5);
            func_0030E4E0(0);
        }
    } else if (n->step == 0) {
        a = n->a;
        if (a < 0x3B || a > 0x59)
            m = ((a < 0x5A || a > 0x62) && a != 0x65) ? 0xAA : 0x12F;
        else
            m = 0xAB;
        func_00374EE0(func_00390760(m));
        pos[4] = 0x80;
        func_003DB220(0xF, pos);
        func_003DB460(0xF, 5);
        n->step++;
    }
}

/* 0x00311380, 0x104 bytes. Notice: the officers' limit (message 0x78). */
void func_00311380(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 2) {
        func_0030E4E0(0);
    } else if (n->step == 1) {
        if (CLOSED_OK())
            n->step++;
    } else if (n->step == 0) {
        int lim = func_00327E50();

        func_001204B0(g_007B4E60, func_00390760(0x78), func_002F8DB0(func_00327D50()), func_0030CB80(lim));
        SHOW();
        n->step++;
    }
}

/* 0x00311490, 0x1D4 bytes. Notice: officer `a`'s two messages (0x73, then 0x75 for `b` 4, else
 * 0x74 with `b` / 4). */
void func_00311490(void)
{
    Notice *n = func_0030E2C0();
    u32 i = n->a;
    int b = n->b;

    switch (n->step) {
    case 4:
        func_0030E4E0(0);
        break;
    case 3:
        if (CLOSED_OK())
            n->step++;
        break;
    case 2:
        if (b == 4)
            func_001204B0(g_007B4E60, func_00390760(0x75), func_002F2890(i));
        else
            func_001204B0(g_007B4E60, func_00390760(0x74), func_002F2890(i), func_0030CB80(b / 4));
        SHOW();
        n->step++;
        break;
    case 1:
        if (CLOSED_OK())
            n->step++;
        break;
    case 0:
        func_001204B0(g_007B4E60, func_00390760(0x73), func_002F2890(i));
        SHOW();
        n->step++;
        break;
    }
}

/* 0x00311670, 0x98 bytes. Runs event command `c` (0x28-0x2A become their success / failure
 * forms). */
void func_00311670(int c, int ok)
{
    if (c > 0x27 && c < 0x2B) {
        if (c == 0x2A)
            c = ok == 0 ? 0x62 : 0x61;
        else if (c == 0x29)
            c = ok == 0 ? 0x73 : 0x72;
        else if (c == 0x28)
            c = ok == 0 ? 0x6A : 0x69;
    }
    func_0030E140(c, -1, -1, -1);
}

/* 0x00311710, 0xB0 bytes, matching. Raises officer `i`'s stat `s` (0-7) by `v`. */
void func_00311710(u32 i, int s, int v)
{
    switch (s) {
    case 0: func_002F3A60(i, v); break;
    case 1: func_002F4CB0(i, v); break;
    case 2: func_002F5480(i, v); break;
    case 3: func_002F4FD0(i, v); break;
    case 4: func_002F52F0(i, v); break;
    case 5: func_002F5610(i, v); break;
    case 6: func_002F4E40(i, v); break;
    case 7: func_002F5160(i, v); break;
    }
}

/* Officer `i`'s stat `s` and its limit (0x15E / 0xFA when func_002F59A0). */
static void stat_and_limit(u32 i, int s, int *v, int *lim)
{
    int full = 0;

    switch (s) {
    case 0: *v = func_002F39F0(i); full = func_002F59A0(i); *lim = full ? 0x15E : func_002F5D30(i); break;
    case 1: *v = func_002F4C40(i); full = func_002F59A0(i); *lim = full ? 0x15E : func_002F5E80(i); break;
    case 2: *v = func_002F5410(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F6510(i); break;
    case 3: *v = func_002F4F60(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F6120(i); break;
    case 4: *v = func_002F5280(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F63C0(i); break;
    case 5: *v = func_002F55A0(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F6660(i); break;
    case 6: *v = func_002F4DD0(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F5FD0(i); break;
    case 7: *v = func_002F50F0(i); full = func_002F59A0(i); *lim = full ? 0xFA : func_002F6270(i); break;
    }
}

/* 0x003117C0, 0x454 bytes. Training command `c` (0x24-0x2A; 0x27 picks a row at random) for
 * officer `i` with `bonus`: one of the row's stats below its limit, raised by 1 + `bonus` +
 * chance (its helping skill) + the force's value / 300 + 0-1 (message 0x2C). 0 when none. */
int func_003117C0(u32 i, int c, int bonus)
{
    int row[3][3], ok[4], n = 0, k, s, v = 0, lim = 0, *r;

    for (k = 0; k < 9; k++)
        (&row[0][0])[k] = (&g_00414B50[0][0])[k];
    switch (c) {
    case 0x24: case 0x28: k = 0; break;
    case 0x25: case 0x29: k = 1; break;
    case 0x26: case 0x2A: k = 2; break;
    case 0x27: k = func_0030CB00(3); break;
    default: k = 0; break;
    }
    r = row[k];
    for (s = 0; s < 3; s++) {
        stat_and_limit(i, r[s], &v, &lim);
        if (v < lim)
            ok[n++] = s;
    }
    if (n == 0)
        return 0;
    s = r[ok[func_0030CB00(n)]];
    {
        int lv = func_002F47A0(i, g_00414B80[s]);
        int fv = func_002FABC0(func_002F4080(i));
        int luck = func_0030CB50((lv + 1) * 0x14);
        int gain = (luck != 0) + bonus + 1 + fv / 300 + func_0030CB00(2);

        if (gain == 0)
            return 0;
        func_001204B0(g_0045CFE8, func_00390760(0x2C), func_002F2890(i), func_00372FF0(s), func_0030CB80(gain));
        func_00374EE0(g_0045CFE8);
        func_00311710(i, s, gain);
    }
    return 1;
}

/* 0x00311C30, 0x8C bytes, matching. Whether training command `c` cannot teach skill `k`. */
int func_00311C30(int c, int k)
{
    int row = 0, j;

    switch (c) {
    case 0x24: case 0x28: row = 0; break;
    case 0x25: case 0x29: row = 1; break;
    case 0x26: case 0x2A: row = 2; break;
    }
    for (j = 0; j < 12; j++) {
        if (k == g_00446900[row][j])
            return 1;
    }
    return 0;
}

/* 0x00311CC0, 0x2AC bytes. Skill training: officer `i` learns a skill (level + 1) that teacher
 * `t` or its force knows better (command 0x27 any, others not their excluded skills nor
 * level 4; skill 0x27 needs func_002FBE80), by chance (90% at least); message 0x2B. */
int func_00311CC0(u32 i, u32 t, int c)
{
    int cand[40], n = 0, k, pct, lv;

    for (k = 0; k < 0x28; k++) {
        int a, b, my;

        if (c != 0x27 && func_00311C30(c, k) != 0)
            continue;
        a = func_002F47A0(t, k);
        b = func_002FA9E0(func_002F4080(i), k);
        if (a == 0 && b == 0)
            continue;
        if (b < a)
            b = a;
        my = func_002F47A0(i, k);
        if (my >= b || (c != 0x27 && my == 4))
            continue;
        if (k == 0x27 && (func_002FBE80(func_002F4080(i)) == 0 || my != 0))
            continue;
        if (my < func_0030AB50(k) && b != 0)
            cand[n++] = k;
    }
    if (n == 0)
        return 0;
    k = cand[func_0030CB00(n)];
    pct = (func_002F47A0(i, 0x23) + 2) * 10 + func_002FABC0(func_002F4080(i)) / 0x14;
    if (pct < 0x5A)
        pct = 0x5A;
    if (func_0030CB50(pct) == 0)
        return 0;
    lv = func_002F47A0(i, k);
    func_001204B0(g_007B4E60, func_00390760(0x2B), func_002F2890(i), g_0042D3E0[k], func_0030CB80(lv + 1));
    SHOW();
    func_002F4820(i, k, lv + 1);
    return 1;
}

const char *func_002F2A30(u32 i);
int func_002FB320(int f, int *out);
int func_002FB2D0(int f);
void func_003986E0(int r, int a, int *l, int n);
void func_0030A870(int kind, u32 i, int r, int *l, int n, int show);
int func_002F7EC0(u32 i, int f);

/* 0x00311F70, 0x11C bytes. The training's closing message: 0x32 for commands outside
 * 0x24-0x27, else when nothing was learned 0x2D-0x30 with both officers. 0 when there is none. */
int func_00311F70(u32 i, u32 j, int any, int c)
{
    char a[32], b[32];
    int m = -1;

    if (c < 0x24 || c > 0x27) {
        func_00374EE0(func_00390760(0x32));
        return 1;
    }
    if (any != 0)
        return 0;
    if (c == 0x27)
        m = 0x30;
    else if (c == 0x26)
        m = 0x2F;
    else if (c == 0x25)
        m = 0x2E;
    else if (c == 0x24)
        m = 0x2D;
    func_00120928(a, func_002F2890(i));
    func_00120928(b, func_002F2890(j));
    func_001204B0(g_007B4E60, func_00390760(m), a, b);
    SHOW();
    return 1;
}

/* 0x00312090, 0x370 bytes. Notice: a training command `a` (succeeded `b`) for the listed
 * officers: its event, then each officer's stat training (the two teachers list[4] / list[5]
 * get a bonus), then skill training between list[4] and list[5], then the closing message.
 * Uses list[6]-list[10] as counters. */
void func_00312090(void)
{
    Notice *n = func_0030E2C0();
    int ok = n->b, c = n->a, *idx = &n->list[6], *idx2 = &n->list[7];
    int cnt = n->list[8], cnt2 = n->list[9], bonus = 0;

    switch (n->step) {
    case 0:
        func_00311670(c, ok);
        n->list[8] = 4;
        if (c < 0x28 || c > 0x2A)
            n->list[8] = 1;
        n->list[9] = 2;
        if (c < 0x28 || c > 0x2A)
            n->list[9] = 1;
        else if (ok == 0)
            n->list[9] = 1;
        n->list[10] = 0;
        *idx = 0;
        *idx2 = 0;
        n->step++;
        break;
    case 1:
        if (func_0030E1F0() == 2) {
            u32 i;

            func_0030E100();
            i = n->list[*idx];
            if (c > 0x27 && c < 0x2B) {
                if (i == (u32)n->list[4])
                    bonus = 2;
                else if (i == (u32)n->list[5])
                    bonus = 1;
            }
            if (func_003117C0(i, c, bonus) == 0) {
                if (++*idx >= cnt)
                    n->step += 2;
            } else {
                n->list[10] = 1;
                n->step++;
            }
        }
        break;
    case 2:
        if (CLOSED_OK()) {
            if (++*idx < cnt)
                n->step = 1;
            else
                n->step++;
        }
        break;
    case 3: {
        u32 i, t;

        if (*idx2 == 0) {
            t = n->list[5];
            i = n->list[4];
        } else {
            i = n->list[5];
            t = n->list[4];
        }
        if (func_00311CC0(i, t, c) == 0) {
            if (++*idx2 >= cnt2)
                n->step += 2;
        } else {
            n->list[10] = 1;
            n->step++;
        }
        break;
    }
    case 4:
        if (CLOSED_OK()) {
            if (++*idx2 < cnt2)
                n->step = 3;
            else
                n->step++;
        }
        break;
    case 5:
        if (func_00311F70(n->list[4], n->list[5], n->list[10], c) == 0)
            n->step += 2;
        else
            n->step++;
        break;
    case 6:
        if (CLOSED_OK())
            n->step++;
        break;
    case 7:
        func_0030E4E0(0);
        break;
    }
}

/* 0x00312400, 0x190 bytes. Notice: force `b`'s leader event (command 0x2B), then its regions on
 * the map with message 0x5E. */
void func_00312400(void)
{
    Notice *n = func_0030E2C0();
    int f = n->b, reg[28];
    u32 lead;

    if (!IS_FORCE(f))
        return;
    lead = func_002F8F20(f);
    if (lead >= 0x19F)
        return;
    switch (n->step) {
    case 3:
        func_0030E4E0(0);
        break;
    case 2:
        if (CLOSED_OK()) {
            func_003A9610();
            n->step++;
        }
        break;
    case 1:
        func_0030E100();
        func_003A9510(reg, func_002FB320(f, reg), 0);
        func_001204B0(g_007B4E60, func_00390760(0x5E), func_002F2A30(lead));
        SHOW();
        n->step++;
        break;
    case 0:
        func_0030E140(0x2B, lead, -1, -1);
        n->step++;
        break;
    }
}

/* 0x00312590, 0xC4 bytes. Notice: event command 0x68 / 0x71 / 0x60 (by `a` 0x28 / 0x29 /
 * other), closed once answered. */
void func_00312590(void)
{
    Notice *n = func_0030E2C0();

    if (n->step == 1) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_0030E4E0(0);
        }
    } else if (n->step == 0 && func_0030E1F0() == 0) {
        int c;

        if (n->a == 0x28)
            c = 0x68;
        else if (n->a == 0x29)
            c = 0x71;
        else
            c = 0x60;
        func_0030E140(c, -1, -1, -1);
        n->step++;
    }
}

/* 0x00312660, 0x18C bytes. Notice: region `a` rises (event 0x2C, or 0x3D with `b`), message 0x49
 * with the region shown. */
void func_00312660(void)
{
    Notice *n = func_0030E2C0();
    int r = n->a, b = n->b;

    if (n->step == 3) {
        func_0030E4E0(0);
    } else if (n->step == 2) {
        if (CLOSED_OK()) {
            func_0023AA40();
            func_003A9610();
            n->step++;
        }
    } else if (n->step == 1) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_001204B0(g_007B4E60, func_00390760(0x49), func_0030ABF0(r));
            SHOW();
            if (func_0023A760(5) != 0) {
                func_00102960(1);
                func_0023A7D0(5);
            }
            n->step++;
        }
    } else if (n->step == 0) {
        if (func_0030E1F0() == 0) {
            func_0030E140(b != 0 ? 0x3D : 0x2C, -1, -1, -1);
            func_003A9510(&n->a, 1, 0);
            n->step++;
        }
    }
}

/* 0x003127F0, 0x184 bytes. Notice: officer `a` in region `b` (event 0x2B, message 0x52). */
void func_003127F0(void)
{
    Notice *n = func_0030E2C0();
    u32 i = n->a;

    if (n->step == 3) {
        func_0030E4E0(0);
    } else if (n->step == 2) {
        if (CLOSED_OK()) {
            func_0023AA40();
            func_003A9610();
            n->step++;
        }
    } else if (n->step == 1) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_001204B0(g_007B4E60, func_00390760(0x52), func_002F2890(i));
            SHOW();
            if (func_0023A760(0xE) != 0) {
                func_00102960(1);
                func_0023A7D0(0xE);
            }
            n->step++;
        }
    } else if (n->step == 0) {
        if (func_0030E1F0() == 0) {
            func_0030E140(0x2B, i, -1, -1);
            func_003A9510(&n->b, 1, 0);
            n->step++;
        }
    }
}

/* 0x00312980, 0x4EC bytes. Notice: officer `a` rebels in region `b` (events 0x2B and 0x2D,
 * messages 0x4B and 0x4C); a new force rises with the listed officers, the region's other
 * officers flee to the player's home (message 0xC7). */
void func_00312980(void)
{
    Notice *n = func_0030E2C0();
    u32 i = n->a;
    int r = n->b, p = func_00327D50(), rest[7], m, k, j, cnt;
    char a[32], b[32];
    u32 *o;

    switch (n->step) {
    case 0:
        if (func_0030E1F0() == 0) {
            func_0030E140(0x2B, i, -1, -1);
            func_003A9510(&n->b, 1, 0);
            n->step++;
        }
        break;
    case 1:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_00120928(b, func_0030ABF0(r));
            func_00120928(a, func_002F2890(i));
            func_001204B0(g_007B4E60, func_00390760(0x4B), a, b);
            SHOW();
            if (func_0023A760(5) != 0) {
                func_00102960(1);
                func_0023A7D0(5);
            }
            n->step++;
        }
        break;
    case 2:
        if (CLOSED_OK()) {
            func_0023AA40();
            if (func_0030E1F0() == 0) {
                func_0030E140(0x2D, i, -1, -1);
                n->step++;
            }
        }
        break;
    case 3:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_00120928(b, func_0030ABF0(r));
            func_00120928(a, func_002F2890(i));
            func_001204B0(g_007B4E60, func_00390760(0x4C), a, b);
            SHOW();
            if (func_0023A760(0xE) != 0) {
                func_00102960(1);
                func_0023A7D0(0xE);
            }
            n->step++;
        }
        break;
    case 4:
        if (CLOSED_OK()) {
            func_0023AA40();
            func_003A9610();
            n->step++;
        }
        break;
    case 5:
        m = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, r, 0, 0);
        o = func_002F7B10();
        cnt = 0;
        for (k = 0; k < m; k++, o++) {
            int x = *o, found = 0;

            if (x == (int)i)
                continue;
            for (j = 0; j < n->count; j++) {
                if (x == n->list[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found)
                rest[cnt++] = x;
        }
        func_0030A870(1, i, r, n->list, n->count, 1);
        for (k = 0; k < cnt; k++)
            n->list[k] = rest[k];
        n->count = cnt;
        if (cnt == 0) {
            n->step += 3;
        } else {
            func_00374EE0(func_00390760(199));
            n->step++;
        }
        break;
    case 6:
        if (CLOSED_OK()) {
            func_0023AA40();
            func_003986E0(func_002FB2D0(p), -1, n->list, n->count);
            n->step++;
        }
        break;
    case 7:
        if (func_0039B980() != 2)
            n->step++;
        break;
    case 8:
        func_0030E4E0(0);
        break;
    }
}

/* A command record (0x20 bytes, 100 of them at 0x00446AD0). */
typedef struct {
    int group;               /* +0x00 */
    int unknown_04;          /* +0x04 */
    int unknown_08;          /* +0x08 */
    int unknown_0C;          /* +0x0C */
    int unknown_10;          /* +0x10 */
    int unknown_14;          /* +0x14 */
    int unknown_18;          /* +0x18 */
    short cost;              /* +0x1C */
    short unknown_1E;        /* +0x1E */
} Command;

extern Command g_00446AD0[100];
extern int g_00447608[];

const char *func_00372250(int k);
u32 func_00328330(int k);
u32 func_00328640(int k);
void func_003DC090(int k, int *pos);
void func_003DC0E0(int k, int a, int b);
int func_003DC2D0(int k);
void func_00328440(int r);
void func_00328360(int a);
void func_00328750(int r);
void func_00328670(int a);
int func_0030AC50(int r);
int func_0017E0A0(void);
void func_0017E010(int k);
int func_003F4D60(int k);
int func_003F1070(int k);
int func_00314030(int k, int f);
int func_002FBC90(int f, int t);
int func_002F8CB0(int f);

#define pad1_held() ((unsigned short)(pad1_ready() ? g_00500700[0].held : 0))

/* 0x00312E70, 0x160 bytes. Notice: message 0x118 for each listed value in turn (window 8). */
void func_00312E70(void)
{
    Notice *n = func_0030E2C0();
    int pos[5];

    switch (n->step) {
    case 3:
        func_0030E4E0(0);
        break;
    case 2:
        if (++n->c > 5) {
            if (++n->a < n->count)
                n->step = 0;
            else
                n->step = 3;
        }
        break;
    case 1:
        if (CLOSED_OK()) {
            func_003DB480(8, 5);
            n->c = 0;
            n->step = 2;
        }
        break;
    case 0:
        pos[4] = 0x80;
        func_003DB220(8, pos);
        func_003DB460(8, 5);
        func_001204B0(g_007B4E60, func_00390760(0x118), func_00372250(n->list[n->a]));
        SHOW();
        n->step = 1;
        break;
    }
}

/* Opens the two windows of a choice list. */
static void open_choice(void)
{
    int pos[5];

    pos[1] = 0x60;
    pos[2] = 0x96;
    pos[3] = 0x18;
    pos[4] = 0x80;
    pos[0] = 0;
    func_003DC090(0x10, pos);
    func_003DC0E0(0x10, 1, 1);
    pos[0] = 0x154;
    pos[1] = 0x68;
    pos[2] = 0x98;
    pos[3] = 0xD8;
    pos[4] = 0x80;
    func_003DC090(0x11, pos);
    func_003DC0E0(0x11, 2, 1);
}

/* 0x00312FD0, 0x12C bytes. The choice list of func_00328330's values (up to five), then `a`. */
void func_00312FD0(void)
{
    Notice *n = func_0030E2C0();
    int cnt = 0, k;

    for (k = 0; k < 5; k++) {
        u32 v = func_00328330(k);

        if (v < 100)
            n->list[cnt++] = v;
    }
    n->list[cnt] = n->a;
    n->count = cnt + 1;
    n->b = 0;
    open_choice();
}

/* 0x00313100, 0x12C bytes. The same with func_00328640's values. */
void func_00313100(void)
{
    Notice *n = func_0030E2C0();
    int cnt = 0, k;

    for (k = 0; k < 5; k++) {
        u32 v = func_00328640(k);

        if (v < 100)
            n->list[cnt++] = v;
    }
    n->list[cnt] = n->a;
    n->count = cnt + 1;
    n->b = 0;
    open_choice();
}

/* 0x00313230, 0x1F4 bytes. Runs the choice list: Up / Down move (wrapping on a press), OK picks
 * (returns the row), else -1. */
int func_00313230(void)
{
    Notice *n = func_0030E2C0();
    int cnt = n->count;
    u32 pressed, held;

    if (func_003DC2D0(0x10) != 0 || func_003DC2D0(0x11) != 0)
        return -1;
    pressed = pad1_pressed();
    held = pad1_held();
    if (pressed & 0x40) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        return n->b;
    }
    if (held & 0x4000) {
        if (n->b < cnt - 1) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            n->b++;
        } else if (pressed & 0x4000) {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            n->b = 0;
        }
    } else if (held & 0x1000) {
        if (n->b < 1) {
            if (pressed & 0x1000) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                n->b = (cnt - 1) & 0xFF;
            }
        } else {
            func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
            n->b--;
        }
    }
    return -1;
}

/* 0x00313430, 0x1C bytes, matching. */
int func_00313430(void)
{
    return func_00313230();
}

/* 0x00313450, 0x158 bytes. Notice: a choice between commands (0x3B-0x59 from func_00328330,
 * else from func_00328640); the chosen one (unless 5) is applied. */
void func_00313450(void)
{
    Notice *n = func_0030E2C0();
    int s = n->step, a = n->a, r;

    if (s == 2) {
        func_0030E4E0(0);
    } else if (s == 1) {
        if (a > 0x3A && a < 0x5A) {
            r = func_00313230();
            if (r != -1) {
                if (r != 5) {
                    func_00328440(r);
                    func_00328360(a);
                }
                n->step++;
            }
        } else {
            r = func_00313430();
            if (r != -1) {
                if (r != 5) {
                    func_00328750(r);
                    func_00328670(a);
                }
                n->step++;
            }
        }
    } else if (s == 0) {
        if (a > 0x3A && a < 0x5A)
            func_00312FD0();
        else
            func_00313100();
        n->step++;
    }
}

/* 0x003135B0, 0x210 bytes, matching. Runs the notice by its kind. */
void func_003135B0(void)
{
    switch (func_0030E2C0()->kind) {
    case 0: func_0030EFF0(); break;
    case 1: func_0030F170(); break;
    case 2: func_0030F240(); break;
    case 3: func_0030FBA0(); break;
    case 4: func_0030FC10(); break;
    case 5: func_0030FC60(); break;
    case 6: func_0030FD00(); break;
    case 7: func_0030FF70(); break;
    case 8: func_003100E0(); break;
    case 9: func_003104D0(); break;
    case 10: func_00310C80(); break;
    case 0xD: func_00310D90(); break;
    case 0xC: func_00311170(); break;
    case 0xE: func_00311260(); break;
    case 0xF: func_00311380(); break;
    case 0x10: func_00311490(); break;
    case 0x11: func_00312090(); break;
    case 0x12: func_00312400(); break;
    case 0x13: func_00312590(); break;
    case 0x14: func_00312660(); break;
    case 0x15: func_003127F0(); break;
    case 0x16: func_00312980(); break;
    case 0x17: func_00312E70(); break;
    case 0x18: func_00313450(); break;
    case 0x19: func_0030F150(); break;
    case 0x1A: func_0030F150(); break;
    case 0x1B: func_0030F150(); break;
    case 0x1C: func_0030F150(); break;
    case 0x1D: func_0030F150(); break;
    case 0xB: break;
    }
}

/* 0x003137C0, 0x108 bytes. The map music: by scenario (0-5), or by the player's leader's
 * region kind (scenarios 6-10). */
void func_003137C0(void)
{
    int s = func_00327C00(), m = 0x33;
    int kind = func_0030AC50(func_002F5CC0(func_00327820()));

    switch (s) {
    case 0: break;
    case 1: m = 0x34; break;
    case 2: m = 0x35; break;
    case 3: m = 0x36; break;
    case 4: m = 0x37; break;
    case 5: m = 0x38; break;
    case 6: case 7: case 8: case 9: case 10:
        switch (kind) {
        case 0: break;
        case 1: m = 0x34; break;
        case 2: case 3: m = 0x35; break;
        case 4: m = 0x36; break;
        case 5: case 6: m = 0x37; break;
        case 7: m = 0x38; break;
        }
        break;
    }
    if (m != func_0017E0A0())
        func_0017E010(m);
}

/* 0x003138D0, 0x1B4 bytes. The map tutorials (5 while one shows): 0x14, then for the player's
 * force from year 2 on those of commands 0x31 (9), 0x32 / 0x33 (10), 0x30 (0xB), 2 (0xF) and
 * 0x11 (0x10). */
int func_003138D0(void)
{
    if (func_003F4D60(0x14) != 0)
        return 5;
    if (func_00314030(0x31, func_00327D50()) != 0 && func_00327C70() > 1 && func_003F1070(9) != 0)
        return 5;
    if (func_00314030(0x32, func_00327D50()) != 0 || func_00314030(0x33, func_00327D50()) != 0) {
        if (func_00327C70() > 1 && func_003F1070(10) != 0)
            return 5;
    }
    if (func_00314030(0x30, func_00327D50()) != 0 && func_00327C70() >= 2 && func_003F1070(0xB) != 0)
        return 5;
    if (func_00314030(2, func_00327D50()) != 0 && func_00327C70() >= 2 && func_003F1070(0xF) != 0)
        return 5;
    if (func_00314030(0x11, func_00327D50()) != 0 && func_00327C70() >= 2 && func_003F1070(0x10) != 0)
        return 5;
    return 0;
}

/* 0x00313A90, 0x30 bytes, matching. Tutorial 0x15. */
int func_00313A90(void)
{
    return func_003F4D60(0x15) != 0 ? 5 : 0;
}

/* 0x00313AC0, 0x64 bytes, matching. The sound for result `k` (1: 0xD, 2: 0xE) of the player's force. */
void func_00313AC0(int f, int k)
{
    int s = 0xD;

    if (k == 0)
        return;
    if (k == 2)
        s = 0xE;
    if (func_002FB2A0(f) != 0 && func_0023A760(s) != 0) {
        func_00102960(1);
        func_0023A7D0(s);
    }
}

/* 0x00313B30-0x00313D50. Command `c`'s record fields (0x65 and others past 100 have fixed
 * values). */
int func_00313B30(u32 c)
{
    if (c == 0x65)
        return 0xF;
    if (c < 100)
        return g_00446AD0[c].unknown_10;
    return 0x12;
}

int func_00313B90(u32 c)
{
    if (c == 0x65)
        return 0x23;
    if (c < 100)
        return g_00446AD0[c].unknown_14;
    return 0x18;
}

int func_00313BF0(u32 c)
{
    if (c < 100)
        return g_00446AD0[c].unknown_04;
    return 5;
}

int func_00313C30(u32 c)
{
    if (c < 100)
        return g_00446AD0[c].unknown_0C;
    return 0;
}

int func_00313C70(u32 c)
{
    if (c < 100)
        return g_00446AD0[c].unknown_18;
    return 0xF;
}

int func_00313CB0(u32 c)
{
    if (c == 0x65)
        return 0xB;
    if (c < 100)
        return g_00446AD0[c].group;
    return 0xD;
}

short func_00313D10(u32 c)
{
    if (c < 100)
        return g_00446AD0[c].unknown_1E;
    return 0;
}

int func_00313D50(u32 c)
{
    if (c == 0x65)
        return 0xB;
    if (c < 100)
        return g_00446AD0[c].unknown_08;
    return 0;
}

/* 0x00313DB0, 0x168 bytes. Command `c`'s cost for force `f` (-1 for 0x65): commands 0x48-0x4E
 * cost half with the matching trait (5, 2, 4, else 3). */
int func_00313DB0(u32 c, int f)
{
    int v, t;

    if (c == 0x65)
        return -1;
    if (c >= 100)
        return 0;
    v = g_00446AD0[c].cost;
    if (func_002F8CB0(f) == 0 || c - 0x48 >= 7)
        return v;
    switch (c) {
    case 0x48: t = 5; break;
    case 0x49: t = 2; break;
    case 0x4A: t = 4; break;
    default: t = 3; break;
    }
    if (func_002FBC90(f, t) != 0)
        v = v / 2;
    return v;
}

/* 0x00313F20, 0x18 bytes, matching. */
int func_00313F20(int k)
{
    return g_00447608[k];
}

/* 0x00313F40, 0x38 bytes. Whether command `c` is 6, 8 or 0x1B. */
int func_00313F40(int c)
{
    if ((u32)(c - 6) < 0x16 && ((1 << (c - 6)) & 0x200005) != 0)
        return 1;
    return 0;
}

/* 0x00313F80, 0x38 bytes. Whether command `c` is 7, 9 or 0x1C. */
int func_00313F80(int c)
{
    if ((u32)(c - 7) < 0x16 && ((1 << (c - 7)) & 0x200005) != 0)
        return 1;
    return 0;
}

/* 0x00313FC0, 0x34 bytes. Command `c`'s cost for force `f` (0 instead of -1). */
int func_00313FC0(u32 c, int a, int f)
{
    int v = func_00313DB0(c, f);

    return v == -1 ? 0 : v;
}

/* 0x00314000, 0x28 bytes, matching. The cost of command record `p` (+0 force, +4 command, +8 value). */
int func_00314000(int *p)
{
    return func_00313FC0(p[1], p[2], p[0]);
}

int func_002F9190(int f);
int func_002FB120(int f);
int func_002FB220(int f);
int func_002FB1A0(int f);
int func_002FB430(int f);
int func_002FBA40(int f);
int func_002FC0C0(int f, int g);
int func_0030C020(int r);
int func_0030BDB0(int r);
int func_0030BEE0(int r);
void func_0030B330(void);
void func_0030B540(int r);
int func_002FA790(u32 f);
int func_002FBE00(int f);
int func_002FBDE0(int f);
int func_002FBDC0(int f);
int func_002FBE40(int f);
int func_002FBEC0(int f);
int func_002FBF00(int f);
int func_002FB100(int f);
int func_002F8630(u32 i, int f);
int func_002F8430(u32 i, int f);
int func_002F85E0(u32 i, int f);
int func_002F8480(u32 i, int f);
int func_001A0700(void);
int func_001A06D0(void);
int func_002F9390(int f, int k);
int func_002FC000(int f);
int func_003285D0(int c);
int func_00327E90(void);
int func_00328190(int k);
int func_002F3110(u32 i, int k);

/* 0x00314030, 0x8E0 bytes. Whether force `f` may give command `c`: it can pay, then each
 * command's own condition (another force for diplomacy, force value and officers for training,
 * traits, regions to act on, free stable slots, values below 400, ...). */
int func_00314030(int c, int f)
{
    int player = func_002FB2A0(f), cost = func_00313DB0(c, f), ok, g, a, b;

    if (cost != -1 && cost > func_002F9190(f))
        return 0;
    ok = 1;
    if (c == 0x35) {
        for (g = 0; g < 0x19; g++) {
            if (func_002F8CB0(g) != 0 && f != g)
                break;
        }
        if (!IS_FORCE(g))
            ok = 0;
    } else if (c == 0x2E) {
        ok = func_002FB120(f) == 0;
        for (g = 0; g < 0x19; g++) {
            if (func_002F8CB0(g) != 0 && f != g && func_002FB220(g) == 0) {
                int t = func_002FB1A0(g);

                if (t == f || t > 0x18)
                    break;
            }
        }
        if (!IS_FORCE(g))
            ok = 0;
    } else if (c == 0x2C || c == 0x2B) {
        ok = func_002FB120(f) == 0;
        for (g = 0; g < 0x19; g++) {
            if (func_002F8CB0(g) != 0 && f != g && func_002FB120(g) == 0)
                break;
        }
        if (!IS_FORCE(g))
            ok = 0;
    } else if (c == 0x2A || c == 0x29 || c == 0x28) {
        ok = func_002FABC0(f) > 299;
        if (func_002FB430(f) < 8)
            ok = 0;
    } else if (c == 0x27 || c == 0x26 || c == 0x25 || c == 0x24) {
        ok = func_002FABC0(f) > 99;
        if (func_002FB430(f) < 2)
            ok = 0;
    } else if (c == 0x10 || c == 0xF || c == 0xE) {
        if (func_002FBA40(f) == 0)
            ok = 0;
    } else if (c == 0x3A) {
        for (g = 0; g < 0x19; g++) {
            if (func_002F8CB0(g) != 0 && f != g && func_002FC0C0(f, g) != 0x19)
                break;
        }
        if (!IS_FORCE(g))
            ok = 0;
    } else if (c == 0x39) {
        ok = func_0030C020(func_002FB2D0(f)) != 0;
        func_0030B330();
    } else if (c == 0x38) {
        if (func_002FA790(f) != 0)
            ok = 0;
    } else if (c == 0x37) {
        ok = func_0030BDB0(func_002FB2D0(f)) != 0;
        func_0030B330();
    } else if (c == 0x36) {
        ok = func_0030BEE0(func_002FB2D0(f)) != 0;
        func_0030B330();
    } else if (c == 0x34) {
        ok = func_0030C020(func_002FB2D0(f));
        func_0030B330();
        return ok != 0;
    } else if (c == 0x33) {
        if (func_002FBC90(f, 8) == 0)
            ok = 0;
    } else if (c == 0x32) {
        if (func_002FBC90(f, 7) == 0)
            ok = 0;
    } else if (c == 0x31) {
        if (func_002FBE00(f) == 0)
            ok = 0;
    } else if (c == 0x30) {
        if (func_002FBDE0(f) == 0)
            ok = 0;
    } else if (c == 0x2F || c == 0x2D) {
        if (func_002FB100(f) == 0)
            ok = 0;
    } else if (c == 0x22) {
        a = func_002F7D90(0, (int (*)(u32, int, int))func_002F8630, f, 0, 0);
        b = func_002F7D90(0, (int (*)(u32, int, int))func_002F8430, f, 0, 1);
        if (a == 0 && b == 0)
            ok = 0;
    } else if (c == 0x20) {
        a = func_002F7D90(0, (int (*)(u32, int, int))func_002F85E0, 0, 0, 0);
        b = func_002F7D90(0, (int (*)(u32, int, int))func_002F8430, f, 0, 1);
        if (a == 0 && b == 0)
            ok = 0;
    } else if (c == 0x1F) {
        a = func_002F7D90(0, (int (*)(u32, int, int))func_002F8630, f, 0, 0);
        func_0030B540(func_002FB2D0(f));
        b = func_002F7D90(0, (int (*)(u32, int, int))func_002F8480, 0, 0, 1);
        func_0030B330();
        if (a == 0 && b == 0)
            ok = 0;
    } else if (c == 0x12) {
        if (func_001A0700() == 0)
            ok = 0;
    } else if (c == 0x11) {
        ok = func_002FBE40(f) != 0;
        if (func_001A06D0() == 0)
            ok = 0;
    } else if (c == 8) {
        if (player == 0)
            ok = 0;
    } else if (c == 0xD) {
        if (func_002F9390(f, 0) > 399 && func_002F9390(f, 1) > 399 && func_002F9390(f, 2) > 399)
            ok = 0;
    } else if (c == 0xC) {
        if (func_002F9390(f, 2) > 399)
            ok = 0;
    } else if (c == 0xB) {
        if (func_002F9390(f, 1) > 399)
            ok = 0;
    } else if (c == 10) {
        if (func_002F9390(f, 0) > 399)
            ok = 0;
    } else if (c == 5 || c == 4 || c == 3) {
        if (func_002FC000(f) == 0)
            ok = 0;
    } else if (c == 2) {
        if (func_002FBDC0(f) == 0)
            ok = 0;
    } else if (c > 0x3A && c < 0x5A && (player == 0 || func_003285D0(c) != 0)) {
        ok = 0;
    }
    return ok;
}

/* 0x00314910, 0x4C bytes. Whether the player's fame is at least `v` (`up`) or at most `v`. */
int func_00314910(int v, int up)
{
    int m = func_00327E90();

    if (up == 0)
        return !(v < m);
    return !(m < v);
}

/* 0x00314960, 0x224 bytes. The commands available now (by their unlock rule: always, unlocked,
 * a trait of the player's force, fame grades), into `out`; their count. */
int func_00314960(int *out)
{
    int n = 0, c;

    for (c = 0; c < 100; c++) {
        int on = 0;

        switch (func_00313C70(c)) {
        case 0: on = 1; break;
        case 2: on = func_00328190(c) != 0; break;
        case 3: on = func_002FBDC0(func_00327D50()) != 0; break;
        case 4: on = func_002FBDE0(func_00327D50()) != 0; break;
        case 5: on = func_002FBE00(func_00327D50()) != 0; break;
        case 6: on = func_002FBE40(func_00327D50()) != 0; break;
        case 7: on = func_00314910(0, 1) != 0; break;
        case 8: on = func_00314910(5, 1) != 0; break;
        case 9: on = func_00314910(-5, 0) != 0; break;
        case 10: on = func_00314910(10, 1) != 0; break;
        case 0xB: on = func_00314910(-10, 0) != 0; break;
        case 0xC: on = func_00314910(-15, 0) != 0; break;
        case 0xD: on = func_002FBEC0(func_00327D50()) != 0; break;
        case 0xE: on = func_002FBF00(func_00327D50()) != 0; break;
        }
        if (on) {
            *out++ = c;
            n++;
        }
    }
    return n;
}

/* 0x00314BA0, 0x9C bytes. Whether one of officers `l` (`n`) has `v` among its three values. */
int func_00314BA0(int v, u32 *l, int n)
{
    int k, j;

    for (k = 0; k < n; k++, l++) {
        for (j = 0; j < 3; j++) {
            if (v == func_002F3110(*l, j))
                return 1;
        }
    }
    return 0;
}

/* One of a command's four results (0x184 bytes). */
typedef struct {
    int kind;                /* +0x000 (0x16 = none) */
    int v[0x1F];             /* +0x004 values (v[0x1E] = a sub-kind) */
    char text[0x104];        /* +0x080 its message */
} CmdResult;

/* A command being run (0x690 bytes; see func_00315510). */
typedef struct {
    int f;                   /* +0x00 the force */
    int cmd;                 /* +0x04 (100 = none) */
    int target;              /* +0x08 */
    int d;                   /* +0x0C */
    int any;                 /* +0x10 regions marked */
    int region[25];          /* +0x14 the regions shown */
    CmdResult res[4];        /* +0x78 */
} CmdRecord;

int func_002FBD60(int f);
int func_00327870(void);
int func_002FAD20(int f);
int func_0011B740(int fame);
int func_002FBF20(int f, int a, int *out);
void func_003F4D20(int k);
int func_0030AE80(int r);
int func_0030AD80(int r);

/* 0x00314C40, 0x5A0 bytes. Whether officer `i` (lists `a` / `b` of the candidates) may give
 * command `c`: commands needing an officer's skill need it (the computer: one of the listed
 * officers; the player: the officer itself unless unlocked, some at 15%), the unlock rule must
 * hold, some commands are the player's only, the free and event commands not already chosen;
 * then func_00314030. */
int func_00314C40(int c, u32 i, u32 *a, int b)
{
    int f = func_002F4080(i), player = func_002FB2A0(f), ok = 0, k;

    if (c == 0x13)
        return 0;
    if (func_00313C30(c) != 0) {
        if (player == 0) {
            if (func_00314BA0(c, a, b) != 0)
                ok = 1;
        } else if (func_00328190(c) == 0) {
            for (k = 0; k < 3; k++) {
                if (c == func_002F3110(i, k)) {
                    ok = 1;
                    break;
                }
            }
        } else if (((c < 0x3B || c > 0x59) && (c < 0x5A || c > 0x62) && c != 0x65)
                   || func_0030CB50(0xF) != 0) {
            ok = 1;
        }
        if (!ok)
            return 0;
    }
    ok = 0;
    switch (func_00313C70(c)) {
    case 0: case 1: case 2: ok = 1; break;
    case 3: ok = func_002FBDC0(f) != 0; break;
    case 4: ok = func_002FBDE0(f) != 0; break;
    case 5: ok = func_002FBE00(f) != 0; break;
    case 6: ok = func_002FBE40(f) != 0; break;
    case 7: ok = player == 0 || func_00314910(0, 1) != 0; break;
    case 8: ok = player == 0 || func_00314910(5, 1) != 0; break;
    case 9: ok = player == 0 || func_00314910(-5, 0) != 0; break;
    case 10: ok = player == 0 || func_00314910(10, 1) != 0; break;
    case 0xB: ok = player == 0 || func_00314910(-10, 0) != 0; break;
    case 0xC: ok = player == 0 || func_00314910(-15, 0) != 0; break;
    case 0xD: ok = func_002FBEC0(f) != 0; break;
    case 0xE: ok = func_002FBF00(f) != 0; break;
    }
    if (!ok)
        return 0;
    if (c == 5 || c == 4 || c == 3) {
        if (func_002FC000(f) == 0)
            ok = 0;
    } else {
        if ((c == 0x10 || c == 0xF || c == 0xE) && func_002FBA40(f) == 0)
            return 0;
        if (c == 0x3A || c == 0x2E || c == 0x37 || c == 0x34 || c == 0x33 || c == 0x32 || c == 0x31
            || c == 0x2A || c == 0x29 || c == 0x28 || c == 0x27 || c == 0x26 || c == 0x25 || c == 0x24
            || c == 0x1C || c == 0x1B || c == 0x12 || c == 0x11 || c == 9 || c == 8 || c == 6 || c == 2) {
            if (player == 0)
                return 0;
        }
        if (c > 0x3A && c < 0x5A) {
            if (player == 0) {
                ok = 0;
            } else {
                for (k = 0; k < 5; k++) {
                    if (c == (int)func_00328330(k)) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
        if ((c > 0x59 && c < 99) || c == 0x65) {
            if (player == 0) {
                ok = 0;
            } else {
                for (k = 0; k < 5; k++) {
                    if (c == (int)func_00328640(k)) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
    }
    return ok ? func_00314030(c, f) : 0;
}

/* 0x003151E0, 0xC8 bytes. Whether command `c` is one of the free commands needing no officer
 * (0x3B-0x40, 0x43-0x47, 0x4F, 0x50, 0x52, 0x59). */
int func_003151E0(int c)
{
    if (c == 0x59 || c == 0x52 || c == 0x50 || c == 0x4F || c == 0x47 || c == 0x46 || c == 0x45
        || c == 0x44 || c == 0x43 || c == 0x40 || c == 0x3F || c == 0x3E || c == 0x3D || c == 0x3C
        || c == 0x3B)
        return 1;
    return 0;
}

/* 0x003152B0, 0x240 bytes. The commands `lo`-`hi` force `f`'s officers know (not the free ones),
 * each kept by chance (30% / 50% / 100% by group), sorted by group then half shuffled; into
 * `out`, their count. */
int func_003152B0(int f, int *out, int lo, int hi)
{
    int n = 0, cnt, c, x, y;

    func_002F7B10();
    cnt = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, 1);
    if (cnt == 0)
        return 0;
    func_002FB3B0(func_00327D50());
    for (c = lo; c <= hi; c++) {
        if (func_003151E0(c) == 0 && func_00314BA0(c, func_002F7B10(), cnt) != 0) {
            int g = func_00313BF0(c), pct = 100;

            if (g == 1)
                pct = 0x32;
            else if (g == 0)
                pct = 0x1E;
            if (func_0030CB50(pct) != 0)
                out[n++] = c;
        }
    }
    if (n > 1) {
        for (x = 0; x < n; x++) {
            int gx = func_00313BF0(out[x]);

            for (y = x + 1; y < n; y++) {
                int gy = func_00313BF0(out[y]);

                if (gy < gx) {
                    int t = out[x];

                    out[x] = out[y];
                    out[y] = t;
                    gx = gy;
                }
            }
        }
        for (x = 0; x < n / 2; x++) {
            int p = func_0030CB00(n), q = func_0030CB00(n);

            if (p != q) {
                int t = out[p];

                out[p] = out[q];
                out[q] = t;
            }
        }
    }
    return n;
}

/* 0x003154F0, 0x20 bytes, matching. The same for commands 0x3B-0x59. */
int func_003154F0(int f, int *out)
{
    return func_003152B0(f, out, 0x3B, 0x59);
}

/* 0x00315510, 0x8C bytes, matching. Clears command record `p` for force `f`. */
void func_00315510(CmdRecord *p, int f)
{
    int k;

    p->f = f;
    p->cmd = 100;
    p->target = -1;
    p->d = -1;
    p->any = 0;
    func_0011ED38(p->region, 0, 100);
    for (k = 0; k < 4; k++) {
        p->res[k].kind = 0x16;
        func_0011ED38(p->res[k].v, 0, 0x7C);
        func_0011ED38(p->res[k].text, 0, 0x102);
    }
}

/* 0x003155A0, 0x20 bytes, matching. Result `k` of command record `p`. */
CmdResult *func_003155A0(CmdRecord *p, int k)
{
    return &p->res[k];
}

/* 0x003155C0, 0x120 bytes, matching. Marks regions `l` (`n`) of command record `p` as shown. */
void func_003155C0(CmdRecord *p, int *l, int n)
{
    int k;

    p->any = 1;
    for (k = 0; k < n; k++)
        p->region[l[k]] = 1;
}

/* 0x003156E0, 0x98 bytes. Command result: 300 gold at the home region (message 0). */
int func_003156E0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int home = func_002FB2D0(p->f);

    r->kind = 0;
    r->v[0] = 300;
    func_001204B0(r->text, func_00390760(0), func_0030ABF0(home));
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

/* 0x00315780, 0x210 bytes. Command result: gold from the regions (100-400 by size, plus fame:
 * 20-300 for infamy, up to 150 for fame, plus 200; message 1). */
int func_00315780(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], v, m = 0;

    v = func_002FB3B0(p->f) * 100 < 400 ? func_002FB3B0(p->f) * 100 : 400;
    if (v < 100)
        v = 100;
    if (func_002FB2A0(p->f) != 0) {
        int e = func_00327E90();

        if (e < 0) {
            m = e * -0x14;
            if ((m < 300 ? m : 300) < 0x14)
                m = 0x14;
            else if (m > 299)
                m = 300;
        } else {
            m = e * 10;
            if (m > 0x95)
                m = 0x96;
        }
    }
    r->kind = 0;
    r->v[0] = (m + v + 200) / 10 * 10;
    func_001204B0(r->text, func_00390760(1), func_0030CB80(r->v[0]));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00315990, 0x2D4 bytes. Command result: trade gold, a small sum (message 2, sub-kind 2) or by
 * chance a large one (message 3, sub-kind 1), from the force's values and the player's fame. */
int func_00315990(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], a = func_002FBD60(p->f), b = func_002FAD20(p->f), k = 1, v, x;

    if (func_002FB2A0(p->f) != 0 && (u32)func_00327870() < 0x19F)
        k = 2;
    if (func_0030CB50(b / 0x12 + a * 0x14 * (func_0030CB00(k) + 1) + 0xF) == 0) {
        x = 100;
        if (func_002FB2A0(p->f) != 0)
            x = func_0011B740(func_00327E90()) * 10;
        v = (func_0030CB00(4) * 0x32 + a * 0x32 + 300 + x) / 10 * 10;
        func_001204B0(r->text, func_00390760(2), func_0030CB80(v));
        r->v[0x1E] = 2;
    } else {
        int y, z;

        x = 200;
        if (func_002FB2A0(p->f) != 0)
            x = func_0011B740(func_00327E90()) * 0x14;
        y = func_0030CB00(5);
        z = func_0030CB00(b + 1);
        v = (z / 10 * 10 + y * 0x32 + (a + 1) * 500 + x) / 10 * 10;
        func_001204B0(r->text, func_00390760(3), func_0030CB80(v));
        r->v[0x1E] = 1;
    }
    r->kind = 0;
    r->v[0] = v;
    func_003155C0(p, reg, func_002FBF20(p->f, 1, reg));
    func_003F4D20(0xF);
    return 0;
}

/* Command result: raises the target region's +0x12 value by `add` (at most its room; message
 * 0x56 with the new value, at most 100). */
static int raise_region(CmdRecord *p, int base)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg = p->target, add = func_002FAD20(p->f) / 200 + base, tot;

    if (func_0030AE80(reg) - func_0030AD80(reg) < add)
        add = func_0030AE80(reg) - func_0030AD80(reg);
    r->kind = 0xD;
    r->v[0] = reg;
    r->v[1] = add;
    tot = add + func_0030AD80(reg) < 100 ? add + func_0030AD80(reg) : 100;
    func_001204B0(r->text, func_00390760(0x56), func_0030ABF0(reg), func_0030CB80(add), func_0030CB80(tot));
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x00315C70, 0x15C bytes. The same with a base of 5. */
int func_00315C70(CmdRecord *p)
{
    return raise_region(p, 5);
}

/* 0x00315DD0, 0x15C bytes. The same with a base of 10. */
int func_00315DD0(CmdRecord *p)
{
    return raise_region(p, 10);
}
