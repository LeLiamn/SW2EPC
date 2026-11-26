# Battlefield terrain files (starting `00 C0 04 66`)

**Status: decoded.** Tool: `tools/battlefield.py` (structure check, export of the terrain to OBJ).

There are **186 files** (59 MB), LINKDATA.BNS entries 2300 to 2485, each a pack
`[terrain, TMD2, TMD2, TIM2]`: the terrain described here, two static object sets
([TMD2.md](TMD2.md)) and the battlefield's top-down map ([TIM2.md](TIM2.md)).

The structure comes from the game code (source file `Stage.c`): `func_00193B90` loads entry
`2300 + battlefield number` (and `2486 + number`), `func_00194010` turns the pack's offsets into
pointers and gives the first file to `func_00196540`, which copies its 0x100-byte header to the
scratchpad (`0x70000770`) and keeps a pointer to each section. The terrain drawing code
(`func_00194D10`, `func_00200490`, `func_002007A0`) reads the sections.

## Header (0x100 bytes)

| Offset | Content |
|---|---|
| 0x00-0x7F | VIF/GIF command templates used when drawing (the file starts with `UNPACK V2-8`, hence `00 C0 04 66`) |
| 0x80 | offset of section 0, the terrain grid |
| 0x84-0x94 | offsets of sections 1-5, the five layers (0 when the file has no layers) |
| 0x98 | offset of section 6, the tiles |
| 0x9C | offset of section 7, the register sets |
| 0xA0 | offset of section 8, the texture coordinates |
| 0xD0, 0xD1 | grid size in cells: width, height (u8) |
| 0xD2-0xDB | origin (x, z cell) of each layer, two u8 per layer |
| 0xDC | non-zero when the layers are used (u32) |

Offsets count from the start of the file. Every section is padded to a 16-byte boundary with
`00 CC CC CC...` (and leftovers of the tool's memory after it); when the padding starts in the slot
of a last record, that slot is padding too.

## Section 0: the terrain grid

`(width + 1) x (height + 1)` vertices of 20 bytes, row by row (x first). Two vertices are 500 world
units apart.

| Offset | Content |
|---|---|
| 0x00 | 4 bytes, unknown |
| 0x04 | s16 height (the game's Y axis points down) |
| 0x06, 0x08, 0x0A | u16 tile of the cell at this vertex, one per drawing pass (0xFFFF = none) |
| 0x0C | colour index (low 7 bits: one of the 16-byte colours of a table at `0x70000A10`) |
| 0x0D | low 2 bits: which diagonal splits the cell; the other bits are not used by the drawing code |
| 0x0E | 6 bytes, unknown |

The 140 small files (all 150,560-150,624 bytes, grid size 60 x 60) have **no grid**: section 0 is
16 bytes of padding. They are placeholders (they also have only a dozen tiles).

## Sections 1-5: layers (when header 0xDC is non-zero)

Five layers of 50 x 50 cells of 12 bytes, placed on the grid at the origin given in the header
(`func_00194480`: a cell outside the 50 x 50 square, or whose byte 7 has its low 2 bits clear, is
empty). In a cell: +4 u16 tile (0xFFFF = none), +6 colour index (low 7 bits), +7 flags.

## Section 6: tiles (12 bytes)

| Offset | Content |
|---|---|
| 0x0 | u16 material: index of a 16-byte texture set at the start of the scene's data (`0x70000760`) |
| 0x2 | u16 register set (section 7) |
| 0x4-0xA | four u16 indices into section 8, the texture coordinates of the cell's four corners |

## Section 7: register sets (8 bytes)

Copied as they are into the drawing packet before the tile's vertices (GS register data).

## Section 8: texture coordinates (16 bytes)

Four floats, multiplied by the vertex colour before being sent to the GS.

## Checked

`py tools/battlefield.py --check image.iso`: the 186 files parse, every section ends with its
padding only, and every tile, register set and coordinate index is in range (140 placeholders).
`py tools/battlefield.py FILE OUT.obj` exports the terrain heights; battlefield 2301 shows bases
joined by paths, a river and hills around the edges, matching its top-down map.

Not decoded yet: the first 4 and last 6 bytes of a vertex, the meaning of the layer flags, and the
content of the register sets beyond "GS data copied as is".

# The second pack of each battlefield (entries 2486-2671)

`func_00193B90` also loads entry `2486 + battlefield number`; `func_00197470` reads it. It is a pack
of 5 parts (`u32 count`, then offsets from the pack's start), checked by
`battlefield.parse_pack2()` on all 186 entries (58 full packs, 128 placeholders):

| Part | Content | Reader |
|---|---|---|
| 0 | 16 bytes per node of part 2 | `func_001FFF10` |
| 1 | 16 bytes per object of part 3 | `func_00208140` |
| 2 | nodes: a pack of records (below) | `func_001FFF10`, `func_001FF140` |
| 3 | objects: a pack of four size tables | `func_00208140`, `func_00208070`, `func_00207FA0` |
| 4 | "ranges": a pack of 5 entries (a u32 value, then four arrays) | `func_00197300`, `func_001F70A0` |

The 128 placeholder battlefields have only the "ranges" part (the entry itself is that pack).

**Node record**: u16 index (= its position), u16 number of links, u16 number of items, u16; header
up to 0x30; then the items, 0x10 bytes when bit 0 of their word at +0xC is set, else 0x20 (their
float at +4 is an angle, snapped to 0, ±90° or 180° at load); then the links, 0x20 bytes each.

**Object tables** (part 3): each is `u32 count, count × u32 size`, then the data aligned to 16
bytes, one slot per object (size 0 = empty). Tables 0 to 2 hold TMD2 objects (one per object; the
third has 15 more, shared, `func_00207D40`), table 3 per-object data: empty, 0x20 bytes (default),
or a 16-byte header followed by data. When placed, an object's bounding box is moved by its centre
(TMD2 +0x90) times 100 (`func_00207DF0`).
