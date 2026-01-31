// libs/uart.h - UART header for vibeOS

#ifndef UART_H
#define UART_H

// Function declarations
void uart_putc(char c);
void uart_puts(const char *s);
void uart_puthex(uint32_t val);

#endif