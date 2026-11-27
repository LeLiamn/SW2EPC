/*
 * fld_event_cmd.c - the battlefield's queued event commands (camera targets, battle messages,
 * scenario calls) and the helpers that queue them. Original file name unknown; this code follows
 * emp_fld_base.c's unit placement (0x00355FE0-0x0035801C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * A command is 8 bytes: u16 kind (1-10, 0xB = free), then three u16 parameters. Up to 0x20 are
 * queued at 0x007B6B20; 0x007B6C20 is the next one to run and 0x007B6C21 the number queued.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 kind;
    u16 a, b, c;
} EvCmd;

extern EvCmd g_007B6B20[0x20];
extern u8 g_007B6C20, g_007B6C21;
extern u8 g_00693970[];                  /* the game state (unit records first, 0x88 bytes) */
extern u8 g_006A1D58[][0x68];            /* the soldier groups */
extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each) */
extern u8 *g_005BA6BC;                   /* the battle message texts */
extern u8 *g_005BA6C4[];                 /* the officers' line texts, by kind */
extern u8 *g_005BA7B4, *g_005BA7B8;      /* two more text tables */
extern u8 g_005BBF18[];                  /* the message formatter */
extern char g_005BBF20[];                /* the message text */
extern u32 g_005BC020, g_005BC028;       /* window kinds */
extern u32 g_005BC02C, g_005BC030, g_005BC034, g_005BC038, g_005BC03C, g_005BC048, g_005BC04C;
extern u32 g_005BC064;
extern u8 g_005BC3A0[];
extern u8 g_005BD740[8];                 /* scenario switches */
extern u32 g_005BD728[2];                /* the camera target (x, z) */
extern void (*g_00415628[])(u16 a, u16 b);   /* the scenario calls */
extern u8 g_00415640[0xC3];              /* the messages that also go to the log */
extern u32 g_00415708[3];
extern u32 g_0045D070, g_0045D074;       /* (small data) */
extern const char g_004480B8[], g_004480C0[], g_004480E8[], g_004480F0[];

#define UNIT(i) (g_00693970 + (i) * 0x88)
#define UNIT_INDEX(u) (((u8 *)(u) - g_00693970) / 0x88)
#define UNIT_FLAGS(u) (*(u32 *)((u) + 0x80))
#define TEXT(t, k) ((char *)(t) + *(int *)((t) + (k) * 4 + 4))

void func_00118AC0(void *to, const void *from, int size);
void func_00183670(float *pos);
int func_0034EC80(int k);
int func_0034EE50(u8 *b);
void func_0034ED90(u8 *b, u8 *out);
void func_0036F9D0(u32 a, u32 b, u32 c);
void func_0036FAE0(u32 a, u32 b);
void func_003F5610(u8 status);
void func_003DD710(char *to, u32 id);
void func_003DD730(char *out, u8 *group);
const char *func_00362A20(u32 side);
const char *func_003DD7D0(u32 id);
const char *func_00372D30(u32 id);
void func_00120928(char *to, const char *from);
void func_001204B0(char *to, const char *format, ...);
int func_001207E0(const char *a, const char *b);
char *func_0019B170(char *out, u32 t, u32 n);
void func_0022F120(u8 *f, char *out, const char *text, u32 ca, u32 cb);
void func_002C4AE0(u32 *a, char *text);
void func_0022EF90(u8 *box, u32 kind, int mode);

EvCmd *func_00356060(u32 k);
int func_00356EF0(void);
int func_00356D50(EvCmd *c);

/* 0x00355FE0, 0x68 bytes. Empties the queue. */
void func_00355FE0(void)
{
    EvCmd *c = func_00356060(0);
    u32 k;

    for (k = 0; k < 0x20; k++, c++)
        c->kind = 0xB;
    g_007B6C20 = 0;
    g_007B6C21 = 0;
}

/* 0x00356050, 8 bytes, matching. */
void func_00356050(void)
{
}

/* 0x00356060, 0x2C bytes. Command slot `k`. */
EvCmd *func_00356060(u32 k)
{
    return k < 0x20 ? &g_007B6B20[k] : 0;
}

/* 0x00356090, 0x38 bytes, matching. Loads the queue from a save image at `p`; the end of it. */
u8 *func_00356090(u8 *p)
{
    func_00118AC0(g_007B6B20, p, 0x102);
    return p + 0x102;
}

/* 0x003560D0, 0x34 bytes, matching. Saves it. */
u8 *func_003560D0(u8 *p)
{
    func_00118AC0(p, g_007B6B20, 0x102);
    return p + 0x102;
}

/* 0x00356110, 0xC0 bytes. Command 1: the camera looks at unit `a` (in use). */
void func_00356110(EvCmd *c)
{
    u8 *u = UNIT(c->a);
    u32 f = UNIT_FLAGS(u);
    u32 t[2];

    if ((f & 1) == 0 || (f & 0x8C40002) != 0)
        return;
    if ((*(u32 *)(u + 0x84) & 0x8000) != 0) {
        *(float *)&t[0] = -1.0f;
        *(float *)&t[1] = -1.0f;
    } else {
        u32 *p = (f & 0x20000) != 0 ? (u32 *)(u + 0x30) : (u32 *)(u + 0x28);

        t[0] = p[0];
        t[1] = p[1];
        func_00183670((float *)t);
    }
    g_005BD728[0] = t[0];
    g_005BD728[1] = t[1];
}

/* 0x003561D0, 0xC0 bytes. Command 2: the camera looks at base `a`. */
void func_003561D0(EvCmd *c)
{
    if (c->a < 0x14) {
        u8 *b = (u8 *)func_0034EC80(c->a);

        if (func_0034EE50(b) != 0) {
            u8 xy[2];
            float t[2];

            func_0034ED90(b, xy);
            t[0] = (float)xy[0] * 5000.0f + 2500.0f;
            t[1] = (float)xy[1] * 5000.0f + 2500.0f;
            func_00183670(t);
            g_005BD728[0] = *(u32 *)&t[0];
            g_005BD728[1] = *(u32 *)&t[1];
        }
    }
}

/* 0x00356290, 0x74 bytes. Command 3: the camera looks at sub-cell (`a`, `b`). */
void func_00356290(EvCmd *c)
{
    float t[2];

    t[0] = (float)(u8)c->a * 1000.0f + 500.0f;
    t[1] = (float)(u8)c->b * 1000.0f + 500.0f;
    func_00183670(t);
    g_005BD728[0] = *(u32 *)&t[0];
    g_005BD728[1] = *(u32 *)&t[1];
}

/* 0x00356310, 0x7C bytes. Command 4: the camera looks at cell (`a`, `b`). */
void func_00356310(EvCmd *c)
{
    float t[2];

    t[0] = (float)(u8)c->a * 5000.0f + 2500.0f;
    t[1] = (float)(u8)c->b * 5000.0f + 2500.0f;
    func_00183670(t);
    g_005BD728[0] = *(u32 *)&t[0];
    g_005BD728[1] = *(u32 *)&t[1];
}

/* 0x00356390, 0x30 bytes. */
void func_00356390(u32 v)
{
    func_0036F9D0(v & 0xF, (v & 0xF0) >> 4, (v & 0xF00) >> 8);
}

/* 0x003563C0, 0x28 bytes. */
void func_003563C0(u32 v)
{
    func_0036FAE0(v & 0xF, (v & 0xF0) >> 4);
}

/* 0x003563F0, 0x1C bytes. */
void func_003563F0(u16 v)
{
    func_003F5610(v);
}

/* 0x00356410, 0x3C bytes, matching. Command 5: scenario call `a` with (`b`, `c`). */
void func_00356410(EvCmd *c)
{
    g_00415628[c->a](c->b, c->c);
}

/* 0x00356450, 0x164 bytes. A message subject of kind `kind` (0 unit, 1 group, 2 side, 3 name,
 * 4 ..., 5 number) and id `id`: its text into `out`, its colour into `colour`. */
void func_00356450(u32 kind, u16 id, u32 *colour, char *out)
{
    switch (kind) {
    case 0:
        *colour = UNIT(id)[0x79];
        func_003DD710(out, id);
        break;
    case 1:
        *colour = (*(u8 **)g_006A1D58[id])[0x79];
        func_003DD730(out, g_006A1D58[id]);
        break;
    case 2:
        *colour = id;
        func_00120928(out, func_00362A20(id));
        break;
    case 3:
        *colour = 3;
        func_00120928(out, func_003DD7D0(id));
        break;
    case 4:
        *colour = 3;
        func_00120928(out, func_00372D30(id));
        break;
    case 5:
        *colour = 3;
        func_001204B0(out, g_004480B8, id);
        break;
    default:
        *colour = 3;
        func_00120928(out, g_004480C0);
        break;
    }
}

/* 0x003565C0, 0x54 bytes. Whether battle message `k` also goes to the log. */
u8 func_003565C0(u32 k)
{
    u8 t[0xC3 + 1];
    int i;

    for (i = 0; i < 0xC3; i++)
        t[i] = g_00415640[i];
    return k < 0xC3 ? t[k] : 0;
}

/* 0x00356620, 0x6C bytes. Puts an article before name `s` ("A %s" when `cap`, else "a %s"). */
void func_00356620(char *s, int cap)
{
    char buf[256];

    if (cap == 0) {
        func_001204B0(buf, g_004480F0, s);
        func_00120928(s, buf);
    } else {
        func_001204B0(buf, g_004480E8, s);
        func_00120928(s, buf);
    }
}

/* 0x00356690, 0xB8 bytes. For messages 0x1A-0x1C: the subjects named like the generic officer
 * get an article (the first one capitalised for message 0x1A). */
void func_00356690(int k, char *a, char *b)
{
    char buf[272];
    int cap = 0;

    if (k == 0x1A)
        cap = 1;
    else if (k != 0x1B && k != 0x1C)
        return;
    func_0019B170(buf, g_0045D070, g_0045D074);
    if (func_001207E0(a, buf) == 0)
        func_00356620(a, cap);
    if (func_001207E0(b, buf) == 0)
        func_00356620(b, 0);
}

/* 0x00356750, 0x110 bytes. Command 6: battle message `a & 0xFF` with two subjects (kinds in bits
 * 8-10 and 11-13, ids `b` and `c`). */
void func_00356750(EvCmd *c)
{
    u32 v = c->a, k = v & 0xFF, ca, cb;
    u16 ib = c->c;
    char a[32], b[32], buf[264];

    func_00356450((int)(v & 0x700) >> 8, c->b, &ca, a);
    func_00356450((int)(v & 0x3800) >> 0xB, ib, &cb, b);
    func_00356690(k, a, b);
    func_0022F120(g_005BBF18, buf, TEXT(g_005BA6BC, k), ca, cb);
    func_001204B0(g_005BBF20, buf, a, b);
    if (func_003565C0(k) != 0)
        func_002C4AE0(g_005BD728, g_005BBF20);
    g_005BC064 = 0;
    g_005BC04C = 0;
    func_0022EF90(g_005BC3A0, g_005BC020, 0);
}

/* 0x00356860, 0x13C bytes. Command 7: the same in one of three windows (bits 14-15). */
void func_00356860(EvCmd *c)
{
    u32 v = c->a, ca, cb;
    u16 ib = c->c;
    char a[32], b[32], buf[264];
    u32 kinds[4];

    kinds[0] = g_00415708[0];
    kinds[1] = g_00415708[1];
    kinds[2] = g_00415708[2];
    func_00356450((int)(v & 0x700) >> 8, c->b, &ca, a);
    func_00356450((int)(v & 0x3800) >> 0xB, ib, &cb, b);
    func_0022F120(g_005BBF18, buf, TEXT(g_005BA6BC, v & 0xFF), ca, cb);
    func_001204B0(g_005BBF20, buf, a, b);
    if (func_003565C0(v & 0xFF) != 0)
        func_002C4AE0(g_005BD728, g_005BBF20);
    g_005BC064 = 2;
    g_005BC04C = 0;
    func_0022EF90(g_005BC3A0, kinds[(int)(v & 0xC000) >> 0xE], 2);
}

/* 0x003569A0, 0x164 bytes. Command 8: officer line `a` spoken by unit `b` (flags `c`: bits 0-1,
 * 2 and 3). */
void func_003569A0(EvCmd *c)
{
    u32 fl = c->c;
    u8 *u = UNIT(c->b), *o = *(u8 **)(u + 8);
    int off = o - g_005BA6A0;
    u32 kind = o[5];
    char buf[256];

    if (kind > 0x21)
        kind -= 9;
    if (g_005BD740[0] != 0)
        return;
    func_0022F120(g_005BBF18, buf, TEXT(g_005BA6C4[kind], c->a), 0, 0);
    func_00120928(g_005BBF20, buf);
    g_005BC064 = 1;
    g_005BC034 = o[6];
    g_005BC048 = u[0x79];
    g_005BC02C = off / 0x2C;
    g_005BC030 = (int)(fl & 4) >> 2;
    g_005BC038 = fl & 3;
    g_005BC03C = (int)(fl & 8) >> 3;
    func_0022EF90(g_005BC3A0, g_005BC028, 1);
}

/* 0x00356B10, 0x118 bytes. Command 9: line `a` of table 0x005BA7B4 by officer `b & 0x3FFF` (side
 * in bits 14-15). */
void func_00356B10(EvCmd *c)
{
    u32 v = c->b, i = v & 0x3FFF, fl = c->c;
    u8 *o = g_005BA6A0 + i * 0x2C;
    char buf[256];

    if (g_005BD740[0] != 0)
        return;
    func_0022F120(g_005BBF18, buf, TEXT(g_005BA7B4, c->a), 0, 0);
    func_00120928(g_005BBF20, buf);
    g_005BC064 = 1;
    g_005BC034 = o[6];
    g_005BC038 = 0;
    g_005BC02C = i;
    g_005BC030 = (int)(fl & 4) >> 2;
    g_005BC03C = (int)(fl & 8) >> 3;
    g_005BC048 = (int)(v & 0xC000) >> 0xE;
    func_0022EF90(g_005BC3A0, g_005BC028, 1);
}

/* 0x00356C30, 0x118 bytes. Command 10: the same from table 0x005BA7B8. */
void func_00356C30(EvCmd *c)
{
    u32 v = c->b, i = v & 0x3FFF, fl = c->c;
    u8 *o = g_005BA6A0 + i * 0x2C;
    char buf[256];

    if (g_005BD740[0] != 0)
        return;
    func_0022F120(g_005BBF18, buf, TEXT(g_005BA7B8, c->a), 0, 0);
    func_00120928(g_005BBF20, buf);
    g_005BC064 = 1;
    g_005BC034 = o[6];
    g_005BC038 = 0;
    g_005BC02C = i;
    g_005BC030 = (int)(fl & 4) >> 2;
    g_005BC03C = (int)(fl & 8) >> 3;
    g_005BC048 = (int)(v & 0xC000) >> 0xE;
    func_0022EF90(g_005BC3A0, g_005BC028, 1);
}

/* 0x00356D50, 0xEC bytes, matching. Runs command `c` and frees its slot. */
int func_00356D50(EvCmd *c)
{
    switch (c->kind) {
    case 1:
        func_00356110(c);
        break;
    case 2:
        func_003561D0(c);
        break;
    case 3:
        func_00356290(c);
        break;
    case 4:
        func_00356310(c);
        break;
    case 5:
        func_00356410(c);
        break;
    case 6:
        func_00356750(c);
        break;
    case 7:
        func_00356860(c);
        break;
    case 8:
        func_003569A0(c);
        break;
    case 9:
        func_00356B10(c);
        break;
    case 10:
        func_00356C30(c);
        break;
    }
    c->kind = 0xB;
    return 1;
}

/* 0x00356E40, 0xAC bytes. Runs the next queued command; whether the queue is done. */
int func_00356E40(void)
{
    EvCmd *c;

    if (func_00356EF0() == 0)
        return 1;
    c = func_00356060(g_007B6C20);
    if (c->kind < 0xB) {
        func_00356D50(c);
        c->kind = 0xB;
    }
    if (++g_007B6C20 < g_007B6C21)
        return 0;
    g_007B6C20 = 0;
    g_007B6C21 = 0;
    return 1;
}

/* 0x00356EF0, 0x10 bytes. Whether commands are queued. */
int func_00356EF0(void)
{
    return g_007B6C21 != 0;
}

/* 0x00356F00, 0x14 bytes. Drops the queued commands. */
void func_00356F00(void)
{
    g_007B6C20 = 0;
    g_007B6C21 = 0;
}

/* 0x00356F20, 0x4C bytes. The first free slot (0x20 for none). */
u32 func_00356F20(void)
{
    EvCmd *c = func_00356060(0);
    u32 k;

    for (k = 0; k < 0x20; k++, c++) {
        if (c->kind > 10)
            return k;
    }
    return 0x20;
}

/* 0x00356F70, 0x60 bytes. Queues command `c`. */
void func_00356F70(EvCmd *c)
{
    u32 k = func_00356F20();

    if (k < 0x20) {
        func_00118AC0(func_00356060(k), c, 8);
        g_007B6C21++;
    }
}

/* 0x00356FD0, 0x28 bytes, matching. Queues "look at unit `i`". */
void func_00356FD0(u16 i)
{
    EvCmd c;

    c.kind = 1;
    c.a = i;
    func_00356F70(&c);
}

/* 0x00357000, 0x68 bytes. Queues "look at group `g`'s leader". */
void func_00357000(int g)
{
    func_00356FD0(UNIT_INDEX(*(u8 **)g_006A1D58[g]));
}

/* 0x00357070, 0x28 bytes, matching. Queues "look at base `b`". */
void func_00357070(u16 b)
{
    EvCmd c;

    c.kind = 2;
    c.a = b;
    func_00356F70(&c);
}

/* 0x003570A0, 0x30 bytes, matching. Queues scenario call `k` (`a`, `b`). */
void func_003570A0(u16 k, u16 a, u16 b)
{
    EvCmd c;

    c.kind = 5;
    c.a = k;
    c.b = a;
    c.c = b;
    func_00356F70(&c);
}

/* 0x003570D0, 0x40 bytes. Queues battle message `k` with subjects (`ka`, `a`) and (`kb`, `b`). */
void func_003570D0(u16 k, short ka, u16 a, short kb, u16 b)
{
    EvCmd c;

    c.a = kb << 0xB | k | ka << 8;
    c.kind = 6;
    c.b = a;
    c.c = b;
    func_00356F70(&c);
}

/* 0x00357110, 0x28 bytes, matching. */
void func_00357110(u16 k)
{
    func_003570D0(k, 6, 0, 6, 0);
}

/* 0x00357140, 0x28 bytes, matching. */
void func_00357140(u16 k, u16 a)
{
    func_003570D0(k, 0, a, 6, 0);
}

/* 0x00357170, 0x28 bytes, matching. */
void func_00357170(u16 k, u16 a)
{
    func_003570D0(k, 1, a, 6, 0);
}

/* 0x003571A0, 0x2C bytes, matching. */
void func_003571A0(u16 k, u16 a, u16 b)
{
    func_003570D0(k, 1, a, 1, b);
}

/* 0x003571D0, 0x28 bytes, matching. */
void func_003571D0(u16 k, u16 a)
{
    func_003570D0(k, 2, a, 6, 0);
}

/* 0x00357200, 0x28 bytes, matching. */
void func_00357200(u16 k, u16 a)
{
    func_003570D0(k, 3, a, 6, 0);
}

/* 0x00357230, 0x2C bytes, matching. */
void func_00357230(u16 k, u16 a, u16 b)
{
    func_003570D0(k, 4, a, 4, b);
}

/* 0x00357260, 0x2C bytes, matching. */
void func_00357260(u16 k, u16 a, u16 b)
{
    func_003570D0(k, 5, a, 5, b);
}

/* 0x00357290, 0x2C bytes, matching. */
void func_00357290(u16 k, u16 a, u16 b)
{
    func_003570D0(k, 1, a, 2, b);
}

/* 0x003572C0, 0x48 bytes. Queues battle message `k` in window `w`. */
void func_003572C0(u16 k, short w, short ka, u16 a, short kb, u16 b)
{
    EvCmd c;

    c.kind = 7;
    c.a = w << 0xE | kb << 0xB | k | ka << 8;
    c.b = a;
    c.c = b;
    func_00356F70(&c);
}

/* 0x00357310, 0x28 bytes, matching. */
void func_00357310(u16 k, short w)
{
    func_003572C0(k, w, 6, 0, 6, 0);
}

/* 0x00357340, 0x28 bytes, matching. */
void func_00357340(u16 k, short w, u16 a)
{
    func_003572C0(k, w, 1, a, 6, 0);
}

/* 0x00357370, 0x28 bytes, matching. */
void func_00357370(u16 k, short w, u16 a)
{
    func_003572C0(k, w, 5, a, 6, 0);
}

/* 0x003573A0, 0x78 bytes. Queues officer line `k` by unit `i` (`side` 2: the unit's side). */
void func_003573A0(u16 k, int i, u16 fl, int side, short e)
{
    EvCmd c;

    if (side == 2)
        side = UNIT(i)[0x79] != 0;
    c.kind = 8;
    c.c = e << 3 | fl | (u16)(side << 2);
    c.b = i;
    c.a = k;
    func_00356F70(&c);
}

/* 0x00357420, 0x68 bytes. The same by group `g`'s leader. */
void func_00357420(u16 k, int g, u16 fl, int side, short e)
{
    func_003573A0(k, UNIT_INDEX(*(u8 **)g_006A1D58[g]), fl, side, e);
}

/* 0x00357490, 0x44 bytes. Queues line `k` of table 0x005BA7B4 by officer `o`. */
void func_00357490(u16 k, u16 o, short s, short side, short e)
{
    EvCmd c;

    c.b = o | s << 0xE;
    c.c = side << 2 | e << 3;
    c.kind = 9;
    c.a = k;
    func_00356F70(&c);
}

/* 0x003574E0, 0x84 bytes. The same by unit `i`'s officer. */
void func_003574E0(u16 k, int i, int side, short e)
{
    u8 s = UNIT(i)[0x79];

    if (side == 2)
        side = s != 0;
    func_00357490(k, (*(u8 **)(UNIT(i) + 8) - g_005BA6A0) / 0x2C, s, side, e);
}

/* 0x00357570, 0x44 bytes. Queues line `k` of table 0x005BA7B8 by officer `o`. */
void func_00357570(u16 k, u16 o, short s, short side, short e)
{
    EvCmd c;

    c.b = o | s << 0xE;
    c.c = side << 2 | e << 3;
    c.kind = 10;
    c.a = k;
    func_00356F70(&c);
}

/* 0x003575C0, 0x84 bytes. The same by unit `i`'s officer. */
void func_003575C0(u16 k, int i, int side, short e)
{
    u8 s = UNIT(i)[0x79];

    if (side == 2)
        side = s != 0;
    func_00357570(k, (*(u8 **)(UNIT(i) + 8) - g_005BA6A0) / 0x2C, s, side, e);
}

/* 0x00357650, 0x68 bytes. The same by group `g`'s leader. */
void func_00357650(u16 k, int g, int side, short e)
{
    func_003575C0(k, UNIT_INDEX(*(u8 **)g_006A1D58[g]), side, e);
}

/* 0x003576C0, 0xAC bytes. Formats battle message `k` with two subjects into `out`. */
void func_003576C0(char *out, int k, u32 ka, u16 a, u32 kb, u16 b)
{
    char fmt[256], sa[32], sb[32];
    u8 f[344];
    u32 ca, cb;

    func_00356450(ka, a, &ca, sa);
    func_00356450(kb, b, &cb, sb);
    func_0022F120(f, fmt, TEXT(g_005BA6BC, k), ca, cb);
    func_001204B0(out, fmt, sa, sb);
}

/* The second queue (0x00357770-): 0x20 commands of 8 bytes at 0x007B6C30 (kind 0x31 = free). */

extern EvCmd g_007B6C30[0x20];
extern u8 g_00669D60[];                  /* the settings (+0x210: how the battle ended) */
extern u32 g_7000015C;                   /* (scratchpad) the random seed */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define BATTLE_END (*(int *)(g_00669D60 + 0x210))

EvCmd *func_003577E0(u32 k);
u8 **func_0033EF80(u32 i);
int func_0033CC20(u8 **g, u8 **h);
int func_0036D2E0(void);
int func_0033BD10(u8 **g);
int func_002F9C90(int f, int g);
int func_0033B3B0(u8 **g);
int func_0033B440(u8 **g);
int func_0033B4E0(u8 **g);
int func_0033B140(u8 **g);
u32 func_0033BA90(u8 **g);
u32 func_0033B740(u8 **g);
u8 **func_0035DD10(int p);
u8 **func_0033F110(u8 kind);

/* 0x00357770, 0x58 bytes. Empties the second queue. */
void func_00357770(void)
{
    EvCmd *c = func_003577E0(0);
    u32 k;

    for (k = 0; k < 0x20; k++, c++)
        c->kind = 0x31;
}

/* 0x003577D0, 8 bytes, matching. */
void func_003577D0(void)
{
}

/* 0x003577E0, 0x2C bytes. Its slot `k`. */
EvCmd *func_003577E0(u32 k)
{
    return k < 0x20 ? &g_007B6C30[k] : 0;
}

/* 0x00357810, 0x38 bytes, matching. Loads it from a save image. */
u8 *func_00357810(u8 *p)
{
    func_00118AC0(g_007B6C30, p, 0x100);
    return p + 0x100;
}

/* 0x00357850, 0x34 bytes, matching. Saves it. */
u8 *func_00357850(u8 *p)
{
    func_00118AC0(p, g_007B6C30, 0x100);
    return p + 0x100;
}

/* 0x00357890, 0x14C bytes. Another active group of `g`'s side that func_0033CC20 accepts (one at
 * random among them), else 0. */
u8 **func_00357890(u8 **g)
{
    u8 side = (*g)[0x79];
    u8 **best = 0;
    u32 k;

    for (k = 0; k < 0x10; k++) {
        u8 **h = func_0033EF80(k);
        u32 f;

        if (h == g || (((u32 *)h)[0x19] & 1) == 0)
            continue;
        f = UNIT_FLAGS(*h);
        if ((f & 0x30) != 0)
            continue;
        if ((f & 1) != 0 && (f & 0x8C40002) == 0 && (f & 4) == 0 && side == (*h)[0x79]
            && func_0033CC20(h, g) != 0 && (best == 0 || RANDOM() % 100 < 0x32))
            best = h;
    }
    return best;
}

/* 0x003579E0, 0x1C0 bytes. Whether group `a` should give way to group `b` (by the officers'
 * relation, then their kinds, then their ranks). */
int func_003579E0(u8 **a, u8 **b)
{
    if (func_0036D2E0() != 0) {
        int ia = func_0033BD10(a), ib = func_0033BD10(b);

        if (ia >= 0 && ia < 0x19 && ib >= 0 && ib < 0x19) {
            int r = func_002F9C90(ia, ib);

            if (r == 2)
                return 1;
            if (r == 3)
                return 0;
        }
    }
    if (func_0033B3B0(b) != 0)
        return func_0033B3B0(a) == 0;
    if (func_0033B440(b) != 0 || func_0033B4E0(b) != 0)
        return !(func_0033B3B0(a) != 0 || func_0033B440(a) != 0 || func_0033B4E0(a) != 0);
    if (func_0033B3B0(a) != 0)
        return 0;
    if (func_0033B440(a) != 0 || func_0033B4E0(a) != 0)
        return func_0033B3B0(b);
    if (func_0033B140(b) != 0)
        return 1;
    if (func_0033B140(a) != 0)
        return 0;
    return func_0033BA90(a) < func_0033BA90(b);
}

/* 0x00357BA0, 0x74 bytes, matching. Whether group `b` is far stronger than `a`. */
int func_00357BA0(u8 **a, u8 **b)
{
    if (func_0033BA90(a) + 10 < func_0033BA90(b))
        return 1;
    return func_0033B740(a) * 3 < func_0033B740(b);
}

/* 0x00357C20, 8 bytes, matching. */
void func_00357C20(void)
{
}

/* 0x00357C30, 0x5C bytes. The battle ends (message 0x75 when won, else 0x77). */
void func_00357C30(int won)
{
    if (won == 0) {
        func_00357110(0x77);
        BATTLE_END = 3;
    } else {
        func_00357110(0x75);
        BATTLE_END = 0;
    }
}

/* 0x00357C90, 0x94 bytes. The same with messages 0x73 / 0x74 (the player's group named). */
void func_00357C90(int won)
{
    if (won == 0) {
        u8 **g = func_0033F110(0);

        func_00357170(0x74, ((u8 *)g - g_006A1D58[0]) / 0x68 & 0xFFFF);
        BATTLE_END = 3;
    } else {
        func_00357110(0x73);
        BATTLE_END = 0;
    }
}

/* 0x00357D30, 0x94 bytes. The same (a second ending kind). */
void func_00357D30(int won)
{
    if (won == 0) {
        u8 **g = func_0033F110(0);

        func_00357170(0x74, ((u8 *)g - g_006A1D58[0]) / 0x68 & 0xFFFF);
        BATTLE_END = 3;
    } else {
        func_00357110(0x73);
        BATTLE_END = 0;
    }
}

/* 0x00357DD0, 0x94 bytes. The same with messages 0x78 / 0x79 (ending 4). */
void func_00357DD0(int won)
{
    if (won == 0) {
        u8 **g = func_0033F110(0);

        func_00357170(0x79, ((u8 *)g - g_006A1D58[0]) / 0x68 & 0xFFFF);
        BATTLE_END = 4;
    } else {
        func_00357110(0x78);
        BATTLE_END = 0;
    }
}

/* 0x00357E70, 0x88 bytes. An ending command: kind `a` (0-3), result `b`. */
void func_00357E70(EvCmd *c)
{
    u16 v = c->b;
    short k = c->a;

    if (k == 3)
        func_00357DD0(v);
    else if (k == 2)
        func_00357D30(v);
    else if (k == 1)
        func_00357C90(v);
    else if (k == 0)
        func_00357C30(v);
}

/* 0x00357F00, 0x118 bytes. Now and then (30% below 50, 10% below 100 of the player's strength)
 * group `g`'s leader comments on meeting player `p` (lines 0x59 / 0x5A). */
void func_00357F00(int p, u8 **g)
{
    u8 **pg = func_0035DD10(p);
    u32 m = 0x5C, chance = 0, v = func_0033B740(pg);

    if (v < 0x32)
        chance = 0x1E;
    else if (v < 100)
        chance = 10;
    if (RANDOM() % 100 < chance)
        m = func_003579E0(g, pg) != 0 ? 0x59 : 0x5A;
    if (m < 0x5C)
        func_00357420(m, ((u8 *)g - g_006A1D58[0]) / 0x68, 0, 2, 0);
}
