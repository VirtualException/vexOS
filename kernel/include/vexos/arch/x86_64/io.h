#ifndef _IO_H
#define _IO_H

#include <vexos/lib/types.h>

extern uint8_t  inportb(uint16_t port);
extern void     outportb(uint16_t port, uint8_t data);

extern uint32_t inportd(uint16_t port);
extern void     outportd(uint16_t port, uint16_t data);

extern uint32_t rdmsr(uint32_t msr);
extern void     wrmsr(uint32_t msr, uint64_t val);

#endif