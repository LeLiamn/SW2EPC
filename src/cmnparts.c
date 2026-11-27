/*
 * cmnparts.c - common interface parts (original source file cmnparts.c: its name is passed to
 * the file loader at 0x001A9030 and 0x001A9140, which open LINKDATA entry 6, the portraits).
 * Written so far: functions from 0x001A8F00.
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
typedef unsigned long long u64;

#define g_70000154 (*(int *)0x70000154)    /* (scratchpad) the vertical scale */

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

/* 0x001A93A0, 0xAC bytes. A new portrait object. */
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

/* 0x001AA2B0, 0xC bytes. Hides it. */
void func_001AA2B0(u8 *f)
{
    *(u64 *)(f + 0x150) = 0;
    *(u64 *)(f + 0x160) = 0;
}

/* 0x001AA2C0, 0x54 bytes. Draws it on layer `layer` (when shown). */
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
