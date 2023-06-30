bits 64

extern inportb:     function
extern outportb:    function
extern inportd:     function
extern outportd:    function
extern waitport:    function
extern rdmsr:       function
extern wrmsr:       function

section .text

inportb:
    mov dx, di

    in al, dx
    ret

outportb:
    mov dx, di
    mov al, sil

    out dx, al
    ret

waitport:

    mov dx, 0x80
    mov al, 0

    out dx, al
    ret

; Read from Model Specific Register
rdmsr: ; uint32_t msr

    mov ecx, edi    ; msr

    rdmsr

    shl rdx, 32     ; rdx = rdx << 32
    or rax, rdx

    ret

; Write to Model Specific Register
wrmsr: ; uint32_t msr, uint64_t val

    mov ecx, edi    ; msr

    mov eax, esi    ; val (low 32-bits)

    mov rdx, rsi    ; val (high 32-bits)
    shr rdx, 32     ; rdx = rdx >> 32

    wrmsr

    ret
