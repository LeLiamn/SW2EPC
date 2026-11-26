/*
 * texture.c - TIM2 pictures and GS textures (original source file unknown; it follows main.c,
 * 0x00106840-0x00107574, just before Sony's libraries). The first three functions are the
 * frame's start and end steps (they may belong to main.c's file).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A TIM2 file (see docs/formats/TIM2.md) is checked (version 4, one picture, no mipmaps), its
 * pixels and its CLUT are loaded into the GS memory at once (by Sony's image transfer), and the
 * TEX0 value to draw it with is built: base, buffer width, pixel format, log2 of the width and
 * height, colours with alpha, then the CLUT's base and format. The next free GS block can be
 * returned, so that callers can pack several textures.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define g_7000015C (*(u32 *)0x7000015C)          /* the random seed (scratchpad) */

extern volatile int g_0045D1AC;          /* (small data) 1: flip at vblank (system.c) */

void func_001020D0(void);
void func_001020E0(void);
void func_00102380(void);
void func_00143C90(void);
void func_00105F90(void);
void func_00114E30(void);
void func_001038D0(void);
void func_00126908(void *load, short dbp, short dbw, short psm, short x, short y, short w,
                   short h);                       /* sceGsSetDefLoadImage */
void func_00128060(int a);                         /* FlushCache */
void func_00126AF0(void *load, void *data);        /* sceGsExecLoadImage */
int func_001265F0(int a, int b);                   /* sceGsSyncPath */

/* 0x00106840, 0x34 bytes, matching. The end of a frame's drawing: the GS packets go out. */
void func_00106840(void)
{
    func_001020D0();
    func_00143C90();
    func_00105F90();
    func_00102380();
}

/* 0x00106880, 0x24 bytes, matching. */
void func_00106880(void)
{
    func_00114E30();
    func_001020E0();
}

/* 0x001068B0, 0x34 bytes, matching. The start of a frame: the random seed moves on, the pads are read. */
void func_001068B0(void)
{
    g_7000015C = g_7000015C * 0x41C64E6D + 0x3039;
    func_001038D0();
}

/* 0x001068F0, 0x8C bytes, matching. Loads `w` x `h` pixels at `data` into GS buffer `dbp` (width `dbw`,
 * format `psm`) at (`x`, `y`), at once; the vblank flip is held meanwhile. */
void func_001068F0(void *data, int dbp, int dbw, int psm, int x, int y, int w, int h)
{
    u8 load[0x60];

    func_00126908(load, dbp, dbw, psm, x, y, w, h);
    func_00128060(0);
    g_0045D1AC = 0;
    func_00126AF0(load, data);
    func_001265F0(0, 0);
    g_0045D1AC = 1;
}

/* 0x00106980, 0x38 bytes. log2 of `n` rounded up (at most 10: 1024). */
int func_00106980(int n)
{
    int i = 0;
    int size;

    for (size = 1; size < n; size <<= 1) {
        if (++i >= 10)
            break;
    }
    return i;
}

/* 0x001069C0, 0xE0 bytes. The buffer width (in 64 pixels) for a texture `width` pixels wide:
 * 4-bit and 8-bit textures round up to 128 pixels, others to 64. */
int func_001069C0(int psm, int width)
{
    int w;

    if (psm == 0x14)
        w = (width + 0x7F) / 128 * 128;
    else if (psm == 0x13)
        w = (width + 0x7F) / 128 * 128;
    else if (psm == 2)
        w = (width + 0x3F) / 64 * 64;
    else if (psm == 1)
        w = (width + 0x3F) / 64 * 64;
    else if (psm == 0)
        w = (width + 0x3F) / 64 * 64;
    else
        w = 0;
    return w / 64;
}

/* 0x00106AA0, 0x1AC bytes. Rounds a texture's size (*w, *h) up to what it takes in the GS
 * memory (blocks while it fits a page, else whole pages); the number of blocks. */
int func_00106AA0(int psm, int *w, int *h)
{
    int k = 0;
    int block_w, block_h, page_w, page_h, tw, th, rw, rh;

    if (psm == 0x14)
        k = 3;
    else if (psm == 0x13)
        k = 2;
    else if (psm == 2)
        k = 1;
    else if (psm == 1 || psm == 0)
        k = 0;
    block_w = 8 << ((k + 1) / 2);
    block_h = 8 << (k / 2);
    page_w = 0x20 << ((k + 2) / 2);
    page_h = 0x20 << ((k + 1) / 2);
    rw = rh = 0;
    tw = th = 0;
    while (!(page_w < tw || page_h < th)) {
        tw = 8 << ((k + 1) / 2);
        th = 8 << (k / 2);
        if (*w <= tw && *h <= th) {
            rw = tw;
            rh = th;
            break;
        }
        k++;
    }
    if (page_w < tw || page_h < th) {
        rw = page_w * ((*w + page_w - 1) / page_w);
        rh = page_h * ((*h + page_h - 1) / page_h);
    }
    *w = rw;
    *h = rh;
    return rw / block_w * (rh / block_h);
}

/* 0x00106C50, 0x34 bytes, matching. A TEX0 value from the texture part of `tex` and the CLUT part of
 * `clut`. */
u64 func_00106C50(u64 tex, u64 clut)
{
    return (tex & 0x1FFFFFFFFF) | (clut & 0xFFFFFFE000000000);
}

/* 0x00106C90, 0x38 bytes. Sets the CLUT base of a TEX0 value. */
u64 func_00106C90(u64 tex, int cbp)
{
    return (tex & 0xFFF8001FFFFFFFFF) | ((u64)(long long)cbp & 0x3FFF) << 37;
}

/* 0x00106CD0, 0x124 bytes. The TEX0 value for a texture already in the GS memory: base `tbp`,
 * format `psm`, `w` x `h` pixels, CLUT at `cbp` (none when negative) of format `cpsm`. */
u64 func_00106CD0(int tbp, int psm, int cbp, int cpsm, int w, int h)
{
    int tw = func_00106980(w);
    int th = func_00106980(h);
    int tbw;
    u64 fmt, clut;

    func_00106AA0(psm, &w, &h);
    tbw = func_001069C0(psm, w);
    fmt = (u64)(long long)psm << 20;
    if (cbp < 0)
        clut = 0;
    else
        clut = (u64)(long long)cpsm << 51 | fmt | (u64)(long long)cbp << 37 | 0x2000000000000000;
    return func_00106C50((u64)(long long)th << 30 | (u64)(long long)tw << 26 | fmt
                         | (u64)(long long)tbp | (u64)(long long)tbw << 14 | 0x400000000, clut);
}

/* 0x00106E00, 0x88 bytes. Whether a file is a TIM2 file this code reads: version 4, format 0,
 * one picture. */
int func_00106E00(const u8 *file)
{
    if (file[0] == 'T' && file[1] == 'I' && file[2] == 'M' && file[3] == '2') {
        if (file[4] == 4) {
            if (file[5] == 0)
                return *(const u16 *)(file + 6) == 1;
            return 0;
        }
        return 0;
    }
    return 0;
}

/* 0x00106E90, 0x70 bytes. The GS pixel format of a TIM2 picture (its image type at +0x13). */
int func_00106E90(const u8 *picture)
{
    switch (picture[0x13]) {
    case 4: return 0x14;     /* 4-bit: PSMT4 */
    case 5: return 0x13;     /* 8-bit: PSMT8 */
    case 1: return 2;        /* 16-bit: PSMCT16 */
    case 2: return 1;        /* 24-bit: PSMCT24 */
    case 3: return 0;        /* 32-bit: PSMCT32 */
    default: return 0;
    }
}

/* 0x00106F10, 0x8 bytes, matching. A TIM2 file's (first) picture header. */
u8 *func_00106F10(u8 *file)
{
    return file + 0x10;
}

/* 0x00106F20, 0x20 bytes, matching. Its width. */
u32 func_00106F20(u8 *file)
{
    return *(u16 *)(func_00106F10(file) + 0x14);
}

/* 0x00106F40, 0x20 bytes, matching. Its height. */
u32 func_00106F40(u8 *file)
{
    return *(u16 *)(func_00106F10(file) + 0x16);
}

/* 0x00106F60, 0x1D4 bytes. Loads all the CLUTs of a picture (header `picture`, CLUT data at
 * `data`) from GS buffer `cbp` on, at once (8-bit: 16 x 16, 4 buffers apart; 4-bit: 8 x 2, 1
 * apart; 32-bit or 16-bit colours). The next buffer in *next; the CLUT part of TEX0 (0 when the
 * picture has no CLUT this code reads). */
u64 func_00106F60(u8 *data, u8 *picture, int cbp, int *next)
{
    int w, h, step, psm, cpsm, qwords, i, at;
    u32 entries, count;

    if (picture[0x13] == 5) {
        h = 16;
        psm = 0x13;
        step = 4;
        w = 16;
    } else if (picture[0x13] == 4) {
        step = 1;
        psm = 0x14;
        h = 2;
        w = 8;
    } else {
        return 0;
    }
    entries = w * h;
    count = *(u16 *)(picture + 0xE) / entries;
    if ((picture[0x12] & 0x3F) == 3) {
        cpsm = 0;
        qwords = (int)entries >> 2;
    } else if ((picture[0x12] & 0x3F) == 1) {
        cpsm = 2;
        qwords = (int)entries >> 3;
    } else {
        return 0;
    }
    at = cbp;
    for (i = 0; i < (int)count; i++) {
        func_001068F0(data, at, 1, cpsm, 0, 0, w, h);
        data += qwords * 16;
        at += step;
    }
    if (next != 0)
        *next = at;
    return (u64)(long long)cpsm << 51 | (u64)(long long)psm << 20 | (u64)(long long)cbp << 37
           | 0x2000000000000000;
}

/* 0x00107140, 0x154 bytes. Loads a picture's pixels (`data`, header `picture`) into GS buffer
 * `tbp` at (`x`, `y`), at once, for a texture of `w` x `h`; the next free block in *next. The
 * texture part of TEX0. */
u64 func_00107140(u8 *data, u8 *picture, int x, int y, int w, int h, int tbp, int *next)
{
    int tw = func_00106980(w);
    int th = func_00106980(h);
    int psm = func_00106E90(picture);
    int blocks = func_00106AA0(psm, &w, &h);
    int tbw = func_001069C0(psm, w);

    func_001068F0(data, tbp, tbw, psm, x, y, *(u16 *)(picture + 0x14), *(u16 *)(picture + 0x16));
    if (next != 0)
        *next = tbp + blocks;
    return (u64)(long long)th << 30 | (u64)(long long)tw << 26 | (u64)(long long)psm << 20
           | (u64)(long long)tbp | (u64)(long long)tbw << 14 | 0x400000000;
}

/* 0x001072A0, 0x138 bytes. Loads a TIM2 file: its pixels to `tbp` (when below 0x4000 and the
 * picture has no mipmaps; the texture's size is the picture's when `w` or `h` is 0), its CLUTs to
 * `cbp` (when below 0x4000). The next free buffers in *next_tbp / *next_cbp; the TEX0 value
 * (0 for a file this code does not read). */
u64 func_001072A0(u8 *file, int x, int y, int w, int h, int tbp, int cbp, int *next_tbp,
                  int *next_cbp)
{
    u8 *picture;
    u64 tex, clut;

    if (func_00106E00(file) == 0)
        return 0;
    picture = file + 0x10;
    tex = 0;
    if (tbp < 0x4000 && file[0x21] == 1) {
        if (w == 0 || h == 0) {
            w = *(u16 *)(file + 0x24);
            h = *(u16 *)(file + 0x26);
        }
        tex = func_00107140(picture + *(u16 *)(file + 0x1C), picture, x, y, w, h, tbp, next_tbp);
    }
    clut = 0;
    if (cbp < 0x4000 && (file[0x22] & 0x3F) != 0)
        clut = func_00106F60(picture + *(u16 *)(file + 0x1C) + *(int *)(file + 0x18), picture, cbp,
                             next_cbp);
    return func_00106C50(tex, clut);
}

/* 0x001073E0, 0x38 bytes, matching. The same at (0, 0) with the picture's size. */
u64 func_001073E0(u8 *file, int tbp, int cbp, int *next_tbp, int *next_cbp)
{
    return func_001072A0(file, 0, 0, 0, 0, tbp, cbp, next_tbp, next_cbp);
}

/* 0x00107420, 0x20 bytes, matching. The same without the next buffers. */
u64 func_00107420(u8 *file, int x, int y, int w, int h, int tbp, int cbp)
{
    return func_001072A0(file, x, y, w, h, tbp, cbp, 0, 0);
}

/* 0x00107440, 0x38 bytes, matching. The same at (0, 0) with the picture's size, without the next
 * buffers. */
u64 func_00107440(u8 *file, int tbp, int cbp)
{
    return func_001072A0(file, 0, 0, 0, 0, tbp, cbp, 0, 0);
}

/* 0x00107480, 0xF8 bytes. The TEX0 value of a TIM2 file already loaded at `tbp` / `cbp`
 * (no CLUT when `cbp` is 0x4000 or more or the picture has none). */
u64 func_00107480(u8 *file, int tbp, int cbp)
{
    int psm, cpsm;

    if (func_00106E00(file) == 0 || file[0x21] != 1 || tbp > 0x3FFF)
        return 0;
    psm = func_00106E90(file + 0x10);
    if ((file[0x22] & 0x3F) == 0 || cbp > 0x3FFF) {
        cpsm = -1;
        cbp = -1;
    } else if ((file[0x22] & 0x3F) == 3) {
        cpsm = 0;
    } else if ((file[0x22] & 0x3F) == 1) {
        cpsm = 2;
    } else {
        cpsm = -1;
        cbp = -1;
    }
    return func_00106CD0(tbp, psm, cbp, cpsm, *(u16 *)(file + 0x24), *(u16 *)(file + 0x26));
}
