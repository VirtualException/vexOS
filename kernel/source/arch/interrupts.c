#include <vexos/printk.h>
#include <vexos/vtt.h>
#include <vexos/lib/def.h>

#include <vexos/arch/interrupts.h>
#include <vexos/arch/io.h>
#include <vexos/dev/pic.h>
#include <vexos/dev/keyboard.h>


interrupt isr_table[ISR_N] = {

    /* Exceptions */

        exc_division_error,
        exc_debug,
        exc_non_maskable,
        exc_breakpoint,
        exc_overflow,
        exc_bound_range_exceeded,
        exc_invalid_opcode,
        exc_device_not_available,
        exc_double_fault,
        exc_cso_old,
        exc_invalid_tss,
        exc_segment_not_present,
        exc_stack_segment_fault,
        exc_general_protection_fault,
        exc_page_fault,
        NULL, /* Reserved */
        exc_x87_floating_point_exception,
        exc_alignment_check,
        exc_machine_check,
        exc_simd_floating_point_exception,
        exc_virtualization_exception,
        exc_control_protection_exception,
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        exc_hypervisor_injection_exception,
        exc_vmm_communication_exception,
        exc_security_exception,
        NULL, /* Reserved */

    /* IRQs (0x20 to 0x30) */

        int_unhandled,
        int_irq_kbd,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_unhandled,
        int_irq_ps2mouse,
        int_unhandled,
        int_unhandled,
        int_unhandled,

    /* Unimplemented */

        [EXC_N + IRQ_N ... ISR_N - 1] = int_unhandled,

};


INTERRUPT(unhandled) {

    printk(KERN_LOG "\nNOT HANDLED : 0x%x\n", intframe);

    return;
}

INTERRUPT(irq_kbd) {

    vtt_handle_key();

    pic_send_eoi(PIC1);

    return;
}

INTERRUPT(irq_ps2mouse) {

    printk("\n#MOUSE\n");

    inb(0x64);

    pic_send_eoi(PIC1);

    return;
}

EXCEPTION(division_error) {

    //printk("\n#DE\n");

    printk("\n#DE DIVISION_ERROR : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(debug) {

    printk("\n#DB DEBUG : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(non_maskable) {

    printk("\nNON_MASKABLE_INTERRUPT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(breakpoint) {

    printk("\n#BP BREAKPOINT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(overflow) {

    printk("\n#OF OVERFLOW : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(bound_range_exceeded) {

    printk("\n#BR BOUND_RANGE_EXCEEDED : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(invalid_opcode) {

    printk("\n#UD INVALID_OPCODE : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(device_not_available) {

    printk("\n#NM DEVICE_NOT_AVAILABLE : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(double_fault) {

    printk("\n#DF DOUBLE_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(cso_old) {

    printk("\nCSO_OLD : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(invalid_tss) {

    printk("\n#TS INVALID_TSS : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(segment_not_present) {

    printk("\n#NP SEGMENT_NOT_PRESENT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(stack_segment_fault) {

    printk("\n#SS STACK_SEGMENT_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(general_protection_fault) {

    printk("\n#GP GENERAL_PROTECTION_FAULT : 0x%x\n", intframe);

    while (1) { };

    return;
}
EXCEPTION(page_fault) {

    printk("\n#PF PAGE_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(x87_floating_point_exception) {

    printk("\n#MF X87_FLOATING_POINT_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(alignment_check) {

    printk("\n#AC ALIGNMENT_CHECK : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(machine_check) {

    printk("\n#MC MACHINE_CHECK : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(simd_floating_point_exception) {

    printk("\n#XM SIMD_FLOATING_POINT_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(virtualization_exception) {

    printk("\n#VE VIRTUALIZATION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(control_protection_exception) {

    printk("\n#CP CONTROL_PROTECTION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(hypervisor_injection_exception) {

    printk("\n#HV HYPERVISOR_INJECTION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(vmm_communication_exception) {

    printk("\n#VC VMM_COMMUNICATION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(security_exception) {

    printk("\n#SX SECURITY_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}