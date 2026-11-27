/*
 * emp_state_bits.c - Empire game state bits and pairs between 0x003280F0 and 0x0032958C: event
 * flags (100 bits from 0x0068F007), province bits (0x0068F035, 0x0068F039), twelve province
 * pairs (0x0068DDE0), ten (value, kind) records (0x0068DF50) and seen bits (0x0068DE40).
 * Original file name unknown.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_0068F007[], g_0068F035[], g_0068F039[];
extern int g_0068DDE0[0xC][2];
extern int g_0068DF50[10][2];
extern u32 g_0068DE40[];

int func_0030AB90(void);
void func_00329590(void);

#define PROVINCE_OK(p) ((p) >= 0 && (p) < func_0030AB90())

/* 0x003280F0, 0xA0 bytes. Sets event flag `k`. */
void func_003280F0(int k, int on)
{
    u8 *b;

    if (k >= 100)
        return;
    b = &g_0068F007[k / 8];
    if (on == 0)
        *b &= ~(1 << (k % 8 & 0x1F));
    else
        *b |= 1 << (k % 8 & 0x1F);
}

/* 0x00328190, 0x5C bytes. */
u32 func_00328190(int k)
{
    if (k < 100)
        return g_0068F007[k / 8] & 1 << (k % 8 & 0x1F);
    return 0;
}

/* 0x00328DE0, 0x8C bytes. */
u32 func_00328DE0(int p)
{
    if (p < 0 || p >= func_0030AB90())
        return 0;
    return g_0068F035[p / 8] & 1 << (p % 8 & 0x1F);
}

/* 0x00328FA0, 0x8C bytes. */
u32 func_00328FA0(int p)
{
    if (p < 0 || p >= func_0030AB90())
        return 0;
    return g_0068F039[p / 8] & 1 << (p % 8 & 0x1F);
}

/* 0x00329030, 0x58 bytes. Clears the province pairs (0x19: none). */
void func_00329030(void)
{
    int k;

    for (k = 0; k < 0xC; k++) {
        g_0068DDE0[k][0] = 0x19;
        g_0068DDE0[k][1] = 0x19;
    }
}

/* 0x00329090, 0xC8 bytes. Sets pair `k`. */
void func_00329090(int k, int a, int b)
{
    if (k >= 0xC)
        return;
    if (!PROVINCE_OK(a) && a != 0x19)
        return;
    if (!PROVINCE_OK(b) && b != 0x19)
        return;
    g_0068DDE0[k][0] = a;
    g_0068DDE0[k][1] = b;
}

/* 0x00329160, 0xB8 bytes. Gets it; whether both are provinces. */
int func_00329160(int k, int *a, int *b)
{
    if (k >= 0xC)
        return 0;
    *a = g_0068DDE0[k][0];
    *b = g_0068DDE0[k][1];
    return PROVINCE_OK(*a) && PROVINCE_OK(*b);
}

/* 0x00329220, 0xA4 bytes. The number of pairs in use. */
int func_00329220(void)
{
    int k;

    for (k = 0; k < 0xC; k++) {
        if (!PROVINCE_OK(g_0068DDE0[k][0]))
            return k;
        if (!PROVINCE_OK(g_0068DDE0[k][1]))
            return k;
    }
    return 0xC;
}

/* 0x003292D0, 0x98 bytes. Sets `a`'s kind `v` (a new record when it has none). */
void func_003292D0(int a, int v)
{
    int i, j;

    if (v >= 8)
        return;
    for (i = 0; i < 10; i++) {
        if (g_0068DF50[i][0] == a) {
            g_0068DF50[i][1] = v;
            break;
        }
    }
    if (i == 10) {
        for (j = 0; j < 10; j++) {
            if (g_0068DF50[j][0] == -1) {
                g_0068DF50[j][0] = a;
                g_0068DF50[j][1] = v;
                break;
            }
        }
    }
}

/* 0x003294E0, 0x60 bytes. Marks `k` seen. */
void func_003294E0(int k)
{
    g_0068DE40[k / 32] |= 1 << (k % 32 & 0x1F);
    func_00329590();
}

/* 0x00329540, 0x4C bytes. */
int func_00329540(int k)
{
    return (1 << (k % 32 & 0x1F) & g_0068DE40[k / 32]) != 0;
}
