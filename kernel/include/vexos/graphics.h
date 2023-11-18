#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <vexos/bootinfo.h>

/* Thanks claudipunchi for macro magic, but its no longer necessary
#define GET_FONT_PIXEL_INDEX(c, x, y, font) \
(UIDw( \
    ((((c)%font->bmp_wdth)) * font->wdth), \
    ((((c)-(((c)%font->bmp_wdth)))/font->bmp_wdth) * font->hght), \
    font->bmp_wdth * font->wdth) \
+ UIDw(x, y, font->bmp_wdth * font->wdth))
*/

#define RGBCOL(r, g, b)     ((color_t) {b, g, r})
#define COL2PIXEL(color)    ((pixel_t) {(color).b, (color).g, (color).r, 0})

typedef struct  {

    uint8_t r;
    uint8_t g;
    uint8_t b;

} __attribute__((aligned(4))) color_t;

typedef struct {

    uint8_t r;
    uint8_t g;
    uint8_t b;

    uint8_t a;

} colorwa_t;

void graphics_drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo);
void graphics_drawchar(uint32_t x, uint32_t y, char c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo);
void graphics_drawstring(uint32_t x, uint32_t y, char* c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo);
//void graphics_drawline();
//void graphics_drawrect();
//void graphics_fillrect();

#endif
