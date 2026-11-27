/*
 * weapon.c - weapons held by battlefield units (original source file Weapon.c: its name is passed
 * to the file loader at 0x0016CD30).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
 *
 * Two tables come from LINKDATA_BNS: entry 0x56B, per unit kind 0x20 bytes (two sets of four
 * (motion, node) pairs from +3, then their modes at +0x13 / +0x15), and entry 0x56C, 0x30-byte
 * weapon records. 160 weapon objects of 0xB0 bytes live at 0x0056DC00; a flag per kind at
 * 0x00574A00 says whether its motions are loaded.
 *
 * Unlike most of the game, this file was built with CodeWarrior's loop unroller on (its clearing
 * loops are unrolled by 8), hence the pragma below.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

typedef u8 Unit;

#pragma opt_unroll_loops on

float fabsf(float x);
float sqrtf(float x);

extern u8 *g_0045D294;                   /* (small data) the kinds' slot table (entry 0x56B) */
extern u8 *g_0045D298;                   /* (small data) the weapon records (entry 0x56C) */
extern u32 g_0045D29C;                   /* (small data) their count */
extern int g_0045D898;                   /* (small data) the current scene */
extern u8 g_0056DC00[0xA0][0xB0];        /* the weapon objects */
extern u8 g_00574A00[0x8D];              /* per kind: motions loaded */
extern const char g_00424BB8[];          /* "Weapon.c" */

u32 func_00102680(int which, int entry);
void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const void *file, int line);
void func_00102EC0(void *data);
void func_001185E0(void *p, int size, int value);  /* memset */
int func_001BD9B0(u8 motion, void *a);
int func_001BDDB0(char motion, void *a);
int func_001BDAE0(char motion, void *a, void *b);
void func_0016D160(u8 *w);

/* 0x0016CD30, 0x150 bytes. Loads the two weapon tables and clears the weapon objects and the
 * loaded flags. */
void func_0016CD30(void)
{
    int k;

    func_00102680(1, 0x56B);
    g_0045D294 = func_001026D0(1, 0x56B, 0, 1, 0, 0, g_00424BB8, 0x61);
    g_0045D29C = func_00102680(1, 0x56C) / 0x30;
    g_0045D298 = func_001026D0(1, 0x56C, 0, 1, 0, 0, g_00424BB8, 0x68);
    for (k = 0; k < 0xA0; k++)
        func_0016D160(g_0056DC00[k]);
    for (k = 0; k < 0x8D; k++)
        g_00574A00[k] = 0;
}

/* 0x0016CE80, 0x30 bytes, matching. Frees the two weapon tables. */
void func_0016CE80(void)
{
    func_00102EC0(g_0045D294);
    g_0045D294 = 0;
    func_00102EC0(g_0045D298);
    g_0045D298 = 0;
    g_0045D29C = 0;
}

/* 0x0016CEB0, 0x80 bytes, matching. Clears the loaded flags. */
void func_0016CEB0(void)
{
    int k;

    for (k = 0; k < 0x8D; k++)
        g_00574A00[k] = 0;
}

/* 0x0016CF30, 0x10 bytes, matching. The slot record of unit kind `k`. */
u8 *func_0016CF30(int k)
{
    return g_0045D294 + k * 0x20;
}

/* 0x0016CF40, 0x70 bytes, matching. Weapon record `k` (0xCE-0xD5 map to 0x8B-0x92); 0 past the end. */
u8 *func_0016CF40(u32 k)
{
    if ((int)k >= 0xCE && (int)k <= 0xD1)
        k = k - 0x43;
    else if ((int)k >= 0xD2 && (int)k < 0xD6)
        k = k - 0x43;
    if (k < g_0045D29C)
        return g_0045D298 + k * 0x30;
    return 0;
}

/* 0x0016CFB0, 0xA4 bytes. Whether all the slot motions of kind `k` are ready (func_001BD9B0). */
int func_0016CFB0(int k, void *a)
{
    u8 *r = func_0016CF30(k);
    int s, i;

    for (s = 0; s < 2; s++, r += 8) {
        for (i = 0; i < 4; i++) {
            u8 m = r[3 + i * 2];

            if (m != 0xFF && func_001BD9B0(m, a) == 0)
                return 0;
        }
    }
    return 1;
}

/* 0x0016D060, 0xFC bytes. Loads the slot motions of kind `k` (by func_001BDDB0 in scene 0x14,
 * the officer editor); marks the kind loaded. Whether all loaded. */
int func_0016D060(int k, void *a, void *b)
{
    u8 *r = func_0016CF30(k);
    int s, i;

    for (s = 0; s < 2; s++, r += 8) {
        for (i = 0; i < 4; i++) {
            char m = r[3 + i * 2];

            if (m != -1) {
                if (g_0045D898 == 0x14) {
                    if (func_001BDDB0(m, a) == 0)
                        return 0;
                } else if (func_001BDAE0(m, a, b) == 0) {
                    return 0;
                }
            }
        }
    }
    g_00574A00[k] = 1;
    return 1;
}

/* 0x0016D160, 0x20 bytes, matching. Clears a weapon object. */
void func_0016D160(u8 *w)
{
    func_001185E0(w, 0xB0, 0);
}

/* 0x0016D180, 0x98 bytes. Sets a weapon part's edge from six floats: its base (+0, w 1), its
 * direction (+0x10), the current (+0x20, +0x30) and previous (+0x40, +0x50) ends; +0x64 = 1. */
void func_0016D180(u8 *e, const float *p)
{
    float t[4];
    int k;

    F32(e, 0) = p[0];
    F32(e, 4) = p[1];
    F32(e, 8) = p[2];
    F32(e, 0xC) = 1.0f;
    F32(e, 0x10) = p[3];
    F32(e, 0x14) = p[4];
    F32(e, 0x18) = p[5];
    F32(e, 0x1C) = 0.0f;
    for (k = 0; k < 4; k++)
        t[k] = F32(e, 0x10 + k * 4) + F32(e, k * 4);
    for (k = 0; k < 4; k++) {
        F32(e, 0x20 + k * 4) = F32(e, k * 4);
        F32(e, 0x40 + k * 4) = F32(e, k * 4);
    }
    for (k = 0; k < 4; k++) {
        F32(e, 0x30 + k * 4) = t[k];
        F32(e, 0x50 + k * 4) = t[k];
    }
    F32(e, 0x64) = 1.0f;
}
