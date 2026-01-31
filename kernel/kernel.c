// kernel/kernel.c - Main kernel entry for vibeOS

#include "../libs/uart.h"

// Kernel main function
void kernel_main() {
    uart_puts("vibeOS Kernel started\n");

    // Initialize subsystems
    memory_init();
    timer_init();
    interrupt_init();
    scheduler_init();

    uart_puts("Kernel initialization complete\n");

    // Start scheduler
    scheduler_start();

    // Should not reach here
    while (1) {
        uart_putc('.');
    }
}