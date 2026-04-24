#include "bootloader.h"

EFI_STATUS ilb_set_graphics_mode(IlbFramebuffer* fb) {
    EFI_STATUS status;
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;

    status = uefi_call_wrapper(BS->LocateProtocol, 3, &gop_guid, NULL, (VOID**)&gop);
    if (EFI_ERROR(status)) return status;

    UINTN best_mode = gop->Mode->Mode;
    UINTN best_area = 0;
    for (UINTN mode = 0; mode < gop->Mode->MaxMode; ++mode) {
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
        UINTN info_size = 0;
        if (EFI_ERROR(uefi_call_wrapper(gop->QueryMode, 4, gop, mode, &info_size, &info))) continue;
        UINTN area = info->HorizontalResolution * info->VerticalResolution;
        if (area > best_area) {
            best_area = area;
            best_mode = mode;
        }
    }

    status = uefi_call_wrapper(gop->SetMode, 2, gop, best_mode);
    if (EFI_ERROR(status)) return status;

    fb->framebuffer_base = gop->Mode->FrameBufferBase;
    fb->width = gop->Mode->Info->HorizontalResolution;
    fb->height = gop->Mode->Info->VerticalResolution;
    fb->pixels_per_scanline = gop->Mode->Info->PixelsPerScanLine;
    fb->bpp = 32;

    return EFI_SUCCESS;
}
