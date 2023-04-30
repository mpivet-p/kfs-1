#include <stdint.h>
#include "string.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "printk.h"

void print(const char* data)
{
	term_write(data, strlen(data));
	update_cursor(terminal_column, terminal_row);
}

void kernel_main(void)
{
	int var;
	int varb;
	install_gdt();
	init_term();

	print("Hello 42!\nby mpivet-p");
	printk("\nTEST %d\n", 42);
	printk("var %p\n", &var);
	printk("var %p\n", &varb);
	printk("var %%%s\n", "FOO");
	printk("var %b\n", 0);
	printk("var %b\n", 1);
	printk("var %b\n", 2);
	printk("var %b\n", 3);
}
