/*
 * draw_lists.c - the 3D draw lists (parts of 0x001C8780-0x001CC9BC): the frame's drawing by
 * scene kind (0x0045D374), the object pools' release, and the DMA/VIF packet pieces written to
 * the packet pointer kept in the scratchpad (0x70000158). Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_DRAW_LISTS_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern int g_0045D374, g_0045D378;       /* (small data) the scene kind, its argument */
extern int g_0045D344, g_0045D34C, g_0045D354, g_0045D35C, g_0045D364, g_0045D370;
extern int g_0072D100;
extern u8 g_00408510[], g_00408530[], g_00408550[];

#define SP_INT(a) (*(int *)(a))
#define SP_PKT (*(u32 **)PS2_PTR(0x70000158))      /* (scratchpad) the packet pointer */
#define SP_LIST SP_INT(0x70000D60)       /* (scratchpad) the list being drawn */
#define SP_COUNT SP_INT(0x70000D64)

void func_002EAB50(void);
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

/* 0x001C8780, 0x2C bytes, matching. */
int func_001C8780(int a, int b, int c, u32 d)
{
    int r;

    if (b != 0)
        r = func_001C7060(a, b, 0, c, d, 1);
    return r;                   /* undefined when b == 0, as in the original */
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

/* ---- The draw lists proper (parts of 0x001C8340-0x001CB960). Each list L (0x350 bytes from
 * 0x0072D130) has four object chains: +0xF4 (next at +0xF4), +0x22C (next at +0x11C), +0x33C
 * (next at +0x10C) and +0x344 (the objects added this frame, links +0x118/+0x11C); the frame's
 * passes draw the lists that are switched on (g_0072D0F0[L]). Objects keep two copies of their
 * matrices (+0x60 + buffer * 0x50, buffer = scratchpad 0x70000150). ---- */

extern u8 g_0072D130[];
extern int g_0072D0F0[16];               /* the lists switched on */
extern u8 *g_0072C870[];                 /* the loaded model files */
extern u8 g_00669D60[];
extern u8 *g_0045D2C0;                   /* (small data) the camera */
extern u8 *g_0045D340;                   /* (small data) the camera kept aside */
extern float g_0045D330;                 /* (small data) a fade */
extern int g_0045D37C;
extern int g_0045D328;                   /* (small data) the next trail slot */
extern u8 *g_006D3370[5];
extern u8 g_006D3390[0x240];             /* a camera copy */
extern u8 g_006D35D0[];
extern int g_0045D348, g_0045D350, g_0045D358, g_0045D360, g_0045D368, g_0045D36C;
extern struct { int c, a, b; } g_0045CD40[6];
extern u8 g_00728250[], g_00724C50[], g_00722A50[], g_0070DA50[], g_006D4DE0[], g_006D35E0[];
extern u8 g_0072CEB0[2][0x120];

#define SP_BUF SP_INT(0x70000150)
#define LIST(l) (g_0072D130 + (l) * 0x350)
#define HEAD(l, o) (*(u8 **)(LIST(l) + (o)))
#define NEXT(p, o) (*(u8 **)((p) + (o)))
#define FL34(p) (*(u32 *)((p) + 0x34))
#define FL38(p) (*(u32 *)((p) + 0x38))
#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))

typedef struct { u32 v[16]; } Mat16;

/* Draws with a copy of the camera (field of view 15 degrees). */
#define TEMP_CAMERA_BEGIN() do {                                        \
    g_0045D340 = g_0045D2C0;                                            \
    func_00118AC0((unsigned int *)(g_006D3390), g_0045D2C0, 0x240);                       \
    g_0045D2C0 = g_006D3390;                                            \
    *(u32 *)(g_006D3390 + 0x224) = 0x3E860A92;                          \
    *(u32 *)(g_006D3390 + 0x220) = 0;                                   \
    func_0017AC50(g_0045D2C0);                                          \
} while (0)
#define TEMP_CAMERA_END() do {                                          \
    g_0045D2C0 = g_0045D340;                                            \
    func_0017AC50(g_0045D2C0);                                          \
} while (0)

void func_0017AC50(u8 *cam);
u8 *func_001CB3F0(void);
void func_001C7560(int k, u8 *o, u32 f);
void func_001C6010(u8 *o);
int func_001C72F0(int k, int a, int b, int c);
u8 *func_001C7FC0(int k, int a, int b, u32 f);
int func_001C8BE0(int k, int x);
int func_001C73A0(int a, int b, int x, int c);
u32 *func_001CC9C0(u32 *p);
void func_001C9CB0(void);
void func_001C9D50(void);
u32 *func_001CCD20(u32 *p, int a, u32 b);
u32 *func_001CCA90(u32 *p, u8 *m);
u32 *func_001CCAC0(u32 *p);
u32 *func_001CCAE0(u32 *p);
u32 *func_001CCCD0(u32 *p);
u32 *func_001CC880(u32 *p, u8 *a, u8 *b, u8 *c);
u32 *func_00229340(u32 *p, int a, int b);
u32 *func_00229800(u32 *p);
u32 *func_00229A40(u32 *p, int k);
u32 *func_001CA720(u32 *p, u8 *o, int a);
u32 *func_002A81C0(int a, u32 *p, u8 *m, int b);
u32 *func_002A83C0(int a, u32 *p, u8 *m, int b);
void func_002AF470(int a, u8 *b, u8 *c, u8 *d);
void func_001C9AC0(void);
void func_001C9BB0(void);

/* Copies an object's current matrices to the other buffer. */
#define KEEP_MATRICES(o) (*(Mat16 *)((o) + (SP_BUF ^ 1) * 0x50 + 0x60) =    \
                          *(Mat16 *)((o) + SP_BUF * 0x50 + 0x60))

/* Adds object `o` to the current list's chain of new objects. */
#define LINK_NEW(o) do {                                                \
    u8 *l_ = LIST(SP_LIST);                                             \
    NEXT(*(u8 **)(l_ + 0x344), 0x11C) = (o);                            \
    NEXT(o, 0x118) = *(u8 **)(l_ + 0x344);                              \
    *(u8 **)(l_ + 0x344) = (o);                                         \
    NEXT(o, 0x11C) = 0;                                                 \
} while (0)

/* 0x001C8340, 0x170 bytes. A new object drawing model `m` of file `k` (part `a`). */
u8 *func_001C8340(int k, u8 *m, int a, u32 f)
{
    u8 *o = 0;

    if (m != 0 && g_0072C870[k] != 0 && (o = func_001CB3F0()) != 0) {
        *(u8 **)(o + 0xF0) = m;
        *(int *)(o + 0xF4) = a;
        *(int *)(o + 0xF8) = 0;
        *(int *)(o + 0x110) = 0x40;
        *(int *)(o + 0x114) = 0x40;
        FL34(o) = f;
        func_001C7560(k, o, f & 0x10);
        if ((f & 0x4000) != 0) {
            *(int *)(o + 0x3C) = -1;
            FL34(o) &= ~0x4000;
        }
        func_001C6010(o);
        KEEP_MATRICES(o);
        LINK_NEW(o);
    }
    return o;
}

/* 0x001C84B0, 0x170 bytes. The same with the other part field. */
u8 *func_001C84B0(int k, u8 *m, int a, u32 f)
{
    u8 *o = 0;

    if (m != 0 && g_0072C870[k] != 0 && (o = func_001CB3F0()) != 0) {
        *(u8 **)(o + 0xF0) = m;
        *(int *)(o + 0xF4) = 0;
        *(int *)(o + 0xF8) = a;
        *(int *)(o + 0x110) = 0x40;
        *(int *)(o + 0x114) = 0x40;
        FL34(o) = f;
        func_001C7560(k, o, f & 0x10);
        if ((f & 0x4000) != 0) {
            *(int *)(o + 0x3C) = -1;
            FL34(o) &= ~0x4000;
        }
        func_001C6010(o);
        KEEP_MATRICES(o);
        LINK_NEW(o);
    }
    return o;
}

/* 0x001C8620, 0x158 bytes. Sets up the caller's object `o` (or, already set up, drops it). */
void func_001C8620(u8 *o, int k, u8 *m, int a, u32 f)
{
    if (*(int *)(o + 0xFC) != 0) {
        FL38(o) |= 8;
        return;
    }
    if (m != 0 && g_0072C870[k] != 0 && o != 0) {
        *(int *)(o + 0xFC) = 1;
        *(u8 **)(o + 0xF0) = m;
        *(int *)(o + 0xF4) = a;
        *(int *)(o + 0xF8) = 0;
        *(int *)(o + 0x110) = 0x40;
        *(int *)(o + 0x114) = 0x40;
        FL34(o) = f | 0x8000000;
        func_001C7560(k, o, f & 0x10);
        if ((f & 0x4000) != 0) {
            *(int *)(o + 0x3C) = -1;
            FL34(o) &= ~0x4000;
        }
        func_001C6010(o);
        KEEP_MATRICES(o);
        LINK_NEW(o);
    }
}

/* 0x001C8130, 0x210 bytes. A unit's effect object (some kinds use one of five trail slots). */
void func_001C8130(int k, int a, int b, u32 f, int u)
{
    int trail = 0, c = b, x = a;
    u8 *o, *p;

    if (k == 3) {
        trail = 1;
        c = 4;
    } else if (k == 5 || k == 0xF0 || k == 0x52 || k == 0x50 || k == 0x54 || k == 0x53
               || k == 0x4E || k == 0x4D || k == 2 || k == 1) {
        trail = 0;
        x = 0;
    } else if (k == 0x56 || k == 0x55 || k == 4) {
        trail = 1;
        x = 0;
    }
    if (func_001C72F0(k, x, c, u) == 0)
        return;
    if (func_001C8BE0(0, a) == 0)
        return;
    if (func_0016C040((u8 *)PS2_PTR(0x574DE0) + u * 0x630) != 0)
        f |= 0x200;
    o = func_001C7FC0(k, a, b, f | 1);
    if (o == 0)
        return;
    *(int *)(o + 0x104) = u;
    FL34(o) &= ~1;
    if (trail != 0) {
        *(int *)(o + 0x108) = g_0045D328;
        p = g_006D3370[g_0045D328];
        if (p != 0)
            FL34(p) |= 0x800;
        p = (u8 *)&g_006D3370[g_0045D328];
        g_0045D328 = (g_0045D328 + 1) % 5;
        *(u8 **)p = o;
    }
}

/* 0x001C8870, 0xD8 bytes, matching. Drops every object of list `l`. */
void func_001C8870(int l)
{
    int keep = SP_LIST;
    u8 *o;

    SP_LIST = l;
    for (o = HEAD(l, 0xF4); o != 0; o = NEXT(o, 0xF4))
        FL38(o) |= 8;
    for (o = HEAD(l, 0x22C); o != 0; o = NEXT(o, 0x11C))
        FL38(o) |= 8;
    for (o = HEAD(l, 0x33C); o != 0; o = NEXT(o, 0x10C))
        FL38(o) |= 8;
    func_001C1230();
    func_001C1230();
    func_001C1230();
    SP_LIST = keep;
}

/* 0x001C8950, 0xA4 bytes. Hides every object of list `l`. */
void func_001C8950(int l)
{
    u8 *o;

    for (o = HEAD(l, 0xF4); o != 0; o = NEXT(o, 0xF4))
        FL34(o) |= 0x800;
    for (o = HEAD(l, 0x22C); o != 0; o = NEXT(o, 0x11C))
        FL34(o) |= 0x800;
    for (o = HEAD(l, 0x33C); o != 0; o = NEXT(o, 0x10C))
        FL34(o) |= 0x800;
}

/* 0x001C8A00, 0x130 bytes. Draws the frame by scene kind, then steps the fade. */
void func_001C8A00(void)
{
    int kind = g_0045D374, flag = 0, h;

    h = func_00102360(0x16E68, (void *)PS2_PTR(0x1C9060), &flag);
    if (kind == 0)
        func_001C0610();
    else if (kind == 1)
        func_001C06E0();
    else if (kind == 2)
        func_001C07A0();
    else if (kind == 3)
        func_001C08B0();
    else if (kind == 4)
        func_001C0940();
    func_00102340((void *)PS2_PTR(h));
    if (1.0f <= g_0045D330)
        g_0045D37C = 0;
    else
        g_0045D330 += 0.04f;
    if (flag != 0) {
        g_0045D330 = 0.0f;
        g_0045D37C = 1;
    }
    SP_LIST = 0;
}

/* 0x001C8BE0, 0x108 bytes. */
int func_001C8BE0(int k, int x)
{
    if (k < 6) {
        if (k == 0)
            return func_001C73A0(g_0045CD40[0].a, g_0045CD40[0].b, x, g_0045CD40[0].c);
        if (k == 5)
            return func_001C73A0(g_0045CD40[5].a, g_0045CD40[5].b, x, g_0045CD40[5].c);
    }
    if (k == 1)
        return func_001C73A0(g_0045CD40[1].a, g_0045CD40[1].b, x, g_0045CD40[1].c);
    if (k == 4)
        return func_001C73A0(g_0045CD40[4].a, g_0045CD40[4].b, x, g_0045CD40[4].c);
    if (k == 2)
        return func_001C73A0(g_0045CD40[2].a, g_0045CD40[2].b, x, g_0045CD40[2].c);
    if (k == 3)
        return func_001C73A0(g_0045CD40[3].a, g_0045CD40[3].b, x, g_0045CD40[3].c);
    return 1;
}

/* 0x001C8ED0, 0x184 bytes. Drops the objects belonging to side `s`. */
void func_001C8ED0(u8 s)
{
    u8 *o, *u;
    int v;

    for (o = HEAD(1, 0xF4); o != 0; o = NEXT(o, 0xF4)) {
        if (*(u32 *)(o + 0x104) == s)
            FL38(o) |= 0x10;
    }
    for (o = HEAD(0, 0x33C); o != 0; o = NEXT(o, 0x10C)) {
        u = *(u8 **)(o + 0xF0);
        if (u != 0 && u[0x14E] == s) {
            v = *(int *)(o + 0x24);
            if (v == 0x42 || v == 0x41 || v == 0x40 || v == 0x3F || v == 0x3E || v == 0x3D
                || v == 0x3C || v == 0x3B || v == 0x20 || v == 0x1D) {
                if (u[0x14E] > 1)
                    FL38(o) |= 0x10;
            } else {
                FL38(o) |= 0x10;
            }
        }
    }
    for (o = HEAD(3, 0x33C); o != 0; o = NEXT(o, 0x10C)) {
        u = *(u8 **)(o + 0xF0);
        if (u != 0 && u[0x14E] == s)
            FL38(o) |= 0x10;
    }
}

#define BATTLE_PAUSED() ((GAME_FLAGS & 0x20000) != 0 || (GAME_FLAGS & 0x40000) != 0)

/* 0x001C9390, 0x140 bytes. Draws lists 6, 14 and 10. */
void func_001C9390(void)
{
    int paused = BATTLE_PAUSED();

    if (!paused && (GAME_FLAGS & 0x100000) == 0 && (g_0072D0F0[6] != 0 || g_0072D0F0[14] != 0)) {
        SP_PKT = func_001CCC00(SP_PKT);
        if (g_0072D0F0[6] != 0) {
            SP_PKT = func_001CC9C0(SP_PKT);
            SP_LIST = 6;
            func_001C9CB0();
        }
        if (g_0072D0F0[14] != 0)
            func_001C9D50();
        if (g_0072D0F0[6] != 0 || g_0072D0F0[14] != 0)
            func_001C9A90();
    }
    if (!paused && g_0072D0F0[10] != 0) {
        func_001C9A40();
        SP_LIST = 10;
        func_001CA620();
        func_001C9A90();
    }
    SP_LIST = 0;
}

/* 0x001C94D0, 0xE4 bytes. Draws list 7 with its own camera. */
void func_001C94D0(int a)
{
    int paused = BATTLE_PAUSED();

    if (!paused && (GAME_FLAGS & 0x100000) == 0 && g_0072D0F0[7] != 0) {
        SP_LIST = 7;
        g_0045D378 = a;
        TEMP_CAMERA_BEGIN();
        func_001C9070();
        func_001C9A40();
        func_001CA620();
        func_001C9A90();
        TEMP_CAMERA_END();
        SP_LIST = 0;
    }
}

/* 0x001C98D0, 0xD8 bytes. Packets for object `o`'s meshes (matrix, then each mesh). */
u32 *func_001C98D0(u32 *p, u8 *o)
{
    u8 *m;

    if ((FL38(o) & 0xC) != 0)
        return p;
    for (m = *(u8 **)(o + 0x18); m != 0; m = NEXT(m, 0x264)) {
        p[0] = 0x30000005;
        p[1] = (u32)(o + SP_BUF * 0x50 + 0x50);
        p[2] = 0;
        p[3] = 0;
        p = func_001CCD20(p + 4, *(int *)(m + 0x27C), *(u32 *)(m + 0x270));
        p = func_001CCD20(p, *(int *)(m + 0x27C), *(u32 *)(m + 0x270));
        p = func_001CCA90(p, m + SP_BUF * 0x130);
        p = func_001CCAC0(p);
    }
    return p;
}

/* 0x001C9AC0, 0xE4 bytes. Draws list 3 (the shadowed objects?). */
void func_001C9AC0(void)
{
    u32 *p;
    u8 *o;

    SP_LIST = 3;
    p = func_00229340(SP_PKT, 2, 0x6F);
    for (o = HEAD(3, 0x22C); o != 0; o = NEXT(o, 0x11C)) {
        p = func_00229800(p);
        p = func_001CCCD0(p);
        p = func_001CA720(p, o, 0);
        p = func_00229A40(p, *(int *)(o + 0x24));
    }
    for (o = HEAD(3, 0x33C); o != 0; o = NEXT(o, 0x10C)) {
        p = func_00229800(p);
        p = func_001CCCD0(p);
        p = func_001CA720(p, o, 0);
        p = func_00229A40(p, *(int *)(o + 0x24));
    }
    SP_PKT = func_001CCCD0(p);
}

/* 0x001C9BB0, 0xF8 bytes. Draws list 13. */
void func_001C9BB0(void)
{
    u32 *p;
    u8 *o, *m;

    SP_LIST = 0xD;
    if (HEAD(13, 0x22C) == 0)
        return;
    p = func_001CC880(SP_PKT, g_00408530, g_00408510, g_00408550);
    for (o = HEAD(13, 0x22C); o != 0; o = NEXT(o, 0x11C)) {
        if ((FL34(o) & 0x20000000) == 0 && (m = *(u8 **)(o + 0x18)) != 0) {
            p = func_001CCD20(p, *(int *)(m + 0x27C), *(u32 *)(m + 0x270));
            p = func_002A81C0(*(int *)(o + 0x2C), p, m + SP_BUF * 0x130, *(int *)(m + 0x2A4));
        }
    }
    SP_PKT = (u32 *)PS2_PTR(func_0024FA80(PS2_ADDR(p)));
}

/* 0x001C9CB0, 0x9C bytes. */
void func_001C9CB0(void)
{
    u32 *p = SP_PKT;
    u8 *o;

    for (o = HEAD(SP_LIST, 0xF4); o != 0; o = NEXT(o, 0xF4))
        p = func_001C98D0(p, o);
    for (o = HEAD(SP_LIST, 0x22C); o != 0; o = NEXT(o, 0x11C))
        p = func_001C98D0(p, o);
    SP_PKT = p;
}

/* 0x001C9D50, 0xC4 bytes. Draws list 14. */
void func_001C9D50(void)
{
    u32 *p, *q;
    u8 *o, *m;

    SP_LIST = 0xE;
    p = SP_PKT;
    if (HEAD(14, 0x22C) != 0) {
        p = func_001CCAE0(p);
        for (o = HEAD(14, 0x22C); o != 0; o = NEXT(o, 0x11C)) {
            m = *(u8 **)(o + 0x18);
            if (m != 0) {
                q = func_001CCD20(p, *(int *)(m + 0x27C), *(u32 *)(m + 0x270));
                p = func_002A83C0(*(int *)(o + 0x2C), q, m + SP_BUF * 0x130, *(int *)(m + 0x2A4));
            }
        }
    }
    SP_PKT = p;
}

#define DRAW_LIST(l) do {                                               \
    if (g_0072D0F0[l] != 0) {                                           \
        SP_LIST = (l);                                                  \
        func_001CA620();                                                \
    }                                                                   \
} while (0)

/* List 5 with its own camera. */
#define DRAW_LIST5() do {                                               \
    if (g_0072D0F0[5] != 0) {                                           \
        SP_LIST = 5;                                                    \
        TEMP_CAMERA_BEGIN();                                            \
        func_001C9070();                                                \
        func_001C9A40();                                                \
        func_001CA620();                                                \
        TEMP_CAMERA_END();                                              \
    }                                                                   \
} while (0)

#define DRAW_LIST3(a) do {                                              \
    if (g_0072D0F0[3] != 0) {                                           \
        func_001C9AC0();                                                \
        func_002AF470((a), g_00408550, g_00408530, g_006D35D0);         \
    }                                                                   \
} while (0)

/* 0x001C9E20, 0x174 bytes. A frame's passes (first order). */
void func_001C9E20(int a)
{
    func_001C9A40();
    DRAW_LIST(2);
    DRAW_LIST(0);
    DRAW_LIST(1);
    DRAW_LIST5();
    func_0024FA00();
    func_002AF340(a, (float *)(g_006D35D0));
    DRAW_LIST3(a);
    if (g_0072D0F0[13] != 0)
        func_001C9BB0();
    func_001C9260();
    func_001C9A90();
}

/* 0x001C9FA0, 0x1A4 bytes. */
void func_001C9FA0(int a)
{
    func_001C9A40();
    DRAW_LIST(2);
    DRAW_LIST(0);
    DRAW_LIST(1);
    if (g_0072D0F0[9] != 0) {
        SP_LIST = 9;
        func_001CA620();
        func_002AF340(a, (float *)(g_006D35D0));
    }
    func_0024FA00();
    func_002AF340(a, (float *)(g_006D35D0));
    DRAW_LIST5();
    DRAW_LIST3(a);
    if (g_0072D0F0[13] != 0)
        func_001C9BB0();
    func_001C9260();
    func_001C9A90();
}

/* 0x001CA150, 0x194 bytes. */
void func_001CA150(int a)
{
    func_001C9A40();
    DRAW_LIST(2);
    DRAW_LIST(0);
    DRAW_LIST(1);
    DRAW_LIST(9);
    func_0024FA00();
    func_002AF340(a, (float *)(g_006D35D0));
    DRAW_LIST5();
    DRAW_LIST3(a);
    if (g_0072D0F0[13] != 0)
        func_001C9BB0();
    func_001C9260();
    func_001C9A90();
}

/* 0x001CA2F0, 0x118 bytes. */
void func_001CA2F0(int a)
{
    func_001C9A40();
    DRAW_LIST(9);
    DRAW_LIST(2);
    DRAW_LIST(0);
    DRAW_LIST(1);
    func_0024FA00();
    func_002AF340(a, (float *)(g_006D35D0));
    DRAW_LIST3(a);
    if (g_0072D0F0[13] != 0)
        func_001C9BB0();
    func_001C9260();
    func_001C9A90();
}

/* 0x001CA410, 0x108 bytes. */
void func_001CA410(int a)
{
    func_001C9A40();
    DRAW_LIST(2);
    DRAW_LIST(11);
    func_002AF340(a, (float *)(g_006D35D0));
    SP_LIST = 0xC;
    TEMP_CAMERA_BEGIN();
    func_001C9070();
    func_001C9A40();
    func_001CA620();
    TEMP_CAMERA_END();
    func_002AF470(a, g_00408550, g_00408530, g_006D35D0);
    func_001C9A90();
}

/* 0x001CA620, 0xF4 bytes. Draws the current list's objects. */
void func_001CA620(void)
{
    u32 *p = SP_PKT;
    u8 *o;

    for (o = HEAD(SP_LIST, 0xF4); o != 0; o = NEXT(o, 0xF4)) {
        if ((FL34(o) & 0x20000000) == 0)
            p = func_001CA720(p, o, 0);
    }
    for (o = HEAD(SP_LIST, 0x22C); o != 0; o = NEXT(o, 0x11C)) {
        if ((FL34(o) & 0x20000000) == 0)
            p = func_001CA720(p, o, *(int *)(o + 0xF4));
    }
    for (o = HEAD(SP_LIST, 0x33C); o != 0; o = NEXT(o, 0x10C))
        p = func_001CA720(p, o, 0);
    SP_PKT = p;
}

/* 0x001CAF50, 0x98 bytes. Draws object `o` alone with its own camera. */
void func_001CAF50(u8 *o)
{
    TEMP_CAMERA_BEGIN();
    func_001C9070();
    func_001C9A40();
    SP_PKT = func_001CA720(SP_PKT, o, *(int *)(o + 0xF4));
    func_001C9A90();
    TEMP_CAMERA_END();
}

/* A matrix packet header (UNPACK of 4 qwords). */
#define MATRIX_HEADER(p) do {                                           \
    *(u32 *)((p) + 0x50) = 0; *(u32 *)((p) + 0x54) = 0;                 \
    *(u32 *)((p) + 0x58) = 0x11000000; *(u32 *)((p) + 0x5C) = 0x6C040013; \
    *(u32 *)((p) + 0xA0) = 0; *(u32 *)((p) + 0xA4) = 0;                 \
    *(u32 *)((p) + 0xA8) = 0x11000000; *(u32 *)((p) + 0xAC) = 0x6C040013; \
} while (0)

/* A mesh's two packet buffers (GIF tag and identity scales). */
#define MESH_BUFFERS(p) do {                                            \
    u8 *b_ = (p);                                                       \
    u32 j_;                                                             \
    for (j_ = 0; j_ < 2; j_++, b_ += 0x130) {                           \
        *(u32 *)(b_ + 0) = 0; *(u32 *)(b_ + 4) = 0;                     \
        *(u32 *)(b_ + 8) = 0x11000000;                                  \
        *(u64 *)(b_ + 0x60) = 0x303E400000008004ULL;                    \
        *(u64 *)(b_ + 0x68) = 0x412;                                    \
        *(float *)(b_ + 0x9C) = 1.0f; *(float *)(b_ + 0x78) = 1.0f; *(u32 *)(b_ + 0x7C) = 0; \
        *(float *)(b_ + 0xCC) = 1.0f; *(float *)(b_ + 0xA8) = 1.0f; *(u32 *)(b_ + 0xAC) = 0; \
        *(float *)(b_ + 0xFC) = 1.0f; *(float *)(b_ + 0xD8) = 1.0f; *(u32 *)(b_ + 0xDC) = 0; \
        *(float *)(b_ + 0x12C) = 1.0f; *(float *)(b_ + 0x108) = 1.0f; *(u32 *)(b_ + 0x10C) = 0; \
    }                                                                   \
} while (0)

void func_001CB810(u8 *p, int k);

/* 0x001CAFF0, 0x328 bytes. Clears the object pools. */
void func_001CAFF0(void)
{
    u32 k;
    u8 *p;

    g_0045D370 = 0x40;
    g_0045D36C = 0;
    g_0045D344 = 0x30;
    g_0045D368 = 0;
    g_0045D364 = 0x20;
    g_0045D360 = 0;
    g_0045D35C = 0x60;
    g_0045D358 = 0;
    g_0045D354 = 0xFF;
    g_0045D350 = 0;
    g_0045D34C = 0x80;
    g_0045D348 = 0;
    for (k = 0, p = g_00728250; k < 0x40; k++, p += 0x110) {
        func_00118850(p, 0x110);
        *(u32 *)(p + 0xFC) = k;
        MATRIX_HEADER(p);
    }
    for (k = 0, p = g_00724C50; k < 0x30; k++, p += 0x120) {
        func_00118850(p, 0x120);
        *(u32 *)(p + 0x100) = k;
        MATRIX_HEADER(p);
    }
    for (k = 0, p = g_00722A50; k < 0x20; k++, p += 0x110) {
        func_00118850(p, 0x110);
        *(u32 *)(p + 0x100) = k;
        MATRIX_HEADER(p);
    }
    for (k = 0, p = g_0070DA50; k < 0x60; k++, p += 0x380) {
        func_00118850(p, 0x380);
        *(u32 *)(p + 0x1C) = k;
        MESH_BUFFERS(p + 0x20);
    }
    for (k = 0, p = g_006D4DE0; k < 0xFF; k++, p += 0x390) {
        func_00118850(p, 0x390);
        *(u32 *)(p + 0x20) = k;
        MESH_BUFFERS(p + 0x30);
    }
    for (k = 0, p = g_006D35E0; k < 0x80; k++, p += 0x30) {
        func_00118850(p, 0x30);
        *(u32 *)(p + 0x24) = k;
    }
    for (k = 0; k < 2; k++)
        func_001CB810(g_0072CEB0[k], 0x30);
}

/* Takes a free record from a pool (from the cursor on, wrapping). */
#define POOL_TAKE(pool, size, used, utype, index, last, cursor, left, min) do {     \
    u8 *p_;                                                                         \
    if ((u32)(left) < (min))                                                        \
        return 0;                                                                   \
    p_ = (pool) + (cursor) * (size);                                                \
    while (*(utype *)(p_ + (used)) != 0) {                                          \
        if (*(u32 *)(p_ + (index)) < (last))                                        \
            p_ += (size);                                                           \
        else                                                                        \
            p_ = (pool);                                                            \
    }                                                                               \
    *(utype *)(p_ + (used)) = 1;                                                    \
    if (*(u32 *)(p_ + (index)) < (last))                                            \
        (cursor) = *(u32 *)(p_ + (index)) + 1;                                      \
    else                                                                            \
        (cursor) = 0;                                                               \
    (left)--;                                                                       \
    return p_;                                                                      \
} while (0)

/* 0x001CB320, 0xAC bytes. */
u8 *func_001CB320(void)
{
    POOL_TAKE(g_00728250, 0x110, 0xF8, int, 0xFC, 0x3F, g_0045D36C, g_0045D370, 6);
}

/* 0x001CB3F0, 0xA8 bytes. */
u8 *func_001CB3F0(void)
{
    POOL_TAKE(g_00724C50, 0x120, 0xFC, int, 0x100, 0x2F, g_0045D368, g_0045D344, 1);
}

/* 0x001CB4C0, 0xA8 bytes. */
u8 *func_001CB4C0(void)
{
    POOL_TAKE(g_00722A50, 0x110, 0x104, char, 0x100, 0x1F, g_0045D360, g_0045D364, 1);
}

/* 0x001CB590, 0xAC bytes. */
u8 *func_001CB590(void)
{
    POOL_TAKE(g_0070DA50, 0x380, 0x18, int, 0x1C, 0x5F, g_0045D358, g_0045D35C, 6);
}

/* 0x001CB660, 0xB4 bytes. */
u8 *func_001CB660(void)
{
    POOL_TAKE(g_006D4DE0, 0x390, 0x1C, int, 0x20, 0xFE, g_0045D350, g_0045D354, 0x15);
}

/* 0x001CB740, 0xA8 bytes. */
u8 *func_001CB740(void)
{
    POOL_TAKE(g_006D35E0, 0x30, 0x20, int, 0x24, 0x7F, g_0045D348, g_0045D34C, 1);
}

/* 0x001CB810, 0x64 bytes, matching. */
void func_001CB810(u8 *p, int k)
{
    func_00118850(p, 0x120);
    *(int *)(p + 0x100) = k;
    MATRIX_HEADER(p);
}

/* 0x001CB880, 0xE8 bytes. The size in qwords of a `w` x `h` image of GS pixel format `f`. */
int func_001CB880(int f, int w, int h)
{
    if (f == 0x2C || f == 0x24 || f == 0x14)
        return w * h >> 5;
    if (f == 0x1B || f == 0x13)
        return w * h >> 4;
    if (f == 0x3A || f == 0x32 || f == 10 || f == 2)
        return w * h >> 3;
    if (f == 0x31 || f == 1)
        return w * h * 3 >> 4;
    if (f == 0x30 || f == 0)
        return w * h >> 2;
    return 0;
}

/* ---- Texture tables and VIF/GIF packet pieces (parts of 0x001CB9E0-0x001CD05C). The packet
 * writer caches the last texture (0x0045CD8C), light set (0x0045CD88) and fog flag
 * (0x0045CD90) to skip repeated state. ---- */

extern int g_0045CD88, g_0045CD8C, g_0045CD90, g_0045CD94;
extern u8 *g_0045D384, *g_0045D388, *g_0045D38C;      /* (small data) texture files being set up */
extern u8 g_00426070[];                  /* texture id -> kind (0x11: none) */
extern int g_00426230[0x11], g_00426280[0x3F];
extern u8 g_004261C0[0x6F];
extern u64 g_0040C3F0[0x6F];             /* TEX0 values */
extern u8 *g_0072C760[0x3F];
extern u8 *g_0072C82C[0x11];
extern u8 g_00426420[], g_00426560[], g_00426580[], g_00426380[], g_004263F0[];
extern u8 g_003FCEB0[], g_003FFF70[], g_003FF550[], g_00400280[];
extern u32 g_0040C770[4], g_0040C780[4];
extern u32 g_007302E0[0x1C];
extern u8 g_006A3A30[][0xC0];

#define TEX_SIZE(k, n) ((int)(k) < (n) ? g_00426230[k] : 0x169)

/* 0x001CB9E0, 0x1B8 bytes. Uploads the common textures, then sets the TEX0 table. */
void func_001CB9E0(void)
{
    u32 k;
    u8 **e;

    func_00103000(0);
    if (g_0045D38C != 0) {
        e = (u8 **)(g_0045D38C + 4);
        for (k = 0; k < 9; k++)
            e[k * 2] += (u32)g_0045D38C;
        e = (u8 **)(g_0045D38C + 4);
        for (k = 2; k < 9; k++, e += 2)
            func_00107440(*e, TEX_SIZE(k, 0x11) << 5, 0);
        for (k = 0; k < 2; k++, e += 2)
            func_00107440(*e, TEX_SIZE(k, 0x11) << 5, 0);
        func_00102EC0(g_0045D38C);
        g_0045D38C = 0;
    }
    for (k = 0; k < 0x6F; k++) {
        u8 b = g_004261C0[k];

        if (b == 0x3F)
            g_0040C3F0[k] |= 0x2840000000000ULL;
        else
            g_0040C3F0[k] |= (u64)(long long)(b < 0x3F ? g_00426280[b] : 0x14) << 0x25;
    }
    func_00103000(1);
}

/* 0x001CBCE0, 0x2D0 bytes. Sets up the two sets of model textures. */
void func_001CBCE0(void)
{
    u32 *keep = SP_PKT;
    u32 k;
    u8 **e;

    func_00103000(0);
    if (g_0045D388 != 0) {
        e = (u8 **)(g_0045D388 + 4);
        for (k = 0; k < 0x18; k++)
            e[k * 2] += (u32)g_0045D388;
        e = (u8 **)(g_0045D388 + 4);
        for (k = 0; k < 0x18; k++, e += 2) {
            if ((int)k < 0x3F)
                g_0072C760[k] = *e;
            func_001CB970(*e, (int)k < 0x3F ? g_00426280[k] : 0x14, 8, 2);
        }
    }
    if (g_0045D384 != 0) {
        e = (u8 **)(g_0045D384 + 4);
        for (k = 0; k < 0x27; k++)
            e[k * 2] += (u32)g_0045D384;
        e = (u8 **)(g_0045D384 + 4);
        for (k = 0x18; k < 0x3F; k++, e += 2) {
            if ((int)k < 0x3F)
                g_0072C760[k] = *e;
            func_001CB970(*e, (int)k < 0x3F ? g_00426280[k] : 0x14, 0x10, 0x10);
        }
    }
    SP_PKT = keep;
    if (g_0045D388 != 0) {
        func_00102EC0(g_0045D388);
        g_0045D388 = 0;
    }
    if (g_0045D384 != 0) {
        func_00102EC0(g_0045D384);
        g_0045D384 = 0;
    }
    func_00103000(1);
}

/* 0x001CC220, 0x188 bytes. Selects texture `k` (TEX0). */
u32 *func_001CC220(u32 *p, int k)
{
    u8 b;
    u8 *t;
    long long v;

    if (k == g_0045CD8C)
        return p;
    b = g_00426070[k];
    p[0] = 0x10000002;
    p[1] = 0;
    p[2] = 0x13000000;
    p[3] = 0x51000002;
    *(u64 *)(p + 4) = 0x1000000000008001ULL;
    *(u64 *)(p + 6) = 0xE;
    if (b == 0x11) {
        *(u64 *)(p + 8) = g_0040C3F0[k];
    } else {
        t = 0;
        if (b > 0xC && b < 0x11)
            t = g_0072C82C[b];
        v = func_00106F40(t) == 0x100 ? 8 : 7;
        *(u64 *)(p + 8) = (u64)(v << 0x1E) | g_0040C3F0[k];
    }
    *(u64 *)(p + 10) = 6;
    g_0045CD8C = k;
    return p + 0xC;
}

/* 0x001CC3B0, 0x98 bytes. Selects the light set of flags `f` (bits 16-25). */
u32 *func_001CC3B0(u32 *p, u32 f)
{
    u32 k = 10, j;

    for (j = 0; j < 10; j++) {
        if ((f >> 0x10 & 0x3FF & 1 << (j & 0x1F)) != 0) {
            k = j;
            break;
        }
    }
    if (k != (u32)g_0045CD88) {
        g_0045CD88 = k;
        p[0] = 0x30000002;
        p[1] = (u32)(g_00426420 + k * 0x20);
        p[2] = 0x13000000;
        p[3] = 0x51000002;
        p += 4;
    }
    return p;
}

/* 0x001CC450, 0xA4 bytes. Switches fog (flag 0x10). */
u32 *func_001CC450(u32 *p, u32 f)
{
    f &= 0x10;
    if ((f != 0 && g_0045CD90 == 0) || (f == 0 && g_0045CD90 != 0)) {
        p[0] = 0x30000002;
        p[1] = f == 0 ? (u32)g_00426580 : (u32)g_00426560;
        p[2] = 0x13000000;
        p[3] = 0x51000002;
        p += 4;
        g_0045CD90 = f;
    }
    return p;
}

/* 0x001CC500, 0x7C bytes. The shadow matrices block (scratchpad matrix, then `a` and `b`). */
void func_001CC500(u32 *a, u32 *b)
{
    int k;

    g_007302E0[0] = 0;
    g_007302E0[1] = 0;
    g_007302E0[2] = 0x11000000;
    g_007302E0[3] = 0x6C060000;
    for (k = 0; k < 16; k++)
        g_007302E0[4 + k] = ((u32 *)PS2_PTR(0x70000000))[k];
    for (k = 0; k < 4; k++)
        g_007302E0[20 + k] = a[k];
    for (k = 0; k < 4; k++)
        g_007302E0[24 + k] = b[k];
}

#define CAM_COPY(p, o, n) do {                                          \
    int k_;                                                             \
    for (k_ = 0; k_ < (n); k_++)                                        \
        (p)[k_] = *(u32 *)(g_0045D2C0 + (o) + k_ * 4);                  \
} while (0)

#define QCOPY(p, s) do {                                                \
    (p)[0] = (s)[0]; (p)[1] = (s)[1]; (p)[2] = (s)[2]; (p)[3] = (s)[3];  \
} while (0)

#define PACKET_END(p) do {                                              \
    (p)[0] = 0x10000000; (p)[1] = 0; (p)[2] = 0; (p)[3] = 0x14000000;   \
} while (0)

/* 0x001CC580, 0x140 bytes. The shadow pass's microcode and camera block. */
u32 *func_001CC580(u32 *p, u8 *a, u8 *b, u8 *c)
{
    p[0] = 0x50000000;
    p[1] = (u32)g_003FCEB0;
    p[2] = 0x11000000;
    p[3] = 0;
    p[4] = 0x30000007;
    p[5] = (u32)g_007302E0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x1000000D;
    p[9] = 0;
    p[10] = 0x11000000;
    p[11] = 0x6C0D0006;
    CAM_COPY(p + 0xC, 0x100, 16);
    CAM_COPY(p + 0x1C, 0xC0, 16);
    CAM_COPY(p + 0x2C, 0x1C0, 4);
    CAM_COPY(p + 0x30, 0x1D0, 4);
    QCOPY(p + 0x34, (u32 *)a);
    QCOPY(p + 0x38, (u32 *)b);
    QCOPY(p + 0x3C, (u32 *)c);
    PACKET_END(p + 0x40);
    return p + 0x44;
}

/* 0x001CC880, 0xEC bytes. Another pass's microcode and camera block. */
u32 *func_001CC880(u32 *p, u8 *a, u8 *b, u8 *c)
{
    p[0] = 0x50000000;
    p[1] = (u32)g_003FFF70;
    p[2] = 0x11000000;
    p[3] = 0;
    p[4] = 0x1000000B;
    p[5] = 0;
    p[6] = 0x11000000;
    p[7] = 0x6C0B0000;
    CAM_COPY(p + 8, 0x100, 16);
    CAM_COPY(p + 0x18, 0x140, 16);
    QCOPY(p + 0x28, (u32 *)a);
    QCOPY(p + 0x2C, (u32 *)b);
    QCOPY(p + 0x30, (u32 *)c);
    PACKET_END(p + 0x34);
    return p + 0x38;
}

/* 0x001CC9C0, 0xCC bytes. */
u32 *func_001CC9C0(u32 *p)
{
    p[0] = 0x50000000;
    p[1] = (u32)g_003FF550;
    p[2] = 0x11000000;
    p[3] = 0;
    p[4] = 0x10000001;
    p[5] = 0;
    p[6] = 0x11000000;
    p[7] = 0x6C010000;
    QCOPY(p + 8, g_0040C770);
    PACKET_END(p + 0xC);
    return p + 0x10;
}

/* 0x001CCA90, 0x2C bytes, matching. Sends mesh buffer `m`. */
u32 *func_001CCA90(u32 *p, u8 *m)
{
    *(u32 *)(m + 0xC) = 0x6C128000;
    p[0] = 0x30000013;
    p[1] = (u32)m;
    p[2] = 0;
    p[3] = 0;
    return p + 4;
}

/* 0x001CCAC0, 0x20 bytes, matching. */
u32 *func_001CCAC0(u32 *p)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x17000000;
    return p + 4;
}

/* 0x001CCAE0, 0xCC bytes. */
u32 *func_001CCAE0(u32 *p)
{
    p[0] = 0x50000000;
    p[1] = (u32)g_00400280;
    p[2] = 0x11000000;
    p[3] = 0;
    p[4] = 0x10000001;
    p[5] = 0;
    p[6] = 0x11000000;
    p[7] = 0x6C010000;
    QCOPY(p + 8, g_0040C780);
    PACKET_END(p + 0xC);
    return p + 0x10;
}

/* 0x001CCBB0, 0x2C bytes, matching. */
u32 *func_001CCBB0(u32 *p, u8 *m)
{
    *(u32 *)(m + 0xC) = 0x6C128004;
    p[0] = 0x30000013;
    p[1] = (u32)m;
    p[2] = 0;
    p[3] = 0;
    return p + 4;
}

/* 0x001CCBE0, 0x20 bytes, matching. */
u32 *func_001CCBE0(u32 *p)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x17000000;
    return p + 4;
}

/* 0x001CCC00, 0xD0 bytes. Starts the 3D packets (resets the cached state). */
u32 *func_001CCC00(u32 *p)
{
    p[0] = 0x30000007;
    p[1] = (u32)g_00426380;
    p[2] = 0x11000000;
    p[3] = 0x50000007;
    p[4] = 0x10000002;
    p[5] = 0;
    p[6] = 0x11000000;
    p[7] = 0x50000002;
    *(u64 *)(p + 8) = 0x1000000000008001ULL;
    *(u64 *)(p + 10) = 0xE;
    *(u64 *)(p + 0xC) = ((u64)func_00100FE0() & 0xFFFFFFFF) | 0x13A000000ULL;
    *(u64 *)(p + 0xE) = 0x4E;
    g_0045CD90 = 1;
    g_0045CD8C = 0x6F;
    g_0045CD88 = 0;
    g_0045CD94 = 0x1E;
    return p + 0x10;
}

/* 0x001CCCD0, 0x50 bytes, matching. */
u32 *func_001CCCD0(u32 *p)
{
    p[0] = 0x30000003;
    p[1] = (u32)g_004263F0;
    p[2] = 0x11000000;
    p[3] = 0x50000003;
    g_0045CD8C = 0x6F;
    g_0045CD88 = 0;
    g_0045CD90 = 1;
    g_0045CD94 = 0x1E;
    return p + 4;
}

/* 0x001CCD20, 0x3C bytes. A mesh's state: lights, fog, texture. */
u32 *func_001CCD20(u32 *p, int k, u32 f)
{
    p = func_001CC3B0(p, f);
    p = func_001CC450(p, f);
    return func_001CC220(p, k);
}

/* 0x001CCFA0, 0xBC bytes. Marks unit `u`'s officer as hit down. */
void func_001CCFA0(u8 *u)
{
    u8 *o = g_006A3A30[*(short *)(u + 0x178)], *w;

    *(u32 *)(o + 0xB8) |= 2;
    w = *(u8 **)(o + 0x10);
    if (w == 0)
        return;
    if ((*(u32 *)(o + 0xB8) & 0x80) != 0)
        *(u32 *)(w + 0x80) |= 4;
    if ((GAME_FLAGS & 0x4000000) == 0 && w[0x79] != 0 && (*(u32 *)(w + 0x84) & 0x1000) == 0)
        u[0x185] = func_002051A0(o);
}
