/*
 * sw2e_pc.h - PC replacements for the PS2 hardware operations the decompiled code does inline
 * (VU0 macro code, interrupts). Only the PC build (SW2E_PC) uses them; the PS2 build keeps the
 * original inline assembly, so the code CodeWarrior generates does not change.
 * The functions are implemented in port/sw2e/pc_hw.c.
 */
#ifndef SW2E_PC_H
#define SW2E_PC_H

#ifdef SW2E_PC

/* VU0 micro subroutine 0x50: the matrix of rotation `rot` (x, y, z angles in radians) and
 * position `pos` into m (4 rows of 4 floats, translation in the last row). */
void sw2e_vu0_matrix(float *m, const float *rot, const float *pos);
/* VU0 micro subroutine 0x40: the rotation matrix of `rot` alone (no translation). */
void sw2e_vu0_rotation(float *m, const float *rot);
/* EI after an interrupt handler (sync.l; ei on the PS2). */
void sw2e_intr_enable(void);

#endif

#endif
