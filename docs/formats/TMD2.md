# TMD2: static scene objects

**Status: understood** (geometry, UVs, colours, normals, placement). Tool: `tools/tmd2.py` (checks
every file, exports one object or a whole pack of objects as OBJ).

There are **26,623 TMD2 files** in `LINKDATA.BNS` (97 MB), mostly inside size-table packs
([PACK.md](PACK.md), variant 3) of the battlefield entries (for example 713 objects in pack
`2528.3.0`). **All of them parse**, and each one's data stream ends exactly at the end of the file.
A scene rendered from one pack shows coherent wooden structures (a scaffold or watchtower with
ladders, a ramp, posts, barrels) whose parts join up.

All values are little-endian.

## Header

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[4] | `TMD2` |
| 0x04 | char[4] | `0060` (version) |
| 0x08 | u32 | File size in 16-byte units |
| 0x0C | u32 | Always `0x6400` |
| 0x10 | u32 × 2 | 1, 7 |
| 0x18 | u32 × 7 pairs | Small values (0/4, 10/0...): meaning unknown |
| 0x50 | f32 × 4 | Bounding box minimum (x, y, z, 1) |
| 0x60 | f32 × 4 | Bounding box maximum (x, y, z, 1) |
| 0x70 | f32 × 4 | (1, 1, 1, ...): scale? |
| ... | | More fields, then a few small records, then the VIF stream |

## Geometry

A chain of VIF packets for the VU1. Each batch is:

| VIF command | Count | Content |
|---|---|---|
| `UNPACK V4-32` | 1 | GIF tag: NLOOP = number of vertices N, PRIM = 4 (triangle strip) or 3 (triangles) |
| `UNPACK V2-32` | N | Texture coordinates (s, t) |
| `UNPACK V4-8` | N | Vertex colours (RGBA, pre-computed lighting) |
| `UNPACK V3-32` | 2N (sometimes N) | N positions, then N normals |
| `MSCNT` | | Run the VU1 microprogram |

Checks: all 1,792,414 normals are unit vectors.

## Placement

About half the objects store positions already in world space (they fit the bounding box as they
are); the other half store positions centred on the bounding box, so the box centre has to be
added. The flag that tells them apart is not identified yet; `tools/tmd2.py` decides with the
bounding box. The world-space objects include very large ones (over 100,000 units: sky or distant
terrain?).

## Open questions

- The header fields between 0x10 and 0x50, and after 0x70.
- Which texture each batch uses.
- The flag that selects world or centred positions.
