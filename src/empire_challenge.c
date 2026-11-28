/*
 * empire_challenge.c - an Empire event: a battle against a chosen officer (a challenge?).
 * Original source file unknown; 0x003F84B0-0x003F8B2C, between the formations
 * (battle_formation.c) and BgManager.c. The event's state is the object func_003EA000 returns
 * (+0 the step, +8 the player's officer).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The opponent is one of the officers with the highest value of func_002F34E0 (its level?)
 * among those that serve an entry of func_002FB2A0 and are free (func_002F3DC0 0), drawn at
 * random. The battle is set up on stage 0x20E; afterwards the player gets half of
 * func_00331010 (a tenth of it as gold?) unless func_0036B260, and the opponent goes back
 * free.
 */

#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_002F3CF0   /* the original callers here see it this way */
void func_002F3CF0(int officer, int a);
#endif
#ifndef SW2E_PC
#define SW2E_OWN_PROTO_func_002F8E50   /* the original callers here see it this way */
int func_002F8E50(int entry);
#endif
#define SW2E_FILE_EMPIRE_CHALLENGE_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned int u32;

#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) the random seed */
#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10 & 0xFFFF)

extern char g_007B4E60[];                 /* a text buffer */

void func_001204B0(char *to, const char *from, ...);

/* 0x003F84B0, 0x284 bytes. The opponent: one of the officers with the highest func_002F34E0,
 * other than the player's ruler (func_00327820), drawn at random (0 when none). */
int func_003F84B0(void)
{
    int values[0x1A0], officers[0x1A0];
    int ruler = func_00327820();
    int n = 0, i, o;

    for (i = 0; i < 0x19F; i++) {
        officers[i] = 0x19F;
        values[i] = -1;
    }
    for (o = 0; o < 0x19F; o++) {
        int ok = 0, entry, game;

        if (o >= 0 && o < 0x19F)
            ok = 1;
        if (!ok || func_002F2840(o) == 0 || o == ruler)
            continue;
        entry = func_002F5CC0(o);
        if (!(entry >= 0 && entry < func_0030AB90()))
            continue;
        game = func_0030AFF0(entry);
        if (!(game >= 0 && game < func_0030AB90()))
            continue;
        if (func_002FB2A0(game) != 0 && func_002F3DC0(o) == 0) {
            int v = func_002F34E0(o);

            for (i = 0; i < 0x19F; i++) {           /* keeps the officers of the best value */
                if (v < values[i])
                    break;
                if (v != values[i]) {
                    n = i + 1;
                    values[i] = v;
                    officers[i] = o;
                    break;
                }
            }
        }
    }
    if (n == 1)
        return officers[0];
    if (n == 0)
        return 0;
    return officers[n == 0 ? 0 : (int)RANDOM() % n];
}

/* 0x003F8740, 0x100 bytes, matching. Sets the battle up: the player's officer against the opponent (put
 * in a free entry with a random value), on stage 0x20E. */
void func_003F8740(u8 *event)
{
    int entry = func_00327D50();
    int *state = func_003EA000();
    int opponent = func_003F84B0();
    int place;

    func_0030CF90(0, 0, state[2]);
    func_0030CF90(1, 0, opponent);
    place = func_002FB8B0();
    func_002F3CF0(opponent, 3);
    func_002F3F70(opponent, place);
    func_002F8E80(place, opponent);
    func_002F69F0(opponent, RANDOM() % 10);
    func_00362990(0, func_002F8E50(entry));
    func_00362990(1, 0x20E);
    func_003EAA50(PS2_ADDR(event + 0x10));
}

/* 0x003F8840, 0x54 bytes, matching. The player's entry gets a tenth of func_00331010. */
int func_003F8840(void)
{
    int entry = func_00327D50();

    func_002F9130(entry, func_00331010() / 10);
    return 0;
}

/* 0x003F88A0, 0x24 bytes. Step 0. */
void func_003F88A0(void)
{
    *func_003EA000() = 1;
}

/* 0x003F88D0, 0x104 bytes. Step 1: the reward (message 0x11E, half of func_00331010, a tenth of
 * it to the entry) or message 0x11D when func_0036B260 holds. */
void func_003F88D0(void)
{
    int *state = func_003EA000();
    int value = func_00331010() / 2;

    if (func_0030E1F0() == 2)
        func_0030E100();
    if (func_0036B260() == 0) {
        func_001204B0(g_007B4E60, (const char *)(func_00390760(0x11E)), func_0030CB80(value));
        func_002F9130(func_00327D50(), value / 10);
    } else {
        func_001204B0(g_007B4E60, (const char *)(func_00390760(0x11D)));
    }
    func_00374EE0(PS2_ADDR(g_007B4E60));
    *state = 2;
}

/* 0x003F89E0, 0x64 bytes, matching. The opponent goes back free. */
void func_003F89E0(void)
{
    int opponent = func_003620E0(1, 0);
    int entry = func_002F4080(opponent);

    func_002F3CF0(opponent, 0);
    func_002F3F70(opponent, 0x19);
    func_002F8E80(entry, 0x19F);
}

/* 0x003F8A50, 0x54 bytes, matching. Step 2: once the message is closed. */
void func_003F8A50(void)
{
    int *state = func_003EA000();

    if (func_00375BF0() != 0 && func_00375B90() == 1) {
        func_003F89E0();
        *state = 3;
    }
}

/* 0x003F8AB0, 0x80 bytes. The event's update after the battle (steps 0-3). */
int func_003F8AB0(void)
{
    int *state = func_003EA000();
    int step = *state;

    if (step != 3) {
        if (step == 2)
            func_003F8A50();
        else if (step == 1)
            func_003F88D0();
        else if (step == 0)
            func_003F88A0();
    }
    return 5;
}
