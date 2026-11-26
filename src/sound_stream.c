/*
 * sound_stream.c - sound set-up, volumes and the music stream (original source file unknown;
 * 0x00114B20-0x0011585C, after the sound library linked before it).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. The func_0010xxxx functions called here belong to the
 * sound library (an IOP sound driver reached by RPC); their meaning is guessed from their use.
 *
 * Volumes go from 0 to 0x3FFF (0x7FFF masked) and can be faded: a fade is (from, to, frames,
 * frame), stepped once per frame by func_00114BB0. There are three kinds: the master volume, the
 * music stream's volume and one per sound channel (16, at 0x00560F60). The music stream itself
 * is driven by a request word (0x00560FE0: 1 play, 2 stop, 4 a third request with the stream's
 * third value, 8 set the volume), handled once per frame by func_001155F0 under the semaphore
 * g_0045D230, and only while the disc reader is idle.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A volume fade. */
typedef struct {
    u16 from;
    u16 to;
    u16 frames;              /* 0: none */
    u16 frame;
} Fade;

/* The reverb settings (passed to func_0010DA50). */
typedef struct {
    int core;
    int mode;
    u16 depth_l;
    u16 depth_r;
    int delay;
    int feedback;
} Reverb;

/* The music stream's request (0x00560FE0). */
extern struct {
    u32 flags;               /* 1 play, 2 stop, 4 ?, 8 set the volume */
    int a;                   /* 0x00560FE4 */
    int start;               /* 0x00560FE8 */
    int b;                   /* 0x00560FEC */
    int c;                   /* 0x00560FF0 (-1: loops?) */
    int volume;              /* 0x00560FF4 */
} g_00560FE0;

extern Fade g_00560F60[16];              /* each channel's fade */

/* The mix settings sent to the sound library (0x004013F0: master volume at +4 and +0xC). */
extern struct {
    u32 head;
    u32 left;                /* 0x004013F4 */
    u32 pad;
    u32 right;               /* 0x004013FC */
} g_004013F0;

/* The driver's settings (0x00401400, 0x1C entries of 8 bytes?): the free voice masks at +0x6C,
 * +0x74, +0x7C, +0x84. */
extern u32 g_00401400[0x38];

/* A semaphore's parameters (ee_sema_t). */
typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    u32 attr;
    u32 option;
} SemaParam;

/* (small data) */
extern u8 g_0045D218;                    /* output mode: 0, 1 or other */
extern u16 g_0045D21C;                   /* master volume */
extern u16 g_0045D220;                   /* music volume */
extern u16 g_0045D224;                   /* channel volume (the last one set) */
extern u32 g_0045D228;
extern int g_0045D230;                   /* the sound semaphore */
extern int g_0045D234;                   /* 1 once the sound is set up */
extern int g_0045D238;                   /* 1 once the driver is started */
extern short g_0045D23C;                 /* music fade-out: frames left */
extern short g_0045D240;                 /* music fade-out: length (0 none) */
extern Fade g_0045D248;                  /* master volume fade */
extern Fade g_0045D250;                  /* music volume fade */
extern u16 g_0045D258;                   /* the music is playing (and will be restarted?) */

int func_0010D860(int core, void *settings, int a, int b);
void func_0010DA50(int core, Reverb *r);
void func_0010C3A0(int core, int a);
void func_0010D5E0(int core, int mode);
int func_0010C170(int port);
int func_0010C4D0(int port);
u32 func_0010C538(void);
void func_0010C420(void);
void func_0010C478(int port);
int func_0010C2F8(int port, int volume, int a, int b);
void func_0010BD90(int port);
int func_0010C060(int port, int a, int b, int c, int volume, int d, int e, int start);
int func_0010C278(int port, int c);
void func_001171A0(void);
void func_00117220(int port);
void func_001178E0(int channel, int volume);
int func_00115C80(int poll);
int func_0010FA38(int core, u32 *voices);
int func_0010BDF0(int port, int a, int b, int c);
int func_0010BEF0(int port, int a, int b, int c, int d, int e, int f);
int func_0010D090(int a);
int func_0011A920(int media);                    /* sceCdMmode */
void func_00117BA0(int bank);
void func_00117DF0(int bank);
void func_00117BD0(void);
void func_00117E30(void);
void func_001178A0(void);
void func_00117620(int volume);
void func_00117C70(int volume);
u16 func_00116FA0(u16 volume);
void func_00115D40(void);
void func_00116520(void);
void func_00115810(u16 playing);
int CreateSema(SemaParam *p);
int DeleteSema(int sema);
int WaitSema(int sema);
int SignalSema(int sema);

void func_001153B0(void);
void func_001155A0(int volume);
void func_001155F0(int port);
void func_00115270(void);
void func_001154A0(u16 volume);

/* 0x00114B20, 0x48 bytes, matching. A short busy wait (0x100000 turns). */
void func_00114B20(void)
{
    volatile int i;

    for (i = 0; i < 0x100000; i++)
        ;
}

/* 0x00114B70, 0x40 bytes, matching. Sets the master volume (both sides). */
void func_00114B70(u16 volume)
{
    g_004013F0.right = volume;
    g_004013F0.left = volume;
    func_0010D860(1, &g_004013F0, 0, 2);
}

/* 0x00114BB0, 0x60 bytes. One step of a fade; the volume now (the target once over). */
u16 func_00114BB0(Fade *f)
{
    f->frame++;
    if (f->frame >= f->frames) {
        f->frames = 0;
        return f->to;
    }
    return f->from + (f->to - f->from) * f->frame / f->frames;
}

/* 0x00114C10, 0x58 bytes. Sets the master volume, at once or over `frames`; the previous one. */
u16 func_00114C10(u16 volume, u16 frames)
{
    u16 old = g_0045D21C;

    volume &= 0x7FFF;
    g_0045D248.frames = frames;
    g_0045D248.frame = 0;
    if (frames == 0) {
        func_00114B70(volume);
        g_0045D21C = volume;
    } else {
        g_0045D248.to = volume;
        g_0045D248.from = old;
    }
    return old;
}

/* 0x00114C70, 0x1C bytes, matching. The same at once. */
void func_00114C70(u16 volume)
{
    func_00114C10(volume, 0);
}

/* 0x00114C90, 0x9C bytes. Sets the reverb of core 1 (its depth by `kind`: 1 more, 0 less), then
 * clears it on core 0? */
void func_00114C90(int kind)
{
    Reverb r;

    r.mode = 0x102;
    r.delay = 0x1E;
    r.core = 0;
    r.feedback = 5;
    if (kind == 1) {
        r.depth_l = 0x9FF;
        r.depth_r = 0x9FF;
    } else if (kind == 0) {
        r.depth_l = 0x4FF;
        r.depth_r = 0x4FF;
    } else {
        r.depth_l = 0x27FF;
        r.depth_r = 0x27FF;
    }
    func_0010DA50(1, &r);
    r.core = 1;
    r.mode = 0x100;
    r.depth_l = 0;
    r.depth_r = 0;
    func_0010DA50(1, &r);
}

/* 0x00114D30, 0x74 bytes. Sets the output mode (1 or 0, as in the options: stereo / mono?); the
 * previous one. */
u8 func_00114D30(int mode)
{
    u8 old = g_0045D218;
    int out;

    g_0045D218 = mode;
    func_0010C3A0(1, mode == 0);
    out = 1;
    if (mode != 1) {
        if (mode == 0)
            out = 2;
        else
            out = 0;
    }
    func_0010D5E0(1, out);
    return old;
}

/* 0x00114DB0, 0x8 bytes, matching. The output mode. */
u8 func_00114DB0(void)
{
    return g_0045D218;
}

/* 0x00114DC0, 0x24 bytes, matching. Drops the queued sound commands and the music request. */
void func_00114DC0(void)
{
    func_001171A0();
    func_00115270();
}

/* 0x00114DF0, 0x40 bytes. Sends the queued commands and handles the music request. */
void func_00114DF0(int all)
{
    if (all == 0) {
        func_00117220(0);
        func_001155F0(0);
    } else {
        func_00117220(3);
        func_001155F0(3);
    }
}

/* 0x00114E30, 0x170 bytes. Once per frame: steps the fades and sends what changed. */
void func_00114E30(void)
{
    u16 v;
    u32 volume, now;
    int i;
    Fade *f;

    if (g_0045D250.frames == 0)
        v = g_0045D220;
    else
        v = func_00114BB0(&g_0045D250);
    volume = v;
    now = volume;
    if (g_0045D240 != 0) {
        g_0045D23C--;
        if (g_0045D23C == 0) {
            g_0045D240 = 0;
            now = 0;
            func_001153B0();
        } else {
            now = (int)(v * (u16)g_0045D23C) / (int)(u16)g_0045D240 & 0xFFFF;
        }
    }
    if (volume != g_0045D220 || volume != now) {
        g_0045D220 = v;
        func_001155A0(now);
    }
    for (i = 0, f = g_00560F60; i < 16; i++, f++) {
        if (f->frames != 0) {
            v = func_00114BB0(f);
            if (v != g_0045D224) {
                g_0045D224 = v;
                func_001178E0(i, v * 0x7F / 0x3FFF & 0xFF);
            }
        }
    }
    if (g_0045D248.frames != 0) {
        v = func_00114BB0(&g_0045D248);
        if (v != g_0045D21C) {
            g_0045D21C = v;
            func_00114B70(v);
        }
    }
    func_00117220(3);
    func_001155F0(0);
}

/* 0x00114FA0, 0x214 bytes. Sets the sound up (first call: voices, the two banks `a` / `b`,
 * driver settings, reverb; later calls: stops everything), then resets the volumes and fades.
 * 0, or the driver's error. */
int func_00114FA0(int a, int b)
{
    int r, i;

    func_00115D40();
    func_00115C80(0);
    if (g_0045D234 == 0) {
        u32 voices[2];

        voices[1] = 0xC00001;
        voices[0] = 0xF00000;
        r = func_0010FA38(1, voices);
        if (r < 0)
            return r;
        g_00401400[27] = voices[0] ^ 0xFFFFFF;
        g_00401400[31] = voices[1] ^ 0xFFFFFF;
        g_00401400[29] = g_00401400[27];
        g_00401400[33] = g_00401400[31];
        func_00117BA0(a);
        func_00117DF0(b);
        r = func_0010BDF0(1, 0x5010, 1, 0x86);
        if (r < 0)
            return r;
        r = func_0010BEF0(1, 2, 1, 0x16, 0x17, 0, 0);
        if (r < 0)
            return r;
        r = func_0010D860(1, g_00401400, 0, 0x1C);
        if (r < 0)
            return r;
        func_00114C90(0);
        func_00117BD0();
        func_00117E30();
        g_0045D234 = 1;
    } else {
        func_00114DC0();
        func_0010C170(1);
        func_001178A0();
        func_00117220(1);
    }
    func_00115810(0);
    g_0045D228 = 0;
    g_0045D224 = 0;
    g_0045D220 = 0;
    g_0045D250.frames = 0;
    g_0045D248.frames = 0;
    for (i = 0; i < 16; i++)
        g_00560F60[i].frames = 0;
    g_0045D240 = 0;
    func_00114D30(1);
    func_001154A0(0x1F72);
    func_00117620(0x3FFF);
    func_00114DF0(1);
    func_00117C70(0x2CDC);
    func_00116FA0(0x3FFF);
    func_00114C70(0x3FFF);
    return 0;
}

/* 0x001151C0, 0xA8 bytes. Starts the sound driver and the disc reader, once; -1 when the driver
 * does not start. */
int func_001151C0(void)
{
    if (g_0045D238 == 0) {
        SemaParam s;
        int r;

        s.max_count = 1;
        s.init_count = 1;
        s.option = 0;
        g_0045D230 = CreateSema(&s);
        r = func_0010D090(0);
        func_00114B20();
        if (r < 0) {
            DeleteSema(g_0045D230);
            return -1;
        }
        func_00114C70(0);
        func_00114B20();
        while (func_0011A920(2) == 0)
            ;
        func_00116520();
        g_0045D238 = 1;
    }
    return 0;
}

/* 0x00115270, 0x2C bytes, matching. Drops the music request. */
void func_00115270(void)
{
    WaitSema(g_0045D230);
    g_00560FE0.flags = 0;
    SignalSema(g_0045D230);
}

/* 0x001152A0, 0x80 bytes, matching. Carries out a stop request now (the semaphore is let go meanwhile). */
void func_001152A0(void)
{
    WaitSema(g_0045D230);
    if (g_00560FE0.flags & 2) {
        int r;

        SignalSema(g_0045D230);
        r = func_0010C170(3);
        WaitSema(g_0045D230);
        if (r >= 0) {
            g_0045D258 = 0;
            g_00560FE0.flags &= ~2;
        }
    }
    SignalSema(g_0045D230);
}

/* 0x00115320, 0x90 bytes. Requests the music stream (a, b, c), at the music volume. */
void func_00115320(int a, int b, int c)
{
    WaitSema(g_0045D230);
    g_0045D240 = 0;
    g_00560FE0.flags = (g_00560FE0.flags & ~0x36) | 1;
    g_00560FE0.start = 0;
    g_00560FE0.a = a;
    g_00560FE0.b = b;
    g_00560FE0.c = c;
    SignalSema(g_0045D230);
    func_001154A0(g_0045D220);
}

/* 0x001153B0, 0x40 bytes, matching. Requests the music to stop. */
void func_001153B0(void)
{
    WaitSema(g_0045D230);
    g_00560FE0.flags = (g_00560FE0.flags & ~0x31) | 2;
    SignalSema(g_0045D230);
}

/* 0x001153F0, 0x3C bytes. Fades the music out over `frames` (0: stops it now). */
void func_001153F0(short frames)
{
    if (frames == 0)
        func_001153B0();
    g_0045D23C = frames;
    g_0045D240 = frames;
}

/* 0x00115430, 0x20 bytes. The frames left of the fade-out (0 when none). */
short func_00115430(void)
{
    if (g_0045D240 == 0)
        return 0;
    return g_0045D23C;
}

/* 0x00115450, 0x48 bytes. Sets the music volume, at once or over `frames`. */
void func_00115450(u16 volume, short frames)
{
    g_0045D250.frame = 0;
    g_0045D250.frames = frames;
    if (frames == 0) {
        g_0045D220 = volume & 0x7FFF;
        func_001155A0(g_0045D220);
    } else {
        g_0045D250.to = volume & 0x7FFF;
        g_0045D250.from = g_0045D220;
    }
}

/* 0x001154A0, 0x1C bytes, matching. The same at once. */
void func_001154A0(u16 volume)
{
    func_00115450(volume, 0);
}

/* 0x001154C0, 0x88 bytes. The music's state: 0x80 requested, 1 playing, 2 (status bit 4);
 * `update` asks the driver first. */
u32 func_001154C0(int update)
{
    u32 state = 0;

    if (update != 0)
        func_0010C4D0(1);
    WaitSema(g_0045D230);
    if (g_00560FE0.flags & 1)
        state = 0x80;
    SignalSema(g_0045D230);
    if (func_0010C538() & 1)
        state |= 1;
    if (func_0010C538() & 4)
        state |= 2;
    return state;
}

/* 0x00115550, 0x50 bytes. Stops the music at once (fades ended, request dropped). */
void func_00115550(void)
{
    if (g_0045D250.frames != 0) {
        g_0045D250.frames = 0;
        g_0045D220 = g_0045D250.to;
    }
    if (g_0045D240 != 0)
        g_0045D240 = 0;
    func_00115270();
    func_0010C170(1);
    g_0045D258 = 0;
}

/* 0x001155A0, 0x4C bytes, matching. Requests a new music volume. */
void func_001155A0(int volume)
{
    WaitSema(g_0045D230);
    g_00560FE0.flags |= 8;
    g_00560FE0.volume = volume;
    SignalSema(g_0045D230);
}

/* 0x001155F0, 0x21C bytes. Handles the music request on port `port` (when the disc reader is
 * idle): a stopped loop is restarted, then volume, stop, play and the third request, each
 * dropped once the driver took it. */
void func_001155F0(int port)
{
    WaitSema(g_0045D230);
    if (g_0045D258 != 0 && func_00115C80(1) == 0 && (func_0010C538() & 1) == 0
        && (g_00560FE0.flags & 3) == 0)
        g_00560FE0.flags |= 1;
    if (g_00560FE0.flags != 0) {
        if ((g_00560FE0.flags & 8) && (g_00560FE0.flags & 3) == 0) {
            if (func_0010C2F8(port, g_00560FE0.volume, -1, -1) != 0)
                goto end;
            g_00560FE0.flags &= ~8;
            if (g_00560FE0.flags != 0)
                func_0010BD90(1);
        }
        if (func_00115C80(1) == 0) {
            if (g_00560FE0.flags & 2) {
                if (func_0010C170(port) != 0)
                    goto end;
                g_0045D258 = 0;
                g_00560FE0.flags &= ~2;
            }
            if (g_00560FE0.flags & 1) {
                int volume = (g_00560FE0.flags & 8) ? g_00560FE0.volume : -1;

                if (func_0010C060(port, g_00560FE0.a, g_00560FE0.b, g_00560FE0.c, volume, -1, -1,
                                  g_00560FE0.start) != 0)
                    goto end;
                g_00560FE0.flags &= ~0xD;
                g_0045D258 = g_00560FE0.c == -1;
            }
        }
        if ((g_00560FE0.flags & 4) && func_0010C278(port, g_00560FE0.c) == 0)
            g_00560FE0.flags &= ~4;
    }
end:
    SignalSema(g_0045D230);
}

/* 0x00115810, 0x8 bytes, matching. */
void func_00115810(u16 playing)
{
    g_0045D258 = playing;
}

/* 0x00115820, 0x40 bytes. Pauses the music while the disc is read (when it plays and is not
 * paused); whether it did. */
int func_00115820(void)
{
    if ((func_0010C4D0(1) & 0x41) == 1) {
        func_0010C420();
        return 1;
    }
    return 0;
}

/* 0x00115860, 0x38 bytes, matching. Resumes it, when func_00115820 paused it. */
void func_00115860(int paused)
{
    if (paused != 0 && (func_0010C4D0(1) & 0x41) == 0x41)
        func_0010C478(1);
}
