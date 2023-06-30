/*  Hi! This an amateur OS kernel, created by VirtualxEception  */
/*    >> Check https://github.com/VirtualException/vexOS <<     */

#include <config.h>

#include <vexos/vtt.h>
#include <vexos/kprintf.h>
#include <vexos/time.h>
#include <vexos/mem.h>
#include <vexos/kbd.h>
#include <vexos/rng.h>
#include <vexos/info/kinfo.h>

#include <vexos/lib/def.h>
#include <vexos/lib/macros.h>

#include <vexos/cpu/dt.h>
#include <vexos/cpu/syscall.h>

#include <vexos/iobus/serial.h>
#include <vexos/iobus/pic.h>
#include <vexos/iobus/pit.h>
#include <vexos/iobus/ps2/ps2kbd.h>
#include <vexos/iobus/ps2/ps2mouse.h>


/* TODO (in order of dificulty)
 *  - Working mouse
 *  - Colors
 *  - Better shell (more like a working shell)
 *  - Memory Allocation
 *  - Magickly create an Intel video driver for non-2-fps rendering, DONE! haha
 * no, but we have +60 fps in vtt
*/

void memory_review();

kernel_info_t* kinfo;

static time_t time;
static uint32_t rng_seed;

void
start_kernel(kernel_info_t* kernelinfo) {

    BREAKPOINT;

    /* Initialization */

    kinfo = kernelinfo;

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

    kprintf(KERN_TLOG "----------------- Setup complete -----------------\n");
    memory_review();
    kprintf(KERN_TLOG "Random seed: %d\n", rng_seed);
    kprintf(KERN_TLOG "Boot date: %02d/%02d/%04d (DD:MM:YYYY)\n",
        time.day, time.month, time.year);
    kprintf(KERN_TLOG "Build Timestamp: %s. Built with gcc-%s\n",
        __TIMESTAMP__, GCCVER);

    kprintf(KERN_LOG
        "                 ____   _____          __ _  _\n"
        "                / __ \\ / ____|        / /| || |\n"
        "__   _______  _| |  | | (___   __  __/ /_| || |_\n"
        "\\ \\ / / _ \\ \\/ / |  | |\\___ \\  \\ \\/ / '_ \\__   _|\n"
        " \\ V /  __/>  <| |__| |____) |  >  <| (_) | | |\n"
        "  \\_/ \\___/_/\\_\\\\____/|_____/  /_/\\_\\\\___/  |_|   by %s\n\n",
        AUTHOR
    );

    kprintf("Booted vexOS ! (%s, %s UEFI) @ ", VERSION, ARCH);
    time_get(&time);
    kprintf("%02d:%02d:%02d, %02d/%02d/%04d\n\n",
        time.hour, time.minute, time.second, time.day, time.month, time.year);

    /* Boot completed */

    while (!vtt_handle()) {

    }

    kprintf(KERN_TLOG "Rebooting in 2... ");
    time_sleep(1000);
    kprintf(KERN_LOG "1... ");
    time_sleep(1000);

    kinfo->reset(RESET_REBOOT_COLD, 0, 0, NULL);

}

void
memory_review() {

    /* Memory review */

    uefi_memory_descriptor_t* desc = kinfo->meminfo.map;
    uint64_t entries = kinfo->meminfo.map_size / kinfo->meminfo.desc_size;

    kprintf(KERN_TLOG "Memory Map Info: %d entries (showing usable):\n", entries);

    uint64_t total_bytes = 0;
    uint64_t total_pages = 0;

    for (size_t i = 0; i < entries; i++) {

        /* if ((   desc->type == mem_type_boot_services_code ||
                desc->type == mem_type_boot_services_data) && i != 0) {
            goto skip;
        } */

        total_pages += desc->number_of_pages;
        total_bytes += PAGES2B(desc->number_of_pages);

        if (desc->type != mem_type_conventional_memory) {
            goto skip;
        }

        kprintf(KERN_TLOG "Entry No %3d: %s    \t%8d KB \t0x%010X %c\n",
                i,
                uefi_memory_types_str[desc->type],
                BYTES2KB(PAGES2B(desc->number_of_pages)),
                desc->physical_start,
                (desc->type == mem_type_conventional_memory) ? '*' : ' '
            );

skip:
        desc = NEXT_MEMORY_DESCRIPTOR(desc, kinfo->meminfo.desc_size);

    }

    kprintf(KERN_TLOG "Total memory: %d Megabytes (%d pages)\n",
        BYTES2MB(total_bytes), total_pages);

    return;
}
