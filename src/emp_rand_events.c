/*
 * emp_rand_events.c - Empire turn events between 0x003300D0 and 0x00334A8C: starting a scene or an
 * event by number (0x0032F770 holds the current one: < 0x1B scenes, < 0x177 story events, < 0x1BE
 * stills), the turn's event dispatcher, and random events (merchants offering stats or horses,
 * officers asking to join, a scripted battle offer). State of the running random event: gp
 * 0x0045D730 (step), 0x0045D738 (an offer was shown), 0x0045D734, 0x0045D72C, 0x0045D728,
 * 0x0045D740 (the chosen officer). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

extern int g_0045D894, g_0045D898, g_0045D89C, g_0045D8A0;  /* scene manager states */
extern u8 g_00669DB2, g_00669DB8;
extern int g_0045D728, g_0045D72C, g_0045D730, g_0045D734, g_0045D738, g_0045D73C;
extern int g_0045D740, g_0045D020;       /* (small data) */
extern char g_0069395E, g_006935DC;
extern u8 g_00500764, g_00500765;
extern u16 g_0050074C;
extern char g_007B4E60[];                /* the message text */
extern char *g_0042D3E0[];               /* stat names ("Vitality"...) */
extern char *g_0042DF00[];               /* horse names ("Chestnut"...) */

typedef struct { int v[7]; } Ints7;
typedef struct { int v[8]; } Ints8;
typedef struct { int v[0xA]; } Ints10;
extern Ints8 g_00415050, g_004150C0;
extern Ints7 g_00415070;
extern Ints10 g_00415090;

#define PAD1_PRESSED() ((g_00500764 & 1) == 0 || (g_00500765 & 1) != 1 ? 0 : g_0050074C)

void func_00228180(void);
void func_0017E0C0(int a, int b);
void func_0017DEA0(int a);
int func_0017E0A0(void);
void func_0017E010(int a);
void func_0017D8E0(int a);
void func_0032F770(int k);
int func_0032F780(void);
void func_0032FAA0(void);
void func_003638D0(void);
void func_0032E7A0(int a);
void func_00334670(int k);
void func_003D32C0(int k);
void func_00329D70(int a);
void func_0023A3D0(void);
void func_0032B730(int k);
void func_0032D110(void);
void func_003698F0(void);
void func_0032B5B0(void);
void func_0032FEF0(int a);
int func_002F4080(int a);
char *func_002F8DB0(int a);
char *func_00390760(int k);
char *func_002F2890(int o);
void func_00374EE0(char *t);
void func_002F7610(int a);
int func_00375B90(void);
void func_003752D0(void);
int func_00337A10(int k);
int func_00329540(int k);
int func_003C0720(void);
void func_0032FF70(int a);
void func_0032E8A0(int a, int b);
void func_0030E100(void);
int func_00327D50(void);
int func_002F9060(int o);
int func_00327AE0(int k);
void func_0032FF10(int a);
int func_00327C70(void);
int func_0032FF00(void);
int func_0032EAC0(void);
void func_003292D0(int a, int v);
int func_00329370(int k);
void func_003D3280(void);
int func_00330650(int k);
void func_0032EFC0(void);
void func_0030E240(void);
void func_0030E210(void);
void func_00376100(int a, int b, int c);
void func_003EAC10(int k);
void func_003295F0(int k, int v);
void func_00331720(int k);
void func_00331860(int k);
void func_003319A0(int k);
void func_003315E0(int k);
int func_003D31F0(void);
int func_0030AB90(void);
int func_00327F60(void);
int func_00327FD0(void);
int func_00328040(void);
int func_003280B0(void);
void func_00327F00(int p);
void func_00327F70(int p);
void func_00327FE0(int p);
void func_00328050(int p);
int func_003293C0(void);
int func_0030C250(int p);
int func_00327E90(void);
int func_002FABC0(int o);
int func_002FAAD0(int o);
void func_002FAB40(int o, int v);
int func_001A06D0(void);
int func_002FA9E0(int o, int k);
void func_002FAA50(int o, int k, int v);
void func_0030E140(int k, int a, int b, int c);
int func_0030E1F0(void);
u8 *func_0030E0F0(void);
void func_002F9130(int o, int v);
char *func_0030CB80(int v);
int func_001204B0(char *to, const char *f, ...);
u8 *func_0019FBC0(int k);
int func_001207E0(const char *a, const char *b);
void func_001A0020(int k);
int func_002F7D90(int a, int fn, int b, int c, int d, int e);
void func_002F86B0(void);
int func_00327820(void);
void func_00327830(int o);
u32 func_00327870(void);
int func_002F4450(u32 o);
int func_002F45A0(u32 o);
int func_002FB430(int o);
int func_0032EB40(int a, int b, int c);
int func_002F3DC0(int o);
int func_002F41E0(int o);
int func_002F3380(int o);
u32 func_002F42F0(int o);
int func_00327B10(int o);
void func_001AFFB0(void);
char *func_002F2A30(int o);
void func_001AEDB0(int a, int b, int c, int d);
void func_001AE9F0(int a, char *t, int b);
void func_001AFC50(int a);
int func_003C1850(void);
int func_00327C00(void);
int func_0032EE10(int k);
void func_003A9170(void);
void func_003A7D90(void);
int func_003A9460(void);
void func_0023AA40(void);
void func_003A9440(void);
void func_003A93B0(int a, int b, int c);
int func_00327C80(void);
int func_0030AFF0(int a);
int func_003C0C60(int a, int b);
void func_003A90E0(int a, int b, int c);
void func_003294E0(int k);
void func_003A4E20(void);
int func_002FB3B0(int o);
int func_00327D60(void);
int func_003303B0(int k);
int func_003301A0(int k);

#define PROVINCE_OK(p) ((p) >= 0 && (p) < func_0030AB90())

/* 0x003300D0, 0x8C bytes. Starts still 0x1BC (a message about officer 0x1A). */
int func_003300D0(void)
{
    func_003303B0(0x1BC);
    func_0032F770(0x1BC);
    func_002F8DB0(func_002F4080(0x1A));
    func_00390760(0x6C);
    func_002F2890(0x1A);
    func_00374EE0(g_007B4E60);
    func_002F7610(0x1A);
    return 5;
}

/* 0x00330160, 0x40 bytes. Waits for the message box to close. */
int func_00330160(void)
{
    if (func_00375B90() == 1) {
        func_0032F770(-1);
        return 0;
    }
    return 5;
}

/* 0x003301A0, 0x14C bytes. Starts scene `k` (< 0x1B). */
int func_003301A0(int k)
{
    func_00228180();
    func_0017E0C0(g_00669DB2 * 8 / 10, 0x1E);
    func_0017DEA0(1);
    func_0032F770(k);
    func_0032FAA0();
    func_003638D0();
    g_0045D894 = g_0045D898;
    g_00669DB8 = 0;
    if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
        g_0045D89C = 9;
    if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D8A0;
        g_0045D89C = 0x18;
    } else {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D89C;
        g_0045D89C = g_0045D8A0;
    }
    func_0032E7A0(1);
    func_00334670(k);
    if (k == 0x17)
        g_0045D734 = 1;
    return 1;
}

/* 0x003302F0, 0x2C bytes, matching. */
void func_003302F0(int k)
{
    func_003D32C0(k);
    func_003301A0(k);
}

/* 0x00330320, 0x8C bytes, matching. Starts story event `k` (0x1B..0x176). */
int func_00330320(int k, int a)
{
    if (k < 0x1B || k > 0x176)
        return 0;
    func_00329D70(a);
    func_0023A3D0();
    func_0032B730(k);
    func_0032F770(k);
    func_0032D110();
    func_003698F0();
    func_0032B5B0();
    func_0032FEF0(3);
    func_00334670(k);
    return 1;
}

/* 0x003303B0, 0x88 bytes, matching. Plays still event `k` (0x177..0x1BD) at once, keeping the music. */
int func_003303B0(int k)
{
    int m = func_0017E0A0();

    if (k < 0x177 || k > 0x1BD)
        return 0;
    func_0032F770(k);
    func_0017D8E0(k - 0x177);
    func_00334670(k);
    func_0032F770(-1);
    if (m != 0x69)
        func_0017E010(m);
    return 1;
}

/* 0x00330440, 0x210 bytes. First-time explanations for screen `s`. */
int func_00330440(int s)
{
    int v = func_00337A10(0xF4);

    switch (s) {
    case 6:
    case 7:
        if (func_00329540(0x1B1) == 0) {
            func_003303B0(0x1B1);
            return 0;
        }
        break;
    case 8:
        if (func_003C0720() == 0) {
            if (func_00329540(0x19) == 0) {
                func_0032FF70(2);
                func_003301A0(0x19);
            }
        } else if (func_00329540(0x1A) == 0) {
            func_0032E8A0(0, 0x10);
            func_003301A0(0x1A);
        }
        break;
    case 9:
        if (func_003C0720() == 0) {
            if (func_00329540(0x1A4) == 0) {
                func_003303B0(0x1A4);
                return 0;
            }
        } else if (func_00329540(0x19) == 0) {
            func_0032FF70(v);
            func_003301A0(0x19);
        }
        break;
    case 10:
        if (func_00329540(0x182) == 0) {
            func_003303B0(0x182);
            return 0;
        }
        break;
    case 0xB:
        if (func_00329540(0x17D) == 0) {
            func_003303B0(0x17D);
            return 0;
        }
        break;
    case 0xC:
    case 0xD:
        if (func_00329540(0x19E) == 0) {
            func_003303B0(0x19E);
            return 0;
        }
        break;
    case 0xE:
        if (func_00329540(0x19) == 0) {
            func_0032FF70(0x10);
            func_003301A0(0x19);
        }
        break;
    case 0xF:
        if (func_00329540(0x1A) == 0) {
            func_0032E8A0(0, 0);
            func_003301A0(0x1A);
        }
        break;
    }
    if (func_0032F780() == -1) {
        func_0023A3D0();
        func_0030E100();
    }
    return 0;
}

/* 0x00331010, 0x88 bytes, matching. A price step from the player's gold. */
int func_00331010(void)
{
    int g = func_002F9060(func_00327D50()) * 10;

    if (g < 5000)
        return 1000;
    if (g < 10000)
        return 2000;
    if (g < 20000)
        return 5000;
    if (g < 50000)
        return 10000;
    return 20000;
}

/* 0x003310A0, 0x170 bytes. The four allies' message (gp 0x0045D734 steps). */
int func_003310A0(void)
{
    if (g_0045D734 == 3) {
        func_003752D0();
        if (func_00375B90() == 1)
            g_0045D734 = 0;
    } else if (g_0045D734 == 2) {
        if (g_0069395E == 0 || g_0069395E == -1)
            g_0045D734 = 3;
    } else {
        if (g_0045D734 != 1)
            return 0;
        func_002F2890(func_00327AE0(0));
        func_002F2890(func_00327AE0(1));
        func_002F2890(func_00327AE0(2));
        func_002F2890(func_00327AE0(3));
        func_00390760(0x131);
        func_00374EE0(g_007B4E60);
        g_0045D734 = 2;
    }
    return 5;
}

/* 0x00331210, 0x34 bytes, matching. Ends the turn's event. */
void func_00331210(void)
{
    func_0023A3D0();
    func_0030E100();
    func_0032FF10(0);
    g_0045D72C = 0;
    g_0045D734 = 0;
}

/* 0x00331250, 0x390 bytes. Runs the event of turn phase `ph`: 5 while one is running. */
int func_00331250(int ph)
{
    int r = 0, k;

    func_00327C70();
    if (func_0032FF00() == 0) {
        switch (ph) {
        case 0:
        case 5:
            if (func_0032F780() == 0x1BC)
                return func_00330160();
            if (func_0032EAC0() == 1) {
                func_003292D0(0, 0);
                if (func_00329370(0) > 0) {
                    func_00331210();
                    return 0;
                }
            }
            break;
        case 1:
            func_003D3280();
            if (func_00329370(0x14) > 0 || func_00329370(0x15) > 0 || func_00329370(0x16) > 0) {
                func_00331210();
                return 0;
            }
            break;
        case 2:
            if (g_0045D734 != 0 && (r = func_003310A0()) == 5)
                return 5;
            if (func_0032EAC0() == 1) {
                func_00331210();
                return r;
            }
            break;
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
            if (g_0045D72C != 0) {
                func_00331210();
                return 0;
            }
            break;
        case 4:
            if (func_00329370(0x10) > 0 || func_00329370(0x11) > 0 || func_00329370(0x12) > 0) {
                func_00331210();
                return 0;
            }
            break;
        case 10:
        case 0xB:
            if (func_00329370(0x3A) > 0) {
                func_00331210();
                return 0;
            }
            break;
        case 0xC:
        case 0xD:
            if (g_0045D72C != 0) {
                func_00331210();
                return 0;
            }
            break;
        }
        k = func_00330650(ph);
        if (k != -1) {
            func_0032F770(k);
            func_0032EFC0();
            func_003D32C0(k);
            if (ph == 0 || ph == 5)
                func_003292D0(0, 2);
            if (ph == 4 || ph == 1)
                func_003292D0(k, 1);
            if (ph == 9)
                func_003292D0(k, 1);
            g_0045D72C = 1;
            if (func_0032F780() == 0x1BC)
                return func_003300D0();
            if (k < 0x1B) {
                func_0032FEF0(1);
                if (func_003301A0(k) != 0)
                    func_0032FEF0(0);
            } else if (k < 0x177) {
                func_00330320(k, 0);
            } else if (k < 0x1BE) {
                func_003303B0(k);
                return 0;
            }
        }
    }
    if (func_0032F780() == -1) {
        func_00331210();
    } else if (func_0032F780() != -1) {
        func_0030E240();
        func_0030E210();
        r = 5;
    }
    return r;
}

/* 0x00331AE0, 0x1C8 bytes. A queued event with a yes/no answer (gp 0x0045D728 steps). */
int func_00331AE0(void)
{
    int r = 5, a;

    if (g_0045D728 == 4) {
        func_003752D0();
        if (func_00375B90() == 1) {
            func_00376100(4, -1, -1);
            g_0045D728 = 0;
            func_003EAC10(g_0045D020);
            func_003295F0(g_0045D020, 2);
            r = 0;
            g_0045D020 = -1;
        }
    } else if (g_0045D728 == 3) {
        func_003752D0();
        if (func_00375B90() == 1) {
            g_0045D728 = 0;
            func_003295F0(g_0045D020, 0);
            r = 0;
            g_0045D020 = -1;
        }
    } else if (g_0045D728 == 2) {
        func_003752D0();
        a = func_00375B90();
        if (a != 5) {
            if (a == 2) {
                g_0045D728 = 3;
                func_00331720(g_0045D020);
            } else if (a == 3) {
                g_0045D728 = 4;
                func_00331860(g_0045D020);
            }
        }
    } else if (g_0045D728 == 1) {
        func_003752D0();
        if (func_00375B90() == 1) {
            func_003319A0(g_0045D020);
            g_0045D728 = 2;
        }
    } else {
        if (g_0045D728 != 0)
            return 5;
        a = func_003D31F0();
        if (a == -1) {
            r = 0;
        } else {
            g_0045D020 = a;
            func_003315E0(a);
            g_0045D728 = 1;
            func_00376100(4, 5, -1);
        }
    }
    return r;
}

/* 0x00331CB0, 0x1B0 bytes. Picks new random provinces for the four rumour slots (50%). */
void func_00331CB0(void)
{
    int k, i, p = 0;

    for (k = 0; k < 4; k++) {
        if (RANDOM() % 100 < 0x32)
            continue;
        for (i = 0; i < func_0030AB90() * 5; i++) {
            int n = func_0030AB90();

            p = n == 0 ? 0 : (int)RANDOM() % n;
            if (p != func_00327F60() && p != func_00327FD0() && p != func_00328040()
                && p != func_003280B0())
                break;
        }
        if (k == 3)
            func_00328050(p);
        else if (k == 2)
            func_00327FE0(p);
        else if (k == 1)
            func_00327F70(p);
        else if (k == 0)
            func_00327F00(p);
    }
}

/* A merchant's gain: how far the closer of the two prices is from 1000, at most `cap`. */
static int merchant_gain(int o, int cap)
{
    int a = func_002FABC0(o), v;

    if (1000 - func_002FAAD0(o) < 1000 - a)
        v = func_002FAAD0(o);
    else
        v = func_002FABC0(o);
    v = 1000 - v;
    if (v > cap - 1)
        v = cap;
    return v;
}

/* A merchant's gift: a stat from list `stats` (0x28 ends it) the player has lowest (0-2), or, when
 * 0x001A06D0 is set, a horse from `horses` not yet in the stable; 0 when there is none. */
static int merchant_gift(int o, int *stats, int *horses)
{
    int s = 0x28, lv, i;

    if (func_001A06D0() == 0) {
        lv = 0;
        do {
            if (stats[0] != 0x28) {
                for (i = 0; stats[i] != 0x28; i++) {
                    if (lv == func_002FA9E0(o, stats[i])) {
                        s = stats[i];
                        break;
                    }
                }
            }
        } while (s == 0x28 && ++lv < 3);
        if (s == 0x28)
            return 0;
        func_002FAA50(o, s, lv + 1);
        func_001204B0(g_007B4E60, func_00390760(8), g_0042D3E0[s], func_0030CB80(lv + 1));
        func_00374EE0(g_007B4E60);
    } else {
        int free;
        char *name;

        do {
            free = 1;
            s = horses[RANDOM() % 6];
            name = g_0042DF00[s];
            for (i = 0; i < 4; i++) {
                if (func_001207E0((char *)func_0019FBC0(i) + 0x13, name) == 0) {
                    free = 0;
                    break;
                }
            }
        } while (!free);
        func_001A0020(s);
        func_001204B0(g_007B4E60, func_00390760(9), name);
        func_00374EE0(g_007B4E60);
    }
    return 1;
}

/* 0x00331E70, 0x78C bytes. The travelling merchant (event 0x41: answers 0x42/0x43). */
int func_00331E70(void)
{
    int o = func_00327D50(), v;
    u32 r1 = (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039);
    u32 r2 = RANDOM();
    Ints8 stats = g_00415050;
    Ints7 horses = g_00415070;

    if (func_00329370(0) > 0) {
        g_0045D738 = 0;
        return 0;
    }
    switch (g_0045D730) {
    case 0:
        func_00331CB0();
        g_0045D738 = 0;
        if (func_00329370(0x41) > 0)
            return 0;
        if (func_003293C0() == 10)
            return 0;
        if (func_0030C250(func_00327F60()) == 0)
            return 0;
        if (func_002F9060(func_00327D50()) < 0x32)
            return 0;
        if (func_00327E90() <= (int)((r1 >> 0x10) % 10))
            return 0;
        if (func_002FABC0(o) == 1000)
            return 0;
        if (func_002FAAD0(o) == 1000)
            return 0;
        if (func_001A06D0() == 0 && func_002FA9E0(o, 0x1E) > 2 && func_002FA9E0(o, 0x1F) > 2
            && func_002FA9E0(o, 0x20) > 2 && func_002FA9E0(o, 0x22) > 2
            && func_002FA9E0(o, 0x23) > 2 && func_002FA9E0(o, 0x24) > 2
            && func_002FA9E0(o, 0x26) > 2)
            return 0;
        func_0030E140(0x41, -1, -1, -1);
        g_0045D730 = 1;
        func_003292D0(0x41, 6);
        g_0045D738 = 1;
        break;
    case 1:
        if (func_0030E1F0() == 2) {
            if (*(int *)(func_0030E0F0() + 0x10) == 0) {
                func_0030E100();
                func_0030E140(0x43, -1, -1, -1);
                g_0045D730 = 3;
            } else {
                func_0030E100();
                func_0030E140(0x42, -1, -1, -1);
                g_0045D730 = 2;
            }
        }
        break;
    case 2:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            g_0045D730 = 4;
        }
        break;
    case 3:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            g_0045D730 = 0;
            return 0;
        }
        break;
    case 4:
        func_002F9130(o, 0x32);
        if (func_00327E90() * 2 + 5 < (int)(r2 % 100)) {
            g_0045D730 = 5;
            v = merchant_gain(o, 5);
            func_002FAB40(o, v + func_002FAAD0(o));
            func_001204B0(g_007B4E60, func_00390760(0x88), func_0030CB80(v));
            func_00374EE0(g_007B4E60);
            return 5;
        }
        g_0045D730 = 6;
        func_002FAB40(o, func_002FAAD0(o) + 1);
        func_001204B0(g_007B4E60, func_00390760(0x89), func_0030CB80(1));
        func_00374EE0(g_007B4E60);
        break;
    case 5:
        func_003752D0();
        if (func_00375B90() == 1) {
            if (!merchant_gift(o, stats.v, horses.v)) {
                g_0045D730 = 0;
                return 0;
            }
            g_0045D730 = 6;
        }
        break;
    case 6:
        func_003752D0();
        if (func_00375B90() == 1) {
            g_0045D730 = 0;
            return 0;
        }
        break;
    }
    return 5;
}

/* 0x00332610, 0x8A4 bytes. The rich merchant (event 0x3E: answers 0x3F/0x40). */
int func_00332610(void)
{
    int o = func_00327D50(), v;
    u32 r1 = (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039);
    u32 r2 = RANDOM();
    Ints10 stats = g_00415090;
    Ints8 horses = g_004150C0;

    if (func_00329370(0) > 0)
        return 0;
    switch (g_0045D730) {
    case 0:
        if (g_0045D738 != 0)
            return 0;
        if (func_00329370(0x3E) != 0)
            return 0;
        if (func_003293C0() == 10)
            return 0;
        if (func_0030C250(func_00327F60()) == 0)
            return 0;
        if (func_002F9060(func_00327D50()) < 100)
            return 0;
        if (func_00327E90() <= (int)((r1 >> 0x10) % 10))
            return 0;
        if ((u32)func_002FABC0(o) <= RANDOM() % 100)
            return 0;
        if (func_002FABC0(o) == 1000)
            return 0;
        if (func_002FAAD0(o) == 1000)
            return 0;
        if (func_001A06D0() == 0 && func_002FA9E0(o, 0x14) > 2 && func_002FA9E0(o, 0x15) > 2
            && func_002FA9E0(o, 0x16) > 2 && func_002FA9E0(o, 0x17) > 2
            && func_002FA9E0(o, 0x18) > 2 && func_002FA9E0(o, 0x19) > 2
            && func_002FA9E0(o, 0x1A) > 2 && func_002FA9E0(o, 0x1B) > 2
            && func_002FA9E0(o, 0x1C) > 2)
            return 0;
        func_0030E140(0x3E, -1, -1, -1);
        g_0045D730 = 1;
        func_003292D0(0x3E, 6);
        return 5;
    case 1:
        if (func_0030E1F0() == 2) {
            if (*(int *)(func_0030E0F0() + 0x10) == 0) {
                func_0030E100();
                func_0030E140(0x40, -1, -1, -1);
                g_0045D730 = 3;
            } else {
                func_0030E100();
                func_0030E140(0x3F, -1, -1, -1);
                g_0045D730 = 2;
            }
        }
        break;
    case 2:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            g_0045D730 = 4;
        }
        break;
    case 3:
        if (func_0030E1F0() == 2) {
            func_0030E100();
            g_0045D730 = 0;
            return 0;
        }
        break;
    case 4:
        func_002F9130(o, 100);
        if (func_00327E90() * 2 + 5 < (int)(r2 % 100)) {
            g_0045D730 = 5;
            v = merchant_gain(o, 5);
            func_002FAB40(o, v + func_002FAAD0(o));
            func_001204B0(g_007B4E60, func_00390760(0x8B), func_0030CB80(v));
        } else {
            g_0045D730 = 6;
            v = merchant_gain(o, 2);
            func_002FAB40(o, v + func_002FAAD0(o));
            func_001204B0(g_007B4E60, func_00390760(0x8C), func_0030CB80(v));
        }
        func_00374EE0(g_007B4E60);
        break;
    case 5:
        func_003752D0();
        if (func_00375B90() == 1) {
            if (!merchant_gift(o, stats.v, horses.v)) {
                g_0045D730 = 0;
                return 0;
            }
            g_0045D730 = 6;
        }
        break;
    case 6:
        func_003752D0();
        if (func_00375B90() == 1) {
            g_0045D730 = 0;
            return 0;
        }
        break;
    }
    return 5;
}

/* A rumour province's event `k`: shown when the province is valid, ours?, the event not seen yet and
 * 0x002F7D90 counts something there. */
static void rumour_event(int p, int k)
{
    if (PROVINCE_OK(p) && func_0030C250(p) != 0 && func_00329370(k) == 0
        && func_002F7D90(0, (int)func_002F86B0, p, 0, 0, 0) > 0) {
        func_0030E140(k, -1, -1, -1);
        g_0045D730 = 10;
        func_003292D0(k, 5);
    }
}

/* 0x00332EC0, 0x2CC bytes. Rumours about three provinces (events 0x74-0x76). */
int func_00332EC0(void)
{
    func_00327D50();
    if (func_00329370(0) > 0)
        return 0;
    if (g_0045D730 == 10) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            g_0045D730 = 0;
            return 0;
        }
    } else {
        if (g_0045D730 != 0)
            return 5;
        if (func_003293C0() == 10)
            return 0;
        if (func_00327E90() < 5)
            return 0;
        rumour_event(func_00327FD0(), 0x74);
        if (g_0045D730 == 0)
            rumour_event(func_00328040(), 0x75);
        if (g_0045D730 == 0)
            rumour_event(func_003280B0(), 0x76);
        if (g_0045D730 == 0) {
            g_0045D730 = 0;
            return 0;
        }
    }
    return 5;
}

/* 0x00333190, 0x4B8 bytes. An officer asks to join (event 0x1D). */
int func_00333190(void)
{
    int me = func_00327820(), o, n1 = 0, n2 = 0, w;
    int list1[0x19F], list2[0x19F];
    char t[0x80], name[0x20], name2[0x20];
    u32 c;

    func_00327D50();
    if (func_00329370(0) > 0)
        return 0;
    if (g_0045D730 == 10) {
        func_003752D0();
        if (func_00375B90() == 1) {
            g_0045D730 = 0;
            return 0;
        }
    } else if (g_0045D730 == 2) {
        if (func_0030E1F0() == 2) {
            func_0030E100();
            func_001204B0(name, func_002F2890(g_0045D740));
            func_001204B0(name2, func_002F2A30(me));
            func_001204B0(g_007B4E60, func_00390760(0x8F), name, name2);
            func_00374EE0(g_007B4E60);
            g_0045D730 = 10;
        }
    } else if (g_0045D730 == 1) {
        if (g_006935DC == 4) {
            func_001AFFB0();
            func_0030E100();
            func_0030E140(0x1D, g_0045D740, me, -1);
            func_00327830(g_0045D740);
            func_003292D0(0x1D, 7);
            g_0045D730 = 2;
        } else if (g_006935DC == 5) {
            func_001AFFB0();
            func_003292D0(0x1D, 7);
            g_0045D730 = 0;
            return 0;
        }
    } else {
        if (g_0045D730 != 0)
            return 5;
        if (func_00329370(0x1D) > 0)
            return 0;
        if (func_003293C0() == 10)
            return 0;
        c = func_00327870();
        if (c < 0x19F && func_002F4450(c) + func_002F45A0(c) < 7)
            return 0;
        if (func_002FB430(func_00327D50()) < 5)
            return 0;
        for (o = 0; o < 0x19F; o++) {
            if (o >= 0 && o < 0x19F && o != me && func_0032EB40(me, o, 0) != 0
                && func_002F3DC0(o) == 2 && func_002F41E0(o) > 4
                && (u32)(func_00327C70() - func_002F3380(o)) > 0x14
                && func_002F42F0(o) > 0xE && func_00327B10(o) == 4
                && o != (int)func_00327870()) {
                if (o < 0x1C || o > 399)
                    list1[n1++] = o;
                else
                    list2[n2++] = o;
            }
        }
        if (n1 < 1) {
            if (n2 < 1)
                return 0;
            w = n2 == 0 ? 0 : (int)RANDOM() % n2;
            g_0045D740 = list2[w];
        } else {
            w = n1 == 0 ? 0 : (int)RANDOM() % n1;
            g_0045D740 = list1[w];
        }
        func_001AEDB0(0, -1, 0x116, 0);
        func_001204B0(t, func_00390760(0x8E), func_002F2890(g_0045D740));
        func_001AE9F0(1, t, 1);
        func_001AFC50(1);
        g_0045D730 = 1;
    }
    return 5;
}

/* 0x00333650, 0x3EC bytes. The scripted alliance battle offer (still 0x1B1, officers 4 and 8). */
int func_00333650(void)
{
    int a = 0x19, b, p1 = 5, p2 = 8;

    if (func_003C1850() != 0) {
        if (func_00327C00() != 2)
            return 0;
        p1 = 0;
        p2 = 3;
    }
    b = a;
    if (g_0045D730 < 10) {
        if (func_0032EE10(4) == 0)
            return 0;
        a = func_002F4080(4);
        if (func_0032EE10(8) == 0)
            return 0;
        b = func_002F4080(8);
        if (!PROVINCE_OK(a))
            return 0;
        if (!PROVINCE_OK(b))
            return 0;
    }
    if (g_0045D730 == 10) {
        func_003752D0();
        if (func_00375B90() == 1) {
            func_003A9170();
            func_003A7D90();
            g_0045D730 = 0;
            return 0;
        }
    } else if (g_0045D730 == 3) {
        func_001204B0(g_007B4E60, func_00390760(0x113));
        func_00374EE0(g_007B4E60);
        g_0045D730 = 10;
    } else if (g_0045D730 == 2) {
        if (func_003A9460() != 0 && (PAD1_PRESSED() & 0x40) == 0)
            return 5;
        func_0023AA40();
        func_003A9440();
        g_0045D730 = 3;
    } else if (g_0045D730 == 1) {
        func_003752D0();
        if (func_00375B90() == 1) {
            func_003303B0(0x1B1);
            func_003A93B0(p1, p2, 0);
            g_0045D730 = 2;
        }
    } else {
        if (g_0045D730 != 0)
            return 5;
        if (func_00327C00() == 10)
            return 0;
        if (func_00329540(0x1B1) != 0)
            return 0;
        if (func_00327C80() != 0x619)
            return 0;
        if ((u32)func_00327C70() < 2)
            return 0;
        if (func_00327820() == 4)
            return 0;
        if (func_00327820() == 8)
            return 0;
        if (func_0030AFF0(p1) != func_002F4080(4))
            return 0;
        if (func_0030AFF0(p2) != func_002F4080(8))
            return 0;
        if (func_003C0C60(a, b) != 0)
            return 0;
        func_001204B0(g_007B4E60, func_00390760(0x112));
        func_00374EE0(g_007B4E60);
        func_003A90E0(0, p1, p2);
        g_0045D730 = 1;
    }
    return 5;
}

/* 0x00334670, 0x24 bytes, matching. Marks event `k` seen. */
void func_00334670(int k)
{
    func_003294E0(k);
    func_003A4E20();
}

/* 0x003346A0, 0x44 bytes. */
int func_003346A0(void)
{
    if (func_003C1850() == 0)
        return func_002FB3B0(func_00327D50()) > 2;
    return 0;
}

/* 0x003346F0, 0x2C bytes, matching. */
int func_003346F0(void)
{
    return func_002FB3B0(func_00327D50()) > 1;
}

/* 0x00334A50, 0x40 bytes. */
int func_00334A50(void)
{
    if (func_003346A0() == 0 && func_003346F0() == 0)
        return 0;
    return 1;
}

typedef struct { int v[6]; } Ints6;
typedef struct { int v[0x19]; } Ints25;
extern Ints6 g_004150E0, g_00415100, g_00415140, g_00415180;
extern Ints8 g_00415120, g_00415160;
extern Ints25 g_004151A0;

/* 0x00334720, 0x324 bytes. The music of the Empire map: by season (0x00327D60) and mode, or 0x1E /
 * 0x1F when the player's force is strong. */
int func_00334720(void)
{
    Ints6 m0 = g_004150E0, m1 = g_00415100, m3 = g_00415140, m5 = g_00415180;
    Ints8 m2 = g_00415120, m4 = g_00415160;
    Ints25 md = g_004151A0;

    if (func_003346A0() != 0)
        return 0x1E;
    if (func_003346F0() != 0)
        return 0x1F;
    switch (func_00327C00()) {
    case 0:
        return m0.v[func_00327D60()];
    case 1:
        return m1.v[func_00327D60()];
    case 2:
        return m2.v[func_00327D60()];
    case 3:
        return m3.v[func_00327D60()];
    case 4:
        return m4.v[func_00327D60()];
    case 5:
        return m5.v[func_00327D60()];
    default:
        return md.v[func_00327D60()];
    }
}

extern char g_00448008[];                /* "" */

char *func_00120928(char *to, const char *from);
char *func_0030ABF0(int p);
int func_002F5CC0(int o);
int func_002F9C90(int a, int b);
void func_002CAD90(int *out);
char *func_00372580(int k);

/* 0x00334A90, 0x570 bytes. The text of news item `k` (< 100) about `a` and `b` into `out`. */
void func_00334A90(char *out, u32 k, int a, int b)
{
    char *s1 = 0, *s2 = 0;
    char t1[0x20], t2[0x20];
    int id = -1, h[2];

    if (k >= 100)
        return;
    if (k == 99) {
        id = 0x7E;
    } else if (k == 0x3A) {
        id = 0x7D;
        s1 = func_002F8DB0(a);
    } else if (k == 0x39) {
        id = 0x7C;
        func_00120928(t1, func_002F8DB0(func_002F4080(a)));
        func_00120928(t2, func_002F2890(a));
        s1 = t2;
        s2 = t1;
    } else if (k == 0x37) {
        id = 0x7B;
        s1 = func_002F8DB0(a);
    } else if (k == 0x36) {
        id = 0x7A;
        s1 = func_0030ABF0(a);
    } else if (k == 0x35) {
        id = 0x79;
        s1 = func_0030ABF0(a);
    } else if (k == 0x34) {
        id = 0x78;
        s1 = func_002F2890(a);
        s2 = func_0030ABF0(func_002F5CC0(a));
    } else if (k == 0x2F) {
        id = 0x77;
        s1 = func_002F8DB0(a);
    } else if (k == 0x2E) {
        id = func_002F9C90(func_00327D50(), a) == 3 ? 0x76 : 0x75;
        s1 = func_002F8DB0(a);
    } else if (k == 0x2D) {
        id = 0x74;
        s1 = func_002F8DB0(a);
    } else if (k == 0x2C) {
        id = 0x73;
        s1 = func_002F8DB0(a);
    } else if (k == 0x2B) {
        id = 0x72;
        s1 = func_002F8DB0(a);
    } else if (k >= 0x24 && k <= 0x27) {
        id = 0x6E + (k - 0x24);
        func_00120928(t1, func_002F2890(a));
        func_00120928(t2, func_002F2890(b));
        s1 = t1;
        s2 = t2;
    } else if (k == 0x23) {
        id = 0x6D;
        s1 = func_002F2890(a);
    } else if (k == 0x22) {
        id = 0x6C;
        s1 = func_002F2890(a);
        s2 = func_0030ABF0(func_002F5CC0(a));
    } else if (k == 0x20 || k == 0x1F) {
        id = 0x6B;
        s1 = func_002F2890(a);
        s2 = func_0030ABF0(func_002F5CC0(a));
    } else if (k == 0x16) {
        id = 0x6A;
        s1 = func_002F2890(a);
    } else if (k == 0x15) {
        id = 0x69;
        s1 = func_002F2890(a);
    } else if (k == 0x14) {
        id = 0x68;
        s1 = func_002F2890(a);
    } else if (k == 0x12) {
        id = 0x67;
        func_002CAD90(h);
        s1 = (char *)func_0019FBC0(h[a]) + 0x13;
    } else if (k == 0xF) {
        id = 0x66;
        s1 = func_0030ABF0(a);
    } else if (k == 0xE) {
        id = 0x65;
        s1 = func_0030ABF0(a);
    } else if (k == 4) {
        id = 100;
        s1 = func_0030ABF0(a);
    } else if (k == 3) {
        s1 = func_0030ABF0(a);
        id = 99;
    }
    if (id == -1) {
        func_00120928(out, func_00372580(k));
    } else {
        if (s2 == 0)
            s2 = g_00448008;
        if (s1 == 0)
            s1 = g_00448008;
        func_001204B0(out, func_00372580(id), s1, s2);
    }
}
