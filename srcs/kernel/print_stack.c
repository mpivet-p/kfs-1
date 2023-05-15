#include <stdint.h>
#include "printk.h"

void	print_stack(void)
{
	int b = 0x42424242;
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

	printk("Stack content:");
	while (ptr <= end)
	{
		printk(" %x", *ptr);
		ptr++;
	}
	printk("\n");
}
