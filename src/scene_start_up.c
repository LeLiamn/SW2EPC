/*
 * scene_start_up.c - scene 0x13, the start of an Empire game (original source file
 * StateStartUp.c: its name is passed to the file loader at 0x00365530). The whole file
 * (0x00365440-0x00369560) is decompiled.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The scene runs in phases (g_007B7070, 0-10):
 *  0  the main menu: a wheel of up to 11 entries (0-6 always, 7-10 when unlocked), four shown;
 *     OK picks the entry (g_007B7074), Cancel goes back to the title (scene 1);
 *  1  a level (g_007B7078, 0-4) for the entry;
 *  2  the entry list (func_00374E00 / func_0030AFF0): start, delete, edit, or pick officers;
 *  3  the options screen (six rows of up to five values, then OK);
 *  4, 5  the choice of the officers of seven slots (4: a new game, 5: an existing entry);
 *  6  func_003672D0 waits for a dialog (2 goes on to 7, 3 back to 2);
 *  7  the save / start check, which stops the music and fades out;
 *  8  waits for the fade-out; 9 and 10 leave the scene (9 falls back to scene 0x11 when nothing
 *     was requested).
 * An officer is 0-0x19E (0x19F = none; 400-0x19E are edited officers); each one has an "in use"
 * byte. The officer lists of the start-up state are built by func_00365690.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The scene manager (0x0045D880, see main.c): one object, reached through lui / %lo. */
extern struct {
    float update_arg;
    u32 result;
    int quit, skip_update_test;
    int force_draw;          /* 0x0045D890 */
    int previous;            /* 0x0045D894 */
    int current;             /* 0x0045D898 */
    int return_to;           /* 0x0045D89C state to return to */
    int requested;           /* 0x0045D8A0 requested state (0x18 = none) */
} g_0045D880;
#define g_0045D890 (g_0045D880.force_draw)
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

#define GO_TO_NEXT_SCENE() do {                                         \
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {            \
            g_0045D894 = g_0045D898;                                    \
            g_0045D898 = g_0045D8A0;                                    \
            g_0045D89C = 0x18;                                          \
        } else {                                                        \
            g_0045D894 = g_0045D898;                                    \
            g_0045D898 = g_0045D89C;                                    \
            g_0045D89C = g_0045D8A0;                                    \
        }                                                               \
    } while (0)

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
#define g_0050074C (g_00500700[0].pressed)
#define g_0050074E (g_00500700[0].held)
#define g_00500764 (g_00500700[0].ready)
#define g_00500765 (g_00500700[0].connected)

/* Controller 1, inlined in the original (macros). */
#define pad1_ready() ((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_0050074C : 0))
#define pad1_held() ((unsigned short)(pad1_ready() ? g_0050074E : 0))

#define BTN_CANCEL 0x0010
#define BTN_OK     0x0040
#define BTN_REMOVE 0x0080
#define BTN_START  0x0800
#define BTN_UP     0x1000
#define BTN_RIGHT  0x2000
#define BTN_DOWN   0x4000
#define BTN_LEFT   0x8000

#define SE_CURSOR 0x2CDC          /* sound effect played on cursor moves and choices */
#define SE(kind) func_0023AD10((kind), 0, SE_CURSOR, SE_CURSOR, 0x1000)   /* 0 move, 1 OK, 2 back, 4 refused */

/* The message boxes' object (0x0068F3E0, see scene_shop.c): box n's state at +0x40D3 + n * 0x128,
 * its answer at +0x40D4 + n * 0x128. */
extern struct {
    u8 unknown_0[0x40D3];
    u8 g_006934B3;           /* box 0 open */
    u8 unknown_40D4[0x127];
    u8 g_006935DB;           /* box 1 open */
    u8 g_006935DC;           /* box 1 answer (4 = yes?) */
    u8 unknown_41FD[0x381];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_006934B3 (s_0068F3E0.g_006934B3)
#define g_006935DB (s_0068F3E0.g_006935DB)
#define g_006935DC (s_0068F3E0.g_006935DC)
#define g_0069395E (s_0068F3E0.g_0069395E)
/* Whether message box 1 is open (an inlined function in the original: the result is a value). */
static inline int box1_open(void)
{
    if (g_0069395E == 0 || g_0069395E == 0xFF)
        return 0;
    return 1;
}

/* Shows message `id` (func_00390760) in box `box`; inlined in the original. */
#define SHOW_MESSAGE(box, id) do {                                      \
        func_001204B0(text, func_00390760(id));                         \
        func_001B8BF0();                                                \
        func_001AEDE0((box), 0xAA);                                     \
        func_001AE9F0((box), text, 1);                                  \
        func_001AFC70((box), 0);                                        \
    } while (0)

/* The scene's state (0x007B7070, returned by func_00365440), not reached through $gp. */
extern struct {
    int g_007B7070;          /* phase (0-10) */
    int g_007B7074;          /* main menu entry chosen */
    int g_007B7078;          /* level (0-4) */
    int g_007B707C[25];      /* passed to func_002FBAC0 (-1 = none) */
} s_007B7070;
#define g_007B7070 (s_007B7070.g_007B7070)
#define g_007B7074 (s_007B7070.g_007B7074)
#define g_007B7078 (s_007B7070.g_007B7078)
#define g_007B707C (s_007B7070.g_007B707C)

/* The options screen (0x007B70E0, returned by func_00365460). */
extern struct OptionsScreen {
    u8 unknown_0[0x14];
    u8 g_007B70F4;           /* 1 in use, 3 closing (0 and 2: nothing to do) */
    u8 g_007B70F5;           /* how it closed: 0 back, 1 OK */
    u8 g_007B70F6;           /* row (0-5, 6 = OK) */
    u8 values[6];             /* 0x007B70F7 each row's value (0-4) */
    u8 rows[7];               /* 0x007B70FD each row offered */
} s_007B70E0;
#define g_007B70F4 (s_007B70E0.g_007B70F4)
#define g_007B70F5 (s_007B70E0.g_007B70F5)
#define g_007B70F6 (s_007B70E0.g_007B70F6)
#define g_007B70F7 (s_007B70E0.values[0])
#define g_007B70F8 (s_007B70E0.values[1])
#define g_007B70F9 (s_007B70E0.values[2])
#define g_007B70FA (s_007B70E0.values[3])
#define g_007B70FB (s_007B70E0.values[4])
#define g_007B70FC (s_007B70E0.values[5])
#define g_007B70FD (s_007B70E0.rows[0])
#define g_007B70FE (s_007B70E0.rows[1])
#define g_007B70FF (s_007B70E0.rows[2])
#define g_007B7100 (s_007B70E0.rows[3])
#define g_007B7101 (s_007B70E0.rows[4])
#define g_007B7102 (s_007B70E0.rows[5])
#define g_007B7103 (s_007B70E0.rows[6])

/* The start-up state (0x007B7104). */
extern struct StartState {
    u8 g_007B7104;           /* slot (0 = the ruler, 1-6 = officers, 7 = OK) */
    u8 unknown_1;
    u8 g_007B7106;           /* 0 choosing, 1 the officer list is open */
    u8 g_007B7107[0x19F];    /* per officer: in use */
    u8 unknown_1A2[2];
    int g_007B72A8[0x19F];   /* officers that can be chosen ... */
    int g_007B7924[0x19F];   /* ... those of them 0x1C-0x18F */
    int g_007B7FA0[0x19F];   /* rulers that can be chosen */
    int g_007B861C[0x19F];   /* the list shown (func_00367C20) */
    int g_007B8C98;          /* count of g_007B72A8 */
    int g_007B8C9C;          /* count of g_007B7924 */
    int g_007B8CA0;          /* count of g_007B7FA0 */
    int g_007B8CA4;          /* officers that can still be chosen */
    int g_007B8CA8;          /* ... of them, 0x1C-0x18F */
    int g_007B8CAC[25];      /* per entry of func_00374E00: holds a game */
    int g_007B8D10;          /* the entry being set up */
    int g_007B8D14[0x19F];   /* officers set free (see func_00368980) */
    int g_007B9390;          /* ... their count */
    int g_007B9394[7];       /* the slots' officers when the choice started */
    int g_007B93B0[7];       /* per slot: the officer (0x19F = none) */
    int unknown_22C8;
    int g_007B93D0;          /* set after a start, cleared when the list opens */
} s_007B7104;
#define g_007B7104 (s_007B7104.g_007B7104)
/* The same fields through a byte pointer `st` to the state (the original keeps that base in a
 * register; a typed pointer to the known address would be folded back into constants). */
#define ST_USED(st)        ((st) + 3)                      /* g_007B7107 */
#define ST_CHOOSABLE(st)   ((int *)((st) + 0x1A4))         /* g_007B72A8 */
#define ST_GENERALS(st)    ((int *)((st) + 0x820))         /* g_007B7924 */
#define ST_SHOWN(st)       ((int *)((st) + 0x1518))        /* g_007B861C */
#define ST_NCHOOSABLE(st)  (*(int *)((st) + 0x1B94))       /* g_007B8C98 */
#define ST_NGENERALS(st)   (*(int *)((st) + 0x1B98))       /* g_007B8C9C */
#define ST_LEFT(st)        (*(int *)((st) + 0x1BA0))       /* g_007B8CA4 */
#define ST_LEFT_GEN(st)    (*(int *)((st) + 0x1BA4))       /* g_007B8CA8 */
#define ST_GAMES(st)       ((int *)((st) + 0x1BA8))        /* g_007B8CAC */
/* Element `i` of an int array at offset `off` of the state, written as the original did. */
#define ST_AT(st, off, i)  (*(int *)((st) + (i) * 4 + (off)))
#define g_007B7106 (s_007B7104.g_007B7106)
#define g_007B7107 (s_007B7104.g_007B7107)
#define g_007B72A8 (s_007B7104.g_007B72A8)
#define g_007B7924 (s_007B7104.g_007B7924)
#define g_007B7FA0 (s_007B7104.g_007B7FA0)
#define g_007B861C (s_007B7104.g_007B861C)
#define g_007B8C98 (s_007B7104.g_007B8C98)
#define g_007B8C9C (s_007B7104.g_007B8C9C)
#define g_007B8CA0 (s_007B7104.g_007B8CA0)
#define g_007B8CA4 (s_007B7104.g_007B8CA4)
#define g_007B8CA8 (s_007B7104.g_007B8CA8)
#define g_007B8CAC (s_007B7104.g_007B8CAC)
#define g_007B8D10 (s_007B7104.g_007B8D10)
#define g_007B8D14 (s_007B7104.g_007B8D14)
#define g_007B9390 (s_007B7104.g_007B9390)
#define g_007B9394 (s_007B7104.g_007B9394)
#define g_007B93B0 (s_007B7104.g_007B93B0)
#define g_007B93D0 (s_007B7104.g_007B93D0)

#define SLOT_VALID(s) ((s) > 0 && (s) < 7)

/* The main menu (0x007B93D8, returned by func_00365450). */
typedef struct {
    int index;               /* +0x00 entry under the cursor (in entries[]) */
    int shown[4];            /* +0x04 the four entries shown */
    int unknown_14;
    int entries[11];         /* +0x18 the entries offered (-1 = none) */
    int count;               /* +0x44 */
    int turn;                /* +0x48 wheel movement: 1 down, 2 up, 3 none, 4 chosen */
    u8 unknown_4C[0xF0];
    u8 anim[0x34];           /* +0x13C passed to func_00383D70 */
    u8 offered[11];          /* +0x170 per entry */
    u8 unknown_17B;
    u8 unknown_17C;
    u8 message;              /* +0x17D a message is shown */
    u8 unknown_17E[2];
    int scroll;              /* +0x180 */
} StartMenu;

extern StartMenu s_007B93D8;

extern void *g_0045D774, *g_0045D778, *g_0045D77C;   /* (small data) the loaded files */

/* Help lines (part of the text table at 0x0043C32C, see scene_config.c; 0xF0 + letter = a
 * button icon). */
extern struct {
    const char *g_0043C578;    /* "Select  Back  OK" */
    const char *unknown_57C[0x2F];
    const char *g_0043C638;    /* "Select  Back  OK" */
    const char *unknown_63C[0x26];
    const char *g_0043C6D4;    /* "Select  Back  OK" */
    const char *unknown_6D8;
    const char *g_0043C6DC;    /* "Remove  Select  Back  OK" */
    const char *unknown_6E0[0x14];
    const char *g_0043C730;    /* "Select  Back  OK" */
    const char *unknown_734[0x22];
    const char *g_0043C7BC;    /* "Select  OK" */
    const char *unknown_7C0[0x16];
    const char *g_0043C818;    /* "Select  Info  Edit  Delete  Details  Back  OK" */
    const char *g_0043C81C;    /* "Select  Info  Delete  Details  Back  OK" */
    const char *g_0043C820;    /* "Select  Info  Edit  Details  Back  OK" */
    const char *g_0043C824;    /* "Select  Info  Details  Back  OK" */
} s_0043C578;
#define g_0043C578 (s_0043C578.g_0043C578)
#define g_0043C638 (s_0043C578.g_0043C638)
#define g_0043C6D4 (s_0043C578.g_0043C6D4)
#define g_0043C6DC (s_0043C578.g_0043C6DC)
#define g_0043C730 (s_0043C578.g_0043C730)
#define g_0043C7BC (s_0043C578.g_0043C7BC)
#define g_0043C818 (s_0043C578.g_0043C818)
#define g_0043C81C (s_0043C578.g_0043C81C)
#define g_0043C820 (s_0043C578.g_0043C820)
#define g_0043C824 (s_0043C578.g_0043C824)

/* Per level (g_007B70FB): officers per step and the most (0x00415E80). */
extern struct {
    int step;
    int most;
} g_00415E80[5];

/* Which values each options row offers (0x00415EB0, copied before use). */
typedef struct {
    int offered[6][5];
} OptionValues;
extern OptionValues g_00415EB0;

void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
int func_00102960(int value);
void func_00102EC0(void *data);
int func_002F3DC0(int officer);
int func_003A0040(int officer);
int func_002F3BB0(int officer);
int func_0039E650(int edited);
int func_0030AB90(void);
int func_0030AFF0(int entry);
int func_002F8F20(int entry);
int func_002F3E70(int officer);
void func_002F3CF0(int officer, int a);
void func_002F3F70(int officer, int a);
void func_002F3B30(int officer, int a);
void func_002F5BE0(int officer, int a);
int func_0030C9C0(int entry);
int func_002F7EC0();
int func_002F80C0();
int func_002F8110();
int func_002F8160();
int func_002F7D90(int a, int (*filter)(), int value, int b, int c, int d);
int *func_002F7B10(void);
void func_0030AF20(int a, int b);
void func_003A8000(int a);
int func_002FB320(int a, int *out);
void func_002F8D20(int a);
static void func_00367B10(int officer, int available);
void func_0011EB80(void *to, const void *from, int size);
int func_0039E5F0(void);
int func_003A2A00(void);
int func_0039FD80(int entry);
void func_003853A0(void);
void func_003849F0(void);
void func_00384E30(void);
void func_00327CF0(int value);
void func_002FBAC0(int *values);
void func_003A5FA0(int a, int b, int c, int d);
int func_00327C00(void);
void func_00373970(int a, int b, int c);
void func_003A9010(int a);
int func_00374E00(void);
void func_00327780(int value);
void func_003A7E10(void);
void func_003A7ED0(void);
void func_003A9060(int a);
void func_003A78E0(int a, int b, int c);
int func_003A28B0(int a);
int func_003A1A80(void);
int func_003A1AC0(void);
int func_003A1B00(void);
int func_003A1B40(void);
void func_0030CE90(int entry);
void func_00384A60(void);
int func_003F1160(int a);
void func_001A7DC0(const char *text, int alpha, int a);
int func_00383B10(int entry);
u32 func_001020C0(void);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_00383D70(u8 *anim);
void func_0017DF10(void);
void func_001B8F60(int a, int b, int c);
void func_00114DF0(int a);
void func_003281F0(int a);
void func_00327BD0(int entry);
void func_00376100(int a, int b, int c);
void func_003A5C40(int entry);
void func_003F4D60(int a);
void func_003B3DD0(int a, int level);
void func_00327C10(int value);
void func_003A5E20(void);
void func_003A8DC0(void);
int func_003748C0(int no_entry, int unprotected, int edit);
void func_00387AC0(void);
const char *func_00390760(int id);
void func_00375030(int x, int y, int w, int h, int a, const char *text);
void func_001204B0(char *to, const char *from);
void func_001B8BF0(void);
void func_001AEDE0(int box, int a);
void func_001AE9F0(int box, const char *text, ...);
void func_001AFC70(int box, int a);
int func_00327D50(void);
int func_002FB3B0(int a);
int func_002FB430(int a);
void func_003852A0(void);
void func_00386520(int a);
int func_00375B90(void);
void func_003F1070(int a);
void func_00387D90(void);
void func_003A5240(void);
void func_00387B70(void);

int *func_00365450(void);
void func_00365650(void);
void func_00365690(void);
void func_003659A0(void);
void func_00366160(int entry, int offered);
int func_00366120(int entry);
static void func_003664D0(void);
void func_00367330(void);

#define ENTRY_VALID(e) ((e) >= 0 && (e) < func_0030AB90())

/* 0x00365440, 0xC bytes, matching. The scene's state. */
void *func_00365440(void)
{
    return &s_007B7070;
}

/* 0x00365450, 0xC bytes, matching. The main menu. */
int *func_00365450(void)
{
    return (int *)&s_007B93D8;
}

/* 0x00365460, 0xC bytes, matching. The options screen. */
void *func_00365460(void)
{
    return &s_007B70E0;
}

/* 0x00365470, 0x8 bytes, matching. */
void *func_00365470(void)
{
    return g_0045D77C;
}

/* 0x00365480, 0x8 bytes, matching. */
void *func_00365480(void)
{
    return g_0045D778;
}

/* 0x00365490, 0x8 bytes, matching. */
void *func_00365490(void)
{
    return g_0045D774;
}

/* 0x003654A0, 0x50 bytes, matching. Wraps a main menu position around the entries offered. */
int func_003654A0(int i)
{
    StartMenu *menu = (StartMenu *)func_00365450();
    int r = i;

    if (r < 0)
        r = menu->count + i;
    else if (r >= menu->count)
        r = i - menu->count;
    return r;
}

/* 0x003654F0, 0x34 bytes, matching. Whether main menu entry `entry` is one of 0-9. */
int func_003654F0(int entry)
{
    int result = 0;

    switch (entry) {
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
        result = 1;
        break;
    case 10:
        break;
    }
    return result;
}

/* 0x00365530, 0xBC bytes, matching. Loads the scene's three files (LINKDATA entries 0x7F, 0x82 and 0x81). */
void func_00365530(void)
{
    g_0045D77C = 0;
    g_0045D77C = func_001026D0(1, 0x7F, 0, 1, 0, 0, "StateStartUp.c", 0xAC);
    func_00102960(1);
    g_0045D778 = 0;
    g_0045D778 = func_001026D0(1, 0x82, 0, 1, 0, 0, "StateStartUp.c", 0xB2);
    func_00102960(1);
    g_0045D774 = 0;
    g_0045D774 = func_001026D0(1, 0x81, 0, 1, 0, 0, "StateStartUp.c", 0xB8);
    func_00102960(1);
}

/* 0x003655F0, 0x5C bytes, matching. Frees them. */
void func_003655F0(void)
{
    if (g_0045D778 != 0) {
        func_00102EC0(g_0045D778);
        g_0045D778 = 0;
    }
    if (g_0045D77C != 0) {
        func_00102EC0(g_0045D77C);
        g_0045D77C = 0;
    }
    if (g_0045D774 != 0) {
        func_00102EC0(g_0045D774);
        g_0045D774 = 0;
    }
}

/* 0x00365650, 0x3C bytes, matching. */
#pragma opt_unroll_loops on
void func_00365650(void)
{
    int i;

    for (i = 0; i < 25; i++)
        g_007B707C[i] = -1;
}
#pragma opt_unroll_loops off

/* 0x00365690, 0x304 bytes. Builds the officer lists: the officers that can be chosen (status 1-3
 * of func_002F3DC0 are listed but already taken; free ones need func_003A0040 and func_002F3BB0
 * 1 or 2; edited officers 400-0x19E need func_0039E650), and the rulers of the entries. */
void func_00365690(void)
{
    int i, taken = 0, taken2 = 0;

    g_007B8C98 = 0;
    g_007B8C9C = 0;
    for (i = 0; i < 0x19F; i++) {
        u8 *available = &g_007B7107[i];

        *available = 0;
        if (i < 400 || i > 0x19E) {
            if (func_002F3DC0(i) == 2 || func_002F3DC0(i) == 1 || func_002F3DC0(i) == 3) {
                taken++;
                g_007B72A8[g_007B8C98++] = i;
                if (i > 0x1B && i < 400) {
                    taken2++;
                    g_007B7924[g_007B8C9C++] = i;
                }
                *available = 0;
            } else if (func_003A0040(i) != 0 && func_002F3DC0(i) == 0 &&
                       (func_002F3BB0(i) == 1 || func_002F3BB0(i) == 2)) {
                g_007B72A8[g_007B8C98++] = i;
                if (i > 0x1B && i < 400)
                    g_007B7924[g_007B8C9C++] = i;
                *available = 1;
            }
        } else if (func_0039E650(i - 400) != 0 && func_002F3DC0(i) == 0) {
            g_007B72A8[g_007B8C98++] = i;
            *available = 1;
        }
    }
    g_007B8CA0 = 0;
    g_007B8CA4 = g_007B8C98 - taken;
    g_007B8CA8 = g_007B8C9C - taken2;
    for (i = 0; i < func_0030AB90(); i++) {
        int entry = func_0030AFF0(i);
        int ruler;

        if (ENTRY_VALID(entry) && (u32)(ruler = func_002F8F20(entry)) < 0x19F) {
            int j;

            for (j = 0; j < g_007B8CA0; j++)
                if (g_007B7FA0[j] == ruler)
                    break;
            if (j >= g_007B8CA0)
                g_007B7FA0[g_007B8CA0++] = ruler;
        }
    }
    g_007B9390 = 0;
}

/* 0x003659A0, 0xA0 bytes, matching. Marks which entries hold a game. */
void func_003659A0(void)
{
    u8 *st = &g_007B7104;
    int i;

    for (i = 0; i < func_0030AB90(); i++) {
        int entry = func_0030AFF0(i), valid;

        valid = entry >= 0 && entry < func_0030AB90();
        if (valid)
            ST_AT(st, 0x1BA8, i) = 1;
        else
            ST_AT(st, 0x1BA8, i) = 0;
    }
}

/* 0x00365A40, 0x34 bytes, matching. Frees an officer (status 0, entry 0x19 = none). */
void func_00365A40(int officer)
{
    func_002F3CF0(officer, 0);
    func_002F3F70(officer, 0x19);
}

/* 0x00365A80, 0xDC bytes, matching. Puts an officer in entry `entry` (status 2), with `kind` (0-5) and
 * `place` (a valid entry, or 0x19) when given. */
void func_00365A80(int officer, int entry, int place, int kind)
{
    int ok;

    func_002F3B30(officer, 2);
    if (kind >= 0 && kind < 6)
        func_002F3CF0(officer, kind);
    ok = 0;
    if (entry >= 0 && entry < func_0030AB90())
        ok = 1;
    if (ok)
        func_002F3F70(officer, entry);
    ok = 0;
    if (place >= 0 && place < func_0030AB90())
        ok = 1;
    if (!ok)
        ok = place == 0x19;
    if (ok)
        func_002F5BE0(officer, place);
}

/* 0x00365B60, 0x1F0 bytes. Deletes the game of entry `entry` (`game` = func_0030AFF0 of it):
 * frees its officers and makes their rulers choosable again. */
void func_00365B60(int entry, int game)
{
    int list[28];
    int i, j, k, n, m;
    int *officers;

    if (func_0030C9C0(entry) == 0) {
        n = func_002F7D90(0, func_002F7EC0, entry, 0, 1, 0);
        officers = func_002F7B10();
        for (i = 0; i < n; i++) {
            func_00365A40(*officers);
            func_00367B10(*officers, 1);
            officers++;
        }
        func_0030AF20(entry, 0x19);
        func_003A8000(entry);
    } else {
        int *p;

        n = func_002FB320(game, list);
        p = list;
        for (i = 0; i < n; i++) {
            func_0030AF20(*p, 0x19);
            func_002F8D20(game);
            func_003A8000(*p);
            m = func_002F7D90(0, func_002F8160, game, 0, 1, 0);
            officers = func_002F7B10();
            for (j = 0; j < m; j++) {
                if (func_002F3E70(*officers) != 0)
                    for (k = 0; k < g_007B8CA0; k++)
                        if (g_007B7FA0[k] == *officers)
                            g_007B7FA0[k] = g_007B7FA0[--g_007B8CA0];
                func_00365A40(*officers);
                func_00367B10(*officers, 1);
                officers++;
            }
            p++;
        }
    }
}

/* 0x00365D50, 0x2D8 bytes. Fills the slots from entry g_007B8D10: the ruler (or the first
 * officer for whom func_002F3E70 holds, in slots 0 and 1), the other officers, then those of
 * func_002F8110 from slot 4; keeps a copy in g_007B9394. */
void func_00365D50(void)
{
    int i, n, slot = 0, extra = 0;
    int game = func_0030AFF0(g_007B8D10);
    int *officers;

    n = func_002F7D90(0, func_002F80C0, g_007B8D10, 0, 1, 0);
    officers = func_002F7B10();
    for (i = 0; i < 7; i++)
        g_007B93B0[i] = 0x19F;
    if (ENTRY_VALID(game))
        g_007B93B0[0] = func_002F8F20(game);
    for (i = 0; i < n; i++) {
        if (func_002F3E70(*officers) != 0) {
            g_007B93B0[0] = *officers;
            slot = 1;
            g_007B93B0[1] = g_007B93B0[0];
            break;
        }
        officers++;
    }
    officers = func_002F7B10();
    for (i = 0; i < n; i++) {
        if (func_002F3E70(*officers) == 0)
            g_007B93B0[1 + slot++] = *officers;
        officers++;
    }
    n = func_002F7D90(0, func_002F8110, g_007B8D10, 0, 1, 0);
    officers = func_002F7B10();
    for (i = 0; i < n; i++)
        g_007B93B0[4 + extra++] = *officers++;
    func_0011EB80(g_007B9394, g_007B93B0, 0x1C);
}

/* 0x00366030, 0xF0 bytes, matching. Which main menu entries are offered: 0-6 always, 10 with
 * func_0039E5F0 or func_003A2A00 > 0, the others with func_0039FD80. */
void func_00366030(void)
{
    int i;

    func_00365450();
    for (i = 0; i < 11; i++) {
        if (i < 7)
            func_00366160(i, 1);
        else if (i == 10) {
            if (func_0039E5F0() != 0 || func_003A2A00() > 0)
                func_00366160(i, 1);
            else
                func_00366160(i, 0);
        } else if (func_0039FD80(i) != 0)
            func_00366160(i, 1);
        else
            func_00366160(i, 0);
    }
}

/* 0x00366120, 0x34 bytes, matching. */
int func_00366120(int entry)
{
    StartMenu *menu = (StartMenu *)func_00365450();

    return menu->offered[entry] == 1;
}

/* 0x00366160, 0x50 bytes, matching. */
void func_00366160(int entry, int offered)
{
    StartMenu *menu = (StartMenu *)func_00365450();

    if (offered != 0)
        menu->offered[entry] = 1;
    else
        menu->offered[entry] = 0;
}

/* 0x003661B0, 0x148 bytes. Sets up the main menu: the entries offered, the cursor on entry 6,
 * the four shown around it. */
#pragma opt_unroll_loops on
void func_003661B0(void)
{
    int i;
    int n;
    StartMenu *menu = (StartMenu *)func_00365450();

    menu->index = 0;
    menu->unknown_14 = 0;
    func_00366030();
    for (i = 0; i < 11; i++)
        menu->entries[i] = -1;
    for (i = 0, n = 0; i < 11; i++) {
        if (i < 7)
            menu->entries[i] = i;
        else if (func_00366120(i) != 0)
            menu->entries[n] = i;
        else
            continue;
        if (i == 6)
            menu->index = n;
        n++;
    }
    menu->count = n;
    for (i = 0; i < 4; i++)
        menu->shown[i] = menu->entries[func_003654A0(menu->index + (i - 1))];
    menu->turn = 3;
    func_003853A0();
    menu->unknown_17B = 0;
    func_003849F0();
    func_00384E30();
}
#pragma opt_unroll_loops off

/* 0x00366300, 0x78 bytes, matching. */
#pragma opt_unroll_loops on
void func_00366300(void)
{
    int i;

    func_003661B0();
    func_00365650();
    for (i = 0; i < 11; i++)
        g_007B707C[i] = i;
}
#pragma opt_unroll_loops off

/* 0x00366380, 0x148 bytes, matching. Sets up the entry list (phase 2). */
void func_00366380(void)
{
    StartMenu *menu = (StartMenu *)func_00365450();
    int i, game;

    menu->unknown_17C = 0;
    menu->message = 0;
    func_00365650();
    func_00327CF0(0x19);
    func_002FBAC0(g_007B707C);
    func_003A5FA0(0, 1, 1, 1);
    func_00373970(6, 0x80000000, func_00327C00());
    if (func_00327C00() >= 6)
        func_003A9010(3);
    else
        func_003A9010(2);
    game = func_0030AFF0(func_00374E00());
    func_00327CF0(game);
    if (func_00327C00() == 10) {
        func_00327780(0x19F);
        func_003A7E10();
    } else {
        func_00327780(func_002F8F20(game));
        func_003A7ED0();
    }
    func_003A9060(-1);
    for (i = 0; i < func_0030AB90(); i++)
        func_003A78E0(i, 0x1E, 0);
    func_003A78E0(0, 0x1F, 1);
}

/* 0x003664D0, 0x50 bytes, matching. The options' default values. */
static void func_003664D0(void)
{
    u8 *o = (u8 *)&s_007B70E0;

    o[0x1B] = 2;
    o[0x18] = 0;
    o[0x17] = 1;
    o[0x19] = 1;
    o[0x1A] = 0;
    o[0x1C] = 1;
    if (o[0x1D] == 1)
        o[0x17] = 0;
    if (o[0x1F] == 1)
        o[0x19] = 0;
}

/* 0x00366520, 0x8C bytes, matching. Sets up the options screen: which rows are offered. */
void func_00366520(void)
{
    u8 *o = (u8 *)&s_007B70E0;

    o[0x16] = 6;
    o[0x14] = 0;
    o[0x15] = 0;
    o[0x1D] = func_003A28B0(0) != 0;
    o[0x1E] = func_003A1A80() != 0;
    o[0x1F] = func_0039E5F0() != 0;
    o[0x20] = func_003A1AC0() != 0;
    o[0x21] = func_003A1B00() != 0;
    o[0x22] = func_003A1B40() != 0;
    o[0x23] = 1;
    func_003664D0();
}

/* 0x003665B0, 0x44 bytes, matching. */
void func_003665B0(void)
{
    u8 *s = &g_007B7104;

    if (func_003A1A80() != 0)
        s[0] = 0;
    else
        s[0] = 1;
    s[2] = 0;
}

/* 0x00366600, 0x44 bytes, matching. Resets the scene's state. */
void func_00366600(void)
{
    func_00366300();
    g_007B7070 = 0;
    g_007B7074 = 0;
    g_007B7078 = 2;
    func_00366520();
    func_003665B0();
}

/* 0x00366650, 0x20 bytes, matching. */
void func_00366650(void)
{
    func_0030CE90(g_007B7074);
}

/* 0x00366670, 0x40 bytes, matching. Phase 0 draw: the menu and its help line. */
void func_00366670(void)
{
    func_00384A60();
    if (func_003F1160(1) == 0)
        func_001A7DC0(g_0043C578, 0x80, 1);
}

/* 0x003666B0, 0x90 bytes, matching. Scrolls the main menu's text every fifth frame. */
void func_003666B0(void)
{
    StartMenu *menu = (StartMenu *)func_00365450();
    int width = func_00383B10(menu->entries[menu->index]);

    if (func_001020C0() % 5 == 0)
        menu->scroll--;
    if (menu->scroll + width * 0x14 < 0x1E)
        menu->scroll = 0x7A;
}

/* The four entries shown around the cursor. */
#define SHOW_AROUND(menu) do {                                          \
        (menu)->shown[0] = (menu)->entries[func_003654A0((menu)->index - 1)]; \
        (menu)->shown[1] = (menu)->entries[func_003654A0((menu)->index)];     \
        (menu)->shown[2] = (menu)->entries[func_003654A0((menu)->index + 1)]; \
        (menu)->shown[3] = (menu)->entries[func_003654A0((menu)->index + 2)]; \
    } while (0)

/* 0x00366740, 0x37C bytes, matching. Phase 0: the main menu. OK picks the entry (9 sets func_003281F0)
 * and goes to phase 1; Cancel goes back to the title (scene 1); Up / Down turn the wheel. */
void func_00366740(void)
{
    StartMenu *menu = (StartMenu *)func_00365450();
    int pressed = (unsigned short)pad1_pressed();
    int held = (unsigned short)pad1_held();

    func_003666B0();
    if (pressed & BTN_OK) {
        SE(1);
        func_00114DF0(1);
        menu->turn = 4;
        func_003853A0();
        g_007B7074 = menu->entries[menu->index];
        if (g_007B7074 == 9)
            func_003281F0(1);
        else
            func_003281F0(0);
        func_00327BD0(g_007B7074);
        g_007B7070 = 1;
        func_00376100(1, -1, -1);
        func_003A5C40(g_007B7074);
        func_003F4D60(0x13);
        func_00383D70(menu->anim);
    } else if (pressed & BTN_CANCEL) {
        g_007B7070 = 10;
        SE(2);
        func_0017DF10();
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
            g_0045D89C = 1;
        func_001B8F60(0, 6, 8);
    } else if (held & BTN_DOWN) {
        SE(0);
        menu->index = func_003654A0(menu->index + 1);
        menu->turn = 1;
        SHOW_AROUND(menu);
        func_003853A0();
        func_00383D70(menu->anim);
        func_00384E30();
    } else if (held & BTN_UP) {
        SE(0);
        menu->index = func_003654A0(menu->index - 1);
        menu->turn = 2;
        SHOW_AROUND(menu);
        func_003853A0();
        func_00383D70(menu->anim);
        func_00384E30();
    }
}

/* 0x00366AC0, 0x48 bytes, matching. Phase 1 draw: the level and its help line. */
void func_00366AC0(void)
{
    func_003B3DD0(1, g_007B7078);
    if (func_003F1160(1) == 0)
        func_001A7DC0(g_0043C6D4, 0x80, 1);
}

/* 0x00366B10, 0x254 bytes, matching. Phase 1: the level (0-4, Left / Right, wrapping on a press). OK keeps
 * it and opens the options; Cancel goes back to the main menu. */
void func_00366B10(void)
{
    int pressed = (unsigned short)pad1_pressed();
    int held = (unsigned short)pad1_held();
    StartMenu *menu = (StartMenu *)func_00365450();

    if (pressed & BTN_OK) {
        SE(1);
        func_00327C10(g_007B7078);
        func_00367330();
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        g_007B7070 = 0;
        menu->turn = 3;
        func_003853A0();
        func_00376100(0, -1, -1);
        func_003A5E20();
        func_00384E30();
    } else if (held & BTN_LEFT) {
        if (g_007B7078 > 0) {
            SE(0);
            g_007B7078--;
        } else if (pressed & BTN_LEFT) {
            SE(0);
            g_007B7078 = 4;
        }
    } else if (held & BTN_RIGHT) {
        if (g_007B7078 < 4) {
            SE(0);
            g_007B7078++;
        } else if (pressed & BTN_RIGHT) {
            SE(0);
            g_007B7078 = 0;
        }
    }
}

/* Starts the officer choice (phase 4 or 5) for entry g_007B8D10. */
#define START_CHOICE(phase) do {                                        \
        func_00365D50();                                                \
        g_007B7104 = 1;                                                 \
        g_007B7070 = (phase);                                           \
        g_007B9390 = 0;                                                 \
        func_00376100(2, 2, -1);                                        \
    } while (0)

/* 0x00366D70, 0x47C bytes. Phase 2: the entry list (func_003748C0: 1 start, 0 back, 3 delete,
 * 4 edit an existing game's officers, 5 choose the officers of a new one). */
void func_00366D70(void)
{
    StartMenu *menu = (StartMenu *)func_00365450();
    int pressed = (unsigned short)pad1_pressed();
    char text[256];

    func_003A8DC0();
    if (menu->message != 0) {
        if (pressed & 0x20) {
            SE(0);
            menu->message = 0;
        }
        return;
    }
    if (g_006934B3 != 0)
        return;
    if (g_006935DB == 0) {
        int entry = func_00374E00();
        int game = func_0030AFF0(func_00374E00());
        int protected_ = 0, valid = 0, r;

        if (g_007B8CAC[entry] != 0)
            protected_ = func_0030C9C0(entry) != 0;
        if (game >= 0 && game < func_0030AB90())
            valid = 1;
        r = func_003748C0(valid ^ 1, protected_ ^ 1, func_003A1A80());
        g_007B8D10 = func_00374E00();
        if (r == 1) {
            game = func_0030AFF0(entry);
            func_00327CF0(game);
            func_00327780(func_002F8F20(game));
            func_00387AC0();
            func_00375030(0x38, 0x10C, 400, 0x50, 0, func_00390760(0x93));
            g_007B7070 = 6;
        } else if (r == 0) {
            if (g_007B93D0 == 0) {
                func_00367330();
            } else {
                SHOW_MESSAGE(1, 0x110);
            }
        } else if (r == 3) {
            entry = func_00374E00();
            game = func_0030AFF0(entry);
            valid = 0;
            if (game >= 0 && game < func_0030AB90())
                valid = 1;
            if (valid && (g_007B8CAC[entry] == 0 || func_0030C9C0(entry) == 0))
                func_00365B60(entry, func_0030AFF0(entry));
        } else if (r == 4) {
            if (func_003A1A80() != 0)
                START_CHOICE(5);
        } else if (r == 5) {
            if (func_003A1A80() == 0) {
                if (g_007B8C98 < 1)
                    SHOW_MESSAGE(0, 0x95);
                else
                    START_CHOICE(4);
            } else {
                START_CHOICE(4);
            }
        }
    } else if (g_006935DC == 4) {
        func_00367330();
    }
}

/* 0x003671F0, 0x78 bytes, matching. How many officers the level allows. */
int func_003671F0(void)
{
    int p = func_00327D50();
    u8 level = g_007B70FB;
    int n = g_00415E80[level].step * (func_002FB3B0(p) - 1) + 6;

    return n < g_00415E80[level].most ? n : g_00415E80[level].most;
}

/* 0x00367270, 0x58 bytes, matching. Phase 6 draw. */
void func_00367270(void)
{
    int allowed = func_003671F0();
    int n = func_002FB430(func_00327D50());

    func_003852A0();
    n -= allowed;
    if (n < 0)
        n = 0;
    func_00386520(n);
}

/* 0x003672D0, 0x58 bytes, matching. Phase 6: waits for func_00375B90 (2 goes on to phase 7, 3 back to
 * phase 2). */
void func_003672D0(void)
{
    int r = func_00375B90();

    func_003A8DC0();
    if (r == 2)
        g_007B7070 = 7;
    else if (r == 3)
        g_007B7070 = 2;
}

/* 0x00367330, 0x78 bytes, matching. Opens the options screen (phase 3). */
void func_00367330(void)
{
    u8 *o = (u8 *)&s_007B70E0;

    func_00387AC0();
    g_007B7070 = 3;
    func_00376100(3, -1, -1);
    if (o[0x1E] != 0 || o[0x20] != 0 || o[0x21] != 0 || o[0x22] != 0)
        func_003F1070(0);
}

/* 0x003673B0, 0x24 bytes, matching. Phase 3 draw. */
void func_003673B0(void)
{
    func_003852A0();
    func_00387D90();
}

/* 0x003673E0, 0x728 bytes. Phase 3: the options screen. Closing it with OK applies the
 * options, builds the officer lists and opens the entry list (phase 2); Back returns to phase 1.
 * In use: Up / Down pick an offered row (row 4 always, wrapping to OK / the first row on a
 * press), Left / Right a value the row offers, Start resets the values, OK on the OK row
 * closes. */
void func_003673E0(void)
{
    OptionValues values = g_00415EB0;
    int pressed, held;
    u32 row;

    if (g_007B70F4 == 0 || g_007B70F4 == 2)
        return;
    if (g_007B70F4 == 3) {
        if (g_007B70F5 == 0) {
            g_007B7070 = 1;
        } else if (g_007B70F5 == 1) {
            func_00366650();
            if (g_007B70F7 == 0)
                func_003A5240();
            if (func_00327C00() == 10) {
                int i;

                for (i = 0; i < func_0030AB90(); i++)
                    func_0030AF20(i, func_0030AB90());
            }
            func_00365690();
            func_003659A0();
            func_00366380();
            g_007B7070 = 2;
            g_007B93D0 = 0;
            func_00376100(2, -1, -1);
            if (func_003654F0(func_00327C00()) != 0 && func_003A1A80() != 0)
                func_003F1070(1);
        }
        return;
    }
    for (row = 0; row < 6; row++) {               /* an offered row gets its extra values */
        if (s_007B70E0.rows[row] == 1) {
            switch (row) {
            case 0:
            case 1:
            case 2:
            case 5:
                values.offered[row][0] = 1;
                values.offered[row][1] = 1;
                break;
            case 3:
                values.offered[row][1] = 1;
                values.offered[row][2] = 1;
                break;
            case 4:
                values.offered[row][0] = 1;
                values.offered[row][4] = 1;
                break;
            }
        }
    }
    pressed = (unsigned short)pad1_pressed();
    held = (unsigned short)pad1_held();
    if (pressed & BTN_OK) {
        if (g_007B70F6 == 6) {
            SE(1);
            g_007B70F5 = 1;
            func_00387B70();
        }
    } else if (pressed & BTN_CANCEL) {
        SE(2);
        g_007B70F5 = 0;
        func_00387B70();
        func_00376100(1, -1, -1);
    } else if (pressed & BTN_START) {
        SE(1);
        func_003664D0();
    } else if (held & BTN_UP) {
        u32 old = g_007B70F6, r = old, n;

        do {
            n = r - 1;
            if ((int)n < 0 || s_007B70E0.rows[r - 1] != 0)
                break;
            r = n;
        } while (n != 4);
        if ((int)n < 0) {
            if ((pressed & BTN_UP) && old != 6) {
                SE(0);
                g_007B70F6 = 6;
            }
        } else if (old != n) {
            SE(0);
            g_007B70F6 = n;
        }
    } else if (held & BTN_DOWN) {
        u32 old = g_007B70F6, r = old, n;

        do {
            n = r + 1;
            if ((int)n > 6 || s_007B70E0.rows[r + 1] != 0)
                break;
            r = n;
        } while (n != 4);
        if ((int)n < 7) {
            if (old != n) {
                SE(0);
                g_007B70F6 = n;
            }
        } else if (pressed & BTN_DOWN) {
            for (r = 0; (int)r < 7 && s_007B70E0.rows[r] == 0 && r != 4; r++)
                ;
            if (old != r) {
                SE(0);
                g_007B70F6 = r;
            }
        }
    } else if (held & BTN_LEFT) {
        row = g_007B70F6;
        if (row != 6) {
            u32 old = s_007B70E0.values[row];
            int v = old - 1;

            while (v >= 0 && values.offered[row][v] == 0)
                v--;
            if (v < 0) {
                if (pressed & BTN_LEFT) {
                    for (v = 4; v >= 0 && values.offered[row][v] == 0; v--)
                        ;
                    if (old != (v & 0xFF)) {
                        SE(0);
                        s_007B70E0.values[g_007B70F6] = v;
                    }
                }
            } else if (old != (v & 0xFF)) {
                SE(0);
                s_007B70E0.values[g_007B70F6] = v;
            }
        }
    } else if ((held & BTN_RIGHT) && (row = g_007B70F6) != 6) {
        u32 old = s_007B70E0.values[row];
        int v = old + 1;

        while (v < 5 && values.offered[row][v] == 0)
            v++;
        if (v < 5) {
            if (old != (v & 0xFF)) {
                SE(0);
                s_007B70E0.values[g_007B70F6] = v;
            }
        } else if (pressed & BTN_RIGHT) {
            for (v = 0; v < 5 && values.offered[row][v] == 0; v++)
                ;
            if (old != (v & 0xFF)) {
                SE(0);
                s_007B70E0.values[g_007B70F6] = v;
            }
        }
    }
}

/* 0x00367B10, 0xB4 bytes, matching. Makes an officer choosable or not, keeping the counts. */
static void func_00367B10(int officer, int available)
{
    u8 *st = &g_007B7104;
    int delta, edited;

    if (officer >= 0x19F)
        return;
    if (available != 0) {
        delta = 1;
        if (ST_USED(st)[officer] == 1)
            return;
        ST_USED(st)[officer] = 1;
    } else {
        if (ST_USED(st)[officer] == 0)
            return;
        ST_USED(st)[officer] = 0;
        delta = -1;
    }
    edited = officer >= 400 && officer < 0x19F;
    if (edited) {
        ST_LEFT(st) += delta;
    } else {
        ST_LEFT(st) += delta;
        if (officer >= 0x1C && officer < 400)
            ST_LEFT_GEN(st) += delta;
    }
}

/* 0x00367BD0, 0x44 bytes. Whether an officer is choosable (none counts as yes). */
int func_00367BD0(int officer)
{
    int result = 1;

    if (officer < 0x19F) {
        if (g_007B7107[officer] == 0)
            result = 0;
        else if (g_007B7107[officer] == 1)
            result = 1;
    }
    return result;
}

/* 0x00367C20, 0xC4 bytes, matching. The list shown: the choosable officers of g_007B72A8 (or of
 * g_007B7924 when `generals`), 0x19F after them. */
int *func_00367C20(int generals)
{
    u8 *st = &g_007B7104;
    int i, n = 0;

    if (generals == 0) {
        for (i = 0; i < 0x19F; i++) {
            ST_AT(st, 0x1518, i) = 0x19F;
            if (i < ST_NCHOOSABLE(st) && ST_USED(st)[ST_AT(st, 0x1A4, i)] != 0)
                ST_AT(st, 0x1518, n++) = ST_AT(st, 0x1A4, i);
        }
        return ST_SHOWN(st);
    } else {
        for (i = 0; i < 0x19F; i++) {
            ST_AT(st, 0x1518, i) = 0x19F;
            if (i < ST_NGENERALS(st) && ST_USED(st)[ST_AT(st, 0x820, i)] != 0)
                ST_AT(st, 0x1518, n++) = ST_AT(st, 0x820, i);
        }
        return ST_SHOWN(st);
    }
}

void func_0032D300(int a, int *list, int count);
int func_002F4080(int officer);
void func_003A7DA0(int entry, int a);
void func_0030A870(int a, int officer, int entry, int b, int c, int d);
int func_002FB910(void);
void func_002F9900(int a, int b);

/* Whether slot 1 cannot be left empty / skipped (the ruler is also slot 1, or a new game without
 * func_003A1A80). */
#define SLOT1_LOCKED() ((g_007B7070 == 5 && g_007B93B0[0] == g_007B93B0[1]) || \
                        (g_007B7070 == 4 && func_003A1A80() == 0))

/* 0x00367CF0, 0xC84 bytes. Phases 4 and 5 with the list closed: Up / Down (wrapping) move among
 * the slots and OK (7); OK on a slot opens its list, OK on 7 checks and applies the choice;
 * Remove clears a slot; Cancel restores the choosable marks and goes back to phase 2. */
void func_00367CF0(void)
{
    int pressed = (unsigned short)pad1_pressed();
    int held = (unsigned short)pad1_held();
    char text[256];
    int i, j;

    if (g_006934B3 != 0)
        return;
    if (pressed & BTN_OK) {
        u32 slot = g_007B7104;

        if (slot == 7) {
            SE(1);
            if (g_007B7070 == 5) {
                int kind;

                if (g_007B93B0[0] == 0x19F) {
                    SHOW_MESSAGE(0, 0x9A);
                    return;
                }
                if (func_002FB3B0(func_002F4080(g_007B93B0[0])) > 9 && g_007B9394[0] != g_007B93B0[0]) {
                    SHOW_MESSAGE(0, 0x10F);
                    return;
                }
                for (i = 0; i < g_007B9390; i++)
                    func_00365A40(g_007B8D14[i]);
                for (i = 1; i < 7; i++) {
                    if (g_007B93B0[i] < 0x19F && func_002F3E70(g_007B93B0[i]) == 0) {
                        if (i > 0 && i < 4)
                            kind = 2;
                        else if (i > 3 && i < 7)
                            kind = 1;
                        func_00365A80(g_007B93B0[i], func_002F4080(g_007B93B0[0]), g_007B8D10, kind);
                    }
                }
                func_0030AF20(g_007B8D10, func_002F4080(g_007B93B0[0]));
                func_003A7DA0(g_007B8D10, 0);
            } else if (g_007B7070 == 4) {
                int ruler, kind;

                if (g_007B93B0[0] == 0x19F && g_007B93B0[1] == 0x19F && g_007B93B0[2] == 0x19F &&
                    g_007B93B0[3] == 0x19F) {
                    SHOW_MESSAGE(0, 0x99);
                    return;
                }
                if (g_007B93B0[0] < 0x19F && func_002FB3B0(func_002F4080(g_007B93B0[0])) > 9) {
                    SHOW_MESSAGE(0, 0x10F);
                    return;
                }
                for (i = 0; i < g_007B9390; i++)
                    func_00365A40(g_007B8D14[i]);
                ruler = g_007B93B0[0];
                if (ruler == 0x19F) {                 /* the first officer becomes the ruler */
                    ruler = g_007B93B0[1];
                    if (ruler >= 0x19F) {
                        ruler = g_007B93B0[2];
                        if (ruler >= 0x19F && g_007B93B0[3] < 0x19F)
                            ruler = g_007B93B0[3];
                    }
                    func_0030A870(2, ruler, g_007B8D10, 0, 0, 1);
                    g_007B7FA0[g_007B8CA0++] = ruler;
                    func_002F9900(func_002F4080(ruler), func_002FB910());
                    func_003A7DA0(g_007B8D10, 0);
                } else {
                    func_0030AF20(g_007B8D10, func_002F4080(ruler));
                    func_003A7DA0(g_007B8D10, 0);
                }
                for (i = 1; i < 7; i++) {
                    if (g_007B93B0[i] < 0x19F && g_007B93B0[i] != ruler) {
                        if (i > 0 && i < 4)
                            kind = 2;
                        else if (i > 3 && i < 7)
                            kind = 1;
                        func_00365A80(g_007B93B0[i], func_002F4080(ruler), g_007B8D10, kind);
                    }
                }
            }
            g_007B7070 = 2;
            func_00376100(2, -1, -1);
            g_007B93D0 = 1;
        } else {
            if (slot == 0) {
                SE(1);
                if (g_007B8CA0 == 0) {
                    SHOW_MESSAGE(0, 0x96);
                    return;
                }
                func_0032D300(0x10, g_007B7FA0, g_007B8CA0);
            } else if (g_007B7104 > 0 && g_007B7104 < 4) {
                if (g_007B93B0[slot] < 0x19F && func_002F3E70(g_007B93B0[slot]) != 0) {
                    SE(4);
                    return;
                }
                SE(1);
                if (g_007B8CA4 == 0) {
                    SHOW_MESSAGE(0, 0x97);
                    return;
                }
                func_0032D300(0x10, func_00367C20(0), g_007B8CA4);
            } else if (g_007B7104 >= 4 && g_007B7104 < 7) {
                SE(1);
                if (g_007B8CA8 == 0) {
                    SHOW_MESSAGE(0, 0x98);
                    return;
                }
                func_0032D300(0x10, func_00367C20(1), g_007B8CA8);
            }
            g_007B7106 = 1;
        }
    } else if (pressed & BTN_UP) {
        SE(0);
        if (g_007B7104 == 1) {
            if (SLOT1_LOCKED())
                g_007B7104 = 7;
            else
                g_007B7104 = 0;
        } else if (g_007B7104 == 0) {
            g_007B7104 = 7;
        } else {
            g_007B7104--;
        }
    } else if (held & BTN_UP) {
        if (g_007B7104 != 0) {
            if (g_007B7104 == 1) {
                if (g_007B7070 == 5) {
                    if (g_007B93B0[0] == g_007B93B0[1])
                        return;
                } else if (g_007B7070 == 4 && func_003A1A80() == 0) {
                    return;
                }
            }
            SE(0);
            g_007B7104--;
        }
    } else if (pressed & BTN_DOWN) {
        SE(0);
        if (g_007B7104 == 7) {
            if (SLOT1_LOCKED())
                g_007B7104 = 1;
            else
                g_007B7104 = 0;
        } else {
            g_007B7104++;
        }
    } else if (held & BTN_DOWN) {
        if (g_007B7104 < 7) {
            SE(0);
            g_007B7104++;
        }
    } else if (pressed & BTN_CANCEL) {
        for (i = 0; i < 7; i++)
            if (g_007B9394[i] < 0x19F && func_00367BD0(g_007B9394[i]) != 0)
                func_00367B10(g_007B9394[i], 0);
        for (i = 1; i < 7; i++) {
            for (j = 0; j < 7; j++)
                if (g_007B93B0[i] == g_007B9394[j])
                    break;
            if (j > 6)
                func_00367B10(g_007B93B0[i], 1);
        }
        g_007B7070 = 2;
        func_00376100(2, -1, -1);
        SE(2);
    } else if ((pressed & BTN_REMOVE) && g_007B7104 < 7) {
        u8 slot = g_007B7104;

        if (g_007B7070 == 4) {
            if (g_007B93B0[slot] < 0x19F) {
                SE(1);
                if (func_002F3E70(g_007B93B0[g_007B7104]) == 0) {
                    func_00367B10(g_007B93B0[g_007B7104], 1);
                    g_007B8D14[g_007B9390++] = g_007B93B0[g_007B7104];
                }
                g_007B93B0[g_007B7104] = 0x19F;
            }
        } else if (g_007B7070 == 5 && g_007B93B0[slot] < 0x19F) {
            if (func_002F3E70(g_007B93B0[slot]) == 0) {
                SE(1);
                func_00367B10(g_007B93B0[g_007B7104], 1);
                g_007B8D14[g_007B9390++] = g_007B93B0[g_007B7104];
                g_007B93B0[g_007B7104] = 0x19F;
            } else {
                SE(4);
            }
        }
    }
}

void func_003A8DC0(void);
int func_0032D9C0(void);

int func_0032E760(void);
static void func_00367B10(int officer, int in_use);
void func_00367CF0(void);
int func_00327C40(void);
void func_00327C10(int value);
void func_00327880(int on);
void func_003278D0(int on);
void func_00327920(int on);
void func_00327970(u8 value);
void func_003279D0(u8 value);
void func_00327A30(int on);
int func_00375BF0(void);
int func_00375B90(void);
int func_00375C10(void);
int func_00374E00(void);
int func_0030AFF0(int entry);
void func_00327CF0(int value);

void func_00327780(int value);
int func_00372230(void);
void func_0017DF10(void);
void func_001B8F60(int a, int b, int c);
int func_003F1160(int a);
int func_0030AB90(void);
int func_003A1A80(void);
int func_0030C9C0(int entry);
void func_001A7DC0(const char *text, int alpha, int a);
int *func_00365450(void);
void func_003F8BB0(void);
void func_003752D0(void);
void func_00278CF0(void);
void func_003F4F40(void);
void func_003F11D0(void);
void func_00375F90(void);
void func_00384E60(int a);
void func_00387A10(int a, int b, int c);
void func_00366670(void);
void func_00366AC0(void);
void func_003A7360(void);
void func_00373B60(void);
int func_00374E10(void);
void func_003852A0(void);
int func_003725A0(int a);
void func_003838B0(int a, int b);
void func_003673B0(void);
void func_003876C0(void *list, int *officers, int a, int b, int c, int d, int slot, int any);
void func_0032D3C0(void *list);
void func_00367270(void);
void func_00375B00(void);
void func_00376450(void);
int func_003F5410(void);
int func_003F13E0(void);
void func_00366740(void);
void func_00366B10(void);
void func_00366D70(void);
void func_003673E0(void);
void func_003672D0(void);
int func_0017DDA0(void);
void func_00366600(void);
void func_002789C0(void);
void func_002787E0(void);
void func_003A5E20(void);
void func_003655F0(void);
void func_00390780(void);
void func_003F54C0(void);
void func_003F8B80(void);
void func_003F8B30(int a);
void func_003F1580(void);
void func_003F5430(void);
void func_003907B0(void);
void func_00365530(void);
void func_001A2040(void);
void func_001A1AC0(void);
void func_00374E20(void);
void func_003273E0(void);
void func_003EA010(void);
void func_0019FC30(void);
void func_00375D30(void *list);
void func_00376100(int a, int b, int c);
void func_0017E010(int a);
void func_003F4D60(int a);

/* 0x00368980, 0x150 bytes. Phases 4 and 5: the officer of the current slot. With the list open,
 * a choice (func_0032D9C0 1) frees the slot's previous officer (kept in g_007B8D14 unless
 * func_002F3E70), marks the new one in use and closes the list; 0 only closes it. */
void func_00368980(void)
{
    func_003A8DC0();
    if (g_007B7106 == 1) {
        int r = func_0032D9C0();

        if (r == 1) {
            int officer;

            if (SLOT_VALID(g_007B7104) && g_007B93B0[g_007B7104] < 0x19F && func_002F3E70(g_007B93B0[g_007B7104]) == 0)
                g_007B8D14[g_007B9390++] = g_007B93B0[g_007B7104];
            officer = func_0032E760();
            if (SLOT_VALID(g_007B7104))
                func_00367B10(g_007B93B0[g_007B7104], 1);
            g_007B93B0[g_007B7104] = officer;
            if (SLOT_VALID(g_007B7104))
                func_00367B10(officer, 0);
            g_007B7106 = 0;
        } else if (r == 0) {
            g_007B7106 = 0;
        }
    } else if (g_007B7106 == 0) {
        func_00367CF0();
    }
}

/* 0x00368AD0, 0x80 bytes, matching. Applies the start-up settings. */
void func_00368AD0(void)
{
    u8 *o = (u8 *)&s_007B70E0;

    func_00327C10((u8)func_00327C40());
    func_00327880(o[0x17] == 0);
    func_003278D0(o[0x18] == 0);
    func_00327920(o[0x19] == 0);
    func_00327970(o[0x1A]);
    func_003279D0(o[0x1B]);
    func_00327A30(o[0x1C] == 0);
}

/* 0x00368B50, 0xAC bytes, matching. Phase 7: when func_00375BF0 is 0, sets up the chosen entry and its
 * settings and goes on unless func_00372230; else waits for func_00375B90 to be 1. Going on
 * stops the music, fades out and moves to phase 8. */
void func_00368B50(void)
{
    if (func_00375BF0() == 0) {
        int entry = func_0030AFF0(func_00374E00());

        func_00327CF0(entry);
        func_00327780(func_002F8F20(entry));
        func_00368AD0();
        if (func_00372230() != 0)
            return;
    } else if (func_00375B90() != 1) {
        return;
    }
    func_0017DF10();
    func_001B8F60(0, 6, 8);
    g_007B7070 = 8;
}

/* 0x00368C00, 0xAC bytes. Phase 9: leaves the scene (to scene 0x11 when nothing was asked). */
void func_00368C00(void)
{
    if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
        g_0045D89C = 0x11;
    GO_TO_NEXT_SCENE();
}

/* 0x00368CB0, 0x1AC bytes, matching. The help line of the entry list: OK only while func_00375C10 is 1,
 * Back without a valid entry; else Info / Details with Edit when func_003A1A80 and Delete unless
 * the entry is protected (g_007B8CAC set and func_0030C9C0). */
void func_00368CB0(void)
{
    u8 *st = &g_007B7104;
    int entry, valid;

    if (func_003F1160(0) != 0)
        return;
    if (func_00375BF0() != 0 && func_00375C10() == 1) {
        func_001A7DC0(g_0043C7BC, 0x80, 1);
        return;
    }
    entry = func_0030AFF0(func_00374E00());
    valid = entry >= 0 && entry < func_0030AB90();
    if (!valid) {
        func_001A7DC0(g_0043C638, 0x80, 1);
    } else if (func_003A1A80() != 0) {
        if (ST_GAMES(st)[func_00374E00()] == 0 || func_0030C9C0(func_00374E00()) == 0)
            func_001A7DC0(g_0043C818, 0x80, 1);
        else
            func_001A7DC0(g_0043C820, 0x80, 1);
    } else {
        if (ST_GAMES(st)[func_00374E00()] == 0 || func_0030C9C0(func_00374E00()) == 0)
            func_001A7DC0(g_0043C81C, 0x80, 1);
        else
            func_001A7DC0(g_0043C824, 0x80, 1);
    }
}

/* 0x00368E60, 0x58 bytes, matching. The page of the slot's list: 0x11 for slot 0, 0x12 for 1-3, 0x13 for
 * 4-6, else -1. */
int func_00368E60(void)
{
    int page = -1;

    if (g_007B7104 == 0)
        page = 0x11;
    else if (g_007B7104 > 0 && g_007B7104 < 4)
        page = 0x12;
    else if (g_007B7104 >= 4 && g_007B7104 < 7)
        page = 0x13;
    return page;
}

/* 0x00368EC0, 0x358 bytes. Scene 0x13 draw. */
void func_00368EC0(void)
{
    int *pictures = func_00365450();

    func_003F8BB0();
    func_003752D0();
    func_00278CF0();
    func_003F4F40();
    func_003F11D0();
    func_00375F90();
    switch (g_007B7070) {
    case 0:
        func_00384E60(1);
        func_00387A10(pictures[pictures[0] + 6], 0, 0x80);
        func_00366670();
        break;
    case 1:
        func_00387A10(pictures[pictures[0] + 6], 0, 0x80);
        func_00366AC0();
        break;
    case 2:
        func_003A7360();
        func_00373B60();
        if (func_00374E10() == 0) {
            func_003852A0();
            if (func_003F1160(0) == 0)
                func_003838B0(func_003725A0(0x10), 1);
        }
        break;
    case 3:
        func_003673B0();
        break;
    case 4:
    case 5:
        func_003A7360();
        if (g_007B7106 == 0) {
            int any, page;

            if (g_007B93B0[0] == 0x19F && g_007B93B0[1] == 0x19F && g_007B93B0[2] == 0x19F &&
                g_007B93B0[3] == 0x19F)
                any = 0;
            else
                any = 1;
            func_003876C0(g_0045D774, g_007B93B0, 0x18, 0x52, 0, 1, g_007B7104, any);
            if (g_007B7070 == 5) {
                u8 slot = g_007B7104;
                int officer = g_007B93B0[slot];

                if (officer == func_002F8F20(func_0030AFF0(g_007B8D10)) || officer >= 0x19F ||
                    slot >= 7)
                    func_001A7DC0(g_0043C730, 0x80, 1);
                else
                    func_001A7DC0(g_0043C6DC, 0x80, 1);
            } else if (g_007B7070 == 4) {
                if (g_007B93B0[g_007B7104] < 0x19F && g_007B7104 < 7)
                    func_001A7DC0(g_0043C6DC, 0x80, 1);
                else
                    func_001A7DC0(g_0043C730, 0x80, 1);
            }
            page = func_00368E60();
            if (page >= 0)
                func_003838B0(func_003725A0(page), 1);
        } else if (g_007B7106 == 1) {
            func_0032D3C0(g_0045D774);
        }
        break;
    case 6:
        func_003A7360();
        func_00367270();
        break;
    case 7:
        func_003A7360();
        break;
    case 8:
        func_003A7360();
        break;
    }
    if (g_007B7070 == 1)
        func_003852A0();
}

/* 0x00369220, 0x8 bytes, matching. Scene 0x13 step: empty. */
void func_00369220(void)
{
}

/* 0x00369230, 0x218 bytes, matching. Scene 0x13 update: nothing while message box 1 is open or
 * func_003F5410 / func_003F13E0 hold; else the phase's handler. */
int func_00369230(void)
{
    if (box1_open())
        return 1;
    func_00375B00();
    func_00376450();
    if (func_003F5410() != 0)
        return 1;
    if (func_003F13E0() != 0)
        return 1;
    switch (g_007B7070) {
    case 0:
        func_00366740();
        break;
    case 1:
        func_00366B10();
        break;
    case 2:
        func_00366D70();
        break;
    case 3:
        func_003673E0();
        break;
    case 4:
    case 5:
        func_00368980();
        break;
    case 6:
        func_003672D0();
        break;
    case 7:
        func_00368B50();
        break;
    case 8:
        if (func_0017DDA0() != 0 || box1_open())
            return 1;
        g_007B7070 = 9;
        break;
    case 9:
        func_00368C00();
        break;
    case 10:
        g_0045D890 = 1;
        GO_TO_NEXT_SCENE();
        break;
    }
    return 1;
}

/* 0x00369450, 0x54 bytes, matching. Scene 0x13 leave. */
void func_00369450(void)
{
    func_00366600();
    func_002789C0();
    func_002787E0();
    func_003A5E20();
    func_003655F0();
    func_00390780();
    func_003F54C0();
    func_003F8B80();
}

/* 0x003694B0, 0xAC bytes, matching. Scene 0x13 enter: sets everything up, starts music 0x31 and fades
 * in. */
void func_003694B0(void)
{
    func_003F8B30(0);
    func_003F1580();
    func_003F5430();
    func_003907B0();
    func_00365530();
    func_001A2040();
    func_001A1AC0();
    func_00374E20();
    func_00366600();
    func_003273E0();
    func_003EA010();
    func_0019FC30();
    func_00375D30(g_0045D774);
    func_00376100(0, -1, -1);
    func_0017E010(0x31);
    func_001B8F60(1, 6, 8);
    func_003F4D60(0x12);
}
