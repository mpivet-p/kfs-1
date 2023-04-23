#include "term.h"
#include "vga.h"

static void	terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

static void shift_terminal_content(void)
{
	for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[index + VGA_WIDTH];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
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
		if (terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			terminal_row++;
		}
	}
	if (terminal_row == VGA_HEIGHT)
	{
		shift_terminal_content();
		terminal_row--;
	}
}

void	term_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		term_putchar(data[i]);
}
