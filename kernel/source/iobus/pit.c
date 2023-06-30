#include <vexos/kprintf.h>
#include <vexos/time.h>

#include <vexos/cpu/interrupts.h>
#include <vexos/cpu/io.h>

#include <vexos/iobus/pit.h>
#include <vexos/iobus/pic.h>

#define PIT_MODE_COMMAND_BYTE 0x36 /* A lot of binary flags grouped up */

void
pit_setup() {

    kprintf(KERN_TLOG "Setting up PIT... ");

    IRQ_OFF;

    volatile uint32_t divisor =  PIT_FREQ / PIT_TIMER_FREQ;
    outb(PIT_CONTROL_PORT_3, PIT_MODE_COMMAND_BYTE);
    outb(PIT_CONTROL_PORT_0, divisor & 0xFF);
    outb(PIT_CONTROL_PORT_0, (divisor >> 8) & 0xFF);

    pic_unmask(PIC_PIT_IRQ);

    IRQ_ON;

    kprintf(KERN_LOG "[DONE]\n");

    return;
}

INTERRUPT(pit_handler) {

    time_tick();

    pic_send_eoi(PIC_PIT_IRQ);

    return;
}
