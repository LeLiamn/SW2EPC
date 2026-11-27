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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 *g_0045D7DC, *g_0045D7E0;      /* (small data) */
extern u8 g_007BA600[];
extern u8 g_007BA7D0[], g_007BA7F0[], g_007BA810[], g_007BA830[];
extern float g_007BA7D8, g_007BA7F8, g_007BA818, g_007BA838;
extern u8 g_007BA7DD, g_007BA7FD, g_007BA81D, g_007BA83D;
extern u8 *g_007BA840;
extern u8 g_00418D80[][4];
extern short g_00418B80[][0x2A];
extern int g_0056CCA4[4];
extern float g_0056CCC0, g_0056CCC4;

#define FONT_COLOUR(c) (g_0056CCA4[0] = g_0056CCA4[1] = g_0056CCA4[2] = g_0056CCA4[3] = (c))
#define FONT_SIZE(s) (g_0056CCC0 = (s), g_0056CCC4 = (s))

void func_00102EC0(void *p);
int func_00328C80(int k, int i);
int func_003E7FA0(int k);
int func_003E7EC0(int k, int a, int i);
int func_003A02F0(int v);
void func_00391A10(void);
void func_002ED190(int k);
void func_003BD640(int x1, int x2, int y, int k);
char *func_002F2970(int o);
void func_00146B40(char *text, int x, int y, int w, int h, int a, int b);

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
        g_0045D7E0 = 0;
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
    func_00146B40(s, x + 0x10, i * 0x18 + 0x5E, 0x98, 0x14, 2, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
}

/* The four list windows: x (+0), slide (+4), speed (+8), alpha (+0xC), flags (+0xD: bit 0
 * still moving), window animation (+0x10). Line `i` slides in two frames after the one above. */
#define LW_X(b) (*(short *)(b))
#define LW_D(b) (*(short *)((b) + 4))
#define LW_SPEED(b) (*(float *)((b) + 8))
#define LW_FLAGS(b) ((b)[0xD])
#define LW_WIN(b) (*(u8 **)((b) + 0x10))

static int slide_x(u8 *b, int i)
{
    int x = LW_X(b) - LW_D(b) * (i * 2 - (LW_WIN(b)[0x13] - 10)) / 10;

    return x > 0x10 ? 0x10 : x;
}

/* Steps list window `b` (`last`: the last line's frame count). */
#define LW_STEP(b, w, last, rest) do {                                  \
    int r_;                                                             \
    LW_WIN(b) = (w);                                                    \
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

void func_002C80A0(int x, int y, int a, int w, int h, int b, int c);
void func_002C8500(int x, int y, int a, int w, int h, int b, int c);
void func_00397700(int o, int i);
void func_001A3460(int x, int y, int a, int b, int h, int c, int n, int m);
char *func_00372750(int i);
char *func_003728D0(int mode, short v);
int func_001AE550(float speed, void *w, short *pos, u8 *alpha, int a);
int func_002ED160(void);
u8 *func_002EE560(void);
u8 *func_002EE570(void);
u8 *func_002EE580(void);
u8 *func_002EE5D0(void);
void func_003923A0(void);
void func_00392790(int a);
void func_00392A10(void);

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
        func_001A3460(200, 0x50, 0, 0x10, 0x102, 0x80, n, m);
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
        func_00146B40(func_00372750(i), x + 0x10, y + 2, 0x58, 0x14, 2, 0);
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
        func_00146B40(func_003728D0(*(int *)(p + 0xC), v), x + 0xC, y + 2, 0xD0, 0x14, 2, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        if (i == *(short *)(p + 0x14C))
            func_002C8500(x, *(short *)(p + 0x14C) * 0x18 + 0x7A, 0, 0xE8, 0x18, 0x80, 1);
    }
    if ((g_007BA7DD & 1) != 0) {
        if (n > 9)
            func_001A3460(0xF8, 0x72, 0, 0x10, 0xE8, 0x80, n < 9 ? 9 : n, 9);
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
    LW_WIN(g_007BA7F0) = func_002EE5D0();
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
