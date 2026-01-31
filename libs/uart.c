// libs/uart.c - UART functions for vibeOS logging

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// UART base address for QEMU virt machine
#define UART_BASE 0x09000000

// Function to send a character to UART
void uart_putc(char c) {
    volatile uint32_t *uart = (volatile uint32_t *)UART_BASE;
    *uart = c;
}

// Function to send a string to UART
void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}