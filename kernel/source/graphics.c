#include <vexos/graphics.h>

#define UIDw(x, y, w) ((x) + ((y) * (w)))

void
graphics_drawpixel(uint32_t x, uint32_t y, color_t col, video_info_t* vinfo) {

    pixel_t* pixel = (pixel_t*) bootinfo->vinfo.vmem + UIDw(x, y, vinfo->x_res);

    pixel->r = col.r;
    pixel->g = col.g;
    pixel->b = col.b;

}

void
graphics_drawchar(uint32_t x, uint32_t y, uint c, color_t fg, color_t bg, font_t* font, video_info_t* vinfo) {

    if (c >= font->chars) {
        return;
    }

    for (size_t dy = 0; dy < font->hght; dy++) {
        for (size_t dx = 0; dx < font->wdth; dx++) {

            uint64_t index = (c * font->wdth * font->hght) + UIDw(dx, dy, font->wdth);

            pixel_t* pixel = (pixel_t*) bootinfo->vinfo.vmem +
                UIDw(x + dx, y + dy, vinfo->x_res);
            *pixel = COL2PIXEL((font->bmp[index].r == 0xFF) ? fg : bg);

        }
    }

    return;
}
