/*
 * draw_lists.c - the 3D draw lists (parts of 0x001C8780-0x001CC9BC): the frame's drawing by
 * scene kind (0x0045D374), the object pools' release, and the DMA/VIF packet pieces written to
 * the packet pointer kept in the scratchpad (0x70000158). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern int g_0045D374, g_0045D378;       /* (small data) the scene kind, its argument */
extern int g_0045D344, g_0045D34C, g_0045D354, g_0045D35C, g_0045D364, g_0045D370;
extern int g_0072D100;
extern u8 g_00408510[], g_00408530[], g_00408550[];

#define SP_INT(a) (*(int *)(a))
#define SP_PKT (*(u32 **)0x70000158)      /* (scratchpad) the packet pointer */
#define SP_LIST SP_INT(0x70000D60)       /* (scratchpad) the list being drawn */
#define SP_COUNT SP_INT(0x70000D64)

int func_001C7060(int a, int b, int c, int d, u32 e, int f);
void func_001C6960(void);
void func_001C6AC0(void);
void func_001C6C80(void);
void func_001C6E40(void);
void func_001C6FA0(void);
void func_002AF1B0(void);
void func_001C10A0(u8 *p);
void func_002EAB50(void);
void func_00208FF0(void);
void func_0020F690(void);
void func_0021A4A0(void);
void func_00229140(void);
void func_001C9070(void);
void func_001C9E20(int a);
void func_001C9FA0(int a);
void func_001CA150(int a);
void func_001CA2F0(int a);
void func_001CA410(int a);
void func_001CA620(void);
u32 func_00100FE0(void);
u32 *func_001CCC00(u32 *p);
u32 *func_001CC580(u32 *p, u8 *a, u8 *b, u8 *c);
u8 *func_00106F10(u8 *t);
void func_001068F0(u8 *img, int a, int b, int c, int d, int e, int f, int g);

/* 0x001C8780, 0x2C bytes, matching. */
void func_001C8780(int a, int b, int c, u32 d)
{
    if (b != 0)
        func_001C7060(a, b, 0, c, d, 1);
}

/* 0x001C87B0, 0x54 bytes. */
int func_001C87B0(int a, int b, int c, u32 d)
{
    int r;

    if (b == 0)
        return 0;
    r = func_001C7060(a, b, 0, c, d, 0);
    if ((d & 1) == 0)
        r = 0;
    return r;
}

/* 0x001C8810, 0x5C bytes. */
int func_001C8810(int a, int b, int c, u32 d)
{
    int r;

    if (b == 0)
        return 0;
    r = func_001C7060(a, 0, b, c, d, 0);
    if ((d & 1) == 0)
        r = 0;
    return r;
}

/* 0x001C8B30, 0xA8 bytes, matching. The frame's drawing set-up by scene kind. */
void func_001C8B30(void)
{
    if (g_0045D374 == 0)
        func_001C6960();
    else if (g_0045D374 == 1)
        func_001C6AC0();
    else if (g_0045D374 == 2)
        func_001C6C80();
    else if (g_0045D374 == 3)
        func_001C6E40();
    else if (g_0045D374 == 4)
        func_001C6FA0();
    func_002AF1B0();
    SP_LIST = 0;
}

/* 0x001C8E80, 0x48 bytes, matching. */
void func_001C8E80(u8 *p)
{
    while (*(u32 *)(p + 0x40) < 2)
        func_001C10A0(p);
}

/* 0x001C9260, 0x68 bytes. */
void func_001C9260(void)
{
    if (g_0045D374 != 4 && g_0045D374 != 1 && g_0045D374 != 3) {
        func_002EAB50();
        func_00208FF0();
        func_0020F690();
        func_0021A4A0();
        func_00229140();
    }
}

/* 0x001C92D0, 0xBC bytes, matching. Draws the frame by scene kind. */
void func_001C92D0(int a)
{
    int k = g_0045D374;

    g_0045D378 = a;
    func_001C9070();
    if (k == 0)
        func_001C9E20(a);
    else if (k == 1)
        func_001C9FA0(a);
    else if (k == 2)
        func_001CA150(a);
    else if (k == 3)
        func_001CA2F0(a);
    else if (k == 4)
        func_001CA410(a);
    SP_LIST = 0;
}

void func_001C9A40(void);
void func_001C9A90(void);

/* 0x001C9870, 0x54 bytes. Draws list 4 alone. */
void func_001C9870(int a)
{
    if (g_0072D100 == 0)
        return;
    g_0045D378 = a;
    func_001C9070();
    func_001C9A40();
    SP_LIST = 4;
    func_001CA620();
    func_001C9A90();
    SP_LIST = 0;
}

/* 0x001C99B0, 0x84 bytes. Writes the end-of-list packet. */
u32 *func_001C99B0(u32 *p)
{
    p[0] = 0x10000002;
    p[1] = 0;
    p[2] = 0x13000000;
    p[3] = 0x51000002;
    *(u64 *)(p + 4) = 0x1000000000008001ULL;
    *(u64 *)(p + 6) = 0xE;
    *(u64 *)(p + 8) = (u64)func_00100FE0() | 0x3A000000;
    *(u64 *)(p + 10) = 0x4E;
    return p + 0xC;
}

/* 0x001C9A40, 0x48 bytes, matching. Writes the start-of-list packets. */
void func_001C9A40(void)
{
    SP_PKT = func_001CC580(func_001CCC00(SP_PKT), g_00408530, g_00408510, g_00408550);
}

/* 0x001C9A90, 0x28 bytes, matching. */
void func_001C9A90(void)
{
    SP_PKT = func_001C99B0(SP_PKT);
}

/* 0x001CB3D0, 0x14 bytes, matching. Gives back an entry of the first pool (0x110 bytes). */
void func_001CB3D0(u8 *p)
{
    *(int *)(p + 0xF8) = 0;
    g_0045D370++;
}

/* 0x001CB4A0, 0x14 bytes, matching. Of the second (0x120 bytes). */
void func_001CB4A0(u8 *p)
{
    *(int *)(p + 0xFC) = 0;
    g_0045D344++;
}

/* 0x001CB570, 0x14 bytes, matching. */
void func_001CB570(u8 *p)
{
    p[0x104] = 0;
    g_0045D364++;
}

/* 0x001CB640, 0x14 bytes, matching. */
void func_001CB640(u8 *p)
{
    *(int *)(p + 0x18) = 0;
    g_0045D35C++;
}

/* 0x001CB720, 0x14 bytes, matching. */
void func_001CB720(u8 *p)
{
    *(int *)(p + 0x1C) = 0;
    g_0045D354++;
}

/* 0x001CB7F0, 0x14 bytes, matching. */
void func_001CB7F0(u8 *p)
{
    *(int *)(p + 0x20) = 0;
    g_0045D34C++;
}

/* 0x001CB970, 0x64 bytes, matching. */
void func_001CB970(u8 *t, int a, int b, int c)
{
    u8 *img = func_00106F10(t);

    func_001068F0(img + *(u16 *)(img + 0xC), a, 1, 0, 0, 0, b, c);
}

/* 0x001CC7C0, 0x50 bytes. A packet calling VU1 block `q` (numbered). */
u32 *func_001CC7C0(u32 *p, u8 *q)
{
    *(u32 *)(q + 0xC) = SP_COUNT * 0x12 | 0x6C128000;
    p[0] = 0x30000013;
    p[1] = (u32)q;
    p[2] = 0;
    p[3] = 0;
    SP_COUNT++;
    return p + 4;
}

/* 0x001CC810, 0x70 bytes. */
u32 *func_001CC810(u32 a, u32 *p, u32 c)
{
    p[0] = 0x10000001;
    p[1] = 0;
    p[2] = 0x11000000;
    p[3] = 0x6C010018;
    p[4] = SP_COUNT;
    p[5] = a;
    p[6] = 0;
    p[7] = c;
    SP_COUNT = 0;
    p[8] = 0x10000000;
    p[9] = 0;
    p[10] = 0;
    p[11] = 0x17000000;
    return p + 0xC;
}

/* 0x001CC970, 0x2C bytes, matching. */
u32 *func_001CC970(u32 *p, u8 *q)
{
    *(u32 *)(q + 0xC) = 0x6C128004;
    p[0] = 0x30000013;
    p[1] = (u32)q;
    p[2] = 0;
    p[3] = 0;
    return p + 4;
}

/* 0x001CC9A0, 0x20 bytes, matching. */
u32 *func_001CC9A0(u32 *p)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x17000000;
    return p + 4;
}
