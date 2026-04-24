#include "kernel/paging.h"
#include "kernel/console.h"

#define MAX_FRAMES 16384
static uint64_t frame_bitmap[MAX_FRAMES / 64];
static uint64_t g_next_frame = 0x100000;

void paging_init(void) {
    for (unsigned i = 0; i < MAX_FRAMES / 64; ++i) frame_bitmap[i] = 0;
    kconsole_write("paging: initialized frame allocator\n");
}

uint64_t paging_alloc_frame(void) {
    uint64_t frame = g_next_frame;
    g_next_frame += 0x1000;
    return frame;
}

void paging_map_page(uint64_t virt, uint64_t phys, uint64_t flags) {
    (void)virt; (void)phys; (void)flags;
}
