#ifndef _FONT_H
#define _FONT_H

#include <vexos/vinfo.h>

typedef struct {

    unsigned int bmp_wdth;
    unsigned int bmp_hght;

    unsigned int wdth;
    unsigned int hght;

    unsigned int bpp;

    pixel_t* bmp;

} font_t;

enum {

#define CURSOR 31

    FONT_NULL,
    FONT_SMILE_WHITE,
    FONT_SMILE_BLACK,
    FONT_ANGER_WHITE,
    FONT_ANGER_BLACK,
    FONT_HEART_WHITE,
    FONT_HEART_BLACK,
    FONT_CROSS = 8,
    FONT_MALE = 11,
    FONT_FEMALE,
    FONT_TRANS,
    FONT_COPYRIGHT,
    FONT_REGISTERED,
    FONT_TULI_LOGO,
    FONT_FIST,
    FONT_ANARCHY,
    FONT_STAR,
    FONT_NOTE,
    FONT_ARROW_UP,
    FONT_ARROW_DOWN,
    FONT_ARROW_VERTICAL,
    FONT_ARROW_RIGHT,
    FONT_ARROW_LEFT,
    FONT_ARROW_HORIZONTAL,
    FONT_GRID1 = 28,
    FONT_GRID2,
    FONT_GRID3,
    FONT_SOLID,
    FONT_DEL_EXTRA = 127,

};

#endif
