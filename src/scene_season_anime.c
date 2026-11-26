/*
 * scene_season_anime.c - scene 0x16 (original source file SeasonAnime.c, probable: the scene's
 * functions sit right after that file's string references).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The season animation between Empire-mode turns: the scene only opens the conquest map's data
 * (StateConquest.c helpers 0x002F1950...) and the animation player (0x003C0070...), and lets the
 * player run.
 */

typedef unsigned int u32;

void func_002F1950(void);
void func_002F19E0(void);
u32 func_003C0070(void);
void func_003C0080(u32 a);
void func_0030CE90(int value);
void func_002C59F0(void);
void func_002C5A30(void);
void func_002C5A60(void);
void func_003EA010(void);
void func_001B8F60(int a, int b, int c);
void func_002F1A20(void);
void func_002F19B0(void);
void func_003C0610(void);
void func_002F1A50(void);
void func_003C05D0(void);

/* 0x003DAB30, 0x24 bytes, matching. Scene 0x16 draw. */
void func_003DAB30(void)
{
    func_002F1A50();
    func_003C05D0();
}

/* 0x003DAB60, 0x8 bytes, matching. Scene 0x16 step: empty. */
void func_003DAB60(void)
{
}

/* 0x003DAB70, 0x20 bytes, matching. Scene 0x16 update: runs the animation. */
int func_003DAB70(void)
{
    func_003C0610();
    return 1;
}

/* 0x003DAB90, 0x24 bytes, matching. Scene 0x16 leave. */
void func_003DAB90(void)
{
    func_002F1A20();
    func_002F19B0();
}

/* 0x003DABC0, 0x6C bytes, matching. Scene 0x16 enter: opens the map and the animation, then fades in. */
void func_003DABC0(void)
{
    func_002F1950();
    func_002F19E0();
    func_003C0080(func_003C0070());
    func_0030CE90(10);
    func_002C59F0();
    func_002C5A30();
    func_002C5A60();
    func_003EA010();
    func_001B8F60(1, 6, 8);
}
