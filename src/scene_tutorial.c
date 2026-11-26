/*
 * scene_tutorial.c - scenes 0x11 and 0x17 (original source file SceneTutorial.c: its name is
 * passed to the file loader at 0x003F4900). Decompiled: 0x003F2A50-0x003F4840; the tutorial
 * window code after it (0x003F4840...) is not yet.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Scene 0x11 starts the first of the tutorials 0x0C, 0x0D and 0x0E that func_003D2F80 accepts
 * (not yet seen?) and does nothing else; its drawing and stepping are empty.
 *
 * Scene 0x17 sets up a prepared Empire game (a tutorial?). Its enter keeps copies of the game
 * state (0x00669D60, 0x25310 bytes), the officer records (0x19F x 0x9C), two per-entry tables
 * (25 x 0x14, 25 x 0x78) and a set-up record (0xE0) in five buffers, then rebuilds the game
 * around the player's entry: the entries of a list chosen by the main menu entry
 * (g_0045C9C0, up to eight, -1 = none) are emptied and given the player's ruler and the player's best
 * officers. Its update waits for the fade and goes to the Empire map (scene 0x12); its leave
 * frees the buffers.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void func_0032F670(void);
void func_0032F640(void);
int func_003D2F80(int tutorial);
void func_003302F0(int tutorial);

/* 0x003F2A50, 0x1C bytes, matching. Scene 0x11 enter. */
void func_003F2A50(void)
{
    func_0032F670();
}

/* 0x003F2A70, 0x1C bytes, matching. Scene 0x11 leave. */
void func_003F2A70(void)
{
    func_0032F640();
}

/* 0x003F2A90, 0x70 bytes, matching. Scene 0x11 update: starts tutorial 0x0C, 0x0D or 0x0E. */
int func_003F2A90(void)
{
    if (func_003D2F80(0x0C) != 0)
        func_003302F0(0x0C);
    else if (func_003D2F80(0x0D) != 0)
        func_003302F0(0x0D);
    else if (func_003D2F80(0x0E) != 0)
        func_003302F0(0x0E);
    return 0;
}

/* 0x003F2B00, 0x8 bytes, matching. Scene 0x11 step: empty. */
void func_003F2B00(void)
{
}

/* 0x003F2B10, 0x8 bytes, matching. Scene 0x11 draw: empty. */
void func_003F2B10(void)
{
}

/* ---- Scene 0x17 ---- */

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

/* Copies kept by scene 0x17 (record layouts as copied: words, or half-words for the 0x78 ones). */
typedef struct { u32 w[4]; } Quad;
typedef struct { Quad q[0x2531]; } GameStateCopy;          /* 0x25310 bytes */
typedef struct { int w[0x27]; } OfficerRecord;             /* 0x9C bytes */
typedef struct { int w[5]; } EntryRecord14;                /* 0x14 bytes */
typedef struct { u16 h[0x3C]; } EntryRecord78;             /* 0x78 bytes */

/* The set-up record (0xE0 bytes). */
typedef struct {
    int kind;                /* 7, 8 or 9 from func_00327C80 (below 0x622, below 0x62E, else) */
    int menu;                /* func_00327C00: picks the entry list of g_0045C9C0 */
    int entry;               /* the player's entry (func_00327D50) */
    int value;               /* func_00327C80 */
    int ratio_a;             /* 50-100 (%) */
    int ratio_b;             /* 50-100 (%) */
    int count_a;
    int count_b;
    int list_a[24];          /* the player's best officers */
    int list_b[24];          /* the next ones (not func_002F3F20) */
} TutorialSetup;

extern GameStateCopy *g_0045D850;         /* (small data) the five buffers */
extern OfficerRecord *g_0045D854;
extern EntryRecord14 *g_0045D858;
extern EntryRecord78 *g_0045D85C;
extern TutorialSetup *g_0045D860;

extern GameStateCopy g_00669D60;          /* the game state (only copied here) */
extern int g_0045C9C0[][8];               /* per main menu entry: up to eight entries */

void *func_00102DB0(int align, int size);
void func_00102EC0(void *data);
void func_0011ED38(void *to, int value, int size);
int func_00327C80(void);
int func_00327C00(void);
int func_00327D50(void);
int func_00327E50(void);
int func_002F7D90(int a, int (*filter)(), int value, int b, int c, int d);
int *func_002F7B10(void);
int func_002F8160();
int func_002F7EC0();
int func_002F8900();
void func_002F87D0(int *list, int n, int (*compare)(), int a, int b);
int func_002F3F20(int officer);
int func_002FB320(int entry, int *out);
int func_0030AD80(int entry);
int func_0030AE80(int entry);
int func_0030B090(int entry);
int func_0030ACE0(int entry);
OfficerRecord *func_0030CCB0(void);
EntryRecord14 *func_0030CCD0(void);
EntryRecord78 *func_0030CCC0(void);
void func_0030CE90(int entry);
void func_00327BD0(int entry);
void func_002F7410(int officer);
void func_002FAFC0(int entry);
void func_002FB7C0(int entry);
int func_0030C4E0(int entry, int *out);
int func_0030AFF0(int entry);
int func_0030AB90(void);
int func_002F8CB0(int entry);
int func_002FB5A0(int entry, int *out);
int func_0030CB00(int n);
void func_0030AF20(int a, int b);
void func_00323840(int entry);
void func_002F8D20(int entry);
void func_002F8E80(int entry, int officer);
int func_002F5CC0(int officer);
int func_002F3C20(OfficerRecord *record);
int func_002F3E70(int officer);
int func_002F4080(int officer);
void func_002F7610(int officer);
int func_002F8F20(int entry);
void func_002F32F0(int officer, int a);
void func_002F4250(int officer, int a);
void func_002F43C0(int officer, int a);
void func_002F4510(int officer, int a);
int func_002F9260(int entry);
void func_002F91C0(int entry, int officer);
void func_002F3B30(int officer, int a);
void func_002F3CF0(int officer, int a);
void func_002F3F70(int officer, int a);
void func_002F5BE0(int officer, int a);
int func_00327820(void);
void func_0030A870(int a, int officer, int entry, int b, int c, int d);
void func_00327CF0(int value);
void func_00329030(void);
void func_00327C50(int a);
void func_00328CB0(void);
void func_00328E70(void);
void func_00327F00(int a);
void func_00327F70(int a);
void func_00327FE0(int a);
void func_00328050(int a);
void func_003292D0(int i, int a);
u32 func_00327870(void);
void func_00327830(int officer);
u32 func_00327AE0(int i);
void func_00327A80(int officer, int i);
int func_002FB910(void);
u32 func_002F9990(int entry);
void func_002F9900(int entry, int a);
void func_002F9A00(int entry, int a);
void func_002F94C0(int entry, int a);
void func_002F8F90(int entry, int a);
void func_002FA400(int entry, int a);
void func_002FA8E0(int entry, int a);
int func_002FA970(int entry);
void func_003280C0(int a);
void func_002F92D0(int entry, int i, int a);
void func_002FAA50(int entry, int i, int a);
void func_0030ADC0(int entry, int a);
void func_0030B030(int entry, int a);
void func_0039E7C0(int edited);
int func_00327950(void);
int func_0039E760(int edited);
void func_002F3440(int officer, int a);
void func_002F40F0(int officer, int a);
void func_002F3660(int officer, int a);
void func_002F56A0(int officer, int a);
void func_002F5930(int officer, int a);
int func_0039E650(int edited);
int func_003278B0(void);
void func_003A54A0(int officer);
void func_003A5650(int officer);
int func_002F2840(int officer);
void func_002F4AE0(int officer, int a);
void func_00327750(int n);
OfficerRecord *func_002F2720(int officer);
int func_0017DDA0(void);
void func_0017DF10(void);
int func_003BA7F0(int a);
void func_003BAB70(int a);
int func_0032EEB0(void);
void func_003BA8F0(int a, int b, int c, int d, int e);
void func_0030E090(int a);

#define ENTRY_VALID(e) ((e) >= 0 && (e) < func_0030AB90())
#define SETUP_LIST() (g_0045C9C0[g_0045D860->menu])

/* 0x003F2B20, 0x68 bytes, matching. */
void func_003F2B20(void)
{
    int value = func_00327C80();
    int kind;

    if (value < 0x622)
        kind = 7;
    else if (value < 0x62E)
        kind = 8;
    else
        kind = 9;
    g_0045D860->kind = kind;
    g_0045D860->menu = func_00327C00();
    g_0045D860->value = func_00327C80();
}

/* 0x003F2B90, 0x50 bytes, matching. How many entries the list holds. */
int func_003F2B90(void)
{
    int n = 0, i;
    int *list = SETUP_LIST();

    for (i = 0; i < 8; i++) {
        if (*list != -1)
            n++;
        list++;
    }
    return n;
}

/* 0x003F2BE0, 0x60 bytes. How many officers are moved: six per entry, at most func_00327E50. */
int func_003F2BE0(void)
{
    if (func_00327E50() < func_003F2B90() * 6)
        return func_00327E50();
    return func_003F2B90() * 6;
}

/* 0x003F2C40, 0x198 bytes. Picks the officers moved: the player's officers sorted
 * (func_002F8900), the best half in list_a, the next half (skipping func_002F3F20 ones) in
 * list_b. */
void func_003F2C40(void)
{
    int half = func_003F2BE0() / 2;
    int n = func_002F7D90(0, func_002F8160, func_00327D50(), 0, 0, 0);
    int *officers = func_002F7B10();
    int *p;
    int i, j = 0;

    func_002F87D0(officers, n, func_002F8900, -1, -1);
    g_0045D860->count_a = 0;
    g_0045D860->count_b = 0;
    p = officers;
    for (i = 0; i < half; i++) {
        if (j < n) {
            j++;
            g_0045D860->list_a[g_0045D860->count_a++] = *p++;
        }
    }
    if (half <= n) {
        for (i = 0; i < half; i++) {
            if (j < n) {
                int *o = &officers[j];

                if (func_002F3F20(*o) == 0) {
                    j++;
                    g_0045D860->list_b[g_0045D860->count_b++] = *o;
                } else {
                    j++;
                    i--;
                }
            }
        }
    }
}

/* 0x003F2DE0, 0x17C bytes. The player's two ratios (%, 50-100) over the entries of
 * func_002FB320: func_0030AD80 / func_0030AE80 and func_0030B090 / func_0030ACE0. */
void func_003F2DE0(void)
{
    int list[28];
    int n = func_002FB320(func_00327D50(), list);
    int a = 0, b = 0, c = 0, d = 0, i, ra, rb;
    int *p = list;

    for (i = 0; i < n; i++) {
        int e = *p;

        a += func_0030AD80(e);
        b += func_0030AE80(e);
        c += func_0030B090(e);
        d += func_0030ACE0(e);
        p++;
    }
    if (b < 1)
        b = 1;
    a = a * 100 / b;
    if (d < 1)
        d = 1;
    c = c * 100 / d;
    ra = a;
    if (a > 99)
        ra = 100;
    if (a < 0x32)
        ra = 0x32;
    rb = c;
    if (c > 99)
        rb = 100;
    if (c < 0x32)
        rb = 0x32;
    g_0045D860->ratio_a = ra;
    g_0045D860->ratio_b = rb;
}

/* 0x003F2F60, 0x4D4 bytes. Keeps the copies. */
void func_003F2F60(void)
{
    OfficerRecord *officers;
    EntryRecord14 *e14;
    EntryRecord78 *e78;
    int i;

    g_0045D860->entry = func_00327D50();
    officers = func_0030CCB0();
    for (i = 0; i < 0x19F; i++)
        g_0045D854[i] = officers[i];
    e14 = func_0030CCD0();
    for (i = 0; i < 25; i++)
        g_0045D858[i] = e14[i];
    e78 = func_0030CCC0();
    for (i = 0; i < 25; i++)
        g_0045D85C[i] = e78[i];
    *g_0045D850 = g_00669D60;
}

/* 0x003F3440, 0x2C bytes, matching. */
void func_003F3440(void)
{
    func_0030CE90(g_0045D860->kind);
    func_00327BD0(g_0045D860->kind);
}

/* 0x003F3470, 0x21C bytes. Empties entry `entry`: its officers leave (func_002F7410), each of
 * its places goes to a random neighbouring entry that func_002F8CB0 accepts (else any). */
void func_003F3470(int entry)
{
    int list[28], places[28], others[28];
    int i, j, n, m, k;
    int *p;

    n = func_002F7D90(0, func_002F8160, entry, 0, 0, 0);
    p = func_002F7B10();
    for (i = 0; i < n; i++)
        func_002F7410(*p++);
    func_002FAFC0(entry);
    func_002FB7C0(entry);
    n = func_002FB320(entry, list);
    p = list;
    for (i = 0; i < n; i++) {
        int *q = places, *o = others;

        m = func_0030C4E0(*p, places);
        k = 0;
        for (j = 0; j < m; j++) {
            int game = func_0030AFF0(*q);

            if (ENTRY_VALID(game) && func_002F8CB0(game) != 0 && game != entry) {
                *o++ = game;
                k++;
            }
            q++;
        }
        if (k == 0)
            k = func_002FB5A0(entry, others);
        if (k == 0) {
            o = others;
            for (j = 0; j < 25; j++) {
                if (func_002F8CB0(j) != 0 && j != entry) {
                    *o++ = j;
                    k++;
                }
            }
        }
        func_0030AF20(*p, others[func_0030CB00(k)]);
        func_00323840(*p);
        p++;
    }
    func_002F8D20(entry);
    func_002F8E80(entry, 0x19F);
}

/* 0x003F3690, 0x70 bytes. Whether `officer`'s entry is in the list. */
int func_003F3690(int officer)
{
    int entry = func_002F5CC0(officer);
    int n = func_003F2B90();
    int i;
    int *list;

    for (i = 0, list = SETUP_LIST(); i < n; i++, list++)
        if (entry == *list)
            return 1;
    return 0;
}

/* 0x003F3700, 0x8C bytes, matching. Whether `officer` is one of the officers moved. */
static int func_003F3700(int officer)
{
    int i;

    for (i = 0; i < g_0045D860->count_a; i++)
        if (g_0045D860->list_a[i] == officer)
            return 1;
    for (i = 0; i < g_0045D860->count_b; i++)
        if (g_0045D860->list_b[i] == officer)
            return 1;
    return 0;
}

/* 0x003F3790, 0xAC bytes, matching. Empties the entries of the rulers among the copied officers that
 * func_002F3C20 accepts (and frees those officers), and of the rulers moved. */
void func_003F3790(void)
{
    int i;

    for (i = 0; i < 0x19F; i++) {
        if (func_002F3C20(&g_0045D854[i]) != 0) {
            if (func_002F3E70(i) != 0)
                func_003F3470(func_002F4080(i));
            func_002F7610(i);
        }
        if (func_003F3700(i) != 0 && func_002F3E70(i) != 0)
            func_003F3470(func_002F4080(i));
    }
}

/* 0x003F3840, 0x128 bytes. Empties the entries of the list (whose ruler's entry is in it) and
 * sends their officers away. */
void func_003F3840(void)
{
    int n = func_003F2B90();
    int i, j;

    for (i = 0; i < n; i++) {
        int entry = SETUP_LIST()[i];
        int game = func_0030AFF0(entry);
        int m;
        int *officers;

        if (func_003F3690(func_002F8F20(game)) != 0)
            func_003F3470(game);
        m = func_002F7D90(0, func_002F7EC0, entry, 0, 0, 0);
        officers = func_002F7B10();
        for (j = 0; j < m; j++)
            func_002F7410(*officers++);
        func_0030AF20(entry, 0x19);
    }
}

/* 0x003F3970, 0x4C bytes, matching. */
void func_003F3970(int officer)
{
    func_002F32F0(officer, 1);
    func_002F4250(officer, 0);
    func_002F43C0(officer, 0);
    func_002F4510(officer, 0);
}

/* 0x003F39C0, 0x84 bytes. Clears `officer` from the entries where func_002F9260 names it. */
void func_003F39C0(int officer)
{
    int i;

    for (i = 0; i < func_0030AB90(); i++)
        if (func_002F8CB0(i) != 0 && officer == func_002F9260(i))
            func_002F91C0(i, 0x19F);
}

/* 0x003F3A50, 0xEC bytes, matching. Puts an officer in entry `entry` (see func_00365A80 in
 * scene_start_up.c) and resets its state. */
void func_003F3A50(int officer, int entry, int place, int kind)
{
    int ok;

    func_002F3B30(officer, 2);
    if (kind >= 0 && kind < 6)
        func_002F3CF0(officer, kind);
    ok = 0;
    if (entry >= 0 && entry < func_0030AB90())
        ok = 1;
    if (ok)
        func_002F3F70(officer, entry);
    ok = 0;
    if (place >= 0 && place < func_0030AB90())
        ok = 1;
    if (!ok)
        ok = place == 0x19;
    if (ok)
        func_002F5BE0(officer, place);
    func_003F3970(officer);
    func_003F39C0(officer);
}

/* 0x003F3B40, 0x348 bytes. Restores the officers moved from the copies and shares them out over
 * the list's entries, two of list_a and three of list_b each; the first entry also gets the
 * ruler func_00327820. */
void func_003F3B40(void)
{
    int n = func_003F2B90();
    int ruler = func_00327820();
    int i, j, a, b, home;

    for (i = 0; i < g_0045D860->count_a; i++) {
        int o = g_0045D860->list_a[i];

        *func_002F2720(o) = g_0045D854[o];
    }
    for (i = 0; i < g_0045D860->count_b; i++) {
        int o = g_0045D860->list_b[i];

        *func_002F2720(o) = g_0045D854[o];
    }
    a = 0;
    b = 0;
    for (i = 0; i < n; i++) {
        int entry = SETUP_LIST()[i];

        if (i == 0) {
            func_0030A870(0, ruler, entry, 0, 0, 0);
            home = func_002F4080(ruler);
            func_00327CF0(home);
            a++;
            for (j = 1; j < 3; j++)
                if (a < g_0045D860->count_a)
                    func_003F3A50(g_0045D860->list_a[a++], home, entry, 2);
        } else {
            func_0030AF20(entry, home);
            for (j = 0; j < 3; j++)
                if (a < g_0045D860->count_a)
                    func_003F3A50(g_0045D860->list_a[a++], home, entry, 2);
        }
        for (j = 0; j < 3; j++)
            if (b < g_0045D860->count_b)
                func_003F3A50(g_0045D860->list_b[b++], home, entry, 1);
    }
}

/* 0x003F3E90, 0x154 bytes. Resets the game's counters and clears the officers set aside
 * (func_00327870, func_00327AE0) who are not in the player's entry. */
void func_003F3E90(void)
{
    int i;

    func_00329030();
    func_00327C50(1);
    func_00328CB0();
    func_00328E70();
    func_00327F00(func_0030CB00(0x19));
    func_00327F70(func_0030CB00(0x19));
    func_00327FE0(func_0030CB00(0x19));
    func_00328050(func_0030CB00(0x19));
    for (i = 0; i < 10; i++)
        func_003292D0(i, 0);
    if (func_00327870() < 0x19F && func_002F4080(func_00327870()) != func_00327D50())
        func_00327830(0x19F);
    for (i = 0; i < 4; i++)
        if (func_00327AE0(i) < 0x19F && func_002F4080(func_00327AE0(i)) != func_00327D50())
            func_00327A80(0x19F, i);
}

/* 0x003F3FF0, 0x158 bytes. Gives the player's entry back its copied values. */
void func_003F3FF0(void)
{
    u8 *saved = (u8 *)&g_0045D85C[g_0045D860->entry];
    int entry = func_00327D50();
    u8 group = saved[0x12];
    int other = func_002FB910();
    int i;

    for (i = 0; i < 25; i++)
        if (func_002F8CB0(i) != 0 && func_002F9990(i) == group)
            func_002F9900(i, other);
    func_002F9900(entry, group);
    func_002F9A00(entry, saved[0x13]);
    func_002F94C0(entry, *(u16 *)(saved + 0x10));
    func_002F8F90(entry, *(u16 *)(saved + 2));
    func_002FA400(entry, saved[0x72]);
    func_002FA8E0(entry, saved[0x77]);
    func_003280C0(func_002FA970(entry));
    for (i = 0; i < 3; i++)
        func_002F92D0(entry, i, *(u16 *)(saved + 6 + i * 2));
    for (i = 0; i < 0x28; i++)
        func_002FAA50(entry, i, saved[0x46 + i]);
}

/* 0x003F4150, 0xE4 bytes. Scales the player's places by the two ratios. */
void func_003F4150(void)
{
    int list[28];
    int n = func_002FB320(func_00327D50(), list);
    int i;
    int *p = list;

    for (i = 0; i < n; i++) {
        int e = *p;

        func_0030ADC0(e, g_0045D860->ratio_a * func_0030AE80(e) / 100);
        func_0030B030(e, g_0045D860->ratio_b * func_0030ACE0(e) / 100);
        p++;
    }
}

/* 0x003F4240, 0x134 bytes, matching. Resets edited officer `officer` (400-0x19E): free (status 3) when
 * func_00327950 is 0 and it has no valid entry, else placed in an entry from func_0039E760. */
void func_003F4240(int officer)
{
    int edited = officer - 400;
    int entry;
    int ok;

    func_0039E7C0(edited);
    entry = func_002F4080(officer);
    ok = 0;
    if (entry >= 0 && entry < func_0030AB90())
        ok = 1;
    if (!ok) {
        if (func_00327950() == 0) {
            func_002F3B30(officer, 3);
            return;
        }
        func_002F3B30(officer, 2);
        func_002F3CF0(officer, 0);
        func_002F5BE0(officer, func_0039E760(edited) % func_0030AB90());
    }
    func_002F32F0(officer, 1);
    func_002F3440(officer, 0);
    func_002F40F0(officer, 0);
    func_002F3660(officer, 2000);
    func_002F4250(officer, 0);
    func_002F43C0(officer, 0);
    func_002F4510(officer, 0);
    func_002F56A0(officer, 0);
    func_002F5930(officer, 0);
}

/* 0x003F4380, 0x1A0 bytes. Resets the edited officers outside the player's entry, then every
 * officer's state; counts the player's officers. */
void func_003F4380(void)
{
    int entry = func_00327D50();
    int i, n = 0;

    for (i = 400; i < 0x19F; i++) {
        if (func_00327950() == 0 || func_0039E650(i - 400) == 0)
            func_002F3B30(i, 3);
        else if (entry != func_002F4080(i))
            func_003F4240(i);
    }
    for (i = 0; i < 0x19F; i++) {
        int ok = 0;

        if (i >= 0 && i < 0x19F)
            ok = 1;
        if (!ok)
            continue;
        if (entry == func_002F4080(i)) {
            func_002F32F0(i, 1);
            n++;
        } else {
            if (func_003278B0() != 0) {
                func_003A54A0(i);
                if (func_00327950() != 0 && i > 399 && i < 0x19F)
                    func_003A5650(i);
            }
            if (func_002F2840(i) != 0 && func_002F8CB0(func_002F4080(i)) != 0)
                func_002F4AE0(i, 7);
            func_002F32F0(i, 1);
        }
    }
    func_00327750(n);
}

/* 0x003F4530, 0x8 bytes, matching. Scene 0x17 draw: empty. */
void func_003F4530(void)
{
}

/* 0x003F4540, 0x8 bytes, matching. Scene 0x17 step: empty. */
void func_003F4540(void)
{
}

/* 0x003F4550, 0xD0 bytes, matching. Scene 0x17 update: once the fade is over, goes to the Empire map
 * (scene 0x12) unless another scene was asked for. */
int func_003F4550(void)
{
    if (func_0017DDA0() == 0) {
        if (g_0045D89C >= 0x18 && g_0045D8A0 >= 0x18)
            g_0045D89C = 0x12;
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
    return 1;
}

/* 0x003F4620, 0x8C bytes, matching. Scene 0x17 leave: frees the buffers. */
void func_003F4620(void)
{
    if (g_0045D860 != 0) {
        func_00102EC0(g_0045D860);
        g_0045D860 = 0;
    }
    if (g_0045D85C != 0) {
        func_00102EC0(g_0045D85C);
        g_0045D85C = 0;
    }
    if (g_0045D858 != 0) {
        func_00102EC0(g_0045D858);
        g_0045D858 = 0;
    }
    if (g_0045D854 != 0) {
        func_00102EC0(g_0045D854);
        g_0045D854 = 0;
    }
    if (g_0045D850 != 0) {
        func_00102EC0(g_0045D850);
        g_0045D850 = 0;
    }
}

/* 0x003F46B0, 0x184 bytes, matching. Scene 0x17 enter. */
void func_003F46B0(void)
{
    g_0045D850 = func_00102DB0(0x10, 0x25310);
    func_0011ED38(g_0045D850, 0, 0x25310);
    g_0045D854 = func_00102DB0(0x10, 0xFCE4);
    func_0011ED38(g_0045D854, 0, 0xFCE4);
    g_0045D858 = func_00102DB0(0x10, 500);
    func_0011ED38(g_0045D858, 0, 500);
    g_0045D85C = func_00102DB0(0x10, 3000);
    func_0011ED38(g_0045D85C, 0, 3000);
    g_0045D860 = func_00102DB0(0x10, 0xE0);
    func_0011ED38(g_0045D860, 0, 0xE0);
    if (func_0017DDA0() != 0)
        func_0017DF10();
    func_003F2B20();
    func_003F2C40();
    func_003F2DE0();
    func_003F2F60();
    func_003F3440();
    func_003F3790();
    func_003F3840();
    func_003F3B40();
    func_003F3E90();
    func_003F3FF0();
    func_003F4150();
    func_003F4380();
    func_003BAB70(func_003BA7F0(0));
    func_003BA8F0(0, func_0032EEB0(), func_002F5CC0(func_0032EEB0()), -1, -1);
    func_0030E090(6);
}
