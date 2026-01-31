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

// Function to print hex value
void uart_puthex(uint32_t val) {
    char buf[9];
    buf[8] = '\0';
    for (int i = 7; i >= 0; i--) {
        uint8_t digit = val & 0xF;
        buf[i] = digit < 10 ? '0' + digit : 'A' + digit - 10;
        val >>= 4;
    }
    uart_puts(buf);
}