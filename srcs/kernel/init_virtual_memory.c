#include <stddef.h>
#include "string.h"
#include "memory.h"
#include "printk.h"
#include "time.h"

pdirectory page_directory __attribute__((aligned(4096)));
ptable first_page_table __attribute__((aligned(4096)));

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
		ptable	*new_table = (ptable*)pmmngr_alloc_block();
		bzero(new_table, sizeof(ptable));
		page_directory.m_entries[i] = (uint32_t)(new_table) | (I86_PDE_WRITABLE | I86_PDE_PRESENT);
	}

	//Map the first 4Mb of physical memory to the first 4Mb of virtual Memory.
	for (size_t i = 0; i < 1024; i++)
	{
		first_page_table.m_entries[i] = (i * 0x1000) | (I86_PTE_WRITABLE | I86_PTE_PRESENT);
	}

	ptable	*pages =
		(ptable*)((uint32_t)(page_directory.m_entries[1]) & I86_PDE_FRAME);
	for (size_t i = 0; i < PAGES_PER_TABLE; i++)
	{
		pages->m_entries[i] = (uint32_t)((page_directory.m_entries[i]) & I86_PDE_FRAME) | (I86_PTE_WRITABLE | I86_PTE_PRESENT);
	}
	page_directory.m_entries[0] = (uint32_t)(&first_page_table) | (I86_PDE_WRITABLE | I86_PDE_PRESENT);

	load_page_dir(&page_directory);
	enable_paging();

	///char *a = vmalloc(1);
	///a[0] = 0;
	///void *b = vmalloc(4097);
	///void *c = kmalloc(13000);
	///printk("%p [%d] | %p [%d] | %p [%d]\n", a, vsize(a), b, vsize(b), c, vsize(c));
}
