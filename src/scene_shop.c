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
extern int g_0077315C;               /* chosen officer? (index of a 0x140-byte record) */
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
#define BTN_CANCEL 0x0010
#define SE_CURSOR 0x2CDC

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
void func_002A3DB0(int value);
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
