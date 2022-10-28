#ifndef _KINFO_H
#define _KINFO_H

#include <osvx_uefi/efi_video_info.h>

typedef
EFI_STATUS (EFIAPI *EfiResetFunction) (
    EFI_RESET_TYPE  ResetType,
    EFI_STATUS      ResetStatus,
    UINTN           DataSize,
    CHAR16*         ResetData
);

typedef struct {

    // Path of the kernel file (in unicode)
    //CHAR16* KernelPath;

    // Set of video-related data
    VIDEO_INFO VideoInfo;

    // Heap-allocated pixel buffer
    PIXEL* BackBuffer;

    EfiResetFunction Reset;

    PIXEL* FontBitmap;

} KINFO;

#endif