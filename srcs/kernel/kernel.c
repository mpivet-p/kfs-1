#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "string.h"
#include "vga.h"
#include "io.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"

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
}
