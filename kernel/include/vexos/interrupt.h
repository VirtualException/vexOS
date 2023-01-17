#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <vexos/lib/macros.h>

struct frame;

typedef
void (__sysv_abi *interrupt) (
    struct frame* intframe
);

extern interrupt exc_table[0x20];

/* Interrupt Service Routines can only have this type of definition */
#define EXCEPTION(name) __interrupt void exc_##name(struct frame* intframe)
#define INTERRUPT(name) __interrupt void int_##name(struct frame* intframe)

EXCEPTION(division_error);
EXCEPTION(debug);
EXCEPTION(non_maskable);
EXCEPTION(breakpoint);
EXCEPTION(overflow);
EXCEPTION(bound_range_exceeded);
EXCEPTION(invalid_opcode);
EXCEPTION(device_not_available);
EXCEPTION(double_fault);
EXCEPTION(cso_old);
EXCEPTION(invalid_tss);
EXCEPTION(segment_not_present);
EXCEPTION(stack_segment_fault);
EXCEPTION(general_protection_fault);
EXCEPTION(page_fault);
/*EXCEPTION(reserved_0);*/
EXCEPTION(x87_floating_point_exception);
EXCEPTION(alignment_check);
EXCEPTION(machine_check);
EXCEPTION(simd_floating_point_exception);
EXCEPTION(virtualization_exception);
EXCEPTION(control_protection_exception);
/*EXCEPTION(reserved_1);*/
EXCEPTION(hypervisor_injection_exception);
EXCEPTION(vmm_communication_exception);
EXCEPTION(security_exception);
/*EXCEPTION(reserved_2);*/

#endif