#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"

#define TERM_BUFF	255

void kernel_main(void)
{
	char	buf[TERM_BUFF + 1];
	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	printk("Hello 42!\nby mpivet-p\n");
	while (1)
	{
		printk("%d\n", readline(&buf, TERM_BUFF));
	}
}
