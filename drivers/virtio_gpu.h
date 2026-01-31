// drivers/virtio_gpu.h - Virtio GPU header for vibeOS

#ifndef VIRTIO_GPU_H
#define VIRTIO_GPU_H

// Define types for bare-metal
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// Virtio GPU command header
struct virtio_gpu_ctrl_hdr {
    uint32_t type;
    uint32_t flags;
    uint32_t fence_id; // simplified to uint32_t
    uint32_t ctx_id;
    uint32_t padding;
};

// Set scanout command
struct virtio_gpu_cmd_set_scanout {
    struct virtio_gpu_ctrl_hdr hdr;
    uint32_t r_x, r_y, r_width, r_height;
    uint32_t scanout_id;
    uint32_t resource_id;
};

// Get display info command
struct virtio_gpu_cmd_get_display_info {
    struct virtio_gpu_ctrl_hdr hdr;
};

// Display info response
struct virtio_gpu_resp_display_info {
    struct virtio_gpu_ctrl_hdr hdr;
    uint32_t num_scanouts;
    struct {
        uint32_t enabled;
        uint32_t flags;
        uint32_t x, y, width, height;
    } pmodes[16];
};

// Create 2D resource command
struct virtio_gpu_resource_create_2d {
    struct virtio_gpu_ctrl_hdr hdr;
    uint32_t resource_id;
    uint32_t format;
    uint32_t width;
    uint32_t height;
};

// Attach backing command
struct virtio_gpu_resource_attach_backing {
    struct virtio_gpu_ctrl_hdr hdr;
    uint32_t resource_id;
    uint32_t nr_entries;
    struct {
        uint64_t addr;
        uint32_t length;
        uint32_t padding;
    } entry[1];
};

// Function declarations
void virtio_gpu_init();
uint32_t *virtio_gpu_get_fb();
void virtio_gpu_set_scanout(uint32_t width, uint32_t height);
void virtio_gpu_send_command(void *cmd, uint32_t size);
void virtio_gpu_get_display_info();
void virtio_gpu_create_resource(uint32_t id, uint32_t width, uint32_t height);
void virtio_gpu_attach_backing(uint32_t id);

#endif