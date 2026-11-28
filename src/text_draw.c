/*
 * text_draw.c - drawing text (original source file unknown, probably the start of font.c, whose
 * name the code right after it passes; 0x00144080-0x00147574).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A font (0x004053C0) is a texture of fixed-size cells (one or two textures: the second one holds
 * the cells after the first page), with an optional table of cell positions and of character
 * widths. Each character is one textured sprite (gs_packet.c), drawn in one of six styles:
 * a quad with a colour per corner, flat, with a shadow, outlined (two kinds), or by a callback.
 * The text state (0x0056CCA0) holds the style, the colours (indices into the palette at
 * 0x004248F0, alphas apart), the scales (20.0 = the font's size), the line height and the
 * depth.
 *
 * In a string, "[NN" sets the colour NN, "]" goes back to the state's colours, TAB moves to the
 * next tab stop, LF starts a new line, 0xF0 + a letter draws a button icon, and the lead byte of a
 * two-byte character is shown as '@'.
 *
 * Screen coordinates: x is in pixels from the left (x * 16 + 0x7000), y in 480-line units scaled
 * to the 448 lines of the display (y * 640 / 480 * 448 / 512) and halved for a field.
 */

#define SW2E_FILE_TEXT_DRAW_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

#define g_70000154 (*(int *)0x70000154)          /* 1 or 2 (field mode?) */

/* A font. */
typedef struct {
    u64 tex0[2];             /* the second is -1 when there is one texture */
    u16 *cells;              /* +0x10 each cell's position (u, v), or 0: a grid from ' ' */
    u32 count;               /* +0x14 characters in the grid */
    u8 *widths;              /* +0x18 each character's width, or 0 */
    u32 pad;
    u16 cell_w;              /* +0x20 */
    u16 cell_h;
    u16 draw_w;              /* +0x24 the size drawn at scale 20 */
    u16 draw_h;
    u16 columns;             /* +0x28 */
    u16 rows;                /* +0x2A per texture */
} Font;

/* A character to draw. */
typedef struct {
    int kind;                /* (icons: unused) */
    Font *font;              /* +4 */
    u32 code;                /* +8 the cell (bit 31: from the font's table), or the icon */
    int x, y;                /* +0xC */
    int w, h;                /* +0x14 */
    int layer;               /* +0x1C */
    u8 colour[4][4];         /* +0x20 RGBA for each corner */
} Glyph;

/* The text state (0x0056CCA0). */
extern struct {
    void (*custom)(Glyph *g);    /* style 5 */
    int colour[4];           /* 0x0056CCA4 palette indices, one per corner */
    int outline;             /* 0x0056CCB4 */
    int style;               /* 0x0056CCB8 0-5 */
    int depth;               /* 0x0056CCBC */
    float scale_x;           /* 0x0056CCC0 20.0 = the font's size */
    float scale_y;
    u8 alpha[4];             /* 0x0056CCC8 */
    u8 line_h;               /* 0x0056CCCC */
    u8 pad[2];
    u8 flags;                /* 0x0056CCCF 1 fixed width, 2 12-pixel steps */
} g_0056CCA0;

extern Font g_004053C0;                  /* the font */
extern u8 g_004248F0[][4];               /* the palette */
extern void (*g_00424950[6])(Glyph *g);  /* the styles */
extern int g_00405420[8][2];             /* the outline's eight offsets */

int func_00146D80(const u8 *text, int *w, int *h);

/* A y coordinate scaled to the display's lines. */
#define SCREEN_Y(y) ((y) * 0x280 / 0x1E0 * 0x1C0 / 512)

/* A vertex position (x in pixels, y in display lines). */
#define XYZ(x, sy)                                                              \
    ((u64)(0xFFFE - g_0056CCA0.depth) << 32 | (u64)((x) * 16 + 0x7000)          \
     | (u64)(((sy) * 16 - 0xE00) / g_70000154 + 0x8000) << 16)

/* A texture position (texel centres). */
#define UV(u, v) ((u64)(int)((u) << 4 | 8) | (u64)(int)((v) << 4 | 8) << 16)

/* An RGBA colour with Q = 1.0. */
#define RGBAQ(c) ((u64)(c) | 0x3F80000000000000)

/* The texture holding a glyph's cell. */
static inline u64 glyph_tex(const Glyph *g)
{
    const Font *f = g->font;

    if ((g->code & 0x80000000) == 0) {
        if (f->tex0[1] == (u64)-1)
            return f->tex0[0];
        if (g->code < (u32)(f->columns * f->rows))
            return f->tex0[0];
    } else if ((g->code & 0x7FFFFFFF) < 0x191) {
        return f->tex0[0];
    }
    return f->tex0[1];
}

/* The position of a glyph's cell in its texture. */
static inline void glyph_cell(const Glyph *g, u32 *u, u32 *v)
{
    const Font *f = g->font;
    int code = g->code;

    if ((g->code & 0x80000000) == 0) {
        if (f->tex0[1] != (u64)-1)
            code %= f->columns * f->rows;
        *u = f->cell_w * (code % f->columns);
        *v = f->cell_h * (code / f->columns);
    } else {
        u16 *c = (u16 *)((u8 *)f->cells + code * 4);

        *u = c[0];
        *v = c[1];
    }
}

/* Fills a textured sprite's two corners: (x, y) and (x + w, y + h) with the glyph's cell. */
static inline void glyph_sprite(u8 *p, const Glyph *g, u32 u, u32 v, int x, int y)
{
    *(u64 *)(p + 0x28) = UV(u, v);
    *(u64 *)(p + 0x38) = UV(g->font->cell_w + u, g->font->cell_h - 1 + v);
    *(u64 *)(p + 0x30) = XYZ(x, SCREEN_Y(y));
    *(u64 *)(p + 0x40) = XYZ(g->w + x, SCREEN_Y(g->h) + SCREEN_Y(y));
}

/* 0x00144080, 0x4C0 bytes. Style 0: a quad with a colour per corner. Only two of its four
 * positions are written (as in the original). */
void func_00144080(Glyph *g)
{
    u8 *p = func_00105B40(glyph_tex(g), 0);
    u32 u, v;
    u64 a, b;

    *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[0]);
    *(u64 *)(p + 0x38) = RGBAQ(*(u32 *)g->colour[1]);
    *(u64 *)(p + 0x50) = RGBAQ(*(u32 *)g->colour[2]);
    *(u64 *)(p + 0x68) = RGBAQ(*(u32 *)g->colour[3]);
    *(u64 *)(p + 0x30) = XYZ(g->x, SCREEN_Y(g->y + 1));
    *(u64 *)(p + 0x78) = XYZ(g->w + g->x, SCREEN_Y(g->h) + SCREEN_Y(g->y + 1));
    glyph_cell(g, &u, &v);
    a = (u64)(u << 4) | 8;
    b = ((u64)(v << 4) | 8) << 16;
    *(u64 *)(p + 0x28) = a | b;
    *(u64 *)(p + 0x40) = b | (u64)((g->font->cell_w + u) * 16) | 8;
    *(u64 *)(p + 0x58) = a | ((u64)((g->font->cell_h - 1 + v) * 16) | 8) << 16;
    *(u64 *)(p + 0x70) = (u64)((g->font->cell_w + u) * 16) | 8
                         | ((u64)((g->font->cell_h - 1 + v) * 16) | 8) << 16;
    func_00105BE0(p, g->layer);
}

/* 0x00144540, 0x3E0 bytes. Style 1: a flat sprite of the first corner's colour. */
void func_00144540(Glyph *g)
{
    u32 u, v;
    u8 *p;

    glyph_cell(g, &u, &v);
    p = func_00105860(glyph_tex(g), 0);
    *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[0]);
    glyph_sprite(p, g, u, v, g->x, g->y + 1);
    func_00105900(p, g->layer);
}

/* 0x00144920, 0x400 bytes. Style 2: a black shadow (2 pixels right, 2 lines down, in the layer
 * above), then the character in the first corner's colour. */
void func_00144920(Glyph *g)
{
    u64 tex = glyph_tex(g);
    u32 u, v;
    int i, d;

    glyph_cell(g, &u, &v);
    for (i = 0, d = 0; i < 2; i++, d += 2) {
        u8 *p = func_00105860(tex, 0);

        *(u64 *)(p + 0x20) = (u64)g->colour[0][3] << 24 | (u64)(g->colour[0][2] * i) << 16
                             | (u64)(g->colour[0][0] * i) | (u64)(g->colour[0][1] * i) << 8
                             | 0x3F80000000000000;
        glyph_sprite(p, g, u, v, g->x + 2 - d, g->y + 3 - d);
        func_00105900(p, i == 0 ? g->layer + 1 : g->layer);
    }
}

/* 0x00144D20, 0xB78 bytes. Style 3: an outline of the second corner's colour (at half alpha:
 * four copies 2 pixels around, two stretched ones), then the character. */
void func_00144D20(Glyph *g)
{
    u64 tex = glyph_tex(g);
    u32 u, v;
    int i;
    u8 *p;

    glyph_cell(g, &u, &v);
    for (i = 0; i < 4; i++) {
        p = func_00105860(tex, 0);
        *(u64 *)(p + 0x20) = (u64)(*(u32 *)g->colour[1] & 0xFFFFFF) | 0x3F80000040000000;
        glyph_sprite(p, g, u, v, g->x - 2 + i % 2 * 4, g->y - 1 + i / 2 * 4);
        func_00105900(p, g->layer);
    }
    p = func_00105860(tex, 0);
    *(u64 *)(p + 0x20) = (u64)(*(u32 *)g->colour[1] & 0xFFFFFF) | 0x3F80000040000000;
    *(u64 *)(p + 0x28) = UV(u, v);
    *(u64 *)(p + 0x38) = UV(g->font->cell_w + u, g->font->cell_h - 1 + v);
    *(u64 *)(p + 0x30) = XYZ(g->x - 2, SCREEN_Y(g->y - 1));
    *(u64 *)(p + 0x40) = XYZ(g->w + g->x + 2, SCREEN_Y(g->h + 4) + SCREEN_Y(g->y - 1));
    func_00105900(p, g->layer);
    p = func_00105860(tex, 0);
    *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[1]);
    *(u64 *)(p + 0x20) = (u64)(*(u32 *)g->colour[1] & 0xFFFFFF) | 0x3F80000040000000;
    *(u64 *)(p + 0x28) = UV(u, v);
    *(u64 *)(p + 0x38) = UV(g->font->cell_w + u, g->font->cell_h - 1 + v);
    *(u64 *)(p + 0x30) = XYZ(g->x - 1, SCREEN_Y(g->y));
    *(u64 *)(p + 0x40) = XYZ(g->w + g->x + 1, SCREEN_Y(g->h + 2) + SCREEN_Y(g->y));
    func_00105900(p, g->layer);
    p = func_00105860(tex, 0);
    *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[0]);
    glyph_sprite(p, g, u, v, g->x, g->y + 1);
    func_00105900(p, g->layer + 1);
}

/* 0x001458A0, 0x664 bytes. Style 4: an outline of the second corner's colour (eight copies
 * around, offsets at 0x00405420), then the character one pixel right, in the layer above. */
void func_001458A0(Glyph *g)
{
    u64 tex = glyph_tex(g);
    u32 u, v;
    int i;
    u8 *p;

    glyph_cell(g, &u, &v);
    for (i = 0; i < 8; i++) {
        p = func_00105860(tex, 0);
        *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[1]);
        glyph_sprite(p, g, u, v, g->x + g_00405420[i][0], g->y + g_00405420[i][1] + 1);
        func_00105900(p, g->layer);
    }
    p = func_00105860(tex, 0);
    *(u64 *)(p + 0x20) = RGBAQ(*(u32 *)g->colour[0]);
    glyph_sprite(p, g, u, v, g->x + 1, g->y);
    func_00105900(p, g->layer + 1);
}

/* 0x00145F10, 0x34 bytes. Style 5: the callback. */
void func_00145F10(Glyph *g)
{
    if (g_0056CCA0.custom != 0)
        g_0056CCA0.custom(g);
}

/* 0x00145F50, 0x58 bytes, matching. Before a string: the alpha blending (ALPHA_2 = 0x44), except for
 * style 5. */
void func_00145F50(int layer)
{
    if (g_0056CCA0.style != 5) {
        u8 *p = func_001050F0();

        *(u64 *)(p + 0x10) = 0x44;
        *(u64 *)(p + 0x18) = 0x43;
        func_00105230(p, layer);
    }
}

/* 0x00145FB0, 0x3C bytes. A character's cell: from ' ' in a grid (0xFF past its end), or the
 * table's entry (bit 31). */
u32 func_00145FB0(Font *f, u32 c)
{
    if (f->cells == 0) {
        c -= 0x20;
        if (c >= f->count)
            c = 0xFF;
    } else {
        c |= 0x80000000;
    }
    return c;
}

/* 0x00145FF0, 0x27C bytes. Draws a button icon (`code` = the letter after 0xF0, minus '@');
 * icons 8, 10 and 15 are twice as wide. */
void func_00145FF0(Glyph *g)
{
    switch (g->code) {
    case 0:
        func_001A5890(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 1:
        func_001A5B50(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 2:
        func_001A55D0(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 3:
        func_001A5E10(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 4:
        func_001A6910(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 5:
        func_001A6BD0(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 6:
        func_001A6E90(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 7:
        func_001A7150(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 8:
        func_001A7410(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w * 2, g->h);
        break;
    case 10:
        func_001A74D0(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w * 2, g->h);
        break;
    case 12:
        func_001A6650(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 13:
        func_001A6390(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 14:
        func_001A60D0(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w, g->h);
        break;
    case 15:
        func_001A76E0(g->x, g->y, g_0056CCA0.depth, g->colour[0][3], g->layer, g->w * 2, g->h);
        break;
    }
}

/* Sets a glyph's four corners from the state's colours. */
static inline void glyph_colours(Glyph *g)
{
    int i;

    for (i = 0; i < 4; i++) {
        g->colour[i][0] = g_004248F0[g_0056CCA0.colour[i]][0];
        g->colour[i][1] = g_004248F0[g_0056CCA0.colour[i]][1];
        g->colour[i][2] = g_004248F0[g_0056CCA0.colour[i]][2];
        g->colour[i][3] = g_0056CCA0.alpha[i];
    }
}

/* Whether a byte leads a two-byte (Shift-JIS) character. */
#define IS_LEAD(c) (((c) >= 0x80 && (c) <= 0x9F) || ((c) >= 0xE0 && (c) <= 0xEF) \
                    || ((c) >= 0xFA && (c) <= 0xFC))

/* 0x00146270, 0x8B4 bytes. Draws a string at (`x`, `y`) in layer `layer`. */
void func_00146270(const u8 *text, int x, int y, int layer, int kind)
{
    float sy = g_0056CCA0.scale_y;
    float sx;
    u32 cw = (u32)((float)g_004053C0.draw_w * g_0056CCA0.scale_x / 20.0f);
    u32 ch = (u32)((float)g_004053C0.draw_h * g_0056CCA0.scale_y / 20.0f);
    Glyph g;
    int drawn = 0;
    u8 c;

    g.font = &g_004053C0;
    g.layer = layer;
    glyph_colours(&g);
    if (g_0056CCA0.style == 3 || (u32)(g_0056CCA0.style - 4) < 2) {
        g.colour[1][0] = g_004248F0[g_0056CCA0.outline][0];
        g.colour[1][1] = g_004248F0[g_0056CCA0.outline][1];
        g.colour[1][2] = g_004248F0[g_0056CCA0.outline][2];
    }
    sx = g_0056CCA0.scale_x;
    g.kind = kind;
    g.x = x;
    g.y = y;
    func_00145F50(layer);
    c = *text;
    if (c != 0) {
        u32 isx = (u32)sx;
        u32 isy = (u32)sy;
        int tab = ((int)isx >> 1) * 4;

        do {
            const u8 *next = text;

            if (c == ']') {
                glyph_colours(&g);
            } else if (c == '[') {
                int n = (text[1] - '0') * 10 + (text[2] - '0');
                int i;

                for (i = 0; i < 4; i++) {
                    g.colour[i][0] = g_004248F0[n][0];
                    g.colour[i][1] = g_004248F0[n][1];
                    g.colour[i][2] = g_004248F0[n][2];
                    g.colour[i][3] = g_0056CCA0.alpha[i];
                }
                next = text + 2;
            } else if (c == '\t') {
                g.x = tab * ((g.x + tab - 1) / tab);
            } else if (c == '\n') {
                g.y += g_0056CCA0.line_h;
                g.x = x;
            } else {
                int start = 0;

                if (c < 0x20 || c > 0x7E) {
                    if (!IS_LEAD(c)) {
                        if (c == 0xF0) {
                            g.code = text[1] - 0x40;
                            g.w = isx;
                            g.h = isy;
                            func_00145FF0(&g);
                            g.x += g.w;
                            next = text + 1;
                            if (g.code == 8 || g.code == 10 || g.code == 15) {
                                g.x += g.w;
                                next = text + 3;
                            }
                        }
                        goto advance;
                    }
                    text++;
                    c = '@';
                }
                g.code = func_00145FB0(g.font, c);
                if (g.font->widths != 0) {
                    start = g.x;
                    if (UBIT(g_0056CCA0.flags, 0) == 0) {
                        if UBIT(g_0056CCA0.flags, 1)
                            g.x += (0xC - g.font->widths[g.code]) / 2;
                    } else {
                        g.x += ((int)(cw & 0xFFFF)
                                - (int)((float)(g.font->draw_w * g.font->widths[g.code]
                                                / g.font->cell_w) * sx / 20.0f)) / 2;
                    }
                }
                g.w = cw & 0xFFFF;
                g.h = ch & 0xFFFF;
                g_00424950[g_0056CCA0.style](&g);
                drawn++;
                next = text;
                if (g.font->widths == 0) {
                    g.x += g.w;
                } else if (UBIT(g_0056CCA0.flags, 0) == 0) {
                    if UBIT(g_0056CCA0.flags, 1)
                        g.x = start + 0xC;
                    else
                        g.x += (int)((float)(g.font->draw_w * g.font->widths[g.code]
                                             / g.font->cell_w) * sx / 20.0f);
                } else {
                    g.x = start + g.w;
                }
            }
advance:
            text = next + 1;
            c = *text;
        } while (c != 0);
    }
}

/* 0x00146B40, 0x158 bytes. Draws a string squeezed into `max_w` x `max_h`; its width. */
int func_00146B40(const u8 *text, int x, int y, int max_w, int max_h, int layer, int kind)
{
    float sy = g_0056CCA0.scale_y;
    float sx = g_0056CCA0.scale_x;
    float old;
    int w, h;

    func_00146D80(text, &w, &h);
    if (max_w < w)
        sx = (float)max_w * g_0056CCA0.scale_x / (float)w;
    g_0056CCA0.scale_y = sy;
    if (max_h < h)
        g_0056CCA0.scale_y = (float)max_h * sy / (float)h;
    old = g_0056CCA0.scale_x;
    g_0056CCA0.scale_x = sx;
    func_00146270(text, x, y, layer, kind);
    func_00146D80(text, &w, &h);
    g_0056CCA0.scale_x = old;
    g_0056CCA0.scale_y = sy;
    return w;
}

/* 0x00146CA0, 0x60 bytes, matching. A string's width at scale `scale`. */
int func_00146CA0(float scale, const u8 *text)
{
    float sx = g_0056CCA0.scale_x;
    float sy = g_0056CCA0.scale_y;
    int w;

    g_0056CCA0.scale_x = scale;
    g_0056CCA0.scale_y = scale;
    w = func_00146D80(text, 0, 0);
    g_0056CCA0.scale_x = sx;
    g_0056CCA0.scale_y = sy;
    return w;
}

/* 0x00146D00, 0x74 bytes. The same, the scale reduced to fit `max` pixels. */
int func_00146D00(float scale, const u8 *text, int max)
{
    int w = func_00146CA0(scale, text);

    if (max < w)
        scale = (float)max * scale / (float)w;
    return func_00146CA0(scale, text);
}

/* The width of one character. */
static inline int char_width(u8 c, float sx)
{
    if (g_004053C0.widths == 0 || UBIT(g_0056CCA0.flags, 0))
        return (int)((float)g_004053C0.draw_w * sx / 20.0f);
    if UBIT(g_0056CCA0.flags, 1)
        return 0xC;
    return (int)((float)(g_004053C0.draw_w * g_004053C0.widths[func_00145FB0(&g_004053C0, c)]
                         / g_004053C0.cell_w) * sx / 20.0f);
}

/* 0x00146D80, 0x2E0 bytes. A string's size: its widest line, and its height; the width. */
int func_00146D80(const u8 *text, int *w, int *h)
{
    float sx = g_0056CCA0.scale_x;
    int x = 0, widest = 0, height = 0;
    u8 c = *text;

    if (c != 0) {
        int isx;

        height = (int)g_0056CCA0.scale_y;
        isx = (int)g_0056CCA0.scale_x;
        do {
            if (c != ']') {
                if (c == '[') {
                    text += 2;
                } else if (c != '\t') {
                    if (c == '\n') {
                        if (widest < x)
                            widest = x;
                        x = 0;
                        height += g_0056CCA0.line_h;
                    } else {
                        if (c < 0x20 || c > 0x7E) {
                            if (!IS_LEAD(c)) {
                                if (c == 0xF0) {
                                    text++;
                                    x += isx;
                                }
                                goto next;
                            }
                            text++;
                            c = '@';
                        }
                        x += char_width(c, sx);
                    }
                }
            }
next:
            text++;
            c = *text;
        } while (c != 0);
    }
    if (x <= widest)
        x = widest;
    if (w != 0)
        *w = x;
    if (h != 0)
        *h = height;
    return x;
}

/* 0x00147070, 0xEC bytes. The number of characters drawn by a string (icons included). */
int func_00147070(const u8 *text)
{
    int n = 0;
    u8 c = *text;

    while (c != 0) {
        if (c != ']') {
            if (c == '[') {
                text += 2;
            } else if (c != '\t' && c != '\n') {
                if (c < 0x20 || c > 0x7E) {
                    if (!IS_LEAD(c)) {
                        if (c == 0xF0) {
                            n++;
                            text++;
                        }
                    } else {
                        n++;
                        text++;
                    }
                } else {
                    n++;
                }
            }
        }
        text++;
        c = *text;
    }
    return n;
}

/* 0x00147160, 0x3A8 bytes. Copies a string to `out`, breaking lines at spaces so that none is
 * wider than `max` (the space becomes LF); the size in *w / *h, the width. The lead byte of a
 * two-byte character is not copied (as in the original). */
int func_00147160(const u8 *text, u8 *out, int max, int *w, int *h)
{
    float sx = g_0056CCA0.scale_x;
    int height = 0, x = 0, widest = 0, space_x = 0;
    u8 *space = (u8 *)text;
    u8 c = *text;

    if (c != 0) {
        int isx;

        height = (int)g_0056CCA0.scale_y;
        isx = (int)g_0056CCA0.scale_x;
        do {
            if (c != '\n' && max < x) {
                *space = '\n';
                if (widest < space_x)
                    widest = space_x;
                x -= space_x;
                height += g_0056CCA0.line_h;
            }
            c = *text;
            if (c == ' ') {
                space_x = x;
                space = out;
                goto measure;
            } else if (c != ']') {
                if (c == '[') {
                    out[0] = '[';
                    out[1] = text[1];
                    text += 2;
                    out += 2;
                } else if (c != '\t') {
                    if (c != '\n')
                        goto measure;
                    if (widest < x)
                        widest = x;
                    x = 0;
                    height += g_0056CCA0.line_h;
                }
            }
            goto copy;
measure:
            if (c < 0x20 || c > 0x7E) {
                if (!IS_LEAD(c)) {
                    if (c == 0xF0) {
                        text++;
                        *out++ = 0xF0;
                        x += isx;
                    }
                    goto copy;
                }
                text++;
                c = '@';
            }
            x += char_width(c, sx);
copy:
            *out++ = *text++;
            c = *text;
        } while (c != 0);
    }
    if (max < x) {
        *space = '\n';
        if (widest < space_x)
            widest = space_x;
        x -= space_x;
        height += g_0056CCA0.line_h;
    }
    *out = *text;
    if (widest < x)
        widest = x;
    if (w != 0)
        *w = widest;
    if (h != 0)
        *h = height;
    return widest;
}

/* 0x00147520, 0x58 bytes, matching. The same at scale `scale`. */
int func_00147520(float scale, const u8 *text, u8 *out, int max, int *w, int *h)
{
    float sx = g_0056CCA0.scale_x;
    float sy = g_0056CCA0.scale_y;
    int r;

    g_0056CCA0.scale_x = scale;
    g_0056CCA0.scale_y = scale;
    r = func_00147160(text, out, max, w, h);
    g_0056CCA0.scale_x = sx;
    g_0056CCA0.scale_y = sy;
    return r;
}
