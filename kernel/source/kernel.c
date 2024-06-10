/*  Hi! This an amateur OS kernel, created by VirtualxEception  */
/*    >> Check https://github.com/VirtualException/vexOS <<     */

#include <config.h>

#include <vexos/vtt.h>
#include <vexos/printk.h>
#include <vexos/time.h>
#include <vexos/kmem.h>
#include <vexos/kbd.h>
#include <vexos/rng.h>
#include <vexos/bootinfo.h>
#include <vexos/panic.h>
#include <vexos/smbios.h>

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


/* 
 * TODO (in order of dificulty)
 *  - vargs rewrite?
 *  - Working mouse
 *  - Colors
 *  - standard io
 *  - Better shell-like environment
 *  - Sys? (system "lib")
 *  - Memory Allocation
 *  - Magickly create an Intel video driver for non-2-fps rendering, DONE! haha
 * no, but we have +60 fps in vtt
*/

static time_t   time;
static uint32_t rng_seed;
boot_info_t     bootinfo;

void
bootinfo_get(boot_info_t* bootinfo_ptr) {

    if (memcmp(MAGIC_VAL, &bootinfo_ptr->magic, MAGIC_VAL_SIZE)) {
        panic();
    }

    /*
     * Copy the boot information argument because it may be overwited as we
     * dont know (and dont care) about where it is.
    */

    bootinfo = *bootinfo_ptr;

    /* TODO: support command line kernel arguments */

    return;
};

void
print_cpu_info() {

    char cpu_id_string[16]      = { 0 };
    char cpu_brand_string[48]   = { 0 };

    uint32_t eax = 0;
    uint32_t ebx = 0;
    uint32_t ecx = 0;
    uint32_t edx = 0;

    cpuid(0x0, &eax, &ebx, &ecx, &edx);

    memcpy(cpu_id_string,        &ebx, sizeof (uint32_t));
    memcpy(cpu_id_string + 4,    &ecx, sizeof (uint32_t));
    memcpy(cpu_id_string + 8,    &edx, sizeof (uint32_t));

    printk(KERN_TLOG "CPU Vendor Identification String: %s\n", cpu_id_string);

    for (size_t i = 0; i < 3; i++) {

        cpuid(0x80000002 + i, &eax, &ebx, &ecx, &edx);

        uint64_t offst = i * 16;

        memcpy(cpu_brand_string + offst,        &eax, sizeof (uint32_t));
        memcpy(cpu_brand_string + offst + 4,    &ebx, sizeof (uint32_t));
        memcpy(cpu_brand_string + offst + 8,    &ecx, sizeof (uint32_t));
        memcpy(cpu_brand_string + offst + 12,   &edx, sizeof (uint32_t));

    }

    printk(KERN_TLOG "CPU Brand String: %s\n", cpu_brand_string);

    /* Doesnt work */
    cpuid(0x16, &eax, &ebx, &ecx, &edx);
    printk(KERN_TLOG "CPU Freqs. Base: %d MHz, Max: %d MHz, Bus %d MHz\n", eax, ebx, ecx);


    return;
}

void
start_kernel(boot_info_t* bootinfo_ptr) {

    /* Basic init */

    bootinfo_get(bootinfo_ptr);
    time_get(&time);

    time_init();
    kbd_init();
    rng_init(rng_seed = *(uint32_t*) (&time.day));

    /* Setup */

    vtt_setup();
    serial_setup();

    gdt_setup();
    idt_setup();
    syscall_setup();

    pic_setup();
    pit_setup();

    ps2kbd_setup();
    //ps2mouse_setup(); /* *crying in assembly* */

    kmem_setup();
    //smbios_setup();   /* *crying in hexadecimal* */

    /* End of setup */

    printk(KERN_TLOG "[Setup completed]\n");

    print_cpu_info();

    kmem_print_info();

    printk(KERN_TLOG "Boot date: %02d/%02d/%04d (DD:MM:YYYY)\n",
        time.day, time.month, time.year);
    printk(KERN_TLOG "Random seed: %d\n", rng_seed);
    printk(KERN_TLOG "Build Timestamp: %s\n", __TIMESTAMP__);
    printk(KERN_TLOG "Built with GCC %s\n", __VERSION__);
    printk(KERN_TLOG "Kernel start: 0x%X, kernel end: 0x%X (size: %d bytes)\n",
        &_kern_start, &_kern_end, &_kern_end - &_kern_start);

    printk(
        "                 ____   _____          __ _  _\n"
        "                / __ \\ / ____|        / /| || |\n"
        "__   _______  _| |  | | (___   __  __/ /_| || |_\n"
        "\\ \\ / / _ \\ \\/ / |  | |\\___ \\  \\ \\/ / '_ \\__   _|\n"
        " \\ V /  __/>  <| |__| |____) |  >  <| (_) | | |\n"
        "  \\_/ \\___/_/\\_\\\\____/|_____/  /_/\\_\\\\___/  |_|"
        "    by VirtualException\n\n"
    );
                    /* ^^^ vexOS ASCII Art ^^^ */

    printk("Booted vexOS! - (%s, %s UEFI) @ ", __BUILDVER__, __ARCH__);
    time_get(&time);
    printk("%02d:%02d:%02d, %02d/%02d/%04d\n\n",
        time.hour, time.minute, time.second, time.day, time.month, time.year);

    void *a = kmem_allocate_pages(10);
    void *b = kmem_allocate_pages(10);
    void *c = kmem_allocate_pages(10);

    kmem_deallocate(a);
    kmem_deallocate(c);
    kmem_deallocate(b);

    while (!vtt_handle()) {

    }

    printk(KERN_TLOG "Rebooting in 1 second... ");
    time_sleep(1000);

    bootinfo.reset(RESET_REBOOT_COLD, 0, 0, NULL);

    return; /* unreachable */
}
