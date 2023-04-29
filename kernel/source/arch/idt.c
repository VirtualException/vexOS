#include <vexos/lib/def.h>
#include <vexos/arch/dt.h>
#include <vexos/printk.h>
#include <vexos/vtt.h>

#include <vexos/arch/io.h>
#include <vexos/arch/interrupts.h>
#include <vexos/dev/pic.h>


idt_entry   idt_isr[ISR_N] = { 0 };
idt_desc    idt = { sizeof(idt_isr) - 1, (uint64_t) idt_isr };

uint64_t
idt_setup(void) {

    printk(KERN_LOG "Setting up IDT...\n");

    /* Exceptions & Interrupts */

    /*for (size_t i = 0; i < IRQ_N; i++) {
        idt_isr[i] = IDTENTRY(isr_table[i], IDT_TA_INTERRUPTGATE, 0x08);
    }
    for (size_t i = IRQ_N; i < IRQ_N + EXC_N; i++) {
        idt_isr[i] = IDTENTRY(isr_table[i], IDT_TA_TRAPGATE, 0x08);
    }*/

    for (size_t i = 0; i < ISR_N; i++) {
        idt_isr[i] = IDTENTRY(isr_table[i], IDT_TA_INTERRUPTGATE, 0x08);
    }

    IRQ_OFF;

    idt_load(&idt);

    IRQ_ON;

    printk(KERN_LOG "IDT set up correctly\n");

    return 0;
}

/*
void
idt_create_desc(idt_entry* idt, uint64_t index, uint64_t type, uint64_t selector, uint64_t offset) {

    idt[index].type_attr  = type;
    idt[index].selector   = selector;
    idt_set_offset(&idt[index], offset);

}

void
idt_set_offset(idt_entry* idt, uint64_t offset) {

    idt->offset_0 = (uint16_t)(offset & 0x000000000000ffff);
    idt->offset_1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
    idt->offset_2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);

}

uint64_t
idt_get_offset(idt_entry* idt) {

    uint64_t offset = 0;
    offset |= (uint64_t) idt->offset_0;
    offset |= (uint64_t) idt->offset_1 << 16;
    offset |= (uint64_t) idt->offset_2 << 32;

    return offset;

}
*/