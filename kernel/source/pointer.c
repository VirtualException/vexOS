#include <vexos/printk.h>
#include <vexos/pointer.h>
#include <vexos/graphics.h>
#include <vexos/bootinfo.h>


volatile uint64_t x = 500;
volatile uint64_t y = 500;

void
pointer_handle_mouse(ps2mouse_packet* mouse_data) {

    if (x + mouse_data->dx <= bootinfo->vinfo.x_res - 50 &&
        y - mouse_data->dy <= bootinfo->vinfo.y_res - 50) {

        x += mouse_data->dx;
        y -= mouse_data->dy;

        graphics_drawchar(x, y, 159, RGBCOL(100, 255, 100), RGBCOL(0, 0, 0), &bootinfo->font, &bootinfo->vinfo);

    }

    return;
}
