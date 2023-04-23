#ifndef GDT_H
# define GDT_H

#include <stddef.h>
#include <stdint.h>

# define GDT_BASE	0x00000800
# define GDT_SIZE	7

# define ACCESS_PRES(x)		x << 7
# define ACCESS_RING(x)		x << 5
# define ACCESS_TYPE(x)		x << 4
# define ACCESS_EXEC(x)		x << 3
# define ACCESS_DC(x)		x << 2
# define ACCESS_RW(x)		x << 1

# define FLAGS_GRAN(x)		x << 3
# define FLAGS_DB(x)		x << 2
# define FLAGS_LONG(x)		x << 1

# define GDT_KERN_ACCESS		ACCESS_PRES(1) | ACCESS_RING(0) | ACCESS_TYPE(1)
# define GDT_USER_ACCESS		ACCESS_PRES(1) | ACCESS_RING(3) | ACCESS_TYPE(1)

# define GDT_SEG_CODE			ACCESS_EXEC(1) | ACCESS_DC(0) | ACCESS_RW(1)
# define GDT_SEG_DATA			ACCESS_EXEC(0) | ACCESS_DC(0) | ACCESS_RW(1)
# define GDT_SEG_STACK			ACCESS_EXEC(0) | ACCESS_DC(1) | ACCESS_RW(1)

# define GDT_FLAGS				FLAGS_GRAN(1) | FLAGS_DB(1) | FLAGS_LONG(0)

/*
**	+---+-----+---+---+----+----+---+
**	| 7 | 6-5 | 4 | 3 | 2  | 1  | 0 |
**	+---+-----+---+---+----+----+---+
**	| P | DPL | S | E | DC | RW | A |
**	+===+=====+===+===+====+====+===+
**  |             | 1 | 0  | 1  | 0 | -> CODE
**  |             +---+----+----+---+
**	|             | 0 | 0  | 1  | 0 | -> DATA
**  |             +---+----+----+---+
**	|             | 0 | 1  | 1  | 0 | -> STACK
**	+===+=====+===+===+====+====+===+
**	| 1 | 00  | 1 |                 | -> KERNEL PERMISSIONS
**  +---+-----+---+                 |
**	| 1 | 11  | 1 |                 | -> USER PERMISSIONS
**  +---+-----+---+---+----+----+---+
**
**	P	- 1 bit  => Present bit, [1] for valid segment
**	DPL	- 2 bits => Desc Privilege Level, [0-3] kernel to user
**	S	- 1 bit  => Desc Type, [0] for system segment, [1] for data/code segment
**	E	- 1 bit  => Executable bit, [0] if data seg, [1] if code seg
**	DC	- 1 bit  => Direction/Conforming bit, [0] if the code segment can only be exec by same DPL
**	RW	- 1 bit  => Readable/Writable bit, [1] read is allowed for code, [1] write is allowed for data
**	A	- 1 bit  => Access bit, [0] leave clear for CPU when seg accessed
*/


typedef struct __attribute__((packed))
{
	uint16_t	limit_low;
	uint16_t	base_low;
	uint8_t		base_middle;
	uint8_t		access;
	uint8_t		limit_high:4;
	uint8_t		flags:4;
	uint8_t		base_high;

} gdt_entry;

typedef struct __attribute__((packed))
{
	uint16_t	limit;
	uint32_t	base;
} gdt_ptr;

void	install_gdt(void);

#endif
