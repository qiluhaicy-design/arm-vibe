// bootloader/main.c - Main bootloader code for vibeOS ARM64
// Initializes CPU, loads kernel, transfers control

// Define types for bare-metal
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

// Main bootloader function
void bootloader_main() {
    // Debug message
    uart_puts("vibeOS Bootloader started\n");

    // CPU initialization (basic)
    // TODO: More advanced init later

    // Load kernel (placeholder)
    uart_puts("Loading kernel...\n");
    // TODO: Actual kernel loading

    // Transfer control to kernel
    uart_puts("Transferring control to kernel...\n");
    // TODO: Jump to kernel entry

    // Infinite loop if kernel fails
    while (1) {
        uart_putc('.');
    }
}