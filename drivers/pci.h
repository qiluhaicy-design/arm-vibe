// drivers/pci.h - PCI header for vibeOS

#ifndef PCI_H
#define PCI_H

// Define types for bare-metal
typedef unsigned int uint32_t;

// PCI config space
#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC

// Virtio GPU PCI IDs
#define VIRTIO_GPU_VENDOR 0x1AF4
#define VIRTIO_GPU_DEVICE 0x1050

// Function declarations
uint32_t pci_read_config(uint32_t bus, uint32_t dev, uint32_t func, uint32_t reg);
uint32_t pci_find_device(uint32_t vendor, uint32_t device);
uint32_t pci_get_bar(uint32_t bus, uint32_t dev, uint32_t func, uint32_t bar);

#endif