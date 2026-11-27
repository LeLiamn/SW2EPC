/*
 * unit_setup.c - setting up battlefield units (original source file unknown; from 0x00164680,
 * after camera.c, up to Weapon.c at 0x0016CD30).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units (0x630 bytes) are reached by offset as in unit.c:
 * +0x40 position, +0x50 rotation, +0x60 scale, +0x118 state, +0x14E player, +0x290 four motion
 * slots of 0x70, +0x450 ten records of 0x30.
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

extern u32 g_00424B30[10];               /* the ten records' kinds */

void func_001185E0(void *p, int size, int value);  /* memset */
void func_00150B20(Unit *u);
void func_00166160(Unit *u);
void func_0016E2E0(u8 *slot);
void func_001BE4F0(void);
void func_001BE540(void);
void func_001BE770(void);
void func_001649C0(Unit *u);

/* The matrix of rotation `rot` and position `pos` (VU0 micro subroutine 0x50) into m. */
#define UNIT_MATRIX(m, rot, pos)                                        \
    __asm__ volatile("lqc2 $vf1, 0(%1)\n"                               \
                     "lqc2 $vf2, 0(%2)\n"                               \
                     "vcallms 0x50\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x00(%0)\n"                           \
                     "sqc2 $vf17, 0x10(%0)\n"                           \
                     "sqc2 $vf18, 0x20(%0)\n"                           \
                     "sqc2 $vf19, 0x30(%0)\n"                           \
                     : : "r"(m), "r"(rot), "r"(pos) : "$9", "memory")

/* 0x00164680, 0x34 bytes, matching. Clears a unit and gives it its defaults. */
void func_00164680(Unit *u)
{
    func_001185E0(u, 0x630, 0);
    func_00150B20(u);
}

/* 0x001646C0, 0x2C4 bytes. Resets a unit for `player`: at the origin, no rotation, scale 1; its
 * matrix (+0, scaled when flag 0x80 of +0x19C is set or +0x1BA > 3 on foot); state 0x40; its
 * counters and links cleared; the four motion slots and the ten records reset. */
void func_001646C0(Unit *u, u8 player)
{
    int i, k;
    u8 *r;

    F32(u, 0x40) = 0.0f;
    F32(u, 0x44) = 0.0f;
    F32(u, 0x48) = 0.0f;
    F32(u, 0x4C) = 1.0f;
    for (k = 0; k < 4; k++)
        F32(u, 0x80 + k * 4) = 0.0f;
    F32(u, 0x90) = 0.0f;
    F32(u, 0x94) = 0.0f;
    F32(u, 0x98) = 0.0f;
    F32(u, 0x9C) = 1.0f;
    F32(u, 0xA0) = 0.0f;
    F32(u, 0xA4) = 0.0f;
    F32(u, 0xA8) = 0.0f;
    F32(u, 0xAC) = 1.0f;
    F32(u, 0xB0) = 0.0f;
    F32(u, 0xB4) = 0.0f;
    F32(u, 0xB8) = 0.0f;
    F32(u, 0xBC) = 1.0f;
    F32(u, 0x60) = 1.0f;
    F32(u, 0x64) = 1.0f;
    F32(u, 0x68) = 1.0f;
    F32(u, 0x6C) = 0.0f;
    if ((U8(u, 0x19C) & 0x80) || (U8(u, 0x1BA) > 3 && S32(u, 0x118) < 0x3C)) {
        float m[4][4], s[4][4];

        UNIT_MATRIX(u, &F32(u, 0x50), &F32(u, 0x40));
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                m[i][k] = F32(u, i * 0x10 + k * 4);
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                s[i][k] = i == k ? (i < 3 ? F32(u, 0x60 + i * 4) : 1.0f) : 0.0f;
        for (i = 0; i < 4; i++)
            for (k = 0; k < 4; k++)
                F32(u, i * 0x10 + k * 4) = m[0][k] * s[i][0] + m[1][k] * s[i][1]
                                           + m[2][k] * s[i][2] + m[3][k] * s[i][3];
    } else {
        UNIT_MATRIX(u, &F32(u, 0x50), &F32(u, 0x40));
    }
    S32(u, 0x118) = 0x40;
    U16(u, 0x12C) = 0;
    U16(u, 0x12E) = 0;
    S32(u, 0x128) = -1;
    U16(u, 0x15E) = 0;
    U8(u, 0x187) = 0;
    U8(u, 0x18A) = 0;
    U8(u, 0x18B) = 0;
    U8(u, 0x157) = 0;
    U16(u, 0x194) = 0;
    U8(u, 0x14D) = 0x80;
    U8(u, 0x185) = 0x17;
    U32(u, 0x120) = 0;
    U32(u, 0x124) = 0;
    U8(u, 0x14C) = 0x40;
    U16(u, 0x188) = 0;
    U16(u, 0x190) = 0;
    U16(u, 0x192) = 0;
    U8(u, 0x1BC) = 0;
    U8(u, 0x1BA) = 7;
    U32(u, 0x19C) = 0;
    U8(u, 0x14E) = player;
    U8(u, 0x14F) = 0;
    U8(u, 0x198) = (U8(u, 0x198) & ~1) | 1;
    U16(u, 0x178) = 0xFFFF;
    for (i = 0; i < 4; i++)
        func_0016E2E0(u + 0x290 + i * 0x70);
    r = u + 0x450;
    for (i = 0; i < 10; i++) {
        func_001185E0(r, 0x30, 0);
        U32(r, 0x20) = g_00424B30[i];
        U8(r, 0x24) &= ~1;
        r += 0x30;
    }
    func_001649C0(u);
}

/* 0x00164990, 0x2C bytes, matching. Drops a unit's links, then clears it. */
void func_00164990(Unit *u)
{
    func_00166160(u);
    func_00164680(u);
}

/* 0x001649C0, 0xC0 bytes. Turns off the four motion slots (flag 2) and the ten records
 * (flag 1). */
void func_001649C0(Unit *u)
{
    u8 *r = u + 0x450;
    int i;

    U8(u, 0x2DC) &= ~2;
    U8(u, 0x34C) &= ~2;
    U8(u, 0x3BC) &= ~2;
    U8(u, 0x42C) &= ~2;
    for (i = 0; i < 10; i += 5) {
        U8(r, 0x24) &= ~1;
        U8(r, 0x54) &= ~1;
        U8(r, 0x84) &= ~1;
        U8(r, 0xB4) &= ~1;
        U8(r, 0xE4) &= ~1;
        r += 0xF0;
    }
}

/* 0x00164A80, 0x54 bytes, matching. Loads the shared motions for state `s`: mounted (0x3C), 0x3D-0x3F,
 * or on foot. */
void func_00164A80(int s)
{
    if (s == 0x3C)
        func_001BE540();
    else if ((u32)(s - 0x3D) < 3)
        func_001BE770();
    else
        func_001BE4F0();
}

/* 0x00164AE0, 0x60 bytes, matching. The same for 0x3C and 0x3D-0x3E; the mounted set otherwise (as in
 * the original). */
void func_00164AE0(int s)
{
    if (s == 0x3C)
        func_001BE540();
    else if (s == 0x3D || (u32)(s - 0x3D) < 2)
        func_001BE770();
    else
        func_001BE540();
}
