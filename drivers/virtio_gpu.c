// drivers/virtio_gpu.c - Virtio GPU driver for vibeOS

#include "virtio.h"
#include "../libs/uart.h"

// Virtio GPU base address (placeholder for PCI)
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
    // TODO: PCI discovery, setup queues, get display info, set scanout
    // For now, assume FB at 0x80000000
    gpu_fb_addr = (uint32_t *)0x80000000;
    uart_puts("Virtio GPU initialized\n");
}

// Get framebuffer address
uint32_t *virtio_gpu_get_fb() {
    return gpu_fb_addr;
}