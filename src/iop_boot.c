/*
 * iop_boot.c - starting the I/O processor (original source file unknown; between the GS
 * packets and main.c's game set-up, 0x00106420-0x00106748).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. The called functions belong to Sony's libraries (their
 * likely names are given in the comments).
 *
 * The IOP is rebooted with the disc's IOPRP300.IMG, then the game's nine IOP modules are loaded
 * from one file, MODULES.BIN: the table at 0x00400C30 gives each module's offset and size in
 * quadwords. The file is read into the EE's memory, and each module is copied to the IOP by DMA
 * and started from there.
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* A file found on the disc (sceCdlFILE). */
typedef struct {
    u32 lsn;
    u32 size;
    u8 rest[0x28];
} DiscFile;

/* A read mode (sceCdRMode). */
typedef struct {
    u8 trycount;
    u8 spindlctrl;
    u8 datapattern;
    u8 pad;
} ReadMode;

/* A DMA copy to the IOP (sceSifDmaData). */
typedef struct {
    u32 data;
    u32 addr;
    int size;
    int mode;
} SifDma;

typedef struct {
    u32 offset;              /* quadwords */
    u32 size;
} Module;

extern Module g_00400C30[9];             /* the modules in MODULES.BIN */
extern SifDma g_00560820;

extern u8 *g_0045D1E4;                   /* (small data) the VIF1 DMA channel */
extern u8 *g_0045D1E0;                   /* (small data) the GIF DMA channel */

void func_00125870(void);                /* sceGsResetPath? */
void func_0011B078(int a);               /* sceDmaReset? */
u8 *func_0011B050(int channel);          /* sceDmaGetChan? */
void func_00130090(void);                /* sceSifInitIopHeap? */
int func_001194A0(DiscFile *file, const char *name, int a);   /* sceCdSearchFile? */
int func_0011A3E8(u32 lsn, u32 sectors, void *buffer, ReadMode *mode);  /* sceCdRead? */
int func_001199B0(int mode);             /* sceCdSync? */
u32 func_00130118(u32 size);             /* sceSifAllocIopHeap? */
u32 func_001281A0(SifDma *dma, int count);  /* sceSifSetDma */
int func_00130D78(u32 iop_addr, int a, int b);  /* sceSifLoadModuleBuffer? */
int func_00130280(u32 iop_addr);         /* sceSifFreeIopHeap? */
void func_0012B3A0(int a);               /* sceSifInitRpc? */
int func_00119CC8(int mode);             /* sceCdInit? */
int func_00131510(const char *image);    /* sceSifRebootIop? */
int func_001314C0(void);                 /* sceSifSyncIop? */
void func_00130770(void);                /* sceSifInitIopHeap / sceFsReset? */
int func_0011A920(int media);            /* sceCdMmode? */
void func_0012CF00(void);
void *func_00102DB0(int align, u32 size);
void func_00102EC0(void *data);
void FlushCache(int a);
int GetThreadId(void);
int ChangeThreadPriority(int thread, int priority);

/* 0x00106420, 0x70 bytes. Resets the GS path and the DMA; tag transfer on for VIF1, off for
 * the GIF. */
void func_00106420(void)
{
    func_00125870();
    func_0011B078(1);
    g_0045D1E4 = func_0011B050(1);
    *g_0045D1E4 = (*g_0045D1E4 & ~0x40) | 0x40;
    g_0045D1E0 = func_0011B050(2);
    *g_0045D1E0 = *g_0045D1E0 & ~0x40;
}

/* 0x00106490, 0x198 bytes. Loads the IOP modules from MODULES.BIN (a module that fails to start
 * is tried again). */
void func_00106490(void)
{
    Module modules[9];
    DiscFile file;
    ReadMode mode;
    u8 *buffer;
    u32 iop, largest, i;

    for (i = 0; i < 9; i++)
        modules[i] = g_00400C30[i];
    func_00130090();
    func_001194A0(&file, "\\MODULES\\MODULES.BIN;1", 0);
    mode.spindlctrl = 1;
    mode.trycount = 0;
    mode.datapattern = 0;
    buffer = func_00102DB0(0x40, (file.size + 0x7FF) & ~0x7FF);
    func_0011A3E8(file.lsn, (file.size + 0x7FF) >> 11, buffer, &mode);
    func_001199B0(0);
    largest = 0;
    for (i = 0; i < 9; i++) {
        if (largest < modules[i].size)
            largest = modules[i].size;
    }
    iop = func_00130118(largest << 4);
    i = 0;
    while (i < 9) {
        g_00560820.addr = iop;
        g_00560820.mode = 0;
        g_00560820.data = (u32)(buffer + modules[i].offset * 16);
        g_00560820.size = modules[i].size << 4;
        func_001281A0(&g_00560820, 1);
        if (func_00130D78(iop, 0, 0) >= 0)
            i++;
    }
    func_00130280(iop);
    func_00102EC0(buffer);
}

/* 0x00106630, 0xD0 bytes. Reboots the IOP with the disc's IOPRP300.IMG and sets the drive to
 * DVD. */
void func_00106630(void)
{
    func_0012B3A0(0);
    while (func_00119CC8(0) == 0)
        ;
    while (func_00131510("cdrom0:\\MODULES\\IOPRP300.IMG;1") == 0)
        ;
    while (func_001314C0() == 0)
        ;
    func_0012B3A0(0);
    func_00130770();
    while (func_00119CC8(0) == 0)
        ;
    while (func_0011A920(2) == 0)
        ;
    func_0012CF00();
}

/* 0x00106700, 0x48 bytes, matching. Starts the IOP side, then lowers the main thread's priority to 2. */
void func_00106700(void)
{
    func_00106630();
    func_00106490();
    func_00106420();
    FlushCache(0);
    ChangeThreadPriority(GetThreadId(), 2);
}
