// drivers/virtio_gpu.c - Virtio GPU driver for vibeOS

#include "virtio_gpu.h"
#include "pci.h"
#include "../libs/uart.h"

// Virtio GPU base address (from PCI BAR)
static uint32_t virtio_gpu_base = 0;

// GPU control registers
#define VIRTIO_GPU_DEVICE_FEATURES 0x00
#define VIRTIO_GPU_DRIVER_FEATURES 0x04
#define VIRTIO_GPU_QUEUE_ADDRESS 0x08
#define VIRTIO_GPU_QUEUE_SIZE 0x0C
#define VIRTIO_GPU_QUEUE_SELECT 0x0E
#define VIRTIO_GPU_QUEUE_NOTIFY 0x10
#define VIRTIO_GPU_DEVICE_STATUS 0x12
#define VIRTIO_GPU_ISR_STATUS 0x13

// GPU commands
#define VIRTIO_GPU_CMD_GET_DISPLAY_INFO 0x0100
#define VIRTIO_GPU_CMD_RESOURCE_CREATE_2D 0x0101
#define VIRTIO_GPU_CMD_RESOURCE_UNREF 0x0102
#define VIRTIO_GPU_CMD_SET_SCANOUT 0x0103
#define VIRTIO_GPU_CMD_RESOURCE_FLUSH 0x0104
#define VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D 0x0105
#define VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING 0x0106
#define VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING 0x0107

// Framebuffer address (set by GPU)
static uint32_t *gpu_fb_addr = 0;

// Initialize virtio GPU
void virtio_gpu_init() {
    uart_puts("Initializing virtio GPU...\n");
    // Find PCI device
    uint32_t pci_addr = pci_find_device(VIRTIO_GPU_VENDOR, VIRTIO_GPU_DEVICE);
    if (pci_addr == 0xFFFFFFFF) {
        uart_puts("Virtio GPU not found\n");
        return;
    }
    uint32_t bus = pci_addr >> 8;
    uint32_t dev = pci_addr & 0xFF;
    virtio_gpu_base = pci_get_bar(bus, dev, 0, 0) & ~0xF; // BAR0, mask flags
    uart_puts("Virtio GPU base: ");
    // (placeholder for hex print)
    // Basic virtio init
    *(volatile uint32_t *)(virtio_gpu_base + VIRTIO_GPU_DEVICE_STATUS) = 0x0F;
    *(volatile uint32_t *)(virtio_gpu_base + VIRTIO_GPU_QUEUE_SELECT) = 0;
    *(volatile uint32_t *)(virtio_gpu_base + VIRTIO_GPU_QUEUE_SIZE) = 256;
    *(volatile uint32_t *)(virtio_gpu_base + VIRTIO_GPU_QUEUE_ADDRESS) = 0x80010000 >> 12;
    // Get display info
    virtio_gpu_get_display_info();
    // Create resource
    virtio_gpu_create_resource(1, 1024, 768);
    // Attach backing
    virtio_gpu_attach_backing(1);
    // Assume FB at 0x80000000
    gpu_fb_addr = (uint32_t *)0x80000000;
    // Set scanout
    virtio_gpu_set_scanout(1024, 768);
    uart_puts("Virtio GPU initialized\n");
}

// Get framebuffer address
uint32_t *virtio_gpu_get_fb() {
    return gpu_fb_addr;
}

// Set scanout
void virtio_gpu_set_scanout(uint32_t width, uint32_t height) {
    struct virtio_gpu_cmd_set_scanout cmd;
    cmd.hdr.type = VIRTIO_GPU_CMD_SET_SCANOUT;
    cmd.hdr.flags = 0;
    cmd.hdr.fence_id = 0;
    cmd.hdr.ctx_id = 0;
    cmd.hdr.padding = 0;
    cmd.r_x = 0;
    cmd.r_y = 0;
    cmd.r_width = width;
    cmd.r_height = height;
    cmd.scanout_id = 0;
    cmd.resource_id = 1; // Use created resource
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}

// Send command (placeholder)
void virtio_gpu_send_command(void *cmd, uint32_t size) {
    // Placeholder: notify
    uart_puts("Sending virtio GPU command...\n");
    if (virtio_gpu_base) {
        *(volatile uint32_t *)(virtio_gpu_base + VIRTIO_GPU_QUEUE_NOTIFY) = 0;
    }
}

// Get display info
void virtio_gpu_get_display_info() {
    struct virtio_gpu_cmd_get_display_info cmd;
    cmd.hdr.type = VIRTIO_GPU_CMD_GET_DISPLAY_INFO;
    cmd.hdr.flags = 0;
    cmd.hdr.fence_id = 0;
    cmd.hdr.ctx_id = 0;
    cmd.hdr.padding = 0;
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}

// Create 2D resource
void virtio_gpu_create_resource(uint32_t id, uint32_t width, uint32_t height) {
    struct virtio_gpu_resource_create_2d cmd;
    cmd.hdr.type = VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
    cmd.hdr.flags = 0;
    cmd.hdr.fence_id = 0;
    cmd.hdr.ctx_id = 0;
    cmd.hdr.padding = 0;
    cmd.resource_id = id;
    cmd.format = 1; // BGRA
    cmd.width = width;
    cmd.height = height;
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}

// Attach backing
void virtio_gpu_attach_backing(uint32_t id) {
    struct virtio_gpu_resource_attach_backing cmd;
    cmd.hdr.type = VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
    cmd.hdr.flags = 0;
    cmd.hdr.fence_id = 0;
    cmd.hdr.ctx_id = 0;
    cmd.hdr.padding = 0;
    cmd.resource_id = id;
    cmd.nr_entries = 1;
    cmd.entry[0].addr = 0x80000000ULL; // FB addr
    cmd.entry[0].length = 1024 * 768 * 4;
    cmd.entry[0].padding = 0;
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}