NAME=kfs.iso

SRC_DIR=srcs/
BUILD_DIR=build/
INCLUDE_DIR=includes

BOOTL_DIR=boot/
BOOTL_FILES=boot.s gdt_flush.s idt_exceptions.s load_idt.s irqs.s
BOOTL_SRCS=$(addprefix $(SRC_DIR), $(addprefix $(BOOTL_DIR), $(BOOTL_FILES)))

KERNEL_DIR=kernel/
KERNEL_FILES=kernel.c string.c term.c init_term.c gdt.c printk.c idt.c exception_handler.c puts.c irq_handler.c install_irq.c system_timer.c keyboard.c
KERNEL_SRCS=$(addprefix $(SRC_DIR), $(addprefix $(KERNEL_DIR), $(KERNEL_FILES)))

SRCS=$(KERNEL_FILES) $(BOOTL_FILES)
OBJS=$(addprefix $(BUILD_DIR), $(KERNEL_FILES:.c=.o) $(BOOTL_FILES:.s=.o))


.PHONY: all run clean fclean

all: $(NAME)

$(NAME): isodir/boot/kfs.bin
	@grub-file --is-x86-multiboot ./isodir/boot/kfs.bin && echo "multiboot check \033[32;1mOK\033[0m" || echo "multiboot check \033[31;1mFAILED\033[0m"
	grub-mkrescue -o kfs.iso isodir

isodir/boot/kfs.bin: $(OBJS)
	i686-elf-gcc -T linker.ld -o ./isodir/boot/kfs.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc

$(BUILD_DIR)%.o: $(SRC_DIR)/$(BOOTL_DIR)%.s
	mkdir build 2>/dev/null || true
	nasm -felf32 $< -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)/$(KERNEL_DIR)%.c
	mkdir build 2>/dev/null || true
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I $(INCLUDE_DIR)

run: all
	qemu-system-i386 -cdrom kfs.iso

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf ./isodir/boot/kfs.bin
	rm -rf ./kfs.iso

re: fclean all
