/*
 * scene_pre_battle.c - scene 0x09, before a battle (original source file StatePreBattle.c: its
 * data is loaded with that file name). Decompiled so far: the scene and its last pages
 * (0x00224D70-0x00228174); the menu pages before them (0x00220780-0x00224D60) are not yet.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The pre-battle screen: a menu of pages (g_00749A10: 0 the main menu, 1-13 the pages: officers,
 * items, formation, bodyguards, music...) for the player g_00749A1C, then the loading screen and
 * the battle (scene 4). Empire battles (g_00669F6C = 1) use the screens of scene 0x08 instead.
 * When a movie plays first (func_0032E7B0), the update builds the battle step by step instead.
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
    u8 unknown_0[0x50];
    u8 g_00669DB0;           /* flags: bits 1-3 the music settings */
    u8 unknown_51[0x7];
    int g_00669DB8;          /* game mode (see scene_initialize.c) */
    u8 unknown_5c[0x4];
    int g_00669DC0[5];       /* stage */
    int g_00669DD4[5];       /* battle type of the stage */
    u32 g_00669DE8;          /* player 1's officer */
    u8 unknown_ec[0x44];
    u32 g_00669E30;          /* player 2's officer */
    u8 unknown_134[0x12C];
    u32 g_00669F60;          /* flags (bit 1: two armies) */
    u8 unknown_204[0x8];
    int g_00669F6C;          /* 1: an Empire battle, 0 / 2: a free battle */
    int g_00669F70;          /* how the battle ended (7 = reset) */
    u8 unknown_214[0x24];
    int g_00669F98;          /* battle number in mode 2 */
} g_00669D60;
#define g_00669DB0 (g_00669D60.g_00669DB0)
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669DC0 (g_00669D60.g_00669DC0)
#define g_00669DD4 (g_00669D60.g_00669DD4)
#define g_00669DE8 (g_00669D60.g_00669DE8)
#define g_00669E30 (g_00669D60.g_00669E30)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)
#define g_00669F70 (g_00669D60.g_00669F70)
#define g_00669F98 (g_00669D60.g_00669F98)
#define PLAYER_OFFICER(p) (*(u32 *)((u8 *)&g_00669DE8 + (p) * 0x48))

/* The battle's stage and type (mode 2 plays a series of five). */
#define BATTLE_STAGE() (g_00669DB8 == 2 ? g_00669DC0[g_00669F98 % 5] : g_00669DC0[0])
#define BATTLE_TYPE()  (g_00669DB8 == 2 ? g_00669DD4[g_00669F98 % 5] : g_00669DD4[0])

/* The message boxes' object (0x0068F3E0, see scene_shop.c). */
extern struct {
    u8 unknown_0[0x40D3];
    u8 g_006934B3;           /* box 0 state */
    u8 unknown_40d4[0x127];
    u8 g_006935DB;           /* box 1 state */
    u8 unknown_41fc[0x380];
    u8 g_0069395C;
    u8 unknown_457d;
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_006934B3 (s_0068F3E0.g_006934B3)
#define g_006935DB (s_0068F3E0.g_006935DB)
#define g_0069395C (s_0068F3E0.g_0069395C)
#define g_0069395E (s_0068F3E0.g_0069395E)
#define box1_open() (g_0069395E != 0 && g_0069395E != 0xFF)

/* Controllers (0x88 bytes each at 0x00500700). */
extern u8 g_00500700_bytes[];
#define PAD_READY_N(p) ((g_00500700_bytes[(p) * 0x88 + 0x64] & 1) ? \
                        (g_00500700_bytes[(p) * 0x88 + 0x65] & 1) == 1 : 0)
#define PAD_PRESSED_N(p) ((unsigned short)(PAD_READY_N(p) ? *(unsigned short *)&g_00500700_bytes[(p) * 0x88 + 0x4C] : 0))
#define PAD_REPEAT_N(p) ((unsigned short)(PAD_READY_N(p) ? *(unsigned short *)&g_00500700_bytes[(p) * 0x88 + 0x4E] : 0))
#define BTN_OK     0x40
#define BTN_CANCEL 0x10
#define BTN_EXTRA  0x20
#define BTN_EXTRA2 0x80
#define BTN_LEFT   0x8000
#define BTN_RIGHT  0x2000
#define SE(n) func_0023AD10((n), 0, 0x2CDC, 0x2CDC, 0x1000)

/* The pre-battle state (0x00749A0C-0x00749BBA, after PostBattle's 0x00747930 object). */
/* Globals 0x0043C55C-0x0043C83C: one object in the original (not reached through $gp). */
extern struct {
    const char *g_0043C55C;
    const char *g_0043C560;
    char pad_0[0x44];
    const char *g_0043C5A8;
    const char *g_0043C5AC;
    const char *g_0043C5B0;
    const char *g_0043C5B4;
    const char *g_0043C5B8;
    char pad_1[0x8];
    const char *g_0043C5C4;
    const char *g_0043C5C8;
    const char *g_0043C5CC;
    char pad_2[0x4];
    const char *g_0043C5D4;
    char pad_3[0x60];
    const char *g_0043C638;
    char pad_4[0xB4];
    const char *g_0043C6F0;
    const char *g_0043C6F4;
    char pad_5[0x4];
    const char *g_0043C6FC;
    const char *g_0043C700;
    const char *g_0043C704;
    const char *g_0043C708;
    const char *g_0043C70C;
    const char *g_0043C710;
    const char *g_0043C714;
    const char *g_0043C718;
    char pad_6[0x10];
    const char *g_0043C72C;
    char pad_7[0x30];
    const char *g_0043C760;
    char pad_8[0x40];
    const char *g_0043C7A4;
    char pad_9[0x90];
    const char *g_0043C838;
} s_0043C55C;
#define g_0043C55C (s_0043C55C.g_0043C55C)
#define g_0043C560 (s_0043C55C.g_0043C560)
#define g_0043C5A8 (s_0043C55C.g_0043C5A8)
#define g_0043C5AC (s_0043C55C.g_0043C5AC)
#define g_0043C5B0 (s_0043C55C.g_0043C5B0)
#define g_0043C5B4 (s_0043C55C.g_0043C5B4)
#define g_0043C5B8 (s_0043C55C.g_0043C5B8)
#define g_0043C5C4 (s_0043C55C.g_0043C5C4)
#define g_0043C5C8 (s_0043C55C.g_0043C5C8)
#define g_0043C5CC (s_0043C55C.g_0043C5CC)
#define g_0043C5D4 (s_0043C55C.g_0043C5D4)
#define g_0043C638 (s_0043C55C.g_0043C638)
#define g_0043C6F0 (s_0043C55C.g_0043C6F0)
#define g_0043C6F4 (s_0043C55C.g_0043C6F4)
#define g_0043C6FC (s_0043C55C.g_0043C6FC)
#define g_0043C700 (s_0043C55C.g_0043C700)
#define g_0043C704 (s_0043C55C.g_0043C704)
#define g_0043C708 (s_0043C55C.g_0043C708)
#define g_0043C70C (s_0043C55C.g_0043C70C)
#define g_0043C710 (s_0043C55C.g_0043C710)
#define g_0043C714 (s_0043C55C.g_0043C714)
#define g_0043C718 (s_0043C55C.g_0043C718)
#define g_0043C72C (s_0043C55C.g_0043C72C)
#define g_0043C760 (s_0043C55C.g_0043C760)
#define g_0043C7A4 (s_0043C55C.g_0043C7A4)
#define g_0043C838 (s_0043C55C.g_0043C838)

/* Globals 0x00749A0C-0x00749B69: one object in the original (not reached through $gp). */
extern struct {
    u32 g_00749A0C;                    /* the stage's display object? */
    int g_00749A10;                    /* page */
    int g_00749A14;
    int g_00749A18;                    /* phase: 0 checks, 1 wait, 2 the page */
    int g_00749A1C;                    /* player using the menu */
    void *g_00749A20;
    void *g_00749A24;
    char pad_0[0xC4];
    u8 g_00749AEC;
    u8 g_00749AED;
    u8 g_00749AEE;
    signed char g_00749AEF;
    u8 g_00749AF0;
    u8 g_00749AF1;
    u8 g_00749AF2;
    u8 g_00749AF3;
    u8 g_00749AF4;
    u8 g_00749AF5;
    u8 g_00749AF6;
    u8 g_00749AF7;
    char pad_1[0x1];
    u8 g_00749AF9;
    char pad_2[0x2];
    int g_00749AFC;
    int g_00749B00;
    int g_00749B04;
    int g_00749B08;
    int g_00749B0C;
    char pad_3[0x58];
    signed char g_00749B68;
} s_00749A0C;
#define g_00749A0C (s_00749A0C.g_00749A0C)
#define g_00749A10 (s_00749A0C.g_00749A10)
#define g_00749A14 (s_00749A0C.g_00749A14)
#define g_00749A18 (s_00749A0C.g_00749A18)
#define g_00749A1C (s_00749A0C.g_00749A1C)
#define g_00749A20 (s_00749A0C.g_00749A20)
#define g_00749A24 (s_00749A0C.g_00749A24)
#define g_00749AEC (s_00749A0C.g_00749AEC)
#define g_00749AED (s_00749A0C.g_00749AED)
#define g_00749AEE (s_00749A0C.g_00749AEE)
#define g_00749AEF (s_00749A0C.g_00749AEF)
#define g_00749AF0 (s_00749A0C.g_00749AF0)
#define g_00749AF1 (s_00749A0C.g_00749AF1)
#define g_00749AF2 (s_00749A0C.g_00749AF2)
#define g_00749AF3 (s_00749A0C.g_00749AF3)
#define g_00749AF4 (s_00749A0C.g_00749AF4)
#define g_00749AF5 (s_00749A0C.g_00749AF5)
#define g_00749AF6 (s_00749A0C.g_00749AF6)
#define g_00749AF7 (s_00749A0C.g_00749AF7)
#define g_00749AF9 (s_00749A0C.g_00749AF9)
#define g_00749AFC (s_00749A0C.g_00749AFC)
#define g_00749B00 (s_00749A0C.g_00749B00)
#define g_00749B04 (s_00749A0C.g_00749B04)
#define g_00749B08 (s_00749A0C.g_00749B08)
#define g_00749B0C (s_00749A0C.g_00749B0C)
#define g_00749B68 (s_00749A0C.g_00749B68)

/* Globals 0x00772D34-0x00772D58: one object in the original (not reached through $gp). */
extern struct {
    u8 g_00772D34;
    char pad_0[0x1];
    u8 g_00772D36;
    char pad_1[0x1];
    int g_00772D38;
    int g_00772D3C;
    char pad_2[0x14];
    int g_00772D54;
} s_00772D34;
#define g_00772D34 (s_00772D34.g_00772D34)
#define g_00772D36 (s_00772D34.g_00772D36)
#define g_00772D38 (s_00772D34.g_00772D38)
#define g_00772D3C (s_00772D34.g_00772D3C)
#define g_00772D54 (s_00772D34.g_00772D54)

/* The menu camera (0x007A1B70): a target that moves from `target` to `target_to` over `frames`,
 * the camera itself at +0x50 (func_002EBD80 / func_002EBAA0), distance limits, and defaults. */
extern struct {
    float g_007A1B70[4];     /* target */
    float g_007A1B80[4];     /* target to reach */
    u8 unknown_20[0x14];
    u32 g_007A1BA4;
    u32 g_007A1BA8;          /* frames to reach it */
    u8 unknown_3c[0x14];
    u8 g_007A1BC0[0x50];     /* the camera (+0x10 a vector, +0x38 its frames) */
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
#define g_007A1BD0 ((float *)(g_007A1BC0 + 0x10))
#define g_007A1BF8 (*(u32 *)(g_007A1BC0 + 0x38))
#define g_007A1C10 (s_007A1B70.g_007A1C10)
#define g_007A1C14 (s_007A1B70.g_007A1C14)
#define g_007A1C18 (s_007A1B70.g_007A1C18)
#define g_007A1C1C (s_007A1B70.g_007A1C1C)
#define g_007A1C20 (s_007A1B70.g_007A1C20)
#define g_007A1C24 (s_007A1B70.g_007A1C24)
#define g_007A1C28 (s_007A1B70.g_007A1C28)
#define g_007A1DF0 (s_007A1B70.g_007A1DF0)
#define g_007A1E00 (s_007A1B70.g_007A1E00)
#define g_007A1E30 (s_007A1B70.g_007A1E30)
#define g_007A1E34 (s_007A1B70.g_007A1E34)

extern u8 g_00749A28[2][0x52];            /* per player: items */
extern u8 g_00749530[], g_007496F0[], g_007499EC[], g_00749ACC[], g_00749AD8[], g_00749AE4[];
extern u8 g_00749B10[0x5C];
/* Page 10 (0x00749B6C, 0x2A bytes): mode, cursor, ..., the list at +6, its count at +0x25. */
extern u8 g_00749B6C[0x2A];
#define g_00749B91 (g_00749B6C[0x25])
/* Page 11 (0x00749B96, 8 bytes): the formation. */
extern u8 g_00749B96[8];
/* Page 12 (0x00749B9E, 0x18 bytes). */
extern struct {
    u8 g_00749B9E;           /* 0 choosing a slot, 1 choosing a value */
    u8 g_00749B9F;           /* slot */
    u8 g_00749BA0;           /* value cursor */
    u8 g_00749BA1[5];        /* values (0xFF = none) */
    u8 g_00749BA6[5];        /* values before the edit */
    u8 g_00749BAB[9];
    u8 g_00749BB4;           /* values available */
    u8 g_00749BB5;           /* changed */
} s_00749B9E;
#define g_00749B9E (s_00749B9E.g_00749B9E)
#define g_00749B9F (s_00749B9E.g_00749B9F)
#define g_00749BA0 (s_00749B9E.g_00749BA0)
#define g_00749BA1 (s_00749B9E.g_00749BA1)
#define g_00749BA6 (s_00749B9E.g_00749BA6)
#define g_00749BAB (s_00749B9E.g_00749BAB)
#define g_00749BB4 (s_00749B9E.g_00749BB4)
#define g_00749BB5 (s_00749B9E.g_00749BB5)
/* Page 13, the music (0x00749BB6). */
extern struct {
    u8 g_00749BB6;           /* cursor (0-2) */
    u8 g_00749BB7;           /* on / off */
    u8 g_00749BB8;           /* music track */
    u8 g_00749BB9;           /* track playing */
    u8 g_00749BBA;           /* playing */
} s_00749BB6;
#define g_00749BB6 (s_00749BB6.g_00749BB6)
#define g_00749BB7 (s_00749BB6.g_00749BB7)
#define g_00749BB8 (s_00749BB6.g_00749BB8)
#define g_00749BB9 (s_00749BB6.g_00749BB9)
#define g_00749BBA (s_00749BB6.g_00749BBA)
extern const char g_00429EA0[];           /* "StatePreBattle.c" */

/* Tables of the battle types (0x00442EA0-0x00443640). */
extern u8 g_00442EA0[][0x10];              /* camera directions per battle type */
extern float g_00443290[][4];              /* camera targets per battle type */
extern struct { float a, b, c; } g_00443530[];   /* camera distances per battle type */
extern struct { float a, b; } g_00443630[];  /* distance ranges per battle type */
extern void (*g_0040DF40[3])(void);       /* page 10 handlers */
extern void (*g_0040DF50[3])(int pad);    /* page 13 handlers (the last one empty) */

/* Help lines. */

/* Small data ($gp). */
extern void (*g_0045CD70[2])(int pad);    /* page 12 handlers */
extern u8 *g_0045D2C0;
extern int g_0045D494;                    /* step of the build-up (movie first) */
extern int g_0045D498;                    /* its frame count */
extern int g_0045D49C;                    /* 1 while the loading screen is open */
extern u8 *g_0045D670;

void func_0023AD10(int a, int b, int c, int d, int e);
u8 func_00362C80(int side);
u8 func_00362D70(int side);
int func_00362D10(int side, u8 value);
void func_00362C50(int side, int value);
void func_002C5220(int pad, u8 *cursor, u8 *stored, int count, int count2);
void func_00220970(int page);
int func_0029D220(u8 *state);
void func_00362BD0(int side, int slot, int value);
u32 func_0029D200(u8 *state);
void func_00118AC0(void *dst, const void *src, int size);
void func_00118850(void *p, int size);
int func_0029D210(u8 *state);
u8 func_00362BB0(void);
void func_0017DE50(void);
void func_0017E060(int track);
int func_0017DC00(u8 track);
int func_0017DC30(void);
u8 func_0017DC50(u8 track, int step);
void func_00362B90(u8 track);
void func_0017DF10(void);
void func_002CAD60(u8 *data);
void func_0028F860(u8 *data);
void func_0028EFC0(u8 *data);
void func_0028F4C0(u8 *data);
void func_002EBE40(void);
void func_002EBD80(float distance, u8 *camera, const void *direction);
void func_002EBAA0(float distance, u8 *camera, const void *direction, int frames);
void func_0028D5D0(int value);
void func_002C59F0(void);
void func_002C5A30(void);
u32 func_00328330(u32 i);
u32 func_0036F600(u32 a);
u32 func_0036F610(u32 i);
int func_00362B60(int side);
int func_003A01A0(u32 a);
int func_0036D2E0(void);
u32 func_003F73E0(u32 i);
void func_0029D1F0(u8 *state, int index, u32 value);
void func_00221890(void);
void func_002CAC30(u8 *items, u32 officer);
void func_00223B60(u8 *data);
void func_00103000(int value);
void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_002D6890(void);
void func_0028F960(u8 *data);
void func_003E4280(void);
void func_00101470(int value);
void func_003F1580(void);
void func_002F15E0(u32 a, int stage);
void func_001B8F60(int a, int b, int c);
int func_0032E7B0(void);
int func_0017DDA0(void);
void func_003DD9A0(void);
void func_001D42E0(void);
void func_00235A70(void);
void func_003E3D70(void);
void func_00376490(u32 a, int b);
int func_0036D310(void);
u32 func_00363B90(void);
int func_003EF0D0(u32 a);
void func_00376100(int a, int b, int c);
int func_00102960(int value);
void func_00103000(int value);
void func_0019B4F0(int side, int b);
void func_0019BD90(int side);
void func_0028FB40(u8 *data);
void func_002D68F0(void);
void func_00102EC0(void *data);
void func_003E42D0(void);
void func_00235F70(void);
void func_002F1660(void);
int func_00221950(int player);
void func_002209E0(void);
int func_00221AB0(int player);
void func_00221F70(int player);
void func_00222450(int player);
void func_00223090(int player);
void func_00223120(int player);
void func_00223220(int player);
void func_00223600(int player);
void func_00223BB0(int player);
void func_0019F410(void);
void func_0035ED20(void);
void func_003635A0(void);
void func_0035FD10(void);
void func_00213F40(int stage);
void func_001C77D0(int value);
void func_0018C500(void);
void func_00216B40(void);
void func_00194010(void);
void func_001BE1A0(void);
void func_00185CA0(void);
void func_0022E150(void);
void func_0020EBB0(void);
void func_00221710(int value);
void func_002F16B0(void);
void func_00376450(void);
int func_003F1400(int value);
int func_00235FC0(float dt);
void func_002EC0A0(void);
void func_00236430(void);
void func_00291650(void *data, int a);
u8 *func_001050F0(void);
void func_00105390(u8 *packet);
u8 *func_00105410(void);
void func_00105560(u8 *packet);
int func_002ECA70(void);
int func_002EC150(void);
void func_00195C20(void);
void func_001FCC50(void);
void func_002937E0(u8 *a, u8 *b);
void func_00292A90(u8 *a);
void func_001FCC90(void);
void func_002944D0(void);
void func_0029B900(void *a, u8 *b, u8 *c, u8 *d, int *e);
void func_0029BBC0(void *a, u8 *b, void *c, u8 d, int e, u8 *f);
void func_0029C690(u8 *a, u8 *b, int c);
void func_0029CC10(int a, u8 *b, u8 *c);
void func_0029CC70(u32 officer);
void func_0029BEC0(void *a, u8 *b, u8 c, int d, u8 *e);
void func_0029C140(u32 officer, u8 b, int c);
void func_0029C460(void *a, void *b, u8 c, int d, u8 *e);
void func_0029CEB0(int a, u8 *b, u8 *c, void *d);
void func_0029D310(int a, u8 *b, u8 *c, void *d);
void func_0029D520(int a, u8 *b, u8 *c, void *d);
void func_0029D6F0(u8 *a);
void func_00290CE0(void *a, u32 b, int c, int d, int e);
void func_003764B0(void);
int func_003F1160(int value);
void func_001A7DC0(const char *text, int alpha, int b);
int func_00328A60(int officer);
int func_0036D780(void);
int func_002208D0(u32 officer);
u32 func_002F6A60(u32 officer);
int func_0036DBA0(u32 officer, u32 item);
int func_002F4900(u32 officer, u32 item);
u32 func_0029A5C0(void);
const char *func_003725A0(int id);
void func_003838B0(const char *text, int b);
void func_003F11D0(void);
void func_00236450(void);
void func_002F16D0(void);
void func_001D1E80(void);

/* ---- The menu and its first pages (0x00220780-0x00224D60) ------------------------------------- */

extern u8 g_007499E9;                     /* unit shown on page 3 */
extern u8 g_0073DCA3[];                   /* player records, 0x290 bytes (+0: bit 2 a flag) */
extern int g_00772D4C;
extern int g_00799A68;
extern u32 g_00429E60[];                  /* main menu entries: what each one opens */
extern int g_0040DF10[7];                 /* main menu entries 0-6: their page */
extern u8 g_00442FF0[][0x10], g_00443140[][0x10];      /* camera directions of pages 2 and 3 */
extern float g_004433E0[][4];             /* camera targets of page 2 */
extern float g_004436D8, g_004436DC;      /* distance range of page 2 */
extern const char *g_0043C3EC;            /* "You do not have any mounts." */

#define g_00749AE8 (g_00749AE4[4])        /* non-zero: the player has mounts */
#define PLAYER_CURSOR(p) ((&g_00749AEC)[p])            /* main menu cursor per player */
#define PLAYER_READY(p) ((&g_00749B08)[p])             /* two armies: player ready */

int func_00362570(void);
u32 func_0033F7D0(int a, int b);
u8 *func_0035DEC0(u32 officer, int i);
void func_0017DEA0(int value);
float (*func_001942C0(void))[4];
void func_002EC0C0(u8 *camera, int mode);
void func_001911A0(float *out, u8 *pos);
void func_003DCA30(void);
u32 func_00290C10(void);
u32 func_00290C90(int page);
int func_003F1070(int value);
int func_0035F440(void);
void func_002ECB80(int pad);
int func_00328B00(int officer);
void func_00328AA0(int officer, int value);
void func_001AE9F0(int box, const char *text, int a);
void func_001AFC70(int box, int pad);
void func_00223100(void);
void func_00224DD0(void);
void func_00224DF0(void);
void func_00225130(void);
void func_002254F0(void);

#define LEAVE_IF_NONE(scene) do {                                       \
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)                   \
            g_0045D89C = (scene);                                       \
    } while (0)

/* 0x00220780, 0x68 bytes. Non-zero when page 10 is offered: not in battle types 6-0x12, and
 * with entries. */
int func_00220780(void)
{
    u32 type = func_00362570();

    if (type >= 6 && type <= 0x0F)
        return 0;
    if (type >= 0x10 && type <= 0x12)
        return 0;
    return g_00749B91 != 0;
}

/* 0x002207F0, 0xC4 bytes. Non-zero when page 11 / 12 is offered: not in battle types 6-0x12,
 * with values (or 2 formations in an Empire battle), and func_0033F7D0 at least 3. */
int func_002207F0(void)
{
    u32 type = func_00362570();

    if (type >= 6 && type <= 0x0F)
        return 0;
    if (type >= 0x10 && type <= 0x12)
        return 0;
    if (func_0036D2E0() == 0) {
        if (g_00749BB4 == 0)
            return 0;
    } else if (func_00362D70(0) < 2) {
        return 0;
    }
    return func_0033F7D0(0, 1) < 3 ? 0 : 1;
}

/* 0x002208C0, 0x10 bytes. */
int func_002208C0(void)
{
    return g_00749AE8 != 0;
}

/* 0x002208D0, 0x9C bytes. How many of `officer`'s four records (func_0035DEC0) are set (first
 * byte below 0x7F). */
int func_002208D0(u32 officer)
{
    int i, n = 0;

    for (i = 0; i < 4; i++) {
        u8 rec[20];
        u8 *src = func_0035DEC0(officer, i);
        int k;

        for (k = 0; k < 20; k++)
            rec[k] = src[k];
        if (rec[0] < 0x7F)
            n++;
    }
    return n;
}

/* 0x00220970, 0x6C bytes. Requests page `page` (applied by func_002209E0); 14 also stops the
 * music and fades out, 15 stops it. */
void func_00220970(int page)
{
    g_00749A18 = 1;
    g_00749A14 = page;
    if (page == 0x0E) {
        func_0017DF10();
        func_001B8F60(0, 6, 8);
    }
    if (page == 0x0F)
        func_0017DEA0(1);
}

/* Starts a camera move to `target` over 15 frames with a distance range (inlined). */
#define CAMERA_TARGET(t) do {                   \
        g_007A1B80[0] = (t)[0];                 \
        g_007A1B80[1] = (t)[1];                 \
        g_007A1B80[2] = (t)[2];                 \
        g_007A1B80[3] = (t)[3];                 \
        g_007A1BA8 = 0x0F;                      \
    } while (0)

/* 0x002209E0, 0xD24 bytes. Applies the requested page (g_00749A14): resets the camera to the
 * map's default view, then sets up the page (its camera, its window layers through
 * func_0028D5D0, its cursor); 14 leaves for the requested scene (the battle), 15 leaves and frees
 * the battle. */
void func_002209E0(void)
{
    float (*box)[4] = func_001942C0();
    float dir[4], len;
    int current;
    int i;

    func_002C59F0();
    func_002C5A30();
    g_007A1C20 = 0;
    g_007A1C14 = g_007A1E34;
    g_007A1BA4 = 0;
    g_007A1C10 = g_007A1E30;
    g_007A1B70[0] = g_007A1E00[0];
    g_007A1B70[1] = g_007A1E00[1];
    g_007A1B70[2] = g_007A1E00[2];
    g_007A1B70[3] = g_007A1E00[3];
    for (i = 0; i < 4; i++)                       /* (VU0) the eye's direction and distance */
        dir[i] = g_007A1DF0[i] - g_007A1E00[i];
    len = __builtin_sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    for (i = 0; i < 4; i++)
        dir[i] = dir[i] * (1.0f / len);
    func_002EBD80(len, g_007A1BC0, dir);
    func_002EBAA0(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()], 0x0F);
    current = g_0045D898;
    g_00749AF0 = 0;
    switch (g_00749A14) {
    case 0:                                       /* the main menu */
        func_0028D5D0(8);
        g_007A1C28 = 2;
        g_007A1C1C = g_00443630[BATTLE_TYPE()].b;
        g_007A1C18 = g_00443630[BATTLE_TYPE()].a;
        g_007A1C24 = 0x0F;
        CAMERA_TARGET(g_00443290[BATTLE_TYPE()]);
        func_002EBAA0(g_00443530[BATTLE_TYPE()].a, g_007A1BC0, g_00442EA0[BATTLE_TYPE()], 0x0F);
        g_00749B00 = 1;
        if (g_00749A10 == 2)
            g_007A1C28 = 0;
        else
            func_002EC0C0(g_007A1BC0, 2);
        func_00221890();
        break;
    case 1:
        func_0028D5D0(10);
        if (g_00749A10 == 0)
            func_0028D5D0(1);
        if (g_00749A10 == 0)
            func_0028D5D0(7);
        if (g_00749A10 < g_00749A14)
            g_00749AEE = 0;
        break;
    case 2:
        g_007A1C28 = 0;
        g_007A1C24 = 0x0F;
        g_007A1C1C = g_004436DC;
        g_007A1C18 = g_004436D8;
        CAMERA_TARGET(g_004433E0[BATTLE_TYPE()]);
        func_002EBAA0(g_00443530[BATTLE_TYPE()].b, g_007A1BC0, g_00442FF0[BATTLE_TYPE()], 0x0F);
        func_0028D5D0(0x16);
        if (g_00749A10 == 0) {
            func_0028D5D0(1);
            func_0028D5D0(7);
        }
        g_00772D4C = g_00749A1C;
        g_00749B00 = 1;
        break;
    case 3:
        g_00749AF2 = 0;
        g_00749AF1 = 0;
        g_00749AF5 = 0;
        if (g_0073DCA3[g_00749A1C * 0x290] & 4) {
            float centre[4];

            g_007A1C18 = 2048.0f;
            g_007A1C24 = 0x0F;
            g_007A1C1C = 2020.0f;
            for (i = 0; i < 4; i++)               /* (VU0) the middle of the map's box */
                centre[i] = (box[0][i] + box[1][i]) * 0.5f;
            CAMERA_TARGET(centre);
            g_007A1BF8 = 0x0F;
            g_007A1BD0[0] = ((float *)g_00443140[BATTLE_TYPE()])[0];
            g_007A1BD0[1] = ((float *)g_00443140[BATTLE_TYPE()])[1];
            g_007A1BD0[2] = ((float *)g_00443140[BATTLE_TYPE()])[2];
            g_007A1BD0[3] = ((float *)g_00443140[BATTLE_TYPE()])[3];
            func_002EC0C0(g_007A1BC0, 1);
        } else {
            u8 *unit = *(u8 **)(g_00749530 + 0x340 + g_007499E9 * 0x78);
            float pos[4];

            g_007A1C28 = 1;
            g_007A1C24 = 0x0F;
            g_007A1C18 = 2048.0f;
            g_007A1C1C = 2048.0f;
            func_001911A0(pos, (*(u32 *)(unit + 0x80) & 0x20000) ? unit + 0x30 : unit + 0x28);
            CAMERA_TARGET(pos);
            func_002EBAA0(g_00443530[BATTLE_TYPE()].c, g_007A1BC0, g_00443140[BATTLE_TYPE()], 0x0F);
            func_002EC0C0(g_007A1BC0, 1);
        }
        g_00749B00 = 1;
        g_00772D4C = g_00749A1C;
        func_0028D5D0(0x18);
        if (g_00749A10 == 0) {
            func_0028D5D0(1);
            func_0028D5D0(7);
        }
        func_00223100();
        break;
    case 4:
        func_0028D5D0(0x1A);
        if (g_00749A10 == 0) {
            func_0028D5D0(1);
            func_0028D5D0(7);
        }
        break;
    case 5:
        func_0028D5D0(0x1C);
        if (g_00749A10 == 1)
            func_0028D5D0(2);
        break;
    case 6:
        func_0028D5D0(0x10);
        func_0028D5D0(2);
        g_00749AF0 = g_00749A28[g_00749A1C][0x51];
        g_00749AEF = -1;
        break;
    case 7: {                                     /* items: the equipped one, or the first usable */
        u32 officer = PLAYER_OFFICER(g_00749A1C);
        u32 item;

        g_00799A68 = g_00749A1C;
        func_0028D5D0(0x0C);
        func_0028D5D0(2);
        item = func_002F6A60(officer);
        if (func_0036DBA0(officer, item) < 1 || func_002F4900(officer, item) == 0) {
            g_00749AF0 = 0;
            for (i = 0; i < 0x28; i++)
                if (func_0036DBA0(officer, i) > 0 && func_002F4900(officer, i) != 0) {
                    g_00749AF0 = (u8)i;
                    break;
                }
        } else {
            g_00749AF0 = 0xFF;
        }
        break;
    }
    case 9:                                       /* mounts: the current one */
        func_0028D5D0(0x14);
        func_0028D5D0(2);
        if (g_00749AE4[5 + g_00749A1C] < 4) {
            for (i = 0; i < 4; i++)
                if (g_00749AE4[5 + g_00749A1C] == g_00749AE4[i])
                    break;
            g_00749AF0 = (u8)i;
        } else {
            g_00749AF0 = 0;
        }
        break;
    case 10:
        func_0028D5D0(10);
        func_0028D5D0(1);
        func_0028D5D0(7);
        func_00224DD0();
        break;
    case 11:
        func_0028D5D0(1);
        func_0028D5D0(7);
        func_0028D5D0(5);
        func_00224DF0();
        break;
    case 12:
        func_0028D5D0(1);
        func_0028D5D0(7);
        func_0028D5D0(4);
        func_00225130();
        break;
    case 13:
        func_0028D5D0(1);
        func_0028D5D0(7);
        func_0028D5D0(3);
        func_002254F0();
        break;
    case 14:                                      /* to the battle */
        if (g_00669F6C != 1)
            func_003DCA30();
        GO_TO_NEXT_SCENE();
        break;
    case 15:                                      /* leave without fighting */
        SWITCH_SCENE();
        g_0045D894 = current;
        func_001D1E80();
        break;
    }
    g_00749A10 = g_00749A14;
    func_00376100(0, func_00290C10(), func_00290C90(g_00749A10));
}

/* 0x00221710, 0xFC bytes. Player `player` is ready: with one army (or both ready) on to the
 * battle (page 14, scene 4). */
void func_00221710(int player)
{
    if ((g_00669F60 & 2) == 0) {
        LEAVE_IF_NONE(4);
        func_00220970(0x0E);
    } else if (PLAYER_READY((player + 1) % 2) == 0) {
        if (PLAYER_READY(player) == 0)
            PLAYER_READY(player) = 1;
    } else {
        LEAVE_IF_NONE(4);
        func_00220970(0x0E);
    }
}

/* 0x00221810, 0x8 bytes, matching. Main menu entries. */
int func_00221810(void)
{
    return 7;
}

/* 0x00221820, 0x18 bytes, matching. What main menu entry `i` opens. */
u32 func_00221820(int i)
{
    return g_00429E60[i];
}

/* 0x00221840, 0x48 bytes. Whether an entry is offered (2: page 11 / 12, 1: page 10, else yes). */
int func_00221840(u32 what)
{
    if (what == 2)
        return func_002207F0();
    if (what == 1)
        return func_00220780();
    return 1;
}

/* 0x00221890, 0xB8 bytes. Moves both players' main menu cursors to an offered entry. */
void func_00221890(void)
{
    int count = func_00221810();
    int p;

    if (count <= 0)
        return;
    for (p = 0; p < 2; p++) {
        u32 i = PLAYER_CURSOR(p);

        while (func_00221840(func_00221820(i)) == 0)
            i = (i + 1) % count;
        PLAYER_CURSOR(p) = (u8)i;
    }
}

/* Shows message `id` (func_003F1070) and asks for a re-check afterwards (inlined, four times). */
#define CHECK_MESSAGE(id) (func_003F1070(id) != 0 ?                                     \
    (g_00772D34 = g_00772D36, g_00772D38 = 0, g_00772D3C = 1, 1) : 0)

/* 0x00221950, 0x15C bytes. Before the menu of an Empire battle: the warnings (messages 0x16,
 * 6, 0x0D, 0x0E) that still have to be shown. Returns 1 while one is shown. */
int func_00221950(int player)
{
    if (func_0036D2E0() == 0)
        return 0;
    if (CHECK_MESSAGE(0x16))
        return 1;
    if (func_0036D780() != 0 && CHECK_MESSAGE(6))
        return 1;
    if (func_002208C0() != 0 && g_00749AE4[5 + player] > 3 && CHECK_MESSAGE(0x0D))
        return 1;
    if (func_0035F440() == 0 && (func_00220780() != 0 || func_002207F0() != 0) &&
        CHECK_MESSAGE(0x0E))
        return 1;
    return 0;
}

/* 0x00221AB0, 0x48C bytes. Page 0, the main menu, for player `player`: Up / Down move among the
 * offered entries (repeating; wrapping only on a new press), OK opens the entry's page (or
 * declares the player ready: entry 6), Start goes to "ready" directly. With two armies a ready
 * player only can cancel (Cancel). Returns 1 when something happened. */
int func_00221AB0(int player)
{
    int port = 0;
    unsigned short pressed, repeat;
    int count;
    u8 *cursor;
    u32 what;

    if (player == 0)
        port = 0;
    else if (player == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    repeat = PAD_REPEAT_N(port);
    count = func_00221810();
    cursor = &PLAYER_CURSOR(player);
    what = func_00221820(*cursor);
    if ((g_00669F60 & 2) != 0 && PLAYER_READY(player) == 1) {
        if ((pressed & BTN_CANCEL) == 0)
            return 0;
        PLAYER_READY(player) = 0;
        SE(2);
        return 1;
    }
    if (pressed & BTN_OK) {
        if (what <= 5) {
            int pages[7];
            int page;

            for (page = 0; page < 7; page++)
                pages[page] = g_0040DF10[page];
            page = pages[what];
            if (page == 0x0B && func_0036D2E0() == 0 && g_00749BB4 != 0)
                page = 0x0C;
            SE(1);
            func_00220970(page);
            g_00749A1C = player;
            return 1;
        }
        if (what == 6) {
            SE(1);
            func_00221710(player);
            g_00749A1C = player;
            return 1;
        }
    } else if ((pressed & BTN_CANCEL) == 0) {
        if (pressed & 0x800) {                    /* Start: ready */
            if (what == 6) {
                SE(1);
                func_00221710(player);
                return 1;
            }
            SE(0);
            *cursor = (u8)(count - 1);
            return 1;
        }
        if ((repeat & 0x1000) || (pressed & 0x1000)) {
            int i = (*cursor + count - 1) % count;

            while (func_00221840(func_00221820(i)) == 0)
                i = (i + count - 1) % count;
            if (i < *cursor || (pressed & 0x1000)) {
                SE(0);
                *cursor = (u8)i;
            }
        } else if ((repeat & 0x4000) || (pressed & 0x4000)) {
            int i = (*cursor + 1) % count;

            while (func_00221840(func_00221820(i)) == 0)
                i = (i + 1) % count;
            if (*cursor < i || (pressed & 0x4000)) {
                SE(0);
                *cursor = (u8)i;
            }
        }
    }
    func_002ECB80(port);
    return 0;
}

/* 0x00221F40, 0x2C bytes. Whether line `line` of page 1 is offered (11: only with mounts). */
int func_00221F40(int line)
{
    if (line == 0x0B)
        return func_002208C0();
    return 1;
}

/* 0x00221F70, 0x4DC bytes. Page 1, the officer (four lines: equipment 6, items 7, mounts 9,
 * bodyguards 5; line 1 needs mounts). The extra button switches the officer's costume (an
 * officer below 0x1C with more than one costume). Cancel goes back. */
void func_00221F70(int player)
{
    int port = 0;
    unsigned short pressed, repeat;

    if (player == 0)
        port = 0;
    else if (player == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    repeat = PAD_REPEAT_N(port);
    if (pressed & BTN_OK) {
        if (g_00749AEE == 3) {
            SE(1);
            func_00220970(5);
        } else if (g_00749AEE == 1) {
            if (g_00749AE8 == 0) {
                SE(4);
                func_001AE9F0(0, g_0043C3EC, 1);
                func_001AFC70(0, port);
            } else {
                SE(1);
                func_00220970(9);
            }
        } else if (g_00749AEE == 2) {
            SE(1);
            func_00220970(7);
        } else if (g_00749AEE == 0) {
            SE(1);
            func_00220970(6);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00220970(0);
    } else if (pressed & BTN_EXTRA) {
        int officer = PLAYER_OFFICER(player);

        if (officer >= 0 && officer < 0x19F) {
            if (officer < 0x1C) {
                u32 costume = (func_00328B00(officer) + 1) % 2;

                if (func_00328A60(officer) < (int)costume)
                    costume = 0;
                if (costume == (u32)func_00328B00(officer)) {
                    SE(4);
                } else {
                    SE(1);
                    func_00328AA0(officer, costume);
                }
            } else {
                SE(4);
            }
        }
    } else if ((repeat & 0x1000) || (pressed & 0x1000)) {
        u32 i = (g_00749AEE + 3) & 3;

        while (func_00221F40(i + 10) == 0)
            i = (i + 3) & 3;
        if ((int)i < (int)g_00749AEE || (pressed & 0x1000)) {
            SE(0);
            g_00749AEE = (u8)i;
        }
    } else if ((repeat & 0x4000) || (pressed & 0x4000)) {
        u32 i = (g_00749AEE + 1) & 3;

        while (func_00221F40(i + 10) == 0)
            i = (i + 1) & 3;
        if ((int)g_00749AEE < (int)i || (pressed & 0x4000)) {
            SE(0);
            g_00749AEE = (u8)i;
        }
    }
}

/* 0x00224D70, 0x54 bytes. Page 10: runs the handler of its mode (g_00749B6C[0], 0-2). */
void func_00224D70(void)
{
    void (*handlers[3])(void);

    handlers[0] = g_0040DF40[0];
    handlers[1] = g_0040DF40[1];
    handlers[2] = g_0040DF40[2];
    handlers[g_00749B6C[0]]();
}

/* 0x00224DD0, 0x1C bytes. */
void func_00224DD0(void)
{
    g_00749B6C[0] = 0;
    g_00749B6C[1] = 0;
    g_00749B6C[2] = 0;
    g_00749B6C[3] = 0;
}

/* 0x00224DF0, 0x24 bytes. Page 11: starts on side 0's formation. */
void func_00224DF0(void)
{
    g_00749B96[0] = func_00362C80(0);
}

/* 0x00224E20, 0x184 bytes. Page 11, the formation (controller `pad`): the cursor moves among
 * func_00362D70's entries; OK picks an allowed one, Cancel goes back to the main menu. */
void func_00224E20(int pad)
{
    int port = 0;
    unsigned short pressed;
    u8 count, current, cursor;

    if (pad == 0)
        port = 0;
    else if (pad == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    count = func_00362D70(0);
    current = g_00749B96[0];
    cursor = current;
    if (pressed & BTN_OK) {
        if (func_00362D10(0, g_00749B96[0]) == 0) {
            SE(4);
        } else {
            SE(1);
            func_00362C50(0, current);
            func_00220970(0);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00220970(0);
    } else {
        func_002C5220(port, &cursor, &g_00749B96[0], count, count);
    }
}

/* 0x00224FB0, 0x18 bytes, matching. Page 12: back to choosing a slot (the cursor to 0 when `reset`). */
void func_00224FB0(int reset)
{
    u8 *page = (u8 *)&s_00749B9E;

    if (reset != 0)
        page[1] = 0;
    page[0] = 0;
}

/* 0x00224FD0, 0x1C bytes, matching. Page 12: choosing a value (its cursor to 0 when `reset`). */
void func_00224FD0(int reset)
{
    u8 *page = (u8 *)&s_00749B9E;

    if (reset != 0)
        page[2] = 0;
    page[0] = 1;
}

/* 0x00224FF0, 0x108 bytes. Page 12 done: writes the chosen values to side 0's slots, in order
 * of value, then the end marker (at most 5). */
void func_00224FF0(void)
{
    u32 slot, value, i;

    if (func_0029D220(&g_00749B9E) == 0)
        return;
    for (slot = 0; slot < 6; slot++)
        func_00362BD0(0, slot, 10);
    slot = 0;
    for (value = 1; value < 10; value++)
        for (i = 0; i < 5; i++)
            if (g_00749BA1[i] < g_00749BB4 && value == func_0029D200(&g_00749B9E)) {
                func_00362BD0(0, slot, value);
                slot++;
            }
    if (slot > 5)
        slot = 5;
    func_00362BD0(0, slot, 0);
    func_00362C50(0, slot);
}

/* 0x00225100, 0x2C bytes. Page 12: undoes the edit. */
void func_00225100(void)
{
    func_00118AC0(g_00749BA1, g_00749BA6, 5);
}

/* 0x00225130, 0x38 bytes. Page 12: starts an edit. */
void func_00225130(void)
{
    g_00749BB5 = 0;
    func_00118AC0(g_00749BA6, g_00749BA1, 5);
    func_00224FB0(1);
}

/* 0x00225170, 0x200 bytes. Page 12, choosing a slot: OK edits it (or with the list done, writes
 * everything and goes to page 11), the second extra button clears it, Cancel undoes the edit. */
void func_00225170(int pad)
{
    u8 cursor = g_00749B9F;
    unsigned short pressed;
    int port = pad;

    if (pad == 0)
        port = 0;
    else if (pad == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    if (pressed & BTN_OK) {
        if (func_0029D210(&g_00749B9E) == 0) {
            SE(1);
            func_00224FD0(1);
        } else {
            SE(1);
            func_00224FF0();
            func_00220970(0x0B);
        }
    } else if (pressed & BTN_CANCEL) {
        func_00225100();
        SE(2);
        func_00220970(0);
    } else if (pressed & BTN_EXTRA2) {
        if (func_0029D210(&g_00749B9E) == 0 && g_00749BA1[g_00749B9F] < 9) {
            SE(2);
            g_00749BA1[g_00749B9F] = 0xFF;
            g_00749BB5 = 1;
        } else {
            SE(4);
        }
    } else {
        func_002C5220(port, &cursor, &g_00749B9F, 6, 6);
    }
}

/* 0x00225370, 0x13C bytes. Page 12, choosing a value for the slot: OK stores it. */
void func_00225370(int pad)
{
    u8 cursor = g_00749BA0;
    unsigned short pressed;
    int port = pad;

    if (pad == 0)
        port = 0;
    else if (pad == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    if (pressed & BTN_OK) {
        SE(1);
        g_00749BA1[g_00749B9F] = g_00749BA0;
        func_00224FB0(0);
        g_00749BB5 = 1;
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00224FB0(0);
    } else {
        func_002C5220(port, &cursor, &g_00749BA0, g_00749BB4, g_00749BB4);
    }
}

/* 0x002254B0, 0x40 bytes. Page 12: runs the handler of its mode. */
void func_002254B0(int pad)
{
    void (*handlers[2])(int pad);

    handlers[0] = g_0045CD70[0];
    handlers[1] = g_0045CD70[1];
    handlers[g_00749B9E](pad);
}

/* 0x002254F0, 0x70 bytes. Page 13, the music: starts the current track. */
void func_002254F0(void)
{
    g_00749BB6 = 0;
    g_00749BB7 = ((g_00669DB0 & 0xF) >> 1) == 1;
    g_00749BB8 = func_00362BB0();
    g_00749BB9 = func_00362BB0();
    g_00749BBA = 1;
    func_0017DE50();
    func_0017E060(g_00749BB8);
}

/* 0x00225560, 0x140 bytes. Page 13, the on / off line: Left / Right switch it. */
void func_00225560(int pad, int port)
{
    u8 on = g_00749BB7;
    unsigned short pressed;

    if (pad == 0)
        port = 0;
    else if (pad == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    if (pressed & BTN_OK)
        return;
    if (pressed & BTN_LEFT) {
        SE(0);
        g_00749BB7 = (on + 1) & 1;
    } else if (pressed & BTN_RIGHT) {
        SE(0);
        g_00749BB7 = (on + 3) & 1;
    }
}

/* 0x002256A0, 0x240 bytes. Page 13, the track line: Left / Right change the track (repeating;
 * at the ends only on a new press); OK plays it. */
void func_002256A0(int pad)
{
    u8 track = g_00749BB8;
    int index = func_0017DC00(g_00749BB8);
    int count = func_0017DC30();
    int port = 0;
    unsigned short pressed, repeat;

    if (pad == 0)
        port = 0;
    else if (pad == 1)
        port = 1;
    pressed = PAD_PRESSED_N(port);
    repeat = PAD_REPEAT_N(port);
    if (pressed & BTN_OK) {
        g_00749BB9 = track;
        func_0017DE50();
        func_0017E060(track);
        g_00749BBA = 1;
    } else if (repeat & BTN_LEFT) {
        if (index >= 1) {
            SE(0);
            track = func_0017DC50(track, -1);
        } else if (pressed & BTN_LEFT) {
            SE(0);
            track = func_0017DC50(track, -1);
        }
    } else if (repeat & BTN_RIGHT) {
        if (index < count - 1) {
            SE(0);
            track = func_0017DC50(track, 1);
        } else if (pressed & BTN_RIGHT) {
            SE(0);
            track = func_0017DC50(track, 1);
        }
    }
    g_00749BB8 = track;
}

/* 0x002258E0, 0x64 bytes. Page 13 done: keeps the track and the on / off setting. */
void func_002258E0(void)
{
    func_00362B90(g_00749BB8);
    g_00669DB0 = (g_00669DB0 & 0xF1) | ((g_00749BB7 == 1) << 1);
}

/* 0x00225950, 0x1BC bytes. Page 13 (three lines: on / off, track, OK): the extra button stops the
 * music, Cancel goes back (music 0x19), OK on the third line keeps the settings; then the line's
 * handler. */
void func_00225950(int pad)
{
    void (*handlers[3])(int pad);
    u8 cursor = g_00749BB6;
    unsigned short pressed;
    int port;

    handlers[0] = g_0040DF50[0];
    handlers[1] = g_0040DF50[1];
    handlers[2] = g_0040DF50[2];
    if (pad == 0)
        port = 0;
    else
        port = pad == 1 ? 1 : pad;
    pressed = PAD_PRESSED_N(port);
    if (pressed & BTN_OK) {
        if (g_00749BB6 == 2) {
            func_002258E0();
            SE(1);
            func_00220970(0);
            func_0017E060(0x19);
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        func_00220970(0);
        func_0017E060(0x19);
    } else if (pressed & BTN_EXTRA) {
        func_0017DF10();
        g_00749BBA = 0;
    } else {
        func_002C5220(port, &cursor, &g_00749BB6, 3, 3);
    }
    if (handlers[g_00749BB6] != 0)
        handlers[g_00749BB6](pad);
}

/* 0x00225B10, 0x3C0 bytes. Sets the battle's scene up from its type (tables 0x00442EA0 -
 * 0x00443640): two camera ranges, the map frame, and the map's data. */
void func_00225B10(void)
{
    func_002CAD60(g_00749ACC);
    func_0028F860(g_00749AD8);
    func_0028EFC0(g_007496F0);
    func_0028F4C0(g_00749530);
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
    func_0028D5D0(0);
    func_002C59F0();
    func_002C5A30();
}

/* 0x00225ED0, 0x4C bytes. Page 10's list: all 31 entries empty (0x1F). */
void func_00225ED0(void)
{
    u32 i;

    for (i = 0; i < 31; i++)
        g_00749530[0x642 + i] = 0x1F;
}

/* 0x00225F20, 0x90 bytes. Page 10's list from the five officers' values (an Empire battle). */
void func_00225F20(void)
{
    u32 i;
    int n = 0;

    for (i = 0; i < 5; i++) {
        u32 v = func_0036F600(func_00328330(i));
        g_00749530[0x642 + i] = (u8)v;
        if (v < 0x1F)
            n++;
    }
    g_00749B91 = n == 0 ? 0 : 5;
}

/* 0x00225FB0, 0xD0 bytes. Page 10's list: the entries allowed (func_003A01A0), except 8 and 0x1D. */
void func_00225FB0(void)
{
    u8 n = 0;
    u32 i;
    u8 *out = &g_00749530[0x642];

    for (i = 0; i < 31; i++) {
        u32 v = func_0036F610(i);
        int ok = 0;

        if (func_00362B60(0) != 0 && ((ok = func_003A01A0(v)), i == 8 || i == 0x1D))
            ok = 0;
        if (ok == 0) {
            *out = 0x1F;
        } else {
            *out++ = (u8)i;
            n++;
        }
    }
    g_00749B91 = n;
}

/* 0x00226080, 0x64 bytes. Page 10 set-up. */
void func_00226080(void)
{
    func_00118850(g_00749B6C, 0x2A);
    g_00749B6C[4] = 0xFF;
    g_00749B6C[5] = 0xFF;
    func_00225ED0();
    if (func_0036D2E0() == 0)
        func_00225FB0();
    else
        func_00225F20();
}

/* 0x002260F0, 0x8 bytes, matching. */
void func_002260F0(void)
{
}

/* 0x00226100, 0xA4 bytes. Page 12's values: those allowed among 1-9. */
void func_00226100(void)
{
    int n = 0;
    u32 v;

    g_00749BA1[0] = 0xFF;
    g_00749BA1[1] = 0xFF;
    g_00749BA1[2] = 0xFF;
    g_00749BA1[3] = 0xFF;
    g_00749BA1[4] = 0xFF;
    if (func_00362B60(0) != 0) {
        for (v = 1; v < 10; v++)
            if (func_003A01A0(func_003F73E0(v)) != 0) {
                func_0029D1F0(&g_00749B9E, n, v);
                n++;
            }
    }
    g_00749BB4 = (u8)n;
}

/* 0x002261B0, 0x88 bytes. Pages 11 and 12 set-up. */
void func_002261B0(void)
{
    u32 i;

    func_00118850(g_00749B96, 8);
    func_00118850(&s_00749B9E, 0x18);
    for (i = 0; i < 9; i++)
        g_00749BAB[i] = 10;
    if (func_0036D2E0() == 0)
        func_00226100();
    else
        func_002260F0();
}

/* Clears the menu's state (inlined in the original, twice). */
#define CLEAR_MENU_STATE() do {                                                        \
        g_0069395E = 0;                                                                \
        g_00749A1C = 0;                                                                \
        g_0069395C = 1;                                                                \
        g_00749A14 = 0;                                                                \
        g_00749A10 = 0;                                                                \
        g_00749AF9 = 0;                                                                \
        g_00749A18 = 0;                                                                \
        g_00749AEF = 0;                                                                \
        g_00749AEE = 0;                                                                \
        g_00749AF1 = 0;                                                                \
        g_00749AF0 = 0;                                                                \
        g_00749AF3 = 0;                                                                \
        g_00749AF2 = 0;                                                                \
        g_00749AF5 = 0;                                                                \
        g_00749AF4 = 0;                                                                \
        g_00749AF7 = 0;                                                                \
        g_00749AF6 = 0;                                                                \
        g_00749AED = 0;                                                                \
        g_00749AEC = 0;                                                                \
        g_00749B0C = 0;                                                                \
        g_00749B08 = 0;                                                                \
    } while (0)

/* 0x00226240, 0x140 bytes. Resets the menu (the build-up path). */
void func_00226240(void)
{
    CLEAR_MENU_STATE();
    g_00749AFC = 0;
    g_00749B00 = 0;
    g_007A1C28 = 0;
    func_00118850(g_00749B10, 0x5C);
    func_00226080();
    func_002261B0();
    func_002CAC30(g_00749A28[0], g_00669DE8);
    func_00223B60(g_00749AE4);
    if ((g_00669F60 & 2) != 0)
        func_002CAC30(g_00749A28[1], g_00669E30);
}

/* 0x00226380, 0x1E8 bytes. Resets the menu and loads its data (LINKDATA 0x36, and 0x37 outside
 * mode 2). */
void func_00226380(void)
{
    CLEAR_MENU_STATE();
    g_00749B00 = 0;
    g_00749AFC = 0;
    g_007A1C28 = 0;
    func_00221890();
    func_00118850(g_00749B10, 0x5C);
    func_00226080();
    func_002261B0();
    func_002CAC30(g_00749A28[0], g_00669DE8);
    func_00223B60(g_00749AE4);
    if ((g_00669F60 & 2) != 0)
        func_002CAC30(g_00749A28[1], g_00669E30);
    func_00103000(0);
    g_00749A20 = func_001026D0(1, 0x36, 0, 1, 0, 0, g_00429EA0, 0xD09);
    if (g_00669DB8 != 2)
        g_00749A24 = func_001026D0(1, 0x37, 0, 1, 0, 0, g_00429EA0, 0xD0C);
    func_002D6890();
    func_0028F960(g_007499EC);
    g_00772D54 = 0;
    func_003E4280();
    func_00103000(1);
}

/* Opens the loading screen for the battle's stage: type 0x0D on stages 0x37 / 0x38 keeps
 * picture 0x0D (else 0x18), type 0x13 uses 0x13 on stage 0x4E (else 0x15), others their type
 * (inlined in the original, twice). */
static void open_loading_screen(void)
{
    if (BATTLE_TYPE() == 0x0D) {
        if (BATTLE_STAGE() != 0x37 && BATTLE_STAGE() != 0x38)
            func_002F15E0(g_00669DE8, 0x18);
        else
            func_002F15E0(g_00669DE8, 0x0D);
    } else if (BATTLE_TYPE() == 0x13) {
        if (BATTLE_STAGE() == 0x4E)
            func_002F15E0(g_00669DE8, 0x13);
        else
            func_002F15E0(g_00669DE8, 0x15);
    } else {
        func_002F15E0(g_00669DE8, BATTLE_TYPE());
    }
}

/* 0x00226570, 0x278 bytes. Scene 0x09 enter when a movie plays first: only the loading screen;
 * the update builds the battle (func_00227060). */
void func_00226570(void)
{
    func_0017DF10();
    func_00101470(1);
    g_00749B04 = 0;
    func_003F1580();
    open_loading_screen();
    func_001B8F60(1, 6, 8);
    g_0045D49C = 1;
}

/* 0x002267F0, 0x3F0 bytes. Scene 0x09 enter: the loading screen (mode 2: picture 0x16), the
 * battle's data, the menu (free battles) or scene 0x08's screens (Empire battles). */
void func_002267F0(void)
{
    if (func_0032E7B0() != 0) {
        func_00226570();
        return;
    }
    if (func_0017DDA0() != 0)
        func_0017DF10();
    func_00101470(1);
    g_00749B04 = 0;
    func_003F1580();
    if (g_00669F6C == 1 && g_00669DB8 == 1)
        func_003DD9A0();
    if (g_00669DB8 != 3) {
        if (g_00669DB8 == 2)
            func_002F15E0(g_00669DE8, 0x16);
        else
            open_loading_screen();
    }
    if (g_00669F6C == 1) {
        func_001D42E0();
        func_00235A70();
        func_001B8F60(1, 6, 8);
    } else if (g_00669F6C == 2 || g_00669F6C == 0) {
        func_00226380();
        func_001D42E0();
    }
    func_00225B10();
    func_003E3D70();
    if (g_00669F6C == 1) {
        func_00376490(g_00749A0C, 0x62);
    } else if (func_0036D310() == 0) {
        u32 a = g_00749A0C;
        func_00376490(a, func_003EF0D0(func_00363B90()));
    } else {
        func_00376490(g_00749A0C, 0xC0);
    }
    func_00376100(0, -1, -1);
}

/* 0x00226BE0, 0x2C bytes, matching. */
void func_00226BE0(void)
{
    g_0045D2C0 = g_0045D670;
    func_00103000(0);
    func_00103000(1);
}

/* 0x00226C10, 0xE8 bytes, matching. Leaves the menu: to the battle (scene 4) sets the players' units up,
 * then frees the menu's data. */
void func_00226C10(void)
{
    u8 *unit = g_0045D670;

    if (func_0032E7B0() != 0) {
        func_00226BE0();
        return;
    }
    if (g_0045D898 == 4) {
        func_0019B4F0(0, 1);
        func_0019BD90(0);
        if ((g_00669F60 & 2) != 0) {
            func_0019B4F0(1, 1);
            func_0019BD90(1);
        }
    }
    g_0045D2C0 = unit;
    func_00103000(0);
    func_0028FB40(g_007499EC);
    func_002D68F0();
    if (g_00669DB8 != 2)
        func_00102EC0(g_00749A24);
    func_00102EC0(g_00749A20);
    func_003E42D0();
    func_00103000(1);
}

/* 0x00226D00, 0x88 bytes. Scene 0x09 leave. */
void func_00226D00(void)
{
    if (g_00669F6C == 1)
        func_00235F70();
    else if (g_00669F6C == 2 || g_00669F6C == 0)
        func_00226C10();
    if (g_00669F6C == 1 && g_0045D898 == 1)
        func_002F1660();
}

/* 0x00226D90, 0x2D0 bytes. The menu's update: waits for the message boxes and checks
 * (func_00221950 per player), then runs the current page's handler. */
int func_00226D90(void)
{
    int box = 5, open;

    if (g_006934B3 != 0)
        box = 0;
    else if (g_006935DB != 0)
        box = 1;
    if (box == 0 || box == 1)
        return 1;
    if (g_00749A18 != 2) {
        if (g_00749A18 == 1) {
            if (g_00772D54 != 0)
                return 1;
            open = box1_open();
            if (open)
                return 1;
            func_002209E0();
            g_00749A18 = 0;
            return 1;
        }
        if (g_00749A18 == 0) {
            if (g_00749A10 == 0) {
                if (func_00221950(0) != 0)
                    return 1;
                if ((g_00669F60 & 2) != 0 && func_00221950(1) != 0)
                    return 1;
            }
            g_00749A18 = 2;
            return 1;
        }
    }
    switch (g_00749A10) {
    case 0:
        if (func_00221AB0(0) == 0 && (g_00669F60 & 2) != 0) {
            func_00221AB0(1);
            return 1;
        }
        break;
    case 1:  func_00221F70(g_00749A1C); break;
    case 2:  func_00222450(g_00749A1C); break;
    case 3:  func_00223090(g_00749A1C); break;
    case 5:  func_00223120(g_00749A1C); break;
    case 6:  func_00223220(g_00749A1C); break;
    case 7:  func_00223600(g_00749A1C); break;
    case 9:  func_00223BB0(g_00749A1C); break;
    case 10: func_00224D70(); break;
    case 11: func_00224E20(g_00749A1C); break;
    case 12: func_002254B0(g_00749A1C); break;
    case 13: func_00225950(g_00749A1C); break;
    }
    return 1;
}

/* 0x00227060, 0x34C bytes. The build-up when a movie plays first: one step a frame (after 120
 * frames), the battle's systems as in func_001D42E0, then the menu. Returns non-zero while the
 * loading screen is closed. */
int func_00227060(float dt)
{
    u32 a = g_00749A0C;
    int closed;

    switch (g_0045D494) {
    case 0:
        g_0045D498++;
        if (g_0045D498 >= 0x78)
            g_0045D494++;
        break;
    case 1:
        func_00226240();
        if (g_00669F6C == 0)
            func_0019F410();
        g_00669F70 = 0;
        g_00669F60 &= 0xF3FFFFF3;
        g_0045D494++;
        break;
    case 2:
        func_0035ED20();
        func_003635A0();
        func_0035FD10();
        g_0045D494++;
        break;
    case 3:
        func_00213F40(BATTLE_STAGE());
        func_001C77D0(0);
        g_0045D494++;
        break;
    case 4:
        func_0018C500();
        func_00216B40();
        g_0045D494++;
        break;
    case 5:
        func_00194010();
        g_0045D494++;
        break;
    case 6:
        if (func_00102960(0) != 0)
            g_0045D494++;
        break;
    case 7:
        func_001BE1A0();
        g_0045D494++;
        break;
    case 8:
        func_00185CA0();
        g_0045D494++;
        break;
    case 9:
        func_0022E150();
        g_0045D494++;
        break;
    case 10:
        func_0020EBB0();
        g_0045D494++;
        break;
    case 11:
        func_00225B10();
        g_0045D494++;
        break;
    case 12:
        func_003E3D70();
        g_0045D494++;
        break;
    case 13:
        if (g_00669F6C == 1)
            func_00376490(g_00749A0C, 0x62);
        else
            func_00376490(a, func_003EF0D0(func_00363B90()));
        g_0045D494++;
        break;
    case 14:
        func_00376100(0, -1, -1);
        g_0045D494++;
        break;
    case 15:
        func_00102960(0);
        g_0045D494++;
        break;
    case 16:
        func_00102960(0);
        g_00749B04 = 1;
        g_0045D494++;
        break;
    case 17:
        g_0045D494 = 0;
        g_0045D498 = 0;
        g_0045D49C = 0;
        func_00221710(0);
        return func_00226D90();
    }
    closed = g_0045D49C == 0;
    if (!closed)
        func_002F16B0();
    return closed;
}

/* 0x002273B0, 0x174 bytes. Scene 0x09 update: until the data is in, music 0x19 and the fade-in;
 * then the menu (or scene 0x08's screens for an Empire battle), unless func_003F1400 shows a
 * message (2: confirm and re-check). */
int func_002273B0(float dt)
{
    int r;

    if (func_0032E7B0() != 0)
        return func_00227060(dt);
    if (g_00749B04 == 0) {
        if (func_0017DDA0() == 0) {
            func_0017E060(0x19);
        } else {
            func_00102960(0);
            g_00749B04 = 1;
            func_001B8F60(1, 6, 8);
        }
        return 1;
    }
    func_00376450();
    r = func_003F1400(g_00749A1C == 1);
    if (r == 0) {
        if (g_00669F6C == 1)
            return func_00235FC0(dt);
        if (g_00669F6C == 2 || g_00669F6C == 0) {
            if (func_0032E7B0() != 0)
                func_00221710(0);
            return func_00226D90();
        }
        return 1;
    }
    if (r == 2) {
        g_00772D38 = 1;
        g_00772D3C = 0;
        g_00772D34 = g_00772D36;
        func_00221950(g_00749A1C);
    }
    return 1;
}

/* 0x00227530, 0x30 bytes, matching. */
void func_00227530(void)
{
    if (g_00669DB8 != 2)
        func_002EC0A0();
}

/* 0x00227560, 0x5C bytes. Scene 0x09 step. */
void func_00227560(void)
{
    if (g_00669F6C == 1)
        func_00236430();
    else if (g_00669F6C == 2 || g_00669F6C == 0)
        func_00227530();
}

/* 0x002275C0, 0xAF4 bytes. The menu's draw: background, a darkened band, the map (outside mode
 * 2), the current page, the frame, then the page's button help line. */
void func_002275C0(void)
{
    u32 officer = PLAYER_OFFICER(g_00749A1C);
    u8 *packet;

    if (g_00749B04 == 0)
        return;
    func_00291650(g_00749A20, 0);
    packet = func_001050F0();
    *(u64 *)(packet + 0x10) = 0x32001;
    *(u64 *)(packet + 0x18) = 0x48;
    func_00105390(packet);
    packet = func_00105410();
    *(u64 *)(packet + 0x20) = 0x79007000;
    *(u64 *)(packet + 0x28) = 0x87009000;
    *(u64 *)(packet + 0x18) = 0x3F80000080808080ULL;
    func_00105560(packet);
    packet = func_001050F0();
    *(u64 *)(packet + 0x10) = 0x5000D;
    *(u64 *)(packet + 0x18) = 0x48;
    func_00105390(packet);
    if (g_00669DB8 != 2) {
        if (g_00749B00 != 0) {
            g_00749B00 = func_002ECA70();
            g_00749B00 = func_002EC150() != 0 || g_00749B00 != 0;
        }
        func_00195C20();
        func_001FCC50();
        func_002937E0(g_00749AD8, g_00749530);
        func_00292A90(g_007496F0);
        func_001FCC90();
        func_002944D0();
    }
    switch (g_00749A10) {
    case 0:  func_0029B900(g_00749A20, &g_00749AEC, g_00749AD8, g_007496F0, &g_00749B08); break;
    case 1:  func_0029BBC0(g_00749A20, g_007499EC, g_00749A24, g_00749AEE, g_00749A1C, g_00749AE4); break;
    case 2:  func_0029C690(g_00749530, g_00749AD8, 0); break;
    case 3:  func_0029CC10(g_00749A1C, g_007496F0, g_00749B10); break;
    case 5:  func_0029CC70(PLAYER_OFFICER(g_00749A1C)); break;
    case 6:
        func_0029BEC0(g_00749A20, g_007499EC + g_00749A1C * 0x10, g_00749AF0, g_00749AEF,
                      g_00749A28[g_00749A1C]);
        break;
    case 7:  func_0029C140(PLAYER_OFFICER(g_00749A1C), g_00749AF0, 1); break;
    case 9:  func_0029C460(g_00749A20, g_00749A24, g_00749AF0, g_00749A1C, g_00749AE4); break;
    case 10: func_0029CEB0(g_00749A1C, g_007496F0, g_00749B6C, g_00749A20); break;
    case 11: func_0029D310(g_00749A1C, g_007496F0, g_00749B96, g_00749A20); break;
    case 12: func_0029D520(g_00749A1C, g_007496F0, &g_00749B9E, g_00749A20); break;
    case 13: func_0029D6F0(&g_00749BB6); break;
    }
    func_00290CE0(g_00749A20, g_00749A0C, 1, g_00749A10, g_00749A1C);
    func_003764B0();
    if (func_003F1160(1) != 0)
        return;
    switch (g_00749A10) {
    case 0:
        func_001A7DC0(g_0043C838, 0x80, 1);
        return;
    case 1: {
        int o = PLAYER_OFFICER(g_00749A1C);
        if (o < 0 || o > 0x1B || func_00328A60(o) < 1)
            func_001A7DC0(g_0043C5A8, 0x80, 1);
        else
            func_001A7DC0(g_0043C760, 0x80, 1);
        break;
    }
    case 2:
        func_001A7DC0(g_0043C5CC, 0x80, 1);
        break;
    case 3:
        if (g_00749B68 == 3) {
            func_001A7DC0(g_0043C7A4, 0x80, 1);
        } else if (g_00749B68 == 0) {
            u8 *s = *(u8 **)(g_00749530 + 0x340 + g_00749B10[0] * 0x78 + g_00749B10[1] * 4);
            if (s != 0) {
                if ((*(u32 *)(s + 0x80) & 0x30) == 0) {
                    if (func_0036D780() == 0 || s[0x79] != 0)
                        func_001A7DC0(g_0043C6F4, 0x80, 1);
                    else
                        func_001A7DC0(g_0043C6F0, 0x80, 1);
                } else if (func_0036D780() == 0) {
                    func_001A7DC0(g_0043C6F4, 0x80, 1);
                } else {
                    func_001A7DC0(g_0043C6F0, 0x80, 1);
                }
            }
        }
        break;
    case 4:
        func_001A7DC0(g_0043C5CC, 0x80, 1);
        break;
    case 5:
        func_001A7DC0(g_0043C5D4, 0x80, 1);
        break;
    case 6:
        if (g_00749AEF == -1) {
            if (func_002208D0(officer) < 2)
                func_001A7DC0(g_0043C55C, 0x80, 1);
            else
                func_001A7DC0(g_0043C5AC, 0x80, 1);
        } else {
            func_001A7DC0(g_0043C5A8, 0x80, 1);
        }
        break;
    case 7: {
        u32 item = g_00749AF0;
        if (item == 0xFF)
            item = func_002F6A60(officer);
        if (func_0036DBA0(officer, item) < 1)
            func_001A7DC0(g_0043C5B0, 0x80, 1);
        else if (func_002F4900(officer, item) == 0)
            func_001A7DC0(g_0043C5B8, 0x80, 1);
        else
            func_001A7DC0(g_0043C5B4, 0x80, 1);
        break;
    }
    case 9:
        if (g_00749AE4[g_00749AF0] == g_00749AE4[5 + g_00749A1C])
            func_001A7DC0(g_0043C5C8, 0x80, 1);
        else
            func_001A7DC0(g_0043C5C4, 0x80, 1);
        break;
    case 10:
        if (g_00749B6C[0] == 0) {
            if (g_00749B6C[4 + g_00749B6C[1]] < 0x1F)
                func_001A7DC0(g_0043C6FC, 0x80, 1);
            else
                func_001A7DC0(g_0043C700, 0x80, 1);
        } else if (func_0029A5C0() < 2) {
            func_001A7DC0(g_0043C560, 0x80, 1);
        } else {
            func_001A7DC0(g_0043C638, 0x80, 1);
        }
        break;
    case 11:
        func_003838B0(func_003725A0(0x62), 1);
        if (func_00362D70(0) < 2)
            func_001A7DC0(g_0043C560, 0x80, 1);
        else
            func_001A7DC0(g_0043C72C, 0x80, 1);
        break;
    case 12:
        func_003838B0(func_003725A0(99), 1);
        if (g_00749B9E == 0) {
            if (g_00749B9F < 5 && g_00749BA1[g_00749B9F] < 10)
                func_001A7DC0(g_0043C6FC, 0x80, 1);
            else
                func_001A7DC0(g_0043C72C, 0x80, 1);
        } else if (g_00749BB4 >= 2) {
            func_001A7DC0(g_0043C72C, 0x80, 1);
        } else if (g_00749BB4 == 1) {
            func_001A7DC0(g_0043C560, 0x80, 1);
        }
        break;
    case 13:
        if (g_00749BB6 == 2)
            func_001A7DC0(g_00749BBA == 0 ? g_0043C718 : g_0043C714, 0x80, 1);
        else if (g_00749BB6 == 1)
            func_001A7DC0(g_00749BBA == 0 ? g_0043C710 : g_0043C70C, 0x80, 1);
        else if (g_00749BB6 == 0)
            func_001A7DC0(g_00749BBA == 0 ? g_0043C708 : g_0043C704, 0x80, 1);
        break;
    }
}

/* 0x002280C0, 0x90 bytes. Scene 0x09 draw: the loading screen while it is open, else the menu
 * (or scene 0x08's screens). */
void func_002280C0(void)
{
    if (func_0032E7B0() != 0) {
        if (g_0045D49C != 0)
            func_002F16D0();
        return;
    }
    func_003F11D0();
    if (g_00669F6C == 1)
        func_00236450();
    else if (g_00669F6C == 2 || g_00669F6C == 0)
        func_002275C0();
}

/* 0x00228150, 0x24 bytes, matching. Scene 0x09 on_reset: the battle ends as "reset" and its systems are
 * freed. */
void func_00228150(void)
{
    g_00669F70 = 7;
    func_001D1E80();
}
