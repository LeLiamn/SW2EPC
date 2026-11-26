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

/* Globals 0x0043C3A0-0x0043C898: one object in the original (not reached through $gp). */
extern struct {
    const char *g_0043C3A0;       /* "You do not have enough gold." */
    char pad_0[0x4];
    const char *g_0043C3A8;       /* "Are you sure you want to purchase the skill %s?" */
    char pad_1[0x10];
    const char *g_0043C3BC;       /* "Are you sure you want to hire %s?" */
    char pad_2[0x8];
    const char *g_0043C3C8;       /* "You cannot employ any more officers." */
    char pad_3[0x10];
    const char *g_0043C3DC;       /* "Purchasing %s. Proceed?" */
    char pad_4[0x4];
    const char *g_0043C3E4;       /* "You cannot purchase any more mounts. Would you like to sell one of your current mounts?" */
    char pad_5[0x38];
    const char *g_0043C420;       /* "Selling %s. Proceed?" */
    char pad_6[0x138];
    const char *g_0043C55C;       /* "Back" */
    char pad_7[0x18];
    const char *g_0043C578;       /* "Select  Back  OK" */
    const char *g_0043C57C;       /* "Select  Skills  Back  OK" */
    const char *g_0043C580;       /* "Select  Skills  Back  Buy" */
    const char *g_0043C584;       /* "Select  Back" */
    char pad_8[0x4];
    const char *g_0043C58C;       /* "Select  Mounts  Back  Buy" */
    const char *g_0043C590;       /* "Select  Back  Buy" */
    const char *g_0043C594;       /* "Select  Back  Sell" */
    const char *g_0043C598;       /* "Select  Guards  Back  Hire" */
    const char *g_0043C59C;       /* "Select  Back  Hire" */
    const char *g_0043C5A0;       /* "Select  Back  Dismiss" */
    char pad_9[0xA4];
    const char *g_0043C648;       /* "Select  Back" */
    char pad_10[0x21C];
    const char *g_0043C868;       /* "All Skills  Select  Back" */
    const char *g_0043C86C;       /* "Own Skills  Select  Back" */
    char pad_11[0xC];
    const char *g_0043C87C;       /* "Skills  Back  Buy" */
    const char *g_0043C880;       /* "Mounts  Back  Buy" */
    const char *g_0043C884;       /* "Back  Sell" */
    const char *g_0043C888;       /* "Back  Hire" */
    const char *g_0043C88C;       /* "Back  Buy" */
    const char *g_0043C890;       /* "Skills  Back" */
    const char *g_0043C894;       /* "Mounts  Back" */
} s_0043C3A0;
#define g_0043C3A0 (s_0043C3A0.g_0043C3A0)
#define g_0043C3A8 (s_0043C3A0.g_0043C3A8)
#define g_0043C3BC (s_0043C3A0.g_0043C3BC)
#define g_0043C3C8 (s_0043C3A0.g_0043C3C8)
#define g_0043C3DC (s_0043C3A0.g_0043C3DC)
#define g_0043C3E4 (s_0043C3A0.g_0043C3E4)
#define g_0043C420 (s_0043C3A0.g_0043C420)
#define g_0043C55C (s_0043C3A0.g_0043C55C)
#define g_0043C578 (s_0043C3A0.g_0043C578)
#define g_0043C57C (s_0043C3A0.g_0043C57C)
#define g_0043C580 (s_0043C3A0.g_0043C580)
#define g_0043C584 (s_0043C3A0.g_0043C584)
#define g_0043C58C (s_0043C3A0.g_0043C58C)
#define g_0043C590 (s_0043C3A0.g_0043C590)
#define g_0043C594 (s_0043C3A0.g_0043C594)
#define g_0043C598 (s_0043C3A0.g_0043C598)
#define g_0043C59C (s_0043C3A0.g_0043C59C)
#define g_0043C5A0 (s_0043C3A0.g_0043C5A0)
#define g_0043C648 (s_0043C3A0.g_0043C648)
#define g_0043C868 (s_0043C3A0.g_0043C868)
#define g_0043C86C (s_0043C3A0.g_0043C86C)
#define g_0043C87C (s_0043C3A0.g_0043C87C)
#define g_0043C880 (s_0043C3A0.g_0043C880)
#define g_0043C884 (s_0043C3A0.g_0043C884)
#define g_0043C888 (s_0043C3A0.g_0043C888)
#define g_0043C88C (s_0043C3A0.g_0043C88C)
#define g_0043C890 (s_0043C3A0.g_0043C890)
#define g_0043C894 (s_0043C3A0.g_0043C894)

/* 0x00500700: the controllers' state, 0x88 bytes per controller. */
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
#define g_0050074C (g_00500700[0].pressed)
#define g_00500764 (g_00500700[0].ready)
#define g_00500765 (g_00500700[0].connected)

/* Globals 0x00669D82-0x00669D83: one object in the original (not reached through $gp). */
extern struct {
    char g_00669D82;              /* 3: everything is a bargain on this visit (cleared after) */
    char size_unknown[8];   /* the whole object is larger (not reached through $gp) */
} s_00669D82;
#define g_00669D82 (s_00669D82.g_00669D82)

/* Globals 0x006934B3-0x0069395F: one object in the original (not reached through $gp). */
extern struct {
    char g_006934B3;
    char pad_0[0x127];
    char g_006935DB;
    char pad_1[0x382];
    u8 g_0069395E;    /* message box 1 open when neither 0 nor -1 */
} s_006934B3;
#define g_006934B3 (s_006934B3.g_006934B3)
#define g_006935DB (s_006934B3.g_006935DB)
#define g_0069395E (s_006934B3.g_0069395E)

/* Globals 0x00773138-0x007731A4: one object in the original (not reached through $gp). */
extern struct {
    u8 g_00773138;                /* (inside it) non-zero: the "Guards" variant of the hire screen */
    char pad_0[0x7];
    u8 g_00773140;                /* (inside it) cursor of screens 5 and 7 */
    char pad_1[0x3];
    int g_00773144;               /* screen being drawn (0..9) */
    int g_00773148;               /* current mode (0..16) */
    int g_0077314C;               /* requested mode */
    int g_00773150;               /* mode before the last request */
    int g_00773154;               /* phase: 0 opening, 1 leaving with a sound, 2 leaving, 3 running */
    int g_00773158;               /* scene we came from */
    int g_0077315C;               /* player using the shop (0 or 1): picks the controller and the 0x140-byte record of g_00772DF0 */
    int g_00773160;               /* shopkeeper picture? (0xB5..0xB9) */
    int g_00773164;               /* shopkeeper sound bank? (0x20..0x24) */
    u32 g_00773168;
    u32 g_0077316C;
    u32 g_00773170;
    char pad_2[0x8];
    u8 g_0077317C;
    u8 g_0077317D;
    u8 g_0077317E;
    u8 g_0077317F;
    char pad_3[0x1];
    u8 g_00773181;
    char pad_4[0x1];
    u8 g_00773183;
    u8 g_00773184;
    u8 g_00773185;
    u8 g_00773186;
    u8 g_00773187;
    u8 g_00773188;
    u8 g_00773189;
    u8 g_0077318A;
    u8 g_0077318B;              /* non-zero: func_002D6890 succeeded at enter */
    int g_0077318C;
    int g_00773190;
    int g_00773194;
    int g_00773198;
    int g_0077319C;
    int g_007731A0;
} s_00773138;
#define g_00773138 (s_00773138.g_00773138)
#define g_00773140 (s_00773138.g_00773140)
#define g_00773144 (s_00773138.g_00773144)
#define g_00773148 (s_00773138.g_00773148)
#define g_0077314C (s_00773138.g_0077314C)
#define g_00773150 (s_00773138.g_00773150)
#define g_00773154 (s_00773138.g_00773154)
#define g_00773158 (s_00773138.g_00773158)
#define g_0077315C (s_00773138.g_0077315C)
#define g_00773160 (s_00773138.g_00773160)
#define g_00773164 (s_00773138.g_00773164)
#define g_00773168 (s_00773138.g_00773168)
#define g_0077316C (s_00773138.g_0077316C)
#define g_00773170 (s_00773138.g_00773170)
#define g_0077317C (s_00773138.g_0077317C)
#define g_0077317D (s_00773138.g_0077317D)
#define g_0077317E (s_00773138.g_0077317E)
#define g_0077317F (s_00773138.g_0077317F)
#define g_00773181 (s_00773138.g_00773181)
#define g_00773183 (s_00773138.g_00773183)
#define g_00773184 (s_00773138.g_00773184)
#define g_00773185 (s_00773138.g_00773185)
#define g_00773186 (s_00773138.g_00773186)
#define g_00773187 (s_00773138.g_00773187)
#define g_00773188 (s_00773138.g_00773188)
#define g_00773189 (s_00773138.g_00773189)
#define g_0077318A (s_00773138.g_0077318A)
#define g_0077318B (s_00773138.g_0077318B)
#define g_0077318C (s_00773138.g_0077318C)
#define g_00773190 (s_00773138.g_00773190)
#define g_00773194 (s_00773138.g_00773194)
#define g_00773198 (s_00773138.g_00773198)
#define g_0077319C (s_00773138.g_0077319C)
#define g_007731A0 (s_00773138.g_007731A0)

/* Globals 0x00780494-0x00780498: one object in the original (not reached through $gp). */
extern struct {
    u32 g_00780494;
    char size_unknown[5];   /* the whole object is larger (not reached through $gp) */
} s_00780494;
#define g_00780494 (s_00780494.g_00780494)

/* Globals 0x00799A24-0x00799A6C: one object in the original (not reached through $gp). */
extern struct {
    unsigned char g_00799A24;
    char pad_0[0x1];
    unsigned char g_00799A26;
    char pad_1[0x1];
    int g_00799A28;
    int g_00799A2C;
    char pad_2[0x38];
    u32 g_00799A68;
} s_00799A24;
#define g_00799A24 (s_00799A24.g_00799A24)
#define g_00799A26 (s_00799A24.g_00799A26)
#define g_00799A28 (s_00799A24.g_00799A28)
#define g_00799A2C (s_00799A24.g_00799A2C)
#define g_00799A68 (s_00799A24.g_00799A68)


/* 0x7000015C: random seed in the scratchpad (set to 12345 at start-up, see main.c). */
#define g_7000015C (*(u32 *)0x7000015C)

/* Shop state. */
extern u8 g_00773130[];              /* data block filled by func_002CAD60 */
extern u8 g_0077313C[];              /* data block filled by func_002CAD90 */
extern u8 g_00773174[];              /* 4 bytes per officer: state of slots 0-3 (0, 1 or more) */
extern u8 g_00772DF0[];              /* 0x140 bytes per officer, 0x50 per slot */
extern u8 g_00773070[], g_007730D0[];
extern u8 g_00440CD8[];
extern u8 g_0045CEA8[8];            /* (small data: reached through $gp) */
extern int g_0045CE98, g_0045CE9C;   /* a pair saved at enter and restored at leave */

/* Controller 1 (see scene_config.c). */
#define BTN_L1R1   0x000C            /* L1 or R1 (swap "All Skills" / "Own Skills") */
#define BTN_CANCEL 0x0010
#define BTN_EXTRA  0x0020            /* the third face button ("Skills", "Mounts", "Guards") */
#define BTN_OK     0x0040
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000
#define SE_CURSOR 0x2CDC

/* Reading a player's controller, inlined in the original (a macro). `player` picks the controller
 * (the original leaves it unset, and the pad unread, when player is neither 0 nor 1). */
#define pad_ready(ps) (((ps)->ready & 1) ? ((ps)->connected & 1) == 1 : 0)
#define read_pad(player, pressed, held) do {                                        \
        int port_;                                                                  \
        PadState *ps_;                                                              \
        if ((player) == 0) port_ = 0; else if ((player) == 1) port_ = 1;            \
        ps_ = &g_00500700[port_];                                                   \
        pressed = (unsigned short)(pad_ready(ps_) ? g_00500700[port_].pressed : 0); \
        held = (unsigned short)(pad_ready(ps_) ? g_00500700[port_].held : 0);       \
    } while (0)

extern u8 g_007731D0[];              /* 0x24-byte records */
extern int g_0045D56C;               /* (gp - 0x7684) officer shown by the skill list, 0x19F = none */

#define OFFICER_NONE 0x19F

void func_00376100(int a, int b, int c);
void func_002A86A0(int value);
int func_0036DC30(u32 officer, u8 skill);

/* Button help lines (0xF0 + letter = a button icon). */

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
int func_002A2EF0(int player);
void func_002A18D0(int officer);
void func_002A21B0(int player, int back);
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

/* Inlined in the original: a macro. */
#define pad1_ready() ((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_0050074C : 0))

/* Next value of the game's random generator (a linear congruential generator, 0..65535), inlined
 * in the original (a macro). */
#define random16() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 16) & 0xFFFF)

/* 0x0029FD10, 0x10 bytes, matching. Non-zero when the shop also sells mounts. */
int func_0029FD10(void)
{
    return g_00773140 > 0;
}

/* 0x0029FD20, 0x30 bytes, matching. Number of entries of the shop's main menu: 4 with mounts, else 3. */
int func_0029FD20(void)
{
    return func_0029FD10() != 0 ? 4 : 3;
}

/* 0x0029FD50, 0x20 bytes, matching. Sets the officer shown by the skill list when `officer` is valid
 * (0..0x19E), and returns the current one. */
int func_0029FD50(int officer)
{
    if (officer >= 0 && officer < OFFICER_NONE)
        g_0045D56C = officer;
    return g_0045D56C;
}

/* 0x0029FD70, 0x1C bytes, matching. The officer shown by the skill list. */
u32 func_0029FD70(void)
{
    return func_0029FD50(OFFICER_NONE);
}

/* 0x0029FD90, 0x1C bytes, matching. Record `index` of the 0x24-byte table at 0x007731D0. */
void *func_0029FD90(int index)
{
    return &g_007731D0[index * 0x24];
}

/* 0x0029FDB0, 0x9C bytes, matching. Requests mode `mode` (applied by func_0029FE50 on the next update) and
 * moves the layout layer to the mode's position: modes 1-4 use layers 5-8, mode 11 layer 8. */
void func_0029FDB0(int mode)
{
    int layer;

    g_00773150 = g_00773148;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        break;
    case 16:
        g_00780494 = 1;
        break;
    }
    g_00773154 = 1;
    layer = -1;
    g_0077314C = mode;
    if (mode > 0 && mode < 5)
        layer = mode + 4;
    if (mode == 11)
        layer = 8;
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

/* 0x002A41D0, 0x40 bytes, matching. Places the shop's layout layers. */
void func_002A41D0(void)
{
    func_00375C20(0, g_00773168, 2, g_0045CEA8, 1);
    func_00376100(3, 4, -1);
}

/* 0x002A4210, 0x33C bytes, matching. Scene enter. Picks a shopkeeper at random: 0xB9 (50 %) or 0xB8 (25 %)
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

/* 0x002A4550, 0x84 bytes, matching. Scene leave. */
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

/* 0x002A45E0, 0x1C bytes, matching. Scene leave_alt (used when another scene was requested). */
void func_002A45E0(void)
{
    func_00375D60();
}

/* 0x002A4600, 0x334 bytes. Scene update: phases, then the current mode's handler. */
int func_002A4600(float dt)
{
    int pressed = pad1_pressed();

    func_00376450();
    if (func_00102960(0) == 0)
        return 1;

    if (g_00773154 == 2) {                      /* leaving: wait for the music and message box */
        if (func_0017DDA0() != 0)
            return 1;
        if (g_0069395E != 0 && g_0069395E != 0xFF)
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

/* 0x002A4940, 8 bytes, matching. Scene step: empty. */
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

/* 0x002A5000, 0x80 bytes, matching. Loads the shop's lists; with `reload` 0 (at enter) also the extra ones. */
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

/* 0x002A01A0, 0x24 bytes, matching. Copies a 16-byte record (three words and the byte at +8). */
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
    int pressed, held;
    u8 count = g_00773140;

    read_pad(player, pressed, held);
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

/* 0x002A3300, 0x274 bytes, matching. Mode 15 (screen 8, "Select  Back"): a list of g_00773138 entries, cursor
 * g_00773186; Cancel or the third button goes back to mode 2. Unlike mode 12 there is no "more than
 * one entry" test: with 0 entries the original divides by zero. */
void func_002A3300(int player)
{
    int pressed, held;

    read_pad(player, pressed, held);
    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(2);
    } else if (pressed & BTN_EXTRA) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(2);
    } else if (held & BTN_UP) {
        if (g_00773186 > 0) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = (g_00773186 + (u8)g_00773138 - 1) % (u8)g_00773138;
        } else if (pressed & BTN_UP) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = g_00773138 - 1;
        }
    } else if (held & BTN_DOWN) {
        if (g_00773186 < (u8)(g_00773138 - 1)) {
            func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            g_00773186 = (g_00773186 + 1) % (u8)g_00773138;
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
    int pressed, held;

    read_pad(player, pressed, held);
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
    int pressed, held;
    u8 cursor = g_00773187;

    read_pad(player, pressed, held);
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
    int pressed, held;
    int count = func_0029FD20();
    u8 *cursor = &g_0077317E + player;

    if (*cursor >= count)
        *cursor = (u8)(count - 1);
    read_pad(player, pressed, held);

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

/* ---- Gold, prices and confirmation boxes ------------------------------------------------------ */

/* Message boxes: two records of 0x128 bytes; +0 (0x006934B3 / 0x006935DB) non-zero while the box is
 * open, +1 (0x006934B4...) the answer (4 = yes). Box 0 shows a message, box 1 asks yes / no. */
extern char g_006934B4[];
#define BOX_NONE 5
#define BOX_YES  4


void func_001204B0(char *dst, const char *format, ...);   /* sprintf */
void func_001AE9F0(int box, const char *text, int c);     /* open a message box */
void func_001AFC70(int box, int player);                  /* give the box to a player's controller */
void func_001AFFB0(void);                                 /* close the yes / no box */
u32 func_00327D50(void);                                  /* the player's force? */
int func_002F9190(u32 force);                             /* its gold */
void func_002F90D0(u32 force, int amount);                /* add gold (in tens) */
void func_002F9130(u32 force, int amount);                /* remove gold (in tens) */
void func_0039F960(void);
u8 *func_0019FBC0(int item);                              /* item record (name at +0x13) */
int func_002F3F20(int officer);
int func_00300560(int *slot_a, int *slot_b);
void func_002F7300(int officer, u32 force, int slot, int kind);
void func_002A85C0(int officer);
const char *func_002A85D0(int officer);                   /* officer name */
int func_002C5220(int player, u8 *top, u8 *cursor, u8 rows, u8 count);   /* scrolling list */
u32 func_001A0670(void);
int func_001A06D0(void);
void func_0019FD50(u32 a, void *mount);
int func_003DD680(int player);                            /* mount the player rides */
void func_003DD660(int player, int mount);

/* Which message box is open (0, 1 or BOX_NONE), and its answer. */
static int open_box(char *answer)
{
    int box = BOX_NONE;

    if (g_006934B3 != 0)
        box = 0;
    else if (g_006935DB != 0)
        box = 1;
    *answer = (box == BOX_NONE) ? 0 : g_006934B4[box * 0x128];
    return box;
    /* (the handlers then test the state of a box other than 0, 1 and BOX_NONE: dead code, left
     * out here) */
}

/* Shows `text` in box `box` for the player's controller. */
static void show_box(int box, int player, const char *format, const char *name)
{
    char text[256];

    func_001204B0(text, format, name);
    func_001AE9F0(box, text, 1);
    func_001AFC70(box, player);
}

/* 0x0029FB70, 0x24 bytes, matching. The player's gold. */
int func_0029FB70(void)
{
    return func_002F9190(func_00327D50());
}

/* 0x0029FBA0, 0x94 bytes, matching. Adds `amount` gold (negative: spends it); gold is kept in tens. */
void func_0029FBA0(int amount)
{
    if (amount > 0)
        func_002F90D0(func_00327D50(), amount / 10);
    else
        func_002F9130(func_00327D50(), -amount / 10);
    func_0039F960();
}

/* 0x0029FC40, 0xC4 bytes, matching. Selling price of a mount: 5000 for type 0x0C, 4000 for 0x0D-0x0F, else
 * (rank + 1) * 100 + 1400 when byte +6 is 3, or + 900. */
int func_0029FC40(int mount)
{
    u8 type = func_0019FBC0(mount)[5];
    int rank;

    if (type == 0x0C)
        return 5000;
    if (type == 0x0D)
        return 4000;
    if ((unsigned)(type - 0x0E) < 2)
        return 4000;
    rank = func_0019FBC0(mount)[8] + 1;
    if (func_0019FBC0(mount)[6] == 3)
        return rank * 100 + 0x578;
    return rank * 100 + 900;
}

/* ---- Mode 3: buy mounts ------------------------------------------------------------------------ */

/* Mounts for sale: 8 records of 12 bytes at 0x00773070: +0 price, +4 index of the mount record
 * in g_007731D0 (0x10 = sold), +8 non-zero for the day's bargain (20 % off). */
typedef struct {
    int price;
    u8 index;
    u8 pad[3];
    int bargain;
} MountOffer;
#define g_MountOffers ((MountOffer *)g_00773070)

/* 0x002A1740, 0x1C bytes, matching. Copies a mount offer. */
void func_002A1740(MountOffer *dst, const MountOffer *src)
{
    dst->index = src->index;
    dst->price = src->price;
    dst->bargain = src->bargain;
}

/* 0x002A1760, 0x16C bytes. Buys the mount under the cursor (g_00773183): pays, gives it to the
 * player and removes it from the offers (the last offer becomes "sold"). */
void func_002A1760(void)
{
    MountOffer *offer = &g_MountOffers[g_00773183];
    void *mount;
    u32 owner;
    int i;

    func_0029FBA0(-offer->price);
    g_0077318A++;                               /* purchases this visit (farewell voice) */
    mount = func_0029FD90(offer->index);
    owner = func_001A0670();
    if (func_001A06D0() != 0) {
        func_0019FD50(owner, mount);
        for (i = g_00773183; i < 7; i++)
            func_002A1740(&g_MountOffers[i], &g_MountOffers[i + 1]);
        g_MountOffers[i].index = 0x10;
        g_0077317C--;
        if (g_0077317C != 0 && g_00773183 > g_0077317C - 1)
            g_00773183 = g_0077317C - 1;
        func_002CAD90(g_0077313C);
    }
}

/* 0x002A18D0, 0x5BC bytes. Mode 3 (screen 3, "Select  Mounts  Back  Buy"): the mounts for sale
 * (g_0077317C offers, cursor g_00773183). OK asks to confirm (or explains why not); "yes" buys,
 * or, when the player already has 4 mounts, opens the sell screen (mode 11). The third button
 * shows the player's mounts (mode 12). */
void func_002A18D0(int player)
{
    int pressed, held;
    char answer;
    int box;

    read_pad(player, pressed, held);
    box = open_box(&answer);
    if (box == 0)
        return;
    if (box == 1) {
        if (answer == BOX_YES) {
            if (g_00773140 < 4)
                func_002A1760();
            else
                func_0029FDB0(11);
        } else if (pressed & BTN_CANCEL) {
            func_001AFFB0();
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
        return;
    }

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(0);
    } else if (pressed & BTN_OK) {
        MountOffer *offer = &g_MountOffers[g_00773183];
        if (g_0077317C == 0 || offer->index == 0x10) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else if (func_0029FB70() < offer->price) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(0, player, g_0043C3A0, 0);
        } else if (g_00773140 < 4) {
            const char *name = (const char *)func_0029FD90(offer->index) + 0x13;
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(1, player, g_0043C3DC, name);
        } else {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(1, player, g_0043C3E4, 0);
        }
    } else if (pressed & BTN_EXTRA) {
        if (func_0029FD10() != 0) {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_0029FDB0(12);
        }
    } else if (g_0077317C > 1) {
        u8 count = g_0077317C;
        if (held & BTN_UP) {
            if (g_00773183 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773183 = (u8)((g_00773183 + count - 1) % count);
            } else if (pressed & BTN_UP) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773183 = count - 1;
            }
        } else if (held & BTN_DOWN) {
            if (g_00773183 < count - 1) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773183 = (u8)((g_00773183 + 1) % count);
            } else if (pressed & BTN_DOWN) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773183 = 0;
            }
        }
    }
}

/* ---- Modes 4 and 11: sell a mount -------------------------------------------------------------- */

/* The player's mounts: g_0077313C[0..3], count g_00773140. */

/* 0x002A2110, 0x9C bytes, matching. Sells the player's mount under the cursor (g_00773186): adds its price
 * to the gold, frees it, and unmounts the player if it was the one ridden. */
void func_002A2110(int player)
{
    int mount = g_0077313C[g_00773186];
    int price = func_0029FC40(mount);
    int ridden = func_003DD680(player);

    func_0029FBA0(price);
    func_0019FBC0(mount)[4] = 4;
    if (ridden == mount)
        func_003DD660(player, 4);
    func_002CAD90(g_0077313C);
}

/* 0x002A21B0, 0x488 bytes. Modes 4 and 11 (screen 5, "Select  Back  Sell"): the player's mounts;
 * OK asks to confirm, "yes" sells. Leaving goes to `back` (mode 0 from the menu, mode 3 when the
 * player was buying with 4 mounts already). */
void func_002A21B0(int player, int back)
{
    int pressed, held;
    char answer;
    int box;

    read_pad(player, pressed, held);
    box = open_box(&answer);
    if (box == 0)
        return;
    if (box == 1) {
        if (answer == BOX_YES) {
            func_002A2110(player);
            if (func_0029FD10() == 0)
                func_0029FDB0(back);
            if (func_0029FD10() == 0) {         /* (asked twice in the original) */
                g_00773186 = 0;
                func_0029FDB0(back);
            } else if (g_00773186 > g_00773140 - 1) {
                g_00773186 = g_00773140 - 1;
            }
        }
        return;
    }

    if (func_0029FD10() == 0) {                 /* nothing left to sell */
        func_0029FDB0(back);
    } else if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(back);
    } else if (pressed & BTN_OK) {
        if (func_0029FD10() == 0) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else {
            const char *name = (const char *)func_0019FBC0(g_0077313C[g_00773186]) + 0x13;
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(1, player, g_0043C420, name);
        }
    } else if (g_00773140 > 1) {
        u8 count = g_00773140;
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

/* ---- Mode 2: hire officers --------------------------------------------------------------------- */

/* Officers for hire: records of 12 bytes at 0x007730D0: +0 price, +4 officer (0x19F = none),
 * +8 1 for the day's bargain (20 % off), +9 non-zero when the player has room for him. */
typedef struct {
    int price;
    int officer;
    u8 bargain;
    u8 can_hire;
    u8 pad[2];
} HireOffer;
#define g_HireOffers ((HireOffer *)g_007730D0)
#define SLOT_COUNT 0x19          /* officer slots 0..24 */

/* 0x002A2AE0, 0x1C bytes, matching. Copies a hire offer. */
void func_002A2AE0(HireOffer *dst, const HireOffer *src)
{
    *dst = *src;
}

/* 0x002A2B00, 0x8C bytes, matching. Can `officer` be hired? `slot_a` / `slot_b` are the free slots found by
 * func_00300560 (0..24, else none) and `room` its result. */
int func_002A2B00(int officer, int slot_a, int slot_b, int room)
{
    if (room < 1)
        return 0;
    if ((slot_a < 0 || slot_a >= SLOT_COUNT) && (slot_b < 0 || slot_b >= SLOT_COUNT))
        return 0;
    if (func_002F3F20(officer) != 0 && (slot_a < 0 || slot_a >= SLOT_COUNT))
        return 0;
    return 1;
}

/* 0x002A2B90, 0x4C bytes, matching. Can `officer` be hired now? */
int func_002A2B90(int officer)
{
    int slot_a = SLOT_COUNT, slot_b = SLOT_COUNT;
    int room = func_00300560(&slot_a, &slot_b);

    return func_002A2B00(officer, slot_a, slot_b, room);
}

/* 0x002A2BE0, 0x308 bytes. Hires the officer under the cursor (g_00773185): pays, places him in a
 * free slot, removes him from the offers and updates which offers can still be hired. */
void func_002A2BE0(void)
{
    int slot_a = SLOT_COUNT, slot_b = SLOT_COUNT;
    int officer, room, i;

    func_00300560(&slot_a, &slot_b);
    officer = g_HireOffers[g_00773185].officer;
    func_0029FBA0(-g_HireOffers[g_00773185].price);
    if (func_002F3F20(officer) != 0 && slot_a >= 0 && slot_a < SLOT_COUNT)
        func_002F7300(officer, func_00327D50(), slot_a, 2);
    else if (slot_b >= 0 && slot_b < SLOT_COUNT)
        func_002F7300(officer, func_00327D50(), slot_b, 1);
    else if (slot_a >= 0 && slot_a < SLOT_COUNT)
        func_002F7300(officer, func_00327D50(), slot_a, 2);
    func_002A85C0(officer);
    g_0077318A++;                               /* purchases this visit (farewell voice) */

    for (i = g_00773185; i < g_0077317D - 1; i++)
        func_002A2AE0(&g_HireOffers[i], &g_HireOffers[i + 1]);
    g_HireOffers[g_0077317D].officer = OFFICER_NONE;   /* (one past the last offer: as in the original) */
    g_0077317D--;

    if (g_0077317D < 8) {                       /* the whole list fits: no scrolling */
        int last = g_0077317D - 1;
        g_00773184 = g_00773185 = (u8)(g_00773185 <= last ? g_00773185 : last);
    } else if (g_0077317D - 8 < g_00773185 - g_00773184) {
        g_00773185--;
    }

    room = func_00300560(&slot_a, &slot_b);
    for (i = 0; i < g_0077317D; i++)
        g_HireOffers[i].can_hire = (u8)func_002A2B00(g_HireOffers[i].officer, slot_a, slot_b, room);
    g_00773138++;
    func_002CAD60(g_00773130);
}

/* 0x002A2EF0, 0x410 bytes. Mode 2 (screen 2, "Select  Back  Hire"): officers for hire, a list of
 * g_0077317D offers shown 8 at a time (top g_00773184, cursor g_00773185). OK asks to confirm (or
 * explains why not); "yes" hires. Returns what the list scrolling returns. */
int func_002A2EF0(int player)
{
    int pressed, held;
    u8 rows = g_0077317D > 7 ? 8 : g_0077317D;
    char answer;
    int box;

    read_pad(player, pressed, held);
    box = open_box(&answer);
    if (box == 0)
        return 0;
    if (box == 1) {
        if (answer == BOX_YES) {
            func_002A2BE0();
            return 1;
        }
        if (pressed & BTN_CANCEL) {
            func_001AFFB0();
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
        return 0;
    }

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(0);
    } else if (pressed & BTN_OK) {
        int officer;
        if (g_0077317D == 0)
            return 0;
        officer = g_HireOffers[g_00773185].officer;
        if (officer == OFFICER_NONE) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            return 0;
        }
        if (func_0029FB70() < g_HireOffers[g_00773185].price) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(0, player, g_0043C3A0, 0);
        } else if (func_002A2B90(officer) == 0) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(0, player, g_0043C3C8, 0);
        } else {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(1, player, g_0043C3BC, func_002A85D0(officer));
        }
    } else if (g_0077317D < 2) {
        return 0;
    }
    return func_002C5220(player, &g_00773184, &g_00773185, rows, g_0077317D);
}

/* ---- Modes 5 to 8: buy a skill for slot 0 to 3 ------------------------------------------------- */

/* Skills for sale: g_00772DF0[player * 0x140 + slot * 0x50] = 5 records of 16 bytes:
 * +0 skill (0x28 = none), +4 price. Their count is g_00773174[player * 4 + slot]. */
typedef struct {
    int skill;
    int price;
    u8 level;                /* level the officer reaches by buying it */
    u8 pad[3];
    int bargain;             /* 1: the day's bargain (20 % off) */
} SkillOffer;
#define SKILL_NONE 0x28

extern const char *g_0042D3E0[];     /* skill names ("Vitality", "Focus", "Potence"...) */
extern u8 g_004281B8[];              /* skill table, 8 bytes per skill (+5: kind) */

int func_002F47A0(u32 officer, int skill);                /* skill level */
void func_002F4820(u32 officer, int skill, int level);

/* Back to the slot choice (mode 1). */
static void back_to_slots(void)
{
    g_00799A28 = 1;
    g_00799A24 = g_00799A26;
    g_00799A2C = 0;
    func_0029FDB0(1);
}

/* 0x002A0B40, 0x838 bytes. Modes 5-8 (screen 1, "Select  Skills  Back  Buy"): the skills for sale
 * in one slot. OK asks to confirm; "yes" raises the skill of the officer shown by one level, pays,
 * and removes the offer (back to the slots when none is left). The third button opens the skill
 * list (mode 9). */
void func_002A0B40(int player)
{
    int pressed, held;
    int slot = g_00773148 - 5;                  /* (left unset by the original for other modes) */
    SkillOffer *offers = (SkillOffer *)&g_00772DF0[g_0077315C * 0x140 + slot * 0x50];
    u8 *count = &g_00773174[player * 4 + slot];
    char answer;
    int box;

    read_pad(player, pressed, held);
    box = open_box(&answer);
    if (box == 0)
        return;
    if (box == 1) {
        if (answer == BOX_YES) {
            int skill = offers[g_00773186].skill;
            int level = func_002F47A0(func_0029FD70(), skill);
            int i;

            func_002F4820(func_0029FD70(), skill, level + 1);
            func_0029FBA0(-offers[g_00773186].price);
            if (g_004281B8[skill * 8 + 5] == 3)
                g_0077319C = 1;                 /* changes the farewell voice */
            g_0077318A++;
            for (i = g_00773186; i < 4; i++)
                func_002A01A0((u32 *)&offers[i], (const u32 *)&offers[i + 1]);
            offers[i].skill = SKILL_NONE;
            (*count)--;
            if (*count != 0 && g_00773186 > *count - 1)
                g_00773186 = *count - 1;
            func_002A0920(g_0077315C);
            if (*count == 0)
                back_to_slots();
        } else if (pressed & BTN_CANCEL) {
            func_001AFFB0();
            func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        }
        return;
    }

    if (pressed & BTN_CANCEL) {
        func_0023AD10(2, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        back_to_slots();
    } else if (pressed & BTN_OK) {
        int skill;
        if (*count == 0) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            return;
        }
        skill = offers[g_00773186].skill;
        if (skill == SKILL_NONE) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        } else if (func_0029FB70() < offers[g_00773186].price) {
            func_0023AD10(4, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            show_box(0, player, g_0043C3A0, 0);
        } else {
            func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
            func_002F47A0(func_0029FD70(), skill);   /* result unused (as in the original) */
            show_box(1, player, g_0043C3A8, g_0042D3E0[skill]);
        }
    } else if (held & BTN_EXTRA) {
        func_0023AD10(1, 0, SE_CURSOR, SE_CURSOR, 0x1000);
        func_0029FDB0(9);
    } else if (*count > 1) {
        u8 n = *count;
        if (held & BTN_UP) {
            if (g_00773186 != 0) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = (u8)((g_00773186 + n - 1) % n);
            } else if (pressed & BTN_UP) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = n - 1;
            }
        } else if (held & BTN_DOWN) {
            if (g_00773186 < n - 1) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = (u8)((g_00773186 + 1) % n);
            } else if (pressed & BTN_DOWN) {
                func_0023AD10(0, 0, SE_CURSOR, SE_CURSOR, 0x1000);
                g_00773186 = 0;
            }
        }
    }
}

/* ---- Building the day's offers and their prices ----------------------------------------------- */

/* The skill table: 8 bytes per skill at 0x004281B8; +4 the slot it belongs to (0-3, else none),
 * +5 its kind (1 and 2 suit one officer type each, 3 = special). */
#define SKILL_SLOT(s) g_004281B8[(s) * 8 + 4]
#define SKILL_KIND(s) g_004281B8[(s) * 8 + 5]
#define SKILL_COUNT 0x28

typedef struct { u8 type[6]; } MountTypes;
extern MountTypes g_0045CEA0;         /* (gp - 0x7D50) the six mounts on sale by default */

int func_002F67B0(u32 officer);                           /* officer type (1 or 2) */
void func_001A0630(void *record, u8 mount);
void func_00372E60(const char **names, int count);
void func_00120928(char *dst, const char *src);           /* strcpy */
int func_003003C0(int *slot_a, int *slot_b, int *room, int *d);
int func_002F7D90(int a, void *filter, int c, int d, int e, int f);
int *func_002F7B10(void);
void func_002F7C40(int *list, int count);
void func_002F85E0(void);
int func_002F41E0(int officer);                           /* officer level */
int func_00327E50(void);
int func_002FB3B0(u32 force);
int func_002FB430(u32 force);
int func_00309FB0(void);

/* The level-4 "ultimate" form of skills 9, 0x13 and 0x25: fixed price, never a bargain. */
static int is_ultimate(const SkillOffer *o)
{
    return (o->skill == 9 || o->skill == 0x13 || o->skill == 0x25) && o->level == 4;
}

/* 0x002A01D0, 0x744 bytes. Fills the four skill slots of `player`'s shop list for the officer
 * shown: every skill below level 3 of the slot (kind 3 never; a skill of the other officer type
 * only 25 % of the time), sorted by level then skill number, at most 5 per slot (a full slot drops
 * a random offer, except an ultimate, to make room). Then picks the day's bargain. */
void func_002A01D0(int player)
{
    SkillOffer *base = (SkillOffer *)&g_00772DF0[player * 0x140];
    int filled[4];
    int type, skill, s, k, total;
    unsigned pick, index;

    for (s = 0; s < 4; s++) {
        for (k = 0; k < 5; k++) {
            base[s * 5 + k].skill = SKILL_NONE;
            base[s * 5 + k].level = 0;
        }
        filled[s] = 0;
    }
    type = func_002F67B0(func_0029FD70());

    for (skill = 0; skill < SKILL_COUNT; skill++) {
        u8 slot = SKILL_SLOT(skill);
        u8 kind;
        SkillOffer *row;
        int n;

        if (slot >= 4 || (u8)func_002F47A0(func_0029FD70(), skill) >= 3)
            continue;
        kind = SKILL_KIND(skill);
        if (kind == 3)
            continue;
        if (((type == 1 && kind == 2) || (type == 2 && kind == 1)) && random16() % 100 >= 25)
            continue;
        row = &base[slot * 5];
        n = filled[slot];
        if (n >= 5) {                           /* full: drop a random offer to make room */
            unsigned r = random16() % 6;
            if (r >= 5)
                continue;
            if (row[r].skill == 9 || row[r].skill == 0x13 || row[r].skill == 0x25)
                continue;
            for (; r < 4; r++)
                func_002A01A0((u32 *)&row[r], (const u32 *)&row[r + 1]);
            row[r].skill = SKILL_NONE;
            n = 4;
        }
        /* insertion sort: by level, then by skill number */
        for (; n > 0; n--) {
            int level = (u8)func_002F47A0(func_0029FD70(), skill) + 1;
            if (row[n - 1].level < level)
                break;
            if (row[n - 1].level == level && row[n - 1].skill < skill)
                break;
            func_002A01A0((u32 *)&row[n], (const u32 *)&row[n - 1]);
        }
        row[n].skill = skill;
        row[n].level = (u8)(func_002F47A0(func_0029FD70(), skill) + 1);
        filled[slot]++;                         /* (can pass 5: only "full or not" matters) */
    }

    /* counts */
    for (s = 0; s < 4; s++) {
        g_00773174[player * 4 + s] = 0;
    }
    for (s = 0; s < 4; s++)
        for (k = 0; k < 5 && base[s * 5 + k].skill < SKILL_COUNT; k++)
            g_00773174[player * 4 + s]++;

    /* bargains */
    if (g_00669D82 == 3) {                      /* sale: everything but the ultimates */
        for (s = 0; s < 4; s++)
            for (k = 0; k < g_00773174[player * 4 + s]; k++) {
                SkillOffer *o = &base[s * 5 + k];
                o->bargain = !is_ultimate(o);
                if (o->bargain)
                    g_00773194 = 1;
            }
        g_00669D82 = 0;
    } else {
        if (random16() % 100 < 50) {            /* one bargain, 50 % of the time */
            total = (u8)((u8)((u8)(g_00773174[player * 4] + g_00773174[player * 4 + 1])
                              + g_00773174[player * 4 + 2]) + g_00773174[player * 4 + 3]);
            pick = total == 0 ? 0 : random16() % (unsigned)total;
        } else {
            pick = 0xFF;
        }
        index = 0;
        for (s = 0; s < 4; s++)
            for (k = 0; k < g_00773174[player * 4 + s]; k++) {
                SkillOffer *o = &base[s * 5 + k];
                if (is_ultimate(o)) {
                    o->bargain = 0;
                } else if (index == pick) {
                    o->bargain = 1;
                    g_00773194 = 1;
                } else {
                    o->bargain = 0;
                }
                index = (index + 1) & 0xFF;
            }
    }

    /* (never true: kind-3 skills are not offered) */
    for (s = 0; s < 4; s++)
        for (k = 0; k < g_00773174[player * 4 + s]; k++)
            if (SKILL_KIND(base[s * 5 + k].skill) == 3) {
                g_00773198 = 1;
                break;
            }
}

/* 0x002A0920, 0x218 bytes. Prices of `player`'s skill offers: level x 400 (x 500 for kind 3), or
 * 10000 for an ultimate; x 0.8 when the skill suits the officer's type, x 1.2 when it suits the
 * other type; x 0.8 again for the bargain. */
void func_002A0920(int player)
{
    SkillOffer *base = (SkillOffer *)&g_00772DF0[player * 0x140];
    int type = func_002F67B0(func_0029FD70());
    int s, k;

    for (k = 0; k < 5; k++)
        for (s = 0; s < 4; s++) {
            SkillOffer *o = &base[s * 5 + k];
            unsigned price;
            u8 kind;

            if (o->skill >= SKILL_COUNT)
                continue;
            kind = SKILL_KIND(o->skill);
            if (is_ultimate(o))
                price = 10000;
            else if (kind == 3)
                price = o->level * 500;
            else
                price = o->level * 400;
            if ((type == 1 && kind == 1) || (type == 2 && kind == 2))
                price = price * 8 / 10;
            else if ((type == 1 && kind == 2) || (type == 2 && kind == 1))
                price = price * 12 / 10;
            if (o->bargain == 1)
                price = price * 8 / 10;
            o->price = (int)price;
        }
}

/* 0x002A1380, 0x2CC bytes. The mounts on sale: six mount records (g_007731D0) built from the
 * default list (30 %: the third one becomes type 3), given random names, shown in a shuffled
 * order; 6 offers. 50 %: one random offer is the day's bargain. */
void func_002A1380(void)
{
    MountTypes order;
    const char *names[6];
    unsigned i;

    order = *(MountTypes *)&g_0045CEA0;
    if (random16() % 100 < 30) {
        order.type[2] = 3;
        g_00773198 = 1;
    }
    for (i = 0; i < 6; i++)
        func_001A0630(&g_007731D0[i * 0x24], order.type[i]);
    func_00372E60(names, 6);
    {
        u8 *rec = g_007731D0;
        for (i = 0; i < 6; i++, rec += 0x24)
            func_00120928((char *)rec + 0x13, names[i]);
    }

    for (i = 0; i < 6; i++)
        order.type[i] = (u8)i;
    order.type[5] = 2;                          /* (as in the original: 2 twice, no 5) */
    for (i = 0; i < 6; i++) {                   /* six random swaps */
        u8 a = random16() % 6;
        u8 b = random16() % 6;
        u8 tmp = order.type[a];
        order.type[a] = order.type[b];
        order.type[b] = tmp;
    }
    for (i = 0; i < 6; i++)
        g_007731D0[i * 0x24 + 7] = order.type[i];

    for (i = 0; i < 8; i++) {
        g_MountOffers[i].price = 0;
        g_MountOffers[i].index = (u8)i;
        g_MountOffers[i].bargain = 0;
    }
    if (i > 6)
        i = 6;
    g_0077317C = (u8)i;
    if (random16() % 100 < 50) {
        u8 r = g_0077317C == 0 ? 0 : random16() % g_0077317C;
        g_MountOffers[r].bargain = 1;
        g_00773194 = 1;
    }
}

/* 0x002A1650, 0xE8 bytes. Mount prices: 3000 for a type-3 mount, else 2000, 2100 or 2200 at
 * random; x 0.8 for the bargain. */
void func_002A1650(void)
{
    int i;

    for (i = 0; i < g_0077317C; i++) {
        MountOffer *o = &g_MountOffers[i];
        int price;

        if (g_007731D0[o->index * 0x24 + 6] == 3)
            price = 3000;
        else
            price = random16() % 3 * 100 + 2000;
        if (o->bargain != 0)
            price = price * 8 / 10;
        o->price = price;
    }
}

/* 0x002A2640, 0x124 bytes, matching. How many officers the shop offers for hire: room left in the force
 * (6 per something, minus those already there), limited by another count while func_00327E50()
 * is below 150; between 0 and 8. */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int func_002A2640(void)
{
    u32 force = func_00327D50();
    int n;

    if (func_00327E50() >= 150) {
        int capacity = func_002FB3B0(force);
        int used = func_002FB430(force);

        n = capacity * 6 - used;
        n = MIN(n, 8);
    } else {
        int capacity = func_002FB3B0(force);
        int limit = func_00309FB0();
        int used = func_002FB430(force);
        int room;

        n = capacity * 6 - used;
        room = limit - used;
        room = MAX(room, 0);
        n = MIN(n, room);
        n = MIN(n, 8);
    }
    return MIN(MAX(n, 0), 8);
}

/* 0x002A2770, 0x268 bytes. The officers for hire: a shuffled list of candidates (func_002F7D90 with
 * the filter func_002F85E0), keeping those the force has room for, up to func_002A2640(). With 3 or
 * more offers, 50 %: one random offer is the day's bargain. */
void func_002A2770(void)
{
    int slot_a = SLOT_COUNT, slot_b = SLOT_COUNT, room = 0, unknown = 0;
    int found, wanted, count, i;
    HireOffer *o = g_HireOffers;

    g_0077317D = 0;
    found = func_003003C0(&slot_a, &slot_b, &room, &unknown);
    wanted = func_002A2640();
    if (found > 0 && wanted > 0) {
        int *list;
        count = func_002F7D90(0, (void *)func_002F85E0, 0, 0, 0, 0);
        list = func_002F7B10();
        func_002F7C40(list, count);
        for (i = 0; i < count; i++) {
            int officer = list[i];
            if ((func_002F3F20(officer) == 0 || (room > 0 && slot_a >= 0 && slot_a < SLOT_COUNT))
                && (unsigned)officer < OFFICER_NONE) {
                if (func_002F3F20(officer) != 0)
                    room--;
                o->officer = officer;
                o->can_hire = 1;
                g_0077317D++;
                o++;
                if (g_0077317D >= wanted)
                    break;
            }
        }
    }
    for (i = 0; i < g_0077317D; i++)
        g_HireOffers[i].bargain = 0;
    if (g_0077317D > 2 && random16() % 100 < 50) {
        unsigned r = g_0077317D == 0 ? 0 : random16() % g_0077317D;
        g_HireOffers[r].bargain = 1;
        g_00773194 = 1;
    }
}

/* 0x002A29E0, 0xF8 bytes. Hire prices: (level / 4 + 1) x 400 + 1000, or x 500 for the unique
 * officers (0-27 and 400-414); x 0.8 for the bargain. */
void func_002A29E0(void)
{
    int i;
    HireOffer *o = g_HireOffers;

    for (i = 0; i < g_0077317D; i++, o++) {
        int unit;
        int price;

        if ((o->officer >= 0 && o->officer < 0x1C) || (o->officer >= 400 && o->officer < 0x19F))
            unit = 500;
        else
            unit = 400;
        price = unit * (func_002F41E0(o->officer) / 4 + 1) + 1000;
        if (o->bargain == 1)
            price = price * 8 / 10;
        o->price = price;
    }
}
