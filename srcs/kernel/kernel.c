#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"

uint32_t sleep(uint32_t seconds);

void kernel_main(void)
{
	install_gdt();
	install_idt();
	install_irq();
//    int divisor = 1193180 / 18;
//    outb(0x43, 0x36);
//    outb(0x40, divisor & 0xFF);
//    outb(0x40, (divisor & 0xFF00) >> 8);
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	//outb(0x64, 0xF2);
	//printk("0x%x\n", inb(0x60));
	printk("Hello 42!\nby mpivet-p\n");
	sleep(2);
	printk("Done!\n");
	while (1);;
}
