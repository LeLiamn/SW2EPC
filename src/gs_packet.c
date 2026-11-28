/*
 * gs_packet.c - building the frame's packets for the Graphics Synthesizer (original source file
 * unknown; it follows the controller code, 0x00104250-0x00106414).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Each frame has a scratch buffer of 0x30000 bytes (two at 0x00500810, picked by the frame index
 * at 0x70000150). Packets are taken from it (func_00104250: 16-aligned; when it is full the start
 * of the buffer is handed out again) and are sent in one of two ways:
 *
 * - queued: a 16-byte node (next, address, quadword count) is added to one of ten layers. The
 *   layers are one chain with a sentinel per layer (at the start of the buffer): a node is put
 *   just before the sentinel of its layer, so the chain runs through the layers in order. At the
 *   end of the frame func_00105F90 turns the chain into DMA "ref" tags after a header of GS
 *   settings, then starts the chain again.
 * - at once: the same tags are written straight into the DMA chain at 0x70000158, with a header
 *   and a tail.
 *
 * A DMA tag here is (0x30000000 | qwc, address) for "ref", followed by two VIF codes: FLUSHA
 * (0x13000000) or NOP, then DIRECT (0x51000000 | qwc), which hands the data to the GIF. An address
 * with its lowest bit set (texture data) gets a NOP instead of FLUSHA.
 *
 * The pictures are TIM2 pictures (header: +0x08 image size, +0x0C header size, +0x0E colours,
 * +0x13 image type: 4 = 4-bit, 5 = 8-bit, +0x14 width, +0x16 height); their upload is a GS
 * transfer (BITBLTBUF, TRXPOS, TRXREG, TRXDIR, then an IMAGE tag), followed by a TEXFLUSH.
 */

#define SW2E_FILE_GS_PACKET_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* The scratchpad words (constant addresses). */
#define g_70000150 (*(int *)0x70000150)          /* frame index: 0 or 1 */
#define g_70000154 (*(int *)0x70000154)          /* 1 or 2 (field mode?) */
#define g_70000158 (*(u32 **)0x70000158)         /* the DMA chain's write cursor */

/* A queued packet. */
typedef struct Node {
    struct Node *next;
    u32 addr;                /* bit 0 set: texture data */
    u32 qwc;                 /* quadwords */
    u32 pad;
} Node;

/* A layer's sentinel in the chain. */
typedef struct {
    Node *next;
    Node *before;            /* the node just before this sentinel */
} Layer;

/* A GIF tag. */
typedef struct {
    u64 nloop : 15;
    u64 eop : 1;
    u64 pad : 30;
    u64 pre : 1;
    u64 prim : 11;
    u64 flg : 2;
    u64 nreg : 4;
    u64 regs;
} GifTag;

extern u8 g_00500810[2][0x30000];        /* the frames' scratch buffers */
extern struct {
    u32 used;                /* 0x00560810 bytes taken from the frame's buffer */
    Layer *layers;           /* 0x00560814 the layers (at the start of the buffer) */
    u32 pad[2];
} g_00560810;

void func_00105230(u8 *packet, int layer);
void func_00105390(u8 *packet);

/* Takes `size` bytes from the frame's buffer (its start when it is full). */
static inline u8 *scratch_take(u32 size)
{
    u8 *p;
    u32 used = g_00560810.used;
    u32 end = used + ((size + 0xF) & ~0xF);

    if (end >= 0x30000) {
        p = g_00500810[g_70000150];
    } else {
        p = g_00500810[g_70000150];
        g_00560810.used = end;
        p += used;
    }
    return p;
}

/* Queues `qwc` quadwords at `addr` in layer `layer` (0-8; layer 9 is the last). */
static inline void queue(u32 addr, u32 qwc, int layer)
{
    Node *n = (Node *)scratch_take(0x10);
    Layer *l;

    n->next = 0;
    layer++;
    n->addr = addr;
    n->qwc = qwc;
    if (layer > 9)
        layer = 9;
    l = &g_00560810.layers[layer];
    n->next = (Node *)l;
    l->before->next = n;
    l->before = n;
}

/* Writes a "ref" DMA tag for `qwc` quadwords at `addr` into the chain. */
static inline void send(u32 addr, u32 qwc)
{
    u32 *d = g_70000158;

    d[0] = 0x30000000 | qwc;
    d[1] = addr;
    d[2] = 0x13000000;
    d[3] = 0x51000000 | qwc;
    g_70000158 = d + 4;
}

/* 0x00104250, 0x88 bytes. Takes `size` bytes (rounded up to 16) from the frame's buffer. */
u8 *func_00104250(int size)
{
    return scratch_take((size + 0xF) & ~0xF);
}

/* 0x001042E0, 0x5C bytes. The tail of a chain: a DMA "cnt" tag of 2 quadwords, then one GS
 * register write (TEXA = 0x80). The cursor after it. */
static u32 *func_001042E0(u32 *d)
{
    u64 *q;

    d[0] = 0x10000002;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x51000002;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008001;
    q[1] = 0xE;
    q[2] = 0x80;
    q[3] = 0x3B;
    return d + 0xC;
}

/* 0x00104340, 0xCC bytes. The frame chain's header: six GS register writes (TEXFLUSH, TEXA,
 * TEX1_2, CLAMP_2, ALPHA_2, TEST_2). */
static u32 *func_00104340(u32 *d)
{
    u64 *q;

    d[0] = 0x10000007;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x51000007;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008006;
    q[1] = 0xE;
    q[2] = 0;
    q[3] = 0x3F;
    q[4] = 0x8000008001;
    q[5] = 0x3B;
    q[6] = 0x60;
    q[7] = 0x15;
    q[8] = 0;
    q[9] = 9;
    q[10] = 0x8000000044;
    q[11] = 0x43;
    q[12] = 0x5000D;
    q[13] = 0x48;
    return d + 0x20;
}

/* 0x00104410, 0x5C bytes. The tail after a packet sent at once (the same as func_001042E0). */
static u32 *func_00104410(u32 *d)
{
    u64 *q;

    d[0] = 0x10000002;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x51000002;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008001;
    q[1] = 0xE;
    q[2] = 0x80;
    q[3] = 0x3B;
    return d + 0xC;
}

/* 0x00104470, 0xA4 bytes. The header before a packet sent at once: four of the frame header's
 * register writes. */
static u32 *func_00104470(u32 *d)
{
    u64 *q;

    d[0] = 0x10000005;
    d[1] = 0;
    d[2] = 0x13000000;
    d[3] = 0x51000005;
    q = (u64 *)(d + 4);
    q[0] = 0x1000000000008004;
    q[1] = 0xE;
    q[2] = 0;
    q[3] = 0x3F;
    q[4] = 0x8000008001;
    q[5] = 0x3B;
    q[6] = 0x60;
    q[7] = 0x15;
    q[8] = 0x8000000044;
    q[9] = 0x43;
    return d + 0x18;
}

void func_001050B0(u8 *packet);
void func_001050D0(u8 *packet);

/* 0x00104520, 0x3C bytes. Sets up an upload packet (0x90 bytes): transfer tag, then a
 * TEXFLUSH at +0x60. */
void func_00104520(u8 *packet)
{
    func_001050D0(packet);
    func_001050B0(packet + 0x60);
    ((u64 *)packet)[14] = 0;
    ((u64 *)packet)[15] = 0x3F;
}

/* 0x00104560, 0x94 bytes. A new upload packet. */
u8 *func_00104560(void)
{
    u8 *p = scratch_take(0x90);

    func_00104520(p);
    return p;
}

/* 0x00104600, 0xE0 bytes. Fills an upload packet: `size` bytes at `data` to the GS buffer
 * `dbp` (format `psm`, width `dbw`) at (`x`, `y`), `w` x `h` pixels. The data's address and
 * quadword count are kept at +0x80 / +0x84. */
void func_00104600(u8 *packet, u8 *data, u32 size, int dbp, int psm, int dbw, int x, int y,
                   int w, int h)
{
    u64 *q = (u64 *)packet;

    q[0] = 0x1000000000000004;
    q[2] = (u64)psm << 56 | (u64)dbp << 32 | (u64)dbw << 48;        /* BITBLTBUF */
    q[3] = 0x50;
    q[4] = (u64)x << 32 | (u64)y << 48;                             /* TRXPOS */
    q[5] = 0x51;
    q[6] = (u64)w | (u64)h << 32;                                   /* TRXREG */
    q[7] = 0x52;
    q[8] = 0;                                                       /* TRXDIR: host to local */
    q[9] = 0x53;
    q[10] = (u64)(int)(size >> 4) | 0x0800000000008000;             /* IMAGE tag */
    q[11] = 0;
    *(u32 *)(packet + 0x80) = (u32)data;
    *(u32 *)(packet + 0x84) = (size + 0xF) >> 4;
}

/* 0x001046E0, 0x17C bytes. Queues an upload packet in layer `layer`: its tags, its data, its
 * TEXFLUSH. */
void func_001046E0(u8 *packet, int layer)
{
    u32 addr, qwc;

    queue((u32)packet, 6, layer);
    addr = *(u32 *)(packet + 0x80);
    qwc = *(u32 *)(packet + 0x84);
    queue(addr | 1, qwc, layer);
    func_00105230(packet + 0x60, layer);
}

/* 0x00104860, 0xA8 bytes. Sends an upload packet at once. */
void func_00104860(u8 *packet)
{
    u32 *d;
    u32 addr;

    send((u32)packet, 6);
    d = g_70000158;
    addr = *(u32 *)(packet + 0x80);
    d[0] = *(u32 *)(packet + 0x84) | 0x30000000;
    d[1] = addr;
    d[2] = 0;
    d[3] = *(u32 *)(packet + 0x84) | 0x51000000;
    g_70000158 = d + 4;
    func_00105390(packet + 0x60);
}

/* 0x00104910, 0x148 bytes. Fills an upload packet with a TIM2 picture's pixels, to buffer
 * `dbp` of width `width` at (`x`, `y`). Its TEX0 value. */
u64 func_00104910(u8 *packet, u8 *picture, int dbp, int width, int x, int y)
{
    u8 *h = func_00106F10(picture);
    u16 w = *(u16 *)(h + 0x14);
    u16 ht = *(u16 *)(h + 0x16);
    int psm = func_00106E90(h);
    int dbw = func_001069C0(psm, width);
    u8 *data = h + *(u16 *)(h + 0xC);
    int size;

    if (h[0x13] == 5)
        size = w * ht;
    else if (h[0x13] == 4)
        size = (int)(w * ht) / 2;
    else
        size = -(w * ht) * 4;   /* (sic) other formats are not used */
    func_00104520(packet);
    func_00104600(packet, data, size, dbp, psm, dbw, x, y, w, ht);
    return func_00106CD0(dbp, psm, -1, -1, w, ht);
}

/* 0x00104A60, 0x5C bytes, matching. The same at (0, 0), with the picture's own width. */
u64 func_00104A60(u8 *packet, u8 *picture, int dbp)
{
    u8 *h = func_00106F10(picture);

    return func_00104910(packet, picture, dbp, *(u16 *)(h + 0x14), 0, 0);
}

/* 0x00104AC0, 0x64 bytes. Queues a TIM2 picture's upload in layer `layer`. */
u64 func_00104AC0(u8 *picture, int dbp, int layer)
{
    u8 *p = func_00104560();
    u64 tex0 = func_00104A60(p, picture, dbp);

    func_001046E0(p, layer);
    return tex0;
}

/* 0x00104B30, 0x54 bytes. Sends a TIM2 picture's upload at once. */
u64 func_00104B30(u8 *picture, int dbp)
{
    u8 *p = func_00104560();
    u64 tex0 = func_00104A60(p, picture, dbp);

    func_00104860(p);
    return tex0;
}

/* 0x00104B90, 0x108 bytes. Fills an upload packet with CLUT `index` of a TIM2 picture
 * (16 x 16 colours for 8-bit pictures, 8 x 2 for 4-bit), to buffer `cbp`. The CLUT part of TEX0
 * (CBP, CLD = 1). */
u64 func_00104B90(u8 *packet, u8 *picture, int index, int cbp)
{
    u8 *h = func_00106F10(picture);
    u8 *cluts = h + *(u16 *)(h + 0xC) + *(u32 *)(h + 8);
    int w, ht, size;

    if (h[0x13] == 5) {
        w = 16;
        ht = 16;
    } else if (h[0x13] == 4) {
        w = 8;
        ht = 2;
    }
    /* other formats: w and ht are not set (as in the original) */
    size = w * ht * 4;
    func_00104520(packet);
    func_00104600(packet, cluts + index * size, size, cbp, 0, size / 64, 0, 0, w, ht);
    return (u64)(long long)cbp << 37 | 0x2000000000000000;
}

/* 0x00104CA0, 0x58 bytes. Sends CLUT 0 of a TIM2 picture at once. */
u64 func_00104CA0(u8 *picture, int cbp)
{
    u8 *p = func_00104560();
    u64 clut = func_00104B90(p, picture, 0, cbp);

    func_00104860(p);
    return clut;
}

/* 0x00104D00, 0x168 bytes. Queues all the CLUTs of a TIM2 picture, from buffer `cbp` on
 * (4 buffers apart for 8-bit pictures, 1 for 4-bit), in layer `layer`. The CLUT part of TEX0
 * for the first. */
u64 func_00104D00(u8 *picture, int cbp, int layer)
{
    u8 *h = func_00106F10(picture);
    u8 *data = h + *(u16 *)(h + 0xC) + *(u32 *)(h + 8);
    int w, ht, step, count, size, i, at;

    if (h[0x13] == 5) {
        w = 16;
        step = 4;
        ht = 16;
    } else if (h[0x13] == 4) {
        step = 1;
        w = 8;
        ht = 2;
    }
    /* other formats: not set (as in the original) */
    count = *(u16 *)(h + 0xE) / (w * ht);
    size = w * ht * 4;
    at = cbp;
    for (i = 0; i < count; i++) {
        u8 *p = func_00104560();

        func_00104600(p, data, size, at, 0, size / 64, 0, 0, w, ht);
        func_001046E0(p, layer);
        at += step;
        data += size;
    }
    return (u64)(long long)cbp << 37 | 0x2000000000000000;
}

/* 0x00104E70, 0x60 bytes, matching. Queues a TIM2 picture and its CLUTs; the full TEX0 value. */
u64 func_00104E70(u8 *picture, int dbp, int cbp, int layer)
{
    u64 tex0 = func_00104AC0(picture, dbp, layer);

    return func_00106C50(tex0, func_00104D00(picture, cbp, layer));
}

/* 0x00104ED0, 0x4C bytes, matching. Sends a TIM2 picture and its first CLUT at once; the TEX0 value. */
u64 func_00104ED0(u8 *picture, int dbp, int cbp)
{
    u64 tex0 = func_00104B30(picture, dbp);

    return func_00106C50(tex0, func_00104CA0(picture, cbp));
}

/* 0x00104F20, 0x3C bytes. The same as func_00104E70 for picture `index` of a pack (base + unit
 * size at +8 times the entry's offset at +0x10 + index * 8). */
u64 func_00104F20(u8 *pack, int index, int dbp, int cbp, int layer)
{
    return func_00104E70(pack + *(int *)(pack + 8) * *(int *)(pack + index * 8 + 0x10), dbp, cbp,
                         layer);
}

/* 0x00104F60, 0xB4 bytes. Queues `size` bytes at `data` in layer `layer`. */
void func_00104F60(u8 *data, int size, int layer)
{
    queue((u32)data, (size + 0xF) >> 4, layer);
}

/* 0x00105020, 0x88 bytes. Sends `size` bytes at `data` at once, with the header and tail. */
void func_00105020(u8 *data, u32 size)
{
    g_70000158 = func_00104470(g_70000158);
    send((u32)data, (size + 0xF) >> 4);
    g_70000158 = func_00104410(g_70000158);
}

/* 0x001050B0, 0x20 bytes, matching. A GIF tag for one A+D register write. */
void func_001050B0(u8 *packet)
{
    ((u64 *)packet)[0] = 0x1000000000008001;
    ((u64 *)packet)[1] = 0xE;
}

/* 0x001050D0, 0x20 bytes, matching. A GIF tag for four A+D register writes. */
void func_001050D0(u8 *packet)
{
    ((u64 *)packet)[0] = 0x1000000000008004;
    ((u64 *)packet)[1] = 0xE;
}

/* 0x001050F0, 0x94 bytes. A new packet of one register write (0x20 bytes). */
u8 *func_001050F0(void)
{
    u8 *p = scratch_take(0x20);

    func_001050B0(p);
    return p;
}

/* 0x00105190, 0x94 bytes. A new packet of four register writes (0x50 bytes). */
u8 *func_00105190(void)
{
    u8 *p = scratch_take(0x50);

    func_001050D0(p);
    return p;
}

/* 0x00105230, 0xB0 bytes. Queues a packet of one register write. */
void func_00105230(u8 *packet, int layer)
{
    queue((u32)packet, 2, layer);
}

/* 0x001052E0, 0xB0 bytes. Queues a packet of four register writes. */
void func_001052E0(u8 *packet, int layer)
{
    queue((u32)packet, 5, layer);
}

/* 0x00105390, 0x4C bytes. Sends a packet of one register write at once (no header). */
void func_00105390(u8 *packet)
{
    send((u32)packet, 2);
}

/* 0x001053E0, 0x28 bytes, matching. A flat sprite (0x30 bytes): a GIF tag in register-list mode, then
 * four 64-bit values (PRIM, RGBAQ, two corners). */
void func_001053E0(u8 *packet)
{
    ((u64 *)packet)[0] = 0x4400000000008001;
    ((u64 *)packet)[1] = 0x5D10;
    ((u64 *)packet)[2] = 0x246;
}

/* 0x00105410, 0x94 bytes. A new flat sprite. */
u8 *func_00105410(void)
{
    u8 *p = scratch_take(0x30);

    func_001053E0(p);
    return p;
}

/* 0x001054B0, 0xB0 bytes. Queues a flat sprite. */
void func_001054B0(u8 *packet, int layer)
{
    queue((u32)packet, 3, layer);
}

/* 0x00105560, 0x7C bytes. Sends a flat sprite at once. */
void func_00105560(u8 *packet)
{
    g_70000158 = func_00104470(g_70000158);
    send((u32)packet, 3);
    g_70000158 = func_00104410(g_70000158);
}

/* 0x001055E0, 0x3C bytes, matching. A sprite with a colour per corner (0x60 bytes, ten values). */
void func_001055E0(u8 *packet)
{
    ((u64 *)packet)[0] = 0xA400000000008001;
    ((u64 *)packet)[1] = 0xF5151D1D10;
    ((u64 *)packet)[2] = 0x24C;
}

/* 0x00105620, 0x94 bytes. A new one. */
u8 *func_00105620(void)
{
    u8 *p = scratch_take(0x60);

    func_001055E0(p);
    return p;
}

/* 0x001056C0, 0xB0 bytes. Queues it. */
void func_001056C0(u8 *packet, int layer)
{
    queue((u32)packet, 6, layer);
}

/* 0x00105770, 0x7C bytes. Sends it at once. */
void func_00105770(u8 *packet)
{
    g_70000158 = func_00104470(g_70000158);
    send((u32)packet, 6);
    g_70000158 = func_00104410(g_70000158);
}

/* 0x001057F0, 0x68 bytes. A textured sprite (0x50 bytes, eight values) with texture `tex0`:
 * `mode` 1 with ST coordinates, 0 with UV ones; other modes leave the registers unset. */
void func_001057F0(u8 *packet, u64 tex0, int mode)
{
    u64 regs, prim;

    if (mode == 1) {
        prim = 0x256;
        regs = 0xF52D2170;
    } else if (mode == 0) {
        prim = 0x356;
        regs = 0xF53D3170;
    }
    ((u64 *)packet)[0] = 0x8400000000008001;
    ((u64 *)packet)[1] = regs;
    ((u64 *)packet)[2] = prim;
    ((u64 *)packet)[3] = tex0;
}

/* 0x00105860, 0x98 bytes. A new textured sprite. */
u8 *func_00105860(u64 tex0, int mode)
{
    u8 *p = scratch_take(0x50);

    func_001057F0(p, tex0, mode);
    return p;
}

/* 0x00105900, 0xB0 bytes. Queues it. */
void func_00105900(u8 *packet, int layer)
{
    queue((u32)packet, 5, layer);
}

/* 0x001059B0, 0x7C bytes. Sends it at once. */
void func_001059B0(u8 *packet)
{
    g_70000158 = func_00104470(g_70000158);
    send((u32)packet, 5);
    g_70000158 = func_00104410(g_70000158);
}

/* 0x00105A30, 0x78 bytes. A textured sprite with a colour per corner (0x70 bytes, twelve values). */
void func_00105A30(u8 *packet, u64 tex0, int mode)
{
    u64 regs, prim;

    if (mode == 1) {
        regs = 0xF5252D2D2170;
        prim = 0x254;
    } else if (mode == 0) {
        regs = 0xF5353D3D3170;
        prim = 0x354;
    }
    ((u64 *)packet)[0] = 0xC400000000008001;
    ((u64 *)packet)[1] = regs;
    ((u64 *)packet)[2] = prim;
    ((u64 *)packet)[3] = tex0;
}

/* 0x00105AB0, 0x88 bytes. A textured quad (0x80 bytes, fourteen values). */
void func_00105AB0(u8 *packet, u64 tex0, int mode)
{
    u64 regs, prim;

    if (mode == 1) {
        regs = 0x521521D21D2170;
        prim = 0x25C;
    } else if (mode == 0) {
        regs = 0x531531D31D3170;
        prim = 0x35C;
    }
    ((u64 *)packet)[0] = 0xE400000000008001;
    ((u64 *)packet)[1] = regs;
    ((u64 *)packet)[2] = prim;
    ((u64 *)packet)[3] = tex0;
}

/* 0x00105B40, 0x98 bytes. A new textured quad. */
u8 *func_00105B40(u64 tex0, int mode)
{
    u8 *p = scratch_take(0x80);

    func_00105AB0(p, tex0, mode);
    return p;
}

/* 0x00105BE0, 0xB0 bytes. Queues it. */
void func_00105BE0(u8 *packet, int layer)
{
    queue((u32)packet, 8, layer);
}

/* 0x00105C90, 0x7C bytes. Sends it at once. */
void func_00105C90(u8 *packet)
{
    g_70000158 = func_00104470(g_70000158);
    send((u32)packet, 8);
    g_70000158 = func_00104410(g_70000158);
}

/* 0x00105D10, 0x40 bytes, matching. A quad with a colour per corner (0x80 bytes, fourteen values). */
void func_00105D10(u8 *packet)
{
    ((u64 *)packet)[0] = 0xE400000000008001;
    ((u64 *)packet)[1] = 0xF5555555551510;
    ((u64 *)packet)[2] = 0x24D;
}

/* 0x00105D50, 0x44 bytes, matching. A textured quad with a colour per corner (0x90 bytes, sixteen values). */
void func_00105D50(u8 *packet, u64 tex0)
{
    ((u64 *)packet)[0] = 0x0400000000008001;
    ((u64 *)packet)[1] = 0xF52525252D2D2170;
    ((u64 *)packet)[2] = 0x255;
    ((u64 *)packet)[3] = tex0;
}

/* 0x00105DA0, 0x6C bytes, matching. Sets up a screen clear (0x70 bytes): a TEST_2 write, a flat sprite
 * over the screen, a TEST_2 write back (the first two without EOP). */
void func_00105DA0(u8 *packet)
{
    func_001050B0(packet);
    ((GifTag *)packet)->eop = 0;
    func_001053E0(packet + 0x20);
    ((GifTag *)(packet + 0x20))->eop = 0;
    func_001050B0(packet + 0x50);
}

/* 0x00105E10, 0x94 bytes. A new screen clear. */
u8 *func_00105E10(void)
{
    u8 *p = scratch_take(0x70);

    func_00105DA0(p);
    return p;
}

/* 0x00105EB0, 0xB4 bytes, matching. Fills a screen clear: test always passing with Z written, the
 * sprite from (0x7000, 0x8000 - 0xE00 / g_70000154) to (0x9000, 0x8000 + 0xE00 / g_70000154),
 * depth `z`, then the usual test. */
void func_00105EB0(u8 *packet, int z)
{
    u64 *q = (u64 *)packet;

    q[2] = 0x32001;
    q[3] = 0x48;
    q[8] = (u64)(long long)(-0xE00 / g_70000154 + 0x8000) << 16 | 0x7000 | (u64)(long long)z << 32;
    q[9] = (u64)(long long)(0xE00 / g_70000154 + 0x8000) << 16 | 0x9000 | (u64)(long long)z << 32;
    q[7] = 0x3F80000080808080;          /* RGBAQ: grey, Q = 1.0 */
    q[12] = 0x5000D;
    q[13] = 0x48;
}

/* 0x00105F70, 0x1C bytes, matching. Sends a screen clear at once. */
void func_00105F70(u8 *packet)
{
    func_00105020(packet, 0x70);
}

/* Starts the chain again: one sentinel per layer, each layer empty. */
static inline void layers_reset(void)
{
    int i;

    g_00560810.used = 0x50;
    g_00560810.layers = (Layer *)g_00500810[g_70000150];
    g_00560810.layers[0].before = 0;
    for (i = 0; i < 9; i++) {
        g_00560810.layers[i].next = (Node *)&g_00560810.layers[i + 1];
        g_00560810.layers[i + 1].before = (Node *)&g_00560810.layers[i];
    }
    g_00560810.layers[i].next = 0;
}

/* 0x00105F90, 0x224 bytes. The end of the frame: the header, then a DMA tag per queued node
 * (sentinels skipped), the tail, and the chain started again. */
void func_00105F90(void)
{
    u32 *d = func_00104340(g_70000158);
    Node *n = g_00560810.layers[0].next;

    while (n != 0) {
        int sentinel = 0;

        if ((Node *)g_00560810.layers <= n && n <= (Node *)&g_00560810.layers[9])
            sentinel = 1;
        if (sentinel) {
            n = n->next;
        } else {
            u32 addr = n->addr;

            if ((addr & 0xF) == 0) {
                d[0] = n->qwc | 0x30000000;
                d[1] = addr;
                d[2] = 0x13000000;
            } else {
                d[0] = n->qwc | 0x30000000;
                d[1] = addr & ~0xF;
                d[2] = 0;
            }
            d[3] = n->qwc | 0x51000000;
            n = n->next;
            d += 4;
        }
    }
    g_70000158 = func_001042E0(d);
    layers_reset();
}

/* 0x001061C0, 0x130 bytes. Starts the chain (at start-up). */
void func_001061C0(void)
{
    layers_reset();
}

/* 0x001062F0, 0x130 bytes. The same (another caller). */
void func_001062F0(void)
{
    layers_reset();
}
