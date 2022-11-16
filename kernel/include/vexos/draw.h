#ifndef _DRAW_H
#define _DRAW_H

#include <vexos/video.h>

void drawpixel(uint32_t x, uint32_t y, pixel_t* vbuff, color_t col);
void drawchar(uint32_t x, uint32_t y, tchar_t* tc, pixel_t* vbuff);

void drawline();
void drawrect();
void fillrect();

#endif