ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    .text :
    {
        *(.text);
        *(.rodata);
    }
    .rodata :
    {
        *(.rodata);
    }
    .data :
    {
        *(.data);
    }
    .bss :
    {
        *(.bss)
    }

}
