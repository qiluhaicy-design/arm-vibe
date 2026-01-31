// drivers/pci.c - PCI driver for vibeOS

#include "pci.h"

// Read PCI config register
uint32_t pci_read_config(uint32_t bus, uint32_t dev, uint32_t func, uint32_t reg) {
    uint32_t addr = (1 << 31) | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC);
    *(volatile uint32_t *)PCI_CONFIG_ADDR = addr;
    return *(volatile uint32_t *)PCI_CONFIG_DATA;
}

// Find PCI device
uint32_t pci_find_device(uint32_t vendor, uint32_t device) {
    for (uint32_t bus = 0; bus < 256; bus++) {
        for (uint32_t dev = 0; dev < 32; dev++) {
            uint32_t id = pci_read_config(bus, dev, 0, 0);
            if ((id & 0xFFFF) == vendor && (id >> 16) == device) {
                return (bus << 8) | dev;
            }
        }
    }
    return 0xFFFFFFFF; // Not found
}

// Get BAR
uint32_t pci_get_bar(uint32_t bus, uint32_t dev, uint32_t func, uint32_t bar) {
    return pci_read_config(bus, dev, func, 0x10 + bar * 4);
}