#include <stdint.h>
#include "printk.h"

#define LOW_NIBBLE(x) x & 0x0F
#define HIGH_NIBBLE(x) (x >> 4) & 0x0F

struct stackframe
{
	struct stackframe	*ebp;
	uint32_t			eip;
}

void	print_stack(void)
{
	int b = 0x42424242;
	struct stackframe *stk;
	uint32_t	*ebp;
	uint32_t	*esp;
	uint32_t	*eip;

	asm ("movl %%ebp,%0" : "=r"(ebp));
	asm ("movl %%esp,%0" : "=r"(esp));
	while (*ebp != 0)
	{
		ebp = (uint32_t*)*ebp;
	}
	dump_stack(esp, ebp);
}

void	dump_stack(uint32_t *begin, uint32_t *end)
{
	uint8_t	*ptr = begin;
	char	conv[] = "0123456789abcdef";

	puts("Stack content:\n");
	while (ptr <= end)
	{
		if ((uint32_t)ptr % 8 == 0)
		{
			printk("%p:", ptr);
		}
		printk(" %c%c", conv[HIGH_NIBBLE(*ptr)], conv[LOW_NIBBLE(*ptr)]);
		if ((uint32_t)ptr % 8 == 7 || ptr == end)
		{
			puts("\n");
		}
		ptr++;
	}
}
