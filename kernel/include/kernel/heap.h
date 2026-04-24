#ifndef ILB_KERNEL_HEAP_H
#define ILB_KERNEL_HEAP_H

#include <stddef.h>

void kheap_init(void* start, size_t size);
void* kmalloc(size_t size);
void kfree(void* ptr);

#endif
