/*
 * fld_event_cmd.c - the battlefield's queued event commands (camera targets, battle messages,
 * scenario calls) and the helpers that queue them. Original file name unknown; this code follows
 * emp_fld_base.c's unit placement (0x00355FE0-0x0035D55C).
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

extern int g_00669F9C;                   /* the battle's frame counter */

#define GROUP(i) ((u8 **)g_006A1D58[i])
#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)
#define SIDE_STATE(s) (g_00693970 + 0x16C84 + (s) * 0x10)

/* Whether unit `u` is active (in use, not down or leaving, without flag 4). */
#define UNIT_ACTIVE(u) ((UNIT_FLAGS(u) & 1) != 0 && (UNIT_FLAGS(u) & 0x8C40002) == 0 \
                        && (UNIT_FLAGS(u) & 4) == 0)

u32 func_0035DCB0(int p);
u32 func_0033BFD0(u8 **g);
int func_0033B150(u8 **g);
int func_0033CD90(u8 **g);
int func_0033B050(u8 **g);
int func_0033B090(u8 **g);
u8 **func_0033D0B0(u8 **g);
u8 *func_0034A740(u8 *u);
int func_00362F40(u32 side, u32 k);
u32 func_0035F520(u32 side);
u32 func_0035F200(int side);
void func_0033DDC0(u8 **g, u8 *cell);
u32 func_0035F0C0(void);
int func_0035D5A0(int side);
void func_0033DF10(u8 **g, int side);
int func_00361540(u32 side);
void func_0035F560(u32 side, int n);
u8 **func_0033F0C0(u32 side, u32 k);
int func_0036F390(u32 side, int k);
int func_0034B5D0(u8 *st, int a, int b);
void func_003701E0(u32 g, int a, int b, int c);

/* 0x00358020, 0x1B4 bytes. Player `p` meets side 1's group `g`: its leader's greeting (0xB, or
 * 0xB-0xD for officer kinds 0x1C-0x21), then the player's group comments (0x30, 0x38-0x3A). */
void func_00358020(int p, u8 **g)
{
    u32 pg = func_0035DCB0(p), kind = func_0033BFD0(g), m;
    int line = 0xB;

    if (kind > 0x21)
        kind -= 9;
    if (kind > 0x1B && kind < 0x22)
        line = RANDOM() % 3 + 0xB;
    func_00357420(line, GROUP_INDEX(g), 0, 2, 0);
    m = 0x5C;
    if (func_0033B150(g) == 0) {
        if (func_0033CD90(g) == 0)
            m = RANDOM() % 100 < 0x32 ? 0x38 : 0x39;
        else
            m = func_00357BA0(func_0035DD10(p), g) != 0 ? 0x3A : 0x30;
    }
    if (m < 0x5C)
        func_00357420(m, pg, 0, 2, 0);
}

/* 0x003581E0, 0xC8 bytes. Command: player `a` meets group `b` (when active). */
void func_003581E0(EvCmd *c)
{
    u8 **g = GROUP(c->b), *u = *g;

    if (!UNIT_ACTIVE(u))
        return;
    if (u[0x79] == 0)
        func_00357F00(c->a, g);
    else
        func_00358020(c->a, g);
}

/* 0x003582B0, 0xD4 bytes. The message after group `g` beat group `h` (0x1D / 0x1E, or 0x1F
 * naming both). */
void func_003582B0(u8 **g, u8 **h)
{
    u32 hi = GROUP_INDEX(h);

    if (func_0033B050(h) != 0)
        return;
    if (func_0033B090(g) != 0) {
        if ((*g)[0x79] == 0)
            func_00357170(0x1D, hi & 0xFFFF);
        else
            func_00357170(0x1E, hi & 0xFFFF);
    } else {
        func_003571A0(0x1F, GROUP_INDEX(g) & 0xFFFF, hi & 0xFFFF);
    }
}

/* 0x00358390, 0xCC bytes. Another group of `g`'s side comments on its defeat (0x41 / 0x42). */
void func_00358390(u8 **g)
{
    u8 **h = func_00357890(g);

    if (h == 0)
        return;
    if (func_003579E0(h, g) == 0)
        func_00357420(0x42, GROUP_INDEX(h), 1, 2, 0);
    else
        func_00357420(0x41, GROUP_INDEX(h), 1, 2, 0);
}

/* 0x00358460, 0x26C bytes. Command: group `a` defeated group `b`'s leader. */
void func_00358460(EvCmd *c)
{
    u32 ai = c->a, bi = c->b;
    u8 **g = GROUP(ai), **h = GROUP(bi);
    u8 *gu = *g, *hu = *h;
    u8 **by = func_0033D0B0(h);

    if ((*h)[0x79] == 1) {
        func_00357420(0x22, bi, 3, 2, 0);
    } else if (func_0033B050(g) != 0 && (UNIT_FLAGS(gu) & 0x20000) != 0) {
        func_00357420(0, ai, 1, 2, 0);
    } else if ((UNIT_FLAGS(hu) & 0x20000) == 0) {
        func_00357420(0x27, bi, 3, 2, 0);
    } else if (func_003579E0(h, by) == 0) {
        func_00357420(0x2A, bi, 3, 2, 0);
    } else {
        func_00357420(0x29, bi, 3, 2, 0);
    }
    func_00357000(ai);
    func_003582B0(g, h);
    if (func_0033B150(h) == 0) {
        if ((*h)[0x79] == 0)
            func_00357170(0x71, bi & 0xFFFF);
        else
            func_00357170(0x83, bi & 0xFFFF);
    }
    if (func_0033B150(h) == 0 && (UNIT_FLAGS(*g) & 0x30) != 0)
        func_00358390(g);
}

/* 0x003586D0, 0x1A8 bytes. Command: group `a`'s leader withdrew from group `b`. */
void func_003586D0(EvCmd *c)
{
    u32 ai = c->a, bi = c->b;
    u8 **g = GROUP(ai), *gu = *g;

    if (gu[0x79] == 0)
        func_00357420(0x28, bi, 3, 2, 0);
    if (func_0033B050(g) != 0 && (UNIT_FLAGS(gu) & 0x20000) != 0)
        func_00357420(0x23, ai, 1, 2, 0);
    func_00357000(ai);
    func_003582B0(g, GROUP(bi));
    if ((*g)[0x79] == 0)
        func_00357170(0x7A, bi & 0xFFFF);
    else
        func_00357170(0x7B, bi & 0xFFFF);
    if (func_0033B150(GROUP(bi)) == 0 && (UNIT_FLAGS(*g) & 0x30) != 0)
        func_00358390(g);
}

/* 0x00358880, 0x88 bytes. Side `side`'s commander group when active, else 0. */
u8 **func_00358880(u8 side)
{
    u8 **g = func_0033F110(side);

    if (!UNIT_ACTIVE(*g))
        return 0;
    return g;
}

/* 0x00358910, 0x248 bytes. Command: unit `c` took base `a` (how: byte `b`, 0-3). */
void func_00358910(EvCmd *c)
{
    u16 ui = c->c, b = c->a;
    u8 how = (u8)c->b;
    u8 *u = UNIT(ui);
    u8 **g = (u8 **)func_0034A740(u);
    u32 m = 0xC3;

    if ((UNIT_FLAGS(u) & 0x30) != 0)
        func_003573A0(0x24, ui, 0, 2, 0);
    func_00357070(b);
    if (how == 3)
        m = 0x1A;
    else if (how == 1)
        m = 0x1C;
    else if (how == 0)
        m = 0x1B;
    if (m < 0xC3)
        func_00357140(m, ui);
    if (how == 1) {
        u8 **h;

        if ((UNIT_FLAGS(u) & 0x30) != 0 && (h = func_00357890(g)) != 0) {
            if (func_003579E0(h, g) == 0)
                func_00357420(0x26, GROUP_INDEX(h) & 0xFFFF, 1, 2, 0);
            else
                func_00357420(0x25, GROUP_INDEX(h) & 0xFFFF, 1, 2, 0);
        }
        h = func_00358880(1);
        if (h != 0 && RANDOM() % 100 < 0x1E)
            func_00357420(0x2B, GROUP_INDEX(h), 3, 2, 0);
    }
}

/* 0x00358B60, 0xD4 bytes. Command: group `a` was beaten (when still active). */
void func_00358B60(EvCmd *c)
{
    u16 ai = c->a;

    if (!UNIT_ACTIVE(*GROUP(ai)))
        return;
    func_00357420(4, ai, 0, 2, 0);
    func_00357000(ai);
    func_00357170(0x72, ai);
}

/* 0x00358C40, 0x164 bytes. Command: group `a` attacks group `b` of the other side. */
void func_00358C40(EvCmd *c)
{
    u16 ai = c->a, bi = c->b;
    u8 *gu = *GROUP(ai), *hu;

    if (!UNIT_ACTIVE(gu))
        return;
    hu = *GROUP(bi);
    if (UNIT_ACTIVE(hu) && gu[0x79] != hu[0x79]) {
        func_00357000(ai);
        func_003571A0(0x14, ai, bi);
    }
}

/* 0x00358DB0, 0x5C bytes. Command: group `a` (`b`: 0x15 / 0x16). */
void func_00358DB0(EvCmd *c)
{
    u16 ai = c->a;
    short v = c->b;

    func_00357000(ai);
    if (v == 0)
        func_00357170(0x16, ai);
    else
        func_00357170(0x15, ai);
}

/* 0x00358E10, 0x40 bytes. Command: side `a` (`b`: 0x17 / 0x18). */
void func_00358E10(EvCmd *c)
{
    if ((short)c->b == 0)
        func_003571D0(0x18, c->a);
    else
        func_003571D0(0x17, c->a);
}

/* 0x00358E50, 0xB8 bytes. Side `side`'s first hidden reserve group (6-8) still waiting. */
u8 **func_00358E50(u32 side)
{
    u32 k;

    if (side >= 2)
        return 0;
    for (k = 6; k < 9; k++) {
        u8 **g = func_0033EF80(side * 8 + k);

        if ((((u32 *)g)[0x19] & 1) != 0 && (UNIT_FLAGS(*g) & 0x40000) != 0
            && func_00362F40(side, k) == 0)
            return g;
    }
    return 0;
}

/* 0x00358F10, 0xB8 bytes. Command: side `a`'s reserve arrives at its base (0x21 / 0x22). */
void func_00358F10(EvCmd *c)
{
    u16 s = c->a;
    u32 b = func_0035F520(s);
    u8 **g = func_00358E50(s);

    if (g != 0 && s < 2 && b < 0x14) {
        func_00357070(b);
        func_00357170(0x21, GROUP_INDEX(g) & 0xFFFF);
        func_003571D0(0x22, s);
    }
}

/* 0x00358FD0, 0x198 bytes. Command: side `a`'s hidden groups (6-7) set out for its main base
 * when it has no reserve base. */
void func_00358FD0(EvCmd *c)
{
    u32 s = c->a, k;
    u8 cell[4];

    if (func_0035F520(s) <= 0x13)
        return;
    func_0034ED90((u8 *)func_0034EC80(func_0035F200(s)), cell);
    for (k = 6; k < 8; k++) {
        u8 **g = func_0033EF80(s * 8 + k);

        if ((((u32 *)g)[0x19] & 1) != 0 && (UNIT_FLAGS(*g) & 0x40000) != 0
            && func_00362F40(s, k) == 0) {
            func_0033DDC0(g, cell);
            if (s == func_0035F0C0())
                func_00357420(0x2D, GROUP_INDEX(g), 0, 2, 0);
            else
                func_00357420(0x2C, GROUP_INDEX(g), 0, 2, 0);
            func_00357000(GROUP_INDEX(g));
            func_00357170(0x25, GROUP_INDEX(g) & 0xFFFF);
        }
    }
}

/* 0x00359170, 0x80 bytes. Command: side `a`'s reserve is ready (0x23 / 0x24). */
void func_00359170(EvCmd *c)
{
    short s = c->a;
    u8 **g = func_00358E50(s);

    if (g == 0)
        return;
    if (s == 0)
        func_00357110(0x23);
    else
        func_00357170(0x24, GROUP_INDEX(g) & 0xFFFF);
}

/* 0x003591F0, 0x154 bytes. Command: group `a` turns against its side. */
void func_003591F0(EvCmd *c)
{
    u16 ai = c->a;
    u8 **g;
    u8 side;
    u32 i;

    if (ai >= 0x47)
        return;
    g = GROUP(ai);
    if (g == 0 || (((u32 *)g)[0x19] & 1) == 0 || !UNIT_ACTIVE(*g))
        return;
    side = (*g)[0x79];
    func_0033F110(side);
    func_0033DF10(g, func_0035D5A0(side));
    i = GROUP_INDEX(g);
    func_00357420(0x2F, i, 0, 2, 0);
    func_00357000(i);
    func_00357290(0x5E, i & 0xFFFF, side);
}

/* 0x00359350, 0x264 bytes. Command: side `a`'s reinforcements (when none, a wait of
 * frames/3000 + 1-3). */
void func_00359350(EvCmd *c)
{
    u32 s = c->a, k;
    u8 **g;

    if (s >= 2)
        return;
    if (func_00361540(s) == 0) {
        func_0035F560(s, g_00669F9C / 3000 + RANDOM() % 3 + 1);
        return;
    }
    g = func_0033F0C0(s, 0);
    if (s == func_0035F0C0())
        func_00357650(1, GROUP_INDEX(g), 2, 0);
    else
        func_00357650(0, GROUP_INDEX(g), 2, 0);
    for (k = 0; k < 3; k++) {
        u8 **h = func_0033F0C0(s, k);

        if (UNIT_ACTIVE(*h))
            func_00357000(GROUP_INDEX(h));
    }
    if (func_0036F390(s, 4) != 0)
        func_00357170(0x20, GROUP_INDEX(func_0033F110(s)) & 0xFFFF);
}

/* 0x003595C0, 0xA4 bytes, matching. Side 1's commander heads for its main base. */
void func_003595C0(void)
{
    u8 **g = func_0033F110(1);
    u8 cell[4];
    u32 i;

    func_0034ED90((u8 *)func_0034EC80(func_0035F200(1)), cell);
    func_0033DDC0(g, cell);
    i = GROUP_INDEX(g);
    func_00357420(0x2E, i, 0, 2, 0);
    func_00357000(i);
    func_00357170(0x68, i & 0xFFFF);
}

/* 0x00359670, 0x6C bytes, matching. Command: player `a` fell (battle lost). */
void func_00359670(EvCmd *c)
{
    u8 **g = func_0035DD10(c->a);

    func_00357420(0x1D, GROUP_INDEX(g) & 0xFFFF, 3, 2, 0);
    BATTLE_END = 3;
}

/* 0x003596E0, 0x134 bytes. Command: group `a`'s side gets order `b` (0-3; lines 0x1E-0x21). */
void func_003596E0(EvCmd *c)
{
    short v = c->b;
    u32 i = c->a;
    u8 **g = GROUP(i), *st;
    u32 m = 0x5C;

    if (g == 0)
        return;
    st = SIDE_STATE((*g)[0x79]);
    if (st == 0)
        return;
    if (v == 3) {
        func_0034B5D0(st, 3, 0xFF);
        m = 0x21;
    } else if (v == 2) {
        func_0034B5D0(st, 2, 0xFF);
        m = 0x20;
    } else if (v == 1) {
        func_0034B5D0(st, 1, 0xFF);
        m = 0x1F;
    } else if (v == 0) {
        func_0034B5D0(st, 0, 0xFF);
        m = 0x1E;
    }
    if (m < 0x5C)
        func_00357420(m, i, 0, 2, 0);
}

/* 0x00359820, 0x104 bytes. Whether group `g` is active (and group `h` too when given). */
int func_00359820(u8 **g, u8 **h)
{
    if (g == 0 || (((u32 *)g)[0x19] & 1) == 0 || !UNIT_ACTIVE(*g))
        return 0;
    if (h != 0 && !UNIT_ACTIVE(*h))
        return 0;
    return 1;
}

/* 0x00359930, 0xB0 bytes. Command: group `a` (in state 2) gets order 0 (lines 0x55, 0x5F). */
void func_00359930(EvCmd *c)
{
    u16 i = c->a;
    u8 **g = GROUP(i);

    if (func_00359820(g, 0) != 0 && (*g)[0x7A] == 2) {
        func_003701E0(i, 0, 1, 0xFF);
        func_00357420(0x55, i, 0, 2, 0);
        func_00357000(i);
        func_00357170(0x5F, i);
    }
}

/* 0x003599E0, 0xB0 bytes. The same with order 1 (lines 0x53, 0x60). */
void func_003599E0(EvCmd *c)
{
    u16 i = c->a;
    u8 **g = GROUP(i);

    if (func_00359820(g, 0) != 0 && (*g)[0x7A] == 2) {
        func_003701E0(i, 1, 1, 0xFF);
        func_00357420(0x53, i, 0, 2, 0);
        func_00357000(i);
        func_00357170(0x60, i);
    }
}

/* The battle officers (0x8F records of 0xC0 bytes at 0x00693970 + 0x100C0): +0x10 its unit,
 * +0x14 its model, +0x80 / +0x82 / +0x84 most life, life, highest life, +0xB8 flags. */
#define OFFICER(k) (g_00693970 + 0x100C0 + (k) * 0xC0)

extern void (*g_00415720[10])(int side, u32 g);   /* order replies, by order 0x15-0x1E */
extern void (*g_00415750[10])(int won);           /* side order replies */
extern u32 g_00415780[4], g_00415790[3];

u8 *func_00338410(u32 g);
u32 func_0036DD30(u32 side, u32 order);
void func_0036DF30(u32 side, u32 order);
int func_0034EDB0(u8 *b);
u8 *func_00352850(u8 *b, int side);
int func_003B0370(u8 *o, u8 *b);
void func_0024D3A0(int kind, int model, int first);
u32 func_00362570(void);
u32 func_00361F50(void);
u32 func_00361E90(void);
int func_0036D310(void);
u32 func_003615C0(int side);
u8 **func_0033F020(u32 side, u32 k);

/* 0x00359A90, 0x98 bytes. The same with order 2 (lines 0x54, 0x61). */
void func_00359A90(EvCmd *c)
{
    u16 i = c->a;

    if (func_00359820(GROUP(i), 0) != 0) {
        func_003701E0(i, 2, 1, 0xFF);
        func_00357420(0x54, i, 0, 2, 0);
        func_00357000(i);
        func_00357170(0x61, i);
    }
}

/* 0x00359B30, 0x1D8 bytes. Command: group `a` ordered to deal with group `b` (`c`: 0 attack, else
 * help) when `b`'s strength is above 70. */
void func_00359B30(EvCmd *c)
{
    u16 ai = c->a, bi = c->b;
    short how = c->c;
    u8 **h = GROUP(bi);

    if (func_00359820(GROUP(ai), h) == 0 || func_00338410(bi)[0x2A] <= 0x46)
        return;
    func_003701E0(ai, 3, how, bi);
    func_00357420(0x56, ai, 0, 2, 0);
    if (how == 0)
        func_00357420(0x58, bi, 0, 2, 0);
    else
        func_00357420(0x57, bi, 2, 2, 0);
    func_00357000(ai);
    func_00357170(0x62, ai);
    if (how == 0) {
        if ((*h)[0x79] == 1)
            func_003571A0(100, ai, bi);
        else
            func_003571A0(0x87, ai, bi);
    } else if ((*h)[0x79] == 1) {
        func_00357170(99, bi);
    } else {
        func_00357170(0x86, bi);
    }
}

/* 0x00359D10-0x0035A060: the order replies (by side 0 / 1). */
/* 0x00359D10, 0x5C bytes. */
void func_00359D10(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x26 : 0x27, g & 0xFFFF);
}

/* 0x00359D70, 0x5C bytes. */
void func_00359D70(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x28 : 0x29, g & 0xFFFF);
}

/* 0x00359DD0, 0x5C bytes. */
void func_00359DD0(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x2A : 0x2B, g & 0xFFFF);
}

/* 0x00359E30, 0x5C bytes. */
void func_00359E30(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x2C : 0x84, g & 0xFFFF);
}

/* 0x00359E90, 0x5C bytes. */
void func_00359E90(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x2D : 0x85, g & 0xFFFF);
}

/* 0x00359EF0, 0x5C bytes. */
void func_00359EF0(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x2E : 0x2F, g & 0xFFFF);
}

/* 0x00359F50, 0x5C bytes. */
void func_00359F50(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x32 : 0x33, g & 0xFFFF);
}

/* 0x00359FB0, 0x5C bytes. */
void func_00359FB0(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x30 : 0x31, g & 0xFFFF);
}

/* 0x0035A010, 0x48 bytes, matching. */
void func_0035A010(int side, u32 g)
{
    func_00357000(g);
    if (side == 0)
        func_00357110(0x34);
    else
        func_00357110(0x7D);
}

/* 0x0035A060, 0x5C bytes. */
void func_0035A060(int side, u32 g)
{
    func_00357000(g);
    func_00357170(side == 0 ? 0x7F : 0x80, g & 0xFFFF);
}

/* 0x0035A0C0, 0x1D0 bytes. Command: side `a` gives order `b` to its group `c` (refused when the
 * group is not active or not of that side). */
void func_0035A0C0(EvCmd *c)
{
    void (*t[10])(int, u32);
    u32 s = c->a, o = c->b, gi = c->c, k;
    u8 *u;

    for (k = 0; k < 10; k++)
        t[k] = g_00415720[k];
    u = *GROUP(gi);
    if (!UNIT_ACTIVE(u) || s != u[0x79]) {
        func_0036DF30(s, o);
        return;
    }
    func_003570A0(0, s | o << 4 | gi << 8, 0);
    func_00357420(0x52, gi, 0, 2, 0);
    t[func_0036DD30(s, o) - 0x15](s, gi);
}

/* 0x0035A290, 0x30 bytes. The side order replies. */
void func_0035A290(int won)
{
    func_00357110(won == 0 ? 0x48 : 0x47);
}

/* 0x0035A2C0, 8 bytes, matching. */
void func_0035A2C0(int won)
{
}

/* 0x0035A2D0, 8 bytes, matching. */
void func_0035A2D0(int won)
{
}

/* 0x0035A2E0, 8 bytes, matching. */
void func_0035A2E0(int won)
{
}

/* 0x0035A2F0, 8 bytes, matching. */
void func_0035A2F0(int won)
{
}

/* 0x0035A300, 8 bytes, matching. */
void func_0035A300(int won)
{
}

/* 0x0035A310, 8 bytes, matching. */
void func_0035A310(int won)
{
}

/* 0x0035A320, 0x30 bytes. */
void func_0035A320(int won)
{
    func_00357110(won == 0 ? 0x4A : 0x49);
}

/* 0x0035A350, 0x30 bytes. */
void func_0035A350(int won)
{
    func_00357110(won == 0 ? 0x4B : 0x7E);
}

/* 0x0035A380, 0x30 bytes. */
void func_0035A380(int won)
{
    func_00357110(won == 0 ? 0x81 : 0x82);
}

/* 0x0035A3B0, 0xFC bytes. Command: side `a` gives order `b` to the whole side. */
void func_0035A3B0(EvCmd *c)
{
    void (*t[10])(int);
    short o = c->b;
    u16 s = c->a;
    u32 k;

    for (k = 0; k < 10; k++)
        t[k] = g_00415750[k];
    func_0036DD30(s, o);
    func_003570A0(1, s | o << 4, 0);
    t[func_0036DD30(s, o) - 0x15](s);
}

/* 0x0035A4B0, 0x168 bytes. Command: group `a` reached situation `b` (1-5; lines 0x43-0x47,
 * messages 0x6D / 0x6E). */
void func_0035A4B0(EvCmd *c)
{
    u16 i = c->a;
    short v = c->b;
    u32 msg = 0xC3, m = 0x5C;

    if (!UNIT_ACTIVE(*GROUP(i)))
        return;
    if (v == 5) {
        m = 0x47;
    } else if (v == 4) {
        m = 0x46;
    } else if (v == 2) {
        m = 0x44;
        msg = 0x6E;
    } else if (v == 3) {
        m = 0x45;
    } else if (v == 1) {
        m = 0x43;
        msg = 0x6D;
    }
    if (m < 0x5C) {
        func_00357420(m, i, 0, 2, 0);
        func_00357000(i);
        if (msg < 0xC3)
            func_00357170(msg, i);
    }
}

/* 0x0035A620, 0x138 bytes. The same for situations 6-7 (lines 0x48-0x49, messages 0x6F / 0x88). */
void func_0035A620(EvCmd *c)
{
    u16 i = c->a;
    u8 *u = *GROUP(i);
    u32 msg = 0xC3, m = 0x5C;

    if (!UNIT_ACTIVE(u))
        return;
    if ((short)c->b == 6) {
        m = 0x49;
        msg = u[0x79] == 0 ? 0x6F : 0x88;
    } else if ((short)c->b == 7) {
        m = 0x48;
    }
    if (m < 0x5C) {
        func_00357420(m, i, 0, 2, 0);
        func_00357000(i);
        if (msg < 0xC3)
            func_00357170(msg, i);
    }
}

/* 0x0035A760, 0xE4 bytes. Command: a guard of base `a` speaks (one of four lines). */
void func_0035A760(EvCmd *c)
{
    u32 t[4];
    u8 *b, *u;
    u32 o;

    t[0] = g_00415780[0];
    t[1] = g_00415780[1];
    t[2] = g_00415780[2];
    t[3] = g_00415780[3];
    b = (u8 *)func_0034EC80(c->a);
    o = func_0034EDB0(b);
    if (o < 2 && (u = func_00352850(b, o)) != 0)
        func_003574E0(t[RANDOM() & 3], UNIT_INDEX(u), 2, 0);
}

/* 0x0035A850, 0xB4 bytes. Command: a guard of side `b`'s base `a` calls for help (line 4). */
void func_0035A850(EvCmd *c)
{
    u16 k = c->a;
    u8 *b = (u8 *)func_0034EC80(k), *u;
    u32 o = func_0034EDB0(b);

    if (o < 2 && o == c->b && (u = func_00352850(b, o)) != 0) {
        func_00357070(k);
        func_003574E0(4, UNIT_INDEX(u), 2, 0);
    }
}

/* 0x0035A910, 0x200 bytes. Command: base `a`'s guard heals its side's officers at the base by
 * half their most life (line 5). */
void func_0035A910(EvCmd *c)
{
    u8 *b = (u8 *)func_0034EC80(c->a), *u;
    u32 o = func_0034EDB0(b), k;

    if (o >= 2 || (u = func_00352850(b, o)) == 0)
        return;
    func_003574E0(5, UNIT_INDEX(u), 2, 0);
    for (k = 0; k < 0x8F; k++) {
        u8 *r = OFFICER(k);
        u32 f = *(u32 *)(r + 0xB8);

        if ((f & 1) != 0 && (f & 2) == 0 && *(u8 **)(r + 0x10) != 0
            && o == (*(u8 **)(r + 0x10))[0x79] && func_003B0370(r, b) != 0) {
            short most = *(short *)(r + 0x80);
            int n = most * 0x32 / 100 + *(short *)(r + 0x82);

            if (n < 2)
                n = 1;
            if (n > most)
                n = most;
            if (n < 1)
                n = 0;
            *(short *)(r + 0x82) = n;
            if (*(short *)(r + 0x84) < n)
                *(short *)(r + 0x84) = n;
        }
    }
}

/* Shows effect `kind` on base `b`'s officers of side `o` (the first with sound). */
static void base_effect(u8 *b, u32 o, int kind)
{
    u32 k;
    int first = 1;

    for (k = 0; k < 0x8F; k++) {
        u8 *r = OFFICER(k);
        u32 f = *(u32 *)(r + 0xB8);

        if ((f & 1) != 0 && (f & 2) == 0 && *(u8 **)(r + 0x10) != 0
            && o == (*(u8 **)(r + 0x10))[0x79] && func_003B0370(r, b) != 0
            && *(int *)(r + 0x14) != 0) {
            func_0024D3A0(kind, *(int *)(r + 0x14), first);
            first = 0;
        }
    }
}

/* 0x0035AB10, 0x14C bytes. Command: base `a`'s guard boosts its side's officers (line 6, effect
 * 8). */
void func_0035AB10(EvCmd *c)
{
    u8 *b = (u8 *)func_0034EC80(c->a), *u;
    u32 o = func_0034EDB0(b);

    if (o < 2 && (u = func_00352850(b, o)) != 0) {
        func_003574E0(6, UNIT_INDEX(u), 2, 0);
        base_effect(b, o, 8);
    }
}

/* 0x0035AC60, 0x14C bytes. The same with line 7, effect 9. */
void func_0035AC60(EvCmd *c)
{
    u8 *b = (u8 *)func_0034EC80(c->a), *u;
    u32 o = func_0034EDB0(b);

    if (o < 2 && (u = func_00352850(b, o)) != 0) {
        func_003574E0(7, UNIT_INDEX(u), 2, 0);
        base_effect(b, o, 9);
    }
}

/* 0x0035ADB0, 0xA4 bytes. The battle's opening message (by battle kind) at the main base. */
void func_0035ADB0(void)
{
    u32 m, b;

    switch (func_00362570()) {
    case 0:
    case 1:
        m = 0x65;
        b = func_0035F200(1);
        break;
    case 2:
    case 3:
        m = 0x66;
        b = func_0035F200(1);
        break;
    case 4:
    case 5:
        m = 0x67;
        b = func_0035F200(0);
        break;
    default:
        m = 0x66;
        b = func_0035F200(1);
        break;
    }
    func_00357070(b);
    func_00357110(m);
}

/* 0x0035AE60, 0x38 bytes, matching. The opening message with func_0036D310. */
void func_0035AE60(void)
{
    func_00357260(0x92, func_00361F50(), func_00361E90());
}

/* 0x0035AEA0, 0x3C bytes. */
void func_0035AEA0(void)
{
    if (func_0036D310() == 0)
        func_0035ADB0();
    else
        func_0035AE60();
}

/* 0x0035AEE0, 0x84 bytes. The player's opening line by side 0's strength. */
void func_0035AEE0(void)
{
    u32 v = func_003615C0(0), m, how;

    if (v >= 0x42) {
        m = 0x1A;
        how = 1;
    } else if (v >= 0x24) {
        m = 0x1B;
        how = 0;
    } else {
        m = 0x1C;
        how = 3;
    }
    func_00357420(m, func_0035DCB0(0), how, 2, 0);
}

extern void (*g_004157A0[13])(u8 **g, u8 **h);   /* the group comments */
extern u32 g_004157E0[8], g_00415800[20];
extern u32 g_0045D078[2];                /* (small data) */
extern u8 g_005BC2A0[0x40][4];           /* the timers (flags, ?, id, ?) */

#define SETTINGS_FLAGS (*(u32 *)(g_00669D60 + 0x200))
#define SETTINGS_B2 (g_00669D60[0x252])
#define SETTINGS_FA0 (*(int *)(g_00669D60 + 0x240))

int func_0033F4D0(u8 *b, int side, int *out, int max);
int func_0034ED40(u8 *b);
u32 func_0036F900(void);
u32 func_003F55E0(void);
u32 func_003F5600(void);
int func_003F5650(void);
u32 func_003F6C10(int side);
int func_003F7090(u32 a, u32 b);
u32 func_003F6CA0(int side, u16 k);
void func_003F74E0(int side, u16 k);
void func_003F75F0(u16 side);
void func_00183410(int a, int id, int b, int delay, int c);

/* 0x0035AF70, 0xF0 bytes. Side 0's first reserve announces itself (and, with event 0x14, a
 * second line). */
void func_0035AF70(void)
{
    u8 **g = func_0033F020(0, 0);

    if ((((u32 *)g)[0x19] & 1) == 0)
        return;
    func_00357650(2, GROUP_INDEX(g), 2, 0);
    if (func_0036F390(0, 0x14) != 0) {
        u32 t[4];

        t[0] = g_00415790[0];
        t[1] = g_00415790[1];
        t[2] = g_00415790[2];
        func_00357570(3, t[RANDOM() % 3], 0, 0, 0);
    }
}

/* 0x0035B060, 0x128 bytes. A side 0 group at side 0's main base speaks (0x31), then message 0x69
 * there. */
void func_0035B060(void)
{
    u8 *b = (u8 *)func_0034EC80(func_0035F200(0)), *g = 0;
    int list[16], n;

    n = func_0033F4D0(b, 0, list, 0x10);
    if (n != 0) {
        g = g_006A1D58[list[n == 0 ? 0 : (int)RANDOM() % n]];
        if (g != 0)
            func_00357420(0x31, GROUP_INDEX(g), 3, 0, 0);
    }
    func_00357070(func_0034ED40(b));
    func_00357110(0x69);
}

/* 0x0035B190, 0x3C bytes. Message 0x6A at side 0's main base. */
void func_0035B190(void)
{
    func_00357070(func_0034ED40((u8 *)func_0034EC80(func_0035F200(0))));
    func_00357110(0x6A);
}

/* 0x0035B1D0, 0x3C bytes. Message 0x6B at side 1's main base. */
void func_0035B1D0(void)
{
    func_00357070(func_0034ED40((u8 *)func_0034EC80(func_0035F200(1))));
    func_00357110(0x6B);
}

/* 0x0035B210-0x0035B9D0: group comments (`g` the speaker, `h` the other group). */
/* 0x0035B210, 0xFC bytes. */
void func_0035B210(u8 **g, u8 **h)
{
    func_00357420(0x32, GROUP_INDEX(h), 0, 2, 0);
    if (func_003579E0(g, h) == 0)
        func_00357420(0x34, GROUP_INDEX(g), 0, 2, 0);
    else
        func_00357420(0x33, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B310, 0x108 bytes. */
void func_0035B310(u8 **g, u8 **h)
{
    if (func_003579E0(g, h) == 0)
        func_00357420(0x4B, GROUP_INDEX(g), 0, 2, 0);
    else
        func_00357420(0x4A, GROUP_INDEX(g), 0, 2, 0);
    func_00357420(0x4E, GROUP_INDEX(h), 0, 2, 0);
}

/* 0x0035B420, 0x164 bytes. */
void func_0035B420(u8 **g, u8 **h)
{
    if (func_003579E0(g, h) == 0)
        func_00357420(0x4D, GROUP_INDEX(g), 0, 2, 0);
    else
        func_00357420(0x4C, GROUP_INDEX(g), 0, 2, 0);
    if (func_003579E0(h, g) == 0)
        func_00357420(0x34, GROUP_INDEX(h), 0, 2, 0);
    else
        func_00357420(0x33, GROUP_INDEX(h), 0, 2, 0);
}

/* 0x0035B590, 0x54 bytes, matching. */
void func_0035B590(u8 **g, u8 **h)
{
    func_00357420(0x4E, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B5F0, 0x54 bytes, matching. */
void func_0035B5F0(u8 **g, u8 **h)
{
    func_00357420(0x4F, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B650, 0x54 bytes, matching. */
void func_0035B650(u8 **g, u8 **h)
{
    func_00357420(0x50, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B6B0, 0xA0 bytes, matching. */
void func_0035B6B0(u8 **g, u8 **h)
{
    u32 i = GROUP_INDEX(g);

    func_00357420(0x51, i, 0, 2, 0);
    func_003571A0(0x70, i & 0xFFFF, GROUP_INDEX(h) & 0xFFFF);
}

/* 0x0035B750, 0x54 bytes, matching. */
void func_0035B750(u8 **g, u8 **h)
{
    func_00357420(0x37, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B7B0, 0x54 bytes, matching. */
void func_0035B7B0(u8 **g, u8 **h)
{
    func_00357420(0x35, GROUP_INDEX(g), 3, 2, 0);
}

/* 0x0035B810, 0x54 bytes, matching. */
void func_0035B810(u8 **g, u8 **h)
{
    func_00357420(0x36, GROUP_INDEX(g), 1, 2, 0);
}

/* 0x0035B870, 0xAC bytes. */
void func_0035B870(u8 **g, u8 **h)
{
    if (func_003579E0(g, h) == 0)
        func_00357420(0x3E, GROUP_INDEX(g), 1, 2, 0);
    else
        func_00357420(0x3D, GROUP_INDEX(g), 1, 2, 0);
}

/* 0x0035B920, 0xAC bytes. */
void func_0035B920(u8 **g, u8 **h)
{
    if (func_003579E0(g, h) == 0)
        func_00357420(0x3C, GROUP_INDEX(g), 0, 2, 0);
    else
        func_00357420(0x3B, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035B9D0, 0x54 bytes, matching. */
void func_0035B9D0(u8 **g, u8 **h)
{
    func_00357420(0x40, GROUP_INDEX(g), 0, 2, 0);
}

/* 0x0035BA30, 0xC4 bytes. Command: group comment `a` by group `b` about group `c`. */
void func_0035BA30(EvCmd *c)
{
    void (*t[13])(u8 **, u8 **);
    u16 hi = c->c;
    int k;

    for (k = 0; k < 13; k++)
        t[k] = g_004157A0[k];
    if (c->a < 0xD)
        t[c->a](GROUP(c->b), hi < 0x47 ? GROUP(hi) : 0);
}

/* 0x0035BB00, 0x34 bytes, matching. Message 0x89 with func_0036F900's value (below 0x1F). */
void func_0035BB00(void)
{
    u32 v = func_0036F900();

    if (v < 0x1F)
        func_00357200(0x89, v & 0xFFFF);
}

/* 0x0035BB40, 0x28 bytes, matching. */
void func_0035BB40(void)
{
    func_00357110(0x34);
    SETTINGS_B2 = 1;
}

/* 0x0035BB70, 0x38 bytes, matching. Adds 250 to the score (message 0x91). */
void func_0035BB70(void)
{
    SETTINGS_FA0 += 0xFA;
    func_00357260(0x91, 0x32, 5);
}

/* 0x0035BBB0, 0x1C bytes, matching. */
void func_0035BBB0(void)
{
    func_00357110(0x93);
}

/* 0x0035BBD0, 0x198 bytes. Command: group `a`'s mission event (messages 0x9E-0xA1, then the
 * mission's own line). */
void func_0035BBD0(EvCmd *c)
{
    u16 i = c->a;
    u32 t[8], k, m;
    int j;

    for (j = 0; j < 8; j++)
        t[j] = g_004157E0[j];
    func_00357000(i);
    if ((*GROUP(i))[0x79] == 1) {
        func_00357170(0x9E, i);
        func_00357170(0x9F, i);
    } else {
        func_00357170(0xA0, i);
        func_00357170(0xA1, i);
    }
    k = func_003F55E0();
    if (k < 8) {
        m = t[k];
        switch (k) {
        case 0:
        case 1:
        case 3:
        case 4:
            func_00357370(m, 0, func_003F5600());
            break;
        case 2:
        case 7:
            func_00357310(m, 0);
            break;
        case 5:
        case 6:
            func_00357340(m, 0, i);
            break;
        }
    }
    func_003570A0(2, 1, 0);
}

/* 0x0035BD70, 0x190 bytes. Command: group `a` changes sides (`b` won, else its side's view). */
void func_0035BD70(EvCmd *c)
{
    u16 i = c->a, won = c->b;
    u8 *u, side;

    if (i >= 0x47)
        return;
    u = *GROUP(i);
    side = u[0x79];
    if (!UNIT_ACTIVE(u))
        won = side == 0;
    if ((side == 1 && won != 0) || (side == 0 && won == 0)) {
        EvCmd d;

        d.kind = 0xD;
        d.a = i;
        func_003591F0(&d);
    }
    if (side == 1) {
        if (won == 0)
            func_00357340(0x8B, 2, i);
        else
            func_00357340(0x8A, 1, i);
    } else if (won == 0) {
        func_00357340(0x8D, 2, i);
    } else {
        func_00357340(0x8C, 1, i);
    }
    func_003F5610(won == 0 ? 4 : 3);
}

/* 0x0035BF00, 0x80 bytes. Command: a mission result `a` (1-3; messages 0x8E-0x90). */
void func_0035BF00(EvCmd *c)
{
    short v = c->a;
    u32 m;

    if (func_003F5650() == 0)
        return;
    if (v == 3)
        m = 0x8E;
    else if (v == 2)
        m = 0x8F;
    else if (v == 1)
        m = 0x90;
    else
        return;
    func_00357110(m);
}

/* 0x0035BF80, 0x78 bytes. The score message (both sides' counts). */
void func_0035BF80(void)
{
    u32 a = func_003F6C10(0), b = func_003F6C10(1), m;
    int r = func_003F7090(a, b);

    if (r >= 1)
        m = 0xBE;
    else if (r == 0)
        m = 0xBF;
    else
        m = 0xC0;
    func_00357230(m, a & 0xFFFF, b & 0xFFFF);
}

/* 0x0035C000, 0x88 bytes. Command: side `a` scores `b` (messages 0xAA-0xBD). */
void func_0035C000(EvCmd *c)
{
    u16 k = c->b;
    short s = c->a;
    u32 n = func_003F6CA0(s, k);

    if (n < 10) {
        func_003F74E0(s, k);
        func_00357110(s == 0 ? n * 2 + 0xAA : n * 2 + 0xAB);
        func_0035BF80();
    }
}

/* 0x0035C090, 0x1C bytes, matching. */
void func_0035C090(void)
{
    func_0035BF80();
}

/* 0x0035C0B0, 0xA8 bytes. Command: side `a` loses a point. */
void func_0035C0B0(EvCmd *c)
{
    u32 t[20];
    u16 s = c->a;
    u32 n;
    int k;

    for (k = 0; k < 20; k++)
        t[k] = g_00415800[k];
    n = func_003F6C10(s);
    if (n < 10) {
        func_003F75F0(s);
        if (t[n * 2 + s] < 0xC3)
            func_00357110(t[n * 2 + s]);
        func_0035BF80();
    }
}

/* 0x0035C160, 0x60 bytes. The same with a fixed message per side. */
void func_0035C160(EvCmd *c)
{
    u32 t[2];
    u16 s = c->a;

    t[0] = g_0045D078[0];
    t[1] = g_0045D078[1];
    func_003F75F0(s);
    if (t[s] < 0xC3)
        func_00357110(t[s]);
    func_0035BF80();
}

/* 0x0035C1C0, 0x34C bytes, matching. Runs a command of the second queue. */
int func_0035C1C0(EvCmd *c)
{
    switch (c->kind) {
    case 0: func_00357C20(); break;
    case 1: func_00357E70(c); break;
    case 2: func_003581E0(c); break;
    case 3: func_00358460(c); break;
    case 4: func_003586D0(c); break;
    case 5: func_00358910(c); break;
    case 6: func_00358B60(c); break;
    case 7: func_00358C40(c); break;
    case 8: func_00358DB0(c); break;
    case 9: func_00358E10(c); break;
    case 10: func_00358F10(c); break;
    case 0xB: func_00358FD0(c); break;
    case 0xC: func_00359170(c); break;
    case 0xD: func_003591F0(c); break;
    case 0xE: func_00359350(c); break;
    case 0xF: func_003595C0(); break;
    case 0x10: func_00359670(c); break;
    case 0x11: func_003596E0(c); break;
    case 0x12: func_00359930(c); break;
    case 0x13: func_003599E0(c); break;
    case 0x14: func_00359A90(c); break;
    case 0x15: func_00359B30(c); break;
    case 0x16: func_0035A0C0(c); break;
    case 0x17: func_0035A3B0(c); break;
    case 0x18: func_0035A4B0(c); break;
    case 0x19: func_0035A620(c); break;
    case 0x1A: func_0035BA30(c); break;
    case 0x1B: func_0035A760(c); break;
    case 0x1C: func_0035A850(c); break;
    case 0x1D: func_0035A910(c); break;
    case 0x1E: func_0035AB10(c); break;
    case 0x1F: func_0035AC60(c); break;
    case 0x20: func_0035AEA0(); break;
    case 0x21: func_0035AEE0(); break;
    case 0x22: func_0035AF70(); break;
    case 0x23: func_0035B060(); break;
    case 0x24: func_0035B190(); break;
    case 0x25: func_0035B1D0(); break;
    case 0x26: func_0035BB00(); break;
    case 0x27: func_0035BB40(); break;
    case 0x28: func_0035BB70(); break;
    case 0x29: func_0035BBB0(); break;
    case 0x2A: func_0035BBD0(c); break;
    case 0x2B: func_0035BD70(c); break;
    case 0x2C: func_0035BF00(c); break;
    case 0x2D: func_0035C000(c); break;
    case 0x2E: func_0035C090(); break;
    case 0x2F: func_0035C0B0(c); break;
    case 0x30: func_0035C160(c); break;
    }
    return 1;
}

/* 0x0035C510, 0x4C bytes. The second queue's first free slot (0x20 for none). */
u32 func_0035C510(void)
{
    EvCmd *c = func_003577E0(0);
    u32 k;

    for (k = 0; k < 0x20; k++, c++) {
        if (c->kind > 0x30)
            return k;
    }
    return 0x20;
}

/* 0x0035C560, 0x78 bytes, matching. Queues command `c` to run after `delay` (timer 0x32 + slot). */
void func_0035C560(EvCmd *c, int delay)
{
    u32 k = func_0035C510();

    if (k < 0x20) {
        func_00118AC0(func_003577E0(k), c, 8);
        func_00183410(1, k + 0x32, 3, delay, 0);
    }
}

/* Removes timer `k` (the later ones move down). */
static void timer_remove(u32 k)
{
    u8 *p = g_005BC2A0[k];
    u32 j;

    *p &= 0xFC;
    for (j = k; j < 0x3F; j++) {
        func_00118AC0(p, p + 4, 4);
        p += 4;
    }
    p[0] = 0;
    p[3] = 0;
}

/* 0x0035C5E0, 0x138 bytes. Cancels the waiting commands that `test` (with `a`, `b`) picks. */
void func_0035C5E0(int (*test)(EvCmd *, int, int), int a, int b)
{
    u32 k = 0;

    if (test == 0)
        return;
    do {
        u8 *p = g_005BC2A0[k];
        EvCmd *c;

        if ((p[0] & 1) == 0 || p[2] < 0x32 || (c = func_003577E0(p[2] - 0x32)) == 0
            || test(c, a, b) == 0) {
            k++;
            continue;
        }
        c->kind = 0x31;
        timer_remove(k);
    } while (k < 0x40);
}

/* 0x0035C730, 0x30 bytes. Whether `c` is order command 0x11 for group `g`. */
int func_0035C730(EvCmd *c, int g)
{
    if (c->kind != 0x11)
        return 0;
    return c->a == g;
}

/* 0x0035C760, 0x28 bytes, matching. */
void func_0035C760(int g)
{
    func_0035C5E0((int (*)(EvCmd *, int, int))func_0035C730, g, 0);
}

/* 0x0035C790, 0x6C bytes. Whether `c` is situation command 0x18 / 0x19 for group `g` (or
 * comment 0x1A by it). */
int func_0035C790(EvCmd *c, int g)
{
    if (c->kind == 0x18)
        return c->a == g;
    if (c->kind == 0x19)
        return c->a == g;
    if (c->kind == 0x1A)
        return c->b == g;
    return 0;
}

/* 0x0035C800, 0x28 bytes, matching. */
void func_0035C800(int g)
{
    func_0035C5E0((int (*)(EvCmd *, int, int))func_0035C790, g, 0);
}

/* 0x0035C830, 0x88 bytes. Whether `c` is a defeat command (3, 4) whose group no longer counts. */
int func_0035C830(EvCmd *c)
{
    u32 g = 0x47;

    if ((short)c->kind == 3)
        g = c->b;
    else if ((short)c->kind == 4)
        g = c->b;
    if (g < 0x47 && func_0033B150(GROUP(g)) != 0)
        return 0;
    return 1;
}

/* 0x0035C8C0, 0x28 bytes, matching. */
void func_0035C8C0(int a)
{
    func_0035C5E0((int (*)(EvCmd *, int, int))func_0035C830, a, 0);
}

/* 0x0035C8F0, 0xDC bytes. Removes the running timers (but the command ones). */
void func_0035C8F0(void)
{
    u32 k = 0;

    do {
        u8 *p = g_005BC2A0[k];
        int del = (p[0] & 1) != 0;

        if ((p[0] & 2) != 0 && p[2] > 0x31)
            del = 0;
        if (del)
            timer_remove(k);
        else
            k++;
    } while (k < 0x40);
}

/* 0x0035C9D0, 0x90 bytes. Ends the battle (`kind`, `won`) after the pending messages; with
 * settings flag 0x10, at once (ending 5). */
void func_0035C9D0(u16 kind, int won)
{
    EvCmd c;

    if ((SETTINGS_FLAGS & 0x10) != 0) {
        SETTINGS_FLAGS |= 0xC000000;
        BATTLE_END = 5;
        return;
    }
    c.kind = 1;
    c.b = won;
    c.a = kind;
    func_0035C8C0(kind);
    func_0035C8F0();
    func_0035C560(&c, won == 0 ? 8 : 7);
}

/* 0x0035CA60-0x0035D438: queue second-queue command kind K (parameters a, b, c) after a
 * delay. */

/* 0x0035CA60, 0x30 bytes, matching. */
void func_0035CA60(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 2;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 5);
}

/* 0x0035CA90, 0x30 bytes, matching. */
void func_0035CA90(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 3;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 6);
}

/* 0x0035CAC0, 0x30 bytes, matching. */
void func_0035CAC0(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 4;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 6);
}

/* 0x0035CAF0, 0x38 bytes. */
void func_0035CAF0(u16 a, u16 b, short c2, u16 d)
{
    EvCmd e;

    e.b = c2 << 8 | b;
    e.kind = 5;
    e.a = a;
    e.c = d;
    func_0035C560(&e, 5);
}

/* 0x0035CB30, 0x28 bytes, matching. */
void func_0035CB30(u16 a)
{
    EvCmd e;

    e.kind = 6;
    e.a = a;
    func_0035C560(&e, 6);
}

/* 0x0035CB60, 0x30 bytes, matching. */
void func_0035CB60(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 7;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 2);
}

/* 0x0035CB90, 0x2C bytes, matching. */
void func_0035CB90(u16 a)
{
    EvCmd e;

    e.kind = 0xA;
    e.a = a;
    func_0035C560(&e, 2);
}

/* 0x0035CBC0, 0x2C bytes, matching. */
void func_0035CBC0(u16 a)
{
    EvCmd e;

    e.kind = 0xB;
    e.a = a;
    func_0035C560(&e, 2);
}

/* 0x0035CBF0, 0x2C bytes, matching. */
void func_0035CBF0(u16 a)
{
    EvCmd e;

    e.kind = 0xC;
    e.a = a;
    func_0035C560(&e, 2);
}

/* 0x0035CC20, 0x2C bytes, matching. */
void func_0035CC20(u16 a)
{
    EvCmd e;

    e.kind = 0xD;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035CC50, 0x2C bytes, matching. */
void func_0035CC50(u16 a)
{
    EvCmd e;

    e.kind = 0xE;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035CC80, 0x28 bytes, matching. */
void func_0035CC80(void)
{
    EvCmd e;

    e.kind = 0xF;
    func_0035C560(&e, 5);
}

/* 0x0035CCB0, 0x2C bytes, matching. */
void func_0035CCB0(u16 a)
{
    EvCmd e;

    e.kind = 0x10;
    e.a = a;
    func_0035C560(&e, 8);
}

/* 0x0035CCE0, 0x34 bytes. */
void func_0035CCE0(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 0x11;
    e.a = a;
    e.b = b;
    func_0035C760(a);
    func_0035C560(&e, 6);
}

/* 0x0035CD20, 0x2C bytes, matching. */
void func_0035CD20(u16 a)
{
    EvCmd e;

    e.kind = 0x12;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035CD50, 0x2C bytes, matching. */
void func_0035CD50(u16 a)
{
    EvCmd e;

    e.kind = 0x13;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035CD80, 0x2C bytes, matching. */
void func_0035CD80(u16 a)
{
    EvCmd e;

    e.kind = 0x14;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035CDB0, 0x34 bytes, matching. */
void func_0035CDB0(u16 a, u16 b, u16 c)
{
    EvCmd e;

    e.kind = 0x15;
    e.a = a;
    e.b = b;
    e.c = c;
    func_0035C560(&e, 0);
}

/* 0x0035CDF0, 0x34 bytes, matching. */
void func_0035CDF0(u16 a, u16 b, u16 c)
{
    EvCmd e;

    e.kind = 0x16;
    e.a = a;
    e.b = b;
    e.c = c;
    func_0035C560(&e, 6);
}

/* 0x0035CE30, 0x30 bytes, matching. */
void func_0035CE30(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 0x17;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 6);
}

/* 0x0035CE60, 0x34 bytes. */
void func_0035CE60(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 0x18;
    e.a = a;
    e.b = b;
    func_0035C800(a);
    func_0035C560(&e, 2);
}

/* 0x0035CEA0, 0x34 bytes. */
void func_0035CEA0(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 0x19;
    e.a = a;
    e.b = b;
    func_0035C800(a);
    func_0035C560(&e, 2);
}

/* 0x0035CEE0, 0x3C bytes. */
void func_0035CEE0(u16 a, u16 b, u16 c)
{
    EvCmd e;

    e.kind = 0x1A;
    e.a = a;
    e.b = b;
    e.c = c;
    func_0035C800(b);
    func_0035C560(&e, 2);
}

/* 0x0035CF20, 0x44 bytes, matching. */
void func_0035CF20(u16 a)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x1B;
    e.a = a;
    func_0035C560(&e, 2);
}

/* 0x0035CF70, 0x54 bytes, matching. */
void func_0035CF70(u16 a, u16 b)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x1C;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 0);
}

/* 0x0035CFD0, 0x44 bytes, matching. */
void func_0035CFD0(u16 a)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x1D;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035D020, 0x44 bytes, matching. */
void func_0035D020(u16 a)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x1E;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035D070, 0x44 bytes, matching. */
void func_0035D070(u16 a)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x1F;
    e.a = a;
    func_0035C560(&e, 0);
}

/* 0x0035D0C0, 0x28 bytes, matching. */
void func_0035D0C0(void)
{
    EvCmd e;

    e.kind = 0x20;
    func_0035C560(&e, 6);
}

/* 0x0035D0F0, 0x28 bytes, matching. */
void func_0035D0F0(void)
{
    EvCmd e;

    e.kind = 0x21;
    func_0035C560(&e, 6);
}

/* 0x0035D120, 0x28 bytes, matching. */
void func_0035D120(void)
{
    EvCmd e;

    e.kind = 0x22;
    func_0035C560(&e, 6);
}

/* 0x0035D150, 0x38 bytes, matching. */
void func_0035D150(void)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x23;
    func_0035C560(&e, 5);
}

/* 0x0035D190, 0x38 bytes, matching. */
void func_0035D190(void)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x24;
    func_0035C560(&e, 5);
}

/* 0x0035D1D0, 0x38 bytes, matching. */
void func_0035D1D0(void)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x25;
    func_0035C560(&e, 5);
}

/* 0x0035D210, 0x28 bytes, matching. */
void func_0035D210(void)
{
    EvCmd e;

    e.kind = 0x26;
    func_0035C560(&e, 6);
}

/* 0x0035D240, 0x28 bytes, matching. */
void func_0035D240(void)
{
    EvCmd e;

    e.kind = 0x27;
    func_0035C560(&e, 6);
}

/* 0x0035D270, 0x28 bytes, matching. */
void func_0035D270(void)
{
    EvCmd e;

    e.kind = 0x28;
    func_0035C560(&e, 6);
}

/* 0x0035D2A0, 0x28 bytes, matching. */
void func_0035D2A0(void)
{
    EvCmd e;

    e.kind = 0x29;
    func_0035C560(&e, 6);
}

/* 0x0035D2D0, 0x2C bytes, matching. */
void func_0035D2D0(u16 a)
{
    EvCmd e;

    e.kind = 0x2A;
    e.a = a;
    func_0035C560(&e, 5);
}

/* 0x0035D300, 0x30 bytes, matching. */
void func_0035D300(u16 a, u16 b)
{
    EvCmd e;

    e.kind = 0x2B;
    e.a = a;
    e.b = b;
    func_0035C560(&e, 6);
}

/* 0x0035D330, 0x2C bytes, matching. */
void func_0035D330(u16 a)
{
    EvCmd e;

    e.kind = 0x2C;
    e.a = a;
    func_0035C560(&e, 5);
}

/* 0x0035D360, 0x34 bytes, matching. */
void func_0035D360(u16 a, u16 b, u16 c)
{
    EvCmd e;

    e.kind = 0x2D;
    e.a = a;
    e.b = b;
    e.c = c;
    func_0035C560(&e, 6);
}

/* 0x0035D3A0, 0x38 bytes, matching. */
void func_0035D3A0(void)
{
    EvCmd e;

    if (func_0036D310() != 0)
        return;
    e.kind = 0x2E;
    func_0035C560(&e, 6);
}

/* 0x0035D3E0, 0x2C bytes, matching. */
void func_0035D3E0(u16 a)
{
    EvCmd e;

    e.kind = 0x2F;
    e.a = a;
    func_0035C560(&e, 6);
}

/* 0x0035D410, 0x2C bytes, matching. */
void func_0035D410(u16 a)
{
    EvCmd e;

    e.kind = 0x30;
    e.a = a;
    func_0035C560(&e, 6);
}

int func_0023E840(u8 *t);

/* 0x0035D440, 0x44 bytes. A plain timer's step (func_0023E840); stops it when it is done. */
int func_0035D440(u8 *t)
{
    int r = func_0023E840(t);

    if (r != 0)
        *t &= 0xFC;
    return r != 0;
}

/* 0x0035D490, 0x7C bytes, matching. A command timer's step: starts its command when the first queue is
 * idle, frees it once the queue is done. */
int func_0035D490(u8 *t)
{
    EvCmd *c = func_003577E0(t[2] - 0x32);

    if (func_00356EF0() == 0) {
        func_00356F00();
        func_0035C1C0(c);
    }
    if (func_00356E40() != 0) {
        c->kind = 0x31;
        *t &= 0xFC;
    }
    return 1;
}

/* 0x0035D510, 0x50 bytes. A timer's step (returns the step's result). */
int func_0035D510(u8 *t)
{
    int r;

    if (t[2] < 0x32)
        r = func_0035D440(t);
    else if (t[2] > 0x31)
        r = func_0035D490(t);
    return r;
}
