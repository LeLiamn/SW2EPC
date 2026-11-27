/*
 * cmnparts.c - common interface parts (original source file cmnparts.c: its name is passed to
 * the file loader at 0x001A9030 and 0x001A9140, which open LINKDATA entry 6, the portraits).
 * Written: 0x001A8F00-0x001AC970 (portraits, glyph and name sprites, TIM2 drawing, window layouts,
 * interface textures, target search); the projectile code after it is likely Bullet.c.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Portraits: 0xB1 images of 0x1600 bytes (64 x 72, 8-bit, then a 256-colour palette) kept in a
 * 0x70A40-byte buffer; officer portraits 0-0x21 and 0x33-0x38 have four variants each,
 * 0x22-0x32 one. A portrait object (0x170 bytes) holds two GS uploads (image, palette) and a
 * sprite packet at +0x120.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"
typedef unsigned long long u64;

#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */

/* A texture coordinate pair (texel centres). */
#define GS_UV(u, v) ((u64)(long long)((u) << 4 | 8) | (u64)(long long)((v) << 4 | 8) << 16)

extern u8 *g_0068F3D0;                   /* the portraits' buffer */
extern u8 *g_0068F10C[0xB1];             /* the portraits loaded */
extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each; +6 portrait) */
extern const char g_00425D40[];          /* "cmnparts.c" */

void func_00118850(void *p, u32 n);
void func_00118AC0(void *d, const void *s, u32 n);
void *func_00102DB0(int align, u32 n);
void func_00102EC0(void *p);
void *func_001026D0(int a, int b, int c, int d, int e, int f, const void *file, int line);
int func_003620E0(int p, int slot);
u32 func_002F27D0(u32 id);
u8 *func_00104250(u32 n);
void func_00104520(u8 *p);
void func_001057F0(u8 *p, u64 tex0, int a);
void func_00104600(u8 *p, const u8 *src, u32 n, int dbp, int dbw, int psm, int x, int y);
void func_001046E0(u8 *p, int layer);
u8 *func_00105860(u64 tex, int a);
void func_00105900(u8 *p, int layer);
const char *func_0019B0C0(u32 id);
int func_00146D00(float size, const char *s, int h);

void func_001A9030(void);
void func_001A9450(u8 *f, int x, int y, int z, int w, int h, int alpha, int flip, int half);

/* A screen point; `half` gives it in half lines (unscaled). */
static inline u64 face_xyz(int x, int sy, int z, int half)
{
    if (half != 0)
        return (u64)(long long)(x * 0x10 + 0x7000) | (u64)(long long)(sy * 8 + 0x7900) << 16
               | (u64)(long long)(0xFFFE - z) << 32;
    return (u64)(long long)(x * 0x10 + 0x7000)
           | (u64)(long long)((sy * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16
           | (u64)(long long)(0xFFFE - z) << 32;
}

static inline int scale_y(int y)
{
    return y * 0x280 / 0x1E0 * 0x1C0 / 0x200;
}

/* 0x001A8F00, 0x30 bytes. Takes the portraits' buffer and loads the main portraits. */
void func_001A8F00(void)
{
    g_0068F3D0 = func_00102DB0(0x10, 0x70A40);
    func_001A9030();
}

/* 0x001A8F30, 0xF8 bytes. Copies portrait `k` (variant `v`) from the portraits' file `f` (+0
 * the file, +4 its table) to `dst` and records it. Returns the next free place. */
u8 *func_001A8F30(u8 **f, u8 *dst, int k, int v)
{
    int i;

    if (k >= 0 && k <= 0x21)
        i = v + k * 4;
    else if (k >= 0x22 && k <= 0x32)
        i = k + 0x66;
    else if (k >= 0x33 && k <= 0x38)
        i = v + (k - 0x33) * 4 + 0x99;
    else
        return dst;
    func_00118AC0(dst, f[0] + *(int *)(f[0] + 8) * *(int *)(f[1] + i * 8) + 0x40, 0x1600);
    g_0068F10C[i] = dst;
    return dst + 0x1600;
}

/* 0x001A9030, 0x104 bytes. Loads the first variant of portraits 0-0x21, 0x30 and 0x33-0x38. */
void func_001A9030(void)
{
    u8 *f[2], *p;
    u8 *file;
    int k;

    func_00118850(g_0068F10C, 0x2C4);
    file = func_001026D0(1, 6, 0, 1, 0, 0, g_00425D40, 0x56D);
    f[0] = file;
    f[1] = file + 0x10;
    p = g_0068F3D0;
    for (k = 0; k < 0x1C; k++)
        p = func_001A8F30(f, p, k, 0);
    for (k = 0x1C; k < 0x22; k++)
        p = func_001A8F30(f, p, k, 0);
    p = func_001A8F30(f, p, 0x30, 0);
    for (k = 0x33; k < 0x39; k++)
        p = func_001A8F30(f, p, k, 0);
    func_00102EC0(file);
}

/* 0x001A9140, 0x204 bytes. Loads the portraits needed by the players' officers (eight each, all
 * four variants) and 0x22-0x32. */
void func_001A9140(void)
{
    int used[0x40];
    int n = 0, p, s, k;

    func_00118850(g_0068F10C, 0x2C4);
    func_00118850(used, 0x100);
    for (p = 0; p < 2; p++) {
        for (s = 0; s < 8; s++) {
            int o = func_003620E0(p, s);

            if (o >= 0 && o < 0x19F) {
                n += 4;
                used[g_005BA6A0[func_002F27D0(o) * 0x2C + 6]] = 1;
            }
        }
    }
    for (k = 0x22; k < 0x33; k++, n++)
        used[k] = 1;
    if (n > 0) {
        u8 *file = func_001026D0(1, 6, 0, 1, 0, 0, g_00425D40, 0x5AE), *f[2], *d;

        f[0] = file;
        f[1] = file + 0x10;
        d = g_0068F3D0;
        for (k = 0; k < 0x39; k++) {
            if (used[k] == 0)
                continue;
            if (k < 0x22 || k > 0x32) {
                for (s = 0; s < 4; s++)
                    d = func_001A8F30(f, d, k, s);
            } else {
                d = func_001A8F30(f, d, k, 0);
            }
        }
        func_00102EC0(file);
    }
}

/* 0x001A9350, 0x48 bytes. Frees the portraits. */
void func_001A9350(void)
{
    if (g_0068F3D0 != 0) {
        func_00102EC0(g_0068F3D0);
        g_0068F3D0 = 0;
    }
    func_00118850(g_0068F10C, 0x2C4);
}

/* 0x001A93A0, 0xAC bytes, matching. A new portrait object. */
u8 *func_001A93A0(int x, int y, int z, int w, int h, int alpha, int flip, int half)
{
    u8 *f = func_00104250(0x170);

    func_001A9450(f, x, y, z, w, h, alpha, flip, half);
    return f;
}

/* Sets the portrait's sprite: (0, 0)-(0x40, 0x47), mirrored with `flip`, at (x, y), w x h. */
static inline void face_sprite(u8 *f, int x, int y, int z, int w, int h, int alpha, int flip,
                               int half)
{
    int sy = scale_y(y);

    *(u64 *)(f + 0x140) = (u64)(long long)alpha << 24 | 0x3F80000000808080ULL;
    *(u64 *)(f + 0x148) = flip == 0 ? 0x80008 : 0x803F8;
    *(u64 *)(f + 0x158) = flip == 0 ? 0x4780408 : 0x4780008;
    *(u64 *)(f + 0x150) = face_xyz(x, sy, z, half);
    *(u64 *)(f + 0x160) = face_xyz(w + x, scale_y(h) + sy, z, half);
}

/* 0x001A9450, 0x6DC bytes. Sets portrait object `f` up: its two uploads, its texture (at 0x1D04,
 * or 0x1324 with `half`) and its sprite. */
void func_001A9450(u8 *f, int x, int y, int z, int w, int h, int alpha, int flip, int half)
{
    func_00104520(f);
    func_00104520(f + 0x90);
    func_001057F0(f + 0x120, half == 0 ? 0x2003A005D9309D04ULL : 0x20026405D9309324ULL, 0);
    face_sprite(f, x, y, z, w, h, alpha, flip, half);
}

/* 0x001A9B30, 0x1A8 bytes. Puts portrait `id` (low byte the portrait, high byte the variant;
 * the first loaded one when it is not) into object `f`'s uploads. */
void func_001A9B30(u8 *f, u32 id, int half)
{
    u32 k = id & 0xFF;
    int v = (int)(id & 0xFFFF) >> 8, i = 0;
    u8 *img;

    if (k < 0x22)
        i = v + k * 4;
    else if (k < 0x33)
        i = k + 0x66;
    else if (k < 0x39)
        i = v + (k - 0x33) * 4 + 0x99;
    if (g_0068F10C[i] == 0) {
        for (i = 0; i < 0xB1; i++) {
            if (g_0068F10C[i] != 0)
                break;
        }
    }
    img = g_0068F10C[i];
    if (img == 0)
        return;
    if (half == 0) {
        func_00104600(f, img, 0x1200, 0x1D04, 0x13, 2, 0, 0);
        func_00104600(f + 0x90, img + 0x1200, 0x400, 0x1D00, 0, 0x10, 0, 0);
    } else {
        func_00104600(f, img, 0x1200, 0x1324, 0x13, 2, 0, 0);
        func_00104600(f + 0x90, img + 0x1200, 0x400, 0x1320, 0, 0x10, 0, 0);
    }
}

/* 0x001A9CE0, 0x5C4 bytes. Moves portrait object `f`'s sprite. */
void func_001A9CE0(u8 *f, int x, int y, int z, int w, int h, int alpha, int flip, int half)
{
    face_sprite(f, x, y, z, w, h, alpha, flip, half);
}

/* 0x001AA2B0, 0xC bytes, matching. Hides it. */
void func_001AA2B0(u8 *f)
{
    *(u64 *)(f + 0x150) = 0;
    *(u64 *)(f + 0x160) = 0;
}

/* 0x001AA2C0, 0x54 bytes, matching. Draws it on layer `layer` (when shown). */
void func_001AA2C0(u8 *f, int layer)
{
    if (*(u64 *)(f + 0x150) != 0) {
        func_001046E0(f, layer);
        func_001046E0(f + 0x90, layer);
        func_00105900(f + 0x120, layer);
    }
}

/* 0x001AA320, 0xD8 bytes. The width at size `size` of character `c` of font `font` (+0x14 its
 * count, +0x18 its widths, +0x20 / +0x24 the scale), or above 0x2D0 of officer name `c`. */
int func_001AA320(float size, u8 *font, u32 c)
{
    if (c <= 0x2D0) {
        if (c < *(u32 *)(font + 0x14))
            return (int)((float)(*(u16 *)(font + 0x24) * (*(u8 **)(font + 0x18))[c]
                                 / *(u16 *)(font + 0x20)) * size / 20.0f);
        return 0;
    }
    return func_00146D00(size, func_0019B0C0(c), (int)(size * 72.0f / 20.0f));
}

/* A font (0x004053C0 the text font, 0x004053F0 the names' font). */
typedef struct {
    u64 tex0[2];          /* the two texture pages (the second for glyphs past 400) */
    u16 *uv;              /* +0x10 the extra glyphs' texels */
    u32 count;            /* +0x14 glyphs with a width */
    u8 *widths;           /* +0x18 */
    u16 tex_w, tex_h;     /* +0x1C */
    u16 cell_w, cell_h;   /* +0x20 */
    u16 scale;            /* +0x24 */
    u16 pad;
    u16 cols, rows;       /* +0x28 glyphs per row and rows per page */
} Font;

extern Font g_004053C0, g_004053F0;
extern const u8 g_004248F0[][4];         /* text colours (RGB) */

u32 func_00145FB0(Font *f, u32 c);
int func_00146CA0(float size, const u8 *s);
const u8 *func_003724C0(void);
u32 func_003629E0(u8 *rec);
u32 func_0019AE90(u32 t);

/* A float point as a GS one (VU0 ftoi4: x 16, z kept whole). */
static inline u64 xyz_ftoi4(float x, float y, float z)
{
    int ix = (int)(x * 16.0f), iy = (int)(y * 16.0f), iz = (int)(z * 16.0f);

    return (u64)(long long)(iz >> 4) << 32 | (u64)(long long)ix | (u64)(long long)iy << 16;
}

/* An RGBAQ of text colour `k` with alpha `a`. */
#define TEXT_RGBA(k, a) \
    ((u64)(long long)(int)((u32)(a) << 24 | g_004248F0[k][0] | g_004248F0[k][1] << 8 \
                           | g_004248F0[k][2] << 16) | 0x3F80000000000000ULL)

/* Two floats as one 64-bit ST register. */
static inline u64 st_pair(float s, float t)
{
    union { float f[2]; u64 v; } u;

    u.f[0] = s;
    u.f[1] = t;
    return u.v;
}

/* 0x001AA400, 0x5A4 bytes. Glyph `c` of the names' font at size `size` (height `h`) at point
 * `pos` into packet `p` (colour `col`, alpha `a`; `flat` for screen coordinates, else GS ones
 * with narrower glyphs at half height). Returns its width. */
float func_001AA400(float size, float h, u8 *p, u32 c, float *pos, int col, int a, int flat)
{
    Font *f = &g_004053F0;
    float w = 0.0f, x1, y1;
    u32 u, v;

    if (c <= 0x2D0)
        w = size * (float)f->widths[c] / 20.0f;
    if (flat == 0) {
        w = w * 0.8f;
        y1 = h * 0.5f + pos[1] + 0.0f;
    } else {
        y1 = pos[1] + h;
    }
    x1 = pos[0] + w;
    *(u64 *)(p + 0x18) = (c & 0x7FFFFFFF) <= 400 ? f->tex0[0] : f->tex0[1];
    *(u64 *)(p + 0x20) = TEXT_RGBA(col, a);
    v = f->uv[c * 2 + 1];
    u = f->uv[c * 2];
    *(u64 *)(p + 0x28) = st_pair((float)u / (float)f->tex_w + 0.001f, (float)(v + 1) / (float)f->tex_h);
    *(u64 *)(p + 0x38) = st_pair((float)(u + f->widths[c]) / (float)f->tex_w,
                                 (float)(v + f->cell_h) / (float)f->tex_h - 0.001f);
    if (flat == 0) {
        *(u64 *)(p + 0x30) = xyz_ftoi4(pos[0], pos[1], pos[2]);
        *(u64 *)(p + 0x40) = xyz_ftoi4(x1, y1, pos[2]);
    } else {
        int sy0 = scale_y((int)pos[1]), sy1 = scale_y((int)y1);

        *(u64 *)(p + 0x30) = (u64)(long long)(int)(65534.0f - pos[2]) << 32
                             | (u64)(long long)((int)pos[0] * 0x10 + 0x7000)
                             | (u64)(long long)((sy0 * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
        *(u64 *)(p + 0x40) = (u64)(long long)(int)(65534.0f - pos[2]) << 32
                             | (u64)(long long)((int)x1 * 0x10 + 0x7000)
                             | (u64)(long long)((sy1 * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
    }
    return w;
}

/* 0x001AA9B0, 0x7C8 bytes. Officer `id`'s name (0x2F9: func_003724C0's text) in the text font,
 * one packet per glyph from `p` (shrunk to fit size x 72 / 20); two-byte characters are drawn
 * as '@'. The width goes to `out` (when given). Returns the number of glyphs. */
int func_001AA9B0(float size, float h, u8 *p, u32 id, float *pos, int col, int a, int flat,
                  float *out)
{
    Font *f = &g_004053C0;
    float x = pos[0], y0 = pos[1], z = pos[2], y1, cw, m;
    const u8 *s = id == 0x2F9 ? func_003724C0() : (const u8 *)func_0019B0C0(id);
    int n = 0, tw;
    u32 code = 0;   /* (left unset in the original before the first character) */

    y1 = flat == 0 ? h * 0.5f + pos[1] + 0.0f : pos[1] + h;
    tw = func_00146CA0(size, s);
    m = size * 72.0f / 20.0f;
    if (m < (float)tw)
        size = size * m / (float)tw;
    cw = size * (float)f->scale / (float)f->cell_w;
    for (; *s != 0; s++, n++, p += 0x50) {
        u32 ch = *s, g, gu, gv;
        int adv;

        if (ch >= 0x20 && ch <= 0x7E) {
            code = ch;
        } else if ((ch >= 0x80 && ch < 0xA0) || (ch >= 0xE0 && ch < 0xF0)
                   || (ch >= 0xFA && ch < 0xFD)) {
            s++;
            code = 0x40;
        }
        g = func_00145FB0(f, code);
        if (g == 0xFF)
            break;
        if ((g & 0x80000000) == 0) {
            *(u64 *)(p + 0x18) = f->tex0[1] != (u64)-1 && g >= (u32)f->cols * f->rows
                                     ? f->tex0[1] : f->tex0[0];
        } else {
            *(u64 *)(p + 0x18) = (g & 0x7FFFFFFF) > 400 ? f->tex0[1] : f->tex0[0];
        }
        *(u64 *)(p + 0x20) = TEXT_RGBA(col, a);
        if ((g & 0x80000000) == 0) {
            int k = f->tex0[1] == (u64)-1 ? (int)g : (int)g % (f->cols * f->rows);

            gu = f->cell_w * (k % f->cols);
            gv = f->cell_h * (k / f->cols);
        } else {
            gu = f->uv[g * 2];
            gv = f->uv[g * 2 + 1];
        }
        *(u64 *)(p + 0x28) = st_pair((float)(int)gu / (float)f->tex_w, (float)(int)gv / (float)f->tex_h);
        *(u64 *)(p + 0x38) = st_pair((float)(int)(gu + f->cell_w) / (float)f->tex_w,
                                     (float)(int)(gv + f->cell_h - 1) / (float)f->tex_h);
        adv = g < f->count ? (int)((float)(f->scale * f->widths[g] / f->cell_w) * size / 20.0f)
                           : 0;
        if (flat == 0) {
            *(u64 *)(p + 0x30) = xyz_ftoi4(x, y0, z);
            *(u64 *)(p + 0x40) = xyz_ftoi4(cw * 0.8f + x + 0.0f, y1, z);
            x = (float)adv * 0.8f + x + 0.0f;
        } else {
            *(u64 *)(p + 0x30) = xyz_ftoi4(x + 1792.0f, 1.1666666f * y0 * 0.5f + 1936.0f,
                                           65534.0f - z);
            *(u64 *)(p + 0x40) = xyz_ftoi4(x + cw + 1792.0f, 1.1666666f * y1 * 0.5f + 1936.0f,
                                           65534.0f - z);
            x = x + (float)adv;
        }
    }
    if (out != 0)
        *out = x - pos[0];
    return n;
}

/* 0x001AB190, 0x3C bytes. Character `id` (below 0x2D1: one glyph of the names' font) or
 * officer name `id`. Returns the number of packets used. */
int func_001AB190(float size, float h, u8 *p, u32 id, float *pos, int col, int a, int flat,
                  float *out)
{
    if (id <= 0x2D0) {
        *out = func_001AA400(size, h, p, id, pos, col, a, flat);
        return 1;
    }
    return func_001AA9B0(size, h, p, id, pos, col, a, flat, out);
}

/* 0x001AB1D0, 0x1C4 bytes. Name `n`, a gap and title `t` (when they differ) from point `pos`
 * (moved past them). The width goes to `out` (when given). Returns the packets used. */
int func_001AB1D0(float size, float h, u8 *p, u32 t, u32 n, float *pos, int col, int a,
                  int flat, float *out)
{
    float x = pos[0], w;
    int k = func_001AB190(size, h, p, n, pos, col, a, flat, &w);

    if (flat == 0)
        pos[0] = pos[0] + (float)(int)(size * 8.0f / 20.0f) * 0.8f + w + 0.0f;
    else
        pos[0] = pos[0] + w + (float)(int)(size * 8.0f / 20.0f);
    if (t != n) {
        k += func_001AB190(size, h, p + k * 0x50, func_0019AE90(t), pos, col, a, flat, &w);
        pos[0] = pos[0] + w;
    }
    if (out != 0)
        *out = pos[0] - x;
    return k;
}

/* 0x001AB3A0, 0x88 bytes. The width of record `rec`'s title with a gap and character 0x1DD. */
int func_001AB3A0(float size, u8 *font, u8 *rec)
{
    u32 t = func_0019AE90(func_003629E0(rec));

    return func_001AA320(size, font, t) + (int)(size * 8.0f / 20.0f) + func_001AA320(size, font, 0x1DD);
}

/* 0x001AB430, 0xB0 bytes. Draws record `rec`'s title and character 0x1DD. */
int func_001AB430(float size, float h, u8 *p, u8 *rec, float *pos, int col, int a, int flat,
                  float *out)
{
    return func_001AB1D0(size, h, p, 0x1DD, func_0019AE90(func_003629E0(rec)), pos, col, a, flat,
                         out);
}

extern int g_0045D1C8;                   /* (small data) 1: textures at the second place */

u8 *func_00106F10(u8 *tim2);
u64 func_00104AC0(u8 *tim2, int dbp, int layer);
u64 func_00104D00(u8 *tim2, int cbp, int layer);
u64 func_00106C50(u64 tex, u64 clut);

/* Image `k` of a pack `f` (+8 the unit, +0x10 the offsets). */
#define PACK_IMAGE(f, k) ((f) + *(int *)((f) + 8) * *(int *)((f) + 0x10 + (k) * 8))

/* 0x001AB4E0, 0x4B4 bytes. Draws TIM2 image `img` (with the palette of `pal`) on layer `layer`:
 * texels (u, v) `uw` x `vh` (-1: all) at (x, y) `w` x `h` (-1: its size), centred on (x, y)
 * with `centred`, colour `rgba`. */
void func_001AB4E0(u8 *img, u8 *pal, int x, int y, int z, int w, int h, int u, int v, int uw,
                   int vh, const u32 *rgba, int layer, int centred)
{
    u8 *info = func_00106F10(img);
    u64 t = func_00104AC0(img, g_0045D1C8 == 1 ? 0x1320 : 0x1D00, layer);
    u8 *p;

    t = func_00106C50(t, func_00104D00(pal, 0x3FFC, layer));
    p = func_00105860(t, 0);
    *(u64 *)(p + 0x20) = (u64)*rgba | 0x3F80000000000000ULL;
    if (uw == -1)
        uw = *(u16 *)(info + 0x14) - 1;
    if (vh == -1)
        vh = *(u16 *)(info + 0x16) - 1;
    *(u64 *)(p + 0x28) = GS_UV(u, v);
    *(u64 *)(p + 0x38) = GS_UV(uw + u, vh + v);
    if (w == -1)
        w = *(u16 *)(info + 0x14);
    if (h == -1)
        h = *(u16 *)(info + 0x16);
    if (centred != 0) {
        y = y - h / 2;
        x = x - w / 2;
    }
    *(u64 *)(p + 0x30) = (u64)(long long)(0xFFFE - z) << 32 | (u64)(long long)(x * 0x10 + 0x7000)
                         | (u64)(long long)((scale_y(y) * 0x10 - 0xE00) / g_70000154 + 0x8000) << 16;
    *(u64 *)(p + 0x40) = (u64)(long long)(0xFFFE - z) << 32
                         | (u64)(long long)((w + x) * 0x10 + 0x7000)
                         | (u64)(long long)((scale_y(h + y) * 0x10 - 0xE00) / g_70000154 + 0x8000)
                               << 16;
    func_00105900(p, layer);
}

/* 0x001AB9A0, 0x60 bytes, matching. The same in grey 0x80 with alpha `alpha`. */
void func_001AB9A0(u8 *img, u8 *pal, int x, int y, int z, int w, int h, int u, int v, int uw,
                   int vh, int alpha, int layer, int centred)
{
    u8 c[4];

    c[0] = 0x80;
    c[3] = (u8)alpha;
    c[1] = 0x80;
    c[2] = 0x80;
    func_001AB4E0(img, pal, x, y, z, w, h, u, v, uw, vh, (const u32 *)c, layer, centred);
}

/* 0x001ABA00, 0x70 bytes, matching. With its own palette. */
void func_001ABA00(u8 *img, int x, int y, int z, int w, int h, int u, int v, int uw, int vh,
                   int alpha, int layer, int centred)
{
    func_001AB9A0(img, img, x, y, z, w, h, u, v, uw, vh, alpha, layer, centred);
}

/* 0x001ABA70, 0x3C bytes, matching. The whole image. */
void func_001ABA70(u8 *img, int x, int y, int z, int w, int h, int alpha, int layer, int centred)
{
    func_001ABA00(img, x, y, z, w, h, 0, 0, -1, -1, alpha, layer, centred);
}

/* 0x001ABAB0, 0x50 bytes, matching. The size of TIM2 image `img`. */
void func_001ABAB0(u8 *img, u32 *w, u32 *h)
{
    u8 *info = func_00106F10(img);

    if (w != 0)
        *w = *(u16 *)(info + 0x14);
    if (h != 0)
        *h = *(u16 *)(info + 0x16);
}

/* 0x001ABB00, 0x90 bytes. Image `i` of pack `f` with the palette of image `j`. */
void func_001ABB00(u8 *f, int i, int j, int x, int y, int z, int w, int h, int u, int v, int uw,
                   int vh, const u32 *rgba, int layer, int centred)
{
    func_001AB4E0(PACK_IMAGE(f, i), PACK_IMAGE(f, j), x, y, z, w, h, u, v, uw, vh, rgba, layer,
                  centred);
}

/* 0x001ABB90, 0x150 bytes. Image `i` of pack `f` at point `pos`, scaled by (sx, sy). */
void func_001ABB90(float sx, float sy, u8 *f, int i, float *pos, int alpha, int layer,
                   int centred)
{
    u8 *img = PACK_IMAGE(f, i), *info = func_00106F10(img);

    func_001ABA00(img, (int)pos[0], (int)pos[1], (int)pos[2],
                  (int)((float)*(u16 *)(info + 0x14) * sx), (int)((float)*(u16 *)(info + 0x16) * sy),
                  0, 0, -1, -1, alpha, layer, centred);
}

/* 0x001ABCE0, 0x154 bytes. The same with colour `rgba`. */
void func_001ABCE0(float sx, float sy, u8 *f, int i, float *pos, const u32 *rgba, int layer,
                   int centred)
{
    u8 *img = PACK_IMAGE(f, i), *info = func_00106F10(img);

    func_001AB4E0(img, img, (int)pos[0], (int)pos[1], (int)pos[2],
                  (int)((float)*(u16 *)(info + 0x14) * sx), (int)((float)*(u16 *)(info + 0x16) * sy),
                  0, 0, -1, -1, rgba, layer, centred);
}

/* 0x001ABE40, 0x54 bytes. The whole image `i` of pack `f`. */
void func_001ABE40(u8 *f, int i, int x, int y, int z, int w, int h, int alpha, int layer,
                   int centred)
{
    func_001ABA70(PACK_IMAGE(f, i), x, y, z, w, h, alpha, layer, centred);
}

/* 0x001ABEA0, 0x74 bytes. Part of image `i` of pack `f`. */
void func_001ABEA0(u8 *f, int i, int x, int y, int z, int w, int h, int u, int v, int uw, int vh,
                   int alpha, int layer, int centred)
{
    func_001ABA00(PACK_IMAGE(f, i), x, y, z, w, h, u, v, uw, vh, alpha, layer, centred);
}

/* 0x001ABF20, 0x174 bytes. Image `i` of pack `f` with the palette of image `j`, scaled. */
void func_001ABF20(float sx, float sy, u8 *f, int i, int j, float *pos, int alpha, int layer,
                   int centred)
{
    u8 *img = PACK_IMAGE(f, i), *info = func_00106F10(img);

    func_001AB9A0(img, PACK_IMAGE(f, j), (int)pos[0], (int)pos[1], (int)pos[2],
                  (int)((float)*(u16 *)(info + 0x14) * sx), (int)((float)*(u16 *)(info + 0x16) * sy),
                  0, 0, -1, -1, alpha, layer, centred);
}

/* 0x001AC0A0, 0x38 bytes. The size of image `i` of pack `f`. */
void func_001AC0A0(u8 *f, int i, u32 *w, u32 *h)
{
    func_001ABAB0(PACK_IMAGE(f, i), w, h);
}

/* A window layout: its place when hidden and shown (x, y, w, h each) and three bytes. */
typedef struct {
    short from[4];
    short to[4];
    u8 b[4];
} Layout;

extern Layout g_0068F070[4];             /* the top, bottom and two side windows' layouts */
extern void *g_0068F0F0, *g_0068F0F8, *g_0068F100;   /* texture sets */
extern u32 g_0068F108;
extern u8 g_00574DE0[][0x630];           /* the units */

#define g_7000015C (*(u32 *)0x7000015C)          /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

void *func_00107440(u8 *img, int tbp, int cbp);
void *func_00107420(u8 *img, int a, int b, int c, int d, int tbp, int cbp);
void vu0_sincos(float a, float *s, float *c);    /* VU0 micro subroutine 0x20 */
float vu0_atan2(float y, float x);                /* VU0 micro subroutine 0x30 */
float sqrtf(float x);

static inline void set_layout(Layout *l, int x0, int y0, int x1, int y1, int w, int h)
{
    l->from[0] = (short)x0;
    l->from[1] = (short)y0;
    l->from[2] = (short)w;
    l->from[3] = (short)h;
    l->to[0] = (short)x1;
    l->to[1] = (short)y1;
    l->to[2] = (short)w;
    l->to[3] = (short)h;
    l->b[0] = 0x80;
    l->b[1] = 0x80;
    l->b[2] = 0xC;
    l->b[3] = 0;
}

/* 0x001AC0E0, 0x1B8 bytes. The four windows' layouts (sliding in from above, below and the
 * sides). */
void func_001AC0E0(void)
{
    set_layout(&g_0068F070[0], 0, -0x10, 0, 0, 0x168, 0x28);
    set_layout(&g_0068F070[1], 0x98, 0x168, 0x98, 0x158, 0x168, 0x28);
    set_layout(&g_0068F070[2], 0, -0x28, 0, 0, 0x130, 0x38);
    set_layout(&g_0068F070[3], 0xD0, 0x170, 0xD0, 0x148, 0x130, 0x38);
}

/* 0x001AC2A0, 0xFC bytes. Uploads officer `id`'s large portrait (LINKDATA entry 9 + portrait,
 * 0x2B for 0x22-0x32, entry - 7 for 0x33-0x38). */
void func_001AC2A0(u32 id)
{
    u8 k = g_005BA6A0[func_002F27D0(id) * 0x2C + 6];
    int e;
    u8 *f;

    if (k <= 0x21)
        e = k + 9;
    else if (k <= 0x32)
        e = 0x2B;
    else if (k <= 0x38)
        e = k - 7;
    else
        e = 9;
    f = func_001026D0(1, e, 0, 1, 0, 0, g_00425D40, 0xC76);
    func_00107440(f, 0x3860, 0x3F93);
    func_00102EC0(f);
}

/* 0x001AC3A0, 0x118 bytes. Loads the interface textures (LINKDATA entry 7: the two main sets and
 * two plates, the second replacing the first) and the portraits. */
void func_001AC3A0(void)
{
    u8 *f = func_001026D0(1, 7, 0, 1, 0, 0, g_00425D40, 0xC89);

    g_0068F0F0 = func_00107440(f + *(int *)(f + 8) * *(int *)(f + 0x10), 0x3560, 0x3EE3);
    g_0068F0F8 = func_00107440(f + *(int *)(f + 8) * *(int *)(f + 0x18), 0x3660, 0x3F53);
    g_0068F100 = func_00107420(f + *(int *)(f + 8) * *(int *)(f + 0x20), 0, 0x4C, 0x80, 0x80,
                               0x3860, 0x3F97);
    g_0068F100 = func_00107420(f + *(int *)(f + 8) * *(int *)(f + 0x28), 0, 0x4C, 0x80, 0x80,
                               0x3860, 0x3F9B);
    func_00102EC0(f);
    g_0068F108 = 0;
    func_001A8F00();
}

/* 0x001AC4C0, 0x1C bytes, matching. Frees the portraits. */
void func_001AC4C0(void)
{
    func_001A9350();
}

/* Wraps an angle into (-pi, pi]. */
static inline float wrap_angle(float a)
{
    if (a > 3.1415927f)
        return a - 6.2831855f;
    if (a <= -3.1415927f)
        return a + 6.2831855f;
    return a;
}

/* 0x001AC4E0, 0x110 bytes. A random direction (sin, 0, cos, 0) at `base` plus an angle between
 * `lo` and `hi`. */
void func_001AC4E0(float lo, float hi, float base, float *out)
{
    float s, c;

    base = base + (hi - lo) / 65535.0f * (float)(RANDOM() % 0xFFFF) + lo + 0.0f;
    vu0_sincos(wrap_angle(base), &s, &c);
    out[0] = s;
    out[2] = c;
    out[1] = 0.0f;
    out[3] = 0.0f;
}

/* The heading of direction `d` (normalised first). */
static inline float heading(const float *d)
{
    float n = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    float q = 1.0f / (n + 0.0f);

    return wrap_angle(vu0_atan2(d[0] * q, d[2] * q));
}

/* 0x001AC5F0, 0x380 bytes. The enemy unit (of another side than `self`, flag 2 of +0x198, with a
 * model) whose heading from `pos` is closest to that of `dir` (within `best`) and farther than
 * `dist` (as Ghidra reads the test?). 0 for none or no `self`. */
u8 *func_001AC5F0(float best, float dist, float *dir, float *pos, u8 *self)
{
    u8 *found = 0, *u;
    float h;
    int k;

    if (self == 0)
        return 0;
    h = heading(dir);
    for (k = 0, u = g_00574DE0[0]; k < 0x8F; k++, u += 0x630) {
        float d[4], a;

        if ((u[0x198] & 2) == 0 || *(u32 *)(u + 0x11C) == 0 || u == self
            || (signed char)u[0x154] == (signed char)self[0x154])
            continue;
        d[0] = ((float *)(u + 0x90))[0] - pos[0];
        d[1] = ((float *)(u + 0x90))[1] - pos[1];
        d[2] = ((float *)(u + 0x90))[2] - pos[2];
        d[3] = 0.0f;
        if (!(dist < sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2])))
            continue;
        a = wrap_angle(heading(d) - h);
        if (a < 0.0f)
            a = -a;
        if (a < best) {
            best = a;
            found = u;
        }
    }
    return found;
}
