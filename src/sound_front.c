/*
 * sound_front.c - the game's sound front end between 0x0023A160 and 0x0023AE2C: voices and
 * streamed sounds from the sound table file (0x0074B7D8: a count, then five words per sound),
 * two stream buffers in IOP memory (0x0074B7EC, switched by 0x0074B7F4), the effects banks
 * table (0x0040E9E0, nine words per sound group) and the volumes. Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int *g_0074B7D8;                  /* the sound table */
extern int g_0074B7EC[2];                /* the two stream buffers */
extern u32 g_0074B7F4;                   /* the one in use */
extern int g_0074B7D4, g_0074B7E8;
extern int g_0045D4C4, g_0045D4C8, g_0045D4CC;   /* (small data) */
extern u8 g_00669D60[];                  /* settings: +0x53, +0x54 volumes */
extern int g_00500474;
extern u8 *g_00500478;
extern int g_0040E9E0[][9];              /* the effects banks */
extern int g_0043D010[0xB], g_0043D040[0xB];
extern char g_0043D070[];

int func_00102960(int a);
int func_00117DE0(void);
void func_00117D00(int *e, int ch, int v, int a, int off, int b);
int func_00117C90(int ch);
void func_00117CE0(int ch);
void func_00117CC0(void);
int func_001020C0(void);
void *func_001026D0(int a, int k, void *dest, int c, u32 size, u32 off, char *name, int line);
void func_00117C70(int v);
void func_00117A90(int k, int v);
void func_00117A40(int k, int v);
void func_001178A0(void);
void func_002A7840(void);
void func_00117280(int a, int b, u32 c, int d, int e, int f, int g);
void func_00117360(int a, int b, u32 c, int d);
void func_00117410(int a, int b, u32 c, int d, int e, int f, int g);
void func_00117650(int a, int b);
void func_00117AE0(int a, int b);

void func_0023AA60(int k, u32 dst, int a);
void func_0023AB00(int k, int a);
void func_0023AB70(u32 v);

/* 0x0023A160, 8 bytes, matching. */
int func_0023A160(void)
{
    return g_0045D4C4;
}

/* 0x0023A170, 8 bytes, matching. */
void func_0023A170(int v)
{
    g_0045D4C4 = v;
}

/* 0x0023A180, 0xE0 bytes. Plays sound `k` on channel `ch` (some voices lower the music). */
void func_0023A180(int k, int ch, int off)
{
    int *e, v;

    if (k >= *g_0074B7D8 || ch >= 4)
        return;
    e = g_0074B7D8 + k * 5 + 2;
    if (k > 0x1E61 && k < 0x1E71) {
        func_0023AB70(g_00669D60[0x53]);
        func_0023A170(1);
    }
    v = g_00500474 == 0 ? 0 : *(int *)(g_00500478 + 0x348);
    func_00117D00(e, ch, v, 0, off + func_00117DE0(), 0);
}

/* 0x0023A260, 0x24 bytes, matching. Whether channel 0 is playing. */
int func_0023A260(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A290, 0x58 bytes, matching. */
void func_0023A290(int k)
{
    if (func_00102960(0) != 0 && k < 0xA6) {
        func_0023AB00(k, 1);
        func_0023A180(k, 0, 0);
    }
}

/* 0x0023A2F0, 0xDC bytes. Plays streamed sound `a` and preloads `b` in the other buffer. */
int func_0023A2F0(int a, int b, int big)
{
    int lim = big == 0 ? 0xEC : 0x1478;

    if (func_00102960(0) == 0)
        return 0;
    if (a < lim) {
        func_0023A180(a + 0xA6, 0, g_0074B7EC[g_0074B7F4] - func_00117DE0());
        g_0074B7F4 = g_0074B7F4 == 0;
    }
    if (b < lim) {
        func_0023AA60(b + 0xA6, g_0074B7EC[g_0074B7F4], 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A3D0, 0x40 bytes. */
void func_0023A3D0(void)
{
    g_0074B7EC[0] = func_00117DE0();
    g_0074B7EC[1] = g_0074B7EC[0] + 0x28000;
    g_0074B7F4 = 0;
}

/* 0x0023A410, 0x68 bytes, matching. Whether the voice still plays (stopped after 750 ticks). */
int func_0023A410(void)
{
    int r = func_00117C90(0) == 1;

    if (r && (u32)(func_001020C0() - g_0045D4C8) > 0x2EE) {
        g_0045D4CC = 1;
        r = 0;
        func_00117CE0(0);
    }
    return r;
}

/* 0x0023A480, 0x6C bytes. Plays voice `k`. */
int func_0023A480(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xDF8) {
        func_0023A180(k + 0x199, 0, 0);
        g_0045D4C8 = func_001020C0();
    }
    return 1;
}

/* 0x0023A4F0, 0x64 bytes. Loads voice `k`. */
int func_0023A4F0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xDF8) {
        func_0023AB00(k + 0x199, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A560, 0x60 bytes. */
int func_0023A560(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 7)
        func_0023A180(k + 0x192, 0, 0);
    return 1;
}

/* 0x0023A5C0, 0x64 bytes. */
int func_0023A5C0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 7) {
        func_0023AB00(k + 0x192, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A630, 0x24 bytes, matching. */
int func_0023A630(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A660, 0x70 bytes. Loads sound `k` into the free stream buffer. */
int func_0023A660(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0x1E62) {
        func_0023AA60(k, g_0074B7EC[g_0074B7F4], 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A6D0, 0x90 bytes. Plays it from there. */
int func_0023A6D0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0x1E62)
        func_0023A180(k, 0, g_0074B7EC[g_0074B7F4] - func_00117DE0());
    g_0074B7F4 = g_0074B7F4 == 0;
    return 1;
}

/* 0x0023A760, 0x64 bytes. */
int func_0023A760(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xF) {
        func_0023AB00(k + 0x1E62, 0);
        func_00102960(0);
    }
    return 1;
}

/* 0x0023A7D0, 0x60 bytes. */
int func_0023A7D0(int k)
{
    if (func_00102960(0) == 0)
        return 0;
    if (k < 0xF)
        func_0023A180(k + 0x1E62, 0, 0);
    return 1;
}

/* 0x0023A830, 0x24 bytes, matching. */
int func_0023A830(void)
{
    return func_00117C90(0) == 1;
}

/* 0x0023A860, 0x48 bytes, matching. Puts the music volume back once the voice is over. */
void func_0023A860(void)
{
    if (func_0023A830() == 0 && func_0023A160() != 0) {
        func_0023AB70(g_00669D60[0x54]);
        func_0023A170(0);
    }
}

/* 0x0023A8B0, 0x4C bytes. */
int func_0023A8B0(int k)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023A180(k, 0, 0);
    return r != 0;
}

/* 0x0023A900, 0x54 bytes. */
int func_0023A900(int k, int a)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023AB00(k, a);
    return r != 0;
}

/* 0x0023A960, 0x4C bytes, matching. */
void func_0023A960(int k)
{
    if (func_00102960(0) != 0 && k < 7)
        func_0023A180(k + 0x192, 0, 0);
}

/* 0x0023A9B0, 0x54 bytes. */
int func_0023A9B0(int k, int a)
{
    int r = func_00102960(0);

    if (r != 0)
        func_0023AB00(k + 0x192, a);
    return r != 0;
}

/* 0x0023AA10, 0x24 bytes, matching. Stops channel `ch`. */
void func_0023AA10(int ch)
{
    if (ch < 4)
        func_00117CE0(ch);
}

/* 0x0023AA40, 0x1C bytes, matching. */
void func_0023AA40(void)
{
    func_00117CC0();
}

/* 0x0023AA60, 0x9C bytes. Loads sound `k` to IOP address `dst` (0: the default buffer). */
void func_0023AA60(int k, u32 dst, int a)
{
    int *t = g_0074B7D8;

    if (k >= *t)
        return;
    if (dst == 0)
        dst = func_00117DE0();
    func_001026D0(0, 0x69, (void *)(dst | 0x80000001), a, t[k * 5 + 4] << 0xB, t[k * 5 + 3] << 0xB,
                  g_0043D070, 0x284);
}

/* 0x0023AB00, 0x20 bytes, matching. */
void func_0023AB00(int k, int a)
{
    func_0023AA60(k, 0, a);
}

/* 0x0023AB20, 0x44 bytes. Loads the sound table. */
void func_0023AB20(void)
{
    g_0074B7D8 = func_001026D0(1, 0x569, 0, 1, 0, 0, g_0043D070, 0x290);
}

/* 0x0023AB70, 0x48 bytes. Sets the music volume (0-15). */
void func_0023AB70(u32 v)
{
    func_00117C70((v & 0xFF) * 0x2CDC / 0xF);
}

/* 0x0023ABC0, 0x74 bytes, matching. The eleven effects groups' volumes and pans. */
void func_0023ABC0(void)
{
    int k;

    for (k = 0; k < 0xB; k++) {
        func_00117A90(k, 100 - g_0043D010[k]);
        func_00117A40(k, g_0043D040[k]);
    }
}

/* 0x0023AC40, 0x2C bytes, matching. */
void func_0023AC40(void)
{
    func_001178A0();
    func_002A7840();
    func_0023ABC0();
}

/* 0x0023AC70, 0x50 bytes, matching. Plays effect `s` (bank by the high byte). */
void func_0023AC70(u32 s, int a, int b, int c, int d)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117280(g[7], g[8], s & 0xFF, a, b, c, d);
}

/* 0x0023ACC0, 0x44 bytes, matching. */
void func_0023ACC0(u32 s, int a)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117360(g[7], g[8], s & 0xFF, a);
}

/* 0x0023AD10, 0x50 bytes, matching. */
void func_0023AD10(u32 s, int a, int b, int c, int d)
{
    int *g = g_0040E9E0[(int)s >> 8];

    func_00117410(g[7], g[8], s & 0xFF, a, b, c, d);
}

/* 0x0023AD60, 0x38 bytes. */
void func_0023AD60(int i)
{
    func_00117650(g_0040E9E0[i][7], g_0040E9E0[i][8]);
}

/* 0x0023ADA0, 0x8C bytes. Frees the battle's effects banks. */
void func_0023ADA0(void)
{
    int k;

    for (k = 0; k < 0xCB; k++) {
        int *e = g_0040E9E0[k];

        if (e[7] > 3 && e[7] < 0xB && e[8] < 0xF) {
            func_00117AE0(e[7], e[8]);
            e[8] = 0xF;
        }
    }
    g_0074B7E8 = 0;
    g_0074B7D4 = 0;
}
