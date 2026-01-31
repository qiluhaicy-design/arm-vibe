// kernel/scheduler.c - Simple scheduler for vibeOS

#include "../libs/uart.h"

// Scheduler init (placeholder)
void scheduler_init() {
    uart_puts("Initializing scheduler...\n");
    // TODO: Set up task list
    uart_puts("Scheduler initialized\n");
}

void scheduler_start() {
    uart_puts("Starting scheduler...\n");
    // TODO: Round-robin scheduling
    while (1) {
        // Yield to next task
    }
}