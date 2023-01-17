#include <vexos/printk.h>
#include <vexos/interrupt.h>
#include <vexos/lib/def.h>

interrupt exc_table[0x20] = {
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
    NULL,
    exc_x87_floating_point_exception,
    exc_alignment_check,
    exc_machine_check,
    exc_simd_floating_point_exception,
    exc_virtualization_exception,
    exc_control_protection_exception,
    NULL,
    exc_hypervisor_injection_exception,
    exc_vmm_communication_exception,
    exc_security_exception,
    NULL,
};

EXCEPTION(division_error) {

    printk("#DE DIVISION_ERROR : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(debug) {

    printk("#DB DEBUG : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(non_maskable) {

    printk("NON_MASKABLE_INTERRUPT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(breakpoint) {

    printk("#BP BREAKPOINT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(overflow) {

    printk("#OF OVERFLOW : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(bound_range_exceeded) {

    printk("#BR BOUND_RANGE_EXCEEDED : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(invalid_opcode) {

    printk("#UD INVALID_OPCODE : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(device_not_available) {

    printk("#NM DEVICE_NOT_AVAILABLE : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(double_fault) {

    printk("#DF DOUBLE_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(cso_old) {

    printk("CSO_OLD : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(invalid_tss) {

    printk("#TS INVALID_TSS : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(segment_not_present) {

    printk("#NP SEGMENT_NOT_PRESENT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(stack_segment_fault) {

    printk("#SS STACK_SEGMENT_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(general_protection_fault) {

    printk("#GP GENERAL_PROTECTION_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(page_fault) {

    printk("#PF PAGE_FAULT : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(x87_floating_point_exception) {

    printk("#MF X87_FLOATING_POINT_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(alignment_check) {

    printk("#AC ALIGNMENT_CHECK : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(machine_check) {

    printk("#MC MACHINE_CHECK : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(simd_floating_point_exception) {

    printk("#XM SIMD_FLOATING_POINT_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(virtualization_exception) {

    printk("#VE VIRTUALIZATION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(control_protection_exception) {

    printk("#CP CONTROL_PROTECTION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(hypervisor_injection_exception) {

    printk("#HV HYPERVISOR_INJECTION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(vmm_communication_exception) {

    printk("#VC VMM_COMMUNICATION_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}
EXCEPTION(security_exception) {

    printk("#SX SECURITY_EXCEPTION : 0x%x\n", intframe);

    //while (1) { };

    return;
}