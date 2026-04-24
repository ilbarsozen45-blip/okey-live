#include "ui/compositor.h"
#include "ui/window.h"
#include "drivers/framebuffer.h"

static int g_tick;

static uint32_t blend(uint32_t c0, uint32_t c1, float t) {
    uint8_t r0 = (c0 >> 16) & 0xFF, g0 = (c0 >> 8) & 0xFF, b0 = c0 & 0xFF;
    uint8_t r1 = (c1 >> 16) & 0xFF, g1 = (c1 >> 8) & 0xFF, b1 = c1 & 0xFF;
    uint8_t r = (uint8_t)(r0 + (r1 - r0) * t);
    uint8_t g = (uint8_t)(g0 + (g1 - g0) * t);
    uint8_t b = (uint8_t)(b0 + (b1 - b0) * t);
    return (r << 16) | (g << 8) | b;
}

void ui_draw_taskbar(void) {
    fb_fill_rect(0, 1020, 1920, 60, 0x181818);
    fb_fill_rect(760, 1032, 400, 36, 0x242424);
}

void ui_draw_start_menu(int expanded) {
    if (!expanded) return;
    fb_fill_rect(560, 420, 800, 560, 0x202020);
    for (int i = 0; i < 24; ++i) {
        int x = 600 + (i % 6) * 110;
        int y = 500 + (i / 6) * 90;
        fb_fill_rect(x, y, 84, 72, 0x2A2A2A);
    }
}

void ui_frame(void) {
    ++g_tick;
    for (int y = 0; y < 1020; ++y) {
        float t = (float)y / 1020.0f;
        uint32_t row = blend(0x0E1117, 0x1A1F2B, t);
        fb_fill_rect(0, y, 1920, 1, row);
    }

    ui_window_t explorer = {240, 120, 760, 640, 0x222831, 12, "Dosya Gezgini"};
    ui_window_t settings = {1040, 190, 620, 520, 0x24242B, 12, "Ayarlar"};
    ui_window_draw(&explorer);
    ui_window_draw(&settings);
    ui_draw_taskbar();
    ui_draw_start_menu((g_tick / 180) % 2);
}

void ui_startup(void) {
    g_tick = 0;
    ui_frame();
}
