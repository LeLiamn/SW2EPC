/*
 * troop_ai2.c - battle officer AI steps between 0x00238090 and 0x002399D4 (officers are the
 * 0xC0-byte records at 0x006A3A30: +0x08 the target, +0x10 the troop, +0x14 the unit, +0x7C the
 * behaviour, +0x7D the state, +0xB8/+0xBC flags). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_006A3A30[][0xC0];
extern u32 g_7000015C;

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define FL_B8(o) (*(u32 *)((o) + 0xB8))
#define FL_BC(o) (*(u32 *)((o) + 0xBC))
#define TARGET(o) (*(u8 **)((o) + 8))
#define SET_STATE(o, s) do { FL_BC(o) &= 0xFFF8003F; (o)[0x7D] = (s); } while (0)

u8 *func_001F14E0(u8 *o);
void func_00237F10(u8 *o);
void func_00237F60(u8 *o);
void func_00237ED0(u8 *o);
void func_00206080(u8 *o);
void func_00238AE0(u8 *o, int t);
int func_00238200(u8 *o);
void func_00237FA0(u8 *o);
void func_00204BF0(u8 *o);
int func_00174A40(float r, u8 *a, u8 *b);
int func_00238C90(u8 *o, int k);
void func_002396B0(u8 *o, int k);
void func_00239520(u8 *o);
void func_00204B60(u8 *o, int k);
void func_00271A10(u8 *o, int k);

int func_00239830(u8 *o);
void func_00239780(u8 *o, int k);

/* 0x00238090, 0x164 bytes. Picks an attack by the officer's chances. */
void func_00238090(u8 *o)
{
    u8 *t = func_001F14E0(o);

    if (RANDOM() % 100 < (u32)(t[0] >> 1))
        func_00237F10(o);
    else if (RANDOM() % 100 < t[1])
        func_00237F60(o);
    else if (RANDOM() % 100 < t[6])
        func_00237ED0(o);
    else if (RANDOM() % 100 < t[2])
        func_00206080(o);
    else if (RANDOM() % 100 < t[3])
        func_00238AE0(o, 0x3C);
    else
        func_00206080(o);
}

/* 0x00238570, 0xB4 bytes. The officer's frame by behaviour. */
void func_00238570(u8 *o)
{
    char k;

    if (func_00238200(o) != 0)
        return;
    k = o[0x7C];
    if (k == 3) {
        if (func_00239830(o) == 0)
            func_00239780(o, 0);
    } else if (k == 2) {
        func_00239780(o, 0);
    } else if (k == 1) {
        func_00238090(o);
    } else if (k == 0) {
        func_00237FA0(o);
    }
}

/* 0x00238630, 0x3C bytes. */
void func_00238630(u8 *o, int k)
{
    if (k == 2)
        func_00204BF0(o);
    else
        FL_BC(o) &= ~0x100000;
}

/* 0x00238670, 0x98 bytes. How many enemy officers on horseback attack `t`. */
int func_00238670(u8 *t)
{
    int n = 0;
    u32 k;

    for (k = 0; k < 0x76; k++) {
        u8 *o = g_006A3A30[4 + k];

        if ((FL_B8(o) & 1) != 0 && (FL_B8(o) & 0x80) != 0 && TARGET(o) != 0 && TARGET(o) == t
            && o[0x7C] == 0 && (*(u32 *)(*(u8 **)(o + 0x10) + 0x80) & 0x1800) != 0
            && (*(u8 **)(t + 0x10))[0x79] != (*(u8 **)(o + 0x10))[0x79])
            n++;
    }
    return n;
}

/* 0x00238DE0, 0x94 bytes. Whether the officer may go for its target (`k`: farther). */
int func_00238DE0(u8 *o, int k)
{
    if ((FL_B8(o) & 0x10200) == 0) {
        int lim = k == 0 ? 7 : 10;

        if (func_00174A40(100.0f, *(u8 **)(o + 0x14) + 0x40, o + 0x20) >= lim)
            return 0;
        if (func_00238C90(o, 1) == 0)
            return 0;
    }
    return 1;
}

/* 0x00239780, 0xA4 bytes. */
void func_00239780(u8 *o, int k)
{
    if (func_00238DE0(o, k) != 0)
        return;
    if (RANDOM() % 100 < 0x32)
        func_00238AE0(o, RANDOM() % 0x28 + 100);
    else
        func_00206080(o);
}

/* 0x00239830, 0x64 bytes. Whether the officer has lost its target. */
int func_00239830(u8 *o)
{
    u8 *t = TARGET(o);

    if (t == 0 || (FL_B8(t) & 0xC) != 0) {
        if (func_00238DE0(o, 0) == 0)
            func_00206080(o);
        return 1;
    }
    return 0;
}

/* 0x002398A0, 0xA0 bytes. Another behaviour frame. */
void func_002398A0(u8 *o)
{
    char k = o[0x7C];

    if (k == 3) {
        if (func_00239830(o) == 0)
            func_00239780(o, 0);
    } else if (k == 2) {
        func_00239780(o, 0);
    } else if (k == 1) {
        func_002396B0(o, 0);
    } else if (k == 0) {
        func_00239520(o);
    }
}

/* 0x00239940, 0x38 bytes, matching. */
void func_00239940(u8 *o)
{
    SET_STATE(o, 1);
    func_00204B60(o, 2);
}

/* 0x00239980, 0x54 bytes. */
void func_00239980(u8 *o)
{
    u8 *u;

    SET_STATE(o, 2);
    u = *(u8 **)(o + 0x14);
    *(int *)(u + 0x13C) = 0;
    *(u32 *)(u + 0x1D0) = *(u32 *)0x700000C0;
    *(u32 *)(u + 0x1D4) = *(u32 *)0x700000C4;
    *(u32 *)(u + 0x1D8) = *(u32 *)0x700000C8;
    *(u32 *)(u + 0x1DC) = *(u32 *)0x700000CC;
    func_00271A10(o, 0x21);
}
