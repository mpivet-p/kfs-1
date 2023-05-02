#include "printk.h"
#include "term.h"
#include "io.h"

volatile uint32_t	timer_ticks = 0;

void	timer_handler(regs_t *re)
{
	timer_ticks++;
	(void)re;
	if (timer_ticks % 180 == 0)
	{
		printk("%ds Elapsed since startup\n", timer_ticks / 18);
	}
}

uint32_t	sleep(uint32_t seconds)
{
	uint64_t	time_target = (uint64_t)timer_ticks + (uint64_t)seconds * 18;

	while (timer_ticks < time_target);
}
