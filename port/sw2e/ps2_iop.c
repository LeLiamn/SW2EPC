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

/* ---- more of the disc library ---- */

int func_0011A1C8(int mode) { (void)mode; return 2; }     /* sceCdDiskReady: 2 = ready */
int func_0011A720(void) { return 0x0A; }                  /* sceCdStatus: paused, a disc in */
int func_0011A7D0(void) { return 0; }                     /* sceCdGetError: none */
int func_0011A868(void) { return 1; }                     /* sceCdBreak */

/* sceCdReadIOPm(lsn, sectors, buffer, mode): a read into IOP memory, for the sound driver's
 * streams. There is no IOP memory on the PC: the sound streams will be read by the port's own
 * mixer, so nothing is read here. */
int func_0011A5C8(unsigned int lsn, unsigned int sectors, void *buffer, void *mode)
{
    (void)lsn; (void)sectors; (void)buffer; (void)mode;
    return 1;
}

/* sceDmaSync-like (0x0011B620): transfers end at once */
void func_0011B620(int chan, int a, int b) { (void)chan; (void)a; (void)b; }

/* ---- files through the C library (open / read / lseek / close on cdrom0:) ----
 * The game opens files on the disc by path ("cdrom0:\\PATH;1"); they are read through the
 * platform's disc calls, which take the path without the device. */

#define MAX_FILES 16
static struct { int used; char path[128]; long long size, pos; } g_files[MAX_FILES];

static const char *disc_path(const char *path)
{
    const char *p = strchr(path, ':');

    return p ? p + 1 : path;
}

/* open(path, mode) */
int func_0012D168(const char *path, int mode)
{
    int i;
    long long size;

    (void)mode;
    size = P->disc_file_size(disc_path(path));
    if (size < 0)
        return -1;
    for (i = 0; i < MAX_FILES; i++) {
        if (!g_files[i].used) {
            g_files[i].used = 1;
            strncpy(g_files[i].path, disc_path(path), sizeof(g_files[i].path) - 1);
            g_files[i].size = size;
            g_files[i].pos = 0;
            return i + 3;                   /* 0-2 are the console's */
        }
    }
    return -1;
}

int func_0012D3F8(int fd)                                 /* close */
{
    if (fd < 3 || fd >= MAX_FILES + 3 || !g_files[fd - 3].used)
        return -1;
    g_files[fd - 3].used = 0;
    return 0;
}

int func_0012D570(int fd, int offset, int whence)         /* lseek: 0 set, 1 current, 2 end */
{
    long long base;

    if (fd < 3 || fd >= MAX_FILES + 3 || !g_files[fd - 3].used)
        return -1;
    base = whence == 0 ? 0 : whence == 1 ? g_files[fd - 3].pos : g_files[fd - 3].size;
    g_files[fd - 3].pos = base + offset;
    return (int)g_files[fd - 3].pos;
}

int func_0012D7B0(int fd, void *buffer, int size)         /* read */
{
    long long n;

    if (fd < 3 || fd >= MAX_FILES + 3 || !g_files[fd - 3].used || size < 0)
        return -1;
    n = P->disc_read_file(g_files[fd - 3].path, (unsigned long long)g_files[fd - 3].pos, buffer, (size_t)size);
    if (n > 0)
        g_files[fd - 3].pos += n;
    return (int)n;
}

/* ---- kernel ---- */

void func_00128060(int a) { (void)a; }                    /* FlushCache */
int func_001288C0(int cause) { (void)cause; return 0; }   /* EnableIntc */
void func_00128990(int channel) { (void)channel; }        /* DisableDmac */

/* ---- IPU (movie pictures): to be written with the movie player ---- */

void func_00127670(int a, int b) { (void)a; (void)b; }    /* sceIpuSync */
void func_00127750(void) {}                               /* sceIpuInit */
