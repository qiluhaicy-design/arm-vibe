// kernel/interrupt.c - Interrupt handler for vibeOS

#include "../libs/uart.h"

// Interrupt init (placeholder)
void interrupt_init() {
    uart_puts("Initializing interrupts...\n");
    // TODO: Set up GIC, handlers
    uart_puts("Interrupts initialized\n");
}