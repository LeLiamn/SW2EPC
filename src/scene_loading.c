/*
 * scene_loading.c - scene 0x0F, the loading screen (original source file SceneLoading.c: the
 * screen's pictures are loaded with that file name).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly; the floating-point and VU0 instructions decoded by hand). Unknown functions and
 * globals keep neutral names (func_/g_ + address); comments with a question mark are hypotheses.
 *
 * The loading screen (0x007A2640) draws a black screen and up to six animated layers. Each layer
 * moves, scales and fades between two values over a time window (in frames, advanced by 1.2 a
 * frame), can rotate and can loop. Its pictures come from one LINKDATA pack per stage (entry
 * 0x5E + stage). The scene itself only waits for the loading and fades out.
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

/* The message boxes' object (0x0068F3E0, see scene_shop.c), up to the bytes used here. */
extern struct {
    u8 unknown_0[0x457C];
    u8 g_0069395C;
    u8 unknown_457D;
    u8 g_0069395E;           /* message box 1 open when neither 0 nor 0xFF */
} s_0068F3E0;
#define g_0069395C (s_0068F3E0.g_0069395C)
#define g_0069395E (s_0068F3E0.g_0069395E)

/* The game state (0x00669D60), the flags word (bit 4: demo, see scene_demo.c). */
extern struct {
    u8 unknown_0[0x200];
    u32 g_00669F60;
} g_00669D60;
#define g_00669F60 (g_00669D60.g_00669F60)

/* (scratchpad) screen scale divisor? */
#define g_70000154 (*(int *)0x70000154)
extern u8 g_0045D678;                     /* 1 once the fade-out started */
extern const char g_00445AE8[];           /* "SceneLoading.c" */

/* A layer of the loading screen (0x34 bytes). Every value goes from `from` to `to` while `time`
 * goes from `start` to `end`. */
typedef struct {
    u32 flags;               /* +0x00: see LAYER_* */
    float alpha_from, alpha_to;          /* +0x04 (0-128, more is clamped) */
    float x_from, x_to;                  /* +0x0C */
    float y_from, y_to;                  /* +0x14 */
    float scale_from, scale_to;          /* +0x1C */
    float time;                          /* +0x24 */
    float start, end;                    /* +0x28 */
    u8 *texture;                         /* +0x30: a TIM2 picture */
} LoadLayer;
#define LAYER_LOOP      0x01             /* time back to 0 after `end` */
#define LAYER_ROTATE    0x02             /* turns by -0.06 rad per frame of time */
#define LAYER_W256      0x04             /* 256 wide, drawn twice (mirrored copy on the right) */
#define LAYER_W512      0x08             /* 512 wide */
#define LAYER_FADE_OUT  0x20             /* after half the window, the fade goes back */
#define LAYER_ADDITIVE  0x40             /* drawn with another blending (ALPHA 0x43) */
#define LAYER_EASE      0x80             /* progress = square root of the time ratio */

typedef struct {
    float speed;             /* +0x0: time added each frame (1.2) */
    LoadLayer *layers;       /* +0x4: six layers */
    int unknown_8;
    u8 *data;                /* +0xC: the stage's LINKDATA pack (entry 0x5E + stage) */
} LoadingScreen;
extern LoadingScreen g_007A2640;

/* Stand-ins for the two VU0 micro subroutines the game calls with vcallms (inline assembly in the
 * original): 0x10 gives the cosine and 0x00 the sine of the angle passed in a VU0 register. */
float vu0_cos(float angle);
float vu0_sin(float angle);

u8 *func_00106F10(u8 *texture);           /* the TIM2 picture header (+0x14 width, +0x16 height) */
u8 *func_001050F0(void);
void func_00105230(u8 *packet, int a);
u8 *func_00104E70(u8 *texture, int a, int b, int c);
u8 *func_00105B40(u8 *packet, int a);
void func_00105BE0(u8 *packet, int a);
u8 *func_00105410(void);
void func_001054B0(u8 *packet, int a);
void *func_00102D30(int size);
void func_00102EC0(void *data);
void func_00118850(void *p, int size);
void func_00103000(int value);
u8 *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
void func_00101470(int value);
void func_001037F0(int value);
int func_00102960(int value);
void func_001B8F60(int a, int b, int c);

#define TEX_W(h) (*(unsigned short *)((h) + 0x14))
#define TEX_H(h) (*(unsigned short *)((h) + 0x16))

/* VU0 vftoi4: to 12.4 fixed point. */
#define FTOI4(v) ((int)((v) * 16.0f))

/* 0x002F0810, 0x38 bytes, matching. The smallest power of two (2 or more, up to 0x20000) not below
 * `value`. */
u32 func_002F0810(u32 value)
{
    u32 p = 1;

    do {
        p <<= 1;
        if (p >= (value & 0xFFFF))
            break;
    } while (p < 0x1FFFE);
    return p;
}

/* 0x002F0850, 0x9C bytes. Turns the point (*x, *y) by `angle` around (cx, cy). */
void func_002F0850(float cx, float cy, float angle, float *x, float *y)
{
    float dx = *x - cx;
    float dy = *y - cy;

    *x = dx * vu0_cos(angle) + dy * vu0_sin(angle);
    *y = (dy * vu0_cos(angle) + 0.0f) - dx * vu0_sin(angle);
    *x = *x + cx;
    *y = *y + cy;
}

/* One corner of a layer's sprite: turned, then to GS coordinates (12.4 fixed point, the 480-line
 * picture scaled to 448 lines, offset 0x7000 / 0x8000). */
static u64 corner_xyz(float cx, float cy, float angle, float x, float y)
{
    int ix, iy;

    func_002F0850(cx, cy, angle, &x, &y);
    ix = FTOI4(x);
    iy = FTOI4(y);
    iy = iy * 0x280 / 0x1E0 * 0x1C0 / 0x200;
    return (u64)(ix + 0x7000) | (u64)((iy - 0xE00) / g_70000154 + 0x8000) << 16 |
           0xFFFE00000000ULL;
}

/* 0x002F08F0, 0x818 bytes. Fills the sprite packet of `layer` at its current time (four corners:
 * colour, texture coordinates and position); `mirrored` draws the right-hand copy of a 256-wide
 * layer, with the texture flipped. Returns 0 before the layer's window. */
int func_002F08F0(u8 *packet, LoadLayer *layer, int mirrored)
{
    u8 *tex = func_00106F10(layer->texture);
    float s0 = 1.0f / (float)(u32)TEX_W(tex);
    float t0 = 1.0f / (float)(u32)TEX_H(tex);
    float s1 = (float)(int)(TEX_W(tex) - 1) / (float)func_002F0810(TEX_W(tex));
    float t1 = (float)(int)(TEX_H(tex) - 1) / (float)func_002F0810(TEX_H(tex));
    float ratio = (layer->time - layer->start) / (layer->end - layer->start);
    float t = ratio, scale, x, y, w, h, angle = 0.0f;
    int alpha;
    u64 rgbaq;

    if (t >= 1.0f)
        t = 1.0f;
    if (t < 0.0f)
        return 0;
    if (layer->flags & LAYER_EASE) {
        float r = __builtin_sqrtf(ratio);         /* (VU0 vsqrt) */
        t = r < 1.0f ? r : 1.0f;
    }
    scale = t * (layer->scale_to - layer->scale_from) + layer->scale_from + 0.0f;
    alpha = (int)(t * (layer->alpha_to - layer->alpha_from) + layer->alpha_from + 0.0f);
    if (alpha > 0x80)
        alpha = 0x80;
    if ((layer->flags & LAYER_FADE_OUT) && t > 0.5f)
        alpha = (int)((1.0f - t) * (layer->alpha_to - layer->alpha_from) + layer->alpha_from + 0.0f);
    x = t * (layer->x_to - layer->x_from) + layer->x_from + 0.0f;
    w = (float)(int)TEX_W(tex) * scale;
    h = (float)(int)TEX_H(tex) * scale;
    y = t * (layer->y_to - layer->y_from) + layer->y_from + 0.0f;
    if (layer->flags & LAYER_W512) {
        w = 512.0f;
    } else if (layer->flags & LAYER_W256) {
        w = 256.0f;
    } else {                                       /* scaled around the picture's centre */
        x = (x + 0.0f) - (w - (float)(int)TEX_W(tex)) * 0.5f;
        y = (y + 0.0f) - (h - (float)(int)TEX_H(tex)) * 0.5f;
    }
    if (mirrored)
        x += w;
    if (layer->flags & LAYER_ROTATE) {
        angle = layer->time * -0.06f;
        if (angle < -3.1415927f)
            angle += 6.2831855f;
    }
    {
        float cx = w * 0.5f + x + 0.0f;
        float cy = h * 0.5f + y + 0.0f;

        *(u64 *)(packet + 0x30) = corner_xyz(cx, cy, angle, x, y);
        *(u64 *)(packet + 0x48) = corner_xyz(cx, cy, angle, x + w, y);
        *(u64 *)(packet + 0x60) = corner_xyz(cx, cy, angle, x, y + h);
        *(u64 *)(packet + 0x78) = corner_xyz(cx, cy, angle, x + w, y + h);
    }
#define ST(s, t) ((u64)*(u32 *)&(s) | (u64)*(u32 *)&(t) << 32)
    *(u64 *)(packet + 0x28) = ST(s0, t0);
    *(u64 *)(packet + 0x40) = ST(s1, t0);
    *(u64 *)(packet + 0x58) = ST(s0, t1);
    *(u64 *)(packet + 0x70) = ST(s1, t1);
    if (mirrored) {
        *(u64 *)(packet + 0x40) = ST(s0, t0);
        *(u64 *)(packet + 0x28) = ST(s1, t0);
        *(u64 *)(packet + 0x70) = ST(s0, t1);
        *(u64 *)(packet + 0x58) = ST(s1, t1);
    }
#undef ST
    rgbaq = (u64)alpha << 24 | 0x3F80000000808080ULL;
    *(u64 *)(packet + 0x20) = rgbaq;
    *(u64 *)(packet + 0x38) = rgbaq;
    *(u64 *)(packet + 0x50) = rgbaq;
    *(u64 *)(packet + 0x68) = rgbaq;
    return 1;
}

/* 0x002F1110, 0x248 bytes. Sets up the six layers: pictures 0-4 of the pack, then per layer its
 * place, scale, fade and time window (defaults: alpha to 128, scale 1, window 0-60 frames). */
void func_002F1110(LoadingScreen *screen)
{
    LoadLayer *wide = 0;
    u8 *tex;
    int i;

    for (i = 0; i < 6; i++) {
        LoadLayer *l = &screen->layers[i];

        l->alpha_to = 128.0f;
        l->scale_from = 1.0f;
        l->scale_to = 1.0f;
        l->end = 60.0f;
        if (i < 5) {
            l->texture = screen->data + *(int *)(screen->data + 4 + i * 4);
            func_00106F10(l->texture);
        }
        switch (i) {
        case 0:
            l->flags = LAYER_W512;
            l->x_from = 0.0f;
            l->y_from = 316.0f;
            l->x_to = l->x_from;
            l->y_to = l->y_from;
            l->end = 120.0f;
            l->start = 60.0f;
            break;
        case 1:
            l->flags = LAYER_ADDITIVE | LAYER_FADE_OUT | LAYER_W256;   /* 100 */
            l->x_from = 0.0f;
            l->y_from = 328.0f;
            l->x_to = l->x_from;
            l->y_to = l->y_from;
            l->alpha_to = 255.0f;
            l->end = 120.0f;
            l->start = 60.0f;
            break;
        case 2:                                     /* x set after the loop */
            l->flags = LAYER_ADDITIVE | LAYER_FADE_OUT | LAYER_ROTATE | LAYER_LOOP;   /* 99 */
            l->y_from = 284.0f;
            l->y_to = 284.0f;
            l->alpha_to = 255.0f;
            l->end = 105.0f;
            l->start = 60.0f;
            break;
        case 3:
            l->x_from = 128.0f;
            l->y_from = 102.0f;
            l->x_to = l->x_from;
            l->y_to = l->y_from;
            l->scale_from = 2.3f;
            l->scale_to = 2.0f;
            l->end = 50.0f;
            break;
        case 4:
            l->x_from = 258.0f;
            l->y_from = 229.0f;
            l->x_to = l->x_from;
            l->y_to = l->y_from;
            l->scale_from = 1.2f;
            l->end = 90.0f;
            l->start = 60.0f;
            wide = l;
            break;
        }
    }
    tex = func_00106F10(wide->texture);             /* layer 2 runs along layer 4's picture */
    screen->layers[2].x_from = wide->x_to - 64.0f;
    screen->layers[2].x_to = wide->x_to + (float)(int)(TEX_W(tex) - 0x20);
}

/* 0x002F1360, 0x60 bytes, matching. Advances the six layers' time (looping layers restart after `end`). */
void func_002F1360(LoadingScreen *screen)
{
    int i;

    for (i = 0; i < 6; i++) {
        LoadLayer *l = &screen->layers[i];

        l->time = l->time + screen->speed;
        if ((l->flags & LAYER_LOOP) && l->end < l->time)
            l->time = 0.0f;
    }
}

/* 0x002F13C0, 0x138 bytes, matching. Draws one layer (twice for a 256-wide one), with the other blending
 * set around it for LAYER_ADDITIVE layers. */
void func_002F13C0(LoadLayer *layer)
{
    u8 *packet;

    if (layer->flags & LAYER_ADDITIVE) {
        packet = func_001050F0();
        *(u64 *)(packet + 0x10) = 0x48;
        *(u64 *)(packet + 0x18) = 0x43;
        func_00105230(packet, 1);
    }
    packet = func_00105B40(func_00104E70(layer->texture, 0x1320, 0x3FFC, 1), 1);
    if (func_002F08F0(packet, layer, 0) != 0)
        func_00105BE0(packet, 1);
    if (layer->flags & LAYER_W256) {
        packet = func_00105B40(func_00104E70(layer->texture, 0x1320, 0x3FFC, 1), 1);
        if (func_002F08F0(packet, layer, 1) != 0)
            func_00105BE0(packet, 1);
    }
    if (layer->flags & LAYER_ADDITIVE) {
        packet = func_001050F0();
        *(u64 *)(packet + 0x10) = 0x8000000044ULL;
        *(u64 *)(packet + 0x18) = 0x43;
        func_00105230(packet, 1);
    }
}

/* 0x002F1500, 0x4C bytes, matching. Draws layers 0, 4, 1 and 2 (3 and 5 are not drawn). */
void func_002F1500(LoadingScreen *screen)
{
    func_002F13C0(&screen->layers[0]);
    func_002F13C0(&screen->layers[4]);
    func_002F13C0(&screen->layers[1]);
    func_002F13C0(&screen->layers[2]);
}

/* 0x002F1550, 0x44 bytes, matching. Allocates and clears the six layers. */
void func_002F1550(LoadingScreen *screen)
{
    screen->layers = func_00102D30(0x138);
    func_00118850(screen->layers, 0x138);
    screen->speed = 1.2f;
}

/* 0x002F15A0, 0x34 bytes, matching. Frees the layers and clears the object. */
void func_002F15A0(LoadingScreen *screen)
{
    func_00102EC0(screen->layers);
    func_00118850(screen, 0x10);
}

/* 0x002F15E0, 0x78 bytes, matching. Opens the loading screen for `stage` (its pictures: LINKDATA entry
 * 0x5E + stage); the first argument is unused. Called when a battle starts (scene_demo.c). */
void func_002F15E0(u32 unused, int stage)
{
    func_00103000(0);
    func_002F1550(&g_007A2640);
    g_007A2640.data = func_001026D0(1, stage + 0x5E, 0, 1, 0, 0, g_00445AE8, 0x161);
    func_002F1110(&g_007A2640);
    func_00103000(1);
}

/* 0x002F1660, 0x50 bytes, matching. Closes the loading screen if it is open. */
void func_002F1660(void)
{
    LoadingScreen *screen = &g_007A2640;

    if (screen->layers != 0) {
        func_00103000(0);
        func_00102EC0(screen->data);
        func_002F15A0(screen);
        func_00103000(1);
    }
}

/* 0x002F16B0, 0x20 bytes, matching. */
void func_002F16B0(void)
{
    func_002F1360(&g_007A2640);
}

/* 0x002F16D0, 0xC0 bytes, matching. Draws the loading screen: a black full-screen rectangle, then the
 * layers. */
void func_002F16D0(void)
{
    u8 *packet = func_00105410();

    *(u64 *)(packet + 0x20) = (u64)(-0xE00 / g_70000154 + 0x8000) << 16 | 0xFFFE00007000ULL;
    *(u64 *)(packet + 0x28) = (u64)(0xE00 / g_70000154 + 0x8000) << 16 | 0xFFFE00009000ULL;
    *(u64 *)(packet + 0x18) = 0x3F80000080000000ULL;
    func_001054B0(packet, 1);
    func_002F1500(&g_007A2640);
}

/* ---- Scene 0x0F -------------------------------------------------------------------------------- */

/* 0x002F1790, 0x3C bytes, matching. Scene 0x0F enter. */
void func_002F1790(void)
{
    func_00101470(1);
    func_001037F0(0);
    g_0069395E = 0;
    g_0045D678 = 0;
    g_0069395C = 1;
}

/* 0x002F17D0, 0x24 bytes, matching. Scene 0x0F leave: closes the loading screen. */
void func_002F17D0(void)
{
    g_0069395E = 0xFF;
    func_002F1660();
}

/* 0x002F1800, 0x11C bytes. Scene 0x0F update: animates the layers; once the loading is done
 * (func_00102960) starts the fade-out, and when it is over leaves (outside a demo, also calls
 * func_001037F0(1)). */
int func_002F1800(void)
{
    func_002F16B0();
    if (g_0045D678 != 0) {
        int open;

        if (g_0069395E == 0 || g_0069395E == 0xFF)
            open = 0;
        else
            open = 1;
        if (!open) {
            int current = g_0045D898;

            if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
                g_0045D898 = g_0045D8A0;
                g_0045D89C = 0x18;
            } else {
                g_0045D898 = g_0045D89C;
                g_0045D89C = g_0045D8A0;
            }
            g_0045D894 = current;
            if ((g_00669F60 & 0x10) == 0)
                func_001037F0(1);
            return 1;
        }
    }
    if (func_00102960(0) != 0) {
        func_001B8F60(0, 6, 0x20);
        g_0045D678 = 1;
    }
    return 1;
}

/* 0x002F1920, 0x8 bytes, matching. Scene 0x0F step: empty. */
void func_002F1920(void)
{
}

/* 0x002F1930, 0x1C bytes, matching. Scene 0x0F draw. */
void func_002F1930(void)
{
    func_002F16D0();
}
