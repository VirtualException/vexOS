ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    .text :
    {
        *(start_kernel);
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
        *(.bss);
    }
}