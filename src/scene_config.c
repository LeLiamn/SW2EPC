/*
 * scene_config.c - scene 0x0C of the scene table: the options menu (original source file:
 * StateConfig.c, whose name is referenced by the enter function).
 *
 * Decompiled from SLES_546.24 with Ghidra (R5900) and checked against the machine code; not
 * verified by compiling with the original compiler. Unknown functions and globals keep neutral
 * names (func_/g_ + address).
 */

typedef unsigned char u8;
typedef unsigned int u32;

#include "sw2e_draw.h"

/* Flag bytes of the live settings (bitfields, first field = lowest bit). */
typedef struct {             /* 0x00669DB0 */
    u8 unknown_0 : 1;
    u8 mode : 3;             /* display mode 0..7 */
    u8 off_11 : 1;           /* set: option 1 of page 5 is off */
    u8 on_12 : 1;            /* set: option 2 is on */
    u8 option_13 : 2;        /* 0: option 3 on, 1: off */
} DisplayFlags;

typedef struct {             /* 0x00669DB1 */
    u8 unknown_0 : 2;
    u8 output : 2;           /* sound output mode 0..3 */
    u8 option : 1;
    u8 unknown_5 : 3;
} SoundFlags;

typedef struct {             /* +0x11 of each pad's settings */
    u8 unknown_0 : 1;
    u8 off_20 : 1;           /* set: option 0 of page 9 is off (vibration?) */
    u8 on_21 : 1;
    u8 off_22 : 1;
    u8 unknown_4 : 4;
} PadFlags;

/* The scene manager (see main.c), used here for the transition when the menu closes. */
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

/* Globals of the options scene (0x00731140 .. 0x0073123F). */
/* Globals 0x0043C32C-0x0043C6D4: one object in the original (not reached through $gp). */
extern struct {
    const char *g_0043C32C;    /* "The abilities and experience of all officers will be reset to default levels. Proceed?" */
    const char *g_0043C330;    /* "All abilities have been reset to default levels." */
    const char *g_0043C334;    /* "Interim data has been voided." */
    const char *g_0043C338;    /* "There is no interim data." */
    const char *g_0043C33C;    /* "Void interim data?" */
    char pad_0[0x268];
    const char *g_0043C5A8;   /* "Select  Back  OK" */
    char pad_1[0x6C];
    const char *g_0043C618;   /* "Default  Adjust  Back" */
    const char *g_0043C61C;   /* "Default  Select  Back  OK" */
    const char *g_0043C620;   /* "Select  Back  Change" */
    char pad_2[0xA0];
    const char *g_0043C6C4;   /* "Select  Cancel  OK" */
    const char *g_0043C6C8;   /* "Select  Change  Cancel" */
    const char *g_0043C6CC;   /* "Select  Change  Cancel  Play" */
    const char *g_0043C6D0;   /* "Back  Next" */
} s_0043C32C;
#define g_0043C32C (s_0043C32C.g_0043C32C)
#define g_0043C330 (s_0043C32C.g_0043C330)
#define g_0043C334 (s_0043C32C.g_0043C334)
#define g_0043C338 (s_0043C32C.g_0043C338)
#define g_0043C33C (s_0043C32C.g_0043C33C)
#define g_0043C5A8 (s_0043C32C.g_0043C5A8)
#define g_0043C618 (s_0043C32C.g_0043C618)
#define g_0043C61C (s_0043C32C.g_0043C61C)
#define g_0043C620 (s_0043C32C.g_0043C620)
#define g_0043C6C4 (s_0043C32C.g_0043C6C4)
#define g_0043C6C8 (s_0043C32C.g_0043C6C8)
#define g_0043C6CC (s_0043C32C.g_0043C6CC)
#define g_0043C6D0 (s_0043C32C.g_0043C6D0)

/* 0x00500700: the controllers' state, 0x88 bytes per controller. */
typedef struct {
    u8 unknown_00[0x4C];
    unsigned short pressed;  /* +0x4C buttons pressed this frame */
    unsigned short held;     /* +0x4E pressed or repeating */
    u8 unknown_50[0x14];
    u8 ready;                /* +0x64 bit 0 (bit 3: vibration off?) */
    u8 connected;            /* +0x65 bit 0 */
    u8 unknown_66[0x22];
} PadState;

extern PadState g_00500700[2];
#define g_0050074C (g_00500700[0].pressed)
#define g_0050074E (g_00500700[0].held)
#define g_00500764 (g_00500700[0].ready)
#define g_00500765 (g_00500700[0].connected)
#define g_005007D4 (g_00500700[1].pressed)
#define g_005007D6 (g_00500700[1].held)
#define g_005007EC (g_00500700[1].ready)
#define g_005007ED (g_00500700[1].connected)

/* 0x00669D60: the game's system settings (saved with the system data?). The code reaches its parts
 * from this base: the two pads' settings at +0x2C, display and sound flags at +0x50... */
typedef struct {             /* 0x12 bytes per pad */
    u8 map[0x10];            /* button map: one byte per action (offsets in g_0040CC20) */
    u8 extra;                /* pad 0's byte: copied to/from DisplaySettings.value_14 */
    PadFlags flags;
} PadConfig;

extern struct {
    u8 unknown_00[0x2C];
    PadConfig pads[2];       /* +0x2C (0x00669D8C) */
    DisplayFlags display;    /* +0x50 (0x00669DB0) */
    SoundFlags sound;        /* +0x51 */
    u8 volume[3];            /* +0x52..0x54 */
    u8 offset_x, offset_y;   /* +0x55, +0x56: screen offset (signed) */
} g_00669D60;
#define g_00669D8C (g_00669D60.pads)
#define g_00669D9C (g_00669D60.pads[0].extra)
#define g_00669DB0 (g_00669D60.display)
#define g_00669DB1 (g_00669D60.sound)
#define g_00669DB2 (g_00669D60.volume[0])
#define g_00669DB3 (g_00669D60.volume[1])
#define g_00669DB4 (g_00669D60.volume[2])
#define g_00669DB5 (g_00669D60.offset_x)
#define g_00669DB6 (g_00669D60.offset_y)

/* 0x0068F3E0: the message boxes' object (the code indexes the boxes from this base). Two boxes of
 * 0x128 bytes at +0x40D3: +0 state (non-zero while open), +1 the answer (4 = yes). */
typedef struct {
    u8 state;
    u8 answer;
    u8 unknown_2[0x126];
} MessageBox;
extern struct {
    u8 unknown_0[0x40D3];
    MessageBox box[2];       /* 0x006934B3, 0x006935DB */
    u8 unknown_4323[0x25B];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor -1 */
} s_0068F3E0;
#define g_006934B3 (s_0068F3E0.box[0].state)
#define g_006935DB (s_0068F3E0.box[1].state)
#define g_0069395E (s_0068F3E0.g_0069395E)
/* Box `b`'s state and answer, as the code reads them (an index from the object's base). */
#define box_state(b) (((u8 *)&s_0068F3E0)[(b) * 0x128 + 0x40D3])
#define box_answer(b) (((u8 *)&s_0068F3E0)[(b) * 0x128 + 0x40D4])

typedef struct {             /* 0x00731140, edited by pages 5 and 8 */
    int x, y;                /* +0x00 screen offset */
    int saved_x, saved_y;    /* +0x08 offset when the page opened */
    u8 mode;                 /* +0x10 0..7 */
    u8 option_11, option_12, option_13;
    u8 value_14;             /* +0x14 copy of 0x669D9C */
} DisplaySettings;
typedef struct {             /* 0x00731158 (one pad at a time), edited by pages 9 and 10 */
    u32 slots[8];            /* +0x00 button map */
    u8 option_20, option_21, option_22;
} PadSettings;

/* 0x00731140: the options menu's state (one object: the code reaches the settings copies as
 * members of it, e.g. the sound settings as base + 0x3C). */
extern struct {
    DisplaySettings display;     /* +0x00 copy edited by pages 5 and 8 */
    PadSettings pad;             /* +0x18 copy edited by pages 9 and 10 */
    u8 sound[8];                 /* +0x3C copy edited by page 7 */
    u8 unknown_44[0x6C];         /* +0x44 (0x00731184: data block given to func_002D0DC0) */
    int g_007311F0;   /* current page of the menu (0..10) */
    int g_007311F4;            /* page to open after closing */
    int g_007311F8;   /* phase: 0 opening, 1 in use, 2 closing, 3 leaving */
    char pad_3[0x4];
    int g_00731200;   /* page 10 mode (0 or 1) */
    char pad_4[0x4];
    int g_00731208;
    int g_0073120C;   /* sub-mode of page 3 (2 or 3) */
    char pad_5[0x4];
    u32 g_00731214;   /* the menu's window / layout handle */
    u8 g_00731218;
    u8 g_00731219;    /* page 0 cursor */
    u8 g_0073121A;    /* page 1 cursor */
    char g_0073121B;  /* page 5 cursor */
    char g_0073121C;  /* page 9 cursor */
    u8 g_0073121D;    /* page 10 cursor */
    u8 g_0073121E;
    u8 g_0073121F;
    char pad_6[0x3];
    u8 g_00731223;
    u8 g_00731224;
    u8 g_00731225;    /* cursor shared by pages 3, 7 and 10 */
    char pad_7[0x2];
    int g_00731228;   /* result of the page drawing: 0 when the page is idle */
    int g_0073122C;
    char pad_8[0xC];
    int g_0073123C;   /* value saved at enter, restored at leave */
} s_00731140;
#define g_00731140 ((u8 *)&s_00731140.display)
#define g_00731158 ((u8 *)&s_00731140.pad)
#define g_0073117C (s_00731140.sound)
#define g_00731184 (s_00731140.unknown_44)
#define g_00731144 (s_00731140.display.y)
#define g_00731148 (s_00731140.display.saved_x)
#define g_0073114C (s_00731140.display.saved_y)
#define g_00731150 (s_00731140.display.mode)
#define g_00731151 (s_00731140.display.option_11)
#define g_00731153 (s_00731140.display.option_13)
#define g_00731178 (s_00731140.pad.option_20)
#define g_00731179 (s_00731140.pad.option_21)
#define g_0073117A (s_00731140.pad.option_22)
#define g_007311F0 (s_00731140.g_007311F0)
#define g_007311F4 (s_00731140.g_007311F4)
#define g_007311F8 (s_00731140.g_007311F8)
#define g_00731200 (s_00731140.g_00731200)
#define g_00731208 (s_00731140.g_00731208)
#define g_0073120C (s_00731140.g_0073120C)
#define g_00731214 (s_00731140.g_00731214)
#define g_00731218 (s_00731140.g_00731218)
#define g_00731219 (s_00731140.g_00731219)
#define g_0073121A (s_00731140.g_0073121A)
#define g_0073121B (s_00731140.g_0073121B)
#define g_0073121C (s_00731140.g_0073121C)
#define g_0073121D (s_00731140.g_0073121D)
#define g_0073121E (s_00731140.g_0073121E)
#define g_0073121F (s_00731140.g_0073121F)
#define g_00731223 (s_00731140.g_00731223)
#define g_00731224 (s_00731140.g_00731224)
#define g_00731225 (s_00731140.g_00731225)
#define g_00731228 (s_00731140.g_00731228)
#define g_0073122C (s_00731140.g_0073122C)
#define g_0073123C (s_00731140.g_0073123C)

/* Globals 0x00799A68-0x00799A6C: one object in the original (not reached through $gp). */
extern struct {
    u32 g_00799A68;
    char size_unknown[5];   /* the whole object is larger (not reached through $gp) */
} s_00799A68;
#define g_00799A68 (s_00799A68.g_00799A68)


/* 0x0069395E: a byte checked before leaving (0 or 0xFF = nothing pending). */

/* Button help lines shown at the bottom of each page (European version, English). In the strings,
 * 0xF0 followed by a letter inserts a button icon. */

u32 func_001026D0(int a, int b, int c, int d, int e, int f, const void *g, int h);
void func_00102960(int value);
void func_00102EC0(u32 handle);
int func_001037F0(int value);
void func_00105EB0(u32 a, int b);
u32 func_00105E10(void);
void func_00105F70(u32 a);
void func_0017E010(int value);
int func_0017DDA0(void);
void func_001A2040(void);
void func_001A7DC0(const char *text, int alpha, int b);
void func_001B8F60(int a, int b, int c);
void func_001E3D50(void);
void func_001E3D90(void);
void func_001E4030(void);
void func_001E4080(void);
void func_001E44C0(void);
void func_001E46E0(void);
void func_001E4BF0(void);
void func_001E4E70(void);
void func_001E5060(void);
void func_001E51C0(void);
void func_001E5750(void);
void func_001E5EF0(void);
void func_00278CF0(void);
void func_002B3CF0(int value);
void func_002B4BE0(u32 handle, int page, int a, int b, int c, int d, int e, int f, int p8);
int func_002B6450(u32 handle, u8 cursor);
int func_002B7DA0(u32 handle, u8 cursor);
int func_002B7E30(u32 handle, u8 cursor);
int func_002B7EC0(u32 handle, void *data, char cursor);
int func_002B8790(u32 handle);
int func_002B89E0(u32 handle);
int func_002B8BC0(u32 handle, void *data, char cursor);
int func_002B9190(u32 handle, void *data, u8 cursor, u8 b, int c);
int func_002B9360(u32 handle, void *data, u8 cursor);
void func_002B9D70(u32 handle);
void func_002C59F0(void);
void func_002C5A30(void);
void func_002D0DC0(void *data);
void func_002DA2C0(void);
void func_002DAE50(void);
void func_00375D60(void);
void func_00376450(void);
void func_003F8B30(int value);
void func_003F8B80(void);
void func_003F8BB0(void);

/* ---- Helpers and page 0 (main options page) ------------------------------------------------ */

/* Controller state kept by the pad code (0x00500740...). */

/* Game button bits as used by the menus (meaning deduced from how page 0 reacts to them). */
#define BTN_CANCEL 0x0010
#define BTN_OK     0x0040
#define BTN_UP     0x1000
#define BTN_DOWN   0x4000

/* Controller 1, inlined in the original (macros). */
#define pad1_ready() ((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_0050074C : 0))
#define pad1_held() ((unsigned short)(pad1_ready() ? g_0050074E : 0))

#define SE_CURSOR 0x2CDC          /* sound effect played on cursor moves and choices */

/* Two message boxes (0x006934B4 + n * 0x128, n = 0 or 1); their first byte is non-zero while open,
 * the byte at +1 (0x006934B4 + n * 0x128) holds the answer (4 = yes?). */

extern u8 g_00429030[2][0x1E];
extern u8 g_004290F8[];          /* layout data of the options menu window */           /* lookup tables used by func_001E6670 */

/* Dialog texts (pointers to English strings). */

void func_001204B0(char *dst, const char *src);
void func_0017DF10(void);
void func_0017E110(u8 value);
void func_001AE9F0(int kind, const char *text, ...);
void func_001AFC50(int kind);
static void func_001E3300(void *data);
void func_001E33D0(int value, void *data);
void func_001E3500(void *data);
void func_0023A480(int value);
void func_0023A4F0(int value);
void func_0023AA40(void);
void func_0023AB70(u8 value);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_0023B530(u8 value);
void func_0023C050(u8 value);
void func_002B9CC0(int page);
int func_002EFBB0(void);
void func_002EFB40(void);
void func_003A32C0(void);

/* 0x001E3D00, 0x4C bytes, matching. Apply the four settings stored at 0x0073117C. */
void func_001E3D00(void)
{
    u8 *sound = g_0073117C;

    func_001E3500(sound);
    func_0023C050(sound[0]);
    func_0017E110(sound[1]);
    func_0023B530(sound[2]);
    func_0023AB70(sound[3]);
}

/* 0x001E3D50, 0x1C bytes, matching. */
void func_001E3D50(void)
{
    func_0023A4F0(0x44);
}

/* 0x001E3D70, 0x1C bytes, matching. */
void func_001E3D70(void)
{
    func_0023A480(0x44);
}

/* 0x001E3D90, 0x1C bytes, matching. */
void func_001E3D90(void)
{
    func_0023AA40();
}

/* 0x001E3DB0, 0x278 bytes. Start closing the current page to open `page` (0xE = leave the menu). */
void func_001E3DB0(int page)
{
    g_007311F8 = 2;
    switch (page) {
    case 0:
        func_002B3CF0(1);
        break;
    case 1:
        if (g_007311F0 < page)
            g_0073121A = 0;
        func_002B3CF0(2);
        break;
    case 2:
        if (g_007311F0 < page) {
            g_0073121E = 0;
            g_0073121F = 0;
            g_00731223 = 0;
            func_002B3CF0(0x0B);
            func_002B3CF0(0x1A);
            func_002B3CF0(0x1B);
            func_002B3CF0(0x1D);
        }
        func_002B3CF0(9);
        func_002B3CF0(0x18);
        break;
    case 3:
        /* The original passes the value left in the argument register by "phase = 2" above. */
        func_002B3CF0(2);
        break;
    case 5:
        if (g_007311F0 < page) {
            g_0073121B = 0;
            func_001E3300(g_00731140);
        }
        func_002B3CF0(8);
        break;
    case 6:
        func_002B3CF0(0x0D);
        break;
    case 9:
        if (g_007311F0 < page) {
            g_0073121C = 0;
            func_001E33D0(g_00731208, g_00731158);
            func_002B3CF0(0x10);
        }
        if (g_007311F0 == 6) {
            func_002B3CF0(0x14);
            g_0073122C = 0;
            g_00731218 = 0;
            func_002B3CF0(g_00731208 + 0x0E);
        }
        break;
    case 10:
        g_0073121D = 0;
        func_002B3CF0(0x11);
        func_002B3CF0(0x18);
        func_002B3CF0(0x1A);
        break;
    case 7:
        if (g_007311F0 < page)
            func_001E3500(g_0073117C);
        func_002B3CF0(0x12);
        break;
    case 13:
        g_00799A68 = 0;
        func_002B3CF0(5);
        g_00731224 = 0;
        g_00731223 = 0x28;
        break;
    case 14:
        func_001B8F60(0, 6, 8);
        g_007311F8 = 3;
        break;
    }
    g_00731225 = 0;
    g_007311F4 = page;
    func_002B9CC0(page);
}

/* 0x001E4030, 0x44 bytes, matching. Closing finished: switch to the page chosen by func_001E3DB0. */
void func_001E4030(void)
{
    func_002C59F0();
    func_002C5A30();
    g_007311F0 = g_007311F4;
    g_007311F8 = 0;
    g_0073122C = 0;
}

/* 0x001E4080, 0x440 bytes. Page 0, the main options page: three entries, plus the message boxes
 * for "reset all officers' abilities" and "void interim data". */
void func_001E4080(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();
    int box = 5;                                   /* 5 = no message box open */
    int answer;
    char text[256];

    if (g_006934B3 != 0)
        box = 0;
    else if (g_006935DB != 0)
        box = 1;
    answer = (box == 5) ? 0 : box_answer(box);

    if (box == 0)
        return;
    if (box == 1) {                                /* a question box is open */
        if (answer == 4) {
            if (g_00731219 == 3) {
                func_002EFB40();
                func_001204B0(text, g_0043C334);   /* "Interim data has been voided." */
            }
            if (g_00731219 == 1) {
                func_003A32C0();
                func_001204B0(text, g_0043C330);   /* "All abilities have been reset..." */
            }
            func_001AE9F0(0, text, 1);
            func_001AFC50(0);
        }
    } else if (box == 1) {
        /* Unreachable: the original code tests box == 1 twice. */
        if (answer == 4) {
            func_001AE9F0(0, text);
            func_001AFC50(0);
        }
    } else if (pressed & BTN_OK) {
        if (g_00731219 == 3) {
            if (func_002EFBB0() != 0) {
                func_001204B0(text, g_0043C338);   /* "There is no interim data." */
                func_001AE9F0(0, text, 1);
                func_001AFC50(0);
            } else {
                func_001204B0(text, g_0043C33C);   /* "Void interim data?" */
                func_001AE9F0(1, text, 1);
                func_001AFC50(1);
            }
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else if (g_00731219 == 1) {
            func_001204B0(text, g_0043C32C);       /* "...will be reset to default levels. Proceed?" */
            func_001AE9F0(1, text, 1);
            func_001AFC50(1);
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E3DB0(g_00731219 + 1);         /* open the chosen page */
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0017DF10();
        func_001E3DB0(14);                          /* leave the options menu */
    } else if (held & BTN_UP) {
        if (g_00731219 > 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731219 = (u8)((g_00731219 + 2) % 3);
        } else if (pressed & BTN_UP) {             /* wrap around only on a fresh press */
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731219 = 2;
        }
    } else if (held & BTN_DOWN) {
        if (g_00731219 < 2) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731219 = (u8)((g_00731219 + 1) % 3);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731219 = 0;
        }
    }
}

/* ---- Pages 1, 3, 6 and 8 ----------------------------------------------------------------------- */

/* Second controller (0x005007C8...), read by page 6. */

#define BTN_RESET  0x0800         /* page 8: back to default position */
#define BTN_RIGHT  0x2000
#define BTN_LEFT   0x8000

/* Page 8 keeps the screen offset x (-24..24) in the first word of g_00731140, and y here. */

void func_00100ED0(int *x, int *y);
void func_001E3C30(void);
void func_001E3CD0(void);
void func_002D8060(int value);
void func_002D8160(void);
int func_002DA090(void);
int func_002DAC30(void);
void func_002DBAA0(void);
void func_002DBAB0(void);

/* Inlined in the original: a macro. */
#define pad2_ready() ((g_005007EC & 1) ? (g_005007ED & 1) == 1 : 0)
#define pad2_pressed() ((unsigned short)(pad2_ready() ? g_005007D4 : 0))
#define pad2_held() ((unsigned short)(pad2_ready() ? g_005007D6 : 0))

/* 0x001E44C0, 0x220 bytes, matching. Page 1: a three-entry sub-menu opening pages 5, 6 and 7. */
void func_001E44C0(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();

    if (pressed & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(g_0073121A + 5);
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(0);
    } else if (held & BTN_UP) {
        if (g_0073121A > 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121A = (u8)((g_0073121A + 2) % 3);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121A = 2;
        }
    } else if (held & BTN_DOWN) {
        if (g_0073121A < 2) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121A = (u8)((g_0073121A + 1) % 3);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121A = 0;
        }
    }
}

/* 0x001E4BF0, 0x280 bytes, matching. Page 3: save or load the settings (two choices, then an operation
 * running in mode 2 or 3 until it reports 1 = done or 2 = cancelled). */
void func_001E4BF0(void)
{
    int pressed = pad1_pressed();
    int r;

    if (g_0073120C == 2) {
        r = func_002DAC30();
        if (r == 1) {
            func_002D8160();
            g_0073120C = 1;
        } else if (r == 2) {
            func_002D8160();
            g_0073120C = 1;
        }
        func_001037F0(0);
    } else if (g_0073120C == 3) {
        r = func_002DA090();
        if (r == 1) {
            func_002D8160();
            func_001E3C30();                    /* apply what was loaded? */
            g_0073120C = 1;
        } else if (r == 2) {
            func_002D8160();
            g_0073120C = 1;
        }
        func_001037F0(0);
    } else if (pressed & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        if (g_00731225 == 0) {
            func_002DBAA0();
            func_002D8060(0);
            g_0073120C = 2;
        } else {
            func_002DBAB0();
            func_002D8060(1);
            g_0073120C = 3;
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(0);
    } else if (pressed & BTN_UP) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731225 = (u8)((g_00731225 + 1) % 2);
    } else if (pressed & BTN_DOWN) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731225 = (u8)((g_00731225 + 1) % 2);
    }
}

/* 0x001E4E70, 0x1F0 bytes, matching. Page 8: adjust the screen position (offsets clamped to -24..24). */
void func_001E4E70(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();
    DisplaySettings *d = &s_00731140.display;

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(5);
    } else if (pressed & BTN_RESET) {
        func_001E3CD0();
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
    } else if (held & BTN_LEFT) {
        d->x = d->x - 1 < -0x18 ? -0x18 : d->x - 1;
        func_00100ED0(&d->x, &d->y);
    } else if (held & BTN_RIGHT) {
        d->x = d->x + 1 < 0x18 ? d->x + 1 : 0x18;
        func_00100ED0(&d->x, &d->y);
    } else if (held & BTN_UP) {
        d->y = d->y - 1 < -0x18 ? -0x18 : d->y - 1;
        func_00100ED0(&d->x, &d->y);
    } else if (held & BTN_DOWN) {
        d->y = d->y + 1 < 0x18 ? d->y + 1 : 0x18;
        func_00100ED0(&d->x, &d->y);
    }
}

/* 0x001E5060, 0x154 bytes, matching. Page 6: press OK on controller 1 or 2; remembers which one, then
 * opens page 9. */
void func_001E5060(void)
{
    int pad1 = pad1_pressed();
    int pad2 = pad2_pressed();

    if (pad1 & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731208 = 0;
        func_001E3DB0(9);
    } else if (pad2 & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731208 = 1;
        func_001E3DB0(9);
    } else if (pad1 & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(1);
    }
}

/* ---- Page 5 ------------------------------------------------------------------------------------ */

/* The settings edited by page 5 live in g_00731140: +0 / +4 screen offset being edited, +8 / +0xC
 * screen offset to restore on cancel, then option bytes. */

int func_001E36D0(void *settings);
void func_001E3560(void *settings);
void func_001E3CA0(void);

/* Turn an On/Off option on (Right) or off (Left), with the cursor sound only when it changes. */
static void toggle_option(u8 *option, int on)
{
    if (on && *option == 0) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        *option = 1;
    } else if (!on && *option != 0) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        *option = 0;
    }
}

/* 0x001E46E0, 0x510 bytes. Page 5: settings with five entries: three On/Off options (0, 1, 2),
 * "adjust screen" (3, opens page 8) and "OK" (4, keeps the settings). Cancel restores them and
 * waits 16 frames before going back, unless nothing had changed. */
void func_001E46E0(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();

    if (g_0073122C != 0) {                          /* waiting after a cancel */
        if (++g_00731218 > 0x0F) {
            func_001E3DB0(1);
            g_00731218 = 0;
            g_0073122C = 0;
        }
        return;
    }

    if (pressed & BTN_OK) {
        if (g_0073121B == 4) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E3DB0(1);
            func_001E3560(g_00731140);              /* keep the new settings */
        } else if (g_0073121B == 3) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E3DB0(8);
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731218 = (func_001E36D0(g_00731140) == 0) ? 0x0F : 0;
        g_0073122C = 1;
        func_001E3CA0();
        g_00669DB6 = (u8)g_0073114C;
        g_00669DB5 = (u8)g_00731148;
        func_00100ED0(&g_00731148, &g_0073114C);
    } else if (held & BTN_UP) {
        if (g_0073121B != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121B = (char)((g_0073121B + 4) % 5);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121B = 4;
        }
    } else if (held & BTN_DOWN) {
        if (g_0073121B < 4) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121B = (char)((g_0073121B + 1) % 5);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121B = 0;
        }
    } else if ((held & (BTN_LEFT | BTN_RIGHT)) && g_0073121B != 4 && g_0073121B != 3) {
        int on = !(held & BTN_LEFT);                /* Left wins when both are held */
        switch (g_0073121B) {
        case 2: toggle_option(&g_00731153, on); break;
        case 1: toggle_option(&g_00731151, on); break;
        case 0:                                     /* the original counts up/down here */
            if (on && g_00731150 == 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731150++;
            } else if (!on && g_00731150 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731150--;
            }
            break;
        }
    }
}

/* ---- Page 9 ------------------------------------------------------------------------------------ */


int func_001E39F0(int pad, void *settings);
void func_001E37E0(int pad, void *settings);

/* Same as toggle_option, but "off" requires the value to be exactly 1 (as in the original). */
static void switch_option(u8 *option, int on)
{
    if (on && *option == 0) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        *option = 1;
    } else if (!on && *option == 1) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        *option = 0;
    }
}

/* 0x001E51C0, 0x590 bytes. Page 9: settings of the controller chosen on page 6 (read from that
 * controller): three On/Off options (0, 1, 2), button set-up (3, opens page 10) and "OK" (4).
 * OK and Cancel both wait a few frames, then go back to page 6. */
void func_001E51C0(void)
{
    int pressed, held;

    if (g_0073122C != 0) {                          /* waiting before leaving */
        if (++g_00731218 > 0x0F) {
            func_001E3DB0(6);
            g_00731208 = 0;
            g_0073122C = 0;
        }
        return;
    }

    if (g_00731208 == 0) {
        pressed = pad1_pressed();
        held = pad1_held();
    } else if (g_00731208 == 1) {
        pressed = pad2_pressed();
        held = pad2_held();
    } else {
        return;
    }

    if (pressed & BTN_OK) {
        if (g_0073121C == 4) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E37E0(g_00731208, g_00731158);   /* keep the new settings */
            g_0073122C = 1;
            g_00731218 = 10;
        } else if (g_0073121C == 3) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E3DB0(10);
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731218 = (func_001E39F0(g_00731208, g_00731158) == 0) ? 10 : 0;
        g_0073122C = 1;
        func_001E33D0(g_00731208, g_00731158);       /* restore the saved settings */
    } else if (held & BTN_UP) {
        if (g_0073121C != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121C = (char)((g_0073121C + 4) % 5);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121C = 4;
        }
    } else if (held & BTN_DOWN) {
        if (g_0073121C < 4) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121C = (char)((g_0073121C + 1) % 5);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121C = 0;
        }
    } else if (held & (BTN_LEFT | BTN_RIGHT)) {
        int on = !(held & BTN_LEFT);                /* Left wins when both are held */
        if (g_0073121C == 2) switch_option(&g_00731178, on);
        if (g_0073121C == 1) switch_option(&g_0073117A, on);
        if (g_0073121C == 0) switch_option(&g_00731179, on);
    }
}

/* ---- Page 10 ----------------------------------------------------------------------------------- */

void func_001A2610(int pad);

/* 0x001E5750, 0x7A0 bytes. Page 10: button set-up of the controller chosen on page 6. The settings
 * hold 8 words (one action per slot). Cursor g_0073121D: entries 0-1 in the left column, 2-7 (the
 * eight slots' list?) in the right one. In mode 0 the player picks a slot; OK enters mode 1, where
 * g_00731225 picks the value to give it, and OK swaps it with the slot that had that value.
 * Reset (BTN_RESET) restores the defaults. Up/Down wrap only on a fresh press. */
void func_001E5750(void)
{
    u32 *slots = (u32 *)g_00731158;
    int pressed, held;

    if (g_00731208 == 0) {
        pressed = pad1_pressed();
        held = pad1_held();
    } else if (g_00731208 == 1) {
        pressed = pad2_pressed();
        held = pad2_held();
    } else {
        return;
    }

    if (pressed & BTN_OK) {
        if (g_00731200 == 1) {                      /* give the chosen value to the slot */
            int other;
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731200 = 0;
            for (other = 0; other < 8; other++)
                if (slots[other] == g_00731225)
                    break;
            slots[other] = slots[g_0073121D];       /* (other == 8 if not found, as in the original) */
            slots[g_0073121D] = g_00731225;
            func_002B3CF0(0x1A);
        } else if (g_00731200 == 0) {               /* start choosing a value for this slot */
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731200 = 1;
            g_00731225 = (u8)slots[g_0073121D];
            func_002B3CF0(0x19);
        }
    } else if (pressed & BTN_CANCEL) {
        if (g_00731200 == 1) {
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731200 = 0;
            func_002B3CF0(0x1A);
        } else if (g_00731200 == 0) {
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E3DB0(9);
        }
    } else if (pressed & BTN_RESET) {
        if (g_00731200 == 0) {
            func_001A2610(g_00731208);
            func_001E33D0(g_00731208, g_00731158);
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
    } else if (held & BTN_UP) {
        if (g_00731200 == 1) {
            if (g_00731225 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731225 = (g_00731225 + 7) & 7;
            } else if (pressed & BTN_UP) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731225 = 7;
            }
        } else if (g_00731200 == 0) {
            if (g_0073121D < 2) {                   /* left column: 0 <-> 1 */
                if (pressed & BTN_UP) {
                    func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                    g_0073121D = (g_0073121D + 1) & 1;
                }
            } else if (g_0073121D < 3) {
                if (pressed & BTN_UP) {
                    func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                    g_0073121D = 7;
                }
            } else {                                /* right column: 2..7 */
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_0073121D = (u8)((g_0073121D + 3) % 6 + 2);
            }
        }
    } else if (held & BTN_DOWN) {
        if (g_00731200 == 1) {
            if (g_00731225 < 7) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731225 = (g_00731225 + 1) & 7;
            } else if (pressed & BTN_DOWN) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00731225 = 0;
            }
        } else if (g_00731200 == 0) {
            if (g_0073121D < 2) {
                if (pressed & BTN_DOWN) {
                    func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                    g_0073121D = (g_0073121D + 1) & 1;
                }
            } else if (g_0073121D < 7) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_0073121D = (u8)((g_0073121D - 1) % 6 + 2);
            } else if (pressed & BTN_DOWN) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_0073121D = 2;
            }
        }
    } else if (held & BTN_LEFT) {                   /* right column -> left column */
        if (g_00731200 == 0 && g_0073121D >= 2) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121D = (g_0073121D < 4) ? 0 : 1;
        }
    } else if (held & BTN_RIGHT) {                  /* left column -> right column */
        if (g_00731200 == 0 && g_0073121D < 2) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073121D = g_0073121D + 3;
        }
    }
}

/* ---- Page 7 ------------------------------------------------------------------------------------ */

/* g_0073117C[0..5]: sound settings edited by page 7. */
#define SOUND_OUTPUT  g_0073117C[0]   /* 0..3 (output mode?), applied by func_0023C050 */
#define SOUND_VOL_1   g_0073117C[1]   /* 0..15, applied by func_0017E110 (music volume?) */
#define SOUND_VOL_2   g_0073117C[2]   /* 0..15, applied by func_0023B530 */
#define SOUND_VOL_3   g_0073117C[3]   /* 0..15, applied by func_0023AB70 */
#define SOUND_TOGGLE  g_0073117C[5]   /* byte 0x731181: On/Off */
#define SOUND_TRACK   g_0073117C[4]   /* byte 0x731180: track chosen in the sound test */
#define MENU_BGM      0x1C            /* music of the options menu */

int func_0017DCE0(void);              /* number of tracks in the sound test */
int func_0017DCF0(u8 index);          /* track id of a sound-test entry */
void func_0017E080(int track);        /* play a track */
int func_0017E0A0(void);              /* track playing now */
void func_001E3AD0(void *settings);
int func_001E3B90(void *settings);

static void play_menu_music(void)
{
    if (func_0017E0A0() != MENU_BGM) {
        func_0017DF10();
        func_0017E010(MENU_BGM);
    }
}

/* 0x001E5EF0, 0x774 bytes. Page 7: sound settings (controller 1). Entries: 0 output mode, 1-3
 * volumes, 4 On/Off, 5 sound test (OK plays the track), 6 "OK" (keep and go back to page 1).
 * Cancel restores the settings, waits a few frames and goes back to page 1. */
void func_001E5EF0(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();

    if (g_0073122C != 0) {                          /* waiting before leaving */
        if (++g_00731218 > 0x0F) {
            func_001E3DB0(1);
            g_00731218 = 0;
            g_0073122C = 0;
        }
        return;
    }

    if (pressed & BTN_OK) {
        if (g_00731225 == 6) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            play_menu_music();
            func_001E3DB0(1);
            func_001E3AD0(g_0073117C);              /* keep the new settings */
            func_001E3D90();
        } else if (g_00731225 == 5) {
            func_0017DCF0(SOUND_TRACK);             /* result unused (as in the original) */
            if (func_0017E0A0() != func_0017DCF0(SOUND_TRACK)) {
                func_0017DF10();
                func_0017E080(func_0017DCF0(SOUND_TRACK));
            }
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731218 = (func_001E3B90(g_0073117C) == 0) ? 0x0F : 0;
        g_0073122C = 1;
        func_001E3D00();
        play_menu_music();
        func_001E3D90();
    } else if (held & BTN_UP) {
        if (g_00731225 != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731225 = (u8)((g_00731225 + 6) % 7);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731225 = 6;
        }
    } else if (held & BTN_DOWN) {
        if (g_00731225 < 6) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731225 = (u8)((g_00731225 + 1) % 7);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00731225 = 0;
        }
    } else if (held & BTN_LEFT) {
        switch (g_00731225) {
        case 0:
            if (SOUND_OUTPUT != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023C050(--SOUND_OUTPUT);
            }
            break;
        case 1:
            if (SOUND_VOL_1 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0017E110(--SOUND_VOL_1);
            }
            break;
        case 2:
            if (SOUND_VOL_2 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023B530(--SOUND_VOL_2);
            }
            break;
        case 3:
            if (SOUND_VOL_3 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023AB70(--SOUND_VOL_3);
                func_001E3D70();
            }
            break;
        case 4:
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            SOUND_TOGGLE = (SOUND_TOGGLE == 0);
            break;
        case 5:                                     /* wraps only on a fresh press */
            if (SOUND_TRACK != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                SOUND_TRACK--;
            } else if (pressed & BTN_LEFT) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                SOUND_TRACK = (u8)(func_0017DCE0() - 1);
            }
            break;
        }
    } else if (held & BTN_RIGHT) {
        switch (g_00731225) {
        case 0:
            if (SOUND_OUTPUT < 3) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023C050(++SOUND_OUTPUT);
            }
            break;
        case 1:
            if (SOUND_VOL_1 < 0x0F) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0017E110(++SOUND_VOL_1);
            }
            break;
        case 2:
            if (SOUND_VOL_2 < 0x0F) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023B530(++SOUND_VOL_2);
            }
            break;
        case 3:
            if (SOUND_VOL_3 < 0x0F) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                func_0023AB70(++SOUND_VOL_3);
                func_001E3D70();
            }
            break;
        case 4:
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            SOUND_TOGGLE = (SOUND_TOGGLE == 0);
            break;
        case 5: {
            int count = func_0017DCE0();
            if (SOUND_TRACK < count - 1) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                SOUND_TRACK++;
            } else if (pressed & BTN_RIGHT) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                SOUND_TRACK = 0;
            }
            break;
        }
        }
    }
}

/* ---- Settings helpers ------------------------------------------------------------------------- */
/*
 * The game's live settings sit at 0x00669D8C (saved with the game's system data?):
 * - 0x669D8C + pad * 0x12: the button map of each pad (one byte per action, at the offsets of the
 *   table g_0040CC20), and at +0x11 (0x669D9D) three flag bits (bits 1, 2, 3) of that pad;
 * - 0x669D9C: one byte of display settings; 0x669DB0: display flags (bits 1-3 a mode 0..7, bits 4, 5
 *   and 6-7 three options); 0x669DB1: sound flags (bits 2-3 output mode, bit 4 an option);
 *   0x669DB2..DB4: three volumes; 0x669DB5/DB6: screen offset (signed).
 * The menu pages edit copies of them (the structs below) and write them back with "OK".
 */

/* Settings of each pad at 0x00669D8C: the button map (one byte per action, at the offsets of the
 * table g_0040CC20) and flags. */
extern int g_0040CC20[8];               /* offset of each button-map entry in a PadConfig */

void func_001036B0(int port, int on);
void func_0017E0C0(u8 volume, int b);

#define PAD_MAP(pad, i) (((u8 *)&g_00669D8C[pad])[g_0040CC20[i]])

/* 0x001E3300, 0xCC bytes, matching. Copies the live display settings into `out`. */
static void func_001E3300(void *out)
{
    DisplaySettings *d = out;

    d->mode = g_00669DB0.mode;
    if (g_00669DB0.off_11)
        d->option_11 = 0;
    else
        d->option_11 = 1;
    if (g_00669DB0.on_12)
        d->option_12 = 1;
    else
        d->option_12 = 0;
    if (g_00669DB0.option_13 == 0)
        d->option_13 = 1;
    else
        d->option_13 = 0;
    d->value_14 = g_00669D9C;
    d->saved_x = (signed char)g_00669DB5;
    d->saved_y = (signed char)g_00669DB6;
    d->x = (signed char)g_00669DB5;
    d->y = (signed char)g_00669DB6;
}

/* 0x001E33D0, 0x12C bytes, matching. Copies the live settings of pad `pad` (0 or 1) into `out`. */
void func_001E33D0(int pad, void *out)
{
    PadSettings *p = out;

    if (g_00669D8C[pad].flags.off_20)
        p->option_20 = 0;
    else
        p->option_20 = 1;
    if (g_00669D8C[pad].flags.on_21 == 0)
        p->option_21 = 0;
    else
        p->option_21 = 1;
    if (g_00669D8C[pad].flags.off_22)
        p->option_22 = 0;
    else
        p->option_22 = 1;
    p->slots[0] = PAD_MAP(pad, 0);
    p->slots[1] = PAD_MAP(pad, 1);
    p->slots[2] = PAD_MAP(pad, 2);
    p->slots[3] = PAD_MAP(pad, 3);
    p->slots[4] = PAD_MAP(pad, 4);
    p->slots[5] = PAD_MAP(pad, 5);
    p->slots[6] = PAD_MAP(pad, 6);
    p->slots[7] = PAD_MAP(pad, 7);
}

/* 0x001E3500, 0x58 bytes, matching. Copies the live sound settings into `out` (6 bytes, see page 7). */
void func_001E3500(void *out)
{
    u8 *s = out;

    s[0] = g_00669DB1.output;
    s[1] = g_00669DB2;
    s[2] = g_00669DB3;
    s[3] = g_00669DB4;
    s[4] = 0x2D;                                /* sound test: first track shown */
    s[5] = g_00669DB1.option;
}

/* 0x001E3560, 0x16C bytes, matching. Writes display settings back and applies the screen offset. */
void func_001E3560(void *in)
{
    DisplaySettings *d = in;

    g_00669DB0.mode = d->mode;
    if (d->option_11 == 0)
        g_00669DB0.off_11 = 1;
    else
        g_00669DB0.off_11 = 0;
    if (d->option_12 == 1)
        g_00669DB0.on_12 = 1;
    else
        g_00669DB0.on_12 = 0;
    if (d->option_13 == 0)
        g_00669DB0.option_13 = 1;
    else
        g_00669DB0.option_13 = 0;
    g_00669D9C = d->value_14;
    {
        int x = d->x;
        int y = d->y;
        g_00669DB5 = x;
        g_00669DB6 = y;
    }
    func_00100ED0(&d->x, &d->y);
}

/* 0x001E36D0, 0x10C bytes, matching. Non-zero when `in` differs from the live display settings (the screen
 * offset is not compared). */
int func_001E36D0(void *in)
{
    DisplaySettings *d = in;

    if (d->mode != g_00669DB0.mode)
        return 1;
    if (d->option_11 == 0) {
        if (g_00669DB0.off_11 == 0)
            return 1;
    } else if (g_00669DB0.off_11 != 0) {
        return 1;
    }
    if (d->option_12 == 1) {
        if (g_00669DB0.on_12 == 0)
            return 1;
    } else if (g_00669DB0.on_12 != 0) {
        return 1;
    }
    if (d->option_13 == 0) {
        if (g_00669DB0.option_13 != 1)
            return 1;
    } else if (g_00669DB0.option_13 != 0) {
        return 1;
    }
    return 0;
}

/* 0x001E37E0, 0x210 bytes. Writes the settings of pad `pad` back and applies them. */
void func_001E37E0(int pad, void *in)
{
    PadSettings *p = in;
    int off22;
    int on21;
    int off20;
    PadState *state;
    int vibration;
    PadFlags *flags;
    int port;                                   /* (unset unless pad is 0 or 1, as in the original) */

    vibration = 0;
    if (p->option_20 != 0)
        vibration = 1;
    off20 = p->option_20 == 0;
    on21 = p->option_21 != 0;
    off22 = p->option_22 == 0;
    if (pad == 0)
        port = 0;
    if (pad == 1)
        port = 1;

    flags = &g_00669D8C[pad].flags;
    flags->off_20 = off20 != 0;
    func_001036B0(port, vibration);             /* vibration on/off? */
    flags->on_21 = on21 != 0;
    flags->off_22 = off22 != 0;

    state = &g_00500700[port];
    if (((state->ready & 1) ? (state->connected & 1) == 1 : 0))
        state->ready = (state->ready & 0xF7) | ((off22 != 0) << 3);

    PAD_MAP(pad, 0) = (u8)p->slots[0];
    PAD_MAP(pad, 1) = (u8)p->slots[1];
    PAD_MAP(pad, 2) = (u8)p->slots[2];
    PAD_MAP(pad, 3) = (u8)p->slots[3];
    PAD_MAP(pad, 4) = (u8)p->slots[4];
    PAD_MAP(pad, 5) = (u8)p->slots[5];
    PAD_MAP(pad, 6) = (u8)p->slots[6];
    PAD_MAP(pad, 7) = (u8)p->slots[7];
}

/* 0x001E39F0, 0xDC bytes. Non-zero when `in` differs from the live settings of pad `pad`.
 * Note: option_21 is compared the opposite way to how func_001E33D0 reads it (bit 2 set gives
 * option_21 = 1 there, but counts as "same" here only when option_21 == 0). Kept as in the
 * original: page 9 therefore always sees the settings as changed when cancelling. */
int func_001E39F0(int pad, void *in)
{
    PadSettings *p = in;
    int a = p->option_20 == 0;
    int c = p->option_22 == 0;
    int b = p->option_21 == 0;
    int i;

    if (a != (g_00669D8C[pad].flags.off_20 != 0))
        return 1;
    if (c != (g_00669D8C[pad].flags.off_22 != 0))
        return 1;
    if (b != (g_00669D8C[pad].flags.on_21 != 0))
        return 1;
    for (i = 0; i < 8; i++)
        if (g_00669D8C[pad].map[g_0040CC20[i]] != p->slots[i])
            return 1;
    return 0;
}

/* 0x001E3AD0, 0xB8 bytes, matching. Writes the sound settings back and applies them. */
void func_001E3AD0(void *in)
{
    u8 *s = in;

    g_00669DB1.output = s[0];
    g_00669DB2 = s[1];
    g_00669DB3 = s[2];
    g_00669DB4 = s[3];
    g_00669DB1.option = s[5];
    func_0023C050(s[0]);
    func_0017E0C0(s[1], 0);
    func_0023B530(s[2]);
    func_0023AB70(s[3]);
}

/* 0x001E3B90, 0x94 bytes, matching. Non-zero when `in` differs from the live sound settings. */
int func_001E3B90(void *in)
{
    u8 *s = in;

    if (s[0] != g_00669DB1.output)
        return 1;
    if (s[1] != g_00669DB2)
        return 1;
    if (s[2] != g_00669DB3)
        return 1;
    if (s[3] != g_00669DB4)
        return 1;
    return s[5] != g_00669DB1.option;
}

/* 0x001E3C30, 0x64 bytes, matching. Applies all live settings again (display, both pads, sound), by reading
 * them and writing them back. */
void func_001E3C30(void)
{
    DisplaySettings display;
    PadSettings pads[2];
    u8 sound[8];

    func_001E3300(&display);
    func_001E33D0(0, &pads[0]);
    func_001E33D0(1, &pads[1]);
    func_001E3500(sound);
    func_001E3560(&display);
    func_001E37E0(0, &pads[0]);
    func_001E37E0(1, &pads[1]);
    func_001E3AD0(sound);
}

/* 0x001E3CA0, 0x30 bytes, matching. Reloads the menu's display copy and applies its saved screen offset.
 * (The original keeps the copy's address in $v0 across the call: the compiler knows the static
 * helper leaves that register alone.) */
void func_001E3CA0(void)
{
    DisplaySettings *d = (DisplaySettings *)g_00731140;

    func_001E3300(d);
    func_00100ED0(&d->saved_x, &d->saved_y);
}

/* 0x001E3CD0, 0x2C bytes, matching. Centres the screen (offset 0, 0) in the menu's copy and applies it. */
void func_001E3CD0(void)
{
    DisplaySettings *d = (DisplaySettings *)g_00731140;

    d->x = 0;
    d->y = 0;
    func_00100ED0(&d->x, &d->y);
}

/* 0x001E6670, 0x1E8 bytes, matching. Look up a byte in one of the tables at 0x00429030 (selected by `table`,
 * row chosen by whether `flag` is 0); out-of-range indexes return the table's first byte. */
extern u8 g_00429070[2][6], g_00429080[2][6], g_00429090[2][9], g_004290A8[2][6];
extern u8 g_004290C0[2][8], g_004290D0[2][6];

u8 func_001E6670(int table, int flag, int index)
{
    u8 value = g_00429030[0][0];
    int row = 0;

    if (flag == 0)
        row = 1;
    if (flag < 0 && flag >= 2)      /* never true in the original code */
        return value;
    {
        switch (table) {
        case 0: if (index >= 0 && (unsigned)index < 6) value = g_00429070[row][index]; break;
        case 1: if (index >= 0 && (unsigned)index < 6) value = g_00429080[row][index]; break;
        case 2:
            if (index == 0x19)
                index = 8;
            if (index >= 0 && (unsigned)index < 9)
                value = g_00429090[row][index];
            break;
        case 3: if (index >= 0 && (unsigned)index < 6) value = g_004290A8[row][index]; break;
        case 4: if (index >= 0 && (unsigned)index < 8) value = g_004290C0[row][index]; break;
        case 5: if (index >= 0 && (unsigned)index < 6) value = g_004290D0[row][index]; break;
        default: if (index >= 0 && (unsigned)index < 0x1E) value = g_00429030[row][index]; break;
        }
    }
    return value;
}

/* 0x001E6860, 0xF4 bytes, matching. Enter: create the menu and reset its state. */
void func_001E6860(void)
{
    func_003F8B30(4);
    g_00731214 = func_001026D0(1, 0x3B, 0, 1, 0, 0, g_004290F8, 0x9D7);
    func_00102960(1);
    func_001E3D50();
    g_007311F0 = 0;
    g_007311F8 = 0;
    g_00731219 = 0;
    g_0073120C = 1;
    g_0073122C = 0;
    func_001A2040();
    func_002D0DC0(g_00731184);
    if (func_0017DDA0() == 0)
        func_0017E010(0x1C);
    func_002B3CF0(0);
    func_002C59F0();
    func_002C5A30();
    func_002B9D70(g_00731214);
    func_001B8F60(1, 6, 8);
    g_0073123C = func_001037F0(0);
}

/* 0x001E6960, 0x44 bytes, matching. Leave: destroy the menu and restore the saved value. */
void func_001E6960(void)
{
    func_00375D60();
    func_00102EC0(g_00731214);
    func_001E3D90();
    func_001037F0(g_0073123C);
    func_003F8B80();
}

/* 0x001E69B0, 0x200 bytes, matching. Update: run the current phase; always returns 1 (so step() runs). */
/* Message box 1 open (inlined in the original). */
static inline int box1_open(void)
{
    int open;

    if (g_0069395E == 0 || g_0069395E == 0xFF)
        open = 0;
    else
        open = 1;
    return open;
}

int func_001E69B0(float dt)
{
    func_00376450();
    switch (g_007311F8) {
    case 0:
        if (g_00731228 == 0)                   /* opening finished */
            g_007311F8 = 1;
        return 1;
    case 1:                                     /* in use: run the current page (below) */
        break;
    case 2:                                     /* closing */
        if (g_00731228 == 0)
            func_001E4030();
        return 1;
    case 3:                                     /* leaving */
        if (!box1_open()) {
            if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
                g_0045D894 = g_0045D898;        /* go to the requested scene */
                g_0045D898 = g_0045D8A0;
                g_0045D89C = 0x18;
            } else {
                g_0045D894 = g_0045D898;        /* go back to the scene we came from */
                g_0045D898 = g_0045D89C;
                g_0045D89C = g_0045D8A0;
            }
        }
        return 1;
    }
    switch (g_007311F0) {
    case 0: func_001E4080(); break;
    case 1: func_001E44C0(); break;
    case 3: func_001E4BF0(); break;
    case 5: func_001E46E0(); break;
    case 6: func_001E5060(); break;
    case 7: func_001E5EF0(); break;
    case 8: func_001E4E70(); break;
    case 9: func_001E51C0(); break;
    case 10: func_001E5750(); break;
    case 13: break;                             /* (no page 13: an empty case, as in the original) */
    }
    return 1;
}

/* 0x001E6BB0, 0x08 bytes, matching. Step: nothing to do. */
void func_001E6BB0(void)
{
}

/* 0x001E6BC0, 0x544 bytes. Draw: the current page, then its button help line. */
void func_001E6BC0(void)
{
    u32 v;

    if (g_007311F0 != 8)
        func_00278CF0();
    v = func_00105E10();
    func_00105EB0(v, 0);
    func_00105F70(v);
    if (g_007311F0 != 8)
        func_003F8BB0();
    func_002B4BE0(g_00731214, g_007311F0, 0x10, 0x0C, 0, 0xD8, 0x28, 0x80, ARG_UNKNOWN);

    switch (g_007311F0) {
    case 0: g_00731228 = func_002B6450(g_00731214, g_00731219); break;
    case 1: g_00731228 = func_002B7DA0(g_00731214, g_0073121A); break;
    case 3:
        g_00731228 = func_002B7E30(g_00731214, g_00731225);
        if (g_0073120C == 3)
            func_002DA2C0();
        else if (g_0073120C == 2)
            func_002DAE50();
        break;
    case 5: g_00731228 = func_002B7EC0(g_00731214, g_00731140, g_0073121B); break;
    case 6: g_00731228 = func_002B89E0(g_00731214); break;
    case 7: g_00731228 = func_002B9360(g_00731214, g_0073117C, g_00731225); break;
    case 8: g_00731228 = func_002B8790(g_00731214); break;
    case 9: g_00731228 = func_002B8BC0(g_00731214, g_00731158, g_0073121C); break;
    case 10:
        if (g_00731200 == 0)
            g_00731228 = func_002B9190(g_00731214, g_00731158, g_0073121D, 0, 0);
        else
            g_00731228 = func_002B9190(g_00731214, g_00731158, g_0073121D, g_00731225, 1);
        break;
    }

    switch (g_007311F0) {                        /* button help line at the bottom */
    case 0:
    case 1:
    case 3:
        func_001A7DC0(g_0043C5A8, 0x80, 2);
        break;
    case 5:
        if (g_0073121B == 4 || g_0073121B == 3)
            func_001A7DC0(g_0043C6C4, 0x80, 2);
        else if (g_0073121B == 2 || g_0073121B == 1 || g_0073121B == 0)
            func_001A7DC0(g_0043C6C8, 0x80, 2);
        break;
    case 6:
        func_001A7DC0(g_0043C6D0, 0x80, 2);
        break;
    case 7:
        if (g_00731225 <= 4)
            func_001A7DC0(g_0043C6C8, 0x80, 2);
        else if (g_00731225 == 5)
            func_001A7DC0(g_0043C6CC, 0x80, 2);
        else if (g_00731225 == 6)
            func_001A7DC0(g_0043C6C4, 0x80, 2);
        break;
    case 8:
        func_001A7DC0(g_0043C618, 0x80, 2);
        break;
    case 9:
        if (g_0073121C == 4 || g_0073121C == 3)
            func_001A7DC0(g_0043C6C4, 0x80, 2);
        else if (g_0073121C == 1 || g_0073121C == 0 || g_0073121C == 2)
            func_001A7DC0(g_0043C6C8, 0x80, 2);
        break;
    case 10:
        if (g_00731200 == 1)
            func_001A7DC0(g_0043C620, 0x80, 2);
        else if (g_00731200 == 0)
            func_001A7DC0(g_0043C61C, 0x80, 2);
        break;
    }
}
