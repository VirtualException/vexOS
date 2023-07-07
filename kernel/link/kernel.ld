ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    . = 0x1000;

    _k_start = .;

    .text :
    {
        _k_code = .;
        /* kernel/out/kernel.o = . */
        *(.text)
        *(.rodata*)
    }

    .data :
    {
        _k_data = .;
        *(.data)
    }

    .bss :
    {
        _k_bss = .;
        *(.bss)
        *(COMMON)
    }

    _k_end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
    }
}
