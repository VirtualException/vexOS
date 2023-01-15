#ifndef _DRAW_H
#define _DRAW_H

#include <vexos/video.h>
#include <vexos/info/font.h>

#define UIDw(x, y, w)       ((x) + ((y) * (w)))

/* Thanks claudipunchi for macro magic! */
#define GET_FONT_PIXEL_INDEX(c, x, y, font) (UIDw(\
                                            ((((c)%font->bmp_wdth)) * font->wdth),\
                                            ((((c)-(((c)%font->bmp_wdth)))/font->bmp_wdth) * font->hght),\
                                            font->bmp_wdth * font->wdth)\
                                            + UIDw(x, y, font->bmp_wdth * font->wdth))

void drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo);
void drawchar(uint32_t x, uint32_t y, uint c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo);

//void drawline(void);
//void drawrect(void);
//void fillrect(void);

#endif