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

#define		KFS_DEBUG	0

void		shell(void);

void	get_memory_infos(multiboot_info_t *mbd, uint32_t magic)
{
	uint32_t				addr_min = 0xFFFFFFFF;
	uint32_t				addr_max = 0x0;
	uint32_t				tmp;

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		printk("ERROR magic number mismatch\n");
	if (!(mbd->flags >> 6 & 0x1))
		printk("Invalid memory map!\n");
	size_t i;
    for (i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t))
    {
        multiboot_memory_map_t *mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
		if (KFS_DEBUG)
			printk("Start Addr: %x | Length: %x | Size: %d | Type: %d\n",
				mmmt->addr_low, mmmt->len_low, mmmt->size, mmmt->type);

        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			if (mmmt->addr_low < addr_min)
				addr_min = mmmt->addr_low;
			tmp = mmmt->addr_low + mmmt->len_low;
			if (addr_max < tmp)
				addr_max = tmp;
        }
    }
	if (KFS_DEBUG)
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
