/*
 * scene_battle_menu.c - scene 0x08, the menu opened during a battle (probable: it fades in when
 * coming from the battle, scene 5). Original source file unknown (no name string is used in
 * it). The whole file is decompiled: 0x0022FF30 (probable start: the code before it belongs to
 * the message window, 0x005BBF18) to 0x00236C44.
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

/* Flag bytes the original tests as one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;
typedef struct {
    unsigned char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} UBits8;

#define SBIT(lv, n) (((Bits8 *)&(lv))->f##n)
#define UBIT(lv, n) (((UBits8 *)&(lv))->f##n)
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
    u8 g_006934B4;           /* box 0 answer */
    u8 unknown_40d5[0x126];
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
    u32 g_007A1C28;          /* camera mode */
    u8 unknown_bc[0x1C4];
    float g_007A1DF0[4];     /* default eye */
    float g_007A1E00[4];     /* default target */
    u8 unknown_2a0[0x20];
    float g_007A1E30, g_007A1E34;        /* default distance range */
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
    u8 g_0074B71C[8];        /* page 5's state (see P5_RECORDS) */
    int g_0074B724;          /* page (0-0x12) */
    int g_0074B728;
    int g_0074B72C;          /* phase: 0 opening, 1 in use, 2-4 leaving */
    int g_0074B730;          /* page 0x12's step */
    int g_0074B734;          /* player */
    u8 g_0074B738[0xE];      /* the map frame (func_0028F860) */
    u8 g_0074B746;
    u8 g_0074B747;
    u8 page0[3];             /* 0x0074B748 page 0's state */
    u8 g_0074B74B;
    u8 g_0074B74C;
    u8 unknown_4d[3];
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
    u8 unknown_1e8[0x10];
    int g_007725E8;          /* the player of page 5 */
    u8 unknown_1fc[8];
    int g_007725F4;          /* set while the menu opens */
} s_007723F0;
#define g_007725CC (s_007723F0.g_007725CC)
#define g_007725CE (s_007723F0.g_007725CE)
#define g_007725D0 (s_007723F0.g_007725D0)
#define g_007725D4 (s_007723F0.g_007725D4)
#define g_007725E8 (s_007723F0.g_007725E8)
#define g_007725F4 (s_007723F0.g_007725F4)

extern int g_0045D2C0, g_0045D4C0;        /* (small data) */

int func_0036D2E0(void);
void func_0023AD10(int a, int b, int c, int d, int e);
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
int func_00231180(void);
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
u8 **func_0034A740(u8 *unit);         /* the group of a unit */
int func_0033BD60(u8 **a);
u32 func_0036F1E0(int a, int b);
int func_003725A0(int a);
void func_003838B0(int a, int b);
u32 func_00362D70(int side);
void func_001D2B60(void);
void func_001D4150(void);

/* ---- The pages (0x0022FF30-0x00235870) ---- */

/* 0x00500700: the controllers' state, 0x88 bytes per controller (see scene_config.c). */
typedef struct {
    u8 unknown_00[0x4C];
    unsigned short pressed;  /* +0x4C buttons pressed this frame */
    unsigned short held;     /* +0x4E pressed or repeating */
    u8 unknown_50[0x14];
    u8 ready;                /* +0x64 bit 0 */
    u8 connected;            /* +0x65 bit 0 */
    u8 unknown_66[0x22];
} PadState;
extern PadState g_00500700[2];

/* A player's controller (inlined in the original). */
#define PORT(player) ((player) == 0 ? 0 : ((player) == 1 ? 1 : (player)))
#define PAD_READY(p) ((g_00500700[p].ready & 1) ? (g_00500700[p].connected & 1) == 1 : 0)
#define PAD_PRESSED(p) ((unsigned short)(PAD_READY(p) ? g_00500700[p].pressed : 0))
#define PAD_HELD(p) ((unsigned short)(PAD_READY(p) ? g_00500700[p].held : 0))

#define BTN_VIEW_L 0x0004
#define BTN_VIEW_R 0x0008
#define BTN_CANCEL 0x0010
#define BTN_EXTRA  0x0020
#define BTN_OK     0x0040
#define BTN_START  0x0800
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000

#define SE_CURSOR 0x2CDC
#define SE(kind) func_0023AD10((kind), 0, SE_CURSOR, SE_CURSOR, 0x1000)   /* 0 move, 1 OK, 2 back, 4 refused */

/* Leaves for the battle (scene 5) unless another scene was asked for (inlined). */
#define BACK_TO_SCENE(scene) do {                                       \
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)                   \
            g_0045D89C = (scene);                                       \
    } while (0)

extern u8 g_0073DCA3[];                   /* player records, 0x290 bytes (+0: bit 2 a flag) */
#define FOLLOW_OFF(player) UBIT(g_0073DCA3[(player) * 0x290], 2)    /* the camera does not follow */

extern u8 g_006A1D58[][0x68];             /* the soldier groups (see scene_battle_initialize.c) */
#define GROUP(i) ((u8 **)g_006A1D58[i])

extern u8 g_00442FF0[][0x10], g_00443140[][0x10];      /* camera directions of pages 2 and 3 */
extern float g_004433E0[][4];             /* camera targets of page 2 */
extern float g_004436D8, g_004436DC;      /* distance range of page 2 */

extern u8 g_0074B719;                     /* (small data?) the unit followed on page 3 */
extern int g_00772D4C, g_00799A68;

/* The battle map's grid (0x0074B420): per side the count of units, their table at +0x180. */
#define UNIT_COUNT(side) (((int *)g_0074B420)[side])
#define UNIT(side, i) (g_0074B5A0[side][i])

/* Page 3's state (0x0074B760). */
#define P3_SIDE      (g_0074B760[0])
#define P3_CURSOR    (g_0074B760[1])
#define P3_SCROLL    (g_0074B760[2])
#define P3_MOVED     (g_0074B760[3])
#define P3_OFFICER   (g_0074B760[4])     /* 1: follow the group's officer */
#define P3_ORDER     (g_0074B760[8])     /* the order chosen (0-4) */
#define P3_OSCROLL   (g_0074B760[9])
#define P3_GKIND     (g_0074B760[0xC])   /* list of groups: kind, cursor, scroll, groups, count */
#define P3_GCURSOR   (g_0074B760[0xD])
#define P3_GSCROLL   (g_0074B760[0xE])
#define P3_GLIST     ((u8 **)&g_0074B760[0x10])   /* the groups' units */
#define P3_GCOUNT    (g_0074B760[0x34])
#define P3_TKIND     (g_0074B760[0x38])  /* list of targets: kind, cursor, scroll, targets, count */
#define P3_TCURSOR   (g_0074B760[0x39])
#define P3_TSCROLL   (g_0074B760[0x3A])
#define P3_TLIST     (&g_0074B760[0x3C])
#define P3_TCOUNT    (g_0074B760[0x50])
#define P3_GROUP     (*(u8 ***)&g_0074B760[0x54])
#define P3_MODE      (g_0074B760[0x58])  /* 0 a unit, 1 an order, 2 a group, 3 a target */
#define P3_VIEW      (g_0074B760[0x59])

/* Page 5's state: g_0074B71C points to 16 records of 0x110 bytes (+0x1100 their count, +0x1104
 * the newest); g_0074B720 the cursor, g_0074B721 the scroll. */
#define P5_RECORDS   (*(u8 **)&g_0074B71C[0])
#define P5_CURSOR    (g_0074B71C[4])
#define P5_SCROLL    (g_0074B71C[5])

/* Page 10's state (0x0074B7C0): cursor, scroll, then six entries (0 = the current one). */
#define P10_CURSOR   (g_0074B7C0[0])
#define P10_SCROLL   (g_0074B7C0[1])
#define P10_LIST     (&g_0074B7C0[2])

extern u8 g_005BC5A8[];                   /* page 5's records */
extern int g_0040E970[8];                 /* main menu entry -> page (a free battle) */
extern int g_0040E990[4];                 /* Empire main menu line -> entry */
extern int g_0040E9A0[8];                 /* entry -> page (an Empire battle) */
extern int g_0042A410[8];                 /* main menu line -> entry */
extern void (*g_0040E9C0[4])(int player); /* page 3's modes */
extern int g_0040E9D0[4];                 /* page 12 line -> page */
extern int g_0042A450[4];                 /* page 12 line -> entry */
extern int g_0045CDD8[2];                 /* (small data) page 16 line -> page */

int func_00362570(void);
int func_0036F320(int a);
u32 func_0033F7D0(int a, int b);
int func_0036D310(void);
u32 func_003F5560(void);
int func_003F5620(void);
void func_0017DF10(void);
float (*func_001942C0(void))[4];
void func_002EC0C0(u8 *camera, int a);
void func_0027FE60(int layer);
void func_001911A0(float *out, u8 *pos);
void func_0028A510(void);
int func_00281C40(void);
int func_00281CD0(int page);
void func_001D1E80(void);
extern int g_0045D210;
int func_003F1070(int a);
void func_002ECB80(int port);
int func_002C5220(int pad, u8 *cursor, u8 *stored, int count, int count2);
int func_002C54F0(int pad, u8 *cursor, u8 *stored, int count, int count2);
u8 *func_0033B700(u8 **group);
void func_0034ED90(u32 target, u8 *cell);
u32 func_0034EC80(u32 target);
u8 *func_00338410(int group);
u8 **func_0033C560(u8 **group);
u32 func_0033C4E0(u8 **group);
u8 **func_0033C3A0(u8 **group);
u32 func_0033C320(u8 **group);
u32 func_00352F20(u8 **group, u32 *out, int most);
u32 func_00352F80(u8 **group, u32 *out, int most);
u8 func_0035D5A0(u8 kind);
u32 func_0033F580(u8 **group, int *out, int most);
u32 func_0033F600(u8 **group, int *out, int most);
int func_003385E0(void);
void func_0035F6F0(int player, int order);
int func_0036F390(int a, int b);
void func_0028D5D0(int value);
int func_0036F290(int a, int b);
int func_0035DC70(int player);
void func_0036F990(int a, int b, int c);
u8 func_003F6BE0(int a);
int func_003F78A0(int a, int b);
u8 func_003F7AE0(int a);
int func_003F77F0(int a, int b);
void func_003F7920(int a, int b, int c);
int func_0035F0C0(void);
const char *func_00372BC0(int id);
void func_0035CCB0(void);
int func_003F5650(void);
void func_00233E00(void);
void func_00234A90(void);
void func_00234D70(void);
void func_00234F20(void);
void func_00235560(void);
void func_00235870(void);
void func_00235990(void);

/* 0x0022FF30, 0x60 bytes. Whether main menu entry 0 (page 9) is offered: not in an Empire battle
 * nor in battle types 0x10-0x12, and func_0036F320. */
int func_0022FF30(void)
{
    u32 type;

    if (g_00669F6C == 1)
        return 0;
    type = func_00362570();
    if (type < 0x10 || type > 0x12)
        return func_0036F320(0);
    return 0;
}

/* 0x0022FF90, 0x80 bytes, matching. Whether entry 1 (page 10) is offered: not in battle types 6-0x12,
 * and func_0033F7D0 of at least 3. */
int func_0022FF90(void)
{
    u32 type = func_00362570();

    if (type >= 6 && type <= 0x0F)
        return 0;
    if (type >= 0x10 && type <= 0x12)
        return 0;
    if (func_0033F7D0(0, 1) < 3)
        return 0;
    return 1;
}

/* 0x00230010, 0x3C bytes. Whether entry 3 (page 11) is offered: an Empire battle without
 * func_0036D310. */
int func_00230010(void)
{
    if (func_0036D2E0() == 0)
        return 0;
    return func_0036D310() == 0;
}

/* 0x00230050, 0x3C bytes. Whether page 12's line 3 is offered. */
int func_00230050(void)
{
    if (func_003F5560() < 0x47)
        return func_003F5620() != 0;
    return 0;
}

/* 0x00230090, 0x14 bytes, matching. */
void func_00230090(void)
{
    P5_RECORDS = g_005BC5A8;
}

/* 0x002300B0, 0xB0 bytes. Requests page `page`: 0x14 leaves for the battle, 0x15 quits (stops
 * the music); both fade out. */
void func_002300B0(int page)
{
    if (page == 0x14) {
        g_0074B72C = 4;
        g_0074B728 = page;
        func_001B8F60(0, 6, 0x80);
    }
    if (page == 0x15) {
        func_001B8F60(0, 6, 8);
        if (func_0017DDA0() != 0)
            func_0017DF10();
        g_0074B72C = 4;
    } else {
        g_0074B72C = 2;
    }
    g_0074B728 = page;
}

/* Starts a camera move to `t` over 15 frames (inlined). */
#define CAMERA_TARGET(t) do {                   \
        g_007A1B80[0] = (t)[0];                 \
        g_007A1B80[1] = (t)[1];                 \
        g_007A1B80[2] = (t)[2];                 \
        g_007A1B80[3] = (t)[3];                 \
        g_007A1BA8 = 0x0F;                      \
    } while (0)

/* 0x00230160, 0xE48 bytes. Applies the requested page (g_0074B728): resets the camera to the
 * default view, then sets the page up (its camera, its window layers through func_0027FE60);
 * 0x14 goes back to the battle, 0x15 quits to the title (or flags a reset in an Empire battle). */
void func_00230160(void)
{
    float (*box)[4] = func_001942C0();
    float dir[4], len;
    int i;

    func_002C59F0();
    func_002C5A30();
    func_002C5A60();
    g_007A1C20 = 0;
    g_007A1C14 = s_007A1B70.g_007A1E34;
    g_007A1BA4 = 0;
    g_007A1C10 = s_007A1B70.g_007A1E30;
    g_007A1B70[0] = s_007A1B70.g_007A1E00[0];
    g_007A1B70[1] = s_007A1B70.g_007A1E00[1];
    g_007A1B70[2] = s_007A1B70.g_007A1E00[2];
    g_007A1B70[3] = s_007A1B70.g_007A1E00[3];
    for (i = 0; i < 4; i++)                       /* (VU0) the eye's direction and distance */
        dir[i] = s_007A1B70.g_007A1DF0[i] - s_007A1B70.g_007A1E00[i];
    len = __builtin_sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    for (i = 0; i < 4; i++)
        dir[i] = dir[i] * (1.0f / len);
    func_002EBD80(len, g_007A1BC0, dir);
    func_002EBAA0(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()], 0x0F);
    g_007725F4 = 1;
    switch (g_0074B728) {
    case 0:                                       /* the main menu */
        func_0027FE60(0);                         /* no value in the original: a0 still holds the camera */
        s_007A1B70.g_007A1C28 = 0;
        g_007A1C1C = g_00443630[BATTLE_TYPE()].b;
        g_007A1C18 = g_00443630[BATTLE_TYPE()].a;
        g_007A1C24 = 0x0F;
        CAMERA_TARGET(g_00443290[BATTLE_TYPE()]);
        func_002EBAA0(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()], 0x0F);
        g_0074B750 = 1;
        if (g_0074B724 == 2)
            s_007A1B70.g_007A1C28 = 0;
        else
            func_002EC0C0(g_007A1BC0, 2);
        if (g_00669F6C == 1)
            func_00231920();
        else
            func_00231040();
        break;
    case 1:
        func_0027FE60(3);
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 2:                                       /* the map */
        func_0027FE60(7);
        s_007A1B70.g_007A1C28 = 0;
        g_007A1C24 = 0x0F;
        g_007A1C1C = g_004436DC;
        g_007A1C18 = g_004436D8;
        CAMERA_TARGET(g_004433E0[BATTLE_TYPE()]);
        func_002EBAA0(g_00443530[BATTLE_TYPE()].b, g_007A1BC0, g_00442FF0[BATTLE_TYPE()], 0x0F);
        g_0074B750 = 1;
        g_00772D4C = g_0074B734;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 3:                                       /* the units */
        func_0027FE60(9);
        s_0074B71C.g_0074B74C = 0;
        s_0074B71C.g_0074B74B = 0;
        s_007A1B70.g_007A1C28 = 1;
        if (FOLLOW_OFF(g_0074B734)) {
            float centre[4];

            g_007A1C18 = 2048.0f;
            g_007A1C24 = 0x0F;
            g_007A1C1C = 2020.0f;
            for (i = 0; i < 4; i++)               /* (VU0) the middle of the map's box */
                centre[i] = (box[0][i] + box[1][i]) * 0.5f;
            CAMERA_TARGET(centre);
        } else {
            u8 *unit = g_0074B5A0[g_0074B719][0];
            float pos[4];

            g_007A1C24 = 0x0F;
            g_007A1C18 = 2048.0f;
            g_007A1C1C = 2048.0f;
            func_001911A0(pos, (*(u32 *)(unit + 0x80) & 0x20000) ? unit + 0x30 : unit + 0x28);
            CAMERA_TARGET(pos);
        }
        func_002EBAA0(g_00443530[BATTLE_TYPE()].c, g_007A1BC0, g_00443140[BATTLE_TYPE()], 0x0F);
        func_002EC0C0(g_007A1BC0, 1);
        g_0074B750 = 1;
        g_00772D4C = g_0074B734;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        func_00233E00();
        break;
    case 4:
        func_0027FE60(0x0D);
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 6:
        func_0027FE60(0x0F);
        if (g_0074B724 == 0x0C)
            func_0027FE60(0x15);
        func_0028A510();
        break;
    case 5:                                       /* the records */
        {
            float centre[4];

            func_0027FE60(0x0B);
            P5_CURSOR = 0;
            P5_SCROLL = 0;
            g_007A1C24 = 0x0F;
            s_007A1B70.g_007A1C28 = 1;
            g_007A1C18 = 2048.0f;
            g_007A1C1C = 2020.0f;
            for (i = 0; i < 4; i++)               /* (VU0) the middle of the map's box */
                centre[i] = (box[0][i] + box[1][i]) * 0.5f;
            CAMERA_TARGET(centre);
            func_002EBAA0(g_00443530[BATTLE_TYPE()].c, g_007A1BC0, g_00443140[BATTLE_TYPE()], 0x0F);
            func_002EC0C0(g_007A1BC0, 1);
            g_0074B750 = 1;
            g_007725E8 = g_0074B734;
            func_0027FE60(0x15);
        }
        break;
    case 7:
        func_0027FE60(0x13);
        g_0074B754 = 0;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 8:
        g_00799A68 = 0;
        func_0027FE60(5);
        func_0027FE60(0x15);
        break;
    case 0x14:                                    /* back to the battle */
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D8A0;
            g_0045D89C = 0x18;
        } else {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D89C;
            g_0045D89C = g_0045D8A0;
        }
        break;
    case 0x15:                                    /* quit */
        if (g_00669F6C == 1) {
            if (func_0017DDA0() != 0)
                func_0017DF10();
            g_0045D894 = g_0045D898;
            BACK_TO_SCENE(1);
            if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
                g_0045D898 = g_0045D8A0;
                g_0045D89C = 0x18;
            } else {
                g_0045D898 = g_0045D89C;
                g_0045D89C = g_0045D8A0;
            }
            func_001D1E80();
        } else {
            g_0045D210 = 1;
        }
        break;
    case 9:
        g_00772D4C = g_0074B734;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 10:
        func_0027FE60(0x1A);
        func_00234A90();
        break;
    case 11:
        func_00234D70();
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        break;
    case 12:
        g_00772D4C = g_0074B734;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        func_00234F20();
        break;
    case 15:
        func_0027FE60(0x19);
        break;
    case 16:
        g_00772D4C = g_0074B734;
        if (g_0074B724 == 0)
            func_0027FE60(0x14);
        func_00235560();
        break;
    case 17:
        func_00235870();
        break;
    case 18:
        func_00235990();
        break;
    }
    g_0074B747 = 0;
    g_0074B724 = g_0074B728;
    g_0074B72C = 0;
    g_007725F4 = 1;
    func_00376100(0, func_00281C40(), func_00281CD0(g_0074B724));
}

/* 0x00230FB0, 0x8 bytes, matching. The main menu's lines. */
int func_00230FB0(void)
{
    return 8;
}

/* 0x00230FC0, 0x18 bytes, matching. */
int func_00230FC0(int line)
{
    return g_0042A410[line];
}

/* 0x00230FE0, 0x60 bytes, matching. Whether main menu entry `entry` is offered. */
int func_00230FE0(int entry)
{
    switch (entry) {
    case 0:
        return func_0022FF30();
    case 1:
        return func_0022FF90();
    case 3:
        return func_00230010();
    }
    return 1;
}

/* 0x00231040, 0xB8 bytes. Puts each player's main menu cursor on an offered line. */
void func_00231040(void)
{
    int n = func_00230FB0();
    int p;

    if (n <= 0)
        return;
    for (p = 0; p < 2; p++) {
        u32 line = g_0074B260[0x4E8 + p];

        while (func_00230FE0(func_00230FC0(line)) == 0)
            line = (int)(line + 1) % n;
        g_0074B260[0x4E8 + p] = line;
    }
}

/* 0x00231100, 0x78 bytes. Whether message box 0 holds the menu (open, and its answer not 1 or
 * 2). */
int func_00231100(void)
{
    if (g_006934B3 == 0 || s_0068F3E0.g_006934B4 == 1 || s_0068F3E0.g_006934B4 == 2)
        return 0;
    return 1;
}

/* 0x00231180, 0x9C bytes. In an Empire game outside an Empire battle, starts help 0x17 or 7
 * when func_003F1070 accepts it. */
int func_00231180(void)
{
    if (func_0036D2E0() != 0 && g_00669F6C != 1) {
        if (func_003F1070(0x17) != 0) {
            g_007725CC = g_007725CE;
            g_007725D0 = 0;
            g_007725D4 = 1;
            return 1;
        }
        if (func_003F1070(7) != 0) {
            g_007725CC = g_007725CE;
            g_007725D0 = 0;
            g_007725D4 = 1;
            return 1;
        }
    }
    return 0;
}

/* 0x00231220, 0x5CC bytes. Page 0 in a free battle (player `player`): OK opens the line's page
 * (6 only for player 0, 7 back to the battle), Start back to the battle (or to the last line),
 * Cancel back to the battle, Up / Down move among the offered lines. */
int func_00231220(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);
    int n = func_00230FB0();
    u8 *line = &g_0074B748[player];
    int entry = func_00230FC0(*line);
    int i;

    if (func_00231100() != 0)
        return 0;
    if (pressed & BTN_OK) {
        switch (entry) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            {
                int pages[8];

                for (i = 0; i < 8; i++)
                    pages[i] = g_0040E970[i];
                SE(1);
                func_002300B0(pages[entry]);
                g_0074B734 = player;
                return 1;
            }
        case 6:
            if (player == 0) {
                SE(1);
                func_002300B0(0x10);
                g_0074B734 = player;
            } else {
                SE(4);
            }
            break;
        case 7:
            SE(1);
            func_002300B0(0x14);
            if (g_00669F6C == 1) {
                BACK_TO_SCENE(4);
                if (func_0017DDA0() != 0)
                    func_0017DF10();
            } else {
                g_0045D880.force_draw = 1;
                BACK_TO_SCENE(5);
            }
            g_0074B734 = player;
            return 1;
        }
    } else if (pressed & BTN_EXTRA) {
    } else if (pressed & BTN_START) {
        if (entry != 7) {
            SE(0);
            *line = n - 1;
            return 1;
        }
        SE(1);
        func_002300B0(0x14);
        BACK_TO_SCENE(5);
        g_0045D880.force_draw = 1;
        return 1;
    } else if (pressed & BTN_CANCEL) {
        *line = n - 1;
        SE(2);
        func_002300B0(0x14);
        BACK_TO_SCENE(5);
        g_0045D880.force_draw = 1;
        return 1;
    } else if ((held & BTN_UP) || (pressed & BTN_UP)) {
        int to = (int)(*line + n - 1) % n;

        while (func_00230FE0(func_00230FC0(to)) == 0)
            to = (to + n - 1) % n;
        if (to < *line || (pressed & BTN_UP)) {
            SE(0);
            *line = to;
        }
    } else if ((held & BTN_DOWN) || (pressed & BTN_DOWN)) {
        int to = (int)(*line + 1) % n;

        while (func_00230FE0(func_00230FC0(to)) == 0)
            to = (to + 1) % n;
        if (*line < to || (pressed & BTN_DOWN)) {
            SE(0);
            *line = to;
        }
    }
    func_002ECB80(port);
    return 0;
}

/* 0x002317F0, 0x12C bytes. Back to the battle from an Empire battle's menu (scene 4); with two
 * armies, the first player to ask waits for the other one. */
void func_002317F0(int player)
{
    if ((g_00669F60 & 2) == 0) {
        BACK_TO_SCENE(4);
        func_002300B0(0x14);
        if (func_0017DDA0() != 0)
            func_0017DF10();
    } else if ((&g_0074B758)[(player + 1) % 2] == 0) {
        int *ready = &(&g_0074B758)[player];

        if (*ready == 0)
            *ready = 1;
    } else {
        BACK_TO_SCENE(4);
        func_002300B0(0x14);
        if (func_0017DDA0() != 0)
            func_0017DF10();
    }
}

/* 0x00231920, 0x8 bytes, matching. */
void func_00231920(void)
{
}

/* 0x00231930, 0x468 bytes. Page 0 in an Empire battle: four lines (entries 2, 4, 5, 7). OK on 2,
 * 4 or 5 opens its page, on 7 goes back to the battle (func_002317F0); a player waiting for the
 * other can only cancel the wait. */
int func_00231930(int player)
{
    int lines[4];
    int port = PORT(player);
    unsigned short pressed, held;
    u8 *line;
    int entry, waiting;
    int i;

    for (i = 0; i < 4; i++)
        lines[i] = g_0040E990[i];
    pressed = PAD_PRESSED(port);
    held = PAD_HELD(port);
    line = &g_0074B748[player];
    entry = lines[*line];
    waiting = 0;
    if (g_00669F60 & 2)
        waiting = (&g_0074B758)[player] != 0;
    if (waiting) {
        if ((pressed & BTN_CANCEL) == 0)
            return 0;
        (&g_0074B758)[player] = 0;
        SE(2);
        return 1;
    }
    if (pressed & BTN_OK) {
        if (entry == 7) {
            SE(1);
            func_002317F0(player);
            g_0074B734 = player;
            return 1;
        }
        if (entry == 5 || entry == 4 || entry == 2) {
            int pages[8];

            for (i = 0; i < 8; i++)
                pages[i] = g_0040E9A0[i];
            SE(1);
            func_002300B0(pages[entry]);
            g_0074B734 = player;
            return 1;
        }
    } else if (pressed & BTN_EXTRA) {
    } else if (pressed & BTN_START) {
        if (entry == 7) {
            SE(1);
            func_002317F0(player);
        } else {
            SE(0);
            *line = 3;
        }
        return 1;
    } else if (pressed & BTN_CANCEL) {
        if (g_00669F6C != 1)
            SE(4);
    } else if ((held & BTN_UP) || (pressed & BTN_UP)) {
        u8 to = (*line + 3) & 3;

        if (to < *line || (pressed & BTN_UP)) {
            SE(0);
            *line = to;
        }
    } else if ((held & BTN_DOWN) || (pressed & BTN_DOWN)) {
        u8 to = (*line + 1) & 3;

        if (*line < to || (pressed & BTN_DOWN)) {
            SE(0);
            *line = to;
        }
    }
    func_002ECB80(port);
    return 0;
}

/* 0x00231DA0, 0x128 bytes. Page 1: Cancel to page 12, the extra button to page 8. */
void func_00231DA0(int player)
{
    unsigned short pressed = 0;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    } else if (pressed & BTN_EXTRA) {
        SE(1);
        func_002300B0(8);
    }
}

/* 0x00231ED0, 0x278 bytes. Page 7: save (line 0) or quit (line 1), each asked in message box 1;
 * Up / Down switch line, Cancel goes back. */
void func_00231ED0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);
    char text[256];

    if (pressed & BTN_OK) {
        if (g_0074B747 == 0) {
            SE(1);
            func_001204B0(text, TEXT(0x0043C318));     /* "Save game data?" */
            func_001AE9F0(1, text, 1);
            func_001AFC70(1, port);
            g_0074B730 = 1;
        } else if (g_0074B747 == 1) {
            SE(1);
            func_001204B0(text, TEXT(0x0043C344));     /* "Exiting game. Proceed?" */
            func_001AE9F0(1, text, 1);
            func_001AFC70(1, port);
            g_0074B730 = 2;
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else if (held & BTN_UP) {
        SE(0);
        g_0074B747 = (g_0074B747 + 1) & 1;
    } else if (held & BTN_DOWN) {
        SE(0);
        g_0074B747 = (g_0074B747 + 1) & 1;
    }
}

/* 0x00232150, 0xDC bytes. Page 2 (the map): Cancel goes back. */
void func_00232150(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);

    if ((pressed & BTN_OK) == 0 && (pressed & BTN_CANCEL) != 0) {
        SE(2);
        func_002300B0(0);
    }
    func_002ECB80(port);
}

/* 0x00232230, 0x5C bytes. Moves the camera's target to `pos` (from the default target). */
void func_00232230(u8 *pos)
{
    float target[4];

    func_001911A0(target, pos);
    g_007A1BA4 = 0;
    g_007A1B70[0] = s_007A1B70.g_007A1E00[0];
    g_007A1B70[1] = s_007A1B70.g_007A1E00[1];
    g_007A1B70[2] = s_007A1B70.g_007A1E00[2];
    g_007A1B70[3] = s_007A1B70.g_007A1E00[3];
    g_007A1BA8 = 0x0F;
    g_007A1B80[0] = target[0];
    g_007A1B80[1] = target[1];
    g_007A1B80[2] = target[2];
    g_007A1B80[3] = target[3];
    g_0074B750 = 1;
}

/* 0x00232290, 0x3C bytes, matching. The camera on a unit. */
void func_00232290(u8 *unit)
{
    func_00232230((*(u32 *)(unit + 0x80) & 0x20000) ? unit + 0x30 : unit + 0x28);
}

/* 0x002322D0, 0x24 bytes, matching. The camera on a group. */
void func_002322D0(u8 **group)
{
    func_00232230(func_0033B700(group));
}

/* 0x00232300, 0x7C bytes. The camera on a target's map cell (5000 units a cell). */
void func_00232300(u32 target)
{
    float pos[2];
    u8 cell[4];

    func_0034ED90(target, cell);
    pos[0] = (float)cell[0] * 5000.0f + 2500.0f;
    pos[1] = (float)cell[1] * 5000.0f + 2500.0f;
    func_00232230((u8 *)pos);
}

/* 0x00232380, 0x13C bytes. The camera on what a group is doing: the group or the cell it goes
 * to (by the order's kind, func_00338410 +8, else +2). */
void func_00232380(u8 **group)
{
    int i = ((u8 *)group - g_006A1D58[0]) / 0x68;
    u8 kind = func_00338410(i)[8];

    if (kind == 3 || kind == 1) {
        func_002322D0(func_0033C560(group));
    } else if (kind == 2 || kind == 0) {
        func_00232300(func_0033C4E0(group));
    } else {
        kind = func_00338410(i)[2];
        if (kind == 4 || kind == 2)
            func_002322D0(func_0033C3A0(group));
        else if (kind == 3 || kind == 1)
            func_00232300(func_0033C320(group));
        else
            func_002322D0(group);
    }
}

/* 0x002324C0, 0x78 bytes. Page 3: back to choosing a unit (from the first one when `reset`). */
void func_002324C0(int reset)
{
    if (reset != 0) {
        P3_SIDE = 0;
        P3_CURSOR = 0;
        P3_SCROLL = 0;
        P3_MOVED = 0;
    }
    P3_OFFICER = 0;
    if (UNIT_COUNT(0) > 0)
        func_00232290(UNIT(P3_SIDE, P3_CURSOR));
    P3_MODE = 0;
}

/* 0x00232540, 0x48 bytes. Page 3: the orders of `group` (the first one when `reset`). */
void func_00232540(u8 **group, int reset)
{
    if (group == 0)
        return;
    if (reset != 0) {
        P3_ORDER = 0;
        P3_OSCROLL = 0;
    }
    P3_GROUP = group;
    func_002322D0(group);
    P3_MODE = 1;
}

/* Fills page 3's target list from `n` targets (inlined twice). */
#define P3_FILL_TARGETS(list, n) do {                                   \
        u32 k_;                                                         \
        for (k_ = 0; k_ < (n); k_++)                                    \
            P3_TLIST[k_] = (u8)(list)[k_];                              \
    } while (0)

/* 0x00232590, 0x14C bytes. Page 3: the targets (func_00352F20) of the order kind. */
void func_00232590(void)
{
    u32 list[20];
    u8 **group = P3_GROUP;
    u32 n = func_00352F20(group, list, 0x14);

    P3_TKIND = func_0035D5A0((*group)[0x79]);
    P3_TCURSOR = 0;
    P3_TSCROLL = 0;
    g_0074B760[0x3B] = 0;
    func_00118850(P3_TLIST, 0x14);
    P3_FILL_TARGETS(list, n);
    P3_TCOUNT = (u8)n;
    if (n != 0)
        func_00232300(func_0034EC80(list[P3_TCURSOR]));
    P3_MODE = 3;
}

/* 0x002326E0, 0x144 bytes. Page 3: the targets (func_00352F80) of the group's kind. */
void func_002326E0(void)
{
    u32 list[20];
    u8 **group = P3_GROUP;
    u32 n = func_00352F80(group, list, 0x14);

    P3_TKIND = (*group)[0x79];
    P3_TCURSOR = 0;
    P3_TSCROLL = 0;
    g_0074B760[0x3B] = 0;
    func_00118850(P3_TLIST, 0x14);
    P3_FILL_TARGETS(list, n);
    P3_TCOUNT = (u8)n;
    if (n != 0)
        func_00232300(func_0034EC80(list[P3_TCURSOR]));
    P3_MODE = 3;
}

/* 0x00232830, 0x2C4 bytes. Page 3: the groups (func_0033F580) of the order kind. */
void func_00232830(void)
{
    int list[16];
    u8 **group = P3_GROUP;
    u32 n = func_0033F580(group, list, 0x10);
    u32 k;

    P3_GKIND = func_0035D5A0((*group)[0x79]);
    P3_GCURSOR = 0;
    P3_GSCROLL = 0;
    g_0074B760[0xF] = 0;
    func_00118850(P3_GLIST, 0x24);
    for (k = 0; k < n; k++)
        P3_GLIST[k] = *GROUP(list[k]);
    P3_GCOUNT = (u8)n;
    if (n != 0)
        func_002322D0(GROUP(list[P3_GCURSOR]));
    P3_MODE = 2;
}

/* 0x00232B00, 0x2C4 bytes. Page 3: the groups (func_0033F600) of the group's kind. */
void func_00232B00(void)
{
    int list[16];
    u8 **group = P3_GROUP;
    u32 n = func_0033F600(group, list, 0x10);
    u32 k;

    P3_GKIND = (*group)[0x79];
    P3_GCURSOR = 0;
    P3_GSCROLL = 0;
    g_0074B760[0xF] = 0;
    func_00118850(P3_GLIST, 0x24);
    for (k = 0; k < n; k++)
        P3_GLIST[k] = *GROUP(list[k]);
    P3_GCOUNT = (u8)n;
    if (n != 0)
        func_002322D0(GROUP(list[P3_GCURSOR]));
    P3_MODE = 2;
}

/* 0x00232DD0, 0x80 bytes. Whether `unit` can be given orders: active, none of the blocking
 * states, not flagged 0x30, and of kind 0. */
int func_00232DD0(u8 *unit)
{
    u32 flags;

    if (unit == 0)
        return 0;
    flags = *(u32 *)(unit + 0x80);
    if ((flags & 1) == 0)
        return 0;
    if ((flags & 1) == 0 || (flags & 0x8C40002) != 0)
        return 0;
    if ((flags & 0x30) != 0)
        return 0;
    return unit[0x79] == 0;
}

/* 0x00232E50, 0xCC bytes. Gives `group` order `order` (towards `target`) for `player`:
 * counts it in the order's record (at most 0xFF) when func_003385E0 allows it. */
void func_00232E50(u8 **group, int order, int target, int player)
{
    int i;
    u8 *rec;

    if (func_003385E0() == 0)
        return;
    i = ((u8 *)group - g_006A1D58[0]) / 0x68;
    rec = func_00338410(i);
    if (rec[0x0B + order] != 0xFF) {
        u32 n = rec[0x0B + order] + 1;

        if (n > 0xFF)
            n = 0xFF;
        func_00338410(i)[0x0B + order] = n;
    }
    func_0035F6F0(player, order);
}

/* Switches the view (three views, or two for units flagged 0x30), forward `step` 1 or 2. */
#define P3_NEXT_VIEW(unit, step) do {                                   \
        if ((*(u32 *)((unit) + 0x80) & 0x30) == 0) {                    \
            P3_VIEW = (u8)((P3_VIEW + (step)) % 3);                     \
        } else {                                                        \
            int was2 = P3_VIEW == 2;                                    \
            P3_VIEW = 2;                                                \
            if (was2)                                                   \
                P3_VIEW = 0;                                            \
        }                                                               \
    } while (0)

/* 0x00232F20, 0x5A8 bytes. Page 3, choosing a unit: the list of one side's units (Left / Right
 * switch side), the cursor (11 shown), L1 / R1 the view, the extra button follows the group's
 * officer; OK on an orderable unit (not in an Empire battle) opens its orders. */
void func_00232F20(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);
    u32 count = UNIT_COUNT(P3_SIDE);
    u32 shown = (int)count > 10 ? 11 : count;
    int moved = 0;
    u8 *unit = UNIT(P3_SIDE, P3_CURSOR);

    P3_MOVED = 0;
    if (pressed & BTN_OK) {
        if (g_00669F6C == 1) {
            SE(4);
        } else if (unit != 0) {
            if (func_00232DD0(unit) == 0) {
                SE(4);
            } else {
                SE(1);
                func_00232540(func_0034A740(unit), 1);
            }
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else if (pressed & BTN_EXTRA) {
        if (func_0033BD60(func_0034A740(unit)) == 0 || P3_VIEW != 0) {
            SE(4);
        } else {
            SE(0);
            P3_OFFICER = P3_OFFICER == 0;
            moved = 1;
        }
    } else if (pressed & BTN_LEFT) {
        SE(0);
        P3_SIDE = (P3_SIDE + 1) & 1;
        moved = 1;
        P3_CURSOR = 0;
        P3_SCROLL = 0;
        P3_MOVED = 1;
        P3_OFFICER = 0;
    } else if (pressed & BTN_RIGHT) {
        SE(0);
        P3_SIDE = (P3_SIDE + 3) & 1;
        moved = 1;
        P3_CURSOR = 0;
        P3_MOVED = 2;
        P3_SCROLL = 0;
        P3_OFFICER = 0;
    } else if (func_002C5220(port, &P3_SCROLL, &P3_CURSOR, shown & 0xFF, count & 0xFF) != 0) {
        P3_OFFICER = 0;
        moved = 1;
    } else if (held & BTN_VIEW_L) {
        if (unit != 0) {
            SE(0);
            P3_NEXT_VIEW(unit, 2);
        }
    } else if (held & BTN_VIEW_R) {
        if (unit != 0) {
            SE(0);
            P3_NEXT_VIEW(unit, 4);
        }
    }
    if (moved && !FOLLOW_OFF(player) && P3_CURSOR < UNIT_COUNT(P3_SIDE)) {
        u8 **group = GROUP(*(int *)(UNIT(P3_SIDE, P3_CURSOR) + 0x10));

        if (P3_OFFICER == 1) {
            if ((*group)[0x79] == 0 || func_0036F390(0, 10) != 0) {
                func_00232380(group);
            } else {
                P3_OFFICER = 0;
                func_002322D0(group);
            }
        } else if (P3_OFFICER == 0) {
            func_002322D0(group);
        }
    }
}

/* 0x002334D0, 0x300 bytes. Page 3, choosing the order (5 lines): 4 gives it at once, 3 / 1 list
 * groups, 2 / 0 list targets; Cancel goes back to the units. */
void func_002334D0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);

    if (pressed & BTN_OK) {
        SE(1);
        if (P3_ORDER == 4) {
            func_00232E50(P3_GROUP, 4, 0xFF, player);
            func_002324C0(0);
        } else if (P3_ORDER == 3) {
            func_00232B00();
        } else if (P3_ORDER == 1) {
            func_00232830();
        } else if (P3_ORDER == 2) {
            func_002326E0();
        } else if (P3_ORDER == 0) {
            func_00232590();
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002324C0(0);
    } else if (func_002C5220(port, &P3_OSCROLL, &P3_ORDER, 5, 5) == 0) {
        if (held & BTN_VIEW_L) {
            SE(0);
            P3_NEXT_VIEW(*P3_GROUP, 2);
        } else if (held & BTN_VIEW_R) {
            SE(0);
            P3_NEXT_VIEW(*P3_GROUP, 4);
        }
    }
}

/* 0x002337D0, 0x314 bytes. Page 3, choosing a group: OK gives the order towards it. */
void func_002337D0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);
    u8 shown = P3_GCOUNT > 10 ? 11 : P3_GCOUNT;
    u8 *chosen = (u8 *)P3_GLIST[P3_GCURSOR];

    if (pressed & BTN_OK) {
        if (chosen != 0) {
            SE(1);
            func_00232E50(P3_GROUP, P3_ORDER, *(int *)(chosen + 0x10), player);
            func_002324C0(0);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00232540(P3_GROUP, 0);
    } else if (func_002C5220(port, &P3_GSCROLL, &P3_GCURSOR, shown, P3_GCOUNT) != 0) {
        if (!FOLLOW_OFF(player))
            func_00232290((u8 *)P3_GLIST[P3_GCURSOR]);
    } else if (held & BTN_VIEW_L) {
        if (chosen != 0) {
            SE(0);
            P3_NEXT_VIEW(chosen, 2);
        }
    } else if (held & BTN_VIEW_R) {
        if (chosen != 0) {
            SE(0);
            P3_NEXT_VIEW(chosen, 4);
        }
    }
}

/* 0x00233AF0, 0x30C bytes. Page 3, choosing a target: OK gives the order towards it. */
void func_00233AF0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    unsigned short held = PAD_HELD(port);
    u8 shown = P3_TCOUNT > 10 ? 11 : P3_TCOUNT;

    if (pressed & BTN_OK) {
        if (P3_TCOUNT != 0) {
            SE(1);
            func_00232E50(P3_GROUP, P3_ORDER, P3_TLIST[P3_TCURSOR], player);
            func_002324C0(0);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00232540(P3_GROUP, 0);
    } else if (func_002C5220(port, &P3_TSCROLL, &P3_TCURSOR, shown, P3_TCOUNT) != 0) {
        if (!FOLLOW_OFF(player))
            func_00232300(func_0034EC80(P3_TLIST[P3_TCURSOR]));
    } else if (held & BTN_VIEW_L) {
        SE(0);
        P3_NEXT_VIEW(*P3_GROUP, 2);
    } else if (held & BTN_VIEW_R) {
        SE(0);
        P3_NEXT_VIEW(*P3_GROUP, 4);
    }
}

/* 0x00233E00, 0x1C bytes, matching. Page 3 set-up. */
void func_00233E00(void)
{
    func_002324C0(1);
}

/* 0x00233E20, 0x60 bytes. Page 3: runs the handler of its mode. */
void func_00233E20(int player)
{
    void (*handlers[4])(int player);

    handlers[0] = g_0040E9C0[0];
    handlers[1] = g_0040E9C0[1];
    handlers[2] = g_0040E9C0[2];
    handlers[3] = g_0040E9C0[3];
    handlers[P3_MODE](player);
}

/* 0x00233E80, 0x100 bytes. Page 4: Cancel goes back. */
void func_00233E80(int player)
{
    unsigned short pressed = 0;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if ((pressed & BTN_OK) == 0 && (pressed & BTN_CANCEL) != 0) {
        SE(2);
        func_002300B0(0);
    }
}

/* 0x00233F80, 0xEC bytes, matching. Page 6: Cancel goes back to page 12. */
void func_00233F80(int player)
{
    u32 pressed = player;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    }
}

/* 0x00234070, 0x94 bytes. The camera on the middle of the map. */
void func_00234070(void)
{
    float (*box)[4] = func_001942C0();
    float centre[4];
    int i;

    for (i = 0; i < 4; i++)                       /* (VU0) the middle of the map's box */
        centre[i] = (box[0][i] + box[1][i]) * 0.5f;
    g_007A1BA8 = 0x0F;
    g_007A1BA4 = 0;
    g_0074B750 = 1;
    g_007A1B70[0] = s_007A1B70.g_007A1E00[0];
    g_007A1B70[1] = s_007A1B70.g_007A1E00[1];
    g_007A1B70[2] = s_007A1B70.g_007A1E00[2];
    g_007A1B70[3] = s_007A1B70.g_007A1E00[3];
    g_007A1B80[0] = centre[0];
    g_007A1B80[1] = centre[1];
    g_007A1B80[2] = centre[2];
    g_007A1B80[3] = centre[3];
}

/* 0x00234110, 0xC8 bytes. The camera on page 5's record (counted back from the newest), or the
 * map's middle when it has no position. */
void func_00234110(void)
{
    u8 *rec = P5_RECORDS + ((*(int *)(P5_RECORDS + 0x1104) - P5_CURSOR + 0x0F) & 0x0F) * 0x110;

    if (0.0f < *(float *)(rec + 8) || 0.0f < *(float *)(rec + 0x0C)) {
        float pos[4];

        func_001911A0(pos, rec + 8);
        g_007A1BA8 = 0x0F;
        g_007A1BA4 = 0;
        g_0074B750 = 1;
        g_007A1B80[0] = pos[0];
        g_007A1B80[1] = pos[1];
        g_007A1B80[2] = pos[2];
        g_007A1B80[3] = pos[3];
        g_007A1B70[0] = s_007A1B70.g_007A1E00[0];
        g_007A1B70[1] = s_007A1B70.g_007A1E00[1];
        g_007A1B70[2] = s_007A1B70.g_007A1E00[2];
        g_007A1B70[3] = s_007A1B70.g_007A1E00[3];
    } else {
        func_00234070();
    }
}

/* 0x002341E0, 0x244 bytes. Page 5, the records: the cursor (func_002C54F0, one shown), the
 * camera follows; Cancel goes back to page 12. */
void func_002341E0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    u8 old;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if (pressed & BTN_OK)
        return;
    if (pressed & BTN_CANCEL) {
        if (!FOLLOW_OFF(player))
            func_00234070();
        func_002300B0(0x0C);
        SE(2);
        return;
    }
    old = P5_CURSOR;
    if (func_002C54F0(port, &old, &P5_CURSOR, 1, P5_RECORDS[0x1100]) != 0 && !FOLLOW_OFF(player))
        func_00234110();
}

/* 0x00234430, 0xC0 bytes. Page 15: Cancel goes back to page 12. */
void func_00234430(int player)
{
    int port = PORT(player);

    if (PAD_PRESSED(port) & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    }
}

/* 0x002344F0, 0x3BC bytes. Page 8: a grid of 4 rows of 10 (0xFF = the header line, g_0074B74A
 * its column): Up / Down / Left / Right; Cancel goes back to page 12. */
void func_002344F0(int player)
{
    u32 held = player;
    unsigned short pressed = 0;

    if (player == 0) {
        pressed = PAD_PRESSED(0);
        held = PAD_HELD(0);
    } else if (player == 1) {
        pressed = PAD_PRESSED(1);
        held = PAD_HELD(1);
    }
    if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    } else if (held & BTN_DOWN) {
        if (g_0074B747 == 0xFF) {
            SE(0);
            g_0074B747 = g_0074B74A * 10;
            func_0028D5D0(0x0E);
        } else if (g_0074B747 % 10 < 9) {
            SE(0);
            g_0074B747++;
            func_0028D5D0(0x0E);
        }
    } else if (held & BTN_UP) {
        if (g_0074B747 != 0xFF) {
            if (g_0074B747 % 10 == 0) {
                SE(0);
                g_0074B74A = g_0074B747;
                g_0074B747 = 0xFF;
                g_0074B74A = g_0074B74A / 10;
                func_0028D5D0(0x0E);
            } else {
                SE(0);
                g_0074B747--;
                func_0028D5D0(0x0E);
            }
        }
    } else if (held & BTN_RIGHT) {
        if (g_0074B747 != 0xFF && g_0074B747 < 0x1E) {
            SE(0);
            g_0074B747 += 10;
            func_0028D5D0(0x0E);
        }
    } else if (held & BTN_LEFT) {
        if (g_0074B747 != 0xFF && g_0074B747 > 9) {
            SE(0);
            g_0074B747 -= 10;
            func_0028D5D0(0x0E);
        }
    }
}

/* 0x002348B0, 0x1D4 bytes. Page 9: a list of func_0036F1E0 entries; OK uses the chosen one
 * (func_0036F290 allows it) and goes back to the battle. */
void func_002348B0(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    u8 n = func_0036F1E0(0, 0);

    if (pressed & BTN_OK) {
        if (func_0036F290(0, g_0074B7BC[0]) == 0) {
            SE(4);
        } else {
            SE(1);
            func_0036F990(0, g_0074B7BC[0], func_0035DC70(player));
            func_002300B0(0x14);
            g_0045D880.force_draw = 1;
            BACK_TO_SCENE(5);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else {
        func_002C5220(port, &g_0074B7BC[1], &g_0074B7BC[0], n, n);
    }
}

/* 0x00234A90, 0xC0 bytes. Page 10 set-up: the current entry first, then the others that
 * func_003F78A0 offers (6 = none). */
void func_00234A90(void)
{
    u32 i, n = 1;

    P10_CURSOR = 0;
    P10_SCROLL = 0;
    P10_LIST[0] = func_003F6BE0(0);
    for (i = 0; i < 6; i++)
        if (P10_LIST[0] != i && func_003F78A0(0, i) != 0)
            P10_LIST[n++] = i;
    for (; n < 6; n++)
        P10_LIST[n] = 6;
}

/* 0x00234B50, 0x14 bytes, matching. */
u8 func_00234B50(int i)
{
    return P10_LIST[i];
}

/* 0x00234B70, 0x200 bytes. Page 10: OK switches to the chosen entry (not the current one,
 * func_003F77F0 allows it) and goes back to the battle. */
void func_00234B70(int player)
{
    int port = PORT(player);
    unsigned short pressed = PAD_PRESSED(port);
    u8 n = func_003F7AE0(0);

    if (pressed & BTN_OK) {
        u8 entry = P10_LIST[P10_CURSOR];

        if (P10_CURSOR == 0) {
            SE(4);
        } else if (func_003F77F0(0, entry) == 0) {
            SE(4);
        } else {
            SE(1);
            func_003F7920(0, entry, func_0035DC70(player));
            func_002300B0(0x14);
            g_0045D880.force_draw = 1;
            BACK_TO_SCENE(5);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else {
        func_002C5220(port, &P10_SCROLL, &P10_CURSOR, n, n);
    }
}

/* 0x00234D70, 0x94 bytes. Page 11 set-up: asks message 1 or 2 (func_0035F0C0) in box 1. */
void func_00234D70(void)
{
    char text[256];
    int second = g_0074B734 == 1;

    func_001204B0(text, func_00372BC0(func_0035F0C0() == 0 ? 1 : 2));
    func_001AE9F0(1, text, 1);
    func_001AFC70(1, second);
    g_0074B730 = 2;
}

/* 0x00234E10, 0xB4 bytes. Page 11: yes (4) applies func_0035CCB0 and goes back to the battle,
 * 5 or a closed box back to the main menu. */
void func_00234E10(int player)
{
    if (g_006935DB == 0) {
        func_002300B0(0);
    } else if (g_006935DC == 4) {
        func_0035CCB0();
        func_002300B0(0x14);
        g_0045D880.force_draw = 1;
        BACK_TO_SCENE(5);
    } else if (g_006935DC == 5) {
        func_002300B0(0);
        g_0074B730 = 0;
    }
}

/* 0x00234ED0, 0x18 bytes, matching. */
int func_00234ED0(int line)
{
    return g_0042A450[line];
}

/* 0x00234EF0, 0x2C bytes. Whether page 12 entry `entry` is offered (0x0B: func_00230050). */
int func_00234EF0(int entry)
{
    if (entry == 0x0B)
        return func_00230050();
    return 1;
}

/* 0x00234F20, 0x34 bytes, matching. Page 12 set-up. */
void func_00234F20(void)
{
    if (g_0074B724 == 0)
        g_0074B7C8 = 0;
    func_0027FE60(0x16);
}

/* 0x00234F60, 0x3F8 bytes. Page 12: four lines (pages 8, 6, 5 and 15); line 3 first asks help
 * message 3 or 4 when func_003F5650 is 0. Cancel goes back. */
void func_00234F60(int player)
{
    int port;
    unsigned short pressed, held;

    if (player == 0)
        port = 0;
    else if (player == 1)
        port = 1;
    else
        return;
    pressed = PAD_PRESSED(port);
    held = PAD_HELD(port);
    if (func_00231100() != 0)
        return;
    if (pressed & BTN_OK) {
        int pages[4];
        int page, i;

        for (i = 0; i < 4; i++)
            pages[i] = g_0040E9D0[i];
        page = pages[g_0074B7C8];
        if (page == 0x0F && func_003F5650() == 0) {
            u32 id;

            if (func_003F5620() == 3)
                id = 3;
            else
                id = func_003F5620() == 4 ? 4 : 5;
            if (id < 5) {
                SE(1);
                func_001AE9F0(0, func_00372BC0(id), 1);
                func_001AFC70(0, port);
                g_0074B730 = 0;
                return;
            }
        }
        SE(1);
        func_002300B0(page);
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else if ((held & BTN_UP) || (pressed & BTN_UP)) {
        int to = (g_0074B7C8 + 3) & 3;

        while (func_00234EF0(func_00234ED0(to)) == 0)
            to = (to + 3) % 4;
        if (to < g_0074B7C8 || (pressed & BTN_UP)) {
            SE(0);
            g_0074B7C8 = to;
        }
    } else if ((held & BTN_DOWN) || (pressed & BTN_DOWN)) {
        int to = (g_0074B7C8 + 1) & 3;

        while (func_00234EF0(func_00234ED0(to)) == 0)
            to = (to + 1) % 4;
        if (g_0074B7C8 < to || (pressed & BTN_DOWN)) {
            SE(0);
            g_0074B7C8 = to;
        }
    }
}

/* 0x00235360, 0xF4 bytes. Page 13: Cancel goes back to page 12. */
void func_00235360(int player)
{
    unsigned short pressed = 0;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    }
}

/* 0x00235460, 0xF4 bytes. Page 14: Cancel goes back to page 12. */
void func_00235460(int player)
{
    unsigned short pressed = 0;

    if (player == 0)
        pressed = PAD_PRESSED(0);
    else if (player == 1)
        pressed = PAD_PRESSED(1);
    if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0x0C);
    }
}

/* 0x00235560, 0x4C bytes, matching. Page 16 set-up. */
void func_00235560(void)
{
    if (g_0074B724 == 0)
        g_0074B7C9 = 0;
    func_0027FE60(0x18);
    if (g_0074B724 == 0)
        func_0027FE60(0x14);
}

/* 0x002355B0, 0x2B8 bytes. Page 16: two lines (pages 17 and 18); Cancel goes back. */
void func_002355B0(int player)
{
    unsigned short pressed = 0, held = 0;

    if (player == 0) {
        pressed = PAD_PRESSED(0);
        held = PAD_HELD(0);
    } else if (player == 1) {
        pressed = PAD_PRESSED(1);
        held = PAD_HELD(1);
    }
    if (pressed & BTN_OK) {
        int pages[2];

        pages[0] = g_0045CDD8[0];
        pages[1] = g_0045CDD8[1];
        SE(1);
        func_002300B0(pages[g_0074B7C9]);
        g_0074B734 = player;
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_002300B0(0);
    } else if ((held & BTN_UP) || (pressed & BTN_UP)) {
        u8 to = (g_0074B7C9 + 1) & 1;

        if (to < g_0074B7C9 || (pressed & BTN_UP)) {
            SE(0);
            g_0074B7C9 = to;
        }
    } else if ((held & BTN_DOWN) || (pressed & BTN_DOWN)) {
        u8 to = (g_0074B7C9 + 1) & 1;

        if (g_0074B7C9 < to || (pressed & BTN_DOWN)) {
            SE(0);
            g_0074B7C9 = to;
        }
    }
}

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
                if (func_0033BD60(func_0034A740(unit)) == 0)
                    func_001A7DC0(TEXT(0x0043C6F0), 0x80, 0);
                else if (g_0074B764 == 1)
                    func_001A7DC0(TEXT(0x0043C84C), 0x80, 0);
                else
                    func_001A7DC0(TEXT(0x0043C848), 0x80, 0);
            } else {
                if (func_0033BD60(func_0034A740(unit)) == 0)
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
