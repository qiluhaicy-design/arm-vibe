// drivers/framebuffer.h - Framebuffer driver header for vibeOS

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

// Framebuffer dimensions
#define FB_WIDTH 1024
#define FB_HEIGHT 768
#define FB_BPP 32  // Bits per pixel

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