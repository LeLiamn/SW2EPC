/*
 * emp_hist_event.c - the Empire mode's historical events: each event runs a 4-step machine
 * (0 notice, 1 message, 2 result, 3 done) on the state at 0x007BFB48, then changes the forces
 * involved (the officers 2, 3, 4, 8, ... name the forces by their current lords). Also the
 * battle-view object helpers just before (0x003E8940-0x003E97F8). Original file name unknown
 * (parts of 0x003E8940-0x003EE49C).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

#define SW2E_FILE_EMP_HIST_EVENT_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_007BFB48[3];                /* the event step, its event, its result */
extern char g_007B4E60[];                /* a message buffer */
#ifdef SW2E_PC
extern ps2ptr g_0045D2C0_a;                   /* (small data) the camera */
#define g_0045D2C0 ((u8 *)PS2_PTR(g_0045D2C0_a))
#define g_0045D2C0_SET(v) (g_0045D2C0_a = PS2_ADDR(v))
#else
extern u8 *g_0045D2C0;
#define g_0045D2C0_a (*(ps2ptr *)&g_0045D2C0)
#define g_0045D2C0_SET(v) (g_0045D2C0 = (v))
#endif
extern u8 g_005B4BC0[];

void func_001784E0(void);
void func_00179320(void);
void func_001204B0(char *buf, int fmt);

#define EV_STEP() ((int *)func_003EA000())
int *func_003EA000(void);
int func_003EA030(int o);
int func_003EA080(void);
int func_003EA0A0(void);
int func_003EA0C0(void);
int func_003EA0E0(void);
int func_003EA100(void);
int func_003EA120(void);
int func_003EA160(void);
void func_003EA1C0(int f);
void func_003EA310(int f);
void func_003EA330(int f);

/* The battle-view object (func_00391250): +0x16C on, +0x170, +0x178, +0x17C. */

/* 0x003E96E0, 0x20 bytes, matching. */
int func_003E96E0(void)
{
    return *(int *)(func_00391250() + 0x16C);
}

/* 0x003E8940, 0x34 bytes, matching. */
void func_003E8940(void)
{
    if (func_003E96E0() != 0) {
        g_0045D2C0_SET(g_005B4BC0);
        func_001796D0();
    }
}

/* 0x003E8980, 0x20 bytes, matching. */
int func_003E8980(void)
{
    func_001784E0();
    return 1;
}

/* 0x003E89A0, 0x24 bytes, matching. */
void func_003E89A0(void)
{
    func_00391250();
    func_00179320();
}

/* 0x003E95D0, 0x2C bytes, matching. */
void func_003E95D0(void)
{
    if (func_003E96E0() != 0)
        func_003E89A0();
}

/* 0x003E9600, 0x2C bytes, matching. */
void func_003E9600(void)
{
    func_00391250();
    func_00178460();
    func_00182C20();
}

/* 0x003E9630, 0x58 bytes. */
int func_003E9630(void)
{
    int on;

    func_00391250();
    on = func_003E96E0();
    if (on == 0) {
        func_00102990();
        func_00279B20();
        func_00178460();
        func_00182C20();
    }
    return on != 0;
}

/* 0x003E9690, 0x1C bytes, matching. */
void func_003E9690(void)
{
    func_003E9600();
}

/* 0x003E96B0, 0x30 bytes, matching. */
void func_003E96B0(void)
{
    u8 *v = func_00391250();

    *(int *)(v + 0x16C) = 0;
    *(int *)(v + 0x170) = 0;
    *(int *)(v + 0x178) = 0;
    v[0x17C] = 0;
    func_0019F550();
}

/* 0x003E9700, 0x28 bytes, matching. */
void func_003E9700(int v)
{
    *(int *)(func_00391250() + 0x16C) = v;
}

/* 0x003E9730, 0x20 bytes, matching. */
int func_003E9730(void)
{
    return *(int *)(func_00391250() + 0x170);
}

/* 0x003E9750, 0x28 bytes, matching. */
void func_003E9750(int v)
{
    *(int *)(func_00391250() + 0x170) = v;
}

/* 0x003E9780, 0x20 bytes, matching. */
int func_003E9780(void)
{
    return *(int *)(func_00391250() + 0x178);
}

/* 0x003E97A0, 0x28 bytes, matching. */
void func_003E97A0(int v)
{
    *(int *)(func_00391250() + 0x178) = v;
}

/* 0x003E97D0, 0x28 bytes, matching. */
void func_003E97D0(u8 v)
{
    func_00391250()[0x17C] = v;
}

/* Step 1 of an event: when the notice is answered, shows message `a` (`b` in the other mode). */
static void event_message(int a, int b)
{
    int *s = EV_STEP();

    if (func_0030E1F0() == 2) {
        func_0030E100();
        func_001204B0(g_007B4E60, PS2_PTR_PC(PS2_ADDR(func_00390760(func_0036B260() == 0 ? a : b))));
        func_00374EE0(PS2_ADDR(g_007B4E60));
        s[0] = 2;
    }
}

/* Runs an event's steps 0-2 (3: done). */
static int event_run(void (*s0)(void), void (*s1)(void), void (*s2)(void))
{
    int v = *EV_STEP();

    if (v != 3) {
        if (v == 2)
            s2();
        else if (v == 1)
            s1();
        else if (v == 0)
            s0();
    }
    return 5;
}

/* 0x003E99C0, 0x28 bytes, matching. */
int func_003E99C0(void)
{
    func_003EA1C0(func_003EA0A0());
    return 0;
}

/* 0x003E99F0, 0x58 bytes. */
void func_003E99F0(void)
{
    int *s = EV_STEP();

    func_0030E140(func_0036B260() == 0 ? 0x7C : 0x7B, 4, -1, -1);
    s[0] = 1;
}

/* 0x003E9A50, 0x8C bytes. */
void func_003E9A50(void)
{
    event_message(0xD3, 0xD2);
}

/* 0x003E9AE0, 0x94 bytes. When the message closes, the force of officer 8 gains (or loses in the
 * other mode). */
void func_003E9AE0(void)
{
    int *s = EV_STEP();

    if (func_00375BF0() != 0 && func_00375B90() == 1) {
        if (func_0036B260() == 0) {
            func_003EA310(func_003EA0A0());
            func_003EA1C0(func_003EA0A0());
        } else {
            func_003EA330(func_003EA0A0());
        }
        s[0] = 3;
    }
}

/* 0x003E9B80, 0x80 bytes. */
int func_003E9B80(void)
{
    return event_run(func_003E99F0, func_003E9A50, func_003E9AE0);
}

/* 0x003E9DC0, 0x28 bytes, matching. */
int func_003E9DC0(void)
{
    func_003EA1C0(func_003EA080());
    return 0;
}

/* 0x003E9DF0, 0x58 bytes. */
void func_003E9DF0(void)
{
    int *s = EV_STEP();

    func_0030E140(func_0036B260() == 0 ? 0x7A : 0x79, 8, -1, -1);
    s[0] = 1;
}

/* 0x003E9E50, 0x8C bytes. */
void func_003E9E50(void)
{
    event_message(0xD9, 0xD8);
}

/* 0x003E9EE0, 0x94 bytes. */
void func_003E9EE0(void)
{
    int *s = EV_STEP();

    if (func_00375BF0() != 0 && func_00375B90() == 1) {
        if (func_0036B260() == 0) {
            func_003EA310(func_003EA080());
            func_003EA1C0(func_003EA080());
        } else {
            func_003EA330(func_003EA080());
        }
        s[0] = 3;
    }
}

/* 0x003E9F80, 0x80 bytes. */
int func_003E9F80(void)
{
    return event_run(func_003E9DF0, func_003E9E50, func_003E9EE0);
}

/* 0x003EA000, 0xC bytes, matching. */
int *func_003EA000(void)
{
    return g_007BFB48;
}

/* 0x003EA010, 0x20 bytes, matching. */
void func_003EA010(void)
{
    g_007BFB48[0] = 0;
    g_007BFB48[1] = -1;
    g_007BFB48[2] = -1;
}

/* 0x003EA030, 0x50 bytes. Officer `o`'s force (0x19 when he is not in play). */
int func_003EA030(int o)
{
    if (func_002F2840(o) == 0 || func_002F3E70(o) == 0)
        return 0x19;
    return func_002F4080(o);
}

/* 0x003EA080, 0x1C bytes, matching. */
int func_003EA080(void)
{
    return func_003EA030(4);
}

/* 0x003EA0A0, 0x1C bytes, matching. */
int func_003EA0A0(void)
{
    return func_003EA030(8);
}

/* 0x003EA0C0, 0x1C bytes, matching. */
int func_003EA0C0(void)
{
    return func_003EA030(2);
}

/* 0x003EA0E0, 0x1C bytes, matching. */
int func_003EA0E0(void)
{
    return func_003EA030(0x10);
}

/* 0x003EA100, 0x1C bytes, matching. */
int func_003EA100(void)
{
    return func_003EA030(0x12);
}

/* 0x003EA120, 0x1C bytes, matching. */
int func_003EA120(void)
{
    return func_003EA030(0xE8);
}

/* 0x003EA140, 0x1C bytes, matching. */
int func_003EA140(void)
{
    return func_003EA030(3);
}

/* 0x003EA160, 0x1C bytes, matching. */
int func_003EA160(void)
{
    return func_003EA030(0x9F);
}

/* 0x003EA180, 0x1C bytes, matching. */
int func_003EA180(void)
{
    return func_003EA030(0xB5);
}

/* 0x003EA1A0, 0x1C bytes, matching. */
int func_003EA1A0(void)
{
    return func_003EA030(0x11);
}

/* 0x003EA1C0, 0x34 bytes, matching. */
void func_003EA1C0(int f)
{
    func_002F9E10(f, 3);
    func_002F9F40(f, 0xFF);
}

/* 0x003EA310, 0x1C bytes, matching. */
void func_003EA310(int f)
{
    func_003EA200(f, 100);
}

/* 0x003EA330, 0x1C bytes, matching. */
void func_003EA330(int f)
{
    func_003EA200(f, -0x1E);
}

/* 0x003EA350, 0x94 bytes. Whether officer `o` is in the battle. */
int func_003EA350(int o)
{
    int s, k;

    for (s = 0; s < 2; s++) {
        for (k = 0; k < 8; k++) {
            if (o == func_003620E0(s, k))
                return 1;
        }
    }
    return 0;
}

/* 0x003EAEF0, 0x4C bytes, matching. */
void func_003EAEF0(void)
{
    int v;

    func_00376100(4, 5, 0x159);
    v = func_003296F0();
    g_007BFB48[1] = v;
    func_00369BB0(v, -1);
    g_007BFB48[0] = 1;
}

/* 0x003EAF40, 0x54 bytes. */
void func_003EAF40(void)
{
    int buf[12];

    if (func_0036B120() == 1) {
        g_007BFB48[0] = 2;
        func_0036B170(buf);
        g_007BFB48[2] = buf[0];
        g_007BFB48[0] = 2;
    }
}

/* 0x003EB0C0, 0x1C bytes, matching. */
void func_003EB0C0(void)
{
    func_0036A560();
}

/* 0x003EB0E0, 0x38 bytes. */
void func_003EB0E0(void)
{
    if (g_007BFB48[0] == 1)
        func_003EB0C0();
}

/* 0x003EB120, 0x7C bytes. */
int func_003EB120(void)
{
    if (g_007BFB48[0] == 2) {
        func_003EAFA0();
        return 0;
    }
    if (g_007BFB48[0] == 1)
        func_003EAF40();
    else if (g_007BFB48[0] == 0)
        func_003EAEF0();
    return 5;
}

/* 0x003EB380, 0x38 bytes, matching. */
int func_003EB380(void)
{
    func_003EA1C0(func_003EA100());
    func_003EA1C0(func_003EA120());
    return 0;
}

/* 0x003EB3C0, 0xA8 bytes. */
void func_003EB3C0(void)
{
    int *s = EV_STEP();
    int m, a;

    if (func_0036B260() == 0) {
        if (func_00327D50() == func_003EA0C0()) {
            m = 0x7E;
            a = 2;
        } else {
            m = 0x80;
            a = 0x10;
        }
    } else {
        if (func_00327D50() == func_003EA0C0()) {
            m = 0x7D;
            a = 2;
        } else {
            m = 0x7F;
            a = 0x10;
        }
    }
    func_0030E140(m, a, -1, -1);
    s[0] = 1;
}

/* 0x003EB470, 0x8C bytes. */
void func_003EB470(void)
{
    event_message(0xDF, 0xDE);
}

/* 0x003EB500, 0xC4 bytes. */
void func_003EB500(void)
{
    int *s = EV_STEP();

    if (func_00375BF0() != 0 && func_00375B90() == 1) {
        if (func_0036B260() == 0) {
            func_003EA310(func_003EA100());
            func_003EA1C0(func_003EA100());
            func_003EA310(func_003EA120());
            func_003EA1C0(func_003EA120());
        } else {
            func_003EA330(func_003EA100());
            func_003EA330(func_003EA120());
        }
        s[0] = 3;
    }
}

/* 0x003EB5D0, 0x80 bytes. */
int func_003EB5D0(void)
{
    return event_run(func_003EB3C0, func_003EB470, func_003EB500);
}

/* 0x003EB840, 0x38 bytes, matching. */
int func_003EB840(void)
{
    func_003EA1C0(func_003EA0C0());
    func_003EA1C0(func_003EA0E0());
    return 0;
}

/* 0x003EB940, 0x8C bytes. */
void func_003EB940(void)
{
    event_message(0xE5, 0xE4);
}

/* 0x003EBAA0, 0x80 bytes. */
int func_003EBAA0(void)
{
    return event_run(func_003EB880, func_003EB940, func_003EB9D0);
}

/* 0x003EBD70, 0x58 bytes. */
void func_003EBD70(void)
{
    int *s = EV_STEP();

    func_0030E140(func_0036B260() == 0 ? 0x16F : 0x16E, 3, -1, -1);
    s[0] = 1;
}

/* 0x003EBDD0, 0x8C bytes. */
void func_003EBDD0(void)
{
    event_message(0xEB, 0xEA);
}

/* 0x003EC0B0, 0x80 bytes. */
int func_003EC0B0(void)
{
    return event_run(func_003EBD70, func_003EBDD0, func_003EC000);
}

/* 0x003EC460, 0x5C bytes. */
void func_003EC460(void)
{
    int *s = EV_STEP();

    func_0030E140(func_0036B260() == 0 ? 0x86 : 0x85, 0xC, 2, -1);
    s[0] = 1;
}

/* 0x003EC8F0, 0x80 bytes. */
int func_003EC8F0(void)
{
    return event_run(func_003EC460, func_003EC4C0, func_003EC800);
}

/* Breaks off `f`'s officers listed by func_003EAB60. */
static int release_all(int f)
{
    int list[28], n = func_003EAB60(f, list), k;

    for (k = 0; k < n; k++)
        func_003EA1C0(list[k]);
    return 0;
}

/* 0x003ECC20, 0x6C bytes. */
int func_003ECC20(void)
{
    return release_all(func_003EA0E0());
}

/* 0x003ECC90, 0x64 bytes. */
void func_003ECC90(void)
{
    int *s = EV_STEP();

    if (func_0036B260() == 0) {
        func_0030E140(0x172, 0x11, 0x13, -1);
    } else {
        func_003303B0(0x1AB);
        func_003137C0();
    }
    s[0] = 1;
}

/* 0x003ECD00, 0x8C bytes. */
void func_003ECD00(void)
{
    event_message(0xF9, 0xF8);
}

/* 0x003ECFC0, 0x80 bytes. */
int func_003ECFC0(void)
{
    return event_run(func_003ECC90, func_003ECD00, func_003ECEB0);
}

/* 0x003ED310, 0x6C bytes. */
int func_003ED310(void)
{
    return release_all(func_003EA160());
}

/* 0x003ED380, 0x68 bytes. */
void func_003ED380(void)
{
    int *s = EV_STEP();

    if (func_0036B260() == 0)
        func_0030E140(0x171, 0x10, 0xE, -1);
    else
        func_0030E140(0x170, 0xE, 0x10, -1);
    s[0] = 1;
}

/* 0x003ED3F0, 0x8C bytes. */
void func_003ED3F0(void)
{
    event_message(0xFF, 0xFE);
}

/* 0x003ED910, 0x80 bytes. */
int func_003ED910(void)
{
    return event_run(func_003ED380, func_003ED3F0, func_003ED7F0);
}

/* 0x003EDBD0, 0x28 bytes, matching. */
int func_003EDBD0(void)
{
    func_003EA1C0(func_003EA160());
    return 0;
}

/* 0x003EDC70, 0x8C bytes. */
void func_003EDC70(void)
{
    event_message(0x105, 0x104);
}

/* 0x003EDED0, 0x80 bytes. */
int func_003EDED0(void)
{
    return event_run(func_003EDC00, func_003EDC70, func_003EDE40);
}

/* 0x003EE170, 0x6C bytes. */
int func_003EE170(void)
{
    return release_all(func_003EA0E0());
}

/* 0x003EE1E0, 0x68 bytes. */
void func_003EE1E0(void)
{
    int *s = EV_STEP();

    if (func_0036B260() == 0)
        func_0030E140(0x176, 0, 0x9F, -1);
    else
        func_0030E140(0x175, 0x9F, 0, -1);
    s[0] = 1;
}

/* 0x003EE250, 0x8C bytes. */
void func_003EE250(void)
{
    event_message(0x10B, 0x10A);
}

/* 0x003EE3A0, 0x80 bytes. */
int func_003EE3A0(void)
{
    return event_run(func_003EE1E0, func_003EE250, func_003EE2E0);
}

/* 0x003EE420, 0x38 bytes. */
int func_003EE420(int a, int b)
{
    if (a == 0x1D)
        return b == 3 ? 0x78 : b + 0x68;
    return b + a * 4;
}

/* 0x003EE460, 0x38 bytes. */
int func_003EE460(int v)
{
    if (v == 0x1A)
        v = 0x1D;
    else if (v > 0x1A && v < 0x1E)
        v--;
    return v;
}
