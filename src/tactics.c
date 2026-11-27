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
int func_0035DBD0(int *t, int a, int b);

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

/* 0x0036F810, 0x54 bytes. A random tactic (Empire battles). */
int func_0036F810(void)
{
    int t[30], k;

    for (k = 0; k < 30; k++)
        t[k] = g_00415F50[k];
    return func_0035DBD0(t, 10, 100);
}

/* 0x0036F870, 0x50 bytes. A random tactic (other battles). */
int func_0036F870(void)
{
    int t[27], k;

    for (k = 0; k < 27; k++)
        t[k] = g_00415FD0[k];
    return func_0035DBD0(t, 9, 0x5A);
}

/* 0x0036F8C0, 0x3C bytes. */
int func_0036F8C0(void)
{
    if (func_0036D2E0() == 0)
        return func_0036F870();
    return func_0036F810();
}

extern u8 g_006A1D58[][0x68];            /* the groups */

u8 func_00362600(u32 s, u32 k);
void func_003283D0(int v);
int func_0032E7B0(void);
int *func_0033EF80(u32 k);
u8 *func_00338410(int g);
int func_0033B1E0(int *g);
void func_00338500(int *g, int v);
u8 func_0035D5A0(int s);
int func_0034EC80(u32 i);
int func_0034EE50(int c);
u32 func_0034EDB0(int c);
int func_0034EE60(int c);
void func_0036E8D0(int c);

#define GROUP_INDEX(g) (((u8 *)(g) - g_006A1D58[0]) / 0x68)

/* 0x0036E170, 0xEC bytes. Loads the battle's tactics (Empire battles: the player's are used up). */
void func_0036E170(void)
{
    u32 s, k;

    if (*(int *)(g_00669D60 + 0x20C) == 1 || func_0032E7B0() != 0)
        return;
    for (s = 0; s < 2; s++) {
        for (k = 0; k < 2; k++) {
            u8 t = func_00362600(s, k);

            if (t < 0x1F)
                func_0036DCE0(s, k, t);
        }
    }
    if (func_0036D2E0() != 0) {
        for (k = 0; k < 2; k++) {
            u8 t = func_00362600(0, k);

            if (t < 0x1F)
                func_003283D0(func_0036F610(t));
        }
    }
}

/* 0x0036E430, 0x104 bytes. Side `s`'s gate groups get a tenth of their strength back (1000 at
 * least). */
void func_0036E430(u32 s)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        int *g = func_0033EF80(k);

        if ((g[0x19] & 1) != 0 && s == ((u8 *)g[0])[0x79]) {
            u8 *r = func_00338410(GROUP_INDEX(g));

            if (r[0x25] == 'G' && func_0033B1E0(g) != 0) {
                u32 v = *(u16 *)(func_00338410(GROUP_INDEX(g)) + 0x1C) / 10;

                if (v < 1000)
                    v = 1000;
                func_00338500(g, v);
            }
        }
    }
}

/* 0x0036E550, 0x114 bytes. The enemy's gate groups lose a fifth (1000 at least). */
void func_0036E550(void)
{
    u8 s = func_0035D5A0(0);
    u32 k;

    for (k = 0; k < 0x10; k++) {
        int *g = func_0033EF80(k);

        if ((g[0x19] & 1) != 0 && s == ((u8 *)g[0])[0x79]) {
            u8 *r = func_00338410(GROUP_INDEX(g));

            if (r[0x25] == 'G' && func_0033B1E0(g) != 0) {
                u32 v = (*(u16 *)(func_00338410(GROUP_INDEX(g)) + 0x1C) << 1) / 10;

                if (v < 1000)
                    v = 1000;
                func_00338500(g, -(int)v);
            }
        }
    }
}

/* 0x0036EA60, 0xC8 bytes. Tactic: turns enemy camps (its timer: 60 or 120 frames). */
void func_0036EA60(u32 s, u32 k)
{
    u8 side = func_0035D5A0(s);
    u32 i;

    for (i = 0; i < 0x14; i++) {
        int c = func_0034EC80(i);

        if (func_0034EE50(c) != 0 && func_0034EDB0(c) == side && func_0034EE60(c) == 0)
            func_0036E8D0(c);
    }
    func_0036DD90(s, k, s == 0 ? 0x3C : 0x78);
}

/* More tactic effects, the tactic choice rules and the weather state (gp 0x0045D7B8: kind,
 * a value, a third byte), parts of 0x0036EC10-0x0036FEE8. */

extern u32 g_7000015C;
extern u8 g_0045D7B8[5];                 /* (small data) */

#define RANDOM() (g_7000015C = g_7000015C * 0x41C64E6D + 0x3039, g_7000015C >> 0x10)
#define GROUP_ALIVE(g) ((*(u32 *)((u8 *)(g)[0] + 0x80) & 1) != 0 &&                       \
                        (*(u32 *)((u8 *)(g)[0] + 0x80) & 0x8C40002) == 0 &&               \
                        (*(u32 *)((u8 *)(g)[0] + 0x80) & 4) == 0)

void func_0035CDF0(void);
void func_0035CE30(void);
u8 *func_002EFB00(int k);
void func_0036FD30(u32 k, u32 v);

/* 0x0036EC10, 0x144 bytes. Side `s`'s gate groups get strong defence (1000) and morale 120. */
void func_0036EC10(u32 s)
{
    u32 k;

    for (k = 0; k < 0x10; k++) {
        int *g = func_0033EF80(k);

        if ((g[0x19] & 1) != 0 && GROUP_ALIVE(g) && s == ((u8 *)g[0])[0x79]) {
            int i = GROUP_INDEX(g);

            if (func_00338410(i)[0x25] == 'G') {
                g[0x13] = 1000;
                if (func_00338410(i)[0x23] < 0x78)
                    func_00338410(i)[0x23] = 0x78;
            }
        }
    }
}

/* 0x0036ED70, 0x12C bytes. The enemy's gate groups lose their defence. */
void func_0036ED70(void)
{
    u8 s = func_0035D5A0(0);
    u32 k;

    for (k = 0; k < 0x10; k++) {
        int *g = func_0033EF80(k);

        if ((g[0x19] & 1) != 0 && GROUP_ALIVE(g) && s == ((u8 *)g[0])[0x79]) {
            if (func_00338410(GROUP_INDEX(g))[0x25] == 'G') {
                g[0x13] = 1;
                func_00338410(GROUP_INDEX(g))[0x23] = 0;
            }
        }
    }
}

/* 0x0036F090, 0xE4 bytes. Whether tactic `k` can be used here. */
int func_0036F090(int k)
{
    if (k == 0x1D)
        return func_0036D2E0();
    if (k == 0x1E || k == 0x17 || k == 0x15 || k == 0x14 || k == 0xC || k == 0xB || k == 10
        || k == 9 || k == 8 || k == 5 || k == 4 || k == 3 || k == 2 || k == 1 || k == 0)
        return 1;
    return 0;
}

/* 0x0036F6A0, 0x164 bytes. Whether tactic `t` fits slot `slot` next to the others (`mode`: the
 * battle's kind). */
int func_0036F6A0(u32 t, u32 slot, u32 *cur, int mode)
{
    u32 i;

    if (t > 0xC && t < 0x14) {
        for (i = 0; i < 2; i++) {
            if (i != slot && cur[i] > 0xC && cur[i] < 0x14)
                return 0;
        }
    }
    if (t < 2) {
        for (i = 0; i < 2; i++) {
            if (i != slot) {
                if (cur[i] == 0 && t == 1)
                    return 0;
                if (cur[i] == 1 && t == 0)
                    return 0;
            }
        }
    }
    if (t == 4 && mode != 2 && mode != 0)
        return 0;
    if (func_0036EFC0(t) == 0) {
        for (i = 0; i < 2; i++) {
            if (i != slot && cur[i] == t)
                return 0;
        }
    }
    return 1;
}

/* 0x0036F900, 0x90 bytes. Gives the first side a random tactic in a free slot (0x1F: none). */
int func_0036F900(void)
{
    u32 k;
    int v;

    for (k = 0; k < 2; k++) {
        func_0036DD30(0, k);
        if (func_0036DD30(0, k) > 0x1E)
            break;
    }
    if (k >= 2)
        return 0x1F;
    v = func_0036F8C0();
    func_0036DCE0(0, k, v);
    return v;
}

/* 0x0036F990, 0x3C bytes, matching. */
void func_0036F990(u32 s, u32 k)
{
    func_0035CDF0();
    func_0036DED0(s, k);
}

/* 0x0036FAC0, 0x1C bytes, matching. */
void func_0036FAC0(u32 s, u32 k)
{
    func_0035CE30();
}

/* 0x0036FBD0, 8 bytes, matching. The weather state. */
u8 *func_0036FBD0(void)
{
    return g_0045D7B8;
}

/* 0x0036FC20, 0x40 bytes. */
void func_0036FC20(void)
{
    func_0036FBD0();
    func_0036FBD0()[0] = 4;
    func_0036FBD0()[1] = 0x47;
    func_0036FBD0()[2] = 0xFF;
}

/* 0x0036FC60, 0x28 bytes, matching. */
u8 func_0036FC60(void)
{
    func_0036FBD0();
    return func_0036FBD0()[0];
}

/* 0x0036FC90, 0x40 bytes. */
int func_0036FC90(void)
{
    func_0036FC60();
    return func_0036FC60() < 4;
}

/* 0x0036FCD0, 0x28 bytes, matching. */
u8 func_0036FCD0(void)
{
    func_0036FBD0();
    return func_0036FBD0()[1];
}

/* 0x0036FD00, 0x28 bytes, matching. */
u8 func_0036FD00(void)
{
    func_0036FBD0();
    return func_0036FBD0()[2];
}

/* 0x0036FDD0, 0x34 bytes. Loads it from the save image. */
void func_0036FDD0(void)
{
    u8 *q = func_002EFB00(9);

    func_0011EB80(func_0036FBD0(), q + 0xB0, 5);
}

/* 0x0036FE10, 0x6C bytes. */
void func_0036FE10(void)
{
    u32 k;

    func_0036FC20();
    for (k = 0; k < 2; k++)
        func_0036FD30(k, RANDOM() % 0x3C);
}

/* 0x0036FE80, 0x1C bytes, matching. */
void func_0036FE80(void)
{
    func_0036FDD0();
}

/* 0x0036FEA0, 0x40 bytes, matching. */
void func_0036FEA0(void)
{
    if (*(int *)(g_00669D60 + 0x20C) == 1)
        func_0036FE80();
    else
        func_0036FE10();
}

/* 0x0036FEE0, 8 bytes, matching. */
void func_0036FEE0(void)
{
}
