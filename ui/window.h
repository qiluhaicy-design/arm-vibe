// ui/window.h - Window system header for vibeOS

#ifndef WINDOW_H
#define WINDOW_H

// Define types for bare-metal
typedef unsigned int uint32_t;

// Window structure
typedef struct {
    int x, y;          // Position
    int width, height; // Size
    uint32_t color;    // Background color
    int z_index;       // Z-order
    int focused;       // Focus flag
    char title[32];    // Title
} Window;

// Max windows
#define MAX_WINDOWS 10

// Function declarations
void window_init();
Window* create_window(int x, int y, int w, int h, uint32_t color, const char *title);
void move_window(Window *win, int x, int y);
void set_focus(Window *win);
void set_z_index(Window *win, int z);
void render_windows();

#endif