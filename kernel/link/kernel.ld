ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    .text ALIGN(0x1000) :
    {
        *(.text);
        *(.data);
        *(.rodata);
    }
    .data ALIGN(0x1000) :
    {
        *(.data);
    }
    .rodata ALIGN(0x1000) :
    {
        *(.rodata);
    }
    .bss ALIGN(0x1000) :
    {
        *(.bss)
        *(.COMMON)
    }

}