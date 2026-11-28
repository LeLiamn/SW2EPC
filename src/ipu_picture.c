/*
 * ipu_picture.c - pictures decoded by the IPU (original source file unknown; 0x00143970-
 * 0x00144070, after Sony's libraries).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Some pictures are MPEG intra frames (the "ipu2" files, see docs/formats/IPU.md). They are
 * decoded by the IPU into 16 x 16 tiles of 32-bit pixels: the coded data goes to the IPU by DMA
 * (channel 4), the tiles come back by DMA (channel 3) into one of two buffers (one per frame),
 * and each tile is then uploaded to the GS by its own upload packet (gs_packet.c). Decodes are
 * queued (up to 4 waiting) and started one after the other by the end-of-transfer handler of
 * channel 3.
 */

#define SW2E_FILE_IPU_PICTURE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define REG_IPU_CMD            (*(volatile u32 *)0x10002000)
#define REG_IPU_CTRL           (*(volatile u32 *)0x10002010)
#define REG_DMAC_3_CHCR        (*(volatile u32 *)0x1000B000)   /* from the IPU */
#define REG_DMAC_3_MADR        (*(volatile u32 *)0x1000B010)
#define REG_DMAC_3_QWC         (*(volatile u32 *)0x1000B020)
#define REG_DMAC_4_CHCR        (*(volatile u32 *)0x1000B400)   /* to the IPU */
#define REG_DMAC_4_MADR        (*(volatile u32 *)0x1000B410)
#define REG_DMAC_4_QWC         (*(volatile u32 *)0x1000B420)
#define REG_DMAC_ENABLER       (*(volatile u32 *)0x1000F520)
#define REG_DMAC_ENABLEW       (*(volatile u32 *)0x1000F590)

#define g_70000150 (*(int *)0x70000150)          /* frame index: 0 or 1 */

/* A picture to decode. */
typedef struct {
    u8 *data;                /* the coded data */
    u32 size;
    u8 *header;              /* +8 the ipu2 header (+8 width, +0xA height) */
    int tiles;               /* +0xC 16 x 16 tiles */
    int dbp;                 /* +0x10 the GS buffer */
    u8 *packets[2];          /* +0x14 one upload packet (0x90 bytes) per tile, per frame */
    u8 *pixels[2];           /* +0x1C the decoded tiles (0x400 bytes each), per frame */
} IpuPicture;

extern struct {
    IpuPicture *queue[4];    /* 0x0056CC80 */
    int current;             /* 0x0056CC90 -1: idle */
    int waiting;             /* 0x0056CC94 */
    int handler;             /* 0x0056CC98 */
    u32 command;             /* 0x0056CC9C bits kept for the next IPU command */
} g_0056CC80;

void func_00127670(int a, int b);                /* sceIpuSync */
void func_00127750(void);                        /* sceIpuInit */
int func_00131EA0(void);                         /* DI */
void func_00131EF0(void);                        /* EI */
void func_001289F8(int channel);                 /* EnableDmac */
void func_00128990(int channel);                 /* DisableDmac */
int AddDmacHandler(int channel, int (*handler)(int), int next);
int RemoveDmacHandler(int channel, int id);

void func_00143FF0(void);

/* 0x00143970, 0x6C bytes. Reads the IPU's next bits (its top byte); the next command starts
 * clean (8?). */
u32 func_00143970(void)
{
    u32 bits;

    REG_IPU_CMD = g_0056CC80.command | 0x40000000;
    func_00127670(0, 0);
    bits = REG_IPU_CMD;
    func_00127670(0, 0);
    g_0056CC80.command = 8;
    return bits >> 24;
}

/* 0x001439E0, 0x60 bytes. Starts receiving the decoded pixels at `to`. */
void func_001439E0(u32 to, u32 qwc)
{
    REG_DMAC_3_MADR = to;
    REG_DMAC_3_QWC = (qwc & 0x3FFFFF) << 6;
    func_00131EA0();
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER | 0x10000;
    REG_DMAC_3_CHCR = 0x100;
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER & ~0x10000;
    func_00131EF0();
}

/* 0x00143A40, 0x68 bytes, matching. Starts sending `size` bytes of coded data at `from`. */
void func_00143A40(u32 from, int size)
{
    REG_DMAC_4_MADR = from & 0xFFFFFFF;
    REG_DMAC_4_QWC = (u32)(size + 0xF) >> 4;
    func_00131EA0();
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER | 0x10000;
    REG_DMAC_4_CHCR = 0x101;
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER & ~0x10000;
    func_00131EF0();
}

/* 0x00143AB0, 0x94 bytes, matching. Decodes a picture: the data sent, the stream's settings read, the
 * decode command given, the pixels received into this frame's buffer. */
void func_00143AB0(IpuPicture *p)
{
    u32 bits;

    func_00143FF0();
    func_00143A40((u32)p->data, p->size);
    bits = func_00143970();
    REG_IPU_CTRL = (bits & ~4) << 16;
    REG_IPU_CMD = ((bits >> 2) & 1) << 24 | 0x10010000 | g_0056CC80.command;
    g_0056CC80.command = 0;
    func_001439E0((u32)p->pixels[g_70000150], p->tiles);
}

/* 0x00143B50, 0x90 bytes. The handler at the end of a decode: starts the next one, or marks the
 * IPU idle. */
int func_00143B50(int arg)
{
    if (g_0056CC80.waiting == 0) {
        g_0056CC80.current = -1;
    } else {
        g_0056CC80.waiting--;
        g_0056CC80.current++;
        func_00143AB0(g_0056CC80.queue[g_0056CC80.current]);
    }
    __asm__ volatile("sync.l");
    __asm__ volatile("ei");
    return arg;
}

/* 0x00143BE0, 0xA8 bytes. Decodes a picture now, or after the ones under way. */
void func_00143BE0(IpuPicture *p)
{
    int enabled = func_00131EA0();

    if (g_0056CC80.current == -1) {
        g_0056CC80.current = 0;
        func_00143AB0(p);
    } else {
        g_0056CC80.queue[g_0056CC80.current + g_0056CC80.waiting + 1] = p;
        g_0056CC80.waiting++;
    }
    if (enabled != 0)
        func_00131EF0();
}

/* 0x00143C90, 0x2C bytes, matching. Waits until the decodes are over. */
void func_00143C90(void)
{
    while (*(volatile int *)&g_0056CC80.current != -1)
        ;
}

/* 0x00143CC0, 0x98 bytes. Shows picture `index` of a pack: the last frame's tiles are uploaded,
 * then the picture is queued for decoding. */
void func_00143CC0(IpuPicture *p, int index)
{
    u32 *entry = (u32 *)(p->header + 0x10 + index * 8);
    u8 *packet;
    int i;

    p->data = p->header + entry[0];
    p->size = entry[1];
    packet = p->packets[g_70000150];
    for (i = 0; i < p->tiles; i++, packet += 0x90)
        func_00104860(packet);
    func_00143BE0(p);
}

/* 0x00143D60, 0x40 bytes, matching. Frees a picture's buffers. */
void func_00143D60(IpuPicture *p)
{
    func_00102EC0(p->pixels[0]);
    func_00102EC0(p->pixels[1]);
    func_00102EC0(p->packets[0]);
    func_00102EC0(p->packets[1]);
}

/* 0x00143DA0, 0x1A4 bytes. Sets a picture up for a pack's header: its buffers and, per frame,
 * one upload packet per tile to GS buffer `dbp`. */
void func_00143DA0(IpuPicture *p, u8 *header, int dbp)
{
    u32 w = *(u16 *)(header + 8) >> 4;
    u32 h = *(u16 *)(header + 0xA) >> 4;
    int f;

    p->header = header;
    p->tiles = w * h;
    for (f = 0; f < 2; f++) {
        u8 *packet, *pixels;
        int x, y;

        p->pixels[f] = func_00102DB0(0x40, p->tiles << 10);
        p->packets[f] = func_00102DB0(0x40, p->tiles * 0x90);
        p->dbp = dbp;
        packet = p->packets[f];
        pixels = p->pixels[f];
        for (y = 0; y < (int)h; y++) {
            for (x = 0; x < (int)w; x++) {
                func_00104520(packet);
                func_00104600(packet, pixels, 0x400, dbp, 0,
                              (*(u16 *)(p->header + 8) + 0x3F) / 64 * 64 / 64, x * 16, y * 16,
                              16, 16);
                packet += 0x90;
                pixels += 0x400;
            }
        }
    }
}

/* 0x00143F50, 0x5C bytes, matching. Starts the IPU and the end-of-decode handler. */
void func_00143F50(void)
{
    func_00127750();
    func_00143FF0();
    g_0056CC80.current = -1;
    g_0056CC80.waiting = 0;
    g_0056CC80.handler = AddDmacHandler(3, func_00143B50, 0);
    func_001289F8(3);
}

/* 0x00143FB0, 0x3C bytes, matching. Stops them, once the decodes are over. */
void func_00143FB0(void)
{
    func_00143C90();
    func_00143FF0();
    func_00128990(3);
    RemoveDmacHandler(3, g_0056CC80.handler);
}

/* 0x00143FF0, 0x84 bytes, matching. Stops both DMA channels and resets the IPU. */
void func_00143FF0(void)
{
    func_00131EA0();
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER | 0x10000;
    REG_DMAC_3_CHCR = 0;
    REG_DMAC_4_CHCR = 0;
    REG_DMAC_ENABLEW = REG_DMAC_ENABLER & ~0x10000;
    func_00131EF0();
    g_0056CC80.command = 0;
    REG_IPU_CTRL = 0x40000000;
    func_00127670(0, 0);
    REG_IPU_CMD = 0;
    func_00127670(0, 0);
}
