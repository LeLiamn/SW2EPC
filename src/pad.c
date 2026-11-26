/*
 * pad.c - the controllers (original source file unknown; 0x00103090-0x0010424C, after the
 * memory allocator). Built on the Sony pad library (libpad: func_001708A8 init, func_00170D00
 * open, func_001711C8 state, func_00171150 read, func_001717E0 actuators...).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * Two ports (g_00500700, 0x88 bytes each). Every frame (func_001038D0) each open pad goes
 * through libpad's set-up steps (analog mode locked, pressure mode, actuators), then its data is
 * read: the buttons (active low), the two sticks (a dead zone of radius 64 around the centre,
 * and the left stick as a D-pad when allowed), pressure values below 0x20 dropped. "Pressed" is
 * a button down this frame; "held" also repeats it every 4 frames after 16. Start + Select held
 * on any pad for 10 frames asks for a soft reset (g_0045D20C, see main.c).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* A controller (0x88 bytes). */
typedef struct {
    u8 *buffer;              /* +0x00 libpad's DMA buffer (0x00500500 + port * 0x100) */
    u8 raw[0x20];            /* +0x04 the data read: [1] the mode (0x41 digital, 0x73 analog,
                              * 0x79 with pressure), [2] [3] the buttons (active low), [4]-[7]
                              * the sticks (right x, y, left x, y), [8]-[19] the pressures */
    int state;               /* +0x24 libpad's state */
    u8 hold[16];             /* +0x28 per button: frames held (to 16) */
    u8 repeat[16];           /* +0x38 per button: frames since its last repeat */
    u16 now;                 /* +0x48 the buttons down */
    u16 prev;                /* +0x4A ... the frame before */
    u16 pressed;             /* +0x4C down this frame */
    u16 held;                /* +0x4E pressed or repeating */
    u16 vib_timer[2];        /* +0x50 per motor: frames left */
    u16 vib_sent;            /* +0x54 the motors' value last sent */
    u8 vib[2];               /* +0x56 per motor: its level */
    u8 unknown_58[4];
    u8 act_align[6];         /* +0x5C the actuators' alignment */
    u8 phase;                /* +0x62 the set-up step (4: none in progress) */
    u8 unknown_63;
    u8 flags;                /* +0x64 bit 0 open, 1 mode set, 2 vibration on, 3, 4 no stick
                              * D-pad, 5 pressure on, 6 pressure checked, 7 actuators set */
    u8 connected;            /* +0x65 bit 0: read this frame */
    u8 unknown_66[2];
    u8 previous[0x20];       /* +0x68 the data read the frame before */
} Pad;

extern Pad g_00500700[2];
extern u8 g_00500500[2][0x100];           /* libpad's DMA buffers */

#define PAD_READY(p) (((p)->flags & 1) ? ((p)->connected & 1) == 1 : 0)

extern int g_0045D20C;                    /* a soft reset asked (see main.c) */
extern int g_0045D210, g_0045D214;        /* (g_0045D214: the reset combination allowed) */
extern u8 g_0045D204;                     /* (small data) the ports to open (bit per port) */
extern int g_0045D208;                    /* (small data) frames left of Start + Select */

int func_001717E0(int port, int slot, u8 *levels);
int func_001711C8(int port, int slot);
int func_00171330(int port, int slot);
int func_00171728(int port, int slot, int a, int b);
int func_00171AE0(int port, int slot);
int func_00171B60(int port, int slot);
int func_001718A8(int port, int slot, u8 *align);
int func_00171150(int port, int slot, u8 *data);
void func_0011EB80(void *to, const void *from, int size);
void func_00118850(void *to, int size);
int func_00170D00(int port, int slot, u8 *buffer);
int func_00170EE8(int port, int slot);
int func_001708A8(int a);
void func_00171E18(int a);
int func_00170B38(void);

void func_00103510(Pad *p);

/* 0x00103090, 0xEC bytes. The vibration: sends the motors' levels when they changed (0 when
 * refused), then counts their frames down. */
int func_00103090(int port)
{
    Pad *p = &g_00500700[port];
    int i;

    if ((p->flags & 7) >> 2 == 1) {
        u16 value = p->vib[0] + p->vib[1] * 2;

        if (p->vib_sent != value) {
            if (func_001717E0(port, 0, p->vib) != 1)
                return 0;
            p->vib_sent = value;
        }
    }
    for (i = 0; i < 2; i++) {
        if (p->vib_timer[i] < 1)
            p->vib[i] = 0;
        else if (--p->vib_timer[i] == 0)
            p->vib[i] = 0;
    }
    return 1;
}

/* 0x00103180, 0xDC bytes. Pressed and held: a button held 16 frames repeats every 4. */
void func_00103180(Pad *p)
{
    int i;
    u16 bit = 1;
    u16 now, prev;

    p->pressed = p->now & (p->prev ^ 0xFFFF);
    p->held = p->pressed;
    now = p->now;
    prev = p->prev;
    for (i = 0; i < 16; i++, bit <<= 1) {
        if ((now & prev & bit) == 0) {
            p->hold[i] = 0;
            p->repeat[i] = 0;
        } else if (p->hold[i] < 0x10) {
            if (++p->hold[i] > 0x0F)
                p->held |= bit;
        } else if (++p->repeat[i] > 3) {
            p->held |= bit;
            p->repeat[i] = 0;
        }
    }
}

/* 0x00103260, 0x38 bytes, matching. Drops pressure values below 0x20. */
void func_00103260(Pad *p)
{
    int i;

    for (i = 8; i < 0x14; i++)
        if (p->raw[i] < 0x20)
            p->raw[i] = 0;
}

/* 0x001032A0, 0x18C bytes. The sticks: centred inside a radius of 64 (VU0: a dot product), and
 * the left stick as the D-pad unless bit 4 is set. */
void func_001032A0(Pad *p)
{
    float x, y;

    x = (float)(p->raw[4] - 0x80);
    y = (float)(p->raw[5] - 0x80);
    if ((int)(x * x + y * y + 0.0f) < 0x1000) {
        p->raw[4] = 0x80;
        p->raw[5] = 0x80;
    }
    x = (float)(p->raw[6] - 0x80);
    y = (float)(p->raw[7] - 0x80);
    if ((int)(x * x + y * y + 0.0f) < 0x1000) {
        p->raw[6] = 0x80;
        p->raw[7] = 0x80;
    }
    if ((p->flags & 0x1F) >> 4 == 1) {
        if (p->raw[6] < 0x40)
            p->now |= 0x8000;
        else if (p->raw[6] > 0xC0)
            p->now |= 0x2000;
        if (p->raw[7] < 0x40)
            p->now |= 0x1000;
        else if (p->raw[7] > 0xC0)
            p->now |= 0x4000;
    }
}

/* 0x00103430, 0x4C bytes. Takes a frame's data. */
void func_00103430(Pad *p)
{
    p->prev = p->now;
    p->now = (p->raw[2] ^ 0xFF) << 8 | (p->raw[3] ^ 0xFF);
    func_001032A0(p);
    func_00103260(p);
    func_00103180(p);
}

/* 0x00103480, 0x8C bytes. Clears the buttons, sticks, counters and motors. */
void func_00103480(Pad *p)
{
    int i;

    p->held = 0;
    p->pressed = 0;
    p->prev = 0;
    p->now = 0;
    p->raw[4] = 0x80;
    p->raw[5] = 0x80;
    p->raw[6] = 0x80;
    p->raw[7] = 0x80;
    for (i = 0; i < 0x10; i++) {
        p->hold[i] = 0;
        p->repeat[i] = 0;
    }
    p->vib[0] = 0;
    p->vib_timer[0] = 0;
    p->vib[1] = 0;
    p->vib_timer[1] = 0;
}

/* 0x00103510, 0x120 bytes. Resets a pad's state (its set-up starts again). */
void func_00103510(Pad *p)
{
    int i;

    p->flags &= 0xFD;
    p->flags &= 0xDF;
    p->flags = (p->flags & 0xF7) | 8;
    p->flags &= 0xBF;
    p->flags &= 0x7F;
    p->state = 0;
    p->phase = 4;
    for (i = 0; i < 0x20; i++)
        p->raw[i] = 0;
    p->raw[4] = 0x80;
    p->raw[5] = 0x80;
    p->raw[6] = 0x80;
    p->raw[7] = 0x80;
    p->act_align[0] = 0;
    p->act_align[1] = 1;
    p->act_align[2] = 0xFF;
    p->act_align[3] = 0xFF;
    p->act_align[4] = 0xFF;
    p->act_align[5] = 0xFF;
    p->vib[0] = 0;
    p->vib[1] = 0;
    p->unknown_58[0] = 0;
    p->unknown_58[1] = 0;
    p->unknown_58[2] = 0;
    p->unknown_58[3] = 0;
    func_00103480(p);
}

/* 0x00103630, 0x7C bytes. Starts motor `motor` (0 on / off, 1 a level) for `frames`. */
void func_00103630(int port, int motor, int level, u16 frames)
{
    Pad *p = &g_00500700[port];

    if (p->flags & 1) {
        p->vib_timer[motor] = frames;
        if (level < 1)
            p->vib[motor] = 0;
        else if (motor == 1)
            p->vib[1] = level;
        else if (motor == 0)
            p->vib[0] = 1;
    }
}

/* 0x001036B0, 0xB4 bytes. Vibration on (`off` 0) or off. */
void func_001036B0(int port, int off)
{
    u8 *flags = &g_00500700[port].flags;
    u8 f = *flags;

    if (f & 1) {
        if (off == 0) {
            if ((f & 7) >> 2 != 1)
                *flags = f & 0x7F;
            *flags = (*flags & 0xFB) | 4;
        } else {
            *flags = f & 0x7F;
            *flags &= 0xFB;
        }
    }
}

/* 0x00103770, 0x78 bytes. The left stick as the D-pad: on when `on` is 0 (bit 4). */
void func_00103770(int port, int on)
{
    if (on == 0)
        g_00500700[port].flags = (g_00500700[port].flags & 0xEF) | 0x10;
    else
        g_00500700[port].flags &= 0xEF;
}

/* 0x001037F0, 0xC bytes, matching. Allows the reset combination; the previous setting. */
int func_001037F0(int allowed)
{
    int old = g_0045D214;

    g_0045D214 = allowed;
    return old;
}

/* 0x00103800, 0xC8 bytes. Start + Select held 10 frames on a pad asks for a soft reset. */
void func_00103800(void)
{
    g_0045D20C = 0;
    if (g_0045D214 == 0) {
        g_0045D208 = 10;
    } else {
        int found = 0, i;
        Pad *p = g_00500700;

        for (i = 0; i < 2; i++, p++) {
            u16 now = PAD_READY(p) ? p->now : 0;

            if ((now & 0x900) == 0x900) {
                found = 1;
                break;
            }
        }
        if (found) {
            if (--g_0045D208 == 0)
                g_0045D20C = 1;
        } else {
            g_0045D208 = 10;
        }
    }
}

/* The pad's mode: digital (0x41), analog (0x73) or with pressure (0x79). */
#define PAD_MODE(p) (((p)->flags & 1) ? (p)->raw[1] : 0)

/* 0x001038D0, 0x49C bytes. Each frame, for each open pad: libpad's state, the set-up steps
 * (the analog mode locked, the pressure mode, the actuators), then the data read. */
void func_001038D0(void)
{
    int port;
    Pad *p = g_00500700;

    for (port = 0; port < 2; port++, p++) {
        int state, step = 0;

        if ((p->flags & 1) == 0)
            continue;
        p->connected &= 0xFE;
        state = func_001711C8(port, 0);
        p->state = state;
        if (state == 1 || state == 5)
            continue;
        if (state == 0 || state == 7) {
            func_00103510(p);
            continue;
        }
        if (p->phase != 4 && (step = func_00171330(port, 0)) == 2)
            continue;
        if ((p->flags & 3) >> 1 != 1) {               /* the analog mode, locked */
            if (p->phase == 4) {
                if (func_00171728(port, 0, 1, 3) == 1)
                    p->phase = 0;
                continue;
            }
            if (p->phase == 0) {
                if (step == 1) {
                    if (func_00171728(port, 0, 1, 3) == 1)
                        p->phase = 0;
                    continue;
                }
                p->flags = (p->flags & 0xFD) | 2;
                p->phase = 4;
            }
        }
        if ((p->flags & 0x7F) >> 6 != 1) {           /* the pressure mode */
            if (func_00171AE0(port, 0) == 1) {
                if (p->phase == 4) {
                    if (func_00171B60(port, 0) == 1)
                        p->phase = 2;
                    continue;
                }
                if (p->phase == 2) {
                    if (step == 1) {
                        if (func_00171B60(port, 0) == 1)
                            p->phase = 2;
                        continue;
                    }
                    if (PAD_READY(p))
                        p->flags = (p->flags & 0xDF) | 0x20;
                    p->phase = 4;
                }
            } else if (PAD_READY(p)) {
                p->flags &= 0xDF;
            }
            p->flags = (p->flags & 0xBF) | 0x40;
        }
        {
            u8 f = p->flags;

            if ((f & 7) >> 2 == 1 && (char)f >= 0) {   /* the actuators */
                if (p->phase == 4) {
                    if (func_001718A8(port, 0, p->act_align) == 1)
                        p->phase = 1;
                    continue;
                }
                if (p->phase == 1) {
                    if (step == 1) {
                        if (func_001718A8(port, 0, p->act_align) == 1)
                            p->phase = 1;
                        continue;
                    }
                    p->flags = (f & 0x7F) | 0x80;
                    p->phase = 4;
                }
            }
        }
        func_0011EB80(p->previous, p->raw, 0x20);
        if (func_00171150(port, 0, p->raw) == 0x20) {
            int ok;

            if ((p->flags & 1) == 0) {
                ok = 0;
            } else {
                u8 mode = PAD_MODE(p);

                ok = mode == 0x73 || mode == 0x73 || mode == 0x79;
            }
            if (ok) {
                func_00103430(p);
                if (func_00103090(port) == 0)
                    func_00103510(p);
                else
                    p->connected = (p->connected & 0xFE) | 1;
            } else {
                func_00103510(p);
            }
        } else {
            func_00103510(p);
        }
    }
    func_00103800();
}

/* 0x00103D90, 0xD0 bytes. Opens port `port`. */
void func_00103D90(int port)
{
    Pad *p = &g_00500700[port];

    if ((p->flags & 1) == 0) {
        func_00118850(p, 0x88);
        p->buffer = g_00500500[port];
        while (func_00170D00(port, 0, p->buffer) != 1)
            ;
        func_00103510(p);
        p->vib_sent = 0;
        func_001036B0(port, 0);
        func_00103770(port, 0);
        p->flags = (p->flags & 0xFE) | 1;
    }
}

/* 0x00103E60, 0xC4 bytes. Closes port `port` (once libpad is idle). */
void func_00103E60(int port)
{
    Pad *p = &g_00500700[port];

    if (p->flags & 1) {
        int state;

        p->flags &= 0xFE;
        do {
            do
                state = func_001711C8(port, 0);
            while (state == 1);
        } while (state == 5 || func_00171330(port, 0) == 2 || func_00170EE8(port, 0) != 1);
        func_00118850(p, 0x88);
    }
}

/* 0x00103F30, 0x68 bytes. Closes both ports. */
void func_00103F30(void)
{
    int port;

    for (port = 1; port >= 0; port--)
        if (g_00500700[port].flags & 1)
            func_00103E60(port);
}

/* 0x00103FA0, 0x88 bytes. Opens the ports asked for. */
void func_00103FA0(void)
{
    u32 port;

    for (port = 0; (int)port < 2; port++)
        if ((g_0045D204 & (1 << port)) != 0 && (g_00500700[port].flags & 1) == 0)
            func_00103D90(port);
}

/* 0x00104030, 0x8 bytes, matching. */
int func_00104030(void)
{
    return 0;
}

/* 0x00104040, 0x90 bytes. Starts libpad and clears both pads; both ports to open. */
void func_00104040(void)
{
    int i;

    while (func_001708A8(0) != 1)
        ;
    func_00171E18(0);
    g_0045D214 = 0;
    g_0045D210 = 0;
    g_0045D20C = 0;
    for (i = 0; i < 2; i++)
        func_00118850(&g_00500700[i], 0x88);
    g_0045D204 = 3;
}

/* 0x001040D0, 0x60 bytes, matching. Closes the ports and stops libpad. */
void func_001040D0(void)
{
    int i;

    for (i = 0; i < 2; i++)
        func_00103E60(i);
    while (func_00170B38() != 1)
        ;
}

/* 0x00104130, 0x74 bytes. The buttons read last (before the frame's processing). */
u32 func_00104130(int port)
{
    Pad *p = &g_00500700[port];

    if (PAD_READY(p))
        return (p->raw[2] ^ 0xFF) << 8 | (p->raw[3] ^ 0xFF);
    return 0;
}

/* 0x001041B0, 0x9C bytes. The buttons released: down in the read before, up in the last one. */
u32 func_001041B0(int port)
{
    Pad *p = &g_00500700[port];

    if (PAD_READY(p))
        return (((p->raw[2] ^ 0xFF) << 8 | (p->raw[3] ^ 0xFF)) ^ 0xFFFF) &
               ((p->previous[2] ^ 0xFF) << 8 | (p->previous[3] ^ 0xFF));
    return 0;
}
