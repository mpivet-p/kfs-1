#include <stddef.h>
#include "memory.h"
//TMP
#include "printk.h"

uint32_t	_pmmngr_map[KFS_PM_MMAP_SIZE];
uint32_t	_pmmngr_size;
uint32_t	_pmmngr_max_blocks;
uint32_t	_pmmngr_used_blocks;

void	init_physical_memory(multiboot_info_t *mbd, uint32_t magic)
{
	_pmmngr_size = get_mem_max_addr(mbd, magic) ^ (KFS_PM_BLOCK_SIZE - 1);
	_pmmngr_used_blocks = 1024; //The first 4Mb of RAM are reserved for the kernel
	_pmmngr_max_blocks = _pmmngr_size / KFS_PM_BLOCK_SIZE;
	// We set the first 4Mb as reserved in the bitmap
	for (size_t i = 0; i < 32; i++)
		_pmmngr_map[i] = 0xFFFFFFFF;
	for (size_t i = 32; i < (_pmmngr_max_blocks / 32); i++)
	{
		_pmmngr_map[i] = 0;
	}

	// Uncomment to test
	//void *test = pmmngr_alloc_block();
	//printk("%p\n", test);
	//test = pmmngr_alloc_blocks(12);
	//printk("%p\n", test);
	//test = pmmngr_alloc_block();
	//printk("%p\n", test);
}
