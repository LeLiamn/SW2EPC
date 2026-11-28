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
char *func_001206B0(char *to, const char *from) { return strcat(to, from); }                     /* strcat */
unsigned int func_00120A40(const char *s) { return (unsigned int)strlen(s); }                    /* strlen */

/* A %s argument: the decompiled code passes strings as native pointers or as PS2 addresses held
 * in integers (both arrive as 8-byte slots on x64). A value below the end of the PS2 RAM is a PS2
 * address (the PS2 RAM block itself is allocated higher, so no native pointer is that low).
 * An integer passed on the stack may come with a garbage upper half: wrap such arguments in
 * PS2_PTR at the call site when one shows up. */
static const char *str_arg(unsigned long long v)
{
    unsigned int low = (unsigned int)v;

    if (v >> 32 == 0 && low < 0x02000000u)
        return low ? (const char *)(sw2e_ram + low) : "(null)";
    return (const char *)v;
}

/* sprintf: formats one conversion at a time, so %s can take either kind of string */
int func_001204B0(char *out, const char *format, ...)
{
    va_list ap;
    char spec[32], *o = out;
    const char *f = format;

    va_start(ap, format);
    while (*f) {
        const char *s = f;
        size_t n;

        if (*f != '%') {
            *o++ = *f++;
            continue;
        }
        f++;
        if (*f == '%') {
            *o++ = '%';
            f++;
            continue;
        }
        while (*f && strchr("-+ #0123456789.*hlLqjzt", *f))
            f++;
        if (!*f)
            break;
        n = (size_t)(f - s + 1);
        if (n >= sizeof(spec))
            n = sizeof(spec) - 1;
        memcpy(spec, s, n);
        spec[n] = 0;
        if (strchr(spec, '*')) {                  /* not used by the game; keep it simple */
            sw2e_platform->log(1, "sprintf: '*' in \"%s\" not supported", format);
            break;
        }
        switch (*f) {
        case 's':
            o += sprintf(o, spec, str_arg(va_arg(ap, unsigned long long)));
            break;
        case 'f': case 'e': case 'g': case 'E': case 'G':
            o += sprintf(o, spec, va_arg(ap, double));
            break;
        case 'p':
            o += sprintf(o, spec, va_arg(ap, void *));
            break;
        default:                                   /* d i u x X o c: 32-bit on the PS2 */
            if (strstr(spec, "ll") || strchr(spec, 'q'))
                o += sprintf(o, spec, va_arg(ap, long long));
            else
                o += sprintf(o, spec, va_arg(ap, int));
            break;
        }
        f++;
    }
    *o = 0;
    va_end(ap);
    return (int)(o - out);
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

/* ---- more of the C library and its maths ---- */

#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int func_0011B740(int v) { return abs(v); }               /* abs */
int func_00121068(int c) { return toupper(c); }           /* toupper */
float func_00136D70(float a) { return tanf(a); }          /* tanf */
float func_00136E00(float y, float x) { return atan2f(y, x); }   /* atan2f */
float func_00136E18(float x, float y) { return fmodf(x, y); }    /* fmodf */

/* ---- GCC's software doubles (the EE has no double unit), as the decompiled code calls them ---- */

double func_00124F18(double a, double b) { return a * b; }         /* __muldf3 */
double func_00125450(unsigned int v) { return (double)(int)v; }   /* __floatsidf */
int func_001438D0(double a, double b) { return a < b; }            /* __ltdf2 < 0 */
int func_001438F0(double a, double b) { return a <= b; }           /* __ledf2 < 1 */
int func_00143920(double a, double b) { return a > b; }            /* __gtdf2 > 0 */
int func_00143940(double a, double b) { return a >= b; }           /* __gedf2 >= 0 */

int func_0011B758(const char *s) { return (int)strtol(s, 0, 10); }    /* atoi */
int func_0011EAE8(const void *a, const void *b, unsigned int n) { return memcmp(a, b, n); }   /* memcmp */
