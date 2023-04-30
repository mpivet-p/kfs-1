#include "term.h"
#include "cursor.h"
#include "string.h"

void puts(const char* data)
{
	term_write(data, strlen(data));
	update_cursor(terminal_column, terminal_row);
}
