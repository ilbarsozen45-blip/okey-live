#ifndef ILB_BOOTLOADER_H
#define ILB_BOOTLOADER_H

#include <efi.h>
#include <efilib.h>

typedef struct {
    UINT64 framebuffer_base;
    UINT32 width;
    UINT32 height;
    UINT32 pixels_per_scanline;
    UINT32 bpp;
} IlbFramebuffer;

typedef struct {
    EFI_MEMORY_DESCRIPTOR* map;
    UINTN map_size;
    UINTN desc_size;
    UINT32 desc_version;
} IlbMemoryMap;

typedef struct {
    IlbFramebuffer fb;
    IlbMemoryMap mm;
    EFI_PHYSICAL_ADDRESS rsdp;
} IlbBootInfo;

EFI_STATUS ilb_set_graphics_mode(IlbFramebuffer* fb);
EFI_STATUS ilb_load_kernel(EFI_HANDLE image, EFI_SYSTEM_TABLE* st, VOID** entry, VOID** image_base, UINTN* image_size);
EFI_STATUS ilb_capture_memory_map(IlbMemoryMap* mm);

#endif
