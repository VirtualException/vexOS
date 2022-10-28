#ifndef _DRAW_H
#define _DRAW_H

#include <kernel/video.h>

void drawchar(uint32_t x, uint32_t y, tchar_t* c, pixel_t* bbuff);

void drawline();
void drawrect();
void fillrect();


#endif