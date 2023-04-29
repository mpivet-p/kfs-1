#include <stdint.h>
#include <stdarg.h>
#include "printk.h"
#include "string.h"
#include "cursor.h"
#include "term.h"

static	int	get_flag(char c)
{
	int		ret = 0;

	switch (c)
	{
		case 's':
			ret = PRINTK_STR;
			break ;
		case 'p':
			ret = PRINTK_PTR;
			break ;
		case 'd':
			ret = PRINTK_INT;
			break ;
		case 'x':
			ret = PRINTK_HEX;
			break ;
	}
	return (ret);
}

static void	get_str(va_list *ap, char *buff)
{
	char *n = va_arg(*ap, char*);
	(void)n;
	buff[0] = 'S';
	buff[1] = 'T';
}

static void	get_ptr(va_list *ap, char *buff)
{
	void	*n = va_arg(*ap, void*);
	(void)n;
	buff[0] = 'P';
	buff[1] = 'T';
}

static void	get_int(va_list *ap, char *buff)
{
	int		n = va_arg(*ap, int);
	(void)n;
	buff[0] = '4';
	buff[1] = '2';
}

static void	get_hex(va_list *ap, char *buff)
{
	uint64_t	n = va_arg(*ap, uint64_t);
	(void)n;
	buff[0] = 'H';
	buff[1] = 'X';
}

static void	flush_printk_buff(char *buff, size_t *j)
{
	term_write(buff, *j);
	update_cursor(terminal_column, terminal_row);
	*j = 0;
}

static void	process_flag(va_list *ap, int flag, char *buff, size_t *j)
{
	static void (*fl[PRINTK_FLAGS_LEN])(va_list *ap, char *buff) = {0x0, get_str,
		get_ptr, get_int, get_hex};
	size_t	len;
	char	loc_buff[32];

	bzero(loc_buff, 32);
	fl[flag](ap, loc_buff);
	len = strlen(loc_buff);
	if (*j + len > PRINTK_BUFF_LEN)
	{
		flush_printk_buff(buff, j);
	}
	//strcat(buff + 1, loc_buff);
	*j += len;
}

int		printk(const char *restrict format, ...)
{
	va_list	ap;
	size_t	len = strlen(format);
	size_t	j = 0;
	char	buff[PRINTK_BUFF_LEN];
	int		flag;

	va_start(ap, format);
	for (size_t i = 0; i < len; i++)
	{
		if (format[i] == '%' && i + 1 < len)
		{
			if ((flag = get_flag(format[i + 1])))
			{
				process_flag(&ap, flag, buff, &j);
			}
			else if (format[i + 1] == '%')
				buff[j++] = '%';
			i++;
		}
		else
		{
			buff[j] = format[i];
			j++;
			buff[j] = 0;
		}
		//Need to add a check for j < PRINTK_BUFF_LEN
	}
	va_end(ap);
	flush_printk_buff(buff, &j);
	return (0);
}
