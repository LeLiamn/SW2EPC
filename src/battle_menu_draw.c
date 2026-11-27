/*
 * battle_menu_draw.c - the windows and page drawers of the battle menu (scene 0x08, see
 * scene_battle_menu.c). Original source file unknown. Decompiled: 0x0027FD20 (probable start:
 * the code before it handles object actions, ObjAction.c) to 0x002856CC.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The menu's windows slide and fade: each one is an animation record (WindowAnim, 0x14 bytes)
 * in the tables at 0x00772320 (34 records) and 0x007725F8 (6). func_0027FE60(layer) sets up the
 * records of a page's windows; func_001AE550 steps one and gives its current position and
 * alpha. The drawers build GS sprite packets themselves (TEX0, RGBAQ, UV, XYZ2 pairs) for the
 * textures of g_0068F0F8 / g_0068F0F0, and use the font state at 0x0056CCA4 for text.
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

/* A window's animation (0x14 bytes): from a rectangle and alpha to another over `frames`. */
typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

extern WindowAnim g_00772320[34];
extern u8 g_007725C8[4];                  /* a gauge (func_002C5AC0 / func_002C5AE0) */
extern float g_007725E0;                  /* page 5's marker angle */
extern u32 g_007725E4;                    /* frames since the page opened (lines slide in) */
extern int g_007725E8;                    /* the player of page 5 */
extern int g_007725F4;                    /* a window is still moving */
extern WindowAnim g_007725F8[6];
extern int g_00772D54;                    /* a page's window is still moving */

/* The game state (0x00669D60), the fields used here. */
extern struct {
    u8 unknown_0[0x58];
    int g_00669DB8;          /* game mode */
    u8 unknown_5c[0x2C];
    u32 g_00669DE8;          /* player 1's officer (player 2's at +0x48) */
    u8 unknown_8c[0x138];
    u8 g_00669F24[0x3C];     /* 8 entries of 8 bytes (byte 1: a side) */
    u32 g_00669F60;          /* flags (bit 1: two armies) */
    u8 unknown_204[0x8];
    int g_00669F6C;          /* 1: an Empire battle */
    u8 unknown_210[0x2C];
    int g_00669F9C;
} g_00669D60;
#define g_00669DB8 (g_00669D60.g_00669DB8)
#define g_00669F24 (g_00669D60.g_00669F24)
#define g_00669F60 (g_00669D60.g_00669F60)
#define g_00669F6C (g_00669D60.g_00669F6C)
#define g_00669F9C (g_00669D60.g_00669F9C)
#define PLAYER_OFFICER(p) (*(u32 *)((u8 *)&g_00669D60.g_00669DE8 + (p) * 0x48))

extern u8 g_0073DCA3[];                   /* player records, 0x290 bytes (+0: bit 2 a flag) */
#define FOLLOW_OFF(player) UBIT(g_0073DCA3[(player) * 0x290], 2)

/* The font state (0x0056CCA4): the four corners' colours, then the size. */
extern struct {
    int colour[4];
    u8 unknown_10[0xC];
    float width, height;     /* 0x0056CCC0 */
    u8 unknown_c8[4];
    int g_0056CCCC;          /* line spacing? */
} s_0056CCA4;
#define FONT_COLOUR(c) do {                                             \
        s_0056CCA4.colour[0] = (c);                                     \
        s_0056CCA4.colour[1] = (c);                                     \
        s_0056CCA4.colour[2] = (c);                                     \
        s_0056CCA4.colour[3] = (c);                                     \
    } while (0)
#define FONT_SIZE(s) do {                                               \
        s_0056CCA4.width = (s);                                         \
        s_0056CCA4.height = (s);                                        \
    } while (0)
/* Text in colour 6 (16 points), then back to colour 5 (inlined). */
#define DRAW_TEXT(text, x, y, a) do {                                   \
        FONT_COLOUR(6);                                                 \
        FONT_SIZE(16.0f);                                               \
        func_00146270((text), (x), (y), (a), 0);                        \
        FONT_SIZE(16.0f);                                               \
        FONT_COLOUR(5);                                                 \
    } while (0)

/* GS packets (see the GS manual: XYZ2 is x, y in 1/16 pixel with a 0x8000 offset, z). */
#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */
#define SCALE_Y(y) ((y) * 0x280 / 0x1E0 * 0x1C0 / 0x200)
#define GS_XYZ(x, y, z) ((u64)(long long)((x) * 16 + 0x7000) |                  \
                         (u64)(long long)(((y) * 16 - 0xE00) / g_70000154 + 0x8000) << 16 | \
                         (u64)(z) << 32)
#define GS_XY(x, y) GS_XYZ((x), SCALE_Y(y), 0xFFFE)
#define GS_UV(u, v) ((u64)(long long)((u) << 4 | 8) | (u64)(long long)((v) << 4 | 8) << 16)
#define GS_RGBAQ(r, g, b, a) ((u64)(r) | (u64)(g) << 8 | (u64)(b) << 16 | (u64)(a) << 24 | \
                              0x3F80000000000000ULL)
#define GREY(a) GS_RGBAQ(0x80, 0x80, 0x80, (a))

/* A sprite of texture `tex` of `ctx` (inlined): p[3] TEX0, p[4] RGBAQ, p[5] / p[7] UV, p[6] /
 * p[8] XYZ2. */
#define SPRITE_BEGIN(p, ctx, tex) do {                                  \
        (p) = func_00105860(func_00106C90((ctx), (tex)), 0);            \
        (p)[3] = func_00106C90((ctx), (tex));                           \
    } while (0)
/* The blending register (0x8000000044: normal, 0x48: additive?). */
#define SET_BLEND(value, arg) do {                                      \
        u64 *b_ = func_001050F0();                                      \
        b_[2] = (value);                                                \
        b_[3] = 0x43;                                                   \
        func_00105230(b_, (arg));                                       \
    } while (0)
#define BLEND_NORMAL 0x8000000044ULL
#define BLEND_ADD    0x48ULL

extern void *g_0068F0F0, *g_0068F0F8;     /* texture sets */

/* Icon rectangles (u, v, w, h) of the menu textures (0x00440450). */
extern struct { int u, v, w, h; } g_00440450[];
/* A menu: its lines (x, y, icon). */
typedef struct { int x, y, icon; } MenuLine;
extern MenuLine g_00410E60[4], g_00410E90[8], g_00410EF0[2], g_00410F10[4];
extern int g_00410F40[22], g_00410FA0[22];            /* per page: help kinds */
extern struct { int x, y, tex; } g_00442030[2];       /* per player: a marker */

u64 *func_001050F0(void);
void func_00105230(u64 *packet, int a);
void func_00105390(u64 *packet);
u64 *func_00105860(u64 tex, int a);
u64 func_00106C90(void *ctx, int tex);
void func_001059B0(u64 *packet);
void func_00105900(u64 *packet, int a);
void func_00290F90(const void *a);
void func_002911C0(void);
int func_001AE550(float speed, WindowAnim *window, short *pos, u8 *alpha, int a);
void func_002C5AC0(float speed, u8 *gauge, int a, int b, int c, int d);
u8 func_002C5AE0(u8 *gauge);
void func_002C65C0(int x, int y, int w, int h, int a, u8 alpha);
void func_002C5C60(int x, int y, int w, int h, int a, int b, int c, int d);
int func_0022FF30(void);
int func_0022FF90(void);
int func_00230010(void);
int func_00230050(void);
int func_0036D310(void);
void func_0028D5D0(int value);
void func_0028FBD0(int x, int y, int a, int b, u8 alpha);
void func_0028FE20(int x, int y, int a, int b, u8 alpha);
void func_00290390(int x, int y, int a, int b);
void func_00290770(int x, int y, int a, int b);
u8 func_003DCB30(void);
u8 func_003DCB70(void);
u8 func_002F47A0(u32 officer, int i);
int func_002F6A60(u32 officer);
void func_00146270(const char *text, int x, int y, int a, int b);
void func_001204B0(char *to, const char *format, ...);

/* 0x0027FD20, 0x64 bytes. Whether player `player`'s item `i` is above func_003DCB30's level. */
int func_0027FD20(int player, int i)
{
    u32 officer = PLAYER_OFFICER(player);
    u8 level = func_003DCB30();

    return level < func_002F47A0(officer, i);
}

/* 0x0027FD90, 0x68 bytes. The same for the officer's own item (func_002F6A60). */
int func_0027FD90(int player)
{
    u32 officer = PLAYER_OFFICER(player);
    u8 level = func_003DCB70();

    return level < func_002F47A0(officer, func_002F6A60(officer));
}

/* 0x0027FE00, 0x60 bytes. How many of the eight entries at 0x00669F24 belong to side `side`
 * (byte 1, and not 2). */
int func_0027FE00(u32 side)
{
    int n = 0, i;
    u8 *e = g_00669F24;

    for (i = 0; i < 8; i++) {
        u32 word = *(u32 *)e;
        u8 owner = (u8)(word >> 8);

        if (owner == side && e[1] != 2)
            n++;
        e += 8;
    }
    return n;
}

/* 0x0027FE60, 0x10CC bytes. Sets up the windows of layer `layer` (a page, see scene_battle_menu.c): each
 * record slides and fades from its first rectangle and alpha to its second; odd layers only
 * close (func_0028D5D0). */
void func_0027FE60(int layer)
{
    g_007725E4 = 0;
    if (layer == 0x1a) {
        g_007725F8[4].x0 = -0xB0;
        g_007725F8[4].y0 = 0x4E;
        g_007725F8[4].w0 = 0;
        g_007725F8[4].h0 = 0;
        g_007725F8[4].timer = 0;
        g_007725F8[4].x1 = 8;
        g_007725F8[4].alpha0 = 0x80;
        g_007725F8[4].w1 = 0;
        g_007725F8[4].y1 = 0x4E;
        g_007725F8[4].alpha1 = 0x80;
        g_007725F8[4].h1 = 0;
        g_007725F8[4].frames = 0xA;
        g_007725F8[5].x0 = 0x200;
        g_007725F8[5].y0 = 0x38;
        g_007725F8[5].x1 = 0xB8;
        g_007725F8[5].w0 = 0;
        g_007725F8[5].w1 = 0;
        g_007725F8[5].h0 = 0;
        g_007725F8[5].alpha1 = 0x80;
        g_007725F8[5].timer = 0;
        g_007725F8[5].alpha0 = 0x80;
        g_007725F8[5].y1 = 0x38;
        g_007725F8[5].h1 = 0;
        g_007725F8[5].frames = 0xA;
        g_00772320[12].x0 = 0x288;
        g_00772320[12].y0 = 0x18;
        g_00772320[12].y1 = 0x18;
        g_00772320[12].w0 = 0x88;
        g_00772320[12].alpha1 = 0x80;
        g_00772320[12].h0 = 0x18;
        g_00772320[12].timer = 0;
        g_00772320[12].alpha0 = 0x80;
        g_00772320[12].x1 = 0x1D8;
        g_00772320[12].w1 = 0x88;
        g_00772320[12].h1 = 0x18;
        g_00772320[12].frames = 0xA;
    }
    else if (layer == 0x19) {
        g_007725F8[3].x0 = 0x100;
        g_007725F8[3].y0 = 0xCE;
        g_007725F8[3].w0 = 0;
        g_007725F8[3].h0 = 0;
        g_007725F8[3].timer = 0;
        g_007725F8[3].alpha0 = 0;
        g_007725F8[3].x1 = 0x24;
        g_007725F8[3].y1 = 0x58;
        g_007725F8[3].w1 = 0x1B8;
        g_007725F8[3].h1 = 0xEC;
        g_007725F8[3].alpha1 = 0x80;
        g_007725F8[3].frames = 0xA;
    }
    else if (layer == 0x18) {
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
    else if (layer == 0x16) {
        g_00772320[13].x0 = 0x200;
        g_00772320[13].y0 = 0x34;
        g_00772320[13].timer = 0;
        g_00772320[13].w0 = 0xF0;
        g_00772320[13].h0 = 0xE2;
        g_00772320[13].alpha0 = 0x80;
        g_00772320[13].x1 = 0x108;
        g_00772320[13].y1 = 0x34;
        g_00772320[13].h1 = 0xE2;
        g_00772320[13].w1 = 0xF0;
        g_00772320[13].alpha1 = 0x80;
        g_00772320[13].frames = 0xA;
        g_00772320[14].x0 = 0x302;
        g_00772320[14].y0 = 0x118;
        g_00772320[14].h0 = 0x8A;
        g_00772320[14].w0 = 0xF0;
        g_00772320[14].alpha0 = 0x80;
        g_00772320[14].timer = 0;
        g_00772320[14].x1 = 0x108;
        g_00772320[14].y1 = 0x118;
        g_00772320[14].w1 = 0xFA;
        g_00772320[14].h1 = 0x8A;
        g_00772320[14].alpha1 = 0x80;
        g_00772320[14].frames = 0xA;
    }
    else if (layer == 0x15) {
        g_00772320[2].x0 = 0x10;
        if ((g_00669F60 & 2) != 0) {
            g_00772320[2].x0 = 0x30;
        }
        g_00772320[2].y0 = -0x18;
        g_00772320[2].w0 = 0x80;
        g_00772320[2].w1 = 0x80;
        g_00772320[2].h0 = 0x18;
        g_00772320[2].timer = 0;
        g_00772320[2].alpha0 = 0x80;
        g_00772320[2].y1 = 0x34;
        g_00772320[2].h1 = 0x18;
        g_00772320[2].alpha1 = 0x80;
        g_00772320[2].frames = 0xA;
        g_00772320[2].x1 = g_00772320[2].x0;
    }
    else if (layer == 0x14) {
        g_00772320[1].x0 = 0x68;
        g_00772320[1].y0 = -0x20;
        g_00772320[1].w0 = 0xA8;
        g_00772320[1].h0 = 0x20;
        g_00772320[1].timer = 0;
        g_00772320[1].alpha0 = 0x80;
        g_00772320[1].x1 = 0x68;
        g_00772320[1].y1 = 0x10;
        g_00772320[1].w1 = 0xA8;
        g_00772320[1].h1 = 0x20;
        g_00772320[1].alpha1 = 0x80;
        g_00772320[1].frames = 0xA;
        g_00772320[12].y0 = 0x18;
        g_00772320[12].x0 = 0x288;
        g_00772320[12].w0 = 0x88;
        g_00772320[12].h0 = 0x18;
        g_00772320[12].y1 = 0x18;
        g_00772320[12].timer = 0;
        g_00772320[12].alpha0 = 0x80;
        g_00772320[12].x1 = 0x1D8;
        g_00772320[12].h1 = 0x18;
        g_00772320[12].w1 = 0x88;
        g_00772320[12].frames = 0xA;
        g_00772320[12].alpha1 = 0x80;
        g_00772320[33].x0 = -0xC8;
        g_00772320[33].y0 = 0x50;
        g_00772320[33].w0 = 0;
        g_00772320[33].h0 = 0;
        g_00772320[33].timer = 0;
        g_00772320[33].alpha0 = 0x80;
        g_00772320[33].x1 = 8;
        g_00772320[33].y1 = 0x50;
        g_00772320[33].w1 = 0;
        g_00772320[33].h1 = 0;
        g_00772320[33].alpha1 = 0x80;
        g_00772320[33].frames = 0xA;
    }
    else if (layer == 0x13) {
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
    else if (layer == 0x11) {
        func_0028D5D0(0x1e);
    }
    else if (layer == 0xf) {
        func_0028D5D0(0x1c);
    }
    else if (layer == 0xd) {
        func_0028D5D0(0x1a);
    }
    else if (layer == 0xb) {
        g_007725E0 = 0;
        g_00772320[27].x0 = 0xF8;
        g_00772320[27].w0 = 0;
        g_00772320[27].y0 = 0x10E;
        g_00772320[27].timer = 0;
        g_00772320[27].h0 = 0;
        g_00772320[27].alpha0 = 0x80;
        g_00772320[27].x1 = 0x18;
        g_00772320[27].y1 = 0xBC;
        g_00772320[27].w1 = 0x1C0;
        g_00772320[27].h1 = 0xA4;
        g_00772320[27].alpha1 = 0x80;
        g_00772320[27].frames = 0xA;
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
    else if (layer == 9) {
        func_0028D5D0(0x18);
    }
    else if (layer == 7) {
        g_00772320[26].x0 = 0x100;
        g_00772320[26].y0 = 0x128;
        g_00772320[26].w0 = 0;
        g_00772320[26].h0 = 0;
        g_00772320[26].timer = 0;
        g_00772320[26].alpha0 = 0x80;
        g_00772320[26].x1 = 0x20;
        g_00772320[26].y1 = 0xF8;
        g_00772320[26].w1 = 0x1C0;
        g_00772320[26].h1 = 0x60;
        g_00772320[26].alpha1 = 0x80;
        g_00772320[26].frames = 0xA;
        func_0028D5D0(0x16);
    }
    else if (layer == 5) {
        func_0028D5D0(0xc);
        g_00772320[30].x0 = 0x200;
        g_00772320[30].w0 = 0;
        g_00772320[30].timer = 0;
        g_00772320[30].y0 = 0x38;
        g_00772320[30].alpha0 = 0x80;
        g_00772320[30].h0 = 0;
        g_00772320[30].x1 = 0x184;
        g_00772320[30].y1 = 0x38;
        g_00772320[30].w1 = 0;
        g_00772320[30].alpha1 = 0x80;
        g_00772320[30].frames = 0xA;
        g_00772320[30].h1 = 0;
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 0);
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
    else if (layer == 3) {
        g_00772320[13].x0 = 0x200;
        g_00772320[13].w0 = 0;
        g_00772320[13].y0 = 0x4E;
        g_00772320[13].timer = 0;
        g_00772320[13].h0 = 0;
        g_00772320[13].alpha0 = 0x80;
        g_00772320[13].x1 = 0xF4;
        g_00772320[13].y1 = 0x4E;
        g_00772320[13].w1 = 0x104;
        g_00772320[13].h1 = 0xFC;
        g_00772320[13].alpha1 = 0x80;
        g_00772320[13].frames = 0xA;
    }
    else if (layer == 1) {
        if (g_00669DB8 != 2) {
            g_00772320[4].x0 = 0x258;
            g_00772320[4].y0 = 0x34;
            g_00772320[4].w0 = 0;
            g_00772320[4].h0 = 0;
            g_00772320[4].timer = 0;
            g_00772320[4].alpha0 = 0x80;
            g_00772320[4].x1 = 0x80;
            g_00772320[4].y1 = 0x34;
            g_00772320[4].w1 = 0;
            g_00772320[4].h1 = 0;
            g_00772320[4].alpha1 = 0x80;
            g_00772320[4].frames = 0xA;
            g_00772320[6].x0 = 0x200;
            g_00772320[6].y0 = 0x46;
            g_00772320[6].w0 = 0;
            g_00772320[6].h0 = 0;
            g_00772320[6].timer = 0;
            g_00772320[6].alpha0 = 0x80;
            g_00772320[6].x1 = 0xC4;
            g_00772320[6].y1 = 0x46;
            g_007725F8[0].w0 = 0;
            g_00772320[6].w1 = 0;
            g_007725F8[0].timer = 0;
            g_00772320[6].h1 = 0;
            g_00772320[6].alpha1 = 0x80;
            g_00772320[6].frames = 0xA;
            g_007725F8[0].x0 = 0x258;
            g_007725F8[0].y0 = 8;
            g_007725F8[0].h0 = 0;
            g_007725F8[0].alpha0 = 0x80;
            g_007725F8[0].x1 = 0xF0;
            g_007725F8[0].y1 = 8;
            g_007725F8[1].w0 = 0;
            g_007725F8[0].w1 = 0;
            g_007725F8[1].timer = 0;
            g_007725F8[0].h1 = 0;
            g_007725F8[0].alpha1 = 0x80;
            g_007725F8[0].frames = 0xA;
            g_007725F8[1].x0 = 0x258;
            g_007725F8[1].y0 = 0x4C;
            g_007725F8[1].h0 = 0;
            g_007725F8[1].alpha0 = 0x80;
            g_007725F8[1].x1 = 0x140;
            g_007725F8[1].y1 = 0x4C;
            g_007725F8[1].w1 = 0;
            g_007725F8[1].h1 = 0;
            g_007725F8[1].alpha1 = 0x80;
            g_007725F8[1].frames = 0xA;
            g_007725F8[2].x0 = 0x258;
            g_007725F8[2].w0 = 0;
            g_007725F8[2].y0 = 0xA8;
            g_007725F8[2].timer = 0;
            g_007725F8[2].h0 = 0;
            g_007725F8[2].x1 = 0x140;
            g_007725F8[2].alpha0 = 0x80;
            g_007725F8[2].y1 = 0xA8;
            g_007725F8[2].h1 = 0;
            g_007725F8[2].w1 = 0;
            g_007725F8[2].alpha1 = 0x80;
            g_007725F8[2].frames = 0xA;
        }
        g_00772320[5].x0 = 0x200;
        g_00772320[5].w0 = 0;
        g_00772320[5].y0 = 0x144;
        g_00772320[5].timer = 0;
        g_00772320[5].h0 = 0;
        g_00772320[5].alpha0 = 0x80;
        g_00772320[5].x1 = 0xFC;
        g_00772320[5].y1 = 0x144;
        g_00772320[5].w1 = 0;
        g_00772320[5].h1 = 0;
        g_00772320[5].alpha1 = 0x80;
        g_00772320[5].frames = 0xA;
        g_00772320[3].x0 = 0x200;
        g_00772320[3].y0 = 0x4E;
        g_00772320[3].y1 = 0x4E;
        g_00772320[3].w0 = 0x60;
        g_00772320[3].h0 = 0;
        g_00772320[3].timer = 0;
        g_00772320[3].alpha0 = 0x80;
        g_00772320[3].x1 = 0x18A;
        g_00772320[3].w1 = 0x60;
        g_00772320[3].h1 = 0;
        g_00772320[3].alpha1 = 0x80;
        g_00772320[3].frames = 0xA;
        g_00772320[8].x0 = 0x200;
        g_00772320[8].y0 = 0x4E;
        g_00772320[8].timer = 0;
        g_00772320[8].w0 = 0x100;
        g_00772320[8].h0 = 0xAC;
        g_00772320[8].alpha0 = 0x80;
        g_00772320[8].x1 = 0xF8;
        g_00772320[8].y1 = 0x4E;
        g_00772320[8].w1 = 0x100;
        g_00772320[8].h1 = 0xAC;
        g_00772320[8].alpha1 = 0x80;
        g_00772320[8].frames = 0xA;
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
    else if (layer == 0) {
        if (g_00669DB8 != 2) {
            g_00772320[4].x0 = 0x258;
            g_00772320[4].y0 = 0x34;
            g_00772320[4].w0 = 0;
            g_00772320[4].h0 = 0;
            g_00772320[4].timer = 0;
            g_00772320[4].alpha0 = 0x80;
            g_00772320[4].x1 = 0x80;
            g_00772320[4].y1 = 0x34;
            g_00772320[4].w1 = 0;
            g_00772320[4].h1 = 0;
            g_00772320[4].alpha1 = 0x80;
            g_00772320[4].frames = 0xA;
            g_00772320[6].x0 = 0x200;
            g_00772320[6].y0 = 0x46;
            g_00772320[6].w0 = 0;
            g_00772320[6].h0 = 0;
            g_00772320[6].timer = 0;
            g_00772320[6].alpha0 = 0x80;
            g_00772320[6].x1 = 0xC4;
            g_00772320[6].y1 = 0x46;
            g_007725F8[0].w0 = 0;
            g_00772320[6].w1 = 0;
            g_007725F8[0].timer = 0;
            g_00772320[6].h1 = 0;
            g_00772320[6].alpha1 = 0x80;
            g_00772320[6].frames = 0xA;
            g_007725F8[0].x0 = 0x258;
            g_007725F8[0].y0 = 8;
            g_007725F8[0].h0 = 0;
            g_007725F8[0].alpha0 = 0x80;
            g_007725F8[0].x1 = 0xF0;
            g_007725F8[0].y1 = 8;
            g_007725F8[1].w0 = 0;
            g_007725F8[0].w1 = 0;
            g_007725F8[1].timer = 0;
            g_007725F8[0].h1 = 0;
            g_007725F8[0].alpha1 = 0x80;
            g_007725F8[0].frames = 0xA;
            g_007725F8[1].x0 = 0x258;
            g_007725F8[1].y0 = 0x4C;
            g_007725F8[1].h0 = 0;
            g_007725F8[1].alpha0 = 0x80;
            g_007725F8[1].x1 = 0x140;
            g_007725F8[1].y1 = 0x4C;
            g_007725F8[1].w1 = 0;
            g_007725F8[1].h1 = 0;
            g_007725F8[1].alpha1 = 0x80;
            g_007725F8[1].frames = 0xA;
            g_007725F8[2].x0 = 0x258;
            g_007725F8[2].w0 = 0;
            g_007725F8[2].y0 = 0xA8;
            g_007725F8[2].timer = 0;
            g_007725F8[2].h0 = 0;
            g_007725F8[2].x1 = 0x140;
            g_007725F8[2].alpha0 = 0x80;
            g_007725F8[2].y1 = 0xA8;
            g_007725F8[2].h1 = 0;
            g_007725F8[2].w1 = 0;
            g_007725F8[2].alpha1 = 0x80;
            g_007725F8[2].frames = 0xA;
        }
        g_00772320[0].x0 = 0x10;
        g_00772320[0].y0 = -0x28;
        g_00772320[0].w0 = 0xC8;
        g_00772320[0].h0 = 0x28;
        g_00772320[0].timer = 0;
        g_00772320[0].alpha0 = 0x80;
        g_00772320[3].y1 = 0x4E;
        g_00772320[0].x1 = 0x10;
        g_00772320[0].y1 = 0x10;
        g_00772320[0].w1 = 0xC8;
        g_00772320[0].h1 = 0x28;
        g_00772320[0].alpha1 = 0x80;
        g_00772320[0].frames = 0xA;
        g_00772320[3].x0 = 0x200;
        g_00772320[3].y0 = 0x4E;
        g_00772320[3].w0 = 0x60;
        g_00772320[3].h0 = 0;
        g_00772320[3].timer = 0;
        g_00772320[3].alpha0 = 0x80;
        g_00772320[3].x1 = 0x18A;
        g_00772320[3].w1 = 0x60;
        g_00772320[3].h1 = 0;
        g_00772320[3].alpha1 = 0x80;
        g_00772320[3].frames = 0xA;
        g_00772320[5].x0 = 0x200;
        g_00772320[5].y1 = 0x144;
        g_00772320[5].y0 = 0x144;
        g_00772320[5].h1 = 0;
        g_00772320[5].w0 = 0;
        g_00772320[5].frames = 0xA;
        g_00772320[5].h0 = 0;
        g_00772320[5].timer = 0;
        g_00772320[5].w1 = 0;
        g_00772320[5].alpha0 = 0x80;
        g_00772320[8].y0 = 0x4E;
        g_00772320[5].x1 = 0xFC;
        g_00772320[5].alpha1 = 0x80;
        g_00772320[8].w0 = 0x100;
        g_00772320[8].x0 = 0x200;
        g_00772320[8].h0 = 0xAC;
        g_00772320[8].timer = 0;
        g_00772320[8].alpha0 = 0x80;
        g_00772320[8].x1 = 0xF8;
        g_00772320[8].y1 = 0x4E;
        g_00772320[8].w1 = 0x100;
        g_00772320[8].h1 = 0xAC;
        g_00772320[8].alpha1 = 0x80;
        g_00772320[8].frames = 0xA;
        g_00772320[7].x0 = 0x200;
        g_00772320[7].y0 = 0xFC;
        g_00772320[7].y1 = 0xFC;
        g_00772320[7].w0 = 0x160;
        g_00772320[7].h1 = 0x34;
        g_00772320[7].h0 = 0x34;
        g_00772320[7].frames = 0xA;
        g_00772320[7].timer = 0;
        g_00772320[7].alpha0 = 0x80;
        g_00772320[7].x1 = 0x98;
        g_00772320[7].w1 = 0x160;
        g_00772320[7].alpha1 = 0x80;
        func_002C5AC0(1.0f, g_007725C8, 0x40, 0x40, 0, 1);
    }
}


extern u8 g_00411350[], g_00411360[], g_00411370[];

/* 0x00280F30, 0x158 bytes. The menu's background (texture 0x3F63) between func_00290F90 layers. */
void func_00280F30(void)
{
    u64 *b, *p;

    func_00290F90(g_00411350);
    b = func_001050F0();
    b[2] = BLEND_NORMAL;
    b[3] = 0x43;
    func_00105390(b);
    SPRITE_BEGIN(p, g_0068F0F8, 0x3F63);
    p[4] = GREY(0x80);
    p[5] = 0x0B081708;
    p[7] = 0x10F81CF8;
    p[6] = GS_XYZ(13, 57, 0xFFFE);
    p[8] = GS_XYZ(166, 236, 0xFFFE);
    func_001059B0(p);
    func_002911C0();
    func_00290F90(g_00411360);
    func_00290F90(g_00411370);
}

/* Whether a menu line's icon is offered (inlined). */
#define ICON_OFFERED(icon) ((icon) == 0x0E ? func_00230050() : (icon) == 5 ? func_00230010() : \
                            (icon) == 0x0D ? func_0022FF90() : (icon) == 1 ? func_0022FF30() : 1)

/* One menu line, sliding in from the left with the frames since the page opened (inlined). */
static void draw_line(const MenuLine *line, int i, int bright, int offered, int arg)
{
    u64 *p;
    u32 grey = (u32)((bright ? 1.0f : 0.675f) * 128.0f) & 0xFF;
    u32 alpha = offered ? 0x80 : 0x50;
    float x = ((float)line->x + 160.0f) / 10.0f * (float)(g_007725E4 - i * 2) - 160.0f;
    int icon = line->icon;

    if ((float)line->x <= x)
        x = (float)line->x;
    SPRITE_BEGIN(p, g_0068F0F8, 0x3F60);
    p[4] = GS_RGBAQ(grey, grey, grey, alpha);
    p[5] = GS_UV(g_00440450[icon].u, g_00440450[icon].v);
    p[7] = GS_UV(g_00440450[icon].u + g_00440450[icon].w - 1,
                 g_00440450[icon].v + g_00440450[icon].h - 1);
    p[6] = GS_XY((int)x, line->y);
    p[8] = GS_XY((int)x + g_00440450[icon].w, line->y + g_00440450[icon].h);
    func_00105900(p, arg);
}

/* 0x00281090, 0x534 bytes. Draws `n` lines of a menu with the cursor's bar on line `cursor`. */
void func_00281090(const MenuLine *lines, u8 n, u8 cursor, int arg)
{
    int i;

    SET_BLEND(BLEND_NORMAL, arg);
    func_002C65C0(-0x3C, lines[cursor].y - 2, 0x100, 0x1C, 0, func_002C5AE0(g_007725C8));
    for (i = 0; i < n; i++) {
        draw_line(lines, i, i == cursor, ICON_OFFERED(lines->icon), arg);
        lines++;
    }
}

/* 0x002815D0, 0x668 bytes. The same with the two players' cursors (two armies). */
void func_002815D0(const MenuLine *lines, u8 n, const u8 *cursors, int arg)
{
    int i;

    SET_BLEND(BLEND_NORMAL, arg);
    func_002C5AE0(g_007725C8);
    func_002C5C60(-0x3C, lines[cursors[0]].y - 2, 0x100, 0x1C, 0, 0x9E, lines[cursors[0]].y, 0);
    func_002C5C60(-0x3C, lines[cursors[1]].y - 2, 0x100, 0x1C, 1, 0xBE, lines[cursors[1]].y, 0);
    for (i = 0; i < n; i++) {
        int bright = i == cursors[0] || i == cursors[1];

        draw_line(lines, i, bright, ICON_OFFERED(lines->icon), arg);
        lines++;
    }
}

typedef struct { int k[22]; } HelpKinds;

/* 0x00281C40, 0x90 bytes, matching. The help kind of page `page` (3 becomes 6 in an Empire battle or with
 * func_0036D310). */
int func_00281C40(int page)
{
    HelpKinds kinds = *(HelpKinds *)g_00410F40;
    int kind = kinds.k[page];

    if (kind == 3 && (g_00669F6C == 1 || func_0036D310() != 0))
        kind = 6;
    return kind;
}

/* 0x00281CD0, 0x48 bytes, matching. */
int func_00281CD0(int page)
{
    HelpKinds kinds = *(HelpKinds *)g_00410FA0;

    return kinds.k[page];
}

/* 0x00281D20, 0x2F8 bytes. Steps the frame window; on a page other than 0 with two armies, also
 * the marker of the player using the menu. */
void func_00281D20(int page, int player)
{
    short pos[4];
    u8 alpha;

    g_007725F4 = func_001AE550(1.0f, &g_00772320[0], pos, &alpha, 0) == 0;
    if (page != 0 && (g_00669F60 & 2) != 0) {
        u64 *p;
        int u, v;

        SPRITE_BEGIN(p, g_0068F0F8, g_00442030[player].tex + 0x3F53);
        g_007725F4 = func_001AE550(1.0f, &g_00772320[12], pos, &alpha, 0) == 0 || g_007725F4 != 0;
        u = g_00442030[player].x;
        v = g_00442030[player].y;
        p[4] = GREY(0x80);
        p[5] = GS_UV(u, v);
        p[7] = GS_UV(u + 0x1E, v + 0x16);
        p[6] = GS_XY(pos[0], pos[1]);
        p[8] = GS_XY(pos[0] + 0x20, pos[1] + 0x18);
        func_00105900(p, 0);
    }
}

/* 0x00282020, 0x1CC bytes. Page 0: the main menu's lines (sliding in), then its windows. */
void func_00282020(u8 *cursors, u8 *frame, u8 *grid, int *ready)
{
    const MenuLine *lines;
    u32 count, n;
    short pos[4];
    u8 alpha;

    if (g_00669F6C == 1) {
        count = 4;
        lines = g_00410E60;
    } else {
        count = 8;
        lines = g_00410E90;
    }
    n = (g_007725E4 >> 1) + 1;
    if (n >= (count & 0xFF))
        n = count & 0xFF;
    if (g_007725E4 < (count & 0xFF) * 2 + 10)
        g_007725E4++;
    if ((g_00669F60 & 2) == 0)
        func_00281090(lines, n, cursors[0], 0);
    else
        func_002815D0(lines, n, cursors, 0);
    g_007725F4 = func_001AE550(1.0f, &g_00772320[5], pos, &alpha, 0) == 0 || g_007725F4 != 0;
    func_0028FBD0(pos[0], pos[1], 0, 0, alpha);
    func_001AE550(1.0f, &g_007725F8[0], pos, &alpha, 0);
    func_0028FE20(pos[0], pos[1], 0, 0, alpha);
    func_001AE550(1.0f, &g_007725F8[1], pos, &alpha, 0);
    func_00290390(pos[0], pos[1], 0, 0);
    func_001AE550(1.0f, &g_007725F8[2], pos, &alpha, 0);
    func_00290770(pos[0], pos[1], 0, 0);
}

extern int g_00411000[10], g_00411030[5], g_00411050[10], g_00411080[5];
extern const char *g_0042DC10[];          /* weapon kind names ("Cross Spear", ...) */
extern const char g_00440540[];           /* "%d"? */
void func_002C7310(int x, int y, int z, int w, int h, int alpha, int a);
const char *func_0019B280(char *text, u32 officer);
u64 *func_001A93A0(int x, int y, int a, int b, int c, int d, int e, int f);
int func_002C5C10(u32 officer);
void func_001A9B30(u64 *a, int b, int c);
void func_001AA2C0(u64 *a, int b);
void func_002D67E0(int icon, int x, int y, int a, int b, int alpha);
void func_002F39F0(u32 officer);
void func_002F4C40(u32 officer);
void func_002F4DD0(u32 officer);
void func_002F4F60(u32 officer);
char func_002F41E0(u32 officer);
int func_002F34E0(u32 officer);
int func_002CAA90(u32 officer, int a);
const char *func_0019B340(u32 officer);
void func_00120928(char *to, const char *from);
void func_002CA490(int x, int y, int a, int b, int c, int alpha, int d);
int func_002F5730(u32 officer);
u8 *func_0035DEC0(u32 officer, int i);
void func_002C5160(float size, const char *text, int x, int y, int w, int a, int b);
int func_002CA730(u32 officer, int stat);

/* 0x002821F0, 0x890 bytes. Page 1, the officer: window frame, then (unless `hidden`) name,
 * portrait, ten stat icons, level and experience, the weapon kind and five values. */
void func_002821F0(int x, int y, int w, int h, int a, int player, int hidden)
{
    char text[128];
    u8 weapon[20];
    int icons[10], stats[5], icon_y[10], stat_y[5];
    u32 officer;
    int i, colour;
    u64 *portrait;
    u32 kind;
    u8 *src;

    for (i = 0; i < 10; i++)
        icons[i] = g_00411000[i];
    for (i = 0; i < 5; i++)
        stats[i] = g_00411030[i];
    for (i = 0; i < 10; i++)
        icon_y[i] = g_00411050[i];
    for (i = 0; i < 5; i++)
        stat_y[i] = g_00411080[i];
    officer = PLAYER_OFFICER(player);
    func_002C7310(x, y, 0, w, h, 0x80, a);
    if (hidden != 0)
        return;
    FONT_COLOUR(6);
    FONT_SIZE(20.0f);
    func_00146270(func_0019B280(text, officer), x + 0x10, y + 0x16, a, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
    portrait = func_001A93A0(x + 0x10, y + 0x2E, 0, 0x3C, 0x44, 0x80, 0, 1);
    func_001A9B30(portrait, func_002C5C10(officer), 1);
    func_001AA2C0(portrait, 0);
    for (i = 0; i < 10; i++)
        func_002D67E0(icons[i], x + 0x50, y + icon_y[i], 0, a, 0x80);
    func_002F39F0(officer);
    func_002F4C40(officer);
    func_002F4DD0(officer);
    func_002F4F60(officer);
    {
        char level = func_002F41E0(officer);
        int exp = func_002F34E0(officer);

        colour = func_002CAA90(officer, 9) == 0 ? 6 : 1;
        func_001204B0(text, g_00440540, level + 1);
        FONT_SIZE(14.0f);
        FONT_COLOUR(colour);
        func_00146270(text, x + 0x94, y + 0x2E, a, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        colour = func_002CAA90(officer, 8) == 0 ? 6 : 1;
        func_001204B0(text, g_00440540, exp);
        FONT_SIZE(14.0f);
        FONT_COLOUR(colour);
        func_00146270(text, x + 0x94, y + 0x40, a, 0);
        FONT_SIZE(16.0f);
        FONT_COLOUR(5);
        func_001204B0(text, g_00440540, exp);
    }
    func_00120928(text, func_0019B340(officer));
    FONT_COLOUR(6);
    FONT_SIZE(16.0f);
    func_00146270(text, x + 0x94, y + 0x5C, a, 0);
    FONT_SIZE(16.0f);
    FONT_COLOUR(5);
    func_002CA490(x + 0x40, y + 0xBB, 0, 0xC4, 8, 0x80, a);
    src = func_0035DEC0(officer, func_002F5730(officer));
    for (i = 0; i < 20; i++)
        weapon[i] = src[i];
    kind = weapon[0] == 0x78 ? 3 : weapon[0] & 3;
    if (kind < 3) {
        DRAW_TEXT(g_0042DC10[weapon[0]], x + 0x94, y + 0xC0, a);
    } else {
        func_002C5160(16.0f, g_0042DC10[weapon[0]], x + 0x94, y + 0xC0, 0x70, a, 0);
    }
    FONT_COLOUR(5);
    for (i = 5; i < 10; i++)
        func_001A85D0(func_002CA730(officer, stats[i - 5]), 0, 1.0f, x + 0x94, y + stat_y[i - 5],
                      0, i, 0, 0x60, a);
}

/* 0x00282A80, 0x78 bytes. Page 1's drawer. */
void func_00282A80(int player)
{
    short pos[4];
    u8 alpha;
    int r = func_001AE550(1.0f, &g_00772320[13], pos, &alpha, 0);

    func_002821F0(pos[0], pos[1], pos[2], pos[3], 0, player, r == 0);
    g_007725F4 = r != 0;
}

/* Page 8's title rectangles (0x004405C8, 0x004405D4) and per-kind ones (0x00440550). */
extern struct { int u, v, w; } g_004405C8, g_004405D4, g_00440550[];

/* Three sprites of texture 0x3EE5 (inlined twice): the title's two parts and the kind's. */
#define TITLE_SPRITES(rgba) do {                                        \
        for (i = 0; i < 3; i++)                                         \
            SPRITE_BEGIN(p[i], g_0068F0F0, 0x3EE5);                     \
        p[0][4] = (rgba);                                               \
        p[0][5] = GS_UV(g_004405D4.u, g_004405D4.v);                    \
        p[0][7] = GS_UV(g_004405D4.u + g_004405D4.w, g_004405D4.v + 0x10); \
        p[0][6] = GS_XYZ(x, y, 0xFFFE - z);                             \
        p[0][8] = GS_XYZ(x + (int)((float)g_004405D4.w * 1.2f), y + 0x13, 0xFFFE - z); \
        p[1][4] = (rgba);                                               \
        p[1][5] = GS_UV(g_004405C8.u, g_004405C8.v);                    \
        p[1][7] = GS_UV(g_004405C8.u + g_004405C8.w, g_004405C8.v + 0x10); \
        p[1][6] = GS_XYZ(x + 0x4D, y, 0xFFFE - z);                      \
        p[1][8] = GS_XYZ(x + 0x4D + (int)((float)g_004405C8.w * 1.2f), y + 0x13, 0xFFFE - z); \
        p[2][4] = (rgba);                                               \
        p[2][5] = GS_UV(g_00440550[kind].u, g_00440550[kind].v);        \
        p[2][7] = GS_UV(g_00440550[kind].u + g_00440550[kind].w, g_00440550[kind].v + 0x10); \
        p[2][6] = GS_XYZ(x + 0x5E, y + 2, 0xFFFE - z);                  \
        p[2][8] = GS_XYZ(x + 0x5E + (int)((float)g_00440550[kind].w * 1.2f), y + 0x15, 0xFFFE - z); \
        for (i = 0; i < 3; i++)                                         \
            func_00105900(p[i], arg);                                   \
    } while (0)

/* 0x00282B00, 0x774 bytes. Page 8's title; with a kind, drawn again additively at `alpha`. */
void func_00282B00(int x, int y, int z, int arg, u8 alpha, int kind)
{
    u64 *p[3];
    int i;

    TITLE_SPRITES(GREY(0x80));
    if (kind != 0) {
        SET_BLEND(BLEND_ADD, arg);
        TITLE_SPRITES(GREY(alpha));
        SET_BLEND(BLEND_NORMAL, arg);
    }
}

/* One sprite of texture 0x3F7C (u 0xE0-0xFF, v 0x30-0x3F) at (x, y), 32 x 16 (inlined). */
#define MARK_SPRITE(rgba) do {                                          \
        SPRITE_BEGIN(p, g_0068F0F8, 0x3F7C);                            \
        p[4] = GREY(alpha);                                             \
        p[5] = 0x03080E08;                                              \
        p[7] = 0x03F80FF8;                                              \
        p[6] = GS_XY(x, y);                                             \
        p[8] = GS_XY(x + 0x20, y + 0x10);                               \
        p[4] = (rgba);                                                  \
        func_00105900(p, arg);                                          \
    } while (0)

/* 0x00283280, 0x374 bytes. A mark, then the same added at `alpha`. */
void func_00283280(int x, int y, int w, int h, u8 alpha, int arg)
{
    u64 *p;

    MARK_SPRITE(GREY(0x80));
    SET_BLEND(BLEND_ADD, arg);
    MARK_SPRITE(GREY(alpha));
    SET_BLEND(BLEND_NORMAL, arg);
}

void func_0029C140(u32 officer, int cursor, int a);
int func_002F4900(u32 officer, int i);

/* An item's slot (texture `tex`, u 0x100-0x16F, v 0xC0-0xD3) lit when func_002F4900 is 1
 * (inlined). */
#define ITEM_SPRITE(tex, xy0, xy1, lit) do {                      \
        u32 g_;                                                         \
        SET_BLEND(BLEND_ADD, 0);                                        \
        SPRITE_BEGIN(p, g_0068F0F8, (tex));                             \
        p[4] = GREY(alpha);                                             \
        p[5] = 0x0C081008;                                              \
        p[7] = 0x0D3816F8;                                              \
        p[6] = (xy0);                                                   \
        p[8] = (xy1);                                                   \
        g_ = (lit) == 1 ? 0x80 : 0x4A;                                  \
        p[4] = GS_RGBAQ(g_, g_, g_, alpha);                             \
        func_00105900(p, 0);                                            \
        SET_BLEND(BLEND_NORMAL, 0);                                     \
    } while (0)

/* 0x00283600, 0x6C0 bytes. Page 8 (the items, 4 columns of 10): the list (func_0029C140), its
 * title, and the slots above func_003DCB30's level lit. */
void func_00283600(int player, int cursor)
{
    u32 officer = PLAYER_OFFICER(player);
    short pos[4];
    u8 alpha;
    int r, col, row;
    u64 *p;

    func_0029C140(officer, cursor, 1);
    g_007725F4 = g_00772D54;
    r = func_001AE550(1.0f, &g_00772320[30], pos, &alpha, 0);
    alpha = func_002C5AE0(g_007725C8);
    func_00282B00(pos[0], pos[1], 0, 0, alpha, func_0027FE00(player));
    g_007725F4 = g_00772D54 != 0 || r == 0;
    if (r == 0)
        return;
    if (func_0027FD90(player) != 0) {
        ITEM_SPRITE(0x3F67, GS_XYZ(20, 115, 0xFFFE), GS_XYZ(132, 138, 0xFFFE),
                    func_002F4900(officer, func_002F6A60(officer)));
        func_00283280(7, 0x66, 0x20, 0x10, alpha, 0);
    }
    for (col = 0; col < 4; col++) {
        int x = 0x14 + col * 0x78;

        for (row = 0; row < 10; row++) {
            int y = 0x90 + row * 0x14;
            int i = col * 10 + row;
            static const int texs[4] = { 0x3F65, 0x3F69, 0x3F68, 0x3F66 };

            if (func_0027FD20(player, i) == 0)
                continue;
            ITEM_SPRITE(texs[col], GS_XY(x, y), GS_XY(x + 0x70, y + 0x14),
                        func_002F47A0(officer, i) == 0 ? 0 : func_002F4900(officer, i));
            func_00283280(x - 0x0D, y + 3, 0x20, 0x10, alpha, 1);
        }
    }
}

extern u8 g_00440430[7], g_00440437[7], g_0044043E[7];   /* per level: a picture */
extern struct { int x, y; } g_00410DE0[][4];             /* per kind: four icons */
u8 func_0035DE00(u32 officer);
int func_003DCB00(int player);
void func_002D2A80(int a, int b, int c, int d, int e, int alpha);
void func_0028B730(int a, u32 level, u32 n, int player);
void func_0028B1D0(int a, u32 level, u32 n, int player);
void func_0028AD00(int a, u32 level, u32 n, int player);
void func_002D32B0(int a, int b, int alpha, int c, u32 officer, int kind);
void func_002D15C0(int x, int y, int a, int alpha, int b, int kind);

/* 0x00283CC0, 0x2AC bytes. Page 6 (the bodyguards): by the officer's kind (func_0035DE00), a
 * picture of the level (0-6) and the guards. */
void func_00283CC0(int player)
{
    u32 officer = PLAYER_OFFICER(player);
    u32 level, n;
    int kind, i;
    u8 type;

    level = (u8)func_002F41E0(officer) >> 1 < 7 ? (u8)func_002F41E0(officer) >> 1 : 6;
    type = func_0035DE00(officer);
    n = (func_003DCB00(player) / 2 & 0xFF) < 7 ? func_003DCB00(player) / 2 & 0xFF : 6;
    g_00772D54 = 0;
    if (type == 2) {
        func_002D2A80(0, 0, g_0044043E[level], 0, 3, 0x80);
        func_0028B730(0, level, n, player);
        kind = 3;
    } else if (type == 0) {
        func_002D2A80(0, 0, g_00440437[level], 0, 2, 0x80);
        func_0028B1D0(0, level, n, player);
        kind = 2;
    } else if (type == 1) {
        u8 picture = g_00440430[level];

        if (picture > 9)
            func_002D2A80(0, 0, picture, 0, 1, 0x80);
        else
            func_002D2A80(0, 0, picture, 0, 0, 0x80);
        kind = picture > 9;
        func_0028AD00(0, level, n, player);
    }
    for (i = 0; i < 4; i++)
        func_002D67E0(i + 0x1A, g_00410DE0[kind][i].x, g_00410DE0[kind][i].y, 0, 0, 0x80);
    func_002D32B0(0, 0, 0x80, 0, officer, kind);
    func_002D15C0(0xE0, 0x38, 0, 0x80, 0, type);
    g_007725F4 = 0;
}

void func_0029C690(u8 *map, u8 *frame, int a);
void func_0029CC10(int player, u8 *grid, u8 *page);

/* 0x00283F70, 0x2C bytes. Page 2's drawer (the map). */
void func_00283F70(u8 *map, u8 *frame, int a)
{
    func_0029C690(map, frame, a);
    g_007725F4 = g_00772D54;
}

/* 0x00283FA0, 0x2C bytes. Page 3's drawer (the units). */
void func_00283FA0(int player, u8 *grid, u8 *page)
{
    func_0029CC10(player, grid, page);
    g_007725F4 = g_00772D54;
}

extern float g_004110A0[4][4];            /* the marker's matrix (3 rows, then a position) */
void func_0028EED0(float *out);
void func_001911A0(float *out, u8 *pos);
void vu0_rotate(float out[4][4], float in[4][4], float angle);   /* stand-in for VU0 micro 0x70 */
void func_001FCAA0(int a, float matrix[4][4]);
void func_002C99F0(int x, int y, int a, int w, int h, int alpha);
void func_002CDB70(float time, int x, int y, int a);
void func_00147160(const u8 *text, char *out, int size, int a, int b);

/* Page 5's record `i` (0x110 bytes: +0 its time, +8 its position, +0x10 its text). */
#define RECORD(records, i) ((records) + (i) * 0x110)

/* 0x00283FD0, 0x974 bytes. Page 5, the battle records: the window frame, then (unless
 * `hidden`) a turning marker at the chosen record's position, three records (the newest first
 * once there are 16) and a scroll bar. */
void func_00283FD0(int x, int y, int z, int w, int h, int blend, int a, u8 **records, int one,
                   u8 cursor, int scroll, int hidden)
{
    float base[4][4];
    char text[400];
    u32 shown, n;
    int i;

    for (i = 0; i < 16; i++)
        base[i / 4][i % 4] = g_004110A0[i / 4][i % 4];
    SET_BLEND(BLEND_NORMAL, blend);
    func_002C7310(x, y, z, w, h, 0x80, blend);
    if (hidden != 0)
        return;
    n = *(u32 *)(*records + 0x1100);
    shown = n < 3 ? n & 0xFF : 3;
    if (shown != 0) {
        u32 k = (*(int *)(*records + 0x1104) - cursor + 0x0F) & 0x0F;
        u8 *rec = RECORD(*records, k);

        if (0.0f < *(float *)(rec + 8) || 0.0f < *(float *)(rec + 0x0C)) {
            float tmp[4];

            func_0028EED0(tmp);
            if (!FOLLOW_OFF(g_007725E8)) {
                float pos[4], m[4][4];

                func_001911A0(pos, RECORD(*records, k) + 8);
                base[3][0] = pos[0];
                base[3][1] = pos[1];
                base[3][2] = pos[2];
                base[3][3] = pos[3];
                vu0_rotate(m, base, g_007725E0);       /* (VU0) turned by the angle */
                for (i = 0; i < 4; i++)
                    m[3][i] += pos[i];
                func_001FCAA0(7, m);
                g_007725E0 += 0.05f;
            }
        }
        func_002C99F0(x + 8, y + 0x38, 0, 0x1A0, 0x34, 0x80);
    }
    s_0056CCA4.g_0056CCCC = 0x12;
    if (shown == 1) {
        func_002CDB70((float)*(int *)*records, x + 0x10, y + 0x3A, 0x0C);
        func_00147160(*records + 0x10, text, 400, 0, 0);
        DRAW_TEXT(text, x + 0x10, y + 0x48, blend);
    } else if (*(u32 *)(*records + 0x1100) < 0x10) {
        for (i = 0; i < 3; i++) {
            u32 total = *(u32 *)(*records + 0x1100);
            u32 j = total - ((cursor - 1) + i) - 1;

            if ((int)j >= 0 && j < total) {
                func_002CDB70((float)*(int *)RECORD(*records, j), x + 0x10, y + 8 + (2 - i) * 0x32, 0x0C);
                func_00147160(RECORD(*records, j) + 0x10, text, 400, 0, 0);
                DRAW_TEXT(text, x + 0x10, y + 0x16 + (2 - i) * 0x32, blend);
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            u32 j = (cursor - 1) + i;

            if ((int)j >= 0 && j < *(u32 *)(*records + 0x1100)) {
                j = (*(int *)(*records + 0x1104) - j + 0x0F) & 0x0F;
                func_002CDB70((float)*(int *)RECORD(*records, j), x + 0x10, y + 8 + (2 - i) * 0x32, 0x0C);
                func_00147160(RECORD(*records, j) + 0x10, text, 400, 0, 0);
                DRAW_TEXT(text, x + 0x10, y + 0x16 + (2 - i) * 0x32, blend);
            }
        }
    }
    s_0056CCA4.g_0056CCCC = 0x14;
    n = *(u32 *)(*records + 0x1100);
    if (n > 2) {
        if (n == 0)
            n = 1;
        func_001A3460(x + 0x1A8, y + 8, 0, 0x10, 0x97, 0x80, n, 1, n - 1 - cursor, blend);
    }
}

/* 0x00284950, 0xC0 bytes. Page 5's drawer. */
void func_00284950(u8 **records)
{
    u8 *state = (u8 *)records;
    short pos[4];
    u8 alpha;
    u8 cursor = state[4];
    u8 scroll = state[5] - cursor;
    int done = func_001AE550(1.0f, &g_00772320[27], pos, &alpha, 0) == 0;

    g_007725F4 = done != 0 || g_007725F4 != 0;
    func_00283FD0(pos[0], pos[1], 0, pos[2], pos[3], 0, 0, records, 1, cursor, scroll, done);
}

/* 0x00284A10, 0x6C bytes. Page 7's drawer: two lines. */
void func_00284A10(u8 cursor)
{
    u32 n = (g_007725E4 >> 1) + 1;

    if (n > 1)
        n = 2;
    if (g_007725E4 < 0x0E)
        g_007725E4++;
    func_00281090(g_00410EF0, n & 0xFF, cursor, 0);
}

u32 func_0036DD30(int a, u32 i);
int func_0036F290(int a, int b);
void func_0029A1C0(int x, int y, int a, int b, u32 *values, int n, u8 cursor, int *offered, int p8, int p9, int p10);
void func_0029A8F0(int x, int y, int a, int b, u32 value, int refused);

/* 0x00284A80, 0xDC bytes. Page 9's list: two values and whether each can be used. */
void func_00284A80(int x, int y, int a, int b, u8 cursor)
{
    u32 values[2];
    int offered[2];
    u32 i;

    for (i = 0; i < 2; i++) {
        values[i] = func_0036DD30(0, i);
        offered[i] = func_0036F290(0, i);
    }
    func_0029A1C0(x, y, a, b, values, 2, cursor, offered, 0, 0, 1);
}

/* 0x00284B60, 0xD4 bytes. Page 9's drawer: the list and the chosen value. */
void func_00284B60(int player, u8 *grid, u8 *page)
{
    short pos[4];
    u8 alpha;
    u32 value;

    g_00772D54 = 0;
    g_00772D54 = func_001AE550(1.0f, &g_00772320[33], pos, &alpha, 0) == 0 || g_00772D54 != 0;
    func_00284A80(pos[0], pos[1], 0, 0, page[0]);
    value = func_0036DD30(0, page[0]);
    if (value < 0x1F)
        func_0029A8F0(0x154, 0x68, 0, 0, value, func_0036F290(0, page[0]) == 0);
}

u8 func_00234B50(int i);
u32 func_003F6CA0(int a, u32 entry);
int func_003F77F0(int a, int b);
u8 func_003F7AE0(int a);
void func_0029ABA0(int x, int y, int a, int b, u32 *values, u8 n, u8 cursor, int *offered, int p8);
void func_0029B5A0(int x, int y, int a, int b, int c);
u32 func_003F6C10(int a);
int func_003F7090(u32 a, u32 b);
u8 func_003F6BE0(int a);
void func_0029B1C0(int x, int y, int a, int b, u32 value, int c, int d, int e);

/* 0x00284C40, 0xF8 bytes. Page 10's list: its entries' values and whether each can be used. */
void func_00284C40(int x, int y, int a, int b, u8 cursor)
{
    u32 values[6];
    int offered[6];
    u32 i;

    for (i = 0; i < 6; i++) {
        u8 entry = func_00234B50(i);

        if (entry > 5)
            break;
        values[i] = func_003F6CA0(0, entry);
        offered[i] = func_003F77F0(0, entry);
    }
    func_0029ABA0(x, y, a, b, values, func_003F7AE0(0), cursor, offered, 0);
}

/* 0x00284D40, 0x1AC bytes. Page 10's drawer: the list, then the chosen entry against the
 * current one (func_003F7090: which is better). */
void func_00284D40(int player, u8 *grid, u8 *page)
{
    short pos[4];
    u8 alpha;
    u32 chosen, current;
    int diff;
    u8 entry, now;

    g_00772D54 = 0;
    g_00772D54 = func_001AE550(1.0f, &g_007725F8[4], pos, &alpha, 0) == 0 || g_00772D54 != 0;
    func_00284C40(pos[0], pos[1], 0, 0, page[0]);
    func_001AE550(1.0f, &g_007725F8[5], pos, &alpha, 0);
    func_0029B5A0(pos[0], pos[1], 0, 0, 0);
    chosen = func_003F6CA0(0, func_00234B50(page[0]));
    current = func_003F6C10(1);
    diff = func_003F7090(chosen, current);
    entry = page[page[0] + 2];
    now = func_003F6BE0(0);
    func_0029B1C0(pos[0] + 0x0C, pos[1] + 0x30, 0, 0, chosen, entry != now && diff > 0, 1, diff > 0);
    func_0029B1C0(pos[0] + 0xAC, pos[1] + 0x30, 0, 0, current, entry != now && diff < 0, 1, diff < 0);
}

/* 0x00284EF0, 0x8 bytes, matching. Page 11's drawer: empty. */
void func_00284EF0(void)
{
}

void func_002989E0(int player, int x, int y, int a);
int func_003DD680(int player);
void func_002966C0(int a, int b, int x, int y, int c, int player, int d);

/* 0x00284F00, 0xF4 bytes. Page 12's drawer: four lines and two windows. */
void func_00284F00(int player, u8 cursor)
{
    u32 n = (g_007725E4 >> 1) + 1;
    short pos[4];
    u8 alpha;

    if (n > 3)
        n = 4;
    if (g_007725E4 < 0x12)
        g_007725E4++;
    func_00281090(g_00410F10, n & 0xFF, cursor, 0);
    func_001AE550(1.0f, &g_00772320[13], pos, &alpha, 0);
    func_002989E0(player, pos[0], pos[1], 0);
    func_001AE550(1.0f, &g_00772320[14], pos, &alpha, 0);
    func_002966C0(0, 0, pos[0], pos[1], 0, player, func_003DD680(player) + 0x10);
}

/* 0x00285000, 0x8 bytes, matching. Page 13's drawer: empty. */
void func_00285000(void)
{
}

/* 0x00285010, 0x8 bytes, matching. Page 14's drawer: empty. */
void func_00285010(void)
{
}

extern char g_007B4E60[], g_007B5062[];   /* text buffers */
extern const char g_004405F0[];
int func_003F5650(void);
int func_003F5560(void);
u32 func_003F55E0(void);
int func_003F55F0(void);
int func_003F5600(void);
void func_003DD730(char *out, u8 **group);
void func_003E41A0(int x, int y, int a, int b, int c);
const char *func_00372CF0(int id);
const char *func_0030CB80(int entry);
void func_003E3270(int x, int y, int a, int alpha, int b);
extern u8 g_006A1D58[][0x68];             /* the soldier groups */

/* 0x00285020, 0x564 bytes. Page 15 (a mission?): the window, the group's name in messages 0-3,
 * its state (messages 4-11 by func_003F55E0) and a timer mark. */
void func_00285020(int x, int y, int w, int h, u8 alpha, int a, int hidden)
{
    char name[32];
    u32 state;
    int limit, entry;
    u8 **group;

    if (func_003F5650() == 0)
        return;
    func_002C7310(x, y, 0, w, h, alpha, a);
    if (hidden != 0)
        return;
    group = (u8 **)g_006A1D58[func_003F5560()];
    state = func_003F55E0();
    limit = func_003F55F0();
    entry = func_003F5600();
    func_003DD730(name, group);
    func_003E41A0(x + 0x10, y + 0x48, 0, a, 0);
    func_003E41A0(x + 0x10, y + 0x88, 0, a, 1);
    func_003E41A0(x + 0x10, y + 0xAC, 0, a, 2);
    if ((*group)[0x79] == 0)
        func_001204B0(g_007B4E60, func_00372CF0(2), name, name);
    else
        func_001204B0(g_007B4E60, func_00372CF0(0), name, name);
    func_00147160((u8 *)g_007B4E60, g_007B5062, 400, 0, 0);
    DRAW_TEXT(g_007B5062, x + 0x18, y + 8, a);
    if ((*group)[0x79] == 0)
        func_001204B0(g_007B4E60, func_00372CF0(3), name);
    else
        func_001204B0(g_007B4E60, func_00372CF0(1), name);
    func_00147160((u8 *)g_007B4E60, g_007B5062, 400, 0, 0);
    DRAW_TEXT(g_007B5062, x + 0x18, y + 0xC0, a);
    switch (state) {
    case 0:
        func_001204B0(g_007B4E60, func_00372CF0(4), func_0030CB80(entry));
        break;
    case 1:
        func_001204B0(g_007B4E60, func_00372CF0(5), func_0030CB80(entry));
        break;
    case 2:
        func_001204B0(g_007B4E60, func_00372CF0(6));
        break;
    case 3:
        func_001204B0(g_007B4E60, func_00372CF0(7), func_0030CB80(entry));
        break;
    case 4:
        func_001204B0(g_007B4E60, func_00372CF0(8), func_0030CB80(entry));
        break;
    case 5:
        func_001204B0(g_007B4E60, func_00372CF0(9), name);
        break;
    case 6:
        func_001204B0(g_007B4E60, func_00372CF0(10), name);
        break;
    case 7:
        func_001204B0(g_007B4E60, func_00372CF0(11));
        break;
    default:
        func_001204B0(g_007B4E60, g_004405F0);
        break;
    }
    func_00147160((u8 *)g_007B4E60, g_007B5062, 400, 0, 0);
    DRAW_TEXT(g_007B5062, x + 0x18, y + 0x5C, a);
    if (limit * 3000 - g_00669F9C >= 0)
        func_003E3270(x + 0x18, y + 0x9C, 0, 0x80, a);
}

/* 0x00285590, 0x80 bytes. Page 15's drawer. */
void func_00285590(void)
{
    short pos[4];
    u8 alpha;

    int done;

    g_00772D54 = 0;
    done = func_001AE550(1.0f, &g_007725F8[3], pos, &alpha, 0) == 0;
    g_00772D54 = done != 0 || g_00772D54 != 0;
    func_00285020(pos[0], pos[1], pos[2], pos[3], alpha, 0, done);
}

/* 0x00285610, 0x6C bytes. Page 16's drawer: two lines. */
void func_00285610(u8 cursor)
{
    u32 n = (g_007725E4 >> 1) + 1;

    if (n > 1)
        n = 2;
    if (g_007725E4 < 0x0E)
        g_007725E4++;
    func_00281090(g_00410EF0, n & 0xFF, cursor, 0);
}

void func_002DB9A0(void);

/* 0x00285680, 0x1C bytes, matching. Page 17's drawer. */
void func_00285680(void)
{
    func_002DB9A0();
}

/* 0x002856A0, 0x2C bytes, matching. Page 18's drawer: page 16's lines with line 1 chosen. */
void func_002856A0(void)
{
    func_00281090(g_00410EF0, 2, 1, 0);
}
