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
