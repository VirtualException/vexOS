#ifndef _KINFO_H
#define _KINFO_H

#include <libc/stdint.h>
#include <vexos/video.h>
#include <vexos/font.h>

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
    video_info_t video_info;

    // Heap-allocated pixel buffer
    pixel_t* back_buffer;

    efi_reset_function reset;

    font_t font;

} kernel_info_t;

#endif