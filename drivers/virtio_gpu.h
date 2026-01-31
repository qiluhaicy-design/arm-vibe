// drivers/virtio_gpu.h - Virtio GPU header for vibeOS

#ifndef VIRTIO_GPU_H
#define VIRTIO_GPU_H

// Function declarations
void virtio_gpu_init();
uint32_t *virtio_gpu_get_fb();
void virtio_gpu_set_scanout(uint32_t width, uint32_t height);

#endif