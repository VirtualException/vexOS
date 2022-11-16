#include <libc/stdio.h>         // Standard libraries
#include <libc/stdlib.h>        //
#include <libc/stdbool.h>       //
#include <libc/string.h>        //

#include <vexos/vtt.h>         // Console

#include <vexos/shell.h>       // Shell

#include <vexos/draw.h>        // Drawing

#include <vexos/ps2.h>         // Keyboard-related
#include <vexos/keymap.h>      //

#include <vexos/kinfo.h>       // Kernel information

#define VERSION "0.5.1"
#define ARCH    "x86_64"


/* TODO
 *  - Implement a better stdout/stderr/stdin model
 *  - Magickly create an Intel video driver for non-2-fps rendering
 *  - Better shell (or just a working shell)
*/

int
start_kernel(kinfo_t* kinfo) {

    srand((uint64_t) kinfo->back_buffer);

    vtt_setup(kinfo, 80, 40);

    printk("Starting vexOS %s (%s, UEFI)\n", VERSION, ARCH);
    printk("[Build timestamp: %s]\n", __TIMESTAMP__);

    printk("Random seed: %d\n", kinfo->back_buffer);

    printk("Welcome vexOS! %c\n\n", FONT_TULI_LOGO);

    while (!vtt_handle()) {

        vtt_renderterm();

    }

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;
}