// kernel/kernel.c - Main kernel entry for vibeOS

#include "../libs/uart.h"
#include "../drivers/framebuffer.h"
#include "../ui/window.h"

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

// Test windows function
void test_windows() {
    window_init();
    Window *win1 = create_window(50, 50, 300, 200, COLOR_RED, "Window 1");
    Window *win2 = create_window(100, 100, 250, 150, COLOR_GREEN, "Window 2");
    Window *win3 = create_window(150, 150, 200, 100, COLOR_BLUE, "Window 3");
    move_window(win1, 60, 60);
    set_focus(win2);
    set_z_index(win3, 10);
    render_windows();
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

    // Test windows
    test_windows();

    uart_puts("Test screen and windows done\n");

    // Start scheduler
    scheduler_start();

    // Should not reach here
    while (1) {
        uart_putc('.');
    }
}