#ifndef _VIDEO_INFO_H
#define _VIDEO_INFO_H

#include <libc/types.h>

typedef struct {

    uint32_t x_res;
    uint32_t y_res;

    uint64_t vmem;
    uint64_t vmem_size;

} videoinfo_t;

#endif