NAME=kfs-1

BOOTDIR=./srcs/boot
KERNELDIR=./srcs/kernel
BUILDDIR=./build

all: $(NAME)

$(NAME): boot kernel link check_multiboot iso


iso:
	grub-mkrescue -o kfs.iso isodir

link:
	i686-elf-gcc -T linker.ld -o ./isodir/boot/kfs.bin -ffreestanding -O2 -nostdlib $(BUILDDIR)/boot.o $(BUILDDIR)/kernel.o -lgcc

check_multiboot:
	@grub-file --is-x86-multiboot ./isodir/boot/kfs.bin && echo "multiboot check \033[32;1mOK\033[0m" || echo "multiboot check \033[31;1mFAILED\033[0m"

boot:
	nasm -felf32 $(BOOTDIR)/boot.s -o $(BUILDDIR)/boot.o

kernel:
	i686-elf-gcc -c $(KERNELDIR)/kernel.c -o $(BUILDDIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -rf build

fclean: clean
	rm -rf ./isodir/boot/kfs.bin
	rm -rf ./kfs.iso
