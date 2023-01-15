bits 64

extern gdt_load
extern idt_load
extern syscall_setup
extern syscall
extern syscall_handler

section .text

; Load GDT
gdt_load:

    lgdt [rdi]

    ; Update segment-stuff

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi
    mov rax, 0x08
    push rax
    push rdi
    retfq

; Load IDT
idt_load:

    lidt [rdi]
    ret