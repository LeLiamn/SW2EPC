/*
 * ps2_iop.c - the Sony library calls that talk to the IOP (the PS2's second processor: disc
 * drive, sound, pads, memory card) and to the DMA controller, for the PC build. There is no IOP
 * on the PC: booting it and loading its modules succeed at once, and disc reads go through the
 * platform (upp_platform's disc calls).
 *
 * Each function is named after its PS2 address; the comment gives the Sony name (from what the
 * function does and how the game calls it). Generic for PS2 games.
 */
#include <string.h>
#include "upp.h"

extern unsigned char *sw2e_ram;
extern unsigned char *sw2e_hw;
extern const upp_platform *sw2e_platform;
#define P sw2e_platform

/* sceCdlFILE */
typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned char rest[0x10];
} CdFile;

/* ---- SIF / IOP: nothing to do on the PC ---- */

void func_0012B3A0(int a) { (void)a; }                    /* sceSifInitRpc */
int func_00131510(const char *image) { (void)image; return 1; }   /* sceSifRebootIop */
int func_001314C0(void) { return 1; }                     /* sceSifSyncIop */
void func_00130770(void) {}                               /* sceFsReset */
void func_00130090(void) {}                               /* sceSifInitIopHeap */
unsigned int func_00130118(unsigned int size) { (void)size; return 0x00100000; }  /* sceSifAllocIopHeap: an IOP address */
int func_00130280(unsigned int iop_addr) { (void)iop_addr; return 0; }   /* sceSifFreeIopHeap */
unsigned int func_001281A0(void *dma, int count) { (void)dma; (void)count; return 1; }  /* sceSifSetDma */
int func_00130D78(unsigned int iop_addr, int a, int b) { (void)iop_addr; (void)a; (void)b; return 0; }  /* sceSifLoadModuleBuffer */

/* 0x0012CF00: clears a word and 4 bytes of the CD library's state (both PS2 data) */
int func_0012CF00(void)
{
    memset(sw2e_ram + 0x403B5C, 0, 4);
    memset(sw2e_ram + 0x567528, 0, 4);
    return 0;
}

/* ---- the disc (sceCd...) ---- */

int func_00119CC8(int mode) { (void)mode; return 1; }      /* sceCdInit */
int func_0011A920(int media) { (void)media; return 1; }    /* sceCdMmode */
int func_001199B0(int mode) { (void)mode; return 0; }      /* sceCdSync: reads are synchronous here */

/* sceCdSearchFile(file, name, ?): the file's first sector and size */
int func_001194A0(CdFile *file, const char *name, int a)
{
    int64_t lsn = P->disc_file_lsn(name), size = P->disc_file_size(name);
    const char *base;

    (void)a;
    if (lsn < 0 || size < 0) {
        P->log(1, "sceCdSearchFile: %s not on the disc", name);
        return 0;
    }
    memset(file, 0, sizeof(*file));
    file->lsn = (unsigned int)lsn;
    file->size = (unsigned int)size;
    base = strrchr(name, '\\');
    strncpy(file->name, base ? base + 1 : name, sizeof(file->name) - 1);
    return 1;
}

/* sceCdRead(lsn, sectors, buffer, mode): read at once */
int func_0011A3E8(unsigned int lsn, unsigned int sectors, void *buffer, void *mode)
{
    (void)mode;
    if (!P->disc_read_sectors(lsn, sectors, buffer)) {
        P->log(0, "sceCdRead: sectors %u-%u cannot be read", lsn, lsn + sectors - 1);
        return 0;
    }
    return 1;
}

/* ---- DMA (sceDma...) ---- */

/* the EE DMA channels' register blocks */
static const unsigned int g_dma_base[10] = {
    0x10008000, 0x10009000, 0x1000A000, 0x1000B000, 0x1000B400,
    0x1000C000, 0x1000C400, 0x1000C800, 0x1000D000, 0x1000D400,
};

void func_00125870(void) {}                               /* sceGsResetPath */
void func_0011B078(int a) { (void)a; }                    /* sceDmaReset */

/* sceDmaGetChan(channel): the channel's register block (stand-in registers on the PC) */
unsigned char *func_0011B050(int channel)
{
    if (channel < 0 || channel > 9)
        return 0;
    return sw2e_hw + (g_dma_base[channel] & 0xFFFF);
}
