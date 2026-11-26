# "PS2 " files: 3D models

**Status: understood** (except a small node-less variant). Tool: `tools/ps2model.py` (exports OBJ
with UVs and normals in bind pose, plus a PNG preview).

There are **476 models** in `LINKDATA.BNS` (51 MB). 455 decode fully, characters included:

| Nodes | Models | What they are (from previews) |
|---:|---:|---|
| 102 | 136 | Main characters: e.g. an armoured samurai with hair, shoulder guards, armour skirt, boots |
| 47 | 33 | Generic soldiers (lower detail) |
| 39 | 56 | Simpler figures (e.g. a robed person) and very small block versions (shadow or collision proxies?) |
| 61, 20, 9, 4, 3, 2 | 32 | Other rigged models, to identify |
| 1 | 194 | Rigid models: weapons (spears, war fans...) and small flat models (effects? flags?) |
| 0 | 21 | **Variant**: no nodes and no vertex batches found with this layout. Still to study |

All values are little-endian.

## Header and skeleton

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `PS2 ` |
| 0x04 | u32 | 16 |
| 0x08 | u32 | Offset of the geometry section |
| 0x0C | u32 | 0 |
| 0x10 | u16 | Number of nodes N |
| 0x12 | u16 | Number of skinning matrices M (bone slots used by vertices) |
| 0x14 | i32 × N | Parent of each node (−1 for the root). Skinning bones come first (0..M−1); the extra nodes (M..N−1) are structural parents |
| ... | i32 × N | Second node table, almost always −1 (meaning unknown) |
| ... | 9 × f32 × N | Per node: rotation (x, y, z, radians), scale (3), translation (3) |

The skeleton ends exactly at the geometry offset (padding to 16 bytes).

A node's local matrix is **T × Rz × Ry × Rx × S**; world matrices chain through the parents. (The other
common order, Rx × Ry × Rz, gives broken characters; this one gives correct ones.) The data uses
Y pointing down: the root of a character sits at y = −117. The export turns the model 180° around X
so it stands upright (no mirroring).

## Geometry

The geometry is a chain of PS2 VIF packets for the VU1 vector unit (`UNPACK` V4-32 commands, e.g.
`6C 83 80 00`). Each batch of vertices starts with a GIF tag: NLOOP = number of vertices, PRIM = 3
(triangles) or 4 (triangle strip), 3 registers ST, RGBAQ, XYZ2 (`REGS = 0x412`). The tag is what the
VU program outputs; the vertices that follow are its **input**, and their size varies:

| Quadwords | Content |
|---|---|
| 1 | f32 s, f32 t (texture coordinates), u32 flags (bit 15: do not draw the triangle ending here, used to restart strips), u32 **k** = number of bones (1 to 4) |
| 2 × k | (f32 normal × weight, u32 bone address) then (f32 x, y, z in that bone's space, f32 weight) |

The bone address is a VU memory address: **slot = address / 4**, and slot *s* is node *s*. The weights
of a vertex add up to 1. The final position is Σ weight × (world matrix of the bone × position).

Checks: on a 102-node character, all 4,907 vertices of the 207 batches parse and their weights add up
to exactly 1; the batches cover 96% of the geometry section (the rest is VIF headers). Previews show
correct, complete characters in T-pose.

## Open questions

- The 21 node-less files.
- The second node table, and the meaning of the per-batch VU parameters before each GIF tag.
- How textures are bound to batches (the TIM2 textures next to the models in the same packs).
