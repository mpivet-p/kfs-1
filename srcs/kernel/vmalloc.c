#include <stddef.h>
#include "string.h"
#include "memory.h"

static virtual_addr get_available_page_table(void)
{
	pdirectory *p = get_page_directory();

	for (size_t i = 0; i < PAGES_PER_DIR; i++)
	{
		if ((p->m_entries[i] & I86_PDE_PRESENT) != I86_PDE_PRESENT)
		{
			return ((virtual_addr)(i * PAGES_PER_TABLE * PAGE_SIZE));
		}
	}
	return (0);
}

static virtual_addr	get_available_virtual_addr(void)
{
	pdirectory *p = get_page_directory();

	for (size_t i = 0; i < PAGES_PER_DIR; i++)
	{
		if ((p->m_entries[i] & I86_PDE_PRESENT) == I86_PDE_PRESENT)
		{
			ptable *table = p->m_entries[i] & I86_PDE_FRAME;
			for (size_t j = 0; j < PAGES_PER_TABLE; j++)
			{
				if ((table->m_entries[j] & I86_PTE_PRESENT) != I86_PTE_PRESENT)
				{
					return ((virtual_addr)(i * PAGES_PER_TABLE + j * PAGE_SIZE));
				}
			}
		}
	}
	return (get_available_page_table());
}

void	*vmalloc(uint32_t size)
{
	// Going crappy mode, just allocating a new page for every call
	if (size != 0 && size <= PAGE_SIZE)
	{
		physical_addr paddr = (physical_addr)pmmngr_alloc_block();
		if (!paddr)
			return (NULL);

		virtual_addr vaddr = get_available_virtual_addr();
		if (vaddr == 0)
			return (NULL);
		printk("%x %x\n", vaddr, paddr);
		vmmngr_map_page((void*)paddr, (void*)vaddr);
		return ((void*)vaddr);
	}
	return (NULL);
}
