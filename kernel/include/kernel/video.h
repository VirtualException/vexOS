#ifndef _VIDEO_H
#define _VIDEO_H

#include <libc/stdlib.h>
#include <kernel/vinfo.h>

typedef struct {

    uint8_t b;
    uint8_t g;
    uint8_t r;

    uint8_t _reserved;

} pixel_t;

typedef struct  {

    uint8_t b;
    uint8_t g;
    uint8_t r;

} __attribute__((aligned(4))) color_t;

typedef struct {

    uint8_t b;
    uint8_t g;
    uint8_t r;

    uint8_t a;

} colorwa_t;


int swapbuff(videoinfo_t* vinfo, pixel_t* buff);

#endif