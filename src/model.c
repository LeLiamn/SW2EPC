/*
 * model.c - motion curves, tm3 textures and 3D models (original source file unknown; this part
 * covers 0x00147780-0x00148784, after font.c; the model code goes on after it).
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
