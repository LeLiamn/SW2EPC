/*
 * preload.c - lists of resources to keep loaded (by kind: units, motions, weapons, items) and the
 * packed-file decoder used for them (an LZ scheme with four window sizes). Original file name
 * unknown; it sits among the title screen's code (parts of 0x00279380-0x0027A030).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_PRELOAD_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8 g_0076F650[0x40];              /* units to keep (bit 7 kept, bit 6 forced; 0xFF free) */
extern u8 g_0076F690[0x6A];              /* motion packs to keep (bit 7 forced) */
extern u8 g_0076F6FA[0x8D];              /* weapons to keep */
extern u8 g_0076F787[4];                 /* items to keep */
extern u8 g_0076F790[0x30];
extern u8 g_0043FDB0[][0x10];
extern u16 g_0045CE30[3];                /* (small data) the weapon model kinds */

void func_00279240(void);
void func_002A7CE0(void);

/* 0x00279380, 0xC8 bytes. Keeps unit `k` loaded (`how` 0: kept, 1: kept and forced). */
int func_00279380(u32 k, int how)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        u8 *p = &g_0076F650[i];

        if (k == (*p & 0x3F)) {
            if (how < 2) {
                *p |= 0x80;
                if (how == 1)
                    *p |= 0x40;
            }
            return 1;
        }
    }
    for (i = 0; i < 0x40; i++) {
        u8 *p = &g_0076F650[i];

        if (*p == 0xFF) {
            *p = k;
            if (how < 2) {
                *p |= 0x80;
                if (how == 1)
                    *p |= 0x40;
            }
            return 1;
        }
    }
    return 0;
}

/* 0x00279450, 0x148 bytes. Keeps motion pack `k` loaded (officer kinds folded into their
 * groups; `forced` marks it). */
int func_00279450(int k, int forced)
{
    int i;

    if (forced == 0 && k > 0x19) {
        if (k >= 0x3E && k <= 0x48)
            k = 0x26;
        else if (k >= 0x49 && k <= 0x53)
            k = 0x2A;
        else if (k >= 0x54 && k <= 0x5C)
            k = 0x20;
        else if (k > 0x5C && k < 0x68)
            k = 0x21;
    }
    if (k == 0x2D)
        forced = 1;
    for (i = 0; i < 0x6A; i++) {
        if (k == (g_0076F690[i] & 0x7F)) {
            if (forced != 0)
                g_0076F690[i] |= 0x80;
            return 1;
        }
    }
    for (i = 0; i < 0x6A; i++) {
        if ((char)g_0076F690[i] == -1) {
            g_0076F690[i] = k;
            if (forced != 0)
                g_0076F690[i] |= 0x80;
            return 1;
        }
    }
    return 0;
}

/* 0x002795A0, 0x78 bytes. Keeps weapon `k` loaded. */
int func_002795A0(u32 k)
{
    int i;

    for (i = 0; i < 0x8D; i++) {
        if (k == g_0076F6FA[i])
            return 1;
    }
    for (i = 0; i < 0x8D; i++) {
        if ((char)g_0076F6FA[i] == -1) {
            g_0076F6FA[i] = k;
            return 1;
        }
    }
    return 0;
}

/* 0x00279620, 0x78 bytes. Keeps item `k` loaded. */
int func_00279620(u32 k)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (k == g_0076F787[i])
            return 1;
    }
    for (i = 0; i < 4; i++) {
        if ((char)g_0076F787[i] == -1) {
            g_0076F787[i] = k;
            return 1;
        }
    }
    return 0;
}

/* 0x002798B0, 0x158 bytes. Asks for everything on the lists to be loaded. */
void func_002798B0(int a)
{
    int i;

    for (i = 0; i < 0x40; i++) {
        u8 *p = &g_0076F650[i];

        if (*p != 0xFF && func_0032E7B0() != 0) {
            u32 c = 0;

            if (*p < 0x1C)
                c = func_00328B00(*p);
            func_001BD180(*p, a, 0, c);
        }
    }
    for (i = 0; i < 0x6A; i++) {
        u8 v = g_0076F690[i];

        if (v != 0xFF)
            func_0017C6D0(v & 0x7F, (v & 0x80) != 0, 0);
    }
    for (i = 0; i < 0x8D; i++) {
        if ((char)g_0076F6FA[i] != -1)
            func_0016CFB0(g_0076F6FA[i], 0);
    }
    for (i = 0; i < 4; i++) {
        if ((char)g_0076F787[i] != -1)
            func_002A7AF0(g_0076F787[i], 0);
    }
}

/* 0x00279A10, 0x104 bytes. Sets up what was loaded. */
void func_00279A10(void)
{
    int i, j;

    for (i = 0; i < 0x40; i++) {
        if ((char)g_0076F650[i] != -1)
            func_001BD2C0(g_0076F650[i]);
    }
    for (i = 0; i < 0x6A; i++) {
        if (g_0076F690[i] != 0xFF)
            func_0017C7D0(g_0076F690[i] & 0x7F);
    }
    func_001BE030();
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 0x8D; j++) {
            if ((char)g_0076F6FA[j] != -1)
                func_0016D060(g_0076F6FA[j], (void *)PS2_PTR(g_0045CE30[i]), 0);
        }
    }
    func_002A7BF0();
    func_00279240();
}

/* 0x00279B20, 0x3C bytes, matching. */
void func_00279B20(void)
{
    func_001BD540();
    func_0017C970();
    func_001BE040();
    func_002A7CE0();
    func_00279240();
}

/* Decodes packed file `src` into `out` with a window of `bits` bits: 64-bit flag words from +0x10
 * (bit set: a literal byte, clear: a back reference of 16 bits, length in its top bits + 3,
 * 0 ends). */
static void unpack(u8 *src, u8 *out, int bits)
{
    u64 *flags = (u64 *)(src + 8), mask = 0;
    u16 *refs = (u16 *)(src + (*(u32 *)(src + 8) & ~3));
    u8 *lits = src + (*(u32 *)(src + 0xC) & ~3), *dst = out;
    u32 n = 0, win = (1 << bits) - 1;

    for (;;) {
        u16 r;
        u8 *from;
        int len;

        mask >>= 1;
        if (mask == 0) {
            mask = 0x8000000000000000ULL;
            flags++;
        }
        if ((*flags & mask) != 0) {
            n++;
            *dst++ = *lits++;
            continue;
        }
        r = *refs;
        if ((r & win) == 0)
            return;
        from = out + (n & ~win) + (r & win) - 1;
        if ((n & win) < (u32)(r & win))
            from -= win + 1;
        len = (r >> bits) + 3;
        refs++;
        n += len;
        for (; len != 0; len--)
            *dst++ = *from++;
    }
}

/* 0x00279B60, 0xEC bytes. Unpacks with a 1 KB window. */
void func_00279B60(u8 *src, u8 *out)
{
    unpack(src, out, 10);
}

/* 0x00279C50, 0xEC bytes. With a 2 KB window. */
void func_00279C50(u8 *src, u8 *out)
{
    unpack(src, out, 11);
}

/* 0x00279D40, 0xEC bytes. With a 4 KB window. */
void func_00279D40(u8 *src, u8 *out)
{
    unpack(src, out, 12);
}

/* 0x00279E30, 0xEC bytes. With an 8 KB window. */
void func_00279E30(u8 *src, u8 *out)
{
    unpack(src, out, 13);
}

/* 0x00279F20, 0x84 bytes. Unpacks packed file `src` (window kind at +0). */
void func_00279F20(int *src, u8 *out)
{
    int k = *src;

    if (k == 3)
        func_00279E30((u8 *)src, out);
    else if (k == 2)
        func_00279D40((u8 *)src, out);
    else if (k == 1)
        func_00279C50((u8 *)src, out);
    else if (k == 0)
        func_00279B60((u8 *)src, out);
}

/* 0x00279FB0, 0x38 bytes. Unpacks it into a new block (size at +4); the block. */
u8 *func_00279FB0(int *src)
{
    u8 *out = func_00102DB0(0x10, src[1]);

    func_00279F20(src, out);
    return out;
}

/* 0x00279FF0, 0x14 bytes, matching. */
u8 *func_00279FF0(int k)
{
    return g_0043FDB0[k];
}

/* 0x0027A010, 0x24 bytes, matching. */
void func_0027A010(void)
{
    func_00118850(g_0076F790, 0x30);
}
