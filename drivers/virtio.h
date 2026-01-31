// drivers/virtio.h - Virtio header for vibeOS

#ifndef VIRTIO_H
#define VIRTIO_H

// Define types for bare-metal
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

// Virtio device IDs
#define VIRTIO_ID_GPU 16

// Virtio status
#define VIRTIO_STATUS_ACK 1
#define VIRTIO_STATUS_DRIVER 2
#define VIRTIO_STATUS_DRIVER_OK 4
#define VIRTIO_STATUS_FEATURES_OK 8
#define VIRTIO_STATUS_FAILED 128

// Virtio structures
typedef struct {
    uint32_t type;
    uint32_t reserved;
    uint64_t addr;
    uint32_t length;
    uint16_t flags;
    uint16_t next;
} virtq_desc_t;

typedef struct {
    uint16_t flags;
    uint16_t idx;
    uint16_t ring[0];
} virtq_avail_t;

typedef struct {
    uint16_t flags;
    uint16_t idx;
    struct {
        uint32_t id;
        uint32_t len;
    } ring[0];
} virtq_used_t;

typedef struct {
    uint32_t num;
    uint32_t num_next;
    uint16_t event;
    uint16_t event_next;
} virtq_event_suppress_t;

typedef struct {
    virtq_desc_t *desc;
    virtq_avail_t *avail;
    virtq_used_t *used;
    uint16_t last_used_idx;
} virtq_t;

// Function declarations
void virtio_init(uint32_t base);
void virtq_init(virtq_t *vq, uint32_t num, uint32_t base);

#endif