/* kernel/linker.ld - Linker script for ARM64 kernel */

ENTRY(kernel_main)

SECTIONS {
    . = 0x40080000;  /* Kernel load address */

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    }
}