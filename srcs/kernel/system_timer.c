#include "printk.h"
#include "term.h"
#include "io.h"

uint16_t	timer_ticks = 0;

void	timer_handler(regs_t *re)
{
	timer_ticks++;
	(void)re;
	puts("tick!\n");
	if (timer_ticks % 18 == 0)
	{
		printk("%ds Elapsed since startup\n", timer_ticks / 18);
	}
}
