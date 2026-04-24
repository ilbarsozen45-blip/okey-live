#include "ui/window.h"
#include "drivers/framebuffer.h"

static int inside_rounded_rect(int px, int py, const ui_window_t* w) {
    int r = w->radius;
    if (px >= w->x + r && px < w->x + w->w - r) return 1;
    if (py >= w->y + r && py < w->y + w->h - r) return 1;

    int cx = (px < w->x + r) ? w->x + r : w->x + w->w - r - 1;
    int cy = (py < w->y + r) ? w->y + r : w->y + w->h - r - 1;
    int dx = px - cx;
    int dy = py - cy;
    return dx*dx + dy*dy <= r*r;
}

void ui_window_draw(const ui_window_t* w) {
    for (int y = w->y; y < w->y + w->h; ++y) {
        for (int x = w->x; x < w->x + w->w; ++x) {
            if (inside_rounded_rect(x, y, w)) {
                fb_fill_rect(x, y, 1, 1, w->bg);
            }
        }
    }
    fb_fill_rect(w->x, w->y, w->w, 36, 0x303744);
}
