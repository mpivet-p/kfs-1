#include "printk.h"
#include "io.h"

#define IS_KEY_RELEASE(x)		x & 0x80
#define KEY_RELEASE(x)			x ^ 0x80

void	keyboard_handler(regs_t *re)
{
	uint8_t		scancode = inb(0x60);
	char		keys[128] = ['\0',
		'', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',/*backspace*/
		'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /*enter*/
		'\0' /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
		'\0' /*Rshift*/, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', /*LShift*/
		'*', '\0', /*alt*/, ' ' /*space*/, 0, /*caps lock*/
	]
	(void)re;

//	if (IS_KEY_RELEASE(scancode))
//	{
//		printk("Key released: %d\n", KEY_RELEASE(scancode));
//	}
//	else
//	{
//		printk("Key pressed: %d\n", scancode);
//	}
}
