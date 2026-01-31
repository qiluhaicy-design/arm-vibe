// drivers/framebuffer.h - Framebuffer driver header for vibeOS

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

// Define types for bare-metal
typedef unsigned int uint32_t;

// Framebuffer dimensions
#define FB_WIDTH 1024
#define FB_HEIGHT 768
#define FB_BPP 32  // Bits per pixel

// Framebuffer size
#define FB_SIZE (FB_WIDTH * FB_HEIGHT * (FB_BPP / 8))  // 1024*768*4 = 3MB

// Colors
#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE 0x0000FF

// Function declarations
void fb_init();
void fb_put_pixel(int x, int y, uint32_t color);
void fb_draw_rect(int x, int y, int w, int h, uint32_t color);
void fb_draw_text(int x, int y, const char *text, uint32_t color);
void fb_swap_buffers();
void fb_clear(uint32_t color);

#endif