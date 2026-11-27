/*
 * scene_demo.c - scene 0x02, the demo (attract mode) (original source file StateDemo.c: the
 * scene's picture is loaded with that file name).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The demo cycles through three entries (g_0045CCBC, advanced when the scene is left): 0 plays a
 * movie or sound cue and goes back to the title, 1 and 2 set up a random battle (two random forces,
 * or for the first 60 demos one of the fixed pairings, on a stage taken in a shuffled order) and
 * start it as a demo battle (scene 4), with one or two armies.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

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

/* The game state (0x00669D60, see scene_config.c and scene_post_battle.c), the fields used here. */
extern struct {
    u8 unknown_0[0x50];
    u8 g_00669DB0;           /* flags; bit 4 saved and cleared during a demo */
    u8 unknown_51[0x7];
    int g_00669DB8;          /* 1 during a demo battle */
    u8 unknown_5C[0x204];
    u32 g_00669F60;          /* flags: bit 0 one army, bit 1 two armies, bit 4 demo */
    u8 unknown_204[0x8];
    int g_00669F6C;
} g_00669D60;
#define g_00669DB0 (g_00669D60.g_00669DB0)
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the bytes used here. */
extern struct {
    u8 unknown_0[0x457E];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* The game's random generator (see scene_shop.c). */
/* 0x7000015C: the random seed in the scratchpad (see main.c). */
#define g_7000015C (*(u32 *)0x7000015C)
#define random16() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 16) & 0xFFFF)

#define OFFICER_NONE 0x19F

/* Scene state, small data ($gp). */
extern u8 *g_0045CCB8;                    /* the demo picture (LINKDATA entry 8), 0 = not loaded */
extern u8 g_0045CCBC;                     /* demo entry 0-2 */
extern u8 g_0045CCBD;                     /* phase */
extern u8 g_0045CCBE;                     /* set when the scene is left */
extern u8 g_0045CCBF;                     /* bit 4 of g_00669DB0 before the demo */
extern u32 g_0045D320;                    /* demos played */

extern u8 g_006D3350[30];                 /* stages in a shuffled order */
extern u8 *g_005BA6A0;                    /* base records, 0x2C bytes (see scene_post_battle.c) */
extern u8 g_0073DCA3, g_0073DF33;         /* flag bytes of two records 0x290 bytes apart */
extern u8 g_00693970[], g_006939F8[];     /* two objects passed to func_001EE9C0 */
extern const char g_00425E80[];           /* "StateDemo.c" */

/* Data tables (0x004082B0-0x004084EF). Each pool is a list of officers for a force: its own
 * officers (slots 0-2 and 6) and generic ones (slots 3-5 and 7). */
typedef struct { u32 v[7]; } Pool7;
typedef struct { u32 v[11]; } Pool11;
typedef struct { u32 v[5]; } Pool5;
typedef struct { u32 v[4]; } Pool4;
typedef struct { u32 v[6]; } Pool6;
extern Pool7 g_004082B0;
extern Pool11 g_004082D0, g_00408320, g_00408360, g_004083B0, g_00408400;
extern Pool5 g_00408300;
extern Pool4 g_00408350;
extern Pool6 g_00408390, g_004083E0;
typedef int (*PoolPick)(int slot);
typedef struct { PoolPick pick[6]; } PoolTable;
extern PoolTable g_00408430;              /* the six force pools */
typedef struct { u32 officer[2][8]; } FixedSides;
extern FixedSides g_00408450;             /* the fixed pairing of the first demos */
typedef struct { u32 stage[24]; } StageList;
extern StageList g_00408490;              /* stages a random demo can use */

void func_00102EC0(u8 *data);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00118850(void *p, int size);
void func_003630C0(void);
void func_00362350(u32 stage);
int func_00363BC0(int officer);
void func_003620B0(int side, int slot, int officer);
void func_00362220(int side, int slot, int value);
void func_003621B0(int side, int slot, int value);
u32 func_003620E0(int side, int slot);
void func_003622F0(int side, int value);
void func_00362550(int value);
void func_00362590(int value);
int func_0036F180(u32 value);
int func_0036EFC0(void);
int func_0036F090(u32 value);
void func_003625D0(int side, int i, u32 value);
void func_00362BD0(int side, int slot, int value);
void func_00362CB0(int side, int value);
void func_00362C50(int side, int value);
void func_00362630(int side, int value);
void func_003627C0(int value);
void func_00362690(int a, int b, int c, int d);
int func_003637D0(int side, int slot);
void func_00362840(int side, int slot, int value);
int func_00362160(int side, int slot);
void func_00362990(int side, u16 value);
void func_00362AD0(int value);
void func_003638D0(void);
void func_0030CE90(int value);
u32 func_00362B60(int value);
void func_0036D230(u32 value);
u32 func_00363720(int value);
u32 func_003638A0(void);
void func_00101470(int value);
void func_001D42E0(void);
void func_001EE9C0(void *object, int value);
void func_002F15E0(u32 a, u32 b);
int func_00102960(int value);
int func_0017D8E0(int cue);
void func_00160020(int value);
void func_00278870(void);

/* 0x001BEAB0, 0x2C bytes. Puts back bit 4 of g_00669DB0 as it was before the demo. */
void func_001BEAB0(void)
{
    g_00669DB0 = (g_00669DB0 & 0xEF) | ((g_0045CCBF != 0) << 4);
}

/* 0x001BEAE0, 0x4C bytes. Loads the demo picture (LINKDATA entry 8) if not loaded. */
void func_001BEAE0(void)
{
    if (g_0045CCB8 == 0)
        g_0045CCB8 = func_001026D0(1, 8, 0, 1, 0, 0, g_00425E80, 0x59);
}

/* 0x001BEB30, 0x2C bytes. Frees the demo picture. */
void func_001BEB30(void)
{
    if (g_0045CCB8 != 0) {
        func_00102EC0(g_0045CCB8);
        g_0045CCB8 = 0;
    }
}

/* 0x001BEB60, 0x44 bytes. Draws the demo picture (240 x 136 at 260, 16). */
void func_001BEB60(void)
{
    if (g_0045CCB8 != 0)
        func_001ABA70(g_0045CCB8, 0x104, 0x10, 0, 0xF0, 0x88, 0x80, 7, 0);
}

/* 0x001BEBB0, 0xC bytes. Non-zero for the first 60 demos (fixed pairings, stages in order). */
int func_001BEBB0(void)
{
    return g_0045D320 < 60;
}

/* 0x001BEBC0, 0xDC bytes. An officer for `slot` from a force's pools: its own officers for
 * slots 0-2 and 6, generic ones for slots 3-5 and 7. */
u32 func_001BEBC0(const u32 *own, int own_count, const u32 *generic, int generic_count, int slot)
{
    int i;

    if (slot < 3 || slot == 6) {
        i = own_count == 0 ? 0 : (int)random16() % own_count;
        return own[i];
    }
    if (slot < 6 || slot == 7) {
        i = generic_count == 0 ? 0 : (int)random16() % generic_count;
        return generic[i];
    }
    return 0;
}

/* 0x001BECA0, 0x104 bytes. Force pool 0. */
int func_001BECA0(int slot)
{
    Pool7 own = g_004082B0;
    Pool11 generic = g_004082D0;

    return func_001BEBC0(own.v, 7, generic.v, 11, slot);
}

/* 0x001BEDB0, 0xEC bytes. Force pool 1. */
int func_001BEDB0(int slot)
{
    Pool5 own = g_00408300;
    Pool11 generic = g_00408320;

    return func_001BEBC0(own.v, 5, generic.v, 11, slot);
}

/* 0x001BEEA0, 0xE0 bytes. Force pool 2. */
int func_001BEEA0(int slot)
{
    Pool4 own = g_00408350;
    Pool11 generic = g_00408360;

    return func_001BEBC0(own.v, 4, generic.v, 11, slot);
}

/* 0x001BEF80, 0xF8 bytes. Force pool 3. */
int func_001BEF80(int slot)
{
    Pool6 own = g_00408390;
    Pool11 generic = g_004083B0;

    return func_001BEBC0(own.v, 6, generic.v, 11, slot);
}

/* 0x001BF080, 0xF8 bytes. Force pool 4. */
int func_001BF080(int slot)
{
    Pool6 own = g_004083E0;
    Pool11 generic = g_00408400;

    return func_001BEBC0(own.v, 6, generic.v, 11, slot);
}

/* 0x001BF180, 0xB0 bytes. Force pool 5: any of the 28 unique officers (slots 0-2 and 6), or any
 * generic one (0x1C-0x18F). */
int func_001BF180(int slot)
{
    if (slot < 3 || slot == 6)
        return random16() % 0x1C;
    if (slot < 6 || slot == 7)
        return random16() % 0x174 + 0x1C;
    return 0;
}

/* 0x001BF230, 0x88 bytes. An officer for `slot` from force pool `force` (0-5, else 0). */
int func_001BF230(int force, int slot)
{
    PoolTable table = g_00408430;

    if (force < 0 || force >= 6)
        force = 0;
    return table.pick[force](slot);
}

/* 0x001BF2C0, 0x80 bytes. The officer of `slot` on `side` in the fixed pairing (0 out of range). */
u32 func_001BF2C0(int side, int slot)
{
    FixedSides fixed = g_00408450;

    if (side < 0 || side > 1 || slot < 0 || slot > 7)
        return 0;
    return fixed.officer[side][slot];
}

/* 0x001BF340, 0x17C bytes. Shuffles the 30 stages of g_006D3350: a rotation by a random start,
 * then 100 random swaps. */
void func_001BF340(void)
{
    u32 i, start;

    func_00118850(g_006D3350, 30);
    start = random16() % 30;
    for (i = 0; i < 30; i++)
        g_006D3350[i] = (u8)((start + i) % 30);
    for (i = 0; i < 100; i++) {
        u32 a = random16() % 30;
        u32 b = random16() % 30;
        if (a != b) {
            u8 t = g_006D3350[a];
            g_006D3350[a] = g_006D3350[b];
            g_006D3350[b] = t;
        }
    }
}

/* 0x001BF4C0, 0xC4 bytes. The demo's stage: random among g_00408490, or for the first 60 demos
 * the shuffled list read from both ends in turn. */
u32 func_001BF4C0(void)
{
    StageList list = g_00408490;
    u32 i;

    if (func_001BEBB0() == 0)
        return list.stage[random16() % 24];
    i = g_0045D320 >> 1;
    if ((g_0045D320 & 1) == 1)
        i = 29 - i;
    return g_006D3350[i];
}

/* 0x001BF590, 0x50 bytes. Stages 3, 6, 0x0D, 0x14 and 0x1C use the fixed pairing. */
int func_001BF590(u32 stage)
{
    switch (stage) {
    case 3:
    case 0x0D:
    case 0x14:
    case 0x1C:
    case 6:
        return 1;
    }
    return 0;
}

/* 0x001BF5E0, 0x7C8 bytes. Sets up the demo battle: the stage, two different random forces (the
 * "any officer" pool always second), their officers with random values, the weather or time of day
 * (one army: 20 % chance of mode 6), random formations, morale, items and flags. */
void func_001BF5E0(int two_armies)
{
    u32 stage, side, slot, i, weather = 0;
    int fixed = 0, mode;
    u32 forces[2];
    u32 pairs[2][2];
    u32 flags[4];

    func_003630C0();
    stage = func_001BF4C0();
    func_00362350(stage);
    if (func_001BEBB0() != 0 && func_001BF590(stage) != 0)
        fixed = 1;
    forces[0] = random16() % 6;
    do
        forces[1] = random16() % 6;
    while (forces[1] == forces[0]);
    if (forces[0] == 5 && forces[1] != 5) {
        forces[0] = forces[1];
        forces[1] = 5;
    }

    for (side = 0; side < 2; side++) {
        for (slot = 0; slot < 8;) {
            int officer = OFFICER_NONE;

            if (fixed)
                officer = func_001BF2C0(side, slot);
            else if (slot < 6)
                officer = func_001BF230(forces[side], slot);
            if (officer >= 0 && officer < OFFICER_NONE) {
                if (func_00363BC0(officer) != 0)
                    continue;                   /* already used: draw again */
                func_003620B0(side, slot, officer);
                func_00362220(side, slot, random16() % 9001 + 1000);
                func_003621B0(side, slot, 10000);
            }
            slot++;
        }
    }

    if (two_armies == 0) {
        func_003620E0(0, 6);
        if (func_003620E0(0, 6) < OFFICER_NONE && random16() % 100 < 20)
            weather = 6;
    }
    func_003622F0(0, weather);
    if (two_armies != 0)
        func_003622F0(1, 1);
    if ((random16() & 1) == 0) {
        if (weather < 6 || weather > 7)
            mode = random16() % 100 < 50 ? 0 : 2;
        else
            mode = random16() % 100 < 50 ? 1 : 3;
    } else if (weather < 6 || weather > 7) {
        mode = 4;
    } else {
        mode = 5;
    }
    func_00362550(mode);
    func_00362590(0);

    for (side = 0; side < 2; side++) {
        u32 *p = pairs[side];

        p[0] = random16() % 31;
        p[1] = random16() % 31;
        if (func_0036F180(p[0]) == 2 && func_0036F180(p[1]) == 2)
            p[1] = 31;
        if (p[0] == p[1] && func_0036EFC0() == 0)
            p[1] = 31;
        for (i = 0; i < 2; i++)
            if (func_0036F090(p[i]) != 0)
                p[i] = 31;
        if (fixed) {
            pairs[0][0] = 0x12;
            pairs[0][1] = 0x1F;
            pairs[1][0] = 0x10;
            pairs[1][1] = 0x1F;
        }
        for (i = 0; i < 2; i++)
            func_003625D0(side, i, p[i]);
    }

    for (side = 0; side < 2; side++) {
        for (slot = 0; slot < 5; slot++) {
            func_00362BD0(side, slot, random16() % 9 + 1);
            if (random16() % 100 < 20)
                break;
        }
        func_00362BD0(side, slot, 0);
        func_00362CB0(side, random16() % 91 + 90);
        func_00362C50(side, slot + 1 == 0 ? 0 : (int)(random16() % (slot + 1)));
    }
    for (side = 0; side < 2; side++)
        func_00362630(side, random16() % 11);
    func_003627C0(1);
    for (i = 0; i < 4; i++)
        flags[i] = random16() % 100 < 50;
    if (weather > 5 && weather < 8)
        flags[0] = 1;
    func_00362690(flags[0], flags[1], flags[2], flags[3]);

    for (side = 0; side < 2; side++) {
        for (slot = 0; slot < 8; slot++) {
            if (slot != 0 && func_003637D0(side, slot) == 0 && random16() % 100 < 3) {
                func_00362840(side, slot, 1);
                break;
            }
        }
    }
    for (side = 0; side < 2; side++)
        func_00362990(side, *(u16 *)(g_005BA6A0 + func_00362160(side, 0) * 0x2C));
    func_00362AD0(0);
}

/* 0x001BFDB0, 0x1A0 bytes. Starts a demo battle with one army (0) or two (1): sets it up, marks
 * the game state as a demo, saves and clears bit 4 of g_00669DB0, and starts the loading. */
void func_001BFDB0(int two_armies)
{
    u32 a, b;
    u8 flags;

    if (g_0045D320 == 0)
        func_001BF340();
    g_00669F60 |= 0x10;
    func_001BF5E0(two_armies);
    func_003638D0();
    func_0030CE90(10);
    func_0036D230(func_00362B60(0));
    a = func_00363720(0);
    b = func_003638A0();
    g_00669DB8 = 1;
    if (two_armies == 0)
        g_00669F60 = (g_00669F60 & ~2u) | 1;
    else
        g_00669F60 = (g_00669F60 & ~1u) | 2;
    g_00669F6C = 0;
    func_00101470(1);
    func_001D42E0();
    g_0073DCA3 = (g_0073DCA3 & 0xFB) | 4;
    flags = g_00669DB0;
    g_0073DF33 = (g_0073DF33 & 0xFB) | 4;
    g_00669DB0 &= 0xEF;
    g_0045CCBF = (flags & 0x10) != 0;
    func_001EE9C0(g_00693970, 0);
    func_001EE9C0(g_006939F8, 0);
    func_002F15E0(a, b);
    func_00102960(0);
    g_0045D320++;
}

/* 0x001BFF50, 0x4C bytes. Plays the first of the movies or cues 0x48, 0x4A and 0x47 that
 * starts (func_0017D8E0 non-zero); returns that result. */
int func_001BFF50(void)
{
    int r;

    if ((r = func_0017D8E0(0x48)) != 0)
        return r;
    if ((r = func_0017D8E0(0x4A)) != 0)
        return r;
    return func_0017D8E0(0x47);
}

/* 0x001BFFA0, 0x8 bytes. Scene 0x02 enter (not found by Ghidra). */
void func_001BFFA0(void)
{
    g_0045CCBD = 0;
}

/* 0x001BFFB0, 0x24 bytes. Scene 0x02 leave (not found by Ghidra): the next demo entry. */
void func_001BFFB0(void)
{
    g_0045CCBE = 1;
    g_0045CCBC = (u8)((g_0045CCBC + 1) % 3);
}

/* 0x001BFFE0, 0x24C bytes. Scene 0x02 update: waits for message box 1, starts the demo entry
 * (0: a movie or cue, then the title; 1 / 2: a demo battle, scene 4), then once box 1 is closed
 * calls func_00278870 (SceneTitle.c) and leaves. */
int func_001BFFE0(void)
{
    if (g_0045CCBD != 2) {
        if (g_0045CCBD == 1) {
            if (g_0045CCBC == 0) {
                if (func_001BFF50() > 0)
                    func_00160020(0);
                else
                    func_00160020(1);
                if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
                    g_0045D89C = 1;
                g_0045CCBD = 2;
            } else if (g_0045CCBC == 2) {
                func_001BEAE0();
                func_001BFDB0(1);
                if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
                    g_0045D89C = 4;
                g_0045CCBD = 2;
            } else if (g_0045CCBC == 1) {
                func_001BEAE0();
                func_001BFDB0(0);
                if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
                    g_0045D89C = 4;
                g_0045CCBD = 2;
            }
        } else if (g_0045CCBD == 0) {
            if (!box1_open())
                g_0045CCBD = 1;
            return 1;
        } else {
            return 1;
        }
    }
    if (!box1_open()) {
        func_00278870();
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D8A0;
            g_0045D89C = 0x18;
        } else {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D89C;
            g_0045D89C = g_0045D8A0;
        }
    }
    return 1;
}

/* 0x001C0230, 0x8 bytes. Scene 0x02 step: empty. */
void func_001C0230(void)
{
}

/* 0x001C0240, 0x8 bytes. Scene 0x02 draw: empty. */
void func_001C0240(void)
{
}
