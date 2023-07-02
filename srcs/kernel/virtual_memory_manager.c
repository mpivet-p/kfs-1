#include <stddef.h>
#include "memory.h"
#include "time.h"

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

void		vmmngr_map_page(void *phys, void *virt)
{
	pdirectory	*p = get_page_directory();
	pd_entry	*e = &(p->m_entries[PAGE_DIR_INDEX((uint32_t)virt)]);

    if ((*e & I86_PDE_PRESENT) != I86_PDE_PRESENT)
    {
    	ptable *table = (ptable*)pmmngr_alloc_block();
    	if (!table)
    		return ;
    	bzero(table, sizeof(ptable));

    	pd_entry *new_e = &(p->m_entries[PAGE_DIR_INDEX((uint32_t)virt)]);
    	pd_entry_add_attrib(new_e, I86_PDE_PRESENT);
    	pd_entry_add_attrib(new_e, I86_PDE_WRITABLE);
    	pd_entry_set_frame(new_e, (physical_addr)table);
    }
	ptable		*table = (ptable*)PAGE_PHYSICAL_ADDR(e);
	pt_entry	*page = &(table->m_entries[PAGE_TABLE_INDEX((uint32_t)virt)]);

	pt_entry_set_frame(page, (physical_addr)phys);
	pt_entry_add_attrib(page, I86_PTE_PRESENT);
}
