// kernel/kernel.c - Main kernel entry for vibeOS

#include "../libs/uart.h"
#include "../drivers/framebuffer.h"

// Function declarations
extern void memory_init();
extern void timer_init();
extern void interrupt_init();
extern void scheduler_init();
extern void scheduler_start();

// Test screen function
void test_screen() {
    fb_draw_rect(100, 100, 200, 150, COLOR_RED);
    fb_draw_text(100, 300, "vibeOS Test Screen", COLOR_WHITE);
    fb_swap_buffers();
}

// Kernel main function
void kernel_main() {
    uart_puts("vibeOS Kernel started\n");

    // Initialize subsystems
    memory_init();
    timer_init();
    interrupt_init();
    scheduler_init();
    fb_init();

    uart_puts("Kernel initialization complete\n");

    // Test screen
    test_screen();

    // Start scheduler
    scheduler_start();

    // Should not reach here
    while (1) {
        uart_putc('.');
    }
}