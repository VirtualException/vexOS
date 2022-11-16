#ifndef _DRAW_H
#define _DRAW_H

#include <kernel/video.h>

void drawpixel(uint32_t x, uint32_t y, pixel_t* bbuff, color_t col);
void drawchar(uint32_t x, uint32_t y, tchar_t* tc, pixel_t* bbuff);

void drawline();
void drawrect();
void fillrect();

#endif