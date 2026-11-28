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

#define SW2E_FILE_HEAP_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned int u32;

/* A block's header (16 bytes). The links are PS2 addresses (docs/port.md). */
typedef struct Block {
    ps2ptr prev;             /* Block */
    ps2ptr next;             /* Block */
    ps2ptr data;             /* 0 = free */
    u32 size;                /* with the header */
} Block;

/* A heap (0x14 bytes); every field is the PS2 address of a Block. */
typedef struct {
    ps2ptr first;
    ps2ptr cursor;           /* where the next search starts */
    ps2ptr last;             /* the farthest block used */
    ps2ptr saved_cursor;
    ps2ptr saved_last;
} Heap;

#define BLK(a) ((Block *)PS2_PTR(a))   /* the block at PS2 address a */

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

    g_005004A0.heap[1].last = PS2_ADDR(end);
    g_005004A0.heap[0].first = PS2_ADDR(start);
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
    g_005004A0.heap[0].last = PS2_ADDR(start);
    g_005004A0.heap[0].cursor = PS2_ADDR(start);
    g_005004A0.heap[1].cursor = PS2_ADDR(end);
    g_005004A0.heap[1].first = PS2_ADDR(end);
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
    Block *b = BLK(h->cursor);

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
                n = BLK(PS2_ADDR(b) + step);     /* 32-bit: step is negative for heap 1 */
                n->size = size - want;
                n->prev = PS2_ADDR(b);
                n->next = b->next;
                n->data = 0;
                if (n->next != 0)
                    BLK(n->next)->prev = PS2_ADDR(n);
                b->size = *need;
                b->next = PS2_ADDR(n);
                b->data = PS2_ADDR(g_005004A0.which == 0 ? b : n) + sizeof(Block);
                if (h->cursor == PS2_ADDR(b))
                    h->cursor = PS2_ADDR(n);
            } else if (want == size) {
                b->size = want;
                n = BLK(b->next);
                b->data = PS2_ADDR(g_005004A0.which == 0 ? b : n) + sizeof(Block);
                for (; n->data != 0; n = BLK(n->next))
                    ;
                h->cursor = PS2_ADDR(n);
            } else {
                goto next;
            }
            if (g_005004A0.which == 0)
                farther = h->last < PS2_ADDR(n);
            else
                farther = PS2_ADDR(n) < h->last;
            if (farther)
                h->last = PS2_ADDR(n);
            return b;
        }
next:
        b = BLK(b->next);
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
    return (u8 *)PS2_PTR(b->data);
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
    data = (u8 *)PS2_PTR(b->data);
    pad = (int)(PS2_ADDR(data) % align);
    data += pad != 0 ? align - pad : 0;
    b->data = PS2_ADDR(data);
    return data;
}

/* 0x00102E70, 0x50 bytes, matching. Merges a block with its next one when that one is free. */
void func_00102E70(Heap *h, Block *b)
{
    Block *n = BLK(b->next);

    if (n != 0 && n->data == 0) {
        b->size += n->size;
        n->size = 0;
        n->prev = 0;
        b->next = n->next;
        if (b->next != 0)
            BLK(b->next)->prev = PS2_ADDR(b);
        else
            h->last = PS2_ADDR(b);
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
    for (b = BLK(BLK(h->last)->prev); PS2_ADDR(data) != b->data; b = BLK(b->prev))
        ;
    b->data = 0;
    if (BLK(h->last)->prev == PS2_ADDR(b))
        h->last = PS2_ADDR(b);
    g_005004A0.free += b->size;
    p = BLK(b->prev);
    if (p != 0 && p->data == 0) {
        p->size += b->size;
        b = BLK(b->next);
        p->next = PS2_ADDR(b);
        if (b == 0)
            h->last = PS2_ADDR(p);
        else
            b->prev = PS2_ADDR(p);
        b = p;
    }
    func_00102E70(h, b);
    if (g_005004A0.which == 0)
        nearer = PS2_ADDR(b) < h->cursor;
    else
        nearer = h->cursor < PS2_ADDR(b);
    if (nearer)
        h->cursor = PS2_ADDR(b);
}

/* 0x00102FC0, 0x40 bytes. The end of the area: the top of the memory (the C library's heap is
 * touched once, func_0011DFB0 / func_0011E008). */
u8 *func_00102FC0(void)
{
    func_0011E008(func_0011DFB0(0x183EFF0));
    return (u8 *)PS2_PTR(0x1FFF000);
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
    func_00102AE0((u8 *)PS2_PTR(0x7C1000), func_00102FC0() - (u8 *)PS2_PTR(0x7C1000));
}

/* 0x00103060, 0x2C bytes, matching. The same, once. */
void func_00103060(void)
{
    if (g_0045D200 == 0) {
        g_0045D200 = 1;
        func_00103020();
    }
}
