bits 64

extern syscall_entry_64
extern syscall

extern syscall_table

section .text

; Function called by the "syscall" instruction
syscall_entry_64:

    push rcx    ; Save old rip

    ; Call function from syscall table
    jmp [syscall_table + rax * 8]

    pop rcx     ; Restore old rip
    o64 sysret

; C-only syscall implementation
syscall:

    ; Change args order

    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov rcx, r8
    mov r8, r9

    syscall

    ret