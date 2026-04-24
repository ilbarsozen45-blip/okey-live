#ifndef ILB_KERNEL_SYSCALL_H
#define ILB_KERNEL_SYSCALL_H

#include <stdint.h>

typedef uint64_t (*syscall_handler_t)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

void syscall_init(void);
void syscall_register(uint64_t nr, syscall_handler_t fn);
uint64_t syscall_dispatch(uint64_t nr, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);

#endif
