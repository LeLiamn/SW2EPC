/*
 * ps2_libc.c - the C library of the PS2 executable (newlib, linked from the Sony SDK) for the PC
 * build. The game calls these functions by their PS2 addresses; on the PC they work inside the
 * PS2 memory block, so the addresses they hand out stay PS2 addresses (docs/port.md).
 *
 * Each function is named after its PS2 address, with what it is in the comment.
 */
#include <string.h>
#include "upp.h"

extern unsigned char *sw2e_ram;
extern const upp_platform *sw2e_platform;

/* ---- strings and memory ---- */

#include <stdarg.h>
#include <stdio.h>

void *func_0011EB80(void *to, const void *from, unsigned int n) { return memmove(to, from, n); }   /* memcpy */
void *func_0011ED38(void *to, int c, unsigned int n) { return memset(to, c, n); }               /* memset */
char *func_00120928(char *to, const char *from) { return strcpy(to, from); }                     /* strcpy */
unsigned int func_00120A40(const char *s) { return (unsigned int)strlen(s); }                    /* strlen */

/* sprintf */
int func_001204B0(char *out, const char *format, ...)
{
    va_list ap;
    int n;

    va_start(ap, format);
    n = vsprintf(out, format, ap);
    va_end(ap);
    return n;
}

/* ---- the heap (newlib malloc) ----
 * The PS2 heap starts at the end of the executable's BSS (0x007C0000) and grows up to the stack.
 * A simple allocator is enough here: the game touches this heap only to find the top of memory
 * (it allocates almost all of it once and frees it at once), and runs its own allocator
 * (src/heap.c) for everything else. */
#define HEAP_START 0x007C0000u
#define HEAP_END   0x02000000u          /* the end of the 32 MB (the game sizes it to the top itself) */

static unsigned int g_heap_top = HEAP_START;
static unsigned int g_heap_last;        /* the last block, so freeing it gives the space back */

/* 0x0011DFB0: malloc(size) */
void *func_0011DFB0(unsigned int size)
{
    unsigned int a = (g_heap_top + 15) & ~15u;

    if (size > HEAP_END - a) {
        sw2e_platform->log(1, "PS2 malloc(0x%X): out of PS2 heap", size);
        return 0;
    }
    g_heap_last = a;
    g_heap_top = a + size;
    return sw2e_ram + a;
}

/* 0x0011E008: free(p) */
void func_0011E008(void *p)
{
    unsigned int a;

    if (!p)
        return;
    a = (unsigned int)((unsigned char *)p - sw2e_ram);
    if (a == g_heap_last)
        g_heap_top = g_heap_last;           /* the last block: its space comes back */
}
