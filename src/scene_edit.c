/*
 * scene_edit.c - scene 0x14, the officer editor (original source file StateEdit.c, probable: its
 * string is referenced at 0x003767A0, in the same block of code). Decompiled so far: the scene and
 * the page set-ups (0x0037BB60-0x0037DA64); the page handlers (0x003789B0-..., table 0x004169A0)
 * and the accessors before them are not yet.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly: Ghidra loses many registers here, because the small accessors 0x003766C0... are
 * known to the compiler not to touch them). Unknown functions and globals keep neutral names
 * (func_/g_ + address); comments with a question mark are hypotheses.
 *
 * The editor keeps its state in a 0xBA0-byte block (g_0045D7C8): the officer being edited at
 * +0x404 (a 0x38-byte record: +0x18 body, +0x1C colour, +0x20 weapon, +0x24, +0x2A-0x2E choices),
 * a copy at +0x43C to undo a page, and per page a cursor and its scroll. A model of the officer is
 * shown on the right (unit 0x00574DE0) and follows the record.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The scene manager (0x0045D880, see main.c): one object, reached through lui / %lo. */
extern struct {
    float update_arg;
    u32 result;
    int quit, skip_update_test, force_draw;
    int previous;            /* 0x0045D894 */
    int current;             /* 0x0045D898 */
    int return_to;           /* 0x0045D89C state to return to */
    int requested;           /* 0x0045D8A0 requested state (0x18 = none) */
} g_0045D880;
#define g_0045D894 (g_0045D880.previous)
#define g_0045D898 (g_0045D880.current)
#define g_0045D89C (g_0045D880.return_to)
#define g_0045D8A0 (g_0045D880.requested)

/* The editor's state (small data: two blocks of 0xBA0 and 0x780 bytes). */
extern u8 *g_0045D7C8;
extern u8 *g_0045D7CC;
#define ES(off, type) (*(type *)(g_0045D7C8 + (off)))
#define ES_RECORD     (g_0045D7C8 + 0x404)          /* the officer being edited */
#define ES_BACKUP     (g_0045D7C8 + 0x43C)          /* its copy when the page opened */
#define ES_REQUESTED  ES(0xB0, int)                 /* page asked for */
#define ES_PAGE       ES(0xB4, int)                 /* page shown (0-11) */
#define ES_PREVIOUS   ES(0xB8, int)
#define ES_PHASE      ES(0x9A4, int)                /* 0 open, 1 in, 2 out, 3 running */
#define ES_TIMER      ES(0x9A8, int)
#define ES_DIRTY      ES(0xB97, u8)                 /* 1: the page changed the record */
#define ES_SHOWN      ES(0xB98, int)                /* a model is shown */
#define ES_HEIGHT     ES(0xB9C, float)              /* the model's view height */

/* Shared menu flags (0x00799A24, see scene_shop.c). */
extern struct {
    u8 g_00799A24;
    u8 pad_0;
    u8 g_00799A26;
    u8 pad_1;
    int g_00799A28;
    int g_00799A2C;
    u8 pad_2[0xC];
    u8 g_00799A3C;
    u8 pad_3;
    u8 g_00799A3E;
    u8 pad_4;
    int g_00799A40;
    int g_00799A44;
} s_00799A24;
#define g_00799A24 (s_00799A24.g_00799A24)
#define g_00799A26 (s_00799A24.g_00799A26)
#define g_00799A28 (s_00799A24.g_00799A28)
#define g_00799A2C (s_00799A24.g_00799A2C)
#define g_00799A3C (s_00799A24.g_00799A3C)
#define g_00799A3E (s_00799A24.g_00799A3E)
#define g_00799A40 (s_00799A24.g_00799A40)
#define g_00799A44 (s_00799A24.g_00799A44)

/* After a page set-up: the list starts (inlined in the original). */
#define LIST_START() do {                       \
        g_00799A40 = 1;                         \
        g_00799A44 = 0;                         \
        g_00799A3C = g_00799A3E;                \
    } while (0)
#define LIST_START_ALT() do {                   \
        g_00799A44 = 1;                         \
        g_00799A40 = 0;                         \
        g_00799A3C = g_00799A3E;                \
    } while (0)

/* The model view (0x007B9E40): position and size words, colour bytes. */
extern struct {
    u16 g_007B9E40, g_007B9E42, g_007B9E44, g_007B9E46;
    u16 g_007B9E48, g_007B9E4A, g_007B9E4C, g_007B9E4E;
    u8 g_007B9E50, g_007B9E51, g_007B9E52, g_007B9E53;
} s_007B9E40;

/* Units (see scene_battle_initialize.c): the player unit and the model's battle unit. */
extern u8 g_005B4BC0[2][0x240];
extern u8 g_00574DE0[2][0x630];
extern u8 *g_0045D2C0;

/* The game state's officer records (0x00669D60 + 0x254, 15 of 0x38 bytes). */
extern u8 g_00669D60[];

/* Tables (0x00416720-0x004169A0). */
extern int g_00416720[22], g_00416780[22];  /* weapons, and their model height offsets */
extern int g_004167E0[13];                  /* bodies of page 1 */
extern int g_00416820[16], g_00416860[18], g_004168B0[15];   /* page 2 lists by body group */
extern int g_004168F0[4], g_00416900[4];    /* page 4 lists by body group */
extern u32 g_00416910[12], g_00416940[12], g_00416970[11];   /* page 5 lists by weapon */
extern void (*g_004169A0[12])(void);        /* the page handlers */

u8 *func_00377330(int i);
u8 *func_00377380(int i);
void func_001BE1A0(void);
void func_001BD2C0(u8 *model);
void func_0017C7D0(u8 *motion);
void func_001BE030(void);
void func_0016D060(int a, int b, int c);
void func_001BC540(void);
u8 *func_003766C0(void);
void func_00166160(u8 *unit);
void func_00165C60(u8 *unit, int body, int kind, int model, int a, int b, u8 colour, int c);
void func_00165180(u8 *unit, int a, int b);
void func_001BE4F0(void);
void func_001646C0(u8 *unit, int a);
int func_003773F0(int weapon);
int func_003774A0(int model, int a);
void func_0017A920(u8 *unit);
void func_003774E0(int value);
void func_0019F550(void);
void func_00101470(int value);
void func_00182C30(void);
void func_00178460(void);
void func_00182C20(void);
void func_003D4770(u8 *list);
int func_00120A40(const u8 *text);
void func_0011EB80(void *dst, const void *src, int size);
void func_003767A0(int value);
void func_001BD180(u8 *model, int a, int b, int c);
void func_0017CC40(u8 *motion, int a);
void func_0016CFB0(int a, int b);
void func_001037F0(int value);
void func_003F8B30(int value);
u8 *func_00102DB0(int align, int size);
void func_00118850(void *p, int size);
void func_002F15E0(u32 unused, int stage);
int func_00102960(int value);
void func_002F1660(void);
void func_001A2040(void);
void func_003A5360(u8 *a, int b);
void func_003776D0(void);
void func_003D8280(void);
int func_0017DDA0(void);
void func_0017E010(int value);
void func_001B8F60(int a, int b, int c);
void func_0023AA40(void);
void func_0017DF10(void);
void func_00375D60(void);
void func_003767E0(void);
void func_00102EC0(void *data);
void func_003F8B80(void);
void func_00376450(void);
void func_003D8DF0(void);
void func_003D93F0(void);
void func_001AE550(float scale, void *view, short *out, u8 *b, int c);
void func_001784E0(float dt);
void func_00179320(void);
void func_00278A20(void);
void func_003F8C00(void);
void func_003D8230(void);
void func_001796D0(void);

/* The motion slot of entry `i` of the model lists (26 of 4 bytes, then three more). */
static int motion_slot(int i)
{
    if (i < 0x1A)
        return i * 4;
    if (i == 0x1A)
        return 0x68;
    if (i == 0x1B)
        return 0x6C;
    return 0x70;
}

/* The model kind of a weapon: weapons 0-0x19 their own, the ranges 0x3E-0x48, 0x49-0x53,
 * 0x54-0x5C and 0x5D-0x67 share the models 0x26, 0x2A, 0x20 and 0x21 (inlined, four times). */
static int weapon_kind(int weapon)
{
    if (weapon < 0x1A)
        return weapon;
    if (weapon >= 0x3E && weapon < 0x49)
        return 0x26;
    if (weapon >= 0x49 && weapon < 0x54)
        return 0x2A;
    if (weapon >= 0x54 && weapon < 0x5D)
        return 0x20;
    if (weapon >= 0x5D && weapon < 0x68)
        return 0x21;
    return weapon;
}

void func_0037BE30(int body, int colour, int kind, int model);

/* Shows the model of officer record `rec` (inlined in the original). */
static void show_record(const u8 *rec)
{
    int weapon = *(int *)(rec + 0x20);
    int kind = weapon_kind(weapon);
    int model = func_003774A0(func_003773F0(weapon), 0);

    func_0037BE30(*(int *)(rec + 0x18), rec[0x1C], kind, model);
}

/* 0x0037BB60, 0x104 bytes. Loads the models and motions of the editor. */
void func_0037BB60(void)
{
    int i;

    func_001BE1A0();
    for (i = 0; i < 0x0D; i++)
        func_001BD2C0(func_00377330(i));
    for (i = 0; i < 0x1E; i++)
        func_0017C7D0(func_00377380(i));
    func_001BE030();
    for (i = 0; i < 0x1E; i++)
        func_0016D060(motion_slot(i), -1, 0);
    func_001BC540();
}

/* 0x0037BC70, 0x1B8 bytes. Sets the model view's height for `kind` (90, plus the weapon's offset;
 * 6 lower for body 0x30 with models 0x26, 0x2A and 0x20) and resets the view. */
void func_0037BC70(int body, int kind)
{
    u8 *es = func_003766C0();
    int weapons[22], offsets[22];
    int i, found = -1;

    for (i = 0; i < 22; i++)
        weapons[i] = g_00416720[i];
    for (i = 0; i < 22; i++)
        offsets[i] = g_00416780[i];
    for (i = 0; i < 0x16; i++)
        if (kind == weapons[i]) {
            found = i;
            break;
        }
    if (found == -1) {
        *(float *)(es + 0xB9C) = 90.0f;
    } else {
        *(float *)(es + 0xB9C) = (float)offsets[found] + 90.0f;
        if (body == 0x30 && (kind == 0x26 || kind == 0x2A || kind == 0x20))
            *(float *)(es + 0xB9C) -= 6.0f;
    }
    s_007B9E40.g_007B9E44 = 0;
    s_007B9E40.g_007B9E40 = 0x28;
    s_007B9E40.g_007B9E53 = 0;
    s_007B9E40.g_007B9E46 = 0;
    s_007B9E40.g_007B9E50 = 0x80;
    s_007B9E40.g_007B9E48 = 0x28;
    s_007B9E40.g_007B9E4A = (u16)(int)*(float *)(es + 0xB9C);
    s_007B9E40.g_007B9E42 = s_007B9E40.g_007B9E4A;
    s_007B9E40.g_007B9E51 = 0x80;
    s_007B9E40.g_007B9E4C = 0;
    s_007B9E40.g_007B9E4E = 0;
    s_007B9E40.g_007B9E52 = 0;
}

/* 0x0037BE30, 0x9C bytes, matching. Shows the model of an officer (body, colour, weapon kind, model). */
void func_0037BE30(int body, int colour, int kind, int model)
{
    func_003766C0();
    func_0037BC70(body, kind);
    func_00166160(g_00574DE0[0]);
    func_00165C60(g_00574DE0[0], body, kind, model, 0x11, 0, colour, 1);
    func_00165180(g_00574DE0[0], 1, 0);
}

/* 0x0037BED0, 0x28 bytes, matching. Hides the model. */
void func_0037BED0(void)
{
    func_003766C0();
    func_00166160(g_00574DE0[0]);
}

/* 0x0037BF00, 0x120 bytes. Shows the first officer record's model (if it is set). */
void func_0037BF00(void)
{
    u8 *es = func_003766C0();
    u8 *rec = es + 0xBC;

    func_001BE4F0();
    func_001646C0(g_00574DE0[0], 0);
    if (rec[0] == 0) {
        ES_SHOWN = 0;
        return;
    }
    show_record(rec);
    ES_SHOWN = 1;
}

/* 0x0037C020, 0x8C bytes, matching. Places the player unit and the model for the editor's view. */
void func_0037C020(void)
{
    u8 *unit = g_005B4BC0[0];

    func_0017A920(unit);
    *(float *)(unit + 0x1C0) = 0.0f;
    *(float *)(unit + 0x1C4) = -60.0f;
    *(float *)(unit + 0x1C8) = 520.0f;
    *(float *)(unit + 0x1CC) = 1.0f;
    *(float *)(unit + 0x1D0) = 0.0f;
    *(float *)(unit + 0x1D4) = 0.0f;
    *(float *)(unit + 0x1D8) = 0.0f;
    *(float *)(unit + 0x1DC) = 1.0f;
    *(float *)(g_00574DE0[0] + 0x40) = 40.0f;
    *(float *)(g_00574DE0[0] + 0x44) = 90.0f;
    func_003774E0(0);
}

/* 0x0037C0B0, 0x78 bytes. Prepares the model and the view. */
void func_0037C0B0(void)
{
    func_0019F550();
    func_00101470(0);
    func_0037BB60();
    func_0037BF00();
    func_00182C30();
    func_0017A920(g_005B4BC0[0]);
    g_0045D2C0 = g_005B4BC0[0];
    g_005B4BC0[0][0x230] = (g_005B4BC0[0][0x230] & 0xFE) | 1;
    func_0037C020();
}

/* 0x0037C130, 0x24 bytes, matching. */
void func_0037C130(void)
{
    func_00178460();
    func_00182C20();
}

/* 0x0037C160, 0x38 bytes. The scroll of a list of `count` entries showing `shown`, with the
 * cursor on `index`. */
int func_0037C160(int count, int shown, int index)
{
    if (shown < count) {
        if (index < shown)
            return 0;
        return index - shown + 1;
    }
    return 0;
}

/* Finds `value` in `list` (-1 when absent). */
static int find_in(const int *list, int count, int value)
{
    int i;

    for (i = 0; i < count; i++)
        if (value == list[i])
            return i;
    return -1;
}

/* 0x0037C1A0, 0xD4 bytes. Page 1 set-up (the body): the cursor on the record's body. */
void func_0037C1A0(void)
{
    u8 *es = func_003766C0();
    int list[13];
    int i, found;

    for (i = 0; i < 13; i++)
        list[i] = g_004167E0[i];
    found = find_in(list, 13, *(int *)(ES_RECORD + 0x18));
    if (found >= 0) {
        *(int *)(es + 0x30) = found;
        *(int *)(es + 0x34) = func_0037C160(0x0D, 10, found);
        *(int *)(es + 0x38) = ES_RECORD[0x1C];
    }
    LIST_START();
    func_003D4770(func_003766C0() + 0x974);
}

/* 0x0037C280, 0x1FC bytes. Page 2 set-up (the weapon): the list by body group, the cursor on
 * the record's weapon. */
void func_0037C280(void)
{
    u8 *es = func_003766C0();
    int list_a[16], list_b[18], list_c[15];
    int body = *(int *)(ES_RECORD + 0x18);
    int *list = 0, count = 0, i, found;      /* (count is left unset by the original for other bodies) */

    for (i = 0; i < 16; i++)
        list_a[i] = g_00416820[i];
    for (i = 0; i < 18; i++)
        list_b[i] = g_00416860[i];
    for (i = 0; i < 15; i++)
        list_c[i] = g_004168B0[i];
    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C) {
        list = list_c;
        count = 0x0F;
    } else if (body == 0x38 || body == 0x37 || body == 0x36) {
        list = list_b;
        count = 0x12;
    } else if (body == 0x35 || body == 0x34 || body == 0x33) {
        list = list_a;
        count = 0x10;
    }
    found = list ? find_in(list, count, *(int *)(ES_RECORD + 0x20)) : -1;
    if (found >= 0) {
        *(int *)(es + 0x40) = found;
        *(int *)(es + 0x44) = func_0037C160(count, 10, found);
    }
    LIST_START();
}

/* 0x0037C480, 0x11C bytes. Page 3 set-up: the cursor on choice +0x2B (9 or 11 entries by body
 * group). */
void func_0037C480(void)
{
    u8 *es = func_003766C0();
    int body = *(int *)(ES_RECORD + 0x18);
    int value = ES_RECORD[0x2B];
    int count = 0;

    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C || body == 0x35 || body == 0x34 || body == 0x33)
        count = 9;
    else if (body == 0x38 || body == 0x37 || body == 0x36)
        count = 0x0B;
    *(int *)(es + 0x64) = value;
    *(int *)(es + 0x68) = func_0037C160(count, 4, value);
    LIST_START();
}

/* 0x0037C5A0, 0x1AC bytes. Page 4 set-up: the cursor on choice +0x24 (two lists of 4 by body
 * group). */
void func_0037C5A0(void)
{
    u8 *es = func_003766C0();
    int list_a[4], list_b[4];
    int body = *(int *)(ES_RECORD + 0x18);
    int *list = 0, count = 0, i, found;

    for (i = 0; i < 4; i++) {
        list_b[i] = g_004168F0[i];
        list_a[i] = g_00416900[i];
    }
    if (body == 0x30 || body == 0x21 || body == 0x20 || body == 0x1F || body == 0x1E ||
        body == 0x1D || body == 0x1C || body == 0x35 || body == 0x34 || body == 0x33) {
        list = list_a;
        count = 4;
    } else if (body == 0x38 || body == 0x37 || body == 0x36) {
        list = list_b;
        count = 4;
    }
    found = list ? find_in(list, count, *(int *)(ES_RECORD + 0x24)) : -1;
    if (found >= 0)
        *(int *)(es + 0x4C) = found;
    LIST_START();
}

/* 0x0037C750, 0x288 bytes. Page 5 set-up: the cursor on choice +0x2A (lists by weapon). */
void func_0037C750(void)
{
    u8 *es = func_003766C0();
    u32 list_a[12], list_b[12], list_c[11];
    int weapon = *(int *)(ES_RECORD + 0x20);
    u32 *list = list_c;
    int count, i, found = -1;

    for (i = 0; i < 12; i++) {
        list_a[i] = g_00416910[i];
        list_b[i] = g_00416940[i];
    }
    for (i = 0; i < 11; i++)
        list_c[i] = g_00416970[i];
    if (weapon == 0x0F || weapon == 7) {
        list = list_b;
        count = 0x0C;
    } else if (weapon == 0x15 || weapon == 2) {
        list = list_a;
        count = 0x0C;
    } else {
        count = 0x0B;
    }
    for (i = 0; i < count; i++)
        if (ES_RECORD[0x2A] == list[i]) {
            found = i;
            break;
        }
    if (found >= 0) {
        *(int *)(es + 0x5C) = found;
        *(int *)(es + 0x60) = func_0037C160(count, 10, found);
    }
    LIST_START();
}

/* 0x0037C9E0, 0x48 bytes. Page 6 set-up: the cursor on choice +0x2D. */
void func_0037C9E0(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x74) = ES_RECORD[0x2D];
    LIST_START();
}

/* 0x0037CA30, 0x48 bytes. Page 7 set-up: the cursor on choice +0x2C. */
void func_0037CA30(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x6C) = ES_RECORD[0x2C];
    LIST_START();
}

/* 0x0037CA80, 0x54 bytes. Page 8 set-up: the cursor on choice +0x2E. */
void func_0037CA80(void)
{
    u8 *es = func_003766C0();

    *(int *)(es + 0x7C) = ES_RECORD[0x2E];
    LIST_START();
    func_003D4770(func_003766C0() + 0x974);
}

/* 0x0037CAE0, 0x20 bytes, matching. The length of a name (func_00120A40). */
u8 func_0037CAE0(const u8 *text)
{
    return func_00120A40(text);
}

/* 0x0037CB00, 0x10C bytes. Page 0 set-up (the name): clears the input state and reads the two
 * name parts' lengths (at most 7). */
void func_0037CB00(void)
{
    u32 *p = (u32 *)func_003766C0();              /* (accessor 0x003766E0: the same block) */
    int i;

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 1;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    ((u8 *)p)[0x20] = 0;
    ((u8 *)p)[0x21] = 0;
    for (i = 0; i < 2; i++) {
        u8 len = func_0037CAE0(ES_RECORD + (i == 1 ? 1 : 10));
        if (len > 7)
            len = 7;
        ((u8 *)p)[0x22 + i] = len;
    }
    LIST_START_ALT();
    func_003D4770(func_003766C0() + 0x974);
    func_003D4770(func_003766C0() + 0x98C);
    ES(0x990, u8) = ES(0x992, u8);
    ES(0x994, int) = 0;
    ES(0x998, int) = 1;
}

/* 0x0037CC10, 0x8C bytes. Page 9 set-up. */
void func_0037CC10(void)
{
    u32 *p = (u32 *)(func_003766C0() + 0x84);    /* (accessor 0x00376770) */

    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    ((u8 *)p)[0x14] = 0;
    ((u8 *)p)[0x15] = 0;
    LIST_START_ALT();
    func_003D4770(func_003766C0() + 0x974);
    func_003D4770(func_003766C0() + 0x98C);
    ES(0x990, u8) = ES(0x992, u8);
    ES(0x994, int) = 0;
    ES(0x998, int) = 1;
}

/* 0x0037CCA0, 0x294 bytes. Opens the page asked for: keeps a copy of the record (to undo the
 * page) and sets the page's cursor up; 10 and 11 are the two confirmations. */
void func_0037CCA0(void)
{
    u8 *es = func_003766C0();

    switch (*(int *)(es + 0xB0)) {
    case 0:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CB00();
        break;
    case 1:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C1A0();
        break;
    case 2:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C280();
        break;
    case 3:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C480();
        break;
    case 4:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        *(int *)(es + 0x50) = 0;
        func_0037C5A0();
        break;
    case 5:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037C750();
        break;
    case 6:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0011EB80(es + 0x92C, es + 0x8E4, 0x48);
        func_0037C9E0();
        break;
    case 7:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CA30();
        break;
    case 8:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CA80();
        break;
    case 9:
        func_0011EB80(ES_BACKUP, ES_RECORD, 0x38);
        func_0037CC10();
        break;
    case 10:
        if (*(int *)(es + 0xB8) == 0x0B)
            *(int *)(es + 0x9C) = 0;
        *(int *)(es + 0xA0) = 1;
        g_00799A24 = g_00799A26;
        g_00799A28 = 1;
        g_00799A2C = 0;
        break;
    case 11:
        if (*(int *)(es + 0xB8) == 0x0C) {
            *(int *)(es + 0xA4) = 0;
            *(int *)(es + 0xA8) = 0;
        }
        *(int *)(es + 0xAC) = 1;
        LIST_START();
        break;
    }
}

/* 0x0037CF40, 0x10C bytes. Frees the editor's models and motions. */
void func_0037CF40(void)
{
    int i;

    func_003767A0(0);
    for (i = 0; i < 0x0D; i++)
        func_001BD180(func_00377330(i), 0, 0, 0);
    for (i = 0; i < 0x1E; i++)
        func_0017CC40(func_00377380(i), 0);
    func_001BC540();
    for (i = 0; i < 0x1E; i++)
        func_0016CFB0(motion_slot(i), 0);
}

/* 0x0037D060, 0xEC bytes. Scene 0x14 enter: allocates the editor's state and goes through the
 * loading screen (0x0F), back here. */
void func_0037D060(void)
{
    func_001037F0(0);
    func_003F8B30(3);
    g_0045D7C8 = func_00102DB0(0x10, 0xBA0);
    g_0045D7CC = func_00102DB0(0x10, 0x780);
    func_00118850(g_0045D7C8, 0xBA0);
    func_00118850(g_0045D7CC, 0x780);
    func_0037CF40();
    func_002F15E0(0, 0);
    g_0045D89C = 0x0F;                            /* to the loading screen, then back */
    g_0045D8A0 = g_0045D898;
    if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D8A0;
        g_0045D89C = 0x18;
    } else {
        g_0045D894 = g_0045D898;
        g_0045D898 = g_0045D89C;
        g_0045D89C = g_0045D8A0;
    }
}

/* 0x0037D150, 0xEC bytes, matching. Scene 0x14 enter_alt (back from the loading screen): copies the 15
 * officer records of the game state, prepares the model and starts music 0x32. */
void func_0037D150(void)
{
    int i;

    func_00102960(1);
    func_002F1660();
    func_001A2040();
    for (i = 0; i < 0x0F; i++) {
        func_0011EB80(g_0045D7C8 + i * 0x38 + 0xBC, g_00669D60 + 0x254 + i * 0x38, 0x38);
        func_003A5360(g_0045D7C8 + i * 0x48 + 0x4AC, i + 400);
    }
    func_0037C0B0();
    func_003776D0();
    func_003D8280();
    if (func_0017DDA0() == 0)
        func_0017E010(0x32);
    func_001037F0(1);
    func_001B8F60(1, 6, 8);
}

/* 0x0037D240, 0x8 bytes, matching. Scene 0x14 leave_alt: empty (not found by Ghidra). */
void func_0037D240(void)
{
}

/* 0x0037D250, 0x6C bytes, matching. Scene 0x14 leave: frees the editor. */
void func_0037D250(void)
{
    func_0023AA40();
    func_0017DF10();
    func_00375D60();
    func_0037C130();
    func_003767E0();
    if (g_0045D7CC != 0)
        func_00102EC0(g_0045D7CC);
    g_0045D7CC = 0;
    if (g_0045D7C8 != 0)
        func_00102EC0(g_0045D7C8);
    g_0045D7C8 = 0;
    func_003F8B80();
}

/* 0x0037D2C0, 0x90 bytes. Undoes the page's changes (pages other than 10-12, when changed). */
void func_0037D2C0(void)
{
    u8 *es = func_003766C0();

    if ((u32)(ES_PAGE - 10) >= 3 && ES_DIRTY == 1) {
        func_0011EB80(ES_RECORD, ES_BACKUP, 0x38);
        if (ES_PAGE == 6)
            func_0011EB80(es + 0x8E4, es + 0x92C, 0x48);
        ES_DIRTY = 0;
    }
}

/* 0x0037D350, 0x690 bytes. Scene 0x14 update: runs the page (phase 3), its transitions (in /
 * out over a timer; page 12 leaves the editor for the title, scene 1), then updates the model
 * when the shown officer changed (page 11: the officer list's choice; pages 10, 1 and 2: the
 * record) and the view. */
int func_0037D350(float dt)
{
    u8 *es = func_003766C0();
    int *list = (int *)func_003766C0() + 0xA4 / 4;    /* (accessor 0x00376790) */
    u8 *p10 = func_003766C0() + 0x9C;                 /* (accessor 0x00376780) */
    u8 *p1 = func_003766C0() + 0x30;                  /* (accessor 0x003766F0) */
    u8 *p2 = func_003766C0() + 0x40;                  /* (accessor 0x00376700) */
    short pos[2];
    u8 flag;

    func_00376450();
    switch (ES_PHASE) {
    case 3:
        g_004169A0[ES_PAGE]();
        if (ES_REQUESTED != ES_PAGE)
            ES_PHASE = 1;
        break;
    case 2:
        if (--ES_TIMER < 0) {
            if (ES_REQUESTED == ES_PAGE) {
                ES_PHASE = 3;
            } else if (ES_REQUESTED == 0x0C) {        /* leave the editor */
                ES_PREVIOUS = ES_PAGE;
                ES_PAGE = ES_REQUESTED;
                if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
                    g_0045D89C = 1;
                if (g_0045D8A0 < 0x18 && g_0045D898 != g_0045D8A0) {
                    g_0045D894 = g_0045D898;
                    g_0045D898 = g_0045D8A0;
                    g_0045D89C = 0x18;
                } else {
                    g_0045D894 = g_0045D898;
                    g_0045D898 = g_0045D89C;
                    g_0045D89C = g_0045D8A0;
                }
            } else {
                func_0037D2C0();
                ES_PREVIOUS = ES_PAGE;
                ES_PAGE = ES_REQUESTED;
                ES_PHASE = 0;
                func_0037CCA0();
                func_003D8DF0();
            }
        }
        break;
    case 1:
        func_003D93F0();
        break;
    case 0:
        func_0037CCA0();
        func_003D8DF0();
        break;
    }

    if (ES_PAGE == 0x0B) {
        if (list[2] != 0) {
            u8 *rec = es + 0xBC + list[0] * 0x38;

            if (rec[0] == 0) {
                func_0037BED0();
                func_003774E0(2);
                ES_SHOWN = 0;
            } else {
                show_record(rec);
                func_003774E0(2);
                ES_SHOWN = 1;
            }
            list[2] = 0;
        }
    } else if (ES_PAGE == 10) {
        if ((u32)(ES_PREVIOUS - 1) < 2 && *(int *)(p10 + 4) != 0) {
            show_record(ES_RECORD);
            ES_SHOWN = 1;
            *(int *)(p10 + 4) = 0;
        }
    } else if (ES_PAGE == 1) {
        if (*(int *)(p1 + 0xC) != 0) {
            show_record(ES_RECORD);
            ES_SHOWN = 1;
            *(int *)(p1 + 0xC) = 0;
        }
    } else if (ES_PAGE == 2 && *(int *)(p2 + 8) != 0) {
        show_record(ES_RECORD);
        ES_SHOWN = 1;
        *(int *)(p2 + 8) = 0;
    }
    func_001AE550(1.0f, &s_007B9E40, pos, &flag, 1);
    *(float *)(g_00574DE0[0] + 0x40) = (float)(int)pos[0];
    *(float *)(g_00574DE0[0] + 0x44) = (float)(int)pos[1];
    if (ES_SHOWN != 0)
        func_001784E0(dt);
    return 1;
}

/* 0x0037D9E0, 0x30 bytes. Scene 0x14 step. */
void func_0037D9E0(void)
{
    if (ES(0xB98, int) != 0)
        func_00179320();
}

/* 0x0037DA10, 0x54 bytes, matching. Scene 0x14 draw: the editor's screen, then the model. */
void func_0037DA10(void)
{
    u8 *es = func_003766C0();

    func_00278A20();
    func_003F8C00();
    func_003D8230();
    if (*(int *)(es + 0xB98) != 0) {
        g_0045D2C0 = g_005B4BC0[0];
        func_001796D0();
    }
}
