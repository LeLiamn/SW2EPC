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

/* The squared distance between two points, as the original's VU0 code sums it (by the weights
 * in vf31, taken here as the first two components?). */
static inline float dist2(const float *a, const float *b)
{
    float x = b[0] - a[0], y = b[1] - a[1];

    return x * x + y * y;
}

/* m (four rows of four) times v, into out. */
static inline void mat_vec(float *out, const float *m, const float *v)
{
    float t[4];
    int k;

    for (k = 0; k < 4; k++)
        t[k] = m[k] * v[0] + m[4 + k] * v[1] + m[8 + k] * v[2] + m[12 + k] * v[3];
    for (k = 0; k < 4; k++)
        out[k] = t[k];
}

/* 0x0016D220, 0x1C4 bytes. Moves a weapon edge with matrix `m` (kept at +0x70): the previous
 * ends (+0x40, +0x50) kept; the base (+0) and its end (along x: the length +0x10 lengthened by
 * `grow`, times `scale` plus `add`, times `k`) placed into +0x20 / +0x30; `scale` kept at +0x64.
 * The divide by w of the second point is tested with the first point's w, as in the original. */
float func_0016D220(float grow, float scale, float add, float k, float *e, const float *m)
{
    float len, x, y, z, w = 0.0f;
    int i;

    for (i = 0; i < 8; i++)
        e[0x10 + i] = e[8 + i];
    for (i = 0; i < 16; i++)
        e[0x1C + i] = m[i];
    e[0x19] = scale;
    if (e[3] != 1.0f)
        e[3] = 1.0f;
    len = e[4] < 0.0f ? e[4] - grow : e[4] + grow;
    x = e[0];
    y = e[1];
    z = e[2];
    for (i = 0; i < 4; i++)
        e[8 + i] = e[i];
    mat_vec(&e[8], &e[0x1C], &e[8]);
    if (e[0xB] != 0.0f) {
        float q = 1.0f / e[0xB];

        for (i = 0; i < 4; i++)
            e[8 + i] = e[8 + i] * q;
    }
    e[0xC] = x + (len * scale + add) * k;
    e[0xD] = y + e[5];
    e[0xE] = z + e[6];
    e[0xF] = 1.0f;
    mat_vec(&e[0xC], &e[0x1C], &e[0xC]);
    if (e[0xB] != 0.0f) {
        float q;

        w = e[0xF];
        q = 1.0f / w;
        for (i = 0; i < 4; i++)
            e[0xC + i] = e[0xC + i] * q;
    }
    return w;
}

/* 0x0016D3F0, 0x18C bytes. Whether a circle of radius `r` at `p` touches the segment a-b. */
int func_0016D3F0(float r, const float *p, const float *a, const float *b)
{
    float r2 = r * r, dx, dy, t, q[4];

    if (!(r2 < dist2(p, a)) || !(r2 < dist2(p, b)))
        return 1;
    dy = b[1] - a[1];
    dx = b[0] - a[0];
    t = (dx * (p[0] - a[0]) + dy * (p[1] - a[1])) / (dx * dx + dy * dy);
    if (t < 0.0f)
        return 0;
    if (1.0f < t)
        return 0;
    q[0] = dx * t + a[0] + 0.0f;
    q[1] = dy * t + a[1] + 0.0f;
    if (r2 < dist2(p, q))
        return 0;
    return 1;
}

/* 0x0016D580, 0x200 bytes. Whether the segment a-b crosses the rectangle (x, y, width,
 * height). */
int func_0016D580(const float *rc, const float *a, const float *b)
{
    float ax = a[0], bx = b[0], ay = a[1], by = b[1];
    float x0 = rc[0], x1 = rc[0] + rc[2], y0 = rc[1], y1 = rc[1] + rc[3];

    if (!(x0 <= (bx < ax ? ax : bx)))
        return 0;
    if (!((bx < ax ? bx : ax) <= x1))
        return 0;
    if (!(y0 <= (by < ay ? ay : by)))
        return 0;
    if (!((by < ay ? by : ay) <= y1))
        return 0;
    if ((x0 <= ax && ax <= x1 && y0 <= ay && ay <= y1)
        || (x0 <= bx && bx <= x1 && y0 <= by && by <= y1))
        return 1;
    if (by - ay == 0.0f)
        return y0 <= ay && ay <= y1;
    if (bx - ax == 0.0f)
        return x0 <= ax && ax <= x1;
    {
        float s = (by - ay) / (bx - ax);
        float c = (ay + 0.0f) - ax * s;
        float v0 = s * x0 + c + 0.0f, v1 = s * x1 + c + 0.0f;

        if (!(y0 <= (v1 < v0 ? v0 : v1)))
            return 0;
        return (v0 <= v1 ? v0 : v1) <= y1;
    }
}

extern float g_0056DBE0[6];              /* the edge of kinds 0x14-0x1B and 0x30-0x37 */
extern u8 g_006C3590[][0x30];            /* the weapon models */

u8 *func_001BE5E0(void);
u8 *func_001BE630(void);
void func_0014FCA0(u8 *o, u8 *model);
void func_00149620(u8 *a, u8 *m, u8 *m2);
void func_0016E910(u8 *slot);
void func_0016E860(u8 *slot);
void func_002088C0(u8 *trail);

/* 0x0016E2E0, 0x20 bytes, matching. Clears a weapon slot. */
void func_0016E2E0(u8 *slot)
{
    func_001185E0(slot, 0x70, 0);
}

/* A free weapon object (flag 1 of +0x60 clear), taken and reset; 0 when all are in use. */
static inline u8 *take_weapon(void)
{
    u8 *w = g_0056DC00[0];
    int k;

    for (k = 0; k < 0xA0; k++, w += 0xB0) {
        if ((U8(w, 0x60) & 1) == 0)
            return w;
    }
    return 0;
}

/* Marks a weapon object used and not drawn. */
static inline void weapon_use(u8 *w)
{
    U8(w, 0x60) = (U8(w, 0x60) & ~1) | 1;
    U8(w, 0x60) &= ~2;
    U8(w, 0x60) &= ~4;
}

/* 0x0016E300, 0x554 bytes. Gives a slot weapon `kind` on node `node`: its parts (one or, with
 * `pair`, two edges from the weapon record; extra edges for kinds 0x3C-0x3F, 0x64-0x6F; the
 * shared edge for kinds 0x14-0x1B and 0x30-0x37), unless `no_parts`; its object (a plain one
 * with the kind's model, or with `actor` a model actor); flags +0x4C (1 on, 4 actor, 8 pair,
 * 0x10 no parts). Whether it worked. */
int func_0016E300(u8 *slot, int kind, u8 node, int actor, int pair, int no_parts)
{
    int n = pair == 0 ? 1 : 2, i, k;
    u8 *o, b;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            F32(slot, i * 0x10 + k * 4) = i == k ? 1.0f : 0.0f;
    U8(slot, 0x48) = (u8)kind;
    U8(slot, 0x49) = node;
    if (no_parts == 0) {
        const float *rec = (const float *)func_0016CF40(U8(slot, 0x48));
        u32 c;

        for (i = 0; i < n; i++, rec += 6) {
            u8 *w = take_weapon();

            PTR(slot, 0x50 + i * 4) = w;
            weapon_use(w);
            func_0016D180(PTR(slot, 0x50 + i * 4), rec);
        }
        c = U8(slot, 0x48);
        if ((u32)(c - 0x3C) < 4 || (u32)(c - 0x6C) < 4 || c - 100 < 4 || c - 0x68 < 4) {
            if (c - 0x3C < 4 || c - 0x6C < 4 || c - 100 < 4)
                n = 2;
            else if (c - 0x68 < 4)
                n = 1;
            else
                n = 0;
            for (i = 0; i < n; i++, rec += 6) {
                u8 *w = take_weapon();

                PTR(slot, 0x58 + i * 4) = w;
                weapon_use(w);
                func_0016D180(PTR(slot, 0x58 + i * 4), rec);
            }
        }
        if ((u32)(U8(slot, 0x48) - 0x30) < 8 || (u32)(U8(slot, 0x48) - 0x14) < 8) {
            u8 *w = take_weapon();

            PTR(slot, 0x58) = w;
            weapon_use(w);
            func_0016D180(PTR(slot, 0x58), g_0056DBE0);
        }
    }
    if (actor == 0) {
        o = func_001BE5E0();
        PTR(slot, 0x44) = o;
        if (o == 0) {
            func_0016E910(slot);
            return 0;
        }
        U8(o, 0x168) = (U8(o, 0x168) & ~1) | 1;
        func_0014FCA0(o, g_006C3590[kind]);
        U8(o, 0x165) = U8(slot, 0x49);
    } else {
        o = func_001BE630();
        PTR(slot, 0x44) = o;
        if (o == 0) {
            func_0016E910(slot);
            return 0;
        }
        U8(o, 0x20C) = (U8(o, 0x20C) & ~1) | 1;
        func_00149620(PTR(slot, 0x44), g_006C3590[kind], 0);
    }
    b = U8(slot, 0x4C);
    U8(slot, 0x4C) = (b & 0x60) | 1 | (actor & 1) << 2 | (pair & 1) << 3 | (no_parts & 1) << 4;
    U8(slot, 0x4D) &= ~1;
    return 1;
}

/* 0x0016E860, 0xB0 bytes. Stops the trails of a weapon's parts. */
void func_0016E860(u8 *slot)
{
    u32 i;

    for (i = 0; i < 2; i++) {
        u8 *p = PTR(slot, 0x50 + i * 4);

        if (p != 0 && PTR(p, 0x68) != 0) {
            func_002088C0(PTR(p, 0x68));
            PTR(PTR(slot, 0x50 + i * 4), 0x68) = 0;
        }
    }
    for (i = 0; i < 2; i++) {
        u8 *p = PTR(slot, 0x58 + i * 4);

        if (p != 0 && PTR(p, 0x68) != 0) {
            func_002088C0(PTR(p, 0x68));
            PTR(PTR(slot, 0x58 + i * 4), 0x68) = 0;
        }
    }
}

void func_00208980(u8 *trail, void *m, int colour);

/* Frees a weapon object (flags 1, 2, 4 of +0x60). */
static inline void weapon_free(u8 *w)
{
    U8(w, 0x60) &= ~1;
    U8(w, 0x60) &= ~2;
    U8(w, 0x60) &= ~4;
}

/* 0x0016E910, 0x198 bytes. Empties a weapon slot: its object released, its trails stopped
 * (flag 1 of +0x4D), its parts freed, the slot cleared. */
void func_0016E910(u8 *slot)
{
    u8 *o = PTR(slot, 0x44);
    u32 i;

    if (o != 0) {
        if (U8(slot, 0x4C) & 4) {
            PTR(o, 0x1E8) = 0;
            U8(PTR(slot, 0x44), 0x20C) &= ~1;
        } else {
            PTR(o, 0x160) = 0;
            U8(PTR(slot, 0x44), 0x168) &= ~1;
        }
    }
    PTR(slot, 0x44) = 0;
    if (U8(slot, 0x4D) & 1)
        func_0016E860(slot);
    for (i = 0; i < 2; i++) {
        if (PTR(slot, 0x50 + i * 4) != 0)
            weapon_free(PTR(slot, 0x50 + i * 4));
    }
    for (i = 0; i < 2; i++) {
        if (PTR(slot, 0x58 + i * 4) != 0)
            weapon_free(PTR(slot, 0x58 + i * 4));
    }
    func_0016E2E0(slot);
}

/* 0x0016EAB0, 0x68 bytes. Starts a part's trail (+0x68) on its edge: from the base to the base
 * plus the length (lengthened by `grow`) times the scale +0x64. */
void func_0016EAB0(float grow, float *e)
{
    u8 *t = *(u8 **)&e[0x1A];
    float *s = (float *)0x70000030, len;
    int k;

    for (k = 0; k < 4; k++) {
        F32(t, 0x20 + k * 4) = s[k];
        F32(t, 0x30 + k * 4) = s[k];
    }
    len = e[4] < 0.0f ? e[4] - grow : e[4] + grow;
    F32(t, 0x20) = e[0] + len * e[0x19];
    F32(t, 0x30) = e[0];
}

/* 0x0016EB20, 0x6C bytes. The same without the scale, when the part has a trail. */
void func_0016EB20(float grow, float *e)
{
    u8 *t = *(u8 **)&e[0x1A];
    float *s = (float *)0x70000030, len;
    int k;

    if (t == 0)
        return;
    for (k = 0; k < 4; k++) {
        F32(t, 0x20 + k * 4) = s[k];
        F32(t, 0x30 + k * 4) = s[k];
    }
    len = e[4] < 0.0f ? e[4] - grow : e[4] + grow;
    F32(t, 0x20) = e[0] + len;
    F32(t, 0x30) = e[0];
}

/* 0x0016EB90, 0x20 bytes, matching. Sets a trail's matrix and colour, if there is one. */
void func_0016EB90(u8 *trail, void *m, int colour)
{
    if (trail != 0)
        func_00208980(trail, m, colour);
}

/* 0x0016EBB0, 0xDC bytes. Sets the matrix and colour of a slot's trails (+0x58 not for the
 * kinds held between two hands). */
void func_0016EBB0(u8 *slot, void *m, int colour)
{
    u32 i;

    for (i = 0; i < 2; i++) {
        if (PTR(slot, 0x50 + i * 4) != 0)
            func_0016EB90(PTR(PTR(slot, 0x50 + i * 4), 0x68), m, colour);
    }
    if (PTR(slot, 0x58) != 0 && (u32)(U8(slot, 0x48) - 0x30) > 7 && (u32)(U8(slot, 0x48) - 0x14) > 7)
        func_0016EB90(PTR(PTR(slot, 0x58), 0x68), m, colour);
    if (PTR(slot, 0x5C) != 0)
        func_0016EB90(PTR(PTR(slot, 0x5C), 0x68), m, colour);
}

typedef unsigned long long u64;

#define g_70000158 (*(u32 **)0x70000158)         /* the DMA chain's write cursor */
#define SCRATCH_W ((const float *)0x70000030)   /* (scratchpad) the point (0, 0, 0, 1) */

extern float g_00406580[0x38];           /* per kind: the reach of a two-handed weapon's end */
extern float g_004065A0[0x38];           /* the same, on the other side */

u8 *func_002087A0(void);
void func_00208820(u8 *trail, float *a, float *b, int player);
void func_0014F0E0(u8 *a, u32 alpha);
void func_0014F970(u8 *o);
u32 *func_0016F9B0(u32 *d, float *a, float *b, int r, int g, int bl, int al);
u32 *func_0016FD00(u32 *d, float *a, float *b, int r, int g, int bl, int al);

/* The point (x, 0, 0, 1) placed by matrix m (divided by its w) into out. */
static inline void place_x(float *out, const float *m, float x)
{
    float v[4];
    int k;

    v[0] = x;
    v[1] = SCRATCH_W[1];
    v[2] = SCRATCH_W[2];
    v[3] = SCRATCH_W[3];
    mat_vec(out, m, v);
    v[3] = 1.0f / out[3];
    for (k = 0; k < 4; k++)
        out[k] = out[k] * v[3];
}

/* Keeps an edge's ends as its previous ones (+0x20 / +0x30 into +0x40 / +0x50). */
static inline void keep_ends(u8 *w)
{
    int i, k;

    for (i = 0; i < 2; i++)
        for (k = 0; k < 4; k++)
            F32(w, 0x40 + i * 0x10 + k * 4) = F32(w, 0x20 + i * 0x10 + k * 4);
}

/* 0x0016F8E0, 0xD0 bytes. Starts a trail for an edge: from its end (the length lengthened by
 * `grow`, times the scale) to its base. Whether it started. */
int func_0016F8E0(float grow, float *e, int player)
{
    float a[4], b[4], len;
    u8 *t;

    if (e == 0)
        return 0;
    a[1] = SCRATCH_W[1];
    a[2] = SCRATCH_W[2];
    a[3] = SCRATCH_W[3];
    b[1] = SCRATCH_W[1];
    b[2] = SCRATCH_W[2];
    b[3] = SCRATCH_W[3];
    len = e[4] < 0.0f ? e[4] - grow : e[4] + grow;
    b[0] = e[0];
    a[0] = len * e[0x19] + b[0];
    t = func_002087A0();
    *(u8 **)&e[0x1A] = t;
    if (t == 0)
        return 0;
    func_00208820(t, a, b, player);
    return 1;
}

/* 0x001700A0, 0x50 bytes. Draws a slot's weapon object (not with flag 0x80): a model actor
 * (flag 4) or a plain object. */
void func_001700A0(u8 *slot, u32 alpha)
{
    if ((U8(slot, 0x4C) & 0x80) == 0) {
        if (U8(slot, 0x4C) & 4)
            func_0014F0E0(PTR(slot, 0x44), alpha);
        else
            func_0014F970(PTR(slot, 0x44));
    }
}

/* 0x001700F0, 0x20C bytes. Places the edge (+0x58) of a two-handed weapon held between two
 * nodes (`on`): from node `ma` to the kind's reach along node `mb` (the table by `side`); on
 * the first frame (flag 0x40 of +0x4C) the previous ends too. */
void func_001700F0(u8 *slot, int on, float *ma, float *mb, int side)
{
    u8 *w = PTR(slot, 0x58);

    U8(w, 0x60) = (U8(w, 0x60) & ~2) | (on & 1) << 1;
    if (on == 0)
        return;
    keep_ends(w);
    place_x(&F32(w, 0x20), ma, SCRATCH_W[0]);
    if (side == 0)
        place_x(&F32(w, 0x30), mb, g_00406580[U8(slot, 0x48)]);
    else
        place_x(&F32(w, 0x30), mb, g_004065A0[U8(slot, 0x48)]);
    if (U8(slot, 0x4C) & 0x40)
        keep_ends(w);
    U8(slot, 0x4C) &= ~0x40;
}

/* 0x00170300, 0x204 bytes. Draws a two-handed weapon's two lines (from node `ma` to the reaches
 * along `mb` and `mc`) as a GS packet. */
void func_00170300(u8 *slot, float *ma, float *mb, float *mc)
{
    float a[4], b[4], c[4];
    u32 *d;
    u64 *q;

    place_x(a, ma, SCRATCH_W[0]);
    place_x(b, mb, g_00406580[U8(slot, 0x48)]);
    place_x(c, mc, g_004065A0[U8(slot, 0x48)]);
    d = g_70000158;
    d[0] = 0x10000002;
    d[1] = 0;
    d[2] = 0x11000000;
    d[3] = 0x50000002;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008001ULL;
    q[1] = 0xE;
    q[2] = 0;
    q[3] = 8;
    d = func_0016FD00((u32 *)(q + 4), a, b, 0x80, 0x80, 0x80, 0x80);
    g_70000158 = d;
    g_70000158 = func_0016FD00(d, a, c, 0x80, 0x80, 0x80, 0x80);
}

/* 0x00170510, 0x18C bytes. The edge of the kinds held at both ends (0x14-0x1B): from 16 along
 * node `ma` to 14 along `mb`. */
void func_00170510(u8 *slot, int on, float *ma, float *mb)
{
    u8 *w = PTR(slot, 0x58);

    U8(w, 0x60) = (U8(w, 0x60) & ~2) | (on & 1) << 1;
    if (on == 0)
        return;
    keep_ends(w);
    place_x(&F32(w, 0x20), ma, 16.0f);
    place_x(&F32(w, 0x30), mb, 14.0f);
    if (U8(slot, 0x4C) & 0x40)
        keep_ends(w);
    U8(slot, 0x4C) &= ~0x40;
}

/* 0x001706A0, 0x100 bytes. Draws that weapon's line (16 along `ma` to 14 along `mb`). */
void func_001706A0(u8 *slot, float *ma, float *mb)
{
    float a[4], b[4];

    place_x(a, ma, 16.0f);
    place_x(b, mb, 14.0f);
    g_70000158 = func_0016F9B0(g_70000158, a, b, 0xBE, 0x80, 0x80, 0x42);
}

/* 0x001707A0, 0x104 bytes. The entry for weapon kind `k` in a table at `base` (kinds 0-0x19
 * 4 bytes each; the groups 0x3E-0x48, 0x49-0x53, 0x54-0x5C, 0x5D-0x67 at +0x68 / +0x6C /
 * +0x70 / +0x70); 0x6A for the others, as in the original. */
int func_001707A0(int k, int base)
{
    if (k > 0x19) {
        if (k >= 0x3E && k <= 0x48)
            k = 0x26;
        else if (k >= 0x49 && k <= 0x53)
            k = 0x2A;
        else if (k >= 0x54 && k <= 0x5C)
            k = 0x20;
        else if (k > 0x5C && k < 0x68)
            k = 0x21;
    }
    if (k < 0 || k > 0x19) {
        if (k == 0x21 || k == 0x20)
            return base + 0x70;
        if (k == 0x2A)
            return base + 0x6C;
        if (k == 0x26)
            return base + 0x68;
        return 0x6A;
    }
    return base + k * 4;
}
