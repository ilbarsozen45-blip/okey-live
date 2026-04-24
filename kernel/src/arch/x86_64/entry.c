#include "kernel/bootinfo.h"
#include "kernel/console.h"
#include "kernel/paging.h"
#include "kernel/heap.h"
#include "kernel/interrupt.h"
#include "kernel/scheduler.h"
#include "kernel/syscall.h"

extern void ui_startup(void);
extern void apps_bootstrap(void);

void kernel_main(ilb_boot_info_t* boot_info) {
    kconsole_init(boot_info->fb.framebuffer_base,
                  boot_info->fb.width,
                  boot_info->fb.height,
                  boot_info->fb.pixels_per_scanline);

    kconsole_write("ILBARSDOWS kernel booting...\n");
    paging_init();
    kheap_init((void*)0x2000000, 64 * 1024 * 1024);
    idt_init();
    irq_install();
    syscall_init();
    sched_init();

    kconsole_write("Core subsystems up. Starting UI and apps...\n");
    ui_startup();
    apps_bootstrap();

    while (1) {
        sched_tick();
    }
}
