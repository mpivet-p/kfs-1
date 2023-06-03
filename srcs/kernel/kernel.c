#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"
#include "stack.h"

//#pragma GCC optimize ("O0")

void		shell(void);

void kernel_main(void)
{
	char	str[] = "Hello World!\nby mpivet-p\n";
	/*
	** Uncomment this and the pragma above to test the stack dump
	** int		nbr = 0x42430102;
	*/

	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	printk(str);
	print_stack(0);
	shell();
}
