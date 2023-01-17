#ifndef _VIDEO_H
#define _VIDEO_H

#include <vexos/lib/types.h>
#include <vexos/info/vinfo.h>

#define RGBCOL(r, g, b)     ((color_t) {b, g, r})
#define COL2PIXEL(color)    ((pixel_t) {(color).b, (color).g, (color).r, 0})

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


int swapbuff(video_info_t* vinfo, pixel_t* buff);

#endif