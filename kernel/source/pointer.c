#include <vexos/pointer.h>
#include <vexos/graphics.h>
#include <vexos/info/kinfo.h>

volatile uint64_t x = 500;
volatile uint64_t y = 500;

void
pointer_handle_mouse(ps2mouse_packet* mouse_data) {

    if (x + mouse_data->dx <= kinfo->vinfo.x_res - 50 &&
        y - mouse_data->dy <= kinfo->vinfo.y_res - 50) {

        x += mouse_data->dx;
        y -= mouse_data->dy;

        graphics_drawchar(x, y, 159, RGBCOL(100, 255, 100), RGBCOL(0, 0, 0), &kinfo->font, &kinfo->vinfo);

    }

    return;
}
