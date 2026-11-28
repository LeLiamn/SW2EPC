/*
 * sw2e_entry.c - the game side of the port: upp_game_entry() for Samurai Warriors 2: Empires.
 *
 * init() sets up the PS2 memory model of docs/port.md: one 32 MB block for the EE's RAM and a
 * 16 KB block for the scratchpad, then loads the player's own boot executable from the disc into
 * the block at its PS2 addresses (its code is not used; its data segments hold the game's tables,
 * strings and initial values). run() then calls the decompiled main() (src/main.c, renamed
 * sw2e_ps2_main for the PC build).
 *
 * The PS2 platform code (CDVD, SIF/IOP, GS, DMA, interrupts) is not replaced yet: a first run stops
 * at the first function that is not decompiled (see tools/pc_build.py, which turns every missing
 * function into a stop that names it).
 */
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include "upp.h"

#define PS2_RAM_SIZE 0x02000000u
#define PS2_SPR_SIZE 0x4000u

unsigned char *sw2e_ram;
unsigned char *sw2e_spr;
unsigned char *sw2e_hw;                 /* stand-ins for the EE hardware registers (64 KB) */
unsigned char *sw2e_gs;                 /* and the GS privileged registers (8 KB) */
const upp_platform *sw2e_platform;

int sw2e_ps2_main(int argc, char **argv);

static int rd16(const unsigned char *p) { return p[0] | p[1] << 8; }
static unsigned rd32(const unsigned char *p) { return p[0] | p[1] << 8 | p[2] << 16 | (unsigned)p[3] << 24; }

/* Copies the PT_LOAD segments of an ELF32 LE (MIPS) file into the PS2 RAM block. */
static int load_elf(const unsigned char *elf, size_t size)
{
    unsigned phoff, i, n;

    if (size < 0x34 || memcmp(elf, "\177ELF", 4) != 0 || elf[4] != 1 || elf[5] != 1)
        return 0;
    phoff = rd32(elf + 0x1C);
    n = rd16(elf + 0x2C);
    for (i = 0; i < n; i++) {
        const unsigned char *ph = elf + phoff + i * rd16(elf + 0x2A);
        unsigned off = rd32(ph + 4), vaddr = rd32(ph + 8), filesz = rd32(ph + 16), memsz = rd32(ph + 20);

        if (rd32(ph) != 1)                  /* PT_LOAD */
            continue;
        if ((vaddr & 0x1FFFFFFF) + memsz > PS2_RAM_SIZE || off + filesz > size)
            return 0;
        memcpy(sw2e_ram + (vaddr & 0x1FFFFFFF), elf + off, filesz);
        memset(sw2e_ram + (vaddr & 0x1FFFFFFF) + filesz, 0, memsz - filesz);
        sw2e_platform->log(2, "segment 0x%08X: 0x%X bytes from the disc", vaddr, filesz);
    }
    return 1;
}

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
/* A crash in the game's code: its place in the executable (exe offset, for addr2line), written
 * before the process ends. Only access violations are reported. */
static LONG WINAPI sw2e_crash(EXCEPTION_POINTERS *e)
{
    if (e->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        HMODULE base = GetModuleHandleA(NULL);

        fprintf(stderr, "[crash] access violation at exe offset 0x%llx, address %p\n",
                (unsigned long long)((char *)e->ExceptionRecord->ExceptionAddress - (char *)base + 0x140000000ULL),
                e->ExceptionRecord->NumberParameters > 1 ? (void *)e->ExceptionRecord->ExceptionInformation[1] : 0);
        fflush(stderr);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
#endif

static int sw2e_init(const upp_platform *platform)
{
#ifdef _WIN32
    AddVectoredExceptionHandler(1, sw2e_crash);
#endif
    const upp_release *rel;
    int64_t size;
    unsigned char *elf;

    sw2e_platform = platform;
    if (platform->version != UPP_PLATFORM_VERSION || platform->size < (int)sizeof(upp_platform)) {
        if (platform->log)
            platform->log(0, "this runtime's platform table is too old (version %d, size %d)",
                          platform->version, platform->size);
        return 0;
    }
    rel = platform->release();
    sw2e_ram = calloc(1, PS2_RAM_SIZE);
    sw2e_spr = calloc(1, PS2_SPR_SIZE);
    sw2e_hw = calloc(1, 0x10000);
    sw2e_gs = calloc(1, 0x2000);
    if (!sw2e_ram || !sw2e_spr || !sw2e_hw || !sw2e_gs) {
        platform->log(0, "out of memory for the PS2 RAM block");
        return 0;
    }
    size = platform->disc_file_size(rel->boot_path);
    if (size <= 0) {
        platform->log(0, "boot executable %s not found on the disc", rel->boot_path);
        return 0;
    }
    elf = malloc((size_t)size);
    if (!elf || platform->disc_read_file(rel->boot_path, 0, elf, (size_t)size) != size || !load_elf(elf, (size_t)size)) {
        platform->log(0, "cannot load the boot executable %s", rel->boot_path);
        free(elf);
        return 0;
    }
    free(elf);
    platform->log(2, "boot executable loaded (%lld bytes)", (long long)size);
    return 1;
}

static jmp_buf g_quit;

/* Leaves run() from anywhere in the game (the window was closed: platform->vsync() returned 0). */
void sw2e_quit(void)
{
    longjmp(g_quit, 1);
}

static void sw2e_run(void)
{
    static char name[] = "cdrom0:\\SLES_546.24;1";
    char *argv[] = { name, 0 };

    if (setjmp(g_quit) == 0)
        sw2e_ps2_main(1, argv);
    sw2e_platform->log(2, "run() ends");
}

static void sw2e_shutdown(void)
{
    free(sw2e_ram);
    free(sw2e_spr);
    free(sw2e_hw);
    free(sw2e_gs);
    sw2e_ram = sw2e_spr = sw2e_hw = sw2e_gs = 0;
}

/* PC data the game keeps as a PS2 address (src/sw2e_mem.h): each pointer seen gets a 64 KB
 * window, so offsets the game adds to the address still land in the same data. */
#define PS2_FOREIGN_BASE 0x50000000u     /* as in src/sw2e_mem.h */
#define FOREIGN_MAX 4096
static const unsigned char *g_foreign[FOREIGN_MAX];
static int g_foreign_count;

void *sw2e_foreign_ptr(unsigned int a)
{
    unsigned int i = (a - PS2_FOREIGN_BASE) >> 16;

    if (i >= (unsigned int)g_foreign_count)
        sw2e_platform->fatal("PS2 address 0x%08X: no PC data there", a);
    return (void *)(g_foreign[i] + (a & 0xFFFF));
}

unsigned int sw2e_foreign_addr(const void *p)
{
    const unsigned char *q = (const unsigned char *)p;
    int i;

    for (i = 0; i < g_foreign_count; i++)
        if (q >= g_foreign[i] && q < g_foreign[i] + 0x10000)
            return PS2_FOREIGN_BASE + ((unsigned int)i << 16) + (unsigned int)(q - g_foreign[i]);
    if (g_foreign_count == FOREIGN_MAX)
        sw2e_platform->fatal("too many PC pointers stored as PS2 addresses");
    g_foreign[g_foreign_count] = q;
    return PS2_FOREIGN_BASE + ((unsigned int)g_foreign_count++ << 16);
}

/* Called by the stops of the functions not decompiled yet (generated by tools/pc_build.py):
 * platform->fatal() logs it, tells the player and ends the process (never returns). */
void sw2e_missing(const char *name)
{
    sw2e_platform->fatal("not decompiled yet: %s", name);
}

const upp_game_api *upp_game_entry(void)
{
    static const upp_game_api api = {
        UPP_PLATFORM_VERSION, sizeof(upp_game_api), "sw2e", 50.0, UPP_THREADS_PS2,
        sw2e_init, 0, sw2e_run, sw2e_shutdown
    };
    return &api;
}
