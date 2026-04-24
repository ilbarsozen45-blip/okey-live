#include "bootloader.h"

typedef struct {
    unsigned char ident[16];
    UINT16 type;
    UINT16 machine;
    UINT32 version;
    UINT64 entry;
    UINT64 phoff;
    UINT64 shoff;
    UINT32 flags;
    UINT16 ehsize;
    UINT16 phentsize;
    UINT16 phnum;
} Elf64Header;

typedef struct {
    UINT32 type;
    UINT32 flags;
    UINT64 offset;
    UINT64 vaddr;
    UINT64 paddr;
    UINT64 filesz;
    UINT64 memsz;
    UINT64 align;
} Elf64ProgramHeader;

EFI_STATUS ilb_load_kernel(EFI_HANDLE image, EFI_SYSTEM_TABLE* st, VOID** entry, VOID** image_base, UINTN* image_size) {
    EFI_LOADED_IMAGE* loaded_image;
    EFI_GUID loaded_image_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_GUID fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
    EFI_FILE_PROTOCOL* root;
    EFI_FILE_PROTOCOL* kernel;

    EFI_STATUS status = uefi_call_wrapper(BS->HandleProtocol, 3, image, &loaded_image_guid, (VOID**)&loaded_image);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(BS->HandleProtocol, 3, loaded_image->DeviceHandle, &fs_guid, (VOID**)&fs);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(fs->OpenVolume, 2, fs, &root);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(root->Open, 5, root, &kernel, L"kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status)) return status;

    UINTN file_info_size = SIZE_OF_EFI_FILE_INFO + 256;
    EFI_FILE_INFO* file_info;
    status = uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, file_info_size, (VOID**)&file_info);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(kernel->GetInfo, 4, kernel, &GenericFileInfo, &file_info_size, file_info);
    if (EFI_ERROR(status)) return status;

    UINTN kernel_size = file_info->FileSize;
    VOID* kernel_buffer;
    status = uefi_call_wrapper(BS->AllocatePool, 3, EfiLoaderData, kernel_size, &kernel_buffer);
    if (EFI_ERROR(status)) return status;

    status = uefi_call_wrapper(kernel->Read, 3, kernel, &kernel_size, kernel_buffer);
    if (EFI_ERROR(status)) return status;

    Elf64Header* ehdr = (Elf64Header*)kernel_buffer;
    if (!(ehdr->ident[0] == 0x7F && ehdr->ident[1] == 'E' && ehdr->ident[2] == 'L' && ehdr->ident[3] == 'F')) {
        return EFI_LOAD_ERROR;
    }

    EFI_PHYSICAL_ADDRESS first = 0xFFFFFFFFFFFFFFFFULL;
    EFI_PHYSICAL_ADDRESS last = 0;
    Elf64ProgramHeader* phdrs = (Elf64ProgramHeader*)((char*)kernel_buffer + ehdr->phoff);

    for (UINT16 i = 0; i < ehdr->phnum; ++i) {
        if (phdrs[i].type != 1) continue;
        if (phdrs[i].paddr < first) first = phdrs[i].paddr;
        if (phdrs[i].paddr + phdrs[i].memsz > last) last = phdrs[i].paddr + phdrs[i].memsz;
    }

    UINTN total_pages = (last - first + 0xFFF) / 0x1000;
    EFI_PHYSICAL_ADDRESS load_addr = first;
    status = uefi_call_wrapper(BS->AllocatePages, 4, AllocateAddress, EfiLoaderData, total_pages, &load_addr);
    if (EFI_ERROR(status)) return status;

    for (UINT16 i = 0; i < ehdr->phnum; ++i) {
        if (phdrs[i].type != 1) continue;
        CopyMem((VOID*)(UINTN)phdrs[i].paddr, (char*)kernel_buffer + phdrs[i].offset, phdrs[i].filesz);
        SetMem((VOID*)(UINTN)(phdrs[i].paddr + phdrs[i].filesz), phdrs[i].memsz - phdrs[i].filesz, 0);
    }

    *entry = (VOID*)(UINTN)ehdr->entry;
    *image_base = (VOID*)(UINTN)first;
    *image_size = (UINTN)(last - first);
    return EFI_SUCCESS;
}
