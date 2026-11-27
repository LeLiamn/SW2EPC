/*
 * camera.c - the battle camera (original source file unknown; from 0x00161490, after
 * scene_initialize.c).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. Units are reached by offset as in unit.c.
 *
 * The camera follows a unit from behind: its eye sits at a distance behind the unit's facing,
 * pitched up by an angle that follows the slope of the ground between the eye and the unit, and
 * is kept above the ground. The camera's state (an array of words) holds: +0 the 3D camera
 * object (eye at +0x1C0, target at +0x1D0), +4 the unit, +8 the yaw, +0xC the distance, +0x14
 * the height offset, +0x18 a timer, +0x38 the slope angle, +0x3C flags, +0x90 / +0xB0 / +0xC0
 * the targets and eye kept.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

#define U8(o, off)  (*(u8 *)((u8 *)(o) + (off)))
#define S16(o, off) (*(short *)((u8 *)(o) + (off)))
#define U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define U32(o, off) (*(u32 *)((u8 *)(o) + (off)))
#define S32(o, off) (*(int *)((u8 *)(o) + (off)))
#define F32(o, off) (*(float *)((u8 *)(o) + (off)))
#define PTR(o, off) (*(u8 **)((u8 *)(o) + (off)))

#define PI     3.1415927f
#define TWO_PI 6.2831855f

typedef u8 Unit;

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

float *func_0016A170(Unit *u, int node);
float func_0029DEF0(float *pos, int a);          /* the ground's height under `pos` */
void func_0029DF20(float angle, float m[4][4], float *axis);   /* a rotation about `axis` */
void func_00164DA0(Unit *u, int a);
void func_00178AC0(Unit *u);
void func_00166A00(Unit *u);
void func_001688D0(Unit *u);
void func_0014D560(u8 *actor, char mode, int n);
void func_00162C30(int *cam, float *eye, float *target, float *out, int a);
void func_0017C0D0(int *p);
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
    if (U8(cam, 0x3C) & 2) {
        eye[1] = F32(*(u8 **)cam, 0x1C4);
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

    if (m != 0 && (U8(u, 0x198) & 2)) {
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
    cam[0] = (int)obj;
    cam[1] = (int)u;
    cam[7] = 0;
    U16(cam, 0x36) = 0;
    cam[0xF] = 0;
    cam[0xE] = 0;
    U8(cam, 0x3C) &= ~4;
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
    func_0017C0D0(cam + 0x10);
    for (k = 0; k < 0x1E; k++)
        func_00164440(1.0f, 50.0f, cam);
}

/* 0x00162130, 0x118 bytes. Turns the camera to behind the unit (in 30 frames): by its model's
 * facing, or its yaw when mounted or in actions with flag 8. */
void func_00162130(int *cam)
{
    Unit *u = (Unit *)cam[1];
    float y;

    cam[6] = 0x1E;
    if ((U32(ACT(u), 0x1C) & 8) == 0 && (U32(ACT((Unit *)cam[1]), 0x18) & 0x8000000) == 0)
        y = func_00161600(u) + PI;
    else
        y = F32(u, 0x54) + PI;
    if (PI < y)
        y -= TWO_PI;
    F32(cam, 8) = y;
}
