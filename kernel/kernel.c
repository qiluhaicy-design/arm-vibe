// kernel/kernel.c - Main kernel entry for vibeOS

#include "../libs/uart.h"

// Function declarations
extern void memory_init();
extern void timer_init();
extern void interrupt_init();
extern void scheduler_init();
extern void scheduler_start();

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