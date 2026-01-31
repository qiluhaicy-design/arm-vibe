// kernel/scheduler.c - Simple scheduler for vibeOS

#include "task.h"
#include "../libs/uart.h"

// Idle task stack (placeholder, 1KB)
static uint32_t idle_stack[256];

// Idle task function
void idle_task() {
    while (1) {
        uart_putc('I'); // Indicate idle
    }
}

// Scheduler init
void scheduler_init() {
    uart_puts("Initializing scheduler...\n");
    task_init();
    // Create idle task
    create_task(idle_task, idle_stack, 256);
    uart_puts("Scheduler initialized\n");
}

// Scheduler start
void scheduler_start() {
    uart_puts("Starting scheduler...\n");
    // For now, just run idle task
    switch_to_task(task_list);
    // Should not return
}