#ifndef IO_H
# define IO_H

#include <stdint.h>

static inline void	outb(uint16_t port, uint8_t val)
{
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t retval;

	asm volatile("inb %1, %0" : "=a"(retval) : "Nd"(port));
	return (retval);
}

typedef struct
{
    unsigned int	gs, fs, es, ds;							/* pushed the segs last */
    unsigned int 	edi, esi, ebp, esp, ebx, edx, ecx, eax;	/* pushed by 'pusha' */
    unsigned int 	int_no, err_code;						/* our 'push byte #' and ecodes do this */
    unsigned int 	eip, cs, eflags, useresp, ss;			/* pushed by the processor automatically */
}					regs_t;

#endif
