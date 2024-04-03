bits 64

extern inportb:     function
extern outportb:    function
extern waitport:    function
extern rdmsr:       function
extern wrmsr:       function
extern cpuid:       function
extern cpuid_eax:   function
extern cpuid_ebx:   function
extern cpuid_ecx:   function
extern cpuid_edx:   function

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

cpuid: ; uint32_t val, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx

;   edi:    uint32_t val
;   rsi:    uint32_t* eax
;   rdx:    uint32_t* ebx
;   rcx:    uint32_t* ecx
;   r8:     uint32_t* edx

    mov r11, rbx    ; save rbx

    mov r9, rdx     ; save rdx
    mov r10, rcx    ; save rcx

    mov eax, edi
    cpuid           ; now cpuid data is on eax, ebx, ecx and edx

    ; move cpuid data into memory
    mov DWORD [rsi], eax
    mov DWORD [r9], ebx
    mov DWORD [r10], ecx
    mov DWORD [r8], edx

    mov rbx, r11    ; restore rbx

    ret

cpuid_eax: ; uint32_t val

    mov r11, rbx    ; save rbx

    mov eax, edi
    cpuid

    mov rbx, r11    ; restore rbx

    ret

cpuid_ebx: ; uint32_t val

    mov r11, rbx    ; save rbx

    mov eax, edi
    cpuid
    mov eax, ebx    ; return ebx

    mov rbx, r11    ; restore rbx

    ret

cpuid_ecx: ; uint32_t val

    mov r11, rbx    ; save rbx

    mov eax, edi
    cpuid
    mov eax, ecx    ; return ecx

    mov rbx, r11    ; restore rbx

    ret

cpuid_edx: ; uint32_t val

    mov r11, rbx    ; save rbx

    mov eax, edi
    cpuid
    mov eax, edx    ; return edx

    mov rbx, r11    ; restore rbx

    ret
