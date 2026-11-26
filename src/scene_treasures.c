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

/* Globals 0x0043C578-0x0043C77C: one object in the original (not reached through $gp). */
extern struct {
    const char *g_0043C578;       /* "Select  Back  OK" */
    char pad_0[0xCC];
    const char *g_0043C648;       /* "Select  Back" */
    char pad_1[0xC];
    const char *g_0043C658;       /* "Select Officer  Skills  Back" */
    const char *g_0043C65C;       /* "Select Officer  Back  OK" */
    const char *g_0043C660;       /* "Select Skill  Back" */
    const char *g_0043C664;       /* "Select Officer  Back" */
    char pad_2[0x8];
    const char *g_0043C670;       /* "Select Mount  Back" */
    char pad_3[0x100];
    const char *g_0043C774;       /* "Turn Page  Select  Back  Enlarge" */
    const char *g_0043C778;       /* "Category  Select  Back  Play" */
} s_0043C578;
#define g_0043C578 (s_0043C578.g_0043C578)
#define g_0043C648 (s_0043C578.g_0043C648)
#define g_0043C658 (s_0043C578.g_0043C658)
#define g_0043C65C (s_0043C578.g_0043C65C)
#define g_0043C660 (s_0043C578.g_0043C660)
#define g_0043C664 (s_0043C578.g_0043C664)
#define g_0043C670 (s_0043C578.g_0043C670)
#define g_0043C774 (s_0043C578.g_0043C774)
#define g_0043C778 (s_0043C578.g_0043C778)

/* Globals 0x0050074C-0x00500766: one object in the original (not reached through $gp). */
extern struct {
    unsigned short g_0050074C;   /* pressed this frame */
    unsigned short g_0050074E;   /* pressed or repeating */
    char pad_0[0x14];
    u8 g_00500764;
    u8 g_00500765;
} s_0050074C;
#define g_0050074C (s_0050074C.g_0050074C)
#define g_0050074E (s_0050074C.g_0050074E)
#define g_00500764 (s_0050074C.g_00500764)
#define g_00500765 (s_0050074C.g_00500765)

/* Globals 0x0069395E-0x0069395F: one object in the original (not reached through $gp). */
extern struct {
    u8 g_0069395E;    /* message box 1 open when neither 0 nor -1 */
    char size_unknown[8];   /* the whole object is larger (not reached through $gp) */
} s_0069395E;
#define g_0069395E (s_0069395E.g_0069395E)

/* Globals 0x00731314-0x00731360: one object in the original (not reached through $gp). */
extern struct {
    u8 g_00731314;                /* number of entries counted at enter */
    char pad_0[0x3];
    u32 g_00731318;
    u32 g_0073131C;
    u32 g_00731320;
    u32 g_00731324;
    u32 g_00731328;
    u32 g_0073132C;
    u32 g_00731330;
    int g_00731334;               /* current mode (0..14) */
    int g_00731338;               /* requested mode */
    int g_0073133C;               /* phase: 0 opening, 2 leaving, 4 changing mode, 3/5 running */
    char pad_1[0x1A];
    u8 g_0073135A;
    u8 g_0073135B;
    u8 g_0073135C;
    u8 g_0073135D;
    u8 g_0073135E;
    char g_0073135F;
} s_00731314;
#define g_00731314 (s_00731314.g_00731314)
#define g_00731318 (s_00731314.g_00731318)
#define g_0073131C (s_00731314.g_0073131C)
#define g_00731320 (s_00731314.g_00731320)
#define g_00731324 (s_00731314.g_00731324)
#define g_00731328 (s_00731314.g_00731328)
#define g_0073132C (s_00731314.g_0073132C)
#define g_00731330 (s_00731314.g_00731330)
#define g_00731334 (s_00731314.g_00731334)
#define g_00731338 (s_00731314.g_00731338)
#define g_0073133C (s_00731314.g_0073133C)
#define g_0073135A (s_00731314.g_0073135A)
#define g_0073135B (s_00731314.g_0073135B)
#define g_0073135C (s_00731314.g_0073135C)
#define g_0073135D (s_00731314.g_0073135D)
#define g_0073135E (s_00731314.g_0073135E)
#define g_0073135F (s_00731314.g_0073135F)

/* Globals 0x00799A68-0x00799A6C: one object in the original (not reached through $gp). */
extern struct {
    u32 g_00799A68;
    char size_unknown[5];   /* the whole object is larger (not reached through $gp) */
} s_00799A68;
#define g_00799A68 (s_00799A68.g_00799A68)


/* Scene state. */

typedef struct {                     /* 0x00731240 */
    int ids[26];                     /* +0x00 */
    u8 count;                        /* +0x68 */
} IdList;

/* 0x00731240: the gallery's lists (one object: the counts are reached as base + 0x100 + i). */
extern struct {
    IdList ids;                      /* +0x000 */
    u8 unknown_6c[0x94];
    u8 counts[0x20];                 /* +0x100 per entry: how many of its 4 records are in use */
} s_00731240;
#define g_00731240 (s_00731240.ids)
#define g_00731340 (s_00731240.counts)
extern u8 g_007312AC[];              /* data block shared with the drawers */

extern u8 g_00429230[];
extern u8 g_0040CC40[];

/* Controller 1 (see scene_config.c). */
#define BTN_CANCEL 0x0010
#define BTN_SKILLS 0x0020            /* the "Skills" button of mode 5 */
#define BTN_OK     0x0040
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000
#define SE_CURSOR 0x2CDC

void func_003BD5C0(void);
void func_003BD540(void);
void func_003971B0(void);
void func_003B20F0(void);
void func_003B2140(void);
int func_003A1FC0(int mount);         /* MOUNT_LOCKED (4) when the mount is not unlocked */
void func_002B3CF0(int value);

/* Button help lines (0xF0 + letter = a button icon). */

#define MENU_BGM 0x1C

void *func_003BD290(void);
void func_00101470(int value);
void func_003F8B30(int value);
u32 func_001026D0(int a, int b, int c, int d, int e, int f, void *g, int h);
void func_003BD430(void);
void func_002D6890(void);
void func_00102960(int value);
void func_002D0DC0(void *data);
typedef struct { char c[20]; } Record20;
const Record20 *func_0035DEC0(int entry, int record);
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

/* Defined further down. */
void func_001E7290(void);            /* applies the requested mode (end of a transition) */
int func_001E7680(void *data);
void func_001E7830(void);            /* mode 0: the gallery's main menu */
void func_001E7DC0(void);            /* mode 3 */
void func_001E8200(void);            /* mode 11: select skill */
void func_001E86D0(void);            /* mode 7: select mount */

/* Inlined in the original: a macro. */
#define pad1_ready() ((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_0050074C : 0))
#define pad1_held() ((unsigned short)(pad1_ready() ? g_0050074E : 0))

/* 0x001E7110, 0x180 bytes, matching. Requests mode `mode`: starts the transition (phase 4), prepares the
 * mode's screen, and moves the two layout layers (func_00376100) to the mode's positions.
 * Mode 15 leaves the gallery (phase 2). */
void func_001E7110(int mode)
{
    int layer = -1;                  /* first layer (-1: do not move) */
    int sub = layer;                 /* second layer (-1: none) */

    g_00731338 = mode;
    g_0073133C = 4;
    switch (mode) {
    case 0: layer = 0; break;
    case 1: layer = 1; func_00391390(0); func_003914C0(); break;
    case 2: layer = 2; func_00391390(1); func_00397660(); break;
    case 3: layer = 3; break;
    case 4: layer = 4; func_003EEE50(); break;
    case 5: layer = 5; break;
    case 6: layer = 6; break;
    case 7: layer = 7; break;
    case 8: layer = 8; func_0039F340(); break;
    case 9: layer = 9; func_003E79C0(); break;
    case 10: layer = 10; func_003F90A0(); break;
    case 12: layer = 3; sub = 2; func_003963D0(); break;
    case 13: layer = 3; sub = layer; func_003E4700(); break;
    case 14: sub = 4; layer = 3; break;
    case 15:                         /* leave the gallery */
        func_001B8F60(0, 6, 8);
        func_0017DF10();
        g_0073133C = 2;
        break;
    }
    if (layer >= 0)
        func_00376100(layer + 4, sub >= 0 ? sub + 0x0F : -1, -1);
}

/* 0x001E7290, 0x3F0 bytes, matching. End of a transition: tidies up the mode being left, prepares the
 * requested one (func_002ED190 starts layout animations?), then makes it current. */
void func_001E7290(void)
{
    func_002C59F0();
    func_002C5A30();
    switch (g_00731338) {
    case 0:                                     /* back to the main menu */
        if (g_00731334 == 5 && g_00731328 != 0) {
            func_00102EC0(g_00731328);
            g_00731328 = 0;
        }
        if (g_00731334 == 4 && g_00731324 != 0) {
            func_00102EC0(g_00731324);
            g_00731324 = 0;
        }
        if ((unsigned)(g_00731334 - 8) < 3)
            func_003BD580();
        if (g_00731334 == 4)
            func_003BD600();
        /* cursor back on the entry of the mode we leave (mode 11 belongs to entry 5) */
        if (g_00731334 == 11)
            g_0073135A = 5;
        else
            g_0073135A = (u8)(g_00731334 - 1);
        break;
    case 1:
        func_002ED190(0x20);
        break;
    case 2:
        func_002ED190(0x20);
        break;
    case 3:                                     /* the sub-menu of modes 12, 13, 14 */
        switch (g_00731334) {
        case 12:
            func_00397260();
            /* fall through */
        case 13:
            g_0073135A = (u8)(g_00731334 - 12);
            break;
        case 14:
            func_003B21A0();
            g_0073135A = (u8)(g_00731334 - 12);
            break;
        default:
            g_0073135A = 0;
            break;
        }
        break;
    case 12:
        func_003971B0();
        func_002ED190(0x16);
        func_002ED190(0x18);
        func_002ED190(0x1D);
        break;
    case 13:
        func_002ED190(0x23);
        func_002ED190(0x24);
        break;
    case 14:
        func_002ED190(0x25);
        func_003B20F0();
        func_003B2140();
        break;
    case 4: {
        u32 *screen;
        func_003BD5C0();
        screen = *(u32 **)((char *)func_002FC2C0() + 0x6AC);
        screen[2] = 0xFFFFFFFF;
        *(unsigned short *)((char *)screen + 0x1E) = 0;
        *(unsigned short *)((char *)screen + 0x1C) = 0;
        screen[0] = 4;
        func_002ED190(0x1E);
        break;
    }
    case 5:
        if (g_00731334 != 11) {                 /* not when coming back from the skills */
            if (g_00731328 == 0)
                g_00731328 = func_001026D0(1, 0x41, 0, 1, 0, 0, g_00429230, 0x15F);
            g_0073135F = 0;
            g_0073135B = 0;
            g_0073135C = 0;
            func_002ED190(0x11);
            func_002ED190(0x1A);
            func_002ED190(0x1C);
        }
        func_002ED190(10);
        func_002ED190(0x12);
        break;
    case 11:
        g_00799A68 = 0;
        g_0073135A = 0x28;
        func_002ED190(0x0C);
        func_002ED190(0x12);
        break;
    case 6:
        g_0073135F = 0;
        g_0073135B = 0;
        g_0073135C = 0;
        func_002ED190(0x11);
        func_002ED190(0x0E);
        func_002ED190(0x12);
        func_002ED190(0x1A);
        func_002ED190(0x1C);
        break;
    case 7:
        g_0073135A = 0;
        func_002ED190(0x1F);
        break;
    case 8:
        func_003BD540();
        func_002ED190(0x27);
        break;
    case 9:
        func_003BD540();
        func_002ED190(0x27);
        /* fall through (as in the original: func_003BD540 runs twice) */
    case 10:
        func_003BD540();
        func_002ED190(0x28);
        func_002ED190(0x29);
        break;
    case 15:                                    /* leaving: nothing to prepare */
        break;
    }
    func_002ED190(3);
    g_00731334 = g_00731338;
    g_0073133C = 0;
}

/* 0x001E7680, 0x1A8 bytes, matching. Officer list (modes 5, 6, 11): Left/Right move through 28 officers,
 * wrapping; g_0073135B follows as a scroll position 0..5, g_00731330 is the direction (1 left,
 * 2 right). Returns 1 when the cursor moved. `data` is not used. */
int func_001E7680(void *data)
{
    int held = pad1_held();

    g_00731330 = 0;
    if (held & BTN_RIGHT) {
        g_00731330 = 2;
        if (g_0073135C < 0x1B) {
            g_0073135C++;
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else {
            g_0073135C = 0;
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
        if (g_0073135B < 5)
            g_0073135B++;
        return 1;
    }
    if (held & BTN_LEFT) {
        g_00731330 = 1;
        if (g_0073135C > 0) {
            g_0073135C--;
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else {
            g_0073135C = 0x1B;
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
        if (g_0073135B > 0)
            g_0073135B--;
        return 1;
    }
    return 0;
}

#define MAIN_ENTRIES 10

/* Moves the main-menu cursor to the next available entry, `step` = 1 (down) or 9 (up). */
static void main_menu_move(const int *available, unsigned step)
{
    unsigned i;

    func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
    i = (g_0073135A + step) % MAIN_ENTRIES;
    g_0073135A = (u8)i;
    while (available[i] == 0) {
        i = (i + step) % MAIN_ENTRIES;
        g_0073135A = (u8)i;
    }
}

/* 0x001E7830, 0x4CC bytes, matching. Mode 0: the gallery's main menu, 10 entries; entry n opens mode n + 1.
 * Entries whose flag (from func_003BD290) is 0 are skipped. A fresh press wraps around, a held
 * one stops at the last available entry. */
void func_001E7830(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();
    int found = 0;
    int *available = func_003BD290();
    unsigned i;

    if (func_002ED150() != 0)                   /* animation still running */
        return;

    if (pressed & BTN_OK) {
        if (g_0073135A == 0x10) {               /* never true (10 entries): leftover in the original */
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E7110(15);
        } else {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E7110(g_0073135A + 1);
        }
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(15);
    } else if (pressed & BTN_UP) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (g_0073135A + 9) % MAIN_ENTRIES;
        while (!available[g_0073135A])
            g_0073135A = (g_0073135A + 9) % MAIN_ENTRIES;
    } else if (pressed & BTN_DOWN) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (g_0073135A + 1) % MAIN_ENTRIES;
        while (!available[g_0073135A])
            g_0073135A = (g_0073135A + 1) % MAIN_ENTRIES;
    } else if (held & BTN_UP) {
        int k = g_0073135A - 1;
        if (k >= 0) {
            int *p = &available[k];
            do {
                if (!!*p) {
                    found = 1;
                    break;
                }
                k--;
                p--;
            } while (k >= 0);
        }
        if (found) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A = (g_0073135A + 9) % MAIN_ENTRIES;
            while (!available[g_0073135A])
                g_0073135A = (g_0073135A + 9) % MAIN_ENTRIES;
        }
    } else if (held & BTN_DOWN) {
        int *p;
        int k = g_0073135A + 1;

        if (k < MAIN_ENTRIES) {
            p = &available[k];
            do {
                if (!!*p) {
                    found = 1;
                    break;
                }
                k++;
                p++;
            } while (k < MAIN_ENTRIES);
        }
        if (found) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A = (g_0073135A + 1) % MAIN_ENTRIES;
            while (!available[g_0073135A])
                g_0073135A = (g_0073135A + 1) % MAIN_ENTRIES;
        }
    }
}

/* 0x001E7D00, 0x60 bytes, matching. Mode 1 (viewer, shared with func_00391xxx). */
void func_001E7D00(float dt)
{
    char *viewer = func_00391250();

    if (func_003955A0(dt) != 0)
        func_00395510();
    if (*(int *)(viewer + 0x150) != 5)
        func_001E7110(0);
}

/* 0x001E7D60, 0x60 bytes, matching. Mode 2 (same as mode 1 with another viewer). */
void func_001E7D60(float dt)
{
    char *viewer = func_00391250();

    if (func_00397AE0(dt) != 0)
        func_00397AC0();
    if (*(int *)(viewer + 0x150) != 5)
        func_001E7110(0);
}

/* 0x001E7DC0, 0x24C bytes, matching. Mode 3: a sub-menu of 3 entries opening modes 12, 13 and 14. A fresh
 * press wraps around, a held one does not. */
void func_001E7DC0(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();

    if (pressed & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(g_0073135A + 12);
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(0);
    } else if (pressed & BTN_UP) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (u8)((g_0073135A + 2) % 3);
    } else if (pressed & BTN_DOWN) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (u8)((g_0073135A + 1) % 3);
    } else if (held & BTN_UP) {
        if (g_0073135A > 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A = (u8)((g_0073135A + 2) % 3);
        }
    } else if ((held & BTN_DOWN) && g_0073135A < 2) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (u8)((g_0073135A + 1) % 3);
    }
}

/* 0x001E8010, 0x40 bytes, matching. Mode 12 ("Turn Page  Select  Back  Enlarge": an art book?). */
void func_001E8010(void)
{
    char *book = func_00397160();

    func_003973E0();
    if (*(int *)(book + 0x34) != 5)
        func_001E7110(3);
}

/* 0x001E8050, 0x5C bytes, matching. Mode 13 ("Category  Select  Back  Play": a sound or movie player?). */
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

/* 0x001E80B0, 0x60 bytes, matching. Mode 14. */
void func_001E80B0(float dt)
{
    char *screen = func_003B2000();

    if (func_003B22C0(dt) != 0)
        func_00395510();
    if (*(int *)(screen + 8) != 5)
        func_001E7110(3);
}

/* 0x001E8110, 0xE4 bytes, matching. Mode 5 ("Select Officer  Skills  Back"). */
void func_001E8110(void)
{
    int pressed = pad1_pressed();

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

#define SKILL_HEADER 0xFF   /* cursor on the header row above the skill columns */

/* 0x001E8200, 0x400 bytes. Mode 11. Step 0 (g_0073135F = 0, "Select Officer  Back  OK"): choose
 * an officer, OK opens the skills. Step 1 ("Select Skill  Back"): 4 columns of 10 skills (cursor
 * 0..39, column = cursor / 10); Up from a column's first row goes to the header row (remembering
 * the column in g_0073135E), Down from it comes back. Cancel returns to step 0. */
void func_001E8200(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();

    if (g_0073135F == 0) {
        if (pressed & BTN_OK) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A = 0;
            g_0073135F = 1;
            g_00731330 = 3;
            func_002ED190(0x14);
            func_002ED190(0x1B);
        } else if (pressed & BTN_CANCEL) {
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_001E7110(5);
        } else {
            func_001E7680(g_007312AC);
        }
        return;
    }

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = 0x28;
        g_0073135F = 0;
        g_00731330 = 0;
        func_002ED190(0x13);
        func_002ED190(0x1C);
    } else if (held & BTN_DOWN) {
        if (g_0073135A == SKILL_HEADER) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A = (u8)(g_0073135E * 10);
            func_002B3CF0(6);
        } else if (g_0073135A % 10 < 9) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A++;
            func_002B3CF0(6);
        }
    } else if (held & BTN_UP) {
        if (g_0073135A != SKILL_HEADER) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            if (g_0073135A % 10 == 0) {
                g_0073135E = g_0073135A / 10;
                g_0073135A = SKILL_HEADER;
            } else {
                g_0073135A--;
            }
            func_002B3CF0(6);
        }
    } else if (held & BTN_RIGHT) {
        if (g_0073135A != SKILL_HEADER && g_0073135A < 0x1E) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A += 10;
            func_002B3CF0(6);
        }
    } else if (held & BTN_LEFT) {
        if (g_0073135A != SKILL_HEADER && g_0073135A > 9) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A -= 10;
            func_002B3CF0(6);
        }
    }
}

/* 0x001E8600, 0xA0 bytes, matching. Mode 6 ("Select Officer  Back"). */
void func_001E8600(void)
{
    int pressed = pad1_pressed();

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(0);
    } else {
        func_001E7680(g_007312AC);
    }
}

/* 0x001E86A0, 0x2C bytes, matching. Mode 4: back to the main menu when its screen is done. */
void func_001E86A0(void)
{
    if (func_003EF070() != 0)
        func_001E7110(0);
}

#define MOUNT_LOCKED 4

/* 0x001E86D0, 0x348 bytes, matching. Mode 7 ("Select Mount  Back"): 4 mounts, locked ones skipped. A fresh
 * press wraps and skips locked mounts; a held press moves by one only when an unlocked mount lies
 * further that way (so it can stop on a locked one, as in the original). OK does nothing. The 8
 * "unreachable" blocks Ghidra removed are the negative fix-ups of `% 4`. */
void func_001E86D0(void)
{
    int pressed = pad1_pressed();
    int held = pad1_held();
    int found = 0;
    int i;

    if (pressed & BTN_OK)
        return;
    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_001E7110(0);
    } else if (pressed & BTN_DOWN) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (u8)((g_0073135A + 1) % 4);
        while (func_003A1FC0(g_0073135A) == MOUNT_LOCKED)
            g_0073135A = (u8)((g_0073135A + 1) % 4);
    } else if (pressed & BTN_UP) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_0073135A = (u8)((g_0073135A + 3) % 4);
        while (func_003A1FC0(g_0073135A) == MOUNT_LOCKED)
            g_0073135A = (u8)((g_0073135A + 3) % 4);
    } else if (held & BTN_DOWN) {
        for (i = g_0073135A + 1; i < 4; i++)
            if (func_003A1FC0(i) != MOUNT_LOCKED) { found = 1; break; }
        if (found) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A++;
        }
    } else if (held & BTN_UP) {
        for (i = g_0073135A - 1; i >= 0; i--)
            if (func_003A1FC0(i) != MOUNT_LOCKED) { found = 1; break; }
        if (found) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_0073135A--;
        }
    }
}

/* 0x001E8A20, 0x2C bytes, matching. Mode 8. */
void func_001E8A20(void)
{
    if (func_0039F7E0() != 0)
        func_001E7110(0);
}

/* 0x001E8A50, 0x2C bytes, matching. Mode 9. */
void func_001E8A50(void)
{
    if (func_003E7E60() != 0)
        func_001E7110(0);
}

/* 0x001E8A80, 0x2C bytes, matching. Mode 10. */
void func_001E8A80(void)
{
    if (func_003F95E0() != 0)
        func_001E7110(0);
}

/* 0x001E8AB0, 0x74 bytes, matching. Fills `list` with the ids 0..25 except 6 and 12, then 26. */
void func_001E8AB0(IdList *list)
{
    int id;

    list->count = 0;
    for (id = 0; id < 0x1A; id++) {
        if (id != 12 && id != 6) {
            list->ids[list->count] = id;
            list->count++;
        }
    }
    list->ids[list->count] = 0x1A;
    list->count++;
}

/* 0x001E8B30, 0x298 bytes, matching. Scene enter. */
void func_001E8B30(void)
{
    char *res = func_003BD290();
    int i, j;

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
            /* the original copies the 20-byte record before testing its first byte */
            Record20 rec;
            rec = *func_0035DEC0(i, j);
            if ((u8)rec.c[0] < 0x7F)
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

/* 0x001E8DD0, 0xD8 bytes, matching. Scene leave: frees what enter made (in reverse order). */
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

/* 0x001E8EB0, 0x288 bytes, matching. Scene update: phases, then the current mode's handler. */
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

int func_001E8EB0(float dt)
{
    func_00376450();
    switch (g_0073133C) {
    case 0:                                     /* opening */
        if (func_002ED150() == 0)
            g_0073133C = 3;
        return 1;
    case 3:
        break;
    case 4:                                     /* changing mode */
        if (func_002ED150() == 0)
            func_001E7290();
        return 1;
    case 2:                                     /* leaving */
        if (!box1_open() && func_0017DDA0() == 0) {
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
    case 5:
        break;
    }
    switch (g_00731334) {
    case 0: func_001E7830(); break;
    case 1: func_001E7D00(dt); break;
    case 2: func_001E7D60(dt); break;
    case 3: func_001E7DC0(); break;
    case 12: func_001E8010(); break;
    case 13: func_001E8050(); break;
    case 14: func_001E80B0(dt); break;
    case 4: func_001E86A0(); break;
    case 5: func_001E8110(); break;
    case 11: func_001E8200(); break;
    case 6: func_001E8600(); break;
    case 7: func_001E86D0(); break;
    case 8: func_001E8A20(); break;
    case 9: func_001E8A50(); break;
    case 10: func_001E8A80(); break;
    }
    return 1;
}

/* 0x001E9140, 8 bytes, matching. Scene step: empty. */
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
