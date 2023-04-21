#ifndef TERM_H
# define TERM_H

# include <stdint.h>
# include <stddef.h>

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;


void	init_term(void);
void	term_write(const char* data, size_t size);

static inline void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

#endif
