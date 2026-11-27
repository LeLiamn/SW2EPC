/*
 * unit_gauges.c - unit helpers between 0x002711F0 and 0x002723AC: the musou gauge (players'
 * maxima in the game settings, the others' in their battle officer record), low life, motion
 * picks by the unit's state, and the event scene's sound slots (16 of 0x20 bytes per player).
 * Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00669D60[];
extern u8 g_006A3A30[][0xC0];
extern int g_00410B30[], g_00410B40[];
extern u16 g_00410B50[][5];
extern int g_0045D3E0;                   /* (small data) the player */
extern u8 *g_0045D530[2], *g_0045D538[2];

#define OFF(u) g_006A3A30[*(short *)((u) + 0x178)]
#define KIND_FLAGS(u, o) (*(u32 *)(*(u8 **)((u) + 0x210) + (o)))

void *func_0020EC50(int n);
int func_002A64C0(u32 s);
int func_002A6910(int v, int a, u8 *r);
void func_0023ACC0(u32 s, int a);
void func_002A5B10(u32 h);

/* 0x00271210, 0x64 bytes. Unit `u`'s musou gauge maximum. */
short func_00271210(u8 *u)
{
    if (u[0x14E] < 2)
        return *(short *)(g_00669D60 + 0xC4 + u[0x14E] * 0x48);
    return *(short *)(OFF(u) + 0x86);
}

/* 0x00271280, 0x80 bytes. How many times full it is. */
int func_00271280(u8 *u)
{
    u8 *o = OFF(u);
    short m;

    if (u[0x14E] < 2)
        m = *(short *)(g_00669D60 + 0xC4 + u[0x14E] * 0x48);
    else
        m = *(short *)(o + 0x86);
    if (m < 1)
        return 0;
    return *(short *)(o + 0x88) / m;
}

/* 0x002711F0, 0x20 bytes, matching. */
int func_002711F0(u8 *u)
{
    return func_00271280(u) > 0;
}

/* 0x00271300, 0x58 bytes. Whether the gauge is full. */
int func_00271300(u8 *u)
{
    short v = *(short *)(OFF(u) + 0x88);

    return func_00271210(u) <= v;
}

/* 0x00271360, 0x18 bytes. */
int func_00271360(int k)
{
    return g_00410B30[k];
}

/* 0x00271380, 0x18 bytes. */
int func_00271380(int k)
{
    return g_00410B40[k];
}

/* 0x002713A0, 0x94 bytes. Whether the unit's officer is at low life (under a quarter, at most
 * 50). */
int func_002713A0(u8 *u)
{
    u8 *o = OFF(u);

    if (o[0xB0] < 2) {
        int q = *(short *)(o + 0x80) / 4, lim = q < 0x32 ? q : 0x32;

        return *(short *)(o + 0x82) < lim;
    }
    return 1;
}

/* 0x00271440, 0x100 bytes. The unit's idle motion by its state. */
u16 func_00271440(u8 *u)
{
    int low = func_002713A0(u);
    u16 *t = g_00410B50[u[0x182]];

    if ((KIND_FLAGS(u, 0x18) & 0x8000000) == 0) {
        if ((u[0x19D] & 0x20) != 0)
            return t[2];
        return low == 0 ? t[0] : t[1];
    }
    return low == 0 ? t[3] : t[4];
}

/* 0x00271540, 0x74 bytes. */
int func_00271540(u8 *u)
{
    int b = (u[0x19F] & 2) != 0;

    if ((KIND_FLAGS(u, 0x18) & 0x8000000) == 0) {
        if ((u[0x19D] & 0x20) != 0)
            return 0xDE;
        return b ? 0xDB : 0xC6;
    }
    return b ? 0xC4 : 0xC2;
}

/* 0x002715C0, 0x48 bytes. */
int func_002715C0(u8 *u)
{
    if ((KIND_FLAGS(u, 0x1C) & 0x20000) == 0 || (int)*(float *)(u + 0x21C) < 0x1E)
        return 0;
    return 1;
}

/* 0x00272110, 0x4C bytes, matching. The player's sound slots. */
void func_00272110(void)
{
    g_0045D538[g_0045D3E0] = func_0020EC50(0x200);
    g_0045D530[g_0045D3E0] = func_0020EC50(0x20);
}

/* 0x00272160, 0x40 bytes. A free slot (0: none). */
u8 *func_00272160(void)
{
    u8 *r = g_0045D538[g_0045D3E0];
    int i;

    for (i = 0; i < 0x10; i++, r += 0x20) {
        if (r[0x1C] == 0)
            return r;
    }
    return 0;
}

/* 0x002721A0, 0x50 bytes. The slot playing sound `k` (0: none). */
u8 *func_002721A0(int k)
{
    u8 *r = g_0045D538[g_0045D3E0];
    int i = 0;

    while (r[0x1C] == 0 || *(int *)(r + 0x18) != k) {
        i++;
        r += 0x20;
        if (i > 0xF)
            return 0;
    }
    return r;
}

/* 0x002721F0, 0x68 bytes. Starts sound `s` in slot `r` (for 60 frames). */
void func_002721F0(u8 *r, u32 s)
{
    int v, h;

    *(int *)(r + 0x18) = s & 0xFFFF;
    v = func_002A64C0(s & 0xFFFF);
    *(int *)(r + 0x18) = v;
    h = func_002A6910(v, 0, r);
    *(int *)(r + 0x14) = h;
    r[0x1C] = h != 0x107;
    *(float *)(r + 0x10) = 60.0f;
}

/* 0x00272260, 0x60 bytes, matching. Frees the slots whose time is over. */
void func_00272260(void)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0 && *(float *)(r + 0x10) <= 0.0f)
            r[0x1C] = 0;
    }
}

/* 0x002722C0, 0x50 bytes, matching. */
void func_002722C0(float dt)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0)
            *(float *)(r + 0x10) -= dt;
    }
}

/* 0x00272310, 0x94 bytes. Stops every slot's sound. */
void func_00272310(void)
{
    int i;

    for (i = 0; i < 0x10; i++) {
        u8 *r = g_0045D538[g_0045D3E0] + i * 0x20;

        if (r[0x1C] != 0) {
            u32 h = *(u32 *)(r + 0x14);

            if (h < 0xF3 || h > 0x106)
                func_0023ACC0(*(u32 *)(r + 0x18), 0);
            else
                func_002A5B10(h);
        }
    }
}
