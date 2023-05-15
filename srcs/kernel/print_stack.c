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
	while (ebp != 0)
	{
		eip = ebp + 1;
		printk("eip: 0x%x\n", eip);
		printk("ebp: ox%x\n",  ebp);
		printk("*ebp: ox%x\n",  *ebp);
		printk("esp: ox%x\n",  esp);

		dump_stack(ebp);
		ebp = (uint32_t*)*ebp;
	}
}

void	dump_stack(uint32_t *ebp)
{
	uint8_t* ptr = ebp + 2;

	printk("Stack content:");
	while (ebp >= ptr)
	{
		printk(" %x", *ptr);
		ebp--;
	}
	printk("\n");
}
