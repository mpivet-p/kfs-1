#include <stddef.h>
#include <stdint.h>
#include "cursor.h"
#include "printk.h"
#include "term.h"

extern volatile uint8_t	in_read;
extern volatile char	read_key;

static void	backspace(size_t *i)
{
	if (*i > 0)
	{
		(*i)--;
		if (terminal_column == 0 && terminal_row != 0)
		{
			terminal_column = VGA_WIDTH - 1;
			terminal_row -= 1;
		}
		else
		{
			terminal_column -= 1;
		}
		update_cursor(terminal_column, terminal_row);
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
	}
}

int		readline(char *buf, size_t size)
{
	size_t	i = 0;
	while (i < size)
	{
		if (in_read == 1 && read_key != 0)
		{
			in_read = 0;
			if (read_key == '\n')
				return (i);
			if (read_key == '\b')
			{
				backspace(&i);
			}
			else if (read_key == '\t')
			{
				;
			}
			else
			{
				printk("%c", read_key);
				buf[i] = read_key;
				i++;
			}
			buf[i] = 0;
		}
	}
	return (i);
}
