#include <libc/stdio.h>         // Standard libraries
#include <libc/stdlib.h>        //
#include <libc/stdbool.h>       //
#include <libc/string.h>        //

#include <vexos/dt.h>           // Descriptor tables (GDT, IDT)

#include <vexos/kinfo.h>        // Kernel information

#include <vexos/vtt.h>          // Console

#include <vexos/ps2.h>          // Devices
#include <vexos/pcspkr.h>       //

#define VERSION "0.6.0"
#define ARCH    "x86_64"

#define ISBITSET(byte, n) ((status & (128 >> n)) == 1)

/* TODO
 *  - Descriptor Tables (GDT, IDT, blahblah)
 *  - Implement a better stdout/stderr/stdin model
 *  - Magickly create an Intel video driver for non-2-fps rendering
 *  - Better shell (or just a working shell)
*/

int
start_kernel(kernel_info_t* kinfo) {

    //gdt_setup();
    //idt_setup();

    uefi_time time;
    kinfo->get_time(&time, NULL);

    srand(time.second + 60 * time.minute + 3600 * time.hour + 86400 * time.day + 2592000 * time.month);

    vtt_setup(kinfo, 80, 40);

    printk("Starting vexOS %s (%s, UEFI)\n", VERSION, ARCH);
    printk("[Build timestamp: %s]\n", __TIMESTAMP__);

    printk("Random seed: %d\n", getseed());
    printk("Time: %d/%d %d:%d:%d %d\n", time.day, time.month, time.hour, time.minute, time.second, time.year);

    printk("Welcome vexOS! %c\n\n", FONT_TULI_LOGO);

    /* Implement custom emojis! + final font */

    while (!vtt_handle()) {

        vtt_renderterm();

    }

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;
}