#include <vexos/draw.h>

void
drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo) {

    pixel_t* pixel = (pixel_t*) vinfo->vmem + UIDw(x, y, vinfo->x_res);

    pixel->r = col.r;
    pixel->g = col.g;
    pixel->b = col.b;

}

void
drawchar(uint32_t x, uint32_t y, char c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo) {

    for (size_t dy = 0; dy < font->hght; dy++) {
        for (size_t dx = 0; dx < font->wdth; dx++) {

            uint64_t index = GET_FONT_PIXEL_INDEX(c, dx, dy, font);
            pixel_t* pixel = (pixel_t*) vinfo->vmem + UIDw(x + dx, y + dy, vinfo->x_res);

            *pixel = COL2PIXEL((font->bmp[index].r == 0xFF) ? fg : bg);

        }
    }

    return;
}