#include <stddef.h>
#include "printk.h"
#include "memory.h"

#define MAX_MAP_HEIGHT	8
#define MAX_MAP_WIDTH	80

extern uint32_t	_pmmngr_map[KFS_PM_MMAP_SIZE];
extern uint32_t	_pmmngr_max_blocks;

static size_t	count_positive_bits(uint32_t m)
{
	size_t	c = 0;

	for (size_t i = 0; i < 32; i++)
	{
		c += m & (0x1 << i);
	}
	return (c);
}

void	print_physical_memory(void)
{
	size_t	pp_char = _pmmngr_max_blocks / (MAX_MAP_HEIGHT * MAX_MAP_WIDTH) + 1;
	size_t	cur_page = 0;

	pp_char += 32 - (pp_char % 32);
	printk("1 char is equivalent to %d physical memory blocks (%d blocks in total)."\
		"\n`.` = 0%% | `*` < 50%% | `#` >= 50%%\n", pp_char, _pmmngr_max_blocks);
	for (size_t i = 0; i < MAX_MAP_HEIGHT; i++)
	{
		for (size_t j = 0; j < MAX_MAP_WIDTH; j++)
		{
			size_t t = 0;
			for (size_t c = 0; c < pp_char; c += 32)
			{
				t += count_positive_bits(_pmmngr_map[(cur_page + c) / 32]);
				cur_page += 32;
			}
			if (t == 0)
				puts(".");
			else if (t < (pp_char / 2))
				puts("*");
			else
				puts("#");
			if (cur_page >= _pmmngr_max_blocks)
			{
				puts("\n");
				return ;
			}
		}
	}
}
