/*
 * sw2e_mem.h - the PS2 memory model of the port (see docs/port.md).
 *
 * The game keeps 32-bit PS2 addresses in its data: in tables of the boot executable, in heap
 * structures, in lists, in the save image. On the PS2 an address is a pointer. On the PC (64-bit)
 * the whole EE RAM is one 32 MB block. The boot executable's data is loaded at its PS2 addresses
 * inside it, and an address stored in game data stays a 32-bit PS2 address. Native pointers only
 * live in C locals and parameters.
 *
 *   ps2ptr          a 32-bit PS2 address stored in game data (a field, a global, a table entry)
 *   PS2_PTR(a)      the native pointer for PS2 address `a`
 *   PS2_ADDR(p)     the PS2 address of native pointer `p` (which must point into PS2 memory)
 *
 * On the PS2 build (CodeWarrior, matching) both are plain casts, so the generated code does not
 * change. The PC build defines SW2E_PC.
 *
 * It uses only the basic C types, so it can be included anywhere.
 */

#ifndef SW2E_MEM_H
#define SW2E_MEM_H

typedef unsigned int ps2ptr;

#ifdef SW2E_PC

#define PS2_RAM_SIZE 0x02000000u         /* 32 MB of EE RAM */
#define PS2_SPR_BASE 0x70000000u         /* the scratchpad, 16 KB */
#define PS2_SPR_SIZE 0x4000u

extern unsigned char *sw2e_ram;                     /* the PS2 RAM block, allocated by the port */
extern unsigned char *sw2e_spr;                     /* the scratchpad */

/* The native pointer for PS2 address `a` (RAM mirrors at 0x20000000/0x30000000 included). */
static inline void *sw2e_ptr(unsigned int a)
{
    if (a == 0)
        return (void *)0;
    if ((a & 0xF0000000u) == PS2_SPR_BASE)
        return sw2e_spr + (a & (PS2_SPR_SIZE - 1));
    return sw2e_ram + (a & (PS2_RAM_SIZE - 1));
}

/* The PS2 address of native pointer `p`, which must point into the RAM block or the scratchpad. */
static inline unsigned int sw2e_addr(const void *p)
{
    const unsigned char *q = (const unsigned char *)p;

    if (q == 0)
        return 0;
    if (q >= sw2e_spr && q < sw2e_spr + PS2_SPR_SIZE)
        return PS2_SPR_BASE + (unsigned int)(q - sw2e_spr);
    return (unsigned int)(q - sw2e_ram);
}

#define PS2_PTR(a) sw2e_ptr((unsigned int)(a))
#define PS2_ADDR(p) sw2e_addr(p)
/* A global at a fixed PS2 address (used by the PC build's rewritten declarations). */
#define PS2_MEM(a) ((unsigned char *)sw2e_ptr(a))

#else /* the PS2 build */

#define PS2_PTR(a) ((void *)(a))
#define PS2_ADDR(p) ((unsigned int)(p))

#endif

#endif
