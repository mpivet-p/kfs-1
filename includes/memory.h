#pragma once

# include <stdint.h>
# include "multiboot.h"

# define	KFS_DEBUG				0
# define	KFS_PM_BLOCK_SIZE		4096
# define	KFS_PM_MMAP_SIZE		32768

uint32_t	get_mem_max_addr(multiboot_info_t *mbd, uint32_t magic);
void		init_physical_memory(multiboot_info_t *mbd, uint32_t magic);

extern uint32_t	_pmmngr_map[KFS_PM_MMAP_SIZE];
extern uint32_t	_pmmngr_size;
extern uint32_t	_pmmngr_max_blocks;
extern uint32_t	_pmmngr_used_blocks;

static inline void		mmap_set(uint32_t bit)
{
	_pmmngr_map[bit / 32] |= (1 << (bit & 31));
}

static inline void		mmap_unset(uint32_t bit)
{
	_pmmngr_map[bit / 32] &= (1 << (bit & 31));
}

static inline uint8_t	mmap_test(uint32_t bit)
{
	return (_pmmngr_map[bit / 32] & (1 << (bit & 31)));
}

static inline uint32_t	pmmngr_free_blocks_count(void)
{
	return (_pmmngr_max_blocks - _pmmngr_used_blocks);
}
