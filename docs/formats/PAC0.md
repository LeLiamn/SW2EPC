# PAC0 files

**Status: structure decoded.** Tool: `tools/pac0.py`.

1,111 small files, one per voice line 0x11CF-0x151D (847 event voices) plus copies inside packs.
`ev_main.c` loads entry `0xE3 + n` for voice `0x11CF + n` (`func_001D9670` / `func_001D9750`), and
`func_001DB520` hands the file to the character speaking with the voice (`func_001DF1C0`), whose
reader (`func_00147BD0`, `func_00147C50`) finds the sections from the header. Probably the mouth
movements of the line (lip sync).

| Offset | Type | Meaning |
|---:|---|---|
| 0x00 | char[12] | `PAC02_00JM20` |
| 0x0C | u32 | (a size) |
| 0x10, 0x12, 0x14 | u16 × 3 | number of entries of sections 0, 1 and 2 |
| 0x20 | | the three sections, 3 bytes per entry |

The file ends right after the last section (inside packs, zero padding to 16 bytes follows).
