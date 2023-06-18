#include <stdint.h>
#include <string.h>
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"
#include "memory.h"
#include "multiboot.h"

void		shell(void);

void	kernel_main(multiboot_info_t* mbd, uint32_t magic)
{
	char	str[] = "Hello World!\nby mpivet-p\n";

	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	init_physical_memory(mbd, magic);
	init_virtual_memory();
	printk(str);
	shell();
}
