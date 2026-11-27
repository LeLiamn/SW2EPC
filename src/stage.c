/*
 * stage.c - the battlefield stage (original source file Stage.c: its name is passed to the file
 * loader at 0x00193B90 and 0x00194130). Written so far: the small functions from 0x00193450
 * (the layers, the frame step, the clean-up), which come just before the name's first use.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The stage keeps its state in the scratchpad: +0x870 the time, +0x874 / +0x878 the frame step
 * and its inverse, +0x87C the number of height layers, +0xB7C the layers' heights, +0x880 /
 * +0x884 two buffers, +0x890 / +0x910 / +0x990 two banks of three matrices, +0xA10 two banks
 * of ten vectors, +0xB90 the banks' rectangles.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SPAD(off) ((u8 *)0x70000000 + (off))
#define SP32(off) (*(u32 *)SPAD(off))
#define SPF(off)  (*(float *)SPAD(off))
#define SPP(off)  (*(u8 **)SPAD(off))
#define PTR4(o)   (*(u8 **)((u8 *)(o) + 4))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

extern u32 g_00669DB8[4];                /* (settings) +0: the game mode */
extern u32 g_00669F60[4];                /* (settings) +0: the battle flags */
extern int g_0045D2A8;                   /* (small data) slow motion */
extern float g_0045CC7C;                 /* (small data) the frame rate factor */

int func_00191330(u8 *r, u8 *c);
int func_001912E0(u8 *grid, int x, int z);
int func_0032E7B0(void);
u8 *func_00194480(int k, int x, int z);
int func_00193620(float *p);
u32 *func_002184D0(int a, int i);
float func_00200110(void);
void func_001930D0(u32 layer, float *m);
void func_00196CB0(float r, u32 layer);
void func_00195920(u32 layer, float *m);
void func_00196B10(int bank);
void func_00245D60(void);
void func_001F5020(void);
void func_001970C0(void);
void func_001FC800(void);
void func_003BF820(void);
void func_0027E470(void);
void func_00247250(void);
u8 *func_00197130(u8 *p);
u8 *func_00197230(u8 *p);
void func_00193A70(void);
u32 func_001934D0(void);
u8 *func_002EFB00(int a);
void func_00102EC0(void *data);          /* free */
void *func_00102D30(u32 size);           /* allocate */
void func_00193710(u32 bank, float *m);
void func_00193830(u32 bank);

/* The bank of layer `k` (layers 3 and 4 use the second one). */
#define BANK(k) (0x18 >> ((k) & 0x1F) & 1)

/* 0x00193450, 0x80 bytes. Whether object `o` (its cell +0x1E, its grid +0x1C) is inside the
 * layer's rectangle and on a clear cell. */
int func_00193450(u32 layer, u8 *o)
{
    u32 b = BANK(layer);

    if (func_00191330(SPAD(0xB90) + b * 4, o + 0x1E) == 0)
        return 0;
    return func_001912E0((u8 *)0x5BF440 + o[0x1C] * 0x1E90 + b * 0x98D0, o[0x1E], o[0x1F]) != 0;
}

/* 0x001934D0, 0xC bytes, matching. The number of height layers. */
u32 func_001934D0(void)
{
    return SP32(0x87C);
}

/* 0x001934E0, 0x14 bytes, matching. The height of layer `i`. */
float func_001934E0(int i)
{
    return ((float *)SPAD(0xB7C))[i];
}

/* 0x00193500, 0x68 bytes. The layer of height `h`: the first whose next layer starts more
 * than 50 above it. */
int func_00193500(float h)
{
    int i;

    for (i = 0; i < (int)SP32(0x87C); i++) {
        if (!(((float *)SPAD(0xB7C))[i + 1] + 50.0f < h))
            return i;
    }
    return i;
}

/* 0x00193570, 0xA4 bytes. The layer under 3D point `p`: from its height down, the first with
 * ground at its 500-unit cell; 0 for none. */
int func_00193570(float *p)
{
    float x = p[0], z = p[2];
    int i = func_00193500(p[1]);

    func_0032E7B0();
    for (; i >= 1; i--) {
        if (func_00194480(i, (int)(x * 0.002f), (int)(z * 0.002f)) != 0)
            return i;
    }
    return 0;
}

/* 0x00193620, 0xE4 bytes. The same for ground that can be stood on (flag 1 of +7); layer 0
 * when the bottom one has flags 3, -1 for none. */
int func_00193620(float *p)
{
    float x = p[0], z = p[2];
    int i = func_00193500(p[1]);
    u8 *g;

    func_0032E7B0();
    for (; i >= 1; i--) {
        g = func_00194480(i, (int)(x * 0.002f), (int)(z * 0.002f));
        if (g != 0 && (g[7] & 1))
            return i;
    }
    g = func_00194480(1, (int)(x * 0.002f), (int)(z * 0.002f));
    if (g == 0 || (g[7] & 3) == 0)
        return -1;
    return 0;
}

/* m (four rows) times each row of r, into out. */
static inline void mat_mul4(float *out, const float *m, const float *r)
{
    int i, k;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            out[i * 4 + k] = m[k] * r[i * 4] + m[4 + k] * r[i * 4 + 1] + m[8 + k] * r[i * 4 + 2]
                             + m[12 + k] * r[i * 4 + 3];
}

/* 0x00193710, 0x114 bytes. Bank `bank`'s matrices from the camera's three (`m`: view, ?,
 * screen): the second with its depth row set (1.0204, -6060.6), then their products. */
void func_00193710(u32 bank, float *m)
{
    float *a = (float *)SPAD(0x890 + bank * 0x40);
    int k;

    for (k = 0; k < 16; k++)
        a[k] = m[16 + k];
    a[10] = 1.0204077f;
    a[14] = -6060.6064f;
    mat_mul4((float *)SPAD(0x910 + bank * 0x40), a, m);
    mat_mul4((float *)SPAD(0x990 + bank * 0x40), m + 32, (float *)SPAD(0x910 + bank * 0x40));
}

/* 0x00193830, 0x7C bytes. Bank `bank`'s ten vectors (func_002184D0). */
void func_00193830(u32 bank)
{
    int i;

    for (i = 0; i < 10; i++) {
        u32 *v = func_002184D0(0, i), *d = (u32 *)SPAD(0xA10 + bank * 0xA0 + i * 0x10);

        d[0] = v[0];
        d[1] = v[1];
        d[2] = v[2];
        d[3] = v[3];
    }
}

/* 0x001938B0, 0x90 bytes. Draws layer `layer` of the stage with the camera's matrices `m`. */
void func_001938B0(u32 layer, float *m)
{
    u32 b = BANK(layer);
    float t = func_00200110();

    func_00193710(b, m);
    func_001930D0(layer, m);
    func_00196CB0(t, layer);
    func_00195920(layer, m);
    func_00193830(b);
    func_00196B10(b);
}

/* 0x00193940, 0x3C bytes, matching. The stage's other parts each frame. */
void func_00193940(void)
{
    func_00245D60();
    func_001F5020();
    func_001970C0();
    func_001FC800();
    func_003BF820();
}

/* 0x00193980, 0xD0 bytes. The stage's frame step from `dt` (by the frame rate factor, a
 * quarter of it in slow motion, unless battle flag 0x100000): +0x874 = 50 dt, +0x878 its
 * inverse added to the time. */
void func_00193980(float dt)
{
    if (dt < 0.0001f)
        return;
    if ((g_00669F60[0] & 0x100000) == 0) {
        if (g_0045D2A8 == 0)
            dt = dt / g_0045CC7C;
        else
            dt = dt / (g_0045CC7C * 0.25f);
    }
    SPF(0x874) = dt * 50.0f;
    SPF(0x878) = 1.0f / SPF(0x874);
    SPF(0x870) = SPF(0x870) + SPF(0x878);
    func_0027E470();
    func_00247250();
}

/* 0x00193A50, 0x1C bytes, matching. Saves the stage models' states (func_00197130). */
u8 *func_00193A50(u8 *p)
{
    return func_00197130(p);
}

/* 0x00193A70, 0x24 bytes, matching. func_00197230 with func_002EFB00(5). */
void func_00193A70(void)
{
    func_00197230(func_002EFB00(5));
}

/* 0x00193AA0, 0xE4 bytes. Frees the stage's buffers (the five maps' and four layers' in game
 * mode 2). */
void func_00193AA0(void)
{
    u32 k;

    if (g_00669DB8[0] == 2) {
        for (k = 0; k < 5; k++) {
            if (SPP(0xB68 + k * 4) != 0) {
                func_00102EC0(SPP(0xB68 + k * 4));
                SPP(0xB68 + k * 4) = 0;
            }
        }
        for (k = 1; k < 5; k++) {
            if (SPP(0xB58 + k * 4) != 0) {
                func_00102EC0(SPP(0xB58 + k * 4));
                SPP(0xB58 + k * 4) = 0;
            }
        }
    }
    if (SPP(0x884) != 0) {
        func_00102EC0(SPP(0x884));
        SPP(0x884) = 0;
    }
    if (SPP(0x880) != 0) {
        func_00102EC0(SPP(0x880));
        SPP(0x880) = 0;
    }
}

extern u32 g_00669DC0[2];                /* (settings) +0: the scenario */
extern u8 *g_005BA694;                   /* the scenario table's entries (100 bytes each) */
extern u8 *g_0045D2F4;                   /* (small data) the stage table file (+4: its data) */
extern int g_00669F6C[4];                /* (settings) +0: the game mode (1: ?) */
extern const char g_004253D0[];          /* "Stage.c" */

void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const void *file, int line);
u32 func_0032F780(void);
int func_0032F090(u32 a);
void func_00118850(void *to, int size);  /* clear */
void func_00118AC0(void *to, const void *from, u32 n);  /* memcpy */
void func_00195EF0(void);
void func_00197420(void);
void func_00195D20(void);
void func_00195DB0(void);
void func_001F4940(void);
void func_00196530(void);
void func_001F4DC0(void);
u32 func_00196540(u8 *h);
void func_001966C0(u8 *a, u8 *b, u32 c);
void func_00197470(u8 *a);
void func_00196980(void);
void func_0027F2C0(void);
void func_00193AA0(void);

/* The scenario of the battle (mode 2: 0x54, mode 3: 0x55). */
#define SCENARIO() (g_00669DB8[0] == 2 ? 0x54 : (g_00669DB8[0] == 3 ? 0x55 : (int)g_00669DC0[0]))

/* 0x00193B90, 0x1A8 bytes. Loads the stage's two files: an event's (entries 0x917 / 0x9D1 +
 * n) or the scenario's map's (0x8FC / 0x9B6 + map). */
void func_00193B90(void)
{
    int ev = -1;

    if (func_0032E7B0() != 0)
        ev = func_0032F090(func_0032F780());
    if (ev == -1) {
        u32 m = *(unsigned short *)(g_005BA694 + SCENARIO() * 100 + 2);

        SPP(0x880) = func_001026D0(1, m + 0x8FC, 0, 1, 0, 0, g_004253D0, 0x49A);
        SPP(0x884) = func_001026D0(1, m + 0x9B6, 0, 1, 0, 0, g_004253D0, 0x49B);
    } else {
        SPP(0x880) = func_001026D0(1, ev + 0x917, 0, 1, 0, 0, g_004253D0, 0x495);
        SPP(0x884) = func_001026D0(1, ev + 0x9D1, 0, 1, 0, 0, g_004253D0, 0x496);
    }
}

/* 0x00193D40, 0x15C bytes. Sets the number of height layers (none in game mode 2) and their
 * heights: the stage's base height and every 1000 above (negative: Y points down). */
void func_00193D40(u32 n)
{
    SP32(0x87C) = n;
    if (g_00669DB8[0] == 2)
        SP32(0x87C) = 0;
    if (func_001934D0() != 0 || g_00669DB8[0] == 2) {
        int h = *(int *)SPP(0xB50), k;

        for (k = 0; k < 5; k++)
            ((float *)SPAD(0xB7C))[k] = ((float)h + (float)k * 1000.0f) * -1.0f;
    }
    func_00195EF0();
}

/* 0x00193EA0, 0x10C bytes. Clears the stage's state and grids; its record from the stage table
 * (by the scenario's map, or the fixed one of mode 2). */
void func_00193EA0(void)
{
    u8 *r;

    if (g_00669DB8[0] == 2)
        r = PTR4(g_0045D2F4) + 0x2E4;
    else
        r = PTR4(g_0045D2F4) + 4 + *(unsigned short *)(g_005BA694 + SCENARIO() * 100 + 2) * 0x10;
    func_00118850(SPAD(0x870), 0x330);
    func_00118850((u8 *)0x5BF440, 0x131A0);
    SPP(0xB50) = r;
    SPF(0x874) = 50.0f;
    SPF(0x878) = 0.02f;
}

/* 0x00193FB0, 0x3C bytes, matching. Shuts the stage down. */
void func_00193FB0(void)
{
    func_00197420();
    func_00195D20();
    func_00195DB0();
    func_001F4940();
    func_00193AA0();
}

/* 0x00193FF0, 0x1C bytes, matching. func_00196530. */
void func_00193FF0(void)
{
    func_00196530();
}

/* 0x00194010, 0xE8 bytes. Sets the stage up: its state, its files (the first one's offsets
 * made into addresses), its layers, its parts and its other data. */
void func_00194010(void)
{
    u32 *p, k, a, b, c, d;

    func_00193EA0();
    func_00193B90();
    p = (u32 *)SPP(0x880);
    for (k = 0; k < p[0]; k++)
        p[1 + k] = p[1 + k] + (u32)p;
    a = p[2];
    b = p[3];
    c = p[4];
    d = p[1];
    func_001F4DC0();
    func_00193D40(func_00196540((u8 *)d));
    func_001966C0((u8 *)a, (u8 *)b, c);
    func_00197470(SPP(0x884));
    func_00196980();
    if (g_00669F6C[0] == 1)
        func_00193A70();
    func_0027F2C0();
}

/* 0x00194100, 0x2C bytes, matching. Frees the stage table file. */
void func_00194100(void)
{
    if (g_0045D2F4 != 0) {
        func_00102EC0(g_0045D2F4);
        g_0045D2F4 = 0;
    }
}

/* The ground grid (scratchpad +0x7F0: cells of 0x14 bytes, +0x840 / +0x841 its width and
 * height in 500-unit cells) and the layers' grids (+0x7F4 + 4k: 50 x 50 cells of 12 bytes from
 * cell +0x842 + 2k). */
#define GRID_W (*(u8 *)SPAD(0x840))
#define GRID_H (*(u8 *)SPAD(0x841))

void func_0027F6D0(u32 a);

/* 0x00194130, 0x84 bytes. Loads the stage table (LINKDATA entry 0x34), its offsets made into
 * addresses. */
void func_00194130(void)
{
    u32 *t = func_001026D0(1, 0x34, 0, 1, 0, 0, g_004253D0, 0x591), k;

    g_0045D2F4 = (u8 *)t;
    for (k = 0; k < t[0]; k++)
        t[1 + k] = t[1 + k] + (u32)t;
    func_0027F6D0(t[2]);
}

/* 0x001941C0, 0xA0 bytes, matching. The terrain kind of ground type `t` (0x15-0x26; others are kept). */
int func_001941C0(int t)
{
    switch (t) {
    case 0x15:
    case 0x22:
        return 3;
    case 0x16:
    case 0x1F:
        return 4;
    case 0x17:
        return 2;
    case 0x18:
        return 0xF;
    case 0x19:
        return 0x14;
    case 0x1A:
    case 0x26:
        return 0xC;
    case 0x1B:
        return 0x12;
    case 0x1C:
        return 0x10;
    case 0x1D:
    case 0x1E:
        return 9;
    case 0x20:
        return 0x11;
    case 0x21:
        return 1;
    case 0x23:
    case 0x24:
        return 6;
    case 0x25:
        return 0;
    }
    return t;
}

/* 0x00194260, 0x30 bytes, matching. Whether ground type `t` is of terrain kind `k`. */
int func_00194260(int k, int t)
{
    return k == func_001941C0(t);
}

/* 0x00194290, 0xC bytes, matching. */
u32 func_00194290(void)
{
    return SP32(0x814);
}

/* 0x001942A0, 0xC bytes, matching. */
u32 func_001942A0(void)
{
    return SP32(0x818);
}

/* 0x001942B0, 0xC bytes, matching. */
u32 func_001942B0(void)
{
    return SP32(0x81C);
}

/* 0x001942C0, 0x20 bytes, matching. */
u32 func_001942C0(void)
{
    return func_001942A0() + 0x50;
}

/* 0x001942E0, 0x48 bytes. Whether cell (x, z) is on the ground grid. */
int func_001942E0(int x, int z)
{
    return x > -1 && z > -1 && x < GRID_W && z < GRID_H;
}

/* 0x00194330, 0x80 bytes. Cell (x, z) kept on the grid. */
void func_00194330(u8 *out, int x, int z)
{
    if (x < 1)
        x = 0;
    if (z < 1)
        z = 0;
    out[0] = (int)(GRID_W - 1) < x ? GRID_W - 1 : x;
    out[1] = (int)(GRID_H - 1) < z ? GRID_H - 1 : z;
}

/* 0x001943B0, 0x38 bytes. A point kept inside the stage's bounds (+0x830) and above 0.0001. */
void func_001943B0(float *p)
{
    float *b = (float *)SPAD(0x830);
    int k;

    for (k = 0; k < 4; k++) {
        float v = p[k] < b[k] ? p[k] : b[k];

        p[k] = v > 0.0001f ? v : 0.0001f;
    }
}

/* 0x001943F0, 0x58 bytes, matching. The four corners of grid cell (x, z). */
void func_001943F0(u8 **out, int x, int z)
{
    u8 *c = SPP(0x7F0) + (x + (GRID_W + 1) * z) * 0x14;

    out[0] = c;
    c = c + 0x14;
    out[1] = c;
    c = c + GRID_W * 0x14;
    out[2] = c;
    out[3] = c + 0x14;
}

/* 0x00194450, 0x2C bytes, matching. Grid corner (x, z). */
u8 *func_00194450(int x, int z)
{
    return SPP(0x7F0) + (x + (GRID_W + 1) * z) * 0x14;
}

/* 0x00194480, 0xA4 bytes. Layer `k`'s cell at grid cell (x, z) (0 off it or without ground). */
u8 *func_00194480(int k, int x, int z)
{
    u8 *c;

    x = x - *(u8 *)SPAD(0x842 + k * 2);
    z = z - *(u8 *)SPAD(0x843 + k * 2);
    if (x < 0 || z < 0 || x > 0x31 || z > 0x31)
        return 0;
    c = SPP(0x7F4 + k * 4) + (x + z * 0x32) * 0xC;
    if ((c[7] & 3) == 0)
        return 0;
    return c;
}

/* 0x00194530, 0x24 bytes, matching. The current bank's entry for the frame parity (+0x7E0). */
u32 func_00194530(void)
{
    return *(u32 *)(SPAD(0x7E0) + SP32(0x88C) * 8 + SP32(0x150) * 4);
}

/* 0x00194560, 0xC bytes, matching. */
u32 func_00194560(void)
{
    return SP32(0x808);
}

/* 0x00194570, 0xC bytes, matching. */
u32 func_00194570(void)
{
    return SP32(0x80C);
}

/* 0x00194580, 0xC bytes, matching. */
u32 func_00194580(void)
{
    return SP32(0x810);
}

/* 0x00194590, 0x20 bytes, matching. The value of grid corner (x, z). */
u32 func_00194590(int x, int z)
{
    return *(u32 *)func_00194450(x, z);
}

/* 0x001945B0, 0x30 bytes, matching. The value of layer `k`'s cell (0 for none). */
u32 func_001945B0(int k, int x, int z)
{
    u8 *c = func_00194480(k, x, z);

    if (c == 0)
        return 0;
    return *(u32 *)c;
}

/* 0x001945E0, 0xB4 bytes. The value at cell (x, z) of layer `k` (the ground grid without
 * layers or for layer 0, except in game mode 2). */
u32 func_001945E0(int k, int x, int z)
{
    if ((func_001934D0() == 0 || k == 0) && g_00669DB8[0] != 2) {
        if (func_001942E0(x, z) == 0)
            return 0;
        return func_00194590(x, z);
    }
    return func_001945B0(k, x, z);
}

/* 0x001946A0, 0x118 bytes. The value under 3D point `p` if its cell has one of `flags` (the
 * ground grid's +0x13 or the layer's +0xB). */
u32 func_001946A0(float *p, u8 flags)
{
    int x = (int)(p[0] * 0.002f), z = (int)(p[2] * 0.002f), k;
    u8 *c;

    if (func_001942E0(x, z) == 0)
        return 0;
    if (func_001934D0() == 0 || (k = func_00193620(p)) < 1) {
        c = func_00194450(x, z);
        if ((c[0x13] & flags) == 0)
            return 0;
        return *(u32 *)c;
    }
    c = func_00194480(k, x, z);
    if (c == 0)
        return 0;
    if ((c[0xB] & flags) == 0)
        return 0;
    return *(u32 *)c;
}

/* 0x001947C0, 0x78 bytes, matching. Marks grid corner (x, z) with `flags` (+0x13), flag 0x40 of +0xE
 * with `f`, its value `v` (when not 0); its kind (+0xC). */
u8 func_001947C0(int x, int z, u32 v, u8 flags, int f)
{
    u8 *c = func_00194450(x, z);

    c[0x13] |= flags;
    if (f != 0)
        ((struct { u8 a : 6; u8 b : 1; } *)(c + 0xE))->b = 1;
    if (v != 0)
        *(u32 *)c = v;
    return c[0xC] & 0x7F;
}

/* 0x00194840, 0x5C bytes, matching. The same for layer `k`'s cell (+0xB, kind +6); 9 for none. */
u8 func_00194840(int k, int x, int z, u32 v, u8 flags)
{
    u8 *c = func_00194480(k, x, z);

    if (c == 0)
        return 9;
    c[0xB] |= flags;
    if (v != 0)
        *(u32 *)c = v;
    return c[6] & 0x7F;
}

/* 0x001948A0, 0xA8 bytes. Bits 2-4 of the cell's height byte (+0xD on the grid, +7 on a
 * layer). */
u32 func_001948A0(int k, int x, int z)
{
    if ((func_001934D0() == 0 || k == 0) && g_00669DB8[0] != 2)
        return (func_00194450(x, z)[0xD] & 0x1F) >> 2;
    {
        u8 *c = func_00194480(k, x, z);

        if (c == 0)
            return 0;
        return (c[7] & 0x1F) >> 2;
    }
}

/* 0x00194950, 0x3C bytes. Grid corner (x, z)'s direction (+0xE, 8 without flag 0x20). */
u32 func_00194950(int x, int z)
{
    u8 *c = func_00194450(x, z);

    if (((struct { u8 a : 5; u8 b : 1; } *)(c + 0xE))->b)
        return c[0xE] & 7;
    return 8;
}

/* 0x00194990, 0x24 bytes, matching. Grid corner (x, z)'s kind. */
u8 func_00194990(int x, int z)
{
    return func_00194450(x, z)[0xC] & 0x7F;
}

void func_00191240(u32 k);
void func_002011B0(void);
void func_00200CE0(int a);
void func_002003D0(void);
void func_002013E0(void);
void func_00201030(void);
void func_00201470(void);
void func_00200EF0(void);
void func_00200AB0(void);
void func_001949C0(void);


/* The larger / smaller of two ints. */
#define IMAX(a, b) ((int)(a) < (int)(b) ? (int)(b) : (int)(a))
#define IMIN(a, b) ((int)(b) < (int)(a) ? (int)(b) : (int)(a))

/* 0x00194B30, 0x1D8 bytes. Marks in the row bits `rows` (one u32 per row of rectangle `r`) the
 * 2 x 2 cells around the camera's eye and the 2 x 2 cells about three cells ahead of it (along
 * its view +0x1E0), kept inside the rectangle. */
void func_00194B30(u8 *cam, u8 *r, u32 *rows)
{
    int x0 = r[0], z0 = r[1];
    int ex = (int)(*(float *)(cam + 0x1C0) * 0.002f - 0.5f);
    int ez = (int)(*(float *)(cam + 0x1C8) * 0.002f - 0.5f);
    int ax, az;
    u32 m1, m2, *p1, *p2;

    ex = IMAX(x0, ex);
    ez = IMAX(z0, ez);
    ex = IMIN(ex, r[2] - 2);
    ez = IMIN(ez, r[3] - 2);
    ax = ex + (int)(*(float *)(cam + 0x1E0) * 2.9f);
    az = ez + (int)(*(float *)(cam + 0x1E8) * 2.9f);
    ax = IMAX(x0, ax);
    az = IMAX(z0, az);
    ax = IMIN(ax, r[2] - 2);
    az = IMIN(az, r[3] - 2);
    p1 = rows + (ez - z0);
    p2 = rows + (az - z0);
    m1 = 3 << (ex - x0);
    m2 = 3 << (ax - x0);
    p1[0] |= m1;
    p1[1] |= m1;
    p2[0] |= m1;
    p2[1] |= m1;
    p1[0] |= m2;
    p1[1] |= m2;
    p2[0] |= m2;
    p2[1] |= m2;
}

/* 0x00195C20, 0x3C bytes, matching. Draws layer 5 of the stage. */
void func_00195C20(void)
{
    func_00191240(5);
    func_002011B0();
    func_00200CE0(1);
    func_002003D0();
    func_002013E0();
}

/* 0x00195C60, 0x74 bytes. Draws the stage's extra pass (flag 0x80 of the bank's layer bits),
 * not for layers 2, 3 and 4. */
void func_00195C60(void)
{
    if ((*(u8 *)SPAD(0xB98 + SP32(0x88C)) & 0x80) && (0xC >> (SP32(0x888) & 0x1F) & 1) == 0
        && SP32(0x888) != 4) {
        func_00201030();
        func_00200CE0(0);
        func_002003D0();
        func_00201470();
    }
}

/* 0x00195CE0, 0x38 bytes, matching. Draws the stage's ground. */
void func_00195CE0(void)
{
    SP32(0x768) = 0;
    func_00200EF0();
    func_00200AB0();
    func_001949C0();
    func_002013E0();
}

/* 0x00195D20, 0x84 bytes. Frees the stage's two pairs of buffers (+0x7E0). */
void func_00195D20(void)
{
    int k;

    for (k = 0; k < 2; k++) {
        if (SPP(0x7E0 + k * 8) != 0) {
            func_00102EC0(SPP(0x7E0 + k * 8));
            SPP(0x7E0 + k * 8) = 0;
        }
        if (SPP(0x7E4 + k * 8) != 0) {
            func_00102EC0(SPP(0x7E4 + k * 8));
            SPP(0x7E4 + k * 8) = 0;
        }
    }
}

/* 0x00195DB0, 0x8 bytes, matching. Nothing. */
void func_00195DB0(void)
{
}

/* 0x00195DC0, 0x68 bytes. Fills `n` 0x70-byte records with the template at +0x770. */
void func_00195DC0(u8 *p, u32 n)
{
    u32 k;

    for (k = 0; k < n; k++, p += 0x70)
        func_00118AC0(p, SPAD(0x770), 0x70);
}

/* 0x00195E30, 0xBC bytes. The draw slot of layer `k` (2-5: 1-4, with `alt` 5-8; 0 / 9 for the
 * others). */
int func_00195E30(int k, int alt)
{
    if (alt == 0) {
        if (k == 5)
            return 4;
        if (k == 4)
            return 3;
        if (k == 3)
            return 2;
        if (k == 2)
            return 1;
        return 0;
    }
    if (k == 5)
        return 8;
    if (k == 4)
        return 7;
    if (k == 3)
        return 6;
    if (k == 2)
        return 5;
    return 9;
}

/* The stage's objects (0x005D25E0): +0 their count, +4 their ids (u16), +8 their points (16
 * bytes), +0xC words, +0x10 bytes; +0x18 / +0x1C / +0x20 / +0x24 / +0x28 counters, +0x2C a flag;
 * +0x30 two banks of 10 light matrices (0x280 bytes each) and +0x530 their colour matrices; +0xA30
 * four slots; +0xAD0 per bank the squared draw distances (3); +0xAE8 / +0xAEC the object followed. */
extern u32 g_005D25E0;
extern u16 *g_005D25E4;
extern u8 *g_005D25E8;
extern u32 *g_005D25EC;
extern u8 *g_005D25F0;
extern u32 g_005D25F8, g_005D25FC, g_005D2600, g_005D2604, g_005D2608, g_005D260C;
extern u8 g_005D2610[2][0x280];          /* the light matrices per bank */
extern u8 g_005D2B10[2][0x280];          /* the colour matrices per bank */
extern u32 g_005D3010[4];
extern float g_005D30B0[2][3];
extern u32 g_005D30C8;
extern u8 *g_005D30CC;
extern u8 *g_0045D460;                   /* (small data) the light set */


void func_00195DC0(u8 *p, u32 n);
void func_00107440(u32 a, int b, int c);
void func_001F6CA0(u8 a, u16 id, u8 *p, u32 w);
void func_00143268(void *m, void *a, void *b, void *c);
void func_00143328(void *m, void *a, void *b, void *c, void *d);

/* 0x00196530, 0x8 bytes, matching. Nothing. */
void func_00196530(void)
{
}

/* 0x00196540, 0x174 bytes. Opens the stage file's header (`h`, copied to +0x770): the ground
 * grid (+0x80), the layers' grids (+0x84-+0x94, with layers), three more tables
 * (+0x98-+0xA0), the stage's bounds, and two pairs of 0x34F-record buffers. Returns the number
 * of layers. */
u32 func_00196540(u8 *h)
{
    int k;

    func_00118AC0(SPAD(0x770), h, 0x100);
    SPP(0x7F0) = h + *(int *)(h + 0x80);
    if (SP32(0x84C) != 0) {
        for (k = 0; k < 5; k++)
            SPP(0x7F4 + k * 4) = h + *(int *)(h + 0x84 + k * 4);
    }
    SPP(0x808) = h + *(int *)(h + 0x98);
    SPP(0x80C) = h + *(int *)(h + 0x9C);
    SPP(0x810) = h + *(int *)(h + 0xA0);
    SPF(0x830) = (float)(int)(GRID_W - 1) + 0.0001f;
    SPF(0x838) = (float)(int)(GRID_H - 1) + 0.0001f;
    SPF(0x834) = SPF(0x830);
    SPF(0x83C) = SPF(0x838);
    for (k = 0; k < 2; k++) {
        u8 *b = func_00102D30(0x17290);

        SPP(0x7E0 + k * 8) = b;
        func_00195DC0(b, 0x34F);
        b = func_00102D30(0x17290);
        SPP(0x7E4 + k * 8) = b;
        func_00195DC0(b, 0x34F);
    }
    return SP32(0x84C);
}

/* Makes a list's offsets (count +0x38, table +0x3C of 16-byte entries) into addresses; entries
 * of kind 0x18000 (+8) get flag +0x10. */
static inline void open_list(u8 *l)
{
    u32 *e = (u32 *)(l + *(int *)(l + 0x3C) * 0x10), k;

    *(u32 **)(l + 0x3C) = e;
    for (k = 0; k < *(u32 *)(l + 0x38); k++, e += 4) {
        u8 *o = l + e[0] * 0x10;

        e[0] = (u32)o;
        if ((*(u32 *)(o + 8) & 0x38000) == 0x18000)
            *(u32 *)(o + 0x10) = 1;
    }
}

/* 0x001966C0, 0x114 bytes. Opens the stage's two object lists and keeps them (+0x814, +0x818)
 * with `c` (+0x81C). */
void func_001966C0(u8 *a, u8 *b, u32 c)
{
    open_list(a);
    open_list(b);
    SP32(0x81C) = c;
    SPP(0x814) = a;
    SPP(0x818) = b;
    func_00107440(c, 0x1320, 0x3ED8);
}

/* 0x001967E0, 0x64 bytes. The eight corners of the box from `b[0]` (min) to `b[1]` (max). */
void func_001967E0(float *out, float *b)
{
    int k;

    for (k = 0; k < 8; k++) {
        out[k * 4 + 0] = (k & 1) ? b[4] : b[0];
        out[k * 4 + 1] = (k & 2) ? b[5] : b[1];
        out[k * 4 + 2] = (k & 4) ? b[6] : b[2];
        out[k * 4 + 3] = b[3];
    }
}

/* 0x00196850, 0xA8 bytes. The box `b` turned by `m`: the min and max of its eight corners. */
void func_00196850(float *out, float *m, float *b)
{
    float c[8][4];
    int i, k;

    func_001967E0(c[0], b);
    for (i = 0; i < 8; i++) {
        float v[4];

        for (k = 0; k < 4; k++)
            v[k] = m[k] * c[i][0] + m[4 + k] * c[i][1] + m[8 + k] * c[i][2] + m[12 + k] * c[i][3];
        for (k = 0; k < 4; k++) {
            if (i == 0 || v[k] < out[k])
                out[k] = v[k];
            if (i == 0 || out[4 + k] < v[k])
                out[4 + k] = v[k];
        }
    }
}

/* 0x00196900, 0x18 bytes. Object `i`'s id. */
u16 func_00196900(int i)
{
    return g_005D25E4[i];
}

/* 0x00196920, 0x14 bytes. Object `i`'s point. */
u8 *func_00196920(int i)
{
    return g_005D25E8 + i * 0x10;
}

/* 0x00196940, 0x18 bytes. Object `i`'s word. */
u32 func_00196940(int i)
{
    return g_005D25EC[i];
}

/* 0x00196960, 0x14 bytes. Object `i`'s byte. */
u8 func_00196960(int i)
{
    return g_005D25F0[i];
}

/* 0x00196980, 0x84 bytes. Places every stage object (func_001F6CA0). */
void func_00196980(void)
{
    u32 k;

    for (k = 0; k < g_005D25E0; k++) {
        u16 id = func_00196900(k);
        u8 *p = func_00196920(k);
        u32 w = func_00196940(k);

        func_001F6CA0(func_00196960(k), id, p, w);
    }
}

/* 0x00196A10, 0xC bytes. */
u32 func_00196A10(void)
{
    return g_005D2600;
}

/* 0x00196A20, 0x18 bytes. */
void func_00196A20(void)
{
    g_005D2600 = g_005D2600 + 1;
}

/* 0x00196A40, 0xC bytes. */
u32 func_00196A40(void)
{
    return g_005D2604;
}

/* 0x00196A50, 0x44 bytes. Counts one (+0x24, or +0x18 with the flag). */
void func_00196A50(void)
{
    if (g_005D260C == 0)
        g_005D2604 = g_005D2604 + 1;
    else
        g_005D25F8 = g_005D25F8 + 1;
}

/* 0x00196AA0, 0xC bytes. */
u32 func_00196AA0(void)
{
    return g_005D2608;
}

/* 0x00196AB0, 0x44 bytes. Counts one (+0x28, or +0x1C with the flag). */
void func_00196AB0(void)
{
    if (g_005D260C == 0)
        g_005D2608 = g_005D2608 + 1;
    else
        g_005D25FC = g_005D25FC + 1;
}

/* 0x00196B00, 0xC bytes. The flag. */
u32 func_00196B00(void)
{
    return g_005D260C;
}

/* 0x00196B10, 0x134 bytes. Bank `bank`'s ten light matrices and colour matrices from the ten
 * lights (func_002184D0). */
void func_00196B10(int bank)
{
    u8 *m = g_005D2610[bank], *c = g_005D2B10[bank];
    int k;

    for (k = 0; k < 10; k++, m += 0x40, c += 0x40) {
        float nl[4][4], cl[4][4];
        u32 *l1 = func_002184D0(1, k), *l2;
        int i, j;

        func_00143268(nl, g_0045D460 + 0x10, (void *)0x700000C0, (void *)0x700000C0);
        l2 = func_002184D0(2, k);
        func_00143328(cl, l2, (void *)0x700000C0, (void *)0x700000C0, l1);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                ((float *)m)[i * 4 + j] = cl[0][j] * nl[i][0] + cl[1][j] * nl[i][1]
                                          + cl[2][j] * nl[i][2] + cl[3][j] * nl[i][3];
        func_00143328(c, (void *)0x700000C0, (void *)0x700000C0, (void *)0x700000C0, l1);
    }
}

/* 0x00196C50, 0x28 bytes. The current bank's colour matrices. */
u8 *func_00196C50(void)
{
    return g_005D2B10[SP32(0x88C)];
}

/* 0x00196C80, 0x28 bytes. The current bank's light matrices. */
u8 *func_00196C80(void)
{
    return g_005D2610[SP32(0x88C)];
}

/* 0x00196CB0, 0x90 bytes. Layer `layer`'s squared draw distances from `r`: r², 1% of it and 4
 * times it (layers 2 and 3: 1e6 and 4e8). */
void func_00196CB0(float r, u32 layer)
{
    float *d = g_005D30B0[0x18 >> (layer & 0x1F) & 1];

    r = r * r;
    d[0] = r;
    if ((0xC >> (layer & 0x1F) & 1) == 0) {
        d[1] = r * 0.01f;
        d[2] = r * 4.0f;
    } else {
        d[1] = 1000000.0f;
        d[2] = 400000000.0f;
    }
}

/* 0x00196D40, 0x30 bytes, matching. Squared draw distance `i` of the current bank. */
float func_00196D40(int i)
{
    return g_005D30B0[SP32(0x88C)][i];
}

/* 0x00196D70, 0x50 bytes. Puts `x` in the first free of the four slots. Whether there was one. */
int func_00196D70(u32 x)
{
    u32 k;

    for (k = 0; k < 4; k++) {
        if (g_005D3010[k] == 0) {
            g_005D3010[k] = x;
            return 1;
        }
    }
    return 0;
}

/* 0x00196DC0, 0x50 bytes. Frees the slot holding `x`. */
int func_00196DC0(u32 x)
{
    u32 k;

    for (k = 0; k < 4; k++) {
        if (x == g_005D3010[k]) {
            g_005D3010[k] = 0;
            return 1;
        }
    }
    return 0;
}

/* 0x00196E10, 0x68 bytes. Follows the last model (of the list at the scratchpad's +0x1D0) of
 * kind above 0xC with `x`. */
void func_00196E10(u32 x)
{
    u32 n = func_00196A10(), k;
    u8 *m = SPP(0x1D0);

    for (k = 0; k < n; k++, m += 0x70) {
        if (m[0x68] > 0xC) {
            g_005D30C8 = x;
            g_005D30CC = m;
        }
    }
}

/* 0x00196E80, 0x14 bytes. Stops following. */
void func_00196E80(void)
{
    g_005D30C8 = 0;
    g_005D30CC = 0;
}

extern u8 *g_005D3020[4];                /* four stage parts drawn */
extern u8 *g_005D3030[0x20];             /* 32 animated stage parts */
extern u32 g_005D25F4;
extern void (*g_00412490[])(float k, u8 *m);   /* model updates by kind (+0x68) */
extern u8 g_00574DE0[][0x630];           /* the units */

void func_001F4FB0(u32 i, u32 bank);
void func_001FBE60(float k, u8 *m);
void func_001FF8F0(u8 *m);
void func_0020FFB0(u8 *a);
void func_00247410(void);
void func_002474A0(void);
int func_001FF160(u16 id);
void func_001F70A0(u32 a, u32 b, u32 c);
void func_001F6FF0(void);
void func_001FF0C0(void);
void func_00247970(void);
void func_0027F430(void);
void func_001FFF00(void);
void func_002080E0(void);
void func_001FFF10(u32 a, u32 b);
void func_00208140(u32 a, u32 b);
void func_0027F5D0(void);
void func_002479C0(void);
void func_001FF0D0(void);
void func_00197300(u32 *f);
void func_001972F0(void);

/* 0x00196EA0, 0x16C bytes. Updates the four slotted models (those of a unit with flag 8 of
 * +0x198 in its own way, the others by their kind), or (battle flag 0x100000) the followed one. */
void func_00196EA0(void)
{
    u32 k;

    if (g_00669F60[0] & 0x100000) {
        if (g_005D30C8 != 0)
            func_001FF8F0(g_005D30CC);
        return;
    }
    for (k = 0; k < 4; k++) {
        u8 *m = (u8 *)g_005D3010[k];

        if (m == 0)
            continue;
        if (m[0x6B] < 0x8F && (g_00574DE0[m[0x6B]][0x198] & 8)) {
            func_001F4FB0((u32)((m - SPP(0x1D0)) / 0x70) / 0x70, SP32(0x88C));
            func_001FBE60(0.15f, m);
        } else {
            g_00412490[m[0x68]](1.0f, m);
        }
    }
}

/* 0x00197010, 0x40 bytes. Puts `p` in every free slot of the four drawn parts (as in the
 * original: it does not stop at the first). */
void func_00197010(u8 *p)
{
    int k;

    for (k = 0; k < 4; k++) {
        if (g_005D3020[k] == 0)
            g_005D3020[k] = p;
    }
}

/* 0x00197050, 0x30 bytes, matching. Drawn part `k`'s +0x40 (0 for none). */
u8 *func_00197050(int k)
{
    u8 *p = g_005D3020[k];

    if (p == 0)
        return 0;
    return p + 0x40;
}

/* 0x00197080, 0x40 bytes. Puts `p` in every free slot of the 32 animated parts. */
void func_00197080(u8 *p)
{
    int k;

    for (k = 0; k < 0x20; k++) {
        if (g_005D3030[k] == 0)
            g_005D3030[k] = p;
    }
}

/* 0x001970C0, 0x6C bytes. Animates the animated parts (those of state 0 in +0x69) up to the
 * first empty slot. */
void func_001970C0(void)
{
    int k;

    for (k = 0; k < 0x20; k++) {
        u8 *p = g_005D3030[k];

        if (p == 0)
            return;
        if ((p[0x69] & 7) == 0)
            func_0020FFB0(p + 0x40);
    }
}

/* 0x00197130, 0x100 bytes. Saves the stage models' states (+0x69, a byte each, 0x2800 in all);
 * returns the end. */
u8 *func_00197130(u8 *p)
{
    u32 n = func_00196A10(), k;
    u8 *m = SPP(0x1D0);

    func_00247410();
    for (k = 0; k < n; k++, m += 0x70)
        *p++ = m[0x69];
    for (; k < 0x2800; k++)
        *p++ = 0;
    func_002474A0();
    return p;
}

/* 0x00197230, 0xB4 bytes. Restores them (not for models func_001FF160 keeps); returns the
 * end. */
u8 *func_00197230(u8 *p)
{
    u32 n = func_00196A10(), k;
    u8 *m = SPP(0x1D0);

    for (k = 0; k < n; k++, m += 0x70, p++) {
        if (func_001FF160(*(u16 *)(m + 0x54)) == 0)
            m[0x69] = *p;
    }
    for (; k < 0x2800; k++)
        p++;
    return p;
}

/* 0x001972F0, 0x8 bytes, matching. Nothing. */
void func_001972F0(void)
{
}

/* 0x00197300, 0x114 bytes. Opens the stage objects' file (its offsets made into addresses):
 * count, ids, points, words, bytes; places them (counting as the flag says) and sets up the
 * model pools (mode 2: fixed sizes). */
void func_00197300(u32 *f)
{
    u32 k;

    func_00118850(&g_005D25E0, 0xAF0);
    for (k = 0; k < f[0]; k++)
        f[1 + k] = f[1 + k] + (u32)f;
    g_005D25E0 = *(u32 *)f[1];
    g_005D25E4 = (u16 *)f[2];
    g_005D25E8 = (u8 *)f[3];
    g_005D25EC = (u32 *)f[4];
    g_005D25F0 = (u8 *)f[5];
    g_005D25F4 = g_005D25E0;
    if (g_00669DB8[0] == 2) {
        g_005D25F8 = 40000;
        g_005D25FC = 5000;
        func_001F70A0(0x4B0, g_005D25F8, g_005D25FC);
    } else {
        g_005D260C = 1;
        func_00196980();
        g_005D260C = 0;
        func_001F70A0(g_005D25F4, g_005D25F8, g_005D25FC);
    }
}

/* 0x00197420, 0x4C bytes, matching. Shuts the stage's model parts down. */
void func_00197420(void)
{
    func_001F6FF0();
    func_001FF0C0();
    func_00247970();
    func_0027F430();
    func_001972F0();
    func_001FFF00();
    func_002080E0();
}

/* 0x00197470, 0x9C bytes, matching. Opens the second stage file (its offsets made into addresses): two
 * pairs of tables, the objects (not in mode 2), the rest. */
void func_00197470(u8 *file)
{
    u32 *f = (u32 *)file, k;

    for (k = 0; k < f[0]; k++)
        f[1 + k] = f[1 + k] + (u32)f;
    func_001FFF10(f[1], f[3]);
    func_00208140(f[2], f[4]);
    if (g_00669DB8[0] != 2)
        func_00197300((u32 *)f[5]);
    func_0027F5D0();
    func_002479C0();
    func_001FF0D0();
}
