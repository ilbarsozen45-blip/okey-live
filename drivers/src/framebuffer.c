#include "drivers/framebuffer.h"

static ilb_fb_t g_fb;

void fb_bind(ilb_fb_t fb) { g_fb = fb; }

void fb_fill_rect(int x, int y, int w, int h, uint32_t color) {
    if (!g_fb.ptr) return;
    for (int yy = 0; yy < h; ++yy) {
        int py = y + yy;
        if (py < 0 || py >= (int)g_fb.height) continue;
        for (int xx = 0; xx < w; ++xx) {
            int px = x + xx;
            if (px < 0 || px >= (int)g_fb.width) continue;
            g_fb.ptr[py * g_fb.stride + px] = color;
        }
    }
}

void fb_blit_rgba(const uint32_t* src, int sx, int sy, int sw, int sh, int dx, int dy) {
    for (int y = 0; y < sh; ++y)
        for (int x = 0; x < sw; ++x)
            g_fb.ptr[(dy + y) * g_fb.stride + (dx + x)] = src[(sy + y) * sw + (sx + x)];
}
