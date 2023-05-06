#ifndef PRINTK_H
# define PRINTK_H

enum PRINTK_FLAGS
{
	PRINTK_NULL,
	PRINTK_STR,
	PRINTK_PTR,
	PRINTK_CHR,
	PRINTK_INT,
	PRINTK_HEX,
	PRINTK_BIN,
	PRINTK_FLAGS_LEN
};

# define PRINTK_BUFF_LEN	256

int		printk(const char *restrict format, ...);



#endif
