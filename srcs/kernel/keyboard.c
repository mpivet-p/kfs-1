#include "printk.h"
#include "stddef.h"
#include "term.h"
#include "io.h"

#define IS_KEY_RELEASE(x)		x & 0x80
#define KEY_RELEASE(x)			x ^ 0x80
enum keysmod
{
	KEYMOD_ALT = 56,
	KEYMOD_CTRL = 29,
	KEYMOD_SHFT = 42,
	KEYMOD_SIZE = 4
};

volatile uint8_t	in_read = 0;
volatile char		read_key = 0;

static uint8_t	is_modifier(uint8_t scancode)
{
	static modifiers[KEYMOD_SIZE] = {KEYMOD_ALT, KEYMOD_CTRL, KEYMOD_SHFT};

	for (size_t i = 0; i  < KEYMOD_SIZE; i++)
	{
		if (modifiers[i] == scancode)
			return (1);
	}
	return (0);
}

void	keyboard_handler(regs_t *re)
{
	static uint8_t	modifier = 0;
	uint8_t		scancode = inb(0x60);
	char		keys[128] = {'\0',
		'\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',/*backspace*/
		'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /*enter*/
		'\0' /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
		'\0', /*Rshift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', /*LShift*/
		'*', '\0' /*alt*/, ' ', /*space*/ 0 /*caps lock*/}; //59
	char		shift_keys[128] = {0,
		0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,
		0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,
		0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
		0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
		'*', 0, ' ', 0};//59


	(void)re;
	if (IS_KEY_RELEASE(scancode))
	{
		if (is_modifier(KEY_RELEASE(scancode)))
			modifier = 0;
	}
	else
	{
		//read_key = keyx[scancode];
		if (modifier == 0 && is_modifier(scancode))
			modifier = scancode;
		else if (modifier == 0 && scancode <= 58)
		{
			read_key = keys[scancode];
			in_read = 1;
		}
		else if (modifier == KEYMOD_SHFT && scancode <= 58)
		{
			read_key = shift_keys[scancode];
			in_read = 1;
		}
//		else
//		{
//			printk("[%d] Key pressed: %d\n", modifier, scancode);
//		}
	}
}


