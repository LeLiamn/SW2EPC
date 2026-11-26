/*
 * main.c - entry point of Samurai Warriors 2: Empires (SLES_546.24).
 *
 * Decompiled by reading the original machine code; not yet verified by compiling (the original
 * compiler, CodeWarrior for PS2, is not available to the project). Unknown functions keep neutral
 * func_<address> names until their role is proven.
 */

int func_001005A0(void);
void func_00106750(void);
void func_001067D0(void);
void func_00106810(void);
void func_00117E50(void);
void func_00117E90(void);

/* 0x00102A20, 0x58 bytes. Called by the start-up code (crt0) with argc/argv, followed by exit(). */
int main(int argc, char **argv)
{
    func_00117E50();              /* system set-up? */
    func_00106750();              /* game set-up? */
    while (func_001005A0() == 0)  /* non-zero: leave the main loop */
        func_00106810();          /* one frame of the game? */
    func_001067D0();              /* game shutdown? */
    func_00117E90();              /* system shutdown? */
    return 0;
}
