/*
 * scene_empty.c - scenes 0x0B and 0x03 (original source file unknown: they follow scene 0x08's
 * functions at 0x00235A70).
 *
 * Decompiled by reading the original machine code (checked against the disassembly; Ghidra did
 * not find these functions, which are only reached through the scene table at 0x00422000).
 *
 * Scene 0x0B leaves as soon as it is entered (to the requested scene, else back, else scene 1).
 * Scene 0x03 does nothing at all. Both may be left-overs of removed scenes.
 */

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

/* ---- Scene 0x0B ------------------------------------------------------------------------------- */

/* 0x00236C50, 0xB0 bytes. Scene 0x0B enter: leaves at once (as LEAVE_SCENE in
 * scene_initialize.c, fallback scene 1). */
void func_00236C50(void)
{
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
}

/* 0x00236D00, 0x8 bytes, matching. Scene 0x0B leave: empty. */
void func_00236D00(void)
{
}

/* 0x00236D10, 0x8 bytes, matching. Scene 0x0B update. */
int func_00236D10(void)
{
    return 1;
}

/* 0x00236D20, 0x8 bytes, matching. Scene 0x0B step: empty. */
void func_00236D20(void)
{
}

/* 0x00236D30, 0x8 bytes, matching. Scene 0x0B draw: empty. */
void func_00236D30(void)
{
}

/* ---- Scene 0x03 ------------------------------------------------------------------------------- */

/* 0x00236D40, 0x8 bytes, matching. Scene 0x03 enter: empty. */
void func_00236D40(void)
{
}

/* 0x00236D50, 0x8 bytes, matching. Scene 0x03 leave: empty. */
void func_00236D50(void)
{
}

/* 0x00236D60, 0x8 bytes, matching. Scene 0x03 update. */
int func_00236D60(void)
{
    return 1;
}

/* 0x00236D70, 0x8 bytes, matching. Scene 0x03 step: empty. */
void func_00236D70(void)
{
}

/* 0x00236D80, 0x8 bytes, matching. Scene 0x03 draw: empty. */
void func_00236D80(void)
{
}
