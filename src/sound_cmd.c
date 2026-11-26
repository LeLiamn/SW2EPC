/*
 * sound_cmd.c - the sound commands and channels (original source file unknown; 0x001171A0-
 * 0x00117E4C, before main.c's system set-up).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. The func_0010xxxx / func_00113xxx functions belong to the
 * sound library linked before the game's code.
 *
 * Commands for the sound driver are written into a buffer (0x00562A80, up to 0x3F2 bytes before
 * it is sent) under the sound semaphore, and the buffer is sent once per frame (func_00117220).
 * The 16 sound channels (0x00562E80, 0x40 bytes each) keep their settings and up to 15 sounds
 * (pointers to (size, offset) records of the sound bank); the bank is loaded into the IOP's
 * memory at g_0045D270. A second bank (g_0045D278) holds the voices played through the
 * streaming functions func_00113xxx.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A sound channel (0x40 bytes). */
typedef struct {
    u8 count;                /* sounds in use */
    u8 b;                    /* +1 (func_00117A90) */
    u8 a;                    /* +2 (func_00117A40) */
    u8 volume;               /* +3 (0-0x7F) */
    u32 *sound[15];          /* +4 each sound's (size, offset) record */
} Channel;

extern Channel g_00562E80[16];
extern u8 g_00562A80[0x400];             /* the command buffer */

/* A channel's volume fade (sound_stream.c). */
typedef struct {
    u16 from;
    u16 to;
    u16 frames;
    u16 frame;
} Fade;
extern Fade g_00560F60[16];

/* (small data) */
extern u16 g_0045D224;                   /* channel volume (the last one set) */
extern u16 g_0045D228;                   /* the voices' volume */
extern int g_0045D230;                   /* the sound semaphore */
extern u32 g_0045D270;                   /* the sound bank in the IOP's memory */
extern int g_0045D274;                   /* bytes in the command buffer */
extern u32 g_0045D278;                   /* the second bank in the IOP's memory */
extern int g_0045D27C;                   /* its size */

int func_0010DAF8(int port, int size, u8 *buffer);
int func_0010F6F8(u8 *to);
int func_0010E018(u8 *to, u8 a, u8 b, u8 c, int d, int e, int f, int g);
int func_0010F1E8(u8 *to, u8 a, u8 b, u8 c, int d);
int func_0010DC40(u8 *to, u8 a, u8 b, u8 c, int d, int e, int f, int g);
int func_0010F648(u8 *to, u8 channel, u8 volume);
int func_0010F5A8(u8 *to, u8 channel, u8 value);
int func_001101B8(int port, u32 address, u8 channel, u8 slot, u32 size);
void func_0010F840(int port, u8 channel, int value);
void func_0010F798(int port, u8 channel, int value);
u8 func_00113560(int port, int a);
void func_001136E0(int port);
void func_00113760(int port, int a);
void func_00113B88(int port, int voice, int a, int b, int c, u32 d, u32 e, int f);
void func_00113940(int port, int voice, int a, u32 b, u32 c, u32 d, u32 e, u32 f, int g, int h);
void func_00113810(int port, int voice, int a, int b, int c, int d);
void func_00113D70(int port, int a);
u32 func_00130118(u32 size);                     /* sceSifAllocIopHeap */
int WaitSema(int sema);
int SignalSema(int sema);

void func_001178E0(int channel, u8 volume);

/* Room for a command: the buffer is sent first when it is nearly full. */
#define CMD_ROOM()                                                  \
    if (g_0045D274 > 0x3F2) {                                       \
        func_0010DAF8(3, g_0045D274, g_00562A80);                   \
        g_0045D274 = 0;                                             \
    }

/* 0x001171A0, 0x8 bytes, matching. Drops the queued commands. */
void func_001171A0(void)
{
    g_0045D274 = 0;
}

/* 0x001171B0, 0x70 bytes, matching. Queues command func_0010F6F8. */
void func_001171B0(void)
{
    int n;

    WaitSema(g_0045D230);
    CMD_ROOM();
    n = func_0010F6F8(g_00562A80 + g_0045D274);
    if (n > 0)
        g_0045D274 += n;
    SignalSema(g_0045D230);
}

/* 0x00117220, 0x5C bytes, matching. Sends the queued commands on port `port`. */
void func_00117220(int port)
{
    WaitSema(g_0045D230);
    if (g_0045D274 != 0 && func_0010DAF8(port, g_0045D274, g_00562A80) != -1)
        g_0045D274 = 0;
    SignalSema(g_0045D230);
}

/* 0x00117280, 0xE0 bytes. Queues command func_0010E018 (a sound with its settings?). */
void func_00117280(u8 a, u8 b, u8 c, int d, int e, int f, int g)
{
    int n;

    WaitSema(g_0045D230);
    CMD_ROOM();
    n = func_0010E018(g_00562A80 + g_0045D274, a, b, c, d, e, f, g);
    if (n > 0)
        g_0045D274 += n;
    SignalSema(g_0045D230);
}

/* 0x00117360, 0xB0 bytes. Queues command func_0010F1E8. */
void func_00117360(u8 a, u8 b, u8 c, int d)
{
    int n;

    WaitSema(g_0045D230);
    CMD_ROOM();
    n = func_0010F1E8(g_00562A80 + g_0045D274, a, b, c, d);
    if (n > 0)
        g_0045D274 += n;
    SignalSema(g_0045D230);
}

/* 0x00117410, 0xE0 bytes. Queues command func_0010DC40. */
void func_00117410(u8 a, u8 b, u8 c, int d, int e, int f, int g)
{
    int n;

    WaitSema(g_0045D230);
    CMD_ROOM();
    n = func_0010DC40(g_00562A80 + g_0045D274, a, b, c, d, e, f, g);
    if (n > 0)
        g_0045D274 += n;
    SignalSema(g_0045D230);
}

/* 0x001174F0, 0x128 bytes. Sets channel `channel`'s volume (16 or more: all), at once or over
 * `frames`; the previous volume. */
u16 func_001174F0(int channel, int volume, short frames)
{
    u16 old = g_0045D224;

    g_00560F60[channel].frames = frames;
    g_00560F60[channel].frame = 0;
    if (frames == 0) {
        func_001178E0(channel, volume * 0x7F / 0x3FFF & 0xFF);
        g_0045D224 = volume;
    } else if (channel < 16) {
        g_00560F60[channel].from = g_0045D224;
        g_00560F60[channel].to = volume;
    } else {
        int i;

        for (i = 0; i < 16; i++) {
            g_00560F60[i].from = g_0045D224;
            g_00560F60[i].to = volume;
        }
    }
    return old;
}

/* 0x00117620, 0x24 bytes, matching. Sets all channels' volume at once. */
void func_00117620(int volume)
{
    func_001174F0(16, volume, 0);
}

/* 0x00117650, 0x124 bytes. Plays sound `slot` of channel `channel` from the bank, then sets the
 * channel's volume. */
void func_00117650(u32 channel, u32 slot)
{
    u32 *sound = g_00562E80[channel].sound[slot];

    if (sound != 0 && func_001101B8(1, g_0045D270 + sound[1], channel, slot, sound[0]) >= 0) {
        u32 volume = g_0045D224 * 0x7F / 0x3FFF;
        int n;

        WaitSema(g_0045D230);
        CMD_ROOM();
        n = func_0010F648(g_00562A80 + g_0045D274, channel, volume);
        if (n > 0) {
            g_0045D274 += n;
            g_00562E80[channel].volume = volume;
        }
        SignalSema(g_0045D230);
    }
}

/* 0x00117780, 0x118 bytes. Queues command func_0010F5A8 for one channel (16 or more: all). */
void func_00117780(int channel, u8 value)
{
    int n;

    if (channel < 16) {
        WaitSema(g_0045D230);
        CMD_ROOM();
        n = func_0010F5A8(g_00562A80 + g_0045D274, channel, value);
        if (n > 0)
            g_0045D274 += n;
        SignalSema(g_0045D230);
    } else {
        u32 i;

        for (i = 0; (int)i < 16; i++) {
            WaitSema(g_0045D230);
            CMD_ROOM();
            n = func_0010F5A8(g_00562A80 + g_0045D274, i, value);
            if (n > 0)
                g_0045D274 += n;
            SignalSema(g_0045D230);
        }
    }
}

/* 0x001178A0, 0x3C bytes, matching. The same with 0xF for each channel. */
void func_001178A0(void)
{
    int i;

    for (i = 0; i < 16; i++)
        func_00117780(i, 0xF);
}

/* 0x001178E0, 0x154 bytes. Sets a channel's volume (0-0x7F; 16 or more: all). */
void func_001178E0(int channel, u8 volume)
{
    int n;

    if (channel < 16) {
        WaitSema(g_0045D230);
        CMD_ROOM();
        n = func_0010F648(g_00562A80 + g_0045D274, channel, volume);
        if (n > 0) {
            g_0045D274 += n;
            g_00562E80[channel].volume = volume;
        }
        SignalSema(g_0045D230);
    } else {
        u32 i;
        Channel *c;

        for (i = 0, c = g_00562E80; (int)i < 16; i++, c++) {
            WaitSema(g_0045D230);
            CMD_ROOM();
            n = func_0010F648(g_00562A80 + g_0045D274, i, volume);
            if (n > 0) {
                c->volume = volume;
                g_0045D274 += n;
            }
            SignalSema(g_0045D230);
        }
    }
}

/* 0x00117A40, 0x50 bytes, matching. */
void func_00117A40(u32 channel, int value)
{
    func_0010F840(1, channel, value);
    g_00562E80[channel].a = value;
}

/* 0x00117A90, 0x50 bytes, matching. */
void func_00117A90(u32 channel, int value)
{
    func_0010F798(1, channel, value);
    g_00562E80[channel].b = value;
}

/* 0x00117AE0, 0x40 bytes, matching. Frees sound `slot` of a channel. */
void func_00117AE0(int channel, int slot)
{
    Channel *c = &g_00562E80[channel];

    if (c->sound[slot] != 0) {
        c->sound[slot] = 0;
        c->count--;
    }
}

/* 0x00117B20, 0x70 bytes. Gives a sound a free slot of a channel; the slot (15: none). */
int func_00117B20(int channel, u32 *sound)
{
    Channel *c = &g_00562E80[channel];
    int i;

    if (c->count >= 15)
        return 15;
    c->count++;
    for (i = 0; i < 15; i++) {
        if (c->sound[i] == 0) {
            c->sound[i] = sound;
            return i;
        }
    }
    return i;
}

/* 0x00117B90, 0x8 bytes, matching. The bank's address in the IOP's memory. */
u32 func_00117B90(void)
{
    return g_0045D270;
}

/* 0x00117BA0, 0x24 bytes, matching. Reserves the bank in the IOP's memory (`size` bytes, none when 0). */
void func_00117BA0(u32 size)
{
    if (size != 0)
        g_0045D270 = func_00130118(size);
}

/* 0x00117BD0, 0xA0 bytes. Resets the channels: no sounds, settings 0, volume 0x7F. */
void func_00117BD0(void)
{
    int i, j;
    Channel *c;

    for (i = 0, c = g_00562E80; i < 16; i++, c++) {
        c->count = 0;
        func_00117A90(i, 0);
        func_00117A40(i, 0);
        func_001178E0(i, 0x7F);
        for (j = 0; j < 15; j++)
            c->sound[j] = 0;
    }
    func_00117220(1);
}

/* 0x00117C70, 0xC bytes, matching. Sets the voices' volume; the previous one. */
u16 func_00117C70(u16 volume)
{
    u16 old = g_0045D228;

    g_0045D228 = volume;
    return old;
}

/* 0x00117C80, 0x8 bytes, matching. The voices' volume. */
u16 func_00117C80(void)
{
    return g_0045D228;
}

/* 0x00117C90, 0x24 bytes. */
u8 func_00117C90(int a)
{
    return func_00113560(1, a);
}

/* 0x00117CC0, 0x1C bytes, matching. */
void func_00117CC0(void)
{
    func_001136E0(1);
}

/* 0x00117CE0, 0x20 bytes, matching. */
void func_00117CE0(int a)
{
    func_00113760(1, a);
}

/* 0x00117D00, 0xE0 bytes, matching. Starts voice `voice` from record `r` (5 words) of the second bank,
 * `offset` added to its start, at the voices' volume. */
void func_00117D00(u32 *r, int voice, int a, int offset, int b, int loop)
{
    u16 volume;

    func_00113B88(1, voice, 0, voice + 0x14, b, voice * 0x1040 + 0x10BE80, r[2] << 11, 0x1000);
    func_00113940(1, voice, a, r[0], r[1] + offset, r[2], r[3], r[4], 2, loop != 0);
    volume = func_00117C80();
    func_00113810(1, voice, volume, volume, 0, 2);
}

/* 0x00117DE0, 0x8 bytes, matching. The second bank's address in the IOP's memory. */
u32 func_00117DE0(void)
{
    return g_0045D278;
}

/* 0x00117DF0, 0x3C bytes, matching. Reserves the second bank (`size` bytes, none when 0). */
void func_00117DF0(u32 size)
{
    if (size != 0) {
        g_0045D278 = func_00130118(size);
        if (g_0045D278 != 0)
            g_0045D27C = size;
    }
}

/* 0x00117E30, 0x20 bytes, matching. */
void func_00117E30(void)
{
    func_00113D70(1, 4);
}
