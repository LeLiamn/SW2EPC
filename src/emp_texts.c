/*
 * emp_texts.c - the Empire mode's text tables (lists of string pointers: menu labels, ranks,
 * seasons, tactics, messages ...) and their getters, plus small turn and menu helpers around
 * them (parts of 0x00370140-0x003764A4). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char g_004484C0[];                /* "" */
extern char *g_004484C8[];               /* the empty text's pointer */

extern char *g_004160F0[];
extern char *g_00416110[];
extern char *g_00416190[];
extern char *g_00448A50[];
extern char *g_00448EE0[];
extern char *g_00448F00[];
extern char *g_00448F10[];
extern char *g_00448F20[];
extern char *g_00448F40[];
extern char *g_00448F58[];
extern char *g_004490B0[];
extern char *g_00449190[];
extern char *g_004491D8[];
extern char *g_00449240[];
extern char *g_0044B0E0[];
extern char *g_0044C980[];
extern char *g_0044D750[];
extern char *g_0044D918[];
extern char *g_0044D930[];
extern char *g_0044D9C0[];
extern char *g_0044D9F0[];
extern char *g_0044DA20[];
extern char *g_0044E100[];
extern char *g_0044E1D8[];
extern char *g_0044E1E8[];
extern char *g_0044E3C0[];
extern char *g_0044E460[];
extern char *g_0044E5E0[];
extern char *g_004512D0[];
extern char *g_00451850[];
extern char *g_00451858[];
extern char *g_00451868[];
extern char *g_00451898[];
extern char *g_00456328[];
extern char *g_004563F0[];
extern char *g_00456420[];
extern char *g_00456540[];
extern char *g_00456880[];
extern char *g_00456930[];
extern char *g_00457E10[];
extern char *g_00457EA0[];
extern char *g_00457ED8[];
extern char *g_00458490[];
extern char *g_00458644[];
extern char *g_00458740[];
extern char *g_004587E0[];
extern char *g_00458848[];
extern char *g_00458878[];
extern char *g_00458CC0[];
extern char *g_00458CF8[];
extern char *g_00458F40[];

extern int g_00669F9C;
extern int g_0045D098[2];                /* (small data) */
extern int (*g_0044F060[6])(void);
extern short g_007B9980;
extern u8 g_007B9982;
extern int g_007B98A4, g_007B98B4;
extern int g_007B99F0, g_007B99F4, g_007B99F8, g_007B99FC;
extern u8 *g_0045D7C0;                   /* (small data) the current menu */

u32 func_0036FD70(u32 s);
void func_0036FD30(u32 s, int v);
void func_00370020(void);
void func_003703A0(void);
void func_00370A00(void);
void func_00371030(void);
int func_002F2840(int o);
int func_002F4660(int o);
void func_002F46D0(int o, int v);
void func_00371850(void);
void func_00371F00(void);
int func_00327C00(void);
void func_003A92D0(void);
void func_003A80A0(int a);
void func_003A7D90(void);
void func_003A9010(int a);
void func_00374E20(void);
int func_0030D7D0(void);
void func_00375C20(int a, int b, int c, int d, int e);
void func_00376370(u8 *p);

/* 0x00372250, 0x18 bytes, matching. */
char *func_00372250(int k)
{
    return g_00448A50[k];
}

/* 0x003724D0, 0x18 bytes, matching. */
char *func_003724D0(int k)
{
    return g_004490B0[k];
}

/* 0x00372580, 0x18 bytes, matching. */
char *func_00372580(int k)
{
    return g_0044B0E0[k];
}

/* 0x00372630, 0x18 bytes, matching. */
char *func_00372630(int k)
{
    return g_0044D918[k];
}

/* 0x00372660, 0x18 bytes, matching. */
char *func_00372660(int k)
{
    return g_0044D9C0[k];
}

/* 0x003727B0, 0x18 bytes, matching. */
char *func_003727B0(int k)
{
    return g_00416110[k];
}

/* 0x00372A10, 0x18 bytes, matching. */
char *func_00372A10(int k)
{
    return g_00451898[k];
}

/* 0x00372DB0, 0x18 bytes, matching. */
char *func_00372DB0(int k)
{
    return g_00458490[k];
}

/* 0x00372DD0, 0x18 bytes, matching. */
char *func_00372DD0(int k)
{
    return g_00458644[k];
}

/* 0x00372DF0, 0x18 bytes, matching. */
char *func_00372DF0(int k)
{
    return g_00458740[k];
}

/* 0x00372E10, 0x18 bytes, matching. */
char *func_00372E10(int k)
{
    return g_004587E0[k];
}

/* 0x00372E30, 0x18 bytes, matching. */
char *func_00372E30(int k)
{
    return g_00458848[k];
}

/* 0x00372FF0, 0x18 bytes, matching. */
char *func_00372FF0(int k)
{
    return g_00458CC0[k];
}

/* 0x00373010, 0x18 bytes, matching. */
char *func_00373010(int k)
{
    return g_00458CF8[k];
}

/* 0x00373030, 0x18 bytes, matching. */
char *func_00373030(int k)
{
    return g_00458F40[k];
}

/* 0x003727D0, 0x1C bytes. */
char *func_003727D0(int k)
{
    return g_0044E3C0[k - 0x22];
}

/* 0x00372450, 0xC bytes, matching. */
char *func_00372450(void)
{
    return g_00448F00[0];
}

/* 0x00372460, 0xC bytes, matching. */
char *func_00372460(void)
{
    return g_00448F10[0];
}

/* 0x00372470, 0xC bytes, matching. */
char *func_00372470(void)
{
    return g_00448F20[0];
}

/* 0x003724C0, 0xC bytes, matching. */
char *func_003724C0(void)
{
    return g_00448F58[0];
}

/* 0x00372530, 0xC bytes, matching. */
char *func_00372530(void)
{
    return g_004491D8[0];
}

/* 0x00372650, 0xC bytes, matching. */
char *func_00372650(void)
{
    return g_0044D930[0];
}

/* 0x00372740, 0xC bytes, matching. */
char *func_00372740(void)
{
    return g_0044E1E8[0];
}

/* 0x00372890, 0xC bytes, matching. */
char *func_00372890(void)
{
    return g_0044E5E0[0];
}

/* 0x003729F0, 0xC bytes, matching. */
char *func_003729F0(void)
{
    return g_00451858[0];
}

/* 0x00372A00, 0xC bytes, matching. */
char *func_00372A00(void)
{
    return g_00451868[0];
}

/* 0x00372B30, 0xC bytes, matching. */
char *func_00372B30(void)
{
    return g_00456328[0];
}

/* 0x00372E50, 0xC bytes, matching. */
char *func_00372E50(void)
{
    return g_00458878[0];
}

/* 0x00372410, 0x3C bytes, matching. */
char *func_00372410(int k)
{
    if (k < 0 || k > 5)
        return g_004484C8[0];
    return g_00448EE0[k];
}

/* 0x00372480, 0x34 bytes. */
char *func_00372480(int k)
{
    if (k < 3)
        return g_00448F40[k];
    return g_004484C0;
}

/* 0x003724F0, 0x34 bytes, matching. */
char *func_003724F0(int k)
{
    if (k < 5)
        return g_00449190[k];
    return g_00449190[0];
}

/* 0x00372540, 0x34 bytes. */
char *func_00372540(u32 k)
{
    if (k < 9)
        return g_00449240[k];
    return g_00449240[0];
}

/* 0x003725A0, 0x4C bytes. */
char *func_003725A0(int k)
{
    if (k < 100 && k != -1)
        return g_0044C980[k];
    return g_004484C8[0];
}

/* 0x003725F0, 0x34 bytes. */
char *func_003725F0(int k)
{
    if (k < 0x65)
        return g_0044D750[k];
    return g_004484C8[0];
}

/* 0x00372680, 0x30 bytes. */
char *func_00372680(int k)
{
    if (k < 0x3)
        return g_0044D9F0[k];
    return 0;
}

/* 0x003726B0, 0x30 bytes. */
char *func_003726B0(int k)
{
    if (k < 0xA)
        return g_0044DA20[k];
    return 0;
}

/* 0x003726E0, 0x30 bytes. */
char *func_003726E0(int k)
{
    if (k < 0x2D)
        return g_0044E100[k];
    return 0;
}

/* 0x00372710, 0x30 bytes. */
char *func_00372710(int k)
{
    if (k < 0x2)
        return g_0044E1D8[k];
    return 0;
}

/* 0x00372780, 0x30 bytes. */
char *func_00372780(int k)
{
    if (k < 0x5)
        return g_004160F0[k];
    return 0;
}

/* 0x003728A0, 0x30 bytes. */
char *func_003728A0(int k)
{
    if (k < 0x6)
        return g_00416190[k];
    return 0;
}

/* 0x00372990, 0x30 bytes. */
char *func_00372990(int k)
{
    if (k < 0x15C)
        return g_004512D0[k];
    return 0;
}

/* 0x003729C0, 0x30 bytes. */
char *func_003729C0(int k)
{
    if (k < 0x2)
        return g_00451850[k];
    return 0;
}

/* 0x003727F0, 0x38 bytes. */
char *func_003727F0(int k)
{
    if (k < 0 || k > 9)
        return 0;
    return g_0044E460[k];
}

/* 0x00372B40, 0x3C bytes. */
char *func_00372B40(int k)
{
    if (k < 0 || k > 6)
        return g_004484C0;
    return g_004563F0[k];
}

/* 0x00372B80, 0x3C bytes. */
char *func_00372B80(int k)
{
    if (k < 0 || k > 4)
        return g_004484C0;
    return g_00456420[k];
}

/* 0x00372BC0, 0x3C bytes. */
char *func_00372BC0(int k)
{
    if (k < 0 || k > 4)
        return g_004484C0;
    return g_00456540[k];
}

/* 0x00372C00, 0x3C bytes. */
char *func_00372C00(int k)
{
    if (k < 0 || k > 31)
        return g_004484C0;
    return g_00456880[k];
}

/* 0x00372C40, 0x3C bytes. */
char *func_00372C40(int k)
{
    if (k < 0 || k > 1)
        return g_004484C0;
    return g_00456930[k];
}

/* 0x00372CF0, 0x3C bytes. */
char *func_00372CF0(int k)
{
    if (k < 0 || k > 11)
        return g_004484C0;
    return g_00457E10[k];
}

/* 0x00372D30, 0x3C bytes. */
char *func_00372D30(int k)
{
    if (k < 0 || k > 9)
        return g_004484C0;
    return g_00457EA0[k];
}

/* 0x00372D70, 0x3C bytes, matching. */
char *func_00372D70(int k)
{
    if (k < 0 || k > 1)
        return g_004484C0;
    return g_00457ED8[k];
}

/* 0x00370140, 0x70 bytes. Every 50 frames, both sides' counters go up (0xFF at most). */
void func_00370140(void)
{
    u32 s;

    if (g_00669F9C % 0x32 != 0)
        return;
    for (s = 0; s < 2; s++) {
        u32 v = func_0036FD70(s);

        if (v < 0xFF)
            func_0036FD30(s, v + 1);
    }
}

/* 0x003701B0, 0x24 bytes, matching. */
void func_003701B0(void)
{
    func_00370020();
    func_00370140();
}

/* 0x003710C0, 0x2C bytes, matching. */
void func_003710C0(void)
{
    func_003703A0();
    func_00370A00();
    func_00371030();
}

/* 0x00371230, 0x88 bytes. Raises officer `o`'s value to `v`. */
void func_00371230(u32 o, int v)
{
    if (o < 0x19F && func_002F2840(o) != 0) {
        if (v < func_002F4660(o))
            v = func_002F4660(o);
        func_002F46D0(o, v);
    }
}

/* 0x003712C0, 0x50 bytes, matching. */
void func_003712C0(int a, int b, int c, int v)
{
    if (b == a || c == a) {
        func_00371230(b, v);
        func_00371230(c, v);
    }
}

/* 0x00372200, 0x24 bytes, matching. */
void func_00372200(void)
{
    func_00371850();
    func_00371F00();
}

/* 0x00372230, 0x1C bytes, matching. */
void func_00372230(void)
{
    func_00372200();
}

/* 0x00372750, 0x2C bytes. */
int func_00372750(int k)
{
    if (k < 2)
        return g_0045D098[k];
    return 0;
}

/* 0x003728D0, 0x34 bytes. */
int func_003728D0(u32 k)
{
    if (k < 6)
        return g_0044F060[k]();
    return 0;
}

/* 0x00373640, 0x64 bytes. */
int func_00373640(void)
{
    if (func_00327C00() > 5) {
        switch (g_007B9980) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
            return 1;
        }
    }
    return 0;
}

/* 0x003736B0, 0x68 bytes. */
int func_003736B0(void)
{
    if (func_00327C00() < 6)
        return 0;
    return g_007B9980 == 10 || g_007B9980 == 0xC || g_007B9980 == 6;
}

/* 0x00373720, 0x68 bytes. */
int func_00373720(void)
{
    if (func_00327C00() < 6)
        return 0;
    return g_007B9980 == 9 || g_007B9980 == 8 || g_007B9980 == 5;
}

/* 0x00373790, 0x10 bytes. */
void func_00373790(int v)
{
    g_007B9982 = v != 0;
}

/* 0x003737A0, 0x40 bytes. */
int func_003737A0(void)
{
    return g_007B98A4 == 0x11 || g_007B98A4 == 0xF || g_007B98A4 == 0xD;
}

/* 0x00373A10, 0x60 bytes. */
int func_00373A10(void)
{
    if (g_007B98A4 < 0x13 || g_007B98A4 > 0x19)
        return g_007B98A4 == 6 || g_007B98A4 == 8 || g_007B98A4 == 9;
    return 1;
}

/* 0x00373F60, 0x44 bytes. */
void func_00373F60(void)
{
    if (g_007B9982 == 0) {
        func_003A92D0();
        func_003A80A0(0);
        func_003A7D90();
        func_003A9010(0);
    }
}

/* 0x00374E00, 0xC bytes. */
short func_00374E00(void)
{
    return g_007B9980;
}

/* 0x00374E10, 0xC bytes. */
int func_00374E10(void)
{
    return g_007B98B4;
}

/* 0x00375B90, 0x60 bytes. The message window's answer (5: none open). */
int func_00375B90(void)
{
    int v = g_007B99FC;

    if (g_007B99F0 == 0)
        v = 5;
    else if (v != 5 && v != 4)
        func_00374E20();
    return v;
}

/* 0x00375BF0, 0x14 bytes. */
int func_00375BF0(void)
{
    return g_007B99F0 == 1;
}

/* 0x00375C10, 0xC bytes. */
int func_00375C10(void)
{
    return g_007B99F8;
}

/* 0x00375CF0, 0x34 bytes, matching. */
void func_00375CF0(void)
{
    func_00375C20(0, func_0030D7D0(), 0xD1, 0, -1);
}

/* 0x00375D30, 0x2C bytes, matching. */
void func_00375D30(int t)
{
    func_00375C20(0, t, 0xD1, 0, -1);
}

/* 0x00375D60, 0x2C bytes, matching. */
void func_00375D60(void)
{
    func_00375C20(0, 0, -1, 0, -1);
}

/* 0x003760C0, 0x20 bytes. */
int func_003760C0(void)
{
    if (g_0045D7C0 == 0)
        return -1;
    return *(int *)(g_0045D7C0 + 0x24);
}

/* 0x003760E0, 0x20 bytes. */
int func_003760E0(void)
{
    if (g_0045D7C0 == 0)
        return -1;
    return *(int *)(g_0045D7C0 + 0x28);
}

/* 0x003762C0, 0x24 bytes, matching. */
void func_003762C0(void)
{
    if (g_0045D7C0 != 0) {
        *(int *)(g_0045D7C0 + 0x44) = 3;
        *(int *)(g_0045D7C0 + 0x54) = 3;
    }
}

/* 0x00376450, 0x34 bytes. */
void func_00376450(void)
{
    if (g_0045D7C0 != 0) {
        func_00376370(g_0045D7C0 + 0x3C);
        func_00376370(g_0045D7C0 + 0x4C);
    }
}

/* 0x00376490, 0x14 bytes, matching. */
void func_00376490(int a, int b)
{
    *(int *)(g_0045D7C0 + 4) = a;
    *(int *)(g_0045D7C0 + 0x10) = b;
}

/* Event results and province picks (parts of 0x00370020-0x00373A08). */

extern char *g_00456080[], *g_00454E60[];

int func_0036FC90(void);
int func_0036FC60(void);
int func_0036FCD0(void);
int func_0036FD00(void);
int func_0036FEF0(int a, int b);
void func_0035CDB0(int a, int b, int c);
void func_0035CD80(int a);
void func_0035CD50(int a);
void func_0035CD20(int a);
u8 *func_00338410(u32 k);
void func_0036FC20(void);
int func_0030AB90(void);
int func_0030AFF0(int p);
int func_0030AD20(int p, int j);
int func_0030CB00(int n);
int func_002F4080(int o);
int func_0030C440(int a, int f);
void func_002F5A10(int o, int v);
int func_002F3DC0(int o);
void func_002F5BE0(int o, int v);
int func_00327820(void);
int func_00327D50(void);
int func_00327D60(void);
void func_003737E0(int k, int a, int b, int p);
int func_0039E6C0(int k);

/* Whether `f` is a force. */
static int is_force(int f)
{
    return f >= 0 && f < func_0030AB90();
}

/* 0x00370020, 0x114 bytes. Sends the pending battle request (kinds 0-3) and marks it sent. */
void func_00370020(void)
{
    int k, g;

    if (func_0036FC90() == 0)
        return;
    k = func_0036FC60();
    g = func_0036FCD0();
    if (k == 3) {
        int h = func_0036FD00();

        func_0035CDB0(g, h, func_0036FEF0(g, h));
    } else if (k == 2) {
        func_0035CD80(g);
    } else if (k == 1) {
        func_0035CD50(g);
    } else if (k == 0) {
        func_0035CD20(g);
    }
    func_00338410(g)[0x2B] |= 0x80;
    func_0036FC20();
}

/* 0x003704C0, 0xA8 bytes. Lists the provinces without an owner; their count. */
int func_003704C0(int *out)
{
    int p, n = 0;

    for (p = 0; p < func_0030AB90(); p++) {
        if (!is_force(func_0030AFF0(p)))
            out[n++] = p;
    }
    return n;
}

/* 0x003707A0, 0x104 bytes. The first of provinces `list` with no free neighbour (else one at
 * random). */
int func_003707A0(int *list, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        int p = list[i], j;

        for (j = 0; j < 6; j++) {
            int q = func_0030AD20(p, j);

            if (q >= 0 && q < func_0030AB90() && !is_force(func_0030AFF0(q)))
                break;
        }
        if (j == 6)
            return i;
    }
    return func_0030CB00(n);
}

/* 0x003708B0, 0xB4 bytes. The first force of officers `list` passing func_0030C440 (else one at
 * random). */
int func_003708B0(int a, int *list, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        int f = func_002F4080(list[i]);

        if (func_0030C440(a, f) != 0)
            return f;
    }
    return func_002F4080(list[func_0030CB00(n)]);
}

/* 0x00370970, 0x84 bytes. Whether an officer of `list` serves force `f`. */
int func_00370970(int *list, int n, int f)
{
    int i;

    for (i = 0; i < n; i++) {
        if (f == func_002F4080(list[i]))
            return 1;
    }
    return 0;
}

/* 0x00371030, 0x88 bytes. Gives every officer a random temper (and a random province when
 * free). */
void func_00371030(void)
{
    int o;

    for (o = 0; o < 0x19F; o++) {
        if (func_002F2840(o) != 0) {
            func_002F5A10(o, func_0030CB00(4));
            if (func_002F3DC0(o) == 0)
                func_002F5BE0(o, func_0030CB00(0x19));
        }
    }
}

/* 0x003717A0, 0xAC bytes. The player force's officers (and the ruler's sworn pairs) start with
 * value 20. */
void func_003717A0(void)
{
    int r = func_00327820(), o;

    for (o = 0; o < 0x19F; o++) {
        if (func_002F4080(o) == func_00327D50())
            func_00371230(o, 0x14);
    }
    func_003712C0(r, 0xD, 7, 0x14);
    func_003712C0(r, 0x11, 0xAF, 0x14);
    func_003712C0(r, 1, 0x16, 0x14);
}

/* 0x00373970, 0x98 bytes. */
void func_00373970(int k, int a, int b)
{
    int p;

    if (k == 6) {
        p = 0;
    } else {
        p = func_00327D60();
        if (!is_force(p))
            p = 0;
    }
    func_003737E0(k, a, b, p);
}

/* 0x00372A30, 0xF8 bytes. The unification text `k` for ruler `o` (two versions by the ruler). */
char *func_00372A30(int k, int o)
{
    if (k >= 0x9D)
        return 0;
    if (o == 5 || o == 6 || o == 10 || o == 0xF || o == 0x15 || o == 0x17)
        return g_00456080[k];
    if (o < 400 || o > 0x19E || o - 400 < 0 || func_0039E6C0(o - 400) != 1)
        return g_00454E60[k];
    return g_00456080[k];
}
