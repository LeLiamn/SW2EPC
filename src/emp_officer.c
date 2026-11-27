/*
 * emp_officer.c - the Empire mode's officer records (0x002F2720-..., before emp_cq_main.c; the
 * original file's name is unknown). Written so far: from 0x002F2720.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * 0x19F records of 0x9C bytes (func_0030CCB0 gives the first; numbers past 0x19E use 0x19F).
 * Numbers 400-0x19E are the created officers, whose values come from their own records
 * (func_0039E7C0...). Record: +0 table record, +0xA / +0xC two officer numbers, +0xE / +0x10
 * ages?, +0x12 a kind, +0x42 a face, +0x44 three bytes, +0x47 a group, +0x48 a value, +0x4A the
 * soldiers, +0x4C the stats (life +0x4C...), +0x50 state (bit 7) and rank, +0x51 a role, +0x52
 * a force (0x19: none), +0x54 the level, +0x98 the experience.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 *g_005BA6A0;                   /* the officer table (0x2C bytes each) */
extern char g_007A2CD0[];                /* a name buffer */
extern u32 g_00446410[];
extern u32 g_004141D0[][3];
extern u16 g_004463E0[];                 /* soldiers by level */

u8 *func_0030CCB0(void);
int func_00328230(void);
char *func_0019B170(char *out, u32 t, u32 n);
char *func_0019B200(char *out, u32 t, u32 n);
char *func_0019B0E0(char *out, u32 t);
char *func_0019B130(char *out, u32 id);
char *func_0019B240(char *out, u32 t);
int func_00120A40(const char *s);
int func_0039E7C0(int k);
int func_0039E760(int k);
int func_0039E740(int k);
u32 func_00327C00(void);
u32 func_00327140(u32 a, int b);
int func_00327C70(void);
int func_002F59A0(u32 id);
int func_002F5D30(u32 id);
int func_0030AB90(void);

/* Record `i` (past 0x19E: 0x19F). */
static inline u8 *ofc(u32 i)
{
    if (i > 0x19E)
        i = 0x19F;
    return func_0030CCB0() + i * 0x9C;
}

/* The record number of record `p`. */
#define OFC_NUM(p) (((p) - func_0030CCB0()) / 0x9C)

/* Whether `i` is a created officer. */
#define CREATED(i) ((int)(i) >= 400 && (int)(i) <= 0x19E)

/* Whether names show as the player's: with func_00328230, for records 0xD, 0x9F, 0xA2, 0xA3. */
#define PLAYER_NAME(i) (func_00328230() != 0 && ((i) == 0xD || (i) == 0x9F || (u32)((i) - 0xA2) < 2))

/* 0x002F2720, 0x60 bytes. Record `i`. */
u8 *func_002F2720(u32 i)
{
    return ofc(i);
}

/* 0x002F2780, 0x48 bytes, matching. The number of record `p`. */
int func_002F2780(u8 *p)
{
    return OFC_NUM(p);
}

/* 0x002F27D0, 0x64 bytes. Record `i`'s officer table record. */
u16 func_002F27D0(u32 i)
{
    return *(u16 *)ofc(i);
}

int func_002F3BB0(u32 i);

/* 0x002F2840, 0x24 bytes, matching. Whether officer `i`'s rank is 2. */
int func_002F2840(u32 i)
{
    return func_002F3BB0(i) == 2;
}

/* 0x002F2870, 0x8 bytes, matching. */
int func_002F2870(void)
{
    return 1;
}

/* 0x002F2880, 0xC bytes, matching. The name buffer. */
char *func_002F2880(void)
{
    return g_007A2CD0;
}

void func_002F2970(u32 i);

/* 0x002F2890, 0xDC bytes. Writes officer `i`'s name and title to the name buffer. */
void func_002F2890(u32 i)
{
    u16 *r;

    if (PLAYER_NAME(i)) {
        func_002F2970(i);
        return;
    }
    r = (u16 *)(g_005BA6A0 + *(u16 *)ofc(i) * 0x2C);
    func_0019B170(g_007A2CD0, r[0], r[1]);
}

/* 0x002F2970, 0x98 bytes. The same with the player's title as 0x17. */
void func_002F2970(u32 i)
{
    u16 *r = (u16 *)(g_005BA6A0 + *(u16 *)ofc(i) * 0x2C);

    func_0019B200(g_007A2CD0, r[0], r[1]);
}

/* 0x002F2A10, 0x1C bytes, matching. */
void func_002F2A10(u32 i)
{
    func_002F2890(i);
}

/* 0x002F2A30, 0x17C bytes. Writes officer `i`'s title (its name when the title is empty). */
void func_002F2A30(u32 i)
{
    u16 *r = (u16 *)(g_005BA6A0 + *(u16 *)ofc(i) * 0x2C);

    if (PLAYER_NAME(i)) {
        func_0019B240(g_007A2CD0, r[0]);
        return;
    }
    if (func_00120A40(func_0019B0E0(g_007A2CD0, r[0])) == 0)
        func_0019B130(g_007A2CD0, r[1]);
    else
        func_0019B0E0(g_007A2CD0, r[0]);
}

/* 0x002F2BB0, 0x94 bytes. Writes officer `i`'s name. */
void func_002F2BB0(u32 i)
{
    func_0019B130(g_007A2CD0, ((u16 *)(g_005BA6A0 + *(u16 *)ofc(i) * 0x2C))[1]);
}

/* 0x002F2C50, 0x150 bytes. Officer `i`'s shown name id (its title, or its name when the title is
 * empty). */
u16 func_002F2C50(u32 i)
{
    u16 *r = (u16 *)(g_005BA6A0 + *(u16 *)ofc(i) * 0x2C);

    if (PLAYER_NAME(i))
        return r[0];
    if (func_00120A40(func_0019B0E0(g_007A2CD0, r[0])) == 0)
        return r[1];
    return r[0];
}

/* 0x002F2DA0, 0x80 bytes. Officer `i`'s +0xA (a created officer's number itself). */
u32 func_002F2DA0(u32 i)
{
    if (CREATED(i))
        return i;
    return *(u16 *)(ofc(i) + 0xA);
}

/* 0x002F2E20, 0x80 bytes. Officer `i`'s +0xC (0x19F for created officers). */
u16 func_002F2E20(u32 i)
{
    if (CREATED(i))
        return 0x19F;
    return *(u16 *)(ofc(i) + 0xC);
}

/* 0x002F2EA0, 0x98 bytes. Officer `i`'s kind (+0x12, or from a created officer's look). */
u32 func_002F2EA0(u32 i)
{
    if (CREATED(i))
        return g_00446410[func_0039E7C0(i - 400)];
    return ofc(i)[0x12];
}

/* 0x002F2F40, 0x94 bytes. Officer `i`'s +0xE (for created officers from the calendar). */
u32 func_002F2F40(u32 i)
{
    if (CREATED(i))
        return func_00327140(func_00327C00(), 0);
    return *(u16 *)(ofc(i) + 0xE);
}

/* 0x002F2FE0, 0x88 bytes. Officer `i`'s +0x10 (created: +0xE less 15). */
u32 func_002F2FE0(u32 i)
{
    if (CREATED(i))
        return func_002F2F40(i) - 0xF;
    return *(u16 *)(ofc(i) + 0x10);
}

/* 0x002F3070, 0x94 bytes. Officer `i`'s face (+0x42; created: its look mod 25). */
u32 func_002F3070(u32 i)
{
    if (CREATED(i))
        return func_0039E760(i - 400) % 0x19;
    return *(u16 *)(ofc(i) + 0x42);
}

/* 0x002F3110, 0xD8 bytes. Officer `i`'s value `k` of three (+0x44). */
u32 func_002F3110(u32 i, int k)
{
    if (k < 0 || k > 2)
        return 0;
    if (CREATED(i))
        return g_004141D0[func_0039E7C0(i - 400)][k];
    return ofc(i)[0x44 + k];
}

/* 0x002F31F0, 0xF8 bytes. Officer `i`'s group (+0x47; created: by weapon 0x2B-0x32). */
u8 func_002F31F0(u32 i)
{
    if (!CREATED(i))
        return ofc(i)[0x47];
    switch (func_0039E740(i - 400)) {
    case 0x2B: return 0;
    case 0x2C: return 1;
    case 0x2D: return 2;
    case 0x2E: return 1;
    case 0x2F: return 0;
    case 0x30: return 2;
    case 0x31: return 1;
    case 0x32: return 1;
    }
    return 0;
}

/* 0x002F32F0, 0x8C bytes. Sets officer `i`'s +0x48 (below 0x10000). */
u32 func_002F32F0(u32 i, u32 v)
{
    if (v >= 0x10000)
        return 0;
    *(short *)(ofc(i) + 0x48) = (short)v;
    return v;
}

/* 0x002F3380, 0x64 bytes. */
u16 func_002F3380(u32 i)
{
    return *(u16 *)(ofc(i) + 0x48);
}

/* 0x002F33F0, 0x4C bytes. How far officer `i`'s +0x48 is below func_00327C70. */
int func_002F33F0(u32 i)
{
    int v = func_002F3380(i);

    return v < func_00327C70() ? func_00327C70() - v : 0;
}

/* 0x002F3440, 0x98 bytes. Sets officer `i`'s experience (0-99999, else 0). */
int func_002F3440(u32 i, int e)
{
    if (e < 0 || e > 99999)
        return 0;
    *(int *)(ofc(i) + 0x98) = e;
    return e;
}

/* 0x002F34E0, 0x64 bytes. */
u32 func_002F34E0(u32 i)
{
    return *(u32 *)(ofc(i) + 0x98);
}

/* 0x002F3550, 0x68 bytes. Adds `n` to officer `i`'s experience (up to 99999). */
void func_002F3550(u32 i, int n)
{
    func_002F3440(i, n + (int)func_002F34E0(i) < 100000 ? n + (int)func_002F34E0(i) : 99999);
}

int func_002F38C0(u8 *p);

/* 0x002F35C0, 0x9C bytes. Sets record `p`'s soldiers (up to its level's). */
int func_002F35C0(u8 *p, int n)
{
    if ((u32)OFC_NUM(p) < 0x19F && n >= 0 && n <= func_002F38C0(p)) {
        *(short *)(p + 0x4A) = (short)n;
        return n;
    }
    return 0;
}

int func_002F38F0(u32 i);

/* 0x002F3660, 0x9C bytes. Sets officer `i`'s soldiers (at most its level's). */
void func_002F3660(u32 i, int n)
{
    if (func_002F38F0(i) < n)
        n = func_002F38F0(i);
    func_002F35C0(ofc(i), n);
}

/* 0x002F3700, 0x70 bytes. Record `p`'s soldiers. */
u16 func_002F3700(u8 *p)
{
    int k = OFC_NUM(p);

    if (k < 0 || k >= 0x19F)
        return 0;
    return *(u16 *)(p + 0x4A);
}

/* 0x002F3770, 0x64 bytes. */
int func_002F3770(u32 i)
{
    return func_002F3700(ofc(i));
}

/* 0x002F37E0, 0x78 bytes. Adds `n` soldiers to officer `i`. */
void func_002F37E0(u32 i, int n)
{
    if (func_002F38F0(i) < n + func_002F3770(i))
        n = func_002F38F0(i);
    else
        n = n + func_002F3770(i);
    func_002F3660(i, n);
}

/* 0x002F3860, 0x5C bytes. Takes `n` soldiers from officer `i`. */
void func_002F3860(u32 i, int n)
{
    func_002F3660(i, n < func_002F3770(i) ? func_002F3770(i) - n : 0);
}

u8 func_002F41D0(u8 *p);

/* 0x002F38C0, 0x30 bytes. Record `p`'s soldiers for its level. */
int func_002F38C0(u8 *p)
{
    return g_004463E0[func_002F41D0(p)];
}

/* 0x002F38F0, 0x64 bytes. */
int func_002F38F0(u32 i)
{
    return func_002F38C0(ofc(i));
}

/* 0x002F3960, 0x90 bytes. Sets officer `i`'s life (0-350, else 0). */
int func_002F3960(u32 i, int v)
{
    if (v < 0 || v > 0x15E)
        return 0;
    *(short *)(ofc(i) + 0x4C) = (short)v;
    return v;
}

/* 0x002F39F0, 0x64 bytes. */
int func_002F39F0(u32 i)
{
    return *(u16 *)(ofc(i) + 0x4C);
}

/* 0x002F3A60, 0x8C bytes. Adds `n` to officer `i`'s life (up to its maximum, 350 with
 * func_002F59A0). */
void func_002F3A60(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F5D30(i) : 0x15E;

    if (n + func_002F39F0(i) <= m)
        m = n + func_002F39F0(i);
    func_002F3960(i, m);
}

/* 0x002F3AF0, 0x38 bytes. Sets record `p`'s rank (0-3, keeping bit 7). */
void func_002F3AF0(u8 *p, int r)
{
    if (r >= 0 && r < 4)
        p[0x50] = (p[0x50] & 0x80) | (u8)r;
}

/* 0x002F3B30, 0x70 bytes. */
void func_002F3B30(u32 i, int r)
{
    func_002F3AF0(ofc(i), r);
}

/* 0x002F3BA0, 0xC bytes, matching. Record `p`'s rank. */
u8 func_002F3BA0(u8 *p)
{
    return p[0x50] & 0x7F;
}

/* 0x002F3BB0, 0x64 bytes. */
int func_002F3BB0(u32 i)
{
    return func_002F3BA0(ofc(i));
}

/* 0x002F3C20, 0xC bytes. Record `p`'s bit 7. */
u8 func_002F3C20(u8 *p)
{
    return p[0x50] & 0x80;
}

/* 0x002F3C30, 0xB8 bytes. Sets officer `i`'s bit 7. */
void func_002F3C30(u32 i)
{
    u8 b = ofc(i)[0x50];

    ofc(i)[0x50] = b | 0x80;
}

int func_002F3F20(u32 i);

/* 0x002F3CF0, 0xB4 bytes. Sets officer `i`'s role (0-5; not 1 for func_002F3F20 officers). */
void func_002F3CF0(u32 i, int r)
{
    if (((r >= 0 && r < 4) || r == 4 || r == 5) && (r != 1 || func_002F3F20(i) == 0))
        ofc(i)[0x51] = (u8)r;
}

/* 0x002F3DB0, 0x8 bytes, matching. */
u8 func_002F3DB0(u8 *p)
{
    return p[0x51];
}

/* 0x002F3DC0, 0x64 bytes. */
int func_002F3DC0(u32 i)
{
    return func_002F3DB0(ofc(i));
}

/* 0x002F3E30, 0x34 bytes. Officer `i`'s side of the role (roles 0-1: 1, others 2). */
int func_002F3E30(u32 i)
{
    return func_002F3DC0(i) < 2 ? 1 : 2;
}

/* 0x002F3E70, 0x44 bytes, matching. Whether officer `i`'s role is 3 or 5. */
int func_002F3E70(u32 i)
{
    return func_002F3DC0(i) == 3 || func_002F3DC0(i) == 5;
}

/* 0x002F3EC0, 0x24 bytes, matching. */
int func_002F3EC0(u32 i)
{
    return func_002F3E30(i) == 2;
}

/* 0x002F3EF0, 0x24 bytes, matching. */
int func_002F3EF0(u32 i)
{
    return func_002F3E30(i) == 1;
}

/* 0x002F3F20, 0x48 bytes. Whether officer `i` is a named one (below 0x1C), a created one or of
 * role 3 / 5. */
int func_002F3F20(u32 i)
{
    if ((int)i < 0x1C || CREATED(i))
        return 1;
    return func_002F3E70(i) != 0;
}

/* 0x002F3F70, 0xA0 bytes. Sets officer `i`'s force (below func_0030AB90, or 0x19 none). */
void func_002F3F70(u32 i, int f)
{
    int ok = 0;

    if (f >= 0)
        ok = f < func_0030AB90();
    if (!ok)
        ok = f == 0x19;
    if (ok)
        ofc(i)[0x52] = (u8)f;
}

/* 0x002F4010, 0x70 bytes. Record `p`'s force (0x19 for none). */
u8 func_002F4010(u8 *p)
{
    int k = OFC_NUM(p);

    if (k < 0 || k >= 0x19F)
        return 0x19;
    return p[0x52];
}

/* 0x002F4080, 0x64 bytes. */
int func_002F4080(u32 i)
{
    return func_002F4010(ofc(i));
}

int func_002F41E0(u32 i);

/* 0x002F40F0, 0xD8 bytes. Sets officer `i`'s level (0-19); a lower level cuts its soldiers. */
void func_002F40F0(u32 i, int lv)
{
    int old = func_002F41E0(i);

    if (lv >= 0 && lv < 0x14) {
        ofc(i)[0x54] = (u8)lv;
        if (lv != old && func_002F38F0(i) < func_002F3770(i))
            func_002F3660(i, func_002F38F0(i));
    }
}

/* 0x002F41D0, 0x8 bytes, matching. */
u8 func_002F41D0(u8 *p)
{
    return p[0x54];
}

/* 0x002F41E0, 0x64 bytes. */
int func_002F41E0(u32 i)
{
    return func_002F41D0(ofc(i));
}

/* GENERATED */
/* PROTOS */
int func_002F42E0(u8 *p);
int func_002F42F0(u32 i);
void func_002F4360(u32 i, int n);
int func_002F4450(u32 i);
void func_002F44C0(u32 i);
int func_002F45A0(u32 i);
void func_002F4610(u32 i);
int func_002F4660(u32 i);
void func_002F46D0(u32 i, int v);
void func_002F4760(u32 i, int n);
void func_002F4B70(u32 i, int n);
int func_002F4BB0(u32 i, int v);
int func_002F4C40(u32 i);
void func_002F4CB0(u32 i, int n);
int func_002F4D40(u32 i, int v);
int func_002F4DD0(u32 i);
void func_002F4E40(u32 i, int n);
int func_002F4ED0(u32 i, int v);
int func_002F4F60(u32 i);
void func_002F4FD0(u32 i, int n);
int func_002F5060(u32 i, int v);
int func_002F50F0(u32 i);
void func_002F5160(u32 i, int n);
int func_002F51F0(u32 i, int v);
int func_002F5280(u32 i);
void func_002F52F0(u32 i, int n);
int func_002F5380(u32 i, int v);
int func_002F5410(u32 i);
void func_002F5480(u32 i, int n);
int func_002F5510(u32 i, int v);
int func_002F55A0(u32 i);
void func_002F5610(u32 i, int n);
int func_002F5730(u32 i);
void func_002F5930(u32 i, int v);
void func_002F5A10(u32 i, int v);
int func_002F5AA0(u32 i);
void func_002F5DA0(u32 i, int v);
int func_002F5E10(u32 i);
int func_002F5E80(u32 i);
void func_002F5EF0(u32 i, int v);
int func_002F5F60(u32 i);
int func_002F5FD0(u32 i);
void func_002F6040(u32 i, int v);
int func_002F60B0(u32 i);
int func_002F6120(u32 i);
void func_002F6190(u32 i, int v);
int func_002F6200(u32 i);
int func_002F6270(u32 i);
void func_002F62E0(u32 i, int v);
int func_002F6350(u32 i);
int func_002F63C0(u32 i);
void func_002F6430(u32 i, int v);
int func_002F64A0(u32 i);
int func_002F6510(u32 i);
void func_002F6580(u32 i, int v);
int func_002F65F0(u32 i);
int func_002F6660(u32 i);
void func_002F66D0(u32 i, int v);
int func_002F6740(u32 i);
int func_002F6980(u32 i);
void func_002F69F0(u32 i, int v);
int func_002F6A60(u32 i);
void func_002F6AD0(u32 i, int v);
int func_002F6B40(u32 i);
void func_002F90D0(u32 i, int n);
void func_0030AE40(u32 i, int n);
int func_002F47A0(u32 i, int k);
void func_002F4820(u32 i, int k, u8 lv);
int func_002F4900(u32 i, int k);
void func_002F4980(u32 i, int k, int on);
int func_002F57A0(u32 w);
int func_002F57F0(u8 w);
int func_002F5840(int g);
int func_002F5890(u32 i);
void func_002F5B30(u8 *p, int f);
int func_002F5C50(u8 *p);
int func_002F67B0(u32 i);
int func_002F6850(u32 i);
int func_002F68E0(u32 i);
void func_002F6BB0(u32 i, u16 v);
int func_002F6FE0(u32 i, int k);
int func_002F7040(u32 i, int k);
void func_002F70A0(u32 i, int to, int from);
int func_002F7160(u32 i);
void func_002F7200(u32 i);
void func_002F7270(u32 i);
void func_002F7290(u32 i);
int func_002F72E0(u32 lv);
void func_002F7300(u32 i, int f, int f2, int role);
void func_002F7410(u32 i);
int func_002F7550(u32 i);
int func_002F75C0(u32 i);
void func_002F7610(u32 i);
int func_002F76B0(u32 i, u32 j);
int func_002F77A0(u32 i, u32 j);
int func_002F77F0(u32 i, u32 j);
int func_002F78C0(u32 i, u32 j);
int func_002F7900(u32 i, u32 j);
int func_002F7AD0(u32 i, u32 j, u32 a, u32 b);
u32 *func_002F7B10(void);
void func_002F7B20(int a, u32 *l, int n);
void func_002F7C40(u32 *l, int n);
int func_002F7CE0(u32 i, u32 j);
int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort, int p5);
int func_002F7EC0(u32 i, int f);
int func_002F7F80(u32 i, int f);
int func_002F8020(u32 i, int f);
int func_002F8070(u32 i, int f);
int func_002F80C0(u32 i, int f);
int func_002F8110(u32 i, int f);
int func_002F8160(u32 i, int f);
int func_002F8200(u32 i, int f, u32 x);
int func_002F8250(u32 i, int f);
int func_002F82A0(u32 i, int f);
int func_002F82F0(u32 i, int f);
int func_002F8340(u32 i, int f);
int func_002F8390(u32 i, int f);
int func_002F8430(u32 i, int f);
int func_002F8480(u32 i);
int func_002F8500(u32 i, int f);
int func_002F8570(u32 i);
int func_002F85E0(u32 i);
int func_002F8630(u32 i, int r);
int func_002F86B0(u32 i, int f);
int func_002F8710(u32 i);
int func_002F8740(u32 i, int r);
int func_002F87A0(u32 i);
int func_002F8900(u32 i, u32 j);
int func_0016CC80(u8 w);
int func_0039E7A0(int k);
u8 *func_0019FBA0(int k);
int func_0019C170(u32 id, u32 level, int learn);
int func_002FB2A0(u32 f);
void func_00328A00(u32 i, int a);
int func_00327C40(void);
void func_00308600(u32 i);
int func_0030AD20(int f, int k);
int func_0030CB00(int n);
int func_00327C80(void);
int func_00327A60(void);
int func_00328270(void);
void func_00328240(int v);
int func_003282C0(void);
int func_0030AFF0(int f);
int func_0030B2F0(int f);
int func_002F8F90();
int func_002F9060();
int func_0030AD80();
int func_0030ADC0();
/* END PROTOS */

/* 0x002F4250, 0x90 bytes. */
int func_002F4250(u32 i, int v)
{
    if (v < 0 || v > 0xFF)
        return 0;
    *(u8 *)(ofc(i) + 0x55) = (u8)v;
    return v;
}

/* 0x002F42E0, 0x8 bytes, matching. */
int func_002F42E0(u8 *p)
{
    return *(u8 *)(p + 0x55);
}

/* 0x002F42F0, 0x64 bytes. */
int func_002F42F0(u32 i)
{
    return func_002F42E0(ofc(i));
}

/* 0x002F4360, 0x5C bytes, matching. */
void func_002F4360(u32 i, int n)
{
    func_002F4250(i, n + func_002F42F0(i) < 0xFF ? n + func_002F42F0(i) : 0xFF);
}

/* 0x002F43C0, 0x90 bytes. */
int func_002F43C0(u32 i, int v)
{
    if (v < 0 || v > 0x5)
        return 0;
    *(u8 *)(ofc(i) + 0x56) = (u8)v;
    return v;
}

/* 0x002F4450, 0x64 bytes. */
int func_002F4450(u32 i)
{
    return *(u8 *)(ofc(i) + 0x56);
}

/* 0x002F44C0, 0x50 bytes. */
void func_002F44C0(u32 i)
{
    int v = func_002F4450(i);

    func_002F43C0(i, v < 0x5 ? v + 1 : 0x1);
}

/* 0x002F4510, 0x90 bytes. */
int func_002F4510(u32 i, int v)
{
    if (v < 0 || v > 0x5)
        return 0;
    *(u8 *)(ofc(i) + 0x57) = (u8)v;
    return v;
}

/* 0x002F45A0, 0x64 bytes. */
int func_002F45A0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x57);
}

/* 0x002F4610, 0x50 bytes. */
void func_002F4610(u32 i)
{
    int v = func_002F45A0(i);

    func_002F4510(i, v < 0x5 ? v + 1 : 0x1);
}

/* 0x002F4660, 0x64 bytes. */
int func_002F4660(u32 i)
{
    return *(u8 *)(ofc(i) + 0x58);
}

/* 0x002F46D0, 0x88 bytes. */
void func_002F46D0(u32 i, int v)
{
    if (v > 0x64)
        v = 0x64;
    if (v < 1)
        v = 0;
    *(u8 *)(ofc(i) + 0x58) = (u8)v;
}

/* 0x002F4760, 0x3C bytes, matching. */
void func_002F4760(u32 i, int n)
{
    func_002F46D0(i, n + func_002F4660(i));
}

/* 0x002F4A70, 0x64 bytes. */
int func_002F4A70(u32 i)
{
    return *(u8 *)(ofc(i) + 0x97);
}

/* 0x002F4AE0, 0x88 bytes. */
void func_002F4AE0(u32 i, int v)
{
    if (v > 0x7)
        v = 0x7;
    if (v < 1)
        v = 0;
    *(u8 *)(ofc(i) + 0x97) = (u8)v;
}

/* 0x002F4B70, 0x3C bytes, matching. */
void func_002F4B70(u32 i, int n)
{
    func_002F4AE0(i, n + func_002F4A70(i));
}

/* 0x002F4BB0, 0x90 bytes. */
int func_002F4BB0(u32 i, int v)
{
    if (v < 0 || v > 0x15E)
        return 0;
    *(short *)(ofc(i) + 0x4E) = (short)v;
    return v;
}

/* 0x002F4C40, 0x64 bytes. */
int func_002F4C40(u32 i)
{
    return *(u16 *)(ofc(i) + 0x4E);
}

/* 0x002F4CB0, 0x8C bytes. */
void func_002F4CB0(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F5E80(i) : 0x15E;

    if (n + func_002F4C40(i) <= m)
        m = n + func_002F4C40(i);
    func_002F4BB0(i, m);
}

/* 0x002F4D40, 0x90 bytes. */
int func_002F4D40(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x59) = (u8)v;
    return v;
}

/* 0x002F4DD0, 0x64 bytes. */
int func_002F4DD0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x59);
}

/* 0x002F4E40, 0x8C bytes. */
void func_002F4E40(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F5FD0(i) : 0xFA;

    if (n + func_002F4DD0(i) <= m)
        m = n + func_002F4DD0(i);
    func_002F4D40(i, m);
}

/* 0x002F4ED0, 0x90 bytes. */
int func_002F4ED0(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x5A) = (u8)v;
    return v;
}

/* 0x002F4F60, 0x64 bytes. */
int func_002F4F60(u32 i)
{
    return *(u8 *)(ofc(i) + 0x5A);
}

/* 0x002F4FD0, 0x8C bytes. */
void func_002F4FD0(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F6120(i) : 0xFA;

    if (n + func_002F4F60(i) <= m)
        m = n + func_002F4F60(i);
    func_002F4ED0(i, m);
}

/* 0x002F5060, 0x90 bytes. */
int func_002F5060(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x5B) = (u8)v;
    return v;
}

/* 0x002F50F0, 0x64 bytes. */
int func_002F50F0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x5B);
}

/* 0x002F5160, 0x8C bytes. */
void func_002F5160(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F6270(i) : 0xFA;

    if (n + func_002F50F0(i) <= m)
        m = n + func_002F50F0(i);
    func_002F5060(i, m);
}

/* 0x002F51F0, 0x90 bytes. */
int func_002F51F0(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x5C) = (u8)v;
    return v;
}

/* 0x002F5280, 0x64 bytes. */
int func_002F5280(u32 i)
{
    return *(u8 *)(ofc(i) + 0x5C);
}

/* 0x002F52F0, 0x8C bytes. */
void func_002F52F0(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F63C0(i) : 0xFA;

    if (n + func_002F5280(i) <= m)
        m = n + func_002F5280(i);
    func_002F51F0(i, m);
}

/* 0x002F5380, 0x90 bytes. */
int func_002F5380(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x5D) = (u8)v;
    return v;
}

/* 0x002F5410, 0x64 bytes. */
int func_002F5410(u32 i)
{
    return *(u8 *)(ofc(i) + 0x5D);
}

/* 0x002F5480, 0x8C bytes. */
void func_002F5480(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F6510(i) : 0xFA;

    if (n + func_002F5410(i) <= m)
        m = n + func_002F5410(i);
    func_002F5380(i, m);
}

/* 0x002F5510, 0x90 bytes. */
int func_002F5510(u32 i, int v)
{
    if (v < 0 || v > 0xFA)
        return 0;
    *(u8 *)(ofc(i) + 0x5E) = (u8)v;
    return v;
}

/* 0x002F55A0, 0x64 bytes. */
int func_002F55A0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x5E);
}

/* 0x002F5610, 0x8C bytes. */
void func_002F5610(u32 i, int n)
{
    int m = func_002F59A0(i) == 0 ? func_002F6660(i) : 0xFA;

    if (n + func_002F55A0(i) <= m)
        m = n + func_002F55A0(i);
    func_002F5510(i, m);
}

/* 0x002F56A0, 0x8C bytes. */
void func_002F56A0(u32 i, int v)
{
    if (v >= 0 && v < 0x4)
        *(u8 *)(ofc(i) + 0x94) = (u8)v;
}

/* 0x002F5730, 0x64 bytes. */
int func_002F5730(u32 i)
{
    return *(u8 *)(ofc(i) + 0x94);
}

/* 0x002F5930, 0x6C bytes. */
void func_002F5930(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x95) = (u8)v;
}

/* 0x002F59A0, 0x64 bytes. */
int func_002F59A0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x95);
}

/* 0x002F5A10, 0x8C bytes. */
void func_002F5A10(u32 i, int v)
{
    if (v >= 0 && v < 0x5)
        *(u8 *)(ofc(i) + 0x96) = (u8)v;
}

/* 0x002F5AA0, 0x84 bytes. */
int func_002F5AA0(u32 i)
{
    if (CREATED(i))
        return func_0039E7A0(i - 400);
    return *(u8 *)(ofc(i) + 0x96);
}

/* 0x002F5BE0, 0x70 bytes. */
void func_002F5BE0(u32 i, int v)
{
    func_002F5B30(ofc(i), v);
}

/* 0x002F5CC0, 0x64 bytes. */
int func_002F5CC0(u32 i)
{
    return func_002F5C50(ofc(i));
}

/* 0x002F5D30, 0x64 bytes. */
int func_002F5D30(u32 i)
{
    return *(u16 *)(ofc(i) + 0x2);
}

/* 0x002F5DA0, 0x6C bytes. */
void func_002F5DA0(u32 i, int v)
{
    *(short *)(ofc(i) + 0x2) = (short)v;
}

/* 0x002F5E10, 0x64 bytes. */
int func_002F5E10(u32 i)
{
    return *(u16 *)(ofc(i) + 0x4);
}

/* 0x002F5E80, 0x64 bytes. */
int func_002F5E80(u32 i)
{
    return *(u16 *)(ofc(i) + 0x6);
}

/* 0x002F5EF0, 0x6C bytes. */
void func_002F5EF0(u32 i, int v)
{
    *(short *)(ofc(i) + 0x6) = (short)v;
}

/* 0x002F5F60, 0x64 bytes. */
int func_002F5F60(u32 i)
{
    return *(u16 *)(ofc(i) + 0x8);
}

/* 0x002F5FD0, 0x64 bytes. */
int func_002F5FD0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x17);
}

/* 0x002F6040, 0x6C bytes. */
void func_002F6040(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x17) = (u8)v;
}

/* 0x002F60B0, 0x64 bytes. */
int func_002F60B0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x18);
}

/* 0x002F6120, 0x64 bytes. */
int func_002F6120(u32 i)
{
    return *(u8 *)(ofc(i) + 0x19);
}

/* 0x002F6190, 0x6C bytes. */
void func_002F6190(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x19) = (u8)v;
}

/* 0x002F6200, 0x64 bytes. */
int func_002F6200(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1A);
}

/* 0x002F6270, 0x64 bytes. */
int func_002F6270(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1B);
}

/* 0x002F62E0, 0x6C bytes. */
void func_002F62E0(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x1B) = (u8)v;
}

/* 0x002F6350, 0x64 bytes. */
int func_002F6350(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1C);
}

/* 0x002F63C0, 0x64 bytes. */
int func_002F63C0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1D);
}

/* 0x002F6430, 0x6C bytes. */
void func_002F6430(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x1D) = (u8)v;
}

/* 0x002F64A0, 0x64 bytes. */
int func_002F64A0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1E);
}

/* 0x002F6510, 0x64 bytes. */
int func_002F6510(u32 i)
{
    return *(u8 *)(ofc(i) + 0x1F);
}

/* 0x002F6580, 0x6C bytes. */
void func_002F6580(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x1F) = (u8)v;
}

/* 0x002F65F0, 0x64 bytes. */
int func_002F65F0(u32 i)
{
    return *(u8 *)(ofc(i) + 0x20);
}

/* 0x002F6660, 0x64 bytes. */
int func_002F6660(u32 i)
{
    return *(u8 *)(ofc(i) + 0x21);
}

/* 0x002F66D0, 0x6C bytes. */
void func_002F66D0(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x21) = (u8)v;
}

/* 0x002F6740, 0x64 bytes. */
int func_002F6740(u32 i)
{
    return *(u8 *)(ofc(i) + 0x22);
}

/* 0x002F6980, 0x64 bytes. */
int func_002F6980(u32 i)
{
    return *(u8 *)(ofc(i) + 0x16);
}

/* 0x002F69F0, 0x6C bytes. */
void func_002F69F0(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x16) = (u8)v;
}

/* 0x002F6A60, 0x64 bytes. */
int func_002F6A60(u32 i)
{
    return *(u8 *)(ofc(i) + 0x3F);
}

/* 0x002F6AD0, 0x6C bytes. */
void func_002F6AD0(u32 i, int v)
{
    *(u8 *)(ofc(i) + 0x3F) = (u8)v;
}

/* 0x002F6B40, 0x64 bytes. */
int func_002F6B40(u32 i)
{
    return *(u16 *)(ofc(i) + 0x40);
}

/* 0x002F90D0, 0x60 bytes, matching. */
void func_002F90D0(u32 i, int n)
{
    func_002F8F90(i, n + func_002F9060(i) < 0xEA60 ? n + func_002F9060(i) : 0xEA60);
}

/* 0x0030AE40, 0x3C bytes, matching. */
void func_0030AE40(u32 i, int n)
{
    func_0030ADC0(i, n + func_0030AD80(i));
}


extern u32 g_00446450[];
extern u32 g_00414230[][3], g_004142F0[][8];
extern u32 g_00428348[0x14];             /* the experience needed per level */
extern int g_004144F0[];
extern u32 g_00414510[0xE][2];           /* pairs of related groups */

/* 0x002F47A0, 0x74 bytes. Officer `i`'s level of skill `k` (+0x5F + k, bits 0-6). */
int func_002F47A0(u32 i, int k)
{
    return ofc(i)[0x5F + k] & 0x7F;
}

/* 0x002F4820, 0xE0 bytes. Sets it (keeping bit 7). */
void func_002F4820(u32 i, int k, u8 lv)
{
    u8 b = ofc(i)[0x5F + k];

    ofc(i)[0x5F + k] = (b & 0x80) | lv;
}

/* 0x002F4900, 0x74 bytes. Skill `k`'s bit 7 (learnt in battle?). */
int func_002F4900(u32 i, int k)
{
    return ofc(i)[0x5F + k] & 0x80;
}

/* 0x002F4980, 0xE4 bytes. Sets or clears skill `k`'s bit 7. */
void func_002F4980(u32 i, int k, int on)
{
    u8 b = ofc(i)[0x5F + k];

    ofc(i)[0x5F + k] = on == 0 ? b & 0x7F : b | 0x80;
}

/* 0x002F57A0, 0x4C bytes. A weapon's group (below 0x74: weapon / 4; 0x74-0x77: 0x1E; 0x78:
 * 0x1D; else 0x28). */
int func_002F57A0(u32 w)
{
    w &= 0xFF;
    if (w < 0x74)
        return w >> 2;
    if (w < 0x78)
        return 0x1E;
    if (w == 0x78)
        return 0x1D;
    return 0x28;
}

/* 0x002F57F0, 0x4C bytes. A weapon's grade (0-3). */
int func_002F57F0(u8 w)
{
    if (w < 0x78)
        return w & 3;
    return w == 0x78 ? 3 : 0;
}

/* 0x002F5840, 0x50 bytes. The number of attributes a weapon grade allows. */
int func_002F5840(int g)
{
    if (g == 3)
        return 8;
    if (g == 2)
        return 6;
    if (g == 1)
        return 4;
    if (g == 0)
        return 2;
    return 8;
}

int func_0016CC80(u8 w);

/* 0x002F5890, 0x94 bytes. Officer `i`'s weapon group. */
int func_002F5890(u32 i)
{
    return func_002F57A0(func_0016CC80(g_005BA6A0[*(u16 *)ofc(i) * 0x2C + 9]));
}

/* 0x002F5B30, 0xB0 bytes. Sets record `p`'s second force (+0x53; a force or 0x19). */
void func_002F5B30(u8 *p, int f)
{
    if ((u32)OFC_NUM(p) < 0x19F) {
        int ok = 0;

        if (f >= 0)
            ok = f < func_0030AB90();
        if (!ok)
            ok = f == 0x19;
        if (ok)
            p[0x53] = (u8)f;
    }
}

/* 0x002F5C50, 0x70 bytes. Record `p`'s second force (0x19 for none). */
int func_002F5C50(u8 *p)
{
    int k = OFC_NUM(p);

    if (k < 0 || k >= 0x19F)
        return 0x19;
    return p[0x53];
}

int func_0039E7A0(int k);
u8 *func_0019FBA0(int k);

/* 0x002F67B0, 0x98 bytes. Officer `i`'s +0x13 (created: from their look). */
int func_002F67B0(u32 i)
{
    if (CREATED(i))
        return g_00446450[func_0039E7C0(i - 400)];
    return ofc(i)[0x13];
}

/* 0x002F6850, 0x84 bytes. Officer `i`'s +0x14 (created: their record's +0x2E). */
int func_002F6850(u32 i)
{
    if (CREATED(i))
        return func_0019FBA0(i - 400)[0x2E];
    return ofc(i)[0x14];
}

/* 0x002F68E0, 0x98 bytes. Officer `i`'s +0x15 (created: their look's low two bits). */
int func_002F68E0(u32 i)
{
    if (CREATED(i))
        return func_0039E760(i - 400) % 4;
    return ofc(i)[0x15];
}

/* 0x002F6BB0, 0x70 bytes. */
void func_002F6BB0(u32 i, u16 v)
{
    *(u16 *)(ofc(i) + 0x40) = v & 0xFF;
}

/* Officer `i`'s byte `k` of a small array at `off`. */
#define ARR_GET(name, off) int name(u32 i, int k) { return ofc(i)[(off) + k]; }
#define ARR_SET(name, off) void name(u32 i, int k, u8 v) { ofc(i)[(off) + k] = v; }

/* 0x002F6C20, 0x70 bytes. */
ARR_GET(func_002F6C20, 0x23)

/* 0x002F6C90, 0x7C bytes. */
ARR_SET(func_002F6C90, 0x23)

/* 0x002F6D10, 0x70 bytes. */
ARR_GET(func_002F6D10, 0x27)

/* 0x002F6D80, 0x7C bytes. */
ARR_SET(func_002F6D80, 0x27)

/* 0x002F6E00, 0x70 bytes. */
ARR_GET(func_002F6E00, 0x2B)

/* 0x002F6E70, 0x7C bytes. */
ARR_SET(func_002F6E70, 0x2B)

/* 0x002F6EF0, 0x70 bytes. */
ARR_GET(func_002F6EF0, 0x35)

/* 0x002F6F60, 0x7C bytes. */
ARR_SET(func_002F6F60, 0x35)

/* 0x002F6FE0, 0x60 bytes, matching. Officer `i`'s kind's value `k` of three. */
int func_002F6FE0(u32 i, int k)
{
    if (k >= 3)
        return 0;
    return g_00414230[func_002F2EA0(i)][k];
}

/* 0x002F7040, 0x58 bytes, matching. Officer `i`'s kind's stat growth `k` of eight. */
int func_002F7040(u32 i, int k)
{
    if (k >= 8)
        return 0;
    return g_004142F0[func_002F2EA0(i)][k];
}

int func_0019C170(u32 id, u32 level, int learn);
int func_002FB2A0(u32 f);
void func_00328A00(u32 i, int a);

/* 0x002F70A0, 0xB8 bytes. Officer `i` goes from level `from` to `to` (each level's growth); a
 * named officer past level 9 of a force that allows it gets flag 1 (func_00328A00). */
void func_002F70A0(u32 i, int to, int from)
{
    int k;

    for (k = 0; k < to - from; k++)
        func_0019C170(i, (from + k + 1) & 0xFF, 1);
    if ((int)i < 0x1C && func_002F41E0(i) > 9 && func_002FB2A0(func_002F4080(i)) != 0)
        func_00328A00(i, 1);
}

int func_00327C40(void);

/* 0x002F7160, 0x98 bytes. Officer `i`'s pay (rounded to 10): 500 + 150 x (level / 4 + the
 * year's) for named officers below 0x2C, 400 + 100 x for the others. */
int func_002F7160(u32 i)
{
    int base = 400, step = 100;

    if ((int)i < 0x2C) {
        base = 500;
        step = 0x96;
    }
    return (base + step * ((func_002F41E0(i) >> 2) + g_004144F0[func_00327C40()])) / 10 * 10;
}

int func_002F4250(u32 i, int v);
int func_002F43C0(u32 i, int v);
int func_002F4510(u32 i, int v);
void func_002F56A0(u32 i, int v);
void func_002F4AE0(u32 i, int v);

/* 0x002F7200, 0x6C bytes, matching. Clears officer `i`'s counters (+0x48 to now). */
void func_002F7200(u32 i)
{
    func_002F32F0(i, func_00327C70());
    func_002F4250(i, 0);
    func_002F43C0(i, 0);
    func_002F4510(i, 0);
    func_002F56A0(i, 0);
    func_002F4AE0(i, 0);
}

/* 0x002F7270, 0x1C bytes, matching. Officer `i` loses its soldiers. */
void func_002F7270(u32 i)
{
    func_002F3660(i, 0);
}

/* 0x002F7290, 0x48 bytes, matching. Officer `i` becomes free (rank 2, role 0, no force). */
void func_002F7290(u32 i)
{
    func_002F3B30(i, 2);
    func_002F3CF0(i, 0);
    func_002F3F70(i, 0x19);
    func_002F7200(i);
}

/* 0x002F72E0, 0x1C bytes. The experience of level `lv`. */
int func_002F72E0(u32 lv)
{
    return g_00428348[lv & 0xFF];
}

void func_002F5BE0(u32 i, int f);
void func_00308600(u32 i);

/* 0x002F7300, 0x108 bytes. Officer `i` joins force `f` (second force `f2`, role `role`): rank
 * 2, experience of its level. */
void func_002F7300(u32 i, int f, int f2, int role)
{
    int ok;

    func_002F3B30(i, 2);
    func_002F3440(i, func_002F72E0(func_002F41E0(i)));
    if (role >= 0 && role < 6)
        func_002F3CF0(i, role);
    ok = 0;
    if (f >= 0)
        ok = f < func_0030AB90();
    if (ok)
        func_002F3F70(i, f);
    ok = 0;
    if (f2 >= 0)
        ok = f2 < func_0030AB90();
    if (!ok)
        ok = f2 == 0x19;
    if (ok)
        func_002F5BE0(i, f2);
    func_002F7200(i);
    func_00308600(i);
}

int func_002F5CC0(u32 i);
int func_0030AD20(int f, int k);
int func_0030CB00(int n);

/* 0x002F7410, 0x138 bytes. Officer `i` leaves its force: free, its second force becomes one of
 * its old force's neighbours (or any force) at random. */
void func_002F7410(u32 i)
{
    int near[8], n = 0, k, f;
    int old;

    func_002F3CF0(i, 0);
    func_002F3F70(i, 0x19);
    old = func_002F5CC0(i);
    if (old >= 0 && old < func_0030AB90()) {
        for (k = 0; k < 6; k++) {
            int g = func_0030AD20(old, k);

            if (g >= 0 && g < func_0030AB90())
                near[n++] = g;
        }
        f = near[func_0030CB00(n)];
    } else {
        f = func_0030CB00(func_0030AB90());
    }
    func_002F5BE0(i, f);
    func_002F7200(i);
    func_002F7270(i);
    func_00308600(i);
}

int func_00327C80(void);
int func_00327A60(void);

/* 0x002F7550, 0x68 bytes, matching. Officer `i`'s age (at most 100). */
int func_002F7550(u32 i)
{
    if ((u32)(func_00327C80() - func_002F2FE0(i)) < 100)
        return func_00327C80() - func_002F2FE0(i);
    return 100;
}

/* 0x002F75C0, 0x44 bytes. Whether officer `i` is old enough to die (ages on, 100). */
int func_002F75C0(u32 i)
{
    if (func_00327A60() == 0)
        return 0;
    return func_002F7550(i) > 99;
}

int func_00328270(void);
void func_00328240(int v);

/* 0x002F7610, 0xA0 bytes, matching. Officer `i` dies (rank 3, no force; officers 0x12 and 0x1B move the
 * story on). */
void func_002F7610(u32 i)
{
    func_002F3B30(i, 3);
    func_002F3F70(i, 0x19);
    func_002F5BE0(i, 0x19);
    func_00308600(i);
    if (i == 0x12 && func_00328270() == 1)
        func_00328240(2);
    if (i == 0x1B && func_00328270() == 3)
        func_00328240(4);
    func_002F3C30(i);
}


/* 0x002F76B0, 0xEC bytes. The kind of officer `i`'s next post for officer `j` (2 or 6), from
 * two counts. */
int func_002F76B0(u32 i, u32 j)
{
    int named = func_002F3F20(i) == 0 ? 1 : 2, ok = 0;
    int a = func_002F7D90(0, (int (*)(u32, int, int))func_002F80C0, j, 0, 0, 0);
    int b = func_002F7D90(0, (int (*)(u32, int, int))func_002F8110, j, 0, 0, 0);

    if (named == 2) {
        b = a;
        if (b < 3)
            ok = 1;
    } else if (named == 1 && a < 3) {
        ok = 1;
    }
    return ok ? 2 : 6;
}

/* 0x002F77A0, 0x50 bytes. Whether officers `i` and `j` are each other's +0xC. */
int func_002F77A0(u32 i, u32 j)
{
    return j == func_002F2E20(i) || i == func_002F2E20(j);
}


/* 0x002F77F0, 0xC4 bytes. Whether officers `i` and `j` are related (the same +0xC, or one of 14
 * pairs). */
int func_002F77F0(u32 i, u32 j)
{
    u32 a = func_002F2E20(i);
    int k;

    if (a < 0x19F && a == func_002F2E20(j))
        return 1;
    for (k = 0; k < 0xE; k++) {
        if (func_002F7AD0(i, j, g_00414510[k][0], g_00414510[k][1]) != 0)
            return 1;
    }
    return 0;
}

/* 0x002F78C0, 0x38 bytes, matching. Whether officers `i` and `j` have the same +0xA. */
int func_002F78C0(u32 i, u32 j)
{
    return func_002F2DA0(i) == func_002F2DA0(j);
}

extern u32 g_00414580[9][3];             /* nine groups of three related officers */
extern u32 g_007A2650[];                 /* officer lists */

int func_003282C0(void);
int func_0030AFF0(int f);
int func_0030B2F0(int f);
int func_002F2840(u32 i);
int func_002F4A70(u32 i);

/* 0x002F7900, 0x1C8 bytes. Whether officers `i` and `j` are in one of the nine groups (groups 2
 * to 8 only once the story allows them; 5-8 only when every member has +0x97 at 7). */
int func_002F7900(u32 i, u32 j)
{
    int g, a, b;

    for (g = 0; g <= 8; g++) {
        if (g == 2) {
            if (func_00328270() != 1)
                continue;
        } else if (g == 3) {
            if (func_00328270() != 3)
                continue;
        } else if (g == 4) {
            if (func_003282C0() != 1)
                continue;
        } else if ((u32)(g - 5) < 4) {
            int bad = 0;

            for (a = 0; a < 3; a++) {
                if (g_00414580[g][a] != 0x19F && func_002F4A70(g_00414580[g][a]) != 7) {
                    bad = 1;
                    break;
                }
            }
            if (bad)
                continue;
        }
        for (a = 0; a < 3; a++) {
            if (i == g_00414580[g][a]) {
                for (b = 0; b < 3; b++) {
                    if (j == g_00414580[g][b])
                        return 1;
                }
            }
        }
    }
    return 0;
}

/* 0x002F7AD0, 0x40 bytes. Whether (i, j) is the pair (a, b) either way round. */
int func_002F7AD0(u32 i, u32 j, u32 a, u32 b)
{
    if (i == a && j == b)
        return 1;
    return i == b && j == a;
}

/* 0x002F7B10, 0xC bytes, matching. The officer lists. */
u32 *func_002F7B10(void)
{
    return g_007A2650;
}

/* 0x002F7B20, 0x118 bytes. Sorts officer list `l` (`n` long, up to the first number past 0x19E,
 * as in the original the test is inverted: it stops at the first real one) by role. */
void func_002F7B20(int a, u32 *l, int n)
{
    int x, y;

    for (x = 0; x < n; x++) {
        u32 u = l[x];

        if (u > 0x19E) {
            int r = func_002F3DC0(u);

            for (y = x + 1; y < n; y++) {
                u32 v = l[y];
                int s;

                if (v > 0x19E)
                    break;
                s = func_002F3DC0(v);
                if (r < s) {
                    l[x] = v;
                    l[y] = u;
                    r = s;
                    u = v;
                }
            }
        }
    }
}

/* 0x002F7C40, 0x94 bytes, matching. Shuffles list `l` of `n`. */
void func_002F7C40(u32 *l, int n)
{
    int k;

    for (k = 0; k < n; k++) {
        int a = func_0030CB00(n), b = func_0030CB00(n);

        if (a != b) {
            u32 t = l[a];

            l[a] = l[b];
            l[b] = t;
        }
    }
}

/* 0x002F7CE0, 0xAC bytes, matching. Officer order: higher role first, then lower second force, then lower
 * number. */
int func_002F7CE0(u32 i, u32 j)
{
    int a = func_002F3DC0(i), b = func_002F3DC0(j);

    if (b < a)
        return 1;
    if (a < b)
        return 0;
    a = func_002F5CC0(i);
    b = func_002F5CC0(j);
    if (a < b)
        return 1;
    if (b < a)
        return 0;
    return (int)i < (int)j;
}

void func_002F87D0(u32 *l, int n, int (*less)(u32, u32, int, int), int a, int b);

/* 0x002F7D90, 0x12C bytes. Lists into list `k` the living officers (rank not 3) that `keep`
 * accepts (all without it), sorted when `sort`. Returns how many. */
int func_002F7D90(int k, int (*keep)(u32, int, int), int a, int b, int sort, int unused)
{
    u32 *l = g_007A2650 + k;
    u8 *p = func_0030CCB0();
    int n = 0, i;

    for (i = 0; i < 0x19F; i++, p += 0x9C) {
        u32 id = OFC_NUM(p);

        if (func_002F3BA0(p) == 3)
            continue;
        if (keep == 0 || keep(id, a, b) != 0)
            l[n++] = id;
    }
    if (sort != 0)
        func_002F87D0(l, n, (int (*)(u32, u32, int, int))func_002F7CE0, 0, 0);
    return n;
}

/* Whether officer `i`'s role counts (not 0, 4 or 5). */
#define ACTIVE_ROLE(i) (func_002F3DC0(i) != 0 && func_002F3DC0(i) != 4 && func_002F3DC0(i) != 5)

/* 0x002F7EC0, 0xBC bytes. Whether officer `i` (rank 2) of second force `f` serves it actively
 * in its own region (func_0030AFF0). */
int func_002F7EC0(u32 i, int f)
{
    int region = func_0030AFF0(f);

    if (func_002F2840(i) == 0)
        return 0;
    return f == func_002F5CC0(i) && ACTIVE_ROLE(i) && region == func_002F4080(i);
}

/* 0x002F7F80, 0x94 bytes. Whether officer `i` serves second force `f` actively. */
int func_002F7F80(u32 i, int f)
{
    if (func_002F2840(i) == 0)
        return 0;
    return f == func_002F5CC0(i) && ACTIVE_ROLE(i);
}

/* 0x002F8020, 0x50 bytes, matching. Whether officer `i` (rank 2) has second force `f`. */
int func_002F8020(u32 i, int f)
{
    if (func_002F2840(i) == 0)
        return 0;
    return f == func_002F5CC0(i);
}

/* 0x002F8070, 0x48 bytes. */
int func_002F8070(u32 i, int f)
{
    return func_002F7EC0(i, f) != 0 && func_002F3E70(i) == 0;
}

/* 0x002F80C0, 0x4C bytes. */
int func_002F80C0(u32 i, int f)
{
    return func_002F7EC0(i, f) != 0 && func_002F3DC0(i) >= 2;
}

/* 0x002F8110, 0x48 bytes. */
int func_002F8110(u32 i, int f)
{
    return func_002F7EC0(i, f) != 0 && func_002F3EF0(i) != 0;
}

/* 0x002F8160, 0x94 bytes. Whether officer `i` serves force `f` actively. */
int func_002F8160(u32 i, int f)
{
    if (func_002F2840(i) == 0)
        return 0;
    return f == func_002F4080(i) && ACTIVE_ROLE(i);
}

/* 0x002F8200, 0x4C bytes. The same, other than officer `x`. */
int func_002F8200(u32 i, int f, u32 x)
{
    return func_002F8160(i, f) != 0 && i != x;
}

/* 0x002F8250, 0x48 bytes. */
int func_002F8250(u32 i, int f)
{
    return func_002F8160(i, f) != 0 && func_002F3E70(i) == 0;
}

/* 0x002F82A0, 0x4C bytes. */
int func_002F82A0(u32 i, int f)
{
    return func_002F8160(i, f) != 0 && func_002F3DC0(i) >= 2;
}

/* 0x002F82F0, 0x4C bytes. */
int func_002F82F0(u32 i, int f)
{
    return func_002F8160(i, f) != 0 && func_002F3DC0(i) == 2;
}

/* 0x002F8340, 0x48 bytes. */
int func_002F8340(u32 i, int f)
{
    return func_002F8160(i, f) != 0 && func_002F3EF0(i) != 0;
}

/* 0x002F8390, 0x94 bytes. Whether officer `i` serves actively another force than `f`. */
int func_002F8390(u32 i, int f)
{
    if (func_002F2840(i) == 0)
        return 0;
    return f != func_002F4080(i) && ACTIVE_ROLE(i);
}

/* 0x002F8430, 0x48 bytes. */
int func_002F8430(u32 i, int f)
{
    return func_002F8390(i, f) != 0 && func_002F3E70(i) == 0;
}

/* 0x002F8480, 0x80 bytes. Whether officer `i` of role 1 or 2 has a second force for which
 * func_0030B2F0 holds. */
int func_002F8480(u32 i)
{
    if (func_002F2840(i) == 0)
        return 0;
    if (func_0030B2F0(func_002F5CC0(i)) == 0)
        return 0;
    return func_002F3DC0(i) == 2 || func_002F3DC0(i) == 1;
}

/* 0x002F8500, 0x6C bytes. Whether officer `i` (role 0) has second force `f`. */
int func_002F8500(u32 i, int f)
{
    if (func_002F2840(i) == 0)
        return 0;
    return func_002F3DC0(i) == 0 && f == func_002F5CC0(i);
}

/* 0x002F8570, 0x68 bytes. */
int func_002F8570(u32 i)
{
    if (func_002F2840(i) != 0 && func_002F3DC0(i) == 0 && func_0030B2F0(func_002F5CC0(i)) != 0)
        return 1;
    return 0;
}

/* 0x002F85E0, 0x44 bytes, matching. */
int func_002F85E0(u32 i)
{
    if (func_002F2840(i) == 0)
        return 0;
    return func_002F3DC0(i) == 0;
}

/* 0x002F8630, 0x74 bytes. Whether officer `i` (role 0) has a second force of region `r`. */
int func_002F8630(u32 i, int r)
{
    if (func_002F2840(i) != 0 && func_002F3DC0(i) == 0 && r == func_0030AFF0(func_002F5CC0(i)))
        return 1;
    return 0;
}

/* 0x002F86B0, 0x58 bytes. Whether officer `i` (rank 1) has second force `f`. */
int func_002F86B0(u32 i, int f)
{
    return func_002F3BB0(i) == 1 && f == func_002F5CC0(i);
}

/* 0x002F8710, 0x24 bytes, matching. */
int func_002F8710(u32 i)
{
    return func_002F3BB0(i) == 1;
}

/* 0x002F8740, 0x60 bytes, matching. */
int func_002F8740(u32 i, int r)
{
    if (func_002F3BB0(i) == 1 && r == func_0030AFF0(func_002F5CC0(i)))
        return 1;
    return 0;
}

/* 0x002F87A0, 0x24 bytes, matching. */
int func_002F87A0(u32 i)
{
    return func_002F3BB0(i) == 0;
}

/* 0x002F87D0, 0x128 bytes. Sorts officer list `l` of `n` with `less` (the same inverted
 * stop as func_002F7B20). */
void func_002F87D0(u32 *l, int n, int (*less)(u32, u32, int, int), int a, int b)
{
    int x, y;

    for (x = 0; x < n; x++) {
        u32 u = l[x];

        if (u > 0x19E) {
            for (y = x + 1; y < n; y++) {
                u32 v = l[y];

                if (v > 0x19E)
                    break;
                if (less != 0 && less(u, v, a, b) == 0) {
                    l[x] = v;
                    l[y] = u;
                    u = v;
                }
            }
        }
    }
}

/* 0x002F8900, 0x220 bytes. Officer order for promotions: role 3 / 5 officers first, then
 * created officers last, named ones (below 0x1C) first, then by experience plus a quarter of
 * their service time x 100, then by number. */
int func_002F8900(u32 i, u32 j)
{
    int ci, cj, si, sj;

    if (func_002F3E70(i) != 0 && func_002F3E70(j) == 0)
        return 1;
    if (func_002F3E70(j) != 0 && func_002F3E70(i) == 0)
        return 0;
    ci = CREATED(i);
    cj = CREATED(j);
    if (ci && !cj)
        return 0;
    if (cj && !ci)
        return 1;
    if ((int)i < 0x1C && (int)j > 0x1B)
        return 1;
    if ((int)j < 0x1C && (int)i > 0x1B)
        return 0;
    si = func_002F34E0(i) + (func_00327C70() - func_002F3380(i)) * 100 / 4;
    sj = func_002F34E0(j) + (func_00327C70() - func_002F3380(j)) * 100 / 4;
    if (sj < si)
        return 1;
    if (si < sj)
        return 0;
    return (int)i < (int)j;
}
