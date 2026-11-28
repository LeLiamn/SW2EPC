/*
 * bullet.c - projectiles (original source file Bullet.c: its name is passed to the file loader at
 * 0x001AE4F0, which loads LINKDATA entry 0x56E, the projectile kinds).
 * Written so far: the simpler functions of 0x001AC980-0x001AE548; the set-up (0x001ACA70), the
 * per-frame update (0x001AD0F0) and two VU0 helpers (0x001AE230, 0x001AE3D0) are left.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A projectile (0xC0 bytes): +0x00 its point, +0x10 its direction, +0x30 / +0x40 its points now
 * and before, +0x50 a random direction, +0x70 its kind (0x48-byte records of the kinds file,
 * +0x30 flags, +0x35 how it moves, +0x36 / +0x38 / +0x39 / +0x3A ... speeds and sizes, +0x45 its
 * effect), +0x88 the unit that shot it, +0x8C flags, +0x96 its side (3: none), +0xA0 its model.
 */

#define SW2E_FILE_BULLET_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 *g_0045D2FC;                   /* (small data) the projectile kinds' file */
extern const char g_00425D50[];          /* "Bullet.c" */

void func_001ACA70(u8 *b, u8 *kind, float *pos, float *dir, u8 *unit);
void func_0024F6B0(u32 a, u32 b, u32 c);
void func_002A6910(u32 h, int a, u8 *p);

/* 0x001AC980, 0xE4 bytes. Sets projectile `b` of kind `kind` up from `pos` along `dir`; one shot
 * by `unit` starts at the unit, set back along its facing by the kind's offset (+0x3A) when that
 * reaches past the unit's model (+0x114, its radius +0x88), unless it follows the unit. */
void func_001AC980(u8 *b, u8 *kind, float *pos, float *dir, u8 *unit)
{
    func_001ACA70(b, kind, pos, dir, unit);
    if (unit != 0) {
        float r = *(float *)(*(u8 **)(unit + 0x114) + 0x88);
        float d = *(float *)(b + 0x78);
        int k;

        for (k = 0; k < 4; k++)
            ((float *)(b + 0x40))[k] = ((float *)(unit + 0x90))[k];
        if (kind != 0 && kind[0x35] != 1 && (d = d + (float)kind[0x3A] - r) > 0.0f) {
            float s = (d + r) * -1.0f;

            for (k = 0; k < 4; k++)
                ((float *)(b + 0x40))[k] += ((float *)(unit + 0x70))[k] * s;
        }
    }
}

/* 0x001AD090, 0x54 bytes. Stops projectile `b`'s effect (when its kind has one). */
void func_001AD090(u8 *b)
{
    u8 *kind = *(u8 **)(b + 0x70);

    if (kind != 0 && (signed char)kind[0x45] != -1) {
        func_0024F6B0(*(u32 *)(b + 0x98), *(u32 *)(b + 0x9C), *(u32 *)(b + 0xB8));
        *(u32 *)(b + 0x98) = 0;
        *(u32 *)(b + 0x9C) = 0;
        *(u32 *)(b + 0xB8) = 0;
    }
}

void func_001AE1A0(u8 *b);

/* 0x001AE090, 0x10C bytes. Ends projectile `b`: tells its unit, an effect for kinds with flag
 * 0x2000000, frees its model and effect, clears it. */
void func_001AE090(u8 *b)
{
    u8 f;

    if (*(u8 **)(b + 0x88) != 0)
        func_0016BFD0(*(u8 **)(b + 0x88), b);
    if (*(u8 **)(b + 0x70) != 0 && (*(u32 *)(*(u8 **)(b + 0x70) + 0x30) & 0x2000000))
        func_0024D070(5, (unsigned int *)(b + 0x30));
    func_001AE1A0(b);
    func_001AD090(b);
    *(u8 **)(b + 0x70) = 0;
    *(u8 **)(b + 0x88) = 0;
    f = b[0x8C];
    b[0x8C] = f & 0xFE;     /* (four writes of the same byte in the original) */
    b[0x8C] = f & 0xFC;
    b[0x8C] = f & 0xF8;
    b[0x8C] = f & 0xF0;
    *(u32 *)(b + 0x90) = 0;
    *(u32 *)(b + 0xA4) = 0;
    *(u16 *)(b + 0x96) = 3;
    *(u32 *)(b + 0xB0) = 0;
    *(u32 *)(b + 0xB4) = 0;
    *(u32 *)(b + 0xAC) = 0;
    *(u32 *)(b + 0xA0) = 0;
    *(u32 *)(b + 0x98) = 0;
    *(u32 *)(b + 0x9C) = 0;
    *(u32 *)(b + 0xB8) = 0;
}

/* 0x001AE1A0, 0x30 bytes. Lets projectile `b`'s model go. */
void func_001AE1A0(u8 *b)
{
    u8 *m = *(u8 **)(b + 0xA0);

    if (m != 0) {
        m[0x168] &= 0xFE;
        *(u8 **)(b + 0xA0) = 0;
    }
}

/* 0x001AE1D0, 0x54 bytes, matching. Plays kind `kind`'s sound (+0x1A) at projectile `b`. */
void func_001AE1D0(u8 *b, u8 *kind)
{
    u32 h;

    if (kind != 0 && kind[0x1A] != 0 && kind[0x1A] != 0xFF) {
        func_0015E890((int *)&h, kind[0x1A]);
        func_002A6910(h, 0, b + 0x30);
    }
}

/* 0x001AE4F0, 0x40 bytes, matching. Loads the projectile kinds (LINKDATA entry 0x56E). */
void func_001AE4F0(void)
{
    g_0045D2FC = func_001026D0(1, 0x56E, 0, 1, 0, 0, g_00425D50, 0x2DF);
}

/* 0x001AE530, 0x20 bytes, matching. Frees them. */
void func_001AE530(void)
{
    func_00102EC0(g_0045D2FC);
    g_0045D2FC = 0;
}
