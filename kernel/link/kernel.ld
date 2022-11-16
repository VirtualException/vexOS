ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    .text :
    {
        *(kmain);
        *(.text*);
    }
    .data :
    {
        *(.data);
    }
    .rodata :
    {
        *(.rodata*);
    }
    .bss :
    {
        *(.bss*);
    }
}