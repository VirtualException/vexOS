bits 64

extern va_save

section .text

va_save:

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
    mov dword [rdi], 0

    ret