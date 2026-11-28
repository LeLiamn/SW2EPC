/*
 * sw2e_ee_kernel.h - the PC names of the EE kernel calls (port/sw2e/ps2_kernel.c).
 *
 * Several PS2 kernel names are also Windows kernel32 functions (CreateThread, ExitThread,
 * TerminateThread, GetThreadId). Defining them in the game would make the link fail, or send the
 * runtime's own thread creation into the game's code. So the PC build gives every EE kernel call
 * an ee_ prefix, and the game's sources keep the original names through these macros
 * (src/sw2e_mem.h includes this file on the PC build only).
 */
#ifndef SW2E_EE_KERNEL_H
#define SW2E_EE_KERNEL_H

#define CreateSema ee_CreateSema
#define DeleteSema ee_DeleteSema
#define WaitSema ee_WaitSema
#define PollSema ee_PollSema
#define SignalSema ee_SignalSema
#define iSignalSema ee_iSignalSema
#define ReferSemaStatus ee_ReferSemaStatus
#define iReferSemaStatus ee_iReferSemaStatus
#define CreateThread ee_CreateThread
#define StartThread ee_StartThread
#define GetThreadId ee_GetThreadId
#define ChangeThreadPriority ee_ChangeThreadPriority
#define SleepThread ee_SleepThread
#define WakeupThread ee_WakeupThread
#define iWakeupThread ee_iWakeupThread
#define TerminateThread ee_TerminateThread
#define DeleteThread ee_DeleteThread
#define ExitThread ee_ExitThread
#define FlushCache ee_FlushCache
#define iFlushCache ee_iFlushCache
#define AddDmacHandler ee_AddDmacHandler
#define RemoveDmacHandler ee_RemoveDmacHandler

#endif
