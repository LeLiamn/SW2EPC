/*
 * emp_game_state.c - the Empire mode's game state (0x0068DDE0, saved with the game): its field
 * accessors (0x00327710-0x003298AC). Original file name unknown (it lies between the turn code
 * and emp_ev_still.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Layout (offsets from 0x0068DDE0): +0x000 12 alliance slots (two forces each), +0x060 the
 * province flags, +0x140 two-bit event states (from event 6), +0x170 10 timed records (who,
 * frames), +0x1C0 a 0x618-byte block, +0x7D8 a 0x34-byte block, +0x80C 0x79 entries of 0x14
 * bytes, +0x11F8 the seed, +0x11FC the play time, +0x1200.. the scalar fields below,
 * +0x1234 five items, +0x1239 28 nibble pairs, +0x1278 five more items.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_0068DDE0[];                  /* the Empire game state */
extern int g_004479DC[], g_00447848[], g_004479E0[];
extern u8 g_0045D6C8[];                  /* (small data) */

#define GS(o) (g_0068DDE0 + (o))
#define GS8(o) (*(u8 *)GS(o))
#define GS16(o) (*(u16 *)GS(o))
#define GS32(o) (*(u32 *)GS(o))

#define FLAGS GS16(0x1210)               /* 0x0068EFF0 */
#define FLAGS2 GS8(0x1225)               /* 0x0068F005 */

void func_0011EB80(u8 *to, const u8 *from, int n);
void func_0011ED38(u8 *p, int v, int n);
u8 *func_002F2890(u32 o);
int func_0030AB90(void);
int func_002F8F20(int f);
int func_002F5CC0(int o);
int func_00327140(int s, int t);
int func_00327170(int t);
int func_002F57F0(int k);
u8 func_002F5840(int v);
int func_002F5890(int o);
void func_00328470(void);
void func_00328820(void);
void func_00328D00(int i, int v);
void func_00328EC0(int i, int v);

/* 0x00327710, 0x34 bytes. */
void func_00327710(int v)
{
    if (v >= 0 && v < 0x927C1)
        GS16(0x1200) = v;
}

/* 0x00327750, 0x2C bytes. */
void func_00327750(int v)
{
    if (v >= 0 && v < 0x19F)
        GS16(0x1202) = v;
}

/* 0x00327780, 0x94 bytes. Sets the ruler (and copies his name; cleared for none). */
void func_00327780(u32 o)
{
    if (o >= 0x1A0)
        return;
    GS16(0x1204) = o;
    if (o < 0x19F)
        func_0011EB80(GS(0x125F), func_002F2890(o), 0x19);
    else
        func_0011ED38(GS(0x125F), 0, 0x19);
}

/* 0x00327820, 0xC bytes, matching. The ruler. */
u16 func_00327820(void)
{
    return GS16(0x1204);
}

/* 0x00327830, 0x3C bytes. */
void func_00327830(u32 o)
{
    if (o < 0x1A0)
        GS16(0x1206) = o;
}

/* 0x00327870, 0xC bytes, matching. */
u16 func_00327870(void)
{
    return GS16(0x1206);
}

/* 0x00327880, 0x30 bytes. Flag 1 (set when `v` is 0). */
void func_00327880(int v)
{
    if (v == 0)
        FLAGS |= 1;
    else
        FLAGS &= 0xFFFE;
}

/* 0x003278B0, 0x18 bytes. */
int func_003278B0(void)
{
    return (FLAGS & 1) == 0;
}

/* 0x003278D0, 0x30 bytes. */
void func_003278D0(int v)
{
    if (v == 0)
        FLAGS |= 2;
    else
        FLAGS &= 0xFFFD;
}

/* 0x00327900, 0x18 bytes. */
int func_00327900(void)
{
    return (FLAGS & 2) == 0;
}

/* 0x00327920, 0x30 bytes. */
void func_00327920(int v)
{
    if (v == 0)
        FLAGS |= 4;
    else
        FLAGS &= 0xFFFB;
}

/* 0x00327950, 0x18 bytes. */
int func_00327950(void)
{
    return (FLAGS & 4) == 0;
}

/* 0x00327970, 0x38 bytes. A two-bit mode (0-2). */
void func_00327970(int v)
{
    if (v < 3)
        FLAGS = (FLAGS & 0xFFCF) | (u16)(v << 4);
}

/* 0x003279B0, 0x14 bytes, matching. */
int func_003279B0(void)
{
    return (FLAGS & 0x30) >> 4;
}

/* 0x003279D0, 0x38 bytes. A three-bit value (0-4). */
void func_003279D0(int v)
{
    if (v < 5)
        FLAGS = (FLAGS & 0x8FFF) | (u16)(v << 0xC);
}

/* 0x00327A10, 0x14 bytes, matching. */
int func_00327A10(void)
{
    return (FLAGS & 0x7000) >> 0xC;
}

/* 0x00327A30, 0x30 bytes. */
void func_00327A30(int v)
{
    if (v == 0)
        FLAGS |= 8;
    else
        FLAGS &= 0xFFF7;
}

/* 0x00327A60, 0x18 bytes. */
int func_00327A60(void)
{
    return (FLAGS & 8) == 0;
}

/* 0x00327A80, 0x5C bytes. The player officers (4 slots). */
void func_00327A80(u32 o, int k)
{
    if (o < 0x1A0 && k < 4)
        ((u16 *)GS(0x1212))[k] = o;
}

/* 0x00327AE0, 0x30 bytes. */
u16 func_00327AE0(int k)
{
    if (k < 4)
        return ((u16 *)GS(0x1212))[k];
    return 0x19F;
}

/* 0x00327B10, 0x58 bytes. Officer `o`'s player slot (4: none). */
int func_00327B10(int o)
{
    int k;

    for (k = 0; k < 4; k++) {
        if (o == func_00327AE0(k))
            return k;
    }
    return 4;
}

/* 0x00327B70, 0x60 bytes. Whether a player slot is used. */
int func_00327B70(void)
{
    int k;

    for (k = 0; k < 4; k++) {
        if (func_00327AE0(k) < 0x19F)
            return 1;
    }
    return 0;
}

/* 0x00327BD0, 0x2C bytes. The scenario (0-10). */
void func_00327BD0(int v)
{
    if (v >= 0 && v < 0xB)
        GS8(0x121A) = v;
}

/* 0x00327C00, 0xC bytes, matching. */
u8 func_00327C00(void)
{
    return GS8(0x121A);
}

/* 0x00327C10, 0x2C bytes. The difficulty (0-4). */
void func_00327C10(int v)
{
    if (v >= 0 && v < 5)
        GS8(0x121B) = v;
}

/* 0x00327C40, 0xC bytes, matching. */
u8 func_00327C40(void)
{
    return GS8(0x121B);
}

/* 0x00327C50, 0x20 bytes, matching. The turn. */
void func_00327C50(u32 v)
{
    if (v < 0x10000)
        GS16(0x1208) = v;
}

/* 0x00327C70, 0xC bytes, matching. */
u16 func_00327C70(void)
{
    return GS16(0x1208);
}

/* 0x00327C80, 0x34 bytes. The current year. */
int func_00327C80(void)
{
    return func_00327140(func_00327C00(), func_00327C70());
}

/* 0x00327CC0, 0x24 bytes. The current season. */
int func_00327CC0(void)
{
    return func_00327170(func_00327C70());
}

/* Whether `v` is a force (or 0x19, none). */
static int force_or_none(int v)
{
    int ok = 0;

    if (v >= 0)
        ok = v < func_0030AB90();
    if (!ok)
        ok = v == 0x19;
    return ok;
}

/* 0x00327CF0, 0x5C bytes. The player's force. */
void func_00327CF0(int v)
{
    if (force_or_none(v))
        GS8(0x121C) = v;
}

/* 0x00327D50, 0xC bytes, matching. */
u8 func_00327D50(void)
{
    return GS8(0x121C);
}

/* 0x00327D60, 0x54 bytes. The province of the player force's ruler (0x19: none). */
int func_00327D60(void)
{
    int o = func_002F8F20(func_00327D50());

    if (o < 0 || o > 0x19E)
        return 0x19;
    return func_002F5CC0(o);
}

/* 0x00327DC0, 0x2C bytes. */
void func_00327DC0(int v)
{
    if (v >= 0 && v < 0x19)
        GS8(0x121D) = v;
}

/* 0x00327DF0, 0x2C bytes. */
void func_00327DF0(int v)
{
    if (v >= 0 && v < 4)
        GS8(0x121E) = v;
}

/* 0x00327E20, 0xC bytes, matching. */
u8 func_00327E20(void)
{
    return GS8(0x121E);
}

/* 0x00327E30, 0x1C bytes, matching. */
void func_00327E30(int v)
{
    if (v < 0x97)
        GS8(0x121F) = v;
}

/* 0x00327E50, 0xC bytes, matching. */
u8 func_00327E50(void)
{
    return GS8(0x121F);
}

/* 0x00327E60, 0x30 bytes. A value in -15..15. */
void func_00327E60(int v)
{
    if (v > -0x10 && v < 0x10)
        GS8(0x1220) = v;
}

/* 0x00327E90, 0xC bytes, matching. */
char func_00327E90(void)
{
    return GS8(0x1220);
}

/* 0x00327EA0, 0x54 bytes. Adds `d` to it (kept within -15..15). */
void func_00327EA0(int d)
{
    d += func_00327E90();
    if (d < -0xF)
        d = -0xF;
    else if (d > 0xF)
        d = 0xF;
    func_00327E60(d);
}

/* 0x00327F00, 0x5C bytes. */
void func_00327F00(int v)
{
    if (force_or_none(v))
        GS8(0x1221) = v;
}

/* 0x00327F60, 0xC bytes, matching. */
u8 func_00327F60(void)
{
    return GS8(0x1221);
}

/* 0x00327F70, 0x5C bytes. */
void func_00327F70(int v)
{
    if (force_or_none(v))
        GS8(0x1222) = v;
}

/* 0x00327FD0, 0xC bytes, matching. */
u8 func_00327FD0(void)
{
    return GS8(0x1222);
}

/* 0x00327FE0, 0x5C bytes. */
void func_00327FE0(int v)
{
    if (force_or_none(v))
        GS8(0x1223) = v;
}

/* 0x00328040, 0xC bytes, matching. */
u8 func_00328040(void)
{
    return GS8(0x1223);
}

/* 0x00328050, 0x5C bytes. */
void func_00328050(int v)
{
    if (force_or_none(v))
        GS8(0x1224) = v;
}

/* 0x003280B0, 0xC bytes, matching. */
u8 func_003280B0(void)
{
    return GS8(0x1224);
}

/* 0x003280C0, 0x1C bytes, matching. */
void func_003280C0(int v)
{
    if (v < 6)
        GS8(0x1226) = v;
}

/* 0x003280E0, 0xC bytes, matching. */
u8 func_003280E0(void)
{
    return GS8(0x1226);
}

/* 0x003281F0, 0x3C bytes. */
void func_003281F0(int v)
{
    if (v == 0)
        FLAGS2 &= 0xFE;
    else
        FLAGS2 |= 1;
}

/* 0x00328230, 0x10 bytes, matching. */
u8 func_00328230(void)
{
    return FLAGS2 & 1;
}

/* 0x00328240, 0x2C bytes. */
void func_00328240(char v)
{
    FLAGS2 = v << 1 | (FLAGS2 & 0x11);
}

/* 0x00328270, 0x18 bytes. */
u8 func_00328270(void)
{
    return FLAGS2 >> 1 & 7;
}

/* 0x00328290, 0x24 bytes. */
void func_00328290(char v)
{
    FLAGS2 |= v << 4;
}

/* 0x003282C0, 0x18 bytes. */
u8 func_003282C0(void)
{
    return FLAGS2 >> 4 & 1;
}

/* 0x003282E0, 0xC bytes, matching. */
void func_003282E0(void)
{
    FLAGS2 = 0;
}

/* 0x003282F0, 0x38 bytes. The first five items (100: empty). */
void func_003282F0(int v, int k)
{
    if (v < 0x65 && k < 5)
        GS8(0x1234 + k) = v;
}

/* 0x00328330, 0x2C bytes. */
u8 func_00328330(int k)
{
    if (k < 5)
        return GS8(0x1234 + k);
    return 100;
}

/* 0x00328360, 0x6C bytes. Adds item `v` (in the first empty slot). */
void func_00328360(int v)
{
    int k;

    for (k = 0; k < 5; k++) {
        if (func_00328330(k) > 99) {
            func_003282F0(v, k);
            break;
        }
    }
    func_00328470();
}

/* 0x003283D0, 0x6C bytes. Removes item `v`. */
void func_003283D0(int v)
{
    int k;

    for (k = 0; k < 5; k++) {
        if (v == func_00328330(k)) {
            func_003282F0(100, k);
            break;
        }
    }
    func_00328470();
}

/* 0x00328440, 0x28 bytes, matching. Empties slot `k`. */
void func_00328440(int k)
{
    func_003282F0(100, k);
    func_00328470();
}

/* 0x00328570, 0x58 bytes. How many slots hold an item. */
int func_00328570(void)
{
    int k, n = 0;

    for (k = 0; k < 5; k++) {
        if (func_00328330(k) < 100)
            n++;
    }
    return n;
}

/* 0x003285D0, 0x24 bytes, matching. Whether all are full. */
int func_003285D0(void)
{
    return func_00328570() == 5;
}

/* 0x00328600, 0x38 bytes. The five reward items (100: empty). */
void func_00328600(int v, int k)
{
    if (v < 0x65 && k < 5)
        GS8(0x1278 + k) = v;
}

/* 0x00328640, 0x2C bytes. */
u8 func_00328640(int k)
{
    if (k < 5)
        return GS8(0x1278 + k);
    return 100;
}

/* 0x00328670, 0x6C bytes. */
void func_00328670(int v)
{
    int k;

    for (k = 0; k < 5; k++) {
        if (func_00328640(k) > 99) {
            func_00328600(v, k);
            break;
        }
    }
    func_00328820();
}

/* 0x003286E0, 0x6C bytes. */
void func_003286E0(int v)
{
    int k;

    for (k = 0; k < 5; k++) {
        if (v == func_00328640(k)) {
            func_00328600(100, k);
            break;
        }
    }
    func_00328820();
}

/* 0x00328750, 0x28 bytes, matching. */
void func_00328750(int k)
{
    func_00328600(100, k);
    func_00328820();
}

/* 0x00328780, 0x2C bytes, matching. */
int func_00328780(int v)
{
    if (v == 0)
        return 0x65;
    return g_004479DC[v];
}

/* 0x003287B0, 0x50 bytes. A reward item's value (0 past them). */
int func_003287B0(int v)
{
    if ((v < 0x5A || v > 0x62) && v != 0x65)
        return 0;
    return g_00447848[v];
}

/* 0x00328800, 0x18 bytes, matching. */
int func_00328800(int v)
{
    return g_004479E0[v];
}

/* 0x00328970, 0x58 bytes. */
int func_00328970(void)
{
    int k, n = 0;

    for (k = 0; k < 5; k++) {
        if (func_00328640(k) < 100)
            n++;
    }
    return n;
}

/* 0x003289D0, 0x24 bytes, matching. */
int func_003289D0(void)
{
    return func_00328970() == 5;
}

/* 0x00328A00, 0x60 bytes. The high nibble of entry `k` (0-1). */
void func_00328A00(int k, int v)
{
    if (k < 0x1C && v < 2) {
        u8 *b = GS(0x1239 + k);

        *b &= 0xF;
        *b |= (u8)(v << 4);
    }
}

/* 0x00328A60, 0x34 bytes. */
int func_00328A60(int k)
{
    if (k < 0x1C)
        return (GS8(0x1239 + k) & 0xF0) >> 4;
    return 2;
}

/* 0x00328AA0, 0x5C bytes. The low nibble. */
void func_00328AA0(int k, int v)
{
    if (k < 0x1C && v < 2) {
        u8 *b = GS(0x1239 + k);

        *b &= 0xF0;
        *b |= (u8)v;
    }
}

/* 0x00328B00, 0x30 bytes. */
u8 func_00328B00(int k)
{
    if (k < 0x1C)
        return GS8(0x1239 + k) & 0xF;
    return 2;
}

/* 0x00328B30, 0x64 bytes. Entry `k` of 0x79 (its +0x12 refreshed). */
u8 *func_00328B30(int k)
{
    u8 *r;

    if (k >= 0x79)
        return 0;
    r = GS(0x80C) + k * 0x14;
    r[0x12] = func_002F5840(func_002F57F0(k));
    return r;
}

/* 0x00328BA0, 0x54 bytes. */
void func_00328BA0(int k, int on)
{
    if (k < 0x79) {
        u8 *p = func_00328B30(k);

        *p = on == 0 ? 0x7F : k;
    }
}

/* 0x00328C00, 0x38 bytes. */
int func_00328C00(int k)
{
    if (k < 0x79)
        return *(char *)func_00328B30(k) != 0x7F;
    return 0;
}

/* 0x00328C40, 0x38 bytes. */
int func_00328C40(int a, int b)
{
    if (a == 0x1D)
        return b == 3 ? 0x78 : b + 0x68;
    return b + a * 4;
}

/* 0x00328C80, 0x30 bytes, matching. */
int func_00328C80(int o, int b)
{
    return func_00328C40(func_002F5890(o), b);
}

/* 0x00328CB0, 0x50 bytes. */
void func_00328CB0(void)
{
    int i;

    for (i = 0; i < func_0030AB90(); i++)
        func_00328D00(i, 0);
}

/* 0x00328E70, 0x50 bytes. */
void func_00328E70(void)
{
    int i;

    for (i = 0; i < func_0030AB90(); i++)
        func_00328EC0(i, 0);
}

/* 0x00329370, 0x48 bytes. The frames left of `who`'s timed record (0: none). */
int func_00329370(int who)
{
    int k;

    for (k = 0; k < 10; k++) {
        if (*(int *)GS(0x170 + k * 8) == who)
            return *(int *)GS(0x174 + k * 8);
    }
    return 0;
}

/* 0x003293C0, 0x40 bytes. How many timed records are used. */
int func_003293C0(void)
{
    int k, n = 0;

    for (k = 0; k < 10; k++) {
        if (*(int *)GS(0x170 + k * 8) != -1)
            n++;
    }
    return n;
}

/* 0x00329400, 0x48 bytes. Counts the timed records down (freed at 0). */
void func_00329400(void)
{
    int k;

    for (k = 0; k < 10; k++) {
        int *r = (int *)GS(0x170 + k * 8);

        if (r[1] != 0 && --r[1] == 0)
            r[0] = -1;
    }
}

/* 0x00329450, 0x48 bytes. */
void func_00329450(int s, int v)
{
    if (s >= 0 && s < 2 && v >= 0 && v < 5)
        GS8(0x125D + s) = v;
}

/* 0x003294A0, 0x34 bytes. */
u8 func_003294A0(int s)
{
    if (s < 0 || s > 1)
        return 4;
    return GS8(0x125D + s);
}

/* 0x00329590, 8 bytes, matching. */
void func_00329590(void)
{
}

/* 0x003295A0, 0x48 bytes. Clears event `k`'s state (events 6-0x12, two bits each). */
void func_003295A0(int k)
{
    u32 sh = (k - 6) * 2;
    int w = (int)sh > 0x1F;

    if (w)
        sh -= 0x20;
    ((u32 *)GS(0x140))[w] &= ~(3 << (sh & 0x1F));
}

/* 0x003295F0, 0x84 bytes. Sets it. */
void func_003295F0(int k, u32 v)
{
    u32 sh;
    int w;

    func_003295A0(k);
    sh = (k - 6) * 2;
    w = (int)sh > 0x1F;
    if (w)
        sh -= 0x20;
    ((u32 *)GS(0x140))[w] |= (v & 3) << (sh & 0x1F);
}

/* 0x00329680, 0x3C bytes. */
u32 func_00329680(int k)
{
    u32 sh = (k - 6) * 2;
    int w = (int)sh > 0x1F;

    if (w)
        sh -= 0x20;
    return ((u32 *)GS(0x140))[w] >> (sh & 0x1F) & 3;
}

/* 0x003296C0, 0x24 bytes, matching. Whether event `k` is running (state 1). */
int func_003296C0(int k)
{
    return func_00329680(k) == 1;
}

/* 0x003296F0, 0x44 bytes. The running event (0x13: none). */
int func_003296F0(void)
{
    int k;

    for (k = 6; k < 0x13; k++) {
        if (func_003296C0(k) != 0)
            return k;
    }
    return k;
}

/* 0x00329740, 0x50 bytes, matching. Ends the running events (state 2). */
void func_00329740(void)
{
    int k;

    for (k = 6; k < 0x13; k++) {
        if (func_00329680(k) == 1)
            func_003295F0(k, 2);
    }
}

/* `v` kept within 0-1000. */
static short clamp1000(int v)
{
    if (v > 1000)
        v = 1000;
    if (v < 1)
        v = 0;
    return v;
}

/* 0x00329790, 0xC bytes, matching. */
u16 func_00329790(void)
{
    return GS16(0x120A);
}

/* 0x003297A0, 0x30 bytes. */
void func_003297A0(int v)
{
    GS16(0x120A) = clamp1000(v);
}

/* 0x003297D0, 0xC bytes, matching. */
u16 func_003297D0(void)
{
    return GS16(0x120C);
}

/* 0x003297E0, 0x30 bytes. */
void func_003297E0(int v)
{
    GS16(0x120C) = clamp1000(v);
}

/* 0x00329810, 0xC bytes, matching. */
u16 func_00329810(void)
{
    return GS16(0x120E);
}

/* 0x00329820, 0x30 bytes. */
void func_00329820(int v)
{
    GS16(0x120E) = clamp1000(v);
}

/* 0x00329850, 0xC bytes, matching. */
u8 *func_00329850(void)
{
    return GS(0x1C0);
}

/* 0x00329860, 0xC bytes, matching. */
u8 *func_00329860(void)
{
    return GS(0x7D8);
}

/* 0x00329870, 0xC bytes, matching. */
u8 func_00329870(void)
{
    return GS8(0x127D);
}

/* 0x00329880, 0xC bytes, matching. */
void func_00329880(u8 v)
{
    GS8(0x127D) = v;
}

/* 0x00329890, 8 bytes. */
u8 *func_00329890(void)
{
    return g_0045D6C8;
}

/* 0x003298A0, 0xC bytes, matching. */
void func_003298A0(int *p)
{
    p[0] = 0;
    p[1] = 0;
}
