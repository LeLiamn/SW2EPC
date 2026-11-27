/*
 * bg_manager.c - backgrounds (original source file BgManager.c: its name is passed to the file
 * loader at 0x003F8B30). Decompiled: 0x003F8B30-0x003F961C (the end is a guess: Ghidra finds
 * no function after it before 0x00403D30).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A background is LINKDATA entry 0x9B + n (n 0-4), loaded into g_0045D870 and drawn full-screen
 * (512 x 384) or as one sprite at its own size. The rest of the file is a picker over twelve
 * lists of up to ten entries (the object at func_002FC2C0() + 0x694), drawn in two sliding
 * windows (0x007BFF10, 0x007BFF30).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

/* Flag bytes the original tests as one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;
typedef struct {
    unsigned char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} UBits8;

#define SBIT(lv, n) (((Bits8 *)&(lv))->f##n)
#define UBIT(lv, n) (((UBits8 *)&(lv))->f##n)
typedef unsigned long long u64;

extern u8 *g_0045D870;                    /* (small data) the background */
extern u32 g_0045D128;                    /* (small data) its colour */
extern int g_0045D1C8;                    /* (small data) 1: a half-height mode? */

/* A window's animation (0x14 bytes, see battle_menu_draw.c). */
typedef struct WindowAnim WindowAnim;

/* A sliding window (0x20 bytes): its current rectangle, speed and alpha, a done bit, and its
 * animation record. */
typedef struct {
    short x, y, w, h;
    float speed;
    u8 alpha;
    u8 flags;                /* bit 0: done */
    u8 unknown_e[2];
    WindowAnim *anim;
    u8 unknown_14[0xC];
} SlidingWindow;

extern SlidingWindow g_007BFF10[2];

/* The picker (func_002FC2C0() + 0x694): twelve lists of ten entries (100 = none; list 11 is
 * the table at 0x0041DD60 then 0x65), their counts, the list shown, the cursor. */
typedef struct {
    int list[12][10];        /* +0x000 */
    int count[12];           /* +0x1E0 */
    int shown;               /* +0x210 */
    int cursor;              /* +0x214 */
    int chosen;              /* +0x218 (-1 = cancelled) */
    int unknown_21c;
    int visible;             /* +0x220 */
} Picker;

#define PICKER() (*(Picker **)(func_002FC2C0() + 0x694))

/* 0x00500700: the controllers' state, 0x88 bytes per controller (see scene_config.c). */
typedef struct {
    u8 unknown_00[0x4C];
    unsigned short pressed;
    unsigned short held;
    u8 unknown_50[0x14];
    u8 ready;
    u8 connected;
    u8 unknown_66[0x22];
} PadState;
extern PadState g_00500700[2];
#define pad1_ready() ((g_00500700[0].ready & 1) ? (g_00500700[0].connected & 1) == 1 : 0)
#define pad1_pressed() ((unsigned short)(pad1_ready() ? g_00500700[0].pressed : 0))
#define pad1_held() ((unsigned short)(pad1_ready() ? g_00500700[0].held : 0))

void func_0023AD10(int a, int b, int c, int d, int e);
#define SE(kind) func_0023AD10((kind), 0, 0x2CDC, 0x2CDC, 0x1000)

#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */
#define SCALE_Y(y) ((y) * 0x280 / 0x1E0 * 0x1C0 / 0x200)
#define GS_XYZ(x, y, z) ((u64)(long long)((x) * 16 + 0x7000) |                  \
                         (u64)(long long)(((y) * 16 - 0xE00) / g_70000154 + 0x8000) << 16 | \
                         (u64)(z) << 32)
#define GS_UV(u, v) ((u64)((u) << 4 | 8) | (u64)((v) << 4 | 8) << 16)

extern int g_0041DD60[9];

void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
int func_00102960(int a);
void func_00102EC0(void *data);
u8 *func_00106F10(void);
u64 func_00104ED0(u8 *picture, int a, int b);
u64 *func_00105860(u64 tex, int a);
void func_001059B0(u64 *packet);
u8 *func_002FC2C0(void);
void func_0011ED38(void *to, int value, int size);
int func_003A01A0(int entry);
int func_00313CB0(int entry);
WindowAnim *func_002EE600(void);
WindowAnim *func_002EE5F0(void);
int func_001AE550(float speed, WindowAnim *window, short *pos, u8 *alpha, int a);
int func_0030D7D0(void);
void func_003821E0(int a, int cursor, int x, int y, u8 *entries, int n);
int func_0031D690(Picker *picker);
void func_0037EAA0(int a, int b, int x, int y, int alpha);

/* 0x003F8B30, 0x50 bytes, matching. Loads background `n` (0-4). */
void func_003F8B30(int n)
{
    if (n < 5) {
        g_0045D870 = func_001026D0(1, n + 0x9B, 0, 1, 0, 0, "BgManager.c", 0x1A);
        func_00102960(1);
    }
}

/* 0x003F8B80, 0x2C bytes, matching. */
void func_003F8B80(void)
{
    if (g_0045D870 != 0) {
        func_00102EC0(g_0045D870);
        g_0045D870 = 0;
    }
}

/* 0x003F8BB0, 0x44 bytes, matching. Draws it full-screen. */
void func_003F8BB0(void)
{
    if (g_0045D870 != 0)
        func_001ABA70(g_0045D870, 0, 0, 0, 0x200, 0x180, 0x80, 0, 0);
}

/* 0x003F8C00, 0x200 bytes. Draws it at its own size, in its colour. */
void func_003F8C00(void)
{
    u32 colour = g_0045D128;

    if (g_0045D870 != 0) {
        u8 *header = func_00106F10();
        u64 *p;
        u16 w, h;

        if (g_0045D1C8 == 1)
            p = func_00105860(func_00104ED0(g_0045D870, 0x1320, 0x3FFC), 0);
        else
            p = func_00105860(func_00104ED0(g_0045D870, 0x1D00, 0x3FFC), 0);
        p[4] = (u64)colour | 0x3F80000080000000ULL;
        h = *(u16 *)(header + 0x16);
        w = *(u16 *)(header + 0x14);
        p[5] = 0x80008;
        p[7] = GS_UV(w - 1, h - 1);
        h = *(u16 *)(header + 0x16);
        w = *(u16 *)(header + 0x14);
        p[6] = GS_XYZ(0, 0, 4);
        p[8] = GS_XYZ(w, SCALE_Y(h), 4);
        func_001059B0(p);
    }
}

/* 0x003F8E00, 0x2C bytes, matching. */
void func_003F8E00(int visible)
{
    PICKER()->visible = visible;
}

/* 0x003F8E30, 0x268 bytes. The picker's input once both windows are in place: Up / Down move
 * (wrapping on a press with more than one entry), Cancel gives 1. */
int func_003F8E30(void)
{
    Picker *p = PICKER();
    int n = p->count[p->shown];
    unsigned short pressed, held;

    if (!SBIT(g_007BFF10[1].flags, 0) || !SBIT(g_007BFF10[0].flags, 0))
        return 0;
    pressed = pad1_pressed();
    held = pad1_held();
    if (pressed & 0x10) {
        SE(2);
        p->chosen = -1;
        return 1;
    }
    if (pressed & 0x4000) {
        if (n > 1) {
            SE(0);
            if (p->cursor == n - 1)
                p->cursor = 0;
            else
                p->cursor++;
        }
    } else if (pressed & 0x1000) {
        if (n > 1) {
            SE(0);
            if (p->cursor == 0)
                p->cursor = n - 1;
            else
                p->cursor--;
        }
    } else if (held & 0x4000) {
        if (p->cursor < n - 1) {
            SE(0);
            p->cursor++;
        }
    } else if ((held & 0x1000) && p->cursor > 0) {
        SE(0);
        p->cursor--;
    }
    return 0;
}

/* 0x003F90A0, 0x308 bytes. Builds the lists: entries 0-0x58 (not 0x13) that func_003A01A0
 * offers, in the list of their group (func_00313CB0); list 11 from the table at 0x0041DD60, then
 * 0x65; the rest of each list is 100. Shows list 11. */
void func_003F90A0(void)
{
    Picker *p = PICKER();
    u8 *other = *(u8 **)(func_002FC2C0() + 0x6AC);
    int i, g;

    func_0011ED38(p->count, 0, 0x30);
    other[0x26] = 0;
    for (i = 0; i < 0x59; i++) {
        if (i != 0x13 && func_003A01A0(i) != 0 && (g = func_00313CB0(i)) < 12)
            p->list[g][p->count[g]++] = i;
    }
    for (i = 0; i < 9; i++)
        if (func_003A01A0(g_0041DD60[i]) != 0)
            p->list[11][p->count[11]++] = g_0041DD60[i];
    p->list[11][p->count[11]] = 0x65;
    p->count[11]++;
    for (g = 0; g < 12; g++)
        for (i = p->count[g]; i < 10; i++)
            p->list[g][i] = 100;
    p->cursor = 0;
    p->shown = 0x0B;
    p->chosen = 0x0B;
    p->unknown_21c = -1;
    func_003F8E00(1);
    g_007BFF10[0].speed = 1.0f;
    SBIT(g_007BFF10[0].flags, 0) = 0;
    g_007BFF10[1].speed = 1.0f;
    SBIT(g_007BFF10[1].flags, 0) = 0;
}

/* 0x003F93B0, 0x228 bytes. Steps the two windows and, when visible, draws list 11 and the
 * entry's details. */
void func_003F93B0(void)
{
    Picker *p = PICKER();
    u8 entries[16];
    int n, i;

    g_007BFF10[0].anim = func_002EE600();
    g_007BFF10[0].flags = (g_007BFF10[0].flags & ~1) |
        (func_001AE550(g_007BFF10[0].speed, g_007BFF10[0].anim, &g_007BFF10[0].x,
                       &g_007BFF10[0].alpha, 0) & 1);
    g_007BFF10[1].anim = func_002EE5F0();
    g_007BFF10[1].flags = (g_007BFF10[1].flags & ~1) |
        (func_001AE550(g_007BFF10[1].speed, g_007BFF10[1].anim, &g_007BFF10[1].x,
                       &g_007BFF10[1].alpha, 0) & 1);
    n = p->count[11];
    for (i = 0; i < n; i++)
        entries[i] = p->list[11][i];
    if (p->visible == 1) {
        func_003821E0(func_0030D7D0(), p->cursor, g_007BFF10[1].x, g_007BFF10[1].y, entries, n);
        func_0037EAA0(func_0030D7D0(), func_0031D690(p), g_007BFF10[0].x, 0x68, 0x80);
    }
}

/* 0x003F95E0, 0x40 bytes. The picker's update while it is visible. */
int func_003F95E0(void)
{
    if (PICKER()->visible == 1)
        return func_003F8E30();
    return 0;
}
