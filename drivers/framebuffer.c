// drivers/framebuffer.c - Framebuffer driver for vibeOS

#include "framebuffer.h"
#include "../libs/uart.h"

// Framebuffer base address (placeholder for QEMU virt)
#define FB_BASE 0x50000000
#define FB_SIZE (FB_WIDTH * FB_HEIGHT * (FB_BPP / 8))

// Double buffering
static uint32_t *front_buffer;
static uint32_t *back_buffer;
static uint32_t *current_buffer;

// Initialize framebuffer
void fb_init() {
    front_buffer = (uint32_t *)FB_BASE;
    back_buffer = (uint32_t *)(FB_BASE + FB_SIZE);
    current_buffer = back_buffer;
    uart_puts("Initializing framebuffer...\n");
    // TODO: Set up virtio-gpu or memory mapping
    // fb_clear(COLOR_BLACK);  // Skip for now to avoid memory issues
    uart_puts("Framebuffer initialized\n");
}

// Put pixel
void fb_put_pixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < FB_WIDTH && y >= 0 && y < FB_HEIGHT) {
        current_buffer[y * FB_WIDTH + x] = color;
        // Debug: show pixel draw
        // uart_puts("Pixel at ");
        // (placeholder for int to string)
    }
}

// Draw rectangle
void fb_draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            fb_put_pixel(x + i, y + j, color);
        }
    }
}

// Draw text (simple, using UART for now)
void fb_draw_text(int x, int y, const char *text, uint32_t color) {
    // Placeholder: draw pixels for text, but for now use UART
    uart_puts("Drawing text: ");
    uart_puts(text);
    uart_puts("\n");
    // TODO: Implement pixel text rendering
}

// Swap buffers
void fb_swap_buffers() {
    // Swap pointers
    uint32_t *temp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
    current_buffer = back_buffer;
    // TODO: Notify display
}

// Clear buffer
void fb_clear(uint32_t color) {
    for (int i = 0; i < FB_WIDTH * FB_HEIGHT; i++) {
        current_buffer[i] = color;
    }
}