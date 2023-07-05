#include <stddef.h>
#include "printk.h"
#include "memory.h"

extern uint32_t	_pmmngr_map[KFS_PM_MMAP_SIZE];
extern uint32_t	_pmmngr_size;

static size_t	count_positive_bits(uint32_t m, size_t begin, size_t len)
{
	size_t	c = 0;

	for (size_t i = begin; i < len; i++)
	{
		c += (m >> i) & 0x1;
	}
	return (c);
}

void	print_physical_memory(void)
{
	size_t pp_char = _pmmngr_size / PAGE_SIZE / 1600 + 1;
	size_t cur_page = 0;
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 80; j++)
		{
			size_t t = 0;
			for (size_t c = 0; c < pp_char; c += 32)
			{
				t += count_positive_bits(_pmmngr_map[(cur_page + c) / 32], ((cur_page + c) % 32), (pp_char - cur_page) % 32);
				printk("[%d | %d | %d] ", (cur_page + c)/32, (cur_page + c)%32, (pp_char - cur_page) % 32);
			}
			cur_page += pp_char;
		}
		return ;
	}
}
