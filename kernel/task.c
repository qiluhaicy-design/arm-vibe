// kernel/task.c - Task management for vibeOS

#include "task.h"
#include "../libs/uart.h"

// Current task
static Task *current_task = 0;

// Task list head
Task *task_list = 0;

// Initialize task system
void task_init() {
    uart_puts("Task system initialized\n");
}

// Create a new task
Task *create_task(void (*entry)(void), uint32_t *stack, uint32_t stack_size) {
    Task *task = (Task *)stack; // Use stack space for task struct
    task->stack_pointer = stack + stack_size - 1; // Top of stack
    task->entry_point = entry;
    task->next = 0;
    task->state = 0; // ready

    // Add to list
    if (!task_list) {
        task_list = task;
        task->next = task; // circular
    } else {
        task->next = task_list->next;
        task_list->next = task;
    }

    return task;
}

// Switch to task (placeholder, no context switch yet)
void switch_to_task(Task *task) {
    current_task = task;
    if (task->entry_point) {
        task->entry_point();
    }
}