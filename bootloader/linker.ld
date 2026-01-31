/* bootloader/linker.ld - Linker script for ARM64 bootloader */

ENTRY(_start)

SECTIONS {
    . = 0x40000000;  /* Load address for QEMU virt */

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

    _stack_bottom = .;
    . += 4096;
    _stack_top = .;
}