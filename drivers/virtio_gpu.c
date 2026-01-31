// drivers/virtio_gpu.c - Virtio GPU driver for vibeOS

#include "virtio_gpu.h"
#include "virtio.h"
#include "../libs/uart.h"

// Virtio GPU base address (MMIO for device)
#define VIRTIO_GPU_BASE 0x0a000000

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
    // Basic virtio init (placeholder)
    // Set device status to ACKNOWLEDGE | DRIVER | FEATURES_OK | DRIVER_OK
    *(volatile uint32_t *)(VIRTIO_GPU_BASE + VIRTIO_GPU_DEVICE_STATUS) = 0x0F;
    // Assume queue 0 for control
    *(volatile uint32_t *)(VIRTIO_GPU_BASE + VIRTIO_GPU_QUEUE_SELECT) = 0;
    *(volatile uint32_t *)(VIRTIO_GPU_BASE + VIRTIO_GPU_QUEUE_SIZE) = 256; // placeholder
    // Set queue addr (placeholder, assume 0x80010000)
    *(volatile uint32_t *)(VIRTIO_GPU_BASE + VIRTIO_GPU_QUEUE_ADDRESS) = 0x80010000 >> 12;
    // Get display info
    virtio_gpu_get_display_info();
    // For now, assume FB at 0x80000000
    gpu_fb_addr = (uint32_t *)0x80000000;
    // Set scanout to activate display
    virtio_gpu_set_scanout(1024, 768);
    uart_puts("Virtio GPU initialized\n");
}

// Get framebuffer address
uint32_t *virtio_gpu_get_fb() {
    return gpu_fb_addr;
}

// Set scanout
void virtio_gpu_set_scanout(uint32_t width, uint32_t height) {
    virtio_gpu_cmd_set_scanout cmd = {
        .hdr = { .type = VIRTIO_GPU_CMD_SET_SCANOUT, .flags = 0, .fence_id = 0, .ctx_id = 0, .padding = 0 },
        .r_x = 0, .r_y = 0, .r_width = width, .r_height = height,
        .scanout_id = 0, .resource_id = 0
    };
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}

// Send command (placeholder)
void virtio_gpu_send_command(void *cmd, uint32_t size) {
    // Placeholder: Copy to queue, notify
    // In real: Add to virtqueue, set avail, notify
    uart_puts("Sending virtio GPU command...\n");
    // Simulate notify
    *(volatile uint32_t *)(VIRTIO_GPU_BASE + VIRTIO_GPU_QUEUE_NOTIFY) = 0;
}

// Get display info
void virtio_gpu_get_display_info() {
    virtio_gpu_get_display_info cmd = {
        .hdr = { .type = VIRTIO_GPU_CMD_GET_DISPLAY_INFO, .flags = 0, .fence_id = 0, .ctx_id = 0, .padding = 0 }
    };
    virtio_gpu_send_command(&cmd, sizeof(cmd));
}