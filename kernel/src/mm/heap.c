#include "kernel/heap.h"
#include "kernel/console.h"
#include <stdint.h>

typedef struct block {
    size_t size;
    int free;
    struct block* next;
} block_t;

static block_t* g_head;

void kheap_init(void* start, size_t size) {
    g_head = (block_t*)start;
    g_head->size = size - sizeof(block_t);
    g_head->free = 1;
    g_head->next = 0;
    kconsole_write("heap: initialized\n");
}

void* kmalloc(size_t size) {
    block_t* cur = g_head;
    while (cur) {
        if (cur->free && cur->size >= size) {
            if (cur->size > size + sizeof(block_t)) {
                block_t* n = (block_t*)((uint8_t*)(cur + 1) + size);
                n->size = cur->size - size - sizeof(block_t);
                n->free = 1;
                n->next = cur->next;
                cur->next = n;
                cur->size = size;
            }
            cur->free = 0;
            return (void*)(cur + 1);
        }
        cur = cur->next;
    }
    return 0;
}

void kfree(void* ptr) {
    if (!ptr) return;
    block_t* b = ((block_t*)ptr) - 1;
    b->free = 1;
}
