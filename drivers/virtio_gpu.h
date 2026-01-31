// drivers/virtio_gpu.h - Virtio GPU header for vibeOS

#ifndef VIRTIO_GPU_H
#define VIRTIO_GPU_H

// Define types for bare-metal
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Virtio GPU command header
typedef struct {
    uint32_t type;
    uint32_t flags;
    uint64_t fence_id;
    uint32_t ctx_id;
    uint32_t padding;
} virtio_gpu_ctrl_hdr;

// Get display info command
typedef struct {
    virtio_gpu_ctrl_hdr hdr;
} virtio_gpu_get_display_info;

// Display info response
typedef struct {
    virtio_gpu_ctrl_hdr hdr;
    uint32_t num_scanouts;
    struct {
        uint32_t enabled;
        uint32_t flags;
        uint32_t x, y, width, height;
    } pmodes[16];
} virtio_gpu_resp_display_info;

// Function declarations
void virtio_gpu_init();
uint32_t *virtio_gpu_get_fb();
void virtio_gpu_set_scanout(uint32_t width, uint32_t height);
void virtio_gpu_send_command(void *cmd, uint32_t size);
void virtio_gpu_get_display_info();

#endif