/*
 * ps2_sound.c - the sound driver calls (Sony's sd_call / SIF RPC to the IOP sound driver) for the
 * PC build.
 *
 * On the PS2 the sound runs on the IOP: the game sends commands (voices, volumes, reverb,
 * streams) through these calls. The port will decode the SPU2 ADPCM data and mix it at 48 kHz on
 * the PC (platform->audio_push, UPP milestone 2). Until then every call succeeds and plays
 * nothing: status words read 0 (idle), so the game never waits on them.
 * Names after the PS2 addresses; the game's own wrappers are in src/sound_stream.c and
 * src/sound_cmd.c.
 */
#include <string.h>
#include "upp.h"

extern const upp_platform *sw2e_platform;

static void silent(void)
{
    static int said;

    if (!said++)
        sw2e_platform->log(2, "sound: driver calls accepted, nothing played yet");
}

int func_0010D090(int a) { (void)a; silent(); return 0; }                         /* driver start (RPC bind) */
int func_0010D860(int core, void *settings, int a, int b) { (void)core; (void)settings; (void)a; (void)b; return 0; }
void func_0010DA50(int core, void *reverb) { (void)core; (void)reverb; }        /* reverb */
void func_0010C3A0(int core, int a) { (void)core; (void)a; }
void func_0010D5E0(int core, int mode) { (void)core; (void)mode; }
int func_0010C170(int port) { (void)port; return 0; }
int func_0010C4D0(int port) { (void)port; return 0; }                           /* stream status: idle */
unsigned int func_0010C538(void) { return 0; }                                  /* stream status: idle */
void func_0010C420(void) {}
void func_0010C478(int port) { (void)port; }
int func_0010C2F8(int port, int volume, int a, int b) { (void)port; (void)volume; (void)a; (void)b; return 0; }   /* volume */
void func_0010BD90(int port) { (void)port; }
int func_0010C060(int port, int a, int b, int c, int volume, int d, int e, int start)
{
    (void)port; (void)a; (void)b; (void)c; (void)volume; (void)d; (void)e; (void)start;
    return 0;
}
int func_0010C278(int port, int c) { (void)port; (void)c; return 0; }
int func_0010FA38(int core, unsigned int *voices) { (void)core; (void)voices; return 0; }
int func_0010BDF0(int port, int a, int b, int c) { (void)port; (void)a; (void)b; (void)c; return 0; }
int func_0010BEF0(int port, int a, int b, int c, int d, int e, int f)
{
    (void)port; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}

/* ---- the sound command encoders: build the driver's command bytes (kept exact, so the port's
 * own sound player can read the same stream later) ---- */

/* 0x0010DBD0: `width` bits of `v` from bit `shift` */
static unsigned int get_bits(unsigned int v, int shift, int width)
{
    return ((int)v >> shift) & ((1u << width) - 1);
}

/* 0x0010DBE8: puts `width` bits of `v` at bit `shift` of byte `at` of `to` */
static void put_bits(unsigned char *to, int at, int shift, int width, unsigned int v)
{
    unsigned char mask;

    if (shift == 0 && width == 8) {
        to[at] = (unsigned char)v;
        return;
    }
    mask = (unsigned char)((1u << width) - 1);
    to[at] = (unsigned char)((to[at] & ~(mask << shift)) | ((v & mask) << shift));
}

/* 0x0010F648: the channel volume command (0x7n, volume 0-128); its size, or an error */
int func_0010F648(unsigned char *to, unsigned char channel, unsigned int volume)
{
    if (channel >= 0x10)
        return -0x29;
    if (volume >= 0x81)
        return -0x2E;
    to[1] = 0;
    to[0] = 0;
    put_bits(to, 0, 4, 4, 7);
    put_bits(to, 0, 0, 4, channel);
    put_bits(to, 1, 0, 8, get_bits(volume, 0, 8));
    return 2;
}

/* 0x0010F798 / 0x0010F840: two per-channel settings sent to the sound driver at once (channel
 * 0-15, value under 0x80 / 0x31); 0 or an error. Kept for the port's sound player: nothing to
 * send on the PC yet. */
int func_0010F798(int port, unsigned char channel, unsigned int value)
{
    (void)port;
    if (channel >= 0x10)
        return -0x29;
    if (value >= 0x80)
        return -0x28;
    return 0;
}

int func_0010F840(int port, unsigned char channel, unsigned int value)
{
    (void)port;
    if (channel >= 0x10)
        return -0x29;
    if (value >= 0x31)
        return -0x28;
    return 0;
}

/* ---- more of the sound library (sd_call.c and the stream / 3D sound parts) ----
 * Requests to the IOP sound driver: accepted at once. The port's own sound player will act on
 * them later; the encoders below keep the command sizes exact. */

int func_00107578(void) { return 0; }                     /* the driver's start-up */
int func_00107628(void) { return 0; }                     /* opens the driver: its handle */
int func_00107670(void) { return 0; }                     /* closes it */
int func_0010B268(int id) { (void)id; return 0; }         /* drops a stream request */
int func_0010B6E0(int port, unsigned int source, int offset, unsigned int to, unsigned int count)
{ (void)port; (void)source; (void)offset; (void)to; (void)count; return 1; }   /* disc read into IOP memory */
int func_0010B7B8(int port, unsigned int source, int offset, unsigned int to, unsigned int count)
{ (void)port; (void)source; (void)offset; (void)to; (void)count; return 1; }   /* a read through the driver */
int func_0010BE98(int port) { (void)port; return 0; }     /* driver command 0x93 */

/* 0x0010C570: how full the driver's stream buffer is, in percent (and its size / fill) */
unsigned int func_0010C570(unsigned int *size, int *fill)
{
    if (size)
        *size = 0;
    if (fill)
        *fill = 0;
    return 100;
}

int func_0010DAF8(int port, unsigned int size, const void *data)   /* sends a data block (0x17) */
{
    (void)port; (void)data;
    return size < 0x439 ? 0 : -0x28;
}

/* 0x0010DC40 / 0x0010E018: the two note commands (10 bytes); the exact bit layout comes with the
 * sound player (the bytes are cleared, the size is right). */
int func_0010DC40(unsigned char *to, unsigned char ch, int a, int b, int c, int d, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    if (ch >= 0x10)
        return -0x29;
    memset(to, 0, 10);
    return 10;
}

int func_0010E018(unsigned char *to, unsigned char ch, int a, int b, int c, int d, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    if (ch >= 0x10)
        return -0x29;
    memset(to, 0, 10);
    return 10;
}

/* 0x0010F1E8: a 4-byte channel command (0x2n) */
int func_0010F1E8(unsigned char *to, unsigned char ch, unsigned char a, unsigned char b, unsigned int c)
{
    if (ch >= 0x10)
        return -0x29;
    if (a >= 0x0F)
        return -0x2A;
    if (b & 0x80)
        return -0x2B;
    if (c >= 0x800)
        return -0x2D;
    memset(to, 0, 4);
    put_bits(to, 0, 4, 4, 2);
    put_bits(to, 0, 0, 4, ch);
    put_bits(to, 1, 4, 4, a);
    put_bits(to, 1, 0, 4, get_bits(b, 3, 4));
    put_bits(to, 2, 5, 3, get_bits(b, 0, 3));
    put_bits(to, 2, 0, 5, get_bits(c, 6, 5));
    put_bits(to, 3, 2, 6, get_bits(c, 0, 6));
    return 4;
}

/* 0x0010F5A8: a 2-byte channel command (0x6n) */
int func_0010F5A8(unsigned char *to, unsigned char ch, unsigned char v)
{
    if (ch >= 0x10)
        return -0x29;
    if (v >= 0x10)
        return -0x2A;
    to[1] = 0;
    to[0] = 0;
    put_bits(to, 0, 4, 4, 6);
    put_bits(to, 0, 0, 4, ch);
    put_bits(to, 1, 4, 4, v);
    return 2;
}

/* 0x0010F6F8: the 1-byte command 0x80 */
int func_0010F6F8(unsigned char *to)
{
    to[0] = 0;
    put_bits(to, 0, 4, 4, 8);
    return 1;
}

int func_001101B8(int port, unsigned char ch, unsigned char v)     /* a channel setting (sent at once) */
{
    (void)port;
    if (ch >= 0x10)
        return -0x29;
    if (v >= 0x0F)
        return -0x2A;
    return 0;
}

/* the stream player's requests (0x00113560-0x00113D70) */
int func_00113560(int port, unsigned int n) { (void)port; return n < 4 ? 0 : -0x33; }
int func_001136E0(int port) { (void)port; return 0; }
int func_00113760(int port, unsigned int n) { (void)port; return n < 4 ? 0 : -0x33; }
int func_00113810(int port, unsigned int n, int a, int b, int c, int d)
{ (void)port; (void)a; (void)b; (void)c; (void)d; return n < 4 ? 0 : -0x33; }
int func_00113940(int port, unsigned int n) { (void)port; return n < 4 ? 0 : -0x33; }
int func_00113B88(int port, unsigned int n) { (void)port; return n < 4 ? 0 : -0x33; }
int func_00113D70(int port, int n) { (void)port; return (unsigned int)(n - 1) < 4 ? 0 : -0x33; }

/* 0x00114240 / 0x00114410 / 0x00114890: default 3D sound parameters */
static void put_words(void *to, int at, const unsigned int *v, int n)
{
    memcpy((unsigned char *)to + at, v, (size_t)n * 4);
}

void func_00114240(void *p)
{
    static const unsigned int v[20] = {
        0, 0, 0, 0x3F800000, 0, 0, 0x3F800000, 0, 0, 0xBF800000, 0, 0, 0, 0, 0, 0,
        0x3F800000, 0x3F800000, 0x3F800000, 0x43AA0000,
    };
    put_words(p, 0x40, v, 20);
}

void func_00114410(void *p)
{
    static const unsigned int v[18] = {
        0, 0, 0, 0x3F800000, 0, 0, 0, 0, 0x3F800000, 0x4E6E6B28, 0x3F800000, 0x3F800000,
        0x3F800000, 0x3F3504F3, 0x3F3504F3, 0x3F800000, 0, 0,
    };
    put_words(p, 0, v, 18);
}

void func_00114890(void *p)
{
    static const unsigned int v[11] = { 0, 0, 0, 0, 0, 0x1000, 0x3F3504F3, 0x3F3504F3, 0x1000, 0, 0 };
    put_words(p, 0, v, 11);
}
