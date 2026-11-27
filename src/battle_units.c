/*
 * battle_units.c - the battlefield's unit and effect managers (original source file unknown;
 * 0x001724C0-0x0017C0CC, between unit_touch.c and the camera shake). Only the simple functions
 * are written so far.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

typedef u8 Unit;

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)(o) + (off)))->f##n)

/* The unit's state flags at +0x198, reached as a member (the original reloads it from the unit
 * each time instead of keeping its address). */
typedef struct {
    u8 pad[0x198];
    Bits8 f198;
} UnitFlags;

#define F198(u, n) (((UnitFlags *)(u))->f198.f##n)

float fabsf(float x);

/* A list of units found in an area of the battlefield grid. */
typedef struct {
    Unit *found[0xA0];
    u32 count;               /* +0x280 */
} UnitList;

extern u8 g_00574DE0[][0x630];           /* the units */
extern u8 g_005ADD80[0x40][0xC0];        /* the effect records */
extern u8 g_005B2BB0[];                  /* the battlefield's unit grid */
extern u32 g_0045D2BC;                   /* (small data) the next effect record to try */
extern u32 g_0045D2C0;                   /* (small data) */
extern u8 g_005B4DF0[0x10], g_005B5030[0x10];   /* flag bytes (bit 0) in larger objects */

void func_00173430(Unit *u);
void func_0017E560(u8 *grid, UnitList *out, float *box);
void func_001AE090(u8 *rec);
void func_00178250(void);
void func_002A7D90(void);
void func_001BCF00(void);
void func_0017C640(void);
void func_0024BF60(void);
void func_0016CEB0(void);
void func_001BCE60(void);
void func_0017C5C0(void);
void func_001AE530(void);
void func_002A7A50(void);
void func_0016CE80(void);
void func_00178460(void);
void func_0024BE90(void);
int func_0032E7B0(void);
void func_00179700(int a);

/* 0x00173970, 0xFC bytes. Runs func_00173430 for every unit on the field (flag 2 of +0x198)
 * that is not hidden (or is a bodyguard of kind 1 or 2), not riding (except actions 0x55, 0x56,
 * 0x60, 0x61), not in states 0x3D-0x3F, with flag 0x10 of +0x198. */
void func_00173970(void)
{
    int k;
    UnitFlags *u = (UnitFlags *)g_00574DE0[0];

    for (k = 0; k < 0x8F; k++, u = (UnitFlags *)((u8 *)u + 0x630)) {
        u16 a;

        if (!u->f198.f1)
            continue;
        if (BIT(u, 0x19C, 7) && (U8(u, 0x15A) == 0 || U8(u, 0x15A) == 3))
            continue;
        if (PTR(u, 0x288) != 0) {
            a = U16(PTR(u, 0x210), 0);
            if (a != 0x55 && a != 0x56 && a != 0x60 && a != 0x61)
                continue;
        }
        if ((u32)(S32(u, 0x118) - 0x3D) > 2 && u->f198.f4)
            func_00173430((Unit *)u);
    }
}

/* 0x001748B0, 0x188 bytes. The first unit on the field near `u` (within `r` flat and `h`
 * high, found in the grid) with a model and mount kind (+0x155) `kind`; 0 for none. */
Unit *func_001748B0(float r, float h, Unit *u, u32 kind)
{
    UnitList list;
    float box[4], e;
    u32 k;

    e = h + F32(PTR(u, 0x114), 0x88);
    box[0] = F32(u, 0x40) - e;
    box[1] = F32(u, 0x40) + e;
    box[2] = F32(u, 0x48) - e;
    list.count = 0;
    box[3] = F32(u, 0x48) + e;
    func_0017E560(g_005B2BB0, &list, box);
    for (k = 0; k < list.count; k++) {
        u8 *v = list.found[k];

        if (BIT(v, 0x198, 1) && PTR(v, 0x11C) != 0 && v != u && kind == U8(v, 0x155)
            && fabsf(F32(u, 0x44) - F32(v, 0x44)) <= h) {
            float x = F32(u, 0x40) - F32(v, 0x40), z = F32(u, 0x48) - F32(v, 0x48);

            if (x * x + z * z < r * r)
                return v;
        }
    }
    return 0;
}

/* 0x00177ED0, 0xA4 bytes. Takes the next effect record not locked (flag 4 of +0x8C), in turn;
 * one still playing (flag 1) is stopped first. */
u8 *func_00177ED0(void)
{
    u8 *r;

    for (;;) {
        r = g_005ADD80[g_0045D2BC];
        if (!BIT(r, 0x8C, 2))
            break;
        g_0045D2BC = g_0045D2BC + 1;
        if (g_0045D2BC > 0x3F)
            g_0045D2BC = 0;
    }
    if (BIT(r, 0x8C, 0))
        func_001AE090(r);
    g_0045D2BC = g_0045D2BC + 1;
    if (g_0045D2BC > 0x3F)
        g_0045D2BC = 0;
    return r;
}

/* 0x001781C0, 0x88 bytes. Shuts the battlefield managers down. */
void func_001781C0(void)
{
    func_00178460();
    func_001BCE60();
    func_0017C5C0();
    func_001AE530();
    func_002A7A50();
    func_0016CE80();
    func_0024BE90();
    g_0045D2C0 = 0;
    BIT(g_005B4DF0, 0, 0) = 0;
    BIT(g_005B5030, 0, 0) = 0;
}

/* 0x00178460, 0x80 bytes. Resets the battlefield managers. */
void func_00178460(void)
{
    func_00178250();
    func_002A7D90();
    func_001BCF00();
    func_0017C640();
    func_0024BF60();
    func_0016CEB0();
    g_0045D2C0 = 0;
    BIT(g_005B4DF0, 0, 0) = 0;
    BIT(g_005B5030, 0, 0) = 0;
}

/* 0x001796D0, 0x2C bytes. func_00179700(0) unless func_0032E7B0 says otherwise. */
void func_001796D0(void)
{
    if (func_0032E7B0() == 0)
        func_00179700(0);
}
