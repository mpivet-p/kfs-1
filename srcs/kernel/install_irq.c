#include "irq.h"
#include "idt.h"
#include "io.h"

#include "term.h"

extern void		*irq_stub_table[];
void			timer_handler(regs_t *re);
void			keyboard_handler(regs_t *re);

void	*irq_routines[16] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

void	install_irq_handler(int irq, void (*handler)(regs_t *re))
{
	irq_routines[irq] = handler;
}

void	uninstall_irq_handler(int irq)
{
	irq_routines[irq] = 0;
}

static void	remap_irq(void)
{
	//Seding the init command to Master and Slave PIC
	outb(PIC_MASTER_0, 0x11);
	outb(PIC_SLAVE_0, 0x11);

	//Setting up Master and Slave with their beginning vectors
	outb(PIC_MASTER_1, 0x20);
	outb(PIC_SLAVE_1, 0x28);

	//Setting up slave PIC on IRQ2 for master PIC
	outb(PIC_MASTER_1, 0x04);
	outb(PIC_SLAVE_1, 0x02);

	//Setting up IRQ0 (sys timer) and IRQ1 (keyboard)
	outb(PIC_MASTER_1, 0x01);
	outb(PIC_SLAVE_1, 0x01);

	//Clearing Masks to enable IRQs reception
	outb(PIC_MASTER_1, 0x0);
	outb(PIC_SLAVE_1, 0x0);
}

void	install_irq(void)
{
	remap_irq();
	for (int i = 0; i < 16; i++)
	{
		set_idt_descriptor(IRQ_VECTOR_OFFSET + i, irq_stub_table[i], 0x8E);
	}
	install_irq_handler(0, timer_handler);
	install_irq_handler(1, keyboard_handler);
}

