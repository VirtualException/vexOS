#ifndef _IO_H
#define _IO_H

#include <vexos/lib/types.h>

#define IO_SLOW_MACHINE 0

extern uint8_t  inportb(uint16_t port);
extern void     outportb(uint16_t port, uint8_t data);
extern void     waitport();

#define inb(port) inportb(port)
#define outb(port, data) outportb(port, data)
#if IO_SLOW_MACHINE
    #define io_wait() waitport()
#else
    #define io_wait() /* Do nothing */
#endif

extern uint32_t rdmsr(uint32_t msr);
extern void     wrmsr(uint32_t msr, uint64_t val);

#endif