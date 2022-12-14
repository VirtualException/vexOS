bits 64

extern va_save
extern va_next

section .text

va_save:

; x86_64 SysV ABI calling convention: rdi, rsi, rdx, rcx, r8, r9, [STACK] (rax -> return)

    mov qword [rdi], rsi

    add rdi, 8
    mov qword [rdi], rdx

    add rdi, 8
    mov qword [rdi], rcx

    add rdi, 8
    mov qword [rdi], r8

    add rdi, 8
    mov qword [rdi], r9

    add rdi, 8
    mov r10, [rbp+16]
    mov qword [rdi], r10

    add rdi, 8
    mov r10, [rbp+24]
    mov qword [rdi], r10

    add rdi, 8
    mov qword [rdi], 0

    ret

va_next:

    ; Get index offset in bytes
    mov r10, [rdi + 56]
    shl r10, 3              ; Same as * 8

    mov rax, [rdi + r10]    ; Move to rax the value in the address offseted

    inc QWORD [rdi + 56]    ; Increment index

    ret