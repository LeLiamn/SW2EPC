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

/* The scene manager (see main.c), used here for the transition when the menu closes. */
extern int g_0045D894;   /* previous state */
extern int g_0045D898;   /* current state */
extern int g_0045D89C;   /* state to return to */
extern int g_0045D8A0;   /* requested state (0x18 = none) */

/* Globals of the options scene (0x00731140 .. 0x0073123F). */
extern int g_007311F0;   /* current page of the menu (0..10) */
extern int g_007311F8;   /* phase: 0 opening, 1 in use, 2 closing, 3 leaving */
extern int g_00731200;   /* page 10 mode (0 or 1) */
extern int g_0073120C;   /* sub-mode of page 3 (2 or 3) */
extern u32 g_00731214;   /* the menu's window / layout handle */
extern u8 g_00731219;    /* page 0 cursor */
extern u8 g_0073121A;    /* page 1 cursor */
extern char g_0073121B;  /* page 5 cursor */
extern char g_0073121C;  /* page 9 cursor */
extern u8 g_0073121D;    /* page 10 cursor */
extern u8 g_00731225;    /* cursor shared by pages 3, 7 and 10 */
extern int g_00731228;   /* result of the page drawing: 0 when the page is idle */
extern int g_0073122C;
extern int g_0073123C;   /* value saved at enter, restored at leave */
extern u8 g_00731140[], g_00731158[], g_0073117C[], g_00731184[];

/* 0x0069395E: a byte checked before leaving (0 or 0xFF = nothing pending). */
extern char g_0069395E;

/* Button help lines shown at the bottom of each page (European version, English). In the strings,
 * 0xF0 followed by a letter inserts a button icon. */
extern const char *g_0043C5A8;   /* "Select  Back  OK" */
extern const char *g_0043C618;   /* "Default  Adjust  Back" */
extern const char *g_0043C61C;   /* "Default  Select  Back  OK" */
extern const char *g_0043C620;   /* "Select  Back  Change" */
extern const char *g_0043C6C4;   /* "Select  Cancel  OK" */
extern const char *g_0043C6C8;   /* "Select  Change  Cancel" */
extern const char *g_0043C6CC;   /* "Select  Change  Cancel  Play" */
extern const char *g_0043C6D0;   /* "Back  Next" */

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
void func_002B4BE0(u32 handle, int page, int a, int b, int c, int d, int e, int f);
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
extern u8 g_00500764;            /* bit 0: pad ready? */
extern u8 g_00500765;            /* bit 0: pad connected? */
extern unsigned short g_0050074C; /* buttons pressed this frame */
extern unsigned short g_0050074E; /* buttons pressed or repeating */

/* Game button bits as used by the menus (meaning deduced from how page 0 reacts to them). */
#define BTN_CANCEL 0x0010
#define BTN_OK     0x0040
#define BTN_UP     0x1000
#define BTN_DOWN   0x4000

#define SE_CURSOR 0x2CDC          /* sound effect played on cursor moves and choices */

/* Two message boxes (0x006934B4 + n * 0x128, n = 0 or 1); their first byte is non-zero while open,
 * the byte at +1 (0x006934B4 + n * 0x128) holds the answer (4 = yes?). */
extern char g_006934B3;
extern char g_006935DB;
extern char g_006934B4[];

extern int g_007311F4;            /* page to open after closing */
extern int g_00731208;
extern u8 g_00731218, g_0073121E, g_0073121F, g_00731223, g_00731224;
extern u32 g_00799A68;
extern u8 g_00429030[];           /* lookup tables used by func_001E6670 */

/* Dialog texts (pointers to English strings). */
extern const char *g_0043C32C;    /* "The abilities and experience of all officers will be reset to
                                     default levels. Proceed?" */
extern const char *g_0043C330;    /* "All abilities have been reset to default levels." */
extern const char *g_0043C334;    /* "Interim data has been voided." */
extern const char *g_0043C338;    /* "There is no interim data." */
extern const char *g_0043C33C;    /* "Void interim data?" */

void func_001204B0(char *dst, const char *src);
void func_0017DF10(void);
void func_0017E110(u8 value);
void func_001AE9F0(int kind, const char *text, ...);
void func_001AFC50(int kind);
void func_001E3300(void *data);
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

/* 0x001E3D00, 0x4C bytes. Apply the four settings stored at 0x0073117C. */
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
    case 7:
        if (g_007311F0 < page)
            func_001E3500(g_0073117C);
        func_002B3CF0(0x12);
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

/* 0x001E4030, 0x44 bytes. Closing finished: switch to the page chosen by func_001E3DB0. */
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
    unsigned short pressed, held;
    int box;
    char answer;
    char text[256];

    pressed = ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074C : 0;
    held = ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074E : 0;

    box = 5;                                       /* 5 = no message box open */
    if (g_006934B3 != 0)
        box = 0;
    else if (g_006935DB != 0)
        box = 1;
    answer = (box == 5) ? 0 : g_006934B4[box * 0x128];

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
            if (func_002EFBB0() == 0) {
                func_001204B0(text, g_0043C33C);   /* "Void interim data?" */
                func_001AE9F0(1, text, 1);
                func_001AFC50(1);
            } else {
                func_001204B0(text, g_0043C338);   /* "There is no interim data." */
                func_001AE9F0(0, text, 1);
                func_001AFC50(0);
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
        if (g_00731219 != 0) {
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
extern u8 g_005007EC;
extern u8 g_005007ED;
extern unsigned short g_005007D4;

#define BTN_RESET  0x0800         /* page 8: back to default position */
#define BTN_RIGHT  0x2000
#define BTN_LEFT   0x8000

/* Page 8 keeps the screen offset x (-24..24) in the first word of g_00731140, and y here. */
extern int g_00731144;

void func_00100ED0(int *x, int *y);
void func_001E3C30(void);
void func_001E3CD0(void);
void func_002D8060(int value);
void func_002D8160(void);
int func_002DA090(void);
int func_002DAC30(void);
void func_002DBAA0(void);
void func_002DBAB0(void);

static unsigned short pad1_pressed(void)
{
    return ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074C : 0;
}

static unsigned short pad1_held(void)
{
    return ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074E : 0;
}

/* 0x001E44C0, 0x220 bytes. Page 1: a three-entry sub-menu opening pages 5, 6 and 7. */
void func_001E44C0(void)
{
    unsigned short pressed = pad1_pressed();
    unsigned short held = pad1_held();

    if (pressed & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(g_0073121A + 5);
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(0);
    } else if (held & BTN_UP) {
        if (g_0073121A != 0) {
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

/* 0x001E4BF0, 0x280 bytes. Page 3: save or load the settings (two choices, then an operation
 * running in mode 2 or 3 until it reports 1 = done or 2 = cancelled). */
void func_001E4BF0(void)
{
    unsigned short pressed = pad1_pressed();
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
    } else if (pressed & (BTN_UP | BTN_DOWN)) {
        /* Up and down are two separate branches in the original, with the same effect. */
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_00731225 = (u8)((g_00731225 + 1) % 2);
    }
}

/* 0x001E4E70, 0x1F0 bytes. Page 8: adjust the screen position (offsets clamped to -24..24). */
void func_001E4E70(void)
{
    unsigned short pressed = pad1_pressed();
    unsigned short held = pad1_held();
    int *x = (int *)g_00731140;

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E3DB0(5);
    } else if (pressed & BTN_RESET) {
        func_001E3CD0();
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
    } else if (held & BTN_LEFT) {
        if (--*x < -0x18)
            *x = -0x18;
        func_00100ED0(x, &g_00731144);
    } else if (held & BTN_RIGHT) {
        if (++*x > 0x17)
            *x = 0x18;
        func_00100ED0(x, &g_00731144);
    } else if (held & BTN_UP) {
        if (--g_00731144 < -0x18)
            g_00731144 = -0x18;
        func_00100ED0(x, &g_00731144);
    } else if (held & BTN_DOWN) {
        if (++g_00731144 > 0x17)
            g_00731144 = 0x18;
        func_00100ED0(x, &g_00731144);
    }
}

/* 0x001E5060, 0x154 bytes. Page 6: press OK on controller 1 or 2; remembers which one, then
 * opens page 9. */
void func_001E5060(void)
{
    unsigned short pad1 = pad1_pressed();
    unsigned short pad2 = ((g_005007EC & 1) && (g_005007ED & 1) == 1) ? g_005007D4 : 0;

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
extern u8 g_00731150, g_00731151, g_00731153;   /* three On/Off options of page 5 */
extern int g_00731148, g_0073114C;               /* screen offset saved when the page opened */
extern u8 g_00669DB5, g_00669DB6;                /* screen offset used by the display code */

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
    unsigned short pressed = pad1_pressed();
    unsigned short held = pad1_held();

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

extern unsigned short g_005007D6;                /* controller 2: buttons pressed or repeating */
extern u8 g_00731178, g_00731179, g_0073117A;    /* three On/Off options of the chosen pad */

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
    unsigned short pressed, held;

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
        int ready = (g_005007EC & 1) && (g_005007ED & 1) == 1;
        pressed = ready ? g_005007D4 : 0;
        held = ready ? g_005007D6 : 0;
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
    unsigned short pressed, held;

    if (g_00731208 == 0) {
        pressed = pad1_pressed();
        held = pad1_held();
    } else if (g_00731208 == 1) {
        int ready = (g_005007EC & 1) && (g_005007ED & 1) == 1;
        pressed = ready ? g_005007D4 : 0;
        held = ready ? g_005007D6 : 0;
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
    unsigned short pressed = pad1_pressed();
    unsigned short held = pad1_held();

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

extern u8 g_00669D8C[];                 /* 2 x 0x12 bytes of pad settings */
extern u8 g_00669D9C, g_00669DB0, g_00669DB1, g_00669DB2, g_00669DB3, g_00669DB4;
extern int g_0040CC20[8];               /* offset of each button-map entry in a pad's settings */

void func_001036B0(int port, int on);
void func_0017E0C0(u8 volume, int b);

#define PAD_FLAGS(pad) g_00669D8C[(pad) * 0x12 + 0x11]

/* 0x001E3300, 0xCC bytes. Copies the live display settings into `out`. */
void func_001E3300(void *out)
{
    DisplaySettings *d = out;

    d->mode = (g_00669DB0 & 0x0F) >> 1;
    d->option_11 = (g_00669DB0 & 0x10) ? 0 : 1;
    d->option_12 = (g_00669DB0 & 0x20) ? 1 : 0;
    d->option_13 = (g_00669DB0 >> 6 == 0) ? 1 : 0;
    d->value_14 = g_00669D9C;
    d->saved_x = (signed char)g_00669DB5;
    d->saved_y = (signed char)g_00669DB6;
    d->x = (signed char)g_00669DB5;
    d->y = (signed char)g_00669DB6;
}

/* 0x001E33D0, 0x12C bytes. Copies the live settings of pad `pad` (0 or 1) into `out`. */
void func_001E33D0(int pad, void *out)
{
    PadSettings *p = out;
    u8 flags = PAD_FLAGS(pad);
    int i;

    p->option_20 = (flags & 0x02) ? 0 : 1;
    p->option_21 = (flags & 0x04) ? 1 : 0;
    p->option_22 = (flags & 0x08) ? 0 : 1;
    for (i = 0; i < 8; i++)                     /* unrolled in the original */
        p->slots[i] = g_00669D8C[pad * 0x12 + g_0040CC20[i]];
}

/* 0x001E3500, 0x58 bytes. Copies the live sound settings into `out` (6 bytes, see page 7). */
void func_001E3500(void *out)
{
    u8 *s = out;

    s[0] = (g_00669DB1 & 0x0F) >> 2;
    s[1] = g_00669DB2;
    s[2] = g_00669DB3;
    s[3] = g_00669DB4;
    s[4] = 0x2D;                                /* sound test: first track shown */
    s[5] = (g_00669DB1 & 0x1F) >> 4;
}

/* 0x001E3560, 0x16C bytes. Writes display settings back and applies the screen offset. */
void func_001E3560(void *in)
{
    DisplaySettings *d = in;
    u8 mode = (d->mode & 7) << 1;

    g_00669DB0 = (g_00669DB0 & 0xE1) | mode | (d->option_11 == 0 ? 0x10 : 0);
    g_00669DB0 = (g_00669DB0 & 0xDF) | (d->option_12 == 1 ? 0x20 : 0);
    g_00669DB0 = (g_00669DB0 & 0x3F) | (d->option_13 == 0 ? 0x40 : 0);
    g_00669D9C = d->value_14;
    g_00669DB5 = (u8)d->x;
    g_00669DB6 = (u8)d->y;
    func_00100ED0(&d->x, &d->y);
}

/* 0x001E36D0, 0x10C bytes. Non-zero when `in` differs from the live display settings (the screen
 * offset is not compared). */
int func_001E36D0(void *in)
{
    DisplaySettings *d = in;

    if (d->mode != (g_00669DB0 & 0x0F) >> 1)
        return 1;
    if (d->option_11 == 0 ? !(g_00669DB0 & 0x10) : (g_00669DB0 & 0x10) != 0)
        return 1;
    if (d->option_12 == 1 ? !(g_00669DB0 & 0x20) : (g_00669DB0 & 0x20) != 0)
        return 1;
    if (d->option_13 == 0 ? (g_00669DB0 >> 6) != 1 : (g_00669DB0 >> 6) != 0)
        return 1;
    return 0;
}

/* 0x001E37E0, 0x210 bytes. Writes the settings of pad `pad` back and applies them. */
void func_001E37E0(int pad, void *in)
{
    PadSettings *p = in;
    u8 o20 = p->option_20, o21 = p->option_21;
    int o22_off = (p->option_22 == 0);
    int port = pad;                             /* original: undefined unless pad is 0 or 1 */
    u8 *state;
    int i;

    PAD_FLAGS(pad) = (PAD_FLAGS(pad) & 0xFD) | ((o20 == 0) << 1);
    func_001036B0(port, o20 != 0);              /* vibration on/off? */
    PAD_FLAGS(pad) = (PAD_FLAGS(pad) & 0xFB) | ((o21 != 0) << 2);
    PAD_FLAGS(pad) = (PAD_FLAGS(pad) & 0xF7) | (o22_off << 3);

    state = &g_00500764 + port * 0x88;          /* the pad's state block */
    if ((state[0] & 1) && (state[1] & 1) == 1)
        state[0] = (state[0] & 0xF7) | (o22_off << 3);

    for (i = 0; i < 8; i++)                     /* unrolled in the original */
        g_00669D8C[pad * 0x12 + g_0040CC20[i]] = (u8)p->slots[i];
}

/* 0x001E39F0, 0xDC bytes. Non-zero when `in` differs from the live settings of pad `pad`.
 * Note: option_21 is compared the opposite way to how func_001E33D0 reads it (bit 2 set gives
 * option_21 = 1 there, but counts as "same" here only when option_21 == 0). Kept as in the
 * original: page 9 therefore always sees the settings as changed when cancelling. */
int func_001E39F0(int pad, void *in)
{
    PadSettings *p = in;
    u8 flags = PAD_FLAGS(pad);
    int i;

    if ((p->option_20 == 0) != ((flags >> 1) & 1))
        return 1;
    if ((p->option_22 == 0) != ((flags >> 3) & 1))
        return 1;
    if ((p->option_21 == 0) != ((flags >> 2) & 1))
        return 1;
    for (i = 0; i < 8; i++)
        if (p->slots[i] != g_00669D8C[pad * 0x12 + g_0040CC20[i]])
            return 1;
    return 0;
}

/* 0x001E3AD0, 0xB8 bytes. Writes the sound settings back and applies them. */
void func_001E3AD0(void *in)
{
    u8 *s = in;

    g_00669DB2 = s[1];
    g_00669DB3 = s[2];
    g_00669DB4 = s[3];
    g_00669DB1 = (g_00669DB1 & 0xE3) | ((s[0] & 3) << 2) | ((s[5] & 1) << 4);
    func_0023C050(s[0]);
    func_0017E0C0(s[1], 0);
    func_0023B530(s[2]);
    func_0023AB70(s[3]);
}

/* 0x001E3B90, 0x94 bytes. Non-zero when `in` differs from the live sound settings. */
int func_001E3B90(void *in)
{
    u8 *s = in;

    if (s[0] != (g_00669DB1 & 0x0F) >> 2 || s[1] != g_00669DB2 || s[2] != g_00669DB3 ||
        s[3] != g_00669DB4)
        return 1;
    return s[5] != (g_00669DB1 & 0x1F) >> 4;
}

/* 0x001E3C30, 0x64 bytes. Applies all live settings again (display, both pads, sound), by reading
 * them and writing them back. */
void func_001E3C30(void)
{
    PadSettings pad0, pad1;
    DisplaySettings display;
    u8 sound[8];

    func_001E3300(&display);
    func_001E33D0(0, &pad0);
    func_001E33D0(1, &pad1);
    func_001E3500(sound);
    func_001E3560(&display);
    func_001E37E0(0, &pad0);
    func_001E37E0(1, &pad1);
    func_001E3AD0(sound);
}

/* 0x001E3CA0, 0x30 bytes. Reloads the menu's display copy and applies its saved screen offset.
 * (The original keeps the struct address in v0 across the call, which func_001E3300 never
 * changes.) */
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

/* 0x001E6670, 0x1E8 bytes. Look up a byte in one of the tables at 0x00429030 (selected by `table`,
 * row chosen by whether `flag` is 0); out-of-range indexes return the table's first byte. */
u8 func_001E6670(int table, int flag, unsigned int index)
{
    unsigned int row = (flag == 0);
    u8 value = g_00429030[0];

    if (flag >= 0 || flag < 2) {   /* always true in the original code */
        switch (table) {
        case 0: if (index < 6) value = g_00429030[0x40 + index + row * 6]; break;
        case 1: if (index < 6) value = g_00429030[0x50 + index + row * 6]; break;
        case 2:
            if (index == 0x19)
                index = 8;
            if (index < 9)
                value = g_00429030[0x60 + index + row * 9];
            break;
        case 3: if (index < 6) value = g_00429030[0x78 + index + row * 6]; break;
        case 4: if (index < 8) value = g_00429030[0x90 + index + row * 8]; break;
        case 5: if (index < 6) value = g_00429030[0xA0 + index + row * 6]; break;
        default: if (index < 0x1E) value = g_00429030[index + row * 0x1E]; break;
        }
    }
    return value;
}

/* 0x001E6860, 0xF4 bytes. Enter: create the menu and reset its state. */
void func_001E6860(void)
{
    func_003F8B30(4);
    g_00731214 = func_001026D0(1, 0x3B, 0, 1, 0, 0, (const void *)0x004290F8, 0x9D7);
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

/* 0x001E6960, 0x44 bytes. Leave: destroy the menu and restore the saved value. */
void func_001E6960(void)
{
    func_00375D60();
    func_00102EC0(g_00731214);
    func_001E3D90();
    func_001037F0(g_0073123C);
    func_003F8B80();
}

/* 0x001E69B0, 0x200 bytes. Update: run the current phase; always returns 1 (so step() runs). */
int func_001E69B0(float dt)
{
    func_00376450();
    if (g_007311F8 == 3) {                       /* leaving */
        if (g_0069395E == 0 || g_0069395E == -1) {
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
    } else if (g_007311F8 == 2) {                /* closing */
        if (g_00731228 == 0)
            func_001E4030();
    } else if (g_007311F8 != 0) {                /* in use: run the current page */
        switch (g_007311F0) {
        case 0: func_001E4080(); return 1;
        case 1: func_001E44C0(); break;
        case 3: func_001E4BF0(); break;
        case 5: func_001E46E0(); break;
        case 6: func_001E5060(); break;
        case 7: func_001E5EF0(); break;
        case 8: func_001E4E70(); break;
        case 9: func_001E51C0(); break;
        case 10: func_001E5750(); break;
        }
    } else if (g_00731228 == 0) {               /* opening finished */
        g_007311F8 = 1;
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
    func_002B4BE0(g_00731214, g_007311F0, 0x10, 0x0C, 0, 0xD8, 0x28, 0x80);

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
