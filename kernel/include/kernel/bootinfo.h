#ifndef ILB_KERNEL_BOOTINFO_H
#define ILB_KERNEL_BOOTINFO_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint64_t framebuffer_base;
    uint32_t width;
    uint32_t height;
    uint32_t pixels_per_scanline;
    uint32_t bpp;
} ilb_framebuffer_t;

typedef struct {
    void* map;
    size_t map_size;
    size_t desc_size;
    uint32_t desc_version;
} ilb_memory_map_t;

typedef struct {
    ilb_framebuffer_t fb;
    ilb_memory_map_t mm;
    uint64_t rsdp;
} ilb_boot_info_t;

#endif
