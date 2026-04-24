#include "kernel/scheduler.h"
#include "kernel/console.h"

#define MAX_TASKS 128
static task_t g_tasks[MAX_TASKS];
static uint64_t g_task_count;
static uint64_t g_current;

void sched_init(void) {
    g_task_count = 0;
    g_current = 0;
    kconsole_write("sched: round-robin initialized\n");
}

uint64_t sched_spawn(const char* name, void (*entry)(void)) {
    if (g_task_count >= MAX_TASKS) return 0;
    task_t* t = &g_tasks[g_task_count];
    t->pid = g_task_count + 1;
    t->state = TASK_READY;
    t->rip = (uint64_t)(uintptr_t)entry;
    t->rsp = 0;
    t->quantum_ticks = 4;
    t->name = name;
    ++g_task_count;
    return t->pid;
}

void sched_tick(void) {
    if (!g_task_count) return;
    g_current = (g_current + 1) % g_task_count;
    g_tasks[g_current].state = TASK_RUNNING;
}

void sched_yield(void) {
    sched_tick();
}
