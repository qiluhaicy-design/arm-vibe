// libs/uart.h - UART header for vibeOS

#ifndef UART_H
#define UART_H

// Define types for bare-metal
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Function declarations
void uart_putc(char c);
void uart_puts(const char *s);
void uart_puthex(uint32_t val);

#endif