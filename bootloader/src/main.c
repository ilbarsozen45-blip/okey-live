#include "bootloader.h"

typedef void (*KernelEntry)(IlbBootInfo* boot_info);

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE* st) {
    InitializeLib(image, st);

    IlbBootInfo info;
    ZeroMem(&info, sizeof(info));

    EFI_STATUS status = ilb_set_graphics_mode(&info.fb);
    if (EFI_ERROR(status)) {
        Print(L"[ILBARSDOWS] GOP setup failed: %r\n", status);
        return status;
    }

    VOID* entry = NULL;
    VOID* image_base = NULL;
    UINTN image_size = 0;
    status = ilb_load_kernel(image, st, &entry, &image_base, &image_size);
    if (EFI_ERROR(status)) {
        Print(L"[ILBARSDOWS] Kernel load failed: %r\n", status);
        return status;
    }

    status = ilb_capture_memory_map(&info.mm);
    if (EFI_ERROR(status)) {
        Print(L"[ILBARSDOWS] Memory map failed: %r\n", status);
        return status;
    }

    KernelEntry kernel = (KernelEntry)entry;
    kernel(&info);

    return EFI_SUCCESS;
}
