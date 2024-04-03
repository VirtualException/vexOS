#include <vexos/graphics.h>
#include <vexos/lib/memory.h>
#undef _FONTDATA
#include "../../font/font.h"

/* X,Y TO LINEAR. Convert (x, y), with y <= w into a linear value */
#define XY2L(x, y, w) ((x) + ((y) * (w)))

void
graphics_drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo) {

    pixel_t* pixel = (pixel_t*) bootinfo.vinfo.vmem + XY2L(x, y, vinfo->x_res);

    *pixel = COL2PIXEL(col);
}

void
graphics_drawchar(uint32_t x, uint32_t y, char c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo) {

    if ((uint) c >= font->chars) return;

    uint64_t index = (uint) c * font->wdth * font->hght;
    pixel_t* pixel = (pixel_t*) vinfo->vmem + XY2L(x, y, vinfo->x_res);

    for (size_t dy = 0; dy < font->hght; dy++) {

        for (size_t dx = 0; dx < font->wdth; dx++) {

            if (font->bmp[index + dx].r != 0)
                *(pixel + dx) = *(pixel_t*)&fg;
            else
                *(pixel + dx) = *(pixel_t*)&bg;

        }

        index += font->wdth;
        pixel += vinfo->x_res;
    }

    return;
}

void
graphics_drawstring(uint32_t x, uint32_t y, char* str, color_t fg, color_t bg, font_t* font, video_info_t* vinfo) {

    uint32_t offx = 0;
    uint32_t offy = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {

        if (str[i] == '\n') {
            offy += CHAR_HGHT;
            offx = 0;
        }
        else if(str[i] == '\t') {
            offx += CHAR_WDTH * 4;
        }
        else {
            graphics_drawchar(x + offx, y + offy, str[i], fg, bg, font, vinfo);
            offx += CHAR_WDTH;
        }
    }

    return;
}

void
graphics_drawline(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, color_t col, video_info_t* vinfo) {

    double m = (y1 - y0) / (x1 - x0);

    uint32_t x = x0;
    uint32_t y = y0;

    while (x < x1 && x <= vinfo->x_res && y <= vinfo->y_res) {
        graphics_drawpixel(x++, y += m, col, vinfo);
    }


    return;
}

//void
//graphics_drawrect(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, color_t col, video_info_t* vinfo) {
//
//    /* hmmm */
//
//    return;
//}
//
//void
//graphics_fillrect(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, color_t col, video_info_t* vinfo) {
//
//    /* slow ... */
//
//    return;
//}
