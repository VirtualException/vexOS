#ifndef _ATTR_H
#define _ATTR_H

#define ASM(...)        asm volatile(__VA_ARGS__)
#define INTCALL(imm)    ASM("int %0" : : "i" (imm)) /* same as ASM("int $"#imm) */
#define IRQ_ON          ASM("sti")
#define IRQ_OFF         ASM("cli")
#ifdef __DEBUG__
    #define BREAKPOINT  ASM("1: jmp 1b");
#else
    #define BREAKPOINT
#endif

#define __ms_abi                __attribute__((ms_abi))
#define __sysv_abi              __attribute__((sysv_abi))
#define __interrupt             __attribute__((interrupt))
#define __general_regs_only     __attribute__((target("general-regs-only")))
#define __aligned(x)            __attribute__((__aligned__(x)))
#define __aligned_largest       __attribute__((__aligned__))
#define __packed                __attribute__((packed))
#define __always_inline         inline __attribute__((always_inline))
#define __unused                __attribute__((unused))
#define __fallthrough           __attribute__((fallthrough));

#endif