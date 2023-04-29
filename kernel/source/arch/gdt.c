#include <vexos/arch/dt.h>
#include <vexos/printk.h>
#include <vexos/vtt.h>


gdt_entry   gdt_seg[GDT_DESCRIPTORS] = { 0 };
gdt_desc    gdt = { sizeof(gdt_seg) - 1, (uint64_t) gdt_seg };

uint64_t
gdt_setup(void) {

    printk(KERN_LOG "Setting up GDT...\n");

    gdt_seg[0] = (gdt_entry) { 0, 0, 0, 0x00, 0x00, 0 }; // null
    gdt_seg[1] = (gdt_entry) { 0, 0, 0, 0x9a, 0xa0, 0 }; // kernel code segment
    gdt_seg[2] = (gdt_entry) { 0, 0, 0, 0x92, 0xa0, 0 }; // kernel data segment
    gdt_seg[3] = (gdt_entry) { 0, 0, 0, 0x00, 0x00, 0 }; // user null

    IRQ_OFF;

    gdt_load(&gdt);

    IRQ_ON;

    printk(KERN_LOG "GDT set up correctly\n");

    return 0;
}