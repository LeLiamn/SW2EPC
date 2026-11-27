/*
 * motion_manager.c - the weapon kinds' motion data (original source file MotionManager.c: its
 * name is passed to the file loader at 0x0017C4A0, 0x0017C6D0 and 0x0017CC40).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Each of the 106 weapon kinds has a 0xD0-byte record at 0x005B5060:
 *   +0x00 its motion file (a LINKDATA entry), +0x04 its mounted motion file;
 *   +0x10, +0x20, +0x30 opened motion packs (pack, count, motion states, flags: see
 *   func_0017C320), the first one being the kind's own motions (states at +0x18);
 *   +0x40 the kind's unit description (func_0015FD90); +0x50 flag 1: the kind has no files;
 *   +0x60 the mounted motions (states at +0x68), +0x70 three extra motion states.
 * The face motion lives at 0x005B5040 (entry 0x56D), the shared motions at 0x005BA680
 * (entry 0x631, states at 0x005BA688).
 */

typedef unsigned char u8;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)(o) + (off)))->f##n)

extern u8 g_005B5060[0x6A][0xD0];        /* the weapon kinds' motion records */
extern u8 g_005B5040[0x20];              /* the face motion's state */
/* An opened motion pack (func_0017C320). */
typedef struct {
    u32 *pack;
    u32 count;
    u8 *states;              /* +8: 0x20 bytes per motion */
    u32 flags;
} MotionPack;

extern MotionPack g_005BA680;            /* the shared motions */
extern const char g_00424D10[];          /* "MotionManager.c" */
extern int g_004067E0[0x58];             /* motion indexes of the kinds 0x3E-0x67, two each */
extern int g_0045CC88, g_0045CC8C, g_0045CC90, g_0045CC94;  /* (small data) kinds 0x68, 0x69 */

void func_001185E0(void *p, int size, int value);  /* memset */
void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const void *file, int line);
void func_00102EC0(void *data);          /* free */
void func_0015FD70(u8 *d);
void func_0015FD90(u32 *data, u8 *d, u8 kind);
void func_001477C0(void *p);
void func_001477E0(u32 *motion, void *out);
void func_001479C0(u32 *motion, void *s);
void func_00147980(void *s);
int func_0017C320(u32 *pack, u32 *out);
void func_0017C3E0(int k);
int func_001BEA10(int k);
int func_001BE990(int k);
unsigned short func_001BE9B0(int k);
int func_001BE9D0(int k);
int func_001BE9F0(int k);
int func_0017C6D0(int k, int mounted, int now);
int func_0017C7D0(u32 k);
int func_0017CA20(int k);
void func_0017C640(void);

/* 0x0017C4A0, 0x11C bytes, matching. Sets the motion data up: the records cleared, the face and shared
 * motions loaded, then the motions of every kind in use (func_001BEA10). */
void func_0017C4A0(void)
{
    int k;
    u8 *r = g_005B5060[0];

    for (k = 0; k < 0x6A; k++, r += 0xD0) {
        func_001185E0(r, 0xD0, 0);
        func_0015FD70(r + 0x40);
    }
    func_001477C0(g_005B5040);
    func_001477E0(func_001026D0(1, 0x56D, 0, 1, 0, 0, g_00424D10, 0x68), g_005B5040);
    func_0017C320(func_001026D0(1, 0x631, 0, 1, 0, 0, g_00424D10, 0x6E), (u32 *)&g_005BA680);
    for (k = 0; k < 0x6A; k++) {
        if (func_001BEA10(k) != 0) {
            func_0017C6D0(k, func_0017CA20(k), 1);
            func_0017C7D0(k);
        }
    }
}

/* 0x0017C5C0, 0x74 bytes. Frees all the motion data. */
void func_0017C5C0(void)
{
    int k;

    func_0017C640();
    for (k = 0; k < 0x6A; k++) {
        if (func_001BEA10(k) != 0)
            func_0017C3E0(k);
    }
    {
        MotionPack *p = &g_005BA680;

        func_00102EC0(p->pack);
        func_00102EC0(p->states);
    }
    func_00147980(g_005B5040);
}

/* 0x0017C640, 0x8C bytes, matching. Frees (or clears) the motion data of the kinds not in use. */
void func_0017C640(void)
{
    int k;
    u8 *r = g_005B5060[0];

    for (k = 0; k < 0x6A; k++, r += 0xD0) {
        if (func_001BEA10(k) == 0) {
            if (BIT(r, 0x1C, 0)) {
                func_0017C3E0(k);
            } else {
                func_001185E0(r, 0xD0, 0);
                func_0015FD70(r + 0x40);
            }
        }
    }
}

/* 0x0017C6D0, 0xF4 bytes. Loads kind `k`'s motion file (and with `mounted` its mounted one),
 * unless loaded or without files. */
int func_0017C6D0(int k, int mounted, int now)
{
    u8 *r = g_005B5060[k];

    if (PTR(r, 0) == 0 && !BIT(r, 0x50, 0)) {
        PTR(r, 0) = func_001026D0(1, func_001BE990(k), 0, now, 0, 0, g_00424D10, 0xC3);
        if (mounted != 0)
            PTR(r, 4) = func_001026D0(1, func_001BE9B0(k), 0, now, 0, 0, g_00424D10, 199);
    }
    return 1;
}

/* 0x0017C7D0, 0x19C bytes. Opens kind `k`'s motion file: its own motions (+0x10), two
 * optional packs (+0x20, +0x30), its unit description (+0x40); and the mounted file's pack
 * (+0x60) with, for four entries, three extra motions (+0x70). */
int func_0017C7D0(u32 k)
{
    u8 *r = g_005B5060[k];
    u32 *f, *m, o;

    if (BIT(r, 0x50, 0))
        return 1;
    f = (u32 *)PTR(r, 0);
    func_0017C320((u32 *)((u8 *)f + (f[1] & ~3)), (u32 *)(r + 0x10));
    o = f[2];
    if (func_001BE9D0(k) != 0)
        func_0017C320((u32 *)(PTR(r, 0) + (o & ~3)), (u32 *)(r + 0x20));
    o = f[3];
    if (func_001BE9F0(k) != 0)
        func_0017C320((u32 *)(PTR(r, 0) + (o & ~3)), (u32 *)(r + 0x30));
    func_0015FD90((u32 *)(PTR(r, 0) + (f[4] & ~3)), r + 0x40, (u8)k);
    m = (u32 *)PTR(r, 4);
    if (m != 0) {
        u32 n = m[0], *e = m + 2, i;
        u8 *s = r;

        func_0017C320((u32 *)((u8 *)m + (m[1] & ~3)), (u32 *)(r + 0x60));
        if (n == 4) {
            for (i = 0; i < 3; i++, s += 0x20) {
                u32 off = *e++;

                func_001477C0(s + 0x70);
                func_001479C0((u32 *)(PTR(r, 4) + (off & ~3)), s + 0x70);
            }
        }
    }
    return 1;
}

/* 0x0017C970, 0xA4 bytes. Frees the motion files of the kinds not in use. */
void func_0017C970(void)
{
    int k;
    u8 *r = g_005B5060[0];

    for (k = 0; k < 0x6A; k++, r += 0xD0) {
        if (func_001BEA10(k) == 0 && !BIT(r, 0x50, 0) && PTR(r, 0) != 0) {
            func_00102EC0(PTR(r, 0));
            PTR(r, 0) = 0;
            if (PTR(r, 4) != 0) {
                func_00102EC0(PTR(r, 4));
                PTR(r, 4) = 0;
            }
        }
    }
}

/* 0x0017CA20, 0x28 bytes, matching. Whether kind `k` has a mounted motion file. */
int func_0017CA20(int k)
{
    return func_001BE9B0(k) != 0xFFFF;
}

/* 0x0017CA50, 0x174 bytes. Motion `i` (0 or 1) of kind `k`: 2k + i for kinds 0-0x19, from the
 * table for kinds 0x3E-0x5C and 0x5D-0x67, two small-data pairs for 0x68 / 0x69, else 0. */
int func_0017CA50(int k, int i)
{
    int t[0x58], x[4], n;

    for (n = 0; n < 0x58; n++)
        t[n] = g_004067E0[n];
    x[2] = g_0045CC88;
    x[0] = g_0045CC90;
    x[3] = g_0045CC8C;
    x[1] = g_0045CC94;
    if (k >= 0 && k < 0x1A)
        return i + k * 2;
    if (k >= 0x3E && k < 0x49)
        return t[(k - 0x3E) * 2 + i];
    if (k >= 0x49 && k < 0x54)
        return t[(k - 0x3E) * 2 + i];
    if (k >= 0x54 && k < 0x5D)
        return t[(k - 0x3E) * 2 + i];
    if (k >= 0x5D && k < 0x68)
        return t[(k - 0x3C) * 2 + i];
    if (k == 0x68)
        return x[i + 2];
    if (k == 0x69)
        return x[i];
    return 0;
}

/* 0x0017CBD0, 0x70 bytes, matching. The LINKDATA entry of kind `k`'s motion file. */
static int func_0017CBD0(int k)
{
    int e = 0x488;

    if (k >= 0 && k <= 0x19)
        e = k + 0x488;
    else if (k == 0x26)
        e = 0x4A2;
    else if (k == 0x2A)
        e = 0x4A3;
    else if (k == 0x20)
        e = 0x4A4;
    else if (k == 0x21)
        e = 0x4A5;
    return e;
}

/* 0x0017CC40, 0x98 bytes. Loads kind `k`'s motion file by its entry (func_0017CBD0). */
int func_0017CC40(int k, int now)
{
    u8 *r = g_005B5060[k];

    if (PTR(r, 0) == 0 && !BIT(r, 0x50, 0))
        PTR(r, 0) = func_001026D0(1, func_0017CBD0(k), 0, now, 0, 0, g_00424D10, 0x243);
    return 1;
}
