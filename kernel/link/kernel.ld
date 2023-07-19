ENTRY(start_kernel)
OUTPUT_FORMAT(elf64-x86-64)

SECTIONS
{
    . = 0x1000;

    _kern_start = .;

    .text :
    {
        _kern_code = .;
        /* kernel/out/kernel.o = . */
        *(.text)
        *(.rodata*)
    }

    .data :
    {
        _kern_data = .;
        *(.data)
    }

    .bss :
    {
        _kern_bss = .;
        *(.bss)
        *(COMMON)
    }

    _kern_end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
    }
}
