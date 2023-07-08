#include <stddef.h>
#include "printk.h"
#include "memory.h"


void	demo_kmalloc(void)
{
	printk("char *a = kmalloc(1)\n");
	char *a = kmalloc(1);
	printk("a = %p | ksize(a) = %d\n", a, vsize(a));
	printk("char *b = kmalloc(12000)\n");
	char *b = kmalloc(12000);
	printk("b = %p | ksize(b) = %d\n", b, vsize(b));
	printk("char *c = kmalloc(1)\n");
	char *c = kmalloc(1);
	printk("c = %p | ksize(c) = %d\n", c, vsize(c));
	printk("kfree(a)\n");
	kfree(a);
	printk("char *d = kmalloc(1)\n");
	char *d = kmalloc(1);
	printk("d = %p | ksize(d) = %d\n", d, vsize(d));
	printk("kfree(b)\n");
	kfree(b);
	printk("kfree(c)\n");
	kfree(c);
	printk("kfree(d)\n");
	kfree(d);
}

void	demo_vmalloc(void)
{
	printk("char *a = vmalloc(1)\n");
	char *a = vmalloc(1);
	printk("a = %p | vsize(a) = %d\n", a, vsize(a));
	printk("char *b = vmalloc(12000)\n");
	char *b = vmalloc(12000);
	printk("b = %p | vsize(b) = %d\n", b, vsize(b));
	printk("char *c = vmalloc(1)\n");
	char *c = vmalloc(1);
	printk("c = %p | vsize(c) = %d\n", c, vsize(c));
	printk("vfree(a)\n");
	vfree(a);
	printk("char *d = vmalloc(1)\n");
	char *d = vmalloc(1);
	printk("d = %p | vsize(d) = %d\n", d, vsize(d));
	printk("vfree(b)\n");
	vfree(b);
	printk("vfree(c)\n");
	vfree(c);
	printk("vfree(d)\n");
	vfree(d);
}

void	demo_paging(void)
{
	printk("char *a = vmalloc(1)\n");
	char *a = vmalloc(1);
	printk("vmmngr_dump_alloc(a)\n");
	vmmngr_dump_alloc(a);
	printk("char *b = vmalloc(4097)\n");
	char *b = vmalloc(4097);
	printk("vmmngr_dump_alloc(b)\n");
	vmmngr_dump_alloc(b);
	printk("vfree(a)\n");
	vfree(a);
	printk("k/v malloc(13000)\n");
	char *c = vmalloc(13000);
	printk("vmmngr_dump_alloc(c)\n");
	vmmngr_dump_alloc(c);
}

void	demo_page_panic(void)
{
	char *ptr = 0xFFF4442F;

	printk("char *ptr = 0xFFF442F\nptr[1] = 0;\n\n");
	ptr[1] = 0;
}

void	demo_div_panic(void)
{
	printk("int b = 1 / 0\n\n");
	int b = 1 / 0;
}
