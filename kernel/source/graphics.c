#include <vexos/graphics.h>
#undef _FONTDATA
#include "../../font/font.h"

#define UIDw(x, y, w) ((x) + ((y) * (w)))

void
graphics_drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo) {

    pixel_t* pixel = (pixel_t*) bootinfo.vinfo.vmem + UIDw(x, y, vinfo->x_res);

    *pixel = COL2PIXEL(col);
}

void
graphics_drawchar(uint32_t x, uint32_t y, char c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo) {

    /* i need to improve this lol */

    if ((unsigned char) c >= font->chars || c < 0) {
        return;
    }

    for (size_t dy = 0; dy < font->hght; dy++) {
        for (size_t dx = 0; dx < font->wdth; dx++) {

            uint64_t index = (c * font->wdth * font->hght) + UIDw(dx, dy, font->wdth);

            pixel_t* pixel = (pixel_t*) bootinfo.vinfo.vmem +
                UIDw(x + dx, y + dy, vinfo->x_res);
            *pixel = COL2PIXEL((font->bmp[index].r == 0xFF) ? fg : bg);

        }
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
