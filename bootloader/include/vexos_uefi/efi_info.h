#ifndef _KINFO_H
#define _KINFO_H

#include <efi/efi.h>

typedef
EFI_STATUS (EFIAPI *EfiResetFunction) (
    EFI_RESET_TYPE  ResetType,
    EFI_STATUS      ResetStatus,
    UINTN           DataSize,
    CHAR16*         ResetData
);

typedef
EFI_STATUS (EFIAPI *EfiGetTime) (
    EFI_TIME*               Time,
    EFI_TIME_CAPABILITIES*  Capabilities
);

typedef struct {

    char R;
    char G;
    char B;

    char _Reserved;

} PIXEL;

typedef struct {

    unsigned int BmpWdth;
    unsigned int BmpHght;

    unsigned int Wdth;
    unsigned int Hght;

    unsigned int Bpp;

    PIXEL* Bmp;

} FONT;

typedef struct {

    UINT32 XRes;
    UINT32 YRes;

    UINT64 VMem;
    UINT64 VMem_Size;

} VIDEO_INFO;

typedef struct {

    // Set of video-related data
    VIDEO_INFO VideoInfo;

    // Heap-allocated pixel buffer
    PIXEL* BackBuffer;

    EFI_TIME Time;

    EfiResetFunction    Reset;
    EfiGetTime          GetTime;

    FONT Font;

} KERNEL_INFO;

#endif