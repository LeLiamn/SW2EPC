/*
 * camera.c - the battle camera (original source file unknown; from 0x00161490, after
 * scene_initialize.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
 *
 * Range 0x00161490-0x0016467C. The camera follows a unit from behind: its eye sits at a
 * distance behind the unit's facing, pitched up by an angle that follows the slope of the ground,
 * kept above the ground and out of the scenery (ray tests). Other views: turning to a set yaw,
 * looking down at a beaten unit, between two units, a motion-driven camera, the slow-motion duel
 * view; func_00164440 picks the view each frame and adds the shake. The camera's state (an
 * array of words) holds: +0 the 3D camera object (eye at +0x1C0, target at +0x1D0, view angle
 * +0x224), +4 the unit, +8 the yaw, +0xC the distance, +0x14 the height offset, +0x18 a timer,
 * +0x20 / +0x24 / +0x2C other units, +0x28 a camera motion (frame +0x30), +0x38 the slope angle,
 * +0x3C flags, +0x40 the shake, +0x90 / +0xB0 / +0xC0 the targets and eye kept, +0xE0 a set eye.
 */

#define SW2E_FILE_CAMERA_C
#include "sw2e_mem.h"
#include "sw2e_protos.h"
#include "sw2e_pc.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

#define U8(o, off)  (*(u8 *)((u8 *)PS2_ANYPTR(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)PS2_ANYPTR(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)PS2_ANYPTR(o) + (off)))
#define PTR(o, off) PS2_LOADP(u8 *, ((u8 *)(o) + (off)))
#define PTR_SET(o, off, v) PS2_STOREP(u8 *, ((u8 *)(o) + (off)), v)

#define PI     3.1415927f
#define TWO_PI 6.2831855f

typedef u8 Unit;

/* A flag byte: the original tests its bits as signed one-bit fields (LSB first). */
typedef struct {
    signed char f0 : 1, f1 : 1, f2 : 1, f3 : 1, f4 : 1, f5 : 1, f6 : 1, f7 : 1;
} Bits8;

#define BIT(o, off, n) (((Bits8 *)((u8 *)PS2_ANYPTR(o) + (off)))->f##n)

#define ACT(u) PTR(u, 0x210)

float sqrtf(float x);
float fabsf(float x);
float vu0_angle(float x, float z);               /* VU0 micro subroutine 0x30 (atan2?) */
void vu0_sincos(float a, float *s, float *c);    /* VU0 micro subroutine 0x20 */

extern float g_004064A0[4];              /* the model's forward vector */
extern float g_00424D00[4];              /* the up vector */
extern u32 g_00669F60;                   /* battle flags (2: two players) */
/* (small data) camera settings */
extern float g_0045CE58, g_0045CE5C, g_0045CE60, g_0045CE64, g_0045CE68, g_0045CE6C;
extern float g_0045CE70, g_0045CE80, g_0045CE84;
extern char g_0045CE8C, g_0045CE90;
extern float g_0045D568;

float func_0029DEF0(float *pos, int a);          /* the ground's height under `pos` */
void func_0029DF20(float angle, float m[4][4], float *axis);   /* a rotation about `axis` */
int func_00162C30(int *cam, float *eye, float *target, float *closeness, int free);
void func_00164440(float a, float b, int *cam);

/* 0x00161490, 0x8C bytes. The point a camera looks at on a unit (its centre; on foot while
 * running, at its feet); 0 for a rider whose mount is not set up. */
int func_00161490(float *out, Unit *u)
{
    float h = F32(PTR(u, 0x114), 0x80);
    u32 f;
    Unit *m;

    out[0] = F32(u, 0x90);
    out[1] = F32(u, 0x94);
    out[2] = F32(u, 0x98);
    out[3] = F32(u, 0x9C);
    f = U32(ACT(u), 0x18);
    if ((f & 0x8000000) == 0) {
        if (f & 0x80)
            out[1] = F32(u, 0x44) - h;
        return 1;
    }
    m = PTR(u, 0x288);
    return m != 0 && PTR(m, 0x11C) != 0 && (U8(m, 0x198) & 2);
}

/* 0x00161520, 0xE0 bytes. A unit's forward direction: from its yaw, or (with a model) its root
 * node's, flattened. */
void func_00161520(float *out, Unit *u)
{
    if (PTR(u, 0x11C) == 0) {
        float s, c;

        vu0_sincos(F32(u, 0x54), &s, &c);
        out[0] = s;
        out[2] = c;
        out[1] = 0.0f;
        out[3] = 0.0f;
    } else {
        float *m = func_0016A170(u, 0), len;
        int k;

        for (k = 0; k < 4; k++)
            out[k] = m[k] * g_004064A0[0] + m[4 + k] * g_004064A0[1] + m[8 + k] * g_004064A0[2]
                     + m[12 + k] * g_004064A0[3];
        out[1] = 0.0f;
        len = sqrtf(out[0] * out[0] + out[2] * out[2] + out[3] * out[3]);
        for (k = 0; k < 4; k++)
            out[k] = out[k] / len;
    }
}

/* 0x00161600, 0x44 bytes. That direction's angle. */
float func_00161600(Unit *u)
{
    float v[4];

    func_00161520(v, u);
    return vu0_angle(v[0], v[2]);
}

/* 0x00161650, 0x138 bytes. The ground under `from` (*ground) and the lowest height the ground
 * between `from` and `eye` asks for (*low: four samples, the rise scaled by distance). */
void func_00161650(float *eye, float *from, float *low, float *ground)
{
    float step[4], p[4];
    int i;

    *ground = func_0029DEF0(from, 1);
    step[0] = (eye[0] - from[0]) * 0.25f;
    step[1] = 0.0f;
    step[2] = (eye[2] - from[2]) * 0.25f;
    step[3] = (eye[3] - from[3]) * 0.25f;
    for (i = 0; i < 4; i++)
        p[i] = from[i];
    p[1] = *ground;
    *low = 100000.0f;
    for (i = 0; i < 4; i++) {
        float v;
        int k;

        for (k = 0; k < 4; k++)
            p[k] = p[k] + step[k];
        p[1] = eye[1];
        p[1] = func_0029DEF0(p, 0);
        v = ((p[1] - *ground) / (float)(i + 1)) * 4.0f + *ground + 0.0f;
        if (v < *low)
            *low = v;
    }
}

/* 0x00161790, 0x5F4 bytes. Places the eye from the target: the pitch (by mode, mount, two
 * players, the action) plus the slope angle (followed at 0.1 degree a frame; the original also
 * lowers it when the difference is small and positive), the eye turned up by it about the side
 * axis, kept above the ground, and lowered by `scale` (looking up) by the setting's way. Whether
 * the ground pushed the eye. */
int func_00161790(float scale, Unit *u, int *cam, float *eye, float *target, int mode)
{
    float low, ground, pitch, cur, delta, d[4], side[4], m[4][4], v[4], len, dist;
    int hit, k;
    char c4, c3;

    if (0.9f < scale)
        scale = 0.9f;
    eye[1] = target[1];
    func_00161650(eye, target, &low, &ground);
    if (mode == 0)
        pitch = (U32(ACT(u), 0x18) & 0x8000000) == 0 ? g_0045CE58 : g_0045CE68;
    else
        pitch = (U32(ACT(u), 0x18) & 0x8000000) == 0 ? g_0045CE5C : g_0045CE6C;
    if (g_00669F60 & 2)
        pitch = pitch * 0.5f;
    if (U32(ACT(u), 0x1C) & 1)
        pitch = pitch + 0.34906587f;
    else if (U32(ACT(u), 0x1C) & 0x40000)
        pitch = pitch - 0.08726647f;
    d[0] = target[0] - eye[0];
    d[1] = 0.0f;
    d[2] = target[2] - eye[2];
    d[3] = target[3] - eye[3];
    side[0] = d[1] * g_00424D00[2] - d[2] * g_00424D00[1];
    side[1] = d[2] * g_00424D00[0] - d[0] * g_00424D00[2];
    side[2] = d[0] * g_00424D00[1] - d[1] * g_00424D00[0];
    side[3] = 0.0f;
    len = sqrtf(side[0] * side[0] + side[1] * side[1] + side[2] * side[2]);
    for (k = 0; k < 4; k++)
        side[k] = side[k] / len;
    dist = sqrtf(d[0] * d[0] + d[2] * d[2]);
    cur = F32(cam, 0x38);
    delta = g_0045CE80 * vu0_angle(ground - low, dist) - cur;
    if (delta < 0.0017453294f)
        F32(cam, 0x38) = cur - 0.0017453294f;
    else if (0.0017453294f < delta)
        F32(cam, 0x38) = cur + 0.0017453294f;
    else
        F32(cam, 0x38) = cur + delta;
    pitch = F32(cam, 0x38) + pitch;
    if (pitch < 0.0f)
        pitch = 0.0f;
    if (1.5707964f <= pitch)
        pitch = 1.5707964f;
    func_0029DF20(pitch * -1.0f, m, side);
    for (k = 0; k < 4; k++)
        v[k] = eye[k] - target[k];
    for (k = 0; k < 4; k++)
        eye[k] = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2] + m[3][k] * v[3] + target[k];
    low = low - 50.0f;
    hit = low < eye[1];
    if (hit)
        eye[1] = low;
    target[1] = target[1] + F32(cam, 0x14);
    if (U32(ACT(u), 0x1C) & 0x40000)
        target[1] = target[1] - 120.0f;
    if ((U32(ACT(u), 0x18) & 0x8000000) == 0) {
        c4 = g_0045CE8C;
        c3 = g_0045CE90;
    } else {
        c4 = 0;
        c3 = 0;
    }
    if (BIT(cam, 0x3C, 1)) {
        eye[1] = F32(PS2_LOADP(u8 *, cam), 0x1C4);
        for (k = 0; k < 4; k++)
            v[k] = eye[k] - target[k];
        len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
        for (k = 0; k < 4; k++)
            eye[k] = target[k] + v[k] / len * g_0045CE60;
    } else if (0.0001f < fabsf(scale)) {
        char how = mode == 0 ? c4 : c3;

        if (how == 0) {
            eye[1] = (eye[1] + 0.0f) - g_0045CE60 * scale;
        } else if (how == 1) {
            eye[1] = (eye[1] + 0.0f) - scale * 100.0f;
            target[1] = (target[1] + 0.0f) - scale * 100.0f;
            if (mode != 0 || (U32(ACT(u), 0x1C) & 0x40000) == 0)
                target[1] = eye[1] < target[1] ? target[1] : eye[1];
        } else {
            eye[1] = (eye[1] + 0.0f) - scale * 300.0f;
        }
    }
    return hit;
}

/* 0x00161D90, 0x80 bytes. The camera's distance (the setting on foot or mounted), eased from
 * `cur` by at most 1 a frame unless `at_once`. */
float func_00161D90(float cur, Unit *u, int at_once)
{
    float d = (U32(ACT(u), 0x18) & 0x8000000) == 0 ? g_0045CE60 : g_0045CE70;

    if (at_once == 0) {
        d = d - cur;
        if (d < -1.0f)
            d = -1.0f;
        else if (1.0f < d)
            d = 1.0f;
        d = cur + d;
    }
    return d;
}

/* 0x00161E10, 0x314 bytes. Starts a camera on unit `u` (and its mount): the unit (and mount)
 * settled, the eye placed behind it at the distance, the camera object's eye and target, and 30
 * steps of the camera's smoothing. */
void func_00161E10(int *cam, Unit *u, u8 *obj)
{
    Unit *m = PTR(u, 0x288);
    float eye[4], target[4], fwd[4], h, x;
    int k;

    if (m != 0 && BIT(u, 0x198, 1)) {
        func_00164DA0(m, 1);
        func_00178AC0(m);
        func_00166A00(m);
        func_00178AC0(m);
        func_001688D0(m);
        if (PTR(m, 0x11C) != 0)
            func_0014D560(PTR(m, 0x11C), 1, 0x3C);
    }
    func_00178AC0(u);
    func_00166A00(u);
    func_00178AC0(u);
    func_001688D0(u);
    if (PTR(u, 0x11C) != 0)
        func_0014D560(PTR(u, 0x11C), 0, 0x3C);
    target[0] = F32(u, 0x40);
    target[2] = F32(u, 0x48);
    target[3] = F32(u, 0x4C);
    h = (U32(ACT(u), 0x18) & 0x8000000) == 0 ? g_0045D568 : g_0045CE64;
    if (g_00669F60 & 2)
        h = h + 50.0f;
    target[1] = (F32(u, 0x44) - F32(PTR(u, 0x114), 0x80)) - h;
    F32(cam, 0xC) = func_00161D90(0.0f, u, 1);
    for (k = 0; k < 4; k++)
        eye[k] = target[k];
    func_00161520(fwd, u);
    eye[3] = 1.0f;
    for (k = 0; k < 3; k++)
        eye[k] = fwd[k] * -F32(cam, 0xC) + eye[k] + 0.0f;
    h = (g_00669F60 & 2) ? g_0045CE84 * 0.3f : g_0045CE84;
    F32(cam, 0x14) = h * -1.0f;
    cam[6] = 0;
    cam[0] = (int)PS2_ADDR(obj);
    cam[1] = (int)PS2_ADDR(u);
    cam[7] = 0;
    U16(cam, 0x36) = 0;
    cam[0xF] = 0;
    cam[0xE] = 0;
    BIT(cam, 0x3C, 2) = 0;
    func_00162C30(cam, eye, target, &x, 0);
    func_00161790(x, u, cam, eye, target, 0);
    for (k = 0; k < 4; k++) {
        F32(obj, 0x1C0 + k * 4) = eye[k];
        F32(obj, 0x1D0 + k * 4) = target[k];
        F32(cam, 0x90 + k * 4) = target[k];
        F32(cam, 0xB0 + k * 4) = target[k];
        F32(cam, 0xC0 + k * 4) = eye[k];
    }
    F32(cam, 0x10) = eye[1];
    cam[10] = 0;
    cam[0xC] = 0;
    cam[0xB] = 0;
    cam[8] = 0;
    cam[9] = 0;
    func_0017C0D0((unsigned int *)(cam + 0x10));
    for (k = 0; k < 0x1E; k++)
        func_00164440(1.0f, 50.0f, cam);
}

/* 0x00162130, 0x118 bytes. Turns the camera to behind the unit (in 30 frames): by its model's
 * facing, or its yaw when mounted or in actions with flag 8. */
void func_00162130(int *cam)
{
    Unit *u = (Unit *)PS2_PTR(cam[1]);
    float y;

    cam[6] = 0x1E;
    if ((U32(ACT(u), 0x1C) & 8) == 0 && (U32(ACT((Unit *)PS2_PTR(cam[1])), 0x18) & 0x8000000) == 0)
        y = func_00161600(u) + PI;
    else
        y = F32(u, 0x54) + PI;
    if (PI < y)
        y -= TWO_PI;
    F32(cam, 8) = y;
}

/* A ray (or swept sphere) test against the scenery (func_001F3930). */
typedef struct {
    float *from;
    float *to;
    void *who;
    float radius;
    float range;
    u32 pad;
    u32 result;              /* +0x18: low byte hit, bit 0x8000 a soft hit */
    float height;            /* +0x1C: the ceiling met */
    float hit[4];            /* +0x20 */
    float normal[4];         /* +0x30 */
} Ray;

extern float g_0045CE88;                 /* (small data) the height offset's rate */

void func_001F3930(Ray *r);
float func_0029DD90(float a, float b, float c, float d, float e);
void vu0_rot_y(float m[4][4], float yaw);        /* VU0 micro subroutine 0x70 */

/* A test from `from` to `to` (radius 30, range 100). */
static inline void ray_test(Ray *r, float *from, float *to)
{
    r->from = from;
    r->to = to;
    r->who = 0;
    r->radius = 30.0f;
    r->range = 100.0f;
    func_001F3930(r);
}

/* `v` turned by `yaw` about Y (the scratchpad's unit matrix rotated). */
static inline void turn_y(float *out, float yaw, const float *v)
{
    float m[4][4];
    int i, k;

    for (i = 0; i < 4; i++)
        for (k = 0; k < 4; k++)
            m[i][k] = ((float *)PS2_PTR(0x70000000))[i * 4 + k];
    vu0_rot_y(m, yaw);
    for (k = 0; k < 4; k++)
        out[k] = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2] + m[3][k] * v[3];
}

/* 0x00162250, 0x488 bytes. The camera's target this frame (*out): the unit's point, lowered by
 * the height; the height offset (+0x14) moved by how much the unit runs across the view; the
 * target kept at +0x90 follows it outside a dead zone of (`mx`, `my`, `mz`) in view space
 * (150, 70, 50 during hits with flag 0x800; 100 high with flag 4). */
void func_00162250(float mx, float my, float mz, int *cam, float *out)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    Unit *u = (Unit *)PS2_PTR(cam[1]);
    float h, dt[4], view[4], d[4], v[4];
    u8 *hit;
    u32 f;
    int k;

    if (func_00161490(out, u) == 0) {
        for (k = 0; k < 4; k++)
            out[k] = F32(obj, 0x1D0 + k * 4);
    }
    h = (U32(ACT((Unit *)PS2_PTR(cam[1])), 0x18) & 0x8000000) == 0 ? g_0045D568 : g_0045CE64;
    if (g_00669F60 & 2)
        h = h + 50.0f;
    out[1] = out[1] - h;
    hit = PTR(ACT((Unit *)PS2_PTR(cam[1])), 0x14);
    if (hit != 0 && (U16(hit, 0x1C) & 0x800)) {
        mx = 150.0f;
        my = 70.0f;
        mz = 50.0f;
    }
    if (BIT(cam, 0x3C, 2))
        my = 100.0f;
    for (k = 0; k < 4; k++) {
        dt[k] = out[k] - F32(obj, 0x1D0 + k * 4);
        view[k] = F32(obj, 0x1D0 + k * 4) - F32(obj, 0x1C0 + k * 4);
    }
    f = U32(ACT((Unit *)PS2_PTR(cam[1])), 0x18);
    if (PTR(ACT((Unit *)PS2_PTR(cam[1])), 0x14) == 0 && (f & 0x40) == 0 && (f & 0x400) == 0) {
        if (1.0f < dt[0] * dt[0] + dt[2] * dt[2] && (f & 0x80)) {
            float a[4] = { dt[0], 0.0f, dt[2], dt[3] }, b[4] = { view[0], 0.0f, view[2], view[3] };
            float la = sqrtf(a[0] * a[0] + a[2] * a[2] + a[3] * a[3]);
            float lb = sqrtf(b[0] * b[0] + b[2] * b[2] + b[3] * b[3]);
            float s = F32(cam, 0x14) - g_0045CE88 * ((a[0] * b[0] + a[2] * b[2] + a[3] * b[3])
                                                     / (la * lb));
            float lim;

            F32(cam, 0x14) = s < 0.0f ? s : 0.0f;
            lim = (g_00669F60 & 2) ? g_0045CE84 * 0.3f : g_0045CE84;
            if (F32(cam, 0x14) < -lim)
                F32(cam, 0x14) = -lim;
        }
    } else {
        float s = F32(cam, 0x14), r = g_0045CE88 * 2.0f;

        if (r < s)
            F32(cam, 0x14) = s - r;
        else if (s < -r)
            F32(cam, 0x14) = s + r;
        else
            F32(cam, 0x14) = 0.0f;
    }
    {
        float yaw = vu0_angle(view[0], view[2]);

        for (k = 0; k < 4; k++)
            d[k] = out[k] - F32(cam, 0x90 + k * 4);
        turn_y(v, yaw * -1.0f, d);
        func_0029DE30(mx, my, mz, v);
        turn_y(d, yaw, v);
    }
    for (k = 0; k < 4; k++) {
        F32(cam, 0x90 + k * 4) = F32(cam, 0x90 + k * 4) + d[k];
        out[k] = F32(cam, 0x90 + k * 4);
    }
}

/* 0x001626E0, 0x158 bytes. Moves the camera object's target and eye towards `t` / `e` by the
 * smoothing helper (rates `a` / `b` over `d`); far from each other (more than 100), the eye's
 * height follows by its own rate `c`. The positions are kept for the next frame. */
void func_001626E0(int *cam, float *t, float *e, float a, float b, float c, float d)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    float nt[4], ne[4], x, z;
    int k;

    func_0029DD40(a, d, PS2_ADDR(nt), PS2_ADDR(t), PS2_ADDR(&F32(cam, 0xB0)), PS2_ADDR(&F32(obj, 0x1D0)));
    func_0029DD40(b, d, PS2_ADDR(ne), PS2_ADDR(e), PS2_ADDR(&F32(cam, 0xC0)), PS2_ADDR(&F32(obj, 0x1C0)));
    x = ne[0] - nt[0];
    z = ne[2] - nt[2];
    if (!(x * x + z * z <= 10000.0f))
        ne[1] = func_0029DD90(e[1], F32(cam, 0x10), F32(obj, 0x1C4), c, d);
    for (k = 0; k < 4; k++) {
        F32(cam, 0xB0 + k * 4) = t[k];
        F32(cam, 0xC0 + k * 4) = e[k];
    }
    F32(cam, 0x10) = e[1];
    for (k = 0; k < 4; k++) {
        F32(obj, 0x1C0 + k * 4) = ne[k];
        F32(obj, 0x1D0 + k * 4) = nt[k];
    }
}

/* The length of a vector (x, y, z). */
static inline float len3(const float *v)
{
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/* 0x00162840, 0x2B8 bytes. Looks for a free place for the eye when the scenery is in the way:
 * straight behind the unit at the same distance, or (if that is blocked) beside the obstacle
 * along its surface; the offset found goes to +0xD0 and is used for 15 frames (+0x36). */
int func_00162840(int *cam, float *eye, float *target)
{
    Unit *u = (Unit *)PS2_PTR(cam[1]);
    float d[4], back[4], p[4], q[4], dist;
    Ray r1, r2;
    int k;

    for (k = 0; k < 4; k++)
        d[k] = target[k] - eye[k];
    dist = len3(d);
    for (k = 0; k < 4; k++)
        back[k] = F32(u, 0x70 + k * 4) * (dist * -1.0f);
    for (k = 0; k < 4; k++)
        p[k] = back[k] + target[k];
    ray_test(&r1, target, p);
    if ((u8)r1.result == 0) {
        for (k = 0; k < 4; k++) {
            F32(cam, 0xD0 + k * 4) = back[k];
            q[k] = F32(cam, 0xD0 + k * 4) + target[k];
        }
        ray_test(&r2, q, eye);
        if ((u8)r2.result == 0) {
            U16(cam, 0x36) = 0xF;
            return 1;
        }
    } else {
        float c1[4], c2[4], l;
        float *n = r1.normal;

        c1[0] = d[1] * n[2] - d[2] * n[1];
        c1[1] = d[2] * n[0] - d[0] * n[2];
        c1[2] = d[0] * n[1] - d[1] * n[0];
        c1[3] = 0.0f;
        c2[0] = c1[1] * n[2] - c1[2] * n[1];
        c2[1] = c1[2] * n[0] - c1[0] * n[2];
        c2[2] = c1[0] * n[1] - c1[1] * n[0];
        c2[3] = 0.0f;
        l = len3(c2);
        for (k = 0; k < 4; k++) {
            back[k] = c2[k] / l * dist;
            p[k] = back[k] + target[k];
        }
        ray_test(&r1, target, p);
        if ((u8)r1.result == 0) {
            for (k = 0; k < 4; k++) {
                F32(cam, 0xD0 + k * 4) = back[k];
                q[k] = F32(cam, 0xD0 + k * 4) + target[k];
            }
            ray_test(&r2, q, eye);
            if ((u8)r2.result == 0) {
                U16(cam, 0x36) = 0xF;
                return 1;
            }
        }
    }
    U16(cam, 0x36) = 0;
    return 0;
}

/* 0x00162B00, 0x124 bytes. Pulls the eye in to where the ray hit the scenery; *closeness =
 * 1 - distance / the camera's distance (0 to 1); the height offset eases back by 5. */
void func_00162B00(int *cam, float *eye, float *target, Ray *r, float *closeness)
{
    float d = func_00161D90(F32(cam, 0xC), (Unit *)PS2_PTR(cam[1]), 0), v[4], c;
    int k;

    for (k = 0; k < 4; k++) {
        eye[k] = r->hit[k];
        v[k] = eye[k] - target[k];
    }
    c = 1.0f - len3(v) / d;
    if (1.0f <= c)
        c = 1.0f;
    *closeness = c < 0.0f ? 0.0f : c;
    c = F32(cam, 0x14);
    if (5.0f < c)
        F32(cam, 0x14) = c - 5.0f;
    else if (c < -5.0f)
        F32(cam, 0x14) = c + 5.0f;
    else
        F32(cam, 0x14) = 0.0f;
}

/* 0x00162C30, 0x418 bytes. Keeps the scenery out of the view: the target pulled back to the
 * unit if a wall stands between; the free place found earlier followed for its 15 frames (the
 * eye moved there by at most 60 a frame, until the view turns less than 2 degrees); else the eye
 * pulled in in front of the obstacle (`free`: first look for a free place). Whether something
 * was in the way; *closeness for the pull. */
int func_00162C30(int *cam, float *eye, float *target, float *closeness, int free)
{
    float p[4];
    Ray r;
    int k;

    *closeness = 0.0f;
    if (BIT(cam, 0x3C, 1)) {
        U16(cam, 0x36) = 0;
        return 0;
    }
    if (func_00161490(p, (Unit *)PS2_PTR(cam[1])) == 0) {
        for (k = 0; k < 4; k++)
            p[k] = F32((u8 *)PS2_PTR(cam[0]), 0x1D0 + k * 4);
    }
    ray_test(&r, p, target);
    if ((u8)r.result != 0 && (r.result & 0x8000) == 0) {
        for (k = 0; k < 4; k++)
            target[k] = p[k];
    }
    if (free == 0)
        U16(cam, 0x36) = 0;
    if (U16(cam, 0x36) != 0) {
        float a[4], d[4], len, a1, a2, x;

        for (k = 0; k < 4; k++) {
            a[k] = F32(cam, 0xD0 + k * 4) + target[k];
            d[k] = target[k] - eye[k];
        }
        len = len3(d);
        if (60.0f < len) {
            for (k = 0; k < 4; k++)
                eye[k] = d[k] / len * 60.0f + eye[k];
        } else {
            for (k = 0; k < 4; k++)
                eye[k] = a[k];
        }
        ray_test(&r, target, eye);
        if ((u8)r.result == 0)
            U16(cam, 0x36) -= 1;
        a1 = vu0_angle(target[0] - a[0], target[2] - a[2]);
        a2 = vu0_angle(target[0] - eye[0], target[2] - eye[2]);
        x = a1 - a2;
        if (PI < x)
            x -= TWO_PI;
        else if (x < -PI)
            x += TWO_PI;
        if (fabsf(x) < 0.034906585f) {
            U16(cam, 0x36) = 0;
            return 1;
        }
    }
    {
        float d[4];

        for (k = 0; k < 4; k++)
            d[k] = target[k] - eye[k];
        if (d[0] * d[0] + d[1] * d[1] + d[2] * d[2] < 0.0001f)
            return 0;
    }
    ray_test(&r, target, eye);
    if ((u8)r.result == 0 || (r.result & 0x8000))
        return 0;
    if (free == 0 || func_00162840(cam, eye, target) == 0)
        func_00162B00(cam, eye, target, &r, closeness);
    return 1;
}

/* A ground probe (func_001F2BF0): the area under a point. */
typedef struct {
    float *pos;
    u32 pad[6];
    u8 area;                 /* +0x1C */
    u8 pad2[0x23];
} Probe;

extern float g_0045CE74, g_0045CE78, g_0045CE7C;   /* (small data) the target's dead zone */

float func_0029DDE0(float cur, float prev, float want, float rate, float dt);

/* Wraps an angle into -pi..pi (one turn at most). */
static inline float wrap1(float a)
{
    if (PI < a)
        a -= TWO_PI;
    else if (a < -PI)
        a += TWO_PI;
    return a;
}

/* 0x00163050, 0x328 bytes. The camera turning to a set yaw (+8) around the target: the eye's
 * direction from the target eased towards the yaw (rate 4), at the camera's distance (+0xC);
 * the turn timer (+0x18) runs out, or ends once within 5 degrees. */
void func_00163050(float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    float t[4], e[4], d[4], v[4], ang, want, left, close, len;
    int k, hit, pulled;

    func_00162250(g_0045CE74, g_0045CE78, g_0045CE7C, cam, t);
    for (k = 0; k < 4; k++)
        d[k] = F32(obj, 0x1C0 + k * 4) - F32(obj, 0x1D0 + k * 4);
    ang = vu0_angle(d[0], d[2]);
    want = func_0029DDE0(*(float *)&cam[2], *(float *)&cam[2], ang, 4.0f, dt);
    left = wrap1(*(float *)&cam[2] - ang);
    turn_y(v, wrap1(want - ang), d);
    len = len3(v);
    for (k = 0; k < 4; k++)
        e[k] = t[k] + v[k] / len * *(float *)&cam[3];
    hit = func_00162C30(cam, e, t, &close, 0);
    pulled = func_00161790(close, (Unit *)PS2_PTR(cam[1]), cam, e, t, 0);
    func_001626E0(cam, t, e, 6.0f, 6.0f, (hit == 0 && pulled == 0) ? 1.0f : 3.0f, dt);
    if (fabsf(left) < 0.08726647f)
        cam[6] = 0;
    else
        cam[6] = cam[6] - 1;
}

/* 0x00163380, 0x268 bytes. The usual camera: behind the unit along the flat line from the eye
 * to the target, at the camera's distance (1.25 times for actions with flag 1); eased at 2.5
 * (4 when mounted), or 5 when the scenery was in the way. */
void func_00163380(float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    float t[4], e[4], f[4], dist, len, close;
    int k, hit, pulled;

    *(float *)&cam[3] = func_00161D90(*(float *)&cam[3], (Unit *)PS2_PTR(cam[1]), 0);
    func_00162250(g_0045CE74, g_0045CE78, g_0045CE7C, cam, t);
    for (k = 0; k < 4; k++)
        f[k] = t[k] - F32(obj, 0x1C0 + k * 4);
    f[1] = 0.0f;
    len = len3(f);
    if (0.0001f < len) {
        for (k = 0; k < 4; k++)
            f[k] = f[k] / len;
    }
    dist = *(float *)&cam[3];
    if (U32(ACT((Unit *)PS2_PTR(cam[1])), 0x1C) & 1)
        dist = dist * 1.25f;
    for (k = 0; k < 3; k++)
        e[k] = f[k] * (dist * -1.0f) + t[k];
    e[3] = 1.0f;
    hit = func_00162C30(cam, e, t, &close, 1);
    pulled = func_00161790(close, (Unit *)PS2_PTR(cam[1]), cam, e, t, 0);
    if (hit == 0 && pulled == 0) {
        if ((U32(ACT((Unit *)PS2_PTR(cam[1])), 0x18) & 0x8000000) == 0)
            func_001626E0(cam, t, e, 2.5f, 2.5f, 1.0f, dt);
        else
            func_001626E0(cam, t, e, 4.0f, 4.0f, 1.0f, dt);
    } else {
        func_001626E0(cam, t, e, 5.0f, 5.0f, 3.0f, dt);
    }
}

/* 0x001635F0, 0x1BC bytes. The camera straight behind the unit's facing (func_00161520), for
 * actions that keep their direction; the height offset eases back to 0. */
void func_001635F0(float dt, int *cam)
{
    Unit *u = (Unit *)PS2_PTR(cam[1]);
    float t[4], e[4], f[4], s, r, close;
    int hit, pulled;

    *(float *)&cam[3] = func_00161D90(*(float *)&cam[3], u, 0);
    func_00162250(g_0045CE74, g_0045CE78, g_0045CE7C, cam, t);
    s = F32(cam, 0x14);
    r = g_0045CE88 * 2.0f;
    if (r < s)
        F32(cam, 0x14) = s - r;
    else if (s < -r)
        F32(cam, 0x14) = s + r;
    else
        F32(cam, 0x14) = 0.0f;
    func_00161520(f, u);
    s = -*(float *)&cam[3];
    e[0] = f[0] * s + t[0] + 0.0f;
    e[1] = f[1] * s + t[1] + 0.0f;
    e[2] = f[2] * s + t[2] + 0.0f;
    e[3] = 1.0f;
    hit = func_00162C30(cam, e, t, &close, 0);
    pulled = func_00161790(close, (Unit *)PS2_PTR(cam[1]), cam, e, t, 1);
    if (hit == 0 && pulled == 0)
        func_001626E0(cam, t, e, 2.5f, 2.5f, 0.5f, dt);
    else
        func_001626E0(cam, t, e, 5.0f, 5.0f, 3.0f, dt);
}

/* 0x001637B0, 0x270 bytes. The battle camera each frame: the mode for the unit's action (none
 * with flag 0x8000; turning while the timer +0x18 runs; behind the facing for actions with flag
 * 8, or 0x20000 / 0x100 kept from the previous action +0x1C; else the usual one); the view angle
 * (15 degrees, 10 with two players); then, if the eye went through the scenery, the eye kept
 * under the ceiling when it stays in the target's area. */
void func_001637B0(float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    u8 *act = ACT((Unit *)PS2_PTR(cam[1]));
    float old[4], q[4];
    Ray r;
    int k;

    for (k = 0; k < 4; k++)
        old[k] = F32(obj, 0x1C0 + k * 4);
    if ((U32(act, 0x1C) & 0x8000) == 0) {
        if (cam[6] != 0) {
            func_00163050(dt, cam);
        } else if (act != 0 && (U32(act, 0x1C) & 8)) {
            func_00162130(cam);
        } else if (act == 0 || ((U32(act, 0x18) & 0x20000) == 0 && (U32(act, 0x18) & 0x100) == 0)) {
            func_00163380(dt, cam);
        } else if (cam[7] == 0 || ((U32(cam[7], 0x18) & 0x20000) == 0
                                   && (U32(cam[7], 0x18) & 0x100) == 0)) {
            func_00162130(cam);
        } else {
            func_001635F0(dt, cam);
        }
    }
    F32(obj, 0x224) = (g_00669F60 & 2) == 0 ? 0.2617994f : 0.17453294f;
    F32(obj, 0x220) = 0.0f;
    cam[7] = (int)PS2_ADDR(act);
    if (BIT(cam, 0x3C, 1) && (U32(act, 0x18) & 0x20) == 0)
        BIT(cam, 0x3C, 1) = 0;
    r.from = old;
    r.to = &F32(obj, 0x1C0);
    r.who = 0;
    r.radius = 30.0f;
    r.range = 100.0f;
    BIT(cam, 0x3C, 2) = 0;
    func_001F3930(&r);
    if (r.result & 0x100) {
        Probe p;
        u8 area;

        for (k = 0; k < 4; k++)
            q[k] = F32(obj, 0x1C0 + k * 4);
        q[1] = q[1] + 100.0f;
        p.pos = q;
        func_001F2BF0((unsigned char *)(&p));
        area = p.area;
        p.pos = &F32(obj, 0x1D0);
        func_001F2BF0((unsigned char *)(&p));
        if (area == p.area) {
            float y = old[1] + 6.0f;

            F32(obj, 0x1C4) = y < r.height ? y : r.height;
        }
        BIT(cam, 0x3C, 2) = 1;
    }
}

typedef struct MotionState MotionState;

extern float g_004064B0[3][2];           /* view angle and +0x220 of the three two-unit views */

void func_0029EC70(float dt, int *cam);

/* The matrix of rotation `rot` and position `pos` (VU0 micro subroutine 0x50) into m. */
#ifdef SW2E_PC
#define CAM_MATRIX(m, rot, pos) sw2e_vu0_matrix((float *)(m), (const float *)(rot), (const float *)(pos))
#else
#define CAM_MATRIX(m, rot, pos)                                         \
    __asm__ volatile("lqc2 $vf1, 0(%1)\n"                               \
                     "lqc2 $vf2, 0(%2)\n"                               \
                     "vcallms 0x50\n"                                   \
                     "qmfc2.i $9, $vf1\n"                               \
                     "sqc2 $vf16, 0x00(%0)\n"                           \
                     "sqc2 $vf17, 0x10(%0)\n"                           \
                     "sqc2 $vf18, 0x20(%0)\n"                           \
                     "sqc2 $vf19, 0x30(%0)\n"                           \
                     : : "r"(m), "r"(rot), "r"(pos) : "$9", "memory")
#endif

/* 0x00163A20, 0x17C bytes. The camera looking down at the unit's point (+0x90) from 300 away
 * along the flat line from it, at least 200 above it and 50 above the ground (Y points down);
 * eased at 0.25; the eye kept in front of the scenery. */
void func_00163A20(float dt, int *cam)
{
    u8 *u = (u8 *)PS2_PTR(cam[1]), *obj = (u8 *)PS2_PTR(cam[0]);
    float t[4], d[4], e[4], h, len;
    Ray r;
    int k;

    for (k = 0; k < 4; k++) {
        t[k] = F32(u, 0x90 + k * 4);
        d[k] = F32(obj, 0x1C0 + k * 4) - F32(u, 0x90 + k * 4);
    }
    d[1] = 0.0f;
    len = len3(d);
    for (k = 0; k < 4; k++)
        e[k] = F32(u, 0x90 + k * 4) + d[k] / len * 300.0f;
    e[1] = F32(obj, 0x1C4);
    h = func_0029DEF0(e, 0) - 50.0f;
    if (t[1] - 200.0f <= h)
        h = t[1] - 200.0f;
    e[1] = h;
    func_001626E0(cam, t, e, 0.25f, 0.25f, 0.25f, dt);
    ray_test(&r, &F32(obj, 0x1D0), &F32(obj, 0x1C0));
    if ((u8)r.result != 0) {
        for (k = 0; k < 4; k++)
            F32(obj, 0x1C0 + k * 4) = r.hit[k];
    }
}

/* 0x00163BA0, 0x35C bytes. The camera on two units (+4 and +0x2C): the target halfway between
 * them, 100 above the ground; the eye 400 to the side of the line between them, on the side
 * nearer the eye (the other one if the scenery is in the way), at least 50 above the ground. */
void func_00163BA0(float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]), *a = (u8 *)PS2_PTR(cam[1]), *b = (u8 *)PS2_PTR(cam[0xB]);
    float half[4], mid[4], side[4], p[4], q[4], e[4], da, db, l, h;
    Ray r;
    int k;

    for (k = 0; k < 4; k++) {
        half[k] = (F32(a, 0x90 + k * 4) - F32(b, 0x90 + k * 4)) * 0.5f;
        mid[k] = half[k] + F32(b, 0x90 + k * 4);
    }
    mid[1] = func_0029DEF0(mid, 1) - 100.0f;
    side[0] = half[1] * g_00424D00[2] - half[2] * g_00424D00[1];
    side[1] = half[2] * g_00424D00[0] - half[0] * g_00424D00[2];
    side[2] = half[0] * g_00424D00[1] - half[1] * g_00424D00[0];
    side[3] = 0.0f;
    l = len3(side);
    for (k = 0; k < 4; k++) {
        side[k] = side[k] / l;
        p[k] = side[k] * 400.0f + mid[k];
        q[k] = side[k] * -400.0f + mid[k];
    }
    da = (F32(obj, 0x1C0) - p[0]) * (F32(obj, 0x1C0) - p[0])
         + (F32(obj, 0x1C8) - p[2]) * (F32(obj, 0x1C8) - p[2]);
    db = (F32(obj, 0x1C0) - q[0]) * (F32(obj, 0x1C0) - q[0])
         + (F32(obj, 0x1C8) - q[2]) * (F32(obj, 0x1C8) - q[2]);
    if (da < db) {
        ray_test(&r, mid, p);
        for (k = 0; k < 4; k++)
            e[k] = (u8)r.result == 0 ? p[k] : q[k];
    } else {
        ray_test(&r, mid, q);
        for (k = 0; k < 4; k++)
            e[k] = (u8)r.result == 0 ? q[k] : p[k];
    }
    ray_test(&r, mid, e);
    if ((u8)r.result != 0) {
        for (k = 0; k < 4; k++)
            e[k] = F32(obj, 0x1C0 + k * 4);
    }
    h = func_0029DEF0(e, 1) - 50.0f;
    if (h < e[1])
        e[1] = h;
    func_001626E0(cam, mid, e, 1.0f, 1.0f, 1.0f, dt);
}

/* 0x00163F00, 0x368 bytes. A camera played from a motion (+0x28, frame +0x30): eye and target
 * (components 9-14) placed by the rotation +0xA0 and position +0x90, the view angle and +0x220
 * (15, 16); kept 50 above the ground. When the scenery stands between the unit and the eye or
 * the target, the camera goes back to where it was and the motion ends; it also ends with its
 * last frame. The unit (and +0x270) gets flag 8 at +0x199 meanwhile. */
void func_00163F00(float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    float t0[4], e0[4], m[4][4], o[8], v[4], h;
    int k, cut = 0;
    Ray r;

    for (k = 0; k < 4; k++) {
        t0[k] = F32(obj, 0x1D0 + k * 4);
        e0[k] = F32(obj, 0x1C0 + k * 4);
    }
    func_001479D0(*(float *)&cam[0xC], (MotionState *)PS2_PTR(cam[0xA]), o);
    CAM_MATRIX(m, &cam[0x28], &cam[0x24]);
    v[0] = o[0];
    v[1] = o[1];
    v[2] = o[2];
    v[3] = 0.0f;
    for (k = 0; k < 4; k++)
        F32(obj, 0x1C0 + k * 4) = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2]
                                  + m[3][k] * v[3] + *(float *)&cam[0x24 + k];
    v[0] = o[3];
    v[1] = o[4];
    v[2] = o[5];
    v[3] = 0.0f;
    for (k = 0; k < 4; k++)
        F32(obj, 0x1D0 + k * 4) = m[0][k] * v[0] + m[1][k] * v[1] + m[2][k] * v[2]
                                  + m[3][k] * v[3] + *(float *)&cam[0x24 + k];
    F32(obj, 0x224) = o[6];
    F32(obj, 0x220) = o[7];
    func_0029EC70(dt, cam);
    h = func_0029DEF0(&F32(obj, 0x1C0), 1) - 50.0f;
    if (h < F32(obj, 0x1C4))
        F32(obj, 0x1C4) = h;
    if (cam[1] != 0) {
        u8 *u = (u8 *)PS2_PTR(cam[1]);
        int pass;

        for (pass = 0; pass < 2; pass++) {
            r.from = &F32(u, 0x90);
            r.to = pass == 0 ? &F32(obj, 0x1D0) : &F32(obj, 0x1C0);
            r.who = 0;
            r.radius = 30.0f;
            r.range = 0.0f;
            func_001F3930(&r);
            if ((u8)r.result != 0) {
                cut = 1;
                F32(obj, 0x224) = (g_00669F60 & 2) == 0 ? 0.2617994f : 0.17453294f;
                F32(obj, 0x220) = 0.0f;
                for (k = 0; k < 4; k++) {
                    F32(obj, 0x1D0 + k * 4) = t0[k];
                    F32(obj, 0x1C0 + k * 4) = e0[k];
                }
            }
        }
        BIT(u, 0x199, 3) = 1;
        if (PTR(u, 0x270) != 0)
            BIT(PTR(u, 0x270), 0x199, 3) = 1;
    }
    *(float *)&cam[0xC] = *(float *)&cam[0xC] + dt;
    if (cut || (float)(S32(PS2_LOADP(u8 *, PS2_PTR(cam[0xA])), 8) - 1) < *(float *)&cam[0xC]) {
        cam[0xA] = 0;
        cam[0xC] = 0;
    }
}

/* 0x00164270, 0x1C4 bytes. The camera between two units (+0x20, +0x24), from a set eye (+0xE0):
 * the target halfway between them (on the second with flag 1), jumping there when it is more
 * than 400 away; the view angle from a table of three (indexed by the second unit's address,
 * as in the original). The first float argument is not used. */
void func_00164270(float unused, float dt, int *cam)
{
    u8 *obj = (u8 *)PS2_PTR(cam[0]);
    float t[4], d[4];
    int k;

    if (cam[8] == 0 || cam[9] == 0)
        return;
    for (k = 0; k < 4; k++) {
        if (BIT(cam, 0x3C, 0))
            t[k] = F32(cam[9], 0x90 + k * 4);
        else
            t[k] = (F32(cam[8], 0x90 + k * 4) - F32(cam[9], 0x90 + k * 4)) * 0.5f
                   + F32(cam[9], 0x90 + k * 4);
    }
    func_001626E0(cam, t, &F32(cam, 0xE0), 0.25f, 1.0f, 1.0f, dt);
    for (k = 0; k < 4; k++)
        d[k] = F32(obj, 0x1D0 + k * 4) - t[k];
    if (160000.0f < d[0] * d[0] + d[2] * d[2]) {
        for (k = 0; k < 4; k++) {
            F32(obj, 0x1D0 + k * 4) = t[k];
            F32(cam, 0xB0 + k * 4) = t[k];
        }
    }
    for (k = 0; k < 4; k++)
        F32(obj, 0x1C0 + k * 4) = F32(cam, 0xE0 + k * 4);
    if (BIT(cam, 0x3C, 0) == 0) {
        F32(obj, 0x224) = g_004064B0[cam[9] % 3][0];
        F32(obj, 0x220) = g_004064B0[cam[9] % 3][1];
    }
}

extern int g_0045D2A8;                   /* (small data) non-zero: slow motion (the duel view) */
extern int g_0045CC80;                   /* (small data) */
extern int g_0045D2C8;                   /* (small data) */

void func_0029EE00(int *cam, int a);
void func_001FAA60(u8 player);

/* 0x00164440, 0x240 bytes. The battle camera's update: the shake (+0x40, offsets +0x60 eye,
 * +0x80 target) taken out, the view for the situation (looking down at a beaten unit; between two
 * units +0x2C; a motion; the slow-motion duel view; else the usual dispatcher), then the shake
 * advanced and put back. Byte +0x230 of the camera object gets flag 2 for the special views. */
void func_00164440(float step, float dt, int *cam)
{
    int k;

#define CAM_OBJ ((u8 *)PS2_PTR(cam[0]))
    if (cam[0x10] != 0) {
        for (k = 0; k < 4; k++) {
            F32(CAM_OBJ, 0x1C0 + k * 4) = F32(CAM_OBJ, 0x1C0 + k * 4) - F32(cam, 0x60 + k * 4);
            F32(CAM_OBJ, 0x1D0 + k * 4) = F32(CAM_OBJ, 0x1D0 + k * 4) - F32(cam, 0x80 + k * 4);
        }
    }
    if (func_0016C070((Unit *)PS2_PTR(cam[1])) != 0) {
        g_0045D2A8 = 0;
        func_00254030();
        func_00163A20(dt, cam);
        BIT(CAM_OBJ, 0x230, 1) = 1;
    } else if (cam[0xB] != 0) {
        g_0045CC80 = 8;
        g_0045D2C8 = 0;
        func_00163BA0(dt, cam);
        BIT(CAM_OBJ, 0x230, 1) = 1;
        if (BIT(cam[0xB], 0x27C, 2) == 0) {
            func_0029EE00(cam, 0);
            if (cam[1] != 0)
                func_001FAA60(U8(cam[1], 0x14E));
        }
    } else if (cam[0xA] != 0) {
        g_0045CC80 = 8;
        g_0045D2C8 = 0;
        func_00163F00(step, cam);
        BIT(CAM_OBJ, 0x230, 1) = 1;
    } else if (g_0045D2A8 != 0) {
        g_0045CC80 = 8;
        g_0045D2C8 = 0;
        func_00164270(step, dt, cam);
        BIT(CAM_OBJ, 0x230, 1) = 1;
    } else {
        func_001637B0(dt, cam);
        BIT(CAM_OBJ, 0x230, 1) = 0;
    }
    if (cam[0x10] != 0) {
        func_0017C230((unsigned int *)(&cam[0x10]));
        for (k = 0; k < 4; k++) {
            F32(CAM_OBJ, 0x1C0 + k * 4) = F32(CAM_OBJ, 0x1C0 + k * 4) + F32(cam, 0x60 + k * 4);
            F32(CAM_OBJ, 0x1D0 + k * 4) = F32(CAM_OBJ, 0x1D0 + k * 4) + F32(cam, 0x80 + k * 4);
        }
    }
#undef CAM_OBJ
}
