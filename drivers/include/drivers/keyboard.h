#ifndef ILB_DRIVERS_KEYBOARD_H
#define ILB_DRIVERS_KEYBOARD_H

#include <stdint.h>

void kb_init(void);
int kb_poll_char(char* out);
void kb_on_scancode(uint8_t sc);

#endif
