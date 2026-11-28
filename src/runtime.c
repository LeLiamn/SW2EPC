/*
 * runtime.c - run-time helpers (original source files unknown; 0x00117EB0-0x00118E94, after
 * main.c's system set-up, before libcdvd).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * - The first three functions are the compiler's run-time support: the destructor chain run at
 *   exit (it uses branch-likely instructions, which the game's code never does: a library built
 *   with other settings) and the static constructors run before main (the game has none).
 * - VU0 set-up: constant vectors loaded into vf21-vf31, matrices and vectors in the scratchpad.
 * - Two sorts of 16-byte records by their first float (insertion sort, and a quicksort that
 *   leaves runs of up to 10 records to the insertion sort).
 * - Memory fills and a copy for large blocks. The original loops of these four functions are
 *   unrolled by 8 (CodeWarrior's loop unroller), so this file was built without
 *   `opt_unroll_loops off`; they are written here as plain loops.
 */

#define SW2E_FILE_RUNTIME_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned int u32;

/* A destructor to run at exit. */
typedef struct Destructor {
    struct Destructor *next;
    void (*run)(void *object, int flag);
    void *object;
} Destructor;

typedef struct {
    float x, y, z, w;
} Vec4;

/* A record sorted by its key. */
typedef struct {
    float key;
    u32 a, b, c;
} SortRecord;

extern Destructor *g_00563280;           /* the destructor chain */
extern Vec4 g_004015D0[10];              /* the VU0 constants */
extern u8 g_0041DE00[];                  /* a DMA packet for VU0 (its microcode?) */
extern int g_00563290[16];               /* the quicksort's pending upper bounds */
extern int g_005632D0[16];               /* and lower bounds */

#define SCRATCH_F(off) (*(float *)(0x70000000 + (off)))

int func_0011B050(int channel);                  /* sceDmaGetChan */
void func_0011B380(int chan, void *packet);      /* sceDmaSend */
int func_001265F0(int a, int b);                 /* sceGsSyncPath */
void func_00142EA8(float *m);                    /* sceVu0UnitMatrix */
void func_00142FF0(float *m, float angle);       /* a rotation matrix (X?) */
void func_00143098(float *m, float angle);       /* a rotation matrix (Y?) */
void func_0011EB80(void *to, const void *from, u32 size);  /* memcpy */

int func_00117F90(int a, int b);

/* 0x00117EB0, 0x54 bytes. Runs the destructor chain. */
void func_00117EB0(void)
{
    while (g_00563280 != 0) {
        Destructor *d = g_00563280;

        g_00563280 = d->next;
        d->run(d->object, -1);
    }
}

/* 0x00117F10, 0x78 bytes. Runs the constructors from `start` to `end`, then func_00117F90. */
int func_00117F10(void (**start)(void), void (**end)(void), int a, int b)
{
    for (; start < end; start++)
        (*start)();
    return func_00117F90(a, b);
}

/* 0x00117F90, 0x8 bytes, matching. */
int func_00117F90(int a, int b)
{
    return 0;
}

/* 0x00117FA0, 0x23C bytes. Loads the constant vectors into VU0: vf28-vf30, vf25-vf27,
 * vf21-vf24 from the table, vf31 = (1, 1, 1, 1). */
void func_00117FA0(void)
{
    Vec4 v[10];
    int i;

    for (i = 0; i < 10; i++)
        v[i] = g_004015D0[i];
    __asm__ volatile(
        "vsub.xyzw $vf31, $vf0, $vf0\n"
        "lqc2 $vf28, 0(%0)\n"
        "lqc2 $vf29, 0(%1)\n"
        "lqc2 $vf30, 0(%2)\n"
        "lqc2 $vf25, 0(%3)\n"
        "lqc2 $vf26, 0x10(%3)\n"
        "lqc2 $vf27, 0x20(%3)\n"
        "lqc2 $vf21, 0(%4)\n"
        "lqc2 $vf22, 0(%5)\n"
        "lqc2 $vf23, 0(%6)\n"
        "lqc2 $vf24, 0(%7)\n"
        "vaddw.xyzw $vf31, $vf31, $vf0w\n"
        :
        : "r"(&v[0]), "r"(&v[1]), "r"(&v[2]), "r"(&v[3]), "r"(&v[6]), "r"(&v[7]), "r"(&v[8]),
          "r"(&v[9])
        : "memory");
}

/* 0x001181E0, 0x114 bytes. Sets VU0 up: its packet sent, the constants loaded, then in the
 * scratchpad a unit matrix (0x00), two rotations by pi (0x40, 0x80) and constant vectors
 * (0xC0-0x14C). */
void func_001181E0(void)
{
    func_0011B380(func_0011B050(0), g_0041DE00);
    func_001265F0(0, 0);
    func_00117FA0();
    func_00142EA8((float *)0x70000000);
    func_00142FF0((float *)0x70000040, 3.14159274f);
    func_00143098((float *)0x70000080, 3.14159274f);
    SCRATCH_F(0xC0) = 0.0f;
    SCRATCH_F(0xC4) = 0.0f;
    SCRATCH_F(0xC8) = 0.0f;
    SCRATCH_F(0xCC) = 0.0f;
    SCRATCH_F(0xD0) = 1.0f;
    SCRATCH_F(0xD4) = 0.0f;
    SCRATCH_F(0xD8) = 0.0f;
    SCRATCH_F(0xDC) = 1.0f;
    SCRATCH_F(0xE0) = 0.0f;
    SCRATCH_F(0xE4) = 1.0f;
    SCRATCH_F(0xE8) = 0.0f;
    SCRATCH_F(0xEC) = 1.0f;
    SCRATCH_F(0xF0) = 0.0f;
    SCRATCH_F(0xF4) = 0.0f;
    SCRATCH_F(0xF8) = 1.0f;
    SCRATCH_F(0xFC) = 1.0f;
    SCRATCH_F(0x100) = -1.0f;
    SCRATCH_F(0x104) = 0.0f;
    SCRATCH_F(0x108) = 0.0f;
    SCRATCH_F(0x10C) = 1.0f;
    SCRATCH_F(0x110) = 0.0f;
    SCRATCH_F(0x114) = -1.0f;
    SCRATCH_F(0x118) = 0.0f;
    SCRATCH_F(0x11C) = 1.0f;
    SCRATCH_F(0x120) = 0.0f;
    SCRATCH_F(0x124) = 0.0f;
    SCRATCH_F(0x128) = -1.0f;
    SCRATCH_F(0x12C) = 1.0f;
    SCRATCH_F(0x130) = 0.0f;
    SCRATCH_F(0x134) = -1.0f;
    SCRATCH_F(0x138) = 0.0f;
    SCRATCH_F(0x13C) = 0.0f;
    SCRATCH_F(0x140) = 1.0f;
    SCRATCH_F(0x144) = 1.0f;
    SCRATCH_F(0x148) = 1.0f;
    SCRATCH_F(0x14C) = 1.0f;
}

/* 0x00118300, 0xC8 bytes. Insertion sort of `n` records by key. */
void func_00118300(int n, SortRecord *r)
{
    int i, j;

    for (i = 1; i < n; i++) {
        SortRecord x = r[i];

        for (j = i - 1; j >= 0 && x.key < r[j].key; j--)
            r[j + 1] = r[j];
        r[j + 1] = x;
    }
}

/* 0x001183D0, 0x1DC bytes. Quicksort of `n` records by key (the middle record as pivot, the
 * larger part kept on a stack of bounds); runs of 10 or fewer are left for the insertion sort,
 * which ends the work over the whole array. */
void func_001183D0(int n, SortRecord *r)
{
    int lo = 0, hi = n - 1, sp = 0;

    for (;;) {
        float pivot;
        int i, j;

        if (hi - lo < 11) {
            if (sp == 0) {
                func_00118300(n, r);
                return;
            }
            sp--;
            lo = g_005632D0[sp];
            hi = g_00563290[sp];
        }
        pivot = r[(lo + hi) >> 1].key;
        i = lo;
        j = hi;
        for (;;) {
            SortRecord t;

            while (r[i].key < pivot)
                i++;
            while (pivot < r[j].key)
                j--;
            if (j <= i)
                break;
            t = r[i];
            r[i] = r[j];
            r[j] = t;
            i++;
            j--;
        }
        if (hi - j < i - lo) {
            if (i - lo > 10) {
                g_005632D0[sp] = lo;
                g_00563290[sp] = i - 1;
                sp++;
            }
            lo = j + 1;
        } else {
            if (hi - j > 10) {
                g_005632D0[sp] = j + 1;
                g_00563290[sp] = hi;
                sp++;
            }
            hi = i - 1;
        }
    }
}

/* 0x001185B0, 0x30 bytes. Clears `n` quadwords. */
void func_001185B0(Vec4 *to, u32 n)
{
    u32 i;

    for (i = 0; i < n; i++)
        __asm__ volatile("sq $0, 0(%0)" : : "r"(&to[i]) : "memory");
}

/* 0x001185E0, 0x268 bytes. Fills `n` bytes with `c`: bytes up to a 16-byte boundary, bytes at
 * the end, quadwords between. */
void func_001185E0(u8 *to, u32 n, u8 c)
{
    u8 pattern[16];
    u32 *q, *p;
    int head, i, quads;
    u32 tail;

    if (n < 0x10) {
        u32 k;

        for (k = 0; k < n; k++)
            *to++ = c;
        return;
    }
    q = (u32 *)(((u32)to + 0xF) & ~0xF);
    head = (u8 *)q - to;
    for (i = 0; i < head; i++)
        *to++ = c;
    tail = (n - head) & 0xF;
    quads = (n - head) - tail;
    to += quads;
    for (i = 0; i < (int)tail; i++)
        *to++ = c;
    for (i = 0; i < 16; i++)
        pattern[i] = c;
    p = (u32 *)pattern;
    for (i = 0; i < quads / 16; i++, q += 4) {
        q[0] = p[0];
        q[1] = p[1];
        q[2] = p[2];
        q[3] = p[3];
    }
}

/* 0x00118850, 0x268 bytes. Clears `n` bytes, the same way. */
void func_00118850(u8 *to, u32 n)
{
    u8 pattern[16];
    u32 *q, *p;
    int head, i, quads;
    u32 tail;

    if (n < 0x10) {
        u32 k;

        for (k = 0; k < n; k++)
            *to++ = 0;
        return;
    }
    q = (u32 *)(((u32)to + 0xF) & ~0xF);
    head = (u8 *)q - to;
    for (i = 0; i < head; i++)
        *to++ = 0;
    tail = (n - head) & 0xF;
    quads = (n - head) - tail;
    to += quads;
    for (i = 0; i < (int)tail; i++)
        *to++ = 0;
    for (i = 0; i < 16; i++)
        pattern[i] = 0;
    p = (u32 *)pattern;
    for (i = 0; i < quads / 16; i++, q += 4) {
        q[0] = p[0];
        q[1] = p[1];
        q[2] = p[2];
        q[3] = p[3];
    }
}

/* 0x00118AC0, 0x3D4 bytes. Copies `n` bytes: up to 0x1B800 with memcpy; larger blocks byte by
 * byte up to the source's 16-byte boundary and at the end, and in between by quadwords through
 * a 4 KB buffer on the stack (256 quadwords at a time). As in the original, the quadwords are
 * written from `to` itself, not after the first bytes: the copy is right only when the source is
 * 16-aligned (as the callers' are?). */
void func_00118AC0(u32 *to, u8 *from, u32 n)
{
    u32 buffer[1024];
    u32 *q;
    u8 *d;
    int head, i, quads, chunk;
    u32 tail;

    if (n <= 0x1B800) {
        func_0011EB80(to, from, n);
        return;
    }
    q = (u32 *)(((u32)from + 0xF) & ~0xF);
    head = (u8 *)q - from;
    d = (u8 *)to;
    for (i = 0; i < head; i++)
        *d++ = *from++;
    tail = (n - head) & 0xF;
    quads = (n - head) - tail;
    from += quads;
    d += quads;
    for (i = 0; i < (int)tail; i++)
        *d++ = *from++;
    chunk = 0x100;
    for (quads /= 16; quads > 0; quads -= chunk) {
        u32 *b;

        if (quads <= chunk)
            chunk = quads;
        for (i = 0, b = buffer; i < chunk; i++, q += 4, b += 4) {
            b[0] = q[0];
            b[1] = q[1];
            b[2] = q[2];
            b[3] = q[3];
        }
        for (i = 0, b = buffer; i < chunk; i++, to += 4, b += 4) {
            to[0] = b[0];
            to[1] = b[1];
            to[2] = b[2];
            to[3] = b[3];
        }
    }
}
