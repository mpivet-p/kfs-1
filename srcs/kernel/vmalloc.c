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

static virtual_addr	get_available_virtual_addr(size_t nbr)
{
	virtual_addr	vaddr;
	pdirectory		*p = get_page_directory();
	size_t			count = 0;

	for (size_t i = 0; i < PAGES_PER_DIR; i++)
	{
		if ((p->m_entries[i] & I86_PDE_PRESENT) == I86_PDE_PRESENT)
		{
			ptable *table = (uint32_t)(p->m_entries[i]) & I86_PDE_FRAME;
			for (size_t j = 0; j < PAGES_PER_TABLE; j++)
			{
				if ((table->m_entries[j] & I86_PTE_PRESENT) != I86_PTE_PRESENT)
				{
					if (count == 0)
						vaddr = (virtual_addr)(i * PAGES_PER_TABLE * PAGE_SIZE + j * PAGE_SIZE);
					count++;
					if (count == nbr)
						return (vaddr);
				}
				else
				{
					count = 0;
				}
			}
		}
		else
		{
			count = 0;
		}
	}
	return (get_available_page_table());
}

void	*vmalloc(uint32_t size)
{
	size_t	pages_needed = (size / PAGE_SIZE) + ((size % PAGE_SIZE == 0) ? 0: 1);

	// Going crappy mode, just allocating a new page for every call
	if (size != 0)
	{
		virtual_addr vaddr_begin = get_available_virtual_addr(pages_needed);
		virtual_addr vaddr = vaddr_begin;
		if (!vaddr_begin)
			return (NULL);
		for (size_t i = 0; i < pages_needed; i++)
		{
			physical_addr paddr = (physical_addr)pmmngr_alloc_block();
			vmmngr_map_page((void*)paddr, (void*)vaddr);
			vaddr += PAGE_SIZE;
		}
		return (vaddr_begin);
	}
	return (NULL);
}
