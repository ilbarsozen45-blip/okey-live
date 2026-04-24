#ifndef ILB_KERNEL_PAGING_H
#define ILB_KERNEL_PAGING_H

#include <stdint.h>

void paging_init(void);
void paging_map_page(uint64_t virt, uint64_t phys, uint64_t flags);
uint64_t paging_alloc_frame(void);

#endif
