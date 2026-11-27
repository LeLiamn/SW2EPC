/*
 * tactics.c - the battle tactics state (0x007B9880: for each side two tactic slots with their
 * kind (0x1F: none), timer and used bit; saved in the save image at +0xB5) and their checks.
 * Original file name unknown (parts of 0x0036DCE0-0x0036F8FC).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_0045D7B0[2];                 /* (small data) */
extern int g_00415F30[5], g_00415F50[30], g_00415FD0[27];
extern u8 g_00669D60[];

u8 *func_0036DCD0(void);
void func_0011EB80(u8 *to, const u8 *from, int n);
void func_00118850(void *p, int n);
void func_0036EB40(u32 s, u32 k);
void func_0036FAC0(u32 s, u32 k);
int func_0036EFA0(u32 v);
int func_0036D2E0(void);
void func_0035DBD0(int *t, int a, int b);

#define TAC() func_0036DCD0()

/* 0x0036DCE0, 0x48 bytes. Sets side `s`'s tactic slot `k`. */
void func_0036DCE0(u32 s, u32 k, u8 v)
{
    if (s < 2 && k < 2)
        TAC()[k + s * 2] = v;
}

/* 0x0036DD30, 0x54 bytes. Its tactic (0x1F: none). */
u8 func_0036DD30(u32 s, u32 k)
{
    if (s < 2 && k < 2)
        return TAC()[k + s * 2];
    return 0x1F;
}

/* 0x0036DD90, 0x68 bytes. Its timer. */
void func_0036DD90(u32 s, u32 k, u8 v)
{
    if (s < 2 && k < 2)
        TAC()[k + 4 + s * 2] = v;
}

/* 0x0036DE00, 0x58 bytes. */
u8 func_0036DE00(u32 s, u32 k)
{
    if (s < 2 && k < 2)
        return TAC()[k + 4 + s * 2];
    return 0;
}

/* 0x0036DE60, 0x6C bytes. Counts the timer down. */
void func_0036DE60(u32 s, u32 k)
{
    if (s < 2 && k < 2) {
        u8 v = func_0036DE00(s, k);

        func_0036DD90(s, k, v != 0 ? v - 1 : 0);
    }
}

/* 0x0036DED0, 0x60 bytes. Marks the slot used. */
void func_0036DED0(u32 s, u32 k)
{
    if (s < 2 && k < 2)
        TAC()[8] |= 1 << ((k + s * 2) & 0x1F);
}

/* 0x0036DF30, 0x64 bytes. */
void func_0036DF30(u32 s, u32 k)
{
    if (s < 2 && k < 2)
        TAC()[8] &= ~(1 << ((k + s * 2) & 0x1F));
}

/* 0x0036DFA0, 0x64 bytes. */
int func_0036DFA0(u32 s, u32 k)
{
    if (s < 2 && k < 2)
        return (1 << ((k + s * 2) & 0x1F) & 0xFF & TAC()[8]) != 0;
    return 0;
}

/* 0x0036E010, 0x2C bytes. Saves the state into save image `p`. */
void func_0036E010(u8 *p)
{
    func_0011EB80(p + 0xB5, TAC(), 9);
}

/* 0x0036E080, 0x84 bytes, matching. Clears every slot. */
void func_0036E080(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 2; k++) {
            func_0036DCE0(s, k, 0x1F);
            func_0036DD90(s, k, 0);
            func_0036DF30(s, k);
        }
    }
    func_00118850(g_0045D7B0, 2);
}

/* 0x0036E260, 0xAC bytes. Running tactics 0x19 act. */
void func_0036E260(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 2; k++) {
            u8 v = func_0036DD30(s, k);

            if (v < 0x1F && func_0036DE00(s, k) != 0 && v == 0x19)
                func_0036EB40(s, k);
        }
    }
}

/* 0x0036E310, 0xA4 bytes. Counts the running tactics down (ending them at 0). */
void func_0036E310(void)
{
    u32 s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 2; k++) {
            if (func_0036DD30(s, k) < 0x1F && func_0036DE00(s, k) != 0) {
                func_0036DE60(s, k);
                if (func_0036DE00(s, k) == 0)
                    func_0036FAC0(s, k);
            }
        }
    }
}

/* 0x0036EFC0, 0xC8 bytes. */
int func_0036EFC0(int v)
{
    if (v == 0x1E || v == 0x1D || v == 0x1C || v == 0x1B || v == 0x1A || v == 0x19 || v == 0x18
        || v == 0x17 || v == 0x16 || v == 0x15 || v == 9 || v == 7 || v == 6 || v == 3 || v == 2)
        return 1;
    return 0;
}

/* 0x0036F1E0, 0xB0 bytes. How many of side `s`'s slots hold a tactic (`b`: not yet used). */
int func_0036F1E0(u32 s, int b)
{
    u32 k;
    int n = 0;

    if (s >= 2)
        return 0;
    for (k = 0; k < 2; k++) {
        func_0036DD30(s, k);
        if (func_0036DD30(s, k) < 0x1F && (b == 0 || func_0036DFA0(s, k) == 0))
            n++;
    }
    return n;
}

/* 0x0036F290, 0x90 bytes. */
int func_0036F290(u32 s, u32 k)
{
    u8 v;

    if (s >= 2 || k >= 2)
        return 0;
    v = func_0036DD30(s, k);
    if (v >= 0x1F)
        return 0;
    if (func_0036EFA0(v) == 0)
        return 0;
    return func_0036DFA0(s, k) == 0;
}

/* 0x0036F320, 0x6C bytes. */
int func_0036F320(u32 s)
{
    u32 k;

    for (k = 0; k < 2; k++) {
        func_0036DD30(s, k);
        if (func_0036DD30(s, k) < 0x1F)
            return 1;
    }
    return 0;
}

/* 0x0036F390, 0x84 bytes. Whether side `s` has tactic `t`. */
int func_0036F390(u32 s, u32 t)
{
    u32 k;

    if (s >= 2 || t >= 0x1F)
        return 0;
    for (k = 0; k < 2; k++) {
        if (t == func_0036DD30(s, k))
            return 1;
    }
    return 0;
}

/* 0x0036F420, 0x90 bytes. */
int func_0036F420(u32 s, u32 t)
{
    u32 k;
    int n = 0;

    if (s >= 2 || t >= 0x1F)
        return 0;
    for (k = 0; k < 2; k++) {
        if (t == func_0036DD30(s, k))
            n++;
    }
    return n;
}

/* 0x0036F4B0, 0x68 bytes. */
u32 func_0036F4B0(u32 s, u32 t)
{
    u32 k;

    for (k = 0; k < 2; k++) {
        if (t == func_0036DD30(s, k))
            return k;
    }
    return 2;
}

/* 0x0036F520, 0x98 bytes. Whether side `s`'s tactic `t` is running. */
int func_0036F520(u32 s, u32 t)
{
    u32 k;

    if (s >= 2 || t >= 0x1F)
        return 0;
    for (k = 0; k < 2; k++) {
        if (t == func_0036DD30(s, k) && func_0036DE00(s, k) != 0)
            return 1;
    }
    return 0;
}

/* 0x0036F5E0, 0x20 bytes, matching. */
int func_0036F5E0(u32 s)
{
    return func_0036F520(s, 0x15) != 0;
}

/* 0x0036F600, 8 bytes, matching. */
int func_0036F600(int v)
{
    return v - 0x3B;
}

/* 0x0036F610, 8 bytes, matching. */
int func_0036F610(int v)
{
    return v + 0x3B;
}

/* 0x0036F620, 0x7C bytes. */
int func_0036F620(void)
{
    int t[5], k;

    for (k = 0; k < 5; k++)
        t[k] = g_00415F30[k];
    return *(int *)(g_00669D60 + 0x224) * 4 / 8 + t[g_00669D60[0x21]];
}

/* 0x0036F810, 0x54 bytes. */
void func_0036F810(void)
{
    int t[30], k;

    for (k = 0; k < 30; k++)
        t[k] = g_00415F50[k];
    func_0035DBD0(t, 10, 100);
}

/* 0x0036F870, 0x50 bytes. */
void func_0036F870(void)
{
    int t[27], k;

    for (k = 0; k < 27; k++)
        t[k] = g_00415FD0[k];
    func_0035DBD0(t, 9, 0x5A);
}

/* 0x0036F8C0, 0x3C bytes. */
void func_0036F8C0(void)
{
    if (func_0036D2E0() == 0)
        func_0036F870();
    else
        func_0036F810();
}
