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
