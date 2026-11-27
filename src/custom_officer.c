/*
 * custom_officer.c - the 15 custom (edit mode) officers kept in the settings (0x38 bytes each at
 * 0x00669FB4) and the custom officers' look tables (0x00418E10, 0x00418FD0). Original file name
 * unknown (parts of 0x0039E5F0-0x0039EF7C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00669FB4[0xF][0x38];         /* the custom officers (+0x00 used, +0x01 name, +0x0A
                                          * reading, ...) */
extern u8 g_00418E10[][0x20];
extern u8 g_00418FD0[][0x20];

void func_0011ED38(void *p, int v, int n);
void func_0039E8C0(int k);

/* 0x0039E650, 0x24 bytes. */
int func_0039E650(int k)
{
    return g_00669FB4[k][0] != 0;
}

/* 0x0039E5F0, 0x54 bytes. Whether any custom officer exists. */
int func_0039E5F0(void)
{
    int k;

    for (k = 0; k < 0xF; k++) {
        if (func_0039E650(k) != 0)
            return 1;
    }
    return 0;
}

/* 0x0039E680, 0x20 bytes. Its name. */
u8 *func_0039E680(int k)
{
    return g_00669FB4[k] + 1;
}

/* 0x0039E6A0, 0x20 bytes. Its reading. */
u8 *func_0039E6A0(int k)
{
    return g_00669FB4[k] + 0xA;
}

/* 0x0039E6C0, 0x20 bytes. */
u8 func_0039E6C0(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x13);
}

/* 0x0039E6E0, 0x20 bytes. */
u32 func_0039E6E0(int k)
{
    return *(u32 *)(g_00669FB4[k] + 0x18);
}

/* 0x0039E700, 0x20 bytes. */
u8 func_0039E700(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x1C);
}

/* 0x0039E720, 0x20 bytes. */
u32 func_0039E720(int k)
{
    return *(u32 *)(g_00669FB4[k] + 0x20);
}

/* 0x0039E740, 0x20 bytes. */
u32 func_0039E740(int k)
{
    return *(u32 *)(g_00669FB4[k] + 0x24);
}

/* 0x0039E760, 0x20 bytes. */
u8 func_0039E760(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x28);
}

/* 0x0039E780, 0x20 bytes. */
u8 func_0039E780(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x2A);
}

/* 0x0039E7A0, 0x20 bytes. */
u8 func_0039E7A0(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x2C);
}

/* 0x0039E7C0, 0x20 bytes. */
u8 func_0039E7C0(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x2D);
}

/* 0x0039E7E0, 0x20 bytes. */
u8 func_0039E7E0(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x2F);
}

/* 0x0039E800, 0x20 bytes. */
u8 func_0039E800(int k)
{
    return *(u8 *)(g_00669FB4[k] + 0x30);
}

/* 0x0039E820, 0x58 bytes. Clears them all. */
void func_0039E820(void)
{
    u32 k;

    for (k = 0; k < 0xF; k++)
        func_0011ED38(g_00669FB4[k], 0, 0x38);
}

/* 0x0039E880, 0x20 bytes, matching. */
u32 func_0039E880(int a, int b)
{
    return *(u32 *)(g_00418FD0[a] + b * 8);
}

/* 0x0039E8A0, 0x20 bytes. */
u32 func_0039E8A0(int a, int b)
{
    return *(u32 *)(g_00418FD0[a] + b * 8 + 4);
}

/* 0x0039EB00, 0x3C bytes, matching. */
void func_0039EB00(void)
{
    int k;

    for (k = 0; k < 0xF; k++)
        func_0039E8C0(k);
}

/* 0x0039EE80, 0x18 bytes. */
u16 func_0039EE80(int k)
{
    return *(u16 *)(g_00418E10[k] + 0x0);
}

/* 0x0039EEA0, 0x18 bytes. */
u16 func_0039EEA0(int k)
{
    return *(u16 *)(g_00418E10[k] + 0x2);
}

/* 0x0039EEC0, 0x18 bytes. */
u16 func_0039EEC0(int k)
{
    return *(u16 *)(g_00418E10[k] + 0x4);
}

/* 0x0039EEE0, 0x18 bytes. */
u16 func_0039EEE0(int k)
{
    return *(u16 *)(g_00418E10[k] + 0x6);
}

/* 0x0039EF00, 0x18 bytes. */
u16 func_0039EF00(int k)
{
    return *(u16 *)(g_00418E10[k] + 0x8);
}

/* 0x0039EF20, 0x18 bytes. */
u16 func_0039EF20(int k)
{
    return *(u16 *)(g_00418E10[k] + 0xA);
}

/* 0x0039EF40, 0x18 bytes. */
u16 func_0039EF40(int k)
{
    return *(u16 *)(g_00418E10[k] + 0xC);
}

/* 0x0039EF60, 0x18 bytes. */
u16 func_0039EF60(int k)
{
    return *(u16 *)(g_00418E10[k] + 0xE);
}
