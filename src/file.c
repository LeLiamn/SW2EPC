/*
 * file.c - reading the LINKDATA containers (original source file file.c: its name is passed
 * with the line number to its own reads, 0x00102410). Decompiled: 0x00102410-0x00102A00; main
 * (0x00102A20, main.c) follows, then the memory allocator.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 *
 * The game reads four containers (0 ANS music, 1 BNS data, 2 CNS movies, 3 DNS: not on the
 * disc, never opened). At start-up each one's first sector is found by name and its header
 * read (0x800 bytes, 0x7000 for BNS); a header starts with the magic 0x33B59 and, from +0x10,
 * holds per entry its offset and size in bytes (see docs/formats/LINKDATA.md). An entry is then
 * read by sectors through the request queue of system.c: queued (func_00100AC0), or at once
 * (func_00100C60). BNS entries can also come from a second source (g_0045CC04) when
 * func_00115C70 holds and the destination is aligned (a host / preloaded copy?).
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* The containers (0x00500460). */
typedef struct {
    u32 *header;             /* the header read at start-up (0 = none) */
    u32 (*index)[2];         /* header + 0x10: per entry its offset and size */
} Container;

extern struct {
    int ready;               /* 0x00500460 */
    u32 start[4];            /* 0x00500464 each container's first sector */
    Container container[4];  /* 0x00500474 */
} g_00500460;

/* A container's index, addressed from the object's base (the original folds the field's offset
 * into the load, not into the address). */
#define CONTAINER_INDEX(w) (*(u32 (**)[2])((u8 *)&g_00500460 + (w) * 8 + 0x18))

extern u32 g_0045CC04;                    /* (small data) the second source of BNS entries */

/* The containers' paths (0x00400C20) and the names searched for their first sector. */
extern const char *g_00400C20[4];         /* "cdrom0:LINKDATA.ANS;1", ... */

void func_00100870(u32 *out, const char *name, int a);
void *func_00102DB0(int align, u32 size);
void func_00102EC0(void *data);
u32 func_00100AC0(u32 a, u32 b, u32 c, u32 d);
u32 func_00100B90(u32 a, u32 b, u32 c, u32 d);
u32 func_00100C60(u32 a, u32 b, u32 c, u32 d);
u32 func_00100D00(u32 a, u32 b, u32 c, u32 d);
int func_00115C70(void);
u32 func_00115AC0(const char *path);
void func_00118850(void *to, int size);
int func_00100A30(int wait);
void func_00100AA0(void);
int func_001151C0(void);
void func_00100DA0(void);

void *func_00102880(const char *path, void *dest, int read, u32 size, u32 offset, const char *file,
                    int line);

/* 0x00102410, 0x1F4 bytes. Opens the containers: finds each one's first sector, reads its
 * header and keeps it when its magic is right. */
void func_00102410(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        Container *c = &g_00500460.container[i];
        u32 found[12];

        if (i == 3) {
            c->header = 0;
        } else if (i == 2) {
            func_00100870(found, "\\LINKDATA.CNS", 0);
            g_00500460.start[i] = found[0];
            c->header = func_00102DB0(0x40, 0x800);
            func_00102880(g_00400C20[i], c->header, 1, 0x800, 0, "file.c", 0x57);
        } else if (i == 1) {
            func_00100870(found, "\\LINKDATA.BNS", 0);
            g_00500460.start[i] = found[0];
            c->header = func_00102DB0(0x40, 0x7000);
            func_00102880(g_00400C20[i], c->header, 1, 0x7000, 0, "file.c", 0x4A);
        } else if (i == 0) {
            func_00100870(found, "\\LINKDATA.ANS", 0);
            g_00500460.start[i] = found[0];
            c->header = func_00102DB0(0x40, 0x800);
            func_00102880(g_00400C20[i], c->header, 1, 0x800, 0, "file.c", 0x3D);
        } else {
            c->header = 0;
        }
        if (c->header != 0) {
            if (c->header[0] == 0x33B59) {
                c->index = (u32 (*)[2])(c->header + 4);
            } else {
                func_00102EC0(c->header);
                c->header = 0;
                c->index = 0;
            }
        }
    }
}

/* 0x00102610, 0x6C bytes. Closes them. */
void func_00102610(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        g_00500460.start[i] = 0;
        if (g_00500460.container[i].header != 0)
            func_00102EC0(g_00500460.container[i].header);
    }
}

/* 0x00102680, 0x48 bytes, matching. The size of entry `entry` of container `which` (0 when closed). */
u32 func_00102680(int which, int entry)
{
    if (g_00500460.container[which].header == 0)
        return 0;
    return CONTAINER_INDEX(which)[entry][1];
}

/* 0x001026D0, 0x190 bytes. Reads entry `entry` of container `which` into `dest` (allocated when
 * 0): `size` bytes (the entry's when 0) from `offset`; at once when `now`, else queued. `file` /
 * `line` name the caller (unused here). */
void *func_001026D0(int which, int entry, void *dest, int now, u32 size, u32 offset,
                    const char *file, int line)
{
    u32 sectors, skip;

    if (size == 0)
        size = func_00102680(which, entry);
    sectors = (size + 0x7FF) >> 11;
    skip = (offset + 0x7FF) >> 11;
    if (dest == 0)
        dest = func_00102DB0(0x40, sectors * 0x800);
    if (func_00115C70() == 0 || which != 1 || ((u32)dest & 0x80000003) != 0) {
        u32 sector = g_00500460.start[which] + g_00500460.container[which].index[entry][0];

        if (now == 0)
            func_00100AC0(sector, skip, sectors, (u32)dest);
        else
            func_00100C60(sector, skip, sectors, (u32)dest);
    } else {
        u32 at = g_00500460.container[1].index[entry][0];

        if (now == 0)
            func_00100B90(g_0045CC04, skip + at, sectors, (u32)dest);
        else
            func_00100D00(g_0045CC04, skip + at, sectors, (u32)dest);
    }
    return dest;
}

/* 0x00102860, 0x1C bytes, matching. The size of a file by its path. */
u32 func_00102860(const char *path)
{
    return func_00115AC0(path);
}

/* 0x00102880, 0xD8 bytes. Reads a file by its path into `dest` (allocated when 0), at once when
 * `read`; the end of its last sector is cleared. */
void *func_00102880(const char *path, void *dest, int read, u32 size, u32 offset, const char *file,
                    int line)
{
    u32 bytes = size, sectors;

    if (size == 0)
        bytes = func_00102860(path);
    sectors = (bytes + 0x7FF) >> 11;
    if (dest == 0)
        dest = func_00102DB0(0x40, sectors * 0x800);
    if (read != 0) {
        func_00100D00((u32)path, (offset + 0x7FF) >> 11, sectors, (u32)dest);
        if ((size & 0x7FF) != 0)
            func_00118850((u8 *)dest + size, 0x800 - (size & 0x7FF));
    }
    return dest;
}

/* 0x00102960, 0x24 bytes, matching. Whether the reads are over (`wait` 0: waits for them). */
int func_00102960(int wait)
{
    return func_00100A30(wait) == 1;
}

/* 0x00102990, 0x1C bytes, matching. */
void func_00102990(void)
{
    func_00100AA0();
}

/* 0x001029B0, 0x50 bytes, matching. Starts reading: waits for the IOP side, empties the requests, opens
 * the containers. */
void func_001029B0(void)
{
    while (func_001151C0() < 0)
        ;
    func_00100DA0();
    func_00102410();
    g_00500460.ready = 1;
}

/* 0x00102A00, 0x20 bytes, matching. */
void func_00102A00(void)
{
    g_00500460.ready = 0;
    func_00102610();
}
