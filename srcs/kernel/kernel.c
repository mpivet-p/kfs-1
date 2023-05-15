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
void		print_stack(void);

void kernel_main(void)
{
	char	str[] = "Hello Worldb\n";
	int		nbr = 0x42430102;
	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	printk("Hello 42!\nby mpivet-p\n");
	print_stack();
	printk("nbr: %p\n", &nbr);
	printk("str: %p\n", &(str[0]));
	shell();
}
