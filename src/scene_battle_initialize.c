/*
 * scene_battle_initialize.c - scenes 0x04, 0x06 and 0x07 (original source file
 * StateBattleInitialize.c: the battle intro's data is loaded with that file name). Scene 0x05,
 * the rest of the file, is not decompiled yet (only its on_reset 0x001D4150 is).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A battle goes 0x04 (set up the battle; through the loading screen 0x0F while data loads) ->
 * 0x07 (the intro: one camera path per army, Start skips it) -> 0x05 (the battle) -> 0x06 (tear
 * everything down, then on to scene 0x0A, the results, or 0x10 / 0x12). Scenes 0x04 and 0x06 do
 * all their work in their enter function.
 */

#define SW2E_FILE_SCENE_BATTLE_INITIALIZE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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
#define g_0045D890 (g_0045D880.force_draw)
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
/* The second half of a scene change, without setting `previous`. */
#define SWITCH_SCENE() do {                                             \
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {            \
            g_0045D898 = g_0045D8A0;                                    \
            g_0045D89C = 0x18;                                          \
        } else {                                                        \
            g_0045D898 = g_0045D89C;                                    \
            g_0045D89C = g_0045D8A0;                                    \
        }                                                               \
    } while (0)

/* The game state (0x00669D60), the fields used here. */
extern struct {
    u8 unknown_0[0x52];
    u8 g_00669DB2;           /* music volume */
    u8 unknown_53[0x5];
    int g_00669DB8;          /* game mode (see scene_initialize.c) */
    u8 unknown_5c[0x4];
    int g_00669DC0[5];       /* stage (per battle of a series in mode 2) */
    u8 unknown_74[0x18C];
    u32 g_00669F60;          /* flags: bit 1 two armies, 4 demo, 20 battle intro, 21 battle on */
    u8 unknown_204[0x8];
    int g_00669F6C;
    int g_00669F70;          /* how the battle ended (7 = reset) */
    u8 unknown_214[0x24];
    int g_00669F98;          /* battle number in mode 2 */
    int g_00669F9C;          /* battle clock (frames, up to 180000) */
} g_00669D60;
#define g_00669DB2 (g_00669D60.g_00669DB2)
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669DC0 (g_00669D60.g_00669DC0)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)
#define g_00669F70 (g_00669D60.g_00669F70)
#define g_00669F98 (g_00669D60.g_00669F98)
#define g_00669F9C (g_00669D60.g_00669F9C)

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the byte used here. */
extern struct {
    u8 unknown_0[0x457E];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* Controllers 1 and 2 (see scene_shop.c). */
extern u8 g_00500764, g_00500765, g_005007EC, g_005007ED;
extern unsigned short g_0050074C, g_005007D4;
#define pad1_pressed() ((unsigned short)(((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0) ? g_0050074C : 0))
#define pad2_pressed() ((unsigned short)(((g_005007EC & 1) ? (g_005007ED & 1) == 1 : 0) ? g_005007D4 : 0))
#define BTN_START 0x800

/* Battle objects. */
extern struct {
    u32 g_0073C78C;          /* officer of the intro (0xB6 = none) */
    int g_0073C790;          /* second army's officer (0xB6 = one army) */
    u8 unknown_8[0x6];
    u8 g_0073C79A;           /* stage of the battle */
    u8 unknown_f[0x2];
    u8 g_0073C79D;           /* army being handled (0 or 1) */
    u8 unknown_12[0xA];
    void *g_0073C7A8;        /* intro data (LINKDATA 0xAD + officer type) */
    void *g_0073C7AC;        /* intro data (LINKDATA 0xC8 + officer type) */
} s_0073C78C;
#define g_0073C78C (s_0073C78C.g_0073C78C)
#define g_0073C790 (s_0073C78C.g_0073C790)
#define g_0073C79A (s_0073C78C.g_0073C79A)
#define g_0073C79D (s_0073C78C.g_0073C79D)
#define g_0073C7A8 (s_0073C78C.g_0073C7A8)
#define g_0073C7AC (s_0073C78C.g_0073C7AC)
extern u32 g_0073C460[][4];               /* 16-byte record per army (func_00190C00) */
extern u8 g_0073D4EC[6];                  /* model of the intro officer, then of five others */

/* The intro cameras (0x00730480, 0x60 bytes per army) and their shot lists (0x00730A44, 0x174
 * bytes per army). */
typedef struct {
    u32 flags;               /* bit 1: Start cannot skip */
    u8 unknown_4[0x3C];
    float position;          /* +0x40 */
    float unknown_44;
    float end;               /* +0x48 */
    u32 shot;                /* +0x4C */
    u8 unknown_50[0x10];
} IntroCamera;
extern IntroCamera g_00730480[2];
typedef struct {
    u32 shots[16];
    int next;                /* +0x40 */
    u8 unknown_44[0x130];
} IntroShots;
extern IntroShots g_00730A44[2];

/* Player units (0x005B4BC0, 0x240 bytes each) and what they are built from. */
extern u8 g_005B4BC0[2][0x240];
extern u8 g_005B49E0[2][0xF0];
extern u8 g_00574DE0[2][0x630];
extern u8 *g_0045D2C0;                    /* the first player unit */
extern u8 *g_005BA694;                    /* stage records, 100 bytes (+2: music?) */
extern int g_0045D2A8;
extern int g_0072CC44, g_0072CC48;
extern const char g_00428EA0[];           /* "StateBattleInitialize.c" */

/* Scene 0x07 state, small data ($gp). */
extern int g_0045D3B0;                    /* Start pressed: skipping the intro */
extern int g_0045D3B4, g_0045D3B8;
extern float g_0045D3BC, g_0045D3C0;     /* sequence timers (frames) */
extern int g_0045D3E0;                    /* army being handled (as g_0073C79D) */

void func_00213F90(void);
void func_00185210(void);
void func_001C7CE0(void);
void func_0022EF00(void);
void func_002E6390(void);
void func_0017DF10(void);
void func_001023B0(int value);
void func_001D2CD0(void);
void func_001D2B60(void);
void func_0017AA80(u8 *unit, int player);
void func_0017AC50(u8 *unit);
void func_001DB8E0(void);
void func_0022E280(void);
void func_00216DF0(void);
void func_001D22F0(void);
void func_002D6FB0(void);
void func_0032F8A0(void);
void func_0027F800(void);
void func_00218790(int a, int b);
void func_00218C40(int a, int b);
int func_0017DDA0(void);
void func_002171E0(void);
void func_0017E0C0(int volume, int b);
void func_001D47C0(void);
void func_001D6B40(void);

/* ---- Scene 0x06: after a battle --------------------------------------------------------------- */

/* 0x001D1E80, 0xAC bytes, matching. Frees the battle's systems. */
void func_001D1E80(void)
{
    func_00102990();
    func_00102960(1);
    func_00213F90();
    func_00185160();
    func_00185210();
    func_00279B20();
    func_00178460();
    func_00193FB0();
    func_0018C730();
    func_001C7CE0();
    func_00216D60();
    func_0022EF00();
    func_0020EC20();
    func_003600F0();
    func_0035ED90();
    func_003E3150();
    func_003E44D0();
    func_003E7260();
    func_001A9030();
}

/* 0x001D1F30, 0x31C bytes. Scene 0x06 enter: tears the battle down and goes on to the results
 * (scene 0x0A); when func_0032E7B0 says so (end of a series?), on again to 0x10 (after a reset in
 * the battle) or 0x12. */
void func_001D1F30(void)
{
    int over = func_0032E7B0();
    int from_reset = g_0045D898 == 0x10;

    func_001020E0();
    func_001020E0();
    func_001020E0();
    func_001D1E80();
    func_0023BFA0();
    func_001B8BF0();
    func_002E5D20();
    func_00213F90();
    func_001FB660();
    func_00178460();
    func_00216D60();
    func_0022EF00();
    func_002E6390();
    g_0045D894 = g_0045D898;
    LEAVE_IF_NONE(0x0A);
    SWITCH_SCENE();
    func_001DB9F0();
    func_001D97B0();
    if (g_0073C7A8 != 0) {
        func_00102EC0(g_0073C7A8);
        g_0073C7A8 = 0;
    }
    if (g_0073C7AC != 0) {
        func_00102EC0(g_0073C7AC);
        g_0073C7AC = 0;
    }
    if (over != 0) {
        func_0017DF10();
        func_0032FF30();
        func_0032E7A0(0);
        if (from_reset) {
            LEAVE_IF_NONE(0x10);
            g_0045D894 = g_0045D898;
            SWITCH_SCENE();
        } else {
            LEAVE_IF_NONE(0x12);
            g_0045D894 = g_0045D898;
            SWITCH_SCENE();
        }
    }
    func_001023B0(0);
}

/* 0x001D2250, 0x8 bytes, matching. Scene 0x06 leave: empty (not found by Ghidra). */
void func_001D2250(void)
{
}

/* 0x001D4150, 0x44 bytes, matching. Scene 0x05 on_reset: the battle ends as "reset" (7, outside a demo),
 * then scene 0x06's tear-down. */
void func_001D4150(void)
{
    if ((g_00669F60 & 0x10) == 0)
        g_00669F70 = 7;
    func_001D2CD0();
    func_001D1F30();
}

/* ---- Scene 0x04: setting up a battle ---------------------------------------------------------- */

/* 0x001D41A0, 0x140 bytes. Builds the player units (two with two armies) and points
 * g_0045D2C0 at the first. */
void func_001D41A0(void)
{
    if ((g_00669F60 & 2) == 0) {
        func_0017A920(g_005B4BC0[0]);
        func_00161E10((int *)(g_005B49E0[0]), g_00574DE0[0], g_005B4BC0[0]);
        g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
        func_0017AC50(g_005B4BC0[0]);
    } else {
        func_0017AA80(g_005B4BC0[0], 0);
        func_00161E10((int *)(g_005B49E0[0]), g_00574DE0[0], g_005B4BC0[0]);
        g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
        func_0017AC50(g_005B4BC0[0]);
        func_0017AA80(g_005B4BC0[1], 1);
        func_00161E10((int *)(g_005B49E0[1]), g_00574DE0[1], g_005B4BC0[1]);
        g_005B4BC0[1][0x230] = (g_005B4BC0[1][0x230] & 0xFE) | 1;
        func_0017AC50(g_005B4BC0[1]);
    }
    g_0045D2C0 = g_005B4BC0[0];
}

/* The stage record of the battle (mode 2 and 3 use fixed records 0x54 / 0x55). */
static int battle_stage_record(void)
{
    if (g_00669DB8 == 2)
        return 0x54;
    if (g_00669DB8 == 3)
        return 0x55;
    return g_00669DC0[0];
}

/* 0x001D4490, 0x318 bytes. Scene 0x04 enter. While data is still loading, goes to the loading
 * screen (0x0F) and comes back here. Then closes the loading screen and sets the battle up;
 * without an intro (func_0032E7B0 = 0) goes straight to the battle (0x05), else to
 * func_001D47C0 (the intro, scene 0x07). */
void func_001D4490(void)
{
    int current = g_0045D898;

    if (func_00102960(0) == 0) {
        g_0045D8A0 = current;
        g_0045D894 = current;
        g_0045D898 = 0x0F;
        g_0045D89C = current;
        return;
    }
    func_002F1660();
    func_00102960(1);
    func_00101470(1);
    func_0036E170();
    func_003F8260();
    func_00360090();
    if (g_00669F6C != 1)
        func_003E4480();
    func_001DB8E0();
    if (func_0032E7B0() == 0) {
        int loaded;

        func_001C7B80();
        func_00193FF0();
        func_00279A10();
        func_0022E280();
        func_00185300();
        func_001D41A0();
        func_001FB440();
        func_0023BFF0();
        func_002E5C80(*(u16 *)(g_005BA694 + battle_stage_record() * 100 + 2));
        func_0024BF20();
        func_00216DF0();
        func_0027A010();
        func_0036D170();
        if (g_00669F6C == 1)
            func_0036D150(1);
        loaded = g_00669F6C;
        g_0045D894 = g_0045D898;
        g_00669F6C = 0;
        LEAVE_IF_NONE(5);
        SWITCH_SCENE();
        func_001D22F0();
        g_0045D2A8 = 0;
        if (loaded == 0)
            func_002D6FB0();
        func_001B8F60(1, 6, 8);
    } else {
        func_001D47C0();
    }
}

/* 0x001D47B0, 0x8 bytes, matching. Scene 0x04 leave: empty (not found by Ghidra). */
void func_001D47B0(void)
{
}

/* 0x001D47C0, 0x42C bytes. Sets the battle up with an intro: loads the intro data for the
 * officer's type (LINKDATA 0xAD + type and 0xC8 + type), the models of the officers shown, and
 * goes to scene 0x07 (keeping the draw on, flag 20 of g_00669F60). */
void func_001D47C0(void)
{
    u32 model = func_002F27D0(func_0032EEB0());
    u32 record[4];
    int i, current;

    func_001C7B80();
    func_00193FF0();
    func_00279A10();
    func_0022E280();
    func_00185300();
    func_001D41A0();
    func_001FB440();
    func_0023BFF0();
    func_002E5C80(*(u16 *)(g_005BA694 + battle_stage_record() * 100 + 2));
    func_0024BF20();
    func_00216DF0();
    func_0027A010();
    g_0045D894 = g_0045D898;
    g_00669F6C = 0;
    LEAVE_IF_NONE(5);
    SWITCH_SCENE();
    func_001D22F0();
    g_0045D2A8 = 0;
    if (g_00669DB8 == 2)
        g_0073C79A = (u8)g_00669DC0[g_00669F98 % 5];
    else
        g_0073C79A = (u8)g_00669DC0[0];
    g_0073C7A8 = func_001026D0(1, func_0032F780() + 0xAD, 0, 1, 0, 0, g_00428EA0, 0x231);
    g_0073C7AC = func_001026D0(1, func_0032F780() + 200, 0, 1, 0, 0, g_00428EA0, 0x233);
    func_001D96E0();
    g_0073C78C = func_0032F780();
    func_00190C00(record, 0);
    g_0073C460[g_0073C79D][0] = record[0];
    g_0073C460[g_0073C79D][1] = record[1];
    g_0073C460[g_0073C79D][2] = record[2];
    g_0073C460[g_0073C79D][3] = record[3];
    g_0073D4EC[0] = func_0020E310(model);
    for (i = 0; i < 5; i++) {
        u32 officer = func_0032E8E0(i);
        if (officer < 0x19F)
            g_0073D4EC[1 + i] = func_0020E310(func_002F27D0(officer));
    }
    current = g_0045D898;
    g_0072CC44 = 0;
    g_0072CC48 = 0;
    g_0045D890 = 1;
    LEAVE_IF_NONE(5);
    SWITCH_SCENE();
    g_0045D894 = current;
    g_00669F60 |= 0x100000;
    func_0032F8A0();
    func_001B8F60(1, 6, 8);
}

/* ---- Scene 0x07: the battle intro ------------------------------------------------------------- */

/* Takes the next shot of `army`'s list. */
#define NEXT_SHOT(army) (g_00730A44[army].shots[g_00730A44[army].next++])

/* 0x001D5F00, 0x220 bytes. Scene 0x07 enter: starts the intro cameras (one per army). With a
 * movie (func_0020E140 / func_0020E170) the cameras start in movie mode. */
void func_001D5F00(void)
{
    func_0023B3C0(0, 1);
    g_0045D3B0 = 0;
    func_0027F800();
    func_001C8870(1);
    func_0020EC70();
    if (func_0020E140() == 0 && func_0020E170() == 0) {
        func_001020E0();
        func_001B8F60(1, 6, 0x20);
        if (func_0020E1A0() == 0)
            func_0017A640();
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D9280((unsigned char *)(&g_00730480[0]));
        if (g_0073C790 == 0xB6) {
            if (func_00102960(0) == 0)
                func_00102960(1);
            g_00730480[g_0045D3E0].shot = NEXT_SHOT(g_0045D3E0);
            func_0023A2F0(0x1478, g_00730480[g_0045D3E0].shot, 1);
            func_00102960(1);
        } else {
            g_0073C79D = 1;
            g_0045D3E0 = 1;
            func_001D9280((unsigned char *)(&g_00730480[1]));
        }
    } else {
        func_0023AA40();
        func_0023B320();
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D91F0((unsigned int *)(&g_00730480[0]), 1);
        if (g_0073C790 == 0xB6) {
            g_00730480[g_0045D3E0].shot = NEXT_SHOT(g_0045D3E0);
        } else {
            g_0073C79D = 1;
            g_0045D3E0 = 1;
            func_001D91F0((unsigned int *)(&g_00730480[1]), 0);
        }
    }
}

/* 0x001D6120, 0x144 bytes, matching. Scene 0x07 leave: stops the cameras and the intro's officers; after a
 * reset (scene 0x10 next) also tears the battle down. */
void func_001D6120(void)
{
    int two = g_0073C790 != 0xB6;

    func_0017DEA0(0);
    if (func_0020E140() != 0 || func_0020E170() != 0)
        func_001020E0();
    g_0073C79D = 0;
    g_0045D3E0 = 0;
    func_001D92E0((unsigned char *)(&g_00730480[0]));
    if (two) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D92E0((unsigned char *)(&g_00730480[1]));
    }
    g_0073C78C = 0xB6;
    g_0073C790 = 0xB6;
    func_0020E570();
    g_0073C79D = 0;
    func_0017A640();
    func_0027F980();
    g_00669F60 &= ~0x100000u;
    func_00218790(0, 0);
    func_00218C40(0, 0);
    if (two) {
        func_00218790(1, 0);
        func_00218C40(1, 0);
    }
    func_002E5ED0();
    if (g_0045D898 == 0x10) {
        func_001D4150();
        func_001D2B60();
    }
}

/* 0x001D6270, 0x55C bytes. Scene 0x07 update: plays the cameras (at 1.2 times the frame time);
 * Start (either controller with two armies) skips, unless the camera forbids it; near the end of
 * the shot the screen fades. When the intro is over: on to the battle (0x05) with the battle flag
 * 21 set, or to scene 0x06. */
int func_001D6270(float dt)
{
    float step = dt * 1.2f;
    int playing;

    g_0073C79D = 0;
    g_0045D3E0 = 0;
    playing = func_001D93B0((unsigned int *)(&g_00730480[0]), &step);
    if (g_0073C790 != 0xB6) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        playing = func_001D93B0((unsigned int *)(&g_00730480[1]), &step);
    }
    if (g_0045D3B0 != 0 && !box1_open() && func_0017DDA0() == 0)
        playing = 0;
    func_002171E0();
    func_00193980(step);
    func_002E5DA0(step);
    if ((g_00730480[g_0045D3E0].flags & 2) == 0) {
        if ((pad1_pressed() & BTN_START) ||
            ((g_00669F60 & 2) != 0 && (pad2_pressed() & BTN_START))) {
            func_001B8F60(0, 6, 0x10);
            func_0017DEA0(0x14);
            g_0045D3B0 = 1;
        }
    }
    if (!box1_open() && g_00730480[g_0045D3E0].end - g_00730480[g_0045D3E0].position < 20.0f)
        func_001B8F60(0, 6, 0x10);
    if (playing == 0) {
        func_00102990();
        if (func_0032E7B0() == 0) {
            int movie = func_0020E1F0();

            g_0045D894 = g_0045D898;
            if (movie == 0) {
                LEAVE_IF_NONE(5);
                SWITCH_SCENE();
                g_00669F60 |= 0x200000;
                func_001B8F60(1, 6, 0x20);
                g_0069395E = 0x80;
                func_001020E0();
                func_00102960(1);
                func_001D6B40();
            } else {
                LEAVE_IF_NONE(6);
                SWITCH_SCENE();
                func_001B8F60(0, 6, 0xFF);
                func_0023AC40();
            }
        } else {
            func_0017DF10();
            func_0023AC40();
            g_0045D894 = g_0045D898;
            LEAVE_IF_NONE(6);
            SWITCH_SCENE();
            func_001B8F60(0, 6, 1);
            func_0023AC40();
            func_0017E0C0(g_00669DB2, 0x1E);
        }
    }
    return 1;
}

/* 0x001D67D0, 0x6C bytes, matching. Scene 0x07 step. */
void func_001D67D0(void)
{
    g_0073C79D = 0;
    g_0045D3E0 = 0;
    func_001D9350((unsigned char *)(&g_00730480[0]));
    if (g_0073C790 != 0xB6) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D9350((unsigned char *)(&g_00730480[1]));
    }
    func_00193940();
    func_0023C0D0();
}

/* 0x001D6840, 0x98 bytes. Scene 0x07 draw: one view, or two split views with two armies. */
void func_001D6840(void)
{
    if (g_0073C790 == 0xB6) {
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D9490((unsigned int *)(&g_00730480[0]), 0);
    } else {
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D9490((unsigned int *)(&g_00730480[0]), 1);
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D9490((unsigned int *)(&g_00730480[1]), 2);
    }
    func_0017A530();
    func_003E7430();
}

/* 0x001D6B40, 0x18 bytes, matching. Resets four battle counters. */
void func_001D6B40(void)
{
    g_0045D3C0 = 0.0f;
    g_0045D3BC = 0.0f;
    g_0045D3B4 = 1;
    g_0045D3B8 = 0;
}

/* ---- Scene 0x05: the battle ------------------------------------------------------------------- */

/* The battle scene's state (0x00730350). */
extern struct {
    u8 phase;                /* 0x00730350: see func_001D3890 */
    u8 unknown_1;
    short countdown;         /* 0x00730352: frames of the ending (250) */
    void *data;              /* 0x00730354 */
    u8 g_00730358;
    u8 started;              /* 0x00730359: the end-of-battle camera has started */
    u8 unknown_a;
    u8 g_0073035B;           /* 1 once the result jingle was started */
} s_00730350;
extern u32 g_00730398;
extern u8 g_00730360[0x30];               /* a camera passed to func_001C8620 */
extern u8 g_00730A20[], g_00730B94[];

/* Combo counters (small data): per player the hits (up to 9999) and the frames left (90). */
extern float g_0045D3A0[2];
extern u32 g_0045D3A8[2];
extern int g_0045D2A8;                    /* non-zero: slow motion (time x 0.25) */
extern u32 g_0045D2C4;                    /* most soldiers on screen? */
extern float g_0045CC7C;                  /* game speed */
extern int g_0045CC80;
extern int g_0045D470;                    /* player being handled (0 or 1) */
/* (scratchpad) non-zero: fewer soldiers */
#define g_70000174 (*(int *)PS2_PTR(0x70000174))
/* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))
/* (scratchpad) the camera's direction vector? */
#define g_700000C0 ((float *)PS2_PTR(0x700000C0))
extern u8 g_00428DC0[];                   /* soldiers per stage music? (indexed by the record) */

/* Players in battle (0x006A3A44, 0xC0 bytes each): +0 their unit, +0xA4 flags. */
typedef struct {
    u8 *unit;                /* +0x00 (its position vector at +0x40) */
    u8 unknown_4[0xA0];
    u32 flags;               /* +0xA4: 0x02 / 0x10 cannot move */
    u8 unknown_a8[0x18];
} BattlePlayer;
extern BattlePlayer g_006A3A44[2];

/* The player records of the game state (0x00669DA8 + 0x48 * i: +0x48 the officer, +0x90 combo,
 * +0x94 best combo, +0xCA controller port), read from the game state's base. */
#define PLAYER_REC(i) ((u8 *)&g_00669D60 + (i) * 0x48)

/* Battle units of the players (0x00574DE0, 0x630 bytes each). */
#define UNIT(i) g_00574DE0[i]

/* A group of soldiers (0x68 bytes, 0x47 of them at 0x006A1D58): up to 13 soldiers and 5 leaders,
 * pointers to 0x88-byte soldier records (0x00693970), saved as indices. */
typedef struct {
    u8 *members[13];         /* +0x00 */
    u8 *leaders[5];          /* +0x34 */
    int unknown_48;
    int strength;            /* +0x4C */
    int timer;               /* +0x50 */
    int unknown_54;
    float unknown_58, unknown_5c, unknown_60;
    u32 flags;               /* +0x64: 1 in use, 2 retreating?, 4 near a player, 8 timed */
} SoldierGroup;
extern SoldierGroup g_006A1D58[0x47];
extern u8 g_00693970[];                   /* soldier records, 0x88 bytes */
#define SOLDIER_INDEX(p) (((u8 *)(p) - g_00693970) / 0x88)

/* A message for the battle's event queue (func_0023EB40). */
typedef struct { u16 type, a, b; } BattleEvent;

/* Stand-ins for VU0 code (inline assembly in the original). */
static float xz_dist2(const float *a, const float *b)
{
    float dx = b[0] - a[0], dz = b[2] - a[2];
    return dx * dx + dz * dz;
}
static float dist2(const float *a, const float *b)
{
    float dx = b[0] - a[0], dy = b[1] - a[1], dz = b[2] - a[2];
    return dx * dx + dy * dy + dz * dz;
}
static void normalize3(float *out, const float *v)
{
    float l = __builtin_sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    out[0] = v[0] / l;
    out[1] = v[1] / l;
    out[2] = v[2] / l;
    out[3] = v[3] / l;
}

int func_0011B740(int value);              /* abs */
void func_0029E070(u32 a, float *vec);
u8 *func_00240CA0(u8 *unit);
int func_001BEA90(u8 kind);
int func_002E6510(float dt);
void func_002E6790(void);
void func_00177530(int player);
void func_001784E0(float dt);
void func_001D5DF0(int wait);
void func_0017E040(int cue);
int func_0017E0A0(void);
int func_001D6920(float dt, int *still);
void func_001D6A60(void);
int func_001D6B60(float dt);
void func_00178CC0(void);
void func_0022E5D0(void);
void func_002E65D0(void);
void func_0022ECD0(int value);
void func_00218E80(void);
void func_00179700(int player);
void func_00279140(int a, int b, int c, int d, int e, int f);
void func_00216B40(void);
void func_0022E150(void);
void func_001EC900(u8 *soldier, int a, int b);
void func_001EE3B0(u8 *soldier);
void func_001EE570(u8 *soldier);
void func_001EE9C0(void *object, int value);

/* 0x001D2260, 0x68 bytes. Adds `hits` to player `player`'s combo (up to 9999) and restarts its
 * 90-frame timer. */
void func_001D2260(int player, u32 hits)
{
    u32 count = g_0045D3A8[player] + hits;

    g_0045D3A8[player] = count;
    if (count >= 9999)
        count = 9999;
    g_0045D3A8[player] = count;
    count = g_0045D3A8[player];
    g_0045D3A0[player] = 90.0f;
    func_00362020(count, count - hits);
}

/* 0x001D22D0, 0x14 bytes, matching. Player `player`'s combo. */
u32 func_001D22D0(int player)
{
    return g_0045D3A8[player];
}

/* 0x001D22F0, 0x14 bytes, matching. Clears both combos. */
void func_001D22F0(void)
{
    g_0045D3A8[0] = 0;
    g_0045D3A0[0] = 0.0f;
    g_0045D3A8[1] = 0;
    g_0045D3A0[1] = 0.0f;
}

/* 0x001D2310, 0xA0 bytes. Counts the combo timers down (not in slow motion nor in the flagged
 * phases); an expired combo goes back to 0. */
void func_001D2310(float dt)
{
    int i;

    if (g_0045D2A8 != 0 || (g_00669F60 & 0x14280000) != 0)
        return;
    for (i = 0; i < 2; i++) {
        if (g_0045D3A0[i] > 0.0001f && (UNIT(i)[0x19C] & 2) == 0) {
            g_0045D3A0[i] -= dt;
            if (g_0045D3A0[i] <= 0.0001f) {
                g_0045D3A8[i] = 0;
                g_0045D3A0[i] = 0.0f;
            }
        }
    }
}

/* 0x001D23B0, 0x174 bytes. Sets g_0045D2C4 (most soldiers on screen?): 20 in one special mode,
 * 30 with two armies, else from the stage (table 0x00428DC0), 5 fewer in two flagged cases, 75 %
 * on a slower machine set-up (g_70000174), at most 51. */
void func_001D23B0(void)
{
    if (func_001F2450() != 0) {
        g_0045D2C4 = 0x14;
    } else if ((g_00669F60 & 2) != 0) {
        g_0045D2C4 = 0x1E;
    } else {
        u16 kind = *(u16 *)(g_005BA694 + battle_stage_record() * 100 + 2);

        if (kind < 0xBA) {
            u32 n = g_00428DC0[kind];
            if ((g_00669F60 & 0x400000) != 0)
                n -= 5;
            if (g_0045D2A8 != 0)
                n -= 5;
            if (g_70000174 != 0)
                n = n * 0x4B / 100;
            if (n < 0x34)
                g_0045D2C4 = n;
        } else {
            g_0045D2C4 = 0x33;
        }
    }
}

/* Controller `port`'s analog byte at +`offset` (0x80, the centre, when not connected). */
#define PAD_READY_N(port) ((g_00500700_bytes[(port) * 0x88 + 0x64] & 1) ? \
                           (g_00500700_bytes[(port) * 0x88 + 0x65] & 1) == 1 : 0)
extern u8 g_00500700_bytes[];             /* the controllers (0x88 bytes each) */

/* 0x001D2530, 0x3B0 bytes. Moves the players' camera with the right stick (beyond a dead zone of
 * 64, inverted unless the controller is in analog mode, the vertical move quartered when the
 * unit's state forbids it), then updates the camera (func_00164440). */
void func_001D2530(float dt)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (g_005B4BC0[i][0x230] & 1) {
            u32 flags = g_006A3A44[i].flags;

            if ((flags & 0x10) == 0 && (flags & 2) == 0) {
                float vec[4];
                int port = PLAYER_REC(i)[0xCA];
                int x, y;
                u8 *p = (u8 *)vec;
                int n;

                for (n = 16; n != 0; n--)
                    *p++ = 0;
                x = PAD_READY_N(port) ? g_00500700_bytes[port * 0x88 + 8] : 0x80;
                y = PAD_READY_N(port) ? g_00500700_bytes[port * 0x88 + 9] : 0x80;
                if (func_0011B740(-(x - 0x80)) > 0x40)
                    vec[0] = (float)-(x - 0x80) / 128.0f;
                if (func_0011B740(-(y - 0x80)) > 0x40)
                    vec[2] = (float)-(y - 0x80) / 128.0f;
                if (!(PAD_READY_N(port) &&
                      ((g_00500700_bytes[port * 0x88 + 0x64] & 0xF) >> 3) == 1)) {
                    vec[0] = vec[0] * -1.0f;
                    vec[2] = vec[2] * -1.0f;
                }
                if (xz_dist2(vec, g_700000C0) > 0.0001f) {
                    if ((*(u32 *)(*(u8 **)(UNIT(i) + 0x210) + 0x18) & 0x20100) != 0 && vec[2] < 0.0f)
                        vec[2] = vec[2] * 0.25f;
                    func_0029E070(*(u32 *)g_005B49E0[i], vec);
                }
            }
            func_00164440(dt, 50.0f, (int *)(g_005B49E0[i]));
        }
    }
}

/* 0x001D28E0, 0x1A8 bytes. End of a frame for both players: officer skill effects
 * (func_00249390 / 670 / AD0) and the best combo of the battle. */
void func_001D28E0(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        u8 *unit = UNIT(i);

        if ((unit[0x198] & 2) && *(int *)(unit + 0x11C) != 0) {
            int skill = func_002F47A0(*(u32 *)(PLAYER_REC(unit[0x14E]) + 0x88), 0x27);
            u8 *other = func_00240CA0(unit);
            u32 combo;

            if (other != 0)
                func_00249390(i, other[0x14E]);
            if (unit[0x19D] & 4)
                func_00249670(i, unit[0x14E], *(u32 *)(*(u8 **)(unit + 0x210) + 0x18) & 0x8000000);
            if (func_0016CA00(unit) != 0) {
                u8 kind = *(u8 **)(unit + 0x110) == 0 ? 0x6A : (*(u8 **)(unit + 0x110))[0x1C];
                if (func_001BEA90(kind) != 0 && skill != 0)
                    func_00249AD0(i, unit[0x14E]);
            }
            if (unit[0x19F] & 0x40)
                func_00249670(i, unit[0x14E], 1);
            combo = g_0045D3A8[i];
            if (combo < 10000) {
                *(u32 *)(PLAYER_REC(i) + 0x90) = combo;
                if (*(u32 *)(PLAYER_REC(i) + 0x94) < combo)
                    *(u32 *)(PLAYER_REC(i) + 0x94) = combo;
            }
        }
    }
}

/* Message box flags of three objects of 0x0068F3E0 (bit 7: hidden during the battle?). */
extern u8 g_00693703, g_0069382B, g_00693953;

/* 0x001D2A90, 0xC4 bytes. Scene 0x05 enter. */
void func_001D2A90(void)
{
    s_00730350.phase = 0;
    g_00669F60 = (g_00669F60 & 0xFFF9FFFF) | 0x10000;
    g_00693703 &= 0x7F;
    g_0069382B &= 0x7F;
    g_00693953 &= 0x7F;
    g_0045CC80 = 8;
    if (g_0045D894 == 8)
        func_001B8F60(1, 6, 0x80);
    s_00730350.data = 0;
    s_00730350.started = 0;
    s_00730350.g_0073035B = 0;
}

/* 0x001D2B60, 0x16C bytes. Scene 0x05 leave. After a demo battle: back to the title through
 * scene 0x10 (the title skips its animation when the demo was cut short, ending 5). */
void func_001D2B60(void)
{
    g_00693703 |= 0x80;
    g_0069382B |= 0x80;
    g_00693953 |= 0x80;
    if ((g_00669F60 & 0x10) == 0) {
        g_00669F60 &= 0xFFFEFFFF;
        func_001D2CD0();
        s_00730350.g_0073035B = 0;
        return;
    }
    g_00669F60 &= 0xFFFEFFFF;
    func_001D4150();
    func_00160020(g_00669F70 == 5);
    g_0045D894 = g_0045D898;
    LEAVE_IF_NONE(0x10);
    SWITCH_SCENE();
    func_001BEAB0();
    func_001BEB30();
    func_00278870();
    s_00730350.g_0073035B = 0;
}

/* 0x001D2CD0, 0x34 bytes, matching. Frees g_00730354. */
void func_001D2CD0(void)
{
    if (s_00730350.data != 0) {
        func_00102EC0(s_00730350.data);
        s_00730350.data = 0;
    }
}

/* The time step of the effects (a quarter in slow motion). */
#define EFFECT_STEP(dt) (g_0045D2A8 == 0 ? (dt) * g_0045CC7C : (dt) * g_0045CC7C * 0.25f)

/* Runs the screen effects at the end of a frame (inlined in the original). */
#define EFFECTS_END(dt) do {                                                           \
        func_002E5DA0(EFFECT_STEP(dt));                                                \
        func_001C8A00();                                                               \
        func_002171E0();                                                               \
        if ((g_00669F60 & 0x400000) != 0 && (g_00669F60 & 0x800000) == 0 &&           \
            (g_00669F60 & 0x2000000) == 0 && func_002E6510(dt) == 0) {                 \
            func_002E6790();                                                           \
            g_00669F60 &= 0xFFBFFFFF;                                                  \
        }                                                                              \
    } while (0)

/* 0x001D2D10, 0xE0 bytes. The battle's frame while a movie plays (func_0032E7B0). */
void func_001D2D10(float dt)
{
    func_00193980(dt);
    func_001D2530(dt);
    EFFECTS_END(dt);
}

/* 0x001D2DF0, 0x244 bytes. The battle's frame: the stage, the players (each army's unit), the
 * combos, the camera and the effects, and the battle clock (g_00669F9C frames, up to 50 minutes). */
void func_001D2DF0(float dt)
{
    func_0035D660();
    if (func_0032E7B0() != 0) {
        func_001D2D10(dt);
        return;
    }
    func_00214E00(dt);
    func_00193980(dt);
    g_70000D60 = 0;
    func_001BB760();
    func_00183DE0();
    if ((g_00669F60 & 0x10) == 0) {
        if ((g_00669F60 & 2) == 0) {
            if ((g_006A3A44[0].flags & 0x10) == 0) {
                g_0045D2C0 = g_005B4BC0[0];
                func_00177530(0);
            }
        } else {
            if ((g_006A3A44[0].flags & 0x10) == 0) {
                g_0045D2C0 = g_005B4BC0[0];
                func_00177530(0);
            }
            if ((g_006A3A44[1].flags & 0x10) == 0) {
                g_0045D2C0 = g_005B4BC0[1];
                func_00177530(1);
            }
            g_0045D2C0 = g_005B4BC0[0];
        }
    }
    func_001784E0(dt);
    func_001D2310(dt);
    func_001D2530(dt);
    EFFECTS_END(dt);
    if ((g_00669F60 & 0x4000000) == 0 || (g_00669F60 & 8) != 0) {
        g_00669F9C++;
        if (g_00669F9C >= 180000)
            g_00669F9C = 180000;
        func_00360B00();
        func_00360B90();
    }
}

/* 0x001D3040, 0x17C bytes. The frame of the end-of-battle camera: both units face the camera's
 * direction; returns non-zero once the 250-frame countdown is over. */
int func_001D3040(float dt)
{
    func_00193980(dt);
    *(int *)(UNIT(0) + 0x13C) = 0;
    normalize3((float *)(UNIT(0) + 0x1D0), g_700000C0);
    *(int *)(UNIT(1) + 0x13C) = 0;
    normalize3((float *)(UNIT(1) + 0x1D0), g_700000C0);
    func_001784E0(dt);
    func_001D2530(dt);
    func_002E5DA0(EFFECT_STEP(dt));
    func_001C8A00();
    func_002171E0();
    if (s_00730350.started == 0) {
        func_003E7310(0);
        g_70000D60 = 0;
        s_00730350.started = 1;
    }
    if (s_00730350.started != 0 && s_00730350.countdown != 0)
        s_00730350.countdown--;
    return s_00730350.countdown == 0;
}

/* 0x001D31C0, 0x460 bytes. Checks the battle's state flags (g_00669F60) and picks the next phase:
 * 7 the ending camera (bit 29), the result by g_00669F70 (bit 27: 5 / 6 a demo cut short, 0 / 3 / 4
 * a jingle then scene 7, others scene 6), 2-5 the special sequences, or scene 7 (bit 20).
 * Returns 0 when nothing happened. */
int func_001D31C0(void)
{
    int current = g_0045D898;

    if (g_00669F60 & 0x20000000) {
        s_00730350.countdown = 0xFA;
        s_00730350.phase = 7;
        s_00730350.g_00730358 = 0;
        s_00730350.started = 0;
        s_00730350.data = 0;
        func_0036D000();
        return 1;
    }
    if (g_00669F60 & 0x8000000) {
        if (g_00669F70 == 6 || g_00669F70 == 5) {
            if ((g_00669F60 & 0x10) != 0 && func_00102960(0) != 0) {
                LEAVE_IF_NONE(0x10);
                func_001B8F60(0, 6, 8);
                s_00730350.phase = 6;
            }
        } else if (g_00669F70 == 4 || g_00669F70 == 3 || g_00669F70 == 0) {
            if (func_00102960(0) != 0) {
                if (s_00730350.g_0073035B == 0) {
                    func_002D6C30(0);
                    func_001D5DF0(0);
                    s_00730350.g_0073035B = 1;
                } else if (func_0017DDA0() == 0) {
                    func_0017E040(g_00669F70 == 0 ? 0x1F : 0x21);
                } else {
                    int cue = func_0017E0A0();
                    if (cue == 0x1F || cue == 0x21) {
                        func_003E57D0();
                        func_001014D0(1);
                        g_0045D890 = 1;
                        g_00669F60 |= 0x100000;
                        LEAVE_IF_NONE(7);
                        g_0045D894 = g_0045D898;
                        SWITCH_SCENE();
                    }
                }
            }
        } else {
            LEAVE_IF_NONE(6);
            func_001B8F60(0, 6, 8);
            s_00730350.phase = 6;
        }
        return 1;
    }
    if (g_00669F60 & 0x800000) {
        s_00730350.phase = 2;
        return 1;
    }
    if (g_00669F60 & 0x2000000) {
        s_00730350.phase = 3;
        return 1;
    }
    if (g_00669F60 & 0x80000) {
        s_00730350.phase = 4;
        return 1;
    }
    if (g_00669F60 & 0x200000) {
        s_00730350.phase = 5;
        return 1;
    }
    if (g_00669F60 & 0x100000) {
        g_0045D890 = 1;
        LEAVE_IF_NONE(7);
        SWITCH_SCENE();
        g_0045D894 = current;
        return 1;
    }
    return 0;
}

/* 0x001D3620, 0x270 bytes. Start pauses the battle (scene 8, the pause menu; which player paused
 * is kept in bits 17 / 18 of g_00669F60). In a demo, Start ends the demo instead (ending 6). */
int func_001D3620(void)
{
    int port1 = PLAYER_REC(0)[0xCA], port2;
    unsigned short pressed1, pressed2;

    pressed1 = PAD_READY_N(port1) ? *(unsigned short *)&g_00500700_bytes[port1 * 0x88 + 0x4C] : 0;
    if ((g_00669F60 & 2) == 0) {
        pressed2 = 0;
    } else {
        port2 = PLAYER_REC(1)[0xCA];
        pressed2 = PAD_READY_N(port2) ? *(unsigned short *)&g_00500700_bytes[port2 * 0x88 + 0x4C] : 0;
    }
    if (func_0032E7B0() == 0 && ((pressed1 & BTN_START) || (pressed2 & BTN_START))) {
        if ((g_00669F60 & 0x10) == 0) {
            if ((g_00669F60 & 0x4000008) == 0) {
                func_0023AD10(5, 0, 0x2CDC, 0x2CDC, 0x1000);
                g_0045D890 = 1;
                LEAVE_IF_NONE(8);
                if (pressed1 & BTN_START)
                    g_00669F60 = (g_00669F60 & 0xFFFBFFFF) | 0x20000;
                else if (pressed2 & BTN_START)
                    g_00669F60 = (g_00669F60 & 0xFFFDFFFF) | 0x40000;
                func_001B8F60(0, 6, 0x80);
                s_00730350.phase = 6;
                return 1;
            }
        } else {
            g_00669F70 = 6;
            g_00669F60 |= 0xC000000;
        }
    }
    return 0;
}

/* 0x001D3890, 0x340 bytes. Scene 0x05 update (time x 1.2). Phases: 0 wait for box 1, 1 the
 * battle (pause check, frame, state check), 2 / 3 the sequences of func_001F2240, 4 / 5 those of
 * func_001D6920 / func_001D6B60, 6 leave once box 1 is closed, 7 the ending camera, then scene 6. */
int func_001D3890(float dt)
{
    int still;

    dt = dt * 1.2f;
    switch (s_00730350.phase) {
    case 0:
        if (box1_open()) {
            func_001D2DF0(dt);
            return 1;
        }
        s_00730350.phase = 1;
        /* fall through */
    case 1:
        if (func_001D3620() == 0) {
            func_001D2DF0(dt);
            func_001D31C0();
        }
        break;
    case 2:
        if (func_001F2240(dt) == 0) {
            g_00669F60 &= 0xFF7FFFFF;
            func_001F2130();
            s_00730350.phase = 1;
        }
        g_0045CC80 = 8;
        break;
    case 3:
        if (func_001F2240(dt) == 0) {
            g_00669F60 &= 0xFDFFFFFF;
            func_001F2130();
            s_00730350.phase = 1;
        }
        g_0045CC80 = 8;
        break;
    case 4:
        if (func_001D6920(dt, &still) == 0) {
            g_00669F60 &= 0xFFF7FFFF;
            func_001D6A60();
            s_00730350.phase = 1;
        }
        if (still != 0)
            func_001D2DF0(dt);
        break;
    case 5:
        if (func_001D6B60(dt) == 0) {
            g_00669F60 &= 0xFFDFFFFF;
            func_001D6B90();
            s_00730350.phase = 1;
        }
        break;
    case 6:
        if (!box1_open())
            GO_TO_NEXT_SCENE();
        break;
    case 7:
        if (func_001D3040(dt) != 0) {
            g_00669F60 &= 0xDFFFFFFF;
            LEAVE_IF_NONE(6);
            func_001B8F60(0, 6, 8);
            func_0023AC40();
            s_00730350.phase = 6;
            g_00669F60 |= 0x8000000;
        }
        break;
    }
    return 1;
}

/* 0x001D3BD0, 0x48 bytes, matching. Scene 0x05 step. */
void func_001D3BD0(void)
{
    func_001D28E0();
    func_001D23B0();
    g_70000D60 = 0;
    func_00178CC0();
    func_00193940();
    func_001C8B30();
    func_0023C0D0();
}

/* 0x001D3C20, 0xC0 bytes, matching. Draws the battle with one view. */
void func_001D3C20(void)
{
    if (func_0032E7B0() != 0)
        return;
    func_00191240(0);
    g_0045D2C0 = g_005B4BC0[0];
    func_0022E5D0();
    func_00195C60();
    func_00195CE0();
    func_001F5150();
    func_001796D0();
    func_001F5260();
    func_002E5E10(0, 0);
    func_001C92D0(0);
    func_0017A350();
    if ((g_00669F60 & 0x400000) != 0 && (g_00669F60 & 0x800000) == 0 &&
        (g_00669F60 & 0x2000000) == 0)
        func_002E65D0();
}

/* Selects player `p` for the split-screen drawing (inlined in the original). */
#define SELECT_PLAYER(p) do {                   \
        func_0017A400(p);                       \
        g_0045D470 = (p);                       \
        g_0045D2C0 = g_005B4BC0[p];             \
    } while (0)

/* 0x001D3CE0, 0x168 bytes. Draws the battle with two views (two armies). */
void func_001D3CE0(void)
{
    func_0022ECD0(0);
    func_0022ECD0(1);
    SELECT_PLAYER(0);
    func_00191240(2);
    func_00195C60();
    func_00195CE0();
    func_001F5150();
    SELECT_PLAYER(1);
    func_00191240(3);
    func_00195C60();
    func_00195CE0();
    func_001F5150();
    SELECT_PLAYER(0);
    func_00218E80();
    func_00179700(0);
    SELECT_PLAYER(1);
    func_00218E80();
    func_00179700(1);
    SELECT_PLAYER(0);
    func_00191240(2);
    func_001F5260();
    func_002E5E10(0, 1);
    func_001C92D0(0);
    SELECT_PLAYER(1);
    func_00191240(3);
    func_001F5260();
    func_002E5E10(1, 1);
    func_001C92D0(1);
    func_0017A530();
}

/* 0x001D3E50, 0x1B0 bytes. Draws the two views, each only when asked (`first`, `second`). */
void func_001D3E50(int first, int second)
{
    if (first)
        func_0022ECD0(0);
    if (second)
        func_0022ECD0(1);
    if (first) {
        SELECT_PLAYER(0);
        func_00191240(2);
        func_00195C60();
        func_00195CE0();
        func_001F5150();
    }
    if (second) {
        SELECT_PLAYER(1);
        func_00191240(3);
        func_00195C60();
        func_00195CE0();
        func_001F5150();
    }
    if (first) {
        SELECT_PLAYER(0);
        func_00179700(0);
    }
    if (second) {
        SELECT_PLAYER(1);
        func_00179700(1);
    }
    if (first) {
        SELECT_PLAYER(0);
        func_00191240(2);
        func_001F5260();
        func_002E5E10(0, 1);
        func_001C92D0(0);
    }
    if (second) {
        SELECT_PLAYER(1);
        func_00191240(3);
        func_001F5260();
        func_002E5E10(1, 1);
        func_001C92D0(1);
    }
    func_0017A530();
}

/* 0x001D4000, 0x150 bytes. Scene 0x05 draw: one or two views (a special sequence may draw them
 * itself), the battle interface, and in a demo the demo picture and a caption. */
void func_001D4000(void)
{
    if ((g_00669F60 & 2) == 0) {
        if ((g_00669F60 & 0x800000) == 0 || func_001F2A00() == 0)
            func_001D3C20();
    } else if ((g_00669F60 & 0x800000) == 0) {
        func_001D3CE0();
    } else if (func_001F2A00() == 0) {
        if (func_001F24C0() == 0)
            func_001D3E50(func_001F2880(0), func_001F2880(1));
        else
            func_001D3C20();
    }
    if (s_00730350.started == 0) {
        func_001FB8E0();
        func_00214F40();
    }
    if (s_00730350.started != 0)
        func_003E7430();
    if ((g_00669F60 & 0x10) != 0) {
        func_001BEB60();
        func_00279140(0x7C, 0xB4, 0, 0x108, 0x18, 7);
    }
}

/* 0x001D42E0, 0x1AC bytes. Prepares the game state for a battle (mode flags 2 / 3, the stage of
 * the battle in a series) and the battle systems. */
void func_001D42E0(void)
{
    if (g_00669F6C == 0)
        func_0019F410();
    g_00669F70 = 0;
    if (g_00669DB8 == 3)
        g_00669F60 = (g_00669F60 & 0xF3FFFFFB) | 8;
    else if (g_00669DB8 == 2)
        g_00669F60 = (g_00669F60 & 0xF3FFFFF7) | 4;
    else
        g_00669F60 &= 0xF3FFFFF3;
    func_0039EB00();
    func_0019FFE0();
    func_001A9140();
    func_003E3100();
    func_003E7150();
    func_0035ED20();
    func_003635A0();
    func_0035FD10();
    if (g_00669F6C == 1)
        func_003E4480();
    func_00213F40(g_00669DB8 == 2 ? g_00669DC0[g_00669F98 % 5] : g_00669DC0[0]);
    func_001C77D0(0);
    func_0018C500();
    func_00216B40();
    func_00194010();
    func_001BE1A0();
    func_00185CE0();
    func_00185CA0();
    func_0022E150();
    func_0020EBB0();
}

/* ---- Soldier groups (0x006A1D58) -------------------------------------------------------------- */

/* 0x001D4BF0, 0x10 bytes, matching. */
void func_001D4BF0(SoldierGroup *group)
{
    group->unknown_58 = 0.0f;
    group->unknown_5c = 0.0f;
    group->unknown_60 = 0.0f;
}

/* 0x001D4C00, 0x20 bytes, matching. */
void func_001D4C00(u8 *group)
{
    func_0033D920(group, 1, 0);
}

/* 0x001D4C20, 0x74 bytes. func_001EEBF0 (or func_001EEC50 when `alt`) on each soldier. */
void func_001D4C20(SoldierGroup *group, int alt)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0) {
            if (alt != 0)
                func_001EEC50(PS2_ADDR(group->members[i]));
            else
                func_001EEBF0(PS2_ADDR(group->members[i]));
        }
}

/* 0x001D4CA0, 0x80 bytes, matching. */
void func_001D4CA0(SoldierGroup *group, int a, int b, int c)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EF190(group->members[i], a, b, c);
}

/* 0x001D4D20, 0x6C bytes, matching. */
void func_001D4D20(SoldierGroup *group, int a, int b)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EC900(group->members[i], a, b);
}

/* 0x001D4D90, 0x48 bytes. Sets each soldier's +0x24 to `value` clamped to 1-20. */
void func_001D4D90(float value, SoldierGroup *group)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0) {
            float v = value < 20.0f ? value : 20.0f;
            *(float *)(group->members[i] + 0x24) = v > 1.0f ? v : 1.0f;
        }
}

/* 0x001D4DE0, 0x60 bytes, matching. */
void func_001D4DE0(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EECE0(PS2_ADDR(group->members[i]), a);
}

/* 0x001D4E40, 0x60 bytes, matching. */
void func_001D4E40(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EEDE0(PS2_ADDR(group->members[i]), a);
}

/* 0x001D4EA0, 0x60 bytes, matching. */
void func_001D4EA0(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EEEE0(group->members[i], a);
}

/* 0x001D4F00, 0x58 bytes, matching. Gives each soldier (except state 3) the target `pos` and `value`. */
void func_001D4F00(SoldierGroup *group, const u64 *pos, const u16 *value)
{
    u32 i;

    for (i = 0; i < 13; i++) {
        u8 *s = group->members[i];
        if (s != 0 && s[0x7A] != 3) {
            *(u64 *)(s + 0x38) = *pos;
            *(u32 *)(s + 0x84) |= 0x10;
            *(u16 *)(s + 0x44) = *value;
        }
    }
}

/* 0x001D4F60, 0x48 bytes, matching. Gives each soldier (except state 3) the value `value` (+0x1C). */
void func_001D4F60(SoldierGroup *group, u32 value)
{
    u32 i;

    for (i = 0; i < 13; i++) {
        u8 *s = group->members[i];
        if (s != 0 && s[0x7A] != 3) {
            *(u32 *)(s + 0x1C) = value;
            *(u32 *)(s + 0x84) |= 0x10;
        }
    }
}

/* 0x001D4FB0, 0xA0 bytes. Dissolves the group: its soldiers leave it (group 0x47 = none). */
void func_001D4FB0(SoldierGroup *group)
{
    u32 i, j;

    for (i = 0; i < 13; i++) {
        u8 *s = group->members[i];
        if (s != 0) {
            for (j = 0; j < 13; j++)
                if (group->members[j] == s) {
                    group->members[j] = 0;
                    break;
                }
            *(u32 *)(s + 0x10) = 0x47;
            func_001EE3B0(s);
        }
    }
    group->flags = 0;
}

/* 0x001D5060, 0x54 bytes, matching. */
void func_001D5060(SoldierGroup *group)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EE570(group->members[i]);
}

/* 0x001D50C0, 0x60 bytes, matching. */
void func_001D50C0(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EE6B0(PS2_ADDR(group->members[i]), a);
}

/* 0x001D5120, 0x7C bytes, matching. func_001EE750 on each soldier, and the group stops retreating. */
void func_001D5120(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0) {
            func_001EE750(PS2_ADDR(group->members[i]), a);
            group->flags &= ~2u;
        }
}

/* 0x001D51A0, 0x48 bytes, matching. Each soldier's +0x5C = `percent` / 100. */
void func_001D51A0(SoldierGroup *group, int percent)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            *(float *)(group->members[i] + 0x5C) = (float)percent * 0.01f;
}

/* 0x001D51F0, 0x48 bytes, matching. Each soldier's +0x58 = `percent` / 100. */
void func_001D51F0(SoldierGroup *group, int percent)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            *(float *)(group->members[i] + 0x58) = (float)percent * 0.01f;
}

/* 0x001D5240, 0x60 bytes, matching. */
void func_001D5240(SoldierGroup *group, int a)
{
    u32 i;

    for (i = 0; i < 13; i++)
        if (group->members[i] != 0)
            func_001EE9C0(group->members[i], a);
}

/* 0x001D52A0, 0x1C4 bytes. When `officer` is within 1000 of a player, marks the group (4) and
 * queues event 0x0F (player, officer). */
void func_001D52A0(SoldierGroup *group, u8 *officer)
{
    float *pos = (float *)(g_006A3A44[*(int *)(officer + 0x14)].unit + 0x40);
    BattleEvent ev;

    if (dist2(pos, (float *)(g_006A3A44[0].unit + 0x40)) <= 1e6f) {
        group->flags |= 4;
        ev.type = 0x0F;
        ev.b = (u16)SOLDIER_INDEX(officer);
        ev.a = 0;
        func_0023EB40((short int *)(&ev), 3, 0);
    } else if ((g_00669F60 & 2) != 0 &&
               dist2(pos, (float *)(g_006A3A44[1].unit + 0x40)) <= 1e6f) {
        group->flags |= 4;
        ev.a = 1;
        ev.type = 0x0F;
        ev.b = (u16)SOLDIER_INDEX(officer);
        func_0023EB40((short int *)(&ev), 3, 0);
    }
}

/* The strength used for a group, by game mode (modes with flags 4 / 8 use fixed values). */
static int group_strength(SoldierGroup *g)
{
    if ((g_00669F60 & 0xC) == 0)
        return g->strength;
    return g->members[0][0x79] == 0 ? 0x15E : 0x28A;
}

/* 0x001D5470, 0x2B8 bytes. Decides whether the group of `officer` retreats: alone with
 * func_0034A200 low, or facing 5 leaders 200 stronger on average. A retreat sets flag 2, a
 * 6000-frame timer and queues events 7 (and 8 when the officer is strong enough). */
void func_001D5470(SoldierGroup *group, u8 *officer)
{
    int count = 0, total = 0, retreat = 0;
    u32 i;

    for (i = 0; i < 5; i++) {
        u8 *l = group->leaders[i];
        if (l != 0) {
            u32 g = *(u32 *)(l + 0x10);
            count++;
            if (g < 0x47)
                total += group_strength(&g_006A1D58[g]);
            else
                total += 100;
        }
    }
    if (count < 1 || func_0034A200(officer) > 0x1D) {
        if (count > 4 && total / count >= group_strength(group) + 200)
            retreat = 1;
    } else {
        retreat = 1;
    }
    if (!retreat) {
        group->flags &= ~2u;
        return;
    }
    group->flags |= 2;
    group->timer = 6000;
    if ((*(u32 *)(officer + 0x80) & 0x20000) == 0) {
        BattleEvent ev;

        ev.type = 7;
        ev.a = (u16)SOLDIER_INDEX(officer);
        ev.b = (*(u32 *)(officer + 0x80) & 0x200) != 0;
        func_0023EB40((short int *)(&ev), 3, 0);
        if ((*(u32 *)(officer + 0x80) & 0x400) != 0) {
            if (*(short *)(officer + 0x52) > 0x32 && total / count < group_strength(group) + 300)
                return;
            ev.type = 8;
            func_0023EB40((short int *)(&ev), 3, 1);
        }
    }
}

/* 0x001D5730, 0x184 bytes. Lets an idle group's leader pick a target (func_0033D0B0 /
 * func_0033CC20) and start it (func_0035CA60), once. */
void func_001D5730(SoldierGroup *group)
{
    u8 *leader;
    u32 flags;
    int target, active = 0, idle = 0;

    if (group == 0 || (group->flags & 1) == 0)
        return;
    leader = group->members[0];
    flags = *(u32 *)(leader + 0x80);
    if ((flags & 1) != 0 && (flags & 0x8C40002) == 0)
        active = 1;
    if (active && (flags & 4) == 0)
        idle = 1;
    if (idle && func_0033B050((unsigned char **)(group)) != 0 && (*(u32 *)(leader + 0x84) & 0x10000) == 0 &&
        (target = PS2_ADDR(func_0033D0B0((unsigned char **)(group)))) != 0 && func_0033CC20((unsigned char **)(group), (unsigned char **)PS2_PTR(target)) != 0 &&
        (group->members[0][0x79] != 1 ||
         (leader[0x7A] == 2 && *(int *)(leader + 0x18) != 0 && PS2_ADDR(func_0034A740((u8 *)PS2_PTR(*(int *)(leader + 0x18)))) == target))) {
        func_0035CA60(func_0033B890((unsigned char **)PS2_PTR(target)), group - g_006A1D58);
        *(u32 *)(leader + 0x84) |= 0x10000;
    }
}

/* 0x001D58C0, 0x1F0 bytes. Runs the soldier groups (not in the flagged phase): targets, retreat
 * decisions (on a timer), player proximity events and timed groups. */
void func_001D58C0(void)
{
    u32 i;

    if ((g_00669F60 & 0x10000000) != 0)
        return;
    for (i = 0; i < 0x47; i++) {
        SoldierGroup *g = &g_006A1D58[i];
        u8 *leader = g->members[0];

        if ((g->flags & 1) && leader != 0 && (*(u32 *)(leader + 0x80) & 8)) {
            u8 kind = leader[0x79];
            u32 flags;
            int active = 0;

            if ((*(u32 *)(leader + 0x80) & 0x4001B0) == 0)
                func_001D5730(g);
            flags = *(u32 *)(leader + 0x80);
            if ((flags & 1) != 0 && (flags & 0x8C40002) == 0)
                active = 1;
            if (active && (flags & 0x1B0) == 0 && kind == 0 && (flags & 0x800) != 0) {
                if (g->timer < 1)
                    func_001D5470(g, leader);
                else
                    g->timer--;
            }
            if ((g->flags & 2) && (g->flags & 4) == 0 && (*(u32 *)(leader + 0x80) & 0x20000) &&
                (*(u32 *)(leader + 0x80) & 0x400))
                func_001D52A0(g, leader);
            if (g->flags & 8) {
                if (g->timer < 1) {
                    func_001D4C20(g, 0);
                    g->flags &= ~8u;
                } else {
                    g->timer--;
                }
            }
        }
    }
}

/* 0x001D5AC0, 0x80 bytes. Clears a group. */
void func_001D5AC0(SoldierGroup *group)
{
    u32 i;

    for (i = 0; i < 13; i++)
        group->members[i] = 0;
    for (i = 0; i < 5; i++)
        group->leaders[i] = 0;
    group->timer = 0;
    func_001D4BF0(group);
    group->flags = 0;
}

/* 0x001D5B40, 0x11C bytes. Loads the groups from `src` (saved with soldier indices, -1 = none):
 * copies them and turns the indices back into pointers. Returns `src` after the 0x47 groups. */
u8 *func_001D5B40(u8 *src)
{
    u32 i, j;

    for (i = 0; i < 0x47; i++, src += 0x68) {
        SoldierGroup *g = &g_006A1D58[i];

        func_00118AC0((unsigned int *)(g), src, 0x68);
        if (g->flags & 1) {
            for (j = 0; j < 13; j++) {
                int k = *(int *)&g->members[j];
                g->members[j] = k == -1 ? 0 : g_00693970 + k * 0x88;
            }
            for (j = 0; j < 5; j++) {
                int k = *(int *)&g->leaders[j];
                g->leaders[j] = k == -1 ? 0 : g_00693970 + k * 0x88;
            }
        }
    }
    return src;
}

/* 0x001D5C60, 0x140 bytes. Saves the groups to `dst`, soldier pointers as indices (-1 = none).
 * Returns `dst` after the 0x47 groups. */
SoldierGroup *func_001D5C60(SoldierGroup *dst)
{
    u32 i, j;

    for (i = 0; i < 0x47; i++, dst++) {
        func_00118AC0((unsigned int *)(dst), (unsigned char *)(&g_006A1D58[i]), 0x68);
        if (dst->flags & 1) {
            for (j = 0; j < 13; j++)
                *(int *)&dst->members[j] = dst->members[j] == 0 ? -1 : (int)SOLDIER_INDEX(dst->members[j]);
            for (j = 0; j < 5; j++)
                *(int *)&dst->leaders[j] = dst->leaders[j] == 0 ? -1 : (int)SOLDIER_INDEX(dst->leaders[j]);
        }
    }
    return dst;
}

/* 0x001D5DA0, 0x1C bytes, matching. */
void func_001D5DA0(void)
{
    func_00339910();
}

/* 0x001D5DC0, 0x2C bytes, matching. Clears all the groups. */
void func_001D5DC0(void)
{
    func_00118850((unsigned char *)(g_006A1D58), 0x1CD8);
    func_003394D0();
}

/* 0x001D5DF0, 0x104 bytes. Starts the end-of-battle cameras (shot lists 0x00730A20 /
 * 0x00730B94); with one army also its first shot's sound (and waits for the loading if `wait`). */
void func_001D5DF0(int wait)
{
    func_0020EC70();
    g_0073C79D = 0;
    g_0045D3E0 = 0;
    func_001D91A0((unsigned char *)(&g_00730480[0]), PS2_ADDR(g_00730A20));
    if (g_0073C790 == 0xB6) {
        func_0023A2F0(0x1478, NEXT_SHOT(g_0045D3E0), 0);
        *(int *)((u8 *)&g_00730A44[g_0045D3E0] - 4) = 0;
        g_00730A44[g_0045D3E0].next = 0;
        if (wait != 0)
            func_00102960(1);
    } else {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D91A0((unsigned char *)(&g_00730480[1]), PS2_ADDR(g_00730B94));
    }
}

/* 0x001D68E0, 0x38 bytes, matching. Resets the sequence of func_001D6920. */
void func_001D68E0(void)
{
    g_0045D3C0 = 0.0f;
    g_0045D3BC = 0.0f;
    g_0045D3B8 = 0;
    func_001CB810(g_00730360, 0x30);
    g_0045D3B4 = 1;
}

/* 0x001D6920, 0x140 bytes. A short sequence (phase 4): a camera on the player (sound 0x0B),
 * 30 frames, then fades out; `*still` is 0 once the battle should stop being updated. Returns
 * non-zero for the first 88 frames. */
int func_001D6920(float dt, int *still)
{
    if (g_0045D3B8 == 0) {
        g_70000D60 = 10;
        func_001C8620(g_00730360, 299, g_0045D2C0 + 0x1C0, 0, 0x225);
        func_0023AD10(0x0B, 0, 0x2CDC, 0x2CDC, 0x1000);
        g_0045D3BC = 0.0f;
        g_0045D3B8++;
    }
    if (g_0045D3B8 == 1 && g_0045D3BC > 30.0f) {
        g_0045D3BC = 0.0f;
        g_0045D3B8 = 2;
    }
    if (g_0045D3B8 == 2) {
        func_001B8F60(0, 6, 0xFF);
        func_0023AA40();
        func_0023B320();
        g_0045D3B4 = 0;
        g_0045D3BC = 0.0f;
        g_0045D3B8++;
    }
    *still = g_0045D3B4;
    g_0045D3C0 += dt;
    g_0045D3BC += dt;
    return g_0045D3C0 - dt < 88.0f;
}

/* 0x001D6A60, 0xD8 bytes. End of the phase-4 sequence: on to scene 7 (an intro). */
void func_001D6A60(void)
{
    g_0045D894 = g_0045D898;
    g_00730398 |= 8;
    g_00669F60 |= 0x100000;
    LEAVE_IF_NONE(7);
    SWITCH_SCENE();
}
