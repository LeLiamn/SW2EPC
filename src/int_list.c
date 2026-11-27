/*
 * int_list.c - a small list of ints over a caller's buffer (used for bases, cells and groups).
 * Original file name unknown (0x00364E40-0x0036543C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int *data;
    int cap;
    int count;
} IntList;

extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

void func_0011ED38(void *p, int v, int n);

int func_00365030(IntList *l, int k);
int func_00365050(IntList *l);
void func_00364F00(IntList *l, int k, int v);
void func_00364FA0(IntList *l, int k);
void func_00364FF0(IntList *l, int k, int v);
int func_003653D0(IntList *l);

/* 0x00364E40, 0x24 bytes, matching. Appends `v`. */
void func_00364E40(IntList *l, int v)
{
    l->data[l->count] = v;
    l->count++;
}

/* 0x00364E70, 0x88 bytes, matching. Inserts `v` before the first smaller entry; its place. */
int func_00364E70(IntList *l, int v)
{
    int n = func_00365050(l), k = 0;

    for (; k < n; k++) {
        if (func_00365030(l, k) < v)
            break;
    }
    func_00364F00(l, k, v);
    return k;
}

/* 0x00364F00, 0x94 bytes. Inserts `v` at `k`. */
void func_00364F00(IntList *l, int k, int v)
{
    int n = l->count;

    l->count = n + 1;
    for (; k < n; n--)
        func_00364FF0(l, n, func_00365030(l, n - 1));
    func_00364FF0(l, k, v);
}

/* 0x00364FA0, 0x50 bytes. Removes entry `k`. */
void func_00364FA0(IntList *l, int k)
{
    int *p = l->data + k, *end = l->data + (l->count - 1);

    for (; p != end; p++)
        *p = p[1];
    l->count--;
}

/* 0x00364FF0, 0x3C bytes. Sets entry `k` (growing the count to it). */
void func_00364FF0(IntList *l, int k, int v)
{
    l->data[k] = v;
    if (k + 1 < l->count)
        l->count = l->count;
    else
        l->count = k + 1;
}

/* 0x00365030, 0x14 bytes, matching. */
int func_00365030(IntList *l, int k)
{
    return l->data[k];
}

/* 0x00365050, 8 bytes, matching. */
int func_00365050(IntList *l)
{
    return l->count;
}

/* 0x00365060, 0x70 bytes. A random entry. */
int func_00365060(IntList *l)
{
    int n = func_00365050(l);

    return func_00365030(l, n == 0 ? 0 : (int)RANDOM() % n);
}

/* 0x003650D0, 0x94 bytes. Takes out a random entry. */
int func_003650D0(IntList *l)
{
    int n = func_00365050(l), k, v;

    k = n == 0 ? 0 : (int)RANDOM() % n;
    v = func_00365030(l, k);
    func_00364FA0(l, k);
    return v;
}

/* 0x00365170, 0x80 bytes, matching. Where `v` is (-1 for nowhere). */
int func_00365170(IntList *l, int v)
{
    int n = func_00365050(l), k;

    for (k = 0; k < n; k++) {
        if (v == func_00365030(l, k))
            return k;
    }
    return -1;
}

/* 0x003651F0, 0x3C bytes, matching. Removes `v`. */
void func_003651F0(IntList *l, int v)
{
    int k = func_00365170(l, v);

    if (k != -1)
        func_00364FA0(l, k);
}

/* 0x00365230, 0x38 bytes, matching. Empties the list. */
void func_00365230(IntList *l)
{
    func_0011ED38(l->data, 0, l->cap << 2);
    l->count = 0;
}

/* 0x00365270, 0xD8 bytes. The place of the entry scoring best by `score` (-1 when empty). */
int func_00365270(IntList *l, int (*score)(int, int, int), int a, int b)
{
    int n, best = 0, k;
    int top = -1;

    if (func_003653D0(l) == 0)
        return -1;
    n = func_00365050(l);
    for (k = 0; k < n; k++) {
        int s = score(func_00365030(l, k), a, b);

        if (top < s) {
            top = s;
            best = k;
        }
    }
    return best;
}

/* 0x00365350, 0x7C bytes. That entry (0 when empty). */
int func_00365350(IntList *l, int (*score)(int, int, int), int a, int b)
{
    if (func_003653D0(l) == 0)
        return 0;
    return func_00365030(l, func_00365270(l, score, a, b));
}

/* 0x003653D0, 0x20 bytes, matching. Whether the list has entries. */
int func_003653D0(IntList *l)
{
    return func_00365050(l) != 0;
}

/* 0x003653F0, 0x50 bytes, matching. Sets the list over buffer `buf` of `cap` entries. */
void func_003653F0(IntList *l, int *buf, int cap)
{
    func_0011ED38(l, 0, 0xC);
    l->data = buf;
    l->cap = cap;
    l->count = 0;
}
