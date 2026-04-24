#include "fs/ilbfs.h"
#include <string.h>

#define MAX_FILES 128
#define MAX_NAME 64

typedef struct {
    char name[MAX_NAME];
    uint8_t data[4096];
    size_t len;
    int used;
} memfile_t;

static memfile_t g_files[MAX_FILES];

int ilbfs_mount(void* device_ctx) {
    (void)device_ctx;
    memset(g_files, 0, sizeof(g_files));
    return 0;
}

static int find_slot(const char* path, int create) {
    for (int i = 0; i < MAX_FILES; ++i) {
        if (g_files[i].used && strcmp(g_files[i].name, path) == 0) return i;
    }
    if (!create) return -1;
    for (int i = 0; i < MAX_FILES; ++i) {
        if (!g_files[i].used) {
            g_files[i].used = 1;
            strncpy(g_files[i].name, path, MAX_NAME - 1);
            return i;
        }
    }
    return -1;
}

int ilbfs_read(const char* path, void* out, size_t max_len) {
    int idx = find_slot(path, 0);
    if (idx < 0) return -1;
    size_t n = g_files[idx].len < max_len ? g_files[idx].len : max_len;
    memcpy(out, g_files[idx].data, n);
    return (int)n;
}

int ilbfs_write(const char* path, const void* in, size_t len) {
    int idx = find_slot(path, 1);
    if (idx < 0) return -1;
    if (len > sizeof(g_files[idx].data)) len = sizeof(g_files[idx].data);
    memcpy(g_files[idx].data, in, len);
    g_files[idx].len = len;
    return (int)len;
}
