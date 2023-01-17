#include <vexos/arch/x86_64/gdt.h>
#include <vexos/printk.h>
#include <vexos/vtt.h>

__aligned(0x1000)
gdt_desc    gdt_table[GDT_DESCRIPTORS] = { 0 };
gdt_ptr     gdt = { sizeof(gdt_table) - 1, (uint64_t) gdt_table };

static bool done_setup = false;

uint64_t
gdt_setup(void) {

    if (done_setup) return (done_setup = 1);

    printk(KERN_LOG "Setting up GDT...\n");

    gdt_table[0] = (gdt_desc) { 0, 0, 0, 0x00, 0x00, 0 }; // null
    gdt_table[1] = (gdt_desc) { 0, 0, 0, 0x9a, 0xa0, 0 }; // kernel code segment
    gdt_table[2] = (gdt_desc) { 0, 0, 0, 0x92, 0xa0, 0 }; // kernel data segment
    gdt_table[3] = (gdt_desc) { 0, 0, 0, 0x00, 0x00, 0 }; // user null

    IRQ_OFF;

    gdt_load(&gdt);

    IRQ_ON;

    printk(KERN_LOG "GDT setup correctly\n");

    return 0;
}

void
readmsr(unsigned int msr, unsigned int *lo, unsigned int *hi) {

   ASM("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));

}