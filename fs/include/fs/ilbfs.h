#ifndef ILB_FS_ILBFS_H
#define ILB_FS_ILBFS_H

#include <stdint.h>
#include <stddef.h>

#define ILBFS_MAGIC 0x494C4246537631ULL

typedef struct {
    uint64_t magic;
    uint32_t block_size;
    uint32_t inode_count;
    uint32_t data_block_count;
    uint32_t root_inode;
} ilbfs_superblock_t;

int ilbfs_mount(void* device_ctx);
int ilbfs_read(const char* path, void* out, size_t max_len);
int ilbfs_write(const char* path, const void* in, size_t len);

#endif
