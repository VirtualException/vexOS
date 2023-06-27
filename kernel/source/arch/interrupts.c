#include <vexos/kprintf.h>
#include <vexos/vtt.h>
#include <vexos/lib/def.h>

#include <vexos/arch/interrupts.h>
#include <vexos/arch/io.h>
#include <vexos/arch/pic.h>
#include <vexos/dev/ps2kbd.h>
#include <vexos/dev/ps2mouse.h>

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

        int_pit_handler,
        int_irq_ps2kbd,
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

    /* Custom */

        int_regdump,

    /* ... */

};

INTERRUPT(unhandled) {

    kprintf(KERN_TLOG "Unhandled @ rip = 0x%x\n", intframe->rip);

    return;
}

INTERRUPT(regdump) {


    kprintf(KERN_TLOG "Registry dump! [...]\n");

    return;
}

EXCEPTION(division_error) {

    kprintf(KERN_TLOG "#DE DIVISION_ERROR @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(debug) {

    kprintf(KERN_TLOG "#DB DEBUG @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(non_maskable) {

    kprintf(KERN_TLOG "\nNON_MASKABLE_INTERRUPT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(breakpoint) {

    kprintf(KERN_TLOG "#BP BREAKPOINT @ rip = 0x%x\n", intframe->rip);

#ifdef __DEBUG__
    kprintf(KERN_TLOG "Stopping execution... ");
    ASM("1: jmp 1b");
#endif

    kprintf(KERN_LOG "Continuing!\n");

    return;
}
EXCEPTION(overflow) {

    kprintf(KERN_TLOG "#OF OVERFLOW @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(bound_range_exceeded) {

    kprintf(KERN_TLOG "#BR BOUND_RANGE_EXCEEDED @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(invalid_opcode) {

    kprintf(KERN_TLOG "#UD INVALID_OPCODE @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(device_not_available) {

    kprintf(KERN_TLOG "#NM DEVICE_NOT_AVAILABLE @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(double_fault) {

    kprintf(KERN_TLOG "#DF DOUBLE_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(cso_old) {

    kprintf(KERN_TLOG "\nCSO_OLD @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(invalid_tss) {

    kprintf(KERN_TLOG "#TS INVALID_TSS @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(segment_not_present) {

    kprintf(KERN_TLOG "#NP SEGMENT_NOT_PRESENT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(stack_segment_fault) {

    kprintf(KERN_TLOG "#SS STACK_SEGMENT_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(general_protection_fault) {

    kprintf(KERN_TLOG "#GP GENERAL_PROTECTION_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(page_fault) {

    kprintf(KERN_TLOG "#PF PAGE_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    while (1) { };

    return;
}
EXCEPTION(x87_floating_point_exception) {

    kprintf(KERN_TLOG "#MF X87_FLOATING_POINT_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(alignment_check) {

    kprintf(KERN_TLOG "#AC ALIGNMENT_CHECK @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(machine_check) {

    kprintf(KERN_TLOG "#MC MACHINE_CHECK @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(simd_floating_point_exception) {

    kprintf(KERN_TLOG "#XM SIMD_FLOATING_POINT_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(virtualization_exception) {

    kprintf(KERN_TLOG "#VE VIRTUALIZATION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(control_protection_exception) {

    kprintf(KERN_TLOG "#CP CONTROL_PROTECTION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(hypervisor_injection_exception) {

    kprintf(KERN_TLOG "#HV HYPERVISOR_INJECTION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(vmm_communication_exception) {

    kprintf(KERN_TLOG "#VC VMM_COMMUNICATION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(security_exception) {

    kprintf(KERN_TLOG "#SX SECURITY_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
