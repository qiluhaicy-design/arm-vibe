# Makefile for vibeOS
# ARM64 modular OS with GUI, desktop/phone modes, ISO install

# Compiler and tools for macOS ARM
CC = clang -target aarch64-elf
LD = ld.lld
QEMU = qemu-system-aarch64

# Directories
BUILD_DIR = build
BOOTLOADER_DIR = bootloader
KERNEL_DIR = kernel

# Targets
.PHONY: all build bootloader run clean

# Default target
all: build

# Build the OS
build: bootloader
	@echo "Building vibeOS complete."

# Build bootloader
bootloader: $(BUILD_DIR)/bootloader.elf

$(BUILD_DIR)/bootloader.elf: $(BOOTLOADER_DIR)/boot.S $(BOOTLOADER_DIR)/main.c $(BOOTLOADER_DIR)/linker.ld
	@echo "Compiling bootloader..."
	$(CC) -c $(BOOTLOADER_DIR)/boot.S -o $(BUILD_DIR)/boot.o
	$(CC) -c $(BOOTLOADER_DIR)/main.c -o $(BUILD_DIR)/main.o
	$(LD) -T $(BOOTLOADER_DIR)/linker.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/bootloader.elf

# Run in QEMU ARM64
run: build
	@echo "Running vibeOS in QEMU ARM64..."
	$(QEMU) -M virt -cpu cortex-a53 -kernel $(BUILD_DIR)/bootloader.elf -nographic

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*
	@echo "Clean complete."