#include "kernel/console.h"
#include <stdarg.h>

static volatile uint32_t* g_fb;
static uint32_t g_w, g_h, g_ppsl;
static uint32_t g_x = 8, g_y = 8;

void kconsole_init(uint64_t fb_base, uint32_t w, uint32_t h, uint32_t ppsl) {
    g_fb = (volatile uint32_t*)(uintptr_t)fb_base;
    g_w = w;
    g_h = h;
    g_ppsl = ppsl;
}

static void draw_dot(uint32_t x, uint32_t y, uint32_t color) {
    if (!g_fb || x >= g_w || y >= g_h) return;
    g_fb[y * g_ppsl + x] = color;
}

void kconsole_putc(char c) {
    if (c == '\n') {
        g_x = 8;
        g_y += 12;
        return;
    }
    for (uint32_t yy = 0; yy < 8; ++yy)
        for (uint32_t xx = 0; xx < 6; ++xx)
            draw_dot(g_x + xx, g_y + yy, 0x00D0D0D0);
    g_x += 7;
    if (g_x + 7 > g_w) {
        g_x = 8;
        g_y += 12;
    }
}

void kconsole_write(const char* s) {
    while (*s) kconsole_putc(*s++);
}

static void print_uint(unsigned long long v, unsigned base) {
    char tmp[32];
    unsigned idx = 0;
    if (v == 0) {
        kconsole_putc('0');
        return;
    }
    while (v && idx < sizeof(tmp)) {
        unsigned d = (unsigned)(v % base);
        tmp[idx++] = d < 10 ? (char)('0' + d) : (char)('a' + d - 10);
        v /= base;
    }
    while (idx) kconsole_putc(tmp[--idx]);
}

void kconsole_printf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    for (const char* p = fmt; *p; ++p) {
        if (*p != '%') {
            kconsole_putc(*p);
            continue;
        }
        ++p;
        if (*p == 's') {
            const char* s = va_arg(ap, const char*);
            kconsole_write(s ? s : "(null)");
        } else if (*p == 'd' || *p == 'u') {
            unsigned v = va_arg(ap, unsigned);
            print_uint(v, 10);
        } else if (*p == 'x') {
            unsigned v = va_arg(ap, unsigned);
            print_uint(v, 16);
        } else if (*p == '%') {
            kconsole_putc('%');
        }
    }
    va_end(ap);
}
