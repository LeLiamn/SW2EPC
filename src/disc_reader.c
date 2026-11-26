/*
 * disc_reader.c - the disc reader thread (original source file unknown; 0x001158A0-0x00116604,
 * after the music stream code).
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses. The libcdvd and C library functions called here are
 * named in the comments by their likely Sony names.
 *
 * The reads of file.c and system.c are handed to a thread of their own (priority 5, its stack
 * at 0x00561000) as a list of up to 255 requests (sector or file path, offset, sectors,
 * destination). The thread reads them in chunks of at most 0x400 sectors, waiting before each
 * chunk until the music stream has enough data buffered (the music and the game's data come from
 * the same disc). A request names a file when its first word has bit 31 set (a pointer to
 * "cdrom0:\\PATH"); a destination with bit 31 set goes to the IOP's memory, bit 1 to the sound
 * driver's (?). The reads can be cancelled (func_00115D40).
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* A read request. */
typedef struct {
    u32 source;              /* a sector, or (bit 31) a pointer to the file's path */
    int offset;              /* sectors */
    u32 count;               /* sectors */
    u32 dest;                /* the destination, flags in its low bits and bit 31 */
} ReadRequest;

/* A file found on the disc (sceCdlFILE). */
typedef struct {
    u32 lsn;
    u32 size;
    u8 rest[0x28];
} DiscFile;

/* The reader (0x00561000). */
extern struct {
    u8 stack[0x800];         /* the thread's stack */
    int thread;              /* 0x00561800 */
    int done_sema;           /* 0x00561804 signalled when a list is over */
    int lock_sema;           /* 0x00561808 */
    int sema3;               /* 0x0056180C */
    int busy;                /* 0x00561810 */
    int cancel;              /* 0x00561814 */
    int reading;             /* 0x00561818 a libcdvd read is under way */
    int count;               /* 0x0056181C requests in the list */
    int done;                /* 0x00561820 requests read */
    int host;                /* 0x00561824 */
    ReadRequest list[256];   /* 0x00561828 */
    u8 mode[4];              /* 0x00562828 the read mode (sceCdRMode) */
} g_00561000;

/* A thread's parameters (ee_thread_t). */
typedef struct {
    int status;
    void (*entry)(void *);
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    int option;
} ThreadParam;

/* A semaphore's parameters (ee_sema_t). */
typedef struct {
    int count;
    int max_count;
    int init_count;
    int wait_threads;
    u32 attr;
    u32 option;
} SemaParam;

extern u8 _gp[];

int func_00121068(int c);                                  /* toupper */
int func_001204B0(char *out, const char *format, ...);     /* sprintf */
char *func_00120928(char *to, const char *from);           /* strcpy */
char *func_001206B0(char *to, const char *from);           /* strcat */
int func_0012D168(const char *path, int mode);             /* open */
int func_0012D570(int fd, int offset, int whence);         /* lseek */
int func_0012D7B0(int fd, void *buffer, int size);         /* read */
int func_0012D3F8(int fd);                                 /* close */
int func_001194A0(DiscFile *file, const char *name, int a);  /* sceCdSearchFile */
int func_0011A1C8(int mode);                               /* sceCdDiskReady */
int func_0011A720(void);                                   /* sceCdStatus? */
int func_001199B0(int mode);                               /* sceCdSync */
int func_0011A3E8(u32 lsn, u32 sectors, void *buffer, void *mode);   /* sceCdRead */
int func_0011A5C8(u32 lsn, u32 sectors, void *buffer, void *mode);   /* sceCdReadIOPm? */
int func_0011A7D0(void);                                   /* sceCdGetError */
int func_0011A868(void);                                   /* sceCdBreak */
int func_0011A920(int media);                              /* sceCdMmode */
int func_0010B6E0(int port, u32 source, int offset, u32 dest, u32 count);
int func_0010B7B8(int port, u32 source, int offset, u32 dest, u32 count);
int func_0010C4D0(int port);
u32 func_0010C538(void);
u32 func_0010C570(int a, int b);
void func_0010C420(void);
void func_0010C478(int port);
void func_00131EA0(void);                                  /* DI? */
void func_00131EF0(void);                                  /* EI? */
void func_00128F20(int thread, void *arg);                 /* StartThread */
int func_00115820(void);
void func_00115860(int paused);
void func_001152A0(void);
void func_001171B0(void);
void func_00117220(int port);
int CreateSema(SemaParam *p);
int CreateThread(ThreadParam *p);
int WaitSema(int sema);
int PollSema(int sema);
int SignalSema(int sema);
int SleepThread(void);
int WakeupThread(int thread);

int func_00115C80(int poll);

/* 0x001158A0, 0xF0 bytes. A disc path for libcdvd: "\\PATH;1", upper case, '/' as '\\', the
 * leading "./" and '/' left out. */
void func_001158A0(char *out, const char *path)
{
    char name[96];
    char *p = name;
    int n = 0, i, started = 0;

    for (i = 0; i < 0x5D; i++, path++) {
        char c = *path;

        if (c == '\0') {
            name[n] = '\0';
            break;
        }
        if (c == '/') {
            if (!started)
                continue;
            *p = '\\';
        } else if (c == '.') {
            if (!started)
                continue;
            *p = '.';
        } else {
            *p = func_00121068(c);
        }
        started = 1;
        p++;
        n++;
    }
    func_001204B0(out, "\\%s;1", name);
}

/* 0x001159A0, 0xA8 bytes. Finds a file on the disc (5 tries, waiting for the drive between
 * them); 0 when not found. */
int func_001159A0(DiscFile *file, const char *path, int a)
{
    char name[96];
    int tries = 5;
    int found;

    func_001158A0(name, path);
    do {
        found = func_001194A0(file, name, a != 0);
        if (found != 0)
            return found;
        func_0011A1C8(0);
        while (func_0011A720() == 0)
            ;
        func_001199B0(0);
    } while (--tries != 0);
    return 0;
}

/* 0x00115A50, 0x6C bytes, matching. The same, once the reader is idle, with the music paused. */
int func_00115A50(DiscFile *file, const char *path, int a)
{
    int paused, found;

    func_00115C80(0);
    paused = func_00115820();
    found = func_001159A0(file, path, a);
    func_00115860(paused);
    return found;
}

/* 0x00115AC0, 0xA8 bytes. A file's size by its path (through the C library), -1 when it
 * cannot be opened. */
int func_00115AC0(const char *path)
{
    char name[96];
    int paused, fd, size;

    func_00115C80(0);
    paused = func_00115820();
    func_00120928(name, "cdrom0:");
    func_001206B0(name, path);
    fd = func_0012D168(name, 1);
    if (fd < 0) {
        size = -1;
    } else {
        size = func_0012D570(fd, 0, 2);
        func_0012D3F8(fd);
    }
    func_00115860(paused);
    return size;
}

/* 0x00115B70, 0x50 bytes. Starts reading the list's `count` requests. */
int func_00115B70(int count)
{
    g_00561000.done = 0;
    g_00561000.busy = 1;
    g_00561000.cancel = 0;
    g_00561000.reading = 0;
    g_00561000.count = count;
    WakeupThread(g_00561000.thread);
    return 1;
}

/* 0x00115BC0, 0xB0 bytes. Hands a list of requests (ended by one with a -1) to the reader, when
 * it is idle; whether it took it. */
int func_00115BC0(ReadRequest *r)
{
    u32 n;
    ReadRequest *to;

    if (func_00115C80(1) != 0)
        return 0;
    for (n = 0, to = g_00561000.list; n < 0xFF; n++, r++, to++) {
        if (r->source == (u32)-1 || r->offset == -1 || r->count == (u32)-1 || r->dest == (u32)-1)
            break;
        *to = *r;
    }
    return func_00115B70(n);
}

/* 0x00115C70, 0xC bytes, matching. */
int func_00115C70(void)
{
    return g_00561000.host;
}

/* 0x00115C80, 0xB8 bytes. Whether the reader is busy; `poll` 0: waits until it is not. */
int func_00115C80(int poll)
{
    int busy = 0;

    if ((poll & 1) == 0) {
        WaitSema(g_00561000.lock_sema);
    } else if (PollSema(g_00561000.lock_sema) == -1) {
        return 1;
    }
    if (g_00561000.busy != 0) {
        if ((poll & 1) == 0) {
            WaitSema(g_00561000.done_sema);
        } else if (PollSema(g_00561000.done_sema) == -1) {
            busy = 1;
            goto end;
        }
        g_00561000.busy = 0;
    }
end:
    SignalSema(g_00561000.lock_sema);
    return busy;
}

/* 0x00115D40, 0x58 bytes, matching. Cancels the reads under way. */
void func_00115D40(void)
{
    if (func_00115C80(1) != 0) {
        if (g_00561000.cancel == 0 && g_00561000.reading != 0)
            func_0011A868();
        g_00561000.cancel = 1;
    }
}

/* 0x00115DA0, 0x60 bytes. Sets the read mode (the default: no retry, normal speed). */
void func_00115DA0(const u8 *mode)
{
    if (mode == 0) {
        g_00561000.mode[0] = 0;
        g_00561000.mode[1] = 1;
        g_00561000.mode[2] = 0;
    } else {
        g_00561000.mode[0] = mode[0];
        g_00561000.mode[1] = mode[1];
        g_00561000.mode[2] = mode[2];
        g_00561000.mode[3] = mode[3];
    }
}

/* 0x00115E00, 0xBC bytes, matching. Reads `count` sectors from `offset` of file `fd` (C library), or of
 * `source` into the IOP's memory when the destination's bit 0 is set. 1, or -1. */
int func_00115E00(int fd, u32 source, int offset, u32 count, u32 dest)
{
    u32 to = dest & ~3;

    if (dest & 1) {
        if (func_0010B6E0(1, source, offset, to, count) < 0)
            return -1;
    } else {
        int size = offset << 11;

        if (func_0012D570(fd, size, 0) != size)
            return -1;
        size = count * 0x800;
        if (func_0012D7B0(fd, (void *)to, size) < size - 0x7FF)
            return -1;
    }
    return 1;
}

/* 0x00115EC0, 0x16C bytes. Reads `count` sectors from sector `lsn` + `offset` (libcdvd), once
 * the drive is ready. 1, or -1 (error), -2 (cancelled or retry). */
int func_00115EC0(u32 lsn, int offset, u32 count, u32 dest)
{
    int r = func_0011A1C8(1);

    for (;;) {
        if (r == 2) {
            g_00561000.reading = 1;
            if ((dest & 1) == 0)
                r = func_0011A3E8(offset + lsn, count, (void *)(dest & ~3), g_00561000.mode);
            else
                r = func_0011A5C8(offset + lsn, count, (void *)(dest & ~3), g_00561000.mode);
            if (r != 0)
                func_001199B0(0);
            g_00561000.reading = 0;
            if (g_00561000.cancel != 0)
                return -2;
            if (r == 0)
                return -1;
            r = func_0011A7D0();
            if (r == 0x31)
                return -1;
            if (r == 1)
                return -2;
            if (r != 0)
                return -1;
            return 1;
        }
        if (g_00561000.cancel != 0)
            break;
        r = func_0011A1C8(1);
    }
    return -2;
}

/* 0x00116030, 0x60 bytes, matching. Reads a chunk from the disc (or, source with bit 31, as
 * func_00115E00). */
int func_00116030(int fd, u32 source, int offset, u32 count, u32 dest)
{
    if (g_00561000.cancel != 0)
        return -2;
    if (source & 0x80000000)
        return func_00115E00(fd, source, offset, count, dest);
    return func_00115EC0(source, offset, count, dest);
}

/* 0x00116090, 0x88 bytes. A read to the IOP's memory (destination bit 31). */
int func_00116090(u32 source, int offset, u32 count, u32 dest)
{
    int r = 1;

    if (dest & 1) {
        if (source & 0x80000000) {
            if (func_0010B6E0(1, source, offset, dest & 0x7FFFFFFE, count) < 0)
                r = -1;
        } else {
            return func_00115EC0(source, offset, count, dest);
        }
    }
    return r;
}

/* 0x00116120, 0x60 bytes. A read through the sound driver: 1, -1 (busy: try again) or -3. */
int func_00116120(u32 source, int offset, u32 dest, u32 count)
{
    int r = func_0010B7B8(1, source, offset, dest, count);

    if (r >= 0)
        return 1;
    if (r == -4)
        return -1;
    return -3;
}

/* 0x00116180, 0x78 bytes. The same, once the queued sound commands are sent, until it is
 * taken. */
int func_00116180(u32 source, int offset, u32 count, u32 dest)
{
    func_001171B0();
    func_00117220(1);
    while (func_00116120(source, offset, dest & ~2, count) == -1)
        ;
    return 1;
}

/* 0x00116200, 0xF8 bytes. Before a chunk: lets the music stream fill its buffer (from below
 * 0x32 to 0x5F) when it plays, then pauses it. 0 when cancelled. */
int func_00116200(void)
{
    func_001152A0();
    func_0010C4D0(1);
    if ((func_0010C538() & 1) && func_0010C570(0, 0) < 0x32) {
        if ((func_0010C538() & 0x41) == 0x41)
            func_0010C478(1);
        while ((func_0010C538() & 1) && func_0010C570(0, 0) < 0x5F) {
            if (g_00561000.cancel != 0)
                return 0;
            func_001152A0();
        }
    }
    if ((func_0010C538() & 0x41) == 1)
        func_0010C420();
    return 1;
}

/* 0x00116300, 0x214 bytes. The reader thread: sleeps until a list comes, reads it request by
 * request (files found by their path once each), then resumes the music and signals the end. */
void func_00116300(void *arg)
{
    for (;;) {
        u32 last = 0, lsn = 0;
        int i;

        SleepThread();
        for (i = 0; i < g_00561000.count; i++) {
            ReadRequest *q = &g_00561000.list[i];
            u32 source = q->source;
            u32 left = q->count;
            u32 dest = q->dest;
            int offset = q->offset;
            int r;

            if ((source & 0x80000000) == 0) {
                lsn = source;
            } else if (source != last) {
                const char *path = (const char *)(source & 0x7FFFFFFF);
                DiscFile file;

                while (*path++ != ':')
                    ;
                while (func_001159A0(&file, path, 0) == 0)
                    ;
                lsn = file.lsn;
                last = source;
            }
            do {
                if (func_00116200() == 0) {
                    r = -2;
                    break;
                }
                if (dest & 0x80000000) {
                    r = func_00116090(lsn, offset, left, dest);
                } else if ((dest & 2) == 0 || (dest & 1) != 0) {
                    u32 n = left > 0x400 ? 0x400 : left;

                    r = func_00116030(-1, lsn, offset, n, dest);
                    if (r == 1) {
                        left -= n;
                        offset += n;
                        dest += n * 0x800;
                        if (left != 0)
                            r = -1;
                    }
                } else {
                    r = func_00116180(lsn, offset, left, dest);
                }
            } while (r == -1);
            if (r == -2)
                break;
            func_00131EA0();
            g_00561000.done++;
            func_00131EF0();
        }
        if ((func_0010C4D0(1) & 0x41) == 0x41)
            func_0010C478(1);
        SignalSema(g_00561000.done_sema);
    }
}

/* 0x00116520, 0xE8 bytes. Creates the reader's semaphores and thread, and starts it. */
void func_00116520(void)
{
    SemaParam s;
    ThreadParam t;

    s.max_count = 1;
    s.init_count = 0;
    s.option = 0;
    g_00561000.done_sema = CreateSema(&s);
    s.option = 0;
    s.max_count = 1;
    s.init_count = 1;
    g_00561000.lock_sema = CreateSema(&s);
    s.option = 0;
    s.max_count = 1;
    s.init_count = 1;
    g_00561000.sema3 = CreateSema(&s);
    g_00561000.busy = 0;
    g_00561000.done = 0;
    func_00115DA0(0);
    g_00561000.host = 0;
    t.option = 0;
    t.entry = func_00116300;
    t.stack = g_00561000.stack;
    t.stack_size = 0x800;
    t.priority = 5;
    t.gp = _gp;
    g_00561000.thread = CreateThread(&t);
    func_00128F20(g_00561000.thread, &g_00561000);
}
