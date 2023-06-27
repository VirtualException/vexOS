#ifndef _MACROS_H
#define _MACROS_H

#define ASM(...)        asm volatile(__VA_ARGS__)
#define INTCALL(imm)    ASM("int %0" : : "i" (imm)) /* same as ASM("int $"#imm) */
#define IRQ_ON  ASM("sti")
#define IRQ_OFF ASM("cli")
#ifdef __DEBUG__
    #define BREAKPOINT  ASM("1: jmp 1b");
#else
    #define BREAKPOINT
#endif

#endif
