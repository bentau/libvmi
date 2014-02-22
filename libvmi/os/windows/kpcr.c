/* The LibVMI Library is an introspection library that simplifies access to
 * memory in a target virtual machine or in a file containing a dump of
 * a system's physical memory.  LibVMI is based on the XenAccess Library.
 *
 * Copyright 2011 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
 * retains certain rights in this software.
 *
 * Author: Bryan D. Payne (bdpayne@acm.org)
 *
 * This file is part of LibVMI.
 *
 * LibVMI is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * LibVMI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LibVMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "libvmi.h"
#include "peparse.h"
#include "private.h"
#define _GNU_SOURCE
#include <string.h>

struct _DBGKD_DEBUG_DATA_HEADER64 {
    uint64_t List[2];
    uint32_t OwnerTag;
    uint32_t Size;
} __attribute__ ((packed));
typedef struct _DBGKD_DEBUG_DATA_HEADER64 DBGKD_DEBUG_DATA_HEADER64;

struct _KDDEBUGGER_DATA64 {
    DBGKD_DEBUG_DATA_HEADER64 Header;
    uint64_t KernBase;
    uint64_t BreakpointWithStatus;
    uint64_t SavedContext;
    uint16_t ThCallbackStack;
    uint16_t NextCallback;
    uint16_t FramePointer;
    uint16_t PaeEnabled;
    uint64_t KiCallUserMode;
    uint64_t KeUserCallbackDispatcher;
    uint64_t PsLoadedModuleList;
    uint64_t PsActiveProcessHead;
    uint64_t PspCidTable;
    uint64_t ExpSystemResourcesList;
    uint64_t ExpPagedPoolDescriptor;
    uint64_t ExpNumberOfPagedPools;
    uint64_t KeTimeIncrement;
    uint64_t KeBugCheckCallbackListHead;
    uint64_t KiBugcheckData;
    uint64_t IopErrorLogListHead;
    uint64_t ObpRootDirectoryObject;
    uint64_t ObpTypeObjectType;
    uint64_t MmSystemCacheStart;
    uint64_t MmSystemCacheEnd;
    uint64_t MmSystemCacheWs;
    uint64_t MmPfnDatabase;
    uint64_t MmSystemPtesStart;
    uint64_t MmSystemPtesEnd;
    uint64_t MmSubsectionBase;
    uint64_t MmNumberOfPagingFiles;
    uint64_t MmLowestPhysicalPage;
    uint64_t MmHighestPhysicalPage;
    uint64_t MmNumberOfPhysicalPages;
    uint64_t MmMaximumNonPagedPoolInBytes;
    uint64_t MmNonPagedSystemStart;
    uint64_t MmNonPagedPoolStart;
    uint64_t MmNonPagedPoolEnd;
    uint64_t MmPagedPoolStart;
    uint64_t MmPagedPoolEnd;
    uint64_t MmPagedPoolInformation;
    uint64_t MmPageSize;
    uint64_t MmSizeOfPagedPoolInBytes;
    uint64_t MmTotalCommitLimit;
    uint64_t MmTotalCommittedPages;
    uint64_t MmSharedCommit;
    uint64_t MmDriverCommit;
    uint64_t MmProcessCommit;
    uint64_t MmPagedPoolCommit;
    uint64_t MmExtendedCommit;
    uint64_t MmZeroedPageListHead;
    uint64_t MmFreePageListHead;
    uint64_t MmStandbyPageListHead;
    uint64_t MmModifiedPageListHead;
    uint64_t MmModifiedNoWritePageListHead;
    uint64_t MmAvailablePages;
    uint64_t MmResidentAvailablePages;
    uint64_t PoolTrackTable;
    uint64_t NonPagedPoolDescriptor;
    uint64_t MmHighestUserAddress;
    uint64_t MmSystemRangeStart;
    uint64_t MmUserProbeAddress;
    uint64_t KdPrintCircularBuffer;
    uint64_t KdPrintCircularBufferEnd;
    uint64_t KdPrintWritePointer;
    uint64_t KdPrintRolloverCount;
    uint64_t MmLoadedUserImageList;
    uint64_t NtBuildLab;
    uint64_t KiNormalSystemCall;
    uint64_t KiProcessorBlock;
    uint64_t MmUnloadedDrivers;
    uint64_t MmLastUnloadedDriver;
    uint64_t MmTriageActionTaken;
    uint64_t MmSpecialPoolTag;
    uint64_t KernelVerifier;
    uint64_t MmVerifierData;
    uint64_t MmAllocatedNonPagedPool;
    uint64_t MmPeakCommitment;
    uint64_t MmTotalCommitLimitMaximum;
    uint64_t CmNtCSDVersion;
    uint64_t MmPhysicalMemoryBlock;
    uint64_t MmSessionBase;
    uint64_t MmSessionSize;
    uint64_t MmSystemParentTablePage;
    uint64_t MmVirtualTranslationBase;
    uint16_t OffsetKThreadNextProcessor;
    uint16_t OffsetKThreadTeb;
    uint16_t OffsetKThreadKernelStack;
    uint16_t OffsetKThreadInitialStack;
    uint16_t OffsetKThreadApcProcess;
    uint16_t OffsetKThreadState;
    uint16_t OffsetKThreadBStore;
    uint16_t OffsetKThreadBStoreLimit;
    uint16_t SizeEProcess;
    uint16_t OffsetEprocessPeb;
    uint16_t OffsetEprocessParentCID;
    uint16_t OffsetEprocessDirectoryTableBase;
    uint16_t SizePrcb;
    uint16_t OffsetPrcbDpcRoutine;
    uint16_t OffsetPrcbCurrentThread;
    uint16_t OffsetPrcbMhz;
    uint16_t OffsetPrcbCpuType;
    uint16_t OffsetPrcbVendorString;
    uint16_t OffsetPrcbProcStateContext;
    uint16_t OffsetPrcbNumber;
    uint16_t SizeEThread;
    uint64_t KdPrintCircularBufferPtr;
    uint64_t KdPrintBufferSize;
    uint64_t KeLoaderBlock;
    uint16_t SizePcr;
    uint16_t OffsetPcrSelfPcr;
    uint16_t OffsetPcrCurrentPrcb;
    uint16_t OffsetPcrContainedPrcb;
    uint16_t OffsetPcrInitialBStore;
    uint16_t OffsetPcrBStoreLimit;
    uint16_t OffsetPcrInitialStack;
    uint16_t OffsetPcrStackLimit;
    uint16_t OffsetPrcbPcrPage;
    uint16_t OffsetPrcbProcStateSpecialReg;
    uint16_t GdtR0Code;
    uint16_t GdtR0Data;
    uint16_t GdtR0Pcr;
    uint16_t GdtR3Code;
    uint16_t GdtR3Data;
    uint16_t GdtR3Teb;
    uint16_t GdtLdt;
    uint16_t GdtTss;
    uint16_t Gdt64R3CmCode;
    uint16_t Gdt64R3CmTeb;
    uint64_t IopNumTriageDumpDataBlocks;
    uint64_t IopTriageDumpDataBlocks;
    uint64_t VfCrashDataBlock;
} __attribute__ ((packed));
typedef struct _KDDEBUGGER_DATA64 KDDEBUGGER_DATA64;

static status_t
kpcr_symbol_resolve(
    vmi_instance_t vmi,
    unsigned long offset,
    addr_t *address)
{
    uint64_t tmp = 0;
    addr_t symaddr = 0;
    windows_instance_t windows = NULL;

    if (vmi->os_data == NULL) {
        return VMI_FAILURE;
    }

    windows = vmi->os_data;
    symaddr = windows->kdversion_block + offset;

    if (VMI_FAILURE == vmi_read_64_pa(vmi, symaddr, &tmp)) {
        return VMI_FAILURE;
    }
    *address = tmp;
    return VMI_SUCCESS;
}

static status_t
kpcr_symbol_offset(
    vmi_instance_t vmi,
    char *symbol,
    unsigned long *offset)
{
    KDDEBUGGER_DATA64 d;
    unsigned long max_symbol_length = 50;

    if (strncmp(symbol, "KernBase", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KernBase)) - (unsigned long) (&d);
    }
    else if (strncmp(symbol, "BreakpointWithStatus", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.BreakpointWithStatus)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "SavedContext", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.SavedContext)) - (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KiCallUserMode", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KiCallUserMode)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "KeUserCallbackDispatcher",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KeUserCallbackDispatcher)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "PsLoadedModuleList", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.PsLoadedModuleList)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "PsActiveProcessHead", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.PsActiveProcessHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "PspCidTable", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.PspCidTable)) - (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "ExpSystemResourcesList",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.ExpSystemResourcesList)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "ExpPagedPoolDescriptor",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.ExpPagedPoolDescriptor)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "ExpNumberOfPagedPools", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.ExpNumberOfPagedPools)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KeTimeIncrement", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KeTimeIncrement)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "KeBugCheckCallbackListHead",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KeBugCheckCallbackListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KiBugcheckData", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KiBugcheckData)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "IopErrorLogListHead", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.IopErrorLogListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "ObpRootDirectoryObject",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.ObpRootDirectoryObject)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "ObpTypeObjectType", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.ObpTypeObjectType)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemCacheStart", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSystemCacheStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemCacheEnd", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSystemCacheEnd)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemCacheWs", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSystemCacheWs)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPfnDatabase", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmPfnDatabase)) - (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemPtesStart", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSystemPtesStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemPtesEnd", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSystemPtesEnd)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSubsectionBase", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSubsectionBase)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmNumberOfPagingFiles", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmNumberOfPagingFiles)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmLowestPhysicalPage", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmLowestPhysicalPage)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmHighestPhysicalPage", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmHighestPhysicalPage)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmNumberOfPhysicalPages",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmNumberOfPhysicalPages)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmMaximumNonPagedPoolInBytes",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmMaximumNonPagedPoolInBytes)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmNonPagedSystemStart", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmNonPagedSystemStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmNonPagedPoolStart", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmNonPagedPoolStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmNonPagedPoolEnd", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmNonPagedPoolEnd)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPagedPoolStart", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmPagedPoolStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPagedPoolEnd", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmPagedPoolEnd)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmPagedPoolInformation",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmPagedPoolInformation)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPageSize", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmPageSize)) - (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmSizeOfPagedPoolInBytes",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSizeOfPagedPoolInBytes)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmTotalCommitLimit", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmTotalCommitLimit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmTotalCommittedPages", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmTotalCommittedPages)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSharedCommit", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSharedCommit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmDriverCommit", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmDriverCommit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmProcessCommit", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmProcessCommit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPagedPoolCommit", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmPagedPoolCommit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmExtendedCommit", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmExtendedCommit)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmZeroedPageListHead", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmZeroedPageListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmFreePageListHead", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmFreePageListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmStandbyPageListHead", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmStandbyPageListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmModifiedPageListHead",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmModifiedPageListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmModifiedNoWritePageListHead",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmModifiedNoWritePageListHead)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmAvailablePages", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmAvailablePages)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmResidentAvailablePages",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmResidentAvailablePages)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "PoolTrackTable", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.PoolTrackTable)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "NonPagedPoolDescriptor",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.NonPagedPoolDescriptor)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmHighestUserAddress", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmHighestUserAddress)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSystemRangeStart", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSystemRangeStart)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmUserProbeAddress", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmUserProbeAddress)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KdPrintCircularBuffer", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.KdPrintCircularBuffer)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "KdPrintCircularBufferEnd",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KdPrintCircularBufferEnd)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KdPrintWritePointer", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.KdPrintWritePointer)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KdPrintRolloverCount", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.KdPrintRolloverCount)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmLoadedUserImageList", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmLoadedUserImageList)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "NtBuildLab", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.NtBuildLab)) - (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KiNormalSystemCall", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.KiNormalSystemCall)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KiProcessorBlock", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.KiProcessorBlock)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmUnloadedDrivers", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmUnloadedDrivers)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmLastUnloadedDriver", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmLastUnloadedDriver)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmTriageActionTaken", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmTriageActionTaken)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSpecialPoolTag", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmSpecialPoolTag)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KernelVerifier", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KernelVerifier)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmVerifierData", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmVerifierData)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmAllocatedNonPagedPool",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmAllocatedNonPagedPool)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPeakCommitment", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.MmPeakCommitment)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmTotalCommitLimitMaximum",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmTotalCommitLimitMaximum)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "CmNtCSDVersion", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.CmNtCSDVersion)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmPhysicalMemoryBlock", max_symbol_length)
             == 0) {
        *offset =
            (unsigned long) (&(d.MmPhysicalMemoryBlock)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSessionBase", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSessionBase)) - (unsigned long) (&d);
    }
    else if (strncmp(symbol, "MmSessionSize", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSessionSize)) - (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmSystemParentTablePage",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmSystemParentTablePage)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "MmVirtualTranslationBase",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.MmVirtualTranslationBase)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "KdPrintCircularBufferPtr",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KdPrintCircularBufferPtr)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KdPrintBufferSize", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.KdPrintBufferSize)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "KeLoaderBlock", max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.KeLoaderBlock)) - (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "IopNumTriageDumpDataBlocks",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.IopNumTriageDumpDataBlocks)) -
            (unsigned long) (&d);
    }
    else if (strncmp
             (symbol, "IopTriageDumpDataBlocks",
              max_symbol_length) == 0) {
        *offset =
            (unsigned long) (&(d.IopTriageDumpDataBlocks)) -
            (unsigned long) (&d);
    }
    else if (strncmp(symbol, "VfCrashDataBlock", max_symbol_length) ==
             0) {
        *offset =
            (unsigned long) (&(d.VfCrashDataBlock)) -
            (unsigned long) (&d);
    }
    else {
        return VMI_FAILURE;
    }

    return VMI_SUCCESS;
}

// Idea from http://gleeda.blogspot.com/2010/12/identifying-memory-images.html
win_ver_t
find_windows_version(
    vmi_instance_t vmi,
    addr_t KdVersionBlock)
{
    windows_instance_t windows = NULL;

    if (vmi->os_data == NULL) {
        return VMI_FAILURE;
    }

    windows = vmi->os_data;

    // no need to repeat this work if we already have the answer
    if (windows->version &&
        windows->version != VMI_OS_WINDOWS_UNKNOWN) {
        return windows->version;
    }

    uint16_t size = 0;

    vmi_read_16_pa(vmi, KdVersionBlock + 0x14, &size);

    if (memcmp(&size, "\x08\x02", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows 2000\n");
        return VMI_OS_WINDOWS_2000;
    }
    else if (memcmp(&size, "\x90\x02", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows XP\n");
        return VMI_OS_WINDOWS_XP;
    }
    else if (memcmp(&size, "\x18\x03", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows 2003\n");
        return VMI_OS_WINDOWS_2003;
    }
    else if (memcmp(&size, "\x28\x03", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows Vista\n");
        return VMI_OS_WINDOWS_VISTA;
    }
    else if (memcmp(&size, "\x30\x03", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows 2008\n");
        return VMI_OS_WINDOWS_2008;
    }
    else if (memcmp(&size, "\x40\x03", 2) == 0) {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Windows 7\n");
        return VMI_OS_WINDOWS_7;
    }
    else {
        dbprint(VMI_DEBUG_MISC, "--OS Guess: Unknown (0x%.4x)\n", size);
        return VMI_OS_WINDOWS_UNKNOWN;
    }
}

static addr_t
find_kdversionblock_address(
    vmi_instance_t vmi)
{
    addr_t kdvb_address = 0;
    addr_t paddr = 0;
    unsigned char buf[12];

    for (paddr = 0; paddr + 12 <= vmi_get_memsize(vmi); paddr += 4) {
        if (12 == vmi_read_pa(vmi, paddr, buf, 12)) {
            if (VMI_PM_IA32E == vmi->page_mode) {
                if (memcmp(buf, "\x00\xf8\xff\xffKDBG", 8) == 0) {
                    kdvb_address = paddr - 0xc;
                    break;
                }
            }
            else {
                if (memcmp
                    (buf, "\x00\x00\x00\x00\x00\x00\x00\x00KDBG",
                     12) == 0) {
                    kdvb_address = paddr - 0x8;
                    break;
                }
            }
        }
    }

    return kdvb_address;
}

static addr_t
find_kdversionblock_address_fast(
    vmi_instance_t vmi)
{
    // Note: this function has several limitations:
    // -the KD version block signature cannot cross block (frame) boundaries
    // -reading PA 0 fails; hope the KD version block is not in frame 0
    //
    // Todo:
    // -support matching across frames (can this happen in windows?)

    addr_t kdvb_address = 0;
    addr_t block_pa = 0;
    addr_t memsize = vmi_get_memsize(vmi);
    size_t read = 0;
    void *bm = 0;   // boyer-moore internal state
    int find_ofs = 0;

#define BLOCK_SIZE 1024 * 1024 * 1
    unsigned char haystack[BLOCK_SIZE];

    if (VMI_PM_IA32E == vmi->page_mode) {
        bm = boyer_moore_init("\x00\xf8\xff\xffKDBG", 8);
        find_ofs = 0xc;
    }
    else {
        bm = boyer_moore_init("\x00\x00\x00\x00\x00\x00\x00\x00KDBG",
                              12);
        find_ofs = 0x8;
    }   // if-else

    for (block_pa = 4096; block_pa + BLOCK_SIZE <= memsize; block_pa += BLOCK_SIZE) {
        read = vmi_read_pa(vmi, block_pa, haystack, BLOCK_SIZE);
        if (BLOCK_SIZE != read) {
            continue;
        }

        int match_offset = boyer_moore2(bm, haystack, BLOCK_SIZE);

        if (-1 != match_offset) {
            kdvb_address =
                block_pa + (unsigned int) match_offset - find_ofs;
            break;
        }   // if
    }   // outer for

    if (kdvb_address)
        dbprint(VMI_DEBUG_MISC, "--Found KD version block at PA %.16"PRIx64"\n",
                kdvb_address);
    boyer_moore_fini(bm);
    return kdvb_address;
}

status_t
find_kdversionblock_address_faster(
    vmi_instance_t vmi,
    addr_t *kdvb_pa)
{

    reg_t cr3;
    driver_get_vcpureg(vmi, &cr3, CR3, 0);

    status_t ret = VMI_FAILURE;
    void *bm = boyer_moore_init("KDBG", 4);
    int find_ofs = 0x10;

    // We know that the Windows kernel is page aligned
    // so we are just checking if the page has a valid PE header
    // and if the first item in the export table is "ntoskrnl.exe".
    // Once the kernel is found, we find the .data section
    // and limit the string search for "KDBG" into that region.

    addr_t page_paddr = 0;
    for(page_paddr = 0; page_paddr + VMI_PS_4KB - 1 < vmi->size; page_paddr += VMI_PS_4KB) {

        uint8_t page[VMI_PS_4KB];
        status_t rc = peparse_get_image_phys(vmi, page_paddr, VMI_PS_4KB, page);
        if(VMI_FAILURE == rc) {
            continue;
        }

        struct pe_header *pe_header = NULL;
        struct dos_header *dos_header = NULL;
        void *optional_pe_header = NULL;
        uint16_t optional_header_type = 0;
        struct export_table et;

        peparse_assign_headers(page, &dos_header, &pe_header, &optional_header_type, &optional_pe_header, NULL, NULL);
        addr_t export_header_offset =
            peparse_get_idd_rva(IMAGE_DIRECTORY_ENTRY_EXPORT, &optional_header_type, optional_pe_header, NULL, NULL);

        uint32_t nbytes = vmi_read_pa(vmi, page_paddr + export_header_offset, &et, sizeof(struct export_table));
        if(nbytes == sizeof(struct export_table) && !(et.export_flags || !et.name) ) {
            char *name = vmi_read_str_pa(vmi, page_paddr + et.name);
            if(name) {
                if(strcmp("ntoskrnl.exe", name)) {
                    free(name);
                    continue;
                }
                free(name);
            }
        }

        uint32_t c;
        for(c=0; c < pe_header->number_of_sections; c++) {

            struct section_header section;
            addr_t section_addr = page_paddr
                + dos_header->offset_to_pe
                + sizeof(struct pe_header)
                + pe_header->size_of_optional_header
                + c*sizeof(struct section_header);

            // Read the section header from memory
            vmi_read_pa(vmi, section_addr, (uint8_t *)&section, sizeof(struct section_header));

            // .data check
            if(memcmp(section.short_name, "\x2E\x64\x61\x74\x61", 5) == 0) {

                uint8_t *haystack = alloca(section.size_of_raw_data);
                vmi_read_pa(vmi, page_paddr + section.virtual_address, haystack, section.size_of_raw_data);
                int match_offset = boyer_moore2(bm, haystack, section.size_of_raw_data);

                if (-1 != match_offset) {
                    *kdvb_pa = page_paddr + section.virtual_address + (unsigned int) match_offset - find_ofs;
                    ret = VMI_SUCCESS;
                    goto done;
                }

                break;
            }
        }
    }

done:

    if (VMI_SUCCESS == ret)
        dbprint(VMI_DEBUG_MISC, "--Found KD version block at PA %.16"PRIx64"\n",
                *kdvb_pa);
    boyer_moore_fini(bm);
    return ret;
}


status_t
init_kdversion_block(
    vmi_instance_t vmi)
{
    addr_t KdVersionBlock_phys = 0;
    addr_t DebuggerDataList = 0, ListPtr = 0;
    windows_instance_t windows = NULL;

    if (vmi->os_data == NULL) {
        return VMI_FAILURE;
    }

    windows = vmi->os_data;

    if(VMI_FAILURE == find_kdversionblock_address_faster(vmi, &KdVersionBlock_phys)) {
        dbprint(VMI_DEBUG_MISC, "**Failed to find KdVersionBlock\n");
        goto error_exit;
    }

    if (!windows->kdversion_block) {
        windows->kdversion_block = KdVersionBlock_phys;
        printf
            ("LibVMI Suggestion: set win_kdvb=0x%"PRIx64" in libvmi.conf for faster startup.\n",
             windows->kdversion_block);
    }
    dbprint(VMI_DEBUG_MISC, "**set KdVersionBlock address=0x%"PRIx64"\n",
            windows->kdversion_block);

    return VMI_SUCCESS;

error_exit:
    return VMI_FAILURE;
}

status_t
windows_kpcr_lookup(
    vmi_instance_t vmi,
    char *symbol,
    addr_t *address)
{
    unsigned long offset = 0;
    windows_instance_t windows = NULL;

    if (vmi->os_data == NULL) {
        return VMI_FAILURE;
    }

    windows = vmi->os_data;

    if (!windows->kdversion_block) {
        if (VMI_FAILURE == init_kdversion_block(vmi)) {
            goto error_exit;
        }
    }

    // Use heuristic to find windows version
    windows->version = find_windows_version(vmi, windows->kdversion_block);

    if (VMI_FAILURE == kpcr_symbol_offset(vmi, symbol, &offset)) {
        goto error_exit;
    }
    if (VMI_FAILURE == kpcr_symbol_resolve(vmi, offset, address)) {
        goto error_exit;
    }

    return VMI_SUCCESS;
error_exit:
    return VMI_FAILURE;
}
