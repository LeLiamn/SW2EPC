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
#define g_7000015C (*(u32 *)0x7000015C)   /* (scratchpad) the random seed */

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

int func_00329540(int k);
int func_00319C50(int *out, int f, int k);
void func_001A0020(int k);
u8 *func_0019FBC0(int k);
void func_0038BE90(u8 *h);
void func_0038BE00(int h, int a, int b);
int func_002FBDA0(int f);
int func_002FBD80(int f);
int func_002F9480(int f, int k);
const char *func_00372630(int k);

/* Raise of force `f`'s value `k` (0-2, at most 400): by 20 at most. */
static int raise_by_20(int f, int k)
{
    int t = 400 - func_002F9390(f, k) < 0x15 ? 400 - func_002F9390(f, k) : 0x14;

    return t < 0 ? 0 : t;
}

/* 0x00315F30, 0x9C bytes. Command result: kind 0xC with the force's value / 200 + 5
 * (message 0x57). */
int func_00315F30(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    r->v[1] = func_002FAD20(p->f) / 200 + 5;
    func_001204B0(r->text, func_00390760(0x57));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00315FD0, 0xE0 bytes. Command result: kind 0xC (message 0x58), with a success by chance from
 * the player's fame (100% below 3, 30% below 6, 10% below 9). */
int func_00315FD0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], pct = 0;

    if (func_002FB2A0(p->f) != 0) {
        int e = func_00327E90();

        if (e < 3)
            pct = 100;
        else if (e < 6)
            pct = 0x1E;
        else if (e < 9)
            pct = 10;
    }
    r->v[0xE] = 0;
    if (pct != 0 && func_0030CB50(pct) != 0)
        r->v[0xE] = 1;
    r->kind = 0xC;
    func_00120928(r->text, func_00390760(0x58));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x003160B0, 0x74 bytes. Command result: 500 gold (message 4). */
int func_003160B0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0;
    r->v[0] = 500;
    func_00120928(r->text, func_00390760(4));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00316130, 0xE8 bytes. Whether a famous horse can be found (fame 15 or more, unlocked);
 * the horse into `out`. */
int func_00316130(int *out)
{
    if (func_00327E90() < 0xF)
        return 0;
    if (func_00329540(0x35) == 0)
        return 0;
    if (func_00329540(0x34) != 0)
        return 0;
    if (func_00319C50(out, func_00327D50(), 8) == 0)
        return 0;
    if (func_002F4080(1) == func_00327D50() || (u32)func_00327870() < 0x19F
        || func_00327B70(func_00327D50()) != 0)
        return 1;
    return 0;
}

/* 0x00316220, 0x1F4 bytes. Command result: kind 0x12 (message 0x59) with a success by chance
 * (fame and force value), and maybe a famous horse found (kind 0x13, message 0x15). */
int func_00316220(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[27], h, e = func_00327E90(), pct;

    if (func_002FABC0(p->f) < 0x1F5)
        pct = e < 9 ? 100 : e == 9 ? 0x1E : 5;
    else
        pct = e <= 9 ? 100 : 0x32;
    r->v[0xE] = 0;
    if (pct != 0 && func_0030CB50(pct) != 0)
        r->v[0xE] = 1;
    r->kind = 0x12;
    func_001204B0(r->text, func_00390760(0x59));
    if (func_00316130(&h) != 0) {
        r = func_003155A0(p, 1);
        r->kind = 0x13;
        r->v[1] = h;
        func_001A0020(0xC);
        func_001204B0(r->text, func_00390760(0x15), func_0019FBC0(h) + 0x13);
        func_0038BE90(func_0019FBC0(h));
        func_0038BE00(h, 0, 0);
        func_003BA8F0(0x17, -1, -1, -1, -1);
    }
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00316420, 0x2F0 bytes. Command result: gold (1000 + 50 per region + 0-200, message 5), with
 * the trait func_002FBA40 a kind 0xC result (message 0xF), and the three values raised by up to
 * 20 each (message 0xC). */
int func_00316420(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], v, t, a, b, c, m;

    v = func_0030CB00(5) * 0x32 + func_002FB3B0(p->f) * 0x32 + 1000;
    r->kind = 0;
    r->v[0] = v / 10 * 10;
    func_001204B0(r->text, func_00390760(5), func_0030CB80(v));
    t = func_002FBA40(p->f);
    if (t != 0) {
        r = func_003155A0(p, 1);
        r->kind = 0xC;
        func_001204B0(r->text, func_00390760(0xF));
    }
    if (func_002F9390(p->f, 0) < 400 || func_002F9390(p->f, 1) < 400 || func_002F9390(p->f, 2) < 400) {
        a = raise_by_20(p->f, 0);
        b = raise_by_20(p->f, 1);
        c = raise_by_20(p->f, 2);
        r = func_003155A0(p, (t != 0) + 1);
        r->kind = 1;
        r->v[0] = a;
        r->v[1] = b;
        r->v[2] = c;
        m = b < a ? a : b;
        if (m <= c)
            m = c;
        func_001204B0(r->text, func_00390760(0xC), func_0030CB80(m));
        func_003BA8F0(0x18, -1, -1, -1, -1);
    }
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* Command result: force value `k` raised by its trait * 10 + 20 (message 0xB), and its grade
 * change (kind 0x15, message 0xD). */
static int raise_value(CmdRecord *p, int k, int trait)
{
    CmdResult *r = func_003155A0(p, 0);
    int t = trait * 10 + 0x14, old, now, home;

    if (400 - func_002F9390(p->f, k) <= t)
        t = 400 - func_002F9390(p->f, k);
    if (t < 0)
        t = 0;
    r->kind = 1;
    r->v[0] = k == 0 ? t : 0;
    r->v[1] = k == 1 ? t : 0;
    r->v[2] = k == 2 ? t : 0;
    func_001204B0(r->text, func_00390760(0xB), func_00372630(k), func_0030CB80(t));
    old = func_002F9480(p->f, k);
    now = (t + func_002F9390(p->f, k) < 400 ? t + func_002F9390(p->f, k) : 400) / 100 + 1;
    if (old != now) {
        r = func_003155A0(p, 1);
        r->kind = 0x15;
        func_001204B0(r->text, func_00390760(0xD), func_00372250(k + 10), func_0030CB80(now));
    }
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

/* 0x00316710, 0x1CC bytes. The same for value 0 (trait func_002FBDA0). */
int func_00316710(CmdRecord *p)
{
    return raise_value(p, 0, func_002FBDA0(p->f));
}

/* 0x003168E0, 0x1CC bytes. The same for value 1 (trait func_002FBDA0). */
int func_003168E0(CmdRecord *p)
{
    return raise_value(p, 1, func_002FBDA0(p->f));
}

/* 0x00316AB0, 0x1CC bytes. The same for value 2 (trait func_002FBD80). */
int func_00316AB0(CmdRecord *p)
{
    return raise_value(p, 2, func_002FBD80(p->f));
}

/* 0x00316C80, 0x2C8 bytes. Command result: all three values raised by up to 20 (message 0xC),
 * then each grade change (kind 0x15, message 0xD). */
int func_00316C80(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int a = raise_by_20(p->f, 0), b = raise_by_20(p->f, 1), c = raise_by_20(p->f, 2);
    int m, k, slot = 1, home;

    r->kind = 1;
    r->v[0] = a;
    r->v[1] = b;
    r->v[2] = c;
    m = b < a ? a : b;
    if (c >= m)
        m = c;
    func_001204B0(r->text, func_00390760(0xC), func_0030CB80(m));
    for (k = 0; k < 3; k++) {
        int t = k == 1 ? b : k == 2 ? c : a, old, now;

        old = func_002F9480(p->f, k);
        now = (t + func_002F9390(p->f, k) < 400 ? t + func_002F9390(p->f, k) : 400) / 100 + 1;
        if (old != now) {
            r = func_003155A0(p, slot);
            r->kind = 0x15;
            func_001204B0(r->text, func_00390760(0xD), func_00372250(k + 10), func_0030CB80(now));
            slot++;
        }
    }
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

int func_002FBE20(int f);
u32 func_001A0670(void);
void func_001A0650(u8 *buf);
int func_002F6C20(u32 i, int k);
int func_002F6D10(u32 i, int k);
int func_002F6E00(u32 i, int k);
int func_002F6EF0(u32 i, int k);
void func_002CAD90(u8 *out);
void func_002F87D0(u32 *l, int n, int (*less)(u32, u32, int, int), int a, int b);

/* 0x00316F50, 0x94 bytes. Command result: region `target` gets kind 0xB value 1 (message 0xE). */
int func_00316F50(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg = p->target;

    r->kind = 0xB;
    r->v[0] = reg;
    r->v[1] = 1;
    func_001204B0(r->text, func_00390760(0xE), func_0030ABF0(reg));
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x00316FF0, 0x94 bytes. The same with value 2 (message 0x10D). */
int func_00316FF0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg = p->target;

    r->kind = 0xB;
    r->v[0] = reg;
    r->v[1] = 2;
    func_001204B0(r->text, func_00390760(0x10D), func_0030ABF0(reg));
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x00317090, 0x70 bytes. Command result: kind 0xC (message 0xF). */
int func_00317090(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(0xF));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* The player's bonus (6 when `on`, else 2). */
#define PLAYER_BONUS(f, on) (func_002FB2A0(f) != 0 && (on) ? 6 : 2)

/* 0x00317100, 0x280 bytes. Command result: looking for a horse; found by chance (the best
 * func_002F50F0 / 4 + trait * 40 + bonuses, 58-100%) when the stable has room: a new horse
 * (kind 0xE, message 0x10), else nothing (kind 0x15, message 0x11). */
int func_00317100(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 *o = func_002F7B10();
    int reg[28], n, t, best = 0, k, a, b, v;
    char name[32];
    u8 buf[0x24];

    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, p->f, 0, 1);
    t = func_002FBE20(p->f);
    for (k = 0; k < n; k++, o++) {
        int s = func_002F50F0(*o);

        if (best < s)
            best = s;
    }
    a = PLAYER_BONUS(p->f, (u32)func_00327870() < 0x19F);
    b = PLAYER_BONUS(p->f, func_00327B70(p->f) != 0);
    v = best / 4 + t * 0x28 + a * b;
    v = v < 0x3B ? 0x3A : v;
    v = v > 100 ? 100 : v;
    if (func_0030CB50(v) == 0 || func_001A06D0() == 0) {
        r->kind = 0x15;
        func_001204B0(r->text, func_00390760(0x11));
        r->v[0x1E] = 2;
    } else {
        u32 h = func_001A0670();
        u8 *rec;

        r->v[1] = h;
        func_001A0650(buf);
        buf[4] = h;
        rec = func_0019FBC0(h);
        func_0011EB80(rec, buf, 0x24);
        r->kind = 0xE;
        func_00120928(name, (char *)func_0019FBC0(h) + 0x13);
        func_001204B0(r->text, func_00390760(0x10), name);
        func_0038BE90(rec);
        r->v[0x1E] = 1;
        func_0038BE00(h, 0, 0);
    }
    func_003155C0(p, reg, func_002FBF20(p->f, 2, reg));
    func_003F4D20(0x10);
    return 0;
}

/* Officer `i`'s riding skills (kinds 4 and 0xE in both skill lists). */
static int riding(u32 i)
{
    int s = 0, k;

    for (k = 0; k < 4; k++) {
        int c = func_002F6C20(i, k);

        if (c == 4 || c == 0xE)
            s += func_002F6D10(i, k);
    }
    for (k = 0; k < 10; k++) {
        int c = func_002F6E00(i, k);

        if (c == 4 || c == 0xE)
            s += func_002F6EF0(i, k);
    }
    return s;
}

/* 0x00317380, 0x1B8 bytes, matching. Order: the better rider first, then the higher func_002F34E0, then
 * the lower number. */
int func_00317380(int i, int j)
{
    int a = 0, b = 0, k, x, y;

    for (k = 0; k < 4; k++) {
        int c = func_002F6C20(i, k);

        if (c == 4 || c == 0xE)
            a += func_002F6D10(i, k);
        c = func_002F6C20(j, k);
        if (c == 4 || c == 0xE)
            b += func_002F6D10(j, k);
    }
    for (k = 0; k < 10; k++) {
        int c = func_002F6E00(i, k);

        if (c == 4 || c == 0xE)
            a += func_002F6EF0(i, k);
        c = func_002F6E00(j, k);
        if (c == 4 || c == 0xE)
            b += func_002F6EF0(j, k);
    }
    if (b < a)
        return 1;
    if (a < b)
        return 0;
    x = func_002F34E0(i);
    y = func_002F34E0(j);
    if (y < x)
        return 1;
    if (x < y)
        return 0;
    return i < j;
}

/* 0x00317540, 0x364 bytes. Command result: training the stable's horse `target` with the best
 * rider (kind 0xE, message 0x12): experience from the rider, the force's value and bonuses,
 * at most 99999 in all. */
int func_00317540(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u8 st[12], *hr;
    u32 *o, best;
    int h, n, s, base, fv, a, b, t, gain, tot, home;

    func_002F7B10();
    func_002CAD90(st);
    h = st[p->target];
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, p->f, 0, 0);
    o = func_002F7B10();
    func_002F87D0(o, n, (int (*)(u32, u32, int, int))func_00317380, -1, -1);
    best = o[0];
    s = riding(best);
    hr = func_0019FBC0(h);
    if (s < 8 || s - (int)hr[8] < 2)
        base = s - (int)hr[8] < 2 ? 1000 : 0x5DC;
    else
        base = 2000;
    fv = func_002FABC0(p->f);
    a = PLAYER_BONUS(p->f, (u32)func_00327870() < 0x19F);
    b = PLAYER_BONUS(p->f, func_00327B70(p->f) != 0);
    t = func_002FBE20(p->f);
    gain = (t * 500 + base + fv / 2 + func_0030CB00(a) * 100 + func_0030CB00(b) * 100) * 2;
    r->v[4] = *(int *)func_0019FBC0(h);
    r->v[3] = gain;
    tot = gain + *(int *)func_0019FBC0(h) < 99999 ? gain + *(int *)func_0019FBC0(h) : 99999;
    func_0038BE00(h, best, gain);
    r->kind = 0xE;
    r->v[1] = h;
    r->v[2] = best;
    func_001204B0(r->text, func_00390760(0x12), (char *)func_0019FBC0(h) + 0x13, func_0030CB80(r->v[3]),
                  func_0030CB80(tot));
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

/* Command result: officer `target` gets `v` soldiers (kind 10, message `m`). */
static int give_soldiers(CmdRecord *p, int m, int v)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->target;
    int reg;

    r->kind = 10;
    r->v[0] = i;
    r->v[1] = v;
    func_001204B0(r->text, func_00390760(m), func_002F2890(i));
    reg = func_002F5CC0(i);
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x003178C0, 0xA0 bytes. 1000 soldiers (message 0x16). */
int func_003178C0(CmdRecord *p)
{
    return give_soldiers(p, 0x16, 1000);
}

/* 0x00317960, 0xA0 bytes. 2000 soldiers (message 0x17). */
int func_00317960(CmdRecord *p)
{
    return give_soldiers(p, 0x17, 2000);
}

/* 0x00317A00, 0xA4 bytes. Back to its most (message 0x18). */
int func_00317A00(CmdRecord *p)
{
    return give_soldiers(p, 0x18, func_002F38F0(p->target));
}

/* Command result: every officer gets `v` soldiers (kind 0xC, message `m`). */
static int all_soldiers(CmdRecord *p, int m, int v)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    r->v[1] = v;
    func_001204B0(r->text, func_00390760(m));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00317AB0, 0x78 bytes. 500 soldiers each (message 0x19). */
int func_00317AB0(CmdRecord *p)
{
    return all_soldiers(p, 0x19, 500);
}

/* 0x00317B30, 0x78 bytes. 1000 each (message 0x1A). */
int func_00317B30(CmdRecord *p)
{
    return all_soldiers(p, 0x1A, 1000);
}

/* 0x00317BB0, 0x78 bytes. 2000 each (message 0x1B). */
int func_00317BB0(CmdRecord *p)
{
    return all_soldiers(p, 0x1B, 2000);
}

extern u32 g_00428348[];                 /* experience needed per level */
extern const char g_00447840[];          /* an empty text */

void func_002F7C40(u32 *l, int n);       /* shuffles a list */
int func_002F8740(u32 i, int f);
int func_002F8710(u32 i, int f);
void func_002F7290(u32 i);
int func_00308890(u32 i, int f);
int func_00308B40(u32 i, int f);
int func_003086C0(u32 i, int f);
int func_002F4A70(u32 i);
u32 func_002FB6F0(int f);
int func_002F41E0(u32 i);
int func_003276C0(void);
int func_002F3F20(u32 i);
int func_0030B3B0(int *out);

/* 0x00317C30, 0x104 bytes. Command result: kind 0xC, (the square root of the player's fame
 * value + 2 + 0-root) hundreds (message 0x1C). */
int func_00317C30(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], v = 0, s, x;

    if (func_002FB2A0(p->f) != 0)
        v = func_0011B740(func_00327E90());
    s = (int)sqrtf((float)v);
    x = func_0030CB00(s + 1);
    r->kind = 0xC;
    v = (s + 2 + x) * 100;
    r->v[1] = v;
    func_001204B0(r->text, func_00390760(0x1C), func_0030CB80(v));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00317D40, 0xCC bytes. Command result: kind 0xC (message 0x1D), a success by chance from the
 * player's fame (100%, 30% at 9, 5% above). */
int func_00317D40(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28], pct = 0;

    if (func_002FB2A0(p->f) != 0) {
        int e = func_00327E90();

        pct = 100;
        if (e == 9)
            pct = 0x1E;
        else if (e > 9)
            pct = 5;
    }
    r->v[0xE] = 0;
    if (pct != 0 && func_0030CB50(pct) != 0)
        r->v[0xE] = 1;
    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(0x1D));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x00317E10, 0x70 bytes. Command result: kind 0xC (message 0x1E). */
int func_00317E10(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(0x1E));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* The second result: officer `i` joins force `f` (kind 0x15, message 0x72). */
static void joined(CmdRecord *p, u32 i)
{
    CmdResult *r = func_003155A0(p, 1);
    char a[32], b[32];

    r->kind = 0x15;
    func_00120928(a, func_002F2890(i));
    func_00120928(b, func_002F8DB0(p->f));
    func_001204B0(r->text, func_00390760(0x72), a, b);
    r->v[0x1E] = 1;
}

/* 0x00317E80, 0x340 bytes. Command result: searching for an officer (0x1D in the force's
 * regions, else anywhere): one found by chance (40% / 60% named, plus the force's value and
 * bonuses) is met (0x20 refuses, 0x21 joins), else none (0x1F). */
int func_00317E80(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 *o = func_002F7B10(), i = 0x19F;
    int reg[27], n, found = 0, fv, a = 0, b = 0, k, at;

    if (p->cmd == 0x1D)
        n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8740, p->f, 0, 0);
    else
        n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8710, 0, 0, 0);
    if (n != 0) {
        func_002F7C40(o, n);
        fv = func_002FABC0(p->f);
        if (func_002FB2A0(p->f) != 0 && (u32)func_00327870() < 0x19F)
            a = 0x14;
        if (func_002FB2A0(p->f) != 0 && func_00327B70(p->f) != 0)
            b = 10;
        for (k = 0; k < n; k++, o++) {
            i = *o;
            if (func_0030CB50((func_002F3F20(i) == 0 ? 0x28 : 0x3C) + b + fv + a) != 0) {
                found = 1;
                break;
            }
        }
    }
    if (found) {
        func_002F7290(i);
        at = func_002F5CC0(i);
        if (func_00308890(i, p->f) == 0) {
            r->kind = 0x15;
            r->v[0] = 0x19F;
            func_001204B0(r->text, func_00390760(0x20), func_0030ABF0(at), func_002F2890(i));
            r->v[0x1E] = 2;
        } else {
            r->kind = 2;
            r->v[0] = i;
            func_001204B0(r->text, func_00390760(0x21), func_0030ABF0(at), func_002F2890(i));
            joined(p, i);
        }
        func_003155C0(p, &at, 1);
    } else {
        r->v[0x1E] = 2;
        r->kind = 0x15;
        r->v[0] = 0x19F;
        func_001204B0(r->text, func_00390760(0x1F));
        func_003155C0(p, reg, func_002FB320(p->f, reg));
    }
    return 0;
}

/* Persuading officer `target` (by `test`): refused (`no`) or joins (`yes` from a force,
 * 0x24 when free). */
static int persuade(CmdRecord *p, int (*test)(u32, int), int no, int yes)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->target;
    int at;
    char a[28], b[32];

    if (test(i, p->f) == 0) {
        r->kind = 0x15;
        r->v[0] = 0x19F;
        func_001204B0(r->text, func_00390760(no), func_002F2890(i));
        r->v[0x1E] = 2;
    } else {
        int g;

        r->kind = 2;
        r->v[0] = i;
        g = func_002F4080(i);
        if (IS_FORCE(g)) {
            func_00120928(a, func_002F8DB0(g));
            func_00120928(b, func_002F2890(i));
            func_001204B0(r->text, func_00390760(yes), b, a);
        } else {
            func_001204B0(r->text, func_00390760(0x24), func_002F2890(i));
        }
        joined(p, i);
    }
    at = func_002F5CC0(i);
    func_003155C0(p, &at, 1);
    return 0;
}

/* 0x003181C0, 0x1DC bytes. Command result: persuading an officer (func_00308B40; 0x22 / 0x23). */
int func_003181C0(CmdRecord *p)
{
    return persuade(p, func_00308B40, 0x22, 0x23);
}

/* 0x003183A0, 0x1C0 bytes. Command result: an officer joins at once (kind 2, message 0x72; the
 * list of five joined, most recent first), or none (kind 0x15, message 0x25). */
int func_003183A0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[27], k, empty = 1, at;
    u32 i;
    char a[32], b[32];

    for (k = 0; k < 5; k++) {
        if (r->v[k] != 0) {
            empty = 0;
            break;
        }
    }
    if (empty) {
        r->v[0] = 0x19F;
        r->v[1] = 0x19F;
        r->v[2] = 0x19F;
        r->v[3] = 0x19F;
        r->v[4] = 0x19F;
    }
    i = p->target;
    if (i < 0x19F) {
        r->kind = 2;
        for (k = 0; k < 5; k++) {
            if ((u32)r->v[k] < 0x19F && (u32)r->v[k] == i) {
                r->v[k] = r->v[0];
                break;
            }
        }
        r->v[0] = i;
        func_00120928(a, func_002F2890(i));
        func_00120928(b, func_002F8DB0(p->f));
        func_001204B0(r->text, func_00390760(0x72), a, b);
        at = func_002F5CC0(i);
        func_003155C0(p, &at, 1);
        r->v[0x1E] = 1;
    } else {
        r->kind = 0x15;
        func_001204B0(r->text, func_00390760(0x25));
        func_003155C0(p, reg, func_0030B3B0(reg));
        r->v[0x1E] = 2;
    }
    func_0030B330();
    return 0;
}

/* 0x00318560, 0xA4 bytes. Whether officer `i` accepts force `f` (always without a role; else
 * when tied, or when its loyalty grade is below the player's fame). */
int func_00318560(u32 i, int f)
{
    int v;

    if (func_002F3DC0(i) == 0)
        return 1;
    v = func_003086C0(i, f);
    if (v == -1) {
        int m = func_002FB2A0(f) == 0 ? 0 : func_00327E90();

        v = func_002F4A70(i) < m ? 100 : 0;
    }
    return v == 100;
}

/* 0x00318610, 0x1DC bytes. Command result: inviting an officer (func_00318560; 0x26 / 0x27). */
int func_00318610(CmdRecord *p)
{
    return persuade(p, (int (*)(u32, int))func_00318560, 0x26, 0x27);
}

/* 0x003187F0, 0x298 bytes. Command result: officer `target` trains with the force's best officer
 * (kind 8, message 0x29): experience 1000-2000 by their level gap, plus the force's value and
 * bonuses; its new level (at most 0x13). */
int func_003187F0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->target, tot;
    int a = func_002F41E0(func_002FB6F0(p->f)), b = func_002F41E0(i), base = 1000, fv, k = 2, x, y, gain, lv;
    int at;

    if (a < 0x12 || a - b < 2) {
        if (a - b > 1)
            base = 0x5DC;
    } else {
        base = 2000;
    }
    fv = func_002FABC0(p->f);
    if (func_002FB2A0(p->f) != 0 && (u32)func_00327870() < 0x19F)
        k = 6;
    if (func_002FB2A0(p->f) != 0 && func_00327B70(p->f) != 0)
        k = 6;
    x = func_0030CB00(k);
    y = func_0030CB00(2);
    r->kind = 8;
    r->v[0] = i;
    gain = base + fv + x * 100 + y * 100;
    r->v[1] = gain;
    tot = gain + func_002F34E0(i) < 99999 ? gain + func_002F34E0(i) : 99999;
    func_001204B0(r->text, func_00390760(0x29), func_002F2890(i), func_0030CB80(gain), func_0030CB80(tot));
    func_002F41E0(i);
    for (lv = 0; lv <= 0x12; lv++) {
        if (g_00428348[lv] <= tot && tot < g_00428348[lv + 1])
            break;
    }
    r->v[2] = lv > 0x12 ? 0x13 : lv;
    at = func_002F5CC0(i);
    func_003155C0(p, &at, 1);
    return 0;
}

/* 0x00318A90, 0x108 bytes. A duel roll between officers `i` and `j` on the stat of training
 * command `c`: half the stat plus 0-99 each; whether `i` wins. */
int func_00318A90(u32 i, u32 j, int c, int *pa, int *pb)
{
    int si = 0, sj = 0;

    switch (c) {
    case 0x24: case 0x28:
        si = func_002F5410(i);
        sj = func_002F5410(j);
        break;
    case 0x25: case 0x29:
        si = func_002F4F60(i);
        sj = func_002F4F60(j);
        break;
    case 0x26: case 0x2A:
        si = func_002F4DD0(i);
        sj = func_002F4DD0(j);
        break;
    }
    *pa = si / 2 + func_0030CB00(100);
    *pb = sj / 2 + func_0030CB00(100);
    return *pb <= *pa;
}

/* 0x00318BA0, 0x148 bytes. Command result: a duel between officers `d` and `target` (kind 0xF,
 * message 0x10C): the winner first, a random order next, and whether it was close. */
void func_00318BA0(CmdRecord *p)
{
    int c = p->cmd, sa, sb, lo;
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->d, j = p->target;
    char a[40], b[32];

    r->kind = 0xF;
    r->v[0] = i;
    r->v[1] = j;
    func_00120928(a, func_002F2890(i));
    func_00120928(b, func_002F2890(j));
    func_001204B0(r->text, func_00390760(0x10C), a, b);
    if (c == 0x27)
        c = r->v[6];
    if (func_00318A90(i, j, c, &sa, &sb) == 0) {
        r->v[2] = j;
        r->v[3] = i;
    } else {
        r->v[2] = i;
        r->v[3] = j;
    }
    if (func_0030CB00(2) == 0) {
        r->v[4] = j;
        r->v[5] = i;
    } else {
        r->v[4] = i;
        r->v[5] = j;
    }
    lo = sb;
    if (sa < sb) {
        lo = sa;
        sa = sb;
    }
    r->v[0x1D] = sa < lo * 2;
}

/* 0x00318CF0, 0x00318D40, 0x00318D90, 0x44 bytes each. The duel, at the home region. */
int func_00318CF0(CmdRecord *p)
{
    int home;

    func_00318BA0(p);
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

int func_00318D40(CmdRecord *p)
{
    int home;

    func_00318BA0(p);
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

int func_00318D90(CmdRecord *p)
{
    int home;

    func_00318BA0(p);
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

/* 0x00318DE0, 0x74 bytes. The same on a random stat (commands 0x24-0x26). */
int func_00318DE0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int home;

    r->v[6] = func_003276C0() % 3 + 0x24;
    func_00318BA0(p);
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    return 0;
}

/* 0x00318E60, 0x110 bytes. Command result kind 0x10: eight of the force's officers at random,
 * the other slots empty. */
void func_00318E60(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int n, k;
    u32 *o;

    r->kind = 0x10;
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, p->f, 0, 0);
    o = func_002F7B10();
    func_002F7C40(o, n);
    for (k = 0; k < 8; k++)
        r->v[6 + k] = o[k];
    r->v[2] = 0x19F;
    r->v[3] = 0x19F;
    r->v[0xE] = 0;
    for (k = 0xF; k < 0x1D; k++)
        r->v[k] = 0x19F;
    func_001204B0(r->text, g_00447840);
}

/* 0x00318F70, 0x00318FC0, 0x00319010, 0x44 bytes each. The same, over all regions. */
int func_00318F70(CmdRecord *p)
{
    int reg[28];

    func_00318E60(p);
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

int func_00318FC0(CmdRecord *p)
{
    int reg[28];

    func_00318E60(p);
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

int func_00319010(CmdRecord *p)
{
    int reg[28];

    func_00318E60(p);
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* A tie with force `target` (kind 3, tie `k`, message `m`), both homes shown. */
static int tie_result(CmdRecord *p, int k, int m)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, homes[2];

    r->kind = 3;
    r->v[0] = g;
    r->v[1] = k;
    r->v[2] = 1;
    func_001204B0(r->text, func_00390760(m), func_002F8DB0(func_002FB2A0(p->f) == 0 ? p->f : g));
    homes[0] = func_002FB2D0(p->f);
    homes[1] = func_002FB2D0(g);
    func_003155C0(p, homes, 2);
    return 0;
}

/* 0x00319060, 0xD0 bytes. Command result: an alliance (tie 4, message 0x3C). */
int func_00319060(CmdRecord *p)
{
    return tie_result(p, 4, 0x3C);
}

/* 0x00319130, 0xD0 bytes. Command result: a truce (tie 0xC, message 0x3D). */
int func_00319130(CmdRecord *p)
{
    return tie_result(p, 0xC, 0x3D);
}

/* 0x00319200, 0x98 bytes, matching. Command result: kind 0xC about force `target` (message 0x3E). */
int func_00319200(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, reg[28];

    r->kind = 0xC;
    r->v[0] = g;
    func_001204B0(r->text, func_00390760(0x3E), func_002F8DB0(g));
    func_003155C0(p, reg, func_002FB320(g, reg));
    return 0;
}

int func_002FA490(int f);
int func_0030C1C0(int x, int g);
int func_002FB470(int f);
int func_002FB500(int f, int g);
int func_002F95C0(int f);
int func_002F9690(int k, int *out);
int func_002F9730(int f, int k, int gold);
int func_002F68E0(u32 i);
const char *func_003725F0(int k);
void func_002F94C0(int f, short v);
int func_00328230(void);
const char *func_002F2BB0(u32 i);

/* 0x003192A0, 0x4A4 bytes. Command result: force `f` demands force `target`'s submission (kind
 * 4; at war or not): a computer target gives in when clearly weaker (sizes, officers and values,
 * weighed by fame, bonuses and its kind) and by the fame's chance; messages 0x3F-0x42. */
int func_003192A0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, ok = 1, war = func_002F9C90(p->f, g) == 3, homes[2];
    char a[40], b[32];

    if (func_002FB2A0(g) == 0) {
        int fame = 0, fg, fv, ba = 1, bb = 1, fo, fn, fr, go, gn, gr, w, div, mul, gap, t;

        if (func_002FB2A0(p->f) != 0)
            fame = func_00327E90();
        fg = 3;
        if (fame < 3)
            fg = 1;
        else if (fame < 10)
            fg = 2;
        fv = func_002FABC0(p->f);
        if (func_002FB2A0(p->f) != 0 && (u32)func_00327870() < 0x19F)
            ba = 2;
        if (func_002FB2A0(p->f) != 0 && func_00327B70(p->f) != 0)
            bb = 2;
        fo = func_002FB470(p->f);
        fn = func_002FB430(p->f);
        fr = func_002FB3B0(p->f);
        go = func_002FB470(g);
        gn = func_002FB430(g);
        gr = func_002FB3B0(g);
        t = func_002FA490(g);
        w = t == 2 ? 0x32 : t == 1 ? 0x1E : 10;
        if (!war)
            w >>= 1;
        div = func_002FB500(p->f, g) == 0 ? 10 : 1;
        mul = war ? 7 : 4;
        if (func_002FABC0(g) < func_002FABC0(p->f))
            gap = (func_002FABC0(p->f) - func_002FABC0(g)) / 100 + 1;
        else
            gap = 1;
        ok = 0;
        if (((gn + gr) * 100 + go / 100) * w
                < (gap * ((fn + fr) * 100 + fo / 100) * bb * ba * fg * (fv / 300 + 1)) / div
            && gr * mul < fr) {
            int c = func_0011B740(fame);

            ok = func_0030CB00(10) < c;
        }
    }
    r->kind = 4;
    r->v[0] = g;
    r->v[2] = war;
    func_00120928(a, func_002F8DB0(g));
    func_00120928(b, func_002F8DB0(p->f));
    if (ok) {
        r->v[1] = 1;
        func_001204B0(r->text, func_00390760(war == 0 ? 0x41 : 0x3F), a, b);
        r->v[0x1E] = 1;
    } else {
        r->v[1] = 0;
        func_001204B0(r->text, func_00390760(war == 0 ? 0x42 : 0x40), a, b);
        r->v[0x1E] = 2;
    }
    homes[0] = func_002FB2D0(p->f);
    homes[1] = func_002FB2D0(g);
    func_003155C0(p, homes, 2);
    return 0;
}

/* 0x00319750, 0xA4 bytes. Command result: kind 0xC about force `target` (message 0x43). */
int func_00319750(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, homes[2];

    r->kind = 0xC;
    r->v[0] = g;
    func_001204B0(r->text, func_00390760(0x43), func_002F8DB0(g));
    homes[0] = func_002FB2D0(p->f);
    homes[1] = func_002FB2D0(g);
    func_003155C0(p, homes, 2);
    return 0;
}

/* Whether officer `i` is one of the special leaders (0xD, 0x9F, 0xA2, 0xA3). */
#define SPECIAL_LEAD(i) ((i) == 0xD || (i) == 0x9F || (u32)((i) - 0xA2) < 2)

/* 0x00319800, 0x3D4 bytes. Command result: force `target` changes its policy (kind 0x11, message
 * 0x45) when its regions' +0x12 values pay for the next one (policy 0xD's successor by its
 * leader, needing fame -15 or 15 for the player; else func_002F9730), or keeps a cheaper one;
 * else nothing (kind 0xC, message 0x44). */
int func_00319800(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, reg[26], s = 0, x, pol, cost, cost2, ok = 0, ok2, nx, next, cur;
    u32 lead;

    for (x = 0; x < 0x19; x++) {
        x = func_0030C1C0(x, g);
        if (x > 0x18)
            break;
        s += func_0030AD80(x);
    }
    pol = func_002F95C0(g);
    cost = func_002F9690(pol == -1 ? 0 : pol + 1, &next);
    if (cost <= s) {
        if (pol == 0xD) {
            if (func_002FB2A0(g) != 0)
                ok = func_00327E90() == -0xF || func_00327E90() == 0xF;
        } else {
            ok = 1;
        }
    }
    cost2 = func_002F9690(pol, &cur);
    if (pol == 0xE)
        ok = 0;
    nx = pol != 0xE;
    ok2 = nx && cost2 <= s;
    lead = func_002F8F20(g);
    if (ok) {
        if (pol == 0xD) {
            if (SPECIAL_LEAD(lead)) {
                next = 0x62;
            } else {
                int k = func_002F68E0(lead);

                next = k == 0 ? 99 : k == 1 ? 0x61 : k == 2 ? 0x62 : 0x61;
            }
        } else {
            next = func_002F9730(g, next, s);
            if (next == 100)
                ok = 0;
        }
    } else if (nx && cost2 <= s) {
        cur = func_002F9730(g, cur, s);
        if (cur == 100)
            ok2 = 0;
    }
    if (ok || ok2) {
        r->kind = 0x11;
        r->v[0] = g;
        r->v[1] = cur;
        if (ok)
            r->v[1] = next;
        func_001204B0(r->text, func_00390760(0x45), func_002F2890(lead), func_003725F0(r->v[1]));
        r->v[0x1E] = 1;
        func_002F94C0(r->v[0], (short)r->v[1]);
        if (func_00328230() == 0 && next == 0x62 && SPECIAL_LEAD(lead)) {
            r = func_003155A0(p, 1);
            r->kind = 0x15;
            func_001204B0(r->text, func_00390760(0x8D), func_002F2BB0(lead));
        }
    } else {
        r->kind = 0xC;
        r->v[1] = -1;
        func_001204B0(r->text, func_00390760(0x44));
        r->v[0x1E] = 2;
    }
    func_003155C0(p, reg, func_002FB320(g, reg));
    func_003F4D20(0xB);
    return 0;
}

/* 0x00319BE0, 0x70 bytes. Command result kind 0x14 for `target`, at the home region. */
int func_00319BE0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int home;

    r->kind = 0x14;
    r->v[0] = p->target;
    func_001204B0(r->text, g_00447840);
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
    func_003F4D20(9);
    return 0;
}

extern u32 g_00414BA0[3];                /* by command: a horse kind wanted */
extern int g_00414BB0[2][3];             /* by command: the skills it may teach the force */

int func_002FAAD0(int f);
void func_002FAB40(int f, int v);
void func_002FAA50(int f, int k, int v);

/* 0x00319C50, 0x110 bytes. Whether the stable has room for a horse of command `c`'s kind and
 * has none of it yet; the first free slot into `out` (-1 for none). */
int func_00319C50(int *out, int f, int c)
{
    u32 kinds[4];
    int row, n = 0, k;

    kinds[0] = g_00414BA0[0];
    kinds[1] = g_00414BA0[1];
    kinds[2] = g_00414BA0[2];
    row = c == 0x32 ? 0 : c == 0x33 ? 1 : 2;
    *out = -1;
    for (k = 0; k < 4; k++) {
        if (func_0019FBC0(k)[4] == 4) {
            if (*out == -1)
                *out = k;
        } else {
            if (kinds[row] == func_0019FBC0(k)[5])
                return 0;
            n++;
        }
    }
    return n != 4;
}

/* 0x00319D70, 0x130 bytes. The skill of command `c`'s three force `f` knows least (below its
 * limit): the skill into `skill`, its level into `lv`; 0 when none. */
int func_00319D70(int *skill, int *lv, int f, int c)
{
    int t[6], *row, k, found = 0;

    for (k = 0; k < 6; k++)
        t[k] = (&g_00414BB0[0][0])[k];
    *lv = 4;
    row = t + (c != 0x32) * 3;
    for (k = 0; k < 3; k++) {
        int s = row[k], l = func_002FA9E0(f, s);

        if (l < func_0030AB50(s) && l < *lv) {
            *lv = l;
            found = 1;
            *skill = s;
        }
    }
    return found;
}

/* 0x00319EA0, 0x19C bytes. Whether command `c` brings force `f` a horse or a skill as well
 * (below the value limits, by chance from its size and fame). */
int func_00319EA0(int f, int c)
{
    int h, s, l, fame, r, v, pct;

    if (func_002FABC0(f) >= 1000 || func_002FAAD0(f) >= 1000)
        return 0;
    if (func_00319C50(&h, f, c) == 0 && func_00319D70(&s, &l, f, c) == 0)
        return 0;
    fame = func_002FB2A0(f) == 0 ? 0 : func_0011B740(func_00327E90());
    r = func_002FB3B0(f);
    v = func_002FABC0(f);
    pct = r + fame * 3 + 10;
    if (pct < 0xB)
        pct = 0xB;
    if (pct > 0x4E)
        pct = 0x4F;
    if (c == 0x33) {
        pct = v / 100 + r + fame * 2 + 10;
        if (pct < 0xB)
            pct = 0xB;
        if (pct > 0x49)
            pct = 0x4A;
    }
    return func_0030CB50(pct) != 0;
}

/* 0x0031A040, 0x490 bytes. Command result: a market (gold, message 6) or by chance a good trade
 * (more gold, message 7, maybe more through func_00319EA0); whether more follows. */
int func_0031A040(CmdRecord *p)
{
    int f = p->f, c = p->cmd, ok = 0, fame, fv, b = 0, n, s, m, pct, root, x, y;
    CmdResult *r;

    func_002F8F20(f);
    r = func_003155A0(p, 0);
    fame = func_002FB2A0(f) == 0 ? 0 : func_0011B740(func_00327E90());
    fv = func_002FABC0(f);
    if (func_002FB2A0(f) != 0 && (u32)func_00327870() < 0x19F)
        b = 5;
    if (func_002FB2A0(f) != 0 && func_00327B70(f) != 0)
        b = 5;
    n = func_002FB430(f);
    s = func_002FB3B0(f);
    m = c == 0x33 ? 4 : 2;
    b += fv / 100 + fame * m;
    root = (int)sqrtf((float)(n + s));
    pct = b + root + 0x28 < 100 ? b + root + 0x28 : 100;
    if (c == 0x33 && pct < 0x29)
        pct = 0x29;
    if (func_0030CB50(pct) == 0) {
        x = func_002FB2A0(f) == 0 ? 100 : func_0011B740(func_00327E90()) * 10;
        y = func_0030CB00(4);
        b = func_002FB2A0(f) == 0 ? 0 : (500 - x + y * -0x32) / 0x14 * 10;
        r->kind = 0;
        r->v[0] = (b + y * 0x32 + x + 500) / 10 * 10;
        func_001204B0(r->text, func_00390760(6), func_00372250(c), func_0030CB80(r->v[0]));
        r->v[0x1E] = 2;
    } else {
        x = 200;
        if (func_002FB2A0(f) != 0)
            x = (func_00327E90() < 0 ? 0x14 : 10) * func_0011B740(func_00327E90());
        y = func_0030CB00(5);
        r->kind = 0;
        r->v[0] = f;
        r->v[0] = (y * 0x32 + x + 0x5DC) / 10 * 10;
        func_001204B0(r->text, func_00390760(7), func_00372250(c), func_0030CB80(r->v[0]));
        ok = func_00319EA0(f, c) != 0;
        r->v[0x1E] = 1;
    }
    return ok;
}

/* A market command (`c`, horse sound `snd`, trait list `t`): on a good trade the force's value
 * grows (up to 5, message 10), then a horse (message 9) or a skill (message 8). */
static int market(CmdRecord *p, int c, int snd, int t)
{
    CmdResult *r = func_003155A0(p, 1);
    int reg[25], h, s, l, inc, a, b;

    if (func_0031A040(p) != 0) {
        r->kind = 0x15;
        a = func_002FABC0(p->f);
        b = func_002FAAD0(p->f);
        inc = 1000 - (1000 - b < 1000 - a ? b : a);
        if (inc >= 5)
            inc = 5;
        r->v[0] = p->f;
        r->v[1] = inc;
        func_001204B0(r->text, func_00390760(10), func_0030CB80(inc));
        func_002FAB40(p->f, inc + func_002FAAD0(p->f));
        if (func_00319C50(&h, p->f, c) != 0) {
            r = func_003155A0(p, 2);
            r->kind = 0xE;
            r->v[0] = p->f;
            r->v[1] = h;
            func_001A0020(snd);
            func_001204B0(r->text, func_00390760(9), func_0019FBC0(h) + 0x13);
            func_0038BE90(func_0019FBC0(h));
            func_0038BE00(h, 0, 0);
        } else if (func_00319D70(&s, &l, p->f, c) != 0) {
            r = func_003155A0(p, 2);
            r->kind = 0x15;
            r->v[0] = p->f;
            r->v[1] = s;
            r->v[2] = l;
            func_001204B0(r->text, func_00390760(8), g_0042D3E0[s], func_0030CB80(l + 1));
            func_002FAA50(p->f, s, l + 1);
        }
    }
    func_003155C0(p, reg, func_002FBF20(p->f, t, reg));
    func_003F4D20(10);
    return 0;
}

/* 0x0031A4D0, 0x26C bytes. Command 0x32's market. */
int func_0031A4D0(CmdRecord *p)
{
    return market(p, 0x32, 0xD, 7);
}

/* 0x0031A740, 0x26C bytes. Command 0x33's market. */
int func_0031A740(CmdRecord *p)
{
    return market(p, 0x33, 0xF, 8);
}

int func_00308F50(u32 i, int f);
int func_00308B70(int v);
int func_0030C250(int r);
int func_0030C440(int r, int f);
int func_0030ACE0(int r);
int func_002F6FE0(u32 i, int k);
int func_002F4450(u32 i);
int func_002F3380(u32 i);
int func_002F8B60(u32 i, u32 j);
int func_002F8110(u32 i, int f);
int func_002F7900(u32 i, u32 j);

/* Whether officer `i` would flee (100% - its loyalty grade * 10): -1, else 0. */
static int flees(u32 i)
{
    int pct = func_002F4A70(i) * -10 + 100;

    if (pct > 100)
        pct = 100;
    if (pct < 1)
        pct = 0;
    return func_0030CB50(pct) != 0 ? -1 : 0;
}

/* 0x0031A9B0, 0x154 bytes. Command result: winning officer `target` over (kind 5, message 0x46),
 * or failing (kind 0x15, message 0x47; it may flee). */
int func_0031A9B0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->target;
    int at;

    if (func_00308F50(i, p->f) == 0) {
        int esc = flees(i);

        r->kind = 0x15;
        r->v[1] = i;
        r->v[2] = esc;
        func_001204B0(r->text, func_00390760(0x47), func_002F2890(i));
        r->v[0x1E] = 2;
    } else {
        r->kind = 5;
        r->v[0] = i;
        func_001204B0(r->text, func_00390760(0x46), func_002F2890(i));
        r->v[0x1E] = 1;
    }
    at = func_002F5CC0(i);
    func_003155C0(p, &at, 1);
    return 0;
}

/* 0x0031AB10, 0x388 bytes. Command result: stirring up region `target`: the chance falls with
 * its troops and its officers' soldiers (and the player's fame); success (kind 5, message 0x48
 * / 0x49, with infamy a chance of more), else failure (kind 0x15, message 0x4A; one of its
 * officers may flee). */
int func_0031AB10(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg = p->target, cap = func_0030ACE0(reg), t = func_0030B090(reg), n, s = 0, k, bonus = 0, div, v;
    u32 *o;

    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, reg, 0, 1);
    o = func_002F7B10();
    for (k = 0; k < n; k++, o++)
        s += func_002F3770(*o);
    if (func_002FB2A0(p->f) != 0 && func_00327B70(p->f) != 0)
        bonus = 0x14;
    div = func_0030C440(reg, p->f) == 0 ? 5 : 1;
    s = s / 1000 + n * 5;
    v = ((bonus + 100 + t * -10) * (0xC - t * 10 / cap)) / 10;
    v = s < v ? v - s : 0;
    v /= div;
    if (func_0030C250(reg) != 0)
        v = func_00308B70(v);
    if (func_0030CB50(v) == 0) {
        int esc = 0;
        u32 i = 0x19F;

        if (n != 0) {
            i = func_002F7B10()[func_0030CB00(n)];
            esc = flees(i);
        }
        r->kind = 0x15;
        r->v[1] = i;
        r->v[2] = esc;
        r->v[0] = 0x19;
        func_001204B0(r->text, func_00390760(0x4A), func_0030ABF0(reg));
        r->v[0x1E] = 2;
    } else {
        int e = func_00327E90();

        r->v[3] = e < 0 ? func_0030CB50(func_0011B740(e) << 1) != 0 : 0;
        r->kind = 5;
        r->v[0] = reg;
        if (func_002FB2A0(func_0030AFF0(reg)) == 0)
            func_001204B0(r->text, func_00390760(0x48), func_0030ABF0(reg));
        else
            func_001204B0(r->text, func_00390760(0x49), func_0030ABF0(reg));
        func_002FB2A0(p->f);
        r->v[0x1E] = 1;
    }
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x0031AEA0, 0x8D0 bytes. Command result: inciting region `target`'s first officer to rebel
 * (not when tied to its leader; by chance from its liking, values and service): the region's
 * other officers follow (when tied to it, or by chance) or stay; the rebels win (kind 7,
 * message 0x4C) when their soldiers beat the others' with the troops, else lose (message 0x4D);
 * failure: kind 0x15, message 0x4E. */
int func_0031AEA0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg = p->target, ok = 0, n, k, nj = 1, nr = 0, sj = 0, sr = 0;
    int joined[7], rest[8];
    u32 *o, i, lead;
    char rn[32], nm[32];

    r->v[2] = 0x19F;
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, reg, 0, 0);
    o = func_002F7B10();
    if (n == 0) {
        int m = func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, reg, 0, 0);

        func_002F87D0(o, m, (int (*)(u32, u32, int, int))func_002F8B60, -1, -1);
    } else {
        func_002F87D0(o, n, (int (*)(u32, u32, int, int))func_002F8B60, -1, -1);
    }
    i = o[0];
    lead = func_002F8F20(func_002F4080(i));
    if (func_002F77A0(i, lead) == 0 && func_002F78C0(i, lead) == 0 && func_002F7900(i, lead) == 0) {
        int kg = 0, x, s, a, b, y, mul, e, v;

        if (func_002FB2A0(p->f) != 0) {
            int m = func_00327E90();

            kg = m < 1 ? 0 : m < 10 ? 1 : 2;
        }
        x = func_002F6FE0(i, kg);
        s = func_002FB3B0(p->f);
        a = func_002F4450(i);
        b = func_002F4450(i);
        y = func_00327C70() - func_002F3380(i);
        mul = func_002FABC0(p->f) < 0x1F5 ? 1 : 2;
        e = func_002F4A70(i);
        v = (x / 4 + s / 4 + mul * a * b - y / 2) / (e + 1);
        if (v > 0x51)
            v = 0x51;
        if (v < 1)
            v = 0;
        if (func_0030C250(reg) != 0)
            v = func_00308B70(v);
        ok = func_0030CB50(v);
    }
    func_00120928(rn, func_0030ABF0(reg));
    func_00120928(nm, func_002F2890(i));
    if (ok == 0) {
        r->v[0x1E] = 2;
        r->kind = 0x15;
        r->v[0] = 0x19;
        func_001204B0(r->text, func_00390760(0x4E), rn);
    } else {
        int m, t;

        r->v[0x1E] = 1;
        m = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, reg, 0, 1);
        o = func_002F7B10();
        joined[0] = i;
        for (k = 0; k < m; k++, o++) {
            u32 x = *o;
            int go;

            if (x == i)
                continue;
            if (func_002F77A0(x, lead) != 0 || func_002F78C0(x, lead) != 0 || func_002F7900(x, lead) != 0) {
                go = 0;
            } else if (func_002F77A0(x, i) != 0 || func_002F78C0(x, i) != 0 || func_002F7900(x, i) != 0) {
                go = 1;
            } else {
                int kg = 0;

                if (func_002FB2A0(p->f) != 0) {
                    int e = func_00327E90();

                    if (e < -10)
                        kg = 2;
                    else if (e < 0)
                        kg = 1;
                }
                go = func_0030CB50((7 - func_002F4A70(i)) * 7
                                   + (func_002F6FE0(x, kg) / 5 + func_002F4450(x) * func_002F4450(x)
                                      - (func_00327C70() - func_002F3380(x)) / 2)) != 0;
            }
            if (go)
                joined[nj++] = x;
            else
                rest[nr++] = x;
        }
        for (k = 0; k < nj; k++)
            sj += func_002F3770(joined[k]);
        for (k = 0; k < nr; k++)
            sr += func_002F3770(rest[k]);
        t = func_0030B090(reg);
        r->kind = 6;
        func_001204B0(r->text, func_00390760(0x4B), nm, rn);
        r->v[0] = reg;
        r->v[2] = i;
        r = func_003155A0(p, 1);
        for (k = 3; k < 0xD; k++)
            r->v[k] = 0x19F;
        if (sr * (t + 10) / 10 < sj) {
            r->kind = 7;
            r->v[0] = reg;
            r->v[2] = i;
            r->v[1] = 1;
            for (k = 0; k < nj; k++)
                r->v[3 + k] = joined[k];
            for (k = 0; k < nr; k++)
                r->v[8 + k] = rest[k];
            func_001204B0(r->text, func_00390760(0x4C), nm, rn);
        } else {
            r->kind = 0x15;
            r->v[0] = reg;
            r->v[2] = i;
            r->v[1] = 0;
            func_001204B0(r->text, func_00390760(0x4D), nm, rn);
        }
    }
    func_003155C0(p, &reg, 1);
    return 0;
}

/* 0x0031B7A0, 0x98 bytes, matching. Command result: kind 0xC about force `target` (message 0x4F). */
int func_0031B7A0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, reg[28];

    r->kind = 0xC;
    r->v[0] = g;
    func_001204B0(r->text, func_00390760(0x4F), func_002F8DB0(g));
    func_003155C0(p, reg, func_002FB320(g, reg));
    return 0;
}

extern int (*g_00414BD0[100])(CmdRecord *p);   /* the command results by command */

int func_00328570(void);
int func_00327C40(void);
void func_0030C920(int *l, int n);
void func_002F7410(u32 i);
int func_0030AD20(int r, int k);
int func_00328970(void);
void func_002F9130(int f, int v);
int func_003276A0(void);
int func_00314000(int *p);
int func_0038C6B0(CmdRecord *p);
void func_003BA520(int c);
int func_0031C5C0(CmdRecord *p, int k);
void func_002F32F0(u32 i, u32 t);
void func_002F4B70(u32 i, int v);
int func_002F57F0(int w);
int func_0030AB20(u8 w);
u8 *func_00328B30(int w);
void func_0030B030(int r, int v);

/* 0x0031B840, 0x70 bytes. Command result: kind 0xC (message 0x50). */
int func_0031B840(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(0x50));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x0031B8B0, 0x190 bytes. Command result: winning officer `target` over (kind 5, message 0x51,
 * 0x52 for the player), or failing (kind 0x15, message 0x53; it may flee). */
int func_0031B8B0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    u32 i = p->target;
    int at;

    if (func_00308F50(i, p->f) == 0) {
        int esc = flees(i);

        r->kind = 0x15;
        r->v[1] = i;
        r->v[2] = esc;
        func_001204B0(r->text, func_00390760(0x53), func_002F2890(i));
        r->v[0x1E] = 2;
    } else {
        r->kind = 5;
        r->v[0] = i;
        func_001204B0(r->text, func_00390760(func_002FB2A0(p->f) == 0 ? 0x51 : 0x52), func_002F2890(i));
        r->v[0x1E] = 1;
    }
    at = func_002F5CC0(i);
    func_003155C0(p, &at, 1);
    return 0;
}

/* 0x0031BA40, 0x1F0 bytes. Command result: setting force `target` against its tied force
 * (func_002FC0C0): by chance from their sizes (50% at least) when not already at odds; success
 * kind 0xC (message 0x54), failure kind 0x15 (message 0x55). */
int func_0031BA40(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int g = p->target, h = func_002FC0C0(p->f, g), reg[28], pct;
    char a[32], b[32];

    if (func_002FB500(g, h) == 0) {
        int sa = func_002FB3B0(g), sb = func_002FB3B0(h);

        if (sb < sa)
            pct = sb * 100 / sa / 2;
        else
            pct = sa * 100 / sb / 2;
        if (pct < 0x32)
            pct = 0x32;
    } else {
        pct = func_0030CB00(0x33) + 0x1E;
    }
    if (func_0030CB50(pct) == 0) {
        r->kind = 0x15;
        r->v[0] = g;
        func_001204B0(r->text, func_00390760(0x55), func_002F8DB0(g));
        r->v[0x1E] = 2;
    } else {
        r->kind = 0xC;
        r->v[0] = g;
        r->v[1] = h;
        func_00120928(a, func_002F8DB0(g));
        func_00120928(b, func_002F8DB0(h));
        func_001204B0(r->text, func_00390760(0x54), a, b);
        r->v[0x1E] = 1;
    }
    func_003155C0(p, reg, func_002FB320(g, reg));
    return 0;
}

/* 0x0031BC30, 0x70 bytes. Command 99's result: kind 0xC (message 0x5B). */
int func_0031BC30(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int reg[28];

    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(0x5B));
    func_003155C0(p, reg, func_002FB320(p->f, reg));
    return 0;
}

/* 0x0031BCA0, 0xF0 bytes. The free commands' result: kind 0xC, message 0x5A (0x3B-0x59) or 0x132
 * (0x5A-0x62, 0x65) with the times used. */
void func_0031BCA0(CmdRecord *p)
{
    CmdResult *r = func_003155A0(p, 0);
    int home = func_002FB2D0(p->f), m = 0x5A, v = func_00328570(), c = p->cmd;

    if ((c > 0x59 && c < 99) || c == 0x65) {
        m = 0x132;
        v = func_00328970();
    }
    r->kind = 0xC;
    func_001204B0(r->text, func_00390760(m), func_00372250(p->cmd), func_0030CB80(v + 1));
    home = func_002FB2D0(p->f);
    func_003155C0(p, &home, 1);
}

/* 0x0031BD90, 0x1D8 bytes. Runs command record `p` (the player's always, the computer's only
 * below difficulty 2): pays a tenth of its cost, builds its results (with the
 * command's own random seed) and applies them (the player's through the result screen). */
int func_0031BD90(CmdRecord *p, int a)
{
    u32 seed = g_7000015C;
    int c = p->cmd, r = 0;

    if ((u32)c >= 100)
        return 0;
    if (func_002FB2A0(p->f) == 0 && func_00327C40() >= 2)
        return 0;
    func_002F9130(p->f, func_00314000((int *)p) / 10);
    g_7000015C = func_003276A0() | 1;
    if ((c < 0x3B || c > 0x59) && (c < 0x5A || c > 0x62) && c != 0x65) {
        if (c == 99)
            func_0031BC30(p);
        else
            r = g_00414BD0[p->cmd](p);
    } else {
        func_0031BCA0(p);
    }
    if (r == 0) {
        if (func_002FB2A0(p->f) == 0)
            r = func_0031C5C0(p, a);
        else
            r = func_0038C6B0(p);
    }
    func_003BA520(c);
    g_7000015C = seed | 1;
    return r;
}

/* 0x0031BF70, 0x130 bytes. An officer without a role, away from force `f`, moves to one of its
 * region's neighbours owned by `f`; its service date is set. */
void func_0031BF70(u32 i, int f)
{
    int l[8], n = 0, k, reg;

    if (func_002F2840(i) == 0 || func_002F3DC0(i) != 0)
        return;
    reg = func_002F5CC0(i);
    if (f != func_0030AFF0(reg)) {
        for (k = 0; k < 6; k++) {
            int x = func_0030AD20(reg, k);

            if (IS_FORCE(x) && f == func_0030AFF0(x))
                l[n++] = x;
        }
        if (n != 0)
            func_002F5BE0(i, l[func_0030CB00(n)]);
    }
    func_002F32F0(i, func_00327C70());
}

/* 0x0031C0A0, 0x368 bytes. Places officers `l` (`n`) in force `f`'s regions (at random) where
 * their role has room (three per role), else in another role, else they are set free. */
void func_0031C0A0(int f, u32 *l, int n)
{
    u32 o[8];
    int reg[28], nr, k, j;

    for (k = 0; k < n; k++)
        o[k] = l[k];
    nr = func_002FB320(f, reg);
    for (k = 0; k < n; k++) {
        u32 i = o[k];
        int role, done = 0;

        if (i >= 0x19F)
            continue;
        func_0030C920(reg, nr);
        role = func_002F3DC0(i);
        for (j = 0; j < nr; j++) {
            if (role == 1) {
                if (func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, reg[j], 0, 0) < 3) {
                    func_002F5BE0(i, reg[j]);
                    done = 1;
                    break;
                }
            } else if (func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, reg[j], 0, 1) < 3) {
                func_002F5BE0(i, reg[j]);
                done = 1;
                break;
            }
        }
        if (done)
            continue;
        for (j = 0; j < nr; j++) {
            int nrole = role;

            if (role == 1 || func_002F3F20(i) == 0)
                nrole = role == 1 ? 2 : 1;
            if (nrole == 1) {
                if (func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, reg[j], 0, 0) < 3) {
                    func_002F3CF0(i, 1);
                    func_002F5BE0(i, reg[j]);
                    done = 1;
                    break;
                }
            } else if (func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, reg[j], 0, 1) < 3) {
                func_002F3CF0(i, nrole);
                func_002F5BE0(i, reg[j]);
                done = 1;
                break;
            }
            role = nrole;
        }
        if (!done)
            func_002F7410(i);
    }
}

/* 0x0031C410, 0x108 bytes. Region `r` is hit (by a battle?): two troops lost, its officers lose
 * 10% (30% when `heavy`) to 30% (50%) of their soldiers. */
void func_0031C410(int r, int heavy)
{
    int t = func_0030B090(r), n, k, cut;
    u32 *o;

    if (t == 0)
        return;
    func_0030B030(r, t - 2 < 0 ? 0 : t - 2);
    n = func_002F7D90(0, (int (*)(u32, int, int))func_002F7EC0, r, 0, 1);
    o = func_002F7B10();
    cut = heavy != 0 ? 0x1E : 10;
    for (k = 0; k < n; k++, o++) {
        int x = func_0030CB00(0x15);

        func_002F3660(*o, func_002F3770(*o) * ((100 - x) - cut) / 100);
        func_002F4B70(*o, -1);
    }
}

/* 0x0031C520, 0x94 bytes. A value grade `g` (2 or 3) reached in value `k`: the weapons of that
 * grade and group are unlocked. */
void func_0031C520(int g, int k)
{
    int w;

    if ((u32)(g - 2) >= 2)
        return;
    for (w = 0; w < 0x79; w++) {
        if (g - 1 == func_002F57F0(w) && k == func_0030AB20(w))
            *func_00328B30(w) = w;
    }
}

void func_00327EA0(int d);
void func_002F9410(int f, int k, int v);
void func_002FAF30(int f, int g);
void func_002FA500(int f, int g);
void func_002FA610(int f, int g);
void func_002FA720(int f, int v);
void func_002FA800(int f, int v);
void func_0030A470(int a, int b);
void func_0030E390(int kind, int a, int b, int c, int *l, int n);
int func_00309F90(u32 i);
void func_002F91C0(int f, u32 i);
void func_0030A870(int kind, u32 i, int r, int *l, int n, int show);
void func_002F3550(u32 i, int v);
void func_002F4760(u32 i, int v);
void func_002F37E0(u32 i, int v);
void func_0030B0D0(int r, int d);
void func_0030ADC0(int r, int v);
void func_0030AE40(int r, int d);
int func_002F45A0(u32 i);
void func_002F4AE0(u32 i, int v);
int func_002F4660(u32 i);
void func_002F46D0(u32 i, int v);
int func_003297D0(void);
void func_003297E0(int v);
int func_00329810(void);
void func_00329820(int v);
int func_00329790(void);
void func_003297A0(int v);
void func_0029FD50(u32 i);
void func_003281F0(int v);
void func_003BACA0(void);

/* For each officer of force `f` (`all`: func_002F7D90's last flag). */
#define EACH_OFFICER(f, all, o, n, k)                                                    \
    for (n = func_002F7D90(0, (int (*)(u32, int, int))func_002F8160, f, 0, all),         \
         o = func_002F7B10(), k = 0; k < n; k++, o++)

/* 0x0031C5C0, 0x10B8 bytes. Applies result `k` of command record `p` for the computer (by the
 * result's kind: gold, values, officers joining, ties, submissions, captures and rebellions,
 * experience, soldiers, troops, the command's own effects (kind 0xC), duels and training
 * (kinds 0xF / 0x10, shown to the player), policies, events...). */
int func_0031C5C0(CmdRecord *p, int k)
{
    int c = p->cmd, f = p->f, player = func_002FB2A0(f), ret = 0, reg[28], list[6], n, j;
    CmdResult *r = &p->res[k];
    int *v = r->v;
    u32 *o;

    switch (r->kind) {
    case 0:
        func_002F90D0(f, v[0] / 10);
        if (player != 0 && c == 7) {
            func_00327EA0(-1);
            return 0;
        }
        break;
    case 1:
        for (j = 0; j < 3; j++) {
            int old = func_002F9480(f, j), now;

            func_002F9410(f, j, v[j]);
            now = func_002F9480(f, j);
            if (player != 0 && old < now)
                func_0031C520(now, j);
        }
        break;
    case 2:
        if ((u32)v[0] < 0x19F) {
            ret = func_00309C30(v[0], f, 0x19);
            if (c == 0x21) {
                for (j = 0; j < 4; j++) {
                    if ((u32)v[1 + j] > 0x19E)
                        return ret;
                    func_0031BF70(v[1 + j], f);
                }
            }
        }
        break;
    case 3: {
        int g = v[0];

        if (func_002FB2A0(f) == 0 && func_002FB2A0(g) != 0)
            func_0030E390(6, f, v[1] != 4, -1, 0, 0);
        else if (IS_FORCE(g) && v[2] != 0)
            func_002FAEA0(f, g, v[1], 1);
        break;
    }
    case 4: {
        int g = v[0];

        if (func_002FB2A0(f) == 0 && func_002FB2A0(g) != 0) {
            func_0030E390(7, f, -1, -1, 0, 0);
        } else if (IS_FORCE(g) && v[1] != 0) {
            if (v[2] == 0) {
                func_002FAFC0(g);
                func_002FAEA0(f, g, 0, 3);
            } else {
                func_0030A470(f, g);
            }
        }
        break;
    }
    case 5:
        if (c == 0x39) {
            int g = func_002F4080(v[0]);

            if (func_002FB2A0(f) == 0 && func_002FB2A0(g) != 0)
                func_0030E390(0x15, v[0], func_002F5CC0(v[0]), -1, 0, 0);
            func_00309F90(v[0]);
        } else if (c == 0x35) {
            if (IS_FORCE(v[0])) {
                func_0031C410(v[0], v[3]);
                if (func_002FB2A0(f) == 0 && func_002FB2A0(func_0030AFF0(v[0])) != 0)
                    func_0030E390(0x14, v[0], v[3], -1, 0, 0);
            }
        } else if (c == 0x34 && (u32)v[0] < 0x19F) {
            func_002F91C0(f, v[0]);
        }
        break;
    case 6: {
        CmdResult *r1 = func_003155A0(p, 1);

        if (func_002FB2A0(f) == 0 && func_002FB2A0(func_0030AFF0(v[0])) != 0 && r1->kind == 7
            && r1->v[1] != 0) {
            func_002F4080(r1->v[2]);
            for (n = 0; n < 5 && (u32)r1->v[3 + n] <= 0x19E; n++)
                list[n] = r1->v[3 + n];
            func_0030E390(0x16, r1->v[2], r1->v[0], -1, list, n);
        }
        break;
    }
    case 7:
        if (IS_FORCE(v[0]) && v[1] != 0) {
            int g = func_002F4080(v[2]);

            for (n = 0; n < 5 && (u32)v[3 + n] <= 0x19E; n++)
                list[n] = v[3 + n];
            func_0030A870(1, v[2], v[0], list, n, 1);
            for (n = 0; n < 5 && (u32)v[8 + n] <= 0x19E; n++)
                list[n] = v[8 + n];
            if (n != 0)
                func_0031C0A0(g, (u32 *)list, n);
        }
        break;
    case 8:
        func_002F3550(v[0], v[1]);
        if (player != 0)
            func_002F4760(v[0], 0xF);
        break;
    case 10:
        func_002F37E0(v[0], v[1]);
        if (player != 0)
            func_002F4760(v[0], 10);
        break;
    case 0xB:
        func_0030B0D0(v[0], v[1]);
        break;
    case 0xC:
        if (c == 0x27) {
        } else if (c == 99) {
            if (player != 0) {
                int e = func_00327E90();

                func_00327EA0(e < 0 ? 1 : -(e > 0));
            }
            EACH_OFFICER(f, 0, o, n, j) {
                if (func_002F45A0(*o) == 0 && func_002F4450(*o) == 0) {
                    func_002F4760(*o, 0x14);
                    func_002F4B70(*o, 1);
                }
            }
        } else if (c == 0x3A) {
            func_002FAF30(v[0], v[1]);
        } else if (c == 9) {
            func_00327EA0(-1);
            EACH_OFFICER(f, 1, o, n, j)
                func_002F4AE0(*o, func_002F4A70(*o) - 1);
            n = func_002FB320(f, reg);
            for (j = 0; j < n; j++) {
                int w = func_0030AD80(reg[j]) * 8 / 10;

                func_0030ADC0(reg[j], w < 10 ? 10 : w);
                func_0030B0D0(reg[j], 1);
            }
        } else if (c == 0x1C) {
            if (player != 0)
                func_00327EA0(-1);
            EACH_OFFICER(f, 1, o, n, j) {
                func_002F3660(*o, func_002F38F0(*o));
                if (player != 0)
                    func_002F4B70(*o, -1);
            }
        } else if (c == 0x1B) {
            if (player != 0)
                func_00327EA0(v[0xE]);
            func_002FA800(f, 1);
            EACH_OFFICER(f, 1, o, n, j) {
                func_002F3660(*o, func_002F3770(*o) * 8 / 10);
                if (player != 0)
                    func_002F4760(*o, 10);
            }
        } else if (c == 0x38) {
            func_002FA720(f, 1);
        } else if (c == 0x37) {
            int g = v[0];

            func_002FA610(f, g);
            if (func_002FB2A0(g) == 0)
                func_002FA720(g, 1);
        } else if (c == 5) {
            n = func_002FB320(f, reg);
            for (j = 0; j < n; j++)
                func_0030AE40(reg[j], v[1]);
        } else if (c == 0x10) {
            n = func_002FB320(f, reg);
            for (j = 0; j < n; j++)
                func_0030B0D0(reg[j], 1);
        } else if (c == 0x1A || c == 0x19 || c == 0x18 || c == 0x17) {
            EACH_OFFICER(f, 1, o, n, j)
                func_002F37E0(*o, v[1]);
        } else if (c == 0x2F) {
            int g = v[0];

            if (func_002FB2A0(f) == 0 && func_002FB2A0(g) != 0) {
                func_0030E390(0x12, g, f, -1, 0, 0);
                func_002FAF30(f, v[0]);
            } else {
                func_002FAF30(f, v[0]);
                if (player != 0)
                    func_00327EA0(-1);
            }
        } else if (c == 0x2D) {
            func_002FA500(f, v[0]);
        } else if (c == 6) {
            if (player != 0)
                func_00327EA0(v[0xE]);
            func_002FA800(f, 1);
        }
        break;
    case 0xD:
        func_0030AE40(v[0], v[1]);
        break;
    case 0xF:
        if (player == 0)
            return 0;
        func_002F4760(v[0], 10);
        func_002F4760(v[1], 10);
        if (c == 0x27) {
            func_003297E0(func_003297D0() + 2);
            func_00329820(func_00329810() + 2);
            func_003297A0(func_00329790() + 2);
        } else if (c == 0x26) {
            func_003297A0(func_00329790() + 2);
        } else if (c == 0x25) {
            func_00329820(func_00329810() + 2);
        } else if (c == 0x24) {
            func_003297E0(func_003297D0() + 2);
        }
        list[0] = v[2];
        list[5] = v[3];
        list[4] = list[0];
        func_0030E390(0x11, c, v[0x1D], -1, list, 6);
        break;
    case 0x10:
        if (player == 0)
            return 0;
        for (j = 6; j < 0xE; j++)
            func_002F4760(v[j], 10);
        func_002F4760(v[0x15], 10);
        if (c == 0x2A)
            func_003297A0(func_00329790() + 10);
        else if (c == 0x29)
            func_00329820(func_00329810() + 10);
        else if (c == 0x28)
            func_003297E0(func_003297D0() + 10);
        list[0] = v[0xF];
        list[1] = v[0x10];
        list[2] = v[0x11];
        list[3] = v[0x12];
        list[4] = v[0x15];
        list[5] = v[0x1C];
        func_0030E390(0x11, c, v[0x1D], -1, list, 6);
        break;
    case 0x11:
        if (v[1] != -1)
            func_002F94C0(v[0], v[1] & 0xFFFF);
        break;
    case 0x12:
        func_002FA800(f, 1);
        func_00327EA0(v[0xE]);
        EACH_OFFICER(f, 1, o, n, j) {
            func_002F4AE0(*o, func_002F4A70(*o) + 1);
            func_002F46D0(*o, func_002F4660(*o) + 0xF);
        }
        break;
    case 0x14:
        func_002F4760(v[0], 10);
        func_0029FD50(v[0]);
        break;
    case 0x15:
        if (c == 0x36) {
            if ((u32)v[2] < 0x19F) {
                int g = func_002F4080(v[2]);

                if (func_002FB2A0(f) != 0 || func_002FB2A0(g) == 0)
                    func_002F7410(v[2]);
            }
        } else if (c == 0x30) {
            func_003281F0(1);
            func_003BACA0();
        } else if (c == 0x39) {
            func_002F4B70(v[1], v[2]);
        } else if (c == 0x35) {
            if ((u32)v[1] < 0x19F)
                func_002F4B70(v[1], v[2]);
        } else if (c == 0x34) {
            func_002F4B70(v[1], v[2]);
        }
        break;
    }
    return ret;
}

/* The command menu's page state (FC2C0 block +0x694). */
typedef struct {
    int grid[12][10];        /* +0x000 commands by group (100 = none) */
    int count[12];           /* +0x1E0 */
    int group;               /* +0x210 */
    int index;               /* +0x214 */
    int unknown_218;         /* +0x218 */
    int unknown_21C;         /* +0x21C */
    int unknown_220;         /* +0x220 */
    int unknown_224;         /* +0x224 */
    int unknown_228;         /* +0x228 */
    int unknown_22C;
    CmdRecord *rec;          /* +0x230 */
} CmdMenu;

extern CmdRecord g_007B5270;
extern u8 g_007B5A50[];

int *func_002FC2C0(void);
int func_003287B0(int c);
int func_00328800(int rank);
void func_003280F0(int c, int v);
void func_00388710(void);
void func_00388200(int a, int b);
void func_003882C0(int *on);
int func_0039BDC0(void);
int func_0039BEE0(void);
int func_0039BF50(void);
void func_003A90D0(int a);
void func_0039F9F0(int a);
void func_003890B0(int a);
int func_00389050(void);
int func_00389090(void);
void func_00327690(int seed);
int func_003280E0(void);

#define CMD_MENU() ((CmdMenu *)func_002FC2C0()[0x1A5])

/* 0x0031D680, 0xC bytes, matching. The command record being built. */
CmdRecord *func_0031D680(void)
{
    return &g_007B5270;
}

/* 0x0031D690, 0x28 bytes, matching. The command under the menu's cursor. */
int func_0031D690(CmdMenu *m)
{
    return m->grid[m->group][m->index];
}

/* 0x0031D6C0, 0xC bytes, matching. */
u8 *func_0031D6C0(void)
{
    return g_007B5A50;
}

/* Whether command `c` is a free one (0x5A-0x62, 0x65) or none (100). */
#define FREE_OR_NONE(c) (((c) > 0x59 && (c) < 99) || (c) == 0x65 || (c) == 100)

/* 0x0031D6D0, 0x160 bytes. Sorts the free commands of `l` (`n`) by their rank. */
void func_0031D6D0(int *l, int n)
{
    int k, j;

    for (k = 0; k < n; k++) {
        if (!FREE_OR_NONE(l[k]))
            continue;
        {
            int a = func_003287B0(l[k]);

            for (j = k + 1; j < n; j++) {
                int b;

                if (!FREE_OR_NONE(l[j]))
                    continue;
                b = func_003287B0(l[j]);
                if (b < a) {
                    l[k] = func_00328800(b);
                    l[j] = func_00328800(a);
                    k--;
                    break;
                }
            }
        }
    }
}

/* 0x0031D830, 0x25C bytes, matching. Fills the command menu with the commands available, by group (the
 * free ones sorted), and gets the command record ready. */
void func_0031D830(CmdMenu *m)
{
    int l[100], n, k, j;

    m->group = 0;
    m->index = 0;
    m->unknown_218 = -1;
    m->unknown_21C = -1;
    m->unknown_220 = 0;
    m->unknown_228 = -1;
    m->unknown_224 = 0;
    func_0011ED38(m->count, 0, 0x30);
    n = func_00314960(l);
    for (k = 0; k < n; k++) {
        int g = func_00313CB0(l[k]);

        m->grid[g][m->count[g]] = l[k];
        m->count[g]++;
        func_003280F0(l[k], 1);
    }
    if (m->count[11] != 0)
        func_0031D6D0(m->grid[11], m->count[11]);
    for (k = 0; k < 12; k++) {
        for (j = m->count[k]; j < 10; j++)
            m->grid[k][j] = 100;
    }
    m->rec = func_0031D680();
    func_00315510(m->rec, func_00327D50());
}

/* 0x0031DA90, 0x1C bytes, matching. */
void func_0031DA90(void)
{
    func_00388710();
}

/* 0x0031DAB0, 0x98 bytes, matching. Opens menu page 1: the seven first groups (those with commands). */
void func_0031DAB0(void)
{
    CmdMenu *m = CMD_MENU();
    int g = m->group, on[8], k;

    func_0031D830(m);
    func_00388200(1, g);
    for (k = 0; k < 7; k++)
        on[k] = 1;
    for (k = 0; k < 7; k++) {
        if (m->count[k] == 0)
            on[k] = 0;
    }
    func_003882C0(on);
}

/* 0x0031DB50, 0x90 bytes, matching. Opens menu page 2: groups 7-10. */
void func_0031DB50(void)
{
    CmdMenu *m = CMD_MENU();
    int g = m->group, on[4], k;

    func_0031D830(m);
    func_00388200(2, g);
    for (k = 0; k < 4; k++)
        on[k] = 1;
    for (k = 0; k < 4; k++) {
        if (m->count[7 + k] == 0)
            on[k] = 0;
    }
    func_003882C0(on);
}

/* 0x0031DBE0, 0x118 bytes. Opens menu page 4 (nine entries, some only when their data exist,
 * entry 8 while a force has func_002FB100, entry 4 with a free stable slot). */
void func_0031DBE0(void)
{
    int on[9], k;

    func_00388200(4, 0);
    for (k = 0; k < 9; k++)
        on[k] = 1;
    if (func_0039BDC0() == 0)
        on[5] = 0;
    if (func_0039BEE0() == 0)
        on[6] = 0;
    if (func_0039BF50() == 0)
        on[7] = 0;
    on[8] = 0;
    for (k = 0; k < 0x19; k++) {
        if (IS_FORCE(k) && func_002F8CB0(k) != 0 && func_002FB100(k) != 0)
            on[8] = 1;
    }
    if (func_001A0700() == 0)
        on[4] = 0;
    func_003882C0(on);
}

/* 0x0031DD00, 0x6C bytes. The help message of main menu entry `k`. */
int func_0031DD00(int k)
{
    switch (k) {
    case 0: return 6;
    case 1: return 7;
    case 2: return 8;
    case 3: return 0x12;
    case 4: return 0x2B;
    case 5: return 9;
    case 6: return 10;
    case 7: return 0xB;
    }
    return -1;
}

/* 0x0031DD70, 0x3C bytes. */
int func_0031DD70(int k)
{
    switch (k) {
    case 0: return 0x15A;
    case 1: return 0x15A;
    }
    return -1;
}

/* 0x0031DDB0, 0x190 bytes. The turn's main menu: the chosen entry opens its page (with its own
 * random seed); 5. */
int func_0031DDB0(void)
{
    int *st = func_002FC2C0();
    CmdMenu *m = (CmdMenu *)st[0x1A5];
    int sel;

    func_003A90D0(0);
    func_003A9010(0);
    func_0039F9F0(1);
    func_003890B0(1);
    sel = func_00389050();
    func_003890B0(0);
    if (sel == 1) {
        func_00327690(func_00327C70() * 0x37 + 0x1E240 + func_003280E0() * 0x42);
        sel = func_00389090();
        st[1] = sel;
        st[0] = sel + 1;
        func_0031DD70(st[1]);
        func_00376100(4, -1, -1);
        if (st[1] == 2)
            func_0031DAB0();
        else if (st[1] == 3)
            func_0031DB50();
        else if (st[1] == 4)
            func_0031D830(m);
        else if (st[1] == 6)
            func_0031DBE0();
        if ((u32)(st[1] - 5) < 4)
            func_003A90D0(0);
        else
            func_003A90D0(1);
    }
    func_0039F9F0(0);
    return 5;
}

/* 0x0031DF40, 0x50 bytes, matching. Sets the menu's +0x220 value (7 reads the player's regions first). */
void func_0031DF40(int k)
{
    int reg[28];

    if (k == 7)
        func_002FB320(func_00327D50(), reg);
    CMD_MENU()->unknown_220 = k;
}
