/*
 * stage_units.c - the stage's placed units (map objects with models: houses, fences, gates...):
 * their tables live in a block whose pointers sit in the scratchpad at 0x70000180-0x7000019F.
 * Original file name unknown (0x00207CC0-0x00208268).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The scratchpad block. */
#define SU_INFO (*(u8 **)0x70000180)       /* 0x10 bytes per unit */
#define SU_A (*(u8 ***)0x70000184)         /* three model lists */
#define SU_B (*(u8 ***)0x70000188)
#define SU_C (*(u8 ***)0x7000018C)
#define SU_SHAPE (*(u8 ***)0x70000190)     /* each unit's shape record */
#define SU_DATA (*(u8 ***)0x70000194)      /* each unit's data */
#define SU_COUNT (*(u16 *)0x70000198)
#define g_700001A0 ((u8 *)0x700001A0)      /* the empty shape */
#define g_700001B0 ((u8 *)0x700001B0)      /* the shape of size 0x20 */

extern u8 g_00669D60[];

void func_001FEEC0(void);
void func_00102EC0(void *p);
void *func_00102D30(int size);
void func_00118850(void *p, int n);

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
u8 func_00207D80(u32 i)
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
    u32 base = ((u32)t + t[0] * 4 + 0x13) & 0xFFFFFFF0, off = 0, k;
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
            data[k] = (u8 *)(base + off);
        } else {
            shape[k] = (u8 *)(base + off);
            data[k] = (u8 *)(base + off + 0x10);
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
            t[k + 1] = (((u32)t + n * 4 + 0x13) & 0xFFFFFFF0) + off;
            off += s;
        }
    }
}

/* 0x002080E0, 0x54 bytes, matching. Frees the shape and data lists. */
void func_002080E0(void)
{
    if (SU_DATA != 0) {
        func_00102EC0(SU_DATA);
        SU_DATA = 0;
    }
    if (SU_SHAPE != 0) {
        func_00102EC0(SU_SHAPE);
        SU_SHAPE = 0;
    }
}

/* 0x00208140, 0x12C bytes. Sets up the stage units from file `f` (its offsets made into
 * pointers) with info table `info`. */
void func_00208140(u8 *info, u32 *f)
{
    u32 *a, k;
    int size;

    func_00118850((void *)0x70000180, 0x40);
    for (k = 0; k < f[0]; k++)
        f[k + 1] += (u32)f;
    a = (u32 *)f[1];
    func_00208070(a);
    func_00208070((u32 *)f[2]);
    func_00208070((u32 *)f[3]);
    size = *(int *)(g_00669D60 + 0x58) == 2 ? 2000 : a[0] << 2;
    SU_INFO = info;
    SU_A = (u8 **)(a + 1);
    SU_B = (u8 **)(f[2] + 4);
    SU_C = (u8 **)(f[3] + 4);
    SU_SHAPE = func_00102D30(size);
    SU_DATA = func_00102D30(size);
    SU_COUNT = a[0];
    func_00118850(SU_SHAPE, size);
    func_00118850(SU_DATA, size);
    func_00207E90();
    func_00207FA0((u32 *)f[4]);
}
