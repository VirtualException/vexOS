#ifndef _IO_H
#define _IO_H

#include <vexos/lib/types.h>

extern uint8_t  inportb(uint16_t port);
extern void     outportb(uint16_t port, uint8_t data);
extern void     waitport();

#define inb(port)           inportb(port)
#define outb(port, data)    outportb(port, data)
#define io_wait()           waitport()

extern void     cpuid(uint32_t val, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx);
extern uint32_t cpuid_eax(uint32_t val);
extern uint32_t cpuid_ebx(uint32_t val);
extern uint32_t cpuid_ecx(uint32_t val);
extern uint32_t cpuid_edx(uint32_t val);

extern uint32_t rdmsr(uint32_t msr);
extern void     wrmsr(uint32_t msr, uint64_t val);

#endif
