#include <stddef.h>
#include "memory.h"

uint8_t		vmmngr_alloc_page(pt_entry *e)
{
	void *p = pmmngr_alloc_block();

	if (!p)
		return (1);

	pt_entry_set_frame(e, (physical_addr)p);
	pt_entry_add_attrib(e, I86_PTE_PRESENT);
	return (0);
}

void		vmmngr_free_page(pt_entry *e)
{
	void *p = pt_entry_pfn(*e);

	if (p)
		pmmngr_free_block(p);
	pt_entry_del_attrib(e, I86_PDE_PRESENT);
}
