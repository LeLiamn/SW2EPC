/*
 * sw2e_draw.h - shared prototypes of the 2D drawing helpers called from many files, with their
 * full argument lists (defined in cmnparts.c and ui_parts.c). Ghidra drops the arguments passed
 * on the stack (the ninth and later), so the local prototypes once copied from it were too short.
 *
 * Include it after the u8/u16/u32 typedefs.
 */

#ifndef SW2E_DRAW_H
#define SW2E_DRAW_H

/* 0x001ABA70 (cmnparts.c): the whole image `img`. */
void func_001ABA70(u8 *img, int x, int y, int z, int w, int h, int alpha, int layer, int centred);

/* 0x001ABE40 (cmnparts.c): the whole image `i` of pack `f`. */
void func_001ABE40(u8 *f, int i, int x, int y, int z, int w, int h, int alpha, int layer,
                   int centred);

/* 0x001ABEA0 (cmnparts.c): part (u, v, uw, vh) of image `i` of pack `f`. */
void func_001ABEA0(u8 *f, int i, int x, int y, int z, int w, int h, int u, int v, int uw, int vh,
                   int alpha, int layer, int centred);

/* 0x001ABB00 (cmnparts.c): image `i` of pack `f` with the palette of image `j`. */
void func_001ABB00(u8 *f, int i, int j, int x, int y, int z, int w, int h, int u, int v, int uw,
                   int vh, const u32 *rgba, int layer, int centred);

/* 0x001A85D0 (ui_parts.c): a gauge. Floats travel in the float registers, so only their order
 * among themselves matters. */
void func_001A85D0(float a, float b, float size, int x, int y, int z, int ia, int ib, int w,
                   int layer);

/* 0x001A3460 (ui_parts.c): a scroll bar on layer `layer`. */
void func_001A3460(int x, int y, int z, int unused, int h, int alpha, int total, int shown,
                   int first, int layer);

/* An argument whose value has not been identified yet: the original computes it in a way the
 * argument fixer could not follow. Find them with `grep -n ARG_UNKNOWN src/*.c` and read the call
 * site in the disassembly. */
#define ARG_UNKNOWN 0

#endif
