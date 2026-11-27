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
