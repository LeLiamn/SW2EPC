# The PC port: memory model and code conventions

The port is a 64-bit program built on the launcher's runtime (see [launcher.md](launcher.md)). This
file sets how the decompiled C has to be written so that the same sources build for the PS2
(CodeWarrior, matching) and for the PC.

## Memory model

- **One 32 MB block stands for the EE's RAM.** The data segments of the player's own boot
  executable are loaded at their PS2 addresses inside it. The game's heaps and file buffers are
  allocated inside it too. A separate 16 KB block stands for the scratchpad (`0x70000000`).
- **Addresses stored in game data stay 32-bit PS2 addresses.** That includes fields, globals and
  table entries. Structure layouts and the save image therefore stay byte-for-byte as on the
  console.
- **Native pointers only live in C locals and parameters.**

`src/sw2e_mem.h` holds the tools:

| Name | PS2 build | PC build |
|---|---|---|
| `ps2ptr` | `unsigned int` | `unsigned int` (a PS2 address) |
| `PS2_PTR(a)` | `(void *)(a)` | `ram + a` (or the scratchpad) |
| `PS2_ADDR(p)` | `(unsigned int)(p)` | `p - ram` |
| `PS2_MEM(a)` | — | the address of a global at a fixed PS2 address |
| `PS2_GETP(T, a)` / `PS2_SETP(a, v)` | `*(T *)a` / `*(T *)a = v` | the pointer stored at PS2 address `a` (4 bytes), read as `T` / stored |
| `PS2_FUNC(a)` / `PS2_CODE(f)` | casts | the C function for code address `a` / the code address of `f` |
| `PS2_ANYPTR(o)` | `(void *)(o)` | for macros given either a pointer or an address held in an integer |
| `sw2e_uptr` | `unsigned int` | an integer as wide as a native pointer (alignment arithmetic) |

On the PS2 build these are plain casts, so the code CodeWarrior generates does not change.

## Rules for decompiled code

1. **A global or field that stores an address is a `ps2ptr`**, not a C pointer. Read it with
   `PS2_PTR(...)` (cast to the type you need) and store it with `PS2_ADDR(...)`.

   ```c
   extern ps2ptr g_0045D7FC;                       /* the sprite bank */
   #define BANK ((u8 *)PS2_PTR(g_0045D7FC))
   ```

2. **Structures keep their PS2 layout:** pointer fields are `ps2ptr` (4 bytes), never `T *`.
3. **No pointer is held in an `int`.** Write `u8 *p` for a local pointer, and `ps2ptr` when it
   is stored.
4. **Globals keep their `extern` declarations as they are.** The PC build rewrites them, see
   below.
5. **Tables of function pointers in PS2 data** (scene tables, callbacks) hold PS2 code addresses.
   On the PC they are looked up through a table generated from the function tags:
   `PS2_FUNC(addr)` gives the C function for a code address, `PS2_CODE(f)` the code address of a
   function (both plain casts on the PS2).
6. **Shared prototypes go in headers** (`src/sw2e_draw.h` for the drawing helpers), with full
   argument lists. See "Shared prototypes and stack arguments" in [code.md](code.md).
7. **Every file in `src/` includes `src/sw2e_protos.h`**, the prototypes of every function
   defined in `src/`. `py tools/make_protos.py` writes it from the definitions; rerun it after
   changing a definition.
   - **Types.** The header uses basic C types only. Types local to a file appear as `void *`.
   - **A file's own functions.** The prototypes are grouped by defining file. Each group sits
     behind a guard (`SW2E_FILE_UNIT_C` for `unit.c`). A hand-written file defines its guard
     before including the header, so its own definitions are not declared twice. Generated files
     do not define one, because they rely on the header for their own forward declarations.
   - **No local declarations.** Files no longer declare functions defined in another file. Every
     call is checked against the callee's real parameters:
     - an `int` holding a PS2 address is passed as `(T *)PS2_PTR(x)`;
     - a pointer passed to an `int` parameter is passed as `PS2_ADDR(p)`;
     - a float parameter gets a float value, never the bit pattern as an integer.
   - **When the original callers see a function differently.** Sometimes the callers of a file
     see a function differently from its definition. For example, `func_00117C90` masks its
     result to a byte, but `sound_front.c` does not mask it. That file then declares the function
     itself, on the PS2 build only:

     ```c
     #ifndef SW2E_PC
     #define SW2E_OWN_PROTO_func_00117C90   /* the original callers here see it this way */
     int func_00117C90(int a);
     #endif
     ```

     The header leaves out its own prototype of that function when `SW2E_OWN_PROTO_<name>` is
     defined. The PC build always uses the definition's prototype.

   Checking the calls this way found many definitions and calls that were wrong. They are listed
   in "Prototypes checked against the definitions" in [code.md](code.md).

## The PC build of the sources

`tools/pc_rewrite.py` copies `src/` to `build/pc/src/` and turns every `extern` declaration of a
global named after its address into an accessor into the memory block:

```c
extern int g_0045D7FC;            ->  #define g_0045D7FC (*(int *)PS2_MEM(0x0045D7FC))
extern u8 g_00669D60[0x300];      ->  #define g_00669D60 (*(u8 (*)[0x300])PS2_MEM(0x00669D60))
extern struct {...} g_007BF680;   ->  typedef struct {...} pc_t_007BF680;
                                      #define g_007BF680 (*(pc_t_007BF680 *)PS2_MEM(0x007BF680))
```

`sizeof` and `&` still work. The sources themselves are not changed, so matching is not
affected.

```sh
py tools/pc_rewrite.py --report
gcc -m64 -DSW2E_PC -std=gnu99 -fsyntax-only -Ibuild/pc/src build/pc/src/<file>.c
```

## The first PC build (2026-11-28)

`py tools/pc_build.py [--disc <image>]` builds `build/pc/sw2epc.exe` and writes
[pc_build.md](pc_build.md). It runs the steps below, in order:

1. Rewrites `src/` into `build/pc/src/`.
2. Compiles every file as 64-bit C.
3. Adds the port's own files (`port/sw2e/`, and `port/stub/` until the UPP runtime exists).
4. Turns every function that is not decompiled yet into a stop that names it.
5. Links the result.

Three more PC forms were added for this build:

- **Inline PS2 assembly** has a PC equivalent under `#ifdef SW2E_PC`, declared in
  `src/sw2e_pc.h`. These are the VU0 matrix subroutines and EI. The PS2 build keeps the
  assembly.
- **Function tables in PS2 data** (`extern R (*g_X[N])(A);`) hold PS2 code addresses. On the PC
  they are read through `sw2e_fntab()`, which turns each address into the C function with that
  address tag (`sw2e_func()`).
- **Single function pointers**, which the game sets itself, become ordinary PC variables.

## Where the code stands (2026-11-27)

- **All 137 files compile as 64-bit C** after the rewrite (`-fsyntax-only`, MinGW GCC 15).
- **Work left before the code can run on the PC**, measured by `pc_rewrite.py --report` and GCC:
  - **379 globals declared with a pointer type**, to turn into `ps2ptr` (rule 1).
    `event_test_menu.c` is done, as the example.
  - **62 tables of function pointers**, kept as they are for now (rule 5).
  - **3,305 casts between pointers and integers** (GCC's `-Wpointer-to-int-cast` and
    `-Wint-to-pointer-cast`). Each is a pointer held in an `int`, or a field that should be a
    `ps2ptr` (rules 2 and 3).
- Much of this can be converted by script. The rest is done file by file as the code is linked
  for the PC.

## Running on the PC: the second round (2026-11-28)

With the first Sony library replacements in place, the PC build boots the EU disc, starts the disc
reader thread, reads the LINKDATA headers and runs the game's start-up up to the first function
that is not decompiled yet (see [pc_build.md](pc_build.md)). Getting there needed the rules above
applied across the sources. Most of it was done by script and checked the same way each time:
every changed file still compiles with CodeWarrior, and no matching function changed
(fingerprints against the last commit).

- **Pointer globals (248) are 4-byte slots.** Each declaration became the form below. The PS2 build
  keeps the original declaration, so CodeWarrior sees the same code:

  ```c
  #ifdef SW2E_PC
  extern ps2ptr g_0045D540_a;
  #define g_0045D540 ((u8 *)PS2_PTR(g_0045D540_a))
  #define g_0045D540_SET(v) (g_0045D540_a = PS2_ADDR(v))
  #else
  extern u8 *g_0045D540;
  #define g_0045D540_a (*(ps2ptr *)&g_0045D540)
  #define g_0045D540_SET(v) (g_0045D540 = (v))
  #endif
  ```

  Assignments read `g_0045D540_SET(x);`. Arrays of pointers (117 declarations) are not converted
  yet.
- **Pointers kept in PS2 memory through macros** (the scratchpad's packet cursor `0x70000158`,
  the stage unit tables) use `PS2_GETP` / `PS2_SETP` the same way (`NAME_SET(v)`).
- **Casts between pointers and integers** follow rule 3 everywhere GCC can see them:
  - 471 pointer-to-`int` casts became `(int)PS2_ADDR(p)`;
  - 3,163 integer-to-pointer casts became `(T *)PS2_PTR(x)`, since an integer in the decompiled
    code holds a PS2 address;
  - 137 integer arguments passed to pointer parameters of the Sony replacements (memset,
    strcpy, sprintf...) became `PS2_PTR(x)`.

  GCC now reports no pointer and integer of different sizes.
- **Fixed addresses written as integers** (`(T *)0x70000000`, `(float *)(0x574E20 + k * 0x630)`)
  go through `PS2_PTR`.
- **PC data the game stores as an address** (string literals of the PC build passed as paths, for
  example) gets a 64 KB window at `0x50000000 + n * 0x10000`, so `PS2_ADDR` and `PS2_PTR` work on
  it too.
- **Code addresses passed as integers** use `PS2_CODE(f)`, and calls through them `PS2_FUNC(a)`.

Still to do on the same lines:

- Pointer fields inside structures that live in PS2 memory (rule 2). GCC cannot see these; they
  show up as crashes (the node lists of `ui_misc2.c` were the first, now `ps2ptr` links).
- The 117 arrays of pointers.
- `sprintf` replacement: a `%s` argument is read as a PS2 address when its value is below
  `0x02000000`. An integer passed on the stack can come with a garbage upper half; wrap such an
  argument in `PS2_PTR` at the call site.
