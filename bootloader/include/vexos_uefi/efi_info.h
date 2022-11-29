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

    // Path of the kernel file (in unicode)
    //CHAR16* KernelPath;

    // Set of video-related data
    VIDEO_INFO VideoInfo;

    // Heap-allocated pixel buffer
    PIXEL* BackBuffer;

    EfiResetFunction Reset;

    FONT Font;

} KERNEL_INFO;

#endif