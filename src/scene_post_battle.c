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
    u8 unknown_8[0x10];
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

/* Globals 0x00747E90-0x00747F34: one object in the original (not reached through $gp). */
extern struct {
    int g_00747E90;
    char pad_0[0x9C];
    int g_00747F30;
} s_00747E90;
#define g_00747E90 (s_00747E90.g_00747E90)
#define g_00747F30 (s_00747E90.g_00747F30)

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
    char pad_0[0x4];
    int g_00748F14;
    int g_00748F18;
    char pad_1[0x4C];
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
#define g_00748F14 (s_00748F0C.g_00748F14)
#define g_00748F18 (s_00748F0C.g_00748F18)
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
