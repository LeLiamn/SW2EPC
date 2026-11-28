/*
 * model.c - motion curves, tm3 textures and 3D models (original source file unknown; 0x00147780-
 * 0x001508E4, after font.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * - Motion curves (docs/formats/MOTION.md): each track is a word (node in bits 0-7, component in
 *   bits 8-12, key size in bits 13-15, key count from bit 18) followed by its keys. A key size of
 *   0 means the value 0, 1 a constant, more a list of cubic segments (end time, a, b, c, d:
 *   v = a s^3 + b s^2 + c s + d). Components 3-5 are a node's translation; components 9-16 are
 *   the camera's (the "atypical" motions are camera motions).
 * - tm3 textures (docs/formats/TM3.md): GS upload packets, patched with the GS buffers given,
 *   then sent by DMA "ref" tags.
 * - Models (docs/formats/PS2MODEL.md): a file whose offsets are turned into pointers, its parts
 *   (VIF packets for VU1) patched with the texture's base, and sent with a VU1 header chosen by
 *   the part's kind.
 */

#define SW2E_FILE_MODEL_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
#include "sw2e_pc.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char s8;

float fabsf(float x);
float sqrtf(float x);

#define g_70000158 PS2_GETP(u32 *, 0x70000158)         /* the DMA chain's write cursor */
#define g_70000158_SET(v) PS2_SETP(0x70000158, v)

/* A motion being played (camera). */
/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

typedef struct {
    u32 *motion;             /* header: +4 tracks, +8 frames, +0xC the tracks */
} MotionState;

/* A tm3 texture once set up (0x9C bytes). */
typedef struct {
    u8 *file;
    u8 *data;                /* +4 file + 0x20: the picture's upload packet */
    u16 qwc;                 /* +8 */
    u16 frames;              /* +0xA palettes */
    short width;             /* +0xC */
    short height;
    u8 *palette[16];         /* +0x10 each palette's upload packet */
    u32 palette_qwc[16];     /* +0x50 */
    u64 tex0;                /* +0x90 */
    u8 a, b;                 /* +0x98 */
    u8 pad[2];
} Tm3;

/* A part of a model (16 bytes). */
typedef struct {
    u32 kind;
    u32 qwc;                 /* its VIF packets */
    u32 *data;
    u8 *header;              /* the VU1 header to send first (2 quadwords) */
} ModelPart;

/* A model (0x30 bytes). */
typedef struct {
    u64 tex0;                /* the texture (its base patched into the parts) */
    u32 *file;               /* +8 */
    ModelPart *parts;        /* +0xC */
    u32 pad;
    u32 count;               /* +0x14 parts */
    u32 *nodes_trs;          /* +0x18 each node's 9 floats (translation, ?, rotation?) */
    int *parents;            /* +0x1C each node's parent (-1: none) */
    Tm3 *texture;            /* +0x20 */
    u16 a;                   /* +0x24 */
    u16 nodes;               /* +0x26 */
    u8 range[6];             /* +0x28 node ranges (first, count): other modes, then mode 0's
                              * two (see func_00149730) */
    u8 flag2e;               /* +0x2E the texture's base and alpha are sent to VU1 */
    u8 alpha;                /* +0x2F */
} Model;

extern u8 g_004062F0[];                  /* the VU1 header for parts of kind 4 */
extern u8 g_00406310[];                  /* the VU1 header for the others */

void func_00148700(u32 *p);
void func_001485C0(u8 *list, int n, int other);
void func_00148660(u8 *list);
void func_001486A0(u8 *o);
void func_00147780(void *node);
void func_001477A0(void *p);

/* 0x00147780, 0x20 bytes, matching. Clears a node (0x70 bytes). */
void func_00147780(void *node)
{
    func_001185E0(node, 0x70, 0);
}

/* 0x001477A0, 0x20 bytes, matching. */
void func_001477A0(void *p)
{
    func_001185E0(p, 0x10, 0);
}

/* 0x001477C0, 0x20 bytes, matching. */
void func_001477C0(void *p)
{
    func_001185E0(p, 0x20, 0);
}

/* A track's value at time `t` (`p` on its first key). */
static inline float track_value(const float *p, u32 size, float t)
{
    const float *k;
    float prev, s;
    int n;

    if (size == 0)
        return 0.0f;
    if (size == 1)
        return *p;
    n = 0;
    prev = 0.0f;
    if (*p <= t) {
        k = p;
        do {
            n += size;
            prev = *k;
            k += size;
        } while (*k <= t);
    }
    k = p + n;
    s = (t - prev) / (*k - prev);
    return k[4] + s * k[3] + k[1] * s * s * s + k[2] * s * s;
}

/* 0x001477E0, 0x190 bytes. Starts a camera motion: the root node's translation at time 0. */
void func_001477E0(u32 *motion, u32 *out)
{
    const float *p = (const float *)(motion + 3);
    float pos[3];
    u32 i;

    out[0] = (u32)PS2_ADDR(motion);
    for (i = 0; i < motion[1]; i++) {
        u32 w = *(const u32 *)p++;
        u32 size = w >> 13 & 7;

        if ((w & 0xFF) == 0) {
            float v = track_value(p, size, 0.0f);

            switch (w >> 8 & 0x1F) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
                pos[0] = v;
                break;
            case 4:
                pos[1] = v;
                break;
            case 5:
                pos[2] = v;
                break;
            }
        }
        p += size * (w >> 18);
    }
    ((float *)out)[4] = pos[0];
    ((float *)out)[5] = pos[1];
    ((float *)out)[6] = pos[2];
    ((float *)out)[7] = 1.0f;
}

/* 0x00147980, 0x34 bytes, matching. Frees a camera motion. */
void func_00147980(u32 *state)
{
    func_00102EC0((void *)PS2_PTR(state[0]));
    state[0] = 0;
    func_001477C0(state);
}

/* 0x001479C0, 0x8 bytes, matching. */
void func_001479C0(u32 *motion, MotionState *s)
{
    s->motion = motion;
}

/* 0x001479D0, 0x1CC bytes. The camera at time `t` (while the motion lasts): components 9-16
 * into out[0-7] (component 15 halved: an angle?). */
void func_001479D0(float t, MotionState *s, float *out)
{
    u32 *m = s->motion;
    const float *p = (const float *)(m + 3);
    u32 i;

    if (t < (float)(int)m[2]) {
        func_001185E0((unsigned char *)(out), 0x20, 0);
        for (i = 0; i < m[1]; i++) {
            u32 w = *(const u32 *)p++;
            u32 size = w >> 13 & 7;
            float v = track_value(p, size, t);

            switch (w >> 8 & 0x1F) {
            case 9:
                out[0] = v;
                break;
            case 10:
                out[1] = v;
                break;
            case 11:
                out[2] = v;
                break;
            case 12:
                out[3] = v;
                break;
            case 13:
                out[4] = v;
                break;
            case 14:
                out[5] = v;
                break;
            case 15:
                out[6] = v * 0.5f;
                break;
            case 16:
                out[7] = v;
                break;
            }
            p += size * (w >> 18);
        }
    }
}

/* 0x00147BB0, 0x1C bytes, matching. */
void func_00147BB0(void *p)
{
    func_00118850(p, 0x10);
}

/* 0x00147BD0, 0x18 bytes, matching. A file with a 0x20-byte header: its start twice, then its data. */
void func_00147BD0(u8 *file, u8 **out)
{
    out[0] = file;
    out[1] = file;
    out[2] = out[0] + 0x20;
}

/* 0x00147BF0, 0xC bytes, matching. */
u32 func_00147BF0(u8 **f)
{
    return *(u32 *)(f[1] + 0xC);
}

/* 0x00147C00, 0x50 bytes. One of three counts of the header (0-2); other values return
 * nothing defined (0 here). */
u32 func_00147C00(u8 **f, int which)
{
    if (which == 2)
        return *(u16 *)(f[1] + 0x14);
    if (which == 1)
        return *(u16 *)(f[1] + 0x12);
    if (which == 0)
        return *(u16 *)(f[1] + 0x10);
    return 0;
}

/* 0x00147C50, 0x74 bytes. Where list `which` starts (records of 3 bytes after the data). */
u8 *func_00147C50(u8 **f, int which)
{
    u8 *p = 0;

    if (which == 2)
        p = f[2] + (*(u16 *)(f[1] + 0x10) + *(u16 *)(f[1] + 0x12)) * 3;
    else if (which == 1)
        p = f[2] + *(u16 *)(f[1] + 0x10) * 3;
    else if (which == 0)
        p = f[2];
    return p;
}

/* 0x00147CD0, 0x50 bytes. One of three bytes of the header (0-2; 0 for others here). */
u8 func_00147CD0(u8 **f, int which)
{
    if (which == 2)
        return f[1][0x1E];
    if (which == 1)
        return f[1][0x1D];
    if (which == 0)
        return f[1][0x1C];
    return 0;
}

/* 0x00147D20, 0xC bytes, matching. */
void func_00147D20(u32 *p)
{
    p[0] = 0;
    p[1] = 0;
}

/* 0x00147D30, 0x208 bytes. Sets a tm3 texture up for GS buffers `tbp` (pixels, 8-bit) and `cbp`
 * (palettes); its TEX0 value. */
u64 func_00147D30(u32 *file, Tm3 *t, u32 tbp, u32 cbp)
{
    int i, tw, th;
    u32 n;
    int stride;

    t->file = (u8 *)file;
    t->width = file[1];
    t->height = file[2];
    t->qwc = file[3];
    t->frames = file[4];
    t->a = file[5];
    t->b = file[6];
    t->data = t->file + 0x20;
    stride = file[7];
    *(u64 *)(t->file + 0x50) = (u64)tbp << 32 | (u64)((t->width + 0x3F) / 64) << 48
                               | 0x1300000000000000;
    for (i = 0; i < t->frames; i++) {
        u8 *p;

        t->palette_qwc[i] = stride;
        p = t->data + (t->qwc + stride * i) * 16;
        t->palette[i] = p;
        *(u64 *)(p + 0x20) = (u64)cbp << 32 | 0x1000000000000;
    }
    for (; i < 16; i++) {
        t->palette[i] = 0;
        t->palette_qwc[i] = 0;
    }
    tw = 0;
    for (n = t->width - 1; n != 0; n >>= 1)
        tw++;
    th = 0;
    for (n = t->height - 1; n != 0; n >>= 1)
        th++;
    t->tex0 = (u64)cbp << 37 | (u64)th << 30 | (u64)tw << 26 | tbp
              | (u64)((t->width + 0x3F) / 64) << 14 | 0x1300000 | 0x400000000
              | 0x4000000000000000;
    return t->tex0;
}

/* 0x00147F40, 0x30 bytes, matching. Frees a tm3 texture's file. */
void func_00147F40(u32 *t)
{
    func_00102EC0((void *)PS2_PTR(t[0]));
    func_00147D20(t);
}

/* Writes a "ref" DMA tag into the chain (VIF NOPs). */
static inline void send_ref(u32 qwc, u32 addr)
{
    u32 *d = g_70000158;

    d[0] = qwc | 0x30000000;
    d[1] = addr;
    d[2] = 0;
    d[3] = 0;
    g_70000158_SET(d + 4);
}

/* Writes a TEXFLUSH into the chain. */
static inline void send_texflush(void)
{
    u32 *d = g_70000158;

    d[0] = 0x10000002;
    d[1] = 0;
    d[2] = 0;
    d[3] = 0x50000002;
    d[4] = 0x8001;
    d[5] = 0x10000000;
    d[6] = 0xE;
    d[7] = 0;
    d[8] = 0;
    d[9] = 0;
    d[10] = 0x3F;
    d[11] = 0;
    g_70000158_SET(d + 12);
}

/* 0x00147F70, 0xFC bytes. Sends palette `frame` and the pixels of a tm3 texture, then a
 * TEXFLUSH. */
void func_00147F70(Tm3 *t, int frame)
{
    send_ref(t->palette_qwc[0], (u32)PS2_ADDR(t->palette[frame]));
    send_ref(t->qwc, (u32)PS2_ADDR(t->data));
    send_texflush();
}

/* 0x00148070, 0xC0 bytes. Sends palette `frame` only, then a TEXFLUSH. */
void func_00148070(Tm3 *t, int frame)
{
    send_ref(t->palette_qwc[0], (u32)PS2_ADDR(t->palette[frame]));
    send_texflush();
}

/* 0x00148130, 0x20 bytes, matching. Clears a model. */
void func_00148130(Model *m)
{
    func_001185E0((unsigned char *)(m), 0x30, 0);
}

/* 0x00148150, 0x198 bytes. Sets a model's parts up: the file's offsets become pointers, each
 * part's packets get the texture's base, and each part its VU1 header. */
void func_00148150(Model *m)
{
    u32 *f = m->file;
    u32 *list, *p;
    ModelPart *part;
    u32 i, n;

    f[1] += (u32)PS2_ADDR(f);
    list = (u32 *)PS2_PTR((f[2] + (u32)PS2_ADDR(f)));
    f[2] = (u32)PS2_ADDR(list);
    m->count = list[0];
    part = (ModelPart *)(func_00102DB0(0x10, list[0] << 4));
    m->parts = part;
    p = list + 4;
    n = 0;
    for (i = 0; i < m->count; i++, part++) {
        part->kind = p[0];
        part->qwc = p[1];
        part->data = p + 4;
        p += p[2] * 4;
        if (part->qwc != 0) {
            u32 *q = part->data;
            int words = 0;

            do {
                int size = (*q >> 16 & 0xFF) * 4 + 2;

                q[10] += (u32)(m->tex0 >> 32) & 0x7FFE0;
                words += size;
                q += size;
            } while ((u32)((words + 3) / 4) < part->qwc);
        }
        n = m->count;
    }
    part = m->parts;
    for (i = 0; i < n; i++, part++) {
        if (part->qwc != 0)
            part->header = (part->data[0xE] >> 15 & 7) == 4 ? g_004062F0 : g_00406310;
    }
}

/* 0x001482F0, 0x78 bytes. Sets a model up from its file, for texture `tex0`. */
void func_001482F0(u32 *file, Model *m, u64 tex0)
{
    u32 *h;

    m->file = file;
    m->tex0 = tex0;
    h = (u32 *)((u8 *)file + (file[1] & ~3));
    m->a = h[0] >> 16;
    m->nodes = h[0];
    m->parents = (int *)(h + 1);
    m->nodes_trs = h + 1 + m->nodes * 2;
    func_00148150(m);
    file[3] = 1;
}

/* 0x00148370, 0x40 bytes, matching. Frees a model and its file. */
void func_00148370(Model *m)
{
    func_00102EC0((unsigned char *)(m->parts));
    m->parts = 0;
    func_00102EC0((unsigned char *)(m->file));
    m->file = 0;
    func_00148130(m);
}

/* 0x001483B0, 0x34 bytes, matching. Frees a model (its file kept). */
void func_001483B0(Model *m)
{
    func_00102EC0((unsigned char *)(m->parts));
    m->parts = 0;
    func_00148130(m);
}

/* 0x001483F0, 0x24 bytes, matching. Sets a model's node ranges. */
void func_001483F0(Model *m, u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    m->range[0] = a;
    m->range[1] = b;
    m->range[2] = c;
    m->range[3] = d;
    m->range[4] = e;
    m->range[5] = f;
    m->alpha = 100;
}

/* 0x00148420, 0x40 bytes, matching. Gives a model its description (`info`, kept at +0x20): the node
 * ranges from its bytes 0x90-0x95, the byte at +0x99. */
void func_00148420(Model *m, u8 *info)
{
    m->texture = (Tm3 *)info;
    m->range[0] = info[0x90];
    m->range[1] = info[0x91];
    m->range[2] = info[0x92];
    m->range[3] = info[0x93];
    m->range[4] = info[0x94];
    m->range[5] = info[0x95];
    m->alpha = info[0x99];
}

/* 0x00148460, 0x80 bytes. Sends a model's parts. */
void func_00148460(Model *m)
{
    ModelPart *part = m->parts;
    u32 i;

    for (i = 0; i < m->count; i++, part++) {
        if (part->qwc != 0)
            send_ref(part->qwc, (u32)PS2_ADDR(part->data));
    }
}

/* 0x001484E0, 0xB8 bytes. Sends a model's parts, each after its VU1 header. */
void func_001484E0(Model *m)
{
    ModelPart *part = m->parts;
    u32 i;

    for (i = 0; i < m->count; i++, part++) {
        if (part->qwc != 0) {
            send_ref(2, (u32)PS2_ADDR(part->header));
            send_ref(part->qwc, (u32)PS2_ADDR(part->data));
        }
    }
}

/* 0x001485A0, 0x20 bytes, matching. */
void func_001485A0(void *p)
{
    func_001185E0(p, 0x10, 0);
}

/* 0x001485C0, 0x98 bytes. Sets up a list of `n` 32-byte transforms (zero, w = 1.0), from the
 * game's heap or (`other`) from func_0020EC50. */
void func_001485C0(u8 *list, int n, int other)
{
    u32 *p;
    int i;

    list[0xC] = n;
    if (other == 0) {
        *(void **)(list + 8) = func_00102D30(n << 5);
        list[0xF] = 0;
    } else {
        *(void **)(list + 8) = func_0020EC50(n << 5);
        list[0xF] = 1;
    }
    p = *(u32 **)(list + 8);
    for (i = 0; i < list[0xC]; i++, p += 8) {
        p[4] = 0;
        p[5] = 0;
        p[6] = 0;
        ((float *)p)[7] = 1.0f;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
    }
}

/* 0x00148660, 0x38 bytes, matching. Frees the list. */
void func_00148660(u8 *list)
{
    func_00102EC0(*(void **)(list + 8));
    func_001185E0(list, 0x10, 0);
}

/* 0x001486A0, 0x60 bytes. Clears an object (0x220 bytes) with a unit matrix at +0x1A0. */
void func_001486A0(u8 *o)
{
    float *m;

    func_001485A0(o + 0x210);
    func_001185E0(o, 0x220, 0);
    m = (float *)(o + 0x1A0);
    m[0] = 1.0f;  m[1] = 0.0f;  m[2] = 0.0f;  m[3] = 0.0f;
    m[4] = 0.0f;  m[5] = 1.0f;  m[6] = 0.0f;  m[7] = 0.0f;
    m[8] = 0.0f;  m[9] = 0.0f;  m[10] = 1.0f; m[11] = 0.0f;
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

/* 0x00148700, 0x8C bytes, matching. Sets up two VU1 packets (0xD0 bytes each): a TEX0_1 write and an
 * UNPACK of 9 quadwords. */
void func_00148700(u32 *p)
{
    int i;

    for (i = 0; i < 2; i++, p += 0x34) {
        p[0] = 0x11000000;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0x50000002;
        *(u64 *)(p + 4) = 0x1000000000008001;
        *(u64 *)(p + 6) = 0xE;
        *(u64 *)(p + 8) = 0;
        *(u64 *)(p + 10) = 6;
        p[12] = 0;
        p[13] = 0;
        p[14] = 0;
        p[15] = 0x6C09000B;
        p[0x30] = 0;
        p[0x31] = 0;
        p[0x32] = 0;
        p[0x33] = 0x80;
    }
}

/* A node of a skeleton being drawn (0x70 bytes). */
typedef struct Node {
    float pos[4];            /* translation, w = 1 */
    float rot[4];            /* +0x10 rotation, w = 0 */
    float matrix[4][4];      /* +0x20 local matrix (VU0 micro subroutine 0x50) */
    struct Node *parent;     /* +0x60 */
    float **slot;            /* +0x64 where its matrices go */
    u8 dirty;                /* +0x68 */
    u8 index;
    u8 pad[6];
} Node;

/* An object drawn with a skeleton (0x220 bytes). */
typedef struct {
    u32 packets[2][0x34];    /* +0x000 the VU1 packets (lights at +0x40 / +0x80 of each) */
    float world[4][4];       /* +0x1A0 */
    u8 *matrices[2];         /* +0x1E0 two matrices per node, per frame */
    Model *model;            /* +0x1E8 */
    Model *model2;           /* +0x1EC */
    Node *nodes;             /* +0x1F0 */
    Node *nodes2;            /* +0x1F4 */
    float **slots;           /* +0x1F8 (16 bytes per node) */
    u32 pad;
    u8 count;                /* +0x200 nodes */
    u8 a;
    u8 b;                    /* +0x202 kept when cleared */
    u8 c;
    u32 d;                   /* +0x204 */
    Node *e;                 /* +0x208 */
    union {
        u8 all;
        Bits8 b;             /* the original tests the bits as signed one-bit fields */
    } flags;                 /* +0x20C */
    u8 pad2[3];
    u8 transforms[0x10];     /* +0x210 */
} Actor;

void func_00143268(void *m, void *a, void *b, void *c);           /* sceVu0NormalLightMatrix? */
void func_00143328(void *m, void *a, void *b, void *c, void *d);  /* sceVu0LightColorMatrix? */

/* A node's local matrix from its rotation and translation (VU0 micro subroutine 0x50). */
#ifdef SW2E_PC
#define NODE_MATRIX(n) sw2e_vu0_matrix((float *)((u8 *)(n) + 0x20), (const float *)((u8 *)(n) + 0x10), (const float *)(n))
#else
#define NODE_MATRIX(n)                                                  \
    __asm__ volatile("lqc2 $vf1, 0x10(%0)\n"                            \
                     "lqc2 $vf2, 0(%0)\n"                               \
                     "vcallms 0x50\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x20(%0)\n"                           \
                     "sqc2 $vf17, 0x30(%0)\n"                           \
                     "sqc2 $vf18, 0x40(%0)\n"                           \
                     "sqc2 $vf19, 0x50(%0)\n"                           \
                     : : "r"(n) : "$9", "memory")
#endif

/* Takes a node's rotation and translation from its 9 floats (rotation, ?, translation). */
#define NODE_TRS(n, trs)                                                \
    do {                                                                \
        (n)->rot[0] = ((float *)(trs))[0];                              \
        (n)->rot[1] = ((float *)(trs))[1];                              \
        (n)->rot[2] = ((float *)(trs))[2];                              \
        (n)->rot[3] = 0.0f;                                             \
        (n)->pos[0] = ((float *)(trs))[6];                              \
        (n)->pos[1] = ((float *)(trs))[7];                              \
        (n)->pos[2] = ((float *)(trs))[8];                              \
        (n)->pos[3] = 1.0f;                                             \
    } while (0)

/* 0x00148790, 0x250 bytes. Builds an object's nodes from its model (and the second node list
 * from `m2`). */
void func_00148790(Actor *a, Model *m, Model *m2)
{
    Node *n = a->nodes;
    u32 *trs = m->nodes_trs;
    int *parent = m->parents;
    int i;

    for (i = 0; i < m->nodes; i++, n++, parent++, trs += 9) {
        func_00147780(n);
        NODE_TRS(n, trs);
        NODE_MATRIX(n);
        n->index = i;
        n->parent = *parent == -1 ? 0 : &a->nodes[*parent];
        n->slot = (float **)((u8 *)a->slots + i * 0x10);
        n->dirty = 1;
    }
    if (m2 != 0 && (n = a->nodes2) != 0) {
        trs = m2->nodes_trs;
        parent = m2->parents;
        for (i = 0; i < m2->nodes; i++, n++, parent++, trs += 9) {
            func_00147780(n);
            NODE_TRS(n, trs);
            NODE_MATRIX(n);
            n->index = i;
            n->parent = *parent == -1 ? 0 : &a->nodes2[*parent];
            n->slot = (float **)((u8 *)a->slots + i * 0x10);
            n->dirty = 1;
        }
    }
}

/* 0x001489F0, 0xC0 bytes. Rebuilds the local matrices of nodes `first` (+0x2C of `m`) to
 * first + count (+0x2D). */
void func_001489F0(Actor *a, Model *m)
{
    u8 first = m->range[4];
    Node *n = &a->nodes[first];
    u32 *trs = m->nodes_trs + first * 9;
    int i;

    for (i = 0; i < m->range[5]; i++, n++, trs += 9) {
        NODE_TRS(n, trs);
        NODE_MATRIX(n);
        n->dirty = 1;
    }
}

/* 0x00148AB0, 0xAC bytes. Sets `count` nodes up without a model: unit matrices, no parent. */
void func_00148AB0(Actor *a, u32 count)
{
    Node *n = a->nodes;
    u32 i;

    for (i = 0; i < count; i++, n++) {
        func_00147780(n);
        n->matrix[0][0] = 1.0f;
        n->matrix[1][1] = 1.0f;
        n->matrix[2][2] = 1.0f;
        n->matrix[3][3] = 1.0f;
        n->index = i;
        n->parent = 0;
        n->slot = (float **)((u8 *)a->slots + i * 0x10);
        n->dirty = 1;
    }
}

/* 0x00148B60, 0x650 bytes. Resets the translation of nodes `first` to `last` from the model.
 * When there is a second model and node list, the same is done a second time on the first list
 * (as in the original). The original loops are unrolled by 8. */
void func_00148B60(Actor *a, int first, int last)
{
    int i;

    for (i = first; i <= last; i++) {
        Node *n = &a->nodes[i];
        float *trs = (float *)a->model->nodes_trs + i * 9;

        n->pos[0] = trs[6];
        n->pos[1] = trs[7];
        n->pos[2] = trs[8];
        n->pos[3] = 1.0f;
    }
    if (a->model2 != 0 && a->nodes2 != 0) {
        for (i = first; i <= last; i++) {
            Node *n = &a->nodes[i];
            float *trs = (float *)a->model->nodes_trs + i * 9;

            n->pos[0] = trs[6];
            n->pos[1] = trs[7];
            n->pos[2] = trs[8];
            n->pos[3] = 1.0f;
        }
    }
}

/* Writes a unit matrix. */
static inline void unit_matrix(float *m)
{
    int i;

    for (i = 0; i < 16; i++)
        m[i] = (i % 5) == 0 ? 1.0f : 0.0f;
}

/* 0x001491B0, 0xF0 bytes. Gives each node its two matrices (unit) in each frame's buffer (a
 * quadword skipped after the first 64 nodes). */
void func_001491B0(Actor *a)
{
    float **slot = a->slots;
    float *m0 = (float *)(a->matrices[0] + 0x10);
    float *m1 = (float *)(a->matrices[1] + 0x10);
    int i;

    for (i = 0; i < a->count; i++, slot += 4, m0 += 16, m1 += 16) {
        if (i == 0x40) {
            m0 += 4;
            m1 += 4;
        }
        func_001477A0(slot);
        unit_matrix(m0);
        unit_matrix(m1);
        slot[0] = m0;
        slot[1] = m1;
    }
}

/* 0x001492A0, 0x10C bytes, matching. Sets an object up for model `m` with `count` nodes and `n`
 * transforms. */
void func_001492A0(Actor *a, Model *m, u8 count, int n)
{
    int f;

    a->model = m;
    a->model2 = 0;
    a->count = count;
    func_00148700(a->packets[0]);
    a->slots = (float **)(func_00102DB0(0x10, a->count << 4));
    a->nodes = (Node *)(func_00102DB0(0x10, a->count * 0x70));
    a->nodes2 = 0;
    for (f = 0; f < 2; f++) {
        a->matrices[f] = func_00102DB0(0x10, a->count * 0x40 + 0x20);
        func_001185E0(a->matrices[f], a->count * 0x40 + 0x20, 0);
    }
    func_001491B0(a);
    if (m != 0)
        func_00148790(a, m, 0);
    a->c = 0;
    func_001485C0(a->transforms, n, 0);
    a->d = 0;
}

/* 0x001493B0, 0x13C bytes. The same with a second model (`count2` nodes for it). */
void func_001493B0(Actor *a, Model *m, Model *m2, u8 count, int count2, int n)
{
    int f;

    a->model = m;
    a->model2 = m2;
    a->count = count;
    func_00148700(a->packets[0]);
    a->slots = (float **)(func_00102DB0(0x10, a->count << 4));
    a->nodes = (Node *)(func_00102DB0(0x10, a->count * 0x70));
    if (count2 == 0)
        a->nodes2 = 0;
    else
        a->nodes2 = (Node *)(func_00102DB0(0x10, count2 * 0x70));
    for (f = 0; f < 2; f++) {
        a->matrices[f] = func_00102DB0(0x10, a->count * 0x40 + 0x20);
        func_001185E0(a->matrices[f], a->count * 0x40 + 0x20, 0);
    }
    func_001491B0(a);
    if (m != 0)
        func_00148790(a, m, m2);
    a->c = 0;
    func_001485C0(a->transforms, n, 0);
    a->d = 0;
}

/* 0x001494F0, 0x9C bytes, matching. Frees an object's buffers and clears it (+0x202 kept). */
void func_001494F0(Actor *a)
{
    int f;
    u8 keep;

    func_00148660(a->transforms);
    func_00102EC0((unsigned char *)(a->slots));
    a->slots = 0;
    func_00102EC0((unsigned char *)(a->nodes));
    a->nodes = 0;
    if (a->nodes2 != 0) {
        func_00102EC0((unsigned char *)(a->nodes2));
        a->nodes2 = 0;
    }
    for (f = 0; f < 2; f++) {
        func_00102EC0(a->matrices[f]);
        a->matrices[f] = 0;
    }
    keep = a->b;
    func_001486A0((u8 *)a);
    a->b = keep;
}

/* 0x00149590, 0x8C bytes. Sets the lights of both packets: directions `dir`, colours `colour`,
 * ambient `ambient`. */
void func_00149590(Actor *a, u8 *dir, u8 *colour, void *ambient)
{
    u8 *p = (u8 *)a;
    int i;

    for (i = 0; i < 2; i++, p += 0xD0) {
        func_00143268(p + 0x40, dir, dir + 0x10, dir + 0x20);
        func_00143328(p + 0x80, colour, colour + 0x10, colour + 0x20, ambient);
    }
}

/* 0x00149620, 0xF4 bytes, matching. Changes an object's models; the nodes are rebuilt when the node count
 * or the presence of the second model changes, or when there is no second model. */
void func_00149620(Actor *a, Model *m, Model *m2)
{
    int rebuild = 0;
    Model *old = a->model;
    Model *old2 = a->model2;

    a->model = m;
    a->model2 = m2;
    if ((old2 != 0 && m2 == 0) || (m2 != 0 && old2 == 0))
        rebuild = 1;
    if (old == 0)
        rebuild = 1;
    else if (m->nodes != old->nodes)
        rebuild = 1;
    if (m != 0) {
        if (m2 == 0)
            a->flags.b.f1 = 0;
        if (rebuild)
            func_00148790(a, m, m2);
        else if (m2 == 0)
            func_00148790(a, m, m2);
        a->e = a->nodes;
    }
    a->d = 0;
    a->flags.b.f3 = 0;
}

/* 0x00149720, 0x8 bytes, matching. */
void func_00149720(Actor *a)
{
    a->d = 0;
}

u32 func_0014E6F0(Actor *a, float base[4][4], float world[4][4], int frame);

/* out = a * b (4 x 4, column vectors: out[j] = a * b[j]), as the VU0's vmulabc / vmaddabc
 * sequences do. */
static inline void mat_mul(float out[4][4], float a[4][4], float b[4][4])
{
    float r[4][4];
    int j, k;

    for (j = 0; j < 4; j++)
        for (k = 0; k < 4; k++)
            r[j][k] = a[0][k] * b[j][0] + a[1][k] * b[j][1] + a[2][k] * b[j][2]
                      + a[3][k] * b[j][3];
    for (j = 0; j < 4; j++)
        for (k = 0; k < 4; k++)
            out[j][k] = r[j][k];
}

/* A node's matrix for frame `frame`, and whether it is up to date (the byte after the two
 * matrix pointers). */
#define NODE_WORLD(n, frame) (*(float (**)[4])((u8 *)(n)->slot + (frame) * 4))
#define NODE_DONE(n)         (((u8 *)(n)->slot)[8])

/* Brings a node's matrix up to date: its ancestors not yet done are done first, from the root
 * (the root's matrix is `base` times its local one, the others their parent's times theirs). */
static inline void node_world(Node *n, float base[4][4], int frame)
{
    Node *chain[40];
    int top = 0, done = 0;
    Node *p;

    for (p = n; p != 0; p = p->parent)
        chain[top++] = p;
    top--;
    while (top >= 0 && NODE_DONE(chain[top])) {
        top--;
        done++;
    }
    if (done == 0) {
        mat_mul(NODE_WORLD(chain[top], frame), base, chain[top]->matrix);
        NODE_DONE(chain[top]) = 1;
        top--;
    }
    for (; top >= 0; top--) {
        mat_mul(NODE_WORLD(chain[top], frame), NODE_WORLD(chain[top + 1], frame),
                chain[top]->matrix);
        NODE_DONE(chain[top]) = 1;
    }
}

/* The nodes done in mode 0 (body), with the hands' fingers when the model has more than 26
 * nodes (+0x29), and the ones done in mode 1. */
static const u8 nodes_mode0_a[] = { 6, 7, 20, 21 };
static const u8 nodes_mode0_b[] = { 24, 25, 22, 23 };
static const u8 nodes_mode0_c[] = { 33, 27, 37, 31, 35, 29, 43, 39, 45, 41 };
static const u8 nodes_mode1[] = { 8, 10, 11, 9, 14, 17, 1, 2 };

/* 0x00149730, 0x3C58 bytes. Brings the matrices of an object's nodes up to date for frame
 * `frame` (the original inlines the chain walk for each node: 15 KB of VU0 code).
 *
 * The base matrix is the object's world matrix times the rotation at 0x70000080 (set up by
 * func_001181E0), or the matrix of the node it is attached to (+0x1FC, node +0x201). Mode 0
 * does the body's nodes (the arms' unless the second model is in use, the fingers for models of
 * more than 26 nodes), node 11, the model's ranges (+0x2C/+0x2D, then +0x2A/+0x2B, the latter by
 * func_0014E6F0 in some states); mode 1 eight fixed nodes; modes above 2 the range +0x28/+0x29;
 * mode 2 nothing. */
void func_00149730(Actor *a, char mode, int frame)
{
    Model *m = a->flags.b.f1 ? a->model2 : a->model;
    Node *list = a->flags.b.f1 ? a->nodes2 : a->nodes;
    float (*attached)[4] = 0;
    float base[4][4];
    Node *n;
    u32 i;

    if (a->e != list)
        return;
    for (i = 0, n = a->e; i < m->nodes; i++, n++)
        NODE_DONE(n) = 0;
    if (*(Actor **)((u8 *)a + 0x1FC) == 0) {
        mat_mul(base, a->world, (float (*)[4])0x70000080);
    } else {
        Actor *parent = *(Actor **)((u8 *)a + 0x1FC);

        attached = NODE_WORLD(&parent->e[a->a], frame);
        for (i = 0; i < 4; i++) {
            base[i][0] = attached[i][0];
            base[i][1] = attached[i][1];
            base[i][2] = attached[i][2];
            base[i][3] = attached[i][3];
        }
    }
    list = a->e;
    if (mode == 0) {
        for (i = 0; i < sizeof(nodes_mode0_a); i++)
            node_world(&list[nodes_mode0_a[i]], base, frame);
        if (a->flags.b.f1 == 0) {
            for (i = 0; i < sizeof(nodes_mode0_b); i++)
                node_world(&list[nodes_mode0_b[i]], base, frame);
            if (m->range[1] > 0x1A) {
                for (i = 0; i < sizeof(nodes_mode0_c); i++)
                    node_world(&list[nodes_mode0_c[i]], base, frame);
            }
        }
        node_world(&list[11], base, frame);
        if (m->range[5] != 0) {
            n = &a->e[m->range[4]];
            for (i = 0; i < m->range[5]; i++, n++)
                node_world(n, base, frame);
        }
        if (m->range[3] != 0) {
            if (a->flags.b.f2 && a->flags.b.f1 == 0 && a->d > 1) {
                if (attached == 0) {
                    func_0014E6F0(a, base, a->world, frame);
                } else {
                    float t[4][4];

                    mat_mul(t, attached, (float (*)[4])0x70000080);
                    func_0014E6F0(a, base, t, frame);
                }
            } else {
                n = &a->e[m->range[2]];
                for (i = 0; i < m->range[3]; i++, n++)
                    node_world(n, base, frame);
            }
        }
    } else if (mode == 1) {
        for (i = 0; i < sizeof(nodes_mode1); i++)
            node_world(&list[nodes_mode1[i]], base, frame);
    } else if (mode != 2) {
        n = &list[m->range[0]];
        for (i = 0; i < m->range[1]; i++, n++)
            node_world(n, base, frame);
    }
    if (a->d != (u32)-1)
        a->d++;
}

#define g_70000150 (*(int *)PS2_PTR(0x70000150))          /* frame index: 0 or 1 */

#define PI     3.1415927f
#define TWO_PI 6.2831855f

/* An angle brought back into (-pi, pi]. */
#define WRAP(a) ((a) > PI ? (a) - TWO_PI : (a) <= -PI ? (a) + TWO_PI : (a))

float vu0_angle(float x, float z);               /* VU0 micro subroutine 0x30 (atan2?) */
void vu0_sincos(float a, float *s, float *c);    /* VU0 micro subroutine 0x20 */
void func_001436C8(float *to, const float *from);   /* copies x, y, z */

/* The node list and model in use (the second ones when flag 2 is set and they exist). */
#define ACTOR_MODEL(a) ((a)->flags.b.f1 ? (a)->model2 : (a)->model)

/* 0x0014D390, 0x20 bytes, matching. Brings the matrices up to date for this frame. */
void func_0014D390(Actor *a, char mode)
{
    func_00149730(a, mode, g_70000150);
}

/* Copies the last frame's matrix of `count` nodes from `n` into this frame's. */
static inline void keep_matrices(Node *n, int count, int frame)
{
    int i, k;

    for (i = 0; i < count; i++, n++) {
        float (*to)[4] = NODE_WORLD(n, frame);
        float (*from)[4] = NODE_WORLD(n, frame ^ 1);

        for (k = 0; k < 16; k++)
            ((float *)to)[k] = ((float *)from)[k];
    }
}

/* 0x0014D3B0, 0x1A8 bytes. Keeps last frame's matrices for the model's ranges (the second range
 * of mode 0 only with the first model). */
void func_0014D3B0(Actor *a)
{
    int frame = g_70000150;
    Model *m = ACTOR_MODEL(a);

    keep_matrices(&a->e[m->range[0]], m->range[1], frame);
    keep_matrices(&a->e[m->range[4]], m->range[5], frame);
    if (a->flags.b.f1 == 0)
        keep_matrices(&a->e[m->range[2]], m->range[3], frame);
}

void func_0014D6C0(Actor *a);

/* 0x0014D560, 0x154 bytes. Settles an object (without a second node list): local matrices
 * rebuilt, both frames' matrices computed, then `n` more updates, each frame in turn (for the
 * swing nodes); flags 2 and 4 put back. */
void func_0014D560(Actor *a, char mode, int n)
{
    int frame = g_70000150;
    u8 saved = a->flags.all;
    int i;

    if (a->nodes2 == 0) {
        a->flags.b.f1 = 0;
        func_0014D6C0(a);
        a->d = 0;
        func_00149730(a, mode, frame ^ 1);
        a->d = 0;
        func_00149730(a, mode, frame);
        a->flags.b.f2 = 1;
        for (i = 0; i < n; i++) {
            frame ^= 1;
            func_00149730(a, mode, frame);
        }
        a->flags.all = (a->flags.all & ~6) | (saved & 6);
    }
}

/* 0x0014D6C0, 0x120 bytes. Rebuilds the local matrices of the changed nodes: the first
 * range[1] nodes of the list, then the range range[4] / range[5]. */
void func_0014D6C0(Actor *a)
{
    Model *m = ACTOR_MODEL(a);
    Node *n;
    int i;

    a->e = (a->flags.b.f1 && a->nodes2 != 0) ? a->nodes2 : a->nodes;
    for (i = 0, n = a->e; i < m->range[1]; i++, n++) {
        if (n->dirty) {
            n->dirty = 0;
            NODE_MATRIX(n);
        }
    }
    for (i = 0, n = &a->e[m->range[4]]; i < m->range[5]; i++, n++) {
        if (n->dirty) {
            n->dirty = 0;
            NODE_MATRIX(n);
        }
    }
}

/* Sets component `comp` of a node (0-2 rotation, 3-5 translation) and marks it changed. */
static inline void node_set(Node *n, u32 comp, float v)
{
    n->dirty = 1;
    switch (comp) {
    case 0: n->rot[0] = v; break;
    case 1: n->rot[1] = v; break;
    case 2: n->rot[2] = v; break;
    case 3: n->pos[0] = v; break;
    case 4: n->pos[1] = v; break;
    case 5: n->pos[2] = v; break;
    }
}

/* 0x0014D7E0, 0x1BC bytes. Applies a motion at time `t` to nodes `first` to `last`. */
void func_0014D7E0(float t, Actor *a, MotionState *s, u32 first, u32 last)
{
    Node *list;
    u32 *m;
    const float *p;
    u32 i;

    if (s == 0)
        return;
    list = (a->flags.b.f1 && a->nodes2 != 0) ? a->nodes2 : a->nodes;
    m = s->motion;
    p = (const float *)(m + 3);
    for (i = 0; i < m[1]; i++) {
        u32 w = *(const u32 *)p++;
        u32 node = w & 0xFF;
        u32 size = w >> 13 & 7;

        if (first <= node && node <= last)
            node_set(&list[node], w >> 8 & 0x1F, track_value(p, size, t));
        p += size * (w >> 18);
    }
}

/* 0x0014D9A0, 0x40 bytes, matching. The same for all the model's nodes. */
void func_0014D9A0(float t, Actor *a, MotionState *s)
{
    func_0014D7E0(t, a, s, 0, ACTOR_MODEL(a)->a);
}

/* 0x0014D9E0, 0x5D4 bytes. Applies a blend of three poses of a face motion to the face's nodes
 * (from node 47: part 0 nodes 0-7, part 1 nodes 8-13, part 2 nodes 14-15): v1 at `t1` is blended
 * towards v2 (`t2`, weight `w2`) and towards v3 (`t3`, `w3`), and the two by `w` (angles kept in
 * (-pi, pi]). With `single`, the pose at `t1` only. */
void func_0014D9E0(float t1, float w, float t2, float t3, float w2, float w3, Actor *a,
                   MotionState *s, int part, int single)
{
    u32 first, last, i;
    Node *face;
    u32 *m;
    const float *p;

    if (s == 0)
        return;
    if (part == 2) {
        first = 0xE;
        last = 0xF;
    } else if (part == 1) {
        first = 8;
        last = 0xD;
    } else if (part == 0) {
        first = 0;
        last = 7;
    } else {
        first = 0;
        last = 0;
    }
    face = a->nodes == 0 ? 0 : (Node *)((u8 *)a->nodes + 0x1490);
    m = s->motion;
    p = (const float *)(m + 3);
    for (i = 0; i < m[1]; i++) {
        u32 w0 = *(const u32 *)p++;
        u32 node = w0 & 0xFF;
        u32 comp = w0 >> 8 & 0x1F;
        u32 size = w0 >> 13 & 7;

        if (single == 0) {
            float v1 = track_value(p, size, t1);
            float v2 = track_value(p, size, t2);
            float v3 = track_value(p, size, t3);
            float v;

            if (comp < 3) {
                float b2 = v1 * (1.0f - w2) + v2 * w2;
                float b3;

                b2 = WRAP(b2);
                b3 = v1 * (1.0f - w3) + v3 * w3;
                b3 = WRAP(b3);
                v = b2 * (1.0f - w) + b3 * w;
                v = WRAP(v);
            } else {
                v = (v1 * (1.0f - w2) + v2 * w2) * (1.0f - w) + (v1 * (1.0f - w3) + v3 * w3) * w;
            }
            if (first <= node && node <= last)
                node_set(&face[node], comp, v);
        } else if (first <= node && node <= last) {
            node_set(&face[node], comp, track_value(p, size, t1));
        }
        p += size * (w0 >> 18);
    }
}

u32 func_00147C00(u8 **f, int which);
u8 *func_00147C50(u8 **f, int which);
u8 func_00147CD0(u8 **f, int which);

/* 0x0014DFC0, 0x3BC bytes. Plays part `part` of a face expression at time `t`: the
 * expression's keys (pose, weight 0-127, frames) are blended in turn from the part's base pose.
 * (When `t` is before the end of the first key, the start time is not set by the original.) */
void func_0014DFC0(float t, Actor *a, MotionState *s, u8 **expr, int part)
{
    u8 *key = func_00147C50(expr, part);
    int base = func_00147CD0(expr, part);
    u32 count = func_00147C00(expr, part);
    u8 *cur, *next;
    int start = 0;
    float k;

    if (count == 0)
        return;
    if (count == 1) {
        float w = (float)key[1] / 127.0f;
        float f;

        if (w >= 1.0f)
            w = 1.0f;
        f = (float)base * (1.0f - w) + (float)key[0] * w;
        func_0014D9E0((float)base, 1.0f, f, f, w, w, a, s, part, 0);
        return;
    }
    cur = key;
    next = key + 3;
    if ((int)key[2] < (int)t) {
        u32 i;
        int at = 0;

        for (i = 0; i < count - 1; i++) {
            cur = key;
            start = at;
            next = cur + 3;
            if (t <= (float)(int)(start + cur[5]))
                break;
            at = start + cur[5];
            key = next;
        }
    }
    k = (t - (float)start) / (float)next[2];
    if (k >= 1.0f)
        k = 1.0f;
    if (k < 0.0f)
        k = 0.0f;
    func_0014D9E0((float)base, k, (float)cur[0], (float)next[0], (float)cur[1] / 127.0f,
                  (float)next[1] / 127.0f, a, s, part, 0);
}

/* 0x0014E380, 0x370 bytes. A transition: the changed nodes are blended back from the pose saved
 * at +0x218 (1 - time / length, +0x210 / +0x214), rotations by the shorter way round; the root
 * keeps the saved height only (or this frame's height, or all of its position: +0x21D,
 * +0x21E). */
void func_0014E380(Actor *a)
{
    Model *m = ACTOR_MODEL(a);
    u8 *t = a->transforms;
    float k = 1.0f - *(float *)(t + 0) / *(float *)(t + 4);
    Node *n = (a->flags.b.f1 && a->nodes2 != 0) ? a->nodes2 : a->nodes;
    float *saved = *(float **)(t + 8);
    int i;

    if (t[0xE] == 0) {
        if (t[0xD] == 0) {
            saved[4] = 0.0f;
            saved[6] = 0.0f;
            saved[7] = 1.0f;
        } else {
            saved[4] = 0.0f;
            saved[5] = n->pos[1];
            saved[6] = 0.0f;
            saved[7] = 1.0f;
        }
    } else {
        saved[4] = n->pos[0];
        saved[5] = n->pos[1];
        saved[6] = n->pos[2];
        saved[7] = n->pos[3];
    }
    for (i = 0; i < m->range[1]; i++, n++, saved += 8) {
        if (n->dirty) {
            float alt[3], best[3], d;
            int c;

            for (c = 0; c < 4; c++)
                n->pos[c] = n->pos[c] * k + saved[4 + c] * (1.0f - k);
            alt[0] = saved[0] + PI;
            alt[1] = PI - saved[1];
            alt[2] = saved[2] + PI;
            for (c = 0; c < 3; c++)
                alt[c] = WRAP(alt[c]);
            if (fabsf(n->rot[2] - saved[2]) + fabsf(n->rot[0] - saved[0])
                + fabsf(n->rot[1] - saved[1])
                < fabsf(n->rot[2] - alt[2]) + fabsf(n->rot[0] - alt[0])
                  + fabsf(n->rot[1] - alt[1])) {
                for (c = 0; c < 3; c++)
                    best[c] = saved[c];
            } else {
                for (c = 0; c < 3; c++)
                    best[c] = alt[c];
            }
            for (c = 0; c < 3; c++) {
                d = n->rot[c] - best[c];
                d = WRAP(d);
                n->rot[c] = d * k + best[c] + 0.0f;
            }
        }
    }
}

/* A swing node's description (32 bytes, from the model's description at +0x20). */
typedef struct {
    float a[4];
    float limit;             /* +0x10 */
    float min;               /* +0x14 the distance kept from the body */
    float length;            /* +0x18 */
    float drop;              /* +0x1C */
} Swing;

extern float g_00406330[4];              /* the forward vector */

/* A position's distance from another. */
static inline float dist3(const float *a, const float *b)
{
    float x = a[0] - b[0], y = a[1] - b[1], z = a[2] - b[2];

    return sqrtf(x * x + y * y + z * z);
}

/* 0x0014E6F0, 0x9C8 bytes. The swing nodes (range[2] / range[3], a skirt?): each keeps last
 * frame's position, is pulled towards its parent at its length, pushed out of the body by its
 * kind (0-4: by the side, front, back or between the legs, nodes 4 and 5), and kept within its
 * limit. `base` is the root's base matrix, `world` the object's. */
u32 func_0014E6F0(Actor *a, float base[4][4], float world[4][4], int frame)
{
    Model *m = ACTOR_MODEL(a);
    float fwd[4];
    float yaw;
    u32 r = 0;
    Node *n;
    Swing *sw;
    int i, c;

    for (c = 0; c < 4; c++)
        fwd[c] = world[0][c] * g_00406330[0] + world[1][c] * g_00406330[1]
                 + world[2][c] * g_00406330[2] + world[3][c] * g_00406330[3];
    yaw = vu0_angle(fwd[0], fwd[2]);
    if ((u8 *)m->texture == 0)
        return r;
    n = &a->e[m->range[2]];
    for (i = 0; i < m->range[3]; i++, n++) {
        float keep[4];

        for (c = 0; c < 4; c++)
            keep[c] = NODE_WORLD(n, frame ^ 1)[3][c];
        node_world(n, base, frame);
        for (c = 0; c < 4; c++)
            NODE_WORLD(n, frame)[3][c] = keep[c];
    }
    sw = (Swing *)m->texture;
    n = &a->e[m->range[2]];
    for (i = 0; i < m->range[3]; i++, n++, sw++) {
        float (*cur)[4] = NODE_WORLD(n, frame);
        float (*pm)[4] = NODE_WORLD(&a->e[n->parent->index], frame);
        float parent[4], dir[4], target[4], len, limit, d;
        s8 kind = ((u8 *)m->texture)[0x8C + i];

        for (c = 0; c < 4; c++)
            parent[c] = pm[3][c] / pm[3][3];
        for (c = 0; c < 4; c++)
            dir[c] = parent[c] - cur[3][c];
        len = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
        for (c = 0; c < 4; c++)
            dir[c] = dir[c] / len;
        for (c = 0; c < 4; c++)
            target[c] = dir[c] * sw->length;
        target[1] += sw->drop;
        for (c = 0; c < 4; c++)
            target[c] += cur[3][c];
        if (kind < 5) {
            float ang = yaw, rx, rz, s, co, s2, c2, push[3] = { 0.0f, 0.0f, 0.0f };
            float *root = NODE_WORLD(&a->e[0], frame)[3];
            float rel[3];
            int pi = n->parent->index;

            if (pi == 1)
                ang = yaw + a->e[1].rot[0];
            else if (pi == 9)
                ang = yaw - a->e[8].rot[0];
            ang = (ang + 0.0f) - (float)(int)(ang / TWO_PI) * TWO_PI;
            ang = WRAP(ang);
            for (c = 0; c < 3; c++)
                rel[c] = target[c] - root[c];
            vu0_sincos(-ang, &s, &co);
            rx = rel[0] * co + rel[2] * s;
            rz = -rel[0] * s + rel[2] * co;
            vu0_sincos(ang, &s2, &c2);
            if (kind == 4) {
                if (rz < sw->min) {
                    d = sw->min - rz;
                    push[0] = d * s2;
                    push[2] = d * c2;
                }
            } else if (kind == 3) {
                if (-rz < sw->min) {
                    d = -sw->min - rz;
                    push[0] = d * s2;
                    push[2] = d * c2;
                }
            } else if (kind == 2) {
                float *l4 = NODE_WORLD(&a->e[4], frame)[3];
                float *l5 = NODE_WORLD(&a->e[5], frame)[3];
                float d4 = dist3(root, l4), d5 = dist3(root, l5);
                float mx = d5 < d4 ? d4 : d5;
                float low;

                mx = sw->min < mx ? mx : sw->min;
                if (rz < mx) {
                    d = mx - rz;
                    push[0] = d * s2;
                    push[2] = d * c2;
                }
                low = (l4[1] < l5[1] ? l4[1] : l5[1]) - 8.0f;
                if (low < target[1])
                    push[1] = low - target[1];
            } else if (kind == 1) {
                if (-rx < sw->min) {
                    d = -sw->min - rx;
                    push[0] = d * c2;
                    push[2] = -d * s2;
                }
            } else if (kind == 0 && rx < sw->min) {
                d = sw->min - rx;
                push[0] = d * c2;
                push[2] = -d * s2;
            }
            target[1] += push[1];
            target[0] += push[0];
            target[2] += push[2];
        }
        limit = (sw->limit + 0.0f) - dist3(parent, target) * 0.5f;
        d = dist3(target, parent);
        if (limit < d) {
            for (c = 0; c < 3; c++)
                target[c] = parent[c] + limit * (target[c] - parent[c]) / d;
        }
        func_001436C8(cur[3], target);
    }
    return r;
}

/* Writes a DMA tag (or any quadword) into the chain. */
static inline void dma_put(u32 a, u32 b, u32 c, u32 d)
{
    u32 *p = g_70000158;

    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    g_70000158_SET(p + 4);
}

/* Copies `n` words into the chain. */
static inline void dma_copy(const void *from, int n)
{
    const u32 *s = from;
    u32 *p = g_70000158;
    int i;

    for (i = 0; i < n; i++)
        p[i] = s[i];
    g_70000158_SET(p + n);
}

/* Starts an object's VU1 data for this frame: its packet (alpha, texture, node count) and its
 * node matrices, with their UNPACK headers (two when there are more than 256 quadwords). */
static inline void actor_begin(Actor *a, Model *m, u32 alpha)
{
    int frame = g_70000150;
    u32 *packet = a->packets[frame];
    u32 *buf = (u32 *)a->matrices[frame];
    u32 *head = buf + 3;
    u32 n = m->a * 4, qwc = n + 1, at = 0x14;

    packet[0xCC / 4] = alpha;
    *(u64 *)(packet + 8) = m->tex0;
    packet[0xC8 / 4] = m->a;
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    if (n > 0x100) {
        at = 0x114;
        qwc = n + 2;
        *head = 0x6C000014;
        buf[0x404] = 0;
        buf[0x405] = 0;
        buf[0x406] = 0;
        head = buf + 0x407;
    }
    *head = at | (n & 0xFF) << 16 | 0x6C000000;
    dma_put(0x3000000D, (u32)PS2_ADDR(packet), 0, 0);
    dma_put(qwc | 0x30000000, (u32)PS2_ADDR(a->matrices[frame]), 0, 0);
}

/* 0x0014F0C0, 0x1C bytes, matching. Draws an object, opaque. */
void func_0014F0E0(Actor *a, u32 alpha);

void func_0014F0C0(Actor *a)
{
    func_0014F0E0(a, 0x80);
}

/* 0x0014F0E0, 0x268 bytes. Draws an object with alpha `alpha`: its packet and matrices, the
 * texture's base and alpha for the models that use them (+0x2E), then the model's parts. */
void func_0014F0E0(Actor *a, u32 alpha)
{
    Model *m = ACTOR_MODEL(a);

    actor_begin(a, ACTOR_MODEL(a), alpha & 0xFF);
    if (m->flag2e == 0) {
        dma_put(0x10000000, 0, 0, 0x14000000);
    } else {
        dma_put(0x10000001, 0, 0, 0x6C010013);
        dma_put(0, (u32)(m->tex0 >> 32) & 0x7FFE0, 0, alpha & 0xFF);
    }
    func_00148460(m);
}

/* 0x0014F350, 0x158 bytes. The matrix projecting onto the plane `plane` (normal, distance)
 * along `light`: a planar shadow. */
void func_0014F350(float *out, const float *light, const float *plane)
{
    float d = plane[0] * light[0] + plane[1] * light[1] + plane[2] * light[2]
              + plane[3] * light[3];
    float inv = 1.0f / d;

    out[0] = inv * ((d + 0.0f) - plane[0] * light[0]);
    out[1] = light[1] * inv * -plane[0];
    out[2] = light[2] * inv * -plane[0];
    out[3] = 0.0f;
    out[4] = light[0] * inv * -plane[1];
    out[5] = inv * ((d + 0.0f) - plane[1] * light[1]);
    out[6] = light[2] * inv * -plane[1];
    out[7] = 0.0f;
    out[8] = light[0] * inv * -plane[2];
    out[9] = light[1] * inv * -plane[2];
    out[10] = inv * ((d + 0.0f) - plane[2] * light[2]);
    out[11] = 0.0f;
    out[12] = light[0] * inv * plane[3];
    out[13] = light[1] * inv * plane[3];
    out[14] = light[2] * inv * plane[3];
    out[15] = 1.0f;
}

/* 0x0014F4B0, 0x354 bytes. Draws an object's shadow on the plane through `point` with normal
 * `normal`, along `light`, in colour `colour` (RGBA; its alpha for the packet). */
void func_0014F4B0(Actor *a, const float *light, const float *normal, const float *point,
                   const u8 *colour)
{
    Model *m = ACTOR_MODEL(a);
    float plane[4], shadow[16];
    u32 *p;

    actor_begin(a, m, colour[3]);
    plane[0] = normal[0];
    plane[1] = normal[1];
    plane[2] = normal[2];
    plane[3] = normal[2] * point[2] + normal[0] * point[0] + normal[1] * point[1];
    func_0014F350(shadow, light, plane);
    dma_put(0x10000005, 0, 0, 0x6C05000B);
    dma_copy(shadow, 16);
    p = g_70000158;
    p[0] = colour[0];
    p[1] = colour[1];
    p[2] = colour[2];
    p[3] = colour[3];
    g_70000158_SET(p + 4);
    if (m->flag2e == 0) {
        dma_put(0x10000000, 0, 0, 0x14000000);
    } else {
        dma_put(0x10000001, 0, 0, 0x6C010013);
        dma_put(0, 0, 0, colour[3]);
    }
    func_001484E0(m);
}

/* 0x0014F810, 0x34 bytes. A node's matrix for this frame. */
float (*func_0014F810(Actor *a, u32 node))[4]
{
    return NODE_WORLD(&a->e[node & 0xFF], g_70000150);
}

/* 0x0014F850, 0x54 bytes. Clears a simple object (0x170 bytes) with a unit matrix at +0x120. */
void func_0014F850(u8 *o)
{
    func_001185E0(o, 0x170, 0);
    unit_matrix((float *)(o + 0x120));
}

/* 0x0014F8B0, 0x94 bytes, matching. Sets a simple object up for model `m`: two VU1 packets (0x90 bytes
 * each: TEX0_1, then an UNPACK of 5 quadwords), opaque. */
void func_0014F8B0(u32 *o, Model *m)
{
    int i;

    o[0x58] = (u32)PS2_ADDR(m);
    ((u8 *)o)[0x164] = 0x80;
    for (i = 0; i < 2; i++, o += 0x24) {
        o[0] = 0x11000000;
        o[1] = 0;
        o[2] = 0;
        o[3] = 0x50000002;
        *(u64 *)(o + 4) = 0x1000000000008001;
        *(u64 *)(o + 6) = 0xE;
        *(u64 *)(o + 8) = 0;
        *(u64 *)(o + 10) = 6;
        o[0xC] = 0;
        o[0xD] = 0;
        o[0xE] = 0;
        o[0xF] = 0x6C050013;
        o[0x10] = 0;
        o[0x11] = 0;
        o[0x12] = 0;
        o[0x13] = 0x80;
    }
}

/* 0x0014F950, 0x1C bytes, matching. */
void func_0014F950(u8 *o)
{
    func_0014F850(o);
}

/* Fills a simple object's packet for this frame: texture, its base, a node count (+0x165) and
 * alpha (+0x164), its matrix; then sends it. */
static inline void simple_begin(u8 *o)
{
    u8 *p = o + g_70000150 * 0x90;
    Model *m = *(Model **)(o + 0x160);

    *(u64 *)(p + 0x20) = m->tex0;
    *(u32 *)(p + 0x44) = (u32)(m->tex0 >> 32) & 0x7FFE0;
    *(u32 *)(p + 0x48) = o[0x165] << 2;
    *(u32 *)(p + 0x4C) = o[0x164];
    {
        int i;

        for (i = 0; i < 16; i++)
            ((u32 *)(p + 0x50))[i] = ((u32 *)(o + 0x120))[i];
    }
    dma_put(0x30000009, (u32)PS2_ADDR(p), 0, 0);
}

/* 0x0014F970, 0xD8 bytes. Draws a simple object. */
void func_0014F970(u8 *o)
{
    simple_begin(o);
    func_00148460(*(Model **)(o + 0x160));
}

/* 0x0014FA50, 0xD8 bytes. The same, each part after its VU1 header. */
void func_0014FA50(u8 *o)
{
    simple_begin(o);
    func_001484E0(*(Model **)(o + 0x160));
}

/* 0x0014FB30, 0x104 bytes. Sends the lights (directions, colours and ambient) to VU1. */
void func_0014FB30(u8 *dir, u8 *colour, void *ambient)
{
    float l[16], c[16];

    func_00143268(l, dir, dir + 0x10, dir + 0x20);
    func_00143328(c, colour, colour + 0x10, colour + 0x20, ambient);
    dma_put(0x10000008, 0, 0, 0x6C08000B);
    dma_copy(l, 16);
    dma_copy(c, 16);
}

/* 0x0014FC40, 0x60 bytes. Sends one quadword to VU1 address 0x12. */
void func_0014FC40(const u32 *v)
{
    dma_put(0x10000001, 0, 0, 0x6C010012);
    dma_copy(v, 4);
}

/* 0x0014FCA0, 0x8 bytes, matching. */
void func_0014FCA0(u8 *o, Model *m)
{
    *(Model **)(o + 0x160) = m;
}

extern u32 g_00406340[];                 /* a VU1 set-up packet (4 quadwords) */
extern struct {
    u32 a, b, c;             /* 0x0056CCD0 */
    float d;                 /* 0x0056CCDC */
} g_0056CCD0;
extern u8 g_0041FD00[], g_0041EC00[], g_00420E00[];   /* VU1 microprograms (MPG packets) */

/* 0x0014FCB0, 0x148 bytes. Sends a camera to VU1: the set-up packet, the fog / depth settings
 * (the camera's +0x210 scaled by 65525), its position (+0x1C0) and its matrix (+0x100). */
void func_0014FCB0(u8 *cam)
{
    dma_put(0x30000004, (u32)PS2_ADDR(g_00406340), 0x13000000, 0);
    g_0056CCD0.d = *(float *)(cam + 0x210);
    g_0056CCD0.d = g_0056CCD0.d * 65525.0f;
    dma_put(0x10000001, 0, 0, 0x6C010000);
    dma_copy(&g_0056CCD0, 4);
    dma_put(0x10000005, 0, 0, 0x6C050002);
    dma_copy(cam + 0x1C0, 4);
    dma_copy(cam + 0x100, 16);
}

/* 0x0014FE00, 0xA8 bytes. Loads the VU1 microprogram at 0x0041FD00 and starts it. */
void func_0014FE00(void)
{
    dma_put(0x3000010F, (u32)PS2_ADDR(g_0041FD00), 0x0300023C, 0x0200008B);
    dma_put(0x10000000, 0, 0, 0x1500000C);
}

/* 0x0014FEB0, 0xA8 bytes. Loads the VU1 microprogram at 0x0041EC00 and starts it. */
void func_0014FEB0(void)
{
    dma_put(0x30000106, (u32)PS2_ADDR(g_0041EC00), 0x0300023C, 0x0200008B);
    dma_put(0x10000000, 0, 0, 0x1500000C);
}

/* 0x0014FF60, 0x178 bytes. Sends a camera's two matrices (+0xC0 to VU1 address 3, +0x80 to 7),
 * then loads the microprogram at 0x00420E00 and starts it. */
void func_0014FF60(u8 *cam)
{
    dma_put(0x10000004, 0, 0, 0x6C040003);
    dma_copy(cam + 0xC0, 16);
    dma_put(0x10000004, 0, 0, 0x6C040007);
    dma_copy(cam + 0x80, 16);
    dma_put(0x30000111, (u32)PS2_ADDR(g_00420E00), 0x0300023C, 0x0200008B);
    dma_put(0x10000000, 0, 0, 0x1500000C);
}

u32 func_00100FE0(void);

/* Sends three GS register writes: TEST_1 `test`, ALPHA_1 = 0x44, ZBUF_1 (the game's Z buffer). */
static inline void gs_test_alpha_zbuf(u64 test)
{
    u64 *q;

    dma_put(0x10000004, 0, 0, 0x50000004);
    q = (u64 *)g_70000158;
    q[0] = 0x1000000000008003;
    q[1] = 0xE;
    q[2] = test;
    q[3] = 0x47;
    q[4] = 0x44;
    q[5] = 0x42;
    q[6] = (u64)func_00100FE0() | 0x3A000000;
    q[7] = 0x4E;
    g_70000158_SET((u32 *)(q + 8));
}

/* 0x001500E0, 0xD8 bytes. The depth and alpha tests, the alpha reference being `ref`. */
void func_001500E0(u32 ref)
{
    gs_test_alpha_zbuf((u64)(ref & 0xFF) << 4 | 0x5000B);
}

/* 0x001501C0, 0xCC bytes. The same with the alpha test off. */
void func_001501C0(void)
{
    gs_test_alpha_zbuf(0x5C00D);
}

/* The direction code of an angle (eight sectors, from behind round to the left). */
static inline u32 direction_code(float a)
{
    if (-2.7576203f < a && a <= -1.9896754f)
        return 0x18000000;
    if (-1.9896754f < a && a < -1.1519173f)
        return 0x10000000;
    if (-1.1519173f <= a && a < -0.38397247f)
        return 0x14000000;
    if (-0.38397247f <= a && a <= 0.38397247f)
        return 0x04000000;
    if (0.38397247f < a && a <= 1.1519173f)
        return 0x24000000;
    if (1.1519173f < a && a < 1.9896754f)
        return 0x20000000;
    if (1.9896754f <= a && a < 2.7576203f)
        return 0x28000000;
    return 0x08000000;
}

/* A direction's code relative to the camera's yaw (+0x54), 0 for a vertical one. */
static inline u32 camera_direction(u8 *cam, const float *dir)
{
    float a;

    if (!(0.0001f < fabsf(dir[0]) || 0.0001f < fabsf(dir[2])))
        return 0;
    a = vu0_angle(dir[0], dir[2]) - *(float *)(cam + 0x54);
    if (PI < a)
        a -= TWO_PI;
    else if (a < -PI)
        a += TWO_PI;
    return direction_code(a);
}

/* Stores a direction, normalised, at +0x1D0. */
static inline void camera_store_dir(u8 *cam, const float *dir)
{
    float len = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2] + dir[3] * dir[3]);
    float *to = (float *)(cam + 0x1D0);
    int i;

    for (i = 0; i < 4; i++)
        to[i] = dir[i] / len;
}

/* 0x00150290, 0x320 bytes. Sets a camera's light direction: its code relative to the camera
 * (with `flags`) at +0x13C, the direction normalised at +0x1D0. */
void func_00150290(u8 *cam, const float *dir, u32 flags)
{
    *(u32 *)(cam + 0x13C) = flags | camera_direction(cam, dir);
    camera_store_dir(cam, dir);
}

/* 0x001505B0, 0x334 bytes. The same, keeping the flags already there. */
void func_001505B0(u8 *cam, const float *dir)
{
    *(u32 *)(cam + 0x13C) &= 0x3FFFFFF;
    *(u32 *)(cam + 0x13C) |= camera_direction(cam, dir);
    camera_store_dir(cam, dir);
}
