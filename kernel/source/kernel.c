#include <libc/stdio.h>         // Standard libraries
#include <libc/stdlib.h>        //
#include <libc/stdbool.h>       //
#include <libc/string.h>        //

#include <vexos/kinfo.h>        // Kernel information

#include <vexos/vtt.h>          // Console

#include <vexos/ps2.h>          // Devices
#include <vexos/pcspkr.h>       //

#define VERSION "0.5.1"
#define ARCH    "x86_64"


/* TODO
 *  - Implement a better stdout/stderr/stdin model
 *  - Magickly create an Intel video driver for non-2-fps rendering
 *  - Better shell (or just a working shell)
*/

int
start_kernel(kernel_info_t* kinfo) {

    srand((uint64_t) start_kernel);

    vtt_setup(kinfo, 80, 40);

    printk("Starting vexOS %s (%s, UEFI)\n", VERSION, ARCH);
    printk("[Build timestamp: %s]\n", __TIMESTAMP__);

    printk("Random seed: %d\n", kinfo->back_buffer);

    printk("Welcome vexOS! %c\n\n", FONT_TULI_LOGO);

    //char buffer[4096] = { 0 };
    //printk("%d\n", testasm(buffer));
    //printf("->%c<-", buffer[0]);

    while (!vtt_handle()) {

        vtt_renderterm();

    }

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;
}