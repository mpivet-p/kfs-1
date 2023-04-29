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
	install_gdt();
	init_term();

	print("Hello 42!\nby mpivet-p");
	printk("\nTEST %s", 42);
}
