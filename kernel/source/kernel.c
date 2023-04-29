/*  Hi! This an amateur OS kernel, created by VirtualxEception  */
/*    >> Check https://github.com/VirtualException/vexOS <<     */

#include <config.h>             /* Configuration */

#include <vexos/info/kinfo.h>   /* Kernel information */
#include <vexos/vtt.h>          /* Console */
#include <vexos/printk.h>       /* Kernel console print */

#include <vexos/arch/dt.h>      /* GDT & IDT */
#include <vexos/arch/syscall.h> /* System calls */
#include <vexos/arch/mem.h>     /* Memory manager */
#include <vexos/arch/serial.h>  /* COM port */

#include <vexos/dev/pic.h>      /* PIC */
#include <vexos/dev/ps2mouse.h> /* Mouse */
#include <vexos/dev/pcspkr.h>   /* PC Speacker */
#include <vexos/dev/keyboard.h> /* Keyboard */

#include <vexos/lib/rng.h>      /* RNG */
#include <vexos/lib/def.h>      /* "Standard" definitions */
#include <vexos/lib/assert.h>   /* Assertion */
#include <vexos/lib/macros.h>   /* Extra macros */

#ifdef __DEBUG__
    #pragma GCC warning "Compiling in debug mode"
#endif

/* TODO
 *  - "Dump" function
 *  - Mouse!!
 *  - Colors
 *  - Memory Allocation (in progress)
 *  - Magickly create an Intel video driver for non-2-fps rendering, DONE! haha no, but we have +60 fps in vtt
 *  - Better shell (or just a working shell)
 *  - Implement c library? (stdio, etc...)
*/


void memory_review();

kernel_info_t* kinfo;

static uefi_time utime;
static uint32_t rng_seed = 0;

void
start_kernel(kernel_info_t* kernelinfo) {

#ifdef __DEBUG__
    while(1) {};
#endif

    kinfo = kernelinfo;
    kinfo->get_time(&utime, NULL);

    vtt_setup(0, 0);

    gdt_setup();
    idt_setup();

    pic_setup();

    serial_setup();

    syscall_setup();

    mem_setup();

    rng_sets(rng_seed = utime.second + utime.minute + utime.hour + utime.day * utime.month * utime.year);

    printk(KERN_LOG "Random seed: %d\n", rng_seed);
    printk(KERN_LOG "Time & date: %d:%d:%d %d/%d %d\n", utime.hour, utime.minute, utime.second, utime.day, utime.month, utime.year);
    printk(KERN_LOG "Build Timestamp: %s\n", __TIMESTAMP__);

    memory_review();

    printk("\nBooted vexOS! (%s, %s, UEFI) by %s\n\n", VERSION, ARCH, AUTHOR);

    while (!vtt_handle()) {

        //ktrip

        vtt_renderterm();

    }

    printk(KERN_LOG "\nRebooting!\n");

    kinfo->reset(RESET_REBOOT_WARM, 0, 0, NULL);

    return;
}

void
memory_review() {

    /* Memory review */

    uefi_memory_descriptor* desc = kinfo->meminfo.map;
    uint64_t entries = kinfo->meminfo.map_size / kinfo->meminfo.desc_size;

    printk(KERN_LOG "Memory Map Info (%d entries):\n", entries);

    for (size_t i = 0; i < entries; i++) {

        if ((desc->type == mem_type_boot_services_code || desc->type == mem_type_boot_services_data) && i != 0) goto skip;

        printk(KERN_LOG "Entry No %d: \t%s  \t%d KB  at \t0x%x %c\n",
                i,
                uefi_memory_types_str[desc->type],
                BYTES2KB(PAGES2B(desc->number_of_pages)),
                desc->physical_start,
                (desc->type == mem_type_conventional_memory) ? '*' : ' '
            );
skip:
        desc = NEXT_MEMORY_DESCRIPTOR(desc, kinfo->meminfo.desc_size);

    }

    return;
}
