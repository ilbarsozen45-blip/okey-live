#include "drivers/keyboard.h"

#define KB_BUF 256
static char g_buf[KB_BUF];
static int g_r, g_w;

void kb_init(void) { g_r = g_w = 0; }

static char sc_to_ascii(uint8_t sc) {
    static const char map[128] = {
        [0x1E]='a',[0x30]='b',[0x2E]='c',[0x20]='d',[0x12]='e',[0x21]='f',[0x22]='g',
        [0x23]='h',[0x17]='i',[0x24]='j',[0x25]='k',[0x26]='l',[0x32]='m',[0x31]='n',
        [0x18]='o',[0x19]='p',[0x10]='q',[0x13]='r',[0x1F]='s',[0x14]='t',[0x16]='u',
        [0x2F]='v',[0x11]='w',[0x2D]='x',[0x15]='y',[0x2C]='z',[0x39]=' '
    };
    return map[sc & 0x7F];
}

void kb_on_scancode(uint8_t sc) {
    if (sc & 0x80) return;
    char c = sc_to_ascii(sc);
    if (!c) return;
    int n = (g_w + 1) % KB_BUF;
    if (n == g_r) return;
    g_buf[g_w] = c;
    g_w = n;
}

int kb_poll_char(char* out) {
    if (g_r == g_w) return 0;
    *out = g_buf[g_r];
    g_r = (g_r + 1) % KB_BUF;
    return 1;
}
