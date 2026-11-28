/*
 * battle_flow.c - battle helpers between 0x00180880 and 0x00183EFC: troop headings and leaders,
 * the troop records' reset, the battle's end states (game state +0x210), the script message
 * queues (0x005BC3A0/0x005BC3A4) and the battle frame's order. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_BATTLE_FLOW_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8 g_00669D60[];
extern u8 g_006A3A30[][0xC0];
extern u8 g_00693970[];
extern int g_006AA574;
extern u8 *g_005BA6A0;
extern u32 *g_005BA7CC;                  /* the stage's script file */
extern u8 **g_005BA7E0;
extern u8 g_005BC3A0[4], g_005BC3A4[4];
extern u8 g_005BC2A0[0x40][4];

#define GAME_FLAGS (*(u32 *)(g_00669D60 + 0x200))
#define BATTLE_END (*(int *)(g_00669D60 + 0x210))

void func_0018A290(u8 *c, u8 a, int b);
void func_0022F510(void);
void func_00183A40(int a);
void func_0018AF30(void);

/* 0x00180880, 0x140 bytes. A troop faces like its leader's unit (when the leader is down). */
void func_00180880(u8 *t)
{
    u8 *o = g_006A3A30[*(int *)(t + 0x14)];

    if ((*(u32 *)(o + 0xB8) & 0xC) != 0) {
        float f = *(float *)(*(u8 **)(o + 0x14) + 0x54);

        if (3.1415927f < f)
            f -= 6.2831855f;
        else if (f <= -3.1415927f)
            f += 6.2831855f;
        *(float *)(t + 0x20) = f;
    }
}

/* 0x00180E90, 0x2C bytes, matching. Troop `t` loses its leader. */
void func_00180E90(u8 *t)
{
    *(int *)(t + 0x14) = 0x8F;
    *(u32 *)(t + 0x80) &= ~0x20000;
    *(u32 *)(t + 0x84) |= 0x10;
}

/* 0x00180EC0, 0x40 bytes. Troop `t` follows leader `v`. */
void func_00180EC0(u8 *t, int v)
{
    u64 *s = (*(u32 *)(t + 0x80) & 0x20000) == 0 ? (u64 *)(t + 0x28) : (u64 *)(t + 0x30);

    *(u64 *)(t + 0x30) = *s;
    *(int *)(t + 0x14) = v;
    *(u32 *)(t + 0x80) |= 0x20000;
}

/* 0x00182340, 8 bytes, matching. */
void func_00182340(void)
{
}

/* 0x00182350, 0x50 bytes. Clears the troop records. */
void func_00182350(void)
{
    func_00118850(g_00693970, 0xE3E8);
    g_006AA574 = 0;
    *(int *)PS2_PTR(0x70000160) = (GAME_FLAGS & 2) == 0 ? 0x50 : 0x3C;
}

/* 0x00182C20, 8 bytes, matching. */
void func_00182C20(void)
{
}

/* 0x00182E30, 0x40 bytes. The battle is lost. */
void func_00182E30(void)
{
    BATTLE_END = 3;
    GAME_FLAGS |= 0x4000000;
    func_001EE4A0(1);
}

/* 0x00182E70, 0x8C bytes. The battle is won (or a special end). */
void func_00182E70(void)
{
    u32 v = GAME_FLAGS | 0x4000000;

    if ((GAME_FLAGS & 4) == 0) {
        BATTLE_END = 0;
        GAME_FLAGS = v;
        func_001EE4A0(0);
    } else if (*(int *)(g_00669D60 + 0x238) % 5 == 4) {
        BATTLE_END = 8;
        GAME_FLAGS = v;
    } else {
        BATTLE_END = 9;
        GAME_FLAGS = v;
    }
}

/* 0x00182F00, 0x44 bytes. */
int func_00182F00(u8 *e)
{
    int r = func_0023E840(e);

    if (r != 0)
        e[0] &= 0xFC;
    return r != 0;
}

/* 0x00182F50, 0x98 bytes. Runs the next command of script event `e` (done after the last). */
void func_00182F50(u8 *e)
{
    u8 *s = (u8 *)g_005BA7CC + g_005BA7CC[3 + e[2]];

    func_0018A290(g_005BA7E0[e[2]] + e[3] * 0x10, e[1], 0);
    e[3]++;
    if (s[5] <= e[3])
        e[0] &= 0xFE;
}

/* 0x00182FF0, 0x20 bytes, matching. */
void func_00182FF0(u8 *d, u8 *s)
{
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = 0;
}

/* 0x00183010, 0x38 bytes. Queues script event `s` (queue `k`). */
void func_00183010(u8 *s, int k)
{
    func_00182FF0(k == 0 ? g_005BC3A0 : g_005BC3A4, s);
}

/* 0x001833C0, 0x48 bytes. */
void func_001833C0(int k)
{
    if (k == 0 || (u32)(BATTLE_END - 1) > 1)
        func_0022F510();
    func_00183240();
    func_00183130();
}

/* 0x001835E0, 0xC bytes. */
void func_001835E0(void)
{
    *(u32 *)g_005BC3A4 = 0;
}

/* 0x001835F0, 0xC bytes. */
void func_001835F0(void)
{
    *(u32 *)g_005BC3A0 = 0;
}

/* 0x00183600, 0x64 bytes. Clears the script event records. */
void func_00183600(void)
{
    u32 k;

    for (k = 0; k < 0x40; k++) {
        g_005BC2A0[k][0] = 0;
        g_005BC2A0[k][3] = 0;
    }
}

/* 0x001839B0, 0x20 bytes, matching. Doubles `v` in two-army battles. */
int func_001839B0(int v)
{
    if ((GAME_FLAGS & 2) != 0)
        v <<= 1;
    return v;
}

/* 0x001839D0, 0x68 bytes. The sum of the battle's counted values. */
int func_001839D0(void)
{
    int s = 0;
    u32 k;

    for (k = 0; k < 3; k++) {
        if (g_00669D60[0x248 + k] == 0)
            s += k < *(u32 *)(g_00669D60 + 0x214) ? *(int *)(g_00669D60 + 0x218 + k * 4) : 0;
    }
    return s;
}

/* 0x00183DE0, 0x84 bytes. The battle frame's script and end steps. */
void func_00183DE0(void)
{
    if ((GAME_FLAGS & 0x4000000) == 0) {
        if ((GAME_FLAGS & 0x10000000) == 0) {
            func_00186050();
            func_001833C0(0);
            func_0018BDE0();
            func_00183A40(0);
        } else {
            func_0018BDE0();
        }
    } else {
        func_001833C0(1);
        func_0018AF30();
    }
}

/* 0x00183E70, 0x8C bytes. Keeps officer `o`'s models, motions and voices loaded. */
void func_00183E70(u8 *o)
{
    u8 *r = g_005BA6A0 + *(u16 *)(o + 0x20) * 0x2C;

    func_00279380(o[6], 2);
    func_00279380(r[6], 2);
    func_00279450(o[7], 0);
    func_00279450(r[7], 0);
    func_002795A0(o[9]);
    func_002795A0(r[9]);
}

extern u32 g_006AA578;                   /* the next free battle officer */
extern int g_005BD738;

void func_001823A0(u8 *o);
void func_002A69D0(int k);
void func_00279240(void);
void func_002796A0(u32 a);
void func_0022FF00(void);
void func_002D6FC0(void);
void func_001BB7F0(int a);

#define OFF_FL(o) (*(u32 *)((o) + 0xB8))

/* 0x001827F0, 0xC0 bytes. The battle officers' frame (the shown life follows the life). */
void func_001827F0(void)
{
    u32 k;

    for (k = 0; k < 0x8F; k++) {
        u8 *o = g_006A3A30[k];
        u32 f;

        if ((OFF_FL(o) & 1) == 0)
            continue;
        if ((OFF_FL(o) & 0x6000C) != 0)
            func_001823A0(o);
        f = OFF_FL(o);
        if ((f & 0xC) == 0 || (f & 0x10) != 0) {
            if ((f & 2) == 0)
                func_002045E0(o);
        } else if (*(short *)(o + 0x82) < *(short *)(o + 0x84)) {
            *(short *)(o + 0x84) -= 1;
        }
    }
}

/* 0x001828C0, 0x90 bytes. Takes a free battle officer record (from 4 on; 0: none). */
u8 *func_001828C0(void)
{
    u32 n;

    for (n = 4; n < 0x7A; n++) {
        u8 *o = g_006A3A30[g_006AA578];

        if ((OFF_FL(o) & 1) == 0) {
            OFF_FL(o) |= 1;
            return o;
        }
        if (g_006AA578 < 0x79)
            g_006AA578++;
        else
            g_006AA578 = 4;
    }
    return 0;
}

/* 0x00182960, 0x7C bytes. Frees battle officer `o`. */
void func_00182960(u8 *o)
{
    if ((OFF_FL(o) & 0x8000) == 0)
        func_002A69D0((o - g_006A3A30[0]) / 0xC0);
    else
        func_00204D20(o);
    func_00166160(*(u8 **)(o + 0x14));
    *(u32 *)(o + 0xBC) = 0;
    OFF_FL(o) = 0;
}

/* 0x00182B40, 0xD8 bytes. Saves the four players' officers into `p`; its end. */
u8 *func_00182B40(u8 *p)
{
    u32 k;

    for (k = 0; k < 4; k++) {
        u8 *o = g_006A3A30[k];

        if ((OFF_FL(o) & 1) != 0) {
            func_00118AC0((unsigned int *)(p), *(u8 **)(o + 0x14) + 0x90, 0x10);
            func_00118AC0((unsigned int *)(p + 0x10), *(u8 **)(o + 0x14) + 0x50, 0x10);
            func_00118AC0((unsigned int *)(p + 0x20), o + 0x80, 0x18);
            func_00118AC0((unsigned int *)(p + 0x38), o + 0x98, 0x20);
            func_00118AC0((unsigned int *)(p + 0x58), o + 0xB8, 4);
            func_00118AC0((unsigned int *)(p + 0x5C), o + 0xBC, 4);
            p += 0x60;
        }
    }
    return p;
}

/* 0x00183F00, 0xF0 bytes. Keeps troop `t`'s two officers loaded (by its kind). */
void func_00183F00(u8 *t)
{
    u32 i = (t - g_00693970) / 0x88, f = *(u32 *)(t + 0x80);
    int kind = 2;
    u8 *a, *b;

    if ((f & 0x400) == 0 || func_00362F40(i >> 3, i & 7) == 0)
        return;
    a = *(u8 **)(t + 0xC);
    b = *(u8 **)(t + 8);
    if ((f & 0x10) != 0)
        kind = 0;
    else if ((f & 0x20) != 0)
        kind = 1;
    func_00279380(b[6], kind);
    func_00279380(a[6], kind);
    func_00279450(b[7], 0);
    func_00279450(a[7], 0);
    func_002795A0(b[9]);
    func_002795A0(a[9]);
}

/* 0x00184270, 0x8C bytes. */
void func_00184270(void)
{
    u32 k;

    for (k = 0; k < 0x1AD; k++) {
        u8 *t = g_00693970 + k * 0x88;
        u32 f = *(u32 *)(t + 0x80);

        if ((f & 1) != 0 && (f & 0x30) == 0 && (f & 0x180) == 0 && (k < 0x166 || k > 0x16F))
            func_00183F00(t);
    }
}

/* 0x00184980, 0x6C bytes, matching. */
void func_00184980(void)
{
    u32 k;

    func_00279240();
    for (k = 0x166; k < 0x170; k++) {
        u8 *t = g_00693970 + k * 0x88;

        if ((*(u32 *)(t + 0x80) & 1) != 0)
            func_00183F00(t);
    }
    func_002796A0(GAME_FLAGS & 2);
}

/* 0x00185160, 0xA4 bytes, matching. Frees the battle. */
void func_00185160(void)
{
    func_0018C080();
    func_0018BF10();
    func_002C4BF0();
    func_0023ED10();
    func_00356050();
    func_003577D0();
    func_0022FF00();
    func_0018BD40();
    func_0018B890();
    func_003E5DE0();
    func_003E5D20();
    func_00354560();
    func_001BC280();
    func_0036FEE0();
    func_0035E0D0();
    func_003F66B0();
    func_003F81D0();
    func_002D6FC0();
}

/* 0x00185300, 0x84 bytes. */
void func_00185300(void)
{
    if (*(int *)(g_00669D60 + 0x20C) == 1) {
        func_00184410();
        func_001BB7F0(0);
    } else {
        func_00183600();
        func_001835F0();
        func_001835E0();
        func_00184550();
        g_005BD738 = 1;
        func_00183A40(0);
    }
    func_003E5610();
    func_00184980();
}
