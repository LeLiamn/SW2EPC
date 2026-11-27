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
   On the PC they are looked up through a table generated from the function tags
   (`PS2_FUNC(addr)`, to be written).
6. **Shared prototypes go in headers** (`src/sw2e_draw.h` for the drawing helpers), with full
   argument lists. See "Shared prototypes and stack arguments" in [code.md](code.md).

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
