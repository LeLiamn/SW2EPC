# "PS2 " files: 3D models

**Status: in progress.** Tool: `tools/ps2model.py` (exports OBJ with UVs and normals, plus a PNG
preview). Geometry, UVs, normals and the skeleton layout are decoded and all 476 models export.
**Not done yet: posing skinned models** (characters): their vertices are stored relative to bones and
are not yet moved by the skeleton, so they come out scattered.

There are **476 models** in `LINKDATA.BNS` (51 MB): 194 rigid models with a single node (weapons such
as spears and war fans recognised in previews, plus small flat models, maybe effects or flags) and
282 skinned models with a skeleton (up to 102 nodes: characters, horses?).

All values are little-endian.

## Header

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `PS2 ` |
| 0x04 | u32 | 16 |
| 0x08 | u32 | Offset of the geometry section |
| 0x0C | u32 | 0 |
| 0x10 | u16 | Number of nodes N |
| 0x12 | u16 | Number of matrices used for skinning? (1 for rigid models, e.g. 67 for a 102-node model) |
| 0x14 | i32 × N | Parent of each node (−1 for the root) |
| ... | i32 × N | Second node table, almost always −1 (links? attachments?) |
| ... | 9 × f32 × N | Per node: rotation (3), scale (3), translation (3). The root of a character sits at y = −117 |

The skeleton ends exactly at the geometry offset (padding to 16 bytes).

## Geometry

The geometry is a chain of PS2 VIF packets meant for the VU1 vector unit (`UNPACK` commands such as
`0x6C` V4-32). Inside, each batch of vertices starts with a GIF tag:

- NLOOP = number of vertices, PRIM = 3 (triangles) or 4 (triangle strip),
- 3 registers per vertex: ST, RGBAQ, XYZ2 (`REGS = 0x412`).

Each vertex is 3 quadwords (48 bytes):

| Quadword | Content |
|---|---|
| 0 | f32 s, f32 t (texture coordinates), u32 flags (bit 15: do not draw the triangle ending here, used to restart strips), u32 (1 in rigid models; meaning unknown) |
| 1 | f32 nx, ny, nz (normal), u32 bone (VU address of a bone matrix, a multiple of 4; some batches hold small values or floats here instead: weights of multi-bone vertices?) |
| 2 | f32 x, y, z (position, in the space of the vertex's bone), f32 w = 1.0 |

## Open questions

- Mapping from the bone field (VU matrix address) to skeleton nodes, and the meaning of the second
  node table.
- Batches whose bone field holds floats or small integers (multi-bone skinning).
- Rotation order and units of the node transforms.

The answers are in the VU1 microcode and the game code that uploads bone matrices; reading those is
the next step for this format.
