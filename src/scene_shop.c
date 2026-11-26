/*
 * scene_shop.c - scene 0x0E, the shop (original source file StateShop.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly); not verified by compiling with the original compiler. Unknown functions and globals
 * keep neutral names (func_/g_ + address); comments with a question mark are hypotheses.
 *
 * The shop has a current mode (g_00773148: what the player is doing) and a screen (g_00773144: what
 * is drawn). func_0029FE50 applies a requested mode (g_0077314C) and picks its screen. Screen names
 * below come from their button help lines (buy skills or mounts, hire or dismiss guards, sell...).
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* Scene manager fields (see main.c). */
extern int g_0045D894;   /* previous state */
extern int g_0045D898;   /* current state */
extern int g_0045D89C;   /* state to return to */
extern int g_0045D8A0;   /* requested state (0x18 = none) */

extern char g_0069395E;  /* message box 1 open when neither 0 nor -1 */

/* 0x7000015C: random seed in the scratchpad (set to 12345 at start-up, see main.c). */
#define g_7000015C (*(volatile u32 *)0x7000015C)

/* Shop state. */
extern u8 g_00773130[];              /* data block filled by func_002CAD60 */
extern char g_00773138;              /* (inside it) non-zero: the "Guards" variant of the hire screen */
extern u8 g_0077313C[];              /* data block filled by func_002CAD90 */
extern u8 g_00773140;                /* (inside it) cursor of screens 5 and 7 */
extern int g_00773144;               /* screen being drawn (0..9) */
extern int g_00773148;               /* current mode (0..16) */
extern int g_0077314C;               /* requested mode */
extern int g_00773154;               /* phase: 0 opening, 1 leaving with a sound, 2 leaving, 3 running */
extern int g_00773158;               /* scene we came from */
extern int g_0077315C;               /* player using the shop (0 or 1): picks the controller and
                                      * the 0x140-byte record of g_00772DF0 */
extern int g_00773160;               /* shopkeeper picture? (0xB5..0xB9) */
extern int g_00773164;               /* shopkeeper sound bank? (0x20..0x24) */
extern u32 g_00773168, g_0077316C, g_00773170;   /* layouts made at enter */
extern u8 g_00773174[];              /* 4 bytes per officer: state of slots 0-3 (0, 1 or more) */
extern u8 g_0077317C, g_0077317D, g_0077317E, g_0077317F, g_00773181, g_00773183, g_00773184;
extern u8 g_00773185, g_00773186, g_00773187, g_00773188, g_00773189, g_0077318A;
extern char g_0077318B;              /* non-zero: func_002D6890 succeeded at enter */
extern int g_0077318C, g_00773190, g_00773194, g_00773198;   /* conditions for the shopkeeper */
extern int g_0077319C, g_007731A0;
extern u8 g_00772DF0[];              /* 0x140 bytes per officer, 0x50 per slot */
extern u8 g_00773070[], g_007730D0[];
extern u8 g_00440CD8[];
extern u8 g_0045CEA8[];
extern int g_0045CE98, g_0045CE9C;   /* a pair saved at enter and restored at leave */
extern u32 g_00780494;
extern u32 g_00799A68;

/* Controller 1 (see scene_config.c). */
extern u8 g_00500764, g_00500765;
extern unsigned short g_0050074C;
#define BTN_L1R1   0x000C            /* L1 or R1 (swap "All Skills" / "Own Skills") */
#define BTN_CANCEL 0x0010
#define BTN_EXTRA  0x0020            /* the third face button ("Skills", "Mounts", "Guards") */
#define BTN_OK     0x0040
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000
#define SE_CURSOR 0x2CDC

/* Controller state blocks, 0x88 bytes per player (block of player 0 at 0x0050074C):
 * +0x00 buttons pressed this frame, +0x02 pressed or repeating, +0x18 / +0x19 ready flags. */
static void read_pad(int player, unsigned short *pressed, unsigned short *held)
{
    /* (the original leaves the pad unread when player is neither 0 nor 1) */
    const u8 *pad = (const u8 *)&g_0050074C + player * 0x88;
    int ready = (pad[0x18] & 1) && (pad[0x19] & 1) == 1;

    *pressed = ready ? *(const unsigned short *)pad : 0;
    *held = ready ? *(const unsigned short *)(pad + 2) : 0;
}

extern int g_00773150;               /* mode before the last request */
extern u8 g_007731D0[];              /* 0x24-byte records */
extern int g_0045D56C;               /* (gp - 0x7684) officer shown by the skill list, 0x19F = none */
extern unsigned char g_00799A24, g_00799A26;
extern int g_00799A28, g_00799A2C;

#define OFFICER_NONE 0x19F

void func_00376100(int a, int b, int c);
void func_002A86A0(int value);
int func_0036DC30(u32 officer, u8 skill);

/* Button help lines (0xF0 + letter = a button icon). */
extern const char *g_0043C55C;       /* "Back" */
extern const char *g_0043C578;       /* "Select  Back  OK" */
extern const char *g_0043C57C;       /* "Select  Skills  Back  OK" */
extern const char *g_0043C580;       /* "Select  Skills  Back  Buy" */
extern const char *g_0043C584;       /* "Select  Back" */
extern const char *g_0043C58C;       /* "Select  Mounts  Back  Buy" */
extern const char *g_0043C590;       /* "Select  Back  Buy" */
extern const char *g_0043C594;       /* "Select  Back  Sell" */
extern const char *g_0043C598;       /* "Select  Guards  Back  Hire" */
extern const char *g_0043C59C;       /* "Select  Back  Hire" */
extern const char *g_0043C5A0;       /* "Select  Back  Dismiss" */
extern const char *g_0043C648;       /* "Select  Back" */
extern const char *g_0043C868;       /* "All Skills  Select  Back" */
extern const char *g_0043C86C;       /* "Own Skills  Select  Back" */
extern const char *g_0043C87C;       /* "Skills  Back  Buy" */
extern const char *g_0043C880;       /* "Mounts  Back  Buy" */
extern const char *g_0043C884;       /* "Back  Sell" */
extern const char *g_0043C888;       /* "Back  Hire" */
extern const char *g_0043C88C;       /* "Back  Buy" */
extern const char *g_0043C890;       /* "Skills  Back" */
extern const char *g_0043C894;       /* "Mounts  Back" */

#define SHOP_BGM 0x2C

void func_002A5000(int reload);
u32 func_001026D0(int a, int b, int c, int d, int e, int f, void *g, int h);
void func_0030D8D0(void);
char func_002D6890(void);
int func_00102960(int value);
void func_002CAD60(void *data);
void func_002CAD90(void *data);
void func_0023A290(int bank);
void func_002C59F0(void);
void func_002C5A30(void);
void func_0039FA40(void *dst, void *src);
void func_002A86A0(int value);
void func_0017E010(int track);
void func_001B8F60(int a, int b, int c);
int func_0023A260(void);
void func_0023AA40(void);
void func_0030DB70(void);
void func_002D68F0(void);
void func_00102EC0(u32 handle);
void func_00375D60(void);
void func_00375C20(int a, u32 b, int c, void *d, int e);
void func_00376100(int a, int b, int c);
void func_00376450(void);
int func_0017DDA0(void);
void func_0017DF10(void);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_002A01D0(int reload);
void func_002A0920(int reload);
void func_002A1380(void);
void func_002A1650(void);
void func_002A2770(void);
void func_002A29E0(void);
int func_002A3DB0(int player);
void func_002A3580(int officer);
void func_002A2EF0(int officer);
void func_002A18D0(int officer);
void func_002A21B0(int officer, int kind);
void func_002A0B40(int officer);
void func_002A3920(int officer);
void func_002A1E90(int officer);
void func_002A3300(int officer);
void func_002AA0C0(u32 layout, int screen, int c);
void func_002AA150(u32 layout, int screen, int officer);
void func_00375F90(void);
u32 func_00105E10(void);
void func_00105EB0(u32 a, int b);
void func_00105F70(u32 a);
void func_002ABFD0(u32 layout, void *data, int keeper);
void func_002AC330(u32 a, u32 b, int mode, void *slots, void *states, u8 slot, u8 c);
void func_002AD0B0(u32 a, int b, u32 c, void *d, u8 e, u8 f, u8 g);
void func_002AC7F0(u32 a, u32 b, u32 c, void *d, u8 e, u8 f);
void func_002ACC30(u32 a, u32 b, u32 c, u8 d, void *e, int f);
void func_002ACEC0(u32 a, u32 b, u32 c, u8 d, void *e, int f);
u32 func_0029FD70(void);
void func_0029C140(u32 a, u8 b, int c);
int func_0029FD10(void);
void func_001A7DC0(const char *text, int alpha, int b);

static unsigned short pad1_pressed(void)
{
    return ((g_00500764 & 1) && (g_00500765 & 1) == 1) ? g_0050074C : 0;
}

/* Next value of the game's random generator (a linear congruential generator, 0..65535). */
static unsigned random16(void)
{
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    return g_7000015C >> 16;
}

/* 0x0029FD10, 0x10 bytes. Non-zero when the shop also sells mounts. */
int func_0029FD10(void)
{
    return g_00773140 != 0;
}

/* 0x0029FD20, 0x30 bytes. Number of entries of the shop's main menu: 4 with mounts, else 3. */
int func_0029FD20(void)
{
    return func_0029FD10() == 0 ? 3 : 4;
}

/* 0x0029FD50, 0x20 bytes. Sets the officer shown by the skill list when `officer` is valid
 * (0..0x19E), and returns the current one. */
int func_0029FD50(int officer)
{
    if (officer >= 0 && officer < OFFICER_NONE)
        g_0045D56C = officer;
    return g_0045D56C;
}

/* 0x0029FD70, 0x1C bytes. The officer shown by the skill list. */
u32 func_0029FD70(void)
{
    return func_0029FD50(OFFICER_NONE);
}

/* 0x0029FD90, 0x1C bytes. Record `index` of the 0x24-byte table at 0x007731D0. */
void *func_0029FD90(int index)
{
    return &g_007731D0[index * 0x24];
}

/* 0x0029FDB0, 0x9C bytes. Requests mode `mode` (applied by func_0029FE50 on the next update) and
 * moves the layout layer to the mode's position: modes 1-4 use layers 5-8, mode 11 layer 8. */
void func_0029FDB0(int mode)
{
    int layer = -1;

    g_00773150 = g_00773148;
    if (mode == 16)
        g_00780494 = 1;
    g_00773154 = 1;
    if (mode > 0 && mode < 5)
        layer = mode + 4;
    if (mode == 11)
        layer = 8;
    g_0077314C = mode;
    func_00376100(3, 4, layer);
}

/* 0x0029FE50, 0x350 bytes. Applies the requested mode (g_0077314C): picks its screen, resets the
 * cursors it needs and starts its layout animations (func_002A86A0). Mode 16 leaves the shop. */
void func_0029FE50(void)
{
    int current = g_0045D898;

    func_002C59F0();
    func_002C5A30();
    switch (g_0077314C) {
    case 0:
        g_00773144 = 0;
        g_00773186 = 0;
        func_002A86A0(2);
        break;
    case 1:
        if (g_00773148 < 1) {
            g_00773181 = 0;
            g_00773186 = 0;
            func_002A86A0(3);
        }
        g_00773144 = 1;
        if (g_00773148 == 0)
            func_002A86A0(0x15);
        break;
    case 2:
        g_00773144 = 2;
        if (g_00773148 != 14 && g_00773148 != 15) {
            g_00773184 = 0;
            g_00773185 = 0;
        }
        func_002A86A0(4);
        if (g_00773148 == 0)
            func_002A86A0(0x15);
        break;
    case 3:
        g_00773144 = 3;
        if (g_00773148 != 11 && g_00773148 != 12)
            g_00773183 = 0;
        func_002A86A0(6);
        if (g_00773148 == 0)
            func_002A86A0(0x15);
        break;
    case 4:
    case 11:
        g_00773144 = 5;
        g_00773186 = 0;
        func_002A86A0(0x0C);
        break;
    case 5: case 6: case 7: case 8:
        g_00773144 = 1;
        if (g_00773148 != 9)
            g_00773186 = 0;
        break;
    case 9:
        g_00799A68 = g_0077315C;
        func_002A86A0(0x0F);
        g_00773144 = 9;
        g_00773187 = 0;
        g_00773188 = 0;
        g_007731A0 = 1;
        break;
    case 12:
        g_00773144 = 7;
        g_00773186 = 0;
        func_002A86A0(0x0E);
        break;
    case 14:
        g_00773144 = 6;
        g_00773189 = 0;
        g_00773186 = 0;
        func_002A86A0(0x0B);
        break;
    case 15:
        g_00773144 = 8;
        g_00773186 = 0;
        func_002A86A0(0x0D);
        break;
    case 16:                                    /* leave the shop */
        if (g_0045D89C > 0x17 && g_0045D8A0 > 0x17)
            g_0045D89C = 0x12;                  /* nowhere to go back to: scene 0x12 */
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
            g_0045D898 = g_0045D8A0;
            g_0045D89C = 0x18;
        } else {
            g_0045D898 = g_0045D89C;
            g_0045D89C = g_0045D8A0;
        }
        g_0045D894 = current;
        g_00773186 = 0;
        break;
    }
    g_00773148 = g_0077314C;
}

/* 0x002A41D0, 0x40 bytes. Places the shop's layout layers. */
void func_002A41D0(void)
{
    func_00375C20(0, g_00773168, 2, g_0045CEA8, 1);
    func_00376100(3, 4, -1);
}

/* 0x002A4210, 0x33C bytes. Scene enter. Picks a shopkeeper at random: 0xB9 (50 %) or 0xB8 (25 %)
 * when their condition holds, else 0xB5 or 0xB6 (50 % each). */
void func_002A4210(void)
{
    func_002A5000(0);
    g_00773158 = g_0045D894;
    g_0077315C = 0;
    g_00773168 = func_001026D0(1, 0x3A, 0, 1, 0, 0, g_00440CD8, 0x85E);
    g_0077316C = func_001026D0(1, 0x36, 0, 1, 0, 0, g_00440CD8, 0x85F);
    g_00773170 = func_001026D0(1, 0x37, 0, 1, 0, 0, g_00440CD8, 0x860);
    func_0030D8D0();
    g_0077318B = func_002D6890();
    func_00102960(1);
    g_0069395E = 0;
    g_00773144 = 0;
    g_00773148 = 0;
    g_0077314C = 0;
    g_00773154 = 3;
    g_00773186 = 0;
    g_00773181 = 0;
    g_0077317F = 0;
    g_0077317E = 0;
    g_0077318A = 0;
    g_0077318C = 0;
    g_00773190 = 0;
    g_0077319C = 0;
    g_007731A0 = 1;
    func_002CAD60(g_00773130);
    func_002CAD90(g_0077313C);

    if ((g_00773190 == 1 || g_00773198 == 1) && random16() % 100 < 50) {
        g_00773160 = 0xB9;
        g_00773164 = 0x24;
    } else if ((g_0077318C == 1 || g_00773194 == 1) && random16() % 100 < 25) {
        g_00773160 = 0xB8;
        g_00773164 = 0x23;
    } else if (random16() % 100 < 50) {
        g_00773160 = 0xB5;
        g_00773164 = 0x20;
    } else {
        g_00773160 = 0xB6;
        g_00773164 = 0x21;
    }

    func_0023A290(g_00773164);
    func_002C59F0();
    func_002C5A30();
    func_002A41D0();
    g_0045CE98 = 1;
    g_0045CE9C = 0;
    func_0039FA40(&g_0045CE98, &g_0045CE98);
    func_002A86A0(0);
    g_00780494 = 0;
    func_0017E010(SHOP_BGM);
    func_001B8F60(1, 6, 8);
}

/* 0x002A4550, 0x84 bytes. Scene leave. */
void func_002A4550(void)
{
    int saved[2];

    func_0039FA40(saved, &g_0045CE98);
    if (func_0023A260() != 0)
        func_0023AA40();
    func_0030DB70();
    if (g_0077318B != 0)
        func_002D68F0();
    func_00102EC0(g_00773170);
    func_00102EC0(g_0077316C);
    func_00102EC0(g_00773168);
    func_00375D60();
}

/* 0x002A45E0, 0x1C bytes. Scene leave_alt (used when another scene was requested). */
void func_002A45E0(void)
{
    func_00375D60();
}

/* 0x002A4600, 0x334 bytes. Scene update: phases, then the current mode's handler. */
int func_002A4600(float dt)
{
    unsigned short pressed = pad1_pressed();

    func_00376450();
    if (func_00102960(0) == 0)
        return 1;

    if (g_00773154 == 2) {                      /* leaving: wait for the music and message box */
        if (func_0017DDA0() != 0)
            return 1;
        if (g_0069395E != 0 && g_0069395E != -1)
            return 1;
        func_0029FE50();
        return 1;
    }
    if (g_00773154 == 1) {
        if (g_0077314C != 16) {
            func_0029FE50();
            g_00773154 = 0;
            return 1;
        }
        if (func_0023A260() == 0) {             /* the shopkeeper's voice has finished */
            if (func_0017DDA0() != 0)
                func_0017DF10();
            func_001B8F60(0, 6, 8);
            g_00773154 = 2;
        }
        if (pressed & BTN_CANCEL) {             /* skip the goodbye */
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            if (func_0017DDA0() != 0)
                func_0017DF10();
            func_0023AA40();
            func_002A86A0(1);
            g_00773154 = 2;
            func_001B8F60(0, 6, 8);
        }
        return 1;
    }
    if (g_00773154 == 0) {
        g_00773154 = 3;
        return 1;
    }

    switch (g_00773148) {
    case 0: func_002A3DB0(0); break;
    case 1: func_002A3580(g_0077315C); break;
    case 2: func_002A2EF0(g_0077315C); break;
    case 3: func_002A18D0(g_0077315C); break;
    case 4: func_002A21B0(g_0077315C, 0); break;
    case 5: case 6: case 7: case 8: func_002A0B40(g_0077315C); break;
    case 9: func_002A3920(g_0077315C); break;
    case 11: func_002A21B0(g_0077315C, 3); break;
    case 12: func_002A1E90(g_0077315C); break;
    case 15: func_002A3300(g_0077315C); break;
    }
    return 1;
}

/* 0x002A4940, 8 bytes. Scene step: empty. */
void func_002A4940(void)
{
}

/* Help line chosen from a "slot state": 0 = only `none`, 1 = `one`, 2 or more = `more`. */
static void help_by_state(u8 state, const char *more, const char *one, const char *none)
{
    if (state >= 2)
        func_001A7DC0(more, 0x80, 1);
    else if (state == 1)
        func_001A7DC0(one, 0x80, 1);
    else if (none != 0)
        func_001A7DC0(none, 0x80, 1);
}

/* 0x002A4950, 0x6A4 bytes. Scene draw: the screen, then its button help line. */
void func_002A4950(void)
{
    u32 view;

    func_002AA0C0(g_00773168, g_00773144, 0);
    func_00375F90();
    view = func_00105E10();
    func_00105EB0(view, 0);
    func_00105F70(view);

    switch (g_00773144) {
    case 0: func_002ABFD0(g_00773168, &g_0077317E, g_00773160); break;
    case 1:
        func_002AC330(g_00773168, g_0077316C, g_00773148,
                      &g_00772DF0[g_0077315C * 0x140 + g_00773181 * 0x50],
                      &g_00773174[g_0077315C * 4], g_00773181, g_00773186);
        break;
    case 2:
        func_002AD0B0(g_00773168, 0, g_0077316C, g_007730D0, g_0077317D, g_00773184, g_00773185);
        break;
    case 3:
        func_002AC7F0(g_00773168, g_00773170, g_0077316C, g_00773070, g_0077317C, g_00773183);
        break;
    case 4:
    case 5:
        func_002ACC30(g_00773168, g_0077316C, g_00773170, g_00773186, g_0077313C, g_0077315C);
        break;
    case 7:
        func_002ACEC0(g_00773168, g_0077316C, g_00773170, g_00773186, g_0077313C, g_0077315C);
        break;
    case 9: func_0029C140(func_0029FD70(), g_00773187, g_007731A0); break;
    }

    switch (g_00773144) {
    case 0: func_001A7DC0(g_0043C578, 0x80, 1); break;
    case 1:
        if (g_00773148 < 5) {
            func_001A7DC0(g_0043C57C, 0x80, 1);
        } else {                                /* modes 5-8: buying for slot 0-3 */
            int slot = g_00773148 - 5;          /* (left unset by the original for other modes) */
            help_by_state(g_00773174[g_0077315C * 4 + slot], g_0043C580, g_0043C87C, g_0043C890);
        }
        break;
    case 2:
        if (g_00773138 != 0)
            func_001A7DC0(g_0043C598, 0x80, 1);
        else
            help_by_state(g_0077317D, g_0043C59C, g_0043C888, g_0043C55C);
        break;
    case 3:
    case 4:
        if (func_0029FD10() == 0)
            help_by_state(g_0077317C, g_0043C590, g_0043C88C, g_0043C55C);
        else
            help_by_state(g_0077317C, g_0043C58C, g_0043C880, g_0043C894);
        break;
    case 5: help_by_state(g_00773140, g_0043C594, g_0043C884, 0); break;
    case 6: func_001A7DC0(g_0043C5A0, 0x80, 1); break;
    case 7: help_by_state(g_00773140, g_0043C648, g_0043C55C, 0); break;
    case 8: func_001A7DC0(g_0043C584, 0x80, 1); break;
    case 9: func_001A7DC0(g_007731A0 == 0 ? g_0043C868 : g_0043C86C, 0x80, 1); break;
    }
    func_002AA150(g_00773168, g_00773144, g_0077315C);
}

/* 0x002A5000, 0x80 bytes. Loads the shop's lists; with `reload` 0 (at enter) also the extra ones. */
void func_002A5000(int reload)
{
    g_00773194 = 0;
    g_00773198 = 0;
    func_002CAD60(g_00773130);
    func_002CAD90(g_0077313C);
    func_002A01D0(reload);
    func_002A0920(reload);
    if (reload == 0) {
        func_002A1380();
        func_002A1650();
        func_002A2770();
        func_002A29E0();
    }
}

/* 0x002A01A0, 0x24 bytes. Copies a 16-byte record (three words and the byte at +8). */
void func_002A01A0(u32 *dst, const u32 *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    *(u8 *)&dst[2] = *(const u8 *)&src[2];
    dst[3] = src[3];
}

/* 0x002A1E90, 0x27C bytes. Mode 12 (screen 7, "Select  Back"): a list of g_00773140 entries, cursor
 * g_00773186; Cancel or the third button goes back to mode 3. A held Up/Down stops at the ends, a
 * fresh press wraps around. */
void func_002A1E90(int player)
{
    unsigned short pressed, held;
    u8 count = g_00773140;

    read_pad(player, &pressed, &held);
    if ((pressed & BTN_CANCEL) || (pressed & BTN_EXTRA)) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(3);
    } else if (count > 1) {
        if (held & BTN_UP) {
            if (g_00773186 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = (u8)((g_00773186 + count - 1) % count);
            } else if (pressed & BTN_UP) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = count - 1;
            }
        } else if (held & BTN_DOWN) {
            if (g_00773186 < count - 1) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = (u8)((g_00773186 + 1) % count);
            } else if (pressed & BTN_DOWN) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = 0;
            }
        }
    }
}

/* 0x002A3300, 0x274 bytes. Mode 15 (screen 8, "Select  Back"): a list of g_00773138 entries, cursor
 * g_00773186; Cancel or the third button goes back to mode 2. Unlike mode 12 there is no "more than
 * one entry" test: with 0 entries the original divides by zero. */
void func_002A3300(int player)
{
    unsigned short pressed, held;
    u8 count = (u8)g_00773138;

    read_pad(player, &pressed, &held);
    if ((pressed & BTN_CANCEL) || (pressed & BTN_EXTRA)) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(2);
    } else if (held & BTN_UP) {
        if (g_00773186 != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = (u8)((g_00773186 + count - 1) % count);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = count - 1;
        }
    } else if (held & BTN_DOWN) {
        if (g_00773186 < (u8)(count - 1)) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = (u8)((g_00773186 + 1) % count);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = 0;
        }
    }
}

/* 0x002A3580, 0x3A0 bytes. Mode 1 (screen 1, "Select  Skills  Back  OK"): choose one of the four
 * skill slots of the player (g_00773181). OK on an empty slot plays the error sound, otherwise it
 * goes straight to mode 5 + slot. The third button opens the skill list (mode 9). The 4
 * "unreachable" blocks Ghidra removed are the negative fix-ups of `% 4`. */
void func_002A3580(int player)
{
    unsigned short pressed, held;

    read_pad(player, &pressed, &held);
    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(0);
    } else if (pressed & BTN_OK) {
        if (g_00773174[player * 4 + g_00773181] == 0) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);   /* error */
        } else {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773148 = g_00773181 + 5;
            g_00773186 = 0;
            g_00799A28 = 0;
            g_00799A24 = g_00799A26;
            g_00799A2C = 1;
        }
    } else if (pressed & BTN_EXTRA) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(9);
    } else if (held & BTN_UP) {
        if (g_00773181 != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773181 = (u8)((g_00773181 + 3) % 4);
            func_002A86A0(0x10);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773181 = 3;
            func_002A86A0(0x10);
        }
    } else if (held & BTN_DOWN) {
        if (g_00773181 < 3) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773181 = (u8)((g_00773181 + 1) % 4);
            func_002A86A0(0x10);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773181 = 0;
            func_002A86A0(0x10);
        }
    }
}

#define SKILL_HEADER 0xFF   /* cursor on the header row above the skill columns */

/* 0x002A3920, 0x484 bytes. Mode 9 (screen 9, "All Skills / Own Skills  Select  Back"): the skill
 * list, 4 columns of 10 (cursor g_00773187, column = cursor / 10), with a header row above
 * (g_00773188 remembers the column). L1/R1 swap between all skills and the officer's own skills.
 * Cancel or the third button go back to the mode the list was opened from. */
void func_002A3920(int player)
{
    unsigned short pressed, held;
    u8 cursor = g_00773187;

    read_pad(player, &pressed, &held);
    if ((pressed & BTN_CANCEL) || (pressed & BTN_EXTRA)) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(g_00773150);
    } else if (pressed & BTN_L1R1) {
        func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        g_007731A0 = (g_007731A0 == 0);
        if (g_007731A0 != 0 && func_0036DC30(func_0029FD70(), g_00773187) != 0)
            func_002A86A0(0x11);
    } else if (held & BTN_DOWN) {
        if (g_00773187 == SKILL_HEADER) {
            g_00773187 = (u8)(g_00773188 * 10);
            func_002A86A0(0x11);
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else if (g_00773187 % 10 < 9) {
            g_00773187++;
            func_002A86A0(0x11);
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
    } else if (held & BTN_UP) {
        if (g_00773187 % 10 == 0) {
            g_00773187 = SKILL_HEADER;
            g_00773188 = cursor / 10;
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_002A86A0(0x11);
        } else if (g_00773187 != SKILL_HEADER) {
            g_00773187 = (u8)((g_00773187 + 9) % 10 + (g_00773187 / 10) * 10);
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_002A86A0(0x11);
        }
    } else if (held & BTN_RIGHT) {
        if (g_00773187 != SKILL_HEADER && g_00773187 < 0x1E) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773187 += 10;
            func_002A86A0(0x11);
        }
    } else if (held & BTN_LEFT) {
        if (g_00773187 != SKILL_HEADER && g_00773187 > 9) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773187 -= 10;
            func_002A86A0(0x11);
        }
    }
}

/* 0x002A3DB0, 0x414 bytes. Mode 0 (screen 0, "Select  Back  OK"): the shop's main menu, 3 or 4
 * entries (cursor g_0077317E[player]); OK requests mode cursor + 1. Cancel says goodbye: the
 * shopkeeper's farewell voice is picked at random (0xBB when g_0077318A >= 3, 50 %; 0xBC when
 * g_0077319C == 1, 50 %; else 0xBA) and mode 16 (leave) is requested. Returns 1 when a choice was
 * made. */
int func_002A3DB0(int player)
{
    unsigned short pressed, held;
    int count = func_0029FD20();
    u8 *cursor = &g_0077317E + player;

    if (*cursor >= count)
        *cursor = (u8)(count - 1);
    read_pad(player, &pressed, &held);

    if (pressed & BTN_CANCEL) {
        if (g_0077318A >= 3 && random16() % 100 <= 49) {
            g_00773160 = 0xBB;
            g_00773164 = 0x26;
        } else if (g_0077319C == 1 && random16() % 100 < 50) {
            g_00773160 = 0xBC;
            g_00773164 = 0x27;
        } else {
            g_00773160 = 0xBA;
            g_00773164 = 0x25;
        }
        if (func_0023A260() != 0)
            func_0023AA40();
        func_0023A290(g_00773164);
        func_0029FDB0(16);
        return 1;
    }
    if (pressed & BTN_OK) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(*cursor + 1);
        g_0077315C = player;
        return 1;
    }
    if (held & BTN_UP) {
        if (*cursor != 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            *cursor = (u8)((*cursor + count - 1) % count);
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            *cursor = (u8)(count - 1);
        }
    } else if (held & BTN_DOWN) {
        if (*cursor < count - 1) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            *cursor = (u8)((*cursor + count + 1) % count);
        } else if (pressed & BTN_DOWN) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            *cursor = 0;
        }
    }
    return 0;
}
