/*
 * model.c - motion curves, tm3 textures and 3D models (original source file unknown; 0x00147780-
 * 0x00149724, after font.c; the drawing function at 0x00149730 follows).
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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define g_70000158 (*(u32 **)0x70000158)         /* the DMA chain's write cursor */

/* A motion being played (camera). */
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
    u8 colour[6];            /* +0x28 */
    u8 pad2;
    u8 alpha;                /* +0x2F */
} Model;

extern u8 g_004062F0[];                  /* the VU1 header for parts of kind 4 */
extern u8 g_00406310[];                  /* the VU1 header for the others */

void func_001185E0(void *to, u32 n, u8 c);   /* memset */
void func_00118850(void *to, u32 n);          /* clear */
void *func_00102DB0(int align, u32 size);
void *func_00102D30(u32 size);
void *func_0020EC50(u32 size);
void func_00102EC0(void *data);
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

    out[0] = (u32)motion;
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
    func_00102EC0((void *)state[0]);
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
        func_001185E0(out, 0x20, 0);
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
    func_00102EC0((void *)t[0]);
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
    g_70000158 = d + 4;
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
    g_70000158 = d + 12;
}

/* 0x00147F70, 0xFC bytes. Sends palette `frame` and the pixels of a tm3 texture, then a
 * TEXFLUSH. */
void func_00147F70(Tm3 *t, int frame)
{
    send_ref(t->palette_qwc[0], (u32)t->palette[frame]);
    send_ref(t->qwc, (u32)t->data);
    send_texflush();
}

/* 0x00148070, 0xC0 bytes. Sends palette `frame` only, then a TEXFLUSH. */
void func_00148070(Tm3 *t, int frame)
{
    send_ref(t->palette_qwc[0], (u32)t->palette[frame]);
    send_texflush();
}

/* 0x00148130, 0x20 bytes, matching. Clears a model. */
void func_00148130(Model *m)
{
    func_001185E0(m, 0x30, 0);
}

/* 0x00148150, 0x198 bytes. Sets a model's parts up: the file's offsets become pointers, each
 * part's packets get the texture's base, and each part its VU1 header. */
void func_00148150(Model *m)
{
    u32 *f = m->file;
    u32 *list, *p;
    ModelPart *part;
    u32 i, n;

    f[1] += (u32)f;
    list = (u32 *)(f[2] + (u32)f);
    f[2] = (u32)list;
    m->count = list[0];
    part = func_00102DB0(0x10, list[0] << 4);
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
    func_00102EC0(m->parts);
    m->parts = 0;
    func_00102EC0(m->file);
    m->file = 0;
    func_00148130(m);
}

/* 0x001483B0, 0x34 bytes, matching. Frees a model (its file kept). */
void func_001483B0(Model *m)
{
    func_00102EC0(m->parts);
    m->parts = 0;
    func_00148130(m);
}

/* 0x001483F0, 0x24 bytes, matching. Sets a model's colours. */
void func_001483F0(Model *m, u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    m->colour[0] = a;
    m->colour[1] = b;
    m->colour[2] = c;
    m->colour[3] = d;
    m->colour[4] = e;
    m->colour[5] = f;
    m->alpha = 100;
}

/* 0x00148420, 0x40 bytes, matching. Gives a model a tm3 texture (its colours copied from the texture's
 * bytes at +0x90). */
void func_00148420(Model *m, Tm3 *t)
{
    u8 *b = (u8 *)&t->tex0;

    m->texture = t;
    m->colour[0] = b[0];
    m->colour[1] = b[1];
    m->colour[2] = b[2];
    m->colour[3] = b[3];
    m->colour[4] = b[4];
    m->colour[5] = b[5];
    m->alpha = t->b;
}

/* 0x00148460, 0x80 bytes. Sends a model's parts. */
void func_00148460(Model *m)
{
    ModelPart *part = m->parts;
    u32 i;

    for (i = 0; i < m->count; i++, part++) {
        if (part->qwc != 0)
            send_ref(part->qwc, (u32)part->data);
    }
}

/* 0x001484E0, 0xB8 bytes. Sends a model's parts, each after its VU1 header. */
void func_001484E0(Model *m)
{
    ModelPart *part = m->parts;
    u32 i;

    for (i = 0; i < m->count; i++, part++) {
        if (part->qwc != 0) {
            send_ref(2, (u32)part->header);
            send_ref(part->qwc, (u32)part->data);
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
    u8 flags;                /* +0x20C */
    u8 pad2[3];
    u8 transforms[0x10];     /* +0x210 */
} Actor;

void func_00143268(void *m, void *a, void *b, void *c);           /* sceVu0NormalLightMatrix? */
void func_00143328(void *m, void *a, void *b, void *c, void *d);  /* sceVu0LightColorMatrix? */

/* A node's local matrix from its rotation and translation (VU0 micro subroutine 0x50). */
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
    u8 first = ((u8 *)m)[0x2C];
    Node *n = &a->nodes[first];
    u32 *trs = m->nodes_trs + first * 9;
    int i;

    for (i = 0; i < ((u8 *)m)[0x2D]; i++, n++, trs += 9) {
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
    a->slots = func_00102DB0(0x10, a->count << 4);
    a->nodes = func_00102DB0(0x10, a->count * 0x70);
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
    a->slots = func_00102DB0(0x10, a->count << 4);
    a->nodes = func_00102DB0(0x10, a->count * 0x70);
    if (count2 == 0)
        a->nodes2 = 0;
    else
        a->nodes2 = func_00102DB0(0x10, count2 * 0x70);
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
    func_00102EC0(a->slots);
    a->slots = 0;
    func_00102EC0(a->nodes);
    a->nodes = 0;
    if (a->nodes2 != 0) {
        func_00102EC0(a->nodes2);
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

/* 0x00149620, 0xF4 bytes. Changes an object's models; the nodes are rebuilt when the node count
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
            a->flags &= ~2;
        if (rebuild)
            func_00148790(a, m, m2);
        else if (m2 == 0)
            func_00148790(a, m, m2);
        a->e = a->nodes;
    }
    a->d = 0;
    a->flags &= ~8;
}

/* 0x00149720, 0x8 bytes, matching. */
void func_00149720(Actor *a)
{
    a->d = 0;
}
