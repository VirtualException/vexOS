section .text

extern memset     ; 1 byte
extern memset32   ; 4 bytes

memset:
    mov rcx, rsi        ; size (vmem size / 1)
l8:
    mov [rdi], dl
    inc rdi
    loop l8

    ret

memset32:
    mov r8, rdx
    mov rdx, 0
    mov rax, rsi        ; dividend (vmem)
    mov rcx, 4          ; divisor
    div rcx
    mov rcx, rax        ; size (vmem size / 4)
l32:
    mov [rdi], r8
    add rdi, 4
    loop l32

    ret