/*
 * motion_misc.c - small helpers just before MotionManager.c (0x0017C0D0-0x0017C49C; they may
 * belong to it): the camera shake and the weapon kinds' motion sets.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A shake (0x50 bytes) holds a timer and its length, then two (velocity, offset) pairs: +0x10 /
 * +0x20 (the eye's) and +0x30 / +0x40 (the target's).
 */

#define SW2E_FILE_MOTION_MISC_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned int u32;

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)(o) + (off)))->f##n)

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) PS2_LOADP(u8 *, ((u8 *)(o) + (off)))
#define PTR_SET(o, off, v) PS2_STOREP(u8 *, ((u8 *)(o) + (off)), v)

extern u8 g_005B5060[][0xD0];            /* the weapon kinds' records (motions at +0x18) */

void func_0017BE10(float *v);            /* a new random velocity? */

/* 0x0017C0D0, 0x4C bytes. Clears a shake. */
void func_0017C0D0(u32 *s)
{
    int k;

    s[0] = 0;
    s[1] = 0;
    for (k = 4; k < 0x14; k++)
        s[k] = 0;
}

/* 0x0017C120, 0x50 bytes. Starts a shake of `n` frames: new velocities, offsets at 0. */
void func_0017C120(u32 *s, u32 n)
{
    int k;

    s[0] = n;
    s[1] = n;
    func_0017BE10((float *)(s + 4));
    for (k = 0; k < 4; k++)
        s[8 + k] = 0;
    func_0017BE10((float *)(s + 0xC));
    for (k = 0; k < 4; k++)
        s[0x10 + k] = 0;
}

/* 0x0017C170, 0xC0 bytes. One step of a shake pair: the offset moves by the velocity (times
 * `k` and the strength `t`) and is damped by `t`; past 5 away (25 squared) a new velocity. */
void func_0017C170(float k, float t, float *v, float *p)
{
    int i;

    for (i = 0; i < 4; i++)
        p[i] = p[i] + v[i] * (k * t);
    for (i = 0; i < 4; i++)
        p[i] = p[i] * t;
    if (25.0f < p[0] * p[0] + p[1] * p[1] + p[2] * p[2])
        func_0017BE10(v);
}

/* 0x0017C230, 0xE8 bytes. A shake's frame: its strength is the time left over the length (at
 * most 1); both pairs stepped (k = 10); the timer runs down. */
void func_0017C230(u32 *s)
{
    float t = 1.0f;

    if ((float)s[0] / (float)s[1] <= 1.0f)
        t = (float)s[0] / (float)s[1];
    func_0017C170(10.0f, t, (float *)(s + 4), (float *)(s + 8));
    func_0017C170(10.0f, t, (float *)(s + 0xC), (float *)(s + 0x10));
    if (s[0] != 0)
        s[0] = s[0] - 1;
}

/* 0x0017C320, 0xC0 bytes. Opens a motion pack (a count, then offsets): `out` gets the pack, the
 * count and one 0x20-byte motion state per motion (its root at time 0); flag 1 at +0xC. */
int func_0017C320(u32 *pack, u32 *out)
{
    u8 *st;
    u32 k;

    out[0] = (u32)PS2_ADDR(pack);
    out[1] = pack[0];
    st = func_00102D30(pack[0] << 5);
    out[2] = (u32)PS2_ADDR(st);
    for (k = 0; k < out[1]; k++) {
        pack++;
        func_001477C0(st);
        func_001477E0((u32 *)PS2_PTR((out[0] + (*pack & ~3))), (u32 *)st);
        st += 0x20;
    }
    BIT(out, 0xC, 0) = 1;
    return 1;
}

/* 0x0017C3E0, 0xC0 bytes. Frees weapon kind `k`'s motion data (the mounted set +0x68 and +4
 * with flag 1 of +0x6C, +0x28 and +0x38 with theirs, +0x18, +0) and clears its record. */
void func_0017C3E0(int k)
{
    u8 *r = g_005B5060[k];

    func_00102EC0(PTR(r, 0x18));
    if (BIT(r, 0x6C, 0)) {
        func_00102EC0(PTR(r, 0x68));
        func_00102EC0(PTR(r, 4));
    }
    if (BIT(r, 0x2C, 0))
        func_00102EC0(PTR(r, 0x28));
    if (BIT(r, 0x3C, 0))
        func_00102EC0(PTR(r, 0x38));
    func_00102EC0(PTR(r, 0));
    func_001185E0(r, 0xD0, 0);
    func_0015FD70(r + 0x40);
}
