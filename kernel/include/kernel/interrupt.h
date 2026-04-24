#ifndef ILB_KERNEL_INTERRUPT_H
#define ILB_KERNEL_INTERRUPT_H

#include <stdint.h>

void idt_init(void);
void irq_install(void);
void irq_ack(uint8_t irq);

#endif
