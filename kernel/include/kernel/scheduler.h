#ifndef ILB_KERNEL_SCHEDULER_H
#define ILB_KERNEL_SCHEDULER_H

#include <stdint.h>

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_ZOMBIE,
} task_state_t;

typedef struct task {
    uint64_t pid;
    task_state_t state;
    uint64_t rsp;
    uint64_t rip;
    uint64_t quantum_ticks;
    const char* name;
} task_t;

void sched_init(void);
uint64_t sched_spawn(const char* name, void (*entry)(void));
void sched_tick(void);
void sched_yield(void);

#endif
