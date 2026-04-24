#include "bootloader.h"

EFI_STATUS ilb_capture_memory_map(IlbMemoryMap* mm) {
    UINTN map_key;
    UINTN map_size = 0;
    UINTN desc_size = 0;
    UINT32 desc_version = 0;
    EFI_STATUS status;

    status = uefi_call_wrapper(BS->GetMemoryMap, 5, &map_size, NULL, &map_key, &desc_size, &desc_version);
    if (status != EFI_BUFFER_TOO_SMALL) return status;

    map_size += desc_size * 8;
    EFI_MEMORY_DESCRIPTOR* map = NULL;
    status = uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, map_size, (VOID**)&map);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(BS->GetMemoryMap, 5, &map_size, map, &map_key, &desc_size, &desc_version);
    if (EFI_ERROR(status)) return status;

    mm->map = map;
    mm->map_size = map_size;
    mm->desc_size = desc_size;
    mm->desc_version = desc_version;
    return EFI_SUCCESS;
}
