/*
 * battle_mission.c - the missions given during a free battle (original source file unknown; the
 * module sits between SceneTutorial.c and the next module, 0x003F5550-0x003F6BA0).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * At the start of a free battle (func_003F6630), one time in four (and when nothing prevents it)
 * a mission is offered: a soldier group of the battle is chosen by a score (func_003F5F00),
 * then one of eight kinds whose condition holds (func_003F6390), with a time limit of 5-7
 * minutes (3000 frames a minute: PAL) and, for some kinds, a target value. During the battle,
 * func_003F6A90 checks the kind's goal and ends the mission as won or lost (func_0035D300). The
 * mission is shown on page 15 of the battle menu (battle_menu_draw.c); an Empire battle keeps
 * it in the save (func_003F5770 / func_003F57A0).
 */

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_002EFB00   /* the original callers here see it this way */
unsigned char *func_002EFB00(int);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_0033B7B0   /* the original callers here see it this way */
unsigned int func_0033B7B0(unsigned char **);
#endif
#define SW2E_FILE_BATTLE_MISSION_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The mission (small data, 0x0045D868, 8 bytes, copied as a block). */
extern struct {
    u8 group;                /* the soldier group (0x47 = none) */
    u8 kind;                 /* 0-7 (8 = none) */
    u8 minutes;              /* the time limit */
    u8 target;               /* the kind's value */
    u8 status;               /* 0 offered, 1 running, 2 over, 5 none */
    u8 unknown_5[3];
} g_0045D868;

extern u8 g_006A1D58[][0x68];             /* the soldier groups (see scene_battle_initialize.c) */
#define GROUP(i) ((u8 **)g_006A1D58[i])
#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)

/* The game state (0x00669D60), the fields used here. */
extern struct {
    u8 unknown_0[0x21];
    u8 g_00669D81;           /* the difficulty (0-4) */
    u8 unknown_22[0x6A];
    u32 g_00669DEC;
    u8 unknown_90[0x17C];
    int g_00669F6C;          /* 1: an Empire battle */
    u8 unknown_210[0x2C];
    u32 g_00669F9C;          /* the battle's time (frames) */
} g_00669D60;

#define g_7000015C (*(u32 *)0x7000015C)   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

extern char g_007BFDF0[];                 /* the mission's text */
extern const char g_0045CAC8[];           /* an empty text */
extern int g_0041DA80[5];                 /* per difficulty: a score bonus (-35 ... -15) */
extern int (*g_0041DAA0[8])(int group);   /* per kind: whether it can be offered */
extern int (*g_0041DAC0[8])(void);        /* per kind: whether its goal is reached */

void func_00120928(char *to, const char *from);
int func_002F7D90(int a, int (*filter)(), int value, int b, int c, int d);
int func_0033F240(int *out, int most, int (*filter)(u8 **group), int a, int b, int c, int d);

/* 0x003F5550, 0x8 bytes, matching. */
void func_003F5550(u8 group)
{
    g_0045D868.group = group;
}

/* 0x003F5560, 0x8 bytes, matching. */
u32 func_003F5560(void)
{
    return g_0045D868.group;
}

/* 0x003F5570, 0x58 bytes. The mission's group (0 = none). */
u8 **func_003F5570(void)
{
    u8 group = func_003F5560();

    if (group < 0x47)
        return GROUP(group);
    return 0;
}

/* 0x003F55D0, 0x10 bytes, matching. */
void func_003F55D0(u8 kind, u8 minutes, u8 target)
{
    g_0045D868.kind = kind;
    g_0045D868.minutes = minutes;
    g_0045D868.target = target;
}

u32 func_003F55E0(void) { return g_0045D868.kind; }       /* 0x003F55E0, 0x8 bytes, matching. */
u32 func_003F55F0(void) { return g_0045D868.minutes; }    /* 0x003F55F0, 0x8 bytes, matching. */
u32 func_003F5600(void) { return g_0045D868.target; }     /* 0x003F5600, 0x8 bytes, matching. */

/* 0x003F5610, 0x8 bytes, matching. */
void func_003F5610(u32 status)
{
    g_0045D868.status = status;
}

/* 0x003F5620, 0x8 bytes, matching. */
u32 func_003F5620(void)
{
    return g_0045D868.status;
}

/* 0x003F5630, 0x20 bytes, matching. Whether there is a mission. */
int func_003F5630(void)
{
    return func_003F5560() < 0x47;
}

/* 0x003F5650, 0x40 bytes. Whether it is running or over. */
int func_003F5650(void)
{
    u8 status = func_003F5620();

    if (status == 2 || status == 1)
        return 1;
    return 0;
}

/* 0x003F5690, 0xD0 bytes. Builds the mission's text (message 0x96 + kind, with the target or
 * the group). */
void func_003F5690(void)
{
    func_00120928(g_007BFDF0, g_0045CAC8);
    if (func_003F5630() != 0) {
        int colour = 6, value = 0;
        u8 kind = func_003F55E0();

        if (kind < 8) {
            switch (kind) {
            case 0:
            case 1:
            case 3:
            case 4:
                colour = 5;
                value = func_003F5600();
                break;
            case 5:
            case 6:
                colour = 1;
                value = func_003F5560();
                break;
            }
            func_003576C0(g_007BFDF0, kind + 0x96, colour, value, 6, 0);
        }
    }
}

/* 0x003F5760, 0xC bytes, matching. */
char *func_003F5760(void)
{
    return g_007BFDF0;
}

/* 0x003F5770, 0x24 bytes, matching. Keeps the mission in a save record. */
void func_003F5770(u8 *save)
{
    func_00118AC0((unsigned int *)(save + 0xAE0), (unsigned char *)(&g_0045D868), 8);
}

/* 0x003F57A0, 0x2C bytes, matching. Takes it back from save slot 9. */
void func_003F57A0(void)
{
    func_00118AC0((unsigned int *)(&g_0045D868), (unsigned char *)PS2_PTR(func_002EFB00(9) + 0xAE0), 8);
}

/* 0x003F57D0, 0x24 bytes, matching. No mission. */
void func_003F57D0(void)
{
    g_0045D868.minutes = 0;
    g_0045D868.group = 0x47;
    g_0045D868.target = 0;
    g_0045D868.kind = 8;
    g_0045D868.status = 5;
}

/* 0x003F5800, 0x9C bytes. Whether two officers are linked (in an Empire game: func_002F78C0
 * or func_0036D850). */
int func_003F5800(int officer, int other)
{
    if (func_0036D2E0() == 0)
        return 0;
    if (officer < 0 || officer > 0x19E || other < 0 || other > 0x19E)
        return 0;
    if (func_002F78C0(officer, other) != 0)
        return 1;
    return func_0036D850(officer, other) != 0;
}

/* 0x003F58A0, 0xD0 bytes. Whether the leaders of two groups are linked. */
int func_003F58A0(u8 **group, u8 **other)
{
    u16 a, b;

    if (group == 0 || other == 0)
        return 0;
    if (func_0033B050(group) == 0 || func_0033B050(other) == 0)
        return 0;
    b = *((u16 *)func_00338410(GROUP_INDEX(other)));
    a = *((u16 *)func_00338410(GROUP_INDEX(group)));
    return func_003F5800(a, b);
}

/* 0x003F5970, 0xA8 bytes. Whether `group` is linked to an active group of side `side`. */
int func_003F5970(u8 **group, u32 side)
{
    u32 i;

    if (group != 0 && side < 2) {
        for (i = 0; i < 0x10; i++) {
            u8 **g = func_0033EF80(i);

            if ((((int *)g)[0x19] & 1) != 0 && side == (*g)[0x79] && func_003F58A0(group, g) != 0)
                return 1;
        }
    }
    return 0;
}

/* 0x003F5A20, 0x2C0 bytes. Whether `group` can be given a mission: active, a plain unit, not
 * busy (func_0033B140 / func_0033B690 / func_0033B440 / func_0033B4E0), its leader not linked to
 * the other side's leaders, nor in an Empire game to the officers of its entry; and while the
 * player's side has 8 groups or more, only an enemy group. */
int func_003F5A20(u8 **group)
{
    if (group == 0)
        return 0;
    if ((((int *)group)[0x19] & 1) == 0)
        return 0;
    if ((*(u32 *)(*group + 0x80) & 0x30) != 0)
        return 0;
    if (func_0033B140(group) != 0 || func_0033B690(group) != 0)
        return 0;
    {
        u8 kind = (*group)[0x79];
        u8 other = func_0035D5A0(kind);

        if (func_003F5970(group, other) == 0) {
            int leader;

            if (func_003F58A0(group, func_0033F110(other)) != 0)
                return 0;
            leader = func_0036D550(kind);
            if (leader >= 0 && leader < 0x19F &&
                func_003F5800(*((u16 *)func_00338410(GROUP_INDEX(group))), leader) != 0)
                return 0;
        }
    }
    if (func_0033B440(group) != 0 || func_0033B4E0(group) != 0)
        return 0;
    if (func_0036D2E0() != 0) {
        u32 *officers = func_002F7B10();
        u32 leader = *((u16 *)func_00338410(GROUP_INDEX(group)));
        int entry = func_002F4080(leader);

        if (entry >= 0 && entry < 0x19) {
            int n = func_002F7D90(0, func_002F8160, entry, 0, 1, 0);
            int i;

            for (i = 0; i < n; i++) {
                u32 o = *officers;

                if (o != leader && (func_002F77A0(o, leader) != 0 || func_002F78C0(o, leader) != 0 ||
                                    func_002F7900(o, leader) != 0))
                    return 0;
                officers++;
            }
        }
    }
    if (func_0033F7D0(1, 0) < 8 || (*group)[0x79] != 0)
        return 1;
    return 0;
}

/* 0x003F5CE0, 0x6C bytes. Whether the group's leader is one of three officers (0xB5, 0xFF,
 * 0x16E). */
int func_003F5CE0(u8 **group)
{
    u16 leader = *((u16 *)func_00338410(GROUP_INDEX(group)));

    return leader == 0xFF || leader == 0xB5 || leader == 0x16E;
}

/* 0x003F5D50, 0x1C bytes, matching. */
int func_003F5D50(u8 **group)
{
    return func_003F5A20(group);
}

/* 0x003F5D70, 0x30 bytes, matching. The groups that can be given a mission. */
int func_003F5D70(int *out, int most)
{
    return func_0033F240(out, most, func_003F5D50, 0, 0, 0, 0x10);
}

/* 0x003F5DA0, 0x20 bytes, matching. */
int func_003F5DA0(void)
{
    int groups[16];

    return func_003F5D70(groups, 0x10);
}

/* 0x003F5DC0, 0x138 bytes. Whether a mission is offered: one time in four, both sides with 8
 * groups or more, not in battle types 6-0x12, and a group that can take it. */
int func_003F5DC0(void)
{
    u32 side, type;

    if (func_0036D300() != 0 || func_0032E7B0() != 0)
        return 0;
    if (RANDOM() % 100 >= 0x19)
        return 0;
    for (side = 0; side < 2; side++) {
        func_00362930(side);
        if (func_00362930(side) < 8)
            return 0;
    }
    if (func_003636F0(1) != 0)
        return 0;
    type = func_00362570();
    if ((type >= 0x10 && type <= 0x12) || (type >= 6 && type <= 0x0F))
        return 0;
    return func_003F5DA0() != 0;
}

/* 0x003F5F00, 0x29C bytes. Chooses the mission's group: the best of a random score (0-49),
 * +25 when linked to the other side's leader, +20 to its main officer, +30 for three officers,
 * and for the player's groups -20 / +20 (func_0036D700 / func_0036D740) and the difficulty's
 * bonus; kept within 0-255. */
void func_003F5F00(void)
{
    int bonus[5];
    int groups[16];
    int i, n, best = -1;
    u8 **chosen = 0;

    for (i = 0; i < 5; i++)
        bonus[i] = g_0041DA80[i];
    n = func_003F5D70(groups, 0x10);
    for (i = 0; i < n; i++) {
        int index = groups[i];
        int score = RANDOM() % 0x32;
        u8 **group = GROUP(index);
        u8 kind = (*group)[0x79];
        u8 other = func_0035D5A0(kind);
        int leader;

        if (func_003F58A0(group, func_0033F110(other)) != 0)
            score += 0x19;
        leader = func_0036D550(other);
        if (leader >= 0 && leader < 0x19F && func_003F5800(*((u16 *)func_00338410(index)), leader) != 0)
            score += 0x14;
        if (func_003F5CE0(group) != 0)
            score += 0x1E;
        if (kind == 0) {
            if (func_0036D700() != 0)
                score -= 0x14;
            if (func_0036D740() != 0)
                score += 0x14;
            score += bonus[g_00669D60.g_00669D81];
        }
        if (score < 1)
            score = 0;
        if (score > 0xFF)
            score = 0xFF;
        if (best < score) {
            best = score;
            chosen = group;
        }
    }
    if (chosen != 0)
        func_003F5550(GROUP_INDEX(chosen));
}

/* The kinds' conditions (table 0x0041DAA0). */

/* 0x003F61A0, 0x34 bytes. Kind 0: func_003519E0 at least 5 above func_003531F0. */
int func_003F61A0(int group)
{
    u32 a = func_003531F0(0);

    return a + 5 <= func_003519E0();
}

/* 0x003F61E0, 0x28 bytes, matching. Kind 1: more than 5 enemy groups? */
int func_003F61E0(int group)
{
    return func_0033F7D0(1, 1) > 5;
}

/* 0x003F6210, 0x40 bytes. Kind 2: side 1 at least 1.5 times side 0 (func_0035F2D0). */
int func_003F6210(int group)
{
    u32 a = func_0035F2D0(0);

    return (a * 3) >> 1 <= func_0035F2D0(1);
}

/* 0x003F6250, 0x8 bytes, matching. Kind 3: always. */
int func_003F6250(int group)
{
    return 1;
}

/* 0x003F6260, 0x8 bytes, matching. Kind 4: always. */
int func_003F6260(int group)
{
    return 1;
}

/* 0x003F6270, 0x60 bytes. Kind 5: a player's group for which func_0033BA60 holds. */
int func_003F6270(int group)
{
    if ((*GROUP(group))[0x79] == 0)
        return func_0033BA60(GROUP(group)) != 0;
    return 0;
}

/* 0x003F62D0, 0x3C bytes. Kind 6: an enemy group. */
int func_003F62D0(int group)
{
    return (*GROUP(group))[0x79] == 1;
}

/* 0x003F6310, 0x74 bytes. Kind 7: an enemy group, while side 0's main group has flag
 * 0x80000. */
int func_003F6310(int group)
{
    if ((*GROUP(group))[0x79] == 1)
        return (*(u32 *)(*func_0035DD10(0) + 0x80) & 0x80000) != 0;
    return 0;
}

/* 0x003F6390, 0x214 bytes. Chooses the mission's kind among those whose condition holds, its
 * time (5-7 minutes) and its target. */
void func_003F6390(void)
{
    int (*conditions[8])(int group);
    u32 kinds[8];
    u8 **group;
    int n = 0, target = 0;
    u32 i, kind, minutes;

    for (i = 0; i < 8; i++)
        conditions[i] = g_0041DAA0[i];
    group = func_003F5570();
    if (group == 0)
        return;
    for (i = 0; i < 8; i++)
        if (conditions[i](GROUP_INDEX(group)) != 0)
            kinds[n++] = i;
    if (n == 0)
        return;
    kind = kinds[n == 0 ? 0 : (int)RANDOM() % n];
    minutes = RANDOM();
    switch (kind) {
    case 0:
        target = func_003531F0(0) + 2;
        break;
    case 1:
        target = func_0033F7D0(1, 1) - 2;
        if (target < 1)
            target = 0;
        break;
    case 3:
        target = 100;
        break;
    case 4:
        target = 100;
        break;
    }
    func_003F55D0(kind, minutes % 3 + 5, target);
}

/* 0x003F65B0, 0x1C bytes, matching. */
void func_003F65B0(void)
{
    func_003F57D0();
}

/* 0x003F65D0, 0x1C bytes, matching. */
void func_003F65D0(void)
{
    func_003F57A0();
}

/* 0x003F65F0, 0x40 bytes. At a battle's set-up: an Empire battle takes the saved mission back,
 * a free battle starts with none. */
void func_003F65F0(void)
{
    if (g_00669D60.g_00669F6C == 1)
        func_003F65D0();
    else
        func_003F65B0();
}

/* 0x003F6630, 0x78 bytes, matching. When a free battle starts: maybe offers a mission (func_0035D2D0
 * announces it), then builds its text. */
void func_003F6630(void)
{
    if (g_00669D60.g_00669F6C != 1 && func_003F5DC0() != 0) {
        func_003F5F00();
        func_003F6390();
        func_003F5610(0);
        func_0035D2D0(func_003F5560());
    }
    if (func_003F5630() != 0)
        func_003F5690();
}

/* 0x003F66B0, 0x8 bytes, matching. */
void func_003F66B0(void)
{
}

/* The kinds' goals (table 0x0041DAC0). */

/* 0x003F66C0, 0x34 bytes, matching. Kind 0: func_003531F0 reached the target. */
int func_003F66C0(void)
{
    u32 a = func_003531F0(0);

    return func_003F5600() <= a;
}

/* 0x003F6700, 0x38 bytes, matching. Kind 1: the enemy groups down to the target. */
int func_003F6700(void)
{
    u32 a = func_0033F7D0(1, 1);

    return a <= func_003F5600();
}

/* 0x003F6740, 0x34 bytes, matching. Kind 2: side 0 above side 1. */
int func_003F6740(void)
{
    u32 a = func_0035F2D0(0);

    return func_0035F2D0(1) < a;
}

/* 0x003F6780, 0x30 bytes, matching. Kind 3: g_00669DEC reached the target. */
int func_003F6780(void)
{
    u32 a = g_00669D60.g_00669DEC;

    return func_003F5600() <= a;
}

/* 0x003F67B0, 0x34 bytes, matching. Kind 4: func_001D22D0 reached the target. */
int func_003F67B0(void)
{
    u32 a = func_001D22D0(0);

    return func_003F5600() <= a;
}

/* 0x003F67F0, 0x98 bytes. Kind 5: the group is the target of one of func_003E2D90's units 1-3. */
int func_003F67F0(void)
{
    u32 i;

    if (func_003E2D90(0, 0) != 0) {
        for (i = 1; i < 4; i++) {
            u8 **unit = (u8 **)PS2_PTR(func_003E2D90(0, i));

            if (unit != 0) {
                u8 **target = func_0033F1A0((unsigned char *)(unit));

                if (target != 0 && target == func_003F5570())
                    return 1;
            }
        }
    }
    return 0;
}

/* 0x003F6890, 0x28 bytes, matching. Kind 6: the group below 50 (func_0033B7B0). */
int func_003F6890(void)
{
    return func_0033B7B0(func_003F5570()) < 0x32;
}

/* 0x003F68C0, 0x44 bytes, matching. Kind 7: sends side 0's main group to side 1's target (the original
 * returns what func_0033CB60 leaves in v0). */
int func_003F68C0(void)
{
    u8 **group = func_0035DD10(0);

    return func_0033CB60(group, func_0034EC80(func_0035F200(1)));
}

/* 0x003F6910, 0x8C bytes. Whether the mission's goal is reached. */
int func_003F6910(void)
{
    int (*goals[8])(void);
    int i;

    for (i = 0; i < 8; i++)
        goals[i] = g_0041DAC0[i];
    return goals[func_003F55E0()]();
}

/* 0x003F69A0, 0x30 bytes, matching. The mission is won. */
void func_003F69A0(void)
{
    func_0035D300(func_003F5560(), 1);
    func_003F5610(2);
}

/* 0x003F69D0, 0x30 bytes, matching. The mission is lost. */
void func_003F69D0(void)
{
    func_0035D300(func_003F5560(), 0);
    func_003F5610(2);
}

/* 0x003F6A00, 0x84 bytes. At each of the last three minutes, a reminder (func_0035D330). */
void func_003F6A00(void)
{
    int left = func_003F55F0() * 3000 - (int)g_00669D60.g_00669F9C;

    if (left >= 0 && left % 3000 == 0 && left / 3000 > 0 && left / 3000 < 4)
        func_0035D330(left / 3000);
}

/* 0x003F6A90, 0x110 bytes. While the mission runs: while the group is active and the time
 * lasts, won once its goal is reached; lost when the time is over; when the group is gone, won
 * for a player's group (?) and lost for an enemy one. */
void func_003F6A90(void)
{
    if (func_003F5620() == 1) {
        u8 **group = func_003F5570();
        u32 flags = *(u32 *)(*group + 0x80);
        int active = 0, alive = 0;

        if ((flags & 1) != 0 && (flags & 0x8C40002) == 0)
            active = 1;
        if (active && (flags & 4) == 0)
            alive = 1;
        if (alive) {
            if (g_00669D60.g_00669F9C < (u32)(func_003F55F0() * 3000)) {
                func_003F6A00();
                if (func_003F6910() != 0)
                    func_003F69A0();
            } else {
                func_003F69D0();
            }
        } else if ((*group)[0x79] == 0) {
            func_003F69A0();
        } else {
            func_003F69D0();
        }
    }
}
