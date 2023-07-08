#include <stddef.h>
#include "memory.h"
//Remove
#include "printk.h"

static int32_t	mmap_get_first_free(void)
{
	for (size_t i = 0; i < _pmmngr_max_blocks / 32; i++)
	{
		if (_pmmngr_map[i] != 0xFFFFFFFF)
		{
			for (size_t block = i * 32; block < ((i + 1) * 32); block++)
			{
				if (!mmap_test(block))
					return (block);
			}
		}
	}
	return (-1);
}

static int32_t	mmap_get_free_consecutives(uint32_t n)
{
	uint32_t c = 0;
	uint32_t first_block;

	for (size_t i = 0; i < _pmmngr_max_blocks / 32; i++)
	{
		if (_pmmngr_map[i] != 0xFFFFFFFF)
		{
			for (size_t block = i * 32; block < (i + 1) * 32; block++)
			{
				if (!mmap_test(block))
				{
					c++;
					if (first_block == 0)
						first_block = block;
					if (c == n)
						return (first_block);
				}
				else
				{
					first_block = 0;
					c = 0;
				}
			}
		}
	}
	return (-1);
}

void	*pmmngr_alloc_blocks(uint32_t n)
{
	void	*physical_addr;
	int		frame;

	if (pmmngr_free_blocks_count() < n)
		return (0x0);

	if ((frame = mmap_get_free_consecutives(n)) == -1)
		return (0x0);

	physical_addr = (void*)(frame * KFS_PM_BLOCK_SIZE);
	for (size_t i = frame; i < frame + n; i++)
		mmap_set(i);
	_pmmngr_used_blocks += n;

	return (physical_addr);
}

void	*pmmngr_alloc_block(void)
{
	void	*physical_addr;
	int		frame;

	if (pmmngr_free_blocks_count() == 0)
		return (0x0);

	if ((frame = mmap_get_first_free()) == -1)
		return (0x0);

	mmap_set(frame);
	physical_addr = (void*)(frame * KFS_PM_BLOCK_SIZE);
	_pmmngr_used_blocks++;

	return (physical_addr);
}

void	pmmngr_free_block(void *block_paddr)
{
	uint32_t frame = (uint32_t)block_paddr / KFS_PM_BLOCK_SIZE;

	mmap_unset(frame);
	_pmmngr_used_blocks--;
}
