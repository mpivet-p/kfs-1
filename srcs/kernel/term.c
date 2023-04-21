#include "term.h"
#include "vga.h"

static void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

static void	term_putchar(char c)
{
	if (c == '\n')
	{
		terminal_row++;
		terminal_column = 0;
	}
	else
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		terminal_column++;
		if (terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			terminal_row++;
			if (terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
}

void	term_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		term_putchar(data[i]);
}
