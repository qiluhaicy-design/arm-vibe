#!/bin/bash
# tests/test_scheduler.sh - Test scheduler compilation and basic functionality

echo "Testing scheduler compilation..."

# Compile scheduler and task
aarch64-elf-gcc -c kernel/scheduler.c -I. -o /tmp/test_sched.o
aarch64-elf-gcc -c kernel/task.c -I. -o /tmp/test_task.o

if [ $? -eq 0 ]; then
    echo "Scheduler compilation successful."
    rm /tmp/test_sched.o /tmp/test_task.o
    exit 0
else
    echo "Scheduler compilation failed."
    exit 1
fi