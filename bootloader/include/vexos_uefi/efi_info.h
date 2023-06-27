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

    EFI_MEMORY_DESCRIPTOR* Map;
    UINTN MapSize;
    UINTN DescSize;
    UINTN DescVersion;

} MEMORY_INFO;

typedef struct {

    CHAR8 R;
    CHAR8 G;
    CHAR8 B;

    CHAR8 _Reserved;

} PIXEL;

typedef struct {

    unsigned int Chars;

    unsigned int Wdth;
    unsigned int Hght;

    unsigned int Bpp;

    PIXEL* Bmp;

} FONT;

typedef struct {

    UINT32 XRes;
    UINT32 YRes;

    UINTN VMem;
    UINTN VMem_Size;

} VIDEO_INFO;

typedef struct {

    // Set of video-related data
    VIDEO_INFO VideoInfo;

    MEMORY_INFO MemInfo;

    // Heap-allocated pixel buffer
    PIXEL* BackBuffer;

    EfiResetFunction    Reset;
    EfiGetTime          GetTime;

    FONT Font;

} KERNEL_INFO;

#endif