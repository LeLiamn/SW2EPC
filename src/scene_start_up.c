/*
 * scene_start_up.c - scene 0x13, the start of an Empire game (original source file
 * StateStartUp.c: its name is referenced at 0x00365530). Only the scene's own part
 * (0x00368980-0x00369560) is decompiled so far; the phase handlers 0x003654A0-0x00368980 are
 * not.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The scene runs in phases (g_007B7070, 0-10): 0-3 the first set-up screens (func_00366740,
 * func_00366B10, func_00366D70, func_003673E0), 4 and 5 the choice of the officers of seven
 * slots (slot 0 = none chosen; the help line offers Remove on a slot holding an officer), 6
 * func_003672D0, 7 the save / start check, 8 waits for the fade-out, 9 and 10 leave the scene
 * (9 falls back to scene 0x11 when nothing was requested). An officer is 0-0x19E (0x19F =
 * none); each one has an "in use" byte.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The scene manager (0x0045D880, see main.c): one object, reached through lui / %lo. */
extern struct {
    float update_arg;
    u32 result;
    int quit, skip_update_test;
    int force_draw;          /* 0x0045D890 */
    int previous;            /* 0x0045D894 */
    int current;             /* 0x0045D898 */
    int return_to;           /* 0x0045D89C state to return to */
    int requested;           /* 0x0045D8A0 requested state (0x18 = none) */
} g_0045D880;
#define g_0045D890 (g_0045D880.force_draw)
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

#define GO_TO_NEXT_SCENE() do {                                         \
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {            \
            g_0045D894 = g_0045D898;                                    \
            g_0045D898 = g_0045D8A0;                                    \
            g_0045D89C = 0x18;                                          \
        } else {                                                        \
            g_0045D894 = g_0045D898;                                    \
            g_0045D898 = g_0045D89C;                                    \
            g_0045D89C = g_0045D8A0;                                    \
        }                                                               \
    } while (0)

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the byte used here. */
extern struct {
    u8 unknown_0[0x457E];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* The phase of the scene (0x007B7070, 0-10), not reached through $gp. */
extern struct {
    int g_007B7070;
} s_007B7070;
#define g_007B7070 (s_007B7070.g_007B7070)

/* Settings shown at the start (0x007B70E0), the bytes used here. */
extern struct {
    u8 unknown_0[0x17];
    u8 g_007B70F7;           /* the next three are "off" flags (passed as 0 == flag) */
    u8 g_007B70F8;
    u8 g_007B70F9;
    u8 g_007B70FA;
    u8 g_007B70FB;
    u8 g_007B70FC;
} s_007B70E0;
#define g_007B70F7 (s_007B70E0.g_007B70F7)
#define g_007B70F8 (s_007B70E0.g_007B70F8)
#define g_007B70F9 (s_007B70E0.g_007B70F9)
#define g_007B70FA (s_007B70E0.g_007B70FA)
#define g_007B70FB (s_007B70E0.g_007B70FB)
#define g_007B70FC (s_007B70E0.g_007B70FC)

/* The start-up state (0x007B7104). */
extern struct {
    u8 g_007B7104;           /* slot (0 = none, 1-6) */
    u8 unknown_1;
    u8 g_007B7106;           /* 0 choosing, 1 the officer list is open */
    u8 g_007B7107[0x19F];    /* per officer: in use */
    u8 unknown_1A2[0x1BA0 - 0x1A2];
    int g_007B8CA4;          /* officers in use */
    int g_007B8CA8;          /* ... of them, 0x1C-0x18F */
    int g_007B8CAC[25];      /* per entry of func_00374E00 */
    int g_007B8D10;
    int g_007B8D14[0x19F];   /* officers set free (see func_00368980) */
    int g_007B9390;          /* ... their count */
    int unknown_2290[7];
    int g_007B93B0[7];       /* per slot: the officer (0x19F = none) */
} s_007B7104;
#define g_007B7104 (s_007B7104.g_007B7104)
#define g_007B7106 (s_007B7104.g_007B7106)
#define g_007B8CAC (s_007B7104.g_007B8CAC)
#define g_007B8D10 (s_007B7104.g_007B8D10)
#define g_007B8D14 (s_007B7104.g_007B8D14)
#define g_007B9390 (s_007B7104.g_007B9390)
#define g_007B93B0 (s_007B7104.g_007B93B0)

#define SLOT_VALID(s) ((s) > 0 && (s) < 7)

extern int g_0045D774;                    /* (small data) passed to the officer list */
/* Help lines (part of the text table at 0x0043C32C, see scene_config.c; 0xF0 + letter = a
 * button icon). */
extern struct {
    const char *g_0043C638;    /* "Select  Back  OK" */
    const char *unknown_63C[0x28];
    const char *g_0043C6DC;    /* "Remove  Select  Back  OK" */
    const char *unknown_6E0[0x14];
    const char *g_0043C730;    /* "Select  Back  OK" */
    const char *unknown_734[0x22];
    const char *g_0043C7BC;    /* "Select  OK" */
    const char *unknown_7C0[0x16];
    const char *g_0043C818;    /* "Select  Info  Edit  Delete  Details  Back  OK" */
    const char *g_0043C81C;    /* "Select  Info  Delete  Details  Back  OK" */
    const char *g_0043C820;    /* "Select  Info  Edit  Details  Back  OK" */
    const char *g_0043C824;    /* "Select  Info  Details  Back  OK" */
} s_0043C638;
#define g_0043C638 (s_0043C638.g_0043C638)
#define g_0043C6DC (s_0043C638.g_0043C6DC)
#define g_0043C730 (s_0043C638.g_0043C730)
#define g_0043C7BC (s_0043C638.g_0043C7BC)
#define g_0043C818 (s_0043C638.g_0043C818)
#define g_0043C81C (s_0043C638.g_0043C81C)
#define g_0043C820 (s_0043C638.g_0043C820)
#define g_0043C824 (s_0043C638.g_0043C824)

void func_003A8DC0(void);
int func_0032D9C0(void);
int func_002F3E70(void);
int func_0032E760(void);
void func_00367B10(int officer, int in_use);
void func_00367CF0(void);
int func_00327C40(void);
void func_00327C10(u8 value);
void func_00327880(int on);
void func_003278D0(int on);
void func_00327920(int on);
void func_00327970(u8 value);
void func_003279D0(u8 value);
void func_00327A30(int on);
int func_00375BF0(void);
int func_00375B90(void);
int func_00375C10(void);
int func_00374E00(void);
int func_0030AFF0(int entry);
void func_00327CF0(int value);
int func_002F8F20(int value);
void func_00327780(int value);
int func_00372230(void);
void func_0017DF10(void);
void func_001B8F60(int a, int b, int c);
int func_003F1160(int a);
int func_0030AB90(void);
int func_003A1A80(void);
int func_0030C9C0(int entry);
void func_001A7DC0(const char *text, int alpha, int a);
int *func_00365450(void);
void func_003F8BB0(void);
void func_003752D0(void);
void func_00278CF0(void);
void func_003F4F40(void);
void func_003F11D0(void);
void func_00375F90(void);
void func_00384E60(int a);
void func_00387A10(int a, int b, int c);
void func_00366670(void);
void func_00366AC0(void);
void func_003A7360(void);
void func_00373B60(void);
int func_00374E10(void);
void func_003852A0(void);
int func_003725A0(int a);
void func_003838B0(int a, int b);
void func_003673B0(void);
void func_003876C0(int list, int *officers, int a, int b, int c, int d, int slot, int any);
void func_0032D3C0(int list);
void func_00367270(void);
void func_00375B00(void);
void func_00376450(void);
int func_003F5410(void);
int func_003F13E0(void);
void func_00366740(void);
void func_00366B10(void);
void func_00366D70(void);
void func_003673E0(void);
void func_003672D0(void);
int func_0017DDA0(void);
void func_00366600(void);
void func_002789C0(void);
void func_002787E0(void);
void func_003A5E20(void);
void func_003655F0(void);
void func_00390780(void);
void func_003F54C0(void);
void func_003F8B80(void);
void func_003F8B30(int a);
void func_003F1580(void);
void func_003F5430(void);
void func_003907B0(void);
void func_00365530(void);
void func_001A2040(void);
void func_001A1AC0(void);
void func_00374E20(void);
void func_003273E0(void);
void func_003EA010(void);
void func_0019FC30(void);
void func_00375D30(int list);
void func_00376100(int a, int b, int c);
void func_0017E010(int a);
void func_003F4D60(int a);

/* 0x00368980, 0x150 bytes. Phases 4 and 5: the officer of the current slot. With the list open,
 * a choice (func_0032D9C0 1) frees the slot's previous officer (kept in g_007B8D14 unless
 * func_002F3E70), marks the new one in use and closes the list; 0 only closes it. */
void func_00368980(void)
{
    func_003A8DC0();
    if (g_007B7106 == 1) {
        int r = func_0032D9C0();

        if (r == 1) {
            int officer;

            if (SLOT_VALID(g_007B7104) && g_007B93B0[g_007B7104] < 0x19F && func_002F3E70() == 0)
                g_007B8D14[g_007B9390++] = g_007B93B0[g_007B7104];
            officer = func_0032E760();
            if (SLOT_VALID(g_007B7104))
                func_00367B10(g_007B93B0[g_007B7104], 1);
            g_007B93B0[g_007B7104] = officer;
            if (SLOT_VALID(g_007B7104))
                func_00367B10(officer, 0);
            g_007B7106 = 0;
        } else if (r == 0) {
            g_007B7106 = 0;
        }
    } else if (g_007B7106 == 0) {
        func_00367CF0();
    }
}

/* 0x00368AD0, 0x80 bytes. Applies the start-up settings. */
void func_00368AD0(void)
{
    func_00327C10(func_00327C40());
    func_00327880(g_007B70F7 == 0);
    func_003278D0(g_007B70F8 == 0);
    func_00327920(g_007B70F9 == 0);
    func_00327970(g_007B70FA);
    func_003279D0(g_007B70FB);
    func_00327A30(g_007B70FC == 0);
}

/* 0x00368B50, 0xAC bytes. Phase 7: when func_00375BF0 is 0, sets up the chosen entry and its
 * settings and goes on unless func_00372230; else waits for func_00375B90 to be 1. Going on
 * stops the music, fades out and moves to phase 8. */
void func_00368B50(void)
{
    if (func_00375BF0() == 0) {
        int entry = func_0030AFF0(func_00374E00());

        func_00327CF0(entry);
        func_00327780(func_002F8F20(entry));
        func_00368AD0();
        if (func_00372230() != 0)
            return;
    } else if (func_00375B90() != 1) {
        return;
    }
    func_0017DF10();
    func_001B8F60(0, 6, 8);
    g_007B7070 = 8;
}

/* 0x00368C00, 0xAC bytes. Phase 9: leaves the scene (to scene 0x11 when nothing was asked). */
void func_00368C00(void)
{
    if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
        g_0045D89C = 0x11;
    GO_TO_NEXT_SCENE();
}

/* 0x00368CB0, 0x1AC bytes. The help line of the entry list: OK only while func_00375C10 is 1,
 * Back without a valid entry; else Info / Details with Edit when func_003A1A80 and Delete unless
 * the entry is protected (g_007B8CAC set and func_0030C9C0). */
void func_00368CB0(void)
{
    int entry;

    if (func_003F1160(0) != 0)
        return;
    if (func_00375BF0() != 0 && func_00375C10() == 1) {
        func_001A7DC0(g_0043C7BC, 0x80, 1);
        return;
    }
    entry = func_0030AFF0(func_00374E00());
    if (!(entry >= 0 && entry < func_0030AB90())) {
        func_001A7DC0(g_0043C638, 0x80, 1);
    } else if (func_003A1A80() == 0) {
        if (g_007B8CAC[func_00374E00()] != 0 && func_0030C9C0(func_00374E00()) != 0)
            func_001A7DC0(g_0043C824, 0x80, 1);
        else
            func_001A7DC0(g_0043C81C, 0x80, 1);
    } else {
        if (g_007B8CAC[func_00374E00()] != 0 && func_0030C9C0(func_00374E00()) != 0)
            func_001A7DC0(g_0043C820, 0x80, 1);
        else
            func_001A7DC0(g_0043C818, 0x80, 1);
    }
}

/* 0x00368E60, 0x58 bytes, matching. The page of the slot's list: 0x11 for slot 0, 0x12 for 1-3, 0x13 for
 * 4-6, else -1. */
int func_00368E60(void)
{
    int page = -1;

    if (g_007B7104 == 0)
        page = 0x11;
    else if (g_007B7104 > 0 && g_007B7104 < 4)
        page = 0x12;
    else if (g_007B7104 >= 4 && g_007B7104 < 7)
        page = 0x13;
    return page;
}

/* 0x00368EC0, 0x358 bytes. Scene 0x13 draw. */
void func_00368EC0(void)
{
    int *pictures = func_00365450();

    func_003F8BB0();
    func_003752D0();
    func_00278CF0();
    func_003F4F40();
    func_003F11D0();
    func_00375F90();
    switch (g_007B7070) {
    case 0:
        func_00384E60(1);
        func_00387A10(pictures[pictures[0] + 6], 0, 0x80);
        func_00366670();
        break;
    case 1:
        func_00387A10(pictures[pictures[0] + 6], 0, 0x80);
        func_00366AC0();
        break;
    case 2:
        func_003A7360();
        func_00373B60();
        if (func_00374E10() == 0) {
            func_003852A0();
            if (func_003F1160(0) == 0)
                func_003838B0(func_003725A0(0x10), 1);
        }
        break;
    case 3:
        func_003673B0();
        break;
    case 4:
    case 5:
        func_003A7360();
        if (g_007B7106 == 0) {
            int any, page;

            if (g_007B93B0[0] == 0x19F && g_007B93B0[1] == 0x19F && g_007B93B0[2] == 0x19F &&
                g_007B93B0[3] == 0x19F)
                any = 0;
            else
                any = 1;
            func_003876C0(g_0045D774, g_007B93B0, 0x18, 0x52, 0, 1, g_007B7104, any);
            if (g_007B7070 == 5) {
                u8 slot = g_007B7104;
                int officer = g_007B93B0[slot];

                if (officer == func_002F8F20(func_0030AFF0(g_007B8D10)) || officer >= 0x19F ||
                    slot >= 7)
                    func_001A7DC0(g_0043C730, 0x80, 1);
                else
                    func_001A7DC0(g_0043C6DC, 0x80, 1);
            } else if (g_007B7070 == 4) {
                if (g_007B93B0[g_007B7104] < 0x19F && g_007B7104 < 7)
                    func_001A7DC0(g_0043C6DC, 0x80, 1);
                else
                    func_001A7DC0(g_0043C730, 0x80, 1);
            }
            page = func_00368E60();
            if (page >= 0)
                func_003838B0(func_003725A0(page), 1);
        } else if (g_007B7106 == 1) {
            func_0032D3C0(g_0045D774);
        }
        break;
    case 6:
        func_003A7360();
        func_00367270();
        break;
    case 7:
        func_003A7360();
        break;
    case 8:
        func_003A7360();
        break;
    }
    if (g_007B7070 == 1)
        func_003852A0();
}

/* 0x00369220, 0x8 bytes, matching. Scene 0x13 step: empty. */
void func_00369220(void)
{
}

/* 0x00369230, 0x218 bytes. Scene 0x13 update: nothing while message box 1 is open or
 * func_003F5410 / func_003F13E0 hold; else the phase's handler. */
int func_00369230(void)
{
    if (box1_open())
        return 1;
    func_00375B00();
    func_00376450();
    if (func_003F5410() != 0)
        return 1;
    if (func_003F13E0() != 0)
        return 1;
    switch (g_007B7070) {
    case 0:
        func_00366740();
        break;
    case 1:
        func_00366B10();
        break;
    case 2:
        func_00366D70();
        break;
    case 3:
        func_003673E0();
        break;
    case 4:
    case 5:
        func_00368980();
        break;
    case 6:
        func_003672D0();
        break;
    case 7:
        func_00368B50();
        break;
    case 8:
        if (func_0017DDA0() != 0)
            return 1;
        if (box1_open())
            return 1;
        g_007B7070 = 9;
        break;
    case 9:
        func_00368C00();
        break;
    case 10:
        g_0045D890 = 1;
        GO_TO_NEXT_SCENE();
        break;
    }
    return 1;
}

/* 0x00369450, 0x54 bytes, matching. Scene 0x13 leave. */
void func_00369450(void)
{
    func_00366600();
    func_002789C0();
    func_002787E0();
    func_003A5E20();
    func_003655F0();
    func_00390780();
    func_003F54C0();
    func_003F8B80();
}

/* 0x003694B0, 0xAC bytes, matching. Scene 0x13 enter: sets everything up, starts music 0x31 and fades
 * in. */
void func_003694B0(void)
{
    func_003F8B30(0);
    func_003F1580();
    func_003F5430();
    func_003907B0();
    func_00365530();
    func_001A2040();
    func_001A1AC0();
    func_00374E20();
    func_00366600();
    func_003273E0();
    func_003EA010();
    func_0019FC30();
    func_00375D30(g_0045D774);
    func_00376100(0, -1, -1);
    func_0017E010(0x31);
    func_001B8F60(1, 6, 8);
    func_003F4D60(0x12);
}
