/*
 * system.c - the system layer that main.c's loop runs on: shutdown, a queue of requests sent
 * to the IOP (func_00115A50...), the display (GS double buffer at 0x00500130, NTSC / PAL-style
 * full or half height, screen offset), the frame flip at vertical blank, timers, the frame
 * semaphore and the interrupt handlers. Original source file unknown (the code area of main.c,
 * 0x00100410-0x00102410; the start-up code at 0x00100008 is assembly: it sets gp and the stack
 * and calls main).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. For the PC port this whole file is to be replaced by the
 * platform layer; it is kept to document what the game expects.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* PS2 hardware registers. */
#define REG_RCNT0_COUNT     (*(volatile u32 *)0x10000000)
#define REG_RCNT0_MODE      (*(volatile u32 *)0x10000010)
#define REG_RCNT1_COUNT     (*(volatile u32 *)0x10000800)
#define REG_RCNT1_MODE      (*(volatile u32 *)0x10000810)
#define REG_VIF1_FBRST      (*(volatile u32 *)0x10003C10)
#define REG_DMAC_2_GIF_CHCR (*(volatile u32 *)0x1000A000)
#define REG_DMAC_2_GIF_MADR (*(volatile u32 *)0x1000A010)
#define REG_DMAC_2_GIF_QWC  (*(volatile u32 *)0x1000A020)
#define REG_GS_PMODE        (*(volatile u64 *)0x12000000)
#define REG_GS_CSR          (*(volatile u64 *)0x12001000)

/* Scratchpad words. */
#define g_70000150 (*(u32 *)0x70000150)    /* the packet buffer in use (0 / 1) */
#define g_70000154 (*(int *)0x70000154)    /* the vertical scale (1 full height, 2 half) */
#define g_70000158 (*(u32 **)0x70000158)   /* the packet's write pointer */

/* Kernel calls. */
void FlushCache(int a);
void iFlushCache(int a);
int CreateSema(void *params);
int WaitSema(int sema);
int iSignalSema(int sema);
int iReferSemaStatus(int sema, void *status);
int AddDmacHandler(int channel, int (*handler)(int), int next);
void EI(void);

/* The scene manager (see main.c), the word passed to the frame functions. */
extern struct {
    float update_arg;
} g_0045D880;

/* Requests to the IOP: one sent at once (0x0045D8D0) and a queue (0x0045D8F0), sorted by the
 * sum of their first two words before being sent. */
typedef struct {
    u32 a, b, c, d;          /* `a` bit 31: the second kind */
} Request;

extern Request g_0045D8D0;
extern Request g_0045D8E0;
extern Request g_0045D8F0[];
extern int g_0045D180;                    /* (small data) the queue's length */

/* (small data) the display and frame state. */
extern u32 g_0045D184;                    /* the line counter at the last handler */
extern int g_0045D188;                    /* the last vblank flipped */
extern int g_0045D18C;                    /* the vblank handler's id */
extern u32 g_0045D190;                    /* a line count before the first callback */
extern u32 g_0045D194;                    /* ... before the second */
extern void (*g_0045D198)(int line);      /* called by the DMA handler */
extern void (*g_0045D19C)(void);          /* called before waiting for the frame */
extern void (*g_0045D1A0)(void);          /* called by func_00102380 */
extern int g_0045D1A4;                    /* frames */
extern int g_0045D1A8;                    /* 1: waiting for the frame */
extern int g_0045D1AC;                    /* 1: flip at vblank */
extern int g_0045D1B0;                    /* the frame semaphore */
extern float g_0045D1B4, g_0045D1B8, g_0045D1BC, g_0045D1C0;
extern int g_0045D1C4;                    /* draw (see main.c) */
extern int g_0045D1C8;                    /* the display mode (0 full height, 1 half) */
extern int g_0045D1CC;                    /* the display's y origin */
extern float g_0045D1D0;
extern int g_0045D1D4;                    /* the height (448 / 224) */
extern float g_0045D1D8;
extern int g_0045D1DC;                    /* the width (512) */
extern int g_0045D1E0;                    /* the GIF DMA channel */
extern u8 *g_0045D1E4;                    /* the VIF1 DMA channel's control */
extern int g_0045D1E8;                    /* the screen offset (y, -24..24) */
extern int g_0045D1EC;                    /* the screen offset (x, -24..24) */
extern u32 g_0045D1F0;                    /* the field (GS_CSR bit 13) */
extern int g_0045D1F4;                    /* the packet buffers' size */
extern u32 *g_0045D1F8[2];                /* the two packet buffers */
extern int g_0045CC00;                    /* the DMA handler's id (-1 = none) */

/* The display environments (0x00500130, two of 0x28 bytes) and the draw environments. */
extern u8 g_00500130[];
extern u8 g_0045E900[2][0x990];           /* two prepared packets: full-height clears */
extern u8 g_0045FC20[];                   /* the half-height one */
extern u8 g_00400B80[];                   /* an initial GS packet (10 quadwords) */

void func_001037F0(int value);
void func_003B3940(void);
void func_001781C0(void);
void func_001F1E90(void);
void func_002E6260(void);
void func_0020E520(void);
void func_001C7730(void);
void func_00185D70(void);
void func_00194100(void);
void func_0019F400(void);
void func_002D8030(void);
void func_001B9230(void);
void func_00147770(void);
void func_001AC4C0(void);
void func_0023C150(void);
void func_00103F30(void);
void func_001B9260(void);
void func_00106840(float dt);
void func_0023C100(void);
void func_00106880(void);
void func_001068B0(float dt);
void func_0019EFD0(void);
int func_00115A50(u32 a, u32 b, int c);
int func_00115C80(int a);
void func_00115BC0(Request *requests);
void func_00115D40(void);
void func_00127000(u8 *env, int x, int w, u16 h, int a, int b, int c);
void func_00125988(u8 *env, int a, int w, int h, int b, int c);
int func_001265F0(int a, int b);
void func_0011B3E8(int channel, void *data, u32 qwc);
void func_001256D0(int a, int b, int c, int d);
u8 *func_00125860(void);
void func_00118850(void *to, int size);
int func_00106980(int size);
int func_001069C0(int a, int w);
void func_00125E88(void *env, int a, u16 w, u16 h, int b, int c);
void func_00126558(int a);
int func_00131EA0(void);
void func_00131EF0(void);
void func_0011B690(u8 *channel);
void func_00125870(void);
void func_00126D10(u8 *env, int a, int b, u16 field);
void func_00126F78(u8 *env, int a, int b, u16 field);
void func_001272E8(u8 *env, u32 field);
void func_0011B380(u8 *channel, u32 *chain);
void func_0023A860(void);
int func_0010B198(int (*handler)(int), int a);
void func_00128928(int a);
void func_001289F8(int a);
void func_0010B158(void);
void func_00133D50(void);
void func_00133B30(void);

void func_00101470(int mode);
void func_00101C90(int flip, int in_interrupt);
void func_001014D0(int value);
void func_001020E0(void);

/* 0x00100410, 0x94 bytes, matching. Shuts the game's systems down (the end of func_001005A0). */
void func_00100410(void)
{
    func_001037F0(0);
    func_003B3940();
    func_001781C0();
    func_001F1E90();
    func_002E6260();
    func_0020E520();
    func_001C7730();
    func_00185D70();
    func_00194100();
    func_0019F400();
    func_002D8030();
    func_001B9230();
    func_00147770();
    func_001AC4C0();
    func_0023C150();
    func_00103F30();
}

/* 0x001004B0, 0x4C bytes. The work after each frame's draw. */
void func_001004B0(void)
{
    func_001B9260();
    func_00106840(g_0045D880.update_arg);
    func_0023C100();
    func_00106880();
    func_001068B0(g_0045D880.update_arg);
    func_0019EFD0();
}

/* 0x00100870, 0x4C bytes. Sends until accepted. */
void func_00100870(u32 a, u32 b)
{
    while (func_00115A50(a, b, 0) == 0)
        ;
}

/* 0x001008C0, 0xB8 bytes. Sorts the queue by the sum of the first two words. */
void func_001008C0(void)
{
    Request *p = g_0045D8F0;
    int i, j;

    for (i = 0; i < g_0045D180 - 1; i++, p++) {
        Request *q = p;

        for (j = i + 1; j < g_0045D180; j++) {
            q++;
            if (q->a + q->b < p->a + p->b) {
                Request t = *p;

                *p = *q;
                *q = t;
            }
        }
    }
}

/* 0x00100980, 0xA8 bytes. Sends the queue (sorted, ended by -1) when the IOP is free. */
void func_00100980(void)
{
    if (func_00115C80(1) != 1 && g_0045D180 != 0) {
        func_001008C0();
        g_0045D8F0[g_0045D180].d = 0xFFFFFFFF;
        g_0045D8F0[g_0045D180].c = 0xFFFFFFFF;
        g_0045D8F0[g_0045D180].b = 0xFFFFFFFF;
        g_0045D8F0[g_0045D180].a = 0xFFFFFFFF;
        func_00115C80(0);
        func_00115BC0(g_0045D8F0);
        g_0045D180 = 0;
    }
}

/* 0x00100A30, 0x70 bytes. Sends the queue, then whether the IOP is free (`wait` 0: blocking). */
int func_00100A30(int wait)
{
    if (g_0045D180 != 0)
        func_00100980();
    return func_00115C80(wait == 0) != 1;
}

/* 0x00100AA0, 0x1C bytes, matching. */
void func_00100AA0(void)
{
    func_00115D40();
}

/* 0x00100AC0, 0xC4 bytes, matching. Queues a request (none when `d` is 0 or the IOP is busy). */
u32 func_00100AC0(u32 a, u32 b, u32 c, u32 d)
{
    if (func_00115C80(1) == 1)
        return 0;
    if (d == 0)
        return 0;
    g_0045D8F0[g_0045D180].a = a;
    g_0045D8F0[g_0045D180].b = b;
    g_0045D8F0[g_0045D180].c = c;
    g_0045D8F0[g_0045D180].d = d;
    g_0045D180++;
    return d;
}

/* 0x00100B90, 0xCC bytes, matching. The same, second kind. */
u32 func_00100B90(u32 a, u32 b, u32 c, u32 d)
{
    if (func_00115C80(1) == 1)
        return 0;
    if (d == 0)
        return 0;
    g_0045D8F0[g_0045D180].a = a | 0x80000000;
    g_0045D8F0[g_0045D180].b = b;
    g_0045D8F0[g_0045D180].c = c;
    g_0045D8F0[g_0045D180].d = d;
    g_0045D180++;
    return d;
}

/* 0x00100C60, 0x94 bytes. Sends one request at once (waiting for the IOP). */
u32 func_00100C60(u32 a, u32 b, u32 c, u32 d)
{
    func_00115C80(0);
    if (d == 0)
        return 0;
    g_0045D8D0.d = d;
    g_0045D8D0.a = a;
    g_0045D8D0.b = b;
    g_0045D8D0.c = c;
    func_00115BC0(&g_0045D8D0);
    func_00115C80(0);
    return d;
}

/* 0x00100D00, 0x9C bytes. The same, second kind. */
u32 func_00100D00(u32 a, u32 b, u32 c, u32 d)
{
    func_00115C80(0);
    if (d == 0)
        return 0;
    g_0045D8D0.a = a | 0x80000000;
    g_0045D8D0.d = d;
    g_0045D8D0.b = b;
    g_0045D8D0.c = c;
    func_00115BC0(&g_0045D8D0);
    func_00115C80(0);
    return d;
}

/* 0x00100DA0, 0x6C bytes, matching. Empties the requests. */
void func_00100DA0(void)
{
    g_0045D8F0[0].d = 0xFFFFFFFF;
    g_0045D180 = 0;
    g_0045D8F0[0].c = 0xFFFFFFFF;
    g_0045D8F0[0].b = 0xFFFFFFFF;
    g_0045D8F0[0].a = 0xFFFFFFFF;
    g_0045D8E0.d = 0xFFFFFFFF;
    g_0045D8E0.c = 0xFFFFFFFF;
    g_0045D8E0.b = 0xFFFFFFFF;
    g_0045D8E0.a = 0xFFFFFFFF;
    g_0045D8D0.d = 0xFFFFFFFF;
    g_0045D8D0.c = 0xFFFFFFFF;
    g_0045D8D0.b = 0xFFFFFFFF;
    g_0045D8D0.a = 0xFFFFFFFF;
}

/* 0x00100E10, 0xB8 bytes. Applies the screen offset to both display environments (DISPLAY
 * register: x in bits 0-11, y in bits 12-22). */
void func_00100E10(u8 *env)
{
    u16 x = (u16)(g_0045D1EC * 0xA00 / 0x200 + 0x290) & 0xFFF;
    u32 y = ((u32)(g_0045D1E8 / 2 * 2 + 0x48) & 0x7FF) << 12;

    *(u16 *)(env + 0x18) = (*(u16 *)(env + 0x18) & 0xF000) | x;
    *(u32 *)(env + 0x18) = (*(u32 *)(env + 0x18) & 0xFF800FFF) | y;
    *(u16 *)(env + 0x40) = (*(u16 *)(env + 0x40) & 0xF000) | x;
    *(u32 *)(env + 0x40) = (*(u32 *)(env + 0x40) & 0xFF800FFF) | y;
    FlushCache(0);
}

/* 0x00100ED0, 0xC0 bytes. Sets the screen offset (each kept within -24..24). */
void func_00100ED0(int *x, int *y)
{
    int v = *x;

    if ((v < 0x19 ? v : 0x18) < -0x17)
        *x = -0x18;
    else
        *x = v > 0x18 ? 0x18 : v;
    v = *y;
    if ((v < 0x19 ? v : 0x18) < -0x17)
        *y = -0x18;
    else
        *y = v > 0x18 ? 0x18 : v;
    g_0045D1EC = *x;
    g_0045D1E8 = *y;
    func_00100E10(g_00500130);
}

/* 0x00100F90, 0x14 bytes, matching. */
void func_00100F90(int *x, int *y)
{
    *x = g_0045D1EC;
    *y = g_0045D1E8;
}

int func_00100FB0(void) { return g_0045D1DC; }     /* 0x00100FB0, 0x8 bytes, matching. the width */
int func_00100FC0(void) { return g_0045D1D4; }     /* 0x00100FC0, 0x8 bytes, matching. the height */
float func_00100FD0(void) { return g_0045D1D0; }   /* 0x00100FD0, 0x8 bytes, matching. */
int func_00100FE0(void) { return g_0045D1CC; }     /* 0x00100FE0, 0x8 bytes, matching. the y origin */

/* 0x00100FF0, 0x40C bytes. Sets the display up: mode 0 full height (448 lines, scale 1), else
 * half height (224, scale 2); both environments, the offset, then the frame's GS registers
 * (SCISSOR 0x40 / 0x41 over the screen). */
void func_00100FF0(int mode)
{
    u64 packet[8];
    u16 field;

    g_0045D1C8 = mode;
    if (mode == 0) {
        g_0045D1D4 = 0x1C0;
        g_0045D1D0 = 448.0f;
        g_0045D1CC = 0xB0;
        g_70000154 = 1;
    } else {
        g_0045D1D4 = 0xE0;
        g_0045D1D0 = 224.0f;
        g_0045D1CC = 0x78;
        g_70000154 = 2;
    }
    g_0045D1DC = 0x200;
    g_0045D1D8 = 512.0f;
    func_00127000(g_00500130, 0, 0x200, (u16)g_0045D1D4, 2, 0x3A, 1);
    *(u64 *)(g_00500130 + 0x180) = 0x3F80000080000000ULL;
    *(u64 *)(g_00500130 + 0x2F0) = 0x3F80000080000000ULL;
    func_00125988(g_00500130, 0, 0x200, 0x100, 0, 0);
    func_00125988(g_00500130 + 0x28, 0, 0x200, 0x100, 0, 0);
    *(u16 *)(g_00500130 + 0x38) &= 0xFE00;
    *(u16 *)(g_00500130 + 0x10) &= 0xFE00;
    *(u16 *)(g_00500130 + 0x1D0) = (*(u16 *)(g_00500130 + 0x1D0) & 0xFE00) | 0x40;
    *(u16 *)(g_00500130 + 0x60) = (*(u16 *)(g_00500130 + 0x60) & 0xFE00) | 0x40;
    *(u16 *)(g_00500130 + 0x250) = (*(u16 *)(g_00500130 + 0x250) & 0xFE00) | 0x40;
    *(u16 *)(g_00500130 + 0xE0) = (*(u16 *)(g_00500130 + 0xE0) & 0xFE00) | 0x40;
    field = (u16)g_0045D1CC & 0x1FF;
    *(u16 *)(g_00500130 + 0x1E0) = (*(u16 *)(g_00500130 + 0x1E0) & 0xFE00) | field;
    *(u16 *)(g_00500130 + 0x70) = (*(u16 *)(g_00500130 + 0x70) & 0xFE00) | field;
    *(u16 *)(g_00500130 + 0x260) = (*(u16 *)(g_00500130 + 0x260) & 0xFE00) | field;
    *(u16 *)(g_00500130 + 0xF0) = (*(u16 *)(g_00500130 + 0xF0) & 0xFE00) | field;
    g_00500130[1] = 0x80;
    g_00500130[0x29] = 0x80;
    g_00500130[0] = (g_00500130[0] & 0x5C) | 0x20;
    g_00500130[0x28] = (g_00500130[0x28] & 0x5C) | 0x20;
    FlushCache(0);
    func_00100E10(g_00500130);
    func_001265F0(0, 0);
    packet[0] = 0x1000000000008002ULL;
    packet[1] = 0x0E;
    packet[2] = (u64)(func_00100FB0() - 1) << 16 | (u64)(func_00100FC0() - 1) << 48;
    packet[3] = 0x40;
    packet[4] = (u64)(func_00100FB0() - 1) << 16 | (u64)(func_00100FC0() - 1) << 48;
    packet[5] = 0x41;
    FlushCache(0);
    func_0011B3E8(g_0045D1E0, packet, 3);
    func_001265F0(0, 0);
}

/* 0x00101400, 0x64 bytes, matching. Changes the display mode between frames. */
void func_00101400(int mode)
{
    if (g_0045D1C8 != mode) {
        func_001014D0(0);
        func_001020E0();
        func_001020E0();
        func_00101470(mode);
        func_001020E0();
        func_001020E0();
        func_001014D0(1);
    }
}

/* 0x00101470, 0x5C bytes, matching. */
void func_00101470(int mode)
{
    if (g_0045D1C8 != mode) {
        func_001256D0(1, 1, 3, 1);
        *(u16 *)(func_00125860() + 4) = 1;
        func_00100FF0(mode);
    }
}

/* 0x001014D0 is in main.c. */

/* 0x001014E0, 0x14 bytes, matching. */
u32 *func_001014E0(int i)
{
    return g_0045D1F8[i];
}

/* 0x00101500, 0x1A0 bytes. A packet that clears a 64-wide strip at `x` (height `h`) with
 * texture `tex` (FRAME 0x42, TEST 0x47, PRIM 0x14, then a sprite). */
void func_00101500(u64 *p, int x, int h, u64 tex, u64 alpha, u64 test, u64 prim, u64 rgbaq, int y)
{
    p[0] = 0x1000000000008003ULL;
    p[1] = 0x0E;
    p[2] = alpha;
    p[3] = 0x42;
    p[4] = test;
    p[5] = 0x47;
    p[6] = prim;
    p[7] = 0x14;
    p[8] = 0x8400000000008001ULL;            /* (a GIF tag: the high half comes from v0) */
    p[9] = 0x53531860;
    func_00118850(p + 10, 0x40);
    p[10] = 0x156;
    p[11] = tex;
    p[12] = (u64)(h - 1) << 34 | (u64)x << 4 | 10 | (u64)(x + 0x3F) << 14;
    p[13] = rgbaq;
    p[15] = (u64)((x + 0x700) * 0x10) | (u64)(y + 0x7800) << 16;
    p[17] = (u64)((x + 0x740) * 0x10) | (u64)(y + 0x8800) << 16;
    p[14] = (u64)(x * 0x10 + 8) | 0x80000;
    p[16] = (u64)((x + 0x40) * 0x10 + 8) | (u64)(h * 0x10 + 8) << 16;
}

/* 0x001016A0, 0x94 bytes. A TEX0 word for a w x h buffer at `base`. */
u64 func_001016A0(int w, int h, int base)
{
    int tw = func_00106980(w);
    int th = func_00106980(h);
    int bw = func_001069C0(0, w);

    return (u64)th << 30 | (u64)tw << 26 | (u64)bw << 14 | (u64)(base << 5);
}

/* 0x00101740, 0x84 bytes. A packet's header and its draw environment. */
void func_00101740(u64 *p, u8 *env, u16 w, u16 h, u16 fbp)
{
    p[0] = 0x1000000000008008ULL;
    p[1] = 0x0E;
    func_00125E88(env, 0, w, h, 0, 0x3A);
    *(u16 *)env = (*(u16 *)env & 0xFE00) | (fbp & 0x1FF);
}

/* 0x001017D0, 0x220 bytes. Prepares the clear packets: per buffer, eight strips drawn, eight
 * blended; and the half-height packet's eight strips. */
void func_001017D0(void)
{
    int b, i;

    for (b = 0; b < 2; b++) {
        u8 *packet = g_0045E900[b];
        u64 tex;

        func_00101740((u64 *)packet, packet + 0x10, 0x200, 0x100, 0);
        tex = func_001016A0(0x200, 0x1C0, 0x40);
        for (i = 0; i < 8; i++)
            func_00101500((u64 *)(packet + 0x90 + i * 0x120), i * 0x40, 0x1C0, tex,
                          0x8000000000ULL, 0x3000D, 0x60, 0x3F80000080808080ULL, 0);
        for (i = 0; i < 8; i++)
            func_00101500((u64 *)(packet + 0x120 + i * 0x120), i * 0x40, 0x1C0, tex,
                          0x8000000044ULL, 0x3000D, 0x60, 0x3F80000040808080ULL, 0);
    }
    {
        u64 tex;

        func_00101740((u64 *)g_0045FC20, g_0045FC20 + 0x10, 0x200, 0x100, 0);
        tex = func_001016A0(0x200, 0xE0, 0x40);
        for (i = 0; i < 8; i++)
            func_00101500((u64 *)(g_0045FC20 + 0x90 + i * 0x90), i * 0x40, 0xE0, tex,
                          0x8000000000ULL, 0x3000D, 0x60, 0x3F80000080808080ULL, 0);
    }
    FlushCache(0);
}

/* 0x001019F0, 0x8C bytes, matching. Starts the GS: PMODE, a first packet by GIF DMA, no offset, full
 * height, the clear packets. */
void func_001019F0(void)
{
    REG_GS_PMODE = 4;
    func_001256D0(0, 1, 3, 1);
    func_00126558(0);
    func_001265F0(0, 0);
    REG_DMAC_2_GIF_QWC = 10;
    REG_DMAC_2_GIF_MADR = (u32)g_00400B80;
    REG_DMAC_2_GIF_CHCR = 0x101;
    func_001265F0(0, 0);
    g_0045D1EC = 0;
    g_0045D1E8 = 0;
    func_00100FF0(0);
    func_001017D0();
}

/* 0x00101A80, 0x19C bytes. The default GS state: 13 registers (PRMODECONT, ALPHA, ..., the two
 * SCISSORs' frames at the display's origin). */
void func_00101A80(void)
{
    u64 packet[28];

    packet[0] = 0x100000000000800DULL;
    packet[1] = 0x0E;
    packet[2] = 1;
    packet[3] = 0x46;
    packet[4] = 0x6051273751603727ULL;
    packet[5] = 0x44;
    packet[6] = 0;
    packet[7] = 0x45;
    packet[8] = 0;
    packet[9] = 0x49;
    packet[10] = 1;
    packet[11] = 0x1A;
    packet[12] = 0;
    packet[13] = 0x22;
    packet[14] = 0x80;
    packet[15] = 0x3B;
    packet[16] = 0;
    packet[17] = 0x4A;
    packet[18] = 0x60;
    packet[19] = 0x14;
    packet[20] = (u32)func_00100FE0() | 0x3A000000;
    packet[21] = 0x4E;
    packet[22] = 0;
    packet[23] = 0x4B;
    packet[24] = 0x60;
    packet[25] = 0x15;
    packet[26] = (u32)func_00100FE0() | 0x3A000000;
    packet[27] = 0x4F;
    FlushCache(0);
    func_0011B3E8(g_0045D1E0, packet, 14);
    func_001265F0(0, 0);
}

/* 0x00101C20, 0x70 bytes. The DMA handler: the line counter (modulo 263) and a callback past
 * g_0045D190 lines. */
int func_00101C20(int cause)
{
    g_0045D184 = REG_RCNT1_COUNT % 0x107;
    if (g_0045D190 < g_0045D184 && g_0045D198 != 0)
        g_0045D198(g_0045D184);
    __asm__ volatile("sync.l");
    EI();
    return cause;
}

/* 0x00101C90, 0x384 bytes. The frame flip: waits for the previous VIF1 transfer (after a
 * time-out, a reset), sends the next frame's clear packet, switches the display buffer (field
 * `g_0045D1F0`), and when `flip` starts the other packet buffer (a new DMA chain: VIF FLUSHA,
 * DIRECT 5, a GIF packet). */
void func_00101C90(int flip, int in_interrupt)
{
    u32 field;
    u8 *env;

    if (func_001265F0(1, 0) != 0) {               /* the previous transfer is not over */
        int stopped = in_interrupt == 0 ? func_00131EA0() : 0;

        func_0011B690(g_0045D1E4);
        *g_0045D1E4 &= 0xCF;
        REG_VIF1_FBRST = 1;
        func_00125870();
        if (stopped != 0)
            func_00131EF0();
        if (g_0045D198 != 0)
            g_0045D198(-1);
    }
    field = g_0045D1F0 ^ 1;
    if (g_0045D1C8 == 0) {
        func_0011B3E8(g_0045D1E0, g_0045E900[field], 0x99);
    } else {
        func_0011B3E8(g_0045D1E0, g_0045FC20, 0x51);
        if ((int)field < 1) {
            func_00126D10(g_00500130 + 0x60, 0x800, 0x800, (u16)field);
            func_00126F78(g_00500130 + 0xE0, 0x800, 0x800, (u16)field);
        } else {
            func_00126D10(g_00500130 + 0x1D0, 0x800, 0x800, (u16)field);
            func_00126F78(g_00500130 + 0x250, 0x800, 0x800, (u16)field);
        }
    }
    env = g_00500130 + field * 0x28;
    *env &= 0xFE;
    if (g_0045D1C4 == 0)
        *env &= 0xFD;
    else
        *env = (*env & 0xFD) | 2;
    if (in_interrupt == 0)
        FlushCache(0);
    else
        iFlushCache(0);
    func_001272E8(g_00500130, field);
    func_001265F0(0, 0);
    *g_0045D1E4 = (*g_0045D1E4 & 0xBF) | 0x40;
    if (flip == 0) {
        func_0011B380(g_0045D1E4, g_0045D1F8[g_70000150 ^ 1]);
    } else {
        u32 *chain;
        u64 *gif;

        func_0011B380(g_0045D1E4, g_0045D1F8[g_70000150]);
        g_70000150 ^= 1;
        chain = g_0045D1F8[g_70000150];
        chain[0] = 0x10000005;
        g_70000158 = chain + 3;
        chain[1] = 0;
        chain[2] = 0x13000000;
        *g_70000158 = 0x51000005;
        g_70000158 = g_70000158 + 1;
        gif = (u64 *)g_70000158;
        gif[0] = 0x1000000000008004ULL;
        gif[1] = 0x0E;
        gif[2] = 0x60;
        gif[3] = 0x14;
        gif[4] = 0;
        gif[5] = 8;
        gif[6] = 0;
        gif[7] = 0x22;
        gif[8] = 0;
        gif[9] = 0x49;
        g_70000158 = (u32 *)(gif + 10);
    }
}

/* 0x00102020, 0x48 bytes, matching. Ends the frame's DMA chain (an END tag). */
void func_00102020(void)
{
    u32 *p = g_70000158;

    *g_70000158 = 0x70000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    FlushCache(0);
    g_70000158 = p + 4;
}

/* 0x00102070, 0x48 bytes. Sets the two packet buffers (by default 0x00460130 and 0x004B0130,
 * 0x50000 bytes each). */
void func_00102070(u32 *base, int size)
{
    if (base == 0) {
        g_0045D1F8[0] = (u32 *)0x460130;
        g_0045D1F8[1] = (u32 *)0x4B0130;
        g_0045D1F4 = 0x50000;
    } else {
        g_0045D1F8[0] = base;
        g_0045D1F8[1] = (u32 *)((u8 *)g_0045D1F8[0] + size);
        g_0045D1F4 = size;
    }
    g_0045D1AC = 1;
}

/* 0x001020C0, 0x8 bytes, matching. Frames since start-up. */
int func_001020C0(void)
{
    return g_0045D1A4;
}

/* 0x001020D0, 0x8 bytes, matching. */
void func_001020D0(void)
{
}

/* 0x001020E0, 0x6C bytes. Ends the frame: closes the chain, the callback past g_0045D194
 * lines, waits for the vertical blank, flips. */
void func_001020E0(void)
{
    func_00102020();
    if (g_0045D194 < REG_RCNT1_COUNT && g_0045D19C != 0)
        g_0045D19C();
    g_0045D1A8 = 0;
    WaitSema(g_0045D1B0);
    g_0045D1A8 = 1;
    func_00101C90(1, 0);
    func_0023A860();
}

/* 0x00102150, 0xA4 bytes. The vertical blank handler (cause 2): the field, a flip when the
 * frame is ready, the frame semaphore, the frame count. */
int func_00102150(int cause)
{
    int status[6];

    if (cause == 2) {
        g_0045D1F0 = (u32)((REG_GS_CSR & 0x2000) >> 13);
        if (g_0045D1A8 == 0 || g_0045D1AC == 0) {
            REG_RCNT1_COUNT = 0;
            g_0045D188 = 0;
        } else {
            func_00101C90(0, 1);
            g_0045D188 = 1;
        }
        iReferSemaStatus(g_0045D1B0, status);
        if (status[3] != 0)
            iSignalSema(g_0045D1B0);
        g_0045D1A4++;
    }
    return 0;
}

/* 0x00102200, 0x8C bytes, matching. The frame semaphore and the two handlers. */
void func_00102200(void)
{
    int params[6];

    params[1] = 1;
    params[2] = 0;
    params[5] = 0;
    g_0045D1B0 = CreateSema(params);
    g_0045D1AC = 1;
    g_0045D1A8 = 0;
    g_0045D1A4 = 0;
    g_0045D18C = func_0010B198(func_00102150, 0);
    func_00128928(2);
    if (g_0045CC00 == -1) {
        g_0045CC00 = AddDmacHandler(1, func_00101C20, 0);
        func_001289F8(1);
    }
}

/* 0x00102290, 0xAC bytes. The frame system's start: timing constants (1/60, 60.0, 3600.0,
 * ...), the packet buffers, the handlers, the two counters (HBLANK clock, mode 0x83). */
void func_00102290(void)
{
    *(u32 *)&g_0045D1BC = 0x3C888889;        /* 1/60 */
    *(u32 *)&g_0045D1C0 = 0x42700000;        /* 60.0 */
    *(u32 *)&g_0045D1B8 = 0x45610000;        /* 3600.0 */
    g_0045D1F0 = 0;
    *(u32 *)&g_0045D1B4 = 0x3991A2B5;
    g_70000150 = 0;
    func_00102070(0, 0);
    g_70000158 = g_0045D1F8[g_70000150];
    g_0045D1A0 = 0;
    g_0045D19C = 0;
    g_0045D198 = 0;
    func_00126558(0);
    func_0010B158();
    func_00102200();
    REG_RCNT0_COUNT = 0;
    REG_RCNT0_MODE = 0x83;
    REG_RCNT1_COUNT = 0;
    REG_RCNT1_MODE = 0x83;
}

/* 0x00102340, 0x1C bytes, matching. */
void func_00102340(void)
{
    func_00133D50();
}

/* 0x00102360, 0x1C bytes, matching. */
void func_00102360(void)
{
    func_00133B30();
}

/* 0x00102380, 0x28 bytes, matching. */
void func_00102380(void)
{
    if (g_0045D1A0 != 0)
        g_0045D1A0();
}

/* 0x001023B0, 0x8 bytes, matching. */
void func_001023B0(void (*callback)(void))
{
    g_0045D1A0 = callback;
}

/* 0x001023C0, 0xC bytes, matching. */
void func_001023C0(void (*callback)(void), u32 lines)
{
    g_0045D19C = callback;
    g_0045D194 = lines;
}

/* 0x001023D0, 0xC bytes, matching. */
void func_001023D0(void (*callback)(int line), u32 lines)
{
    g_0045D198 = callback;
    g_0045D190 = lines;
}

/* 0x001023E0, 0x2C bytes, matching. Starts the display and the frame system. */
void func_001023E0(void)
{
    func_001019F0();
    func_00101A80();
    func_00102290();
}
