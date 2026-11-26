/*
 * font.c - loading the fonts (original source file font.c: its name is passed with the line
 * number to its reads; 0x00147580-0x00147778). The text drawing right before it
 * (text_draw.c) probably belongs to the same file.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Two fonts (0x004053C0, 0x30 bytes each) come from LINKDATA.BNS entries 1 and 2, TIM2 pictures
 * loaded into the GS memory once. Font 1's second texture is the same picture with the next
 * CLUT.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* A font (see text_draw.c). */
typedef struct {
    u64 tex0[2];             /* the second is -1 when there is one texture */
    u16 *cells;
    u32 count;
    u8 *widths;
    u32 pad;
    u16 cell_w, cell_h;
    u16 draw_w, draw_h;
    u16 columns, rows;
    u8 pad2[4];
} Font;

extern Font g_004053C0[2];

/* The text state (see text_draw.c). */
extern struct {
    void *custom;
    int colour[4];
    int outline;
    int style;
    int depth;
    float scale_x;
    float scale_y;
    u8 alpha[4];
    u8 line_h;
    u8 pad[2];
    u8 flags;
} g_0056CCA0;

u8 *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                  const char *file, int line);
u64 func_00107440(u8 *file, int tbp, int cbp);
u64 func_00106C90(u64 tex, int cbp);
void func_00102EC0(void *data);

/* 0x00147580, 0x100 bytes. Loads font `which` (0 or 1) into the GS memory. */
void func_00147580(int which)
{
    Font *f = &g_004053C0[which];
    u8 *file;

    if (which == 1) {
        file = func_001026D0(1, 2, 0, 1, 0, 0, "font.c", 0x3BB);
        f->tex0[0] = func_00107440(file, 0x38A0, 0x3EE0);
        f->tex0[1] = func_00106C90(f->tex0[0], 0x3EE1);
        func_00102EC0(file);
    } else if (which == 0) {
        file = func_001026D0(1, 1, 0, 1, 0, 0, "font.c", 0x3B5);
        f->tex0[0] = func_00107440(file, 0x3CA0, 0x3EE2);
        f->tex0[1] = (u64)-1;
        func_00102EC0(file);
    }
}

/* 0x00147680, 0xF0 bytes. Loads both fonts and sets the text state to its defaults: flat
 * style, colour 5, opaque (0x80), scale 16, lines 20 apart. */
void func_00147680(void)
{
    func_00147580(0);
    func_00147580(1);
    g_0056CCA0.custom = 0;
    g_0056CCA0.colour[0] = 5;
    g_0056CCA0.colour[1] = 5;
    g_0056CCA0.colour[2] = 5;
    g_0056CCA0.colour[3] = 5;
    g_0056CCA0.outline = 5;
    g_0056CCA0.alpha[0] = 0x80;
    g_0056CCA0.alpha[1] = 0x80;
    g_0056CCA0.alpha[2] = 0x80;
    g_0056CCA0.alpha[3] = 0x80;
    g_0056CCA0.style = 1;
    g_0056CCA0.depth = 0;
    g_0056CCA0.scale_x = 16.0f;
    g_0056CCA0.scale_y = 16.0f;
    g_0056CCA0.line_h = 0x14;
    g_0056CCA0.flags &= ~3;
}

/* 0x00147770, 0x8 bytes, matching. Nothing to do (the fonts stay loaded). */
void func_00147770(void)
{
}
