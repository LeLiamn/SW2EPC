/*
 * battle_flow.c - battle helpers between 0x00180880 and 0x00183EFC: troop headings and leaders,
 * the troop records' reset, the battle's end states (game state +0x210), the script message
 * queues (0x005BC3A0/0x005BC3A4) and the battle frame's order. Original file names unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

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

void func_00118850(void *p, int n);
void func_001EE4A0(int a);
int func_0023E840(u8 *e);
void func_0018A290(u8 *c, u8 a, int b);
void func_0022F510(void);
void func_00183240(void);
void func_00183130(void);
void func_00186050(void);
void func_0018BDE0(void);
void func_00183A40(int a);
void func_0018AF30(void);
void func_00279380(u8 k, int a);
void func_00279450(u8 k, int a);
void func_002795A0(u8 k);

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
    *(int *)0x70000160 = (GAME_FLAGS & 2) == 0 ? 0x50 : 0x3C;
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
