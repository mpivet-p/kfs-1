#include <stdint.h>
#include "printk.h"
#include "term.h"

#define LOW_NIBBLE(x) x & 0x0F
#define HIGH_NIBBLE(x) (x >> 4) & 0x0F

struct stackframe
{
	struct stackframe	*ebp;
	uint32_t			eip;
};

void	dump_stack(uint32_t *begin, uint32_t *end)
{
	uint32_t	i = 0;
	uint8_t		*ptr = (uint8_t*)begin;
	char		conv[] = "0123456789abcdef";

	puts("Stack content:\n");
	while ((uint32_t*)ptr <= end)
	{
		if (i % 8 == 0)
		{
			printk("%p:", ptr);
		}
		printk(" %c%c", conv[HIGH_NIBBLE(*ptr)], conv[LOW_NIBBLE(*ptr)]);
		if (i % 8 == 7 || (uint32_t)ptr == (uint32_t)end)
		{
			puts("\n");
		}
		ptr++;
		i++;
	}
	puts("\n");
}

void	print_stack(uint8_t dump)
{
	struct stackframe *stk;
	uint32_t	*ebp;
	uint32_t	*esp;

	asm ("movl %%ebp,%0" : "=r"(stk));
	asm ("movl %%ebp,%0" : "=r"(ebp));
	asm ("movl %%esp,%0" : "=r"(esp));
	printk("Stack Trace:\n");
	while (stk)
	{
		printk("<0x%x> at ?\n", stk->eip - 5);
		ebp = (uint32_t*)stk;
		stk = stk->ebp;
	}
	puts("\n");
	if (dump == 0)
		dump_stack(esp, ebp);
}
