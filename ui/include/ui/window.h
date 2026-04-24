#ifndef ILB_UI_WINDOW_H
#define ILB_UI_WINDOW_H

#include <stdint.h>

typedef struct {
    int x, y, w, h;
    uint32_t bg;
    int radius;
    const char* title;
} ui_window_t;

void ui_window_draw(const ui_window_t* window);

#endif
