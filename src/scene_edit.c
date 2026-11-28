/*
 * scene_edit.c - scene 0x14, the officer editor (original source file StateEdit.c, probable: its
 * string is passed to the file loader at 0x003767A0). The whole file is decompiled
 * (0x003766C0-0x0037DA64): the accessors and helpers, the page handlers (0x003789B0-0x0037BB5C,
 * table 0x004169A0), the scene and the page set-ups.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly: Ghidra loses many registers here, because the small accessors 0x003766C0... are
 * known to the compiler not to touch them). Unknown functions and globals keep neutral names
 * (func_/g_ + address); comments with a question mark are hypotheses.
 *
 * The editor keeps its state in a 0xBA0-byte block (g_0045D7C8): the officer being edited at
 * +0x404 (a 0x38-byte record: +0x18 body, +0x1C colour, +0x20 weapon, +0x24, +0x2A-0x2E choices),
 * a copy at +0x43C to undo a page, and per page a cursor and its scroll. A model of the officer is
 * shown on the right (unit 0x00574DE0) and follows the record.
 */

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_00165C60   /* the original callers here see it this way */
void func_00165C60(unsigned char *, int, int, int, int, int, unsigned char, int);
#endif
#define SW2E_FILE_SCENE_EDIT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

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

/* The editor's state (small data: two blocks of 0xBA0 and 0x780 bytes). */
#ifdef SW2E_PC
extern ps2ptr g_0045D7C8_a;
#define g_0045D7C8 ((u8 *)PS2_PTR(g_0045D7C8_a))
#define g_0045D7C8_SET(v) (g_0045D7C8_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7C8;
#define g_0045D7C8_a (*(ps2ptr *)&g_0045D7C8)
#define g_0045D7C8_SET(v) (g_0045D7C8 = (v))
#endif
#ifdef SW2E_PC
extern ps2ptr g_0045D7CC_a;
#define g_0045D7CC ((u8 *)PS2_PTR(g_0045D7CC_a))
#define g_0045D7CC_SET(v) (g_0045D7CC_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7CC;
#define g_0045D7CC_a (*(ps2ptr *)&g_0045D7CC)
#define g_0045D7CC_SET(v) (g_0045D7CC = (v))
#endif
#define ES(off, type) (*(type *)(g_0045D7C8 + (off)))
#define ES_RECORD     (g_0045D7C8 + 0x404)          /* the officer being edited */
#define ES_BACKUP     (g_0045D7C8 + 0x43C)          /* its copy when the page opened */
#define ES_REQUESTED  ES(0xB0, int)                 /* page asked for */
#define ES_PAGE       ES(0xB4, int)                 /* page shown (0-11) */
#define ES_PREVIOUS   ES(0xB8, int)
#define ES_PHASE      ES(0x9A4, int)                /* 0 open, 1 in, 2 out, 3 running */
#define ES_TIMER      ES(0x9A8, int)
#define ES_DIRTY      ES(0xB97, u8)                 /* 1: the page changed the record */
#define ES_SHOWN      ES(0xB98, int)                /* a model is shown */
#define ES_HEIGHT     ES(0xB9C, float)              /* the model's view height */

/* Shared menu flags (0x00799A24, see scene_shop.c). */
extern struct {
    u8 g_00799A24;
    u8 pad_0;
    u8 g_00799A26;
    u8 pad_1;
    int g_00799A28;
    int g_00799A2C;
    u8 pad_2[0xC];
    u8 g_00799A3C;
    u8 pad_3;
    u8 g_00799A3E;
    u8 pad_4;
    int g_00799A40;
    int g_00799A44;
} s_00799A24;
#define g_00799A24 (s_00799A24.g_00799A24)
#define g_00799A26 (s_00799A24.g_00799A26)
#define g_00799A28 (s_00799A24.g_00799A28)
#define g_00799A2C (s_00799A24.g_00799A2C)
#define g_00799A3C (s_00799A24.g_00799A3C)
#define g_00799A3E (s_00799A24.g_00799A3E)
#define g_00799A40 (s_00799A24.g_00799A40)
#define g_00799A44 (s_00799A24.g_00799A44)

/* After a page set-up: the list starts (inlined in the original). */
#define LIST_START() do {                       \
        g_00799A40 = 1;                         \
        g_00799A44 = 0;                         \
        g_00799A3C = g_00799A3E;                \
    } while (0)
#define LIST_START_ALT() do {                   \
        g_00799A44 = 1;                         \
        g_00799A40 = 0;                         \
        g_00799A3C = g_00799A3E;                \
    } while (0)

/* The model view (0x007B9E40): position and size words, colour bytes. */
extern struct {
    u16 g_007B9E40, g_007B9E42, g_007B9E44, g_007B9E46;
    u16 g_007B9E48, g_007B9E4A, g_007B9E4C, g_007B9E4E;
    u8 g_007B9E50, g_007B9E51, g_007B9E52, g_007B9E53;
} s_007B9E40;

/* Units (see scene_battle_initialize.c): the player unit and the model's battle unit. */
extern u8 g_005B4BC0[2][0x240];
extern u8 g_00574DE0[2][0x630];
#ifdef SW2E_PC
extern ps2ptr g_0045D2C0_a;
#define g_0045D2C0 ((u8 *)PS2_PTR(g_0045D2C0_a))
#define g_0045D2C0_SET(v) (g_0045D2C0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2C0;
#define g_0045D2C0_a (*(ps2ptr *)&g_0045D2C0)
#define g_0045D2C0_SET(v) (g_0045D2C0 = (v))
#endif

/* The game state's officer records (0x00669D60 + 0x254, 15 of 0x38 bytes). */
extern u8 g_00669D60[];

/* Tables (0x00416720-0x004169A0). */
extern int g_00416720[22], g_00416780[22];  /* weapons, and their model height offsets */
extern int g_004167E0[13];                  /* bodies of page 1 */
extern int g_00416820[16], g_00416860[18], g_004168B0[15];   /* page 2 lists by body group */
extern int g_004168F0[4], g_00416900[4];    /* page 4 lists by body group */
extern u32 g_00416910[12], g_00416940[12], g_00416970[11];   /* page 5 lists by weapon */
extern void (*g_004169A0[12])(void);        /* the page handlers */

int func_00377330(int i);
int func_00377380(int i);
u8 *func_003766C0(void);
void func_001BE4F0(void);
int func_003773F0(int weapon);
int func_003774A0(int model, int a);
void func_003774E0(int value);
void func_00182C30(void);
int func_00120A40(const u8 *text);
void func_0011EB80(void *dst, const void *src, int size);
void func_003767A0(int value);
void func_003776D0(void);
int func_0017DDA0(void);
void func_0017DF10(void);
void func_003767E0(void);
void func_001784E0(float dt);
void func_00179320(void);
void func_00278A20(void);

/* The motion slot of entry `i` of the model lists (26 of 4 bytes, then three more). */
static int motion_slot(int i)
{
    if (i < 0x1A)
        return i * 4;
    if (i == 0x1A)
        return 0x68;
    if (i == 0x1B)
        return 0x6C;
    return 0x70;
}

/* The model kind of a weapon: weapons 0-0x19 their own, the ranges 0x3E-0x48, 0x49-0x53,
 * 0x54-0x5C and 0x5D-0x67 share the models 0x26, 0x2A, 0x20 and 0x21 (inlined, four times). */
static int weapon_kind(int weapon)
{
    if (weapon < 0x1A)
        return weapon;
    if (weapon >= 0x3E && weapon < 0x49)
        return 0x26;
    if (weapon >= 0x49 && weapon < 0x54)
        return 0x2A;
    if (weapon >= 0x54 && weapon < 0x5D)
        return 0x20;
    if (weapon >= 0x5D && weapon < 0x68)
        return 0x21;
    return weapon;
}

void func_0037BE30(int body, int colour, int kind, int model);

/* Shows the model of officer record `rec` (inlined in the original). */
static void show_record(const u8 *rec)
{
    int weapon = *(int *)(rec + 0x20);
    int kind = weapon_kind(weapon);
    int model = func_003774A0(func_003773F0(weapon), 0);

    func_0037BE30(*(int *)(rec + 0x18), rec[0x1C], kind, model);
}

/* ---- The accessors, helpers and page handlers (0x003766C0-0x0037BB60) ---- */

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
#define pad1_ready() ((g_00500700[0].ready & 1) ? (g_00500700[0].connected & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_00500700[0].pressed : 0))
#define pad1_held() ((unsigned short)(pad1_ready() ? g_00500700[0].held : 0))

#define BTN_L      0x0004
#define BTN_R      0x0008
#define BTN_CANCEL 0x0010
#define BTN_EXTRA  0x0020
#define BTN_OK     0x0040
#define BTN_EXTRA2 0x0080
#define BTN_START  0x0800
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000

#define SE(kind) func_0023AD10((kind), 0, 0x2CDC, 0x2CDC, 0x1000)   /* 0 move, 1 OK, 2 back, 4 refused */

/* The message boxes' object (0x0068F3E0, see scene_shop.c): box n's state at +0x40D3 +
 * n * 0x128, its answer at +0x40D4 + n * 0x128 (4 yes, 5 no). */
extern u8 g_0068F3E0[];
#define BOX_STATE(n) (g_0068F3E0[0x40D3 + (n) * 0x128])
#define BOX_ANSWER(n) (g_0068F3E0[0x40D4 + (n) * 0x128])

/* The text table at 0x0043C120 (messages by number, see scene_config.c). */
extern const char *g_0043C120[];
#define MESSAGE(id) (g_0043C120[id])
extern const char *g_0043CC54[];          /* "Saving data. Proceed?", "Deleting officer...", ... */
#define TEXT_SAVE     (g_0043CC54[0])     /* 0x0043CC54 */
#define TEXT_LOST     (g_0043CC54[1])     /* 0x0043CC58 "Changes will be lost if data is not saved..." */
#define TEXT_DELETE   (g_0043CC54[2])     /* 0x0043CC5C "Deleting officer. Proceed?" */
#define TEXT_IN_USE   (g_0043CC54[3])     /* 0x0043CC60 "This officer is currently in use..." */
#define TEXT_OFFICER  (g_0043CC54[8])     /* 0x0043CC74 "Officer" */
#define TEXT_NEW      (g_0043CC54[9])     /* 0x0043CC78 "New" */
extern const char g_004594C8[];           /* an empty name */
#ifdef SW2E_PC
extern ps2ptr g_0045C478_a;            /* the name grid: 17 characters a row, '@' = none */
#define g_0045C478 ((const char *)PS2_PTR(g_0045C478_a))
#define g_0045C478_SET(v) (g_0045C478_a = PS2_ADDR(v))
#else
extern const char *g_0045C478;
#define g_0045C478_a (*(ps2ptr *)&g_0045C478)
#define g_0045C478_SET(v) (g_0045C478 = (v))
#endif
extern int g_00416460[64];                /* voices: 8 per voice kind */
extern int g_00416560[13], g_004165A0[16], g_004165E0[18], g_00416630[15];
extern int g_00416670[8], g_00416690[12], g_004166C0[12], g_004166F0[11];

#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

/* Two window layouts of a page's list (inlined): the list in front, or the grid. */
#define SHOW_GRID(es) do {                                              \
        (es)[0x978] = (es)[0x97A];                                      \
        *(int *)((es) + 0x97C) = 0;                                     \
        *(int *)((es) + 0x980) = 1;                                     \
        (es)[0x990] = (es)[0x992];                                      \
        *(int *)((es) + 0x994) = 1;                                     \
        *(int *)((es) + 0x998) = 0;                                     \
    } while (0)
#define SHOW_LIST(es) do {                                              \
        (es)[0x978] = (es)[0x97A];                                      \
        *(int *)((es) + 0x97C) = 1;                                     \
        *(int *)((es) + 0x980) = 0;                                     \
        (es)[0x990] = (es)[0x992];                                      \
        *(int *)((es) + 0x994) = 0;                                     \
        *(int *)((es) + 0x998) = 1;                                     \
    } while (0)

/* Asks `text` in message box `box`, with the list's windows in front (inlined). */
#define ASK(box, text) do {                                             \
        func_001204B0(buffer, (text));                                  \
        func_001AE9F0((box), buffer, 1);                                \
        func_001AFC50(box);                                             \
    } while (0)
#define BOX_CLOSED() do {                                               \
        g_00799A24 = g_00799A26;                                        \
        g_00799A28 = 1;                                                 \
        g_00799A2C = 0;                                                 \
    } while (0)
#define BOX_OPENED() do {                                               \
        g_00799A24 = g_00799A26;                                        \
        g_00799A28 = 0;                                                 \
        g_00799A2C = 1;                                                 \
    } while (0)

#ifdef SW2E_PC
extern ps2ptr g_0045D7C4_a;                    /* (small data) the editor's file */
#define g_0045D7C4 ((u8 *)PS2_PTR(g_0045D7C4_a))
#define g_0045D7C4_SET(v) (g_0045D7C4_a = PS2_ADDR(v))
#else
extern u8 *g_0045D7C4;
#define g_0045D7C4_a (*(ps2ptr *)&g_0045D7C4)
#define g_0045D7C4_SET(v) (g_0045D7C4 = (v))
#endif
void func_00120928(char *to, const char *from);
void func_003A53D0(u8 *a, u8 b);
void func_003A53A0(u8 *a, int b, int c, int d);
int func_0011EAE8(const void *a, const void *b, int size);
void func_0011ED38(void *to, int value, int size);
void func_001204B0(char *to, const char *from, ...);
void func_002DBAA0(void);
void func_002D8060(int a);

/* 0x003766C0, 0x8 bytes, matching. */
u8 *func_003766C0(void)
{
    return g_0045D7C8;
}

/* 0x003766D0, 0x8 bytes, matching. */
u8 *func_003766D0(void)
{
    return g_0045D7CC;
}

/* 0x003766E0, 0x8 bytes, matching. Page 0's state (at the block's start). */
u8 *func_003766E0(void)
{
    return g_0045D7C8;
}

/* 0x003766F0-0x00376790: the other pages' states. */
u8 *func_003766F0(void) { return g_0045D7C8 + 0x30; }   /* 0x003766F0, 0xC bytes, matching. page 1 */
u8 *func_00376700(void) { return g_0045D7C8 + 0x40; }   /* 0x00376700, 0xC bytes, matching. page 2 */
u8 *func_00376710(void) { return g_0045D7C8 + 0x4C; }   /* 0x00376710, 0xC bytes, matching. page 4 */
u8 *func_00376720(void) { return g_0045D7C8 + 0x5C; }   /* 0x00376720, 0xC bytes, matching. page 5 */
u8 *func_00376730(void) { return g_0045D7C8 + 0x64; }   /* 0x00376730, 0xC bytes, matching. page 3 */
u8 *func_00376740(void) { return g_0045D7C8 + 0x6C; }   /* 0x00376740, 0xC bytes, matching. page 7 */
u8 *func_00376750(void) { return g_0045D7C8 + 0x74; }   /* 0x00376750, 0xC bytes, matching. page 6 */
u8 *func_00376760(void) { return g_0045D7C8 + 0x7C; }   /* 0x00376760, 0xC bytes, matching. page 8 */
u8 *func_00376770(void) { return g_0045D7C8 + 0x84; }   /* 0x00376770, 0xC bytes, matching. page 9 */
u8 *func_00376780(void) { return g_0045D7C8 + 0x9C; }   /* 0x00376780, 0xC bytes, matching. page 10 */
u8 *func_00376790(void) { return g_0045D7C8 + 0xA4; }   /* 0x00376790, 0xC bytes, matching. page 11 */

/* 0x003767A0, 0x40 bytes, matching. Loads the editor's file (LINKDATA entry 0x8A). */
void func_003767A0(int value)
{
    g_0045D7C4_SET(func_001026D0(1, 0x8A, 0, value, 0, 0, "StateEdit.c", 0xEA));
}

/* 0x003767E0, 0x2C bytes, matching. */
void func_003767E0(void)
{
    if (g_0045D7C4 != 0) {
        func_00102EC0(g_0045D7C4);
        g_0045D7C4_SET(0);
    }
}

/* 0x00376810, 0x8 bytes, matching. */
u8 *func_00376810(void)
{
    return g_0045D7C4;
}

u8 *func_00376820(void) { return g_0045D7C8 + 0x404; }  /* 0x00376820, 0xC bytes, matching. the record */
u8 *func_00376830(void) { return g_0045D7C8 + 0x43C; }  /* 0x00376830, 0xC bytes, matching. its backup */
u8 *func_00376840(void) { return g_0045D7C8 + 0x474; }  /* 0x00376840, 0xC bytes, matching. when opened */
u8 *func_00376850(void) { return g_0045D7C8 + 0x8E4; }  /* 0x00376850, 0xC bytes, matching. its extra data */
u8 *func_00376860(void) { return g_0045D7C8 + 0x92C; }  /* 0x00376860, 0xC bytes, matching. */

/* 0x00376870, 0x3C bytes. The length of a name (at most `most`), -1 without an end. */
int func_00376870(const char *name, int most)
{
    int i;

    for (i = 0; i <= most; i++)
        if (name[i] == 0)
            return i;
    return -1;
}

/* 0x003768B0, 0x268 bytes. Inserts `c` in an 8-character name at the cursor. */
int func_003768B0(char *name, u8 *cursor, char c)
{
    char copy[16];
    int at = *cursor;
    int len = func_00376870(name, 8);
    int i;

    if (len == -1)
        name[7] = 0;
    if (len >= 8)
        return -1;
    if (name[at] == 0) {
        name[at] = c;
        name[at + 1] = 0;
    } else {
        func_00120928(copy, name);
        for (i = len; i >= at; i--)
            copy[i + 1] = copy[i];
        *(int *)&copy[8] = 0;
        func_00120928(name, copy);
        name[at] = c;
    }
    at++;
    if (at > 7)
        at = 7;
    *cursor = at;
    return at;
}

/* 0x00376B20, 0x200 bytes. Deletes the character at the cursor (or before it at the end). */
int func_00376B20(char *name, u8 *cursor)
{
    int len = func_00376870(name, 8);
    int at, i;

    if (len == -1)
        name[7] = 0;
    if (len == 0)
        return -1;
    at = *cursor;
    if (name[at] == 0) {
        name[at - 1] = 0;
        at--;
    } else {
        for (i = at + 1; i <= len; i++)
            name[i - 1] = name[i];
    }
    if (at < 0)
        at = 0;
    *cursor = at;
    return at;
}

/* 0x00376D20, 0x80 bytes. The cursor right in a name (up to its end, at most 7). */
void func_00376D20(const char *name, u8 *cursor)
{
    int end = func_00147070((const unsigned char *)(name)) < 8 ? func_00147070((const unsigned char *)(name)) : 7;

    if (*cursor < end) {
        (*cursor)++;
        SE(0);
    }
}

/* 0x00376DA0, 0x40 bytes, matching. The cursor left in a name. */
void func_00376DA0(u8 *cursor)
{
    if (*cursor > 0) {
        (*cursor)--;
        SE(0);
    }
}

/* 0x00376DE0, 0x1C bytes, matching. */
void func_00376DE0(u8 *extra, u8 value)
{
    func_003A53D0(extra, value);
}

/* 0x00376E00, 0xBC bytes. Sets the four motions of a weapon (with the variant of the four
 * weapons with variants). */
void func_00376E00(u8 *extra, int weapon, int variant)
{
    int i;

    if (weapon == 0x3E || weapon == 0x49 || weapon == 0x54 || weapon == 0x5D)
        weapon += variant;
    for (i = 0; i < 4; i++) {
        int motion = func_0039E880(weapon, i);

        if (motion < 0x35)
            func_003A53A0(extra, motion, func_0039E8A0(weapon, i), 1);
    }
}

void func_00377190(int weapon);
void func_00377210(u8 value);
void func_00377230(int voice);

/* 0x00376EC0, 0x20 bytes. */
void func_00376EC0(u8 value)
{
    func_00376820()[0x13] = value;
}

/* The weapon and voice a body group cannot keep (inlined three times). */
#define FIX_CHOICES(rec, female) do {                                   \
        if (*(int *)((rec) + 0x20) == 0x5D)                             \
            func_00377190(0x54);                                        \
        if ((u32)(*(int *)((rec) + 0x24) - 0x2F) < 4)                   \
            func_00377230(0x2B);                                        \
        if ((u32)((rec)[0x2B] - 9) < 2)                                 \
            func_00377210(0);                                           \
    } while (0)

/* 0x00376EE0, 0x28C bytes. Sets the body, and the gender of its group (0x1C-0x21 / 0x30,
 * 0x33-0x35: male; 0x36-0x38: female), dropping the weapon, voice and accessory the other group
 * uses. */
void func_00376EE0(int body)
{
    u8 *rec = func_00376820();
    int w;

    *(int *)(rec + 0x18) = body;
    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C) {
        func_00376EC0(0);
        w = *(int *)(rec + 0x20);
        if (w == 0x0C || w == 6 || w == 0x0A || w == 0x0F || w == 0x15 || w == 0x17)
            func_00377190(0x3E);
        FIX_CHOICES(rec, 0);
    } else if (body == 0x35 || body == 0x34 || body == 0x33) {
        func_00376EC0(0);
        w = *(int *)(rec + 0x20);
        if (w == 6 || w == 0x0A || w == 0x0F || w == 0x15 || w == 0x17)
            func_00377190(0x3E);
        FIX_CHOICES(rec, 0);
    } else if (body == 0x38 || body == 0x37 || body == 0x36) {
        func_00376EC0(1);
        w = *(int *)(rec + 0x20);
        if (w == 0 || w == 0x11 || w == 0x13)
            func_00377190(0x3E);
        if (*(int *)(rec + 0x20) == 0x54)
            func_00377190(0x5D);
        if ((u32)(*(int *)(rec + 0x24) - 0x2B) < 4)
            func_00377230(0x2F);
    }
}

/* 0x00377170, 0x20 bytes. */
void func_00377170(u8 colour)
{
    func_00376820()[0x1C] = colour;
}

/* 0x00377190, 0x74 bytes. Sets the weapon (dropping the choices 0x0C and 8 the weapon does not
 * allow). */
void func_00377190(int weapon)
{
    u8 *rec = func_00376820();

    *(int *)(rec + 0x20) = weapon;
    if (weapon != 2 && weapon != 0x15 && rec[0x2A] == 0x0C)
        rec[0x2A] = 0;
    if (weapon != 7 && weapon != 0x0F && rec[0x2A] == 8)
        rec[0x2A] = 0;
}

void func_00377210(u8 value) { func_00376820()[0x2B] = value; }             /* 0x00377210, 0x20 bytes. */
void func_00377230(int voice) { *(int *)(func_00376820() + 0x24) = voice; }  /* 0x00377230, 0x20 bytes. */
void func_00377250(u8 value) { func_00376820()[0x2A] = value; }             /* 0x00377250, 0x20 bytes. */
void func_00377270(u8 value) { func_00376820()[0x2C] = value; }             /* 0x00377270, 0x20 bytes. */

/* 0x00377290, 0x34 bytes. */
void func_00377290(u8 value)
{
    u8 *rec = func_00376820();

    rec[0x2D] = value;
    func_00376DE0(func_00376850(), rec[0x2D]);
}

void func_003772D0(u8 value) { func_00376820()[0x2E] = value; }             /* 0x003772D0, 0x20 bytes. */
void func_003772F0(u8 value) { func_00376820()[0x2F] = value; }             /* 0x003772F0, 0x20 bytes. */
void func_00377310(u8 value) { func_00376820()[0x30] = value; }             /* 0x00377310, 0x20 bytes. */

/* 0x00377330, 0x30 bytes. The editor's models: bodies 0x1C-0x21, 0x33-0x38, 0x30. */
int func_00377330(int i)
{
    switch (i) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return i + 0x1C;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        return i + 0x2D;
    case 12:
        return 0x30;
    }
    return 0;
}

/* 0x00377380, 0x70 bytes. The editor's weapons: 0-0x19, then 0x26, 0x2A, 0x20, 0x21. */
int func_00377380(int i)
{
    if (i >= 0 && i <= 0x19)
        return i;
    if (i == 0x1A)
        return 0x26;
    if (i == 0x1B)
        return 0x2A;
    if (i == 0x1C)
        return 0x20;
    return i == 0x1D ? 0x21 : 0;
}

/* 0x003773F0, 0xA8 bytes. The motion set of a weapon. */
int func_003773F0(int weapon)
{
    int set = 0;

    if (weapon >= 0 && weapon <= 0x19)
        set = weapon;
    else if ((weapon >= 0x3E && weapon <= 0x48) || weapon == 0x26)
        set = 0x1A;
    else if ((weapon >= 0x49 && weapon <= 0x53) || weapon == 0x2A)
        set = 0x1B;
    else if ((weapon > 0x53 && weapon < 0x68) || (u32)(weapon - 0x20) < 2)
        set = 0x1C;
    return set;
}

/* 0x003774A0, 0x38 bytes. The motion slot of `motion` in set `set`. */
int func_003774A0(int set, int motion)
{
    if (set == 0x1D)
        return motion == 3 ? 0x78 : motion + 0x68;
    return motion + set * 4;
}

/* 0x003774E0, 0x1E4 bytes. The model view: 2 hides it, 1 / 0 shows it small / large. */
void func_003774E0(int mode)
{
    u8 *es = func_003766C0();
    float *pos = (float *)(g_00574DE0[0] + 0x40);

    if (mode == 2) {
        *(int *)(g_00574DE0[0] + 0x54) = 0;
    } else if (mode == 1 || mode == 0) {
        s_007B9E40.g_007B9E46 = 0;
        s_007B9E40.g_007B9E44 = 0;
        s_007B9E40.g_007B9E53 = 0;
        s_007B9E40.g_007B9E42 = (int)pos[1];
        s_007B9E40.g_007B9E50 = 0x80;
        s_007B9E40.g_007B9E40 = (int)pos[0];
        s_007B9E40.g_007B9E52 = 0x19;
        s_007B9E40.g_007B9E48 = mode == 1 ? 4 : 0x28;
        s_007B9E40.g_007B9E51 = 0x80;
        s_007B9E40.g_007B9E4C = 0;
        s_007B9E40.g_007B9E4E = 0;
        s_007B9E40.g_007B9E4A = (int)*(float *)(es + 0xB9C);
    }
}

/* 0x003776D0, 0x5C bytes, matching. Resets the editor's state. */
void func_003776D0(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0xB4) = 0x0B;
    *(int *)(es + 0xB0) = 0x0B;
    *(int *)(es + 0xB8) = 0x0C;
    *(int *)(es + 0x9A8) = 0;
    *(int *)(es + 0x9A4) = 0;
    *(int *)(es + 0xB8C) = 0;
    *(int *)(es + 0xB90) = 0;
    es[0xB94] = 0;
    es[0xB95] = 0;
    es[0xB96] = 0;
    es[0xB97] = 0;
    *(int *)(es + 0xB98) = 0;
    *(float *)(es + 0xB9C) = 90.0f;
}

typedef struct { int v[64]; } Voices;

/* 0x00377730, 0x48 bytes, matching. */
int func_00377730(int i)
{
    Voices voices = *(Voices *)g_00416460;

    return voices.v[i];
}

/* 0x00377780, 0x7C bytes. A cursor up over `n` lines (wrapping when `wrap`). */
int func_00377780(int *cursor, int n, int wrap)
{
    if (*cursor == 0) {
        if (wrap == 0)
            return 0;
        *cursor = n - 1;
    } else {
        (*cursor)--;
    }
    SE(0);
    return 1;
}

/* 0x00377800, 0x7C bytes. A cursor down. */
int func_00377800(int *cursor, int n, int wrap)
{
    if (*cursor == n - 1) {
        if (wrap == 0)
            return 0;
        *cursor = 0;
    } else {
        (*cursor)++;
    }
    SE(0);
    return 1;
}

/* 0x00377880, 0xA4 bytes. A scrolled cursor up (`shown` lines of `n`). */
int func_00377880(int *cursor, int *scroll, int shown, int n, int wrap)
{
    if (*cursor == 0) {
        if (wrap == 0)
            return 0;
        *scroll = n - shown;
        *cursor = n - 1;
    } else {
        if (*cursor == *scroll && --*scroll < 0)
            *scroll = 0;
        (*cursor)--;
    }
    SE(0);
    return 1;
}

/* 0x00377930, 0xB0 bytes. A scrolled cursor down. */
int func_00377930(int *cursor, int *scroll, int shown, int n, int wrap)
{
    if (*cursor == n - 1) {
        if (wrap == 0)
            return 0;
        *scroll = 0;
        *cursor = 0;
    } else {
        if (*cursor == *scroll + shown - 1 && ++*scroll > n - shown)
            *scroll = n - shown;
        (*cursor)++;
    }
    SE(0);
    return 1;
}

/* 0x003779E0, 0xBC bytes. Stores the record in slot `slot` (the weapon with its variant). */
void func_003779E0(int slot)
{
    u8 *es = func_003766C0();
    u8 *saved = es + slot * 0x38;
    int w;

    func_0011EB80(saved + 0xBC, es + 0x404, 0x38);
    w = *(int *)(saved + 0xDC);
    if (w == 0x3E || w == 0x49 || w == 0x54 || w == 0x5D)
        *(u32 *)(saved + 0xDC) = w + saved[0xE7];
    func_0011EB80(es + slot * 0x48 + 0x4AC, es + 0x8E4, 0x48);
}

/* 0x00377AA0, 0x118 bytes. A new officer: empty names, body 0x33, weapon 0x3E, voice 0x2B, a
 * random value. */
void func_00377AA0(void)
{
    u8 *es = func_003766C0();
    u8 *rec = func_00376820();
    u8 *extra = func_00376850();

    rec[0] = 1;
    func_00120928((char *)es + 0x405, g_004594C8);
    func_00120928((char *)es + 0x40E, g_004594C8);
    es[0x417] = 0;
    *(int *)(es + 0x41C) = 0x33;
    es[0x420] = 0;
    *(int *)(es + 0x424) = 0x3E;
    *(int *)(es + 0x428) = 0x2B;
    es[0x42C] = (u8)(RANDOM() % 0x7F);
    es[0x42D] = es[0x42C] % 5 + 1;
    es[0x42E] = 0;
    es[0x42F] = 0;
    es[0x430] = 0;
    es[0x431] = 0;
    es[0x432] = 0;
    es[0x433] = 0;
    es[0x434] = 0;
    func_00376DE0(extra, es[0x431]);
    *(u16 *)(extra + 4) = es[0xB94] + 400;
    es[0xB95] = 1;
}

/* 0x00377BC0, 0x150 bytes. Opens slot `slot`: the record (its weapon's variant split off), and
 * a copy to see whether it changed. */
void func_00377BC0(int slot)
{
    u8 *es = func_003766C0();
    int w;

    func_0011EB80(es + 0x404, es + slot * 0x38 + 0xBC, 0x38);
    func_0011EB80(es + 0x8E4, es + slot * 0x48 + 0x4AC, 0x48);
    w = *(int *)(g_0045D7C8 + 0x424);
    if (w >= 0x3E && w <= 0x48) {
        g_0045D7C8[0x42F] = w - 0x3E;
        *(int *)(g_0045D7C8 + 0x424) = 0x3E;
    } else if (w >= 0x49 && w <= 0x53) {
        g_0045D7C8[0x42F] = w - 0x49;
        *(int *)(g_0045D7C8 + 0x424) = 0x49;
    } else if (w >= 0x54 && w <= 0x5C) {
        g_0045D7C8[0x42F] = w - 0x54;
        *(int *)(g_0045D7C8 + 0x424) = 0x54;
    } else if (w >= 0x5D && w <= 0x67) {
        g_0045D7C8[0x42F] = w - 0x5D;
        *(int *)(g_0045D7C8 + 0x424) = 0x5D;
    } else {
        g_0045D7C8[0x42F] = 0;
    }
    func_0011EB80(func_00376840(), func_00376820(), 0x38);
    es[0xB95] = 0;
}

/* 0x00377D10, 0x38 bytes, matching. Deletes slot `slot`. */
void func_00377D10(int slot)
{
    func_003766C0()[slot * 0x38 + 0xBC] = 0;
}

/* 0x00377D50, 0x30 bytes. Whether the officer is a new one. */
int func_00377D50(void)
{
    return func_003766C0()[0xB95] == 1;
}

/* 0x00377D80, 0x6C bytes. Whether the weapon variant can be chosen (a new officer with one of
 * the four weapons with variants). */
int func_00377D80(void)
{
    u8 *es = func_003766C0();
    int w = *(int *)(func_00376820() + 0x20);
    int r = 0;

    if (w == 0x3E || w == 0x49 || w == 0x54 || w == 0x5D)
        r = 1;
    if (es[0xB95] == 0)
        r = 0;
    return r;
}

/* 0x00377DF0, 0x30 bytes. */
int func_00377DF0(void)
{
    return func_003766C0()[0xB95] == 1;
}

/* 0x00377E20, 0x4C bytes. Whether the record changed since it was opened. */
int func_00377E20(void)
{
    func_003766C0();
    return func_0011EAE8(func_00376820(), func_00376840(), 0x38) != 0;
}

/* 0x00377E70, 0x9C bytes, matching. Whether edited officer `slot` is free (not placed in the battle's
 * sides). */
int func_00377E70(int slot)
{
    u32 side, i;

    if (func_0019FB80() != 0) {
        func_001A1CD0();
        func_00362E20();
        for (side = 0; side < 2; side++)
            for (i = 0; i < 8; i++)
                if (slot + 400 == func_003620E0(side, i))
                    return 0;
    }
    return 1;
}

/* 0x00377F10, 0xC4 bytes. Whether a cell of the name grid holds no character (a lead byte, '@'
 * or 0). */
int func_00377F10(int col, int row, const u8 *grid)
{
    u8 c = grid[col + row * 0x11];

    if ((c >= 0x80 && c < 0xA0) || (c >= 0xE0 && c <= 0xEF) || (c >= 0xFA && c <= 0xFC) ||
        c == 0x40 || c == 0)
        return 1;
    return 0;
}

/* 0x00377FE0, 0xB4 bytes. The name grid's cursor up (column `col` - 1), skipping empty cells. */
int func_00377FE0(int col, int *row, int rows, const u8 *grid, int wrap)
{
    int r, k;

    if (col == 0)
        return 0;
    r = *row;
    for (k = 0; k < rows; k++) {
        r = (r + rows - 1) % rows;
        if (func_00377F10(col - 1, r, grid) == 0)
            break;
    }
    if (r != *row && (wrap != 0 || r < *row)) {
        *row = r;
        SE(0);
        return 1;
    }
    return 0;
}

/* 0x003780A0, 0xAC bytes. The name grid's cursor down. */
int func_003780A0(int col, int *row, int rows, const u8 *grid, int wrap)
{
    int r, k;

    if (col == 0)
        return 0;
    r = *row;
    for (k = 0; k < rows; k++) {
        r = (r + 1) % rows;
        if (func_00377F10(col - 1, r, grid) == 0)
            break;
    }
    if (r != *row && (wrap != 0 || *row < r)) {
        *row = r;
        SE(0);
        return 1;
    }
    return 0;
}

/* 0x00378150, 0xBC bytes. The name grid's cursor left (column 0 = the side buttons). */
int func_00378150(int *col, int *row, int cols, const u8 *grid, int wrap)
{
    int n = cols + 1;
    int c = *col, k;

    for (k = 0; k < n; k++) {
        c = (c + n - 1) % n;
        if (c == 0)
            break;
        if (func_00377F10(c - 1, *row, grid) == 0)
            break;
    }
    if (c == *col || (wrap == 0 && *col <= c))
        return 0;
    *col = c;
    SE(0);
    return 1;
}

/* 0x00378210, 0xB4 bytes. The name grid's cursor right. */
int func_00378210(int *col, int *row, int cols, const u8 *grid, int wrap)
{
    int n = cols + 1;
    int c = *col, k;

    for (k = 0; k < n; k++) {
        c = (c + 1) % n;
        if (c == 0)
            break;
        if (func_00377F10(c - 1, *row, grid) == 0)
            break;
    }
    if (c == *col || (wrap == 0 && c <= *col))
        return 0;
    *col = c;
    SE(0);
    return 1;
}

/* 0x003782D0, 0xF4 bytes. A 14-wide grid of `n` cells: up a row. */
int func_003782D0(int *col, int *row, int n, int wrap)
{
    int rows = n / 0x0E;

    if (n % 0x0E > 0)
        rows++;
    if (*row == 0 || *col + (*row - 1) * 0x0E < 0) {
        if (wrap == 0)
            return 0;
        if (*col + (rows - 1) * 0x0E < n)
            *row = rows - 1;
        else
            *row = rows - 2;
    } else {
        (*row)--;
    }
    SE(0);
    return 1;
}

/* 0x003783D0, 0x90 bytes. Down a row. */
int func_003783D0(int *col, int *row, int n, int wrap)
{
    if (*col + (*row + 1) * 0x0E < n) {
        (*row)++;
    } else {
        if (wrap == 0)
            return 0;
        *row = 0;
    }
    SE(0);
    return 1;
}

/* 0x00378460, 0xB4 bytes. Left. */
int func_00378460(int *col, int *row, int n, int wrap)
{
    if (*col == 0) {
        int c = 0x0D, i;

        if (wrap == 0)
            return 0;
        for (i = *row * 0x0E + 0x0D; i >= n; i--)
            c--;
        *col = c;
    } else {
        (*col)--;
    }
    SE(0);
    return 1;
}

/* 0x00378520, 0x98 bytes. Right. */
int func_00378520(int *col, int *row, int n, int wrap)
{
    int c = *col + 1;

    if (*col == 0x0D || c + *row * 0x0E >= n) {
        if (wrap == 0)
            return 0;
        *col = 0;
    } else {
        *col = c;
    }
    SE(0);
    return 1;
}

/* Page 9's colour grid (13 wide, 0x8E colours; 8 rows shown): +8 column, +0xC row, +0x10
 * scroll. */
#define P9_COL(s)    (*(int *)((s) + 8))
#define P9_ROW(s)    (*(int *)((s) + 0x0C))
#define P9_SCROLL(s) (*(int *)((s) + 0x10))

/* 0x003785C0, 0xE4 bytes. Page 9: up a row. */
int func_003785C0(int wrap)
{
    u8 *s = func_00376770();
    int row = P9_ROW(s), scroll = P9_SCROLL(s);

    if (row == 0 || P9_COL(s) + (row - 1) * 0x0D < 0) {
        if (wrap == 0)
            return 0;
        P9_ROW(s) = P9_COL(s) + 0x82 < 0x8E ? 10 : 9;
        P9_SCROLL(s) = 7;
    } else {
        if (row == scroll && --scroll < 0)
            scroll = 0;
        P9_ROW(s) = row - 1;
        P9_SCROLL(s) = scroll;
    }
    SE(0);
    return 1;
}

/* 0x003786B0, 0x134 bytes. Page 9: down a row (the last rows only scroll). */
int func_003786B0(int wrap)
{
    u8 *s = func_00376770();
    int row = P9_ROW(s), scroll = P9_SCROLL(s);

    if (P9_COL(s) + (row + 1) * 0x0D < 0x8E) {
        if (row == scroll + 3 && ++scroll > 7)
            scroll = 7;
        P9_ROW(s) = row + 1;
        P9_SCROLL(s) = scroll;
        SE(0);
        return 1;
    }
    if (wrap == 0) {
        if (scroll < 7) {
            P9_SCROLL(s) = 7;
            SE(0);
            return 1;
        }
        return 0;
    }
    if (scroll < 7) {
        P9_SCROLL(s) = 7;
        SE(0);
    } else {
        P9_ROW(s) = 0;
        P9_SCROLL(s) = 0;
        SE(0);
    }
    return 1;
}

/* 0x003787F0, 0xBC bytes. Page 9: left. */
int func_003787F0(int wrap)
{
    u8 *s = func_00376770();

    if (P9_COL(s) == 0) {
        int c = 0x0C, i;

        if (wrap == 0)
            return 0;
        for (i = P9_ROW(s) * 0x0D + 0x0C; i > 0x8D; i--)
            c--;
        P9_COL(s) = c;
    } else {
        P9_COL(s)--;
    }
    SE(0);
    return 1;
}

/* 0x003788B0, 0xA4 bytes. Page 9: right. */
int func_003788B0(int wrap)
{
    u8 *s = func_00376770();
    int c = P9_COL(s) + 1;

    if (P9_COL(s) == 0x0C || c + P9_ROW(s) * 0x0D > 0x8D) {
        if (wrap == 0)
            return 0;
        P9_COL(s) = 0;
    } else {
        P9_COL(s) = c;
    }
    SE(0);
    return 1;
}

/* 0x00378960, 0x50 bytes. Whether both names are set. */
int func_00378960(void)
{
    u8 *rec = func_00376820();

    if (func_00147070((const unsigned char *)((char *)rec + 1)) < 1 || func_00147070((const unsigned char *)((char *)rec + 10)) < 1)
        return 0;
    return 1;
}

/* Page 0's state (the block's start): +0 mode (0 the lines, 1 the grid), +4, +8 line, +0xC
 * column, +0x10 row, +0x20, +0x21 the name being typed, +0x22 its cursors. */
#define P0_MODE(s)   (*(int *)((s) + 0))
#define P0_LINE(s)   (*(int *)((s) + 8))
#define P0_COL(s)    (*(int *)((s) + 0x0C))
#define P0_ROW(s)    (*(int *)((s) + 0x10))
#define P0_WHICH(s)  ((s)[0x21])
#define P0_CURSOR(s) (&(s)[0x22 + P0_WHICH(s)])

/* Back from a page to the menu (page 10) (inlined). */
#define TO_MENU(es) (*(int *)((es) + 0xB0) = 10)

/* 0x003789B0, 0x5BC bytes. Page 0, the names: three lines (the two names, OK); on a name the
 * grid of characters (Start the side buttons, L / R move in the name, the extra button
 * deletes, OK types or, on the side buttons, goes back to the lines). */
int func_003789B0(void)
{
    u8 *es = func_003766C0();
    u8 *rec = func_00376820();
    char buffer[0x400];
    u8 *s;
    unsigned short held, pressed;

    func_0011ED38(buffer, 0, 0x400);
    s = func_003766E0();
    held = pad1_held();
    pressed = pad1_pressed();
    if (P0_MODE(s) == 0) {
        int line = P0_LINE(s);

        if (pressed & BTN_OK) {
            SE(1);
            if (line == 2) {
                TO_MENU(es);
                func_003774E0(0);
                return 0;
            }
            SHOW_GRID(es);
            P0_WHICH(s) = line;
            P0_COL(s) = 1;
            P0_ROW(s) = 0;
            s[0x20] = 0;
            *(int *)(s + 4) = 0;
            P0_MODE(s) = 1;
        } else if (pressed & BTN_CANCEL) {
            es[0xB97] = 1;
            TO_MENU(es);
            func_003774E0(0);
            SE(2);
            return 0;
        } else if (held & BTN_UP) {
            func_00377780(&line, 3, pressed & BTN_UP);
            if (func_00378960() == 0 && line == 2)
                line = 1;
        } else if (held & BTN_DOWN) {
            func_00377800(&line, 3, pressed & BTN_DOWN);
            if (func_00378960() == 0 && line == 2)
                line = 0;
        }
        P0_LINE(s) = line;
        return 1;
    }
    if (P0_MODE(s) != 1)
        return 1;
    {
        const u8 *grid = (const u8 *)g_0045C478;
        int col, row;
        char *name;

        if (*(int *)(s + 4) == 4)
            *(int *)(s + 4) = 0;
        col = P0_COL(s);
        row = P0_ROW(s);
        name = (char *)rec + (P0_WHICH(s) == 1 ? 1 : 10);
        if (pressed & BTN_OK) {
            if (col == 0) {
                SE(1);
                SHOW_LIST(es);
                P0_MODE(s) = 0;
            } else if (func_00147070((const unsigned char *)(name)) < 8) {
                func_003768B0(name, P0_CURSOR(s), grid[col - 1 + row * 0x11]);
                SE(1);
            } else {
                SE(4);
            }
        } else if (pressed & BTN_EXTRA2) {
            if (func_00147070((const unsigned char *)(name)) > 0) {
                SE(2);
                func_00376B20(name, P0_CURSOR(s));
            }
        } else if (pressed & BTN_START) {
            col = 0;
            SE(1);
        } else if (pressed & BTN_L) {
            func_00376DA0(P0_CURSOR(s));
        } else if (pressed & BTN_R) {
            func_00376D20(name, P0_CURSOR(s));
        } else {
            if (held & BTN_UP) {
                if (func_00377FE0(col, &row, 6, grid, pressed & BTN_UP) != 0)
                    func_003D4770(func_003766C0() + 0x98C);
            } else if (held & BTN_DOWN) {
                if (func_003780A0(col, &row, 6, grid, pressed & BTN_DOWN) != 0)
                    func_003D4770(func_003766C0() + 0x98C);
            }
            if (held & BTN_LEFT) {
                if (func_00378150(&col, &row, 0x11, grid, pressed & BTN_LEFT) != 0)
                    func_003D4770(func_003766C0() + 0x98C);
            } else if (held & BTN_RIGHT) {
                if (func_00378210(&col, &row, 0x11, grid, pressed & BTN_RIGHT) != 0)
                    func_003D4770(func_003766C0() + 0x98C);
            }
        }
        P0_COL(s) = col;
        P0_ROW(s) = row;
    }
    return 1;
}

/* A list page (inlined in each): OK keeps the choice, Cancel undoes the page (the flag makes
 * the menu restore the record), Up / Down move; the choice is shown at once. */
#define LIST_CANCEL(es) do {                                            \
        (es)[0xB97] = 1;                                                \
        TO_MENU(es);                                                    \
        SE(2);                                                          \
    } while (0)
#define RESTORE_RECORD() func_0011EB80(func_00376820(), func_00376830(), 0x38)

typedef struct { int v[13]; } Bodies;

/* 0x00378F70, 0x308 bytes. Page 1, the body (13, 10 shown), Left / Right its colour (10). */
int func_00378F70(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_003766F0();
    Bodies bodies = *(Bodies *)g_00416560;
    int colour = s[2], scroll = s[1], cursor = s[0];
    unsigned short held = pad1_held();
    unsigned short pressed = pad1_pressed();

    s[3] = 0;
    if (pressed & BTN_OK) {
        RESTORE_RECORD();
        func_00376EE0(bodies.v[cursor]);
        func_00377170((u8)colour);
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        return 0;
    }
    if (held & BTN_UP) {
        if (func_00377880(&cursor, &scroll, 10, 0x0D, pressed & BTN_UP) != 0)
            s[3] = 1;
    } else if (held & BTN_DOWN) {
        if (func_00377930(&cursor, &scroll, 10, 0x0D, pressed & BTN_DOWN) != 0)
            s[3] = 1;
    }
    if (held & BTN_LEFT) {
        if (func_00377780(&colour, 10, pressed & BTN_LEFT) != 0) {
            func_003D4770(func_003766C0() + 0x974);
            s[3] = 1;
        }
    } else if (held & BTN_RIGHT) {
        if (func_00377800(&colour, 10, pressed & BTN_RIGHT) != 0) {
            func_003D4770(func_003766C0() + 0x974);
            s[3] = 1;
        }
    }
    s[0] = cursor;
    s[2] = colour;
    s[1] = scroll;
    RESTORE_RECORD();
    func_00376EE0(bodies.v[cursor]);
    func_00377170((u8)colour);
    return 1;
}

/* The body groups (inlined): 0 male, 1 female, 2 the others. */
#define BODY_MALE(b) ((b) == 0x30 || (b) == 0x21 || (b) == 0x20 || (b) == 0x1F || (b) == 0x1E || \
                      (b) == 0x1D || (b) == 0x1C)
#define BODY_FEMALE(b) ((b) == 0x38 || (b) == 0x37 || (b) == 0x36)
#define BODY_OTHER(b) ((b) == 0x35 || (b) == 0x34 || (b) == 0x33)

typedef struct { int v[16]; } List16;
typedef struct { int v[18]; } List18;
typedef struct { int v[15]; } List15;

/* 0x00379280, 0x3A0 bytes. Page 2, the weapon: the list of the body's group (10 shown). */
int func_00379280(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_00376700();
    List16 other = *(List16 *)g_004165A0;
    List18 female = *(List18 *)g_004165E0;
    List15 male = *(List15 *)g_00416630;
    int scroll = s[1], cursor = s[0];
    int body = *(int *)(es + 0x41C);
    int *list;
    int n;
    unsigned short held, pressed;

    if (BODY_MALE(body)) {
        list = male.v;
        n = 0x0F;
    } else if (BODY_FEMALE(body)) {
        list = female.v;
        n = 0x12;
    } else if (BODY_OTHER(body)) {
        list = other.v;
        n = 0x10;
    }
    held = pad1_held();
    pressed = pad1_pressed();
    s[2] = 0;
    if (pressed & BTN_OK) {
        RESTORE_RECORD();
        func_00377190(list[cursor]);
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        return 0;
    }
    if (held & BTN_UP) {
        if (func_00377880(&cursor, &scroll, 10, n, pressed & BTN_UP) != 0)
            s[2] = 1;
    } else if (held & BTN_DOWN) {
        if (func_00377930(&cursor, &scroll, 10, n, pressed & BTN_DOWN) != 0)
            s[2] = 1;
    }
    s[0] = cursor;
    s[1] = scroll;
    RESTORE_RECORD();
    func_00377190(list[cursor]);
    return 1;
}

/* 0x00379620, 0x280 bytes. Page 3 (record +0x2B): 9 choices, 11 for the female group. */
int func_00379620(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_00376730();
    int scroll = s[1], cursor = s[0];
    int body = *(int *)(es + 0x41C);
    int n;
    unsigned short held = pad1_held();
    unsigned short pressed = pad1_pressed();

    if (BODY_MALE(body) || BODY_OTHER(body))
        n = 9;
    else if (BODY_FEMALE(body))
        n = 0x0B;
    if (pressed & BTN_OK) {
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        return 0;
    }
    if (held & BTN_UP)
        func_00377880(&cursor, &scroll, 4, n, pressed & BTN_UP);
    else if (held & BTN_DOWN)
        func_00377930(&cursor, &scroll, 4, n, pressed & BTN_DOWN);
    s[0] = cursor;
    s[1] = scroll;
    func_00377210((u8)cursor);
    return 1;
}

/* 0x003798A0, 0x3AC bytes. Page 4, the voice (four of the group); the extra button plays one of
 * its eight samples (func_00377730) when none is playing. */
int func_003798A0(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_00376710();
    int female[4], male[4];
    int *list;
    int base, n = 4, i;
    int cursor = s[0];
    int body = *(int *)(es + 0x41C);
    unsigned short held, pressed;

    for (i = 0; i < 4; i++) {
        female[i] = g_00416670[i];
        male[i] = g_00416670[4 + i];
    }
    if (BODY_MALE(body) || BODY_OTHER(body)) {
        list = male;
        base = 0;
    } else if (BODY_FEMALE(body)) {
        list = female;
        base = 0x20;
    }
    if (s[1] > 0xF90 && s[1] < 0x151E && func_0023A8B0(s[1]) != 0)
        s[1] = 0;
    held = pad1_held();
    pressed = pad1_pressed();
    if (pressed & BTN_OK) {
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        func_0023AA40();
        return 0;
    }
    if (pressed & BTN_EXTRA) {
        if (s[1] < 0xF91 || s[1] > 0x151D) {
            s[1] = func_00377730((RANDOM() & 7) + base + cursor * 8);
            if (func_0023A900(s[1], 0) == 0)
                s[1] = 0;
        }
    } else if (held & BTN_UP) {
        func_00377780(&cursor, n, pressed & BTN_UP);
    } else if (held & BTN_DOWN) {
        func_00377800(&cursor, n, pressed & BTN_DOWN);
    }
    s[0] = cursor;
    func_00377230(list[cursor]);
    return 1;
}

/* 0x00379C50, 0x3D0 bytes. Page 5 (record +0x2A): the list of the weapon's kind (10 shown). */
int func_00379C50(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_00376720();
    int a[12], b[12], c[11];
    int *list;
    int n, i, weapon;
    int scroll, cursor = s[0];
    unsigned short held, pressed;

    for (i = 0; i < 12; i++) {
        a[i] = g_00416690[i];
        b[i] = g_004166C0[i];
    }
    for (i = 0; i < 11; i++)
        c[i] = g_004166F0[i];
    scroll = s[1];
    weapon = *(int *)(func_00376820() + 0x20);
    if (weapon == 0x0F || weapon == 7) {
        list = b;
        n = 0x0C;
    } else if (weapon == 0x15 || weapon == 2) {
        list = a;
        n = 0x0C;
    } else {
        list = c;
        n = 0x0B;
    }
    held = pad1_held();
    pressed = pad1_pressed();
    if (pressed & BTN_OK) {
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        return 0;
    }
    if (held & BTN_UP)
        func_00377880(&cursor, &scroll, 10, n, pressed & BTN_UP);
    else if (held & BTN_DOWN)
        func_00377930(&cursor, &scroll, 10, n, pressed & BTN_DOWN);
    s[0] = cursor;
    s[1] = scroll;
    func_00377250((u8)list[cursor]);
    return 1;
}

/* A simple list page of `n` lines calling `set` (inlined: pages 6 and 7). */
#define SIMPLE_PAGE(state, n, set) do {                                 \
        u8 *es = func_003766C0();                                       \
        int *s = (int *)(state);                                        \
        int cursor = s[0];                                              \
        unsigned short held = pad1_held();                              \
        unsigned short pressed = pad1_pressed();                        \
                                                                        \
        if (pressed & BTN_OK) {                                         \
            TO_MENU(es);                                                \
            SE(1);                                                      \
            return 0;                                                   \
        }                                                               \
        if (pressed & BTN_CANCEL) {                                     \
            LIST_CANCEL(es);                                            \
            return 0;                                                   \
        }                                                               \
        if (held & BTN_UP)                                              \
            func_00377780(&cursor, (n), pressed & BTN_UP);              \
        else if (held & BTN_DOWN)                                       \
            func_00377800(&cursor, (n), pressed & BTN_DOWN);            \
        s[0] = cursor;                                                  \
        set((u8)cursor);                                                \
        return 1;                                                       \
    } while (0)

/* 0x0037A020, 0x1A0 bytes. Page 6 (record +0x2D): 7 lines. */
int func_0037A020(void)
{
    SIMPLE_PAGE(func_00376750(), 7, func_00377290);
}

/* 0x0037A1C0, 0x1A0 bytes. Page 7 (record +0x2C): 4 lines. */
int func_0037A1C0(void)
{
    SIMPLE_PAGE(func_00376740(), 4, func_00377270);
}

/* 0x0037A360, 0x2A8 bytes. Page 8 (record +0x2E): a 14-wide grid of 0x43. */
int func_0037A360(void)
{
    u8 *es = func_003766C0();
    u32 *s = (u32 *)func_00376760();
    int col = (int)*s % 0x0E, row = (int)*s / 0x0E;
    unsigned short held = pad1_held();
    unsigned short pressed = pad1_pressed();

    if (pressed & BTN_OK) {
        TO_MENU(es);
        SE(1);
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        LIST_CANCEL(es);
        return 0;
    }
    if (held & BTN_UP) {
        if (func_003782D0(&col, &row, 0x43, pressed & BTN_UP) != 0)
            func_003D4770(func_003766C0() + 0x974);
    } else if (held & BTN_DOWN) {
        if (func_003783D0(&col, &row, 0x43, pressed & BTN_DOWN) != 0)
            func_003D4770(func_003766C0() + 0x974);
    }
    if (held & BTN_LEFT) {
        if (func_00378460(&col, &row, 0x43, pressed & BTN_LEFT) != 0)
            func_003D4770(func_003766C0() + 0x974);
    } else if (held & BTN_RIGHT) {
        if (func_00378520(&col, &row, 0x43, pressed & BTN_RIGHT) != 0)
            func_003D4770(func_003766C0() + 0x974);
    }
    *s = col + row * 0x0E;
    func_003772D0((u8)*s);
    return 1;
}

/* 0x0037A610, 0x53C bytes. Page 9, the two colours (record +0x2F, +0x30): three lines (the two
 * colours, OK); the extra button picks two different random colours; on a colour, its grid. */
int func_0037A610(void)
{
    u8 *rec = func_00376820();
    u8 *es = func_003766C0();
    int *s = (int *)func_00376770();
    unsigned short held = pad1_held();
    unsigned short pressed = pad1_pressed();

    if (s[0] == 0) {
        int line = s[1];

        if (pressed & BTN_OK) {
            u8 colour;

            SE(1);
            if (line == 2) {
                TO_MENU(es);
                func_003774E0(0);
                return 0;
            }
            colour = line == 0 ? rec[0x2F] : rec[0x30];
            SHOW_GRID(es);
            ((u8 *)s)[0x14] = line;
            s[2] = colour % 0x0D;
            s[3] = colour / 0x0D;
            s[4] = colour < 0x34 ? 0 : (colour - 0x34) / 0x0D + 1;
            ((u8 *)s)[0x15] = 0;
            s[0] = 1;
        } else if (pressed & BTN_CANCEL) {
            es[0xB97] = 1;
            TO_MENU(es);
            func_003774E0(0);
            SE(2);
            return 0;
        } else if (pressed & BTN_EXTRA2) {
            u32 second;

            func_003772F0((u8)(RANDOM() % 0x8E));
            second = RANDOM() % 0x8E;
            while (second == func_00376820()[0x2F])
                second = RANDOM() % 0x8E;
            func_00377310((u8)second);
            SE(1);
        } else if (held & BTN_UP) {
            func_00377780(&line, 3, pressed & BTN_UP);
        } else if (held & BTN_DOWN) {
            func_00377800(&line, 3, pressed & BTN_DOWN);
        }
        s[1] = line;
        return 1;
    }
    if (s[0] != 1)
        return 1;
    if (pressed & BTN_OK) {
        u32 colour = s[2] + s[3] * 0x0D;

        if (((u8 *)s)[0x14] == 0)
            func_003772F0((u8)colour);
        else
            func_00377310((u8)colour);
        SHOW_LIST(es);
        s[0] = 0;
        SE(1);
        return 1;
    }
    if (pressed & BTN_CANCEL) {
        SHOW_LIST(es);
        s[0] = 0;
        SE(2);
        return 1;
    }
    if (held & BTN_UP) {
        if (func_003785C0(pressed & BTN_UP) != 0)
            func_003D4770(func_003766C0() + 0x98C);
    } else if (held & BTN_DOWN) {
        if (func_003786B0(pressed & BTN_DOWN) != 0)
            func_003D4770(func_003766C0() + 0x98C);
    }
    if (held & BTN_LEFT) {
        if (func_003787F0(pressed & BTN_LEFT) != 0)
            func_003D4770(func_003766C0() + 0x98C);
    } else if (held & BTN_RIGHT) {
        if (func_003788B0(pressed & BTN_RIGHT) != 0)
            func_003D4770(func_003766C0() + 0x98C);
    }
    return 1;
}

/* Which message box is open (inlined): 0, 1, or 5 = none; and its answer. */
#define OPEN_BOX() (BOX_STATE(0) != 0 ? 0 : BOX_STATE(1) != 0 ? 1 : 5)

/* 0x0037AB50, 0x724 bytes. Page 10, the menu (11 lines: pages 0-9, then done). Lines 1, 2 and
 * 5 only for a new officer, 3 only with a weapon variant, 6 only for a new officer. Done (or
 * Cancel) asks to keep the changes (messages 0x2D1-0x2D4), then goes back to the list. */
int func_0037AB50(void)
{
    u8 *es = func_003766C0();
    int *s = (int *)func_00376780();
    int box = OPEN_BOX();
    char answer = box == 5 ? 0 : BOX_ANSWER(box);
    char buffer[256];
    int line;
    unsigned short held, pressed;

    if (box == 0)
        return 1;
    if (box == 1) {
        if (*(int *)(es + 0xB8C) == 0x2D1) {
            if (answer == 4) {
                *(int *)(es + 0xB0) = 0x0B;
                func_001AFE20(1);
                BOX_CLOSED();
                return 0;
            }
            if (answer == 5) {
                func_001AFE20(1);
                BOX_CLOSED();
            }
            return 1;
        }
        if (*(int *)(es + 0xB8C) == 0x2D2) {
            if (answer != 4) {
                if (answer == 5) {
                    func_001AFE20(1);
                    BOX_CLOSED();
                }
                return 1;
            }
            if (es[0x405] == 0)
                func_00120928((char *)es + 0x405, TEXT_OFFICER);
            if (es[0x40E] == 0)
                func_00120928((char *)es + 0x40E, TEXT_NEW);
            if (es[0xB95] == 1)
                func_00376E00(func_00376850(), *(int *)(es + 0x424), es[0x42F]);
            if (func_00377E20() != 0)
                es[0xB96] = 1;
            func_003779E0(es[0xB94]);
            func_003774E0(2);
            *(int *)(es + 0xB0) = 0x0B;
            func_001AFE20(1);
            BOX_CLOSED();
            return 0;
        }
    }
    line = s[0];
    held = pad1_held();
    pressed = pad1_pressed();
    if (pressed & BTN_OK) {
        SE(1);
        if (line == 10) {
            if (func_00377E20() != 0) {
                int id = es[0xB95] == 0 ? 0x2D4 : 0x2D2;

                *(int *)(es + 0xB8C) = 0x2D2;
                ASK(1, MESSAGE(id));
                BOX_OPENED();
                return 1;
            }
            func_003774E0(2);
            *(int *)(es + 0xB0) = 0x0B;
        } else {
            *(int *)(es + 0xB0) = line;
            if (line == 0 || line == 9)
                func_003774E0(1);
        }
        return 0;
    }
    if (pressed & BTN_CANCEL) {
        int id;

        SE(2);
        if (func_00377E20() == 0) {
            func_003774E0(2);
            *(int *)(es + 0xB0) = 0x0B;
            return 0;
        }
        id = es[0xB95] == 0 ? 0x2D3 : 0x2D1;
        *(int *)(es + 0xB8C) = 0x2D1;
        ASK(1, MESSAGE(id));
        BOX_OPENED();
    } else if (pressed & BTN_START) {
        line = 10;
        SE(1);
    } else if (held & BTN_UP) {
        func_00377780(&line, 0x0B, pressed & BTN_UP);
        if (line == 6 && func_00377DF0() == 0)
            line--;
        if (line == 5 && func_00377D50() == 0)
            line--;
        if (line == 3 && func_00377D80() == 0)
            line--;
        if (line == 2 && func_00377D50() == 0)
            line--;
        if (line == 1 && func_00377D50() == 0)
            line--;
    } else if (held & BTN_DOWN) {
        func_00377800(&line, 0x0B, pressed & BTN_DOWN);
        if (line == 1 && func_00377D50() == 0)
            line++;
        if (line == 2 && func_00377D50() == 0)
            line++;
        if (line == 3 && func_00377D80() == 0)
            line++;
        if (line == 5 && func_00377D50() == 0)
            line++;
        if (line == 6 && func_00377DF0() == 0)
            line++;
    }
    s[0] = line;
    return 1;
}

/* 0x0037B280, 0x8DC bytes. Page 11, the list of the 15 edited officers (10 shown): OK edits
 * one (or makes a new one), the extra button deletes one (unless in use), Cancel saves (asked)
 * and leaves; then the save dialog (func_002DAC30). */
int func_0037B280(void)
{
    u8 *es = func_003766C0();
    u8 *saved = func_003766D0();
    int *s = (int *)func_00376790();
    int box = 5;
    char answer;
    char buffer[256];
    int i;

    s[2] = 0;
    box = OPEN_BOX();
    answer = box == 5 ? 0 : BOX_ANSWER(box);
    if (*(int *)(es + 0xB90) == 2) {
        int r = func_002DAC30();

        if (r == 1) {
            func_002D8160();
            *(int *)(es + 0xB90) = 1;
            *(int *)(es + 0xB0) = 0x0C;
            LIST_START();
            return 0;
        }
        if (r == 2) {
            u8 *rec = saved, *extra = saved;

            func_002D8160();
            for (i = 0; i < 0x0F; i++) {               /* the save failed: back to the copies */
                func_0011EB80(g_00669D60 + 0x254 + i * 0x38, rec, 0x38);
                func_003A5320(extra + 0x348, i + 400);
                rec += 0x38;
                extra += 0x48;
            }
            *(int *)(es + 0xB90) = 1;
            func_001037F0(0);
            LIST_START();
        }
        return 1;
    }
    if (box == 0) {
        if (answer == 1)
            LIST_START();
        return 1;
    }
    if (box == 1) {
        int asked = *(int *)(es + 0xB8C);

        if (asked == 0x2CD) {                          /* save? */
            if (answer == 4) {
                u8 *rec = saved, *extra = saved;

                func_001037F0(0);
                for (i = 0; i < 0x0F; i++) {
                    func_0011EB80(rec, g_00669D60 + 0x254 + i * 0x38, 0x38);
                    func_003A5360(extra + 0x348, i + 400);
                    func_0011EB80(g_00669D60 + 0x254 + i * 0x38, es + 0xBC + i * 0x38, 0x38);
                    if (es[0xBC + i * 0x38] != 0)
                        func_003A5320(g_0045D7C8 + i * 0x48 + 0x4AC, i + 400);
                    rec += 0x38;
                    extra += 0x48;
                }
                func_002DBAA0();
                func_002D8060(0);
                *(int *)(es + 0xB90) = 2;
                func_001AFE20(1);
                return 0;
            }
            if (answer == 5) {
                func_001AFE20(1);
                func_001AEE10(1, -1, -1);
                func_001AEDB0(1, -1, -1, 0);
                *(int *)(es + 0xB8C) = 0x2CE;
                ASK(1, TEXT_LOST);
                return 1;
            }
            return 1;
        }
        if (asked == 0x2CE) {                          /* leave without saving? */
            if (answer == 4) {
                *(int *)(es + 0xB0) = 0x0C;
                func_001AFE20(1);
                LIST_START();
                return 0;
            }
            if (answer == 5) {
                func_001AFE20(1);
                LIST_START();
            }
            return 1;
        }
        if (asked == 0x2CF) {                          /* delete? */
            if (answer == 4) {
                func_00377D10(s[0]);
                es[0xB96] = 1;
                s[2] = 1;
                func_001AFE20(1);
                LIST_START();
                return 0;
            }
            if (answer == 5) {
                func_001AFE20(1);
                LIST_START();
            }
            return 1;
        }
    }
    {
        int cursor = s[0], scroll = s[1];
        unsigned short held = pad1_held();
        unsigned short pressed = pad1_pressed();

        if (held & BTN_UP) {
            if (func_00377880(&cursor, &scroll, 10, 0x0F, pressed & BTN_UP) != 0)
                s[2] = 1;
        } else if (held & BTN_DOWN) {
            if (func_00377930(&cursor, &scroll, 10, 0x0F, pressed & BTN_DOWN) != 0)
                s[2] = 1;
        } else if (pressed & BTN_OK) {
            SE(1);
            es[0xB94] = cursor;
            if (es[cursor * 0x38 + 0xBC] == 0) {
                func_00377AA0();
            } else {
                if (func_00377E70(cursor) == 0) {
                    *(int *)(es + 0xB8C) = 0x2D0;
                    ASK(0, TEXT_IN_USE);
                    LIST_START_ALT();
                    return 1;
                }
                func_00377BC0(cursor);
            }
            func_003774E0(2);
            *(int *)(es + 0xB0) = 10;
            show_record(func_00376820());
            *(int *)(es + 0xB98) = 1;
            return 0;
        } else if (pressed & BTN_CANCEL) {
            SE(2);
            if (es[0xB96] == 1) {
                *(int *)(es + 0xB8C) = 0x2CD;
                ASK(1, TEXT_SAVE);
                LIST_START_ALT();
                return 1;
            }
            *(int *)(es + 0xB0) = 0x0C;
            return 0;
        } else if ((pressed & BTN_EXTRA2) && es[cursor * 0x38 + 0xBC] != 0) {
            SE(1);
            if (func_00377E70(cursor) == 0) {
                *(int *)(es + 0xB8C) = 0x2D0;
                ASK(0, TEXT_IN_USE);
            } else {
                *(int *)(es + 0xB8C) = 0x2CF;
                ASK(1, TEXT_DELETE);
            }
            LIST_START_ALT();
        }
        s[0] = cursor;
        s[1] = scroll;
    }
    return 1;
}

/* 0x0037BB60, 0x104 bytes. Loads the models and motions of the editor. */
void func_0037BB60(void)
{
    int i;

    func_001BE1A0();
    for (i = 0; i < 0x0D; i++)
        func_001BD2C0(func_00377330(i));
    for (i = 0; i < 0x1E; i++)
        func_0017C7D0(func_00377380(i));
    func_001BE030();
    for (i = 0; i < 0x1E; i++)
        func_0016D060(motion_slot(i), (void *)PS2_PTR(-1), 0);
    func_001BC540();
}

/* 0x0037BC70, 0x1B8 bytes. Sets the model view's height for `kind` (90, plus the weapon's offset;
 * 6 lower for body 0x30 with models 0x26, 0x2A and 0x20) and resets the view. */
void func_0037BC70(int body, int kind)
{
    u8 *es = func_003766C0();
    int weapons[22], offsets[22];
    int i, found = -1;

    for (i = 0; i < 22; i++)
        weapons[i] = g_00416720[i];
    for (i = 0; i < 22; i++)
        offsets[i] = g_00416780[i];
    for (i = 0; i < 0x16; i++)
        if (kind == weapons[i]) {
            found = i;
            break;
        }
    if (found == -1) {
        *(float *)(es + 0xB9C) = 90.0f;
    } else {
        *(float *)(es + 0xB9C) = (float)offsets[found] + 90.0f;
        if (body == 0x30 && (kind == 0x26 || kind == 0x2A || kind == 0x20))
            *(float *)(es + 0xB9C) -= 6.0f;
    }
    s_007B9E40.g_007B9E44 = 0;
    s_007B9E40.g_007B9E40 = 0x28;
    s_007B9E40.g_007B9E53 = 0;
    s_007B9E40.g_007B9E46 = 0;
    s_007B9E40.g_007B9E50 = 0x80;
    s_007B9E40.g_007B9E48 = 0x28;
    s_007B9E40.g_007B9E4A = (u16)(int)*(float *)(es + 0xB9C);
    s_007B9E40.g_007B9E42 = s_007B9E40.g_007B9E4A;
    s_007B9E40.g_007B9E51 = 0x80;
    s_007B9E40.g_007B9E4C = 0;
    s_007B9E40.g_007B9E4E = 0;
    s_007B9E40.g_007B9E52 = 0;
}

/* 0x0037BE30, 0x9C bytes, matching. Shows the model of an officer (body, colour, weapon kind, model). */
void func_0037BE30(int body, int colour, int kind, int model)
{
    func_003766C0();
    func_0037BC70(body, kind);
    func_00166160(g_00574DE0[0]);
    func_00165C60(g_00574DE0[0], body, kind, model, 0x11, 0, colour, 1);
    func_00165180(g_00574DE0[0], 1, 0);
}

/* 0x0037BED0, 0x28 bytes, matching. Hides the model. */
void func_0037BED0(void)
{
    func_003766C0();
    func_00166160(g_00574DE0[0]);
}

/* 0x0037BF00, 0x120 bytes. Shows the first officer record's model (if it is set). */
void func_0037BF00(void)
{
    u8 *es = func_003766C0();
    u8 *rec = es + 0xBC;

    func_001BE4F0();
    func_001646C0(g_00574DE0[0], 0);
    if (rec[0] == 0) {
        ES_SHOWN = 0;
        return;
    }
    show_record(rec);
    ES_SHOWN = 1;
}

/* 0x0037C020, 0x8C bytes, matching. Places the player unit and the model for the editor's view. */
void func_0037C020(void)
{
    u8 *unit = g_005B4BC0[0];

    func_0017A920(unit);
    *(float *)(unit + 0x1C0) = 0.0f;
    *(float *)(unit + 0x1C4) = -60.0f;
    *(float *)(unit + 0x1C8) = 520.0f;
    *(float *)(unit + 0x1CC) = 1.0f;
    *(float *)(unit + 0x1D0) = 0.0f;
    *(float *)(unit + 0x1D4) = 0.0f;
    *(float *)(unit + 0x1D8) = 0.0f;
    *(float *)(unit + 0x1DC) = 1.0f;
    *(float *)(g_00574DE0[0] + 0x40) = 40.0f;
    *(float *)(g_00574DE0[0] + 0x44) = 90.0f;
    func_003774E0(0);
}

/* 0x0037C0B0, 0x78 bytes. Prepares the model and the view. */
void func_0037C0B0(void)
{
    func_0019F550();
    func_00101470(0);
    func_0037BB60();
    func_0037BF00();
    func_00182C30();
    func_0017A920(g_005B4BC0[0]);
    g_0045D2C0_SET(g_005B4BC0[0]);
    g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
    func_0037C020();
}

/* 0x0037C130, 0x24 bytes, matching. */
void func_0037C130(void)
{
    func_00178460();
    func_00182C20();
}

/* 0x0037C160, 0x38 bytes. The scroll of a list of `count` entries showing `shown`, with the
 * cursor on `index`. */
int func_0037C160(int count, int shown, int index)
{
    if (count <= shown)
        return 0;
    if (index < shown)
        return 0;
    return index - shown + 1;
}

/* Finds `value` in `list` (-1 when absent). */
static int find_in(const int *list, int count, int value)
{
    int i;

    for (i = 0; i < count; i++)
        if (value == list[i])
            return i;
    return -1;
}

/* 0x0037C1A0, 0xD4 bytes. Page 1 set-up (the body): the cursor on the record's body. */
void func_0037C1A0(void)
{
    u8 *es = func_003766C0();
    int list[13];
    int i, found;

    for (i = 0; i < 13; i++)
        list[i] = g_004167E0[i];
    found = find_in(list, 13, *(int *)(ES_RECORD + 0x18));
    if (found >= 0) {
        *(int *)(es + 0x30) = found;
        *(int *)(es + 0x34) = func_0037C160(0x0D, 10, found);
        *(int *)(es + 0x38) = ES_RECORD[0x1C];
    }
    LIST_START();
    func_003D4770(func_003766C0() + 0x974);
}

/* 0x0037C280, 0x1FC bytes. Page 2 set-up (the weapon): the list by body group, the cursor on
 * the record's weapon. */
void func_0037C280(void)
{
    u8 *es = func_003766C0();
    int list_a[16], list_b[18], list_c[15];
    int body = *(int *)(ES_RECORD + 0x18);
    int *list = 0, count = 0, i, found;      /* (count is left unset by the original for other bodies) */

    for (i = 0; i < 16; i++)
        list_a[i] = g_00416820[i];
    for (i = 0; i < 18; i++)
        list_b[i] = g_00416860[i];
    for (i = 0; i < 15; i++)
        list_c[i] = g_004168B0[i];
    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C) {
        list = list_c;
        count = 0x0F;
    } else if (body == 0x38 || body == 0x37 || body == 0x36) {
        list = list_b;
        count = 0x12;
    } else if (body == 0x35 || body == 0x34 || body == 0x33) {
        list = list_a;
        count = 0x10;
    }
    found = list ? find_in(list, count, *(int *)(ES_RECORD + 0x20)) : -1;
    if (found >= 0) {
        *(int *)(es + 0x40) = found;
        *(int *)(es + 0x44) = func_0037C160(count, 10, found);
    }
    LIST_START();
}

/* 0x0037C480, 0x11C bytes. Page 3 set-up: the cursor on choice +0x2B (9 or 11 entries by body
 * group). */
void func_0037C480(void)
{
    u8 *es = func_003766C0();
    int body = *(int *)(ES_RECORD + 0x18);
    int value = ES_RECORD[0x2B];
    int count = 0;

    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C || body == 0x35 || body == 0x34 || body == 0x33)
        count = 9;
    else if (body == 0x38 || body == 0x37 || body == 0x36)
        count = 0x0B;
    *(int *)(es + 0x64) = value;
    *(int *)(es + 0x68) = func_0037C160(count, 4, value);
    LIST_START();
}

/* 0x0037C5A0, 0x1AC bytes. Page 4 set-up: the cursor on choice +0x24 (two lists of 4 by body
 * group). */
void func_0037C5A0(void)
{
    u8 *es = func_003766C0();
    int list_a[4], list_b[4];
    int body = *(int *)(ES_RECORD + 0x18);
    int *list = 0, count = 0, i, found;

    for (i = 0; i < 4; i++) {
        list_b[i] = g_004168F0[i];
        list_a[i] = g_00416900[i];
    }
    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C || body == 0x35 || body == 0x34 || body == 0x33) {
        list = list_a;
        count = 4;
    } else if (body == 0x38 || body == 0x37 || body == 0x36) {
        list = list_b;
        count = 4;
    }
    found = list ? find_in(list, count, *(int *)(ES_RECORD + 0x24)) : -1;
    if (found >= 0)
        *(int *)(es + 0x4C) = found;
    LIST_START();
}

/* 0x0037C750, 0x288 bytes. Page 5 set-up: the cursor on choice +0x2A (lists by weapon). */
void func_0037C750(void)
{
    u8 *es = func_003766C0();
    u32 list_a[12], list_b[12], list_c[11];
    int weapon = *(int *)(ES_RECORD + 0x20);
    u32 *list = list_c;
    int count, i, found = -1;

    for (i = 0; i < 12; i++) {
        list_a[i] = g_00416910[i];
        list_b[i] = g_00416940[i];
    }
    for (i = 0; i < 11; i++)
        list_c[i] = g_00416970[i];
    if (weapon == 0x0F || weapon == 7) {
        list = list_b;
        count = 0x0C;
    } else if (weapon == 0x15 || weapon == 2) {
        list = list_a;
        count = 0x0C;
    } else {
        count = 0x0B;
    }
    for (i = 0; i < count; i++)
        if (ES_RECORD[0x2A] == list[i]) {
            found = i;
            break;
        }
    if (found >= 0) {
        *(int *)(es + 0x5C) = found;
        *(int *)(es + 0x60) = func_0037C160(count, 10, found);
    }
    LIST_START();
}

/* 0x0037C9E0, 0x48 bytes. Page 6 set-up: the cursor on choice +0x2D. */
void func_0037C9E0(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x74) = ES_RECORD[0x2D];
    LIST_START();
}

/* 0x0037CA30, 0x48 bytes. Page 7 set-up: the cursor on choice +0x2C. */
void func_0037CA30(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x6C) = ES_RECORD[0x2C];
    LIST_START();
}

/* 0x0037CA80, 0x54 bytes. Page 8 set-up: the cursor on choice +0x2E. */
void func_0037CA80(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x7C) = ES_RECORD[0x2E];
    LIST_START();
    func_003D4770(func_003766C0() + 0x974);
}

/* 0x0037CAE0, 0x20 bytes, matching. The length of a name (func_00120A40). */
u8 func_0037CAE0(const u8 *text)
{
    return func_00120A40(text);
}

/* 0x0037CB00, 0x10C bytes. Page 0 set-up (the name): clears the input state and reads the two
 * name parts' lengths (at most 7). */
void func_0037CB00(void)
{
    u32 *p = (u32 *)func_003766C0();              /* (accessor 0x003766E0: the same block) */
    int i;

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 1;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    ((u8 *)p)[0x20] = 0;
    ((u8 *)p)[0x21] = 0;
    for (i = 0; i < 2; i++) {
        u8 len = func_0037CAE0(ES_RECORD + (i == 1 ? 1 : 10));
        if (len > 7)
            len = 7;
        ((u8 *)p)[0x22 + i] = len;
    }
    LIST_START_ALT();
    func_003D4770(func_003766C0() + 0x974);
    func_003D4770(func_003766C0() + 0x98C);
    ES(0x990, u8) = ES(0x992, u8);
    ES(0x994, int) = 0;
    ES(0x998, int) = 1;
}

/* 0x0037CC10, 0x8C bytes. Page 9 set-up. */
void func_0037CC10(void)
{
    u32 *p = (u32 *)(func_003766C0() + 0x84);    /* (accessor 0x00376770) */

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    ((u8 *)p)[0x14] = 0;
    ((u8 *)p)[0x15] = 0;
    LIST_START_ALT();
    func_003D4770(func_003766C0() + 0x974);
    func_003D4770(func_003766C0() + 0x98C);
    ES(0x990, u8) = ES(0x992, u8);
    ES(0x994, int) = 0;
    ES(0x998, int) = 1;
}

/* 0x0037CCA0, 0x294 bytes. Opens the page asked for: keeps a copy of the record (to undo the
 * page) and sets the page's cursor up; 10 and 11 are the two confirmations. */
void func_0037CCA0(void)
{
    u8 *es = func_003766C0();

    switch (*(int *)(es + 0xB0)) {
    case 0:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CB00();
        break;
    case 1:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C1A0();
        break;
    case 2:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C280();
        break;
    case 3:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C480();
        break;
    case 4:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        *(int *)(es + 0x50) = 0;
        func_0037C5A0();
        break;
    case 5:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C750();
        break;
    case 6:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0011EB80(es + 0x92C, es + 0x8E4, 0x48);
        func_0037C9E0();
        break;
    case 7:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CA30();
        break;
    case 8:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CA80();
        break;
    case 9:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CC10();
        break;
    case 10:
        if (*(int *)(es + 0xB8) == 0x0B)
            *(int *)(es + 0x9C) = 0;
        *(int *)(es + 0xA0) = 1;
        g_00799A24 = g_00799A26;
        g_00799A28 = 1;
        g_00799A2C = 0;
        break;
    case 11:
        if (*(int *)(es + 0xB8) == 0x0C) {
            *(int *)(es + 0xA4) = 0;
            *(int *)(es + 0xA8) = 0;
        }
        *(int *)(es + 0xAC) = 1;
        LIST_START();
        break;
    }
}

/* 0x0037CF40, 0x10C bytes. Frees the editor's models and motions. */
void func_0037CF40(void)
{
    int i;

    func_003767A0(0);
    for (i = 0; i < 0x0D; i++)
        func_001BD180(func_00377330(i), 0, 0, 0);
    for (i = 0; i < 0x1E; i++)
        func_0017CC40(func_00377380(i), 0);
    func_001BC540();
    for (i = 0; i < 0x1E; i++)
        func_0016CFB0(motion_slot(i), 0);
}

/* 0x0037D060, 0xEC bytes. Scene 0x14 enter: allocates the editor's state and goes through the
 * loading screen (0x0F), back here. */
void func_0037D060(void)
{
    func_001037F0(0);
    func_003F8B30(3);
    g_0045D7C8_SET(func_00102DB0(0x10, 0xBA0));
    g_0045D7CC_SET(func_00102DB0(0x10, 0x780));
    func_00118850(g_0045D7C8, 0xBA0);
    func_00118850(g_0045D7CC, 0x780);
    func_0037CF40();
    func_002F15E0(0, 0);
    g_0045D89C = 0x0F;                            /* to the loading screen, then back */
    g_0045D8A0 = g_0045D898;
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

/* 0x0037D150, 0xEC bytes, matching. Scene 0x14 enter_alt (back from the loading screen): copies the 15
 * officer records of the game state, prepares the model and starts music 0x32. */
void func_0037D150(void)
{
    int i;

    func_00102960(1);
    func_002F1660();
    func_001A2040();
    for (i = 0; i < 0x0F; i++) {
        func_0011EB80(g_0045D7C8 + i * 0x38 + 0xBC, g_00669D60 + 0x254 + i * 0x38, 0x38);
        func_003A5360(g_0045D7C8 + i * 0x48 + 0x4AC, i + 400);
    }
    func_0037C0B0();
    func_003776D0();
    func_003D8280();
    if (func_0017DDA0() == 0)
        func_0017E010(0x32);
    func_001037F0(1);
    func_001B8F60(1, 6, 8);
}

/* 0x0037D240, 0x8 bytes, matching. Scene 0x14 leave_alt: empty (not found by Ghidra). */
void func_0037D240(void)
{
}

/* 0x0037D250, 0x6C bytes, matching. Scene 0x14 leave: frees the editor. */
void func_0037D250(void)
{
    func_0023AA40();
    func_0017DF10();
    func_00375D60();
    func_0037C130();
    func_003767E0();
    if (g_0045D7CC != 0)
        func_00102EC0(g_0045D7CC);
    g_0045D7CC_SET(0);
    if (g_0045D7C8 != 0)
        func_00102EC0(g_0045D7C8);
    g_0045D7C8_SET(0);
    func_003F8B80();
}

/* 0x0037D2C0, 0x90 bytes. Undoes the page's changes (pages other than 10-12, when changed). */
void func_0037D2C0(void)
{
    u8 *es = func_003766C0();

    if ((u32)(ES_PAGE - 10) >= 3 && ES_DIRTY == 1) {
        func_0011EB80(ES_RECORD, ES_BACKUP, 0x38);
        if (ES_PAGE == 6)
            func_0011EB80(es + 0x8E4, es + 0x92C, 0x48);
        ES_DIRTY = 0;
    }
}

/* 0x0037D350, 0x690 bytes. Scene 0x14 update: runs the page (phase 3), its transitions (in /
 * out over a timer; page 12 leaves the editor for the title, scene 1), then updates the model
 * when the shown officer changed (page 11: the officer list's choice; pages 10, 1 and 2: the
 * record) and the view. */
int func_0037D350(float dt)
{
    u8 *es = func_003766C0();
    int *list = (int *)func_003766C0() + 0xA4 / 4;    /* (accessor 0x00376790) */
    u8 *p10 = func_003766C0() + 0x9C;                 /* (accessor 0x00376780) */
    u8 *p1 = func_003766C0() + 0x30;                  /* (accessor 0x003766F0) */
    u8 *p2 = func_003766C0() + 0x40;                  /* (accessor 0x00376700) */
    short pos[2];
    u8 flag;

    func_00376450();
    switch (ES_PHASE) {
    case 3:
        g_004169A0[ES_PAGE]();
        if (ES_REQUESTED != ES_PAGE)
            ES_PHASE = 1;
        break;
    case 2:
        if (--ES_TIMER < 0) {
            if (ES_REQUESTED == ES_PAGE) {
                ES_PHASE = 3;
            } else if (ES_REQUESTED == 0x0C) {        /* leave the editor */
                ES_PREVIOUS = ES_PAGE;
                ES_PAGE = ES_REQUESTED;
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
            } else {
                func_0037D2C0();
                ES_PREVIOUS = ES_PAGE;
                ES_PAGE = ES_REQUESTED;
                ES_PHASE = 0;
                func_0037CCA0();
                func_003D8DF0();
            }
        }
        break;
    case 1:
        func_003D93F0();
        break;
    case 0:
        func_0037CCA0();
        func_003D8DF0();
        break;
    }

    if (ES_PAGE == 0x0B) {
        if (list[2] != 0) {
            u8 *rec = es + 0xBC + list[0] * 0x38;

            if (rec[0] == 0) {
                func_0037BED0();
                func_003774E0(2);
                ES_SHOWN = 0;
            } else {
                show_record(rec);
                func_003774E0(2);
                ES_SHOWN = 1;
            }
            list[2] = 0;
        }
    } else if (ES_PAGE == 10) {
        if ((u32)(ES_PREVIOUS - 1) < 2 && *(int *)(p10 + 4) != 0) {
            show_record(ES_RECORD);
            ES_SHOWN = 1;
            *(int *)(p10 + 4) = 0;
        }
    } else if (ES_PAGE == 1) {
        if (*(int *)(p1 + 0xC) != 0) {
            show_record(ES_RECORD);
            ES_SHOWN = 1;
            *(int *)(p1 + 0xC) = 0;
        }
    } else if (ES_PAGE == 2 && *(int *)(p2 + 8) != 0) {
        show_record(ES_RECORD);
        ES_SHOWN = 1;
        *(int *)(p2 + 8) = 0;
    }
    func_001AE550(1.0f, &s_007B9E40, pos, &flag, 1);
    *(float *)(g_00574DE0[0] + 0x40) = (float)(int)pos[0];
    *(float *)(g_00574DE0[0] + 0x44) = (float)(int)pos[1];
    if (ES_SHOWN != 0)
        func_001784E0(dt);
    return 1;
}

/* 0x0037D9E0, 0x30 bytes, matching. Scene 0x14 step. */
void func_0037D9E0(void)
{
    if (*(int *)(func_003766C0() + 0xB98) != 0)
        func_00179320();
}

/* 0x0037DA10, 0x54 bytes, matching. Scene 0x14 draw: the editor's screen, then the model. */
void func_0037DA10(void)
{
    u8 *es = func_003766C0();

    func_00278A20();
    func_003F8C00();
    func_003D8230();
    if (*(int *)(es + 0xB98) != 0) {
        g_0045D2C0_SET(g_005B4BC0[0]);
        func_001796D0();
    }
}
