#ifndef ILB_KERNEL_CONSOLE_H
#define ILB_KERNEL_CONSOLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void kconsole_init(uint64_t fb_base, uint32_t w, uint32_t h, uint32_t ppsl);
void kconsole_putc(char c);
void kconsole_write(const char* s);
void kconsole_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
