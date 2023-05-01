#include "irq.h"
#include "term.h"
#include "io.h"

extern void		*irq_routines[];

void	irq_handler(regs_t *re)
{
	void	(*handler)(regs_t *re);

	puts("INT\n");
	handler = irq_routines[re->int_no - IRQ_VECTOR_OFFSET];
	if (handler)
	{
		handler(re);
	}
	if (IS_IRQ_SLAVE(re->int_no))
	{
		outb(PIC_SLAVE_0, PIC_EOI);
	}
	outb(PIC_MASTER_0, PIC_EOI);
}
