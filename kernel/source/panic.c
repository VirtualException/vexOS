#include <vexos/panic.h>
#include <vexos/printk.h>
#include <vexos/graphics.h>
#include <vexos/lib/macros.h>

void
panic_spin() {

spin_loop:

    ASM("pause");

    goto spin_loop;

    return;
}

void
panic() {

    printk(KERN_TLOG "KERNEL PANICKED\n");

    graphics_drawstring(bootinfo.vinfo.x_res / 2, bootinfo.vinfo.y_res / 2, "! PANIC !",
        (color_t) {255, 0, 0}, (color_t) {0, 0, 0}, &bootinfo.font, &bootinfo.vinfo
    );

    panic_spin();

    return;
}
