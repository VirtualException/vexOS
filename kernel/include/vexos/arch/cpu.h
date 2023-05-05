#ifndef _CPU_H
#define _CPU_H

#include <vexos/lib/types.h>
#include <vexos/lib/macros.h>

#define REG_D(reg) uint64_t reg ()

REG_D(rax);
REG_D(rcx);
REG_D(rdx);
REG_D(rbx);
REG_D(rsi);
REG_D(rdi);
REG_D(rsp);
REG_D(rbp);
REG_D(r8);
REG_D(r9);
REG_D(r10);
REG_D(r11);
REG_D(r12);
REG_D(r13);
REG_D(r14);
REG_D(r15);
REG_D(eflags);

#endif