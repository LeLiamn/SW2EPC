/*
 * battle_formation.c - the armies' formations during a battle (original source file unknown;
 * the module follows the missions, 0x003F6BA0-0x003F84A4).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Each side (0 the player, 1 the enemy) has six formation slots (a formation 0-9, 10 = none,
 * and a "used" bit), the slot in use, points (0-180) to pay for a change (func_003F7110 the
 * cost), three flags and a counter (0-300). The formations' advantage over each other is a
 * 10 x 10 table (func_003F7090: > 0 better, < 0 worse); a change gives the side with the
 * advantage a bonus (func_0033BE80). The points grow by one every 100 frames and by 30 (150 every
 * 1000) for each 50 of func_003F7C60's count; the enemy picks its formation at the start
 * (func_003F8000) by a random mood: 30% worse, 50% equal, 20% better than the player's. Page 10
 * of the battle menu changes the player's formation (battle_menu_draw.c, scene_battle_menu.c).
 * An Empire battle keeps the state in its save (record +0xAE8).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A side's formations (0x007BFEF0, 16 bytes a side). */
typedef struct {
    u8 slot;                 /* the slot in use (0-5) */
    u8 formation[6];         /* per slot: bits 0-6 the formation (10 = none), bit 7 used */
    u8 points;               /* 0-180 */
    u8 flags;                /* bit 0 the advantage, bit 1 changed, bit 2 warned */
    u8 unknown_9;
    u16 counter;             /* 0-300 */
    u8 unknown_c[4];
} Formations;

extern Formations g_007BFEF0[2];

/* The game state (0x00669D60), the fields used here. */
extern struct {
    u8 unknown_0[0x20C];
    int g_00669F6C;          /* 1: an Empire battle */
    u8 unknown_210[0x2C];
    u32 g_00669F9C;          /* the battle's time (frames) */
} g_00669D60;

#define g_7000015C (*(u32 *)0x7000015C)   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)

typedef struct { int v[100]; } Advantages;
typedef struct { int v[10]; } PerFormation;
typedef struct { int v[9]; } PerKind;

extern int g_0041DAE0[100];               /* formation x formation: the advantage */
extern int g_0041DC70[10];                /* per formation: its cost */
extern int g_0041DCA0[10], g_0041DCD0[10], g_0041DD30[10];
extern int g_0041DD00[9];

void func_00118AC0(void *to, const void *from, int size);
void func_00118850(void *to, int size);
u8 *func_002EFB00(int slot);
u32 func_0033F7D0(int side, int a);
void func_0033BE80(int side, int a, int value);
void func_003AFD90(void);
u8 func_0035D5A0(u32 side);
void func_0035D360(u32 side, u32 slot, int a);
void func_0035D3E0(u32 side);
void func_0035D410(u32 side);
u32 func_00362CE0(void);
u32 func_00362C10(u32 side, u32 slot);
u32 func_00362C80(u32 side);
void func_00362C50(u32 side, u32 slot);
void func_0035D3A0(void);
int func_0036D2E0(void);
int func_00328780(u32 formation);
void func_003286E0(int a);
int func_0032E7B0(void);
u32 func_00362D70(int side);
void func_00362BD0(u32 side, u32 slot, u32 formation);

void func_003F7640(void);
u8 func_003F6CA0(u32 side, u32 slot);
u8 func_003F6E60(u32 side);

/* 0x003F6BA0, 0x3C bytes. */
void func_003F6BA0(u32 side, u32 slot)
{
    if (side < 2 && slot < 6)
        g_007BFEF0[side].slot = slot;
}

/* 0x003F6BE0, 0x30 bytes, matching. */
u8 func_003F6BE0(u32 side)
{
    if (side < 2)
        return g_007BFEF0[side].slot;
    return 10;
}

/* 0x003F6C10, 0x30 bytes. The formation in use. */
u8 func_003F6C10(u32 side)
{
    return func_003F6CA0(side, func_003F6BE0(side));
}

/* 0x003F6C40, 0x58 bytes. */
void func_003F6C40(u32 side, u32 slot, u8 formation)
{
    if (side < 2 && slot < 6) {
        u8 *f = &g_007BFEF0[side].formation[slot];

        *f &= 0x80;
        *f |= formation & 0x7F;
    }
}

/* 0x003F6CA0, 0x44 bytes. */
u8 func_003F6CA0(u32 side, u32 slot)
{
    if (side < 2 && slot < 6)
        return g_007BFEF0[side].formation[slot] & 0x7F;
    return 10;
}

/* 0x003F6CF0, 0x74 bytes. */
void func_003F6CF0(u32 side, u32 slot, int used)
{
    if (side < 2 && slot < 6) {
        if (used == 0)
            g_007BFEF0[side].formation[slot] &= 0x7F;
        else
            g_007BFEF0[side].formation[slot] |= 0x80;
    }
}

/* 0x003F6D70, 0x48 bytes. */
int func_003F6D70(u32 side, u32 slot)
{
    if (side < 2 && slot < 6)
        return (g_007BFEF0[side].formation[slot] & 0x80) != 0;
    return 0;
}

/* 0x003F6DC0, 0x28 bytes, matching. */
void func_003F6DC0(u32 side, u8 points)
{
    if (side < 2)
        g_007BFEF0[side].points = points;
}

/* 0x003F6DF0, 0x6C bytes. Adds to the points (kept within 0-180). */
void func_003F6DF0(u32 side, int add)
{
    if (side < 2) {
        int p = func_003F6E60(side) + add;
        int q = p;

        if (p < 1)
            q = 0;
        if (p > 0xB4)
            q = 0xB4;
        func_003F6DC0(side, q);
    }
}

/* 0x003F6E60, 0x30 bytes, matching. */
u8 func_003F6E60(u32 side)
{
    if (side < 2)
        return g_007BFEF0[side].points;
    return 0;
}

/* 0x003F6E90, 0x88 bytes. */
void func_003F6E90(u32 side, u32 flag, int on)
{
    if (side < 2 && flag < 3) {
        if (on == 0)
            g_007BFEF0[side].flags &= ~(u8)(1 << flag);
        else
            g_007BFEF0[side].flags |= (u8)(1 << flag);
    }
}

/* 0x003F6F20, 0x4C bytes. */
int func_003F6F20(u32 side, u32 flag)
{
    if (side < 2 && flag < 3)
        return ((1 << flag) & g_007BFEF0[side].flags) != 0;
    return 0;
}

/* 0x003F6F70, 0x4C bytes. Sets the counter (at most 300). */
void func_003F6F70(u32 side, u32 value)
{
    if (side < 2) {
        u32 v = value;
        u16 c;

        if (value == 0)
            v = 0;
        c = v;
        if (value > 300)
            c = 300;
        g_007BFEF0[side].counter = c;
    }
}

/* 0x003F6FC0, 0x30 bytes, matching. */
u16 func_003F6FC0(u32 side)
{
    if (side < 2)
        return g_007BFEF0[side].counter;
    return 0;
}

/* 0x003F6FF0, 0x40 bytes. */
void func_003F6FF0(u32 side)
{
    if (side < 2)
        func_003F6F70(side, func_003F6FC0(side) + 1);
}

/* 0x003F7030, 0x28 bytes, matching. Keeps the state in a save record. */
void func_003F7030(u8 *save)
{
    func_00118AC0(save + 0xAE8, g_007BFEF0, 0x20);
}

/* 0x003F7060, 0x30 bytes, matching. Takes it back from save slot 9. */
void func_003F7060(void)
{
    func_00118AC0(g_007BFEF0, func_002EFB00(9) + 0xAE8, 0x20);
}

/* 0x003F7090, 0x78 bytes. The advantage of formation `a` over formation `b`. */
int func_003F7090(u32 a, u32 b)
{
    Advantages table = *(Advantages *)g_0041DAE0;

    if (a < 10 && b < 10)
        return table.v[a * 10 + b];
    return 0;
}

/* 0x003F7110, 0xA0 bytes, matching. A formation's cost. */
int func_003F7110(u32 formation)
{
    PerFormation table = *(PerFormation *)g_0041DC70;

    if (formation < 10)
        return table.v[formation];
    return 0;
}

/* 0x003F71B0, 0x1C bytes, matching. */
int func_003F71B0(u32 formation)
{
    return func_003F7110(formation);
}

/* 0x003F71D0, 0xA0 bytes, matching. */
int func_003F71D0(u32 formation)
{
    PerFormation table = *(PerFormation *)g_0041DCA0;

    if (formation < 10)
        return table.v[formation];
    return 4;
}

/* 0x003F7270, 0xA0 bytes, matching. */
int func_003F7270(u32 formation)
{
    PerFormation table = *(PerFormation *)g_0041DCD0;

    if (formation < 10)
        return table.v[formation];
    return 4;
}

/* 0x003F7310, 0xCC bytes. A value for kinds 0x5A-0x62 and 0x65. The original indexes its 9-entry
 * copy with `kind - 0x5A`, so 0x65 reads past it (on the stack); kept as it is. */
int func_003F7310(int kind)
{
    PerKind table = *(PerKind *)g_0041DD00;
    int ok = 1;
    int in_range = 0;

    if (kind > 0x59 && kind < 99)
        in_range = 1;
    if (!in_range && kind != 0x65)
        ok = 0;
    if (ok)
        return table.v[kind - 0x5A];
    return 10;
}

/* 0x003F73E0, 0xA8 bytes. */
int func_003F73E0(int formation)
{
    PerFormation table = *(PerFormation *)g_0041DD30;

    if (formation < 0 || formation > 9)
        return 100;
    return table.v[formation];
}

/* 0x003F7490, 0x4C bytes, matching. Changes the slot in use (re-judging the advantage when `judge`) and
 * resets the counter. */
void func_003F7490(u32 side, u32 slot, int judge)
{
    func_003F6BA0(side, slot);
    if (judge != 0)
        func_003F7640();
    func_003F6F70(side, 0);
}

int func_003F7C00(u32 side);
u32 func_003F7A50(u32 side);
void func_003F7A00(u32 side);

/* 0x003F74E0, 0x108 bytes. Changes to slot `slot` when the points pay for it; the side with the
 * advantage then gets a bonus of 10 per point of it. */
void func_003F74E0(u32 side, u32 slot)
{
    u8 formation;

    if (side < 2 && slot < 6 && (formation = func_003F6CA0(side, slot)) < 10) {
        u32 cost = func_003F7110(formation);

        if (cost <= func_003F6E60(side)) {
            int adv;

            func_003F6DF0(side, -(int)cost);
            func_003F7490(side, slot, 1);
            adv = func_003F7C00(0);
            if (adv >= 1)
                func_0033BE80(0, 0, adv * 10);
            else if (adv < 0)
                func_0033BE80(1, 0, adv * -10);
            func_003F6E90(side, 1, 0);
        }
    }
}

/* 0x003F75F0, 0x44 bytes, matching. Changes to the last slot. */
void func_003F75F0(u32 side)
{
    func_003F7490(side, func_003F7A50(side) - 1, 1);
    func_003F6E90(side, 2, 0);
}

/* 0x003F7640, 0x108 bytes. Judges the advantage (flag 0 of the side that has it); a side with
 * fewer than 3 groups and a formation is warned. */
void func_003F7640(void)
{
    u32 side;
    int adv;

    for (side = 0; side < 2; side++)
        if (func_0033F7D0(side, 1) < 3 && func_003F6C10(side) != 0)
            func_003F7A00(side);
    adv = func_003F7090(func_003F6C10(0), func_003F6C10(1));
    if (adv >= 1) {
        func_003F6E90(0, 0, 1);
        func_003F6E90(1, 0, 0);
    } else if (adv < 0) {
        func_003F6E90(0, 0, 0);
        func_003F6E90(1, 0, 1);
    } else {
        func_003F6E90(0, 0, 0);
        func_003F6E90(1, 0, 0);
    }
    func_003AFD90();
}

/* 0x003F7750, 0x30 bytes, matching. Whether the side has the advantage. */
int func_003F7750(u32 side)
{
    if (side < 2)
        return func_003F6F20(side, 0);
    return 0;
}

/* 0x003F7780, 0x6C bytes. Whether `formation` is in use and has the advantage. */
int func_003F7780(u32 side, u32 formation)
{
    if (side < 2 && formation < 10 && formation == func_003F6C10(side))
        return func_003F7750(side) != 0;
    return 0;
}

/* 0x003F77F0, 0xA8 bytes. Whether slot `slot` can be chosen now (a formation, not used, and
 * the points for it). */
int func_003F77F0(u32 side, u32 slot)
{
    if (side < 2 && slot < 6) {
        u8 formation = func_003F6CA0(side, slot);

        if (formation < 10) {
            if (func_003F6D70(side, slot) == 0) {
                u8 points = func_003F6E60(side);

                return (u32)func_003F7110(formation) <= points;
            }
        }
    }
    return 0;
}

/* 0x003F78A0, 0x78 bytes. Whether slot `slot` holds a formation not used yet. */
int func_003F78A0(u32 side, u32 slot)
{
    if (side < 2 && slot < 6 && func_003F6CA0(side, slot) < 10)
        return func_003F6D70(side, slot) == 0;
    return 0;
}

/* 0x003F7920, 0x8C bytes. The first change of the battle (flag 1): announced
 * (func_0035D360), the slot marked used. */
void func_003F7920(u32 side, u32 slot, int a)
{
    if (func_003F6F20(side, 1) == 0) {
        func_0035D360(side, slot, a);
        func_003F6E90(side, 1, 1);
        if (func_003F6CA0(side, slot) != 0)
            func_003F6CF0(side, slot, 1);
    }
}

/* 0x003F79B0, 0x48 bytes, matching. A warning (flag 2), once. */
void func_003F79B0(u32 side)
{
    if (func_003F6F20(side, 2) == 0) {
        func_0035D3E0(side);
        func_003F6E90(side, 2, 1);
    }
}

/* 0x003F7A00, 0x48 bytes, matching. Another warning (flag 2), once. */
void func_003F7A00(u32 side)
{
    if (func_003F6F20(side, 2) == 0) {
        func_0035D410(side);
        func_003F6E90(side, 2, 1);
    }
}

/* 0x003F7A50, 0x84 bytes. How many slots hold a formation. */
u32 func_003F7A50(u32 side)
{
    int n = 0;
    u32 slot;

    if (side >= 2)
        return 0;
    for (slot = 0; slot < 6; slot++) {
        func_003F6CA0(side, slot);
        if (func_003F6CA0(side, slot) < 10)
            n++;
    }
    return n;
}

/* 0x003F7AE0, 0x90 bytes. How many lines page 10 shows: the formation in use and the others not
 * used yet. */
u8 func_003F7AE0(u32 side)
{
    int n = 0;
    u32 current, slot;

    if (side >= 2)
        return 0;
    current = func_003F6BE0(side);
    for (slot = 0; slot < 6; slot++)
        if (slot != current && func_003F78A0(side, slot) != 0)
            n++;
    return n + 1;
}

/* 0x003F7B70, 0x8C bytes. How many slots hold an unused formation other than 0. */
int func_003F7B70(u32 side)
{
    int n = 0;
    u32 slot;

    if (side >= 2)
        return 0;
    for (slot = 0; slot < 6; slot++)
        if (func_003F78A0(side, slot) != 0 && func_003F6CA0(side, slot) != 0)
            n++;
    return n;
}

/* 0x003F7C00, 0x60 bytes. The side's advantage over the other side. */
int func_003F7C00(u32 side)
{
    if (side < 2) {
        u8 mine = func_003F6C10(side);

        return func_003F7090(mine, func_003F6C10(func_0035D5A0(side)));
    }
    return 0;
}

/* 0x003F7C60, 0x8C bytes. When a count passes a multiple of 50 (from `before` to `now`), the
 * player gets 30 points, and 150 more at each multiple of 1000. */
void func_003F7C60(u32 now, u32 before)
{
    u32 step = (before + 0x32) / 0x32 * 0x32;

    if (before < step && step <= now) {
        func_003F6DF0(0, 0x1E);
        if ((int)step % 1000 == 0)
            func_003F6DF0(0, 0x96);
    }
}

/* 0x003F7CF0, 0x8 bytes, matching. */
void func_003F7CF0(void)
{
}

/* 0x003F7D00, 0x1C bytes, matching. */
void func_003F7D00(void)
{
    func_003F7640();
}

/* 0x003F7D20, 0x1C bytes, matching. */
void func_003F7D20(void)
{
    func_003F7640();
}

/* 0x003F7D40, 0xB4 bytes, matching. Resets both sides: slot 0, no formations, no points. */
void func_003F7D40(void)
{
    u32 side, slot;

    func_00118850(g_007BFEF0, 0x20);
    for (side = 0; side < 2; side++) {
        func_003F6BA0(side, 0);
        for (slot = 0; slot < 6; slot++) {
            func_003F6C40(side, slot, 10);
            func_003F6CF0(side, slot, 0);
        }
        func_003F6DC0(side, 0);
        func_003F6F70(side, 0);
        g_007BFEF0[side].flags = 0;
    }
}

/* 0x003F7E00, 0x1C bytes, matching. */
void func_003F7E00(void)
{
    func_003F7060();
}

/* 0x003F7E20, 0x40 bytes, matching. At a battle's set-up: an Empire battle takes the saved state back, a
 * free battle starts afresh. */
void func_003F7E20(void)
{
    if (g_00669D60.g_00669F6C == 1)
        func_003F7E00();
    else
        func_003F7D40();
}

/* 0x003F7E60, 0x19C bytes. A random slot of side `side` (its cost within func_00362CE0) whose
 * formation is worse (mood 2), equal (1) or better (0) than `against`; formation 0 only when it
 * comes first. 6 when none. */
u32 func_003F7E60(u32 side, u32 against, int mood)
{
    u32 slots[8];
    u32 budget = func_00362CE0();
    int n = 0;
    u32 slot;

    for (slot = 0; slot < 6; slot++) {
        u32 f = func_00362C10(side, slot);

        if (f < 10 && (u32)func_003F71B0(f) <= budget) {
            int ok = 0;

            if (mood == 2)
                ok = func_003F7090(f, against) < 0;
            else if (mood == 1)
                ok = func_003F7090(f, against) == 0;
            else if (mood == 0)
                ok = func_003F7090(f, against) > 0;
            if (ok && (f != 0 || n == 0))
                slots[n++] = slot;
        }
    }
    if (n == 0)
        return 6;
    return slots[n == 0 ? 0 : (int)RANDOM() % n];
}

/* 0x003F8000, 0xF4 bytes. The enemy's first formation against the player's: 30% worse (else
 * equal), 50% equal, 20% better. */
void func_003F8000(void)
{
    u32 player = func_00362C10(0, func_00362C80(0));
    u32 mood = RANDOM() % 100;
    u32 slot;

    if (mood < 0x1E) {
        slot = func_003F7E60(1, player, 2);
        if (slot > 5)
            slot = func_003F7E60(1, player, 1);
    } else if (mood < 0x50) {
        slot = func_003F7E60(1, player, 1);
    } else {
        slot = func_003F7E60(1, player, 0);
    }
    if (slot < 6)
        func_00362C50(1, slot);
}

/* 0x003F8100, 0xD0 bytes. When the battle starts: each side takes its slot (the last one with
 * fewer than 3 groups) and pays for it. */
void func_003F8100(void)
{
    u32 side;

    func_003F8000();
    for (side = 0; side < 2; side++) {
        int slot = func_00362C80(side);
        u8 formation;

        if (func_0033F7D0(side, 1) < 3)
            slot = func_003F7A50(side) - 1;
        func_003F7490(side, slot, 0);
        formation = func_003F6C10(side);
        func_003F6DF0(side, -func_003F71B0(formation));
        if (formation != 0)
            func_003F6CF0(side, slot, 1);
    }
    func_003F7640();
    func_0035D3A0();
}

/* 0x003F81D0, 0x84 bytes. After an Empire battle: the formations the player used
 * (func_00328780 / func_003286E0). */
void func_003F81D0(void)
{
    u32 slot;

    if (func_0036D2E0() == 0)
        return;
    for (slot = 0; slot < 6; slot++) {
        u8 f = func_003F6CA0(0, slot);

        if (f < 10 && func_003F6D70(0, slot) != 0)
            func_003286E0(func_00328780(f));
    }
}

/* 0x003F8260, 0x108 bytes. A free battle's set-up: without an Empire game and with fewer than 2
 * player formations, the enemy only has formation 0; then both sides' slots from the battle's
 * settings, with no points. */
void func_003F8260(void)
{
    u32 side, slot;

    if (g_00669D60.g_00669F6C == 1 || func_0032E7B0() != 0)
        return;
    if (func_0036D2E0() == 0 && func_00362D70(0) < 2) {
        func_00362BD0(1, 0, 0);
        for (slot = 1; slot < 6; slot++)
            func_00362BD0(1, slot, 10);
        func_00362C50(1, 0);
    }
    for (side = 0; side < 2; side++) {
        for (slot = 0; slot < 6; slot++) {
            u32 f = func_00362C10(side, slot);

            if (f < 10)
                func_003F6C40(side, slot, f);
        }
        func_003F6DC0(side, 0);
    }
}

/* 0x003F8370, 0x58 bytes, matching. Every 100 frames, a point for each side. */
void func_003F8370(void)
{
    u32 side;

    if (g_00669D60.g_00669F9C % 100 == 0)
        for (side = 0; side < 2; side++)
            func_003F6DF0(side, 1);
}

/* 0x003F83D0, 0xA8 bytes. Every 50 frames, the counter of a side that has not changed yet; at
 * 300 with a formation, a warning. */
void func_003F83D0(void)
{
    u32 side;

    if (g_00669D60.g_00669F9C % 0x32 == 0) {
        for (side = 0; side < 2; side++) {
            if (func_003F6FC0(side) < 300 && func_003F6F20(side, 1) == 0) {
                func_003F6FF0(side);
                if (func_003F6C10(side) != 0 && func_003F6FC0(side) > 299)
                    func_003F79B0(side);
            }
        }
    }
}

/* 0x003F8480, 0x24 bytes, matching. Each frame of a battle. */
void func_003F8480(void)
{
    func_003F8370();
    func_003F83D0();
}
