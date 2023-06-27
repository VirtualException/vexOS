bits 64

extern syscall_entry_64:    function
extern syscall:             function
extern syscall_table:       data

%define SYSRET 0

section .text

; Function called by the "syscall" instruction
syscall_entry_64:

    push rcx
    push r11

    ; Call function from syscall table
    call [syscall_table + rax * 8]

    pop r11
    pop rcx

    ; IMPORTANT!
    ; If we return using "sysret", we will crash, as privilege/segment stuff
    ; is broken/unimplemented. We need to return using normal "ret", like a
    ; normal function.

%if !SYSRET
    ret
%else
    o64 sysret
%endif

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