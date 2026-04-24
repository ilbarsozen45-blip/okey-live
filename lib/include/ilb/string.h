#ifndef ILB_STRING_H
#define ILB_STRING_H

#include <stddef.h>

size_t ilb_strlen(const char* s);
int ilb_strncmp(const char* a, const char* b, size_t n);
char* ilb_strncpy(char* dst, const char* src, size_t n);
void* ilb_memcpy(void* dst, const void* src, size_t n);
void* ilb_memset(void* dst, int c, size_t n);

#endif
