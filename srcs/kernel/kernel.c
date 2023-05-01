#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"

void kernel_main(void)
{
	install_gdt();
	install_idt();
	install_irq();
    int divisor = 1193180;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor & 0xFF00) >> 8);
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	printk("Hello 42!\nby mpivet-p");
//	__asm__ volatile ("int %0" : : "i"(32));
//	__asm__ volatile ("int %0" : : "i"(33));
//	__asm__ volatile ("int %0" : : "i"(33));
}
