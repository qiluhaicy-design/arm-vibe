#!/bin/bash
# Test script for vibeOS project structure
# Checks if all required directories exist

REQUIRED_DIRS=("bootloader" "kernel" "drivers" "ui" "apps" "libs" "build" "tests" "docs")

echo "Testing vibeOS project structure..."

for dir in "${REQUIRED_DIRS[@]}"; do
    if [ -d "$dir" ]; then
        echo "✓ $dir exists"
    else
        echo "✗ $dir missing"
        exit 1
    fi
done

echo "All directories present. Structure test passed."