/*
 * pc_hw.c - the PC side of src/sw2e_pc.h: the VU0 micro subroutines and the interrupt calls
 * the decompiled code uses inline on the PS2.
 *
 * The matrix order (T x Rz x Ry x Rx, rows stored with the translation last) is the one that
 * poses the game's characters correctly (docs/formats/PS2MODEL.md). It still has to be checked
 * against the VU0 microcode itself, which is not decompiled yet.
 */
#include <math.h>
#include "upp.h"

extern const upp_platform *sw2e_platform;

static void rotation(float *m, const float *rot)
{
    float cx = cosf(rot[0]), sx = sinf(rot[0]);
    float cy = cosf(rot[1]), sy = sinf(rot[1]);
    float cz = cosf(rot[2]), sz = sinf(rot[2]);
    /* column-vector R = Rz * Ry * Rx */
    float r[3][3] = {
        { cz * cy, cz * sy * sx - sz * cx, cz * sy * cx + sz * sx },
        { sz * cy, sz * sy * sx + cz * cx, sz * sy * cx - cz * sx },
        { -sy, cy * sx, cy * cx },
    };
    int i, k;

    /* the PS2 keeps row vectors: row i holds column i of R */
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 3; k++)
            m[i * 4 + k] = r[k][i];
        m[i * 4 + 3] = 0.0f;
    }
    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
}

void sw2e_vu0_rotation(float *m, const float *rot)
{
    rotation(m, rot);
}

void sw2e_vu0_matrix(float *m, const float *rot, const float *pos)
{
    rotation(m, rot);
    m[12] = pos[0];
    m[13] = pos[1];
    m[14] = pos[2];
    m[15] = 1.0f;
}

/* Stand-ins the decompiled code declares for VU0 micro subroutines (to check against the VU0
 * microcode): 0x30 the angle of (x, z), 0x20 sine and cosine, 0x70 a turn about the Y axis
 * applied after a matrix (rows: v' = v * m * Ry). */
float vu0_angle(float x, float z)
{
    return atan2f(x, z);
}

void vu0_sincos(float a, float *s, float *c)
{
    *s = sinf(a);
    *c = cosf(a);
}

void vu0_rotate(float out[4][4], float in[4][4], float angle)
{
    float c = cosf(angle), s = sinf(angle), t[4][4];
    int i;

    for (i = 0; i < 4; i++) {
        t[i][0] = in[i][0] * c + in[i][2] * s;
        t[i][1] = in[i][1];
        t[i][2] = -in[i][0] * s + in[i][2] * c;
        t[i][3] = in[i][3];
    }
    for (i = 0; i < 4; i++) {
        out[i][0] = t[i][0];
        out[i][1] = t[i][1];
        out[i][2] = t[i][2];
        out[i][3] = t[i][3];
    }
}

void vu0_rot_y(float m[4][4], float yaw)
{
    vu0_rotate(m, m, yaw);
}

/* 0x60: a turn about the X axis applied after a matrix */
void vu0_rot_x(float m[4][4], float a)
{
    float c = cosf(a), s = sinf(a);
    int i;

    for (i = 0; i < 4; i++) {
        float y = m[i][1], z = m[i][2];

        m[i][1] = y * c - z * s;
        m[i][2] = y * s + z * c;
    }
}

float vu0_atan2(float y, float x) { return atan2f(y, x); }   /* 0x30 */
float vu0_cos(float a) { return cosf(a); }                     /* 0x10 */
float vu0_sin(float a) { return sinf(a); }                     /* 0x00 */

void sw2e_intr_enable(void)
{
    if (sw2e_platform)
        sw2e_platform->intr_enable();
}
