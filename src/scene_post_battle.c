/*
 * scene_post_battle.c - scene 0x0A, after a battle (original source file StatePostBattle.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Work in progress: enter and leave so far. The scene's state is the object at 0x00747930
 * (0x1C00 bytes); the battle's results come from the game state at 0x00669D60.
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
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

/* 0x7000015C: random seed in the scratchpad (see main.c). */
#define g_7000015C (*(u32 *)0x7000015C)

/* ---- The game state (0x00669D60): what this scene reads ---------------------------------------- */

/* One record per player (0x48 bytes, at 0x00669DE8 and 0x00669E30). */
typedef struct {
    u32 data_0;              /* +0x00 given to func_002CAC30 */
    u32 value_4;             /* +0x04 above 999: see func_0021C5F0 */
    u32 value_8;
    u32 value_c;             /* +0x0C */
    u8 unknown_10[0x8];
    int active;              /* +0x18 non-zero for a player in the game */
    u8 unknown_1c[0x2C];
} PlayerRecord;

extern struct {
    u8 unknown_0[0x58];
    int g_00669DB8;              /* +0x058 (0 for the Empire game?) */
    u8 unknown_5c[0x8C];
    PlayerRecord players[2];     /* +0x088 0x00669DE8, 0x00669E30 */
    u8 unknown_178[0x88];
    u32 g_00669F60;              /* +0x200 bit 1: two players */
    u8 unknown_204[0xC];
    u32 g_00669F70;              /* +0x210 how the battle ended? (0, 1-4, 5-7) */
} g_00669D60;
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F70 (g_00669D60.g_00669F70)
#define TWO_PLAYERS() ((g_00669F60 & 2) != 0)

/* ---- The scene's state (0x00747930) ------------------------------------------------------------ */

/* An officer's results (0xA0 bytes, 8 per side, 0x500 bytes per side, at 0x00747F5C). */
typedef struct {
    int level;               /* +0x00 level + 1 */
    int stats[9];            /* +0x04 func_002F34E0 ... func_002F55A0 */
    u8 unknown_28[0x78];
} OfficerResult;

/* An entry of the list of officers shown (0x24 bytes, at 0x00748DC8). */
typedef struct {
    int side;
    int slot;
    int officer;
    int value_c;             /* func_00362260 */
    int value_10;
    int value_14;            /* func_0036B340 */
    int value_18;            /* func_0036BA20 */
    int value_1c;            /* 1 when func_0036BA40 / func_0036BA60 gives 2 */
    int value_20;
} ShownOfficer;

/* Globals 0x00747930-0x00747970: one object in the original (not reached through $gp). */
extern struct {
    int g_00747930;
    int g_00747934;
    int g_00747938;
    int g_0074793C;
    int g_00747940;
    char pad_0[0x8];
    int g_0074794C;
    u32 g_00747950;
    u32 g_00747954;
    u32 g_00747958;
    u32 g_0074795C;
    u32 g_00747960;
    u32 g_00747964;
    u32 g_00747968;
    int g_0074796C;
} s_00747930;
#define g_00747930 (s_00747930.g_00747930)
#define g_00747934 (s_00747930.g_00747934)
#define g_00747938 (s_00747930.g_00747938)
#define g_0074793C (s_00747930.g_0074793C)
#define g_00747940 (s_00747930.g_00747940)
#define g_0074794C (s_00747930.g_0074794C)
#define g_00747950 (s_00747930.g_00747950)
#define g_00747954 (s_00747930.g_00747954)
#define g_00747958 (s_00747930.g_00747958)
#define g_0074795C (s_00747930.g_0074795C)
#define g_00747960 (s_00747930.g_00747960)
#define g_00747964 (s_00747930.g_00747964)
#define g_00747968 (s_00747930.g_00747968)
#define g_0074796C (s_00747930.g_0074796C)

/* A player's results (0xA0 bytes, at 0x00747DF8 and 0x00747E98). */
typedef struct {
    u8 unknown_0[0x24];
    int level;               /* +0x24 level + 1 (func_003DCB00) */
    int stats[9];            /* +0x28 func_003DCBB0 ... func_003DCD30 */
    u8 block_4c[0x24];       /* +0x4C filled by func_002CA590 */
    int value_70;            /* +0x70 (0x00747E68) */
    int value_74;
    int rating_points;       /* +0x78 points scaled by the difficulty (0x00747E70) */
    int value_7c;
    int value_80;            /* +0x80 game state player +0x04 */
    int value_84;            /* +0x84 0x00669F9C */
    int value_88;            /* +0x88 game state player +0x0C */
    int points;              /* +0x8C 0..0xFFFF (0x00747E84) */
    int value_90;
    u8 rank;                 /* +0x94 0 (best) .. 4 */
    u8 pad_95[3];
    int shown;               /* +0x98 (0x00747E90) */
    int value_9c;            /* +0x9C (0x00747E94) */
} PlayerResult;

extern PlayerResult g_00747DF8[2];
#define g_00747E90 (g_00747DF8[0].shown)
#define g_00747F30 (g_00747DF8[1].shown)

/* Globals 0x00748A30-0x00748A49: one object in the original (not reached through $gp). */
extern struct {
    int g_00748A30;
    int g_00748A34;
    int g_00748A38;
    int g_00748A3C;
    int g_00748A40;
    int g_00748A44;
    u8 g_00748A48;
} s_00748A30;
#define g_00748A30 (s_00748A30.g_00748A30)
#define g_00748A34 (s_00748A30.g_00748A34)
#define g_00748A38 (s_00748A30.g_00748A38)
#define g_00748A3C (s_00748A30.g_00748A3C)
#define g_00748A40 (s_00748A30.g_00748A40)
#define g_00748A44 (s_00748A30.g_00748A44)
#define g_00748A48 (s_00748A30.g_00748A48)

/* Globals 0x00748F0C-0x00748FA4: one object in the original (not reached through $gp). */
extern struct {
    int g_00748F0C;                           /* entries in g_00748DC8 */
    int g_00748F10;                           /* experience shown on the level-up step */
    int g_00748F14;
    int g_00748F18;
    int g_00748F1C[9][2];                     /* (side, slot) of the officers that levelled up */
    int g_00748F64;                           /* their number */
    int g_00748F68;
    u8 g_00748F6C;
    char pad_2[0x4];
    u8 g_00748F71;
    u8 g_00748F72;
    u8 g_00748F73;
    u8 g_00748F74;
    char pad_3[0x1];
    u8 g_00748F76;
    char pad_4[0x9];
    int g_00748F80;
    int g_00748F84;
    int g_00748F88;
    int g_00748F8C;
    int g_00748F90;
    int g_00748F94;
    int g_00748F98;
    int g_00748F9C;
    u32 g_00748FA0;                           /* random seed when the scene started */
} s_00748F0C;
#define g_00748F0C (s_00748F0C.g_00748F0C)
#define g_00748F10 (s_00748F0C.g_00748F10)
#define g_00748F14 (s_00748F0C.g_00748F14)
#define g_00748F18 (s_00748F0C.g_00748F18)
#define g_00748F1C (s_00748F0C.g_00748F1C)
#define g_00748F64 (s_00748F0C.g_00748F64)
#define g_00748F68 (s_00748F0C.g_00748F68)
#define g_00748F6C (s_00748F0C.g_00748F6C)
#define g_00748F71 (s_00748F0C.g_00748F71)
#define g_00748F72 (s_00748F0C.g_00748F72)
#define g_00748F73 (s_00748F0C.g_00748F73)
#define g_00748F74 (s_00748F0C.g_00748F74)
#define g_00748F76 (s_00748F0C.g_00748F76)
#define g_00748F80 (s_00748F0C.g_00748F80)
#define g_00748F84 (s_00748F0C.g_00748F84)
#define g_00748F88 (s_00748F0C.g_00748F88)
#define g_00748F8C (s_00748F0C.g_00748F8C)
#define g_00748F90 (s_00748F0C.g_00748F90)
#define g_00748F94 (s_00748F0C.g_00748F94)
#define g_00748F98 (s_00748F0C.g_00748F98)
#define g_00748F9C (s_00748F0C.g_00748F9C)
#define g_00748FA0 (s_00748F0C.g_00748FA0)

/* Globals 0x00749434-0x00749530: one object in the original (not reached through $gp). */
extern struct {
    int g_00749434;
    char pad_0[0xF0];
    int g_00749528;
    int g_0074952C;
} s_00749434;
#define g_00749434 (s_00749434.g_00749434)
#define g_00749528 (s_00749434.g_00749528)
#define g_0074952C (s_00749434.g_0074952C)

/* Globals 0x007729FC-0x00772D50: one object in the original (not reached through $gp). */
extern struct {
    int g_007729FC;
    int g_00772A00;
    char pad_0[0x348];
    int g_00772D4C;
} s_007729FC;
#define g_007729FC (s_007729FC.g_007729FC)
#define g_00772A00 (s_007729FC.g_00772A00)
#define g_00772D4C (s_007729FC.g_00772D4C)

extern OfficerResult g_00747F5C[2][8];
extern u8 g_00748938[], g_0074898A[];
extern ShownOfficer g_00748DC8[];
extern int g_00748FA4[2];                        /* officer of each player (0x19F = none) */
extern int g_00749180[];                         /* per player, added up for the gold */
extern int g_007494D8[2];
extern int g_00749520[2];

extern const char g_00429CB0[];                  /* "StatePostBattle.c" (__FILE__ for the loader) */

u32 func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00102EC0(u32 handle);
void func_00101470(int value);
void func_003F1580(void);
int func_0021BE80(void);
void func_002D6890(void);
void func_002D68F0(void);
int func_0036B330(void);
int func_003623B0(void);
int func_00362320(int player);
int func_003620E0(int side, int slot);
int func_003294A0(int player);
int func_0036D310(void);
u8 *func_0019FBC0(int item);
int func_003637D0(int side, int slot);
int func_002F41E0(int officer);
int func_002F34E0(int officer);
int func_002F39F0(int officer);
int func_002F4C40(int officer);
int func_002F4DD0(int officer);
int func_002F4F60(int officer);
int func_002F50F0(int officer);
int func_002F5280(int officer);
int func_002F5410(int officer);
int func_002F55A0(int officer);
void func_002CAC30(void *dst, u32 data);
void func_003ACC90(void);
void func_003AA920(void);
void func_003AE420(void);
void func_003AC340(void);
int func_002F59A0(int officer);
void func_002F5930(int officer, int value);
u32 func_00327D50(void);
void func_002F90D0(u32 force, int amount);
void func_003AD790(void);
void func_003AE2D0(void);
void func_0017E010(int track);
void func_0021BFC0(int player);
void func_0021A840(int player);
void func_002857E0(int value);
int func_0036B8C0(int side);
int func_0036B940(int side, int slot);
int func_00362260(int side, int slot);
int func_0036B340(int side, int slot);
int func_0036BA20(int side, int slot);
int func_0036BA40(int slot);
int func_0036BA60(int slot);
void func_001B8F60(int a, int b, int c);
void func_001A2960(void);

/* 0x0021C5F0, 0xA4C bytes. Scene enter: loads the scene's data (7 LINKDATA entries), takes the
 * battle's results (officers' levels and stats, rewards, the gold earned when g_00669DB8 is 0),
 * chooses the music, or for results 5-7 leaves at once, then builds the list of officers shown
 * (side 0, and one officer of side 1). */
void func_0021C5F0(void)
{
    int i, side, slot, officer, total, player;

    func_00101470(1);
    func_003F1580();
    g_00747950 = func_001026D0(1, 0x38, 0, 1, 0, 0, g_00429CB0, 1303);
    g_00747954 = func_001026D0(1, 0x8D, 0, 1, 0, 0, g_00429CB0, 1304);
    g_00747958 = func_001026D0(1, 0x36, 0, 1, 0, 0, g_00429CB0, 1305);
    g_0074795C = func_001026D0(1, 0x39, 0, 1, 0, 0, g_00429CB0, 1306);
    g_00747964 = func_001026D0(1, 0x37, 0, 1, 0, 0, g_00429CB0, 1307);
    g_00747968 = func_001026D0(1, 0x81, 0, 1, 0, 0, g_00429CB0, 1308);
    g_00747960 = func_001026D0(1, func_0021BE80(), 0, 1, 0, 0, g_00429CB0, 1309);
    func_002D6890();

    g_00748F84 = g_00669DB8;
    g_00748F88 = 0;
    g_00748F8C = 1;
    g_00748F90 = TWO_PLAYERS();
    switch (func_0036B330()) {
    case 0:
    case 1:
    case 2:
        g_00748F94 = 1;
        break;
    case 3:
    case 4:
    case 5:
        g_00748F94 = 0;
        break;
    default:
        g_00748F94 = 1;
        break;
    }
    if (g_00748F90 == 0)
        g_00748F98 = 1;
    else
        g_00748F98 = 2;
    g_00748F9C = func_003623B0();
    g_00748FA0 = g_7000015C;

    for (player = 0; player < 2; player++) {
        if (g_00669D60.players[player].active == 0)
            g_00748FA4[player] = 0x19F;
        else
            g_00748FA4[player] = func_003620E0(0, func_00362320(player));
    }

    for (player = 0; player < 2; player++) {
        if (func_003294A0(player) < 4 && func_0036D310() == 0) {
            if (func_0019FBC0(func_003294A0(player))[4] == 4)
                g_00749520[player] = 0;
            else
                g_00749520[player] = 1;
        } else {
            g_00749520[player] = 0;
        }
    }

    for (side = 0; side < 2; side++)
        for (slot = 0; slot < 8; slot++) {
            OfficerResult *r = &g_00747F5C[side][slot];
            officer = func_003620E0(side, slot);
            if (func_003637D0(side, slot) == 0 && officer < 0x19F) {
                r->level = func_002F41E0(officer) + 1;
                r->stats[0] = func_002F34E0(officer);
                r->stats[1] = func_002F39F0(officer);
                r->stats[2] = func_002F4C40(officer);
                r->stats[3] = func_002F4DD0(officer);
                r->stats[4] = func_002F4F60(officer);
                r->stats[5] = func_002F50F0(officer);
                r->stats[6] = func_002F5280(officer);
                r->stats[7] = func_002F5410(officer);
                r->stats[8] = func_002F55A0(officer);
            }
        }

    g_0074952C = 0;
    func_002CAC30(g_00748938, g_00669D60.players[0].data_0);
    if (TWO_PLAYERS())
        func_002CAC30(g_0074898A, g_00669D60.players[1].data_0);
    func_003ACC90();
    func_003AA920();
    func_003AE420();
    func_003AC340();

    for (player = 0; player < 2; player++) {
        g_007494D8[player] = 0;
        if (g_00669D60.players[player].active != 0 && g_00669D60.players[player].value_4 > 999) {
            if (func_002F59A0(func_003620E0(0, func_00362320(player))) == 0) {
                g_007494D8[player] = 1;
                func_002F5930(func_003620E0(0, func_00362320(player)), 1);
            }
        }
    }

    if (g_00669DB8 == 0) {                      /* gold earned (in tens) */
        u32 force = func_00327D50();
        total = 0;
        for (i = 0; i < g_00748F98; i++)
            total += g_00749180[i];
        func_002F90D0(force, (total + g_00749434) / 10);
    }
    func_003AD790();
    func_003AE2D0();

    g_00747930 = 0;
    g_00747934 = 0;
    g_00747938 = 1;
    g_0074793C = 0x0E;
    g_00747940 = 7;
    g_00748F71 = 0;
    g_00748F72 = 0;
    g_00748F73 = 0;
    g_0074796C = 0;
    g_0074794C = 0;
    g_00772D4C = 0;
    g_00748F74 = 0;
    g_00748F76 = 0;
    g_00748F80 = 1;
    g_00749528 = 0;
    switch (g_00669F70) {
    case 0:
        g_00747E90 = 1;
        g_00747F30 = TWO_PLAYERS();
        func_0017E010(0x1A);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        func_0017E010(0x1A);
        g_00747E90 = 0;
        g_00747F30 = 0;
        g_007729FC = 0;
        break;
    case 5:
    case 6:
    case 7:                                     /* leave at once */
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
            g_0045D89C = 1;
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D8A0;
            g_0045D89C = 0x18;
        } else {
            g_0045D894 = g_0045D898;
            g_0045D898 = g_0045D89C;
            g_0045D89C = g_0045D8A0;
        }
        g_00747E90 = 0;
        g_00747F30 = 0;
        break;
    }

    func_0021BFC0(0);
    func_0021A840(0);
    func_002857E0(0);
    if (TWO_PLAYERS()) {
        func_0021BFC0(1);
        func_0021A840(1);
    }
    g_00748A30 = 0;
    g_00748A34 = 0;
    g_00748A38 = 0;
    g_00748A3C = 0;
    g_00748A40 = 0;
    g_00748A44 = 0;
    g_00748A48 = 0;
    g_00748F18 = 0;
    g_00748F0C = 0;
    g_00748F14 = 0;
    g_00748F6C = 0;

    /* The officers shown: those of side 0 (except a special one, see func_0036B940), then the
     * special officer of side 1. */
    officer = func_0036B8C0(0);
    for (slot = 0; slot < 8; slot++) {
        if ((officer != slot || func_0036B940(0, officer) == 0) && func_003620E0(0, slot) < 0x19F) {
            ShownOfficer *e = &g_00748DC8[g_00748F0C];
            e->side = 0;
            e->slot = slot;
            e->officer = func_003620E0(0, slot);
            e->value_c = func_00362260(0, slot);
            e->value_10 = 0;
            e->value_14 = func_0036B340(0, slot);
            e->value_18 = func_0036BA20(0, slot);
            if (func_0036BA40(slot) == 2) {
                e->value_1c = 1;
                g_00748F14 = 1;
            } else {
                e->value_1c = 0;
            }
            e->value_20 = 1;
            g_00748F0C++;
        }
    }
    slot = func_0036B8C0(1);
    if (slot < 8 && func_0036B940(1, slot) != 0) {
        ShownOfficer *e = &g_00748DC8[g_00748F0C];
        e->side = 1;
        e->slot = slot;
        e->officer = func_003620E0(1, slot);
        e->value_c = func_00362260(1, slot);
        e->value_10 = 0;
        e->value_14 = func_0036B340(1, slot);
        e->value_18 = func_0036BA20(1, slot);
        if (func_0036BA60(slot) == 2) {
            e->value_1c = 1;
            g_00748F14 = 1;
        } else {
            e->value_1c = 0;
        }
        e->value_20 = 1;
        g_00748F0C++;
    }
    g_00772A00 = 0;
    g_00748F68 = 0;
    func_001B8F60(1, 6, 8);
}

/* 0x0021D050, 0x78 bytes, matching. Scene leave: frees the scene's data. */
void func_0021D050(void)
{
    func_002D68F0();
    func_00102EC0(g_00747960);
    func_00102EC0(g_0074795C);
    func_00102EC0(g_00747958);
    func_00102EC0(g_00747950);
    func_00102EC0(g_00747954);
    func_00102EC0(g_00747964);
    func_00102EC0(g_00747968);
    func_001A2960();
}

/* ---- Helpers (0x0021A720-0x0021BC80) ------------------------------------------------------------ */

extern int g_00749110[];                  /* per officer slot: points earned in the battle */
extern int g_0074941C;                    /* points added to every player */
extern char g_00669D81;                   /* difficulty (0..4) */
extern u32 g_00669F9C;

u8 func_003A0EC0(int item);
u8 func_003A1070(int item, int i);
u8 func_003A1180(int item, int i);
u8 func_003A0F60(int item);
u8 func_003A1260(int item);
int func_003DCB00(int player);
int func_003DCBB0(int player);
int func_003DCBE0(int player);
int func_003DCC10(int player);
int func_003DCC40(int player);
int func_003DCC70(int player);
int func_003DCCA0(int player);
int func_003DCCD0(int player);
int func_003DCD00(int player);
int func_003DCD30(int player);
void func_002CA590(u32 data, void *dst);
void func_002F4820(int officer, int skill, int level);
extern u32 g_00428348[];                  /* 20 thresholds (u32) */

/* 0x0021A720, 0x9C bytes. Fills a 0x14-byte item record: the item, its kind, 8 pairs of values,
 * then two more values (func_003A0EC0 ... func_003A1260). */
void func_0021A720(u8 *out, int item)
{
    int i;

    out[0] = (u8)item;
    out[1] = func_003A0EC0(item);
    for (i = 0; i < 8; i++) {
        out[i + 2] = func_003A1070(item, i);
        out[i + 10] = func_003A1180(item, i);
    }
    out[0x12] = func_003A0F60(item);
    out[0x13] = func_003A1260(item);
}

/* 0x0021A7C0, 0x80 bytes. Index (0..18) of the band of g_00428348 that holds `value`, else 19. */
u32 func_0021A7C0(u32 value)
{
    u32 i;

    for (i = 0; (int)i <= 0x12; i++)
        if (g_00428348[i & 0xFF] <= value && value < g_00428348[(i + 1) & 0xFF])
            return i & 0xFF;
    return 0x13;
}

/* 0x0021A840, 0x350 bytes. Fills player `player`'s results: level, nine stats, the game state's
 * values, and the battle points (own slot + g_0074941C, between 0 and 0xFFFF), their rank (4 below
 * 2000 points ... 0 from 10000) and the rating points scaled by the difficulty. */
void func_0021A840(int player)
{
    PlayerResult *r = &g_00747DF8[player];
    int points;

    r->value_9c = 0;
    r->level = func_003DCB00(player) + 1;
    r->stats[0] = func_003DCBB0(player);
    r->stats[1] = func_003DCBE0(player);
    r->stats[2] = func_003DCC10(player);
    r->stats[3] = func_003DCC40(player);
    r->stats[4] = func_003DCC70(player);
    r->stats[5] = func_003DCCA0(player);
    r->stats[6] = func_003DCCD0(player);
    r->stats[7] = func_003DCD00(player);
    r->stats[8] = func_003DCD30(player);
    func_002CA590(g_00669D60.players[player].data_0, r->block_4c);
    r->value_80 = g_00669D60.players[player].value_4;
    r->value_88 = g_00669D60.players[player].value_c;
    r->value_84 = g_00669F9C;

    if (g_00749110[func_00362320(player)] + g_0074941C < 1)
        points = 0;
    else
        points = g_00749110[func_00362320(player)] + g_0074941C;
    if (points >= 0x10000)
        points = 0xFFFF;
    r->points = points;

    if (points >= 0 && points < 2000)
        r->rank = 4;
    else if (points >= 2000 && points < 3000)
        r->rank = 3;
    else if (points >= 3000 && points < 4000)
        r->rank = 2;
    else if (points >= 4000 && points < 10000)
        r->rank = 1;
    else
        r->rank = 0;

    if (g_00669D81 == 4)
        r->rating_points = r->points * 2;
    else if (g_00669D81 == 3)
        r->rating_points = r->points;
    else if (g_00669D81 == 2 || g_00669D81 == 1 || g_00669D81 == 0)
        r->rating_points = r->points / 3;
}

/* 0x0021AB90, 0xC8 bytes. Non-zero when the player's level (halved, at most 6) is below the
 * officer's (func_002F41E0, halved, at most 6): a new rank of something? */
int func_0021AB90(int player)
{
    u32 a, b;

    if (func_003DCB00(player) / 2 < 7)
        a = func_003DCB00(player) / 2;
    else
        a = 6;
    if ((func_002F41E0(g_00669D60.players[player].data_0) & 0xFF) >> 1 < 7)
        b = (func_002F41E0(g_00669D60.players[player].data_0) & 0xFF) >> 1;
    else
        b = 6;
    return (a & 0xFF) < b;
}

/* A skill on a player's list (8 bytes). */
typedef struct {
    int skill;               /* 0xFF = none */
    u8 level;
    u8 state;
    u8 pad[2];
} SkillEntry;

/* 0x0021AC60, 0xAC bytes. Gives `player`'s officer the skills of the list `list` (except skills
 * 0x28-0x34). */
void func_0021AC60(int player, SkillEntry *list)
{
    int i;

    for (i = 0; i < ((u8 *)list)[0x148]; i++)
        if (list[i].skill < 0x28 || list[i].skill > 0x34)
            func_002F4820(g_00669D60.players[player].data_0, list[i].skill, list[i].level);
}



/* A skill on a player's list (8 bytes); each player has 0x14C bytes of them at 0x00747B60, the
 * count in the byte at +0x148. */
typedef struct {
    SkillEntry entries[41];
    u8 count;                /* +0x148 */
    u8 pad[3];
} SkillList;
extern SkillList g_00747B60[2];

extern u8 g_00428B79[];                   /* default item records, 0x13 bytes per kind */
extern u8 g_00748C30[];                   /* per player, 0x14 bytes: the item being offered */
extern u8 g_00748C58[];                   /* per player, 0x14 bytes: the item it replaces */
extern u8 g_007489DC[], g_007489F0[], g_00748AC8[];
extern int g_00748FAC[2];
extern u8 g_00748F70;
extern int g_00747948;
extern int g_007729DC;
extern u8 g_00748A2C, g_00748A2D;
extern int g_00669F6C;
extern u8 g_006935DB_state;               /* message box 1 state (see scene_shop.c) */
extern const char *g_0043C31C;            /* "Saving here will update your per..." */

void func_00328BA0(int item, int value);
int func_002F57A0(int item);
u8 *func_00328B30(int item);
int func_002F57F0(int item);
u8 func_002F5840(int kind);
int func_003278B0(void);
int func_003A02F0(int item);
int func_00328C00(int item);
int func_0030AAD0(int kind);
int func_002F9480(u32 force, int kind);
void func_0021C090(void);
void func_0021C0D0(void);
void func_0021C1D0(void);
void func_0021C1F0(void);
void func_0021C280(void);
void func_0011EB80(void *dst, const void *src, int size);
void func_0019DDC0(void *item);
void func_0017DF10(void);
int func_0019FB90(void);
int func_0036B2F0(void);
void func_002EFB40(void);
void func_002885E0(void *data);
void func_0028C310(void);
void func_00289100(void);
void func_001A2940(void);
void func_001204B0(char *dst, const char *format, ...);
void func_001B8BF0(void);
void func_001AE9F0(int box, const char *text, int c);
void func_001AFC50(int box);

/* 0x0021B270, 0x104 bytes. Gives the player item `item` with the default values of its kind
 * (table 0x00428B79, 0x13 bytes per kind). */
void func_0021B270(int item)
{
    const u8 *def;
    u8 *rec;
    int i;

    func_00328BA0(item, 1);
    def = &g_00428B79[func_002F57A0(item & 0xFF) * 0x13];
    rec = func_00328B30(item);
    rec[1] = def[0];                       /* (byte 1 of the default is not used) */
    for (i = 2; i < 0x12; i++)
        rec[i] = def[i];
    rec[0x12] = func_002F5840(func_002F57F0(item));
    rec[0x13] = 0;
}

/* 0x0021B380, 0x1A8 bytes. Non-zero (and the item is given, func_0021B270) when the current
 * player earns the item of their last result: not in the Empire game (g_00748F84), when the item
 * is not owned yet, the force has at least 4 of its kind and items are allowed (g_00748F94). */
int func_0021B380(void)
{
    int player = g_00749528 != 0;
    u8 *rec = &g_00748938[player * 0x52];
    int kind = func_002F57A0(rec[rec[0x51] * 0x14]);
    int item;

    if (g_00748FA4[player] == 0x1A) {
        kind = 0x1D;
        item = 0x78;
    } else {
        item = kind * 4 + 3;
    }
    if (g_00748F84 != 0)
        return 0;
    if (func_002F59A0(0) == 0 && (func_003278B0() == 0 || func_003A02F0(item) == 0) &&
        g_00669D60.players[player].value_4 < 500)
        return 0;
    if (func_00328C00(item) != 0)
        return 0;
    if (func_002F9480(func_00327D50(), func_0030AAD0(kind)) < 4)
        return 0;
    if (g_00748F94 == 0)
        return 0;
    func_0021B270(item);
    return 1;
}

/* 0x0021B530, 0x110 bytes. Non-zero when the item offered to the current player differs from the
 * one it replaces (kind, values or the last byte). */
int func_0021B530(void)
{
    u8 *a = &g_00748C30[g_0074794C * 0x14];
    u8 *b = &g_00748C58[g_0074794C * 0x14];
    int i;

    if (func_003A02F0(a[0]) == 0)
        return 0;
    if (a[1] != b[1])
        return 1;
    for (i = 0; i < func_002F5840(func_002F57F0(a[0])); i++)
        if (a[i + 2] != b[i + 2] || a[i + 10] != b[i + 10])
            return 1;
    return a[0x13] != b[0x13];
}

/* 0x0021B640, 0x20 bytes. */
int func_0021B640(void)
{
    return g_00749520[g_0074794C];
}

/* 0x0021B660, 0x3D8 bytes. Goes to page `page` of the results (0 summary ... 10 leaving), or
 * skips it when it has nothing to show, and starts the page's window (func_002857E0). */
void func_0021B660(int page)
{
    int next = g_00747938;

    g_00772A00 = 1;
    switch (page) {
    case 0:
        g_00747938 = page;
        func_002857E0(10);
        next = g_00747938;
        break;
    case 1:
        if (func_0021B380() == 0) {
            func_0021C090();
            func_0021B660(2);
            next = g_00747938;
        } else {
            g_00747938 = page;
            func_002857E0(0x0B);
            next = g_00747938;
        }
        break;
    case 2:
        g_00747938 = page;
        func_002857E0(0);
        next = g_00747938;
        break;
    case 3:
        if (func_0021AB90(g_0074794C) == 0) {
            func_0021B660(4);
            next = g_00747938;
        } else {
            g_00747938 = page;
            func_002857E0(0x0D);
            next = g_00747938;
        }
        break;
    case 4:
        if (g_00747B60[g_0074794C].count == 0) {
            func_0021C0D0();
            func_0021C1D0();
            func_0021B660(5);
            next = g_00747938;
        } else {
            g_00747938 = page;
            func_002857E0(9);
            next = g_00747938;
        }
        break;
    case 5:
        if (g_00748FAC[g_0074794C] == 0) {
            if (g_0074794C == 1 && g_00748F98 == 2 && g_007489DC[0] == g_007489F0[0])
                func_0011EB80(g_007489F0, g_007489DC, 0x14);
            func_0021B660(7);
            next = g_00747938;
        } else {
            func_002857E0(0x0F);
            g_00748F70 = 0;
            g_00748F71 = 0;
            g_00748F72 = 0;
            g_00748F73 = 0;
            next = page;
        }
        break;
    case 6:
        func_0011EB80(&g_007489DC[g_0074794C * 0x14], g_00748AC8, 0x14);
        func_0019DDC0(&g_007489DC[g_0074794C * 0x14]);
        if (func_0021B530() == 0) {
            func_0021C280();
            func_0021B660(7);
            next = g_00747938;
        } else {
            g_00747938 = page;
            func_002857E0(0x10);
            next = g_00747938;
        }
        break;
    case 7:
        if (func_0021B640() == 0) {
            func_0021B660(8);
            next = g_00747938;
        } else {
            func_0021C1F0();
            g_00747938 = page;
            func_002857E0(0x11);
            next = g_00747938;
        }
        break;
    case 8:
        if (!TWO_PLAYERS() || g_0074794C != 0) {
            g_00747938 = page;
            func_002857E0(0x12);
            next = g_00747938;
        } else {
            g_00749528 = 1;
            func_0021B660(1);
            next = g_00747938;
        }
        break;
    case 9:
        if (g_00748F84 == 1) {
            func_0017DF10();
            next = page;
        } else if (g_00748F84 == 0) {
            func_0017DF10();
            func_0021B660(10);
            next = g_00747938;
        }
        break;
    case 10:
        next = page;
        if (g_00748F84 == 1 && func_0019FB90() != 0 &&
            (func_0036B2F0() != 0 || (g_00669F6C == 0 && g_0074952C != 0)))
            func_002EFB40();
        break;
    case 11:
        next = page;
        break;
    }
    g_00747938 = next;
    g_00747940 = 2;
}

/* 0x0021BA40, 0x234 bytes. Moves to the page asked for (g_00747938); pages 9-11 leave the scene. */
void func_0021BA40(void)
{
    g_0074793C = g_00747934;
    g_00772A00 = 0;
    g_00748F80 = 1;
    g_00747934 = g_00747938;
    if (TWO_PLAYERS() && g_00749528 != 0) {
        g_0074794C = 1;
        g_00772D4C = 1;
    }
    if (g_00747938 == 9) {
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
            g_0045D89C = 1;
    } else if (g_00747938 == 10 || g_00747938 == 11) {
        if (g_00747938 == 10) {
            if (g_00669DB8 == 0 && g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
                g_0045D89C = 0x12;
        } else if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18) {
            g_0045D89C = 1;
        }
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
}

/* 0x0021BC80, 0x200 bytes. Opens page g_00747934 (sets the shown page g_00747930); page 9 asks
 * whether to save. */
void func_0021BC80(void)
{
    char text[256];

    switch (g_00747934) {
    case 0: g_00747930 = 0; break;
    case 1: g_00747930 = 1; break;
    case 2:
        if (g_00747E90 != 0) {
            func_002857E0(0x0C);
            func_002885E0(&g_00747DF8[g_0074794C]);
        }
        g_00747930 = 2;
        break;
    case 3:
        g_00747930 = 3;
        func_0028C310();
        break;
    case 4:
        g_007729DC = g_0074794C;
        if (g_00747B60[g_0074794C].count == 1) {
            g_00748A2C = 1;
            g_00748A2D = 1;
        } else {
            g_00748A2C = 2;
            g_00748A2D = 2;
        }
        g_00747930 = 4;
        func_00289100();
        break;
    case 5:
        g_00748F70 = 0;
        g_00747930 = 5;
        break;
    case 6: g_00747930 = 6; break;
    case 7: g_00747930 = 7; break;
    case 8: g_00747930 = 8; break;
    case 9:
        func_0017DF10();
        func_001A2940();
        func_001204B0(text, g_0043C31C);
        func_001B8BF0();
        func_001AE9F0(1, text, 1);
        func_001AFC50(1);
        g_006935DB_state = 5;
        g_00747948 = 0;
        g_00747930 = 9;
        break;
    case 10:
        g_00747930 = 10;
        break;
    }
}


/* Entry of the item screen's data for each scenario (func_003623B0), 0 when none. */
static const u8 s_scenario_entry[0x1E] = {
    0x56, 0x44, 0x52, 0x4F, 0x48, 0x5B, 0x50, 0x49, 0x43, 0x57, 0x51, 0x4C, 0x47, 0x46, 0x58,
    0x53, 0x54, 0x45, 0x4E, 0x5D, 0x4D, 0x42, 0x4A, 0x5A, 0x4B, 0x4A, 0x42, 0x55, 0x5C, 0x45,
};

/* 0x0021BE80, 0x138 bytes. LINKDATA entry loaded by enter for the current scenario (a switch in
 * the original). */
int func_0021BE80(void)
{
    u32 scenario = func_003623B0();

    if (scenario < 0x1E)
        return s_scenario_entry[scenario];
    return 0;
}

extern u8 g_00748A04[];                   /* per player, 0x14 bytes: the item kept */
void func_002205E0(int player);
void func_002206B0(int player);

/* 0x0021BFC0, 0xD0 bytes. Copies player `player`'s last item (0x00748938 record, index at +0x51)
 * to the offered item (0x007489DC) and to the kept item (0x00748A04), the latter with its default
 * values when the item is known (func_0021A720). */
void func_0021BFC0(int player)
{
    u8 *src = &g_00748938[player * 0x52 + g_00748938[player * 0x52 + 0x51] * 0x14];
    u8 tmp[32];

    func_0011EB80(&g_007489DC[player * 0x14], src, 0x14);
    if (func_003A02F0(src[0]) == 0) {
        func_0011EB80(&g_00748A04[player * 0x14], &g_007489DC[player * 0x14], 0x14);
    } else {
        func_0021A720(tmp, src[0]);
        func_0011EB80(&g_00748A04[player * 0x14], tmp, 0x14);
    }
}

extern int g_00748A60[11];                /* item screen: 0x00748A60-0x00748A88 */
extern int g_00748AA4[9];                 /* 0x00748AA4-0x00748AC4 */
extern int g_00748ADC[24];                /* 0x00748ADC-0x00748B38 */
extern int g_00748CAC, g_00748CB0;

/* 0x0021C090, 0x38 bytes. Clears the item screen's values. */
void func_0021C090(void)
{
    int i;

    for (i = 0; i < 11; i++)
        g_00748A60[i] = 0;
}

/* 0x0021C0D0, 0xFC bytes. Prepares the skill screen for the current player: its lists
 * (func_002205E0, func_002206B0), a copy of the offered item, and the screen's default values. */
void func_0021C0D0(void)
{
    int i;

    func_002205E0(g_0074794C);
    func_002206B0(g_0074794C);
    func_0011EB80(g_00748AC8, &g_007489DC[g_0074794C * 0x14], 0x14);
    for (i = 0; i < 3; i++)
        g_00748AA4[i] = 0;
    for (i = 3; i < 9; i++)
        g_00748AA4[i] = 1;
    g_00748ADC[0] = 0;
    for (i = 0; i < 12; i++)
        g_00748ADC[1 + i] = (i & 1) ? 8 : 6;            /* 0x00748AE0-0x00748B0C: 6, 8, 6, 8... */
    for (i = 13; i < 21; i++)
        g_00748ADC[i] = 1;                              /* 0x00748B10-0x00748B2C */
    for (i = 21; i < 24; i++)
        g_00748ADC[i] = 8;                              /* 0x00748B30-0x00748B38 */
}

/* 0x0021C1D0, 0x14 bytes. */
void func_0021C1D0(void)
{
    g_00748CAC = 0;
    g_00748CB0 = 0;
}

extern u8 g_00748CB4[];
extern int g_00749438[2], g_007494D0[2];
extern u8 g_00749440[];                   /* 0x24 bytes per player */
void func_003DF970(int item, void *a, int b, int c, void *d);

/* 0x0021C1F0, 0x84 bytes. */
void func_0021C1F0(void)
{
    int player = g_0074794C;

    func_003DF970(func_003294A0(g_0074794C), g_00748CB4, g_00749438[g_0074794C],
                  g_007494D0[g_0074794C], &g_00749440[player * 0x24]);
}

/* 0x0021C280, 0x104 bytes. Keeps the item chosen on the item screen (g_00748CB0: 0 keep the new
 * one), and in two-player games copies player 0's item to player 1 when they are the same kind. */
void func_0021C280(void)
{
    if (g_00748CB0 == 0)
        func_0011EB80(&g_00748A04[g_0074794C * 0x14], g_00748AC8, 0x14);
    else if (g_00748CB0 == 1 && g_0074794C == 1 && g_00748F98 == 2 &&
             g_007489F0[0] == g_007489DC[0])
        func_0011EB80(g_007489F0, g_007489DC, 0x14);
    if (g_0074794C == 0 && g_00748F98 == 2 && g_00748A04[0] == g_00748A04[0x14])
        func_0011EB80(&g_00748A04[0x14], g_00748A04, 0x14);
}


int func_002F4080(int officer);
int func_002FB2A0(int value);
void func_00328A00(int officer, int value);
int func_003635F0(void);
void func_003A4DA0(int scenario, int b, int points, int c);

/* 0x0021C390, 0x254 bytes. Saves the battle's results: the kept items (0x00748A04) into the item
 * records, unlocks officers (func_00328A00) of side 0 below 0x1C whose level is above 9 (in the
 * Empire game only when func_002FB2A0 agrees), records the best player's points for the scenario
 * (func_003A4DA0), then the offered items (0x007489DC). */
void func_0021C390(void)
{
    int i, best, officer, points;

    for (i = 0; i < g_00748F98; i++) {
        u8 *item = &g_00748A04[i * 0x14];
        func_0019DDC0(item);
        func_0011EB80(func_00328B30(item[0]), item, 0x14);
    }
    for (i = 0; i < 8; i++) {
        officer = func_003620E0(0, i);
        if (officer >= 0x1C)
            continue;
        if (g_00748F84 == 0) {
            if (func_002F41E0(officer) > 9 && func_002FB2A0(func_002F4080(officer)) != 0)
                func_00328A00(officer, 1);
        } else if (g_00748F84 == 1 && func_002F41E0(officer) > 9) {
            func_00328A00(officer, 1);
        }
    }
    best = 0;
    for (i = 0; i < g_00748F98; i++) {
        points = g_00749110[func_00362320(i)] + g_0074941C;
        if (best < points)
            best = points;
    }
    if (best > 0xFFFF)
        best = 0xFFFF;
    func_003A4DA0(func_003623B0(), func_003635F0(), best, g_00748F94);
    for (i = 0; i < g_00748F98; i++) {
        u8 *item = &g_007489DC[i * 0x14];
        func_0019DDC0(item);
        func_0011EB80(func_00328B30(item[0]), item, 0x14);
    }
}


int func_002F6A60(int officer);           /* the officer's weapon skill */
int func_002F47A0(int officer, int skill);/* skill level */
int func_003DCB30(int player, int skill); /* the skill's level before the battle */

/* A skill learnt during the battle, in the game state (8 records of 8 bytes at 0x00669F20). */
typedef struct {
    int skill;
    u8 level;
    u8 player;
    u8 state;                /* 2 = not to show */
    u8 pad;
} LearntSkill;
#define g_00669F20 ((LearntSkill *)((u8 *)&g_00669D60 + 0x1C0))

/* 0x0021AD10, 0x550 bytes. Builds player `player`'s list of skills that went up in the battle
 * (0x00747B60): the weapon skill first, then skills 0-0x27 whose level rose, then (when the
 * player's results are shown) the skills learnt in the battle, inserted in skill order (a skill
 * already listed keeps the higher level). Skills 0x28-0x34 are skipped when looking for the place. */
void func_0021AD10(int player)
{
    SkillList *list = &g_00747B60[player];
    SkillEntry *p = list->entries;
    int officer = func_003620E0(0, func_00362320(player));
    int i, skill;

    for (i = 0; i < 41; i++) {
        list->entries[i].skill = 0xFF;
        list->entries[i].state = 2;
        list->entries[i].level = 4;
        list->count = 0;
    }

    if (func_003DCB30(g_0074794C, func_002F6A60(g_00748FA4[g_0074794C])) <
        (int)(func_002F47A0(officer, func_002F6A60(officer)) & 0xFF)) {
        p->skill = func_002F6A60(officer);
        p->state = 0;
        p++;
        list->count++;
    }
    for (skill = 0; skill < 0x28; skill++) {
        if (func_003DCB30(g_0074794C, skill) < (int)(func_002F47A0(officer, skill) & 0xFF)) {
            p->skill = skill;
            p->level = (u8)func_002F47A0(officer, skill);
            p->state = 0;
            p++;
            list->count++;
        }
    }

    if (g_00747DF8[player].shown == 0)
        return;
    for (i = 0; i < 8; i++) {
        LearntSkill *l = &g_00669F20[i];
        SkillEntry *q;
        int at = 0, n;

        if (l->player != player || l->state == 2)
            continue;
        for (q = list->entries; q->skill < l->skill || (q->skill >= 0x28 && q->skill < 0x35); q++)
            at++;
        if (q->skill == l->skill) {
            if (q->level <= l->level)
                q->level = l->level;
            continue;
        }
        for (n = list->count; n > at; n--)             /* make room */
            list->entries[n] = list->entries[n - 1];
        q = &list->entries[list->count > at ? at : list->count];
        q->skill = l->skill;
        q->level = l->level;
        q->state = 0;
        list->count++;
    }
}


/* The item comparison of the item screen, per player (0x2C bytes at 0x00748B80): six values and
 * a copy of the offered item. */
typedef struct {
    int value[6];
    u8 item[0x14];
} ItemCompare;
extern ItemCompare g_00748B80[2];
extern int g_00748B7C;
extern int g_00748C90, g_00748C94, g_00748C98, g_00748C9C;
extern u8 g_00748CA8;

/* 0x002205E0, 0x98 bytes. Copies player `player`'s offered and kept items to the item screen's
 * pair (0x00748C30 / 0x00748C58), the kept one taking the offered one's kind. */
void func_002205E0(int player)
{
    u8 *offered = &g_00748C30[player * 0x14];
    u8 *kept = &g_00748C58[player * 0x14];

    func_0011EB80(offered, &g_007489DC[player * 0x14], 0x14);
    func_0011EB80(kept, &g_00748A04[player * 0x14], 0x14);
    if (offered[0] != kept[0])
        kept[0] = offered[0];
    g_00748CA8 = 0;
}

/* 0x00220680, 0x28 bytes. */
u8 *func_00220680(int player)
{
    return g_00748B80[player].item;
}

void func_002206F0(int player);

/* 0x002206B0, 0x34 bytes. */
void func_002206B0(int player)
{
    g_00748C94 = 0;
    g_00748C90 = 4;
    g_00748C98 = 0;
    g_00748C9C = 0;
    func_002206F0(player);
}

/* 0x002206F0, 0x8C bytes. Resets player `player`'s item comparison with the offered item. */
void func_002206F0(int player)
{
    int i;

    func_0011EB80(func_00220680(player), &g_00748C30[player * 0x14], 0x14);
    for (i = 0; i < 6; i++)
        g_00748B80[player].value[i] = 0;
    g_00748B7C = 0;
    g_00748C94 = 0;
}

/* 0x00220140, 0x8 bytes, matching. Scene step: empty. */
void func_00220140(void)
{
}


/* The item being edited on the item screen (0x00748AC8, a 0x14-byte item record): +0 item,
 * +1 kind, +2 eight attributes, +10 their values, +0x12 number of attributes, +0x13 a bonus. */
#define g_00748AC9 (g_00748AC8[1])
#define g_00748ADA (g_00748AC8[0x12])
#define g_00748ADB (g_00748AC8[0x13])

/* The choices made on the item screen, per player (0x30 bytes at 0x0074901C): (type, value)
 * pairs. */
typedef struct {
    int type;                /* 10-14 kind, 15 bonus, else an attribute */
    int value;
} ItemChoice;
extern ItemChoice g_0074901C[2][6];
extern u8 g_00428138[];                   /* base bonus of each kind */

/* 0x0021E1F0, 0x22C bytes. Undoes the item screen's choices back to choice `count`: restarts from
 * the offered item and replays the first `count` choices (g_00748ADC: number of choices made,
 * then (choice, slot) pairs). */
void func_0021E1F0(int count)
{
    int i;

    if (count >= g_00748ADC[0])
        return;
    g_00748ADC[0] = count;
    func_0011EB80(g_00748AC8, &g_007489DC[g_0074794C * 0x14], 0x14);
    for (i = 3; i < 9; i++)
        g_00748AA4[i] = 1;
    for (i = 0; i < count; i++) {
        int choice = g_00748ADC[1 + 2 * i];
        int slot = g_00748ADC[2 + 2 * i];
        ItemChoice *c = &g_0074901C[g_0074794C][choice];

        g_00748AA4[3 + choice] = 0;
        if (c->type >= 10 && c->type <= 14) {
            static const u8 kinds[5] = { 1, 3, 2, 4, 5 };        /* types 10-14 */
            g_00748AC9 = kinds[c->type - 10];
        } else if (c->type == 15) {
            g_00748ADB = (u8)(c->value - g_00428138[g_00748AC8[0]]);
        } else {
            g_00748AC8[2 + slot] = (u8)c->type;
            g_00748AC8[10 + slot] = (u8)c->value;
        }
    }
}

/* 0x0021E430, 0xEC bytes. Marks (g_00748ADC[13 + i]) the attributes of the edited item equal to
 * `attribute`; returns the first marked one, or with fewer than 3 marked, clears the marks and
 * returns the first free slot (attribute 10 or more), else 0. */
int func_0021E430(u32 attribute)
{
    int i, first_free = 8, first_marked = 8, marked = 0;

    for (i = 0; i < g_00748ADA; i++) {
        g_00748ADC[13 + i] = 0;
        if (g_00748AC8[2 + i] < 10) {
            if (g_00748AC8[2 + i] == attribute) {
                g_00748ADC[13 + i] = 1;
                if (i < first_marked)
                    first_marked = i;
                marked++;
            }
        } else if (i < first_free) {
            first_free = i;
        }
    }
    if (marked < 3) {
        for (i = 13; i < 21; i++)
            g_00748ADC[i] = 1;
        first_marked = first_free == 8 ? 0 : first_free;
    }
    return first_marked;
}


/* Controllers (see scene_shop.c): 0x88 bytes each at 0x00500700. */
extern u8 g_00500700_pads[];
#define PAD_READY(n) ((g_00500700_pads[(n) * 0x88 + 0x64] & 1) ? \
                      (g_00500700_pads[(n) * 0x88 + 0x65] & 1) == 1 : 0)
#define PAD_PRESSED(n) (*(unsigned short *)&g_00500700_pads[(n) * 0x88 + 0x4C])

extern u8 g_006934B4_answers[];           /* message box answers, 0x128 bytes per box */
extern const char *g_004563A0;            /* "This weapon's data will be saved..." */
void func_0023AD10(int a, int b, int c, int d, int e);
void func_001AEDE0(int box, int width);
void func_001AFC70(int box, int pad);

/* 0x0021ED70, 0x1D4 bytes. Item screen, "keep which one" step (controller `pad`, open box `box`):
 * a "yes" in the question box keeps the choice and moves on (page 7); OK asks to confirm, Up or
 * Down switches between the new and the old item (g_00748CB0). Returns 1 while a box is busy. */
int func_0021ED70(int pad, int box)
{
    unsigned short pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    char text[256];
    char answer;

    if (g_00748CAC == 0)
        g_00748CAC = 1;
    if (g_00748CAC != 1)
        return 0;
    answer = box == 5 ? 0 : (char)g_006934B4_answers[box * 0x128];
    if (box == 1) {
        if (answer == 4) {
            func_0021C280();
            func_0021B660(7);
        }
        return 1;
    }
    if (pressed & 0x40) {
        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
        func_001204B0(text, g_004563A0);
        func_001B8BF0();
        func_001AEDE0(1, 0x96);
        func_001AE9F0(1, text, 1);
        func_001AFC70(1, pad);
        return 1;
    }
    if (pressed & 0x5000) {
        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
        if (g_00748CB0 == 0)
            g_00748CB0 = 1;
        else if (g_00748CB0 == 1)
            g_00748CB0 = 0;
    }
    return 0;
}


typedef unsigned long long u64;

extern int g_0056CCA4, g_0056CCA8, g_0056CCAC, g_0056CCB0;    /* drawing modes */
extern u8 *g_005BD724;
extern const char *g_0043C5EC, *g_0043C610, *g_0043C6E4, *g_0043C6E8, *g_0043C804;
extern const char *g_00456368;            /* "Please select the weapon whose d..." */

void func_00285E50(u32 a, u32 b, u32 c, int d, int e);
u8 *func_001050F0(void);
void func_00105390(u8 *packet);
u8 *func_00105410(void);
void func_00105560(u8 *packet);
void func_003F11D0(void);
int func_0036B260(void);
void func_003DACA0(void);
void func_003DAF70(void);
void func_003DC300(void);
void func_0028D0D0(u32 a, u32 b, int c, int d, int player, PlayerResult *r);
void func_0028A420(u32 a, u32 b, SkillEntry *list);
void func_003DE580(void);
void func_003E0910(void);
void func_003E0290(void);
void func_003E0730(void);
int func_003F1160(int value);
void func_001A7DC0(const char *text, int alpha, int b);
void func_003838B0(const char *text, int b);
void func_00285D50(u32 a, int page, u8 b, int c);
void func_002DAE50(void);

/* 0x00220150, 0x484 bytes. Scene draw: the background, a darkened band (two GS packets), the
 * current page (with the drawing modes forced to 3), then its button help line. */
void func_00220150(void)
{
    u8 *packet;
    int saved;

    if (g_00747934 >= 9) {
        func_002DAE50();
        return;
    }
    func_00285E50(g_00747950, g_00747960, g_00669D60.players[g_0074794C].data_0, 0, g_0074796C);
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

    saved = g_0056CCA4;
    g_0056CCAC = 3;
    g_0056CCA4 = 3;
    g_0056CCA8 = 3;
    g_0056CCB0 = 3;
    func_003F11D0();
    switch (g_00747934) {
    case 0:
        if (func_0036B260() != 0)
            func_003DACA0();
        break;
    case 1: func_003DAF70(); break;
    case 2:
        func_003DC300();
        func_002857E0(0x13);
        break;
    case 3:
        func_0028D0D0(g_00747958, g_00747950, 0, 0, g_0074794C, &g_00747DF8[g_0074794C]);
        break;
    case 4:
        func_0028A420(g_00747958, g_00747950,
                      &g_00747B60[g_0074794C].entries[g_00748A2D - g_00748A2C]);
        break;
    case 5: func_003DE580(); break;
    case 6: func_003E0910(); break;
    case 7: func_003E0290(); break;
    case 8: func_003E0730(); break;
    }
    g_0056CCA8 = saved;
    g_0056CCAC = saved;
    g_0056CCB0 = saved;
    g_0056CCA4 = saved;

    if (func_003F1160(0) == 0) {
        switch (g_00747934) {
        case 5:
            if (g_00748AA4[0] != 0)
                func_001A7DC0(g_0043C6E8, 0x80, 0);
            else if (g_00748AA4[1] == 6)
                func_001A7DC0(g_0043C804, 0x80, 0);
            else
                func_001A7DC0(g_0043C6E4, 0x80, 0);
            break;
        case 6:
            func_003838B0(g_00456368, 0);
            func_001A7DC0(g_0043C610, 0x80, 0);
            break;
        case 0: case 1: case 2: case 3: case 4: case 7: case 8:
            func_001A7DC0(g_0043C5EC, 0x80, 0);
            break;
        }
    }
    func_00285D50(g_00747950, g_00747934, g_005BD724[4], 0);
}
extern u8 g_006934B3_state;               /* message box 0 state */
extern u8 g_0069395E_state;               /* box 1 open when neither 0 nor 0xFF */


extern int g_00747970;                    /* frames before leaving */
extern u8 *g_005BA6A0_bases;              /* sc_ubase.c records, 0x2C bytes (see MISC.md 0051) */
extern const char *g_00456318;            /* "... %s ... %s" (item earned) */
extern const char *g_0042DC10[];          /* item names ("Cross Spear"...) */

int func_0021D0D0(int pad, int box);
int func_0021D6A0(int pad);
int func_0021E520(int pad);
int func_0021EF50(int pad);
int func_003F13E0(void);
void func_002872E0(PlayerResult *r);
void func_0028A3D0(void);
void func_00288990(void);
int func_00362160(int side, int slot);
const char *func_0019B170(char *buf, int a, int b);
int func_003DFAB0(void *data, int pad);
int func_002DAC30(void);
void func_002D8160(void);
void func_002DBA90(void);
void func_002D8060(int value);
void func_003A3CE0(int item);
void func_003F1070(int value);

/* Which message box is open (0, 1, or 5 for none), as the scene tests it. */
static int open_box(void)
{
    if (g_006934B3_state != 0)
        return 0;
    if (g_006935DB_state != 0)
        return 1;
    return 5;
}

/* 0x0021F680, 0xAB0 bytes. Scene update. g_00747940 is the window phase: 0 in use (runs the
 * shown page's handler), 2 closing then fade (6), 3/4 opening, 5 waits for box 1 then opens the
 * page, 6 waits for every box then switches page (func_0021BA40), 7 back to 5. Player 2's
 * controller is used for player 2's pages. */
int func_0021F680(void)
{
    int player = g_0074794C;
    int box, pad = 0, item;
    unsigned short pressed;
    char text[256], name[32];
    u8 *last = &g_00748938[player * 0x52 + g_00748938[player * 0x52 + 0x51] * 0x14];

    item = func_002F57A0(last[0]);
    if (g_00748FA4[player] == 0x1A)
        item = 0x78;
    else
        item = item * 4 + 3;
    if (player == 0 || g_00747934 == 0 || g_00747934 == 8)
        pad = 0;
    else if (player == 1)
        pad = 1;
    pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    box = open_box();
    g_0074796C++;

    switch (g_00747940) {
    case 0:
        if (g_007729FC == 0) {
            g_00747940 = 1;
        } else if (g_00748F80 != 0 && (pressed & 0x40)) {
            g_00748F80 = 0;
            func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_002872E0(&g_00747DF8[player]);
        }
        if (g_00747930 == 4 && (pressed & 0x40) && g_007729FC != 0) {
            func_0028A3D0();
            g_00747940 = 1;
        }
        break;
    default:
        if (func_003F13E0() != 0)
            return 0;
        switch (g_00747930) {
        case 0:
            func_0021D0D0(pad, box);
            return 1;
        case 1: {                                   /* an item was earned */
            char answer = box == 5 ? 0 : (char)g_006934B4_answers[box * 0x128];
            if (box != 0) {
                u8 *base = &g_005BA6A0_bases[func_00362160(0, func_00362320(player)) * 0x2C];
                func_001204B0(text, g_00456318,
                              func_0019B170(name, ((short *)base)[0], ((short *)base)[1]),
                              g_0042DC10[item]);
                func_001B8BF0();
                func_001AEDE0(0, 300);
                func_001AE9F0(0, text, 1);
                func_001AFC70(0, pad);
                return 1;
            }
            if (answer == 1) {
                func_0021C090();
                func_0021B660(2);
            }
            return 1;
        }
        case 2:
            func_0021D6A0(pad);
            return 1;
        case 3:
            if (box == 0)
                return 0;
            if (pressed & 0x40) {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021B660(4);
            }
            break;
        case 4:                                     /* skills, two at a time */
            if (pressed & 0x40) {
                if (g_007729FC == 0) {
                    int left = g_00747B60[player].count - g_00748A2D;
                    if (left == 0) {
                        func_0021C0D0();
                        func_0021C1D0();
                        func_0021B660(5);
                        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                    } else if (left == 1) {
                        g_00748A2C = 1;
                        g_00748A2D++;
                        func_00288990();
                        func_00289100();
                        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                    } else if (left > 1) {
                        g_00748A2D += 2;
                        g_00748A2C = 2;
                        func_00288990();
                        func_00289100();
                        func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                    }
                } else {
                    func_0028A3D0();
                    func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                }
            }
            break;
        case 5:
            func_0021E520(pad);
            break;
        case 6:
            func_0021ED70(pad, box);
            return 1;
        case 7:
            if (func_003DFAB0(g_00748CB4, pad) != 0) {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021B660(8);
            }
            break;
        case 8:
            func_0021EF50(pad);
            break;
        case 9:                                     /* save? */
            if (g_00747948 == 1) {
                int r = func_002DAC30();
                if (r == 2) {
                    func_002D8160();
                    func_001204B0(text, g_0043C31C);
                    func_001B8BF0();
                    func_001AE9F0(1, text, 1);
                    func_001AFC50(1);
                    g_006935DB_state = 5;
                    g_00747948 = 0;
                } else if (r == 1) {
                    g_0074952C = 1;
                    func_002D8160();
                    func_0021B660(10);
                }
            } else if (g_00747948 == 0) {
                char answer = box == 5 ? 0 : (char)g_006934B4_answers[box * 0x128];
                if (box == 1) {
                    if (answer == 4) {                  /* yes: save */
                        func_002DBA90();
                        func_002D8060(0);
                        g_00747948 = 1;
                    } else if (answer == 5) {           /* no: keep the items, leave */
                        int i, prev = 0;
                        u8 *first = 0;
                        for (i = 0; i < g_00748F98; i++) {
                            u8 *rec = &g_00748938[i * 0x52 + g_00748938[i * 0x52 + 0x51] * 0x14];
                            if (i == 0) {
                                first = rec;
                                func_0011EB80(func_00328B30(rec[0]), rec, 0x14);
                                func_003A3CE0(rec[0]);
                                prev = rec[0];
                            } else if (i == 1) {
                                if (first[0] != rec[0]) {
                                    func_0011EB80(func_00328B30(rec[0]), rec, 0x14);
                                    func_003A3CE0(rec[0]);
                                }
                            } else {
                                func_003A3CE0(prev);
                            }
                        }
                        func_0021B660(10);
                    }
                } else {
                    func_001204B0(text, g_0043C31C);
                    func_001B8BF0();
                    func_001AE9F0(1, text, 1);
                    func_001AFC50(1);
                    g_006935DB_state = 5;
                    g_00747948 = 0;
                }
            }
            break;
        }
        break;
    case 2:
        if (g_007729FC == 0) {
            if (g_00747970 == 0) {
                func_001B8F60(0, 6, 8);
                g_00747940 = 6;
            } else {
                g_00747970--;
            }
        }
        break;
    case 3:
        if (g_007729FC == 0)
            g_00747940 = 1;
        break;
    case 4:
        if (g_007729FC == 0) {
            if (g_00747934 == 5)
                func_002857E0(4);
            g_00747940 = 3;
        }
        break;
    case 5:
        if (g_0069395E_state == 0 || g_0069395E_state == 0xFF) {
            func_0021BC80();
            g_00747940 = 0;
        }
        break;
    case 6:
        if (g_006934B3_state != 1 && g_006934B3_state != 8 &&
            g_006935DB_state != 1 && g_006935DB_state != 8 &&
            (g_0069395E_state == 0 || g_0069395E_state == 0xFF)) {
            func_0021BA40();
            if (g_00747934 == 6)
                func_003F1070(8);
            g_00747940 = 5;
            func_001B8F60(1, 6, 8);
        }
        break;
    case 7:
        g_00747940 = 5;
        break;
    }
    return 1;
}


/* ---- Counting pages: numbers that count up by 8 a frame, with a tick sound every other frame - */

#define PAD_REPEAT(n) (*(unsigned short *)&g_00500700_pads[(n) * 0x88 + 0x4E])

extern int g_00749410, g_00749414, g_00749418;   /* army page targets (0x00749414 negated) */
extern const char *g_0044D990;            /* "Your army has earned no experience..." */

/* One counting step: `value` goes up by 8 towards `target`, with a tick sound on odd frames
 * (`blink`). Sets `counting` to 0 once it got there. */
#define COUNT_UP(counting, value, target, blink)                        \
    do {                                                                \
        (counting) = (value) < (target);                                \
        if (counting) {                                                 \
            if (((blink) & 1) == 1)                                     \
            func_0023AD10(3, 0, 0x2CDC, 0x2CDC, 0x1000);                \
            (value) += 8;                                               \
            if ((value) > (target))                                     \
            (value) = (target);                                         \
            (blink) = ((blink) + 1) & 1;                                \
        }                                                               \
    } while (0)

/* 0x0021D0D0, 0x5CC bytes. Army experience page (controller `pad`, open box `box`): without
 * results (func_0036B260) shows "no experience" in box 0 and moves on (page 1) on its answer;
 * otherwise counts up five values one after another (g_00748A44 is the one counting; the 4th is
 * skipped when g_00669DB8 is set). OK shows them all at once, then moves on. */
int func_0021D0D0(int pad, int box)
{
    unsigned short pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    int counting;
    char text[256];
    char answer = box == 5 ? 0 : (char)g_006934B4_answers[box * 0x128];

    if (func_0036B260() == 0) {
        if (box == 0) {
            if (answer == 1)
                func_0021B660(1);
            return 1;
        }
        func_001204B0(text, g_0044D990);
        func_001B8BF0();
        func_001AE9F0(0, text, 1);
        func_001AFC50(0);
        return 1;
    }
    if (func_0036B260() != 0) {
        switch (g_00748A44) {
        case 0:
            COUNT_UP(counting, g_00748A30, g_00749410, g_00748A48);
            if (!counting) {
                g_00748A44 = 1;
                g_00748A48 = 0;
            }
            break;
        case 1:
            COUNT_UP(counting, g_00748A34, -g_00749414, g_00748A48);
            if (!counting) {
                g_00748A44 = 2;
                g_00748A48 = 0;
            }
            break;
        case 2:
            COUNT_UP(counting, g_00748A38, g_00749418, g_00748A48);
            if (!counting) {
                g_00748A44 = 3;
                g_00748A48 = 0;
            }
            break;
        case 3:
            COUNT_UP(counting, g_00748A3C, g_0074941C, g_00748A48);
            if (!counting) {
                if (g_00669DB8 == 0) {
                    g_00748A44 = 4;
                    g_00748A48 = 0;
                } else {
                    g_00748A44 = 5;
                }
            }
            break;
        case 4:
            COUNT_UP(counting, g_00748A40, g_00749434, g_00748A48);
            if (!counting)
                g_00748A44 = 5;
            break;
        }
        if (pressed & 0x40) {
            if (g_00748A44 < 5) {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                g_00748A30 = g_00749410;
                g_00748A44 = 5;
                g_00748A34 = -g_00749414;
                g_00748A38 = g_00749418;
                g_00748A3C = g_0074941C;
                g_00748A40 = g_00749434;
            } else {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021B660(1);
            }
        }
    }
    return 0;
}

/* The officer results page's counters, in g_00748A60. */
#define PB_COUNT0  (g_00748A60[0])         /* 0x00748A60 */
#define PB_COUNT1  (g_00748A60[1])
#define PB_COUNT2  (g_00748A60[2])
#define PB_COUNT3  (g_00748A60[3])
#define PB_COUNT5  (g_00748A60[5])         /* 0x00748A74: points */
#define PB_COUNT6  (g_00748A60[6])         /* 0x00748A78: gold */
#define PB_PHASE   (g_00748A60[7])         /* 0x00748A7C */
#define PB_BLINK   (g_00748A60[8])         /* 0x00748A80 (read as a byte) */
#define PB_WAIT    (g_00748A60[9])         /* 0x00748A84 */
#define PB_LEVEL   (g_00748A60[10])        /* 0x00748A88: experience shown */

/* Per officer slot targets of the officer results page. */
extern int g_0074907C[], g_007490A0[], g_007490C4, g_007490C8[];

/* The level gauge (0x00772674): two bytes of colour, a byte and a word. */
extern struct {
    u8 a, b, c, pad;
    int d;
} g_00772674_gauge;
#define SET_GAUGE(x) (g_00772674_gauge.a = (x), g_00772674_gauge.b = (x), \
                      g_00772674_gauge.c = 0, g_00772674_gauge.d = 0)

void func_002868F0(void);
int func_002861B0(void);
void func_003DC9E0(void);
void func_0028C330(int a, int b);
void func_003E0320(int value);

/* 0x0021D6A0, 0xB50 bytes. Officer results page: counts up the officer's values (phases 0-5),
 * runs an animation (6, 7), then on OK either shows a level-up (9 waits for box 1, 10 counts the
 * experience) or stores the skills and opens the skills page (3). OK during the counts shows
 * every value. */
int func_0021D6A0(int pad)
{
    unsigned short pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    int target, counting;

    switch (PB_PHASE) {
    case 0:
        COUNT_UP(counting, PB_COUNT0, g_0074907C[func_00362320(g_0074794C)], PB_BLINK);
        if (!counting) {
            PB_BLINK = 0;
            PB_PHASE = 1;
        }
        break;
    case 1:
        COUNT_UP(counting, PB_COUNT1, g_007490A0[func_00362320(g_0074794C)], PB_BLINK);
        if (!counting) {
            PB_BLINK = 0;
            PB_PHASE = 2;
        }
        break;
    case 2:
        COUNT_UP(counting, PB_COUNT2, g_007490C4, PB_BLINK);
        if (!counting) {
            PB_BLINK = 0;
            PB_PHASE = 3;
        }
        break;
    case 3:
        COUNT_UP(counting, PB_COUNT3, g_007490C8[func_00362320(g_0074794C)], PB_BLINK);
        if (!counting) {
            PB_BLINK = 0;
            PB_PHASE = 4;
        }
        break;
    case 4:
        COUNT_UP(counting, PB_COUNT5, g_00749110[func_00362320(g_0074794C)] + g_0074941C, PB_BLINK);
        if (!counting) {
            if (g_00669DB8 == 0)
                PB_PHASE = 5;
            else
                PB_PHASE = 6;
            PB_BLINK = 0;
        }
        break;
    case 5:
        COUNT_UP(counting, PB_COUNT6, g_00749180[g_0074794C], PB_BLINK);
        if (!counting) {
            PB_BLINK = 0;
            PB_PHASE = 6;
        }
        break;
    case 6:
        PB_PHASE = 7;
        func_002868F0();
        break;
    case 7:
        if (func_002861B0() != 0)
            PB_PHASE = 8;
        break;
    case 9:
        if (PB_WAIT == 0) {
            if (g_0069395E_state == 0 || g_0069395E_state == 0xFF) {
                func_001B8F60(1, 6, 8);
                PB_WAIT = 1;
            }
        } else if (g_0069395E_state == 0 || g_0069395E_state == 0xFF) {
            PB_PHASE = 10;
        }
        break;
    case 10:
        target = func_002F34E0(g_00748FA4[g_0074794C]);
        COUNT_UP(counting, PB_LEVEL, target, PB_BLINK);
        if (!counting) {
            SET_GAUGE(0x40);
            func_0028C310();
            PB_PHASE = 11;
        }
        break;
    }

    if ((pressed & 0x40) && (g_0069395E_state == 0 || g_0069395E_state == 0xFF)) {
        if (PB_PHASE < 6) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            PB_COUNT0 = g_0074907C[func_00362320(g_0074794C)];
            PB_COUNT1 = g_007490A0[func_00362320(g_0074794C)];
            PB_COUNT2 = g_007490C4;
            PB_COUNT3 = g_007490C8[func_00362320(g_0074794C)];
            PB_COUNT5 = g_00749110[func_00362320(g_0074794C)] + g_0074941C;
            PB_COUNT6 = g_00749180[g_0074794C];
            PB_PHASE = 6;
        } else if (PB_PHASE == 8) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            PB_WAIT = 0;
            if (func_0021A7C0(PB_COUNT5 + func_003DCBB0(g_0074794C)) >
                func_0021A7C0(func_003DCBB0(g_0074794C))) {        /* level up */
                PB_LEVEL = func_003DCBB0(g_0074794C);
                PB_PHASE = 9;
                func_003DC9E0();
            } else {
                func_0021AD10(g_0074794C);
                func_0021AC60(g_0074794C, g_00747B60[g_0074794C].entries);
                func_0021B660(3);
            }
        } else if (PB_PHASE == 10) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_0023AD10(7, 0, 0x2CDC, 0x2CDC, 0x1000);
            SET_GAUGE(0x40);
            func_0028C310();
            PB_LEVEL = func_002F34E0(g_00748FA4[g_0074794C]);
            PB_PHASE = 11;
        } else if (PB_PHASE == 11) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_0021AD10(g_0074794C);
            func_0021AC60(g_0074794C, g_00747B60[g_0074794C].entries);
            func_0021B660(3);
        }
    }
    return 0;
}

/* ---- Item screen ------------------------------------------------------------------------------ */

#define ITEM_MODE    (g_00748AA4[0])       /* 0 choosing a choice, 1 choosing its slot */
#define ITEM_CURSOR  (g_00748AA4[1])       /* choice (0-5), 6 = done */
#define ITEM_SLOT    (g_00748AA4[2])       /* attribute slot (two columns) */
#define ITEM_FREE(i) (g_00748AA4[3 + (i)]) /* choice not used yet */
extern u8 g_00748A9E, g_00748A9F;         /* item screen animation: busy while they differ */

/* Clears the slot marks set by func_0021E430. */
static void clear_marks(void)
{
    int i;

    for (i = 13; i < 21; i++)
        g_00748ADC[i] = 1;
}

/* 0x0021E520, 0x850 bytes. Item screen, choice step: Up/Down pick one of the player's choices
 * (g_00748FAC of them) or "done" (6); OK applies it (kind, bonus, or an attribute: then Left/Right/
 * Up/Down pick the slot, OK writes it); Cancel undoes the last choice, Triangle undoes all. */
int func_0021E520(int pad)
{
    unsigned short pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    unsigned short repeat = PAD_READY(pad) ? PAD_REPEAT(pad) : 0;
    int busy;

    if (g_00748A9E == 0)
        busy = 0;
    else if (g_00748A9F == g_00748A9E)
        busy = 0;
    else
        busy = 1;
    if (busy)
        return 0;

    if (ITEM_MODE == 0) {
        if (pressed & 0x40) {
            if (ITEM_CURSOR == 6) {
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021B660(6);
            } else if (ITEM_FREE(ITEM_CURSOR) == 0) {
                func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
            } else {
                ItemChoice *c;

                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                g_00748ADC[1 + 2 * g_00748ADC[0]] = ITEM_CURSOR;
                c = &g_0074901C[g_0074794C][ITEM_CURSOR];
                if (c->type >= 10 && c->type <= 14) {
                    static const u8 kinds[5] = { 1, 3, 2, 4, 5 };    /* types 10-14 */
                    g_00748AC9 = kinds[c->type - 10];
                    ITEM_FREE(ITEM_CURSOR) = 0;
                    g_00748ADC[2 + 2 * g_00748ADC[0]] = 8;
                    g_00748ADC[0]++;
                } else if (c->type == 15) {
                    g_00748ADB = (u8)(c->value - g_00428138[g_00748AC8[0]]);
                    ITEM_FREE(ITEM_CURSOR) = 0;
                    g_00748ADC[2 + 2 * g_00748ADC[0]] = 8;
                    g_00748ADC[0]++;
                } else {
                    ITEM_MODE = 1;
                    ITEM_SLOT = func_0021E430(c->type);
                }
            }
        } else if (pressed & 0x10) {                /* cancel: undo the last choice */
            if (g_00748ADC[0] < 1) {
                func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
            } else {
                func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021E1F0(g_00748ADC[0] - 1);
            }
        } else if (pressed & 0x80) {                /* undo every choice */
            func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
            func_0021E1F0(0);
        } else if (repeat & 0x1000) {               /* up */
            if (ITEM_CURSOR == 0) {
                if (pressed & 0x1000) {
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    ITEM_CURSOR = 6;
                }
            } else if (ITEM_CURSOR == 6) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_CURSOR = g_00748FAC[g_0074794C] - 1;
            } else {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_CURSOR--;
            }
        } else if (repeat & 0x4000) {               /* down */
            if (ITEM_CURSOR == g_00748FAC[g_0074794C] - 1) {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_CURSOR = 6;
            } else if (ITEM_CURSOR == 6) {
                if (pressed & 0x4000) {
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    ITEM_CURSOR = 0;
                }
            } else {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_CURSOR++;
            }
        }
    } else if (pressed & 0x40) {                    /* write the attribute in the slot */
        if (g_00748ADC[13 + ITEM_SLOT] == 0) {
            func_0023AD10(4, 0, 0x2CDC, 0x2CDC, 0x1000);
        } else {
            ItemChoice *c = &g_0074901C[g_0074794C][ITEM_CURSOR];

            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_00748AC8[2 + ITEM_SLOT] = (u8)c->type;
            g_00748AC8[10 + ITEM_SLOT] = (u8)c->value;
            ITEM_FREE(ITEM_CURSOR) = 0;
            ITEM_MODE = 0;
            g_00748ADC[2 + 2 * g_00748ADC[0]] = ITEM_SLOT;
            g_00748ADC[0]++;
            clear_marks();
        }
    } else if (pressed & 0x10) {                    /* cancel the slot choice */
        func_0023AD10(2, 0, 0x2CDC, 0x2CDC, 0x1000);
        ITEM_MODE = 0;
        clear_marks();
    } else if (repeat & 0x1000) {                   /* up: previous row (wraps on Up press) */
        if (g_00748ADA > 2) {
            if (ITEM_SLOT < 2) {
                if (pressed & 0x1000) {
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    ITEM_SLOT = (ITEM_SLOT + (g_00748ADA - 2)) % g_00748ADA;
                }
            } else {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_SLOT = (ITEM_SLOT + (g_00748ADA - 2)) % g_00748ADA;
            }
        }
    } else if (repeat & 0x4000) {                   /* down: next row */
        if (g_00748ADA > 2) {
            if (ITEM_SLOT == g_00748ADA - 2 || ITEM_SLOT == g_00748ADA - 1) {
                if (pressed & 0x4000) {
                    func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                    ITEM_SLOT = (ITEM_SLOT + 2) % g_00748ADA;
                }
            } else {
                func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
                ITEM_SLOT = (ITEM_SLOT + 2) % g_00748ADA;
            }
        }
    } else if (pressed & 0xA000) {                  /* left/right: other column */
        func_0023AD10(0, 0, 0x2CDC, 0x2CDC, 0x1000);
        if (ITEM_SLOT % 2 == 0)
            ITEM_SLOT++;
        else
            ITEM_SLOT--;
    }
    return 0;
}

/* ---- Officers page ---------------------------------------------------------------------------- */

#define MAX0(x) ((x) > 0 ? (x) : 0)

/* Moves `value` 16 towards `target` (as the game does it: clamped to [0, value] going down and to
 * [0, target] going up). */
#define SLIDE(value, target)                                                    \
    do {                                                                        \
        if ((target) < (value)) {                                               \
            int n_ = (value) - 0x10;                                            \
            (value) = MAX0(n_) > (value) ? (value) : MAX0(n_);                  \
        } else if ((value) < (target)) {                                        \
            int n_ = (value) + 0x10;                                            \
            (value) = MAX0(n_) > (target) ? (target) : MAX0(n_);                \
        }                                                                       \
    } while (0)

extern u8 g_00748D26, g_00748D27;         /* level-up animation: busy while they differ */

/* 0x0021EF50, 0x728 bytes. Officers page (controller `pad`): slides the officer rows into place
 * (g_00748F18 = 0), shows the army's level-up (1), then the level-up of each officer in
 * g_00748F1C (3-6, the experience counting up); OK skips each step; at the end (7) opens the save
 * page (9). */
int func_0021EF50(int pad)
{
    unsigned short pressed = PAD_READY(pad) ? PAD_PRESSED(pad) : 0;
    int i, officer, busy, counting;

    switch (g_00748F18) {
    case 0:
        for (i = 0; i < g_00748F0C; i++) {
            ShownOfficer *e = &g_00748DC8[i];
            if (e->value_20 != 0) {
                SLIDE(e->value_c, e->value_14);
                SLIDE(e->value_10, e->value_18);
                if (e->value_c == e->value_14 && e->value_10 == e->value_18)
                    e->value_20 = 0;
            }
        }
        for (i = 0; i < g_00748F0C; i++) {
            if (g_00748DC8[i].value_20 != 0)
                break;
        }
        if (i < g_00748F0C) {
            if ((g_00748F6C & 1) == 1)
                func_0023AD10(3, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_00748F6C = (g_00748F6C + 1) & 1;
        } else if (g_00748F84 == 0 && g_00748F14 != 0) {
            func_003E0320(1);
            g_00748F18 = 1;
        } else {
            g_00748F18 = 2;
        }
        break;
    case 1:
        if (g_00748D26 == 0)
            busy = 0;
        else if (g_00748D27 == g_00748D26)
            busy = 0;
        else
            busy = 1;
        if (!busy) {
            func_0023AD10(7, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_00748F18 = 2;
        }
        break;
    case 3:
        g_00748F18 = 4;
        break;
    case 4:
        officer = func_003620E0(g_00748F1C[g_00748F68][0], g_00748F1C[g_00748F68][1]);
        COUNT_UP(counting, g_00748F10, func_002F34E0(officer), g_00748F6C);
        if (!counting) {
            SET_GAUGE(0x40);
            func_0028C310();
            g_00748F18 = 5;
        }
        break;
    case 6:
        g_00748F68++;
        if (g_00748F68 < g_00748F64) {
            g_00748F10 = g_00747F5C[g_00748F1C[g_00748F68][0]][g_00748F1C[g_00748F68][1]].stats[0];
            func_003E0320(3);
            SET_GAUGE(0);
            func_0028C330(0x12E, 0x44);
            g_00748F18 = 3;
        } else {
            g_00748F18 = 7;
        }
        break;
    }

    if (pressed & 0x40) {
        if (g_00748F18 == 2) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            g_00748F18 = g_00748F64 < 1 ? 7 : 3;
        } else if (g_00748F18 == 5) {
            if (g_00748F68 == g_00748F64) {
                func_0021B660(9);
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
                func_0021C390();
            } else {
                g_00748F18 = 6;
                func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            }
        } else if (g_00748F18 == 4) {
            officer = func_003620E0(g_00748F1C[g_00748F68][0], g_00748F1C[g_00748F68][1]);
            g_00748F10 = func_002F34E0(officer);
            SET_GAUGE(0x40);
            func_0028C310();
            g_00748F18 = 5;
        } else if (g_00748F18 == 0) {
            func_0023AD10(1, 0, 0x2CDC, 0x2CDC, 0x1000);
            for (i = 0; i < g_00748F0C; i++) {
                g_00748DC8[i].value_c = g_00748DC8[i].value_14;
                g_00748DC8[i].value_10 = g_00748DC8[i].value_18;
            }
        }
    }
    if (g_00748F18 == 7) {
        func_0021B660(9);
        func_0021C390();
        g_007729FC = 0;
    }
    return 0;
}
