#include <vexos/kprintf.h>
#include <vexos/lib/def.h>
#include <vexos/cpu/dt.h>
#include <vexos/cpu/io.h>
#include <vexos/cpu/interrupts.h>

__aligned(0x1000)
idt_entry_t idt_isr[ISR_N] = { 0 };
idt_desc_t  idt = { sizeof(idt_isr) - 1, (uint64_t) idt_isr };

uint64_t
idt_setup(void) {

    kprintf(KERN_TLOG "Setting up IDT... ");

    idt = (idt_desc_t) { sizeof(idt_isr) - 1, (uint64_t) idt_isr };

    /* Exceptions & Interrupts */

    for (size_t i = 0; i < EXC_N; i++) {
        idt_isr[i] = IDTENTRY(isr_table[i], IDT_TA_INTERRUPTGATE, 0x08);
    }

    for (size_t i = EXC_N; i < ISR_N; i++) {
        idt_isr[i] = IDTENTRY(isr_table[i], IDT_TA_INTERRUPTGATE, 0x08);
    }

    IRQ_OFF;

    idt_load(&idt);

    IRQ_ON;

    kprintf(KERN_LOG "[DONE]\n");

    return 0;
}
