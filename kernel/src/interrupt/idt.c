#include "kernel/interrupt.h"
#include "kernel/console.h"

void idt_init(void) {
    kconsole_write("interrupt: idt initialized\n");
}

void irq_install(void) {
    kconsole_write("interrupt: irq handlers installed\n");
}

void irq_ack(uint8_t irq) {
    (void)irq;
}
