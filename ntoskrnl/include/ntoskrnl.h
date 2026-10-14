/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Kernel
 * FILE:            ntoskrnl/include/ntoskrnl.h
 * PURPOSE:         Main Kernel Header
 * PROGRAMMER:      Alex Ionescu (alex@relsoft.net)
 * CURRENTPROGRAMMER: SpixzyYT (@spixzyyt on YouTube)
 */

#ifndef _NTOSKRNL_PCH
#define _NTOSKRNL_PCH

/* INCLUDES ******************************************************************/

/*
 * ARM Bring-up Support
 *
 * Preserve the existing early-debug-output mapping used during ARM bring-up.
 */
#ifdef _M_ARM
#define DbgPrint DbgPrintEarly
#endif

/*
 * AMD64 WDK Compatibility
 *
 * These aliases preserve the symbol names expected by this codebase.
 */
#ifdef _M_AMD64
#define IoAllocateAdapterChannel _IoAllocateAdapterChannel
#define KeGetCurrentThread _KeGetCurrentThread
#define RtlFillMemoryUlong _RtlFillMemoryUlong
#endif

/* Version Information */
#undef __MSVCRT__
#include <psdk/ntverp.h>

/*
 * DDK, IFS and NDK Headers
 *
 * Keep the original ordering: these declarations precede the
 * kernel's internal configuration and implementation headers.
 */
#define _REALLY_GET_CALLERS_CALLER

#include <excpt.h>
#include <ntdef.h>
#include <ntifs.h>
#include <wdmguid.h>
#include <diskguid.h>
#include <arc/arc.h>
#include <mountmgr.h>

/*
 * HAL API Imports
 *
 * Preserve the existing import configuration for NTHALAPI.
 */
#undef NTHALAPI
#define NTHALAPI __declspec(dllimport)

/* Native Development Kit Headers */
#include <ndk/asm.h>
#include <ndk/cctypes.h>
#include <ndk/cmfuncs.h>
#include <ndk/dbgkfuncs.h>
#include <ndk/exfuncs.h>
#include <ndk/halfuncs.h>
#include <ndk/inbvfuncs.h>
#include <ndk/iofuncs.h>
#include <ndk/kdfuncs.h>
#include <ndk/kefuncs.h>
#include <ndk/ldrfuncs.h>
#include <ndk/lpcfuncs.h>
#include <ndk/mmfuncs.h>
#include <ndk/muptypes.h>
#include <ndk/obfuncs.h>
#include <ndk/pofuncs.h>
#include <ndk/psfuncs.h>
#include <ndk/rtlfuncs.h>
#include <ndk/sefuncs.h>
#include <ndk/vftypes.h>

/*
 * String Compatibility
 *
 * The kernel expects TEXT() to generate wide-string literals.
 */
#undef TEXT
#define TEXT(s) L##s

#define _IN_KERNEL_
#include <regstr.h>

#include <ntstrsafe.h>
#include <ntpoapi.h>

/*
 * Integer Safety Functions
 *
 * Enable signed integer-safe functions only for this include.
 */
#define ENABLE_INTSAFE_SIGNED_FUNCTIONS
#include <ntintsafe.h>
#undef ENABLE_INTSAFE_SIGNED_FUNCTIONS

/* Standard C Headers */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <wchar.h>

/* Structured Exception Handling */
#include <pseh/pseh2.h>

/* Setup Loader Support */
#include <arc/setupblk.h>

/*
 * Kernel Debugger Support
 *
 * Preserve the original debugger declarations and conditional
 * KDBG symbol remapping.
 */
#define NOEXTAPI
#include <windbgkd.h>
#include <wdbgexts.h>
#include <kddll.h>

#ifdef KDBG

    /*
     * Redirect debugger exports to their KDBG implementations.
     */
    #define KdD0Transition  KdbgD0Transition
    #define KdD3Transition  KdbgD3Transition
    #define KdSave          KdbgSave
    #define KdRestore       KdbgRestore
    #define KdSendPacket    KdbgSendPacket
    #define KdReceivePacket KdbgReceivePacket

    /*
     * Reload the definitions using the KDBG symbol mappings.
     * Retain the original ReactOS header-reload mechanism.
     */
    #undef _KDDLL_
    #include <kddll.h>

#endif /* KDBG */

/* Plug and Play System GUIDs */
#include <umpnpmgr/sysguid.h>

/* Security Reference Monitor */
#include <srmp.h>

/*
 * Status Exception Compatibility
 *
 * Preserve the existing alias used throughout the kernel.
 */
#define ExRaiseStatus RtlRaiseStatus

/*
 * Pointer Helpers
 *
 * These helpers are also defined by fltkernel.h. Avoid redefining
 * them if a preceding header has already provided the macros.
 */
#ifndef Add2Ptr
#define Add2Ptr(P,I) ((PVOID)((PUCHAR)(P) + (I)))
#endif

#ifndef PtrOffset
#define PtrOffset(B,O) ((ULONG)((ULONG_PTR)(O) - (ULONG_PTR)(B)))
#endif

/*
 * MAX_PATH Compatibility Check
 *
 * Preserve the original check and subsequent undefinition.
 * Do not introduce a fallback that masks a missing definition.
 */
#define MAX_WIN32_PATH 260
C_ASSERT(MAX_WIN32_PATH == MAX_PATH);
#undef MAX_PATH

/*
 * Internal Kernel Headers
 *
 * Keep config.h immediately before internal/ntoskrnl.h, as in
 * the original StratumOS branch.
 */
#include "config.h"
#include "internal/ntoskrnl.h"

#include <reactos/probe.h>
#include "internal/probe.h"
#include "resource.h"

/* Internal Process Structure Alignment Probing */
#include "internal/ps_i.h"

/* MSVC-Specific Section Attributes */
#ifdef _MSC_VER
#pragma section("INITDATA", read, write, discard)
#endif

#endif /* _NTOSKRNL_PCH */
