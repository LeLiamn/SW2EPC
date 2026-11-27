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
typedef unsigned int u32;

#define SPAD(off) ((u8 *)0x70000000 + (off))
#define SP32(off) (*(u32 *)SPAD(off))
#define SPF(off)  (*(float *)SPAD(off))
#define SPP(off)  (*(u8 **)SPAD(off))

extern u32 g_00669DB8[4];                /* (settings) +0: the game mode */
extern u32 g_00669F60[4];                /* (settings) +0: the battle flags */
extern int g_0045D2A8;                   /* (small data) slow motion */
extern float g_0045CC7C;                 /* (small data) the frame rate factor */

int func_00191330(u8 *r, u8 *c);
int func_001912E0(u8 *grid, int x, int z);
int func_0032E7B0(void);
u8 *func_00194480(int layer, int x, int z);
u32 *func_002184D0(int a, int i);
int func_00200110(void);
void func_001930D0(u32 layer, float *m);
void func_00196CB0(int a, u32 layer);
void func_00195920(u32 layer, float *m);
void func_00196B10(u32 bank);
void func_00245D60(void);
void func_001F5020(void);
void func_001970C0(void);
void func_001FC800(void);
void func_003BF820(void);
void func_0027E470(void);
void func_00247250(void);
void func_00197130(void);
void func_00197230(u8 *a);
u8 *func_002EFB00(int a);
void func_00102EC0(void *data);          /* free */
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

/* 0x001934D0, 0xC bytes. The number of height layers. */
u32 func_001934D0(void)
{
    return SP32(0x87C);
}

/* 0x001934E0, 0x14 bytes. The height of layer `i`. */
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
    int t = func_00200110();

    func_00193710(b, m);
    func_001930D0(layer, m);
    func_00196CB0(t, layer);
    func_00195920(layer, m);
    func_00193830(b);
    func_00196B10(b);
}

/* 0x00193940, 0x3C bytes. The stage's other parts each frame. */
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

/* 0x00193A50, 0x1C bytes. func_00197130. */
void func_00193A50(void)
{
    func_00197130();
}

/* 0x00193A70, 0x24 bytes. func_00197230 with func_002EFB00(5). */
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
