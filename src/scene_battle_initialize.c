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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
} g_00669D60;
#define g_00669DB2 (g_00669D60.g_00669DB2)
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669DC0 (g_00669D60.g_00669DC0)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)
#define g_00669F70 (g_00669D60.g_00669F70)
#define g_00669F98 (g_00669D60.g_00669F98)

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
extern int g_0045D3B4, g_0045D3B8, g_0045D3BC, g_0045D3C0;
extern int g_0045D3E0;                    /* army being handled (as g_0073C79D) */

void func_00102990(void);
int func_00102960(int value);
void func_00213F90(void);
void func_00185160(void);
void func_00185210(void);
void func_00279B20(void);
void func_00178460(void);
void func_00193FB0(void);
void func_0018C730(void);
void func_001C7CE0(void);
void func_00216D60(void);
void func_0022EF00(void);
void func_0020EC20(void);
void func_003600F0(void);
void func_0035ED90(void);
void func_003E3150(void);
void func_003E44D0(void);
void func_003E7260(void);
void func_001A9030(void);
int func_0032E7B0(void);
void func_001020E0(void);
void func_0023BFA0(void);
void func_001B8BF0(void);
void func_002E5D20(void);
void func_001FB660(void);
void func_002E6390(void);
void func_001DB9F0(void);
void func_001D97B0(void);
void func_00102EC0(void *data);
void func_0017DF10(void);
void func_0032FF30(void);
void func_0032E7A0(int value);
void func_001023B0(int value);
void func_001D2CD0(void);
void func_001D2B60(void);
void func_0017A920(u8 *unit);
void func_0017AA80(u8 *unit, int player);
void func_00161E10(u8 *a, u8 *b, u8 *unit);
void func_0017AC50(u8 *unit);
void func_002F1660(void);
void func_00101470(int value);
void func_0036E170(void);
void func_003F8260(void);
void func_00360090(void);
void func_003E4480(void);
void func_001DB8E0(void);
void func_001C7B80(void);
void func_00193FF0(void);
void func_00279A10(void);
void func_0022E280(void);
void func_00185300(void);
void func_001FB440(void);
void func_0023BFF0(void);
void func_002E5C80(u16 value);
void func_0024BF20(void);
void func_00216DF0(void);
void func_0027A010(void);
void func_0036D170(void);
void func_0036D150(void);
void func_001D22F0(void);
void func_002D6FB0(void);
void func_001B8F60(int a, int b, int c);
u32 func_0032EEB0(void);
u32 func_002F27D0(u32 officer);
int func_0032F780(void);
void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_001D96E0(void);
void func_00190C00(u32 *out, int a);
u8 func_0020E310(u32 model);
u32 func_0032E8E0(int i);
void func_0032F8A0(void);
void func_0023B3C0(int a, int b);
void func_0027F800(void);
void func_001C8870(int value);
void func_0020EC70(void);
int func_0020E140(void);
int func_0020E170(void);
int func_0020E1A0(void);
void func_0017A640(void);
void func_001D9280(IntroCamera *camera);
void func_0023A2F0(int a, u32 shot, int b);
void func_0023AA40(void);
void func_0023B320(void);
void func_001D91F0(IntroCamera *camera, int a);
void func_0017DEA0(int value);
void func_001D92E0(IntroCamera *camera);
void func_0020E570(void);
void func_0027F980(void);
void func_00218790(int a, int b);
void func_00218C40(int a, int b);
void func_002E5ED0(void);
int func_001D93B0(IntroCamera *camera, float *step);
int func_0017DDA0(void);
void func_002171E0(void);
void func_00193980(float step);
void func_002E5DA0(float step);
int func_0020E1F0(void);
void func_0023AC40(void);
void func_0017E0C0(int volume, int b);
void func_001D9350(IntroCamera *camera);
void func_00193940(void);
void func_0023C0D0(void);
void func_001D9490(IntroCamera *camera, int a);
void func_0017A530(void);
void func_003E7430(void);
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
        func_00161E10(g_005B49E0[0], g_00574DE0[0], g_005B4BC0[0]);
        g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
        func_0017AC50(g_005B4BC0[0]);
    } else {
        func_0017AA80(g_005B4BC0[0], 0);
        func_00161E10(g_005B49E0[0], g_00574DE0[0], g_005B4BC0[0]);
        g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
        func_0017AC50(g_005B4BC0[0]);
        func_0017AA80(g_005B4BC0[1], 1);
        func_00161E10(g_005B49E0[1], g_00574DE0[1], g_005B4BC0[1]);
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
            func_0036D150();
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
        func_001D9280(&g_00730480[0]);
        if (g_0073C790 == 0xB6) {
            if (func_00102960(0) == 0)
                func_00102960(1);
            g_00730480[g_0045D3E0].shot = NEXT_SHOT(g_0045D3E0);
            func_0023A2F0(0x1478, g_00730480[g_0045D3E0].shot, 1);
            func_00102960(1);
        } else {
            g_0073C79D = 1;
            g_0045D3E0 = 1;
            func_001D9280(&g_00730480[1]);
        }
    } else {
        func_0023AA40();
        func_0023B320();
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D91F0(&g_00730480[0], 1);
        if (g_0073C790 == 0xB6) {
            g_00730480[g_0045D3E0].shot = NEXT_SHOT(g_0045D3E0);
        } else {
            g_0073C79D = 1;
            g_0045D3E0 = 1;
            func_001D91F0(&g_00730480[1], 0);
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
    func_001D92E0(&g_00730480[0]);
    if (two) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D92E0(&g_00730480[1]);
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
    playing = func_001D93B0(&g_00730480[0], &step);
    if (g_0073C790 != 0xB6) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        playing = func_001D93B0(&g_00730480[1], &step);
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
    func_001D9350(&g_00730480[0]);
    if (g_0073C790 != 0xB6) {
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D9350(&g_00730480[1]);
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
        func_001D9490(&g_00730480[0], 0);
    } else {
        g_0073C79D = 0;
        g_0045D3E0 = 0;
        func_001D9490(&g_00730480[0], 1);
        g_0073C79D = 1;
        g_0045D3E0 = 1;
        func_001D9490(&g_00730480[1], 2);
    }
    func_0017A530();
    func_003E7430();
}

/* 0x001D6B40, 0x18 bytes, matching. Resets four battle counters. */
void func_001D6B40(void)
{
    g_0045D3C0 = 0;
    g_0045D3BC = 0;
    g_0045D3B4 = 1;
    g_0045D3B8 = 0;
}
