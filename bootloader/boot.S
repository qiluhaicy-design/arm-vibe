/* bootloader/boot.S - ARM64 bootloader entry point */
/* Initializes CPU, sets up stack, calls main */

.section .text
.global _start

_start:
    /* Disable interrupts */
    msr daifset, #0xF

    /* Set up stack pointer */
    ldr x0, =_stack_top
    mov sp, x0

    /* Initialize UART (basic) */
    /* TODO: More init */

    /* Call main bootloader function */
    bl bootloader_main

    /* Should not reach here */
    b .

.section .bss
.align 16
_stack_bottom:
    .space 4096  /* 4KB stack */
_stack_top: