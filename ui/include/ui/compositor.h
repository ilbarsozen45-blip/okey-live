#ifndef ILB_UI_COMPOSITOR_H
#define ILB_UI_COMPOSITOR_H

#include <stdint.h>

void ui_startup(void);
void ui_frame(void);
void ui_draw_taskbar(void);
void ui_draw_start_menu(int expanded);

#endif
