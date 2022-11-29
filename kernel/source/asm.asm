bits 64
extern testasm

section .text

testasm:

    int 0x10

    mov rax, 777
    ret