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
