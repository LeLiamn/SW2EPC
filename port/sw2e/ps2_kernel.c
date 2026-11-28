/*
 * ps2_kernel.c - the EE kernel calls the game makes (threads, semaphores, DMA handlers, cache),
 * on top of the UPP platform. Nothing here is specific to SW2E: the same layer serves any PS2
 * game of the family.
 *
 * Semaphores map to platform events (counting, like the PS2's), threads to platform threads
 * (priority 1 = highest, as on the PS2; UPP_THREADS_PS2 keeps one thread running at a time).
 * Thread ids: 0 is the thread running run() (the game's main thread), as in UPP's numbering.
 * A PS2 thread is created dormant and started by StartThread, so the PS2 ids given out here map
 * to the platform ids of the started threads.
 * DMA end handlers are not interrupts on the PC: the port calls them where the transfer ends.
 */
#include <string.h>
#include "upp.h"

extern const upp_platform *sw2e_platform;
#define P sw2e_platform

/* ee_sema_t */
typedef struct {
    int count, max_count, init_count, wait_threads;
    unsigned attr, option;
} SemaParam;

/* ee_thread_t */
typedef struct {
    int status;
    void (*entry)(void *);
    void *stack;
    int stack_size;
    void *gp;
    int priority;
    int option;
} ThreadParam;

#define MAX_THREADS 32
/* PS2 id -> its entry, priority and platform id (-1 while dormant); 0 = the run() thread */
static struct { void (*entry)(void *); int priority; int id; } g_threads[MAX_THREADS] = { { 0, 0, 0 } };
static int g_nthreads = 1;

static int plat_id(int thread)
{
    if (thread == 0)                        /* TH_SELF */
        return P->thread_self();
    return thread > 0 && thread < g_nthreads ? g_threads[thread].id : -1;
}

/* ---- semaphores ---- */

int CreateSema(SemaParam *p) { return P->event_create(p->init_count, p->max_count); }
int DeleteSema(int sema) { P->event_destroy(sema); return sema; }
int WaitSema(int sema) { return P->event_wait(sema, -1) ? sema : -1; }
int PollSema(int sema) { return P->event_wait(sema, 0) ? sema : -1; }
int SignalSema(int sema) { P->event_signal(sema); return sema; }
int iSignalSema(int sema) { P->event_signal(sema); return sema; }

static int refer(int sema, SemaParam *status)
{
    int n = P->event_count(sema);

    if (n < 0)
        return -1;
    memset(status, 0, sizeof(*status));
    status->count = n;
    return sema;
}

int ReferSemaStatus(int sema, void *status) { return refer(sema, status); }
int iReferSemaStatus(int sema, void *status) { return refer(sema, status); }

/* ---- threads ---- */

int CreateThread(ThreadParam *p)
{
    int i = g_nthreads;

    if (i >= MAX_THREADS)
        return -1;
    g_nthreads++;
    g_threads[i].entry = p->entry;
    g_threads[i].priority = p->priority;
    g_threads[i].id = -1;
    return i;
}

/* StartThread(thread, arg): the dormant thread starts on a platform thread. */
int StartThread(int thread, void *arg)
{
    if (thread <= 0 || thread >= g_nthreads || g_threads[thread].id >= 0)
        return -1;
    g_threads[thread].id = P->thread_create((upp_thread_fn)g_threads[thread].entry, arg, g_threads[thread].priority);
    return g_threads[thread].id >= 0 ? thread : -1;
}

int GetThreadId(void)
{
    int self = P->thread_self(), i;

    for (i = 1; i < g_nthreads; i++)
        if (g_threads[i].id == self)
            return i;
    return 0;
}

int ChangeThreadPriority(int thread, int priority)
{
    int id = plat_id(thread);

    if (thread > 0 && thread < g_nthreads)
        g_threads[thread].priority = priority;
    if (id >= 0)
        P->thread_set_priority(id, priority);
    return thread;
}

int SleepThread(void) { P->thread_sleep(); return 0; }

int WakeupThread(int thread)
{
    int id = plat_id(thread);

    if (id >= 0)
        P->thread_wakeup(id);
    return thread;
}

int iWakeupThread(int thread) { return WakeupThread(thread); }

int TerminateThread(int thread)
{
    int id = plat_id(thread);

    if (id >= 0)
        P->thread_terminate(id);
    return thread;
}

int DeleteThread(int thread)
{
    if (thread > 0 && thread < g_nthreads)
        g_threads[thread].id = -1;          /* the PS2 id may be started again */
    return thread;
}

void ExitThread(void) { P->thread_exit(); }

/* ---- cache: nothing to flush on the PC ---- */

void FlushCache(int a) { (void)a; }
void iFlushCache(int a) { (void)a; }

/* ---- DMA end handlers: kept so the port can call them where a transfer ends ---- */

static int (*g_dmac[16])(int);

int AddDmacHandler(int channel, int (*handler)(int), int next)
{
    (void)next;
    if (channel < 0 || channel >= 16)
        return -1;
    g_dmac[channel] = handler;
    return channel;
}

int RemoveDmacHandler(int channel, int id)
{
    (void)id;
    if (channel >= 0 && channel < 16)
        g_dmac[channel] = 0;
    return channel;
}

/* The handler of DMA channel `channel`, for the port's transfer code (0 = none). */
int (*sw2e_dmac_handler(int channel))(int)
{
    return channel >= 0 && channel < 16 ? g_dmac[channel] : 0;
}

/* The game's _gp (the MIPS global pointer): only stored in thread parameters, unused on the PC. */
unsigned char _gp[16];
