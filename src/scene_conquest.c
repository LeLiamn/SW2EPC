/*
 * scene_conquest.c - scene 0x12, the Empire mode's conquest map (original source file
 * StateConquest.c: its background is loaded with that file name).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The scene is the frame of the Empire turn: an animated background (LINKDATA entry 4, one frame
 * every other frame), the map and the menus of other files. The current Empire screen is
 * g_007B4E4C (0-0x1F); the update runs that screen's handler and the draw its drawer. Screen 0x1F
 * starts a battle (scene 9). The scene can also be the base for the season animation (0x16).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The scene manager (0x0045D880, see main.c): one object, reached through lui / %lo. */
extern struct {
    float update_arg;
    u32 result;
    int quit, skip_update_test, force_draw;
    int previous;            /* 0x0045D894 */
    int current;             /* 0x0045D898 */
    int return_to;           /* 0x0045D89C state to return to */
    int requested;           /* 0x0045D8A0 requested state (0x18 = none) */
} g_0045D880;
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

#define LEAVE_IF_NONE(scene) do {                                       \
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)                   \
            g_0045D89C = (scene);                                       \
    } while (0)
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

/* The game state (0x00669D60), the word used here (see scene_battle_initialize.c). */
extern struct {
    u8 unknown_0[0x20C];
    int g_00669F6C;          /* 1: a battle started from the Empire map */
} g_00669D60;
#define g_00669F6C (g_00669D60.g_00669F6C)

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the byte used here. */
extern struct {
    u8 unknown_0[0x457E];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* The Empire turn's state (0x007B4E48). */
extern struct {
    int g_007B4E48;          /* 2: leaving */
    int g_007B4E4C;          /* current Empire screen (0-0x1F) */
    int g_007B4E50;          /* scene to leave for (0x12 = this one) */
} s_007B4E48;
#define g_007B4E48 (s_007B4E48.g_007B4E48)
#define g_007B4E4C (s_007B4E48.g_007B4E4C)
#define g_007B4E50 (s_007B4E48.g_007B4E50)

/* (scratchpad) screen scale divisor? */
#define g_70000154 (*(int *)0x70000154)
extern const char g_00446350[];           /* "StateConquest.c" */
extern const char *g_0043C5EC;            /* a button help line */
extern u16 g_004463E0[];                  /* 2000, 2400 ... 8000 (gold per level?) */

/* Small data ($gp). */
extern u8 *g_0045D67C;                    /* the background (LINKDATA entry 4) */
extern u8 *g_0045D680;                    /* its animation player */
extern int g_0045D684;                    /* frame shown */

void func_00101400(int value);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
int func_00102960(int value);
void func_00102EC0(void *data);
u8 *func_00102DB0(int size, int align);
void func_00143DA0(u8 *player, u8 *data, int vram);
void func_00143D60(u8 *player);
u32 func_001020C0(void);                  /* frame counter */
void func_00143CC0(u8 *player, int frame);
u32 func_00106CD0(int vram, int a, int b, int c, u16 w, u16 h);
u8 *func_00105860(u32 texture, int a);
void func_001059B0(u8 *packet);
void func_003F8BB0(void);
int func_0032F780(void);
u8 *func_003B5E90(void);
void func_003A7360(void);
int func_0030E1F0(void);
void func_00375F90(void);
void func_0039F880(void);
void func_003752D0(void);
int func_0030E4D0(void);
int func_0038C7C0(void);
void func_003F4F40(void);
void func_003F11D0(void);
void func_003B7160(void);
void func_003270B0(void);
void func_00326390(void);
int func_003296F0(void);
void func_002FC9A0(void);
void func_003EB0E0(void);
void func_003085F0(void);
void func_002FC6F0(void);
void func_003071D0(void);
void func_00323680(void);
void func_0038C800(void);
void func_001A7DC0(const char *text, int alpha, int b);
void func_0030EDC0(void);
void func_0030E210(void);
int func_003A8DC0(void);
void func_00376450(void);
int func_0017DDA0(void);
void func_0030E240(void);
void func_00375B00(void);
void func_003DB860(void);
void func_003DC110(void);
void func_003135B0(void);
void func_0038C910(void);
int func_003F5410(void);
int func_003F13E0(void);
int func_003F11C0(void);
int func_00323730(int value);
void func_003F1070(int value);
int func_003235A0(void);
void func_003C3360(void);
int func_00331250(int value);
int func_00331AE0(void);
void func_0030E090(void);
int func_00331E70(void);
int func_00332610(void);
int func_00332EC0(void);
int func_00333190(void);
int func_00333650(void);
int func_00333A40(void);
int func_00334000(void);
int func_00307120(void);
int func_003138D0(void);
void func_00327DF0(int value);
void func_00329880(int value);
int func_002FC860(void);
int func_003236A0(void);
int func_00308500(void);
int func_00330440(int value);
int func_00313A90(void);
void func_003630C0(void);
int func_002FCB50(void);
int func_003EB120(void);
int func_0030DD70(void);
int func_0030D3F0(void);
void func_0030CC20(int value);
int func_0030D370(void);
int func_003261C0(void);
int func_003EAD10(void);
void func_003BAD20(void);
int func_00326E30(void);
int func_003B7350(void);
void func_003DD970(void);
void func_0030DDB0(void);
void func_0032E800(void);
void func_0032F530(void);
void func_0032F640(void);
void func_003F54C0(void);
void func_003B6E80(void);
void func_0030DC10(int value);
void func_003F8B80(void);
int func_0030DFA0(void);
int func_003C1850(void);
int func_00329540(int value);
int func_0036B260(void);
void func_003F8B30(int value);
void func_0030DB30(int value);
void func_0030DD10(int value);
void func_003F1580(void);
void func_003F5430(void);
void func_0032F670(void);
void func_0032F5A0(void);
void func_0032E7C0(void);
void func_002C59F0(void);
void func_002C5A30(void);
void func_002C5A60(void);
void func_0032FEB0(void);
void func_003137C0(void);
u8 *func_0030CCB0(void);

/* 0x002F1950, 0x5C bytes, matching. Loads the background (LINKDATA entry 4) if needed. */
void func_002F1950(void)
{
    if (g_0045D67C == 0) {
        func_00101400(0);
        g_0045D67C = func_001026D0(1, 4, 0, 1, 0, 0, g_00446350, 0x32);
        func_00102960(0);
    }
}

/* 0x002F19B0, 0x2C bytes, matching. Frees the background. */
void func_002F19B0(void)
{
    if (g_0045D67C != 0) {
        func_00102EC0(g_0045D67C);
        g_0045D67C = 0;
    }
}

/* 0x002F19E0, 0x40 bytes, matching. Starts the background's animation player. */
void func_002F19E0(void)
{
    func_00102960(1);
    g_0045D680 = func_00102DB0(0x40, 0x24);
    func_00143DA0(g_0045D680, g_0045D67C, 0x1D00);
    g_0045D684 = 0;
}

/* 0x002F1A20, 0x28 bytes, matching. Stops the background's animation player. */
void func_002F1A20(void)
{
    func_00143D60(g_0045D680);
    func_00102EC0(g_0045D680);
    g_0045D680 = 0;
}

/* 0x002F1A50, 0x14C bytes. Draws the background: the next frame every other frame, as one
 * sprite over the screen. */
void func_002F1A50(void)
{
    u8 *anim = *(u8 **)(g_0045D680 + 8);   /* +8 width, +0xA height, +0xC frames */
    u8 *packet;

    if ((func_001020C0() & 1) == 0)
        g_0045D684 = (g_0045D684 + 1) % *(int *)(anim + 0xC);
    func_00143CC0(g_0045D680, g_0045D684);
    packet = func_00105860(func_00106CD0(0x1D00, 0, 0, 0, *(u16 *)(anim + 8), *(u16 *)(anim + 0xA)), 0);
    *(u64 *)(packet + 0x30) = (u64)(-0xE00 / g_70000154 + 0x8000) << 16 | 0xFFFE00007000ULL;
    *(u64 *)(packet + 0x40) = (u64)(0x12A0 / g_70000154 + 0x8000) << 16 | 0xFFFE00009000ULL;
    *(u64 *)(packet + 0x20) = 0x3F80000080808080ULL;
    *(u64 *)(packet + 0x28) = 0x80008;
    *(u64 *)(packet + 0x38) = (u64)(int)((u32)*(u16 *)(anim + 8) << 4 | 8) | 0x0C080000;
    func_001059B0(packet);
    func_003F8BB0();
}

/* 0x002F1BA0, 0x6C bytes. Non-zero when the map is drawn: no officer chosen (func_0032F780 =
 * -1), and on screen 0x1E only while func_003B5E90's record is not busy. */
int func_002F1BA0(void)
{
    if (func_0032F780() != -1)
        return 0;
    if (g_007B4E4C == 0x1E)
        return *(int *)(func_003B5E90() + 4) == 0 ? 1 : 0;
    return 1;
}

/* 0x002F1C10, 0x1E4 bytes. Scene 0x12 draw: the background, the map, then whatever is on top:
 * the screen func_0030E1F0 / func_0030E4D0 / func_0038C7C0 opened, or the current Empire screen's
 * drawer. */
void func_002F1C10(void)
{
    func_002F1A50();
    func_003A7360();
    if (func_0030E1F0() != 0) {
        func_0030E210();
        return;
    }
    if (func_002F1BA0() != 0) {
        func_00375F90();
        func_0039F880();
    }
    func_003752D0();
    if (func_0030E4D0() != 0) {
        func_0030EDC0();
        return;
    }
    if (func_0038C7C0() != 0) {
        func_0038C800();
        func_001A7DC0(g_0043C5EC, 0x80, 2);
        return;
    }
    func_003F4F40();
    func_003F11D0();
    if (g_007B4E4C == 0x1E) {
        func_003B7160();
    } else if (g_007B4E4C == 0x1D) {
        func_003270B0();
    } else if (g_007B4E4C == 0x18) {
        func_00326390();
    } else if (g_007B4E4C != 0x17) {
        if (g_007B4E4C == 0x15) {
            if (func_003296F0() == 0x13)
                func_002FC9A0();
            else
                func_003EB0E0();
        } else if (g_007B4E4C == 0x12) {
            func_003085F0();
        } else if (g_007B4E4C == 0x10) {
            func_002FC6F0();
        } else if (g_007B4E4C == 0x0E) {
            func_003071D0();
        } else if (g_007B4E4C == 0) {
            func_00323680();
        }
    }
}

/* 0x002F1E00, 0x8 bytes, matching. Scene 0x12 step: empty (not found by Ghidra). */
void func_002F1E00(void)
{
}

/* 0x002F1E10, 0xC4 bytes. Leaves for g_007B4E50 when nothing else is requested. */
void func_002F1E10(void)
{
    g_0045D894 = g_0045D898;
    if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
        g_0045D89C = g_007B4E50;
    if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
        g_0045D898 = g_0045D8A0;
        g_0045D89C = 0x18;
    } else {
        g_0045D898 = g_0045D89C;
        g_0045D89C = g_0045D8A0;
    }
    g_007B4E50 = 0x12;
    g_007B4E48 = 0;
}

/* 0x002F1EE0, 0x638 bytes. Scene 0x12 update. Waits for func_003A8DC0; when leaving (phase 2)
 * waits for the music and box 1, then leaves. Otherwise runs, in order, the screens that may be
 * open on top (each returns 2 when done), then the current Empire screen's handler (0-0x1F);
 * screen 0x1F starts a battle (scene 9). Returns 0 while something above still runs. */
int func_002F1EE0(void)
{
    int result = 0;

    if (func_003A8DC0() == 0)
        return 1;
    func_00376450();
    if (g_007B4E48 == 2) {
        if (func_0017DDA0() == 0 && !box1_open())
            func_002F1E10();
        return 1;
    }
    if (func_0030E1F0() != 0) {
        func_0030E240();
        if (func_0030E1F0() != 2)
            return 0;
    }
    func_00375B00();
    func_003DB860();
    func_003DC110();
    if (func_0030E4D0() != 0) {
        func_003135B0();
        if (func_0030E4D0() != 2)
            return 0;
    }
    if (func_0038C7C0() != 0) {
        func_0038C910();
        if (func_0038C7C0() == 1)
            return 0;
    }
    if (func_003F5410() != 0)
        return 0;
    {
        int r = func_003F13E0();
        if (r != 0) {
            if (r != 2)
                return 0;
            if (g_007B4E4C != 0x0F) {
                if (func_003F11C0() == 4 && func_00323730(1) != 0)
                    func_003F1070(5);
                return 0;
            }
        }
    }
    switch (g_007B4E4C) {
    case 0:
        result = func_003235A0();
        func_003C3360();
        break;
    case 1:
        result = func_00331250(4);
        break;
    case 2:
        result = func_00331250(1);
        break;
    case 3:
        result = func_00331AE0();
        if (func_003296F0() != 0x13) {
            func_0030E090();
            return 1;
        }
        break;
    case 4:
        result = func_00331250(2);
        break;
    case 5:
        result = func_00331250(3);
        break;
    case 6:
        result = func_00331250(5);
        break;
    case 7:
        result = func_00331E70();
        break;
    case 8:
        result = func_00332610();
        break;
    case 9:
        result = func_00332EC0();
        break;
    case 10:
        result = func_00333190();
        break;
    case 11:
        result = func_00333650();
        break;
    case 12:
        result = func_00333A40();
        break;
    case 13:
        result = func_00334000();
        break;
    case 14:
        result = func_00307120();
        break;
    case 15:
        result = func_003138D0();
        break;
    case 16:
        func_00327DF0(0);
        func_00329880(0);
        result = func_002FC860();
        break;
    case 17:
        result = func_003236A0();
        break;
    case 18:
        result = func_00308500();
        break;
    case 19:
        if (func_003296F0() != 0x13)
            result = func_00330440(func_003296F0());
        break;
    case 20:
        result = func_00313A90();
        break;
    case 21:
        func_003630C0();
        if (func_003296F0() == 0x13) {
            func_00327DF0(1);
            result = func_002FCB50();
        } else {
            result = func_003EB120();
        }
        break;
    case 22:
        if (func_003296F0() == 0x13)
            result = func_00331250(7);
        break;
    case 23:
        func_00327DF0(2);
        result = func_0030DD70();
        if (result == 8 && func_0030D3F0() == 0)
            func_0030CC20(9);
        break;
    case 31:                                        /* a battle: scene 9 */
        func_003DD970();
        g_007B4E4C = 0x17;
        g_00669F6C = 1;
        LEAVE_IF_NONE(9);
        GO_TO_NEXT_SCENE();
        break;
    case 24:
        if (func_0030D370() != 0 && func_0030D3F0() == 0) {
            if (func_003296F0() == 0x13)
                result = func_003261C0();
            else
                result = func_003EAD10();
        }
        break;
    case 25:
        if (func_003296F0() == 0x13) {
            func_003BAD20();
            result = func_00331250(8);
        }
        break;
    case 26:
        if (func_003296F0() == 0x13)
            result = func_00331250(9);
        break;
    case 27:
        if (func_003296F0() == 0x13)
            result = func_00331250(10);
        break;
    case 28:
        if (func_003296F0() == 0x13)
            result = func_00331250(11);
        break;
    case 29:
        result = func_00326E30();
        break;
    case 30:
        result = func_003B7350();
        break;
    }
    if (result != 5)
        func_0030DDB0();
    return 1;
}

/* 0x002F2520, 0x5C bytes, matching. Scene 0x12 leave. */
void func_002F2520(void)
{
    func_0032E800();
    func_0032F530();
    func_0032F640();
    func_003F54C0();
    func_003B6E80();
    func_0030DC10(0);
    func_002F1A20();
    func_002F19B0();
    func_003F8B80();
}

/* 0x002F2580, 0x98 bytes, matching. Non-zero when entering the map should run func_003137C0: not in
 * state 6 with func_00329540 set, nor in state 0x0D with func_0036B260 set. */
int func_002F2580(void)
{
    if (func_0030DFA0() == 6) {
        if (func_003C1850() != 0) {
            if (func_00329540(0x14) != 0)
                return 0;
        } else {
            if (func_00329540(0x18) != 0)
                return 0;
        }
    }
    if (func_003296F0() == 0x0D && func_0036B260() != 0)
        return 0;
    return 1;
}

/* 0x002F2620, 0xB0 bytes, matching. Scene 0x12 enter. */
void func_002F2620(void)
{
    func_003F8B30(0);
    func_002F1950();
    func_002F19E0();
    func_0030DB30(0);
    func_0030DD10(0);
    func_003F1580();
    func_003F5430();
    func_0032F670();
    func_0032F5A0();
    func_0032E7C0();
    func_002C59F0();
    func_002C5A30();
    func_002C5A60();
    func_0032FEB0();
    if (g_007B4E4C != 0x1F && func_002F2580() != 0)
        func_003137C0();
}

/* 0x002F26D0, 0x18 bytes, matching. Entry `i` of the table 2000, 2400 ... 8000 at 0x004463E0. */
u16 func_002F26D0(int i)
{
    return g_004463E0[i];
}

/* 0x002F26F0, 0x2C bytes. */
void func_002F26F0(void)
{
    func_0030CCB0()[0xFD34] = 3;
}
