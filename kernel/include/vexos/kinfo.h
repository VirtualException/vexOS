#ifndef _KINFO_H
#define _KINFO_H

#include <libc/stdint.h>
#include <vexos/video.h>
#include <vexos/font.h>
#include <vexos/attr.h>

typedef struct {

    uint16_t    year;       /* 1998 - 20XX */
    uint8_t     month;      /* 1 - 12 */
    uint8_t     day;        /* 1 - 31 */
    uint8_t     hour;       /* 0 - 23 */
    uint8_t     minute;     /* 0 - 59 */
    uint8_t     second;     /* 0 - 59 */
    uint8_t     reserved1;
    uint32_t    nanosecond; /* 0 - 999,999,999 */
    int16_t     timezone;   /* -1440 to 1440 or 2047 */
    uint8_t     daylight;
    uint8_t     reserved2;

} uefi_time;


typedef
uint64_t (__ms_abi *efi_reset_function) (

    uint32_t    reset_type,
    uint64_t    reset_status,
    uint64_t    data_dize,
    wchar_t*    reset_data

);

typedef
uint64_t (__ms_abi *efi_get_time) (

    uefi_time*  time,
    void*       capabilities

);


typedef struct {

    // Set of video-related data
    video_info_t video_info;

    // Heap-allocated pixel buffer
    pixel_t* back_buffer;

    uefi_time time;

    efi_reset_function  reset;
    efi_get_time        get_time;

    font_t font;

} kernel_info_t;

#endif