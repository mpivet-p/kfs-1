#pragma once

# include <stdint.h>
# include "multiboot.h"

# define	KFS_DEBUG				0
# define	KFS_PM_BLOCK_SIZE		4096

uint32_t	get_mem_max_addr(multiboot_info_t *mbd, uint32_t magic);

static uint32_t	_pmmngr_map[32768];
static uint32_t	_pmmngr_size;
static uint32_t	_pmmngr_max_blocks;
static uint32_t	_pmmngr_used_blocks;

inline void		mmap_set(uint32_t bit)
{
	_pmmngr_map[bit / 32] |= (1 << (bit & 31));
}

inline void		mmap_unset(uint32_t bit)
{
	_pmmngr_map[bit / 32] &= (1 << (bit & 31));
}

inline uint8_t	mmap_test(uint32_t bit)
{
	return (_pmmngr_map[bit / 32] & (1 << (bit & 31)));
}
