/*
 * mc_state.c - resets of the memory card state records (original source file unknown; around
 * 0x0022D550, after sceMcInit at start-up, see func_0022DE80).
 *
 * Decompiled by reading the original machine code (checked against the disassembly). Unknown
 * functions and globals keep neutral names (func_/g_ + address); comments with a question mark
 * are hypotheses.
 *
 * Three tables follow each other: a 0x18-byte state at 0x0074A000 (func_0022D550), records of
 * 0x98 bytes from 0x0074A0A0, and records of 0x14 bytes from 0x0074A140.
 */

#define SW2E_FILE_MC_STATE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned int u32;

extern u8 g_0074A0A0[];                   /* records of 0x98 bytes (per card port?) */
extern u8 g_0074A140[];                   /* records of 0x14 bytes */

/* 0x0022D590, 0x40 bytes, matching. Resets record `i` of the 0x98-byte table: three -1 words, three 0. */
void func_0022D590(int i)
{
    u8 *r = g_0074A0A0 + i * 0x98;

    *(int *)(r + 8) = -1;
    *(int *)(r + 0) = -1;
    *(int *)(r + 4) = -1;
    *(int *)(r + 0xC) = 0;
    *(int *)(r + 0x10) = 0;
    *(int *)(r + 0x14) = 0;
}

/* 0x0022D5D0, 0x2C bytes, matching. Resets record `i` of the 0x14-byte table (all but its second word). */
void func_0022D5D0(int i)
{
    u8 *r = g_0074A140 + i * 0x14;

    *(int *)(r + 0) = 0;
    *(int *)(r + 8) = 0;
    *(int *)(r + 0xC) = 0;
    *(int *)(r + 0x10) = 0;
}
