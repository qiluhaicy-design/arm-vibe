# Makefile for vibeOS
# ARM64 modular OS with GUI, desktop/phone modes, ISO install

# Compiler and tools for macOS ARM
CC = aarch64-elf-gcc
LD = aarch64-elf-ld
QEMU = qemu-system-aarch64

# Directories
BUILD_DIR = build
BOOTLOADER_DIR = bootloader
KERNEL_DIR = kernel
LIBS_DIR = libs
DRIVERS_DIR = drivers
UI_DIR = ui

# Targets
.PHONY: all build bootloader kernel run clean

# Default target
all: build

# Build the OS
build: bootloader kernel
	@echo "Building vibeOS complete."

# Build bootloader (including kernel)
bootloader: $(BUILD_DIR)/bootloader.elf

$(BUILD_DIR)/bootloader.elf: $(BOOTLOADER_DIR)/boot.S $(BOOTLOADER_DIR)/main.c $(KERNEL_DIR)/kernel.c $(KERNEL_DIR)/memory.c $(KERNEL_DIR)/timer.c $(KERNEL_DIR)/interrupt.c $(KERNEL_DIR)/scheduler.c $(KERNEL_DIR)/task.c $(LIBS_DIR)/uart.c $(DRIVERS_DIR)/framebuffer.c $(DRIVERS_DIR)/virtio_gpu.c $(DRIVERS_DIR)/pci.c $(UI_DIR)/window.c $(BOOTLOADER_DIR)/linker.ld
	@echo "Compiling bootloader with kernel..."
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(BOOTLOADER_DIR)/boot.S -o $(BUILD_DIR)/boot.o
	$(CC) -c $(BOOTLOADER_DIR)/main.c -o $(BUILD_DIR)/main.o
	$(CC) -c $(KERNEL_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o
	$(CC) -c $(KERNEL_DIR)/memory.c -o $(BUILD_DIR)/memory.o
	$(CC) -c $(KERNEL_DIR)/timer.c -o $(BUILD_DIR)/timer.o
	$(CC) -c $(KERNEL_DIR)/interrupt.c -o $(BUILD_DIR)/interrupt.o
	$(CC) -c $(KERNEL_DIR)/scheduler.c -o $(BUILD_DIR)/scheduler.o
	$(CC) -c $(KERNEL_DIR)/task.c -o $(BUILD_DIR)/task.o
	$(CC) -c $(LIBS_DIR)/uart.c -o $(BUILD_DIR)/uart.o
	$(CC) -c $(DRIVERS_DIR)/framebuffer.c -o $(BUILD_DIR)/framebuffer.o
	$(CC) -c $(DRIVERS_DIR)/virtio_gpu.c -o $(BUILD_DIR)/virtio_gpu.o
	$(CC) -c $(DRIVERS_DIR)/pci.c -o $(BUILD_DIR)/pci.o
	$(CC) -c $(UI_DIR)/window.c -o $(BUILD_DIR)/window.o
	$(LD) -T $(BOOTLOADER_DIR)/linker.ld $(BUILD_DIR)/boot.o $(BUILD_DIR)/main.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/interrupt.o $(BUILD_DIR)/scheduler.o $(BUILD_DIR)/task.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/framebuffer.o $(BUILD_DIR)/virtio_gpu.o $(BUILD_DIR)/pci.o $(BUILD_DIR)/window.o -o $(BUILD_DIR)/bootloader.elf

# Build kernel
kernel: $(BUILD_DIR)/kernel.elf

$(BUILD_DIR)/kernel.elf: $(KERNEL_DIR)/kernel.c $(KERNEL_DIR)/memory.c $(KERNEL_DIR)/timer.c $(KERNEL_DIR)/interrupt.c $(KERNEL_DIR)/scheduler.c $(KERNEL_DIR)/task.c $(LIBS_DIR)/uart.c $(DRIVERS_DIR)/framebuffer.c $(DRIVERS_DIR)/virtio_gpu.c $(DRIVERS_DIR)/pci.c $(UI_DIR)/window.c $(KERNEL_DIR)/linker.ld
	@echo "Compiling kernel..."
	$(CC) -c $(KERNEL_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o
	$(CC) -c $(KERNEL_DIR)/memory.c -o $(BUILD_DIR)/memory.o
	$(CC) -c $(KERNEL_DIR)/timer.c -o $(BUILD_DIR)/timer.o
	$(CC) -c $(KERNEL_DIR)/interrupt.c -o $(BUILD_DIR)/interrupt.o
	$(CC) -c $(KERNEL_DIR)/scheduler.c -o $(BUILD_DIR)/scheduler.o
	$(CC) -c $(KERNEL_DIR)/task.c -o $(BUILD_DIR)/task.o
	$(CC) -c $(LIBS_DIR)/uart.c -o $(BUILD_DIR)/uart.o
	$(CC) -c $(DRIVERS_DIR)/framebuffer.c -o $(BUILD_DIR)/framebuffer.o
	$(CC) -c $(DRIVERS_DIR)/virtio_gpu.c -o $(BUILD_DIR)/virtio_gpu.o
	$(CC) -c $(DRIVERS_DIR)/pci.c -o $(BUILD_DIR)/pci.o
	$(CC) -c $(UI_DIR)/window.c -o $(BUILD_DIR)/window.o
	$(LD) -T $(KERNEL_DIR)/linker.ld $(BUILD_DIR)/kernel.o $(BUILD_DIR)/memory.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/interrupt.o $(BUILD_DIR)/scheduler.o $(BUILD_DIR)/task.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/framebuffer.o $(BUILD_DIR)/virtio_gpu.o $(BUILD_DIR)/pci.o $(BUILD_DIR)/window.o -o $(BUILD_DIR)/kernel.elf

# Run in QEMU ARM64 with virtio GPU
run: build
	@echo "Running vibeOS in QEMU ARM64 with virtio GPU..."
	$(QEMU) -M virt -cpu cortex-a53 -kernel $(BUILD_DIR)/bootloader.elf -device virtio-gpu-pci -serial stdio

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)/*
	@echo "Clean complete."