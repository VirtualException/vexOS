#include <vexos/kprintf.h>
#include <vexos/vtt.h>
#include <vexos/cpu/dt.h>

__aligned(0x1000)
gdt_entry_t gdt_seg[GDT_DESCRIPTORS] = { 0 };
gdt_desc_t  gdt = { sizeof(gdt_seg) - 1, (uint64_t) gdt_seg };

uint64_t
gdt_setup(void) {

    kprintf(KERN_TLOG "Setting up GDT... ");

    gdt = (gdt_desc_t) { sizeof(gdt_seg) - 1, (uint64_t) gdt_seg };

    gdt_seg[0] = (gdt_entry_t) { 0, 0, 0, 0x00, 0x00, 0 }; // null
    gdt_seg[1] = (gdt_entry_t) { 0, 0, 0, 0x9a, 0xa0, 0 }; // kernel code segment
    gdt_seg[2] = (gdt_entry_t) { 0, 0, 0, 0x92, 0xa0, 0 }; // kernel data segment
    gdt_seg[3] = (gdt_entry_t) { 0, 0, 0, 0x00, 0x00, 0 }; // user null

    IRQ_OFF;

    gdt_load(&gdt);

    IRQ_ON;

    kprintf(KERN_LOG "[DONE]\n");

    return 0;
}
