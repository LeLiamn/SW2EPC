/*
 * movie.c - playing the MPEG movies (original source file unknown; 0x00116610-0x0011719C,
 * after the disc reader).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Sony's libgraph, libdma and kernel functions are named in
 * the comments.
 *
 * The movies (LINKDATA.CNS, see docs/formats/PSS.md) are played by a player linked before the
 * sound library (func_00107578). This file sets it up: a parameter block at 0x00400C78 (sizes,
 * buffers, and callbacks into this file and the allocator), a work area of 0x5014 bytes, and a
 * thread of its own (priority 2) in which the scratchpad is saved and restored around the
 * player. Its own double buffer at 0x00562830 shows the frames; at each vblank the display is
 * moved one line down (and one line shorter), for the interlaced field. A callback given by the
 * caller is called on each frame (with the frame number from 1) and another one can stop the
 * movie (the pads are read once, on the first call).
 */

#define SW2E_FILE_MOVIE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define REG_RCNT1_COUNT (*(volatile u32 *)0x10000800)
#define REG_GS_DISPFB1  (*(volatile u64 *)0x12000070)
#define REG_GS_DISPLAY1 (*(volatile u64 *)0x12000080)

/* GS registers as bitfields (first field = lowest bits). */
typedef struct {
    u64 en1 : 1, en2 : 1, crtmd : 3, mmod : 1, amod : 1, slbg : 1, alp : 8, pad : 48;
} GsPmode;
typedef struct {
    u64 fbp : 9, fbw : 6, psm : 5, pad0 : 12, dbx : 11, dby : 11, pad1 : 10;
} GsDispfb;
typedef struct {
    u64 dx : 12, dy : 11, magh : 4, magv : 2, pad0 : 3, dw : 12, dh : 11, pad1 : 9;
} GsDisplay;
typedef struct {
    u64 fbp : 9, pad0 : 7, fbw : 6, pad1 : 2, psm : 6, pad2 : 2, fbmsk : 32;
} GsFrame;
typedef struct {
    u64 zbp : 9, pad0 : 15, psm : 4, pad1 : 4, zmsk : 1, pad2 : 31;
} GsZbuf;

/* A display environment (sceGsDispEnv). */
typedef struct {
    GsPmode pmode;
    u64 smode2;
    GsDispfb dispfb;
    GsDisplay display;
    u64 bgcolor;
} DispEnv;

/* A drawing environment with its GIF tag (sceGsDrawEnv1 + the clear sprite). */
typedef struct {
    u64 giftag[2];
    GsFrame frame;           /* +0x10 */
    u64 frame_reg;
    GsZbuf zbuf;             /* +0x20 */
    u64 rest[0x19];
} DrawEnv;

/* The movie's double buffer (sceGsDBuff, 0x00562830). */
extern struct {
    DispEnv disp[2];         /* 0x00562830 */
    DrawEnv draw[2];         /* 0x00562880, 0x00562970 */
} g_00562830;

/* The frame registers of the restore packet (0x004014E0, 15 quadwords). */
extern u8 g_004014E0[0xF0];
#define RESTORE_FRAME(i) (*(GsFrame *)(g_004014E0 + 0x50 + (i) * 0x50))   /* 0x00401530, 0x00401580 */

/* The player's parameters (0x00400C78). */
extern struct {
    int width;               /* 0x00400C78 */
    int height;
    int buffer;              /* 0x1400 */
    int a;
    int b;                   /* 10 */
    int width2;
    int height2;
    u8 c, d, e, f;           /* 0x00400C94 */
    float scale;             /* 0x00400C98 */
    void (*leave)(void);     /* 0x00400C9C */
    void (*leave2)(void);
    void (*on_header)(u32 *header);
    int (*stop)(void);
    void (*on_frame)(int frame);
    void (*on_vblank)(int field);
    void *(*alloc)(int align, u32 size);
    void (*free)(void *data);
    int g;                   /* 0x00400CBC */
    int h;
    int entry;               /* 0x00400CC4 */
    int entry2;              /* -1 without the second option */
    int i;                   /* 0x00400CCC */
    int field;               /* 0x00400CD0 */
} g_00400C78;

extern u32 g_00562A60[8];                /* the last stream header */

/* (small data) */
extern u16 g_0045D220;                   /* music volume (sound_stream.c) */
extern u16 g_0045D22C;                   /* the movie's volume */
extern int g_0045D25C;                   /* pad reads left / vblanks */
extern void (*g_0045D260)(int frame);    /* the caller's frame callback */
extern int (*g_0045D264)(void);          /* the caller's stop test */
extern u8 *g_0045D268;                   /* the work area */
extern int g_0045D26C;                   /* the movie has no audio track? */
extern int g_0045D1E0;                   /* the GIF DMA channel */

extern u8 _gp[];

/* A thread's parameters (ee_thread_t). */
typedef struct {
    int status;
    void (*entry)(void *);
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    int option;
} ThreadParam;

int func_0010C2F8(int port, int volume, int a, int b);
void func_0010BDF0(int port, int a, int b, int c);
void func_0010BE98(int port);
int func_0010B198(int (*handler)(void), int a);        /* adds a vblank handler? */
void func_0010B268(int id);
int func_00107578(u8 *data, u32 size, int a, int *b);  /* the movie player */
int func_00107628(void);                               /* a timer start? */
int func_00107670(void);                               /* its time, in ms? */
void func_00128060(int a);                             /* FlushCache */
int func_00126558(int mode);                           /* sceGsSyncV */
int func_001265F0(int a, int b);                       /* sceGsSyncPath */
void func_0011B620(int chan, int a, int b);            /* sceDmaSync? */
void func_0011B3E8(int chan, void *data, int qwc);     /* sceDmaSendN */
void func_00126178(void *draw);                        /* sceGsPutDrawEnv */
void func_001264F8(void *db, int field);               /* sceGsSwapDBuff */
void func_001256D0(int a, int b, int c, int d);        /* sceGsResetGraph */
u8 *func_00125860(void);                               /* sceGsGetGParam */
void func_00126260(void *db, int psm, int w, int h, int ztest, int zpsm, int clear);
                                                       /* sceGsSetDefDBuff */
void func_0011EB80(void *to, const void *from, u32 size);  /* memcpy */
int func_00128928(int cause);                          /* DisableIntc */
int func_001288C0(int cause);                          /* EnableIntc */
void func_00128F20(int thread, void *arg);             /* StartThread */
void FlushCache(int a);
int GetThreadId(void);
int CreateThread(ThreadParam *p);
int SleepThread(void);
int WakeupThread(int thread);
int TerminateThread(int thread);
int DeleteThread(int thread);
void ExitThread(void);

/* 0x00116610, 0x23C bytes. Gives the game's display back: the restore packet takes the movie
 * buffers' frame settings, is sent, and the drawing environment is set again. */
void func_00116610(void)
{
    GsFrame *f;

    f = &RESTORE_FRAME(0);
    f->fbp = g_00562830.draw[0].frame.fbp;
    f->pad0 = g_00562830.draw[0].frame.pad0;
    f->fbw = g_00562830.draw[0].frame.fbw;
    f->pad1 = g_00562830.draw[0].frame.pad1;
    f->psm = g_00562830.draw[0].frame.psm;
    f->pad2 = g_00562830.draw[0].frame.pad2;
    f->fbmsk = g_00562830.draw[0].frame.fbmsk;
    f = &RESTORE_FRAME(1);
    f->fbp = g_00562830.draw[1].frame.fbp;
    f->pad0 = g_00562830.draw[1].frame.pad0;
    f->fbw = g_00562830.draw[1].frame.fbw;
    f->pad1 = g_00562830.draw[1].frame.pad1;
    f->psm = g_00562830.draw[1].frame.psm;
    f->pad2 = g_00562830.draw[1].frame.pad2;
    f->fbmsk = g_00562830.draw[1].frame.fbmsk;
    func_00128060(0);
    func_00126558(0);
    func_0011B620(g_0045D1E0, 1, 0);
    func_0011B3E8(g_0045D1E0, g_004014E0, 0xF);
    func_001265F0(0, 0);
    func_00126178(g_00400C78.field != 0 ? (void *)&g_00562830.draw[1] : (void *)&g_00562830.draw[0]);
    func_001265F0(0, 0);
}

/* 0x00116850, 0xE0 bytes. The vblank callback: swaps the buffers and shows field `field` one
 * line lower and one line shorter. */
void func_00116850(int field)
{
    GsDispfb fb;
    GsDisplay d;

    REG_RCNT1_COUNT = 0;
    func_001264F8(&g_00562830, field);
    fb = g_00562830.disp[field].dispfb;
    d = g_00562830.disp[field].display;
    fb.dby = fb.dby + 1;
    d.dh = d.dh - 1;
    REG_GS_DISPFB1 = *(u64 *)&fb;
    REG_GS_DISPLAY1 = *(u64 *)&d;
}

/* 0x00116930, 0x28 bytes, matching. The frame callback: the caller's, with frames counted from 1. */
void func_00116930(int frame)
{
    if (g_0045D260 != 0)
        g_0045D260(frame + 1);
}

/* 0x00116960, 0x60 bytes, matching. At the end of the movie: its volume back, the display back. */
void func_00116960(void)
{
    func_0010C2F8(1, g_0045D22C, 0x3FFF, 0);
    func_001265F0(0, 0);
    func_00126558(0);
    func_00116610();
    func_001264F8(&g_00562830, 0);
    func_001265F0(0, 0);
}

/* 0x001169C0, 0x38 bytes, matching. The same, without the buffer swap, at the music volume. */
void func_001169C0(void)
{
    func_0010C2F8(1, g_0045D220, 0x3FFF, 0);
    func_00126558(0);
    func_00116610();
}

/* 0x00116A00, 0xB4 bytes. Keeps a stream header (8 words); unless its second word is 0x1C, its
 * last word becomes 0x18, or 0 when g_0045D26C is set. */
void func_00116A00(u32 *header)
{
    g_00562A60[0] = header[0];
    g_00562A60[1] = header[1];
    g_00562A60[2] = header[2];
    g_00562A60[3] = header[3];
    g_00562A60[4] = header[4];
    g_00562A60[5] = header[5];
    g_00562A60[6] = header[6];
    g_00562A60[7] = header[7];
    if (header[1] != 0x1C) {
        header[7] = g_0045D26C != 0 ? 0 : 0x18;
        g_00562A60[7] = g_0045D26C != 0 ? 0 : 0x18;
    }
}

/* 0x00116AC0, 0x54 bytes. The stop test: the caller's (the pads are read before its first
 * call); 0 without one. */
int func_00116AC0(void)
{
    if (g_0045D264 == 0)
        return 0;
    if (g_0045D25C == 0) {
        func_001038D0();
        g_0045D25C = 2;
    }
    return g_0045D264();
}

/* 0x00116B20, 0x20 bytes. A handler counting g_0045D25C down. */
int func_00116B20(void)
{
    if (g_0045D25C != 0)
        g_0045D25C--;
    return -1;
}

/* 0x00116B40, 0x68 bytes, matching. The player's thread: the scratchpad is saved around the player, then
 * the caller is woken. */
void func_00116B40(void *arg)
{
    u8 *work = arg;

    func_0011EB80(work + 0x1000, (void *)0x70000000, 0x4000);
    *(int *)(work + 0x5010) = func_00107578(*(u8 **)(work + 0x5004), *(u32 *)(work + 0x5008), 0,
                                            *(int **)(work + 0x500C));
    func_0011EB80((void *)0x70000000, work + 0x1000, 0x4000);
    WakeupThread(*(int *)(work + 0x5000));
    ExitThread();
}

/* 0x00116BB0, 0xB8 bytes. Plays movie `entry` (offset, size) of `data` in the player's thread
 * and waits for it; the player's result. */
int func_00116BB0(u8 *data, int *entry)
{
    u8 *work = g_0045D268;
    ThreadParam t;
    int thread;

    *(int *)(work + 0x5000) = GetThreadId();
    *(u8 **)(work + 0x5004) = data + entry[0];
    *(int *)(work + 0x5008) = entry[1];
    *(int *)(work + 0x500C) = 0;
    t.entry = func_00116B40;
    t.stack_size = 0x1000;
    t.priority = 2;
    t.stack = work;
    t.option = 0;
    t.gp = _gp;
    thread = CreateThread(&t);
    func_00128F20(thread, work);
    SleepThread();
    TerminateThread(thread);
    DeleteThread(thread);
    return *(int *)(work + 0x5010);
}

/* 0x00116C70, 0x134 bytes. Fills the player's parameters: 640 x 512, the callbacks. */
void func_00116C70(int entry, int both)
{
    g_00400C78.width = 0x280;
    g_00400C78.height = 0x200;
    g_00400C78.buffer = 0x1400;
    g_00400C78.a = 0;
    g_00400C78.b = 10;
    g_00400C78.width2 = 0x280;
    g_00400C78.height2 = 0x200;
    g_00400C78.c = 0;
    g_00400C78.d = 5;
    g_00400C78.e = 2;
    g_00400C78.f = 2;
    g_00400C78.scale = 1.0f;
    g_00400C78.leave = func_00116960;
    g_00400C78.leave2 = func_001169C0;
    g_00400C78.on_header = func_00116A00;
    g_00400C78.stop = func_00116AC0;
    g_00400C78.on_frame = func_00116930;
    g_00400C78.on_vblank = func_00116850;
    g_00400C78.alloc = (void * (*)(int,  u32))(func_00102DB0);
    g_00400C78.free = (void (*)(void *))(func_00102EC0);
    g_00400C78.g = 0;
    g_00400C78.entry = entry;
    if (both == 0)
        entry = -1;
    g_00400C78.entry2 = entry;
    g_00400C78.i = 0x514;
}

/* 0x00116DB0, 0x68 bytes. Sets the sound driver up for a movie (`on`) or back for the game. */
void func_00116DB0(int on)
{
    if (on == 0) {
        func_0010BE98(1);
        func_0010BDF0(1, 0x5010, 1, 0x86);
    } else {
        func_00115C80(0);
        func_00115550();
        func_0010BE98(1);
        func_0010BDF0(1, 0x5010, 1, 0x32);
    }
}

/* 0x00116E20, 0x180 bytes. Plays a movie: `data` with its entry table `entries`, `stop` /
 * `on_frame` the caller's callbacks. When `timed`, waits afterwards as many frames as the
 * player's time (ms). The player's result, -1 without memory. */
int func_00116E20(u8 *data, int entry, int *entries, int timed, int (*stop)(void),
                  void (*on_frame)(int frame), int no_audio)
{
    int ms = 0, r, handler, masked;

    func_00116DB0(1);
    g_0045D26C = no_audio;
    if (timed != 0)
        ms = func_00107628();
    g_0045D268 = func_00102DB0(0x40, 0x5014);
    if (g_0045D268 == 0) {
        r = -1;
    } else {
        g_0045D25C = 0;
        g_0045D260 = on_frame;
        g_0045D264 = stop;
        handler = func_0010B198(func_00116B20, 0);
        masked = func_00128928(2);
        func_00116C70(entry, timed);
        r = func_00116BB0(data, entries);
        if (masked != 0)
            func_001288C0(2);
        func_0010B268(handler);
        func_00102EC0(g_0045D268);
    }
    if (timed != 0)
        ms = func_00107670();
    func_00116DB0(0);
    if (timed != 0) {
        int n;

        for (n = ms * 60 / 1000; n > 0; n--)
            func_00126558(0);
    }
    return r;
}

/* 0x00116FA0, 0xC bytes, matching. Sets the movies' volume; the previous one. */
u16 func_00116FA0(u16 volume)
{
    u16 old = g_0045D22C;

    g_0045D22C = volume;
    return old;
}

/* 0x00116FB0, 0x1EC bytes. Sets the movie's double buffer up: 640 x 512, frames at 0 and 0xA0,
 * Z at 0x140, both circuits on with alpha 0x80. */
void func_00116FB0(void)
{
    func_001256D0(1, 1, 3, 0);
    *(u16 *)(func_00125860() + 4) = 0;
    func_00126260(&g_00562830, 0, 0x280, 0x200, 0, 0x3A, 1);
    g_00562830.disp[0].dispfb.fbp = 0;
    g_00562830.disp[1].dispfb.fbp = 0xA0;
    g_00562830.draw[0].frame.fbp = 0xA0;
    g_00562830.draw[1].frame.fbp = 0;
    g_00562830.draw[0].zbuf.zbp = 0x140;
    g_00562830.draw[1].zbuf.zbp = 0x140;
    func_00100E10((unsigned char *)(&g_00562830));
    g_00562830.disp[1].pmode.alp = 0x80;
    g_00562830.disp[0].pmode.alp = 0x80;
    g_00562830.disp[0].pmode.en1 = 1;
    g_00562830.disp[0].pmode.en2 = 1;
    g_00562830.disp[0].pmode.mmod = 1;
    g_00562830.disp[0].pmode.slbg = 0;
    g_00562830.disp[1].pmode.en1 = 1;
    g_00562830.disp[1].pmode.en2 = 1;
    g_00562830.disp[1].pmode.mmod = 1;
    g_00562830.disp[1].pmode.slbg = 0;
    FlushCache(0);
}
