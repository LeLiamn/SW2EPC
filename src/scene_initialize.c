/*
 * scene_initialize.c - scenes 0x00 and 0x10 (original source file StateInitialize.c, probable:
 * scene 0x00's picture is loaded with that file name). Scene 0x01 belongs here too (not yet).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Scene 0x00 runs once at start-up: it waits for the memory card check, plays sound cue 0x48,
 * shows a full-screen picture (LINKDATA entry 3) for 150 frames (Start skips it after 50), then
 * plays cues 0x4A and 0x47 and leaves for the requested scene. Scene 0x10 is where the game goes
 * after a soft reset: it stops everything, closes the message boxes and re-applies the saved sound
 * volumes before leaving.
 */

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

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

/* Leaves the current scene (inlined in the original, as in StateShop.c): goes to the requested
 * scene, or back to the one to return to; with neither, to scene `fallback`. */
#define LEAVE_SCENE(fallback) do {                                      \
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)                   \
            g_0045D89C = (fallback);                                    \
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

/* Controller 1 (see scene_shop.c). */
extern u8 g_00500764, g_00500765;
extern unsigned short g_0050074C;
#define pad1_ready() ((g_00500764 & 1) ? (g_00500765 & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_0050074C : 0))
#define BTN_START 0x800

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the bytes used here. */
extern struct {
    u8 unknown_0[0x457C];
    u8 g_0069395C;
    u8 unknown_457D;
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395C (s_0068F3E0.g_0069395C)
#define g_0069395E (s_0068F3E0.g_0069395E)

/* The live settings (0x00669D60, see scene_config.c), up to the saved volumes. */
extern struct {
    u8 unknown_0[0x52];
    u8 g_00669DB2;           /* music volume */
    u8 g_00669DB3;           /* sound-effect volume */
} g_00669D60;
#define g_00669DB2 (g_00669D60.g_00669DB2)
#define g_00669DB3 (g_00669D60.g_00669DB3)
extern int g_70000154;                    /* (scratchpad) screen scale divisor? */
extern const char g_00424AD0[];           /* "StateInitialize.c" */

/* Scene 0x00 state, small data ($gp). */
extern u8 g_0045D280;                     /* frames left on the picture */
extern u8 g_0045D284;                     /* 1 once the picture is done */
extern u64 g_0045D288;                    /* the picture's texture */
extern int g_0045D290;                    /* phase */

void func_002D8060(int value);
void func_002D8160(void);
void func_001E3C30(void);
int func_002DAEE0(void);
void func_0017D8E0(int cue);
u32 func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
u64 func_00107440(u32 data, int a, int b);
void func_00102EC0(u32 data);
void func_001B8F60(int a, int b, int c);
void func_0023AD10(int a, int b, int c, int d, int e);
void func_002DA2C0(void);
u8 *func_00105860(u64 texture, int a);
void func_00105900(u8 *packet, int a);
void func_001037F0(int value);
void func_0017DEA0(int value);
void func_0017DE50(void);
void func_00102990(void);
int func_00102960(int value);
void func_001A2950(void);
void func_0019F550(void);
void func_001B8BF0(void);
void func_0023C160(void);
void func_001023B0(int value);
int func_0017DDA0(void);
void func_0017E0C0(int volume, int b);
void func_0023B530(int volume);

/* ---- Scene 0x00 ------------------------------------------------------------------------------- */

/* 0x00160FA0, 0x8C bytes, matching. Loads the picture (LINKDATA entry 3), shows it for 150 frames and
 * starts the fade-in. */
void func_00160FA0(void)
{
    u32 data = func_001026D0(1, 3, 0, 1, 0, 0, g_00424AD0, 0x19);

    g_0045D288 = func_00107440(data, 0x1D00, 0x3FFC);
    func_00102EC0(data);
    g_0045D280 = 150;
    g_0069395E = 0xFF;
    g_0045D284 = 0;
    func_001B8F60(1, 6, 2);
}

/* 0x00161030, 0x140 bytes. Counts the picture's frames down; after the first 50, Start skips
 * it (returns 0 at once). When the count reaches 0, starts the fade-out; returns 0 once done. */
int func_00161030(void)
{
    int open;

    g_0045D280 = g_0045D280 != 0 ? g_0045D280 - 1 : 0;
    if (g_0045D280 < 100) {
        if (pad1_pressed() & BTN_START) {
            func_0023AD10(5, 0, 0x2CDC, 0x2CDC, 0x1000);
            return 0;
        }
    }
    if (g_0069395E == 0 || g_0069395E == 0xFF)
        open = 0;
    else
        open = 1;
    if (open)
        return 1;
    if (g_0045D284 == 1)
        return 0;
    if (g_0045D280 == 0)
        g_0045D284 = 1;
    if (g_0045D284 == 1)
        func_001B8F60(0, 6, 8);
    return 1;
}

/* 0x00161170, 0xD4 bytes. Draws the picture as one full-screen sprite (GS packet: colour
 * 0x80808080 with Q = 1.0, the X range scaled by g_70000154). */
void func_00161170(void)
{
    u8 *packet = func_00105860(g_0045D288, 0);

    *(u64 *)(packet + 0x20) = 0x3F80000080808080ULL;
    *(u64 *)(packet + 0x28) = 0x80008;
    *(u64 *)(packet + 0x38) = 0x9081108;
    *(u64 *)(packet + 0x30) = (u64)(-0x480 / g_70000154 + 0x8000) << 16 | 0xFFFE00007780ULL;
    *(u64 *)(packet + 0x40) = (u64)(0x480 / g_70000154 + 0x8000) << 16 | 0xFFFE00008880ULL;
    func_00105900(packet, 0);
}

/* 0x00161250, 0x20 bytes, matching. Scene 0x00 enter. */
void func_00161250(void)
{
    func_002D8060(2);
    g_0045D290 = 0;
}

/* 0x00161270, 0x24 bytes, matching. Scene 0x00 leave. */
void func_00161270(void)
{
    func_002D8160();
    func_001E3C30();
}

/* 0x001612A0, 0x17C bytes, matching. Scene 0x00 update: waits for func_002DAEE0 (the memory card check?),
 * then runs the picture between sound cues 0x48 and 0x4A / 0x47, then leaves (scene 1 when
 * nothing is requested). */
int func_001612A0(void)
{
    switch (g_0045D290) {
    case 0:
        if (func_002DAEE0() != 0)
            g_0045D290++;
        break;
    case 1:
        func_0017D8E0(0x48);
        func_00160FA0();
        g_0045D290++;
        break;
    case 2:
        if (func_00161030() == 0)
            g_0045D290++;
        break;
    case 3:
        func_0017D8E0(0x4A);
        g_0045D290++;
        break;
    case 4:
        func_0017D8E0(0x47);
        g_0045D290++;
        break;
    case 5:
        LEAVE_SCENE(1);
        break;
    }
    return 1;
}

/* 0x00161420, 0x8 bytes, matching. Scene 0x00 step: empty. */
void func_00161420(void)
{
}

/* 0x00161430, 0x58 bytes, matching. Scene 0x00 draw: the memory card screen in phase 0, the picture in
 * phase 2. */
void func_00161430(void)
{
    switch (g_0045D290) {
    case 0:
        func_002DA2C0();
        break;
    case 2:
        func_00161170();
        break;
    case 1:
    case 3:
    case 4:
    case 5:
        break;
    }
}

/* ---- Scene 0x10: after a soft reset ----------------------------------------------------------- */

/* 0x0015FE60, 0x8 bytes, matching. Scene 0x10 draw: empty. */
void func_0015FE60(void)
{
}

/* 0x0015FE70, 0x8 bytes, matching. Scene 0x10 step: empty. */
void func_0015FE70(void)
{
}

/* 0x0015FE80, 0xEC bytes, matching. Scene 0x10 update: once func_0017DDA0 is clear (music stopped?),
 * re-applies the saved music and sound-effect volumes and leaves (scene 1 when nothing is
 * requested). */
int func_0015FE80(void)
{
    if (func_0017DDA0() == 0) {
        func_0017E0C0(g_00669DB2, 1);
        func_0023B530(g_00669DB3);
        LEAVE_SCENE(1);
    }
    return 1;
}

/* 0x0015FF70, 0x74 bytes, matching. Scene 0x10 enter: stops what was running and closes the message
 * boxes. */
void func_0015FF70(void)
{
    func_001037F0(0);
    func_0017DEA0(1);
    func_0017DE50();
    func_00102990();
    func_00102960(1);
    g_0069395E = 0;
    g_0069395C = 1;
    func_001A2950();
    func_0019F550();
    func_001B8BF0();
    func_0023C160();
    func_001023B0(0);
}

/* 0x0015FFF0, 0x1C bytes, matching. Scene 0x10 leave. */
void func_0015FFF0(void)
{
    func_001037F0(1);
}
