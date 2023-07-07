#ifndef _KINFO_H
#define _KINFO_H

#include <vexos/lib/types.h>
#include <vexos/lib/attributes.h>

#define RESET_REBOOT_COLD   0
#define RESET_REBOOT_WARM   1
#define RESET_SHUTDOWN      2

typedef struct {

    uint8_t b;
    uint8_t g;
    uint8_t r;

    uint8_t _reserved;

} pixel_t;

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

} uefi_time_t;

typedef struct {

    unsigned int chars;

    unsigned int wdth;
    unsigned int hght;

    unsigned int bpp;

    pixel_t* bmp;

} font_t;

typedef struct {

    uint32_t type;
    uint32_t pad;
    uint64_t physical_start;
    uint64_t virtual_start;
    uint64_t number_of_pages;
    uint64_t attribute;

} uefi_memory_descriptor_t;


typedef
uint64_t (__ms_abi *efi_reset_func) (

    uint32_t    reset_type,
    uint64_t    reset_status,
    uint64_t    data_size,
    wchar_t*    reset_data

);

typedef
uint64_t (__ms_abi *efi_get_time_func) (

    uefi_time_t*    time,
    void*           capabilities

);

typedef struct {

    uefi_memory_descriptor_t* map;
    uint64_t map_size;
    uint64_t desc_size;
    uint64_t desc_version;

} memory_info_t;

typedef struct {

    uint32_t x_res;
    uint32_t y_res;

    uint64_t vmem;
    uint64_t vmem_size;

} video_info_t;

typedef struct {

    // Set of video-related data
    video_info_t vinfo;

    memory_info_t meminfo;

    // Heap-allocated pixel buffer
    pixel_t* back_buffer;

    efi_reset_func      reset;
    efi_get_time_func   get_time;

    font_t font;

} boot_info_t;

extern boot_info_t* bootinfo;

extern char _k_start;
extern char _k_end;

#endif
