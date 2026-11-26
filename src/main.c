/*
 * main.c - entry point and main loop of Samurai Warriors 2: Empires (SLES_546.24).
 *
 * Decompiled by reading the original machine code (with Ghidra and the R5900 extension); not
 * verified by compiling, since the original compiler (CodeWarrior for PS2) is not available to the
 * project. Unknown functions and globals keep neutral names (func_/g_ + address) until their role
 * is proven; comments with a question mark are hypotheses.
 */

typedef unsigned int u32;

/* 0x0045D1C4 (gp - 0x7A2C): a flag set to 0 before and 1 after set-up, shutdown and every pass of
 * the main loop. Its readers are not identified yet. */
extern int g_0045D1C4;

/*
 * 0x0045D880: the scene (state) manager that runs the whole game. Each scene of the game plugs its
 * own functions in; the state numbers are not mapped to scenes yet. 0x18 in `requested` means "no
 * change requested". Field names are descriptive guesses from how func_001005A0 uses them.
 */
typedef struct {
    float update_arg;        /* +0x00 argument passed to update(): 1.0 at start-up (time step?) */
    u32 result;              /* +0x04 returned by func_001005A0 when the game quits */
    int quit;                /* +0x08 non-zero: leave the main loop */
    int skip_update_test;    /* +0x0C non-zero: run step() without asking update() */
    int force_draw;          /* +0x10 non-zero: draw even when the state is changing */
    int previous;            /* +0x14 state before a reset */
    int current;             /* +0x18 current state */
    int unknown_1c;          /* +0x1C set to 0x18 on reset */
    int requested;           /* +0x20 requested state (0x18 = none) */
    int running;             /* +0x24 the per-frame loop runs while current == running */
    void (*enter)(void);     /* +0x28 */
    void (*leave)(void);     /* +0x2C */
    int (*update)(float dt); /* +0x30 non-zero: run step() */
    void (*step)(void);      /* +0x34 */
    void (*draw)(void);      /* +0x38 */
    void (*enter_alt)(void); /* +0x3C used instead of enter when set */
    void (*leave_alt)(void); /* +0x40 used instead of leave when set */
    void (*on_reset)(void);  /* +0x44 called when a reset is requested */
} SceneManager;

extern SceneManager g_0045D880;

/*
 * 0x00422000: the scene table, 24 entries of 0x24 bytes, indexed by state number. Each entry is
 * copied into the manager (from `running` to `on_reset`) when its scene becomes current.
 * Scenes identified so far (see docs/code.md): 0x0A StatePostBattle.c, 0x0C StateConfig.c,
 * 0x0D StateTreasures.c, 0x0E StateShop.c, 0x15 StateSetupEmpMogi.c.
 */
typedef struct {
    int running;             /* always the entry's own state number */
    void (*enter)(void);
    void (*leave)(void);
    int (*update)(float dt);
    void (*step)(void);
    void (*draw)(void);
    void (*enter_alt)(void);
    void (*leave_alt)(void);
    void (*on_reset)(void);
} SceneEntry;

#define SCENE_COUNT 0x18
extern SceneEntry g_00422000[SCENE_COUNT];

/* 0x0045D20C and 0x0045D210: two reset requests (soft reset by button combination?). */
extern int g_0045D20C;
extern int g_0045D210;

void func_00100410(void);
void func_001023C0(void *callback, int value);
void func_001023D0(void *callback, int value);
void func_001037F0(int value);
void func_00103FA0(void);
void func_00147680(void);
void func_00177F80(void);
void func_00185DA0(void);
void func_00194130(void);
void func_0019F350(void);
void func_001AC3A0(void);
void func_001B9200(void);
void func_001C7620(void);
void func_001F1C70(void);
void func_0020E4E0(void);
void func_00214F90(void);
void func_0023C120(void);
void func_002D7F90(void);
void func_002E6210(void);
void func_00374E20(void);
void func_003B38F0(void);
void func_003DB0B0(void);
void func_003DC030(void);
void func_00100230(void);
void func_00100240(void);
void func_001004B0(void);
void func_00100500(void);
void func_001020E0(void);

/* 0x0045CB80: passed four times to func_00117F10 during system set-up. */
/* Four different symbols that the linker placed at the same address (the compiler loads each one
 * separately, so they are distinct names in the source; linker-defined section bounds?). */
extern u32 g_0045CB80_a[], g_0045CB80_b[], g_0045CB80_c[], g_0045CB80_d[];

/* 0x7000015C: a word in the PS2 scratchpad RAM, set to 12345 at start-up (random seed?). */
#define g_7000015C (*(volatile u32 *)0x7000015C)

void func_00102380(void);
void func_001023E0(void);
void func_001029B0(void);
void func_00102A00(void);
void func_00102B80(void);
void func_00103060(void);
void func_00104040(void);
void func_001040D0(void);
void func_001062F0(void);
void func_00106700(void);
void func_00117EB0(void);
void func_00117F10(void *a, void *b, void *c, void *d);
void func_001181E0(void);
void func_0022DE80(void);
void func_00143F50(void);
void func_00143FB0(void);

/* 0x001014D0, 8 bytes, matching. */
void func_001014D0(int value)
{
    g_0045D1C4 = value;
}

/* 0x00117E50, 0x38 bytes, matching. First call of main. */
void func_00117E50(void)
{
    func_00117F10(g_0045CB80_a, g_0045CB80_b, g_0045CB80_c, g_0045CB80_d);
}

/* 0x00117E90, 0x1C bytes, matching. Last call of main. */
void func_00117E90(void)
{
    func_00117EB0();
}

/* 0x00106750, 0x80 bytes, matching. Game set-up: eleven initialisation calls, bracketed by the flag. */
void func_00106750(void)
{
    func_001014D0(0);
    func_00103060();
    func_00106700();
    func_001023E0();
    func_001062F0();
    func_00104040();
    func_0022DE80();
    func_001029B0();
    func_001181E0();
    func_00143F50();
    func_00102B80();
    g_7000015C = 12345;
    func_001014D0(1);
}

/* 0x001067D0, 0x3C bytes, matching. Game shutdown, bracketed by the flag. */
void func_001067D0(void)
{
    func_001014D0(0);
    func_00143FB0();
    func_00102A00();
    func_001040D0();
    func_001014D0(1);
}

/* 0x00106810, 0x24 bytes, matching. Called after each pass of the main loop: only toggles the flag. */
void func_00106810(void)
{
    func_001014D0(0);
    func_001014D0(1);
}

/* Copy a scene table entry into the manager (running .. on_reset). */
static void load_scene(SceneManager *s, const SceneEntry *e)
{
    s->running = e->running;
    s->enter = e->enter;
    s->leave = e->leave;
    s->update = e->update;
    s->step = e->step;
    s->draw = e->draw;
    s->enter_alt = e->enter_alt;
    s->leave_alt = e->leave_alt;
    s->on_reset = e->on_reset;
}

/* 0x00100260, 0x1A8 bytes. Resets the scene manager to scene 0, then initialises 20 subsystems
 * (font.c, cmnparts.c, effect.c, Stage.c, RelayCamera.c, StationEmp.c... are among the callees). */
void func_00100260(void)
{
    SceneManager *s = &g_0045D880;

    s->result = 0;
    s->quit = 0;
    s->skip_update_test = 0;
    s->force_draw = 0;
    s->update_arg = 1.0f;
    s->previous = 0x18;
    s->current = 0;
    s->unknown_1c = 0x18;
    s->requested = 0x18;
    load_scene(s, &g_00422000[0]);

    func_00103FA0();
    func_001037F0(0);
    func_001AC3A0();
    func_00147680();
    func_001B9200();
    func_0019F350();
    func_0023C120();
    func_00194130();
    func_00185DA0();
    func_00177F80();
    func_001F1C70();
    func_002E6210();
    func_0020E4E0();
    func_001C7620();
    func_002D7F90();
    func_00214F90();
    func_00374E20();
    func_003DB0B0();
    func_003DC030();
    func_003B38F0();
    func_001023C0(func_00100240, 100);
    func_001023D0(func_00100230, 0xF0);
}

/* 0x00100500, 0xA0 bytes. Loads the current scene's functions from the scene table. */
void func_00100500(void)
{
    SceneManager *s = &g_0045D880;

    if (s->current < SCENE_COUNT)
        load_scene(s, &g_00422000[s->current]);
}

/* 0x001005A0, 0x2C4 bytes. Runs the scene manager until the game quits, then returns its result.
 * This is where each frame of the game happens (main's loop calls it until it returns non-zero).
 */
int func_001005A0(void)
{
    SceneManager *s = &g_0045D880;

    func_001014D0(0);
    func_00100260();
    while (s->quit == 0) {
        func_00100500();

        /* Enter the current scene (once, when it was just requested). */
        if (s->requested < 0x18 && s->current == s->requested) {
            s->requested = 0x18;
            if (s->enter_alt != 0)
                s->enter_alt();
            else
                s->enter();
        } else {
            s->enter();
        }
        func_001014D0(1);

        /* Run the scene while it stays current. */
        if (s->current == s->running) {
            do {
                if (s->skip_update_test != 0)
                    s->step();
                else if (s->update(s->update_arg) != 0)
                    s->step();

                if ((s->current == s->running || s->force_draw != 0) &&
                    g_0045D20C == 0 && g_0045D210 == 0) {
                    s->draw();
                    s->force_draw = 0;
                } else {
                    func_001014D0(0);
                }
                func_001004B0();

                if (g_0045D20C != 0 || g_0045D210 != 0) {   /* reset requested */
                    func_001020E0();
                    func_001020E0();
                    if (s->on_reset != 0)
                        s->on_reset();
                    g_0045D20C = 0;
                    g_0045D210 = 0;
                    s->previous = s->current;
                    s->current = 0x10;
                    s->requested = 0x18;
                    s->unknown_1c = 0x18;
                }
            } while (s->current == s->running);
        }

        /* Leave the scene. */
        if (s->requested < 0x18 && s->leave_alt != 0)
            s->leave_alt();
        else
            s->leave();
    }
    func_001014D0(0);
    func_00100410();
    return s->result;
}

/* 0x00102A20, 0x58 bytes. Called by the start-up code (crt0) with argc/argv, followed by exit().
 * The work of each frame is done by the loop condition, func_001005A0 (large: game state machine?). */
int main(int argc, char **argv)
{
    func_00117E50();
    func_00106750();
    while (func_001005A0() == 0)  /* non-zero: leave the main loop */
        func_00106810();
    func_001067D0();
    func_00117E90();
    return 0;
}
