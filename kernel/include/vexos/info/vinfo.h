#ifndef _VINFO_H
#define _VINFO_H

#include <vlibc/stdint.h>

typedef struct {

    uint8_t b;
    uint8_t g;
    uint8_t r;

    uint8_t _reserved;

} pixel_t;

typedef struct {

    uint32_t x_res;
    uint32_t y_res;

    uint64_t vmem;
    uint64_t vmem_size;

} video_info_t;

#endif