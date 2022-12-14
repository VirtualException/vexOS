bits 64

extern gdt_load
extern idt_load

section .text

gdt_load:
    ; Load GDT
    ;lgdt [rdi]
    ; Apply changes ?
    ret

idt_load:
    ; Load IDT
    ;lidt [rdi]
    ret