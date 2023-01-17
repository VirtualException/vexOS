#ifndef _ATTR_H
#define _ATTR_H

#define ASM(...)        asm volatile(__VA_ARGS__)
#define INTCALL(imm)    ASM("int %0" : : "i" (imm)) /* same as ASM("int $"#imm) */
#define SYSCALL         ASM("syscall")
#define IRQ_ON          ASM("sti")
#define IRQ_OFF         ASM("cli")
#define STOP            while(1){}

#define __ms_abi                __attribute__((ms_abi))
#define __sysv_abi              __attribute__((sysv_abi))
#define __interrupt             __attribute__((interrupt))
#define __aligned(x)            __attribute__((__aligned__(x)))
#define __aligned_largest       __attribute__((__aligned__))
#define __packed                __attribute__((packed))
#define __always_inline         inline __attribute__((always_inline))

#endif