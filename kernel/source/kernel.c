/*  Hi! This an amateur OS kernel, created by VirtualxEception  */
/*    >> Check https://github.com/VirtualException/vexOS <<     */

#include <config.h>

#include <vexos/vtt.h>
#include <vexos/printk.h>
#include <vexos/time.h>
#include <vexos/mem.h>
#include <vexos/kbd.h>
#include <vexos/rng.h>
#include <vexos/bootinfo.h>

#include <vexos/lib/assert.h>
#include <vexos/lib/def.h>
#include <vexos/lib/memory.h>
#include <vexos/lib/macros.h>

#include <vexos/cpu/dt.h>
#include <vexos/cpu/syscall.h>

#include <vexos/iobus/serial.h>
#include <vexos/iobus/pic.h>
#include <vexos/iobus/pit.h>
#include <vexos/iobus/ps2/ps2kbd.h>
#include <vexos/iobus/ps2/ps2mouse.h>


/* TODO (in order of dificulty)
 *  - Modules w/ mprint
 *  - Working mouse
 *  - Colors
 *  - Better shell (more like a working shell)
 *  - Sys? (system "lib")
 *  - Memory Allocation
 *  - Magickly create an Intel video driver for non-2-fps rendering, DONE! haha
 * no, but we have +60 fps in vtt
*/

boot_info_t* bootinfo;

static time_t time;
static uint32_t rng_seed;

void
start_kernel(boot_info_t* boot_info_arg) {

    BREAKPOINT;

    /* Initialization */
    bootinfo = boot_info_arg;

    time_init();
    kbd_init();

    time_get(&time);
    rng_seed = (time.minute + time.hour + time.day) << (time.second / 2);
    rng_init(rng_seed);

    /* Setup */

    vtt_setup(0, 0);
    serial_setup();

    gdt_setup();
    idt_setup();
    syscall_setup();

    pic_setup();
    pit_setup();
    ps2kbd_setup();
    //ps2mouse_setup();

    mem_setup();

    /* End startup */

    printk(KERN_TLOG "--- Setup complete ---\n");
    printk(KERN_TLOG "Kernel start: 0x%X, kernel end: 0x%X\n", &_k_start, &_k_end);
    printk(KERN_TLOG "Random seed: %d\n", rng_seed);
    printk(KERN_TLOG "Boot date: %02d/%02d/%04d (DD:MM:YYYY)\n",
        time.day, time.month, time.year);
    printk(KERN_TLOG "Build Timestamp: %s. Built with gcc-%s\n",
        __TIMESTAMP__, GCCVER);
    mem_review();

    printk(KERN_LOG
        "                 ____   _____          __ _  _\n"
        "                / __ \\ / ____|        / /| || |\n"
        "__   _______  _| |  | | (___   __  __/ /_| || |_\n"
        "\\ \\ / / _ \\ \\/ / |  | |\\___ \\  \\ \\/ / '_ \\__   _|\n"
        " \\ V /  __/>  <| |__| |____) |  >  <| (_) | | |\n"
        "  \\_/ \\___/_/\\_\\\\____/|_____/  /_/\\_\\\\___/  |_|   by %s\n\n",
        AUTHOR
    );

    printk("Booted vexOS ! (%s, %s UEFI) @ ", VERSION, ARCH);
    time_get(&time);
    printk("%02d:%02d:%02d, %02d/%02d/%04d\n\n",
        time.hour, time.minute, time.second, time.day, time.month, time.year);

    /* Boot completed */

    while (!vtt_handle()) {

    }

    printk(KERN_TLOG "Rebooting in 2... ");
    time_sleep(1000);
    printk(KERN_LOG "1... ");
    time_sleep(1000);

    bootinfo->reset(RESET_REBOOT_COLD, 0, 0, NULL);

    return; /* unreachable */
}
