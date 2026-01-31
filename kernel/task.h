// kernel/task.h - Task management header for vibeOS

#ifndef TASK_H
#define TASK_H

// Define types for bare-metal
typedef unsigned int uint32_t;

// Task structure
typedef struct Task {
    uint32_t *stack_pointer;  // Current stack pointer
    void (*entry_point)(void); // Function to run
    struct Task *next;        // Next task in list
    uint32_t state;           // 0 = ready, 1 = running
} Task;

// Function declarations
void task_init();
Task *create_task(void (*entry)(void), uint32_t *stack, uint32_t stack_size);
void switch_to_task(Task *task);

#endif