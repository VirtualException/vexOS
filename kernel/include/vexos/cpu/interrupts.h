#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <vexos/lib/types.h>
#include <vexos/lib/macros.h>
#include <vexos/lib/attributes.h>

#define ISR_N 0x100 /* Nº of Interrupt Service Rutines */
#define EXC_N 0x20  /* Nº of Exceptions */
#define IRQ_N 0x10  /* Nº of IRQs */

typedef struct _interrupt_frame {

    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;

} interrupt_frame_t;

typedef void* interrupt_ptr;

extern interrupt_ptr isr_table[ISR_N];

/* Interrupt Service Routines can only have this type of definition
 * All interrupts are wrappers to other system functions
 * For this implementation, all exceptions will return, except for the #GP
 */
#define INTERRUPT(name) __interrupt __general_regs_only void int_##name(__unused interrupt_frame_t* intframe)
#define EXCEPTION(name) __interrupt __general_regs_only void exc_##name(__unused interrupt_frame_t* intframe)
#define EXCEPTERR(name) __interrupt __general_regs_only void exc_##name(__unused interrupt_frame_t* intframe, uint64_t error_code)

INTERRUPT(unhandled);
INTERRUPT(regdump);
INTERRUPT(pit_handler);
INTERRUPT(irq_ps2kbd);
INTERRUPT(irq_ps2mouse);

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
/*EXCEPTION(reserved_2);*/
/*EXCEPTION(reserved_3);*/
/*EXCEPTION(reserved_4);*/
/*EXCEPTION(reserved_5);*/
/*EXCEPTION(reserved_6);*/
EXCEPTION(hypervisor_injection_exception);
EXCEPTION(vmm_communication_exception);
EXCEPTION(security_exception);
/*EXCEPTION(reserved_7);*/

#endif
