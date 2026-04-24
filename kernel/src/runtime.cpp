#include "kernel/console.h"

extern "C" void __cxa_pure_virtual(void) {
    kconsole_write("c++ runtime: pure virtual call\n");
    while (1) {}
}

class KernelBanner {
public:
    KernelBanner() { kconsole_write("c++ module: initialized\n"); }
};

static KernelBanner g_banner;
