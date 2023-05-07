#include "printk.h"
#include "string.h"
#include "readline.h"
#include "io.h"

#define TERM_BUFF	255

int		readline(char *buf, size_t size);
extern  volatile uint32_t	timer_ticks;

void	shell(void)
{
	char	buf[TERM_BUFF + 1];

	while (1)
	{
		bzero(buf, TERM_BUFF + 1);
		printk("#> ");
		readline(&buf, TERM_BUFF);
		printk("\n");
		if (strcmp(buf, "time") == 0)
		{
			printk("Up time is %d minutes %d seconds.\n", (timer_ticks / 18) / 60, (timer_ticks / 18) % 60);
		}
		else if (strcmp(buf, "shutdown") == 0)
		{
			outw(0x604, 0x2000);
		}
		else if (strlen(buf) > 0)
			printk("kfsh: %s: Command not found.\n", buf);
	}
}
