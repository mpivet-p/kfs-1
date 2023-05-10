#include "printk.h"
#include "string.h"
#include "readline.h"
#include "io.h"

#define TERM_BUFF	255

int		readline(char *buf, size_t size);
extern  volatile uint32_t	timer_ticks;

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

static int	get_stack(void)
{
	register uint32_t esp asm("esp");
	register uint32_t ebp asm("ebp");

	//print_stack();
	return ((int)(ebp - esp));
}

void	shell(void)
{
	char	buf[TERM_BUFF + 1];

	printk("Welcome to kfsh!\nAvailable commands are `stack`, `time`, `shutdown` and `reboot`\n");
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
		else if (strcmp(buf, "stack") == 0)
			printk("Stack size is %d bytes\n", get_stack());
		else if (strlen(buf) > 0)
			printk("kfsh: Command not found.\n");
	}
}
