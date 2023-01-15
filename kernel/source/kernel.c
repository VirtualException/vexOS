#include <vlibc/stdlib.h>
#include <vlibc/stdbool.h>
#include <vlibc/string.h>

#undef QEMU

#include <vexos/info/kinfo.h>           // Kernel information

#include <vexos/vtt.h>                  // Console

#include <vexos/printk.h>               // Kernel console print

#include <vexos/arch/x86_64/gdt.h>      // GDT
#include <vexos/arch/x86_64/idt.h>      // IDT

#include <vexos/arch/x86_64/syscall.h>  // System calls

#include <vexos/arch/x86_64/mem.h>      // Memory manager

#include <vexos/utils/macros.h>         // Extra macros

#include <vexos/dev/ps2.h>              // PS2 I/O
#include <vexos/dev/pcspkr.h>           // PC Speacker
#include <vexos/dev/keyboard.h>         // Keyboard

#define VERSION "0.8.9"
#define ARCH    "x86_64"


/* TODO
 *  - FIX THE FUCKING VARGS PROBLEM
 *  - Memory Allocation (in progress)
 *  - Final font
 *  - Working Descriptor Tables (GDT, IDT, blahblah)
 *  - Better stdout/stderr/stdin model
 *  - Magickly create an Intel video driver for non-2-fps rendering, DONE! haha no, but we have +60 fps in vtt
 *  - Better shell (or just a working shell)
*/


void memory_review();

kernel_info_t* kinfo;

static unsigned int seed = 0;

int
start_kernel(kernel_info_t* kernelinfo) {

    kinfo = kernelinfo;

    vtt_setup(0, 0);

    gdt_setup();
    idt_setup();

    mem_setup();

    syscall_setup();

    kbd_setup();

    uefi_time time;
    kinfo->get_time(&time, NULL);
    srand(seed = time.second + time.minute + time.hour + time.day * time.month * time.year);

    printk(KERN_LOG "Random seed: %d\n", seed);
    printk(KERN_LOG "Time & date: %d:%d:%d %d/%d %d\n", time.hour, time.minute, time.second, time.day, time.month, time.year);
    printk(KERN_LOG "Build Timestamp: %s\n", __TIMESTAMP__);
    printk(KERN_LOG "Booted vexOS %s (%s, UEFI)\n", VERSION, ARCH);

    printk("\nWelcome to vexOS!\n\n");

    memory_review();

    /* */

    while (!vtt_handle()) {

        vtt_renderterm();

    }

    kinfo->reset(0, 0, 0, NULL);

    return EXIT_SUCCESS;
}

void
memory_review() {

    /* Memory review */

    uefi_memory_descriptor* desc = kinfo->meminfo.map;
    uint64_t entries = kinfo->meminfo.map_size / kinfo->meminfo.desc_size;

    printk(KERN_LOG "Memory Map Info (%d entries):\n", entries);

    for (size_t i = 0; i < entries; i++) {

        if ((desc->type == mem_type_boot_services_code || desc->type == mem_type_boot_services_data) && i != 0) goto skip;

        printk("Entry No %d: \t%s  \t%d KB  at \t0x%x %c\n",
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