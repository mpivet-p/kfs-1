#include <stddef.h>
#include "memory.h"

pdirectory page_directory __attribute__((aligned(4096)));
ptable first_page_table __attribute__((aligned(4096)));
//uint32_t	page_directory[1024] __attribute__((aligned(4096)));
//uint32_t	first_page_table[1024] __attribute__((aligned(4096)));

extern void load_page_dir(pdirectory *dir);
extern void enable_paging();

pdirectory *get_page_directory(void)
{
	return (&page_directory);
}

void	init_virtual_memory(void)
{
	//Initializing page_directory with ring 0, read/write and present = 0
	for (size_t i = 0; i < 1024; i++)
	{
		page_directory.m_entries[i] = I86_PDE_WRITABLE;
	}

	//Map the first 4Mb of physical memory to the first 4Mb of virtual Memory.
	for (size_t i = 0; i < 1024; i++)
	{
		first_page_table.m_entries[i] = (i * 0x1000) | (I86_PTE_WRITABLE | I86_PTE_PRESENT);
	}
	page_directory.m_entries[0] = (uint32_t)(&first_page_table) | (I86_PDE_WRITABLE | I86_PDE_PRESENT);

	load_page_dir(&page_directory);
	enable_paging();

	// Uncomment to trigger page fault exception
	//char *blob = 0x500000;
	//blob[0] = 'a';
	void *a = vmalloc(1);
	void *b = vmalloc(4097);
	//void *c = vmalloc(4096);
	printk("%p\n", a);
}
