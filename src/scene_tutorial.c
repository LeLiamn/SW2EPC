/*
 * scene_tutorial.c - scenes 0x11 and 0x17 (original source file SceneTutorial.c: its name is
 * passed to the file loader at 0x003F4900). The whole file is decompiled (0x003F2A50-0x003F5550):
 * scenes 0x11 and 0x17, then the tutorial window that other scenes open (func_003F4D60).
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

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_0039E760   /* the original callers here see it this way */
int func_0039E760(int edited);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_002F3C20   /* the original callers here see it this way */
int func_002F3C20(void *);
#endif
#define SW2E_FILE_SCENE_TUTORIAL_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#include "sw2e_draw.h"

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

void func_0011ED38(void *to, int value, int size);
int func_002F7D90(int a, int (*filter)(), int value, int b, int c, int d);
void func_002F87D0(int *list, int n, int (*compare)(), int a, int b);
OfficerRecord *func_0030CCB0(void);
EntryRecord78 *func_0030CCC0(void);
int func_0017DDA0(void);
void func_0017DF10(void);

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
    int *officers = (int *)func_002F7B10();
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
    e14 = (EntryRecord14 *)(func_0030CCD0());
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
    p = (int *)(func_002F7B10());
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
        if (func_002F3C20((unsigned char *)(&g_0045D854[i])) != 0) {
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
        officers = (int *)(func_002F7B10());
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

        *(OfficerRecord *)func_002F2720(o) = g_0045D854[o];
    }
    for (i = 0; i < g_0045D860->count_b; i++) {
        int o = g_0045D860->list_b[i];

        *(OfficerRecord *)func_002F2720(o) = g_0045D854[o];
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
        func_00102EC0((unsigned char *)(g_0045D860));
        g_0045D860 = 0;
    }
    if (g_0045D85C != 0) {
        func_00102EC0((unsigned char *)(g_0045D85C));
        g_0045D85C = 0;
    }
    if (g_0045D858 != 0) {
        func_00102EC0((unsigned char *)(g_0045D858));
        g_0045D858 = 0;
    }
    if (g_0045D854 != 0) {
        func_00102EC0((unsigned char *)(g_0045D854));
        g_0045D854 = 0;
    }
    if (g_0045D850 != 0) {
        func_00102EC0((unsigned char *)(g_0045D850));
        g_0045D850 = 0;
    }
}

/* 0x003F46B0, 0x184 bytes, matching. Scene 0x17 enter. */
void func_003F46B0(void)
{
    g_0045D850 = (GameStateCopy *)(func_00102DB0(0x10, 0x25310));
    func_0011ED38(g_0045D850, 0, 0x25310);
    g_0045D854 = (OfficerRecord *)(func_00102DB0(0x10, 0xFCE4));
    func_0011ED38(g_0045D854, 0, 0xFCE4);
    g_0045D858 = (EntryRecord14 *)(func_00102DB0(0x10, 500));
    func_0011ED38(g_0045D858, 0, 500);
    g_0045D85C = (EntryRecord78 *)(func_00102DB0(0x10, 3000));
    func_0011ED38(g_0045D85C, 0, 3000);
    g_0045D860 = (TutorialSetup *)(func_00102DB0(0x10, 0xE0));
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

/* ---- The tutorial window (0x003F4840-0x003F5550) ---- */

typedef unsigned long long u64;

/* A window's animation (0x14 bytes, see battle_menu_draw.c). */
typedef struct {
    short x0, y0, w0, h0;
    short x1, y1, w1, h1;
    u8 alpha0, alpha1;
    u8 frames;
    u8 timer;
} WindowAnim;

/* The tutorial window (0x2C bytes, allocated by func_003F5430): its animation, the tutorial,
 * two page buffers loaded in turn, and the page shown. */
typedef struct {
    WindowAnim anim;
    int tutorial;            /* +0x14 (0-0x17) */
    u8 *page[2];             /* +0x18 the pictures of two pages */
    u8 loaded[2];            /* +0x20 per buffer: 1 loading, 2 loaded, 3 cancelled */
    u8 timer;                /* +0x22 */
    u8 mode;                 /* +0x23 0 closed, 1 open, 2 opening, 3 closing, 4 a page in, 5 a page out */
    u8 page_no;              /* +0x24 */
    u8 pages;                /* +0x25 */
    u8 shown;                /* +0x26 the buffer shown */
    u8 loading;              /* +0x27 the buffer loaded next */
    u8 had_box;              /* +0x28 the message box flags were free when it opened */
    u8 had_list;             /* +0x29 */
    u8 unknown_2a[2];
} TutorialWindow;

extern TutorialWindow *g_0045D864;        /* (small data) */

/* Shared menu flags (0x00799A24, see scene_edit.c). */
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

/* 0x00500700: the controllers' state, 0x88 bytes per controller (see scene_config.c). */
typedef struct {
    u8 unknown_00[0x4C];
    unsigned short pressed;
    unsigned short held;
    u8 unknown_50[0x14];
    u8 ready;
    u8 connected;
    u8 unknown_66[0x22];
} PadState;
extern PadState g_00500700[2];
#define PAD_READY(p) ((g_00500700[p].ready & 1) ? (g_00500700[p].connected & 1) == 1 : 0)
#define PAD_PRESSED(p) ((unsigned short)(PAD_READY(p) ? g_00500700[p].pressed : 0))

#define SE(kind) func_0023AD10((kind), 0, 0x2CDC, 0x2CDC, 0x1000)

#define g_70000154 (*(int *)PS2_PTR(0x70000154))    /* (scratchpad) the vertical scale */
#define GS_XYZ(x, y, z) ((u64)(long long)((x) * 16 + 0x7000) |                  \
                         (u64)(long long)(((y) * 16 - 0xE00) / g_70000154 + 0x8000) << 16 | \
                         (u64)(z) << 32)

extern int g_0041DA40[16];
void func_003F4A00(int mode);

/* 0x003F4840, 0x8 bytes, matching. */
TutorialWindow *func_003F4840(void)
{
    return g_0045D864;
}

/* 0x003F4850, 0x54 bytes. The LINKDATA entry of a tutorial's page (-1 = none). The original
 * copies a 16-entry table (0x0041DA40) but reads 72 words below it, outside the copy (on the
 * stack below its own frame); kept as it is. */
int func_003F4850(int tutorial, u8 page)
{
    int table[16];
    int i;

    for (i = 0; i < 16; i++)
        table[i] = g_0041DA40[i];
    return table[tutorial * 4 + page - 72];
}

/* 0x003F48B0, 0x48 bytes. How many pages a tutorial has (at most 4). */
int func_003F48B0(int tutorial)
{
    int i;

    for (i = 0; i < 4; i++)
        if (func_003F4850(tutorial, (u8)i) == -1)
            return i;
    return 4;
}

/* 0x003F4900, 0x78 bytes. Starts loading page `page` into the next buffer. */
void func_003F4900(int tutorial, u8 page)
{
    TutorialWindow *w = func_003F4840();
    int entry = func_003F4850(tutorial, page);

    if (entry != -1) {
        func_001026D0(1, entry, w->page[w->loading], 0, 0, 0, "SceneTutorial.c", 0x6B);
        w->loaded[w->loading] = 1;
    }
}

/* 0x003F4980, 0x3C bytes, matching. Swaps the buffer shown. */
void func_003F4980(void)
{
    TutorialWindow *w = func_003F4840();

    w->shown++;
    if (w->shown > 1)
        w->shown = 0;
}

/* 0x003F49C0, 0x3C bytes, matching. Swaps the buffer loaded next. */
void func_003F49C0(void)
{
    TutorialWindow *w = func_003F4840();

    w->loading++;
    if (w->loading > 1)
        w->loading = 0;
}

/* The window's animation (inlined). */
#define WINDOW(w, fx, fy, fw, fh, tx, ty, tw, th) do {                  \
        (w)->anim.x0 = (fx);                                            \
        (w)->anim.y0 = (fy);                                            \
        (w)->anim.w0 = (fw);                                            \
        (w)->anim.h0 = (fh);                                            \
        (w)->anim.x1 = (tx);                                            \
        (w)->anim.y1 = (ty);                                            \
        (w)->anim.w1 = (tw);                                            \
        (w)->anim.h1 = (th);                                            \
    } while (0)

/* 0x003F4A00, 0x2A8 bytes. Sets the window's mode and its animation: 0 closed (everything
 * reset), 1 open, 2 opening (10 frames), 3 closing (5), 4 the next page fading in (10), 5 the
 * page fading out (5). */
void func_003F4A00(int mode)
{
    TutorialWindow *w = func_003F4840();

    w->mode = mode;
    switch (mode) {
    case 0:
        w->tutorial = 0;
        w->timer = 0;
        w->page_no = 0;
        w->pages = 0;
        w->loaded[0] = 0;
        w->loaded[1] = 0;
        w->shown = 0;
        w->loading = 0;
        WINDOW(w, 0x100, 0xC9, 0, 0, 0x100, 0xC9, 0, 0);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0;
        w->anim.alpha1 = 0;
        break;
    case 1:
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0x80;
        w->anim.alpha1 = 0x80;
        break;
    case 2:
        w->timer = 0;
        w->shown = 0;
        w->loading = 0;
        WINDOW(w, 0x100, 0xC9, 0, 0, 0x100, 0xC9, 0, 0);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0;
        w->anim.alpha1 = 0;
        w->anim.x1 = 0x10;
        w->anim.y1 = 0x3B;
        w->anim.w1 = 0x1E0;
        w->anim.h1 = 0x11C;
        w->anim.alpha1 = 0x80;
        w->anim.frames = 10;
        break;
    case 3:
        w->timer = 0;
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0x80;
        w->anim.alpha1 = 0x80;
        w->anim.x1 = 0x100;
        w->anim.y1 = 0xC9;
        w->anim.w1 = 0;
        w->anim.h1 = 0;
        w->anim.alpha1 = 0;
        w->anim.frames = 5;
        break;
    case 4:
        func_003F4980();
        w->timer = 0;
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0;
        w->anim.alpha1 = 0;
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.alpha1 = 0x80;
        w->anim.frames = 10;
        break;
    case 5:
        w->timer = 0;
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.frames = 0;
        w->anim.timer = 0;
        w->anim.alpha0 = 0x80;
        w->anim.alpha1 = 0x80;
        WINDOW(w, 0x10, 0x3B, 0x1E0, 0x11C, 0x10, 0x3B, 0x1E0, 0x11C);
        w->anim.alpha1 = 0;
        w->anim.frames = 5;
        break;
    }
}

/* 0x003F4CB0, 0x68 bytes. Whether the window is shown (modes 1-5). */
int func_003F4CB0(void)
{
    TutorialWindow *w = func_003F4840();

    if (w == 0)
        return 0;
    switch (w->mode) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return 1;
    }
    return 0;                                     /* (the original returns an unset register) */
}

/* 0x003F4D20, 0x1C bytes, matching. Marks a tutorial as seen. */
void func_003F4D20(int tutorial)
{
    func_003A1CF0(tutorial, 1);
}

/* 0x003F4D40, 0x1C bytes, matching. */
int func_003F4D40(int k)
{
    return func_003A1DF0(k);
}

/* 0x003F4D60, 0x104 bytes. Opens tutorial `tutorial` (at most 0x17) unless func_003F4D40
 * holds: marks it seen, takes the message box and list flags, opens the window and loads its
 * first page. */
int func_003F4D60(int tutorial)
{
    TutorialWindow *w = func_003F4840();

    if (w == 0 || func_003F4D40(tutorial) != 0)
        return 0;
    func_003A1CF0(tutorial, 1);
    if (tutorial > 0x17)
        tutorial = 0x17;
    w->tutorial = tutorial;
    w->page_no = 0;
    w->pages = func_003F48B0(w->tutorial);
    w->had_box = s_00799A24.g_00799A2C == 0;
    w->had_list = s_00799A24.g_00799A44 == 0;
    s_00799A24.g_00799A28 = 0;
    s_00799A24.g_00799A2C = 1;
    s_00799A24.g_00799A44 = 1;
    s_00799A24.g_00799A40 = 0;
    s_00799A24.g_00799A24 = s_00799A24.g_00799A26;
    s_00799A24.g_00799A3C = s_00799A24.g_00799A3E;
    func_003F4A00(2);
    func_003F4900(w->tutorial, w->page_no);
    return 1;
}

/* 0x003F4E70, 0x30 bytes, matching. Whether the next buffer is loading. */
int func_003F4E70(void)
{
    TutorialWindow *w = func_003F4840();

    return w->loaded[w->loading] == 1;
}

/* 0x003F4EA0, 0x2C bytes. Whether buffer `i` is loaded. */
int func_003F4EA0(u8 i)
{
    return func_003F4840()->loaded[i] == 2;
}

/* 0x003F4ED0, 0x2C bytes, matching. */
void func_003F4ED0(void)
{
    TutorialWindow *w = func_003F4840();

    w->loaded[w->loading] = 2;
}

/* 0x003F4F00, 0x38 bytes, matching. Cancels the load. */
void func_003F4F00(void)
{
    TutorialWindow *w = func_003F4840();

    func_00102990();
    w->loaded[w->loading] = 3;
}

/* 0x003F4F40, 0x1D4 bytes. Draws the window: the screen darkened (alpha / 4), the frame, and
 * the page shown once loaded. */
void func_003F4F40(void)
{
    TutorialWindow *w = func_003F4840();
    short pos[4];
    u8 alpha, frame_alpha;
    int dark;
    u64 *p;

    if (w == 0 || w->mode == 0)
        return;
    func_001AE550(1.0f, &w->anim, pos, &alpha, 0);
    dark = (alpha * 0x20) >> 7;
    frame_alpha = alpha;
    if ((u32)(w->mode - 4) < 2) {
        frame_alpha = 0x80;
        dark = 0x20;
    }
    p = (u64 *)(func_00105410());
    p[3] = (u64)(long long)dark << 24 | 0x3F80000000000000ULL;
    p[4] = GS_XYZ(0, 0, 0xFFFE);
    p[5] = GS_XYZ(0x200, 0x1C0, 0xFFFE);
    func_001054B0((unsigned char *)(p), 3);
    func_001A4340(pos[0], pos[1], 0, pos[2], pos[3], frame_alpha, 3);
    if (func_003F4EA0(w->shown) != 0)
        func_001ABA70(w->page[w->shown], pos[0], pos[1], 0, pos[2], pos[3], alpha, 3, 0);
}

/* 0x003F5120, 0x2E8 bytes. Steps the window (controller `port`): finishes the loads, preloads
 * the next page, runs the animations; while open, OK turns the page or closes the window on the
 * last one. Gives 0 when closed, 2 the frame it closes, else 1. */
int func_003F5120(int port)
{
    TutorialWindow *w = func_003F4840();

    if (w == 0 || w->mode == 0)
        return 0;
    if (func_003F4E70() != 0 && func_00102960(0) != 0)
        func_003F4ED0();
    if (func_003F4EA0(w->loading) != 0 && w->shown == w->loading && w->page_no < w->pages - 1) {
        func_003F49C0();
        func_003F4900(w->tutorial, w->page_no + 1);
    }
    if (w->mode == 2 || w->mode == 4) {
        w->timer++;
        if (w->timer > 9)
            func_003F4A00(1);
        return 1;
    }
    if (w->mode == 5) {
        w->timer++;
        if (w->timer > 4)
            func_003F4A00(4);
        return 1;
    }
    if (w->mode == 3) {
        w->timer++;
        if (w->timer < 5)
            return 1;
        if (w->had_box == 1) {
            s_00799A24.g_00799A24 = s_00799A24.g_00799A26;
            s_00799A24.g_00799A28 = 1;
            s_00799A24.g_00799A2C = 0;
            w->had_box = 0;
        }
        if (w->had_list == 1) {
            s_00799A24.g_00799A40 = 1;
            s_00799A24.g_00799A44 = 0;
            s_00799A24.g_00799A3C = s_00799A24.g_00799A3E;
            w->had_list = 0;
        }
        func_003F4A00(0);
        return 2;
    }
    if (func_003F4EA0(w->shown) == 0)
        return 1;
    if (PAD_PRESSED(port) & 0x40) {
        if (w->page_no >= w->pages - 1) {
            SE(1);
            func_003F4A00(3);
            return 1;
        }
        SE(1);
        w->page_no++;
        func_003F4A00(5);
    }
    return 1;
}

/* 0x003F5410, 0x1C bytes, matching. */
int func_003F5410(void)
{
    return func_003F5120(0);
}

/* 0x003F5430, 0x88 bytes. Creates the window and its two page buffers (the size of LINKDATA
 * entry 0x91, rounded up to 0x800). */
void func_003F5430(void)
{
    g_0045D864 = (TutorialWindow *)(func_00102DB0(0x10, 0x2C));
    func_00118850((unsigned char *)(g_0045D864), 0x2C);
    g_0045D864->page[0] = func_00102DB0(0x40, (func_00102680(1, 0x91) + 0x7FF) & ~0x7FF);
    g_0045D864->page[1] = func_00102DB0(0x40, (func_00102680(1, 0x91) + 0x7FF) & ~0x7FF);
    func_003F4A00(0);
}

/* 0x003F54C0, 0x90 bytes, matching. Frees the window (cancelling a load). */
void func_003F54C0(void)
{
    if (g_0045D864 == 0)
        return;
    if (func_003F4E70() != 0)
        func_003F4F00();
    if (g_0045D864->page[1] != 0)
        func_00102EC0(g_0045D864->page[1]);
    g_0045D864->page[1] = 0;
    if (g_0045D864->page[0] != 0)
        func_00102EC0(g_0045D864->page[0]);
    g_0045D864->page[0] = 0;
    if (g_0045D864 != 0)
        func_00102EC0((unsigned char *)(g_0045D864));
    g_0045D864 = 0;
}
