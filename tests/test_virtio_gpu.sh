#!/bin/bash
# tests/test_virtio_gpu.sh - Test compilation of virtio GPU driver

echo "Testing virtio GPU driver compilation..."

# Compile virtio_gpu.c with headers
aarch64-elf-gcc -c drivers/virtio_gpu.c -I. -o /tmp/test_vgpu.o

if [ $? -eq 0 ]; then
    echo "Virtio GPU compilation successful."
    rm /tmp/test_vgpu.o
    exit 0
else
    echo "Virtio GPU compilation failed."
    exit 1
fi