#include <vexos/arch/x86_64/idt.h>
#include <vexos/arch/x86_64/syscall.h>
#include <vexos/printk.h>
#include <vexos/vtt.h>

#include <vlibc/string.h>
#include <vexos/info/kinfo.h>


__aligned(0x1000)
idt_desc idt_table[IDT_DESCRIPTORS] = { 0 };

static bool done_setup = false;

uint64_t
idt_setup(void) {

    if (done_setup) return 1;

    printk(KERN_LOG "Setting up IDT...\n");

    idt_ptr idt = { sizeof(idt_table) - 1, (uint64_t) idt_table };

    /* Assign all exceptions to the int_handler() function */
    for (size_t i = 0; i < IDT_DESCRIPTORS; i++) {
        idt_create_desc(idt_table, i, IDT_TA_INTERRUPTGATE, 0x08, (uint64_t) int_handler);
    }

    IRQ_OFF;

    idt_load(&idt);

    IRQ_ON;

    printk(KERN_LOG "IDT setup correctly\n");

    return 0;
}

void idt_create_desc(idt_desc* idt, uint64_t index, uint64_t type, uint64_t selector, uint64_t offset) {

    idt[index].type_attr  = type;
    idt[index].selector   = selector;
    idt_set_offset(&idt[index], offset);

}

void
idt_set_offset(idt_desc* idt, uint64_t offset) {

    idt->offset_0 = (uint16_t)(offset & 0x000000000000ffff);
    idt->offset_1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
    idt->offset_2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);

}

uint64_t
idt_get_offset(idt_desc* idt) {

    uint64_t offset = 0;
    offset |= (uint64_t) idt->offset_0;
    offset |= (uint64_t) idt->offset_1 << 16;
    offset |= (uint64_t) idt->offset_2 << 32;

    return offset;

}

__interrupt
void
int_handler(struct interrupt_frame* intframe) {

    printk("#XX EXCEPTION HANDLER : 0x%x\n", intframe);

    while (1) { };

    return;
}