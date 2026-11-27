/*
 * model_cache.c - the battle's model file cache (0xB6 entries at 0x0073C484, with "keep" and
 * "wanted" bit sets), the small linear heaps used while loading (0x0045D418, 0x0045D424) and the
 * minimap cell colour table (0x0073DA10). Original file name unknown (parts of 0x0020DF00-
 * 0x0020FFB8).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8 *g_0073C484[0xB6];             /* the model files */
extern u32 g_0073C75C[6], g_0073C774[6];   /* the keep and wanted bits */
extern u8 g_0073C460[];
extern u8 *g_0073C480;
extern int g_0073C78C, g_0073C790;
extern u8 g_0073C798, g_0073C79A, g_0073C79E, g_0073C79F;
extern u8 *g_0073C7AC;
extern u8 g_00730570[];
extern u8 *g_005BA6A0;
extern int g_0045D430, g_0045D434;       /* (small data) */
extern u8 *g_0045D418, *g_0045D41C, *g_0045D420;   /* (small data) the load heap */
extern u8 *g_0045D424, *g_0045D428;
extern u8 *g_0073DA10, *g_0073DA14, *g_0073DA1C;

#define SP_PKT (*(u8 **)0x70000158)

void func_0020E9D0(int k);
void func_0020E8C0(int k, int a, int b);
void func_0020ED30(void);
void func_0020EAA0(int k, int a);
u8 *func_00102D30(int n);
void func_00118850(void *p, int n);
void func_00102EC0(u8 *p);
u8 *func_00102DB0(int a, int n);
void func_0020EE50(void);
u8 *func_001050F0(void);
u8 *func_0020EEC0(u8 *p);
void func_00105390(u8 *p);
int func_00190480(u8 *q);
int func_0020FD50(u8 *q);

/* 0x0020DF00, 0x20 bytes, matching. The two models kept for the whole battle. */
int func_0020DF00(int k)
{
    return k == 0x1C || k == 0x24;
}

/* 0x0020DF20, 0x4C bytes. */
void func_0020DF20(u32 k, int on, u32 *bits)
{
    u32 *w = bits + (k >> 5);

    if (on == 0)
        *w &= ~(1 << (k & 0x1F));
    else
        *w |= 1 << (k & 0x1F);
}

/* 0x0020DF70, 0x24 bytes. */
u32 func_0020DF70(u32 k, u32 *bits)
{
    return bits[k >> 5] & 1 << (k & 0x1F);
}

/* 0x0020DFA0, 0x1C bytes, matching. */
void func_0020DFA0(u32 *bits)
{
    bits[0] = 0;
    bits[1] = 0;
    bits[2] = 0;
    bits[3] = 0;
    bits[4] = 0;
    bits[5] = 0;
}

/* 0x0020DFC0, 0x20 bytes, matching. */
void func_0020DFC0(u32 k, int on)
{
    func_0020DF20(k, on, g_0073C75C);
}

/* 0x0020DFE0, 0x48 bytes. Whether model `k` is loaded and kept. */
u32 func_0020DFE0(int k)
{
    if (g_0073C484[k] == 0)
        return 0;
    return func_0020DF70(k, g_0073C75C);
}

void func_0020EB40(void);

/* 0x0020E030, 0x44 bytes. */
void func_0020E030(void)
{
    func_0020EB40();
    func_0020DFA0(g_0073C75C);
    g_0073C78C = 0xB6;
    g_0045D434 = 0;
    g_0045D430 = 0;
    g_0073C790 = 0xB6;
}

/* 0x0020E080, 0x48 bytes. Frees the two battle-long models. */
void func_0020E080(void)
{
    int k;

    for (k = 0; k < 0xB6; k++) {
        if (func_0020DF00(k) != 0)
            func_0020E9D0(k);
    }
}

/* 0x0020E140, 0x2C bytes. */
int func_0020E140(void)
{
    if (g_0073C78C > 0x27 && g_0073C78C < 0x45)
        return 1;
    return 0;
}

/* 0x0020E170, 0x2C bytes. */
int func_0020E170(void)
{
    if (g_0073C78C > 0x44 && g_0073C78C < 0x62)
        return 1;
    return 0;
}

/* 0x0020E1A0, 0x4C bytes. */
int func_0020E1A0(void)
{
    if (g_0073C78C > 0x61 && g_0073C78C < 0xB6 && g_0073C798 == 0)
        return 1;
    return 0;
}

/* 0x0020E1F0, 0x34 bytes, matching. */
int func_0020E1F0(void)
{
    int on = func_0020E140() != 0;

    if (!on)
        on = func_0020E170() != 0;
    return on;
}

/* 0x0020E440, 0x34 bytes. */
int func_0020E440(u32 v)
{
    v &= 0xFF;
    if (v < 0x1C)
        return v;
    if (v < 0x40)
        return v + 4;
    return v;
}

/* 0x0020E480, 0x24 bytes. */
int func_0020E480(void)
{
    return func_0020E440(g_005BA6A0[0x656E]);
}

/* 0x0020E4B0, 0x24 bytes. */
int func_0020E4B0(void)
{
    return func_0020E440(g_005BA6A0[0x659A]);
}

/* 0x0020E4E0, 0x3C bytes. */
void func_0020E4E0(void)
{
    func_00118850(g_0073C460, 0x10A0);
    func_0020E030();
    g_0073C480 = g_00730570;
}

/* 0x0020E520, 0x1C bytes, matching. */
void func_0020E520(void)
{
    func_0020E080();
}

void func_0020EA40(void);

/* 0x0020E540, 0x24 bytes, matching. */
void func_0020E540(void)
{
    func_0020EA40();
    func_0020E030();
}

/* 0x0020E570, 0x30 bytes. */
void func_0020E570(void)
{
    g_0073C79E = func_0020E480();
    g_0073C79F = func_0020E4B0();
}

/* 0x0020E5A0, 0x20 bytes. */
void func_0020E5A0(u8 v)
{
    g_0073C79A = v;
    func_0020E570();
}

/* 0x0020E8B0, 0xC bytes. */
u8 *func_0020E8B0(void)
{
    return g_0073C7AC;
}

/* 0x0020E960, 0x70 bytes, matching. Loads the wanted models. */
void func_0020E960(int a, int b)
{
    int k;

    for (k = 0; k < 0xB6; k++) {
        if (func_0020DF70(k, g_0073C774) != 0)
            func_0020E8C0(k, a, b);
    }
}

/* 0x0020E9D0, 0x6C bytes. Frees model `k` unless kept. */
void func_0020E9D0(int k)
{
    u8 **p = &g_0073C484[k];

    if (*p != 0 && func_0020DFE0(k) == 0) {
        func_00102EC0(*p);
        *p = 0;
        func_0020DFC0(k, 0);
    }
}

/* 0x0020EA40, 0x5C bytes. Frees all but the battle-long models. */
void func_0020EA40(void)
{
    int k;

    for (k = 0; k < 0xB6; k++) {
        if (func_0020DF00(k) == 0)
            func_0020E9D0(k);
    }
    if (g_0045D424 != 0)
        func_0020ED30();
}

/* 0x0020EB10, 0x24 bytes, matching. */
void func_0020EB10(u32 k)
{
    func_0020DF20(k, 1, g_0073C774);
}

/* 0x0020EB40, 0x20 bytes, matching. */
void func_0020EB40(void)
{
    func_0020DFA0(g_0073C774);
}

/* 0x0020EB60, 0x44 bytes. */
void func_0020EB60(int k, int a, int on)
{
    if (on != 0) {
        func_0020EB10(k);
        func_0020EAA0(k, a);
    }
}

void func_0020EC20(void);
void func_0020EBE0(int n);
void func_0020EC70(void);

/* 0x0020EBB0, 0x30 bytes. */
void func_0020EBB0(void)
{
    if (g_0045D418 != 0) {
        func_0020EC20();
        func_0020EBE0(0x2800);
    }
}

/* 0x0020EBE0, 0x34 bytes, matching. Takes the load heap (`n` bytes). */
void func_0020EBE0(int n)
{
    g_0045D418 = func_00102D30(n);
    g_0045D41C = g_0045D418 + n;
    func_0020EC70();
}

/* 0x0020EC20, 0x28 bytes, matching. */
void func_0020EC20(void)
{
    func_00102EC0(g_0045D418);
    g_0045D418 = 0;
    g_0045D420 = 0;
    g_0045D41C = 0;
}

/* 0x0020EC50, 0x1C bytes, matching. Takes `n` bytes of it (16-aligned). */
u8 *func_0020EC50(int n)
{
    u8 *r = (u8 *)(((u32)g_0045D420 + 0xF) & 0xFFFFFFF0);

    g_0045D420 = r + n;
    return r;
}

/* 0x0020EC70, 0x2C bytes, matching. Empties it. */
void func_0020EC70(void)
{
    func_00118850(g_0045D418, g_0045D41C - g_0045D418);
    g_0045D420 = g_0045D418;
}

/* 0x0020ECA0, 0x3C bytes, matching. */
void func_0020ECA0(int n)
{
    g_0045D424 = func_00102DB0(0x40, n);
    g_0045D428 = g_0045D424 + n;
    func_0020EE50();
}

/* 0x0020F130, 0x54 bytes, matching. */
void func_0020F130(void)
{
    u8 *p = func_001050F0();

    SP_PKT = func_0020EEC0(SP_PKT);
    *(u64 *)(p + 0x10) = 0x3000D;
    *(u64 *)(p + 0x18) = 0x48;
    func_00105390(p);
}

/* 0x0020F190, 0x38 bytes, matching. */
void func_0020F190(void)
{
    u8 *p = func_001050F0();

    *(u64 *)(p + 0x10) = 0x5000D;
    *(u64 *)(p + 0x18) = 0x48;
    func_00105390(p);
}

u8 *func_0020FE60(u8 *base, u32 v);

/* 0x0020FCF0, 0x54 bytes. Sets map cell `q`'s colour. */
void func_0020FCF0(u8 *q, int v)
{
    *(int *)func_0020FE60(g_0073DA1C, g_0073DA14[q[0] * 0x20 + q[1]]) = v;
}

/* 0x0020FE60, 0x4C bytes. The palette slot of index `v` (CSM1 order: 8-15 and 16-23 swapped). */
u8 *func_0020FE60(u8 *base, u32 v)
{
    u32 u = v & 0x1F;

    if (u < 8 || u > 0xF) {
        if (u > 0xF && u < 0x18)
            v -= 8;
    } else {
        v += 8;
    }
    return base + v * 4;
}

/* 0x0020FEB0, 0x3C bytes. */
void func_0020FEB0(void)
{
    if (g_0073DA10 != 0) {
        func_00102EC0(g_0073DA10);
        func_00118850(&g_0073DA10, 0x10);
    }
}

/* 0x0020FF60, 0x4C bytes. */
void func_0020FF60(u8 *q)
{
    int v;

    if (func_00190480(q) == 0)
        v = 0;
    else
        v = func_0020FD50(q);
    func_0020FCF0(q, v);
}

/* 0x0020FFB0, 8 bytes, matching. */
void func_0020FFB0(void)
{
}
