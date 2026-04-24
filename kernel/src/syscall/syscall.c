#include "kernel/syscall.h"
#include "kernel/console.h"

#define MAX_SYSCALL 256
static syscall_handler_t g_handlers[MAX_SYSCALL];

static uint64_t sys_log(uint64_t ptr, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) {
    const char* s = (const char*)(uintptr_t)ptr;
    kconsole_write("syscall-log: ");
    kconsole_write(s);
    kconsole_write("\n");
    return 0;
}

void syscall_init(void) {
    for (unsigned i = 0; i < MAX_SYSCALL; ++i) g_handlers[i] = 0;
    syscall_register(1, sys_log);
    kconsole_write("syscall: table initialized\n");
}

void syscall_register(uint64_t nr, syscall_handler_t fn) {
    if (nr < MAX_SYSCALL) g_handlers[nr] = fn;
}

uint64_t syscall_dispatch(uint64_t nr, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5) {
    if (nr >= MAX_SYSCALL || !g_handlers[nr]) return (uint64_t)-1;
    return g_handlers[nr](a0,a1,a2,a3,a4,a5);
}
