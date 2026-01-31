// kernel/memory.c - Memory initialization for vibeOS

#include "../libs/uart.h"

// Simple memory init (placeholder)
void memory_init() {
    uart_puts("Initializing memory...\n");
    // TODO: Set up page tables, heap, etc.
    uart_puts("Memory initialized\n");
}