/*
 * scene_treasures.c - scene 0x0D, the Treasures gallery (original source file StateTreasures.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly); not verified by compiling with the original compiler. Unknown functions and globals
 * keep neutral names (func_/g_ + address); comments with a question mark are hypotheses.
 *
 * The scene is a set of sub-screens ("modes", g_00731334). func_001E7110 asks for another mode and
 * starts a transition; the update function runs the current mode's handler, the draw function its
 * drawer and its button help line. Mode names below come from those help lines.
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* Scene manager fields (see main.c). */
extern int g_0045D894;   /* previous state */
extern int g_0045D898;   /* current state */
extern int g_0045D89C;   /* state to return to */
extern int g_0045D8A0;   /* requested state (0x18 = none) */

extern char g_0069395E;  /* message box 1 open when neither 0 nor -1 */

/* Scene state. */
extern u32 g_00731318, g_0073131C, g_00731320, g_0073132C;  /* windows / layouts made at enter */
extern u32 g_00731324, g_00731328;                          /* optional handles, freed at leave */
extern u32 g_00731330;
extern u8 g_00731314;                /* number of entries counted at enter */
extern u8 g_00731340[];              /* per entry: how many of its 4 records are in use */
extern int g_00731334;               /* current mode (0..14) */
extern int g_00731338;               /* requested mode */
extern int g_0073133C;               /* phase: 0 opening, 2 leaving, 4 changing mode, 3/5 running */
extern u8 g_0073135A, g_0073135B, g_0073135C, g_0073135D, g_0073135E;  /* cursors? */
extern char g_0073135F;

typedef struct {                     /* 0x00731240 */
    int ids[26];                     /* +0x00 */
    u8 count;                        /* +0x68 */
} IdList;
extern IdList g_00731240;
extern u8 g_007312AC[];              /* data block shared with the drawers */

extern u8 g_00429230[];
extern u8 g_0040CC40[];

/* Controller 1 (see scene_config.c). */
extern u8 g_00500764, g_00500765;
extern unsigned short g_0050074C;
#define BTN_CANCEL 0x0010
#define BTN_SKILLS 0x0020            /* the "Skills" button of mode 5 */
#define SE_CURSOR 0x2CDC

/* Button help lines (0xF0 + letter = a button icon). */
extern const char *g_0043C578;       /* "Select  Back  OK" */
extern const char *g_0043C648;       /* "Select  Back" */
extern const char *g_0043C658;       /* "Select Officer  Skills  Back" */
extern const char *g_0043C65C;       /* "Select Officer  Back  OK" */
extern const char *g_0043C660;       /* "Select Skill  Back" */
extern const char *g_0043C664;       /* "Select Officer  Back" */
extern const char *g_0043C670;       /* "Select Mount  Back" */
extern const char *g_0043C774;       /* "Turn Page  Select  Back  Enlarge" */
extern const char *g_0043C778;       /* "Category  Select  Back  Play" */

#define MENU_BGM 0x1C

void *func_003BD290(void);
void func_00101470(int value);
void func_003F8B30(int value);
u32 func_001026D0(int a, int b, int c, int d, int e, int f, void *g, int h);
void func_003BD430(void);
void func_002D6890(void);
void func_00102960(int value);
void func_002D0DC0(void *data);
const u8 *func_0035DEC0(int entry, int record);
void func_002ED190(int value);
int func_002ED150(void);
void func_002C5A60(void);
void func_002C59F0(void);
void func_002C5A30(void);
int func_001037F0(int value);
void func_00375C20(int a, int b, int c, void *d, int e);
void func_00376100(int a, int b, int c);
void func_0030CE90(int value);
void func_001B8F60(int a, int b, int c);
void func_0017E010(int value);
void func_0017DF10(void);
int func_0017DDA0(void);
void func_00375D60(void);
void func_003BD4A0(void);
void func_002D68F0(void);
void func_00102EC0(u32 handle);
void func_003BD580(void);
void func_003BD600(void);
void func_003B21A0(void);
void func_00397260(void);
void func_0023AF50(int a, int b);
void func_003F8B80(void);
void func_00376450(void);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_00391390(int value);
void func_003914C0(void);
void func_00397660(void);
void func_003EEE50(void);
void func_0039F340(void);
void func_003E79C0(void);
void func_003F90A0(void);
void func_003963D0(void);
void func_003E4700(void);
void *func_00391250(void);
int func_003955A0(float dt);
void func_00395510(void);
int func_00397AE0(float dt);
void func_00397AC0(void);
void *func_00397160(void);
void func_003973E0(void);
void *func_003E46F0(void);
void func_003E4F40(void);
void *func_003B2000(void);
int func_003B22C0(float dt);
int func_003EF070(void);
int func_0039F7E0(void);
int func_003E7E60(void);
int func_003F95E0(void);
void func_00278A20(void);
void func_003F8C00(void);
void func_00375F90(void);
void func_001A7DC0(const char *text, int alpha, int b);
void func_00391DA0(void);
void func_003EEDD0(void);
void func_003B20B0(void);
void *func_002FC2C0(void);
void func_002EE610(u32 a, u8 b);
void func_002EF7F0(void);
void func_002EF870(void);
void func_002EEB60(u32 a, u8 b);
void func_002EF150(u32 a, u32 b, u32 c, u32 d, u32 e, void *f, u8 g, u8 h);
void func_002EF360(u32 a, u32 b, void *c, u32 d, u8 e, u8 f);
void func_002EF300(u32 a, void *b, u32 c, u8 d, u8 e);
void func_002EF390(u32 a, u32 b, u32 c, u8 d);
void func_002EF8F0(void);
void func_002EF970(void);
void func_002EF9F0(void);
void func_002EF330(u32 a, void *b, u32 c, u8 d, u8 e, u8 f);
void func_002EF180(u32 a);
void func_002EF200(u32 a, u32 b, int c, void *d, u32 e, u8 f, u8 g, u8 h);
void func_002EF280(void);

/* Mode handlers not decompiled yet. */
void func_001E7290(void);            /* applies the requested mode (end of a transition) */
int func_001E7680(void *data);
void func_001E7830(void);            /* mode 0: the gallery's main menu */
void func_001E7DC0(void);            /* mode 3 */
void func_001E8200(void);            /* mode 11: select skill */
void func_001E86D0(void);            /* mode 7: select mount */

static unsigned short pad1_pressed(void)
{
    return ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074C : 0;
}

/* 0x001E7110, 0x180 bytes. Requests mode `mode`: starts the transition (phase 4), prepares the
 * mode's screen, and moves the two layout layers (func_00376100) to the mode's positions.
 * Mode 15 leaves the gallery (phase 2). */
void func_001E7110(int mode)
{
    int second = -1;                 /* second layer (-1: none) */
    int first = -1;                  /* first layer (-1: do not move) */

    g_00731338 = mode;
    g_0073133C = 4;
    switch (mode) {
    case 0: first = 0; break;
    case 1: first = 1; func_00391390(0); func_003914C0(); break;
    case 2: first = 2; func_00391390(1); func_00397660(); break;
    case 3: first = 3; break;
    case 4: func_003EEE50(); first = 4; break;
    case 5: first = 5; break;
    case 6: first = 6; break;
    case 7: first = 7; break;
    case 8: func_0039F340(); first = 8; break;
    case 9: func_003E79C0(); first = 9; break;
    case 10: func_003F90A0(); first = 10; break;
    case 12: second = 2; func_003963D0(); first = 3; break;
    case 13: second = 3; func_003E4700(); first = 3; break;
    case 14: second = 4; first = 3; break;
    case 15:                         /* leave the gallery */
        func_001B8F60(0, 6, 8);
        func_0017DF10();
        g_0073133C = 2;
        break;
    }
    if (first >= 0)
        func_00376100(first + 4, second < 0 ? -1 : second + 0x0F, -1);
}

/* 0x001E7D00, 0x60 bytes. Mode 1 (viewer, shared with func_00391xxx). */
void func_001E7D00(float dt)
{
    char *viewer = func_00391250();

    if (func_003955A0(dt) != 0)
        func_00395510();
    if (*(int *)(viewer + 0x150) != 5)
        func_001E7110(0);
}

/* 0x001E7D60, 0x60 bytes. Mode 2 (same as mode 1 with another viewer). */
void func_001E7D60(float dt)
{
    char *viewer = func_00391250();

    if (func_00397AE0(dt) != 0)
        func_00397AC0();
    if (*(int *)(viewer + 0x150) != 5)
        func_001E7110(0);
}

/* 0x001E8010, 0x40 bytes. Mode 12 ("Turn Page  Select  Back  Enlarge": an art book?). */
void func_001E8010(void)
{
    char *book = func_00397160();

    func_003973E0();
    if (*(int *)(book + 0x34) != 5)
        func_001E7110(3);
}

/* 0x001E8050, 0x5C bytes. Mode 13 ("Category  Select  Back  Play": a sound or movie player?). */
void func_001E8050(void)
{
    char *player = func_003E46F0();

    func_003E4F40();
    if (*(int *)(player + 0x10) != 5) {
        if (*(int *)(player + 0x10) == 1)
            func_001E7110(15);       /* leave the gallery */
        else
            func_001E7110(3);
    }
}

/* 0x001E80B0, 0x60 bytes. Mode 14. */
void func_001E80B0(float dt)
{
    char *screen = func_003B2000();

    if (func_003B22C0(dt) != 0)
        func_00395510();
    if (*(int *)(screen + 8) != 5)
        func_001E7110(3);
}

/* 0x001E8110, 0xE4 bytes. Mode 5 ("Select Officer  Skills  Back"). */
void func_001E8110(void)
{
    unsigned short pressed = pad1_pressed();

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(0);
    } else if (pressed & BTN_SKILLS) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(11);
    } else if (func_001E7680(g_007312AC) != 0) {
        func_002ED190(11);
    }
}

/* 0x001E8600, 0xA0 bytes. Mode 6 ("Select Officer  Back"). */
void func_001E8600(void)
{
    if (pad1_pressed() & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(0);
    } else {
        func_001E7680(g_007312AC);
    }
}

/* 0x001E86A0, 0x2C bytes. Mode 4: back to the main menu when its screen is done. */
void func_001E86A0(void)
{
    if (func_003EF070() != 0)
        func_001E7110(0);
}

/* 0x001E8A20, 0x2C bytes. Mode 8. */
void func_001E8A20(void)
{
    if (func_0039F7E0() != 0)
        func_001E7110(0);
}

/* 0x001E8A50, 0x2C bytes. Mode 9. */
void func_001E8A50(void)
{
    if (func_003E7E60() != 0)
        func_001E7110(0);
}

/* 0x001E8A80, 0x2C bytes. Mode 10. */
void func_001E8A80(void)
{
    if (func_003F95E0() != 0)
        func_001E7110(0);
}

/* 0x001E8AB0, 0x74 bytes. Fills `list` with the ids 0..25 except 6 and 12, then 26. */
void func_001E8AB0(IdList *list)
{
    int id;

    list->count = 0;
    for (id = 0; id < 0x1A; id++) {
        if (id != 12 && id != 6)
            list->ids[list->count++] = id;
    }
    list->ids[list->count++] = 0x1A;
}

/* 0x001E8B30, 0x298 bytes. Scene enter. */
void func_001E8B30(void)
{
    char *res = func_003BD290();
    int i, j, k;

    func_00101470(1);
    func_003F8B30(2);
    g_00731318 = func_001026D0(1, 0x36, 0, 1, 0, 0, g_00429230, 0x461);
    g_0073131C = func_001026D0(1, 0x40, 0, 1, 0, 0, g_00429230, 0x462);
    g_00731320 = func_001026D0(1, 0x37, 0, 1, 0, 0, g_00429230, 0x465);
    g_0073132C = func_001026D0(1, 0x3B, 0, 1, 0, 0, g_00429230, 0x469);
    func_003BD430();
    func_002D6890();
    func_00102960(1);
    func_001E8AB0(&g_00731240);
    func_002D0DC0(g_007312AC);

    /* Count the records in use (first byte < 0x7F) of each entry. */
    for (i = 0; i < g_00731314; i++) {
        g_00731340[i] = 0;
        for (j = 0; j < 4; j++) {
            const u8 *rec = func_0035DEC0(i, j);
            u8 copy[20];
            for (k = 0; k < 20; k++)            /* the original copies the record first */
                copy[k] = rec[k];
            if (copy[0] < 0x7F)
                g_00731340[i]++;
        }
    }

    g_0073135A = 0;
    g_00731334 = 0;
    g_0073133C = 0;
    g_00731338 = 0;
    func_002ED190(0);
    func_002C5A60();
    func_002C59F0();
    func_002C5A30();
    g_0073135A = 0;
    g_0073135B = 0;
    g_0073135C = 0;
    g_0073135D = 0;
    g_0073135E = 0;
    func_001037F0(1);
    func_00375C20(0, *(int *)(res + 0x30), 0x17, g_0040CC40, 0x0B);
    func_00376100(4, -1, -1);
    func_0030CE90(10);
    func_001B8F60(1, 6, 8);
    func_0017E010(MENU_BGM);
}

/* 0x001E8DD0, 0xD8 bytes. Scene leave: frees what enter made (in reverse order). */
void func_001E8DD0(void)
{
    func_00375D60();
    func_003BD4A0();
    func_002D68F0();
    if (g_00731328 != 0) {
        func_00102EC0(g_00731328);
        g_00731328 = 0;
    }
    func_00102EC0(g_0073132C);
    func_00102EC0(g_00731320);
    if (g_00731324 != 0) {
        func_00102EC0(g_00731324);
        g_00731324 = 0;
    }
    func_00102EC0(g_0073131C);
    func_00102EC0(g_00731318);
    func_003BD580();
    func_003BD600();
    func_003B21A0();
    func_00397260();
    func_001037F0(0);
    func_0023AF50(3, 1);
    func_003F8B80();
}

/* 0x001E8EB0, 0x288 bytes. Scene update: phases, then the current mode's handler. */
int func_001E8EB0(float dt)
{
    func_00376450();
    if (g_0073133C == 2) {                      /* leaving */
        if (g_0069395E != 0 && g_0069395E != -1)
            return 1;
        if (func_0017DDA0() != 0)
            return 1;
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
            g_0045D894 = g_0045D898;            /* go to the requested scene */
            g_0045D898 = g_0045D8A0;
            g_0045D89C = 0x18;
        } else {
            g_0045D894 = g_0045D898;            /* go back to the scene we came from */
            g_0045D898 = g_0045D89C;
            g_0045D89C = g_0045D8A0;
        }
        return 1;
    }
    if (g_0073133C == 4) {                      /* changing mode */
        if (func_002ED150() == 0)
            func_001E7290();
        return 1;
    }
    if (g_0073133C == 0) {                      /* opening */
        if (func_002ED150() == 0)
            g_0073133C = 3;
        return 1;
    }

    switch (g_00731334) {
    case 0: func_001E7830(); break;
    case 1: func_001E7D00(dt); break;
    case 2: func_001E7D60(dt); break;
    case 3: func_001E7DC0(); break;
    case 4: func_001E86A0(); break;
    case 5: func_001E8110(); break;
    case 6: func_001E8600(); break;
    case 7: func_001E86D0(); break;
    case 8: func_001E8A20(); break;
    case 9: func_001E8A50(); break;
    case 10: func_001E8A80(); break;
    case 11: func_001E8200(); break;
    case 12: func_001E8010(); break;
    case 13: func_001E8050(); break;
    case 14: func_001E80B0(dt); break;
    }
    return 1;
}

/* 0x001E9140, 8 bytes. Scene step: empty. */
void func_001E9140(void)
{
}

/* 0x001E9150, 0x498 bytes. Scene draw: the current mode's screen, then its button help line. */
void func_001E9150(void)
{
    func_00278A20();
    func_003F8C00();
    switch (g_00731334) {
    case 0: func_002EE610(g_0073131C, g_0073135A); break;
    case 1: func_002EF7F0(); break;
    case 2: func_002EF870(); break;
    case 3: func_002EEB60(g_0073131C, g_0073135A); break;
    case 4:
        func_002EF150(g_00731324, g_0073131C, g_00731318, g_0073132C, g_00731330, g_007312AC,
                      g_0073135B, g_0073135A);
        break;
    case 5:
        func_002EF360(g_0073132C, g_00731328, g_007312AC, g_00731330, g_0073135B, g_0073135C);
        break;
    case 6: func_002EF300(g_0073132C, g_007312AC, g_00731330, g_0073135B, g_0073135C); break;
    case 7: func_002EF390(g_00731320, g_0073131C, g_00731318, g_0073135A); break;
    case 8: func_002EF8F0(); break;
    case 9: func_002EF970(); break;
    case 10: func_002EF9F0(); break;
    case 11:
        func_002EF330(g_0073132C, g_007312AC, g_00731330, g_0073135B, g_0073135A, g_0073135C);
        break;
    case 12: func_002EF180(g_0073131C); break;
    case 13:
        func_002EF200(g_0073131C, g_0073132C, 0, &g_00731240, g_00731330, g_0073135B, g_0073135A,
                      g_0073135C);
        break;
    case 14: func_002EF280(); break;
    }
    func_00375F90();

    switch (g_00731334) {
    case 0: case 3: func_001A7DC0(g_0043C578, 0x80, 2); break;
    case 1: case 2: func_00391DA0(); break;
    case 4: func_003EEDD0(); break;
    case 5: func_001A7DC0(g_0043C658, 0x80, 2); break;
    case 6: func_001A7DC0(g_0043C664, 0x80, 2); break;
    case 7: func_001A7DC0(g_0043C670, 0x80, 2); break;
    case 8: case 9: {
        char *game = func_002FC2C0();
        int kind = *(int *)(*(char **)(game + 0x694) + 0x220);
        func_001A7DC0(kind == 1 ? g_0043C648 : g_0043C578, 0x80, 2);
        break;
    }
    case 10: func_001A7DC0(g_0043C648, 0x80, 2); break;
    case 11:
        if (g_0073135F == 1)
            func_001A7DC0(g_0043C660, 0x80, 2);
        else if (g_0073135F == 0)
            func_001A7DC0(g_0043C65C, 0x80, 2);
        break;
    case 12: func_001A7DC0(g_0043C774, 0x80, 2); break;
    case 13: func_001A7DC0(g_0043C778, 0x80, 2); break;
    case 14: func_003B20B0(); break;
    }
}
