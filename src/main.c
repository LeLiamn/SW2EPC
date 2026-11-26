/*
 * main.c - entry point and main loop of Samurai Warriors 2: Empires (SLES_546.24).
 *
 * Decompiled by reading the original machine code (with Ghidra and the R5900 extension); not
 * verified by compiling, since the original compiler (CodeWarrior for PS2) is not available to the
 * project. Unknown functions and globals keep neutral names (func_/g_ + address) until their role
 * is proven; comments with a question mark are hypotheses.
 */

typedef unsigned int u32;

/* 0x0045D1C4 (gp - 0x7A2C): a flag set to 0 before and 1 after set-up, shutdown and every pass of
 * the main loop. Its readers are not identified yet. */
extern int g_0045D1C4;

/* 0x0045CB80: passed four times to func_00117F10 during system set-up. */
extern u32 g_0045CB80[];

/* 0x7000015C: a word in the PS2 scratchpad RAM, set to 12345 at start-up (random seed?). */
#define g_7000015C (*(volatile u32 *)0x7000015C)

int func_001005A0(void);
void func_00102380(void);
void func_001023E0(void);
void func_001029B0(void);
void func_00102A00(void);
void func_00102B80(void);
void func_00103060(void);
void func_00104040(void);
void func_001040D0(void);
void func_001062F0(void);
void func_00106700(void);
void func_00117EB0(void);
void func_00117F10(void *a, void *b, void *c, void *d);
void func_001181E0(void);
void func_0022DE80(void);
void func_00143F50(void);
void func_00143FB0(void);

/* 0x001014D0, 8 bytes. */
void func_001014D0(int value)
{
    g_0045D1C4 = value;
}

/* 0x00117E50, 0x38 bytes. First call of main. */
void func_00117E50(void)
{
    func_00117F10(g_0045CB80, g_0045CB80, g_0045CB80, g_0045CB80);
}

/* 0x00117E90, 0x1C bytes. Last call of main. */
void func_00117E90(void)
{
    func_00117EB0();
}

/* 0x00106750, 0x80 bytes. Game set-up: eleven initialisation calls, bracketed by the flag. */
void func_00106750(void)
{
    func_001014D0(0);
    func_00103060();
    func_00106700();
    func_001023E0();
    func_001062F0();
    func_00104040();
    func_0022DE80();
    func_001029B0();
    func_001181E0();
    func_00143F50();
    func_00102B80();
    g_7000015C = 12345;
    func_001014D0(1);
}

/* 0x001067D0, 0x3C bytes. Game shutdown, bracketed by the flag. */
void func_001067D0(void)
{
    func_001014D0(0);
    func_00143FB0();
    func_00102A00();
    func_001040D0();
    func_001014D0(1);
}

/* 0x00106810, 0x24 bytes. Called after each pass of the main loop: only toggles the flag. */
void func_00106810(void)
{
    func_001014D0(0);
    func_001014D0(1);
}

/* 0x00102A20, 0x58 bytes. Called by the start-up code (crt0) with argc/argv, followed by exit().
 * The work of each frame is done by the loop condition, func_001005A0 (large: game state machine?). */
int main(int argc, char **argv)
{
    func_00117E50();
    func_00106750();
    while (func_001005A0() == 0)  /* non-zero: leave the main loop */
        func_00106810();
    func_001067D0();
    func_00117E90();
    return 0;
}
