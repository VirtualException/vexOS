#ifndef _KINFO_H
#define _KINFO_H

#include <libc/types.h>
#include <vexos/video.h>

typedef
uint64_t (__attribute__((ms_abi)) *efi_reset_function) (
    uint32_t reset_type,
    uint64_t reset_status,
    uint64_t data_dize,
    wchar_t* reset_data
);

typedef struct {

    // Path of the kernel file (in unicode)
    //short int* kernel_path;

    // Set of video-related data
    videoinfo_t video_info;

    // Heap-allocated pixel buffer
    pixel_t* back_buffer;

    efi_reset_function reset;

    pixel_t* font_bitmap;

} kinfo_t;

#endif