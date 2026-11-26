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
    func_001E3500(g_0073117C);
    func_0023C050(g_0073117C[0]);
    func_0017E110(g_0073117C[1]);
    func_0023B530(g_0073117C[2]);
    func_0023AB70(g_0073117C[3]);
}

/* 0x001E3D50, 0x1C bytes. */
void func_001E3D50(void)
{
    func_0023A4F0(0x44);
}

/* 0x001E3D70, 0x1C bytes. */
void func_001E3D70(void)
{
    func_0023A480(0x44);
}

/* 0x001E3D90, 0x1C bytes. */
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

/* 0x001E6BB0, 0x08 bytes. Step: nothing to do. */
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
