/*
 * model_manager.c - the battle's models (original source file ModelManager.c: its name is
 * passed to the file loader at 0x001BC8C0 and 0x001BD180...). Complete: 0x001BC8C0-0x001BEAA8.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Character slots: 0x40 of 0x150 bytes at 0x006CDF50 (+0 the loaded file, +4 set up, +0x10 the
 * skeleton, +0xB0 / +0xE0 two meshes, +0x110 a motion pack, +0x130 / +0x140 two more), described
 * by a 16-byte table at 0x00406C50 (LINKDATA entries, sizes, flags). Object slots: 0xD6 meshes of
 * 0x30 bytes at 0x006C3590, described by a table at 0x00407050, with their files at 0x006AAAE0
 * and their textures shared through slot lists (0x006AA9B0, 0x006AA630 in mode 2). Model actors
 * (0x220 bytes) and objects (0x170 bytes) come from fixed pools.
 */

#define SW2E_FILE_MODEL_MANAGER_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

/* A character slot's description (0x00406C50, 16 bytes). */
typedef struct {
    u16 entry, entry2;
    u32 size, size2;
    u16 kept;
    u8 motions, extra;
} ModelDesc;

/* An object's description (0x00407050, 16 bytes). */
typedef struct {
    int tex, mesh;
    int pad;
    u8 colour;
    u8 b[1];
    u16 kept;
} ObjectDesc;

/* A model's colour description (0x00407DB0, 12 bytes). */
typedef struct {
    u16 a, b;
    u8 c[7];
    u8 pad;
} ColourDesc;

/* A file and texture slot (0x10 bytes). */
typedef struct {
    u32 id;
    u32 pad;
    u64 tex;
} TexSlot;

extern ModelDesc g_00406C50[0x40];
extern ObjectDesc g_00407050[0xD6];
extern ColourDesc g_00407DB0[];
extern float g_00406740[10][4];          /* ten directions (none, then eight by 45 degrees) */
extern u8 g_006CDF50[0x40][0x150];
extern u8 g_006C3590[0xD6][0x30];
extern u8 *g_006AAAE0[0xD6][4];          /* per object: its texture file, id, mesh file, id */
extern TexSlot g_006AA9B0[0x12], g_006AA630[0x38];
extern int g_006AAAD0[4];                /* texture memory used (two banks), next CLUT */
extern u16 g_006AAADC, g_006AAADE;
extern u8 *g_0045D300;                   /* the slots' colours (0xA0 each) */
extern void *g_0045D308, *g_0045D310, *g_0045D318;
extern u8 g_006D2EC0[], g_006D2EF0[];
extern u32 g_00669DB8[4];
extern float g_0045CDA4, g_0045CDA8;
extern const char g_00425E70[];          /* "ModelManager.c" */
extern u8 g_00425E00[], g_00425E30[], g_00425E60[];

/* The actor pools (0x220 bytes) and object pools (0x170 bytes). */
extern u8 g_006CC5D0[0xC][0x220], g_006C6630[0x2D][0x220], g_006C5DB0[4][0x220];
extern u8 g_006AE040[2][0x220], g_006AFB80[0x18][0x220], g_006AB840[8][0x220];
extern u8 g_006B2E80[0xB7][0x170], g_006AC940[0x10][0x170], g_006AE480[0x10][0x170];

void vu0_sincos(float a, float *s, float *c);    /* VU0 micro subroutine 0x20 */

u16 func_001BE870(int k); u16 func_001BE890(int k); u32 func_001BE8B0(int k);
u32 func_001BE8D0(int k); u16 func_001BE8F0(int k); u8 func_001BE910(int k);
u8 func_001BE930(int k); ObjectDesc *func_001BE950(int k); u16 func_001BE970(int k);
int func_001BD180(int k, int alt, int a, int v);
int func_001BD2C0(int k);
int func_001BD5D0(int k);
int func_001BD9B0(int k, int a);
int func_001BDAE0(int k, int h, int bank);
void func_001BE0F0(int k);
void func_001BCF00(void);

/* Each pool's set-up and freeing (`k` numbers the actors). */
#define POOL_220(pool, n, f)  do { int i_; for (i_ = 0; i_ < (n); i_++) f(pool[i_]); } while (0)

/* 0x001BC8C0, 0x594 bytes. Sets the battle's models up: the slots' colours (LINKDATA 0x56A),
 * the ten directions, the shadow textures (0x570) and object textures (0x68E), clears every
 * slot, pool and texture list, and loads the kept slots and objects. */
void func_001BC8C0(void)
{
    u8 *f;
    int k;
    u8 n;

    func_00102680(1, 0x56A);
    g_0045D300 = func_001026D0(1, 0x56A, 0, 1, 0, 0, g_00425E70, 0xDC);
    g_00406740[0][0] = 0.0f;
    g_00406740[0][1] = 0.0f;
    g_00406740[0][2] = 0.0f;
    g_00406740[0][3] = 1.0f;
    for (k = 1; k < 10; k++) {
        float a = (float)k * 0.7853982f, s, c;

        if (a > 3.1415927f)
            a = a - 6.2831855f;
        else if (a <= -3.1415927f)
            a = a + 6.2831855f;
        vu0_sincos(a, &s, &c);
        g_00406740[k][0] = s * 1.5f;      /* (0, 0, 1.5, 1) turned by a) */
        g_00406740[k][1] = 0.0f;
        g_00406740[k][2] = c * 1.5f;
        g_00406740[k][3] = 1.0f;
    }
    f = func_001026D0(1, 0x570, 0, 1, 0, 0, g_00425E70, 0xF0);
    g_0045D310 = (void *)PS2_PTR(func_00107440(f, 0x2920, 0x3CE4));
    g_0045D318 = (void *)PS2_PTR(func_00107440(f, 0x2920, 0x3CE0));
    func_00102EC0(f);
    for (k = 0; k < 0x40; k++) {
        func_00147D20((unsigned int *)(g_006CDF50[k] + 0x10));
        func_00148130(g_006CDF50[k] + 0xB0);
        func_00148130(g_006CDF50[k] + 0xE0);
        func_001477C0(g_006CDF50[k] + 0x110);
        func_00147BB0(g_006CDF50[k] + 0x130);
        func_00147BB0(g_006CDF50[k] + 0x140);
    }
    for (k = 0; k < 0x40; k++) {
        if (func_001BE8F0(k) != 0) {
            func_001BD180(k, 0, 1, 0);
            func_001BD2C0(k);
        }
    }
    n = 0;
    for (k = 0; k < 0xC; k++, n++) {
        func_001486A0(g_006CC5D0[k]);
        g_006CC5D0[k][0x202] = n;
    }
    for (k = 0; k < 0x2D; k++, n++) {
        func_001486A0(g_006C6630[k]);
        g_006C6630[k][0x202] = n;
    }
    for (k = 0; k < 4; k++, n++) {
        func_001486A0(g_006C5DB0[k]);
        g_006C5DB0[k][0x202] = n;
    }
    for (k = 0; k < 2; k++, n++) {
        func_001486A0(g_006AE040[k]);
        g_006AE040[k][0x202] = n;
    }
    for (k = 0; k < 0xD6; k++)
        func_00148130(g_006C3590[k]);
    f = func_001026D0(1, 0x68E, 0, 1, 0, 0, g_00425E70, 0x12E);
    g_0045D308 = (void *)PS2_PTR(func_00107440(f, 0x2A20, 0x3ED0));
    func_00102EC0(f);
    func_001BC540();
    for (k = 0; k < 0xD6; k++) {
        if (func_001BE970(k) != 0) {
            func_001BD9B0(k, 1);
            func_001BDAE0(k, -1, 0);
        }
    }
    for (k = 0; k < 0xB7; k++) {
        func_0014F850(g_006B2E80[k]);
        g_006B2E80[k][0x166] = (u8)k;
    }
    for (k = 0; k < 0x18; k++) {
        func_001486A0(g_006AFB80[k]);
        g_006AFB80[k][0x202] = (u8)k;
    }
    for (k = 0; k < 0x10; k++) {
        func_0014F850(g_006AC940[k]);
        g_006AC940[k][0x166] = (u8)k;
    }
    for (k = 0; k < 8; k++) {
        func_001486A0(g_006AB840[k]);
        g_006AB840[k][0x202] = (u8)k;
    }
    for (k = 0; k < 0x10; k++) {
        func_0014F850(g_006AE480[k]);
        g_006AE480[k][0x166] = (u8)k;
    }
    func_001BC710();
    func_001BC690();
    func_001BC540();
    func_002AD4C0();
}

/* 0x001BCE60, 0x94 bytes. Frees every model, the kept ones too, and the colours. */
void func_001BCE60(void)
{
    int k;

    func_002AD610();
    func_001BCF00();
    for (k = 0; k < 0x40; k++) {
        if (func_001BE8F0(k) != 0)
            func_001BD5D0(k);
    }
    for (k = 0; k < 0xD6; k++) {
        if (func_001BE970(k) != 0)
            func_001BE0F0(k);
    }
    func_00102EC0(g_0045D300);
    g_0045D300 = 0;
}

/* Frees a pool's actors that hold a model (+0x1F8). */
#define FREE_ACTORS(pool, n) \
    do { int i_; for (i_ = 0; i_ < (n); i_++) if (*(u32 *)(pool[i_] + 0x1F8) != 0) func_001494F0(pool[i_]); } while (0)

/* 0x001BCF00, 0x250 bytes. Frees the models not kept between battles, the pools' models and
 * the texture lists. */
void func_001BCF00(void)
{
    int k;

    for (k = 0; k < 0x40; k++) {
        if (func_001BE8F0(k) == 0)
            func_001BD5D0(k);
    }
    FREE_ACTORS(g_006CC5D0, 0xC);
    FREE_ACTORS(g_006C6630, 0x2D);
    FREE_ACTORS(g_006C5DB0, 4);
    FREE_ACTORS(g_006AE040, 2);
    for (k = 0; k < 0xD6; k++) {
        if (func_001BE970(k) == 0)
            func_001BE0F0(k);
    }
    for (k = 0; k < 0xB7; k++)
        func_0014F950(g_006B2E80[k]);
    FREE_ACTORS(g_006AFB80, 0x18);
    for (k = 0; k < 0x10; k++)
        func_0014F950(g_006AC940[k]);
    FREE_ACTORS(g_006AB840, 8);
    for (k = 0; k < 0x10; k++)
        func_0014F950(g_006AE480[k]);
    if (g_00669DB8[0] == 2)
        func_001BC710();
    else
        func_001BC690();
    func_002AD690();
}

/* 0x001BD150, 0x28 bytes. Whether slot `k` has no model. */
int func_001BD150(int k)
{
    return (short)func_001BE870(k) == -1;
}

/* 0x001BD180, 0x13C bytes. Loads slot `k`'s file (its second one with `alt`, variant `v` 0 / 1)
 * when it is not loaded. */
int func_001BD180(int k, int alt, int a, int v)
{
    u32 *s = (u32 *)g_006CDF50[k];

    if (v > 1)
        v = 0;
    if (s[0] == 0 && s[1] == 0 && func_001BD150(k) == 0) {
        if (alt == 0)
            s[0] = (u32)func_001026D0(1, v + func_001BE870(k), 0, a, 0, 0, g_00425E70, 0x201);
        else
            s[0] = (u32)func_001026D0(1, v + func_001BE890(k), 0, a, 0, 0, g_00425E70, 0x1FD);
    }
    return 1;
}

/* Sets slot `slot` up from its loaded file with description `k`'s sizes and colours. */
static inline void setup_slot(int k, int slot, int mode2)
{
    u8 *s = g_006CDF50[slot];
    u32 *f = *(u32 **)s;
    u8 *col = g_0045D300 + k * 0xA0;
    u32 *p;

    if (mode2)
        func_00147D30((unsigned int *)((u8 *)f + (f[1] & ~3u)), s + 0x10, 0x25A0, func_001BE8D0(k));
    else
        func_00147D30((unsigned int *)((u8 *)f + (f[1] & ~3u)), s + 0x10, func_001BE8B0(k), func_001BE8D0(k));
    if (slot == 0x3C)
        func_001482F0((unsigned int *)((u8 *)f + (f[2] & ~3u)), g_006D2EC0, (u64)(u32)g_0045D318);
    else
        func_001482F0((unsigned int *)((u8 *)f + (f[2] & ~3u)), s + 0xB0, *(u64 *)(s + 0xA0));
    p = f + 3;
    func_00148420(s + 0xB0, col);
    if (f[0] == 6) {
        if (slot == 0x3C)
            func_001482F0((unsigned int *)((u8 *)f + (*p & ~3u)), g_006D2EF0, (u64)(u32)g_0045D318);
        else
            func_001482F0((unsigned int *)((u8 *)f + (*p & ~3u)), s + 0xE0, *(u64 *)(s + 0xA0));
        p = f + 4;
        func_001483F0(s + 0xE0, col[0x96], col[0x97], 0, 0, 0, 0);
    }
    if (func_001BE910(k) != 0) {
        func_001477E0((unsigned int *)((u8 *)f + (*p & ~3u)), (unsigned int *)(s + 0x110));
        p++;
    }
    if (func_001BE930(k) != 0) {
        func_00147BD0((u8 *)f + (p[0] & ~3u), (unsigned char **)(s + 0x130));
        func_00147BD0((u8 *)f + (p[1] & ~3u), (unsigned char **)(s + 0x140));
    }
    *(u32 *)(s + 4) = 1;
}

/* 0x001BD2C0, 0x27C bytes. Sets slot `k` up from its file: skeleton, meshes (slot 0x3C with the
 * shadow textures), a second mesh for 6-part files, motions, extras. */
int func_001BD2C0(int k)
{
    if (*(u32 *)(g_006CDF50[k] + 4) == 0 && func_001BD150(k) == 0)
        setup_slot(k, k, g_00669DB8[0] == 2);
    return 1;
}

/* 0x001BD540, 0x84 bytes. Frees the loaded files of slots not set up nor kept. */
void func_001BD540(void)
{
    int k;

    for (k = 0; k < 0x40; k++) {
        u32 *s = (u32 *)g_006CDF50[k];

        if (func_001BE8F0(k) == 0 && s[1] == 0 && s[0] != 0) {
            func_00102EC0((void *)s[0]);
            s[0] = 0;
        }
    }
}

/* 0x001BD5D0, 0x100 bytes. Frees slot `k`'s parts and file. */
int func_001BD5D0(int k)
{
    u8 *s = g_006CDF50[k];

    if (*(u32 *)(s + 4) != 0 && func_001BD150(k) == 0) {
        if (*(u32 *)(s + 0x10) != 0)
            func_00147D20((unsigned int *)(s + 0x10));
        if (*(u32 *)(s + 0xB8) != 0)
            func_001483B0(s + 0xB0);
        if (*(u32 *)(s + 0xE8) != 0)
            func_001483B0(s + 0xE0);
        if (*(u32 *)(s + 0x110) != 0)
            func_001477C0(s + 0x110);
        if (*(u32 *)(s + 0x130) != 0)
            func_00147BB0(s + 0x130);
        if (*(u32 *)(s + 0x140) != 0)
            func_00147BB0(s + 0x140);
        func_00102EC0(*(void **)s);
        *(u32 *)s = 0;
        *(u32 *)(s + 4) = 0;
    }
    return 1;
}

/* 0x001BD6D0, 0x120 bytes. Loads slot `k`'s two variants into slots `k` and `k` + 1 (only the
 * first for slots past 0x1B). */
int func_001BD6D0(int k, int a)
{
    u32 *s = (u32 *)g_006CDF50[k];
    int v;

    if (s[0] == 0 && s[1] == 0 && func_001BD150(k) == 0) {
        for (v = 0; v < 2; v++) {
            s[v * 0x54] = (u32)func_001026D0(1, v + func_001BE870(k), 0, a, 0, 0, g_00425E70, 0x2B4);
            if (k > 0x1B)
                return 1;
        }
    }
    return 1;
}

/* 0x001BD7F0, 0x1C0 bytes. Sets slot `k` + `v` up from its file with slot `k`'s description. */
int func_001BD7F0(int k, int v)
{
    if (func_001BD150(k) == 0)
        setup_slot(k, k + v, 0);
    return 1;
}

/* 0x001BD9B0, 0x12C bytes. Loads object `k`'s texture file (unless already shared) and mesh
 * file. */
int func_001BD9B0(int k, int a)
{
    u8 **f = g_006AAAE0[k];

    if (f[2] == 0 && *(u32 *)(g_006C3590[k] + 8) == 0) {
        ObjectDesc *d = func_001BE950(k);

        if (d->tex != 0xFFFF && func_001BC650(d->tex) == 0) {
            func_00103000(0);
            f[0] = func_001026D0(1, d->tex, 0, a, 0, 0, g_00425E70, 0x396);
            f[1] = (u8 *)d->tex;
            func_00103000(1);
        }
        f[2] = func_001026D0(1, d->mesh, 0, a, 0, 0, g_00425E70, 0x39F);
        f[3] = (u8 *)d->mesh;
    }
    return 1;
}

/* Uploads object `k`'s texture into texture slot list entry `e` (bank memory at `tbp`, CLUT
 * at `cbp`), counting the memory it takes. */
static inline u64 upload_object(int k, TexSlot *e, ObjectDesc *d, int *used, int tbp, int cbp)
{
    u8 **f = g_006AAAE0[k], *img = f[0];
    u64 t = func_00107420(img, 0, 0, *(u16 *)(img + 0x24), *(u16 *)(img + 0x26), tbp / 0x100,
                          cbp / 0x100);
    u16 h = *(u16 *)(img + 0x26);
    int n;

    if (h < 0x40) {
        if (g_006AAADC == 1) {
            g_006AAADC = 0;
            n = *(u16 *)(img + 0x24) * 0x60;
        } else {
            n = *(u16 *)(img + 0x24) * h / 2;
            g_006AAADC++;
        }
    } else {
        n = *(u16 *)(img + 0x24) * h;
    }
    *used += n;
    g_006AAAD0[2] += 0x400;
    func_00103000(0);
    func_00102EC0(img);
    f[0] = 0;
    func_00103000(1);
    e->id = d->tex;
    e->tex = t;
    g_006AAADE++;
    return t;
}

/* 0x001BDAE0, 0x2C4 bytes. Sets object `k` up: its texture uploaded into bank `bank` (or the
 * shared one; height `h` when given must match), its mesh opened with it and coloured. */
int func_001BDAE0(int k, int h, int bank)
{
    u64 t = (u64)(u32)g_0045D308;
    ObjectDesc *d;
    u8 **f = g_006AAAE0[k];

    if (*(u32 *)(g_006C3590[k] + 8) != 0)
        return 1;
    d = func_001BE950(k);
    if (d->tex != 0xFFFF) {
        TexSlot *e = func_001BC7A0(d->tex);

        if (e->id == 0xFFFF) {
            u8 *img = f[0];

            if (img == 0)
                return 1;
            if (h >= 0 && (h & 0xFFFF) != *(u16 *)(img + 0x26))
                return 1;
            if (g_00669DB8[0] == 4 && k == 0x6C)
                *(u16 *)(img + 0x26) = 0x40;
            t = upload_object(k, e, d, &g_006AAAD0[bank],
                              bank == 0 ? g_006AAAD0[0] + 0x2AA000 : g_006AAAD0[1] + 0x2C2000,
                              g_006AAAD0[2] + 0x2CA000);
        } else {
            t = e->tex;
        }
    }
    func_001482F0((unsigned int *)(f[2]), g_006C3590[k], t);
    f[2] = 0;
    func_001483F0(g_006C3590[k], 0, d->colour, 0, 0, 0, 0);
    return 1;
}

/* 0x001BDDB0, 0x27C bytes. The same for mode 2 (one bank, its own list). */
int func_001BDDB0(int k, int h)
{
    u64 t = (u64)(u32)g_0045D308;
    ObjectDesc *d;
    u8 **f = g_006AAAE0[k];

    if (*(u32 *)(g_006C3590[k] + 8) != 0)
        return 1;
    d = func_001BE950(k);
    if (d->tex != 0xFFFF) {
        TexSlot *e = func_001BC830(d->tex);

        if (e->id == 0xFFFF) {
            u8 *img = f[0];

            if (img == 0)
                return 1;
            if (h >= 0 && (h & 0xFFFF) != *(u16 *)(img + 0x26))
                return 1;
            if (k == 0x2C)
                g_006AAADC = 0;
            t = upload_object(k, e, d, &g_006AAAD0[0], g_006AAAD0[0] + 0x202000, g_006AAAD0[2] + 0x248000);
        } else {
            t = e->tex;
        }
    }
    func_001482F0((unsigned int *)(f[2]), g_006C3590[k], t);
    f[2] = 0;
    func_001483F0(g_006C3590[k], 0, d->colour, 0, 0, 0, 0);
    return 1;
}

/* 0x001BE030, 0xC bytes. */
void func_001BE030(void)
{
    g_006AAADC = 0;
}

/* 0x001BE040, 0xAC bytes. Frees the object files of objects not kept. */
void func_001BE040(void)
{
    int k;

    for (k = 0; k < 0xD6; k++) {
        u8 **f = g_006AAAE0[k];

        if (func_001BE970(k) != 0)
            continue;
        if (f[0] != 0) {
            func_00103000(0);
            func_00102EC0(f[0]);
            func_00103000(1);
            f[0] = 0;
            f[1] = (u8 *)0xFFFF;
        }
        if (f[2] != 0) {
            func_00102EC0(f[2]);
            f[2] = 0;
            f[3] = (u8 *)0xFFFF;
        }
    }
    func_001BC540();
}

/* 0x001BE0F0, 0xAC bytes. Frees object `k`'s mesh and its texture slot. */
void func_001BE0F0(int k)
{
    if (*(u32 *)(g_006C3590[k] + 8) != 0) {
        ObjectDesc *d = func_001BE950(k);

        if (d->tex != 0xFFFF) {
            TexSlot *e = g_00669DB8[0] == 2 ? func_001BC830(d->tex) : func_001BC7A0(d->tex);

            if (e != 0) {
                e->id = 0xFFFF;
                e->tex = 0;
            }
        }
        func_00148370(g_006C3590[k]);
    }
}

/* Resets a pool of actors with func_001492A0 and the default lights. */
#define RESET_ACTORS(pool, n, a, b) \
    do { int i_; for (i_ = 0; i_ < (n); i_++) { func_001492A0(pool[i_], 0, a, b); \
        func_00149590(pool[i_], g_00425E00, g_00425E30, g_00425E60); pool[i_][0x20C] &= 0xFE; } } while (0)

/* Resets a pool of objects. */
#define RESET_OBJECTS(pool, n) \
    do { int i_; for (i_ = 0; i_ < (n); i_++) { func_0014F8B0((unsigned int *)(pool[i_]), 0); pool[i_][0x168] &= 0xFE; } } while (0)

/* 0x001BE1A0, 0x348 bytes. Resets every pool (all free). */
void func_001BE1A0(void)
{
    int k;

    RESET_ACTORS(g_006CC5D0, 0xC, 0x67, 0x2E);
    for (k = 0; k < 0x2D; k++) {
        func_001493B0(g_006C6630[k], 0, 0, 0x4F, 0x2F, 0x2E);
        func_00149590(g_006C6630[k], g_00425E00, g_00425E30, g_00425E60);
        g_006C6630[k][0x20C] &= 0xFE;
    }
    for (k = 0; k < 4; k++) {
        func_001492A0(g_006C5DB0[k], 0, 10, 8);
        func_00148AB0(g_006C5DB0[k], 10);
        g_006C5DB0[k][0x20C] &= 0xFE;
    }
    RESET_ACTORS(g_006AE040, 2, 0x67, 0x2E);
    RESET_OBJECTS(g_006B2E80, 0xB7);
    RESET_ACTORS(g_006AFB80, 0x18, 0x14, 8);
    RESET_OBJECTS(g_006AC940, 0x10);
    RESET_ACTORS(g_006AB840, 8, 0x14, 8);
    RESET_OBJECTS(g_006AE480, 0x10);
}

/* The first free actor (bit 0 of +0x20C clear) or object (bit 0 of +0x168) of a pool. */
#define FIRST_FREE(pool, n, off) \
    do { int i_; for (i_ = 0; i_ < (n); i_++) if ((pool[i_][off] & 1) == 0) return pool[i_]; return 0; } while (0)

/* 0x001BE4F0, 0x44 bytes. */
u8 *func_001BE4F0(void) { FIRST_FREE(g_006CC5D0, 0xC, 0x20C); }

/* 0x001BE540, 0x44 bytes. */
u8 *func_001BE540(void) { FIRST_FREE(g_006C6630, 0x2D, 0x20C); }

/* 0x001BE590, 0x44 bytes. */
u8 *func_001BE590(void) { FIRST_FREE(g_006AE040, 2, 0x20C); }

/* 0x001BE5E0, 0x44 bytes. */
u8 *func_001BE5E0(void) { FIRST_FREE(g_006B2E80, 0xB7, 0x168); }

/* 0x001BE630, 0x44 bytes. */
u8 *func_001BE630(void) { FIRST_FREE(g_006AFB80, 0x18, 0x20C); }

/* 0x001BE680, 0x44 bytes. */
u8 *func_001BE680(void) { FIRST_FREE(g_006AC940, 0x10, 0x168); }

/* 0x001BE6D0, 0x44 bytes. */
u8 *func_001BE6D0(void) { FIRST_FREE(g_006AB840, 8, 0x20C); }

/* 0x001BE720, 0x44 bytes. */
u8 *func_001BE720(void) { FIRST_FREE(g_006AE480, 0x10, 0x168); }

/* 0x001BE770, 0x44 bytes. */
u8 *func_001BE770(void) { FIRST_FREE(g_006C5DB0, 4, 0x20C); }

/* 0x001BE7C0, 0xA8 bytes. A fog alpha for distance `d` with far plane `far` (0-255, 10% more
 * than linear). */
float func_001BE7C0(float d, float far)
{
    float a = (255.0f - g_0045CDA8 * 128.0f / (far - g_0045CDA4) * (d >= 0.0f ? d : 0.0f)) * 1.1f;

    if (a >= 255.0f)
        a = 255.0f;
    return a >= 0.0f ? a : 0.0f;
}

/* 0x001BE870, 0x18 bytes, matching. */
u16 func_001BE870(int k) { return g_00406C50[k].entry; }

/* 0x001BE890, 0x18 bytes, matching. */
u16 func_001BE890(int k) { return g_00406C50[k].entry2; }

/* 0x001BE8B0, 0x18 bytes, matching. */
u32 func_001BE8B0(int k) { return g_00406C50[k].size; }

/* 0x001BE8D0, 0x18 bytes, matching. */
u32 func_001BE8D0(int k) { return g_00406C50[k].size2; }

/* 0x001BE8F0, 0x18 bytes, matching. */
u16 func_001BE8F0(int k) { return g_00406C50[k].kept; }

/* 0x001BE910, 0x18 bytes, matching. */
u8 func_001BE910(int k) { return g_00406C50[k].motions; }

/* 0x001BE930, 0x18 bytes, matching. */
u8 func_001BE930(int k) { return g_00406C50[k].extra; }

/* 0x001BE950, 0x14 bytes, matching. */
ObjectDesc *func_001BE950(int k) { return &g_00407050[k]; }

/* 0x001BE970, 0x18 bytes, matching. */
u16 func_001BE970(int k) { return g_00407050[k].kept; }

/* 0x001BE990, 0x20 bytes, matching. */
u16 func_001BE990(int k) { return g_00407DB0[k].a; }

/* 0x001BE9B0, 0x20 bytes, matching. */
u16 func_001BE9B0(int k) { return g_00407DB0[k].b; }

/* 0x001BE9D0, 0x20 bytes, matching. */
u8 func_001BE9D0(int k) { return g_00407DB0[k].c[0]; }

/* 0x001BE9F0, 0x20 bytes, matching. */
u8 func_001BE9F0(int k) { return g_00407DB0[k].c[1]; }

/* 0x001BEA10, 0x20 bytes, matching. */
u8 func_001BEA10(int k) { return g_00407DB0[k].c[2]; }

/* 0x001BEA30, 0x20 bytes, matching. */
u8 func_001BEA30(int k) { return g_00407DB0[k].c[3]; }

/* 0x001BEA50, 0x20 bytes, matching. */
u8 func_001BEA50(int k) { return g_00407DB0[k].c[4]; }

/* 0x001BEA70, 0x20 bytes, matching. */
u8 func_001BEA70(int k) { return g_00407DB0[k].c[5]; }

/* 0x001BEA90, 0x20 bytes, matching. */
u8 func_001BEA90(int k) { return g_00407DB0[k].c[6]; }
