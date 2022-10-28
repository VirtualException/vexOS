extern inportb
extern outportb
extern inportd
extern outportd

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

inportd:
    mov dx, di

    in eax, dx
    ret

outportd:
    mov dx, di
    mov eax, esi

    out dx, eax
    ret