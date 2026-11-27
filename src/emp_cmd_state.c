/*
 * emp_cmd_state.c - the Empire command state's small accessors between 0x0032E760 and
 * 0x0032EE08: the chosen officers (five slots at 0x007B5E50), the chosen provinces and
 * forces (gp 0x0045D004-0x0045D01C), the menus' open and close glue and the "same force
 * officers" checks. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int *g_007B5E4C;
extern short g_007B5E44, g_007B5E46;
extern int g_007B5E24;
extern int g_007B5E50[5];
extern int g_0045D6FC;                   /* (small data) */
extern u32 g_0045D004;
extern int g_0045D010, g_0045D014, g_0045D018, g_0045D01C;

void func_0032BAF0(void);
void func_0032BB10(void);
void func_0032BB30(void);
void func_003D3980(void);
void func_003D36D0(void);
void func_003D3770(void);
void func_003D3A40(void);
void func_003D39F0(void);
void func_003D3720(void);
void func_0032F770(int a);
int func_0030AB90(void);
u32 func_002F8F20(int p);
int func_00327C70(void);
int func_002F8CB0(int f);
int func_00327C00(void);
int func_002F2840(u32 o);
int func_002F3DC0(u32 o);
int func_002F4080(u32 o);

/* 0x0032E760, 0x20 bytes. The officer under the list's cursor. */
int func_0032E760(void)
{
    return g_007B5E4C[g_007B5E44];
}

/* 0x0032E780, 0x10 bytes. */
void func_0032E780(void)
{
    g_007B5E24 = 1;
}

/* 0x0032E790, 0xC bytes. */
short func_0032E790(void)
{
    return g_007B5E46;
}

/* 0x0032E7A0, 8 bytes, matching. */
void func_0032E7A0(int v)
{
    g_0045D6FC = v;
}

/* 0x0032E7B0, 8 bytes, matching. */
int func_0032E7B0(void)
{
    return g_0045D6FC;
}

/* 0x0032E7C0, 0x34 bytes, matching. */
void func_0032E7C0(void)
{
    func_0032BAF0();
    func_003D3980();
    func_003D36D0();
    func_0032F770(-1);
}

/* 0x0032E800, 0x2C bytes, matching. */
void func_0032E800(void)
{
    func_003D3770();
    func_003D3A40();
    func_0032BB30();
}

/* 0x0032E830, 0x34 bytes, matching. */
void func_0032E830(void)
{
    func_0032BB10();
    func_003D39F0();
    func_003D3720();
    func_0032F770(-1);
}

/* 0x0032E870, 0x2C bytes, matching. */
void func_0032E870(void)
{
    func_003D3770();
    func_003D3A40();
    func_0032BB30();
}

/* 0x0032E8A0, 0x34 bytes, matching. */
void func_0032E8A0(int k, int o)
{
    if (k < 5 && o < 0x19F)
        g_007B5E50[k] = o;
}

/* 0x0032E8E0, 0x30 bytes. */
int func_0032E8E0(int k)
{
    if (k < 5)
        return g_007B5E50[k];
    return 0;
}

/* 0x0032E910, 0x3C bytes. Chooses officer `o`. */
void func_0032E910(u32 o)
{
    if (o < 0x19F) {
        g_0045D004 = o;
        func_0032E8A0(0, o);
    }
}

/* 0x0032E950, 8 bytes, matching. */
u32 func_0032E950(void)
{
    return g_0045D004;
}

/* 0x0032E960, 0x78 bytes. Chooses province `p` (and its lord). */
void func_0032E960(int p)
{
    if (p >= 0 && p < func_0030AB90()) {
        u32 o;

        g_0045D010 = p;
        o = func_002F8F20(p);
        if (o < 0x19F)
            func_0032E8A0(0, o);
    }
}

/* 0x0032E9E0, 0x48 bytes. */
void func_0032E9E0(int p)
{
    if (p >= 0 && p < func_0030AB90())
        g_0045D014 = p;
}

/* 0x0032EA30, 0x48 bytes. */
void func_0032EA30(int p)
{
    if (p >= 0 && p < func_0030AB90())
        g_0045D018 = p;
}

/* 0x0032EA80, 0x18 bytes, matching. */
void func_0032EA80(int k)
{
    if (k < 5)
        g_0045D01C = k;
}

/* 0x0032EAA0, 8 bytes, matching. */
int func_0032EAA0(void)
{
    return g_0045D01C;
}

/* 0x0032EAB0, 0xC bytes, matching. */
void func_0032EAB0(int a, int *b, int *c)
{
    *b = 0;
    *c = 0;
}

/* 0x0032EAC0, 0x1C bytes, matching. */
int func_0032EAC0(void)
{
    return func_00327C70();
}

/* 0x0032EAE0, 0x1C bytes, matching. */
int func_0032EAE0(int f)
{
    return func_002F8CB0(f);
}

/* 0x0032EB00, 8 bytes, matching. */
int func_0032EB00(void)
{
    return 0;
}

/* 0x0032EB10, 0x24 bytes, matching. */
int func_0032EB10(void)
{
    return func_00327C00() != 10;
}

/* 0x0032EB40, 0x108 bytes. Whether officers `a` and `b` serve the same force (`c`: `a` may be
 * `b`). */
int func_0032EB40(u32 a, u32 b, int c)
{
    if (a >= 0x19F || b >= 0x19F)
        return 0;
    if (func_002F2840(a) == 0 || func_002F2840(b) == 0)
        return 0;
    if (func_002F3DC0(a) != 3)
        return 0;
    if (c == 0 && a == b)
        return 0;
    return func_002F4080(a) == func_002F4080(b);
}

/* 0x0032EC50, 0xDC bytes. Whether `a` serves with both `b` and `c`. */
int func_0032EC50(u32 a, u32 b, int c, int d)
{
    if (a >= 0x19F || b >= 0x19F || c < 0 || c >= 0x19F)
        return 0;
    return func_0032EB40(a, b, d) != 0 && func_0032EB40(a, c, d) != 0;
}

/* 0x0032ED30, 0xD8 bytes. Whether `a` serves with exactly one of `b` and `c`. */
int func_0032ED30(u32 a, u32 b, u32 c, int d)
{
    if (a >= 0x19F)
        return 0;
    if (func_0032EB40(a, b, d) == 0 || func_0032EB40(a, c, d) != 0)
        return func_0032EB40(a, b, d) == 0 && func_0032EB40(a, c, d) != 0;
    return 1;
}

extern u8 g_00669D60[];
extern int *g_0045D718;                  /* (small data) the six command values */
extern u8 *g_0045D71C;                   /* (small data) records of 0x3C bytes */
extern int (*g_00414EF0[6])(void);
extern int g_00414EA0[0x12];

int func_00327820(void);
int func_0030D370(void);
int func_0036B280(int s);
int func_00334720(void);
int func_003C1850(void);

/* 0x0032EE10, 0x9C bytes. Whether officer `o` is the lord of a force still in the game. */
int func_0032EE10(int o)
{
    int f = func_002F4080(o);

    if (f < 0 || f >= func_0030AB90())
        return 0;
    if (func_002F8CB0(f) == 0 || func_0032EAE0(f) == 0)
        return 0;
    return o == (int)func_002F8F20(f);
}

/* 0x0032EEB0, 0x1C bytes, matching. */
int func_0032EEB0(void)
{
    return func_00327820();
}

/* 0x0032EED0, 0x44 bytes, matching. The player's officer when in the battle (0x19F: none). */
u32 func_0032EED0(void)
{
    if (func_0030D370() == 0 || func_0036B280(0) == 0)
        return 0x19F;
    return *(u32 *)(g_00669D60 + 0x88);
}

/* 0x0032EF20, 0x1C bytes, matching. */
int func_0032EF20(void)
{
    return func_0032E8E0(0);
}

/* 0x0032EF40, 0x1C bytes, matching. */
int func_0032EF40(void)
{
    return func_0032E8E0(1);
}

/* 0x0032EF60, 0x1C bytes, matching. */
int func_0032EF60(void)
{
    return func_0032E8E0(2);
}

/* 0x0032EF80, 0x1C bytes, matching. */
int func_0032EF80(void)
{
    return func_0032E8E0(3);
}

/* 0x0032EFA0, 0x1C bytes, matching. */
int func_0032EFA0(void)
{
    return func_0032E8E0(4);
}

/* 0x0032EFC0, 0x78 bytes. Fills the six command values. */
void func_0032EFC0(void)
{
    int k;

    for (k = 0; k < 6; k++)
        g_0045D718[k] = g_00414EF0[k]();
}

/* 0x0032F040, 0x18 bytes, matching. */
u8 *func_0032F040(int k)
{
    return g_0045D71C + k * 0x3C;
}

/* 0x0032F090, 0xAC bytes. The special stage of scenario kind `k` (0: none). */
int func_0032F090(int k)
{
    switch (k) {
    case 0xC:
    case 0xD:
    case 0xE:
        return func_00334720() - 0x1E;
    case 0x10:
    case 0x11:
    case 0x12:
        return 10;
    case 0x14:
        return func_003C1850() == 0 ? 0xB : 0xD;
    case 0x15:
        return 0xC;
    case 0x16:
        return 0xD;
    case 0x17:
        return 0xE;
    case 0x18:
        return 0xF;
    case 0x19:
        return 0x10;
    case 0x1A:
        return 0x11;
    default:
        return 0;
    }
}

/* 0x0032F140, 0x30 bytes. */
int func_0032F140(int k)
{
    if (k < 0x12)
        return g_00414EA0[k];
    return 0x11;
}

/* 0x0032F060, 0x24 bytes, matching. */
int func_0032F060(int k)
{
    return func_0032F140(func_0032F090(k));
}

/* 0x0032F170, 0x30 bytes, matching. */
int func_0032F170(int a, int i)
{
    return *(int *)(func_0032F040(a) + i * 4);
}

/* 0x0032F1A0, 0x30 bytes. */
int func_0032F1A0(int a, int i)
{
    return *(int *)(func_0032F040(a) + 0x20 + i * 4);
}

/* ---- The command state's buffers, text helpers and Empire flags (parts of 0x0032F1D0-
 * 0x0032FF64). ---- */

extern u8 *g_005BA6A0;
extern int (*g_00447AD0[0x18])(void), (*g_00447BB0[0x8D])(void);
extern u8 *g_0045D710, *g_0045D714;      /* (small data) */
extern int g_0045D700, g_0045D704, g_0045D708, g_0045D70C;
extern u32 g_0045D000, g_0045D008, g_0045D00C;
extern int g_0045D020, g_0045D720, g_0045D724, g_0045D728, g_0045D72C, g_0045D730, g_0045D738;
extern char g_00447B50[];
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_00102EC0(void *p);
void *func_00102DB0(int align, int size);
u8 *func_001026D0(int a, int k, int b, int c, int d, int e, char *name, int line);
int func_00102960(int a);
u32 func_00120A40(const char *s);
void func_003C0770(void);
void func_0017E0C0(int v, int a);
void func_0017DEA0(int v);
void func_0023B3C0(int on, int all);

/* 0x0032F1D0, 0xC4 bytes. A weapon kind's model group. */
int func_0032F1D0(int k)
{
    if (k > 0x19) {
        if (k >= 0x3E && k <= 0x48)
            k = 0x26;
        else if (k >= 0x49 && k <= 0x53)
            k = 0x2A;
        else if (k >= 0x54 && k <= 0x5C)
            k = 0x20;
        else if (k > 0x5C && k < 0x68)
            k = 0x21;
        if (k == 0x69)
            k = 0x2A;
        else if (k == 0x68)
            k = 0x26;
    }
    return k;
}

/* 0x0032F2A0, 0x3C bytes. Officer `o`'s one. */
int func_0032F2A0(int o)
{
    return func_0032F1D0(g_005BA6A0[o * 0x2C + 7]);
}

/* 0x0032F3D0, 0x34 bytes. */
int func_0032F3D0(u32 k)
{
    if (k < 0x18)
        return g_00447AD0[k]();
    return 0;
}

/* 0x0032F530, 0x64 bytes, matching. */
void func_0032F530(void)
{
    if (g_0045D710 != 0) {
        func_00102EC0(g_0045D710);
        g_0045D710 = 0;
    }
    if (g_0045D714 != 0) {
        func_00102EC0(g_0045D714);
        g_0045D714 = 0;
    }
    if (g_0045D718 != 0) {
        func_00102EC0(g_0045D718);
        g_0045D718 = 0;
    }
    g_0045D70C = 0;
    g_0045D708 = 0;
}

/* 0x0032F5A0, 0xA0 bytes. */
void func_0032F5A0(void)
{
    g_0045D718 = func_00102DB0(0x10, 0x18);
    g_0045D714 = func_00102DB0(0x10, 600);
    g_0045D710 = func_00102DB0(0x10, 0x240);
    g_007B5E50[0] = 0;
    g_007B5E50[1] = 0;
    g_0045D000 = 0x19F;
    g_007B5E50[2] = 0;
    g_0045D004 = 0x19F;
    g_007B5E50[3] = 0;
    g_0045D008 = 0x19F;
    g_007B5E50[4] = 0;
    g_0045D00C = 0x19F;
    g_0045D01C = 5;
    g_0045D010 = 0x19;
    g_0045D014 = 0x19;
    g_0045D018 = 0x19;
    g_0045D70C = 0;
    g_0045D708 = 0;
}

/* 0x0032F640, 0x2C bytes, matching. */
void func_0032F640(void)
{
    if (g_0045D71C != 0) {
        func_00102EC0(g_0045D71C);
        g_0045D71C = 0;
    }
}

/* 0x0032F670, 0x48 bytes, matching. */
void func_0032F670(void)
{
    g_0045D71C = func_001026D0(1, 0xAB, 0, 1, 0, 0, g_00447B50, 0x499);
    func_00102960(1);
}

/* 0x0032F6C0, 0xA4 bytes. Copies a text, dropping the "\n" escapes. */
void func_0032F6C0(char *d, char *s)
{
    u32 n = func_00120A40(s), k = 0;

    if (n != 0) {
        do {
            int nl = *s == '\\' && s[1] == 'n';

            if (nl)
                s++;
            if (!nl)
                d[k++] = *s;
            s++;
        } while (k < n);
    }
    d[k] = 0;
}

/* 0x0032F770, 8 bytes, matching. */
void func_0032F770(int v)
{
    g_0045D704 = v;
}

/* 0x0032F780, 8 bytes, matching. */
int func_0032F780(void)
{
    return g_0045D704;
}

/* 0x0032F790, 0x38 bytes. */
void func_0032F790(void)
{
    g_0045D700 = RANDOM() % 100;
}

/* 0x0032F950, 0x34 bytes. */
int func_0032F950(u32 k)
{
    if (k < 0x8D)
        return g_00447BB0[k]();
    return k;
}

/* 0x0032FEB0, 0x38 bytes, matching. */
void func_0032FEB0(void)
{
    g_0045D020 = -1;
    g_0045D720 = 0;
    g_0045D724 = 0;
    g_0045D728 = 0;
    g_0045D72C = 0;
    g_0045D730 = 0;
    g_0045D738 = 0;
    func_003C0770();
}

/* 0x0032FEF0, 8 bytes, matching. */
void func_0032FEF0(int v)
{
    g_0045D720 = v;
}

/* 0x0032FF00, 8 bytes, matching. */
int func_0032FF00(void)
{
    return g_0045D720;
}

/* 0x0032FF10, 8 bytes, matching. */
void func_0032FF10(int v)
{
    g_0045D724 = v;
}

/* 0x0032FF20, 8 bytes, matching. */
int func_0032FF20(void)
{
    return g_0045D724;
}

/* 0x0032FF30, 0x38 bytes, matching. The Empire screens' music and sounds back on. */
void func_0032FF30(void)
{
    func_0017E0C0(g_00669D60[0x52], 0xF);
    func_0017DEA0(0x1E);
    func_0023B3C0(1, 0);
}
