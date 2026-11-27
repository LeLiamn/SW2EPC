/*
 * emp_battle_pick.c - pieces between 0x003E9800 and 0x003EA46C: the two sides' officer slots of
 * a special battle (slot 0 the leader, then seven officers with their minimum levels), officer
 * level changes by percent and small list helpers. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_0045D100, g_0045D104;       /* (small data) */

u8 *func_003EA000(void);
int func_00327D50(void);
int func_003EA080(void);
int func_003EA0A0(void);
void func_0030CF90(int s, int k, int o);


int func_002F8E50(int f);
void func_00362990(int s, int v);
void func_003EAA50(int k);
int func_002F7D90(int a, int (*fn)(), int b, int c, int d, int e);
int func_002F8160();
u32 *func_002F7B10(void);
int func_002F3770(u32 o);
int func_0011B740(int v);
void func_002F3860(u32 o, int v);
void func_002F37E0(u32 o, int v);
void func_003EA470(int a, int b, int *c, int n, int d, int e, int f, int g);
void func_003EA820(int s, int k, int f, int lv);
void func_003EAA20(int s, int k, int f, int lv, int *a, int b);
void func_003EA430(int a, int b, int c, int d, int e, int f, int g);
int func_003EA3F0(int v, int *l, int n);
int func_003EA660(int a, int b, int *list, int n);
int func_003EA8B0(int a, int b, int *list, int n);

/* The seven officer slots of side `s` from force `f`. */
static void side_slots(int s, int f)
{
    func_003EA820(s, 2, f, 1000);
    func_003EA820(s, 3, f, 500);
    func_003EA820(s, 4, f, 500);
    func_003EA820(s, 5, f, 500);
    func_003EA820(s, 6, f, 1000);
}

/* 0x003E9800, 0x1BC bytes. */
void func_003E9800(void)
{
    u8 *p = func_003EA000();
    int a, b;

    func_00327D50();
    a = func_003EA080();
    b = func_003EA0A0();
    func_0030CF90(0, 0, *(int *)(p + 8));
    func_003EAA20(0, 1, a, 1000, &g_0045D100, 1);
    side_slots(0, a);
    func_003EA820(0, 7, a, 500);
    func_0030CF90(1, 0, 8);
    func_003EA820(1, 1, b, 1000);
    side_slots(1, b);
    func_003EA820(1, 7, b, 500);
    func_00362990(0, func_002F8E50(a));
    func_00362990(1, func_002F8E50(b));
    func_003EAA50(6);
}

/* 0x003E9C00, 0x1BC bytes. The same with the forces swapped (the last slot from the first). */
void func_003E9C00(void)
{
    u8 *p = func_003EA000();
    int a, b;

    func_00327D50();
    a = func_003EA0A0();
    b = func_003EA080();
    func_0030CF90(0, 0, *(int *)(p + 8));
    func_003EAA20(0, 1, a, 1000, &g_0045D104, 1);
    side_slots(0, a);
    func_003EA820(0, 7, a, 500);
    func_0030CF90(1, 0, 4);
    func_003EA820(1, 1, b, 1000);
    side_slots(1, b);
    func_003EA820(1, 7, a, 500);
    func_00362990(0, func_002F8E50(a));
    func_00362990(1, func_002F8E50(b));
    func_003EAA50(7);
}

/* 0x003EA200, 0x104 bytes. Changes the levels of force `f`'s officers by `pct` percent. */
void func_003EA200(int f, int pct)
{
    int n = func_002F7D90(0, func_002F8160, f, 0, 1, 0), k;
    u32 *l = func_002F7B10();

    for (k = 0; k < n; k++, l++) {
        if (pct < 0)
            func_002F3860(*l, func_002F3770(*l) * func_0011B740(pct) / 100);
        else
            func_002F37E0(*l, pct * func_002F3770(*l) / 100);
    }
}

/* 0x003EA3F0, 0x38 bytes. Whether `v` is in the list. */
int func_003EA3F0(int v, int *l, int n)
{
    int k;

    for (k = 0; k < n; k++, l++) {
        if (v == *l)
            return 1;
    }
    return 0;
}

/* 0x003EA430, 0x3C bytes, matching. */
void func_003EA430(int a, int b, int c, int d, int e, int f, int g)
{
    int t = c;

    func_003EA470(a, b, &t, 1, d, e, f, g);
}

int func_002F3E70(int o);
int func_0030CB50(int pct);
int func_00327C00(void);
int func_00327C40(void);
void func_00362350(int v);
void func_00362550(int k);
void func_00362630(int s, int v);
void func_00362590(int v);
int func_0030AB90(void);
int func_002FAFA0(int f, int p);
int func_003E99C0(void);
int func_003E9DC0(void);
int func_003EB380(void);
int func_003EB840(void);
int func_003EBD10(void);
int func_003EC400(void);
int func_003ED310(void);
int func_003ECC20(void);
int func_003EDBD0(void);
int func_003EE170(void);
int func_003F8840(void);
void func_003EA010(void);

/* 0x003EA660, 0x1B4 bytes. Whether officer `b` should come before `a` (listed ones first, then
 * the free ones, then by level; ties at random). */
int func_003EA660(int a, int b, int *list, int n)
{
    if (list != 0 || n != 0) {
        int x = func_003EA3F0(a, list, n), y = func_003EA3F0(b, list, n);

        if (y < x)
            return 1;
        if (x < y)
            return 0;
    }
    if (func_002F3E70(a) == 0 && func_002F3E70(b) != 0)
        return 1;
    if (func_002F3E70(a) == 0 && func_002F3E70(b) == 0) {
        u32 ka = func_002F3770(a) << 0x10 | (a < 0x1C ? 0x8000 : 0)
                 | (a < 400 || a > 0x19E ? 0 : 0x4000);
        u32 kb = func_002F3770(b) << 0x10 | (b < 0x1C ? 0x8000 : 0)
                 | (b < 400 || b > 0x19E ? 0 : 0x4000);

        if (ka < kb || (ka == kb && func_0030CB50(0x32) != 0))
            return 1;
    }
    return 0;
}

/* 0x003EA820, 0x28 bytes, matching. */
void func_003EA820(int s, int k, int f, int lv)
{
    func_003EA430(s, k, f, lv, (int)func_003EA660, 0, 0);
}

/* 0x003EA850, 0x2C bytes, matching. */
void func_003EA850(int s, int k, int f, int lv, int a, int b)
{
    func_003EA430(s, k, f, lv, (int)func_003EA660, a, b);
}

/* 0x003EA880, 0x2C bytes, matching. */
void func_003EA880(int s, int k, int *l, int n, int lv, int a, int b)
{
    func_003EA470(s, k, l, n, lv, (int)func_003EA660, a, b);
}

/* 0x003EA8B0, 0x16C bytes. The same order without the free officers rule. */
int func_003EA8B0(int a, int b, int *list, int n)
{
    u32 ka, kb;

    if (list != 0 || n != 0) {
        int x = func_003EA3F0(a, list, n), y = func_003EA3F0(b, list, n);

        if (y < x)
            return 1;
        if (x < y)
            return 0;
    }
    ka = (a < 0x1C ? 0x80000000 : 0) | (a < 400 || a > 0x19E ? 0 : 0x40000000) | func_002F3770(a);
    kb = (b < 0x1C ? 0x80000000 : 0) | (b < 400 || b > 0x19E ? 0 : 0x40000000) | func_002F3770(b);
    return ka < kb || (ka == kb && func_0030CB50(0x32) != 0);
}

/* 0x003EAA20, 0x2C bytes, matching. */
void func_003EAA20(int s, int k, int f, int lv, int *a, int b)
{
    func_003EA430(s, k, f, lv, (int)func_003EA8B0, (int)a, b);
}

/* 0x003EAA50, 0x110 bytes. Sets up special battle `k` (its stage and weather?). */
void func_003EAA50(int k)
{
    int v = k;

    switch (k) {
    case 6:
    case 7:
        v = 0x19;
        break;
    case 8:
    case 9:
        v = 0x1A;
        break;
    case 10:
    case 0xB:
        v = 0x1B;
        break;
    case 0xC:
    case 0xD:
        v = 0x1C;
        break;
    case 0xE:
    case 0xF:
        v = 0x1D;
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        switch (func_00327C00()) {
        case 0:
        case 1:
        case 5:
            v = 3;
            break;
        case 2:
        case 4:
            v = 5;
            break;
        case 3:
            v = 0x37;
            break;
        default:
            v = 0x10;
            break;
        }
        break;
    }
    func_00362350(v);
    func_00362550(k);
    func_00362630(0, 10);
    func_00362630(1, 10);
    func_00362590(func_00327C40());
}

/* 0x003EAB60, 0xA8 bytes. Force `f`'s provinces then `f`; their count. */
int func_003EAB60(int f, int *out)
{
    int n = 0, p;

    for (p = 0; p < func_0030AB90(); p++) {
        if (func_002FAFA0(f, p) != 0)
            out[n++] = p;
    }
    out[n] = f;
    return n + 1;
}

/* 0x003EAC10, 0x100 bytes, matching. Whether special battle `k` happens this turn. */
int func_003EAC10(int k)
{
    int r = 0;

    switch (k) {
    case 6:
        r = func_003E99C0();
        break;
    case 7:
        r = func_003E9DC0();
        break;
    case 8:
        r = func_003EB380();
        break;
    case 9:
        r = func_003EB840();
        break;
    case 10:
        r = func_003EBD10();
        break;
    case 0xB:
        r = func_003EC400();
        break;
    case 0xC:
        r = func_003ED310();
        break;
    case 0xD:
        r = func_003ECC20();
        break;
    case 0xE:
        r = func_003EDBD0();
        break;
    case 0xF:
        r = func_003EE170();
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        r = func_003F8840();
        break;
    }
    func_003EA010();
    return r;
}

/* ---- The special battles' turn step and set-ups (state 0x007BFB48, kind 0x007BFB4C), parts of
 * 0x003EAD10-0x003EBD6C. ---- */

extern int g_007BFB48, g_007BFB4C;
extern int g_0045D108, g_0045D10C, g_0045D110[2], g_0045D118, g_0045D11C;
extern int g_0041D7F0[4];

void func_00376100(int a, int b, int c);
int func_003296F0(void);
int func_003E9B80(void);
int func_003E9F80(void);
int func_003EB5D0(void);
int func_003EBAA0(void);
int func_003EC0B0(void);
int func_003EC8F0(void);
int func_003ED910(void);
int func_003ECFC0(void);
int func_003EDED0(void);
int func_003EE3A0(void);
int func_003F8AB0(void);
int func_002FB9D0(int f);
int func_002FA970(int f);
void func_002FA8E0(int f, int v);
void func_003280C0(int v);
int func_0036B260(void);
void func_003BC6B0(int k, int v);
void func_003A7D90(void);
void func_003EB1A0(void);
void func_003EB650(void);
void func_003EBB20(void);
void func_003EC220(void);
void func_003ED040(void);
void func_003EC970(void);
void func_003ED990(void);
void func_003EDF50(void);
void func_003F8740(int k);
void func_003622F0(int a, int b);
void func_003638D0(void);
int func_003EA0C0(void);
int func_003EA0E0(void);
int func_003EA100(void);
int func_003EA120(void);
int func_003EA140(void);
void func_0030E140(int a, int b, int c, int d);
int func_00375BF0(void);
int func_00375B90(void);
void func_003EA310(int f);
void func_003EA1C0(int f);
void func_003EA330(int f);
int func_002F8CB0(int f);
void func_002FAF30(int f, int g);

/* 0x003EAD10, 0x1E0 bytes. The special battle's step of the turn. */
int func_003EAD10(void)
{
    int r = 5, f = func_00327D50();

    if (g_007BFB48 == 0) {
        func_00376100(4, 5, -1);
        g_007BFB4C = func_003296F0();
    }
    switch (g_007BFB4C) {
    case 6:
        r = func_003E9B80();
        break;
    case 7:
        r = func_003E9F80();
        break;
    case 8:
        r = func_003EB5D0();
        break;
    case 9:
        r = func_003EBAA0();
        break;
    case 10:
        r = func_003EC0B0();
        break;
    case 0xB:
        r = func_003EC8F0();
        break;
    case 0xC:
        r = func_003ED910();
        break;
    case 0xD:
        r = func_003ECFC0();
        break;
    case 0xE:
        r = func_003EDED0();
        break;
    case 0xF:
        r = func_003EE3A0();
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        r = func_003F8AB0();
        break;
    }
    if (g_007BFB48 == 3) {
        int a = func_002FB9D0(f);

        if (func_002FA970(f) < a)
            func_002FA8E0(f, a);
        func_003280C0(func_002FA970(f));
        func_00376100(4, -1, -1);
        r = 0;
        func_003BC6B0(g_007BFB4C, func_0036B260());
        func_003EA010();
        func_003A7D90();
    }
    return r;
}

/* 0x003EAFA0, 0x118 bytes. Sets the special battle up. */
void func_003EAFA0(void)
{
    switch (g_007BFB4C) {
    case 6:
        func_003E9800();
        break;
    case 7:
        func_003E9C00();
        break;
    case 8:
        func_003EB1A0();
        break;
    case 9:
        func_003EB650();
        break;
    case 10:
        func_003EBB20();
        break;
    case 0xB:
        func_003EC220();
        break;
    case 0xC:
        func_003ED040();
        break;
    case 0xD:
        func_003EC970();
        break;
    case 0xE:
        func_003ED990();
        break;
    case 0xF:
        func_003EDF50();
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        func_003F8740(g_007BFB4C - 0x10);
        break;
    }
    func_003622F0(0, 0);
    func_003638D0();
    g_007BFB48 = 0;
}

/* 0x003EB1A0, 0x1DC bytes, matching. */
void func_003EB1A0(void)
{
    u8 *p = func_003EA000();
    int a, b, c, d;

    func_00327D50();
    a = func_003EA0C0();
    b = func_003EA0E0();
    c = func_003EA100();
    d = func_003EA120();
    func_0030CF90(0, 0, *(int *)(p + 8));
    func_003EAA20(0, 1, a, 1000, &g_0045D108, 1);
    func_003EA820(0, 2, a, 1000);
    func_003EA820(0, 3, a, 500);
    func_003EA820(0, 4, a, 500);
    func_003EA820(0, 5, b, 500);
    func_003EAA20(0, 6, b, 1000, &g_0045D10C, 1);
    func_003EA820(0, 7, b, 500);
    func_0030CF90(1, 0, 0x12);
    func_0030CF90(1, 1, 5);
    func_003EA820(1, 2, c, 1000);
    func_003EA820(1, 3, c, 500);
    func_003EA820(1, 4, c, 500);
    func_003EA820(1, 5, c, 500);
    func_0030CF90(1, 6, 0xE8);
    func_003EA820(1, 7, d, 500);
    func_00362990(0, func_002F8E50(a));
    func_00362990(1, func_002F8E50(c));
    func_003EAA50(8);
}

/* 0x003EB650, 0x1E8 bytes, matching. */
void func_003EB650(void)
{
    u8 *p = func_003EA000();
    int a, b, c, d;

    func_00327D50();
    a = func_003EA0C0();
    b = func_003EA0E0();
    c = func_003EA100();
    d = func_003EA120();
    func_0030CF90(0, 0, *(int *)(p + 8));
    func_003EAA20(0, 1, c, 1000, g_0045D110, 2);
    func_003EAA20(0, 2, c, 1000, g_0045D110, 2);
    func_003EA820(0, 3, c, 500);
    func_003EA820(0, 4, c, 500);
    func_003EA820(0, 5, d, 500);
    func_003EAA20(0, 6, d, 1000, &g_0045D118, 1);
    func_003EA820(0, 7, d, 500);
    func_0030CF90(1, 0, 2);
    func_003EA820(1, 1, a, 1000);
    func_003EA820(1, 2, a, 1000);
    func_003EA820(1, 3, a, 500);
    func_003EA820(1, 4, a, 500);
    func_003EA820(1, 5, a, 500);
    func_0030CF90(1, 6, 0x10);
    func_003EA820(1, 7, b, 500);
    func_00362990(0, func_002F8E50(c));
    func_00362990(1, func_002F8E50(a));
    func_003EAA50(9);
}

/* 0x003EB880, 0xB4 bytes. The battle's opening event (by side and result). */
void func_003EB880(void)
{
    u32 *p = (u32 *)func_003EA000();
    int x, y, z;

    if (func_0036B260() == 0) {
        if (func_00327D50() == func_003EA100()) {
            x = 0x82;
            y = 0x12;
            z = 5;
        } else {
            x = 0x84;
            y = 0xE8;
            z = -1;
        }
    } else if (func_00327D50() == func_003EA100()) {
        x = 0x81;
        y = 0x12;
        z = 5;
    } else {
        x = 0x83;
        y = 0xE8;
        z = -1;
    }
    func_0030E140(x, y, z, -1);
    p[0] = 1;
}

/* 0x003EB9D0, 0xC4 bytes. The battle's result on the two forces. */
void func_003EB9D0(void)
{
    u32 *p = (u32 *)func_003EA000();

    if (func_00375BF0() == 0 || func_00375B90() != 1)
        return;
    if (func_0036B260() == 0) {
        func_003EA310(func_003EA0C0());
        func_003EA1C0(func_003EA0C0());
        func_003EA310(func_003EA0E0());
        func_003EA1C0(func_003EA0E0());
    } else {
        func_003EA330(func_003EA0C0());
        func_003EA330(func_003EA0E0());
    }
    p[0] = 3;
}

/* 0x003EBB20, 0x1EC bytes, matching. */
void func_003EBB20(void)
{
    u8 *p = func_003EA000();
    int a, e;

    func_00327D50();
    a = func_003EA0C0();
    e = func_003EA140();
    func_0030CF90(0, 0, *(int *)(p + 8));
    func_003EAA20(0, 1, e, 1000, &g_0045D11C, 1);
    func_003EA820(0, 2, e, 1000);
    func_003EA820(0, 3, e, 500);
    func_003EA820(0, 4, e, 500);
    func_003EA820(0, 5, e, 500);
    func_003EA820(0, 6, e, 1000);
    func_003EA820(0, 7, e, 500);
    func_0030CF90(1, 0, 2);
    func_003EAA20(1, 1, a, 1000, g_0041D7F0, 4);
    func_003EAA20(1, 2, a, 1000, g_0041D7F0, 4);
    func_003EAA20(1, 3, a, 500, g_0041D7F0, 4);
    func_003EAA20(1, 4, a, 500, g_0041D7F0, 4);
    func_003EA820(1, 5, a, 500);
    func_003EA820(1, 6, a, 1000);
    func_003EA820(1, 7, a, 500);
    func_00362990(0, func_002F8E50(e));
    func_00362990(1, func_002F8E50(a));
    func_003EAA50(10);
}

/* 0x003EBD10, 0x60 bytes, matching. */
int func_003EBD10(void)
{
    func_003EA1C0(func_003EA0C0());
    if (func_002F8CB0(func_003EA140()) != 0)
        func_002FAF30(func_003EA0C0(), func_003EA140());
    return 0;
}
