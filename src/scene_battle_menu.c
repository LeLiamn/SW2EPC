/*
 * scene_battle_menu.c - scene 0x08, the menu opened during a battle (probable: it fades in when
 * coming from the battle, scene 5). Original source file unknown (no name string is used in
 * it). Only the scene's own functions and the small handlers just before them
 * (0x00235870-0x00236C44) are decompiled; its pages 0x0022F000?-0x00235870 are not.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The scene shows one of 19 pages (g_0074B724, 0-0x12) for player g_0074B734, over the battle
 * map; func_002300B0 changes page. Like the pre-battle menu (scene_pre_battle.c) it sets the
 * menu camera up from the battle type. The update runs in phases (g_0074B72C): 0 opening, 1 the
 * page's handler, 2-4 leaving (func_00230160).
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

/* The game state (0x00669D60), the fields used here (see scene_pre_battle.c). */
extern struct {
    u8 unknown_0[0x58];
    int g_00669DB8;          /* game mode */
    u8 unknown_5c[0x4];
    int g_00669DC0[5];       /* stage */
    int g_00669DD4[5];       /* battle type of the stage */
    u8 unknown_e8[0x178];
    u32 g_00669F60;          /* flags (bit 1: two armies) */
    u8 unknown_204[0x8];
    int g_00669F6C;          /* 1: an Empire battle */
    u8 unknown_210[0x28];
    int g_00669F98;          /* battle number in mode 2 */
} g_00669D60;
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669DC0 (g_00669D60.g_00669DC0)
#define g_00669DD4 (g_00669D60.g_00669DD4)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)
#define g_00669F98 (g_00669D60.g_00669F98)
#define BATTLE_TYPE()  (g_00669DB8 == 2 ? g_00669DD4[g_00669F98 % 5] : g_00669DD4[0])

/* The message boxes' object (0x0068F3E0, see scene_shop.c). */
extern struct {
    u8 unknown_0[0x40D3];
    u8 g_006934B3;           /* box 0 state */
    u8 unknown_40d4[0x127];
    u8 g_006935DB;           /* box 1 state */
    u8 g_006935DC;           /* box 1 answer (4 = yes) */
    u8 unknown_41fd[0x381];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_006934B3 (s_0068F3E0.g_006934B3)
#define g_006935DB (s_0068F3E0.g_006935DB)
#define g_006935DC (s_0068F3E0.g_006935DC)
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* The menu camera (0x007A1B70, see scene_pre_battle.c). */
extern struct {
    float g_007A1B70[4];     /* target */
    float g_007A1B80[4];     /* target to reach */
    u8 unknown_20[0x14];
    u32 g_007A1BA4;
    u32 g_007A1BA8;          /* frames to reach it */
    u8 unknown_3c[0x14];
    u8 g_007A1BC0[0x50];     /* the camera */
    float g_007A1C10, g_007A1C14;        /* distance range */
    float g_007A1C18, g_007A1C1C;        /* distance range to reach */
    u32 g_007A1C20;
    u32 g_007A1C24;          /* frames to reach it */
} s_007A1B70;
#define g_007A1B70 (s_007A1B70.g_007A1B70)
#define g_007A1B80 (s_007A1B70.g_007A1B80)
#define g_007A1BA4 (s_007A1B70.g_007A1BA4)
#define g_007A1BA8 (s_007A1B70.g_007A1BA8)
#define g_007A1BC0 (s_007A1B70.g_007A1BC0)
#define g_007A1C10 (s_007A1B70.g_007A1C10)
#define g_007A1C14 (s_007A1B70.g_007A1C14)
#define g_007A1C18 (s_007A1B70.g_007A1C18)
#define g_007A1C1C (s_007A1B70.g_007A1C1C)
#define g_007A1C20 (s_007A1B70.g_007A1C20)
#define g_007A1C24 (s_007A1B70.g_007A1C24)

/* Tables of the battle types (see scene_pre_battle.c). */
extern u8 g_00442EA0[][0x10];              /* camera directions per battle type */
extern float g_00443290[][4];              /* camera targets per battle type */
extern struct { float a, b, c; } g_00443530[];   /* camera distances per battle type */
extern struct { float a, b; } g_00443630[];  /* distance ranges per battle type */

/* The text table at 0x0043C32C (see scene_config.c): help lines and messages. */
extern const char *g_0043C32C[];
#define TEXT(addr) (g_0043C32C[((addr) - 0x0043C32C) / 4])

/* The menu's state (0x0074B71C-0x0074B7CF). */
extern struct {
    u8 g_0074B71C[8];        /* page 5's state */
    int g_0074B724;          /* page (0-0x12) */
    int g_0074B728;
    int g_0074B72C;          /* phase: 0 opening, 1 in use, 2-4 leaving */
    int g_0074B730;          /* page 0x12's step */
    int g_0074B734;          /* player */
    u8 g_0074B738[0xE];      /* the map frame (func_0028F860) */
    u8 g_0074B746;
    u8 g_0074B747;
    u8 page0[3];             /* 0x0074B748 page 0's state */
    u8 unknown_4b[5];
    int g_0074B750;          /* the camera is moving */
    int g_0074B754;          /* a dialog of func_002DAC30 is open */
    int g_0074B758;
    int g_0074B75C;
    u8 page3[0x5C];          /* 0x0074B760 page 3's state: +0 column, +1 row, +4 mode, +0x58 sub-page */
    u8 g_0074B7BC[4];        /* page 9's state */
    u8 g_0074B7C0[8];        /* page 10's state */
    u8 g_0074B7C8;           /* page 12's value */
    u8 g_0074B7C9;           /* page 16's value */
    u8 unknown_ae[2];
    int g_0074B7CC;          /* page 17's step */
} s_0074B71C;
#define g_0074B71C (s_0074B71C.g_0074B71C)
#define g_0074B724 (s_0074B71C.g_0074B724)
#define g_0074B728 (s_0074B71C.g_0074B728)
#define g_0074B72C (s_0074B71C.g_0074B72C)
#define g_0074B730 (s_0074B71C.g_0074B730)
#define g_0074B734 (s_0074B71C.g_0074B734)
#define g_0074B738 (s_0074B71C.g_0074B738)
#define g_0074B746 (s_0074B71C.g_0074B746)
#define g_0074B747 (s_0074B71C.g_0074B747)
#define g_0074B748 (s_0074B71C.page0)
#define g_0074B749 (s_0074B71C.page0[1])
#define g_0074B74A (s_0074B71C.page0[2])
#define g_0074B750 (s_0074B71C.g_0074B750)
#define g_0074B754 (s_0074B71C.g_0074B754)
#define g_0074B758 (s_0074B71C.g_0074B758)
#define g_0074B75C (s_0074B71C.g_0074B75C)
#define g_0074B760 (s_0074B71C.page3)
#define g_0074B761 (s_0074B71C.page3[1])
#define g_0074B764 (s_0074B71C.page3[4])
#define g_0074B7B8 (s_0074B71C.page3[0x58])
#define g_0074B7BC (s_0074B71C.g_0074B7BC)
#define g_0074B7C0 (s_0074B71C.g_0074B7C0)
#define g_0074B7C8 (s_0074B71C.g_0074B7C8)
#define g_0074B7C9 (s_0074B71C.g_0074B7C9)
#define g_0074B7CC (s_0074B71C.g_0074B7CC)

extern u8 g_0074B260[];                   /* the battle map */
extern u8 g_0074B420[];                   /* the map's grid (func_0028EFC0) */
extern u8 *g_0074B5A0[][30];              /* in it: the unit of each cell (column, row) */

/* The shop's / page state used on leaving (see scene_shop.c). */
extern struct {
    u8 unknown_0[0x1DC];
    u16 g_007725CC;
    u16 g_007725CE;
    int g_007725D0;
    int g_007725D4;
    u8 unknown_1e8[0x1C];
    int g_007725F4;          /* set while the menu opens */
} s_007723F0;
#define g_007725CC (s_007723F0.g_007725CC)
#define g_007725CE (s_007723F0.g_007725CE)
#define g_007725D0 (s_007723F0.g_007725D0)
#define g_007725D4 (s_007723F0.g_007725D4)
#define g_007725F4 (s_007723F0.g_007725F4)

extern int g_0045D2C0, g_0045D4C0;        /* (small data) */

int func_0036D2E0(void);
void func_002DB990(int a);
int func_002DB9F0(void);
void func_002300B0(int page);
void func_001204B0(char *to, const char *from);
void func_001AE9F0(int box, const char *text, ...);
void func_001AFC70(int box, int a);
void func_001B8D10(void);
void func_0023B3C0(int a, int b);
void func_00118850(void *to, int size);
void func_00231920(void);
void func_00231040(void);
void func_0028EFC0(u8 *grid);
void func_00230090(void);
void func_0028F4C0(u8 *map);
void func_0028F860(u8 *frame);
void func_002EBE40(void);
void func_002EBD80(float distance, u8 *camera, const void *direction);
void func_002EBAA0(float distance, u8 *camera, const void *direction, int frames);
void func_002C59F0(void);
void func_002C5A30(void);
void func_002C5A60(void);
void func_0027FE60(int a);
void func_003F1580(void);
void func_003E3D70(void);
void func_00376100(int a, int b, int c);
void func_001B8F60(int a, int b, int c);
void func_00376450(void);
int func_002DAC30(void);
void func_002D8160(void);
int func_0017DDA0(void);
void func_00230160(void);
int func_003F1400(int a);
void func_00231180(void);
int func_00231930(int a);
int func_00231220(int a);
void func_00231DA0(int player);
void func_00232150(int player);
void func_00233E20(int player);
void func_00233E80(int player);
void func_002341E0(int player);
void func_00233F80(int player);
void func_00231ED0(int player);
void func_002344F0(int player);
void func_002348B0(int player);
void func_00234B70(int player);
void func_00234E10(int player);
void func_00234F60(int player);
void func_00235360(int player);
void func_00235460(int player);
void func_00234430(int player);
void func_002355B0(int player);
void func_002EC0A0(void);
void func_00280F30(void);
u64 *func_001050F0(void);
void func_00105390(u64 *packet);
u64 *func_00105410(void);
void func_00105560(u64 *packet);
void func_003F11D0(void);
int func_002ECA70(void);
int func_002EC150(void);
void func_00195C20(void);
void func_001FCC50(void);
void func_00292A90(u8 *grid);
void func_002937E0(u8 *frame, u8 *map);
void func_001FCC90(void);
void func_002944D0(void);
void func_00282020(u8 *state, u8 *frame, u8 *grid, int *value);
void func_00282A80(int player);
void func_00283F70(u8 *map, u8 *frame, int a);
void func_00283FA0(int player, u8 *grid, u8 *page);
void func_00284950(u8 *page);
void func_00283CC0(int player);
void func_00284A10(int a);
void func_002DAE50(void);
void func_00283600(int player, int a);
void func_00284B60(int player, u8 *grid, u8 *page);
void func_00284D40(int player, u8 *grid, u8 *page);
void func_00284EF0(void);
void func_00284F00(int player, int value);
void func_00285000(int player);
void func_00285010(void);
void func_00285590(void);
void func_00285610(int value);
void func_00285680(void);
void func_002856A0(void);
void func_00281D20(int page, int player);
void func_003765C0(void);
int func_003F1160(int a);
void func_001A7DC0(const char *text, int alpha, int a);
u8 **func_0034A740(void);
int func_0033BD60(u8 **a);
u32 func_0036F1E0(int a, int b);
int func_003725A0(int a);
void func_003838B0(int a, int b);
u32 func_00362D70(int side);
void func_001D2B60(void);
void func_001D4150(void);

/* 0x00235870, 0xC bytes, matching. Page 17 set-up. */
void func_00235870(void)
{
    g_0074B7CC = 0;
}

/* 0x00235880, 0x48 bytes, matching. Page 17, step 0: opens dialog 4 (7 in an Empire battle). */
void func_00235880(void)
{
    if (func_0036D2E0() != 0)
        func_002DB990(7);
    else
        func_002DB990(4);
    g_0074B7CC = 1;
}

/* 0x002358D0, 0x30 bytes, matching. Page 17, step 1: waits for the dialog. */
void func_002358D0(void)
{
    if (func_002DB9F0() != 0)
        g_0074B7CC = 2;
}

/* 0x00235900, 0x1C bytes, matching. Page 17, step 2: back to page 16. */
void func_00235900(void)
{
    func_002300B0(0x10);
}

/* 0x00235920, 0x6C bytes. Page 17. */
void func_00235920(int player)
{
    if (g_0074B7CC == 2)
        func_00235900();
    else if (g_0074B7CC == 1)
        func_002358D0();
    else if (g_0074B7CC == 0)
        func_00235880();
}

/* 0x00235990, 0x74 bytes. Page 18 set-up: asks "Exiting game. Proceed?" (the default answer
 * follows the player). */
void func_00235990(void)
{
    char text[256];
    int second = g_0074B734 == 1;

    func_001204B0(text, TEXT(0x0043C344));
    func_001AE9F0(1, text, 1);
    func_001AFC70(1, second);
    g_0074B730 = 2;
}

/* 0x00235A10, 0x54 bytes, matching. Page 18: back to page 16 once the box is closed, page 21 on yes. */
void func_00235A10(int player)
{
    if (g_006935DB != 0) {
        if (g_006935DC == 4) {
            func_002300B0(0x15);
            g_0074B730 = 0;
        }
    } else {
        func_002300B0(0x10);
    }
}

/* 0x00235A70, 0x4F4 bytes. Scene 0x08 enter. */
void func_00235A70(void)
{
    g_0074B734 = 0;
    g_0074B748[0] = 0;
    g_0074B749 = 0;
    g_0074B74A = 0;
    func_001B8D10();
    if (g_00669F6C != 1)
        func_0023B3C0(0, 0);
    func_00118850(g_0074B760, 0x5C);
    func_00118850(g_0074B7BC, 4);
    g_0074B7C8 = 0;
    g_0074B7C9 = 0;
    g_0074B746 = 0x10;
    func_002300B0(0);
    if (g_00669F6C == 1)
        func_00231920();
    else
        func_00231040();
    func_0028EFC0(g_0074B420);
    func_00230090();
    func_0028F4C0(g_0074B260);
    func_0028F860(g_0074B738);
    g_0074B750 = 0;
    func_002EBE40();
    g_007A1C14 = g_00443630[BATTLE_TYPE()].b;
    g_007A1C20 = 0;
    g_007A1C10 = g_00443630[BATTLE_TYPE()].a;
    g_007A1C1C = g_00443630[BATTLE_TYPE()].b;
    g_007A1C24 = 0;
    g_007A1C18 = g_00443630[BATTLE_TYPE()].a;
    {
        int type = BATTLE_TYPE();

        g_007A1BA4 = 0;
        g_007A1BA8 = 0;
        g_007A1B70[0] = g_00443290[type][0];
        g_007A1B70[1] = g_00443290[type][1];
        g_007A1B70[2] = g_00443290[type][2];
        g_007A1B70[3] = g_00443290[type][3];
    }
    g_007A1B80[0] = g_007A1B70[0];
    g_007A1B80[1] = g_007A1B70[1];
    g_007A1B80[2] = g_007A1B70[2];
    g_007A1B80[3] = g_007A1B70[3];
    func_002EBD80(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()]);
    func_002EBAA0(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()], 0);
    g_0074B730 = 0;
    func_002C59F0();
    func_002C5A30();
    func_002C5A60();
    g_0074B758 = 0;
    g_0074B75C = 0;
    g_0074B724 = 0;
    g_0074B728 = 0;
    g_0074B72C = 0;
    func_0027FE60(0);
    g_007725F4 = 1;
    func_003F1580();
    func_003E3D70();
    func_00376100(0, -1, -1);
    if (g_0045D894 == 5)
        func_001B8F60(1, 6, 0x80);
}

/* 0x00235F70, 0x44 bytes, matching. Scene 0x08 leave. */
void func_00235F70(void)
{
    g_0045D2C0 = g_0045D4C0;
    g_00669F60 &= ~0x20000;
    func_0023B3C0(1, 0);
}

/* 0x00235FC0, 0x470 bytes. Scene 0x08 update. */
int func_00235FC0(void)
{
    int r;

    func_00376450();
    if (g_0074B754 != 0) {
        r = func_002DAC30();
        if (r == 2 || r == 1) {
            g_0074B754 = 0;
            func_002D8160();
        }
        return 1;
    }
    if (g_006934B3 == 1 || g_006934B3 == 8)
        return 1;
    switch (g_0074B72C) {
    case 0:
        if (g_0074B724 == 0)
            func_00231180();
        g_0074B72C = 1;
        return 1;
    case 2:
        if (g_007725F4 == 0)
            func_00230160();
        return 1;
    case 3:
        if (!box1_open()) {
            g_0074B72C = 0;
            func_00230160();
        }
        return 1;
    case 4:
        if (!box1_open()) {
            if (g_00669F6C == 1) {
                if (func_0017DDA0() == 0)
                    func_00230160();
            } else {
                func_00230160();
            }
        }
        return 0;
    case 1:
    default:
        r = func_003F1400(g_0074B734 == 1);
        if (r != 0) {
            if (r == 2) {
                g_007725D0 = 1;
                g_007725D4 = 0;
                g_007725CC = g_007725CE;
                func_00231180();
            }
            return 1;
        }
        switch (g_0074B724) {
        case 0:
            if (g_00669F6C == 1) {
                if (func_00231930(0) == 0 && (g_00669F60 & 2) != 0) {
                    func_00231930(1);
                    return 1;
                }
            } else if (func_00231220(0) == 0 && (g_00669F60 & 2) != 0) {
                func_00231220(1);
            }
            break;
        case 1:
            func_00231DA0(g_0074B734);
            break;
        case 2:
            func_00232150(g_0074B734);
            break;
        case 3:
            func_00233E20(g_0074B734);
            break;
        case 4:
            func_00233E80(g_0074B734);
            break;
        case 5:
            func_002341E0(g_0074B734);
            break;
        case 6:
            func_00233F80(g_0074B734);
            break;
        case 7:
            func_00231ED0(g_0074B734);
            break;
        case 8:
            func_002344F0(g_0074B734);
            break;
        case 9:
            func_002348B0(g_0074B734);
            break;
        case 10:
            func_00234B70(g_0074B734);
            break;
        case 11:
            func_00234E10(g_0074B734);
            break;
        case 12:
            func_00234F60(g_0074B734);
            break;
        case 13:
            func_00235360(g_0074B734);
            break;
        case 14:
            func_00235460(g_0074B734);
            break;
        case 15:
            func_00234430(g_0074B734);
            break;
        case 16:
            func_002355B0(g_0074B734);
            break;
        case 17:
            func_00235920(g_0074B734);
            break;
        case 18:
            func_00235A10(g_0074B734);
            break;
        }
        return 1;
    }
}

/* 0x00236430, 0x1C bytes, matching. Scene 0x08 step. */
void func_00236430(void)
{
    func_002EC0A0();
}

/* 0x00236450, 0x7C4 bytes. Scene 0x08 draw: GS settings, the map (not in mode 2), the page's
 * drawer, then its help line. */
void func_00236450(void)
{
    u64 *packet;

    func_00280F30();
    packet = func_001050F0();
    packet[2] = 0x32001;
    packet[3] = 0x48;
    func_00105390(packet);
    packet = func_00105410();
    packet[4] = 0x79007000;
    packet[5] = 0x87009000;
    packet[3] = 0x3F80000080808080ULL;
    func_00105560(packet);
    packet = func_001050F0();
    packet[2] = 0x5000D;
    packet[3] = 0x48;
    func_00105390(packet);
    func_003F11D0();
    if (g_00669DB8 != 2) {
        if (g_00669DB8 != 2) {
            if (g_0074B750 != 0) {
                g_0074B750 = func_002ECA70();
                g_0074B750 = func_002EC150() != 0 || g_0074B750 != 0;
            }
            func_00195C20();
        }
        func_001FCC50();
        func_00292A90(g_0074B420);
        func_002937E0(g_0074B738, g_0074B260);
        func_001FCC90();
        func_002944D0();
    }
    func_00376450();
    switch (g_0074B724) {
    case 0:
        func_00282020(g_0074B748, g_0074B738, g_0074B420, &g_0074B758);
        break;
    case 1:
        func_00282A80(g_0074B734);
        break;
    case 2:
        func_00283F70(g_0074B260, g_0074B738, 0);
        break;
    case 3:
        func_00283FA0(g_0074B734, g_0074B420, g_0074B760);
        break;
    case 5:
        func_00284950(g_0074B71C);
        break;
    case 6:
        func_00283CC0(g_0074B734);
        break;
    case 7:
        func_00284A10(g_0074B747);
        func_002DAE50();
        break;
    case 8:
        func_00283600(g_0074B734, g_0074B747);
        break;
    case 9:
        func_00284B60(g_0074B734, g_0074B420, g_0074B7BC);
        break;
    case 10:
        func_00284D40(g_0074B734, g_0074B420, g_0074B7C0);
        break;
    case 11:
        func_00284EF0();
        break;
    case 12:
        func_00284F00(g_0074B734, g_0074B7C8);
        break;
    case 13:
        func_00285000(g_0074B734);
        break;
    case 14:
        func_00285010();
        break;
    case 15:
        func_00285590();
        break;
    case 16:
        func_00285610(g_0074B7C9);
        break;
    case 17:
        func_00285680();
        break;
    case 18:
        func_002856A0();
        break;
    }
    func_00281D20(g_0074B724, g_0074B734);
    func_003765C0();
    if (func_003F1160(1) != 0)
        return;
    switch (g_0074B724) {
    case 0:
        if (g_00669F6C == 1) {
            func_001A7DC0(TEXT(0x0043C838), 0x80, 0);
            return;
        }
        func_001A7DC0(TEXT(0x0043C5A4), 0x80, 0);
        break;
    case 1:
        func_001A7DC0(TEXT(0x0043C5DC), 0x80, 0);
        break;
    case 2:
        func_001A7DC0(TEXT(0x0043C5CC), 0x80, 0);
        break;
    case 3:
        if (g_0074B7B8 == 3) {
            func_001A7DC0(TEXT(0x0043C6F8), 0x80, 0);
        } else if (g_0074B7B8 == 2) {
            func_001A7DC0(TEXT(0x0043C720), 0x80, 0);
        } else if (g_0074B7B8 == 1) {
            func_001A7DC0(TEXT(0x0043C79C), 0x80, 0);
        } else if (g_0074B7B8 == 0) {
            u8 *unit = g_0074B5A0[g_0074B760[0]][g_0074B761];

            if (unit == 0)
                break;
            if ((*(u32 *)(unit + 0x80) & 0x30) != 0) {
                func_001A7DC0(TEXT(0x0043C6F4), 0x80, 0);
            } else if (unit[0x79] == 0 && g_00669F6C != 1) {
                if (func_0033BD60(func_0034A740()) == 0)
                    func_001A7DC0(TEXT(0x0043C6F0), 0x80, 0);
                else if (g_0074B764 == 1)
                    func_001A7DC0(TEXT(0x0043C84C), 0x80, 0);
                else
                    func_001A7DC0(TEXT(0x0043C848), 0x80, 0);
            } else {
                if (func_0033BD60(func_0034A740()) == 0)
                    func_001A7DC0(TEXT(0x0043C6F4), 0x80, 0);
                else if (g_0074B764 == 1)
                    func_001A7DC0(TEXT(0x0043C854), 0x80, 0);
                else
                    func_001A7DC0(TEXT(0x0043C850), 0x80, 0);
            }
        }
        break;
    case 4:
        func_001A7DC0(TEXT(0x0043C5D0), 0x80, 0);
        break;
    case 5:
        func_001A7DC0(TEXT(0x0043C5E8), 0x80, 0);
        break;
    case 6:
        func_001A7DC0(TEXT(0x0043C5D4), 0x80, 0);
        break;
    case 7:
        func_001A7DC0(TEXT(0x0043C5A8), 0x80, 0);
        break;
    case 8:
        func_001A7DC0(TEXT(0x0043C5E0), 0x80, 0);
        break;
    case 9:
        if (func_0036F1E0(0, 0) < 2)
            func_001A7DC0(TEXT(0x0043C560), 0x80, 0);
        else
            func_001A7DC0(TEXT(0x0043C724), 0x80, 0);
        break;
    case 10:
        func_003838B0(func_003725A0(0x62), 0);
        if (func_00362D70(0) < 2)
            func_001A7DC0(TEXT(0x0043C560), 0x80, 0);
        else
            func_001A7DC0(TEXT(0x0043C72C), 0x80, 0);
        break;
    case 12:
        func_001A7DC0(TEXT(0x0043C72C), 0x80, 0);
        break;
    case 15:
        func_001A7DC0(TEXT(0x0043C55C), 0x80, 0);
        break;
    case 16:
        func_001A7DC0(TEXT(0x0043C730), 0x80, 0);
        break;
    }
}

/* 0x00236C20, 0x24 bytes, matching. Scene 0x08 on reset. */
void func_00236C20(void)
{
    func_001D2B60();
    func_001D4150();
}
