#ifndef TERM_H
#define TERM_H

#include "../../font.h"

#include <libc/stdio.h>
#include <kernel/video.h>

typedef struct {

    char    c;
    color_t fg;
    color_t bg;

} tchar_t;



void init_terminal(uint32_t x_res, uint32_t y_res, pixel_t* font_bitmap);
void newline();
void scroll(uint32_t lines);

void resetcolor();
void setfgcolor(uint8_t r, uint8_t g, uint8_t b);
void setbgcolor(uint8_t r, uint8_t g, uint8_t b);

void renderterm(pixel_t* buffer);
void rendercur(uint32_t x, uint32_t y, pixel_t* bbuff);

#endif