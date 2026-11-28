/*
 * emp_lists.c - Empire screen lists between 0x00390760 and 0x00392568: the officer text table
 * (gp 0x0045D7DC), the officer voice/line list (state at 0x007BA600: mode +0xC, officer +0x94,
 * lines +0x9C/+0xF0, count +0x144, cursor +0x14C/+0x14E; per officer flags at 0x00418D80) and
 * the four sliding list windows (0x007BA7D0-0x007BA830). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_LISTS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

#ifdef SW2E_PC
extern ps2ptr g_0045D7DC_a;      /* (small data) */
#define g_0045D7DC ((u8 *)PS2_PTR(g_0045D7DC_a))
#define g_0045D7DC_SET(v) (g_0045D7DC_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7DC;
#define g_0045D7DC_a (*(ps2ptr *)&g_0045D7DC)
#define g_0045D7DC_SET(v) (g_0045D7DC = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0045D7E0_a;      /* (small data) */
#define g_0045D7E0 ((u8 *)PS2_PTR(g_0045D7E0_a))
#define g_0045D7E0_SET(v) (g_0045D7E0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7E0;
#define g_0045D7E0_a (*(ps2ptr *)&g_0045D7E0)
#define g_0045D7E0_SET(v) (g_0045D7E0 = (v))
#endif
extern u8 g_007BA600[];
extern u8 g_007BA7D0[], g_007BA7F0[], g_007BA810[], g_007BA830[];
extern float g_007BA7D8, g_007BA7F8, g_007BA818, g_007BA838;
extern u8 g_007BA7DD, g_007BA7FD, g_007BA81D, g_007BA83D;
#ifdef SW2E_PC
extern ps2ptr g_007BA840_a;
#define g_007BA840 ((u8 *)PS2_PTR(g_007BA840_a))
#define g_007BA840_SET(v) (g_007BA840_a = PS2_ADDR(v))
#else
extern u8 *g_007BA840;
#define g_007BA840_a (*(ps2ptr *)&g_007BA840)
#define g_007BA840_SET(v) (g_007BA840 = (v))
#endif
extern u8 g_00418D80[][4];
extern short g_00418B80[][0x2A];
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;

#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))
#define FONT_SIZE(s) (g_0056CCC0 = (s), g_0056CCC4 = (s))

void func_00391A10(void);

/* 0x00390760, 0x14 bytes, matching. Officer text `k`. */
u8 *func_00390760(int k)
{
    return ((u8 **)(g_0045D7DC + 4))[k];
}

/* 0x00390780, 0x2C bytes, matching. */
void func_00390780(void)
{
    if (g_0045D7E0 != 0) {
        func_00102EC0(g_0045D7E0);
        g_0045D7E0_SET(0);
    }
}

/* 0x00391250, 0xC bytes, matching. */
u8 *func_00391250(void)
{
    return g_007BA600;
}

/* 0x00391260, 0x128 bytes, matching. A special officer's portrait (0x7F: none). */
int func_00391260(int k)
{
    if (k == 0x22 || k == 0x2D)
        return 0x68;
    if (k == 0x23 || k == 0x24 || (u32)(k - 0x2B) < 2)
        return 0x6C;
    if (k == 0x25)
        return 0x7F;
    if (k == 0x26)
        return 0x70;
    if (k == 0x27)
        return 0x7D;
    if (k == 0x28)
        return 0x7E;
    if (k == 0x29 || k == 0x2A || k == 0x32)
        return 0x74;
    if (k == 0x2E)
        return 0x79;
    if (k == 0x2F)
        return 0x7A;
    if (k == 0x30)
        return 0x7B;
    if (k == 0x31)
        return 0x7C;
    return 0x7F;
}

/* 0x00391700, 0x130 bytes. Whether officer `o` has line `k`. */
int func_00391700(int o, int k)
{
    u8 *t = g_00418D80[o];

    func_00391250();
    if (k == 6)
        return -(t[0] & 1);
    if (k == 10)
        return -((t[0] >> 1) & 1);
    if (k == 0x5A)
        return -((t[0] >> 2) & 1);
    if (k >= 0xB && k <= 0xD)
        return k < t[1] + 0xB;
    if (k >= 0xE && k <= 0x19)
        return k < t[2] * 3 + 0xE;
    return 1;
}

/* 0x00391830, 0xD8 bytes. Line `k`'s index among officer `o`'s lines (-1: none). */
short func_00391830(int o, int k)
{
    short s = -1;

    func_00391250();
    if (func_00391700(o, k) != 0) {
        s = k;
        if (k > 0xD)
            s -= 3 - g_00418D80[o][1];
        if (k > 0x19)
            s -= g_00418D80[o][2] * -3 + 0xC;
    }
    return s;
}

/* 0x00391910, 0xFC bytes. Keeps the lines the officer has. */
void func_00391910(void)
{
    u8 *p = func_00391250();
    short n = *(short *)(p + 0x144), i;
    int j = 0;

    for (i = 0; i < n; i++) {
        short v = g_00418B80[*(int *)(p + 0xC)][i];

        if (*(int *)(p + 0xC) == 0) {
            *(short *)(p + 0x9C + j * 2) = i;
            *(short *)(p + 0xF0 + j * 2) = i;
            j++;
        } else if (func_00391700(*(int *)(p + 0x94), v) != 0) {
            *(short *)(p + 0x9C + j * 2) = i;
            *(short *)(p + 0xF0 + j * 2) = func_00391830(*(int *)(p + 0x94), v);
            j++;
        }
    }
    *(short *)(p + 0x144) = j;
}

/* 0x00391B10, 0x11C bytes. The portraits of officer kind `k` (up to four). */
void func_00391B10(int k)
{
    u8 *p = func_00391250();
    int n = 0, i;

    for (i = 0; i < 4; i++) {
        int v;

        if (k < 0x1C || k > 0x21)
            v = func_00328C80(k, i);
        else
            v = func_003E7EC0(k, func_003E7FA0(k), i);
        if (v != 0x7F && (i < 1 || func_003A02F0(v) != 0)) {
            *(int *)(p + 0x14 + n * 4) = v;
            n++;
        }
    }
    *(int *)(p + 0x28) = n;
    if (k > 0x21 && k < 0x33) {
        *(int *)(p + 0x14) = func_00391260(k);
        *(int *)(p + 0x28) = 1;
    }
    *(int *)(p + 0x24) = 0;
}

/* 0x00391C30, 0x2C bytes, matching. */
void func_00391C30(void)
{
    u8 *p = func_00391250();

    *(int *)(p + 0xC) = 0;
    *(short *)(p + 0x14C) = 0;
    *(short *)(p + 0x14E) = 0;
    func_00391A10();
}

/* 0x00391C60, 0x1C bytes. */
int func_00391C60(u32 k)
{
    return k < 0x22;
}

/* 0x00391C80, 0xC bytes, matching. */
u8 *func_00391C80(void)
{
    return g_007BA830;
}

/* 0x00391C90, 0xC bytes, matching. */
u8 *func_00391C90(void)
{
    return g_007BA810;
}

/* 0x00391CA0, 0xC bytes, matching. */
u8 *func_00391CA0(void)
{
    return g_007BA7F0;
}

/* 0x00391CB0, 0xC bytes, matching. */
u8 *func_00391CB0(void)
{
    return g_007BA7D0;
}

/* 0x00391E60, 0x48 bytes. */
void func_00391E60(void)
{
    func_002ED190(0x20);
    g_007BA838 = 1.0f;
    g_007BA83D &= 0xFE;
}

/* 0x00391EB0, 0x48 bytes. */
void func_00391EB0(void)
{
    func_002ED190(0x21);
    g_007BA818 = 1.0f;
    g_007BA81D &= 0xFE;
}

/* 0x00391F00, 0x48 bytes. */
void func_00391F00(void)
{
    func_002ED190(0x2A);
    g_007BA7F8 = 1.0f;
    g_007BA7FD &= 0xFE;
}

/* 0x00391F50, 0x48 bytes. */
void func_00391F50(void)
{
    func_002ED190(0x22);
    g_007BA7D8 = 1.0f;
    g_007BA7DD &= 0xFE;
}

/* 0x00392340, 0x60 bytes. The list's arrows. */
void func_00392340(int on)
{
    if (func_00391250() != 0 && (g_007BA83D & 1) != 0 && on != 0)
        func_003BD640(0x1A, 0xAE, 0x40, 0);
}

/* 0x00392440, 0x128 bytes. Draws officer `o`'s name on line `i` (sliding in). */
void func_00392440(int o, int i)
{
    int x = *(short *)g_007BA830 - *(short *)(g_007BA830 + 4) * (i * 2 - (g_007BA840[0x13] - 10)) / 10;
    char *s;

    if (x > 0x10)
        x = 0x10;
    s = func_002F2970(o);
    FONT_COLOUR(6);
    FONT_SIZE(20.0f);
    func_00146B40((const unsigned char *)(s), x + 0x10, i * 0x18 + 0x5E, 0x98, 0x14, 2, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
}

/* The four list windows: x (+0), slide (+4), speed (+8), alpha (+0xC), flags (+0xD: bit 0
 * still moving), window animation (+0x10). Line `i` slides in two frames after the one above. */
#define LW_X(b) (*(short *)(b))
#define LW_D(b) (*(short *)((b) + 4))
#define LW_SPEED(b) (*(float *)((b) + 8))
#define LW_FLAGS(b) ((b)[0xD])
#define LW_WIN(b) PS2_LOADP(u8 *, ((b) + 0x10))
#define LW_WIN_SET(b, v) PS2_STOREP(u8 *, ((b) + 0x10), v)

static int slide_x(u8 *b, int i)
{
    int x = LW_X(b) - LW_D(b) * (i * 2 - (LW_WIN(b)[0x13] - 10)) / 10;

    return x > 0x10 ? 0x10 : x;
}

/* Steps list window `b` (`last`: the last line's frame count). */
#define LW_STEP(b, w, last, rest) do {                                  \
    int r_;                                                             \
    LW_WIN_SET(b, (w));                                                    \
    r_ = func_001AE550(LW_SPEED(b), (w), (short *)(b), (b) + 0xC, 0);   \
    LW_FLAGS(b) = (LW_FLAGS(b) & 0xFE) | (r_ & 1);                      \
    if ((r_ & 1) != 0) {                                                \
        int t_ = func_002ED160();                                       \
        if (t_ < (last)) {                                              \
            LW_FLAGS(b) &= 0xFE;                                        \
            LW_WIN(b)[0x13] = t_;                                       \
        } else {                                                        \
            LW_WIN(b)[0x13] = (rest);                                   \
        }                                                               \
    }                                                                   \
} while (0)

void func_00397700(int o, int i);
int func_002ED160(void);
u8 *func_002EE560(void);
u8 *func_002EE570(void);
u8 *func_002EE580(void);
u8 *func_002EE5D0(void);

/* 0x00392570, 0x214 bytes. Draws the officer list (`k`: names or the other column). */
void func_00392570(int k)
{
    u8 *p = func_00391250();
    short n = *(short *)(p + 0x144), m = n;
    int i;

    if (*(short *)(p + 0x146) < n)
        m = *(short *)(p + 0x146);
    for (i = 0; i < *(short *)(p + 0x146); i++) {
        int x = slide_x(g_007BA830, i), o;

        o = *(int *)(p + (*(short *)(p + 0x14A) + i) * 4 + 0x38);
        if (o != 0x40) {
            func_002C80A0(x, i * 0x18 + 0x5C, 0, 0xB8, 0x18, 0x80, 0);
            if (k == 0)
                func_00392440(o, i);
            else
                func_00397700(o, i);
            if (i == *(short *)(p + 0x148))
                func_002C8500(x, i * 0x18 + 0x5C, 0, 0xB8, 0x18, 0x80, 1);
        }
    }
    if ((g_007BA83D & 1) != 0 && *(short *)(p + 0x146) < n)
        func_001A3460(200, 0x50, 0, 0x10, 0x102, 0x80, n, m, *(short *)(p + 0x14A), 1);
}

/* 0x00392850, 0x1B4 bytes. Draws the two choices. */
void func_00392850(void)
{
    int *p = (int *)func_00391250(), sel = p[0], i;

    for (i = 0; i < 2; i++) {
        int x = slide_x(g_007BA810, i), y = 0x58 + i * 0x18;

        func_002C80A0(x, y, 0, 0x78, 0x18, 0x80, 0);
        FONT_COLOUR(6);
        FONT_SIZE(20.0f);
        func_00146B40((const unsigned char *)PS2_PTR(func_00372750(i)), x + 0x10, y + 2, 0x58, 0x14, 2, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        if (sel == i)
            func_002C8500(x, y, 0, 0x78, 0x18, 0x80, 1);
    }
}

/* 0x00392AF0, 0x284 bytes. Draws the lines list (nine at most). */
void func_00392AF0(void)
{
    u8 *p = func_00391250();
    int n = *(short *)(p + 0x144), m = n < 10 ? n : 9, i;

    for (i = 0; i < m; i++) {
        int x = slide_x(g_007BA7D0, i), y = 0x7A + i * 0x18;
        short v = *(short *)(p + (*(short *)(p + 0x14E) + i) * 2 + 0x9C);

        func_002C80A0(x, y, 0, 0xE8, 0x18, 0x80, 0);
        FONT_COLOUR(6);
        FONT_SIZE(20.0f);
        func_00146B40((const unsigned char *)PS2_PTR(func_003728D0(*(int *)(p + 0xC), v)), x + 0xC, y + 2, 0xD0, 0x14, 2, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        if (i == *(short *)(p + 0x14C))
            func_002C8500(x, *(short *)(p + 0x14C) * 0x18 + 0x7A, 0, 0xE8, 0x18, 0x80, 1);
    }
    if ((g_007BA7DD & 1) != 0) {
        if (n > 9)
            func_001A3460(0xF8, 0x72, 0, 0x10, 0xE8, 0x80, n < 9 ? 9 : n, 9, *(short *)(p + 0x14E), 0);
        func_003BD640(0x28, 0xD0, 0x5C, 0);
    }
}

/* 0x00392D80, 0x12C bytes. The officer list window's frame. */
void func_00392D80(void)
{
    u8 *p = func_00391250();
    short n = *(short *)(p + 0x144);

    if (*(short *)(p + 0x146) < n)
        n = *(short *)(p + 0x146);
    LW_STEP(g_007BA830, func_002EE560(), (n - 1) * 2 + 10, n * 2 + 10);
    func_00392340(1);
    func_003923A0();
    func_00392570(0);
}

/* 0x00392EB0, 0x140 bytes. The choices window's frame. */
void func_00392EB0(void)
{
    int r;

    LW_STEP(g_007BA810, func_002EE570(), 0xC, 0xE);
    LW_WIN_SET(g_007BA7F0, func_002EE5D0());
    r = func_001AE550(LW_SPEED(g_007BA7F0), LW_WIN(g_007BA7F0), (short *)g_007BA7F0,
                      g_007BA7F0 + 0xC, 0);
    g_007BA7FD = (g_007BA7FD & 0xFE) | (r & 1);
    func_00392790(0);
    func_00392850();
}

/* 0x00393560, 0x11C bytes. The lines window's frame. */
void func_00393560(void)
{
    u8 *p = func_00391250();
    int n = *(short *)(p + 0x144);

    if (n > 9)
        n = 9;
    LW_STEP(g_007BA7D0, func_002EE580(), (n - 1) * 2 + 10, n * 2 + 10);
    func_00392790(0);
    func_00392A10();
    func_00392AF0();
}

/* ---- The lists screen's set-up and the movie gallery grid (5 x 10 entries per page; state
 * func_00397160: page +0x24, column +0x28, row +0x2C), parts of 0x00395330-0x003964E0. ---- */

typedef unsigned long long u64;

extern char g_00459AE0[], g_00459B08[], g_00459B20[];
extern short g_007BA850, g_007BA852;
extern u8 g_007BA85C, g_007BA85D;
#ifdef SW2E_PC
extern ps2ptr g_0045D0B0_a;                   /* (small data) */
#define g_0045D0B0 ((u8 *)PS2_PTR(g_0045D0B0_a))
#define g_0045D0B0_SET(v) (g_0045D0B0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D0B0;
#define g_0045D0B0_a (*(ps2ptr *)&g_0045D0B0)
#define g_0045D0B0_SET(v) (g_0045D0B0 = (v))
#endif
extern u8 g_0056CCC8[4];

#define SP_PKT PS2_GETP(u32 *, 0x70000158)
#define SP_PKT_SET(v) PS2_SETP(0x70000158, v)

void func_003914C0(void);
void func_00392FF0(int a);
u8 *func_00397160(void);
u8 *func_002EE530(void);
int func_001204B0(char *buf, const char *fmt, ...);
void func_0011EB80(void *to, const void *from, int n);
int func_0011EAE8(const void *a, const void *b, int n);
void func_00396160(u32 a);

/* 0x00395330, 0xEC bytes. Opens the lists screen. */
void func_00395330(void)
{
    u8 *p = func_00391250();

    func_00118850(p, 0x1CC);
    PS2_STOREP(u8 *, (p + 0x2C), func_001026D0(1, 0x84, 0, 1, 0, 0, g_00459AE0, 0x74D));
    func_003914C0();
    g_007BA838 = 1.0f;
    g_007BA83D &= 0xFE;
    g_007BA818 = 1.0f;
    g_007BA81D &= 0xFE;
    g_007BA7F8 = 1.0f;
    g_007BA7FD &= 0xFE;
    g_007BA7D8 = 1.0f;
    g_007BA7DD &= 0xFE;
}

/* 0x00395420, 0x38 bytes, matching. */
void func_00395420(void)
{
    u8 *p = func_00391250();

    if (PS2_LOADP(u8 *, (p + 0x2C)) != 0) {
        func_00102EC0(PS2_LOADP(u8 *, (p + 0x2C)));
        PS2_STOREP(u8 *, (p + 0x2C), 0);
    }
}

/* 0x00395460, 0xB0 bytes. Draws the lists screen by its step. */
void func_00395460(void)
{
    int s = *(int *)(func_00391250() + 4);

    if (s == 4) {
        func_00393560();
        func_003E8940();
    } else if (s == 2 || s == 3) {
        func_00392FF0(0);
        func_003E8940();
    } else if (s == 1) {
        func_003E8940();
        func_00392EB0();
    } else if (s == 0) {
        func_00392D80();
    }
}

/* 0x00395510, 0x88 bytes. */
void func_00395510(void)
{
    int s = *(int *)(func_00391250() + 4);

    if (s == 4)
        func_003E95D0();
    else if (s == 3 || s == 2)
        func_003E95D0();
    else if (s == 1)
        func_003E95D0();
}

/* 0x003956B0, 0x128 bytes. The selected movie's picture. */
int func_003956B0(void)
{
    int *q = (int *)func_00397160();
    int v = q[0x28 / 4] + q[0x2C / 4] * 5 + q[0x24 / 4] * 0x32;

    if (v >= 0 && v <= 0x37)
        return v % 0x1C;
    if (v >= 0x38 && v <= 0x8B)
        return v % 0x1C + 0x1C;
    if (v >= 0x8C && v <= 0xA8)
        return (v - 0x8C) % 0x1D + 0x38;
    if (v >= 0xA9 && v <= 0xBF)
        return 0x55;
    if (v == 0xC0)
        return 0x56;
    if (v >= 0xC1 && v <= 0xC6)
        return 0x57;
    return 0x58;
}

/* 0x003957E0, 0x160 bytes. Draws the grid's cells (the cursor's glows). */
void func_003957E0(void)
{
    u8 *q = func_00397160();
    int r, c;

    if (q == 0)
        return;
    for (r = 0; r < 10; r++) {
        for (c = 0; c < 5; c++) {
            u8 a = g_007BA85C;

            func_001ABE40(PS2_LOADP(u8 *, (q + 0x14)), 0, g_007BA850 + c * 0x28, g_007BA852 + r * 0x18, 0,
                          0x28, 0x18, g_007BA85C, 0, 0);
            if (*(int *)(q + 0x28) == c && *(int *)(q + 0x2C) == r) {
                u8 *g = func_002EE530();
                u8 b;

                func_002C5AE0(g);
                b = g[4];
                if ((g_007BA85D & 1) == 0)
                    b = a;
                func_001ABE40(PS2_LOADP(u8 *, (q + 0x14)), 1, g_007BA850 + c * 0x28, g_007BA852 + r * 0x18,
                              0, 0x28, 0x18, b, 1, 0);
            }
        }
    }
}

/* 0x00395940, 0x178 bytes. Draws the grid's numbers (dim: locked, plain: not seen). */
void func_00395940(void)
{
    u8 *q = func_00397160();
    char buf[4];
    int r, c;

    if (q == 0)
        return;
    for (r = 0; r < 10; r++) {
        for (c = 0; c < 5; c++) {
            int k = c + r * 5 + *(int *)(q + 0x24) * 0x32, col;
            u8 a = g_007BA85C;

            func_001204B0(buf, g_00459B08, k + 1);
            if (func_003A17A0(k) == 0) {
                col = 6;
                a >>= 1;
            } else {
                col = func_003A1930(k) == 0 ? 6 : 1;
            }
            g_0056CCC8[0] = a;
            g_0056CCC8[1] = a;
            g_0056CCC8[2] = a;
            g_0056CCC8[3] = a;
            func_002C4F40(12.0f, buf, g_007BA850 + c * 0x28 + 2, g_007BA852 + r * 0x18 + 8, 2, 0,
                          col);
        }
    }
}

/* 0x00395E20, 0x9C bytes, matching. Loads the gallery's files (`k`: only the save copy). */
void func_00395E20(u8 *p, int k)
{
    u8 *q;

    if (k == 0) {
        PS2_STOREP(u8 *, (p + 0x14), func_001026D0(1, 0x86, 0, 1, 0, 0, g_00459B20, 0x118));
        PS2_STOREP(void *, (p + 0xC), func_00102DB0(0x40, 0x24));
    }
    q = func_001026D0(1, 0x83, 0, 0, 0, 0, g_00459B20, 0x11C);
    PS2_STOREP(u8 *, (p + 0x10), q);
    func_0011EB80(q, g_0045D0B0, 4);
}

/* A full screen rectangle with GS ALPHA value `a` and TEST `t`. */
static void full_screen(u64 a, u64 t, int k)
{
    u64 *q = (u64 *)(func_00105190());

    q[2] = a;
    q[3] = 0x43;
    q[4] = t;
    q[5] = 0x48;
    q[6] = 0;
    q[7] = 9;
    q[8] = 0x8000008001ULL;
    q[9] = 0x3B;
    if (k == 4) {
        u32 *p = SP_PKT;

        p[0] = 0x30000005;
        p[1] = (u32)PS2_ADDR(q);
        p[2] = 0x13000000;
        p[3] = 0x51000005;
        SP_PKT_SET(p + 4);
    } else {
        func_001052E0((unsigned char *)(q), k);
    }
}

/* 0x00395EC0, 0xD4 bytes. */
void func_00395EC0(int k)
{
    full_screen(0x8000000044ULL, 0x5000D, k);
}

/* 0x00395FA0, 0xD4 bytes. */
void func_00395FA0(u32 a, int k)
{
    full_screen(0x8000000049ULL, 0x43001, k);
}

/* 0x00396080, 0xD4 bytes. */
void func_00396080(u32 a, int k)
{
    full_screen(0x8000000042ULL, 0x43001, k);
}

/* 0x003963D0, 0x40 bytes, matching. */
void func_003963D0(void)
{
    u8 *q = func_00397160();

    *(int *)(q + 0x1C) = 0;
    *(int *)(q + 0x20) = 0x32;
    *(int *)(q + 0x24) = 0;
    *(int *)(q + 0x28) = 0;
    *(int *)(q + 0x2C) = 0;
    *(int *)(q + 0x30) = 0;
    *(int *)(q + 0x34) = 5;
}

/* 0x00396410, 8 bytes, matching. */
void func_00396410(void)
{
}

/* 0x00396420, 0x5C bytes, matching. Draws the movie being played. */
void func_00396420(u32 *p)
{
    if ((p[0] & 0x10) == 0)
        return;
    func_00395EC0(4);
    func_00396160(p[3]);
    func_00395FA0(p[1], 4);
    func_00396080(p[1], 4);
    func_00143C90();
}

/* 0x00396480, 0xA4 bytes. Waits for the movie file (reloading it when its header is wrong). */
void func_00396480(u32 *p)
{
    if ((p[0] & 0x10) != 0 || func_00102960(0) == 0)
        return;
    if (func_0011EAE8((u8 *)PS2_PTR(p[4]), g_0045D0B0, 4) == 0) {
        if (p[4] != 0) {
            func_00102EC0((u8 *)PS2_PTR(p[4]));
            p[4] = 0;
        }
        func_00395E20((u8 *)p, 1);
    } else {
        func_00143DA0((void *)PS2_PTR(p[3]), (unsigned char *)PS2_PTR(p[4]), 0x1300);
        p[0] |= 0x10;
        func_001037F0(1);
    }
}

/* ---- The movie gallery's frame, the special officers list (the same windows) and the command
 * menu's checks (parts of 0x00397160-0x00397F3C). ---- */

extern u8 g_007BA870[0x38];              /* the movie gallery */
extern float g_007BA858;
#ifdef SW2E_PC
extern ps2ptr g_007BA860_a;
#define g_007BA860 ((u8 *)PS2_PTR(g_007BA860_a))
#define g_007BA860_SET(v) (g_007BA860_a = PS2_ADDR(v))
#else
extern u8 *g_007BA860;
#define g_007BA860_a (*(ps2ptr *)&g_007BA860)
#define g_007BA860_SET(v) (g_007BA860 = (v))
#endif
extern u8 g_007BA8B0[];                  /* the command menu */

void func_001265F0(int a, int b);
u8 *func_002EE540(void);
void func_00395AC0(void);

/* 0x00397160, 0xC bytes, matching. */
u8 *func_00397160(void)
{
    return g_007BA870;
}

/* 0x00397170, 0x38 bytes, matching. */
void func_00397170(void)
{
    u8 *q = func_00397160();

    func_00118850(q, 0x38);
    *(int *)(q + 0x18) = 0;
    func_003963D0();
}

/* 0x003971B0, 0x80 bytes. Opens the gallery (once). */
void func_003971B0(void)
{
    u8 *q = func_00397160();

    if (*(int *)(q + 0x18) == 0) {
        func_00395E20(g_007BA870, 0);
        func_00102960(0);
        *(int *)(q + 0x18) = 1;
        func_001037F0(0);
        g_007BA858 = 1.0f;
        g_007BA85D &= 0xFE;
    }
}

/* 0x00397230, 0x28 bytes. */
void func_00397230(void)
{
    func_00397160();
    func_00396410();
}

/* 0x00397260, 0xC8 bytes. Closes the gallery (stopping the movie). */
void func_00397260(void)
{
    u32 *q = (u32 *)func_00397160();
    int k;

    if (q[6] == 0)
        return;
    func_00102990();
    func_00102960(1);
    func_001265F0(0, 1);
    if ((q[0] & 0x10) != 0) {
        func_00143D60((void *)PS2_PTR(q[3]));
        q[0] &= ~0x10;
    }
    for (k = 3; k < 6; k++) {
        if (q[k] != 0) {
            func_00102EC0((u8 *)PS2_PTR(q[k]));
            q[k] = 0;
        }
    }
    q[6] = 0;
    func_001037F0(1);
}

/* 0x00397330, 0xB0 bytes. Draws the gallery. */
void func_00397330(void)
{
    u8 *q = func_00397160();
    int r;

    if (q == 0)
        return;
    g_007BA860_SET(func_002EE540());
    r = func_001AE550(g_007BA858, g_007BA860, &g_007BA850, &g_007BA85C, 0);
    g_007BA85D = (g_007BA85D & 0xFE) | (r & 1);
    func_00396420((u32 *)q);
    func_003957E0();
    func_00395940();
    func_00395AC0();
    func_00395C90();
}

/* 0x003973E0, 0x48 bytes. The gallery's frame. */
int func_003973E0(void)
{
    u8 *q = func_00397160();

    if (q != 0) {
        func_00396480((u32 *)q);
        func_003967D0(PS2_ADDR((u32 *)q));
    }
    return 0;
}

/* 0x00397430, 0x10C bytes. The special officers list window's frame. */
void func_00397430(void)
{
    u8 *p = func_00391250();
    short n = *(short *)(p + 0x144);
    u8 *b = func_00391C80();

    if (*(short *)(p + 0x146) < n)
        n = *(short *)(p + 0x146);
    LW_STEP(b, func_002EE560(), (n - 1) * 2 + 10, n * 2 + 10);
    func_00392340(0);
    func_00392570(1);
}

/* 0x00397540, 0x11C bytes. */
void func_00397540(void)
{
    u8 *b = func_00391C90(), *c = func_00391CA0();
    int r;

    LW_STEP(b, func_002EE570(), 0xC, 0xE);
    LW_WIN_SET(c, func_002EE5D0());
    r = func_001AE550(LW_SPEED(c), LW_WIN(c), (short *)c, c + 0xC, 0);
    LW_FLAGS(c) = (LW_FLAGS(c) & 0xFE) | (r & 1);
    func_00392790(1);
    func_00392850();
}

/* 0x00397660, 0x94 bytes. The special officers (0x1C-0x32). */
void func_00397660(void)
{
    u8 *p = func_00391250();
    int k;

    for (k = 0; k < 0x17; k++)
        *(int *)(p + 0x38 + k * 4) = k + 0x1C;
    *(short *)(p + 0x144) = 0x17;
    *(short *)(p + 0x146) = 10;
}

/* 0x00397700, 0x12C bytes. Draws special officer `o`'s name on line `i`. */
void func_00397700(int o, int i)
{
    int x = slide_x(func_00391C80(), i);
    char *s = func_003727B0(o - 0x1C);

    FONT_COLOUR(6);
    FONT_SIZE(20.0f);
    func_00146270((const unsigned char *)(s), x + 0x10, i * 0x18 + 0x5E, 2, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
}

/* 0x00397830, 0xB4 bytes. */
void func_00397830(void)
{
    u8 *a = func_00391C80(), *b = func_00391C90(), *c = func_00391CA0(), *d = func_00391CB0();

    func_00397660();
    LW_FLAGS(a) &= 0xFE;
    LW_SPEED(a) = 1.0f;
    LW_FLAGS(b) &= 0xFE;
    LW_SPEED(b) = 1.0f;
    LW_FLAGS(c) &= 0xFE;
    LW_SPEED(c) = 1.0f;
    LW_FLAGS(d) &= 0xFE;
    LW_SPEED(d) = 1.0f;
}

/* 0x003978F0, 8 bytes, matching. */
void func_003978F0(void)
{
}

/* 0x00397900, 0x104 bytes. */
void func_00397900(void)
{
    u8 *p = func_00391250(), *b = func_00391CB0();
    int n = *(short *)(p + 0x144);

    if (n > 9)
        n = 9;
    LW_STEP(b, func_002EE580(), (n - 1) * 2 + 10, n * 2 + 10);
    func_00392790(1);
    func_00392A10();
    func_00392AF0();
}

/* 0x00397A10, 0xB0 bytes. Draws the special officers screen by its step. */
void func_00397A10(void)
{
    int s = *(int *)(func_00391250() + 4);

    if (s == 4) {
        func_00397900();
        func_003E8940();
    } else if (s == 2 || s == 3) {
        func_00392FF0(1);
        func_003E8940();
    } else if (s == 1) {
        func_003E8940();
        func_00397540();
    } else if (s == 0) {
        func_00397430();
    }
}

/* 0x00397AC0, 0x1C bytes, matching. */
void func_00397AC0(void)
{
    func_00395510();
}

/* 0x00397AE0, 0x1C bytes, matching. */
int func_00397AE0(float dt)
{
    return func_003955A0(dt);
}

/* 0x00397B00, 8 bytes, matching. */
int func_00397B00(int v)
{
    return v;
}

/* 0x00397E00, 0x44 bytes. Makes every command available. */
void func_00397E00(void)
{
    int k;

    for (k = 0; k < 0x15; k++)
        *(int *)(g_007BA8B0 + 0x24 + k * 4) = 1;
}

/* 0x00397E50, 0xA8 bytes. Whether the chosen province has a force to act on. */
int func_00397E50(void)
{
    int v = *(int *)g_007BA8B0, r = 0, k;

    if (v >= 0 && v < func_0030AB90()) {
        func_0030BBD0(v, 0);
        for (k = 0; k < 0x19; k++) {
            if (func_0030B2F0(k) != 0) {
                r = 1;
                break;
            }
        }
        func_0030B330();
    }
    return r;
}

/* 0x00397F00, 0x40 bytes, matching. Whether a slot is in use. */
int func_00397F00(void)
{
    int k;

    for (k = 0; k < 6; k++) {
        if (*(short *)(g_007BA8B0 + 0x1A4 + k * 2) != -1)
            return 1;
    }
    return 0;
}
