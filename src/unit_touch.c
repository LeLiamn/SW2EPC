/*
 * unit_touch.c - units running into each other (original source file unknown; from 0x00171FA8,
 * right after Sony's pad library, which ends at 0x00171FA4).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
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

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)(o) + (off)))->f##n)

float sqrtf(float x);
void vu0_sincos(float a, float *s, float *c);     /* VU0 micro subroutine 0x20 */

extern int g_0040669C[4];                /* +0: a setting in 0x4123-0x1046B (or 0) */

int func_0016B9B0(Unit *u, Unit *v, u8 *hit, u8 alpha);
int func_0016AA60(Unit *u, Unit *v, u8 *hit, void *pos, short *damage, u8 alpha);
u8 *func_003DD3C0(u8 horse);
void func_0029F790(Unit *u, Unit *v, u8 *hit, u8 alpha);

/* 0x00171FA8, 0x34 bytes. Sets g_0040669C to `v` (0, or 0x4123-0x1046B); whether it was
 * accepted. */
int func_00171FA8(int v)
{
    if (0xC348 < (u32)(v - 0x4123)) {
        if (v != 0)
            return 0;
    }
    g_0040669C[0] = v;
    return 1;
}

/* Whether a unit cannot be run into: actions with flags 0x100000, 0x20, 0x40 or 0x8000000, or
 * flag 8 of +0x19F (already pushed this frame). */
static inline int no_touch(Unit *v)
{
    u32 f = U32(PTR(v, 0x210), 0x18);

    return (f & 0x100000) || (f & 0x20) || (f & 0x40) || (f & 0x8000000) || (U8(v, 0x19F) & 8);
}

/* `v` takes the touch `hit` from `u` at u's point; pushed (flag 8 of +0x19F) by its offset. */
static inline void touch(Unit *v, Unit *u, u8 *hit, float *pos, u8 alpha)
{
    short d;
    int k;

    func_0016AA60(v, u, hit, pos, &d, alpha);
    BIT(v, 0x19F, 3) = 1;
    for (k = 0; k < 4; k++)
        F32(v, 0x80 + k * 4) = F32(v, 0x90 + k * 4) - F32(v, 0x40 + k * 4);
}

/* 0x00171FE0, 0x190 bytes. Unit `u` runs into `v` of its own side (+0x154): a push, unless
 * `v` cannot be touched, or `u` has flag 0x20 of +0x19C and `v` not. Whether it pushed. */
int func_00171FE0(Unit *u, Unit *v, u8 *hit)
{
    float p[4];
    int k;

    if (no_touch(v))
        return 0;
    if (U8(u, 0x154) != U8(v, 0x154))
        return 0;
    if (func_0016B9B0(v, u, hit, 0xFF) != 0)
        return 0;
    if (BIT(u, 0x19C, 5) && BIT(v, 0x19C, 5) == 0)
        return 0;
    for (k = 0; k < 4; k++)
        p[k] = F32(u, 0x90 + k * 4);
    touch(v, u, hit, p, 0xFF);
    return 1;
}

/* 0x00172170, 0x10C bytes. Unit `u` runs into an enemy `v` (a horse's rider takes it; nothing
 * for an empty horse). Whether it hit. */
int func_00172170(Unit *u, Unit *v, u8 *hit)
{
    float p[4];
    int k;

    if (U32(PTR(v, 0x210), 0x18) & 0x40)
        return 0;
    if (U8(u, 0x154) == U8(v, 0x154))
        return 0;
    if (func_0016B9B0(v, u, hit, 0xFF) != 0)
        return 0;
    if (S32(v, 0x118) == 0x3C) {
        v = PTR(v, 0x28C);
        if (v == 0)
            return 0;
    }
    for (k = 0; k < 4; k++)
        p[k] = F32(u, 0x90 + k * 4);
    touch(v, u, hit, p, 0xFF);
    return 1;
}

/* 0x00172280, 0x1C8 bytes. Horse `h` runs into `v` (on behalf of its rider): units of its own
 * side and weaker ones (level +0x1BA up to the horse's +0x1A) are knocked over, with func_0029F790;
 * returns 1 when a stronger enemy stops the horse. */
int func_00172280(Unit *h, Unit *v, u8 *hit)
{
    u8 *r, alpha = U8(h, 0x14E) + 0x40;
    short d;
    float p[4];
    int k;

    if (no_touch(v))
        return 0;
    r = PTR(h, 0x28C);
    if (r == 0)
        return 0;
    if (U8(r, 0x154) == U8(v, 0x154))
        return 0;
    if (func_0016B9B0(v, r, hit, alpha) != 0)
        return 0;
    if (U8(v, 0x154) == U8(h, 0x154)
        || S16(func_003DD3C0(U8(h, 0x180)), 0x1A) <= (short)(u16)U8(v, 0x1BA)) {
        for (k = 0; k < 4; k++)
            p[k] = F32(h, 0x90 + k * 4);
        func_0016AA60(v, r, hit, p, &d, alpha);
        func_0029F790(v, r, hit, alpha);
        BIT(v, 0x19F, 3) = 1;
        for (k = 0; k < 4; k++)
            F32(v, 0x80 + k * 4) = F32(v, 0x90 + k * 4) - F32(v, 0x40 + k * 4);
        return 0;
    }
    return 1;
}

/* 0x00172450, 0x64 bytes. A horse's reach at angle `a`: an ellipse 45 wide and 140 long. */
float func_00172450(float a)
{
    float s, c;

    vu0_sincos(a, &s, &c);
    return sqrtf(s * 45.0f * (s * 45.0f) + c * 140.0f * (c * 140.0f));
}
