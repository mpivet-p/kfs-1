#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"

//#pragma GCC optimize ("O0")
uint32_t	sleep(uint32_t seconds);
void		shell(void);

void kernel_main(void)
{
	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	printk("Hello 42!\nby mpivet-p\n");
	sleep(4);
	shell();
}
