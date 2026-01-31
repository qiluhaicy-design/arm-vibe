#!/bin/bash
# tests/test_framebuffer.sh - Test compilation of framebuffer driver

echo "Testing framebuffer driver compilation..."

# Compile framebuffer.c with headers
aarch64-elf-gcc -c drivers/framebuffer.c -I. -o /tmp/test_fb.o

if [ $? -eq 0 ]; then
    echo "Framebuffer compilation successful."
    rm /tmp/test_fb.o
    exit 0
else
    echo "Framebuffer compilation failed."
    exit 1
fi