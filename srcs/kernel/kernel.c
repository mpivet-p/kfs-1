#include <stdint.h>
#include "string.h"
#include "multiboot.h"
#include "cursor.h"
#include "term.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "printk.h"
#include "stack.h"

void		shell(void);

void	get_memory_infos(multiboot_info_t *mbd, uint32_t magic)
{
	multiboot_memory_map_t	*mmap;
	uint32_t				addr_min = 0xFFFFFFFF;
	uint32_t				addr_max = 0x0;

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		printk("ERROR magic number mismatch\n");
	if (!(mbd->flags >> 6 & 0x1))
		printk("Invalid memory map!\n");
	mmap = mbd->mmap_addr;
	for (size_t i = 0; i < mbd->mmap_length; i++)
	{
		if (mmap[i].type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			if (mmap[i].addr < addr_min)
				addr_min = mmap[i].addr;
			if ((mmap[i].addr + mmap[i].len) > addr_max)
				addr_max = mmap[i].addr + mmap[i].len;
			printk("%x %x %x\n", mmap[i].addr, mmap[i].len, mmap[i].size);
			printk("=> %x %x\n", mmap[i].addr +  mmap[i].len, addr_max);
			//printk("=> %d\n", mmap[i].addr +  mmap[i].len, addr_max);
		}
	}
	printk("min address: 0x%x   max address: 0x%x\n", addr_min, addr_max);
}

void	kernel_main(multiboot_info_t* mbd, uint32_t magic)
{
	char	str[] = "Hello World!\nby mpivet-p\n";

	install_gdt();
	install_idt();
	install_irq();
	__asm__ volatile ("sti"); //Set Interrupt Flag

	init_term();

	get_memory_infos(mbd, magic);
	printk(str);
	//print_stack(0);
	shell();
}
