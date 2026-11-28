/*
 * stage_units.c - the stage's placed units (map objects with models: houses, fences, gates...):
 * their tables live in a block whose pointers sit in the scratchpad at 0x70000180-0x7000019F.
 * Original file name unknown (0x00207CC0-0x00208268, parts of 0x0020A710-0x0020BF4C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_STAGE_UNITS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The scratchpad block. */
#define SU_INFO PS2_GETP(u8 *, 0x70000180)       /* 0x10 bytes per unit */
#define SU_INFO_SET(v) PS2_SETP(0x70000180, v)
#define SU_A (*(u8 ***)PS2_PTR(0x70000184))         /* three model lists */
#define SU_B (*(u8 ***)PS2_PTR(0x70000188))
#define SU_C (*(u8 ***)PS2_PTR(0x7000018C))
#define SU_SHAPE (*(u8 ***)PS2_PTR(0x70000190))     /* each unit's shape record */
#define SU_DATA (*(u8 ***)PS2_PTR(0x70000194))      /* each unit's data */
#define SU_COUNT (*(u16 *)PS2_PTR(0x70000198))
#define g_700001A0 ((u8 *)PS2_PTR(0x700001A0))      /* the empty shape */
#define g_700001B0 ((u8 *)PS2_PTR(0x700001B0))      /* the shape of size 0x20 */

extern u8 g_00669D60[];

void func_001FEEC0(void);

/* 0x00207CC0, 0x20 bytes. Byte `k` of unit `i`'s info. */
u8 func_00207CC0(u32 i, int k)
{
    return SU_INFO[(i & 0xFFFF) * 0x10 + k];
}

/* 0x00207CE0, 0x1C bytes, matching. */
u8 *func_00207CE0(u32 i)
{
    return SU_A[i & 0xFFFF];
}

/* 0x00207D00, 0x1C bytes, matching. */
u8 *func_00207D00(u32 i)
{
    return SU_B[i & 0xFFFF];
}

/* 0x00207D20, 0x1C bytes, matching. */
u8 *func_00207D20(u32 i)
{
    return SU_C[i & 0xFFFF];
}

/* 0x00207D40, 0x20 bytes, matching. The 15 extra models after them. */
u8 *func_00207D40(int k)
{
    return SU_C[SU_COUNT + k];
}

/* 0x00207D60, 0x1C bytes, matching. */
u8 *func_00207D60(u32 i)
{
    return SU_DATA[i & 0xFFFF];
}

/* 0x00207D80, 0x20 bytes, matching. Unit `i`'s shape kind. */
u32 func_00207D80(u32 i)
{
    return *SU_SHAPE[i & 0xFFFF];
}

/* 0x00207DA0, 0x20 bytes, matching. */
u8 *func_00207DA0(u32 i)
{
    return SU_SHAPE[i & 0xFFFF] + 1;
}

/* 0x00207DC0, 0x30 bytes, matching. Unit `i`'s first model's box (+0x50). */
u8 *func_00207DC0(u32 i)
{
    u8 *m = func_00207CE0(i);

    return m == 0 ? 0 : m + 0x50;
}

/* 0x00207DF0, 0x94 bytes, matching. Moves model `m`'s box by its offset (+0x90, scaled by 100, y and z
 * negated). */
void func_00207DF0(u8 *m)
{
    float *b = (float *)(m + 0x50), *o = (float *)(m + 0x90);

    b[0] = o[0] * 100.0f + b[0] + 0.0f;
    b[1] = o[1] * -100.0f + b[1] + 0.0f;
    b[2] = o[2] * -100.0f + b[2] + 0.0f;
    b[4] = o[0] * 100.0f + b[4] + 0.0f;
    b[5] = o[1] * -100.0f + b[5] + 0.0f;
    b[6] = o[2] * -100.0f + b[6] + 0.0f;
}

/* 0x00207E90, 0x104 bytes. Places every unit's models (and the 15 extra ones). */
void func_00207E90(void)
{
    u32 k;

    for (k = 0; k < SU_COUNT; k++) {
        u8 *m;

        if ((m = func_00207CE0(k)) != 0) {
            func_00207DF0(m);
            func_001FEEC0();
        }
        if ((m = func_00207D00(k)) != 0) {
            func_00207DF0(m);
            func_001FEEC0();
        }
        if ((m = func_00207D20(k)) != 0) {
            func_00207DF0(m);
            func_001FEEC0();
        }
    }
    for (k = 0; k < 0xF; k++) {
        u8 *m = func_00207D40(k);

        if (m != 0) {
            func_00207DF0(m);
            func_001FEEC0();
        }
    }
}

/* 0x00207FA0, 0xC8 bytes. Finds each unit's shape and data in shape table `t` (sizes: 0 empty,
 * 0x20 the fixed one, else a record of that size). */
void func_00207FA0(u32 *t)
{
    u32 base = ((u32)PS2_ADDR(t) + t[0] * 4 + 0x13) & 0xFFFFFFF0, off = 0, k;
    u8 **shape = SU_SHAPE, **data = SU_DATA;

    g_700001A0[0] = 0;
    g_700001A0[1] = 4;
    g_700001B0[0] = 1;
    g_700001B0[1] = 4;
    for (k = 0; k < t[0]; k++) {
        u32 n = t[k + 1];

        if (n == 0) {
            shape[k] = g_700001A0;
            data[k] = 0;
        } else if (n == 0x20) {
            shape[k] = g_700001B0;
            data[k] = (u8 *)PS2_PTR((base + off));
        } else {
            shape[k] = (u8 *)PS2_PTR((base + off));
            data[k] = (u8 *)PS2_PTR((base + off + 0x10));
        }
        off += n;
    }
}

/* 0x00208070, 0x68 bytes. Turns a size table into pointers (the records follow it). */
void func_00208070(u32 *t)
{
    u32 n = t[0], off = 0, k;

    for (k = 0; k < t[0]; k++) {
        u32 s = t[k + 1];

        if (s != 0) {
            t[k + 1] = (((u32)PS2_ADDR(t) + n * 4 + 0x13) & 0xFFFFFFF0) + off;
            off += s;
        }
    }
}

/* 0x002080E0, 0x54 bytes, matching. Frees the shape and data lists. */
void func_002080E0(void)
{
    if (SU_DATA != 0) {
        func_00102EC0((void *)SU_DATA);
        SU_DATA = 0;
    }
    if (SU_SHAPE != 0) {
        func_00102EC0((void *)SU_SHAPE);
        SU_SHAPE = 0;
    }
}

/* 0x00208140, 0x12C bytes. Sets up the stage units from file `f` (its offsets made into
 * pointers) with info table `info`. */
void func_00208140(u8 *info, u32 *f)
{
    u32 *a, k;
    int size;

    func_00118850((void *)PS2_PTR(0x70000180), 0x40);
    for (k = 0; k < f[0]; k++)
        f[k + 1] += (u32)PS2_ADDR(f);
    a = (u32 *)PS2_PTR(f[1]);
    func_00208070(a);
    func_00208070((u32 *)PS2_PTR(f[2]));
    func_00208070((u32 *)PS2_PTR(f[3]));
    size = *(int *)(g_00669D60 + 0x58) == 2 ? 2000 : a[0] << 2;
    SU_INFO_SET(info);
    SU_A = (u8 **)(a + 1);
    SU_B = (u8 **)PS2_PTR((f[2] + 4));
    SU_C = (u8 **)PS2_PTR((f[3] + 4));
    SU_SHAPE = (u8 **)(func_00102D30(size));
    SU_DATA = (u8 **)(func_00102D30(size));
    SU_COUNT = a[0];
    func_00118850((void *)SU_SHAPE, size);
    func_00118850((void *)SU_DATA, size);
    func_00207E90();
    func_00207FA0((u32 *)PS2_PTR(f[4]));
}

/* The stage units' collision boxes (0x20 bytes each; parts of 0x0020A710-0x0020BF4C): a unit's
 * parts (+0x5C: the parts in place) each own func_00207D80 boxes of the kinds func_00207DA0
 * gives (0-3 a slope side, 4 and up flat). */

u8 *func_001FF140(u16 v);
u32 func_001FF100(u16 v, int k);
u8 *func_001FF230(u8 *part);
void func_00247530(u8 *u, u8 *a, int b, int c);
void func_0020A970(u8 *q, u8 *box, int side);
void func_0020AB00(u8 *q, u8 *box, int side);
void func_0020AD40(u8 *q, u8 *box);
u32 func_0020AEA0(u8 *q, u8 *box);
void func_0020AFF0(u8 *q, u8 *box);
void func_0020B110(u8 *q, u8 *box);
void func_0020B2B0(u8 *q, u8 *box);
void func_0020B410(u8 *q, u8 *box);

/* The slope side of box `j` of part `p` of unit `u`. */
#define BOX_SIDE(p, k, u) ((*(char *)((p) + 8) + (k) + *(char *)((u) + 0x5B)) & 3)

/* 0x0020A710, 0xD0 bytes. Actor `a` meets stage unit `u` (when it can break it). */
int func_0020A710(u8 *a, u8 *u)
{
    u8 v;

    if ((u[0x65] & 0x80) == 0)
        return 0;
    v = func_001FF100(*(u16 *)(u + 0x54), 0xC);
    if (v == 1)
        return 0;
    if (v >= 2 && func_001FF100(*(u16 *)(u + 0x54), 0xD) >= 2)
        return 0;
    if ((char)func_001FF100(*(u16 *)(u + 0x54), 0xB) == 2)
        return 0;
    func_00247530(u, a, 0, 1);
    return 1;
}

/* 0x0020B530, 0xCC bytes. Checks query `q` against part `p`'s slope boxes from `box`; past them. */
u8 *func_0020B530(u8 *q, u8 *box, u8 *u, u16 *p)
{
    u32 n = func_00207D80(*p), k;
    u8 *kinds = func_00207DA0(*p);

    for (k = 0; k < n; k++, box += 0x20)
        func_002E18C0(q, (float *)(box), BOX_SIDE((u8 *)p, (char)kinds[k], u));
    return box;
}

/* 0x0020B7A0, 0xEC bytes. The same with the slope or flat checks of another kind. */
u8 *func_0020B7A0(u8 *q, u8 *box, u8 *u, u16 *p)
{
    u32 n = func_00207D80(*p), k;
    u8 *kinds = func_00207DA0(*p);

    for (k = 0; k < n; k++, box += 0x20) {
        if (kinds[k] < 4)
            func_0020A970(q, box, BOX_SIDE((u8 *)p, kinds[k], u));
        else
            func_0020B110(q, box);
    }
    return box;
}

/* 0x0020B890, 0x60 bytes. Height checks of part `p`'s boxes. */
u8 *func_0020B890(u8 *q, u8 *box, u16 *p)
{
    u32 n = func_00207D80(*p), k;

    for (k = 0; k < n; k++, box += 0x20)
        func_0020AEA0(q, box);
    return box;
}

/* 0x0020B8F0, 0x70 bytes, matching. */
u8 *func_0020B8F0(u8 *q, u8 *box, u16 *p)
{
    u32 n = func_00207D80(*p), k;

    for (k = 0; k < n; k++, box += 0x20)
        func_0020AFF0(q, box);
    return box;
}

/* 0x0020B960, 0xEC bytes. */
u8 *func_0020B960(u8 *q, u8 *box, u8 *u, u16 *p)
{
    u32 n = func_00207D80(*p), k;
    u8 *kinds = func_00207DA0(*p);

    for (k = 0; k < n; k++, box += 0x20) {
        if (kinds[k] < 4)
            func_0020AB00(q, box, BOX_SIDE((u8 *)p, kinds[k], u));
        else
            func_0020B2B0(q, box);
    }
    return box;
}

/* 0x0020BA50, 0x70 bytes, matching. */
u8 *func_0020BA50(u8 *q, u8 *box, u16 *p)
{
    u32 n = func_00207D80(*p), k;

    for (k = 0; k < n; k++, box += 0x20)
        func_0020B410(q, box);
    return box;
}

/* 0x0020BD00, 0xE0 bytes. Checks query `q` against stage unit `u`'s parts in place. */
void func_0020BD00(u8 *q, u8 *box, u8 *u)
{
    u16 v = *(u16 *)(u + 0x54);
    u8 *d = func_001FF140(v), *p;
    u32 on = *(u32 *)(u + 0x5C), k;

    if ((char)func_001FF100(v, 1) == 0)
        return;
    p = d + 0x30;
    for (k = 0; k < *(u16 *)(d + 4); k++) {
        if ((on & 1 << k) != 0)
            box = (u8 *)PS2_PTR(func_0020BAC0(PS2_ADDR(q), PS2_ADDR(box), PS2_ADDR(u), PS2_ADDR(p)));
        p = func_001FF230(p);
    }
}

/* 0x0020BDE0, 0x16C bytes. The same with the climbing checks. */
void func_0020BDE0(u8 *q, u8 *box, u8 *u)
{
    u16 v = *(u16 *)(u + 0x54);
    u8 *d = func_001FF140(v), *p;
    u32 on = *(u32 *)(u + 0x5C), k;

    if ((char)func_001FF100(v, 5) == 0)
        return;
    p = d + 0x30;
    for (k = 0; k < *(u16 *)(d + 4); k++) {
        if ((on & 1 << k) != 0) {
            u32 n = func_00207D80(*(u16 *)p), j;
            u8 *kinds = func_00207DA0(*(u16 *)p);

            for (j = 0; j < n; j++, box += 0x20) {
                if (kinds[j] < 4)
                    func_0020AB00(q, box, BOX_SIDE(p, kinds[j], u));
                else
                    func_0020AD40(q, box);
            }
        }
        p = func_001FF230(p);
    }
}

/* Ground heights over the stage units (0x00209BB0-0x0020A04C; heights grow downward, so the
 * highest is the smallest). */

#define SU_BOXES PS2_GETP(float *, 0x700001D4)  /* (scratchpad) the collision boxes (8 floats each) */
#define SU_BOXES_SET(v) PS2_SETP(0x700001D4, v)
#define UNITS PS2_GETP(u8 *, 0x700001D0)        /* (scratchpad) the stage units (0x70 bytes each) */
#define UNITS_SET(v) PS2_SETP(0x700001D0, v)

/* Whether point `p` lies over box `b` (with a 0.1 margin). */
static int over_box(float *p, float *b)
{
    return p[0] < b[4] + 0.1f && p[2] < b[6] + 0.1f && b[0] - 0.1f < p[0] && b[2] - 0.1f < p[2];
}

/* 0x00209BB0, 0x250 bytes. The highest ground of stage unit `u`'s boxes at point `p` (0 when
 * over none). */
float func_00209BB0(u8 *u, float *p)
{
    u16 v = *(u16 *)(u + 0x54);
    u8 *d = func_001FF140(v), *part = d + 0x30;
    u32 on = *(u32 *)(u + 0x5C), kind = func_001FF100(v, 0), k;
    float *b = SU_BOXES + *(u16 *)(u + 0x56) * 8, h = 0.0f;

    for (k = 0; k < *(u16 *)(d + 4); k++) {
        if ((on & 1 << k) != 0) {
            u32 n = func_00207D80(*(u16 *)part), j;

            if (func_001FF290((short unsigned int *)(part), kind) == 1) {
                u8 *kinds = func_00207DA0(*(u16 *)part);

                for (j = 0; j < n; j++, b += 8) {
                    if (over_box(p, b)) {
                        float g = kinds[j] == 4 ? b[1]
                            : func_00209310(b, (part[8] + kinds[j] + u[0x5B]) & 3, p);

                        h = h < g ? h : g;
                    }
                }
            } else {
                b += n * 8;
            }
        }
        part = func_001FF230(part);
    }
    return h;
}

/* 0x00209E00, 0x24C bytes. The highest stage unit ground at point `p` (each unit once). */
float func_00209E00(float *p)
{
    u8 *seen = (u8 *)PS2_PTR(0x700001E0);
    u32 *c;
    float h = 0.0f;

    func_001185B0(seen, 0x50);
    for (c = (u32 *)PS2_PTR(func_001946A0(p, 1)); c != 0; c = (u32 *)PS2_PTR(c[1])) {
        u32 i = c[0], bit = 1 << (i & 7);
        u8 *u;
        int ok;
        float g;

        if ((bit & 0xFF & seen[i >> 3]) != 0)
            continue;
        seen[i >> 3] |= bit;
        u = UNITS + i * 0x70;
        if ((u[0x64] & 1) == 0)
            ok = 0;
        else if ((*(u32 *)(g_00669D60 + 0x200) & 0x100000) == 0
                 || (char)func_001FF100(*(u16 *)(u + 0x54), 4) != 1)
            ok = (u[0x69] & 4) == 0;
        else
            ok = 0;
        if (!ok)
            continue;
        if ((u[0x64] & 4) == 0) {
            g = func_00209BB0(u, p);
        } else {
            float *b = SU_BOXES + *(u16 *)(u + 0x56) * 8;

            g = over_box(p, b) ? b[1] : 0.0f;
        }
        h = h < g ? h : g;
    }
    return h;
}
