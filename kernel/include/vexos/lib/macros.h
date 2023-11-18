#ifndef _MACROS_H
#define _MACROS_H

#define ASM(...)        asm volatile(__VA_ARGS__)
#define INTCALL(imm)    ASM("int %0" : : "i" (imm)) /* same as ASM("int $"#imm) */

#define IRQ_ON  ASM("sti")  /* Enable all interrupts */
#define IRQ_OFF ASM("cli")  /* Disable all interrupts */

#ifdef __DEBUG__
    #define BREAKPOINT  ASM("int3");
    #define STOP        ASM("1: pause; jmp 1");
#else
    #define BREAKPOINT
    #define STOP
#endif

#endif
