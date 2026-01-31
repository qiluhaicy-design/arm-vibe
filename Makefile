# Makefile for vibeOS
# ARM64 modular OS with GUI, desktop/phone modes, ISO install

# Compiler and tools
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
QEMU = qemu-system-aarch64

# Directories
BUILD_DIR = build
KERNEL_DIR = kernel
BOOTLOADER_DIR = bootloader

# Targets
.PHONY: all build run clean

# Default target
all: build

# Build the OS (placeholder for now)
build:
	@echo "Building vibeOS..."
	# TODO: Compile kernel, bootloader, etc.
	# For now, just create a dummy kernel image
	$(CC) -c $(KERNEL_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o 2>/dev/null || echo "Kernel source not ready yet"
	$(LD) -T $(KERNEL_DIR)/linker.ld $(BUILD_DIR)/kernel.o -o $(BUILD_DIR)/kernel.elf 2>/dev/null || echo "Linking not ready yet"
	@echo "Build complete (placeholder)."

# Run in QEMU ARM64
run: build
	@echo "Running vibeOS in QEMU ARM64..."
	$(QEMU) -M virt -cpu cortex-a53 -kernel $(BUILD_DIR)/kernel.elf -nographic

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*
	@echo "Clean complete."