// ui/window.c - Window system for vibeOS

#include "window.h"
#include "../drivers/framebuffer.h"
#include "../libs/uart.h"

// Window list
static Window windows[MAX_WINDOWS];
static int window_count = 0;
static int next_z = 0;

// Initialize window system
void window_init() {
    uart_puts("Initializing window system...\n");
    window_count = 0;
    next_z = 0;
    uart_puts("Window system initialized\n");
}

// Create window
Window* create_window(int x, int y, int w, int h, uint32_t color, const char *title) {
    if (window_count >= MAX_WINDOWS) return 0;
    Window *win = &windows[window_count++];
    win->x = x;
    win->y = y;
    win->width = w;
    win->height = h;
    win->color = color;
    win->z_index = next_z++;
    win->focused = 0;
    for (int i = 0; i < 31 && title[i]; i++) win->title[i] = title[i];
    win->title[31] = 0;
    uart_puts("Created window: ");
    uart_puts(title);
    uart_puts("\n");
    return win;
}

// Move window
void move_window(Window *win, int x, int y) {
    win->x = x;
    win->y = y;
    uart_puts("Moved window\n");
}

// Set focus
void set_focus(Window *win) {
    for (int i = 0; i < window_count; i++) {
        windows[i].focused = 0;
    }
    win->focused = 1;
    uart_puts("Set focus to window\n");
}

// Set Z-index
void set_z_index(Window *win, int z) {
    win->z_index = z;
    uart_puts("Set Z-index\n");
}

// Render windows (sort by Z and draw)
void render_windows() {
    // Simple sort by Z (bubble sort for simplicity)
    for (int i = 0; i < window_count - 1; i++) {
        for (int j = 0; j < window_count - i - 1; j++) {
            if (windows[j].z_index > windows[j+1].z_index) {
                Window temp = windows[j];
                windows[j] = windows[j+1];
                windows[j+1] = temp;
            }
        }
    }
    // Draw each window
    for (int i = 0; i < window_count; i++) {
        Window *win = &windows[i];
        fb_draw_rect(win->x, win->y, win->width, win->height, win->color);
        // Draw title bar
        fb_draw_rect(win->x, win->y - 20, win->width, 20, COLOR_BLUE);
        fb_draw_text(win->x + 5, win->y - 15, win->title, COLOR_WHITE);
    }
    fb_swap_buffers();
    uart_puts("Rendered windows\n");
}