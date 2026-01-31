#!/bin/bash
# Test script for vibeOS bootloader and kernel
# Builds and runs in QEMU, checks for debug output

echo "Testing vibeOS bootloader and kernel in QEMU..."

# Build
make build
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

# Run in QEMU with timeout and capture output
timeout 10s make run > test_output.log 2>&1 &
QEMU_PID=$!

# Wait a bit
sleep 5

# Kill QEMU
kill $QEMU_PID 2>/dev/null

# Check output for debug messages
if grep -q "vibeOS Bootloader started" test_output.log && grep -q "vibeOS Kernel started" test_output.log; then
    echo "✓ Bootloader and kernel debug messages found"
else
    echo "✗ Debug messages not found"
    cat test_output.log
    exit 1
fi

echo "Bootloader and kernel test passed."
rm test_output.log