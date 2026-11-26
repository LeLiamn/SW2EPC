/*
 * scene_tutorial.c - scene 0x11 (original source file SceneTutorial.c, probable). Scene 0x17,
 * the rest of the file, is not decompiled yet.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Scene 0x11 starts the first of the tutorials 0x0C, 0x0D and 0x0E that func_003D2F80 accepts
 * (not yet seen?) and does nothing else; its drawing and stepping are empty.
 */

void func_0032F670(void);
void func_0032F640(void);
int func_003D2F80(int tutorial);
void func_003302F0(int tutorial);

/* 0x003F2A50, 0x1C bytes, matching. Scene 0x11 enter. */
void func_003F2A50(void)
{
    func_0032F670();
}

/* 0x003F2A70, 0x1C bytes, matching. Scene 0x11 leave. */
void func_003F2A70(void)
{
    func_0032F640();
}

/* 0x003F2A90, 0x70 bytes, matching. Scene 0x11 update: starts tutorial 0x0C, 0x0D or 0x0E. */
int func_003F2A90(void)
{
    if (func_003D2F80(0x0C) != 0)
        func_003302F0(0x0C);
    else if (func_003D2F80(0x0D) != 0)
        func_003302F0(0x0D);
    else if (func_003D2F80(0x0E) != 0)
        func_003302F0(0x0E);
    return 0;
}

/* 0x003F2B00, 0x8 bytes, matching. Scene 0x11 step: empty. */
void func_003F2B00(void)
{
}

/* 0x003F2B10, 0x8 bytes, matching. Scene 0x11 draw: empty. */
void func_003F2B10(void)
{
}
