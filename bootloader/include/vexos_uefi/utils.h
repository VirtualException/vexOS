#ifndef _UTILS_H
#define _UTILS_H

#define HAVE_USE_MS_ABI

#define SYSVABI __attribute__((sysv_abi))

#include <efi/efi.h>
#include <efi/efilib.h>

#include <vexos_uefi/bootinfo.h>
#include <vexos_uefi/elf.h>

#define NORMALTXT       L"%N"
#define WARNINGTXT      L"%E"
#define HIGHLIGHTTXT    L"%H"

#define PrintPause(str) Print(str);Pause();

#if defined(_M_X64) || defined(__x86_64__)
#define ARCHNAME    L"64-bit x86"
#else
#error Unsupported architecture
#endif

#define PAGE_SIZE 4096

#if defined(_DEBUG)
#define BUILDNUM    L"Debug"
#else
#define BUILDNUM    L"Release"
#endif

typedef
int (SYSVABI  *KernelEntry) (
    KERNEL_INFO*          KInfo
);


KernelEntry SetupKernel(CHAR16* KernelPath, EFI_HANDLE ImageHandle);
EFI_STATUS  SetupMemMap(UINTN* MapKey);
EFI_STATUS  SetupEnv(KERNEL_INFO** KInfo, UINT32 PrefResX, UINT32 PrefResY);

#endif
