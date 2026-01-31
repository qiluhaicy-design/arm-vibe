// bootloader/main.c - Main bootloader code for vibeOS ARM64
// Initializes CPU, loads kernel, transfers control

#include "../libs/uart.h"

// UART base address for QEMU virt machine
#define UART_BASE 0x09000000

// Main bootloader function
void bootloader_main() {
    // Debug message
    uart_puts("vibeOS Bootloader started\n");

    // CPU initialization (basic)
    // TODO: More advanced init later

    // Load kernel (placeholder)
    uart_puts("Loading kernel...\n");
    // TODO: Actual kernel loading

    // Transfer control to kernel
    uart_puts("Transferring control to kernel...\n");
    // Call kernel main directly since embedded
    kernel_main();

    // Infinite loop if kernel fails
    while (1) {
        uart_putc('.');
    }
}