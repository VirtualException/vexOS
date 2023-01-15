bits 64

extern va_save
extern va_next

section .text

va_save:

; x86_64 SysV ABI calling convention: rdi, rsi, rdx, rcx, r8, r9, [STACK] (rax -> return)

    mov qword [rdi],    rsi
    mov qword [rdi+8],  rdx
    mov qword [rdi+16], rcx
    mov qword [rdi+24], r8
    mov qword [rdi+32], r9

    mov r10, qword [rbp+16]       ; stack argument
    mov qword [rdi+40], r10 
    mov r10, qword [rbp+24]       ; stack argument
    mov qword [rdi+48], r10
    mov r10, qword [rbp+32]       ; stack argument
    mov qword [rdi+56], r10

    mov qword [rdi+64], 0

    ret

va_next:

    mov r10,    [rdi+64]    ; Get index offset in bytes
    inc qword   [rdi+64]    ; Increment index
    mov rax,    [rdi+r10*8] ; Move into rax the value in the address, offseted

    ret