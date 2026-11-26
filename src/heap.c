/*
 * heap.c - the memory allocator (original source file unknown; it follows main, 0x00102A80-
 * 0x00103090).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * One memory area (from 0x007C1000, after the BSS, to 0x01FFF000) is shared by two heaps: heap 0
 * allocates from its start upwards, heap 1 from its end downwards (g_005004D8 picks the one in
 * use; the game uses heap 1). Every block has a 16-byte header (its neighbours, its data, its
 * size); a free block has no data. Allocation is first fit from a cursor; freeing merges a block
 * with free neighbours. The state can be saved (func_00102B80), e.g. before a scene.
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* A block's header (16 bytes). */
typedef struct Block {
    struct Block *prev;
    struct Block *next;
    u8 *data;                /* 0 = free */
    u32 size;                /* with the header */
} Block;

/* A heap (0x14 bytes). */
typedef struct {
    Block *first;
    Block *cursor;           /* where the next search starts */
    Block *last;             /* the farthest block used */
    Block *saved_cursor;
    Block *saved_last;
} Heap;

extern struct {
    Heap heap[2];            /* 0x005004A0, 0x005004B4 */
    u32 size;                /* 0x005004C8 the area */
    u32 free;                /* 0x005004CC bytes free */
    u32 saved_size;
    u32 saved_free;
    int which;               /* 0x005004D8 0 upwards, 1 downwards */
} g_005004A0;

extern int g_0045D200;                    /* (small data) 1 once set up */

void *func_0011DFB0(u32 size);
void func_0011E008(void *data);
int func_00103000(u32 which);

/* 0x00102A80, 0x58 bytes, matching. The heap in use (a bad choice is reset to heap 1). */
Heap *func_00102A80(void)
{
    if (g_005004A0.which == 0)
        return &g_005004A0.heap[0];
    if (g_005004A0.which == 1)
        return &g_005004A0.heap[1];
    func_00103000(1);
    return func_00102A80();
}

/* 0x00102AE0, 0x7C bytes. Sets the area up: one free block at each end, both of all the free
 * space. */
void func_00102AE0(u8 *base, u32 size)
{
    Block *start = (Block *)base;
    Block *end = (Block *)(base + ((size - 0x10) & ~0xF));

    g_005004A0.heap[1].last = end;
    g_005004A0.heap[0].first = start;
    end->prev = 0;
    start->prev = 0;
    g_005004A0.free = size - 0x20 - (size & 0xF);
    end->next = 0;
    start->next = 0;
    end->data = 0;
    start->data = 0;
    end->size = g_005004A0.free;
    start->size = g_005004A0.free;
    g_005004A0.size = size;
    g_005004A0.heap[0].last = start;
    g_005004A0.heap[0].cursor = start;
    g_005004A0.heap[1].cursor = end;
    g_005004A0.heap[1].first = end;
}

/* 0x00102B60, 0x14 bytes, matching. */
void func_00102B60(Heap *h)
{
    h->saved_cursor = h->cursor;
    h->saved_last = h->last;
}

/* 0x00102B80, 0x4C bytes, matching. Saves both heaps' state. */
void func_00102B80(void)
{
    func_00102B60(&g_005004A0.heap[0]);
    func_00102B60(&g_005004A0.heap[1]);
    g_005004A0.saved_size = g_005004A0.size;
    g_005004A0.saved_free = g_005004A0.free;
}

/* 0x00102BD0, 0x154 bytes. Finds a free block of at least *need bytes from the cursor and takes
 * it (splitting off the rest: after it in heap 0, before it in heap 1). The block, or 0. */
Block *func_00102BD0(u32 *need)
{
    Heap *h = func_00102A80();
    Block *b = h->cursor;

    for (;;) {
        if (b->data == 0) {
            u32 size = b->size;
            u32 want = *need;
            Block *n;
            int farther;

            if (want < size) {
                u32 step = want;

                if (g_005004A0.which != 0)
                    step = -want;
                n = (Block *)((u8 *)b + step);
                n->size = size - want;
                n->prev = b;
                n->next = b->next;
                n->data = 0;
                if (n->next != 0)
                    n->next->prev = n;
                b->size = *need;
                b->next = n;
                b->data = (u8 *)((g_005004A0.which == 0 ? b : n) + 1);
                if (h->cursor == b)
                    h->cursor = n;
            } else if (want == size) {
                b->size = want;
                n = b->next;
                b->data = (u8 *)((g_005004A0.which == 0 ? b : n) + 1);
                for (; n->data != 0; n = n->next)
                    ;
                h->cursor = n;
            } else {
                goto next;
            }
            if (g_005004A0.which == 0)
                farther = h->last < n;
            else
                farther = n < h->last;
            if (farther)
                h->last = n;
            return b;
        }
next:
        b = b->next;
        if (b == 0)
            return 0;
    }
}

/* 0x00102D30, 0x80 bytes, matching. Allocates `size` bytes (16-aligned). */
u8 *func_00102D30(u32 size)
{
    Block *b;

    if (size == 0)
        return 0;
    size = (size + 0x2F) & ~0xF;
    if (g_005004A0.free < size)
        return 0;
    b = func_00102BD0(&size);
    if (b == 0)
        return 0;
    g_005004A0.free -= size;
    return b->data;
}

/* 0x00102DB0, 0xB4 bytes. Allocates `size` bytes aligned to `align`. */
u8 *func_00102DB0(int align, u32 size)
{
    u32 need;
    Block *b;
    u8 *data;
    int pad;

    if (size == 0)
        return 0;
    need = (size + align + 0x2E) & ~0xF;
    if (g_005004A0.free < need)
        return 0;
    b = func_00102BD0(&need);
    if (b == 0)
        return 0;
    g_005004A0.free -= need;
    data = b->data;
    pad = (int)((unsigned long)data % align);
    data += pad != 0 ? align - pad : 0;
    b->data = data;
    return data;
}

/* 0x00102E70, 0x50 bytes, matching. Merges a block with its next one when that one is free. */
void func_00102E70(Heap *h, Block *b)
{
    Block *n = b->next;

    if (n != 0 && n->data == 0) {
        b->size += n->size;
        n->size = 0;
        n->prev = 0;
        b->next = n->next;
        if (b->next != 0)
            b->next->prev = b;
        else
            h->last = b;
    }
}

/* 0x00102EC0, 0xF4 bytes. Frees a block by its data (searched back from the last block), merges
 * it with its free neighbours and moves the cursor back to it. */
void func_00102EC0(u8 *data)
{
    Heap *h;
    Block *b, *p;
    int nearer;

    if (data == 0)
        return;
    h = func_00102A80();
    for (b = h->last->prev; data != b->data; b = b->prev)
        ;
    b->data = 0;
    if (h->last->prev == b)
        h->last = b;
    g_005004A0.free += b->size;
    p = b->prev;
    if (p != 0 && p->data == 0) {
        p->size += b->size;
        b = b->next;
        p->next = b;
        if (b == 0)
            h->last = p;
        else
            b->prev = p;
        b = p;
    }
    func_00102E70(h, b);
    if (g_005004A0.which == 0)
        nearer = b < h->cursor;
    else
        nearer = h->cursor < b;
    if (nearer)
        h->cursor = b;
}

/* 0x00102FC0, 0x40 bytes. The end of the area: the top of the memory (the C library's heap is
 * touched once, func_0011DFB0 / func_0011E008). */
u8 *func_00102FC0(void)
{
    func_0011E008(func_0011DFB0(0x183EFF0));
    return (u8 *)0x1FFF000;
}

/* 0x00103000, 0x20 bytes, matching. Picks the heap in use (0 or 1); the previous choice. */
int func_00103000(u32 which)
{
    int old = g_005004A0.which;

    if (which < 2)
        g_005004A0.which = which;
    return old;
}

/* 0x00103020, 0x3C bytes. Sets the area up from 0x007C1000, heap 1 in use. */
void func_00103020(void)
{
    func_00103000(1);
    func_00102AE0((u8 *)0x7C1000, func_00102FC0() - (u8 *)0x7C1000);
}

/* 0x00103060, 0x2C bytes, matching. The same, once. */
void func_00103060(void)
{
    if (g_0045D200 == 0) {
        g_0045D200 = 1;
        func_00103020();
    }
}
