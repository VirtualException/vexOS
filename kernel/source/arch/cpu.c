#include <vexos/arch/cpu.h>

#define REG(reg) REG_D(reg) { register uint64_t ret asm (#reg); return ret; }

REG(rax)
REG(rcx)
REG(rdx)
REG(rbx)
REG(rsi)
REG(rdi)
REG(rsp)
REG(rbp)
REG(r8)
REG(r9)
REG(r10)
REG(r11)
REG(r12)
REG(r13)
REG(r14)
REG(r15)

REG_D(eflags) {
    uint64_t ret;

    asm volatile("pushfq");
    asm volatile("pop %0" : "=r"(ret)); /* LORD HAVE MERCY, AT&T syntax is SHIT */

    return ret;
}