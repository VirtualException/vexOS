#ifndef _KINFO_H
#define _KINFO_H

#include <vexos/lib/types.h>
#include <vexos/video.h>
#include <vexos/font.h>
#include <vexos/lib/macros.h>

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

typedef struct {
    uint32_t type;
    uint32_t pad;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attribute;
} uefi_memory_descriptor;


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

    uefi_memory_descriptor* map;
    uint64_t map_size;
    uint64_t desc_size;
    uint64_t desc_version;

} memory_info_t;


typedef struct {

    // Set of video-related data
    video_info_t video_info;

    memory_info_t meminfo;

    // Heap-allocated pixel buffer
    pixel_t* back_buffer;

    efi_reset_function  reset;
    efi_get_time        get_time;

    font_t font;

} kernel_info_t;

extern kernel_info_t* kinfo;

#endif