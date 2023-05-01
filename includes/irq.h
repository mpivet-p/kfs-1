#ifndef IRQ_H
# define IRQ_H

#define PIC_MASTER_0		0x20
#define PIC_MASTER_1		0x21
#define PIC_SLAVE_0			0xA0
#define PIC_SLAVE_1 		0xA1
#define PIC_EOI				0x20
#define IRQ_VECTOR_OFFSET	32
#define IS_IRQ_SLAVE(x)		x >= 40

void	install_irq(void);



#endif
