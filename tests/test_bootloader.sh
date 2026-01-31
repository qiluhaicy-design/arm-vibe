#!/bin/bash
# Test script for vibeOS bootloader
# Builds and runs in QEMU, checks for debug output

echo "Testing vibeOS bootloader in QEMU..."

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
if grep -q "vibeOS Bootloader started" test_output.log; then
    echo "✓ Bootloader debug message found"
else
    echo "✗ Bootloader debug message not found"
    cat test_output.log
    exit 1
fi

echo "Bootloader test passed."
rm test_output.log