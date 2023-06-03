#include "idt.h"
#include "io.h"
#include "printk.h"

static char	*exception_msgs[32] = 
	{
		"Division Error",
		"Debug",
		"Non-maskable Interrupt",
		"Breakpoint",
		"Overflow",
		"Bound Range Exceeded",
		"Invalid Opcode",
		"Device Not Available",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack-Segment Fault",
		"General Protection Fault",
		"Page Fault",
		"Reserved",
		"x87 Floating-Point Exception",
		"Alignment Check",
		"Machine Check",
		"SIMD Floating-Point Exception",
		"Virtualization Exception",
		"Control Protection Exception",
		"Reserved",
		"Hypervisor Injection Exception",
		"VMM Communication Exception",
		"Security Exception",
		"Reserved"
	};

__attribute__((noreturn))
void	exception_handler(regs_t *re)
{
	if (re->int_no < 32)
	{
		printk("\n%s Exception. System Halted", exception_msgs[re->int_no]);
		__asm__ volatile ("cli; hlt");
	}
	while (1);
}
