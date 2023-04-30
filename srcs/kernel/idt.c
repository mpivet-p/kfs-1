#include "idt.h"

extern void			*isr_stub_table[];
extern void			load_idt(void);

__attribute__((aligned(0x10)))
static idt_entry_t	idt[256];
idtr_t		idtr;

void	set_idt_descriptor(uint8_t vector, void *isr, uint8_t flags)
{
	idt_entry_t		*desc = &idt[vector];

	desc->isr_low = (uint32_t)isr & 0xFFFF;
	desc->kernel_cs = 0x08;
	desc->attributes = flags;
	desc->isr_high = ((uint32_t)isr >> 16) & 0xFFFF;
	desc->reserved = 0;
}

void	install_idt(void)
{
	idtr.base = (uint32_t)&idt[0];
	idtr.limit = (sizeof(idt_entry_t) * 256) - 1;
	for (int i = 0; i < 32; i++)
	{
		set_idt_descriptor(i, isr_stub_table[i], 0x8E);
	}

	load_idt();
}
