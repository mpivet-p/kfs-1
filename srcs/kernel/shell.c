#include "printk.h"
#include "string.h"
#include "stack.h"
#include "readline.h"
#include "io.h"

#define TERM_BUFF	255

extern  volatile uint32_t	timer_ticks;
void	print_physical_memory(void);
void	demo_vmalloc(void);
void	demo_kmalloc(void);
void	demo_page_panic(void);
void	demo_div_panic(void);
void	demo_paging(void);

static void reboot(void)
{
	uint8_t	kbrd_status = 0x02;

	while (kbrd_status & 0x02)
		kbrd_status = inb(0x64);

	asm volatile ("cli");
	outb(0x64, 0xFE);
loop:
	asm volatile ("hlt");
	goto loop;

}

static void	shutdown(void)
{
	outw(0x604, 0x2000);
}

void	shell(void)
{
	char	buf[TERM_BUFF + 1];

	printk("Welcome to kfsh!\nAvailable commands are:\n  - stacktrace\n"\
			"  - time\n  - shutdown\n  - reboot\n  - map\n  - kmalloc\n"\
			"  - vmalloc\n  - page_panic\n  - div_panic\n  - paging\n");
	while (1)
	{
		bzero(buf, TERM_BUFF + 1);
		printk("#> ");
		readline(buf, TERM_BUFF);
		printk("\n");
		if (strcmp(buf, "time") == 0)
			printk("Up time is %d minutes %d seconds.\n", (timer_ticks / 18) / 60, (timer_ticks / 18) % 60);
		else if (strcmp(buf, "shutdown") == 0)
			shutdown();
		else if (strcmp(buf, "reboot") == 0)
			reboot();
		else if (strcmp(buf, "stacktrace") == 0)
			print_stack(1);
		else if (strcmp(buf, "map") == 0)
			print_physical_memory();
		else if (strcmp(buf, "kmalloc") == 0)
			demo_kmalloc();
		else if (strcmp(buf, "vmalloc") == 0)
			demo_vmalloc();
		else if (strcmp(buf, "paging") == 0)
			demo_paging();
		else if (strcmp(buf, "page_panic") == 0)
			demo_page_panic();
		else if (strcmp(buf, "div_panic") == 0)
			demo_div_panic();
		else if (strlen(buf) > 0)
			printk("kfsh: Command not found.\n");
	}
}
