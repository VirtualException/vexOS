bits 64

extern syscall_enable
extern syscall_entry_64
extern syscall

extern syscall_table

section .text

; Setup cpu to handle syscalls
syscall_enable:

    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000001  ; enable syscalls
    wrmsr

    mov ecx, 0xC0000082
    mov edx, esi        ; high 32-bits of entry point
    mov eax, edi        ; low 32-bits of entry point
    wrmsr

    ret

; Function called by the "syscall" instruction
syscall_entry_64:

    push rcx    ; save old rip

    ; call function from syscall table
    jmp [syscall_table + rax * 8]

    pop rcx     ; restore old rip
    o64 sysret

; C-only syscall implementation
syscall:

    ; change args order

    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov rcx, r8
    mov r8, r9

    syscall

    ret