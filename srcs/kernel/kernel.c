#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "printk.h"



void kernel_main(void)
{
	install_gdt();
	install_idt();

	init_term();

	printk("Hello 42!\nby mpivet-p");
	__asm__ volatile ("int %0" : : "i"(3));
}
