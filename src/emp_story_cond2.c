/*
 * emp_story_cond2.c - Empire story event conditions from 0x003D00D0: each returns 1 when its
 * event can play this turn (dates are 0x00327C80 values, 0x00327C70 the turn, 0x00327820 the
 * player's officer, 0x00327D50 the player's force, 0x002F4080 an officer's province, 0x0030AFF0 a
 * province's force). gp 0x0045D820 receives which variant of the event plays. Original file name
 * unknown (next to the conditions of emp_cmd_misc.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_0045D820;                   /* (small data) the variant */

int func_00327820(void);
int func_00327D50(void);
int func_002F5CC0(int o);
int func_002F4080(int o);
int func_0030AB90(void);
int func_003C1850(void);
int func_00329540(int k);
u32 func_00327C70(void);
u32 func_00327C80(void);
int func_0032EB40(int a, int b, int c);
int func_002F3BB0(int o);
int func_002F3DC0(int o);
int func_003C2090(int f, int p);
int func_0030AFF0(int p);
int func_00329680(int k);
int func_0032EE10(int o);
int func_003C3040(void);
int func_00327C00(void);
int func_002F3770(int o);
int func_003C1460(int a, int p, int v);
int func_003C1120(int o);
int func_00337A10(int k);
int func_003C0C60(int a, int b);

#define PROVINCE_OK(p) ((p) >= 0 && (p) < func_0030AB90())
#define NEED(x) do { if (!(x)) return 0; } while (0)
#define DATE_IN(a, b) (func_00327C80() >= (a) && func_00327C80() < (b))

/* 0x003D00D0, 0x1F0 bytes. Still 0x1BC (officer 0x1A). */
int func_003D00D0(void)
{
    int me = func_00327820(), f = func_00327D50();
    int a = func_002F5CC0(0x1A), p = func_002F4080(0x1A);

    NEED(PROVINCE_OK(a));
    NEED(func_003C1850() == 0);
    NEED(func_00329540(0x1BC) == 0);
    NEED(func_00327C70() >= 0xB);
    NEED(func_0032EB40(me, 0x19, 0) != 0);
    NEED(PROVINCE_OK(p));
    NEED(func_0032EB40(me, 0x1A, 1) == 0);
    NEED(func_002F3BB0(0x1A) == 2);
    NEED(func_002F3DC0(0x1A) != 0);
    NEED(func_002F3DC0(0x1A) != 3);
    NEED(func_003C2090(f, a) != 0);
    if (func_00327D50() != func_0030AFF0(0x12) && func_00327D50() != func_0030AFF0(0x15))
        return 0;
    return 1;
}

/* Event 6 / 7 (officers 4 and 8, one of them the player, both strong). */
static int pair_event(int k, int me, int other, int mine0, int other0, int mine1, int other1)
{
    int a, b;

    NEED(func_00329680(k) == 0);
    a = func_002F4080(me);
    b = func_002F4080(other);
    NEED(PROVINCE_OK(a));
    NEED(PROVINCE_OK(b));
    NEED(func_0032EE10(other) != 0);
    NEED(func_003C3040() != 0);
    NEED(func_00327C00() != 10);
    NEED(func_00327C00() != 0);
    NEED(func_00327C00() != 1);
    NEED(func_00327C00() != 3);
    NEED(func_00327C00() != 4);
    NEED(func_00327C00() != 5);
    NEED(DATE_IN(0x619, 0x61E));
    NEED(func_00327C70() >= 2);
    NEED(func_00327820() == me);
    NEED(func_002F3770(me) >= 1000);
    NEED(func_003C1460(2, a, 1000) >= 3);
    NEED(func_002F3770(other) >= 1000);
    NEED(func_003C1460(2, b, 1000) >= 3);
    NEED(func_003C1460(1, b, 500) >= 3);
    if (func_00327C00() == 2) {
        NEED(func_0030AFF0(mine0) == func_00327D50());
        NEED(b == func_0030AFF0(other0));
    } else {
        NEED(func_0030AFF0(mine1) == func_00327D50());
        NEED(b == func_0030AFF0(other1));
    }
    return func_003C1120(other) == 0;
}

/* 0x003D02D0, 0x334 bytes. Event 6. */
int func_003D02D0(void)
{
    return pair_event(6, 4, 8, 0, 3, 5, 8);
}

/* 0x003D0610, 0x334 bytes. Event 7. */
int func_003D0610(void)
{
    return pair_event(7, 8, 4, 3, 0, 8, 5);
}

/* 0x003D0950, 0x160 bytes. Whether four provinces have their expected owners. */
int func_003D0950(int a, int b, int c, int d)
{
    NEED(PROVINCE_OK(a));
    NEED(PROVINCE_OK(b));
    NEED(PROVINCE_OK(c));
    NEED(PROVINCE_OK(d));
    NEED(a == func_0030AFF0(0xB));
    NEED(a == func_0030AFF0(0xC));
    NEED(b == func_0030AFF0(10));
    NEED(d == func_0030AFF0(7));
    return c == func_0030AFF0(0xD);
}

/* The common part of events 8 and 9 (officers 2, 0x10, 0x12 and the text record 0xF4's). */
static int trio_common(int o, int *a, int *b, int *c, int *d)
{
    *a = func_002F4080(2);
    *b = func_002F4080(0x10);
    *c = func_002F4080(0x12);
    *d = func_002F4080(o);
    NEED(PROVINCE_OK(*a));
    NEED(PROVINCE_OK(*b));
    NEED(PROVINCE_OK(*c));
    NEED(PROVINCE_OK(*d));
    NEED(func_0032EE10(2) != 0);
    NEED(func_0032EE10(0x10) != 0);
    NEED(func_0032EE10(0x12) != 0);
    NEED(func_0032EE10(o) != 0);
    NEED(func_003C3040() != 0);
    NEED(func_003C1850() == 0);
    NEED(func_00327C00() != 10);
    NEED(DATE_IN(0x622, 0x627));
    NEED(func_00327C70() >= 2);
    return 1;
}

/* 0x003D0AB0, 0x56C bytes. Event 8 (as officer 2 or 0x10). */
int func_003D0AB0(void)
{
    int o = func_00337A10(0xF4), a, b, c, d;

    NEED(func_00329680(8) == 0);
    NEED(trio_common(o, &a, &b, &c, &d));
    NEED(func_002F3770(2) >= 1000);
    NEED(func_002F3770(0x10) >= 1000);
    if (func_00327820() == 2) {
        NEED(func_003C1460(2, a, 1000) >= 3);
        NEED(func_003C1460(2, b, 1000) >= 1);
        NEED(func_002F3770(0x12) >= 1000);
        NEED(func_002F3770(5) >= 1000);
        NEED(func_002F3770(o) >= 1000);
        NEED(func_003C1460(2, c, 1000) >= 3);
        NEED(func_003C1460(1, c, 500) >= 3);
        NEED(func_003D0950(a, b, c, d) != 0);
        NEED(func_003C0C60(a, b) != 0);
        NEED(func_003C0C60(a, c) == 0);
        NEED(func_003C0C60(a, d) == 0);
        g_0045D820 = 0;
        return 1;
    }
    NEED(func_00327820() == 0x10);
    NEED(func_003C1460(2, b, 1000) >= 2);
    NEED(func_003C1460(2, a, 1000) >= 2);
    NEED(func_002F3770(0x12) >= 1000);
    NEED(func_002F3770(5) >= 1000);
    NEED(func_002F3770(o) >= 1000);
    NEED(func_003C1460(2, c, 1000) >= 3);
    NEED(func_003C1460(1, c, 500) >= 3);
    NEED(func_003D0950(a, b, c, d) != 0);
    NEED(func_003C0C60(b, a) != 0);
    NEED(func_003C0C60(b, c) == 0);
    NEED(func_003C0C60(b, d) == 0);
    g_0045D820 = 1;
    return 1;
}

/* 0x003D1020, 0x570 bytes. Event 9 (as officer 0x12 or the text record 0xF4's). */
int func_003D1020(void)
{
    int o = func_00337A10(0xF4), a, b, c, d;

    NEED(func_00329680(9) == 0);
    NEED(trio_common(o, &a, &b, &c, &d));
    NEED(func_002F3770(0x12) >= 1000);
    NEED(func_002F3770(5) >= 1000);
    NEED(func_002F3770(o) >= 1000);
    if (func_00327820() == 0x12) {
        NEED(func_003C1460(2, c, 1000) >= 3);
        NEED(func_003C1460(2, d, 1000) >= 1);
        NEED(func_002F3770(2) >= 1000);
        NEED(func_002F3770(0x10) >= 1000);
        NEED(func_003C1460(2, a, 1000) >= 3);
        NEED(func_003C1460(1, a, 500) >= 3);
        NEED(func_003D0950(a, b, c, d) != 0);
        NEED(func_003C0C60(c, d) != 0);
        NEED(func_003C0C60(c, a) == 0);
        NEED(func_003C0C60(c, b) == 0);
        NEED(func_0032EB40(0x12, 5, 0) != 0);
        g_0045D820 = 0;
        return 1;
    }
    NEED(o == func_00327820());
    NEED(func_003C1460(2, c, 1000) >= 2);
    NEED(func_003C1460(2, d, 1000) >= 2);
    NEED(func_002F3770(2) >= 1000);
    NEED(func_002F3770(0x10) >= 1000);
    NEED(func_003C1460(2, a, 1000) >= 3);
    NEED(func_003C1460(1, a, 500) >= 3);
    NEED(func_003D0950(a, b, c, d) != 0);
    NEED(func_003C0C60(d, c) != 0);
    NEED(func_003C0C60(d, a) == 0);
    NEED(func_003C0C60(d, b) == 0);
    g_0045D820 = 1;
    return 1;
}

/* 0x003D1590, 0x338 bytes. Event 10 (as officer 3, officers 2, 0xD, 0x1B). */
int func_003D1590(void)
{
    int a, b, c, d;

    NEED(func_00329680(10) == 0);
    a = func_002F4080(3);
    b = func_002F4080(2);
    c = func_002F4080(0xD);
    d = func_002F4080(0x1B);
    NEED(PROVINCE_OK(a));
    NEED(PROVINCE_OK(b));
    NEED(PROVINCE_OK(c));
    NEED(PROVINCE_OK(d));
    NEED(func_0032EE10(2) != 0);
    NEED(func_0032EE10(0xD) != 0);
    NEED(func_0032EE10(0x1B) != 0);
    NEED(func_003C3040() != 0);
    NEED(func_003C1850() == 0);
    NEED(func_00327C00() != 10);
    NEED(DATE_IN(0x62E, 0x633));
    NEED(func_00327C70() >= 2);
    NEED(func_00327820() == 3);
    NEED(func_002F3770(3) >= 1000);
    NEED(func_003C1460(2, a, 1000) >= 3);
    NEED(func_003C1460(1, a, 500) >= 3);
    NEED(func_002F3770(2) >= 1000);
    NEED(func_003C1460(2, b, 1000) >= 3);
    NEED(a == func_0030AFF0(0xE));
    NEED(func_003C0C60(a, b) != 0);
    NEED(func_003C0C60(a, c) == 0);
    return func_003C0C60(a, d) == 0;
}

int func_003C16F0(int a, int p, int v);
int func_002FB3B0(int p);

/* The common start of events 0xC/0xD (officers 0x10, 0x11, text records 0xAB and 0xC1). */
static int quad_common(int o1, int o2, int *a, int *b, int *c, int *d)
{
    *a = func_002F4080(o1);
    *b = func_002F4080(0x10);
    *c = func_002F4080(0x11);
    *d = func_002F4080(o2);
    NEED(PROVINCE_OK(*a));
    NEED(PROVINCE_OK(*b));
    NEED(PROVINCE_OK(*c));
    NEED(PROVINCE_OK(*d));
    NEED(func_003C3040() != 0);
    NEED(func_003C1850() == 0);
    NEED(func_00327C00() != 10);
    NEED(DATE_IN(0x640, 0x645));
    NEED(func_00327C70() >= 2);
    return 1;
}

/* 0x003D2060, 0x470 bytes. Event 0xD. */
int func_003D2060(void)
{
    int o1 = func_00337A10(0xAB), o2 = func_00337A10(0xC1), a, b, c, d;

    NEED(func_00329680(0xD) == 0);
    NEED(quad_common(o1, o2, &a, &b, &c, &d));
    NEED(func_0032EE10(o1) != 0);
    NEED(func_0032EE10(0x10) != 0);
    NEED(func_0032EE10(0x11) != 0);
    NEED(func_0032EE10(o2) != 0);
    NEED(o1 == func_00327820() || func_003C1120(o1) != 0);
    NEED(func_002F3770(0x11) >= 1000);
    NEED(func_002F3770(0x13) >= 1000);
    NEED(func_002F3770(o2) >= 1000);
    NEED(func_003C16F0(2, a, 1000) >= 3);
    NEED(func_003C16F0(1, a, 500) >= 3);
    NEED(func_002F3770(0x10) >= 1000);
    NEED(func_002F3770(0xE) >= 1000);
    NEED(func_002F3770(0xF) >= 1000);
    NEED(func_003C16F0(1, b, 500) >= 3);
    NEED(func_003C0C60(a, b) == 0);
    NEED(func_003C0C60(c, b) == 0);
    NEED(func_003C0C60(d, b) == 0);
    NEED(func_003C0C60(c, a) != 0);
    NEED(func_003C0C60(d, a) != 0);
    NEED(func_0032EB40(0x10, 0xE, 0) != 0);
    NEED(func_0032EB40(0x11, 0x13, 0) != 0);
    return func_0032EB40(0x10, 0xF, 0) != 0;
}

/* 0x003D24D0, 0x498 bytes. Event 0xC. */
int func_003D24D0(void)
{
    int o1 = func_00337A10(0xAB), o2 = func_00337A10(0xC1), a, b, c, d;

    NEED(func_00329680(0xC) == 0);
    NEED(quad_common(o1, o2, &a, &b, &c, &d));
    NEED(func_0032EE10(0x10) != 0);
    NEED(func_0032EE10(o1) != 0);
    NEED(func_0032EE10(0x11) != 0);
    NEED(func_0032EE10(o2) != 0);
    NEED(func_00327820() == 0x10 || func_003C1120(0x10) != 0);
    NEED(func_002F3770(0x10) >= 1000);
    NEED(func_002F3770(0xE) >= 1000);
    NEED(func_002F3770(0xF) >= 1000);
    NEED(func_003C16F0(2, b, 1000) >= 3);
    NEED(func_003C16F0(1, b, 500) >= 3);
    NEED(func_002F3770(0x11) >= 1000);
    NEED(func_002F3770(0x13) >= 1000);
    NEED(func_002F3770(o2) >= 1000);
    NEED(func_003C16F0(2, b, 1000) >= 3);
    NEED(func_003C16F0(1, b, 500) >= 3);
    NEED(func_003C0C60(b, a) == 0);
    NEED(func_003C0C60(c, b) == 0);
    NEED(func_003C0C60(d, b) == 0);
    NEED(func_003C0C60(c, a) != 0);
    NEED(func_003C0C60(d, a) != 0);
    NEED(func_0032EB40(0x10, 0xE, 0) != 0);
    NEED(func_0032EB40(0x11, 0x13, 0) != 0);
    return func_0032EB40(0x10, 0xF, 0) != 0;
}

/* 0x003D2970, 0x308 bytes. Event 0xE (officer 0x10 and the text record 0xAB's). */
int func_003D2970(void)
{
    int o = func_00337A10(0xAB), a, b;

    NEED(func_00329680(0xE) == 0);
    a = func_002F4080(0x10);
    b = func_002F4080(o);
    NEED(PROVINCE_OK(a));
    NEED(PROVINCE_OK(b));
    NEED(func_0032EE10(o) != 0);
    NEED(func_0032EE10(0x10) != 0);
    NEED(func_003C3040() != 0);
    NEED(func_003C1850() == 0);
    NEED(func_00327C00() != 10);
    NEED(DATE_IN(0x64F, 0x654));
    NEED(func_00327C70() >= 2);
    NEED(func_00327820() == 0x10 || func_003C1120(0x10) != 0);
    NEED(func_0032EB40(o, 0, 0) != 0);
    NEED(func_002F3770(0x10) >= 1000);
    NEED(func_003C16F0(2, a, 1000) >= 3);
    NEED(func_003C16F0(1, a, 500) >= 3);
    NEED(func_002F3770(o) >= 1000);
    NEED(func_002F3770(0) >= 1000);
    NEED(func_003C1460(2, b, 1000) >= 3);
    NEED(func_003C1460(1, b, 500) >= 3);
    NEED(b == func_0030AFF0(0xF));
    NEED(func_002FB3B0(b) < 3);
    return func_003C0C60(a, b) == 0;
}

/* 0x003D2C80, 0x2E8 bytes. Event 0xF (as the text record 0xAB's officer). */
int func_003D2C80(void)
{
    int o = func_00337A10(0xAB), a, b;

    NEED(func_00329680(0xF) == 0);
    a = func_002F4080(o);
    b = func_002F4080(0x10);
    NEED(PROVINCE_OK(a));
    NEED(PROVINCE_OK(b));
    NEED(func_003C3040() != 0);
    NEED(func_003C1850() == 0);
    NEED(func_00327C00() != 10);
    NEED(DATE_IN(0x64F, 0x654));
    NEED(func_00327C70() >= 2);
    NEED(o == func_00327820());
    NEED(func_0032EE10(0x10) != 0);
    NEED(func_002F3770(o) >= 1000);
    NEED(func_002F3770(0) >= 1000);
    NEED(func_003C1460(2, a, 1000) >= 3);
    NEED(func_003C1460(1, a, 500) >= 3);
    NEED(func_002F3770(0x10) >= 1000);
    NEED(func_003C16F0(2, b, 1000) >= 3);
    NEED(func_003C16F0(1, b, 500) >= 3);
    NEED(func_0030AFF0(0xF) == func_00327D50());
    NEED(func_002FB3B0(a) < 3);
    NEED(func_003C0C60(a, b) == 0);
    return func_0032EB40(o, 0, 0) != 0;
}

/* ---- Running the events: a function table per event (0x0041C470), the random events after the
 * story ones, and what happens when an event ends. ---- */

typedef int (*EventFn)(void);
extern EventFn g_0041C470[0x1BE];        /* event starters */
extern EventFn g_0041CB70[10];           /* story event conditions 6..15 */
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

void func_0032F790(void);
int func_002F34E0(int o);
int func_0030CA50(void);
int func_00329370(int k);
int func_002F9060(int f);
int func_002F7D90(int a, int fn, int b, int c, int d, int e);
void func_002F8630(void);
int func_00327E90(void);
void func_003292D0(int a, int v);
int func_003CF030(void);
void func_00334670(int k);
void func_003BAB70(int a);
u8 *func_0030E0F0(void);
int func_0032E8E0(int k);
void func_003BA8F0(int k, int a, int b, int c, int d);
void func_00327A80(int o, int k);
void func_00327EA0(int v);
u32 func_002F9550(int f);
void func_00328290(int v);
void func_00328240(int v);
void func_002F3F70(int o, int p);
void func_002F5BE0(int o, int f);

/* 0x003D2F80, 0x60 bytes. Starts event `k`. */
int func_003D2F80(int k)
{
    if (k < 0 || k > 0x1BD)
        return 0;
    func_0032F790();
    return g_0041C470[k]();
}

/* 0x003D2FE0, 0x210 bytes. The random event of the turn (0x10-0x12), -1 for none. */
int func_003D2FE0(void)
{
    int d = func_00327C80(), r;
    u32 o = func_00327820();
    int s1, s2;
    u32 v;

    if (o >= 0x19F)
        return -1;
    s1 = func_002F34E0(o);
    s2 = func_002F3770(o);
    if (func_0030CA50() >= func_0030AB90())
        return -1;
    if (func_00329370(1) >= 1)
        return -1;
    if (func_00327C70() < 5)
        return -1;
    if (func_002F9060(func_00327D50()) * 10 < 2000)
        return -1;
    if (func_002F7D90(0, (int)func_002F8630, func_00327D50(), 0, 0, 0) < 1)
        return -1;
    if (func_00327E90() >= 1)
        return -1;
    r = (s2 + d + s1) % 0xC;
    if (func_00327E90() < -4) {
        if (r != 0 && r != 6)
            return -1;
    } else if (r != 0) {
        return -1;
    }
    func_003292D0(1, 4);
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    v = (g_7000015C >> 0x10) % 10;
    if (v < 7)
        return 0x10;
    if (v < 9)
        return 0x11;
    return 0x12;
}

/* 0x003D31F0, 0x84 bytes. The event to play: the first story event whose condition holds, else a
 * random one. */
int func_003D31F0(void)
{
    int k;

    for (k = 0; k < 10; k++) {
        if (g_0041CB70[k]() != 0)
            return k + 6;
    }
    k = func_003D2FE0();
    if (k == -1)
        k = -1;
    return k;
}

/* 0x003D3280, 0x34 bytes, matching. */
void func_003D3280(void)
{
    if (func_003CF030() != 0) {
        func_00334670(0x16D);
        func_003BAB70(1);
    }
}

#define NONE (-1)

/* 0x003D32C0, 0x3F4 bytes. The after-effects of event `k`. */
void func_003D32C0(int k)
{
    int me = func_00327820(), f = func_00327D50(), o, i;
    u8 *ev = func_0030E0F0();

    switch (k) {
    case 0xC:
    case 0xD:
    case 0xE:
        func_00334670(0xC);
        func_00334670(0xD);
        func_00334670(0xE);
        func_003BAB70(0);
        return;
    case 0x10:
    case 0x11:
    case 0x12:
        func_00334670(0x10);
        func_00334670(0x11);
        func_00334670(0x12);
        func_003BA8F0(0x21, func_0032E8E0(1), NONE, NONE, NONE);
        break;
    case 0x14:
        if (func_003C1850() == 0)
            func_003BAB70(1);
        break;
    case 0x15:
        func_003BAB70(2);
        break;
    case 0x16:
        func_003BAB70(3);
        break;
    case 0x17:
        for (i = 0; i < 4; i++) {
            if ((u32)func_0032E8E0(i) < 0x19F)
                func_00327A80(func_0032E8E0(i), i);
        }
        func_003292D0(0x17, 4);
        func_003BA8F0(0x12, func_0032E8E0(0), NONE, NONE, NONE);
        break;
    case 0x27:
        func_003BAB70(4);
        break;
    case 0x2A:
        o = func_0032E8E0(0);
        if (f == func_002F4080(o))
            func_003BA8F0(4, o, NONE, NONE, NONE);
        break;
    case 0x2B:
        o = func_0032E8E0(0);
        i = func_002F5CC0(o);
        if (f == func_002F4080(o))
            func_003BA8F0(1, i, o, NONE, NONE);
        break;
    case 0x34:
        func_00327EA0(-1);
        func_003BA8F0(0x11, NONE, NONE, NONE, NONE);
        break;
    case 0x35:
        func_00327EA0(1);
        func_003BA8F0(0x10, NONE, NONE, NONE, NONE);
        break;
    case 0x36:
        *(u32 *)(ev + 8) = func_002F9550(f) & 0xFFFF;
        break;
    case 0x37:
        func_003BA8F0(0xF, me, 2, NONE, NONE);
        break;
    case 0x38:
        func_003BA8F0(0xF, me, 1, NONE, NONE);
        break;
    case 0x39:
        func_003BA8F0(0xF, me, 0, NONE, NONE);
        break;
    case 0x3A:
        func_003BA8F0(0x20, NONE, NONE, NONE, NONE);
        break;
    case 0x3E:
        func_003BA8F0(0x13, NONE, NONE, NONE, NONE);
        break;
    case 0x77:
        func_00327EA0(1);
        break;
    case 0x78:
        func_00327EA0(-1);
        break;
    case 0x10B:
        func_00328290(1);
        func_003BA8F0(0xD, func_00337A10(0x8C), 0xF, NONE, NONE);
        break;
    case 0x122:
        func_00328240(1);
        func_003BA8F0(0xD, 0x12, 5, NONE, NONE);
        func_002F3F70(5, func_002F4080(0x12));
        func_002F5BE0(5, func_002F5CC0(0x12));
        break;
    case 0x16B:
        func_00328240(3);
        func_003BA8F0(0xD, 0x1B, 5, NONE, NONE);
        break;
    }
}

/* ---- Event pictures: two loaded files (gp 0x0045D828: a picture bank, a model?). ---- */

extern u32 g_0045D828[2];                /* (small data) */
extern char g_0045C3F0[];                /* this source file's name */

u32 func_001026D0(int a, int k, int b, int c, int d, int e, const char *file, int line);
void func_00102EC0(u32 h);
void func_00102960(int a);
void func_001ABB00(u32 h, int a, int b, int c, int d, int e, int f, int g);
void func_001ABE40(u32 h, int k, int a, int b, int c, int d, int e, int f);
void func_001B8F60(int a, int b, int c);
u32 func_00376810(void);
void func_001ABEA0(u32 h, int k, int a, int b, int c, int d, int e, int f);

/* 0x003D36C0, 8 bytes, matching. */
u32 *func_003D36C0(void)
{
    return g_0045D828;
}

/* 0x003D36D0, 0x50 bytes, matching. Loads file 0x8B (kept). */
void func_003D36D0(void)
{
    u32 *p = func_003D36C0();

    *p = func_001026D0(1, 0x8B, 0, 1, 0, 0, g_0045C3F0, 0x1F);
}

/* 0x003D3720, 0x50 bytes, matching. */
void func_003D3720(void)
{
    u32 *p = func_003D36C0();

    *p = func_001026D0(1, 0x8B, 0, 0, 0, 0, g_0045C3F0, 0x26);
}

/* 0x003D3770, 0x38 bytes, matching. */
void func_003D3770(void)
{
    u32 *p = func_003D36C0();

    if (*p != 0) {
        func_00102EC0(*p);
        *p = 0;
    }
}

/* 0x003D37B0, 0xF0 bytes. Draws picture `k` of the bank. */
void func_003D37B0(int k, int x, int y, int a, int b)
{
    u32 *p = func_003D36C0();

    if (p != 0)
        func_001ABB00(*p, k + 5, k + 5, x, y, 0, a, b);
}

/* 0x003D38A0, 0xB8 bytes. */
void func_003D38A0(int k, int a, int b, int c, int d, int e, int f)
{
    u32 *p = func_003D36C0();

    if (p != 0 && k < 5)
        func_001ABE40(*p, k, a, b, c, d, e, f);
}

/* 0x003D3960, 0x20 bytes, matching. */
u32 func_003D3960(void)
{
    return func_003D36C0()[1];
}

/* 0x003D3980, 0x70 bytes, matching. Loads file 0x77 (kept). */
void func_003D3980(void)
{
    u32 h;

    func_00102960(1);
    h = func_001026D0(1, 0x77, 0, 1, 0, 0, g_0045C3F0, 0x67);
    func_003D36C0()[1] = h;
    func_00102960(1);
    func_001B8F60(1, 6, 8);
}

/* 0x003D39F0, 0x50 bytes, matching. */
void func_003D39F0(void)
{
    u32 h = func_001026D0(1, 0x77, 0, 0, 0, 0, g_0045C3F0, 0x78);

    func_003D36C0()[1] = h;
}

/* 0x003D3A40, 0x38 bytes, matching. */
void func_003D3A40(void)
{
    u32 *p = func_003D36C0();

    if (p[1] != 0) {
        func_00102EC0(p[1]);
        p[1] = 0;
    }
}

/* 0x003D3A80, 0xC4 bytes. Draws the face of officer record `k` (0..0x42). */
void func_003D3A80(int x, int y, int a, int b, int c, int d, int k)
{
    if (k >= 0 && k < 0x43)
        func_001ABEA0(func_00376810(), k + 0x37, x, y, 0, b, c, 0);
}
