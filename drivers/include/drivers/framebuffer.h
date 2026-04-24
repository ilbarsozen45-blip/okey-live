#ifndef ILB_DRIVERS_FB_H
#define ILB_DRIVERS_FB_H

#include <stdint.h>

typedef struct {
    uint32_t* ptr;
    uint32_t width;
    uint32_t height;
    uint32_t stride;
} ilb_fb_t;

void fb_bind(ilb_fb_t fb);
void fb_fill_rect(int x, int y, int w, int h, uint32_t color);
void fb_blit_rgba(const uint32_t* src, int sx, int sy, int sw, int sh, int dx, int dy);

#endif
