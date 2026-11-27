/*
 * obj_effects.c - stage object effects between 0x002AE090 and 0x002AF46C: up to 255 effect
 * requests (0x40 bytes each from 0x0078E010: kind, sound, position, state) shown through 64
 * drawn slots (0x60 bytes each from 0x00792070: a matrix block, kind, owner request, state 2
 * shown, 1 hidden this frame, 0 to free) and one model per kind (0x00791FD0). Original file name
 * unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8 g_0078E010[0xFF][0x40];        /* the requests */
extern u8 g_00792070[0x40][0x60];        /* the drawn slots */
extern u8 *g_00791FD0[0x28];             /* a model per kind */
extern u32 g_0045D57C, g_0045D580;       /* (small data) the first free request, slot */
extern int g_0045CEC8, g_0045CECC;       /* free counts */
extern int g_0045D584, g_0045D588, g_0045D58C;
extern u8 *g_0045D2C0;                   /* the camera */
extern u8 g_004004B0[];
extern u8 g_00441570[0x28];
extern int g_00441430[0x28], g_004414D0[0x28], g_00441390[0x28], g_004412F0[0x28];

#define SP_PKT (*(u32 **)0x70000158)
#define REQ(k) g_0078E010[k]
#define SLOT(k) g_00792070[k]
#define FL38(o) (*(u32 *)((o) + 0x38))

void func_00118850(void *p, int n);
void func_002ADA00(void);
void func_002ADDE0(void);
void func_002A6770(int s, int v);
u32 *func_002AE2A0(float f, u32 *p, u8 *slot, float *cam);

/* 0x002AE090, 0xC0 bytes. The effects' microcode and camera block. */
u32 *func_002AE090(u32 *p)
{
    int k;

    p[0] = 0x50000000;
    p[1] = (u32)g_004004B0;
    p[2] = 0x11000000;
    p[3] = 0;
    p[4] = 0x10000008;
    p[5] = 0;
    p[6] = 0x11000000;
    p[7] = 0x6C080000;
    for (k = 0; k < 16; k++)
        p[8 + k] = *(u32 *)(g_0045D2C0 + 0x100 + k * 4);
    for (k = 0; k < 16; k++)
        p[0x18 + k] = *(u32 *)(g_0045D2C0 + 0xC0 + k * 4);
    p[0x28] = 0x10000000;
    p[0x29] = 0;
    p[0x2A] = 0;
    p[0x2B] = 0x14000000;
    return p + 0x2C;
}

/* 0x002AE150, 0x20 bytes, matching. */
u32 *func_002AE150(u32 *p)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x17000000;
    return p + 4;
}

/* 0x002AE170, 0x80 bytes. Takes a drawn slot (0x40: none). */
u8 func_002AE170(void)
{
    u8 r = 0x40, *b;

    if (g_0045D580 < 0x40) {
        b = SLOT(g_0045D580);
        b[0x5A] = 1;
        b[0x5B] = 2;
        g_0045CECC--;
        r = b[0x59];
        while (g_0045D580 < 0x40 && b[0x5A] != 0) {
            g_0045D580++;
            b += 0x60;
        }
    }
    return r;
}

/* 0x002AE1F0, 0xB0 bytes. Frees slot `k`. */
void func_002AE1F0(u32 k)
{
    u8 *b = (k & 0xFF) < 0x40 ? SLOT(k & 0xFF) : 0;

    if (b == 0)
        return;
    b[0x5A] = 0;
    b[0x58] = 0x28;
    if (*(int *)(b + 0x54) != 0) {
        g_0045D584--;
        *(int *)(b + 0x54) = 0;
    }
    if (*(int *)(b + 0x50) != 0) {
        g_0045D588--;
        *(int *)(b + 0x50) = 0;
    }
    *(short *)(b + 0x5C) = 0xFF;
    b[0x5B] = 3;
    if (b[0x59] <= g_0045D580)
        g_0045D580 = b[0x59];
    g_0045CECC++;
}

/* 0x002AEBB0, 0x150 bytes. Clears every request and slot. */
void func_002AEBB0(void)
{
    u32 k;
    int j;

    g_0045D57C = 0;
    g_0045CEC8 = 0xFF;
    for (k = 0; k < 0xFF; k++) {
        func_00118850(REQ(k), 0x40);
        *(u32 *)REQ(k) = k;
    }
    g_0045D580 = 0;
    g_0045CECC = 0x40;
    for (k = 0; k < 0x40; k++) {
        u8 *b = SLOT(k);

        func_00118850(b, 0x60);
        b[0x59] = k;
        b[0x58] = 0x28;
        *(u32 *)(b + 0) = 0;
        *(u32 *)(b + 4) = 0;
        *(u32 *)(b + 8) = 0x11000000;
        *(u32 *)(b + 0xC) = 0x6C040013;
        for (j = 0; j < 16; j++)
            *(u32 *)(b + 0x10 + j * 4) = ((u32 *)0x70000000)[j];
    }
    for (k = 0; k < 0x28; k++)
        g_00791FD0[k] = 0;
    func_002ADA00();
    func_002ADDE0();
    g_0045D584 = 0;
    g_0045D588 = 0;
    g_0045D58C = 0;
}

/* 0x002AED00, 0x100 bytes. A new effect request of kind `kind` at `pos`; its index (0xFF:
 * none). */
u32 func_002AED00(float f, int kind, u32 *pos, int b)
{
    u8 *a;
    u32 r;

    if (g_0045D57C >= 0xFF)
        return 0xFF;
    a = REQ(g_0045D57C);
    a[0xC] = 1;
    *(int *)(a + 0x18) = kind;
    *(int *)(a + 4) = b;
    if (g_00441570[kind] != 0)
        f = f * -1.0f;
    *(float *)(a + 8) = f;
    g_0045CEC8--;
    *(int *)(a + 0x1C) = g_00441430[kind];
    *(int *)(a + 0x10) = 0x107;
    g_0045D58C++;
    a[0xD] = 0x40;
    *(int *)(a + 0x20) = 0;
    *(int *)(a + 0x24) = 0;
    *(u32 *)(a + 0x30) = pos[0];
    *(u32 *)(a + 0x34) = pos[1];
    *(u32 *)(a + 0x38) = pos[2];
    *(u32 *)(a + 0x3C) = pos[3];
    *(int *)(a + 0x14) = 0;
    r = *(u32 *)a;
    for (; g_0045D57C < 0xFF; g_0045D57C++) {
        if (REQ(g_0045D57C)[0xC] == 0)
            return r;
    }
    return r;
}

/* 0x002AEE00, 0x8C bytes. Sets request `k`'s state from `s`. */
void func_002AEE00(u32 k, char s)
{
    u8 *a;

    if (k >= 0xFF)
        return;
    a = REQ(k);
    if (s == 3)
        *(int *)(a + 0x1C) = 0;
    else if (s == 2)
        *(int *)(a + 0x1C) = g_004414D0[*(int *)(a + 0x18)];
    else if (s == 1)
        *(int *)(a + 0x1C) = 0;
    else if (s == 0)
        *(int *)(a + 0x1C) = 3;
}

/* 0x002AF070, 0x78 bytes. Drops request `k`'s model (and its sound). */
void func_002AF070(u32 k)
{
    u8 *a;

    if (k >= 0xFF)
        return;
    a = REQ(k);
    if (*(int *)(a + 0x14) != 0) {
        *(int *)(a + 0x14) = 0;
        if (*(int *)(a + 0x10) != 0x107) {
            func_002A6770(*(int *)(a + 0x10), g_00441390[*(int *)(a + 0x18)]);
            *(int *)(a + 0x10) = -1;
        }
    }
}

/* 0x002AF0F0, 0x30 bytes, matching. Effect kind `k`'s model. */
int func_002AF0F0(int k)
{
    if (k < 0x28)
        return g_004412F0[k];
    return 0xEC;
}

/* 0x002AF120, 0x88 bytes. Hides request `k`. */
void func_002AF120(u32 k)
{
    u8 *a;
    u8 s;

    if (k >= 0xFF)
        return;
    a = REQ(k);
    s = a[0xD];
    if (s < 0x40) {
        SLOT(s)[0x5B] = 1;
        a[0xD] = 0x40;
    } else {
        u8 *o = *(u8 **)(a + 0x14);

        if (o != 0)
            FL38(o) |= 8;
    }
    *(int *)(a + 0x1C) = 0;
}

/* 0x002AF1B0, 0x188 bytes. The frame's clean-up of slots and requests not refreshed. */
void func_002AF1B0(void)
{
    u32 n = g_0045D58C, k;

    for (k = 0; k < 0x40; k++) {
        u8 *b = SLOT(k);

        if (b[0x5A] != 0) {
            if (b[0x5B] == 0)
                func_002AE1F0(b[0x59]);
            else if (b[0x5B] == 1)
                b[0x5B] = 0;
        }
    }
    for (k = 0; k < n; k++) {
        u8 *a = REQ(k), *o;

        if (a[0xC] == 0)
            continue;
        o = *(u8 **)(a + 0x14);
        if (o == 0) {
            u8 s = a[0xD];

            if (s < 0x40 && *(int *)(a + 0x20) == 0 && *(int *)(a + 0x24) == 0) {
                SLOT(s)[0x5B] = 0;
                a[0xD] = 0x40;
                if (*(int *)(a + 0x10) != 0x107) {
                    func_002A6770(*(int *)(a + 0x10), g_00441390[*(int *)(a + 0x18)]);
                    *(int *)(a + 0x10) = -1;
                }
            }
        } else if (*(int *)(a + 0x20) == 0 && *(int *)(a + 0x24) == 0) {
            FL38(o) |= 8;
        }
        *(int *)(a + 0x20) = 0;
        *(int *)(a + 0x24) = 0;
    }
}

/* 0x002AF340, 0x130 bytes. Draws the shown slots for camera `cam`, dropping unused models. */
void func_002AF340(int cam, float *c)
{
    u32 *pk = SP_PKT;
    u64 used = 0;
    u32 k;

    for (k = 0; k < 0x40; k++) {
        u8 *b = SLOT(k);

        if (b[0x5A] != 0 && b[0x5B] == 2 && b[0x58] < 0x28) {
            pk = func_002AE2A0(*(float *)(REQ(*(u16 *)(b + 0x5C)) + 0x28 + cam * 4), pk, b, c);
            used |= 1ULL << b[0x58];
        }
    }
    for (k = 0; k < 0x28; k++) {
        if ((used & 1ULL << k) == 0 && g_00791FD0[k] != 0) {
            FL38(g_00791FD0[k]) |= 8;
            g_00791FD0[k] = 0;
        }
    }
    SP_PKT = pk;
}
