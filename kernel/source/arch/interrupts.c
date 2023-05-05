#include <vexos/printk.h>
#include <vexos/vtt.h>
#include <vexos/lib/def.h>

#include <vexos/arch/interrupts.h>
#include <vexos/arch/io.h>
#include <vexos/arch/cpu.h>
#include <vexos/dev/pic.h>
#include <vexos/dev/ps2kbd.h>
#include <vexos/dev/ps2mouse.h>

__interrupt __general_regs_only void mouse_handler(void *r); /* TEMPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP */

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
        exc_control_protection_exception, /* 21th  */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* Reserved */
        NULL, /* exc_hypervisor_injection_exception */
        NULL, /* exc_vmm_communication_exception */
        NULL, /* exc_security_exception */
        NULL, /* Reserved */

    /* IRQs (0x20 to 0x30) */

        int_regdump,
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
        int_unhandled, /* MOUSE */
        int_unhandled,
        int_unhandled,
        int_unhandled,

    /* Unimplemented */

        [EXC_N + IRQ_N ... ISR_N - 1] = int_unhandled,

};

INTERRUPT(unhandled) {

    printk(KERN_TLOG "NOT HANDLED @ rip = 0x%x\n", intframe->rip);

    return;
}

INTERRUPT(regdump) {


    printk(KERN_TLOG "Registry dump! [rip = 0x%x]\n", intframe->rflags);

/*
    printk(KERN_TLOG KERN_TLOG "rax: 0x%X  rcx: 0x%X  rdx: 0x%X  rbx: 0x%X\n", rax(), rcx(), rdx(), rbx());
    printk(KERN_TLOG KERN_TLOG "rsi: 0x%X  rdi: 0x%X  rsp: 0x%X  rbp: 0x%X\n", rsi(), rdi(), rsp(), rbp());
    printk(KERN_TLOG KERN_TLOG "r8:  0x%X  r9:  0x%X  r10: 0x%X  r11: 0x%X\n", r8(), r9(), r10(), r11());
    printk(KERN_TLOG KERN_TLOG "r12: 0x%X  r13: 0x%X  r14: 0x%X  r15: 0x%X\n", r12(), r13(), r14(), r15());
    printk(KERN_TLOG KERN_TLOG "eflags: 0x%X\n", eflags());
*/

    return;
}

INTERRUPT(irq_kbd) {

    vtt_handle_key();

    pic_send_eoi(PIC1);

    return;
}

INTERRUPT(irq_ps2mouse) {

    printk(KERN_TLOG "MOUSE @ rip = 0x%x\n", intframe->rip);

    //inportb(0x64);

    pic_send_eoi(PIC1);

    return;
}

EXCEPTION(division_error) {

    printk(KERN_TLOG "#DE DIVISION_ERROR @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(debug) {

    printk(KERN_TLOG "#DB DEBUG @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(non_maskable) {

    printk(KERN_TLOG "\nNON_MASKABLE_INTERRUPT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(breakpoint) {

    printk(KERN_TLOG "#BP BREAKPOINT @ rip = 0x%x\n", intframe->rip);

#ifdef __DEBUG__
    printk(KERN_TLOG "Stopping execution... ");
    ASM("1: jmp 1b");
#endif

    printk(KERN_LOG "Continuing!\n");

    return;
}
EXCEPTION(overflow) {

    printk(KERN_TLOG "#OF OVERFLOW @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(bound_range_exceeded) {

    printk(KERN_TLOG "#BR BOUND_RANGE_EXCEEDED @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(invalid_opcode) {

    printk(KERN_TLOG "#UD INVALID_OPCODE @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(device_not_available) {

    printk(KERN_TLOG "#NM DEVICE_NOT_AVAILABLE @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(double_fault) {

    printk(KERN_TLOG "#DF DOUBLE_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(cso_old) {

    printk(KERN_TLOG "\nCSO_OLD @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(invalid_tss) {

    printk(KERN_TLOG "#TS INVALID_TSS @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(segment_not_present) {

    printk(KERN_TLOG "#NP SEGMENT_NOT_PRESENT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(stack_segment_fault) {

    printk(KERN_TLOG "#SS STACK_SEGMENT_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(general_protection_fault) {

    printk(KERN_TLOG "#GP GENERAL_PROTECTION_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(page_fault) {

    printk(KERN_TLOG "#PF PAGE_FAULT @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    while (1) { };

    return;
}
EXCEPTION(x87_floating_point_exception) {

    printk(KERN_TLOG "#MF X87_FLOATING_POINT_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(alignment_check) {

    printk(KERN_TLOG "#AC ALIGNMENT_CHECK @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(machine_check) {

    printk(KERN_TLOG "#MC MACHINE_CHECK @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(simd_floating_point_exception) {

    printk(KERN_TLOG "#XM SIMD_FLOATING_POINT_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(virtualization_exception) {

    printk(KERN_TLOG "#VE VIRTUALIZATION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(control_protection_exception) {

    printk(KERN_TLOG "#CP CONTROL_PROTECTION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(hypervisor_injection_exception) {

    printk(KERN_TLOG "#HV HYPERVISOR_INJECTION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(vmm_communication_exception) {

    printk(KERN_TLOG "#VC VMM_COMMUNICATION_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}
EXCEPTION(security_exception) {

    printk(KERN_TLOG "#SX SECURITY_EXCEPTION @ rip = 0x%x\n", intframe->rip);

    BREAKPOINT;

    return;
}