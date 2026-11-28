/*
 * ps2_kernel.c - the EE kernel calls the game makes (threads, semaphores, DMA handlers, cache),
 * on top of the UPP platform. Nothing here is specific to SW2E: the same layer serves any PS2
 * game of the family.
 *
 * Semaphores map to platform events (counting, like the PS2's), threads to platform threads
 * (priority 1 = highest, as on the PS2; UPP_THREADS_PS2 keeps one thread running at a time).
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
static struct { void (*entry)(void *); int priority; int id; int started; } g_threads[MAX_THREADS];
static int g_nthreads = 1;          /* 0 = the main game thread */

int CreateSema(SemaParam *p)
{
    return P->event_create(p->init_count, p->max_count);
}

int DeleteSema(int sema) { P->event_destroy(sema); return sema; }
int WaitSema(int sema) { return P->event_wait(sema, -1) ? sema : -1; }
int PollSema(int sema) { return P->event_wait(sema, 0) ? sema : -1; }
int SignalSema(int sema) { P->event_signal(sema); return sema; }
int iSignalSema(int sema) { P->event_signal(sema); return sema; }

int iReferSemaStatus(int sema, void *status)
{
    (void)sema;
    memset(status, 0, sizeof(SemaParam));   /* not tracked by the platform: the count reads 0 */
    P->log(1, "iReferSemaStatus: semaphore status not available");
    return sema;
}

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

/* StartThread(thread, arg) starts the entry on a platform thread. */
int StartThread(int thread, void *arg)
{
    if (thread <= 0 || thread >= g_nthreads || g_threads[thread].started)
        return -1;
    g_threads[thread].started = 1;
    g_threads[thread].id = P->thread_create((upp_thread_fn)g_threads[thread].entry, arg, g_threads[thread].priority);
    return thread;
}

int ChangeThreadPriority(int thread, int priority)
{
    if (thread > 0 && thread < g_nthreads)
        g_threads[thread].priority = priority;    /* applies when the platform supports it */
    return thread;
}

int GetThreadId(void) { return 0; }       /* the platform does not tell; 0 = the main thread */
int SleepThread(void) { P->thread_yield(); return 0; }
int WakeupThread(int thread) { (void)thread; return 0; }
int TerminateThread(int thread) { (void)thread; P->log(1, "TerminateThread: not supported"); return 0; }
int DeleteThread(int thread) { (void)thread; return 0; }
void ExitThread(void) { P->log(1, "ExitThread: not supported"); }

/* Caches do not need flushing on the PC. */
void FlushCache(int a) { (void)a; }
void iFlushCache(int a) { (void)a; }

/* DMA end handlers: kept so the port can call them where a transfer ends. */
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
