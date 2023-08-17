
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
    . = 0x40008000; /* 0x40008000 is the start address of the program */
    . = ALIGN(4);
    .text :
    {
        start.o(.text)
        *(.text)
    }
    . = ALIGN(4);
    .data :
    {
        *(.data)
    }
    . = ALIGN(4);
    .bss :
    {
        *(.bss)
    }
}