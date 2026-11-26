/*
 * scene_setup_emp_mogi.c - scene 0x15 (original source file StateSetupEmpMogi.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The scene sets up an Empire-mode game ("Mogi" is probably 模擬, a mock or free game?): it
 * allocates a 0x8EC4-byte work object, loads its data (LINKDATA entry 0x88), and runs the set-up
 * screens of other files (emp_free_setup.c and its neighbours) through a mode number. Mode 9 waits,
 * picks random forces for the computer side (func_003909A0) and leaves the scene.
 */

typedef unsigned char u8;
typedef unsigned int u32;

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
#define g_0045D890 (g_0045D880.force_draw)
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

/* 0x0068F3E0: the message boxes' object (see scene_shop.c). */
typedef struct {
    u8 state;                /* non-zero while open */
    u8 answer;
    u8 unknown_2[0x126];
} MessageBox;
extern struct {
    u8 unknown_0[0x40D3];
    MessageBox box[2];       /* 0x006934B3, 0x006935DB */
    u8 unknown_4323[0x25B];
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_006934B3 (s_0068F3E0.box[0].state)
#define g_0069395E (s_0068F3E0.g_0069395E)

/* Message box 1 is open (inlined in the original). */
static inline int box1_open(void)
{
    int open;

    if (g_0069395E == 0 || g_0069395E == 0xFF)
        open = 0;
    else
        open = 1;
    return open;
}

/* 0x7000015C: random seed in the scratchpad (see main.c). */
#define g_7000015C (*(u32 *)0x7000015C)
/* Next value of the game's random generator (0..65535), inlined in the original. */
#define random16() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, (g_7000015C >> 16) & 0xFFFF)

/* The scene's work object (0x8EC4 bytes, allocated at enter). Only the end is known here; the
 * rest belongs to the set-up screens. */
typedef struct {
    u8 unknown_0[0x8E6C];
    int mode;                /* +0x8E6C set-up screen: 0 start, 2-4, 5, 6-7, 8, 9 leaving */
    u8 unknown_8e70[0x48];
    int timer;               /* +0x8EB8 frames waited in mode 9 */
    u32 data;                /* +0x8EBC loaded data (LINKDATA entry 0x88) */
    u32 data2;               /* +0x8EC0 */
} MogiWork;

extern MogiWork *g_0045D7E4;               /* (small data: reached through $gp) */
extern const char g_00459A40[];            /* "StateSetupEmpMogi.c" (__FILE__ for the loader) */

void *func_00102DB0(int align, int size);   /* allocate */
void func_00102EC0(u32 handle);            /* free */
u32 func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00102960(int value);
void func_00376100(int a, int b, int c);
void func_003BD710(void);
void func_003625D0(int side, int slot, int value);
int func_00362600(int side, int slot);
int func_0036F090(int value);
int func_0036F180(int value);
void func_00364E00(void);
int func_003623B0(void);
int func_00363620(int side);
int func_003620E0(int side, int slot);
void func_00362840(int side, int slot, int value);
int func_003637D0(int side, int slot);
void func_003F8B30(int value);
void func_001A2040(void);
void func_001A1AC0(void);
void func_003630C0(void);
void func_00362630(u32 side, int value);
void func_003621B0(u32 side, u32 slot, int value);
void func_003622F0(int side, int value);
void func_0038D0F0(void);
void func_0038F4B0(void);
void func_003E3100(void);
void func_0030CEF0(void);
void func_0038FBD0(void);
void func_0038D2E0(void);
void func_0038ECF0(void);
void func_0038DF90(void);
void func_0038F6F0(void);
u32 func_0038F4A0(void);
void func_00375D30(u32 value);
void func_002C59F0(void);
void func_002C5A30(void);
void func_002C5A60(void);
void func_0017E010(int track);
void func_001B8F60(int a, int b, int c);
void func_002789C0(void);
void func_002787E0(void);
void func_0038F560(void);
void func_003E3150(void);
void func_0038FDB0(void);
void func_0038D330(void);
void func_0038ED70(void);
void func_0038E000(void);
void func_003F8B80(void);
void func_00376450(void);
void func_003DC110(void);
void func_0038FDD0(void);
void func_0038D340(void);
void func_0038ED90(void);
void func_0038E020(void);
int func_0017DDA0(void);
void func_003638D0(void);
void func_00278CF0(void);
void func_003F8BB0(void);
void func_0038F740(void);
void func_003906F0(void);
void func_0038DC20(void);
void func_0038F480(void);
void func_0038E710(void);

/* 0x00390940, 0x8 bytes, matching. The scene's work object. */
MogiWork *func_00390940(void)
{
    return g_0045D7E4;
}

/* 0x00390950, 0x44 bytes, matching. Goes to set-up mode 5. */
void func_00390950(void)
{
    MogiWork *w = func_00390940();

    w->mode = 5;
    func_00376100(3, -1, -1);
    func_003BD710();
}

/* 0x003909A0, 0x2D0 bytes. Picks the forces of side 1 at random: two different values below 31
 * that func_0036F090 accepts (the second one is cleared when both give 2 in func_0036F180). Then,
 * when func_003623B0() is 0x1C, finds a side for which func_00363620 gives 1 and, on that side,
 * the slot holding 0xB5 (officer 181?), and marks only that slot; the marks are all cleared again
 * when there is no such slot, when the other side has 8 officers, or when func_003637D0 refuses.
 * The variable `side` is the counter of the first loop, reused as in the original (it is 2 when
 * the 0x1C block is skipped). */
void func_003909A0(void)
{
    int side;
    int slot;
    int i;
    int count;
    int found = 0;
    u32 r;

    for (side = 0; side < 2; side++)
        func_003625D0(0, side, 0x1F);

    do {
        r = random16() % 0x1F;
    } while (func_0036F090(r) != 0);
    func_003625D0(1, 0, r);
    do {
        do {
            r = random16() % 0x1F;
        } while (r == func_00362600(1, 0));
    } while (func_0036F090(r) != 0);
    func_003625D0(1, 1, r);
    if (func_0036F180(func_00362600(1, 0)) == 2 && func_0036F180(func_00362600(1, 1)) == 2)
        func_003625D0(1, 1, 0x1F);
    func_00364E00();

    if (func_003623B0() == 0x1C) {
        for (side = 0; side < 2; side++)
            if (func_00363620(side) == 1)
                break;
        for (slot = 0; slot < 8; slot++)
            if (func_003620E0(side, slot) == 0xB5) {
                found = 1;
                break;
            }
        for (i = 0; i < 8; i++)
            func_00362840(side, i, 0);
        if (slot < 8)
            func_00362840(side, slot, 1);
    }

    count = 0;
    for (i = 0; i < 8; i++)
        if (func_003620E0(side == 0 ? 1 : 0, i) != 0x19F)
            count++;
    if (func_003623B0() == 0x1C) {
        if (!found || count >= 8 || func_003637D0(side, slot) != 0)
            for (i = 0; i < 8; i++)
                func_00362840(side, i, 0);
    }
}

/* 0x00390C70, 0x1B8 bytes. Scene enter (unless coming back from scene 9): resets both sides
 * (10, and 10000 for each of 8 slots), allocates and fills the work object, loads its data and
 * starts the set-up screens, music 0x31 and the fade-in. */
void func_00390C70(void)
{
    MogiWork *w;
    u32 side, slot;

    func_003F8B30(1);
    func_001A2040();
    func_001A1AC0();
    if (g_0045D894 == 9)
        return;

    func_003630C0();
    for (side = 0; side < 2; side++) {
        func_00362630(side, 10);
        for (slot = 0; slot < 8; slot++)
            func_003621B0(side, slot, 10000);
    }
    func_003622F0(0, 0);
    func_003622F0(1, 8);
    func_0038D0F0();

    w = func_00102DB0(0x10, sizeof(MogiWork));
    w->mode = 0;
    g_0045D7E4 = w;
    w->data = 0;
    w->data = func_001026D0(1, 0x88, 0, 1, 0, 0, g_00459A40, 206);
    func_0038F4B0();
    func_00102960(1);
    func_003E3100();
    w->data2 = 0;
    func_0030CEF0();
    func_0038FBD0();
    func_0038D2E0();
    func_0038ECF0();
    func_0038DF90();
    func_0038F6F0();
    func_00375D30(func_0038F4A0());
    func_00376100(9, -1, -1);
    func_002C59F0();
    func_002C5A30();
    func_002C5A60();
    func_0017E010(0x31);
    func_001B8F60(1, 6, 8);
}

/* 0x00390E30, 0xA4 bytes, matching. Scene leave: frees what enter made. */
void func_00390E30(void)
{
    MogiWork *w = func_00390940();

    func_002789C0();
    func_002787E0();
    func_0038F560();
    func_003E3150();
    func_00102EC0(w->data);
    func_00102EC0(w->data2);
    w->data = 0;
    w->data2 = 0;
    func_0038FDB0();
    func_0038D330();
    func_0038ED70();
    func_0038E000();
    func_00102EC0((u32)g_0045D7E4);
    func_003F8B80();
}

/* Leave the scene: go to the requested one, or back to the one we came from (inlined in the
 * original, as in the options menu). */
#define leave_scene() do {                                       \
        if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {     \
            g_0045D894 = g_0045D898;                             \
            g_0045D898 = g_0045D8A0;                             \
            g_0045D89C = 0x18;                                   \
        } else {                                                 \
            g_0045D894 = g_0045D898;                             \
            g_0045D898 = g_0045D89C;                             \
            g_0045D89C = g_0045D8A0;                             \
        }                                                        \
    } while (0)

/* 0x00390EE0, 0x2B8 bytes, matching. Scene update, paused while a message box is open: runs the current
 * set-up screen. Mode 1 leaves once box 1 is closed; mode 9 waits for func_0017DDA0 (or 250
 * frames), picks the computer's forces and leaves (to scene 9 when nothing else is set). */
int func_00390EE0(void)
{
    MogiWork *w = func_00390940();

    if (box1_open())
        return 1;
    if (g_006934B3 != 0)
        return 1;
    func_00376450();
    func_003DC110();
    switch (w->mode) {
    case 0:
        w->mode = 2;
        break;
    case 1:
        if (!box1_open()) {
            g_0045D890 = 1;
            leave_scene();
        }
        break;
    case 2:
    case 3:
    case 4:
        func_0038FDD0();
        break;
    case 5:
        func_0038D340();
        break;
    case 6:
    case 7:
        func_0038ED90();
        break;
    case 8:
        func_0038E020();
        break;
    case 9:
        if (func_0017DDA0() != 0 && ++w->timer < 0xFB)
            return 1;
        func_003909A0();
        func_003638D0();
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
            g_0045D89C = 9;
        leave_scene();
        break;
    }
    return 1;
}

/* 0x003911A0, 0x8 bytes, matching. Scene step: empty. */
void func_003911A0(void)
{
}

/* 0x003911B0, 0xA0 bytes, matching. Scene draw: the current set-up screen. */
void func_003911B0(void)
{
    MogiWork *w;

    func_00278CF0();
    func_003F8BB0();
    func_0038F740();
    w = func_00390940();
    switch (w->mode) {
    case 2:
    case 3:
    case 4:
        func_003906F0();
        return;
    case 5:
        func_0038DC20();
        break;
    case 6:
    case 7:
        func_0038F480();
        break;
    case 8:
        func_0038E710();
        break;
    case 0:
    case 1:
    case 9:
        break;
    }
}
